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
 * $Id: load.c,v 1.1.1.1 2007-10-08 11:12:23 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:24:59  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:18  cvsadmin
 * BSC project
 *
 * Revision 9.2  2005/04/05 11:58:35  sjaddu
 * Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * Code changes for ISSUE ID 289.
 *
 * Revision 9.1  2005/03/23 12:55:15  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.3  2005/03/21 13:54:27  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1.4.1.6.1  2004/09/13 06:07:40  ssingh
 * Changes done to comply with ISUP Stack changes.
 *
 * Revision 7.1.4.1  2003/05/09 04:57:58  ssingh
 * Handle incomming calls as well.
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.5  2002/08/13 20:56:10  ssingh
 * Print statement got removed from excecution.
 *
 * Revision 1.4  2002/08/08 19:49:51  hbalimid
 * updated for ANSI Load test.
 *
 * Revision 1.3  2002/08/07 21:51:49  hbalimid
 * updated to work with new infrastructure.
 *
 * Revision 1.2  2002/05/20 15:58:50  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.4  2002/05/09 18:40:21  labuser
 * Merge from ISUP_APR_19_2002 to PR6.
 *
 * Revision 1.1.2.3.2.1  2002/04/24 23:35:05  labuser
 * added new commands
 *
 * Revision 1.1.2.3  2002/04/15 00:54:50  hbalimid
 * ISUP Load test - Base Version Done.
 *
 * Revision 1.1.2.2  2002/04/13 02:09:07  hbalimid
 * added perror for !fopen()
 *
 * Revision 1.1.2.1  2002/04/13 01:39:18  hbalimid
 * New Updates
 *
 * Revision 1.1.2.5  2002/04/07 22:42:28  hbalimid
 * New code for ISUP load test;
 * yetto be made coding standards'c compliant
 *
 * Revision 1.1.2.4  2002/04/07 22:35:49  hbalimid
 * updated with $Log and $Id
 *
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
#include <mtp3_intern.h>

/*
 * Transport Handle For the ISUP send APIs
 */
#if defined(CCITT)
#define HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define HANDLE ISS7_ANSI_Stack
#endif

typedef unsigned char uchar;

extern int errno;

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
    uchar sio;
    ushort numCics;
    ushort startCic;
} ConfigInfo;

CicInfo* cicInfo;
CicInfo* currPtr;
ConfigInfo configInfo;

ITS_MUTEX configLock;
ITS_SEMAPHORE loadSem;
ITS_SEMAPHORE preFuncSem;

TPOOL_THREAD* callThread;
TPOOL_THREAD* timerThread;
ITS_USHORT timerInstance;

FILE* logFp = NULL;

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
ITS_BOOLEAN isFirstEntry = ITS_FALSE;

/*
 * Function Forward Declarations
 */
int SelectApplication(ITS_HDR *hdr,ITS_EVENT *event);
int Node1SelectApplication(ITS_HDR *hdr,ITS_EVENT *event);
int Node2SelectApplication(ITS_HDR *hdr,ITS_EVENT *event);
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

void ExtractCicGrps(ISUP_CFG_CKGP_INFO *ckgp,int noEnt);
void UpdateCicPool(ushort startCic, ushort numberCics);
void AddtoCicPool(ushort startCic, ushort numberCics);


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

    DBC_SetDoCommand(ExecuteCommand);

    printf("Load: Entered PreFunc\n");
    memset( dmpFile, 0 , BUF_SIZE );
    memset( logFile, 0 , BUF_SIZE );
    memset( buf, 0 , BUF_SIZE );

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("App Dmp Name = %s\n", dmpFile);

    sleep (2);
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

        if( feof(load) ) break;
    }
    fclose(load);
   

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

    sleep(2);

#if 0
    /* wait on signal from IAM Dispatch */
    SEMA_WaitSemaphore(&preFuncSem);
    /* The above is commented because of some reason */

    printf("Deleting callThread\n");
    WORKER_DeleteWorker( (WORKER_Control *) callThread );
    printf("Deleting TimerThread\n");
    WORKER_DeleteWorker( (WORKER_Control *) timerThread );
    printf("Load: Leaving PreFunc...\n");
    printf("*** LOAD TEST COMPLETED! GET LEAKS NOW ***\n");
    sleep(5); /* for the workers to finsih their jobs */

    /* Delete the mutexes */
    printf("Deleting Muexs!\n");
    MUTEX_DeleteMutex(&configLock);

    /* Delete the semaphores */
    printf("Deleting Semahores!\n");
    SEMA_DeleteSemaphore(&loadSem);
    SEMA_DeleteSemaphore(&preFuncSem);


    raise(SIGINT);
