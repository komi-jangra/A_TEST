/***********************************File Header ***************************
  File Name        : Oamcfg_e1timeSlot_object_handler.c
Purpose          : This function contains function defintions required for
handling Timeslot object.
Project          :  BSC
Subsystem        : OAMS
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>
I_S8 e1Index;
I_S8 timeslotIndex;

/********************************* Function  Header********************************
  Function Name:       getTimeSlotObjectState()
Parameters:          void
Return type:         void
Purpose:             To get the object state of received message.
Other Note:
 ************************************************************************************/
objectState getTimeSlotObjectState(I_U16 e1Num,I_U16 tsNum)
{
   objectState state;
   state = gE1TimeslotData[e1Num][tsNum].e1TimeslotState;
   e1Index = (e1Num);
   timeslotIndex = tsNum;
   LOG_PRINT(LOG_DEBUG,"getTimeSlotObjectState: e1Num %d tsNum %d ",e1Num,tsNum);
   return state;     
}

/********************************* Function  Header********************************
  Function Name:       getStateTimeSlot()
Parameters:          void
Return type:         objectState
Purpose:             To typecast the received message buffer based on message type
Other Note:
 ************************************************************************************/
objectState getStateTimeSlot()
{
   objectState state;
   I_U16 e1Num=0;
   I_U16 tsNum=0;
   /*Pointers to point the Received Message*/

   /* Fix for SPR 169 Start....*/
   AbisTimeSlotPerTableApi *e1TimeSlotObjPtr;
   /* Fix for SPR 169 End....*/
   sCmMsg  *receivedCmMsgPtr = 0;

   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case BSC_API_SET_ABISTIMESLOTPERTABLE:
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         e1TimeSlotObjPtr = (AbisTimeSlotPerTableApi *)((I_S8 *)receivedCmMsgPtr + sizeof(sCmMsg)); /*point to payload of received message*/ 
         state = getTimeSlotObjectState(e1TimeSlotObjPtr->e1Num,e1TimeSlotObjPtr->tsNum); 
         break;                     

      case CSAPP_GRHM_CFG_ALARM_IND:
         LOG_PRINT(LOG_INFO,"  CSAPP_GRHM_CFG_ALARM_IND: ..."); 
         SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
         if(recAlarmPtr->key1 == OAMS_OBJTYPE_TIMESLOT)
         {
            /*unmask the e1Num & tsNum  from rMsgtimeSlotGrhmUnlockresp->objectId*/         
            unMaskBits(recAlarmPtr->key2,&tsNum,&e1Num);          
            state = getTimeSlotObjectState(e1Num,tsNum);           
         } 
         break;
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            unMaskBits((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);          
            state = getTimeSlotObjectState(e1Num,tsNum);           
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            unMaskBits((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);          
            state = getTimeSlotObjectState(e1Num,tsNum);           
            break;
         }
      case CSAPP_GRHM_CFG_UNLOCK_FAIL:
         {
            unMaskBits((( CsappGrhmCfgUnlockFail* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);          
            state = getTimeSlotObjectState(e1Num,tsNum);           
            LOG_PRINT(LOG_MAJOR,"CSAPP_GRHM_CFG_UNLOCK_FAIL not expected for E1");   
            break;
         }
#if 0 /* CS4.0 HA Stack Changes */
      case BSC_API_SET_LINKADMINSTATETABLE:    
         /* Already e1Index,timeslotIndex has been assigned in the scmMsgHandler() */
         state = getTimeSlotObjectState(e1Index,timeslotIndex); 
         break;                          
#endif

      default:
         break;
   }/*switch ends here..*/
   return state;

}


/********************************* Function  Header********************************
  Function Name:       e1TimeSlotObjectHandler()
Parameters:          void
Return type:         void
Purpose:             To handle all states of the e1TimeSlotObject
Other Note:          This is invoked by the cfg main  module.
 ************************************************************************************/
void e1TimeSlotObjectHandler()
{
   objectState state;
   state = getStateTimeSlot();
   switch (state)
   {
      case locked:
         setTimeSlot();
         break;

      case unlockInProgress:
         timeSlotUnlockInProgressHandler();
         break;
      case unlocked:
         setTimeSlot();
         break;
      case lockInProgress:
         timeSlotLockInProgressHandler(); 
         break;
      default:
         break;
   }
}/*end e1TimeSlotObjectHandler*/



/********************************* Function  Header********************************
  Function Name:       timeSlotUnlockInProgressHandler()
Parameters:          void
Return type:         void
Purpose:             To handle unlockInProgress state.
Other Note:          
 ************************************************************************************/
void timeSlotUnlockInProgressHandler()
{
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   { 
#if 0 /* CS4.0 HA Stack Changes */  
      case BSC_API_SET_LINKADMINSTATETABLE:     
         scmUnlockRespTimeSlot();           
         break;                     
#endif
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            if((( CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_TIMESLOT)
            {
               csappGrhmCfgUnlockRespTimeSlot();            
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"timeSlotLockInProgressHandler(): Invalid Object Type");  
            } 
         }  
         break;

      case BSC_API_SET_ABISTIMESLOTPERTABLE:
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
         break;
      default:
         LOG_PRINT(LOG_MAJOR,"timeSlotUnlockInProgressHandler(): Unexpected Message");  
         break; 

   }
}

/********************************* Function  Header********************************
  Function Name:       timeSlotLockInProgressHandler()
Parameters:          void
Return type:         void
Purpose:             To handle lockInProgress state.
Other Note:          
 ************************************************************************************/
void timeSlotLockInProgressHandler()
{
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
#if 0 /* CS4.0 HA Stack Changes */ 
      case BSC_API_SET_LINKADMINSTATETABLE:
         scmLockRespTimeSlot();           
         break;                          
#endif
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            if((( CsappGrhmCfgLockResp* )gCfgMsgBuf)->objType == OAMS_OBJTYPE_TIMESLOT)
            {
               csappGrhmCfgLockRespTimeSlot();            
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"timeSlotLockInProgressHandler(): Invalid Object Type");  
            } 
         } 
         break;  

      case BSC_API_SET_ABISTIMESLOTPERTABLE:
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         break;
      default:
         LOG_PRINT(LOG_MAJOR,"timeSlotLockInProgressHandler(): Unexpected Message");
         break;
   }
}


