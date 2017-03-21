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
 * ID:$Id: ISUP_Test.c,v 1.1.1.1 2007-10-08 11:12:21 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:24:57  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:15  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:06  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 8.5  2005/03/21 13:54:17  cvsadmin
 * LOG:PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG:Revision 1.3.2.2  2003/05/09 05:30:45  ssingh
 * LOG:Changes back ported from current to 6.3
 * LOG:
 * LOG:Revision 8.3  2003/03/28 07:35:58  ssingh
 * LOG:Removed Extra reference of accessing STACK functionality.
 * LOG:Peg things removed. Will be accessed through MML.
 * LOG:
 * LOG:Revision 8.2  2003/02/27 06:13:35  akumar
 * LOG:Added ITU Variant
 * LOG:
 * LOG:Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG:Begin PR6.4
 * LOG:
 * LOG:Revision 1.3  2003/01/30 13:11:07  ssingh
 * LOG:VCIC related changes and CIC initialization as LBLOCKED.
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>

#include <its.h>
#include <engine.h>
#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <its_iniparse.h>
#include <dbc_serv.h>
#include <its_dsm_stub.h>
#include <ss7_mgmt.h>

#include <isup_intern.h>
#include "ISUP_Test.h"
#include "ISUP_SendMsg.h"
#include "ISUP_PrintMsg.h"
#include "ISUP_ProcessMsg.h"

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#else
#error "Protocol family not defined."
#endif

#if defined (CCITT)
static const char* section = "ITU-ISUP";
#elif defined (ANSI)
static const char* section = "ANSI-ISUP";
#else
#error "Protocol Not Defined"
#endif

#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#define HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack ISS7_ANSI_Stack
#define HANDLE ISS7_ANSI_Stack
#endif

#define NEWCODE 0
#define OLDCODE 1

#if NEWCODE
static TRANSPORT_Control* tc = NULL;
static ITS_SHORT instance = 0;
static ITS_HDR hdr;
#endif

ITS_MUTEX configLock;

static void InitCircuitInfo(const char* dmpFile);
static void WorkerThreadDispatchFunction(TPOOL_THREAD* thr, ITS_HANDLE handle);
static void DumpITSEvent(ITS_EVENT* ev);
int    RouteApp(ITS_HDR *hdr,ITS_EVENT *event);
void   ExecuteCommand(DBC_Server *dbc, const char *cmdLine);

int    GetOpcDpcInfo(OpcDpcInfo*);

extern int ValidateCicRange(const char* cmdLine, ITS_USHORT* startcic, 
                            ITS_USHORT* endcic);
extern int PrintCICRecInfo(int opc, int dpc, int sio, int cic);
extern int PrintCicRangeInfo(ITS_USHORT opc, ITS_USHORT dpc, ITS_USHORT sio,
                             ITS_USHORT startcic, ITS_USHORT endcic);

void   ISUP_HandleLocalCongestion (ITS_POINTER object, ITS_POINTER userData, 
                                   ITS_POINTER callData);
