/************************************************************* File Header ***
File Name      : oamscfg_eic_sw_upgrade_handler.c
Purpose        : This file contains function defintions required for handling
                 EIC SW Download and Activation.
Project        : BSC
Subsystem      : OAMS 
Author         : Aricent 
CSCI id        :
Version        :
 ******************************************************************** End ***/

#include "oamscfg_includes.h"

#define convertNodeType(nodeType,intValue) \
if(intValue == SYS_NODE_TYPE_BSC) \
strcpy(nodeType,"BSC"); \
else if(intValue == SYS_NODE_TYPE_EIC) \
strcpy(nodeType,"EIC"); \
else if(intValue == SYS_NODE_TYPE_BIC) \
strcpy(nodeType,"BIC"); \
else if(intValue == SYS_NODE_TYPE_R2_BTS) \
strcpy(nodeType,"BTS"); \
else if(intValue == SYS_NODE_TYPE_TRX) \
strcpy(nodeType,"TRX"); \
else if(intValue == SYS_NODE_TYPE_DSP) \
strcpy(nodeType,"DSP");


/******************************* Function  Header*****************************
   Function Name :    setEicSwMOfferTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles EIC Sw Upgrade Offer request from OMC/CLI
Other Note    : Added For BSC CS4.0
*****************************************************************************/
I_Void setEicSwMOfferTableHandler()
{
   SwMOfferTableApi *receiveMsgPtr = NULL;
   SwMOfferTableApi *swMOfferTableDbPtr = NULL;
   
   receiveMsgPtr = (SwMOfferTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SwMOfferTableIndices swMOfferTableindex;
   SwMTableApi *swMTableDbPtr = NULL;
   SwMTableIndices swMTableindex;
   I_S32 actionInProgress = I_FALSE;
   I_S32 ret = ONE;
   I_U32 rowCount = ZERO;
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;
   I_CHAR logPasswdChSum[OAMS_NAME_SIZE + 1]; 
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_U32 nodeType = 0, failType =0, swStatus = 0;

   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   if ( ( receiveMsgPtr->slotId != slotId ) && (receiveMsgPtr->slotId != 0xFF ))
   {
      LOG_PRINT(LOG_INFO,"Invalid SlotId Passed");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;
   }

   swMOfferTableindex.nodeType = receiveMsgPtr->nodeType;
   swMOfferTableindex.chasisFrameId = chasisFrameId;
   swMOfferTableindex.slotId = slotId;
   strcpy(swMOfferTableindex.upgradeVersion,receiveMsgPtr->upgradeVersion);
   swMTableindex.nodeType = receiveMsgPtr->nodeType;
   swMTableindex.chasisFrameId = chasisFrameId;
   swMTableindex.slotId = slotId;
   strcpy(swMTableindex.swVersion,receiveMsgPtr->upgradeVersion);

   LOG_PRINT(LOG_INFO,"setEicSwMOfferTableHandler : Entering function");
   LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->upgradeVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
   LOG_PRINT(LOG_INFO,"ftpServerAddress: %u",receiveMsgPtr->ftpServerAddress);
   memset(logPasswdChSum,(I_S32)NULL,OAMS_NAME_SIZE + 1);
   memcpy(logPasswdChSum,receiveMsgPtr->loginName,OAMS_NAME_SIZE);
   LOG_PRINT(LOG_INFO,"loginName: %s ",logPasswdChSum);
   memset(logPasswdChSum,(I_S32)NULL,OAMS_NAME_SIZE + 1);
   memcpy(logPasswdChSum,receiveMsgPtr->password,OAMS_NAME_SIZE);
   LOG_PRINT(LOG_INFO,"password: %s",logPasswdChSum);
   memset(logPasswdChSum,(I_S32)NULL,OAMS_NAME_SIZE + 1);
   memcpy(logPasswdChSum,receiveMsgPtr->checksum,OAMS_NAME_SIZE);
   LOG_PRINT(LOG_INFO,"checksum: %s",logPasswdChSum);
   LOG_PRINT(LOG_INFO,"size: %u",receiveMsgPtr->size);

   /*Check Sw Version is in correct format*/
   if (convertInputStringToNumber(receiveMsgPtr->upgradeVersion,&tokenNum,
            token,&errCause) == SW_VER_SUCCESS)
   {
      if ((token[0] == 0) || (token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
      {
         LOG_PRINT(LOG_DEBUG,"Recieved Sw Version format incorrect ");
         cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
         return;
      }         
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
      cfgSendNackToCm(errCause);
      return;
   }

   /*Retrieve count of number of rows present in SwMOffer Table */ 
   if (getCountOfSwUpgradeOfferTable(&rowCount) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"No row present in SwMOffer Table");
   }
   else
   {
      /*Check if already maximum allowed upgrade offer is in progress */
      if (rowCount == MAX_SW_UPGRADE_OFFER_IN_PARALLEL)
      {
         LOG_PRINT(LOG_DEBUG,"Already Max allowed swUpgradeOffer is in progress");
         cfgSendNackToCm(CM_ERR_MAX_SW_UPGRADE_OFFER_ALREADY_RUNNING);
         return;
      }

      /*Check if entry exists in SwMOffer table for req swVersion */
      ret = getSwMOfferTable(&swMOfferTableindex,&swMOfferTableDbPtr);
      if (swMOfferTableDbPtr != NULL)
      {
         LOG_PRINT(LOG_DEBUG,"Platform has already started download procedure");
         cfgSendNackToCm(CM_ERR_DWNLD_ALREADY_INITIATED);
         free(swMOfferTableDbPtr);
         return;
      }
   }
   /* check if activation is in progress for BSC/EIC */
   actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
      fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
      return;
   }
   /* FIX for Mantis: 6130 start */
   /* check if deletion is in progress for BSC/EIC/BIC/TRX */
   actionInProgress = isDeletionInProgress();
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC");
      cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
      return;
   }
   /* FIX for Mantis: 6130 End */

   /*Check if for the requested sw version, there is an entry in SwM table */
   ret = getSwMTable(&swMTableindex,&swMTableDbPtr);
   if (swMTableDbPtr != NULL)
   {
      LOG_PRINT(LOG_DEBUG,"Software version is already present with platform");
      cfgSendNackToCm(CM_ERR_SW_VERSION_ALREADY_DWNLDED);
      free(swMTableDbPtr);
      return;
   }

   /*Insert record in SwMOffer Table indicating download is in process for 
    * requested sw version */
   receiveMsgPtr->chasisFrameId = chasisFrameId;
   receiveMsgPtr->slotId = slotId;

   if (insertSwMOfferTable(receiveMsgPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"insertSwMOfferTable DB call is getting failed.");
      cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"insertSwMOfferTable Successful");

   /*Send Ack of Set command */
   cfgSendAckToCm();

   /*Send Software Offer Request to Platform */
   LOG_PRINT(LOG_INFO,"Sending Upgrade Offer Request");
   sendSwUpgradeOfferRequest(receiveMsgPtr);
   LOG_PRINT(LOG_INFO,"setEicSwMOfferTableHandler : Exiting function");
}

/******************************* Function  Header*****************************
Function Name : setEicSwMNodeTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles EIC software activation 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setEicSwMNodeTableHandler()
{
   SwMNodeTableApi *receiveMsgPtr = NULL;
   receiveMsgPtr = (SwMNodeTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;

   LOG_PRINT(LOG_INFO,"setEicSwMNodeTableHandler : Entering function");
   LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersionNew);
   LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
   LOG_PRINT(LOG_INFO,"FrameId: %d",receiveMsgPtr->chasisFrameId);
   LOG_PRINT(LOG_INFO,"Slotd: %d",receiveMsgPtr->slotId);
   LOG_PRINT(LOG_INFO,"SwAction: %d",receiveMsgPtr->swAction);

   /*Check Sw Version is in correct format*/
   if (convertInputStringToNumber(receiveMsgPtr->swVersionNew,&tokenNum,
            token,&errCause) == SW_VER_SUCCESS)
   {
      if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
      {
         LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
         cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
         return;
      }         
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
      cfgSendNackToCm(errCause);
      return;
   }

   if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
   {
      performEicSwActivationOperation(receiveMsgPtr);
   }
   LOG_PRINT(LOG_INFO,"setEicSwMNodeTableHandler : Exiting function");
}

/******************************* Function  Header*****************************
Function Name : eicDelSwMTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles EIC software deletion procedure
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void eicDelSwMTableHandler()
{
   SwMTableApi *swMTableDbPtr =NULL;
   SwMTableApi *receiveMsgPtr =NULL;
   SwMNodeTableApi *swMNodeDbPtr =NULL;
   SwMTableIndices SwMTableIndex;
   SwMOfferTableApi *swMOfferBuff = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_U32 eicId[MAX_EIC];
   I_U8 noOfEic = ZERO;
   I_S32 ret = ONE;
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;
   I_U32 index = ZERO;
   I_S32 actionInProgress = I_FALSE;
   I_U32 nodeType = 0, failType =0, swStatus = 0;


   receiveMsgPtr = (SwMTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   /* In case of Eic Activation ActiveICC frameId and SlotId will be used */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);


   SwMTableIndex.nodeType = receiveMsgPtr->nodeType;
   SwMTableIndex.chasisFrameId = chasisFrameId;
   SwMTableIndex.slotId = slotId;
   strcpy(SwMTableIndex.swVersion,receiveMsgPtr->swVersion);

   LOG_PRINT(LOG_INFO,"eicDelSwMTableHandler: Enter function");
   LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
   LOG_PRINT(LOG_INFO,"Received FrameId: %d ",receiveMsgPtr->chasisFrameId);
   LOG_PRINT(LOG_INFO,"Received slotId: %d ",receiveMsgPtr->slotId);

   if (convertInputStringToNumber(receiveMsgPtr->swVersion,&tokenNum,
            token,&errCause) == SW_VER_SUCCESS)
   {
      if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
      {
         LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
         cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
         return;
      }         
   }
   else
   {
      LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
      cfgSendNackToCm(errCause);
      return;
   }

   /* FIX for Mantis: 6130 start */
   /* Check if upgrade Offer is ongoing */
   ret = getallSwMOfferTable( &swMOfferBuff, &outCount, &outSize);
   if ( ret == CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_DEBUG,"Software Offer is on going on BSC");
      free(swMOfferBuff);
      cfgSendNackToCm(CM_ERR_SW_OFFER_IN_PROGRESS);
      return;
   }
   /* check if activation is in progress for BSC/EIC */
   actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx(&nodeType, &swStatus);
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
      fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
      return;
   }
   /* check if deletion is in progress for BSC/EIC/BIC/TRX */
   actionInProgress = isDeletionInProgress();
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC");
      cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
      return;
   }
   /* FIX for Mantis: 6130 end */

   /*Check if for the requested sw version, there is an entry in SwM table*/
   ret = getSwMTable(&SwMTableIndex,&swMTableDbPtr);
   if (swMTableDbPtr == NULL)
   {
      LOG_PRINT(LOG_DEBUG,"Requested software version is not present on BSC");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   else if (swMTableDbPtr->deletionInProgress == I_TRUE)
   {
      LOG_PRINT(LOG_DEBUG,"Deletion is in progress for req sw version");
      if (swMTableDbPtr != NULL)
         free(swMTableDbPtr);
      cfgSendNackToCm(CM_ERR_SW_DEL_ALREADY_IN_PROGRESS);
      return;
   }
   if (swMTableDbPtr != NULL)
      free(swMTableDbPtr);

   /*Check if deletion recieved for EIC*/
   if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_EIC)
   {
      SwMNodeTableIndices sApiSwMNodeTableIndices;
      /* Retrieve eicId from SwmNode Table */
      if (getEicIdFromSwMNodeTable(eicId,&noOfEic) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"getEicId call is getting failed..");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
      }

      /*Retrieve active version and swStatus from SwMNode Table */
      for( index=0; index<noOfEic; index++)
      {
         sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_EIC;
         sApiSwMNodeTableIndices.nodeIdentity = eicId[index];
         sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
         sApiSwMNodeTableIndices.slotId = eicId[index];

         if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeDbPtr) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable Failed..");
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }

         /*Check if requested Sw Version is the Active SwVersion for EIC */ 
         if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionActive) == ZERO)
         {
            LOG_PRINT(LOG_INFO,"Req. Sw Version is currently the Active SwVersion for eicId %d",eicId[index]);
            if (swMNodeDbPtr != NULL)
               free(swMNodeDbPtr);
            cfgSendNackToCm(CM_ERR_ACTIVE_SW);
            return;
         }

         /*Check if requested Sw Version is the Inactive SwVersion for EIC */ 
         if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionInactive) == ZERO)
         {
            LOG_PRINT(LOG_INFO,"Deletion not allowed for Inactive SwVersion for EIC %d",eicId[index]);
            if (swMNodeDbPtr != NULL)
               free(swMNodeDbPtr);
            cfgSendNackToCm(CM_ERR_INACTIVE_SW);
            return;
         }

         /*Check if requested Sw Version is activation in progress */ 
         if (swMNodeDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS)
         {
            LOG_PRINT(LOG_INFO,"Activation is in progress for req. Sw version for eicId %d",eicId[index]);
            if (swMNodeDbPtr != NULL)
               free(swMNodeDbPtr);
            cfgSendNackToCm(CM_ERR_SW_ACT_IN_PROGRESS);
            return;
         }                   
         if (swMNodeDbPtr != NULL)
            free(swMNodeDbPtr);
      }
   }
      /*Update the swAction value as swDelete in SwM Table */
   if (updateDelStatusInSwMTable(SwMTableIndex,I_TRUE) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateDelStatusInSwMTable Failed..");
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateDelStatusInSwMTable Success");
   /*send SET Ack message to OMC */
   cfgSendAckToCm();

   /*Send Delete request to Platform*/
   LOG_PRINT(LOG_INFO,"Sending Deletion request");

   sendSwDeletionRequest(chasisFrameId,slotId,receiveMsgPtr->nodeType,receiveMsgPtr->swVersion);
   LOG_PRINT(LOG_INFO,"eicDelSwMTableHandler: Exit function");
}