/********************************* Function  Header********************************
  Function Name:       setTimeSlot()
Parameters:          void
Return type:         void
Purpose:             To Lock/Unlock TimeSlot
Other Note:
 ************************************************************************************/
void setTimeSlot()
{ 
   I_Bool sendAckToCm = FALSE;
   AbisTimeSlotPerTableApi *e1TimeSlotObjPtr; 
   AbisTimeSlotTableApi *timeSlotFromDbObjPtr; /*To point the timeslot Object from DB.*/
   AbisTimeSlotTableIndices timeSlotTableIndicesObj;
   sCmMsg* receivedCmMsgPtr = 0;
   I_U32 oprStateAInterface = 0;
   I_U8 tsUsageType = ZERO;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   e1TimeSlotObjPtr=(AbisTimeSlotPerTableApi *)(((I_S8 *)receivedCmMsgPtr)+ sizeof(sCmMsg)); /*point to payload of received message*/
   /*read TimeSlotTable*/

   /* Change For CS2.2 : Start */
   TrunkTableApi* e1TablePtr = PNULL;
   TrunkTableIndices e1TableIndices;
   I_S32 dbStatus = -1, retVal = CFG_FAILURE;
   OamsCfgAfhSysAlarm alarmBuff;
   /* Change For CS2.2 : End */
#if 0 /* CS4.0 HA Stack Changes*/    
   LinkAdminStateTableApi linkAdminStateTableApiVar;
#endif    
   I_S32 ret;

   timeSlotTableIndicesObj.e1Num = e1TimeSlotObjPtr->e1Num;
   timeSlotTableIndicesObj.tsNum = e1TimeSlotObjPtr->tsNum;
   if (CLIB_SUCCESS != getAbisTimeSlotTable(&timeSlotTableIndicesObj,&timeSlotFromDbObjPtr))
   {
      LOG_PRINT(LOG_DEBUG,"E1TimeSlotObjHandler: readE1Table db Failed");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return ;
   }

   /* Change For CS2.2 : Start */
   e1TableIndices.e1Num = e1TimeSlotObjPtr->e1Num;
   dbStatus = getTrunkTable(&e1TableIndices, &e1TablePtr);
   if(DBLIB_SUCCESS != dbStatus)
   {
      LOG_PRINT(LOG_MAJOR,"e1Id : %d Received in Request is Not Configured at BSC",
            e1TimeSlotObjPtr->e1Num);
      cfgSendNackToCm(CM_ERR_INVALID_E1_TYPE);
      free(timeSlotFromDbObjPtr);
      return;
   }
   else 
   {
      /* Bug Fixed - Mantis#3866 : Start */
      if(((timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_LAPD_TRX) ||
               (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_TRAFFIC) ||
               (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_LAPD_BIC)
         ) &&
            (e1TablePtr->usageType != SYS_E1_USAGE_AIF)
        )
      {
         LOG_PRINT(LOG_MAJOR,"Lock/Unlock Not Allowed. ");
         cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
         free(timeSlotFromDbObjPtr);
         free(e1TablePtr);
         return;
      }
      else if((timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_ABIS_FREE) &&
            (e1TablePtr->usageType != SYS_E1_USAGE_AIF)
             )
      {
         //tsUsageType = getTimeslotUsage(e1TimeSlotObjPtr->e1Num, e1TimeSlotObjPtr->tsNum);
         if((TS_USAGE_LAPD_TRX == tsUsageType) || 
               (ZERO == tsUsageType)
           )
         {
            LOG_PRINT(LOG_MAJOR,"Lock/Unlock Not Allowed. Timeslot Not Used for LAPD_BIC");
            cfgSendNackToCm(CM_ERR_OPERATION_NOT_ALLOWED);
            free(timeSlotFromDbObjPtr);
            free(e1TablePtr);
            return;
         }
      }
      else
      {
         free(e1TablePtr);
      }
      /* Bug Fixed - Mantis#3866 : End */
   }
   /* Change For CS2.2 : End */

   switch (e1TimeSlotObjPtr->adminState)
   {
      case LOCKED: /*request type is Lock.*/
         {
            if (e1TimeSlotObjPtr->adminState == LOCKED && timeSlotFromDbObjPtr->adminState == UNLOCKED)  /*Valid Scenario..*/
            {
               /* Change For CS2.2 : Start */
               if( (timeSlotFromDbObjPtr->usageType) == SYS_TS_USAGE_LAPD_BIC || 
                     (timeSlotFromDbObjPtr->usageType) ==SYS_TS_USAGE_ABIS_FREE
                 )
               {
                  retVal = prepAndSndSwitchDisConForBic(timeSlotFromDbObjPtr->e1Num, 
                        timeSlotFromDbObjPtr->tsNum);
                  if(CFG_FAILURE == retVal)
                  {
                     LOG_PRINT(LOG_MAJOR,"Switch Connect Failed");
                     cfgSendNackToCm(CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA);
                     free(timeSlotFromDbObjPtr);
                     return;
                  }

                  /*Database Updatation is Required */
                  if(updateTimeSlotAdminState(timeSlotFromDbObjPtr->e1Num,timeSlotFromDbObjPtr->tsNum,LOCKED) != CLIB_SUCCESS)
                  {
                     LOG_PRINT(LOG_MAJOR,"Updation of AdminState in DB Failed For TimeSlot : %d & E1 : %d",
                           timeSlotFromDbObjPtr->tsNum, timeSlotFromDbObjPtr->e1Num);
                     cfgSendNackToCm(CM_ERR_UNKNOWN);
                  }
                  else
                  {
                     LOG_PRINT(LOG_INFO,"TimeSlot Updation in DB is Successfull");
                     cfgSendAckToCm();
                     gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState=locked;
                     /*Sending the Alarm...*/
                     memset(&alarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
                     alarmBuff.sysAlarm.sysalarmId = TIMESLOT_LOCKED;
                     alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TIMESLOT;
                     alarmBuff.sysAlarm.key2 = timeslotIndex;
                     alarmBuff.sysAlarm.key1 = e1Index;

                     alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;

                     alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,
                           "Timeslot %d on E1 %d is LOCKED",
                           alarmBuff.sysAlarm.key2,alarmBuff.sysAlarm.key1);

                     cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND,0);
                  }
               }
               /* Change For CS2.2 : End */
               else
               {
                  if (gBssState == lockInProgress)
                  {
                     /*As BSS LOCK in Progress...*/
                     LOG_PRINT(LOG_INFO,"As BSS is in Lock in progress, TimeSlot Lock is not Possible..");
                     /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
                     cfgSendNackToCm(CM_ERR_BSS_LOCK_IN_PROGRESS);
                     free(timeSlotFromDbObjPtr); 
                     return;
                  }
                  if (gBssState == unlockInProgress)
                  {
                     /*As BSS UNLOCK is in Progress...*/
                     LOG_PRINT(LOG_INFO,"As BSS is in unlock in progress, TimeSlot Lock is not Possible..");
                     /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
                     cfgSendNackToCm(CM_ERR_BSS_UNLOCK_IN_PROGRESS);
                     free(timeSlotFromDbObjPtr); 
                     return;
                  }

                  /*1.send CM_SUCCESS to CM.*/
                  sendAckToCm=TRUE; //cfgSendAckToCm(0);
                  if(gE1Data[timeSlotFromDbObjPtr->e1Num].e1State == locked || gBssState == locked)
                  {
                     LOG_PRINT(LOG_INFO,"As BSS is LOCKED or E1 is LOCKED, So Only Adminstate for TimeSlot %d is Updated",timeSlotFromDbObjPtr->tsNum);

                     /* CS4.0 HA Stack Changes */

/*Changes PCU R2.5 Aricent -- START*/
/* 
                     if(timeSlotFromDbObjPtr->usageType==SYS_TS_USAGE_FR)
                        psappPsscmCfgLockRespTimeSlot();
                     else
*/
                     if(timeSlotFromDbObjPtr->usageType != SYS_TS_USAGE_FR)
/*Changes PCU R2.5 Aricent -- END*/
                        sendAckToCm = FALSE;

                     if (sendAckToCm) cfgSendAckToCm(0);
                     else cfgSendNackToCm(CM_ERR_TS_USAGE_TYPE_NOT_ALLOWED);

                     free(timeSlotFromDbObjPtr);
                     return;
                  }

/*Changes PCU R2.5 Aricent -- START*/
/* 
                  if(timeSlotFromDbObjPtr->usageType==SYS_TS_USAGE_FR)
                        psappPsscmCfgLockRespTimeSlot();
                  else
*/
                     if(timeSlotFromDbObjPtr->usageType != SYS_TS_USAGE_FR)
                        sendAckToCm = FALSE;

                  if (sendAckToCm) cfgSendAckToCm(0);
                  else cfgSendNackToCm(CM_ERR_TS_USAGE_TYPE_NOT_ALLOWED);
               }

#if 0 /* CS4.0 HA Stack Changes */
               {
                  if (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2 )
                  {
                     /* Update adminState in LinkAdminStateTable as Locked */
                     linkAdminStateTableApiVar.linkAdminlinkCode   =
                        M_GET_LINKCODE(timeSlotFromDbObjPtr->usingEntity);
                     linkAdminStateTableApiVar.linkAdminlinksetID   =
                        M_GET_LINKSET(timeSlotFromDbObjPtr->usingEntity);
                     linkAdminStateTableApiVar.linkAdminadminState   = LOCKED;
                     ret = updateLinkAdminStateTable(&linkAdminStateTableApiVar);
                     if(DBLIB_SUCCESS != ret)
                     {
                        LOG_PRINT(LOG_MAJOR,"Update on LinkAdminStateTable Failed");
                        cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                        free(timeSlotFromDbObjPtr); 
                        return;
                     }
                     scmLockRespTimeSlot(); 
                  }
                  else if(timeSlotFromDbObjPtr->usageType==SYS_TS_USAGE_FR)
                     psappPsscmCfgLockRespTimeSlot();  
                  else if(timeSlotFromDbObjPtr->usageType==SYS_TS_USAGE_CIC)
                     csappGrhmCfgLockRespTimeSlot();
                  else
                     sendAckToCm = FALSE;

                  if (sendAckToCm) cfgSendAckToCm(0);
                  else cfgSendNackToCm(CM_ERR_TS_USAGE_TYPE_NOT_ALLOWED);

                  free(timeSlotFromDbObjPtr);
                  return;
               }

               /*2. check for MTPP2/FR/LAPD/CIC*/
               if (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2 )
                  sendAckToCm = sendTimeSlotMessageToSCM(LOCKED); 
               else if(timeSlotFromDbObjPtr->usageType==SYS_TS_USAGE_FR)
                  sendTimeSlotMessageToPSSCM(LOCKED); 
               else if(timeSlotFromDbObjPtr->usageType==SYS_TS_USAGE_CIC)
                  sendTimeSlotMessageToGRHM(LOCKED);
               else
                  sendAckToCm = FALSE;

               if (sendAckToCm) cfgSendAckToCm(0);
               else cfgSendNackToCm(CM_ERR_TS_USAGE_TYPE_NOT_ALLOWED);
            }
            else /*Invaild Scenario..*/
            {          
               /* it may be update request */
               if (timeSlotFromDbObjPtr->adminState == LOCKED )
               {
                  LinkAdminStateTableApi linkAdminStateTableApi;
                  LinkAdminStateTableIndices linkAdminStateTableInd;
                  TimeSlotNonPerTableApi tsNonPerTableApi;

                  if (((timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2) ||
                           (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_FR)) &&
                        (e1TimeSlotObjPtr->usageType == timeSlotFromDbObjPtr->usageType))
                  {
                     if (timeSlotFromDbObjPtr->usingEntity != e1TimeSlotObjPtr->usingEntity)
                     {
                        if(timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2)
                        {
                           /* Bug Fixed - Mantis #5206 : Start */
                           /* Delete Previous LinkCode & LinkSetId corresponding to the Timeslot */
                           linkAdminStateTableInd.linkAdminlinkCode   = 
                              M_GET_LINKCODE(timeSlotFromDbObjPtr->usingEntity);
                           linkAdminStateTableInd.linkAdminlinksetID  = 
                              M_GET_LINKSET(timeSlotFromDbObjPtr->usingEntity);
                           ret = deleteLinkAdminStateTable(&linkAdminStateTableInd);
                           if(DBLIB_SUCCESS != ret)
                           {
                              LOG_PRINT(LOG_MAJOR,"Delete on LinkAdminStateTable Failed");
                              cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                              free(timeSlotFromDbObjPtr);
                              return;
                           }
                           /* Insert New LinkCode & LinkSetId corresponding to the Timeslot */
                           linkAdminStateTableApi.linkAdminlinkCode   = 
                              M_GET_LINKCODE(e1TimeSlotObjPtr->usingEntity);
                           linkAdminStateTableApi.linkAdminlinksetID  = 
                              M_GET_LINKSET(e1TimeSlotObjPtr->usingEntity);
                           linkAdminStateTableApi.linkAdminadminState = 
                              e1TimeSlotObjPtr->adminState;
                           ret = insertLinkAdminStateTable(&linkAdminStateTableApi);
                           if(DBLIB_SUCCESS != ret)
                           {
                              LOG_PRINT(LOG_MAJOR,"Insert on LinkAdminStateTable Failed");
                              cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                              free(timeSlotFromDbObjPtr);
                              return;
                           }
                           /* Bug Fixed - Mantis #5206 : Start */
                        }

                        /* Update Data in TimeSlotPerTable */
                        ret = updateTimeSlotPerTable(e1TimeSlotObjPtr);
                        if (ret == CLIB_SUCCESS)
                        {
                           LOG_PRINT(LOG_INFO,"Update DB Successful, Sending Ack");
                           /* Update usingEntity in TimeSlotNonPerTable */
                           tsNonPerTableApi.e1Num   = timeSlotFromDbObjPtr->e1Num;
                           tsNonPerTableApi.tsNum   = timeSlotFromDbObjPtr->tsNum;
                           tsNonPerTableApi.oprState   = DISABLED;
                           tsNonPerTableApi.usageType   = timeSlotFromDbObjPtr->usageType;
                           tsNonPerTableApi.usingEntity   = e1TimeSlotObjPtr->usingEntity;
                           tsNonPerTableApi.adminState   = timeSlotFromDbObjPtr->adminState;
                           ret = updateTimeSlotNonPerTable(&tsNonPerTableApi);
                           /* Sending Ack to CM */
                           cfgSendAckToCm();
                           free(timeSlotFromDbObjPtr);
                           return;
                        }
                        else
                        {
                           LOG_PRINT(LOG_CRITICAL," Update DB Failed, Sending Nack");
                           free(timeSlotFromDbObjPtr);
                           cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                           return;
                        }
                     }

                  }
               }

               /*send CM_API_APP_RESPONSE message with status = CM_FAILURE to CM.*/
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
#endif
            }
         }  
         break;
      case UNLOCKED:  /*request type is unlock.*/
         {
            if (timeSlotFromDbObjPtr->adminState == UNLOCKED)
            {
               LOG_PRINT(LOG_INFO, "Ts=%d is already unlocked", timeSlotFromDbObjPtr->tsNum);
               cfgSendAckToCm(CM_SUCCESS);
            }
            else
            {
               /* Change For CS2.2 : Start */
               if((timeSlotFromDbObjPtr->usageType) == SYS_TS_USAGE_LAPD_BIC ||
                     (timeSlotFromDbObjPtr->usageType) == SYS_TS_USAGE_ABIS_FREE
                 )
               {
                  retVal = prepAndSndSwitchConForBic(timeSlotFromDbObjPtr->e1Num,
                        timeSlotFromDbObjPtr->tsNum);
                  if(CFG_FAILURE == retVal)
                  {
                     LOG_PRINT(LOG_MAJOR,"Switch Connect Failed");
                     cfgSendNackToCm(CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA);
                     free(timeSlotFromDbObjPtr);
                     return;
                  }
                  else
                  {
                     gE1TimeslotData[timeSlotFromDbObjPtr->e1Num][timeSlotFromDbObjPtr->tsNum].
                        e1TimeslotState = unlockInProgress;
                  }
               }
               /* Change For CS2.2 : End */
#if 0 /* CS4.0 HA Stack Changes */
               else
               {
                  if (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2)
                  {
                     /** StateTable:
TsType : E1 State     : Bss State     : A i/f State : Action
----------------------------------------------------------------------
1  mtp2   : X            : unlockInProg : X           : CFG_REJECT  
2  mtp2   : X            : lockInProg   : X           : CFG_REJECT
3  mtp2   : locked       :     X        : X           : CFG_NOSIG
4  mtp2   : X            : locked       : X           : CFG_NOSIG
5  mtp2   : unlocked     : unlocked     : X           : CFG_DOSIG
                      */

                     char reason[40];
                     CfgActionType action = CFG_REJECT;

                     if (unlockInProgress == gBssState /*1*/)
                     {
                        action = CFG_REJECT;
                        sprintf(reason, "BSS-Unlock-In-Progress");
                     }
                     else if (lockInProgress == gBssState /*2*/)
                     {
                        action = CFG_REJECT;
                        sprintf(reason, "BSS-Lock-In-Progress");
                     }
                     else if (gE1Data[timeSlotFromDbObjPtr->e1Num].e1State == locked /*3*/)
                     {
                        action = CFG_NOSIG;
                        sprintf(reason, "E1-Locked");
                     }
                     else if (locked == gBssState /*4*/)
                     {
                        action = CFG_NOSIG;
                        sprintf(reason, "BSS-Locked");
                     }
                     else if (gE1Data[timeSlotFromDbObjPtr->e1Num].e1State == unlocked &&
                           gBssState == unlocked /*5*/)
                     {
                        action = CFG_DOSIG;
                     }

                     /* Action */
                     switch(action) {
                        case CFG_REJECT:
                           LOG_PRINT(LOG_INFO, "Unlock of Ts=%d CFG_REJECTed. Reason=%s", timeSlotFromDbObjPtr->tsNum, reason);
                           cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
                           break;
                        case CFG_NOSIG:
                           LOG_PRINT(LOG_INFO, "Unlock of Ts=%d not signalled. Reason=%s", timeSlotFromDbObjPtr->tsNum, reason);
                           LOG_PRINT(LOG_INFO, "Updating AdminState=unlocked of Ts=%d", timeSlotFromDbObjPtr->tsNum);
                           /* Update adminState in LinkAdminStateTable as UnLocked */
                           linkAdminStateTableApiVar.linkAdminlinkCode    =
                              M_GET_LINKCODE(timeSlotFromDbObjPtr->usingEntity);
                           linkAdminStateTableApiVar.linkAdminlinksetID    =
                              M_GET_LINKSET(timeSlotFromDbObjPtr->usingEntity);
                           linkAdminStateTableApiVar.linkAdminadminState = UNLOCKED;
                           ret = updateLinkAdminStateTable(&linkAdminStateTableApiVar);
                           if(DBLIB_SUCCESS != ret)
                           {
                              LOG_PRINT(LOG_MAJOR,"Update on LinkAdminStateTable Failed");
                              cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
                              free(timeSlotFromDbObjPtr); 
                              return;
                           }
                           scmUnlockRespTimeSlot();
                           cfgSendAckToCm(CM_SUCCESS);
                           break;
                        case CFG_DOSIG:
                           LOG_PRINT(LOG_INFO, "Sending Unlock of Ts=%d to SCM", timeSlotFromDbObjPtr->tsNum);
                           if (sendTimeSlotMessageToSCM(UNLOCKED))
                              cfgSendAckToCm(CM_SUCCESS);
                           else
                              cfgSendNackToCm(CM_ERR_UNKNOWN);
                           break;
                        default:
                           LOG_PRINT(LOG_INFO, "Coding Error");
                           cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
                           break;
                     }
                  } /* SYS_TS_USAGE_MTP2 */

                  else if (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_CIC)
                  {
                     /** StateTable:
TsType : E1 State     : Bss State     : A i/f State : Action
----------------------------------------------------------------------
1  cic    : X            : unlockInProg : X           : CFG_REJECT  
2  cic    : X            : lockInProg   : X           : CFG_REJECT
3  cic    : locked       :     X        : X           : CFG_NOSIG
4  cic    : X            : locked       : X           : CFG_NOSIG
5  cic    : unlocked     : unlocked     : enabled     : CFG_DOSIG
6  cic    : unlocked     : unlocked     : disabled    : CFG_NOSIG
                      */

                     char reason[40];
                     CfgActionType action = CFG_REJECT;

                     getAInterfaceOprState(&oprStateAInterface);

                     if (unlockInProgress == gBssState /*1*/)
                     {
                        action = CFG_REJECT;
                        sprintf(reason, "BSS-Unlock-In-Progress");
                     }
                     else if (lockInProgress == gBssState /*2*/)
                     {
                        action = CFG_REJECT;
                        sprintf(reason, "BSS-Lock-In-Progress");
                     }
                     else if (gE1Data[timeSlotFromDbObjPtr->e1Num].e1State == locked /*3*/)
                     {
                        action = CFG_NOSIG;
                        sprintf(reason, "E1-Locked");
                     }
                     else if (locked == gBssState /*4*/)
                     {
                        action = CFG_NOSIG;
                        sprintf(reason, "BSS-Locked");
                     }
                     else if (gE1Data[timeSlotFromDbObjPtr->e1Num].e1State == unlocked &&
                           gBssState == unlocked && 
                           oprStateAInterface == ENABLED /*5*/)
                     {
                        action = CFG_DOSIG;
                     }
                     else if (gE1Data[timeSlotFromDbObjPtr->e1Num].e1State == unlocked &&
                           gBssState == unlocked && 
                           oprStateAInterface == DISABLED /*6*/)
                     {
                        action = CFG_NOSIG;
                     }

                     /* Action */
                     switch(action) {
                        case CFG_REJECT:
                           LOG_PRINT(LOG_INFO, "Unlock of Ts=%d CFG_REJECTed. Reason=%s", timeSlotFromDbObjPtr->tsNum, reason);
                           cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
                           break;
                        case CFG_NOSIG:
                           LOG_PRINT(LOG_INFO, "Unlock of Ts=%d not signalled. Reason=%s", timeSlotFromDbObjPtr->tsNum, reason);
                           LOG_PRINT(LOG_INFO, "Updating AdminState=unlocked of Ts=%d", timeSlotFromDbObjPtr->tsNum);
                           csappGrhmCfgUnlockRespTimeSlot();
                           cfgSendAckToCm(CM_SUCCESS);
                           break;
                        case CFG_DOSIG:
                           LOG_PRINT(LOG_INFO, "Sending Unlock of Ts=%d to SCM", timeSlotFromDbObjPtr->tsNum);
                           sendTimeSlotMessageToGRHM(UNLOCKED);
                           cfgSendAckToCm(CM_SUCCESS);
                           break;
                        default:
                           LOG_PRINT(LOG_INFO, "Coding Error");
                           cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
                           break;
                     }
                  } /* SYS_TS_USAGE_CIC */
               }
#endif
               else 
               { /* FR or other type of TS */
                  LOG_PRINT(LOG_INFO, "Unlock of Ts=%d, usageType=%d not supported", timeSlotFromDbObjPtr->tsNum, timeSlotFromDbObjPtr->usageType);
                  cfgSendNackToCm(CM_ERR_TS_USAGE_TYPE_NOT_ALLOWED);
               }
            }
         }
         break;   
      default:
         break;     
   }/*ends switch*/
   /*free the db pointer..*/
   free(timeSlotFromDbObjPtr);
}/*end setTimeSlot.*/

