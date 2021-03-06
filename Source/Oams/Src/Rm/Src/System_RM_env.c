
/* SKELETON for env functions */
/* Program generated by Cadvanced 3.0.0.0.2032 */
#define XSCT_CADVANCED

#define C_TRANSLATOR_2_6
#include "scttypes.h"
#ifdef XUSE_SIGNAL_NUMBERS
#include "System_RM.hs"
#endif
#ifdef XENV_INC
#include XENV_INC
#endif
#include "System_RM.ifc"

#include <stdio.h>
#include <signal.h>
#include "oamsrm_signal_handler.h"
#include "dbsxxx_commondefs.h"
#include "dbsxxx_commonwrappers.h"
#include "DBLIBError.h"
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include "sysxxx_msgstruct.h"
#include "sysxxx_proc.h"
#include "sysinst_hashdefs.h"

#include"ipcfrm_extern.h"
#include"ipcfrm_msgqueue.h"
#include"ipcfrm_syslog.h"
#include"sysxxx_msgopcode.h"
#ifndef XNOGLOBALNODENUMBER
/*---+---------------------------------------------------------------
     xGlobalNodeNumber  extern
-------------------------------------------------------------------*/
#ifndef XENV_NODENUMBER
#define XENV_NODENUMBER return 1;
#endif

#define SELF_ENTITY_ID ENT_OAMS_RM
#define SELF_ENTITY_NAME "RM"
extern int xGlobalNodeNumber(void)
{
  /* Assign a unique global system Id to each SDL system in a cluster of systems. */
return (int)SELF_ENTITY_ID;
XENV_NODENUMBER
}
#endif

/**
  * Interface with Base Platform Module (BPM)
  * Note1: BPM is an optional feature in the system.
  * All code pertaining to BPM interface should be under a compile time
  * flag.
  */
#include "bpmxxx_commonDef.h"
#include "bpmxxx_platformLib.h"
#include "oamsxxx_mutex.h"
I_Bool cardStateRecovery=I_FALSE;
I_Bool globalExitCheck=I_FALSE;
I_S32 gCurrentCardState = CARDSTATE_INIT;
I_U8 isStndbyCard=I_FALSE;
DEFINE_MUTEX;
#if BPM_PRESENT != 1

#define RegisterRmWithBpm() bpmGetComponentReg(ENT_OAMS_RM_STUB,&RmBpmCallbackFunc);
#define bpmRespondToAis(a,b) 
                          
#warning "BPM support not compiled"

#else
void RmBpmCallbackFunc (struct sAisParam *);
void RegisterRmWithBpm(void)
{
   bpmGetComponentRegister (RmBpmCallbackFunc, ENT_OAMS_RM);
   bpmComponentConfigure ();
}

#endif /* BPM_PRESENT */

void  lockDb()
{
  I_S32 res=0, retVal;
  I_S32 i = 0;

  LOG_PRINT(DEBUG,"Entering LockDb()");
  res = clib_put((I_S32)0, EDB_DEMOTE_MASTER, (I_Void*) &i, (I_S16)sizeof(I_S32));

  res=dbDestroy();

  retVal = dbConnect();

  LOG_PRINT(DEBUG,"Exiting LockDb()");
  return ;

}//LockDB

void  lock1Db()
{
  I_S32 res=0, retVal;
  I_S32 i = 0;

  LOG_PRINT(DEBUG,"Entering Lock1Db()");
  //res = clib_put((I_S32)0, EDB_DEMOTE_MASTER, (I_Void*) &i, (I_S16)sizeof(I_S32));
  LOG_PRINT(DEBUG,"Exiting Lock1Db()");
  exit(0);
  /*
  res=dbDestroy();

  retVal = dbConnect();

  LOG_PRINT(DEBUG,"Exiting Lock1Db()");
  return ;
  */

}//Lock1DB