/******************************* Function  Header*****************************
   Function Name : eicSwOfferRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Offer respose recieved from OIL
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void eicSwOfferRespHandler()
{
   OamOilCfgSwOfferResp *swOfferRespPtr = NULL;
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoSwDwnldResult *bpmOfferResp = (OamOilCfgInfoSwDwnldResult*)gCfgMsgBuf;
   swOfferRespPtr = (OamOilCfgSwOfferResp*)(&(bpmOfferResp->swMOfferResp));
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmOfferResp->nodeInfo));
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   SwMOfferTableIndices swMOfferTableIndex;
   SwMNodeTableIndices swMNodeTableIndex;
   SwMOfferTableApi *swMOfferBuff = NULL;
   I_U32 eicId[MAX_EIC] ;
   I_U8 noOfEic = ZERO;
   I_U8 string[MAX_STRING_LENGTH];
   I_S32 status = -1;
   I_U8 cpBinaryPath[OAMS_CMD_PARAM_MAX_SIZE];
   I_U32 index = ZERO;
   I_U8 type[4];

   swMOfferTableIndex.nodeType = swOfferRespPtr->nodeType;
   swMOfferTableIndex.chasisFrameId = swOfferRespPtr->frameId;
   swMOfferTableIndex.slotId = swOfferRespPtr->slotId;
   strcpy(swMOfferTableIndex.upgradeVersion,swOfferRespPtr->upgradeVersion);

   LOG_PRINT(LOG_INFO,"eicSwOfferRespHandler : Enter Function");
   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swOfferRespPtr->upgradeVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swOfferRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swOfferRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"SlotId: %d ",swOfferRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"BinaryPath: %s",swOfferRespPtr->binaryPath);
   LOG_PRINT(LOG_INFO,"Result: %d ",swOfferRespPtr->upgradeOfferResult);

   /* Retrieve eicId's from SwmNodeTable */
   if (getEicIdFromSwMNodeTable(eicId, &noOfEic) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getEicIdFromSwMNodeTable call is getting failed..");
      return;
   }
   if (getSwMOfferTable( &swMOfferTableIndex, &swMOfferBuff) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"Upgrade Version mismatch in EIC SW offer request and response");
      LOG_PRINT(LOG_DEBUG,"Version received in offer Response %s",swOfferRespPtr->upgradeVersion );
   }
   else
   {
     free (swMOfferBuff); 
   }

   /*Check if Upgrade Offer is successful */
   if (swOfferRespPtr->upgradeOfferResult == UPGRADE_OFFER_SUCCESSFUL)
   {
      /*Insert a record in SwM Table for the given software version */
      SwMTableApi swMTableBuf;
      swMTableBuf.nodeType = swOfferRespPtr->nodeType;
      swMTableBuf.chasisFrameId = swOfferRespPtr->frameId;
      swMTableBuf.slotId = swOfferRespPtr->slotId;
      strcpy(swMTableBuf.swVersion,swOfferRespPtr->upgradeVersion);

      /*Changes for copying from PP to CP: To be commented after SWMH moved to PP :Start*/
      status = copyReleaseFromPPToCP(swOfferRespPtr->binaryPath,swOfferRespPtr->upgradeVersion,
            swOfferRespPtr->nodeType,cpBinaryPath);
      if (status != I_TRUE)
      {
         sendSwDeletionRequest(swOfferRespPtr->frameId,swOfferRespPtr->slotId,swOfferRespPtr->nodeType,swOfferRespPtr->upgradeVersion);
         return;
      }
      memcpy(swMTableBuf.binaryPath,cpBinaryPath,OAMS_CMD_PARAM_MAX_SIZE);
      /*Changes for copying from PP to CP: End*/

      /*Changes for copying from PP to CP: Uncomment this part of code :Start*/
      /*memcpy(swMTableBuf.binaryPath,swOfferRespPtr->binaryPath,OAMS_CMD_PARAM_MAX_SIZE); */
      /*Changes for copying from PP to CP: End*/
      swMTableBuf.swDownloadCount = 0;
      swMTableBuf.deletionInProgress = I_FALSE;

      /*Delete record from SwMOffer Table */
      if (deleteSwMOfferTable(&swMOfferTableIndex) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferTable DB call is getting failed");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"deleteSwMOfferTable Success");

      if (insertSwMTable(&swMTableBuf) !=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"insertSwMTable DB call is getting failed..");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"insertSwMTable Success");
 
      if (swOfferRespPtr->nodeType == SYS_NODE_TYPE_EIC)
      {
        for( index=0; index<noOfEic; index++ )
        {
           /*Update the upgraded version recieved as downloaded version 
           * in SwMNode Table for both the EIC's*/
           swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
           swMNodeTableIndex.nodeIdentity = eicId[index];
           swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
           swMNodeTableIndex.slotId = eicId[index];
           if (updateVersionDownloadedInSwMNodeTable(swMNodeTableIndex,
                 swOfferRespPtr->upgradeVersion) != CLIB_SUCCESS)
           {
              LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed for eicId: %d",eicId[index]);
              return;
           }
           else
              LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success for eicId %d", eicId[index]);

           if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
               SW_DOWNLOAD_SUCCESS) !=CLIB_SUCCESS)  
           {
               LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
           }
        }//for
      }

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success ALARM: INFO_BPM_SW_DWNLD_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      convertNodeType(type,swOfferRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "Sw Offer for SwVer [%s],NodeType [%s] is Completed at Chasis [%d],Slot [%d]",
            swOfferRespPtr->upgradeVersion,type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   else
   {
      /*Delete record from SwMOffer Table */
      if (deleteSwMOfferTable(&swMOfferTableIndex) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferTable DB call is getting failed");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"deleteSwMOfferTable Success");

      if (swOfferRespPtr->nodeType == SYS_NODE_TYPE_EIC)
      {
        for( index=0; index<noOfEic; index++ )
        {
           /*Update the upgraded version recieved as downloaded version 
           * in SwMNode Table for both the EIC's*/
           swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
           swMNodeTableIndex.nodeIdentity = eicId[index];
           swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
           swMNodeTableIndex.slotId = eicId[index];

           if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
               SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)  
           {
               LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
           }
        }
      }

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending failure ALARM: INFO_BPM_SW_DWNLD_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel =  bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      getStringForSwOfferErrorCause(swOfferRespPtr->upgradeOfferResult,
            swOfferRespPtr->upgradeVersion,swOfferRespPtr->nodeType,string,nodeInfo->chasisFrameId,nodeInfo->slotId);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   } 
   LOG_PRINT(LOG_INFO,"eicSwOfferRespHandler : Exit Function");
}

/******************************* Function  Header*****************************
Function Name : eicSwActivationRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation response recieved from OIL
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void eicSwActivationRespHandler()
{
   OamOilCfgSwActResp *swActRespPtr = NULL;
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoSwActResult *bpmSwAct = (OamOilCfgInfoSwActResult *)gCfgMsgBuf;
   swActRespPtr = (OamOilCfgSwActResp*)(&(bpmSwAct->swMActResp));
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmSwAct->nodeInfo));

   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   I_U8 string[MAX_STRING_LENGTH];
   I_U8 type[4];
   
   LOG_PRINT(LOG_INFO,"Entering eicSwActivationRespHandler");
   LOG_PRINT(LOG_INFO,"Recieved Sw Activation Response");
   LOG_PRINT(LOG_INFO,"Recieved NodeType: %d",swActRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"Recieved SwActVersion: %s",swActRespPtr->actVersion);
   LOG_PRINT(LOG_INFO,"Result: %d ",swActRespPtr->actResult);
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swActRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"SlotId: %d ",swActRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"RevertVersion: %s ",swActRespPtr->revVersion);


   if (swActRespPtr->actResult == ACTIVATION_SUCCESSFUL)
   {

      LOG_PRINT(LOG_INFO,"Preparing Success Alarm: INFO_BPM_SW_ACT_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; /*OAMS_OBJTYPE_EIC;*/
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.key3 = swActRespPtr->nodeType;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swActRespPtr->actResult;
      convertNodeType(type,swActRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,
              "Sw Act for SwVer [%s] is Completed for NodeType [%s],ChasisFrameId [%d],SlotId [%d]",
                swActRespPtr->actVersion,type, nodeInfo->chasisFrameId,nodeInfo->slotId); 
      makeCopyOfActAlarm(&sysAlarmBuff);
      /*cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);*/
   }
   else
   {
      /* Sending Alarm */
      LOG_PRINT(LOG_INFO,"Sending Failure Alarm: INFO_BPM_SW_ACT_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC /*OAMS_OBJTYPE_EIC*/;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.key3 = swActRespPtr->nodeType;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel;
      sysAlarmBuff.sysAlarm.alarmReason = swActRespPtr->actResult;
      getStringForSwActErrorCause(swActRespPtr->nodeType,swActRespPtr->actResult,
                                  swActRespPtr->actVersion,nodeInfo->chasisFrameId,nodeInfo->slotId,string);
      sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      makeCopyOfActAlarm(&sysAlarmBuff);
      /*cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);*/
  }
  //gFirstEicAvailResp = SW_ACTIVATION_IN_PROGRESS;
/*For Mantis 11329*/
  //updateEicDetail = TRUE;
  //sendPresentCardInfoReq();
/*For Mantis 11329*/
  LOG_PRINT(LOG_INFO,"eicSwActivationRespHandler : Exit Function");

} 

/******************************* Function  Header*****************************
   Function Name : eicSwDeletionRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw deletion response recieved from OIL
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void eicSwDeletionRespHandler()
{
   OamOilCfgSwDelResp *swDelRespPtr = NULL;
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoDelResult *bpmSwDel = (OamOilCfgInfoDelResult *)gCfgMsgBuf;
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmSwDel->nodeInfo));
   swDelRespPtr = (OamOilCfgSwDelResp*)(&(bpmSwDel->swMDelResp));

   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMTableIndices sApiSwMTableIndices;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 eicId[MAX_EIC];
   I_U8 noOfEic;
   I_U8 string[MAX_STRING_LENGTH];
   I_U32 index = ZERO;
   I_U8 type[4];

   LOG_PRINT(LOG_INFO,"Recieved Deletion Response");
   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swDelRespPtr->delVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swDelRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swDelRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"SlotId: %d ",swDelRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"Result: %d ",swDelRespPtr->versionDelResult);

   sApiSwMTableIndices.nodeType = swDelRespPtr->nodeType;
   sApiSwMTableIndices.chasisFrameId = swDelRespPtr->frameId;
   sApiSwMTableIndices.slotId = swDelRespPtr->slotId;
   strcpy(sApiSwMTableIndices.swVersion,swDelRespPtr->delVersion);

   if (getEicIdFromSwMNodeTable(eicId, &noOfEic) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getEicId call is getting failed..");
      return;
   }

   if (swDelRespPtr->versionDelResult == DELETE_SUCCESSFUL)
   {
      /*Delete the record of the requested sw version from T2 Table */
      if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"deleteSwMTable Success");

      /*Check if deletion request comes for EIC */
      if (swDelRespPtr->nodeType == SYS_NODE_TYPE_EIC)
      {
         for (index=0; index<noOfEic; index++)
         {
            sApiSwMNodeTableIndices.nodeType = swDelRespPtr->nodeType;
            sApiSwMNodeTableIndices.nodeIdentity = eicId[index];
            sApiSwMNodeTableIndices.chasisFrameId = swDelRespPtr->frameId;
            sApiSwMNodeTableIndices.slotId = eicId[index];
            if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr) != 
                CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable DB call Failed");
               return;
            }

            /*Check if deleted version is Inactive Sw Version */
            if (strcmp(swMNodeTableDbPtr->swVersionInactive,
                      swDelRespPtr->delVersion) == ZERO )
            {
               LOG_PRINT(LOG_DEBUG,"Deletion response recieved for Inactive SwVersion");
               if (swMNodeTableDbPtr != NULL)
                  free(swMNodeTableDbPtr);
               return;
            }

            /*Update Downloaded Version in SwMNode Table if deleted version is downloaded Version */
            if (strcmp(swMNodeTableDbPtr->swVersionDownloaded,
                      swDelRespPtr->delVersion) == ZERO )
            {
               if (updateVersionDownloadedInSwMNodeTable(sApiSwMNodeTableIndices
                     ,"") != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed for eicId: %d", eicId[index] );
                  if (swMNodeTableDbPtr != NULL)
                     free(swMNodeTableDbPtr);
                  return;
               }
               else
                  LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success");
            }
            if (swMNodeTableDbPtr != NULL)
               free(swMNodeTableDbPtr);
         }
      }

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success Alarm: INFO_BPM_DEL_VERSION_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwDel->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwDel->alarmLevel;
      sysAlarmBuff.sysAlarm.alarmReason = swDelRespPtr->versionDelResult;
      convertNodeType(type,swDelRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,
               "Sw Del for SwVer [%s],NodeType [%s] is Completed at ChasisFrameId [%d],SlotId [%d]",
               swDelRespPtr->delVersion,type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
      cfgSendMessage((I_Void *)&sysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   else
   {
      /*Update the swAction value as swDelete in SwM Table */
      if (updateDelStatusInSwMTable(sApiSwMTableIndices,I_FALSE) !=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"updateDelStatusInSwMTable Failed");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"updateDelStatusInSwMTable Success");

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Failure Alarm: INFO_BPM_DEL_VERSION_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwDel->alarmId; 
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwDel->alarmLevel;
      sysAlarmBuff.sysAlarm.alarmReason = swDelRespPtr->versionDelResult;
      getStringForSwDelErrorCause(swDelRespPtr->versionDelResult,
            swDelRespPtr->delVersion,swDelRespPtr->nodeType,string,nodeInfo->chasisFrameId,nodeInfo->slotId);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   } 
}