#if 0 /* CS4.0 HA Stack Changes */
/********************************* Function  Header********************************
  Function Name:       sendTimeSlotMessageToGRHM()
Parameters:          I_U16
Return type:         void
Purpose:             To send a lock/unlock request to GRHM for CIC.
Other Note:
 ************************************************************************************/
void sendTimeSlotMessageToGRHM(I_U16 reqType)
{
   AbisTimeSlotPerTableApi *e1TimeSlotObjPtr; 
   sCmMsg* receivedCmMsgPtr = 0;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   e1TimeSlotObjPtr=(AbisTimeSlotPerTableApi *)(((I_S8 *)receivedCmMsgPtr)+ sizeof(sCmMsg)); /*point to payload of received message*/
   I_U8 rval=0;
   switch (reqType)
   {
      case LOCKED:
         {
            /*Lock*/
            OamsCfgGrhmLockReq reqMsg;
            /************* fix for mantis-1797 ***********************/
            memset(&reqMsg,0,sizeof(OamsCfgGrhmLockReq));
            /**********************************************************/
            /* Fill in oamsCfgScmUnlockReq message to be sent to PSSCM*/
            reqMsg.objectId = 0;
            reqMsg.objectId = maskBits(reqMsg.objectId,e1TimeSlotObjPtr->tsNum,lBYtes);/*Mask TimeSlot Number with ObjectId*/
            reqMsg.objectId= maskBits(reqMsg.objectId,e1TimeSlotObjPtr->e1Num,hBytes);/*Mask E1 Number with Object Id*/
            reqMsg.objType = OAMS_OBJTYPE_TIMESLOT; 
            reqMsg.reason = OAMS_RSN_OPERATORINITIATED;
            rval = cfgSendMessage(&reqMsg,sizeof(OamsCfgGrhmLockReq),ENT_CSAPP_GRHM,OAMS_CFG_GRHM_LOCK_REQ,0);
            if (rval == CFG_FAILURE)
            {
               LOG_PRINT(LOG_CRITICAL, "E1TimeSlotObjHandler:setTimeSlotGrhmLock,OAMS_CFG_SYS_ALARM send Failed");
            }
            if (rval == CFG_SUCCESS)
            {
               LOG_PRINT(LOG_INFO, "E1TimeSlotObjHandler:setTimeSlotGrhmLock,send SUCCESS");
               gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState = lockInProgress;
            }
         }
         break;

      case UNLOCKED:
         {
            /*Unlock*/
            OamsCfgGrhmUnlockReq reqMsg;
            /* Fill in oamsCfgScmUnlockReq message to be sent to PSSCM*/
            reqMsg.objectId = 0;
            reqMsg.objectId = maskBits(reqMsg.objectId,e1TimeSlotObjPtr->tsNum,lBYtes);/*Mask TimeSlot Number with ObjectId*/
            reqMsg.objectId = maskBits(reqMsg.objectId,e1TimeSlotObjPtr->e1Num,hBytes);/*Mask E1 Number with Object Id*/
            reqMsg.objType = OAMS_OBJTYPE_TIMESLOT; 
            reqMsg.reason = OAMS_RSN_OPERATORINITIATED;
            rval = cfgSendMessage(&reqMsg,sizeof(OamsCfgGrhmUnlockReq),ENT_CSAPP_GRHM,OAMS_CFG_GRHM_UNLOCK_REQ,0);
            if (rval == CFG_FAILURE)
            {
               LOG_PRINT(LOG_CRITICAL,"E1TimeSlotObjHandler:setTimeSlotGrhmUnlock,send Failed");
            }
            if (rval == CFG_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"E1TimeSlotObjHandler:setTimeSlotGrhmUnlock,send SUCCESS");
               gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState=unlockInProgress;
            }
         }
         break;
      default:
         break;
   }   
}