void CardStateChangeHandler(I_S8 targetState)
{
	xSignalNode         S;
        I_S32   retVal = ZERO;
        SDL_Pid             rcvr;
        rcvr.GlobalNodeNr = (I_S32)(SELF_ENTITY_ID);
        rcvr.LocalPId = (xLocalPIdNode)ZERO;


	switch(targetState)
        {
		case CARDSTATE_INIT:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_INIT ");
                        gCurrentCardState = CARDSTATE_INIT;
												isStndbyCard = I_FALSE;
                        RELEASE_MUTEX;
                        break;

		}
		case CARDSTATE_IN_SERVICE:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_IN_SERVICE:");
			if (gCurrentCardState==CARDSTATE_INIT)
			{
                                LOG_PRINT(DEBUG,"Registering with DB Server...");
                                /*result = dbDestroy();
                                if ( result != DBLIB_SUCCESS )
                                {
                                         LOG_PRINT(CRITICAL,"GRHM: Unable to Register itself with DBServer:Exiting");
                                         exit(0);
                                }*/
                                /*Initialize logging Utility*/

                                retVal = dbConnect();
                                if ( retVal != DBLIB_SUCCESS )
                                {
                                        LOG_PRINT(CRITICAL,"RM: Unable to Register itself with DBServer:Exiting");
                                        exit(0);
                                }
                                LOG_PRINT(DEBUG,"RM:Successfully Registered with DB Server.");

				InitInstMap(SELF_ENTITY_ID,CPHM_ACT_CLID_CPM);
	                        InitInstMap(SELF_ENTITY_ID,CPHM_ACT_CLID_RM);
	                        
				S = xGetSignal( sig_ENV_RM_CARD_STATE_CHANGE, xNotDefPId, xEnv);
	      	                (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_INIT; 
				SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );

                                gCurrentCardState = CARDSTATE_IN_SERVICE;
			}
			else if(gCurrentCardState==CARDSTATE_ACTIVE)
			{

				/* S = xGetSignal( sig_ENV_RM_CARD_STATE_CHANGE, xNotDefPId, xEnv);
        	                (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_ACTIVE; 
				SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 ); */
				
				LOG_PRINT(DEBUG,"RM:Successfully RELEASE_MUTEX in CARDSTATE_ACTIVE");
				cardStateRecovery=I_TRUE;	
        gCurrentCardState = CARDSTATE_IN_SERVICE;
				globalExitCheck=I_TRUE;

			}
   			else 
 			{
                                gCurrentCardState = CARDSTATE_IN_SERVICE;
                        	RELEASE_MUTEX;
			}
																isStndbyCard=I_FALSE;
		}
		break;
		case CARDSTATE_STANDBY:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_STANDBY");
                        gCurrentCardState = CARDSTATE_STANDBY;
			lockDb();
			isStndbyCard=I_TRUE;
                        RELEASE_MUTEX;
                        break;
		}
                case CARDSTATE_ACTIVE_IN_PROGRESS:
                {
                        LOG_PRINT(INFO,"(ENV) : Recieved State :CARDSTATE_ACTIVE_IN_PROGRESS ");
			S = xGetSignal( sig_ENV_RM_CARD_STATE_CHANGE, xNotDefPId, xEnv);
        	        if(gCurrentCardState==CARDSTATE_IN_SERVICE)
		           (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_IN_SERVICE; 
        	        if(gCurrentCardState==CARDSTATE_STANDBY)
		           (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_STANDBY; 
                        SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
                        gCurrentCardState = CARDSTATE_ACTIVE_IN_PROGRESS;
                        break;
                }
		case CARDSTATE_ACTIVE:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_ACTIVE");
                        gCurrentCardState = CARDSTATE_ACTIVE;
												if(isStndbyCard == I_TRUE)
												{
											 S = xGetSignal( sig_ENV_RM_CARD_STATE_CHANGE, xNotDefPId, xEnv);
                       (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_ACTIVE_IN_PROGRESS;
                       SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
											  }
												else
												{				
												isStndbyCard=I_FALSE;
                        RELEASE_MUTEX;
												}
                        break;

		}
		case CARDSTATE_RECOVERY:
		{
                        LOG_PRINT(INFO,"(ENV) : Received State :  CARDSTATE_RECOVERY");
			if (gCurrentCardState == CARDSTATE_ACTIVE )
                        {
			  S = xGetSignal( sig_ENV_RM_CARD_STATE_CHANGE, xNotDefPId, xEnv);
                          (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_ACTIVE;
                          SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
                        }
			else
			{
			   RELEASE_MUTEX;
			}
		   	cardStateRecovery=I_TRUE;	
                        gCurrentCardState = CARDSTATE_RECOVERY;
							isStndbyCard=I_FALSE;
                        break;
		}
		case CARDSTATE_TEST:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_TEST");
                        gCurrentCardState = CARDSTATE_TEST;
                        RELEASE_MUTEX;
                        break;

		}
#if 0
		case CARDSTATE_MAJOR_UPGRADE:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_MAJOR_UPGRADE");
                        gCurrentCardState = CARDSTATE_MAJOR_UPGRADE;
                        RELEASE_MUTEX;
                        break;

		}
		case CARDSTATE_MINOR_UPGRADE:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_MINOR_UPGRADE");
                        gCurrentCardState = CARDSTATE_MINOR_UPGRADE;
                        RELEASE_MUTEX;
                        break;

		}
