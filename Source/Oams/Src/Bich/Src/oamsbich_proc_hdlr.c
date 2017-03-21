/************************** File Header *****************************************
FILE NAME         :  oamsbich_proc_hdlr.c
PURPOSE           :  Bic Handler procedures implementaiton.
PROJECT           :  BSS R2.2
SUBSYSTEM         :  OAMS
AUTHOR            :  VNL/Bikram Bhatt
CSCI ID           :
VERSION           :  V0.1
 *******************************************************************************/

#include <oamsbich_includes.h>
#include <msg_struct.h>
#include <syscmn_hashdefs.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_datastruct.h>
#include <syscmn_datastruct.h>
#include <oamsxxx_alarmid.h>
#include <oams_msgstruct.h>
#include <oamsbich_abis_chain_mgr.h>
#include <oamsbich_proc_hdlr.h>
#include <oams_hashdefs.h>
#include <psapptb_hashdefs.h>


/*****************************************************************************************
***********************************MACRO NEEDED ONLY FOR THIS FILE START******************
*****************************************************************************************/

#ifdef LOG_PRINT
#undef LOG_PRINT
#define LOG_PRINT(level,format,args...)\
{\
  if(logLevelPtrG != (I_U32 *)0)\
  if((*logLevelPtrG & level) || (consolePrintFlagG == 1))\
  {\
     CallLog4Func(level, (I_U32)(GET_TAU_INST_NR()), format, ##args);\
  }\
}
#endif

/*****************************************************************************************
***********************************MACRO NEEDED ONLY FOR THIS FILE END********************
*****************************************************************************************/

/*****************************************************************************************
***********************************GLOBAL VARIABLES START*********************************
*****************************************************************************************/

OamsBichContext *gOamsBichContextPtr;
//I_U32  BtsOprState;
/* mapStateNumToStateName
String are filled in same order as in state__e
typedef enum 
{
  eInvalidState, 
  eIdle,
  eLockedDisabled,
  eUnlockedDisabled,
  eUnlockedEnabled,
  eWaitForLinkEstab,
  eWaitForChildTrxDisc,
  eSameState,
  eStarState,
  eStateCount //Keep it last as it givies the count for the states used in mapStateNumToStateName
} state__e;
*/
static I_PU8 mapStateNumToStateName[] =  {
    [eIdle]                 ="eIdle",
    [eLockedDisabled]       ="eLockedDisabled",
    [eUnlockedDisabled]     ="eUnlockedDisabled",
    [eUnlockedEnabled]      ="eUnlockedEnabled",
    [eWaitForLinkEstab]     ="eWaitForLinkEstab",
    [eWaitForChildTrxDisc]  ="eWaitForChildTrxDisc",
    [eSameState]            ="eSameState",
    [eStarState]            ="eStarState",
    [eInvalidState]         ="eInvalidState"
};

static I_PU8 mapProcNumToProcName[] =  {
  [eNoProc]                 = "eNoProc",
  [eAddBtsProc]             = "eAddBtsProc",
  [eDelBtsProc]             = "eDelBtsProc",
  [eLockProc]               = "eLockProc",
  [eUnlockProc]             = "eUnlockProc",
  [eLapdDownProc]           = "eLapdDownProc",
  [eLapdLinkEstabProc]      = "eLapdLinkEstabProc",
  [eAddChildTrxProc]        = "eAddChildTrxProc",
  [eDelChildTrxProc]        = "eDelChildTrxProc",
  [eResetBtsProc]           = "eResetBtsProc"
};
/*Changes merged from R2.9 Issue #31185 Gaurav Sinha*/
I_Void prepareAlarmFromFailureEventReportForR3(CsappAbihmBichFailureEventReport *pRcvdMsg,I_U8 alarmString[100]);

//static OamsBichContext *gOamsBichContextPtr;

/*****************************************************************************************
***********************************GLOBAL VARIABLES END***********************************
*****************************************************************************************/

/*****************************************************************************************
***********************************UTILITY BASED PROCEDURES END***************************
*****************************************************************************************/

/******************************* Function  Header*****************************
Function Name : logPrintBichContext()
Parameters    : None
Return type   : I_Void
Purpose       : This func print Bich Context stored
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void logPrintBichContext(I_Void)
{
  LOG_PRINT(
   INFO,
   "[%s][E1:%u][Ts:%u][BtsID:%u][BtsTei:%u][BtsType:%u][AS:%u][LS:%u][OS:%u][TrxId:%u][OS:%u][TrxId:%u][OS:%u]",
   GET_STATE_NAME(GET_ACTIVE_STATE()),
   GET_BTS_TRUNK(),
   GET_BTS_TRUNK_TS(),
   GET_BTS_ID(),
   GET_BTS_TEI(),
   GET_BTS_TYPE(),
   GET_BTS_ADMIN_STATE(),
   GET_BTS_LAPD_OPR_STATE(),
   getOprState(),
   GET_CHILD_TRX_ID(0),
   GET_CHILD_TRX_OPR_STATE(0),
   GET_CHILD_TRX_ID(1),
   GET_CHILD_TRX_OPR_STATE(1)            
  );
}

/******************************* Function  Header*****************************
Function Name : logPrintBichContextFromTau()
Parameters    : None
Return type   : I_Void
Purpose       : This func print Bich Context stored from TAU
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void logPrintBichContextFromTau(OamsBichContext *OamsBichContextPtr)
{
  SET_BICH_CNTX_PTR(OamsBichContextPtr);
  LOG_PRINT(INFO,"Enter [%s]",__func__);  
  logPrintBichContext();
  LOG_PRINT(INFO,"Exit [%s]",__func__);  
}

/******************************* Function  Header*****************************
Function Name : logPrintStateNameFromTau()
Parameters    : None
Return type   : I_Void
Purpose       : This func print Bich Context stored from TAU
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void logPrintStateNameFromTau(state__e stateNr)
{
  LOG_PRINT(INFO,"[%s] BICH NEXT_STATE = [%s:%d]",__func__,GET_STATE_NAME(stateNr),stateNr);  
}

/******************************* Function  Header*****************************
Function Name : resetBichContext()
Parameters    : None
Return type   : I_Void
Purpose       : This func reset Bich Context stored
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void resetBichContext(I_Void)
{
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  
  I_S32 InstNr = GET_TAU_INST_NR();
  
  delTsNodeFromAbisChain(gOamsBichContextPtr);

  memset(gOamsBichContextPtr,0x00,sizeof (OamsBichContext));
  
  gOamsBichContextPtr->InstNr = InstNr;

  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
Function Name : resetLapdDiscCntxt() Added for changes for issue 19948
Parameters    : None
Return type   : I_Void
Purpose       : This func reset Bich Context stored
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void resetLapdDiscCntxt(I_Void)
{
  
  I_U8 i=ZERO;
  for(i=ZERO;i<50;i++)
  {  
  memset(&lapdDiscCntxt[i],0,sizeof(lapdDiscCntxt[i]));
  }

}
/******************************* Function  Header*****************************
  Function Name : getProcResult()
Parameters    : None
Return type   : I_Void
Purpose       : This function return Procedure result 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_U32 getProcResult(I_Void)
{
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  switch ( GET_PROC_RESULT_SRC() ) {
    case eDbs:
      LOG_PRINT(INFO,"[%s] DBS error found [%d]",__func__,GET_PROC_RESULT_CODE());
      return (I_S32)GET_PROC_RESULT_CODE();
    case eInternal:
      LOG_PRINT(INFO,"[%s] Internal error found [%u]",__func__,GET_PROC_RESULT_CODE());
      return GET_PROC_RESULT_CODE();
  }  
  LOG_PRINT(INFO,"[%s] OAMS_RSLT_SUCCESS ",__func__);
  LOG_PRINT(INFO,"Exit [%s]",__func__);
  return OAMS_RSLT_SUCCESS;
}


/******************************* Function  Header*****************************
  Function Name : getOprState()
Parameters    : None
Return type   : I_Void
Purpose       : This func returns the Opertaion State of Bic/Bts based on its
child trx operation state
Other Note    : Added For BSC R22
 *****************************************************************************/
I_U32 getOprState(I_Void)
{
  I_U32 i = 0;
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  for (i = 0; i < MAX_NUM_OF_CHILD_TRX; i++) {
    if ( ENABLED == GET_CHILD_TRX_OPR_STATE(i) ) {
      LOG_PRINT(INFO,"%s: ENABLED",__func__);
      return ENABLED;
    }
  }
  LOG_PRINT(INFO,"%s: DISABLED",__func__);
  LOG_PRINT(INFO,"Exit [%s]",__func__);
  return DISABLED;  
}


/******************************* Function  Header*****************************
  Function Name : outputMsg()
Parameters    : None
Return type   : I_Void
Purpose       : This func sends the message to rcvrEntId
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void outputMsg(I_U32 sendMsgType, I_U32 rcvrEntId, I_PU8 msgName, I_PU8 rcvrName)
{
	I_PVoid msgPtr = GET_SEND_MSG_PTR();
  I_U8    prcr   = PRCR_CP;
  
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( !msgPtr ) {
    LOG_PRINT(CRITICAL,"SEND_MSG_PTR is not allocated");
    return;
  }

  prcr = ((ENT_PSAPP_TBBSC == rcvrEntId) || (ENT_CSAPP_ABIHM == rcvrEntId)) ? PRCR_PP : PRCR_CP;
  FILL_SYS_HDR(msgPtr,
               sendMsgType, 
               MSG_SUB_TYPE, 
               PRCR_CP,
               ENT_OAMS_BICH, 
               GET_TAU_INST_NR(), 
               prcr, 
               rcvrEntId, 
               ZERO);    
  if ( !SendMsg(msgPtr, 1, GET_SEND_MSG_SIZE()) )  {
    LOG_PRINT(LOG_CRITICAL,"\n[%s] SendMsg failed",__func__); 
    return ; 
  }
  LOG_PRINT(INFO,"\n[State:%s][Sendign Message :%s][To:%s]",GET_STATE_NAME(GET_ACTIVE_STATE()),msgName,rcvrName);
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : updBichContxtFromAddBicReq()
Parameters    : None
Return type   : I_Void
Purpose       : This func update Bich Context Data based on Add Bic Request
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void updBichContxtFromAddBicReq(I_Void)
{
  OamsCfgBichAddBicReq *msgPtr = GET_RCVD_MSG_PTR();
  
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  SET_BTS_ID(msgPtr->bicId);
 
  SET_BTS_TRUNK(msgPtr->e1Id);
  SET_BTS_TRUNK_TS(msgPtr->e1Ts);
  
  SET_BTS_TYPE(msgPtr->btsType);
  SET_BTS_ADMIN_STATE(msgPtr->adminState);
  SET_BTS_TEI(msgPtr->applTei);
  
  LOG_PRINT(INFO,"[%s][E1Id: %d E1Ts: %d BtsId: %u BtsType: %u] [BtsTei: %u] AddBts/AddBic rcvd ",
                 __func__,
                 GET_BTS_TRUNK(),
                 GET_BTS_TRUNK_TS(),
                 GET_BTS_ID(),
                 GET_BTS_TYPE(),
                 GET_BTS_TEI());
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : addBtsInStatusTable()
Parameters    : None
Return type   : I_Void
Purpose       : This func add Bts entry in status table
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void addBtsInStatusTable(I_Void)
{
  BicStatusTableApi bicStatusTableApiBuff = {0};  

  LOG_PRINT(INFO,"Enter [%s]",__func__);

	if(ENT_OAMS_BICH != GET_MSG_RCVR())
   {
    bicStatusTableApiBuff.bicId             = GET_BTS_ID();
   /*Added for R3 BTS starts*/
    if ((GET_BTS_TYPE() == BIC) || (GET_BTS_TYPE() == R2_BTS))
    {
    bicStatusTableApiBuff.lapdLinkStatus    = BTS_LAPD_LINK_DOWN; 
    }
    else 
    { 
    bicStatusTableApiBuff.lapdLinkStatus    = BTS_LAPD_NOT_APPLICABLE;  
    }
   /*Added for R3 BTS ends*/
    
    bicStatusTableApiBuff.btsIpLinkStatus   = ABIS_IP_DOWN ;
    bicStatusTableApiBuff.parentBicId       = ZERO;
    bicStatusTableApiBuff.parentBicPortNum  = ZERO;
    bicStatusTableApiBuff.oprState          = DISABLED ;
    bicStatusTableApiBuff.maxStepsSize      = 0xFF ;
    bicStatusTableApiBuff.clockSource       = 0xFF ;

    if ( CLIB_SUCCESS != insertBicStatusTable(&bicStatusTableApiBuff)) {
      LOG_PRINT(MAJOR,"[%s] insertBicStatusTable failed",__func__);
      SET_PROC_RESULT(eDbs,OAMS_RSLT_FAILURE);
    }
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendAddBtsResp()
Parameters    : None
Return type   : I_Void
Purpose       : This func sends fills and send Add Bts Response to message to CFG
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendAddBtsResp(I_Void)
{
  OamsBichCfgAddBicResp *msgPtr = (OamsBichCfgAddBicResp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCfgAddBicResp) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr ) {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicId   = GET_BTS_ID();
  msgPtr->e1Id    = GET_BTS_TRUNK();
  msgPtr->e1Ts    = GET_BTS_TRUNK_TS();
  msgPtr->result  = getProcResult();

  OUTPUT_MSG(OAMS_BICH_CFG_ADD_BIC_RESP,ENT_OAMS_CFG);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/* Add Changes HA ABIS BSC-R2.5.5 Start */
/******************************* Function  Header*****************************
Function Name : updateContextOnStateTransition()
Parameters    : Void
Return type   : I_U32
Purpose       : This fucn handles the BicContext in DB.
Other Note    : Added For HA ABIS BSC R2.5.5
 *****************************************************************************/

I_U32 updateContextOnStateTransition(I_Void)
{
	 I_U32 									 		biId;
	 I_S32											errCode;
	 I_U32                      i = 0;
   BtsContextTableApi					*upDataBtsContextTable = NULL;
	 OamsBichStandbyCardContext *tmpPtrCnxtData = NULL;	
	
	  upDataBtsContextTable =  AlocOrdBuf(sizeof(BtsContextTableApi));	
		if (upDataBtsContextTable == NULL ) {
    LOG_PRINT(CRITICAL,"Could Not allocate memory for BtsContextTableApi in function updateContextOnStateTransition ");
    return I_FALSE;
  	}

    tmpPtrCnxtData = upDataBtsContextTable->data; 
	 
LOG_PRINT(INFO,"LocalContext:bicId (%d) , e1Id (%d) & e1Ts (%d)",gOamsBichContextPtr->bicId, gOamsBichContextPtr->e1Id, gOamsBichContextPtr->e1Ts);
		
		upDataBtsContextTable->btsId = gOamsBichContextPtr->bicId; 

    tmpPtrCnxtData->isBicSwDesInActiveSwPresent = gOamsBichContextPtr->isBicSwDesInActiveSwPresent;
    tmpPtrCnxtData->e1Id =	gOamsBichContextPtr->e1Id;
    tmpPtrCnxtData->e1Ts = gOamsBichContextPtr->e1Ts;
    tmpPtrCnxtData->bicId = gOamsBichContextPtr->bicId;
    tmpPtrCnxtData->bicTei = gOamsBichContextPtr->bicTei;
    tmpPtrCnxtData->parentBicId = gOamsBichContextPtr->parentBicId;
    tmpPtrCnxtData->upStreamPort = gOamsBichContextPtr->upStreamPort;
    tmpPtrCnxtData->swDes = gOamsBichContextPtr->swDes;
    tmpPtrCnxtData->inactiveSwDes = gOamsBichContextPtr->inactiveSwDes;
    tmpPtrCnxtData->activeState = gOamsBichContextPtr->activeState;
    tmpPtrCnxtData->btsType = gOamsBichContextPtr->btsType;
    tmpPtrCnxtData->adminState = gOamsBichContextPtr->adminState;
    tmpPtrCnxtData->btsLapdOprState = gOamsBichContextPtr->btsLapdOprState;
    tmpPtrCnxtData->IpAdd.AAA = gOamsBichContextPtr->IpAdd.AAA;
    tmpPtrCnxtData->IpAdd.BBB = gOamsBichContextPtr->IpAdd.BBB;
    tmpPtrCnxtData->IpAdd.CCC = gOamsBichContextPtr->IpAdd.CCC;
    tmpPtrCnxtData->IpAdd.DDD = gOamsBichContextPtr->IpAdd.DDD;
    tmpPtrCnxtData->UdpPort = gOamsBichContextPtr->UdpPort;
    
    /* R2.9 changes starts */
    if(GET_BTS_TYPE() != R2_BTS)
    {
      tmpPtrCnxtData->nextState = gOamsBichContextPtr->actProcState.procResult.nextState; 
      tmpPtrCnxtData->activeProc = gOamsBichContextPtr->actProcState.ActiveProc; 
      
      for (i = 0; i < MAX_NUM_OF_CHILD_TRX; i++) 
      {
        tmpPtrCnxtData->childTrxCntxt.ChildTrxInfo[i].trxId = gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[i].trxId;
        tmpPtrCnxtData->childTrxCntxt.ChildTrxInfo[i].oprState = gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[i].oprState;
      }
    }
    /* R2.9 changes ends */
    
    LOG_PRINT(INFO,"Oper State for BIC Lapd in context  is =%d",gOamsBichContextPtr->btsLapdOprState);
	  errCode = updateBtsContextTable(upDataBtsContextTable);
		if(errCode != CLIB_SUCCESS)
		{
		LOG_PRINT(INFO,"Updation of context failed...insert data");
			errCode = insertBtsContextTable(upDataBtsContextTable);

			if(errCode != CLIB_SUCCESS)
			{
			LOG_PRINT(INFO,"Insertion of context failed...do nothing");
			}
			else
			{
			LOG_PRINT(INFO,"Insertion of context SUCCESS");
			}
			
		}
		else
		{
			LOG_PRINT(INFO,"Updation of context Success");
		}
	  /* freeing pointer */	
		if(upDataBtsContextTable != NULL)
		{
			DalocOrdBuf((I_Void *)upDataBtsContextTable);
		}


}  

/******************************* Function  Header*****************************
Function Name : compareOperStateContext()
Parameters    : Void
Return type   : I_U32
Purpose       : This fucn compares cuurent operState with BicContext.
Other Note    : Added For HA ABIS BSC R2.5.5
 *****************************************************************************/

I_U32 compareOperStateContext(I_Void)
{
	BtsContextTableIndices          inDataBtsContextTable = {0};
	BtsContextTableApi             *outDataBtsContextTable;
	OamsBichStandbyCardContext     *bichContext;
	I_S32                           errCode;
	I_U32														curOperState = getOprState();

		/* Allocate memory to bichContext */
		bichContext = (OamsBichStandbyCardContext *)AlocOrdBuf(sizeof(OamsBichStandbyCardContext));
		if (bichContext == NULL ) {
    LOG_PRINT(CRITICAL,"ENV: Could Not allocate memory for OamsBichStandbyCardContext ");
    return I_FALSE;
  	}

	 inDataBtsContextTable.btsId= GET_BTS_ID();
	/* Db Query to get Context data for Bic */

		errCode = getBtsContextTable(&inDataBtsContextTable,&outDataBtsContextTable);
		if(errCode != CLIB_SUCCESS)
    	{
    		LOG_PRINT(INFO,"get of context failed for bicId : %d",GET_BTS_ID());
    		DalocOrdBuf((I_Void *)bichContext);
    		return I_FALSE;
    	}
	/* Copy Context Data */
		memcpy(bichContext,outDataBtsContextTable->data,(sizeof(OamsBichStandbyCardContext)));
	/* print Context data */
		LOG_PRINT(INFO,"Context :operState(%d) , bicId (%d)",bichContext->btsLapdOprState,GET_BTS_ID());
		
		if(outDataBtsContextTable != NULL)
		{
  		free(outDataBtsContextTable);
  		LOG_PRINT(INFO,"freed outDataBtsContextTable");
		}

	
	/*Compare OperState */
		if( (bichContext->btsLapdOprState) == curOperState)
		 {
				LOG_PRINT(INFO,"compareOperStateContext returning True");
				DalocOrdBuf((I_Void *)bichContext);
				return I_TRUE;
		 }
		else
		 {
    		DalocOrdBuf((I_Void *)bichContext);
				return I_FALSE;
		 }
}
 
/******************************* Function  Header*****************************
Function Name : checkLapdStatusInBicStatusTable()
Parameters    : Void
Return type   : I_U32
Purpose       : This fucn gets  LapdState with DB on active Card after switchover.
								Added to fix Mantis: 14459
Other Note    : Added For HA ABIS BSC R2.5.5
 *****************************************************************************/
I_U32 checkLapdStatusInBicStatusTable(void)
{
BicStatusTableIndices        bicStatusTableIndices = {0};
BicStatusTableApi           *bicStatusTableApiBuff = NULL;
I_S32												 errCode;
I_U32												 lapdLinkStatus = 0 ;

if ( GET_MSG_TYPE() == CSAPP_ABIHM_BICH_BM_HELLO)
{
bicStatusTableIndices.bicId = GET_BTS_ID();

errCode=getBicStatusTable(&bicStatusTableIndices,&bicStatusTableApiBuff);

   if( errCode == CLIB_SUCCESS )
		{
    	lapdLinkStatus	=	bicStatusTableApiBuff->lapdLinkStatus;
      if(lapdLinkStatus == BTS_LAPD_LINK_DOWN)	
			{
				free(bicStatusTableApiBuff);
				return I_FALSE;
			}
		  else
      {   
        LOG_PRINT(INFO,"BM_HELLO Received and Lapd Status is UP, so discard HELLO");
				free(bicStatusTableApiBuff);
				return I_TRUE;
			}
    }
}
return I_FALSE;
} 

/* Add Changes HA ABIS BSC-R2.5.5 End */

/******************************* Function  Header*****************************
  Function Name : findNextStateBasedOnAdminAndOprState()
Parameters    : None
Return type   : I_Void
Purpose       : This function returns NextState based on Operation State and 
Admin State 
Other Note    : Added For BSC R22
 *****************************************************************************/
state__e findNextStateBasedOnAdminAndOprState(I_Void)
{
  I_U32  BtsOprState = getOprState(); 
  
  LOG_PRINT(INFO,"Enter [%s]",__func__);

  switch (GET_BTS_ADMIN_STATE()) {
    case LOCKED:
      switch (BtsOprState) {
        case ENABLED:
          LOG_PRINT(INFO,"[E:]Invalid State Bts is Locked and Enabled");
          break;
        case DISABLED:
					updateContextOnStateTransition();
          /* R2.9 changes starts */
          if(GET_BTS_TYPE() != R2_BTS)
          {
            if ((GET_NEXT_STATE() == eWaitForLinkEstab) && (ENT_OAMS_BICH == GET_MSG_RCVR()))
            {
              return eWaitForLinkEstab;
              break;
            }  
            else if((GET_NEXT_STATE() == eWaitForChildTrxDisc) && (ENT_OAMS_BICH == GET_MSG_RCVR()))   
            {
              return eWaitForChildTrxDisc;  
              break;
            }  
            else  
            {
              return eLockedDisabled;
              break;
            }
          } 
          else
          {  
           return eLockedDisabled;
           break;
          }  
          /* R2.9 changes ends */
      }
      break;
    case UNLOCKED:
      switch (BtsOprState) {
        case ENABLED:
					updateContextOnStateTransition();
          /* R2.9 changes starts */
          if(GET_BTS_TYPE() != R2_BTS)
          {
            if ((GET_NEXT_STATE() == eWaitForLinkEstab) && (ENT_OAMS_BICH == GET_MSG_RCVR()))
            {
              return eWaitForLinkEstab;
              break;
            }  
            else if((GET_NEXT_STATE() == eWaitForChildTrxDisc) && (ENT_OAMS_BICH == GET_MSG_RCVR()))   
            {
              return eWaitForChildTrxDisc;  
              break;
            }  
            else  
            {
              return eUnlockedEnabled;
              break;
            }
          } 
          else
          {  
           return eUnlockedEnabled;
           break;
          }
        /* R2.9 changes ends */ 
        case DISABLED:
					updateContextOnStateTransition();
          /* R2.9 changes starts */
          if(GET_BTS_TYPE() != R2_BTS)
          {
            if ((GET_NEXT_STATE() == eWaitForLinkEstab) && (ENT_OAMS_BICH == GET_MSG_RCVR()))
            {
              return eWaitForLinkEstab;
              break;
            }  
            else if((GET_NEXT_STATE() == eWaitForChildTrxDisc) && (ENT_OAMS_BICH == GET_MSG_RCVR()))   
            {
              return eWaitForChildTrxDisc;  
              break;
            }  
            else  
            {
              return eUnlockedDisabled;
              break;
            }
          } 
          else
          {  
            return eUnlockedDisabled;
            break;
          }  
          /* R2.9 changes ends */
       }    
      break;
  }  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
  return eInvalidState;
}

/******************************* Function  Header*****************************
  Function Name : handleTrxOperStateChangeIndInLockedState()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles the Trx Operation State Change Ind
It update child Trx operation state and check if Bic/Bts operation state is also changed
or not. If operation state of Bic/Bts is changed it send event to OMC
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleTrxOperStateChangeIndInLockedState(I_Void)
{
  OamsTrxhBichOperStateChangeInd   *msgPtr = GET_RCVD_MSG_PTR(); 
  I_U32  i = 0;
	BicStatusTableApi               bicStatusTableApiInData ;
	BicStatusTableApi               *bicStatusTableApi;
  BicStatusTableIndices           bicStatusTableIndex = {0};
	I_S32               errCode;
  I_U8      alarmString[150];
  I_U32     isBtsLinkMaster;

  /*Mantis -- 14848 Start*/ 
  I_S8 ipAddr[25];
  /*Mantis -- 14848 End*/ 
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (msgPtr->bicId != GET_BTS_ID() )  {
    LOG_PRINT(INFO,"\n[%s:] rcvd BtsId[%u] is not same as stored BtsId[%u]", 
                   __func__,
                   msgPtr->bicId,
                   GET_BTS_ID());
    return;
  }

 
	/* Added for HA ABIS BSC-2.5.5 Start*/
		if (msgPtr->isBtsLapdOprStatePresent == I_TRUE )
		{	
				if((msgPtr->btsLapdOprState) == LAPD_LINK_DOWN)
				{
          
       	 sprintf(alarmString,"LAPD Link Down between BSC and BIC[%u] via E1[%d]E1Ts[%d]",
       		GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
       	  strcat(alarmString, "\0"); 
          fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
         updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_NO_BIC);
         deleteBicFromAbisChain(gOamsBichContextPtr);
         
         if ( (errCode =getIsBtsLapdMasterBssCsPreConTable(&isBtsLinkMaster) ) != CLIB_SUCCESS )
         {
            LOG_PRINT(MAJOR,"Error in getIsBtsLapdMasterBssCsPreConTable: err = %s",clib_strerror(errCode));
         }
         else 
         {
         		if ( getOprState() == ENABLED )
						{
            	if ( isBtsLinkMaster == I_TRUE )
            	{ 
               	LOG_PRINT(MAJOR,"BTS is Link Master So, Sending LAPD_DISC_IND to all Child TRX's");
      					SET_ACTIVE_PROC(eLapdDownProc);
              	fillAndSendLapdDiscIndToTrxh();
                SET_NEXT_STATE(eWaitForChildTrxDisc);
            	  /* R2.9 changes starts */
                if(GET_BTS_TYPE() != R2_BTS)
                {
                  updateContextOnStateTransition();
                }
                /* R2.9 changes ends */ 
              } 
            	else
            	{
              	 LOG_PRINT(DEBUG,"Not Sending OAMS_BICH_TRXH_LAPD_DISCONNECT_IND as Bts is not Link Master");
            	}
						}
						else
						{
            	SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
						}
         }
         	/*	if ( getOprState() != ENABLED )
         		{
            	SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
         		}
         		else
         		{
            	SET_NEXT_STATE(eWaitForChildTrxDisc);
         		}*/
				}
				else if((msgPtr->btsLapdOprState) == LAPD_LINK_UP)
				{
					updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_BIC_CONNECTED);
        	addBicInAbisChain(gOamsBichContextPtr);
        	if (  GET_BTS_TYPE() == R2_BTS ){ /*! Mantis:15499 */
           fillAndSendAddBtsIpToTB(); }
					SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
				}
        /* Retrieve BTS Status Table Record for this BTS Id */
        bicStatusTableIndex.bicId = GET_BTS_ID();

        if (CLIB_SUCCESS == (errCode = getBicStatusTable(&bicStatusTableIndex, &bicStatusTableApi)))
        {
          LOG_PRINT(INFO,"[%s] getBicStatusTable Success for BtsId: %u", __func__, bicStatusTableIndex.bicId);
          bicStatusTableApi->lapdLinkStatus = msgPtr->btsLapdOprState;
          /*Mantis -- 14848 Start*/
          memset(ipAddr,0, sizeof(ipAddr));
          getIpAddrAsString(ipAddr);
          strncpy(bicStatusTableApi->btsIpAddr, ipAddr, sizeof(ipAddr)); 
          /*Mantis -- 14848 End*/ 
          bicStatusTableApi->oprState     = getOprState();
          if ( (errCode =updateBicStatusTable(bicStatusTableApi) ) != CLIB_SUCCESS )
				  {
        		LOG_PRINT(MAJOR,"Error in updateBicStatusTable: err = %s",clib_strerror(errCode));
          }

          free(bicStatusTableApi);
        }
        else
        {
          LOG_PRINT(MAJOR,"[%s] getBicStatusTable Failed for BtsId: %u, Inserting record",
              __func__, bicStatusTableIndex.bicId);
          bicStatusTableApiInData.bicId = GET_BTS_ID();
          bicStatusTableApiInData.lapdLinkStatus = msgPtr->btsLapdOprState;
          memset(ipAddr,0, sizeof(ipAddr));
          getIpAddrAsString(ipAddr);
          strncpy(bicStatusTableApiInData.btsIpAddr, ipAddr, sizeof(ipAddr)); 
          bicStatusTableApiInData.oprState          = getOprState();
          bicStatusTableApiInData.btsIpLinkStatus   = ABIS_IP_DOWN ;
          bicStatusTableApiInData.parentBicId       = ZERO;
          bicStatusTableApiInData.parentBicPortNum  = ZERO;
          bicStatusTableApiInData.clockSource       = GET_BTS_CLOCK_SOURCE();
          bicStatusTableApiInData.maxStepsSize      = GET_BTS_MAX_STEPS_SIZE();
          if ( CLIB_SUCCESS != insertBicStatusTable(&bicStatusTableApiInData))
          {
            LOG_PRINT(MAJOR,"[%s] insertBicStatusTable failed",__func__);
            SET_PROC_RESULT(eDbs,OAMS_RSLT_FAILURE);
          }
        }

        SET_BTS_LAPD_OPR_STATE(msgPtr->btsLapdOprState);
				LOG_PRINT(INFO,"Oper State for BIC Lapd is =%d",msgPtr->btsLapdOprState);
        SET_IP_OPR_STATE(ABIS_IP_DOWN);
		}
		else
    {
      SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
    }
	/* Added for HA ABIS BSC-2.5.5 End*/
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}
/******************************* Function  Header*****************************
  Function Name : handleTrxOperStateChangeInd()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles the Trx Operation State Change Ind
It update child Trx operation state and check if Bic/Bts operation state is also changed
or not. If operation state of Bic/Bts is changed it send event to OMC
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleTrxOperStateChangeInd(I_Void)
{
  OamsTrxhBichOperStateChangeInd   *msgPtr = GET_RCVD_MSG_PTR(); 
  I_U32  i = 0;
  I_Bool trxFound = I_FALSE;
  I_U32  oldBtsOprState = getOprState(); 
  I_U32  newBtsOprState ; 
	BicStatusTableApi           bicStatusTableApiInData ;
	BicStatusTableApi           *bicStatusTableApi;
  BicStatusTableIndices       bicStatusTableIndex = {0};
	I_S32               errCode;
  I_U8      alarmString[150];
  I_U32     isBtsLinkMaster;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (msgPtr->bicId != GET_BTS_ID() )  {
    LOG_PRINT(INFO,"\n[%s:] rcvd BtsId[%u] is not same as stored BtsId[%u]", 
                   __func__,
                   msgPtr->bicId,
                   GET_BTS_ID());
    return;
  }

  for (i=0; i < MAX_NUM_OF_CHILD_TRX; i++) {
    if ( GET_CHILD_TRX_ID(i) == msgPtr->ptrxId ) {
      SET_CHILD_TRX_OPR_STATE(i,msgPtr->operState);
      trxFound = I_TRUE;
    }
  }

  if (!trxFound)  {
    LOG_PRINT(INFO,"\n[%s:] TrxId[%u] not found", __func__,msgPtr->ptrxId)
    return;
  }
 
  newBtsOprState =  getOprState() ;
  switch ( newBtsOprState ) {
    case ENABLED:
      switch (oldBtsOprState) {
        case DISABLED:
          if (CLIB_SUCCESS != updateOperStateInBicStatusTable(GET_BTS_ID(), newBtsOprState)) {
             LOG_PRINT(MAJOR,"[%s] updOperStateInBicStatusTable failed",__func__);            
          }
					if (msgPtr->isBtsLapdOprStatePresent != I_TRUE )
   	 			{				
          	fillAndSendBichCfgAlarmInd(ALARM_BTS_ENABLED ,TRAP_SEVERITY_INFORMATION,"EVENT_BTS_ENABLED");
					}
					else
					{
							 if (I_TRUE != compareOperStateContext() ) {
          		 fillAndSendBichCfgAlarmInd(ALARM_BTS_ENABLED ,TRAP_SEVERITY_INFORMATION,"EVENT_BTS_ENABLED");
          		}
					}
          break;
      }
      break;
    case DISABLED:
      switch (oldBtsOprState) {
        case ENABLED:
          if (CLIB_SUCCESS != updateOperStateInBicStatusTable(GET_BTS_ID(), newBtsOprState)) {
             LOG_PRINT(MAJOR,"[%s] updOperStateInBicStatusTable failed",__func__);            
          }
					if (msgPtr->isBtsLapdOprStatePresent != I_TRUE )
   	 			{				
          	fillAndSendBichCfgAlarmInd(ALARM_BTS_DISABLED,TRAP_SEVERITY_MAJOR,"EVENT_BTS_DISABLED"); 
					}
					else
					{
							 if (I_TRUE != compareOperStateContext() ) {
          		 fillAndSendBichCfgAlarmInd(ALARM_BTS_DISABLED,TRAP_SEVERITY_MAJOR,"EVENT_BTS_DISABLED"); 
          		}

					}
          break;
      }      
      break;    
  }
	/* Added for HA ABIS BSC-2.5.5 Start*/
		if (msgPtr->isBtsLapdOprStatePresent == I_TRUE )
		{	
                    /*Mantis -- 14848 Start*/ 
                    I_S8 ipAddr[25];
                    /*Mantis -- 14848 End*/ 
				if((msgPtr->btsLapdOprState) == LAPD_LINK_UP)
				{
        /* 
        sprintf(alarmString,"LAPD link is UP between BSC and BIC[%u] via E1[%d] E1Ts[%d]",
                            GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
        strcat(alarmString, "\0"); 
        fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_UP, TRAP_SEVERITY_CLEARED, alarmString); */
					updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_BIC_CONNECTED);
        	addBicInAbisChain(gOamsBichContextPtr);
        	if (  GET_BTS_TYPE() == R2_BTS ){ /*! Mantis:15499 */
					fillAndSendAddBtsIpToTB(); }
         	SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
				}
				else if((msgPtr->btsLapdOprState) == LAPD_LINK_DOWN)
				{
					 if (LAPD_LINK_UP == GET_BTS_LAPD_OPR_STATE()) {/*! Mantis: 15408 */
					 fillAndSendLapdDiscIndForBts(GET_BTS_TEI() );     }
					          
       	 sprintf(alarmString,"LAPD Link Down between BSC and BIC[%u] via E1[%d]E1Ts[%d]",
       		GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
       	  strcat(alarmString, "\0"); 
          fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
         updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_NO_BIC);
         deleteBicFromAbisChain(gOamsBichContextPtr);
         
         if ( (errCode =getIsBtsLapdMasterBssCsPreConTable(&isBtsLinkMaster) ) != CLIB_SUCCESS )
         {
            LOG_PRINT(MAJOR,"Error in getIsBtsLapdMasterBssCsPreConTable: err = %s",clib_strerror(errCode));
         }
         else 
         {
        	if ( getOprState() == ENABLED )
						{
            	if ( isBtsLinkMaster == I_TRUE )
            	{ 
               	LOG_PRINT(MAJOR,"BTS is Link Master So, Sending LAPD_DISC_IND to all Child TRX's");
								SET_ACTIVE_PROC(eLapdDownProc); // Added on 22Nov2010
              	fillAndSendLapdDiscIndToTrxh();
           			SET_NEXT_STATE(eWaitForChildTrxDisc);
            	  /* R2.9 changes starts */
                if(GET_BTS_TYPE() != R2_BTS)
                {
                  updateContextOnStateTransition();
                }
               /* R2.9 changes ends */
              } 
            	else
            	{
              	 LOG_PRINT(DEBUG,"Not Sending OAMS_BICH_TRXH_LAPD_DISCONNECT_IND as Bts is not Link Master");
            	}
						}
						else
						{
           		SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
						}
         }
      /*  if ( getOprState() != ENABLED )
         {
           	SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
         }
         else
         {
           	SET_NEXT_STATE(eWaitForChildTrxDisc);
         }*/
			 }
        /* Retrieve BTS Status Table Record for this BTS Id */
        bicStatusTableIndex.bicId = GET_BTS_ID();

        if (CLIB_SUCCESS == (errCode = getBicStatusTable(&bicStatusTableIndex, &bicStatusTableApi)))
        {
          LOG_PRINT(INFO,"[%s] getBicStatusTable Success for BtsId: %u", __func__, bicStatusTableIndex.bicId);
          bicStatusTableApi->lapdLinkStatus = msgPtr->btsLapdOprState;
          /*Mantis -- 14848 Start*/
          memset(ipAddr,0, sizeof(ipAddr));
          getIpAddrAsString(ipAddr);
          strncpy(bicStatusTableApi->btsIpAddr, ipAddr, sizeof(ipAddr)); 
          /*Mantis -- 14848 End*/ 
          bicStatusTableApi->oprState     = getOprState();
          if ( (errCode =updateBicStatusTable(bicStatusTableApi) ) != CLIB_SUCCESS )
				  {
        		LOG_PRINT(MAJOR,"Error in updateBicStatusTable: err = %s",clib_strerror(errCode));
          }

          free(bicStatusTableApi);
        }
        else
        {
          LOG_PRINT(MAJOR,"[%s] UpdateBicStatusTable Failed, Inserting record",__func__);
          bicStatusTableApiInData.bicId = GET_BTS_ID();
          bicStatusTableApiInData.lapdLinkStatus = msgPtr->btsLapdOprState;
          memset(ipAddr,0, sizeof(ipAddr));
          getIpAddrAsString(ipAddr);
          strncpy(bicStatusTableApiInData.btsIpAddr, ipAddr, sizeof(ipAddr)); 
          bicStatusTableApiInData.oprState          = getOprState();
          bicStatusTableApiInData.btsIpLinkStatus   = ABIS_IP_DOWN ;
          bicStatusTableApiInData.parentBicId       = ZERO;
          bicStatusTableApiInData.parentBicPortNum  = ZERO;
          bicStatusTableApiInData.clockSource       = GET_BTS_CLOCK_SOURCE();
          bicStatusTableApiInData.maxStepsSize      = GET_BTS_MAX_STEPS_SIZE();
          if ( CLIB_SUCCESS != insertBicStatusTable(&bicStatusTableApiInData))
          {
            LOG_PRINT(MAJOR,"[%s] insertBicStatusTable failed",__func__);
            SET_PROC_RESULT(eDbs,OAMS_RSLT_FAILURE);
          }
        }

        SET_BTS_LAPD_OPR_STATE(msgPtr->btsLapdOprState);
				LOG_PRINT(INFO,"Oper State for BIC Lapd is =%d",msgPtr->btsLapdOprState);
        SET_IP_OPR_STATE(ABIS_IP_DOWN);
		}
		else
		{
  		SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
		}
	/* Added for HA ABIS BSC-2.5.5 End*/
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendBmRestart()
Parameters    : None
Return type   : I_Void
Purpose       : This func sends Bm Restart message to ABIHM
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendBmRestart(I_Void)
{
  OamsBichAbihmBmRestart *msgPtr = (OamsBichAbihmBmRestart *)ALLOC_IPC_MSG_BUF( sizeof (OamsBichAbihmBmRestart));

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr ) {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicTei = GET_BTS_TEI();

  FILL_ABIS_HDR_FOR_BTS(msgPtr);
  
  OUTPUT_MSG(OAMS_BICH_ABIHM_BM_RESTART,ENT_CSAPP_ABIHM);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : verifyResetBtsReq()
Parameters    : None
Return type   : I_Void
Purpose       : This func verify that Bts Request is valid
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Bool verifyResetBtsReq(I_Void)
{
  OamsCfgBichBtsReset *msgPtr = GET_RCVD_MSG_PTR();

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr) {
    LOG_PRINT(INFO,"[%s] rcvd msgPtr is null",__func__);
    return I_FALSE;
  }

  if (msgPtr->bicId != GET_BTS_ID() ) {
    LOG_PRINT(INFO,"[%s] Rcvd BtsId[%u] Expected BtsId[%u] ",__func__,msgPtr->bicId,GET_BTS_ID());
    return I_FALSE;
  }

  /* Added From CS2.4 Having tag BSC-7.0.3.013 */
  /*
  if (GET_BTS_TYPE() == BIC) {
    LOG_PRINT(INFO,"[%s] Reset request is rcvd for incorrect Bts Type[%u] ",__func__,GET_BTS_TYPE());
    return I_FALSE;
  }
  */ 
 
  if ((LAPD_LINK_DOWN == GET_BTS_LAPD_OPR_STATE()) && (GET_BTS_TYPE() == R2_BTS)){
    LOG_PRINT(INFO,"[%s] Lapd Link is down[%u]  ignore reset",__func__,GET_BTS_LAPD_OPR_STATE());
    return I_FALSE;
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
  return I_TRUE;
}


/******************************* Function  Header*****************************
  Function Name : BICH_INPUT()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn set the bic context for the instance.
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void BICH_INPUT(I_PU8 msgName, state__e stateName, I_PU8 senderName, OamsBichContext *OamsBichContextPtr)
{
  /* S-> StateName
  ** M-> MsgName  
  ** F-> From (SenderName) 
  */
  SET_BICH_CNTX_PTR(OamsBichContextPtr); /*This should be the first call as it sets Contxt Ptr*/
  LOG_PRINT(INFO,"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  LOG_PRINT(INFO,"Enter [%s]",__func__);

  logPrintBichContext();
  if (GET_ACTIVE_STATE() != stateName ) {
    LOG_PRINT(INFO,"[%s:] Active State mismatch [Cxt:%d][Tau:%d]",__func__,GET_ACTIVE_STATE(), stateName);
  }
  SET_ACTIVE_STATE(stateName);
  SET_NEXT_STATE(eSameState); //default nextState is same as current state
  SET_MSG_TYPE_N_MSG_SENDER();  
  LOG_PRINT(INFO,"\n[%s] [State:%s][Rcvd Message:%s][From:%s]",
      __func__,GET_STATE_NAME(stateName),msgName,senderName);
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : BICH_NEXTSTATE()
Parameters    : None
Return type   : I_Void
Purpose       : This func reset the biccontext/IpcBuff/ProcState for the instance.
Other Note    : Added For BSC R22
 *****************************************************************************/
state__e BICH_NEXTSTATE(I_Void)
{
  state__e actState = GET_ACTIVE_STATE(), nextState = GET_NEXT_STATE();

  LOG_PRINT(INFO,"Enter [%s]",__func__);

/* 
 R2.9 changes :-
 a) When card state changes from STANDBY->AIP Bich internally sends ADD_BIC_REQ
    thus for IP BTS if Active Procedure on Active card is eAddBtsProc and eLockProc. These needs 
    to be resetted for handling BM_HELLO from ABIHM and OPER_STATE_CHANGE_IND from TRXH respectively.
 b) For Other, Active Procedures not to be resetted as based on this it handles further messages.
*/
  
  if ((GET_PROC_DONE_STATUS() == I_TRUE) ||
     ((ENT_OAMS_BICH == GET_MSG_RCVR()) && (GET_ACTIVE_PROC() != eNoProc)))
     //((ENT_OAMS_BICH == GET_MSG_RCVR()) && ((GET_ACTIVE_PROC() == eAddBtsProc) ||
     //(GET_ACTIVE_PROC() == eLockProc) || (GET_ACTIVE_PROC() == eLapdLinkEstabProc))))
                                           
  {
    LOG_PRINT(INFO, "Received next state and resetting the active state \n");  
    RESET_ACTIVE_PROC_STATE();
  }

  FREE_IPC_MSG_BUF();
  
  LOG_PRINT(INFO,"\n [%s] State change From:[%s] To:[%s]",
                 __func__,
                 GET_STATE_NAME(actState),
                 GET_STATE_NAME( (nextState == eSameState) ? actState : nextState));
  
  SET_ACTIVE_STATE(nextState);

  if (eIdle == nextState ) {
    resetBichContext();
  }

  logPrintBichContext();

  LOG_PRINT(INFO,"Exit [%s]",__func__);
  
  LOG_PRINT(INFO,"-------------------------------------------------------------------------------");
  return nextState;
                 
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendBichCfgAlarmInd()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn sends Alarm to CFG.
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendBichCfgAlarmInd(I_U32 alarmId, I_U32 alarmLevel, I_U8 alarmString[])
{
   I_U32	mSize;
   mSize = sizeof(OamsBichCfgAlarmInd) ;
   OamsBichCfgAlarmInd *msgPtr ;
   
   msgPtr = (OamsBichCfgAlarmInd *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCfgAlarmInd) );
   LOG_PRINT(INFO,"Enter [%s]",__func__);
   if (!msgPtr )
   {    
      LOG_PRINT(CRITICAL,"Could Not allocate memory");
      return ;
   }
	/*Changes merged from R2.9 Issue #31185 Gaurav Sinha*/
   LOG_PRINT(INFO,"ALARM ID=%d",alarmId);	 
   msgPtr->sysAlarm.sysalarmId = alarmId ;
   msgPtr->sysAlarm.alarmLevel = alarmLevel ;
   msgPtr->sysAlarm.info3= OAMS_OBJTYPE_BIC ;
   msgPtr->sysAlarm.key1= GET_BTS_ID() ;

   strcpy(msgPtr->sysAlarm.infoString,alarmString);
   strcat(msgPtr->sysAlarm.infoString, "\0"); 
   msgPtr->sysAlarm.infoStrLen = strlen(msgPtr->sysAlarm.infoString);
   LOG_PRINT(INFO,"sysAlarm Info: %s ",msgPtr->sysAlarm.infoString ); 
   LOG_PRINT(INFO,"sysAlarm info len: %d ",msgPtr->sysAlarm.infoStrLen );

   OUTPUT_MSG(OAMS_BICH_CFG_ALARM_IND,ENT_OAMS_CFG);  

   LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : delBtsFromStatusTable()
Parameters    : None
Return type   : I_Void
Purpose       : This func delete Bts/Bich from the Status Table.
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void delBtsFromStatusTable(I_Void)
{
  BicStatusTableIndices bicStatusIndices = {0};  
  I_S32 delStatus = CLIB_SUCCESS;
  
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  bicStatusIndices.bicId = GET_BTS_ID();
    
  if ( CLIB_SUCCESS != ( delStatus = deleteBicStatusTable(&bicStatusIndices) )) {
     LOG_PRINT(MAJOR,"[%s] deleteBicStatusTable failed",__func__);
     SET_PROC_RESULT(eInternal,OAMS_RSLT_FAILURE);
     return;
  } 
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendDelBtsResp()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn fills and send Del Bts Response to CFG.
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendDelBtsResp(I_Void)
{
  OamsBichCfgDelBicResp *msgPtr = (OamsBichCfgDelBicResp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCfgDelBicResp) );
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr )
  {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicId   = GET_BTS_ID();
  msgPtr->result  = getProcResult();


  /* msgPtr->cause is not being used */

  OUTPUT_MSG( OAMS_BICH_CFG_DEL_BIC_RESP, ENT_OAMS_CFG );  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendLockIndToTrx()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends Lock request to all Child Trx
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLockIndToTrx(I_Void)
{
   OamsBichTrxhLockInd    *msgPtr  = NULL;
   I_U32                  index    = 0;
   I_U32                  trxId;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  for (index = 0; index < MAX_NUM_OF_CHILD_TRX; index++)
  {
     if( !(trxId  = GET_CHILD_TRX_ID(index) ))
     {
        LOG_PRINT(INFO," No TRX is Present for BIC[%d] at Position[%d]",GET_BTS_ID(), index);
        continue;
     } 
     msgPtr = (OamsBichTrxhLockInd *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTrxhLockInd) );
     if (!msgPtr )
     {    
       LOG_PRINT(CRITICAL,"Could Not allocate memory");
       return ;
     }
     msgPtr->ptrxId  = trxId;
     msgPtr->bicId   = GET_BTS_ID();

     LOG_PRINT(DEBUG,"Sending OAMS_BICH_TRXH_LOCK_IND for TRX[%d]",trxId);
     OUTPUT_MSG(OAMS_BICH_TRXH_LOCK_IND,ENT_OAMS_TRXH); 
  }
  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendLockBtsResp()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and send Lock Request response to CFG
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLockBtsResp(I_Void)
{
  OamsBichCfgLockResp *msgPtr = (OamsBichCfgLockResp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCfgLockResp) );
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr )
  {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicId   = GET_BTS_ID();
  msgPtr->result  = getProcResult();

  /* msgPtr->cause is not being used */

  OUTPUT_MSG(OAMS_BICH_CFG_LOCK_RESP,ENT_OAMS_CFG);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : updBichContxtFromOperStateChange()
Parameters    : None
Return type   : I_Void
Purpose       : This func update the Child Trx operation state in it Bich Context
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void updBichContxtFromOperStateChange(I_Void)
{
   I_U32 index;

   OamsTrxhBichOperStateChangeInd *msgPtr = (OamsTrxhBichOperStateChangeInd *)GET_RCVD_MSG_PTR();
   LOG_PRINT(INFO,"Enter [%s]",__func__);
   LOG_PRINT(INFO,"Received OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND from TRX[%d] with OperState[%d]"
                 , msgPtr->ptrxId, msgPtr->operState);

   for ( index=0; index<MAX_NUM_OF_CHILD_TRX; index++ )
   {
      if ( GET_CHILD_TRX_ID(index) == msgPtr->ptrxId)
      {
         LOG_PRINT(DEBUG,"Setting TRX[%d]  state as %d",msgPtr->ptrxId, msgPtr->operState);
         SET_CHILD_TRX_OPR_STATE(index,msgPtr->operState);
         return;
      }
   }
   LOG_PRINT(INFO,"Exit [%s]",__func__);
   LOG_PRINT(MAJOR,"TRX[%d] received in OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND is not CHILD of BTS/BIC[%d]"
                  ,msgPtr->ptrxId,GET_BTS_ID());
}



/******************************* Function  Header*****************************
  Function Name : fillAndSendUnlockIndToTrx()
Parameters    : None
Return type   : I_Void
Purpose       : This func fills and sends Unlock Indication to all Child Trx
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendUnlockIndToTrx(I_Void)
{
   OamsBichTrxhUnlockInd      *msgPtr;
   I_U32                      index     = 0;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  for (index = 0; index < MAX_NUM_OF_CHILD_TRX; index++)
  {
     if ( GET_CHILD_TRX_ID(index) != ZERO )
     {
        msgPtr = (OamsBichTrxhUnlockInd *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTrxhUnlockInd) );
        if (!msgPtr )
        {    
           LOG_PRINT(CRITICAL,"Could Not allocate memory");
           return ;
        }
        msgPtr->ptrxId   = GET_CHILD_TRX_ID(index);
        msgPtr->bicId    = GET_BTS_ID();

        LOG_PRINT(DEBUG,"Sending OAMS_BICH_TRXH_UNLOCK_IND to TRX[%d]", msgPtr->ptrxId);
        OUTPUT_MSG(OAMS_BICH_TRXH_UNLOCK_IND,ENT_OAMS_TRXH); 
     }
     else
     {
        LOG_PRINT(DEBUG,"No Child TRX present at Position[%d]", index);
     }
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendUnlockBtsResp()
Parameters    : None
Return type   : I_Void
Purpose       : This func fills and sends Unlock Response to CFG
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendUnlockBtsResp(I_Void)
{
  OamsBichCfgUnlockResp *msgPtr = (OamsBichCfgUnlockResp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCfgUnlockResp) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr )
  {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicId   = GET_BTS_ID();
  msgPtr->result  = OAMS_RSLT_SUCCESS;

  /* msgPtr->cause is not being used */

  OUTPUT_MSG (OAMS_BICH_CFG_UNLOCK_RESP, ENT_OAMS_CFG);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendLinkDownToCcuh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fills and sends Bts/Bic Lapd down message to CCUH
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLinkDownToCcuh(I_Void)
{
  OamsBichCcuhLapdLinkDown *msgPtr = (OamsBichCcuhLapdLinkDown *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCcuhLapdLinkDown) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr )
  {    
     LOG_PRINT(CRITICAL,"Could Not allocate memory");
     return ;
  }
  
  msgPtr->bicTei  = GET_BTS_TEI();
  msgPtr->bicId   = GET_BTS_ID();
  msgPtr->sapi    = SAPI62;

  OUTPUT_MSG(OAMS_BICH_CCUH_LAPD_LINK_DOWN,ENT_OAMS_CCUH);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendLinkDownToSwmh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fills and sends Bic/Bts Lapd down message to Swmh
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLinkDownToSwmh(I_Void)
{
  OamsBichSwmhLapdLinkDown *msgPtr = (OamsBichSwmhLapdLinkDown *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichSwmhLapdLinkDown) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr ) 
  {    
     LOG_PRINT(CRITICAL,"Could Not allocate memory");
     return ;
  }
  if ( GET_BTS_TYPE() == BIC )
     msgPtr->nodeType      = SYS_NODE_TYPE_BIC;
  else
     msgPtr->nodeType      = SYS_NODE_TYPE_R2_BTS;

  msgPtr->nodeIdentity  = GET_BTS_ID();

  OUTPUT_MSG(OAMS_BICH_SWMH_LAPD_LINK_DOWN,ENT_OAMS_SWMH);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendLapdDiscIndToTrxh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends Bts/Bic lapd down indication to Child Trx
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLapdDiscIndToTrxh(I_Void)
{
   OamsBichTrxhLapdDiscInd  *msgPtr  = NULL;
   I_U32                    index    = 0;
   I_U32                    lapdStatus;
   I_S32                    errCode   = CLIB_SUCCESS;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  for (index = 0; index < MAX_NUM_OF_CHILD_TRX; index++)
  {
     if ( GET_CHILD_TRX_ID(index) != ZERO )
     {
        msgPtr = (OamsBichTrxhLapdDiscInd *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTrxhLapdDiscInd) );
        if (!msgPtr )
        {    
           LOG_PRINT(CRITICAL,"Could Not allocate memory");
           return ;
        }
        msgPtr->ptrxId   = GET_CHILD_TRX_ID(index);
        msgPtr->bicId    = GET_BTS_ID();

        LOG_PRINT(DEBUG,"Sending OAMS_BICH_TRXH_LAPD_DISCONNECT_IND to TRX[%d]", GET_CHILD_TRX_ID(index));
        OUTPUT_MSG(OAMS_BICH_TRXH_LAPD_DISCONNECT_IND,ENT_OAMS_TRXH); 

     }
     else
     {
        LOG_PRINT(DEBUG,"No Child TRX present at Position[%d]", index);

     }
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendLapdDiscIndForBts()
Parameters    : None
Return type   : bicTei
Purpose       : This func fill and sends Bts/Bic lapd disc message to Abihm
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLapdDiscIndForBts(BicTei bicTei) /*Changes for #19948*/
{
  OamsBichAbihmLinkDiscReq *msgPtr  = ALLOC_IPC_MSG_BUF(sizeof (OamsBichAbihmLinkDiscReq) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);

  if(!msgPtr) {
    LOG_PRINT(CRITICAL,"Could Not allocate memory \n");
    return;
  }
  
  msgPtr->bicTei = bicTei;
  msgPtr->sapi   = SAPI62;

  OUTPUT_MSG(OAMS_TRXH_ABIHM_LINK_DISC_REQ,ENT_CSAPP_ABIHM);/*tobechanged msgtype 19948*/ 

  LOG_PRINT(INFO,"Exit [%s]",__func__);
}
      
/******************************* Function  Header*****************************
  Function Name : updBichContxtFromBicHello()
Parameters    : None
Return type   : I_Void
Purpose       : This function update Bich context based on Bich Hello message
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void updBichContxtFromBicHello(I_Void)
{
  CsappAbihmBichBicHello *csappAbihmBichBicHello;
  CsappAbihmBichBmHello *csappAbihmBichBmHello;
  I_U8 alarmString[150];

  
  LOG_PRINT(INFO,"Enter [%s]",__func__);

  if ( GET_MSG_TYPE() == CSAPP_ABIHM_BICH_BIC_HELLO )
  {
     csappAbihmBichBicHello = (CsappAbihmBichBicHello *)GET_RCVD_MSG_PTR();
     gOamsBichContextPtr->parentBicId   = ZERO;
     gOamsBichContextPtr->upStreamPort  = ZERO;

     if (  gOamsBichContextPtr->btsType == R2_BTS )
     {
        sprintf(alarmString,"BIC[%u] BTS Type Mismatch Reported BtsType: [%d] Config BtsType: [%d]",
            GET_BTS_ID(), BIC, GET_BTS_TYPE()
	       );
        strcat(alarmString, "\0");

        LOG_PRINT(INFO,"BIC[%d] is configured as R2_BTS, so discarding BIC_HELLO", GET_BTS_ID() );
        SET_PROC_RESULT(eInternal,OAMS_RSLT_FAILURE);
        fillAndSendBichCfgAlarmInd( EVENT_BTS_TYPE_MISMATCH, TRAP_SEVERITY_MAJOR, alarmString); 

     }
  }
  else
  {
     csappAbihmBichBmHello = (CsappAbihmBichBmHello *)GET_RCVD_MSG_PTR();
     gOamsBichContextPtr->parentBicId   = ZERO;
     gOamsBichContextPtr->upStreamPort  = ZERO;
     /*Changed for mantis #0032378 Gaurav Sinha 10 Nov 2016*/
     //LOG_PRINT(INFO,"BTSTYPE[%s] reported in BM_HELLO",&csappAbihmBichBmHello->btsHwDescription.btsEquipmentType.btsEqpmtTypeInfo);
     I_U8 btsTypeLocal = ZERO;
     //if(strcmp(&csappAbihmBichBmHello->btsHwDescription.btsEquipmentType.btsEqpmtTypeInfo,"R3-PICO") == 0)
     if(csappAbihmBichBmHello->btsHwDescription.btsEquipmentType.btsEqpmtTypeLen == SEVEN)
     {
       btsTypeLocal = R3_BTS; 
       LOG_PRINT(INFO,"BTS[%d] BTSTYPE[%d] [R3_BTS] reported in BM_HELLO", GET_BTS_ID(),btsTypeLocal );
     }
     //if(strcmp(&csappAbihmBichBmHello->btsHwDescription.btsEquipmentType.btsEqpmtTypeInfo,"R2-IP-BTS") == 0)
     if(csappAbihmBichBmHello->btsHwDescription.btsEquipmentType.btsEqpmtTypeLen == NINE)
     {
       btsTypeLocal = R2_BTS_IP;
       LOG_PRINT(INFO,"BTS[%d] BTSTYPE[%d] [R2_BTS_IP] reported in BM_HELLO", GET_BTS_ID(),btsTypeLocal );
     }
     /*Changed for mantis #0032378 Gaurav Sinha 10 Nov 2016*/
     //if (  GET_BTS_TYPE() == BIC )
     if (  GET_BTS_TYPE() != btsTypeLocal)
     {
        sprintf(alarmString,"BIC[%u] BTS Type Mismatch Reported BtsType: [%d] Config BtsType: [%d]",
            //GET_BTS_ID(), R2_BTS, GET_BTS_TYPE() 
            GET_BTS_ID(), btsTypeLocal, GET_BTS_TYPE() //0032378 
             );
        strcat(alarmString, "\0");
       if(gOamsBichContextPtr->btsType == R3_BTS)
       {
        LOG_PRINT(INFO,"BTS[%d] is configured as R3-BTS, so discarding BM_HELLO", GET_BTS_ID() );
       }
       if(gOamsBichContextPtr->btsType == R2_BTS_IP)
       {
        LOG_PRINT(INFO,"BTS[%d] is configured as R2-BTS, so discarding BM_HELLO", GET_BTS_ID() );
       }
     /*Changed for mantis #0032378 Gaurav Sinha 10 Nov 2016*/

        //LOG_PRINT(INFO,"BIC[%d] is configured as BIC, so discarding BM_HELLO", GET_BTS_ID() ); //0032378
        SET_PROC_RESULT(eInternal,OAMS_RSLT_FAILURE);
        fillAndSendBichCfgAlarmInd( EVENT_BTS_TYPE_MISMATCH, TRAP_SEVERITY_MAJOR, alarmString); 
        fillAndSendLockIndToTrx();  //Changed for mantis #0032378 #0032377 Gaurav Sinha 22 Nov 2016
     }
               /*PCU REL 2.5 CHANGES BEGIN */
     /*Added for R3 BTS starts*/
     else
     {
       gOamsBichContextPtr->IpAdd.AAA = csappAbihmBichBmHello->btsIpAddrV4.AAA; 
       gOamsBichContextPtr->IpAdd.BBB = csappAbihmBichBmHello->btsIpAddrV4.BBB; 
       gOamsBichContextPtr->IpAdd.CCC = csappAbihmBichBmHello->btsIpAddrV4.CCC; 
       gOamsBichContextPtr->IpAdd.DDD = csappAbihmBichBmHello->btsIpAddrV4.DDD; 
       gOamsBichContextPtr->UdpPort   = csappAbihmBichBmHello->btsUdpPort;

       if(GET_BTS_TYPE() != R2_BTS)
       {
         /* R2.8 Changes Start */
         gOamsBichContextPtr->numberOfTrx = csappAbihmBichBmHello->btsProdNum.productNumberInfo[0];
         gOamsBichContextPtr->localSwitchingSupport = csappAbihmBichBmHello->btsLocation.locationInfo[0];
         LOG_PRINT(INFO,"BIC has numberOfTrx %d and localSwitchingSupport %d",  gOamsBichContextPtr->numberOfTrx,gOamsBichContextPtr->localSwitchingSupport);
         /* R2.8 Changes End */
       }
     }
    /*Added for R3 BTS ends*/
  }
  
         
  LOG_PRINT(INFO,"[E1Id: %d E1Ts: %d BtsId: %u BtsType: %u] BicHello/BtsHello rcvd ",
                 GET_BTS_TRUNK(),
                 GET_BTS_TRUNK_TS(),
                 GET_BTS_ID(),
                 GET_BTS_TYPE());
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : checkParamInBicHello()
Parameters    : None
Return type   : I_Void
Purpose       : This function validiates that Bich Hello is rcvd by the correct instance
incase it is not the correct raised alarm/event and ignore the message.
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void checkParamInBicHello(I_Void)
{
   BicE1TeiMapTableIndices      bicE1TeiMapTableIndices;
   BicE1TeiMapTableApi          *bicE1TeiMapTableApi;
   BicStatusTableIndices        bicStatusTableIndices;
   BicStatusTableApi            *pBicStatusTableApi = NULL ;
   BicStatusTableApi            setBicStatusTableApi ;
   I_U32                        reportedE1Id;
   I_U32                        reportedLapdTs;
   I_S32                        errCode;
   I_U8                         alarmString[150];
   CsappAbihmBichBmHello        *csappAbihmBichBmHello;   
   BicTableIndices              bicTableIndx = {0};
   BicTableApi                  *pBicTableApi = NULL;
   
   LOG_PRINT(INFO,"Enter [%s]",__func__);

   switch ( GET_MSG_TYPE() ) {
     case CSAPP_ABIHM_BICH_BIC_HELLO :
      bicE1TeiMapTableIndices.bicTei = ((CsappAbihmBichBicHello *)GET_RCVD_MSG_PTR())->bicTei;       
      break;

     case CSAPP_ABIHM_BICH_BM_HELLO :
      bicE1TeiMapTableIndices.bicTei = ((CsappAbihmBichBmHello *)GET_RCVD_MSG_PTR())->bicTei;       

      /* LCLS Change Start */
      csappAbihmBichBmHello = (CsappAbihmBichBmHello *)GET_RCVD_MSG_PTR();
      /* Update BTS Status Table for received BtsId */
      bicStatusTableIndices.bicId = csappAbihmBichBmHello->btsId;
      
      errCode = getBicStatusTable(&bicStatusTableIndices, &pBicStatusTableApi);
      if (errCode != CLIB_SUCCESS)
      {
        LOG_PRINT(INFO,"BTS Status Record Not Present for BTS ID: %u", bicStatusTableIndices.bicId );
        return;
      }
      else 
      {
        LOG_PRINT(INFO,"[%s] getBicStatusTable Success for BtsId: %u", __func__, bicStatusTableIndices.bicId);
        memcpy((I_U8*)(&setBicStatusTableApi),(I_U8*)pBicStatusTableApi,sizeof(BicStatusTableApi));
        
        /* Get record from BTS Table to check it's BtsType */
        bicTableIndx.bicId = bicStatusTableIndices.bicId;
        errCode = getBicTable(&bicTableIndx, &pBicTableApi);
        if (errCode != CLIB_SUCCESS)
        {
          LOG_PRINT(INFO,"BTS Record Not Present for BTS ID: %u", bicTableIndx.bicId );
          return;
        }

        if ((pBicTableApi->btsType == BIC) || (pBicTableApi->btsType == R2_BTS))
        {
          /* TDM BTS case */
          setBicStatusTableApi.maxStepsSize = NUM_PC_STEPS_TRX;
          setBicStatusTableApi.clockSource = CLK_NOT_APPLICABLE;
          LOG_PRINT(INFO,"BTS: %u is TDM BTS with Type: %u", bicTableIndx.bicId, pBicTableApi->btsType);
        }
        else
        {
          /* IP BTS case */
          LOG_PRINT(INFO,"BTS: %u is IP BTS with Type: %u", bicTableIndx.bicId, pBicTableApi->btsType);
          LOG_PRINT(INFO,"ClockSource rcvd = %u, MaxStepsSize rcvd PrsntFlag: %u, Value = %u",
              csappAbihmBichBmHello->clockSource, csappAbihmBichBmHello->isMaxStepsSizePresent, csappAbihmBichBmHello->maxStepsSize);
          /* Check if Max Steps Size is Present, store it otherwise set it to '0' */
          if (csappAbihmBichBmHello->isMaxStepsSizePresent)
          {
            setBicStatusTableApi.maxStepsSize = csappAbihmBichBmHello->maxStepsSize;
          }
          else
          {
            setBicStatusTableApi.maxStepsSize = NUM_PC_STEPS_TRX;
          }
          /* Store Clock Source as received */
          setBicStatusTableApi.clockSource = csappAbihmBichBmHello->clockSource;
        }

        LOG_PRINT(INFO,"Updating BtsStatusTable with ClkSrc: %u, MaxStepsSize: %u",
            setBicStatusTableApi.clockSource, setBicStatusTableApi.maxStepsSize);

        /* Now Update the BTS Status Table */
        if (CLIB_SUCCESS == updateBicStatusTable(&setBicStatusTableApi))
        {
          LOG_PRINT(INFO, "BicStatusTable Updated Successfully");
        }
        else
        {
          LOG_PRINT(INFO, "BicStatusTable Update Failed");
        }

        /* set satFlag in BicTable - for handling AMR-FR in satellite sites - R2.9 */
        LOG_PRINT(INFO,"btsAbisType for this BTS id %u in BM_HELLO is %u", bicTableIndx.bicId, csappAbihmBichBmHello->btsAbisType);

        if(csappAbihmBichBmHello->btsAbisType == TB_BTS_ABIS_TYPE_SATELLITE)
        {
            pBicTableApi->satFlag = 0x01;
        }
        else
        {
            pBicTableApi->satFlag = 0x00;
        }  

        LOG_PRINT(INFO,"satFlag for this BTS id %u is %u", bicTableIndx.bicId, pBicTableApi->satFlag);

        errCode = updateBicTable(pBicTableApi);
        if (errCode != CLIB_SUCCESS)
        {
          LOG_PRINT(CRITICAL,"Failure in updating satFlag in BicTable for BTS ID: %u", bicTableIndx.bicId );
          return;
        }

        free(pBicTableApi);
        free(pBicStatusTableApi);
      }
      /* Update BTS Context */
      SET_BTS_MAX_STEPS_SIZE(csappAbihmBichBmHello->maxStepsSize);
      SET_BTS_CLOCK_SOURCE(csappAbihmBichBmHello->clockSource);
      /* LCLS Change End */
      break;
   }   

   errCode=getBicE1TeiMapTable(&bicE1TeiMapTableIndices,&bicE1TeiMapTableApi);

   if( errCode == CLIB_SUCCESS )    
   {
      reportedE1Id    = bicE1TeiMapTableApi->e1Id ;
      reportedLapdTs  = bicE1TeiMapTableApi->e1Ts ;
      if (reportedE1Id != GET_BTS_TRUNK())
      {
         sprintf(alarmString,"BIC[%u]E1 Mismatch[Reported E1: %d][Config E1:%d]",GET_BTS_ID() , 
             bicE1TeiMapTableApi->e1Id,GET_BTS_TRUNK());
        strcat(alarmString, "\0");
        fillAndSendBichCfgAlarmInd( EVENT_BIC_E1_MISMATCH, TRAP_SEVERITY_MAJOR, alarmString); 

        SET_PROC_RESULT(eInternal,BIC_E1_MISMATCH);
      }
      else if (reportedLapdTs != GET_BTS_TRUNK_TS())
      {
        sprintf(alarmString,"BIC[%u]LAPD Ts Mismatch[Reported Ts:%d][Allocated Ts:%d]", 
            GET_BTS_ID(),bicE1TeiMapTableApi->e1Ts,GET_BTS_TRUNK_TS());
        strcat(alarmString, "\0");
        fillAndSendBichCfgAlarmInd( EVENT_BIC_LAPD_TS_MISMATCH, TRAP_SEVERITY_MAJOR, alarmString); 

        SET_PROC_RESULT(eInternal,BIC_LAPD_TS_MISMATCH);
      }
      free(bicE1TeiMapTableApi) ;
      LOG_PRINT(INFO,"[%s] [E1:%d Ts: %d BtsId: %u BtsTei: %d] From Hello",
                __func__,
                reportedE1Id,
                reportedLapdTs,
                GET_BTS_ID(),
                bicE1TeiMapTableIndices.bicTei);      
  }
  else
  {
     LOG_PRINT(MAJOR,"Error in getBicE1TeiMapTable: err = %s",clib_strerror(errCode));
     SET_PROC_RESULT(eDbs,errCode );
  }
  
LOG_PRINT(INFO,"Exit [%s]",__func__)
}



/******************************* Function  Header*****************************
  Function Name : updSwVersionFromBicHello()
Parameters    : None
Return type   : I_Void
Purpose       : This function update Sw verion in Bich context as reported in Bich Hello
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void updSwVersionFromBicHello(I_Void)
{
  CsappAbihmBichBicHello  *msgPtr;
  CsappAbihmBichBmHello   *bmMsgPtr;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( GET_MSG_TYPE() == CSAPP_ABIHM_BICH_BIC_HELLO )
  {
     msgPtr = (CsappAbihmBichBicHello *)GET_RCVD_MSG_PTR();
     gOamsBichContextPtr->swDes.len = msgPtr->swDes.len;
     strcpy(gOamsBichContextPtr->swDes.fileVer, msgPtr->swDes.fileVer);
      if (msgPtr->isInactiveSwDesPresent == I_TRUE)
      {
         gOamsBichContextPtr->isBicSwDesInActiveSwPresent = I_TRUE ;
         gOamsBichContextPtr->inactiveSwDes.len = msgPtr->inactiveSwDes.len;
         strcpy(gOamsBichContextPtr->inactiveSwDes.fileVer, msgPtr->inactiveSwDes.fileVer) ;
         LOG_PRINT(INFO,"BIC inactiveSwDes: len=%d inactiveSwDescription= %s\n", 
                     gOamsBichContextPtr->inactiveSwDes.len,
                     gOamsBichContextPtr->inactiveSwDes.fileVer);
      }
      else
      {
         gOamsBichContextPtr->isBicSwDesInActiveSwPresent = I_FALSE ;
      }
  }
  else
  {
     bmMsgPtr = (CsappAbihmBichBmHello *)GET_RCVD_MSG_PTR();
     gOamsBichContextPtr->swDes.len = bmMsgPtr->btsActiveSwDes.len;
     strcpy(gOamsBichContextPtr->swDes.fileVer, bmMsgPtr->btsActiveSwDes.fileVer);
     if (bmMsgPtr->isInactiveSwDesPresent == I_TRUE)
     {
         gOamsBichContextPtr->isBicSwDesInActiveSwPresent = I_TRUE ;
         gOamsBichContextPtr->inactiveSwDes.len = bmMsgPtr->btsInactiveSwDes.len;
         strcpy(gOamsBichContextPtr->inactiveSwDes.fileVer, bmMsgPtr->btsInactiveSwDes.fileVer) ;
         LOG_PRINT(INFO,"BIC inactiveSwDes: len=%d inactiveSwDescription= %s\n", 
                     gOamsBichContextPtr->inactiveSwDes.len,
                     gOamsBichContextPtr->inactiveSwDes.fileVer);
      }
      else
      {   
         gOamsBichContextPtr->isBicSwDesInActiveSwPresent = I_FALSE ;
      }
 
  }

  LOG_PRINT(INFO,"BIC ActiveSwDescription: len=%d Description= %s\n", 
                 gOamsBichContextPtr->swDes.len,gOamsBichContextPtr->swDes.fileVer);
        
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendBicHelloToSwmh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends Bich Hello to Swmh module
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendBicHelloToSwmh(I_Void)
{
  OamsBichSwmhBicHello * msgPtr; //OamsBichSwmhBicHello and OamsBichSwmhBmHello struct are same 

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  msgPtr = (OamsBichSwmhBicHello *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichSwmhBicHello) );

  if (!msgPtr )
  {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }

  msgPtr->bicTei                = GET_BTS_TEI();
  msgPtr->nodeIdentity          = GET_BTS_ID();
  msgPtr->swDesActiveSw.len     = gOamsBichContextPtr->swDes.len;

  LOG_PRINT(INFO,"BIC swDesActiveSw: len=%d", msgPtr->swDesActiveSw.len);

  strcpy(msgPtr->swDesActiveSw.fileVer,gOamsBichContextPtr->swDes.fileVer);
  LOG_PRINT(INFO,"BIC swDesActiveSw: %s", msgPtr->swDesActiveSw.fileVer);

  if(gOamsBichContextPtr->isBicSwDesInActiveSwPresent  == I_TRUE)
  {    
    msgPtr->isBicSwDesInActiveSwPresent     = I_TRUE ;
    msgPtr->swDesInActiveSw.len             = gOamsBichContextPtr->inactiveSwDes.len;
    LOG_PRINT(INFO,"BIC inactiveSwDes: len=%d", msgPtr->swDesInActiveSw.len);

    strcpy(msgPtr->swDesInActiveSw.fileVer,gOamsBichContextPtr->inactiveSwDes.fileVer);
    LOG_PRINT(INFO,"BIC inactiveSwDes: %s",msgPtr->swDesInActiveSw.fileVer);
  }
  else
  {
    msgPtr->isBicSwDesInActiveSwPresent = I_FALSE ;
  }
   LOG_PRINT(INFO,"[E1 Id:%d E1Ts: %d BicId: %u]Returning from prepareOamsBichSwmhBicHello",
                  GET_BTS_TRUNK(),GET_BTS_TRUNK_TS(),GET_BTS_ID());

  if ( GET_MSG_TYPE() == CSAPP_ABIHM_BICH_BIC_HELLO )
  {
     msgPtr->nodeType = SYS_NODE_TYPE_BIC;
     OUTPUT_MSG(OAMS_BICH_SWMH_BIC_HELLO,ENT_OAMS_SWMH);  
  }
  else
  {
    switch(gOamsBichContextPtr->btsType){
      case R2_BTS     :
        msgPtr->nodeType =SYS_NODE_TYPE_R2_BTS;
        break; 
      case R3_BTS     :
        msgPtr->nodeType =SYS_NODE_TYPE_R3_BTS;
        break; 
      case R2_BTS_IP  :
        msgPtr->nodeType =SYS_NODE_TYPE_R2_BTS_IP;
        break; 
    }
    OUTPUT_MSG(OAMS_BICH_SWMH_BM_HELLO,ENT_OAMS_SWMH);  
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendLinkEstabReq()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends Lapd Link Estab request to ABIHM
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLinkEstabReq(I_Void)
{
  OamsBichAbihmLinkEstabReq *msgPtr = ALLOC_IPC_MSG_BUF(sizeof (OamsBichAbihmLinkEstabReq) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr ) 
  {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicTei = GET_BTS_TEI() ;
  msgPtr->sapi = SAPI62;

  OUTPUT_MSG(OAMS_BICH_ABIHM_LINK_EST_REQ, ENT_CSAPP_ABIHM);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendLinkUpToCcuh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends Link Up indication to Ccuh 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendLinkUpToCcuh(I_Void)
{
  OamsBichCcuhLapdLinkUp *msgPtr = (OamsBichCcuhLapdLinkUp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichCcuhLapdLinkUp) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if (!msgPtr )
  {    
    LOG_PRINT(CRITICAL,"Could Not allocate memory");
    return ;
  }
  
  msgPtr->bicTei  = GET_BTS_TEI();
  msgPtr->bicId   = GET_BTS_ID();
  msgPtr->sapi    = SAPI62;

  OUTPUT_MSG(OAMS_BICH_CCUH_LAPD_LINK_UP,ENT_OAMS_CCUH);  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendBscBicCfgReq()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends BscBichCfg request to ABIHM
Other Note    : Added For BSC R22
 *****************************************************************************/
/* I_Void fillAndSendBscBicCfgReq(I_Void)
{

   struct tm *local_time;
   time_t currentTime;
   I_S8 str[20];

   I_U32 len;
   OamsBichAbihmBscBicCfgReq *msgPtr ;

   LOG_PRINT(INFO,"Enter [%s]",__func__);
   currentTime = time( &currentTime);
   if( currentTime == ((time_t)-1))
   {
      LOG_PRINT(INFO,"Retrieval of current time failed using API time()");
      return;
   }
   local_time = localtime((const time_t*)(&currentTime));
   LOG_PRINT(INFO,"Current Time is: ");
   len = strftime(str,20,"%d:%m:%y:%H:%M:%S",local_time);
   strcat(str,"\0");

   LOG_PRINT(INFO,"%s",str);
   LOG_PRINT(INFO,"Length is %d",strlen(str));

   msgPtr = (OamsBichAbihmBscBicCfgReq *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichAbihmBscBicCfgReq) );
   if (!msgPtr )
   {    
     LOG_PRINT(CRITICAL,"Could Not allocate memory");
     return ;
   }
   FILL_ABIS_HDR_FOR_BIC(msgPtr);
   msgPtr->isAbsTimePresent = I_TRUE;
   msgPtr->isEpochTimePresent = I_TRUE; // Added From CS2.4 Having tag BSC-7.0.3.013 
   msgPtr->bicTei = GET_BTS_TEI();
   // Added From CS2.4 Having tag BSC-7.0.3.013 - Begin
   msgPtr->placementInd = PLACEMENT_IND;
   msgPtr->seqNum= SEQUENCE_NUM;
   msgPtr->objClass = OBJECT_CLASS;
   msgPtr->objInstance.bicObjInst[0] = OBJECT_INST_OCTET1;
   msgPtr->objInstance.bicObjInst[1] = OBJECT_INST_OCTET2;
   msgPtr->objInstance.bicObjInst[2] = OBJECT_INST_OCTET3;
   // Added From CS2.4 Having tag BSC-7.0.3.013 - End
   msgPtr->bicId =GET_BTS_ID();
   strcpy(msgPtr->absTime.absTimeInfo, str);
   msgPtr->epochTime = currentTime;

   OUTPUT_MSG(OAMS_BICH_ABIHM_BSC_BIC_CFG_REQ,ENT_CSAPP_ABIHM);  

   LOG_PRINT(INFO,"Exit [%s]",__func__);
}
*/
/*PCU Rel 2.5 Changes Start */

/******************************* Function  Header*****************************
Function Name : fillAndSendDelBtsIpToTB()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends request to TB
Other Note    : Added For BSC R22
*****************************************************************************/
I_Void fillAndSendDelBtsIpToTB(I_Void)
{

     OamsBichTbDelBtsIp *msgPtr = (OamsBichTbDelBtsIp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTbDelBtsIp));
     LOG_PRINT(INFO,"Enter [%s]",__func__);
     if (!msgPtr )
     {     
        LOG_PRINT(CRITICAL,"Could Not allocate memory");
        return ;
     }
     msgPtr->btsApplTei  = GET_BTS_TEI();
     OUTPUT_MSG(OAMS_BICH_TB_DEL_BTS_IP,ENT_PSAPP_TBBSC);  
     LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
Function Name : fillAndSendAddBtsIpToTB()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends request to TB
Other Note    : Added For BSC R22
*****************************************************************************/
I_Void fillAndSendAddBtsIpToTB(I_Void)
{

     OamsBichTbAddBtsIp *msgPtr = (OamsBichTbAddBtsIp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTbAddBtsIp));
     LOG_PRINT(INFO,"Enter [%s]",__func__);
     if (!msgPtr )
     {    
        LOG_PRINT(CRITICAL,"Could Not allocate memory");
        return ;
     }
     msgPtr->btsApplTei = GET_BTS_TEI();
     msgPtr->btsId      = GET_BTS_ID(); 
     msgPtr->btsIp.AAA  =  gOamsBichContextPtr->IpAdd.AAA ;
     msgPtr->btsIp.BBB  =  gOamsBichContextPtr->IpAdd.BBB ;
     msgPtr->btsIp.CCC  =  gOamsBichContextPtr->IpAdd.CCC ;
     msgPtr->btsIp.DDD  =  gOamsBichContextPtr->IpAdd.DDD ;
     msgPtr->btsUdpPort =  gOamsBichContextPtr->UdpPort;
     msgPtr->btsType    =  gOamsBichContextPtr->btsType;
     LOG_PRINT(CRITICAL,"sending message size : %d",gOamsBichContextPtr->sendMsgSize);
     OUTPUT_MSG(OAMS_BICH_TB_ADD_BTS_IP,ENT_PSAPP_TBBSC);
     LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
Function Name : fillAndSendIpLinkDownToTB()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends request to TB
Other Note    : Added For BSC R22
*****************************************************************************/
I_Void fillAndSendIpLinkDownToTB(I_Void)
{

     OamsBichTbIpLinkDown *msgPtr = (OamsBichTbIpLinkDown *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTbIpLinkDown));
     LOG_PRINT(INFO,"Enter [%s]",__func__);
     if (!msgPtr )
     {    
        LOG_PRINT(CRITICAL,"Could Not allocate memory");
        return ;
     }
     msgPtr->btsApplTei  = GET_BTS_TEI();
     OUTPUT_MSG(OAMS_BICH_TB_IP_LINK_DOWN,ENT_PSAPP_TBBSC);  
     LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
Function Name : fillAndSendIpLinkUpToTrxh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends request to Trxh
Other Note    : Added For BSC R22
*****************************************************************************/
I_Void fillAndSendIpLinkUpToTrxh(I_Void)
{
  
   I_U32         *ptrxId   = NULL;
   I_U32         trxCount  = 0;
   I_U32         i   ;
   OamsBichTrxhIpLinkUp *msgPtr;
    
   if (CLIB_SUCCESS != getAllPtrxTrxTable(GET_BTS_ID(), &ptrxId, &trxCount))
   {
      LOG_PRINT(INFO,"%s: getAllPtrxTrxTable failed for BTSID [%u]",__func__,GET_BTS_ID());
      LOG_PRINT(INFO,"%s: Child Trx Context is not updated",__func__);
      return;
   }
   LOG_PRINT(INFO,"Enter [%s]",__func__);
   for (i=0; i < trxCount; i++) 
   {
      msgPtr = (OamsBichTrxhIpLinkUp *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTrxhIpLinkUp));
      if (!msgPtr )
      {    
         LOG_PRINT(CRITICAL,"Could Not allocate memory");
         free(ptrxId);
         return ;
      }
      msgPtr->ptrxId  = ptrxId[i];
      OUTPUT_MSG(OAMS_BICH_TRXH_IP_LINK_UP,ENT_OAMS_TRXH);
   }
   free(ptrxId);
   LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
Function Name : fillAndSendIpLinkDownToTrxh()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends request to Trxh
Other Note    : Added For BSC R22
*****************************************************************************/
I_Void fillAndSendIpLinkDownToTrxh(I_Void)
{

   I_U32         *ptrxId   = NULL;
   I_U32         trxCount  = 0;
   I_U32         i  ;
   I_U32         ptrxList[MAX_NUM_TRX_PER_BTS] = {0};
   I_U8          ptrxBcchCount = 0;
   I_S32         retVal = I_FALSE;
   CellNonPerTableApi *pCellNonPerOutData=NULL;

   OamsBichTrxhIpLinkDown *msgPtr ;
 
   if (CLIB_SUCCESS != getAllPtrxTrxTable(GET_BTS_ID(), &ptrxId, &trxCount)) 
   {
      LOG_PRINT(INFO,"%s: getAllPtrxTrxTable failed for BTSID [%u]",__func__,GET_BTS_ID());
      LOG_PRINT(INFO,"%s: Child Trx Context is not updated",__func__);
      return;
   }
   LOG_PRINT(INFO,"Enter [%s]",__func__);
   for (i = 0; i < trxCount; i++)
   {
      retVal = checkBcchTrx(ptrxId[i],&pCellNonPerOutData);
      if(retVal == CLIB_SUCCESS)
      {
         ptrxBcchCount++;
         ptrxList[trxCount-ptrxBcchCount] = ptrxId[i];
         free(pCellNonPerOutData);
      }
      else
      {
         ptrxList[i-ptrxBcchCount] = ptrxId[i];
      }
   }
   for (i=0; i < trxCount; i++) 
   {
      msgPtr = (OamsBichTrxhIpLinkDown *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichTrxhIpLinkDown));
      if (!msgPtr )
      {    
         LOG_PRINT(CRITICAL,"Could Not allocate memory");
         free(ptrxId);
         return ;
      }
      msgPtr->ptrxId  = ptrxList[i];
         LOG_PRINT(DEBUG,"IP_LINK_DOWN for ptrxID %d",msgPtr->ptrxId);
      OUTPUT_MSG(OAMS_BICH_TRXH_IP_LINK_DOWN,ENT_OAMS_TRXH);  
   }
   free(ptrxId);
   LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
Function Name : fillAndSendIpLinkDownToAbihm()
Parameters    : None
Return type   : I_Void
Purpose       : This func fill and sends request to Abihm
Other Note    : Added For BSC R22
*****************************************************************************/
I_Void fillAndSendIpLinkDownToAbihm(I_Void)
{

   OamsBichAbihmIpLinkDown *msgPtr = (OamsBichAbihmIpLinkDown *)ALLOC_IPC_MSG_BUF(sizeof (OamsBichAbihmIpLinkDown));
   LOG_PRINT(INFO,"Enter [%s]",__func__);
   if (!msgPtr )
   {    
      LOG_PRINT(CRITICAL,"Could Not allocate memory");
      return ;
   }
  /* Mantis fix for 23967 */ 
   msgPtr->bicTei  = GET_BTS_TEI();
   msgPtr->placementInd              = PLACEMENT_IND;\
   msgPtr->seqNum                    = SEQUENCE_NUM;\
   msgPtr->objClass                  = 0x13 ; //TB there is no OBJECT  class defined for it  
   msgPtr->objInstance.bicObjInst[0] = 0xFF ; 
   msgPtr->objInstance.bicObjInst[1] = 0xFF ; 
   msgPtr->objInstance.bicObjInst[2] = 0xFF ;
  /* Mantis fix for 23967 */ 
   OUTPUT_MSG(OAMS_BICH_ABIHM_IP_LINK_DOWN,ENT_CSAPP_ABIHM);
   LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/*PCU Rel 2.5 Changes End */


/******************************* Function  Header*****************************
  Function Name : updBichContxtFromAddTrxInd()
Parameters    : None
Return type   : I_Void
Purpose       : This func update CHILD TRX operation state and also bic/bts operation 
state if needed 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void updBichContxtFromAddTrxInd(I_Void)
{
  OamsCfgBichAddTrxInd *msgPtr  = GET_RCVD_MSG_PTR();
  I_U32                index; 
  gOamsBichContextPtr->bicId       = msgPtr->bicId;

  LOG_PRINT(INFO,"Enter [%s]",__func__);

  for ( index=0; index < MAX_NUM_OF_CHILD_TRX; index++ )
  {
     if ( (GET_CHILD_TRX_ID(index) != ZERO) && (GET_CHILD_TRX_ID(index) == msgPtr->pTrxId) )
     {
        LOG_PRINT(DEBUG,"\n TRX[%d] received in ADD_TRX_IND already for present for BIC[%d] at Position[%d]", 
            msgPtr->pTrxId, GET_BTS_ID(), index);
        return;
     }
     if ( GET_CHILD_TRX_ID(index) == ZERO )
     {
         LOG_PRINT(DEBUG,"\n Adding TRX[%d] for BIC[%d] at Position[%d]", msgPtr->pTrxId, GET_BTS_ID(), index);
         ADD_CHILD_TRX(index,msgPtr->pTrxId);
         return;
     }
  }
  LOG_PRINT(MAJOR,"\n Unable to ADD TRX[%d] for BIC[%d]", msgPtr->pTrxId,GET_BTS_ID());
  LOG_PRINT(MAJOR,"\n MAX TRX's are already Present for BIC[%d]",  GET_BTS_ID());
  LOG_PRINT(INFO,"Exit [%s]",__func__);

}

/******************************* Function  Header*****************************
  Function Name : sendSlotConnectForTrx()
Parameters    : None
Return type   : I_Void
Purpose       : This func sends slot connect for Child Trx 
state if needed 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void sendSlotConnectForTrx(I_Void)
{
   OamsCfgBichAddTrxInd *msgPtr     = GET_RCVD_MSG_PTR();
   I_U8 *startTs                    = (I_U8*)MALLOC(sizeof(I_U8)); 
   I_U8 *lapdTs                     = (I_U8*)MALLOC(sizeof(I_U8)); 
   I_U8 *firstTsTraffic             = (I_U8*)MALLOC(sizeof(I_U8)); 
   I_U8 *secondTsTraffic            = (I_U8*)MALLOC(sizeof(I_U8)); 

   LOG_PRINT(INFO,"Enter [%s]",__func__);

   if(lapdTs == NULL || startTs == NULL || firstTsTraffic == NULL || secondTsTraffic == NULL)
   {
      LOG_PRINT(CRITICAL,"\n Memory Allocation failure for startTs or lapdTs or firstTsTraffic or secondTsTraffic");
      if(lapdTs != NULL)
         FREE(lapdTs);
      if(startTs != NULL)
         FREE(startTs);
      if( firstTsTraffic != NULL)
         FREE(firstTsTraffic);
      if( secondTsTraffic != NULL)
         FREE(secondTsTraffic);
      return;
    }

  
   if((getStartTs(&(msgPtr->pTrxId), ONE,startTs) && 
            getTrxTs(&(msgPtr->pTrxId), ONE,lapdTs, firstTsTraffic, secondTsTraffic) ) == BICH_FAILURE )
   {
      LOG_PRINT(CRITICAL,"getStartTs or getLapdTs function failed :exiting sendSlotConnectForTrx");
      FREE(lapdTs);
      FREE(startTs);
      FREE(firstTsTraffic);
      FREE(secondTsTraffic);
      return;
    }
    sendSlotConnectMsg(GET_BTS_ID(),GET_BTS_ID(),GET_BTS_ID(),ONE,GET_BTS_TEI(),
                       lapdTs,startTs,firstTsTraffic,secondTsTraffic);
    FREE(lapdTs);
    FREE(startTs);
    FREE(firstTsTraffic);
    FREE(secondTsTraffic);

    LOG_PRINT(INFO,"Exit [%s]",__func__);

}

/******************************* Function  Header*****************************
  Function Name : updBichContxtFromDelTrxInd()
Parameters    : None
Return type   : I_Void
Purpose       : This func removed the deleted Trx data from Bic context  
state if needed 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void updBichContxtFromDelTrxInd(I_Void)
{
  OamsCfgBichDelTrxInd *msgPtr = GET_RCVD_MSG_PTR();
  I_U32                index;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  
  for ( index=0; index < MAX_NUM_OF_CHILD_TRX; index++ )
  {
	  if ( GET_CHILD_TRX_ID(index) == msgPtr->pTrxId )
	  {
		  DEL_CHILD_TRX(index);
      return;
     }
  }
  LOG_PRINT(INFO,"\nTRX[%d] is not Child of BIC/BTS[%d]", msgPtr->pTrxId, GET_BTS_ID() )

  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamsBichAbihmBicCcPwrOrderReq()
Parameters    : None
Return type   : I_Void
Purpose       : This func fills and sends Ccu Power Order Request to Abihm
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void fillAndSendOamsBichAbihmBicCcPwrOrderReq(I_Void)
{
  OamsCfgBichBicPowerOrderReq   *rcvMsgPtr  = GET_RCVD_MSG_PTR();  
  OamsBichAbihmBicCcPwrOrderReq *sendMsgPtr = ALLOC_IPC_MSG_BUF(sizeof (OamsBichAbihmBicCcPwrOrderReq) );
  
  LOG_PRINT(INFO,"Enter [%s]",__func__);

  if(!rcvMsgPtr) {
    LOG_PRINT(CRITICAL,"Rcvr Msg Ptr is Null");
    return ;
  }

  if(!sendMsgPtr) {
    LOG_PRINT(CRITICAL,"Send Msg Ptr allocation fails");
    return ;
  }
  
  if (GET_BTS_TEI() != rcvMsgPtr->bicTei) {
    LOG_PRINT(INFO,"[%s] Expected TEI[%u] , rcvd TEI[%u]",__func__,GET_BTS_TEI(),rcvMsgPtr->bicTei);
    return ;
  }
 
  if (GET_BTS_LAPD_OPR_STATE() != LAPD_LINK_UP) {
    LOG_PRINT(INFO,"[%s] LAPD link is down ignoring....",__func__);
    return ;
  }
  FILL_ABIS_HDR_FOR_BIC(sendMsgPtr); 
  sendMsgPtr->bicId                     = GET_BTS_ID(); 
  sendMsgPtr->ccuId                     = 0xFF;
  sendMsgPtr->pwrActionType             = rcvMsgPtr->pwrActionType;
  sendMsgPtr->pwrEntity                 = rcvMsgPtr->pwrEntity;
  sendMsgPtr->pwrRestartTime            = 0xFF;
  sendMsgPtr->bicTei                    = rcvMsgPtr->bicTei;
  
  OUTPUT_MSG(OAMS_BICH_ABIHM_BIC_PWR_ORDER_REQ,ENT_CSAPP_ABIHM);  
  LOG_PRINT(INFO,"Enter [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendBicRestart()
Parameters    : None
Return type   : I_Void
Purpose       : This func fills and sends Power Order Request to Abihm to Restart BIC
Other Note    : Added For BSC R24
 *****************************************************************************/
I_Void fillAndSendBicRestart(I_Void)
{
  OamsBichAbihmBicCcPwrOrderReq *sendMsgPtr = ALLOC_IPC_MSG_BUF(sizeof (OamsBichAbihmBicCcPwrOrderReq) );

  LOG_PRINT(INFO,"Enter [%s]",__func__);

  if(!sendMsgPtr) {
    LOG_PRINT(CRITICAL,"Send Msg Ptr allocation fails");
    return ;
  }

  if (GET_BTS_LAPD_OPR_STATE() != LAPD_LINK_UP) {
    LOG_PRINT(INFO,"[%s] LAPD link is down ignoring....",__func__);
    return ;
  }
  FILL_ABIS_HDR_FOR_BIC(sendMsgPtr);
  sendMsgPtr->isCcuIdPresent            = I_FALSE;
  sendMsgPtr->placementInd              = PLACEMENT_IND;
  sendMsgPtr->seqNum                    = SEQUENCE_NUM;
  sendMsgPtr->objClass                  = OBJECT_CLASS;
  sendMsgPtr->objInstance.bicObjInst[0] = OBJECT_INST_OCTET1;
  sendMsgPtr->objInstance.bicObjInst[1] = OBJECT_INST_OCTET2;
  sendMsgPtr->objInstance.bicObjInst[2] = OBJECT_INST_OCTET3;
  sendMsgPtr->bicId                     = GET_BTS_ID();
  sendMsgPtr->pwrActionType             = PWR_ACTION_SOFT_RESET;
  sendMsgPtr->pwrEntity                 = PWR_ENTITY_BIC_ALL_TRX;
  sendMsgPtr->pwrRestartTime            = 0x01;
  sendMsgPtr->bicTei                    = GET_BTS_TEI();

  OUTPUT_MSG(OAMS_BICH_ABIHM_BIC_PWR_ORDER_REQ,ENT_CSAPP_ABIHM);
  LOG_PRINT(INFO,"Enter [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleBtsAlarmInd()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Alarm Indication rcvd from Bic/Bts
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleBtsAlarmInd(I_Void)
{
  CsappAbihmBichBicBscAlarmInd *msgPtr = GET_RCVD_MSG_PTR();
  LOG_PRINT(INFO,"Enter [%s]",__func__);  
  if (!msgPtr) {
    LOG_PRINT(INFO,"[%s]: rcvd msg Ptr is Null",__func__);
    return ;
  }
  switch ( msgPtr->alarmCause) {
    case CLK_SYN_IN_PROGRESS:
    {
      LOG_PRINT(INFO,"[%s:]BIC_BSC_ALARM_IND contain Alarm cause as CLK_SYN_IN_PROGRESS",__func__);
      fillAndSendBichCfgAlarmInd( EVENT_CLK_SYN_IN_PROGRESS, TRAP_SEVERITY_INFORMATION,"EVENT_CLK_SYN_IN_PROGRESS");
      break;
    }
    case CLK_SYN_SUCCESSFUL:
    {
      LOG_PRINT(INFO,"[%s:]BIC_BSC_ALARM_IND contain Alarm cause as CLK_SYN_SUCCESSFUL",__func__);
      fillAndSendBichCfgAlarmInd( EVENT_CLK_SYN_SUCCESSFUL, TRAP_SEVERITY_INFORMATION,"EVENT_CLK_SYN_SUCCESSFUL");
      break;
    }      
    case CLK_SYN_HOLD_OVER_MODE:
    {
      LOG_PRINT(INFO,"[%s]BIC_BSC_ALARM_IND contain Alarm cause as CLK_SYN_HOLD_OVER_MODE",__func__);
      fillAndSendBichCfgAlarmInd(EVENT_CLK_SYN_HOLD_OVER_MODE,TRAP_SEVERITY_INFORMATION,
                                 "EVENT_CLK_SYN_HOLD_OVER_MODE");
      break;
    }   
    case BIC_TRX_POWER_ON_STATE:
    {
      LOG_PRINT(INFO,"[%s:]BIC_BSC_ALARM_IND contain Alarm cause as BIC_TRX_POWER_ON_STATE",__func__);
      fillAndSendBichCfgAlarmInd(ALARM_BIC_TRX_POWER_ON_STATE,TRAP_SEVERITY_CLEARED,"ALARM_BIC_TRX_POWER_ON_STATE");
      break;
    }    
    case BIC_TRX_POWER_OFF_STATE:
    {
      LOG_PRINT(INFO,"[%s:]BIC_BSC_ALARM_IND contain Alarm cause as BIC_TRX_POWER_OFF_STATE",__func__);
      fillAndSendBichCfgAlarmInd(ALARM_BIC_TRX_POWER_OFF_STATE,TRAP_SEVERITY_MAJOR,"ALARM_BIC_TRX_POWER_OFF_STATE");
      break;
    }      
    default :
    {
      LOG_PRINT(INFO,"[%s:]BIC_BSC_ALARM_IND contain Unhandled Alarm cause[%d]",__func__, msgPtr->alarmCause);
      break;
    }     
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);  
}

/******************************* Function  Header*****************************
  Function Name : handleFailureEventReport()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Failure Event Report rcvd from Bic/Bts
Other Note    : Added For BSC R255
 *****************************************************************************/
I_Void handleFailureEventReport(I_Void)
{
  CsappAbihmBichFailureEventReport *msgPtr = GET_RCVD_MSG_PTR();
  I_U16		probableCause = ZERO ;

  /*Changes for mantis - 28228 and 28230 info len will be less than or equal to 100.
    the alarm string will provide info available in the failure event report and will not be contructed per FER */
  /*Changes merged from R2.9 Issue #31185 Gaurav Sinha*/
	//I_U8 alarmString[100];
  I_U8 alarmString[100]={'\0'};
  I_U8 addInfoLen = 0;
  I_U8 btsType = 0xFF; /* Mantis #31185*/
  addInfoLen = msgPtr->addInfo.len;
  btsType = msgPtr->probableCause.causeType; /* Mantis #31185*/
  LOG_PRINT(INFO," addInfoLen---- %d",addInfoLen);
  LOG_PRINT(INFO," addInfo--- %s",msgPtr->addInfo.addInfo);
  if(addInfoLen <=99)
  {
    memcpy(alarmString,msgPtr->addInfo.addInfo,msgPtr->addInfo.len);
  }
  else
  {
    memcpy(alarmString,msgPtr->addInfo.addInfo,99);
  }
  strcat(alarmString, "\0");
  LOG_PRINT(INFO,"alarmString ---- %s",alarmString);

  /*Changes for mantis - 28228 and 28230*/

  LOG_PRINT(INFO,"Enter [%s]",__func__);  
  if (!msgPtr) {
    LOG_PRINT(INFO,"[%s]: rcvd msg Ptr is Null",__func__);
    return ;
  }
	/* Mantis #31185*/
     
  if (btsType == 0x00 || btsType == 0x02 )
  {
    prepareAlarmFromFailureEventReportForR3(msgPtr,alarmString);
  }
  else
  {
  probableCause	= ((msgPtr->probableCause.causeValue[0]) << 8) ;
  probableCause = (probableCause | (msgPtr->probableCause.causeValue[1]));
  LOG_PRINT(INFO,"value of severity=%d",msgPtr->severityValue); /* Mantis #31185*/
  switch (probableCause) {
    case CP_SW_FATAL_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as CP_SW_FATAL_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_CP_SW_FATAL_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        /*else if(msgPtr->severityValue == TRAP_SEVERITY_CLEARED)
          {
          fillAndSendBichCfgAlarmInd(ALARM_CP_SW_FATAL_PC_OK,TRAP_SEVERITY_CLEARED,"ALARM_CP_SW_FATAL_PC_OK");
          }*/
        break;
      }      
    case CP_OVERLOAD_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as CP_OVERLOAD_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_CP_OVERLOAD_PC,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CLEARED)
        {
          fillAndSendBichCfgAlarmInd(ALARM_CP_OVERLOAD_PC_OK,TRAP_SEVERITY_CLEARED,alarmString);
        }
        break;
      }      
    case GPS_STATELLITE_SIGNAL_LEVELS_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as GPS_STATELLITE_SIGNAL_LEVELS_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_GPS_STATELLITE_SIGNAL_LEVELS_PC,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CLEARED)
        {
          fillAndSendBichCfgAlarmInd(ALARM_GPS_STATELLITE_SIGNAL_LEVELS_PC_OK,TRAP_SEVERITY_CLEARED,alarmString);
        }
        break;
      }      
    case GPS_ANTENNA_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as GPS_ANTENNA_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_GPS_ANTENNA_PC_WARNING,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CLEARED)
        {
          fillAndSendBichCfgAlarmInd(ALARM_GPS_ANTENNA_PC_OK,TRAP_SEVERITY_CLEARED,alarmString);
        }
        break;
      }      
    case GPS_RECIEVER_HEALTH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as GPS_RECIEVER_HEALTH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_GPS_RECIEVER_HEALTH_PC,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CLEARED)
        {
          fillAndSendBichCfgAlarmInd(ALARM_GPS_RECIEVER_HEALTH_PC_OK,TRAP_SEVERITY_CLEARED,alarmString);
        }
        break;
      }      
    case BS_TEMP_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as BS_TEMP_LOW_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_BS_TEMP_HIGH_PC_WARNING,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_BS_TEMP_HIGH_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_BS_TEMP_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,alarmString);
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case BS_TEMP_LOW_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as BS_TEMP_LOW_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_BS_TEMP_LOW_PC_WARNING,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_BS_TEMP_LOW_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_BS_TEMP_LOW_PC_OK,TRAP_SEVERITY_INFORMATION,alarmString);
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case MAIN_PLL_UNLOCKED_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as MAIN_PLL_UNLOCKED_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_MAIN_PLL_UNLOCKED_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        /*else if(msgPtr->severityValue == TRAP_SEVERITY_CLEARED)
          {
          fillAndSendBichCfgAlarmInd(ALARM_MAIN_PLL_UNLOCKED_OK,TRAP_SEVERITY_CLEARED,"ALARM_MAIN_PLL_UNLOCKED_PC_OK");
          }*/
        break;
      }      
    case TB_IP_LINK_DOWN_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as TB_IP_LINK_DOWN_PC",__func__);
        fillAndSendBichCfgAlarmInd(EVENT_TB_IP_LINK_DOWN_PC,TRAP_SEVERITY_MAJOR,"EVENT_TB_IP_LINK_DOWN_PC");
        break;
      }      
    case DLNA_TEMP_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as DLNA_TEMP_HIGH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_TEMP_HIGH_PC_WARNING,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_TEMP_HIGH_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_TEMP_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,alarmString);
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case DMB_TEMP_1_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as DMB_TEMP_1_HIGH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DMB_TEMP_1_HIGH_PC_WARNING,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DMB_TEMP_1_HIGH_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DMB_TEMP_1_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,alarmString);
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case DMB_TEMP_2_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as DMB_TEMP_2_HIGH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DMB_TEMP_2_HIGH_PC_WARNING,TRAP_SEVERITY_WARNING,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DMB_TEMP_2_HIGH_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,alarmString);
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DMB_TEMP_2_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,alarmString);
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case TX_SWR_FAULT_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as TX_SWR_FAULT_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_TX_SWR_FAULT_PC,TRAP_SEVERITY_WARNING,"ALARM_TX_SWR_FAULT_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_TX_SWR_FAULT_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_TX_SWR_FAULT_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case RX_DIVERSITY_FAULT_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as RX_DIVERSITY_FAULT_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_RX_DIVERSITY_FAULT_PC,TRAP_SEVERITY_WARNING,"ALARM_RX_DIVERSITY_FAULT_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_RX_DIVERSITY_FAULT_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_RX_DIVERSITY_FAULT_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case FM_TRX_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as FM_TRX_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_FM_TRX_PC,TRAP_SEVERITY_WARNING,"ALARM_FM_TRX_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_FM_TRX_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_FM_TRX_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case RADIO_SUPERVISION_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as RADIO_SUPERVISION_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_RADIO_SUPERVISION_PC,TRAP_SEVERITY_WARNING,"ALARM_RADIO_SUPERVISION_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_RADIO_SUPERVISION_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_RADIO_SUPERVISION_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case TRX_FRAME_SYNC_SUPERVISION_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as TRX_FRAME_SYNC_SUPERVISION_PC",__func__);
        fillAndSendBichCfgAlarmInd(EVENT_TRX_FRAME_SYNC_SUPERVISION_PC,TRAP_SEVERITY_CRITICAL,"EVENT_TRX_FRAME_SYNC_SUPERVISION_PC");
        break;
      }      
    case TRX_RX_SYNTH_SUPERVISION_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as TRX_RX_SYNTH_SUPERVISION_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(ALARM_TRX_RX_SYNTH_SUPERVISION_PC,TRAP_SEVERITY_CRITICAL,"ALARM_TRX_RX_SYNTH_SUPERVISION_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_TRX_RX_SYNTH_SUPERVISION_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_TRX_RX_SYNTH_SUPERVISION_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case RM_HW_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as RM_HW_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_RM_HW_PC,TRAP_SEVERITY_WARNING,"ALARM_RM_HW_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_RM_HW_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_RM_HW_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case DLNA_MAIN_CURR_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as DLNA_MAIN_CURR_HIGH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_MAIN_CURR_HIGH_PC_WARNING,TRAP_SEVERITY_WARNING,"EVENT_DLNA_MAIN_CURR_HIGH_PC_WARNING");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_MAIN_CURR_HIGH_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,"EVENT_DLNA_MAIN_CURR_HIGH_PC_CRITICAL");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_MAIN_CURR_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,"EVENT_DLNA_MAIN_CURR_HIGH_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case DLNA_DIV_CURR_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as DLNA_DIV_CURR_HIGH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_DIV_CURR_HIGH_PC_WARNING,TRAP_SEVERITY_WARNING,"EVENT_DLNA_DIV_CURR_HIGH_PC_WARNING");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_CRITICAL)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_DIV_CURR_HIGH_PC_CRITICAL,TRAP_SEVERITY_CRITICAL,"EVENT_DLNA_DIV_CURR_HIGH_PC_CRITICAL");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(EVENT_DLNA_DIV_CURR_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,"EVENT_DLNA_DIV_CURR_HIGH_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    case PA_CURR_HIGH_PC:
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as PA_CURR_HIGH_PC",__func__);
        if(msgPtr->severityValue == TRAP_SEVERITY_WARNING)
        {
          fillAndSendBichCfgAlarmInd(ALARM_PA_CURR_HIGH_PC,TRAP_SEVERITY_WARNING,"ALARM_PA_CURR_HIGH_PC");
        }
        else if(msgPtr->severityValue == TRAP_SEVERITY_INFORMATION)
        {
          fillAndSendBichCfgAlarmInd(ALARM_PA_CURR_HIGH_PC_OK,TRAP_SEVERITY_INFORMATION,"ALARM_PA_CURR_HIGH_PC_OK");
        }
        else
        {
          LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Severity Value[%d]",__func__, msgPtr->severityValue);
        }
        break;
      }      
    default :
      {
        LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled Probable cause[%d]",__func__, probableCause);
        break;
      }     
  }
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);  
}

