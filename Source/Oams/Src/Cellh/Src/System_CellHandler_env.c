
/* SKELETON for env functions */
#define XSCT_CADVANCED

#define C_TRANSLATOR_2_6
#include "scttypes.h"
#ifdef XUSE_SIGNAL_NUMBERS
#include "System_CellHandler.hs"
#endif
#ifdef XENV_INC
#include XENV_INC
#endif
#include "System_CellHandler.ifc"

#include "bpmxxx_platformLib.h"
#include "bpmxxx_OAM_commonDef.h"
#include "bpmxxx_commonDef.h"
#include "oamsxxx_mutex.h"


/* CS4.0: Changes for HA Start */
I_Void reg_sig_hndlr(I_Void);
I_S32 gCurrentCardState = CARDSTATE_INIT;
I_U32 gHandleMsgStart = I_FALSE;
I_S32 gNewCardState = CARDSTATE_INVALID;
I_U32 gLclPidActiveClass = INVALID_LCL_PID_PTR ;
I_U32 gInstancesCreated  = I_FALSE ;
I_U32 gSignalSent = ZERO;
I_S32 gInvocation;
I_U8 isStandbyCard=I_FALSE; //Abis HA
I_U8 isDbUnLockRcvd=I_FALSE; //Abis HA
I_U8 isAipRcvd = I_FALSE;
I_U8 isBpmActRcvd = I_FALSE;
I_U8 isRmActRcvd = I_FALSE;
I_S32 retVal=0; 
I_U32 bssAdminState=0;
I_S32 res;
CellPerTableApi           *ptrCellPerTableApi=NULL;
I_U32                      noOfRows=0;
I_U16                      rowSize=0;
I_U16                      i= 0;
CellPerTableApi            *tmpPtrCellPerTableApi;
I_U32 cellAdminState=0;


/* Defining Mutex */
DEFINE_MUTEX;
/* CS4.0: Changes for HA End */

I_S32 sendCellhRmAipResp(void)
{
  I_PVoid  sndAipPtr = NULL;
  I_U32    msgAipSize = ZERO;

  msgAipSize = sizeof(OamsCellhRmAipResp);
  sndAipPtr = (OamsCellhRmAipResp *)(AlocMsgBuf(msgAipSize));

  if(sndAipPtr == NULL)
  {
    LOG_PRINT(CRITICAL,"OamsCellhRmAipResp: Memory Alloc Fail");
    return I_FALSE;
  }

  FILL_SYS_HDR(sndAipPtr, OAMS_CELLHM_RM_AIP_RESP, 0, 0, ENT_OAMS_CELLH, 0, 0, ENT_OAMS_RM, 0);

  if (SendMsg(sndAipPtr, MSG_ORD_PRIO, msgAipSize) == SND_FAIL) 
  {
    LOG_PRINT(MAJOR,"xOutEnv:Snd. Fail.Message CSAPP_CELLH_RM_AIP_RESP");
    return I_FALSE;
  }

  else
    LOG_PRINT(INFO,"xOutEnv:Snd. Message CSAPP_CELLH_RM_AIP_RESP");

  return I_TRUE;
}



I_S32 sendCellhRmActiveResp(void)
{
  I_PVoid  sndAipPtr = NULL;
  I_U32    msgAipSize = ZERO;

  msgAipSize = sizeof(OamsCellhRmActiveResp);
  sndAipPtr = (OamsCellhRmActiveResp *)(AlocMsgBuf(msgAipSize));

  if(sndAipPtr == NULL)
  {
    LOG_PRINT(CRITICAL,"OamsCellhRmActiveResp: Memory Alloc Fail");
    return I_FALSE;
  }

  FILL_SYS_HDR(sndAipPtr, OAMS_CELLHM_RM_ACTIVE_RESP, 0, 0, ENT_OAMS_CELLH, 0, 0, ENT_OAMS_RM, 0);

  if (SendMsg(sndAipPtr, MSG_ORD_PRIO, msgAipSize) == SND_FAIL) 
  {
    LOG_PRINT(MAJOR,"xOutEnv:Snd. Fail.Message CSAPP_CELLH_RM_ACTIVE_RESP");
    return I_FALSE;
  }
  else
    LOG_PRINT(INFO,"xOutEnv:Snd. Message CSAPP_CELLH_RM_ACTIVE_RESP");

  return I_TRUE;
}

#ifndef XNOGLOBALNODENUMBER
/*---+---------------------------------------------------------------
  xGlobalNodeNumber  extern
  -------------------------------------------------------------------*/
#ifndef XENV_NODENUMBER
#define XENV_NODENUMBER return 1;
#endif

#define SELF_ENTITY_NAME "CELLHM"

I_S32   selfEntIdG ;
extern int xGlobalNodeNumber(void)
{
  /* Assign a unique global system Id to each SDL system in a cluster of systems. */
  return ENT_OAMS_CELLH ;
  XENV_NODENUMBER
}
#endif

/** 
 * Interface with Base Platform Module (BPM)
 * Note1: BPM is an optional feature in the system.
 * All code pertaining to BPM interface should be under a compile time
 * flag.
 */

#if BPM_PRESENT != 1

#define RegisterCellhmWithBpm() bpmGetComponentReg(ENT_OAMS_CELLH_STUB,&CellhmBpmCallbackFunc); 
/* CS4.0: Changes for HA Start */
#define bpmRespondToAis(a,b)
/* CS4.0: Changes for HA End */
#warning "BPM support not compiled"

#else

void CellhmBpmCallbackFunc (struct sAisParam *param);
void RegisterCellhmWithBpm(void) 
{
  bpmGetComponentRegister (CellhmBpmCallbackFunc, APPID_OAMS_CELLHM);
  bpmComponentConfigure ();
}

#endif /* BPM_PRESENT */