#endif

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

    assert(dmpFile != NULL);

    MUTEX_AcquireMutex(&configLock);


    cicInfo = (CicInfo *) malloc (sizeof(CicInfo) * 1);
    assert ( cicInfo != NULL);

    cicInfo->cic = -1;
    cicInfo->next = NULL;
    ptr = cicInfo;

    fp  = fopen(dmpFile, "r");
    assert(fp != NULL);

    while( !feof(fp) )
    {
        fgets(buf, BUF_SIZE, fp);

        buf[strlen(buf)-1] = 0;

        if( strcmp(section,buf) == 0 )
        {
            printf("Entered ISUP : %s\n", buf);
            break;
        }
    }
    while( !feof(fp) )
    {
        fgets(buf, BUF_SIZE, fp);
        buf[strlen(buf)-1] = 0;

        tmp = strchr((const char*)buf,'=');
        if( !tmp ) continue;
        *tmp = 0;
        tmp++;

        if((strcmp("DPC",buf) == 0))
        {
            if( destDpc == 1 ) break;
            configInfo.dpc = RESFILE_ParseNum(tmp);
            printf("DPC = %d\n", configInfo.dpc);
            destDpc = 1;
        }
        else if((strcmp("LPC",buf) == 0))
        {
            configInfo.lpc = RESFILE_ParseNum(tmp);
            printf("LPC = %d\n", configInfo.lpc);
        }
        else if((strcmp("SIO",buf) == 0))
        {
            configInfo.sio = (ITS_OCTET)RESFILE_ParseNum(tmp);
            printf("SIO = %d\n", configInfo.sio);
        }
        else if((strcmp("startCic",buf) == 0))
        {
            if( startCic < 0 )
            {
                startCic = RESFILE_ParseNum(tmp);
                configInfo.startCic = startCic;
            }
            else
            {
               startCic = RESFILE_ParseNum(tmp);
            }
        }
        else if((strcmp("numberCics",buf) == 0))
        {
            numCics = RESFILE_ParseNum(tmp); 

            if( cicInfo->cic == -1 )
            {
                cicInfo->cic = startCic;
                j = 1;
            }
            else
            {
                j = 0;
            }

            for( i = j ; i < numCics; i++ )
            {
                if( ptr->next == NULL )
                {
                    ptr->next = (CicInfo *) malloc (sizeof(CicInfo) * 1);
                    assert( ptr->next != NULL );
                    ptr->next->next = NULL;
                }
                ptr->next->cic = startCic + i;
                ptr = ptr->next;
            }
        }

        if( feof(fp) ) break;
    }

    configInfo.numCics = 0;
    ptr = cicInfo;
    while( ptr )
    {
        printf("CIC: *%d*\t", ptr->cic);
        fprintf(logFp,"Cic: %d\n", ptr->cic);
        fflush(logFp);
        ptr->state = CIC_LR_BLOCKED;
        ptr = ptr->next;
        configInfo.numCics++;
    }
    printf("InitConfig(): Num Cics = %d\n", configInfo.numCics);
 
    fprintf(logFp,"\nNumber of Configured Cics = %d\n", configInfo.numCics);
    fflush(logFp);
    sleep(2);

    MUTEX_ReleaseMutex(&configLock);

    fclose(fp);

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    ExtractCicGrps
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
 *      This function extract the Cic groups for the given dest
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    03-31-2005  ISSUEID::289            Modified for adding cics  
 *                                                 dynamically 
 ****************************************************************************/
void ExtractCicGrps(ISUP_CFG_CKGP_INFO *ckgp, int noEnt)
{
   ITS_UINT count;
   int cicsInckg;

   #if defined(CCITT)
     cicsInckg = 32;
   #else
     cicsInckg = ISUP_ANSI_MAX_CICS_IN_GP;
   #endif

   int j =0;
   ITS_USHORT cic = 0, startcic = 0;
   ITS_OCTET cicrule = ISUP_CKGP_CTRL_DEF;
   ITS_BOOLEAN cics_present = ITS_FALSE;
   ITS_BOOLEAN startcicFound = ITS_FALSE;


   if (noEnt == 0)
   {
      return;
   }

   for (count = 0; count < (ITS_UINT)noEnt; ++count)
   {
      if (ckgp[count].usable_cics[0] == 0)
      {
          continue;
      }
      startcicFound = ITS_FALSE;

      for (j = 0; j < cicsInckg; j++)
      {
          if ((ckgp[count].usable_cics[0] & (0x00000001 << j)) != 0)
          {
              cics_present = ITS_TRUE;
              #if defined(CCITT)
                 cic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);
              #else
                 cic = (ckgp[count].ckgp_id * cicsInckg) + j;
              #endif

              if (!startcicFound)
              {
                  #if defined(CCITT)
                   startcic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);
                  #else
                   startcic = (ckgp[count].ckgp_id * cicsInckg) + j;
                  #endif

                  startcicFound = ITS_TRUE;
              }
              else if (cicrule != ckgp[count].contl[j])
              {
                 /* Update the Cic in pool */
                 UpdateCicPool(startcic, (((cic - 1) + 1)  - startcic));

                 #if defined(CCITT)
                   startcic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);
                 #else
                   startcic = (ckgp[count].ckgp_id * cicsInckg) + j;
                 #endif
              }
          }
          else
          {
              if (startcicFound)
              {
                 /* Update the Cic in pool */
                 UpdateCicPool(startcic, ((cic + 1)  - startcic));
              }
              startcicFound = ITS_FALSE;
          }

          cicrule = ckgp[count].contl[j];
      }

      if (startcicFound)
      {
          /* Update the Cic in pool */
          UpdateCicPool(startcic, ((cic + 1)  - startcic));
      }
   }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    AddtoCicPool
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
 *      This function update Cic pool
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    03-31-2005  ISSUEID::289            Modified for adding cics  
 *                                                 dynamically 
 ****************************************************************************/
