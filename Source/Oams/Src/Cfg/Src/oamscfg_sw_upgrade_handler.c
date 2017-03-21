/************************************************************* File Header ***
   File Name      : oamscfg_sw_upgrade_handler.c
Purpose        : This file contains function defintions required for handling
SW Download and Activation.
Project        : BSC
Subsystem      : OAMS 
Author         : Aricent 
CSCI id        :
Version        :
 ******************************************************************** End ***/

#include "oamscfg_includes.h"
I_CHAR *trxPathName = NULL;
I_CHAR *bicPathName = NULL;
I_CHAR *btsPathName = NULL;

#define convertNodeType(nodeType,intValue) \
if(intValue == SYS_NODE_TYPE_BSC) \
strcpy(nodeType,"BSC"); \
else if(intValue == SYS_NODE_TYPE_EIC) \
strcpy(nodeType,"EIC"); \
else if(intValue == SYS_NODE_TYPE_BIC) \
strcpy(nodeType,"BIC"); \
else if(intValue == SYS_NODE_TYPE_R2_BTS) \
strcpy(nodeType,"BTS"); \
else if(intValue == SYS_NODE_TYPE_R2_BTS_IP) \
strcpy(nodeType,"BTS"); \
else if(intValue == SYS_NODE_TYPE_R3_BTS) \
strcpy(nodeType,"BTS"); \
else if(intValue == SYS_NODE_TYPE_TRX) \
strcpy(nodeType,"TRX"); \
else if(intValue == SYS_NODE_TYPE_DSP) \
strcpy(nodeType,"DSP"); 

/******************************* Function  Header*****************************
   Function Name : setSwMOfferTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Upgrade Offer request from OMC/CLI
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void setSwMOfferTableHandler()
{
   SwMOfferTableApi *receiveMsgPtr = NULL;
   SwMOfferTableApi *swMOfferTableDbPtr = NULL;
   receiveMsgPtr = (SwMOfferTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   SwMOfferTableIndices swMOfferTableindex;
   SwMTableApi *swMTableDbPtr = NULL;
   SwMTableIndices swMTableindex;
   I_S32 ret = ONE;
   I_U32 rowCount = ZERO;
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;
   I_S32 actionInProgress = I_FALSE;
   I_CHAR logPasswdChSum[OAMS_NAME_SIZE + 1];
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_U32 nodeType =0, failType =0, swStatus = 0;

   if((receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS_IP) || (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R3_BTS))
   {
      setIpBtsSwMOfferTableHandler();
   }
   else
   {
     if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
     {
       LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
       cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
       return;
     }
     LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

     swMOfferTableindex.nodeType = receiveMsgPtr->nodeType;
     strcpy(swMOfferTableindex.upgradeVersion,receiveMsgPtr->upgradeVersion);
     swMTableindex.nodeType = receiveMsgPtr->nodeType;
     strcpy(swMTableindex.swVersion,receiveMsgPtr->upgradeVersion);

     if ((receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC) || 
         (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX) || (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS) )
     {
       receiveMsgPtr->chasisFrameId = chasisFrameId;
       receiveMsgPtr->slotId = slotId;
       swMOfferTableindex.chasisFrameId = chasisFrameId;
       swMOfferTableindex.slotId = slotId;
       swMTableindex.chasisFrameId = chasisFrameId;
       swMTableindex.slotId = slotId;
     }
     else
     {
       swMOfferTableindex.chasisFrameId = receiveMsgPtr->chasisFrameId;
       swMOfferTableindex.slotId = receiveMsgPtr->slotId;
       swMTableindex.chasisFrameId = receiveMsgPtr->chasisFrameId;
       swMTableindex.slotId = receiveMsgPtr->slotId;
     } 
     LOG_PRINT(LOG_INFO,"setSwMOfferTableHandler : Entering function");
     LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->upgradeVersion);
     LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
     LOG_PRINT(LOG_INFO,"FrameId: %d ",receiveMsgPtr->chasisFrameId);
     LOG_PRINT(LOG_INFO,"SlotId: %d ",receiveMsgPtr->slotId);

     LOG_PRINT(LOG_INFO,"ftpServerAddress: %u",receiveMsgPtr->ftpServerAddress);
     memset(logPasswdChSum,NULL,OAMS_NAME_SIZE + 1);
     memcpy(logPasswdChSum,receiveMsgPtr->loginName,OAMS_NAME_SIZE);
     LOG_PRINT(LOG_INFO,"loginName: %s ",logPasswdChSum);
     memset(logPasswdChSum,NULL,OAMS_NAME_SIZE + 1);
     memcpy(logPasswdChSum,receiveMsgPtr->password,OAMS_NAME_SIZE);
     LOG_PRINT(LOG_INFO,"password: %s",logPasswdChSum);
     memset(logPasswdChSum,NULL,OAMS_NAME_SIZE + 1);
     memcpy(logPasswdChSum,receiveMsgPtr->checksum,OAMS_NAME_SIZE);
     LOG_PRINT(LOG_INFO,"checksum: %s",logPasswdChSum);
     LOG_PRINT(LOG_INFO,"size: %u",receiveMsgPtr->size);

     if ((receiveMsgPtr->nodeType != SYS_NODE_TYPE_BSC) &&
         (receiveMsgPtr->nodeType != SYS_NODE_TYPE_BIC) && 
         (receiveMsgPtr->nodeType != SYS_NODE_TYPE_TRX) && (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS) )
     {
       LOG_PRINT(LOG_DEBUG,"Invalid NodeType recieved");
       cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
       return; 
     }

     /*Check Sw Version is in correct format*/
     if (convertInputStringToNumber(receiveMsgPtr->upgradeVersion,&tokenNum,
           token,&errCause) == SW_VER_SUCCESS)
     {
  //       LOG_PRINT(LOG_INFO,"token[0]: %d",token[0]);
  //       LOG_PRINT(LOG_INFO,"token[1]: %d",token[0]);
  //       LOG_PRINT(LOG_INFO,"token[2]: %d",token[0]);
   //      LOG_PRINT(LOG_INFO,"token[3]: %d",token[0]);
       if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255) )        
       {
         LOG_PRINT(LOG_INFO,"token[0]: %d",token[0]);
         LOG_PRINT(LOG_INFO,"token[1]: %d",token[1]);
         LOG_PRINT(LOG_INFO,"token[2]: %d",token[2]);
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

       if (rowCount > 0 && (rowCount < MAX_SW_UPGRADE_OFFER_IN_PARALLEL)) 
       {
         /*Check if entry exists in SwMOffer table for req swVersion */
         ret = getSwMOfferTable(&swMOfferTableindex,&swMOfferTableDbPtr);
         if (swMOfferTableDbPtr != NULL)
         {
           LOG_PRINT(LOG_DEBUG,"Platform has already started dnload procedure");
           cfgSendNackToCm(CM_ERR_DWNLD_ALREADY_INITIATED);
           free(swMOfferTableDbPtr);
           return;
         }
       }
     }
     /* CS4.0 changes start */
     /* check if activation is in progress for BSC/EIC */
     actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
     if ( actionInProgress == I_TRUE )
     {
       LOG_PRINT(LOG_DEBUG,"Activation/Download is in progress for nodeType:%d", nodeType);
       fillFailTypeFromNodeType(nodeType, failType)
         cfgSendNackToCm(failType);
       return;
     }
     /* FIX for Mantis: 6130 start */
     /* check if deletion is in progress for BSC/EIC/BIC/TRX */
     actionInProgress = isDeletionInProgress();
     if ( actionInProgress == I_TRUE )
     {
       LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC or BIC or TRX");
       cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
       return;
     }
     /* FIX for Mantis: 6130 End */
     /* CS4.0 changes End */
     /*Check if for the requested sw version, there is an entry in SwM table */
     ret = getSwMTable(&swMTableindex,&swMTableDbPtr);
     if (swMTableDbPtr != NULL)
     {
       LOG_PRINT(LOG_DEBUG,"Software version is already present with platform");
       cfgSendNackToCm(CM_ERR_SW_VERSION_ALREADY_DWNLDED);
       free(swMOfferTableDbPtr);
       return;
     }

     /*Insert record in SwMOffer Table indicating download is in process for 
      * requested sw version */
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
     LOG_PRINT(LOG_INFO,"setSwMOfferTableHandler : Exiting function");
   }
}

/******************************* Function  Header*****************************
   Function Name : setSwMNodeTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles BSC software activation, BIC/TRX/BTS software downlaod 
and activation procedure
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void setSwMNodeTableHandler()
{
   SwMNodeTableApi *receiveMsgPtr = NULL;
   receiveMsgPtr = (SwMNodeTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
   I_U32 tokenNum;
   I_U32 token[MAX_DIGITS];
   I_U32 errCause;
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_S32 ret = ZERO ;

   if((receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS_IP)|| (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R3_BTS))
   {
      setIpBtsSwMNodeTableHandler();
   }
   else
   {
     LOG_PRINT(LOG_INFO,"setSwMNodeTableHandler : Entering function");
     LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersionNew);
     LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
     LOG_PRINT(LOG_INFO,"SwAction: %d",receiveMsgPtr->swAction);

     if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
     {
       LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
       cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
       return;
     }
     LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);


     if ((receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC) || 
         (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX) ||
         (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS))
     {
       if ( (receiveMsgPtr->chasisFrameId != chasisFrameId) || (receiveMsgPtr->slotId != slotId) )
       {
         LOG_PRINT(LOG_DEBUG,"ChasisFrameId or SlotId is not of Active Card ");
         cfgSendNackToCm(CM_ERR_CHASISID_SLOTID_PROVIDED_NOT_ACTIVE);
         return;
       }
       receiveMsgPtr->chasisFrameId = chasisFrameId;
       receiveMsgPtr->slotId = slotId;
     }
     LOG_PRINT(LOG_INFO,"FrameId: %d",receiveMsgPtr->chasisFrameId); /* CS4.0 HA Change */
     LOG_PRINT(LOG_INFO,"SlotId: %d",receiveMsgPtr->slotId); /* CS4.0 HA Change */

     if ((receiveMsgPtr->nodeType != SYS_NODE_TYPE_BSC) && 
         (receiveMsgPtr->nodeType != SYS_NODE_TYPE_BIC) && 
         (receiveMsgPtr->nodeType != SYS_NODE_TYPE_TRX)  &&
         (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS))
     {
       LOG_PRINT(LOG_DEBUG,"Invalid NodeType recieved");
       cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
       return; 
     }

     /*Check Sw Version is in correct format*/
     if (convertInputStringToNumber(receiveMsgPtr->swVersionNew,&tokenNum,
           token,&errCause) == SW_VER_SUCCESS)
     {
       if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255) )        
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

     if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BSC)
     {
       performBscSwActivationOperation(receiveMsgPtr);
     }
     else if ((receiveMsgPtr->swAction == SW_DOWNLOAD) && 
         ((receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC) || 
          (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX) || 
          (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS)))
     {
       performBicAndTrxSwDownloadOperation(receiveMsgPtr);
     }
     else if ((receiveMsgPtr->swAction == SW_ACTIVATE) && 
         ((receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC) || 
          (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX) ||
          (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS)))
     {
       performBicAndTrxSwActivationOperation(receiveMsgPtr);
     }
     else
     {
       LOG_PRINT(LOG_DEBUG,"Invalid request recieved");
       cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
       return; 
     }
     LOG_PRINT(LOG_INFO,"setSwMNodeTableHandler : Exiting function");
   }
}

/******************************* Function  Header*****************************
   Function Name : performBscSwActivationOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles BSC software activation procedure
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void performBscSwActivationOperation(SwMNodeTableApi *receiveMsgPtr)
{
   SwMTableApi *swMTableDbPtr = NULL;
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMNodeTableIndices swMNodeTableIndex;
   SwMTableIndices swMTableIndex;
   OamsCfgOilSwActReq swActBuff;
   I_S32 ret = ONE;
   /* CS4.0 Changes Start */
   SwMOfferTableApi *swMOfferBuff = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;
   I_U32 swStatus[MAX_EIC]={ZERO};
   I_U32 index;
   I_U8 count = ZERO;
   I_S32 actionInProgress = I_FALSE;
   I_U8 chasisFrameId;
   I_U8 slotId;
   I_U32 nodeType =0, failType =0, swStatus_o = 0;

   /* CS4.0 Changes End */
   swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
   swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
   swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMNodeTableIndex.slotId = receiveMsgPtr->slotId;

   swMTableIndex.nodeType = receiveMsgPtr->nodeType;
   swMTableIndex.slotId = receiveMsgPtr->slotId;
   swMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);

   LOG_PRINT(LOG_INFO,"performBscSwActivationOperation : Entering function");

   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);


   /*Check if swAction is SW_ACTIVATE */
   if (receiveMsgPtr->swAction != SW_ACTIVATE)
   {
      LOG_PRINT(LOG_DEBUG,"Invalid request recieved for BSC");
      cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
      return;
   }
   LOG_PRINT(LOG_INFO,"Recieved BSC Sw Activation Request");
   if ( (receiveMsgPtr->chasisFrameId == chasisFrameId) && (receiveMsgPtr->slotId == slotId) )
   {
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
   }
   /* Changes for CS4.0 start */
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
   /* Changes for CS4.0 End */

   /*Check if requested sw version of BSC is present in T3 table */
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
   /*Check if req Sw version is not active SwVersion of BSC in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionActive,receiveMsgPtr->swVersionNew) == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"Requested Sw version is the Active SwVersion of BSC");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      cfgSendNackToCm(CM_ERR_VERSION_ALREADY_ACTIVATE);
      return;
   }
   /*Check if req Sw version is present in inactive/downloaded SwVersion list
    *  of BSC in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionInactive,receiveMsgPtr->swVersionNew) != ZERO && 
         strcmp(swMNodeTableDbPtr->swVersionDownloaded,receiveMsgPtr->swVersionNew) != ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"Requested Sw version is not present in inactive/downloaded SwVersion List of BSC");
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
   /* CS4.0 Changes Start */
   if( getEicSwStatusFromSwMNodeTable(SYS_NODE_TYPE_EIC, swStatus, &count) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable call is getting failed.."); 
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }

   for ( index=0; index<count; index++)
   { 
      if(swStatus[index] == SW_ACTIVATION_IN_PROGRESS)
      {
         LOG_PRINT(LOG_DEBUG,"Activation is in progress for EIC ");
         cfgSendNackToCm(CM_ERR_SW_EIC_ACT_IN_PROGRESS);
         return;
      }
   }
   /* CS4.0 Changes End */
   #endif
   /*Update record in SwMNode table indicating sw activation is in progress */
   if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
            SW_ACTIVATION_IN_PROGRESS,SW_ACTIVATE,receiveMsgPtr->swVersionNew) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");

   /*send SET Ack message to OMC */
   cfgSendAckToCm();

   /* CS4.0 Changes Start */

   gSwActBuff.frameId = receiveMsgPtr->chasisFrameId;
   gSwActBuff.slotId = receiveMsgPtr->slotId;
   gSwActBuff.nodeType = receiveMsgPtr->nodeType;
   //gSwActBuff.cardState = BPM_CARDSTATE_OUT_OF_SERVICE;
   strcpy(gSwActBuff.actVersion,receiveMsgPtr->swVersionNew);
		LOG_PRINT(LOG_INFO,"Values Recived  SlotID = %d  nodeType = %d ActVer = %s",gSwActBuff.slotId, gSwActBuff.nodeType,gSwActBuff.actVersion);
   /* CS4.0 Changes End */
   LOG_PRINT(LOG_INFO,"OOS For Slot = %d",gSwActBuff.slotId);
	 sendQuerySetCardOperState(BPM_CARDSTATE_OUT_OF_SERVICE,gSwActBuff.slotId);


   //LOG_PRINT(LOG_INFO,"Sending BSC Sw Activation request");
   //LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SW_ACT_REQ to Oil");
   //cfgSendMessage((I_Void *)&swActBuff, sizeof(OamsCfgOilSwActReq), ENT_OAM_OIL,
   //      OAMS_CFG_OIL_SW_ACT_REQ , 0);
   LOG_PRINT(LOG_INFO,"performBscSwActivationOperation : Exiting function");

}

/******************************* Function  Header*****************************
   Function Name : performBicAndTrxSwDownloadOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles BIC/TRX/BTS software download procedure
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void performBicAndTrxSwDownloadOperation(SwMNodeTableApi *receiveMsgPtr)
{
   SwMTableApi *swMTableDbPtr = NULL;
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMNodeTableIndices swMNodeTableIndex;
   SwMTableIndices swMTableIndex;
   I_S32 ret = ONE;
   I_U32 adminState,status;
   I_U32 index;
   I_U8 swDownloadCount = 0;
   I_U8 binaryPath[OAMS_CMD_PARAM_MAX_SIZE];
   I_S32 actionInProgress = I_FALSE;
   I_U32 nodeType =0, failType =0, swStatus = 0;
   swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
   swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
   swMTableIndex.nodeType = receiveMsgPtr->nodeType;
   strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);
   /*CS4.0 HA Changes Start*/
   swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMNodeTableIndex.slotId = receiveMsgPtr->slotId;
   swMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMTableIndex.slotId = receiveMsgPtr->slotId;
   /*CS4.0 HA Changes End*/

   LOG_PRINT(LOG_INFO,"performBicAndTrxSwDownloadOperation:Entering function");
   /*Check the admin state of TRX */
   if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      LOG_PRINT(LOG_INFO,"Recieved TRX Sw Download Request");
      ret = getPtrxAdminStatus(receiveMsgPtr->nodeIdentity,&adminState);
      if (ret != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"Requested Trx does not exist in Trx Table");
         cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
         return;
      }
      if (gPtrxData[receiveMsgPtr->nodeIdentity].ptrxState == unlocked) 
      {
         LOG_PRINT(LOG_DEBUG,"TRX is in UnLocked state");
         LOG_PRINT(LOG_DEBUG,"Download allowed only if TRX is in Locked state");
         cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
         return;
      }
      else if (gPtrxData[receiveMsgPtr->nodeIdentity].ptrxState == unlockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"TRX is UnLock in Progress state");
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
         return;
      }
      else if (gPtrxData[receiveMsgPtr->nodeIdentity].ptrxState == lockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"TRX is Lock in Progress state");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"TRX is in Locked state");
   }
   else 
   {
      if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC)
      {
         LOG_PRINT(LOG_INFO,"Recieved BIC  Sw Download Request");
      }
      else {
         LOG_PRINT(LOG_INFO,"Recieved BTS  Sw Download Request");
      }

      if(getIndex(receiveMsgPtr->nodeIdentity, &index) == CFG_FAILURE)
      {
         LOG_PRINT(LOG_CRITICAL,"BIC/BTS[%d] is not present in Internal Data Structure", receiveMsgPtr->nodeIdentity);
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         return;
      }
      else
      {
         if (gBtsData[index].btsState == unlocked) 
         {
            LOG_PRINT(LOG_DEBUG,"BIC/BTS is in UnLocked state");
            LOG_PRINT(LOG_DEBUG,"Download allowed only if BIC/BTS is in Locked state");
            cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
            return;
         }
         else if (gBtsData[index].btsState == unlockInProgress)
         {
            LOG_PRINT(LOG_DEBUG,"BIC/BTS is UnLock in Progress state");
            cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
            return;
         }
         else if (gBtsData[index].btsState == lockInProgress)
         {
            LOG_PRINT(LOG_DEBUG,"BIC/BTS is Lock in Progress state");
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
            return;
         }
         else
            LOG_PRINT(LOG_INFO,"BIC/BTS is in Locked state");
      }
   }

   /*Check if requested sw version of BSC is present in SwM table */
   ret = getSwMTable(&swMTableIndex,&swMTableDbPtr);
   if (swMTableDbPtr == NULL)
   {
      LOG_PRINT(LOG_DEBUG,"Software version is not present with platform");
      cfgSendNackToCm(CM_ERR_VERSION_NOT_FOUND);
      return;
   }
   else if (swMTableDbPtr->deletionInProgress == I_TRUE)
   {
      LOG_PRINT(LOG_DEBUG,"Deletion is in progress for the req Sw version");
      if (swMTableDbPtr != NULL)
         free(swMTableDbPtr);
      cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
      return; 
   }

   memcpy(binaryPath,swMTableDbPtr->binaryPath,OAMS_CMD_PARAM_MAX_SIZE);
   /*Check if for the nodeId and nodeType, there is a record in T2 table */
   ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
   if (swMNodeTableDbPtr == NULL)
   {
      LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
            receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      free(swMTableDbPtr);  /* Mantis Fixed #4819 */
      return;
   }
   /*Check if requested Sw version is active or inactive SwVersion in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionActive,receiveMsgPtr->swVersionNew) == ZERO ||
         strcmp(swMNodeTableDbPtr->swVersionInactive,receiveMsgPtr->swVersionNew) == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"Req Sw version is already downloaded on the node");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      free(swMTableDbPtr);  /* Mantis Fixed #4819 */
      cfgSendNackToCm(CM_ERR_VERSION_ALREADY_AVAILABLE);
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
      free(swMTableDbPtr);  /* Mantis Fixed #4819 */
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
   }

   /*Check how many downloads are already in progress for the BIC/TRX belonging
    *  to the same Abis E1 compared to the received request */
   if (checkMaxDownloadAllowed(swMNodeTableDbPtr->e1Num,
            swMNodeTableDbPtr->lapdTs) != I_TRUE)
   {
      LOG_PRINT(LOG_DEBUG,"Maximum Number of downloads limit reached");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      free(swMTableDbPtr);  /* Mantis Fixed #4819 */
      return;
   }

   if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
   /*Check the link Status for the node */
   if (getLapdLinkStatus(receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity, 
            &status) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getLapdLinkStatus DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      free(swMTableDbPtr);  /* Mantis Fixed #4819 */
      return;
   }
   if (status != CONNECTED)
   {
      LOG_PRINT(LOG_DEBUG,"Lapd link is not Connected");
      free(swMTableDbPtr);  /* Mantis Fixed #4819 */

      /*if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC)
         cfgSendNackToCm(CM_ERR_BIC_NOT_CONNECTED);*/
      if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS || receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC )
         cfgSendNackToCm(CM_ERR_BTS_LAPD_NOT_ESTABLISHED);
      else
         cfgSendNackToCm(CM_ERR_TRX_NOT_CONNECTED);
      return;
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

   /*Update record in SwMNode table indicating sw download is in progress */
   if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
            SW_DOWNLOAD_IN_PROGRESS,SW_DOWNLOAD,receiveMsgPtr->swVersionNew) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      free(swMTableDbPtr);   /* Mantis Fixed #4819 */
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");

   /*Increment the swDownloadCount value in T3 table for requested sw version */
   swDownloadCount = swMTableDbPtr->swDownloadCount + 1;   
   free(swMTableDbPtr);      /* Mantis Fixed #4819 */
   if (updateCountInSwMTable(swMTableIndex,swDownloadCount) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

   /*send SET Ack message to OMC */
   cfgSendAckToCm();

   /*Send request to the SwMH to download the software */
   LOG_PRINT(LOG_INFO,"Sending Sw Download Request");
   sendSwDownloadRequest(receiveMsgPtr,binaryPath);
   LOG_PRINT(LOG_INFO,"performBicAndTrxSwDownloadOperation:Exiting function");
}