/******************************* Function  Header*****************************
  Function Name : updChildTrxContxtFromDB()
Parameters    : None
Return type   : I_Void
Purpose       : This func reads the Trx table and fill the child Trx information
Other Note    : Added For BSC R22
 *****************************************************************************/
void updChildTrxContxtFromDB(void)
{
  I_U32         *ptrxId   = NULL;
  I_U32         trxCount  = 0;  
  I_U32         i         = 0;
  I_U32         j         = 0;

  LOG_PRINT(INFO,"Enter [%s]",__func__);  
  if (CLIB_SUCCESS != getAllPtrxTrxTable(GET_BTS_ID(), &ptrxId, &trxCount)) {
    LOG_PRINT(INFO,"%s: getAllPtrxTrxTable failed for BTSID [%u]",__func__,GET_BTS_ID());
    LOG_PRINT(INFO,"%s: Child Trx Context is not updated",__func__);
    return;
  }
  for (i=0; i < trxCount; i++) {
    for ( j=0; j < MAX_NUM_OF_CHILD_TRX; j++)
    {
      if ( (GET_CHILD_TRX_ID(j) == ptrxId[i]) )
      {
        LOG_PRINT(DEBUG,"\n %s: TRX[%d] received in ADD_TRX_IND already for present for BTS[%d] at Position[%d]", 
            __func__,ptrxId[i], GET_BTS_ID(), j);
        if((GET_BTS_TYPE() == R2_BTS_IP) || (GET_BTS_TYPE() == R3_BTS))
        {
            SET_CHILD_TRX_OPR_STATE(j,DISABLED);
        }
        continue;
      }
      if ( GET_CHILD_TRX_ID(j) == ZERO )
      {
        LOG_PRINT(DEBUG,"\n%s: Adding TRX[%d] for BTS[%d] at Position[%d]", 
            __func__,ptrxId[i], GET_BTS_ID(), j);
        ADD_CHILD_TRX(j,ptrxId[i]);
        break;
      }
    }
    if (j == MAX_NUM_OF_CHILD_TRX) {
       LOG_PRINT(DEBUG,"\n%s: Already max num of TRX configured for this bici",__func__);
       return;
    }
  }
  free(ptrxId);
  LOG_PRINT(INFO,"Exit [%s]",__func__);  
}

