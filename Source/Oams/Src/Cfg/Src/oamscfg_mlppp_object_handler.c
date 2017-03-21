/***********************************File Header ********************************
File Name        : oamscfg_mlppp_object_handler.c
Purpose          : This file contains functions definition required for the 
handling of MLPPP object 
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Team
CSCI ID          :
Version          :
 ************************************* End *************************************/

#include <oamscfg_includes.h>

/********************************* Function  Header*****************************
   Function Name   : addMlpppConfigTableHandler()
Parameters   : None
Return type   : I_Void
Purpose      : Handler add MLPPP request from OMC/CLI
Other Note   : Added For BSC CS4.0 HA Feature
 *******************************************************************************/
I_Void addMlpppConfigTableHandler()
{
   MlpppConfigTableApi * receivedMsgPtr = (MlpppConfigTableApi*)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
   MlpppConfigTableApi  tbMsgPtr ;
   memcpy(&tbMsgPtr,receivedMsgPtr,sizeof(MlpppConfigTableApi));
   OamsCfgOilMlpppConfigReq oamsCfgOilMlpppConfigReq;
   I_Bool storeStatus;
   I_U8 chasisFrameId;
   I_U8 slotId;

   LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Entering in Function");
   LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Doing Validation Checks");
   if(validateMlpppConfigReq() == CFG_FAILURE)
   {
      LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Can Not add MlpppConfig");
      LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Exiting from Function");
      return;
   }
   if(receivedMsgPtr->mlppLinkStatus != MLPPP_LINK_DISABLED)
   {
      LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Link status is not disabled");
      cfgSendNackToCm(CM_ERR_MLPPP_LINKUP_NOT_ALLOWED);
      return ;
   }

   //storeStatus = storeReceivedMsgBuffer(receivedMsgPtr, sizeof(MlpppConfigTableApi));

   gMlpppStoredMsgBufPtr = AlocOrdBuf(sizeof(MlpppConfigTableApi));
   if(gMlpppStoredMsgBufPtr != NULL)
   {
      memcpy(gMlpppStoredMsgBufPtr,receivedMsgPtr,sizeof(MlpppConfigTableApi));
   }

   /*Everything is fine. Sending request to BPM*/
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Db Call failed. No Active card is there");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return ;
   }

   oamsCfgOilMlpppConfigReq.frameID = chasisFrameId;
	oamsCfgOilMlpppConfigReq.slotID = slotId;
	oamsCfgOilMlpppConfigReq.forcedConfiguration = NORMALCONFIG;
	oamsCfgOilMlpppConfigReq.numChannel = receivedMsgPtr->numChannel;
   memcpy(oamsCfgOilMlpppConfigReq.nodeIp, receivedMsgPtr->nodeIpAddr , MAX_IP_ADDR_LEN) ;
   memcpy(oamsCfgOilMlpppConfigReq.omcIp, receivedMsgPtr->omcIpAddr , MAX_IP_ADDR_LEN) ;    

   if(allocateChannel(receivedMsgPtr, slotId, &oamsCfgOilMlpppConfigReq) == CFG_FAILURE)
   {
      return;
   }

   cfgSendMessage(&oamsCfgOilMlpppConfigReq, sizeof(OamsCfgOilMlpppConfigReq), ENT_OAM_OIL, OAMS_CFG_OIL_MLPPP_CONFIG_REQ, 0);
   /*sending same message to TB_BSC    */
   cfgSendMessage(&tbMsgPtr, sizeof(MlpppConfigTableApi), ENT_PSAPP_TBBSC, OAMS_CFG_TBBSC_ADD_MLPPP_CONFIG, 0);

   LOG_PRINT(LOG_INFO,"addMlpppConfigTableHandler: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : allocateChannel()
Parameters   : OamsCfgOilMlpppConfigReq *oamsCfgOilMlpppConfigReq
Return type   : I_S32
Purpose      : Allocate Free channels for the request
Other Note   : Added For BSC CS4.0 HA Feature
 *******************************************************************************/

I_S32 allocateChannel(MlpppConfigTableApi *receivedMsgPtr, I_U8 slotId, OamsCfgOilMlpppConfigReq *oamsCfgOilMlpppConfigReq )
{
   MccLinkResourceTableApi *mccLinkResourceRow = NULL;
   MccLinkResourceTableApi *tmpRow = NULL;
   I_U32 outCount;
   I_U16 outSize;
   I_U32 count;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;
   I_U16 portId;
   I_U8 timeSlot;
   E1StreamMapTableIndices strmIndices;
   E1StreamMapTableApi *e1StreamRow = NULL;

   LOG_PRINT(LOG_INFO,"allocateChannel: Entering in Function");
   if(getTrunkNumTsMccLinkTable( SYS_TS_USAGE_MLPPP, SYS_TS_FREE, slotId, &mccLinkResourceRow,&outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"allocateChannel: DB Operation FAILED. No Row Found in MccLinkResource Table");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
   
   incrSize   = offsetof(MlpppConfigTableApi, trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   
   basePtr    = (I_U8 *)receivedMsgPtr + portBaseOffset;


   for(count = 0 ; count < receivedMsgPtr->numChannel ; count++)
   {
      tmpRow = (MccLinkResourceTableApi *)((I_U8 *) mccLinkResourceRow + (count*outSize));
      portId = (*(I_U16 *) (basePtr + count*incrSize ));
      timeSlot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;
      LOG_PRINT(LOG_INFO,"allocateChannel: Allocating Channel for PortId [%d], TimeSlot [%d]", portId,timeSlot);

      if(updateMccLinkResource (tmpRow, portId ,timeSlot, SYS_TS_ALLOCATED) == CFG_FAILURE)
      {
         free(mccLinkResourceRow);
         return CFG_FAILURE;
      }
      
      strmIndices.e1Num = tmpRow->mccTrunkNum;
      strmIndices.e1Ts = tmpRow->mccTrunkTs;

      if(getE1StreamMapTable( &strmIndices, &e1StreamRow) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"allocateChannel: get operation on E1StreamMapTable Failed");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         free(mccLinkResourceRow);
         return CFG_FAILURE;
      }
      
      oamsCfgOilMlpppConfigReq->mlpppChannel[count] = e1StreamRow->strmTs;
      free(e1StreamRow);
   }
   free(mccLinkResourceRow);

   LOG_PRINT(LOG_INFO,"allocateChannel: Exiting from Function");
   return CFG_SUCCESS; 
}

/********************************* Function  Header*****************************
Function Name   : updateMccLinkResource()
Parameters   : MccLinkResourceTableApi *mccRow I_U32 extE1 , I_U32 extTs
Return type   : I_Void
Purpose      : update MccLinkReqource Table
Other Note   : Added For BSC CS4.0 HA Feature
 *******************************************************************************/

I_S32 updateMccLinkResource(MccLinkResourceTableApi *mccRow, I_U32 extE1, I_U32 extTs , I_U32 linkStatus)
{
   
   MccLinkResourceTableApi updateRow ;
   LOG_PRINT(LOG_INFO,"updateMccLinkResource: Entering in Function");
   updateRow.mccTrunkNum = mccRow->mccTrunkNum;
   updateRow.mccTrunkTs = mccRow->mccTrunkTs;
   updateRow.cardNum = ICCSELFCARD;
   updateRow.mccLinkType = mccRow->mccLinkType;
   updateRow.extTrunkNum = extE1;
   updateRow.extTrunkTs = extTs;
   updateRow.mccLinkStatus = linkStatus;
   if(updateMccLinkResourceTable (&updateRow) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateMccLinkResource: Update Operation FAILED on MccLinkResource Table");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
   updateRow.cardNum = ICCMATECARD;
   if(updateMccLinkResourceTable (&updateRow) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateMccLinkResource: Update Operation FAILED on MccLinkResource Table");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }


   LOG_PRINT(LOG_INFO,"updateMccLinkResource: Exiting from Function");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : validateMlpppConfigReq()
Parameters   : None
Return type   : I_S32
Purpose      : Validate add MLPPP request from OMC/CLI
Other Note   : Added For BSC CS4.0 HA Feature
 *******************************************************************************/
I_S32 validateMlpppConfigReq()
{
   MlpppConfigTableApi * receivedMsgPtr = (MlpppConfigTableApi*)(((I_U8 *)gCfgMsgBuf)+ sizeof (sCmMsg));
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_U32 count;
   I_U32 outCount;
   I_U16 outSize;
   MccLinkResourceTableApi *mccLinkResourceTablePtr = NULL;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;
   I_U16 portId;
   I_U8 timeSlot;
   I_U32 incrSize;
   I_U32 *nodeIp[4];
   I_U32 *omcIp[4];
   I_S32 res =0;
   SetOmcIpAddressTableApi *setOmcIpAddressTableApiPtr = NULL;
   SetNeIpAddressTableApi  *setNeIpAddressTableApiPtr = NULL;

   LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Entering in Function to validate request");
   if(receivedMsgPtr->numChannel > NUMOFCHANNEL || receivedMsgPtr->numChannel < 1)
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validation Check failed. NumChannel Out of Range");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return CFG_FAILURE;
   }
   
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Db Call failed. No Active card is there");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }

   if(getMccLinkRowsOfLinkType(SYS_TS_USAGE_MLPPP, slotId, &mccLinkResourceTablePtr, &outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Db Call failed. No Row in MccLinkResource Table of MLPPP Type ");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
   
   if(outCount < receivedMsgPtr->numChannel)
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validation Check failed. Sufficient channels are not available.");
      cfgSendNackToCm(CM_ERR_MLPPP_RESOURCE_NOT_AVAILABLE);
      free(mccLinkResourceTablePtr);
      return CFG_FAILURE;
   }

   /*Fixed Issue 8558*/
   
   res = strcmp(receivedMsgPtr->omcIpAddr,receivedMsgPtr->nodeIpAddr);
   if(0 == res) 
   {
      LOG_PRINT(DEBUG,"Received OmcIp and NodeIp are same which is invalid case");
      cfgSendNackToCm(CM_ERR_OMCIP_AND_NODEIP_ARE_SAME);
      free(mccLinkResourceTablePtr);
      return CFG_FAILURE;
   }
   
   /*Fix Of Mantis-0011829 Starts*/
   if(getallSetOmcIpAddressTable(&setOmcIpAddressTableApiPtr, &outCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"sendSetOmcipAddressReqToCmInActive: Get All failed on SetOmcIpAddressTable ");
   }
   else
   {   
      res = strcmp(setOmcIpAddressTableApiPtr->omcIpAddr,receivedMsgPtr->omcIpAddr);
      if(0 == res) 
      {
         LOG_PRINT(DEBUG,"Received Local OmcIp and Mlppp OmcIp are same which is invalid case");
         cfgSendNackToCm(CM_ERR_LOCAL_AND_REMOTE_OMCIP_ARE_SAME);
         free(mccLinkResourceTablePtr);
         return CFG_FAILURE;
      }
      free(setOmcIpAddressTableApiPtr);
   }
   /*Fix Of Mantis-0011829 Ends*/
   
   /*Fix Of Mantis-0013192 Starts*/
   if(getallSetNeIpAddressTable(&setNeIpAddressTableApiPtr, &outCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"sendSetOmcipAddressReqToCmInActive: Get All failed on SetNeIpAddressTable");
   }
   else
   {   
      res = strcmp(setNeIpAddressTableApiPtr->nodeIpAddr,receivedMsgPtr->nodeIpAddr);
      if(0 == res) 
      {
         LOG_PRINT(DEBUG,"Received Local NodeIp and Mlppp NodeIp are same which is invalid case");
         cfgSendNackToCm(CM_ERR_NODEIP_ALREADY_CONFIGURED);
         free(mccLinkResourceTablePtr);
         return CFG_FAILURE;
      }
      free(setOmcIpAddressTableApiPtr);
   }
   /*Fix Of Mantis-0013192 Ends*/

   /*Check whether ip are of same subnet*/
   LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: IP Subnet checking");
   memset(nodeIp,4,0);
   memset(omcIp,4,0);
   
   if(receivedMsgPtr->nodeIpAddr !=NULL)
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Before Converting [%s]",receivedMsgPtr->nodeIpAddr );
      convertIpToToken(receivedMsgPtr->nodeIpAddr, nodeIp); 
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: After Converting [%s]",receivedMsgPtr->nodeIpAddr );
   } 

   if(receivedMsgPtr->omcIpAddr !=NULL)
   {
      convertIpToToken(receivedMsgPtr->omcIpAddr, omcIp); 
   } 

   if(nodeIp[0] != omcIp[0])
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validation Check failed. IP are of diffrent subnet");
      cfgSendNackToCm(CM_ERR_IP_NOT_OF_SAME_SUBNET);
      free(mccLinkResourceTablePtr);
      return CFG_FAILURE;
   }
   if(nodeIp[1] != omcIp[1])
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validation Check failed. IP are of diffrent subnet");
      cfgSendNackToCm(CM_ERR_IP_NOT_OF_SAME_SUBNET);
      free(mccLinkResourceTablePtr);
      return CFG_FAILURE;
   }
   if(nodeIp[2] != omcIp[2])
   {
      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validation Check failed. IP are of diffrent subnet");
      cfgSendNackToCm(CM_ERR_IP_NOT_OF_SAME_SUBNET);
      free(mccLinkResourceTablePtr);
      return CFG_FAILURE;
   }

   free(mccLinkResourceTablePtr);
   incrSize   = offsetof(MlpppConfigTableApi, trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   basePtr    = (I_U8 *) receivedMsgPtr + portBaseOffset;
   for(count = 0 ; count < receivedMsgPtr->numChannel ; count++)
   {
      portId = (*(I_U16 *) (basePtr + count*incrSize ));
      timeSlot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;

      LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validating PortId [%d], timeSlot [%d]", portId,timeSlot);
      if(validateTrunkPortAndTs(portId, timeSlot) == CFG_FAILURE)
      {
         LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Validation failed for PortId [%d], timeSlot [%d]", portId,timeSlot);
         LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Exiting from Function");
         return CFG_FAILURE;
      }
   }
   LOG_PRINT(LOG_INFO,"validateMlpppConfigReq: Exiting from Function");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : validateTrunkPortAmdTs()
Parameters   : None
Return type   : I_S32
Purpose      : Validate Trunk Port Time Slots from OMC/CLI
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_S32 validateTrunkPortAndTs(I_U16 portId, I_U8 timeSlot)
{
   LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: Entering from Function");
   LinkTableApi *linkTablePtr = NULL;
   CicTableApi *cicTablePtr = NULL;

/* Changes PCU R2.5 Aricent --START*/
   I_U32 i = 0;
   I_U32 rowCount = 0;
   I_U16 rowSize = 0;
   FrLinkTableApi *frLinkTablePtr = NULL;
   FrLinkTableApi *frLinkTableAllPtr = NULL;
   I_S32 ret = CLIB_SUCCESS;
   I_U32 tsMap=0;
/* Changes PCU R2.5 Aricent --END*/
   /*Validating Trunk Port*/ 
   /* changes For E1-T1 */
   if(((gBscTrunkType == BPM_TRUNK_TYPE_E1) && (timeSlot > 31)) || 
      ((gBscTrunkType == BPM_TRUNK_TYPE_T1) && (timeSlot > 23)) )
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TimeSlot Invalid ");
      cfgSendNackToCm( CM_ERR_INVALID_TIMESLOT);
      return CFG_FAILURE;
   }
   if(portId > 39)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TrunPort Invalid ");
      cfgSendNackToCm( CM_ERR_INVALID_TRUNKPORT);
      return CFG_FAILURE;
   }


   if(gE1Data[portId].trunkState == EnableInProgress)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TrunkPort is in Enable in Progress ");
      cfgSendNackToCm( CM_ERR_TRUNKPORT_ENABLE_IN_PROGRESS);
      return CFG_FAILURE;
   }

   if(gE1Data[portId].trunkState == Disabled)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TrunkPort is in Disbaled ");
      cfgSendNackToCm( CM_ERR_TRUNKPORT_DISABLED);

      return CFG_FAILURE;
   }
   
   if(gE1Data[portId].trunkState == DisableInProgress)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TrunkPort is in Disable in Progress ");
      cfgSendNackToCm( CM_ERR_TRUNKPORT_DISABLE_IN_PROGRESS);
      return CFG_FAILURE;
   }
   
   if(gE1Data[portId].usageType != SYS_E1_USAGE_AIF)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TrunkPort is not configured for A-Interface ");
      cfgSendNackToCm(CM_ERR_E1_USAGE_TYPE_NOT_AIF);
      return CFG_FAILURE;
   }
   
   /*Validating Time Slot*/ 
   
   if(getLinkTableUsingE1Ts( portId, timeSlot, &linkTablePtr) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TimeSlot is configured for MTP2 Link ");
      cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_LINK);
      free(linkTablePtr);
      return CFG_FAILURE;
      
   }
   
   if(getCicTableUsingE1Ts(portId, timeSlot, &cicTablePtr ) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TimeSlot is configured for CIC ");
      cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_CIC);
      free(cicTablePtr);
      return CFG_FAILURE;
   }