/******************************* Function  Header*****************************
   Function Name : performBicAndTrxSwActivationOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles BIC/TRX/BTS software activation procedure
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void performBicAndTrxSwActivationOperation(SwMNodeTableApi *receiveMsgPtr)
{
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMNodeTableIndices swMNodeTableIndex;
   SwMTableIndices swMTableIndex;
   I_S32 ret = ONE;
   I_U32 index;
   I_U32 adminState,status;
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   I_S32 actionInProgress = 0;
   I_U32 nodeType =0, failType =0, swStatus = 0;
   I_U8 type[4];
  
   swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
   swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
   swMTableIndex.nodeType = receiveMsgPtr->nodeType;
   strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);
   /* CS4.0: HA changes start */
   swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMNodeTableIndex.slotId = receiveMsgPtr->slotId;
   swMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
   swMTableIndex.slotId = receiveMsgPtr->slotId;
   /* CS4.0: HA changes end */

   LOG_PRINT(LOG_INFO,"performBicAndTrxSwActivationOperation:Enter function");
   /*Check the admin state of TRX */
   if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      LOG_PRINT(LOG_INFO,"Recieved TRX Sw Activation request");
      ret = getPtrxAdminStatus(receiveMsgPtr->nodeIdentity,&adminState);
      if (ret != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"Requested Trx does not exist in Trx Table");
         cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
         return;
      }
      if (gPtrxData[receiveMsgPtr->nodeIdentity].ptrxState == unlocked) 
      {
         LOG_PRINT(LOG_DEBUG,"TRX is in UnLocked state");
         LOG_PRINT(LOG_DEBUG,"Activation allowed only if TRX is in Locked state");
         cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
         return;
      }
      else if (gPtrxData[receiveMsgPtr->nodeIdentity].ptrxState == unlockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"TRX is UnLock in Progress state");
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
         return;
      }
      else if (gPtrxData[receiveMsgPtr->nodeIdentity].ptrxState == lockInProgress)
      {
         LOG_PRINT(LOG_DEBUG,"TRX is Lock in Progress state");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"TRX is in Locked state");
   }
   else 
   {
      if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC) {
         LOG_PRINT(LOG_INFO,"Recieved BIC  Sw Download Request");
      }
      else  {
         LOG_PRINT(LOG_INFO,"Recieved BTS  Sw Download Request");
      }
      if(getIndex(receiveMsgPtr->nodeIdentity, &index) == CFG_FAILURE)
      {
         LOG_PRINT(LOG_CRITICAL,"BIC/BTS[%d] is not present in Internal Data Structure", receiveMsgPtr->nodeIdentity);
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         return;
      }
      else 
      {
         if (gBtsData[index].btsState == unlocked) 
         {
            LOG_PRINT(LOG_DEBUG,"BIC/BTS is in UnLocked state");
            LOG_PRINT(LOG_DEBUG,"Download allowed only if BIC/BTS is in Locked state");
            cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
            return;
         }
         else if (gBtsData[index].btsState == unlockInProgress)
         {
            LOG_PRINT(LOG_DEBUG,"BIC/BTS is UnLock in Progress state");
            cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
            return;
         }
         else if (gBtsData[index].btsState == lockInProgress)
         {
            LOG_PRINT(LOG_DEBUG,"BIC/BTS is Lock in Progress state");
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
            return;
         }
         else
            LOG_PRINT(LOG_INFO,"BIC/BTS is in Locked state");
      }
   }
   /*Check if for the nodeId and nodeType, there is a record in T2 table */
   ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
   if (swMNodeTableDbPtr == NULL)
   {
      LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
            receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   /*Check if requested Sw version is active SwVersion in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionActive,
            receiveMsgPtr->swVersionNew) == ZERO )
   {
      LOG_PRINT(LOG_DEBUG,"Requested Sw version is already activated on Node");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      cfgSendNackToCm(CM_ERR_VERSION_ALREADY_ACTIVATE);
      return;
   }
   /*Check if requested Sw version is inactive SwVersion in SwMNode Table*/
   else if (strcmp(swMNodeTableDbPtr->swVersionInactive,
            receiveMsgPtr->swVersionNew) != ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"Req Sw version is not available for activation");
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
      LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress ");
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);
      cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
      return;
   }

   if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
   /*Check the link Status for the node */
   if (getLapdLinkStatus(receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity,
            &status) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getLapdLinkStatus DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   LOG_PRINT(LOG_INFO,"LapdLinkStatus: %d",status);
   if (status != CONNECTED)
   {
      LOG_PRINT(LOG_DEBUG,"Lapd link is not Connected");

      /*if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC)
         cfgSendNackToCm(CM_ERR_BIC_NOT_CONNECTED);*/
      if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS || receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC)
         cfgSendNackToCm(CM_ERR_BTS_LAPD_NOT_ESTABLISHED);
      else
         cfgSendNackToCm(CM_ERR_TRX_NOT_CONNECTED);
      return;
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
   /*Update record in SwMNode table indicating sw activation is in progress */
   if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
            SW_ACTIVATION_IN_PROGRESS,SW_ACTIVATE,receiveMsgPtr->swVersionNew) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");

   /*send SET Ack message to OMC */
   cfgSendAckToCm();

   /*Send the Activation request to SwMH module */
   LOG_PRINT(LOG_INFO,"Sending Sw Activation Request");
   sendSwActivationRequest(receiveMsgPtr);
 
   /*Mantis Fix : 10735*/
   LOG_PRINT(LOG_INFO,"Sending Alarm: INFO_BPM_SW_ACT_STARTED");
   sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_ACT_STARTED; 
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; /*OAMS_OBJTYPE_EIC;*/
   sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
   sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
   convertNodeType(type,receiveMsgPtr->nodeType);
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,"Sw Act for NodeType [%s] is Started at ChasisFrameId [%d],SlotId [%d]",type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2)); //Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                     ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   /*Mantis Fix : 10735*/
   LOG_PRINT(LOG_INFO,"performBicAndTrxSwActivationOperation: Exit function");
}

/******************************* Function  Header*****************************
   Function Name : delSwMTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles BSC/BIC/TRX/BTS software deletion procedure
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void delSwMTableHandler()
{
//Veena 
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMTableIndices sApiSwMTableIndices;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMOfferIpTableIndices swMOfferIpTableindex;
  //I_U8 string[MAX_STRING_LENGTH];
  //I_U8 binaryPath[OAMS_CMD_PARAM_MAX_SIZE];
  I_S32 status;
//Veena
  SwMTableApi *swMTableDbPtr =NULL;
  SwMTableApi *receiveMsgPtr =NULL;
  SwMNodeTableApi *swMNodeDbPtr =NULL;
  SwMTableIndices SwMTableIndex;
  receiveMsgPtr = (SwMTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  SwMOfferTableApi *swMOfferBuff = NULL;
  I_U32 outCount = ZERO;
  I_U16 outSize = ZERO;
  I_S32 actionInProgress = I_FALSE;
  I_U32 bscId =0;
  I_S32 ret = CFG_FAILURE;
  I_U32 tokenNum;
  I_U32 token[MAX_DIGITS +1];
  I_U32 errCause;
  I_U8 chasisFrameId;
  I_U8 slotId;
  I_U32 nodeType =0, failType =0, swStatus = 0;
   I_U8 type[4];
  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

  if ((receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC) || 
      (receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX) || 
      (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS) ||
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R3_BTS))
  {
    if ( (receiveMsgPtr->chasisFrameId != chasisFrameId) || (receiveMsgPtr->slotId != slotId) )
    {
      LOG_PRINT(LOG_DEBUG,"ChasisFrameId or SlotId is not of Active Card ");
      cfgSendNackToCm(CM_ERR_CHASISID_SLOTID_PROVIDED_NOT_ACTIVE);
      return;
    }
    receiveMsgPtr->chasisFrameId = chasisFrameId;
    receiveMsgPtr->slotId = slotId;
    SwMTableIndex.chasisFrameId = chasisFrameId;
    SwMTableIndex.slotId = receiveMsgPtr->slotId;
  }
  else
  {
    SwMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
    SwMTableIndex.slotId = receiveMsgPtr->slotId;
  }
  SwMTableIndex.nodeType = receiveMsgPtr->nodeType;
  strcpy(SwMTableIndex.swVersion,receiveMsgPtr->swVersion);

  LOG_PRINT(LOG_INFO,"delSwMTableHandler: Enter function");
  LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersion);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
  LOG_PRINT(LOG_INFO,"FrameId: %d ",receiveMsgPtr->chasisFrameId);
  LOG_PRINT(LOG_INFO,"slotId: %d ",receiveMsgPtr->slotId);

  if ((receiveMsgPtr->nodeType != SYS_NODE_TYPE_BSC) && 
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_BIC) && 
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_TRX) &&
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS_IP) &&
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R3_BTS) &&
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS))
  {
    LOG_PRINT(LOG_DEBUG,"Invalid NodeType recieved");
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return; 
  }
   
  
  
  if(   (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS_IP) ||
      (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R3_BTS) )
  {
     tokenNum = 4; //except for IP-BTS all versions are 3 byte
    if (convertInputStringToNumber(receiveMsgPtr->swVersion,&tokenNum,
          token,&errCause) == SW_VER_SUCCESS)
    {
      if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255) || (token[3] > 255))        
        //if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
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
  }
  else 
  {

    if (convertInputStringToNumber(receiveMsgPtr->swVersion,&tokenNum,
          token,&errCause) == SW_VER_SUCCESS)
    {
      if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255) )        
        //if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
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
  }

  /* CS4.0 Changes start */
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
  actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx(&nodeType, &swStatus );
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
    fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
    return;
  }
  /* check if deletion is in progress for BSC/EIC/BIC/TRX/BTS */
  actionInProgress = isDeletionInProgress();
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC/EIC/BIC/TRX/BTS");
    cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
    return;
  }
  /* FIX for Mantis: 6130 end */
  /* CS4.0 Changes end */

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
/* Mantis-id 28664 - commenting the check not valid in R2.9 
  if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BIC || 
      receiveMsgPtr->nodeType == SYS_NODE_TYPE_TRX || receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS || receiveMsgPtr->nodeType == SYS_NODE_TYPE_R3_BTS || receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS_IP )
  {
    // Check if swDownloadCount value is greater than 0 
    if (swMTableDbPtr->swDownloadCount >0)
    {
      LOG_PRINT(LOG_DEBUG,"Software downloading is in progress");
      if (swMTableDbPtr != NULL)
        free(swMTableDbPtr);
      cfgSendNackToCm(CM_ERR_SW_BEING_DWNLDED);
      return;
    }
  }
*/
  if (swMTableDbPtr != NULL)
    free(swMTableDbPtr);
  /*Check if deletion recieved for BSC */
  if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_BSC)
  {
    SwMNodeTableIndices sApiSwMNodeTableIndices;
    /* Retrieve bscId from BSS Table */
    if (getBscId(&bscId) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
    }

    /*Retrieve active version and swStatus from SwMNode Table */
    sApiSwMNodeTableIndices.nodeType = receiveMsgPtr->nodeType; /*SYS_NODE_TYPE_BSC;*/
    sApiSwMNodeTableIndices.nodeIdentity = bscId;
    sApiSwMNodeTableIndices.chasisFrameId = receiveMsgPtr->chasisFrameId;
    sApiSwMNodeTableIndices.slotId = receiveMsgPtr->slotId;

    if (getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeDbPtr) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"getSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
    }

    /*Check if requested Sw Version is the Active SwVersion for BSC */ 
    if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionActive) == ZERO)
    {
      LOG_PRINT(LOG_INFO,"Req. Sw Version is currently the Active SwVersion for BSC");
      if (swMNodeDbPtr != NULL)
        free(swMNodeDbPtr);
      cfgSendNackToCm(CM_ERR_ACTIVE_SW);
      return;
    }

    /*Check if requested Sw Version is the Inactive SwVersion for BSC */ 
    if (strcmp(receiveMsgPtr->swVersion,swMNodeDbPtr->swVersionInactive) == ZERO)
    {
      LOG_PRINT(LOG_INFO,"Deletion not allowed for Inactive SwVersion for BSC");
      if (swMNodeDbPtr != NULL)
        free(swMNodeDbPtr);
      cfgSendNackToCm(CM_ERR_INACTIVE_SW);
      return;
    }

    /*Check if requested Sw Version is activation in progress */ 
    if (swMNodeDbPtr->swStatus == SW_ACTIVATION_IN_PROGRESS)
    {
      LOG_PRINT(LOG_INFO,"Activation is in progress for req. Sw version");
      if (swMNodeDbPtr != NULL)
        free(swMNodeDbPtr);
      cfgSendNackToCm(CM_ERR_SW_ACT_IN_PROGRESS);
      return;
    }                   
    
  }

  if (swMNodeDbPtr != NULL)
    free(swMNodeDbPtr);
  /*Update the swAction value as swDelete in SwM Table */
  if (updateDelStatusInSwMTable(SwMTableIndex,I_TRUE) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateDelStatusInSwMTable Failed..");
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateDelStatusInSwMTable Success");


  /*Send Delete request to Platform*/
  LOG_PRINT(LOG_INFO,"Sending Deletion request");
  if((receiveMsgPtr->nodeType != SYS_NODE_TYPE_R3_BTS) && (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS_IP) ){

    /*send SET Ack message to OMC */
    cfgSendAckToCm();
    sendSwDeletionRequest(receiveMsgPtr->chasisFrameId,receiveMsgPtr->slotId,receiveMsgPtr->nodeType,receiveMsgPtr->swVersion);
  }
  else
  {
    //delete from SWMTable also 



    LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",receiveMsgPtr->swVersion);
    LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
    LOG_PRINT(LOG_INFO,"FrameId: %d ",receiveMsgPtr->chasisFrameId);
    LOG_PRINT(LOG_INFO,"SlotId: %d ",receiveMsgPtr->slotId);

    sApiSwMTableIndices.nodeType = receiveMsgPtr->nodeType;
    sApiSwMTableIndices.chasisFrameId = receiveMsgPtr->chasisFrameId;
    sApiSwMTableIndices.slotId = receiveMsgPtr->slotId;
    strcpy(sApiSwMTableIndices.swVersion,receiveMsgPtr->swVersion);

  swMOfferIpTableindex.nodeType = receiveMsgPtr->nodeType;
  strcpy(swMOfferIpTableindex.upgradeVersion,receiveMsgPtr->swVersion);
  
  
  status = deleteSwMOfferIpTable(&swMOfferIpTableindex) ; 


  //delete from SWMOfferIpTable 
    LOG_PRINT(LOG_INFO,"status: %d",status);
    if (status != CLIB_SUCCESS)
    {
      return;
    }

    /*Delete the record of the requested sw version from T2 Table */
    if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"deleteSwMTable Success");

    /*Check if deletion request comes for BSC */
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);

    /* Send Alarm */
    LOG_PRINT(LOG_INFO,"Sending Success Alarm: INFO_BPM_DEL_VERSION_SUCCESS");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_DEL_VERSION_SUCCESS;
    /* CS4.0 changes start */
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
    /* Fixed issue 7297 */
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId; /*nodeInfo->chasisFrameId*/ 
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId; /*nodeInfo->slotId*/
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Del for SwVer [%s] nodeType [%s] is Completed at ChasisFrameId [%d],SlotId [%d]",
          receiveMsgPtr->swVersion,type,receiveMsgPtr->chasisFrameId,receiveMsgPtr->slotId); 
    /*Mantis Fix: 11303 Starts*/
    FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    /*Mantis Fix: 11303 Ends*/

    cfgSendMessage((I_Void *)&sysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);


    cfgSendAckToCm();
  }//Veena  

  LOG_PRINT(LOG_INFO,"delSwMTableHandler: Exit function");
}

/******************************* Function  Header*****************************
   Function Name : checkMaxDownloadAllowed()
Parameters    : I_U32 nodeType,I_U32 nodeIdentity,I_U32 e1Num
Return type   : I_Bool
Purpose       : It checks the maximum software download allowed in the system
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Bool checkMaxDownloadAllowed(I_U32 e1Num,I_U8 lapdTs)
{
   SwMPreconfigTableApi *swMPreconfigTablePtr =NULL;
   SwMNodeTableSecIndices SwMNodeSecIndex;
   SwMNodeTableTerIndices SwMNodeTerIndex;
   I_U16 outSize = 0;
   I_U32 rowCount = 0;
   I_U32 countOfSwDownloads = 0;
   I_U32 countOfSwDownloadsTotal = 0;

   SwMNodeSecIndex.e1Num = e1Num;
   SwMNodeSecIndex.lapdTs = lapdTs;
   SwMNodeSecIndex.swStatus = SW_DOWNLOAD_IN_PROGRESS;
   SwMNodeTerIndex.swStatus = SW_DOWNLOAD_IN_PROGRESS;

   LOG_PRINT(LOG_INFO,"checkMaxDownloadAllowed: Enter function");
   LOG_PRINT(LOG_INFO,"e1Num: %d lapdTs: %d",e1Num,lapdTs);
   /* Retreive row from SwMPreconfig Table to check maximim downloads */
   if (getallSwMPreconfigTable(&swMPreconfigTablePtr,&rowCount,&outSize) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getallSwMPreconfigTable Failed..");
      return I_FALSE;
   }

   /*Check if Max allowed downlaods Per E1Ts is Download in progress */
   if (getCountOfSwDnldsOnE1Ts(SwMNodeSecIndex,&countOfSwDownloads) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"No Sw Download is in progress for the requested E1Ts");
   }
   LOG_PRINT(LOG_INFO,"Count of Sw Download in progress for E1Ts: %d",countOfSwDownloads);
   if ( countOfSwDownloads == swMPreconfigTablePtr->maxSwDownloadsPerSharedTs)
   {
      LOG_PRINT(LOG_DEBUG,"Already max allowed dnlds per E1Ts is in progress");
      cfgSendNackToCm(CM_ERR_MAX_SW_DWNLD_ON_E1TS_REACHED);
      if (swMPreconfigTablePtr != NULL)
         free(swMPreconfigTablePtr);
      return I_FALSE;
   }

   /*Check if Max allowed total downlaods is Download in progress */
   if (getCountOfSwDnlds(SwMNodeTerIndex,&countOfSwDownloadsTotal) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"No Sw Download is in progress for any E1Ts");
   }
   LOG_PRINT(LOG_INFO,"Total Count of Sw Download in progress: %d",countOfSwDownloadsTotal);
   if ( countOfSwDownloadsTotal == swMPreconfigTablePtr->maxSwDownloadsTotal)
   {
      LOG_PRINT(LOG_DEBUG,"Already max allowed total downloads is in progress");
      cfgSendNackToCm(CM_ERR_MAX_SW_DWNLD_TOTAL_REACHED);
      if (swMPreconfigTablePtr != NULL)
         free(swMPreconfigTablePtr);
      return I_FALSE;
   }

   if (swMPreconfigTablePtr != NULL)
      free(swMPreconfigTablePtr);
   LOG_PRINT(LOG_INFO,"checkMaxDownloadAllowed: Exit function");
   return I_TRUE;
}

/******************************* Function  Header*****************************
   Function Name : sendSwUpgradeOfferRequest()
Parameters    : SwMOfferTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Sends Sw Upgrade Offer request to OIL
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void sendSwUpgradeOfferRequest(SwMOfferTableApi *receiveMsgPtr)
{
   OamsCfgOilSwOfferReq swOfferReqBuff;
   swOfferReqBuff.frameId = receiveMsgPtr->chasisFrameId;
   swOfferReqBuff.slotId = receiveMsgPtr->slotId;
   swOfferReqBuff.nodeType = receiveMsgPtr->nodeType;
   strcpy(swOfferReqBuff.upgradeVersion,receiveMsgPtr->upgradeVersion);
   swOfferReqBuff.ftpServerAddress = receiveMsgPtr->ftpServerAddress;
   memcpy(swOfferReqBuff.binaryPath,receiveMsgPtr->tarPathName,OAMS_CMD_PARAM_MAX_SIZE);
   memcpy(swOfferReqBuff.loginName,receiveMsgPtr->loginName,OAMS_NAME_SIZE);
   memcpy(swOfferReqBuff.password,receiveMsgPtr->password,OAMS_NAME_SIZE);
   memcpy(swOfferReqBuff.checkSum,receiveMsgPtr->checksum,OAMS_NAME_SIZE);
   swOfferReqBuff.size = receiveMsgPtr->size;
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SW_OFFER_REQ to Oil..")
      cfgSendMessage((I_Void *)&swOfferReqBuff, sizeof(OamsCfgOilSwOfferReq),
            ENT_OAM_OIL, OAMS_CFG_OIL_SW_OFFER_REQ , 0);
}

/******************************* Function  Header*****************************
   Function Name : sendSwDeletionRequest()
Parameters    : SwMTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Sends Sw deletion request to OIL
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void sendSwDeletionRequest(I_U8 frameId,I_U8 slotId,I_U32 nodeType,I_S8 *swVersion)
{
   OamsCfgOilSwDelReq swDelBuff;
   swDelBuff.frameId = frameId;
   swDelBuff.slotId = slotId;
   swDelBuff.nodeType = nodeType;
   strcpy(swDelBuff.delVersion,swVersion);
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_SW_DEL_REQ to Oil..")
   LOG_PRINT(LOG_INFO,"Sending request for SwVersion: %s",swDelBuff.delVersion);
   LOG_PRINT(LOG_INFO,"FrameId: %d SlotId: %d NodeType: %d",swDelBuff.frameId,swDelBuff.slotId,swDelBuff.nodeType);
   cfgSendMessage((I_Void *)&swDelBuff, sizeof(OamsCfgOilSwDelReq), 
         ENT_OAM_OIL, OAMS_CFG_OIL_SW_DEL_REQ , 0);
}

/******************************* Function  Header*****************************
   Function Name : sendSwDownloadRequest()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Sends Sw download request to SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void sendSwDownloadRequest(SwMNodeTableApi *receiveMsgPtr, I_U8 *binaryPath)
{
   OamsCfgSwmhSwDnldReq swDnldReqBuff;
   I_U32 applTei;
   if (getApplTei(receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity,
            &applTei) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }

   swDnldReqBuff.nodeType = receiveMsgPtr->nodeType;  
   swDnldReqBuff.nodeIdentity = receiveMsgPtr->nodeIdentity;
   swDnldReqBuff.applTei = applTei;
   strcpy(swDnldReqBuff.swVersion,receiveMsgPtr->swVersionNew);
   memcpy(swDnldReqBuff.binaryPath,binaryPath,OAMS_CMD_PARAM_MAX_SIZE);
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_SWMH_SW_DNLD_REQ to Swmh..");
   LOG_PRINT(LOG_INFO,"Sending request for SwVersion: %s",swDnldReqBuff.swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",swDnldReqBuff.nodeType,swDnldReqBuff.nodeIdentity);
   LOG_PRINT(LOG_INFO,"ApplTei:%d",applTei);
   cfgSendMessage((I_Void *)&swDnldReqBuff, sizeof(OamsCfgSwmhSwDnldReq), 
         ENT_OAMS_SWMH, OAMS_CFG_SWMH_SW_DNLD_REQ, 0);

}

/******************************* Function  Header*****************************
   Function Name : sendSwActivationRequest()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Sends Sw activation request to SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void sendSwActivationRequest(SwMNodeTableApi *receiveMsgPtr)
{
   OamsCfgSwmhSwActReq swActReqBuff;
   I_U32 applTei;
   if (getApplTei(receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity,
            &applTei) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }

   swActReqBuff.nodeType = receiveMsgPtr->nodeType;  
   swActReqBuff.nodeIdentity = receiveMsgPtr->nodeIdentity;
   swActReqBuff.applTei = applTei;
   strcpy(swActReqBuff.swVersion,receiveMsgPtr->swVersionNew);
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_SWMH_SW_ACT_REQ to Swmh..");
   LOG_PRINT(LOG_INFO,"Sending request for SwVersion: %s",swActReqBuff.swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",swActReqBuff.nodeType,swActReqBuff.nodeIdentity);
   LOG_PRINT(LOG_INFO,"ApplTei:%d",applTei);
   cfgSendMessage((I_Void *)&swActReqBuff, sizeof(OamsCfgSwmhSwActReq),
         ENT_OAMS_SWMH, OAMS_CFG_SWMH_SW_ACT_REQ, 0);
}

/******************************* Function  Header*****************************
   Function Name : swOfferRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Offer respose recieved from OIL
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swOfferRespHandler()
{
   OamOilCfgSwOfferResp *swOfferRespPtr = NULL;
   /* CS4.0 Changes start */
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoSwDwnldResult *bpmOfferResp = (OamOilCfgInfoSwDwnldResult*)gCfgMsgBuf;
   swOfferRespPtr = (OamOilCfgSwOfferResp*)(&(bpmOfferResp->swMOfferResp));
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmOfferResp->nodeInfo));
   I_U8 type[4];
   /* CS4.0 Changes End */
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   SwMOfferTableIndices swMOfferTableIndex;
   SwMNodeTableIndices swMNodeTableIndex;
   I_U32 bscId = ZERO;
   I_U8 string[MAX_STRING_LENGTH];
   I_S32 status = -1;
   I_U8 cpBinaryPath[OAMS_CMD_PARAM_MAX_SIZE];
   swMOfferTableIndex.nodeType = swOfferRespPtr->nodeType;
   swMOfferTableIndex.chasisFrameId = swOfferRespPtr->frameId;
   swMOfferTableIndex.slotId = swOfferRespPtr->slotId;
   strcpy(swMOfferTableIndex.upgradeVersion,swOfferRespPtr->upgradeVersion);

   LOG_PRINT(LOG_INFO,"swOfferRespHandler : Enter Function");
   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swOfferRespPtr->upgradeVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swOfferRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swOfferRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"slotId: %d ",swOfferRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"BinaryPath: %s",swOfferRespPtr->binaryPath);
   LOG_PRINT(LOG_INFO,"Result: %d ",swOfferRespPtr->upgradeOfferResult);

   /* Retrieve bscId from BSS Table */
   if (getBscId(&bscId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
      return;
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

      if (swOfferRespPtr->nodeType == SYS_NODE_TYPE_BSC)
      {
         /*Update the upgraded version recieved as downloaded version 
          * in SwMNode Table */
         swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
         swMNodeTableIndex.nodeIdentity = bscId;
         swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
         swMNodeTableIndex.slotId = swOfferRespPtr->slotId;
         if (updateVersionDownloadedInSwMNodeTable(swMNodeTableIndex,
                  swOfferRespPtr->upgradeVersion) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed");
            return;
         }
         else
            LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success");

         if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
             SW_DOWNLOAD_SUCCESS) !=CLIB_SUCCESS)  
         {
             LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
         }
      }

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success ALARM: INFO_BPM_SW_DWNLD_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId;

   /* CS4.0 changes start */

      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId; 
      sysAlarmBuff.sysAlarm.key2 =  nodeInfo->slotId; 
      sysAlarmBuff.sysAlarm.alarmLevel = bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      convertNodeType(type,swOfferRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "Sw Offer for SwVer [%s],NodeType [%s] is Completed at ChasisFrameId [%d],SlotId [%d]",
            swOfferRespPtr->upgradeVersion,type,nodeInfo->chasisFrameId,nodeInfo->slotId); 
    /* CS4.0 changes End */

      /*Mantis Fix: 11303 Starts*/
      FillObjTypeFromNodeType(swOfferRespPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      /*Mantis Fix: 11303 Ends*/
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

      if (swOfferRespPtr->nodeType == SYS_NODE_TYPE_BSC)
      {
         /*Update the upgraded version recieved as downloaded version 
          * in SwMNode Table */
         swMNodeTableIndex.nodeType = swOfferRespPtr->nodeType;
         swMNodeTableIndex.nodeIdentity = bscId;
         swMNodeTableIndex.chasisFrameId = swOfferRespPtr->frameId;
         swMNodeTableIndex.slotId = swOfferRespPtr->slotId;

         if (updateSwStatusInSwMNodeTable(swMNodeTableIndex,
             SW_DOWNLOAD_SUCCESS) !=CLIB_SUCCESS)  
         {
             LOG_PRINT(DEBUG,"updateSwStatusInSwMNodeTable getting failed");
         }
      }

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending failure ALARM: INFO_BPM_SW_DWNLD_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmOfferResp->alarmId;
      /* CS4.0 changes start */
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId; 
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId; 
      sysAlarmBuff.sysAlarm.alarmLevel = bpmOfferResp->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swOfferRespPtr->upgradeOfferResult;
      getStringForSwOfferErrorCause(swOfferRespPtr->upgradeOfferResult,
            swOfferRespPtr->upgradeVersion,swOfferRespPtr->nodeType,string,nodeInfo->chasisFrameId,nodeInfo->slotId);
   /* CS4.0 changes End */
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      /*Mantis Fix: 11303 Starts*/
      FillObjTypeFromNodeType(swOfferRespPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      /*Mantis Fix: 11303 Ends*/
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   } 
   LOG_PRINT(LOG_INFO,"swOfferRespHandler : Exit Function");
}