/********************************* Function  Header********************************
  Function Name:       sendTimeSlotMessageToSCM(I_U16 reqType)
Parameters:          I_U16
Return type:         void
Purpose:             To send a lock/unlock request to Scm for MTP2 / LAPD
Other Note:
 ************************************************************************************/
I_Bool sendTimeSlotMessageToSCM(I_U16 reqType)
{
   I_Bool result = FALSE;
   AbisTimeSlotPerTableApi *e1TimeSlotObjPtr;  
   AbisTimeSlotTableApi *timeSlotFromDbObjPtr; /*To point the timeslot Object from DB.*/
   AbisTimeSlotTableIndices timeSlotTableIndicesObj;
   sCmMsg* receivedCmMsgPtr = 0;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   e1TimeSlotObjPtr = (AbisTimeSlotPerTableApi *)(((I_S8 *)receivedCmMsgPtr)+ sizeof(sCmMsg)); /*point to payload of received message*/
   /*read TimeSlotTable*/
   timeSlotTableIndicesObj.e1Num = e1TimeSlotObjPtr->e1Num;
   timeSlotTableIndicesObj.tsNum = e1TimeSlotObjPtr->tsNum;
   if (CLIB_SUCCESS != getAbisTimeSlotTable(&timeSlotTableIndicesObj,&timeSlotFromDbObjPtr))
   {
      LOG_PRINT(LOG_CRITICAL,"E1TimeSlotObjHandler: readE1Table db Failed");
      return result;
   }
   switch (reqType)
   {
      case LOCKED:
         {
            /*Lock*/
            if (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2)
            {
               result = e1TimeSlotSendLinkAdminTableToScm(e1TimeSlotObjPtr,reqType);
               if (TRUE == result) {      
                  gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState = lockInProgress;
               }
            }

         }
         break;

      case UNLOCKED:
         {
            /*Unlock*/   
            if (timeSlotFromDbObjPtr->usageType == SYS_TS_USAGE_MTP2)
            {
               result = e1TimeSlotSendLinkAdminTableToScm(e1TimeSlotObjPtr,reqType); 
               if (TRUE == result) {      
                  gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState = unlockInProgress;
               }
            }
         }
         break;   

      default:
         break;
   }
   return result;
}
#endif