/******************************* Function  Header*****************************
   Function Name : sendRequestForEicAvailableReleases()
Parameters    : None
Return type   : I_Void
Purpose       : Sends request for Eic available releases present on BSC platform
for EIC
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendRequestForEicAvailableReleases()
{
   OamsCfgOilAvailableReleasesReq  availableReleasesReqBuff;  
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_S32 ret = ZERO;
 
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   availableReleasesReqBuff.frameId = chasisFrameId;
   availableReleasesReqBuff.slotId = slotId;
   availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_EIC;
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ EIC for ChasisFrameId[%d],SlotId[%d]",chasisFrameId,slotId);
   cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
                 sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
                 OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
   gAvailReleaseRspFlag++;
   //LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag.. %d",gAvailReleaseRspFlag);
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented in sendRequestForEicAvailableReleases()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
}

/******************************* Function  Header*****************************
   Function Name : eicAvailableReleasesRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : populate SwM table with releases recieved from platform
for EIC
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void eicAvailableReleasesRespHandler()
{
   OamOilCfgAvailableReleasesResp *availableReleasesRespPtr = NULL;
   OamOilCfgInfoAvailableVersion *bpmAvailVersion = (OamOilCfgInfoAvailableVersion *)gCfgMsgBuf;
   availableReleasesRespPtr = (OamOilCfgAvailableReleasesResp*)(&(bpmAvailVersion->swMAvailResp));
   SwMTableApi swMTableBuff;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 count = 0 ;
   I_U8 eicId[MAX_EIC];
   I_U8 chasisFrameId[MAX_EIC];
   I_U8 noOfEic=0;
   I_U32 index = ZERO,nodeType =0;
	 I_S32 retCode;

   LOG_PRINT(LOG_INFO,"Received AvailableReleasesResp for NodeType[%d], ChasisFrameId[%d], SlotId[%d]",availableReleasesRespPtr->nodeType,availableReleasesRespPtr->frameId,availableReleasesRespPtr->slotId);

   if (getEicIdChasisId(eicId, chasisFrameId, &noOfEic) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getEicIdChasisId call is getting failed.."); 
      return;
   }

   gAvailReleaseRspFlag--;
   //LOG_PRINT(DEBUG,"Val of gAvailReleaseRspFlag %d",gAvailReleaseRspFlag);
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) decremented in eicAvailableReleasesRespHandler()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS


   if (availableReleasesRespPtr->numVersion == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"No version present on the BSC Card for NodeType: %d",
            availableReleasesRespPtr->nodeType );
   }

   if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_EIC  && availableReleasesRespPtr->availVersionResult == OPERATION_SUCCESS)
   {
      nodeType = availableReleasesRespPtr->nodeType;

      if(deleteDataForNodeTypeFromSwMTable(&nodeType) != CLIB_SUCCESS)
      {
         LOG_PRINT(DEBUG,"deleteDataForNodeTypeFromSwMTable failed");
      }
      for (count = 0;count < 3;count++)
      { 
         LOG_PRINT(INFO,"Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[count]);    
         if (strlen(availableReleasesRespPtr->availSwVersions[count]) == ZERO)
         {
            LOG_PRINT(INFO,"No EIC release present for count: %d",count + 1);    
         }
         else
         {
            swMTableBuff.nodeType = availableReleasesRespPtr->nodeType;
            swMTableBuff.chasisFrameId = availableReleasesRespPtr->frameId;
            swMTableBuff.slotId = availableReleasesRespPtr->slotId;
            strcpy(swMTableBuff.swVersion,
                  availableReleasesRespPtr->availSwVersions[count]);
            memcpy(swMTableBuff.binaryPath,availableReleasesRespPtr->availSwBinaryPath[count],
                  OAMS_CMD_PARAM_MAX_SIZE); 
            swMTableBuff.swDownloadCount = ZERO;
            swMTableBuff.deletionInProgress = I_FALSE;
           /*Not Required at BSC-DB/OMC 27 Sept 2016*/
            /*if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
            {
               if ( updateSwMTable(&swMTableBuff ) != CLIB_SUCCESS )
                  LOG_PRINT(LOG_MAJOR,"updateSwMTable DB call is getting failed..");
            }
            else
               LOG_PRINT(LOG_INFO,"insertSwMTable Successful");*/           
           /*Not Required at BSC-DB/OMC 27 Sept 2016*/
         }

      }

      LOG_PRINT(LOG_INFO,"no Of EIC  = %d",noOfEic);           
      for( index=0; index<noOfEic; index++)
      {
         sApiSwMNodeTableIndices.nodeIdentity = eicId[index];
         sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
         sApiSwMNodeTableIndices.slotId = eicId[index];
         sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
         #if 0
         if ( gFirstEicAvailResp == FALSE )
         {
            if (updateVersionDownloadedInSwMNodeTable( sApiSwMNodeTableIndices,
                   availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR,"updateVersionDownloadedInSwMNodeTable Failed for eicId[%d]",availableReleasesRespPtr->slotId);
            }
            else
               LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success"); 

            /*if ( index == noOfEic-1)
               gFirstEicAvailResp = TRUE;*/
         }
         #endif
					LOG_PRINT(INFO,"updating Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[0]);
					LOG_PRINT(INFO,"updating Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[1]);
					LOG_PRINT(INFO,"updating Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[2]);
         if (updateVersionActiveInactiveDnldedInSwMNodeTable(
            sApiSwMNodeTableIndices,
            availableReleasesRespPtr->availSwVersions[0],
            availableReleasesRespPtr->availSwVersions[1],
            availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"updateVersionActiveInactiveDnldedInSwMNodeTable Failed for eicId[%d]",availableReleasesRespPtr->slotId);
         }
         else
            LOG_PRINT(LOG_INFO,"updateVersionActiveInactiveDnldedInSwMNodeTable Success");
         //gFirstEicAvailResp = FALSE;
      }

      if ( gCfgActAlarmBuf != NULL )
      { 
         sendActivationAlarm(availableReleasesRespPtr);
      }
   }
   else if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_EIC  && availableReleasesRespPtr->availVersionResult != OPERATION_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR,"Available Release Query Response returned Failure");
   }
   sendUpgradeAlarm();
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) gCfgState(%d) eicAvailableReleasesRespHandler()",gAvailReleaseRspFlag,gCfgState); //CLOUD TMP PRINTS
   if (gAvailReleaseRspFlag == ZERO && gCfgState == CFG_BPM_SW_QUERY)
   {
      goToReadyState();
   }

}

/******************************* Function  Header*****************************
Function Name : performEicSwActivationOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles EIC software activation procedure
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void performEicSwActivationOperation(SwMNodeTableApi *receiveMsgPtr)
{
   SwMTableApi *swMTableDbPtr = NULL;
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMNodeTableIndices swMNodeTableIndex;
   SwMTableIndices swMTableIndex;
   OamsCfgOilSwActReq swActBuff;
   SwMOfferTableApi *swMOfferBuff = NULL;
   I_U32 outCount = ZERO;
   I_U8 count = ZERO;
   I_U16 outSize = ZERO;
   I_S32 ret = ONE;
   I_U32 bscId = ZERO;
   I_U32 eicId[MAX_EIC];
   I_U8 noOfEic = ZERO;
   I_U32 index = ZERO;
   I_S32 actionInProgress = I_FALSE;
   I_U32 swStatus[TWO]={ZERO};
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_U32 nodeType = 0;
   I_U32 failType = 0;
   I_U32 swStatus_o = 0;

   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: ChasisFrameId[%d] SlotId[%d]",chasisFrameId,slotId);


   swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
   swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
   swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMNodeTableIndex.slotId = receiveMsgPtr->slotId;
   swMTableIndex.nodeType = receiveMsgPtr->nodeType;
   swMTableIndex.chasisFrameId = chasisFrameId;
   swMTableIndex.slotId = slotId;
   strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);

   LOG_PRINT(LOG_INFO,"performEicSwActivationOperation : Entering function");

   /*Check if swAction is SW_ACTIVATE */
   if (receiveMsgPtr->swAction != SW_ACTIVATE)
   {
      LOG_PRINT(LOG_DEBUG,"Invalid request recieved for EIC");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
      return;
   }
   LOG_PRINT(LOG_INFO,"Recieved EIC Sw Activation Request");

   if (gBssState == unlocked)
   {
      LOG_PRINT(LOG_DEBUG,"BSS is in UnLocked state");
      cfgSendNackToCm(CM_ERR_BSS_UNLOCKED);
      return;
   }
   else if (gBssState == unlockInProgress)
   {
      LOG_PRINT(LOG_DEBUG,"BSS is UnLock in Progress state");
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
      return;
   }
   else if (gBssState == lockInProgress)
   {
      LOG_PRINT(LOG_DEBUG,"BSS is Lock in Progress state");
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"BSS is in Locked state");

   /* Check if upgrade Offer is ongoing */
   ret = getallSwMOfferTable( &swMOfferBuff, &outCount, &outSize);
   if ( ret == CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_DEBUG,"Software Offer is on going on BSC");
      free(swMOfferBuff);
      cfgSendNackToCm(CM_ERR_SW_OFFER_IN_PROGRESS);
      return;
   }
   /* FIX for Mantis: 6130 start */
   /* check if deletion is in progress for BSC/EIC/BIC/TRX */
   actionInProgress = isDeletionInProgress();
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC");
      cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
      return;
   }
   /* FIX for Mantis: 6130 End */
 
   /*Check if requested sw version of EIC is present in T3 table */
   ret = getSwMTable(&swMTableIndex,&swMTableDbPtr);
   if (swMTableDbPtr == NULL)
   {
      LOG_PRINT(LOG_DEBUG,"Software version is not present with platform");
      cfgSendNackToCm(CM_ERR_VERSION_NOT_FOUND);
      return;
   }
   /*Check if deletion is in progress for requested sw version in SwMTable*/ 
   else if (swMTableDbPtr->deletionInProgress == I_TRUE)
   {
      LOG_PRINT(LOG_DEBUG,"Delete is in progress for the required Sw version");
      if (swMTableDbPtr != NULL)
         free(swMTableDbPtr);
      cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
      return;
   }

   if (swMTableDbPtr != NULL)
      free(swMTableDbPtr);
   /*Check if for the nodeId and nodeType, there is a record in T2 table */
   ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
   if (swMNodeTableDbPtr == NULL)
   {
      LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
            receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   /*Check if req Sw version is not active SwVersion of EIC in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionActive,receiveMsgPtr->swVersionNew) == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"Requested Sw version is the Active SwVersion of EIC");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      cfgSendNackToCm(CM_ERR_VERSION_ALREADY_ACTIVATE);
      return;
   }
   /*Check if req Sw version is present in inactive/downloaded SwVersion list
    *  of EIC in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionInactive,receiveMsgPtr->swVersionNew) != ZERO && 
         strcmp(swMNodeTableDbPtr->swVersionDownloaded,receiveMsgPtr->swVersionNew) != ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"Requested Sw version is not present in inactive/downloaded SwVersion List of EIC");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      cfgSendNackToCm(CM_ERR_VERSION_NOT_AVAILABLE_FOR_ACT);
      return;
   }
   /*Check if in SwMNode table,the status is NOT swDownloadInProgress or 
    * swActivationInProgress */
   else if (swMNodeTableDbPtr->swStatus == SW_DOWNLOAD_IN_PROGRESS || 
         swMNodeTableDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS )
   {
      LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress for the node");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
   }
   if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);

   /* check if activation is in progress for BSC/EIC */
   actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus_o );
   if ( actionInProgress == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
      fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
      return;
   }
   #if 0
   if (getBscId(&bscId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
      bscId = 0;
   }
   /* To retrieve SwStatus From SwmNodeTable for NODE_TYPE_BSC */
   if( getEicSwStatusFromSwMNodeTable(SYS_NODE_TYPE_BSC, swStatus, &count) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable call is getting failed.."); 
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   for ( index=0; index<count; index++)
   { 
      if(swStatus[index] == SW_ACTIVATION_IN_PROGRESS)
      {
         LOG_PRINT(LOG_DEBUG,"Activation is in progress for BSC ");
         cfgSendNackToCm(CM_ERR_SW_BSC_ACT_IN_PROGRESS);
         return;
      }
   }

   /*Check if in SwMNodeTable, the status of the other EIC is not swActivationInProgress */ 
   /* Retrieve eicId's from eicCardInfoTable */
   if (getEicIdFromSwMNodeTable(eicId, &noOfEic) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getEicId call is getting failed.."); 
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   for ( index=0; index<noOfEic; index++)
   { 
      if(eicId[index] == receiveMsgPtr->nodeIdentity)
      {
         continue;
      }
      else
      {
         swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
         swMNodeTableIndex.nodeIdentity = eicId[index];
         swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
         swMNodeTableIndex.slotId = eicId[index];
         ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
         if (swMNodeTableDbPtr == NULL)
         {
            LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
            swMNodeTableIndex.nodeType,swMNodeTableIndex.nodeIdentity);
            cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
            return;
         }
         if (swMNodeTableDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS )
         {
            LOG_PRINT(LOG_DEBUG,"Activation is in progress for Peer EIC Card");
            if (swMNodeTableDbPtr != NULL)
               free(swMNodeTableDbPtr);
            cfgSendNackToCm(CM_ERR_SW_EIC_ACT_IN_PROGRESS);
            return;
         }

      }
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      
   }
   for ( index=0; index<noOfEic; index++)
   { 
      swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
      swMNodeTableIndex.nodeIdentity = eicId[index];
      swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
      swMNodeTableIndex.slotId = eicId[index];
    /*Update record in SwMNode table for both the EIC's indicating sw activation is in progress */
      if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
          SW_ACTIVATION_IN_PROGRESS,SW_ACTIVATE,receiveMsgPtr->swVersionNew) != 
          CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed for eicId: %d", eicId[index]);
         cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");
   }

   #endif
   /*send SET Ack message to OMC */
   cfgSendAckToCm();

   /*Send the EIC software activation request to Platform */
   LOG_PRINT(LOG_INFO,"Sending EIC Sw Activation request");
   /* In case of Eic Activation ActiveICC frameId and SlotId will be used */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: ChasisFrameId[%d] SlotId[%d]",chasisFrameId,slotId);

   swActBuff.frameId = chasisFrameId;
   swActBuff.slotId = slotId;
   swActBuff.nodeType = receiveMsgPtr->nodeType;
   swActBuff.cardState = ZERO; /* No need to set cardState as OOS */
   strcpy(swActBuff.actVersion,receiveMsgPtr->swVersionNew);
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SW_ACT_REQ to Oil");
   cfgSendMessage((I_Void *)&swActBuff, sizeof(OamsCfgOilSwActReq), ENT_OAM_OIL,
         OAMS_CFG_OIL_SW_ACT_REQ , 0);
   LOG_PRINT(LOG_INFO,"performEicSwActivationOperation : Exiting function");
}

