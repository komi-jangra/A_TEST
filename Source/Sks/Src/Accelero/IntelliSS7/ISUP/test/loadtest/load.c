/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * $Id: load.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 ****************************************************************************/


/*
 * System Includes
 */
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/types.h>

/*
 * IntelliSS7 includes
 */
#include <its.h>
#include <engine.h>
#include <its_app.h>
#include <its_mutex.h>
#include <its_semaphore.h>
#include <dbc_serv.h>
#include <itu/mtp3.h>
#include <ss7_mgmt.h>
#include <clientapi.h>


/*
 * IntelliNet ISUP includes
 */
#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#else
#error "Protocol family not defined."
#endif


/*
 * Includes used for extracting cic
 */
#include <isup_cmn.h>
#include <isup_variants.h>
#include <isup_intern.h>

/* These unresolved symbols */
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;

#if defined(CCITT)
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#elif defined(ANSI)
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#endif

extern int errno;

int debug_flag =0;

typedef struct _cicInfo
{
    short cic;
    short state;
    struct _cicInfo* next;
} CicInfo;

typedef struct _configInfo
{
#if defined (CCITT)
    ushort dpc;
    ushort lpc;
#elif defined (ANSI)
    uint dpc;
    uint lpc;
#endif
    unchar sio;
    ushort numCics;
    ushort startCic;
} ConfigInfo;

CicInfo* cicInfo;
ConfigInfo configInfo = { 21, 16, 133, 100, 1}; /* defualt values */

ITS_MUTEX configLock;
ITS_SEMAPHORE loadSem;
ITS_SEMAPHORE preFuncSem;

TPOOL_THREAD* callThread;
TPOOL_THREAD* timerThread;
ITS_USHORT timerInstance;

FILE* logFp = NULL;

uint duration = 0;
ushort callsPerSec = 0; 
ushort callDuration = 0;
uint loadTestDuration = 0; /* in seconds */

#define BUF_SIZE 128
#define MAX_BUFF 2048

enum CicState { CIC_IDLE = 0,
                CIC_LR_BLOCKED,
                CIC_WAIT_FOR_R_UBL,
                CIC_RSC_WAIT_FOR_RLC,
                CIC_BUSY };

/*
 * Message counters for statistics
 */
uint ublSentSuccessCounter = 0;
uint ublSentFailCounter = 0;
uint ubaSentSuccessCounter = 0;
uint ubaSentFailCounter = 0;
uint iamSentSuccessCounter = 0;
uint iamSentFailCounter = 0;
uint rlcSentSuccessCounter = 0;
uint rlcSentFailCounter = 0;
uint rscSentSuccessCounter = 0;
uint rscSentFailCounter = 0;

uint iamReceivedCounter = 0;
uint acmReceivedCounter = 0;
uint anmReceivedCounter = 0;
uint relReceivedCounter = 0;
uint rlcReceivedCounter = 0;
uint ubaReceivedCounter = 0;
uint ublReceivedCounter = 0;
uint invalidMsgCounter = 0;

uint cicBusy = 0;
uint unexpUBL = 0;

/*
 * Function Forward Declarations
 */
void InitConfigInfo(const char* dmpFile);
void TimerDispatchFunction(TPOOL_THREAD* thr, void* arg);
void StartIAMDispatchFunction(TPOOL_THREAD* thr, void* arg);
void WorkerThreadDispatchFunction(TPOOL_THREAD* thr, ITS_HANDLE handle);
void HandleUBL(ITS_HANDLE handle, ITS_EVENT* event);
void HandleUBA(ITS_HANDLE handle, ITS_EVENT* event);
void HandleIAM(ITS_HANDLE handle, ITS_EVENT* event);
void HandleACM(ITS_HANDLE handle, ITS_EVENT* event);
void HandleANM(ITS_HANDLE handle, ITS_EVENT* event);
void HandleREL(ITS_HANDLE handle, ITS_EVENT* event);
void HandleRLC(ITS_HANDLE handle, ITS_EVENT* event);
void HandleUnexpectedMessage(ITS_HANDLE handle, ITS_EVENT* event);

static void ExecuteCommand(DBC_Server* dbc, const char* cmdLine);




