/***********************************File Header ***************************
File Name        : oamscfg_nsvc_object_handler.c
Purpose          : This file contains CFG Nsvc Handler implementation
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>

/********************************* Function  Header********************************
Function Name:       nsvcObjectHandler()
Parameters:          I_Void
Return type:         I_Void
Purpose:             to fetch the state of requested NsvcHandler and call the appropriate 
                     handler acording to its state
Other Note:
 ************************************************************************************/
I_Void nsvcObjectHandler(I_Void)
{
   I_U8 caseIndex = 0;

   LOG_PRINT(LOG_INFO,"Entering nsvcObjectHandler()");

   caseIndex = getNsvcDataState();

   if (caseIndex == OAMS_CFG_MAX_NUM_NSVCS)
   {
      LOG_PRINT(LOG_MAJOR,"NSVC not found in gNsvcData" );
      cfgSendNackToCm(CM_ERR_UNKNOWN);
      return;
   }
   LOG_PRINT(LOG_MAJOR,"nsvcObjectHandler index = %u, gNsvcData[caseIndex].nsvcId = %u, gNsvcData[caseIndex].nsvcState = %u", caseIndex, gNsvcData[caseIndex].nsvcId, gNsvcData[caseIndex].nsvcState);
   switch(gNsvcData[caseIndex].nsvcState)
   {
      case locked:                             
         /* Locked in DB and in Local context */
         nsvcObjectLockedHandler();
         break;
      case unlockOrEnableInProgress:
         /*  Unlock is sent to NSVCH, the DB State can be Locked or Unlocked 
          *  Locked: when - Operator has requested NSVC Unlock
          *  Unlocked: when NSVCH unlcok is in progress due to BSS Unlock
          */
         nsvcObjectUnlockOrEnableInProgressHandler();
         break;
      case unlockedEnabled:
         /*  Unlocked in DB 
          *  Unlock Response is received from NSVCH
          */
         nsvcObjectUnlockedEnabledHandler();
         break;
      case unlockedDisabled:
         /*  Unlocked in DB 
          *  Unlock request is not yet sent to NSVCH
          */
         nsvcObjectUnlockedDisabledHandler();
         break;
      case lockeOrDisableInProgress:
         /*  Unlocked in DB 
          *  Lock request is sent to NSVCH
          */
         nsvcObjectLockOrDisableInProgressHandler();
         break;
      default:
         break;
   }
   LOG_PRINT(LOG_INFO,"Exiting nsvcObjectHandler()");
}

/********************************* Function  Header********************************
Function Name:       nsvcObjectLockedHandler()
Parameters:          I_Void
Return type:         I_Void
Purpose:             To do the handling of messages in Locked State
Other Note:
 ************************************************************************************/
I_Void nsvcObjectLockedHandler(I_Void)
{

   NsvcTableApi          *nsvcTableApiPtr        = NULL;
   NsvcTableApi          *nsvcTableApiDb         = NULL;
   GbInterfaceTableApi   *gbInterfaceTableApiPtr = NULL;
   sCmMsg                *receivedCmMsgPtr       = NULL;
   NsvcTableIndices      inData;
   OamsNsvchCfgAlarmInd  oamsNsvchCfgAlarmIndBuff;
   I_S32                 ret                     = CLIB_SUCCESS;
   I_Bool                statusRange             = FALSE;
   I_U32                 outRowsGb               = 0;
   I_U16                 e1Id                    = 0;
   I_U16                 outSizeGb               = 0;
   /*Mantis 13886 Start*/
   I_U32                 count                   = 0;
   I_U16                 outSize                 = 0;
   BssTableApi           *bssTable               = NULL;
   /*Mantis 13886 End*/

   LOG_PRINT(LOG_INFO, "Entering nsvcObjectLockedHandler()");
   LOG_PRINT(LOG_INFO, "Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
   
   memset(&oamsNsvchCfgAlarmIndBuff, 0, sizeof(OamsNsvchCfgAlarmInd)); 

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_NSVCTABLE:
      {

         /*Fetch the row from DB*/ 
         receivedCmMsgPtr = (sCmMsg*)gCfgMsgBuf;
         nsvcTableApiPtr = (NsvcTableApi*)(((I_U8*)receivedCmMsgPtr) + sizeof(sCmMsg));
         inData.nsvcId = nsvcTableApiPtr->nsvcId;
   
         ret = getNsvcTable(&inData, &nsvcTableApiDb);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR, "%s:: getNsvcTable DB call failed for NSVC ID [%u]. Error Code = [%d], Sending Nack",
                      __FUNCTION__,inData.nsvcId, ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }

         /*Check if Request is for Unlock*/
         if ((UNLOCKED == nsvcTableApiPtr->adminState) && (LOCKED == nsvcTableApiDb->adminState))
         {
            LOG_PRINT(LOG_INFO, "%s:: NSVC Unlock is received for NSVC ID [%u]",__FUNCTION__,nsvcTableApiPtr->nsvcId);

            /*Mantis 13886 Start*/
		    ret = getallBssTable(&bssTable,&count,&outSize);
            if(CLIB_SUCCESS != ret)
            {
                 LOG_PRINT(LOG_MAJOR,"Error getting BSS Table, Error Code = [%d] ", ret);
			     cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
				 free(nsvcTableApiDb);
                 return;
            }
            if ( FALSE == bssTable->gprsEnabled)
            {
               LOG_PRINT(LOG_INFO, "gprsEnabled is false in BSS Table, sending Nack");
               cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
               free(nsvcTableApiDb);
	           free(bssTable);
               return; 
            }
	        free(bssTable);
            /*Mantis 13886 End*/

            ret = getE1IdForNsvcId(nsvcTableApiPtr->nsvcId, &e1Id);

            if (CLIB_SUCCESS != ret)
            {
               LOG_PRINT(LOG_INFO, "No E1 present for NsvcId %u, Error Code = [%d]", nsvcTableApiPtr->nsvcId, ret);
               cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
               free(nsvcTableApiDb);
               return;
            }
            LOG_PRINT(LOG_INFO, "E1Id = %u for NsvcId %u", e1Id, nsvcTableApiPtr->nsvcId);
            ret = getallGbInterfaceTable(&gbInterfaceTableApiPtr, &outRowsGb, &outSizeGb);
            if(CLIB_SUCCESS != ret || 0 == outRowsGb)
            {
               LOG_PRINT(LOG_MAJOR,"%s::getallGbInterfaceTable DB call failed. Sending Nack",__FUNCTION__);
               cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
               free(nsvcTableApiDb);
               return;
            }
            

            /* If Bss is Locked or E1 is locked or transportType is IP (IP_STATIC | IP_DYNAMIC) 
             * update nsvc Admin State in DB only and Send Alarm to AFH
             */
            if (locked == gBssState || locked == gE1Data[e1Id].e1State || gbInterfaceTableApiPtr->transportType != FR)
            {
               ret = updateNsvcAdminState(nsvcTableApiPtr->nsvcId, UNLOCKED);
               if (CLIB_SUCCESS == ret) 
               {
                  LOG_PRINT(LOG_INFO,"%s::Updated adminState of NSVC to UNLOCKED only in DB ",__FUNCTION__);
                  updateNsvcDataStruct(nsvcTableApiPtr->nsvcId, unlockedDisabled, OAMS_RSN_OPERATORINITIATED);
                  cfgSendAckToCm();
                  oamsNsvchCfgAlarmIndBuff.sysAlarm.sysalarmId = ALARM_NSVC_UNLOCKED;
                  oamsNsvchCfgAlarmIndBuff.sysAlarm.info3 = OAMS_OBJTYPE_NSVC;
                  oamsNsvchCfgAlarmIndBuff.sysAlarm.key1 = nsvcTableApiPtr->nsvcId;
                  oamsNsvchCfgAlarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
                  oamsNsvchCfgAlarmIndBuff.sysAlarm.infoStrLen = sprintf((char*)oamsNsvchCfgAlarmIndBuff.sysAlarm.infoString,"NSVC %u is UNLOCKED",oamsNsvchCfgAlarmIndBuff.sysAlarm.key1);
                  LOG_PRINT(LOG_INFO, "Sending Alarm OAMS_CFG_AFH_ALARM_IND (ALARM_NSVC_UNLOCKED)");
                  cfgSendMessage(&oamsNsvchCfgAlarmIndBuff, sizeof(OamsNsvchCfgAlarmInd), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               }
               else
               {
                  LOG_PRINT(LOG_MAJOR,"Updating the NSVC Admin State to UNLOCK for NSVC ID[%u] failed. Error Code = [%d], sending Nack",
                            nsvcTableApiPtr->nsvcId, ret);
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);                  
               }
            }
            /*Mantis 13886 Start*/
            /*Mantis 13939 Start*/
            else 
            {
               if (unlockInProgress == gBssState)
               {
                  LOG_PRINT(LOG_INFO, "Bss Unlock in progress, sending Nack");
                  cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
               }

               /* If Bss is Unlocked  
                * then send Nsvc Unlock Req to NSVCH
                */
               else if(unlocked == gBssState)
               {
                  LOG_PRINT(LOG_INFO,"%s::calling nsvcUnlockReq for nsvcId = %u",__FUNCTION__, nsvcTableApiPtr->nsvcId);
                  nsvcUnlockReq(nsvcTableApiPtr->nsvcId, OAMS_RSN_OPERATORINITIATED);
               }
            }
            free(gbInterfaceTableApiPtr);
            /*Mantis 13886 End*/
            /*Mantis 13939 End*/
         }
         /*Check if Request is for Modification*/
         else if ((LOCKED == nsvcTableApiPtr->adminState) && (LOCKED == nsvcTableApiDb->adminState))
         {
            LOG_PRINT(LOG_INFO, "%s:: Modify is received for NSVC ID [%u]",__FUNCTION__,nsvcTableApiPtr->nsvcId);
            
            ret = doConsistencyChecksOnSetOnNsvcTable(nsvcTableApiPtr, FALSE);

            if( CM_SUCCESS != ret )
            {
               LOG_PRINT(LOG_MAJOR, "doConsistencyChecksOnSetOnNsvcTable failed :: Sending Nack: Error Code [%d]", ret);
               cfgSendNackToCm(ret);
               free(nsvcTableApiDb);
               return;
            }
 
            LOG_PRINT(LOG_INFO, "Consistency Check passed on NsvcTable");
            statusRange = nsvcTableRangeChk(nsvcTableApiPtr);
            
            if (statusRange)
            {
               LOG_PRINT(LOG_INFO, "Range Check passed on NsvcTable");
               ret = updateNsvcTable(nsvcTableApiPtr);
               if (CLIB_SUCCESS != ret)
               {
                  LOG_PRINT(LOG_MAJOR, "DB call updateNsvcTable failed. NSVC ID[%u], Error Code [%d] ",
                            nsvcTableApiPtr->nsvcId, ret);
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
               }
               else
               {
                  LOG_PRINT(LOG_INFO, "Nsvc Table for NSVC ID [%u] modified successfully, sending Ack",
                            nsvcTableApiPtr->nsvcId);
                  cfgSendAckToCm();
               }
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"Insert Row Operation with out of range value, Sending Nack");
               cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
            }
         }
         else
         {
              cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }
      
         free(nsvcTableApiDb);
         break;
      }
      case BSC_API_DEL_NSVCTABLE:
      {
         LOG_PRINT(LOG_INFO, "BSC_API_DEL_NSVCTABLE is received, calling delNsvcTableHandler()");
         delNsvcTableHandler();
         break;
      }
      default:
      {
         LOG_PRINT(LOG_INFO, "Invalid Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
         break;
      }
   }   
   LOG_PRINT(LOG_INFO, "Exiting nsvcObjectLockedHandler()");
   
}

