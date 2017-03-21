/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.2  2008/02/15 10:38:10  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:12:26  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/27 03:53:24  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2007/08/22 05:25:05  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.6  2007/05/04 09:10:16  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  2007/04/17 14:16:07  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/04/17 08:35:35  ashutosh.singh
 * LOG: Logger Lib related changes
 * LOG:
 * LOG: Revision 1.3  2007/03/19 05:08:28  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/01/05 06:00:43  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: BscMain.cpp,v 1.3 2008-06-05 04:50:03 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: BscMain.cpp,v 1.3 2008-06-05 04:50:03 bsccs2 Exp $"

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>
#include <engine++.h>

#include<mtp3_intern.h>
#include <its++.h>
#include <its_transports.h>
#include <its_types.h>
#include <its_link.h>
#include <mtp2_cmn.h>
#include <its_route_rwlock.h>
#include "trace.h"
#include <interface.h>
#ifdef LAPD_HA
#include <lapd_adaptation_layer.h>
#endif

#ifdef PLATFORM_IMR
extern "C"
{
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
unsigned char HealthNwStack;
}
#endif


#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
SysAddr slfAddr;
#endif



#include <stdlib.h>
#include <signal.h>
#define __USE_GNU
#include <string.h> //strsignal
#include <execinfo.h> //backtrace,backtrace_symbols
#include <ucontext.h> //ucontext_t
#define BACK_TRACE_DEPTH   100
void reg_sig_hndlr();

extern int NODECARDSTATE ;
#if defined (ANSI)
#define ITS_MTP2_SRC   ITS_MTP2_ANSI_SRC
#elif defined (CCITT)
#define ITS_MTP2_SRC ITS_MTP2_CCITT_SRC
#endif


#if defined (ANSI)
#define ITS_MTP3_SRC   ITS_MTP3_ANSI_SRC
#elif defined (CCITT)
#define ITS_MTP3_SRC ITS_MTP3_CCITT_SRC
#endif

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

THREAD_RET_TYPE Console_Thread(void *arg);
ITS_THREAD conThread;
void static ShutDownNode();
extern "C" void  read_config();
#ifdef LAPD_HA
/* lapd HA defines */
extern "C" void send_card_state_event_to_lapd(int cardState);
/* end here */

extern "C" int G_CARD_STATE;
#endif


static void Usage(const char** args)
{
    cout << " Usage: " << args[0] << endl;
    cout << " ConfigFileName <configFile> " << endl;
    cout << endl;
    exit (0);
}


int
ParseArguments(int argc, const char** args)
{
    int i = 3;
    int flag = 1;
    int ret = 0;

//    if (argc <= 5)
    if (argc <= 4)
    {
        Usage (args);
        return -1; 
    }

    for(; i < argc && flag; i++)
    {
        if(strcmp(args[i], "-configFile") == 0)
        {
           flag = 0;
        }
        else
        {
           Usage(args);
        }
    }

    /* from here onwards are engine arguments. */
    return (i - 2);
}
#ifdef PLATFORM_IMR
/*******************************************************************************
 * Function    : bpmAisCallbackFunc                                            *
 * Parameters  : None                                                          *
 * Description :                                                               *
 *                                                                             *
 *                                                                             *
 *                                                                             *
 *******************************************************************************/