/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Load test PreFunc
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
LoadPreFunc(void)
{
    char dmpFile[BUF_SIZE];
    char logFile[BUF_SIZE];
    FILE* load = NULL;
    char buf[BUF_SIZE];
    char* tmp = NULL, *dup = NULL;
    ushort len = 0;
    int ret = 0;
    TPOOL_THREAD* thread;


    DBC_SetDoCommand(ExecuteCommand);

    printf("Load: Entered PreFunc\n");
    memset( dmpFile, 0 , BUF_SIZE );
    memset( logFile, 0 , BUF_SIZE );
    memset( buf, 0 , BUF_SIZE );

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("App Dmp Name = %s\n", dmpFile);

    if (MUTEX_CreateMutex(&configLock, 0) != ITS_SUCCESS) 
    {
        printf("Failed to create mutex!\n");
        exit (1);
    }

    if (SEMA_CreateSemaphore(&loadSem, 0) != ITS_SUCCESS) 
    {
        printf("Failed to create Load Semaphore!\n");
        exit (1);
    }

    if (SEMA_CreateSemaphore(&preFuncSem, 0) != ITS_SUCCESS) 
    {
        printf("Failed to create preFunc Semaphore!\n");
        exit (1);
    }


    /* Get the load test parameters */
    load = fopen("load.ini", "r");
    if( !load ) perror("fopen");
    assert( load != NULL );

    while( !feof(load) )
    {
        fgets(buf, BUF_SIZE, load);

        tmp = strchr(buf,'=');
        if( !tmp ) continue;
        *tmp = 0; tmp++;
        while(*tmp == ' ' || *tmp == '\t') tmp++;
        dup = tmp;
        while( isdigit(*dup) ) dup++;
        *dup = 0;
        printf("key = (%s), value = (%s)\n", buf, tmp);
        if( (len = strlen(tmp)) == 0 )
        {
            printf("Error: Check your load.ini for entry %s\n", buf);
            return;
        }
        if( strstr(buf,"callsPerSec") != NULL )
        {
            callsPerSec = atoi(tmp);
            printf("callsPerSec = %d\n", callsPerSec);
        }
        else if( strstr(buf,"callDuration") != NULL )
        {
            callDuration = atoi(tmp);
            printf("callDuration = %d\n", callDuration);
        }
        else if( strstr(buf,"loadTestDuration") != NULL )
        {
            /* input is to be specified as minutes
             * in the config file
             * convert into seconds and store
             */
            loadTestDuration = 60 * atoi(tmp);
            printf("loadTestDuration = %d (in seconds) \n", loadTestDuration);
        }
        else if(strstr(buf,"opc") != NULL)
        {
            configInfo.lpc = atoi(tmp);
            printf("OPC val is %d\n", configInfo.lpc);
        }
        else if (strstr(buf,"dpc") != NULL)
        {
            configInfo.dpc = atoi(tmp);
            printf("DPC val is %d\n", configInfo.dpc);
        }
        else if (strstr(buf,"sio") != NULL)
        {
            configInfo.sio = atoi(tmp);
            printf("SIO val is %d\n", configInfo.sio);
        }
        else if (strstr(buf,"startCic") != NULL)
        {
            configInfo.startCic = atoi(tmp);
            printf("CIC number is %d\n", configInfo.startCic);
        }
        else if (strstr(buf,"noCics") != NULL)
        {
            configInfo.numCics = atoi(tmp);
            printf("CIC number is %d\n", configInfo.numCics);
        }

        if( feof(load) ) break;
    }
    fclose(load);


    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ;
        /* ISUP is getting terminated because of this return value!! */
    }

    /* printf("LOAD: SelectApp: Dispatching worker thread with instance %d\n",
            ((WORKER_Control*)thread)->worker.instance ); */

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_TRANSPORT(thread));

    /* open the log file */

    strcpy(logFile,APPL_GetName());
    strcat(logFile,".log");

    printf("App Log File Name = %s\n", logFile);

    logFp = fopen(logFile,"w");
    assert( logFp != NULL );

    fprintf(logFp,"Intellinet ISUP Load Test statistics: \n");
    fprintf(logFp,"_____________________________________ \n");
    fprintf(logFp,"calls per second = %d\n", callsPerSec);
    fprintf(logFp,"call duration = %d seconds\n", callDuration);
    fprintf(logFp,"load test duration = %d seconds\n", loadTestDuration);
    fflush(logFp);

    /* initialize the config info */
    InitConfigInfo(dmpFile);

    /* Unblock all the circuits */
    /* StartUnblocking(); */

    /* printf("UBL Sent Success = %d\n", ublSentSuccessCounter);
    printf("UBL Sent Failure = %d\n", ublSentFailCounter); */
    /* Call the above function in DBC */

    /* Start a timer thread */

    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &timerThread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return;
    }

    ret = TPOOL_DispatchOnThread(timerThread,
                                 TimerDispatchFunction,
                                (void*)NULL);
    if( ret != ITS_SUCCESS )
    {
        printf("TPOOL_DispatchOnThread \"TimerDispatchFunction\" failed in PreFunc()\n");
        exit (1);
    }

    /* Wait for some time here so that every is intialized */
    sleep(5);

    printf("Coming out of PreFunc\n");

    return;
}
 

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      InitConfigInfo
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *      This function is to modified with RESFILE Manager
 *
 *  See Also:
 ****************************************************************************/