/******************************* Function  Header*****************************
   Function Name : cfgInitEicSwMNodeTable()
Parameters    : None
Return type   : I_Void
Purpose       : Initialize SwMNode Table with the EIC present in the 
system.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void cfgInitEicSwMNodeTable()
{
   SwMNodeTableApi swMNodeTableBuf;
   SwMNodeTableIndices swmNodeTableIndices;
   SwMNodeTableApi *swMNodeTableData = NULL;
   I_U8 eicId[MAX_EIC];
   I_U8 chasisFrameId[MAX_EIC];
   I_U8 noOfEic=ZERO;
   I_U32 idx = ZERO;
   I_U8 slotId;
   I_S32 ret = ZERO;

   /*Retrieve EicIds from EicCardInfoTable */
   if (  getEicIdChasisId( eicId, chasisFrameId, &noOfEic ) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_DEBUG,"No row present in eicCardInfoTable");
      return;
   }

   /*Insert Two record's in SwMNode table for EIC */
   for(idx=0; idx<noOfEic; idx++)
   {   
      /* changes for EIC card eject case start */
      swmNodeTableIndices.nodeType = SYS_NODE_TYPE_EIC;
      swmNodeTableIndices.nodeIdentity = eicId[idx];
      swmNodeTableIndices.chasisFrameId = chasisFrameId[idx];
      swmNodeTableIndices.slotId = eicId[idx];
       
      LOG_PRINT(DEBUG,"For Eic going to get frameId:%d, slotId:%d",
          swmNodeTableIndices.chasisFrameId, swmNodeTableIndices.slotId);
      if ( getSwMNodeTable( &swmNodeTableIndices, &swMNodeTableData) == CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_INFO,"cfgInitEicSwMNodeTable: NodeType: %d and NodeIdentity: %d already exists in SwMNodeTable",swmNodeTableIndices.nodeType, swmNodeTableIndices.nodeIdentity);
         free(swMNodeTableData);
         continue;
      }
      /* changes for EIC card eject case end */
      swMNodeTableBuf.nodeType = SYS_NODE_TYPE_EIC;
      swMNodeTableBuf.nodeIdentity = eicId[idx];
      swMNodeTableBuf.chasisFrameId = chasisFrameId[idx];
      swMNodeTableBuf.slotId = eicId[idx];
      swMNodeTableBuf.e1Num = E1_INVALID;
      swMNodeTableBuf.lapdTs = TS_INVALID;
      strcpy(swMNodeTableBuf.swVersionActive,"");
      strcpy(swMNodeTableBuf.swVersionInactive,"");
      strcpy(swMNodeTableBuf.swVersionDownloaded,"");
      strcpy(swMNodeTableBuf.swVersionNew,"");
      swMNodeTableBuf.swAction = SW_NO_ACTION;
      swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
      LOG_PRINT(DEBUG,"For Eic going to enter frameId:%d, slotId:%d",
          swMNodeTableBuf.chasisFrameId, swMNodeTableBuf.slotId);
      /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
      /*if (insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed in function cfgInitEicSwMNodeTable");
         return;
      }
      else
      {
         LOG_PRINT(LOG_INFO,"insertSwMNodeTable Successfull");
      }*/
      /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
   }
}