extern  "C"
{
void nwStackBpmAisCallbackFunc(struct sAisParam* param)
{
DSM_MembershipChangeCbData_temp membershipChangeCbData;
CALLBACK_Manager *callbackManager = NULL;
ITS_USHORT ftGroupId = 0;
ITS_UINT ABSENT_FLAG=1; 

        ISIL_DEBUG_TRACE(("In AIS Handler Function\n"));

        switch(param->messageId)
        {
                case BPM_HEALTHCHECK_MESSAGE:
                       { 
                        ISIL_DEBUG_TRACE((" HealthCheck Callback Function by NW_STACKS \n"));
                        fflush(stdout);

                            bpmRespondToAis (param->invocation,OK);
                        }
                        break;

                case BPM_SELFCARD_STATE_CHANGE:
                    {
#ifdef LAPD_HA
                       G_CARD_STATE = param->cardState;
                       ISIL_DEBUG_TRACE(("SelfCard State Change Callback called: gcardState : %d \n", G_CARD_STATE));
                       if(param->cardState == CARDSTATE_ACTIVE)
                         {
                          ISIL_DEBUG_TRACE(("Card state active: event reported to lapd"));
                          send_card_state_event_to_lapd(CARD_ACTIVE);
                         }
                        else if(param->cardState == CARDSTATE_STANDBY)
                          {
                             ISIL_DEBUG_TRACE(("Card state standby: event reported to lapd"));
                             send_card_state_event_to_lapd(STANDBY);
                          }
#endif
                        ftGroupId = DSM_GetMaxNumFtGroups(); 
                        if(ftGroupId == 0)
                        {
                           ISIL_ERROR_TRACE((" MaxNumFtGroups is 0 :Xml not read successfully\n"));
                           break; 
                        }
                        else
                        {
                          ISIL_DEBUG_TRACE((" MaxNumFtGroups is [%d] \n",ftGroupId));
                        }
        
                       callbackManager = DSM_GetMembershipChangeCallbacks(DSM_Mtp3FtGroupId);
                       if (callbackManager != NULL )
                          {
                            if(param->cardState == CARDSTATE_ACTIVE)
                            {
                              memset(&membershipChangeCbData,0,sizeof(DSM_MembershipChangeCbData_temp));
                              membershipChangeCbData.membershipChangeType= PLATFORM_ACT_NOTIF_EVENT;
                              sleep(3);
                              CALLBACK_CallCallbackList(callbackManager,NULL,(ITS_POINTER)&membershipChangeCbData);
                              bpmRespondToAis (param->invocation,OK);
                              NODECARDSTATE = CARDSTATE_ACTIVE;
                              ISIL_DEBUG_TRACE(("SETTING NODECARDSTATE[%d] To ACTIVE\n",NODECARDSTATE));
                              ISIL_DEBUG_TRACE(("SelfCard State Change Successful Done from BACKUP TO ACTIVE :BPMCOMMAND CARDSTATE_ACTIVE\n"));
                            }
                         else if(param->cardState == CARDSTATE_STANDBY)
                          {
                             memset(&membershipChangeCbData,0,sizeof(DSM_MembershipChangeCbData_temp));
                             membershipChangeCbData.membershipChangeType= PLATFORM_BKUP_NOTIF_EVENT;
                             CALLBACK_CallCallbackList(callbackManager,NULL,(ITS_POINTER)&membershipChangeCbData);
                             NODECARDSTATE = CARDSTATE_STANDBY;
                              ISIL_DEBUG_TRACE(("SETTING NODECARDSTATE[%d] To BACKUP\n",NODECARDSTATE));
                             ISIL_DEBUG_TRACE(("SelfCard State Change Successful Done to  BACKUP :BPMCOMMAND CARDSTATE_STANDBY\n"));
                             bpmRespondToAis (param->invocation,OK);
                          }
                         else if(param->cardState == CARDSTATE_RECOVERY)
                          {
                             ISIL_DEBUG_TRACE(("SelfCard State Change SELF :BPMCOMMAND CARDSTATE_RECOVERY\n"));
                             bpmRespondToAis (param->invocation,OK);
                             abort();
                                 
                          }
                          else
                           {
                              bpmRespondToAis (param->invocation,OK);
                              ISIL_DEBUG_TRACE(("CARD STATE RECEVIED %d\n", param->cardState));
                           }

                          }
                      }
                       break;

                case BPM_PEERCARD_STATE_CHANGE:

#ifdef LAPD_HA
                       if(param->cardState == CARDSTATE_ABSENT)
                       {
                         ISIL_DEBUG_TRACE(("PEER CARD ABSENT received"));
                         send_card_state_event_to_lapd(PEER_ABSENT);
                       }
                       ISIL_DEBUG_TRACE(("PeerCard State Change Callback called: state :%d", param->cardState));
#endif
                     /**********ACTIVE IN CASE OF PEER CARD ABSENT OR FAIL**************/
                  if((param->cardState == CARDSTATE_ABSENT ||param->cardState == CARDSTATE_FAIL ||param->cardState == CARDSTATE_RECOVERY) && (ABSENT_FLAG == 1) )
                    {
                       ABSENT_FLAG = 0;
                       callbackManager = DSM_GetMembershipChangeCallbacks(DSM_Mtp3FtGroupId);
                       if (callbackManager != NULL )
                          {
                           memset(&membershipChangeCbData,0,sizeof(DSM_MembershipChangeCbData_temp));
                           membershipChangeCbData.membershipChangeType= PLATFORM_ACT_NOTIF_EVENT;
                           NODECARDSTATE = CARDSTATE_ACTIVE;
                           ISIL_DEBUG_TRACE(("Setting NODECARDSTATE[%d] TO ACTIVE\n",NODECARDSTATE));
                           ISIL_DEBUG_TRACE(("SelfCard State Change BACKUP TO ACTIVE:: :PEER BPMCOMMAND CARDSTATE_ABSENT CARDSTATE_FAIL CARDSTATE_RECOVERY \n"));
                           CALLBACK_CallCallbackList(callbackManager,NULL,(ITS_POINTER)&membershipChangeCbData);
                          }
                          
                    }
                    else if(param->cardState == CARDSTATE_IN_SERVICE)
                     {
                           ISIL_DEBUG_TRACE(("SelfCard :PEER BPMCOMMAND CARDSTATE_IN_SERVICE \n"));
                           ABSENT_FLAG=1;
                     }
                     bpmRespondToAis (param->invocation,OK);
                     break;

                case BPM_MSG_ACK_CONFIGURE:
                     ISIL_DEBUG_TRACE(("Message Acknowledgement received from Executive\n"));
                     bpmRespondToAis (param->invocation,OK);
                        break;

                case BPM_SHUTDOWN:
                        ISIL_DEBUG_TRACE(("\n SIGUSR1 RECEIVED by NW_STACKS and calling ABORT\n"));
                        bpmRespondToAis (param->invocation,OK);
                        abort();
                        TIMERS_Sleep(5);
                       /*         ShutDownNode();


                               ENGINE_Terminate(); */
                      break;
                default:
                        break;
        }
}



}  /* extern  "C" */
#endif