void
InitConfigInfo(const char* dmpFile)
{
    FILE* fp = NULL;
    char buf[BUF_SIZE];
    char* tmp = NULL;
#if defined (CCITT)
    char* section = "[ITU-ISUP]";
    short destDpc = 0;
#elif defined (ANSI)
    char* section = "[ANSI-ISUP]";
    int destDpc = 0;
#endif

    short startCic = -1;
    short numCics = 0;
    CicInfo* ptr = NULL;
    short i = 0, j = 0;

    MUTEX_AcquireMutex(&configLock);

    cicInfo = (CicInfo *) malloc (sizeof(CicInfo) * 1);
    assert ( cicInfo != NULL);

    cicInfo->cic = -1;
    cicInfo->next = NULL;
    ptr = cicInfo;

    cicInfo->cic = configInfo.startCic;
    j = 1;
    for( i = j ; i < configInfo.numCics; i++ )
    {
        if( ptr->next == NULL )
        {
            ptr->next = (CicInfo *) malloc (sizeof(CicInfo) * 1);
            assert( ptr->next != NULL );
            ptr->next->next = NULL;
        }
        ptr->next->cic = configInfo.startCic + i;
        ptr = ptr->next;
    }

    configInfo.numCics = 0;
    ptr = cicInfo;
    while( ptr )
    {
        printf("CIC: *%d*\t", ptr->cic);
        fprintf(logFp,"Cic: %d\n", ptr->cic);
        fflush(logFp);
        ptr->state = IDLE;
        ptr = ptr->next;
        configInfo.numCics++;
    }
    printf("InitConfig(): Num Cics = %d\n", configInfo.numCics);
 
    fprintf(logFp,"\nNumber of Configured Cics = %d\n", configInfo.numCics);
    fflush(logFp);

    MUTEX_ReleaseMutex(&configLock);

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     StartRSC
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
StartRSC(void)
{
    CicInfo* ptr= NULL;
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;

#if defined (CCITT)
    ITS_USHORT lpc = 0;
    ITS_USHORT dpc = 0;
#elif defined (ANSI)
    uint lpc = 0;
    uint dpc = 0;
#endif
    ITS_OCTET sio = 0;

    assert( cicInfo != NULL );

    ptr = cicInfo;
    assert ( ptr != NULL );

    MUTEX_AcquireMutex(&configLock);

    lpc = configInfo.lpc;
    dpc = configInfo.dpc;
    sio = configInfo.sio;


    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    
    printf("Start Unblocking!\n");


#if defined(P)
purify_clear_leaks();
#endif
    do
    {
        usleep(1000);
#if defined(P)
purify_new_leaks();
purify_new_inuse();
purify_clear_inuse();
purify_clear_leaks();
#endif

       ieIndex = 0;
       hdr.context.cic = ptr->cic;

       ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
       ies[ieIndex].param_length = sizeof(MTP3_HEADER);

       ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                            sio, lpc, dpc, (ptr->cic & 0x000F) );
       ieIndex++;
       /* printf("ieIndex = %d\n", ieIndex); */

       ieCount = ieIndex;

       res  = ISUP_SendRSCRequest(__ISUP_Handle, &hdr, ies, ieCount);
       if(res != ITS_SUCCESS)
       {
           printf("Error in sending RSC for cic %d \n", ptr->cic);
           rscSentFailCounter++;
       }
       else
       {
           ptr->state = CIC_RSC_WAIT_FOR_RLC;
           rscSentSuccessCounter++;
       }

       printf("Reset for CIC %d\n", ptr->cic);
       ptr = ptr->next;

    } while( ptr );



    MUTEX_ReleaseMutex(&configLock);

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      main program
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
TimerDispatchFunction(TPOOL_THREAD* thr, void* arg)
{
    ITS_EVENT event;
    ITS_INT ret;
    static ITS_UINT intervTime = 0;

    ITS_INT timerDuration = 1; /* one second */

    WORKER_Control* timer = (WORKER_Control*)thr;
    timerInstance = timer->worker.instance;

    printf("TimerDispatchFunction() : Entering in Timer Thread!\n");
    memset( &event, 0, sizeof(ITS_EVENT));

    if( SEMA_WaitSemaphore(&loadSem) != ITS_SUCCESS )
    {
        printf("SEMA_WaitSemaphore() failed in Timer Thread!\n");
        return;
    }
    else
    {
    }
        

    for(;;)
    {
        sleep(timerDuration); /* sleep for a second */
        if( SEMA_PostSemaphore(&loadSem) != ITS_SUCCESS )
        {
            printf("TimerDispatchFunction(): SEMA_PostSemaphore failed\n"); 
            return;
        }
    }
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      WorkerThreadDispatchFunction
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;

    memset( &event, 0, sizeof(ITS_EVENT));

    while(1)
    {
        ret = CL_GetNextEvent(__ISUP_Handle, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }
        else
        {
            /*printf("Received some event\n");*/
        }
        fflush(stdout);

        /* DumpITSEvent(&event); */

        if ( event.src == ITS_ISUP_SRC )
        {
            if (debug_flag)
            {
                printf("Received ISUP  *%s* code %d\n",
                       ISUP_GetMsgName(event.data[0]), event.data[0] );
            }
   
        }

        switch( event.data[0] )
        {
            case ISUP_MSG_IAM:
                iamReceivedCounter++;
                HandleIAM(__ISUP_Handle, &event);
                break;

            case ISUP_MSG_ACM:
                acmReceivedCounter++;
                HandleACM(__ISUP_Handle, &event);
                break;

            case ISUP_MSG_ANM:
                anmReceivedCounter++;
                HandleANM(__ISUP_Handle, &event);
                break;

            case ISUP_MSG_REL:
                relReceivedCounter++;
                HandleREL(__ISUP_Handle, &event);
                break;

            case ISUP_MSG_RLC:
                rlcReceivedCounter++;
                HandleRLC(__ISUP_Handle, &event);
                break;
            case CL_ISUP_REGISTER_RESP:
            {
                 CL_ISUP_REG_ENTRY  regInfo;
                 printf("Received Register Response\n");

                 ret = ISUP_ReceiveRegisterIndication(__ISUP_Handle,
                                                      &event, &regInfo);
                 printf("Ret = %d\n", regInfo.ret);
                 printf("OPC = %d  DPC %d SIO %d\n",
                         MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                         MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                         (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                         (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
            break;
            }
            case CL_ISUP_DEREGISTER_RESP:
            {
                 CL_ISUP_REG_ENTRY  regInfo;
                 printf("Received DeRegister Response\n");

                 ret = ISUP_ReceiveDeRegisterIndication(__ISUP_Handle,
                                                        &event, &regInfo);
                 printf("Ret = %d\n", regInfo.ret);
                 printf("OPC = %d  DPC %d SIO %d\n",
                         MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                         MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                         (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                         (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
                 break;
             }

            case CL_ISUP_RESERVE_CIC_RESP:
            case CL_ISUP_UNRESERVE_CIC_RESP:
                 break;
            default:
                invalidMsgCounter++;
                if (debug_flag)
                {
                    printf("Received  *%s* code %d\n",
                            ISUP_GetMsgName(event.data[0]), event.data[0] );
                }
                HandleUnexpectedMessage(__ISUP_Handle, &event);
                break;
        }
        ITS_EVENT_TERM(&event);
    }
    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SendACM(ITS_HANDLE handle, ITS_EVENT *evt, ITS_HDR *hdr)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT res = 0;
    ITS_OCTET msgType;

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x000F) );

    ies[1].param_id = ISUP_PRM_BKWD_CALL_INDICATORS;
    ies[1].param_length = 0x02;
    ies[1].param_data.backwardCallIndicators.bkwd_ci[0] = 0xA1;
    ies[1].param_data.backwardCallIndicators.bkwd_ci[1] = 0xB1;

    ies[2].param_id = ISUP_PRM_ACCESS_TRANSPORT;
    ies[2].param_length = 0x03;
    ies[2].param_data.accessTransport.acc_transport[0] = 0xF1;
    ies[2].param_data.accessTransport.acc_transport[1] = 0xF2;
    ies[2].param_data.accessTransport.acc_transport[2] = 0xF3;
    ieCount = 3;

    res  = ISUP_SendACMRequest(__ISUP_Handle, hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
       printf("Error in sending RLC for cic %d \n", hdr->context.cic);
    }
    else
    {
       /* printf("Sent RLC successfully on cic %d\n", hdr->context.cic); */
    }

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SendANM(ITS_HANDLE handle, ITS_EVENT *evt, ITS_HDR *hdr)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT res = 0;
    ITS_OCTET msgType;

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x000F) );

    ieCount = 1;

    res  = ISUP_SendANMRequest(__ISUP_Handle, hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
       printf("Error in sending RLC for cic %d \n", hdr->context.cic);
    }
    else
    {
       /* printf("Sent RLC successfully on cic %d\n", hdr->context.cic); */
    }

}

static void
SendREL(ITS_HANDLE handle, ITS_EVENT *evt, ITS_HDR *hdr)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT res = 0;
    ITS_OCTET msgType;

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x000F) );

   ies[1].param_id = ISUP_PRM_CAUSE_INDICATORS;
    SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[1].param_data.causeIndicator,
                   CI_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[1].param_data.causeIndicator, CI_CS_ANSI);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[1].param_data.causeIndicator,
                    CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[1].param_data.causeIndicator, CI_EXTEND);
    SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[1].param_data.causeIndicator,
                 CI_CAUSE_NORMAL_UNSPECIFIED);
    ies[1].param_length = 2;


    ieCount = 2;

    res  = ISUP_SendRELRequest(__ISUP_Handle, hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
       printf("Error in sending RLC for cic %d \n", hdr->context.cic);
    }
    else
    {
       /* printf("Sent RLC successfully on cic %d\n", hdr->context.cic); */
    }

}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HandleIAM(ITS_HANDLE handle, ITS_EVENT* event)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;
    ITS_OCTET msgType;
    CicInfo* ptr = NULL;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveIAMIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("ISUP_ReceiveIAMIndication Failed!\n");
        return;
    }

    SendACM(handle, event, &hdr);
    SendANM(handle, event, &hdr);
    SendREL(handle, event, &hdr);
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleACM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HandleACM(ITS_HANDLE handle, ITS_EVENT* event)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;
    ITS_OCTET msgType;
    CicInfo* ptr = NULL;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveACMIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("ISUP_ReceiveACMIndication Failed!\n");
        return;
    }
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HandleANM(ITS_HANDLE handle, ITS_EVENT* event)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;
    ITS_OCTET msgType;
    CicInfo* ptr = NULL;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveANMIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("ISUP_ReceiveIANMIndication Failed!\n");
        return;
    }

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HandleREL(ITS_HANDLE handle, ITS_EVENT* event)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;
    ITS_OCTET msgType;
    CicInfo* ptr = NULL;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveRELIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("ISUP_ReceiveRELIndication Failed!\n");
    }

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr.context.cic & 0x000F) );

    ieCount = 1;


    res  = ISUP_SendRLCRequest(__ISUP_Handle, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
       rlcSentFailCounter++;
       printf("Error in sending RLC for cic %d \n", hdr.context.cic);
    }
    else
    {
       /* printf("Sent RLC successfully on cic %d\n", hdr.context.cic); */
       rlcSentSuccessCounter++;
    }

    /* traverse to the cic in the list and set state to IDLE */

    MUTEX_AcquireMutex(&configLock);
    ptr = cicInfo;

    while( ptr )
    {
        if( ptr->cic != hdr.context.cic )
        {
            ptr = ptr->next;
            continue;
        }
        ptr->state = CIC_IDLE;
        if (debug_flag)
        {
            printf("Received REL making CIC =  %d idle\n", ptr->cic);
        }
        break;
    }

    if( ptr == NULL )
    {
        printf("HandleREL:Couldn't find the cic!\n");
    }
    MUTEX_ReleaseMutex(&configLock);
    
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HandleRLC(ITS_HANDLE handle, ITS_EVENT* event)
{
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;
    ITS_OCTET msgType;
    CicInfo* ptr = NULL;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveRLCIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("ISUP_ReceiveRLCIndication Failed!\n");
    }

    /*printf("cic for received RLC = %d\n", hdr.context.cic);*/

    /* traverse to the cic in the list and set state to IDLE */

    MUTEX_AcquireMutex(&configLock);
    ptr = cicInfo;

    while( ptr )
    {
        if( ptr->cic != hdr.context.cic )
        {
            ptr = ptr->next;
            continue;
        }
        ptr->state = CIC_IDLE;
        break;
    }
    if( ptr == NULL )
    {
        printf("HandleRLC:Couldn't find the cic!\n");
    }
    MUTEX_ReleaseMutex(&configLock);
    
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
HandleUnexpectedMessage(ITS_HANDLE handle, ITS_EVENT* event)
{
    return;
}