/*****************************************************************************************
***********************************UTILITY BASED PROCEDURES END***************************
*****************************************************************************************/

/*****************************************************************************************
***********************************SCENARIO BASED PROCEDURES START**********************
*****************************************************************************************/

/******************************* Function  Header*****************************
  Function Name : handleAddBtsProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Add Bts procedure related message
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleAddBtsProc(I_Void)
{
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eAddBtsProc != GET_ACTIVE_PROC() ) {
    LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
        GET_PROC_NAME(eAddBtsProc),
        GET_PROC_NAME(GET_ACTIVE_PROC()));
    return;
  }
  switch ( GET_MSG_TYPE() ) {
    case OAMS_CFG_BICH_ADD_BIC_REQ:
      updBichContxtFromAddBicReq();
      addBtsInStatusTable();
      updChildTrxContxtFromDB();
   /* Added for HA ABIS BSC-2.5.5 Start*/
     	if(ENT_OAMS_BICH != GET_MSG_RCVR()) 
		  {
	  		fillAndSendAddBtsResp(); 
			}
			else
			{
				updateBtsDataFromContext();      // R2.9 changes 
      }
      if((GET_BTS_TYPE() != R2_BTS) && (ENT_OAMS_BICH != GET_MSG_RCVR()))
      {
        fillAndSendAddBtsIpToTB();
      }
	/* Added for HA ABIS BSC-2.5.5 End*/
      if ( OAMS_RSLT_SUCCESS == getProcResult() ) {
        I_U8      alarmString[150];        
        SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
      		if (ENT_OAMS_BICH != GET_MSG_RCVR()) {
			  		sprintf(alarmString,"LAPD Link Down between BSC and BIC[%u] via E1[%d]E1Ts[%d]",
            GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
        		/*Bhaumik changes for alarm type Start*/
            if(GET_BTS_TYPE() == R2_BTS_IP)
            {
              fillAndSendBichCfgAlarmInd( ALARM_BTS_IP_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
            }
            else
            {
              fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
            }
        		/*Bhaumik changes for alarm type End*/
            sprintf(alarmString,"BTSId[%d] is Disabled",GET_BTS_ID());
        		fillAndSendBichCfgAlarmInd( ALARM_BTS_DISABLED, TRAP_SEVERITY_MAJOR, alarmString);         
					 }
      }
      /* R2.9 changes starts */  
      if((ENT_OAMS_BICH != GET_MSG_RCVR()) || (GET_BTS_TYPE() == R2_BTS))
      {
        SET_PROC_DONE(I_TRUE);      
      }
      /* R2.9 changes ends */
      break;
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : handleResetBtsProc()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles message related to Reset Bts procedure
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleResetBtsProc(I_Void)
{
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eResetBtsProc != GET_ACTIVE_PROC() ) {
    LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
        GET_PROC_NAME(eAddBtsProc),
        GET_PROC_NAME(GET_ACTIVE_PROC()));
    return;
  }
  switch ( GET_MSG_TYPE() ) {
    case OAMS_CFG_BICH_BTS_RESET:
      if ( verifyResetBtsReq()) {      
        /* Added From CS2.4 Having tag BSC-7.0.3.013 - Start*/
        if (GET_BTS_TYPE() == BIC)
        {
           fillAndSendBicRestart();
        }
        else
        {
           fillAndSendBmRestart();
        }
        /* Added From CS2.4 Having tag BSC-7.0.3.013 - End*/
        SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
      }  
      SET_PROC_DONE(I_TRUE);      
      break;
  }  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/* Add Changes HA ABIS BSC-R2.5.5 Start */
/******************************* Function  Header*****************************
Function Name : deleteContextOnDelBicReq()
Parameters    : Void
Return type   : I_U32
Purpose       : This fucn deletes the BicContext from DB.
Other Note    : Added For HA ABIS BSC R2.5.5
 *****************************************************************************/

I_U32 deleteContextOnDelBicReq(I_Void)
{
	 I_U32 									 		bicId;
	 I_S32											errCode;
	 BtsContextTableIndices			*inDelDataBtsContextTable = NULL;
	
	  inDelDataBtsContextTable =  AlocOrdBuf(sizeof(BtsContextTableIndices));	
		if (inDelDataBtsContextTable == NULL ) {
    LOG_PRINT(CRITICAL,"Could Not allocate memory for BtsContextTableIndices in function deleteContextOnDelBicReq ");
    return I_FALSE;
    }
 
LOG_PRINT(INFO,"LocalContext For Delete:bicId (%d), e1Id (%d) & e1Ts (%d)",gOamsBichContextPtr->bicId, gOamsBichContextPtr->e1Id, gOamsBichContextPtr->e1Ts);
		
		inDelDataBtsContextTable->btsId = gOamsBichContextPtr->bicId; 

	  errCode = deleteBtsContextTable(inDelDataBtsContextTable);
		if(errCode != CLIB_SUCCESS)
		{
			LOG_PRINT(MAJOR,"Deletion of context failed");
		}
		else
		{
			LOG_PRINT(INFO,"Deletion of context Success");
		}
		if(inDelDataBtsContextTable != NULL)
		{
		  DalocOrdBuf((I_Void *)inDelDataBtsContextTable);	
		}

}  

/* Add Changes HA ABIS BSC-R2.5.5 End */
/******************************* Function  Header*****************************
  Function Name : handleDelBtsProc()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles message related to Delete Bts procedure
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleDelBtsProc(I_Void)
{
  OamsBichCfgDelBicResp *msgPtr = NULL;
  I_U32   lapdStatus = I_FALSE;
  I_S32   dbResult;
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eDelBtsProc != GET_ACTIVE_PROC() ) {
    LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
        GET_PROC_NAME(eDelBtsProc),
        GET_PROC_NAME(GET_ACTIVE_PROC()));
    return;
  }
  switch ( GET_MSG_TYPE() ) {
    case OAMS_CFG_BICH_DEL_BIC_REQ:
      /* Incase of delete BTS slot disconnect is not sent to BTS/BIC as CFG will remove the 
      ** switching of Abis TS between allocated to BTS/BIC   
      */
      LOG_PRINT(INFO,"[E1Id: %d E1Ts: %d BtsId: %u BtsType: %u] DelBts/DelBic rcvd ",
                 GET_BTS_TRUNK(),
                 GET_BTS_TRUNK_TS(),
                 GET_BTS_ID(),
                 GET_BTS_TYPE());
      /* PCU REL 2.5 changes Begin */
      dbResult=getBtsLapdLinkStatus(GET_BTS_ID(),&lapdStatus);
      if(CLIB_SUCCESS !=dbResult)
      {
          LOG_PRINT(MAJOR,"getBtsLapdlinkStatus Failed for bicId: %u ",GET_BTS_ID());
      }
      else
      {
          if(lapdStatus)
          {
              fillAndSendDelBtsIpToTB();         
          }
      }	  
      /*PCU REL 2.5 changes End */ 
      delBtsFromStatusTable();
      fillAndSendDelBtsResp();

      if ( OAMS_RSLT_SUCCESS == getProcResult() ) {
         SET_NEXT_STATE(eIdle);
        /* R2.9 changes starts */
        if(GET_BTS_TYPE() != R2_BTS)
        {
         updateContextOnStateTransition();  
        }
       /* R2.9 changes ends */
     }
			/* Delete BIC Context from DB */
			deleteContextOnDelBicReq();
      SET_PROC_DONE(I_TRUE);      
      break;
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleLockProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles messages for Bts/Bic Lock procedure
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleLockProc(I_Void)
{
  I_U8      alarmString[150];

  LOG_PRINT(INFO,"Enter [%s]",__func__);

  if ( eLockProc != GET_ACTIVE_PROC() ) 
  {
     LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
                   GET_PROC_NAME(eLockProc),
                   GET_PROC_NAME(GET_ACTIVE_PROC()));
     return;
  }
  switch ( GET_MSG_TYPE() ) 
  {
    case OAMS_CFG_BICH_LOCK_REQ:
      {
         fillAndSendLockIndToTrx();

         if ( getOprState() == DISABLED )
         {
            SET_BTS_ADMIN_STATE(LOCKED);
            SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
            fillAndSendLockBtsResp();
            SET_PROC_DONE(I_TRUE);  
         }
         else 
         {
            SET_NEXT_STATE(eWaitForChildTrxDisc);
            /* R2.9 changes starts */
            if (GET_BTS_TYPE() != R2_BTS)
            {
              updateContextOnStateTransition();
            }
           /* R2.9 changes ends */
         }
         break;
      }
    case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND:
      {
         updBichContxtFromOperStateChange();
         /* getOprState() is called at updBichContxtFromOperStateChange might have update
         ** BIC/BTS operation state   
         */ 
         if ( getOprState() == DISABLED )
         {
            if ( (updateOperStateInBicStatusTable(GET_BTS_ID(), DISABLED) ) != CLIB_SUCCESS )
               LOG_PRINT(MAJOR,"[%s] updOperStateInBicStatusTable failed",__func__);
            sprintf(alarmString,"BTSId[%d] is Disabled",GET_BTS_ID());
            fillAndSendBichCfgAlarmInd( ALARM_BTS_DISABLED, TRAP_SEVERITY_MAJOR, alarmString); 
            SET_BTS_ADMIN_STATE(LOCKED); 
            SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
            fillAndSendLockBtsResp();
            SET_PROC_DONE(I_TRUE);
         }
         else
         {
            LOG_PRINT(INFO,"More OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND expected in eWaitForChildTrxDisc state");
         }
         break;
      }
    default: 
      {
         LOG_PRINT(MAJOR,"UnHandled Message[%d] reecived at state [%s]",GET_MSG_TYPE(), 
             GET_STATE_NAME(GET_ACTIVE_STATE()));
      } 
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleUnlockProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles messages related to Unlock Procedure
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleUnlockProc(I_Void)
{
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eUnlockProc != GET_ACTIVE_PROC() )
  {
     LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
                   GET_PROC_NAME(eUnlockProc),
                   GET_PROC_NAME(GET_ACTIVE_PROC()));
     return;
  }
  switch ( GET_MSG_TYPE() )
  {
    case OAMS_CFG_BICH_UNLOCK_REQ:
      {
        fillAndSendUnlockIndToTrx();
        SET_BTS_ADMIN_STATE(UNLOCKED);
        fillAndSendUnlockBtsResp();
        SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
        SET_PROC_DONE(I_TRUE);      
        break;
      }
    default: 
      {
        LOG_PRINT(MAJOR,"UnHandled Message[%d] reecived at state [%s]",GET_MSG_TYPE(), 
            GET_STATE_NAME(GET_ACTIVE_STATE()));
      } 
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
} 

/******************************* Function  Header*****************************
  Function Name : handleAbisLinkDownProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Lapd Link Down and Ip Link down procedure messges
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleAbisLinkDownProc(I_Void)
{
  I_U8      alarmString[150];
  I_U32     isBtsLinkMaster;
  I_S32     errCode;
  I_U32     btsOprState = getOprState();
  LOG_PRINT(INFO,"Enter [%s]",__func__);

  if ( eLapdDownProc != GET_ACTIVE_PROC() )
  {
     LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
               GET_PROC_NAME(eLapdDownProc),
               GET_PROC_NAME(GET_ACTIVE_PROC()));
     return;
  }
  switch ( GET_MSG_TYPE() ) 
  {
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN:
      {
         fillAndSendLinkDownToCcuh();
        
        /* R2.8 changes starts */
        if ( GET_BTS_TYPE() == R2_BTS)
        {
           sprintf(alarmString,"LAPD Link Down between BSC and BIC[%u] via E1[%d]E1Ts[%d]",
                      GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
           strcat(alarmString, "\0");
           fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString);
        }
        else
        {
           sprintf(alarmString,"IP Link Down BTSID[%d]",GET_BTS_ID());
           strcat(alarmString, "\0");
           fillAndSendBichCfgAlarmInd( ALARM_BTS_IP_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString);
        }
        /* R2.8 changes ends */
                         
         fillAndSendLinkDownToSwmh();
         prepareSlotDisConnect(gOamsBichContextPtr,&sendBicParentNotAvail);
         updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_NO_BIC);
         deleteBicFromAbisChain(gOamsBichContextPtr);
          /* PCU RELEASE 2.5 CHANGES BEGIN */ 
         if(GET_BTS_TYPE() == R2_BTS)
                fillAndSendDelBtsIpToTB();
        /*Added for R2.8 starts*/
        if ((GET_BTS_TYPE() == R2_BTS_IP) || (GET_BTS_TYPE() == R3_BTS))
        {
         updateBtsIpLinkStatus(GET_BTS_ID(),ABIS_IP_DOWN);
         LOG_PRINT(INFO,"BTS IP Link Status is DOWN for IP BTS");
        } 
        /*Added for R2.8 ends*/
         /* PCU RELEASE 2.5 CHANGES ENDS  */ 
         /* Incase BTS/BIC is in Enable state and LS will be udpated after Child Trx are moved to Disable
         ** state , which will also put BTS/BIC in Disable state.   
         */
         if ( btsOprState != ENABLED )
         {
           if ((GET_BTS_TYPE() == R2_BTS_IP) || (GET_BTS_TYPE() == R3_BTS))
           { 
            errCode = updateConStateBicStatusTable(GET_BTS_ID(), LAPD_NOT_APPLICABLE);
           } 
           else 
           {
            errCode = updateConStateBicStatusTable(GET_BTS_ID(), LAPD_LINK_DOWN);
           }
           if (errCode != CLIB_SUCCESS)
           {
             LOG_PRINT(MAJOR,"Error in updateConStateBicStatusTable: err = %s",clib_strerror(errCode));
           }
         }
         if ( (errCode =getIsBtsLapdMasterBssCsPreConTable(&isBtsLinkMaster) ) != CLIB_SUCCESS )
         {
            LOG_PRINT(MAJOR,"Error in getIsBtsLapdMasterBssCsPreConTable: err = %s",clib_strerror(errCode));
         }
         else 
         {
            if ( isBtsLinkMaster == I_TRUE )
            { 
               if(((GET_BTS_TYPE() == R2_BTS_IP) || (GET_BTS_TYPE() == R3_BTS)))
               {
                  LOG_PRINT(MAJOR,"BTS is Link Master So, Sending IP_LINK_DOWN to all Child TRX's");
                  fillAndSendIpLinkDownToTrxh();
               }
               else
               {
                  LOG_PRINT(MAJOR,"BTS is Link Master So, Sending LAPD_DISC_IND to all Child TRX's");
                  fillAndSendLapdDiscIndToTrxh();
               }
            } 
            else
            {
               LOG_PRINT(DEBUG,"Not Sending OAMS_BICH_TRXH_LAPD_DISCONNECT_IND as Bts is not Link Master");
            }
         }
         SET_BTS_LAPD_OPR_STATE(LAPD_LINK_DOWN); 
         if ( btsOprState != ENABLED )
         {
            SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
            SET_PROC_DONE(I_TRUE);      
         }
         else
         {
            SET_NEXT_STATE(eWaitForChildTrxDisc);
            /* R2.9 changes starts */
            if(GET_BTS_TYPE() != R2_BTS)
            {
              updateContextOnStateTransition();
            }
           /* R2.9 changes ends */
         }
         break;
      }
    case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND: 
      {
         updBichContxtFromOperStateChange();
         /* getOprState() is called at updBichContxtFromOperStateChange might have update
         ** BIC/BTS operation state   
         */ 
         if ( getOprState() == DISABLED )
         {
            if ( (updateOperStateInBicStatusTable(GET_BTS_ID(), DISABLED) ) != CLIB_SUCCESS )
               LOG_PRINT(MAJOR,"[%s] updOperStateInBicStatusTable failed",__func__);
            if ((GET_BTS_TYPE() != R2_BTS_IP) && (GET_BTS_TYPE() != R3_BTS))
            {
               if ( (errCode = updateConStateBicStatusTable(GET_BTS_ID(), LAPD_LINK_DOWN) ) != CLIB_SUCCESS )
               LOG_PRINT(MAJOR,"Error in updateConStateBicStatusTable: err = %s",clib_strerror(errCode));
            }

            sprintf(alarmString,"BTSId[%d] is Disabled",GET_BTS_ID());
          fillAndSendBichCfgAlarmInd( ALARM_BTS_DISABLED, TRAP_SEVERITY_MAJOR, alarmString);
            SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
            SET_PROC_DONE(I_TRUE);
         }
         else
         {
            LOG_PRINT(INFO,"More OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND expected in eWaitForChildTrxDisc state");
         }

         break;
      }
     /* PCU REL 2.5 CHANGES START */
     case CSAPP_ABIHM_BICH_IP_LINK_DOWN:
     {
        if(GET_IP_OPR_STATE() != ABIS_IP_DOWN)
	        {      
            if( (updateBtsIpLinkStatus(GET_BTS_ID(),ABIS_IP_DOWN) )!= CLIB_SUCCESS )
               LOG_PRINT(MAJOR,"[%s] updBtsIpLinkStatus failed",__func__);
            sprintf(alarmString,"IP Link Down BTSID[%d]",GET_BTS_ID());
            strcat(alarmString, "\0"); 
            fillAndSendBichCfgAlarmInd( ALARM_BTS_IP_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
            fillAndSendIpLinkDownToTB();
            fillAndSendIpLinkDownToTrxh();   
            SET_IP_OPR_STATE(ABIS_IP_DOWN);
            if(GET_ACTIVE_STATE() != eWaitForChildTrxDisc) 
               SET_PROC_DONE(I_TRUE);
         }
         else
         {
            LOG_PRINT(MAJOR,"[%s] IP Link Is Already Down",__func__);
            if(GET_ACTIVE_STATE() != eWaitForChildTrxDisc) 
              SET_PROC_DONE(I_TRUE);
         }
         
         break;
    }
   
    case PSAPP_TB_BICH_IP_LINK_DOWN:
    {
       if(GET_IP_OPR_STATE() != ABIS_IP_DOWN)
       {        
          if( (updateBtsIpLinkStatus(GET_BTS_ID(),ABIS_IP_DOWN) )!= CLIB_SUCCESS )
             LOG_PRINT(MAJOR,"[%s] updBtsIpLinkStatus failed",__func__);
          sprintf(alarmString,"IP Link Down BTSID[%d]",GET_BTS_ID());
          strcat(alarmString, "\0"); 
          fillAndSendBichCfgAlarmInd( ALARM_BTS_IP_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
          if ( GET_BTS_LAPD_OPR_STATE() == LAPD_LINK_UP)
	        fillAndSendIpLinkDownToAbihm();
          fillAndSendIpLinkDownToTrxh();   
          SET_IP_OPR_STATE(ABIS_IP_DOWN); 
          if(GET_ACTIVE_STATE() != eWaitForChildTrxDisc) 
             SET_PROC_DONE(I_TRUE);
       }
       else
       {	  
          LOG_PRINT(MAJOR,"[%s] IP LINK Is Already Down",__func__);
          if(GET_ACTIVE_STATE() != eWaitForChildTrxDisc) 
             SET_PROC_DONE(I_TRUE);
       }
       break;
    }	
    /* PCU REL 2.5 CHANGES END*/
    default:
      {
         LOG_PRINT(MAJOR,"UnHandled Message[%d] reecived at state [%s]",GET_MSG_TYPE(),
            GET_STATE_NAME(GET_ACTIVE_STATE()));

      } 
   }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
} 