/******************************* Function  Header*****************************
   Function Name : getStringForSwActErrorCause()
Parameters    : I_U32 nodeType, I_U16 result,I_U8 *swVersion,I_U32 nodeId,I_U8 *string
Return type   : I_Void
Purpose       : Return a string corresponding to the failure cause for 
software activation error causes
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void getStringForSwActErrorCause(I_U32 nodeType,I_U16 result,I_U8 *swVersion,I_U8 chasisFrameId,I_U8 slotId,I_U8 *string)
{
   I_U8 type[4];
   convertNodeType(type,nodeType);
   switch(result)
   {
      case UNABLE_TO_ACTIVATE:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Unable to Activate",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_VERSION_NOT_PRESENT:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Version Not Present",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_VERSION_ALREADY_RUNNING:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Version Running",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_CONNECTING_UA_CP:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Error Connecting CP ",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_CONNECTING_UA_PP:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Error Connecting PP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_FILE_TRANSFER_PP:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Error File Transfer PP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_FILE_TRANSFER_CP:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Error File Transfer CP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_ACTIVATION_FAILURE:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Activation Failure",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_REVERT_FAILURE:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Revert Failure",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_ACTIVATION_IN_PROGRESS:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Activation in Progress",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_UNABLE_TO_SEND_BINARY_TO_CP:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Unable to Send Binary to CP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_UNABLE_TO_SEND_BINARY_TO_PP:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Unable to Send Binary to PP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_CARDSTATE_INVALID:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid Card State",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_BPM_INTERNAL :
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Internal Error occurred",
               swVersion,type,chasisFrameId,slotId);       
         break;
      default:
         sprintf(string,"Sw Act Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] with Invalid cause value",
               swVersion,type,chasisFrameId,slotId);       
         break;
   }
}

/******************************* Function  Header*****************************
Function Name : sendUpgradeAlarm()
Parameters    : I_Void  
Return type   : I_Void
Purpose       :Sends n a string corresponding to the failure cause for 
software activation error causes
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendUpgradeAlarm()
{
   OamOilCfgInfoUpgradeOffer *bpmOfferResp;
   OamOilCfgEicConnectLoad *bpmEicConnect;
   OamOilCfgInfoSwAct *bpmSwAct;
   OamOilCfgAvailableReleasesResp *availableReleasesRespPtr = NULL;
   OamOilCfgInfoAvailableVersion *bpmAvailVersion;
   OamOilCfgNodeInfo *nodeInfo;
   OamOilCfgEicEnableDisableLoad *bpmEicEnable;
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   SwMNodeTableIndices swMNodeTableIndex;
   I_U32 dspId[MAX_DSP] ;
   I_U8 noOfDsp = ZERO;
   I_U32 index = ZERO;
   I_U8 noOfEic = ZERO;
   I_U32 eicId[MAX_EIC] ;
   I_U32 bscId = ZERO;

   I_U8 type[4];
   
   LOG_PRINT(LOG_INFO," Entering function sendUpgradeAlarm.. ");
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case OAM_OIL_CFG_INFO_SW_UPGRADE_OFFER:
         {
             bpmOfferResp = (OamOilCfgInfoUpgradeOffer*)gCfgMsgBuf;
             nodeInfo = (OamOilCfgNodeInfo*)(&(bpmOfferResp->nodeInfo));

             LOG_PRINT(LOG_INFO,"Sending Alarm: INFO_BPM_SW_UPGRADE_OFFER");
             sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId;
             sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
             sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
             sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
             sysAlarmBuff.sysAlarm.alarmLevel = bpmOfferResp->alarmLevel;
             convertNodeType(type,nodeInfo->nodeType);
             sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
                       "Sw Offer for NodeType [%s] is in Progress at ChasisFrameId [%d],SlotId [%d]",
                       type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
             /*Mantis Fix: 11303 Starts*/
             FillObjTypeFromNodeType(nodeInfo->nodeType,sysAlarmBuff.sysAlarm.info3);
             /*Mantis Fix: 11303 Ends*/
             cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         }
         break; 
      case OAM_OIL_CFG_INFO_SW_ACT_STARTED: 
         {
             bpmSwAct = (OamOilCfgInfoSwAct *)gCfgMsgBuf;
             nodeInfo = (OamOilCfgNodeInfo*)(&(bpmSwAct->nodeInfo));

             LOG_PRINT(LOG_INFO,"Sending Alarm: INFO_BPM_SW_ACT_STARTED");
             sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId;
             sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel;

             if( nodeInfo->nodeType == SYS_NODE_TYPE_EIC)
             {
                sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; /*OAMS_OBJTYPE_EIC;*/
                sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
                sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
                convertNodeType(type,nodeInfo->nodeType);
                sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Sw Act for NodeType [%s] is Started at ChasisFrameId [%d],SlotId [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId);
                /*Mantis Fix: 11303 Starts*/
                FillObjTypeFromNodeType(nodeInfo->nodeType,sysAlarmBuff.sysAlarm.info3);
                /*Mantis Fix: 11303 Ends*/
                cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                                  ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                if (getEicIdFromSwMNodeTable(eicId, &noOfEic) != CLIB_SUCCESS)
                {
                   LOG_PRINT(LOG_CRITICAL,"getEicIdFromSwMNodeTable call is getting failed..");
                   return;
                }
                for( index=0; index<noOfEic; index++ )
                {
                   /*Update the upgraded version recieved as downloaded version 
                   * in SwMNode Table for both the EIC's*/
                   swMNodeTableIndex.nodeType = nodeInfo->nodeType;
                   swMNodeTableIndex.nodeIdentity = eicId[index];
                   swMNodeTableIndex.chasisFrameId = nodeInfo->chasisFrameId;
                   swMNodeTableIndex.slotId = eicId[index];
                   if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                       SW_ACTIVATION_IN_PROGRESS) !=CLIB_SUCCESS)  
                   {
                       LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
                   }
                }//for

             }//NODETYPE_EIC
             if( nodeInfo->nodeType == SYS_NODE_TYPE_DSP)
             {
               LOG_PRINT(LOG_INFO,"nodeInfo->slotId  = %d",nodeInfo->slotId);
               if(nodeInfo->slotId == 3 || nodeInfo->slotId == 4)
               { 
                 sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; /*OAMS_OBJTYPE_DSP;*/
                 sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
                 sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
                 convertNodeType(type,nodeInfo->nodeType);
                 sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Sw Act for NodeType [%s] is Started at ChasisFrameId [%d],SlotId [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId);
                 /*Mantis Fix: 11303 Starts*/
                 FillObjTypeFromNodeType(nodeInfo->nodeType,sysAlarmBuff.sysAlarm.info3);
                 /*Mantis Fix: 11303 Ends*/
                 cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                 if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
                 {
                   LOG_PRINT(LOG_CRITICAL,"getDspIdFromSwMNodeTable call is getting failed..");
                   return;
                 }
                 for( index=0; index<noOfDsp; index++ )
                 {
                   /*Update the upgraded version recieved as downloaded version 
                    * in SwMNode Table for all the Dsp's*/
                   swMNodeTableIndex.nodeType = nodeInfo->nodeType;
                   swMNodeTableIndex.nodeIdentity = dspId[index];
                   swMNodeTableIndex.chasisFrameId = nodeInfo->chasisFrameId;
                   //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;
                   if (index > 1)
                   {
                     break;
                   }

                   if(dspId[index] == 0)
                   {
                     swMNodeTableIndex.slotId = 3;
                   }			 
                   if(dspId[index] == 1)
                   {
                     swMNodeTableIndex.slotId = 4;
                   }			 

                   if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                         SW_ACTIVATION_IN_PROGRESS) !=CLIB_SUCCESS)  
                   {
                     LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
                   }
                 }//for
               }//if icc dsp 
               else if(nodeInfo->slotId == 5 || nodeInfo->slotId == 6)
               { 
                 sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_EIC; /*OAMS_OBJTYPE_DSP;*/
                 sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
                 sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
                 convertNodeType(type,nodeInfo->nodeType);
                 sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Sw Act for NodeType [%s] is Started at ChasisFrameId [%d],SlotId [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId);
                 /*Mantis Fix: 11303 Starts*/
                 FillObjTypeFromNodeType(nodeInfo->nodeType,sysAlarmBuff.sysAlarm.info3);
                 /*Mantis Fix: 11303 Ends*/
                 cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                 if (getDspIdFromSwMNodeTable(dspId, &noOfDsp) != CLIB_SUCCESS)
                 {
                   LOG_PRINT(LOG_CRITICAL,"getDspIdFromSwMNodeTable call is getting failed..");
                   return;
                 }
                 for( index=0; index<noOfDsp; index++ )
                 {
                   /*Update the upgraded version recieved as downloaded version 
                    * in SwMNode Table for all the Dsp's*/
                   swMNodeTableIndex.nodeType = nodeInfo->nodeType;
                   swMNodeTableIndex.nodeIdentity = dspId[index];
                   swMNodeTableIndex.chasisFrameId = nodeInfo->chasisFrameId;
                   //   swMNodeTableIndex.slotId = swOfferRespPtr->slotId;
                   if (index < 2)
                   {
                     continue;
                   }

                   if((dspId[index] == 2) || (dspId[index] == 3))
                   {
                     swMNodeTableIndex.slotId = 5;
                   }			 
                   if((dspId[index] == 4) || (dspId[index] == 5))
                   {
                     swMNodeTableIndex.slotId = 6;
                   }			 

                   if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                         SW_ACTIVATION_IN_PROGRESS) !=CLIB_SUCCESS)  
                   {
                     LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
                   }
                 }//for
               }//if eic dsp 

             }//NODETYPE_DSP
             if( nodeInfo->nodeType == SYS_NODE_TYPE_BSC)
             {
                sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
                sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
                sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
                convertNodeType(type,nodeInfo->nodeType);
                sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Sw Act for NodeType [%s] is Started at ChasisFrameId [%d],SlotId [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId);
                /*Mantis Fix: 11303 Starts*/
                FillObjTypeFromNodeType(nodeInfo->nodeType,sysAlarmBuff.sysAlarm.info3);
                /*Mantis Fix: 11303 Ends*/
                cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                /* Retrieve bscId from BSS Table */
                if (getBscId(&bscId) != CLIB_SUCCESS)
                {
                   LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
                   return;
                }
                swMNodeTableIndex.nodeType = nodeInfo->nodeType;
                swMNodeTableIndex.nodeIdentity = bscId;
                swMNodeTableIndex.chasisFrameId =  nodeInfo->chasisFrameId;
                swMNodeTableIndex.slotId = nodeInfo->slotId;
                if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
                    SW_ACTIVATION_IN_PROGRESS) !=CLIB_SUCCESS)  
                {
                    LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
                }
            }//NODETYPE_BSC
        }
      break; 
      case OAM_OIL_CFG_INFO_AVAILABLE_VERSION:
         {
            bpmAvailVersion = (OamOilCfgInfoAvailableVersion *)gCfgMsgBuf;
            nodeInfo = (OamOilCfgNodeInfo*)(&(bpmAvailVersion->nodeInfo));
            availableReleasesRespPtr = (OamOilCfgAvailableReleasesResp*)(&(bpmAvailVersion->swMAvailResp));
            LOG_PRINT(LOG_INFO,"1U: NOT Sending Alarm: INFO_BPM_AVAILABLE_VERSION"); //1U Specific Changes
            sysAlarmBuff.sysAlarm.sysalarmId = bpmAvailVersion->alarmId;
            sysAlarmBuff.sysAlarm.alarmLevel = bpmAvailVersion->alarmLevel; 
            FillObjTypeFromNodeType(nodeInfo->nodeType,sysAlarmBuff.sysAlarm.info3);
           // sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
            sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId;
            sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId;
            sysAlarmBuff.sysAlarm.key3 = nodeInfo->nodeType;
            convertNodeType(type,nodeInfo->nodeType);
            if ( availableReleasesRespPtr->availVersionResult == OPERATION_SUCCESS )
            { 
               if(availableReleasesRespPtr->numVersion > 0)
               {
                  sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Version Available for NodeType [%s] on ChasisFrameId [%d],SlotId [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
               }
               else
               {
                  sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Version not Available for NodeType [%s] on ChasisFrameId [%d],SlotId [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
               }
            }
            else 
            {
                sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Query Available Version Failed for NodeType [%s],ChasisFrameId [%d],SlotId [%d],Cause [%d]",type,nodeInfo->chasisFrameId,nodeInfo->slotId,availableReleasesRespPtr->availVersionResult); 

            }  
            /*cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);*/ //1U Specific Changes
         }
         break;
      case OAM_OIL_CFG_INFO_EIC_CONNECT:
         {
            bpmEicConnect = (OamOilCfgEicConnectLoad *)gCfgMsgBuf;

            LOG_PRINT(LOG_INFO,"Sending Alarm: INFO_BPM_EIC_CONNECTED");
            sysAlarmBuff.sysAlarm.sysalarmId = bpmEicConnect->alarmId;
            sysAlarmBuff.sysAlarm.alarmLevel = bpmEicConnect->alarmLevel;
            sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_EIC;
            sysAlarmBuff.sysAlarm.key1 = bpmEicConnect->chasisFrameId;
            sysAlarmBuff.sysAlarm.key2 = bpmEicConnect->slotId;
            sysAlarmBuff.sysAlarm.infoStrLen = bpmEicConnect->infoStrLen;
            strcpy ( sysAlarmBuff.sysAlarm.infoString, bpmEicConnect->infoString ); 
            cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
          }
          break; 
      case OAM_OIL_CFG_INFO_EIC_ENABLE_DISABLE:
         {
            bpmEicEnable = (OamOilCfgEicEnableDisableLoad *)gCfgMsgBuf;

            LOG_PRINT(LOG_INFO,"Sending Alarm: INFO_BPM_EIC_ENABLE/DISABLE alarmId[%d]",bpmEicEnable->alarmId);
            sysAlarmBuff.sysAlarm.sysalarmId = bpmEicEnable->alarmId;
            sysAlarmBuff.sysAlarm.alarmLevel = bpmEicEnable->alarmLevel;
            sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_EIC;
            sysAlarmBuff.sysAlarm.key1 = bpmEicEnable->chasisFrameId;
            sysAlarmBuff.sysAlarm.key2 = bpmEicEnable->slotId;
            sysAlarmBuff.sysAlarm.infoStrLen = bpmEicEnable->infoStrLen;
            strcpy ( sysAlarmBuff.sysAlarm.infoString, bpmEicEnable->infoString ); 
            cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                                ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
          }
          break; 

   }

   LOG_PRINT(LOG_INFO," Exiting function sendUpgradeAlarm.. ");
}
/******************************* Function  Header*****************************
   Function Name : getStringForSwOfferErrorCause()
Parameters    : I_U16 result,I_U8 *swVersion,I_U32 nodeType,I_U8 *string I_U8 chasisFrameId
                I_U8 slotId 
Return type   : I_Void
Purpose       : Return a string corresponding to the failure cause for 
software offer error causes
Other Note    : Modified For BSC CS4.0
 *****************************************************************************/

I_Void getStringForSwOfferErrorCause(I_U16 result,I_U8 *swVersion,I_U32 nodeType,I_U8 *string, I_U8 chasisFrameId, I_U8 slotId)
{
   I_U8 type[4];
   convertNodeType(type,nodeType);
   switch(result)
   {
      case ERROR_INVALID_PARAM :
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Error: Invalid Param",
               swVersion,type,chasisFrameId,slotId);       
      break; 
      case ERROR_WRITING_TO_FLASH :
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Error Writing to Flash",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_AUTHENTICATION_FAILURE:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Authentication Failure",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_UNABLE_TO_OPEN_FTP:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Unable to Open Ftp",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_OFFERED_VERSION_EXISTS: 
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Offered Version Exists",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_TRANSFER_FAILED:
         sprintf(string,"Sw Offer Failed for SwVern [%s],NodeType [%s],Chasis [%d],Slot [%d] as Transfer Failed",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_INCOMPLETE_TREE:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Incomplete Tree",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_INVALID_NODE_TYPE:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid NodeType",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_HARDWARE_VERSION_MISMATCH:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Hardware Version Mismatch",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_PEER_SIDE:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as PeerSide Error",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_BADLINK:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Badlink",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_OTHER:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Other Error",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_TAR_AND_INFOFILE_MISMATCH:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Tar and InfoFile Mismatch",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_CHECKSUM_FAILED:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Checksum Failed",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_SPACE_UNAVAILABLE:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Space Unavailable",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_COMPATIBILITY_MATRIX:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Compatability Matrix",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_FILE_NOT_PRESENT:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as File Not Present",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_DOWNLOAD_IN_PROGRESS:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Download in Progress",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_MAX_DOWNLOAD_LIMIT:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Max Download Limit",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_OLDER_VERSION:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Older Version Error",
               swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_EIC_INTERNAL_SYNC_IN_PROGRESS:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Eic Internal Sync in progress"               ,swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVALID_SIZE:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid size received",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_CARDSTATE_INVALID:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid Card State",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVALID_FRAMEID:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid FrameId",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVALID_NAME_PASSWD:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid name password",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVALID_DSPID:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid DspId",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVALID_IP :
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid IP",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVAL_NUM_PORTS :
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid NumPorts",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_DOWNLOAD_VERSION_ALREADY_EXISTS :
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as download version already exists",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_INVALID_VERSION :
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid vesrion",swVersion,type,chasisFrameId,slotId);       
         break;    
      case ERROR_FTP_MISCELLANEOUS_FAILURE :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: Ftp Miscellaneous failure",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_NO_CREDENTIALS_CACHE_FOUND :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: No Credential Cache Found",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_INITIALIZING_CONTEXT :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: Initializing context failed",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_CONNECT_NO_ROUTE_TO_HOST :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: No Route To Host",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_CONNECT_CONNECTION_REFUSED :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: Connection Refused",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_NO_SUCH_FILE_OR_DIRECTORY :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: No such File or Directory",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_COMMAND_NOT_FOUND :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: FTP command Not Found",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_CONNECT_CONNECTION_TIMED_OUT :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: Connect Connection Timed Out",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_CONNECT_NETWORK_IS_UNREACHABLE :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: Network is Unreachable",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_GSSAPI_AUTHENTICATION_FAILED :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: GSSAPI Authentication Failed",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_530_LOGIN_INCORRECT :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: 530 Authentication Failed",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_550_FAILED_TO_OPEN_FILE :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: 550 failed to open file",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_530_PLEASE_LOGIN_WITH_USER_AND_PASS :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: 530 Please Login With Username and Password",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_NO_SPACE_LEFT_ON_DEVICE :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: No Space Left on Device",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_TERMINATED :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: Ftp Terminated",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_FILE_NOT_PRESENT :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: File Not Present",swVersion,type,chasisFrameId,slotId);       
      break;   
      case ERROR_FTP_530_AUTHENTICATION_FAILED :
         sprintf(string,"Sw Offer Failed for SwVer[%s],NodeType[%s],Chasis[%d],Slot[%d] as Ftp: 530 Authentication Failed",swVersion,type,chasisFrameId,slotId);       
      break;   
      default:
         sprintf(string,"Sw Offer Failed for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] With Invalid Cause Value",
               swVersion,type,chasisFrameId,slotId);       
         break;    
   }
}

/******************************* Function  Header*****************************
Function Name : getStringForSwDelErrorCause()
Parameters    : I_U16 result,I_U8 *swVersion,I_U32 nodeType,I_U8 *string 
                I_U8 chasisFrameId, I_U8 slotId
Return type   : I_Void
Purpose       : Return a string corresponding to the failure cause for 
software deletion error causes
Other Note    : Added For BSC CS3.0
 *****************************************************************************/