#endif
		case CARDSTATE_UPGRADE:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_UPGRADE");
                        gCurrentCardState = CARDSTATE_UPGRADE;
                        RELEASE_MUTEX;
                        break;

		}
		case CARDSTATE_OUT_OF_SERVICE:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_OUT_OF_SERVICE");
        	        if(gCurrentCardState==CARDSTATE_ACTIVE)
			{
			   S = xGetSignal( sig_ENV_RM_CARD_STATE_CHANGE, xNotDefPId, xEnv);
		           (((yPDP_sig_ENV_RM_CARD_STATE_CHANGE)S)->Param1) =BSC_APP_CARDSTATE_ACTIVE; 
			   SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
			}
			else 
			{
                           RELEASE_MUTEX;
			}
                        gCurrentCardState = CARDSTATE_OUT_OF_SERVICE;
                        break;

							isStndbyCard=I_FALSE;
		}
		case CARDSTATE_PLATFORM_INS:
		{
			LOG_PRINT(INFO,"(ENV) : Received State : CARDSTATE_PLATFORM_INS");
                        gCurrentCardState = CARDSTATE_PLATFORM_INS;
                        RELEASE_MUTEX;
                        break;

		}
		default:
			LOG_PRINT(INFO,"(ENV) : Unhandled State Recieved");

	}

}
void RmBpmCallbackFunc (struct sAisParam *param)
{
   switch (param->messageId)
   {
      case BPM_HEALTHCHECK_MESSAGE:
            	bpmRespondToAis (param->invocation, OK);
           break;

      case BPM_SELFCARD_STATE_CHANGE:
           LOG_PRINT(INFO, "(RM): Env):BPM_SELFCARD_STATE_CHANGE recd");
	   LOCK_MUTEX;
	   //SendBpmNotification(param->cardState);
           CardStateChangeHandler(param->cardState);
						if (globalExitCheck==I_TRUE)
							{	
							  	
					    	LOG_PRINT(INFO,"calling bpmRespondToAis.. ");
								bpmRespondToAis (param->invocation, OK);
								LOG_PRINT(INFO,"called bpmRespondToAis.. globalExitCheck is %d ",globalExitCheck);
								struct timeval tv;
								tv.tv_sec = 1;
								tv.tv_usec = 0;
								timeToSleep:
								select(1, NULL, NULL, NULL, &tv);
								if(errno == EINTR)
								{
									LOG_PRINT(DEBUG,"Err Signal caught EINTR");
									goto timeToSleep;
								}        
								exit(0);
							} //if of globalExitCheck
           if ( LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE && cardStateRecovery != I_TRUE )
           {
           	LOG_PRINT(INFO,"calling bpmRespondToAis.. ");
           	bpmRespondToAis (param->invocation, OK);
                RELEASE_MUTEX;
           }
           else
           {
           	LOG_PRINT(INFO,"MUTEX Wait Timed Out Or Card in Recovery State ");
           }
           break;

      case BPM_PEERCARD_STATE_CHANGE:
           LOG_PRINT(INFO, "(RM): (Env):BPM_PEERCARD_STATE_CHANGE recd, No Action Taken");
           bpmRespondToAis (param->invocation, OK);
           break;

      case BPM_MSG_ACK_PEER_HEALTH_BAD:
           LOG_PRINT(INFO, "(RM): (Env):BPM_MSG_ACK_PEER_HEALTH_BAD recd, Not Expected");
           break;

      case BPM_MSG_ACK_CONFIGURE:
           LOG_PRINT(INFO, "(RM): (Env):BPM_MSG_ACK_CONFIGURE recd");
           break;

      case BPM_MSG_ACK_CONFIGURE_RESET:
           LOG_PRINT(INFO, "(RM): (Env):BPM_MSG_ACK_CONFIGURE_RESET recd, No Action Taken");
           break;

      case BPM_SHUTDOWN:
           LOG_PRINT(INFO, "(RM): (Env):BPM_SHUTDOWN recd, Exiting");
           exit (1);
           break;

      default:
           LOG_PRINT(MAJOR, "(RM): (Env):Unexpected msg from BPM: %d", param->messageId);
           break;
   }
}
I_U32 rmSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   LOG_PRINT(DEBUG,"Entering into rmSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      LOG_PRINT(DEBUG,"Memory Allocation Failed");
      return -1;
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   sndPtr->src.entity = SrcEntId;
   sndPtr->dest.entity = DestEntId;

   //sndPtr->dest.entity = DESTINATION;


   LOG_PRINT(DEBUG," sndPtr->msgType = %d", sndPtr->msgType);
   LOG_PRINT(DEBUG," sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   LOG_PRINT(DEBUG," sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);
   LOG_PRINT(DEBUG," Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      LOG_PRINT(DEBUG,"In func rmSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   LOG_PRINT(DEBUG,"Exiting from rmSendMessage().....");
   return(1);
}

void SendBpmNotification(I_S8 state)
{
	RmCardStateNotification rmCardStateNotification;
	rmCardStateNotification.cardState=state; 
	I_U32 result=rmSendMessage(&rmCardStateNotification,sizeof(RmCardStateNotification) ,ENT_OAMS_RM,ENT_OAMS_CFG,BPM_SELFCARD_STATE_CHANGE,0);
}


void *rmSigalrmHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal Alarm");
} /* End of function cfgSigalrmHandler() */