/********************************* Function  Header********************************
  Function Name:       scmUnlockRespTimeSlot()
Parameters:          void
Return type:         void
Purpose:             To handle the Time slot Unlock response from SCM .
Other Note:
 ************************************************************************************/
void scmUnlockRespTimeSlot()
{
   OamsCfgAfhSysAlarm alarmBuff={0};
   /*Database Updatation is Required (changing in AST of TimeSlot Table)..   */
   if(updateTimeSlotAdminState(e1Index,timeslotIndex,UNLOCKED)==CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"E1TimeSlotObjHandler:scmUnlockRespTimeSlot,DB Updation is Done..");
   }

   gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState=unlocked;
   /*Sending the Alarm...*/
   alarmBuff.sysAlarm.sysalarmId = TIMESLOT_UNLOCKED;
   alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TIMESLOT;
   alarmBuff.sysAlarm.key2 = timeslotIndex;   
   alarmBuff.sysAlarm.key1 = e1Index;   

   /* Mantis Id 2242 Start */
   //         alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   /* Mantis Id 2242 End */
   //Changes made during OMC Integration
   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;

   alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d on E1 %d is UNLOCKED",alarmBuff.sysAlarm.key2,alarmBuff.sysAlarm.key1);

   cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND,0); 
}/*end scmUnlockRespTimeSlot*/