/* Changes PCU R2.5 Aricent --START*/
   ret =  getallFrLinkTable(&frLinkTableAllPtr, &rowCount, &rowSize);
   if ( CLIB_SUCCESS == ret)
   {
      for ( i = 0; i < rowCount; i++ )
      {
         frLinkTablePtr = (FrLinkTableApi*)((I_U8 *)frLinkTableAllPtr + ( i *rowSize));
         if ( (frLinkTablePtr->e1Id == portId) && 
              (timeSlot >= frLinkTablePtr->startTs && timeSlot <= (frLinkTablePtr->startTs + frLinkTablePtr->numTs -1) )
            )
         {
            LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: TimeSlot is configured for FR ");
            cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_FR);
            free(frLinkTableAllPtr);
            return CFG_FAILURE;
         }
      }
   }

/* Changes PCU R2.5 Aricent --END*/

/*Changes for TsGroup Start*/
      tsMap=1<<timeSlot;
      if(AreTimeSlotsNotUsedForTsGroup(portId,tsMap) != CFG_SUCCESS)
      {
        LOG_PRINT(LOG_DEBUG,"validateTrunkPortAndTs: E1Id[%u] & TimeSlot[%u] is allocated for TsGroup, sending Nack",
            portId,timeSlot);
        cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_TSGROUP);
        return ;

      }
 /*Changes for TsGroup End*/

   
   
   LOG_PRINT(LOG_INFO,"validateTrunkPortAndTs: Exiting from Function");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : mlpppConfigRespHAndler()
Parameters   : None
Return type   : I_S32
Purpose      : Handles the response received from BPM
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void mlpppConfigRespHandler()
{
   MlpppConfigTableApi *mlpppConfigTableApiPtr = NULL;
   I_U32 outCount;
   I_U16 outSize;
   OamOilCfgMlpppConfigResp *oamOilCfgMlpppConfigResp  = (OamOilCfgMlpppConfigResp*)(gCfgMsgBuf);
   LOG_PRINT(LOG_INFO,"mlpppConfigRespHandler: Entering in Function");
   
   if(gMlpppStoredMsgBufPtr == NULL)
   {
      if(oamOilCfgMlpppConfigResp->result != OPERATION_SUCCESS) 
      {
         LOG_PRINT(LOG_INFO,"mlpppConfigRespHandler: Response from BPM came with Error [%d] ", oamOilCfgMlpppConfigResp->result);
         if(gCurrentConnectivityMode == NO_MODE)
         {
            sendConfigFailAlarmToAfh(oamOilCfgMlpppConfigResp->result);
            sendSetOmcipAddressReqToCmInActive();
         }
      }
      else
      {
         sendSwitchConnect(oamOilCfgMlpppConfigResp->slotID);
         
      }
      /*request was sent for retry */
   }
   else
   {
      /*Request was sent first time*/
      if(getallMlpppConfigTable(&mlpppConfigTableApiPtr, &outCount, &outSize) != CLIB_SUCCESS)
      {
         /*Request was sent to Add MlpppConfig*/
         LOG_PRINT(LOG_INFO,"mlpppConfigRespHandler: Adding Mlppp Configuration ");
         addMlpppConfigRespHandler();
         
      }
      else
      {
         /*Request was sent to Modify MlpppConfig*/
         LOG_PRINT(LOG_INFO,"mlpppConfigRespHandler: Modifying Mlppp Configuration ");
         modifyMlpppConfigRespHandler();
      }
   }
   if(mlpppConfigTableApiPtr != NULL)
   {
      free(mlpppConfigTableApiPtr);
   }
   LOG_PRINT(LOG_INFO,"mlpppConfigRespHandler: Exiting from Function");
   
}