extern  "C"
{
int
main(int argc, const char **args)
{
    int ret;
    char *path=NULL;
   const char *Orgpath; 
  #ifdef LOGGER_IMR
    slfAddr.prcr = 0;
    slfAddr.entity = 86;
    slfAddr.clsId = 0;
    slfAddr.rfu = 0;
    slfAddr.inst = 0;
    if(InitLoggingUtility(slfAddr) == 0)
     {
      printf(" ISIL GET REGISTERED  with LOGGER Utility   ");
     }
    else
     {
      printf (" ISIL couldnot  REGISTERED  with LOGGER Utility   ");
     }

  #endif


    Orgpath=(const char *)malloc(200);


    ret = ParseArguments(argc, args);
    path=getenv((const char *)"CONFIG");


    if(path == NULL)
    {
       printf("NO XML PATH FOUND\n");
     }
    strcat((char *)Orgpath,path);

#ifndef MTP2SIM

#ifdef PLATFORM_IMR
#ifdef CCITT
    strcat((char *)Orgpath,"CCITT-NWSTK-MCC.xml");
#else
    strcat((char *)Orgpath,"ANSI-NWSTK-MCC.xml");
#endif

    /*  Application will  register with application  */
    bpmGetComponentRegister(nwStackBpmAisCallbackFunc, (unsigned short)APPID_NW_STACKS);
    bpmComponentConfigure();   
    reg_sig_hndlr();
#else

#ifdef CCITT
    strcat((char *)Orgpath,"CCITT-NWSTK-MCC.xml");
#else
    strcat((char *)Orgpath,"ANSI-NWSTK-MCC.xml");
#endif

#endif


#endif 

#ifdef PLATFORM_IMR
 /* replace with  connection lib  */
    read_config();  //ADDED  by ANAND
#else

    read_config();  //ADDED  by ANAND
#endif
   
    strcpy((char *)args[4],Orgpath);  
    printf("args[4] %s\n",args[4]); 
		ENGINE_Initialize((argc - ret), &args[ret], NULL, 0);

    ret = ENGINE_Run(argc, args);

    return ret;
}

} /*  extern "C" */