/********************************************************************/
/* CS4.0: Changes for HA Start */
I_Void cardStateChangeHandler(struct sAisParam *param)
{
  xSignalNode     S;
  SDL_Pid         rcvr;
  I_U32           lclPidPtr = INVALID_LCL_PID_PTR ;
  I_S32           result = ZERO;
  I_U32           instId = ZERO;
  I_S8            instCountResult = ZERO;
  I_U16           instCount = ZERO;
  I_U32           signalSentToModel = I_FALSE;
  I_U32       								refId = 0; 
  I_U32       								refId2 = 0; 
  CellhSwitchOverContextTableApi *ptrCellhSwitchOverContextTableApi=NULL;
  CellPerTableApi                *ptrCellPerTableApi=NULL;
  I_U32											noOfRows=0;
  I_U16											rowSize=0;
  I_U16 											i= 0;
  CellhSwitchOverContextTableApi *tmpPtrCellhSwitchOverContextTableApi=NULL;
  CellPerTableApi                *tmpPtrCellPerTableApi;
  I_S32 res;
  CellPerTableApi *cntxtCellTblRec;
  CellPerTableIndices *cntxtCellTblIndices;
  I_U32 chkresult=0;
  I_U32 cellAdminState=0;
  I_U32 bssAdminState=0;
  I_S32                     retVal = ZERO;


  rcvr.GlobalNodeNr = (I_S32)selfEntIdG;
  rcvr.LocalPId = (xLocalPIdNode)0;
  LOG_PRINT(INFO,"BPM_SELFCARD_STATE_CHANGE recd with CARD_STATE = %d", param->cardState) ;

  /* Init -> InService */
  //R2.9 Changes start
  if ( (param->cardState == CARDSTATE_IN_SERVICE) && (gCurrentCardState == CARDSTATE_INIT) )
  {
    gNewCardState = CARDSTATE_IN_SERVICE;
    LOG_PRINT(DEBUG,"Registering with DB Server...");
    result = dbConnect();
    if ( result != DBLIB_SUCCESS )
    {
      LOG_PRINT(CRITICAL,"CELLHandler: Unable to Register itself with DBServer:Exiting");
      return;
    }
    //LOG_PRINT(DEBUG,"Successfully Registered with DB Server.");
    LOG_PRINT(INFO,"Succ Registered with DB. Moving from INIT to INSERVICE..");

    instCountResult = GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER , &instCount);
    if ( instCountResult != INST_SUCCESS )
    {
      LOG_PRINT(MAJOR,"[ENV]GetInstCount Db call failed..");
      return;
    }

    if ( gInstancesCreated == I_FALSE )
    {
      InitInstMap(ENT_OAMS_CELLH,CELLHM_HANDLER);
      /* Sending internal signal to system class for creating tau instances */
      LOG_PRINT(INFO,"Handling INIT to INSERVICE: Send signal CELLH_INT_ADD_TAU_INSTANCE to model"); 
      gSignalSent = instCount;
      LOG_PRINT(INFO, "gSignalSent: %d", gSignalSent);
      rcvr.LocalPId = (xLocalPIdNode)gLclPidActiveClass;
      S = xGetSignal( sig_CELLH_INT_ADD_TAU_INSTANCE, rcvr, xEnv);
      SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
      gCurrentCardState = CARDSTATE_IN_SERVICE; 
    }
    else
    {
      gCurrentCardState = CARDSTATE_IN_SERVICE; 
      gNewCardState = CARDSTATE_INVALID;
      gHandleMsgStart = I_FALSE;
      RELEASE_MUTEX;
    }
    //R2.9 changes end
#if 0
    else
    {
      for ( instId = 1; instId <= instCount; instId++ )
      {
        findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
        LOG_PRINT(DEBUG,"findLclPidPtr Success lclPid=0x%x",(I_U32)lclPidPtr);
        if ( lclPidPtr != INVALID_LCL_PID_PTR ) 
        {
          if ((retVal = FreInstId(lclPidPtr, ENT_OAMS_CELLH, CELLHM_HANDLER)) != INST_SUCCESS)
          {
            LOG_PRINT(CRITICAL, "activeInProgressStateHandler: FreeInstId() Failed lclPidPtr = 0x%x [Act Cls Id = %d], [errCode =%d]",lclPidPtr, CELLHM_HANDLER,retVal);
            return;
          }
          else
          {
            LOG_PRINT(DEBUG,"activeInProgressStateHandler: FreeInstId() Success lclPidPtr = 0x%x [Act Cls Id = %d]",lclPidPtr, CELLHM_HANDLER);
          }
        }
        else
        {
          LOG_PRINT(INFO,"activeInProgressStateHandler: Instance is Created and is in FREE State...");
        }
      }

    }
#endif
  }  

  /* Active -> InService*/ 
  else if ( (param->cardState == CARDSTATE_IN_SERVICE) && ( gCurrentCardState == CARDSTATE_ACTIVE) )
  {
    gNewCardState = CARDSTATE_IN_SERVICE;
    instCountResult = GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER , &instCount);
    if ( instCountResult != INST_SUCCESS )
    {
      LOG_PRINT(MAJOR,"[ENV]GetInstCount Db call failed.. ");
      return;
    }
    gSignalSent = getCountAllocatedInst ( instCount ); /* To track No. of Signal sent to Model */
    LOG_PRINT(INFO, "Signal Sent to Model: %d", gSignalSent);

    for ( instId = 1; instId <= instCount; instId++ )
    {
      findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
      LOG_PRINT(DEBUG,"findLclPidPtr Success lclPid=0x%x",(I_U32)lclPidPtr);
      if ( lclPidPtr != INVALID_LCL_PID_PTR ) 
      {
        rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
        LOG_PRINT(INFO,"Send signal CELLH_INT_SELFCARD_STATE_CHANGE to Model");
        S = xGetSignal( sig_CELLH_INT_SELFCARD_STATE_CHANGE, rcvr, xEnv);

        (((yPDP_sig_CELLH_INT_SELFCARD_STATE_CHANGE)S)->Param1) = gCurrentCardState;
        (((yPDP_sig_CELLH_INT_SELFCARD_STATE_CHANGE)S)->Param2) = gNewCardState;
        SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
        signalSentToModel = I_TRUE;

      }

      if ( signalSentToModel == I_FALSE)
      {
        activeStateHandler();
      }
      LOG_PRINT(INFO,"Moving from ACTIVE->INSERVICE..");
    }
  }

  /* Active -> outOfService*/ 
  else if ( (param->cardState == CARDSTATE_OUT_OF_SERVICE) && ( gCurrentCardState == CARDSTATE_ACTIVE) )
  {
    gNewCardState = CARDSTATE_OUT_OF_SERVICE;
    instCountResult = GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER , &instCount);
    if ( instCountResult != INST_SUCCESS )
    {
      LOG_PRINT(MAJOR,"[ENV]GetInstCount Db call failed.. ");
      return;
    }
    gSignalSent = getCountAllocatedInst ( instCount ); /* To track No. of Signal sent to Model */
    LOG_PRINT(INFO, "Signal Sent to Model: %d", gSignalSent);

    for ( instId = 1; instId <= instCount; instId++ )
    {
      findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
      LOG_PRINT(DEBUG,"findLclPidPtr Success lclPid=0x%x",(I_U32)lclPidPtr);
      if ( lclPidPtr != INVALID_LCL_PID_PTR ) 
      {
        rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
        LOG_PRINT(INFO,"Send signal CELLH_INT_SELFCARD_STATE_CHANGE to Model");
        S = xGetSignal( sig_CELLH_INT_SELFCARD_STATE_CHANGE, rcvr, xEnv);

        (((yPDP_sig_CELLH_INT_SELFCARD_STATE_CHANGE)S)->Param1) = gCurrentCardState;
        (((yPDP_sig_CELLH_INT_SELFCARD_STATE_CHANGE)S)->Param2) = gNewCardState;
        SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
        signalSentToModel = I_TRUE;

      }

      if ( signalSentToModel == I_FALSE)
      {
        activeStateHandler();
      }
      LOG_PRINT(INFO,"Moving from ACTIVE->out of service..");
    }
  }

  /* InService -> StandBy*/
  /* InService -> StandBy*/
  else if ( (param->cardState == CARDSTATE_STANDBY) && (gCurrentCardState == CARDSTATE_IN_SERVICE) )
  {
    gNewCardState = CARDSTATE_STANDBY;
    //R2.9 changes start
    /*Abis HA changes start */
    /*	instCountResult = GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER , &instCount);
        if ( instCountResult != INST_SUCCESS )
        {
        LOG_PRINT(MAJOR,"[ENV]GetInstCount Db call failed..");
        return;
        }

        if ( gInstancesCreated == I_FALSE )
        {
        InitInstMap(ENT_OAMS_CELLH,CELLHM_HANDLER);*/
    /* Sending internal signal to system class for creating tau instances */
    /*LOG_PRINT(INFO,"Handling INSERVICE to Standbytransition: Send signal CELLH_INT_ADD_TAU_INSTANCE to model"); 
      gSignalSent = instCount;
    //LOG_PRINT(INFO, "gSignalSent: %d", gSignalSent);
    rcvr.LocalPId = (xLocalPIdNode)gLclPidActiveClass;
    S = xGetSignal( sig_CELLH_INT_ADD_TAU_INSTANCE, rcvr, xEnv);
    SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
    }
    else
    {
    for ( instId = 1; instId <= instCount; instId++ )
    {
    findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
    LOG_PRINT(DEBUG,"findLclPidPtr Success lclPid=0x%x",(I_U32)lclPidPtr);
    if ( lclPidPtr != INVALID_LCL_PID_PTR ) 
    {
    if ((retVal = FreInstId(lclPidPtr, ENT_OAMS_CELLH, CELLHM_HANDLER)) != INST_SUCCESS)
    {
    LOG_PRINT(CRITICAL, "activeInProgressStateHandler: FreeInstId() Failed lclPidPtr = 0x%x [Act Cls Id = %d], [errCode =%d]",lclPidPtr, CELLHM_HANDLER,retVal);
    return;
    }
    else
    {
    LOG_PRINT(DEBUG,"activeInProgressStateHandler: FreeInstId() Success lclPidPtr = 0x%x [Act Cls Id = %d]",lclPidPtr, CELLHM_HANDLER);
    }
    }
    else
    {
    LOG_PRINT(INFO,"activeInProgressStateHandler: Instance is Created and is in FREE State...");
    }
    }
    }*/
    gCurrentCardState = CARDSTATE_STANDBY; 
    gNewCardState = CARDSTATE_INVALID;
    LOG_PRINT(INFO,"Moving from INSERVICE->StandBy");
    RELEASE_MUTEX;
    gHandleMsgStart = I_FALSE;
    isStandbyCard = I_TRUE;	 



    /*Abis HA changes END */
    //R2.9 changes end
  }  

  /* InService,StandBy -> ActiveInProgress*/ 
  else if ( (param->cardState == CARDSTATE_ACTIVE_IN_PROGRESS) && ( ( gCurrentCardState == CARDSTATE_IN_SERVICE) || (gCurrentCardState == CARDSTATE_STANDBY) ) )  
  {
    gNewCardState = CARDSTATE_ACTIVE_IN_PROGRESS;

    if (isStandbyCard == I_TRUE )  //Abis HA
    {
      gHandleMsgStart = I_TRUE;
      isAipRcvd = I_TRUE;			
      if(isDbUnLockRcvd == I_TRUE)				
      {			 
        LOG_PRINT(INFO,"Entered STANDBY->AIP , flag = TRUE");
        if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
        {
          LOG_PRINT(INFO,"Error in fetching BSC Admin State");
        }
        if(bssAdminState == UNLOCKED)		
        {	

          //res = getallCellhSwitchOverContextTable(&ptrCellhSwitchOverContextTableApi, &noOfRows, &rowSize); 
          res = getallCellPerTable(&ptrCellPerTableApi,&noOfRows,&rowSize);
          if(res != CLIB_SUCCESS)
          {
            LOG_PRINT(INFO,"No Cell in DB. Moving from INSERVICE/StandBy->AIP");

          } //if res
          else
          {					
            LOG_PRINT(INFO,"Entered AIP,send INT MSG  noOfRows = %d",noOfRows);
            for(i=0; i<noOfRows; i++)
            {			 
              //tmpPtrCellhSwitchOverContextTableApi  = (CellhSwitchOverContextTableApi *)((I_U8*)(ptrCellhSwitchOverContextTableApi) + i*rowSize);
              tmpPtrCellPerTableApi  = (CellPerTableApi *)((I_U8*)(ptrCellPerTableApi) + i*rowSize);

              /*Read the Replicated context for CellId and Lac  in for loop*/				

              refId = tmpPtrCellPerTableApi->cellId;//From Replicated context
              refId2= tmpPtrCellPerTableApi->lac;   //From Replicated context
              LOG_PRINT(INFO,"CELLH:(Env): Prepare INT_CONTEXT_SWITCHOVER msg for  CellId - [%d], Lac - [%d]",refId,refId2); 

              cellAdminState =    tmpPtrCellPerTableApi->adminState;

              if(cellAdminState == 1)	
              {				


                LOG_PRINT(INFO,"ALLOCATE New Instance for CellId=%d Lac=%d",tmpPtrCellPerTableApi->cellId,tmpPtrCellPerTableApi->lac);	
                if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS )
                {
                  LOG_PRINT(CRITICAL,"No CELLHM Ins found for cellId = [%d] LAC = [%d]",refId, refId2);
                if (AlocNewInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS )
                {
                  LOG_PRINT(CRITICAL,"CELLH:(Env):Unable to create New Instance..\n") ;
                  gCurrentCardState = gNewCardState;
                  LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d]Moving to AIP State", gCurrentCardState,gNewCardState);
                  //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
                  //LOG_PRINT(INFO,"Moving to ACTIVE IN PROGRESS State ");
                  gHandleMsgStart = I_TRUE;

                  RELEASE_MUTEX;
                  return ;
                }
                }
                else
                {
                  LOG_PRINT(DEBUG, "xInEnv : INSTANCE ALLOCATED SEARCHED FOR CELLHM CELLID : %d, LAC : %d", refId, refId2);
                }
                /* R2.9 changes ends */
                if (lclPidPtr == 0)
                {
                  LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Inst Found...\n");
                  return ;
                }
                rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
                LOG_PRINT(INFO,"CELLH:(Env):LclPidPtr[%d]",lclPidPtr)
                                            /* Send this Message into TAU model */
                                            S = xGetSignal( sig_CELLH_INT_CHECK_CONTEXT_SWITCHOVER, rcvr, xEnv);
                (((yPDP_sig_CELLH_INT_CHECK_CONTEXT_SWITCHOVER)S)->Param1) = tmpPtrCellPerTableApi->cellId;
                (((yPDP_sig_CELLH_INT_CHECK_CONTEXT_SWITCHOVER)S)->Param2) = tmpPtrCellPerTableApi->lac;
                SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );	
              }//cellAdminState=1
            }//for
            free(ptrCellPerTableApi);
          }//else	
        }//if BscUnlocked
        gCurrentCardState = gNewCardState;
        gNewCardState = CARDSTATE_INVALID;
        LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d]Moving to AIP", gCurrentCardState,gNewCardState);
        //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
        //LOG_PRINT(INFO,"Moving to ACTIVE IN PROGRESSState ");
        gHandleMsgStart = I_TRUE;
        isAipRcvd = I_FALSE;
        isDbUnLockRcvd = I_FALSE;
        sendCellhRmAipResp();
        LOG_PRINT(INFO,"Msg sent to RM");
        RELEASE_MUTEX;
      }//if DbUnLockRcvd				 
      else
      {
        LOG_PRINT(INFO,"Wait For DbUnlock Ind from RM");				 
      }				
    }
    else
    {				
      gNewCardState = CARDSTATE_ACTIVE_IN_PROGRESS;
      gCurrentCardState = CARDSTATE_ACTIVE_IN_PROGRESS; 
      gNewCardState = CARDSTATE_INVALID;
      LOG_PRINT(INFO,"Moving from INSERVICE/StandBy->AIP");
      gHandleMsgStart = I_TRUE;
      RELEASE_MUTEX;
    }

  }

  /* ActiveInProgress -> Active */ 
  else if ( (param->cardState == CARDSTATE_ACTIVE) && (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) )
  {
    gNewCardState = CARDSTATE_ACTIVE;
    isBpmActRcvd = I_TRUE;
    if(isStandbyCard == I_TRUE)
    {
      if(isRmActRcvd == I_TRUE)
      {
        activeInProgressStateHandler();
        sendCellhRmActiveResp();

        LOG_PRINT(INFO,"Moving from AIP->ACTIVE");

      }				
      else
      {
        LOG_PRINT(INFO,"Wait For Act Ind From RM");				
      }				
    }
    else
    {				
      gNewCardState = CARDSTATE_ACTIVE;
      activeInProgressStateHandler();
      isStandbyCard = I_FALSE;
      LOG_PRINT(INFO,"Moving from AIP->ACTIVE.. ");
    }		
  }				

  /* StandBy -> Recovery */ 
  else if ( (param->cardState == CARDSTATE_RECOVERY) && (gCurrentCardState == CARDSTATE_STANDBY) )
  {
    gNewCardState = CARDSTATE_RECOVERY;
    gCurrentCardState = CARDSTATE_RECOVERY;
    gNewCardState = CARDSTATE_INVALID;
    LOG_PRINT(INFO,"Moving from StandBy to Recovery");
    isStandbyCard = I_FALSE; //Abis HA
    gHandleMsgStart = I_FALSE;
    RELEASE_MUTEX;
  }