/********************************* Function  Header*****************************
Function Name   : sendConfigFailAlarmToAfh()
Parameters   : None
Return type   : I_VOid
Purpose      : Handles the response received from BPM
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void sendConfigFailAlarmToAfh(I_U16 errCode)
{
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff ; 
   LOG_PRINT(LOG_INFO,"sendConfigFailAlarmToAfh: Entering from Function");
   memset(&OamsCfgAfhSysAlarmBuff, 0 , sizeof(OamsCfgAfhSysAlarm)); 
   OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = EVENT_MLPPP_CONFIG_FAILED;
   OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSSNODE;
   switch(errCode)
   {
      case ERR_MLPPP_INVAL_LOCAL_IP:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_INVAL_LOCAL_IP ");
         break;
      case ERR_MLPPP_INVAL_PEER_IP:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_INVAL_PEER_IP ");
         break;
      case ERR_MLPPP_NUM_CHAN_ZERO:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_NUM_CHAN_ZERO ");
         break;
      case ERR_MLPPP_NUM_CHAN_EXCD_MAX:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_NUM_CHAN_EXCD_MAX ");
         break;
      case ERR_MLPPP_OPEN_READUSER:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_OPEN_READUSER ");
         break;
      case ERR_MLPPP_OPEN_READUSERIP:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_OPEN_READUSERIP ");
         break;
      case ERR_MLPPP_WRITE_READUSER:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_WRITE_READUSER ");
         break;
      case ERR_MLPPP_WRITE_READUSERIP:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_WRITE_READUSERIP ");
         break;
      case ERR_MLPPP_ALREADY_CONFIGURED:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_ALREADY_CONFIGURED ");
         break;
      case ERR_MLPPP_DECONFIGURATION_FAILED:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code ERR_MLPPP_DECONFIGURATION_FAILED ");
         break;
      default:
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"MLPPP Config failed with error Code [%d] ", errCode);
         break;
   }
   cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   LOG_PRINT(LOG_INFO,"sendConfigFailAlarmToAfh: Exiting from Function");

}
/********************************* Function  Header*****************************
Function Name   : addMlpppConfigRespHandler()
Parameters   : None
Return type   : I_S32
Purpose      : Handles the response received from BPM for addition
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_Void addMlpppConfigRespHandler()
{
   OamOilCfgMlpppConfigResp *oamOilCfgMlpppConfigResp  = (OamOilCfgMlpppConfigResp*)(gCfgMsgBuf);
   LOG_PRINT(LOG_INFO,"addMlpppConfigRespHandler: Entering in  Function");
   if(oamOilCfgMlpppConfigResp->result == OPERATION_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addMlpppConfigRespHandler: BPM Sends Mlppp Config Success"); 
      sendSwitchConnect(oamOilCfgMlpppConfigResp->slotID);
      if(updateMlpppConfigInDb() == CFG_FAILURE)
      {
         return;
      }
      /* Insert all MlpppChannelStatus in db for all channels with status disabled*/
      insertMlpppChannelStatusforAllRows();
      cfgSendAckToCm();
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addMlpppConfigRespHandler: BPM Sends Mlppp Config Failure response with Error [%d]" , oamOilCfgMlpppConfigResp->result);
      freeMccLinkResource(oamOilCfgMlpppConfigResp->slotID); 
      cfgSendNackToCm(CM_ERR_BPM_OPERATION_FAILS);
   }
   //freegStoreMsgBuff();
   if (gMlpppStoredMsgBufPtr !=NULL)
   {
      DalocOrdBuf(gMlpppStoredMsgBufPtr);
      gMlpppStoredMsgBufPtr = NULL;
   }
   LOG_PRINT(LOG_INFO,"addMlpppConfigRespHandler: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : populateChannelStatus()
Parameters   : I_U32 slotIdI_U32 channel, I_U32 channelStatus, I_U8 *timeslot
Return type   : I_Void
Purpose      : Populate Channel Status Table
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void  populateChannelStatus(I_U32 slotId, I_U32 channel, I_U32 channelStatus, I_U8 *timeslot )
{
   I_U32 e1Num;
   I_U32 e1Ts;
   I_U32 outCount;
   I_U16 outSize;
   MccLinkResourceTableIndices mccLinkResourceIndices;
   MccLinkResourceTableApi *mccLinkRow = NULL;
   MlpppChannelStatusTableApi channelStatusTableRow;
   MlpppConfigTableApi *mlpppConfigTablePtr = NULL;

   LOG_PRINT(LOG_INFO,"populateChannelStatus: Entering in Function");
   if(getE1TsFromE1StreamMap(STREAM_NUM, channel, &e1Num, &e1Ts)!= CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"populateChannelStatus: No Entry found in E1 StreamMap Table for Channel [%d]", channel);
      return;
   }
   mccLinkResourceIndices.mccTrunkNum = e1Num;
   mccLinkResourceIndices.mccTrunkTs = e1Ts;
   mccLinkResourceIndices.cardNum = slotId;
   
   if(getMccLinkResourceTable(&mccLinkResourceIndices , &mccLinkRow) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"populateChannelStatus: No Entry found in MccLinkResourceTable for mccTrunkNum [%d], mccTrunkTs [%d]", e1Num, e1Ts);
      return;
   }
   if(gStoredMsgBufPtr != NULL)
   {
      channelStatusTableRow.mlpppLinkId = ((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->mlpppLinkId;
   }
   else
   {
      if(getallMlpppConfigTable(&mlpppConfigTablePtr, &outCount, &outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"populateChannelStatus: No Entry found in MlpppConfig Table");
         free(mccLinkRow);
         return;
      }
      channelStatusTableRow.mlpppLinkId = mlpppConfigTablePtr->mlpppLinkId;
      
   }
   
   channelStatusTableRow.trunkportId = mccLinkRow->extTrunkNum;
   channelStatusTableRow.timeslot = mccLinkRow->extTrunkTs;
   channelStatusTableRow.channelStatus = channelStatus;
   if(updateMlpppChannelStatusTable(&channelStatusTableRow) != CLIB_SUCCESS) 
   {
      if(insertMlpppChannelStatusTable(&channelStatusTableRow) != CLIB_SUCCESS) 
      {
         LOG_PRINT(LOG_CRITICAL,"populateChannelStatus: Insertion in Channel Status Table failed");
         free(mccLinkRow);
         free(mlpppConfigTablePtr);
         return;
      }
   }
   *timeslot = channelStatusTableRow.timeslot;
   free(mccLinkRow);
   free(mlpppConfigTablePtr);
   
   LOG_PRINT(LOG_INFO,"populateChannelStatus: Exiting from Function");
   return ;
   
}

/********************************* Function  Header*****************************
Function Name   : freeLinkResource()
Parameters   : None
Return type   : I_Void
Purpose      : Mark LinkResource as  Free in DB
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_Void freeMccLinkResource(I_U8 slotId)
{
   I_U32 outCount;
   I_U16 outSize;
   I_U32 count;
   MccLinkResourceTableApi *mccLinkResourceRow = NULL;
   MccLinkResourceTableApi *tmpRow = NULL;
   LOG_PRINT(LOG_INFO,"addfreeMccLinkResource: Entering in Function");
      
   if(getTrunkNumTsMccLinkTable( SYS_TS_USAGE_MLPPP, SYS_TS_ALLOCATED, slotId, &mccLinkResourceRow, &outCount, &outSize)!= CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addfreeMccLinkResource: No Row Allocated in MccLinkResource Table");
      return;
   }
   
   for(count = 0 ; count < outCount ; count++)
   {
      tmpRow = (MccLinkResourceTableApi*)((I_U8 *)mccLinkResourceRow + outSize * count);
      updateMccLinkResource (tmpRow, INVALID_E1 , INVALID_TS, SYS_TS_FREE);
   }
   free(mccLinkResourceRow);
   LOG_PRINT(LOG_INFO,"addfreeMccLinkResource: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : updateMlpppConfigInDb()
Parameters   : None
Return type   : I_S32
Purpose      : Update MlpppConfig Table
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_S32 updateMlpppConfigInDb()
{
   MlpppConfigTableApi mlpppConfigTableApiRow;
   LOG_PRINT(LOG_INFO,"updateMlpppConfigInDb: Entering in Function");
   
    
   memcpy(&mlpppConfigTableApiRow, (MlpppConfigTableApi*)gMlpppStoredMsgBufPtr , sizeof(MlpppConfigTableApi));
   
   mlpppConfigTableApiRow.mlppLinkStatus = gMlpppLinkStatus;
   if(updateMlpppConfigTable(&mlpppConfigTableApiRow) != CLIB_SUCCESS)
   {
      if(insertMlpppConfigTable(&mlpppConfigTableApiRow) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"updateMlpppConfigInDb: Insertion in MlpppConfgiTable failed");
         return CFG_FAILURE;
      }
   }
   
   LOG_PRINT(LOG_INFO,"updateMlpppConfigInDb: Exiting from Function");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : sendSwitchConnect()
Parameters   : I_U8 slotId
Return type   : I_Void
Purpose      : Sending Switch Connect to GRHM
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void sendSwitchConnect(I_U8 slotId)
{
   MccLinkResourceTableApi *mccLinkResourceRow = NULL;
   MccLinkResourceTableApi *tmpRow = NULL;
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
   I_U32 outCount ;
   I_U16 outSize;
   I_U32 count;
   LOG_PRINT(LOG_INFO,"sendSwitchConnect: Entering in Function");
   if(getTrunkNumTsMccLinkTable( SYS_TS_USAGE_MLPPP, SYS_TS_ALLOCATED, slotId, &mccLinkResourceRow, &outCount, &outSize)!= CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"sendSwitchConnect: No Row Allocated in MccLinkResource Table");
      return;
   }   
   
   for(count = 0 ; count < outCount ; count++)
   {
      tmpRow = (MccLinkResourceTableApi *)((I_U8 *) mccLinkResourceRow + count*outSize);
      oamsCfgGrhmSwitchConnect.firstE1Num = tmpRow->extTrunkNum;
      oamsCfgGrhmSwitchConnect.firstTimeSlotNum = tmpRow->extTrunkTs;
      oamsCfgGrhmSwitchConnect.secondE1Num = tmpRow->mccTrunkNum;
      oamsCfgGrhmSwitchConnect.secondTimeSlotNum = tmpRow->mccTrunkTs;
      cfgSendMessage(&oamsCfgGrhmSwitchConnect,sizeof(OamsCfgGrhmSwitchConnect), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0); 
   }
   free(mccLinkResourceRow);
   LOG_PRINT(LOG_INFO,"sendSwitchConnect: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : modifyMlpppConfigRespHandler()
Parameters   : None
Return type   : I_Void
Purpose      : This function handles the response of modification request.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void modifyMlpppConfigRespHandler()
{
   OamOilCfgMlpppConfigResp *oamOilCfgMlpppConfigResp  = (OamOilCfgMlpppConfigResp*)(gCfgMsgBuf);

   if(oamOilCfgMlpppConfigResp->result == OPERATION_SUCCESS)
   {
      /* Update MlpppConfigTable row in Db with value stored in gBuffer*/
      if(updateMlpppConfigInDb() == CFG_FAILURE)
      {
         LOG_PRINT(LOG_MAJOR,"Db updation failed for MlpppConfigTable");
         sendConfigFailAlarmToAfh(CM_ERR_UPDATE_DB_OPER_FAILED);
//         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         free(gMccLinkResourcePtr);
         //freegStoreMsgBuff();
         if (gMlpppStoredMsgBufPtr !=NULL)
         {
            DalocOrdBuf(gMlpppStoredMsgBufPtr);
            gMlpppStoredMsgBufPtr = NULL;
         }
         return;
      }
      /* Send Switch disconnect towards GRHM for old configured channels */ 
      if(disconTsForMlppp() == CFG_FAILURE)
      {
         LOG_PRINT(LOG_MAJOR,"disconTsForMlppp functionality failed");
         return;
      }

      /* Reset all Mlppp based rows in MccLinkResourceTable */ 
      resetAllMlppMccTrunkTsRows();

      /* Update rows of MccLinkResourceTable with the values of gMccLinkResourcePtr */ 
      updateMccLinkResforAllrows(gMccLinkResourcePtr, gMccOutCount, gMccOutSize);

      /* Send Switch connect for all the new Mlppp based rows in MccLinkResourceTable. */ 
      sendSwitchConnect(oamOilCfgMlpppConfigResp->slotID);

      free(gMccLinkResourcePtr);
      //freegStoreMsgBuff();
      if (gMlpppStoredMsgBufPtr !=NULL)
      {
         DalocOrdBuf(gMlpppStoredMsgBufPtr);
         gMlpppStoredMsgBufPtr = NULL;
      }

      /* Insert all MlpppChannelStatus in db for all channels with status disabled*/
      insertMlpppChannelStatusforAllRows();

      /* Delete all invalid rows MlpppConfigStatusTable */ 
      if(delAllInvalidMlpppStatusRows() == CFG_FAILURE)
      {
         LOG_PRINT(LOG_MAJOR,"delAllInvalidMlpppStatusRows() operation failed");
         sendConfigFailAlarmToAfh(CM_ERR_DELETE_DB_OPER_FAILED);
//         cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
         free(gMccLinkResourcePtr);
         //freegStoreMsgBuff();
         if (gMlpppStoredMsgBufPtr !=NULL)
         {
            DalocOrdBuf(gMlpppStoredMsgBufPtr);
            gMlpppStoredMsgBufPtr = NULL;
         }
         return;
      }
   
//      cfgSendAckToCm();
   }
   else /* ERROR/NACK is received in response from BPM*/
   {
      free(gMccLinkResourcePtr);
      //freegStoreMsgBuff();
      if (gMlpppStoredMsgBufPtr !=NULL)
      {
         DalocOrdBuf(gMlpppStoredMsgBufPtr);
         gMlpppStoredMsgBufPtr = NULL;
      }
      sendConfigFailAlarmToAfh(CM_ERR_BPM_OPERATION_FAILS);
//      cfgSendNackToCm(CM_ERR_BPM_OPERATION_FAILS);
   }
}