/******************************* Function  Header*****************************
   Function Name : swActivationRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation response recieved from OIL
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swActivationRespHandler()
{
   OamOilCfgSwActResp *swActRespPtr = NULL;
   /* CS4.0 changes start */
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoSwActResult *bpmSwAct = (OamOilCfgInfoSwActResult *)gCfgMsgBuf;
   nodeInfo = (OamOilCfgNodeInfo*)(&(bpmSwAct->nodeInfo));
   swActRespPtr = (OamOilCfgSwActResp*)(&(bpmSwAct->swMActResp));
   I_U8 type[4];
   I_U32 oprState;
   /* CS4.0 changes End */
   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 bscId;
   I_U8 string[MAX_STRING_LENGTH];

   LOG_PRINT(LOG_INFO,"Recieved Sw Activation Response");
   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swActRespPtr->actVersion);
   LOG_PRINT(LOG_INFO,"Result: %d ",swActRespPtr->actResult);
   /* CS4.0 HA changes start */
   LOG_PRINT(LOG_INFO,"FrameId: %d ",swActRespPtr->frameId);
   LOG_PRINT(LOG_INFO,"SlotId: %d ",swActRespPtr->slotId);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swActRespPtr->nodeType);
   LOG_PRINT(LOG_INFO,"RevertVersion: %d ",swActRespPtr->revVersion);

   /* Retrieve bscId from BSS Table */
   if (getBscId(&bscId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
      return;
   }

   sApiSwMNodeTableIndices.nodeType = swActRespPtr->nodeType /*SYS_NODE_TYPE_BSC*/;
   sApiSwMNodeTableIndices.nodeIdentity = bscId;
   sApiSwMNodeTableIndices.slotId = swActRespPtr->slotId ;
   sApiSwMNodeTableIndices.chasisFrameId = swActRespPtr->frameId;

   if (swActRespPtr->actResult == ACTIVATION_SUCCESSFUL)
   {
      /* Prepare Alarm */
      LOG_PRINT(LOG_INFO,"Preparing Success Alarm: INFO_BPM_SW_ACT_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId;
      /* CS4.0 changes start */
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId; 
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId; 
      sysAlarmBuff.sysAlarm.key3 = swActRespPtr->nodeType;
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swActRespPtr->actResult;
      convertNodeType(type,swActRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,
               "Sw Act for SwVer [%s] is Completed for NodeType [%s],ChasisFrameId [%d],SlotId [%d]",
               swActRespPtr->actVersion,type,nodeInfo->chasisFrameId,(nodeInfo->slotId-2)); //Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
      makeCopyOfActAlarm(&sysAlarmBuff);
      sendRequestForSpecificSlotAvailableReleases(swActRespPtr->nodeType, swActRespPtr->frameId, swActRespPtr->slotId);
      if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
               SW_ACTIVATION_SUCCESS) !=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
      }
   }//SUCCESSFUL
   else
   {
       if ( getStateForSlotIdIccTable( nodeInfo->slotId, &oprState ) != CLIB_SUCCESS )
       {
          LOG_PRINT(LOG_CRITICAL,"getStateForSlotIdIccTable Failed");
       }
       else
       {
          if( (oprState == BPM_CARDSTATE_OUT_OF_SERVICE) ||
              (gCurrentCardState  == BPM_CARDSTATE_OUT_OF_SERVICE) )
          {
             sendQuerySetCardOperState(BPM_CARDSTATE_STANDBY, nodeInfo->slotId);
             //return;
          }
          #if 0
          else if(gCurrentCardState  == BPM_CARDSTATE_OUT_OF_SERVICE) 
          {
             sendQuerySetCardOperState(BPM_CARDSTATE_ACTIVE, nodeInfo->slotId);
          } 
          #endif   
       } 
      /*Update status in SwMNode Table as Activation Failure */
      if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
               SW_ACTIVATION_FAILED) !=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
         /* CS4.0: Fix For Mantis 6764 */ 
         gSwActStatus = SW_ACTIVATION_FAILED;
        //return;
      }
      else
         LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success");  
      /* Sending Alarm */
      LOG_PRINT(LOG_INFO,"Sending Failure Alarm: INFO_BPM_SW_ACT_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwAct->alarmId;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      sysAlarmBuff.sysAlarm.key1 = nodeInfo->chasisFrameId; 
      sysAlarmBuff.sysAlarm.key2 = nodeInfo->slotId; 
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwAct->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swActRespPtr->actResult;
      getStringForSwActErrorCause(swActRespPtr->nodeType,swActRespPtr->actResult,
            swActRespPtr->actVersion,nodeInfo->chasisFrameId,(nodeInfo->slotId-2),string); //Changed for issue #0031513 Gaurav Sinha 13 JULY 2016
      /* CS4.0 Changes End */
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      /*Mantis Fix: 11303 Starts*/
      FillObjTypeFromNodeType(swActRespPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      /*Mantis Fix: 11303 Ends*/
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   } 
}

/******************************* Function  Header*****************************
   Function Name : swDeletionRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw deletion response recieved from OIL
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swDeletionRespHandler()
{
   OamOilCfgSwDelResp *swDelRespPtr = NULL;
   /* CS4.0 changes start */
   OamOilCfgNodeInfo *nodeInfo = NULL;
   OamOilCfgInfoDelResult *bpmSwDel = (OamOilCfgInfoDelResult *)gCfgMsgBuf;
   nodeInfo =  (OamOilCfgNodeInfo*)(&(bpmSwDel->nodeInfo));
   swDelRespPtr = (OamOilCfgSwDelResp*)(&(bpmSwDel->swMDelResp));
   I_U8 type[4];
   /* CS4.0 changes End */
   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   SwMNodeTableApi *swMNodeTableDbPtr = NULL;
   SwMTableIndices sApiSwMTableIndices;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 bscId;
   I_U8 string[MAX_STRING_LENGTH];
   I_U8 binaryPath[OAMS_CMD_PARAM_MAX_SIZE];
   I_S32 status;

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

   /* Retrieve bscId from BSS Table */

   if (getBscId(&bscId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed..");
      return;
   }
   if (swDelRespPtr->versionDelResult == DELETE_SUCCESSFUL)
   {
      /*Changes for copying from PP to CP: To be commented after SWMH moved to PP :Start*/
      if (swDelRespPtr->nodeType == SYS_NODE_TYPE_BIC ||
          swDelRespPtr->nodeType == SYS_NODE_TYPE_TRX ||
          swDelRespPtr->nodeType == SYS_NODE_TYPE_R2_BTS )
      {
         /* CS4.0 changes start */
         status = deleteReleaseFromCP(swDelRespPtr,nodeInfo->chasisFrameId,nodeInfo->slotId);
         /* CS4.0 changes End */
         LOG_PRINT(LOG_INFO,"status: %d",status);
         if (status != I_TRUE)
         {
            return;
         }
      }
      /*Changes for copying from PP to CP: End*/

      /*Delete the record of the requested sw version from T2 Table */
      if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"deleteSwMTable Success");

      /*Check if deletion request comes for BSC */
      if (swDelRespPtr->nodeType == SYS_NODE_TYPE_BSC)
      {
         sApiSwMNodeTableIndices.nodeType = swDelRespPtr->nodeType;
         /* CS4.0 HA changes start */
          sApiSwMNodeTableIndices.nodeIdentity = bscId; 
         sApiSwMNodeTableIndices.chasisFrameId = swDelRespPtr->frameId;
         sApiSwMNodeTableIndices.slotId = swDelRespPtr->slotId;
         /* CS4.0 HA changes end */
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
               LOG_PRINT(LOG_CRITICAL,"updateVersionDownloadedInSwMNodeTable Failed");
               if (swMNodeTableDbPtr != NULL)
                  free(swMNodeTableDbPtr);
               return;
            }
            else
               LOG_PRINT(LOG_INFO,"updateVersionDownloadedInSwMNodeTable Success");
         }
      }
      if (swMNodeTableDbPtr != NULL)
         free(swMNodeTableDbPtr);

      /* Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending Success Alarm: INFO_BPM_DEL_VERSION_SUCCESS");
      sysAlarmBuff.sysAlarm.sysalarmId = bpmSwDel->alarmId;
      /* CS4.0 changes start */
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      /* Fixed issue 7297 */
      sysAlarmBuff.sysAlarm.key1 = swDelRespPtr->frameId; /*nodeInfo->chasisFrameId*/ 
      sysAlarmBuff.sysAlarm.key2 = swDelRespPtr->slotId; /*nodeInfo->slotId*/
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwDel->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swDelRespPtr->versionDelResult;
      convertNodeType(type,swDelRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,
               "Sw Del for SwVer [%s] nodeType [%s] is Completed at ChasisFrameId [%d],SlotId [%d]",
               swDelRespPtr->delVersion,type,swDelRespPtr->frameId,swDelRespPtr->slotId); 
      /*Mantis Fix: 11303 Starts*/
      FillObjTypeFromNodeType(swDelRespPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      /*Mantis Fix: 11303 Ends*/

      cfgSendMessage((I_Void *)&sysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   }
   else
   {
      /*Changes for copying from PP to CP: To be commented after SWMH moved to PP :Start*/
      if (swDelRespPtr->nodeType == SYS_NODE_TYPE_BIC ||
          swDelRespPtr->nodeType == SYS_NODE_TYPE_TRX || 
          swDelRespPtr->nodeType == SYS_NODE_TYPE_R2_BTS )
      {
         status = checkUpgradeOfferFailure(swDelRespPtr,nodeInfo->chasisFrameId, nodeInfo->slotId,binaryPath);
        
         LOG_PRINT(LOG_INFO,"status: %d",status);
         if (status != I_TRUE)
         {
            LOG_PRINT(LOG_CRITICAL,"Failed to delete release from PP",binaryPath);
            return;
         }
      }
      /*Changes for copying from PP to CP: End*/

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
      sysAlarmBuff.sysAlarm.key1 = swDelRespPtr->frameId; 
      sysAlarmBuff.sysAlarm.key2 = swDelRespPtr->slotId; /*nodeInfo->slotId */
      sysAlarmBuff.sysAlarm.alarmLevel = bpmSwDel->alarmLevel; 
      sysAlarmBuff.sysAlarm.alarmReason = swDelRespPtr->versionDelResult;
      getStringForSwDelErrorCause(swDelRespPtr->versionDelResult,
            swDelRespPtr->delVersion,swDelRespPtr->nodeType,string,swDelRespPtr->frameId,swDelRespPtr->slotId);
      /* CS4.0 changes end */ 
      sysAlarmBuff.sysAlarm.infoStrLen = 
         sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
      /*Mantis Fix: 11303 Starts*/
      FillObjTypeFromNodeType(swDelRespPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      /*Mantis Fix: 11303 Ends*/
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   } 
}

/******************************* Function  Header*****************************
   Function Name : swDownloadSuccessHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw download Ack recieved from SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swDownloadSuccessHandler()
{
   OamsSwmhCfgSwDnldAck *swDnldAckPtr = NULL;
   swDnldAckPtr = (OamsSwmhCfgSwDnldAck *)gCfgMsgBuf;
   SwMTableApi *swMTablePtr = NULL;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   SwMTableIndices sApiSwMTableIndices;
   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   sApiSwMNodeTableIndices.nodeType = swDnldAckPtr->nodeType;
   sApiSwMNodeTableIndices.nodeIdentity = swDnldAckPtr->nodeIdentity;
   I_U8 slotId;
   I_U8 chasisFrameId;
   sApiSwMTableIndices.nodeType = swDnldAckPtr->nodeType;
   strcpy(sApiSwMTableIndices.swVersion,swDnldAckPtr->swVersion);
   I_U32 swDownloadCount = ZERO;
   I_U8 type[4];
   I_S32 ret = CFG_FAILURE;
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 

   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swDnldAckPtr->swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swDnldAckPtr->nodeType);
   LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swDnldAckPtr->nodeIdentity);

   /* CS4.0 HA changes Start */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMTableIndices.slotId = slotId;

   /* CS4.0 HA changes End */

   /*Update status in SwMNode Table as Download Success */
   //if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
   //          SW_DOWNLOAD_SUCCESS) !=CLIB_SUCCESS)
   sendRequestForSpecificSlotAvailableReleases(swDnldAckPtr->nodeType, chasisFrameId, slotId);
   if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_DOWNLOAD_SUCCESS,SW_NO_ACTION, " ") != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success");   

   /*Retreive the count value from SwM Table */
   if (getSwMTable(&sApiSwMTableIndices,&swMTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwMTable DB call is getting failed..");
      return;
   }

   /*Decrement the swDownloadCount value in T3 table for requested sw version*/
   swDownloadCount = swMTablePtr->swDownloadCount - 1;   
   if (updateCountInSwMTable(sApiSwMTableIndices,swDownloadCount) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
      if (swMTablePtr != NULL)
         free(swMTablePtr);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

   /* Send Alarm */
   LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_SW_DWNLD_COMPLETED");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_DWNLD_COMPLETED;
   sysAlarmBuff.sysAlarm.key1 = swDnldAckPtr->nodeIdentity;
   if (swDnldAckPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      trxTableIndices.ptrxId = swDnldAckPtr->nodeIdentity; 
      if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
      {
          LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",swDnldAckPtr->nodeIdentity);
          return;
      }
      sysAlarmBuff.sysAlarm.key1 = trxTableApi->bicId;
      sysAlarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;;
      free(trxTableApi);
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
   }
   else if (swDnldAckPtr->nodeType == SYS_NODE_TYPE_BIC)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   else if (swDnldAckPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   convertNodeType(type,swDnldAckPtr->nodeType);
   sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,
            "Sw Dwnld for SwVer [%s] NodeType [%s] is Completed on NodeId [%u]",
            swDnldAckPtr->swVersion,type,swDnldAckPtr->nodeIdentity); 
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
   if (swMTablePtr != NULL)
      free(swMTablePtr);
}

/******************************* Function  Header*****************************
   Function Name : swDownloadFailureHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw download Nack recieved from SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swDownloadFailureHandler()
{
   OamsSwmhCfgSwDnldNack *swDnldNackPtr = NULL;
   swDnldNackPtr = (OamsSwmhCfgSwDnldNack *)gCfgMsgBuf;
   SwMTableApi *swMTablePtr = NULL;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   SwMTableIndices sApiSwMTableIndices;
   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   sApiSwMNodeTableIndices.nodeType = swDnldNackPtr->nodeType;
   sApiSwMNodeTableIndices.nodeIdentity = swDnldNackPtr->nodeIdentity;
   sApiSwMTableIndices.nodeType = swDnldNackPtr->nodeType;
   strcpy(sApiSwMTableIndices.swVersion,swDnldNackPtr->swVersion);
   I_U32 swDownloadCount = ZERO;
   I_U8 string[MAX_STRING_LENGTH];
   I_S8 oprStatus[] = "Sw Dnld";
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 

   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swDnldNackPtr->swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swDnldNackPtr->nodeType);
   LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swDnldNackPtr->nodeIdentity);
   LOG_PRINT(LOG_INFO,"NackCause: %d ",swDnldNackPtr->nackCause);

    /* CS4.0 HA changes Start */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   sApiSwMTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMTableIndices.slotId = slotId;
   /* CS4.0 HA changes End */

   sendRequestForSpecificSlotAvailableReleases(swDnldNackPtr->nodeType, chasisFrameId, slotId);
   /*Update status in SwMNode Table as Download Failure */
   if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_DOWNLOAD_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
   //if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
   //         SW_DOWNLOAD_FAILED) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success");   

   /*Retreive the count value from SwM Table */
   if (getSwMTable(&sApiSwMTableIndices,&swMTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwMTable DB call is getting failed..");
      return;
   }

   /*Decrement the swDownloadCount value in T3 table for requested sw version*/
   swDownloadCount = swMTablePtr->swDownloadCount - 1;   
   if (updateCountInSwMTable(sApiSwMTableIndices,swDownloadCount) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
      if (swMTablePtr != NULL)
         free(swMTablePtr);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

   /* Send Alarm */
   LOG_PRINT(LOG_INFO,"Sending failure alarm: EVENT_SW_DWNLD_FAILED");
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_DWNLD_FAILED;
   sysAlarmBuff.sysAlarm.key1 = swDnldNackPtr->nodeIdentity;
   if (swDnldNackPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      trxTableIndices.ptrxId = swDnldNackPtr->nodeIdentity; 
      if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
      {
          LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",swDnldNackPtr->nodeIdentity);
          return;
      }
      sysAlarmBuff.sysAlarm.key1 = trxTableApi->bicId;
      sysAlarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;;
      free(trxTableApi);
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
   }
   else if (swDnldNackPtr->nodeType == SYS_NODE_TYPE_BIC)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   else if (swDnldNackPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }

   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
   sysAlarmBuff.sysAlarm.alarmReason = swDnldNackPtr->nackCause;
   getStringForSwmhErrorCause(swDnldNackPtr->nackCause,oprStatus,
         swDnldNackPtr->swVersion,swDnldNackPtr->nodeType,
         swDnldNackPtr->nodeIdentity,string);
   sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
   if (swMTablePtr != NULL)
      free(swMTablePtr);
}

/******************************* Function  Header*****************************
   Function Name : swActivationSuccessHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation Ack recieved from SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swActivationSuccessHandler()
{
   I_U8 type[4];
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 
   I_U32 ptrxId;

   OamsSwmhCfgSwActAck *swActAckPtr = NULL;
   swActAckPtr = (OamsSwmhCfgSwActAck *)gCfgMsgBuf;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   sApiSwMNodeTableIndices.nodeType = swActAckPtr->nodeType;
   sApiSwMNodeTableIndices.nodeIdentity = swActAckPtr->nodeIdentity;

   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swActAckPtr->swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swActAckPtr->nodeType);
   LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swActAckPtr->nodeIdentity);
    /* CS4.0 HA changes Start */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   /* CS4.0 HA changes End */


   /*Update status in SwMNode Table as Activation Success */
   sendRequestForSpecificSlotAvailableReleases(swActAckPtr->nodeType, chasisFrameId, slotId);
   if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_ACTIVATION_SUCCESS,SW_NO_ACTION, " ") != CLIB_SUCCESS)
   //if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
   //         SW_ACTIVATION_SUCCESS) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success");   

   /* Send Alarm */
   LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_SW_ACT_COMPLETED");   
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_ACT_COMPLETED;
   sysAlarmBuff.sysAlarm.key1 = swActAckPtr->nodeIdentity;

   if (swActAckPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      trxTableIndices.ptrxId = swActAckPtr->nodeIdentity; 
      if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
      {
          LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",swActAckPtr->nodeIdentity);
          return;
      }
      sysAlarmBuff.sysAlarm.key1 = trxTableApi->bicId;
      sysAlarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;;
      free(trxTableApi);
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
   }
   else if (swActAckPtr->nodeType == SYS_NODE_TYPE_BIC)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   else if (swActAckPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   convertNodeType(type,swActAckPtr->nodeType);
   sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString, 
            "Sw Act for SwVer [%s] NodeType [%s] is Completed on NodeId [%u]",
            swActAckPtr->swVersion,type,swActAckPtr->nodeIdentity); 
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
}

/******************************* Function  Header*****************************
   Function Name : swActivationFailureHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation Nack recieved from SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void swActivationFailureHandler()
{
   OamsSwmhCfgSwActNack *swActNackPtr = NULL;
   swActNackPtr = (OamsSwmhCfgSwActNack *)gCfgMsgBuf;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
   sApiSwMNodeTableIndices.nodeType = swActNackPtr->nodeType;
   sApiSwMNodeTableIndices.nodeIdentity = swActNackPtr->nodeIdentity;
   I_U8 string[MAX_STRING_LENGTH];
   I_S8 oprStatus[] = "Sw Act";
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 

   LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swActNackPtr->swVersion);
   LOG_PRINT(LOG_INFO,"NodeType: %d ",swActNackPtr->nodeType);
   LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swActNackPtr->nodeIdentity);
   LOG_PRINT(LOG_INFO,"NackCause: %d ",swActNackPtr->nackCause);
    /* CS4.0 HA changes Start */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
   sApiSwMNodeTableIndices.slotId = slotId;
   /* CS4.0 HA changes End */

   /*Update status in SwMNode Table as Activation Failure */
   sendRequestForSpecificSlotAvailableReleases(swActNackPtr->nodeType, chasisFrameId, slotId);
   if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_ACTIVATION_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
   //if (updateSwStatusInSwMNodeTable(sApiSwMNodeTableIndices,
   //         SW_ACTIVATION_FAILED) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusInSwMNodeTable Failed");
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateSwStatusInSwMNodeTable Success");   

   /* Send Alarm */
   LOG_PRINT(LOG_INFO,"Sending failure alarm: EVENT_SW_ACT_FAILED");   
   sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_ACT_FAILED;
   sysAlarmBuff.sysAlarm.key1 = swActNackPtr->nodeIdentity;
   if (swActNackPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      trxTableIndices.ptrxId = swActNackPtr->nodeIdentity; 
      if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
      {
          LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",swActNackPtr->nodeIdentity);
          return;
      }
      sysAlarmBuff.sysAlarm.key1 = trxTableApi->bicId;
      sysAlarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;;
      free(trxTableApi);
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
   }
   else if (swActNackPtr->nodeType == SYS_NODE_TYPE_BIC)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   else if (swActNackPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
   }
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
   sysAlarmBuff.sysAlarm.alarmReason = swActNackPtr->nackCause;
   getStringForSwmhErrorCause(swActNackPtr->nackCause,oprStatus,
         swActNackPtr->swVersion,swActNackPtr->nodeType,
         swActNackPtr->nodeIdentity,string);
   sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
}