void   ISUP_HandleMTP3Mgmt (ITS_POINTER object, ITS_POINTER userData, 
                            ITS_POINTER callData);

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called when App is initialized
 *
 *  Input Parameters:
 *      NONE.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void ftestPreFunc(void)
{
    static char dmpFile[256];

    printf("Ftest: Entered PreFunc\n");

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("App Dmp Name = %s\n", dmpFile);

    printf("Before DBC_SetDoCommand() in ftestPreFunc\n");

    DBC_SetDoCommand(ExecuteCommand);

    printf("After DBC_SetDoCommand() in ftestPreFunc\n");

    /* initialize the circuit Info */
    InitCircuitInfo(dmpFile);

    printf("Ftest: Ready to accept Commands!\n");

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called when the App is Terminating.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void ftestPostFunc(void)
{
    printf("Ftest: Entered PostFunc\n");

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called for Routing Purpose.
 *
 *  Input Parameters:
 *      hdr - provides context for individual messages.
 *      event - Message to be routed in tlv format.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
RouteApp(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;


    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
    }

    ROUTE_AddApplication( ((WORKER_Control*)thread)->worker.instance, &routeHeader);

    printf("Ftest: RouteApp: Dispatching worker thread\n");

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_BACK_PTR(thread));

    return ( ((WORKER_Control*)thread)->worker.instance );
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Dispatches the Event to a Thread.
 *
 *  Input Parameters:
 *      thr - Pointer to Pool of Threads.
 *      handle - void pointer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;
    printf("Application:: Instance Number of Worker is ... %d\n",workerInstance);

    memset(&event,0,sizeof(event));

    while(1)
    {
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }

        printf("Application:: Event Src = %x\n", event.src);
        DumpITSEvent(&event);

        if ( event.src == ITS_ISUP_SRC )
        {

            printf("Application:: Decoding the Received Event from ISUP:\n");
            if (ISUP_ReceiveMsg(HANDLE, &event) == ITS_SUCCESS)
            {
                printf("Application:: Worker Thread: ISUP msg receive success\n");
                printf("------------------------------------------------------\n");
            }
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function porvides HEX dump of the Event.
 *
 *  Input Parameters:
 *      ev - Received Event from Stack.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DumpITSEvent(ITS_EVENT* ev)
{
    int i;

    switch(ev->src)
    {
        case ITS_ISUP_CCITT_SRC:
             printf("Event Source is ITS_ISUP_CCITT_SRC\n");
             break;
        case ITS_ISUP_ANSI_SRC:
             printf("Event Source is ITS_ISUP_ANSI_SRC\n");
             break;
        case ITS_MTP3_CCITT_SRC:
             printf("Event Source is ITS_MTP3_CCITT_SRC\n");
             break;
        case ITS_MTP3_ANSI_SRC:
             printf("Event Source is ITS_MTP3_ANSI_SRC\n");
             break;
        case ITS_TIMER_SRC:
             printf("Event Source is ITS_TIMER_SRC\n");
             break;
        default:
             printf("Event Source is * UNKNOWN * (%d)\n", ev->src);
             break;
    }

    printf("Event Length: %d\n", ev->len);
    printf("Event Dump follows:\n");

    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);
        if (!((i+1) % 20))
        {
            printf("\n");
        }
    }
    if ((i+1) % 20)
    {
        printf("\n");
    }

    printf("------------------------------------------------------\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      InitCircuitInfo
 *
 *  Input Parameters:
 *      const char* dmpFile
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
static void
InitCircuitInfo(const char* dmpFile)
{
    FILE* fp = NULL;
    char buf[128];
    char* tmp = NULL;
#if defined(ANSI)
    char* section = "[ANSI-ISUP]"; 
#elif defined(CCITT)
    char* section = "[ITU-ISUP]"; 
#endif

    short startCic = -1;
    short numCics = 0;
    short cicCount = 0;
    short i = 0;

    assert(dmpFile != NULL);

    MUTEX_AcquireMutex(&configLock);

    cicStatus[cicCount].cic_num=-1;

    fp  = fopen(dmpFile, "r");
    assert(fp != NULL);

    while( !feof(fp) )
    {
        fgets(buf, 128, fp);

        buf[strlen(buf)-1] = 0;

        if( strcmp(section,buf) == 0 )
        {
            printf("Entered ISUP : %s\n", buf);
            break;
        }
    }

    while( !feof(fp) )
    {
        fgets(buf, 128, fp);
        buf[strlen(buf)-1] = 0;

        tmp = strchr((const char*)buf,'=');
        if( !tmp ) continue;
        *tmp = 0;
        tmp++;

        if((strcmp("startCic",buf) == 0))
        {
            cicStatus[cicCount].cic_num = RESFILE_ParseNum(tmp);
            startCic = RESFILE_ParseNum(tmp);
        }
        else if((strcmp("numberCics",buf) == 0))
        {
            numCics = RESFILE_ParseNum(tmp);

            for( i = 0; i < numCics; i++)
            {
                cicStatus[cicCount].cic_num = startCic + i;
                cicCount+=1;
            }
        }

        if( feof(fp) ) break;
    }

    for(i=0; i< cicCount; i++)
    {
#if defined(CCITT)
        ISUP_CICStateFromParts_CCITT(&cicStatus[i].cic_state, CKTS_LRBLOCKED,
                                 CKTS_IDLE_CTK, CKTS_ACTIVE);
#elif defined(ANSI)
        cicStatus[i].cic_state = CKTS_IDLE_LBLOCKED;
#endif
        cicStatus[i].fsm_state = CPC_IDLE;
        printf("CIC index = %3d | CIC number = %3d | CIC State : %d  and FSM State : %d\n", 
                              i, cicStatus[i].cic_num, cicStatus[i].cic_state, 
                                                       cicStatus[i].fsm_state);
    }

    numOfCICs = cicCount;

    printf("InitCircuitInfo(): Total Number of Cics = %d\n", numOfCICs);

    sleep(2);

    MUTEX_ReleaseMutex(&configLock);

    fclose(fp);

    return;
}

#if OLDCODE
#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
        int len = 0; \
        printf("Command entered = %s\n", cmdLine); \
        tmp = strchr(cmdLine,' '); \
        if( !tmp) tmp = strchr(cmdLine, '\t'); \
        if(!tmp) \
        { \
           printf("Usage: %s <cic>\n",x); \
           return; \
        } \
        else \
        { \
          *tmp = 0; tmp++; \
           while(*tmp == ' ' || *tmp == '\t') tmp++; \
           dup = tmp; \
           while( isdigit(*dup) ) dup++; \
           *dup = 0; \
           if( (len = strlen(tmp)) == 0 ) \
           { \
               printf("Usage: %s <cic>\n",x); \
               return; \
           } \
           hdr.context.cic = atoi(tmp); \
        } \
        }
#endif

#if NEWCODE
#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
        int len = 0; \
        char buf[ITS_PATH_MAX]; \
        printf("Command entered = %s\n", cmdLine); \
        tmp = strchr(cmdLine,' '); \
        if( !tmp) tmp = strchr(cmdLine, '\t'); \
        if(!tmp) \
        { \
           printf("Usage: %s <cic>\n",x); \
           sprintf(buf,"Usage: %s <cic>\n",x); \
           DBC_AppendText(dbc, buf); \
           DBC_SendCommandResult(dbc,instance); \
           return; \
        } \
        else \
        { \
          *tmp = 0; tmp++; \
           while(*tmp == ' ' || *tmp == '\t') tmp++; \
           dup = tmp; \
           while( isdigit(*dup) ) dup++; \
           *dup = 0; \
           if( (len = strlen(tmp)) == 0 ) \
           { \
               printf("Usage: %s <cic>\n",x); \
               return; \
           } \
           hdr.context.cic = atoi(tmp); \
        } \
        }
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads ISUP commands along with arguments and executes
 *      it to print the output on Console or send the Msg to ISUP
 *
 *  Input Parameters:
 *      dbc - Pointer to the DBC_Server
 *      cmdLine - String to be read from the Command Line
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    ITS_INT result = 0;
    ITS_HDR hdr;

    ITS_USHORT startcic = 0;
    ITS_USHORT endcic = 0;

    static ITS_BOOLEAN firstCall = ITS_TRUE;
    static OpcDpcInfo info;

