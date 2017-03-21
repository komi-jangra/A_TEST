/*************************************************************** File Header ***
File Name      : oamscfg_clk_object_handler.c
Purpose        : This file contains functions defintions for Clock Object handling.
Project        : BSC
Subsystem      : OAMS 
Author         : Bikram Bhatt (BB) / VNL Gurgaon
CSCI id        :
Version        :
 ********************************************************************** End ***/

#include <oamscfg_includes.h>
/********************************* Function  Header********************************
Function Name:       isSetClkSrcCfgReqValid()
Parameters:          void
Return type:         I_U16
Purpose:             Func checks input request which is rcvd from CM and if the input
                     request is valid then this function returns TRUE else FALSE.
                     Request is considered as Valid if any of the given Clock Source 
                     are valid.
Other Note:
 ************************************************************************************/

I_U32 isSetClkSrcCfgReqValid(I_Void)
{
   I_U8   i = 0,j=0;
   I_U8   frameId = 0;
   I_U8   slotId = 0;
   I_U16  trunkPortId = 0;
   I_U32  priority = 0;
   I_U16  result = CM_SUCCESS;
   I_U32  E1Num = 0;
   I_U32  OperatorControlTrunkState;
   I_Bool ReqIsValid = FALSE;
   I_U32  clockTripletSize = 0 ;
   I_U32  sizeOfCfgClkSrc=0;
   ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = PNULL;   
   ClkSourceConfigTableApi *ClkSourceConfigTableApiDbPtr ;
   I_U16  *trunkIdPtr;
   I_U32 outRows;
   I_U16 outSize;
   I_U32  physicalState;
   TrunkPortStatusTableIndices trunkPortStsIndex;
   TrunkPortStatusTableApi *trunkPortStsApiPtr;

   clockTripletSize = offsetof(ClkSourceConfigTableApi,trunkPortId2)-offsetof(ClkSourceConfigTableApi,trunkPortId1); 
   pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)((sCmMsg *)gCfgMsgBuf + 1) ;

   /* Is Card State Change Notification already rcvd for Standby or Recovery */
   /* ToDo this will be done while code HA */

   /* Is Clock Source Configuration is already on-going */
   if ( isClkSrcProcOngoing() ) {
     LOG_PRINT(LOG_DEBUG," Clr Src Already on-going"); 
     return CM_ERR_CLK_SRC_CFG_IN_PROGRESS;
   }
   
   /* Is there Request for Clock Clk */
   if ( !(pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc) ) {
     LOG_PRINT(LOG_DEBUG," No Clk Src is Requested[%d]",
               pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc 
              );
     return CM_ERR_ATLEAST_ONE_CLK_SRC_IS_NEEDED;
   }

   /*If it is modification case then check modification case is valid or not
   **Please note that atmax only one row is allowed for the clock source 
   **so if there exists already row and new row has differenet primary key 
   **then reject the request 
   */ 
   if ( CLIB_SUCCESS == getallClkSourceConfigTable( &ClkSourceConfigTableApiDbPtr,&outRows,&outSize) ) {
     if ( ClkSourceConfigTableApiDbPtr->index != pClkSrcCfgTblApiRcvdPtr->index) {
        LOG_PRINT(LOG_DEBUG,"Invalid row recieved for Clk Src Configuration with different Index.");
        free(ClkSourceConfigTableApiDbPtr);
        return CM_ERR_INVALID_REQUEST;
     }
     sizeOfCfgClkSrc = offsetof(ClkSourceConfigTableApi,slotId1) + 
                       clockTripletSize*pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc;    
     /*Check if the requested clock resources are already configured */
     if ( !compareRcvdMsgAndDbEntry(
                                   pClkSrcCfgTblApiRcvdPtr,
                                   ClkSourceConfigTableApiDbPtr,
                                   sizeOfCfgClkSrc
                                  ) 
        ) {
        free(ClkSourceConfigTableApiDbPtr);
        return CM_ERR_CLK_SRC_ALRDY_CONFIGURED;
     }
     free(ClkSourceConfigTableApiDbPtr);
   }
  
   /* Is Configured Clock Count exceeds MAXIMUM supported list */
   if ( pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc > MAX_CFG_CLK_COUNT ) {
     LOG_PRINT(LOG_DEBUG," Clk Src Count exceeds MAX_CFG_CLK_COUNT %d",
               MAX_CFG_CLK_COUNT 
              );
     return CM_ERR_CLK_SRC_CFG_COUNT_INVALID;
   }
   
   /* Check configured Clock Sources and Priorities are Unique */
   clockTripletSize = offsetof(ClkSourceConfigTableApi,trunkPortId2)-offsetof(ClkSourceConfigTableApi,trunkPortId1); 
   trunkIdPtr = (I_U16 *)((I_U8 *)pClkSrcCfgTblApiRcvdPtr + offsetof(ClkSourceConfigTableApi,trunkPortId1));
   for (i=1; i < pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc;  i++) {
     for (j=0; j <= i-1 ; j++) {
        if ( 
             ( (*(I_U16 *)(( I_U8* )trunkIdPtr + j*clockTripletSize ))  /* TrunkPort */
                                   == 
             (*(I_U16 *)(( I_U8* )trunkIdPtr + i*clockTripletSize)) ) /* TrunkPort */
           ) {
             LOG_PRINT(LOG_DEBUG,"Same Trunk Port is used for multiple Clock Sources.");
             return CM_ERR_CLK_DUPLICATE_TRUNKPORT;
        } 
        /* Check for priority uniqueness */
        if ( 
             ( (*(I_U32 *)(( I_U8* )trunkIdPtr + j*clockTripletSize + sizeof(I_U16) ))  /* Priority */
                                   == 
             (*(I_U32 *)(( I_U8* )trunkIdPtr + i*clockTripletSize + sizeof(I_U16)))) /* Priority */
           ) {
             LOG_PRINT(LOG_DEBUG,"Same Priority is used for multiple Clock Sources.");
             return CM_ERR_CLK_DUPLICATE_PRIORITY;
        }         
     }
   }
   
   updMaxClkConfig(pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc);
   updDbIndex(pClkSrcCfgTblApiRcvdPtr->index);
   frameId = pClkSrcCfgTblApiRcvdPtr->chasisFrameId;
   
   for (i=0; i < pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc; i++) {
     switch (i) {
      case 0 : /* 1 Clock Source is configured*/
        // frameId = pClkSrcCfgTblApiRcvdPtr->chasisFrameId;
        slotId  = pClkSrcCfgTblApiRcvdPtr->slotId1;
        trunkPortId = pClkSrcCfgTblApiRcvdPtr->trunkPortId1;
        priority = pClkSrcCfgTblApiRcvdPtr->clkPriority1;
        break; 
      case 1 : /* 2 Clock Sources are configured */
        slotId  = pClkSrcCfgTblApiRcvdPtr->slotId2;
        trunkPortId = pClkSrcCfgTblApiRcvdPtr->trunkPortId2;
        priority = pClkSrcCfgTblApiRcvdPtr->clkPriority2;     
        break;
      case 2 : /* 3 Clock Sources are configured */
        slotId  = pClkSrcCfgTblApiRcvdPtr->slotId3;
        trunkPortId = pClkSrcCfgTblApiRcvdPtr->trunkPortId3;
        priority = pClkSrcCfgTblApiRcvdPtr->clkPriority3;      
        break;
      case 3 : /* 4 Clock Sources are configured */
        slotId  = pClkSrcCfgTblApiRcvdPtr->slotId4;
        trunkPortId = pClkSrcCfgTblApiRcvdPtr->trunkPortId4;
        priority = pClkSrcCfgTblApiRcvdPtr->clkPriority4;     
        break;
      case 4 : /* 5 Clock Sources are configred */
        slotId  = pClkSrcCfgTblApiRcvdPtr->slotId5;
        trunkPortId = pClkSrcCfgTblApiRcvdPtr->trunkPortId5;
        priority = pClkSrcCfgTblApiRcvdPtr->clkPriority5;      
        break;
      default: /* Do nothitng */
        break;
     } /* switch */
     updClkSrcNrslt(i,frameId,slotId,trunkPortId,priority);

     /*Check priority is valid */
     if (priority < CLOCK_PRIORITY_1 || priority > CLOCK_PRIORITY_5) {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_CLK_INVALID_PRIORITY ", 
                  trunkPortId
                 ); 
        updClkSrcLvlResult(i,CM_ERR_CLK_INVALID_PRIORITY);
        continue;
     }
    
     /*BSC R2.0 Changes Starts*/
     /*Is TrunkId Physically Present*/
     trunkPortStsIndex.chasisFrameId = frameId;
     trunkPortStsIndex.slotId = slotId;
     trunkPortStsIndex.trunkPortId = trunkPortId;
     if ( CLIB_SUCCESS != getTrunkPortStatusTable(&trunkPortStsIndex,&trunkPortStsApiPtr)) 
     {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB ", 
                  trunkPortId); 
        updClkSrcLvlResult(i,CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB);
        continue;
     }
     else
     {
        physicalState =  trunkPortStsApiPtr->physicalPresenceState;
        free(trunkPortStsApiPtr);

        if(physicalState != PRESENT)
        {
           LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_TRUNKPORT_PHYSICALLY_NOT_PRESENT", 
                     trunkPortId); 
           updClkSrcLvlResult(i,CM_ERR_TRUNKPORT_PHYSICALLY_NOT_PRESENT);
           continue;
        }
     }
 
     /*BSC R2.0 Changes Ends*/

     /* Is TRUNKID exists in TrunkPortTable */
     if ( I_TRUE != findTrunkIdTrunkPortTable(trunkPortId,&OperatorControlTrunkState)) {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB ", 
                  trunkPortId); 
        updClkSrcLvlResult(i,CM_ERR_TRUNK_ID_NOT_PRESENT_IN_DB);
        continue;
     }
     else
     {
       if(OperatorControlTrunkState != ACTIVATED)
       {
          LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_TRUNKPORT_DISABLED", 
                    trunkPortId); 
          updClkSrcLvlResult(i,CM_ERR_TRUNKPORT_DISABLED);
          continue;
       } 
     }
     E1Num = trunkPortId; 
     //if ( CFG_SUCCESS != isAnyTrunkExistOnGivenPort(trunkPortId) ) {
     //    LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_E1_MAP_NOT_CREATED ", 
     //              trunkPortId
     //              );      
     //     updClkSrcLvlResult(i,CM_ERR_E1_MAP_NOT_CREATED);
     //      continue;
     //   }

     /* Check E1Num is configured towards A-Interface */
     if (! isE1NumOfTypeAIF(E1Num)) {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_E1_IS_NOT_A_INTERFACE_TYPE ", 
                  trunkPortId
                 );     
        updClkSrcLvlResult(i,CM_ERR_E1_IS_NOT_A_INTERFACE_TYPE);
        continue;
     }
     if(! isTrunkPortFirstOrSecondOfFramer(E1Num)) 
     {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] is not first or second TrunkPort of a framer",
                trunkPortId);     
        updClkSrcLvlResult(i,CM_ERR_INVALID_TRUNKPORT);
        continue;
            
     }
     /* Is TRUNKID is Operator_Enable */
     if ( ! isTrunkPortEnable(E1Num) ) {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_TRUNKPORT_DISABLED ", 
                  trunkPortId
                 );      
        updClkSrcLvlResult(i,CM_ERR_TRUNKPORT_DISABLED);
        continue;
     }
     
     /* Is TRUNKID has active LOS Alarm Clock Source are allowed for configuration */
     if (isLOSactive(E1Num)) {
        LOG_PRINT(LOG_DEBUG," Clk Src [%d] CM_ERR_LOS_ACTIVE ", 
                  trunkPortId
                 );      
        //updClkSrcLvlResult(i,CM_ERR_LOS_ACTIVE);
        //continue;
     }
     /* If control reaches here then  Current Clock Source is Valid */
     ReqIsValid = TRUE; 
     
   }
   
   /* Incase request is rcvd only one Clock Source then send the exact failure cause to the user */
   if (1 == pClkSrcCfgTblApiRcvdPtr->totalNumClkSrc ) {
      return readClkSrcLvlResult(0);
   }
   return (ReqIsValid ? CM_SUCCESS : CM_ERR_INVALID_REQUEST) ;
}