/******************************* Function  Header*****************************
   Function Name : sendRequestForAvailableReleases()
Parameters    : None
Return type   : I_Void
Purpose       : Sends request for available releases present on BSC platform
for BSC/BIC/TRX/BTS
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void sendRequestForAvailableReleases()
{
   //gAvailReleaseRspFlag = ZERO;  //Mantis-Fix : 0016214
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;
   I_U8 iccId[MAX_ICC];
   I_U8 chasisId[MAX_EIC];
   I_U32 count =ZERO;
   I_U32 index = ZERO;
   I_CHAR *tmpBicPath = NULL;
   I_CHAR *tmpTrxPath = NULL;
   I_CHAR *tmpBtsPath = NULL;

   OamsCfgOilAvailableReleasesReq  availableReleasesReqBuff;  
   IccCardInfoTableApi *cardInfoPtr = NULL;
   IccCardInfoTableIndices cardInfoIndices;
   
   /* CS4.0 HA changes Start */
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   if (getIccIdChasisId( iccId, chasisId, &count ) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getIccIdChasisId call is getting failed.."); 
      return;
   }
   LOG_PRINT(LOG_CRITICAL,"Count %d",count); 
   for( index = 0; index < count; index++ )
   {
      LOG_PRINT(DEBUG,"In getIccIdChasisId returned ChasisId[%d] slotId[%d]",chasisId[index], iccId[index]); 
   }

   availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_BSC;
   for( index = 0; index < count; index++ )
   { 
      ret = sendRequestForBscAvailableReleases(chasisId[index],iccId[index]);
      if(ret == CFG_SUCCESS)
         gAvailReleaseRspFlag++;
   			 LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented after sendRequestForBscAvailableReleases()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
   }

   availableReleasesReqBuff.frameId = chasisFrameId;
   availableReleasesReqBuff.slotId = slotId;


   //if(gCfgStandbyToActive != I_TRUE)
   //{ 
     availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_BIC;
     LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for BIC for ChasisFrameId[%d],SlotId[%d]",chasisFrameId,slotId);
        cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
              sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
              OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
     gAvailReleaseRspFlag++;
   	LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented after OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for BIC ()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
     
     availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_TRX;
     LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for TRX for ChasisFrameId[%d],SlotId[%d]",chasisFrameId,slotId);
        cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
              sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
              OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
     gAvailReleaseRspFlag++;
   	LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented after OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for TRX ()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
     
     availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_R2_BTS;
     LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for BTS for ChasisFrameId[%d],SlotId[%d]",chasisFrameId,slotId);
        cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
              sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
              OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
     gAvailReleaseRspFlag++;
   	LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) incremented after OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for BTS()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS
     /* CS4.0 Changes Start */
   //} 
#if 0
   else
   {
      //TRX
      tmpTrxPath = getenv("TRX_REL_PATH");
      if (tmpTrxPath == NULL)
      {
         LOG_PRINT(INFO,"TRX_REL_PATH is not Set");
         if ((trxPathName = malloc(32)) == NULL)
         {
            LOG_PRINT(CRITICAL,"TRX_REL_PATH: Memory Allocation failure");
            exit(0); 
         }
         strcpy(trxPathName,"/tmp/SwReleases/Trx");
      }
      else
      {
         LOG_PRINT(INFO,"TRX_REL_PATH is Set");
         if ((trxPathName = malloc(strlen(tmpTrxPath))) == NULL)
         {
            LOG_PRINT(CRITICAL,"TRX_REL_PATH: Memory Allocation failure");
            exit(0); 
         }
         strcpy(trxPathName,tmpTrxPath);

      }
      //BIC
      tmpBicPath = getenv("BIC_REL_PATH");
      if (tmpBicPath == NULL)
      {
         LOG_PRINT(INFO,"BIC_REL_PATH is not Set");
         /*bicPathName = malloc(32);*/ /* Fixed in CS4.0 */
         if ((bicPathName = malloc(32)) == NULL)
         {
            LOG_PRINT(CRITICAL,"BIC_REL_PATH: Memory Allocation failure");
            exit(0); 
         }
         strcpy(bicPathName,"/tmp/SwReleases/Bic");
      }
      else
      {
         LOG_PRINT(INFO,"BIC_REL_PATH is Set");
         /*bicPathName = malloc(32);*/ /* Fixed in CS4.0 */
         if ((bicPathName = malloc(strlen(tmpBicPath))) == NULL)
         {
            LOG_PRINT(CRITICAL,"BIC_REL_PATH: Memory Allocation failure");
            exit(0); 
         }
         strcpy(bicPathName,tmpBicPath);
      }
      //R2 BTS 
      tmpBtsPath = getenv("BTS_REL_PATH");
      if (tmpBtsPath == NULL)
      {
         LOG_PRINT(INFO,"BTS_REL_PATH is not Set");
         if ((btsPathName = malloc(32)) == NULL)
         {
            LOG_PRINT(CRITICAL,"BTS_REL_PATH: Memory Allocation failure");
            exit(0); 
         }
         strcpy(btsPathName,"/tmp/SwReleases/Bts");
      }
      else
      {
         LOG_PRINT(INFO,"BTS_REL_PATH is Set");
         if ((btsPathName = malloc(strlen(tmpBtsPath))) == NULL)
         {
            LOG_PRINT(CRITICAL,"BTS_REL_PATH: Memory Allocation failure");
            exit(0); 
         }
         strcpy(btsPathName,tmpBtsPath);
      }
   }
#endif
   sendRequestForEicAvailableReleases();
   /* CS4.0 Changes End */

   /*BSC R2.0 Changes Starts*/
   sendRequestForDspAvailableReleases();
   /*BSC R2.0 Changes Ends*/
   /*BSC R2.8 Changes Starts*/
   sendRequestForEicDspAvailableReleases();
   /*BSC R2.8 Changes Ends*/
}

/******************************* Function  Header*****************************
   Function Name : availableReleasesRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : populate SwM table with releases recieved from platform
for BSC/BIC/TRX/BTS
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void availableReleasesRespHandler()
{
   OamOilCfgAvailableReleasesResp *availableReleasesRespPtr = NULL;
   /* CS4.0 Changes start */
   OamOilCfgInfoAvailableVersion *bpmAvailVersion = (OamOilCfgInfoAvailableVersion *)gCfgMsgBuf;
   availableReleasesRespPtr = (OamOilCfgAvailableReleasesResp *)(&(bpmAvailVersion->swMAvailResp));
   /* CS4.0 Changes End */
   SwMTableApi swMTableBuff;
   SwMNodeTableIndices sApiSwMNodeTableIndices;
   I_U32 count = 0, bscId,nodeType =0;
   I_U8 cpBinaryPath[OAMS_CMD_PARAM_MAX_SIZE];
   I_S32 status;
   I_CHAR *tmpBicPath = NULL;
   I_CHAR *tmpTrxPath = NULL;
   I_CHAR *tmpBtsPath = NULL;
   LOG_PRINT(LOG_INFO,"Recieved NodeType: %d availVersionResult:%d",availableReleasesRespPtr->nodeType,
       availableReleasesRespPtr->availVersionResult);
   LOG_PRINT(LOG_INFO,"FrameId: %d, SlotId: %d ",availableReleasesRespPtr->frameId,availableReleasesRespPtr->slotId);
   gAvailReleaseRspFlag--;
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) decremented in availableReleasesRespHandler()",gAvailReleaseRspFlag); //CLOUD TMP PRINTS

   /*Changes for copying from PP to CP: To be commented after SWMH moved to PP :Start*/
   if( availableReleasesRespPtr->availVersionResult == OPERATION_SUCCESS )
   {
      nodeType = availableReleasesRespPtr->nodeType;

      if(deleteDataForNodeTypeFromSwMTable(&nodeType) != CLIB_SUCCESS)
      {
         LOG_PRINT(DEBUG,"deleteDataForNodeTypeFromSwMTable failed");

      }    
   if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_BIC ||
         availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_TRX || 
         availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_R2_BTS )
   {
      if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_TRX)
      {
         tmpTrxPath = getenv("TRX_REL_PATH");
         if (tmpTrxPath == NULL)
         {
            LOG_PRINT(INFO,"TRX_REL_PATH is not Set");
            if ((trxPathName = malloc(32)) == NULL)
            {
               LOG_PRINT(CRITICAL,"TRX_REL_PATH: Memory Allocation failure");
               exit(0); 
            }
            strcpy(trxPathName,"/tmp/SwReleases/Trx");
         }
         else
         {
            LOG_PRINT(INFO,"TRX_REL_PATH is Set");
            if ((trxPathName = malloc(strlen(tmpTrxPath))) == NULL)
            {
               LOG_PRINT(CRITICAL,"TRX_REL_PATH: Memory Allocation failure");
               exit(0); 
            }
            strcpy(trxPathName,tmpTrxPath);

         }
      }
      else if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_BIC)
      {
         tmpBicPath = getenv("BIC_REL_PATH");
         if (tmpBicPath == NULL)
         {
            LOG_PRINT(INFO,"BIC_REL_PATH is not Set");
            /*bicPathName = malloc(32);*/ /* Fixed in CS4.0 */
            if ((bicPathName = malloc(32)) == NULL)
            {
               LOG_PRINT(CRITICAL,"BIC_REL_PATH: Memory Allocation failure");
               exit(0); 
            }
            strcpy(bicPathName,"/tmp/SwReleases/Bic");
         }
         else
         {
            LOG_PRINT(INFO,"BIC_REL_PATH is Set");
            /*bicPathName = malloc(32);*/ /* Fixed in CS4.0 */
            if ((bicPathName = malloc(strlen(tmpBicPath))) == NULL)
            {
               LOG_PRINT(CRITICAL,"BIC_REL_PATH: Memory Allocation failure");
               exit(0); 
            }
            strcpy(bicPathName,tmpBicPath);
         }
      }
      else if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
      {
         tmpBtsPath = getenv("BTS_REL_PATH");
         if (tmpBtsPath == NULL)
         {
            LOG_PRINT(INFO,"BTS_REL_PATH is not Set");
            if ((btsPathName = malloc(32)) == NULL)
            {
               LOG_PRINT(CRITICAL,"BTS_REL_PATH: Memory Allocation failure");
               exit(0); 
            }
            strcpy(btsPathName,"/tmp/SwReleases/Bts");
         }
         else
         {
            LOG_PRINT(INFO,"BTS_REL_PATH is Set");
            if ((btsPathName = malloc(strlen(tmpBtsPath))) == NULL)
            {
               LOG_PRINT(CRITICAL,"BTS_REL_PATH: Memory Allocation failure");
               exit(0); 
            }
            strcpy(btsPathName,tmpBtsPath);
         }
      }


      status = delNonExistingAvailRelFromCP(availableReleasesRespPtr);
      if (status != I_TRUE)
      {
         exit(0); 
      }
   }
   /*Changes for copying from PP to CP: End*/

   if (availableReleasesRespPtr->numVersion == ZERO)
   {
      LOG_PRINT(LOG_DEBUG,"No version present on the BSC Card for NodeType: %d",
            availableReleasesRespPtr->nodeType );
      return;
   }

   if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_BSC)
   {
      for (count = 0;count < 3;count++)
      { 
         LOG_PRINT(INFO,"Recieved swVersion: %s",availableReleasesRespPtr->availSwVersions[count]);    
         if (strlen(availableReleasesRespPtr->availSwVersions[count]) == ZERO)
         {
            LOG_PRINT(INFO,"No BSC release present for count: %d",count + 1);    
         }
         else
         {
            swMTableBuff.nodeType = availableReleasesRespPtr->nodeType;
            /* CS4.0 HA changes start */
            swMTableBuff.chasisFrameId = availableReleasesRespPtr->frameId;
            swMTableBuff.slotId = availableReleasesRespPtr->slotId;
            /* CS4.0 HA changes start */
            strcpy(swMTableBuff.swVersion,
                  availableReleasesRespPtr->availSwVersions[count]);
            memcpy(swMTableBuff.binaryPath,availableReleasesRespPtr->availSwBinaryPath[count],
                  OAMS_CMD_PARAM_MAX_SIZE); 
            swMTableBuff.swDownloadCount = ZERO;
            swMTableBuff.deletionInProgress = I_FALSE;
            if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
            {
               if ( updateSwMTable(&swMTableBuff ) != CLIB_SUCCESS )
                   LOG_PRINT(LOG_MAJOR,"updateSwMTable DB call is getting failed..");
            }
            else
               LOG_PRINT(LOG_INFO,"insertSwMTable Successful");          
         }

      }
   }
   else
   {    
      for (count = 0;count < availableReleasesRespPtr->numVersion;count++)
      { 
         swMTableBuff.nodeType = availableReleasesRespPtr->nodeType;
         /* CS4.0 HA changes start */
         swMTableBuff.chasisFrameId = availableReleasesRespPtr->frameId;
         swMTableBuff.slotId = availableReleasesRespPtr->slotId;
         /* CS4.0 HA changes start */
         strcpy(swMTableBuff.swVersion,
               availableReleasesRespPtr->availSwVersions[count]);

         /*Changes for copying from PP to CP: To be commented after SWMH moved to PP :Start*/
         if (copyReleaseFromPPToCP(availableReleasesRespPtr->availSwBinaryPath[count],
                  availableReleasesRespPtr->availSwVersions[count],
                  availableReleasesRespPtr->nodeType,cpBinaryPath) != I_TRUE)
         {
            exit(0); 
         }
         memcpy(swMTableBuff.binaryPath,cpBinaryPath,OAMS_CMD_PARAM_MAX_SIZE);
         /*Changes for copying from PP to CP: End*/

         /*Changes for copying from PP to CP: Uncomment this part of code :Start*/
         /* memcpy(swMTableBuff.binaryPath,availableReleasesRespPtr->availSwBinaryPath[count],
             OAMS_CMD_PARAM_MAX_SIZE); */
         /*Changes for copying from PP to CP: End*/
         swMTableBuff.swDownloadCount = ZERO;
         swMTableBuff.deletionInProgress = I_FALSE;
         if (insertSwMTable(&swMTableBuff) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"insertSwMTable DB call is getting failed..");
         }
         else
            LOG_PRINT(LOG_INFO,"insertSwMTable Successful");          
      }
   }

   if (availableReleasesRespPtr->nodeType == SYS_NODE_TYPE_BSC)
   {
      /* CS4.0 HA changes start */
      /* Retrieve bscId from BSS Table */
      if (getBscId(&bscId) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG,"No row present in BSS Table");
         sApiSwMNodeTableIndices.nodeIdentity = 0;
      }
      else
      {
         sApiSwMNodeTableIndices.nodeIdentity = bscId;
      }
      sApiSwMNodeTableIndices.chasisFrameId = availableReleasesRespPtr->frameId;
      sApiSwMNodeTableIndices.slotId = availableReleasesRespPtr->slotId;
      /* CS4.0 HA changes end */
      sApiSwMNodeTableIndices.nodeType = availableReleasesRespPtr->nodeType;
      if (updateVersionActiveInactiveDnldedInSwMNodeTable(
               sApiSwMNodeTableIndices,
               availableReleasesRespPtr->availSwVersions[0],
               availableReleasesRespPtr->availSwVersions[1],
               availableReleasesRespPtr->availSwVersions[2]) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"updateVersionActiveInactiveDnldedInSwMNodeTable Failed");
      }
      else
         LOG_PRINT(LOG_INFO,"updateVersionActiveInactiveDnldedInSwMNodeTable Success");
   }
   if ( gCfgActAlarmBuf != NULL )
   { 
      sendActivationAlarm(availableReleasesRespPtr);
   }
   }
   /* CS4.0 Changes start */
   sendUpgradeAlarm();
   /* CS4.0 Changes End */
   LOG_PRINT(LOG_INFO,"gAvailReleaseRspFlag(%d) gCfgState(%d) in availableReleasesRespHandler()",gAvailReleaseRspFlag,gCfgState); //CLOUD TMP PRINTS
   if (gAvailReleaseRspFlag == ZERO && gCfgState == CFG_BPM_SW_QUERY && gCfgStandbyToActive == I_FALSE)
   {
      goToReadyState();
   }
}

/******************************* Function  Header*****************************
   Function Name : getStringForSwmhInstallFailureCause()
Parameters    : I_U32 cause,I_S8 *oprStat,I_U8 *swVersion,I_U32 nodeType,
I_U32 nodeIdentity,I_U8 *string
Return type   : I_Void
Purpose       : Return a string corresponding to the failure cause for 
download and activation error causes from SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void getStringForSwmhInstallFailureCause(I_U32 cause,I_S8 *oprStat,I_U8 *swVersion,I_U32 nodeType,I_U32 nodeIdentity,I_U8 *string)

{
   I_U8 type[4];
   convertNodeType(type,nodeType);
   switch(cause)
   {
     case CAUSE_SW_PACK_ALREADY_EXIST:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Package Already Exist ",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_FAULTY_FTP_SERVER_IP_ADDR:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Faulty FTP server Ip Address",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_FAULTY_USRNAME_PASSWRD_COMB:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Faulty User Name and Password Combination",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_FAULTY_PATH_AND_FILENAME:
       sprintf(string,"%s for SwVer [%s] NodeType [%s] NodeId [%u] Faulty Path and FileName ",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_FLASH_RESOURCE_NOT_AVAILABLE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Flash Resource not Available",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_FTP_RESOURCE_NOT_AVAILABLE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s] NodeId [%u] FTP resource not available ",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_FTP_FAILURE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] FTP Failure",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_UNPACK_NOT_OK:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Unpack not OK",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     default:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed with Invalid Cause Value",
           oprStat,swVersion,type,nodeIdentity);       
       break;
   }
}

/******************************* Function  Header*****************************
   Function Name : getStringForSwmhErrorCause()
Parameters    : I_U32 cause,I_S8 *oprStat,I_U8 *swVersion,I_U32 nodeType,
I_U32 nodeIdentity,I_U8 *string
Return type   : I_Void
Purpose       : Return a string corresponding to the failure cause for 
download and activation error causes from SWMH
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void getStringForSwmhErrorCause(I_U32 cause,I_S8 *oprStat,I_U8 *swVersion,I_U32 nodeType,I_U32 nodeIdentity,I_U8 *string)

{
   I_U8 type[4];
   convertNodeType(type,nodeType);
   switch(cause)
   {
     case CAUSE_INCORRECT_MESSAGE_STRUCTURE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Msg Struct Incorrect",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_SW_IMAGE_ALREADY_EXITS:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Image Already Exists",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_ACTIVE_SW_VER_APPROVAL_ONGOING:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Ver Approve Ongoing",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_INSUFFICIENT_MEMORY:
       sprintf(string,"%s for SwVer [%s] NodeType [%s] NodeId [%u] Failed as Insufficient Memory",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_MESSAGE_CANNOT_PERFORMED:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Msg can't Performed",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_RESOURCE_NOT_AVAILABLE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s] NodeId [%u] Failed as Resource Not Avail",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_CHEKSUM_FAILED:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Checksum Fail",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_SW_IMAGE_NOT_EXIST:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Image Not Exist",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_SW_IMAGE_CANNOT_ACTIVATE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Image Can't Activate",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_TRX_LAPD_NOT_CONNECTED:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Trx Lapd Not Connected",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_BIC_NOT_CONNECTED:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Bic Not Connected",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_TRX_LAPD_LINK_DOWN:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Trx Lapd Link Down",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_BIC_CONNECTION_LOST:
       sprintf(string,"%s for SwVer [%s] NodeType [%s],NodeId [%u] Failed as Bic Connection Lost",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_LOAD_DATA_INIT_ACK_TIMER_EXPIRY:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Init Ack Timer Expired",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_LOAD_DATA_SEG_ACK_TIMER_EXPIRY:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Seg Ack Timer Expired",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_LOAD_DATA_END_ACK_TIMER_EXPIRY:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as End Ack Timer Expired",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_ACT_SW_VERSION_MISMATCH:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Sw Version Mismatch",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_LOAD_DATA_ABORT:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Load Data Abort",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_FILE_SYSTEM_ERROR:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Error in File System",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_INTERNAL_DB_ERROR:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Internal DB Error",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_ZERO_FILE_SIZE:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as File Size is Zero",
           oprStat,swVersion,type,nodeIdentity);       
       break;
       /*      case CAUSE_SW_IMAGE_IS_DEFAULT:
               sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Image is Default",
               oprStat,swVersion,type,nodeIdentity);       
               break;
        */
     case CAUSE_COMPLETE_FILE_NOT_RECEIVED:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Complete File Not Received",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case CAUSE_SW_IMAGE_IS_EXECUTING:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Image is Already Executing",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case OAMS_CAUSE_BTS_LAPD_LINK_DOWN:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as BTS Lapd Link Down",
           oprStat,swVersion,type,nodeIdentity);       
       break;
     case  CAUSE_SW_PACK_COMB_ALREADY_ACT:         
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Package combination is already active ",oprStat,swVersion,type,nodeIdentity);       
       break; 
     case CAUSE_SW_PACK_COMB_NOT_INSTALLED:       
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as Package combination is not installed ",oprStat,swVersion,type,nodeIdentity);       
       break; 
     case CAUSE_SW_TRAIL_ALREADY_IN_PROG:         
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as trial already in progress ",oprStat,swVersion,type,nodeIdentity);       
       break; 
     case CAUSE_SW_NO_TRIAL_ONGOING:              
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed as no trial is ongoing",oprStat,swVersion,type,nodeIdentity);       
       break; 
     default:
       sprintf(string,"%s for SwVer [%s],NodeType [%s],NodeId [%u] Failed with Invalid Cause Value",
           oprStat,swVersion,type,nodeIdentity);       
       break;
   }
}