static void
BuildIAMIEs(ITS_ISUP_IE *ies, ITS_USHORT *ieCount, ITS_USHORT cic)
{
    int ieIndex =0;
    
    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                                    configInfo.sio, configInfo.lpc,configInfo.dpc, (cic & 0x000F) );

    /* printf("CIC in IAM = %d\n", cic); */

    ieIndex++;

    ies[ieIndex].param_id = ISUP_PRM_NATURE_CONN_INDICATORS;
    ies[ieIndex].param_length = sizeof(ISUP_CONNECTION_INDICATORS);
    ies[ieIndex].param_data.connectionIndicator.subfields4 = 0x00;
                 
    ieIndex++;

    ies[ieIndex].param_id = ISUP_PRM_FWD_CALL_INDICATORS;
    ies[ieIndex].param_length = sizeof(ISUP_FORWARD_CALL_INDICATORS);
    ies[ieIndex].param_data.forwardCallIndicators.fwd_ci[0] = 0x20;
    ies[ieIndex].param_data.forwardCallIndicators.fwd_ci[1] = 0x01;

    ieIndex++;

    ies[ieIndex].param_id = ISUP_PRM_CALLING_PARTY_CATEGORY;
    ies[ieIndex].param_length = sizeof(ISUP_CALLING_PARTY_CATEGORY);
    ies[ieIndex].param_data.callingPartyCategory.cat = 0x0A;

    ieIndex++;