/********************************* Function  Header********************************
Function Name:       nsvcObjectUnlockOrEnableInProgressHandler()
Parameters:          I_Void
Return type:         I_Void
Purpose:             To do the handling of messages in UnlockOrEnableInProgress State
Other Note:
 ************************************************************************************/
I_Void nsvcObjectUnlockOrEnableInProgressHandler(I_Void)
{
   NsvcTableApi                    *nsvcTableApiPtr            = NULL;
   NsvcTableApi                    *nsvcTableApiDb             = NULL;
   sCmMsg                          *receivedCmMsgPtr           = NULL;
   OamsNsvchCfgUnlockResp          *oamsNsvchCfgUnlockRespPtr  = NULL;
   GbInterfaceTableApi             *gbInterfaceTableApiPtr     = NULL;
   I_U8                            index                       = 0;
   I_S32                           ret                         = CLIB_SUCCESS;
   I_U16                           e1Id                        = 0;
   NsvcTableIndices                inData;
   OamsCfgAfhSysAlarm              oamsCfgAfhSysAlarmBuff;

   
   LOG_PRINT(LOG_INFO, "Entering nsvcObjectUnlockOrEnableInProgressHandler()");
   LOG_PRINT(LOG_INFO, "Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
  
   memset(&oamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_NSVCTABLE:
      {
          /*Mantis 13886 Start*/
          /* In case of NSVC LOCK send Nack with Error Code CM_ERR_BSS_UNLOCK_IN_PROGRESS 
          * In case of parameter modification we need to send Nack CM_ERR_INCORRECT_OBJ_STATE
          */
        
         /*Fetch the row from DB*/
         receivedCmMsgPtr = (sCmMsg*)gCfgMsgBuf;
         nsvcTableApiPtr = (NsvcTableApi*)(((I_U8*)receivedCmMsgPtr) + sizeof(sCmMsg));
         inData.nsvcId = nsvcTableApiPtr->nsvcId;
         ret = getNsvcTable(&inData, &nsvcTableApiDb);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR, "Requested Nsvc with NSVC ID [%u] not present in the Db,Error Code = [%d] Sending Nack",nsvcTableApiPtr->nsvcId, ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }


         if ((LOCKED == nsvcTableApiPtr->adminState) && (UNLOCKED == nsvcTableApiDb->adminState))
         {
            LOG_PRINT(LOG_INFO, "%s:: NSVC Lock is received for NSVC ID [%u]",__FUNCTION__,nsvcTableApiPtr->nsvcId);
            
            /*NSVC Lock is recived while Bss UnlockInProgress send Nack with Error Code CM_ERR_BSS_UNLOCK_IN_PROGRESS*/ 
            if (unlockInProgress == gBssState)
            {
               LOG_PRINT(LOG_INFO, "Bss Unlock in progress, sending Nack");
               cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
            }
            else if (lockInProgress == gBssState)
            {
               LOG_PRINT(LOG_INFO, "Bss Lock in progress, sending Nack");
               cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
            }
            /*Mantis 13886 End*/
         }
         /*Check if Request is for Modification*/
         else if (nsvcTableApiPtr->adminState == nsvcTableApiDb->adminState)
         {
            LOG_PRINT(LOG_INFO, "%s:: Modify is received for NSVC ID [%u]",__FUNCTION__,nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }
         else
         {
              cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }

         free(nsvcTableApiDb);
         free(gbInterfaceTableApiPtr);
         break;
      } 
      /* send Nack in  case BSC_API_DEL_NSVCTABLE */
      case BSC_API_DEL_NSVCTABLE:
      {
         LOG_PRINT(LOG_MAJOR, "BSC_API_DEL_NSVCTABLE is received during UnlockOrEnableInProgress, Sending Nack" );
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         break;
      }
      case OAMS_NSVCH_CFG_UNLOCK_RESP:
      {
         oamsNsvchCfgUnlockRespPtr = (OamsNsvchCfgUnlockResp*)gCfgMsgBuf;
         index = getNsvcDataStruct(oamsNsvchCfgUnlockRespPtr->nsvcId);
         if (OAMS_RSN_OPERATORINITIATED == gNsvcData[index].reqType)
         {
            LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_UNLOCK_RESP is received for NSVC [%u] in case of operator initiated NSVC Unlock", 
                      oamsNsvchCfgUnlockRespPtr->nsvcId);
            ret = updateNsvcAdminState(oamsNsvchCfgUnlockRespPtr->nsvcId, UNLOCKED);
            if (CLIB_SUCCESS == ret)
            {
               LOG_PRINT(LOG_INFO,"%s::Updated adminState of NSVC to UNLOCKED in DB ",__FUNCTION__);
               updateNsvcDataStruct(oamsNsvchCfgUnlockRespPtr->nsvcId, unlockedEnabled, OAMS_RSN_OPERATORINITIATED);
               cfgSendAckToCm();
               
               oamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = ALARM_NSVC_UNLOCKED;
               oamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_NSVC;
               oamsCfgAfhSysAlarmBuff.sysAlarm.key1 = oamsNsvchCfgUnlockRespPtr->nsvcId;
               oamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
               oamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf((char*)oamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"NSVC %u is UNLOCKED",oamsCfgAfhSysAlarmBuff.sysAlarm.key1);
               LOG_PRINT(LOG_INFO, "sending Alarm OAMS_CFG_AFH_ALARM_IND(ALARM_NSVC_UNLOCKED) for Nsvc [ nsvcId = %u] ", oamsNsvchCfgUnlockRespPtr->nsvcId);
               cfgSendMessage(&oamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
             } /* End updateNsvcAdminState() */ 
             else
             {
                LOG_PRINT(LOG_MAJOR,"Update Nsvctable for NSVC ID [%u] Not Successfull, Error Code = [%d], Sending Nack",
                          oamsNsvchCfgUnlockRespPtr->nsvcId, ret);
                cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
             } 
         } /* End case Operator Initiated */
         else if (OAMS_RSN_PARENTOBJECTLOCKED == gNsvcData[index].reqType) /*During Bss Unlock or E1 Unlock*/
         {
            LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_UNLOCK_RESP is received for NSVC [%u] in case Parent Object Unlock ", 
                      oamsNsvchCfgUnlockRespPtr->nsvcId);
            ret = updateNsvcAdminState(oamsNsvchCfgUnlockRespPtr->nsvcId, UNLOCKED);
            if (CLIB_SUCCESS == ret)
            {
               LOG_PRINT(LOG_INFO,"%s::Updated adminState of NSVC to UNLOCKED in DB ",__FUNCTION__);
               updateNsvcDataStruct(oamsNsvchCfgUnlockRespPtr->nsvcId, unlockedEnabled, OAMS_RSN_PARENTOBJECTLOCKED);
               /* If no Nsvcs are there for which we are wating for Unlock resp from NSVCH then
                * if Bss Unlock in Progress, inform bssObject Handler that all the NSVCs are enabled
                */ 
               if (ZERO == getEnableInProgressNsvcsCount() )
               {
                  if (unlockInProgress == gBssState)
                  {
                     LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_UNLOCK_RESP is received during BSS Unlock, sending Nsvc Unlock Enable Requst to Nsvcs which are unlcked in DB");
                     informNsvcUnlockEnableForUnlockDisabledNsvcsToBss();
                  }
                  /* get the E1 Id for this Nsvc */
                  ret = getE1IdForNsvcId(oamsNsvchCfgUnlockRespPtr->nsvcId, &e1Id);
                  if( CLIB_SUCCESS != ret)
                  {
                     LOG_PRINT(LOG_MAJOR,"getE1IdForNsvcId for NSVC ID [%u] Not Successfull, Error Code = [%d]",
                               oamsNsvchCfgUnlockRespPtr->nsvcId, ret);
                  }
                  LOG_PRINT(LOG_INFO, "E1Id = %u for NsvcId %u", e1Id, oamsNsvchCfgUnlockRespPtr->nsvcId);
                  /* If no Nsvcs are there for which we are wating for Unlock resp from NSVCH then
                   * If E1 Unlock in Progress, inform E1 Object Handler that all the NSVCs for that E1 are Enabled
                   */
                  if(unlockInProgress == gE1Data[e1Id].e1State)
                  {
                     LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_UNLOCK_RESP is received during E1 Unlock, sending Nsvc Unlock Enable Requst to Nsvcs for this E1 which are unlcked in DB");
                     informNsvcUnlockEnableForUnlockDisabledNsvcsToE1();
                  }
               }
            } /* End updateNsvcAdminState() */
            else
            {
               LOG_PRINT(LOG_MAJOR,"Update Nsvctable for NSVC ID [%u] Not Successfull, Error Code = [%d]",
                         oamsNsvchCfgUnlockRespPtr->nsvcId, ret);
            }
                           
         } /* End case Bss Unlock or E1 Unlock */
         free(nsvcTableApiDb);
         break;
      }
      case OAMS_NSVCH_CFG_LOCK_RESP :
      {
         LOG_PRINT(LOG_INFO, "received OAMS_NSVCH_CFG_LOCK_RESP in UnlockOrEnableInProgress, ignoring this message");
         break;
      }
      default:
      {
         LOG_PRINT(LOG_INFO, "Invalid Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
         break;
      }
    }
   LOG_PRINT(LOG_INFO, "Exiting nsvcObjectUnlockOrEnableInProgressHandler()");
}

/********************************* Function  Header********************************
Function Name:       nsvcObjectUnlockedEnabledHandler()
Parameters:          I_Void
Return type:         I_Void
Purpose:             To do the handling of messages in UnlockedEnabled State
Other Note:
 ************************************************************************************/
I_Void nsvcObjectUnlockedEnabledHandler()
{
   NsvcTableApi                *nsvcTableApiPtr          = NULL;
   NsvcTableApi                *nsvcTableApiDb           = NULL;
   sCmMsg                      *receivedCmMsgPtr         = NULL;
   NsvcTableIndices            inData;
   I_S32                       ret                       = CLIB_SUCCESS;


   LOG_PRINT(LOG_INFO, "Entering nsvcObjectUnlockedEnabledHandler()");
   LOG_PRINT(LOG_INFO, "Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_NSVCTABLE:
      {
         /*Fetch the row from DB*/
         receivedCmMsgPtr = (sCmMsg*)gCfgMsgBuf;
         nsvcTableApiPtr = (NsvcTableApi*)(((I_U8*)receivedCmMsgPtr) + sizeof(sCmMsg));
         inData.nsvcId = nsvcTableApiPtr->nsvcId;
         ret = getNsvcTable(&inData, &nsvcTableApiDb);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR, "Requested Nsvc with NSVC ID [%u] not present in the Db,Error Code = [%d] Sending Nack",
                      nsvcTableApiPtr->nsvcId, ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }

         /* NSVC Lock */
         if ((LOCKED == nsvcTableApiPtr->adminState) && (UNLOCKED == nsvcTableApiDb->adminState))
         {
            LOG_PRINT(LOG_INFO, "NSVC LOcked is Received for NSVC [%u] ", nsvcTableApiPtr->nsvcId);
            /*Mantis 13886 Start*/
    
            if (unlockInProgress == gBssState)
            {
               LOG_PRINT(LOG_INFO, "Bss Unlock in progress, sending Nack");
               cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
            }
            else if (lockInProgress == gBssState)
            {
               LOG_PRINT(LOG_INFO, "Bss Lock in progress, sending Nack");
               cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
            }
            else
            {
               nsvcLockReq(nsvcTableApiPtr->nsvcId, OAMS_RSN_OPERATORINITIATED);
               updateNsvcDataStruct(nsvcTableApiPtr->nsvcId, lockeOrDisableInProgress, OAMS_RSN_OPERATORINITIATED);
            }
            /*Mantis 13886 End*/

         }
         else if ((UNLOCKED == nsvcTableApiPtr->adminState) && (UNLOCKED == nsvcTableApiDb->adminState))
         {
            /*Request is for NSVC table modification*/
            LOG_PRINT(LOG_MAJOR, "Parameter modification for NSVC ID [%u] not Allowed sending Nack",nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }
         else
         {
              cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }

         free(nsvcTableApiDb);
         break;
      }
      case BSC_API_DEL_NSVCTABLE:
      {
         LOG_PRINT(LOG_MAJOR, "Deletion not Allowed in Unlocked-Enabled state,sending Nack");
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         break;
      }
      case OAMS_PSSCM_CFG_ALARM_IND :
      {
	     /* the mesage is handled in Alarmhandler */
	     break;
      }
      case OAMS_NSVCH_CFG_ALARM_IND:
      {
	     /* the mesage is handled in Alarmhandler */
	     break;
      }	 
      default:
      {
         LOG_PRINT(LOG_INFO, "Invalid Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
         break;
      }
   }
   LOG_PRINT(LOG_INFO, "Exiting nsvcObjectUnlockedEnabledHandler()");
}

/********************************* Function  Header********************************
Function Name:       nsvcObjectUnlockedDisabledHandler()
Parameters:          I_Void
Return type:         I_Void
Purpose:             To do the handling of messages in UnlockedDisabled State
Other Note:
 ************************************************************************************/
I_Void nsvcObjectUnlockedDisabledHandler()
{
   NsvcTableApi             *nsvcTableApiPtr  = NULL;
   NsvcTableApi             *nsvcTableApiDb   = NULL;
   sCmMsg                   *receivedCmMsgPtr = NULL;
   NsvcTableIndices         inData;
   I_S32                    ret               = CLIB_SUCCESS;
   /*Mantis 13886 Start*/
   I_U32                    count             = 0;
   I_U16                    outSize           = 0;
   BssTableApi              *bssTable         = NULL;
   /*Mantis 13886 End*/

   /* Mantis 15557 Fix --Start*/
   OamsNsvchCfgAlarmInd  oamsNsvchCfgAlarmIndBuff;
   /* Mantis 15557 Fix --End*/
   
   LOG_PRINT(LOG_INFO, "Entering nsvcObjectUnlockedDisabledHandler()");
   LOG_PRINT(LOG_INFO, "Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_NSVCTABLE:
      {
         /* Mantis 15557 Fix --Start*/
         memset(&oamsNsvchCfgAlarmIndBuff, 0, sizeof(OamsNsvchCfgAlarmInd)); 
         /* Mantis 15557 Fix --End*/

         /*Fetch the row from DB*/
         receivedCmMsgPtr = (sCmMsg*)gCfgMsgBuf;
         nsvcTableApiPtr  = (NsvcTableApi*)(((I_U8*)receivedCmMsgPtr) + sizeof(sCmMsg));
         inData.nsvcId    = nsvcTableApiPtr->nsvcId;

         ret = getNsvcTable(&inData, &nsvcTableApiDb);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR, "Requested Nsvc with NSVC ID [%u] not present in the Db,Error Code = [%d]. Sending Nack",
                      nsvcTableApiPtr->nsvcId, ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }
         /* Nsvc Lock */
         if ((LOCKED == nsvcTableApiPtr->adminState) && (UNLOCKED == nsvcTableApiDb->adminState))
         {
            /*Mantis 13886 Start*/
		    ret = getallBssTable(&bssTable,&count,&outSize);
            if(CLIB_SUCCESS != ret)
            {
               LOG_PRINT(LOG_MAJOR,"Error getting BSS Table, Error Code = [%d] ", ret);
               cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
			   free(nsvcTableApiDb);
               return;
            }
            else
            {
               if ( FALSE == bssTable->gprsEnabled)
               {
                  LOG_PRINT(LOG_INFO, "gprsEnabled is false in BSS Table, sending Nack");
                  cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
                  free(bssTable);
               }
               else
               {
                  if (unlockInProgress == gBssState)
                  {
                     LOG_PRINT(LOG_INFO, "Bss Unlock in progress, sending Nack");
                     cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
                  }
                  else if (lockInProgress == gBssState)
                  {
                     LOG_PRINT(LOG_INFO, "Bss Lock in progress, sending Nack");
                     cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
                  }
                  else
                  {
                     ret = updateNsvcAdminState(nsvcTableApiPtr->nsvcId, LOCKED);
                     if (CLIB_SUCCESS == ret)
                     {
                        LOG_PRINT(LOG_INFO,"%s::Updated adminState of NSVC to LOCKED in DB ",__FUNCTION__);
                        LOG_PRINT(LOG_MAJOR,"Update Nsvc adminState for NSVC ID [%u] Successfull",nsvcTableApiPtr->nsvcId);
                        updateNsvcDataStruct(nsvcTableApiPtr->nsvcId, locked, OAMS_RSN_PARENTOBJECTLOCKED);
                        cfgSendAckToCm();
						/* Mantis 15557 Fix --Start*/
                        oamsNsvchCfgAlarmIndBuff.sysAlarm.sysalarmId = ALARM_NSVC_LOCKED;
                        oamsNsvchCfgAlarmIndBuff.sysAlarm.info3 = OAMS_OBJTYPE_NSVC;
                        oamsNsvchCfgAlarmIndBuff.sysAlarm.key1 = nsvcTableApiPtr->nsvcId;
                        oamsNsvchCfgAlarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
                        oamsNsvchCfgAlarmIndBuff.sysAlarm.infoStrLen = sprintf((char*)oamsNsvchCfgAlarmIndBuff.sysAlarm.infoString,"NSVC %u is LOCKED",oamsNsvchCfgAlarmIndBuff.sysAlarm.key1);
                        LOG_PRINT(LOG_INFO, "Sending Alarm OAMS_CFG_AFH_ALARM_IND (ALARM_NSVC_LOCKED)");
                        cfgSendMessage(&oamsNsvchCfgAlarmIndBuff, sizeof(OamsNsvchCfgAlarmInd), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
						/* Mantis 15557 Fix --End*/
                     }
                     else
                     {
                        LOG_PRINT(LOG_MAJOR, "Db Call updateNsvcAdminState failed, Error Code = [%d], sending Nack", ret);
                        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                     }
                  }
                  free(bssTable);
               }
            }
            /*Mantis 13886 End*/
         }
         else if (nsvcTableApiPtr->adminState == nsvcTableApiDb->adminState)
         {
            /*Request is for Modification*/
            LOG_PRINT(LOG_MAJOR, "Parameter modification for NSVC ID [%u] not Allowed in UnlockedDisabled state, sending Nack",nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }
         else
         {
             cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }

         free(nsvcTableApiDb);
         break;
      }
      case BSC_API_DEL_NSVCTABLE:
      {
         LOG_PRINT(LOG_MAJOR, "Deletion not Allowed in UnlockedDisabled State, sending Nack");
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         break;
      }
      default:
      {
         LOG_PRINT(LOG_INFO, "Invalid Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
         break;   
      }
   }
   LOG_PRINT(LOG_INFO, "Exiting nsvcObjectUnlockedDisabledHandler()");
}

/********************************* Function  Header********************************
Function Name:       nsvcObjectLockOrDisableInProgressHandler()
Parameters:          I_Void
Return type:         I_Void
Purpose:             To do the handling of messages in LockOrDisableInProgress State
Other Note:
 ************************************************************************************/
I_Void nsvcObjectLockOrDisableInProgressHandler()
{
   NsvcTableApi                 *nsvcTableApiPtr         = NULL;
   NsvcTableApi                 *nsvcTableApiDb          = NULL;
   FrLinkTableIndices           frLinkTableIndicesBuff;
   FrLinkTableApi               *frLinkTableApiPtr       = NULL;

   sCmMsg                       *receivedCmMsgPtr       = NULL;
   OamsCfgAfhSysAlarm           oamsCfgAfhSysAlarmBuff;
   NsvcTableIndices             inData;
   OamsNsvchCfgLockResp         *oamsNsvchCfgLockRespPtr = NULL;
   I_U32 index;
   I_S32                        ret                    = CLIB_SUCCESS;
   I_U16                        e1Id                   = 0;

   LOG_PRINT(LOG_INFO, "Entering nsvcLockOrDisableInProgressHandler()");
   LOG_PRINT(LOG_INFO, "Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);

   memset(&oamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_NSVCTABLE:
      {
         /*Fetch the row from DB*/
         receivedCmMsgPtr = (sCmMsg*)gCfgMsgBuf;
         nsvcTableApiPtr = (NsvcTableApi*)(((I_U8*)receivedCmMsgPtr) + sizeof(sCmMsg));
         index =  getNsvcDataStruct(nsvcTableApiPtr->nsvcId);
         /* Operator initiated Nsvc Lock */
         if ((OAMS_RSN_OPERATORINITIATED == gNsvcData[index].reqType) && (LOCKED == nsvcTableApiPtr->adminState))     
         {
            LOG_PRINT(LOG_INFO, "NSVC ID[%u] is already in LockInProgress, Sending Nack", nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         }
         
		 /*  parameter modification */
         else
         {
            LOG_PRINT(LOG_MAJOR, "NSVC ID[%u] is in LockInProgress, Sending Nack", nsvcTableApiPtr->nsvcId);
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }
         break;
      }
      case BSC_API_DEL_NSVCTABLE:
      {
         LOG_PRINT(LOG_MAJOR, "Deletion not allowed in LockInProgress, Sending Nack");
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         break;
      }
      case OAMS_NSVCH_CFG_LOCK_RESP:
      {
         LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_LOCK_RESP is received");
         oamsNsvchCfgLockRespPtr = (OamsNsvchCfgLockResp*)gCfgMsgBuf;         
         /*Fetch the row from DB*/
         inData.nsvcId = oamsNsvchCfgLockRespPtr->nsvcId;
         ret = getNsvcTable(&inData, &nsvcTableApiDb);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR, "Requested Nsvc with NSVC ID [%u] not present in the Db, Error Code = [%d] Sending Nack",
                      oamsNsvchCfgLockRespPtr->nsvcId, ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return;
         }

          frLinkTableIndicesBuff.frChnId = nsvcTableApiDb->frChnId;
          ret = getFrLinkTable(&frLinkTableIndicesBuff,&frLinkTableApiPtr);
          if (CLIB_SUCCESS != ret)
          {
             LOG_PRINT(LOG_MAJOR, "Could not fetch FrChnId [%u] from FrLinkTable, Error Code = [%d] ",
                       frLinkTableIndicesBuff.frChnId, ret);
          }
          free(nsvcTableApiDb);
          /*Update MccLinkresource, Mark TSs as Free, delete rows from FrLinkExtE1TsMccE1TsMapTable for FrChnId, Send SwitchDisconnect to Grhm*/
          LOG_PRINT(LOG_INFO, "calling deallocateContiguousNumMccFrTs()");
          deallocateContiguousNumMccFrTs(frLinkTableApiPtr->frChnId);

         index = getNsvcDataStruct(oamsNsvchCfgLockRespPtr->nsvcId);
         if (OAMS_RSN_OPERATORINITIATED == gNsvcData[index].reqType)
         {
            ret = updateNsvcAdminState(oamsNsvchCfgLockRespPtr->nsvcId, LOCKED);
            if (CLIB_SUCCESS == ret)
            {
               LOG_PRINT(LOG_INFO,"%s::OAMS_NSVCH_CFG_LOCK_RESP is recieved for operator initiated NSVC Lock, Updated adminState of NSVC to UNLOCKED in DB ",__FUNCTION__);
               /*Send Alarm to AFH*/
               oamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = ALARM_NSVC_LOCKED;
               oamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_NSVC;
               oamsCfgAfhSysAlarmBuff.sysAlarm.key1 = oamsNsvchCfgLockRespPtr->nsvcId;
               oamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
               oamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf((char*)oamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"NSVC %u is LOCKED",oamsCfgAfhSysAlarmBuff.sysAlarm.key1);
               cfgSendMessage(&oamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               updateNsvcDataStruct(oamsNsvchCfgLockRespPtr->nsvcId, locked, OAMS_RSN_OPERATORINITIATED);
               cfgSendAckToCm();

               /* If Bss Unlock in Progress and Unlock Request has been sent to NSVCH for unlocked Nsvcs in DB during Bss Unlcok
                * In this case if OAMS_NSVCH_CFG_LOCK_RESP is received for operator initiated Nsvc Lock and No Nsvc is in 
                * UnlockOrEnableInProgress then informNsvcUnlockEnableForUnlockDisabledNsvcsToBss to proceed further in Bss Unlock
                */
               if(nsvcsUnlockInProgress == gBssSubState)
               {  
                  if (ZERO == getEnableInProgressNsvcsCount() )
                  {
                     LOG_PRINT(LOG_INFO,"%s::BSS Unlock In Progress (with gBssSubState is nsvcsUnlockInProgress) , OAMS_NSVCH_CFG_LOCK_RESP is received in LockOrDisableInProgress state, and no other NSVC is in Unlock in Progress, calling informNsvcUnlockEnableForUnlockDisabledNsvcsToBss() to proceed BSS Unlock ",__FUNCTION__);
                     informNsvcUnlockEnableForUnlockDisabledNsvcsToBss();
                  }
               }

            } /* End updateNsvcAdminState() */
            else
            {
               LOG_PRINT(LOG_MAJOR,"Update Nsvctable for NSVC ID [%u] Not Successfull",oamsNsvchCfgLockRespPtr->nsvcId);
            }
         } /* End case operator initiated Lock request */

         else if (OAMS_RSN_PARENTOBJECTLOCKED == gNsvcData[index].reqType)
         {
            updateNsvcDataStruct(oamsNsvchCfgLockRespPtr->nsvcId, unlockedDisabled, OAMS_RSN_PARENTOBJECTLOCKED);

            if (ZERO == getDisableInProgressNsvcsCount())
            {
               /* If no Nsvcs are there for which we are wating for Lock resp from NSVCH then
                * If Bss is in lock in Progress, inform Bss Object Handler that all the NSVCs are Disabled
                */
               if (lockInProgress == gBssState)
               {
                  LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_LOCK_RESP is received during BSS Unlock, sending Nsvc Unlock Enable Requst to Nsvcs which are unlcked in DB");
                  informNsvcUnlockDisableForUnlockedNsvcsToBss();
               }
               /* get the E1 Id for this Nsvc */
               ret = getE1IdForNsvcId(oamsNsvchCfgLockRespPtr->nsvcId, &e1Id);
               if( CLIB_SUCCESS != ret)
               {
                  LOG_PRINT(LOG_MAJOR,"getE1IdForNsvcId for NSVC ID [%u] Not Successfull, Error Code = [%d]",
                            oamsNsvchCfgLockRespPtr->nsvcId, ret);
               }
               LOG_PRINT(LOG_INFO, "E1Id = %u for NsvcId %u", e1Id, oamsNsvchCfgLockRespPtr->nsvcId);
               /* If no Nsvcs are there for which we are wating for Lock resp from NSVCH then
                * If E1 lock in Progress, inform E1 Object Handler that all the NSVCs for that E1 are Disabled
                */
               LOG_PRINT(LOG_INFO, "gE1Data[e1Id].e1State = %u", gE1Data[e1Id].e1State);
               if(lockInProgress == gE1Data[e1Id].e1State)
               {
                  LOG_PRINT(LOG_INFO, "OAMS_NSVCH_CFG_LOCK_RESP is received during E1 Unlock, sending Nsvc Unlock Enable Requst to Nsvcs for this E1 which are unlcked in DB");
                  informNsvcUnlockDisableForUnlockedNsvcsToE1();
               }
            }

         } /* End case parent object Locked */
         break;
      } /* end case OAMS_NSVCH_CFG_LOCK_RESP */
      
      case OAMS_NSVCH_CFG_UNLOCK_RESP :
      {
         LOG_PRINT(LOG_INFO, "received OAMS_NSVCH_CFG_UNLOCK_RESP in LockOrDisableInProgress, ignoring this message");
         break;
      }
      case OAMS_PSSCM_CFG_ALARM_IND :
      {
         /* the mesage is handled in Alarmhandler */
         break;
      }
      case OAMS_NSVCH_CFG_ALARM_IND:
      {
         /* the mesage is handled in Alarmhandler */
         break;
      }
      default:
      {
         LOG_PRINT(LOG_INFO, "Invalid Message Received = %u",((SysHdr*) gCfgMsgBuf)->msgType);
         break;
      }
   }
   LOG_PRINT(LOG_INFO, "Exiting nsvcLockOrDisableInProgressHandler()");
}

/********************************* Function  Header********************************
Function Name:       initiateNsvcLockDisableForUnlockedNsvcs()
Parameters:          I_Void
Return type:         I_Void
Purpose:             disables all the Nsvcs that are Unlocked in DB 
                    (called from BssObjectHandler when BSS is Locked)
Other Note:
 ************************************************************************************/
I_Void initiateNsvcLockDisableForUnlockedNsvcs()
{
   I_U32 i;
   I_S32 ret = CLIB_SUCCESS;
   I_U16 e1Id = 0;
   I_Bool allNsvcsDisabled = TRUE;
   TrunkTableApi *trunkTableApiPtr = NULL;
   TrunkTableIndices trunkTableInidcesBuff;
   
   LOG_PRINT(LOG_INFO,"Entering initiateNsvcLockDisableForUnlockedNsvcs()");
   
   gBssSubState = nsvcsLockInProgress;
   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS;i++ )
   {
      if ((FALSE == gNsvcData[i].availability) && (unlockedEnabled == gNsvcData[i].nsvcState))
      {
         ret = getE1IdForNsvcId(gNsvcData[i].nsvcId, &e1Id);
         LOG_PRINT(LOG_INFO, "E1Id = %u for NsvcId %u", e1Id, gNsvcData[i].nsvcId);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "No E1 present for NsvcId %u, Error Code = [%d]", gNsvcData[i].nsvcId, ret);
            return;
         }
         trunkTableInidcesBuff.e1Num = e1Id;
         ret = getTrunkTable(&trunkTableInidcesBuff, &trunkTableApiPtr);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "DB call getTrunkTable failed, returned Error Code = [%d]",ret);
            return;
         }
         if(LOCKED != trunkTableApiPtr->adminState)
         {
            LOG_PRINT(LOG_INFO, "calling nsvcLockReq()");
            nsvcLockReq(gNsvcData[i].nsvcId, OAMS_RSN_PARENTOBJECTLOCKED);
            
            gNsvcData[i].nsvcState = lockeOrDisableInProgress;
            gNsvcData[i].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
            allNsvcsDisabled = FALSE;
         }
      }
      else if ((gNsvcData[i].availability == FALSE) && (gNsvcData[i].nsvcState == lockeOrDisableInProgress))
      {
         allNsvcsDisabled = FALSE;
      }
   }
   
   if (TRUE == allNsvcsDisabled)
   {
      LOG_PRINT(LOG_INFO, "No Nsvc is Unlocked, calling informNsvcUnlockDisableForUnlockedNsvcsToBss() to Proceed further in BSS Lock");
      informNsvcUnlockDisableForUnlockedNsvcsToBss();
   }
   LOG_PRINT(LOG_INFO,"Exiting initiateNsvcLockDisableForUnlockedNsvcs()");
}


/********************************* Function  Header********************************
Function Name:       initiateNsvcUnlockEnableForUnlockedDisabledNsvcs()
Parameters:          I_Void
Return type:         I_Void
Purpose:             enables all the Nsvcs that are Unlocked in DB 
                    (called from BssObjectHandler when BSS is Unlocked)
Other Note:
 ************************************************************************************/
I_Void initiateNsvcUnlockEnableForUnlockedDisabledNsvcs()
{
   I_U32 i = 0;
   I_S32 ret = CLIB_SUCCESS;
   I_U16 e1Id = 0;
   I_Bool allNsvcsEnabled = TRUE;
   TrunkTableApi *trunkTableApiPtr = NULL;
   TrunkTableIndices trunkTableInidcesBuff;
   LOG_PRINT(LOG_INFO,"Entering initiateNsvcUnlockEnableForUnlockedDisabledNsvcs()");

   gBssSubState = nsvcsUnlockInProgress;
   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS;i++ )
   {
      if (FALSE == gNsvcData[i].availability && unlockedDisabled == gNsvcData[i].nsvcState)
      {
         ret = getE1IdForNsvcId(gNsvcData[i].nsvcId, &e1Id);
         if (CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "No E1 present for NsvcId %u, Error Code = [%d]", gNsvcData[i].nsvcId, ret);
            return;
         }
         trunkTableInidcesBuff.e1Num = e1Id;
         ret = getTrunkTable(&trunkTableInidcesBuff, &trunkTableApiPtr);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_INFO, "DB call getTrunkTable failed, returned Error Code = [%d]",ret);
            return;
         }
         LOG_PRINT(LOG_INFO, "E1Id = %u for NsvcId %u", e1Id, gNsvcData[i].nsvcId);
         if(LOCKED != trunkTableApiPtr->adminState) 
         {
            /*Send Unlock Request To Nsvc*/
            gNsvcData[i].nsvcState = unlockOrEnableInProgress;
            
            /* OAMS_RSN_PARENTOBJECTLOCKED is used for both LOCK/UNLOCK, The other one is 
             * OAMS_RSN_OPERATOR_INITIATED just to differentiate whether the LOCK/UNLOCK 
             * is operator initiated or because of LOCK?UNLOCK of parent object
             */
            gNsvcData[i].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
            allNsvcsEnabled = FALSE;
   
            LOG_PRINT(LOG_INFO, "calling nsvcUnlockReq()");
            nsvcUnlockReq(gNsvcData[i].nsvcId, OAMS_RSN_PARENTOBJECTLOCKED);
         }
      }
   }
   if ( TRUE == allNsvcsEnabled)
   {
      LOG_PRINT(LOG_INFO, "No Nsvc is Unlocked, calling informNsvcUnlockEnableForUnlockDisabledNsvcsToBss() to Proceed further in BSS Unlock");
      informNsvcUnlockEnableForUnlockDisabledNsvcsToBss();  
   }
   LOG_PRINT(LOG_INFO,"Exiting initiateNsvcUnlockEnableForUnlockedDisabledNsvcs()");
}