/* Signal handling of SIGINT */
void *rmSigintHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGINT");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}

/* Signal handling of SIGQUIT */
void *rmSigquitHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGQUIT");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}

/* Signal handling of SIGSTOP */
void *rmSigstopHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGSTOP");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}
/* Signal handling of SIGSEGV */
void *rmSigsegvHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGSEGV");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}

/* Signal handling of SIGBUS */
void *rmSigbusHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGBUS");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}
/* Signal handling of SIGILL */
void *rmSigillHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGILL");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}
/* Signal handling of SIGFPEV */
void *rmSigfpeHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGFPE");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}
/* Signal handling of SIGTERM */
void *rmSigtermHandler()
{
   LOG_PRINT(LOG_CRITICAL,"\nRM: Recieved signal SIGTERM");
   //lockDb();
   lock1Db();
   LOG_PRINT(LOG_INFO,"\nRM: Exiting.......");
   exit(0);
}
void rmSigInit()
{
   /* Ignore the signals */
   LOG_PRINT(LOG_INFO,"\nIam In rmSigInit()\n");
   signal(SIGINT, (sighandler_t )rmSigintHandler);
   signal(SIGQUIT, (sighandler_t )rmSigquitHandler);
   signal(SIGSTOP, (sighandler_t )rmSigstopHandler);
   signal(SIGUSR1, SIG_IGN);
   signal(SIGUSR2, SIG_IGN);
   //signal(SIGTERM, SIG_IGN);
   signal(SIGALRM, (sighandler_t )rmSigalrmHandler);

   signal(SIGSEGV, (sighandler_t )rmSigsegvHandler);
   signal(SIGBUS,(sighandler_t ) rmSigbusHandler);
   signal(SIGILL,(sighandler_t ) rmSigillHandler);
   signal(SIGFPE,(sighandler_t ) rmSigfpeHandler);
   signal(SIGTERM,(sighandler_t ) rmSigtermHandler);
   LOG_PRINT(LOG_INFO,"\n Iam exiting rmSigInit()\n");
}  

#ifndef XNOINITENV
/*---+---------------------------------------------------------------
     xInitEnv  extern
-------------------------------------------------------------------*/
#ifndef XENV_INIT
#define XENV_INIT
#endif

extern void xInitEnv(void)
{
  /* Code to initialize your SDL-system environment may be inserted here */
   SysAddr slfAddr;

#ifdef XTRACE
xPrintString("(RM): (Env):xInitEnv called\n");
#endif
   
  /* 
   if(InitLoggingUtility(slfAddr) < ZERO)
   {
      LOG_PRINT(CRITICAL," InitLoggingUtility Failed");
      exit(EXIT_FAILURE);
   }
   LOG_PRINT(INFO,"(RM): (Env):Registering with IPC FramWork...\n");
*/


   if (RegisterWithIpcFrmwrk(SELF_ENTITY_ID, SELF_ENTITY_NAME) < 0)
   {
      LOG_PRINT(CRITICAL,"(RM): (Env):Unable to Register itself with IPC FrameWork : Exiting");
      exit(0) ;
   }

   LOG_PRINT(INFO, "(RM): (Env):** SystemName=%s, ModuleName=%s, Version=%s **",SYSTEM_NAME, SELF_ENTITY_NAME, VERSION);


   /* retVal=SetInstCount(ENT_OAMS_CELLH,CELLHM_HANDLER,MAX_CELLHM_INST);  */

   RegisterRmWithBpm();

   rmSigInit();

   LOG_PRINT(INFO,"(RM): (Env):RM Process Initialized Successfully\n") ;
   

}
#endif