/********************************* Function  Header********************************
Function Name:       sendClkSrcCfgReqToOil()
Parameters:          void
Return type:         I_Bool
Purpose:             This function construct message OAMS_CFG_OIL_SET_CLK_SRC_REQ
                     and send it to OIL. CFG fills this message from its internal 
                     structure.
Other Note:
 ************************************************************************************/
I_Bool sendClkSrcCfgReqToOil(I_Void)
{
   I_U8 i=0;
   I_U8 clkSrcCount = 0;
   ClkSrcPortPriority *clkSrcPortPriorityPtr = NULL;
   OamsCfgOilSetClkSrcReq *oamsCfgOilSetClkSrcReqPtr = NULL;

   oamsCfgOilSetClkSrcReqPtr = AlocMsgBuf(sizeof(OamsCfgOilSetClkSrcReq)); 

   if (!oamsCfgOilSetClkSrcReqPtr) { 
      LOG_PRINT(LOG_CRITICAL,"AllocMsgBuf failed in sendClkSrcCfgReqToOil"); 
      return FALSE;  
   } 

   memset(oamsCfgOilSetClkSrcReqPtr,0,sizeof(OamsCfgOilSetClkSrcReq)) ; 

   oamsCfgOilSetClkSrcReqPtr->sHdr.msgType     = OAMS_CFG_OIL_SET_CLK_SRC_REQ; 
   oamsCfgOilSetClkSrcReqPtr->sHdr.src.entity  = ENT_OAMS_CFG; 
   oamsCfgOilSetClkSrcReqPtr->sHdr.dest.entity = ENT_OAM_OIL; 

   oamsCfgOilSetClkSrcReqPtr->maxClkConfig = 0;
   
   //Fill only valid clock sources in message
   clkSrcCount = 0;
   clkSrcPortPriorityPtr = oamsCfgOilSetClkSrcReqPtr->clkSrcPriority;
   for (i=0; i < readMaxClkConfig(); i++) {
     if ( CM_SUCCESS == readClkSrcLvlResult(i)) {
       readClkSrc(i,
                  clkSrcPortPriorityPtr[clkSrcCount].frameId,
                  clkSrcPortPriorityPtr[clkSrcCount].slotId,
                  clkSrcPortPriorityPtr[clkSrcCount].trunkPortId,
                  clkSrcPortPriorityPtr[clkSrcCount].priority
                 );
       clkSrcCount++;          
     }
   }
   oamsCfgOilSetClkSrcReqPtr->maxClkConfig = clkSrcCount;

   LOG_PRINT(LOG_DEBUG," msgType = %d, sHdr.src.entity = %d, sHdr.dest.entity = %d", 
                       oamsCfgOilSetClkSrcReqPtr->sHdr.msgType,
                       oamsCfgOilSetClkSrcReqPtr->sHdr.src.entity,
                       oamsCfgOilSetClkSrcReqPtr->sHdr.dest.entity);    

   if (SendMsg(oamsCfgOilSetClkSrcReqPtr, 1, sizeof(OamsCfgOilSetClkSrcReq)) < 0) 
   { 
      LOG_PRINT(LOG_CRITICAL,"CFG: In sendClkSrcCfgReqToOil() - msg sending failed"); 
      //DalocMsgBuf((I_PVoid) oamsCfgOilSetClkSrcReqPtr); 
      return(FALSE); 
   } 

   LOG_PRINT(LOG_DEBUG," CFG send OAMS_CFG_OIL_SET_CLK_SRC_REQ msg to OIL");

   return(TRUE); 
}