/********************************* Function  Header********************************
Function Name:       initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1()
Parameters:          e1Id : E1 Id for which the Nsvcs are to be Enabled
Return type:         I_Bool true indicates that NSVC Unlock request is sent to NSVCH
Purpose:             Enables all the Nsvcs for that E1 that are Unlocked in DB 
                    (called from E1ObjectHandler when E1 is Unlocked)
Other Note:
 ************************************************************************************/

/*Mantis 13886 Start*/
I_Bool initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1(I_U32 e1Id)
{
   NsvcTableApi   *nsvcTablePtr     = NULL;
   NsvcTableApi   *tempNsvcTablePtr = NULL;
   I_U32          noOfRows          = 0;
   I_U16          rowSize           = 0;
   I_S32 ret                        = CLIB_SUCCESS;
   I_U16          i, index;
   I_Bool         allNsvcsEnabled   = TRUE;
   
   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   I_U32                outRowsGb              = 0;
   I_U16                outSizeGb              = 0;

   LOG_PRINT(LOG_INFO,"Entering initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1(), e1Id = %u", e1Id);
   ret = getNsvcsForE1Id(e1Id, &nsvcTablePtr, &noOfRows, &rowSize);
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_INFO, "No NSVC present for E1 Id %u, Error Code = [%d]", e1Id, ret);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1()");
      return I_FALSE;
   }
   ret = getallGbInterfaceTable(&gbInterfaceTableApiPtr, &outRowsGb, &outSizeGb);
   if(CLIB_SUCCESS != ret || 0 == outRowsGb)
   {
      free(nsvcTablePtr);
      LOG_PRINT(LOG_MAJOR,"%s::getallGbInterfaceTable DB call failed.",__FUNCTION__);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1()");
      return I_FALSE;
   }
   if ( FR != gbInterfaceTableApiPtr->transportType)
   {
      free(nsvcTablePtr);
      LOG_PRINT(LOG_MAJOR,"%s::transportType is not FR so NSVC to Enable",__FUNCTION__);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1()");
      return I_FALSE;
   }
            
   for (i = 0; i < noOfRows; i++)
   {
      tempNsvcTablePtr = (NsvcTableApi *)(((I_U8*)nsvcTablePtr) + i * rowSize);
      index = getNsvcDataStruct(tempNsvcTablePtr->nsvcId);
      if (unlockedDisabled == gNsvcData[index].nsvcState);
      {
         /*Send Unlock Request To Nsvc*/

         /* OAMS_RSN_PARENTOBJECTLOCKED is used for both LOCK/UNLOCK, The other one is 
          * OAMS_RSN_OPERATOR_INITIATED just to differentiate whether the LOCK/UNLOCK 
          * is operator initiated or because of LOCK?UNLOCK of parent object
          */
         
         LOG_PRINT(LOG_INFO, "calling nsvcUnlockReq()");
         nsvcUnlockReq(tempNsvcTablePtr->nsvcId, OAMS_RSN_PARENTOBJECTLOCKED);
         
         gNsvcData[index].nsvcState = unlockOrEnableInProgress;
         gNsvcData[index].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
         allNsvcsEnabled = FALSE;
      }
   }
   free(nsvcTablePtr);
   if (TRUE == allNsvcsEnabled)
   {
      LOG_PRINT(LOG_INFO, "No Nsvc is Unlocked for this E1 [e1Id = %u] ", e1Id);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1()");
      return I_FALSE;
   }
   LOG_PRINT(LOG_INFO,"Exiting initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1()");
   return I_TRUE;
}
/*Mantis 13886 End*/