/******************************* Function  Header*****************************
   Function Name : cfgInitSwMNodeTable()
Parameters    : None
Return type   : I_Void
Purpose       : Initialize SwMNode Table with the BIC/TRX/BSC present in the 
system.
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_Void cfgInitSwMNodeTable()
{
   SwMNodeTableApi swMNodeTableBuf;
   BicTrxTimeslotUsageTableApi *bicTrxTsUsagePtr = NULL;
   BicTableApi *bicTablePtr = NULL;
   BicTrxTimeslotUsageTableApi *tempBicTrxTsUsagePtr = NULL;
   BicTableApi *tempBicTablePtr = NULL;
   TrxTableApi *trxTablePtr = NULL;
   TrxTableApi *tempTrxTablePtr = NULL;
   InFrameTrxE1TsTableApi *inFrameTrxE1TsTablePtr = NULL;
   InFrameTrxE1TsTableIndices inFrameTrxE1TsTableIndex;
   I_U32 outRows,count,outRowsBicTable;
   I_U16 outSize,outSizeBicTable;
   I_U32 bscId;
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;
   I_U8 iccId[MAX_ICC];
   I_U8 chasisId[MAX_ICC];
   I_U32 index;

   LOG_PRINT(LOG_INFO,"Entered cfgInitSwMNodeTable From initializingCfg ");
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   if(gCfgStandbyToActive != I_TRUE )
   {


     /*Insert one record in SwMNode table for each BIC/TRX/BTS */
     if (getallBicTrxTimeslotUsageTable(&bicTrxTsUsagePtr,&outRows,&outSize) != 
         CLIB_SUCCESS)
     {
       LOG_PRINT(LOG_DEBUG,"No rows present in the BicTrxTimeslotUsage Table");



     }
     else
     {
       for(count = 0;count < outRows;count++)
       {
         tempBicTrxTsUsagePtr = (BicTrxTimeslotUsageTableApi *)
           ((I_U8 *)bicTrxTsUsagePtr + (count*outSize));
         if (tempBicTrxTsUsagePtr->tsUser == TS_USAGE_BIC)
           swMNodeTableBuf.nodeType = SYS_NODE_TYPE_BIC;
         else if (tempBicTrxTsUsagePtr->tsUser == TS_USAGE_BICTRX)
           swMNodeTableBuf.nodeType = SYS_NODE_TYPE_TRX;
         else if (tempBicTrxTsUsagePtr->tsUser == TS_USAGE_BTS)
           swMNodeTableBuf.nodeType = SYS_NODE_TYPE_R2_BTS;
         else if (tempBicTrxTsUsagePtr->tsUser == TS_USAGE_BTS_TRX)
           continue;
         swMNodeTableBuf.nodeIdentity = tempBicTrxTsUsagePtr->bicOrTrxId;
         swMNodeTableBuf.e1Num = tempBicTrxTsUsagePtr->e1Id;
         swMNodeTableBuf.lapdTs = tempBicTrxTsUsagePtr->lapdTs;
         strcpy(swMNodeTableBuf.swVersionActive,"");
         strcpy(swMNodeTableBuf.swVersionInactive,"");
         strcpy(swMNodeTableBuf.swVersionDownloaded,"");
         strcpy(swMNodeTableBuf.swVersionNew,"");
         swMNodeTableBuf.swAction = SW_NO_ACTION;
         swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
         swMNodeTableBuf.chasisFrameId = chasisFrameId;
         swMNodeTableBuf.slotId = slotId;
         if (insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
         {
           LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed");
           free(bicTrxTsUsagePtr);
           return;
         }
         else
         {
           LOG_PRINT(LOG_INFO,"insertSwMNodeTable Successfull");
         }
       }
       if (bicTrxTsUsagePtr != NULL)
         free(bicTrxTsUsagePtr);
     }

     //Veena Prasad  
     if (getallBicTable(&bicTablePtr,&outRowsBicTable, &outSizeBicTable) != CLIB_SUCCESS ) {
           LOG_PRINT(LOG_INFO,"No Bts configured ");

     }
     else {
           LOG_PRINT(LOG_INFO, "%d Bts configured ", outRowsBicTable);
       for(count = 0;count < outRowsBicTable;count++)
       {
         tempBicTablePtr = (BicTableApi *)
           ((I_U8 *)bicTablePtr + (count*outSizeBicTable));
         if (tempBicTablePtr->btsType == R3_BTS)
           swMNodeTableBuf.nodeType = SYS_NODE_TYPE_R3_BTS;
         else if (tempBicTablePtr->btsType == R2_BTS_IP)
           swMNodeTableBuf.nodeType = SYS_NODE_TYPE_R2_BTS_IP;
         else 
           continue;

         swMNodeTableBuf.nodeIdentity = tempBicTablePtr->bicId;
         swMNodeTableBuf.e1Num = E1_INVALID;
         swMNodeTableBuf.lapdTs = TS_INVALID;
         //swMNodeTableBuf.e1Num = 0xFFFFFFFF;
         //swMNodeTableBuf.lapdTs = 0xFFFFFFFF ;
         strcpy(swMNodeTableBuf.swVersionActive,"");
         strcpy(swMNodeTableBuf.swVersionInactive,"");
         strcpy(swMNodeTableBuf.swVersionDownloaded,"");
         strcpy(swMNodeTableBuf.swVersionNew,"");
         swMNodeTableBuf.swAction = SW_NO_ACTION;
         swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
         swMNodeTableBuf.chasisFrameId = chasisFrameId;
         swMNodeTableBuf.slotId = slotId;
         if (insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
         {
           LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed");
           free(bicTablePtr);
           return;
         }
         else
         {
           LOG_PRINT(LOG_INFO,"insertSwMNodeTable Successfull");
         }
       }
       if (bicTablePtr != NULL)
         free(bicTablePtr);
     }
     /*Insert one record in SwMNode table (T2) for each Internal TRX */
     if (getallTrxTable(&trxTablePtr,&outRows,&outSize) != CLIB_SUCCESS)
     {
       LOG_PRINT(LOG_DEBUG,"No rows present in the Trx Table");
     }
     else
     {
       for(count = 0;count < outRows;count++)
       {
         tempTrxTablePtr = (TrxTableApi *)((I_U8 *)trxTablePtr + (count*outSize));
         if (tempTrxTablePtr->trxLocation == TRX_LOCATION_IN_FRAME)
         {
           inFrameTrxE1TsTableIndex.trxPos = tempTrxTablePtr->trxPos;
           if (getInFrameTrxE1TsTable(&inFrameTrxE1TsTableIndex,&inFrameTrxE1TsTablePtr) != CLIB_SUCCESS)
           {
             LOG_PRINT(LOG_MAJOR,"getInFrameTrxE1TsTable Failed..");
             free(trxTablePtr);
           }
           else
           {             
             swMNodeTableBuf.nodeType = SYS_NODE_TYPE_TRX;
             swMNodeTableBuf.nodeIdentity = tempTrxTablePtr->ptrxId;
             swMNodeTableBuf.e1Num = inFrameTrxE1TsTablePtr->e1Id;
             swMNodeTableBuf.lapdTs = inFrameTrxE1TsTablePtr->startTs;
             strcpy(swMNodeTableBuf.swVersionActive,"");
             strcpy(swMNodeTableBuf.swVersionInactive,"");
             strcpy(swMNodeTableBuf.swVersionDownloaded,"");
             strcpy(swMNodeTableBuf.swVersionNew,"");
             swMNodeTableBuf.swAction = SW_NO_ACTION;
             swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
             swMNodeTableBuf.chasisFrameId = chasisFrameId;
             swMNodeTableBuf.slotId = slotId;
             if (insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
             {
               LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed");
               free(trxTablePtr);
               free(inFrameTrxE1TsTablePtr);
               return;
             }
             else
               LOG_PRINT(LOG_INFO,"insertSwMNodeTable Successfull")
                 free(inFrameTrxE1TsTablePtr); /* Bug Fixed : Mantis #6182 and #6158 */

           }
         }
       }
       if (trxTablePtr != NULL)
         free(trxTablePtr);
       /*if (inFrameTrxE1TsTablePtr != NULL)
         free(inFrameTrxE1TsTablePtr);*/
     }
   }

   /*Insert one record in SwMNode table for BSC */
   if (getIccIdChasisId( iccId, chasisId, &count ) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getIccIdChasisId call is getting failed.."); 
      return;
   }
   if (getBscId(&bscId) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"No row present in BSS Table");
      swMNodeTableBuf.nodeIdentity = 0;
   }
   else
   {
      swMNodeTableBuf.nodeIdentity = bscId;
   }
   for ( index = 0; index< count; index++ )
   {
      swMNodeTableBuf.nodeType = SYS_NODE_TYPE_BSC;
      /* CS4.0 Changes Start */
      swMNodeTableBuf.e1Num = E1_INVALID;
      swMNodeTableBuf.lapdTs = TS_INVALID;
      /* CS4.0 Changes End */
      strcpy(swMNodeTableBuf.swVersionActive,"");
      strcpy(swMNodeTableBuf.swVersionInactive,"");
      strcpy(swMNodeTableBuf.swVersionDownloaded,"");
      strcpy(swMNodeTableBuf.swVersionNew,"");
      swMNodeTableBuf.swAction = SW_NO_ACTION;
      /* CS4.0: Fix For Mantis 6764 Start*/ 
      /*swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;*/
      swMNodeTableBuf.swStatus = gSwActStatus;
      gSwActStatus = SW_NO_LAST_ACTION;
      /* CS4.0: Fix For Mantis 6764 End*/ 
      swMNodeTableBuf.chasisFrameId = chasisId[index];
      swMNodeTableBuf.slotId = iccId[index];

      if (insertSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"insertSwMNodeTable DB call Failed");
      }
      else
      {
         LOG_PRINT(LOG_INFO,"insertSwMNodeTable Successfull");
      }
   } 
    /* SWUPG changes for IP_BTS */
    fillIpBtsInSWMTableAtInit();
   /* CS4.0 Changes Start */
   cfgInitEicSwMNodeTable();
	 LOG_PRINT(DEBUG,"GOING for InitDSPSwmNodeTable");
   cfgInitDspSwMNodeTable();
   /* CS4.0 Changes End */
}

/******************************* Function  Header*****************************
   Function Name : cfgInsertSwMNodeTableForBic()
Parameters    : None
Return type   : I_S32
Purpose       : Populate SwMNode Table with the Bic recieved in Add Bic request
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_S32 cfgInsertSwMNodeTableForBic(I_U32 bicId,I_U32 e1Id,I_U32 lapdTs, I_U32 btsType)
{
   I_S32 dbStatus = -1;
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;

   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return ret;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   SwMNodeTableApi swMNodeTableBuf;
   swMNodeTableBuf.chasisFrameId = chasisFrameId;
   swMNodeTableBuf.slotId = slotId;
   if ( btsType == BIC )
      swMNodeTableBuf.nodeType = SYS_NODE_TYPE_BIC;
   else if ( btsType == R2_BTS )
      swMNodeTableBuf.nodeType = SYS_NODE_TYPE_R2_BTS;

   swMNodeTableBuf.nodeIdentity = bicId;
   swMNodeTableBuf.e1Num = e1Id ;
   swMNodeTableBuf.lapdTs = lapdTs ;
   strcpy(swMNodeTableBuf.swVersionActive,"");
   strcpy(swMNodeTableBuf.swVersionInactive,"");
   strcpy(swMNodeTableBuf.swVersionDownloaded,"");
   strcpy(swMNodeTableBuf.swVersionNew,"");
   swMNodeTableBuf.swAction = SW_NO_ACTION;
   swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
   dbStatus = insertSwMNodeTable(&swMNodeTableBuf);
   return dbStatus;
}
/******************************* Function  Header*****************************
   Function Name : cfgInsertSwMNodeTableForIpBts()
Parameters    : None
Return type   : I_S32
Purpose       : Populate SwMNode Table with the Bic recieved in Add Bic request
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_S32 cfgInsertSwMNodeTableForIpBts(I_U32 bicId, I_U32 btsType)
{
   I_S32 dbStatus = -1;
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CFG_FAILURE;

   LOG_PRINT(LOG_INFO,"Entering function cfgInsertSwMNodeTableForIpBts ");
   
   if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return ret;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   SwMNodeTableApi swMNodeTableBuf;
   swMNodeTableBuf.chasisFrameId = chasisFrameId;
   swMNodeTableBuf.slotId = slotId;
   if ( btsType == R3_BTS )
      swMNodeTableBuf.nodeType = SYS_NODE_TYPE_R3_BTS;
   else if ( btsType == R2_BTS_IP )
      swMNodeTableBuf.nodeType = SYS_NODE_TYPE_R2_BTS_IP;

   swMNodeTableBuf.nodeIdentity = bicId;
   swMNodeTableBuf.e1Num = E1_INVALID;
   swMNodeTableBuf.lapdTs = TS_INVALID;
   //swMNodeTableBuf.e1Num = 0xFFFFFFFF;
   //swMNodeTableBuf.lapdTs = 0xFFFFFFFF ;
   strcpy(swMNodeTableBuf.swVersionActive,"");
   strcpy(swMNodeTableBuf.swVersionInactive,"");
   strcpy(swMNodeTableBuf.swVersionDownloaded,"");
   strcpy(swMNodeTableBuf.swVersionNew,"");
   swMNodeTableBuf.swAction = SW_NO_ACTION;
   swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
   dbStatus = insertSwMNodeTable(&swMNodeTableBuf);
   LOG_PRINT(LOG_INFO,"Exiting function cfgInsertSwMNodeTableForIpBts ");
   return dbStatus;
}

/******************************* Function  Header*****************************
   Function Name : cfgInsertSwMNodeTableForTrx()
Parameters    : None
Return type   : I_S32
Purpose       : Populate SwMNode Table with the Trx recieved in Add Trx request
Other Note    : Added For BSC CS3.0
 *****************************************************************************/