/********************************* Function  Header********************************
Function Name:       findClkSrc()
Parameters:          frameId,slotId,trunkPortId
Return type:         Index
Purpose:             Find Clock Source in internal Clock Configuraion Data and if 
                     clock source is found in that case it retruns the index
                     If the clock source is not found in that it returns invalid 
                     Index. In CS4.0 TrunkPortId itseld is unique so other parameters 
                     are not checked
Other Note:
 ************************************************************************************/
I_U8 findClkSrc(I_U8 frameId, I_U8 slotId, I_U16 trunkPId)
{
   I_U8   i=0;
   
   for (i=0; i < gclkSrcCfgData.clkSrcCfg.maxClkConfig; i++) {
    if (readClkSrcTrunkPortIdAtIdx(i) == trunkPId) {
      return i;
    }  
   }
   return INVALID_CLK_SRC_IDX;
}

/********************************* Function  Header********************************
Function Name:       sendClkSrcResultEventToAfh()
Parameters:          void
Return type:         void
Purpose:             Check Clock Source Configuration result and send the needed alarms
                     These Events are not shown to the operator , OMC needs these
                     events to reconcile the DB as ACK has been sent to OMC after the 
                     validiation checks. Only one event would be suffice to OMC as OMC 
                     would do the reconile and it will get the updated DB. But to keep
                     design generic events are raised for each alarm clock.
Other Note:
 ************************************************************************************/
I_Void sendClkSrcResultEventToAfh(I_Void)
{
  I_U8 i = 0;

  OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr = NULL;
  
  LOG_PRINT(DEBUG,"readMaxClkConfig val is %d", readMaxClkConfig());
  for (i = 0; i <  readMaxClkConfig(); i++) 
  {  
    oamsCfgAfhSysAlarmPtr = (OamsCfgAfhSysAlarm *)AlocMsgBuf(sizeof(OamsCfgAfhSysAlarm)); 

    if (oamsCfgAfhSysAlarmPtr == NULL) { 
       LOG_PRINT(LOG_CRITICAL,"AllocMsgBuf failed in sendClkSrcResultEventToAfh"); 
       return ;  
    } 

    memset(oamsCfgAfhSysAlarmPtr,0,sizeof(OamsCfgAfhSysAlarm)) ; 

    oamsCfgAfhSysAlarmPtr->sysHdr.msgType     = OAMS_CFG_AFH_ALARM_IND; 
    oamsCfgAfhSysAlarmPtr->sysHdr.src.entity  = ENT_OAMS_CFG; 
    oamsCfgAfhSysAlarmPtr->sysHdr.dest.entity = ENT_OAM_AFH; 

    readClkSrc(i,
               oamsCfgAfhSysAlarmPtr->sysAlarm.key1, 
               oamsCfgAfhSysAlarmPtr->sysAlarm.key2,
               oamsCfgAfhSysAlarmPtr->sysAlarm.key3,
               oamsCfgAfhSysAlarmPtr->sysAlarm.key4
              );    
    //oamsCfgAfhSysAlarmPtr->sysAlarm.info3 = OAMS_OBJTYPE_TRUNKPORT;
    //FillObjTypeFromSlotId( oamsCfgAfhSysAlarmPtr->sysAlarm.key2,
    //                       oamsCfgAfhSysAlarmPtr->sysAlarm.info3);
		LOG_PRINT(LOG_DEBUG,"KEYS 1 = %d 2 = %d 3 = %d 4 = %d",oamsCfgAfhSysAlarmPtr->sysAlarm.key1,oamsCfgAfhSysAlarmPtr->sysAlarm.key2,oamsCfgAfhSysAlarmPtr->sysAlarm.key3,oamsCfgAfhSysAlarmPtr->sysAlarm.key4);
		if((oamsCfgAfhSysAlarmPtr->sysAlarm.key2 == 5) || (oamsCfgAfhSysAlarmPtr->sysAlarm.key2 == 6))
		{				
			LOG_PRINT(LOG_DEBUG,"OBJ TYPE = EIC ");			
    	oamsCfgAfhSysAlarmPtr->sysAlarm.info3 = OAMS_OBJTYPE_EIC;
		}
		else
    {
			LOG_PRINT(LOG_DEBUG,"OBJ TYPE = ICC ");			
			oamsCfgAfhSysAlarmPtr->sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    }
    
    if ( isClkSrcResultOK(readClkSrcLvlResult(i) ) ) 
    {
      oamsCfgAfhSysAlarmPtr->sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;      
      oamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId = EVENT_CLOCK_SRC_CFG_SUCCESSFUL;    
 
     sprintf(oamsCfgAfhSysAlarmPtr->sysAlarm.infoString,
                   CLK_SRC_OK_EVENT_STRING,
                   oamsCfgAfhSysAlarmPtr->sysAlarm.key1,   
                   oamsCfgAfhSysAlarmPtr->sysAlarm.key2,   
                   oamsCfgAfhSysAlarmPtr->sysAlarm.key3);   
    }
    else 
    {
      oamsCfgAfhSysAlarmPtr->sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;      
      oamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId = EVENT_CLOCK_SRC_CFG_FAILED;

          sprintf(oamsCfgAfhSysAlarmPtr->sysAlarm.infoString,
                   CLK_SRC_NOK_EVENT_STRING,
                   oamsCfgAfhSysAlarmPtr->sysAlarm.key1,   
                   oamsCfgAfhSysAlarmPtr->sysAlarm.key2,   
                  oamsCfgAfhSysAlarmPtr->sysAlarm.key3); 
    }

    FillObjTypeFromSlotId(oamsCfgAfhSysAlarmPtr->sysAlarm.key2,oamsCfgAfhSysAlarmPtr->sysAlarm.info3);
    if (SendMsg(oamsCfgAfhSysAlarmPtr, 1, sizeof(OamsCfgAfhSysAlarm)) < 0) 
    { 
       LOG_PRINT(LOG_CRITICAL,"CFG: sendClkSrcResultEventToAfh() - msg sending failed");
       DalocMsgBuf((I_PVoid) oamsCfgAfhSysAlarmPtr); 
       return; 
    } 

    #if 0
    if ( isClkSrcResultOK(readClkSrcLvlResult(i) ) ) 
    {
       oamsCfgAfhSysAlarmPtr->sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;      
       oamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId = EVENT_CLOCK_SRC_APPLIED;    

         sprintf(oamsCfgAfhSysAlarmPtr->sysAlarm.infoString,
                  CLK_SRC_OK_EVENT_STRING,
                  oamsCfgAfhSysAlarmPtr->sysAlarm.key1,   
                  oamsCfgAfhSysAlarmPtr->sysAlarm.key2,   
                  oamsCfgAfhSysAlarmPtr->sysAlarm.key3);   
       if (SendMsg(oamsCfgAfhSysAlarmPtr, 1, sizeof(OamsCfgAfhSysAlarm)) < 0) 
       { 
          LOG_PRINT(LOG_CRITICAL,"CFG: sendClkSrcResultEventToAfh() - msg sending failed");
          DalocMsgBuf((I_PVoid) oamsCfgAfhSysAlarmPtr); 
          return; 
       } 

    }

    LOG_PRINT(LOG_DEBUG," msgType = %d, sHdr.src.entity = %d, sHdr.dest.entity = %d", 
                        oamsCfgAfhSysAlarmPtr->sysHdr.msgType,
                        oamsCfgAfhSysAlarmPtr->sysHdr.src.entity,
                        oamsCfgAfhSysAlarmPtr->sysHdr.dest.entity); 
   
    #endif 
  }
  return ;
}

