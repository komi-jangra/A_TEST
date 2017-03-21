/************************************************************* File Header ***
  File Name      : oamscfg_stack_object_handler.c
Purpose        : This file contains function definitions required for handling
addition/deletion/modification on stack objects.
Project        : BSC
Subsystem      : OAMS
Author         : VNL Bikram Bhatt (BB)
CSCI id        :
Version        :
 ******************************************************************** End ***/

#include "oamscfg_includes.h"

/******************************* Function  Header*****************************
  Function Name : setSs7StackTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : This can be for following:
To add new entry in Ss7Stack table
To Modify the parameters in the Ss7Stack table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setSs7StackTableHandler()
{
   Ss7StackConfigTableApi* receivedMsgPtr = (Ss7StackConfigTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   Ss7StackConfigTableApi  *ss7StackTableDbPtr = NULL;
   I_U32 outCount = ZERO, bssAdminState;
   I_U16 outSize = ZERO;
   I_Bool statusRange = FALSE;

   LOG_PRINT(LOG_INFO,"Entering function: setSs7StackTableHandler");
   LOG_PRINT(LOG_INFO,"Reseived sksCommonopc:%u sksCommonfamily:%u alarmLevel:%u",
         receivedMsgPtr->sksCommonopc,receivedMsgPtr->sksCommonfamily,receivedMsgPtr->alarmLevel);


   /* Check whether request received request is for modification or addition */
   if(CLIB_SUCCESS == getallSs7StackConfigTable(&ss7StackTableDbPtr, &outCount, &outSize))
   {
      if (ss7StackTableDbPtr->index == receivedMsgPtr->index)
      {
         LOG_PRINT(LOG_INFO, "Modification request received for Ss7StackTable");
         modifySs7StackTable(receivedMsgPtr, ss7StackTableDbPtr);
      }
      else
      {
         LOG_PRINT(LOG_INFO, "Row already exists in Ss7StackConfig Table");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(ss7StackTableDbPtr);
      }
      return;
   }
   else /* Request received for addition */
   {
      /* Check if BSS Admin State is LOCK or not */ 
      if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"getBssAdminState DB call is geting failed..");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;     
      }  
      if (bssAdminState != LOCKED || gBssState != locked)
      {
         LOG_PRINT(LOG_DEBUG,"BSS is not locked: Precondition Failed, Sending Nack");
         cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
         return;    
      }

      /* Perform range check on received parameters */
      statusRange = ss7StackRangeChk(receivedMsgPtr);
      if(!statusRange)
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(Ss7StackConfigTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_SS7STACKCONFIGTABLE, SCM_ADD, OAM_SCM_SS7_STACK_CONFIG);

      /* Frame and Send the message to the OIL */
      if (!fillAndSendOamScmSs7StackConfig())
      {
         sendStackProcRespToCm();
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : modifySs7StackTable()
Parameters    : Ss7StackConfigTableApi *receivedMsgPtr, Ss7StackConfigTableApi *ss7StackTableDbPtr
Return type   : I_Void
Purpose       : To Modify the parameters in the Ss7Stack table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifySs7StackTable(Ss7StackConfigTableApi *receivedMsgPtr, Ss7StackConfigTableApi *ss7StackTableDbPtr)
{
   I_Bool statusRange = FALSE, storeStatus = FALSE;

   if (receivedMsgPtr->sksCommonfamily != ss7StackTableDbPtr->sksCommonfamily ||
         receivedMsgPtr->sksCommonopc != ss7StackTableDbPtr->sksCommonopc)
   {
      LOG_PRINT(LOG_DEBUG,"Modification not allowed for family and selfPointCode");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      free(ss7StackTableDbPtr);
      return; 
   }

   if (receivedMsgPtr->alarmLevel == ss7StackTableDbPtr->alarmLevel)
   {
      LOG_PRINT(LOG_DEBUG,"Received same parameter as in DB");
      cfgSendAckToCm();
      free(ss7StackTableDbPtr);
      return; 
   }
   free(ss7StackTableDbPtr);

   /* Perform range check on received parameters */
   statusRange = ss7StackRangeChk(receivedMsgPtr);
   if(!statusRange)
   {
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return; 
   }

   /* Store the received message in global pointer */
   storeStatus = storeReceivedMsgBuffer(receivedMsgPtr, sizeof(Ss7StackConfigTableApi));
   if (!storeStatus)
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_SS7STACKCONFIGTABLE, SCM_MODIFY, OAM_SCM_ALARM_MODIFY);

   if (!fillAndSendOamScmAlarmModify() )
   {
      sendStackProcRespToCm();
      return;
   }
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmAlarmModify()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmAlarmModify(I_Void)
{
   OamScmAlarmModify alarmModify;
   Ss7StackConfigTableApi *Ss7StackConfigTableApiPtr = (Ss7StackConfigTableApi*)gStoredMsgBufPtr;

   alarmModify.alarmLevel = Ss7StackConfigTableApiPtr->alarmLevel;  

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_ALARM_MODIFY to Oil..");

   if ( cfgSendStackMessage((I_Void *)&alarmModify, sizeof(alarmModify) ) != CFG_SUCCESS )
   {
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : setAifInterfaceTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : To add new entry in AifInterface table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setAifInterfaceTableHandler()
{
   AifInterfaceTableApi* receivedMsgPtr = (AifInterfaceTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));

   AifInterfaceTableApi  *aifInterfaceTableDbPtr = NULL;
   Ss7StackConfigTableApi  *ss7StackTableDbPtr = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;
   I_Bool statusRange = FALSE;

   LOG_PRINT(LOG_INFO,"Entering function: setAifInterfaceTableHandler");
   LOG_PRINT(LOG_INFO,"Reseived interfaceId:%u interfaceType:%u dpc:%u",
         receivedMsgPtr->interfaceId,receivedMsgPtr->operationalState,receivedMsgPtr->dpc);
   LOG_PRINT(LOG_INFO,"tgpId:%u interfaceType:%u interfaceAdminState:%u",
         receivedMsgPtr->tgpId,receivedMsgPtr->operationalState,receivedMsgPtr->interfaceAdminState);

   /* Check whether request received request is for modification or addition */
   if(CLIB_SUCCESS == getallAifInterfaceTable(&aifInterfaceTableDbPtr, &outCount, &outSize))
   {
      if (aifInterfaceTableDbPtr->interfaceId == receivedMsgPtr->interfaceId)
      {
         LOG_PRINT(LOG_DEBUG, "Modification of AifInterface Table is not allowed");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      }
      else 
      {
         LOG_PRINT(LOG_DEBUG, "Row already exist in Aif Interface Table");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      }
      free(aifInterfaceTableDbPtr);
      return;
   }
   else /* Request received for addition */
   {
      /* Check whether row exists in Ss7StackConfig Table */
      if(CLIB_SUCCESS != getallSs7StackConfigTable(&ss7StackTableDbPtr, &outCount, &outSize))
      {
         LOG_PRINT(LOG_INFO, "Ss7StackConfig Table does not exists");
         cfgSendNackToCm(CM_ERR_SS7STACK_OBJ_NOT_PRESENT);
         return;
      }
      free(ss7StackTableDbPtr);

      /* Perform range check on received parameters */
      statusRange = aifInterfaceRangeChk(receivedMsgPtr);
      if(!statusRange)
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(AifInterfaceTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_AIFINTERFACETABLE, SCM_ADD, OAM_SCM_INTERFACE_CONFIG);

      /* Frame and Send the message to the OIL */
      if ( ! fillAndSendOamScmInterfaceConfig() ) 
      {
         sendStackProcRespToCm();
         return;      
      }
   }
}

#if 0 /* AbisInterface is removed */
/******************************* Function  Header*****************************
  Function Name : setAbisInterfaceTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : To add new entry in AbisInterface table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setAbisInterfaceTableHandler()
{
   AbisInterfaceTableApi* receivedMsgPtr = (AbisInterfaceTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));

   AbisInterfaceTableApi  *abisInterfaceTableDbPtr = NULL;
   AbisInterfaceTableIndices abisInterfaceTableIndex;
   abisInterfaceTableIndex.interfaceId = receivedMsgPtr->interfaceId;

   LOG_PRINT(LOG_INFO,"Entering function: setAbisInterfaceTableHandler");
   LOG_PRINT(LOG_INFO,"Reseived interfaceId:%u bicId:%u",
         receivedMsgPtr->interfaceId,receivedMsgPtr->bicId);
   LOG_PRINT(LOG_INFO,"interfaceType:%u adminState:%u",
         receivedMsgPtr->interfaceType,receivedMsgPtr->adminState);

   /* Check whether request received request is for modification or addition */
   if(CLIB_SUCCESS == getAbisInterfaceTable(&abisInterfaceTableIndex, &abisInterfaceTableDbPtr))
   {
      LOG_PRINT(LOG_DEBUG, "Modification of AbisInterface Table is not allowed");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      free(abisInterfaceTableDbPtr);
      return;
   }
   else /* Request received for addition */
   {
      if (receivedMsgPtr->bicId != INVALID_BIC)
      {
         LOG_PRINT(LOG_INFO,"Insertion allowed with Invalid BicId Only");
         cfgSendNackToCm(CM_ERR_VALID_BICID_RCVD);
         return; 
      }

      if (receivedMsgPtr->interfaceType != IF_TYPE_ABIS)
      {
         LOG_PRINT(LOG_INFO,"Invalid E1 Type received ");
         cfgSendNackToCm(CM_ERR_INVALID_E1_TYPE);
         return; 
      }

      /* Insert row in AbisInterface Table */
      AbisInterfaceTableApi abisInterfaceBuff;
      abisInterfaceBuff.interfaceId = receivedMsgPtr->interfaceId; 
      abisInterfaceBuff.bicId = INVALID_BIC;
      memcpy(abisInterfaceBuff.interfaceNameString,receivedMsgPtr->interfaceNameString,20); 
      abisInterfaceBuff.interfaceType = receivedMsgPtr->interfaceType;
      abisInterfaceBuff.adminState = UNLOCKED;
      if (insertAbisInterfaceTable(&abisInterfaceBuff) !=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"insertAbisInterfaceTable DB call is getting failed..");
         return;
      }
      else
         LOG_PRINT(LOG_INFO,"insertAbisInterfaceTable Success");

      /*Send Ack of Set command */
      cfgSendAckToCm(); 
   }
}
#endif

/******************************* Function  Header*****************************
  Function Name : setLinkSetTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : To add a row in LinkSet table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setLinkSetTableHandler()
{
   LinksetTableApi *receivedMsgPtr = (LinksetTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));

   LinksetTableApi  *linkSetTableDbPtr = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;
   I_Bool statusRange = FALSE;

   LOG_PRINT(LOG_INFO,"Entering function: setLinkSetTableHandler");
   LOG_PRINT(LOG_INFO,"Reseived linksetID:%u interfaceId:%u adjacentPointCode:%u",
         receivedMsgPtr->linksetID,receivedMsgPtr->interfaceId,receivedMsgPtr->adjacentPointCode);
   LOG_PRINT(LOG_INFO,"networkIndicator:%u adminstate:%u",
         receivedMsgPtr->networkIndicator,receivedMsgPtr->adminstate);

   /* Check whether row exists in DB for the request received request */
   if(CLIB_SUCCESS == getallLinksetTable(&linkSetTableDbPtr,&outCount,&outSize))
   {
      if (linkSetTableDbPtr->linksetID == receivedMsgPtr->linksetID)
      {
         LOG_PRINT(LOG_DEBUG, "Modification of LinkSet Table is not allowed");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      }
      else 
      {
         LOG_PRINT(LOG_DEBUG, "Row already exist in LinkSet Table");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      }
      free(linkSetTableDbPtr);
      return;
   }
   else 
   {  
      AifInterfaceTableApi  *aifInterfaceTableDbPtr = NULL;
      AifInterfaceTableIndices aifInterfaceTableIndex;
      aifInterfaceTableIndex.interfaceId = receivedMsgPtr->interfaceId;

      /* Check whether row exist in AifInterface Table */
      if(CLIB_SUCCESS != getAifInterfaceTable(&aifInterfaceTableIndex, &aifInterfaceTableDbPtr))
      {
         LOG_PRINT(LOG_DEBUG, "AifInterface Table does not exists");
         cfgSendNackToCm(CM_ERR_AIFINTERFACE_OBJ_NOT_PRESENT);
         return;
      }

      /* Check adjacentPointCode is same as in AifInterface Table*/
      /* Changes for ETISLAT SETUP Starts 
      if (aifInterfaceTableDbPtr->dpc != receivedMsgPtr->adjacentPointCode)
      {
         LOG_PRINT(LOG_DEBUG, "adjacentPointCode is not same as in AifInteface Table");
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         free(aifInterfaceTableDbPtr);
         return;
      }
      Changes for ETISLAT SETUP Ends*/
      free(aifInterfaceTableDbPtr);

      /* Perform range check on received parameters */
      statusRange = linkSetRangeChk(receivedMsgPtr);
      if(!statusRange)
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(LinksetTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_LINKSETTABLE, SCM_ADD, OAM_SCM_LINKSET_CONFIG);

      /* Frame and Send the message to the OIL */
      if (!fillAndSendOamScmLinkSetConfig()) 
      {
         sendStackProcRespToCm();
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : setTrunkTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : To configure Cic in Trunk table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setTrunkTableHandler()
{
   AiftrunkTableApi* receivedMsgPtr = (AiftrunkTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));

   AiftrunkTableApi  *AiftrunkTableDbPtr = NULL;
   AiftrunkTableIndices trunkTableIndex;
   trunkTableIndex.interfaceId = receivedMsgPtr->interfaceId;
   trunkTableIndex.tgpId = receivedMsgPtr->tgpId;
   trunkTableIndex.e1Num = receivedMsgPtr->e1Num;
   I_Bool statusRange = FALSE;
   I_U32 tsMap;
   I_U32 trunkUsageType;
   I_U32 retStatus;

   LOG_PRINT(LOG_INFO,"Entering function: setAiftrunkTableHandler");
   LOG_PRINT(LOG_INFO,"Received interfaceId:%u tgpId:%u e1Num:%u",
         receivedMsgPtr->interfaceId,receivedMsgPtr->tgpId,receivedMsgPtr->e1Num);
   LOG_PRINT(LOG_INFO,"startCic:%u endCic:%u trunkType:%u",
         receivedMsgPtr->startCic,receivedMsgPtr->endCic,receivedMsgPtr->trunkType);
   LOG_PRINT(LOG_INFO,"trunkAdminState:%u trunkReset:%u tsCicMap:%u",
         receivedMsgPtr->trunkAdminState,receivedMsgPtr->trunkReset,receivedMsgPtr->tsCicMap);

   /* Check whether row exists in DB for the request received request */
   if(CLIB_SUCCESS == getAiftrunkTable(&trunkTableIndex, &AiftrunkTableDbPtr))
   {
      LOG_PRINT(LOG_DEBUG, "Modification of trunk is not allowed");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      free(AiftrunkTableDbPtr);
      return;
   }
   else 
   {
      TrunkGroupTableApi  *trunkGroupTableDbPtr = NULL;
      TrunkGroupTableIndices trunkGroupTableIndex;
      trunkGroupTableIndex.interfaceId = receivedMsgPtr->interfaceId;
      trunkGroupTableIndex.tgpId = receivedMsgPtr->tgpId;

      /* Check whether row exists in TrunkGroup Table for received request */
      if(CLIB_SUCCESS != getTrunkGroupTable(&trunkGroupTableIndex, &trunkGroupTableDbPtr))
      {
         LOG_PRINT(LOG_DEBUG, "TrunkGroup Table does not exists");
         cfgSendNackToCm(CM_ERR_TRUNKGROUP_OBJ_NOT_PRESENT);
         return;
      }
      free(trunkGroupTableDbPtr);

      /* Perform range check on received parameters */
      statusRange = trunkRangeChk(receivedMsgPtr);
      if(!statusRange)
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return;
      }

      /* Check that the received e1Num is valid */
      TrunkTableApi *e1PerTableDbPtr = NULL;
      TrunkTableIndices e1PerTableIndex;
      e1PerTableIndex.e1Num = receivedMsgPtr->e1Num;
      if(CLIB_SUCCESS != getTrunkTable(&e1PerTableIndex, &e1PerTableDbPtr))
      {
         LOG_PRINT(LOG_DEBUG,"Received e1Num does not exist in TrunkTable");
         cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
         return;
      }

      /* Check that the received e1Num is of type AIF */
      if (e1PerTableDbPtr->usageType != SYS_E1_USAGE_AIF)
      {
         LOG_PRINT(LOG_DEBUG,"Received e1Num is not configured for A-Interface");
         cfgSendNackToCm(CM_ERR_INVALID_E1_TYPE);
         free(e1PerTableDbPtr);
         return;
      }

      /* Check that the received e1Num is mapped or not */
      if (e1PerTableDbPtr->e1Category == EXTERNAL_E1)
      {
         if (e1PerTableDbPtr->trunkPortId == INVALID_TRUNK_ID)
         {
            LOG_PRINT(LOG_DEBUG,"Received e1Num is not mapped to any trunk");
            cfgSendNackToCm(CM_ERR_E1_MAP_NOT_CREATED);
            free(e1PerTableDbPtr);
            return;
         }
      }
      free(e1PerTableDbPtr);

      /* Check that the received Cic are valid */
      if (receivedMsgPtr->startCic == INVALID_CIC || 
            receivedMsgPtr->endCic == INVALID_CIC)
      {
         LOG_PRINT(LOG_DEBUG, "Invalid Cic received from operator");
         cfgSendNackToCm(CM_ERR_INVALID_CIC_RCVD);
         return;
      }

      /* Check the uniqueness of received Cic */
      if (checkUniqueCicFromCicTable(receivedMsgPtr->startCic, receivedMsgPtr->endCic) != CFG_SUCCESS) 
      {
         cfgSendNackToCm(CM_ERR_CIC_ALREADY_EXISTS);
         return;
      }
      else 
         LOG_PRINT(LOG_INFO, "Received Cics are unique");

      /* Check the uniqueness of TimeSlot received in tsCicMap */
      LOG_PRINT(LOG_INFO, "Verifying uniqueness of received E1-Timeslot");
      if (isTimeSlotNotUsedForCicOrLink(receivedMsgPtr) != CFG_SUCCESS) 
      {
         return;
      }

      /*Changes for TsGroup Start*/
      tsMap=receivedMsgPtr->tsCicMap;
      if(AreTimeSlotsNotUsedForTsGroup(receivedMsgPtr->e1Num,tsMap) != CFG_SUCCESS)
      {
        LOG_PRINT(LOG_DEBUG,"E1Id[%u] & TsMap[0x%x] is allocated for TsGroup, sending Nack",
            receivedMsgPtr->e1Num,tsMap);
        cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_TSGROUP);
        return ;

      }
      /*Changes for TsGroup End*/

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(AiftrunkTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_AIFTRUNKTABLE, SCM_ADD, OAM_SCM_TRUNK_CIC_CONFIG);

      /* Frame and Send the message to the OIL */
      if ( ! fillAndSendOamScmTrunkCicConfig() ) 
      {
         sendStackProcRespToCm();
         return;      
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : setLinkTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : This can be for following:
To add new entry in Link table
To Modify the e1Num and timeslot in the Link table
To Lock/Unlock the Link
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setLinkTableHandler()
{
   LinkTableApi* receivedMsgPtr = (LinkTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));

   LinkTableApi  *linkTableDbPtr = NULL;
   LinkTableIndices linkTableIndex;
   linkTableIndex.linksetID = receivedMsgPtr->linksetID;
   linkTableIndex.linkId = receivedMsgPtr->linkId;
   I_Bool statusRange = FALSE;
   I_U32 cardOprState = 0;

   LOG_PRINT(LOG_INFO,"Entering function: setLinkTableHandler");
   LOG_PRINT(LOG_INFO,"Reseived linksetID:%u linkId:%u slc:%u",
         receivedMsgPtr->linksetID,receivedMsgPtr->linkId,receivedMsgPtr->slc);
   LOG_PRINT(LOG_INFO,"e1Num:%u timeSlot:%u cardNum:%u",
         receivedMsgPtr->e1Num,receivedMsgPtr->timeSlot,receivedMsgPtr->cardNum);
   LOG_PRINT(LOG_INFO,"crcFlag:%u adminState:%u ",
         receivedMsgPtr->crcFlag,receivedMsgPtr->adminState);

   /* Check whether row exists in DB for the request received request */
   if(CLIB_SUCCESS == getLinkTable(&linkTableIndex, &linkTableDbPtr))
   {
      LOG_PRINT(LOG_INFO, "Row exists in Link Table");

      if (receivedMsgPtr->slc != linkTableDbPtr->slc || 
            receivedMsgPtr->cardNum != linkTableDbPtr->cardNum || 
            receivedMsgPtr->crcFlag != linkTableDbPtr->crcFlag) 
      {
         LOG_PRINT(LOG_DEBUG,"Modification not allowed for slc, cardNum or crcFlag");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         free(linkTableDbPtr);
         return; 
      }
      #if 0 
      /* FIXED MANTIS 9568 Start*/
     if(CLIB_SUCCESS == getStateForSlotIdIccTable(receivedMsgPtr->cardNum,&cardOprState) )
     {
         if (cardOprState != CARDSTATE_ACTIVE && cardOprState != CARDSTATE_STANDBY)
         {
            LOG_PRINT(LOG_DEBUG, "Card State is invalid for link configuration.");
            cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
            return;
         }
      }
      /* FIXED MANTIS 9568 End*/
      #endif

      if (receivedMsgPtr->adminState == linkTableDbPtr->adminState)
      {
         /* FIXED MANTIS 9568 Start*/
         if(CLIB_SUCCESS == getStateForSlotIdIccTable(receivedMsgPtr->cardNum,&cardOprState) )
         {
            if (cardOprState != CARDSTATE_ACTIVE && cardOprState != CARDSTATE_STANDBY)
            {
               LOG_PRINT(LOG_DEBUG, "Card State is invalid for link configuration.");
               cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
               return;
            }
         }
         /* FIXED MANTIS 9568 End*/
         if(receivedMsgPtr->e1Num == linkTableDbPtr->e1Num &&
               receivedMsgPtr->timeSlot == linkTableDbPtr->timeSlot &&
              receivedMsgPtr->satFlag == linkTableDbPtr->satFlag )
         {
            LOG_PRINT(LOG_DEBUG,"Received parameters are same as present in DB");
            cfgSendAckToCm();
            free(linkTableDbPtr);
            return; 
         }
         else
         {
            modifyLinkTable(receivedMsgPtr, linkTableDbPtr);      
         }
      }
      else
      {
         if(receivedMsgPtr->e1Num != linkTableDbPtr->e1Num ||
               receivedMsgPtr->timeSlot != linkTableDbPtr->timeSlot)
         {
            LOG_PRINT(LOG_DEBUG,"Simultaneous modification and link Lock/Unlock not supported");
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
            free(linkTableDbPtr);
            return; 
         }
         else
         {
            linkLockUnlockHandler(receivedMsgPtr, linkTableDbPtr);
         }
      }      
   }
   else 
   {
      LinksetTableApi  *linkSetTableDbPtr = NULL;
      LinksetTableIndices linkSetTableIndex;
      linkSetTableIndex.linksetID = receivedMsgPtr->linksetID;

      /* Check whether row exists in LinkSet Table for received request */
      if(CLIB_SUCCESS != getLinksetTable(&linkSetTableIndex, &linkSetTableDbPtr))
      {
         LOG_PRINT(LOG_DEBUG, "LinkSet does not exists for the received Link");
         cfgSendNackToCm(CM_ERR_LINKSET_OBJ_NOT_PRESENT);
         return;
      }
      free(linkSetTableDbPtr);

      /* Perform range check on received parameters */
      statusRange = linkRangeChk(receivedMsgPtr);
      if(!statusRange)
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      if (receivedMsgPtr->linkId != receivedMsgPtr->slc)
      {
         LOG_PRINT(LOG_DEBUG, "Received linkId and slc are different");
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         return;
      }

      /* Check that the adminState is LOCKED for received Link request */
      if (receivedMsgPtr->adminState != LOCKED) 
      {
         LOG_PRINT(LOG_DEBUG, "Link addition allowed in Locked State Only");
         cfgSendNackToCm(CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE);
         return;
      }

      if (validateE1AndTimeSlot(receivedMsgPtr) != CFG_SUCCESS)
      {
         return;
      }


     switch (getStateForSlotIdIccTable(receivedMsgPtr->cardNum,&cardOprState)) {
       case CLIB_SUCCESS:
	 break;
       case DBLIBERR_BASEDAO_NO_INDEX_ENTRY:			
         LOG_PRINT(LOG_DEBUG, "Received cardNum does not exists in iccCardInfo Table");
         cfgSendNackToCm(CM_ERR_INVALID_CARD);
         return;
       default :
         LOG_PRINT(LOG_DEBUG, "%s: getStateForSlotIdIccTable failed ",__func__);
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
      }
#if 0
      if (cardOprState != CARDSTATE_ACTIVE)
      {
         LOG_PRINT(LOG_DEBUG, "Received cardNum is not in active state. Sending Switching Request to RM");
//         sendSwitchConForMate(slotIdreceivedMsgPtr->cardNum);
         return;
      }
#endif
      /* Retrieve free MccTrunkNum, MccTrunkTs from MccLinkResource Table */

/* FIXED MANTIS 9568 */
      if (cardOprState != CARDSTATE_ACTIVE && cardOprState != CARDSTATE_STANDBY)
      {
         LOG_PRINT(LOG_DEBUG, "Card State is invalid for link configuration.");
         cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
         return;
      }
/* FIXED MANTIS 9568 */
      if (findFreeMccTrunkNumMccTrunkTs() != CFG_SUCCESS)
      {
         return; 
      }     


      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(LinkTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_LINKTABLE, SCM_ADD, OAM_SCM_LINK_CONFIG);

      /* Frame and Send the message to the OIL */
      if ( ! fillAndSendOamScmLinkConfig() ) 
      {
         sendStackProcRespToCm();
         return;      
      }
   }
}

I_S32 validateE1AndTimeSlot(LinkTableApi *receivedMsgPtr)
{
   I_S32 ret;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0;
   I_U32 tsMap;
   I_U32 trunkUsageType,retStatus;

   /* Check that the received e1Num is valid */
   TrunkTableApi *e1PerTableDbPtr = NULL;
   TrunkTableIndices e1PerTableIndex;
   e1PerTableIndex.e1Num = receivedMsgPtr->e1Num;
   if(CLIB_SUCCESS != getTrunkTable(&e1PerTableIndex, &e1PerTableDbPtr))
   {
      LOG_PRINT(LOG_DEBUG,"Received e1Num does not exist in TrunkTable");
      cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
      return CFG_FAILURE;
   }

   /* Check that the received e1Num is of type AIF */
   if (e1PerTableDbPtr->usageType != SYS_E1_USAGE_AIF)
   {
      LOG_PRINT(LOG_DEBUG,"Received e1Num is not configured for A-Interface");
      cfgSendNackToCm(CM_ERR_INVALID_E1_TYPE);
      free(e1PerTableDbPtr);
      return CFG_FAILURE;
   }
   free(e1PerTableDbPtr);

   /* Check no link is configured on received E1-timeslot*/
   LinkTableApi *linkTableDbPtr = NULL;
   ret = getLinkTableUsingE1Ts(receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot, &linkTableDbPtr); 
   if (linkTableDbPtr != NULL)
   {
      LOG_PRINT(LOG_DEBUG, "Entry exists in Link Table for Received e1Num: %d timeSlot: %d",
            receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
      cfgSendNackToCm(CM_ERR_LINK_EXISTS_ON_RCVD_E1TS);
      free(linkTableDbPtr); 
      return CFG_FAILURE;
   }

   /* Check no Cic is configured on received E1-timeslot*/
   CicTableApi *cicTableDbPtr = NULL;
   ret = getCicTableUsingE1Ts(receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot, &cicTableDbPtr); 
   if (cicTableDbPtr != NULL)
   {
      LOG_PRINT(LOG_DEBUG, "Entry exists in Cic Table for Received e1Num: %d timeSlot: %d",
            receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
      cfgSendNackToCm(CM_ERR_CIC_EXISTS_ON_RCVD_E1TS);
      free(cicTableDbPtr); 
      return CFG_FAILURE;
   }

   /*Check whether received Ext-e1&Ts is not used by Mlppp configuration */

   if(CLIB_SUCCESS == getMccTrunkNumTsUsingExtTrunkNumTs(receivedMsgPtr->e1Num, 
    receivedMsgPtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_DEBUG,"MccLinkResourceTable is already having entry for received E1Ts");
      cfgSendNackToCm(CM_ERR_MLPPP_CONFIGURED_FOR_E1TS);
      free(mccLinkResourceDbPtr);
      return CFG_FAILURE;
   }
/*Changes R2.5 Aricent -- Start*/
   if(isTimeslotAllocatedForFr(receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot))
   {
      LOG_PRINT(LOG_DEBUG,"E1Id[%u] & TS[%u] is allocated for FR Channel, sending Nack",
                receivedMsgPtr->e1Num,receivedMsgPtr->timeSlot);
      cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_FR);
      return CFG_FAILURE;
   }
/*Chnages R2.5 Aricent -- End*/

   /* Changes for TsGroup Start */
   retStatus=getTrunkUsageType(receivedMsgPtr->e1Num,&trunkUsageType);
   tsMap=1<<receivedMsgPtr->timeSlot;
   if(AreTimeSlotsNotUsedForTsGroup(receivedMsgPtr->e1Num,tsMap) != CFG_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG,"E1Id[%u] & TS[%u] is allocated for TsGroup, sending Nack",
                receivedMsgPtr->e1Num,receivedMsgPtr->timeSlot);
      cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_TSGROUP);
      return CFG_FAILURE;

   }
   /* Changes for TsGroup End */

   return CFG_SUCCESS;
}

/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header********************************
Function Name:       isTimeslotAllocatedForFr()
Parameters:          e1Num
                     timeslot
Return type:         I_S8
Purpose:             To check whether the given timeslot on the givem e1 is allocated for any fr link.
Other Note:
 ************************************************************************************/
I_Bool  isTimeslotAllocatedForFr(I_U16 e1Num, I_U8 timeslot)
{
   FrLinkTableApi *frLinkPtr = NULL;
   FrLinkTableApi *tempFrLinkPtr = NULL;
   I_U32 noOfRows = 0;
   I_S32 ret = CM_FAILURE;
   I_U16 rowSize = 0;
   I_Bool frFlag = FALSE;
   I_S8 i = 0;

   ret = getallFrLinkTable(&frLinkPtr, &noOfRows, &rowSize);
   if (CLIB_SUCCESS == ret)
   {
      for (i = 0; i <noOfRows; i++)
      {
         tempFrLinkPtr = (FrLinkTableApi*)((I_U8*)frLinkPtr + (i * rowSize));
         if (tempFrLinkPtr->e1Id == e1Num )
         {
            if ( timeslot >= tempFrLinkPtr->startTs && timeslot < (tempFrLinkPtr->startTs + tempFrLinkPtr->numTs) )
            {
               frFlag = TRUE;
               break;
            }
         }
      }
      free(frLinkPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO," No rows in FrLink table Error Code = [%d] ", ret);
   }
   return frFlag;
}/*end isTimeslotAllocatedForFr*/
/*Changes PCU R2.5 Aricent -- END*/

I_S32 findFreeMccTrunkNumMccTrunkTs()
{ 
   LinkTableApi* receivedMsgPtr = (LinkTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));
   MccLinkResourceTableApi *mccLinkResourcePtr = NULL;
   MccLinkResourceTableIndices mccLinkTableIndex;
   I_U32 outCount = 0;
   I_U16 outSize = 0;
   I_U32 peerTrunk = 0, peerTs = 0;
   I_S32 res;

	 LOG_PRINT(LOG_INFO,"LINK TEST: CN =%d", receivedMsgPtr->cardNum);
   if (getFreeMccTrunkNumTsFromMccLinkTable(receivedMsgPtr->cardNum, SYS_TS_USAGE_MTP2, INVALID_E1, 
      INVALID_TS, SYS_TS_FREE, &mccLinkResourcePtr, &outCount, &outSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_DEBUG, "No Free MccTrunkNum, MccTrunkTs available");
      cfgSendNackToCm(CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS);
      return CFG_FAILURE;
   }
  
   LOG_PRINT(LOG_INFO,"Allocated cardNum:%d mccTrunkNum:%d, mccTrunkTs:%d",
         mccLinkResourcePtr->cardNum,mccLinkResourcePtr->mccTrunkNum,mccLinkResourcePtr->mccTrunkTs);
  
   mccLinkResourcePtr->extTrunkNum = receivedMsgPtr->e1Num;
   mccLinkResourcePtr->extTrunkTs = receivedMsgPtr->timeSlot;

   /*HA Changes Starts*/
   res =  getFreePeerTrunkTsAndMarkItBusy(&peerTrunk,&peerTs);
   if(  CLIB_SUCCESS != res  )
   {
      LOG_PRINT(DEBUG,"No Free Peer Trunk and TimeSlot err:%d", res);
      free(mccLinkResourcePtr);
      cfgSendNackToCm(CM_ERR_NO_FREE_PEER_TRUNK_TRUNKTS);
      return CFG_FAILURE;
   }
   /*HA Changes Ends*/
  
   mccLinkResourcePtr->peerTrunkNum = peerTrunk;
   mccLinkResourcePtr->peerTrunkTs = peerTs;

   res = updateMccLinkResourceTable(mccLinkResourcePtr);

   if ( CLIB_SUCCESS != res)
   {
      LOG_PRINT(LOG_MAJOR, "updateMccLinkResourceTable Failed err:%d", res);
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
      return CFG_FAILURE;
   }
    
   return CFG_SUCCESS;
}

/******************************* Function  Header*****************************
  Function Name : modifyLinkTable()
Parameters    : LinkTableApi *receivedMsgPtr
Return type   : I_Void
Purpose       : To modify e1Num, timeslot in Link Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifyLinkTable(LinkTableApi *receivedMsgPtr, LinkTableApi *linkTableDbPtr)
{
   I_U32 cardOprState = 0;

   if (linkTableDbPtr->adminState != LOCKED)
   {
      LOG_PRINT(LOG_DEBUG,"Modification allowed in Locked state only");
      cfgSendNackToCm(CM_ERR_LINK_NOT_LOCKED);
      free(linkTableDbPtr);
      return; 
   }

   if( (receivedMsgPtr->e1Num != linkTableDbPtr->e1Num) ||
         (receivedMsgPtr->timeSlot != linkTableDbPtr->timeSlot) ) 
   { 
      /* Changes For E1-T1:Starts */
       if(gBscTrunkType == BPM_TRUNK_TYPE_E1)
       {
          if((receivedMsgPtr->timeSlot < 1) || (receivedMsgPtr->timeSlot > 31))
          {
             LOG_PRINT(LOG_DEBUG,"modifyLinkTable : Range Check Failed for Trunk Type %d timeSlot : %d",
             BPM_TRUNK_TYPE_E1,receivedMsgPtr->timeSlot);
             cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
             free(linkTableDbPtr);
             return; 
          }
       }
       if(gBscTrunkType == BPM_TRUNK_TYPE_T1)
       {
          if((receivedMsgPtr->timeSlot < 1) || (receivedMsgPtr->timeSlot > 23))
          {
             LOG_PRINT(LOG_DEBUG,"modifyLinkTable : Range Check Failed for Trunk Type %d timeSlot : %d",
             BPM_TRUNK_TYPE_T1,receivedMsgPtr->timeSlot);
             cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
             free(linkTableDbPtr);
             return; 
          }
       }
       /* Changes For E1-T1:End */
       if (validateE1AndTimeSlot(receivedMsgPtr) != CFG_SUCCESS)
       {
          free(linkTableDbPtr);
          return;
       }
       /* Store the received message in global pointer */
       if (storeReceivedMsgBuffer(receivedMsgPtr, sizeof(LinkTableApi)) != TRUE )
       {
          free(linkTableDbPtr);
          return; 
       }
       
       if (getStateForSlotIdIccTable(linkTableDbPtr->cardNum,&cardOprState) != CLIB_SUCCESS)
       {
          LOG_PRINT(LOG_DEBUG, "Received cardNum does not exists in iccCardInfo Table");
          cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
          free(linkTableDbPtr);
          return;
       }
       
       if(cardOprState == CARDSTATE_ACTIVE)
       {
          if (!(sendSwitchDisconnectReqToGrhm(linkTableDbPtr)))
          {
             free(linkTableDbPtr);
             cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
             return;
          }
          setStackObject(BSC_API_SET_LINKTABLE, SCM_MODIFY, OAMS_CFG_GRHM_SWITCH_CONNECT);
          sendSwitchConnectReqToGrhm(linkTableDbPtr);
       }
       else if(cardOprState == CARDSTATE_STANDBY)
       {
          sendPeerSwitchDisconnectReqToGrhm(linkTableDbPtr);
          setStackObject(BSC_API_SET_LINKTABLE, SCM_MODIFY, OAMS_CFG_GRHM_SWITCH_CONNECT);
          sendPeerSwitchConnectReqToGrhm(linkTableDbPtr);
       }
       free(linkTableDbPtr);
   }

   if( receivedMsgPtr->satFlag != linkTableDbPtr->satFlag)
   {
       if( receivedMsgPtr->satFlag == I_TRUE ||
           receivedMsgPtr->satFlag == I_FALSE )
       {
           linkTableDbPtr->satFlag = receivedMsgPtr->satFlag;
           if(updateLinkTable(receivedMsgPtr) != CLIB_SUCCESS)
           {
               LOG_PRINT(DEBUG,"updateLinkTable failed");
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
               return;
           }
           cfgSendAckToCm();
       }
       else
       {
            LOG_PRINT(DEBUG," SatFlag is not set/Reset: param out of range");
            cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            return;
       }  
   } 

}

/******************************* Function  Header*****************************
  Function Name : setSs7RouteTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : This can be for following:
To add new entry in Ss7Route table
To Modify the parameters in the Ss7Route table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setSs7RouteTableHandler()
{
   Ss7RouteTableApi* receivedMsgPtr = (Ss7RouteTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   Ss7RouteTableApi  *ss7RouteTableDbPtr = NULL;
   Ss7RouteTableIndices ss7RouteTableIndex;
   ss7RouteTableIndex.linksetID = receivedMsgPtr->linksetID;
   ss7RouteTableIndex.routeID = receivedMsgPtr->routeID;
   I_Bool statusRange = FALSE;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;

   LOG_PRINT(LOG_INFO,"Entering function: setSs7RouteTableHandler");

   /* Check whether request received request is for modification or addition */
   if(CLIB_SUCCESS == getSs7RouteTable(&ss7RouteTableIndex, &ss7RouteTableDbPtr))
   {
      LOG_PRINT(LOG_DEBUG, "Modification of Ss7Route is not allowed");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      free(ss7RouteTableDbPtr);
      /*modifySs7RouteTable(receivedMsgPtr, ss7RouteTableDbPtr); */
      return;
   }
   else /* Request received for addition */
   {
      /* Check that linkSet exists for the received link */
      LinksetTableApi *linkSetTablePtr = NULL;
      LinksetTableIndices linkSetTableIndex;
      linkSetTableIndex.linksetID = receivedMsgPtr->linksetID;
      if (getLinksetTable(&linkSetTableIndex, &linkSetTablePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG, "LinkSet: %d does not exists for the received link ", 
               receivedMsgPtr->linksetID);
         cfgSendNackToCm(CM_ERR_LINKSET_OBJ_NOT_PRESENT);
         return; 
      }
      if (linkSetTablePtr->networkIndicator != receivedMsgPtr->networkIndicator)
      {
         LOG_PRINT(LOG_DEBUG, "Received networkIndicator is not same as present in LinkSet Table");
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         free(linkSetTablePtr);
         return; 
      }
      free(linkSetTablePtr);

      /* Check that no row exists in Ss7RouteTable w.r.t Style,DPC & NI */
      if (getRowSs7RouteTableForDpcNi(receivedMsgPtr->style, receivedMsgPtr->dpc, receivedMsgPtr->networkIndicator,  &ss7RouteTableDbPtr, &outCount, &outSize) == CLIB_SUCCESS )
      {
         LOG_PRINT(LOG_DEBUG, " Ss7Route Row already exists for Style, DPC & NI");
         cfgSendNackToCm(CM_ERR_ENTRY_EXISTS_FOR_DPC_NI);
         free(ss7RouteTableDbPtr);
         return;
      }

      /* Perform range check on received parameters */
      statusRange = ss7RouteRangeChk(receivedMsgPtr);
      if(!statusRange)
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }


      if (receivedMsgPtr->style == DPC_NI && receivedMsgPtr->sstTestOn == ENABLED)
      {
         cfgSendNackToCm(CM_ERR_INVALID_TESTON_ENTRY_FOR_STYLE);
         LOG_PRINT(LOG_DEBUG, " sstTestOn cannot be ENABLED for style DPC_NI");
         return; 
      }

      if (receivedMsgPtr->style == DPC_SIO_SSN && receivedMsgPtr->sstTestOn == DISABLE)
      {
         cfgSendNackToCm(CM_ERR_INVALID_TESTON_ENTRY_FOR_STYLE);
         LOG_PRINT(LOG_DEBUG, " sstTestOn cannot be DISABLED for style DPC_SIO_SSN");
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(Ss7RouteTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_SS7ROUTETABLE, SCM_ADD, OAM_SCM_SS7ROUTE_CONFIG);

      /* Frame and Send the message to the OIL */
      OamScmSs7RouteConfig routeConfig;
      routeConfig.destinationPointCode = receivedMsgPtr->dpc ;
      routeConfig.linkSetId = receivedMsgPtr->linksetID;
      routeConfig.interfaceType = receivedMsgPtr->interfaceType;
      routeConfig.style = receivedMsgPtr->style;
      routeConfig.sio = receivedMsgPtr->sio;
      routeConfig.rssn = receivedMsgPtr->rssn;
      routeConfig.lssn = receivedMsgPtr->lssn;
      routeConfig.sstTestOn = receivedMsgPtr->sstTestOn;
      routeConfig.networkIndicator = receivedMsgPtr->networkIndicator;
      LOG_PRINT(LOG_INFO,"Sending OAM_SCM_ROUTE_CONFIG to Oil..");
      if (cfgSendStackMessage((I_Void *)&routeConfig, sizeof(routeConfig) ) != CFG_SUCCESS) {
         cfgSendNackToCm( getFailCauseInStackObj() );
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : modifySs7RouteTable()
Parameters    : Ss7RouteTableApi *receivedMsgPtr, Ss7RouteTableApi *ss7RouteTableDbPtr
Return type   : I_Void
Purpose       : To Modify the parameters in the Ss7Route table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifySs7RouteTable(Ss7RouteTableApi *receivedMsgPtr, Ss7RouteTableApi *ss7RouteTableDbPtr)
{
   I_Bool statusRange = FALSE, storeStatus = FALSE;

   if (!(compareRcvdMsgAndDbEntry((void*)receivedMsgPtr,
               (void*)ss7RouteTableDbPtr,sizeof(Ss7RouteTableApi))))
   {
      LOG_PRINT(LOG_INFO,"Received parameter values are same as in DB");
      cfgSendAckToCm();
      free(ss7RouteTableDbPtr);
      return;
   }

   if (receivedMsgPtr->style != ss7RouteTableDbPtr->style ||
         receivedMsgPtr->dpc != ss7RouteTableDbPtr->dpc ||
         receivedMsgPtr->interfaceType != ss7RouteTableDbPtr->interfaceType ||
         receivedMsgPtr->sio != ss7RouteTableDbPtr->sio ||
         receivedMsgPtr->rssn != ss7RouteTableDbPtr->rssn ||
         receivedMsgPtr->lssn != ss7RouteTableDbPtr->lssn ||
         receivedMsgPtr->networkIndicator != ss7RouteTableDbPtr->networkIndicator ||
         receivedMsgPtr->adminstate != ss7RouteTableDbPtr->adminstate )
   {
      LOG_PRINT(LOG_DEBUG,"Modification allowed only for sstTestOn");
      cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
      free(ss7RouteTableDbPtr);
      return; 
   }

   /* Perform range check on received parameters */
   statusRange = ss7RouteRangeChk(receivedMsgPtr);
   if(!statusRange)
   {
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      free(ss7RouteTableDbPtr);
      return; 
   }

   /* Store the received message in global pointer */
   storeStatus = storeReceivedMsgBuffer(receivedMsgPtr, sizeof(Ss7RouteTableApi));
   if (!storeStatus)
   {
      free(ss7RouteTableDbPtr);
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_SS7ROUTETABLE, SCM_MODIFY, OAM_SCM_SS7ROUTE_TESTON_CONFIG);

   /* Frame and Send the message to the OIL */
   OamScmSs7RouteTestOnConfig routeConfig;
   routeConfig.destinationPointCode = ss7RouteTableDbPtr->dpc ;
   routeConfig.linkSetId = ss7RouteTableDbPtr->linksetID;
   routeConfig.style = ss7RouteTableDbPtr->style;
   routeConfig.sio = ss7RouteTableDbPtr->sio;
   routeConfig.rssn = ss7RouteTableDbPtr->rssn;
   routeConfig.lssn = ss7RouteTableDbPtr->lssn;
   routeConfig.testOn = receivedMsgPtr->sstTestOn;
   routeConfig.networkIndicator = ss7RouteTableDbPtr->networkIndicator;
   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_SS7ROUTE_TESTON_CONFIG to Oil..");
   free(ss7RouteTableDbPtr);
   if (cfgSendStackMessage((I_Void *)&routeConfig, sizeof(routeConfig) ) != CFG_SUCCESS) {
      cfgSendNackToCm( getFailCauseInStackObj() );
      return;
   }
}

/******************************* Function  Header*****************************
  Function Name : linkLockUnlockHandler()
Parameters    : LinkTableApi *receivedMsgPtr, LinkTableApi *linkTableDbPtr
Return type   : I_Void
Purpose       : To handle Lock/Unlock request 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void linkLockUnlockHandler(LinkTableApi *receivedMsgPtr, LinkTableApi *linkTableDbPtr)
{
   TrunkTableApi* e1TableApiPtr = PNULL;
   TrunkTableIndices apiE1Index ={0} ;
	LinkTableApi *linkPtr = NULL;
	LinkTableApi *LinkTableApiDbTmpPtr  = NULL;
	I_U32 outRows =0;
	I_U16 outSize=0;
	I_U32 i=0,cardOprState;
   apiE1Index.e1Num = receivedMsgPtr->e1Num;
 //Mantis 8719 Operation on only one link is allowed
	if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
	{
	   LOG_PRINT(INFO,"linkLockUnlockHandler:getallLinkTable success");
		for (i=0; i < outRows; i++) 
		{
		   LinkTableApiDbTmpPtr = (LinkTableApi *) (((I_U8 *)linkPtr + i*outSize));
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/

/*			if ((receivedMsgPtr->linkId != LinkTableApiDbTmpPtr->linkId) && 
			((gE1TimeslotData[LinkTableApiDbTmpPtr->e1Num][LinkTableApiDbTmpPtr->timeSlot].e1TimeslotState== lockInProgress)         || (gE1TimeslotData[LinkTableApiDbTmpPtr->e1Num][LinkTableApiDbTmpPtr->timeSlot].e1TimeslotState == unlockInProgress)))*/

/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/

/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
			if((receivedMsgPtr->linkId != LinkTableApiDbTmpPtr->linkId))
			{
				  LOG_PRINT(LOG_INFO,"linkLockUnlockHandler:Simultaneous procedure on more than one link are not allowed");
				  free(linkPtr);
				  cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
				  return;
			 }
	   }
		free(linkPtr);
    }
	 else
	 {
	   LOG_PRINT(INFO,"linkLockUnlockHandler:getallLinkTable fail"); 
	   cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      free(linkTableDbPtr);
      return;
	 }
						 
	 //End

   /* Check is E1 is External. it should be Enabled */
   if( getTrunkTable(&apiE1Index, &e1TableApiPtr) == CLIB_SUCCESS)
   {
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
    //if( e1TableApiPtr->e1Category == EXTERNAL_E1 && 
    //      gE1Data[e1TableApiPtr->e1Num].trunkState != Enabled )
    //{
    //   LOG_PRINT(LOG_INFO,"linkLockUnlockHandler: E1 in Disabled State");
    //   cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLED);
    //   free(e1TableApiPtr);
    //   free(linkTableDbPtr);
    //   return;
    //}
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
      free(e1TableApiPtr);
   }
   else
   {
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      free(linkTableDbPtr);
      return;
   }

   /* Reject the request if Bss or E1 is Lock In Progress state */

/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
   /*if (gBssState == lockInProgress || gE1Data[receivedMsgPtr->e1Num].e1State == lockInProgress ||
      gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState == lockInProgress)*/
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
	 if (gBssState == lockInProgress)
   {
      //LOG_PRINT(LOG_INFO,"Either BSS or E1 or Ts is lockInProgress,Operation not Possible"); commented for cloud
      LOG_PRINT(LOG_INFO,"BSS is lockInProgress,Operation not Possible");
      cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
      free(linkTableDbPtr);
      return;
   }

   /* Reject the request if Bss or E1 is Unlock In Progress state */

/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
  /* if (gBssState == unlockInProgress || gE1Data[receivedMsgPtr->e1Num].e1State == unlockInProgress ||
      gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState == unlockInProgress)*/
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
		if (gBssState == unlockInProgress)
   {
      //LOG_PRINT(LOG_INFO,"Either BSS or E1 or Ts is unlockInProgress,Operation not Possible"); commented for cloud
      LOG_PRINT(LOG_INFO,"BSS is unlockInProgress,Operation not Possible");
      cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
      free(linkTableDbPtr);
      return;
   }

   /* Check If request received for Link Unlock */
   if (receivedMsgPtr->adminState == UNLOCKED && 
         linkTableDbPtr->adminState == LOCKED)
   {
      LOG_PRINT(LOG_INFO,"Received Link Unlock request..");
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
      /* If E1 or Bss is Locked, Don't send request for Link Unlock */
      //if (gE1Data[receivedMsgPtr->e1Num].e1State == locked || gBssState == locked)
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
/*Changes done for not sending UNLOCK req if the Oper State is ENABLED 13-06-2015 GAURAV SINHA*/
			LinkStatusTableApi *linkStatusTableApi = NULL;
			LinkStatusTableIndices inData;
			inData.linksetID = linkTableDbPtr->linksetID;
			inData.linkId    = linkTableDbPtr->linkId;
			if(CLIB_SUCCESS == getLinkStatusTable(&inData,&linkStatusTableApi))
			{
				if(linkStatusTableApi->oprState == ENABLED)
				{
          LOG_PRINT(LOG_DEBUG, "Link Operational Status is Still ENABLED: LINK_UNLOCK_REQ not permisibble");
          cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
					if(linkStatusTableApi)
					{
					 	free(linkStatusTableApi);
					}
					return;
				}
			}
/*Changes done for not sending UNLOCK req if the Oper State is ENABLED 13-06-2015 GAURAV SINHA*/
      if (gBssState == locked)
      {
         //LOG_PRINT(LOG_INFO,"Either E1 or Bss is Locked,Only adminState is updated"); commented for cloud
         LOG_PRINT(LOG_INFO,"Bss is Locked,Only adminState is updated");
         cfgSendAckToCm();
         sendLinkUnlockAlarm(receivedMsgPtr);
         free(linkTableDbPtr);
         return; 
      }

      /* FIXED MANTIS 9568 Start*/
			/*Changed for CLOUD-BSC Gaurav Sinha 05-May-2016 Mantis #31127*/		
     // if(CLIB_SUCCESS == getStateForSlotIdIccTable(receivedMsgPtr->cardNum,&cardOprState) )
     // {
     //     if (cardOprState != CARDSTATE_ACTIVE && cardOprState != CARDSTATE_STANDBY)
     //     {
     //        LOG_PRINT(LOG_DEBUG, "Card State is invalid for link configuration.");
     //        cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
     //        return;
     //     }
     //  }
			/*Changed for CLOUD-BSC Gaurav Sinha 05-May-2016 Mantis #31127*/		
			
       /* FIXED MANTIS 9568 End*/

      /* If received e1 timeslot is already in unlockinprogress */
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
    //if (gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState == unlockInProgress)
    //{
    //   LOG_PRINT(LOG_INFO,"Link unLock is already in progress");
    //   cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
    //   free(linkTableDbPtr);
    //   return;
    //}
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_LINKTABLE, SCM_UNLOCK, OAM_SCM_LINK_ADMIN_CONFIG);
      gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = unlockInProgress;
      LOG_PRINT(LOG_INFO,"Moving to Unlock-In-Progress State");
   }
   /* Check If request received for Link Lock */
   else if (receivedMsgPtr->adminState == LOCKED && 
         linkTableDbPtr->adminState == UNLOCKED)
   {
      LOG_PRINT(LOG_INFO,"Received Link Lock request..");
      /* If E1 or Bss is Locked, Don't send request for Link Lock */
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
      //if (gE1Data[receivedMsgPtr->e1Num].e1State == locked || gBssState == locked)
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
      if (gBssState == locked)
      {
         //LOG_PRINT(LOG_INFO,"Either E1 or Bss is Locked,Only adminState is updated"); commented for cloud
         LOG_PRINT(LOG_INFO,"Bss is Locked,Only adminState is updated");
         cfgSendAckToCm();
         sendLinkLockAlarm(receivedMsgPtr);
         free(linkTableDbPtr);
         return;
      }

      #if 0 
      /* FIXED MANTIS 9568 Start*/
      if(CLIB_SUCCESS == getStateForSlotIdIccTable(receivedMsgPtr->cardNum,&cardOprState) )
      {
         if (cardOprState != CARDSTATE_ACTIVE && cardOprState != CARDSTATE_STANDBY)
         {
            LOG_PRINT(LOG_DEBUG, "Card State is not active or standby in linklock request allowing lock");
            cfgSendAckToCm();
            sendLinkLockAlarm(receivedMsgPtr);
            free(linkTableDbPtr);
            return;
         }
      }
      /* FIXED MANTIS 9568 End*/
      #endif

      /* If received e1 timeslot is already in lockinprogress */
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
    //if (gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState == lockInProgress)
    //{
    //   LOG_PRINT(LOG_INFO,"Link Lock is already in progress");
    //   cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
    //   free(linkTableDbPtr);
    //   return;
    //}
/*Above condition check commented for cloud related to e1 & trunk to send link lock/unlock to scm*/
/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_LINKTABLE, SCM_LOCK, OAM_SCM_LINK_ADMIN_CONFIG);
      gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = lockInProgress;
      LOG_PRINT(LOG_INFO,"Moving to Lock-In-Progress State");
   }
   free(linkTableDbPtr);
   /* Frame and Send the message to the OIL */
   OamScmLinkAdminState linkConfig;
   linkConfig.linkId = receivedMsgPtr->linkId; 
   linkConfig.linkSetId = receivedMsgPtr->linksetID; 
   linkConfig.adminState = receivedMsgPtr->adminState; 
   /*Changes for R2.3.4 Starts*/
   if(receivedMsgPtr->adminState == UNLOCKED) 
   {
      if(fillMtp2TimerInfo(&(linkConfig.mtp2TimerConfig),receivedMsgPtr->satFlag) != I_TRUE)
      {
         LOG_PRINT(DEBUG,"fillMtp2TimerInfo failed");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = locked;
         return;
      }
   }
   /*Changes for R2.3.4 Ends*/
   
   gMsgSentForE1TSNum = receivedMsgPtr->timeSlot;
   gMsgSentForE1TSNum = ((receivedMsgPtr->e1Num << 16)| gMsgSentForE1TSNum);

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LINK_ADMIN_CONFIG to Oil..");
   if (cfgSendStackMessage((I_Void *)&linkConfig, sizeof(linkConfig)) != CFG_SUCCESS)
   {
      cfgSendNackToCm(CM_ERR_SEND_MESSAGE_FAILS);
      return;
   }
   cfgSendAckToCm();
}

/******************************* Function  Header*****************************
  Function Name : setCicTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : This can be for following:
To add new entry in Cic table
To Modify the parameters in the Cic table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setCicTableHandler()
{
   CicTableApi* receivedMsgPtr = (CicTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   TrunkTableApi* e1TableApiPtr = PNULL;
   TrunkTableIndices apiE1Index ={0} ;
   CicTableApi  *cicTableDbPtr = NULL;
   CicTableIndices cicTableIndex;
   cicTableIndex.interfaceId = receivedMsgPtr->interfaceId;
   cicTableIndex.tgpId = receivedMsgPtr->tgpId;
   cicTableIndex.e1Num = receivedMsgPtr->e1Num;
   cicTableIndex.timeSlot = receivedMsgPtr->timeSlot;

   LOG_PRINT(LOG_INFO,"Entering function: setCicTableHandler");
   LOG_PRINT(LOG_INFO,"Reseived interfaceId:%u tgpId:%u e1Num:%u",
         receivedMsgPtr->interfaceId,receivedMsgPtr->tgpId,receivedMsgPtr->e1Num);
   LOG_PRINT(LOG_INFO,":timeSlot%u cicId:%u usage:%u",
         receivedMsgPtr->timeSlot,receivedMsgPtr->cicId,receivedMsgPtr->usage);
   LOG_PRINT(LOG_INFO,"adminState:%u reset:%u ",
         receivedMsgPtr->adminState,receivedMsgPtr->reset);

   /* Check whether row exists in DB for the received request */
   if(CLIB_SUCCESS != getCicTable(&cicTableIndex, &cicTableDbPtr))
   {
      LOG_PRINT(LOG_DEBUG, "No row exist in DB for the received request");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   else 
   {
      if (!(compareRcvdMsgAndDbEntry((void*)receivedMsgPtr,
                  (void*)cicTableDbPtr,sizeof(CicTableApi))))
      {
         LOG_PRINT(LOG_INFO,"Received parameter values are same as in DB");
         cfgSendAckToCm();
         free(cicTableDbPtr);
         return;
      }

      if((receivedMsgPtr->adminState != LOCK) &&
            (receivedMsgPtr->adminState != UNLOCK))
      {
         LOG_PRINT(LOG_DEBUG,"Received Wrong adminState value from Operator");         
         cfgSendNackToCm(CM_ERR_INVALID_REQUEST);
         free(cicTableDbPtr);
         return;
      }

      if (receivedMsgPtr->adminState == cicTableDbPtr->adminState)
      {
         LOG_PRINT(LOG_DEBUG,"Modification Not allowed on Cic Table");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         free(cicTableDbPtr);
         return;
      }

      apiE1Index.e1Num = receivedMsgPtr->e1Num;
      if( getTrunkTable(&apiE1Index, &e1TableApiPtr) == CLIB_SUCCESS)
      {
         if( e1TableApiPtr->e1Category == EXTERNAL_E1 && 
               gE1Data[e1TableApiPtr->e1Num].trunkState != Enabled)
         {
            LOG_PRINT(LOG_INFO," setTimeslotTableHandler: E1 in Disabled State");
            cfgSendNackToCm(CM_ERR_TRUNKPORT_DISABLED);
            free(e1TableApiPtr);
            free(cicTableDbPtr);
            return;
         }
         free(e1TableApiPtr);
      }
      else
      {
         cfgSendNackToCm(CM_ERR_E1_NOT_PRESENT_IN_DB);
         free(cicTableDbPtr);
         return;
      }

      if (gBssState == lockInProgress )
      {
         LOG_PRINT(LOG_INFO,"BSS is in lockInProgress state, Operation not Possible");
         cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
         free(cicTableDbPtr);
         return;
      }

      if (gE1Data[receivedMsgPtr->e1Num].e1State == lockInProgress)
      {
         LOG_PRINT(LOG_INFO,"Trunk is in lockInProgress state, Operation not Possible");
         cfgSendNackToCm(CM_ERR_TRUNK_LOCK_IN_PROGRESS);
         free(cicTableDbPtr);
         return;
      }

      if (gBssState == unlockInProgress)
      {
         LOG_PRINT(LOG_INFO,"BSS is in unlockInProgress state, Operation not Possible");
         cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
         free(cicTableDbPtr);
         return;
      }

      if (gE1Data[receivedMsgPtr->e1Num].e1State == unlockInProgress)
      {
         LOG_PRINT(LOG_INFO,"Trunk is in unlockInProgress state, Operation not Possible");
         cfgSendNackToCm(CM_ERR_TRUNK_UNLOCK_IN_PROGRESS);
         free(cicTableDbPtr);
         return;
      }

      switch (gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState)
      {
         case locked:
            LOG_PRINT(LOG_INFO,"E1[%d].Ts[%d] internal State is locked",
               receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
            if (receivedMsgPtr->adminState == UNLOCKED && 
                  cicTableDbPtr->adminState == LOCKED)
            {
               LOG_PRINT(LOG_INFO,"Received Cic Unlock Request..");
               cicUnlockReqHandler(receivedMsgPtr);
            }
            break;
         case unlockInProgress:
            LOG_PRINT(LOG_INFO,"E1[%d].Ts[%d] internal State is unlockInProgress",
               receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
            cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
            break;
         case unlocked:
            LOG_PRINT(LOG_INFO,"E1[%d].Ts[%d] internal State is unlocked",
               receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
            if (receivedMsgPtr->adminState == LOCKED && 
                  cicTableDbPtr->adminState == UNLOCKED)
            {
               LOG_PRINT(LOG_INFO,"Received Cic Lock Request..");
               cicLockReqHandler(receivedMsgPtr);   
            }
            break;
         case lockInProgress:
            LOG_PRINT(LOG_INFO,"E1[%d].Ts[%d] internal State is lockInProgress",
               receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
            break;
         default:
            LOG_PRINT(LOG_DEBUG,"Invalid State");
            break;
      }
      free(cicTableDbPtr);
   }
}

I_Void cicLockReqHandler(CicTableApi *receivedMsgPtr)
{
   if (gE1Data[receivedMsgPtr->e1Num].e1State == locked || gBssState == locked)
   {
      LOG_PRINT(LOG_INFO,"Either E1 or Bss is Locked,Only AdminState is Updated");
      cfgSendAckToCm();
      sendCicLockAlarm(receivedMsgPtr);
   }
   else if (gE1Data[receivedMsgPtr->e1Num].e1State == unlocked && gBssState == unlocked)
   {
      cfgSendAckToCm();
      sendCicLockUnlockRequestToGrhm(LOCKED);
   }
}

I_Void cicUnlockReqHandler(CicTableApi *receivedMsgPtr)
{
   I_S32 oprStateAInterface;
   if (getAInterfaceOprState(&oprStateAInterface) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getAInterfaceOprState Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
   }
   if (gE1Data[receivedMsgPtr->e1Num].e1State == locked || 
         gBssState == locked || oprStateAInterface == DISABLED)
   {
      LOG_PRINT(LOG_INFO,"Either E1 or Bss is Locked or AInterface Disabled,,Only AdminState is Updated");
      cfgSendAckToCm();
      sendCicUnlockAlarm(receivedMsgPtr);
   }
   else if (gE1Data[receivedMsgPtr->e1Num].e1State == unlocked && 
         gBssState == unlocked && oprStateAInterface == ENABLED)
   {
      cfgSendAckToCm();
      sendCicLockUnlockRequestToGrhm(UNLOCKED);
   }
}

I_Void cicLockRespHandler()
{
   I_U16 e1Num=0;
   I_U16 tsNum=0;
   CicTableApi *cicTableDbPtr = NULL;
   unMaskBits(((CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);

   if (gE1TimeslotData[e1Num][tsNum].e1TimeslotState != lockInProgress)
   {
      LOG_PRINT(LOG_MAJOR,"Cfg internal state is not lockInProgress for E1:%d,Ts:%d", e1Num,tsNum);
      return; 
   }

   if (getCicTableUsingE1Ts(e1Num, tsNum, &cicTableDbPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getCicTableUsingE1Ts Failed..");
      return; 
   }
   sendCicLockAlarm(cicTableDbPtr);
   free(cicTableDbPtr); 
}

I_Void cicUnlockRespHandler()
{
   I_U16 e1Num=0;
   I_U16 tsNum=0;
   CicTableApi *cicTableDbPtr = NULL;
   unMaskBits(((CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);

   if (gE1TimeslotData[e1Num][tsNum].e1TimeslotState != unlockInProgress)
   {
      LOG_PRINT(LOG_MAJOR,"Cfg internal state is not unlockInProgress for E1:%d,Ts:%d", e1Num,tsNum);
      return; 
   }

   if (getCicTableUsingE1Ts(e1Num, tsNum, &cicTableDbPtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getCicTableUsingE1Ts Failed..");
      return; 
   }
   sendCicUnlockAlarm(cicTableDbPtr);
   free(cicTableDbPtr); 
}

/********************************* Function  Header********************************
  Function Name:       sendCicLockUnlockRequestToGrhm()
Parameters:          I_U16
Return type:         void
Purpose:             To send a lock/unlock request to GRHM for CIC.
Other Note:
 ************************************************************************************/
I_Void sendCicLockUnlockRequestToGrhm(I_U16 reqType)
{
   CicTableApi *receivedMsgPtr = (CicTableApi *)(((I_U8 *)gCfgMsgBuf)+ sizeof(sCmMsg));
   switch (reqType)
   {
      case LOCKED:
         {
            OamsCfgGrhmLockReq reqMsg;
            reqMsg.objectId = 0;
            reqMsg.objectId = maskBits(reqMsg.objectId,receivedMsgPtr->timeSlot,lBYtes);/*Mask TimeSlot Number with ObjectId*/
            reqMsg.objectId= maskBits(reqMsg.objectId,receivedMsgPtr->e1Num,hBytes);/*Mask E1 Number with Object Id*/
            reqMsg.objType = OAMS_OBJTYPE_CIC; 
            reqMsg.reason = OAMS_RSN_OPERATORINITIATED;
            LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_GRHM_LOCK_REQ..");
            if (cfgSendMessage(&reqMsg, sizeof(OamsCfgGrhmLockReq),
                     ENT_CSAPP_GRHM, OAMS_CFG_GRHM_LOCK_REQ, 0) == CFG_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"Updating internal state as lockInProgress for E1:%d,Ts:%d", receivedMsgPtr->e1Num,receivedMsgPtr->timeSlot);
               gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = lockInProgress;
            }
         }
         break;

      case UNLOCKED:
         {
            OamsCfgGrhmUnlockReq reqMsg;
            reqMsg.objectId = 0;
            reqMsg.objectId = maskBits(reqMsg.objectId,receivedMsgPtr->timeSlot,lBYtes);/*Mask TimeSlot Number with ObjectId*/
            reqMsg.objectId = maskBits(reqMsg.objectId,receivedMsgPtr->e1Num,hBytes);/*Mask E1 Number with Object Id*/
            reqMsg.objType = OAMS_OBJTYPE_CIC; 
            reqMsg.reason = OAMS_RSN_OPERATORINITIATED;
            LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_GRHM_UNLOCK_REQ..");
            if (cfgSendMessage(&reqMsg, sizeof(OamsCfgGrhmUnlockReq), 
                     ENT_CSAPP_GRHM, OAMS_CFG_GRHM_UNLOCK_REQ, 0) == CFG_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"Updating internal state as unlockInProgress for E1:%d,Ts:%d", receivedMsgPtr->e1Num,receivedMsgPtr->timeSlot);
               gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = unlockInProgress;
            }          
         }
         break;
      default:
         break;
   }   
}

/******************************* Function  Header*****************************
  Function Name : sendCicLockAlarm()
Parameters    : CicTableApi *receivedMsgPtr 
Return type   : I_Void
Purpose       : To send Cic Lock Alarm towards AFH 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendCicLockAlarm(CicTableApi *receivedMsgPtr)
{
   CicTableIndices cicIndex;
   cicIndex.interfaceId = receivedMsgPtr->interfaceId;
   cicIndex.tgpId = receivedMsgPtr->tgpId;
   cicIndex.e1Num = receivedMsgPtr->e1Num;
   cicIndex.timeSlot = receivedMsgPtr->timeSlot;
   if (CLIB_SUCCESS != updateAdminStateInCicTable(cicIndex,LOCKED))
   {
      LOG_PRINT(LOG_MAJOR, "DB updation failed for CIC Table ");
      return;
   }
   gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = locked;
   LOG_PRINT(LOG_INFO,"Sending ALARM: ALARM_CIC_LOCK_COMPLETED");
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   sysAlarmBuff.sysAlarm.sysalarmId = ALARM_CIC_LOCK_COMPLETED;
   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CIC;
   sysAlarmBuff.sysAlarm.key1 = receivedMsgPtr->interfaceId; 
   sysAlarmBuff.sysAlarm.key2 = receivedMsgPtr->tgpId;
   sysAlarmBuff.sysAlarm.key3 = receivedMsgPtr->e1Num;
   sysAlarmBuff.sysAlarm.key4 = receivedMsgPtr->timeSlot;
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
         "Cic Lock for Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d] is successfully completed",receivedMsgPtr->cicId,
         receivedMsgPtr->interfaceId, receivedMsgPtr->tgpId, receivedMsgPtr->e1Num, receivedMsgPtr->timeSlot);
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 
}

/******************************* Function  Header*****************************
  Function Name : sendCicUnlockAlarm()
Parameters    : CicTableApi *receivedMsgPtr 
Return type   : I_Void
Purpose       : To send Cic Lock Alarm towards AFH 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendCicUnlockAlarm(CicTableApi *receivedMsgPtr)
{
   CicTableIndices cicIndex;
   cicIndex.interfaceId = receivedMsgPtr->interfaceId;
   cicIndex.tgpId = receivedMsgPtr->tgpId;
   cicIndex.e1Num = receivedMsgPtr->e1Num;
   cicIndex.timeSlot = receivedMsgPtr->timeSlot;
   if (CLIB_SUCCESS !=  updateAdminStateInCicTable(cicIndex,UNLOCKED))
   {
      LOG_PRINT(LOG_MAJOR, "DB updation failed for CIC Table ");
      return;
   }
   gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = unlocked;
   LOG_PRINT(LOG_INFO,"Sending ALARM: ALARM_CIC_UNLOCK_COMPLETED");
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   sysAlarmBuff.sysAlarm.sysalarmId = ALARM_CIC_UNLOCK_COMPLETED;
   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CIC;
   sysAlarmBuff.sysAlarm.key1 = receivedMsgPtr->interfaceId; 
   sysAlarmBuff.sysAlarm.key2 = receivedMsgPtr->tgpId;
   sysAlarmBuff.sysAlarm.key3 = receivedMsgPtr->e1Num;
   sysAlarmBuff.sysAlarm.key4 = receivedMsgPtr->timeSlot;
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
         "Cic Unlock for Cic[%d],Interface[%d],TrunkGroup[%d],Trunk[%d],TimeSlot[%d] is successfully completed",
         receivedMsgPtr->cicId, receivedMsgPtr->interfaceId, receivedMsgPtr->tgpId, receivedMsgPtr->e1Num, 
         receivedMsgPtr->timeSlot);
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 
}

/******************************* Function  Header*****************************
  Function Name : sendLinkLockAlarm()
Parameters    : LinkTableApi *receivedMsgPtr 
Return type   : I_Void
Purpose       : To send Link Lock Alarm towards AFH 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendLinkLockAlarm(LinkTableApi *receivedMsgPtr)
{
   LinkTableIndices linkIndex;
   linkIndex.linksetID = receivedMsgPtr->linksetID;
   linkIndex.linkId = receivedMsgPtr->linkId;
   if (CLIB_SUCCESS !=   updateAdminStateInLinkTable(linkIndex, LOCKED))
   {
      LOG_PRINT(LOG_MAJOR, "DB updation failed for Link Table ");
      return;
   }
   gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = locked;
   LOG_PRINT(LOG_INFO,"Sending ALARM: ALARM_LINK_LOCK_COMPLETED");
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   sysAlarmBuff.sysAlarm.sysalarmId = ALARM_LINK_LOCK_COMPLETED;
   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_LINK;
   sysAlarmBuff.sysAlarm.key1 = receivedMsgPtr->linksetID; 
   sysAlarmBuff.sysAlarm.key2 = receivedMsgPtr->linkId;
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
         "Link Lock for LinkId: %u is successfully completed",receivedMsgPtr->linkId);
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 
}

/******************************* Function  Header*****************************
  Function Name : sendLinkUnlockAlarm()
Parameters    : LinkTableApi *receivedMsgPtr 
Return type   : I_Void
Purpose       : To send Link Unlock Alarm towards AFH 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendLinkUnlockAlarm(LinkTableApi *receivedMsgPtr)
{
   LinkTableIndices linkIndex;
   linkIndex.linksetID = receivedMsgPtr->linksetID;
   linkIndex.linkId = receivedMsgPtr->linkId;
   if (CLIB_SUCCESS !=   updateAdminStateInLinkTable(linkIndex, UNLOCKED))
   {
      LOG_PRINT(LOG_MAJOR, "DB updation failed for Link Table ");
      return;
   }
   gE1TimeslotData[receivedMsgPtr->e1Num][receivedMsgPtr->timeSlot].e1TimeslotState = unlocked;
   LOG_PRINT(LOG_INFO,"Sending ALARM: ALARM_LINK_UNLOCK_COMPLETED");
   OamsCfgAfhSysAlarm sysAlarmBuff = {0};
   sysAlarmBuff.sysAlarm.sysalarmId = ALARM_LINK_UNLOCK_COMPLETED;
   sysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_LINK;
   sysAlarmBuff.sysAlarm.key1 = receivedMsgPtr->linksetID; 
   sysAlarmBuff.sysAlarm.key2 = receivedMsgPtr->linkId;
   sysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
   sysAlarmBuff.sysAlarm.infoStrLen = sprintf(sysAlarmBuff.sysAlarm.infoString,
         "Link Unlock for LinkId: %u is successfully completed",receivedMsgPtr->linkId);
   cfgSendMessage((I_Void *)&sysAlarmBuff,sizeof(OamsCfgAfhSysAlarm),
         ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 
}

/******************************* Function  Header*****************************
  Function Name : checkUniqueCicFromCicTable()
Parameters    : I_U32 startCic, I_U32 endCic
Return type   : I_S32
Purpose       : To check the uniqueness of received of received cic 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 checkUniqueCicFromCicTable(I_U32 startCic, I_U32 endCic)
{
   I_U32 cic;
   CicTableApi *cicTableDbPtr;
   for (cic = startCic; cic <= endCic; cic++)
   {
      if (getCicTableUsingCicId(cic, &cicTableDbPtr) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG, "Received CicId: %u already exists in Cic Table", cic);
         free(cicTableDbPtr);
         return CFG_FAILURE;
      }
   } 
   return CFG_SUCCESS;
}

/******************************* Function  Header*****************************
  Function Name : getCicForTimeSlots()
Parameters    : I_U32 startCic, I_U32 endCic, I_U32 tsCicMap
Return type   : I_Void
Purpose       : To decode tsCicMap to retreive Cic corresponding to timeslots 
in array timeSlotCicMap.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 getCicForTimeSlots(I_U32 startCic, I_U32 endCic, I_U32 tsCicMap, I_U32 *timeSlotCicMap)
{
   I_U32 tempCic, currentTsCicMap;
   I_S32 count;
   I_S32 tsRange;
   tempCic = startCic;
   currentTsCicMap = tsCicMap;
   LOG_PRINT(LOG_INFO, "Decoding tsCicMap for mapping of Cics with E1-TimeSlot");
  /* Changes For E1-T1:Start */ 
   if(gBscTrunkType == BPM_TRUNK_TYPE_E1)
   {  
     tsRange=32;
   }  
   
   if(gBscTrunkType == BPM_TRUNK_TYPE_T1)
   {  
     tsRange=24;
   }  
   
  /* Changes For E1-T1:End */ 
   for (count = 0; count < tsRange; count++)
   {
      if ((currentTsCicMap & 0x1) == 1)
      {
         timeSlotCicMap[count] = tempCic;
         tempCic++;
      }

      else
      {
         timeSlotCicMap[count] = INVALID_CIC;
      }
      currentTsCicMap = currentTsCicMap >> 1;
   }
   if (--tempCic != endCic)
   {
      LOG_PRINT(LOG_DEBUG, "Mismatch between number of timeSlots and number of Cics ");
      return CFG_FAILURE;
   }
   return CFG_SUCCESS;
}

/******************************* Function  Header*****************************
  Function Name : isTimeSlotNotUsedForCicOrLink()
Parameters    : TrunkTableApi *receivedMsgPtr 
Return type   : I_S32
Purpose       : To check the uniqueness of received timeSlots in tsCicMap.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 isTimeSlotNotUsedForCicOrLink(AiftrunkTableApi *receivedMsgPtr)
{
   I_U32 count;
   I_S32 ret;
   LinkTableApi *linkTableDbPtr = NULL;
   CicTableApi *cicTableDbPtr = NULL;
   I_U32 timeSlotCicMap[CFG_MAX_NUM_E1_TS]={0};
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0;
   if (getCicForTimeSlots(receivedMsgPtr->startCic, receivedMsgPtr->endCic, receivedMsgPtr->tsCicMap, timeSlotCicMap) != CFG_SUCCESS)
   { 
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return CFG_FAILURE;
   }

   for (count = 0; count < CFG_MAX_NUM_E1_TS; count++)
   {
      if (timeSlotCicMap[count] != INVALID_CIC)
      {
         LOG_PRINT(LOG_INFO, "Verifying uniqueness of e1Num: %d timeSlot: %d mapped with cicId: %u",receivedMsgPtr->e1Num, count,timeSlotCicMap[count]);
         ret = getLinkTableUsingE1Ts(receivedMsgPtr->e1Num, count, &linkTableDbPtr); 
         if (linkTableDbPtr != NULL)
         {
            LOG_PRINT(LOG_DEBUG, "Entry exists in Link Table for Received e1Num: %d timeSlot: %d",
                  receivedMsgPtr->e1Num, count);
            /*cfgSendNackToCm(CM_ERR_LINK_EXISTS_ON_RCVD_E1TS); Feature for Mantis-7848 */
            free(linkTableDbPtr); 
            //return CFG_FAILURE;
         }
         ret = getCicTableUsingE1Ts(receivedMsgPtr->e1Num, count, &cicTableDbPtr); 
         if (cicTableDbPtr != NULL)
         {
            LOG_PRINT(LOG_DEBUG, "Entry exists in Cic Table for Received e1Num: %d timeSlot: %d",
                  receivedMsgPtr->e1Num, count);
            cfgSendNackToCm(CM_ERR_CIC_EXISTS_ON_RCVD_E1TS);
            free(cicTableDbPtr); 
            return CFG_FAILURE;
          }
         /*Changes R2.5 Aricent -- Start*/
         if(isTimeslotAllocatedForFr(receivedMsgPtr->e1Num, count))
         {
            LOG_PRINT(LOG_DEBUG,"E1Id[%u] & TS[%u] is allocated for FR Channel, sending Nack",
                      receivedMsgPtr->e1Num, count);
            cfgSendNackToCm(CM_ERR_TS_CONFIGURED_FOR_FR);
            return CFG_FAILURE;
         }
         /*Chnages R2.5 Aricent -- End*/
       /*BSC R2.0 MergedChanges with BSNL-GB-IOT Branch Starts*/
      /*Check whether received Ext-e1&Ts is not used by Mlppp configuration */
         #if 0
         if(CLIB_SUCCESS == getMccTrunkNumTsUsingExtTrunkNumTs(receivedMsgPtr->e1Num, 
            count, &mccLinkResourceDbPtr, &outCount, &outSize))
         {
            LOG_PRINT(LOG_DEBUG,"MccLinkResourceTable is already having entry for received E1Ts");
            cfgSendNackToCm(CM_ERR_MLPPP_CONFIGURED_FOR_E1TS);
            free(mccLinkResourceDbPtr);
            return CFG_FAILURE;
         }
         #endif
       /*BSC R2.0 MergedChanges with BSNL-GB-IOT Branch Ends*/
      }
   }
   return CFG_SUCCESS;
}

/******************************* Function  Header*****************************
  Function Name : ss7StackRangeChk()
Parameters    : Ss7StackConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SS7STACKTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool ss7StackRangeChk(Ss7StackConfigTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->sksCommonfamily < 1) || (receivedMsgPtr->sksCommonfamily > 4))
   {
      LOG_PRINT(LOG_DEBUG,"ss7StackRangeChk : Range Check Failed - sksCommonfamily : %d",
            receivedMsgPtr->sksCommonfamily);
      return FALSE;
   }
   if((receivedMsgPtr->sksCommonfamily ==1) && (gBscTrunkType != BPM_TRUNK_TYPE_E1))
   {
      LOG_PRINT(LOG_DEBUG,"ss7StackRangeChk : Range Check Failed - sksCommonfamily : %d not compatible with preconfigured TrunkType %d",receivedMsgPtr->sksCommonfamily,BPM_TRUNK_TYPE_E1);
      return FALSE;
   }
   if((receivedMsgPtr->sksCommonfamily ==2) && (gBscTrunkType != BPM_TRUNK_TYPE_T1))
   {
      LOG_PRINT(LOG_DEBUG,"ss7StackRangeChk : Range Check Failed - sksCommonfamily : %d not compatible with preconfigured TrunkType %d",receivedMsgPtr->sksCommonfamily,BPM_TRUNK_TYPE_T1);
      return FALSE;
   }
   if((receivedMsgPtr->sksCommonopc < 1) || (receivedMsgPtr->sksCommonopc > 16383))
   {
      LOG_PRINT(LOG_DEBUG,"ss7StackRangeChk : Range Check Failed - sksCommonopc : %d",
            receivedMsgPtr->sksCommonopc);
      return FALSE;
   }
   if((receivedMsgPtr->alarmLevel < 2) || (receivedMsgPtr->alarmLevel > 5))
   {
      LOG_PRINT(LOG_DEBUG,"ss7StackRangeChk : Range Check Failed - alarmLevel : %d",
            receivedMsgPtr->alarmLevel);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : aifInterfaceRangeChk()
Parameters    : Ss7StackConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_AIFINTERFACETABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool aifInterfaceRangeChk(AifInterfaceTableApi *receivedMsgPtr)
{
   if(receivedMsgPtr->interfaceType != IF_TYPE_AIF)
   {
      LOG_PRINT(LOG_DEBUG,"aifInterfaceRangeChk : Range Check Failed - interfaceType : %d",
            receivedMsgPtr->interfaceType);
      return FALSE;
   }
   if((receivedMsgPtr->dpc < 1) || (receivedMsgPtr->dpc > 16383))
   {
      LOG_PRINT(LOG_DEBUG,"aifInterfaceRangeChk : Range Check Failed - dpc : %d",
            receivedMsgPtr->dpc);
      return FALSE;
   }
   if((receivedMsgPtr->operationalState != DISABLED) && (receivedMsgPtr->operationalState != ENABLED))
   {
      LOG_PRINT(LOG_DEBUG,"aifInterfaceRangeChk : Range Check Failed - operationalState : %d",
            receivedMsgPtr->operationalState);
      return FALSE;
   }
   if((receivedMsgPtr->interfaceAdminState != LOCKED) && (receivedMsgPtr->interfaceAdminState != UNLOCKED))
   {
      LOG_PRINT(LOG_DEBUG,"aifInterfaceRangeChk : Range Check Failed - interfaceAdminState : %d",
            receivedMsgPtr->interfaceAdminState);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : trunkRangeChk()
Parameters    : TrunkTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_AIFTRUNKTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool trunkRangeChk(AiftrunkTableApi *receivedMsgPtr)
{
  /* Changes For E1-T1:Start */ 
   if (gBscTrunkType == BPM_TRUNK_TYPE_E1)
   {
      if(receivedMsgPtr->trunkType == TRUNK_T1_TYPE) 
      {
         LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed - mismatch in Preconfigured %d and received  trunkType : %d",BPM_TRUNK_TYPE_E1,receivedMsgPtr->trunkType);
         return FALSE;
      }   
   }
   if (gBscTrunkType == BPM_TRUNK_TYPE_T1)
   {
      if(receivedMsgPtr->trunkType == TRUNK_E1_TYPE) 
      {
         LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed - mismatch in Preconfigured %d and received  trunkType : %d",BPM_TRUNK_TYPE_T1,receivedMsgPtr->trunkType);
         return FALSE;
      }
      /* check tscicMapagainst max value(24 bits) for T1*/
      if(receivedMsgPtr->tsCicMap>0xFFFFFF) 
      {
         LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed -received Invalid(more than maximum value) tsCicMap : %u",receivedMsgPtr->tsCicMap);
         return FALSE;
      }
      
   }  
   
  /* Changes For E1-T1:Ends */ 
   //if ((receivedMsgPtr->e1Num < 0) || (receivedMsgPtr->e1Num > 7))
   /*BSC R2.0 Changes*/
   if ((receivedMsgPtr->e1Num < 0) || (receivedMsgPtr->e1Num > 39))
   {
      LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed - e1Num : %d",
            receivedMsgPtr->e1Num);
      return FALSE;
   }
   if ((receivedMsgPtr->trunkAdminState != LOCKED) && (receivedMsgPtr->trunkAdminState != UNLOCKED))
   {
      LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed - trunkAdminState : %d",
            receivedMsgPtr->trunkAdminState);
      return FALSE;
   }
   if ((receivedMsgPtr->trunkReset != RESET) && (receivedMsgPtr->trunkReset != NO_RESET))
   {
      LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed - trunkReset : %d",
            receivedMsgPtr->trunkReset);
      return FALSE;
   }
   if ((receivedMsgPtr->operationalState != ENABLED) && (receivedMsgPtr->operationalState != DISABLED))
   {
      LOG_PRINT(LOG_DEBUG,"trunkRangeChk : Range Check Failed - operationalState : %d",
            receivedMsgPtr->operationalState);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : linkSetRangeChk()
Parameters    : LinksetTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_LINKSETTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool linkSetRangeChk(LinksetTableApi *receivedMsgPtr)
{
   if ((receivedMsgPtr->linksetID < 1) || (receivedMsgPtr->linksetID > 250))
   {
      LOG_PRINT(LOG_DEBUG,"linkSetRangeChk : Range Check Failed - linksetID : %d",
            receivedMsgPtr->linksetID);
      return FALSE;
   }
   if((receivedMsgPtr->networkIndicator != NATIONAL) && 
         (receivedMsgPtr->networkIndicator != NATIONAL_RESERVED) &&
         (receivedMsgPtr->networkIndicator != INTERNATIONAL_RESERVED) &&
         (receivedMsgPtr->networkIndicator != INTERNATIONAL))
   {
      LOG_PRINT(LOG_DEBUG,"linkSetRangeChk : Range Check Failed - networkIndicator : %d",
            receivedMsgPtr->networkIndicator);
      return FALSE;
   }
   if((receivedMsgPtr->adminstate != LOCKED) && 
         (receivedMsgPtr->adminstate != UNLOCKED))
   {
      LOG_PRINT(LOG_DEBUG,"linkSetRangeChk : Range Check Failed - adminstate : %d",
            receivedMsgPtr->adminstate);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : linkRangeChk()
Parameters    : LinkTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_LINKTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool linkRangeChk(LinkTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->linkId < 0) || (receivedMsgPtr->linkId > 15))
   {
      LOG_PRINT(LOG_DEBUG,"linkRangeChk : Range Check Failed - linkId : %d",
            receivedMsgPtr->linkId);
      return FALSE;
   }
   if((receivedMsgPtr->e1Num < 0) || (receivedMsgPtr->e1Num > CFG_MAX_NUM_EXT_E1))
   {
      LOG_PRINT(LOG_DEBUG,"linkRangeChk : Range Check Failed - e1Num : %d",
            receivedMsgPtr->e1Num);
      return FALSE;
   }
   /* Changes For E1-T1:Starts */
   if(gBscTrunkType == BPM_TRUNK_TYPE_E1)
   {  
      if((receivedMsgPtr->timeSlot < 1) || (receivedMsgPtr->timeSlot > 31))
      {
          LOG_PRINT(LOG_DEBUG,"linkRangeChk : Range Check Failed for Trunk Type %d timeSlot : %d",
            BPM_TRUNK_TYPE_E1,receivedMsgPtr->timeSlot);
          return FALSE;
      }
   }
   if(gBscTrunkType == BPM_TRUNK_TYPE_T1)
   {  
      if((receivedMsgPtr->timeSlot < 1) || (receivedMsgPtr->timeSlot > 23))
      {
          LOG_PRINT(LOG_DEBUG,"linkRangeChk : Range Check Failed for Trunk Type %d timeSlot : %d",
            BPM_TRUNK_TYPE_T1,receivedMsgPtr->timeSlot);
          return FALSE;
      }
   }
   /* Changes For E1-T1:End */
   if((receivedMsgPtr->crcFlag != CRC_ENABLE) && (receivedMsgPtr->crcFlag != CRC_DISABLE))
   {
      LOG_PRINT(LOG_DEBUG,"linkRangeChk : Range Check Failed - crcFlag : %d",
            receivedMsgPtr->crcFlag);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : ss7RouteRangeChk()
Parameters    : Ss7RouteTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SS7ROUTETABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool ss7RouteRangeChk(Ss7RouteTableApi *receivedMsgPtr)
{
   if ((receivedMsgPtr->linksetID < 1) || (receivedMsgPtr->linksetID > 250))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - linksetID : %d",
            receivedMsgPtr->linksetID);
      return FALSE;
   }
   if ((receivedMsgPtr->routeID < 1) || (receivedMsgPtr->routeID > 100))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - routeID : %d",
            receivedMsgPtr->routeID);
      return FALSE;
   }
   if ((receivedMsgPtr->style != DPC_NI) && 
         (receivedMsgPtr->style != DPC_SIO_SSN))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - style : %d",
            receivedMsgPtr->style);
      return FALSE;
   }
   if((receivedMsgPtr->dpc < 1) || (receivedMsgPtr->dpc > 16383))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - dpc : %d",
            receivedMsgPtr->dpc);
      return FALSE;
   }
   if ((receivedMsgPtr->interfaceType != IF_TYPE_AIF))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - interfaceType : %d",
            receivedMsgPtr->interfaceType);
      return FALSE;
   }
   if ((receivedMsgPtr->rssn != SSN_BSSAP))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - rssn : %d",
            receivedMsgPtr->rssn);
      return FALSE;
   }
   if ((receivedMsgPtr->lssn != SSN_BSSAP))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - lssn : %d",
            receivedMsgPtr->lssn);
      return FALSE;
   }
   if((receivedMsgPtr->sstTestOn != ENABLE) && (receivedMsgPtr->sstTestOn != DISABLE))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - sstTestOn : %d",
            receivedMsgPtr->sstTestOn);
      return FALSE;
   }
   if((receivedMsgPtr->networkIndicator != NATIONAL) &&
	(receivedMsgPtr->networkIndicator != NATIONAL_RESERVED) &&
         (receivedMsgPtr->networkIndicator != INTERNATIONAL_RESERVED)&& 
         (receivedMsgPtr->networkIndicator != INTERNATIONAL))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - networkIndicator : %d",
            receivedMsgPtr->networkIndicator);
      return FALSE;
   }
   if((receivedMsgPtr->adminstate != LOCKED) && 
         (receivedMsgPtr->adminstate != UNLOCKED))
   {
      LOG_PRINT(LOG_DEBUG,"ss7RouteRangeChk : Range Check Failed - adminstate : %d",
            receivedMsgPtr->adminstate);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : storeReceivedMsgBuffer()
Parameters    : I_Void *receivedMsgPtr, I_U32 len
Return type   : I_Bool
Purpose       : To store the received message buffer in global pointer 
gStoredMsgBufPtr.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool storeReceivedMsgBuffer(I_Void *receivedMsgPtr, I_U32 len)
{
   gStoredMsgBufPtr= AlocOrdBuf(len);
   if(PNULL == gStoredMsgBufPtr) 
   {
      LOG_PRINT(LOG_CRITICAL,"Memory allocation using AlocOrdBuf API Failed Function:%s Line:%d",__FUNCTION__,__LINE__);   
      cfgSendNackToCm(CM_ERR_MEMORY_FAILURE);
      return FALSE;  
   }
   memcpy(gStoredMsgBufPtr,receivedMsgPtr,len);
   LOG_PRINT(LOG_INFO,"Stored the received message in gStoredMsgBufPtr");
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : setMtp3TimerTable()
Parameters    : None
Return type   : I_Void
Purpose       : To Modify the timers in Mtp3Timer table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setMtp3TimerTable()
{
   Mtp3TimerTableApi* receivedMsgPtr = (Mtp3TimerTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   Mtp3TimerTableApi  *mtp3TimerPtr = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;

   LOG_PRINT(LOG_INFO,"Entering function: setMtp3TimerTable");

   /* Check whether row exists in DB or not */ 
   if(CLIB_SUCCESS != getallMtp3TimerTable(&mtp3TimerPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_DEBUG, "No row exists in Mtp3Timer Table ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   else 
   {
      if (mtp3TimerPtr->dummyIndex != receivedMsgPtr->dummyIndex)
      {
         LOG_PRINT(LOG_DEBUG, "Row exists: Insertion not allowed in Mtp3Timer Table ");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(mtp3TimerPtr);
         return;
      }
      free(mtp3TimerPtr);

      /* Perform range check on received parameters */
      if(!mtp3TimerRangeChk(receivedMsgPtr))
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(Mtp3TimerTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_MTP3TIMERTABLE, SCM_MODIFY, OAM_SCM_MTP3_TIMER_CONFIG);

      /* Frame and Send the message to the OIL */
      if (!fillAndSendOamScmMtp3TimerConfig())
      {
         sendStackProcRespToCm();
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmMtp3TimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmMtp3TimerConfig(I_Void)
{
   OamScmMtp3TimerConfig mtp3TimerConfig;
   Mtp3TimerTableApi *mtp3TimerPtr = (Mtp3TimerTableApi*)gStoredMsgBufPtr;

   mtp3TimerConfig.mtp3TimerT1 = mtp3TimerPtr->mtp3Timermtp3_T1;
   mtp3TimerConfig.mtp3TimerT2 = mtp3TimerPtr->mtp3Timermtp3_T2;
   mtp3TimerConfig.mtp3TimerT3 = mtp3TimerPtr->mtp3Timermtp3_T3;
   mtp3TimerConfig.mtp3TimerT4 = mtp3TimerPtr->mtp3Timermtp3_T4;
   mtp3TimerConfig.mtp3TimerT5 = mtp3TimerPtr->mtp3Timermtp3_T5;
   mtp3TimerConfig.mtp3TimerT6 = mtp3TimerPtr->mtp3Timermtp3_T6;
   mtp3TimerConfig.mtp3TimerT7 = mtp3TimerPtr->mtp3Timermtp3_T7;
   mtp3TimerConfig.mtp3TimerT8 = mtp3TimerPtr->mtp3Timermtp3_T8;
   mtp3TimerConfig.mtp3TimerT9 = mtp3TimerPtr->mtp3Timermtp3_T9;
   mtp3TimerConfig.mtp3TimerT10 = mtp3TimerPtr->mtp3Timermtp3_T10;
   mtp3TimerConfig.mtp3TimerT11 = mtp3TimerPtr->mtp3Timermtp3_T11;
   mtp3TimerConfig.mtp3TimerT12 = mtp3TimerPtr->mtp3Timermtp3_T12;
   mtp3TimerConfig.mtp3TimerT13 = mtp3TimerPtr->mtp3Timermtp3_T13;
   mtp3TimerConfig.mtp3TimerT14 = mtp3TimerPtr->mtp3Timermtp3_T14;
   mtp3TimerConfig.mtp3TimerT15 = mtp3TimerPtr->mtp3Timermtp3_T15;
   mtp3TimerConfig.mtp3TimerT16 = mtp3TimerPtr->mtp3Timermtp3_T16;
   mtp3TimerConfig.mtp3TimerT17 = mtp3TimerPtr->mtp3Timermtp3_T17;
   mtp3TimerConfig.mtp3TimerT18 = mtp3TimerPtr->mtp3Timermtp3_T18;
   mtp3TimerConfig.mtp3TimerT19 = mtp3TimerPtr->mtp3Timermtp3_T19;
   mtp3TimerConfig.mtp3TimerT20 = mtp3TimerPtr->mtp3Timermtp3_T20;
   mtp3TimerConfig.mtp3TimerT21 = mtp3TimerPtr->mtp3Timermtp3_T21;
   mtp3TimerConfig.mtp3TimerT22 = mtp3TimerPtr->mtp3Timermtp3_T22;
   mtp3TimerConfig.mtp3TimerT23 = mtp3TimerPtr->mtp3Timermtp3_T23;
   mtp3TimerConfig.mtp3TimerT24 = mtp3TimerPtr->mtp3Timermtp3_T24;
   mtp3TimerConfig.mtp3TimerT25 = mtp3TimerPtr->mtp3Timermtp3_T25;
   mtp3TimerConfig.mtp3TimerT26 = mtp3TimerPtr->mtp3Timermtp3_T26;
   mtp3TimerConfig.mtp3TimerT27 = mtp3TimerPtr->mtp3Timermtp3_T27;
   mtp3TimerConfig.mtp3TimerT28 = mtp3TimerPtr->mtp3Timermtp3_T28;
   mtp3TimerConfig.mtp3TimerT29 = mtp3TimerPtr->mtp3Timermtp3_T29;
   mtp3TimerConfig.mtp3TimerT30 = mtp3TimerPtr->mtp3Timermtp3_T30;
   mtp3TimerConfig.mtp3TimerT31 = mtp3TimerPtr->mtp3Timermtp3_T31;
   mtp3TimerConfig.mtp3TimerT32 = mtp3TimerPtr->mtp3Timermtp3_T32;
   mtp3TimerConfig.mtp3TimerT33 = mtp3TimerPtr->mtp3Timermtp3_T33;
   mtp3TimerConfig.mtp3TimerT34 = mtp3TimerPtr->mtp3Timermtp3_T34;

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_MTP3_TIMER_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&mtp3TimerConfig, sizeof(mtp3TimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : mtp3TimerRangeChk()
Parameters    : Mtp3TimerTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_MTP3TIMERTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool mtp3TimerRangeChk(Mtp3TimerTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->mtp3Timermtp3_T1 < 5) || (receivedMsgPtr->mtp3Timermtp3_T1 > 12))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T1 : %d",
            receivedMsgPtr->mtp3Timermtp3_T1);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T2 < 7) || (receivedMsgPtr->mtp3Timermtp3_T2 > 20))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T2 : %d",
            receivedMsgPtr->mtp3Timermtp3_T2);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T3 < 5) || (receivedMsgPtr->mtp3Timermtp3_T3 > 12))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T3 : %d",
            receivedMsgPtr->mtp3Timermtp3_T3);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T4 < 5) || (receivedMsgPtr->mtp3Timermtp3_T4 > 12))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T4 : %d",
            receivedMsgPtr->mtp3Timermtp3_T4);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T5 < 5) || (receivedMsgPtr->mtp3Timermtp3_T5 > 12))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T5 : %d",
            receivedMsgPtr->mtp3Timermtp3_T5);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T6 < 5) || (receivedMsgPtr->mtp3Timermtp3_T6 > 12))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T6 : %d",
            receivedMsgPtr->mtp3Timermtp3_T6);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T7 < 10) || (receivedMsgPtr->mtp3Timermtp3_T7 > 20))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T7 : %d",
            receivedMsgPtr->mtp3Timermtp3_T7);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T8 < 8) || (receivedMsgPtr->mtp3Timermtp3_T8 > 12))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T8 : %d",
            receivedMsgPtr->mtp3Timermtp3_T8);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T9 != 0))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T9 : %d",
            receivedMsgPtr->mtp3Timermtp3_T9);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T10 < 300) || (receivedMsgPtr->mtp3Timermtp3_T10 > 600))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T10 : %d",
            receivedMsgPtr->mtp3Timermtp3_T10);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T11 < 300) || (receivedMsgPtr->mtp3Timermtp3_T11 > 900))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T11 : %d",
            receivedMsgPtr->mtp3Timermtp3_T11);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T12 < 8) || (receivedMsgPtr->mtp3Timermtp3_T12 > 15))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T12 : %d",
            receivedMsgPtr->mtp3Timermtp3_T12);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T13 < 8) || (receivedMsgPtr->mtp3Timermtp3_T13 > 15))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T13 : %d",
            receivedMsgPtr->mtp3Timermtp3_T13);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T14 < 20) || (receivedMsgPtr->mtp3Timermtp3_T14 > 30))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T14 : %d",
            receivedMsgPtr->mtp3Timermtp3_T14);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T15 < 20) || (receivedMsgPtr->mtp3Timermtp3_T15 > 30))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T15 : %d",
            receivedMsgPtr->mtp3Timermtp3_T15);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T16 < 14) || (receivedMsgPtr->mtp3Timermtp3_T16 > 20))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T16 : %d",
            receivedMsgPtr->mtp3Timermtp3_T16);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T17 < 8) || (receivedMsgPtr->mtp3Timermtp3_T17 > 15))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T17 : %d",
            receivedMsgPtr->mtp3Timermtp3_T17);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T18 < 20) || (receivedMsgPtr->mtp3Timermtp3_T18 > 500))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T18 : %d",
            receivedMsgPtr->mtp3Timermtp3_T18);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T19 < 670) || (receivedMsgPtr->mtp3Timermtp3_T19 > 6000))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T19 : %d",
            receivedMsgPtr->mtp3Timermtp3_T19);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T20 < 590) || (receivedMsgPtr->mtp3Timermtp3_T20 > 1200))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T20 : %d",
            receivedMsgPtr->mtp3Timermtp3_T20);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T21 < 630) || (receivedMsgPtr->mtp3Timermtp3_T21 > 1200))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T21 : %d",
            receivedMsgPtr->mtp3Timermtp3_T21);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T22 < 10) || (receivedMsgPtr->mtp3Timermtp3_T22 > 3600))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T22 : %d",
            receivedMsgPtr->mtp3Timermtp3_T22);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T23 < 10) || (receivedMsgPtr->mtp3Timermtp3_T23 > 3600))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T23 : %d",
            receivedMsgPtr->mtp3Timermtp3_T23);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T24 < 10) || (receivedMsgPtr->mtp3Timermtp3_T24 > 3600))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T24 : %d",
            receivedMsgPtr->mtp3Timermtp3_T24);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T25 < 300) || (receivedMsgPtr->mtp3Timermtp3_T25 > 350))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T25 : %d",
            receivedMsgPtr->mtp3Timermtp3_T25);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T26 < 120) || (receivedMsgPtr->mtp3Timermtp3_T26 > 150))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T26 : %d",
            receivedMsgPtr->mtp3Timermtp3_T26);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T27 < 20) || (receivedMsgPtr->mtp3Timermtp3_T27 > 50))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T27 : %d",
            receivedMsgPtr->mtp3Timermtp3_T27);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T28 < 30) || (receivedMsgPtr->mtp3Timermtp3_T28 > 350))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T28 : %d",
            receivedMsgPtr->mtp3Timermtp3_T28);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T29 < 600) || (receivedMsgPtr->mtp3Timermtp3_T29 > 650))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T29 : %d",
            receivedMsgPtr->mtp3Timermtp3_T29);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T30 < 300) || (receivedMsgPtr->mtp3Timermtp3_T30 > 350))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T30 : %d",
            receivedMsgPtr->mtp3Timermtp3_T30);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T31 < 1) || (receivedMsgPtr->mtp3Timermtp3_T31 > 200))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T31 : %d",
            receivedMsgPtr->mtp3Timermtp3_T31);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T32 < 1) || (receivedMsgPtr->mtp3Timermtp3_T32 > 100))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T32 : %d",
            receivedMsgPtr->mtp3Timermtp3_T32);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T33 < 300) || (receivedMsgPtr->mtp3Timermtp3_T33 > 1200))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T33 : %d",
            receivedMsgPtr->mtp3Timermtp3_T33);
      return FALSE;
   }
   if((receivedMsgPtr->mtp3Timermtp3_T34 < 1) || (receivedMsgPtr->mtp3Timermtp3_T34 > 100))
   {
      LOG_PRINT(LOG_DEBUG,"mtp3TimerRangeChk : Range Check Failed - mtp3Timermtp3_T34 : %d",
            receivedMsgPtr->mtp3Timermtp3_T34);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : setSccpTimerTable()
Parameters    : None
Return type   : I_Void
Purpose       : To Modify the timers in SccpTimer table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setSccpTimerTable()
{
   SccpTimerTableApi* receivedMsgPtr = (SccpTimerTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   SccpTimerTableApi  *sccpTimerPtr = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;

   LOG_PRINT(LOG_INFO,"Entering function: setSccpTimerTable");

   /* Check whether row exists in DB or not */ 
   if(CLIB_SUCCESS != getallSccpTimerTable(&sccpTimerPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_INFO, "No row exists in SccpTimer Table ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   else 
   {
      if (sccpTimerPtr->dummyIndex != receivedMsgPtr->dummyIndex)
      {
         LOG_PRINT(LOG_DEBUG, "Row exists: Insertion not allowed in SccpTimer Table ");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(sccpTimerPtr);
         return;
      }
      free(sccpTimerPtr);

      /* Perform range check on received parameters */
      if(!sccpTimerRangeChk(receivedMsgPtr))
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SccpTimerTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_SCCPTIMERTABLE, SCM_MODIFY, OAM_SCM_SCCP_TIMER_CONFIG);

      /* Frame and Send the message to the OIL */
      if (!fillAndSendOamScmSccpTimerConfig())
      {
         sendStackProcRespToCm();
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmSccpTimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmSccpTimerConfig(I_Void)
{
   OamScmSccpTimerConfig sccpTimerConfig;
   SccpTimerTableApi *sccpTimerPtr = (SccpTimerTableApi*)gStoredMsgBufPtr;

   sccpTimerConfig.sccpTimerstatInfo = sccpTimerPtr->sccpTimerstatInfo ;
   sccpTimerConfig.sccpTimercoordChg = sccpTimerPtr->sccpTimercoordChg ;
   sccpTimerConfig.sccpTimerig0reSST = sccpTimerPtr->sccpTimerig0reSST;
   sccpTimerConfig.sccpTimerrtgStatInfor = sccpTimerPtr->sccpTimerrtgStatInfo ;
   sccpTimerConfig.sccpTimerconn = sccpTimerPtr->sccpTimerconn ;
   sccpTimerConfig.sccpTimerrelease = sccpTimerPtr->sccpTimerrelease ;
   sccpTimerConfig.sccpTimerreset = sccpTimerPtr->sccpTimerreset ;
   sccpTimerConfig.sccpTimerias = sccpTimerPtr->sccpTimerias ;
   sccpTimerConfig.sccpTimeriar = sccpTimerPtr->sccpTimeriar ;
   sccpTimerConfig.sccpTimerguard = sccpTimerPtr->sccpTimerguard ;
   sccpTimerConfig.sccpTimerreassembly = sccpTimerPtr->sccpTimerreassembly ;
   sccpTimerConfig.sccpTimerinterval = sccpTimerPtr->sccpTimerinterval ;
   sccpTimerConfig.sccpTimerrepeatRelease = sccpTimerPtr->sccpTimerrepeatRelease ;

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_SCCP_TIMER_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sccpTimerConfig, sizeof(sccpTimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : sccpTimerRangeChk()
Parameters    : SccpTimerTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SCCPTIMERTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool sccpTimerRangeChk(SccpTimerTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->sccpTimerstatInfo < 5) || (receivedMsgPtr->sccpTimerstatInfo > 1200))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerstatInfo : %d",
            receivedMsgPtr->sccpTimerstatInfo);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimercoordChg < 60) || (receivedMsgPtr->sccpTimercoordChg > 120))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimercoordChg : %d",
            receivedMsgPtr->sccpTimercoordChg);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerig0reSST < 30) || (receivedMsgPtr->sccpTimerig0reSST > 60))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerig0reSST : %d",
            receivedMsgPtr->sccpTimerig0reSST);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerrtgStatInfo < 30) || (receivedMsgPtr->sccpTimerrtgStatInfo > 60))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerrtgStatInfo : %d",
            receivedMsgPtr->sccpTimerrtgStatInfo);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerconn < 60) || (receivedMsgPtr->sccpTimerconn > 120))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerconn : %d",
            receivedMsgPtr->sccpTimerconn);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerrelease < 10) || (receivedMsgPtr->sccpTimerrelease > 20))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerrelease : %d",
            receivedMsgPtr->sccpTimerrelease);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerreset < 10) || (receivedMsgPtr->sccpTimerreset > 20))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerreset : %d",
            receivedMsgPtr->sccpTimerreset);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerias < 1) || (receivedMsgPtr->sccpTimerias > 600))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerias : %d",
            receivedMsgPtr->sccpTimerias);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimeriar < 1) || (receivedMsgPtr->sccpTimeriar > 1260))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimeriar : %d",
            receivedMsgPtr->sccpTimeriar);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerguard < 60) || (receivedMsgPtr->sccpTimerguard > 600))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerguard : %d",
            receivedMsgPtr->sccpTimerguard);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerreassembly < 10) || (receivedMsgPtr->sccpTimerreassembly > 20))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerreassembly : %d",
            receivedMsgPtr->sccpTimerreassembly);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerinterval < 1) || (receivedMsgPtr->sccpTimerinterval > 60))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerinterval : %d",
            receivedMsgPtr->sccpTimerinterval);
      return FALSE;
   }
   if((receivedMsgPtr->sccpTimerrepeatRelease < 1) || (receivedMsgPtr->sccpTimerrepeatRelease > 20))
   {
      LOG_PRINT(LOG_DEBUG,"sccpTimerRangeChk : Range Check Failed - sccpTimerrepeatRelease : %d",
            receivedMsgPtr->sccpTimerrepeatRelease);
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : setBssapTimerTable()
Parameters    : None
Return type   : I_Void
Purpose       : To Modify the timers in BssapTimer table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setBssapTimerTable()
{
   BssapTimerTableApi* receivedMsgPtr = (BssapTimerTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   BssapTimerTableApi  *bssapTimerPtr = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;

   LOG_PRINT(LOG_INFO,"Entering function: setBssapTimerTable");

   /* Check whether row exists in DB or not */ 
   if(CLIB_SUCCESS != getallBssapTimerTable(&bssapTimerPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_INFO, "No row exists in BssapTimer Table ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   else 
   {
      if (bssapTimerPtr->index != receivedMsgPtr->index)
      {
         LOG_PRINT(LOG_DEBUG, "Row exists: Insertion not allowed in BssapTimer Table ");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(bssapTimerPtr);
         return;
      }
      free(bssapTimerPtr);

      /* Perform range check on received parameters */
      if(!bssapTimerRangeChk(receivedMsgPtr))
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(BssapTimerTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_BSSAPTIMERTABLE, SCM_MODIFY, OAM_SCM_BSSAP_TIMER_CONFIG);

      /* Frame and Send the message to the OIL */
      if (!fillAndSendOamScmBssapTimerConfig())
      {
         sendStackProcRespToCm();
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmBssapTimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmBssapTimerConfig(I_Void)
{
   OamScmBssapTimerConfig bssapTimerConfig;
   BssapTimerTableApi *bssapTimerPtr = (BssapTimerTableApi*)gStoredMsgBufPtr;

   bssapTimerConfig.bssapTimerT1 = bssapTimerPtr->bssapTimerT1;
   bssapTimerConfig.bssapTimerT4 = bssapTimerPtr->bssapTimerT4;
   bssapTimerConfig.bssapTimerT10 = bssapTimerPtr->bssapTimerT10;
   bssapTimerConfig.bssapTimerT11 = bssapTimerPtr->bssapTimerT11;
   bssapTimerConfig.bssapTimerT13 = bssapTimerPtr->bssapTimerT13;
   bssapTimerConfig.bssapTimerT17 = bssapTimerPtr->bssapTimerT17;
   bssapTimerConfig.bssapTimerT18 = bssapTimerPtr->bssapTimerT18;
   bssapTimerConfig.bssapTimerT19 = bssapTimerPtr->bssapTimerT19;
   bssapTimerConfig.bssapTimerT20 = bssapTimerPtr->bssapTimerT20;

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_BSSAP_TIMER_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&bssapTimerConfig, sizeof(bssapTimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : bssapTimerRangeChk()
Parameters    : BssapTimerTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_BSSAPTIMERTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool bssapTimerRangeChk(BssapTimerTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->bssapTimerT1 < 1) || (receivedMsgPtr->bssapTimerT1 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk : Range Check Failed - bssapTimerT1 : %d",
            receivedMsgPtr->bssapTimerT1);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT4 < 1) || (receivedMsgPtr->bssapTimerT4 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT4 : %d",
            receivedMsgPtr->bssapTimerT4);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT10 < 1) || (receivedMsgPtr->bssapTimerT10 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT10 : %d",
            receivedMsgPtr->bssapTimerT10);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT11 < 1) || (receivedMsgPtr->bssapTimerT11 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT11 : %d",
            receivedMsgPtr->bssapTimerT11);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT13 < 1) || (receivedMsgPtr->bssapTimerT13 > 300))
   {
      LOG_PRINT(LOG_DEBUG,":bssapTimerRangeChk Range Check Failed - bssapTimerT13 : %d",
            receivedMsgPtr->bssapTimerT13);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT17 < 1) || (receivedMsgPtr->bssapTimerT17 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT17 : %d",
            receivedMsgPtr->bssapTimerT17);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT18 < 1) || (receivedMsgPtr->bssapTimerT18 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT18 : %d",
            receivedMsgPtr->bssapTimerT18);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT19 < 1) || (receivedMsgPtr->bssapTimerT19 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT19 : %d",
            receivedMsgPtr->bssapTimerT19);
      return FALSE;
   }
   if((receivedMsgPtr->bssapTimerT20 < 1) || (receivedMsgPtr->bssapTimerT20 > 300))
   {
      LOG_PRINT(LOG_DEBUG,"bssapTimerRangeChk: Range Check Failed - bssapTimerT20 : %d",
            receivedMsgPtr->bssapTimerT20);
      return FALSE;
   }
   return TRUE;
}

/*Changes for R2.3.4 starts*/
#if 0
/******************************* Function  Header*****************************
  Function Name : setLapdTimerTable()
Parameters    : None
Return type   : I_Void
Purpose       : To Modify the timers in LapdTimer table
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void setLapdTimerTable()
{
   LapdTimerTableApi* receivedMsgPtr = (LapdTimerTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

   LapdTimerTableApi  *lapdTimerPtr = NULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;

   LOG_PRINT(LOG_INFO,"Entering function: setLapdTimerTable");

   /* Check whether row exists in DB or not */ 
   if(CLIB_SUCCESS != getallLapdTimerTable(&lapdTimerPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_INFO, "No row exists in LapdTimer Table ");
      cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return;
   }
   else 
   {
      if (lapdTimerPtr->lapdTimerDUMMYIndex != receivedMsgPtr->lapdTimerDUMMYIndex)
      {
         LOG_PRINT(LOG_DEBUG, "Row exists: Insertion not allowed in LapdTimer Table ");
         cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
         free(lapdTimerPtr);
         return;
      }
      free(lapdTimerPtr);

      /* Perform range check on received parameters */
      if(!lapdTimerRangeChk(receivedMsgPtr))
      {
         cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
         return; 
      }

      /* Store the received message in global pointer */
      if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(LapdTimerTableApi)))
      {
         return; 
      }

      /* Set Stack object data structure */
      setStackObject(BSC_API_SET_LAPDTIMERTABLE, SCM_MODIFY, OAM_SCM_LAPDTIMER_CONFIG);

      /* Frame and Send the message to the OIL */
      if (!fillAndSendOamScmLapdTimerConfig())
      {
         sendStackProcRespToCm();
         return;
      }
   }
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmLapdTimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmLapdTimerConfig(I_Void)
{
   OamScmLapdTimerConfig lapdTimerConfig;
   LapdTimerTableApi *lapdTimerPtr = (LapdTimerTableApi*)gStoredMsgBufPtr;

   lapdTimerConfig.lapdTimerT200 = lapdTimerPtr->lapdTimerT200; 
   lapdTimerConfig.lapdTimerT201 = lapdTimerPtr->lapdTimerT201; 
   lapdTimerConfig.lapdTimerT202 = lapdTimerPtr->lapdTimerT202; 
   lapdTimerConfig.lapdTimerT203 = lapdTimerPtr->lapdTimerT203; 

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LAPDTIMER_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&lapdTimerConfig, sizeof(lapdTimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : lapdTimerRangeChk()
Parameters    : LapdTimerTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_LAPDTIMERTABLE.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool lapdTimerRangeChk(LapdTimerTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->lapdTimerT200 < 1) || (receivedMsgPtr->lapdTimerT200 > 5))
   {
      LOG_PRINT(LOG_DEBUG,"lapdTimerRangeChk : Range Check Failed - lapdTimerT200 : %d",
            receivedMsgPtr->lapdTimerT200);
      return FALSE;
   }
   if((receivedMsgPtr->lapdTimerT201 < 1) || (receivedMsgPtr->lapdTimerT201 > 5))
   {
      LOG_PRINT(LOG_DEBUG,"lapdTimerRangeChk : Range Check Failed - lapdTimerT201 : %d",
            receivedMsgPtr->lapdTimerT201);
      return FALSE;
   }
   if((receivedMsgPtr->lapdTimerT202 < 1) || (receivedMsgPtr->lapdTimerT202 > 5))
   {
      LOG_PRINT(LOG_DEBUG,"lapdTimerRangeChk : Range Check Failed - lapdTimerT202 : %d",
            receivedMsgPtr->lapdTimerT202);
      return FALSE;
   }
   if((receivedMsgPtr->lapdTimerT203 < 10) || (receivedMsgPtr->lapdTimerT203 > 100))
   {
      LOG_PRINT(LOG_DEBUG,"lapdTimerRangeChk : Range Check Failed - lapdTimerT203 : %d",
            receivedMsgPtr->lapdTimerT203);
      return FALSE;
   }
   return TRUE;
}
#endif
/*Changes for R2.3.4 starts*/

/******************************* Function  Header*****************************
  Function Name : addSs7StackScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles response from SCM for addition in Ss7Stack Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void addSs7StackScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      Ss7StackConfigTableApi *ss7StackTablePtr = (Ss7StackConfigTableApi *)gStoredMsgBufPtr;
      if (insertSs7StackConfigTable(ss7StackTablePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"In addSs7StackScmRespHandler: insertSs7StackConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }  
   else
   {
			LOG_PRINT(LOG_INFO,"Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : modifySs7StackScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles response from SCM for modification in Ss7Stack Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifySs7StackScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      Ss7StackConfigTableApi *ss7StackTablePtr = (Ss7StackConfigTableApi *)gStoredMsgBufPtr;
      if (updateSs7StackConfigTable(ss7StackTablePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"In modifySs7StackScmRespHandler: updateSs7StackConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	     LOG_PRINT(LOG_INFO,"Received error from SCM");
     // setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : addInterfaceScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles response from SCM for addition in AifInterface Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void addInterfaceScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {

      AifInterfaceTableApi *aifInterfacePtr = (AifInterfaceTableApi *)gStoredMsgBufPtr;
      TrunkGroupTableApi trunkGroupBuf;     
      trunkGroupBuf.interfaceId = aifInterfacePtr->interfaceId;
      trunkGroupBuf.tgpId = DEFAULT_TGPID;
      trunkGroupBuf.tgpAdminState = UNLOCKED;
      trunkGroupBuf.operationalState = ENABLED;
      if (insertTrunkGroupTable(&trunkGroupBuf) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"In addInterfaceScmRespHandler: insertTrunkGroupTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
         goto label_fail;
      }

      aifInterfacePtr->tgpId = DEFAULT_TGPID;
      aifInterfacePtr->interfaceAdminState = UNLOCKED;
      aifInterfacePtr->operationalState = DISABLED;
      if (insertAifInterfaceTable(aifInterfacePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"In addInterfaceScmRespHandler: insertAifInterfaceTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
         goto label_fail;
      }
   }
   else
   {
	
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
      goto label_fail;
   }
label_fail:   
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : addLinkSetScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles response from SCM for addition in LinkSet Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void addLinkSetScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      LinksetTableApi *linkSetPtr = (LinksetTableApi *)gStoredMsgBufPtr;
      if (insertLinksetTable(linkSetPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"In addLinkSetScmRespHandler: insertLinksetTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
      else
      {
         updateOrInsertLinkSetStatusTable(linkSetPtr->linksetID,DISABLED);
      }  
   }
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : addTrunkScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles response from SCM for addition in Trunk Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void addTrunkScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
   I_U32 timeSlotCicMap[CFG_MAX_NUM_E1_TS] = {0}, count;
   AiftrunkTableApi *trunkPtr = (AiftrunkTableApi *)gStoredMsgBufPtr;
   LinkTableApi  *linkTableDbPtr = NULL;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (getCicForTimeSlots(trunkPtr->startCic, trunkPtr->endCic, 
               trunkPtr->tsCicMap, timeSlotCicMap) != CFG_SUCCESS)
      { 
         return;
      }
      CicTableApi cicTableBuf;

      /* For loop starts from 1 in order to skip timeslot 0 */
      for (count = 1; count < CFG_MAX_NUM_E1_TS; count++)
      {
         if ((timeSlotCicMap[count] != INVALID_CIC) ) 
         {
            cicTableBuf.interfaceId = trunkPtr->interfaceId;
            cicTableBuf.tgpId = trunkPtr->tgpId;
            cicTableBuf.e1Num = trunkPtr->e1Num;
            cicTableBuf.timeSlot = count;
            cicTableBuf.cicId = timeSlotCicMap[count];
            cicTableBuf.usage = SPEECH;
            cicTableBuf.adminState = UNLOCKED;
            cicTableBuf.reset = NO_RESET;

            /* Continue the loop without inserting CIC-row if E1 AND timeslot is configured for MTP2 */
            if (CLIB_SUCCESS == getLinkTableUsingE1Ts(trunkPtr->e1Num, count, &linkTableDbPtr))
            {
               LOG_PRINT(LOG_DEBUG,"Mtp2-Link configured for TrunkPort=%d timeslot=%d..", trunkPtr->e1Num, count);
               continue;
            }
            /* Continue the loop without inserting CIC-row if E1 AND timeslot is configured for MLPPP */
            if(CLIB_SUCCESS == getMccTrunkNumTsUsingExtTrunkNumTs(trunkPtr->e1Num, 
               count, &mccLinkResourceDbPtr, &outCount, &outSize))
            {
               LOG_PRINT(LOG_DEBUG,"Mlppp is configured for TrunkPort=%d timeslot=%d..", trunkPtr->e1Num, count);
               continue;
            }

            if (insertCicTable(&cicTableBuf) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL,"In addTrunkScmRespHandler: insertCicTable Failed..");
               cfgSendNackToCm(CM_ERR_INSERT_DB_OPER_FAILED);
            }
            else
               gE1TimeslotData[cicTableBuf.e1Num][cicTableBuf.timeSlot].e1TimeslotState = unlocked;
         }
      }
      if (gE1Data[trunkPtr->e1Num].e1State == unlocked &&
            gE1Data[trunkPtr->e1Num].LOS_Active == FALSE &&
            gE1Data[trunkPtr->e1Num].trunkState == Enabled)
      {
         sendE1UnlockReqToGrhm(trunkPtr->e1Num);
      }
      else 
         unblockCicsRespHandler();       
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
     // setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
      sendStackProcRespToCm();
   }
}

/******************************* Function  Header*****************************
  Function Name : sendE1UnlockReqToGrhm()
Parameters    : I_U32 e1Num
Return type   : I_Void
Purpose       : Send E1 unlock request to GRHM 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendE1UnlockReqToGrhm(I_U32 e1Num)
{
   OamsCfgGrhmUnlockReq unlockReqToGrhm;        
   unlockReqToGrhm.objectId = e1Num;
   unlockReqToGrhm.objType = OAMS_OBJTYPE_E1;
   unlockReqToGrhm.reason = OAMS_RSN_UNBLOCKCICS;

   setStackObject(BSC_API_SET_AIFTRUNKTABLE, SCM_ADD, OAMS_CFG_GRHM_UNLOCK_REQ);
   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_GRHM_UNLOCK_REQ..");
   cfgSendMessage(&unlockReqToGrhm,sizeof(OamsCfgGrhmUnlockReq),ENT_CSAPP_GRHM,
         OAMS_CFG_GRHM_UNLOCK_REQ,0);
}

/******************************* Function  Header*****************************
  Function Name : unblockCicsRespHandler()
Parameters    : void 
Return type   : I_Void
Purpose       : Handle E1 unlock response from GRHM 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void unblockCicsRespHandler()
{
   AiftrunkTableApi *trunkTablePtr = (AiftrunkTableApi *)gStoredMsgBufPtr;

   trunkTablePtr->trunkAdminState = UNLOCKED;
   trunkTablePtr->trunkReset = NO_RESET;
   if (insertAiftrunkTable(trunkTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"In unblockCicsRespHandler: insertAiftrunkTable Failed..");
      setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : addLinkScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles response from SCM for addition in Link Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void addLinkScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   LinkTableApi *linkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   I_U32 cardOprState = 0;
   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      setFailCauseInStackObj(CM_SUCCESS);
      setStackObject(BSC_API_SET_LINKTABLE, SCM_ADD, OAMS_CFG_GRHM_SWITCH_CONNECT);
      /*BSC CS4.0 HA Changes Starts*/
      if (getStateForSlotIdIccTable(linkTablePtr->cardNum,&cardOprState) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_DEBUG, "Received cardNum does not exists in iccCardInfo Table");
         cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
         return;
      }

      if (cardOprState == CARDSTATE_STANDBY)
      {
         /*
         LOG_PRINT(LOG_DEBUG, 
         "%s: Rcvd cardNum not active Sending Switching Request to RM",__func__);
         sendSwitchConnectReqToRm(linkTablePtr);
         */
        
         /*HA-CHANGES Starts*/
         sendPeerSwitchConnectReqToGrhm(linkTablePtr);
         //linkSwitchConnectAckHandler();
         /*HA-CHANGES Ends*/
         return;
      }
      else if (cardOprState == CARDSTATE_ACTIVE)
      {
         LOG_PRINT(LOG_DEBUG, "addLinkScmRespHandler: Received cardNum is in active state. Sending Switching Request to GRHM");
         sendSwitchConnectReqToGrhm(linkTablePtr);
      }
      else
      {
         LOG_PRINT(LOG_DEBUG, "addLinkScmRespHandler: Card is not ready for switching");
         setFailCauseInStackObj(CM_ERR_CARD_NOT_READY_FOR_SWITCHING);
         modifyExtTrunkNumTsPeerTrunkNumTsInMccLink(INVALID_E1,INVALID_TS,INVALID_E1,INVALID_TS);
         sendStackProcRespToCm();  
         
      }

      /*BSC CS4.0 HA Changes Ends*/
   }  
   else
   {
		  LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
      modifyExtTrunkNumTsPeerTrunkNumTsInMccLink(INVALID_E1,INVALID_TS,INVALID_E1,INVALID_TS);
      sendStackProcRespToCm();
   }
}

/******************************* Function  Header*****************************
  Function Name : modifyExtTrunkNumTsPeerTrunkNumTsInMccLink()
Parameters    : I_U32 e1Num, I_U8 timeSlot
Return type   : I_Void
Purpose       : To modify extTrunkNum, extTrunkTs in MccLinkResource Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifyExtTrunkNumTsPeerTrunkNumTsInMccLink(I_U32 e1Num, I_U8 timeSlot, I_U32 peerTrunkNum, I_U32 peerTs)
{
   LinkTableApi *linkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   MccLinkResourceTableIndices mccLinkTableIndex;
   I_U32 outCount = 0;
   I_U16 outSize = 0;
   I_S32 res;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(linkTablePtr->e1Num, 
      linkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"getMccLinkResourceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }

   res = markPeerTrunkTsFree(mccLinkResourceDbPtr->peerTrunkNum,mccLinkResourceDbPtr->peerTrunkTs);

   LOG_PRINT(DEBUG,"markPeerTrunkTsFree for peerTrunk:%d peerTs:%d ret err:%d",
        mccLinkResourceDbPtr->peerTrunkNum, mccLinkResourceDbPtr->peerTrunkTs, res );
   mccLinkResourceDbPtr->extTrunkNum = e1Num;
   mccLinkResourceDbPtr->extTrunkTs = timeSlot;
   mccLinkResourceDbPtr->peerTrunkNum = peerTrunkNum;
   mccLinkResourceDbPtr->peerTrunkTs = peerTs;
   res = updateMccLinkResourceTable(mccLinkResourceDbPtr);
   if (res != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_MAJOR, "updateExtTrunkNumTsInMccLinkTable Failed..err:%d", res);
      setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      free(mccLinkResourceDbPtr);
      return;
   }

   free(mccLinkResourceDbPtr);
}

/******************************* Function  Header*****************************
  Function Name : linkSwitchConnectAckHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles Switch Connect Ack for add or modify in Link Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void linkSwitchConnectAckHandler()
{
   LinkStatusTableApi linkStatus;
   I_U32 cardOprState = 0;
   LinkTableApi *linkPtr = (LinkTableApi *)gStoredMsgBufPtr;
   switch ( getScmAction() ) 
   {
      case SCM_ADD:
         {
            LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
            if (insertLinkTable(linkPtr) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR,"In linkSwitchConnectAckHandler: insertLinkTable Failed..");
               setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
            }
            else
            {
               gE1TimeslotData[linkPtr->e1Num][linkPtr->timeSlot].e1TimeslotState = locked;

               linkStatus.linksetID = linkPtr->linksetID;
               linkStatus.linkId = linkPtr->linkId;
               linkStatus.oprState = DISABLED;
               if (insertLinkStatusTable(&linkStatus) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_MAJOR,"In linkSwitchConnectAckHandler: insertLinkStatusTable Failed..");
               }
            }

            LOG_PRINT(LOG_INFO,"Updating Link Status as Allocated in MccLinkResource Table for e1Mum:%d timeSlot:%d",linkPtr->e1Num, linkPtr->timeSlot);
            if (updateLinkStatusInMccLinkTable(linkPtr->e1Num, linkPtr->timeSlot, SYS_TS_ALLOCATED) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR,"In linkSwitchConnectAckHandler: updateLinkStatusInMccLinkResourceTable Failed..");
               setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
            }
            else 
               LOG_PRINT(LOG_INFO,"Updated Link Status as Allocated in MccLinkResource Table");

            if (getStateForSlotIdIccTable(linkPtr->cardNum,&cardOprState) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_DEBUG, "Received cardNum does not exists in iccCardInfo Table");
               setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
            }
            else
            {
                if (cardOprState == CARDSTATE_STANDBY)
                {
                   sendSwitchReqToPeerCfg(linkPtr->e1Num,linkPtr->timeSlot,CFG_MAKE_SWITCH,CFG_SWITCH_LINK_ADD_DEL); 
                   sendBpmSwitchInfoForPeerCard(linkPtr->cardNum);
                }  
            }
            sendStackProcRespToCm();
         }
         break;
      case SCM_MODIFY:
         {
            LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
            MccLinkResourceTableIndices mccLinkTableIndex;
            if (updateLinkTable(linkPtr) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR,"In linkSwitchConnectAckHandler: updateLinkTable Failed..");
               setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
            }
            mccLinkTableIndex.mccTrunkNum  = gStackObject.mccTrunkNum;
            mccLinkTableIndex.mccTrunkTs   = gStackObject.mccTrunkTs;
            mccLinkTableIndex.cardNum      = gStackObject.cardNum;

            if (updateExtTrunkNumTsInMccLinkTable(&mccLinkTableIndex, linkPtr->e1Num,
                     linkPtr->timeSlot) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_MAJOR, "updateExtTrunkNumTsInMccLinkTable Failed..");
               setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
            }

            if (getStateForSlotIdIccTable(linkPtr->cardNum,&cardOprState) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_DEBUG, "Received cardNum does not exists in iccCardInfo Table");
               setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
            }
            else
            {
                if (cardOprState == CARDSTATE_STANDBY)
                {
                   sendBpmSwitchInfoForPeerCard(linkPtr->cardNum);
                }  
            }
            sendStackProcRespToCm();
         }
         break;
      default : 
         LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
}

/******************************* Function  Header*****************************
  Function Name : linkSwitchConnectNackHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles Switch Connect Nack for add or modify in Link Table 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void linkSwitchConnectNackHandler()
{
   switch ( getScmAction() ) 
   {
      case SCM_ADD:
         {
            LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
            setStackObject(BSC_API_SET_LINKTABLE, SCM_DELETE, OAM_SCM_LINK_CONFIG);
            setFailCauseInStackObj(CM_ERR_SWITCH_CONNECT_NACK);
            if ( ! fillAndSendOamScmLinkConfig() ) 
            {
               sendStackProcRespToCm();
               return;      
            }
         }
         break;
      case SCM_MODIFY:
         {
            LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
            setFailCauseInStackObj(CM_ERR_SWITCH_CONNECT_NACK);
            sendStackProcRespToCm();
         }
         break;
      default : 
         LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
}

/******************************* Function  Header*****************************
  Function Name : sendSwitchConnectReqToGrhm()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch connect request to GRHM 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendSwitchConnectReqToGrhm(LinkTableApi *linkTablePtr)
{
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   LinkTableApi *rcvlinkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(linkTablePtr->e1Num, 
      linkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"getMccLinkResourceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      sendStackProcRespToCm();
      return;
   }

   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_GRHM_SWITCH_CONNECT..");
   oamsCfgGrhmSwitchConnect.firstE1Num = rcvlinkTablePtr->e1Num;
   oamsCfgGrhmSwitchConnect.firstTimeSlotNum = rcvlinkTablePtr->timeSlot;
   oamsCfgGrhmSwitchConnect.secondE1Num = mccLinkResourceDbPtr->mccTrunkNum;
   oamsCfgGrhmSwitchConnect.secondTimeSlotNum = mccLinkResourceDbPtr->mccTrunkTs;
   LOG_PRINT(LOG_INFO,"oamsCfgGrhmSwitchConnect : First E1 : %d, \
         First Ts : %d, SecE1 : %d, SecTs : %d",
         oamsCfgGrhmSwitchConnect.firstE1Num, oamsCfgGrhmSwitchConnect.firstTimeSlotNum,
         oamsCfgGrhmSwitchConnect.secondE1Num, oamsCfgGrhmSwitchConnect.secondTimeSlotNum);

   cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
         ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
   free(mccLinkResourceDbPtr);
}

/******************************* Function  Header*****************************
  Function Name : sendSwitchDisconnectReqToGrhm()
Parameters    : LinkTableApi *linkTablePtr 
Return type   : I_Bool
Purpose       : Send Switch disconnect request to GRHM 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool sendSwitchDisconnectReqToGrhm(LinkTableApi *linkTablePtr)
{
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;

   LOG_PRINT(LOG_INFO,"e1Num:%d, timeslot:%d",linkTablePtr->e1Num, linkTablePtr->timeSlot);
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(linkTablePtr->e1Num, 
      linkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"getMccLinkResourceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      sendStackProcRespToCm();
      return FALSE;
   }

   gStackObject.mccTrunkNum = mccLinkResourceDbPtr->mccTrunkNum; 
   gStackObject.mccTrunkTs  = mccLinkResourceDbPtr->mccTrunkTs;
   gStackObject.cardNum     = mccLinkResourceDbPtr->cardNum;

   LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_GRHM_SWITCH_DISCONNECT..");
   oamsCfgGrhmSwitchDisconnect.firstE1Num = linkTablePtr->e1Num;
   oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = linkTablePtr->timeSlot;
   oamsCfgGrhmSwitchDisconnect.secondE1Num = mccLinkResourceDbPtr->mccTrunkNum;
   oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = mccLinkResourceDbPtr->mccTrunkTs;
   LOG_PRINT(LOG_INFO,"oamsCfgGrhmSwitchDisconnect : First E1 : %d, \
         First Ts : %d, SecE1 : %d, SecTs : %d",
         oamsCfgGrhmSwitchDisconnect.firstE1Num, oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum, 
         oamsCfgGrhmSwitchDisconnect.secondE1Num, oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum);

   cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchDisconnect),
         ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
   free(mccLinkResourceDbPtr);
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : linkLockUnlockScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles Link Lock/Unlock response from SCM 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void linkLockUnlockScmRespHandler()
{
   I_U32 e1Num;   
   I_U32 tsNum;   
   e1Num = (gMsgSentForE1TSNum >> 16);
   tsNum = (gMsgSentForE1TSNum & 0x00ff);
   gMsgSentForE1TSNum = 0xff;
   LinkTableApi *linkTableDbPtr = NULL; 
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (getLinkTableUsingE1Ts(e1Num, tsNum, &linkTableDbPtr) != CLIB_SUCCESS) 
      {
         LOG_PRINT(LOG_MAJOR, "No entry exists in Link Table for Received e1Num: %d timeSlot: %d",e1Num, tsNum);
         return;
      }

      if ( gE1TimeslotData[e1Num][tsNum].e1TimeslotState== unlockInProgress)  
      {
         sendLinkUnlockAlarm(linkTableDbPtr);
      }
      else if  ( gE1TimeslotData[e1Num][tsNum].e1TimeslotState == lockInProgress)
      {
         sendLinkLockAlarm(linkTableDbPtr);
      }
      else
      {
         LOG_PRINT(LOG_MAJOR," No Match found for Link object state");   
      }           
      free(linkTableDbPtr); 
   }  
   else
   {
      LOG_PRINT(LOG_MAJOR,"Received Error from SCM(error: %d)",ScmOamRespPtr->erro_code);

      if ( gE1TimeslotData[e1Num][tsNum].e1TimeslotState== unlockInProgress)  
      {
         gE1TimeslotData[e1Num][tsNum].e1TimeslotState = locked; 
      }
      else if  ( gE1TimeslotData[e1Num][tsNum].e1TimeslotState == lockInProgress)
      {
         gE1TimeslotData[e1Num][tsNum].e1TimeslotState = unlocked; 
      }
   }
   resetStackObject();
}

/******************************* Function  Header*****************************
  Function Name : aspLockUnlockHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles Asp Lock/Unlock response from SCM 
Other Note    : Added For IP_BSC_STACK 
 *****************************************************************************/
I_Void aspLockUnlockHandler()
{
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering aspLockUnlockHandler()");
   I_U8 flag = I_FALSE;
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)gStoredMsgBufPtr;
      if(ScmOamRespPtr->scmhdr.operation == SCM_UNLOCK)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In aspLockUnlockHandler: Going for UNLOCK update.. in DB");
         sigtranM3uaLAspConfigTableApi->adminState = UNLOCKED;
         flag = I_TRUE; 
      }
      if(ScmOamRespPtr->scmhdr.operation == SCM_LOCK)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In aspLockUnlockHandler: Going for LOCK update.. in DB");
         sigtranM3uaLAspConfigTableApi->adminState = LOCKED; 
         flag = I_TRUE; 
      }
      if(flag == I_TRUE)
      {
				if (updateSigtranM3uaLAspConfigTable(sigtranM3uaLAspConfigTableApi) != CLIB_SUCCESS)
				{
					 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In aspLockUnlockHandler: updateSigtranM3uaLAspConfigTable Failed..");
					 setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
				}
       /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
       setStatusAspLocal(sigtranM3uaLAspConfigTableApi->localAspId,(I_U16)ZERO,STK_RESPONSE);
       /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
       flag = I_FALSE;
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
   resetStackObject();
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting aspLockUnlockHandler()");
}

/******************************* Function  Header*****************************
  Function Name : addSs7RouteScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles response from SCM for addition in Ss7 Route
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void addSs7RouteScmRespHandler()
{
   Ss7RouteStatusTableApi ss7RouteStatus;
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      Ss7RouteTableApi *ss7RouteTablePtr = (Ss7RouteTableApi *)gStoredMsgBufPtr;
      if (insertSs7RouteTable(ss7RouteTablePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"In addRouteScmRespHandler: insertSs7RouteTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
      else
      {
         ss7RouteStatus.linksetID = ss7RouteTablePtr->linksetID;
         ss7RouteStatus.routeID = ss7RouteTablePtr->routeID;
         ss7RouteStatus.oprState = DISABLED;
         if (insertSs7RouteStatusTable(&ss7RouteStatus) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_CRITICAL,"In addRouteScmRespHandler: insertSs7RouteStatusTable Failed..");
         }
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
     // setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : modifySs7RouteScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles response from SCM for modification in Ss7 Route
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifySs7RouteScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      Ss7RouteTableApi *ss7RouteTablePtr = (Ss7RouteTableApi *)gStoredMsgBufPtr;
      if (updateSs7RouteTable(ss7RouteTablePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"modifySs7RouteScmRespHandler: updateSs7StackConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : modifyMtp3TimerScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : To handle response from SCM for Mtp3 Timer modification
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifyMtp3TimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateMtp3TimerTable((Mtp3TimerTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"In modifyMtp3TimerScmRespHandler: updateMtp3TimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : modifySccpTimerScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : To handle response from SCM for Sccp Timer modification
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifySccpTimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateSccpTimerTable((SccpTimerTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"In modifySccpTimerScmRespHandler: updateSccpTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
    //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : modifyBssapTimerScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : To handle response from SCM for Bssap Timer modification
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifyBssapTimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateBssapTimerTable((BssapTimerTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"In modifyBssapTimerScmRespHandler: updateBssapTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

/******************************* Function  Header*****************************
  Function Name : modifyLapdTimerScmRespHandler()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : To handle response from SCM for Lapd Timer modification
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void modifyLapdTimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateLapdTimerTable((LapdTimerTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"In modifyLapdTimerScmRespHandler: updateLapdTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
     // setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}

I_Void sendStackProcRespToCm()
{
   if (getFailCauseInStackObj() == CM_SUCCESS)
      cfgSendAckToCm();
   else 
      cfgSendNackToCm(getFailCauseInStackObj());
   resetStackObject();

   if (gStoredMsgBufPtr!=NULL)
   {
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr= NULL;
   }
}

/******************************* Function  Header*****************************
  Function Name : cfgSendStackMessage()
Parameters    : I_Void *bufPtr, I_U32 size, I_U16 msgType
Return type   : I_S32
Purpose       : To send the request towards OIL.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_S32 cfgSendStackMessage(I_Void *bufPtr, I_U32 size) 
{ 
   SysHdr   *sndPtr; 
   I_S16  sndMsgSize = 0; 

   LOG_PRINT(LOG_INFO,"Entering  cfgSendStackMessage...."); 
   if (bufPtr != NULL)  {
      sndMsgSize = size + sizeof(SysHdr); 
   }   
   else {
      LOG_PRINT(CRITICAL,"Input Msg pointer is Null");
      setFailCauseInStackObj(CM_ERR_MEMORY_FAILURE);
      return CFG_FAILURE;
   }   
   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL) 
   { 
      LOG_PRINT(LOG_CRITICAL,"CFG_SEND_ALLOC_FAIL"); 
      setFailCauseInStackObj(CM_ERR_MEMORY_FAILURE);      
      return CFG_FAILURE;  
   } 

   /* Fill the ScmHdr to be send to SCM */
   fillScmHdr(((ScmHdr *)bufPtr), size); 

   memset(sndPtr,0,sndMsgSize) ; 

   memcpy(((I_U8 *)sndPtr + sizeof(SysHdr)), (I_U8*)bufPtr, size); 

   sndPtr->msgType = OAMS_CFG_OIL_SCM_MSG_REQ; 
   sndPtr->src.entity = ENT_OAMS_CFG; 
   sndPtr->dest.entity = ENT_OAM_OIL; 

   LOG_PRINT(LOG_INFO,"MsgType = %d, SourceEntity = %d, DestEntity = %d", 
         sndPtr->msgType,sndPtr->src.entity,sndPtr->dest.entity); 
   LOG_PRINT(LOG_INFO,"AppId = %d, Operation = %d, Opcode = %d",
         ((ScmHdr *)bufPtr)->appid, ((ScmHdr *)bufPtr)->operation, ((ScmHdr *)bufPtr)->opcode);

   if (SendMsg(sndPtr, 1, sndMsgSize) < 0) 
   { 
      LOG_PRINT(LOG_CRITICAL,"CFG: cfgSendStackMessage() - msg sending failed"); 
      DalocMsgBuf((I_PVoid) sndPtr); 
      setFailCauseInStackObj(CM_ERR_SEND_MESSAGE_FAILS);   
      return(CFG_FAILURE); 
   }

   /* Start SCM_CFG_RESP_TIMER to await response from SCM*/
   if ( (getScmSubProcState() != OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG) &&  //06 Oct 2016 Gaurav Sinha 
        (getScmSubProcState() != OAM_SCM_LAPDTIMER_CONFIG)  )
   {
      LOG_PRINT(LOG_INFO,"Starting Timer.."); 
      cfgStartTimer("SCM_CONFIG"); 
   }
   return(CFG_SUCCESS); 
} /* cfgSendStackMessage */ 

/******************************* Function  Header*****************************
  Function Name : updateOrInsertLinkSetStatusTable()
Parameters    : I_U16 linkSetId,I_U32 status
Return type   : I_Void
Purpose       : To Update the Linkset Status if row is present in DB and 
insert a row if no row is present in DB.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void updateOrInsertLinkSetStatusTable(I_U16 linkSetId,I_U32 status)
{
   LinksetStatusTableApi linksetStatus;
   LinksetTableApi *linksetPtr = NULL;
   LinksetTableIndices linksetIndex;

   linksetIndex.linksetID = linkSetId;
   if (getLinksetTable(&linksetIndex,&linksetPtr) == CLIB_SUCCESS)      
   {
      free(linksetPtr);
      linksetStatus.linksetID = linkSetId;
      linksetStatus.oprState = status;
      if (updateLinksetStatusTable(&linksetStatus) != CLIB_SUCCESS)
      {
         if (insertLinksetStatusTable(&linksetStatus) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"insertLinksetStatusTable call Failed.."); 
            if( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) ||
                (gCurrentCardState == CARDSTATE_STANDBY) ||
                (gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS)  ) 
            {
               LOG_PRINT(DEBUG,"Storing LINKSET_OOS/INS as card is in AIP state");   
               gAipLinkSetAlarmData.flag = TRUE;
               gAipLinkSetAlarmData.linkSetId = linkSetId;
               gAipLinkSetAlarmData.oprState = status;
            }
         }
      }
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"Received LinkSet in Alarm does not exists in DB"); 
   }
}

/******************************* Function  Header*****************************
  Function Name : updateOrInsertLinkStatusTable()
Parameters    : I_U16 linkSetId,I_U16 linkId,I_U32 status 
Return type   : I_Void
Purpose       : To Update the Link Status if row is present in DB and 
insert a row if no row is present in DB.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void updateOrInsertLinkStatusTable(I_U16 linkSetId,I_U16 linkId,I_U32 status)
{
   LinkStatusTableApi linkStatus;
   LinkTableApi *linkPtr = NULL;
   LinkTableIndices linkIndex;
   I_U16 i =0;

   linkIndex.linksetID = linkSetId;
   linkIndex.linkId = linkId;
   if (getLinkTable(&linkIndex,&linkPtr) == CLIB_SUCCESS)      
   {
      free(linkPtr);
      linkStatus.linksetID = linkSetId;
      linkStatus.linkId = linkId;
      linkStatus.oprState = status;
      if (updateLinkStatusTable(&linkStatus) != CLIB_SUCCESS)
      {
         if (insertLinkStatusTable(&linkStatus) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"insertLinkStatusTable call Failed.."); 
            if( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) ||
                (gCurrentCardState == CARDSTATE_STANDBY) ||
                (gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS)  ) 
            {
               LOG_PRINT(DEBUG,"Storing LINK_OOS/INS as card is in AIP state");   
               for(i = 0; i< 8; i++)
               {
                 if(gAipLinkAlarmData[i].flag == TRUE)  
                 {
                    if( (gAipLinkAlarmData[i].linkSetId == linkSetId) &&
                        (gAipLinkAlarmData[i].linkId == linkId) ) 
                    {
                       gAipLinkAlarmData[i].oprState = status;
                       break; 
                    }
                    else
                    {
                        i++;
                    } 
                 } 
                 else
                 {
                    gAipLinkAlarmData[i].flag = TRUE;
                    gAipLinkAlarmData[i].linkSetId = linkSetId;
                    gAipLinkAlarmData[i].linkId = linkId;
                    gAipLinkAlarmData[i].oprState = status;
                    break;  
                 }
               }//for 
            }
         }
      }
   }
   else
   {
      LOG_PRINT(LOG_MAJOR,"Received Link in Alarm does not exists in DB"); 
   }
}

/******************************* Function  Header*****************************
  Function Name : updateOrInsertSs7RouteStatusTable()
Parameters    : I_U32 dpc,I_U32 status 
Return type   : I_Void
Purpose       : To Update the Ss7Route Status if row is present in DB and 
insert a row if no row is present in DB.
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void updateOrInsertSs7RouteStatusTable(I_U32 dpc,I_U32 status)
{
   Ss7RouteTableApi *ss7RoutePtr =NULL;
   Ss7RouteTableApi *tmpSs7RoutePtr =NULL;
   Ss7RouteStatusTableApi ss7RouteStatus;
   I_U32 outRows = 0, i;
   I_U16 outSize = 0;

   if (getallSs7RouteTable(&ss7RoutePtr,&outRows,&outSize) == CLIB_SUCCESS)
   {
      for (i = 0; i < outRows; i++)
      {
         tmpSs7RoutePtr = (Ss7RouteTableApi *)((I_U8*)ss7RoutePtr + (i *outSize));
         if (tmpSs7RoutePtr->dpc == dpc)
         {
            ss7RouteStatus.linksetID = tmpSs7RoutePtr->linksetID;
            ss7RouteStatus.routeID = tmpSs7RoutePtr->routeID;
            ss7RouteStatus.oprState = status;
            if (updateSs7RouteStatusTable(&ss7RouteStatus) != CLIB_SUCCESS)
            {
               if (insertSs7RouteStatusTable(&ss7RouteStatus) != CLIB_SUCCESS)
               {
                  LOG_PRINT(LOG_MAJOR,"insertSs7RouteStatusTable call Failed.."); 
                  if( (gCurrentCardState == CARDSTATE_ACTIVE_IN_PROGRESS) ||
                      (gCurrentCardState == CARDSTATE_STANDBY) ||
                      (gNextCardState == CARDSTATE_ACTIVE_IN_PROGRESS)  ) 
                  {
                     LOG_PRINT(DEBUG,"Storing RESUME/PAUSE as card is in AIP state");   
                     if(status == ENABLED)
                     {
                        gAipPauseRcvd = TRUE;
                        gAipResumeRcvd = FALSE;  
                     } 
                     else
                     {
                        gAipPauseRcvd = TRUE;  
                        gAipResumeRcvd = FALSE;
                     }   
                     gAipResumeRcvdPc = dpc; 
                  }
               }   
            }   
         }
      }
      free(ss7RoutePtr);
   }
   else
   {
      LOG_PRINT(LOG_MAJOR, "INIT : read getallSs7RouteTable() Failed");
   }
}

/******************************* Function  Header*****************************
  Function Name : updateStackTableStatus()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Handles alarms for Status updation 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void updateStackTableStatus()
{
   I_U32 outRows=0;
   I_U16 outSize=0;
   LinkTableApi *linkPtr=NULL;

   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   switch (recAlarmPtr->sysalarmId)
   {
      case ALARM_ID_BSC_SS7_DOWN: 
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_BSC_SS7_DOWN.."); 
         gStackStatus = SS7_STACK_DOWN; 
         break;             
      case ALARM_ID_BSC_SS7_UP: 
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_BSC_SS7_UP.."); 
         gStackStatus = SS7_STACK_UP;
         if ((gBssState == unlocked) || (gBssState == unlockInProgress))
         {
            gLinkMsgSentForBss = 0;
            /*Changes for R2.3.4 Starts */
            if(bssObjectSendLapdTimerConfigToScm() != I_TRUE)
            {
               if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
               {
                  if (gLinkMsgSentForBss != outRows)
                  {
                     if (checkAndSendLinkActivationRequest() != TRUE)
                        LOG_PRINT(LOG_INFO,"Link Activation cannot be send");
                  }
                  free(linkPtr);
               }
            }
            /*Changes for R2.3.4 Ends*/
         }
         break;          
      case ALARM_ID_MSC_LINKSET_OOS:   
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_MSC_LINKSET_OOS.."); 
         updateOrInsertLinkSetStatusTable(recAlarmPtr->key1,DISABLED);
         break;
      case ALARM_ID_MSC_LINKSET_INS:   
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_MSC_LINKSET_INS.."); 
         updateOrInsertLinkSetStatusTable(recAlarmPtr->key1,ENABLED);
         break;
      case ALARM_ID_MSC_LINK_OOS:   
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_MSC_LINK_OOS.."); 
         updateOrInsertLinkStatusTable(recAlarmPtr->key1,recAlarmPtr->key2,DISABLED);
         break;
      case ALARM_ID_MSC_LINK_INS:   
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_MSC_LINK_INS.."); 
         updateOrInsertLinkStatusTable(recAlarmPtr->key1,recAlarmPtr->key2,ENABLED);
         break;
      case ALARM_ID_DEST_UNAVAILABLE_MTP3_PAUSE:  
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_DEST_UNAVAILABLE_MTP3_PAUSE.."); 
         updateOrInsertSs7RouteStatusTable(recAlarmPtr->key1,DISABLED);
         break;
      case ALARM_ID_DEST_AVAILABLE_MTP3_RESUME:  
         LOG_PRINT(LOG_INFO,"Received ALARM_ID_DEST_AVAILABLE_MTP3_RESUME.."); 
         updateOrInsertSs7RouteStatusTable(recAlarmPtr->key1,ENABLED);
         break;
   }
}

#if 0
/******************************* Function  Header*****************************
  Function Name : sendLinkActivationRequest()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : For sending Link activation request to SCM for all unlock links 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendLinkActivationRequest()
{
   LinkTableApi       *linkPtr=NULL;
   LinkTableApi       *tmpLinkPtr=NULL;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_U8 i=0;

   if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO, "Number of rows returned by API getallLinkTable = %d", outRows);
      for (i = 0; i < outRows; i++)
      {
         tmpLinkPtr = (LinkTableApi *)((I_U8*)linkPtr + (i *outSize));

         if (tmpLinkPtr->adminState == UNLOCKED && 
               gE1Data[tmpLinkPtr->e1Num].e1State == unlocked)
         {
            OamScmLinkAdminState linkConfig;
            linkConfig.linkId = tmpLinkPtr->linkId; 
            linkConfig.linkSetId = tmpLinkPtr->linksetID;
            linkConfig.adminState = UNLOCKED;  
            setStackObject(ALARM_ID_MSC_SS7_UP, SCM_UNLOCK, OAM_SCM_LINK_ADMIN_CONFIG);
            LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LINK_ADMIN_CONFIG to Oil..");
            if (cfgSendStackMessage((I_Void *)&linkConfig, sizeof(linkConfig)) != CFG_SUCCESS)
            {
               free(linkPtr);
               return;
            }
         }
      }
      free(linkPtr);
   }
   else 
      LOG_PRINT(LOG_INFO, "INIT : read getallLinkTable() Failed");
}
#endif

/**********************************Deletion of Stack Objects Handling Start*****************************
 *Following are Stack Object which could be deleted by Operator
 * -Ss7StackConfig Table
 * -AifInterface Table
 * -Trunk Table
 * -Cic Table
 * -LinkSet Table
 * -Ss7Route Table
 * -Link Table
 * Please note that CS4.0 does not support all the Table configuration from Operator.
 * Following are the Tables which are internally maintain by BSC
 * -TrunkGroup Table
 * -Trunk Table

 * Hierarchy of the Tables. 
 * Ss7StackConfig Table -> Interface Table -> LinkSet Table -> Link Table
 * Ss7StackConfig Table -> Interface Table -> Ss7Route Table
 * Ss7StackConfig Table -> Interface Table -> TrunkGroup Table -> Trunk Table -> Cic Table
 * Based on the Hierarchy first the child table should be deleted and then only the parent table
 * could be deleted.

 * Deletion Order
 * 1. Deletion of Trunk & Deletion of CIC
 * 2. Deletion of Link
 * 3. Deletion of Ss7Route
 * 4. Deletion of Interface (LinkSet & TrunkGroup)
 * 5. Deletion of Ss7StackConfig Table
 */

#if 0 /* AbisInterface is removed */
/******************************* Function  Header*****************************
  Function Name : isDelAbisInterfaceTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete ABISINTERFACE Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelAbisInterfaceTableAllowed(I_Void)
{
   AbisInterfaceTableApi *AbisInterfaceTableApiPtr;
   AbisInterfaceTableIndices *KeysPtr = (AbisInterfaceTableIndices *)( ( (sCmMsg *) gCfgMsgBuf )+ 1);

   if (CLIB_SUCCESS != getAbisInterfaceTable(  KeysPtr, &AbisInterfaceTableApiPtr) ) {
      LOG_PRINT(LOG_INFO, "AbisInterface Table is empty");
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;    
   }

   /* BIC should be already deleted for AbisInterface */
   if (INVALID_BIC != AbisInterfaceTableApiPtr->bicId) {
      LOG_PRINT(LOG_DEBUG, "Child Object BIC[0x%X] is not deleted",AbisInterfaceTableApiPtr->bicId);
      setFailCauseInStackObj(CM_ERR_CHILD_OBJ_EXISTS);  
      free(AbisInterfaceTableApiPtr);
      return FALSE;
   }

   free(AbisInterfaceTableApiPtr);
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delAbisInterfaceTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete ABISINTERFACE Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delAbisInterfaceTableHandler(I_Void)
{
   if ( isDelAbisInterfaceTableAllowed() ) {
      if ( deleteAbisInterfaceTable( (AbisInterfaceTableIndices *)( ( (sCmMsg *) gCfgMsgBuf )+ 1)) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"deleteAbisInterfaceTable Failed inside delAbisInterfaceTableHandler");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);  
      }    
   }  
   sendStackProcRespToCm();    
}
#endif

/******************************* Function  Header*****************************
  Function Name : isDelSs7StackTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete SS7 Stack Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelSs7StackTableAllowed(I_Void)
{
   Ss7StackConfigTableApi *Ss7StackConfigTableApiDbPtr = PNULL;
   Ss7StackConfigTableIndices *KeysPtr = (Ss7StackConfigTableIndices *)( ( (sCmMsg *) gCfgMsgBuf )+ 1);
   AifInterfaceTableApi  *AifInterfaceTableDbPtr;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO; 

   /* Check BSS is locked otherwise sends FALSE*/
   if ( ! isBssLocked() ) {
      LOG_PRINT(LOG_INFO, "Bss is Unlocked");
      setFailCauseInStackObj(CM_ERR_BSS_NOT_LOCKED);
      return FALSE;
   }

   /* Check that DB has entry in Ss7StackTable (This table has only one Row) */
   if ( CLIB_SUCCESS != getSs7StackConfigTable( KeysPtr, &Ss7StackConfigTableApiDbPtr) ) {
      LOG_PRINT(LOG_INFO, "Ss7Stack Table is empty");
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;
   }  

   /* Check that DB does not have entry for interface Talble */
   if ( CLIB_SUCCESS == getallAifInterfaceTable(&AifInterfaceTableDbPtr, &outCount, &outSize)) {
      LOG_PRINT(LOG_DEBUG, "Child Object AifInterface Table is not empty");
      setFailCauseInStackObj(CM_ERR_AIFINTERFACE_OBJ_EXISTS);
      free(Ss7StackConfigTableApiDbPtr);
      free(AifInterfaceTableDbPtr);
      return FALSE;
   }  

   // Note: free of AifInterfaceTableDbPtr is not required as the DB call must fails to reach control here
   if ( ! storeReceivedMsgBuffer(Ss7StackConfigTableApiDbPtr, sizeof(Ss7StackConfigTableApi)) ) {
      free(Ss7StackConfigTableApiDbPtr);
      return FALSE;

   }

   free(Ss7StackConfigTableApiDbPtr);
   return TRUE;
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmSs7StackConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmSs7StackConfig(I_Void)
{
   OamScmSs7StackConfig Ss7StackConfig;
   Ss7StackConfigTableApi *Ss7StackConfigTableApiPtr = (Ss7StackConfigTableApi*)gStoredMsgBufPtr;

   Ss7StackConfig.family = Ss7StackConfigTableApiPtr->sksCommonfamily; 
   Ss7StackConfig.selfPointCode = Ss7StackConfigTableApiPtr->sksCommonopc; 
   Ss7StackConfig.alarmLevel = Ss7StackConfigTableApiPtr->alarmLevel;  

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_SS7_STACK_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&Ss7StackConfig, sizeof(Ss7StackConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delSs7StackTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete SS7 Stack Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delSs7StackTableHandler(I_Void)
{
   if ( ! isDelSs7StackTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() ); 
      return;
   }

   setStackObject(BSC_API_DEL_SS7STACKCONFIGTABLE, SCM_DELETE, OAM_SCM_SS7_STACK_CONFIG);

   if ( ! fillAndSendOamScmSs7StackConfig() ) {
      sendStackProcRespToCm();
      return;      
   }
}

/******************************* Function  Header*****************************
  Function Name : delSs7StackScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Ss7 Stack Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delSs7StackScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSs7StackConfigTable((Ss7StackConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL," In deleteSs7StackConfigTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }  
   else {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();  
}

/******************************* Function  Header*****************************
  Function Name : Ss7StackScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Ss7 Stack Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void Ss7StackScmRespHandler(I_Void)
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
         addSs7StackScmRespHandler();         
         break;
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
         modifySs7StackScmRespHandler();         
         break;
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"Received SCM_DELETE..");
         delSs7StackScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}


/******************************* Function  Header*****************************
  Function Name : isDelAifInterfaceTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete AifInterface Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelAifInterfaceTableAllowed(I_Void)
{
   AifInterfaceTableApi *AifInterfaceTablePtr = PNULL;
   AifInterfaceTableIndices *KeysPtr = (AifInterfaceTableIndices *) ( ( (sCmMsg *) gCfgMsgBuf )+ 1);
   LinksetTableApi      *linkSetTableDbPtr;
   AiftrunkTableApi *trunkTableDbPtr = NULL; 
   I_U32 i = ZERO;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;


   /* Check that DB does have entry for AifInterface Talble */
   if ( CLIB_SUCCESS != getAifInterfaceTable( KeysPtr, &AifInterfaceTablePtr) ) {
      LOG_PRINT(LOG_INFO, "AifInterface Table is empty");
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;    
   }  

   /* Check that DB does not have entry LinkSet associated with this AifInterface */
   if ( CLIB_SUCCESS == getallLinksetTable(&linkSetTableDbPtr, &outCount, &outSize)) {
      /* Check that there are entries for the associated AifInterface */
      for (i=0; i < outCount; i++) {
         if ( ((LinksetTableApi *)((I_U8 *)linkSetTableDbPtr + outSize*i))->interfaceId == 
               AifInterfaceTablePtr->interfaceId )  {
            LOG_PRINT(LOG_DEBUG, "Child Object LinkSet Table is not empty");
            setFailCauseInStackObj(CM_ERR_LINKSET_OBJ_EXISTS);
            break;
         }  
      }
      free(linkSetTableDbPtr);
      if (i < outCount) {
         free(AifInterfaceTablePtr);
         return FALSE;
      }  
   } 

   /* Since when the interface is deleted TrunkGroup is also deleted by CFG internally 
    ** But TrunkGroup has dependency that Trunk Table should also be empty 
    ** So AifInterface Table delete also require that Trunk Table is deleted */ 
   if ( CLIB_SUCCESS == getallAiftrunkTable(&trunkTableDbPtr, &outCount, &outSize)) {
      for (i=0; i < outCount; i++) {
         if ( ( ((AiftrunkTableApi *)((I_U8 *)trunkTableDbPtr + outSize*i))->tgpId == DEFAULT_TGPID) 
               && 
               ( ((AiftrunkTableApi *)((I_U8 *)trunkTableDbPtr + outSize*i))->interfaceId == 
                 AifInterfaceTablePtr->interfaceId )
            ) {
            LOG_PRINT(LOG_DEBUG, "Child Object Trunk Tabke is not empty");
            setFailCauseInStackObj(CM_ERR_TRUNK_OBJ_EXISTS);
            break;
         }  
      }  
      free(trunkTableDbPtr);
      if (i < outCount ) {
         free(AifInterfaceTablePtr);
         return FALSE;
      }
   } 

   if ( ! storeReceivedMsgBuffer(AifInterfaceTablePtr, sizeof(AifInterfaceTableApi)) ) {
      free(AifInterfaceTablePtr);
      return FALSE;
   }

   free(AifInterfaceTablePtr);
   return TRUE;
}


/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmInterfaceConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmInterfaceConfig(I_Void)
{
   AifInterfaceTableApi *AifInterfaceTablePtr = ( AifInterfaceTableApi *)gStoredMsgBufPtr;
   OamScmInterfaceConfig InterfaceConfig ;

   InterfaceConfig.interfaceType  = AifInterfaceTablePtr->interfaceType; 
   InterfaceConfig.interfaceId    = AifInterfaceTablePtr->interfaceId; 
   InterfaceConfig.pointCode      = AifInterfaceTablePtr->dpc;  

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_INTERFACE_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&InterfaceConfig, sizeof(InterfaceConfig) ) != CFG_SUCCESS ){
      return FALSE;
   } 
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delAifInterfaceTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete AifInterface Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delAifInterfaceTableHandler(I_Void)
{

   if ( ! isDelAifInterfaceTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() ); 
      return;
   }

   setStackObject(BSC_API_DEL_AIFINTERFACETABLE, SCM_DELETE, OAM_SCM_INTERFACE_CONFIG);

   if ( ! fillAndSendOamScmInterfaceConfig() ) {
      sendStackProcRespToCm();
      return;      
   }
}

/******************************* Function  Header*****************************
  Function Name : delAifInterfaceScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for AifInetrface Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delAifInterfaceScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
   TrunkGroupTableIndices Keys;

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if ( CLIB_SUCCESS != deleteAifInterfaceTable((AifInterfaceTableIndices *)gStoredMsgBufPtr) ) {
         LOG_PRINT(LOG_CRITICAL," In deleteAifInterfaceTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
      /*Delete the Trunk Group internally */ 
      Keys.interfaceId = ((AifInterfaceTableApi *)gStoredMsgBufPtr)->interfaceId;
      Keys.tgpId = DEFAULT_TGPID; 
      if ( CLIB_SUCCESS != deleteTrunkGroupTable(&Keys) ) {
         LOG_PRINT(LOG_CRITICAL," In deleteTrunkGroupTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }      
   }  
   else {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();  
   return;
}

/******************************* Function  Header*****************************
  Function Name : AifInterfaceScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for AifInterface Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void AifInterfaceScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
         addInterfaceScmRespHandler();
         break;
      case SCM_DELETE:
         delAifInterfaceScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : isDelLinkSetTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete LinkSet Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelLinkSetTableAllowed(I_Void)
{
   LinksetTableApi *LinkSetTablePtr = PNULL;
   LinksetTableIndices *KeysPtr = (LinksetTableIndices *)  ( ( (sCmMsg *) gCfgMsgBuf )+ 1);
   LinkTableApi *linkTablePtr = PNULL;
   I_U32 outCount = ZERO;
   I_U16 outSize = ZERO;
   I_U32 i = ZERO;

   /* Check that DB does have entry for LinkSet Talble */
   if ( CLIB_SUCCESS != getLinksetTable( KeysPtr, &LinkSetTablePtr) ) {
      LOG_PRINT(LOG_INFO, "LinksetTable is empty");
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;    
   }  

   /* Check that DB does not have entry in Link Table associated with this linksetID */
   if ( CLIB_SUCCESS == getallLinkTable(&linkTablePtr, &outCount, &outSize)) {
      for (i=0; i < outCount; i++) {
         if ( ((LinkTableApi *)((I_U8 *)linkTablePtr + outSize*i))->linksetID == LinkSetTablePtr->linksetID ) {
            LOG_PRINT(LOG_DEBUG, "Child Object LinkTable has associated entry");
            setFailCauseInStackObj(CM_ERR_LINK_OBJ_EXISTS);
            break;
         }   
      }
      free(linkTablePtr);
      if (i < outCount ) {
         free(LinkSetTablePtr);
         return FALSE;
      }
   } 

   if ( ! storeReceivedMsgBuffer(LinkSetTablePtr, sizeof(LinksetTableApi)) ) {
      free(LinkSetTablePtr);
      return FALSE;
   }
   free(LinkSetTablePtr);

   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmLinkSetConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmLinkSetConfig(I_Void)
{
   LinksetTableApi *LinkSetTablePtr = ( LinksetTableApi *)gStoredMsgBufPtr;
   OamScmLinkSetConfig LinkSetConfig ;

   LinkSetConfig.linkSetId           = LinkSetTablePtr->linksetID; 
   LinkSetConfig.adjacentPointCode   = LinkSetTablePtr->adjacentPointCode; 
   LinkSetConfig.networkIndicator    = LinkSetTablePtr->networkIndicator;  

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LINKSET_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&LinkSetConfig, sizeof(LinkSetConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delLinkSetTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete Link Set Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delLinkSetTableHandler(I_Void)
{

   if ( ! isDelLinkSetTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() ); 
      return;
   }

   setStackObject(BSC_API_DEL_LINKSETTABLE, SCM_DELETE, OAM_SCM_LINKSET_CONFIG);

   if ( ! fillAndSendOamScmLinkSetConfig() ) {
      sendStackProcRespToCm();
      return;      
   }
}

/******************************* Function  Header*****************************
  Function Name : delLinkSetScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Link Set Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delLinkSetScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteLinksetTable((LinksetTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL," In deleteLinksetTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }            
      else
      {
         if (deleteLinksetStatusTable((LinksetStatusTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_INFO,"Row not present in LinkSetStatus Table");
         }
      }
   }  
   else {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();  
   return;
}

/******************************* Function  Header*****************************
  Function Name : LinkSetScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Link Set Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void LinkSetScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
         addLinkSetScmRespHandler();
         break;
      case SCM_DELETE:
         LOG_PRINT(LOG_INFO,"Received SCM_DELETE..");
         delLinkSetScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : isDelLinkTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete Link Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelLinkTableAllowed(I_Void)
{
   LinkTableApi *LinkTablePtr = PNULL;
   LinkTableIndices *KeysPtr = (LinkTableIndices *)( (sCmMsg *)gCfgMsgBuf + 1);

	 LinkTableApi* receivedMsgPtr = (LinkTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof(sCmMsg));
   I_U32 cardOprState = 0;	
   /* Check that DB does have entry for LinkSet Talble */
   if ( CLIB_SUCCESS != getLinkTable(KeysPtr, &LinkTablePtr)) {
      LOG_PRINT(LOG_INFO, "Link Table is empty");
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;    
   }  
   /* FIXED MANTIS 9568 Start*/
   if(CLIB_SUCCESS == getStateForSlotIdIccTable(receivedMsgPtr->cardNum,&cardOprState) )
    {
      if (cardOprState != CARDSTATE_ACTIVE && cardOprState != CARDSTATE_STANDBY)
      {
         LOG_PRINT(LOG_DEBUG, "Card State is invalid for link configuration.");
         cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
         return;
      }
   }
   /* FIXED MANTIS 9568 End*/

   /* Check that the Link is in Locked State */
   if ( LOCKED != LinkTablePtr->adminState ) { 
      LOG_PRINT(LOG_INFO,"Link should be Admin Locked");
      setFailCauseInStackObj(CM_ERR_LINK_NOT_LOCKED);    
      free(LinkTablePtr);
      return FALSE;
   }

   if ( ! storeReceivedMsgBuffer(LinkTablePtr, sizeof(LinkTableApi)) ) {
      free(LinkTablePtr);
      return FALSE;
   }

   free(LinkTablePtr);
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmLinkConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmLinkConfig(I_Void)
{
   LinkTableApi *LinkTablePtr = ( LinkTableApi *)gStoredMsgBufPtr;
   OamScmLinkConfig LinkConfig ;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(LinkTablePtr->e1Num, 
            LinkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"getMccLinkResourceTable call is getting failed..");
      //setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
			/*Above condition check commented for cloud */
      LOG_PRINT(LOG_MAJOR,"DEL Operation not allowd for LINKSET/LINK tables .. ");
      setFailCauseInStackObj(CM_ERR_DEL_OBJ_NOT_ALLOWED);
/*Changed for cloud for throwing proper errCode to OMC for Del of LinkSet/Link table 13 Jan 2016*/
      return FALSE;
   }

   LinkConfig.linkId      = LinkTablePtr->linkId; 
   LinkConfig.linkSetId   = LinkTablePtr->linksetID; 
   LinkConfig.trunkNum    = mccLinkResourceDbPtr->mccTrunkNum;  
   LinkConfig.timeSlot    = mccLinkResourceDbPtr->mccTrunkTs; 
   LinkConfig.cardNum     = LinkTablePtr->cardNum; 
   LinkConfig.crcFlag     = LinkTablePtr->crcFlag;    

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LINK_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&LinkConfig, sizeof(LinkConfig) ) != CFG_SUCCESS ){
      return FALSE;
   } 
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delLinkTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete Link Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delLinkTableHandler(I_Void)
{

   if ( ! isDelLinkTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() ); 
      return;
   }

   setStackObject(BSC_API_DEL_LINKTABLE, SCM_DELETE, OAM_SCM_LINK_CONFIG);

   if ( ! fillAndSendOamScmLinkConfig() ) {
      sendStackProcRespToCm();
      return;      
   }
}

/******************************* Function  Header*****************************
  Function Name : delLinkScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Link Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delLinkScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
   I_U32 cardOprState = 0;

   LinkTableApi *linkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {

      if (getScmOperation() == BSC_API_DEL_LINKTABLE)
      {
         setFailCauseInStackObj(CM_SUCCESS);

         if (getStateForSlotIdIccTable(linkTablePtr->cardNum,&cardOprState) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_DEBUG, "Received cardNum does not exists in iccCardInfo Table");
         }

         if (updateLinkStatusInMccLinkTable(linkTablePtr->e1Num,linkTablePtr->timeSlot,
                  SYS_TS_FREE) != CLIB_SUCCESS)
         {
            LOG_PRINT(LOG_MAJOR,"updateLinkStatusInMccLinkResourceTable Failed..");
            setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
         } 

         if(cardOprState == CARDSTATE_ACTIVE)
         {
            if (!(sendSwitchDisconnectReqToGrhm(linkTablePtr)))
            {
               return;
            }
         } 
         else if(cardOprState == CARDSTATE_STANDBY)
         {
            sendPeerSwitchDisconnectReqToGrhm(linkTablePtr);
            sendSwitchReqToPeerCfg(linkTablePtr->e1Num,linkTablePtr->timeSlot,CFG_BREAK_SWITCH,CFG_SWITCH_LINK_ADD_DEL); 
            sendBpmSwitchInfoForPeerCard(linkTablePtr->cardNum);
         }


         if (deleteLinkTable((LinkTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) 
         { 
            LOG_PRINT(LOG_CRITICAL," In deleteLinkTable: Failed");
            setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
         }           
         else 
         { 
            if (deleteLinkStatusTable((LinkStatusTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) 
            { 
               LOG_PRINT(LOG_INFO,"Row not Present in LinkStatus Table");
            }           
         }           
      }
      modifyExtTrunkNumTsPeerTrunkNumTsInMccLink(INVALID_E1,INVALID_TS,INVALID_E1,INVALID_TS);
   }  
   else 
   {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();  
   return;
}

/******************************* Function  Header*****************************
  Function Name : LinkScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Link Set Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void LinkScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
         addLinkScmRespHandler();
         break;
      case SCM_DELETE:
         LOG_PRINT(LOG_INFO,"Received SCM_DELETE..");
         delLinkScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : AreAllCICsLockedOnGivenE1Num()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if all the Cic on Givne E1 are locked or not
TRUE is returned if all the Cic are in locked state.
FALSE is returned if any of the Cic is unlocked 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool AreAllCICsLockedOnGivenE1Num(I_U32 e1Num)
{
   CicTableApi *CicTableApiPtr = PNULL;
   I_U32 outCount = ZERO;
   I_U16 outSize  = ZERO;
   I_U8  timeSlot = ZERO;
   I_U32 i        = ZERO;

   if(CLIB_SUCCESS ==  getCicListUsingE1Num(e1Num, &CicTableApiPtr, &outCount, &outSize)) {
      for (i=0; i < outCount; i++) {
         timeSlot = ((CicTableApi *)((I_U8 *)CicTableApiPtr + i*outSize))->timeSlot;
         if ( gE1TimeslotData[e1Num][timeSlot].e1TimeslotState != locked) {
            free(CicTableApiPtr);
            return FALSE;
         }
      }
   }
   if (CicTableApiPtr) {
      free(CicTableApiPtr);
   }
   return TRUE;
}
/******************************* Function  Header*****************************
  Function Name : isDelTrunkTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete Link Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelTrunkTableAllowed(I_Void)
{
   AiftrunkTableApi *AiftrunkTablePtr = PNULL;
/*Changes R2.5 Aricent -- Start*/
   NsvcTableApi *nsvcTableApiPtr = NULL;
   NsvcTableApi *tmpNsvcTableApiPtr = NULL;
   I_U32 outCount, i;
   I_U16 outSize;
/*Changes R2.5 Aricent -- End*/
   AiftrunkTableIndices *KeysPtr = (AiftrunkTableIndices *)( (sCmMsg *)gCfgMsgBuf + 1);

   /* Check that DB does have entry for LinkSet Talble */
   if ( CLIB_SUCCESS != getAiftrunkTable(KeysPtr, &AiftrunkTablePtr)) {
      LOG_PRINT(LOG_INFO, "Entry does not exits in Trunk Table for e1Num: %d", KeysPtr->e1Num);
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;    
   }  
   /* Check that all the configured CIC's on this E1 are in locked state */
   if ( ! AreAllCICsLockedOnGivenE1Num(KeysPtr->e1Num) ) {
      LOG_PRINT(LOG_INFO, "All CICs are not LOCKED of E1 : %d",KeysPtr->e1Num);
      setFailCauseInStackObj(CM_ERR_TRUNK_CICS_NOT_LOCKED);    
      free(AiftrunkTablePtr);
      return FALSE;
   }

/*Changes R2.5 Aricent -- Start*/
   if(CLIB_SUCCESS == getNsvcsForE1Id(KeysPtr->e1Num, &nsvcTableApiPtr, &outCount, &outSize))
   {
      for(i = 0; i < outCount; i++)
      {
         tmpNsvcTableApiPtr = (NsvcTableApi*)(((I_U8*)nsvcTableApiPtr + i * sizeof(NsvcTableApi)));
         if(tmpNsvcTableApiPtr->adminState != LOCKED)
         {
             LOG_PRINT(LOG_INFO, "NSVC not Locked for E1Id: %d", KeysPtr->e1Num);
             setFailCauseInStackObj(CM_ERR_TRUNK_NSVCS_NOT_LOCKED);
             free(AiftrunkTablePtr);
             free(nsvcTableApiPtr);
             return FALSE;
         }
      }
   }
/*Changes R2.5 Aricent -- End*/
   if ( ! storeReceivedMsgBuffer(AiftrunkTablePtr, sizeof(AiftrunkTableApi)) ) {
      free(AiftrunkTablePtr);
      return FALSE;
   }

   free(AiftrunkTablePtr);
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmTrunkCicConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmTrunkCicConfig(I_Void)
{
   AiftrunkTableApi *AiftrunkTablePtr = ( AiftrunkTableApi *)gStoredMsgBufPtr;

   /* Retreive Dest Point code from AifInterface Table */
   AifInterfaceTableApi  *AifInterfaceTableDbPtr;
   AifInterfaceTableIndices Keys;
   Keys.interfaceId = AiftrunkTablePtr->interfaceId;
   if(CLIB_SUCCESS != getAifInterfaceTable(&Keys, &AifInterfaceTableDbPtr))
   {
      LOG_PRINT(LOG_CRITICAL,"getAifInterfaceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      return FALSE;
   }

   OamScmTrunkCicConfig TrunkCicConfig ;

   TrunkCicConfig.interfaceType      = AifInterfaceTableDbPtr->interfaceType; 
   TrunkCicConfig.interfaceId        = AiftrunkTablePtr->interfaceId; 
   TrunkCicConfig.pointCode          = AifInterfaceTableDbPtr->dpc;  
   TrunkCicConfig.startCic           = AiftrunkTablePtr->startCic; 
   TrunkCicConfig.endCic             = AiftrunkTablePtr->endCic;    

   free(AifInterfaceTableDbPtr); 
   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_TRUNK_CIC_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&TrunkCicConfig, sizeof(TrunkCicConfig) ) != CFG_SUCCESS ){
      return FALSE;
   } 
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delTrunkTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete Link Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delTrunkTableHandler(I_Void)
{

   if ( ! isDelTrunkTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() ); 
      return;
   }

   setStackObject(BSC_API_DEL_AIFTRUNKTABLE, SCM_DELETE, OAM_SCM_TRUNK_CIC_CONFIG);

   if ( ! fillAndSendOamScmTrunkCicConfig() ) {
      sendStackProcRespToCm();
      return;      
   }
}

/******************************* Function  Header*****************************
  Function Name : delTrunkScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from Trunk Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delTrunkScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
   AiftrunkTableApi *trunkTablePtr = (AiftrunkTableApi *)gStoredMsgBufPtr;
   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteAiftrunkTable((AiftrunkTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL," In deleteAiftrunkTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }  
      if ( deleteCicListUsingRange(trunkTablePtr->startCic,trunkTablePtr->endCic) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL," In deleteCicFromCicTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }        
   }  
   else {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();  
   return;
}

/******************************* Function  Header*****************************
  Function Name : TrunkScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Trunk Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void TrunkScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
         addTrunkScmRespHandler();
         break;
      case SCM_DELETE:
         LOG_PRINT(LOG_INFO,"Received SCM_DELETE..");
         delTrunkScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}


/******************************* Function  Header*****************************
  Function Name : AreAllLinksLockedOnGivenlinksetID()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if all the associated links for linkSetIf are in locked state
Other Note    : Added For BSC CS4.0
 **************************************************************************/
I_Bool AreAllLinksLockedOnGivenlinksetID(I_U16 linksetID)
{
   LinkTableApi *linkTableDataPtr;
   I_U32 outCount = ZERO;
   I_U16 outSize  = ZERO;
   I_U32 e1Num    = ZERO;
   I_U8  timeSlot = ZERO;
   I_U32 i        = ZERO;

   if ( CLIB_SUCCESS == getLinkListUsingLinksetID(linksetID, &linkTableDataPtr, &outCount,&outSize) ) {
      for (i=0; i < outCount; i++) {
         e1Num    = ((LinkTableApi *)((I_U8 *)linkTableDataPtr + i*outSize))->e1Num;
         timeSlot = ((LinkTableApi *)((I_U8 *)linkTableDataPtr + i*outSize))->timeSlot;
         if ( gE1TimeslotData[e1Num][timeSlot].e1TimeslotState != locked  ) {
            free(linkTableDataPtr);
            return FALSE;
         }  
      }
      free(linkTableDataPtr);
   }
   return TRUE;
}
/******************************* Function  Header*****************************
  Function Name : isDelSs7RouteTableAllowed()
Parameters    : None
Return type   : I_Bool
Purpose       : Check if delete Ss7 Route Table request is allowed towards SCM
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool isDelSs7RouteTableAllowed(I_Void)
{
   Ss7RouteTableApi *Ss7RouteTableApiPtr = PNULL;
   Ss7RouteTableIndices *KeysPtr = (Ss7RouteTableIndices *)( (sCmMsg *)gCfgMsgBuf + 1);

   /* Check that DB does have entry for LinkSet Talble */
   if ( CLIB_SUCCESS != getSs7RouteTable(KeysPtr, &Ss7RouteTableApiPtr)) {
      LOG_PRINT(LOG_INFO, "Entry does not exits SS7 Route Table for routeId [%d]",KeysPtr->routeID);
      setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
      return FALSE;    
   }  

   /* Check that all the Links in Link Table for the associated linksetID are locked state */
   if ( ! AreAllLinksLockedOnGivenlinksetID(Ss7RouteTableApiPtr->linksetID) ) {
      LOG_PRINT(LOG_INFO, "All Links for linksetID[%d] are not LOCKED",Ss7RouteTableApiPtr->linksetID);
      setFailCauseInStackObj(CM_ERR_LINK_NOT_LOCKED);    
      free(Ss7RouteTableApiPtr);
      return FALSE;
   }

   if ( ! storeReceivedMsgBuffer(Ss7RouteTableApiPtr, sizeof(Ss7RouteTableApi)) ) {
      free(Ss7RouteTableApiPtr);
      return FALSE;
   }

   free(Ss7RouteTableApiPtr);
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : fillAndSendOamScmSs7RouteConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Bool fillAndSendOamScmSs7RouteConfig(I_Void)
{
   Ss7RouteTableApi *Ss7RouteTablePtr = ( Ss7RouteTableApi *)gStoredMsgBufPtr;
   OamScmSs7RouteConfig Ss7RouteConfig ;

   Ss7RouteConfig.destinationPointCode      = Ss7RouteTablePtr->dpc; 
   Ss7RouteConfig.linkSetId                 = Ss7RouteTablePtr->linksetID; 
   Ss7RouteConfig.interfaceType             = Ss7RouteTablePtr->interfaceType;  
   Ss7RouteConfig.style                     = Ss7RouteTablePtr->style; 
   Ss7RouteConfig.sio                       = Ss7RouteTablePtr->sio; 
   Ss7RouteConfig.rssn                      = Ss7RouteTablePtr->rssn;    
   Ss7RouteConfig.lssn                      = Ss7RouteTablePtr->lssn; 
   Ss7RouteConfig.sstTestOn                 = Ss7RouteTablePtr->sstTestOn; 
   Ss7RouteConfig.networkIndicator          = Ss7RouteTablePtr->networkIndicator;      

   LOG_PRINT(LOG_INFO,"Sending OAM_SCM_SS7ROUTE_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&Ss7RouteConfig, sizeof(Ss7RouteConfig) ) != CFG_SUCCESS ){
      return FALSE;
   } 
   return TRUE;
}

/******************************* Function  Header*****************************
  Function Name : delSs7RouteTableHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles delete Link Table request from OMC/CLI
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delSs7RouteTableHandler(I_Void)
{

   if ( ! isDelSs7RouteTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() ); 
      return;
   }

   setStackObject(BSC_API_DEL_SS7ROUTETABLE, SCM_DELETE, OAM_SCM_SS7ROUTE_CONFIG);

   if ( ! fillAndSendOamScmSs7RouteConfig() ) {
      sendStackProcRespToCm();
      return;      
   }
}

/******************************* Function  Header*****************************
  Function Name : delSs7RouteScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from Ss7 Route Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void delSs7RouteScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSs7RouteTable((Ss7RouteTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL," In deleteSs7RouteTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }               
      else
      {
         if (deleteSs7RouteStatusTable((Ss7RouteStatusTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) 
         {
            LOG_PRINT(LOG_INFO,"No row present in Ss7RouteStatus Table");
         }               
      }
   }  
   else {
	   LOG_PRINT(LOG_INFO,"Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
   return;
}

/******************************* Function  Header*****************************
  Function Name : Ss7RouteScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Trunk Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void Ss7RouteScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"Received SCM_ADD..");
         addSs7RouteScmRespHandler();
         break;
      case SCM_MODIFY:
         modifySs7RouteScmRespHandler();
         break;
      case SCM_DELETE:
         LOG_PRINT(LOG_INFO,"Received SCM_DELETE..");
         delSs7RouteScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : Mtp3TimerScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Mtp3Timer Modification 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void Mtp3TimerScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
         modifyMtp3TimerScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : SccpTimerScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Sccp Timer modification 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void SccpTimerScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
         modifySccpTimerScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : BssapTimerScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Bssap timer modification 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void BssapTimerScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
         modifyBssapTimerScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : LapdTimerScmRespHandler()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Lapd timer modificaton 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void LapdTimerScmRespHandler(I_Void)
{
   switch ( getScmAction() ) {
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"Received SCM_MODIFY..");
         modifyLapdTimerScmRespHandler();
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");  
   }
   return;
}

/******************************* Function  Header*****************************
  Function Name : convertMsgOpCodeFromResp2Req()
Parameters    : None
Return type   : I_Void
Purpose       : Handles the response from SCM for Ss7 Stack Table deletion 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_U32 convertMsgOpCodeFromResp2Req(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   switch ( ScmOamRespPtr->scmhdr.opcode ) {
      case SCM_OAM_SS7_STACK_CONFIG_RESP:
         return OAM_SCM_SS7_STACK_CONFIG;
      case SCM_OAM_INTERFACE_CONFIG_RESP:
         return OAM_SCM_INTERFACE_CONFIG;
      case SCM_OAM_LINKSET_CONFIG_RESP:
         return OAM_SCM_LINKSET_CONFIG;  
      case SCM_OAM_LINK_CONFIG_RESP:
         return OAM_SCM_LINK_CONFIG;  
      case SCM_OAM_TRUNK_CIC_CONFIG_RESP:
         return OAM_SCM_TRUNK_CIC_CONFIG;
      case SCM_OAM_SS7ROUTE_CONFIG_RESP:
         return OAM_SCM_SS7ROUTE_CONFIG;
      case SCM_OAM_MTP3_TIMER_CONFIG_RESP:
         return OAM_SCM_MTP3_TIMER_CONFIG;  
      case SCM_OAM_SCCP_TIMER_CONFIG_RESP:
         return OAM_SCM_SCCP_TIMER_CONFIG;  
      case SCM_OAM_BSSAP_TIMER_CONFIG_RESP:
         return OAM_SCM_BSSAP_TIMER_CONFIG;  
      case SCM_OAM_LAPDTIMER_CONFIG_RESP:
         return OAM_SCM_LAPDTIMER_CONFIG;  
      case SCM_OAM_LINK_ADMIN_CONFIG_RESP:
         return OAM_SCM_LINK_ADMIN_CONFIG;  
      case SCM_OAM_SS7ROUTE_TESTON_CONFIG_RESP:
         return OAM_SCM_SS7ROUTE_TESTON_CONFIG;  
      case SCM_OAM_ALARM_MODIFY_RESP:
         return OAM_SCM_ALARM_MODIFY;  
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
      case SCM_OAM_BS_INTERFACE_CONFIG_RESP:
         return OAM_SCM_BS_INTERFACE_CONFIG;  
      case SCM_OAM_SCCP_SP_CONFIG_RESP:
         return OAM_SCM_SCCP_SP_CONFIG;  
      case SCM_OAM_SCCP_SS_CONFIG_RESP:
         return OAM_SCM_SCCP_SS_CONFIG;  
      case SCM_OAM_SCCP_CSS_CONFIG_RESP:
         return OAM_SCM_SCCP_CSS_CONFIG;  
      case SCM_OAM_SCCP_CSP_CONFIG_RESP:
         return OAM_SCM_SCCP_CSP_CONFIG;  
      case SCM_OAM_M3UA_LOCAL_ASP_CONFIG_RESP:
         return OAM_SCM_M3UA_LOCAL_ASP_CONFIG;  
      case SCM_OAM_M3UA_REMOTE_ASP_CONFIG_RESP:
         return OAM_SCM_M3UA_REMOTE_ASP_CONFIG;  
      case SCM_OAM_M3UA_LOCAL_AS_CONFIG_RESP:
         return OAM_SCM_M3UA_LOCAL_AS_CONFIG;  
      case SCM_OAM_M3UA_REMOTE_AS_CONFIG_RESP:
         return OAM_SCM_M3UA_REMOTE_AS_CONFIG;  
      case SCM_OAM_SCTP_GEN_CONFIG_RESP:
         return OAM_SCM_SCTP_GEN_CONFIG;  
      case SCM_OAM_BS_TIMER_CONFIG_RESP:
         return OAM_SCM_BS_TIMER_CONFIG;  
      case SCM_OAM_M3UA_TIMER_CONFIG_RESP:
         return OAM_SCM_M3UA_TIMER_CONFIG;  
      case SCM_OAM_SCCP_TMR_CONFIG_RESP:
         return OAM_SCM_SCCP_TMR_CONFIG;  
      case SCM_OAM_SCTP_TIMER_CONFIG_RESP:
         return OAM_SCM_SCTP_TIMER_CONFIG;  
      case SCM_OAM_M3UA_LOCAL_ASP_ADMIN_CONFIG_RESP:
         return OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG;  
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
      default: 
         return BASE_OPCODE_SCM;  // This will not match to exiting codes.
   }
   return BASE_OPCODE_SCM;
}

I_Void ScmRespHandler(I_Void)
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isScmRespValid(ScmOamRespPtr->scmhdr) ) {
      /* Start SCM_CFG_RESP_TIMER to await response from SCM*/
      cfgStopTimer();   
      switch ( convertMsgOpCodeFromResp2Req() ) {
         case OAM_SCM_SS7_STACK_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_SS7_STACK_CONFIG_RESP..");
            Ss7StackScmRespHandler();
            break;
         case OAM_SCM_INTERFACE_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_INTERFACE_CONFIG_RESP..");
            AifInterfaceScmRespHandler();
            break;
         case OAM_SCM_LINKSET_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_LINKSET_CONFIG_RESP..");
            LinkSetScmRespHandler();
            break;
         case OAM_SCM_LINK_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_LINK_CONFIG_RESP..");
            LinkScmRespHandler();
            break;
         case OAM_SCM_TRUNK_CIC_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_TRUNK_CIC_CONFIG_RESP..");
            TrunkScmRespHandler();
            break;
         case OAM_SCM_SS7ROUTE_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_SS7ROUTE_CONFIG_RESP..");
            Ss7RouteScmRespHandler();
            break;
         case OAM_SCM_MTP3_TIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_MTP3_TIMER_CONFIG_RESP..");
            Mtp3TimerScmRespHandler();
            break;
         case OAM_SCM_SCCP_TIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_SCCP_TIMER_CONFIG_RESP..");
            SccpTimerScmRespHandler();
            break;
         case OAM_SCM_BSSAP_TIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_BSSAP_TIMER_CONFIG_RESP..");
            BssapTimerScmRespHandler();
            break;
         case OAM_SCM_LAPDTIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_LAPDTIMER_CONFIG_RESP..");
            LapdTimerScmRespHandler();
            break;
         case OAM_SCM_SS7ROUTE_TESTON_CONFIG:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_SS7ROUTE_TESTON_CONFIG_RESP..");
            Ss7RouteScmRespHandler();
            break;
         case OAM_SCM_ALARM_MODIFY:
            LOG_PRINT(LOG_INFO,"Received SCM_OAM_ALARM_MODIFY_RESP..");
            Ss7StackScmRespHandler();
            break;
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
         case OAM_SCM_BS_INTERFACE_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_BS_INTERFACE_CONFIG_RESP ..");
            BssapInterfaceScmRespHandler();
            break;
         case OAM_SCM_SCCP_SP_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received OAM_SCM_SCCP_SP_CONFIG ..");
					  SccpSpConfigScmRespHandler();	
            break;
         case OAM_SCM_SCCP_SS_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_SCCP_SS_CONFIG_RESP ..");
					  SccpSsConfigScmRespHandler();	
            break;
         case OAM_SCM_SCCP_CSS_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_SCCP_CSS_CONFIG_RESP ..");
					  SccpCssConfigScmRespHandler();	
            break;
         case OAM_SCM_SCCP_CSP_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_SCCP_CSP_CONFIG_RESP ..");
					  SccpCspConfigScmRespHandler();	
            break;
         case OAM_SCM_M3UA_LOCAL_ASP_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_M3UA_LOCAL_ASP_CONFIG_RESP ..");
					  M3uaLocalAspConfigScmRespHandler();	
            break;
         case OAM_SCM_M3UA_REMOTE_ASP_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_M3UA_REMOTE_ASP_CONFIG_RESP ..");
					  M3uaRemoteAspConfigScmRespHandler();	
            break;
         case OAM_SCM_M3UA_LOCAL_AS_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_M3UA_LOCAL_AS_CONFIG_RESP ..");
					  M3uaLocalAsConfigScmRespHandler();	
            break;
         case OAM_SCM_M3UA_REMOTE_AS_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_M3UA_REMOTE_AS_CONFIG_RESP ..");
					  M3uaRemoteAsConfigScmRespHandler();	
            break;
         case OAM_SCM_SCTP_GEN_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_SCTP_GEN_CONFIG_RESP ..");
					  SctpConfigScmRespHandler();	
            break;
         case OAM_SCM_BS_TIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_BS_TIMER_CONFIG_RESP ..");
					  SigtranBssapTimerScmRespHandler();	
            break;
         case OAM_SCM_SCCP_TMR_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_SCCP_TMR_CONFIG_RESP ..");
					  SigtranSccpTimerScmRespHandler();	
            break;
         case OAM_SCM_M3UA_TIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_M3UA_TIMER_CONFIG_RESP ..");
					  SigtranM3uaTimerScmRespHandler();	
            break;
         case OAM_SCM_SCTP_TIMER_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_OAM_SCTP_TIMER_CONFIG_RESP ..");
					  SigtranSctpTimerScmRespHandler();	
            break;
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
         case OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG:
            LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG..");
					  aspLockUnlockHandler();	
         default :;
             LOG_PRINT(LOG_DEBUG,"Received Invalid msgopcode..");
             break;
      }
   }
   else {
      LOG_PRINT(LOG_CRITICAL," Unexpected ScmOamResponse from SCM..ignored");    
   }
   return;  
}
/**********************************Deletion of Stack Objects Handling End  *****************************/

/*BSC CS4.0 HA Changes Starts*/
/******************************* Function  Header*****************************
  Function Name : sendSwitchConnectReqToRm()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch connect request to RM 
Other Note    : Added For BSC CS4.0
 *****************************************************************************/
I_Void sendSwitchConnectReqToRm(LinkTableApi *linkTablePtr)
{
   OamsCfgRmPeerSwitchConnect oamsCfgRmPeerSwitchConnect;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   LinkTableApi *rcvlinkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   LOG_PRINT(LOG_INFO,"sendSwitchConnectReqToRm: Entering in Function");
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(linkTablePtr->e1Num, 
      linkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"sendSwitchConnectReqToRm: getMccLinkResourceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      sendStackProcRespToCm();
      return;
   }

   LOG_PRINT(LOG_INFO,"sendSwitchConnectReqToRm OAMS_CFG_RM_PEER_SWITCH_CONNECT..");
   oamsCfgRmPeerSwitchConnect.srcE1 = rcvlinkTablePtr->e1Num;
   oamsCfgRmPeerSwitchConnect.srcTs = rcvlinkTablePtr->timeSlot;
   oamsCfgRmPeerSwitchConnect.destE1 = mccLinkResourceDbPtr->mccTrunkNum;
   oamsCfgRmPeerSwitchConnect.destTs = mccLinkResourceDbPtr->mccTrunkTs;
   LOG_PRINT(LOG_DEBUG,"sendSwitchConnectReqToRm : Src E1 : %d, \
         Src Ts : %d, Dest E1 : %d, Dest Ts : %d",
         oamsCfgRmPeerSwitchConnect.srcE1, oamsCfgRmPeerSwitchConnect.srcTs,
         oamsCfgRmPeerSwitchConnect.destE1, oamsCfgRmPeerSwitchConnect.destTs);

   cfgSendMessage(&oamsCfgRmPeerSwitchConnect, sizeof(OamsCfgRmPeerSwitchConnect),
         ENT_OAMS_RM, OAMS_CFG_RM_PEER_SWITCH_CONNECT, 0);
   free(mccLinkResourceDbPtr);
   LOG_PRINT(LOG_INFO,"sendSwitchConnectReqToRm: Exiting From Function");
}

/******************************* Function  Header*****************************
  Function Name : AreAllLinksLockedOnGivenTrunkPortID()
  Parameters    : None
  Return type   : I_Bool
  Purpose       : Check if all the associated links for TrunkPort are in locked state
  Other Note    : Added For BSC CS4.0
   **************************************************************************/
I_Bool AreAllLinksLockedOnGivenTrunkPortID(I_U16 TrunkPortID)
{
	LinkTableApi *linkTableDataPtr;
	I_U32 outCount = ZERO;
	I_U16 outSize  = ZERO;
	I_U32 e1Num    = ZERO;
	I_U8  timeSlot = ZERO;
	I_U32 i        = ZERO;

	if (getallLinkTable(&linkTableDataPtr,&outCount,&outSize) == CLIB_SUCCESS) {
	  for (i=0; i < outCount; i++) {
	    e1Num    = ((LinkTableApi *)((I_U8 *)linkTableDataPtr + i*outSize))->e1Num;
		 timeSlot = ((LinkTableApi *)((I_U8 *)linkTableDataPtr + i*outSize))->timeSlot;
       LOG_PRINT(LOG_INFO,"AreAllLinksLockedOnGivenTrunkPortID : e1Num is %d",e1Num);
       LOG_PRINT(LOG_INFO,"AreAllLinksLockedOnGivenTrunkPortID : Trunkport is %d",TrunkPortID);
		 if ( (e1Num == TrunkPortID ) && (gE1TimeslotData[e1Num][timeSlot].e1TimeslotState != locked  )) {
		   free(linkTableDataPtr);
		   return FALSE;
		 }
	  }
	  free(linkTableDataPtr);
	}
	return TRUE;
}

//Mantis #9191 #8595 #8873 start - Replace isStackResp macro with function 
/************************* Function  Header*****************************
  Function Name : isStackRespOK()
  Parameters    : I_S16
  Return type   : I_Bool
  Purpose       : Check if response received from stack is ok or not 
  Other Note    : Added For BSC CS4.0
**************************************************************************/
I_Bool isStackRespOK(I_S16 err)
{
		  LOG_PRINT(DEBUG,"Received error from stack %d",err);
		  if(err == 0)
		  {
					 return 1;
		  }
		  else
		  {
				if(err == ERROR_PREVIOUS_CMD_IN_PROGRESS)
				{
						  setFailCauseInStackObj(CM_ERR_STACK_PREVIOUS_CMD_IN_PROGRES);
				}
				else
				{
						  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);

				}
				  return 0;
		  }
}
//End			
/*BSC CS4.0 HA Changes Ends*/

/******************************* Function  Header*****************************
  Function Name : sendPeerSwitchConnectReqToGrhm()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch connect request to GRHM 
Other Note    : Added For BSC HA 
 *****************************************************************************/
I_Void sendPeerSwitchConnectReqToGrhm(LinkTableApi *linkTablePtr)
{
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnect;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   LinkTableApi *rcvlinkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(linkTablePtr->e1Num, 
      linkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"sendPeerSwitchConnect: getMccLinkResourceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      sendStackProcRespToCm();
      return;
   }

   LOG_PRINT(LOG_INFO,"sendPeerSwitchConnect: Sending OAMS_CFG_GRHM_SWITCH_CONNECT..");
   oamsCfgGrhmSwitchConnect.firstE1Num = linkTablePtr->e1Num;
   oamsCfgGrhmSwitchConnect.firstTimeSlotNum = linkTablePtr->timeSlot;
   oamsCfgGrhmSwitchConnect.secondE1Num = mccLinkResourceDbPtr->peerTrunkNum;
   oamsCfgGrhmSwitchConnect.secondTimeSlotNum = mccLinkResourceDbPtr->peerTrunkTs;
   LOG_PRINT(LOG_INFO,"oamsCfgGrhmSwitchConnectPeer : First E1 : %d, \
         First Ts : %d, SecE1 : %d, SecTs : %d",
         oamsCfgGrhmSwitchConnect.firstE1Num, oamsCfgGrhmSwitchConnect.firstTimeSlotNum,
         oamsCfgGrhmSwitchConnect.secondE1Num, oamsCfgGrhmSwitchConnect.secondTimeSlotNum);

   cfgSendMessage(&oamsCfgGrhmSwitchConnect, sizeof(OamsCfgGrhmSwitchConnect),
         ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
   free(mccLinkResourceDbPtr);
}/*sendPeerSwitchConnectReqToGrhm*/

/******************************* Function  Header*****************************
	Function Name : sendSwitchReqToPeerCfg()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch connect request to peer CFG 
Other Note    : Added For BSC HA 
 *****************************************************************************/
I_Void sendSwitchReqToPeerCfg(I_U16 extTrunkNum, I_U8 extTs, I_U32 action, I_U8 subType)
{
	 CfgCfgSwitchInfoMsg cfgCfgSwitchInfo;
	 MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
	 I_U32 outCount = 0;
	 I_U16 outSize = 0;
   I_U32 msgSz=0;

	 if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(extTrunkNum,extTs,
             &mccLinkResourceDbPtr, &outCount, &outSize))
	 {
			LOG_PRINT(LOG_MAJOR,"sendSwitchReqToPeerCfg: getMccLinkResourceTable call is getting failed for e1:%d ts:%d",
          extTrunkNum,extTs);
			return;
	 }

	 LOG_PRINT(LOG_INFO,"sendSwitchReqToPeerCfg: Sending CFG_PEERCFG_SWITCH_CONNECT..");
   cfgCfgSwitchInfo.count = 1;
	 cfgCfgSwitchInfo.switchingInfo[0].srcStreamId = mccLinkResourceDbPtr->mccTrunkNum;
	 cfgCfgSwitchInfo.switchingInfo[0].srcTsId = mccLinkResourceDbPtr->mccTrunkTs;
	 cfgCfgSwitchInfo.switchingInfo[0].dstStreamId = mccLinkResourceDbPtr->peerTrunkNum;
	 cfgCfgSwitchInfo.switchingInfo[0].dstTsId = mccLinkResourceDbPtr->peerTrunkTs;
	 cfgCfgSwitchInfo.switchingInfo[0].direction = CFG_SWITCH_BI_DIRECTN;
	 cfgCfgSwitchInfo.switchingInfo[0].action = action;

	 LOG_PRINT(LOG_INFO,"sendSwitchReqToPeerCfg : First E1 : %d, \
				 First Ts : %d, SecE1 : %d, SecTs : %d",
          mccLinkResourceDbPtr->mccTrunkNum,mccLinkResourceDbPtr->mccTrunkTs,
          mccLinkResourceDbPtr->peerTrunkNum,mccLinkResourceDbPtr->peerTrunkTs);
   
   msgSz = sizeof(CfgCfgSwitchInfoMsg);  
	 cfgSendMessage(&cfgCfgSwitchInfo, msgSz,ENT_OAMS_CFG, CFG_PEERCFG_SWITCH_INFO,subType );
	 free(mccLinkResourceDbPtr);
}/*sendSwitchReqToPeerCfg*/

/******************************* Function  Header*****************************
	Function Name : sendBpmSwitchInfoForPeerCard()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch connect request to BPM for peer card links
Other Note    : Added For BSC HA 
 *****************************************************************************/
I_S32 sendBpmSwitchInfoForPeerCard( I_U8 slotId)
{
	 MccLinkResourceTableApi *mccLinkResourcePtr_mtp2 = NULL;
	 MccLinkResourceTableApi *mccLinkResourcePtr_bic = NULL;
	 MccLinkResourceTableApi *mccLinkResourcePtr_trx = NULL;
	 MccLinkResourceTableApi *tmpMccLinkResourcePtr = NULL;
	 I_U32 outRows_mtp2 = 0;
	 I_U16 outSize_mtp2 = 0;
	 I_U32 outRows_bic = 0;
	 I_U16 outSize_bic = 0;
	 I_U32 outRows_trx = 0;
	 I_U16 outSize_trx = 0;
   OamsCfgOilSwitchInfoReq *oamsCfgOilSwitchInfoReq;
   E1StreamMapTableIndices e1StrmMapTblIndex;
   E1StreamMapTableApi *outData = NULL;
   I_U32 msgSz=0;
   I_U32 i = 0, j =0;
   I_S32 res;
   I_U8 chasisFrameId = 0;
   I_U8 activeSlotId = 0;

   if ( ( res = getActiveIccSlotId( &chasisFrameId, &activeSlotId) != CLIB_SUCCESS ) )
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",res);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",activeSlotId,chasisFrameId);


   res = getTrunkNumTsMccLinkTable( SYS_TS_USAGE_MTP2, SYS_TS_ALLOCATED, slotId,
            &mccLinkResourcePtr_mtp2, &outRows_mtp2, &outSize_mtp2);
   if(CLIB_SUCCESS != res)
	 {
			LOG_PRINT(LOG_MAJOR,"sendBpmSwitchInfoForPeerCard: getTrunkNumTsMccLinkTable failed for Mtp2 err:%d ",
          res);
	 }
   else
   {
      LOG_PRINT(DEBUG,"getTrunkNumTsMccLinkTable ret %d rows for mtp2",outRows_mtp2);
   }
  
   #if 0

   res = getTrunkNumTsMccLinkTable( SYS_TS_USAGE_LAPD_BIC, SYS_TS_ALLOCATED, slotId,
            &mccLinkResourcePtr_bic, &outRows_bic, &outSize_bic);
   if(CLIB_SUCCESS != res)
	 {
			LOG_PRINT(LOG_MAJOR,"sendBpmSwitchInfoForPeerCard: getTrunkNumTsMccLinkTable failed err:%d for bic",
          res);
	 }
   else
   {
      LOG_PRINT(DEBUG,"getTrunkNumTsMccLinkTable ret %d rows for bic",outRows_bic);
   }

   res = getTrunkNumTsMccLinkTable( SYS_TS_USAGE_LAPD_TRX, SYS_TS_ALLOCATED, slotId,
            &mccLinkResourcePtr_trx, &outRows_trx, &outSize_trx);
   if(CLIB_SUCCESS != res)
	 {
			LOG_PRINT(LOG_MAJOR,"sendBpmSwitchInfoForPeerCard: getTrunkNumTsMccLinkTable failed err:%d for trx",
          res);
	 }
   else
   {
      LOG_PRINT(DEBUG,"getTrunkNumTsMccLinkTable ret %d rows for trx",outRows_trx);
   }
   #endif

   if( (outRows_mtp2 + outRows_bic + outRows_trx) == 0)
   {
       LOG_PRINT(DEBUG,"No rows found for peer card for mtp2 bic or trx sending with count = 0");
   }

   msgSz = sizeof(OamsCfgOilSwitchInfoReq) + sizeof(sSwitchingMatrix) * (outRows_mtp2 + outRows_bic + outRows_trx - 1);
   oamsCfgOilSwitchInfoReq = (OamsCfgOilSwitchInfoReq *)AlocOrdBuf(msgSz);
   if(oamsCfgOilSwitchInfoReq == NULL)
   {
      LOG_PRINT(DEBUG,"AlocOrdBuf ret NULL for size:%d", msgSz); 
      if(mccLinkResourcePtr_mtp2 != NULL)
      {
         free(mccLinkResourcePtr_mtp2); 
      }
      //free(mccLinkResourcePtr_bic); 
      //free(mccLinkResourcePtr_trx); 
      return ; 
   }

   oamsCfgOilSwitchInfoReq->switchInfo.frameID = chasisFrameId;
   oamsCfgOilSwitchInfoReq->switchInfo.slotID = slotId;
   oamsCfgOilSwitchInfoReq->switchInfo.switchingCount = outRows_mtp2 + outRows_bic + outRows_trx;

   /*for loop for mtp2 entries*/
   for(j=0,i =0 ; i < outRows_mtp2; i++)
   {
      tmpMccLinkResourcePtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkResourcePtr_mtp2 + i* outSize_mtp2);
      e1StrmMapTblIndex.e1Num = tmpMccLinkResourcePtr->extTrunkNum;
      e1StrmMapTblIndex.e1Ts = tmpMccLinkResourcePtr->extTrunkTs;
      res = getE1StreamMapTable(&e1StrmMapTblIndex,&outData);
      if(res != CLIB_SUCCESS)
      {
        LOG_PRINT(MAJOR,"getE1StreamMapTable Failed in sendSwitchMakeReq err=%d srcE1=%d srcTs=%d",
             res,e1StrmMapTblIndex.e1Num,e1StrmMapTblIndex.e1Ts);
        continue;
      }  

      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].srcStreamId = outData->strmNum;
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].srcTsId = outData->strmTs; 
      free(outData);
      outData = NULL;
    
      e1StrmMapTblIndex.e1Num = tmpMccLinkResourcePtr->mccTrunkNum;
      e1StrmMapTblIndex.e1Ts = tmpMccLinkResourcePtr->mccTrunkTs;
      res = getE1StreamMapTable(&e1StrmMapTblIndex,&outData);
      if(res != CLIB_SUCCESS)
      {
        LOG_PRINT(MAJOR,"getE1StreamMapTable Failed in sendSwitchMakeReq err=%d srcE1=%d srcTs=%d",
             res,e1StrmMapTblIndex.e1Num,e1StrmMapTblIndex.e1Ts);
        continue;
      }  

      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].dstStreamId = outData->strmNum; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].dstTsId = outData->strmTs; 

      free(outData);
      outData = NULL;

      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].direction = CFG_SWITCH_BI_DIRECTN; 
      j++;
   }
   free(mccLinkResourcePtr_mtp2); 

   #if 0
   /*for loop for bic entries*/
   for(i =0;i<outRows_bic;i++)
   {
      tmpMccLinkResourcePtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkResourcePtr_bic + i* outSize_bic);
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].srcStreamId = tmpMccLinkResourcePtr->extTrunkNum; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].srcTsId = tmpMccLinkResourcePtr->extTrunkTs; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].dstStreamId = tmpMccLinkResourcePtr->mccTrunkNum; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].dstTsId = tmpMccLinkResourcePtr->mccTrunkTs; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].direction = CFG_SWITCH_BI_DIRECTN; 
      j++;
   }
   free(mccLinkResourcePtr_bic); 
   
   /*for loop for trx entries*/
   for(i =0;i<outRows_trx;i++)
   {
      tmpMccLinkResourcePtr = (MccLinkResourceTableApi *)((I_U8 *)mccLinkResourcePtr_trx + i* outSize_bic);
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].srcStreamId = tmpMccLinkResourcePtr->extTrunkNum; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].srcTsId = tmpMccLinkResourcePtr->extTrunkTs; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].dstStreamId = tmpMccLinkResourcePtr->mccTrunkNum; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].dstTsId = tmpMccLinkResourcePtr->mccTrunkTs; 
      oamsCfgOilSwitchInfoReq->switchInfo.switchMatrix[j].direction = CFG_SWITCH_BI_DIRECTN; 
      j++;
   }
   free(mccLinkResourcePtr_trx); 
   #endif
   
	 cfgSendMessage(oamsCfgOilSwitchInfoReq, msgSz,ENT_OAM_OIL, OAMS_CFG_OIL_SWITCH_INFO, 0 );

   DalocOrdBuf(oamsCfgOilSwitchInfoReq);
}/*sendBpmSwitchInfoForPeerCard*/

/******************************* Function  Header*****************************
Function Name : sendPeerSwitchDisconnectReqToGrhm()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch disconnect request to GRHM 
Other Note    : Added For BSC HA 
 *****************************************************************************/
I_Void sendPeerSwitchDisconnectReqToGrhm(LinkTableApi *linkTablePtr)
{
   OamsCfgGrhmSwitchDisconnect oamsCfgGrhmSwitchDisconnect;
   MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
   LinkTableApi *rcvlinkTablePtr = (LinkTableApi *)gStoredMsgBufPtr;
   I_U32 outCount = 0;
   I_U16 outSize = 0;

   if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(linkTablePtr->e1Num, 
      linkTablePtr->timeSlot, &mccLinkResourceDbPtr, &outCount, &outSize))
   {
      LOG_PRINT(LOG_MAJOR,"sendPeerSwitchConnect: getMccLinkResourceTable call is getting failed..");
      setFailCauseInStackObj(CM_ERR_GET_DB_OPER_FAILED);
      sendStackProcRespToCm();
      return;
   }

   gStackObject.mccTrunkNum = mccLinkResourceDbPtr->mccTrunkNum; 
   gStackObject.mccTrunkTs  = mccLinkResourceDbPtr->mccTrunkTs;
   gStackObject.cardNum     = mccLinkResourceDbPtr->cardNum;

   LOG_PRINT(LOG_INFO,"sendPeerSwitchConnect: Sending OAMS_CFG_GRHM_SWITCH_CONNECT..");
   oamsCfgGrhmSwitchDisconnect.firstE1Num = linkTablePtr->e1Num;
   oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum = linkTablePtr->timeSlot;
   oamsCfgGrhmSwitchDisconnect.secondE1Num = mccLinkResourceDbPtr->peerTrunkNum;
   oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum = mccLinkResourceDbPtr->peerTrunkTs;
   LOG_PRINT(LOG_INFO,"oamsCfgGrhmSwitchDisconnectPeer : First E1 : %d, \
         First Ts : %d, SecE1 : %d, SecTs : %d",
         oamsCfgGrhmSwitchDisconnect.firstE1Num, oamsCfgGrhmSwitchDisconnect.firstTimeSlotNum,
         oamsCfgGrhmSwitchDisconnect.secondE1Num, oamsCfgGrhmSwitchDisconnect.secondTimeSlotNum);

   cfgSendMessage(&oamsCfgGrhmSwitchDisconnect, sizeof(OamsCfgGrhmSwitchConnect),
         ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
   free(mccLinkResourceDbPtr);
}/*sendPeerSwitchConnectReqToGrhm*/


/******************************* Function  Header*****************************
Function Name : sendLapdSwitchReqToPeerCfg()
Parameters    : I_Void 
Return type   : I_Void
Purpose       : Send Switch connect request to peer CFG 
Other Note    : Added For BSC HA 
*****************************************************************************/
I_Void sendLapdSwitchReqToPeerCfg(I_U16 extTrunkNum, I_U8 extTs, I_U32 action, I_U8 subType)
{
	 CfgCfgSwitchInfoMsg cfgCfgSwitchInfo;
	 MccLinkResourceTableApi *mccLinkResourceDbPtr = NULL;
	 I_U32 outCount = 0;
	 I_U16 outSize = 0;
	 I_U32 msgSz=0;

	 if(CLIB_SUCCESS != getMccTrunkNumTsUsingExtTrunkNumTs(extTrunkNum,extTs,
						 &mccLinkResourceDbPtr, &outCount, &outSize))
	 {
			LOG_PRINT(LOG_MAJOR,"sendLapdSwitchReqToPeerCfg: getMccLinkResourceTable call is getting failed for e1:%d ts:%d",
					extTrunkNum,extTs);
			return;
	 }

	 LOG_PRINT(LOG_INFO,"sendLapdSwitchReqToPeerCfg: Sending CFG_PEERCFG_SWITCH_CONNECT..");
	 cfgCfgSwitchInfo.count = 1;
	 cfgCfgSwitchInfo.switchingInfo[0].srcStreamId = mccLinkResourceDbPtr->mccTrunkNum;
	 cfgCfgSwitchInfo.switchingInfo[0].srcTsId = mccLinkResourceDbPtr->mccTrunkTs;
	 cfgCfgSwitchInfo.switchingInfo[0].dstStreamId = mccLinkResourceDbPtr->extTrunkNum;
	 cfgCfgSwitchInfo.switchingInfo[0].dstTsId = mccLinkResourceDbPtr->extTrunkTs;
	 cfgCfgSwitchInfo.switchingInfo[0].direction = CFG_SWITCH_BI_DIRECTN;
	 cfgCfgSwitchInfo.switchingInfo[0].action = action;

	 LOG_PRINT(LOG_INFO,"sendLapdSwitchReqToPeerCfg : First E1 : %d, \
				 First Ts : %d, SecE1 : %d, SecTs : %d",
					mccLinkResourceDbPtr->mccTrunkNum,mccLinkResourceDbPtr->mccTrunkTs,
					mccLinkResourceDbPtr->extTrunkNum,mccLinkResourceDbPtr->extTrunkTs);
	 
	 msgSz = sizeof(CfgCfgSwitchInfoMsg);  
	 cfgSendMessage(&cfgCfgSwitchInfo, msgSz,ENT_OAMS_CFG, CFG_PEERCFG_SWITCH_INFO,subType );
	 free(mccLinkResourceDbPtr);
}/*sendLapdSwitchReqToPeerCfg*/

/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
/******************************* Function  Header*****************************
Function Name : setBssapInterfaceTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setBssapInterfaceTable(BssapIntfConfigTableApi *receivedMsgPtr)
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setBssapInterfaceTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 BssapIntfConfigTableApi *bssapIntfConfigTableApi = NULL;
 BssapTmrConfigTableApi *bssapTmrTblPtr = NULL;
 BssapTmrConfigTableIndices bssapTmrIndex;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 I_U32 bscId = ZERO;
 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: bscId:%d tProfile:%d",
          receivedMsgPtr->bscId, receivedMsgPtr->timerProfileId);

 if(CLIB_SUCCESS == getallBssapIntfConfigTable(&bssapIntfConfigTableApi,&outCount,&outSize))
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry ALREADY present in BssapIntfConfigTable() ..Sending NACK");
   free(bssapIntfConfigTableApi);
   cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
   return; 
 }
 
  /* Perform range check on whether Timer ProfileId exists or not*/
 bssapTmrIndex.profileID =  receivedMsgPtr->timerProfileId;
 if(getBssapTmrConfigTable(&bssapTmrIndex,&bssapTmrTblPtr) != CLIB_SUCCESS)
 {
    cfgSendNackToCm(CM_ERR_REFERENCED_OBJECT_NOT_FOUND);
    return;
 }
 free(bssapTmrTblPtr);
 if(CLIB_SUCCESS!=getBscId(&bscId))
 {
    LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed, returned Error Code ");
    cfgSendNackToCm(CM_ERR_REFERENCED_OBJECT_NOT_FOUND);
    return;
 }
 if(bscId!=receivedMsgPtr->bscId)
 {
    LOG_PRINT(LOG_CRITICAL,"bscId rcvd[%d] is different from BscId [%d]in BSS table", receivedMsgPtr->bscId,bscId);
    cfgSendNackToCm(CM_ERR_REFERENCED_OBJECT_NOT_FOUND);
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of BssapIntfConfigTable(): going for rangeChk..");
 /* Perform range check on received parameters */
 if(!bssapIntfConfigRangeChk(receivedMsgPtr))
 {
    cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
    return; 
 }

 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(BssapIntfConfigTableApi)))
 {
    return; 
 }

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_BSSAPINTFCONFIGTABLE, SCM_ADD, OAM_SCM_BS_INTERFACE_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmBsInterfaceConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setBssapInterfaceTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delBssapInterfaceTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delBssapInterfaceTable(BssapIntfConfigTableApi *receivedMsgPtr)
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delBssapInterfaceTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 BssapIntfConfigTableApi *bssapIntfConfigTableApi = NULL;
 SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi = NULL,*tmpsigtranSccpSPConfigTableApi=NULL;
 SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi=NULL,*tmpSigtranM3uaLAsConfigTableApi=NULL;
 SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi=NULL,*tmpSigtranM3uaRAsConfigTableApi=NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO,i=ZERO;
 BssapIntfConfigTableIndices *KeysPtr = (BssapIntfConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getBssapIntfConfigTable(KeysPtr, &bssapIntfConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getBssapIntfConfigTable for bscId[%d]",KeysPtr->bscId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(bssapIntfConfigTableApi);
 if(CLIB_SUCCESS == getallSigtranSccpSPConfigTable(&sigtranSccpSPConfigTableApi,&outCount,&outSize))
 {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: outCount[%d] outSize[%d]",outCount,outSize);
    for(i = 0; i < outCount; ++i)
    { 
      tmpsigtranSccpSPConfigTableApi = (SigtranSccpSPConfigTableApi *)((I_U8 *)sigtranSccpSPConfigTableApi+ i * outSize);
      //LOG_PRINT(LOG_INFO, "IP_BSC_STACK: [%d] BssapOpc[%d] BssapDpc[%d]",tmpsigtranSccpSPConfigTableApi->pointCode,receivedMsgPtr->opc,receivedMsgPtr->dpc);
			if((tmpsigtranSccpSPConfigTableApi->pointCode == bssapIntfConfigTableApi->opc) || (tmpsigtranSccpSPConfigTableApi->pointCode == bssapIntfConfigTableApi->dpc))
			{
			  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Either OPC/DPC[%d] present in SigtranSccpSPConfigTable: Sending NACK",tmpsigtranSccpSPConfigTableApi->pointCode);
        free(sigtranSccpSPConfigTableApi);
        free(bssapIntfConfigTableApi);
			  cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_SP_TABLE_EXITS);
			  return;
			}
    }
   free(sigtranSccpSPConfigTableApi);
 }
 outSize = ZERO;
 outCount =ZERO;
 /*Check for opc if present in M3UA LOCAL AS CONFIG Table*/
 if(CLIB_SUCCESS == getallSigtranM3uaLAsConfigTable(&sigtranM3uaLAsConfigTableApi,&outCount,&outSize))
 {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: outCount[%d] outSize[%d]",outCount,outSize);
  	for(i = 0; i < outCount; ++i)
  	{
  	 tmpSigtranM3uaLAsConfigTableApi = (SigtranM3uaLAsConfigTableApi *)((I_U8 *)sigtranM3uaLAsConfigTableApi+ i * outSize);
  	 if((tmpSigtranM3uaLAsConfigTableApi->sourcePointCode == bssapIntfConfigTableApi->opc))   	 {
  		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:opc[%d] Already present in SigtranM3uaLAsConfigTableApi",bssapIntfConfigTableApi->opc);
  		 free(sigtranM3uaLAsConfigTableApi);
       free(bssapIntfConfigTableApi);
  		 cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_LOCAL_AS_TABLE_EXISTS);
  		 return;
  	 }
  	}
  	free(sigtranM3uaLAsConfigTableApi);
 }
 /*Check for opc if present in M3UA LOCAL AS CONFIG Table*/
 outSize = ZERO;
 outCount =ZERO;
 /*Check for dpc if present in M3UA REMOTE AS CONFIG Table*/
 if(CLIB_SUCCESS == getallSigtranM3uaRAsConfigTable(&sigtranM3uaRAsConfigTableApi,&outCount,&outSize))
 {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: outCount[%d] outSize[%d]",outCount,outSize);
  	for(i = 0; i < outCount; ++i)
  	{
  	 tmpSigtranM3uaRAsConfigTableApi = (SigtranM3uaRAsConfigTableApi *)((I_U8 *)sigtranM3uaRAsConfigTableApi+ i * outSize);
  	 if((tmpSigtranM3uaRAsConfigTableApi->remPointCode == bssapIntfConfigTableApi->dpc)) 
  	 {
  		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:dpc[%d]Already present in SigtranM3uaRAsConfigTableApi",bssapIntfConfigTableApi->dpc);
  		 free(sigtranM3uaRAsConfigTableApi);
       free(bssapIntfConfigTableApi);
  		 cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_REMOTE_AS_TABLE_EXISTS);
  		 return;
  	 }
  	}
  	free(sigtranM3uaRAsConfigTableApi);
 }
 /*Check for dpc if present in M3UA REMOTE AS CONFIG Table*/
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(bssapIntfConfigTableApi, sizeof(BssapIntfConfigTableApi)))
 {
    free(bssapIntfConfigTableApi);
    return; 
 }
 free(bssapIntfConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_BSSAPINTFCONFIGTABLE, SCM_DELETE, OAM_SCM_BS_INTERFACE_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmBsInterfaceConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delBssapInterfaceTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setSccpSpConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setSccpSpConfigTable(SigtranSccpSPConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSccpSpConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi = NULL,*tmpsigtranSccpSPConfigTableApi = NULL;
 BssapIntfConfigTableApi *bssapIntfConfigTableApi = NULL,*tmpbssapIntfConfigPtr=NULL;;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO,i=ZERO;

 if(CLIB_SUCCESS == getallSigtranSccpSPConfigTable(&sigtranSccpSPConfigTableApi,&outCount,&outSize))
 {
   if(outCount > 1)
   {
     LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Max Entries [%d] ALREADY present in SigtranSccpSPConfigTable() ..Sending NACK",outCount);
     cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
     free(sigtranSccpSPConfigTableApi);
     return; 
	 }
    for(i = 0; i < outCount; ++i)
    { 
      tmpsigtranSccpSPConfigTableApi = (SigtranSccpSPConfigTableApi *)((I_U8 *)sigtranSccpSPConfigTableApi+ i * outSize);
			if(tmpsigtranSccpSPConfigTableApi->spId == receivedMsgPtr->spId)
			{
			  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entry for this SpId[%d] is Already Present::NOT MODIFIABLE: Sending NACK");
			  cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST_MOD_NOT_ALLOWED);
        free(sigtranSccpSPConfigTableApi);
			  return;
			}
    }
   free(sigtranSccpSPConfigTableApi);
 }
 if(CLIB_SUCCESS == getallBssapIntfConfigTable(&bssapIntfConfigTableApi,&outCount,&outSize))
 {
    for(i = 0; i < outCount; ++i)
  {
    tmpbssapIntfConfigPtr = (BssapIntfConfigTableApi *)((I_U8 *)bssapIntfConfigTableApi + i * outSize);
 		if(receivedMsgPtr->local == PC_AOIP_REMOTE)
 		{
 		  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ADD for REMOTE PC:");
 		  if(receivedMsgPtr->pointCode != tmpbssapIntfConfigPtr->dpc)
 		  {
 		 		LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Rcvd REMOTE PC[%d] different from REMOTE PC[%d]in BssapIntfConfigTableApi",receivedMsgPtr->pointCode,tmpbssapIntfConfigPtr->dpc);
 		 		cfgSendNackToCm(CM_ERR_SIGTRAN_PC_DIFF_FROM_BSSAP_INTF_TBL);
        free(bssapIntfConfigTableApi);
 		 		return;
 		  }
 		}
 		if(receivedMsgPtr->local == PC_AOIP_LOCAL)
 		{
 		  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ADD for LOCAL PC:");
 		  if(receivedMsgPtr->pointCode != tmpbssapIntfConfigPtr->opc)
 		  {
 		 		LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Rcvd LOCAL PC[%d] different from LOCAL PC[%d]in BssapIntfConfigTableApi",receivedMsgPtr->pointCode,tmpbssapIntfConfigPtr->opc);
 		 		cfgSendNackToCm(CM_ERR_SIGTRAN_PC_DIFF_FROM_BSSAP_INTF_TBL);
        free(bssapIntfConfigTableApi);
 		 		return;
 		  }
 		}
  }
   free(bssapIntfConfigTableApi);
 }
 else
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry not present in BssapIntfConfigTableApi ..SENDING NACK");
		cfgSendNackToCm(CM_ERR_SIGTRAN_BSSAP_INTF_TBL_NOT_PRESENT);
		return;
 }
  
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSccpSPConfigTable(): going for rangeChk..");
 /* Perform range check on received parameters */
 if(!sccpSpConfigRangeChk(receivedMsgPtr))
 {
   cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
   return; 
 }

 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSccpSPConfigTableApi)))
 {
    return; 
 }

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_SIGTRANSCCPSPCONFIGTABLE, SCM_ADD, OAM_SCM_SCCP_SP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpSpConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSccpSpConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delSccpSpConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delSccpSpConfigTable(SigtranSccpSPConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delSccpSpConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi = NULL;
 SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = NULL,*tmpSigtranSccpSSConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO,i=ZERO;
 SigtranSccpSPConfigTableIndices *KeysPtr = (SigtranSccpSPConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSccpSPConfigTable(KeysPtr, &sigtranSccpSPConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSccpSPConfigTable for spId[%d]",KeysPtr->spId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranSccpSPConfigTableApi);
 if(CLIB_SUCCESS == getallSigtranSccpSSConfigTable(&sigtranSccpSSConfigTableApi,&outCount,&outSize))
 {
	LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Rows present in SigtranSccpSSConfigTableApi : Sending NACK");
  free(sigtranSccpSSConfigTableApi);
  free(sigtranSccpSPConfigTableApi);
	cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_SS_TBL_EXISTS);
	return;
 /*
    for(i = 0; i < outCount; ++i)
   {
    tmpSigtranSccpSSConfigTableApi = (SigtranSccpSSConfigTableApi *)((I_U8 *)sigtranSccpSSConfigTableApi + i * outSize);
    if(tmpSigtranSccpSSConfigTableApi->spId == receivedMsgPtr->spId)
    {
			LOG_PRINT(LOG_INFO,"IP_BSC_STACK: spId[%d] present in SigtranSccpSSConfigTableApi row[%d]: Sending NACK",receivedMsgPtr->spId,i);
      free(sigtranSccpSSConfigTableApi);
			cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_SS_TBL_EXISTS);
			return;
    }
   }
  free(sigtranSccpSSConfigTableApi);*/
  }
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranSccpSPConfigTableApi, sizeof(SigtranSccpSPConfigTableApi)))
 {
    free(sigtranSccpSPConfigTableApi);
    return; 
 }
 free(sigtranSccpSPConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANSCCPSPCONFIGTABLE, SCM_DELETE, OAM_SCM_SCCP_SP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpSpConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delSccpSpConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setSccpSsConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setSccpSsConfigTable(SigtranSccpSSConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSccpSsConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = NULL,*tmpSigtranSccpSSConfigTableApi=NULL;
 SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi = NULL;
 SigtranSccpSPConfigTableIndices key;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ssId:%d spId:%d",
           receivedMsgPtr->ssId, receivedMsgPtr->spId);

 if(CLIB_SUCCESS == getallSigtranSccpSSConfigTable(&sigtranSccpSSConfigTableApi,&outCount,&outSize))
 {
   if(outCount >1)
   {
      LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MAX Rows[%d] already present in SigtranSccpSSConfigTable() Sending NACK:");
      free(sigtranSccpSSConfigTableApi);
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      return; 
   }
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Rows[%d] present SigtranSccpSSConfigTable()",outCount);
    for(i = 0; i < outCount; ++i)
    {
     tmpSigtranSccpSSConfigTableApi = (SigtranSccpSSConfigTableApi *)((I_U8 *)sigtranSccpSSConfigTableApi + i * outSize);
     if(tmpSigtranSccpSSConfigTableApi->ssId == receivedMsgPtr->ssId)
     {
			 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:ssId[%d]Already present in SigtranSccpSSConfigTableApi row[%d]:No modification allowed Sending NACK",receivedMsgPtr->ssId,i);
       free(sigtranSccpSSConfigTableApi);
			 cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST_MOD_NOT_ALLOWED);
			 return;
     }
    }
   free(sigtranSccpSSConfigTableApi);
 }
 key.spId = receivedMsgPtr->spId;
 if(CLIB_SUCCESS != getSigtranSccpSPConfigTable(&key,&sigtranSccpSPConfigTableApi))
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: SigtranSccpSPConfigTableApi not present for the rcvd spId[%d]",receivedMsgPtr->spId);
		cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_SP_TBL_NOT_PRESENT);
		return;
 }
 free(sigtranSccpSPConfigTableApi);
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSccpSSConfigTable()");

 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSccpSSConfigTableApi)))
 {
    return; 
 }

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_SIGTRANSCCPSSCONFIGTABLE, SCM_ADD, OAM_SCM_SCCP_SS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpSsConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSccpSsConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delSccpSsConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delSccpSsConfigTable(SigtranSccpSSConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delSccpSsConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi = NULL,*tmpSigtranSccpCSSConfigTableApi = NULL;
 SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = NULL;
 SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = NULL,*tmpSigtranSccpCSPConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO,i=ZERO;
 SigtranSccpSSConfigTableIndices *KeysPtr = (SigtranSccpSSConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSccpSSConfigTable(KeysPtr, &sigtranSccpSSConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSccpSSConfigTable for ssId[%d]",KeysPtr->ssId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranSccpSSConfigTableApi);
 if(CLIB_SUCCESS == getallSigtranSccpCSSConfigTable(&sigtranSccpCSSConfigTableApi,&outCount,&outSize))
 {
	LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Row present in SigtranSccpCSSConfigTableApi : Sending NACK");
  free(sigtranSccpCSSConfigTableApi);
  free(sigtranSccpSSConfigTableApi);
	cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_CSS_TBL_EXISTS);
	return;
   /* for(i = 0; i < outCount; ++i)
   {
    tmpSigtranSccpCSSConfigTableApi = (SigtranSccpCSSConfigTableApi *)((I_U8 *)sigtranSccpCSSConfigTableApi + i * outSize);
    if(tmpSigtranSccpCSSConfigTableApi->ssId == receivedMsgPtr->ssId)
    {
			LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ssId[%d] present in SigtranSccpCSSConfigTableApi row[%d]: Sending NACK",receivedMsgPtr->ssId,i);
      free(sigtranSccpCSSConfigTableApi);
      free(sigtranSccpSSConfigTableApi);
			cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_CSS_TBL_EXISTS);
			return;
    }
   }
  free(sigtranSccpCSSConfigTableApi);*/
  }
 outCount=ZERO;
 outSize=ZERO;
 if(CLIB_SUCCESS == getallSigtranSccpCSPConfigTable(&sigtranSccpCSPConfigTableApi,&outCount,&outSize))
 {
	LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Row present in SigtranSccpCSPConfigTableApi : Sending NACK");
  free(sigtranSccpCSPConfigTableApi);
  free(sigtranSccpSSConfigTableApi);
	cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_CSP_TBL_EXISTS);
	return;
  /*  for(i = 0; i < outCount; ++i)
   {
    tmpSigtranSccpCSPConfigTableApi = (SigtranSccpCSPConfigTableApi *)((I_U8 *)sigtranSccpCSSConfigTableApi + i * outSize);
    if(tmpSigtranSccpCSPConfigTableApi->ssId == receivedMsgPtr->ssId)
    {
			LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ssId[%d] present in SigtranSccpCSPConfigTableApi row[%d]: Sending NACK",receivedMsgPtr->ssId,i);
      free(sigtranSccpCSPConfigTableApi);
      free(sigtranSccpSSConfigTableApi);
			cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_CSP_TBL_EXISTS);
			return;
    }
   }
  free(sigtranSccpCSPConfigTableApi);*/
  }
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranSccpSSConfigTableApi, sizeof(SigtranSccpSSConfigTableApi)))
 {
    free(sigtranSccpSSConfigTableApi);
    return; 
 }
 free(sigtranSccpSSConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANSCCPSSCONFIGTABLE, SCM_DELETE, OAM_SCM_SCCP_SS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpSsConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delSccpSsConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setSccpCssConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setSccpCssConfigTable(SigtranSccpCSSConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSccpCssConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi = NULL;
 SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = NULL;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ssId:%d cssId:%d",
           receivedMsgPtr->ssId, receivedMsgPtr->cssId);

 if(CLIB_SUCCESS == getallSigtranSccpCSSConfigTable(&sigtranSccpCSSConfigTableApi,&outCount,&outSize))
 {
   if(outCount >0)
   {
      LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MAX Rows[%d] already present in SigtranSccpCSSConfigTableApi Modification not allowed() Sending NACK:",outCount);
      free(sigtranSccpCSSConfigTableApi);
      cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST_MOD_NOT_ALLOWED);
      return; 
   }
 }
 free(sigtranSccpCSSConfigTableApi);
 SigtranSccpSSConfigTableIndices *key = (SigtranSccpSSConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSccpSSConfigTable(key, &sigtranSccpSSConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSccpSSConfigTable for ssId[%d]",key->ssId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_SS_TBL_NOT_PRESENT);
    return FALSE;
 }
 free(sigtranSccpSSConfigTableApi);
   
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSccpCSSConfigTableApi()");

 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSccpCSSConfigTableApi)))
 {
    return; 
 }

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_SIGTRANSCCPCSSCONFIGTABLE, SCM_ADD, OAM_SCM_SCCP_CSS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpCssConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSccpCssConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delSccpCssConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delSccpCssConfigTable(SigtranSccpCSSConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delSccpCssConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi = NULL;
 SigtranSccpCSSConfigTableIndices *KeysPtr = (SigtranSccpCSSConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSccpCSSConfigTable(KeysPtr, &sigtranSccpCSSConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSccpCSSConfigTable for ssId[%d],cssId[%d]",KeysPtr->ssId,KeysPtr->cssId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranSccpCSSConfigTableApi);
 SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi=NULL;
 if(CLIB_SUCCESS == getallSigtranSccpCSPConfigTable(&sigtranSccpCSPConfigTableApi,&outCount,&outSize))
 {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry Present in SigtranSccpCSPConfigTableApi : sending NACK");
    cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_CSP_TBL_EXISTS);
    free(sigtranSccpCSPConfigTableApi);
    free(sigtranSccpCSSConfigTableApi);
    return FALSE;
 }
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranSccpCSSConfigTableApi, sizeof(SigtranSccpCSSConfigTableApi)))
 {
    free(sigtranSccpCSSConfigTableApi);
    return; 
 }
 free(sigtranSccpCSSConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANSCCPCSSCONFIGTABLE, SCM_DELETE, OAM_SCM_SCCP_CSS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpCssConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delSccpCssConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setSccpCspConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setSccpCspConfigTable(SigtranSccpCSPConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSccpCspConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = NULL;
 SigtranSccpTimerTableApi *sigtranSccTmrIndex = NULL;
 SigtranSccpTimerTableIndices sigtranSccpTmrIndex;
 SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ssId:%d cspId:%d tProfile:%d",
           receivedMsgPtr->ssId,receivedMsgPtr->cspId ,receivedMsgPtr->timerProfileId);

 if(CLIB_SUCCESS == getallSigtranSccpCSPConfigTable(&sigtranSccpCSPConfigTableApi,&outCount,&outSize))
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry ALREADY present in SigtranSccpTimerTableApi() ..Sending NACK");
   free(sigtranSccpCSPConfigTableApi);
   cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST_MOD_NOT_ALLOWED);
   return; 
 }
 SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi = NULL;
 if(CLIB_SUCCESS != getallSigtranSccpCSSConfigTable(&sigtranSccpCSSConfigTableApi,&outCount,&outSize))
 {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getallSigtranSccpCSSConfigTable");
    cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_CSS_TBL_NOT_PRESENT);
    return;
 }
 free(sigtranSccpCSSConfigTableApi);
 SigtranSccpSSConfigTableIndices *key = (SigtranSccpSSConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSccpSSConfigTable(key, &sigtranSccpSSConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSccpSSConfigTable for ssId[%d]",key->ssId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_SIGTRAN_SCCP_SS_TBL_NOT_PRESENT);
    return FALSE;
 }
 free(sigtranSccpSSConfigTableApi);
  /* Perform range check on whether Timer ProfileId exists or not*/
 sigtranSccpTmrIndex.profileId =  receivedMsgPtr->timerProfileId;
 if(getSigtranSccpTimerTable(&sigtranSccpTmrIndex,&sigtranSccTmrIndex) != CLIB_SUCCESS)
 {
   cfgSendNackToCm(CM_ERR_SIGTRAN_TIMER_TABLE_NOT_PRESENT);
   return;
 }
 free(sigtranSccTmrIndex);
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSccpTimerTableApi()");

 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSccpCSPConfigTableApi)))
 {
    return; 
 }

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_SIGTRANSCCPCSPCONFIGTABLE, SCM_ADD, OAM_SCM_SCCP_CSP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpCspConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSccpCspConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delSccpCspConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delSccpCspConfigTable(SigtranSccpCSPConfigTableApi *receivedMsgPtr)	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delSccpCspConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = NULL;
 SigtranSccpCSPConfigTableIndices *KeysPtr = (SigtranSccpCSPConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSccpCSPConfigTable(KeysPtr, &sigtranSccpCSPConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSccpCSPConfigTable for ssId[%d],cspId[%d]",KeysPtr->ssId,KeysPtr->cspId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranSccpCSPConfigTableApi);
 SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outCount,&outSize))
 {
  free(sigtranM3uaLAspConfigTableApi);
  free(sigtranSccpCSPConfigTableApi);
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: sigtranM3uaLAspConfigTableApi Present: Sending NACK...");
  cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_LOCAL_AS_TBL_PRESENT);
  return;
 }
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranSccpCSPConfigTableApi, sizeof(SigtranSccpCSPConfigTableApi)))
 {
    free(sigtranSccpCSPConfigTableApi);
    return; 
 }
 free(sigtranSccpCSPConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANSCCPCSPCONFIGTABLE, SCM_DELETE, OAM_SCM_SCCP_CSP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSccpCspConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delSccpCspConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setM3uaLocalAspConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setM3uaLocalAspConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setM3uaLocalAspConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 SigtranM3uaLAspConfigTableApi* receivedMsgPtr = (SigtranM3uaLAspConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 //LOG_PRINT(DEBUG,"HEX DUMP from CM..");
 //PRINT_HEX_DUMP(LOG_DEBUG, receivedMsgPtr,sizeof(SigtranM3uaLAspConfigTableApi));
 SigtranM3uaLAspConfigTableApi* sigtranM3uaLAspConfigTableApi = NULL,*tmpSigtranM3uaLAspConfigTableApi=NULL;
 SigtranM3uaLAspConfigTableIndices key;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 key.localAspId = receivedMsgPtr->localAspId;
 if(CLIB_SUCCESS==getSigtranM3uaLAspConfigTable(&key,&sigtranM3uaLAspConfigTableApi))
 {
  if (gBssState == unlockInProgress )
  {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: BSS is unlockInProgress,Operation not Possible");
     cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
     free(sigtranM3uaLAspConfigTableApi);
     return;
  }
  /* Reject the request if Bss is Lock In Progress state */
  if (gBssState == lockInProgress )
  {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: BSS is lockInProgress,Operation not Possible");
     cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
     free(sigtranM3uaLAspConfigTableApi);
     return;
  }

  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MODIFICATION of SigtranM3uaLAspConfigTable LOCK/UNLOCK");

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranM3uaLAspConfigTableApi)))
   {
      free(sigtranM3uaLAspConfigTableApi);
      return; 
   }
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
      I_S32 i=-1;
			i = getIndexFromAspId(receivedMsgPtr->localAspId);
			if(i<0)
			{
				LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Invalid index returned by getIndexFromAspId() for AspId [%d] NOT PROCEEDING",receivedMsgPtr->localAspId);
				return;
			}
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   if(receivedMsgPtr->adminState!=sigtranM3uaLAspConfigTableApi->adminState)
   {
   	/* Set Stack object data structure */
    if(receivedMsgPtr->adminState == LOCKED)
		{
     LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: SigtranM3uaLAspConfigTable LOCK REQ rcvd");
      if(bssAdminState == LOCKED)
      {
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Bss is Locked,Only adminState is updated as LOCKED");
         //sendPspLockAlarm(sigtranM3uaLAspConfigTableApi);AlarmsToBeRaisedAfterWards
          sigtranM3uaLAspConfigTableApi->adminState = LOCKED; 
					if (updateSigtranM3uaLAspConfigTable(sigtranM3uaLAspConfigTableApi) != CLIB_SUCCESS)
					{
						 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In setM3uaLocalAspConfigTable(): updateSigtranM3uaLAspConfigTable Failed..");
						 //setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
             cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
             free(sigtranM3uaLAspConfigTableApi);
             return;
					}
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
         gStructAspStatusVar[i].gAdminState = locked;
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: After Updating AspId[%d] Admin State in DB as LOCKED, Updated gAdminState [%d]",sigtranM3uaLAspConfigTableApi->localAspId,gStructAspStatusVar[i].gAdminState);
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
         free(sigtranM3uaLAspConfigTableApi);
         cfgSendAckToCm();
         return;
      }
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
      if(gStructAspStatusVar[i].gAdminState == lockInProgress)
      {
					LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ASPID [%d] is Already lockInProgress,Operation not Possible",gStructAspStatusVar[i].localAspId);
					cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
					return;
      }
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
      

   	 setStackObject(BSC_API_SET_SIGTRANM3UALASPCONFIGTABLE, SCM_LOCK, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG);
		/* Frame and Send the message to the OIL */
			if (!fillAndSendOamScmM3uaLocalAspAdminConfig(LOCKED))
			{   
				sendStackProcRespToCm();
				free(sigtranM3uaLAspConfigTableApi);
				return;
			}
			free(sigtranM3uaLAspConfigTableApi);
			return;
      
    }
		else
		{
     LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: SigtranM3uaLAspConfigTable UNLOCK REQ rcvd");
      if(bssAdminState == LOCKED)
      {
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Bss is Locked,Only adminState is updated as UNLOCKED");
         //sendPspLockAlarm(sigtranM3uaLAspConfigTableApi);AlarmsToBeRaisedAfterWards
          sigtranM3uaLAspConfigTableApi->adminState = UNLOCKED; 
					if (updateSigtranM3uaLAspConfigTable(sigtranM3uaLAspConfigTableApi) != CLIB_SUCCESS)
					{
						 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In setM3uaLocalAspConfigTable() : updateSigtranM3uaLAspConfigTable Failed..");
						 //setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
             cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
						 free(sigtranM3uaLAspConfigTableApi);
						 return;
					}
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
         gStructAspStatusVar[i].gAdminState = unlocked;
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: After Updating AspId[%d] Admin State in DB as UNLOCKED::Updated gAdminState [%d]",sigtranM3uaLAspConfigTableApi->localAspId,gStructAspStatusVar[i].gAdminState);
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
         free(sigtranM3uaLAspConfigTableApi);
         cfgSendAckToCm();
         return;
      }
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
      if(gStructAspStatusVar[i].gAdminState == lockInProgress)
      {
					LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ASPID [%d] is lockInProgress,Operation not Possible",gStructAspStatusVar[i].localAspId);
					cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
					return;
      }
      if(gStructAspStatusVar[i].gAdminState == unlockInProgress)
      {
					LOG_PRINT(LOG_INFO,"IP_BSC_STACK: ASPID [%d] is Already unlockInProgress,Operation not Possible",gStructAspStatusVar[i].localAspId);
					cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
					return;
      }
		/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   	 setStackObject(BSC_API_SET_SIGTRANM3UALASPCONFIGTABLE, SCM_UNLOCK, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG);
		/* Frame and Send the message to the OIL */
			if (!fillAndSendOamScmM3uaLocalAspAdminConfig(UNLOCKED))
			{   
				sendStackProcRespToCm();
				free(sigtranM3uaLAspConfigTableApi);
				return;
			}
			free(sigtranM3uaLAspConfigTableApi);
			return;
		}
   }
   else
   {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Admin State rcvd same as in DB.. Sending ACK..");
     cfgSendAckToCm();
     free(sigtranM3uaLAspConfigTableApi);
     return;
   }
 }
 else
 {
  if(bssAdminState == UNLOCKED)
  {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
  }
 BssapIntfConfigTableApi *bssapIntfConfigTableApi=NULL;
 if(CLIB_SUCCESS != getallBssapIntfConfigTable(&bssapIntfConfigTableApi,&outCount,&outSize))
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: No Entry present in BssapIntfConfigTable() ..Sending NACK");
   cfgSendNackToCm(CM_ERR_SIGTRAN_BSSAP_INTF_TBL_NOT_PRESENT);
   return; 
 }
 free(bssapIntfConfigTableApi);
  SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = NULL;
  if(CLIB_SUCCESS != getallSigtranSccpCSPConfigTable(&sigtranSccpCSPConfigTableApi,&outCount,&outSize))
  {
  	 	LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Incomplete Configuration  SIGTRAN SCCP ");
      cfgSendNackToCm(CM_ERR_SIGTRAN_INCOMPLETE_SCCP_CONF);
      return;
  }
  free(sigtranSccpCSPConfigTableApi);
  if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outCount,&outSize))
  {
    if(outCount > 1)
    {
  	 	LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MAX rows [%d] ALREADY PRESENT",outCount);
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      return;
    }
	 	for(i = 0; i < outCount; ++i)
	 	{
	 	 tmpSigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)((I_U8 *)sigtranM3uaLAspConfigTableApi + i * outSize);
	 	 if(tmpSigtranM3uaLAspConfigTableApi->localAspId == receivedMsgPtr->localAspId)
	 	 {
	 		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:localAspId[%d]Already present in SigtranM3uaLAspConfigTable row[%d]",receivedMsgPtr->localAspId,i);
	 		 free(sigtranM3uaLAspConfigTableApi);
	 		 cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST);
	 		 return;
	 	 }
	 	}
	 	free(sigtranM3uaLAspConfigTableApi);
  }

    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of :SigtranM3uaLAspConfigTable for localAspId : [%d]",receivedMsgPtr->localAspId);

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranM3uaLAspConfigTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   	 setStackObject(BSC_API_SET_SIGTRANM3UALASPCONFIGTABLE, SCM_ADD, OAM_SCM_M3UA_LOCAL_ASP_CONFIG);

   /* Frame and Send the message to the OIL */
	 if (!fillAndSendOamScmM3uaLocalAspConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setM3uaLocalAspConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delM3uaLocalAspConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delM3uaLocalAspConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delM3uaLocalAspConfigTable() ..");
 SigtranM3uaLAspConfigTableApi *receivedMsgPtr = (SigtranM3uaLAspConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 //LOG_PRINT(DEBUG,"HEX DUMP from CM..");
 //PRINT_HEX_DUMP(LOG_DEBUG, receivedMsgPtr,sizeof(SigtranM3uaLAspConfigTableApi));
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = NULL;
 SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi=NULL,*tmpSigtranM3uaLAsConfigTableApi=NULL;
 //SigtranM3uaLAspConfigTableIndices *KeysPtr = (SigtranM3uaLAspConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranM3uaLAspConfigTableIndices KeysPtr;
 KeysPtr.localAspId = receivedMsgPtr->localAspId; 
 if ( CLIB_SUCCESS != getSigtranM3uaLAspConfigTable(&KeysPtr, &sigtranM3uaLAspConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranM3uaLAspConfigTable for localAspId[%d]",KeysPtr.localAspId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranM3uaLAspConfigTableApi);
 /*Check in SigtranM3uaLAsConfigTableApi for localAspId*/
 if(CLIB_SUCCESS == getallSigtranM3uaLAsConfigTable(&sigtranM3uaLAsConfigTableApi,&outCount,&outSize))
 {
  	for(i = 0; i < outCount; ++i)
  	{
  	 tmpSigtranM3uaLAsConfigTableApi = (SigtranM3uaLAsConfigTableApi *)((I_U8 *)sigtranM3uaLAsConfigTableApi+ i * outSize);
  	 if((tmpSigtranM3uaLAsConfigTableApi->localAspId1 == receivedMsgPtr->localAspId) || (tmpSigtranM3uaLAsConfigTableApi->localAspId2 == receivedMsgPtr->localAspId))
  	 {
  		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:localAspId[%d]Already present in SigtranM3uaLAsConfigTableApi",receivedMsgPtr->localAspId);
  		 free(sigtranM3uaLAsConfigTableApi);
       free(sigtranM3uaLAspConfigTableApi);
  		 cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_LOCAL_AS_TBL_PRESENT);
  		 return;
  	 }
  	}
  	free(sigtranM3uaLAsConfigTableApi);
 }
 /*Check in SigtranM3uaLAsConfigTableApi for localAspId*/
 SigtranM3uaRAspConfigTableApi *sigtranM3uaRAspConfigTableApi=NULL;
 if(CLIB_SUCCESS == getallSigtranM3uaRAspConfigTable(&sigtranM3uaRAspConfigTableApi,&outCount,&outSize))
 {
   free(sigtranM3uaRAspConfigTableApi);
   free(sigtranM3uaLAspConfigTableApi);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry present in sigtranM3uaRAspConfigTableApi() ..");
   cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_REMOTE_ASP_TBL_EXIST);
   return;
 }
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranM3uaLAspConfigTableApi, sizeof(SigtranM3uaLAspConfigTableApi)))
 {
    free(sigtranM3uaLAspConfigTableApi);
    return; 
 }
 free(sigtranM3uaLAspConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANM3UALASPCONFIGTABLE, SCM_DELETE, OAM_SCM_M3UA_LOCAL_ASP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaLocalAspConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delM3uaLocalAspConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setM3uaRemoteAspConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setM3uaRemoteAspConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setM3uaRemoteAspConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranM3uaRAspConfigTableApi *receivedMsgPtr = (SigtranM3uaRAspConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranM3uaRAspConfigTableApi *sigtranM3uaRAspConfigTableApi = NULL,*tmpSigtranM3uaRAspConfigTableApi=NULL;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaRAspConfigTable(&sigtranM3uaRAspConfigTableApi,&outCount,&outSize))
 {
    if(outCount > 1)
    {
 			LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MAX rows [%d] ALREADY PRESENT",outCount);
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      free(sigtranM3uaRAspConfigTableApi);
      return;
    }
  	for(i = 0; i < outCount; ++i)
  	{
  	 tmpSigtranM3uaRAspConfigTableApi = (SigtranM3uaRAspConfigTableApi *)((I_U8 *)sigtranM3uaRAspConfigTableApi + i * outSize);
  	 if(tmpSigtranM3uaRAspConfigTableApi->remAspId == receivedMsgPtr->remAspId)
  	 {
  		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:remAspId[%d]Already present in SigtranM3uaRAspConfigTable in row[%d]",receivedMsgPtr->remAspId,i);
  		 free(sigtranM3uaRAspConfigTableApi);
  		 cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST_MOD_NOT_ALLOWED);
  		 return;
  	 }
  	}
  free(sigtranM3uaRAspConfigTableApi);
 }
 SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = NULL;
 if(CLIB_SUCCESS != getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outCount,&outSize))
 {
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: sigtranM3uaLAspConfigTableApi NOT ADDED");
  cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_LOCAL_ASP_TBL_NOT_PRESENT);
  return;
 }
 free(sigtranM3uaLAspConfigTableApi);
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of :SigtranM3uaRAspConfigTable for remAspId: [%d]",receivedMsgPtr->remAspId);
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranM3uaRAspConfigTableApi)))
 {
    return; 
 }
 /* Set Stack object data structure */
 	 setStackObject(BSC_API_SET_SIGTRANM3UARASPCONFIGTABLE, SCM_ADD, OAM_SCM_M3UA_REMOTE_ASP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaRemoteAspConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setM3uaRemoteAspConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delM3uaRemoteAspConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delM3uaRemoteAspConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delM3uaRemoteAspConfigTable() ..");
 SigtranM3uaRAspConfigTableApi  *receivedMsgPtr = (SigtranM3uaRAspConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 SigtranM3uaRAspConfigTableApi *sigtranM3uaRAspConfigTableApi= NULL;
 SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi=NULL,*tmpSigtranM3uaRAsConfigTableApi=NULL;
 SigtranM3uaRAspConfigTableIndices *KeysPtr = (SigtranM3uaRAspConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranM3uaRAspConfigTable(KeysPtr, &sigtranM3uaRAspConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranM3uaRAspConfigTable for remAspId[%d]",KeysPtr->remAspId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranM3uaRAspConfigTableApi);
 SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi=NULL;
 if(CLIB_SUCCESS == getallSigtranM3uaLAsConfigTable(&sigtranM3uaLAsConfigTableApi,&outCount,&outSize))
 {
  free(sigtranM3uaLAsConfigTableApi);
  free(sigtranM3uaRAspConfigTableApi);
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry present in SigtranM3uaLAsConfigTableApi: Sending NACK...");
  cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_LOCAL_AS_TABLE_EXISTS);
  return FALSE;
 }
 /*Check in SigtranM3uaRAsConfigTableApi for remAspId*/
 if(CLIB_SUCCESS == getallSigtranM3uaRAsConfigTable(&sigtranM3uaRAsConfigTableApi,&outCount,&outSize))
 {
  	for(i = 0; i < outCount; ++i)
  	{
  	 tmpSigtranM3uaRAsConfigTableApi = (SigtranM3uaRAsConfigTableApi *)((I_U8 *)sigtranM3uaRAsConfigTableApi+ i * outSize);
  	 if((tmpSigtranM3uaRAsConfigTableApi->remAspId1 == receivedMsgPtr->remAspId) || (tmpSigtranM3uaRAsConfigTableApi->remAspId2 == receivedMsgPtr->remAspId))
  	 {
  		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:remAspId[%d]Already present in SigtranM3uaRAsConfigTableApi",receivedMsgPtr->remAspId);
  		 free(sigtranM3uaRAsConfigTableApi);
       free(sigtranM3uaRAspConfigTableApi);
  		 cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_REMOTE_AS_TBL_EXIST);
  		 return;
  	 }
  	}
  	free(sigtranM3uaRAsConfigTableApi);
 }
 /*Check in SigtranM3uaRAsConfigTableApi for remAspId*/
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranM3uaRAspConfigTableApi, sizeof(SigtranM3uaRAspConfigTableApi)))
 {
    free(sigtranM3uaRAspConfigTableApi);
    return; 
 }
 free(sigtranM3uaRAspConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANM3UARASPCONFIGTABLE, SCM_DELETE, OAM_SCM_M3UA_REMOTE_ASP_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaRemoteAspConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delM3uaRemoteAspConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setM3uaLocalAsConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setM3uaLocalAsConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setM3uaLocalAsConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranM3uaLAsConfigTableApi *receivedMsgPtr = (SigtranM3uaLAsConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaLAsConfigTable(&sigtranM3uaLAsConfigTableApi,&outCount,&outSize))
 {
    if(outCount > 0)
    {
 			LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MAX row [%d] ALREADY PRESENT: NOT MODIABLE : SENDING NACK",outCount);
      cfgSendNackToCm(CM_ERR_SIGTRAN_ENTRY_ALREADY_EXIST_MOD_NOT_ALLOWED);
      free(sigtranM3uaLAsConfigTableApi);
      return;
    }
  free(sigtranM3uaLAsConfigTableApi);
 }
 SigtranM3uaRAspConfigTableApi *sigtranM3uaRAspConfigTableApi=NULL;
 if(CLIB_SUCCESS != getallSigtranM3uaRAspConfigTable(&sigtranM3uaRAspConfigTableApi,&outCount,&outSize))
 {
 	LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry not exits in sigtranM3uaRAspConfigTableApi");
  cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_REMOTE_ASP_TBL_NOT_PRESENT);
  return;
 }
 free(sigtranM3uaRAspConfigTableApi);
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of :SigtranM3uaLAsConfigTableApi for localAsId : [%d]",receivedMsgPtr->localAsId);
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranM3uaLAsConfigTableApi)))
 {
    return; 
 }
 /* Set Stack object data structure */
 	 setStackObject(BSC_API_SET_SIGTRANM3UALASCONFIGTABLE, SCM_ADD, OAM_SCM_M3UA_LOCAL_AS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaLocalAsConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setM3uaLocalAsConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delM3uaLocalAsConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delM3uaLocalAsConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delM3uaLocalAsConfigTable() ..");
 SigtranM3uaLAsConfigTableApi *receivedMsgPtr = ( SigtranM3uaLAsConfigTableApi*)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi = NULL;
 SigtranM3uaLAsConfigTableIndices *KeysPtr = (SigtranM3uaLAsConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranM3uaLAsConfigTable(KeysPtr, &sigtranM3uaLAsConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranM3uaLAsConfigTable for localAsId[%d]",KeysPtr->localAsId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi=NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaRAsConfigTable(&sigtranM3uaRAsConfigTableApi,&outCount,&outSize))
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry Present in SigtranM3uaRAsConfigTableApi: SENDING NACK() ..");
   cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_REMOTE_AS_TBL_EXIST);
   free(sigtranM3uaRAsConfigTableApi);
   free(sigtranM3uaLAsConfigTableApi);
   return;
 }
 //free(sigtranM3uaLAsConfigTableApi);
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranM3uaLAsConfigTableApi, sizeof(SigtranM3uaLAsConfigTableApi)))
 {
    free(sigtranM3uaLAsConfigTableApi);
    return; 
 }
 free(sigtranM3uaLAsConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANM3UALASCONFIGTABLE, SCM_DELETE, OAM_SCM_M3UA_LOCAL_AS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaLocalAsConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delM3uaLocalAsConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setM3uaRemoteAsConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setM3uaRemoteAsConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setM3uaRemoteAsConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranM3uaRAsConfigTableApi *receivedMsgPtr = (SigtranM3uaRAsConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaRAsConfigTable(&sigtranM3uaRAsConfigTableApi,&outCount,&outSize))
 {
    if(outCount > 0)
    {
 			LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MAX row [%d] ALREADY PRESENT: NOT MODIABLE : SENDING NACK",outCount);
      cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
      free(sigtranM3uaRAsConfigTableApi);
      return;
    }
  free(sigtranM3uaRAsConfigTableApi);
 }
 SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi=NULL;
 if(CLIB_SUCCESS != getallSigtranM3uaLAsConfigTable(&sigtranM3uaLAsConfigTableApi,&outCount,&outSize))
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry Not Present in SigtranM3uaLAsConfigTableApi : SENDING NACK() ..");
   cfgSendNackToCm(CM_ERR_SIGTRAN_M3UA_LOCAL_AS_TBL_NOT_PRESENT);
   return;
 }
 free(sigtranM3uaLAsConfigTableApi);
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of :SigtranM3uaRAsConfigTableApi for remAsId: [%d]",receivedMsgPtr->remAsId);
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranM3uaRAsConfigTableApi)))
 {
    return; 
 }
 /* Set Stack object data structure */
 	 setStackObject(BSC_API_SET_SIGTRANM3UARASCONFIGTABLE, SCM_ADD, OAM_SCM_M3UA_REMOTE_AS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaRemoteAsConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setM3uaRemoteAsConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delM3uaRemoteAsConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delM3uaRemoteAsConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delM3uaRemoteAsConfigTable() ..");
 SigtranM3uaRAsConfigTableApi *receivedMsgPtr = ( SigtranM3uaRAsConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi = NULL;
 SigtranM3uaRAsConfigTableIndices *KeysPtr = (SigtranM3uaRAsConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranM3uaRAsConfigTable(KeysPtr, &sigtranM3uaRAsConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranM3uaLAsConfigTable for remAsId[%d]",KeysPtr->remAsId);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranM3uaRAsConfigTableApi);
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranM3uaRAsConfigTableApi, sizeof(SigtranM3uaRAsConfigTableApi)))
 {
    free(sigtranM3uaRAsConfigTableApi);
    return; 
 }
 free(sigtranM3uaRAsConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_DEL_SIGTRANM3UARASCONFIGTABLE, SCM_DELETE, OAM_SCM_M3UA_REMOTE_AS_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmM3uaRemoteAsConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delM3uaRemoteAsConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : setSctpConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setSctpConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSctpConfigTable() ..");
 I_U32 bssAdminState = ZERO;
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSctpConfigTableApi *receivedMsgPtr = ( SigtranSctpConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranSctpConfigTableApi *sigtranSctpConfigTableApi = NULL;
 I_U32 outCount = ZERO;
 I_U16 outSize = ZERO;
 SigtranSctpConfigTableIndices key;
 key.dummyIndex = receivedMsgPtr->dummyIndex;
 if(CLIB_SUCCESS==getSigtranSctpConfigTable(&key,&sigtranSctpConfigTableApi))
 //if(CLIB_SUCCESS == getallSigtranSctpConfigTable(&sigtranSctpConfigTableApi,&outCount,&outSize))
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry ALREADY present in SigtranSctpConfigTable() ..MODIFY REQ Rcvd going for RangeCheck..");
   free(sigtranSctpConfigTableApi);
   //cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
   //return; 
		/* Perform range check on received parameters */
		if(!sctpConfigRangeChk(receivedMsgPtr))
		{
		 cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
		 return; 
		}
		/* Store the received message in global pointer */
		if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSctpConfigTableApi)))
		{
		 	return; 
		}
    /* Set Stack object data structure */
    setStackObject(BSC_API_SET_SIGTRANSCTPCONFIGTABLE, SCM_MODIFY, OAM_SCM_SCTP_GEN_CONFIG);
		/* Frame and Send the message to the OIL */
		if (!fillAndSendOamScmSctpConfig())
		{
		 	sendStackProcRespToCm();
		 	return;
		}
 }
 else
 {
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSctpConfigTable(): ");
		if(CLIB_SUCCESS == getallSigtranSctpConfigTable(&sigtranSctpConfigTableApi,&outCount,&outSize))
		{
		  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entry ALREADY present in SigtranSctpConfigTable() ..Sending NACK.. for dummyIndex[%d]",receivedMsgPtr->dummyIndex);
		  free(sigtranSctpConfigTableApi);
		  cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
		  return;
    }
    BssapIntfConfigTableApi *bssapIntfConfigTableApi=NULL; 
		if(CLIB_SUCCESS != getallBssapIntfConfigTable(&bssapIntfConfigTableApi,&outCount,&outSize))
		{
		  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: No Entry present in BssapIntfConfigTable() ..Sending NACK");
		  cfgSendNackToCm(CM_ERR_SIGTRAN_BSSAP_INTF_TBL_NOT_PRESENT);
		  return; 
		}
    free(bssapIntfConfigTableApi);
		SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = NULL;
		if(CLIB_SUCCESS != getallSigtranSccpCSPConfigTable(&sigtranSccpCSPConfigTableApi,&outCount,&outSize))
		{
				LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Incomplete Configuration SIGTRAN SCCP: Sending NACK...");
				cfgSendNackToCm(CM_ERR_SIGTRAN_INCOMPLETE_SCCP_CONF);
				return;
		}
		free(sigtranSccpCSPConfigTableApi);
    SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi=NULL;
		if(CLIB_SUCCESS != getallSigtranM3uaRAsConfigTable(&sigtranM3uaRAsConfigTableApi,&outCount,&outSize))
		{
      LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: INCOMPLETE M3UA CONFIG(): sending NACK..");
		  cfgSendNackToCm(CM_ERR_SIGTRAN_INCOMPLETE_M3UA_CONF);
		  return;
		}
		free(sigtranM3uaRAsConfigTableApi);
   /* Perform range check on received parameters */
		if(!sctpConfigRangeChk(receivedMsgPtr))
		{
		 cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
		 return; 
		}

		/* Store the received message in global pointer */
		if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSctpConfigTableApi)))
		{
		 	return; 
		}
		/* Set Stack object data structure */
		setStackObject(BSC_API_SET_SIGTRANSCTPCONFIGTABLE, SCM_ADD, OAM_SCM_SCTP_GEN_CONFIG);

		/* Frame and Send the message to the OIL */
		if (!fillAndSendOamScmSctpConfig())
		{
		 	sendStackProcRespToCm();
		 	return;
		}
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSctpConfigTable() ..");
}	
/******************************* Function  Header*****************************
Function Name : delSctpConfigTable()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void delSctpConfigTable()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delSctpConfigTable() ..");
 SigtranSctpConfigTableApi *receivedMsgPtr = ( SigtranSctpConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranSctpConfigTableApi *sigtranSctpConfigTableApi = NULL;
 SigtranSctpConfigTableIndices *KeysPtr = (SigtranSctpConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 if ( CLIB_SUCCESS != getSigtranSctpConfigTable(KeysPtr, &sigtranSctpConfigTableApi)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getSigtranSctpConfigTable for dummyIndex [%d]",KeysPtr->dummyIndex);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }
 //free(sigtranSctpConfigTableApi);
 /* Store the received message in global pointer */
 if (!storeReceivedMsgBuffer(sigtranSctpConfigTableApi, sizeof(SigtranSctpConfigTableApi)))
 {
    free(sigtranSctpConfigTableApi);
    return; 
 }
 free(sigtranSctpConfigTableApi);

 /* Set Stack object data structure */
 setStackObject(BSC_API_SET_SIGTRANSCTPCONFIGTABLE, SCM_DELETE, OAM_SCM_SCTP_GEN_CONFIG);

 /* Frame and Send the message to the OIL */
 if (!fillAndSendOamScmSctpConfig())
 {
    sendStackProcRespToCm();
    return;
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delSctpConfigTable() ..");
}
/******************************* Function  Header*****************************
Function Name : isDelBssapTimerConfigTableAllowed()
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void isDelBssapTimerConfigTableAllowed()	
{
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering isDelBssapTimerConfigTableAllowed() ..");
 BssapTmrConfigTableApi *BssapTmrConfigTableApiPtr = NULL;
 BssapTmrConfigTableIndices *KeysPtr = (BssapTmrConfigTableIndices *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));

 BssapIntfConfigTableApi *bssapIntfConfigPtr=NULL, *tmpbssapIntfConfigPtr=NULL;
 I_U32 outRows=0, i=0;
 I_U16 outSize=0;

 if ( CLIB_SUCCESS != getBssapTmrConfigTable(KeysPtr, &BssapTmrConfigTableApiPtr)) {
    LOG_PRINT(LOG_INFO, "IP_BSC_STACK: Entry does not exits getBssapTmrConfigTable for profileId [%d]",KeysPtr->profileID);
    //setFailCauseInStackObj(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    cfgSendNackToCm(CM_ERR_ENTRY_NOT_PRES_IN_DB);
    return FALSE;
 }

 // Check Entry in Bssap I/f Table
 if(CLIB_SUCCESS == getallBssapIntfConfigTable(&bssapIntfConfigPtr, &outRows, &outSize))
  {
    for(i = 0; i < outRows; ++i)
     {
       tmpbssapIntfConfigPtr = (BssapIntfConfigTableApi *)((I_U8 *)bssapIntfConfigPtr + i * outSize);

       if(tmpbssapIntfConfigPtr->timerProfileId == KeysPtr->profileID)
        {
          LOG_PRINT(DEBUG,"S: profileId=%d exists in BssapIntfConfigTableApi", KeysPtr->profileID);
          free(bssapIntfConfigPtr);
          free(BssapTmrConfigTableApiPtr);
          //setFailCauseInStackObj(CM_ERR_AIFINTERFACE_OBJ_EXISTS);
          cfgSendNackToCm(CM_ERR_AIFINTERFACE_OBJ_EXISTS);
          return FALSE;

        }
     }
    free(bssapIntfConfigPtr);
  }
 if ( ! storeReceivedMsgBuffer(BssapTmrConfigTableApiPtr, sizeof(BssapTmrConfigTableApi)) ) {
    free(BssapTmrConfigTableApiPtr);
    return FALSE;
 }

 free(BssapTmrConfigTableApiPtr);
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting isDelBssapTimerConfigTableAllowed() ..");
 return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmBsTimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmBsTimerConfig(I_Void)
{
   OamScmBsTimerConfig bsTimerConfig;
   BssapTmrConfigTableApi *bssapTmrConfigTableApi = (BssapTmrConfigTableApi *)gStoredMsgBufPtr;

   bsTimerConfig.profileId = bssapTmrConfigTableApi->profileID;
   bsTimerConfig.timer_T1  = bssapTmrConfigTableApi->timer_T1;
   bsTimerConfig.timer_T4  = bssapTmrConfigTableApi->timer_T4;
   bsTimerConfig.timer_T10 = bssapTmrConfigTableApi->timer_T10;
   bsTimerConfig.timer_T11 = bssapTmrConfigTableApi->timer_T11;
   bsTimerConfig.timer_T17 = bssapTmrConfigTableApi->timer_T17;
   bsTimerConfig.timer_T18 = bssapTmrConfigTableApi->timer_T18;
   bsTimerConfig.timer_T25 = bssapTmrConfigTableApi->timer_T25;
   bsTimerConfig.timer_Trbsc = bssapTmrConfigTableApi->timer_Trbsc;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_BS_TIMER_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&bsTimerConfig, sizeof(bsTimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSccpTmrConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSccpTmrConfig(I_Void)
{
   OamScmSccpTmrConfig sccpTimerConfig;
   SigtranSccpTimerTableApi *sigtranSccpTimerTableApi= (SigtranSccpTimerTableApi *)gStoredMsgBufPtr;

   sccpTimerConfig.profileId   = sigtranSccpTimerTableApi->profileId;
   sccpTimerConfig.treass      = sigtranSccpTimerTableApi->treass;
   sccpTimerConfig.tstatinfo   = sigtranSccpTimerTableApi->tstatinfo;
   sccpTimerConfig.tcongattack = sigtranSccpTimerTableApi->tcongattack;
   sccpTimerConfig.tcongdecay  = sigtranSccpTimerTableApi->tcongdecay;
   sccpTimerConfig.segparmz    = sigtranSccpTimerTableApi->segparmz;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_SCCP_TMR_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sccpTimerConfig, sizeof(sccpTimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
} 
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmM3uaTimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmM3uaTimerConfig(I_Void)
{
   OamScmM3uaTimerConfig m3uaTimerConfig;
   M3uaTmrConfigTableApi *m3uaTmrConfigTableApi = (M3uaTmrConfigTableApi *)gStoredMsgBufPtr;

   m3uaTimerConfig.profileId      = m3uaTmrConfigTableApi->profileId;
   m3uaTimerConfig.tmrAsPend      = m3uaTmrConfigTableApi->tmrAsPend;
   m3uaTimerConfig.tmrRetransLow  = m3uaTmrConfigTableApi->tmrRetransLow;
   m3uaTimerConfig.tmrRetransHigh = m3uaTmrConfigTableApi->tmrRetransHigh;
   m3uaTimerConfig.tmrRetransMax  = m3uaTmrConfigTableApi->tmrRetransMax;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_M3UA_TIMER_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&m3uaTimerConfig, sizeof(m3uaTimerConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSctpTimerConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSctpTimerConfig(I_Void)
{
	OamScmSctpTimerConfig sctpTimerConfig;
  SigtranSctpTimerTableApi *sigtranSctpTimerTableApi = (OamScmSctpTimerConfig *)gStoredMsgBufPtr;
  
  sctpTimerConfig.profileId         = sigtranSctpTimerTableApi->profileId; 
  sctpTimerConfig.rto_init          = sigtranSctpTimerTableApi->rto_init; 
  sctpTimerConfig.rto_min           = sigtranSctpTimerTableApi->rto_min; 
  sctpTimerConfig.rto_max           = sigtranSctpTimerTableApi->rto_max; 
  sctpTimerConfig.rto_alpha_percent = sigtranSctpTimerTableApi->rto_alpha_percent; 
  sctpTimerConfig.rto_beta_percent  = sigtranSctpTimerTableApi->rto_beta_percent; 
  sctpTimerConfig.valid_cookie_life = sigtranSctpTimerTableApi->valid_cookie_life; 
  sctpTimerConfig.hb_interval = sigtranSctpTimerTableApi->hb_interval; 
  
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_SCTP_TIMER_CONFIG to Oil..");

  if ( cfgSendStackMessage((I_Void *)&sctpTimerConfig, sizeof(sctpTimerConfig) ) != CFG_SUCCESS ){
     return FALSE;
  }
  return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSctpConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSctpConfig(I_Void)
{
   OamScmSctpConfig sctpConfig; 
   SigtranSctpConfigTableApi *sigtranSctpConfigTableApi = (SigtranSctpConfigTableApi *)gStoredMsgBufPtr;

   //sctpConfig.dummyIndex          = sigtranSctpConfigTableApi->dummyIndex;
   sctpConfig.assoc_max_retrans   = sigtranSctpConfigTableApi->assoc_max_retrans;
   sctpConfig.path_max_retrans    = sigtranSctpConfigTableApi->path_max_retrans;
   sctpConfig.max_init_retrans    = sigtranSctpConfigTableApi->max_init_retrans;
   sctpConfig.timerProfileId      = sigtranSctpConfigTableApi->timerProfileId;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_SCTP_GEN_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sctpConfig, sizeof(sctpConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmBsInterfaceConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmBsInterfaceConfig(I_Void)
{
   OamScmBsInterfaceConfig bsIntfConfig; //sctpConfig; 
   BssapIntfConfigTableApi *bssapIntfConfigTableApi = (BssapIntfConfigTableApi *)gStoredMsgBufPtr;

   bsIntfConfig.bscId          = bssapIntfConfigTableApi->bscId;
   bsIntfConfig.interfaceType  = bssapIntfConfigTableApi->interfaceType;
   bsIntfConfig.ni             = bssapIntfConfigTableApi->ni;
   memcpy(bsIntfConfig.name,bssapIntfConfigTableApi->name,20);
   bsIntfConfig.opc            = bssapIntfConfigTableApi->opc;
   bsIntfConfig.dpc            = bssapIntfConfigTableApi->dpc;
   bsIntfConfig.variant        = bssapIntfConfigTableApi->variant;
   bsIntfConfig.timerProfileId = bssapIntfConfigTableApi->timerProfileId;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_BS_INTERFACE_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&bsIntfConfig, sizeof(bsIntfConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSccpSpConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSccpSpConfig(I_Void)
{
   OamScmSccpSpConfig sccpSpConfig; 
   SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi = (SigtranSccpSPConfigTableApi *)gStoredMsgBufPtr;

   sccpSpConfig.spId      = sigtranSccpSPConfigTableApi->spId;
   sccpSpConfig.nwId      = sigtranSccpSPConfigTableApi->nwId;
   sccpSpConfig.pointCode = sigtranSccpSPConfigTableApi->pointCode;
   sccpSpConfig.local     = sigtranSccpSPConfigTableApi->local;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_SCCP_SP_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sccpSpConfig, sizeof(sccpSpConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSccpSsConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSccpSsConfig(I_Void)
{
   OamScmSccpSsConfig sccpSsConfig; 
   SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = (SigtranSccpSSConfigTableApi *)gStoredMsgBufPtr;

   sccpSsConfig.ssId      = sigtranSccpSSConfigTableApi->ssId;
   sccpSsConfig.spId      = sigtranSccpSSConfigTableApi->spId;
   sccpSsConfig.ssn       = sigtranSccpSSConfigTableApi->ssn;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_SCCP_SS_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sccpSsConfig, sizeof(sccpSsConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSccpCssConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSccpCssConfig(I_Void)
{
   OamScmSccpCssConfig sccpCssConfig; 
   SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi = (SigtranSccpCSSConfigTableApi *)gStoredMsgBufPtr;

   sccpCssConfig.ssId      =  sigtranSccpCSSConfigTableApi->ssId;
   sccpCssConfig.cssId     =  sigtranSccpCSSConfigTableApi->cssId;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending  OAM_SCM_SCCP_CSS_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sccpCssConfig, sizeof(sccpCssConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmSccpCspConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmSccpCspConfig(I_Void)
{
   OamScmSccpCspConfig sccpCspConfig; 
   SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = (SigtranSccpCSPConfigTableApi *)gStoredMsgBufPtr;

   sccpCspConfig.ssId           =  sigtranSccpCSPConfigTableApi->ssId;
   sccpCspConfig.cspId          =  sigtranSccpCSPConfigTableApi->cspId;
   sccpCspConfig.timerProfileId =  sigtranSccpCSPConfigTableApi->timerProfileId;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending  OAM_SCM_SCCP_CSS_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&sccpCspConfig, sizeof(sccpCspConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmM3uaLocalAspConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmM3uaLocalAspConfig(I_Void)
{
   OamScmM3uaLocalAspConfig m3uaLocalAspConfig; 
   SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)gStoredMsgBufPtr;
   //LOG_PRINT(DEBUG,"HEX DUMP of gStoredMsgBufPtr ..");
   //PRINT_HEX_DUMP(LOG_DEBUG, gStoredMsgBufPtr,sizeof(SigtranM3uaLAspConfigTableApi));

   m3uaLocalAspConfig.localAspId   =  sigtranM3uaLAspConfigTableApi->localAspId;
   m3uaLocalAspConfig.localPort    =  sigtranM3uaLAspConfigTableApi->localPort;
   memcpy(m3uaLocalAspConfig.localIp,sigtranM3uaLAspConfigTableApi->localIp,25);
   memcpy(m3uaLocalAspConfig.name,sigtranM3uaLAspConfigTableApi->name,20);
   m3uaLocalAspConfig.slotId       =  sigtranM3uaLAspConfigTableApi->slotId;
   m3uaLocalAspConfig.assocType    =  sigtranM3uaLAspConfigTableApi->assocType;
   m3uaLocalAspConfig.maxInStream  =  sigtranM3uaLAspConfigTableApi->maxInStream;
   m3uaLocalAspConfig.maxOutStream =  sigtranM3uaLAspConfigTableApi->maxOutStream;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_M3UA_LOCAL_ASP_CONFIG to Oil.. AspId[%d]",m3uaLocalAspConfig.localAspId);
   //LOG_PRINT(DEBUG,"HEX DUMP of m3uaLocalAspConfig .. being sent to OIL...");
   //PRINT_HEX_DUMP(LOG_DEBUG,&m3uaLocalAspConfig,sizeof(SigtranM3uaLAspConfigTableApi));

   if ( cfgSendStackMessage((I_Void *)&m3uaLocalAspConfig, sizeof(m3uaLocalAspConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmM3uaLocalAspAdminConfig(I_U16 adminState)
Parameters    : I_U16 adminState 
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmM3uaLocalAspAdminConfig(I_U16 adminState)
{
   OamScmM3uaLocalAspAdminConfig m3uaLocalAspAdminConfig; 
   SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)gStoredMsgBufPtr;

   m3uaLocalAspAdminConfig.localAspId   =  sigtranM3uaLAspConfigTableApi->localAspId;
   m3uaLocalAspAdminConfig.adminState   =  adminState;
   
   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending  OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG to Oil.. AspId [%d]AdminState [%d]",m3uaLocalAspAdminConfig.localAspId,m3uaLocalAspAdminConfig.adminState);

   if ( cfgSendStackMessage((I_Void *)&m3uaLocalAspAdminConfig, sizeof(m3uaLocalAspAdminConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   setStatusAspLocal(sigtranM3uaLAspConfigTableApi->localAspId,adminState,STK_REQUEST);
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmM3uaRemoteAspConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmM3uaRemoteAspConfig(I_Void)
{
   OamScmM3uaRemoteAspConfig m3uaRemoteAspConfig; 
   SigtranM3uaRAspConfigTableApi *sigtranM3uaRAspConfigTableApi = (SigtranM3uaRAspConfigTableApi *)gStoredMsgBufPtr;

   m3uaRemoteAspConfig.remAspId  =  sigtranM3uaRAspConfigTableApi->remAspId;
   m3uaRemoteAspConfig.remotePort=  sigtranM3uaRAspConfigTableApi->remotePort;
   memcpy(m3uaRemoteAspConfig.name,sigtranM3uaRAspConfigTableApi->name,20);
   memcpy(m3uaRemoteAspConfig.remoteIp,sigtranM3uaRAspConfigTableApi->remoteIp,25);

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_M3UA_REMOTE_ASP_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&m3uaRemoteAspConfig, sizeof(m3uaRemoteAspConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmM3uaLocalAsConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmM3uaLocalAsConfig(I_Void)
{
   OamScmM3uaLocalAsConfig m3uaLocalAsConfig; 
   SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi = (SigtranM3uaLAsConfigTableApi *)gStoredMsgBufPtr;

   m3uaLocalAsConfig.localAsId       =  sigtranM3uaLAsConfigTableApi->localAsId;
   m3uaLocalAsConfig.asMode          =  sigtranM3uaLAsConfigTableApi->asMode;
   m3uaLocalAsConfig.sourcePointCode =  sigtranM3uaLAsConfigTableApi->sourcePointCode;
   m3uaLocalAsConfig.rkType          =  sigtranM3uaLAsConfigTableApi->rkType;
   m3uaLocalAsConfig.numAsp          =  sigtranM3uaLAsConfigTableApi->numAsp;
   m3uaLocalAsConfig.localAspId1     =  sigtranM3uaLAsConfigTableApi->localAspId1;
   m3uaLocalAsConfig.localAspId2     =  sigtranM3uaLAsConfigTableApi->localAspId2;
   m3uaLocalAsConfig.numbRc          =  sigtranM3uaLAsConfigTableApi->numbRc;
   m3uaLocalAsConfig.remAspRc1       =  sigtranM3uaLAsConfigTableApi->remAspRc1;
   m3uaLocalAsConfig.remAspRc2       =  sigtranM3uaLAsConfigTableApi->remAspRc2;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_M3UA_LOCAL_AS_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&m3uaLocalAsConfig, sizeof(m3uaLocalAsConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : fillAndSendOamScmM3uaRemoteAsConfig()
Parameters    : None
Return type   : I_Bool
Purpose       : fill and Send the message to the OIL 
Other Note    : Added For IP_BSC_STACK
 *****************************************************************************/
I_Bool fillAndSendOamScmM3uaRemoteAsConfig(I_Void)
{
   OamScmM3uaRemoteAsConfig m3uaRemoteAsConfig; 
   SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi = (SigtranM3uaRAsConfigTableApi *)gStoredMsgBufPtr;

   m3uaRemoteAsConfig.remAsId          =  sigtranM3uaRAsConfigTableApi->remAsId;
   m3uaRemoteAsConfig.remAsMode        =  sigtranM3uaRAsConfigTableApi->remAsMode;
   m3uaRemoteAsConfig.remPointCode     =  sigtranM3uaRAsConfigTableApi->remPointCode;
   m3uaRemoteAsConfig.rkType           =  sigtranM3uaRAsConfigTableApi->rkType;
   m3uaRemoteAsConfig.numAsp           =  sigtranM3uaRAsConfigTableApi->numAsp;
   m3uaRemoteAsConfig.remAspId1        =  sigtranM3uaRAsConfigTableApi->remAspId1;
   m3uaRemoteAsConfig.remAspId2        =  sigtranM3uaRAsConfigTableApi->remAspId2;
   m3uaRemoteAsConfig.timerProfileId   =  sigtranM3uaRAsConfigTableApi->timerProfileId;

   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Sending OAM_SCM_M3UA_REMOTE_AS_CONFIG to Oil..");

   if ( cfgSendStackMessage((I_Void *)&m3uaRemoteAsConfig, sizeof(m3uaRemoteAsConfig) ) != CFG_SUCCESS ){
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
  Function Name : bssapTmrConfigRangeChk()
Parameters    : BssapTmrConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_BSSAPTMRCONFIGTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool bssapTmrConfigRangeChk(BssapTmrConfigTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->timer_T1 < 1) || (receivedMsgPtr->timer_T1 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T1: %d",
            receivedMsgPtr->timer_T1);
      return FALSE;
   }
   if((receivedMsgPtr->timer_T4 < 1) || (receivedMsgPtr->timer_T4 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T4: %d",
            receivedMsgPtr->timer_T4);
      return FALSE;
   }
   if((receivedMsgPtr->timer_T10 < 1) || (receivedMsgPtr->timer_T10 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T10: %d",
            receivedMsgPtr->timer_T4);
      return FALSE;
   }
   if((receivedMsgPtr->timer_T11 < 1) || (receivedMsgPtr->timer_T11 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T11: %d",
            receivedMsgPtr->timer_T11);
      return FALSE;
   }
   if((receivedMsgPtr->timer_T13 < 1) || (receivedMsgPtr->timer_T13 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T13: %d",
            receivedMsgPtr->timer_T13);
      return FALSE;
   }
   if((receivedMsgPtr->timer_T17 < 1) || (receivedMsgPtr->timer_T17 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T17: %d",
            receivedMsgPtr->timer_T17);
      return FALSE;
   }
   if((receivedMsgPtr->timer_T25 < 1) || (receivedMsgPtr->timer_T25 > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_T25: %d",
            receivedMsgPtr->timer_T25);
      return FALSE;
   }
   if((receivedMsgPtr->timer_Trbsc < 1) || (receivedMsgPtr->timer_Trbsc > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapTmrConfigRangeChk: Range Check Failed - timer_Trbsc: %d",
            receivedMsgPtr->timer_Trbsc);
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : sccpTmrConfigRangeChk()
Parameters    : SigtranSccpTimerTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SIGTRANSCCPTIMERTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool sccpTmrConfigRangeChk(SigtranSccpTimerTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->treass < 1) || (receivedMsgPtr->treass > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - treass: %d",
            receivedMsgPtr->treass);
      return FALSE;
   }
   if((receivedMsgPtr->tstatinfo < 1) || (receivedMsgPtr->tstatinfo > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tstatinfo: %d",
            receivedMsgPtr->tstatinfo);
      return FALSE;
	 }
   if((receivedMsgPtr->tcongattack < 1) || (receivedMsgPtr->tcongattack > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tcongattack: %d",
            receivedMsgPtr->tcongattack);
      return FALSE;
	 }
   if((receivedMsgPtr->tcongdecay < 1) || (receivedMsgPtr->tcongdecay > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tcongdecay: %d",
            receivedMsgPtr->tcongdecay);
      return FALSE;
	 }
   if((receivedMsgPtr->segparmz < 1) || (receivedMsgPtr->segparmz > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - segparmz: %d",
            receivedMsgPtr->segparmz);
      return FALSE;
	 }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : m3uaTmrConfigRangeChk()
Parameters    : M3uaTmrConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_M3UATMRCONFIGTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool m3uaTmrConfigRangeChk(M3uaTmrConfigTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->tmrAsPend < 1) || (receivedMsgPtr->tmrAsPend > 60))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tmrAsPend: %d",
            receivedMsgPtr->tmrAsPend);
      return FALSE;
   }
   if((receivedMsgPtr->tmrRetransLow < 1) || (receivedMsgPtr->tmrRetransLow > 2))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tmrRetransLow: %d",
            receivedMsgPtr->tmrRetransLow);
      return FALSE;
   }
   if((receivedMsgPtr->tmrRetransHigh < 1) || (receivedMsgPtr->tmrRetransHigh > 5))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tmrRetransHigh: %d",
            receivedMsgPtr->tmrRetransHigh);
      return FALSE;
   }
   if((receivedMsgPtr->tmrRetransMax < 1) || (receivedMsgPtr->tmrRetransMax > 20))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpTmrConfigRangeChk: Range Check Failed - tmrRetransMax: %d",
            receivedMsgPtr->tmrRetransMax);
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : sctpTmrConfigRangeChk()
Parameters    : SigtranSctpTimerTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SIGTRANSCTPTIMERTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool sctpTmrConfigRangeChk(SigtranSctpTimerTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->rto_init < 1) || (receivedMsgPtr->rto_init > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - rto_init: %d",
            receivedMsgPtr->rto_init);
      return FALSE;
   }
   if((receivedMsgPtr->rto_min < 1) || (receivedMsgPtr->rto_min > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - rto_min: %d",
            receivedMsgPtr->rto_min);
      return FALSE;
   }
   if((receivedMsgPtr->rto_max < 1) || (receivedMsgPtr->rto_max > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - rto_max: %d",
            receivedMsgPtr->rto_max);
      return FALSE;
   }
   if((receivedMsgPtr->rto_alpha_percent < 1) || (receivedMsgPtr->rto_alpha_percent > 100))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - rto_alpha_percent: %d",
            receivedMsgPtr->rto_alpha_percent);
      return FALSE;
   }
   if((receivedMsgPtr->rto_beta_percent < 1) || (receivedMsgPtr->rto_beta_percent > 100))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - rto_beta_percent: %d",
            receivedMsgPtr->rto_beta_percent);
      return FALSE;
   }
   if((receivedMsgPtr->valid_cookie_life < 1) || (receivedMsgPtr->valid_cookie_life > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - valid_cookie_life: %d",
            receivedMsgPtr->valid_cookie_life);
      return FALSE;
   }
   if((receivedMsgPtr->hb_interval < 1) || (receivedMsgPtr->hb_interval > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpTmrConfigRangeChk: Range Check Failed - hb_interval: %d",
            receivedMsgPtr->hb_interval);
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : sctpConfigRangeChk()
Parameters    : SigtranSctpConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SIGTRANSCTPCONFIGTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool sctpConfigRangeChk(SigtranSctpConfigTableApi *receivedMsgPtr)
{
   /*Changed for mantis #0032113 Gaurav Sinha 15 Nov 2016*/
   if((receivedMsgPtr->assoc_max_retrans < receivedMsgPtr->path_max_retrans))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpConfigRangeChk: Range Check Failed - assoc_max_retrans: %d less than path_max_retrans : %d",
            receivedMsgPtr->assoc_max_retrans,receivedMsgPtr->path_max_retrans);
      return FALSE;
   }
   /*Changed for mantis #0032113 Gaurav Sinha 15 Nov 2016*/
   if((receivedMsgPtr->assoc_max_retrans < 1) || (receivedMsgPtr->assoc_max_retrans > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpConfigRangeChk: Range Check Failed - assoc_max_retrans: %d",
            receivedMsgPtr->assoc_max_retrans);
      return FALSE;
   }
   if((receivedMsgPtr->path_max_retrans < 1) || (receivedMsgPtr->path_max_retrans > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpConfigRangeChk: Range Check Failed - path_max_retrans: %d",
            receivedMsgPtr->path_max_retrans);
      return FALSE;
   }
   if((receivedMsgPtr->max_init_retrans < 1) || (receivedMsgPtr->max_init_retrans > 65535))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpConfigRangeChk: Range Check Failed - max_init_retrans: %d",
            receivedMsgPtr->max_init_retrans);
      return FALSE;
   }
   if((receivedMsgPtr->timerProfileId < 1) || (receivedMsgPtr->timerProfileId > 5))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sctpConfigRangeChk: Range Check Failed - timerProfileId: %d",
            receivedMsgPtr->timerProfileId);
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : bssapIntfConfigRangeChk()
Parameters    : BssapIntfConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_BSSAPINTFCONFIGTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool bssapIntfConfigRangeChk(BssapIntfConfigTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->interfaceType != SS7) && (receivedMsgPtr->interfaceType != SIGTRAN))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapIntfConfigRangeChk: Range Check Failed - interfaceType: %d",
            receivedMsgPtr->interfaceType);
      return FALSE;
   }
   if((receivedMsgPtr->ni!= INTERNATIONAL_00)&&(receivedMsgPtr->ni!= INTERNATIONAL_01)&&(receivedMsgPtr->ni!= NATIONAL_10)&&((receivedMsgPtr->ni!= NATIONAL_01)))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapIntfConfigRangeChk: Range Check Failed - networkIndicator(ni): %d",
            receivedMsgPtr->ni);
      return FALSE;
   }
   if(strlen(receivedMsgPtr->name) > 20) 
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapIntfConfigRangeChk: Range Check Failed - name: %d",
            receivedMsgPtr->name);
      return FALSE;
   }
   if((receivedMsgPtr->opc < 0) || (receivedMsgPtr->opc > 16777215))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapIntfConfigRangeChk: Range Check Failed - opc: %d",
            receivedMsgPtr->opc);
      return FALSE;
   }
   if((receivedMsgPtr->dpc < 0) || (receivedMsgPtr->dpc > 16777215))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapIntfConfigRangeChk: Range Check Failed - dpc: %d",
            receivedMsgPtr->dpc);
      return FALSE;
   }
   if((receivedMsgPtr->variant != ITU) && (receivedMsgPtr->dpc != ANSI))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:bssapIntfConfigRangeChk: Range Check Failed - variant: %d",
            receivedMsgPtr->variant);
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : sccpSpConfigRangeChk()
Parameters    : SigtranSccpSPConfigTableApi *receivedMsgPtr
Return type   : I_Bool
Purpose       : To perform range check for parameters received in 
BSC_API_SET_SIGTRANSCCPSPCONFIGTABLE
Other Note    : Added For IP_BSC_STACK implementation
 *****************************************************************************/
I_Bool sccpSpConfigRangeChk(SigtranSccpSPConfigTableApi *receivedMsgPtr)
{
   if((receivedMsgPtr->spId < 1) || (receivedMsgPtr->spId > 64))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpSpConfigRangeChk: Range Check Failed - spId: %d",
            receivedMsgPtr->spId);
      return FALSE;
   }
   if((receivedMsgPtr->nwId < 0) || (receivedMsgPtr->nwId > 3))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpSpConfigRangeChk: Range Check Failed - nwId: %d",
            receivedMsgPtr->nwId);
      return FALSE;
   }
   if((receivedMsgPtr->local != PC_AOIP_REMOTE) && (receivedMsgPtr->local != PC_AOIP_LOCAL))
   {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:sccpSpConfigRangeChk: Range Check Failed - local: %d",
            receivedMsgPtr->local);
      return FALSE;
   }
   return TRUE;
}
/******************************* Function  Header*****************************
Function Name : setSigtranBssapTimerTable()
Parameters    : NULL 
Return type   : I_Bool
Other Note    : Added For IP_BSC_STACK implementation
*****************************************************************************/
I_Void setSigtranBssapTimerTable()	
{
 I_U32 bssAdminState = ZERO;
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSigtranBssapTimerTable() ..");
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 BssapTmrConfigTableApi *receivedMsgPtr = (BssapTmrConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 BssapTmrConfigTableApi* bssapTmrConfigPtr = NULL;
 BssapTmrConfigTableIndices key;
 //I_U32 outCount = ZERO;
 //I_U16 outSize = ZERO;
 key.profileID = receivedMsgPtr->profileID;
 if(CLIB_SUCCESS==getBssapTmrConfigTable(&key,&bssapTmrConfigPtr))
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MODIFICATION of BssapTmrConfigTable : going for rangeChk");
   /* Perform range check on received parameters */
   if(!bssapTmrConfigRangeChk(receivedMsgPtr))
   {
    cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
    return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(BssapTmrConfigTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_BSSAPTMRCONFIGTABLE, SCM_MODIFY, OAM_SCM_BS_TIMER_CONFIG);

   /* Frame and Send the message to the OIL */
   if (!fillAndSendOamScmBsTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 else
 {
   /*if(CLIB_SUCCESS == getallBssapTmrConfigTable(&bssapTmrConfigPtr,&outCount,&outSize))
     {
       free(bssapTmrConfigPtr);

       if(outCount >= MAX_BSSAP_TIMER_PROFILES)
        {
          cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
          return;
        }
     }*/

    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of BssapTmrConfigTable : going for rangeChk for profileID : [%d]",receivedMsgPtr->profileID);
   /* Perform range check on received parameters */
   if(!bssapTmrConfigRangeChk(receivedMsgPtr))
   {
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(BssapTmrConfigTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_BSSAPTMRCONFIGTABLE, SCM_ADD, OAM_SCM_BS_TIMER_CONFIG);

   /* Frame and Send the message to the OIL */
   if (!fillAndSendOamScmBsTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSigtranBssapTimerTable() ..");
}	
/*I_Void delSigtranBssapTimerTable()	
{
 I_U32 bssAdminState = ZERO;
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering delSigtranBssapTimerTable() ..");
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
 }
 if ( ! isDelBssapTimerConfigTableAllowed() ) {
      cfgSendNackToCm( getFailCauseInStackObj() );
      return;
   }
   * Set Stack object data structure *
   setStackObject(BSC_API_SET_BSSAPTMRCONFIGTABLE, SCM_DELETE, OAM_SCM_BS_TIMER_CONFIG);

   * Frame and Send the message to the OIL *
   if (!fillAndSendOamScmBsTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting delSigtranBssapTimerTable() ..");
}*/
//////////////////////////////////////////////////////////////////////////////////////	
/******************************* Function  Header*****************************
Function Name : setSigtranSccpTimerTable()
Parameters    : NULL 
Return type   : I_Bool
Other Note    : Added For IP_BSC_STACK implementation
*****************************************************************************/
I_Void setSigtranSccpTimerTable()	
{
 I_U32 bssAdminState = ZERO;
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSigtranSccpTimerTable() ..");
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSccpTimerTableApi *receivedMsgPtr = (SigtranSccpTimerTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranSccpTimerTableApi *sigtranSccpTimerTableApi= NULL;
 SigtranSccpTimerTableIndices key;
 //I_U32 outCount = ZERO;
 //I_U16 outSize = ZERO;
 key.profileId= receivedMsgPtr->profileId;
 if(CLIB_SUCCESS==getSigtranSccpTimerTable(&key,&sigtranSccpTimerTableApi))
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MODIFICATION of SigtranSccpTimerTable : going for rangeChk");
   /* Perform range check on received parameters */
   if(!sccpTmrConfigRangeChk(receivedMsgPtr))
   {
     cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
     return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSccpTimerTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_SIGTRANSCCPTIMERTABLE, SCM_MODIFY, OAM_SCM_SCCP_TMR_CONFIG);

   /* Frame and Send the message to the OIL */
   if (!fillAndSendOamScmSccpTmrConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 else
 {
   /*if(CLIB_SUCCESS == getallSigtranSccpTimerTable(&sigtranSccpTimerTableApi,&outCount,&outSize))
     {
       free(sigtranSccpTimerTableApi);

       if(outCount >= MAX_BSSAP_TIMER_PROFILES)
        {
          cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
          return;
        }
     }*/

    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSccpTimerTable: going for rangeChk for profileId : [%d]",receivedMsgPtr->profileId);
   /* Perform range check on received parameters */
   if(!sccpTmrConfigRangeChk(receivedMsgPtr))
   {
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSccpTimerTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_SIGTRANSCCPTIMERTABLE, SCM_ADD, OAM_SCM_SCCP_TMR_CONFIG);

   /* Frame and Send the message to the OIL */
   if (!fillAndSendOamScmSccpTmrConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSigtranSccpTimerTable() ..");
}	
/*I_Void delSigtranSccpTimerTable()	
{
}	*/
/******************************* Function  Header*****************************
Function Name : setSigtranM3uaTimerTable()
Parameters    : NULL 
Return type   : I_Bool
Other Note    : Added For IP_BSC_STACK implementation
*****************************************************************************/
I_Void setSigtranM3uaTimerTable()	
{
 I_U32 bssAdminState = ZERO;
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSigtranM3uaTimerTable() ..");
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 M3uaTmrConfigTableApi *receivedMsgPtr = (M3uaTmrConfigTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 M3uaTmrConfigTableApi *m3uaTmrConfigTableApi= NULL;
 M3uaTmrConfigTableIndices key;
 //I_U32 outCount = ZERO;
 //I_U16 outSize = ZERO;
 key.profileId= receivedMsgPtr->profileId;
 if(CLIB_SUCCESS==getM3uaTmrConfigTable(&key,&m3uaTmrConfigTableApi))
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MODIFICATION of M3uaTmrConfigTable : going for rangeChk");
   /* Perform range check on received parameters */
   if(!m3uaTmrConfigRangeChk(receivedMsgPtr))
   {
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(M3uaTmrConfigTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_M3UATMRCONFIGTABLE, SCM_MODIFY, OAM_SCM_M3UA_TIMER_CONFIG);

   /* Frame and Send the message to the OIL */
   //if (!fillAndSendOamScmSccpTmrConfig())
   if (!fillAndSendOamScmM3uaTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 else
 {
   /*if(CLIB_SUCCESS == getallM3uaTmrConfigTable(&m3uaTmrConfigTableApi,&outCount,&outSize))
     {
       free(m3uaTmrConfigTableApi);

       if(outCount >= MAX_BSSAP_TIMER_PROFILES)
        {
          cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
          return;
        }
     }*/

    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of M3uaTmrConfigTable: going for rangeChk for profileId : [%d]",receivedMsgPtr->profileId);
   /* Perform range check on received parameters */
   if(!m3uaTmrConfigRangeChk(receivedMsgPtr))
   {
    cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
    return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(M3uaTmrConfigTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_M3UATMRCONFIGTABLE, SCM_ADD, OAM_SCM_M3UA_TIMER_CONFIG);

   /* Frame and Send the message to the OIL */
   //if (!fillAndSendOamScmSccpTmrConfig())
   if (!fillAndSendOamScmM3uaTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSigtranM3uaTimerTable() ..");
}	
/*I_Void delSigtranM3uaTimerTable()	
{
}	*/
/******************************* Function  Header*****************************
Function Name : setSigtranSctpTimerTable()
Parameters    : NULL 
Return type   : I_Bool
Other Note    : Added For IP_BSC_STACK implementation
*****************************************************************************/
I_Void setSigtranSctpTimerTable()	
{
 I_U32 bssAdminState = ZERO;
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Entering setSigtranSctpTimerTable() ..");
 if(getBssAdminState(&bssAdminState) != CLIB_SUCCESS)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: getBssAdminState DB call is geting failed..");
    cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
    return;
 }
 if(bssAdminState == UNLOCKED)
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: BSS is UNLOCKED.. FIRST LOCK BSS");
    cfgSendNackToCm(CM_ERR_BSS_NOT_LOCKED);
    return;
 }
 SigtranSctpTimerTableApi *receivedMsgPtr = (SigtranSctpTimerTableApi *)(((I_U8 *)gCfgMsgBuf )+ sizeof (sCmMsg));
 SigtranSctpTimerTableApi *sigtranSctpTimerTableApi= NULL;
 SigtranSctpTimerTableIndices key;
 //I_U32 outCount = ZERO;
 //I_U16 outSize = ZERO;
 key.profileId = receivedMsgPtr->profileId;
 if(CLIB_SUCCESS==getSigtranSctpTimerTable(&key,&sigtranSctpTimerTableApi))
 {
    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: MODIFICATION of SigtranSctpTimerTable : going for rangeChk");
   /* Perform range check on received parameters */
   if(!sctpTmrConfigRangeChk(receivedMsgPtr))
   {
    cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
    return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSctpTimerTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_SIGTRANSCTPTIMERTABLE, SCM_MODIFY, OAM_SCM_SCTP_TIMER_CONFIG);

   /* Frame and Send the message to the OIL */
   //if (!fillAndSendOamScmM3uaTimerConfig())
   if (!fillAndSendOamScmSctpTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 else
 {
   /*if(CLIB_SUCCESS == getallSigtranSctpTimerTable(&sigtranSctpTimerTableApi,&outCount,&outSize))
     {
       free(sigtranSctpTimerTableApi);

       if(outCount >= MAX_BSSAP_TIMER_PROFILES)
        {
          cfgSendNackToCm(CM_ERR_MAX_ENTRY_PRES);
          return;
        }
     }*/

    LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: ADDITION of SigtranSctpTimerTable : going for rangeChk for profileId: [%d]",receivedMsgPtr->profileId);
   /* Perform range check on received parameters */
   if(!sctpTmrConfigRangeChk(receivedMsgPtr))
   {
    cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
    return; 
   }

   /* Store the received message in global pointer */
   if (!storeReceivedMsgBuffer(receivedMsgPtr, sizeof(SigtranSctpTimerTableApi)))
   {
      return; 
   }

   /* Set Stack object data structure */
   setStackObject(BSC_API_SET_SIGTRANSCTPTIMERTABLE, SCM_ADD, OAM_SCM_SCTP_TIMER_CONFIG);

   /* Frame and Send the message to the OIL */
   //if (!fillAndSendOamScmM3uaTimerConfig())
   if (!fillAndSendOamScmSctpTimerConfig())
   {
      sendStackProcRespToCm();
      return;
   }
 }
 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: Exiting setSigtranSctpTimerTable() ..");
}	
/*I_Void delSigtranSctpTimerTable()	
{
}*/
/*SCM_RESP-NESTED*/	
I_Void addBssapInterfaceScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      BssapIntfConfigTableApi *bssapIntfConfigTableApi = (BssapIntfConfigTableApi *)gStoredMsgBufPtr;
      if (insertBssapIntfConfigTable(bssapIntfConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addBssapInterfaceScmRespHandler : insertBssapIntfConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
      else /*Going to add AifInterfaceTable IP_BSC_STACK: Gaurav Sinha 18 July 2016*/
      {
        AifInterfaceTableApi aifInterfacePtr;

				aifInterfacePtr.interfaceId          = bssapIntfConfigTableApi->bscId;
        memcpy(aifInterfacePtr.interfaceNameString,bssapIntfConfigTableApi->name,20);
				aifInterfacePtr.interfaceType        = bssapIntfConfigTableApi->interfaceType;
				aifInterfacePtr.dpc                  = bssapIntfConfigTableApi->dpc;
				aifInterfacePtr.tgpId                = DEFAULT_TGPID;
				aifInterfacePtr.interfaceAdminState  = UNLOCKED;
				aifInterfacePtr.operationalState     = DISABLED;
				
				if (insertAifInterfaceTable(&aifInterfacePtr) != CLIB_SUCCESS)
				{
					 LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addBssapInterfaceScmRespHandler : insertAifInterfaceTable Failed..");
					 setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
				}
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delBssapInterfaceScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteBssapIntfConfigTable((BssapIntfConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In delBssapInterfaceScmRespHandler : Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
      else
      {
        AifInterfaceTableIndices *keysPtr=NULL;
        keysPtr = (BssapIntfConfigTableIndices *)gStoredMsgBufPtr;
        if ( CLIB_SUCCESS != deleteAifInterfaceTable(keysPtr) ) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK:  In delBssapInterfaceScmRespHandler():deleteAifInterfaceTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
        }
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addSccpSpConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSccpSPConfigTableApi *sigtranSccpSPConfigTableApi = (SigtranSccpSPConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSccpSPConfigTable(sigtranSccpSPConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSccpSpConfigScmRespHandler : insertSigtranSccpSPConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delSccpSpConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranSccpSPConfigTable((SigtranSccpSPConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranSccpSPConfigTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addSccpSsConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSccpSSConfigTableApi *sigtranSccpSSConfigTableApi = (SigtranSccpSSConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSccpSSConfigTable(sigtranSccpSSConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSccpSsConfigScmRespHandler : insertSigtranSccpSSConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delSccpSsConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranSccpSSConfigTable((SigtranSccpSSConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranSccpSSConfigTable : Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addSccpCssConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSccpCSSConfigTableApi *sigtranSccpCSSConfigTableApi = (SigtranSccpCSSConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSccpCSSConfigTable(sigtranSccpCSSConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSccpCssConfigScmRespHandler : insertSigtranSccpCSSConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delSccpCssConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranSccpCSSConfigTable((SigtranSccpCSSConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranSccpCSSConfigTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addSccpCspConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSccpCSPConfigTableApi *sigtranSccpCSPConfigTableApi = (SigtranSccpCSPConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSccpCSPConfigTable(sigtranSccpCSPConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSccpCspConfigScmRespHandler : insertSigtranSccpCSPConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delSccpCspConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranSccpCSPConfigTable((SigtranSccpCSPConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranSccpCSPConfigTable : Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addM3uaLocalAspConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   I_S32 index = -1;
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranM3uaLAspConfigTable(sigtranM3uaLAspConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addM3uaLocalAspConfigScmRespHandler : insertSigtranM3uaLAspConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
      else
      {
				index = getFreeIndexAspStatus();
				if(index < 0)
				{
					LOG_PRINT(DEBUG,"IP_BSC_STACK: Free index not found in gStructAspStatusVar()");
				}
				else
				{
					LOG_PRINT(DEBUG,"IP_BSC_STACK: Free index [%d] found in gStructAspStatusVar",index);
					gStructAspStatusVar[index].localAspId = sigtranM3uaLAspConfigTableApi->localAspId;
					gStructAspStatusVar[index].gAdminState = locked;
					gStructAspStatusVar[index].status = ONE;
					LOG_PRINT(DEBUG,"IP_BSC_STACK: index[%d] updated in gStructAspStatusVar : localAspId[%d] gAdminState[%d] status[%d]",index,gStructAspStatusVar[index].localAspId,gStructAspStatusVar[index].gAdminState,gStructAspStatusVar[index].status);
				}
      }
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void modifyM3uaLocalAspConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)gStoredMsgBufPtr;
      if (updateSigtranM3uaLAspConfigTable(sigtranM3uaLAspConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In modifyM3uaLocalAspConfigScmRespHandler : updateSigtranM3uaLAspConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delM3uaLocalAspConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranM3uaLAspConfigTable((SigtranM3uaLAspConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranM3uaLAspConfigTable : Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
      else
      {
        SigtranM3uaLAspConfigTableIndices *sigtranM3uaLAspConfigTableIndices = (SigtranM3uaLAspConfigTableIndices *)gStoredMsgBufPtr;
        freeIndexfromgStructAspStatusVar(sigtranM3uaLAspConfigTableIndices->localAspId);
      }
   /*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addM3uaRemoteAspConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranM3uaRAspConfigTableApi *sigtranM3uaRAspConfigTableApi = (SigtranM3uaRAspConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranM3uaRAspConfigTable(sigtranM3uaRAspConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addM3uaRemoteAspConfigScmRespHandler: insertSigtranM3uaRAspConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delM3uaRemoteAspConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranM3uaRAspConfigTable((SigtranM3uaRAspConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranM3uaRAspConfigTable : Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addM3uaLocalAsConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranM3uaLAsConfigTableApi *sigtranM3uaLAsConfigTableApi = (SigtranM3uaLAsConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranM3uaLAsConfigTable(sigtranM3uaLAsConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addM3uaLocalAsConfigScmRespHandler : insertSigtranM3uaLAsConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delM3uaLocalAsConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranM3uaLAsConfigTable((SigtranM3uaLAsConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranM3uaLAsConfigTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addM3uaRemoteAsConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranM3uaRAsConfigTableApi *sigtranM3uaRAsConfigTableApi = (SigtranM3uaRAsConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranM3uaRAsConfigTable(sigtranM3uaRAsConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addM3uaRemoteAsConfigScmRespHandler: insertSigtranM3uaRAsConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delM3uaRemoteAsConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteSigtranM3uaRAsConfigTable((SigtranM3uaRAsConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In deleteSigtranM3uaRAsConfigTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addSctpConfigScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSctpConfigTableApi *sigtranSctpConfigTableApi = (SigtranSctpConfigTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSctpConfigTable(sigtranSctpConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSctpConfigScmRespHandler : insertSigtranSctpConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void modifySctpConfigScmRespHandler()	
{
  ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (updateSigtranSctpConfigTable((SigtranSctpConfigTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In updateSigtranSctpConfigTable : Failed");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK:Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addBssapTimerScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      BssapTmrConfigTableApi *bssapTmrConfigTableApi = (BssapTmrConfigTableApi *)gStoredMsgBufPtr;
      if (insertBssapTmrConfigTable(bssapTmrConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addBssapTimerScmRespHandler : insertBssapTmrConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void modifyBssapTimerConfigScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateBssapTmrConfigTable((BssapTmrConfigTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"IP_BSC_STACK: In modifyBssapTimerScmRespHandler : updateBssapTmrConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void modifySigtranSccpTimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateSigtranSccpTimerTable((SigtranSccpTimerTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"IP_BSC_STACK: In modifySigtranSccpTimerScmRespHandler: updateSigtranSccpTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void modifySigtranM3uaTimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateM3uaTmrConfigTable((M3uaTmrConfigTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"IP_BSC_STACK: In modifySigtranM3uaTimerScmRespHandler : updateM3uaTmrConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void modifySigtranSctpTimerScmRespHandler()
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  
   {
      if (updateSigtranSctpTimerTable((SigtranSctpTimerTableApi *)gStoredMsgBufPtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_MAJOR,"IP_BSC_STACK: In modifySigtranSctpTimerScmRespHandler: updateSigtranSctpTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_UPDATE_DB_OPER_FAILED);
      }
   }  
   else
   {
	   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
      //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void delBssapTimerScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )  {
      if (deleteBssapTmrConfigTable((BssapTmrConfigTableIndices *)gStoredMsgBufPtr) != CLIB_SUCCESS) {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK:  In deleteBssapTmrConfigTable: Failed");
         setFailCauseInStackObj(CM_ERR_DELETE_DB_OPER_FAILED);
      }
   }
   else {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
     //setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
I_Void addSigtranSccpTimerScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSccpTimerTableApi *sigtranSccpTimerTableApi= (SigtranSccpTimerTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSccpTimerTable(sigtranSccpTimerTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSigtranSccpTimerScmRespHandler: insertSigtranSccpTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
/*I_Void delSigtranSccpTimerScmRespHandler()	
{
}*/
I_Void addSigtranM3uaTimerScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      M3uaTmrConfigTableApi *m3uaTmrConfigTableApi= (M3uaTmrConfigTableApi *)gStoredMsgBufPtr;
      if (insertM3uaTmrConfigTable(m3uaTmrConfigTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSigtranM3uaTimerScmRespHandler: insertM3uaTmrConfigTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
/*I_Void delSigtranM3uaTimerScmRespHandler()	
{
}*/
I_Void addSigtranSctpTimerScmRespHandler()	
{
   ScmOamResponse *ScmOamRespPtr = (ScmOamResponse *)( ( (SysHdr* ) gCfgMsgBuf )+ 1);

   if ( isStackRespOK(ScmOamRespPtr->erro_code) )
   {
      SigtranSctpTimerTableApi *sigtranSctpTimerTableApi= (SigtranSctpTimerTableApi *)gStoredMsgBufPtr;
      if (insertSigtranSctpTimerTable(sigtranSctpTimerTableApi) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In addSigtranSctpTimerScmRespHandler: insertSigtranSctpTimerTable Failed..");
         setFailCauseInStackObj(CM_ERR_INSERT_DB_OPER_FAILED);
      }
   }
   else
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received error from SCM");
    //  setFailCauseInStackObj(CM_ERR_STACK_CONFIG_FAIL);
   }
   sendStackProcRespToCm();
}
/*I_Void delSigtranSctpTimerScmRespHandler()	
{
}*/
/*SCM_RESP-NESTED*/	
/*SCM_RESP IP_BSC_STACK*/	
I_Void BssapInterfaceScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addBssapInterfaceScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delBssapInterfaceScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SccpSpConfigScmRespHandler()	
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSccpSpConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSccpSpConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SccpSsConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSccpSsConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSccpSsConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SccpCssConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSccpCssConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSccpCssConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SccpCspConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSccpCspConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSccpCspConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void M3uaLocalAspConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addM3uaLocalAspConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         modifyM3uaLocalAspConfigScmRespHandler();
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delM3uaLocalAspConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void M3uaRemoteAspConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addM3uaRemoteAspConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delM3uaRemoteAspConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void M3uaLocalAsConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addM3uaLocalAsConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delM3uaLocalAsConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void M3uaRemoteAsConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addM3uaRemoteAsConfigScmRespHandler();         
         break;
      /*case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         break;*/
      case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delM3uaRemoteAsConfigScmRespHandler();         
         break;
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SctpConfigScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSctpConfigScmRespHandler();         
         break;
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         modifySctpConfigScmRespHandler();         
         break;
      /*case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         modifySctpConfigScmRespHandler();         
         break;*/
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SigtranBssapTimerScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addBssapTimerScmRespHandler();         
         break;
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         modifyBssapTimerConfigScmRespHandler();
         break;
      /*case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delBssapTimerScmRespHandler();         
         break;*/
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SigtranSccpTimerScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSigtranSccpTimerScmRespHandler();         
         break;
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         modifySigtranSccpTimerScmRespHandler();
         break;
      /*case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSigtranSccpTimerScmRespHandler();         
         break;*/
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SigtranM3uaTimerScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSigtranM3uaTimerScmRespHandler();         
         break;
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         modifySigtranM3uaTimerScmRespHandler();
         break;
      /*case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSigtranM3uaTimerScmRespHandler();         
         break;*/
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
I_Void SigtranSctpTimerScmRespHandler()
{
   switch (getScmAction() ) {
      case SCM_ADD:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_ADD..");
         addSigtranSctpTimerScmRespHandler();         
         break;
      case SCM_MODIFY:
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_MODIFY..");
         modifySigtranSctpTimerScmRespHandler();
         break;
      /*case SCM_DELETE:  
         LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Received SCM_DELETE..");
         delSigtranSctpTimerScmRespHandler();         
         break;*/
      default : LOG_PRINT(LOG_MAJOR,"Invalid ScmAction");
   }      
   return;
}	
/*SCM_RESP IP_BSC_STACK*/	
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
/*IP_BSC_STACK: Initializing SigtranM3uaLAspConfigTableApi OperationalState Gaurav Sinha 29-09-2016*/
/******************************* Function  Header*****************************
Function Name : initSigtranM3UALocalAspOperStateAtStartUp(I_Void)
Parameters    : I_Void 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void initSigtranM3UALocalAspOperStateAtStartUp(I_Void)
{
 LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: Entering in initSigtranM3UALocalAspOperStateAtStartUp() ..");
 SigtranM3uaLAspConfigTableApi* sigtranM3uaLAspConfigTableApi = NULL,*tmpSigtranM3uaLAspConfigTableApi=NULL;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outCount,&outSize))
 {
  LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: No of rows present[%d]",outCount);
	for(i = 0; i < outCount; ++i)
	{
	 tmpSigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)((I_U8 *)sigtranM3uaLAspConfigTableApi + (i * outSize));
   /*LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: localAspId[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->localAspId,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: localPort [%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->localPort,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: localIp[%s] row[%d]",tmpSigtranM3uaLAspConfigTableApi->localIp,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: name[%s] row[%d]",tmpSigtranM3uaLAspConfigTableApi->name,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: slotId[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->slotId,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: assocType[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->assocType,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: maxInStream[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->maxInStream,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: maxOutStream[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->maxOutStream,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: operationalStatus[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->operationalStatus,i);
   LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: adminState[%d] row[%d]",tmpSigtranM3uaLAspConfigTableApi->adminState,i);*/
	 tmpSigtranM3uaLAspConfigTableApi->operationalStatus = DISABLED;
	 if (updateSigtranM3uaLAspConfigTable(tmpSigtranM3uaLAspConfigTableApi) != CLIB_SUCCESS)
   {
			LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: In setM3uaLocalAspConfigTable() : updateSigtranM3uaLAspConfigTable Failed..");
      free(sigtranM3uaLAspConfigTableApi);
      return;
   }
	 LOG_PRINT(LOG_INFO,"IP_BSC_STACK:localAspId[%d]OperationalState[%d]",tmpSigtranM3uaLAspConfigTableApi->localAspId,tmpSigtranM3uaLAspConfigTableApi->operationalStatus);
	 //free(sigtranM3uaLAspConfigTableApi);
	}
  free(sigtranM3uaLAspConfigTableApi);
 }
 else
 {
  LOG_PRINT(LOG_CRITICAL,"IP_BSC_STACK: No rows present in sigtranM3uaLAspConfigTableApi() ..");
 }
 LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: Exiting initSigtranM3UALocalAspOperStateAtStartUp() ..");
}
/*IP_BSC_STACK: Initializing SigtranLocalAspConfigTable OperationalState Gaurav Sinha 29-09-2016*/
/*Added for mantis #32112 #32021 Gaurav Sinha 04-10-2016*/
/******************************* Function  Header*****************************
Function Name : checkAndSendAspUnlock(I_U32 aspId)
Parameters    : I_U32 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void checkAndSendAspUnlock(I_U32 aspId)
{
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering in checkAndSendAspUnlock()");
  SigtranM3uaLAspConfigTableIndices key;
  SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi= NULL;
  key.localAspId = aspId;
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
  I_S32 i=-1;
  i = getIndexFromAspId(aspId);
  if(i<0)
  {
    LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Invalid index returned by getIndexFromAspId() for AspId [%d] NOT PROCEEDING",aspId);
    return;
  }
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
  if(CLIB_SUCCESS==getSigtranM3uaLAspConfigTable(&key,&sigtranM3uaLAspConfigTableApi))
  {
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
    if((sigtranM3uaLAspConfigTableApi->adminState==UNLOCKED) && ((gStructAspStatusVar[i].gAdminState == unlocked) || (gStructAspStatusVar[i].gAdminState == unlockInProgress)))
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
    {
      if((gBssState == unlocked) || (gBssState == unlockInProgress))
			{
       OamScmM3uaLocalAspAdminConfig oamScmM3uaLocalAspAdminConfig;
       oamScmM3uaLocalAspAdminConfig.localAspId = aspId; 
       oamScmM3uaLocalAspAdminConfig.adminState = UNLOCKED; 
       setStackObject(BSC_API_SET_BSSTABLE, SCM_MODIFY, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG);
       if (cfgSendStackMessage((I_Void *)&oamScmM3uaLocalAspAdminConfig, sizeof(OamScmM3uaLocalAspAdminConfig)) == CFG_SUCCESS) 
       {
          LOG_PRINT(LOG_INFO,"IP_BSC_STACK: checkAndSendAspUnlock: Sending OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG ASPID[%u] to Oil..",oamScmM3uaLocalAspAdminConfig.localAspId);
          LOG_PRINT(LOG_INFO,"IP_BSC_STACK: BssState[%d] AspAdminStateDB [%d]()",gBssState,sigtranM3uaLAspConfigTableApi->adminState);
          gReqSentToScm =1;
       }
      }
      else
      {
        LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Bss State is not unlocked/unlockInProgress / Current Bss State[%d] Dumping the Alarm",gBssState);
      }
    }
    else
    {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: LocalAspId [%d] is LOCKED in DB or OAM operation is in Progress gAdminState [%d] ::Dumping the Alarm",key.localAspId,gStructAspStatusVar[i].gAdminState);
    }
    
  free(sigtranM3uaLAspConfigTableApi);
  }
  else
  {
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: No Entry present for LocalAspId [%d] Dumping the Alarm",key.localAspId);
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
  }
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting checkAndSendAspUnlock()");
}
/******************************* Function  Header*****************************
Function Name : getAspIdFromSlotId(I_U32 slotId)
Parameters    : I_U32 
Return type   : I_U32
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_U32 getAspIdFromSlotId(I_U32 slotId)
{
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering getAspIdFromSlotId()");
  SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = NULL,*tmpSigtranM3uaLAspConfigTableApi=NULL;;
  I_U32 outCount = ZERO;
  I_U16 outSize = ZERO;
  I_U32 localAspIdRet = ZERO;
  I_U32 i=ZERO;
  if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outCount,&outSize))
  {
	 	for(i = 0; i < outCount; ++i)
    {
	 	 tmpSigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)((I_U8 *)sigtranM3uaLAspConfigTableApi + i * outSize);
     if(tmpSigtranM3uaLAspConfigTableApi->slotId == slotId)
     {
       localAspIdRet = tmpSigtranM3uaLAspConfigTableApi->localAspId;
  		 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: localAspId[%d] found corressponding to slotId[%d]",localAspIdRet,slotId);
		   return localAspIdRet;	
     }
    }
    LOG_PRINT(LOG_INFO,"IP_BSC_STACK: No AspId found for SlotId[%d]",slotId);
    free(sigtranM3uaLAspConfigTableApi);
  }
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting getAspIdFromSlotId()");
  return ZERO;
}
/*Added for mantis #32112 #32021 Gaurav Sinha 04-10-2016*/
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
/******************************* Function  Header*****************************
Function Name : getFreeIndexAspStatus(I_Void)
Parameters    : I_Void 
Return type   : I_U32
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_S32 getFreeIndexAspStatus(I_Void)
{
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering getFreeIndexAspStatus()");
  I_S32 i=ZERO;
  for(i=ZERO;i<TWO;i++)
  {
    if(gStructAspStatusVar[i].status == ZERO)
    {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: Exiting getFreeIndexAspStatus : Returning Free index [%d] for Global Asp Status",i)
      return i;
    } 
  }
  i=-1;
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting getFreeIndexAspStatus() returning index [%d]",i);
  return -1;
}
/******************************* Function  Header*****************************
Function Name : freeIndexfromgStructAspStatusVar(I_U16 localAspId)
Parameters    : I_U16 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void freeIndexfromgStructAspStatusVar(I_U16 localAspId)
{
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering getFreeIndexAspStatus()");
  I_U32 i=ZERO;
  for(i=ZERO;i<2;i++)
  {
   if(gStructAspStatusVar[i].localAspId == localAspId)
   {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Index[%d] found for localAspId [%d]",i,localAspId);
     gStructAspStatusVar[i].localAspId = ZERO;
     gStructAspStatusVar[i].gAdminState = ZERO;
     gStructAspStatusVar[i].status      = ZERO;
		LOG_PRINT(DEBUG,"IP_BSC_STACK: index[%d] updated in gStructAspStatusVar : localAspId[%d] gAdminState[%d] status[%d]",index,gStructAspStatusVar[i].localAspId,gStructAspStatusVar[i].gAdminState,gStructAspStatusVar[i].status);
   }
  }
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting getFreeIndexAspStatus()");
}
/******************************* Function  Header*****************************
Function Name : setStatusAspLocal(I_U16 localAspId,I_U16 adminState,I_U32 operation)
Parameters    : I_U16 localAspId,I_U16 adminState,I_U32 operation 
Return type   : I_Void
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void setStatusAspLocal(I_U16 localAspId,I_U16 adminState,I_U32 operation)
{
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering in setStatusAspLocal(): OPERATION : [%d] 1-STK_REQUEST / 2-STK_RESPONSE / 3-STK_FAILURE",operation);
  I_U32 i=ZERO;
  for(i=ZERO;i<2;i++)
  {
   if(gStructAspStatusVar[i].localAspId == localAspId)
   {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Index[%d] found for localAspId [%d]",i,localAspId);
     break;
   }
  }
  if(operation == STK_REQUEST)
  {
    LOG_PRINT(DEBUG,"IP_BSC_STACK: STK_REQUEST case AspId [%d] from OMC for AdminState[%d]",localAspId,adminState)
		if( adminState == LOCKED)
		{
			gStructAspStatusVar[i].gAdminState = lockInProgress;   
		}
		else if(operation == UNLOCKED)
		{
			gStructAspStatusVar[i].gAdminState = unlockInProgress;   
		}
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Updated gAdminState[%d] of AspId [%d]",gStructAspStatusVar[i].gAdminState,localAspId);
  }
  else if(operation == STK_RESPONSE)
  {
    LOG_PRINT(DEBUG,"IP_BSC_STACK: STK_RESPONSE case AspId [%d] for Previous gAdminState [%d]",localAspId,gStructAspStatusVar[i].gAdminState)
    if(gStructAspStatusVar[i].gAdminState == lockInProgress)
    {
      gStructAspStatusVar[i].gAdminState = locked;
    }
    else if(gStructAspStatusVar[i].gAdminState == unlockInProgress)
    {
      gStructAspStatusVar[i].gAdminState = unlocked;
    }
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Updated gAdminState[%d] of Asp[%d]",gStructAspStatusVar[i].gAdminState,localAspId);
  }
  else if(operation == STK_FAILURE)
  {
    LOG_PRINT(DEBUG,"IP_BSC_STACK: STK_FAILURE case AspId [%d] for Previous gAdminState [%d]",localAspId,gStructAspStatusVar[i].gAdminState)
    if(gStructAspStatusVar[i].gAdminState == lockInProgress)
    {
      gStructAspStatusVar[i].gAdminState = unlocked;
    }
    else if(gStructAspStatusVar[i].gAdminState == unlockInProgress)
    {
      gStructAspStatusVar[i].gAdminState = locked;
    }
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Updated gAdminState[%d] of Asp[%d]",gStructAspStatusVar[i].gAdminState,localAspId);
  }
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting in setStatusAspLocal()");
}
/******************************* Function  Header*****************************
Function Name : getIndexFromAspId(I_U16 localAspId)
Parameters    : I_U16 localAspId 
Return type   : I_S32 index
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_S32 getIndexFromAspId(I_U16 localAspId)
{
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering getIndexFromAspId()");
  I_S32 i=-1;
  for(i=ZERO;i<2;i++)
  {
   if(gStructAspStatusVar[i].localAspId == localAspId)
   {
     LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Found index [%d] for localAspId [%d]",i,localAspId);
     return i;
   }
  }
  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting getIndexFromAspId() : No Index found for localAspId [%d]",localAspId);
  return i;
}
/******************************* Function  Header*****************************
Function Name : initGlobalDsForAspStatusAtStartup(I_Void)
Parameters    : I_Void 
Return type   : I_Void 
Other Note    : Added For IP_BSC_STACK 
*****************************************************************************/
I_Void initGlobalDsForAspStatusAtStartup(I_Void)
{
 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Entering in initGlobalDsForAspStatusAtStartup()");
 SigtranM3uaLAspConfigTableApi *sigtranM3uaLAspConfigTableApi = NULL,*tmpSigtranM3uaLAspConfigTableApi=NULL;
 I_U32 outCount = ZERO,i=ZERO;
 I_U16 outSize = ZERO;
 if(CLIB_SUCCESS == getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outCount,&outSize))
 {
  LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: No of rows present[%d]",outCount);
	for(i = 0; i < outCount; ++i)
	{
	 tmpSigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)((I_U8 *)sigtranM3uaLAspConfigTableApi + (i * outSize));
   I_S32 index = -1;
		index = getFreeIndexAspStatus();
		if(index < 0)
		{
			LOG_PRINT(DEBUG,"IP_BSC_STACK: Free index not found in gStructAspStatusVar()");
		}
    else
    {
			LOG_PRINT(DEBUG,"IP_BSC_STACK: Allocating index [%d] in gStructAspStatusVar() for localAspId [%d]",index,tmpSigtranM3uaLAspConfigTableApi->localAspId);
      gStructAspStatusVar[index].localAspId = tmpSigtranM3uaLAspConfigTableApi->localAspId;
      if(tmpSigtranM3uaLAspConfigTableApi->adminState == UNLOCKED)
      {
        gStructAspStatusVar[index].gAdminState = unlocked;
      }
      else if(tmpSigtranM3uaLAspConfigTableApi->adminState == LOCKED)
      {
        gStructAspStatusVar[index].gAdminState = locked;
      }
      gStructAspStatusVar[index].status = ONE;
			LOG_PRINT(DEBUG,"IP_BSC_STACK: index [%d] in gStructAspStatusVar[] localAspId [%d] gAdminState[%d] status[%d]",index,gStructAspStatusVar[index].localAspId,gStructAspStatusVar[index].gAdminState,gStructAspStatusVar[index].status);
    }
  }
 }
 LOG_PRINT(LOG_INFO,"IP_BSC_STACK: Exiting from initGlobalDsForAspStatusAtStartup()");
}
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