#if defined(CCITT)
    ies[ieIndex].param_id = ISUP_PRM_TX_MEDIUM_REQMNT;
    ies[ieIndex].param_length = sizeof(ISUP_TX_MEDIUM_REQUIREMENT);
    ies[ieIndex].param_data.txMediumRequirement.tmr = 0x02;

    ieIndex++;
#elif defined (ANSI)
    ies[ieIndex].param_id = ISUP_PRM_USER_SERVICE_INFO;
    ies[ieIndex].param_length = sizeof(ISUP_USER_SERVICE_INFO);
    ies[ieIndex].param_data.userServiceInfo.coding = 0xC0; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.trans_mode = 0x90; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.config = 0xA2; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.symmetry = 0x07; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer1 = 0x03; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer1_ext_user_rate = 0x10; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer1_ext_rate_adaption_3b = 0x04; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer1_ext_parity = 0x77; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer1_ext_modem_type = 0x62; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer2 = 0x60; /* ITS_OCTET */
    ies[ieIndex].param_data.userServiceInfo.layer3 = 0x38; /* ITS_OCTET */

    ieIndex++;
#endif

    ies[ieIndex].param_id = ISUP_PRM_CALLED_PARTY_NUM;
    ies[ieIndex].param_data.calledPartyNum.addr_ind = 0x01;
    ies[ieIndex].param_data.calledPartyNum.num_plan = 0x10;
    memset( &(ies[ieIndex].param_data.calledPartyNum.dgts), 1,
                 MAX_NB_OCTETS_DIGITS);
    ies[ieIndex].param_length = sizeof(ISUP_CALLED_PARTY_NUM);

    ieIndex++;
    *ieCount = ieIndex;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