/********************************* Function  Header********************************
  Function Name:       csappGrhmCfgUnlockRespTimeSlot()
Parameters:          void
Return type:         void
Purpose:             To handle the CSAPP_GRHM_CFG_UNLOCK_RESP message.
Other Note:
 ************************************************************************************/
void csappGrhmCfgUnlockRespTimeSlot()
{
   AbisTimeSlotTableIndices timeSlotTableIndicesObj;
   OamsCfgAfhSysAlarm alarmBuff={0};  
   I_U16 e1Num=0;
   I_U16 tsNum=0;
   AbisTimeSlotPerTableApi *e1TimeSlotObjPtr = NULL;
   sCmMsg *receivedCmMsgPtr = NULL;
   LOG_PRINT(LOG_INFO," Got UNLOCK_COMPLETE Message FROM GRHM.. ");   
   if((((SysHdr*) gCfgMsgBuf)->msgType) == BSC_API_SET_ABISTIMESLOTPERTABLE)
   {
      receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
      e1TimeSlotObjPtr = (AbisTimeSlotPerTableApi *)((I_S8 *)receivedCmMsgPtr + sizeof(sCmMsg));
      e1Num = e1TimeSlotObjPtr->e1Num;
      tsNum = e1TimeSlotObjPtr->tsNum;
   }
   else
      unMaskBits(((CsappGrhmCfgUnlockResp* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);

   /*Sending the Alarm...*/
   alarmBuff.sysAlarm.sysalarmId = TIMESLOT_UNLOCKED;
   alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TIMESLOT;
   alarmBuff.sysAlarm.key2 = tsNum;
   alarmBuff.sysAlarm.key1 = e1Num;
   /* Mantis Id 2242 Start */
   //   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   /* Mantis Id 2242 End */
   //Changes made during OMC Integration
   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
   alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d on E1 %d is UNLOCKED",alarmBuff.sysAlarm.key2,alarmBuff.sysAlarm.key1);
   gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState=unlocked;
   /*Database Updatation is Required (changing in AST of TimeSlot Table)..*/
   timeSlotTableIndicesObj.e1Num=e1Num;
   timeSlotTableIndicesObj.tsNum=tsNum;
   if(updateTimeSlotAdminState(timeSlotTableIndicesObj.e1Num,timeSlotTableIndicesObj.tsNum,UNLOCKED)==CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"E1TimeSlotObjHandler:csappGrhmUnlockRespTimeSlot,DB Updation is Done..");
   }
   LOG_PRINT(LOG_INFO,"csppGrhmCfgUnlockRespTimeSlot: Sending Alarm : ");
   cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
}/* end csappGrhmCfgUnlockRespTimeSlo*/


/********************************* Function  Header********************************
  Function Name:       scmLockRespTimeSlot()
Parameters:          void
Return type:         void
Purpose:             To handle the Time Slot Lock RESP from SCM.
Other Note:
 ************************************************************************************/
void scmLockRespTimeSlot()
{
   OamsCfgAfhSysAlarm alarmBuff={0};

   /*Database Updatation is Required (changing in AST of TimeSlot Table)..   */
   if(updateTimeSlotAdminState(e1Index,timeslotIndex,LOCKED)==CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"E1TimeSlotObjHandler:scmUnlockRespTimeSlot,DB Updation is Done..");
   }

   gE1TimeslotData[e1Index][timeslotIndex].e1TimeslotState=locked;

   /*Sending the Alarm...*/
   alarmBuff.sysAlarm.sysalarmId = TIMESLOT_LOCKED;
   alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TIMESLOT;
   alarmBuff.sysAlarm.key2 = timeslotIndex;
   alarmBuff.sysAlarm.key1 = e1Index;
   /* Mantis Id 2242 Start */
   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   /* Mantis Id 2242 End */
   alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d on E1 %d is LOCKED",alarmBuff.sysAlarm.key2,alarmBuff.sysAlarm.key1);

   LOG_PRINT(LOG_INFO,"scmLockRespTimeSlot: Sending Alarm : ");
   cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
}/*end scmLockRespTimeSlot*/