void AddtoCicPool(ushort startCic, ushort numCics)
{
    CicInfo* ptr = NULL;

    MUTEX_AcquireMutex(&configLock);

    /* Free the config Info */
    if( cicInfo )
    {
        ptr = cicInfo;
        /* traverse the list and free all cics */
        cicInfo = cicInfo->next;
        free( ptr );
    }

    /*Initial state */
    cicInfo = (CicInfo *) malloc (sizeof(CicInfo) * 1);
    assert ( cicInfo != NULL);

    cicInfo->cic = -1;
    cicInfo->next = NULL;
    ptr = NULL;

    /* add the cics to the pool*/
    short i = 0, j = 0;

    ptr = cicInfo;
    if( cicInfo->cic == -1 )
    {
        cicInfo->cic = startCic;
        j = 1;
    }
    else
    {
        j = 0;
    }

    for( i = j ; i < numCics; i++ )
    {
        if( ptr->next == NULL )
        {
            ptr->next = (CicInfo *) malloc (sizeof(CicInfo) * 1);
            assert( ptr->next != NULL );
            ptr->next->next = NULL;
        }
        ptr->next->cic = startCic + i;
        ptr->next->state = CIC_LR_BLOCKED;
        ptr = ptr->next;
        currPtr = ptr;
    }

    MUTEX_ReleaseMutex(&configLock);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    UpdateCicPool
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
 *      This function update Cic pool
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    03-31-2005  ISSUEID::289            Modified for adding cics  
 *                                                 dynamically 
 ****************************************************************************/
void UpdateCicPool(ushort startCic, ushort numCics)
{

  /*check whether cic pool has to be deleted */
  if (isFirstEntry)
  {
      /* First time */
      AddtoCicPool(startCic, numCics);
      isFirstEntry = ITS_FALSE;
      return;
  }

  /* add the cics to the pool*/
  CicInfo* ptr = NULL;
  short i = 0;

  MUTEX_AcquireMutex(&configLock);

  ptr = currPtr;

  for( i = 0 ; i < numCics; i++ )
  {
      if( ptr->next == NULL )
      {
          ptr->next = (CicInfo *) malloc (sizeof(CicInfo) * 1);
          assert( ptr->next != NULL );
          ptr->next->next = NULL;
      }

      ptr->next->cic = startCic + i;
      ptr->next->state = CIC_LR_BLOCKED;
      ptr = ptr->next;
      currPtr = ptr;
  }

  MUTEX_ReleaseMutex(&configLock);
}



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     StartUnblocking
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
 ****************************************************************************/
void
StartUnblocking(void)
{
    CicInfo* ptr= NULL;
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_HDR hdr;
    ITS_INT res = 0;

    ITS_USHORT lpc = 0;
    ITS_USHORT dpc = 0;
    ITS_OCTET sio = 0;

    assert( cicInfo != NULL );

    ptr = cicInfo;
    assert ( ptr != NULL );

    MUTEX_AcquireMutex(&configLock);

    lpc = configInfo.lpc;
    dpc = configInfo.dpc;
    sio = configInfo.sio;

    printf("LPC = 0x%x\n", lpc);
    printf("DPC = 0x%x\n", dpc);
    printf("SIO = 0x%x\n", sio);

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    
    printf("Start Unblocking!\n");


#if defined(P)
purify_clear_leaks();
#endif
    do
    {
        usleep(100000);
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

       #if defined(ANSI)
        ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                            sio, lpc, dpc, (ptr->cic & 0x001F) );
       #else
        ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                            sio, lpc, dpc, (ptr->cic & 0x000F) );
       #endif
       ieIndex++;
       /* printf("ieIndex = %d\n", ieIndex); */

       ieCount = ieIndex;

       res  = ISUP_SendUBLRequest(HANDLE, &hdr, ies, ieCount);
       if(res != ITS_SUCCESS)
       {
           printf("Error in sending UBL for cic %d \n", ptr->cic);
           ublSentFailCounter++;
       }
       else
       {
           ptr->state = CIC_WAIT_FOR_R_UBL;
           ublSentSuccessCounter++;
       }

       ptr = ptr->next;

    } while( ptr );



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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
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

       #if defined(ANSI)
        ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                            sio, lpc, dpc, (ptr->cic & 0x001F) );
       #else
        ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                            sio, lpc, dpc, (ptr->cic & 0x000F) );
       #endif
       ieIndex++;
       /* printf("ieIndex = %d\n", ieIndex); */

       ieCount = ieIndex;

       res  = ISUP_SendRSCRequest(HANDLE, &hdr, ies, ieCount);
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

    ITS_INT timerDuration = 1; /* one second */

    WORKER_Control* timer = (WORKER_Control*)thr;
    timerInstance = timer->worker.instance;
    printf("Instance Number of Timer is ... %d\n",timerInstance);

    memset( &event, 0, sizeof(ITS_EVENT));

    if( SEMA_WaitSemaphore(&loadSem) != ITS_SUCCESS )
    {
        printf("Exiting Due to Failure in SEMA_WaitSemaphore() in Timer Thread!\n");
        fprintf (logFp,"Exiting Due to Failure in SEMA_WaitSemaphore() in Timer Thread!");
        return;
    }

    for(;;)
    {
        sleep(timerDuration); /* sleep for a second */
        if( SEMA_PostSemaphore(&loadSem) != ITS_SUCCESS )
        {
            printf("TimerDispatchFunction(): SEMA_PostSemaphore failed\n"); 
            return;
        }

#if 0
    /* I doub't that Timer is not functioning properly
     * It seems it is not popping up and putting events
     * we are getting blocked on GetNextEvent
     * so lets use sleep
     */
        if( (ret = TIMERS_StartTimer(timerInstance, timerDuration, NULL,0)) == 0 )
        {
            printf("TimerDispatchFunction(): Failed to start the timer! res = %d\n\n", ret);
            return ;
        }

        ret = WORKER_GetNextEvent(timer, &event);
        printf("Got timer event: src = %d\n", event.src);
        if (ret != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }
        /*DumpITSEvent(&event);*/

        if ( event.src == ITS_TIMER_SRC )
        {
           /* printf("Timer Thread: Received Timer Event\n"); */
            if( SEMA_PostSemaphore(&loadSem) != ITS_SUCCESS )
            {
                printf("TimerDispatchFunction(): SEMA_PostSemaphore failed\n"); 
                return;
            }
        }
        else
        {
            printf("Junk Event for me!!\n");
        }
#endif
    }

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      SelectApplication
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
ITS_USHORT inst = 0;
int
SelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;
    static int first= 0;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;