I_S32 cfgInsertSwMNodeTableForTrx(I_U32 trxId,I_U32 trxType)
{
   I_S32 dbStatus = -1;
   I_S32 retVal = CFG_FAILURE;
   I_U32 e1Id;
   I_U32 lapdTs;
   I_U8 slotId;
   I_U8 chasisFrameId;

   if (TRX_LOCATION_BIC == trxType)
   {
      retVal = getE1TsFromBicTrxTimeslotUsageTable(TS_USAGE_BICTRX, trxId, &e1Id, &lapdTs);
      if (CFG_FAILURE == retVal)
      {
         LOG_PRINT(LOG_MAJOR,"getE1TsFromBicTrxTimeslotUsageTable Failure");
         return dbStatus;
      }
   }
   else
   {
      retVal = getE1TsForInFrameTrx(trxId, &e1Id, &lapdTs);
      if (CFG_FAILURE == retVal)
      {
         LOG_PRINT(LOG_MAJOR,"getE1TsForInFrameTrx Failure");
         return dbStatus;
      }
   }
   
   if ( ( retVal = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",retVal);
      return retVal;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

 
   SwMNodeTableApi swMNodeTableBuf;
   swMNodeTableBuf.chasisFrameId = chasisFrameId;
   swMNodeTableBuf.slotId = slotId;
   swMNodeTableBuf.nodeType = SYS_NODE_TYPE_TRX;
   swMNodeTableBuf.nodeIdentity = trxId;
   swMNodeTableBuf.e1Num = e1Id ;
   swMNodeTableBuf.lapdTs = lapdTs ;
   strcpy(swMNodeTableBuf.swVersionActive,"");
   strcpy(swMNodeTableBuf.swVersionInactive,"");
   strcpy(swMNodeTableBuf.swVersionDownloaded,"");
   strcpy(swMNodeTableBuf.swVersionNew,"");
   swMNodeTableBuf.swAction = SW_NO_ACTION;
   swMNodeTableBuf.swStatus = SW_NO_LAST_ACTION;
   dbStatus = insertSwMNodeTable(&swMNodeTableBuf);
   return dbStatus;
}

I_S32 file_select(struct direct *entry)   
{
   if ((strcmp(entry->d_name, ".") == 0) ||
         (strcmp(entry->d_name, "..") == 0))
      return (I_FALSE);
   else
      return (I_TRUE);
}

I_Bool delNonExistingAvailRelFromCP(OamOilCfgAvailableReleasesResp *availRelRespPtr)
{
   I_S32 count1,count2,noOfReleases;
   I_S32 fileExist = 0;
   struct direct **files = NULL;
   I_S32 file_select();
   I_S8 rmDirString[OAMS_CMD_PARAM_MAX_SIZE];
/*
   I_S8 mkDirString[OAMS_CMD_PARAM_MAX_SIZE];
*/
   I_S8 *pathName = NULL;
   I_S32 status = 0;

   if (availRelRespPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      pathName = trxPathName;
   }
   else if (availRelRespPtr->nodeType == SYS_NODE_TYPE_BIC)
   {
      pathName = bicPathName;
   }
   else if (availRelRespPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      pathName = btsPathName;
   }
   LOG_PRINT(LOG_INFO,"delNonExistingAvailRelFromCP: PathName:: %s" , pathName);
   /* Fix for Mantis Id: 6241: start */
   /* sprintf(mkDirString,"mkdir -p %s",pathName);
   status = (system(mkDirString)); */
   status=make_parent_dir(pathName);
   /* Fix for Mantis Id: 6241: End */
   if(status != 0)
   {
      LOG_PRINT(CRITICAL,"Error in creating release directory with status: %d",status >> 8);
      return I_FALSE;
   }   

   noOfReleases = scandir(pathName, &files, file_select, alphasort);
   if (noOfReleases <= 0)
   { 
      LOG_PRINT(INFO,"No files present in CP");
   }
   else
   {
      LOG_PRINT(INFO,"Number of files = %d",noOfReleases);
      for (count1 = 0;count1 < noOfReleases;count1++)
      {
         LOG_PRINT(INFO,"%s ",files[count1]->d_name);
         fileExist = 0;
         for (count2 =0;count2 < availRelRespPtr->numVersion;count2++)
         {
            if (strcmp(files[count1]->d_name,availRelRespPtr->availSwVersions[count2]) == 0)
               fileExist = 1;
         }
         if (fileExist != 1)
         {
            LOG_PRINT(INFO,"%s release not exist in PP,Deleting release..",files[count1]->d_name);
            sprintf(rmDirString,"rm -rf %s/%s",pathName,files[count1]->d_name);
            LOG_PRINT(INFO,"rmDirString: %s",rmDirString);
            status = (system(rmDirString));
            if(status != 0)
            {
               LOG_PRINT(CRITICAL,"Error in deleting release with error: %d",status >> 8);
               if (files != NULL)
                  free(files);
               return I_FALSE;
            }
            else
            { 
               LOG_PRINT(INFO,"Successfully Deleted release from CP"); 
            }
         }
      }
   }
   if (files != NULL)
      free(files);
   return I_TRUE;
}

I_Bool copyReleaseFromPPToCP(I_U8 *srcBinaryPath,I_S8 *swVersion,I_U32 nodeType,I_U8 *destBinaryPath)
{
   I_S32 status;
   I_S8 *tempPtr = srcBinaryPath;
   I_S8 *fileNamePtr = NULL;
   I_S8 *pathName = NULL;
   I_S8 *ppIpAdr = NULL;
   I_S8 rsyncString[OAMS_CMD_PARAM_MAX_SIZE];
   I_S8 mkDirString[OAMS_CMD_PARAM_MAX_SIZE];

   if (nodeType == SYS_NODE_TYPE_BIC || nodeType == SYS_NODE_TYPE_TRX || nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      LOG_PRINT(INFO,"Copying File from PP(Path:%s) for NodeType: %d",srcBinaryPath,nodeType);
      while (*tempPtr != '\0') 
      {
         fileNamePtr = tempPtr;
         tempPtr++;
      }
      tempPtr = fileNamePtr;
      while (*tempPtr != '/')
      {
         fileNamePtr = tempPtr;
         tempPtr--;
      }
      LOG_PRINT(INFO,"Release Name: %s",fileNamePtr);
      if (nodeType == SYS_NODE_TYPE_TRX)
      {
         pathName = trxPathName;
      }
      else if (nodeType == SYS_NODE_TYPE_BIC)
      {
         pathName = bicPathName;
      }
      else if (nodeType == SYS_NODE_TYPE_R2_BTS)
      {
         pathName = btsPathName;
      }

      ppIpAdr = getenv("config_PP_IP");
      if (ppIpAdr == NULL)
      {
         LOG_PRINT(CRITICAL,"config_PP_IP is not Set");
         return I_FALSE;
      }

      //sprintf(mkDirString,"mkdir -p %s/%s",pathName,swVersion);
      //LOG_PRINT(INFO,"mkDirString: %s",mkDirString);
      //status = (system(mkDirString));
      sprintf(mkDirString,"%s/%s",pathName,swVersion);
      LOG_PRINT(INFO,"mkDirString: %s",mkDirString);
      status=make_parent_dir(mkDirString);
      if(status != 0)
      {
         LOG_PRINT(CRITICAL,"Error in creating release directory with status: %d",status >> 8);
         return I_FALSE;
      }

      sprintf(rsyncString,"rsync %s::ICC_ICC_USER%s %s/%s",ppIpAdr,srcBinaryPath,pathName,swVersion);
      LOG_PRINT(INFO,"rsyncString: %s",rsyncString);
      status = (system(rsyncString));
      //LOG_PRINT(INFO,"Rsync Status =%d",status);
      if(status != 0)
      {
         LOG_PRINT(CRITICAL,"Error in copying release using rsync with errorcode:%d, errno=%d, %s",
              status >> 8, errno, strerror(errno));
         return I_FALSE;
      }
      else
      {
         sprintf(destBinaryPath,"%s/%s/%s",pathName,swVersion,fileNamePtr);
         LOG_PRINT(INFO,"File Copied on CP(Path:%s)",destBinaryPath);
         return I_TRUE;
      }
   }
/* CS4.0 Change */
   else if (nodeType == SYS_NODE_TYPE_BSC || nodeType == SYS_NODE_TYPE_EIC || nodeType == SYS_NODE_TYPE_DSP)
   {
      memcpy(destBinaryPath,srcBinaryPath,OAMS_CMD_PARAM_MAX_SIZE);
   }

    return I_TRUE;
}
/* CS4.0 Changes start */
I_Bool deleteReleaseFromCP(OamOilCfgSwDelResp *swDelRespPtr,I_U8 chasisFrameId,I_U8 slotId)
/* CS4.0 Changes End */
{
   I_U8 binaryPath[OAMS_CMD_PARAM_MAX_SIZE]; 
   I_S8 *pathName = NULL;
   I_S8 rmDirString[OAMS_CMD_PARAM_MAX_SIZE];
   I_S32 status;

  if (checkUpgradeOfferFailure(swDelRespPtr,chasisFrameId,slotId,binaryPath) != I_TRUE)
   {
      return I_FALSE;
   }

   if (swDelRespPtr->nodeType == SYS_NODE_TYPE_TRX)
   {
      pathName = trxPathName;
   }
   else if (swDelRespPtr->nodeType == SYS_NODE_TYPE_BIC)
   {
      pathName = bicPathName;
   }
   else if (swDelRespPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
   {
      pathName = btsPathName;
   }

   sprintf(rmDirString,"rm -rf %s/%s",pathName,swDelRespPtr->delVersion);
   LOG_PRINT(INFO,"Deleting release %s from CP",rmDirString);
   status = (system(rmDirString));
   if(status != 0)
   {
      LOG_PRINT(CRITICAL,"Error in deleting release with error: %d",status >> 8);
   }
   else
   { 
      LOG_PRINT(INFO,"Successfully Deleted release from CP"); 
   }
   return I_TRUE;
}

/* CS4.0 changes start */
I_Bool checkUpgradeOfferFailure(OamOilCfgSwDelResp *swDelRespPtr,I_U8 chasisFrameId,I_U8 slotId,I_U8 *binaryPath)
/* CS4.0 Changes End */
{
   I_U8 type[4];
   SwMTableApi *swMTablePtr = NULL;
   SwMTableIndices sApiSwMTableIndices;
   sApiSwMTableIndices.nodeType = swDelRespPtr->nodeType;
   strcpy(sApiSwMTableIndices.swVersion,swDelRespPtr->delVersion);
   /* CS4.0 HA changes start */
   sApiSwMTableIndices.chasisFrameId = swDelRespPtr->frameId;
   sApiSwMTableIndices.slotId = swDelRespPtr->slotId;
   /* CS4.0 HA changes start */
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   SwMOfferTableIndices swMOfferTableIndex;

   if (getSwMTable(&sApiSwMTableIndices,&swMTablePtr) != CLIB_SUCCESS)
   {
      swMOfferTableIndex.nodeType = swDelRespPtr->nodeType;
      strcpy(swMOfferTableIndex.upgradeVersion,swDelRespPtr->delVersion);
      /* CS4.0 HA changes start */
      swMOfferTableIndex.chasisFrameId = swDelRespPtr->frameId;
      swMOfferTableIndex.slotId = swDelRespPtr->slotId;
      /* CS4.0 HA changes start */

      /*Delete record from SwMOffer Table */
      if (deleteSwMOfferTable(&swMOfferTableIndex) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferTable DB call is getting failed");
         return I_FALSE;
      }
      else
         LOG_PRINT(LOG_INFO,"deleteSwMOfferTable Success");

      /*Send Alarm */
      LOG_PRINT(LOG_INFO,"Sending failure ALARM: INFO_BPM_SW_DWNLD_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_DWNLD_FAIL;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC; 
      sysAlarmBuff.sysAlarm.key1 = chasisFrameId; 
      sysAlarmBuff.sysAlarm.key2 = slotId; 
      sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
      sysAlarmBuff.sysAlarm.alarmReason = ERROR_TRANSFER_FAILED;
      convertNodeType(type,swDelRespPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "Sw Offer for SwVer [%s] NodeType [%s] Failed due to Transfer Failed at Chasis [%d],Slot [%d]",
            swDelRespPtr->delVersion,type,chasisFrameId,slotId); 
      /* CS4.0 changes End */
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      return I_FALSE;
   }
   else
   {
      memcpy(binaryPath,swMTablePtr->binaryPath,OAMS_CMD_PARAM_MAX_SIZE);
      if (swMTablePtr != NULL)
         free(swMTablePtr);
      return I_TRUE;
   }
}
/* Fix for Mantis Id: 6241: start */
I_S32 make_parent_dir (const I_S8 * arg_path)
{
    struct stat		stat_buf;
    I_S8 *		slash_ptr = NULL;
    I_S8		work_path[ OAMS_CMD_PARAM_MAX_SIZE + 1 ];
    I_S32               arg_mode = 0;

    work_path[ OAMS_CMD_PARAM_MAX_SIZE ] = 0;
    strncpy( work_path, arg_path, OAMS_CMD_PARAM_MAX_SIZE + 1 );
    if ( work_path[ OAMS_CMD_PARAM_MAX_SIZE ] != 0 ) {
	errno = ENAMETOOLONG;
	return -1;
    }

    arg_mode |= ( S_IWUSR | S_IXUSR | S_IRUSR);

    slash_ptr = work_path;
    while ( * slash_ptr ) {

	if ( * slash_ptr == '/' ) {
	    * slash_ptr = 0;

	  if(strlen(work_path)!=0) {
	    if ( stat( work_path, & stat_buf ) < 0 ) {
		if ( mkdir( work_path, arg_mode ) < 0 ) return -1;
	    }

	    else if ( ! S_ISDIR( stat_buf.st_mode ) ) {
		errno = ENOTDIR;
		return -2;
	    }
         }

	    * slash_ptr = '/';
	}

	++ slash_ptr;
    }
    if(*(slash_ptr-1)!='/')
    if ( stat( work_path, & stat_buf ) < 0 )
        if ( mkdir( work_path, arg_mode ) < 0 ) return -1;
    return 0;
}
/* Fix for Mantis Id: 6241: End */

/********************************* Function  Header*****************************
Function Name   : cfgFreePathNameResources()
Parameters      : None
Return type     : I_Void
Purpose         : This function will free Path Name Resources. 
Other Note   : Added For BSC CS4.0 HA Feature
*******************************************************************************/
I_Void cfgFreePathNameResources()
{
   LOG_PRINT(LOG_INFO,"cfgFreePathNameResources : Entering in function");
   if(bicPathName !=NULL)
   {
      free(bicPathName);
      bicPathName = NULL;
   }
   if(btsPathName !=NULL)
   {
      free(btsPathName);
      btsPathName = NULL;
   }
   if(trxPathName !=NULL)
   {
      free(trxPathName);
      trxPathName = NULL;
   }
   LOG_PRINT(LOG_INFO,"cfgFreePathNameResources : Exiting from function");
   
}

/******************************* Function  Header*****************************
   Function Name : sendRequestForBscAvailableReleases()
Parameters    : None
Return type   : I_Void
Purpose       : Sends request for available releases present on BSC platform
for BSC
Other Note    : Added For BSC R2.3  
 *****************************************************************************/
I_S32 sendRequestForBscAvailableReleases(I_U8 frameId, I_U8 slotId)
{
   I_S32 ret = CFG_FAILURE;
   I_U32 count =ZERO;
   I_U32 index = ZERO;

   OamsCfgOilAvailableReleasesReq  availableReleasesReqBuff;  
   IccCardInfoTableApi *cardInfoPtr = NULL;
   IccCardInfoTableIndices cardInfoIndices;

   availableReleasesReqBuff.nodeType = SYS_NODE_TYPE_BSC;
   cardInfoIndices.chasisFrameId = frameId; 
   cardInfoIndices.slotId = slotId;
   if(getIccCardInfoTable( &cardInfoIndices, &cardInfoPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"Db query failed");
      return CFG_FAILURE;
   }
   if( (cardInfoPtr->cardOperationalState == CARDSTATE_ABSENT) ||
       (cardInfoPtr->cardOperationalState == CARDSTATE_FAIL) ||
       (cardInfoPtr->cardOperationalState == CARDSTATE_SHUTDOWN)  )
   {
      LOG_PRINT(LOG_INFO,"CARD is ABSENT/FAIL. No request will be sent for chasisFrameId [%d], SlotId [%d]",frameId,slotId);
      free(cardInfoPtr);
      return CFG_FAILURE;
      
   }
   free(cardInfoPtr);
   
   availableReleasesReqBuff.frameId = frameId; 
   availableReleasesReqBuff.slotId = slotId;

   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ for BSC ChasisFrameId[%d],SlotId[%d]",frameId,slotId);
   cfgSendMessage((I_Void *)&availableReleasesReqBuff, 
         sizeof(OamsCfgOilAvailableReleasesReq), ENT_OAM_OIL, 
         OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ, 0);       
   return CFG_SUCCESS; 
}


/******************************* Function  Header*****************************
   Function Name : cfgInitSwMNodeTableDelBicTrx()
Parameters    : None
Return type   : I_Void
Purpose       : Initialize SwMNode Table and delete the entry for standby peer
card
Other Note    : Added For BSC R2.0 
 *****************************************************************************/
I_Void cfgInitSwMNodeTableDelBicTrx()
{
   SwMNodeTableApi *tmpPtr;
   SwMNodeTableApi *outData;
   SwMNodeTableIndices swmTblIndex;
   TrxTableIndices trxTableIndices;
   TrxTableApi *trxTableApi; 
   OamsCfgAfhSysAlarm sysAlarmBuff;
   I_U8 string[MAX_STRING_LENGTH];
   I_S8 oprStatus[] = "Sw Dnld";
   I_U32 outRows,i;
   I_U16 outSize;
   I_S32 ret;
   I_U8 chasisFrameId= 0, slotId = 0; 
  LOG_PRINT(INFO,"Enter in CfgInitSwMNode");
   ret = getActiveIccSlotId(&chasisFrameId, &slotId);
   if(ret != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"getActiveIccSlotId failed err:%d",ret);
   }
   ret = getallSwMNodeTable(&outData, &outRows, &outSize);
   if(ret != CLIB_SUCCESS)
   {
      LOG_PRINT(DEBUG,"No Rows Present in SwMNodeTable retVal:%d", ret); 
      return; 
   }
   LOG_PRINT(INFO,"Value of gCfgStandbyToActive:%d",gCfgStandbyToActive); 
   for(i=0; i< outRows; i++)
   {
      tmpPtr = (SwMNodeTableApi *)(((I_U8 *)outData) + i * outSize);
      LOG_PRINT(INFO,"NodeType :%d, SwStatus :%d",tmpPtr->nodeType,tmpPtr->swStatus);
      if(  (tmpPtr->nodeType == SYS_NODE_TYPE_BIC) ||
           (tmpPtr->nodeType == SYS_NODE_TYPE_TRX)  ||  
           (tmpPtr->nodeType == SYS_NODE_TYPE_R2_BTS)  || 
           (tmpPtr->nodeType == SYS_NODE_TYPE_R2_BTS_TRX)   ) 
      {
         if( (I_TRUE == gCfgStandbyToActive) && 
             (tmpPtr->swStatus == SW_DOWNLOAD_IN_PROGRESS)  ) 
         {
              gSystemDetails->selfInfo.slotID;
              
              /* Send Alarm */
              LOG_PRINT(LOG_INFO,"Sending failure alarm: EVENT_SW_DWNLD_FAILED");
              sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_DWNLD_FAILED;
              sysAlarmBuff.sysAlarm.key1 = tmpPtr->nodeIdentity;
              if (tmpPtr->nodeType == SYS_NODE_TYPE_TRX)
              {
                 trxTableIndices.ptrxId = tmpPtr->nodeIdentity; 
                 if( CLIB_SUCCESS != getTrxTable(&trxTableIndices,&trxTableApi) )	
                 {
                     LOG_PRINT(DEBUG,"getTrxTable failed for Trx:%d",tmpPtr->nodeIdentity);
                     return;
                 }
                 sysAlarmBuff.sysAlarm.key1 = trxTableApi->bicId;
                 sysAlarmBuff.sysAlarm.key2 = trxTableApi->ptrxId;;
                 free(trxTableApi);
                 sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_PTRX;
              }
              else if (tmpPtr->nodeType == SYS_NODE_TYPE_BIC)
              {
                 sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
              }
              else if (tmpPtr->nodeType == SYS_NODE_TYPE_R2_BTS)
              {
                 sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
              }
    
              sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
              sysAlarmBuff.sysAlarm.alarmReason = CAUSE_COMPLETE_FILE_NOT_RECEIVED; 
              getStringForSwmhErrorCause(CAUSE_COMPLETE_FILE_NOT_RECEIVED,oprStatus,
                    tmpPtr->swVersionNew,tmpPtr->nodeType,
                    tmpPtr->nodeIdentity,string);
              sysAlarmBuff.sysAlarm.infoStrLen = 
                 sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
              cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
                        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);  
             /* Added For Issue 16838 */ 
              sendLoadAbortIndToSWMH(tmpPtr->nodeType,tmpPtr->nodeIdentity);
              
         }
         swmTblIndex.chasisFrameId = tmpPtr->chasisFrameId;
         swmTblIndex.slotId = tmpPtr->slotId ;
         swmTblIndex.nodeType = tmpPtr->nodeType;
         swmTblIndex.nodeIdentity = tmpPtr->nodeIdentity;
         ret = deleteSwMNodeTable(&swmTblIndex); 
         if(ret == CLIB_SUCCESS)
         {
             LOG_PRINT(DEBUG,"DelSwMNodeTable succ for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }
         else
         {
             LOG_PRINT(DEBUG,"DelSwMNodeTable fail for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }

         tmpPtr->slotId = slotId;
         tmpPtr->swAction = SW_NO_ACTION;
         tmpPtr->swStatus = SW_NO_LAST_ACTION;
         strcpy(tmpPtr->swVersionNew,""); 
         ret = insertSwMNodeTable(tmpPtr); 
         if(ret == CLIB_SUCCESS)
         {
             LOG_PRINT(DEBUG,"update succ for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }
         else
         {
             LOG_PRINT(DEBUG,"updateSwMNodeTable fail for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }
      }
      else if(  (tmpPtr->nodeType == SYS_NODE_TYPE_R2_BTS_IP) || (tmpPtr->nodeType == SYS_NODE_TYPE_R3_BTS)){
         
         swmTblIndex.chasisFrameId = tmpPtr->chasisFrameId;
         swmTblIndex.slotId = tmpPtr->slotId ;
         swmTblIndex.nodeType = tmpPtr->nodeType;
         swmTblIndex.nodeIdentity = tmpPtr->nodeIdentity;
         ret = deleteSwMNodeTable(&swmTblIndex); 
         if(ret == CLIB_SUCCESS)
         {
             LOG_PRINT(DEBUG,"DelSwMNodeTable succ for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }
         else
         {
             LOG_PRINT(DEBUG,"DelSwMNodeTable fail for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }

         tmpPtr->slotId = slotId;
         tmpPtr->swAction = SW_NO_ACTION;
         tmpPtr->swStatus = SW_NO_LAST_ACTION;
         strcpy(tmpPtr->swVersionNew,""); 
         ret = insertSwMNodeTable(tmpPtr); 
         if(ret == CLIB_SUCCESS)
         {
             LOG_PRINT(DEBUG,"update succ for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }
         else
         {
             LOG_PRINT(DEBUG,"updateSwMNodeTable fail for slotId:%d,nodeType:%d,nodeId:%d",
                swmTblIndex.slotId,swmTblIndex.nodeType,swmTblIndex.nodeIdentity);
         }

       }
   }
}
/* Added For Issue :16838 */
/******************************* Function  Header*****************************
   Function Name : sendLoadAbortIndToSWMH()
Parameters    : NodeType,NodeId
Return type   : I_Void
Purpose       : Send LoadAbort message in case of swichover from standby to avtive and
               bts/trx download in progress.
Other Note    : Added For BSC R2.5.5 
 *****************************************************************************/
I_Void sendLoadAbortIndToSWMH(I_U32 nodeType,I_U32 nodeId)
{
     LOG_PRINT(INFO,"Enter in sendLoadAbortIndToSWMH "); 
     OamsCfgSwmhLoadAbortInd loadAbortIndBuff;
     I_U32 applTei;
       if (getApplTei(nodeType, nodeId, &applTei) !=CLIB_SUCCESS)
       {
          LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
          cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
          return;
       }
   
       loadAbortIndBuff.nodeType = nodeType;
       loadAbortIndBuff.nodeIdentity = nodeId;
       loadAbortIndBuff.applTei = applTei;
       LOG_PRINT(LOG_INFO,"NodeType: %u NodeId: %u,ApplTei:%u",loadAbortIndBuff.nodeType,loadAbortIndBuff.nodeIdentity,loadAbortIndBuff.applTei);
       cfgSendMessage((I_Void *)&loadAbortIndBuff, sizeof(OamsCfgSwmhLoadAbortInd),
            ENT_OAMS_SWMH, OAMS_CFG_SWMH_LOAD_ABORT_IND, 0);
     LOG_PRINT(INFO,"sent LoadAbortInd Msg to SWMH, Exting sendLoadAbortIndToSWMH "); 
}


/******************************* Function  Header*****************************
   Function Name : setIpBtsSwMOfferTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Upgrade Offer request from OMC/CLI
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void setIpBtsSwMOfferTableHandler()
{

  SwMOfferTableApi *receiveMsgPtr = NULL;
  SwMOfferIpTableApi *swMOfferIpTableDbPtr = NULL;
  SwMOfferIpTableApi swMOfferIpTableIns; 
  receiveMsgPtr = (SwMOfferTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  SwMOfferIpTableIndices swMOfferIpTableindex;
  SwMTableApi *swMTableDbPtr = NULL;
  SwMTableIndices swMTableindex;
  I_S32 ret = ONE;
  I_U32 rowCount = ZERO;
  I_U32 tokenNum;
  I_U32 token[MAX_DIGITS + 1 ];
  I_U32 errCause;
  I_S32 actionInProgress = I_FALSE;
  I_CHAR logPasswdChSum[OAMS_NAME_SIZE + 1];
  I_U8 chasisFrameId;
  I_U8 slotId;
  I_U32 nodeType =0, failType =0, swStatus = 0;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_U8 type[4];
  I_U8 strUpgradeVersion[25];
  I_U8 tempToken[MAX_DIGITS + 1];
  int i;
  LOG_PRINT(LOG_INFO,"setIpBtsSwMOfferTableHandler:Entering function");
  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

  swMOfferIpTableindex.nodeType = receiveMsgPtr->nodeType;
  strcpy(swMOfferIpTableindex.upgradeVersion,receiveMsgPtr->upgradeVersion);
  swMTableindex.nodeType = receiveMsgPtr->nodeType;
  strcpy(swMTableindex.swVersion,receiveMsgPtr->upgradeVersion);


  receiveMsgPtr->chasisFrameId = chasisFrameId;
  receiveMsgPtr->slotId = slotId;
  //swMOfferIpTableindex.chasisFrameId = chasisFrameId;
  // swMOfferIpTableindex.slotId = slotId;
  swMTableindex.chasisFrameId = chasisFrameId;
  swMTableindex.slotId = slotId;
  LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->upgradeVersion);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",receiveMsgPtr->nodeType);
  LOG_PRINT(LOG_INFO,"FrameId: %d ",receiveMsgPtr->chasisFrameId);
  LOG_PRINT(LOG_INFO,"SlotId: %d ",receiveMsgPtr->slotId);

  LOG_PRINT(LOG_INFO,"ftpServerAddress: %u",receiveMsgPtr->ftpServerAddress);
  memset(logPasswdChSum,NULL,OAMS_NAME_SIZE + 1);
  memcpy(logPasswdChSum,receiveMsgPtr->loginName,OAMS_NAME_SIZE);
  LOG_PRINT(LOG_INFO,"loginName: %s ",logPasswdChSum);
  memset(logPasswdChSum,NULL,OAMS_NAME_SIZE + 1);
  memcpy(logPasswdChSum,receiveMsgPtr->password,OAMS_NAME_SIZE);
  LOG_PRINT(LOG_INFO,"password: %s",logPasswdChSum);
  memset(logPasswdChSum,NULL,OAMS_NAME_SIZE + 1);
  memcpy(logPasswdChSum,receiveMsgPtr->checksum,OAMS_NAME_SIZE);
  LOG_PRINT(LOG_INFO,"checksum: %s",logPasswdChSum);
  LOG_PRINT(LOG_INFO,"size: %u",receiveMsgPtr->size);

  if ((receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS_IP) && (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R3_BTS))
  {
    LOG_PRINT(LOG_DEBUG,"Invalid NodeType recieved");
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return; 
  }

  /*Check Sw Version is in correct format*/
     tokenNum = 4; //except for IP-BTS all versions are 3 byte
  if (convertInputStringToNumber(receiveMsgPtr->upgradeVersion,&tokenNum,
        token,&errCause) == SW_VER_SUCCESS)
  {
    
         LOG_PRINT(LOG_INFO,"token[0]: %d",token[0]);
         LOG_PRINT(LOG_INFO,"token[1]: %d",token[1]);
         LOG_PRINT(LOG_INFO,"token[2]: %d",token[2]);
         LOG_PRINT(LOG_INFO,"token[3]: %d",token[3]);
         LOG_PRINT(LOG_INFO,"tokenNum: %d",tokenNum);
    if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255) || (token[3] > 255))        
    {
      LOG_PRINT(LOG_DEBUG,"Recieved Sw Version format incorrect ");
      cfgSendNackToCm(CM_ERR_SW_VERSION_TOKENS_EXCEEDS_RANGE);
      LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      convertNodeType(type,receiveMsgPtr->nodeType);
			//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016
      /*sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Offer for NodeType [%s] completed ChasisFrameId [%d],SlotId [%d]",
          type,receiveMsgPtr->chasisFrameId,receiveMsgPtr->slotId); */
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
          type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2)); 
			//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016
      //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      return;
    }         
  }
  else
  {
    LOG_PRINT(LOG_DEBUG,"Recieved sw version format incorrect ");
    cfgSendNackToCm(errCause);
    LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
        "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
        type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2)); //Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
    //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    return;
  }

  /*Retrieve count of number of rows present in SwMOffer Table */ 
  if (getIpBtsCountOfSwUpgradeOfferTable(&rowCount) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_DEBUG,"No row present in SwMOffer Table");
  }
  else
  {
    /*Check if already maximum allowed upgrade offer is in progress */
    if(rowCount == MAX_IP_SW_UPGRADE_OFFER_IN_PARALLEL)
    {
      LOG_PRINT(LOG_DEBUG,"Max allowed swUpgradeOffer Limit Reached");
      //cfgSendNackToCm(CM_ERR_MAX_SW_UPGRADE_OFFER_ALREADY_REACHED);
      cfgSendNackToCm(CM_ERR_MAX_SW_UPGRADE_OFFER_ALREADY_RUNNING);
      LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
      sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
      sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
      sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
      sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
      convertNodeType(type,receiveMsgPtr->nodeType);
      sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
          type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2)); //Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
      //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
      cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
          ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
      return;
    }

    if (rowCount > 0 && (rowCount < MAX_IP_SW_UPGRADE_OFFER_IN_PARALLEL)) 
    {
      /*Check if entry exists in SwMOffer table for req swVersion */
      ret = getSwMOfferIpTable(&swMOfferIpTableindex,&swMOfferIpTableDbPtr);
      if (ret == CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_DEBUG,"Not able to update version in SwmOffer IP  Table,Version already stored");
        cfgSendNackToCm(CM_ERR_VERSION_ALREADY_AVAILABLE);
        LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
        sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
        sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
        sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
        sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
        sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
        convertNodeType(type,receiveMsgPtr->nodeType);
        sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
            "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
            type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
        //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
        cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
            ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
        free(swMOfferIpTableDbPtr);
        return;
      }
    }
  }

  /* check if activation is in progress for BSC/EIC/DSP/R2_BTS/R2_BTS_TRX/R2_BTS_IP/R2_BTS_IP_TRX/R3_BTS/R3_BTS_TRX */
  actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
    fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
    LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
        "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
        type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
    //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    return;
  }
  /* check if deletion is in progress for BSC/EIC/BIC/TRX/R2_BTS_IP/R3_BTS */
  //actionInProgress = isDeletionInProgressIpBts();
  actionInProgress = isDeletionInProgress();
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Deletion is in progress for BSC or EIC or BIC or TRX");
    cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
    LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
        "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
        type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
    //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    return;
  }

  /*Check if for the requested sw version, there is an entry in SwM table */
  ret = getSwMTable(&swMTableindex,&swMTableDbPtr);
  if (swMTableDbPtr != NULL)
  {
    LOG_PRINT(LOG_DEBUG,"Software version is already available in DataBase");
    cfgSendNackToCm(CM_ERR_VERSION_ALREADY_AVAILABLE);
    LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
        "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
        type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
    //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    free(swMOfferIpTableDbPtr);
    return;
  }

  /*Insert record in SwMOffer Table indicating download could be start when DNLD req will come for 
   * requested sw version */

  swMOfferIpTableIns.nodeType = receiveMsgPtr->nodeType;
  
  
  /* changes mantis-28550 start*/
  for(i=0;i<tokenNum;i++)
    tempToken[i]= (I_U8)token[i];
  if(convertInputNumberToString(tempToken,tokenNum,strUpgradeVersion)==SW_VER_SUCCESS)
  {
    LOG_PRINT(LOG_DEBUG," strUpgradeVersion = %s",strUpgradeVersion);
    strcpy(swMOfferIpTableIns.upgradeVersion,strUpgradeVersion);
  }
  else 
  {
    strcpy(swMOfferIpTableIns.upgradeVersion,receiveMsgPtr->upgradeVersion);
  }
  /* changes mantis-28550 end*/
  swMOfferIpTableIns.ftpServerAddress = receiveMsgPtr->ftpServerAddress;
  strcpy(swMOfferIpTableIns.tarPathName,receiveMsgPtr->tarPathName);
  strcpy(swMOfferIpTableIns.loginName,receiveMsgPtr->loginName);
  strcpy(swMOfferIpTableIns.password,receiveMsgPtr->password);
  strcpy(swMOfferIpTableIns.checksum,receiveMsgPtr->checksum);
  swMOfferIpTableIns.size = receiveMsgPtr->size;



  if (insertSwMOfferIpTable(&swMOfferIpTableIns) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"insertSwMOfferIpTable DB call is getting failed.");
    cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
    LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
        "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
        type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
    //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"insertSwMOfferIpTable Successful");

  /*Insert a record in SwM Table for the given software version */
  SwMTableApi swMTableBuf;
  swMTableBuf.nodeType = receiveMsgPtr->nodeType;
  swMTableBuf.chasisFrameId = receiveMsgPtr->chasisFrameId;
  swMTableBuf.slotId = receiveMsgPtr->slotId;
  /* changes mantis-28550 start*/
  for(i=0;i<tokenNum;i++){
    tempToken[i]= (I_U8)token[i];
   LOG_PRINT(LOG_DEBUG," tempToken[%d] = %d",i,tempToken[i]);
   }
  if(convertInputNumberToString(tempToken,tokenNum,strUpgradeVersion)==SW_VER_SUCCESS)
  {
    LOG_PRINT(LOG_DEBUG," strUpgradeVersion = %s",strUpgradeVersion);
    strcpy(swMTableBuf.swVersion,strUpgradeVersion);
  }
  else 
  {
    strcpy(swMTableBuf.swVersion,receiveMsgPtr->upgradeVersion);
  }
  //strcpy(swMTableBuf.swVersion,receiveMsgPtr->upgradeVersion);
  /* changes mantis-28550 end*/
  memcpy(swMTableBuf.binaryPath,"NOT APPLICABLE FOR IP BTS",OAMS_CMD_PARAM_MAX_SIZE);
  swMTableBuf.swDownloadCount = 0;
  swMTableBuf.deletionInProgress = I_FALSE;

  if (insertSwMTable(&swMTableBuf) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"insertSwMTable DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
    LOG_PRINT(LOG_INFO,"Sending failure alarm: INFO_BPM_SW_OFFER_FAIL");
    sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_FAIL;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
    sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
    sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,receiveMsgPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
        "Sw Offer for NodeType [%s] FAILED ChasisFrameId [%d],SlotId [%d]",
        type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 
    //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"insertSwMTable Success");

  /*Send Ack of Set command */
  cfgSendAckToCm();
  /*alarm to be raised */
  LOG_PRINT(LOG_INFO,"Sending success alarm: INFO_BPM_SW_OFFER_SUCCESS = %d\n",INFO_BPM_SW_OFFER_SUCCESS);
  sysAlarmBuff.sysAlarm.sysalarmId = INFO_BPM_SW_OFFER_SUCCESS;
  sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
  sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_ICC;
  sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->chasisFrameId;
  sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
  convertNodeType(type,receiveMsgPtr->nodeType);
  /*sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
      "Sw Offer for NodeType [%s] completed ChasisFrameId [%d],SlotId [%d]",
      type,receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2));//Changed for issue #0031513 Gaurav Sinha 13 JULY 2016 */
  sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
      "Sw Upgrade Offer Completed at Chasis [%d] slot [%d] for SwVersion [%s]  NodeType [%s]",
      receiveMsgPtr->chasisFrameId,(receiveMsgPtr->slotId-2),receiveMsgPtr->upgradeVersion,type); 
  //FillObjTypeFromNodeType(receiveMsgPtr->nodeType,sysAlarmBuff.sysAlarm.info3);
  cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);



  free(swMOfferIpTableDbPtr);
  LOG_PRINT(LOG_INFO,"setIpBtsSwMOfferTableHandler : Exiting function");

}

/******************************* Function  Header*****************************
Function Name : setIpBtsSwMNodeTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles BSC software activation, IP_BTS software downlaod 
and activation procedure
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void setIpBtsSwMNodeTableHandler()
{
  SwMNodeTableApi *receiveMsgPtr = NULL;
  receiveMsgPtr = (SwMNodeTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
  I_U32 tokenNum;
  //I_U32 token[MAX_DIGITS];
  I_U32 token[MAX_DIGITS+1];//Mantis 31507 Gaurav Sinha 13 July 2016
  I_U32 errCause;
  I_U8 chasisFrameId;
  I_U8 slotId;
  I_S32 ret = ZERO ;

  LOG_PRINT(LOG_INFO,"setIpBtsSwMNodeTableHandler : Entering function");
  LOG_PRINT(LOG_INFO,"Recieved request for SwVersion: %s",receiveMsgPtr->swVersionNew);
  LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
  LOG_PRINT(LOG_INFO,"SwAction: %d",receiveMsgPtr->swAction);

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);


    if ( (receiveMsgPtr->chasisFrameId != chasisFrameId) || (receiveMsgPtr->slotId != slotId) )
    {
      LOG_PRINT(LOG_DEBUG,"ChasisFrameId or SlotId is not of Active Card ");
      cfgSendNackToCm(CM_ERR_CHASISID_SLOTID_PROVIDED_NOT_ACTIVE);
      return;
    }
  LOG_PRINT(LOG_INFO,"FrameId: %d",receiveMsgPtr->chasisFrameId); 
  LOG_PRINT(LOG_INFO,"SlotId: %d",receiveMsgPtr->slotId); 

  if ((receiveMsgPtr->nodeType != SYS_NODE_TYPE_R2_BTS_IP) && (receiveMsgPtr->nodeType != SYS_NODE_TYPE_R3_BTS))  
  {
    LOG_PRINT(LOG_DEBUG,"Invalid NodeType recieved");
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return; 
  }

  /*Check Sw Version is in correct format*/
     tokenNum = 4; //except for IP-BTS all versions are 3 byte
  if (convertInputStringToNumber(receiveMsgPtr->swVersionNew,&tokenNum,
        token,&errCause) == SW_VER_SUCCESS)
  {
     if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255) || (token[3] > 255))        
    //if ((token[0] > 255) || (token[1] > 255) || (token[2] > 255))        
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

  if (receiveMsgPtr->swAction == SW_DOWNLOAD)  
  {
    performR2BtsIPSwDownloadOperation(receiveMsgPtr);
  }
  else if (receiveMsgPtr->swAction == SW_ACTIVATE)  
  {
    performR2BtsIPSwActivationOperation(receiveMsgPtr);
  }
  else
  {
    LOG_PRINT(LOG_DEBUG,"Invalid request recieved");
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return; 
  }
  LOG_PRINT(LOG_INFO,"setSwMNodeTableHandler : Exiting function");
}