I_Void getStringForSwDelErrorCause(I_U16 result,I_U8 *swVersion,I_U32 nodeType,I_U8 *string, I_U8 chasisFrameId,I_U8 slotId)
{
   I_U8 type[4];
   convertNodeType(type,nodeType);
   switch(result)
   {
      case ERROR_VERSION_NOT_PRESENT:
         sprintf(string,"Sw Del for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] Failed as Version Not Present",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_CONNECTING_UA_CP:
         sprintf(string,"Sw Del for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] Failed as Error Connecting CP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_CONNECTING_UA_PP:
         sprintf(string,"Sw Del for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] Failed as Error Connecting PP",
               swVersion,type,chasisFrameId,slotId);       
         break;
      case ERROR_VERSION_ALREADY_RUNNING:
         sprintf(string,"Sw Del for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] Failed as Version Already Running",
               swVersion,type,chasisFrameId,slotId);       
         break;
       case ERROR_ACTIVATION_IN_PROGRESS:
         sprintf(string,"Sw Del for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Activation in Progress",
               swVersion,type,chasisFrameId,slotId);    
         break;
       case ERROR_CARDSTATE_INVALID:
         sprintf(string,"Sw Del for SwVer [%s],NodeType [%s],Chasis [%d],Slot [%d] as Invalid Card State",
               swVersion,type,chasisFrameId,slotId);    
         break;
      default:
         sprintf(string,"Sw Del for SwVer [%s] NodeType [%s],Chasis [%d],SlotId [%d] Failed With Invalid Cause Value",
               swVersion,type,chasisFrameId,slotId);       
         break;
   }
}

/******************************* Function  Header*****************************
Function Name : deleteRowsFromEicCardInfo()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Deletes Rows from EicCardInfoTable if the PRESENT_CARD_INFO_RESP 
does not contain those chasisFrameId and slotId                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
 
I_Void deleteRowsFromEicCardInfo()
{
   OamOilCfgPresentCardInfoResp      *oamOilCfgPresentCardInfoRespPtr = NULL;
   EicCardInfoTableIndices           eicCardInfoIndices;

   I_U8           eicId[MAX_EIC];
   I_U8           chasisId[MAX_EIC];
   I_U8           count =ZERO; 
   I_S32          retCode = ONE;
   I_U16          index = ZERO;
   I_U16          index1 = ZERO;
   I_U32          isFound = I_FALSE;

   LOG_PRINT(LOG_INFO,"deleteRowsFromEicCardInfo: Entering in function");
   oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

   if ( (retCode = getEicIdChasisId( eicId, chasisId, &count ) ) != CLIB_SUCCESS )
   {
      LOG_PRINT(LOG_INFO,"EicCardInfoTable is Empty");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"EicCardInfoTable contains %d rows",count);
      for ( index = 0; index < count; index++ )
      {  
         for ( index1= ZERO; index1 < oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards; index1++ )
         {
            if ( (chasisId[index] == oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[index1].frameID ) && (eicId[index] == oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[index1].slotID))
            {
               isFound = I_TRUE;
               break;
            }
         }
         if ( isFound == I_FALSE )
         {
            eicCardInfoIndices.chasisFrameId = chasisId[index];
            eicCardInfoIndices.slotId = eicId[index];

            LOG_PRINT(LOG_DEBUG," Deleting row from EicCardInfoTable for ChasisId: %d SlotId: %d as this data does                                                            not exist in PRESENT_CARD_INFO_RESP",eicCardInfoIndices.chasisFrameId, 
                                  eicCardInfoIndices.slotId);  
            //if ( (retCode = deleteEicCardInfoTable ( &eicCardInfoIndices ) ) != CLIB_SUCCESS ) 
            if ( (retCode = markEicCardNotPresent(eicCardInfoIndices.chasisFrameId, eicCardInfoIndices.slotId ) ) != CLIB_SUCCESS ) 
            {
               LOG_PRINT(LOG_CRITICAL,"deleteEicCardInfoTable call is getting failed..");
            }
           
         }
         isFound = I_FALSE;
      }
   }
    LOG_PRINT(LOG_INFO,"deleteRowsFromEicCardInfo: Exiting from function");
}

/******************************* Function  Header*****************************
Function Name : deleteRowsFromSwmNodeTable()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Deletes Rows from SwMNodeTable if the PRESENT_CARD_INFO_RESP 
does not contain those slotId                
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void deleteRowsFromSwmNodeTable()
{
   OamOilCfgPresentCardInfoResp   *oamOilCfgPresentCardInfoRespPtr = NULL;
   SwMNodeTableIndices           swMNodeIndices;
   I_U32                         eicId[MAX_EIC];
   I_U8                          chasisId[MAX_EIC];
   I_U8                          count =ZERO; 
   I_S32                         retCode = ONE;
   I_U16                         index = ZERO;
   I_U16                         index1 = ZERO;
   I_U32                         isFound = I_FALSE;

   LOG_PRINT(LOG_INFO,"deleteRowsFromSwmNodeTable: Entering in function");
   oamOilCfgPresentCardInfoRespPtr = (OamOilCfgPresentCardInfoResp *)((I_U8 *)gCfgMsgBuf);

   if ( ( retCode = getEicIdChasisIdFromSwMNodeTable(chasisId, eicId, &count) ) != CLIB_SUCCESS ) 
   {
      LOG_PRINT(LOG_INFO,"SwMNodeTable is Empty");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"SwMNodeTable contains %d rows",count);
      for ( index = 0; index < count; index++ )
      {  
         for ( index1= ZERO; index1 < oamOilCfgPresentCardInfoRespPtr->cardInfo.numRemoteCards; index1++ )
         {
            if ( eicId[index] == oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[index1].slotID  && chasisId[index] == oamOilCfgPresentCardInfoRespPtr->cardInfo.eicInfo[index1].frameID )
            {
               isFound = I_TRUE;
               break;
            }
         }
         if ( isFound == I_FALSE )
         {
            swMNodeIndices.nodeType = SYS_NODE_TYPE_EIC;
            swMNodeIndices.nodeIdentity = eicId[index];
            swMNodeIndices.chasisFrameId = chasisId[index];
            swMNodeIndices.slotId = eicId[index];

            LOG_PRINT(LOG_DEBUG," Deleting row from SwMNodeTable for NodeType: %d NodeIdentity: %d FrameId: %d SlotId: %d as this data does not exist in PRESENT_CARD_INFO_RESP", swMNodeIndices.nodeType, swMNodeIndices.nodeIdentity, swMNodeIndices.chasisFrameId , swMNodeIndices.slotId);  
            if ( (retCode = deleteSwMNodeTable ( &swMNodeIndices ) ) != CLIB_SUCCESS ) 
            {
               LOG_PRINT(LOG_CRITICAL,"deleteSwMNodeTable call is getting failed..");
            }
         }
         isFound = I_FALSE;
      }
   }
    LOG_PRINT(LOG_INFO,"deleteRowsFromSwmNodeTable: Exiting from function");
}

/********************************* Function  Header********************************
  Function Name:     makeCopyOfActAlarm()
Parameters:          void
Return type:         void
Purpose:             To Preserve the alarm. This alarm will be sent after updating DB.
Other Note:          Added for CS4.0
 ************************************************************************************/
I_Void makeCopyOfActAlarm(OamsCfgAfhSysAlarm *sysAlarmBuff)
{
   LOG_PRINT(LOG_INFO,"makeCopyOfActAlarm: Entering in function");
   gCfgActAlarmBuf =(I_PVoid) AlocOrdBuf(sizeof(OamsCfgAfhSysAlarm));
   if(gCfgActAlarmBuf == NULL) 
   {
      LOG_PRINT(MAJOR,"AlocOrdBuf Failed for size:%d", sizeof(OamsCfgAfhSysAlarm));
      return;
   }
   memcpy(gCfgActAlarmBuf , (I_PVoid)sysAlarmBuff, sizeof (OamsCfgAfhSysAlarm));
   LOG_PRINT(LOG_INFO,"makeCopyOfActAlarm: Exiting from function");
}

/******************************* Function  Header*****************************
   Function Name : sendRequestForBscAvailableReleases()
Parameters    : None
Return type   : I_Void
Purpose       : Sends request for Bsc available releases present on BSC platform
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendRequestForSpecificSlotAvailableReleases(NodeType nodeType, I_U8 frameId, I_U8 slotId)
{
    LOG_PRINT(LOG_INFO,"sendRequestForSpecificSlotAvailableReleases: Entering in function");
   OamsCfgOilAvailableReleasesReq  availableReleasesReqBuff;  

   availableReleasesReqBuff.frameId = frameId;
   availableReleasesReqBuff.slotId = slotId;
   availableReleasesReqBuff.nodeType = nodeType;
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for ChasisFrameId[%d],SlotId[%d], NodeType[%d]",frameId,slotId,nodeType);
   cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
                  sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
                  OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
   gAvailReleaseRspFlag++;
   //LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag.. %d",gAvailReleaseRspFlag)
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented in sendRequestForSpecificSlotAvailableReleases()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
   LOG_PRINT(LOG_INFO,"sendRequestForSpecificSlotAvailableReleases: Exiting from function");
}

I_Void sendActivationAlarm( OamOilCfgAvailableReleasesResp *availableReleasesRespPtr)
{
  I_S32 retCode;
  I_U8 count = ZERO;
  I_U32 eicId[MAX_EIC];
  I_U32 dspId[MAX_DSP];
  I_U32 bscId;
  I_U32 status = SW_ACTIVATION_FAILED; 
  I_U8 chasisFrameId, slotId;
  I_S32 ret = ZERO;
  I_U8 noOfDsp = 0;
  I_U32 index=ZERO;
  I_U8 type[4];
  OamsCfgAfhSysAlarm *sysAlarmBuff = {0};
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;

  if(gCfgActAlarmBuf != NULL)
  {
    sysAlarmBuff = (OamsCfgAfhSysAlarm*)gCfgActAlarmBuf;
    if(sysAlarmBuff->sysAlarm.key3  != availableReleasesRespPtr->nodeType )
    {
      LOG_PRINT(DEBUG,"Available release resp rcvd for nodetype:%d while\
          Activationalarm is stored for nodetype:%d",availableReleasesRespPtr->nodeType,
          sysAlarmBuff->sysAlarm.key3  );
      return;
    }
    LOG_PRINT(LOG_INFO,"sendActivationAlarm: Entering in function");
    if(availableReleasesRespPtr->nodeType != SYS_NODE_TYPE_DSP)
    {
      LOG_PRINT(LOG_INFO,"sendActivationAlarm: FOR EIC");
      if (sysAlarmBuff->sysAlarm.alarmReason == ACTIVATION_SUCCESSFUL )
      {
        status = SW_ACTIVATION_SUCCESS;
        LOG_PRINT(LOG_INFO,"sendActivationAlarm: STATUS = SUCCESS");
      }
      else
        status = SW_ACTIVATION_FAILED;
    }
  }

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  if ( ( retCode = getEicIdFromSwMNodeTable(eicId, &count) ) != CLIB_SUCCESS ) 
  {
    LOG_PRINT(LOG_INFO,"SwMNodeTable is Empty");
    return;
  }

  if (getDspIdFromSwMNodeTable(dspId,&noOfDsp) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getDspId call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }

  LOG_PRINT(DEBUG,"noOfDsp returned from db : %d",noOfDsp);

  if (getBscId(&bscId) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
    bscId = 0;
  }
  if(  (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_BSC ) ||
      (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_EIC)  )
  {
    if ( availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_BSC )
    {
      sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
      sApiSwMNodeTableIndices.nodeIdentity = bscId;
      sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
      sApiSwMNodeTableIndices.slotId = availableReleasesRespPtr->slotId;
      status = SW_ACTIVATION_SUCCESS;
      if(gCfgActAlarmBuf != NULL)
      {
        cfgSendMessage(gCfgActAlarmBuf, sizeof(OamsCfgAfhSysAlarm), 
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      } 
    }
    else if ( availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_EIC )
    {
      sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
      sApiSwMNodeTableIndices.nodeIdentity = eicId[0];
      sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
      sApiSwMNodeTableIndices.slotId = eicId[0];
      if(gCfgActAlarmBuf != NULL)
      {
        cfgSendMessage(gCfgActAlarmBuf, sizeof(OamsCfgAfhSysAlarm), 
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      } 
    }

    retCode = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
    if (swMNodeTableDbPtr == NULL)
    {
      LOG_PRINT(LOG_DEBUG,"No Entry for NodeType[%d] NodeId[%u] FrameId[%d] in SwMNodeTable",
          sApiSwMNodeTableIndices.nodeType,sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.chasisFrameId);
      return;
    }
    /*    if (swMNodeTableDbPtr->swStatus ==  SW_ACTIVATION_IN_PROGRESS)
          {
          LOG_PRINT(LOG_INFO,"Activation is in Progress for FrameId: %d, SlotId: %d, NodeType: %u",
          availableReleasesRespPtr->frameId,availableReleasesRespPtr->slotId,availableReleasesRespPtr->nodeType);
     */   
    //if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
    //                                  status) !=CLIB_SUCCESS)
    if( updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,status,SW_NO_ACTION," ")
        != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
      gSwActStatus = SW_ACTIVATION_SUCCESS;
    }
    else
      LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success"); 

    if ( availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_EIC && count > 1 )
    {
      sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
      sApiSwMNodeTableIndices.nodeIdentity = eicId[1];
      sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
      sApiSwMNodeTableIndices.slotId = eicId[1];
      if( updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,status,SW_NO_ACTION," ")
          != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
        gSwActStatus = SW_ACTIVATION_SUCCESS;
      }
      else
        LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success"); 

    } 
  }
    else if ( availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_DSP )
    {
      //for( index=0; index < noOfDsp; index++ )
      if(availableReleasesRespPtr->slotId == 3 || availableReleasesRespPtr->slotId == 4) 
      { 
        for( index=0; index < MAX_DSP; index++ )
        {
          if(index >1)
          {
            break;  
          }
          if(gDspInfo[index].isDspPresent == NOT_PRESENT)
          {
            LOG_PRINT(DEBUG,"DspId:%d is not present hence not sending SW_ACT alarm", index);
            continue;
          }
          /*Update the upgraded version recieved as downloaded version 
           * in SwMNode Table for all the Dsp's*/
          sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
          sApiSwMNodeTableIndices.nodeIdentity = index;
          sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
          //sApiSwMNodeTableIndices.slotId = eicId[1];
          if(index == 0)
          {
            sApiSwMNodeTableIndices.slotId = 3;
          }			 
          if(index == 1)
          {
            sApiSwMNodeTableIndices.slotId = 4;
          }			 

          if(gCfgActAlarmBuf != NULL)
          { 
            sysAlarmBuff->sysAlarm.key2 = sApiSwMNodeTableIndices.slotId; 
            sysAlarmBuff->sysAlarm.key3 = index;
            FillObjTypeFromSlotId(sApiSwMNodeTableIndices.slotId,sysAlarmBuff->sysAlarm.info3 ); 
            if((sysAlarmBuff->sysAlarm.alarmReason & (0x01 << index)) != 0)
            {
              LOG_PRINT(DEBUG,"DspId:%d SW_ACT_SUCC alarm", index);
              status = SW_ACTIVATION_SUCCESS; 
              sysAlarmBuff->sysAlarm.sysalarmId = INFO_BPM_SW_ACT_SUCCESS;
              convertNodeType(type,availableReleasesRespPtr->nodeType);
              sysAlarmBuff->sysAlarm.infoStrLen = 
                sprintf(sysAlarmBuff->sysAlarm.infoString,"Sw Act for SwVer [%s] is Successful for NodeType [%s],ChasisFrameId [%d],SlotId [%d],dspId [%d]",
                    availableReleasesRespPtr->availSwVersions[0],type,sysAlarmBuff->sysAlarm.key1,
                    sysAlarmBuff->sysAlarm.key2,sysAlarmBuff->sysAlarm.key3); 
            }
            else
            {
              LOG_PRINT(DEBUG,"DspId:%d SW_ACT_FAIL alarm", index);
              status = SW_ACTIVATION_FAILED; 
              sysAlarmBuff->sysAlarm.sysalarmId = INFO_BPM_SW_ACT_FAIL;
              convertNodeType(type,availableReleasesRespPtr->nodeType);
              if(availableReleasesRespPtr->availSwVersions[2] != NULL)
              {
                sysAlarmBuff->sysAlarm.infoStrLen = 
                  sprintf(sysAlarmBuff->sysAlarm.infoString,"Sw Act for SwVer [%s] has failed for NodeType [%s],ChasisFrameId [%d],SlotId [%d],dspId [%d]",
                      availableReleasesRespPtr->availSwVersions[2],type,sysAlarmBuff->sysAlarm.key1,
                      sysAlarmBuff->sysAlarm.key2,sysAlarmBuff->sysAlarm.key3); 
              } 
              else
              {
                sysAlarmBuff->sysAlarm.infoStrLen = 
                  sprintf(sysAlarmBuff->sysAlarm.infoString,"Sw Act for SwVer [%s] has failed for NodeType [%s],ChasisFrameId [%d],SlotId [%d],dspId [%d]",
                      availableReleasesRespPtr->availSwVersions[0],type,sysAlarmBuff->sysAlarm.key1,
                      sysAlarmBuff->sysAlarm.key2,sysAlarmBuff->sysAlarm.key3); 
              }
            }

            cfgSendMessage(gCfgActAlarmBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
          }

          LOG_PRINT(DEBUG,"UPDATING SWMNODE TABLE with Data NodeType = %d, Node Id = %d, FrameId = %d, SlotId = %d",sApiSwMNodeTableIndices.nodeType,sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.chasisFrameId,sApiSwMNodeTableIndices.slotId);

          // if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
          //                               status) !=CLIB_SUCCESS)
          if( updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,status,SW_NO_ACTION," ")
              != CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
            gSwActStatus = SW_ACTIVATION_SUCCESS;
          }
          else
            LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success"); 
        }
      }//if icc dsp
      else if(availableReleasesRespPtr->slotId == 5 || availableReleasesRespPtr->slotId == 6) 
      { 
        for( index=0; index < MAX_DSP; index++ )
        {
          if(index <2)
          {
            continue;  
          }

          if(gDspInfo[index].isDspPresent == NOT_PRESENT)
          {
            LOG_PRINT(DEBUG,"DspId:%d is not present hence not sending SW_ACT alarm", index);
            continue;
          }
          /*Update the upgraded version recieved as downloaded version 
           * in SwMNode Table for all the Dsp's*/
          sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
          sApiSwMNodeTableIndices.nodeIdentity = index;
          sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
          //sApiSwMNodeTableIndices.slotId = eicId[1];
          if(index == 0)
          {
            sApiSwMNodeTableIndices.slotId = 3;
          }			 
          if(index == 1)
          {
            sApiSwMNodeTableIndices.slotId = 4;
          }			 
          if((index == 2) || (index == 3))
          {
            sApiSwMNodeTableIndices.slotId = 5;
          }			 
          if((index == 4) || (index == 5))
          {
            sApiSwMNodeTableIndices.slotId = 6;
          }			 

          if(gCfgActAlarmBuf != NULL)
          { 
            sysAlarmBuff->sysAlarm.key2 = sApiSwMNodeTableIndices.slotId; 
            sysAlarmBuff->sysAlarm.key3 = index;
            FillObjTypeFromSlotId(sApiSwMNodeTableIndices.slotId,sysAlarmBuff->sysAlarm.info3 ); 
            if((sysAlarmBuff->sysAlarm.alarmReason & (0x01 << index)) != 0)
            {
              LOG_PRINT(DEBUG,"DspId:%d SW_ACT_SUCC alarm", index);
              status = SW_ACTIVATION_SUCCESS; 
              sysAlarmBuff->sysAlarm.sysalarmId = INFO_BPM_SW_ACT_SUCCESS;
              convertNodeType(type,availableReleasesRespPtr->nodeType);
              sysAlarmBuff->sysAlarm.infoStrLen = 
                sprintf(sysAlarmBuff->sysAlarm.infoString,"Sw Act for SwVer [%s] is Successful for NodeType [%s],ChasisFrameId [%d],SlotId [%d],dspId [%d]",
                    availableReleasesRespPtr->availSwVersions[0],type,sysAlarmBuff->sysAlarm.key1,
                    sysAlarmBuff->sysAlarm.key2,sysAlarmBuff->sysAlarm.key3); 
            }
            else
            {
              LOG_PRINT(DEBUG,"DspId:%d SW_ACT_FAIL alarm", index);
              status = SW_ACTIVATION_FAILED; 
              sysAlarmBuff->sysAlarm.sysalarmId = INFO_BPM_SW_ACT_FAIL;
              convertNodeType(type,availableReleasesRespPtr->nodeType);
              if(availableReleasesRespPtr->availSwVersions[2] != NULL)
              {
                sysAlarmBuff->sysAlarm.infoStrLen = 
                  sprintf(sysAlarmBuff->sysAlarm.infoString,"Sw Act for SwVer [%s] has failed for NodeType [%s],ChasisFrameId [%d],SlotId [%d],dspId [%d]",
                      availableReleasesRespPtr->availSwVersions[2],type,sysAlarmBuff->sysAlarm.key1,
                      sysAlarmBuff->sysAlarm.key2,sysAlarmBuff->sysAlarm.key3); 
              } 
              else
              {
                sysAlarmBuff->sysAlarm.infoStrLen = 
                  sprintf(sysAlarmBuff->sysAlarm.infoString,"Sw Act for SwVer [%s] has failed for NodeType [%s],ChasisFrameId [%d],SlotId [%d],dspId [%d]",
                      availableReleasesRespPtr->availSwVersions[0],type,sysAlarmBuff->sysAlarm.key1,
                      sysAlarmBuff->sysAlarm.key2,sysAlarmBuff->sysAlarm.key3); 
              }
            }

            cfgSendMessage(gCfgActAlarmBuf, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
          }

          LOG_PRINT(DEBUG,"UPDATING SWMNODE TABLE with Data NodeType = %d, Node Id = %d, FrameId = %d, SlotId = %d",sApiSwMNodeTableIndices.nodeType,sApiSwMNodeTableIndices.nodeIdentity,sApiSwMNodeTableIndices.chasisFrameId,sApiSwMNodeTableIndices.slotId);

          // if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
          //                               status) !=CLIB_SUCCESS)
          if( updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,status,SW_NO_ACTION," ")
              != CLIB_SUCCESS)
          {
            LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
            gSwActStatus = SW_ACTIVATION_SUCCESS;
          }
          else
            LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success"); 
        }
      }//for eic dsp
    } 
    if(gCfgActAlarmBuf != NULL) 
    {
      DalocOrdBuf((I_Void *)gCfgActAlarmBuf);
      gCfgActAlarmBuf = NULL;
    }
    /*}
      else
      {
      LOG_PRINT(LOG_INFO,"Activation is not in Progress for FrameId: %d, SlotId: %d, NodeType: %u",
      availableReleasesRespPtr->frameId,availableReleasesRespPtr->slotId,availableReleasesRespPtr->nodeType); 
      }*/
    if (swMNodeTableDbPtr != NULL)
    {
      free(swMNodeTableDbPtr);
      swMNodeTableDbPtr = NULL;
    }
    LOG_PRINT(LOG_INFO,"sendActivationAlarm: Exiting from function");
}