if (!first)
{
    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
        /* ISUP is getting terminated because of this return value!! */
    }

    /* printf("LOAD: SelectApp: Dispatching worker thread with instance %d\n",
            ((WORKER_Control*)thread)->worker.instance ); */

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_TRANSPORT(thread));
    first = 1;
    inst = ((WORKER_Control*)thread)->worker.instance;
    return ( ((WORKER_Control*)thread)->worker.instance );
}
    return inst;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Node1SelectApplication
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
Node1SelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;
    static int first= 0;
    ITS_USHORT cic= 0;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;

if (!first)
{
    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
        /* ISUP is getting terminated because of this return value!! */
    }

    /* printf("LOAD: SelectApp: Dispatching worker thread with instance %d\n",
            ((WORKER_Control*)thread)->worker.instance ); */

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_TRANSPORT(thread));
    first = 1;
    inst = ((WORKER_Control*)thread)->worker.instance;
    return ( ((WORKER_Control*)thread)->worker.instance );
}

  if (event->src == ITS_ISUP_SRC)
  {
      cic = ((event->data[3]) & 0x00FF);
      cic |= ((event->data[4] << 8) & 0xFF00);
  }
  else
  {
      #if defined(ANSI)
        cic = ((event->data[9]) & 0x00FF);
        cic |= ((event->data[10] << 8) & 0xFF00);
      #else
        cic = ((event->data[6]) & 0x00FF);
        cic |= ((event->data[7] << 8) & 0xFF00);
      #endif
  }

  if (cic % 2 == 0)
  {
     return inst;
  }
  else
     return (ITS_INVALID_SRC);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Node2SelectApplication
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
Node2SelectApplication(ITS_HDR *hdr,ITS_EVENT *event)
{
    ITS_INT ret = 0;
    TPOOL_THREAD* thread;
    static int first1= 0;
    ITS_USHORT cic = 0;

    ITS_HDR routeHeader;

    routeHeader.type = ITS_ISUP;
    routeHeader.context.cic = hdr->context.cic;

if (!first1)
{
    if( (ret = TPOOL_GetFirstAvailThread(workerPool, &thread)) != ITS_SUCCESS )
    {
        printf("***No more worker threads!\n");
        return ret;
        /* ISUP is getting terminated because of this return value!! */
    }

    /* printf("LOAD: SelectApp: Dispatching worker thread with instance %d\n",
            ((WORKER_Control*)thread)->worker.instance ); */

    ret = TPOOL_DispatchOnThread(thread,WorkerThreadDispatchFunction,
                                       WORKER_TRANSPORT(thread));
    first1 = 1;
    inst = ((WORKER_Control*)thread)->worker.instance;
    return ( ((WORKER_Control*)thread)->worker.instance );
}

    if (event->src == ITS_ISUP_SRC)
    {
        cic = ((event->data[3]) & 0x00FF);
        cic |= ((event->data[4] << 8) & 0xFF00);
    }
    else
    {
        #if defined(ANSI)
          cic = ((event->data[9]) & 0x00FF);
          cic |= ((event->data[10] << 8) & 0xFF00);
        #else
          cic = ((event->data[6]) & 0x00FF);
          cic |= ((event->data[7] << 8) & 0xFF00);
        #endif
    }

    if (cic % 2 != 0)
    {
       return inst;
    }
    else
       return (ITS_INVALID_SRC);
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
    /* printf("Instance Number of Worker is ... %d\n",workerInstance); */

while(1)
{
    memset( &event, 0, sizeof(ITS_EVENT));

    ret = WORKER_GetNextEvent(worker, &event);
    if (ret != ITS_SUCCESS)
    {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
    }
    /* DumpITSEvent(&event); */

    if ( event.src == ITS_ISUP_SRC )
    {
        /*printf("Worker Thread: ISUP msg *%s* receive success; Msg is %d\n",
                ISUP_GetMsgName(event.data[0]), event.data[0] );*/
    }

    switch( event.data[0] )
    {
        case ISUP_MSG_UBL:
            ublReceivedCounter++;
            HandleUBL(HANDLE, &event);
            break;

        case ISUP_MSG_UBA:
            ubaReceivedCounter++;
            HandleUBA(HANDLE, &event);
            /* currently these globals are unprotected! */
            if( ubaReceivedCounter == ublSentSuccessCounter )
            {
                printf("Worker Thread:: %d :: UBA Received = %d\n",
                                        workerInstance, ubaReceivedCounter);
            }
            if( ublReceivedCounter == ubaSentSuccessCounter )
            {
                printf("Worker Thread:: %d :: UBL Received = %d\n",
                                        workerInstance, ublReceivedCounter);
            }
            break;

        case ISUP_MSG_IAM:
            iamReceivedCounter++;
            HandleIAM(HANDLE, &event);
            break;

        case ISUP_MSG_ACM:
            acmReceivedCounter++;
            HandleACM(HANDLE, &event);
            break;

        case ISUP_MSG_ANM:
            anmReceivedCounter++;
            HandleANM(HANDLE, &event);
            break;

        case ISUP_MSG_REL:
            relReceivedCounter++;
            HandleREL(HANDLE, &event);
            break;

        case ISUP_MSG_RLC:
            rlcReceivedCounter++;
            HandleRLC(HANDLE, &event);
            break;

        default:
            invalidMsgCounter++;
            printf("Invalid Message:\n");
            HandleUnexpectedMessage(HANDLE, &event);
            break;
    }

    ITS_EVENT_TERM(&event);
}

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      ExtractCic
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
int
ExtractCic( ITS_HDR* hdr, ITS_EVENT* event)
{
    ITS_USHORT vcic = 0;
    ITS_INT ret = 0;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;

    /* VFRAME: FIXME */
    /* Idea is to get cic in hdr */
    /* also we should be using the ie[0] that contains the routing label */
    /* cic is coming wrong here and that too it is a vcic */
    /* use event->data[1] and event->data[2] for vcic */
    /* use some function to get cic from vcic */

    /* FIXME */


    vcic = ((event->data[1]) & 0x00FF);
    vcic |= ((event->data[2] << 8) & 0xFF00);
    /* printf("VCIC = 0x%04x\n", vcic); */

    cic_rec = ISUP_FindVcic( vcic );
    if (cic_rec == NULL)
    {
        printf("couldn't Find cic_rec!\n");
        return (ITS_EINVALIDERR);
    }
    /* Get OPC_DPC configuration for access to Variant info. */
    ret = ISUP_FindOpcDpc(ISUP_PCIC_TO_OPC_DPC(cic_rec->pcic),
                                  &config_info, ITS_FALSE);
    if (ret != ITS_SUCCESS)
    {
        printf("ConfigInfo is NULL\n");
        ISUP_ReleaseCic( cic_rec, ITS_FALSE );
        return (ITS_EINVALIDERR);
    }

    hdr->type = ITS_ISUP;
    hdr->context.cic = ISUP_PCIC_TO_CIC( cic_rec->pcic );

    /* printf("***Finally Incoming CIC = %d\n", hdr->context.cic); */

    ISUP_FreeOpcDpc(&config_info);
    ISUP_ReleaseCic( cic_rec, ITS_FALSE );

    return (ITS_SUCCESS);
}

/* All the Message Handling Routines are Here */
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleUBL
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
 ****************************************************************************/
void
HandleUBL(ITS_HANDLE handle, ITS_EVENT* event)
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

    res = ISUP_ReceiveUBLIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleUBL:ISUP_ReceiveUBLIndication Failed!\n");
        return;
    }

    /* printf("cic for received UBL = %d\n", hdr.context.cic);
    printf("ieCount for received UBL = %d\n", ieCount); */


    if( ExtractCic(&hdr, event) != ITS_SUCCESS )
    {
        printf("HandleUBL:Error in extracting cic!\n");
        return;
    }

    MUTEX_AcquireMutex(&configLock);

    ptr = cicInfo;

    while( ptr )
    {
        if( ptr->cic != hdr.context.cic )
        {
            ptr = ptr->next;
            continue;
        }
        if( ptr->state != CIC_WAIT_FOR_R_UBL )
        {
            printf("*HandleUBL:Unexpected UBL here cic = %d"
                    " state = *%d* WaitforUBL = *%d*\n",
                     ptr->cic, ptr->state, CIC_WAIT_FOR_R_UBL);
            unexpUBL++;
            MUTEX_ReleaseMutex(&configLock);

            return;
        }
        else
        {
            /* send a message on this cic */ 
            /*printf("HandleUBL:Found the CIC. So send message cic = %d\n", ptr->cic);*/
            break;
        }
    }
    if( ptr == NULL)
    {
        printf("Couldn't find the cic!\n");
    }

    MUTEX_ReleaseMutex(&configLock);
    

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    #if defined(ANSI)
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr.context.cic & 0x001F) );
    #else
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr.context.cic & 0x000F) );
    #endif

    ieCount = 1;


    res  = ISUP_SendUBARequest(HANDLE, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
       printf("Error in sending UBA for cic %d \n", hdr.context.cic);
       ubaSentFailCounter++;
    }
    else
    {
       /*printf("--->Sent UBA successfully for cic %d!!\n", hdr.context.cic);*/
       ubaSentSuccessCounter++;
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
        break;
    }
    if( ptr == NULL)
    {
        printf("Couldn't find the cic!\n");
    }
    else
    {
        /* printf("New State for cic %d = %d\n", ptr->cic, ptr->state); */
    }
    
    MUTEX_ReleaseMutex(&configLock);


    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      HandleUBA
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
HandleUBA(ITS_HANDLE handle, ITS_EVENT* event)
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

    res = ISUP_ReceiveUBAIndication(handle, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleUBA:ISUP_ReceiveUBAIndication Failed!\n");
        return;
    }

    /*printf("cic for received UBA = %d\n", hdr.context.cic);
    printf("ieCount for received UBA = %d\n", ieCount);*/

    if( ExtractCic(&hdr, event) != ITS_SUCCESS )
    {
        printf("HandleUBA:Error in extracting cic!\n");
        return;
    }

    /* traverse to the cic in the list and set state to WAIT_FOR_UBL */

    MUTEX_AcquireMutex(&configLock);

    ptr = cicInfo;
    while( ptr )
    {
        if( ptr->cic != hdr.context.cic )
        {
            ptr = ptr->next;
            continue;
        }
        ptr->state = CIC_WAIT_FOR_R_UBL;
        break;
    }
    if( ptr == NULL)
    {
        printf("HandleUBA:Couldn't find the cic!\n");
    }
    else
    {
        /* printf("HandleUBA: New State for cic %d = %d\n", ptr->cic, ptr->state); */
    }
    
    MUTEX_ReleaseMutex(&configLock);


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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
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

    #if defined(ANSI)
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x001F) );
    #else
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x000F) );
    #endif

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

    res  = ISUP_SendACMRequest(HANDLE, hdr, ies, ieCount);
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
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

    #if defined(ANSI)
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x001F) );
    #else
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x000F) );
    #endif

    ieCount = 1;

    res  = ISUP_SendANMRequest(HANDLE, hdr, ies, ieCount);
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
 *      SendREL
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
 ****************************************************************************/
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

    #if defined(ANSI)
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x001F) );
    #else
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr->context.cic & 0x000F) );
    #endif

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

    res  = ISUP_SendRELRequest(HANDLE, hdr, ies, ieCount);
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
        printf("ISUP_ReceiveRELIndication Failed!\n");
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
        printf("ISUP_ReceiveRELIndication Failed!\n");
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
        printf("ISUP_ReceiveRELIndication Failed!\n");
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
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
        return;
    }