/********************************* Function  Header********************************
Function Name:       initiateNsvcLockDisableForUnlockedNsvcsForE1()
Parameters:          e1Id : E1 Id for which the Nsvcs are to be Disabled
Return type:         I_Bool true indicates that NSVC Lock request is sent to NSVCH
Purpose:             Disables all the Nsvcs for that E1 that are Unlocked in DB 
                    (called from E1ObjectHandler when E1 is Locked)
Other Note:
 ************************************************************************************/
/*Mantis 13886 Start*/
I_Bool initiateNsvcLockDisableForUnlockedNsvcsForE1(I_U32 e1Id)
{
   NsvcTableApi        *nsvcTablePtr     = NULL;
   NsvcTableApi        *tempNsvcTablePtr = NULL;
   I_U32               noOfRows          = 0;
   I_U16               rowSize           = 0;
   I_S32               ret               = CLIB_SUCCESS;
   I_U16               i, index;
   I_Bool              allNsvcsDisabled  = TRUE;
   GbInterfaceTableApi *gbInterfaceTableApiPtr = NULL;
   I_U32                outRowsGb              = 0;
   I_U16                outSizeGb              = 0;


   LOG_PRINT(LOG_INFO,"Entering initiateNsvcLockDisableForUnlockedNsvcsForE1()");
   ret = getNsvcsForE1Id(e1Id, &nsvcTablePtr, &noOfRows, &rowSize);
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_INFO, "No NSVC present for E1 Id %u, Error Code = [%d] ", e1Id, ret);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcLockDisableForUnlockedNsvcsForE1()");
      return I_FALSE;
   }
   
   ret = getallGbInterfaceTable(&gbInterfaceTableApiPtr, &outRowsGb, &outSizeGb);
   if(CLIB_SUCCESS != ret || 0 == outRowsGb)
   {
      free(nsvcTablePtr);
      LOG_PRINT(LOG_MAJOR,"%s::getallGbInterfaceTable DB call failed.",__FUNCTION__);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcLockDisableForUnlockedNsvcsForE1()");
      return I_FALSE;
   }
   if ( FR != gbInterfaceTableApiPtr->transportType)
   {
      free(nsvcTablePtr);
      LOG_PRINT(LOG_MAJOR,"%s::transportType is not FR. So NSVC to Enable",__FUNCTION__);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcLockDisableForUnlockedNsvcsForE1()");
      return I_FALSE;
   }
            
   for (i = 0; i < noOfRows; i++)
   {
      tempNsvcTablePtr = (NsvcTableApi *)(((I_U8*)nsvcTablePtr) + i * rowSize);
      index = getNsvcDataStruct(tempNsvcTablePtr->nsvcId);
      LOG_PRINT(LOG_INFO, " index = %u for nsvcId = %u nsvcState = %u " ,  index, tempNsvcTablePtr->nsvcId, gNsvcData[index].nsvcState);
      if (unlockedEnabled == gNsvcData[index].nsvcState)
      {
         LOG_PRINT(LOG_INFO, "calling nsvcLockReq()");
         nsvcLockReq(tempNsvcTablePtr->nsvcId, OAMS_RSN_PARENTOBJECTLOCKED);

         gNsvcData[index].nsvcState = lockeOrDisableInProgress;
         gNsvcData[index].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
         allNsvcsDisabled = FALSE;
      }
   }
   free(nsvcTablePtr);
   if (TRUE == allNsvcsDisabled)
   {
      LOG_PRINT(LOG_INFO, "No Nsvc is Unlocked for this E1 [ e1Id = %u]", e1Id);
      LOG_PRINT(LOG_INFO,"Exiting initiateNsvcLockDisableForUnlockedNsvcsForE1()");
      return I_FALSE;
   }
   LOG_PRINT(LOG_INFO,"Exiting initiateNsvcLockDisableForUnlockedNsvcsForE1()");
   return I_TRUE;
}
/*Mantis 13886 End*/