#if 0
  /* Active -> StandBy */ 
  else if ( (param->cardState == CARDSTATE_STANDBY) && (gCurrentCardState == CARDSTATE_ACTIVE) )
  {
    gNewCardState = CARDSTATE_STANDBY;
    gCurrentCardState = CARDSTATE_STANDBY;
    gNewCardState = CARDSTATE_INVALID;
    gHandleMsgStart = I_FALSE;
    LOG_PRINT(INFO,"Moving from Active to Standby");
    RELEASE_MUTEX;
  }
#endif
  /* Active -> Recovery */
  //R2.9 changes start
  else if ( (param->cardState == CARDSTATE_RECOVERY) && (gCurrentCardState == CARDSTATE_ACTIVE) )
  {
    //R2.9 changes end
    gNewCardState = CARDSTATE_RECOVERY;
    instCountResult = GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER , &instCount);
    if ( instCountResult != INST_SUCCESS )
    {
      LOG_PRINT(MAJOR,"[ENV] GetInstCount Db call failed.. ");
      return;
    }

    gSignalSent = getCountAllocatedInst ( instCount ); /* To track No. of Signal sent to Model */
    LOG_PRINT(INFO, "Signal Sent to Model:%d", gSignalSent);

    for ( instId = 1; instId <= instCount; instId++ )
    {
      findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
      LOG_PRINT(DEBUG,"findLclPidPtr Success lclPid=0x%x",(I_U32)lclPidPtr);
      if ( lclPidPtr != INVALID_LCL_PID_PTR ) 
      {
        rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
        S = xGetSignal( sig_CELLH_INT_SELFCARD_STATE_CHANGE, rcvr, xEnv);
        (((yPDP_sig_CELLH_INT_SELFCARD_STATE_CHANGE)S)->Param1) = gCurrentCardState;
        (((yPDP_sig_CELLH_INT_SELFCARD_STATE_CHANGE)S)->Param2) = gNewCardState;
        SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
        signalSentToModel = I_TRUE;
      }
    }
    gInvocation = param->invocation;
    if ( signalSentToModel == I_FALSE )
    {
      activeStateHandler();
    }
    LOG_PRINT(INFO,"Moving from Active to Recovery..");
  }
  /* Recovery -> InService */
  else if ( (param->cardState == CARDSTATE_IN_SERVICE) && (gCurrentCardState == CARDSTATE_RECOVERY) )
  {
    gNewCardState = CARDSTATE_IN_SERVICE;
    /* DeRegister with DB */
    if ((result = dbDestroy()) != DBLIB_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"clib_destroy failed for CELLH(Error = %d)",result);
      return;
    }

    LOG_PRINT(DEBUG,"Registering with DB Server...");
    result = dbConnect();
    if ( result != DBLIB_SUCCESS )
    {
      LOG_PRINT(CRITICAL,"CELLHandler: Unable to Register itself with DBServer:Exiting");
      return;
    }
    LOG_PRINT(DEBUG,"Successfully Registered with DB Server.");
    gCurrentCardState = CARDSTATE_IN_SERVICE;
    gNewCardState = CARDSTATE_INVALID;
    gHandleMsgStart = I_FALSE;
    RELEASE_MUTEX;
    LOG_PRINT(INFO,"Moving to Recovery to InService.. ");
  }

  else if ( (param->cardState == CARDSTATE_DIAGNOSTIC) || (param->cardState == CARDSTATE_UPGRADE) || (param->cardState == CARDSTATE_OUT_OF_SERVICE ) || (param->cardState == CARDSTATE_PLATFORM_INS ))
  {
    gCurrentCardState = param->cardState;
    RELEASE_MUTEX;
  }
  else if ( (param->cardState == CARDSTATE_IN_SERVICE) && (gCurrentCardState == CARDSTATE_DIAGNOSTIC) )
  {
    LOG_PRINT(INFO,"STATE TRANSITION DIAGNOSTIC->INSERVICE");
    gCurrentCardState = CARDSTATE_IN_SERVICE;
    gNewCardState = BSC_APP_CARDSTATE_INVALID;
    LOG_PRINT(DEBUG,"Relasing semaphore");
    RELEASE_MUTEX;
    LOG_PRINT(INFO,"Moving to InService.. ");
  }

  else
  {
    LOG_PRINT(INFO,"cardStateChangeHandler:Unexpected state rcvd  = %d",param->cardState) ;
  }
  LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d]", gCurrentCardState,gNewCardState) ; 

}
void CellhmBpmCallbackFunc (struct sAisParam *param)
{
  switch (param->messageId)
  {
    case BPM_HEALTHCHECK_MESSAGE:
      bpmRespondToAis (param->invocation, OK);
      break;

    case BPM_SELFCARD_STATE_CHANGE:
      /* CS4.0: Changes for HA Start*/
      LOCK_MUTEX;
      //LOG_PRINT(DEBUG, "CellhBpmCallbackFunc: MUTEX is Locked");
      cardStateChangeHandler(param);
      if ( LOCK_MUTEX_AND_WAIT != MUTEX_WAIT_COMPLETE )
      {
        //LOG_PRINT(INFO,"calling bpmRespondToAis.. ");
        bpmRespondToAis (param->invocation, OK);
        LOG_PRINT(INFO,"Moving to CARD_STATE: [%d]",param->cardState);
      }
      else
      {
        LOG_PRINT(CRITICAL,"MUTEX Wait Timed Out.. Not sending OK notification");
      }
      RELEASE_MUTEX;
      /* CS4.0: Changes for HA End*/
      break;

    case BPM_PEERCARD_STATE_CHANGE:
      LOG_PRINT(INFO, "CELLH:(Env):BPM_PEERCARD_STATE_CHANGE recd, No Action Taken");
      bpmRespondToAis (param->invocation, OK);
      break;

    case BPM_MSG_ACK_PEER_HEALTH_BAD:
      LOG_PRINT(INFO, "CELLH:(Env):BPM_MSG_ACK_PEER_HEALTH_BAD recd, Not Expected");
      break;

    case BPM_MSG_ACK_CONFIGURE:
      LOG_PRINT(INFO, "CELLH:(Env):BPM_MSG_ACK_CONFIGURE recd");
      break;

    case BPM_MSG_ACK_CONFIGURE_RESET:
      LOG_PRINT(INFO, "CELLH:(Env):BPM_MSG_ACK_CONFIGURE_RESET recd, No Action Taken");
      break;

    case BPM_SHUTDOWN:
      LOG_PRINT(INFO, "CELLH:(Env):BPM_SHUTDOWN recd, Exiting");
      exit (1);
      break;

    default:
      LOG_PRINT(MAJOR, "CELLH:(Env):Unexpected msg from BPM: %d", param->messageId);
      break;
  }
}