/*
    printf("cic for received REL = %d\n", hdr.context.cic);
    printf("ieCount for received REL = %d\n", ieCount);

    if( ExtractCic(&hdr, event) != ITS_SUCCESS )
    {
        printf("HandleREL:Error in extracting cic!\n");
        return;
    }

    printf("Finally Incoming CIC = %d\n", hdr.context.cic);
*/

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    #if defined(ANSI)
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr.context.cic & 0x001F) );
    #else
     ISUP_SET_MTP3_HEADER( ies[0].param_data.routingLabel,
                configInfo.sio, configInfo.lpc,
                configInfo.dpc, (hdr.context.cic & 0x000F) );
    #endif

    ieCount = 1;


    res  = ISUP_SendRLCRequest(HANDLE, &hdr, ies, ieCount);
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
        return;
    }

    printf("cic for received RLC = %d\n", hdr.context.cic);

/*
    if( ExtractCic(&hdr, event) != ITS_SUCCESS )
    {
        printf("HandleRLC:Error in extracting cic!\n");
        return;
    }
*/

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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Masking cic with 0x1F (ANSI)
 *                     ID::D0020                   and 0x0F(ITU) for SLS  
 ****************************************************************************/
void
StartIAMDispatchFunction(TPOOL_THREAD* thr, void* arg)
{
    time_t t_loc1;
    time_t t_loc2;
    CicInfo* ptr = NULL;

    ushort cic = 0;
    ushort lpc = 0;
    ushort dpc = 0;
    uchar sio = 0;
    uint duration = 0;
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

    lpc = configInfo.lpc;
    dpc = configInfo.dpc;
    sio = configInfo.sio;

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

    for( duration = 0; duration < loadTestDuration; duration++)
    {

        /* TIMERS_StartTimer(timerInstance, timerDuration, NULL,0); */

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
                if( ptr->state != CIC_IDLE )
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

                if( select(0,NULL,NULL,NULL,&sel) < 0 )
                {
                    fprintf (logFp,"StartIAM(): Try Again: Select() Error; %d\n", errno);
                    fflush(logFp);
                    printf("Select() Error!\n");
                }
                continue;
            }

            MUTEX_ReleaseMutex(&configLock);


            /* Start out an IAM on this cic */

            hdr.type = ITS_ISUP;
            hdr.context.cic = cic;

            ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
            ies[ieIndex].param_length = sizeof(MTP3_HEADER);

            #if defined(ANSI)
             ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                                            sio, lpc, dpc, (cic & 0x001F) );
            #else
             ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                                            sio, lpc, dpc, (cic & 0x000F) );
            #endif

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
            ieCount = ieIndex;

            /* printf("Number fo IEs in IAM = %d\n", ieCount); */

            res  = ISUP_SendIAMRequest(HANDLE, &hdr, ies, ieCount);
            if(res != ITS_SUCCESS)
            {
                    printf("Error in sending IAM for cic %d \n", hdr.context.cic);
                    iamSentFailCounter++;
                    usleep(interCallGap);
                    continue;
            }
            else
            {
                    iamSentSuccessCounter++;
                    /* printf("Sentout IAM successfully on cic %d\n", hdr.context.cic); */
            }

            if(ftime(&en) < 0)
            perror("ftime()"), exit(1);
            
            /*
            interCallGap = ( ((en.time - st.time) * 1000) + (en.millitm - st.millitm) );
            interCallGap *= 1000;
            usleep(interCallGap);
            */

            /* Try using select for a high precison sleep */

            interCallGap = ( ((en.time - st.time) * 1000) + (en.millitm - st.millitm) );
            interCallGap *= 1000;

            if( interCallGap > 1000000 )
            {
                printf("InterCall Gap is greater than a second!\n");
                fprintf (logFp,"InterCallGap exceeds 1 second; intercallgap = %u microseconds\n", interCallGap);
                fflush(logFp);
                continue;
            }

            sel.tv_sec = 0;
            sel.tv_usec = interCallGap;

            if( select(0,NULL,NULL,NULL,&sel) < 0 )
            {
/*
                fprintf (logFp,"StartIAM(): Select() Error; %d\n", errno);
                fflush(logFp);
                printf("Select() Error!\n");
*/
                continue;
            }
        }

        if( SEMA_WaitSemaphore(&loadSem) != ITS_SUCCESS )
        {
            printf("Exiting Due to Failure in SEMA_WaitSemaphore() in IAM Thread!\n");
            fprintf (logFp,"Exiting Due to Failure in SEMA_WaitSemaphore() in IAM Thread!");
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
    LoadPostFunc();

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

    exit(0);
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
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    03-31-2005  ISSUEID::289            Modified for adding cics  
 *                                                 dynamically 
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

    /* Alignment of Links */

#if defined (CCITT)
    if (DBC_Cmd(dbc, "start", "Start ITU MTP3", "", ""))
    {
        printf("*********** Starting ITU MTP3 **************\n");
        MGMT_Main_CCITT(MTP3_USER,
                       MGMT_TRIGGER_RESTART,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        printf("*********** Returned from the MGMT Restart *************\n");
        mtp3flag = 1;
    }
#elif defined (ANSI)
    if (DBC_Cmd(dbc, "start", "Start ANSI MTP3", "", ""))
    {
        printf("*********** Starting ANSI MTP3 **************\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_RESTART,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        printf("*********** Returned from the MGMT Restart *************\n");
        mtp3flag = 1;
    }
#endif

#if 0
/* this is changed to StartRSC */
    else if(DBC_Cmd(dbc, "startUBL", "Start Unblocking Now", "", ""))
    {
        if( mtp3flag == 0 )
        {
            printf("Start MTP3 first!\n");
            sprintf(buf,"Start MTP3 first!");
            DBC_AppendText(dbc, buf);
            DBC_SendCommandResult(dbc, instance);
        }
        else
        {
            printf("*********** Starting UBLS for Local Unblock **************\n");
            StartUnblocking();
        }
    }
#endif

    else if(DBC_Cmd(dbc, "startRSC", "Start Reset of Circuits Now", "", ""))
    {
        if( mtp3flag == 0 )
        {
            printf("Start MTP3 first!\n");
            printf("Usage: >> start\n");
            sprintf(buf,"Start MTP3 first!");
            DBC_AppendText(dbc, buf);
            DBC_SendCommandResult(dbc, instance);
        }
        else
        {
            printf("*********** Starting RSC for Circuit Reset **************\n");
            StartRSC();
        }
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
    else if(DBC_Cmd(dbc, "rscRange", "Reset the Cic Range", "", ""))
    {
        ISUP_CFG_KEY cfg;
        ISUP_CFG_CKGP_INFO * info;
        int noEnt;

        cfg.opc = configInfo.lpc;
        cfg.dpc = configInfo.dpc;
        cfg.sio = configInfo.sio;

        #if defined(CCITT)
            ret = ISUP_GetAllCicsCfg_CCITT(cfg, &info, &noEnt);
        #else
            ret = ISUP_GetAllCicsCfg_ANSI(cfg, &info, &noEnt);
        #endif

        if (ret == ITS_SUCCESS)
        {
            isFirstEntry = ITS_TRUE;
            CicInfo* ptr = NULL;
            configInfo.numCics = 0;

            /*Extract the circuit groups and add them
             *in cic pool*/
            ExtractCicGrps(info, noEnt);
            free(info);

            /*Print the the cic pool*/
            ptr = cicInfo;

            if (ptr)
            {
                fprintf(logFp,"\n");
            }

            while( ptr )
            {
                printf("CIC: *%d*\t", ptr->cic);
                fprintf(logFp,"Cic: %d\n", ptr->cic);
                fflush(logFp);
                ptr = ptr->next;
                configInfo.numCics++;
            }

            printf("InitConfig(): Num Cics = %d\n", configInfo.numCics);

            fprintf(logFp,"\nNumber of Configured Cics = %d\n",
                    configInfo.numCics);
            fflush(logFp);
        }
        else if (ret == ITS_ENOTCONFIG)
        {
            sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                    " SIO (%d)\n ",configInfo.lpc,
                   configInfo.dpc,configInfo.sio);

            DBC_AppendText(dbc, buf);
        }
    }
    else if(DBC_Cmd(dbc, "STOPLOAD", "Stop Load test", "", ""))
    {
        loadTestDuration = 0;
        printf("Stopped Load \n");
    }
    else if (DBC_Cmd(dbc, "stat", "Print Statistics", "", ""))
    {
        /* send stats to client */
        /* Idea is to use the debug console to 
         * view load statistics whenever required.
         * The stats info should be sent to the 
         * DebugConsole client over a socket
         */

        sprintf(buf,"RLC Received = %d\n",rlcReceivedCounter);
        DBC_AppendText(dbc, buf);
        DBC_SendCommandResult(dbc, instance);
    }

    return;
}