/********************************* Function  Header********************************
Function Name:       updateNsvcDataStruct()
Parameters:          nsvcId : NSVC Id for which the Updation is to be done
                     state  : state that is to be set for that Nsvc
                     reqType: reqType to set
Return type:         I_Void
Purpose:             updates the Nsvc state and reqType in gNsvcData array for 
                     the given NsvcId
Other Note:
 ************************************************************************************/
I_Void updateNsvcDataStruct(I_U32 nsvcId, I_S32 state, I_Bool reqType)
{
   I_U8 i = 0;
   LOG_PRINT(LOG_INFO,"Entering updateNsvcDataStruct()");

   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS;i++ )
   {
      if (gNsvcData[i].nsvcId == nsvcId)
      {
         gNsvcData[i].nsvcState = state;
         gNsvcData[i].reqType = reqType;
      }
   }
   LOG_PRINT(LOG_INFO,"Exiting updateNsvcDataStruct()");
}

/********************************* Function  Header********************************
Function Name:       getNsvcDataState()
Parameters:          I_Void
Return type:         index index of the gNsvcData
Purpose:             returns the index of the gNsvcData array at which the Nsvc is present
Other Note:
 ************************************************************************************/
I_U8 getNsvcDataState()
{
   NsvcTableApi                 *nsvcTableApiPtr           = NULL;
   sCmMsg                       *receivedCmMsgPtr          = NULL;
   OamsNsvchCfgUnlockResp       *oamsNsvchCfgUnlockRespPtr = NULL;
   OamsNsvchCfgLockResp         *oamsNsvchCfglockRespPtr   = NULL;
   OamsNsvchCfgAlarmInd         *oamsNsvchCfgAlarmIndPtr   = NULL;
   OamsPsscmCfgAlarmInd         *oamsPsscmCfgAlarmIndPtr   = NULL;
   I_U8                         index                      = 0;

   LOG_PRINT(LOG_INFO,"Entering getNsvcDataState()");
   LOG_PRINT(LOG_INFO,"Message Recvd = %u",((SysHdr*) gCfgMsgBuf)->msgType);

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_NSVCTABLE:
      {
        receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
        nsvcTableApiPtr = (NsvcTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
        index = getNsvcDataStruct(nsvcTableApiPtr->nsvcId);
        break;
      }
      case BSC_API_DEL_NSVCTABLE:
      {
        receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
        nsvcTableApiPtr = (NsvcTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
        index = getNsvcDataStruct(nsvcTableApiPtr->nsvcId);
        break;
      }
      case OAMS_NSVCH_CFG_UNLOCK_RESP:
      {
        oamsNsvchCfgUnlockRespPtr = (OamsNsvchCfgUnlockResp*)gCfgMsgBuf;
        index = getNsvcDataStruct(oamsNsvchCfgUnlockRespPtr->nsvcId);
        break;
      }
      case OAMS_NSVCH_CFG_ALARM_IND:
      {
        oamsNsvchCfgAlarmIndPtr = (OamsNsvchCfgAlarmInd*)gCfgMsgBuf;
        index = getNsvcDataStruct(oamsNsvchCfgAlarmIndPtr->sysAlarm.key1);
        break;
      }
      case OAMS_PSSCM_CFG_ALARM_IND:
      {
        oamsPsscmCfgAlarmIndPtr = (OamsPsscmCfgAlarmInd*)gCfgMsgBuf;
        index = getNsvcDataStruct(oamsPsscmCfgAlarmIndPtr->sysAlarm.key1);
        break;
      }
      case OAMS_NSVCH_CFG_LOCK_RESP:
      {
        oamsNsvchCfglockRespPtr = (OamsNsvchCfgLockResp*)gCfgMsgBuf;
        index = getNsvcDataStruct(oamsNsvchCfglockRespPtr->nsvcId);
        break;
      }
      default:
      {
         break;
      }
   }

   LOG_PRINT(LOG_INFO, "Exiting getNsvcDataState()");
   return index;
}

/********************************* Function  Header********************************
Function Name:       getNsvcDataStruct()
Parameters:          nsvcId for which index is to be returned
Return type:         index of the gNsvcData
Purpose:             returns the index of the gNsvcData array at which the Nsvc is present
Other Note:
 ************************************************************************************/
I_U8 getNsvcDataStruct(I_U32 nsvcId)
{
   I_U8 i = 0;

   LOG_PRINT(LOG_INFO,"Entering getNsvcDataStruct()");
   LOG_PRINT(LOG_INFO,"nsvcId = %u",nsvcId);
   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS; i++ )
   {

      if (nsvcId == gNsvcData[i].nsvcId && FALSE == gNsvcData[i].availability)
      {
         LOG_PRINT(LOG_INFO,"Index = %d for NSVC ID = %u",i,nsvcId);
         return i;
      }
   }
   LOG_PRINT(LOG_INFO,"Exiting getNsvcDataStruct()");
   return i;
}