I_Void activeInProgressStateHandler()
{
  LtrxTableApi             *ltrxTablePtr = NULL;
  LtrxTableApi             *ltrxTempPtr = NULL;
  LtrxTableIndices          ltrxIndices; 
  BaIndCellTableApi        *baIndTablePtr = NULL;
  BaIndCellTableApi        *baIndTempPtr = NULL;
  BaIndCellTableIndices     baIndIndices;
  I_U32                     outCount = ZERO;
  I_U16                     outSize = ZERO;
  I_S32                     retCode = ZERO;
  I_S32                     retVal = ZERO;
  I_U32                     lclPidPtr = INVALID_LCL_PID_PTR ;
  I_U32                     instId = INVALID_INST_ID ;
  I_U32                     index = ZERO;
  I_S8                      instCountResult = ZERO;
  I_U16                     instCount = ZERO;
  SDL_Pid                   rcvr;
  xSignalNode               S;
  I_U32       								refId = 0; 
  I_U32       								refId2 = 0; 
  CellhSwitchOverContextTableApi *ptrCellhSwitchOverContextTableApi=NULL;
  CellPerTableApi *ptrCellPerTableApi=NULL;
  I_U32											noOfRows=0;
  I_U16											rowSize=0;
  I_U16 											i= 0;
  CellhSwitchOverContextTableApi *tmpPtrCellhSwitchOverContextTableApi=NULL;
  CellPerTableApi *tmpPtrCellPerTableApi=NULL;
  I_S32 res;
  CellPerTableApi *cntxtCellTblRec;
  CellPerTableIndices *cntxtCellTblIndices;
  I_U32 chkresult=0;
  I_U32 cellAdminState=0;
  I_U32 bssAdminState=0;
  LtrxTableApi *ltrxList=NULL;
  I_U32 noOfLtrxs=0;
  I_U16 indx=0;
  I_U16 recSize; 
  I_S32 dbResult;
  LtrxTableApi *tmpPtr;
  LtrxTableIndices ltrxIndices1 ;

  selfEntIdG = (int)ENT_OAMS_CELLH;
  rcvr.GlobalNodeNr = (I_S32)selfEntIdG;

  //if ( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) &&  (gNewCardState = CARDSTATE_ACTIVE) )
  if ( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) &&  (gNewCardState = CARDSTATE_ACTIVE) && isStandbyCard == I_FALSE )  //Abis HA
  {
    retCode = getallBaIndCellTable( &baIndTablePtr, &outCount, &outSize);
    if ( retCode != CLIB_SUCCESS )
    {
      LOG_PRINT(LOG_INFO,"activeInProgressStateHandler: No Data is Populated in BaIndTable.");
    }
    /* Cleaning Transient table BaIndCellTable */
    else
    {
      for ( index=0; index<outCount; index++ )
      {
        baIndTempPtr = (BaIndCellTableApi *)((I_U8 *)(baIndTablePtr) + index*outSize);
        baIndIndices.cellId = baIndTempPtr->cellId;
        baIndIndices.lac    = baIndTempPtr->lac;

        if ((deleteBaIndCellTable(&baIndIndices)) != CLIB_SUCCESS)
        {
          LOG_PRINT(CRITICAL,"deleteBaIndCellTable failed for CellId:%d Lac:%d",baIndIndices.cellId,baIndIndices.lac); 
        }
      }
      free(baIndTablePtr);
    }
    retCode = getallLtrxTable( &ltrxTablePtr, &outCount, &outSize);
    if ( retCode != CLIB_SUCCESS )
    {
      LOG_PRINT(LOG_INFO,"activeInProgressStateHandler: No LTRX is Populated in DB");
    }
    /* Cleaning Transient table LtrxTable */
    else
    {
      for ( index=0; index<outCount; index++ )
      {
        ltrxTempPtr = (LtrxTableApi *)((I_U8 *)(ltrxTablePtr) + index*outSize);
        ltrxIndices.ltrxId = ltrxTempPtr->ltrxId;
        if ((deleteLtrxTable(&ltrxIndices)) != CLIB_SUCCESS)
        {
          LOG_PRINT(CRITICAL,"deleteLtrxTable failed for LtrxId: %d",ltrxIndices.ltrxId); 
        }
      }
      free(ltrxTablePtr);
    }
    instCountResult = GetInstCount(ENT_OAMS_CELLH, CELLHM_HANDLER , &instCount);
    if ( instCountResult != INST_SUCCESS )
    {
      LOG_PRINT(MAJOR,"[ENV]GetInstCount Db call failed.. ");
      return;
    }

    if ( gInstancesCreated == I_FALSE )
    {
      InitInstMap(ENT_OAMS_CELLH,CELLHM_HANDLER);
      /* Sending internal signal to system class for creating tau instances */
      LOG_PRINT(INFO,"activeInProgressStateHandler:Send signal CELLH_INT_ADD_TAU_INSTANCE to model"); 
      gSignalSent = instCount;
      //LOG_PRINT(INFO, "gSignalSent: %d", gSignalSent);
      rcvr.LocalPId = (xLocalPIdNode)gLclPidActiveClass;
      S = xGetSignal( sig_CELLH_INT_ADD_TAU_INSTANCE, rcvr, xEnv);
      SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
    }
    else
    {
      for ( instId = 1; instId <= instCount; instId++ )
      {
        findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
        LOG_PRINT(DEBUG,"findLclPidPtr Success lclPid=0x%x",(I_U32)lclPidPtr);
        if ( lclPidPtr != INVALID_LCL_PID_PTR ) 
        {
          if ((retVal = FreInstId(lclPidPtr, ENT_OAMS_CELLH, CELLHM_HANDLER)) != INST_SUCCESS)
          {
            LOG_PRINT(CRITICAL, "activeInProgressStateHandler: FreeInstId() Failed lclPidPtr = 0x%x [Act Cls Id = %d], [errCode =%d]",lclPidPtr, CELLHM_HANDLER,retVal);
            return;
          }
          else
          {
            LOG_PRINT(DEBUG,"activeInProgressStateHandler: FreeInstId() Success lclPidPtr = 0x%x [Act Cls Id = %d]",lclPidPtr, CELLHM_HANDLER);
          }
        }
        else
        {
          LOG_PRINT(INFO,"activeInProgressStateHandler: Instance is Created and is in FREE State...");
        }
      }
      gCurrentCardState = gNewCardState; 
      gNewCardState = CARDSTATE_INVALID;
      LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d]", gCurrentCardState,gNewCardState) ; 
      //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
      RELEASE_MUTEX;
      isRmActRcvd = I_FALSE;
      isBpmActRcvd = I_FALSE;
      LOG_PRINT(INFO,"Moving to ACTIVE State");
    }
  }
  else if ( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) &&  (gNewCardState = CARDSTATE_ACTIVE) && isStandbyCard == I_TRUE )  //Abis HA
  {
    LOG_PRINT(INFO,"Enter AIP->Active,flag=TRUE");

    if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)			 
    {
      LOG_PRINT(INFO,"Error in fetching BSC Admin State");			
    }				
    if(bssAdminState == UNLOCKED)		
    {	

      res = getallCellPerTable(&ptrCellPerTableApi,&noOfRows,&rowSize);
      if(res != CLIB_SUCCESS)
      {
        LOG_PRINT(INFO,"No Cell in DB. Moving from INSERVICE/StandBy->AIP");

      } //if res
      else
      {					
        LOG_PRINT(INFO,"Entered AIP,send INT MSG noOfRows=%d",noOfRows);
        for(i=0; i<noOfRows; i++)
        {			 
          tmpPtrCellPerTableApi  = (CellPerTableApi *)((I_U8*)(ptrCellPerTableApi) + i*rowSize);

          /*Read the Replicated context for CellId and Lac  in for loop*/				

          refId = tmpPtrCellPerTableApi->cellId;//From Replicated context
          refId2= tmpPtrCellPerTableApi->lac;   //From Replicated context
          LOG_PRINT(INFO,"CELLH:(Env):Prepare PREP_SYS_INFO_SWITCHOVER msg for CellId[%d]Lac[%d]",refId,refId2); 

          cellAdminState = tmpPtrCellPerTableApi->adminState;

          if(cellAdminState == 1)	
          {				
            LOG_PRINT(INFO,"Search Inst for CellId=%d Lac=%d",tmpPtrCellPerTableApi->cellId,tmpPtrCellPerTableApi->lac);	
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              //LOG_PRINT(CRITICAL,"CELLH:(Env):Unable to find instance...\n") ;
              gCurrentCardState = gNewCardState;
              gNewCardState = CARDSTATE_INVALID;
              LOG_PRINT(INFO,"Unable to find Inst.CurrentCardState[%d]NewCardState[%d]", gCurrentCardState,gNewCardState) ;
              //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
              //LOG_PRINT(INFO,"Moving to ACTIVE IN PROGRESS State ");
              gHandleMsgStart = I_TRUE;

              RELEASE_MUTEX;
              return ;

            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found..\n");
              continue;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            LOG_PRINT(INFO,"CELLH:(Env):LclPdPtr[%d]",lclPidPtr)
                                        /* Send this Message into TAU model */
                                        S = xGetSignal( sig_CELLH_INT_PREP_SYS_INFO_SWITCHOVER, rcvr, xEnv);
            (((yPDP_sig_CELLH_INT_PREP_SYS_INFO_SWITCHOVER)S)->Param1) = tmpPtrCellPerTableApi->cellId;
            (((yPDP_sig_CELLH_INT_PREP_SYS_INFO_SWITCHOVER)S)->Param2) = tmpPtrCellPerTableApi->lac;
            SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );	
          }//cellAdminState=1
          else
          {
            LOG_PRINT(INFO,"Cell Locked-Find all Ltrx For Cell");		
            dbResult=getAllLtrxForCellH(tmpPtrCellPerTableApi->cellId,tmpPtrCellPerTableApi->lac,&ltrxList,&noOfLtrxs,&recSize);
            if(dbResult == CLIB_SUCCESS)
            {
              LOG_PRINT(INFO,"No of Ltrx Found=%d",noOfLtrxs);			
              for(indx=0;indx < noOfLtrxs; indx++)			
              {

                tmpPtr = (I_U8*)ltrxList + (indx * recSize);
                dbResult = updatePtrxMappingStatus(tmpPtr->ptrxId, UNMAPPED) ;	
                if(dbResult != CLIB_SUCCESS)
                {
                  LOG_PRINT(INFO,"update PtrxTable failed");				 
                }				 

                ltrxIndices1.ltrxId = tmpPtr->ltrxId;
                dbResult = deleteLtrxTable(&ltrxIndices1);	
                if(dbResult != CLIB_SUCCESS)
                {
                  LOG_PRINT(INFO,"Ltrx Table deletion failed");				
                }

              }				
              free(ltrxList);

            }				
            else
            {
              LOG_PRINT(INFO,"No Ltrx present for cell");				
            }				


          }//else cell locked				

        }//for
        free(ptrCellPerTableApi);
      }//else	
    }//BscAdmin	
    gCurrentCardState = gNewCardState;
    gNewCardState = CARDSTATE_INVALID;
    //LOG_PRINT(INFO,"CurrentCardState: [%d]", gCurrentCardState) ;
    //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
    isRmActRcvd = I_FALSE;
    isBpmActRcvd = I_FALSE;
    RELEASE_MUTEX;
    LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d].Moving to ACTIVE State",gCurrentCardState,gNewCardState);


  }				 
  else
    LOG_PRINT(MAJOR,"Unexpected State change notification received");
}  


I_Void  activeStateHandler()
{
  gCurrentCardState = gNewCardState;
  gNewCardState = CARDSTATE_INVALID;
  gHandleMsgStart = I_FALSE;
  RELEASE_MUTEX;
}