#ifndef XNOCLOSEENV
/*---+---------------------------------------------------------------
     xCloseEnv  extern
-------------------------------------------------------------------*/
#ifndef XENV_CLOSE
#define XENV_CLOSE
#endif

extern void xCloseEnv(void)
{
  /* Code to bring down the environment in a controlled manner
     may be inserted here. */
  I_S32 retVal;

  /* DeRegister with DB */
  if ((retVal = dbDestroy()) != DBLIB_SUCCESS)
  {
     LOG_PRINT(CRITICAL,"(CELLH): (Env):clib_destroy failed for CELLH (Error = %d)",retVal);
     exit(0);
  }/*if retVal */

#ifdef XTRACE
   xPrintString("(CELLH): (Env):xCloseEnv called\n");
#endif

}
#endif


/*---+---------------------------------------------------------------
     Macros for xOutEnv
-------------------------------------------------------------------*/
#ifndef OUT_LOCAL_VARIABLES
#define OUT_LOCAL_VARIABLES
#endif

#ifndef IF_OUT_SIGNAL
#define IF_OUT_SIGNAL(SIGNAL_NAME, SIGNAL_NAME_STRING) \
  if (((*SignalOut)->NameNode) == SIGNAL_NAME) {
#define END_IF_OUT_SIGNAL(SIGNAL_NAME, SIGNAL_NAME_STRING) \
  }
#endif

#ifndef OUT_SIGNAL1
#define OUT_SIGNAL1(SIGNAL_NAME, SIGNAL_NAME_STRING)
#endif

#ifndef OUT_SIGNAL2
#define OUT_SIGNAL2(SIGNAL_NAME, SIGNAL_NAME_STRING)
#endif

#ifndef XENV_ENC
#define XENV_ENC(stmt) stmt
#endif

#ifndef XENV_OUT_START
#define XENV_OUT_START
#endif

#ifndef RELEASE_SIGNAL
#define RELEASE_SIGNAL   xReleaseSignal(SignalOut); return;
#endif


/*---+---------------------------------------------------------------
     xOutEnv  extern
-------------------------------------------------------------------*/
extern void xOutEnv( xSignalNode *SignalOut
#ifdef XPATH_INFO_IN_ENV_FUNC
  , xChannelIdNode Port
#endif
 )
{
   I_Void  *sndPtr;
   I_S32   msgSize;

#ifdef XTRACE
	#ifdef XIDNAMES
	  char  Temp[100];
	  sprintf(Temp, "xOutEnv:  %s has been received by env\n",(*SignalOut)->NameNode->Name );
	  xPrintString(Temp);
	#else
	  xPrintString("xOutEnv:  One signal has been received by env\n");
	#endif
#endif

switch((*SignalOut)->NameNode->SignalNumber)
    {
       case SN_OAMS_RM_CFG_PEER_SWITCH_CONNECT_ACK:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CFG_PEER_SWITCH_CONNECT_ACK)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CFG_PEER_SWITCH_CONNECT_ACK)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv:Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CFG_PEER_SWITCH_CONNECT_NACK:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CFG_PEER_SWITCH_CONNECT_NACK)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CFG_PEER_SWITCH_CONNECT_NACK)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_GRHM_SWITCH_CONNECT:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_GRHM_SWITCH_CONNECT)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_GRHM_SWITCH_CONNECT)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_GRHM_SWITCH_RELEASE_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_GRHM_SWITCH_RELEASE_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_GRHM_SWITCH_RELEASE_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CFG_SLOT_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CFG_SLOT_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CFG_SLOT_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CFG_SLOT_RESP:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CFG_SLOT_RESP)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CFG_SLOT_RESP)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CPIF_PEER_SWITCH_CONNECT:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CPIF_PEER_SWITCH_CONNECT)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CPIF_PEER_SWITCH_CONNECT)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CPIF_PEER_SWITCH_ACK:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CPIF_PEER_SWITCH_ACK)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CPIF_PEER_SWITCH_ACK)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CPIF_PEER_SWITCH_NACK:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CPIF_PEER_SWITCH_NACK)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CPIF_PEER_SWITCH_NACK)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CPIF_SLOT_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CPIF_SLOT_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CPIF_SLOT_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CPIF_SLOT_RESP:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CPIF_SLOT_RESP)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CPIF_SLOT_RESP)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CELLH_AIP_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CELLH_AIP_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CELLH_AIP_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_TRXH_AIP_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_TRXH_AIP_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_TRXH_AIP_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_GRHM_AIP_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_GRHM_AIP_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_GRHM_AIP_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_BICH_AIP_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_BICH_AIP_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_BICH_AIP_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_BICH_ACTIVE_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_BICH_ACTIVE_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_BICH_ACTIVE_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_TRXH_ACTIVE_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_TRXH_ACTIVE_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_TRXH_ACTIVE_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_CELLH_ACTIVE_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_CELLH_ACTIVE_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_CELLH_ACTIVE_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_OAMS_RM_GRHM_ACTIVE_REQ:
       {
          sndPtr = ((yPDP_sig_OAMS_RM_GRHM_ACTIVE_REQ)(*SignalOut))->Param1;
          msgSize = ((yPDP_sig_OAMS_RM_GRHM_ACTIVE_REQ)(*SignalOut))->Param2;
          if (sndPtr == NULL)
          {
             LOG_PRINT(INFO,"xOutEnv :Received NULL pointer from Module, Returning without Sending to FRM........\n");
             xReleaseSignal(SignalOut);
             return ;
          }
          break;
       }
       case SN_ENV_RM_CARD_STATE_ACK:
       {
           LOG_PRINT(DEBUG,"xOutEnv: ENV_RM_CARD_STATE_ACK Received from Tau Model");
   	   RELEASE_MUTEX;
           xReleaseSignal(SignalOut);
           return;
       }
       default:
        LOG_PRINT(MAJOR,"xOutEnv: Invalid Msg.(0x%0x) Rcvd. From Model",
                  ((SysHdr *)sndPtr)->msgType);
        PRINT_HEX_DUMP(DEBUG, (I_U8 *)sndPtr, (I_U16)msgSize);

        DalocMsgBuf((I_Void *)sndPtr);
        xReleaseSignal(SignalOut);
        return;

  /* Signals going to the env via the port pPort */

       
   }//Switch
   PRINT_HEX_DUMP(DEBUG, (I_U8 *)sndPtr, (I_U16)msgSize);
   if (SendMsg(sndPtr,MSG_ORD_PRIO,msgSize) == SND_FAIL)
   {
	LOG_PRINT(CRITICAL,"xOutEnv :MESSAGE SENDING FAILED \n");
	xReleaseSignal(SignalOut);
	return;
   }
   else
   {
      LOG_PRINT(INFO,"xOutEnv:Successfully sent message out \n");
      xReleaseSignal(SignalOut);
      return;
   }
   
  /* Signals going to the env via the port ToEnv  */

}/*xOutEnv*/