/********************************* Function  Header********************************
Function Name:       resetNsvcDataStruct()
Parameters:          nsvcId for which index is to be returned
Return type:         index of the gNsvcData
Purpose:             resets the gNsvcData for the particular index for the given NsvcId
Other Note:
 ************************************************************************************/
I_Void resetNsvcDataStruct(I_U16 nsvcId)
{
   I_U8 i = 0;
   
   LOG_PRINT(LOG_INFO, "Entering function resetNsvcDataStruct()");
   LOG_PRINT(LOG_INFO,"Resetting NSVC Data structures for nsvcId: %d", nsvcId);
   for(i = 0; i < OAMS_CFG_MAX_NUM_NSVCS; i++)
   {
      if (gNsvcData[i].nsvcId == nsvcId)
      {
         gNsvcData[i].nsvcState = ZERO;
         gNsvcData[i].availability = TRUE;
         gNsvcData[i].nsvcId = ZERO;
         gNsvcData[i].reqType = ZERO;
      }

   }
   LOG_PRINT(LOG_INFO, "Exiting function resetNsvcDataStruct()");
}

/********************************* Function  Header********************************
Function Name:       initNsvcDataStruct()
Parameters:          nsvcId for which nsvcData is to be reset
Return type:         I_Void
Purpose:             initializes a new element in gNsvcData with default values
Other Note:
 ************************************************************************************/