/******************************* Function  Header*****************************
  Function Name : handleAbisLinkEstabProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Lapd Link and Ip link Estab procedure messages
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleAbisLinkEstabProc(I_Void)
{
	BicStatusTableApi     *bicStatusTableApi;
  BicStatusTableIndices bicStatusTableIndex = {0};
  I_U8                alarmString[150];
  I_S32               errCode;
	I_U32								retStatus = I_FALSE;

  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eLapdLinkEstabProc != GET_ACTIVE_PROC() )
  {
    LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
        GET_PROC_NAME(eLapdLinkEstabProc),
        GET_PROC_NAME(GET_ACTIVE_PROC()));
    return;
  }
  switch ( GET_MSG_TYPE() )
  {
    case CSAPP_ABIHM_BICH_BIC_HELLO:
    case CSAPP_ABIHM_BICH_BM_HELLO:
     {
      /*Added for R3 BTS starts*/
       if ((GET_BTS_TYPE() == BIC) || (GET_BTS_TYPE() == R2_BTS)) 
       {
         retStatus = checkLapdStatusInBicStatusTable();
       }
      else 
      {
       LOG_PRINT(INFO,"BIC is configured as R2 BTS IP or R3 BTS, so LAPD NOT APPLICABLE");  
      }  
      /*Added for R3 BTS ends*/ 
      if (retStatus == I_FALSE) 
				{
          updBichContxtFromBicHello();
          updSwVersionFromBicHello();
          checkParamInBicHello();
         if (  getProcResult() == OAMS_RSLT_SUCCESS)
         		{
              fillAndSendBicHelloToSwmh();
              updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_BIC_CON_IN_PROGRESS);
            	addBicInAbisChain(gOamsBichContextPtr);
            	fillAndSendLinkEstabReq();
              SET_NEXT_STATE(eWaitForLinkEstab); 
             /* R2.9 changes starts */
              if(GET_BTS_TYPE() !=R2_BTS)
              {
                updateContextOnStateTransition();
              }
             /*R2.9 changes ends */
            }
         		else
         		{
            	SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
            	SET_PROC_DONE(I_TRUE);               
          	}
					}/*end of checkLapdStatusInBicStatusTable */
			/*	else
					{
						SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
            SET_PROC_DONE(I_TRUE);
					}*/
      break;
      }
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN:
      {
         fillAndSendLinkDownToCcuh();
         sprintf(alarmString,"LAPD Link Down between BSC and BIC[%u] via E1[%d]E1Ts[%d]",
                            GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
         strcat(alarmString, "\0"); 
        /*Added for R2.8 starts*/
        if ((GET_BTS_TYPE() == R2_BTS_IP) || (GET_BTS_TYPE() == R3_BTS))
        {
         updateBtsIpLinkStatus(GET_BTS_ID(),ABIS_IP_DOWN);
         LOG_PRINT(INFO,"BTS IP Link Status is DISABLED for IP BTS");
         errCode = updateConStateBicStatusTable(GET_BTS_ID() , LAPD_NOT_APPLICABLE);
         LOG_PRINT(INFO,"LAPD link is not applicable for IP BTS");
        }
        else
        {
        errCode = updateConStateBicStatusTable(GET_BTS_ID() , LAPD_LINK_DOWN);
        }
        if (errCode != CLIB_SUCCESS)
        {
         LOG_PRINT(MAJOR,"Error in updateConStateBicStatusTable: err = %s",clib_strerror(errCode));
        } 
        /*Added for R2.8 ends*/
        /*Mantis -- 14848 Start*/
         fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_DOWN, TRAP_SEVERITY_MAJOR, alarmString); 
         /* Merged Mantis: 8677 */ 
         /*
         sprintf(alarmString,"Link Estab Failed for BIC [%u]BSC E1[%d]",GET_BTS_ID(),GET_BTS_TRUNK());
         strcat(alarmString, "\0");
         fillAndSendBichCfgAlarmInd( EVENT_BIC_LINK_EST_FAILED, TRAP_SEVERITY_MAJOR, alarmString); 
         */
         
         updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_NO_BIC);
         deleteBicFromAbisChain(gOamsBichContextPtr);
         SET_BTS_LAPD_OPR_STATE(LAPD_LINK_DOWN);
         SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
         SET_PROC_DONE(I_TRUE);      
         break;
      }
    case CSAPP_ABIHM_BICH_LAPD_LINK_UP:
      {
        /*Mantis -- 14848 Start*/ 
        I_S8 ipAddr[25];
        /*Mantis -- 14848 End*/ 
        fillAndSendLinkUpToCcuh();
        /* Added for R2.8 starts*/
        if( GET_BTS_TYPE() == R2_BTS)
        {
           sprintf(alarmString,"LAPD link is UP between BSC and BIC[%u] via E1[%d] E1Ts[%d]",
               GET_BTS_ID(),GET_BTS_TRUNK(),GET_BTS_TRUNK_TS());
           strcat(alarmString, "\0");
           fillAndSendBichCfgAlarmInd( ALARM_BIC_LINK_UP, TRAP_SEVERITY_CLEARED, alarmString);
        }
        else
        {
            sprintf(alarmString,"IP Link UP BTSID[%d]",GET_BTS_ID());
            strcat(alarmString, "\0");
            fillAndSendBichCfgAlarmInd( ALARM_BTS_IP_LINK_UP, TRAP_SEVERITY_CLEARED, alarmString);
        }
        /* Added for R2.8 ends */
        
        updateAbisChainStatus(GET_BTS_TEI(), ABIS_E1_STATUS_BIC_CONNECTED);
        if (  GET_BTS_TYPE() == BIC )
           prepareSlotConnect(gOamsBichContextPtr);
        /* PCU REL 2.5 CHANGES START*/
        if (  GET_BTS_TYPE() == R2_BTS )
           fillAndSendAddBtsIpToTB();  
        /* PCU REL 2.5 CHANGES END */ 
        bicStatusTableIndex.bicId = GET_BTS_ID() ;
        if (CLIB_SUCCESS == (errCode = getBicStatusTable(&bicStatusTableIndex, &bicStatusTableApi)))
        {
          LOG_PRINT(INFO,"[%s] getBicStatusTable Success for BtsId: %u", __func__, bicStatusTableIndex.bicId);
          /*Added for R3 BTS starts*/
          if ((GET_BTS_TYPE() == BIC) || (GET_BTS_TYPE() == R2_BTS))
          {  
            bicStatusTableApi->lapdLinkStatus = LAPD_LINK_UP ; 
            bicStatusTableApi->btsIpLinkStatus = ABIS_IP_DOWN ;
          }
          else
          {
            bicStatusTableApi->lapdLinkStatus = LAPD_NOT_APPLICABLE;
            bicStatusTableApi->btsIpLinkStatus = ABIS_IP_UP ;
          }
          /*Mantis -- 14848 Start*/
          memset(ipAddr,0, sizeof(ipAddr));
          getIpAddrAsString(ipAddr);
          strncpy(bicStatusTableApi->btsIpAddr, ipAddr, sizeof(ipAddr));
          /*Mantis -- 14848 End*/
          bicStatusTableApi->oprState = DISABLED ;
          if ( (errCode = updateBicStatusTable(bicStatusTableApi) ) != CLIB_SUCCESS )
          {
            LOG_PRINT(MAJOR,"Error in updateBicStatusTable: err = %s",clib_strerror(errCode));
          }
          
          free(bicStatusTableApi);
        }
        else
        {
          LOG_PRINT(MAJOR,"Error in getBicStatusTable: err = %s",clib_strerror(errCode));
        }

        SET_BTS_LAPD_OPR_STATE(LAPD_LINK_UP);
        /* PCU REL 2.5 CHANGES START*/
        SET_IP_OPR_STATE(ABIS_IP_DOWN); 
       /* PCU REL 2.5 CHANGES START*/
        SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
        SET_PROC_DONE(I_TRUE);    
        break;
      }
    
   /* PCU REL 2.5 CHANGES STARTS*/
   case PSAPP_TB_BICH_IP_LINK_UP:   
    {
       if( (updateBtsIpLinkStatus(GET_BTS_ID(),ABIS_IP_UP) )!= CLIB_SUCCESS )
             LOG_PRINT(MAJOR,"[%s] updBtsIpLinkStatus failed",__func__);
       sprintf(alarmString,"IP Link UP BTSID[%d]",GET_BTS_ID());
       strcat(alarmString, "\0");
       fillAndSendBichCfgAlarmInd( ALARM_BTS_IP_LINK_UP, TRAP_SEVERITY_CLEARED, alarmString);
       fillAndSendIpLinkUpToTrxh();
       SET_IP_OPR_STATE(ABIS_IP_UP); 
       if(GET_ACTIVE_STATE() != eWaitForChildTrxDisc) 
          SET_PROC_DONE(I_TRUE);
       break;
    }
   /* PCU REL 2.5 CHANGES END */
   default:
      {
         LOG_PRINT(MAJOR,"UnHandled Message[%d] reecived at state [%s]",GET_MSG_TYPE(), 
             GET_STATE_NAME(GET_ACTIVE_STATE()));
      } 
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleAddChildTrxProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Addition of Trx procedure messages
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleAddChildTrxProc(I_Void)
{
   
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eAddChildTrxProc != GET_ACTIVE_PROC() ) 
  {
     LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
                 GET_PROC_NAME(eAddChildTrxProc),
                 GET_PROC_NAME(GET_ACTIVE_PROC()));
     return;
  }
  switch ( GET_MSG_TYPE() ) 
  {
     case OAMS_CFG_BICH_ADD_TRX_INDICATION:
       {
          updBichContxtFromAddTrxInd();
          if ( GET_BTS_TYPE() == BIC 
               && GET_BTS_ADMIN_STATE() == LOCKED
               && GET_BTS_LAPD_OPR_STATE() == LAPD_LINK_UP )
          {
             sendSlotConnectForTrx();
          } 
      
          SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
          SET_PROC_DONE(I_TRUE);    
          break;
       }
       default:
       {
         LOG_PRINT(MAJOR,"UnHandled Message[%d] reecived at state [%s]",GET_MSG_TYPE(), 
             GET_STATE_NAME(GET_ACTIVE_STATE()));
       } 
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleDelChildTrxProc()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Delete child Trx procedure messages
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleDelChildTrxProc(I_Void)
{
   
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eDelChildTrxProc != GET_ACTIVE_PROC() ) 
  {
     LOG_PRINT(INFO,"\nExpected Active Proc [%s], but Active Proc [%s] ",
                   GET_PROC_NAME(eDelChildTrxProc),
                   GET_PROC_NAME(GET_ACTIVE_PROC()));
     return;
  }
  switch ( GET_MSG_TYPE() )
  {
     case OAMS_CFG_BICH_DEL_TRX_INDICATION:
       {
          updBichContxtFromDelTrxInd();
          SET_NEXT_STATE(findNextStateBasedOnAdminAndOprState());
          SET_PROC_DONE(I_TRUE);    
          break;
       }
       default:
       {
         LOG_PRINT(MAJOR,"UnHandled Message[%d] reecived at state [%s]",GET_MSG_TYPE(), 
             GET_STATE_NAME(GET_ACTIVE_STATE()));
       } 
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/*****************************************************************************************
***********************************SCENARIO BASED PROCEDURES END************************
*****************************************************************************************/

/*****************************************************************************************
***********************************STATE BASED PROCEDURES START**************************
*****************************************************************************************/

/******************************* Function  Header*****************************
  Function Name : handleIdleStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This func handle all the message in Idle state and it sets new procedure 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleIdleStateMsgs(I_Void)
{
  /* In Idle state only AddBts/AddBic procedure is possible 
  ** incase some procedure is already on-going that flag error 
  ** remain in sameState
  */
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( IS_ANY_PROC_ONGOING() ) {    
    LOG_PRINT(INFO,"\n[%s:] Procedure is alredy on-going",GET_PROC_NAME(GET_ACTIVE_PROC()));
    return ;
  } 
  switch ( GET_MSG_TYPE() ) {
    case OAMS_CFG_BICH_ADD_BIC_REQ:
      SET_ACTIVE_PROC(eAddBtsProc);
      handleAddBtsProc();      
  }
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}



/******************************* Function  Header*****************************
  Function Name : handleUnlockedDisabledStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Unlocked Disabled state messges and trigger/start 
procedures 
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleUnlockedDisabledStateMsgs(I_Void)
{
  /* In UnlockedDisabled state is stable state 
  ** incase some procedure is already on-going that flag error 
  ** remain in sameState
  */
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( IS_ANY_PROC_ONGOING() ) {    
    LOG_PRINT(INFO,"\n[%s:] Procedure is alredy on-going",GET_PROC_NAME(GET_ACTIVE_PROC()));
    return ;
  }     
  switch ( GET_MSG_TYPE() ) {
    case CSAPP_ABIHM_BICH_BIC_HELLO:  
    case CSAPP_ABIHM_BICH_BM_HELLO:  
      SET_ACTIVE_PROC(eLapdLinkEstabProc);      
      handleAbisLinkEstabProc();  
      break;     
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN:      
      SET_ACTIVE_PROC(eLapdDownProc);      
      handleAbisLinkDownProc();   
      break;
    /* PCU REL 2.5 CHANGES START*/ 
    case CSAPP_ABIHM_BICH_IP_LINK_DOWN :
    case PSAPP_TB_BICH_IP_LINK_DOWN    :  
      SET_ACTIVE_PROC(eLapdDownProc);      
      handleAbisLinkDownProc();   
      SET_NEXT_STATE(eUnlockedDisabled);
      break;
    case PSAPP_TB_BICH_IP_LINK_UP:
      SET_ACTIVE_PROC(eLapdLinkEstabProc);
      handleAbisLinkEstabProc();  
      SET_NEXT_STATE(eUnlockedDisabled);
      break;
    /* PCU REL 2.5 CHANGES END */  
     case OAMS_CFG_BICH_LOCK_REQ:
      SET_ACTIVE_PROC(eLockProc);
      handleLockProc();
      break;
    case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND:
      handleTrxOperStateChangeInd();
      break;
}    
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleUnlockedEnabledStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This func handles Unlocked Enabled state messages
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleUnlockedEnabledStateMsgs(I_Void)
{
  /* In UnlockedDisabled state is stable state 
  ** incase some procedure is already on-going that flag error 
  ** remain in sameState
  */
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( IS_ANY_PROC_ONGOING() ) {    
    LOG_PRINT(INFO,"\n[%s:] Procedure is alredy on-going",GET_PROC_NAME(GET_ACTIVE_PROC()));
    return ;
  }     
  switch ( GET_MSG_TYPE() ) 
  {
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN :      
      SET_ACTIVE_PROC(eLapdDownProc);      
      handleAbisLinkDownProc();   
      break;   
    case OAMS_CFG_BICH_LOCK_REQ:  
      SET_ACTIVE_PROC(eLockProc);      
      handleLockProc();   
      break;
    case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND:  
      handleTrxOperStateChangeInd();   
      break;            
    /* PCU REL 2.5 CHANGES BEGIN */  
    case PSAPP_TB_BICH_IP_LINK_UP:
      SET_ACTIVE_PROC(eLapdLinkEstabProc);
      handleAbisLinkEstabProc();  
      SET_NEXT_STATE(eUnlockedEnabled);
      break;
    case CSAPP_ABIHM_BICH_IP_LINK_DOWN   :
    case PSAPP_TB_BICH_IP_LINK_DOWN      :    
      SET_ACTIVE_PROC(eLapdDownProc);      
      handleAbisLinkDownProc();   
      SET_NEXT_STATE(eUnlockedEnabled);
      break;   
    /* PCU REL 2.5 CHANGES END  */  
  }    
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleLockedDisabledStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles Locked Disabled state messages.
It set new procedure if needed or call the on-going procedure specific function
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleLockedDisabledStateMsgs(I_Void)
{
  /* In LockedDisabled state is stable state 
  ** incase some procedure is already on-going that flag error 
  ** remain in sameState
  */
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( IS_ANY_PROC_ONGOING() ) {    
    LOG_PRINT(INFO,"\n[%s:] Procedure is alredy on-going",GET_PROC_NAME(GET_ACTIVE_PROC()));
    return ;
  }   
  switch ( GET_MSG_TYPE() ) {
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN:      
      SET_ACTIVE_PROC(eLapdDownProc);      
      handleAbisLinkDownProc();      
      break;
    case OAMS_CFG_BICH_DEL_BIC_REQ:  
      SET_ACTIVE_PROC(eDelBtsProc);      
      handleDelBtsProc();        
      break;
    case OAMS_CFG_BICH_UNLOCK_REQ:  
      SET_ACTIVE_PROC(eUnlockProc);      
      handleUnlockProc();   
      break;
    case CSAPP_ABIHM_BICH_BIC_HELLO:  
    case CSAPP_ABIHM_BICH_BM_HELLO:  
      SET_ACTIVE_PROC(eLapdLinkEstabProc);      
      handleAbisLinkEstabProc(); 
      break;  
    case OAMS_CFG_BICH_ADD_TRX_INDICATION:
      SET_ACTIVE_PROC(eAddChildTrxProc);      
      handleAddChildTrxProc();       
      break;   
    case OAMS_CFG_BICH_BTS_RESET:
      SET_ACTIVE_PROC(eResetBtsProc);      
      handleResetBtsProc();       
      break;    
    case OAMS_CFG_BICH_DEL_TRX_INDICATION:
      SET_ACTIVE_PROC(eDelChildTrxProc);      
      handleDelChildTrxProc();       
      break;       
    /* PCU REL 2.5 CHANGES START*/
    case CSAPP_ABIHM_BICH_IP_LINK_DOWN :
    case PSAPP_TB_BICH_IP_LINK_DOWN    :
      SET_ACTIVE_PROC(eLapdDownProc);
      handleAbisLinkDownProc();
      SET_NEXT_STATE(eLockedDisabled);
      break;
    case PSAPP_TB_BICH_IP_LINK_UP:
      SET_ACTIVE_PROC(eLapdLinkEstabProc);
      handleAbisLinkEstabProc();
      SET_NEXT_STATE(eLockedDisabled);
      break;
		case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND:
      handleTrxOperStateChangeIndInLockedState();
      break;
   /* PCU REL 2.5 CHANGES END*/

 } 
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}


/******************************* Function  Header*****************************
  Function Name : handleWaitForLinkEstabStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles WaitForLinkEstabState messages.
It set new procedure if needed or call the on-going procedure specific function
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleWaitForLinkEstabStateMsgs(I_Void)
{
  /* In  WaitForLinkEstab state is reached when LAPD link is established for Bts/Bic 
  */
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  if ( eLapdLinkEstabProc != GET_ACTIVE_PROC() ) {    
    LOG_PRINT(INFO,"\nExpected Proc [%s] , Active Proc [%s:] ",
                  GET_PROC_NAME(eLapdLinkEstabProc),
                  GET_PROC_NAME(GET_ACTIVE_PROC()));
    return ;
  } 
  switch ( GET_MSG_TYPE() ) {
    case CSAPP_ABIHM_BICH_LAPD_LINK_UP:      
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN:      
    {
      handleAbisLinkEstabProc();         
      break;
    }
    case OAMS_CFG_BICH_ADD_TRX_INDICATION:
    {
      updBichContxtFromAddTrxInd(); //No need call procedure specific func     
      break;
    }
    case OAMS_CFG_BICH_DEL_TRX_INDICATION:
    {
      updBichContxtFromDelTrxInd(); //No need to call procedure specific func     
      break;
    }
  }  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleWaitForChildTrxDiscStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles WaitForChildTrxDiscState messages.
It set new procedure if needed or call the on-going procedure specific function
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleWaitForChildTrxDiscStateMsgs(I_Void)
{
  /* In  WaitForChildTrxDisc state is reached when Bich LAPD Link is Down or Bich Lock is Triggered 
  */
  I_U16 activeProc = GET_ACTIVE_PROC();
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  switch ( GET_MSG_TYPE() ) {
    case OAMS_TRXH_BICH_OPER_STATE_CHANGE_IND:        
      switch ( GET_ACTIVE_PROC() ) {    
        case eLapdDownProc:
          handleAbisLinkDownProc();
	  activeProc=eLapdDownProc;
          break;
        case eLockProc:
	  activeProc=eLockProc;
          handleLockProc();
          break;  
      }       
      break;     
    
    /* PCU REL 2.5 CHANGES START */
    case CSAPP_ABIHM_BICH_IP_LINK_DOWN   :
    case PSAPP_TB_BICH_IP_LINK_DOWN      :
       SET_ACTIVE_PROC(eLapdDownProc);
       handleAbisLinkDownProc();
       if(activeProc==eLockProc)
       {  
          SET_ACTIVE_PROC(eLockProc);
         /* R2.9 changes starts */
         if(GET_BTS_TYPE() != R2_BTS)
         {
          updateContextOnStateTransition();  
         }
         /* R2.9 changes ends */
       }
       else	  
       {   
        SET_ACTIVE_PROC(eLapdDownProc);
       /* R2.9 changes starts */
        if(GET_BTS_TYPE() != R2_BTS)
        {
         updateContextOnStateTransition();  
        }
       /* R2.9 changes ends */
       } 
        SET_NEXT_STATE(eWaitForChildTrxDisc);
       break;
    case PSAPP_TB_BICH_IP_LINK_UP:
       SET_ACTIVE_PROC(eLapdLinkEstabProc);
       handleAbisLinkEstabProc();
       if(activeProc==eLockProc)
       {  
         SET_ACTIVE_PROC(eLockProc);
         /* R2.9 changes starts */
         if(GET_BTS_TYPE() != R2_BTS)
         {
          updateContextOnStateTransition();  
         }
        /* R2.9 changes ends */
       }       
       else	  
       {   
         SET_ACTIVE_PROC(eLapdDownProc);
         /* R2.9 changes starts */
        if(GET_BTS_TYPE() != R2_BTS)
        {
         updateContextOnStateTransition();  
        }
        /* R2.9 changes ends */
       } 
       SET_NEXT_STATE(eWaitForChildTrxDisc);
       break;
    case CSAPP_ABIHM_BICH_LAPD_LINK_DOWN:  
       SET_ACTIVE_PROC(eLapdDownProc);
       handleAbisLinkDownProc();
       SET_NEXT_STATE(eWaitForChildTrxDisc);
       break;
   /* PCU REL 2.5 CHANGES END */
 
  }  
  LOG_PRINT(INFO,"Exit [%s]",__func__);
}

/******************************* Function  Header*****************************
  Function Name : handleStarStateMsgs()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles Start(*) State messages.
It does not set new procedure nor it change the state , In Start (*) State only
those messages are handled which does not have impact on the on-going procedure
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleStarStateMsgs (I_Void)
{
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  switch ( GET_MSG_TYPE() ) {
    case CSAPP_ABIHM_BICH_BIC_BSC_ALARM_IND:        
    {
      handleBtsAlarmInd();
      break;     
    }
    case OAMS_CFG_BICH_BIC_CC_PWR_ORDER_REQ:
    {
      fillAndSendOamsBichAbihmBicCcPwrOrderReq();
      break;
    } 
	  case CSAPP_ABIHM_BICH_FAILURE_EVENT_REPORT: 
    {
      handleFailureEventReport();
      break;     
    }
  }  
  LOG_PRINT(INFO,"Exit [%s]",__func__);  
}
/******************************* Function  Header*****************************
Function Name : handleCardStateChangeNotification()
Parameters    : None
Return type   : I_Void
Purpose       : This fucn handles CardStateChangeNotification  message.
Other Note    : Added For BSC R22
 *****************************************************************************/
I_Void handleCardStateChangeNotification(OamsBichContext *OamsBichContextPtr)
{
  SET_BICH_CNTX_PTR(OamsBichContextPtr); 
  LOG_PRINT(INFO,"Enter [%s]",__func__);
  logPrintBichContext();  
/*  if (LAPD_LINK_UP == GET_BTS_LAPD_OPR_STATE()) {
    fillAndSendLapdDiscIndForBts();     
  }
*/ // Commented for HA-Abis  
  resetBichContext();
  LOG_PRINT(INFO,"Exit [%s]",__func__);  
}

/* PCU REL 2.5 CHANGES END */
/******************************* Function  Header*****************************
Function Name : getIpAddr()
Parameters    : Void
Return type   : I_U32
Purpose       : This fucn handles the btsIpAddr  message.
Other Note    : Added For BSC R22
 *****************************************************************************/

I_U32 getIpAddr(I_Void)
{
   I_U32 tempIpAddr[3];
   tempIpAddr[0] = gOamsBichContextPtr->IpAdd.AAA;
   tempIpAddr[1] = gOamsBichContextPtr->IpAdd.BBB;
   tempIpAddr[2] = gOamsBichContextPtr->IpAdd.CCC;
   tempIpAddr[0] <<= 24; 
   tempIpAddr[1] <<= 16 ;
   tempIpAddr[2] <<= 8 ;
   tempIpAddr[0] = (tempIpAddr[0] |tempIpAddr[1] |tempIpAddr[2] | gOamsBichContextPtr->IpAdd.DDD);
   return tempIpAddr[0];
}  
 /*Mantis -- 14848 Start*/ 
/******************************* Function  Header*****************************
Function Name : getIpAddrAsString(I_U8 *)
Parameters    : I_U8 *ipAddr 
Return type   : void
Purpose       : This func handles the btsIpAddr  message.
Other Note    : Added For BSC PCU R2.5
 *****************************************************************************/
 I_Void getIpAddrAsString(I_S8 *ipAddr)
 {
    sprintf(ipAddr, "%u.%u.%u.%u", gOamsBichContextPtr->IpAdd.AAA, gOamsBichContextPtr->IpAdd.BBB, gOamsBichContextPtr->IpAdd.CCC, gOamsBichContextPtr->IpAdd.DDD);
 }
 /*Mantis -- 14848 End*/ 

/* PCU REL 2.5 CHANGES END */
/*****************************************************************************************/
/******************************* Function  Header*****************************
Function Name : updateBtsDataFromContext()
Parameters    :  
Return type   : void
Purpose       : This func handles the Bts Data stored in context
Other Note    : Added For BSC HA R2.5.5
 *****************************************************************************/
I_Void updateBtsDataFromContext()
{
/* Get Ip Address from Context */

BtsContextTableIndices         inDataBtsContextTable = {0};
BtsContextTableApi             *outDataBtsContextTable;
OamsBichStandbyCardContext     *bichContext = NULL;
I_S32                           errCode;
I_U32                           i = 0;
bichContext = (OamsBichStandbyCardContext *)AlocOrdBuf(sizeof(OamsBichStandbyCardContext));
if (bichContext == NULL ) {
    LOG_PRINT(CRITICAL,"updateBtsDataFromContext: Could Not allocate memory for OamsBichStandbyCardContext ");
    return;
  }

inDataBtsContextTable.btsId=GET_BTS_ID();
errCode = getBtsContextTable(&inDataBtsContextTable,&outDataBtsContextTable);
if(errCode != CLIB_SUCCESS)
    {
    LOG_PRINT(INFO,"get of context failed for bicId : %d",GET_BTS_ID());
    DalocOrdBuf((I_Void *)bichContext);
    return;
    }
memcpy(bichContext,outDataBtsContextTable->data,sizeof(OamsBichStandbyCardContext));

gOamsBichContextPtr->IpAdd.AAA = bichContext->IpAdd.AAA;
gOamsBichContextPtr->IpAdd.BBB = bichContext->IpAdd.BBB;
gOamsBichContextPtr->IpAdd.CCC = bichContext->IpAdd.CCC;
gOamsBichContextPtr->IpAdd.DDD = bichContext->IpAdd.DDD;
gOamsBichContextPtr->UdpPort = bichContext->UdpPort;

/* R2.9 changes starts */
if (GET_BTS_TYPE() != R2_BTS)
{    
  gOamsBichContextPtr->actProcState.procResult.nextState= bichContext->nextState;
  gOamsBichContextPtr->actProcState.ActiveProc = bichContext->activeProc; 

  for (i = 0; i < MAX_NUM_OF_CHILD_TRX; i++)
  {
    gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[i].trxId = bichContext->childTrxCntxt.ChildTrxInfo[i].trxId;
    gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[i].oprState = bichContext->childTrxCntxt.ChildTrxInfo[i].oprState;
  }
}
/* R2.9 changes ends */
DalocOrdBuf((I_Void *)bichContext);
return;
}
/* Mantis #31185*/

/**************************R3-BTS CHANGES START*********************************/

/******************************* Function  Header*****************************
Function Name : prepareAlarmFromFailureEventReportForR3()
Parameters    : 1.Abihm Bich Failure event report structure pointer
                2.Alarm String : copying the alarmString rxd from BTS
Return type   : I_Void
Purpose       : This func handles Failure Event Report rcvd from R3 BTS
*****************************************************************************/

I_Void prepareAlarmFromFailureEventReportForR3(CsappAbihmBichFailureEventReport *pRcvdMsg,
	I_U8 alarmString[])
{
	LOG_PRINT(INFO,"Entering[%s]",__func__);

	I_U32 severityValue = pRcvdMsg->severityValue;
	I_U8 probableCause = pRcvdMsg->probableCause.causeValue[0];
	I_U16 alarmId = 0;

	switch(probableCause)
	{ 
		case DMB_CONFIGURATION_MANAGEMENT:
		{       
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as"
				" DMB_CONFIGURATION_MANAGEMENT",__func__);
			alarmId = EVENT_DMB_CONFIGURATION_MANAGEMENT;
			break;
		}
		case TRX_START:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as"
				" TRX_START",__func__);
			alarmId = EVENT_TRX_START;
			break;
		}
		case FREQUENCY_CALIBRATION_SUPERVISION:	
		{       
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as"
				" FREQUENCY_CALIBRATION_SUPERVISION",__func__);
			alarmId = EVENT_FREQUENCY_CALIBRATION_SUPERVISION;
			break;
		}
		case SYSTEM_CALIBRATION_SUPERVISION:
		{       
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as SYSTEM_CALIBRATION_SUPERVISION",__func__);
			alarmId = EVENT_SYSTEM_CALIBRATION_SUPERVISION;
			break;
		}
		case CP_OVERLOAD:
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm"
				" cause as CP_OVERLOAD",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_CP_OVERLOAD;
			}
			else
			{
				alarmId = ALARM_CP_OVERLOAD_OK;
			}				
			break;
		}
		case CP_PROCESSOR_OVERLOAD:
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as CP_PROCESSOR_OVERLOAD",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_CP_PROCESSOR_OVERLOAD;
			}
			else
			{
				alarmId = ALARM_CP_PROCESSOR_OVERLOAD_OK;	
			}
			break;
		}
		case CP_DSP_COMMUNICATION_AND_STATUS_AUDIT: 
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause as"
				" CP_DSP_COMMUNICATION_AND_STATUS_AUDIT",__func__);
			alarmId = EVENT_CP_DSP_COMMUNICATION_AND_STATUS_AUDIT;
			break;
		}
		case SCTP_ASSOCIATION_A_B_CONNECTION:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as SCTP_ASSOCIATION_A_B_CONNECTION",__func__);
			alarmId = EVENT_SCTP_ASSOCIATION_A_B_CONNECTION;
			break;
		}
		case ETHERNET_SUPERVISION:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as ETHERNET_SUPERVISION",__func__);
			alarmId = EVENT_ETHERNET_SUPERVISION;
			break;
		}
		case INTERNAL_TEMPERATURE:
		{   
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as INTERNAL_TEMPERATURE",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{ 
				alarmId = EVENT_INTERNAL_TEMPERATURE;
			} 
			else if(severityValue == TRAP_SEVERITY_CRITICAL) 
			{	
				alarmId = ALARM_INTERNAL_TEMPERATURE;
			}
			else
			{
				alarmId = ALARM_INTERNAL_TEMPERATURE_OK;
			}
			break;
		}
		case DMB_CLOCK_CP_TEMPERATURE:
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as DMB_CLOCK_CP_TEMPERATURE",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{ 
				alarmId = EVENT_DMB_CLOCK_CP_TEMPERATURE;	
			} 
			else if(severityValue == TRAP_SEVERITY_CRITICAL) 
			{	
				alarmId = ALARM_DMB_CLOCK_CP_TEMPERATURE;
			}
			else
			{
				alarmId = ALARM_DMB_CLOCK_CP_TEMPERATURE_OK;
			}
			break;
		}
		case DMB_DSP_TEMPERATURE:
		{
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as DMB_DSP_TEMPERATURE",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{ 
				alarmId = EVENT_DMB_DSP_TEMPERATURE;
			} 	
			else if(severityValue == TRAP_SEVERITY_CRITICAL) 
			{	
				alarmId = ALARM_DMB_DSP_TEMPERATURE;		
			}
			else
			{
				alarmId = ALARM_DMB_DSP_TEMPERATURE_OK;
			}
			break;
		}
		case GPS_ANTENNA_SUPERVISION:
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as GPS_ANTENNA_SUPERVISION",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_GPS_ANTENNA_SUPERVISION;
			}
			else
			{
				alarmId = ALARM_GPS_ANTENNA_SUPERVISION_OK;
			}
			break;
		}
		case GPS_RECEIVER_HEALTH:
		{ 
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as GPS_RECEIVER_HEALTH",__func__);	
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_GPS_RECEIVER_HEALTH;
			}
			else
			{
				alarmId = ALARM_GPS_RECEIVER_HEALTH_OK;
			}
			break;
		}
		case GPS_SATELLITE_SIGNAL:	
		{
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as GPS_SATELLITE_SIGNAL",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_GPS_SATELLITE_SIGNAL;
			}
			else		
			{
				alarmId = ALARM_GPS_SATELLITE_SIGNAL_OK;
			}
			break;
		}
		case CP_SW_EXECUTION:	
		{       
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as CP_SW_EXECUTION",__func__);	
			alarmId = EVENT_CP_SW_EXECUTION;
			break;
		}	
		case PSU_TEMPERATURE:
		{       
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as PSU_TEMPERATURE",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{ 
				alarmId = EVENT_PSU_TEMPERATURE;
			} 
			else if(severityValue == TRAP_SEVERITY_CRITICAL) 
			{	
				alarmId = ALARM_PSU_TEMPERATURE;
			}
			else
			{
				alarmId = ALARM_PSU_TEMPERATURE_OK;
			}
			break;
		}
		case PSU_CURRENT:
		{       
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as PSU_CURRENT",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{ 
				alarmId = EVENT_PSU_CURRENT;
			} 
			else if(severityValue == TRAP_SEVERITY_CRITICAL) 
			{	
				alarmId = ALARM_PSU_CURRENT;
			}
			else
			{
				alarmId = ALARM_PSU_CURRENT_OK;
			}
			break;
		}
		case PSU_VOLTAGE:
		{         
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as PSU_VOLTAGE",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{ 
				alarmId = EVENT_PSU_VOLTAGE;
			} 
			else if(severityValue == TRAP_SEVERITY_CRITICAL) 
			{	
				alarmId = ALARM_PSU_VOLTAGE;
			}
			else
			{
				alarmId = ALARM_PSU_VOLTAGE_OK;
			}
			break;
		}
		case PSU_VERSION:
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as PSU_VERSION",__func__);
			alarmId = EVENT_PSU_VERSION;
			break;
		}
		case RTP_IP_ADDRESS:
		{ 
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as RTP_IP_ADDRESS",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_RTP_IP_ADDRESS;
			}
			else
			{
				alarmId = ALARM_RTP_IP_ADDRESS_OK;
			}	
			break;
		}
		case RTP_PORT:
		{  
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as RTP_PORT",__func__);
			if(severityValue == TRAP_SEVERITY_WARNING)
			{
				alarmId = ALARM_RTP_PORT;
			}
			else
			{		
				alarmId = ALARM_RTP_PORT_OK;
			}
			break;
		}
		case FPGA_OBN:
		{    
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as FPGA_OBN",__func__);
			alarmId = EVENT_FPGA_OBN;
			break;
		}
		case FPGA_TIME_SLOT_BOUNDARY:
		{   
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as FPGA_TIME_SLOT_BOUNDARY",__func__);
			alarmId = EVENT_FPGA_TIME_SLOT_BOUNDARY;
			break;
		}
		case SRIO_PHY:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as SRIO_PHY",__func__);	
			alarmId = EVENT_SRIO_PHY;
			break;
		}
		case SRIO_I2C:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as SRIO_I2C",__func__);
			alarmId = EVENT_SRIO_I2C;
			break;
		}
		case SRIO_ADC_CONTROL:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as SRIO_ADC_CONTROL",__func__);
			alarmId = EVENT_SRIO_ADC_CONTROL;
			break;
		}
		case SRIO_SPI:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as SRIO_SPI",__func__);
			alarmId = EVENT_SRIO_SPI;
			break;
		}
		case MAIN_PLL_LOCK:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as MAIN_PLL_LOCK",__func__);
			alarmId = EVENT_MAIN_PLL_LOCK;
		break;
		}
		case NB_AB_BURST_SUPERVISION:
		{        
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as NB_AB_BURST_SUPERVISION",__func__);	
			alarmId = EVENT_NB_AB_BURST_SUPERVISION;
			break;
		}
		case DLNA_IDENTITY:
		{    
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as DLNA_IDENTITY",__func__);
			alarmId = EVENT_DLNA_IDENTITY;
			break;
		}
		case DLNA_CALIBRATION:
		{    
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as DLNA_CALIBRATION",__func__);
			alarmId = EVENT_DLNA_CALIBRATION;
			break;
		}	
		case FLASH_SUPERVISION:
		{    
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Alarm cause"
				" as FLASH_SUPERVISION",__func__);
			alarmId = EVENT_FLASH_SUPERVISION;
			break;
		}

		default:
		{	
			LOG_PRINT(INFO,"[%s:]FAILURE_EVENT_REPORT contain Unhandled"
				" Probable cause[%d]",__func__, probableCause);
			return;
				
		}
	}	
	fillAndSendBichCfgAlarmInd(alarmId,severityValue,alarmString);
	LOG_PRINT(INFO,"Exit from [%s]",__func__);
	return;
}


/**************************R3-BTS CHANGES END***************************/


/******************************* Function  Header*****************************
 ***********************************STATE BASED PROCEDURES END*******************************************************************************************************************/