/********************************* Function  Header********************************
Function Name:       updClkSrcCfgInDB()
Parameters:          void
Return type:         void
Purpose:             Update successful configuration in DB. First it update in DB.
                     If update fails in DB in that case it calls the insert as 
                     update will fail in case table does not exist.
Other Note:
 ************************************************************************************/
I_Void updClkSrcCfgInDB(I_Void)
{
  I_S32 eCode = CLIB_SUCCESS;
  I_U32 outRow  = 0;
  I_U16 outSize = 0;
  I_U32 i     = 0; 
  I_U32 priority = 0xFF;
  ClkSourceConfigTableApi clkSrcCfgTableApi;
  ClkSourceConfigTableApi *clkSrcCfgTableApiDbPtr;

  ClkSourceConfigStatusTableApi clkStsTbl;
  ClkSourceConfigStatusTableApi *outData;

  ClkSourceConfigStatusTableIndices clkStsTblIndex;

  
  LOG_PRINT(LOG_INFO," [%s] Enter ",__func__);

  memset((void *)&clkSrcCfgTableApi,0xFF,sizeof  clkSrcCfgTableApi );
  clkSrcCfgTableApi.clkPriority1 = 0xFF;
  clkSrcCfgTableApi.clkPriority2 = 0xFF;
  clkSrcCfgTableApi.clkPriority3 = 0xFF;
  clkSrcCfgTableApi.clkPriority4 = 0xFF;
  clkSrcCfgTableApi.clkPriority5 = 0xFF;
  clkSrcCfgTableApi.totalNumClkSrc = 0;
  clkSrcCfgTableApi.index = readDbIndex();  
  
  for (i=0; i < readMaxClkConfig(); i++) {
    if ( isClkSrcResultOK( readClkSrcLvlResult(i) ) ) {
       clkSrcCfgTableApi.totalNumClkSrc++;
    }
    else {
      continue ;
    }
    priority = 0xFF;
    switch (clkSrcCfgTableApi.totalNumClkSrc) {
     case 1 : /* 1 Clock Source is configured Successful*/
       readClkSrc(i,
                  clkSrcCfgTableApi.chasisFrameId,
                  clkSrcCfgTableApi.slotId1,
                  clkSrcCfgTableApi.trunkPortId1,
                  clkSrcCfgTableApi.clkPriority1);
          priority = clkSrcCfgTableApi.clkPriority1;
       break; 
     case 2 : /* 2 Clock Sources are configured Successful */
       readClkSrc(i,
                  clkSrcCfgTableApi.chasisFrameId,
                  clkSrcCfgTableApi.slotId2,
                  clkSrcCfgTableApi.trunkPortId2,
                  clkSrcCfgTableApi.clkPriority2);   
          priority = clkSrcCfgTableApi.clkPriority2;
       break;
     case 3 : /* 3 Clock Sources are configured Sucessful */
       readClkSrc(i,
                  clkSrcCfgTableApi.chasisFrameId,
                  clkSrcCfgTableApi.slotId3,
                  clkSrcCfgTableApi.trunkPortId3,
                  clkSrcCfgTableApi.clkPriority3);   
          priority = clkSrcCfgTableApi.clkPriority3;
       break;
     case 4 : /* 4 Clock Sources are configured Sucessful*/
       readClkSrc(i,
                  clkSrcCfgTableApi.chasisFrameId,
                  clkSrcCfgTableApi.slotId4,
                  clkSrcCfgTableApi.trunkPortId4,
                  clkSrcCfgTableApi.clkPriority4);  
          priority = clkSrcCfgTableApi.clkPriority4;
       break;
     case 5 : /* 5 Clock Sources are configred Sucessful*/
       readClkSrc(i,
                  clkSrcCfgTableApi.chasisFrameId,
                  clkSrcCfgTableApi.slotId5,
                  clkSrcCfgTableApi.trunkPortId5,
                  clkSrcCfgTableApi.clkPriority5); 
          priority = clkSrcCfgTableApi.clkPriority5;
       break;
     default: /* Do nothitng */
       break;
    } /* switch */

    /*BSC R2.0 Changes Starts*/

    readClkSrcSts(i,
          clkStsTbl.chasisFrameId,
          clkStsTbl.slotId,
          clkStsTbl.trunkPortId,
          clkStsTbl.clkConfigStatus );
    
    clkStsTblIndex.chasisFrameId = clkStsTbl.chasisFrameId;
    clkStsTblIndex.slotId = clkStsTbl.slotId;
    clkStsTblIndex.trunkPortId = clkStsTbl.trunkPortId;

    if(CLIB_SUCCESS == getClkSourceConfigStatusTable(&clkStsTblIndex,&outData) )
    {
      if(gE1Data[ clkStsTbl.trunkPortId ].LOS_Active == TRUE )
      {
         if(outData->clkConfigStatus != PENDING)
         {
            clkStsTbl.clkConfigStatus = PENDING;
            if(CLIB_SUCCESS != updateClkSourceConfigStatusTable(&clkStsTbl) )
            {
               updClkSrcLvlResult(i,CM_ERR_INSERT_DB_OPER_FAILED);  
            }
            sendClkSourcePendingAlarm(clkStsTbl.chasisFrameId,clkStsTbl.slotId,
                 clkStsTbl.trunkPortId,priority);
         }
      }//LOS_ACTIV
      else
      {
         if(outData->clkConfigStatus != APPLIED)
         {
            clkStsTbl.clkConfigStatus = APPLIED;
            if(CLIB_SUCCESS != updateClkSourceConfigStatusTable(&clkStsTbl) )
            {
               updClkSrcLvlResult(i,CM_ERR_INSERT_DB_OPER_FAILED);  
            }
            sendClkSourceAppliedAlarm(clkStsTbl.chasisFrameId,clkStsTbl.slotId,
                 clkStsTbl.trunkPortId,priority);
         }
      }

      free(outData);
    }  
    else
    {
      if(gE1Data[ clkStsTbl.trunkPortId ].LOS_Active == TRUE )
      {
         clkStsTbl.clkConfigStatus = PENDING;
         if(CLIB_SUCCESS != insertClkSourceConfigStatusTable(&clkStsTbl) )
         {
            updClkSrcLvlResult(i,CM_ERR_INSERT_DB_OPER_FAILED); 
         }
         sendClkSourcePendingAlarm(clkStsTbl.chasisFrameId,clkStsTbl.slotId,
              clkStsTbl.trunkPortId,priority);
      }//LOS_ACTIV
      else
      {
         clkStsTbl.clkConfigStatus = APPLIED;
         if(CLIB_SUCCESS != insertClkSourceConfigStatusTable(&clkStsTbl) )
         {
            updClkSrcLvlResult(i,CM_ERR_INSERT_DB_OPER_FAILED); 
         }
         sendClkSourceAppliedAlarm(clkStsTbl.chasisFrameId,clkStsTbl.slotId,
              clkStsTbl.trunkPortId,priority);
      }

    }
    /*BSC R2.0 Changes Ends*/
  }
  
  if ( CLIB_SUCCESS == getallClkSourceConfigTable(&clkSrcCfgTableApiDbPtr , &outRow, &outSize) ) {
    //This indicate there already exists a ROW , so just update that ROW 
    free(clkSrcCfgTableApiDbPtr);
    eCode = updateClkSourceConfigTable(&clkSrcCfgTableApi);
    if (eCode != CLIB_SUCCESS) {
      LOG_PRINT(DEBUG,"\[%s]updateClkSourceConfigTable Fail: [%d]",__func__,eCode);
      for (i=0; i < readMaxClkConfig(); i++) {
        updClkSrcLvlResult(i,CM_ERR_INSERT_DB_OPER_FAILED); 
      }
    }
  }
  else {
     eCode = insertClkSourceConfigTable(&clkSrcCfgTableApi);
     if (eCode != CLIB_SUCCESS)
     {
        LOG_PRINT(DEBUG,"[%s] insertClkSourceConfigTable Fail: [%d]",__func__,eCode);
        for (i=0; i < readMaxClkConfig(); i++) {
          updClkSrcLvlResult(i,CM_ERR_INSERT_DB_OPER_FAILED); 
        }
        return ;
     }
  }  
  return ;
}
/********************************* Function  Header********************************
Function Name:       setOilClkSrcRespHldr()
Parameters:          void
Return type:         void
Purpose:             Handling of Clock Source Configuration Respose from Oil
Other Note:
 ************************************************************************************/