/*---+---------------------------------------------------------------
     Macros for xInEnv
-------------------------------------------------------------------*/
#ifndef IN_LOCAL_VARIABLES
#define IN_LOCAL_VARIABLES \
  xSignalNode SignalIn;
#endif

#ifndef IN_SIGNAL1
#define IN_SIGNAL1(SIGNAL_NAME, SIGNAL_NAME_STRING) \
  SignalIn = xGetSignal(SIGNAL_NAME, xNotDefPId, xEnv);
#endif

#ifndef IN_SIGNAL2
#define IN_SIGNAL2(SIGNAL_NAME, SIGNAL_NAME_STRING) \
  SDL_Output(SignalIn xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0);
#endif

#ifndef IF_IN_SIGNAL
#define IF_IN_SIGNAL(SIGNAL_NAME, SIGNAL_NAME_STRING) \
  if (TEST_IF_IN_SIGNAL(SIGNAL_NAME)) {
#define END_IF_IN_SIGNAL(SIGNAL_NAME, SIGNAL_NAME_STRING) \
  }
#endif

#ifndef TEST_IF_IN_SIGNAL
#define TEST_IF_IN_SIGNAL(SIGNAL_NAME)  0
#endif

#ifndef XENV_DEC
#define XENV_DEC(stmt) stmt
#endif

#ifndef XENV_IN_START
#define XENV_IN_START
#endif

#ifndef XENV_IN_END
#define XENV_IN_END
#endif