/********************************* Function  Header********************************
  Function Name:       csappGrhmCfgLockRespTimeSlot()
Parameters:          void
Return type:         void
Purpose:             To handle the CSAPP_GRHM_CFG_LOCK_RESP message.
Other Note:
 ************************************************************************************/
void csappGrhmCfgLockRespTimeSlot()
{
   OamsCfgAfhSysAlarm alarmBuff={0}; 
   AbisTimeSlotTableIndices timeSlotTableIndicesObj;
   AbisTimeSlotPerTableApi *e1TimeSlotObjPtr = NULL;
   sCmMsg *receivedCmMsgPtr = NULL;
   I_U16 e1Num=0;
   I_U16 tsNum=0;
   LOG_PRINT(LOG_INFO,"Got LOCK_COMPLTE Message from GRHM...");
   if((((SysHdr*) gCfgMsgBuf)->msgType) == BSC_API_SET_ABISTIMESLOTPERTABLE)
   {
      receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
      e1TimeSlotObjPtr = (AbisTimeSlotPerTableApi *)((I_S8 *)receivedCmMsgPtr + sizeof(sCmMsg));
      e1Num = e1TimeSlotObjPtr->e1Num;
      tsNum = e1TimeSlotObjPtr->tsNum;
   }
   else 
      unMaskBits(((CsappGrhmCfgLockResp* )gCfgMsgBuf)->objectId,&tsNum,&e1Num);
   LOG_PRINT(LOG_DEBUG,"e1 = %d , ts = %d",e1Num,tsNum); 
   /*Sending the Alarm...*/
   alarmBuff.sysAlarm.sysalarmId = TIMESLOT_LOCKED;
   alarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_TIMESLOT;
   alarmBuff.sysAlarm.key2 = tsNum;
   alarmBuff.sysAlarm.key1 = e1Num;
   /* Mantis Id 2242 Start */
   alarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   /* Mantis Id 2242 End */ 
   alarmBuff.sysAlarm.infoStrLen = sprintf(alarmBuff.sysAlarm.infoString,"Timeslot %d on E1 %d is LOCKED",alarmBuff.sysAlarm.key2,alarmBuff.sysAlarm.key1);
   gE1TimeslotData[e1Num][tsNum].e1TimeslotState=locked;
   /*Database Updatation is Required (changing in AST of TimeSlot Table)..*/
   timeSlotTableIndicesObj.e1Num=e1Num;
   timeSlotTableIndicesObj.tsNum=tsNum;
   if(updateTimeSlotAdminState(timeSlotTableIndicesObj.e1Num,timeSlotTableIndicesObj.tsNum,LOCKED)==CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"E1TimeSlotObjHandler:csappGrhmLockRespTimeSlot,DB Updation is Done..");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"E1TimeSlotObjHandler:csappGrhmLockRespTimeSlot,DB Updation Failed");
   }
   LOG_PRINT(LOG_INFO,"csppGrhmCfgLockRespTimeSlot: Sending Alarm : ");
   cfgSendMessage(&alarmBuff, sizeof(alarmBuff), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0); 
}/*end csappGrhmCfgLockRespTimeSlot*/