I_Void setOilClkSrcRespHldr(I_Void)
{
  I_U8 i = 0,j;
  OamOilCfgSetClkSrcResp *OamOilCfgSetClkSrcRespPtr = NULL;
  OamOilCfgSetClkSrcRespPtr = (OamOilCfgSetClkSrcResp *)gCfgMsgBuf;
  ClkSrcPortPriorityResult *ClkSrcPortPriorityResultPtr = NULL;
  
  LOG_PRINT(DEBUG,"setOilClkSrcRespHldr: Entering in function");
  ClkSrcPortPriorityResultPtr = OamOilCfgSetClkSrcRespPtr->clkSrcPriorityResult;
  for (i=0; i < OamOilCfgSetClkSrcRespPtr->maxClkConfig; i++) {
    if (isClkSrcResultNOKFromOil(ClkSrcPortPriorityResultPtr[i].result)) {
       j = findClkSrc(ClkSrcPortPriorityResultPtr[i].frameId,
                      ClkSrcPortPriorityResultPtr[i].slotId,
                      ClkSrcPortPriorityResultPtr[i].trunkPortId);
       if (INVALID_CLK_SRC_IDX != j ) {
        updClkSrcLvlResult(j,CM_ERR_BPM_OPERATION_FAILS);
        LOG_PRINT(LOG_CRITICAL,"Clk Src Cfg Fails from Bpm %d",ClkSrcPortPriorityResultPtr[i].result);
       } 
       else {
        LOG_PRINT(LOG_CRITICAL,"Invalid Clk Src in OamOilCfgSetClkSrcResp");
       }
    }
  }
  updClkSrcCfgInDB();
  sendClkSrcResultEventToAfh();
/*Mantis Id 28077 start */
//  setClkSrcProcState(clkSrcCfgNone);
/*Mantis Id 28077 end */
  LOG_PRINT(DEBUG,"setOilClkSrcRespHldr: Exiting in function");
  return ;
}
/********************************* Function  Header********************************
Function Name:       setClkSrcTblHdlr()
Parameters:          void
Return type:         void
Purpose:             Implementation of Set Clock Source Configuration message
Other Note:
 ************************************************************************************/
I_Void setClkSrcTblHdlr(I_Void)
{
   I_U32 isClkSrcReqValid = CM_SUCCESS;
   LOG_PRINT(LOG_INFO," setClkSrcTblHdlr... ");
   switch (((SysHdr*) gCfgMsgBuf)->msgType) {
      case BSC_API_SET_CLKSOURCECONFIGTABLE: 
            //Check the validity of the input request
            isClkSrcReqValid =  isSetClkSrcCfgReqValid();
            if (CM_ERR_CLK_SRC_ALRDY_CONFIGURED == isClkSrcReqValid) {
               cfgSendAckToCm();
               return ;
            }
            if ( CM_SUCCESS != isClkSrcReqValid ) {
              cfgSendNackToCm(isClkSrcReqValid);
              return;
            }
            /* Request from CM has some valid Clock Sources send the request to OIL */
            if ( sendClkSrcCfgReqToOil() ) {
               CALLCLEANDBTABLE(ClkSourceConfigStatusTable);
              setClkSrcProcState(clkSrcCfgOngoing);
              cfgSendAckToCm();
            }
            else {
              cfgSendNackToCm(CM_ERR_SEND_MESSAGE_FAILS);
            }
            return;
   }
   
   return ;

}