/*---+---------------------------------------------------------------
     xInEnv  extern
-------------------------------------------------------------------*/
#ifndef XTENV
extern void xInEnv ( SDL_Time Time_for_next_event )
#else
extern SDL_Duration xInEnv ( SDL_Time Time_for_next_event )
#endif
{
  xSignalNode S;
 

#ifdef XTRACE
#ifndef XNOXINENVTRACE
  xPrintString( "xInEnv: Called!\n");
#endif
#endif

  I_PVoid rcvPtr = NULL;
  I_U32   msgSize= ZERO;
  I_S32   messageSize;
  I_U16   msgType = ZERO;
  SDL_Pid rcvr;
   
  if ((rcvPtr = (I_Void *)RecvMsg(SELF_ENTITY_ID, &messageSize)) != NULL)
  {

    msgSize=(I_U32)messageSize;
    msgType = ((SysHdr *)(rcvPtr))->msgType;

    LOG_PRINT(DEBUG,"xInEnv :  Msg. Rcvd type(0x%0x) size(%d) rcvPtr (0x%x)"
             , msgType, msgSize, (I_S32)rcvPtr);

    rcvr.GlobalNodeNr = (I_S32)(SELF_ENTITY_ID);
    rcvr.LocalPId = (xLocalPIdNode)ZERO;

    switch(msgType) {
	case BPM_SELFCARD_STATE_CHANGE:
	{
	   I_PVoid sndPtr;
 	   sndPtr=AlocMsgBuf(msgSize);
	   memcpy(sndPtr,rcvPtr,msgSize);
	   ((SysHdr*)sndPtr)->src.entity = ENT_OAMS_RM;
	   ((SysHdr*)sndPtr)->dest.entity = ENT_OAMS_CFG;
	   if (SendMsg(sndPtr,MSG_ORD_PRIO,msgSize) == SND_FAIL)
   	 {
	        LOG_PRINT(CRITICAL,"xOutEnv :MESSAGE SENDING FAILED \n");
		      DalocMsgBuf((I_PVoid) sndPtr);
   	 }
 	   else
	   {
	        LOG_PRINT(CRITICAL,"xOutEnv :MESSAGE SENT SUCCESSFULL \n");
		      DalocMsgBuf((I_PVoid) rcvPtr);
	   }
		 return;
	}

      case OAMS_CELLHM_RM_ACTIVE_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_CELLHM_RM_ACTIVE_RESP received ");
        S = xGetSignal( sig_OAMS_CELLH_RM_ACTIVE_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_CELLH_RM_ACTIVE_RESP)S)->Param1 = rcvPtr;
        break;
      case OAMS_TRXHM_RM_ACTIVE_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_TRXHM_RM_ACTIVE_RESP received ");
        S = xGetSignal( sig_OAMS_TRXH_RM_ACTIVE_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_TRXH_RM_ACTIVE_RESP)S)->Param1 = rcvPtr;
        break;
      case CSAPP_GRHM_RM_ACTIVE_RESP:
        LOG_PRINT(DEBUG,"xInEnv : CSAPP_GRHM_RM_ACTIVE_RESP received ");
        S = xGetSignal( sig_CSAPP_GRHM_RM_ACTIVE_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_CSAPP_GRHM_RM_ACTIVE_RESP)S)->Param1 = rcvPtr;
        break;
      case OAMS_BICHM_RM_ACTIVE_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_BICHM_RM_ACTIVE_RESP received ");
        S = xGetSignal( sig_OAMS_BICH_RM_ACTIVE_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_BICH_RM_ACTIVE_RESP)S)->Param1 = rcvPtr;
        break;
      case OAMS_CELLHM_RM_AIP_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_CELLHM_RM_AIP_RESP received ");
        S = xGetSignal( sig_OAMS_CELLH_RM_AIP_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_CELLH_RM_AIP_RESP)S)->Param1 = rcvPtr;
        break;
      case OAMS_TRXHM_RM_AIP_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_TRXHM_RM_AIP_RESP received ");
        S = xGetSignal( sig_OAMS_TRXH_RM_AIP_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_TRXH_RM_AIP_RESP)S)->Param1 = rcvPtr;
        break;
      case CSAPP_GRHM_RM_AIP_RESP:
        LOG_PRINT(DEBUG,"xInEnv : CSAPP_GRHM_RM_AIP_RESP received ");
        S = xGetSignal( sig_CSAPP_GRHM_RM_AIP_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_CSAPP_GRHM_RM_AIP_RESP)S)->Param1 = rcvPtr;
        break;
      case OAMS_BICHM_RM_AIP_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_BICHM_RM_AIP_RESP received ");
        S = xGetSignal( sig_OAMS_BICH_RM_AIP_RESP, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_BICH_RM_AIP_RESP)S)->Param1 = rcvPtr;
        break;