I_Void findLclPidPtr ( I_U32 instId, I_U8 classId, I_U32 *lclPidPtr, I_U8 entId)
{
  I_S32 retCode       = ZERO;
  I_S32 localInstId   = ZERO;
  InstMapTbl          instMapTblPtr;

  LOG_PRINT(INFO,"Find LclPidPtr for class:%d", classId);
  retCode = GetRowFrmInstId ( &instMapTblPtr, (I_S32)instId, entId, classId);
  if ( retCode != INST_SUCCESS )
  {
    LOG_PRINT(MAJOR,"[ENV]GetRowFrmInstId Db call failed.. ");
    *lclPidPtr = INVALID_LCL_PID_PTR;
    return;
  } 
  if (  instMapTblPtr.status  == INST_FREE )
  {
    LOG_PRINT(INFO,"[ENV]Instance is not allocated.. ");
    *lclPidPtr = INVALID_LCL_PID_PTR;
    return;
  }
  retCode = SearchAlocatedInst( lclPidPtr, &localInstId,  entId, classId, instMapTblPtr.refId1, instMapTblPtr.refId2,                                   instMapTblPtr.refId3, instMapTblPtr.refId4, instMapTblPtr.refId5);
  if ( ( retCode != INST_SUCCESS ) )
  {
    *lclPidPtr = INVALID_LCL_PID_PTR;
  } 
}

I_U32 getCountAllocatedInst ( I_U16 instCount )
{
  I_U32 instId = ZERO;
  I_U32 count = ZERO;
  I_U32 lclPidPtr  = INVALID_LCL_PID_PTR ;

  //LOG_PRINT(INFO,"Entering getCountAllocatedInst");
  for ( instId = 1; instId <= instCount; instId++ )
  {
    findLclPidPtr ( instId, CELLHM_HANDLER, &lclPidPtr, (I_U8)ENT_OAMS_CELLH );
    if ( lclPidPtr != INVALID_LCL_PID_PTR )
    {
      count++;
    }
  }
  LOG_PRINT(INFO,"Total Allocated Instance[%d]",count);
  //LOG_PRINT(INFO," Exiting getCountAllocatedInst");
  return count;
}

/* CS4.0: Changes for HA End */
/********************************************************************/