/********************************* Function  Header********************************
Function Name:       IsTrunkPortConfiguredAsClkSrc
Parameters:          I_U16  
Return type:         I_Bool
Purpose:             Check if passed trunk port is configured as clock source or not 
Other Note:          Added for CS4.0 
************************************************************************************/
I_Bool IsTrunkPortConfiguredAsClkSrc(I_U16 TrunkPortID)
{
    ClkSourceConfigTableApi *clkSrcCfgTableApi;
    I_U32 outRow  = 0;
    I_U16 outSize = 0;
    I_U8  i       = 0;   

    LOG_PRINT(LOG_INFO,"%s:Entering",__func__);


    if(getallClkSourceConfigTable(&clkSrcCfgTableApi , &outRow, &outSize) !=CLIB_SUCCESS)
    {
       return FALSE; 
    }
    
    for( i = 1; i <=clkSrcCfgTableApi->totalNumClkSrc; i++ ){
       switch (i) {
        case 1 : /* 1 Clock Source is configured Successful*/
          if (clkSrcCfgTableApi->trunkPortId1 == TrunkPortID) {
            free(clkSrcCfgTableApi);
	          return TRUE;
          }
          break; 
        case 2 : /* 2 Clock Sources are configured Successful */
          if (clkSrcCfgTableApi->trunkPortId2 == TrunkPortID) {
            free(clkSrcCfgTableApi);
      	    return TRUE;
          }
          break; 
        case 3 : /* 3 Clock Sources are configured Sucessful */
          if (clkSrcCfgTableApi->trunkPortId3 == TrunkPortID) {
            free(clkSrcCfgTableApi);
      	    return TRUE;
          }
          break; 
        case 4 : /* 4 Clock Sources are configured Sucessful*/
          if (clkSrcCfgTableApi->trunkPortId4 == TrunkPortID) {
            free(clkSrcCfgTableApi);
      	    return TRUE;
          }
          break; 
        case 5 : /* 5 Clock Sources are configred Sucessful*/
          if (clkSrcCfgTableApi->trunkPortId5 == TrunkPortID) {
            free(clkSrcCfgTableApi);
      	    return TRUE;
          }
          break; 
        default: /* Do nothitng */
          break;
    } /* switch */
    }//for
   LOG_PRINT(LOG_INFO,"%s:Exit",__func__);
   free(clkSrcCfgTableApi);
   return FALSE;
}
/********************************* Function  Header********************************
Function Name:       sendClockSourceConfigReq()
Parameters:          void
Return type:         void
Purpose:             To Configure Clock Source  BPM.
Other Note:          Added for CS4.0 Init Part
************************************************************************************/
I_Bool sendClockSourceConfigReq()
{
   ClkSourceConfigTableApi *clkSourceConfigTableApi ;
   ClkSourceConfigTableApi newClkSourceConfigTableApi ;
   ClkSourceConfigStatusTableApi clkStsTbl;
   ClkSourceConfigStatusTableApi *outData;
   OamsCfgOilSetClkSrcReq oamsCfgOilSetClkSrcReq;
   ClkSourceConfigStatusTableIndices clkStsTblIndex;
   ClkSourceConfigTableIndices clkTblIndex;
   I_U32 priority = 0xFF;
   I_U32 outRow = 0;
   I_U16 outSize = 0;
   I_U8 i=0,clockCount = 0,flagUpdateSlotId = 0;
   I_U8 chasisFrameId, slotId;

   LOG_PRINT(LOG_INFO,"sendClockSourceConfigReq: Entering in Function");
   if( getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getActiveIccSlotId failed"); 
   }
   if(getallClkSourceConfigTable(&clkSourceConfigTableApi , &outRow, &outSize) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"sendClockSourceConfigReq: No ClockSource configured");
      return CFG_FAILURE;
   }
   memcpy(&newClkSourceConfigTableApi,clkSourceConfigTableApi,outSize);

   for( i = 1; i <=clkSourceConfigTableApi->totalNumClkSrc; i++ )
   {
       switch (i)
       {
          case 1 : /* 1 Clock Source is configured Successful*/
            {
               clkStsTbl.chasisFrameId = newClkSourceConfigTableApi.chasisFrameId;
               if( (newClkSourceConfigTableApi.slotId1 == ICCSELFCARD) ||
                   (newClkSourceConfigTableApi.slotId1 == ICCMATECARD) ) 
               {
                  if(newClkSourceConfigTableApi.slotId1 != slotId)
                  {
                     newClkSourceConfigTableApi.slotId1 = slotId;
                     flagUpdateSlotId = 1;
                  }
               }  
               clkStsTbl.slotId = newClkSourceConfigTableApi.slotId1;
               clkStsTbl.trunkPortId = newClkSourceConfigTableApi.trunkPortId1;
               clkStsTbl.clkConfigStatus = PENDING; 
               
               if(GetTrunkPortPhysicalStateFromSystemDetails(newClkSourceConfigTableApi.trunkPortId1) ==
                  PRESENT )
               {
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].frameId = newClkSourceConfigTableApi.chasisFrameId;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].slotId = newClkSourceConfigTableApi.slotId1;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].trunkPortId = newClkSourceConfigTableApi.trunkPortId1;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].priority = newClkSourceConfigTableApi.clkPriority1;
                 clockCount++;

                 priority = newClkSourceConfigTableApi.clkPriority1;
                 clkStsTbl.clkConfigStatus = APPLIED; 
                 
                 LOG_PRINT(DEBUG,"updating clkSourceSts Table as APPLIED for port(%d)",newClkSourceConfigTableApi.trunkPortId1);
               }
            }
          break; 
 
          case 2 : /* 2 Clock Sources are configured Successful */
            {
               clkStsTbl.chasisFrameId = newClkSourceConfigTableApi.chasisFrameId;
               if( (newClkSourceConfigTableApi.slotId2 == ICCSELFCARD) ||
                   (newClkSourceConfigTableApi.slotId2 == ICCMATECARD) ) 
               {
                  if(newClkSourceConfigTableApi.slotId2 != slotId)
                  {
                     newClkSourceConfigTableApi.slotId2 = slotId;
                     flagUpdateSlotId = 1;
                  }
               }  
               clkStsTbl.slotId = newClkSourceConfigTableApi.slotId2;
               clkStsTbl.trunkPortId = newClkSourceConfigTableApi.trunkPortId2;
               clkStsTbl.clkConfigStatus = PENDING; 
               
               if(GetTrunkPortPhysicalStateFromSystemDetails(newClkSourceConfigTableApi.trunkPortId2) ==
                  PRESENT )
               {
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].frameId = newClkSourceConfigTableApi.chasisFrameId;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].slotId = newClkSourceConfigTableApi.slotId2;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].trunkPortId = newClkSourceConfigTableApi.trunkPortId2;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].priority = newClkSourceConfigTableApi.clkPriority2;
                 clockCount++;
               
                 LOG_PRINT(DEBUG,"updating clkSourceSts Table as APPLIED for port(%d)",newClkSourceConfigTableApi.trunkPortId2);
                 priority = newClkSourceConfigTableApi.clkPriority2;
                 clkStsTbl.clkConfigStatus = APPLIED; 
               }
            }
          break; 
          case 3 : /* 3 Clock Sources are configured Sucessful */
            {
               clkStsTbl.chasisFrameId = newClkSourceConfigTableApi.chasisFrameId;
               if( (newClkSourceConfigTableApi.slotId3 == ICCSELFCARD) ||
                   (newClkSourceConfigTableApi.slotId3 == ICCMATECARD) ) 
               {
                  if(newClkSourceConfigTableApi.slotId3 != slotId)
                  {
                     newClkSourceConfigTableApi.slotId3 = slotId;
                     flagUpdateSlotId = 1;
                  }
               }  
               clkStsTbl.slotId = newClkSourceConfigTableApi.slotId3;
               clkStsTbl.trunkPortId = newClkSourceConfigTableApi.trunkPortId3;
               clkStsTbl.clkConfigStatus = PENDING; 
               
               if(GetTrunkPortPhysicalStateFromSystemDetails(newClkSourceConfigTableApi.trunkPortId3) ==
                  PRESENT )
               {
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].frameId = newClkSourceConfigTableApi.chasisFrameId;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].slotId = newClkSourceConfigTableApi.slotId3;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].trunkPortId = newClkSourceConfigTableApi.trunkPortId3;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].priority = newClkSourceConfigTableApi.clkPriority3;
                 clockCount++;
               
                 LOG_PRINT(DEBUG,"updating clkSourceSts Table as APPLIED for port(%d)",newClkSourceConfigTableApi.trunkPortId3);
                 priority = newClkSourceConfigTableApi.clkPriority3;
                 clkStsTbl.clkConfigStatus = APPLIED; 
               }
            }
          break; 
          case 4 : /* 4 Clock Sources are configured Sucessful*/
            {
               clkStsTbl.chasisFrameId = newClkSourceConfigTableApi.chasisFrameId;
               if( (newClkSourceConfigTableApi.slotId4 == ICCSELFCARD) ||
                   (newClkSourceConfigTableApi.slotId4 == ICCMATECARD) ) 
               {
                  if(newClkSourceConfigTableApi.slotId4 != slotId)
                  {
                     newClkSourceConfigTableApi.slotId4 = slotId;
                     flagUpdateSlotId = 1;
                  }
               }  
               clkStsTbl.slotId = newClkSourceConfigTableApi.slotId4;
               clkStsTbl.trunkPortId = newClkSourceConfigTableApi.trunkPortId4;
               clkStsTbl.clkConfigStatus = PENDING; 
               
               if(GetTrunkPortPhysicalStateFromSystemDetails(newClkSourceConfigTableApi.trunkPortId4) ==
                  PRESENT )
               {
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].frameId = newClkSourceConfigTableApi.chasisFrameId;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].slotId = newClkSourceConfigTableApi.slotId4;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].trunkPortId = newClkSourceConfigTableApi.trunkPortId4;
                 oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].priority = newClkSourceConfigTableApi.clkPriority4;
                 clockCount++;
               
                 LOG_PRINT(DEBUG,"updating clkSourceSts Table as APPLIED for port(%d)",newClkSourceConfigTableApi.trunkPortId4);
                 priority = newClkSourceConfigTableApi.clkPriority4;
                 clkStsTbl.clkConfigStatus = APPLIED; 
               }
            }
          break; 
          case 5 : /* 5 Clock Sources are configred Sucessful*/
            {
               clkStsTbl.chasisFrameId = newClkSourceConfigTableApi.chasisFrameId;
               if( (newClkSourceConfigTableApi.slotId5 == ICCSELFCARD) ||
                   (newClkSourceConfigTableApi.slotId5 == ICCMATECARD) ) 
               {
                  if(newClkSourceConfigTableApi.slotId5 != slotId)
                  {
                     newClkSourceConfigTableApi.slotId5 = slotId;
                     flagUpdateSlotId = 1;
                  }
               }  
                clkStsTbl.slotId = newClkSourceConfigTableApi.slotId5;
                clkStsTbl.trunkPortId = newClkSourceConfigTableApi.trunkPortId5;
                clkStsTbl.clkConfigStatus = PENDING; 
                
                if(GetTrunkPortPhysicalStateFromSystemDetails(newClkSourceConfigTableApi.trunkPortId5) ==
                   PRESENT )
                {
                  oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].frameId = newClkSourceConfigTableApi.chasisFrameId;
                  oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].slotId = newClkSourceConfigTableApi.slotId5;
                  oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].trunkPortId = newClkSourceConfigTableApi.trunkPortId5;
                  oamsCfgOilSetClkSrcReq.clkSrcPriority[clockCount].priority = newClkSourceConfigTableApi.clkPriority5;
                  clockCount++;
                  LOG_PRINT(DEBUG,"updating clkSourceSts Table as APPLIED for port(%d)",newClkSourceConfigTableApi.trunkPortId5);
                 priority = newClkSourceConfigTableApi.clkPriority5;
                  clkStsTbl.clkConfigStatus = APPLIED; 
                }
            }
          break; 

          default: /* Do nothitng */
            break;
      } /* switch */


      clkStsTblIndex.chasisFrameId = clkStsTbl.chasisFrameId;
      clkStsTblIndex.slotId = clkStsTbl.slotId;
      clkStsTblIndex.trunkPortId = clkStsTbl.trunkPortId;

      if(CLIB_SUCCESS != getClkSourceConfigStatusTable(&clkStsTblIndex,&outData) )
      {
          LOG_PRINT(DEBUG,"getClkSourceConfigStatusTable not success");
      } 
     
      if(gE1Data[ clkStsTbl.trunkPortId ].LOS_Active == TRUE )
      {
         LOG_PRINT(DEBUG,"Los Active for TrunkPort:%d", clkStsTbl.trunkPortId );        
         clkStsTbl.clkConfigStatus =  PENDING; 
         if(outData != NULL) 
         {
            if(outData->clkConfigStatus != PENDING)
            {
               sendClkSourcePendingAlarm(clkStsTbl.chasisFrameId,clkStsTbl.slotId,
                   clkStsTbl.trunkPortId,priority);
            }
            free(outData);
         }
      }
      else
      {
         clkStsTbl.clkConfigStatus =  APPLIED; 
         if(outData != NULL) 
         {
            if(outData->clkConfigStatus != PENDING)
            {
               sendClkSourceAppliedAlarm(clkStsTbl.chasisFrameId,clkStsTbl.slotId,
                 clkStsTbl.trunkPortId,priority);
            }
            free(outData);
         }  
      }

      if(CLIB_SUCCESS == updateClkSourceConfigStatusTable(&clkStsTbl) )
      {
        LOG_PRINT(LOG_MAJOR,"updateClkSourceConfigStatusTable succ for port%d",
          clkStsTbl.trunkPortId);
      }
      else
      {
         if(CLIB_SUCCESS == insertClkSourceConfigStatusTable(&clkStsTbl))
         {
            LOG_PRINT(LOG_MAJOR,"insertClkSourceConfigStatusTable succ for port%d",
               clkStsTbl.trunkPortId);
         }
      }
   }//for

   oamsCfgOilSetClkSrcReq.maxClkConfig = clockCount; 

   cfgSendMessage(&oamsCfgOilSetClkSrcReq, sizeof(OamsCfgOilSetClkSrcReq), ENT_OAM_OIL, OAMS_CFG_OIL_SET_CLK_SRC_REQ, 0);

   if(flagUpdateSlotId == 1)
   {
      if(updateClkSourceConfigTable(&newClkSourceConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(DEBUG,"updateClkSourceConfigTable failed");    
      }  
   } 
   free(clkSourceConfigTableApi);

   LOG_PRINT(LOG_INFO,"sendClockSourceConfigReq: Exiting from Function");
   DalocOrdBuf((I_Void *)gSystemDetails);// BSC R2.0 Changes
   gSystemDetails = NULL;
   LOG_PRINT(DEBUG,"Going To DeAloc gSystemDetails");
   return CFG_SUCCESS;
}