#if OLDCODE /* retianed */
    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);
    }
#endif

#if NEWCODE
    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);

        tc = TRANSPORT_FindTransportByName("Debug Console");
        ITS_C_ASSERT( tc != NULL );

        instance = TRANSPORT_INSTANCE(tc);
        printf("Instance of DBC = %d\n", instance);
    }
#endif

    ITS_C_ASSERT(dbc != NULL);

    printf("------------------------------------------------------\n");

    if (DBC_Cmd(dbc, "acm", "SendACM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("acm");
        result = TestSendACMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "anm", "SendANM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("anm");
        result = TestSendANMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send ANM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "bla", "SendBLA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("bla");
        result = TestSendBLARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send BLA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "blo", "SendBLO", "<cic>", ""))
    {
        VALIDATE_CMDLINE("blo");
        result = TestSendBLORequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send BLO return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ccr", "SendCCR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ccr");
        result = TestSendCCRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CCR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cfn", "SendCFN", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cfn");
        result = TestSendCFNRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CFN return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgb", "SendCGB", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgb");
        result = TestSendCGBRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGB return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgba", "SendCGBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgba");
        result = TestSendCGBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgu", "SendCGU", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgu");
        result = TestSendCGURequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGU return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgua", "SendCGUA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgua");
        result = TestSendCGUARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGUA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cot", "SendCOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cot");
        result = TestSendCOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send COT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cpg", "SendCPG", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cpg");
        result = TestSendCPGRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CPG return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cqm", "SendCQM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cqm");
        result = TestSendCQMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CQM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fot", "SendFOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fot");
        result = TestSendFOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FOT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "grs", "SendGRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("grs");
        result = TestSendGRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send GRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "gra", "SendGRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("gra");
        result = TestSendGRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send GRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "iam", "SendIAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("iam");
        result = TestSendIAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inf", "SendINF", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inf");
        result = TestSendINFRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send INF return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inr", "SendINR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inr");
        result = TestSendINRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send INR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "lpa", "SendLPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lpa");
        result = TestSendLPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "pam", "SendPAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("pam");
        result = TestSendPAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send PAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rel", "SendREL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rel");
        result = TestSendRELRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send REL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "res", "SendRES", "<cic>", ""))
    {
        VALIDATE_CMDLINE("res");
        result = TestSendRESRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RES return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rlc", "SendRLC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rlc");
        result = TestSendRLCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RLC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rsc", "SendRSC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rsc");
        result = TestSendRSCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RSC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sus", "SendSUS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sus");
        result = TestSendSUSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SUS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "uba", "SendUBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("uba");
        result = TestSendUBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ubl", "SendUBL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ubl");
        result = TestSendUBLRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UBL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ucic", "SendUCIC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ucic");
        result = TestSendUCICRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UCIC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cic", "PrintCicInfo", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cic");
        PrintCICRecInfo(info.opc, info.dpc, info.sio, hdr.context.cic);
        printf("\n");
    }
    else if (DBC_Cmd(dbc, "cicrange", "CicInfo for a range", "<startcic endcic>", ""))
    {
        /* printf("ExecuteCommand:cmdLine = *%s*\n",cmdLine); */
        if(ValidateCicRange(cmdLine, &startcic, &endcic) != ITS_SUCCESS)
        {
            return;
        }
        /* printf("startcic = %d\n",startcic); */
        /* printf("endcic = %d\n",endcic); */

        PrintCicRangeInfo(info.opc, info.dpc, info.sio, startcic, endcic);
        printf("\n");
    }