/*-----------------------------------------------------------------------------------*/

I_U32 maskBits(I_U32 var,I_U32 value,int bitCount)
{
   /*---------------------------------*/
   /*var - ObjectId.*/
   /*value - E1 Number /TimeSlot Number*/
   /*---------------------------------*/
   while(value>0)
   {
      if (value%2 != 0)
         SET_BIT(var,bitCount);
      value = value/2;
      bitCount++;    
   }
   return var;
}

void unMaskBits(I_U32  n ,I_U16 * tsNum, I_U16 *e1Num)
{
   LOG_PRINT(LOG_INFO,"unMaskBits : Function Entring");
   I_U16 i;
   for (i = 0; i < 16; i++)
   {
      if (n & 0x1u) 
         SET_BIT(*tsNum,i);
      n >>= 1 ;      
   }
   for (i = 0; i < 16; i++)
   {
      if(n & 0x1u) 
         SET_BIT(*e1Num,i);
      n >>= 1 ;      
   }
   LOG_PRINT(LOG_INFO,"unMaskBits : Function Exiting");
}

#if 0 /* CS4.0 HA Stack Changes */
I_Bool e1TimeSlotSendLinkAdminTableToScm(AbisTimeSlotPerTableApi *e1TimeSlotObjPtr, I_U32 admStateReqst)
{
   I_Bool result = FALSE;
   LinkAdminStateTableIndices linkAdminStateTableIndicesBuff={0};
   LinkAdminStateTableApi*   linkAdminStateTableApiPtr=NULL;

   linkAdminStateTableIndicesBuff.linkAdminlinksetID= 
      M_GET_LINKSET(e1TimeSlotObjPtr->usingEntity);
   linkAdminStateTableIndicesBuff.linkAdminlinkCode =
      M_GET_LINKCODE(e1TimeSlotObjPtr->usingEntity);


   if ( getLinkAdminStateTable(&linkAdminStateTableIndicesBuff,
            &linkAdminStateTableApiPtr) == CLIB_SUCCESS )
   {
      linkAdminStateTableApiPtr->linkAdminadminState = admStateReqst;
      if ( updateLinkAdminStateTable(linkAdminStateTableApiPtr) == CLIB_SUCCESS)
      {
         result = TRUE;
         gMsgSentForE1TSNum = e1TimeSlotObjPtr->tsNum;
         gMsgSentForE1TSNum = ((e1TimeSlotObjPtr->e1Num << 16)| gMsgSentForE1TSNum);
         sendLinkAdminStateTableReqToScm(linkAdminStateTableApiPtr);
      }
      else
      {
         LOG_PRINT(LOG_CRITICAL,"updateLinkAdminStateTable() DB Failure... ");
      }
      free(linkAdminStateTableApiPtr);
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL,"getLinkAdminStateTable() DB Failure... ");
   }

   return result;
}
#endif
/********************************* Change History ***************************
  Release     Patch       Author         Description
  CS2                     Pratibha       Enum Removal Change

 ************************************** End *********************************/