/********************************* Function  Header********************************
Function Name:       checkClockSourceResp()
Parameters:          void
Return type:         void
Purpose:             To Check Clock Source  Response.
Other Note:          Added for CS4.0 Init Part
************************************************************************************/
I_Bool checkClockSourceResp()
{
   OamOilCfgSetClkSrcResp *oamOilCfgSetClkSrcResp =NULL;
   I_U32 count = 0;
   LOG_PRINT(LOG_INFO,"checkClockSourceResp: Entering in Function");

   oamOilCfgSetClkSrcResp = (OamOilCfgSetClkSrcResp *)((I_U8*) gCfgMsgBuf);
   if(oamOilCfgSetClkSrcResp->result != OPERATION_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"checkClockSourceResp: Clock source configuration failed at BPM");
/*      LOG_PRINT(LOG_CRITICAL,"checkClockSourceResp: CFG is deleting Clock source configuration from DB");
      if(deleteClkSourceConfigTable(&clkSourceConfigTableIndices) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"checkClockSourceResp: Deletion Failed");
      }*/
      for(count = 0; count < oamOilCfgSetClkSrcResp->maxClkConfig; count++)
      {
            sendClkSourceConfigFailAlarm( oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].frameId , oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].slotId ,oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].trunkPortId ,oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].priority);
      }
      return CFG_FAILURE;
   }
   for(count = 0; count < oamOilCfgSetClkSrcResp->maxClkConfig ; count++)
   {
      if(oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].result !=OPERATION_SUCCESS )   
      {
         sendClkSourceConfigFailAlarm( oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].frameId , oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].slotId ,oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].trunkPortId ,oamOilCfgSetClkSrcResp->clkSrcPriorityResult[count].priority);
      }
   
   }
   LOG_PRINT(LOG_INFO,"checkClockSourceResp: Clock Source are configured.");
   LOG_PRINT(LOG_INFO,"checkClockSourceResp: Exiting from Function");
   
}