StartIAMDispatchFunction(TPOOL_THREAD* thr, void* arg)
{
    time_t t_loc1;
    time_t t_loc2;
    CicInfo* ptr = NULL;

    ushort cic = 0;
    uint callCount = 0;

    struct timeb st;
    struct timeb en;
    struct timeval sel;

    ushort ieCount = 0;
    ushort ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    int res = 0;
    ushort timerDuration = 1; /* one second */

    ulong interCallGap = 0; /* in micro seconds */
    ulong initCallGap = 0; /* in micro seconds */

    interCallGap = ( 1 * 1000 * 1000 ) / (callsPerSec);
    initCallGap = interCallGap * 2;

    memset(&st, 0, sizeof(st));
    memset(&en, 0, sizeof(en));
    memset(&sel, 0, sizeof(sel));

    printf("Entered IAM Dispatch function!\n");

    t_loc1 = time(&t_loc1);
    fprintf (logFp,"IAM:Load test start time = %s\n", ctime( &t_loc1 ));
    fflush(logFp);

    fprintf (logFp,"Duration Start = %d\n", duration);
    fflush(logFp);

    /* Post the semaphore here so that timer thread starts */

     if( SEMA_PostSemaphore(&loadSem) != ITS_SUCCESS )
     {
         printf("IAMD(): SEMA_PostSemaphore failed\n"); 
         return;
     }
     else
     {
     }


    for( duration = 0; duration < loadTestDuration; duration++)
    {
        interCallGap = ( 1 * 1000 * 1000 ) / (callsPerSec);
        initCallGap = interCallGap * 2;
        for(callCount = 0; callCount < callsPerSec; callCount++)
        {
            if(ftime(&st) < 0)
            perror("ftime()"), exit(1);

            ieIndex = 0;
            ieCount = 0;
            memset( (char*)&ies[0], 0, sizeof(ies) );
            memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

            MUTEX_AcquireMutex(&configLock);

            ptr = cicInfo;

            while( ptr )
            {
#if defined(EVEN)
                if( ptr->state != CIC_IDLE || (ptr->cic % 2 != 0))
#elif defined(ODD)
                if( ptr->state != CIC_IDLE || (ptr->cic % 2 == 0))
#elif defined(ALL)
                if( ptr->state != CIC_IDLE)
#endif
                {
                    ptr = ptr->next;
                    continue;
                }

                /* get hold of the free cic  and mark it BUSY */
                cic = ptr->cic; 
                ptr->state = CIC_BUSY;
                break;
            }

            /* if ptr is NULL means reached end of list */
            /* no cics are free */
            /* so wait for a while and try again */
            if( ptr == NULL )
            {
                MUTEX_ReleaseMutex(&configLock);
                printf("Try again!\n");
                cicBusy++;

                sel.tv_sec = 0;
                sel.tv_usec = initCallGap;

                TIMERS_USleep(initCallGap);
                continue;
            }

            MUTEX_ReleaseMutex(&configLock);


            /* Start out an IAM on this cic */

            hdr.type = ITS_ISUP;
            hdr.context.cic = cic;
            BuildIAMIEs(ies, &ieCount, cic);

            res  = ISUP_SendIAMRequest(__ISUP_Handle, &hdr, ies, ieCount);
            if(res != ITS_SUCCESS)
            {
                printf("Error in sending IAM for cic %d \n", hdr.context.cic);
                iamSentFailCounter++;
                TIMERS_USleep(interCallGap);
                continue;
            }
            else
            {
                iamSentSuccessCounter++;
            }

            if(ftime(&en) < 0)
            perror("ftime()"), exit(1);
            
            interCallGap = ( ((en.time - st.time) * 1000) +
                              (en.millitm - st.millitm) );
            interCallGap *= 1000;

            if( interCallGap > 1000000 )
            {
                printf("InterCall Gap is greater than a second!\n");
                continue;
            }

            sel.tv_sec = 0;
            sel.tv_usec = interCallGap;

            TIMERS_USleep(interCallGap);
        }

        if( SEMA_WaitSemaphore(&loadSem) != ITS_SUCCESS )
        {
            printf("SEMA_WaitSemaphore() failed in IAM Thread!\n");
            return;
        }
    }

    fprintf (logFp,"Duration End = %d\n", duration);
    fprintf (logFp,"CallCount per Duration = %d\n", callCount);

    t_loc2 = time(&t_loc2);
    fprintf (logFp,"IAM:Load test End time = %s\n", ctime( &t_loc2 ));
    fflush(logFp);

    printf("Configured duration of load test = %d seconds\n", loadTestDuration);
    printf("Actual duration of load test = %d seconds\n", (t_loc2 - t_loc1));

    /* signal the PreFunc */
    SEMA_PostSemaphore(&preFuncSem);

    return;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleIAM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
LoadPostFunc(void)
{
    time_t t_loc;
    CicInfo* ptr = NULL;

    printf("Load: Entered PostFunc\n");

    t_loc = time(&t_loc);
    fprintf (logFp,"PostFun():Load test End time = %s\n", ctime( &t_loc ));
    fflush(logFp);


    /* Free the config Info */

    if( cicInfo )
    {
        ptr = cicInfo;
        /* traverse the list and free all cics */
        cicInfo = cicInfo->next;
        free( ptr );
    }



    fprintf(logFp,"SentOut UBL SuccessCounter = %d\n", ublSentSuccessCounter);
    fprintf(logFp,"SentOut UBL FailCounter    = %d\n", ublSentFailCounter);

    fprintf(logFp,"SentOut UBA SuccessCounter = %d\n", ubaSentSuccessCounter);
    fprintf(logFp,"SentOut UBA FailCounter    = %d\n", ubaSentFailCounter);

    fprintf(logFp,"SentOut IAM SuccessCounter = %d\n", iamSentSuccessCounter);
    fprintf(logFp,"SentOut IAM Fail Counter   = %d\n", iamSentFailCounter);

    fprintf(logFp,"SentOut RLC SuccessCounter = %d\n", rlcSentSuccessCounter);
    fprintf(logFp,"SentOut RLC Fail Counter   = %d\n", rlcSentFailCounter);

    fprintf(logFp,"Received IAM Counter = %d\n", iamReceivedCounter);
    fprintf(logFp,"Received ACM Counter = %d\n", acmReceivedCounter);
    fprintf(logFp,"Received ANM Counter = %d\n", anmReceivedCounter);
    fprintf(logFp,"Received REL Counter = %d\n", relReceivedCounter);
    fprintf(logFp,"Received RLC Counter = %d\n", rlcReceivedCounter);
    fprintf(logFp,"Received UBL Counter = %d\n", ublReceivedCounter);
    fprintf(logFp,"Received UBA Counter = %d\n", ubaReceivedCounter);
    fprintf(logFp,"Received Unexpected Counter = %d\n", invalidMsgCounter);
    fprintf(logFp,"Call Attempts when all cics Busy = %d\n", cicBusy++);
    fprintf(logFp,"Number of Unexpected UBLs = %d\n", unexpUBL);


    fflush(logFp);
    fclose(logFp);

    /* raise(SIGABRT); */

#if 0
    /* Delete the mutexes */
printf("Deleting Muexs!\n");
    MUTEX_DeleteMutex(&configLock);

    /* Delete the semaphores */
    printf("Deleting Semahores!\n");
    SEMA_DeleteSemaphore(&loadSem);
    SEMA_DeleteSemaphore(&preFuncSem);


    printf("Deleting callThread\n");
    WORKER_DeleteWorker( (WORKER_Control *) callThread );
    printf("Deleting TimerThread\n");
    WORKER_DeleteWorker( (WORKER_Control *) timerThread );
#endif


    printf("Before Return in My Post Func!\n");
    printf("PostFunc:Before Abort\n");
    /*raise(SIGABRT);*/
    printf("PostFunc:After Abort\n");

    return;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     ExecuteCommand 
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    int ret = 0;
    static ushort iamflag = 1;
    static ushort mtp3flag = 0;
    char buf[MAX_BUFF];

    static ITS_BOOLEAN firstCall = ITS_TRUE;
    static ITS_SHORT instance;
    TRANSPORT_Control* tc = NULL;

    printf("Entered ExecuteCommand !\n");

    assert( dbc != NULL );

    if(firstCall)
    {
        firstCall = ITS_FALSE;
        tc = TRANSPORT_FindTransportByName("Debug Console");
        ITS_C_ASSERT( tc != NULL );

        instance = TRANSPORT_INSTANCE(tc);
    }

    memset(buf, 0, MAX_BUFF);

    /* Start Adding Command fro here! */

    if(DBC_Cmd(dbc, "startRSC", "Start Reset of Circuits Now", "", ""))
    {
        StartRSC();
    }

    else if(DBC_Cmd(dbc, "startIAM", "Start IAM Thread Now", "", ""))
    {
        if( iamflag == 0 )
        {
            printf("IAM Thread already started!\n");
            sprintf(buf,"IAM Thread already started!");
            DBC_AppendText(dbc, buf);
            DBC_SendCommandResult(dbc, instance);
            iamflag = 0;
        }

        printf("*********** Starting IAM Thread **************\n");

        /* Dispatch a worker for StartIAMProcedure */

        if( (ret = TPOOL_GetFirstAvailThread(workerPool, &callThread)) != ITS_SUCCESS )
        {
                printf("***No more worker threads!\n");
                return;
        }

        ret = TPOOL_DispatchOnThread(callThread,
                                      StartIAMDispatchFunction,
                                      (void*)NULL);
        if( ret != ITS_SUCCESS )
        {
                printf("TPOOL_DispatchOnThread failed in PreFunc()\n");
                exit (1);
        }

        iamflag = 0;
    }
    else if (DBC_Cmd(dbc, "reg", "Register Message", "<opc>,<dpc>,<sio>",
                     "<opc# > <dpc#> <sio#>"))
    {
        ITS_UINT opc, dpc;
        ITS_UINT sio;
        MTP3_HEADER mtp3;

        memset(&mtp3, 0, sizeof(MTP3_HEADER));
        printf("DBC_Cmd : Inside Register Command !!\n");

        /* Need to send Register Event */

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &opc, &dpc, &sio);

        MTP3_RL_SET_DPC_VALUE(mtp3.label, dpc);
        MTP3_RL_SET_OPC_VALUE(mtp3.label, opc);
        mtp3.sio = sio;
        printf("The OPC = %d \t DPC = %d \t SIO = %d\n", opc,dpc,sio);
        ret = CL_Register(__ISUP_Handle, &mtp3, 1);
    }
    else if(DBC_Cmd(dbc, "STOPLOAD", "Stop Load test", "", ""))
    {
        duration = loadTestDuration;

    }
    else if(DBC_Cmd(dbc, "showcallspsec", "Shows calls/sec running", "", ""))
    {
        sprintf(buf,"Current calls/sec set = %d\n", callsPerSec);
        DBC_AppendText(dbc, buf);
        DBC_SendCommandResult(dbc, instance); 
    }
    else if(DBC_Cmd(dbc, "endebug", "Enable the debug flag", "", ""))
    {
        debug_flag = 1;
    }
    else if(DBC_Cmd(dbc, "desdebug", "Desable the debug flag", "", ""))
    {
        debug_flag = 0;
    }
    else if(DBC_Cmd(dbc, "chcallspsec", "increase/decrease call/sec ", "", ""))
    {
        int inc =0;
        ret = sscanf(cmdLine, "%s" "%d", buf, &inc);
        
        callsPerSec +=  inc; 
        if (callsPerSec <= 0)
        { 
            callsPerSec = 1;
        }
        sprintf(buf, "Current calls per sec set = %d \n", callsPerSec);
        DBC_AppendText(dbc, buf);
        DBC_SendCommandResult(dbc, instance);
    }
    else if (DBC_Cmd(dbc, "stat", "Print Statistics", "", ""))
    {
        /* send stats to client */
        /* Idea is to use the debug console to 
         * view load statistics whenever required.
         * The stats info should be sent to the 
         * DebugConsole client over a socket
         */

        if (iamReceivedCounter)
        {
            sprintf(buf,"IAM Received = %d\n",iamReceivedCounter);
            DBC_AppendText(dbc, buf);
            sprintf(buf,"RLC Received = %d\n",rlcReceivedCounter);
            DBC_AppendText(dbc, buf);
        }
        if (iamSentSuccessCounter)
        {
            sprintf(buf,"IAM Sent = %d\n",iamSentSuccessCounter);
            DBC_AppendText(dbc, buf);
            sprintf(buf,"ACM Received = %d\n",acmReceivedCounter);
            DBC_AppendText(dbc, buf);
            sprintf(buf,"ANM Received = %d\n",anmReceivedCounter);
            DBC_AppendText(dbc, buf);
            sprintf(buf,"REL Received = %d\n",relReceivedCounter);
            DBC_AppendText(dbc, buf);
            sprintf(buf,"RLC Sent = %d\n",rlcSentSuccessCounter);
            DBC_AppendText(dbc, buf);
        }

        DBC_SendCommandResult(dbc, instance);
    }

    return;
}