I_Void updateEicDataOnEicConnect()
{
    OamOilCfgEicConnectLoad *bpmEicConnect = (OamOilCfgEicConnectLoad *)gCfgMsgBuf;
    SwMNodeTableIndices sApiSwMNodeTableIndices;
    SwMNodeTableApi *swMNodeTableBuf = NULL;
    SwMNodeTableApi swMNodeTableData;
    I_S32 res; 
    res = ChkActiveCardAlarm(bpmEicConnect->chasisFrameId,bpmEicConnect->iccSlotId);
    if(res != TRUE)
    {
       LOG_PRINT(DEBUG,"Eic Connect Alarm is not raised for active card thus discarding it");
       return; 
    }
 
    LOG_PRINT(LOG_INFO,"updateEicDataOnEicConnect: Entering in function");
    LOG_PRINT(LOG_MAJOR,"Alarm Received ChasisFrameId [%d] SlotId [%d]",bpmEicConnect->chasisFrameId,bpmEicConnect->slotId);

    sApiSwMNodeTableIndices.chasisFrameId = bpmEicConnect->chasisFrameId;
    sApiSwMNodeTableIndices.slotId = bpmEicConnect->slotId;
    sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_EIC;
    sApiSwMNodeTableIndices.nodeIdentity = bpmEicConnect->slotId;
   
   if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableBuf) != CLIB_SUCCESS)
   {
       LOG_PRINT(LOG_DEBUG,"getSwMNodeTable Failed..");
       swMNodeTableData.e1Num = E1_INVALID;
       swMNodeTableData.lapdTs = TS_INVALID;
       strcpy(swMNodeTableData.swVersionDownloaded,"");
       strcpy(swMNodeTableData.swVersionNew,"");
       swMNodeTableData.swAction = SW_NO_ACTION;
       swMNodeTableData.swStatus = SW_NO_LAST_ACTION;
   }
   else
   {
       swMNodeTableData.e1Num = swMNodeTableBuf->e1Num;
       swMNodeTableData.lapdTs = swMNodeTableBuf->lapdTs;
       strcpy(swMNodeTableData.swVersionDownloaded,swMNodeTableBuf->swVersionDownloaded);
       strcpy(swMNodeTableData.swVersionNew,swMNodeTableBuf->swVersionNew);
       swMNodeTableData.swAction = swMNodeTableBuf->swAction;
       swMNodeTableData.swStatus = swMNodeTableBuf->swStatus;
   }

   swMNodeTableData.chasisFrameId = bpmEicConnect->chasisFrameId;
   swMNodeTableData.slotId = bpmEicConnect->slotId;
   swMNodeTableData.nodeType = SYS_NODE_TYPE_EIC;
   swMNodeTableData.nodeIdentity = bpmEicConnect->slotId;
   strcpy(swMNodeTableData.swVersionActive,bpmEicConnect->eicActiveVersion);
   strcpy(swMNodeTableData.swVersionInactive,bpmEicConnect->eicBackupVersion);

   LOG_PRINT(DEBUG,"Going To update EIC SwmNodeTAble frameId:%d slotId:%d",
         swMNodeTableData.chasisFrameId, swMNodeTableData.slotId );

   /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
   /*if(updateSwMNodeTable(&swMNodeTableData) != CLIB_SUCCESS)
   {
      if (insertSwMNodeTable(&swMNodeTableData) != CLIB_SUCCESS)
      {
          LOG_PRINT(LOG_DEBUG,"insertSwMNode Failed..");
      }
   }*/
   /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
   if ( swMNodeTableBuf != NULL )
      free(swMNodeTableBuf);
   sendUpgradeAlarm();
   LOG_PRINT(LOG_INFO,"updateEicDataOnEicConnect: Exiting from function");
}