/*      case OAMS_CFG_RM_PEER_SWITCH_CONNECT:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_CFG_RM_PEER_SWITCH_CONNECT received ");
        S = xGetSignal( sig_OAMS_CFG_RM_PEER_SWITCH_CONNECT, xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_CFG_RM_PEER_SWITCH_CONNECT)S)->Param1 = rcvPtr;
        break;
      
      case CSAPP_GRHM_RM_SWITCH_CONNECT_ACK:
        LOG_PRINT(DEBUG,"xInEnv : CSAPP_GRHM_RM_SWITCH_CONNECT_ACK received ");
        S = xGetSignal( sig_CSAPP_GRHM_RM_SWITCH_CONNECT_ACK, xNotDefPId, xEnv);
        ((yPDP_sig_CSAPP_GRHM_RM_SWITCH_CONNECT_ACK)S)->Param1 = rcvPtr;
        break;

      case CSAPP_GRHM_RM_SWITCH_CONNECT_NACK:
        LOG_PRINT(DEBUG,"xInEnv : CSAPP_GRHM_RM_SWITCH_CONNECT_NACK received ");
        S = xGetSignal( sig_CSAPP_GRHM_RM_SWITCH_CONNECT_NACK, xNotDefPId, xEnv);
        ((yPDP_sig_CSAPP_GRHM_RM_SWITCH_CONNECT_NACK)S)->Param1 = rcvPtr;
        break;

      case OAMS_CFG_RM_SLOTID_REQ:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_CFG_RM_SLOTID_REQ received ");
        S = xGetSignal( sig_OAMS_CFG_RM_SLOT_REQ , xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_CFG_RM_SLOT_REQ)S)->Param1 = rcvPtr;
        break;
      
      case OAMS_CFG_RM_SLOTID_RESP:
        LOG_PRINT(DEBUG,"xInEnv : OAMS_CFG_RM_SLOTID_RESP received ");
        S = xGetSignal( sig_OAMS_CFG_RM_SLOT_RESP , xNotDefPId, xEnv);
        ((yPDP_sig_OAMS_CFG_RM_SLOT_RESP)S)->Param1 = rcvPtr;
        break;
      
      case TCP_CPIF_RM_PEER_SWITCH_CONNECT:
        LOG_PRINT(DEBUG,"xInEnv : TCP_CPIF_RM_PEER_SWITCH_CONNECT received ");
        S = xGetSignal( sig_TCP_CPIF_RM_PEER_SWITCH_CONNECT , xNotDefPId, xEnv);
        ((yPDP_sig_TCP_CPIF_RM_PEER_SWITCH_CONNECT )S)->Param1 = rcvPtr;
        break;
      
      case TCP_CPIF_RM_PEER_SWITCH_CONNECT_ACK:
        LOG_PRINT(DEBUG,"xInEnv : TCP_CPIF_RM_PEER_SWITCH_CONNECT_ACK received ");
        S = xGetSignal( sig_TCP_CPIF_RM_PEER_SWITCH_ACK , xNotDefPId, xEnv);
        ((yPDP_sig_TCP_CPIF_RM_PEER_SWITCH_ACK )S)->Param1 = rcvPtr;
        break;
      
      case TCP_CPIF_RM_PEER_SWITCH_CONNECT_NACK:
        LOG_PRINT(DEBUG,"xInEnv : TCP_CPIF_RM_PEER_SWITCH_CONNECT_NACK received ");
        S = xGetSignal( sig_TCP_CPIF_RM_PEER_SWITCH_NACK , xNotDefPId, xEnv);
        ((yPDP_sig_TCP_CPIF_RM_PEER_SWITCH_NACK )S)->Param1 = rcvPtr;
        break;
      
      case TCP_CPIF_RM_SLOT_REQ:
        LOG_PRINT(DEBUG,"xInEnv : TCP_CPIF_RM_SLOT_REQ received ");
        S = xGetSignal( sig_TCP_CPIF_RM_SLOT_REQ , xNotDefPId, xEnv);
        ((yPDP_sig_TCP_CPIF_RM_SLOT_REQ )S)->Param1 = rcvPtr;
        break;
      
      case TCP_CPIF_RM_SLOT_RESP:
        LOG_PRINT(DEBUG,"xInEnv : TCP_CPIF_RM_SLOT_RESP received ");
        S = xGetSignal( sig_TCP_CPIF_RM_SLOT_RESP , xNotDefPId, xEnv);
        ((yPDP_sig_TCP_CPIF_RM_SLOT_RESP)S)->Param1 = rcvPtr;
        break;*/
	
      default:
        LOG_PRINT(MAJOR,"Invalid Msg. Rcvd. From Outside(msgTyp = 0x%d) ",((SysHdr *)rcvPtr)->msgType);
        DalocMsgBuf(rcvPtr);
        return;
    }/*End of Switch condition*/
    PRINT_HEX_DUMP(DEBUG, (I_U8 *)rcvPtr, (I_U16)msgSize);
    SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );

  }/*End of If Condition*/

#ifdef XTENV
  return SDL_Time_Lit((xint32) ZERO,(xint32) ZERO);
#endif

}