/******************************* Function  Header*****************************
   Function Name : performR2BtsIPSwDownloadOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles R@BTS software download procedure
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void performR2BtsIPSwDownloadOperation(SwMNodeTableApi *receiveMsgPtr)
{
  BicStatusTableIndices bicStatusTableIndex;
  BicStatusTableApi *bicStatusDbPtr = NULL;
  SwMTableApi *swMTableDbPtr = NULL;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices swMNodeTableIndex;
  SwMTableIndices swMTableIndex;
  I_S32 ret = ONE;
  I_U32 index;
  I_U8 swDownloadCount = 0;
  I_S32 actionInProgress = I_FALSE;
  I_U32 nodeType =0, failType =0, swStatus = 0;

  LOG_PRINT(LOG_INFO,"performR2BtsIPSwDownloadOperation:Entering function");
  
  swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
  swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
  swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
  swMNodeTableIndex.slotId = receiveMsgPtr->slotId;
  swMTableIndex.nodeType = receiveMsgPtr->nodeType;
  strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);
  swMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
  swMTableIndex.slotId = receiveMsgPtr->slotId;

  if(getIndex(receiveMsgPtr->nodeIdentity, &index) == CFG_FAILURE)
  {
    LOG_PRINT(LOG_CRITICAL,"BIC/R2_BTS_IP[%d] is not present in Internal Data Structure", receiveMsgPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return;
  }
  else
  {
    
    /*Removing this check as not required in case of R2_BTS_IP or R3_BTS*/
    /*if (gBtsData[index].btsState == unlocked) 
    {
      LOG_PRINT(LOG_DEBUG,"BIC/R2_BTS_IP is in UnLocked state");
      LOG_PRINT(LOG_DEBUG,"Download allowed only if BIC/R2_BTS_IP is in Locked state");
      cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
      return;
    }*/
    if (gBtsData[index].btsState == unlockInProgress)
    {
      LOG_PRINT(LOG_DEBUG,"BIC/R2_BTS_IP is UnLock in Progress state");
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
      return;
    }
    else if (gBtsData[index].btsState == lockInProgress)
    {
      LOG_PRINT(LOG_DEBUG,"BIC/R2_BTS_IP is Lock in Progress state");
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"BIC/R2_BTS_IP is in Locked state");
  }

  /*Check if requested sw version of R2_BTS_IP is present in SwM table */
  ret = getSwMTable(&swMTableIndex,&swMTableDbPtr);
  if (swMTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"Software version is not present in SwMTable");
    cfgSendNackToCm(CM_ERR_VERSION_NOT_FOUND);
    return;
  }
  else if (swMTableDbPtr->deletionInProgress == I_TRUE)
  {
    LOG_PRINT(LOG_DEBUG,"Deletion is in progress for the req Sw version");
    if (swMTableDbPtr != NULL)
      free(swMTableDbPtr);
    cfgSendNackToCm(CM_ERR_SW_DEL_IN_PROGRESS);
    return; 
  }

  /*Check if for the nodeId and nodeType, there is a record in SwMNodeTable table */
  ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    free(swMTableDbPtr);  /* Mantis Fixed #4819 */
    return;
  }
  /*Check if requested Sw version is active or inactive SwVersion in SwMNode Table*/
  else if (strcmp(swMNodeTableDbPtr->swVersionActive,receiveMsgPtr->swVersionNew) == ZERO ||
      strcmp(swMNodeTableDbPtr->swVersionInactive,receiveMsgPtr->swVersionNew) == ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Req Sw version is already downloaded on the node");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    free(swMTableDbPtr);
    cfgSendNackToCm(CM_ERR_VERSION_ALREADY_AVAILABLE);
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
    free(swMTableDbPtr);
    cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
    return;
  }


  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);
  /*Check the IP link Status for the node R2_BTS_IP */
  bicStatusTableIndex.bicId = receiveMsgPtr->nodeIdentity;
  /* Check R2_BTS_IP is Connect or Not */
  LOG_PRINT(LOG_INFO, "performR2BtsIPSwDownloadOperation : Going to Check BTS_IP is Connected or Not ");
  if(getBicStatusTable(&bicStatusTableIndex, &bicStatusDbPtr) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_INFO, "performR2BtsIPSwDownloadOperation : No row exists in BicStatusTable ");
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  if(bicStatusDbPtr->btsIpLinkStatus!=ABIS_IP_UP )/* Change For R2.8*/
  {
    LOG_PRINT(LOG_INFO, "performR2BtsIPSwDownloadOperation : Send Nack to CM BTS_IP Not Connected ");
    cfgSendNackToCm(CM_ERR_BTS_IP_LINK_DOWN); // For IP_BTS it is updated as CM_ERR_BTS_IP_NOT_ESTABLISHED
    free(bicStatusDbPtr);
    return;
  }


  /* check if activation is in progress for BSC/EIC/DSP/R2_BTS/R2_BTS_TRX/R2_BTS_IP/R2_BTS_IP_TRX/R3_BTS/R3_BTS_TRX */
  actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
    fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
    return;
  }

  /*Update record in SwMNode table indicating sw download is in progress */
  if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
        SW_DOWNLOAD_IN_PROGRESS,SW_DOWNLOAD,receiveMsgPtr->swVersionNew) != 
      CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    free(swMTableDbPtr);   /* Mantis Fixed #4819 */
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");

  /*Increment the swDownloadCount value in T3 table for requested sw version */
  swDownloadCount = swMTableDbPtr->swDownloadCount + 1;   
  free(swMTableDbPtr);
  if (updateCountInSwMTable(swMTableIndex,swDownloadCount) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

  /*send SET Ack message to OMC */
  cfgSendAckToCm();

  /*Send INSTALL_REQ to the SwMH to download the software */
  LOG_PRINT(LOG_INFO,"Sending Sw Download Request");
  sendIpBtsSwDownloadRequest(receiveMsgPtr);
  LOG_PRINT(LOG_INFO,"performR2BtsIPSwDownloadOperation:Exiting function");
}

/******************************* Function  Header*****************************
   Function Name : sendIpBtsSwDownloadRequest()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Sends INSTALL_REQ to SWMH for downloading the BTS_IP release at BTS 
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void sendIpBtsSwDownloadRequest(SwMNodeTableApi *receiveMsgPtr)
{
  SwMOfferTableApi *swMOfferTableDbPtr = NULL;
  SwMOfferIpTableApi *swMOfferIpTableDbPtr = NULL;
  OamsCfgSwmhSwInstallReq swInstallReqBuff;
  SwMOfferIpTableIndices swMOfferIpTableindex;
  I_S32 ret = ONE;
  I_U8 chasisFrameId;
  I_U8 slotId;
  I_U32 applTei;

  LOG_PRINT(LOG_INFO,"sendIpBtsSwDownloadRequest:Entering function");
  LOG_PRINT(LOG_INFO,"OamsCfgSwmhSwInstallReq : %d",sizeof(OamsCfgSwmhSwInstallReq));
  LOG_PRINT(LOG_INFO,"OamsSwmhAbihmSwInstallReq : %d",sizeof(OamsSwmhAbihmSwInstallReq));
  LOG_PRINT(LOG_INFO,"OamsCfgSwmhCvActReq : %d",sizeof(OamsCfgSwmhCvActReq));
  LOG_PRINT(LOG_INFO,"OamsSwmhAbihmCvActReq : %d",sizeof(OamsSwmhAbihmCvActReq));

  if (getApplTei(receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity,
        &applTei) !=CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

  swMOfferIpTableindex.nodeType = receiveMsgPtr->nodeType;
  strcpy(swMOfferIpTableindex.upgradeVersion,receiveMsgPtr->swVersionNew);

  ret = getSwMOfferIpTable(&swMOfferIpTableindex,&swMOfferIpTableDbPtr);
  if (ret != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_INFO,"No Data Present in DB for sending INSTALL_REQ to SWMH");
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }


  swInstallReqBuff.nodeType = receiveMsgPtr->nodeType;  
  swInstallReqBuff.nodeIdentity = receiveMsgPtr->nodeIdentity;
  swInstallReqBuff.applTei = applTei;
  strcpy(swInstallReqBuff.softPack,receiveMsgPtr->swVersionNew);
  swInstallReqBuff.ftpServerAddress = swMOfferIpTableDbPtr->ftpServerAddress;
  strcpy(swInstallReqBuff.ftpUsrName,swMOfferIpTableDbPtr->loginName);
  strcpy(swInstallReqBuff.ftpPassword,swMOfferIpTableDbPtr->password);
  strcpy(swInstallReqBuff.ftpFilePathName,swMOfferIpTableDbPtr->tarPathName);

  LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_SWMH_SW_INSTALL_REQ to Swmh..");
  LOG_PRINT(LOG_INFO,"Sending request value for SP: %s",swInstallReqBuff.softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",swInstallReqBuff.nodeType,swInstallReqBuff.nodeIdentity);
  LOG_PRINT(LOG_INFO,"ApplTei::%ld",swInstallReqBuff.applTei);
  LOG_PRINT(LOG_INFO,"FTP Server Address::%ld",swInstallReqBuff.ftpServerAddress);
  LOG_PRINT(LOG_INFO,"FTP UserName:%s",swInstallReqBuff.ftpUsrName);
  LOG_PRINT(LOG_INFO,"FTP Password:%s",swInstallReqBuff.ftpPassword);
  LOG_PRINT(LOG_INFO,"FTP FILE PATH NAME:%s",swInstallReqBuff.ftpFilePathName);
  LOG_PRINT(LOG_INFO,"UserName lenfth:%d",strlen(swInstallReqBuff.ftpUsrName));
  cfgSendMessage((I_Void *)&swInstallReqBuff, sizeof(OamsCfgSwmhSwInstallReq), 
      ENT_OAMS_SWMH, OAMS_CFG_SWMH_SW_INSTALL_REQ, 0);

  LOG_PRINT(LOG_INFO,"sendIpBtsSwDownloadRequest:Exiting function");
}

/******************************* Function  Header:*****************************
   Function Name : swInstallAckHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Install Ack recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void swInstallAckHandler()
{
  OamsSwmhCfgSwInstallAck *swInstallAckPtr = NULL;
  swInstallAckPtr = (OamsSwmhCfgSwInstallAck *)gCfgMsgBuf;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_U8 type[4];
  I_S32 ret = CFG_FAILURE;
  
  LOG_PRINT(LOG_INFO,"swInstallAckHandler:Entering function");
  
  sApiSwMNodeTableIndices.nodeType = swInstallAckPtr->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = swInstallAckPtr->nodeIdentity;

  LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swInstallAckPtr->softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",swInstallAckPtr->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swInstallAckPtr->nodeIdentity);

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;

  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        swInstallAckPtr->nodeType,swInstallAckPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  if(strcmp(swMNodeTableDbPtr->swVersionNew,swInstallAckPtr->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in Install ACK is not same as downloaded SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
    return;
  }
  /*Check if in SwMNode table,the status is NOT swDownloadInProgress or 
   * swActivationInProgress */
  if (swMNodeTableDbPtr->swStatus != SW_DOWNLOAD_IN_PROGRESS) 
  {
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_DNLD_STATUS_MISMATCH);
  LOG_PRINT(LOG_INFO,"swInstallAckHandler:Exiting function");
    return;
  }
  else
  {
    LOG_PRINT(LOG_DEBUG,"Rcvd SP version is  already set as Download in progress for the node");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    /* Send Alarm */
    LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_SW_INSTALLATION_INITIATED");
    sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_INSTALLATION_INITIATED;
    sysAlarmBuff.sysAlarm.key1 = swInstallAckPtr->nodeIdentity;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,swInstallAckPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Installation for SwVer [%s] NodeType [%s] has been started on NodeId [%d]",
          swInstallAckPtr->softPack,type,swInstallAckPtr->nodeIdentity); 
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
  }
  LOG_PRINT(LOG_INFO,"swInstallAckHandler:Exiting function");
}
/******************************* Function  Header:*****************************
   Function Name : swInstallNackHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Install Nack recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void swInstallNackHandler()
{
   I_U8 swDownloadCount = 0;
  OamsSwmhCfgSwInstallNack *swInstallNackPtr = NULL;
  swInstallNackPtr = (OamsSwmhCfgSwInstallNack *)gCfgMsgBuf;
  SwMTableApi *swMTablePtr = NULL;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMTableIndices sApiSwMTableIndices;
  SwMOfferIpTableIndices swMOfferIpTableIndex;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_S8 oprStatus[] = "Sw Dnld";
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_U8 string[MAX_STRING_LENGTH];
  I_U8 type[4];
  I_S32 ret = CFG_FAILURE;

  LOG_PRINT(LOG_INFO,"swInstallNackHandler:Entering function");
  LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swInstallNackPtr->softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",swInstallNackPtr->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swInstallNackPtr->nodeIdentity);

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }

  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  sApiSwMTableIndices.nodeType = swInstallNackPtr->nodeType;
  strcpy(sApiSwMTableIndices.swVersion,swInstallNackPtr->softPack);
  sApiSwMTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMTableIndices.slotId = slotId;

  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;
  sApiSwMNodeTableIndices.nodeType = swInstallNackPtr->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = swInstallNackPtr->nodeIdentity;

  swMOfferIpTableIndex.nodeType = swInstallNackPtr->nodeType;
  strcpy(swMOfferIpTableIndex.upgradeVersion,swInstallNackPtr->softPack);
  //swMOfferTableIndex.chasisFrameId = chasisFrameId;
  //swMOfferTableIndex.slotId = slotId;
  
  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        swInstallNackPtr->nodeType,swInstallNackPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  if(strcmp(swMNodeTableDbPtr->swVersionNew,swInstallNackPtr->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in SW_INSTALL_NACK is not same as downloaded SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
    return;
  }
  if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_DOWNLOAD_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");   

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);
   /*Retreive the count value from SwM Table */
   if (getSwMTable(&sApiSwMTableIndices,&swMTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwMTable DB call is getting failed..");
      return;
   }

   /*Decrement the swDownloadCount value in T3 table for requested sw version*/
   swDownloadCount = swMTablePtr->swDownloadCount - 1;   
   if (updateCountInSwMTable(sApiSwMTableIndices,swDownloadCount) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
      if (swMTablePtr != NULL)
         free(swMTablePtr);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

#if 0
  /*Delete the record of the requested software Pack from SwmOfferTable Table */
  if (deleteSwMOfferIpTable(&swMOfferIpTableIndex) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferIpTable DB call is getting failed");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
  }
  else
    LOG_PRINT(LOG_INFO,"deleteSwMOfferIpTable Success");

  /*Delete the record of the requested software Pack from SwmTable Table */
  if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
    return;
  }
  else
  {
 #endif
    /* Send Alarm */
    LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_SW_INSTALLATION_NOT_ACCPETED");
    sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_INSTALLATION_NOT_ACCPETED;
    sysAlarmBuff.sysAlarm.key1 = swInstallNackPtr->nodeIdentity;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
    sysAlarmBuff.sysAlarm.alarmReason = swInstallNackPtr->nackCause;
    getStringForSwmhErrorCause(swInstallNackPtr->nackCause,oprStatus,
        swInstallNackPtr->softPack,swInstallNackPtr->nodeType,
        swInstallNackPtr->nodeIdentity,string);
  convertNodeType(type,swInstallNackPtr->nodeType);
  sysAlarmBuff.sysAlarm.infoStrLen = 
    sprintf(sysAlarmBuff.sysAlarm.infoString, 
        "SW INSTALL NACK for SP val [%s] NodeType [%s] is rcvd for NodeId [%d]",
        swInstallNackPtr->softPack,type,swInstallNackPtr->nodeIdentity); 
  /*
    sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,string); */
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
 // }
  if (swMTablePtr != NULL)
    free(swMTablePtr);
  LOG_PRINT(LOG_INFO,"swInstallNackHandler:Exiting function");
}
/******************************* Function  Header:*****************************
   Function Name : swInstallSuccessHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Install Ack recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void swInstallSuccessHandler()
{
  OamsSwmhCfgSwInstallSuccess *swInstallSuccessPtr = NULL;
  swInstallSuccessPtr = (OamsSwmhCfgSwInstallSuccess *)gCfgMsgBuf;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMOfferIpTableIndices swMOfferIpTableIndex;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_U8 type[4];
  I_S32 ret = CFG_FAILURE;

  LOG_PRINT(LOG_INFO,"swInstallSuccessHandler:Entering function");
  LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swInstallSuccessPtr->softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",swInstallSuccessPtr->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swInstallSuccessPtr->nodeIdentity);

  sApiSwMNodeTableIndices.nodeType = swInstallSuccessPtr->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = swInstallSuccessPtr->nodeIdentity;

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;

  swMOfferIpTableIndex.nodeType = swInstallSuccessPtr->nodeType;
  strcpy(swMOfferIpTableIndex.upgradeVersion,swInstallSuccessPtr->softPack);
  //swMOfferIpTableIndex.chasisFrameId = chasisFrameId;
  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        swInstallSuccessPtr->nodeType,swInstallSuccessPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  if(strcmp(swMNodeTableDbPtr->swVersionNew,swInstallSuccessPtr->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in Install SUCCESS is not same as downloaded SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
    return;
  }
  /*Check if in SwMNode table,the status is NOT swDownloadInProgress or 
   * swActivationInProgress */
  if (swMNodeTableDbPtr->swStatus == SW_DOWNLOAD_IN_PROGRESS) 
  {
    if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_DOWNLOAD_SUCCESS,SW_NO_ACTION, " ") != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");   

    if(updateVersionInactiveInSwMNodeTable(sApiSwMNodeTableIndices,swMNodeTableDbPtr->swVersionNew) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateVersionInactiveInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"updateVersionInactiveInSwMNodeTable Success");   
#if 0    
  /*Delete the record of the requested software Pack from SwmOfferIpTable Table */
  if (deleteSwMOfferIpTable(&swMOfferIpTableIndex) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferIpTable DB call is getting failed");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
  }
  else
    LOG_PRINT(LOG_INFO,"deleteSwMOfferIpTable Success");
#endif
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);

    /* Send Alarm */
    LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_SW_INSTALLATION_SUCCESS");
    sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_DWNLD_COMPLETED;
    sysAlarmBuff.sysAlarm.key1 = swInstallSuccessPtr->nodeIdentity;
      sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
    sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
    convertNodeType(type,swInstallSuccessPtr->nodeType);
    sysAlarmBuff.sysAlarm.infoStrLen = 
      sprintf(sysAlarmBuff.sysAlarm.infoString,
          "Sw Installation for SwVer [%s] NodeType [%s] is Completed on NodeId [%u]",
          swInstallSuccessPtr->softPack,type,swInstallSuccessPtr->nodeIdentity); 
    cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
        ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
  }
  else
  {
    LOG_PRINT(LOG_DEBUG,"BTS INSTALLATION can not be completed because swStatus was not set as DNLD_IN_PROGRESS");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
  LOG_PRINT(LOG_INFO,"swInstallSuccessHandler:Exiting function");
    return;
  }
  LOG_PRINT(LOG_INFO,"swInstallSuccessHandler:Exiting function");
}
/******************************* Function  Header:*****************************
Function Name : swInstallFailureHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Install Ack recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void swInstallFailureHandler()
{
   I_U8 swDownloadCount = 0;
  OamsSwmhCfgSwInstallFailure *swInstallFailurePtr = NULL;
   SwMTableApi *swMTablePtr = NULL;
  swInstallFailurePtr = (OamsSwmhCfgSwInstallFailure *)gCfgMsgBuf;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMTableIndices sApiSwMTableIndices;
  SwMOfferIpTableIndices swMOfferIpTableIndex;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_S8 oprStatus[] = "Sw Dnld";
  I_U8 string[MAX_STRING_LENGTH];
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_U8 type[4];
  I_S32 ret = CFG_FAILURE;

  LOG_PRINT(LOG_INFO,"swInstallFailureHandler:Entering function");
  LOG_PRINT(LOG_INFO,"Recieved SwVersion: %s",swInstallFailurePtr->softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",swInstallFailurePtr->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",swInstallFailurePtr->nodeIdentity);

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;
  sApiSwMNodeTableIndices.nodeType = swInstallFailurePtr->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = swInstallFailurePtr->nodeIdentity;
  
  sApiSwMTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMTableIndices.slotId = slotId;
  sApiSwMTableIndices.nodeType = swInstallFailurePtr->nodeType;
  strcpy(sApiSwMTableIndices.swVersion,swInstallFailurePtr->softPack);


  swMOfferIpTableIndex.nodeType = swInstallFailurePtr->nodeType;
  strcpy(swMOfferIpTableIndex.upgradeVersion,swInstallFailurePtr->softPack);
  //swMOfferIpTableIndex.chasisFrameId = chasisFrameId;
  //swMOfferTableIndex.slotId = slotId;

  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        swInstallFailurePtr->nodeType,swInstallFailurePtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  if(strcmp(swMNodeTableDbPtr->swVersionNew,swInstallFailurePtr->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in SW_INSTALL_FAILED is not same as downloaded SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
    return;
  }
  if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_DOWNLOAD_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");   

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);
   /*Retreive the count value from SwM Table */
   if (getSwMTable(&sApiSwMTableIndices,&swMTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwMTable DB call is getting failed..");
      return;
   }

   /*Decrement the swDownloadCount value in T3 table for requested sw version*/
   swDownloadCount = swMTablePtr->swDownloadCount - 1;   
   if (updateCountInSwMTable(sApiSwMTableIndices,swDownloadCount) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
      if (swMTablePtr != NULL)
         free(swMTablePtr);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

#if 0
  /*Delete the record of the requested software Pack from SwmOfferIpTable Table */
  if (deleteSwMOfferIpTable(&swMOfferIpTableIndex) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferIpTable DB call is getting failed");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
  }
  else
    LOG_PRINT(LOG_INFO,"deleteSwMOfferIpTable Success");

  /*Delete the record of the requested software Pack from SwmTable Table */
  if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"deleteSwMTable Success");
  
#endif 
  /* Send Alarm */
  LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_SW_INSTALLATION_FAILED");
  sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_DWNLD_FAILED;
  sysAlarmBuff.sysAlarm.key1 = swInstallFailurePtr->nodeIdentity;
    sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
  sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
  sysAlarmBuff.sysAlarm.alarmReason = swInstallFailurePtr->nackCause;
  getStringForSwmhInstallFailureCause(swInstallFailurePtr->nackCause,oprStatus,
      swInstallFailurePtr->softPack,swInstallFailurePtr->nodeType,
      swInstallFailurePtr->nodeIdentity,string);
  sysAlarmBuff.sysAlarm.infoStrLen = 
    sprintf(sysAlarmBuff.sysAlarm.infoString,string); 

  cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
  LOG_PRINT(LOG_INFO,"swInstallFailureHandler:Exiting function");
}
/******************************* Function  Header*****************************
   Function Name : performR2BtsIPSwActivationOperation()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Handles BIC/TRX/BTS software activation procedure
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void performR2BtsIPSwActivationOperation(SwMNodeTableApi *receiveMsgPtr)
{
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices swMNodeTableIndex;
  SwMTableIndices swMTableIndex;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0};
  I_S32 ret = ONE;
  I_U32 index;
  I_U32 status;
  I_S32 actionInProgress = 0;
  I_U32 nodeType =0, failType =0, swStatus = 0;
  I_U8 type[4];


  LOG_PRINT(LOG_INFO,"performR2BtsIPSwActivationOperation:Entering function");

  swMNodeTableIndex.nodeType = receiveMsgPtr->nodeType;
  swMNodeTableIndex.nodeIdentity = receiveMsgPtr->nodeIdentity;
  swMTableIndex.nodeType = receiveMsgPtr->nodeType;
  strcpy(swMTableIndex.swVersion,receiveMsgPtr->swVersionNew);
  swMNodeTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
  swMNodeTableIndex.slotId = receiveMsgPtr->slotId;
  swMTableIndex.chasisFrameId = receiveMsgPtr->chasisFrameId;
  swMTableIndex.slotId = receiveMsgPtr->slotId;
  /*Check the admin state of R2_BTS_IP */
  if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R2_BTS_IP) {
    //LOG_PRINT(LOG_INFO,"Recieved R2_BTS_IP  Sw Download Request"); Mantis #0031565 Gaurav Sinha
    LOG_PRINT(LOG_INFO,"Recieved R2_BTS_IP  Sw Activate Request");
  }
  else if (receiveMsgPtr->nodeType == SYS_NODE_TYPE_R3_BTS) {
    //LOG_PRINT(LOG_INFO,"Recieved R3_BTS  Sw Download Request"); Mantis #0031565 Gaurav Sinha
    LOG_PRINT(LOG_INFO,"Recieved R3_BTS  Sw Activate Request");
    //return; Mantis #0031565 Gaurav Sinha
  }

  if(getIndex(receiveMsgPtr->nodeIdentity, &index) == CFG_FAILURE)
  {
    LOG_PRINT(LOG_CRITICAL,"BtsId[%d] is not present in Internal Data Structure", receiveMsgPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
    return;
  }
  else 
  {
    if (gBtsData[index].btsState == unlocked) 
    {
      LOG_PRINT(LOG_DEBUG,"BtsId is in UnLocked state");
      LOG_PRINT(LOG_DEBUG,"Activate allowed only if BTS is in Locked state");
      cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
      return;
    }
    else if (gBtsData[index].btsState == unlockInProgress)
    {
      LOG_PRINT(LOG_DEBUG,"BTS is UnLock in Progress state");
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
      return;
    }
    else if (gBtsData[index].btsState == lockInProgress)
    {
      LOG_PRINT(LOG_DEBUG,"BTS is Lock in Progress state");
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
      return;
    }
    else
      LOG_PRINT(LOG_INFO,"BTS is in Locked state");
  }
  /*Check if for the nodeId and nodeType, there is a record in SwMNodeTable table */
  ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if requested Sw version is active SwVersion in SwMNode Table*/
  else if (strcmp(swMNodeTableDbPtr->swVersionActive,
        receiveMsgPtr->swVersionNew) == ZERO )
  {
    LOG_PRINT(LOG_DEBUG,"Requested Sw version is already activated on Node");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_VERSION_ALREADY_ACTIVATE);
    return;
  }
  /*Check if requested Sw version is inactive SwVersion in SwMNode Table*/
  else if (strcmp(swMNodeTableDbPtr->swVersionInactive,
        receiveMsgPtr->swVersionNew) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Req Sw version is not available for activation");
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
    LOG_PRINT(LOG_DEBUG,"Either Download or Activation is in progress ");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_NODE_ALREADY_BUSY_WITH_DWNLD_OR_ACT);
    return;
  }

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);
  /*Check the link Status for the node */
  if (getBtsIpLinkStatus(receiveMsgPtr->nodeIdentity,
        &status) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"getBtsIpLinkStatus DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
  }
  LOG_PRINT(LOG_INFO,"IPLink Status: %d",status);
  if (status != CONNECTED)
  {
    LOG_PRINT(LOG_DEBUG,"IP link is not Connected");

    cfgSendNackToCm(CM_ERR_BTS_IP_LINK_DOWN); // It should be updated as CM_ERR_BTS_IP_NOT_ESTABLISHED 
    return;
  }

  /* check if activation is in progress for BSC/EIC/DSP/R2_BTS/R2_BTS_TRX/R2_BTS_IP/R2_BTS_IP_TRX/R3_BTS/R3_BTS_TRX */
  actionInProgress = isActivationOrDwnldInProgressForBscEicDspBicTrx( &nodeType, &swStatus );
  if ( actionInProgress == I_TRUE )
  {
    LOG_PRINT(LOG_DEBUG,"Activation is in progress for nodeType:%d", nodeType);
    fillFailTypeFromNodeType(nodeType, failType)
      cfgSendNackToCm(failType);
    return;
  }

  /*Update record in SwMNode table indicating sw activation is in progress */
  if (updateSwStatusActionVersionInSwMNodeTable(swMNodeTableIndex,
        SW_ACTIVATION_IN_PROGRESS,SW_ACTIVATE,receiveMsgPtr->swVersionNew) != 
      CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");

  /*send SET Ack message to OMC */
  cfgSendAckToCm();

  /*Send the CvActivation request to SwMH module */
  LOG_PRINT(LOG_INFO,"Sending Sw Activation Request");
  sendCvActivationRequest(receiveMsgPtr);

  /*Mantis Fix : 10735*/
  LOG_PRINT(LOG_INFO,"Sending Alarm: EVENT_SW_ACT_STARTED");
  sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_ACT_STARTED; 
  sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION; 
  sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC; /*OAMS_OBJTYPE_EIC;*/
  sysAlarmBuff.sysAlarm.key1 = receiveMsgPtr->nodeIdentity;
  //sysAlarmBuff.sysAlarm.key2 = receiveMsgPtr->slotId;
  convertNodeType(type,receiveMsgPtr->nodeType);
  sysAlarmBuff.sysAlarm.infoStrLen = 
    sprintf(sysAlarmBuff.sysAlarm.infoString, 
        " Act for SP val [%s] NodeType [%s] is started on NodeId [%d]",
        receiveMsgPtr->swVersionNew,type,receiveMsgPtr->nodeIdentity); 
  cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
  /*Mantis Fix : 10735*/
  LOG_PRINT(LOG_INFO,"performR2BtsIPSwActivationOperation: Exit function");
}
/******************************* Function  Header*****************************
Function Name : sendCvActivationRequest()
Parameters    : SwMNodeTableApi *receiveMsgPtr
Return type   : I_Void
Purpose       : Sends Sw activation request to SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW 
 *****************************************************************************/