/********************************* Function  Header*****************************
Function Name   : mlpppConnectHandler()
Parameters   : None
Return type   : I_Void
Purpose      : This function handles the Connect alarm.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void mlpppConnectHandler()
{
   OamsCfgCmSetIpAddress oamsCfgCmSetIpAddress;
   MlpppConfigTableApi *mlpppConfigRow = NULL;
   SetOmcIpAddressTableApi *setOmcIpAddressTableApiPtr = NULL;
   I_U32 outCount;
   I_U16 outSize;
   OamsCfgAfhConModeIndi oamsCfgAfhConModeIndi;
   LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Entering from Function");
   gMlpppLinkStatus = MLPPP_LINK_ENABLED;
   if(updateMlpppLinkStatus(MLPPP_LINK_ENABLED) != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Db Operation on MlpppConfigTable failed");
   }
   LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Link Status set as ENABLED");
   LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Sending OmcIp Config to CM");

   if(gStoredMsgBufPtr != NULL)
   {
      LOG_PRINT(LOG_INFO,"mlpppConnectHandler: OMC_IP [%s]" , ((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->omcIpAddr);
      LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Node_IP [%s]" ,((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->nodeIpAddr);
      memcpy(oamsCfgCmSetIpAddress.neipAddress, ((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->nodeIpAddr , MAX_IP_ADDR_LEN);
      memcpy(oamsCfgCmSetIpAddress.omcipAddress, ((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->omcIpAddr, MAX_IP_ADDR_LEN);
      
   }
   else
   {
      if(getallMlpppConfigTable(&mlpppConfigRow, &outCount, &outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"mlpppConnectHandler: No Row in MlpppConfig Table");
         return;
      }
   
      LOG_PRINT(LOG_INFO,"mlpppConnectHandler: OMC_IP [%s]" , mlpppConfigRow->omcIpAddr);
      LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Node_IP [%s]" , mlpppConfigRow->nodeIpAddr);
      memcpy(oamsCfgCmSetIpAddress.neipAddress, mlpppConfigRow->nodeIpAddr , MAX_IP_ADDR_LEN);
      memcpy(oamsCfgCmSetIpAddress.omcipAddress, mlpppConfigRow->omcIpAddr, MAX_IP_ADDR_LEN);
   }
   
   if(getallSetOmcIpAddressTable(&setOmcIpAddressTableApiPtr, &outCount,&outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"mlpppConnectHandler: Get All failed on SetOmcIpAddressTable ");
      free(mlpppConfigRow);
      return;
   }

   /*Sending Config request to CM*/
   gCurrentConnectivityMode = MLPPP_MODE;
   oamsCfgCmSetIpAddress.neipPort = CONFIG_CP_PORT ;
   oamsCfgCmSetIpAddress.omcPort =setOmcIpAddressTableApiPtr->omcIpPort ;

   cfgSendMessage(&oamsCfgCmSetIpAddress, sizeof(OamsCfgCmSetIpAddress), ENT_OAM_CM, OAMS_CFG_CM_SET_IP_ADDRESS_REQ, 0); 

   /*Sending Mode Indication to AFH*/
   memcpy(oamsCfgAfhConModeIndi.nodeipAddress, oamsCfgCmSetIpAddress.neipAddress, MAX_IP_ADDR_LEN);
   memcpy(oamsCfgAfhConModeIndi.omcipAddress, oamsCfgCmSetIpAddress.omcipAddress, MAX_IP_ADDR_LEN);
   oamsCfgAfhConModeIndi.connectivityMode = MLPPP_MODE;
   cfgSendMessage(&oamsCfgAfhConModeIndi, sizeof(OamsCfgAfhConModeIndi), ENT_OAM_AFH, OAMS_CFG_AFH_CON_MODE_INDICATION, 0); 

   free(mlpppConfigRow);
   free(setOmcIpAddressTableApiPtr);
   
   LOG_PRINT(LOG_INFO,"mlpppConnectHandler: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : mlpppDisconnectHandler()
Parameters   : None
Return type   : I_Void
Purpose      : This function handles the Disconnect alarm.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void mlpppDisconnectHandler()
{
   SetOmcIpAddressTableApi *setOmcIpAddressTableApiPtr = NULL;
   I_U32 outRows;
   I_U16 outSize;
   LOG_PRINT(LOG_INFO,"mlpppDisconnectHandler: Entering in Function");
   
   if(gStoredMsgBufPtr != NULL && gMlpppLinkStatus == MLPPP_LINK_ENABLED)
   {
      gMlpppLinkStatus = MLPPP_LINK_DISABLED;
      if(updateMlpppLinkStatus(MLPPP_LINK_DISABLED) != CLIB_SUCCESS) 
      {
         LOG_PRINT(MAJOR,"mlpppDisconnectHandler: Db Operation on MlpppConfigTable failed");
      }
      return;
   }

   gMlpppLinkStatus = MLPPP_LINK_DISABLED;
   if(updateMlpppLinkStatus(MLPPP_LINK_DISABLED) != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO,"mlpppDisconnectHandler: Db Operation on MlpppConfigTable failed");
   }

   if(gCurrentConnectivityMode == MLPPP_MODE || gCurrentConnectivityMode == NO_MODE)
   {
      if(getallSetOmcIpAddressTable(&setOmcIpAddressTableApiPtr, &outRows,&outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"mlpppDisconnectHandler: Get All failed on SetOmcIpAddressTable ");
         return;
      }
      sendSetOmcipAddressReqToCm(setOmcIpAddressTableApiPtr->omcIpAddr, setOmcIpAddressTableApiPtr->omcIpPort);
      free(setOmcIpAddressTableApiPtr);
   }
   
  

   LOG_PRINT(LOG_INFO,"mlpppDisconnectHandler: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : mlpppExhaustHandler()
Parameters   : None
Return type   : I_Void
Purpose      : This function handles the Mlppp Exhaust Alarm.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void mlpppExhaustHandler()
{
   MlpppConfigTableApi *mlpppConfigTable = NULL;
   SetOmcIpAddressTableApi *setOmcIpAddressTableApiPtr = NULL;
   OamsCfgOilMlpppConfigReq oamsCfgOilMlpppConfigReq;
   I_U32 count;
   I_U32 outRows;
   I_U16 outSize;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;
   I_U16 portId;
   I_U8 timeSlot;
   MccLinkResourceTableApi *mccLinkTablePtr = NULL;
   I_U8 chasisFrameId;
   I_U8 slotId;
   E1StreamMapTableIndices strmIndices;
   E1StreamMapTableApi *e1StreamRow = NULL;
 
   LOG_PRINT(LOG_INFO,"mlpppExhaustHandler: Entering in Function");
   if(gCurrentConnectivityMode == NO_MODE)
   {
      if(getallSetOmcIpAddressTable(&setOmcIpAddressTableApiPtr, &outRows,&outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"mlpppDisconnectHandler: Get All failed on SetOmcIpAddressTable ");
         return;
      }
      sendSetOmcipAddressReqToCm(setOmcIpAddressTableApiPtr->omcIpAddr, setOmcIpAddressTableApiPtr->omcIpPort);
      free(setOmcIpAddressTableApiPtr);
   }

   if(gStoredMsgBufPtr != NULL )
   {
      memcpy(oamsCfgOilMlpppConfigReq.nodeIp,((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->nodeIpAddr , MAX_IP_ADDR_LEN) ;
      memcpy(oamsCfgOilMlpppConfigReq.omcIp,((MlpppConfigTableApi *)(I_U8 *)gStoredMsgBufPtr)->omcIpAddr , MAX_IP_ADDR_LEN) ;    
   }
   else
   {
      if(getallMlpppConfigTable(&mlpppConfigTable, &outRows, &outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"mlpppExhaustHandler: Get All failed on MLpppconfigTable ");
         return;
      }
      memcpy(oamsCfgOilMlpppConfigReq.nodeIp, mlpppConfigTable->nodeIpAddr , MAX_IP_ADDR_LEN) ;
      memcpy(oamsCfgOilMlpppConfigReq.omcIp, mlpppConfigTable->omcIpAddr , MAX_IP_ADDR_LEN) ;    
   }
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"mlpppExhaustHandler: Db Call failed. No Active card is there");
      free(mlpppConfigTable);
      return ;
   }
 
   oamsCfgOilMlpppConfigReq.frameID = chasisFrameId;
   oamsCfgOilMlpppConfigReq.slotID = slotId;
	 oamsCfgOilMlpppConfigReq.forcedConfiguration = FORCEDCONFIG;
	 oamsCfgOilMlpppConfigReq.numChannel = mlpppConfigTable->numChannel;
   
   incrSize   = offsetof(MlpppConfigTableApi, trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   
   basePtr    = (I_U8 *) mlpppConfigTable + portBaseOffset;

   for(count = 0 ; count < mlpppConfigTable->numChannel ; count++)
   {
      portId = (*(I_U16 *) (basePtr + count*incrSize ));
      timeSlot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;
      if(getMccTrunkNumTsUsingExtTrunkNumTs(portId, timeSlot, &mccLinkTablePtr, &outRows, &outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"mlpppExhaustHandler: No Row for PortId [%d], TimeSlot [%d]", portId,timeSlot);   
         continue;
      }
      strmIndices.e1Num = mccLinkTablePtr->mccTrunkNum;
      strmIndices.e1Ts = mccLinkTablePtr->mccTrunkTs;

      if(getE1StreamMapTable( &strmIndices, &e1StreamRow) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: get operation on E1StreamMapTable Failed");
         free(mlpppConfigTable);
         free(mccLinkTablePtr);
         return CFG_FAILURE;
      }

      LOG_PRINT(LOG_INFO,"mlpppExhaustHandler: PortId [%d], TimeSlot [%d] MccTimeSlot [%d]", portId,timeSlot,  mccLinkTablePtr->mccTrunkTs);   
      oamsCfgOilMlpppConfigReq.mlpppChannel[count] =e1StreamRow->strmTs;
      free(mccLinkTablePtr);
   }

   cfgSendMessage(&oamsCfgOilMlpppConfigReq, sizeof(OamsCfgOilMlpppConfigReq), ENT_OAM_OIL, OAMS_CFG_OIL_MLPPP_CONFIG_REQ, 0);
      free(mlpppConfigTable);
   LOG_PRINT(LOG_INFO,"mlpppExhaustHandler: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : mlpppChanStatusHandler()
Parameters   : I_U8 *timeSlot
Return type   : I_Void
Purpose      : This function handles the ChanStatus alarm.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void mlpppChanStatusHandler(I_U8 *timeSlot)
{
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   
   LOG_PRINT(LOG_INFO,"mlpppChanStatusHandler: Entering in Function");
   populateChannelStatus(recAlarmPtr->key2, recAlarmPtr->key3, recAlarmPtr->key4, timeSlot);
   
   LOG_PRINT(LOG_INFO,"mlpppChanStatusHandler: Exiting from Function");
}

/********************************* Function  Header*****************************
Function Name   : sendSetOmcIpUsingMlpppConfig()
Parameters   : None
Return type   : I_Void
Purpose      : This function sends SetOmc Ip towards CM using MLPPP Config.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_S32 sendSetOmcIpUsingMlpppConfig()
{
   MlpppConfigTableApi  tbMsgPtr ;
   MlpppConfigTableApi *mlpppConfigTableApiPtr = NULL;
   I_U32 count;
   I_U32 outCount;
   I_U16 outSize;
   OamsCfgOilMlpppConfigReq oamsCfgOilMlpppConfigReq ;
   I_U8 chasisFrameId = gMyFrameId;
   I_U8 slotId = gMySlotId;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;
   I_U16 portId;
   I_U8 timeSlot;
   MccLinkResourceTableApi *mccLinkTablePtr = NULL;
   E1StreamMapTableIndices strmIndices;
   E1StreamMapTableApi *e1StreamRow = NULL;
   LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: Entering in Function");

   /* Fixed Issue 8574*/
   if(updateMlpppLinkStatus(MLPPP_LINK_DISABLED) != CLIB_SUCCESS) 
   {
      LOG_PRINT(MAJOR," sendSetOmcIpUsingMlpppConfig: Db Operation on MlpppConfigTable failed");
   }

   if(getallMlpppConfigTable(&mlpppConfigTableApiPtr, &outCount, &outSize) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: No MlpppConfugartion Available");
      return CFG_FAILURE;
   }
   memcpy(&tbMsgPtr,&mlpppConfigTableApiPtr,sizeof(MlpppConfigTableApi));
   #if 0
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: Card is not in Active state");
      free(mlpppConfigTableApiPtr);
      return CFG_FAILURE;
   }
   #endif

   oamsCfgOilMlpppConfigReq.frameID = chasisFrameId;
 	 oamsCfgOilMlpppConfigReq.slotID = slotId;
	 oamsCfgOilMlpppConfigReq.forcedConfiguration = FORCEDCONFIG;
	 oamsCfgOilMlpppConfigReq.numChannel = mlpppConfigTableApiPtr->numChannel;
   memcpy(oamsCfgOilMlpppConfigReq.nodeIp, mlpppConfigTableApiPtr->nodeIpAddr, sizeof (oamsCfgOilMlpppConfigReq.nodeIp)) ;
   memcpy(oamsCfgOilMlpppConfigReq.omcIp, mlpppConfigTableApiPtr->omcIpAddr, sizeof (oamsCfgOilMlpppConfigReq.omcIp)) ;    

/*   memcpy(oamsCfgOilMlpppConfigReq.nodeIp, 
          mlpppConfigTableApiPtr->nodeIpAddr , 
          MAX_IP_ADDR_LEN) ;
   memcpy(oamsCfgOilMlpppConfigReq.omcIp, 
          mlpppConfigTableApiPtr->omcIpAddr , 
          MAX_IP_ADDR_LEN) ;    

   count = sizeof (oamsCfgOilMlpppConfigReq.omcIp) ;
   count = MAX_IP_ADDR_LEN;
   count = sizeof (oamsCfgOilMlpppConfigReq.nodeIp) ;
*/
   incrSize   = offsetof(MlpppConfigTableApi ,trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   
   basePtr    = (I_U8 *)mlpppConfigTableApiPtr + portBaseOffset;

   for(count = 0 ; count < mlpppConfigTableApiPtr->numChannel ; count++)
   {
      portId = (*(I_U16 *) (basePtr + count*incrSize ));
      timeSlot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;
      if(getMccTrunkNumTsUsingExtTrunkNumTs(portId, timeSlot, &mccLinkTablePtr, &outCount, &outSize) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: No Row found for PortId[%d] , timeslot [%d] in Mcc LinkResource Table", portId, timeSlot);
         continue;
         
      }
      strmIndices.e1Num = mccLinkTablePtr->mccTrunkNum;
      strmIndices.e1Ts = mccLinkTablePtr->mccTrunkTs;

      if(getE1StreamMapTable( &strmIndices, &e1StreamRow) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: get operation on E1StreamMapTable Failed");
         free(mlpppConfigTableApiPtr);
         free(mccLinkTablePtr);
         return CFG_FAILURE;
      }
      
      oamsCfgOilMlpppConfigReq.mlpppChannel[count] = e1StreamRow->strmTs;
      free(e1StreamRow);
      free(mccLinkTablePtr);
   }

   cfgSendMessage(&oamsCfgOilMlpppConfigReq, sizeof(OamsCfgOilMlpppConfigReq), ENT_OAM_OIL, OAMS_CFG_OIL_MLPPP_CONFIG_REQ, 0);
   /*sending same message to TB_BSC    */
   cfgSendMessage(&tbMsgPtr, sizeof(MlpppConfigTableApi), ENT_PSAPP_TBBSC, OAMS_CFG_TBBSC_ADD_MLPPP_CONFIG, 0);
   
   gMlpppLinkStatus = mlpppConfigTableApiPtr->mlppLinkStatus;
   free(mlpppConfigTableApiPtr);
   LOG_PRINT(LOG_INFO,"sendSetOmcIpUsingMlpppConfig: Exiting from Function");
   return CFG_SUCCESS;
}

/********************************* Function  Header*****************************
Function Name   : checkForMlpppConfig()
Parameters   : None
Return type   : I_Void
Purpose      : This function Checks Mlppp Configuration when Trunk State Change 
               request comes to disable the trunk port.
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/

I_S32 checkForMlpppConfig(I_U16 trunkPortId)
{
   MlpppConfigTableApi *mlpppConfigTableApiPtr = NULL;
   I_U32 count;
   I_U32 outCount;
   I_U16 outSize;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U8 *basePtr;
   I_U16 portId;

   LOG_PRINT(LOG_INFO,"checkForMlpppConfig: Entering from Function");
   if(getallMlpppConfigTable(&mlpppConfigTableApiPtr, &outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"checkForMlpppConfig: No Row found in MlpppConfigTable");
      return CFG_SUCCESS;
   }
   
   incrSize   = offsetof(MlpppConfigTableApi ,trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   
   basePtr    = (I_U8 *)mlpppConfigTableApiPtr + portBaseOffset;
   for(count = 0 ; count < mlpppConfigTableApiPtr->numChannel ; count++)
   {
      portId = (*(I_U16 *) (basePtr + count*incrSize ));
      if(portId == trunkPortId)
      {
         free(mlpppConfigTableApiPtr);
         return CFG_FAILURE;
      }
   }
  
   free(mlpppConfigTableApiPtr);
   LOG_PRINT(LOG_INFO,"checkForMlpppConfig: Exiting from Function");
   return CFG_SUCCESS;
}


/******************************* Function  Header*****************************
  Function Name : modifyMlppConfigTable()
Parameters    : MlpppConfigTableApi *receivedMsgPtr, MlpppConfigTableApi *mlpppConfigTableDbPtr
Return type   : I_Void
Purpose       : To Modify the parameters in the MlpppConfig table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifyMlppConfigTable(MlpppConfigTableApi *receivedMsgPtr, MlpppConfigTableApi *mlpppConfigTableDbPtr)
{
   OamsCfgOilMlpppConfigReq oamsCfgOilMlpppConfigReq;
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_Bool storeStatus;

   LOG_PRINT(LOG_INFO,"modifyMlppConfigTable: Entering from Function");
   /* Check any field is getting modified */
   if(isAnyFieldModifiedinMlppp(receivedMsgPtr,mlpppConfigTableDbPtr) == CFG_FAILURE) {
      LOG_PRINT(LOG_INFO,"modifyMlpppConfigTableHandler: no field modified");
      return;
   }
   /* Validate parameters received for modification */
   if(validateMlpppConfigReq() == CFG_FAILURE)
   {
      LOG_PRINT(LOG_INFO,"modifyMlpppConfigTableHandler: Cannot modify MlpppConfig");
      return;
   }

   /* Store all related(mlpp configured) rows of MccLinkResourceTable in local global pointer*/
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"modifyMlppConfigTable: Db Call failed. No Active card is there");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }

   if (getMccLinkRowsOfLinkType(SYS_TS_USAGE_MLPPP, slotId,
      &gMccLinkResourcePtr, &gMccOutCount, &gMccOutSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR, "Data inconsistency found in MccLinkReourceTable for MLPPP Function:%s Line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return ;
   }

   /* Update all locally retrived rows of MccLinkResourceTable for Mlppp  
     gMccLinkResourcePtr with Status=Free, ExtTrunkNum=INVALID and ExtTrunkTs=INVALID */
   resetMccTrunkTsRowsforMlppIngBuff();

   /* Store the received message buffer in global pointer */
   //storeStatus = storeReceivedMsgBuffer(receivedMsgPtr, sizeof(MlpppConfigTableApi));

   gMlpppStoredMsgBufPtr = AlocOrdBuf(sizeof(MlpppConfigTableApi));
   if(gMlpppStoredMsgBufPtr != NULL)
   {
      memcpy(gMlpppStoredMsgBufPtr,receivedMsgPtr,sizeof(MlpppConfigTableApi));
   }

   /* From MccLinkResourceTable update receive TrunkPort & Ts and mark status Busy locally */
   if(allocateChannelOnModify(receivedMsgPtr, slotId, &oamsCfgOilMlpppConfigReq) == CFG_FAILURE)
   {
      return;
   }


   oamsCfgOilMlpppConfigReq.frameID = chasisFrameId;
   oamsCfgOilMlpppConfigReq.slotID = slotId; 
   oamsCfgOilMlpppConfigReq.forcedConfiguration = FORCEDCONFIG;
   oamsCfgOilMlpppConfigReq.numChannel = receivedMsgPtr->numChannel;
   memcpy(oamsCfgOilMlpppConfigReq.nodeIp, receivedMsgPtr->nodeIpAddr , MAX_IP_ADDR_LEN) ;
   memcpy(oamsCfgOilMlpppConfigReq.omcIp, receivedMsgPtr->omcIpAddr , MAX_IP_ADDR_LEN) ;    

   cfgSendAckToCm();
   sleep(1);
   cfgSendMessage(&oamsCfgOilMlpppConfigReq, sizeof(OamsCfgOilMlpppConfigReq), ENT_OAM_OIL, OAMS_CFG_OIL_MLPPP_CONFIG_REQ, 0);

   LOG_PRINT(LOG_INFO,"modifyMlpppConfigTableHandler: Exiting from Function");

}

/******************************* Function  Header*****************************
Function Name : disconTsForMlppp()
Parameters    :  
Return type   : I_S32
Purpose       : Send Switch Disconnect to GRHM, for all the connections existing
                in MccLinkResourcePtr for Mlppp.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/

I_S32 disconTsForMlppp()
{
   MccLinkResourceTableApi *tmpMccPtr = NULL;
   OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;

   MccLinkResourceTableApi *mccLinkResourcePtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0,i;
   I_U8 chasisFrameId;
   I_U8 slotId;
 
   LOG_PRINT(LOG_INFO,"disconTsForMlppp: Entering from Function");
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"disconTsForMlppp: Db Call failed. No Active card is there");
      sendConfigFailAlarmToAfh(CM_ERR_GET_DB_OPER_FAILED);
//      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
  
   if (getMccLinkRowsOfLinkType(SYS_TS_USAGE_MLPPP, slotId,
      &mccLinkResourcePtr, &outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "disconTsForMlppp:Data inconsistency found in MccLinkReourceTable for MLPPP Function:%s Line:%d",__FUNCTION__,__LINE__);
      sendConfigFailAlarmToAfh(CM_ERR_GET_DB_OPER_FAILED);
//      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }

   for (i = 0; i < outCount; i++)
   {
      tmpMccPtr = (MccLinkResourceTableApi *)((I_U8*)mccLinkResourcePtr + (i *outSize));
      if (tmpMccPtr->mccLinkStatus != SYS_TS_FREE)
      {
        /* Send SWITCH_DISCONNECT to GRHM */
        LOG_PRINT(LOG_INFO,"disconTsForMlppp: Sending OAMS_CFG_GRHM_SWITCH_DISCONNECT..");
        oamsCfgGrhmSwitchDisconnect.firstE1Num = tmpMccPtr->mccTrunkNum;
        oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = tmpMccPtr->mccTrunkTs;
        oamsCfgGrhmSwitchDisconnect.secondE1Num = tmpMccPtr->extTrunkNum;
        oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = tmpMccPtr->extTrunkTs;
        LOG_PRINT(LOG_INFO,"disconTsForMlppp: oamsCfgGrhmSwitchDisconnect : First E1 : %d, \
         First Ts : %d, SecE1 : %d, SecTs : %d",
         oamsCfgGrhmSwitchDisconnect.firstE1Num, oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum, 
         oamsCfgGrhmSwitchDisconnect.secondE1Num, oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum);

        cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchDisconnect),
        ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
  
        #if 0 
        /*Temp Changes for MLPPP Starts - GRV*/ 

        /* Send SWITCH_DISCONNECT to GRHM */
        LOG_PRINT(LOG_INFO,"disconTsForMlppp-2: Sending OAMS_CFG_GRHM_SWITCH_DISCONNECT..");
        oamsCfgGrhmSwitchDisconnect.firstE1Num = tmpMccPtr->extTrunkNum;
        oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = tmpMccPtr->extTrunkTs;
        oamsCfgGrhmSwitchDisconnect.secondE1Num = tmpMccPtr->mccTrunkNum;
        oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = tmpMccPtr->mccTrunkTs;
        LOG_PRINT(LOG_INFO,"disconTsForMlppp-2: oamsCfgGrhmSwitchDisconnect : First E1 : %d, \
         First Ts : %d, SecE1 : %d, SecTs : %d",
         oamsCfgGrhmSwitchDisconnect.firstE1Num, oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum, 
         oamsCfgGrhmSwitchDisconnect.secondE1Num, oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum);

        cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchDisconnect),
        ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);

        /*Temp Changes for MLPPP Ends- GRV*/ 
        #endif
      }
   }
   LOG_PRINT(LOG_INFO,"disconTsForMlppp: Exiting from Function");
   return CFG_SUCCESS;
}