I_U32 GetRefId(I_Void *rcvPtr , I_U32 * refId2)
{
  /* Logic for getting the CEllID from the Incoming Message needs to be writen here.*/

  SysHdr      *sysHdr ;
  I_U16       msgType ;
  I_U32       refId = 0 ;
  sysHdr = (SysHdr *)rcvPtr ;
  msgType = sysHdr->msgType ;
  switch(msgType)
  {
    case OAMS_TRXH_CELLH_BCCH_AVAIL:
      refId = ((OamsTrxhCellhBcchAvail *)rcvPtr)->cellId ;
      *refId2 = ((OamsTrxhCellhBcchAvail *)rcvPtr)->lac ;
      break ;
    case OAMS_TRXH_CELLH_BCCH_UNAVAIL:
      refId = ((OamsTrxhCellhBcchUnAvail *)rcvPtr)->cellId ;
      *refId2 = ((OamsTrxhCellhBcchUnAvail *)rcvPtr)->lac ;
      break ;
    case OAMS_TRXH_MAPENT_INITIATE_MAP:
      break ;
    case OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP:
      refId = ((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->cellId ;
      *refId2 = ((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->lac ;
      break ;
    case OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED:
      refId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed *)rcvPtr)->cellId ;
      *refId2 = ((OamsTrxhMapentCreLtrxPtrxMappingFailed *)rcvPtr)->lac ;
      break ;
    case OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP:
      refId = ((OamsTrxhMapentDelLtrxPtrxMappingResp *)rcvPtr)->cellId ;
      *refId2 = ((OamsTrxhMapentDelLtrxPtrxMappingResp *)rcvPtr)->lac ;
    case OAMS_CFG_CELLH_UNLOCK_REQ:
      refId = ((OamsCfgCellhUnlockReq *)rcvPtr)->objId ;
      *refId2 = ((OamsCfgCellhUnlockReq *)rcvPtr)->lac ;
      break ;
    case OAMS_CFG_CELLH_LOCK_REQ:
      refId = ((OamsCfgCellhLockReq *)rcvPtr)->objId ;
      *refId2 = ((OamsCfgCellhLockReq *)rcvPtr)->lac ;
      break ;
    case OAMS_CFG_CELLH_CELL_BAR_ACCESS:
      refId = ((OamsCfgCellhCellBarAccess *)rcvPtr)->cellId ;
      *refId2 = ((OamsCfgCellhCellBarAccess *)rcvPtr)->lac ;
      break ;
    case OAMS_CFG_CELLH_BLOCK_IND:
      refId = ((OamsCfgCellhBlockInd *)rcvPtr)->objId ;
      *refId2 = ((OamsCfgCellhBlockInd *)rcvPtr)->lac ;
      break ;
    case OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE:
      refId = ((OamsCfgCellhCsNeighCellsChange *)rcvPtr)->cellId ;
      *refId2 = ((OamsCfgCellhCsNeighCellsChange *)rcvPtr)->lac ;
      break ;
    case OAMS_MAPENT_CELLH_DEL_MAP_RESP:
      refId = ((OamsMapentCellhDelMapResp *)rcvPtr)->cellId ;
      *refId2 = ((OamsMapentCellhDelMapResp *)rcvPtr)->lac ;
      break ;
    case OAMS_TRXH_CELLH_SEND_SACCH_INFO:
      refId = ((OamsTrxhCellhSendSacchInfo *)rcvPtr)->cellId ;
      *refId2 = ((OamsTrxhCellhSendSacchInfo *)rcvPtr)->lac ;
      break ;
      /* PCU Rel 2.5 Changes : Starts */
    case OAMS_PSCH_CELLH_PS_CELL_ENABLED:
      refId = ((OamsPschCellhPsCellEnabled *)rcvPtr)->cellId ;
      *refId2 = ((OamsPschCellhPsCellEnabled *)rcvPtr)->lac ;
      break ;
    case OAMS_PSCH_CELLH_PS_CELL_DISABLED:
      refId = ((OamsPschCellhPsCellDisabled *)rcvPtr)->cellId ;
      *refId2 = ((OamsPschCellhPsCellDisabled *)rcvPtr)->lac ;
      break ;
      /* PCU Rel 2.5 Changes : Ends */
      /* CS4.0 : Abis E1 Lock/Unlock Changes : Starts */
    case OAMS_CFG_CELLH_E1_UNLOCK_REQ:
      refId = ((OamsCfgCellhAbisE1UnlockReq *)rcvPtr)->objId ;
      *refId2 = ((OamsCfgCellhAbisE1UnlockReq *)rcvPtr)->lac ;
      break ;
    case OAMS_CFG_CELLH_E1_LOCK_REQ:
      refId = ((OamsCfgCellhAbisE1LockReq *)rcvPtr)->objId ;
      *refId2 = ((OamsCfgCellhAbisE1LockReq *)rcvPtr)->lac ;
      break ;
      /* CS4.0 : Abis E1 Lock/Unlock Changes : Ends */
    case CSAPP_CBSH_CELLH_CBCH_SI_MODIFY_REQ:
      refId = ((CsappCbshCellhSIMOdifyReq *)rcvPtr)->ci;
      *refId2 = ((CsappCbshCellhSIMOdifyReq *)rcvPtr)->lac ;
      break ;
    case OAMS_TRXH_CELLH_OPR_STATE_IND:
      refId = ((OamsTrxhCellhOprStateInd *)rcvPtr)->cellId;
      *refId2 = ((OamsTrxhCellhOprStateInd *)rcvPtr)->lac ;
      break;	
    default:
      refId = 0;
      *refId2 = 0;
  }
  return refId ;
}
/* R2.4 Changes Start */
I_Void PrepareOamsCellhCfgAlarmInd(I_U32 cellId, I_U16 lac, I_U32 alarmId, I_U32 alarmLevel, I_U8 alarmString[])
{
  I_U32 msgSize;
  I_U32 retCode = OAMS_SUCCESS;
  I_PVoid sndMsgPtr = NULL;

  msgSize = sizeof(OamsCellhCfgAlarmInd);
  OamsCellhCfgAlarmInd *msgPtr = NULL;
  sndMsgPtr = (I_PVoid)AlocMsgBuf(msgSize);
  msgPtr = (OamsCellhCfgAlarmInd *)sndMsgPtr;

  if (sndMsgPtr == NULL)
  {
    LOG_PRINT(CRITICAL,"(ENV):Errror in Allocating memory");
    retCode = OAMS_FAILURE;
    return ;
  }

  FILL_SYS_HDR(msgPtr , OAMS_CELLH_CFG_ALARM_IND, MSG_SUB_TYPE, PRCR_CP, ENT_OAMS_CELLH, ZERO , PRCR_CP, ENT_OAMS_CFG, ZERO); 

  msgPtr->sysAlarm.sysalarmId = alarmId;
  msgPtr->sysAlarm.alarmSeqNo = ZERO;
  msgPtr->sysAlarm.alarmTime = ZERO;
  msgPtr->sysAlarm.alarmLevel = alarmLevel;
  msgPtr->sysAlarm.info3 = OAMS_OBJTYPE_CELL;
  msgPtr->sysAlarm.key1 = lac;
  msgPtr->sysAlarm.key2 = cellId;

  strcpy(msgPtr->sysAlarm.infoString,alarmString);
  strcat(msgPtr->sysAlarm.infoString,"\0");   
  msgPtr->sysAlarm.infoStrLen = strlen(msgPtr->sysAlarm.infoString);
  LOG_PRINT(INFO,"(ENV): Alarm String(len=%d) Sent- %s",msgPtr->sysAlarm.infoStrLen,msgPtr->sysAlarm.infoString);
  if (SendMsg((I_PVoid)sndMsgPtr,MSG_ORD_PRIO,msgSize) == SND_FAIL)
  {
    LOG_PRINT(CRITICAL,"[ENV:]Sending failed of OAMS_CELLH_CFG_ALARM_IND");
    return ;
  }
  return ;
}
/* R2.4 Changes End */


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

  I_S32         retVal;
  I_U8          appId;
  I_U8          *appName;
  I_S32         result;
  selfEntIdG = (int)ENT_OAMS_CELLH;

#ifdef XTRACE
  xPrintString("CELLH:(Env):xInitEnv called\n");
#endif

  LOG_PRINT(INFO,"CELLH:(Env):Registering with BPM");
  //RegisterCellhmWithBpm();CLOUD

  LOG_PRINT(INFO,"CELLH:(Env):Register with IPC FramWork");
  if (RegisterWithIpcFrmwrk(selfEntIdG, (I_S8 *)"ENT_OAMS_CELLH") < 0)
  {
    LOG_PRINT(CRITICAL,"CELLH:(Env):Unable to Register itself with IPC FrameWork : Exiting");
    exit(0) ;
  }
  RegisterCellhmWithBpm();
  reg_sig_hndlr();
  INIT_MUTEX;
  LOG_PRINT(INFO, "Mutex Intialized**SystemName=%s,ModuleName=%s,Version=%s**CurrentCardState=%d,NewCardState=%d",SYSTEM_NAME,SELF_ENTITY_NAME,VERSION,gCurrentCardState,gNewCardState);

#if 0
  LOG_PRINT(INFO,"CELLH:(Env):Registering with DB Server...\n");
  result = dbConnect();

  if (result != DBLIB_SUCCESS)
  {
    LOG_PRINT(CRITICAL,"CELLH:(Env):Unable to Register itself with DBServer:Exiting");
    exit(0) ;
  }
  LOG_PRINT(INFO,"CELLH:(Env):Successfully Registered with DB Server.\n");
  LOG_PRINT(INFO,"CELLH:(Env):Initializing Inst Map Table...\n");

  InitInstMap(ENT_OAMS_CELLH,CELLHM_HANDLER);

  /* retVal=SetInstCount(ENT_OAMS_CELLH,CELLHM_HANDLER,MAX_CELLHM_INST);  */
  LOG_PRINT(CRITICAL,"CELLH:(Env):CELLH Process Initialized Successfully\n") ;
#endif
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
  I_S32 retVal;

  /* DeRegister with DB */
  if ((retVal = dbDestroy()) != DBLIB_SUCCESS)
  {
    LOG_PRINT(CRITICAL,"CELLH:(Env):clib_destroy failed for CELLH (Error = %d)",retVal);
    exit(0);
  }/*if retVal */

#ifdef XTRACE
  xPrintString("CELLH:(Env):xCloseEnv called\n");
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
  I_Void  *sndPtr     = NULL;
  I_S32   msgSize     = 0;
  I_U32   lclPidPtr   = INVALID_LCL_PID_PTR;
  I_S32   retVal      = 0;
  I_U16   msgType     = 0;
  I_U8    actClsId    = INVALID_LCL_PID_PTR;
  I_U16   invocationMode;

#ifdef XTRACE
#ifdef XIDNAMES
  char  Temp[100];
  sprintf(Temp, "CELLH:(Env):xOutEnv:  %s has been rcvd by env\n",(*SignalOut)->NameNode->Name );
  xPrintString(Temp);
#else
  xPrintString("CELLH:(Env):xOutEnv:  One signal has been rcvd by env\n");
#endif
#endif

  switch((*SignalOut)->NameNode->SignalNumber)
  {
    /* PCU Rel2.5 Changes : Starts */
    case SN_OAMS_CELLH_GRHM_CRE_CELL_MAP_IND:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_GRHM_CRE_CELL_MAP_IND)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_GRHM_CRE_CELL_MAP_IND)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
    case SN_OAMS_CELLH_GRHM_DEL_CELL_MAP_IND:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_GRHM_DEL_CELL_MAP_IND)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_GRHM_DEL_CELL_MAP_IND)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
    case SN_OAMS_CELLH_GRHM_CRS_IND:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_GRHM_CRS_IND)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_GRHM_CRS_IND)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
    case SN_OAMS_CELLH_PSMSH_ADD_BCCH_TRX_INFO:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_PSMSH_ADD_BCCH_TRX_INFO)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_PSMSH_ADD_BCCH_TRX_INFO)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
    case SN_OAMS_CELLH_PSMSH_DEL_BCCH_TRX_INFO:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_PSMSH_DEL_BCCH_TRX_INFO)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_PSMSH_DEL_BCCH_TRX_INFO)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module, Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
    case SN_OAMS_CELLH_TRXH_UPDATE_PS_CELL_ATTR:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_TRXH_UPDATE_PS_CELL_ATTR)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_TRXH_UPDATE_PS_CELL_ATTR)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
      /* PCU Rel2.5 Changes : Ends */
      /* CS4.0 : Abis E1 Lock/Unlock Changes : Starts */
    case SN_OAMS_CELLH_CFG_E1_LOCK_RESP:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_CFG_E1_LOCK_RESP)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_CFG_E1_LOCK_RESP)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }

    case SN_OAMS_CELLH_CFG_E1_UNLOCK_RESP:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_CFG_E1_UNLOCK_RESP)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_CFG_E1_UNLOCK_RESP)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
      /* CS4.0 : Abis E1 Lock/Unlock Changes : Ends */

      /* CS3.0 : On The Fly Related Changes : Starts */
    case SN_OAMS_CELLH_MRHM_CSNEIGHCELLS_CHANGE:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_MRHM_CSNEIGHCELLS_CHANGE)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_MRHM_CSNEIGHCELLS_CHANGE)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }
      /* CS3.0 : On The Fly Related Changes : Ends */

    case SN_OAMS_CELLH_ABIHM_BCCH_INFO:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_ABIHM_BCCH_INFO)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_ABIHM_BCCH_INFO)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM........\n");
          xReleaseSignal(SignalOut);
          return ;
        }
        LOG_PRINT(INFO,"CELLH:(Env):Send OAMS_CELLH_ABIHM_BCCH_INFO Signal::msgSize=%d msgType=0x%x",msgSize , ((SysHdr *)sndPtr)->msgType);
        break;
      }

    case SN_OAMS_CELLH_ABIHM_SACCH_FILL:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_ABIHM_SACCH_FILL)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_ABIHM_SACCH_FILL)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module, Returning without Sending to FRM........\n");
          xReleaseSignal(SignalOut);
          return ;
        }
        LOG_PRINT(INFO,"CELLH:(Env):Send OAMS_CELLH_ABIHM_SACCH_FILL Signal::msgSize=%d msgType=0x%x",msgSize , ((SysHdr *)sndPtr)->msgType);
        break;
      }

    case SN_OAMS_CELLH_CFG_ALARM_IND:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_CFG_ALARM_IND)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_CFG_ALARM_IND)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }

    case SN_OAMS_CELLH_CFG_LOCK_RESP:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_CFG_LOCK_RESP)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_CFG_LOCK_RESP)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }

    case SN_OAMS_CELLH_CFG_UNLOCK_RESP:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_CFG_UNLOCK_RESP)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_CFG_UNLOCK_RESP)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module,Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        break;
      }

    case SN_OAMS_CELLH_MAPENT_CRE_MAP_REQ:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_MAPENT_CRE_MAP_REQ)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_MAPENT_CRE_MAP_REQ)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL ptr from Module, Returning without Sending to FRM");
          xReleaseSignal(SignalOut);
          return ;
        }
        invocationMode = ((SysHdr *)sndPtr)->msgType;
        //LOG_PRINT(INFO,"CELLH:(Env):Before Invoking MappingLtrxPtrxEntity function");
        MappingLtrxPtrxEntity(invocationMode,sndPtr);
        xReleaseSignal(SignalOut);
        return;
      }

    case SN_OAMS_CELLH_MAPENT_DEL_MAP_REQ:
      {
        sndPtr = ((yPDP_sig_OAMS_CELLH_MAPENT_DEL_MAP_REQ)(*SignalOut))->Param1;
        msgSize = ((yPDP_sig_OAMS_CELLH_MAPENT_DEL_MAP_REQ)(*SignalOut))->Param2;
        if (sndPtr == NULL)
        {
          LOG_PRINT(INFO,"CELLH:(Env):Rcvd NULL pointer from Module, Returning without Sending to FRM........\n");
          xReleaseSignal(SignalOut);
          return ;
        }
        invocationMode = ((SysHdr *)sndPtr)->msgType;
        MappingLtrxPtrxEntity(invocationMode,sndPtr);
        xReleaseSignal(SignalOut);
        return;
      }

    case SN_OAMS_ADD_TAU_INST_IN_INSTMAP :
      LOG_PRINT(INFO,"CELLH:(Env):Rcvd OAMS_ADD_TAU_INST_IN_INSTMAP");
      actClsId = 1 ;
      lclPidPtr = (I_U32)((*SignalOut)->Sender.LocalPId);
      if ((retVal = AddTauInst(lclPidPtr,ENT_OAMS_CELLH, actClsId)) < 0)
      {
        LOG_PRINT(CRITICAL, "CELLH:(Env):xOutEnv:AddTauInstId() Failed lclPidPtr=0x%x[ActClsId=%d]",lclPidPtr, actClsId);
      }
      else
      {
        LOG_PRINT(INFO, "CELLH:(Env):xOutEnv:AddTauInstId() Succ lclPidPtr=0x%x[ActClsId=%d]",lclPidPtr, actClsId);
        /* CS4.0: HA changes start */
        gSignalSent--;
        LOG_PRINT(INFO, "gSignalSent: %d", gSignalSent);
        if ( gSignalSent == 0 && gInstancesCreated == I_FALSE )
        {
          //gCurrentCardState = gNewCardState; 
          gNewCardState = CARDSTATE_INVALID;
          gInstancesCreated = I_TRUE;
          LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d]", gCurrentCardState,gNewCardState); 
          if(gCurrentCardState == CARDSTATE_STANDBY)  //Abis HA
          {				
            LOG_PRINT(INFO,"Moving to STANDBY State..");
            isStandbyCard = I_TRUE;		 //Abis HA	
          }
          else
          {
            gCurrentCardState = CARDSTATE_IN_SERVICE; 
            LOG_PRINT(INFO,"Moving to INSERVICE State..");
          }
          RELEASE_MUTEX;
        }
        /* CS4.0: HA changes End */              
      }
      xReleaseSignal(SignalOut);
      return;

    case SN_OAMS_FREE_INST :
      actClsId = 1 ;
      lclPidPtr = (I_U32)((*SignalOut)->Sender.LocalPId);
      if ((retVal = FreInstId(lclPidPtr, ENT_OAMS_CELLH,actClsId)) < 0)
      {
        LOG_PRINT(CRITICAL, "CELLH:(Env):xOutEnv:FreeInstId() Failed lclPidPtr=0x%x[ActClsId=%d]",lclPidPtr, actClsId);
      }
      else
      {
        LOG_PRINT(INFO, "CELLH:(Env):xOutEnv:FreeInstId() Succ lclPidPtr=0x%x[ActClsId=%d]",lclPidPtr, actClsId);
      }
      xReleaseSignal(SignalOut);
      return;

      /* CS4.0: HA changes start */
    case SN_CELLH_INT_ACTIVE_CLASS_PID :
      gLclPidActiveClass = (I_U32)((*SignalOut)->Sender.LocalPId);
      LOG_PRINT(DEBUG, "xOutEnv:System class LCLPID: 0x%0x", gLclPidActiveClass);
      //LOG_PRINT(DEBUG," [ENV]LocalPid for active class is %d",gLclPidActiveClass);
      xReleaseSignal(SignalOut);
      return;

    case SN_CELLH_INT_SELFCARD_STATE_CHANGE_RESP :
      gSignalSent--;
      LOG_PRINT(DEBUG, "xOutEnv:Rcvd SN_CELLH_INT_SELFCARD_STATE_CHANGE_RESP. gSignalSent: %d",gSignalSent);
      if ( gSignalSent == 0 )
      {
        LOG_PRINT(INFO,"All instances goes to INIT State while going ACTIVE to INSERVICE/RECOVERY state. ");
        activeStateHandler();
      }
      xReleaseSignal(SignalOut);
      return;

      /* CS4.0: HA changes End */

      /* Default */
    default:
      {
        LOG_PRINT(INFO,"CELLH:(Env):Entered Default Case : xOutEnv \n");
        sndPtr = ((yPDP_sig_OAMS_CELLH_CFG_ALARM_IND)(*SignalOut))->Param1;
        if (sndPtr !=NULL)
        {
          DalocMsgBuf((I_Void *)sndPtr);
        }
        xReleaseSignal(SignalOut);
        return;
      }

  }/*switch*/

  //LOG_PRINT(INFO,"MsgOpCode = 0x%d ", ((SysHdr *)rcvPtr)->msgType);
  LOG_PRINT(INFO,"CELLH:(Env):OUT OF SWITCH XOUT::ENV \n ");
  if (SendMsg(sndPtr,MSG_ORD_PRIO,msgSize) == SND_FAIL)
  {
    LOG_PRINT(CRITICAL,"CELLH:(Env):MESSAGE SENDING FAILED \n");
    xReleaseSignal(SignalOut);
    return;
  }
  else
  {
    LOG_PRINT(INFO,"CELLH:(Env):Successfully sent message out \n");
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
  xPrintString( "CELLH:(Env):xInEnv: Called!\n");
#endif
#endif
  I_Void        *rcvPtr;
  I_S32          msgSize;
  I_U32          refId;
  I_S32          instId;
  I_U16          msgType;
  I_U8           subType;
  SDL_Pid        rcvr;
  I_U32          lclPidPtr;
  I_U8           srcEntity;
  I_U8           dstEntity;
  I_S32          srcInst;
  I_U32          refId2;
  I_U16          invocationMode;
  I_U8           alarmString[100];

  struct sAisParam *param;
  if ((rcvPtr = (I_Void *)RecvMsg(selfEntIdG, &msgSize)) != NULL)
  {
    msgType = ((SysHdr *)rcvPtr)->msgType;
    subType = ((SysHdr *)rcvPtr)->subType;
    instId = ((SysHdr *)rcvPtr)->dest.inst;
    //LOG_PRINT(INFO,"CELLH:(Env):Msg Rcvd msgTyp=0x%x subTyp=%d",msgType,subType);
    rcvr.GlobalNodeNr = (I_S32)selfEntIdG;
    rcvr.LocalPId = (xLocalPIdNode)0;
    lclPidPtr = INVALID_LCL_PID_PTR;

    /* CS4.0: Changes for HA Start */
    if ( gHandleMsgStart == I_TRUE )
    {
      /* CS4.0: Changes for HA End */
      switch(msgType)
      {
        /* CS4.0 : Abis E1 Lock/Unlock Changes : Starts */
        case OAMS_CFG_CELLH_E1_UNLOCK_REQ:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_E1_UNLOCK_REQ Rcvd. CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_CFG_CELLH_E1_UNLOCK_REQ, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_E1_UNLOCK_REQ)S)->Param1) = rcvPtr;
            break;
          }

        case OAMS_CFG_CELLH_E1_LOCK_REQ:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_E1_LOCK_REQ Rcvd. CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for[cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_CFG_CELLH_E1_LOCK_REQ, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_E1_LOCK_REQ)S)->Param1) = rcvPtr;
            break;
          }

          /* CS4.0 : Abis E1 Lock/Unlock Changes : Ends */

          /* PCU Rel 2.5 Changes : Starts */
        case OAMS_PSCH_CELLH_PS_CELL_ENABLED:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):PSCH_CELLH_PS_CELL_ENABLED Rcvd. CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for[cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found...\n");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_PSCH_CELLH_PS_CELL_ENABLED, rcvr, xEnv);
            (((yPDP_sig_OAMS_PSCH_CELLH_PS_CELL_ENABLED)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_PSCH_CELLH_PS_CELL_DISABLED:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):PSCH_CELLH_PS_CELL_DISABLED Rcvd. CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for[cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found\n");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_PSCH_CELLH_PS_CELL_DISABLED, rcvr, xEnv);
            (((yPDP_sig_OAMS_PSCH_CELLH_PS_CELL_DISABLED)S)->Param1) = rcvPtr;
            break;
          }
          /* PCU Rel 2.5 Changes : Ends */

          /* CS3.0 : On The Fly Related Changes  : Starts */
        case OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_CSNEIGHCELLS_CHANGE Rcvd. CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for[cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE)S)->Param1) = rcvPtr;
            break;
          }
          /* CS3.0 : On The Fly Related Changes  : Ends */

        case OAMS_TRXH_CELLH_SEND_SACCH_INFO:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):TRXH_CELLH_SEND_SACCH_INFO Signal rcvd CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found...\n");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_TRXH_CELLH_SEND_SACCH_INFO, rcvr, xEnv);
            (((yPDP_sig_OAMS_TRXH_CELLH_SEND_SACCH_INFO)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_MAPENT_CELLH_DEL_MAP_RESP:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):MAPENT_CELLH_DEL_MAP_RESP Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found...\n");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_MAPENT_CELLH_DEL_MAP_RESP, rcvr, xEnv);
            (((yPDP_sig_OAMS_MAPENT_CELLH_DEL_MAP_RESP)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_CFG_CELLH_BLOCK_IND:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_BLOCK_IND Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found...\n");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_CFG_CELLH_BLOCK_IND, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_BLOCK_IND)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_CFG_CELLH_UNLOCK_REQ:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_UNLOCK_REQ Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (AlocNewInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS )
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Search for allocated instance") ;

              if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
              {
                LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
                DalocMsgBuf((I_Void *)rcvPtr);
                return;
              }
              if (lclPidPtr == 0)
              {
                LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
                DalocMsgBuf((I_Void *)rcvPtr);
                return ;
              }

            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            LOG_PRINT(INFO,"CELLH:(Env):Value of LclPidPtr[%d]",lclPidPtr)
                                        /* Send this Message into TAU model */
                                        S = xGetSignal( sig_OAMS_CFG_CELLH_UNLOCK_REQ, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_UNLOCK_REQ)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_CFG_CELLH_LOCK_REQ:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_LOCK_REQ Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_CFG_CELLH_LOCK_REQ, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_LOCK_REQ)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_CFG_CELLH_CELL_BAR_ACCESS:
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CFG_CELLH_CELL_BAR_ACCESS Signal Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_CFG_CELLH_CELL_BAR_ACCESS, rcvr, xEnv);
            (((yPDP_sig_OAMS_CFG_CELLH_CELL_BAR_ACCESS)S)->Param1) = rcvPtr;
            break;
          }
        case  OAMS_TRXH_CELLH_BCCH_AVAIL :
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):TRXH_CELLH_BCCH_AVAIL Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_TRXH_CELLH_BCCH_AVAIL, rcvr, xEnv);
            (((yPDP_sig_OAMS_TRXH_CELLH_BCCH_AVAIL)S)->Param1) = rcvPtr;
            break;
          }
        case  OAMS_TRXH_CELLH_BCCH_UNAVAIL :
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):TRXH_CELLH_BCCH_UNAVAIL Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_OAMS_TRXH_CELLH_BCCH_UNAVAIL, rcvr, xEnv);
            (((yPDP_sig_OAMS_TRXH_CELLH_BCCH_UNAVAIL)S)->Param1) = rcvPtr;
            break;
          } 

        case  OAMS_TRXH_MAPENT_INITIATE_MAP :
          {
            LOG_PRINT(INFO,"CELLH:(Env):TRXH_MAPENT_INITIATE_MAP(0x%x) Rcvd for TRXID(%d)",
                ((SysHdr *)rcvPtr)->msgType,((OamsTrxhMapentInitiateMap *)rcvPtr)->ptrxId);     
            /* Send this Message to MapEnt*/
            invocationMode = ((SysHdr *)rcvPtr)->msgType;
            MappingLtrxPtrxEntity(invocationMode,rcvPtr);   
            return;
          }

        case  OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP:
          {
            ChnGrpTableIndices apiChnGrpIndex;
            ChnGrpTableApi* chnGrpTblApiPtr = NULL;

            LOG_PRINT(INFO,"CELLH:(Env):Rcvd MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_RESP::msgType=0x%x",((SysHdr *)rcvPtr)->msgType);
            /* Send this Message to MapEnt*/
            invocationMode = ((SysHdr *)rcvPtr)->msgType;
            /* Changes for R2.4 start */
            //LOG_PRINT(DEBUG,"Received the message OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP");
            apiChnGrpIndex.chnGrpId =  ((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->chgrId;
            apiChnGrpIndex.cellId =  ((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->cellId;
            apiChnGrpIndex.lac = ((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->lac;
            LOG_PRINT(DEBUG,"chnGrpId:%d,cellId:%d,lac:%d", apiChnGrpIndex.chnGrpId,apiChnGrpIndex.cellId,apiChnGrpIndex.lac);
            if ( CLIB_SUCCESS == getChnGrpTable(&apiChnGrpIndex, &chnGrpTblApiPtr) )
            {
              LOG_PRINT(DEBUG,"BcchCcchSdcch4:%d,BcchCcch:%d",chnGrpTblApiPtr->bcchCcchSdcch4,chnGrpTblApiPtr->bcchCcch);
              if ( chnGrpTblApiPtr->bcchCcchSdcch4 >=1 || chnGrpTblApiPtr->bcchCcch >=1 )
              {
                sprintf(alarmString,"Cell with Lac - %d and CellId - %d is ENABLED",((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->lac, ((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->cellId);
                strcat(alarmString,"\0");
                PrepareOamsCellhCfgAlarmInd(((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->cellId,((OamsTrxhMapentCreLtrxPtrxMappingResp *)rcvPtr)->lac , ALARM_CELL_ENABLED,TRAP_SEVERITY_CLEARED,alarmString);
              }
              free(chnGrpTblApiPtr);
            }
            MappingLtrxPtrxEntity(invocationMode,rcvPtr);
            /* Changes for R2.4 End */
            return;
          }

        case  OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED :
          {
            LOG_PRINT(INFO,"CELLH:(Env):Rcvd TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED::msgType=0x%x",((SysHdr *)rcvPtr)->msgType);
            /* Send this Message to MapEnt */
            invocationMode = ((SysHdr *)rcvPtr)->msgType;
            MappingLtrxPtrxEntity(invocationMode,rcvPtr);
            return;
          }

        case  OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP :
          {
            LOG_PRINT(INFO,"CELLH:(Env):Rcvd TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP::msgType=0x%x",((SysHdr *)rcvPtr)->msgType);
            /* Send this Message to MapEnt */
            invocationMode = ((SysHdr *)rcvPtr)->msgType;
            MappingLtrxPtrxEntity(invocationMode,rcvPtr);
            return; 
          }
        case  CSAPP_CBSH_CELLH_CBCH_SI_MODIFY_REQ :
          {
            refId = GetRefId(rcvPtr,&refId2) ;
            LOG_PRINT(INFO,"CELLH:(Env):CBSH_CELLH_CBCH_SI_MODIFY_REQ Rcvd for CellId[%d]Lac[%d]",refId,refId2); 
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for[cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found.");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
            /* Send this Message into TAU model */
            S = xGetSignal( sig_CSAPP_CBSH_CELLH_SI_MODIFY_REQ, rcvr, xEnv);
            (((yPDP_sig_CSAPP_CBSH_CELLH_SI_MODIFY_REQ)S)->Param1) = rcvPtr;
            break;
          }
#if BPM_PRESENT != 1
        case BPM_SELFCARD_STATE_CHANGE:
          {
            LOG_PRINT(DEBUG,"[ENV]BPM_SELFCARD_STATE_CHANGE:signal rcvd from BPM in ACTIVE State");
            param = (struct sAisParam *)(rcvPtr+sizeof(SysHdr));
            cardStateChangeHandler(param); 
            DalocMsgBuf((I_Void *)rcvPtr) ;
            return;
          }
#endif 
        case OAMS_TRXH_CELLH_OPR_STATE_IND: //abis HA
          {
            refId = GetRefId(rcvPtr,&refId2) ;

            LOG_PRINT(INFO,"CELLH:(Env):OAMS_TRXH_CELLH_OPR_STATE_IND: Rcvd from CFG for CellId[%d]Lac[%d]",refId,refId2);
            if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS)
            {
              LOG_PRINT(MAJOR,"CELLH:(Env):No CELLHM Inst found for [cellId=%d][lac=%d]",refId,refId2);
              DalocMsgBuf((I_Void *)rcvPtr);                          
              return;
            }
            if (lclPidPtr == 0)
            {
              LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found");
              DalocMsgBuf((I_Void *)rcvPtr);
              return ;
            }
            rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;

            LOG_PRINT(INFO,"CELLH:(Env):Value of LclPidPtr[%d]",lclPidPtr)
                                        /* Send this Message into TAU model */
                                        S = xGetSignal( sig_OAMS_TRXH_CELLH_OPER_STATE_IND, rcvr, xEnv);
            (((yPDP_sig_OAMS_TRXH_CELLH_OPER_STATE_IND)S)->Param1) = rcvPtr;
            break;
          }
        case OAMS_RM_CELLHM_AIP_REQ: //abis HA
          {

            DalocMsgBuf((I_Void *)rcvPtr);

            isDbUnLockRcvd = I_TRUE;
            LOG_PRINT(INFO,"CELLH:(Env):OAMS_RM_CELLH_AIP_REQ RCVD");
            if (isStandbyCard == I_TRUE )  //Abis HA
            {				
              if(isAipRcvd == I_TRUE)
              {
                isAipRcvd = I_TRUE;			
                LOG_PRINT(INFO,"Entered STANDBY to AIP , flag=TRUE");
                if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
                {
                  LOG_PRINT(INFO,"Error in fetching BSC Admin State");
                }
                if(bssAdminState == UNLOCKED)		
                {	

                  //res = getallCellhSwitchOverContextTable(&ptrCellhSwitchOverContextTableApi, &noOfRows, &rowSize); 
                  res = getallCellPerTable(&ptrCellPerTableApi,&noOfRows,&rowSize);
                  if(res != CLIB_SUCCESS)
                  {
                    LOG_PRINT(INFO,"No cell found in DB");
                    LOG_PRINT(INFO,"Moving from INSERVICE/StandBy->AIP");

                  } //if res
                  else
                  {					
                    LOG_PRINT(INFO,"Entered AIP,send INT MSG noOfRows=%d",noOfRows);
                    for(i=0; i<noOfRows; i++)
                    {			 
                      //tmpPtrCellhSwitchOverContextTableApi  = (CellhSwitchOverContextTableApi *)((I_U8*)(ptrCellhSwitchOverContextTableApi) + i*rowSize);
                      tmpPtrCellPerTableApi  = (CellPerTableApi *)((I_U8*)(ptrCellPerTableApi) + i*rowSize);

                      /*Read the Replicated context for CellId and Lac  in for loop*/				

                      refId = tmpPtrCellPerTableApi->cellId;//From Replicated context
                      refId2= tmpPtrCellPerTableApi->lac;   //From Replicated context
                      LOG_PRINT(INFO,"CELLH:(Env):Prepare INT_CONTEXT_SWITCHOVER msg for CellId[%d]Lac[%d]",refId,refId2); 

                      cellAdminState =    tmpPtrCellPerTableApi->adminState;

                      if(cellAdminState == 1)	
                      {				


                        LOG_PRINT(INFO,"ALLOCATE New Inst for CellId=%d Lac=%d",tmpPtrCellPerTableApi->cellId,tmpPtrCellPerTableApi->lac);	
                if (SearchAlocatedInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS )
                {
                  LOG_PRINT(CRITICAL,"No CELLHM Ins found for cellId = [%d] LAC = [%d]",refId, refId2);
                        if (AlocNewInst(&lclPidPtr,(I_S32*)&instId,ENT_OAMS_CELLH,CELLHM_HANDLER,refId,refId2,0,0,0) != INST_SUCCESS )
                        {
                          //LOG_PRINT(CRITICAL,"CELLH:(Env):Unable to create New Instance...\n") ;
                          gCurrentCardState = gNewCardState;
                          //LOG_PRINT(INFO,"CurrentCardState: [%d]", gCurrentCardState) ;
                          //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
                          LOG_PRINT(INFO,"Cannot create new Inst.CurrentCardState[%d]NewCardState[%d] Moving to ACTIVE IN PROGRESS State ");
                          gHandleMsgStart = I_TRUE;

                          RELEASE_MUTEX;
                          return ;
                        }
                }
                else
                {
                  LOG_PRINT(DEBUG, "xInEnv : INSTANCE ALLOCATED SEARCHED FOR CELLHM CELLID : %d, LAC : %d", refId, refId2);
                }
                        if (lclPidPtr == 0)
                        {
                          LOG_PRINT(CRITICAL,"CELLH:(Env):Invalid Instance Found...\n");
                          return ;
                        }
                        rcvr.LocalPId = (xLocalPIdNode)lclPidPtr;
                        LOG_PRINT(INFO,"CELLH:(Env):Value of LclPidPtr[%d]",lclPidPtr)
                                                    /* Send this Message into TAU model */
                                                    S = xGetSignal( sig_CELLH_INT_CHECK_CONTEXT_SWITCHOVER, rcvr, xEnv);
                        (((yPDP_sig_CELLH_INT_CHECK_CONTEXT_SWITCHOVER)S)->Param1) = tmpPtrCellPerTableApi->cellId;
                        (((yPDP_sig_CELLH_INT_CHECK_CONTEXT_SWITCHOVER)S)->Param2) = tmpPtrCellPerTableApi->lac;
                        SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );	
                      }//cellAdminState=1
                    }//for
                    free(ptrCellPerTableApi);
                  }//else	
                }//if BscUnlocked
                gCurrentCardState = gNewCardState;
                gNewCardState = CARDSTATE_INVALID;
                //LOG_PRINT(INFO,"CurrentCardState: [%d]", gCurrentCardState) ;
                //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ;
                LOG_PRINT(INFO,"CurrentCardState[%d]NewCardState[%d]Moving to ACTIVE IN PROGRESSState ");
                gHandleMsgStart = I_TRUE;
                isAipRcvd = I_FALSE;
                isDbUnLockRcvd = I_FALSE;
                sendCellhRmAipResp();
                LOG_PRINT(INFO,"Msg sent to RM");
                RELEASE_MUTEX;

              }//isAipRcvd
              else
              {
                LOG_PRINT(INFO,"Wait For AIP from BPM");				
              }				
            }//if StandbyCard
            else
            {
              LOG_PRINT(INFO,"Handling Not Required..Card not Standby");				
            }				

            return;
          }
        case OAMS_RM_CELLHM_ACTIVE_REQ:
          {
            LOG_PRINT(INFO,"OAMS_RM_CELLHM_ACTIVE_REQ rcvd");
            isRmActRcvd = I_TRUE;
            if(isBpmActRcvd == I_TRUE)
            {
              activeInProgressStateHandler();
              sendCellhRmActiveResp();
              LOG_PRINT(INFO,"Moving from AIP->ACTIVE.. ");
            }				
            else
            {
              LOG_PRINT(INFO,"Wait for Act notification from BPM");				
            }				
            return;				
          }


        default:
          {
            /* CS4.0: Changes for HA Start */
            //LOG_PRINT(INFO,"CurrentCardState: [%d]", gCurrentCardState) ; 
            //LOG_PRINT(INFO,"NewCardState: [%d]", gNewCardState) ; 
            LOG_PRINT(INFO,"CELLH:(xInEnv):Entered Default Case:CurrentCardState[%d]NewCardState[%d]");
            /* CS4.0: Changes for HA End */
            DalocMsgBuf((I_Void *)rcvPtr);
            return;
          }
      }
      SDL_Output( S xSigPrioPar(xDefaultPrioSignal), (xIdNode *)0 );
    }
    else
    {
#if BPM_PRESENT != 1
      if ( msgType == BPM_SELFCARD_STATE_CHANGE )
      {
        LOG_PRINT(DEBUG,"[ENV]BPM_SELFCARD_STATE_CHANGE: signal rcvd from BPM");
        param = (struct sAisParam *)(rcvPtr+sizeof(SysHdr));
        cardStateChangeHandler(param); 
        DalocMsgBuf((I_Void *)rcvPtr) ;
        return;
      }
#endif  
      LOG_PRINT(DEBUG,"Card is not in Active State. Dalocate msg");
      DalocMsgBuf((I_Void *)rcvPtr) ;
      return ;
    }

#ifdef XTENV
    return SDL_Time_Lit((xint32)0,(xint32)0);
#endif
  }
}