I_Void sendCvActivationRequest(SwMNodeTableApi *receiveMsgPtr)
{
   OamsCfgSwmhCvActReq cvActReqBuff;
   I_U32 applTei;
 

   LOG_PRINT(LOG_INFO,"sendCvActivationRequest:Entering function");
   if (getApplTei(receiveMsgPtr->nodeType,receiveMsgPtr->nodeIdentity,
            &applTei) !=CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getApplTei DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   cvActReqBuff.nodeType = receiveMsgPtr->nodeType;  
   cvActReqBuff.nodeIdentity = receiveMsgPtr->nodeIdentity;
   cvActReqBuff.applTei = applTei;
   strcpy(cvActReqBuff.softPack,receiveMsgPtr->swVersionNew);
   memset(cvActReqBuff.cfgData, 0, sizeof(I_S8));
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_SWMH_CV_ACT_REQ to Swmh..");
   LOG_PRINT(LOG_INFO,"Sending request for SP: %s",cvActReqBuff.softPack);
   LOG_PRINT(LOG_INFO,"NodeType: %d NodeId: %u",cvActReqBuff.nodeType,cvActReqBuff.nodeIdentity);
   LOG_PRINT(LOG_INFO,"ApplTei: %d",cvActReqBuff.applTei);
   cfgSendMessage((I_Void *)&cvActReqBuff, sizeof(OamsCfgSwmhCvActReq),
         ENT_OAMS_SWMH, OAMS_CFG_SWMH_CV_ACT_REQ, 0);
   LOG_PRINT(LOG_INFO,"sendCvActivationRequest:Exiting function");
}

/******************************* Function  Header*****************************
Function Name : cvActivationNackHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation Nack recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void cvActivationNackHandler()
{
  OamsSwmhCfgCvActNack *cvActNackPtr = NULL;
  cvActNackPtr = (OamsSwmhCfgCvActNack *)gCfgMsgBuf;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  I_U8 string[MAX_STRING_LENGTH];
  I_S8 oprStatus[] = "Sw Act";
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_S32 ret = CFG_FAILURE;

  LOG_PRINT(LOG_INFO,"cvActivationNackHandler:Entering function");

  LOG_PRINT(LOG_INFO,"Recieved SP Value: %s",cvActNackPtr->softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",cvActNackPtr->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",cvActNackPtr->nodeIdentity);
  LOG_PRINT(LOG_INFO,"NackCause: %d ",cvActNackPtr->nackCause);
  

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

  sApiSwMNodeTableIndices.nodeType = cvActNackPtr->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = cvActNackPtr->nodeIdentity;
  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;
  

  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        cvActNackPtr->nodeType,cvActNackPtr->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  if(strcmp(swMNodeTableDbPtr->swVersionNew,cvActNackPtr->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in BTS_INSTALL_FAILED is not same as downloaded SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
    return;
  }

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);


  /*Update status in SwMNode Table as Activation Failure */
  if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_ACTIVATION_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");   

  /* Send Alarm */
  LOG_PRINT(LOG_INFO,"Sending failure alarm: EVENT_BTS_START_ACTIVATE_FAIL");   
  sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_ACT_FAILED;
  sysAlarmBuff.sysAlarm.key1 = cvActNackPtr->nodeIdentity;
  sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
  sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
  sysAlarmBuff.sysAlarm.alarmReason = cvActNackPtr->nackCause;
  getStringForSwmhErrorCause(cvActNackPtr->nackCause,oprStatus,
      cvActNackPtr->softPack,cvActNackPtr->nodeType,
      cvActNackPtr->nodeIdentity,string);
  sysAlarmBuff.sysAlarm.infoStrLen = 
    sprintf(sysAlarmBuff.sysAlarm.infoString,string); 
  cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
  LOG_PRINT(LOG_INFO,"cvActivationNackHandler:Exiting function");
}

/******************************* Function  Header*****************************
Function Name : cvActivationCommitInd()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw activation Ack recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void cvActivationCommitInd()
{
  I_U8 type[4];
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_S32 ret = CFG_FAILURE;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  OamsSwmhCfgCvCommitInd *cvCommitInd = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 

  cvCommitInd = (OamsSwmhCfgCvCommitInd *)gCfgMsgBuf;

  sApiSwMNodeTableIndices.nodeType = cvCommitInd->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = cvCommitInd->nodeIdentity;

  LOG_PRINT(LOG_INFO,"cvActivationCommitInd:Entering function");

  LOG_PRINT(LOG_INFO,"Recieved SP Val: %s",cvCommitInd->softPack);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",cvCommitInd->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",cvCommitInd->nodeIdentity);

  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;

  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        cvCommitInd->nodeType,cvCommitInd->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  if(strcmp(swMNodeTableDbPtr->swVersionNew,cvCommitInd->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in Commit Ind is not same as activated SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);

    /*Update status in SwMNode Table as Activation Failed */
    if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_ACTIVATION_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return;
    }
    else{
      LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable as SW_ACTIVATION_FAILED Success");   
    }
    if(updateVersionActiveInSwMNodeTable(sApiSwMNodeTableIndices,cvCommitInd->softPack) != CLIB_SUCCESS)
    {
      LOG_PRINT(LOG_CRITICAL,"updateVersionActiveInSwMNodeTable Failed");
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return;
    }
    else{
      LOG_PRINT(LOG_INFO,"updateVersionActiveInSwMNodeTable as SP version rcvd in cvCommitInd Success");   
      cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
      return;
    }
  }

  /*Update status in SwMNode Table as Activation Success */
  if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_ACTIVATION_SUCCESS,SW_NO_ACTION, " ") != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");   

      if (updateVersionActiveInactiveDnldedInSwMNodeTable(
               sApiSwMNodeTableIndices,swMNodeTableDbPtr->swVersionNew,swMNodeTableDbPtr->swVersionActive, " " ) != CLIB_SUCCESS)
      {
        LOG_PRINT(LOG_MAJOR,"updateVersionActiveInactiveDnldedInSwMNodeTable Failed");
        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
        return;
      }
      else
         LOG_PRINT(LOG_INFO,"updateVersionActiveInactiveDnldedInSwMNodeTable Success");

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);

  /* Send Alarm */
  LOG_PRINT(LOG_INFO,"Sending success alarm: EVENT_CV_ACTIVATE_COMPLETED");   
  sysAlarmBuff.sysAlarm.sysalarmId = EVENT_SW_ACT_COMPLETED;
  sysAlarmBuff.sysAlarm.key1 = cvCommitInd->nodeIdentity;
  sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
  sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
  convertNodeType(type,cvCommitInd->nodeType);
  sysAlarmBuff.sysAlarm.infoStrLen = 
    sprintf(sysAlarmBuff.sysAlarm.infoString, 
        "CV Act for SP val [%s] NodeType [%s] is Completed on NodeId [%d]",
        cvCommitInd->softPack,type,cvCommitInd->nodeIdentity); 
  LOG_PRINT(LOG_INFO,"Commit_IND Info String::%s",sysAlarmBuff.sysAlarm.infoString);
  cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
  LOG_PRINT(LOG_INFO,"cvActivationCommitInd:Exiting function");
}
/******************************* Function  Header*****************************
Function Name : cvActivationStatusReport()
Parameters    : None
Return type   : I_Void
Purpose       : Handles CV_STATUS_REPORT recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void cvActivationStatusReport()
{
  OamsSwmhCfgCvStatusReport *cvStatusReport = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMNodeTableIndices swMNodeTableIndex;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_U8 string[MAX_STRING_LENGTH];
  I_S8 oprStatus[] = "Sw Act";
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_S32 ret = CFG_FAILURE;
  I_U8 type[4];

  cvStatusReport = (OamsSwmhCfgCvStatusReport *)gCfgMsgBuf;

  LOG_PRINT(LOG_INFO,"cvActivationStatusReport:Entering function");

  LOG_PRINT(LOG_INFO,"Recieved Default SP Value: %s",cvStatusReport->softPack);
  LOG_PRINT(LOG_INFO,"Recieved Default CD Value: %s",cvStatusReport->cfgData);
  LOG_PRINT(LOG_INFO,"NodeType: %d ",cvStatusReport->nodeType);
  LOG_PRINT(LOG_INFO,"NodeIdentity: %u ",cvStatusReport->nodeIdentity);
  LOG_PRINT(LOG_INFO,"Recieved Trail SP Value: %s",cvStatusReport->softPackTrail);
  LOG_PRINT(LOG_INFO,"Recieved Trail CD Value: %s",cvStatusReport->cfgDataTrail);


  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }
  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;
  sApiSwMNodeTableIndices.nodeType = cvStatusReport->nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = cvStatusReport->nodeIdentity;
  swMNodeTableIndex.nodeType = cvStatusReport->nodeType;
  swMNodeTableIndex.nodeIdentity = cvStatusReport->nodeIdentity;
  swMNodeTableIndex.chasisFrameId = chasisFrameId;
  swMNodeTableIndex.slotId = slotId;
  /*Check if for the nodeId and nodeType, there is a record in SwMNodeTable table */
  ret = getSwMNodeTable(&swMNodeTableIndex,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        cvStatusReport->nodeType,cvStatusReport->nodeIdentity);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  if(strcmp(swMNodeTableDbPtr->swVersionNew,cvStatusReport->softPackTrail) == 0)
  {
    //if (swMNodeTableDbPtr != NULL)
    //  free(swMNodeTableDbPtr);
  /* Send Alarm */
  LOG_PRINT(LOG_INFO,"Sending CV_STATUS_REPORT alarm: EVENT_RCVD_CV_STATUS_REPORT");   
  sysAlarmBuff.sysAlarm.sysalarmId = EVENT_RCVD_CV_STATUS_REPORT;
  sysAlarmBuff.sysAlarm.key1 = cvStatusReport->nodeIdentity;

  sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BIC;
  sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
  convertNodeType(type,cvStatusReport->nodeType);
  sysAlarmBuff.sysAlarm.infoStrLen = 
    sprintf(sysAlarmBuff.sysAlarm.infoString, 
        "CV STATUS REPORT for SP val [%s] NodeType [%s] is rcvd for NodeId [%d]",
        cvStatusReport->softPack,type,cvStatusReport->nodeIdentity); 
  cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
      ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);       
  }

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);
  LOG_PRINT(LOG_INFO,"cvActivationStatusReport:Exiting function");
}
/******************************* Function  Header:*****************************
   Function Name : swInstallTimeOutHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles Sw Install TimeOut recieved from SWMH
Other Note    : Added For BSC_R2.8-EXT_ALARM_NEW
 *****************************************************************************/
I_Void swInstallTimeOutHandler(I_U32 btsId)
{
   I_U8 swDownloadCount = 0;
  //OamsSwmhCfgSwInstallNack *swInstallNackPtr = NULL;
  //swInstallNackPtr = (OamsSwmhCfgSwInstallNack *)gCfgMsgBuf;
  SwMTableApi *swMTablePtr = NULL;
  SwMNodeTableApi *swMNodeTableDbPtr = NULL;
  SwMNodeTableIndices sApiSwMNodeTableIndices;
  SwMTableIndices sApiSwMTableIndices;
  SwMOfferIpTableIndices swMOfferIpTableIndex;
  OamsCfgAfhSysAlarm sysAlarmBuff = {0}; 
  I_S8 oprStatus[] = "Sw Dnld";
  I_U8 slotId;
  I_U8 chasisFrameId;
  I_U8 string[MAX_STRING_LENGTH];
  I_U8 type[4];
  I_S32 ret = CFG_FAILURE;
  I_U32 nodeType = 0;
 BicTableApi *bicTablePtr = NULL; 
 BicTableIndices bicTableIndex ;   
  LOG_PRINT(LOG_INFO,"swInstallTimeOutHandler:Entering function");
  /* getNodeTYPE (R2-IP or R3)*/
     bicTableIndex.bicId = btsId;
   if( (ret =getBicTable(&bicTableIndex,&bicTablePtr))!=CLIB_SUCCESS){
    LOG_PRINT(LOG_INFO,"getBtsTable Db call failed ErrorCause: %d",ret);
    return;
   }
   else 
    {
         if (bicTablePtr->btsType == R3_BTS)
           nodeType = SYS_NODE_TYPE_R3_BTS;
         else if (bicTablePtr->btsType == R2_BTS_IP)
           nodeType = SYS_NODE_TYPE_R2_BTS_IP;
    }
  if ( ( ret = getActiveIccSlotId( &chasisFrameId, &slotId) != CLIB_SUCCESS ) )
  {
    LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
    return;
  }

  LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
  
  

  sApiSwMNodeTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMNodeTableIndices.slotId = slotId;
  sApiSwMNodeTableIndices.nodeType = nodeType;
  sApiSwMNodeTableIndices.nodeIdentity = btsId ;

  //swMOfferTableIndex.chasisFrameId = chasisFrameId;
  //swMOfferTableIndex.slotId = slotId;
  
  /*Check if for the nodeId and nodeType, there is a record in SwMNode table */
  /*getSoftPack*/
  ret = getSwMNodeTable(&sApiSwMNodeTableIndices,&swMNodeTableDbPtr);
  if (swMNodeTableDbPtr == NULL)
  {
    LOG_PRINT(LOG_DEBUG,"No Entry for NodeType:%d NodeId:%u in SwMNodeTable",
        nodeType,btsId);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return;
  }
  sApiSwMTableIndices.nodeType = nodeType;
  strcpy(sApiSwMTableIndices.swVersion,swMNodeTableDbPtr->swVersionNew);
  sApiSwMTableIndices.chasisFrameId = chasisFrameId;
  sApiSwMTableIndices.slotId = slotId;
  
  
  swMOfferIpTableIndex.nodeType = nodeType;
  strcpy(swMOfferIpTableIndex.upgradeVersion,swMNodeTableDbPtr->swVersionNew);
  
  /*Check if req Sw version is present in downloaded SwVersion list
   *  of BSC in SwMNode Table*/
  /*if(strcmp(swMNodeTableDbPtr->swVersionNew,swInstallNackPtr->softPack) != ZERO)
  {
    LOG_PRINT(LOG_DEBUG,"Received SP version in SW_INSTALL_NACK is not same as downloaded SwVersion List of BSC");
    if (swMNodeTableDbPtr != NULL)
      free(swMNodeTableDbPtr);
    cfgSendNackToCm(CM_ERR_RCVD_VERSION_MISMATCH);
    return;
  }*/
  if(updateSwStatusActionVersionInSwMNodeTable(sApiSwMNodeTableIndices,SW_DOWNLOAD_FAILED,SW_NO_ACTION, " ") != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"updateSwStatusActionVersionInSwMNodeTable Failed");
    cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
    return;
  }
  else
    LOG_PRINT(LOG_INFO,"updateSwStatusActionVersionInSwMNodeTable Success");   

   /*Retreive the count value from SwM Table */
   if (getSwMTable(&sApiSwMTableIndices,&swMTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwMTable DB call is getting failed..");
      return;
   }

   /*Decrement the swDownloadCount value in T3 table for requested sw version*/
   swDownloadCount = swMTablePtr->swDownloadCount - 1;   
   if (updateCountInSwMTable(sApiSwMTableIndices,swDownloadCount) != 
         CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"updateCountInSwMTable Failed");
      if (swMTablePtr != NULL)
         free(swMTablePtr);
      return;
   }
   else
      LOG_PRINT(LOG_INFO,"updateCountInSwMTable Success");

  if (swMNodeTableDbPtr != NULL)
    free(swMNodeTableDbPtr);
#if 0
  /*Delete the record of the requested software Pack from SwmOfferTable Table */
  if (deleteSwMOfferIpTable(&swMOfferIpTableIndex) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMOfferIpTable DB call is getting failed");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
  }
  else
    LOG_PRINT(LOG_INFO,"deleteSwMOfferIpTable Success");

  /*Delete the record of the requested software Pack from SwmTable Table */
  if (deleteSwMTable(&sApiSwMTableIndices) != CLIB_SUCCESS)
  {
    LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call is getting failed..");
    cfgSendNackToCm(CM_ERR_DELETE_DB_OPER_FAILED);
    return;
  }
#endif
  if (swMTablePtr != NULL)
    free(swMTablePtr);
  LOG_PRINT(LOG_INFO,"swInstallTimeOutHandler:Exiting function");
}