/******************************* Function  Header*****************************
Function Name : delAllInvalidMlpppStatusRows()
Parameters    :  
Return type   : I_S32
Purpose       : Delete all rows from MlpppChannelStatusTable that are not in sync 
                with TrunkPort-Ts available in MlpppConfigTable. 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/

I_S32 delAllInvalidMlpppStatusRows()
{
   MlpppConfigTableApi *mlpppConfigTableDbPtr = NULL;
   MlpppChannelStatusTableApi *mlpppChannelStsTableDbPtr = NULL;
   MlpppChannelStatusTableApi *tmpMlpppChannelStatusPtr = NULL;
   MlpppChannelStatusTableIndices mlpppChannelStatus;

   I_U32 outRows = 0, outStsRows = 0;
   I_U16 outSize = 0, outStsSize = 0, i;

   LOG_PRINT(LOG_INFO,"delAllInvalidMlpppStatusRows: Entering from Function");
   if(getallMlpppConfigTable(&mlpppConfigTableDbPtr, &outRows, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "Data inconsistency found MlpppConfigTable Function:%s Line:%d",__FUNCTION__,__LINE__);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
  
   
   if(getallMlpppChannelStatusTable(&mlpppChannelStsTableDbPtr, &outStsRows, &outStsSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "No row found in MlpppChannelStatusTable");
      return CFG_SUCCESS;
   }


   for (i=0; i< outStsRows; i++)
   {
      tmpMlpppChannelStatusPtr = (MlpppChannelStatusTableApi *)((I_U8*)mlpppChannelStsTableDbPtr + (i *outStsSize));
    
      if(isMlpppStsTrunkPortTsValid(tmpMlpppChannelStatusPtr, mlpppConfigTableDbPtr) == CFG_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG, "MlpppStatusTable entry is valid for Trunkport:%d Ts%d", tmpMlpppChannelStatusPtr->trunkportId,tmpMlpppChannelStatusPtr->timeslot);
      }
      else
      {
     
         LOG_PRINT(LOG_DEBUG, "MlpppStatusTable entry is invalid for Trunkport:%d Ts%d", tmpMlpppChannelStatusPtr->trunkportId,tmpMlpppChannelStatusPtr->timeslot);
         mlpppChannelStatus.trunkportId =tmpMlpppChannelStatusPtr->trunkportId ;
         mlpppChannelStatus.timeslot = tmpMlpppChannelStatusPtr->timeslot;
         
         if(deleteMlpppChannelStatusTable(&mlpppChannelStatus) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_CRITICAL, "Entry can not be deleted Trunkport: [%d] Ts [%d]", tmpMlpppChannelStatusPtr->trunkportId,tmpMlpppChannelStatusPtr->timeslot);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return CFG_FAILURE;
            
         }
      }
   } 
   free(mlpppConfigTableDbPtr); 
   free(mlpppChannelStsTableDbPtr); 
   LOG_PRINT(LOG_INFO,"delAllInvalidMlpppStatusRows: Exiting from Function");
   return CFG_SUCCESS;
}

/******************************* Function  Header*****************************
Function Name : isMlpppStsTrunkPortTsValid()
Parameters    :  
Return type   : I_S32
Purpose       : Checks Trunkport & Ts of MlpppChannelStatus row is available on 
                any of the TrunkPort & Ts of MlpppConfigTable.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 isMlpppStsTrunkPortTsValid(MlpppChannelStatusTableApi *mlpppChannelStatusPtr,MlpppConfigTableApi *mlpppConfigTableDbPtr)
{
   I_U32 count;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;
   I_U16 trunkportId;
   I_U8 timeSlot;

   LOG_PRINT(LOG_INFO,"isMlpppStsTrunkPortTsValid: Entering from Function");
   incrSize   = offsetof(MlpppConfigTableApi, trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   
   basePtr    = (I_U8 *) mlpppConfigTableDbPtr + portBaseOffset;

   for(count = 0 ; count < mlpppConfigTableDbPtr->numChannel ; count++)
   {
      trunkportId = (*(I_U16 *) (basePtr + count*incrSize ));
      timeSlot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;
      if( (trunkportId == mlpppChannelStatusPtr->trunkportId) && (timeSlot == mlpppChannelStatusPtr->timeslot))
      {
         LOG_PRINT(LOG_DEBUG,"Mlppp status valid for PortId [%d], TimeSlot [%d]", trunkportId,timeSlot);   
         return CFG_SUCCESS;
      }
   }
   LOG_PRINT(LOG_INFO,"isMlpppStsTrunkPortTsValid: Exiting from Function");
   return CFG_FAILURE;
}

/******************************* Function  Header*****************************
Function Name : updateMccLinkResforAllrows()
Parameters    : MccLinkResourceTableApi *mccLinkResourcePtr, I_U32 outRows, I_U16 outSize
Return type   : I_S32
Purpose       : Updates MccLinkRespourceTable for the rows received in input.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 updateMccLinkResforAllrows(MccLinkResourceTableApi *mccLinkResourcePtr, I_U32 outRows, I_U16 outSize)
{
   MccLinkResourceTableApi *tmpMccLinkResourcePtr = NULL;
   I_U16 i;

   LOG_PRINT(LOG_INFO,"updateMccLinkResforAllrows: Entering from Function");
   for (i=0; i< outRows; i++)
   {
      tmpMccLinkResourcePtr = (MccLinkResourceTableApi *)((I_U8*)mccLinkResourcePtr + (i *outSize));
      tmpMccLinkResourcePtr->cardNum = ICCSELFCARD;
      if (updateMccLinkResourceTable(tmpMccLinkResourcePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(MAJOR,"updateMccLinkResforAllrows: Updation failed on self card for MccLinkResourceTable for mccTrunkNum: %d mccTrunkTs: %d", tmpMccLinkResourcePtr->mccTrunkNum, tmpMccLinkResourcePtr->mccTrunkTs);
         return CFG_FAILURE;
      }  
      tmpMccLinkResourcePtr->cardNum = ICCMATECARD;
      if (updateMccLinkResourceTable(tmpMccLinkResourcePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(MAJOR,"updateMccLinkResforAllrows: Updation failed on Mate card for MccLinkResourceTable for mccTrunkNum: %d mccTrunkTs: %d", tmpMccLinkResourcePtr->mccTrunkNum, tmpMccLinkResourcePtr->mccTrunkTs);
         return CFG_FAILURE;
      }
      LOG_PRINT(DEBUG,"updateMccLinkResforAllrows: Updation successful on Self & Mate card for MccLinkResourceTable for mccTrunkNum: %d mccTrunkTs: %d", tmpMccLinkResourcePtr->mccTrunkNum, tmpMccLinkResourcePtr->mccTrunkTs);
   } 
   LOG_PRINT(LOG_INFO,"updateMccLinkResforAllrows: Exiting from Function");
   return CFG_SUCCESS;
}
/******************************* Function  Header*****************************
Function Name : resetAllMlppMccTrunkTsRows()
Parameters    : 
Return type   : I_S32
Purpose       : Reset all Mlppp based rows in MccLinkResourceTable to FREE,
                INAVID_TRUNKPORT, INVALID_TS in extTrunk and extTs 
                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/

I_S32 resetAllMlppMccTrunkTsRows()
{
   MccLinkResourceTableApi *mccLinkResourcePtr = NULL;
   MccLinkResourceTableApi *tmpMccPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0,i;
   I_U8 chasisFrameId;
   I_U8 slotId;
 
   LOG_PRINT(LOG_INFO,"resetAllMlppMccTrunkTsRows: Entering into Function");
   if(getActiveIccSlotId(&chasisFrameId, &slotId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"resetAllMlppMccTrunkTsRows: Db Call failed. No Active card is there");
      sendConfigFailAlarmToAfh(CM_ERR_GET_DB_OPER_FAILED);
//      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
  
   if (getMccLinkRowsOfLinkType(SYS_TS_USAGE_MLPPP, slotId,
      &mccLinkResourcePtr, &outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL, "resetAllMlppMccTrunkTsRows: Data inconsistency found in MccLinkReourceTable for MLPPP Function:%s Line:%d",__FUNCTION__,__LINE__);
      sendConfigFailAlarmToAfh(CM_ERR_GET_DB_OPER_FAILED);
//      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
   
   for (i = 0; i < outCount; i++)
   {
      tmpMccPtr = (MccLinkResourceTableApi *)((I_U8*)mccLinkResourcePtr + (i *outSize));
      if (tmpMccPtr->mccLinkStatus != SYS_TS_FREE)
      {
        /* update MccLinkResourceTable for status(FREE), TrunkPort(INVALID) & Timeslot(INVALID) in DB */
        tmpMccPtr->extTrunkNum = INVALID_E1;
        tmpMccPtr->extTrunkTs = INVALID_TS;
        tmpMccPtr->mccLinkStatus = SYS_TS_FREE;
        tmpMccPtr->cardNum = ICCSELFCARD;
        if( updateMccLinkResourceTable( tmpMccPtr ) != CLIB_SUCCESS)
        {
           LOG_PRINT(MAJOR,"resetAllMlppMccTrunkTsRows: Updation failed on Selfcard for MccLinkResourceTable for mccTrunkNum: %d mccTrunkTs: %d", tmpMccPtr->mccTrunkNum, tmpMccPtr->mccTrunkTs);
           return CFG_FAILURE;
        }
        tmpMccPtr->cardNum = ICCMATECARD;
        if(updateMccLinkResourceTable (tmpMccPtr) != CLIB_SUCCESS)
        {
           LOG_PRINT(MAJOR,"resetAllMlppMccTrunkTsRows: Updation failed on Matecardfor MccLinkResourceTable for mccTrunkNum: %d mccTrunkTs: %d", tmpMccPtr->mccTrunkNum, tmpMccPtr->mccTrunkTs);
           return CFG_FAILURE;
        }
        LOG_PRINT(DEBUG,"resetAllMlppMccTrunkTsRows: Updation successful on Mate and Self card for MccLinkResourceTable for mccTrunkNum: %d mccTrunkTs: %d", tmpMccPtr->mccTrunkNum, tmpMccPtr->mccTrunkTs);
      }
   }
   free(mccLinkResourcePtr);
   LOG_PRINT(LOG_INFO,"resetAllMlppMccTrunkTsRows: Exiting from Function");
   return CFG_SUCCESS;
}
/******************************* Function  Header*****************************
Function Name : isAnyFieldModifiedinMlppp()
Parameters    : MlpppConfigTableApi *receivedMsgPtr, MlpppConfigTableApi *mlpppConfigTableDbPtr
Return type   : I_S32
Purpose       : Checks Trunkport & Ts of MlpppChannelStatus row is available on 
                any of the TrunkPort & Ts of MlpppConfigTable.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 isAnyFieldModifiedinMlppp(MlpppConfigTableApi *receivedMsgPtr, MlpppConfigTableApi *mlpppConfigTableDbPtr)
{
   LOG_PRINT(LOG_INFO,"isAnyFieldModifiedinMlppp: entering into Function");
   if ( memcmp((void *)receivedMsgPtr,(void *)mlpppConfigTableDbPtr,sizeof(MlpppConfigTableApi)))
   {
      /* Update operation. */
      LOG_PRINT(LOG_DEBUG,"isAnyFieldModifiedinMlppp: Received message pointer is getting modified");
      return CFG_SUCCESS;
   }
   else
   {
      LOG_PRINT(LOG_INFO," isAnyFieldModifiedinMlppp: Received parameters and DB parameters are same");
      cfgSendAckToCm(); /* No need to send Nack. Send Ack no update required. */
      return CFG_FAILURE;
    }
}