#if defined (ANSI)
    else if (DBC_Cmd(dbc, "cra", "SendCRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cra");
        result = TestSendCRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "crm", "SendCRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("crm");
        result = TestSendCRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvr", "SendCVR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvr");
        result = TestSendCVRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CVR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvt", "SendCVT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvt");
        result = TestSendCVTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CVT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "exm", "SendEXM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("exm");
        result = TestSendEXMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send EXM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "start", "Start ANSI MTP3", "", ""))
    {
        printf("*********** Starting ANSI MTP3 **************\n");

        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_RESTART,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        printf("*********** Returned from the MGMT Restart *************\n");
    }
#endif /* ANSI */

#if defined (CCITT)
    else if (DBC_Cmd(dbc, "con", "SendCON", "<cic>", ""))
    {
        VALIDATE_CMDLINE("con");
        result = TestSendCONRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CON return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "faa", "SendFAA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("faa");
        result = TestSendFAARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FAC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "far", "SendFAR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("far");
        result = TestSendFARRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "frj", "SendFRJ", "<cic>", ""))
    {
        VALIDATE_CMDLINE("frj");
        result = TestSendFRJRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FRJ return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "idr", "SendIDR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("idr");
        result = TestSendIDRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IDR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "irs", "SendIRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("irs");
        result = TestSendIRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "nrm", "SendNRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("nrm");
        result = TestSendNRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send NRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "olm", "SendOLM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("olm");
        result = TestSendOLMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send OLM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sam", "SendSAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sam");
        result = TestSendSAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sgm", "SendSGM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sgm");
        result = TestSendSGMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SGM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upa", "SendUPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upa");
        result = TestSendUPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upt", "SendUPT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upt");
        result = TestSendUPTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UPT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "usr", "SendUSR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("usr");
        result = TestSendUSRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send USR return result = %d\n", result);
    }
#endif /* CCITT */

#if defined (CCITT) && defined (ITU_ISUP_97)
    else if (DBC_Cmd(dbc, "lop", "SendLOP", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lop");
        result = TestSendLOPRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LOP return result = %d\n", result);
    }
#endif /* ITU_ISUP_97 */

#if defined (ANSI) && defined (ANSI_ISUP_95)
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAC return result = %d\n", result);
    }