I_Void updateEicDataOnEicEnableDisable()
{
    OamOilCfgEicEnableDisableLoad *bpmEicEnable = (OamOilCfgEicEnableDisableLoad *)gCfgMsgBuf;
    SwMNodeTableIndices sApiSwMNodeTableIndices;
    SwMNodeTableApi *swMNodeTableBuf = NULL;
    SwMNodeTableApi swMNodeTableData;
     
    LOG_PRINT(LOG_INFO,"updateEicDataOnEicEnableDisable: Entering in function");
    LOG_PRINT(LOG_MAJOR,"Alarm Received [%d]",bpmEicEnable->alarmId);
    sApiSwMNodeTableIndices.chasisFrameId = bpmEicEnable->chasisFrameId;
    sApiSwMNodeTableIndices.slotId = bpmEicEnable->slotId;
    sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_EIC;
    sApiSwMNodeTableIndices.nodeIdentity = bpmEicEnable->slotId;
    if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableBuf) != CLIB_SUCCESS)
    {
       LOG_PRINT(LOG_DEBUG,"getSwMNodeTable Failed..");
       swMNodeTableData.e1Num = E1_INVALID;
       swMNodeTableData.lapdTs = TS_INVALID;
       strcpy(swMNodeTableData.swVersionDownloaded,"");
       strcpy(swMNodeTableData.swVersionNew,"");
       swMNodeTableData.swAction = SW_NO_ACTION;
       swMNodeTableData.swStatus = SW_NO_LAST_ACTION;
    }
   else
   {
       swMNodeTableData.e1Num = swMNodeTableBuf->e1Num;
       swMNodeTableData.lapdTs = swMNodeTableBuf->lapdTs;
       strcpy(swMNodeTableData.swVersionDownloaded,swMNodeTableBuf->swVersionDownloaded);
       strcpy(swMNodeTableData.swVersionNew,swMNodeTableBuf->swVersionNew);
       swMNodeTableData.swAction = swMNodeTableBuf->swAction;
      swMNodeTableData.swStatus = swMNodeTableBuf->swStatus;
   }
   swMNodeTableData.chasisFrameId = bpmEicEnable->chasisFrameId;
   swMNodeTableData.slotId = bpmEicEnable->slotId;
   swMNodeTableData.nodeType = SYS_NODE_TYPE_EIC;
   swMNodeTableData.nodeIdentity = bpmEicEnable->slotId;
   strcpy(swMNodeTableData.swVersionActive,bpmEicEnable->eicActiveVersion);
   strcpy(swMNodeTableData.swVersionInactive,bpmEicEnable->eicBackupVersion);

   LOG_PRINT(DEBUG,"Going To update EIC SwmNodeTAble frameId:%d slotId:%d",
         swMNodeTableData.chasisFrameId, swMNodeTableData.slotId );

   /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
   /*if(updateSwMNodeTable(&swMNodeTableData) != CLIB_SUCCESS)
   {
      if (insertSwMNodeTable(&swMNodeTableData) != CLIB_SUCCESS)
      { 
          LOG_PRINT(LOG_DEBUG,"insertSwMNode failed ");
      }
   }*/
   /*Not Required at BSC-DB/OMC 27 Sept 2016*/ 
   if ( swMNodeTableBuf != NULL )
   {
   // Mantis 11329 if ( swMNodeTableBuf->swStatus != SW_ACTIVATION_IN_PROGRESS )
   //if ( swMNodeTableBuf->swStatus == SW_ACTIVATION_IN_PROGRESS )
   //{
         updateEicDetail = TRUE;
         sendPresentCardInfoReq();
   //}
      free(swMNodeTableBuf);
   }
   else
   {
      if(gCfgState != CFG_BPM_INIT)
      {
       updateEicDetail = TRUE;
       sendPresentCardInfoReq(); 
      }
   }
   sendUpgradeAlarm();
   LOG_PRINT(LOG_INFO,"updateEicDataOnEicEnableDisable: Exiting from function");
}
 
I_Void cfgInsertIccDetails(sCardObjInfo cardObjInfo)
{
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   SwMNodeTableApi swMNodeTableBuf;
   SwMNodeTableApi *swMNodeDbPtr = NULL;
   SwMTableApi swMTableBuff;
   I_U8 swVersion[TOKENS_IN_STRING];
   I_U32 bscId;

   LOG_PRINT(LOG_INFO,"cfgInsertIccDetails : Entering in function");

   swVersion[0] = cardObjInfo.activeRelVersion.major;
   swVersion[1] = cardObjInfo.activeRelVersion.minor;
   swVersion[2] = cardObjInfo.activeRelVersion.revision;
   if(convertInputNumberToString(swVersion,TOKENS_IN_STRING,swMNodeTableBuf.swVersionActive) == SW_VER_FAILURE)
   {
     LOG_PRINT(LOG_MAJOR,"conversion of software version from number to string failed");
     return;
   }
   LOG_PRINT(LOG_INFO,"Active software version Received :%s",swMNodeTableBuf.swVersionActive);

   swVersion[0] = cardObjInfo.backUpRelVersion.major;
   swVersion[1] = cardObjInfo.backUpRelVersion.minor;
   swVersion[2] = cardObjInfo.backUpRelVersion.revision;
   if(convertInputNumberToString(swVersion,TOKENS_IN_STRING,swMNodeTableBuf.swVersionInactive) == SW_VER_FAILURE)
   {
     LOG_PRINT(LOG_MAJOR,"ERROR : conversion of software version from number to string failed");
     return;
   }
   LOG_PRINT(LOG_INFO,"Inactive software version Received :%s", swMNodeTableBuf.swVersionInactive);

   swVersion[0] = cardObjInfo.downLoadedRelVersion.major;
   swVersion[1] = cardObjInfo.downLoadedRelVersion.minor;
   swVersion[2] = cardObjInfo.downLoadedRelVersion.revision;
   if(convertInputNumberToString(swVersion,TOKENS_IN_STRING,swMNodeTableBuf.swVersionDownloaded) == SW_VER_FAILURE)
   {
     LOG_PRINT(LOG_MAJOR,"ERROR : conversion of software version from number to string failed");
     return;
   }
   LOG_PRINT(INFO,"Downloaded software version Received :%s",swMNodeTableBuf.swVersionDownloaded);

   if (getBscId(&bscId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"No row present in BSS Table");
      swMNodeTableBuf.nodeIdentity = 0;
   }
   else
   {
      swMNodeTableBuf.nodeIdentity = bscId;
   }

   sApiSwMNodeTableIndices.nodeType = SYS_NODE_TYPE_BSC;
   sApiSwMNodeTableIndices.nodeIdentity = swMNodeTableBuf.nodeIdentity;
   sApiSwMNodeTableIndices.chasisFrameId = cardObjInfo.frameID;
   sApiSwMNodeTableIndices.slotId = cardObjInfo.slotID;
   swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
   strcpy(swMNodeTableBuf.swVersionNew,"");

   if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeDbPtr) != CLIB_SUCCESS)
   {
        LOG_PRINT(LOG_DEBUG,"getSwMNodeTable Failed..");
   }
   else
   {
      if (swMNodeDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS)
      {
         LOG_PRINT(DEBUG,"SW_ACTIVATION_IN_PROGRESS for Icc of slotId:%d",cardObjInfo.slotID);
         swMNodeTableBuf.swStatus = SW_ACTIVATION_IN_PROGRESS;
         strcpy(swMNodeTableBuf.swVersionNew,swMNodeDbPtr->swVersionNew);
      }
      free(swMNodeDbPtr);
   }

   swMNodeTableBuf.nodeType = SYS_NODE_TYPE_BSC;
   swMNodeTableBuf.e1Num = E1_INVALID;
   swMNodeTableBuf.lapdTs = TS_INVALID;
   swMNodeTableBuf.swAction = SW_NO_ACTION;
   swMNodeTableBuf.chasisFrameId = cardObjInfo.frameID;
   swMNodeTableBuf.slotId = cardObjInfo.slotID;
   
   if ( cardObjInfo.activeRelVersion.major == 0)
   {
      strcpy(swMNodeTableBuf.swVersionActive,"");
   }
   if ( cardObjInfo.backUpRelVersion.major == 0)
   {
      strcpy(swMNodeTableBuf.swVersionInactive,"");
   }
   if ( cardObjInfo.downLoadedRelVersion.major == 0)
   {
      strcpy(swMNodeTableBuf.swVersionDownloaded,"");
   }


   if(updateSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
   {
      if(insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed");
         return;
      }
   }

   /* Update SwMTable */

   swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
   swMTableBuff.chasisFrameId = cardObjInfo.frameID;
   swMTableBuff.slotId = cardObjInfo.slotID;
   strcpy(swMTableBuff.swVersion,
          swMNodeTableBuf.swVersionActive);
   memcpy(swMTableBuff.binaryPath,"",
                  OAMS_CMD_PARAM_MAX_SIZE);
   swMTableBuff.swDownloadCount = ZERO;
   swMTableBuff.deletionInProgress = I_FALSE;
   if ( cardObjInfo.activeRelVersion.major != 0)
   {
      if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"insertSwMTable DB call is getting failed..");
      } 
   }
   strcpy(swMTableBuff.swVersion,
           swMNodeTableBuf.swVersionInactive);
   if ( cardObjInfo.backUpRelVersion.major != 0)
   {
      if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"insertSwMTable DB call is getting failed..");
      }   
   }
   strcpy(swMTableBuff.swVersion,
           swMNodeTableBuf.swVersionDownloaded);
   
   if ( cardObjInfo.downLoadedRelVersion.major != 0)
   {
      if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_MAJOR,"insertSwMTable DB call is getting failed..");
      }
   }   

   LOG_PRINT(LOG_INFO,"cfgInsertIccDetails : Exiting from function");
}

/******************************* Function  Header*****************************
Function Name : sendQuerySetCardOperState()
Parameters    : I_U32: cardState  
Return type   : I_Void
Purpose       : Send Request to OIL for setting ICC cardState 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendQuerySetCardOperState(I_U32 cardState, I_U8 slotId)
{
   OamsCfgOilSetCardOperState setOperState;
   LOG_PRINT(LOG_INFO,"Entering function: sendQuerySetCardOperState");

   setOperState.cardType = BPM_CARD_ICC;
   setOperState.slotId = slotId; 
   setOperState.cardState = cardState;
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SET_OPER_CON_STATE_REQ to Oil.. for slotId: %d", setOperState.slotId);
   cfgSendMessage((I_Void *)&setOperState, sizeof(OamsCfgOilSetCardOperState),
                  ENT_OAM_OIL, OAMS_CFG_OIL_SET_OPER_CON_STATE_REQ , 0);
   LOG_PRINT(LOG_INFO,"Exiting function: sendQuerySetCardOperState");
         
}

I_S32 handlingPlatformInst()
{
    I_S8 fileForTesting[] = "/home/PLATFORM_INST_RECEIVED";
    I_S8 touchString[50];
    I_U32 swStatus[TWO]={ZERO};
    I_U8 count = ZERO;
    I_S32 status = ZERO;
    I_U32 index = ZERO;
 
   LOG_PRINT(LOG_INFO,"Entering function: handlingPlatformInst");

   if( getEicSwStatusFromSwMNodeTable(SYS_NODE_TYPE_EIC, swStatus, &count) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable call is getting failed.."); 
      return CFG_SUCCESS;
   }
   for ( index=0; index<count; index++)
   { 
      if(swStatus[index] == SW_ACTIVATION_IN_PROGRESS)
      {
         LOG_PRINT(LOG_DEBUG,"Activation is in progress for EIC ");
         sprintf(touchString,"touch %s", fileForTesting);
         LOG_PRINT(LOG_DEBUG,"For EIC Activation support........... ");
         LOG_PRINT(LOG_INFO,"Going to create file %s.... ", touchString);
         status = system(touchString);
         if( status != ZERO )
         {
            LOG_PRINT(CRITICAL,"ERROR in Creating file: %d",status >> 8);
            return CFG_FAILURE;
         }
         LOG_PRINT(LOG_INFO," Created FILE %s",touchString);
         break;
      }
   }

   LOG_PRINT(LOG_INFO,"Exiting function: handlingPlatformInst");
   return CFG_SUCCESS;
}

I_S32 checkPlatformInstFile()
{
   I_S8 fileForTesting[] = "/home/PLATFORM_INST_RECEIVED";
   I_S8 removeString[50];

   struct stat *buf;
   I_S32 status = ZERO; 
   LOG_PRINT(LOG_INFO,"Entering function: checkPlatformInstFile");
   if (!(stat(fileForTesting,buf)))
   {
      LOG_PRINT(LOG_INFO,"%s File exists",fileForTesting);
      LOG_PRINT(LOG_INFO,"EIC ACTIVATION was in Progress",fileForTesting);
      LOG_PRINT(LOG_INFO,"Now removing file");
      sprintf(removeString," rm -rf %s",fileForTesting);
      status = system(removeString);
      if ( status != ZERO  )
      {
         LOG_PRINT(CRITICAL,"ERROR in removing file: %d",status >> 8);
         return CFG_SUCCESS;
      }
      LOG_PRINT(LOG_INFO,"File Removed successfully");
      return CFG_SUCCESS;
   }
   else
   {
      LOG_PRINT(LOG_INFO,"%s File does not exists",fileForTesting);
      return CFG_FAILURE;
   }
   
   LOG_PRINT(LOG_INFO,"Exiting function: checkPlatformInstFile");
}


/********************************* Change History ***************************
   Release        Author             Description
   BSC CS4.0     Geetanjali Arya     Initial Draft

 ************************************** End *********************************/