/******************************* Function  Header*****************************
Function Name : freegStoreMsgBuff()
Parameters    : 
Return type   : 
Purpose       :  
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void freegStoreMsgBuff()
{
   LOG_PRINT(LOG_DEBUG,"freegStoreMsgBuff: Enetring in function");
   if (gStoredMsgBufPtr!=NULL)
   {
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr= NULL;
   }
   LOG_PRINT(LOG_DEBUG,"freegStoreMsgBuff: Exiting from function");
}

/********************************* Function  Header*****************************
Function Name   : allocateChannelOnModify()
Parameters   : OamsCfgOilMlpppConfigReq *oamsCfgOilMlpppConfigReq
Return type   : I_S32
Purpose      : Allocate Free channels for the request
Other Note   : Added For BSC CS4.0 HA Feature
 *******************************************************************************/

I_S32 allocateChannelOnModify(MlpppConfigTableApi *receivedMsgPtr, I_U8 slotId, OamsCfgOilMlpppConfigReq *oamsCfgOilMlpppConfigReq )
{
   MccLinkResourceTableApi *tmpRow = NULL;
   I_U32 count;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;
   I_U16 portId;
   I_U8 timeSlot;
   E1StreamMapTableIndices strmIndices;
   E1StreamMapTableApi *e1StreamRow = NULL;

   LOG_PRINT(LOG_INFO,"allocateChannelOnModify: Entering in Function");
   
   incrSize   = offsetof(MlpppConfigTableApi, trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   
   basePtr    = (I_U8 *)receivedMsgPtr + portBaseOffset;


   for(count = 0 ; count < receivedMsgPtr->numChannel ; count++)
   {
      tmpRow = (MccLinkResourceTableApi *)((I_U8 *) gMccLinkResourcePtr + (count*gMccOutSize));
      portId = (*(I_U16 *) (basePtr + count*incrSize ));
      timeSlot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;
      LOG_PRINT(LOG_INFO,"allocateChannelOnModify: Allocating Channel for PortId [%d], TimeSlot [%d]", portId,timeSlot);

      /* Update linkstatus, portId and timeslot in extTrunkNum and Timeslots*/
      tmpRow->extTrunkNum = portId;
      tmpRow->extTrunkTs = timeSlot;
      tmpRow->mccLinkStatus = SYS_TS_ALLOCATED;
      
      strmIndices.e1Num = tmpRow->mccTrunkNum;
      strmIndices.e1Ts = tmpRow->mccTrunkTs;

      if(getE1StreamMapTable( &strmIndices, &e1StreamRow) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"allocateChannelOnModify: get operation on E1StreamMapTable Failed");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         free(gMccLinkResourcePtr);
         return CFG_FAILURE;
      }
      oamsCfgOilMlpppConfigReq->mlpppChannel[count] = e1StreamRow->strmTs;
      free(e1StreamRow);
   }
   LOG_PRINT(LOG_INFO,"allocateChannelOnModify: Exiting from Function");
   return CFG_SUCCESS; 
}