#endif /* ANSI_ISUP_95 */
    printf("------------------------------------------------------\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function Gets OPC, DPC ans SIO values from the DMP file
 *
 *  Input Parameters:
 *      info - Pointer to the OpcDpcInfo struct
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int GetOpcDpcInfo(OpcDpcInfo* info)
{
    static char dmpFile[256];

    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    RESFILE_Manager* res = NULL;

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    ITS_C_ASSERT( info != NULL );

    res = RESFILE_CreateResourceManager(dmpFile);

    ITS_C_ASSERT( res != NULL );

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    while (RESFILE_GetKeyName(res, section, key, ITS_PATH_MAX)
                                                   == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section, val, ITS_PATH_MAX)
                                                   == ITS_SUCCESS)
    {
        if(strcmp(DEST_POINT_CODE_STRING, key) == 0)
        {
            info->dpc = RESFILE_ParseNum(val);
        }
        else if (strcmp(LOCAL_POINT_CODE_STRING, key) == 0)
        {
            info->opc = RESFILE_ParseNum(val);
        }
        else if (strcmp(SIO_STRING, key) == 0)
        {
            info->sio = RESFILE_ParseNum(val);
        }

    }
    RESFILE_Unlock(res);

    printf("\nDPC = %d |", info->dpc);
    printf("OPC = %d |", info->opc);
    printf("SIO = %d\n", info->sio);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is Call Back function, used for sending the ISUP Local
 *      Congestion Indications to the App.
 *
 *  Input Parameters:
 *      object   - Call Back function argument
 *      userData - Call Back function argument
 *      callData - Per invocation callback function argument
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ISUP_HandleLocalCongestion (ITS_POINTER object, ITS_POINTER userData, 
                            ITS_POINTER callData)
{
     ISUP_CONGESTION_ENTRY *cong = (ISUP_CONGESTION_ENTRY *)callData;

     printf("------------------------------------------------------\n");
     switch (cong->congId)
     {
     case  ITS_ISUP_LOC_CONGLEVEL1_IND:
           printf("Application: ISUP Local Congestion Level 1 Detected\n");
           printf("====  Cut down Traffic by 1/3 ====\n");
	   break;

     case  ITS_ISUP_LOC_CONGLEVEL2_IND:
           printf("Application: ISUP Local Congestion Level 2 Detected\n");
           printf("====  Cut down Traffic by 2/3 ====\n");
           break;

     case  ITS_ISUP_LOC_CONGLEVEL3_IND:
           printf("Application: ISUP Local Congestion Level 3 Detected\n");
           printf("====  Cut down complete Traffic ====\n");
	   break;

     case  ITS_ISUP_LOC_NOCONG_IND:
           printf("Application: ISUP Local Congestion ceased\n");
           printf("====  Resume Traffic Procedures ====\n");
           break;
     }
     printf("------------------------------------------------------\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is Call Back function, used for sending the MTP3
 *      Indications to the App.
 *
 *  Input Parameters:
 *      object   - Call Back function argument
 *      userData - Call Back function argument
 *      callData - Per invocation callback function argument
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ISUP_HandleMTP3Mgmt (ITS_POINTER object, ITS_POINTER userData, 
                     ITS_POINTER callData)
{
     ITS_EVENT *ev = (ITS_EVENT *)callData;

     printf("------------------------------------------------------\n");

     switch (ev->data[0])
     {
     case MTP3_MSG_PAUSE:
           printf ("Application: Rcvd MTP3 PAUSE from OPC|DPC|NI %06x\n",
#if defined(ANSI)
           MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)&ev->data[1])->affected));
#elif defined(CCITT)
           MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_CCITT *)&ev->data[1])->affected));
#endif
           printf("====  Stop Traffic Procedures ====\n");
           break;

     case MTP3_MSG_RESUME:
           printf ("Application: Rcvd MTP3 RESUME from OPC|DPC|NI %06x\n",
#if defined(ANSI)
           MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)&ev->data[1])->affected));
#elif defined(CCITT)
           MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_CCITT *)&ev->data[1])->affected));
#endif
           printf("====  Resume Traffic Procedures ====\n");
           break;

     case MTP3_MSG_STATUS:
           printf ("Application: Rcvd MTP3 STATUS from opc|dpc|ni %06x cause %d cong %d\n",
#if defined(ANSI)
           MTP3_PC_GET_VALUE(((MTP3_STATUS_ANSI *)&ev->data[1])->affected),
           ((MTP3_STATUS_ANSI *)&ev->data[1])->cause,
           ((MTP3_STATUS_ANSI *)&ev->data[1])->congLevel);
#elif defined(CCITT)
           MTP3_PC_GET_VALUE(((MTP3_STATUS_CCITT *)&ev->data[1])->affected),
           ((MTP3_STATUS_CCITT *)&ev->data[1])->cause,
           ((MTP3_STATUS_CCITT *)&ev->data[1])->congLevel);
#endif
           printf("====  MTP3 Status Indication Received  ====\n");

     default:
           printf ("Application: Received MTP3 USER DATA \n");
           break;
     }
     printf("------------------------------------------------------\n");
}