/********************************* Function  Header********************************
Function Name:       sendClkSourceConfigFailAlarm ()
Parameters:          void
Return type:         void
Purpose:             To Send alarm if Clock Source Config Failed.
Other Note:          Added for CS4.0 Init Part
************************************************************************************/
I_Void sendClkSourceConfigFailAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId , I_U32 priority)
{
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
   
   LOG_PRINT(LOG_INFO,"sendClkSourceConfigFailAlarm: Entering in Function");

   OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_CLOCK_SRC_CFG_FAILED;
   OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;

   OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  frameId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  slotId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  trunkPortId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key4       =  priority;
   OamsCfgAfhSysAlarmBuff.sysAlarm.info3       =  OAMS_OBJTYPE_TRUNKPORT;

   OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
                                          CLK_SRC_NOK_EVENT_STRING,frameId,slotId,trunkPortId);

   cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

   LOG_PRINT(LOG_INFO,"sendClkSourceConfigFailAlarm: Extiting from Function");
}

/*BSC R2.0 Changes Starts*/
#if 0
/********************************* Function  Header********************************
Function Name:       updSlotIdInClkSrcCfg ()
Parameters:          void
Return type:         void
Purpose:             Update SlolID of active card in Clk Src Cfg.
Other Note:          Added for CS4.0 Init Part
************************************************************************************/
I_Void updSlotIdInClkSrcCfg()
{
  I_U8 ActiveCardSlotID;
  I_U8 ChasisFrameID;
  I_U32 retVal  = 0;
  I_U32 outRow  = 0;
  I_U16 outSize = 0;
  I_U8  i       = 0;     
  ClkSourceConfigTableApi *clkSrcCfgTableApiDbPtr;

  LOG_PRINT(LOG_INFO,"%s:Entering",__func__);
  
  if ( ( retVal = getActiveIccSlotId( &ChasisFrameID, &ActiveCardSlotID)  ) != CLIB_SUCCESS  ) {
      LOG_PRINT(LOG_INFO,"[%s]:getActiveIccSlotId Db call failed ErrorCause: %d",__func__,retVal);
      return ;
  }


  if( ( retVal = getallClkSourceConfigTable(&clkSrcCfgTableApiDbPtr , &outRow, &outSize)) !=CLIB_SUCCESS) {
    LOG_PRINT(LOG_INFO,"[%s]:getallClkSourceConfigTable Db call failed ErrorCause: %d",__func__,retVal);
    return ; 
  }
    
  clkSrcCfgTableApiDbPtr->chasisFrameId = ChasisFrameID;

  //case fall back is used as if totalNumClkSrc is 5 then all the Clk Src SlotIDs will be changed
  switch (clkSrcCfgTableApiDbPtr->totalNumClkSrc) {
    case 5 : /* 1 Clock Source is configured Successful*/
      clkSrcCfgTableApiDbPtr->slotId5 = ActiveCardSlotID;
    case 4 : /* 2 Clock Sources are configured Successful */
      clkSrcCfgTableApiDbPtr->slotId4 = ActiveCardSlotID;
    case 3 : /* 3 Clock Sources are configured Sucessful */
      clkSrcCfgTableApiDbPtr->slotId3 = ActiveCardSlotID;
    case 2 : /* 4 Clock Sources are configured Sucessful*/
      clkSrcCfgTableApiDbPtr->slotId2 = ActiveCardSlotID;
    case 1 : /* 5 Clock Sources are configred Sucessful*/
      clkSrcCfgTableApiDbPtr->slotId1 = ActiveCardSlotID;
  }/* switch */

  if ( ( retVal = updateClkSourceConfigTable(clkSrcCfgTableApiDbPtr)) != CLIB_SUCCESS) {
    LOG_PRINT(LOG_INFO,"[%s]:updateClkSourceConfigTable Db call failed ErrorCause: %d",__func__,retVal);
  }
  
  LOG_PRINT(LOG_INFO,"%s:Exit",__func__);
  free(clkSrcCfgTableApiDbPtr);  
}
#endif

/********************************* Function  Header********************************
Function Name:       sendClkSourceAppliedAlarm ()
Parameters:          void
Return type:         void
Purpose:             To Send alarm if Clock Source has been applied.
Other Note:          Added for R2.0 development 
************************************************************************************/
I_Void sendClkSourceAppliedAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId , I_U32 priority)
{
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
   
   LOG_PRINT(LOG_INFO,"sendClkSourceAppliedAlarm : Entering in Function");

   OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_CLOCK_SRC_APPLIED;
   OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;

   OamsCfgAfhSysAlarmBuff.sysAlarm.key1       =  frameId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key2       =  slotId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key3       =  trunkPortId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key4       =  priority;

   FillObjTypeFromSlotId(slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);

   OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
                                          CLK_SRC_OK_EVENT_STRING,frameId,slotId,trunkPortId);

   cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

   LOG_PRINT(LOG_INFO,"sendClkSourceAppliedAlarm: Extiting from Function");
}

/******************************* Function  Header*****************************
Function Name : sendClkSourcePendingAlarm()
Parameters    : I_U8 frameId, I_U8 slotId, I_U16 portId
Return type   : I_S32 
Purpose       : 
Other Note    : Added For BSC R2.0
*****************************************************************************/
I_Void sendClkSourcePendingAlarm(I_U8 frameId, I_U8 slotId, I_U16 portId,I_U32 priority)
{  
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
   OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_CLOCK_SRC_PENDING;
   OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_WARNING;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = frameId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key2 = slotId; 
   OamsCfgAfhSysAlarmBuff.sysAlarm.key3 = portId;
   OamsCfgAfhSysAlarmBuff.sysAlarm.key4 = priority;
   
   FillObjTypeFromSlotId(slotId,OamsCfgAfhSysAlarmBuff.sysAlarm.info3);
                         
   OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen =
               sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,
                         "ClkSrcConfigPending ChasisId[%d],SlotId[%d],portId[%d]",
                           frameId,slotId, portId);
     
   cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
}
/*BSC R2.0 Changes Ends*/