/******************************* Function  Header*****************************
Function Name : resetMccTrunkTsRowsforMlppIngBuff()
Parameters    : 
Return type   : I_S32
Purpose       : Reset all Mlppp based rows in MccLinkResourceTable to FREE,
                INAVID_TRUNKPORT, INVALID_TS in extTrunk and extTs 
                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/

I_S32 resetMccTrunkTsRowsforMlppIngBuff()
{
   MccLinkResourceTableApi *tmpMccPtr = NULL;
   I_U16 i; 
   for (i = 0; i < gMccOutCount; i++)
   {
      tmpMccPtr = (MccLinkResourceTableApi *)((I_U8*)gMccLinkResourcePtr + (i *gMccOutSize));
      if (tmpMccPtr->mccLinkStatus != SYS_TS_FREE)
      {
        /* update MccLinkResourceTable for status(FREE), TrunkPort(INVALID) & Timeslot(INVALID) in local buffer */
        tmpMccPtr->extTrunkNum = INVALID_E1;
        tmpMccPtr->extTrunkTs = INVALID_TS;
        tmpMccPtr->mccLinkStatus = SYS_TS_FREE;
      }
   }
   return CFG_SUCCESS;
}
/******************************* Function  Header*****************************
Function Name : insertMlpppChannelStatusforAllRows()
Parameters    : 
Return type   : I_Void
Purpose       : Insert rows for mlppp channel status table for all the channels present in 
                MlpppConfigTable in DB.                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void insertMlpppChannelStatusforAllRows()
{
   MlpppConfigTableApi *mlpppConfigTableApiPtr = NULL;
   MlpppChannelStatusTableApi channelStatusTableRow;
   I_U32 count;
   I_U32 outCount;
   I_U16 outSize;
   I_U32 incrSize;
   I_U32 portBaseOffset;
   I_U32 tsBaseOffset;
   I_U8 *basePtr;

   LOG_PRINT(LOG_INFO,"insertMlpppChannelStatusforAllRows: Entering into Function");
    if(getallMlpppConfigTable(&mlpppConfigTableApiPtr, &outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertMlpppChannelStatusforAllRows: No Row found in MlpppConfigTable");
      return;
   }
   
   incrSize   = offsetof(MlpppConfigTableApi ,trunkportId2) - offsetof(MlpppConfigTableApi, trunkportId1);
   portBaseOffset = offsetof(MlpppConfigTableApi, trunkportId1);
   tsBaseOffset   = offsetof(MlpppConfigTableApi, timeslot1) - offsetof(MlpppConfigTableApi, trunkportId1);
   basePtr    = (I_U8 *)mlpppConfigTableApiPtr + portBaseOffset;

   for(count = 0 ; count < mlpppConfigTableApiPtr->numChannel ; count++)
   {
      channelStatusTableRow.mlpppLinkId = mlpppConfigTableApiPtr->mlpppLinkId;
      channelStatusTableRow.trunkportId = (*(I_U16 *) (basePtr + count*incrSize ));
      channelStatusTableRow.timeslot = (* (I_U8 *) (basePtr + tsBaseOffset + count*incrSize)) ;
      channelStatusTableRow.channelStatus = MLPPP_CHANNEL_DISABLED;
      if(updateMlpppChannelStatusTable(&channelStatusTableRow) != CLIB_SUCCESS) 
      {
         if(insertMlpppChannelStatusTable(&channelStatusTableRow) != CLIB_SUCCESS) 
         {
            LOG_PRINT(LOG_CRITICAL,"insertMlpppChannelStatusforAllRows: Insertion in Channel Status Table failed");
            free(mlpppConfigTableApiPtr);
            return;
         }
      }
   }  
   free(mlpppConfigTableApiPtr);
   LOG_PRINT(LOG_INFO,"insertMlpppChannelStatusforAllRows: Exiting from Function");
   return;
}

/******************************* Function  Header*****************************
Function Name : convertIpToToken()
Parameters    : char *s, int *a[]
Return type   : I_Void
Purpose       : Converts IP in to Token.                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/

void convertIpToToken(char *s,int *a[])
{
   char *tempString;
   char tempString1[25];
   int i=0,number;
   LOG_PRINT(LOG_INFO,"convertIpToToken: Entering from Function");
   memcpy(tempString1, s, strlen(s) + 1);
   tempString=strtok(tempString1,".");
   while(tempString !=NULL)
   {
      number=atoi(tempString);
      *(a+i)=number; 
      LOG_PRINT(INFO,"convertIpToToken: a[%d] : %d , number : %d ",i,a[i],number);
      i++;
      tempString=strtok(NULL,".");
   }
   
   tempString=NULL;
   LOG_PRINT(LOG_INFO,"convertIpToToken: Exiting from Function");
  
}