I_Void initNsvcDataStruct(I_U16 nsvcId)
{
   NsvcTableApi    *nsvcTableApiPtr = NULL;
   I_U32           rowCount         = ZERO;
   I_U16           outSize          = ZERO;
   I_U32           index            = 0;

   LOG_PRINT(LOG_INFO, "Entering function initNsvcDataStruct()");
   
   LOG_PRINT(LOG_INFO,"Initialize NSVC Data structures for nsvcId: %u", nsvcId);
   
   /* Mantis Fix 14400 --Start*/
   LOG_PRINT(LOG_INFO,"Initialize NSVC Data structures for nsvcId: %u", nsvcId);
   
   for ( index = 0; index < OAMS_CFG_MAX_NUM_NSVCS; index++ )
   {
      if (TRUE == gNsvcData[index].availability)
      {
         gNsvcData[index].nsvcState = locked;
         gNsvcData[index].availability = FALSE;
         gNsvcData[index].nsvcId = nsvcId;
         gNsvcData[index].reqType = ZERO;
         break;
      }
   }
   /* Mantis Fix 14400 --End*/
   
   LOG_PRINT(LOG_INFO, "Exiting function initNsvcDataStruct()");
}

/********************************* Function  Header********************************
Function Name:       nsvcUnlockReq()
Parameters:          nsvcId for which nsvcData is to be reset
                     reason; reason for Nsvc Unlock
Return type:         I_Void
Purpose:             fills and sends OamsCfgNsvchUnlockReq to NSVCH
Other Note:
 ************************************************************************************/