void static
ShutDownNode()
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;
    char buf[ITS_PATH_MAX];

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return;
    }

    for ( tr = tm->listHead;
          tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
    {
        mask = TRANSPORT_MASK(tr);

        if ((mask & ITS_MTP2) == ITS_MTP2)
        {
            SS7_LinkPtr lp;

            for (lp = TRANSPORT_SS7_INFO(tr).linkInfo;
                 lp != NULL; lp = lp->next)
            {
               sprintf(buf, "Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);

#ifdef  CCITT
               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
#else
               MGMT_Main_ANSI(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);

#endif
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);
}




void print_ppc_context(ucontext_t *uc)
{
  unsigned int i = 0;
  for (i=0; i < 32; i++) {
   ISIL_ERROR_TRACE(("R%d [0x%x] [%u]",i,uc->uc_mcontext.regs->gpr[i],uc->uc_mcontext.regs->gpr[i]));
  }
   ISIL_ERROR_TRACE(("NIP       [0x%x] [%u]",uc->uc_mcontext.regs->nip,uc->uc_mcontext.regs->nip));
  ISIL_ERROR_TRACE(("MSR       [0x%x] [%u]",uc->uc_mcontext.regs->msr,uc->uc_mcontext.regs->msr));
  ISIL_ERROR_TRACE(("ORIG_GPR3 [0x%x] [%u]",uc->uc_mcontext.regs->orig_gpr3,uc->uc_mcontext.regs->orig_gpr3));
  ISIL_ERROR_TRACE(("CTR       [0x%x] [%u]",uc->uc_mcontext.regs->ctr,uc->uc_mcontext.regs->ctr));
  ISIL_ERROR_TRACE(("LINK      [0x%x] [%u]",uc->uc_mcontext.regs->link,uc->uc_mcontext.regs->link));
  ISIL_ERROR_TRACE(("XER       [0x%x] [%u]",uc->uc_mcontext.regs->xer,uc->uc_mcontext.regs->xer));
  ISIL_ERROR_TRACE(("CCR       [0x%x] [%u]",uc->uc_mcontext.regs->ccr,uc->uc_mcontext.regs->ccr));
  ISIL_ERROR_TRACE(("MQ        [0x%x] [%u]",uc->uc_mcontext.regs->mq,uc->uc_mcontext.regs->mq));
}

void printBackTrace(ucontext_t *uc)
{
  void *BackTrace[BACK_TRACE_DEPTH];
  char **messages = (char **)NULL;
  int i, BackTraceSize = 0;

  BackTraceSize = backtrace(BackTrace, BACK_TRACE_DEPTH);

  /* overwrite sigaction with caller's address */
  if (uc)  {
    BackTrace[2] = (void * )uc->uc_mcontext.regs->nip;
    BackTrace[3] = (void * )uc->uc_mcontext.regs->link;
  }

  messages = backtrace_symbols(BackTrace, BackTraceSize);
  /* skip first stack frame (points here) */

  ISIL_ERROR_TRACE(("[bt] Execution path:"));

  for (i=2; i < BackTraceSize; ++i) {
    ISIL_ERROR_TRACE(("[bt]#[%u]->%s",i-2,messages[i]));
  }
}

void bsc_sighandler(int signum, siginfo_t *sig_info, void *secret)
{
  ucontext_t *uc = (ucontext_t *)secret;


  ISIL_ERROR_TRACE(("Got Signal [%d] [%s]",signum,strsignal(signum)));

  if (signum == SIGSEGV) {
    ISIL_ERROR_TRACE(("SIGSEGV Faulty Address is [%p]",sig_info->si_addr));
  }
  print_ppc_context(uc);
  printBackTrace(uc);
  printf("\n");

  signal(signum,SIG_DFL);

  kill(getpid(),signum);
  return ;
}

void reg_sig_hndlr()
{
  /* Install our signal handler */
  struct sigaction sa;

//  sa.sa_sigaction = (void *)bsc_sighandler;
  sa.sa_sigaction = bsc_sighandler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGFPE , &sa, NULL);
  sigaction(SIGABRT , &sa, NULL);
  sigaction(SIGKILL , &sa, NULL);

  /* ... add any other signal here */

  return ;
}