I_Void nsvcUnlockReq(I_U16 nsvcId, I_U8 reason)
{
  
   NsvcTableIndices nsvcIndicesBuff;
   FrLinkTableIndices frLinkTableIndicesBuff;
   FrLinkTableApi *frLinkTableApiPtr = NULL;
   NsvcTableApi * nsvcTableApiPtr = NULL; 
   OamsCfgNsvchUnlockReq oamsCfgNsvchUnlockReqBuff;
   I_S32 ret = CLIB_SUCCESS;
  
   /*Fetch the row from DB*/
   nsvcIndicesBuff.nsvcId = nsvcId;
   ret = getNsvcTable(&nsvcIndicesBuff, &nsvcTableApiPtr);
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR, "DB call getNsvcTable failed for NSVC ID [%u]. Error Code = [%d]", nsvcId, ret);
      return;
   }
   
   frLinkTableIndicesBuff.frChnId = nsvcTableApiPtr->frChnId;
   ret = getFrLinkTable(&frLinkTableIndicesBuff,&frLinkTableApiPtr);
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR, "Could not fetch FrChnId [%u] from FrLinkTable, Error Code = [%d] ",
                frLinkTableIndicesBuff.frChnId, ret);
      free(nsvcTableApiPtr);
      return;
   }

   /* allocateContiguousNumMccFrTs will search contiguous Mcc Link 
    * Resource for FR and if found allocate them and 
    * insert row in FrLinkExtE1TsMccE1TsMapTableApi 
    * and send SwitchConnect to GRHM 
    * If allocateContiguousNumMccFrTs returns FALSE, send Nack to CM
    */
   LOG_PRINT(LOG_INFO, "calling allocateContiguousNumMccFrTs()");
   if( FALSE == allocateContiguousNumMccFrTs(frLinkTableApiPtr->frChnId, frLinkTableApiPtr->e1Id, frLinkTableApiPtr->startTs, frLinkTableApiPtr->numTs))
   {
      if (OAMS_RSN_OPERATORINITIATED == reason)
      {
         cfgSendNackToCm(CM_ERR_BSS_LOCK_REQUIRED); 
         free(frLinkTableApiPtr); 
         free(nsvcTableApiPtr);
         return;
      }
   }

   free(frLinkTableApiPtr); 
   free(nsvcTableApiPtr);

   oamsCfgNsvchUnlockReqBuff.nsvcId = nsvcId;
   oamsCfgNsvchUnlockReqBuff.reason = reason;

   cfgSendMessage(&oamsCfgNsvchUnlockReqBuff, sizeof(OamsCfgNsvchUnlockReq), ENT_OAMS_PSSCM, OAMS_CFG_NSVCH_UNLOCK_REQ, 0); 
   
   /* In case of operator initiated NSVC Unlock, update NsvcObject Handler State
    * In case of Nsvc Unlock during E1/Bss Unlock, the ste is being updated at 
    * the time of call to this function so no need to update here 
    */
   if (OAMS_RSN_OPERATORINITIATED == reason)
   {
      LOG_PRINT(LOG_INFO, "NSVC Unlock is operator initiated , Changing nsvcState to unlockOrEnableInProgress for nsvcId = %u", nsvcId);
      updateNsvcDataStruct(nsvcId, unlockOrEnableInProgress, reason);
   }
 
}

/********************************* Function  Header********************************
Function Name:       nsvcLockReq()
Parameters:          nsvcId for which nsvcData is to be reset
                     reason; reason for Nsvc Unlock
Return type:         I_Void
Purpose:             fills and sends OamsCfgNsvchUnlockReq to NSVCH
Other Note:
 ************************************************************************************/
I_Void nsvcLockReq(I_U16 nsvcId, I_U8 reason)
{
  OamsCfgNsvchLockReq oamsCfgNsvchLockReqBuff;
    
  LOG_PRINT(LOG_INFO,"Entering nsvcLockReq()");
  oamsCfgNsvchLockReqBuff.nsvcId = nsvcId;
  oamsCfgNsvchLockReqBuff.reason = reason;

  cfgSendMessage(&oamsCfgNsvchLockReqBuff, sizeof(OamsCfgNsvchLockReq), ENT_OAMS_PSSCM, OAMS_CFG_NSVCH_LOCK_REQ, 0);
  LOG_PRINT(LOG_INFO,"Exiting nsvcLockReq()");
   
}

/********************************* Function  Header********************************
Function Name:       sendSwitchConnect2Grhm()
Parameters:          frE1Id : E1Id for E1 used for Fr Link
                     frE1Ts : Timeslot of Fr E1 
                     mccE1Id: MccE1 Id
                     mccE1Ts: Timeslot of MccE1  
Return type:         I_Void
Purpose:             fills and sends OamsCfgGrhmSwitchConnect to NSVCH
Other Note:
 ************************************************************************************/
I_Void sendSwitchConnect2Grhm(I_U32 frE1Id, I_U32 frE1Ts, I_U32 mccE1Id, I_U32 mccE1Ts)
{
   LOG_PRINT(LOG_INFO,"Entering sendSwitchConnect2Grhm()");
   OamsCfgGrhmSwitchConnect oamsCfgGrhmSwitchConnectBuff;
   
   oamsCfgGrhmSwitchConnectBuff.firstE1Num = frE1Id;
   oamsCfgGrhmSwitchConnectBuff.firstTimeSlotNum = frE1Ts;
   oamsCfgGrhmSwitchConnectBuff.secondE1Num = mccE1Id;
   oamsCfgGrhmSwitchConnectBuff.secondTimeSlotNum = mccE1Ts;
   cfgSendMessage(&oamsCfgGrhmSwitchConnectBuff, sizeof(OamsCfgGrhmSwitchConnect), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_CONNECT, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendSwitchConnect2Grhm()");
}

/********************************* Function  Header********************************
Function Name:       sendSwitchDisconnect2Grhm()
Parameters:          frE1Id : E1Id for E1 used for Fr Link
                     frE1Ts : Timeslot of Fr E1 
                     mccE1Id: MccE1 Id
                     mccE1Ts: Timeslot of MccE1  
Return type:         I_Void
Purpose:             fills and sends OamsCfgGrhmSwitchDisconnect to NSVCH
Other Note:
 ************************************************************************************/
I_Void sendSwitchDisconnect2Grhm (I_U32 frE1Id, I_U32 frE1Ts, I_U32 mccE1Id, I_U32 mccE1Ts)
{
   LOG_PRINT(LOG_INFO,"Entering sendSwitchDisconnect2Grhm()");
   OamsCfgGrhmSwitchDisconnect     oamsCfgGrhmSwitchDisconnectBuff;
   
   oamsCfgGrhmSwitchDisconnectBuff.firstE1Num = frE1Id;
   oamsCfgGrhmSwitchDisconnectBuff.firstTimeSlotNum = frE1Ts;
   oamsCfgGrhmSwitchDisconnectBuff.secondE1Num = mccE1Id;
   oamsCfgGrhmSwitchDisconnectBuff.secondTimeSlotNum = mccE1Ts;
   cfgSendMessage(&oamsCfgGrhmSwitchDisconnectBuff, sizeof(OamsCfgGrhmSwitchDisconnect), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_SWITCH_DISCONNECT, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendSwitchDisconnect2Grhm()");
}

/********************************* Function  Header********************************
Function Name:       getEnableInProgressNsvcsCount()
Parameters:          I_Void
Return type:         I_U32 number of Nsvcs 
Purpose:             fills and sends OamsCfgNsvchUnlockReq to NSVCH
Other Note:
 ************************************************************************************/
I_U32 getEnableInProgressNsvcsCount()
{
   I_U32 count = 0;
   I_U32 i = 0;

   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS;i++ )
   {
      if (FALSE == gNsvcData[i].availability && unlockOrEnableInProgress == gNsvcData[i].nsvcState)
      {
         count++;
      }
   }
   return count;
}
/********************************* Function  Header********************************
Function Name:       getDisableInProgressNsvcsCount()
Parameters:          I_Void
Return type:         I_U32 number of Nsvcs 
Purpose:             fills and sends OamsCfgNsvchUnlockReq to NSVCH
Other Note:
 ************************************************************************************/
I_U32 getDisableInProgressNsvcsCount()
{
   I_U32 count = 0;
   I_U32 i = 0;

   for ( i = 0; i < OAMS_CFG_MAX_NUM_NSVCS;i++ )
   {
      if (FALSE == gNsvcData[i].availability && lockeOrDisableInProgress == gNsvcData[i].nsvcState)
      {
         count++;
      }
   }
   return count;
}
/********************************* Change History ****************************************
   Release     Patch       Author                Description
   R2.5                    Aricent Gurgaon       Initial Draft for NSVC Object Handler

 ************************************** End *********************************************/
