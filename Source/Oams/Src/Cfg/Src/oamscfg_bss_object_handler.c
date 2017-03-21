/*************************************************************** File Header ***
  File Name      : oamcfg_bss_object_handler.c
Purpose        : This file contains fucntion defintions required for handling
BSS Object.
Project        : BSC
Subsystem      : OAMS 
Author         : Aricent Bangalore
CSCI id        :
Version        :
 ********************************************************************** End ***/

#include <oamscfg_includes.h>
void bssObjectHandler()
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectHandler()");
   switch ( gBssState )
   {
      case locked:
         bssObjectLockedHandler();
         break;
      case lockInProgress:   
         bssObjectLockInProgressHandler();
         break;
      case unlocked:
         bssObjectUnockHandler();
         break;
      case unlockInProgress:   
         bssObjectUnLockInProgressHandler();
         break;
      default:
         LOG_PRINT(LOG_MAJOR,"Invalid BSS state");
         break;
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectHandler()");

}/* bssObjectHandler */

/*BSC R2.0 changes Starts*/
/********************************* Function  Header*****************************
Function Name   : initiateDspLockforBssLock()
Parameters      : none 
Return type     : none
Purpose         : sends Dsp Lock for all present Dsps at the time of BSS lock
Other Note      : 
 *******************************************************************************/

I_Void initiateDspLockforBssLock()
{
   DspStatusTableApi *dspStsTbl;
   DspStatusTableApi *dspTmpPtr;
   I_U32 outRows=0,i;
   I_U16 outSize=0;
   if(getallDspStatusTable(&dspStsTbl,&outRows,&outSize) == CLIB_SUCCESS)
   {
      for(i=0;i< outRows;i++)
      {
         dspTmpPtr = (DspStatusTableApi *)(((I_U8 *)dspStsTbl) + i * outSize);
         if(dspTmpPtr->physicalPresenceState == PRESENT )
         {
             sendDspLockReqToDsph(dspTmpPtr->chasisFrameId, dspTmpPtr->slotId,
                  dspTmpPtr->dspId,OAMS_RSN_PARENTOBJECTLOCKED); 
         } 
      } 
   }
}

/********************************* Function  Header*****************************
Function Name   : initiateDspUnlockforBssUnlock()
Parameters      : none 
Return type     : none
Purpose         : sends Dsp Unlock for all present Dsps at the time of BSS unlock
Other Note      : 
 *******************************************************************************/

I_Void initiateDspUnlockforBssUnlock()
{
   DspStatusTableApi *dspStsTbl;
   DspStatusTableApi *dspTmpPtr;
   I_U32 outRows=0,i;
   I_U16 outSize=0;
   LOG_PRINT(DEBUG,"Entering in func initiateDspUnlockforBssUnlock");
   if(getallDspStatusTable(&dspStsTbl,&outRows,&outSize) == CLIB_SUCCESS)
   {
      for(i=0;i< outRows;i++)
      {
         dspTmpPtr = (DspStatusTableApi *)(((I_U8 *)dspStsTbl) + i * outSize);
         if(dspTmpPtr->physicalPresenceState == PRESENT )
         {
             sendDspUnlockReqToDsph(dspTmpPtr->chasisFrameId, dspTmpPtr->slotId,
                  dspTmpPtr->dspId,OAMS_RSN_PARENTOBJECTUNLOCKED); 
         } 
      } 
   }
}//initiateDspUnlockforBssUnlock

/*BSC R2.0 changes Ends*/
void bssObjectLockedHandler()
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectLockedHandler()");
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case BSC_API_SET_BSSTABLE:
         bssObjectBssSetTableHandler();
         break;
      case CSAPP_GRHM_CFG_ALARM_IND:
         {
            /* No LOCK_COMPLETE Alarm after changes for Mantis#2284 */      
         }
         break;
      default:
         LOG_PRINT(LOG_MAJOR," State : locked , Message received %u , ignored ",(((SysHdr*) gCfgMsgBuf)->msgType));
         break;
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectLockedHandler()");
} /* bssObjectLockedHandler */

void bssObjectLockInProgressHandler()
{
   I_S32 ret = CM_FAILURE;

   LOG_PRINT(LOG_INFO,"ENTERING bssObjectLockInProgressHandler()");
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case BSC_API_SET_BSSTABLE:
         LOG_PRINT(LOG_MAJOR,"Bss Lock is in Progress...");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         break;   
/*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSSCM_CFG_LOCK_RESP:
         LOG_PRINT(LOG_INFO,"Received message OAMS_PSSCM_CFG_LOCK_RESP");
         bssObjectSendLinkAdminStateTableToScm(UNLOCKED, LOCKED);
         break;
/*Changes PCU R2.5 Aricent -- END*/

#if 0 /* CS4.0 HA Stack Changes */ 
      case BSC_API_SET_LINKADMINSTATETABLE:     
         LOG_PRINT(LOG_INFO,"BSC_API_SET_LINKADMINSTATETABLE  has been received.."); 
         bssObjectHandlerForSSProhibit();
         break;
#endif
      case CSAPP_GRHM_CFG_LOCK_RESP:
         {
            /*Changes for Mantis 2284 - Start*/ 
            OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff={0};
            
            /*Changes PCU R2.5 Aricent -- START*/ 
            OamsCfgPdcBssLockInd oamsCfgPdcBssLockIndBuff;
            /*Changes PCU R2.5 Aricent -- END*/
            
            LOG_PRINT(LOG_INFO,"Received message CSAPP_GRHM_CFG_LOCK_RESP");
            memset(&OamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
            /* Update DB state to LOCKED */
            gDbBssTableApiStorage.adminState = LOCKED;
            getDbBssTable();
            ret = updateBssAdminState(gDbBssTableApiStorage.bscId,LOCKED);
            if(CLIB_SUCCESS == ret)
            {

               LOG_PRINT(LOG_INFO,"BSS Admin state has been updated to LOCKED.."); 
               /* Send Alarm */
               OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = BSS_LOCKED;
               OamsCfgAfhSysAlarmBuff.sysAlarm.info3=OAMS_OBJTYPE_BSS;
               OamsCfgAfhSysAlarmBuff.sysAlarm.key1=gDbBssTableApiStorage.bscId;
               /* Mantis Id 2242 Start */
               OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
               /* Mantis Id 2242 End */
               OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
                  sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"BSS [%u] is LOCKED",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"Sending Alarm BSS_LOCKED to AFH"); 
               cfgSendMessage((void *)&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

               /*Changes PCU R2.5 Aricent -- START*/      
               /* send OAMS_CFG_PDC_BSS_LOCK_IND to PDC */
               LOG_PRINT(LOG_INFO,"Sending message OAMS_CFG_PDC_BSS_LOCK_IND to PDC"); 
               cfgSendMessage((void *)&oamsCfgPdcBssLockIndBuff, sizeof(OamsCfgPdcBssLockInd), ENT_OAM_PDC, OAMS_CFG_PDC_BSS_LOCK_IND, 0);
               /*Changes PCU R2.5 Aricent -- END*/

               gBssState = locked;  
               gBssSubState = noneBssSubState;  
            }   
            #if 0 //Changes PCU R2.5 Aricent
            /* Send CELL_BARR_ACESS to the CELLH */
            sendCellBarAccessToCells(LockProcedure,OAMS_RSN_AINTERFACEDOWN);
            #endif  
            else
            {  
               LOG_PRINT(LOG_CRITICAL, "Db call updateBssAdminState failed returned Error Code = [%d]", ret);
            }
         }
         break;
      default :
         LOG_PRINT(LOG_MAJOR," State : LockInProgress , Message received %u , ignored ",(((SysHdr*) gCfgMsgBuf)->msgType));
         break;         
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectLockInProgressHandler()");
} /* bssObjectLockInProgressHandler*/

void bssObjectUnockHandler()
{
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case BSC_API_SET_BSSTABLE:
         LOG_PRINT(LOG_INFO,"Received message BSC_API_SET_BSSTABLE");
         bssObjectBssSetTableHandler();
         break;   
/*Changes PCU R2.5 Aricent -- START*/
      /* if  OAMS_PSSCM_CFG_UNLOCK_RESP message is received as response
       * of Gb-Interface Unlock, this message should be handled in 
       * UnLockInProgress state, so calling bssObjectUnLockInProgressHandler()
       */
      case OAMS_PSSCM_CFG_UNLOCK_RESP:
         LOG_PRINT(LOG_INFO,"Received message OAMS_PSSCM_CFG_UNLOCK_RESP");
/*Changes PCU R2.5 Aricent -- END*/
         bssObjectUnLockInProgressHandler();
         break;   
      default :
         LOG_PRINT(LOG_MAJOR," State : unlocked , Message received %u , ignored ",(((SysHdr*) gCfgMsgBuf)->msgType));
         break;         
   }
} /* bssObjectUnockHandler */

void bssObjectUnLockInProgressHandler()
{
/*Changes PCU R2.5 Aricent -- START*/
   GbInterfaceTableApi *gbInterfaceTablePtr = NULL;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_S32 ret = CM_FAILURE;
/*Changes PCU R2.5 Aricent -- END*/
   
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectUnLockInProgressHandler()");
   switch ((((SysHdr*) gCfgMsgBuf)->msgType))
   {
      case BSC_API_SET_BSSTABLE:
         LOG_PRINT(LOG_INFO,"Received message BSC_API_SET_BSSTABLE");
         bssObjectBssSetTableHandler();
         break;

#if 0 /* CS4.0 HA Stack Changes */
      case BSC_API_SET_LINKADMINSTATETABLE:     
         LOG_PRINT(LOG_INFO,"BSC_API_SET_LINKADMINSTATETABLE:  has been received.."); 
         /* Just consume it */
         break;
#endif

/*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSSCM_CFG_UNLOCK_RESP:   
         {
            LOG_PRINT(LOG_INFO,"Received message OAMS_PSSCM_CFG_UNLOCK_RESP");
            ret = getallGbInterfaceTable(&gbInterfaceTablePtr, &outCountGb, &outSizeGb);
            if (CLIB_SUCCESS == ret)
            {
               if ( FR == gbInterfaceTablePtr->transportType ) /* Case transport type is FR */ 
               {
                  LOG_PRINT(LOG_INFO, "getallGbInterfaceTable Passed transportType FR: Calling initiateNsvcUnlockEnableForUnlockedDisabledNsvcs");
                  /* CFG will execute Unlock (Enabled) Nsvc procedure 
                  for all the Unlocked and Disabled Nsvcs */
                  initiateNsvcUnlockEnableForUnlockedDisabledNsvcs();
               }
               else /* Case transport type is IP */
               {
                  LOG_PRINT(LOG_INFO, "getallGbInterfaceTable Passed transportType IP: Calling informNsvcUnlockEnableForUnlockDisabledNsvcsToBss");
                  /* CFG will inform BssObjectHandler to proceed further */
                  informNsvcUnlockEnableForUnlockDisabledNsvcsToBss();
               }
            }
            else
            {
               LOG_PRINT(LOG_CRITICAL, "Db call getallGbInterfaceTable failed returned Error Code = [%d]", ret);
            }
             if(I_TRUE == gCfgStandbyToActive) 
             {/*changes for mantis #16235 starts */ 
                 generateResetAfterSwitchOver();  
                 if ((CLIB_SUCCESS != ret)|| ((gCellEnableSent == 0) && (FR != gbInterfaceTablePtr->transportType)))
                 { 
                     /* for standby card BSS unlock is over here*/
                     informCellUnLockEnableforUnlockDisabledCellsToBss();
                 }
                      
                 //sendCellEnableToCbsh();/*changes for mantis #16678 */
                 
             }
             else
             {
               /* CFG will execute Unlock (Enabled) Cell procedure 
                  for all the Unlocked and Disabled cells */
               if(ret!=CLIB_SUCCESS)
               initiateCellUnlockEnableforUnlcokedDisabledCells();
             } 
            
               if(ret==CLIB_SUCCESS)
               free(gbInterfaceTablePtr);
             /*changes for mantis #16235 Ends*/ 
         }
         break;
      case CSAPP_GRHM_CFG_UNLOCK_RESP:
         {
            LOG_PRINT(LOG_INFO,"Received message CSAPP_GRHM_CFG_UNLOCK_RESP");

            setAinterfaceTableOperationalState(ENABLED);
/*Changes PCU R2.5 Aricent -- END*/
            sendCellBarAccessToCells(UnlockProcedure,OAMS_RSN_AINTERFACEUP);
            /*Changes for Mantis 9617 Starts*/
            #if 0 
            if (gDbBssTableApiStorage.gprsEnabled )
            {
               LOG_PRINT(LOG_INFO,"UNLOCK GB interface towards GB interface"); 
               /* UNLOCK GB interface towards GB interface */
               sendPsscmUnlockReq(OAMS_RSN_PARENTOBJECTLOCKED);
            }
            else
            {
               LOG_PRINT(LOG_INFO,"GPRS is disabled. Calling initiateCellUnlockEnableforUnlcokedDisabledCells");
               /* CFG will execute Unlock (Enabled) Cell procedure 
                  for all the Unlocked and Disabled cells */
               initiateCellUnlockEnableforUnlcokedDisabledCells();
            }
            #endif  
            /*Changes for Mantis 9617 Ends*/
         }
         break;
      default :
         LOG_PRINT(LOG_INFO," bssObjectUnLockInProgressHandler: Received Unexpected Message, MessageType %u ",(((SysHdr*) gCfgMsgBuf)->msgType));

         break;         
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectUnLockInProgressHandler()");
}/* bssObjectUnLockInProgressHandler */

void bssObjectBssSetTableHandler()
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectBssSetTableHandler()");
   I_S32 retValue = CM_FAILURE;
   sCmMsg* receivedCmMsgPtr = 0;
   receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
   BssTableApi * bssTableApiRcvdPtr;
   BssTableApi * bssTableApiDbPtr;
   BssTableIndices BssTableIndicesBuff;
   bssTableApiRcvdPtr = (BssTableApi *)( ((I_U8 *)receivedCmMsgPtr)+sizeof(sCmMsg));
   /* Read the DB and get the database table for the BSS */

   /* retValue = getallBssTable(&bssTableApiDbPtr,&outPutCount,&outSize); */
   BssTableIndicesBuff.bscId = bssTableApiRcvdPtr->bscId;
   retValue = getBssTable(&BssTableIndicesBuff,&bssTableApiDbPtr);
   LOG_PRINT(LOG_DEBUG,"retValue=%d",retValue);
   if ( retValue == CLIB_SUCCESS )
   {
      gDbBssTableApiStorage = *bssTableApiDbPtr;
      bssObjectPerformOperationOnBssTable(bssTableApiRcvdPtr, bssTableApiDbPtr);
      free(bssTableApiDbPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Db call getBssTable failed returned Error Code = [%d] ", retValue);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectBssSetTableHandler()");
} /* bssObjectBssSetTableHandler */

void  bssObjectPerformOperationOnBssTable(BssTableApi* bssTableApiRcvdPtr, BssTableApi* bssTableApiDbPtr)
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectPerformOperationOnBssTable");

   /* Fixed Mantis#2768 : Start */
   /* Code Change to handle Lock in UnlockInProgress State and 
    * rejecting Unlock req when state is UnlockInProgress
    */
   if ((bssTableApiRcvdPtr->adminState == LOCKED ) &&
         ( gBssState == unlockInProgress ))
   {
      bssObjectPerformLockOperation(bssTableApiRcvdPtr);   
   }
   else if
      ((bssTableApiRcvdPtr->adminState == UNLOCKED ) &&
       ( gBssState == unlockInProgress ))
      {
         LOG_PRINT(LOG_MAJOR,"Unlock Request Already in Progress. Sending Nack to CM");
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
      }
   /* Fixed Mantis#2768 : End */

   else if ((bssTableApiRcvdPtr->adminState == LOCKED ) &&
         ( bssTableApiDbPtr->adminState == LOCKED ))
   {
      if ( memcmp((void *)bssTableApiRcvdPtr,(void *)bssTableApiDbPtr,sizeof(BssTableApi)))
      {
         /* Update operation. */
         bssObjectPerformUpdateOperation(bssTableApiRcvdPtr);
      }
      else
      {
         LOG_PRINT(LOG_INFO," Received parameters and DB parameters are same");
         cfgSendAckToCm(); /* No need to send Nack. Send Ack no update required. */
      }
   }
   else
      if ((bssTableApiRcvdPtr->adminState == UNLOCKED ) && ( bssTableApiDbPtr->adminState == LOCKED ))
      {
         if ( memcmp((void *)bssTableApiRcvdPtr,(void *)bssTableApiDbPtr,sizeof(BssTableApi)))
         {
            /*  UNLOCK opeartoin*/
        #if 0 
        Not required now
				/*Changes done for not sending UNLOCK req if the Oper State is ENABLED 15-06-2015 GAURAV SINHA for BSS UNLOCK ISSUE*/
							LinkStatusTableApi *linkStatusTableApi = NULL;
							LinkStatusTableApi *tempLinkStatusTableApi = NULL;
							I_U32 outRows = ZERO;
							I_U16 outSize = ZERO;
							I_U32 cntVar = ZERO;
						  if(CLIB_SUCCESS == getallLinkStatusTable(&linkStatusTableApi,&outRows,&outSize))
							{
								for(cntVar=ZERO;cntVar<outRows;cntVar++)
								{
         					tempLinkStatusTableApi = (LinkStatusTableApi *)((I_U8 *)linkStatusTableApi + (outRows * outSize));
									if(linkStatusTableApi->oprState == ENABLED)
									{
										LOG_PRINT(LOG_DEBUG, "Link Operational Status is Still ENABLED: BSS_UNLOCK_REQ not permisibble");
										cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
										if(linkStatusTableApi)
										{
											free(linkStatusTableApi);
										}
										return;
									}
								}
							}
				/*Changes done for not sending UNLOCK req if the Oper State is ENABLED 15-06-2015 GAURAV SINHA for BSS UNLOCK ISSUE*/
        #endif
            bssObjectPerformUnlockOperation(bssTableApiRcvdPtr);         
         }
         else
         {
            LOG_PRINT(LOG_INFO,"Invalid request");
            cfgSendNackToCm(CM_ERR_UNKNOWN);
         }
      }
      else if ((bssTableApiRcvdPtr->adminState == LOCKED ) && ( bssTableApiDbPtr->adminState == UNLOCKED ))
      {
         if ( memcmp((void *)bssTableApiRcvdPtr,(void *)bssTableApiDbPtr,sizeof(BssTableApi)))
         {
            /* LOCK opeartoin */
            bssObjectPerformLockOperation(bssTableApiRcvdPtr);         
         }
         else
         {
            LOG_PRINT(LOG_INFO,"BSS is Unlocked, Invalid request, sending Nack");
            cfgSendNackToCm(CM_ERR_UNKNOWN);
         }      
      }   

   LOG_PRINT(LOG_INFO,"EXITING bssObjectPerformOperationOnBssTable");
   return ;
} /* bssObjectPerformOperationOnBssTable */

void   bssObjectPerformUpdateOperation(BssTableApi* bssTableApiRcvdPtr)
{
/*Changes PCU R2.5 Aricent -- START*/
   BssPsPreConfigTableApi* psPreConfigTablePtr = NULL;
   I_S32 ret = CM_FAILURE;
   I_U32 rowsCount = 0;
   I_U16 outSize = 0;
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectPerformUpdateOperation");
  
   if (TRUE == bssTableApiRcvdPtr->gprsEnabled)
   {
      ret = getallBssPsPreConfigTable(&psPreConfigTablePtr, &rowsCount, &outSize);
      
      if(DBLIB_SUCCESS != ret)
      {
         LOG_PRINT(LOG_MAJOR,"BssPsPreConfigTable is not configured at BSC, sending Nack");
         cfgSendNackToCm(CM_ERR_GPRS_NOT_ALLOWED);
         return;
      }
      else
      {
         free(psPreConfigTablePtr);
      }
   }
   if (FALSE == bssTableRangeChk(bssTableApiRcvdPtr))
   {
      LOG_PRINT(LOG_MAJOR, "bssTableRangeChk Failed, Sending Nack");
      cfgSendNackToCm(CM_ERR_PARAM_OUT_OF_RANGE);
      return;
   }
/*Changes PCU R2.5 Aricent -- END*/
   ret = updateBssTable(bssTableApiRcvdPtr);
   if (CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_CRITICAL,"DB Failure updateBssTable returned Error Code = [%d]", ret);
      cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);
   }
   else
   {
      gDbBssTableApiStorage = (*bssTableApiRcvdPtr);
      gBssNcc = bssTableApiRcvdPtr->ncc;
      cfgSendAckToCm();
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectPerformUpdateOperation");
} /* bssObjectPerformUpdateOperation */

I_Bool  bssObjectPerformConsistencyCheck()
{
   I_U32 noOfRACount = ZERO;
   I_U16 raSize = ZERO;
   RaTableApi *RaTableApiPtr = PNULL;
   RaTableApi *tempRaTableApiPtr = PNULL;
   LaTableApi *LaTableApiPtr = PNULL;
   LaTableIndices LaTableApiIndices;
   I_U32 raRecords = ZERO;
   /* Start of CCB Pcu Code change 9 */
   GbInterfaceTableIndices gbInterfaceTableIndicesBuff;
   GbInterfaceTableApi     *gbInterfaceTablePtr = PNULL;
   LepInfoTableApi *lepInfoTableApiPtr = PNULL;
   RepInfoTableApi *repInfoTableApiPtr =PNULL;
   I_U32 outCount = 0;
   I_U16 outSize  = 0;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_S32 ret = CM_FAILURE ;

   /* End of CCB Pcu Code change 9 */


   LOG_PRINT(LOG_INFO,"ENTERING bssObjectPerformConsistencyCheck");
   /* Read RA table and compare it against the LA table */
   ret = getallRaTable(&RaTableApiPtr,&noOfRACount,&raSize);
   if (CLIB_SUCCESS == ret)
   {
      for ( raRecords =0; raRecords < noOfRACount; raRecords++ )
      {
         tempRaTableApiPtr = (RaTableApi*)((I_U8 *)RaTableApiPtr + (raRecords *raSize));
         LaTableApiIndices.lac = tempRaTableApiPtr->lac;

         ret = getLaTable(&LaTableApiIndices,&LaTableApiPtr);
         if (CLIB_SUCCESS != ret)
         {
            free(RaTableApiPtr);
            return FALSE;
         }
         free(LaTableApiPtr);
      }
   }
   else 
   {   
      LOG_PRINT(LOG_CRITICAL,"Db call getallRaTable Failed, returned Error Code = [%d] ", ret);  
      return FALSE;
   }

   /* CCB Changes - Pcu # 7 & 9 Start...*/  
   gbInterfaceTableIndicesBuff.gbIfIndex= 0;
   LOG_PRINT(LOG_INFO,"Calling getallGbInterfaceTable()");
   ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outCountGb, &outSizeGb); 
   if ( CLIB_SUCCESS == ret )
   {
      LOG_PRINT(LOG_INFO,"getallGbInterfaceTable Passed : %d ",gbInterfaceTablePtr->transportType); 
      if (gbInterfaceTablePtr->transportType != FR )
      {
         ret = getallLepInfoTable( &lepInfoTableApiPtr, &outCount, &outSize);
         if (CLIB_SUCCESS != ret && 0 == outCount)
         {
            LOG_PRINT(LOG_CRITICAL,"There is no rows in LepInfo Table, Error Code = [%d]", ret);
            free(gbInterfaceTablePtr);
            return FALSE; 
         }
         ret = getallRepInfoTable( &repInfoTableApiPtr, &outCount, &outSize); 
         if (CLIB_SUCCESS != ret && 0 == outCount)
         {
            LOG_PRINT(LOG_CRITICAL,"There is no rows in repInfo Table, Error Code = [%d]", ret);
            free(gbInterfaceTablePtr);
            return FALSE; 
         }  
         if ( repInfoTableApiPtr != PNULL) free(repInfoTableApiPtr);
         if ( lepInfoTableApiPtr != PNULL) free(lepInfoTableApiPtr);
      }
      free(gbInterfaceTablePtr);
   }
   else
   {
      LOG_PRINT(CRITICAL,"getall GbInterface Table Failed, returned Error Code = [%d]", ret);  
      return FALSE;
   }

   /* CCB Changes - Pcu # 7 & 9 End...*/  

   LOG_PRINT(LOG_INFO,"EXITING bssObjectPerformConsistencyCheck");
   return TRUE;
} /* ssObjectPerformConsistencyCheck */

void bssObjectPerformUnlockOperation(BssTableApi* bssTableApiRcvdPtr)
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectPerformUnlockOperation");
   /* CS3.0 Changes : Start*/
   HoCtrlPreconfigTableApi *hoCtrlPreconfigTablePtr = PNULL;
   BssTableApi *bssTablePtr = PNULL;
   I_U32 rowCount = 0,bscId;
   I_U16 rowSize = 0;
   /* CS4.0: SwM Changes start */ 
   I_U8 slotId;
   I_U8 chasisFrameId;
   I_S32 ret = CM_FAILURE;
   /* CS4.0: SwM Changes End */ 
   /* Retrieve bscId from BSS Table */
   ret = getBscId(&bscId);
   if(CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_CRITICAL,"getBscId call is getting failed, returned Error Code = [%d]", ret);
      return;
   }
   ret = getActiveIccSlotId( &chasisFrameId, &slotId); 
   if ( CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call failed ErrorCause: %d",ret);
      return;
   }
   LOG_PRINT(LOG_INFO,"getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);

   /*Retrieve swStatus from SwMNode Table */
   #if 0
   swMNodeTableIndex.nodeType = SYS_NODE_TYPE_BSC;
   swMNodeTableIndex.nodeIdentity = bscId;
   swMNodeTableIndex.chasisFrameId = chasisFrameId;
   swMNodeTableIndex.slotId = slotId;
   ret = getSwStatusFromSwMNodeTable(swMNodeTableIndex,&swStatus);
   if(CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable DB call is getting failed, Error Code = [%d]", ret);
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   if(swStatus == SW_ACTIVATION_IN_PROGRESS)
   { 
      LOG_PRINT(LOG_DEBUG,"Software activation is in progress for the BSC");
      cfgSendNackToCm(CM_ERR_SW_BSC_ACT_IN_PROGRESS);
      return;
   }
   /* CS4.0: SwM Changes Start */ 
   ret = getEicSwStatusFromSwMNodeTable(SYS_NODE_TYPE_EIC, eicSwStatus, &count);
   if(CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_CRITICAL,"getSwStatusFromSwMNodeTable call is getting failed, Error Code = %d", ret); 
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   for ( index=0; index<count; index++)
   { 
      if(eicSwStatus[index] == SW_ACTIVATION_IN_PROGRESS)
      {
         LOG_PRINT(LOG_DEBUG,"Activation is in progress for EIC");
         cfgSendNackToCm(CM_ERR_SW_EIC_ACT_IN_PROGRESS);
         return;
      }
   }
   /* CS4.0: SwM Changes End */ 
   #endif
  /* check if activation is in progress for BSC/EIC/DSP */
   ret = isActivationInProgressForBscEicDsp( );
   if ( ret == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Activation is in progress for BSC or EIC or DSP or other");
      cfgSendNackToCm(CM_ERR_SW_ACT_IN_PROGRESS);
      return;
   }


   if(getallBssTable(&bssTablePtr,&rowCount,&rowSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getallBssTable DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      return;
   }
   if(getallHoCtrlPreconfigTable(&hoCtrlPreconfigTablePtr,&rowCount,&rowSize) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"getallHoCtrlPreconfigTable DB call is getting failed..");
      cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
      free(bssTablePtr); 
      return;
   }

   if(hoCtrlPreconfigTablePtr->tHoSeiz >= bssTablePtr->bssapTimer8)
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed : tHoSeiz is not less than bssapTimerT8");
      free(bssTablePtr); 
      free(hoCtrlPreconfigTablePtr); 
      cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
      return ;
   }
   if(bssTablePtr->tHandRqd  > hoCtrlPreconfigTablePtr->tHandUnsucc)
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed : tHandRqd is greater than tHandUnsucc");
      free(bssTablePtr); 
      free(hoCtrlPreconfigTablePtr); 
      cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
      return ;
   }
   if(bssTablePtr->bssapTimer8  < hoCtrlPreconfigTablePtr->t3103)
   {
      LOG_PRINT(LOG_DEBUG,"Consistancy failed : bssapTimer8 is lesser than t3101");
      free(bssTablePtr); 
      free(hoCtrlPreconfigTablePtr); 
      cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
      return ;
   }
   free(bssTablePtr); 
   free(hoCtrlPreconfigTablePtr); 
   /* CS3.0 Changes : End*/
   LOG_PRINT(LOG_DEBUG,"bssTableApiRcvdPtr->gprsEnabled : %d",bssTableApiRcvdPtr->gprsEnabled);
   if ( TRUE == gDbBssTableApiStorage.gprsEnabled)
   {

      if ( !bssObjectPerformConsistencyCheck())
      {
         LOG_PRINT(LOG_CRITICAL,"bssObjectPerformConsistencyCheck : consistancy failed.");
         LOG_PRINT(LOG_CRITICAL,"BSS Unlock not possible due to inconsistent configuration data.");
         cfgSendNackToCm(CM_ERR_BSS_CONSIST_CHECK_FAILED);
         return ;
      }
   }

   gUnlockReqFlag = TRUE; //change for mantis-30968
 
   /* Mantis 13939 Start*/
   gGbUnlockReqSent = FALSE; 
   /* Mantis 13939 End*/
   
   /* Send Immediate ACK to the CM */
   cfgSendAckToCm();

   /* Send LCLS_IND to AIFDHM to get it initialized after BSS-UNLOCK */
   cfgSendAifdhmLclsInd(gDbBssTableApiStorage.localSwitchingSupport, gDbBssTableApiStorage.bscId);

   /*BSC R2.0 changes Starts*/
    initiateDspUnlockforBssUnlock(); /*Required at the time of BSS LOCK/UNLOCK 29 Jan 2016 Gaurav Sinha*/
	 /*Above function commented for cloud as DSP LOCK_UNLOCK FEATURE not supported in CLOUD BSC 13 Jan 2016 Gaurav Sinha*/
   /*BSC R2.0 changes Starts*/
   
   /* Bug Fix - Mantis#4129 : Start */
   gBssState = unlockInProgress;
   gBssSubState = aIfUnlockInProgress;  
   bssObjectSendLinkAdminStateTableToScm(UNLOCKED,UNLOCKED);
   /* Bug Fix - Mantis#4129 : End */

   LOG_PRINT(LOG_INFO,"EXITING bssObjectPerformUnlockOperation");
} /* bssObjectPerformUnlockOperation */

void   bssObjectPerformLockOperation(BssTableApi* bssTableApiRcvdPtr)
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectPerformlockOperation");
   /* Send Immediate ACK to the CM */
   cfgSendAckToCm();
   gBssState = lockInProgress;
   gBssSubState = cellsLockInProgress;  
   gAifMsgSentToGrhm = 0;
   initiateDspLockforBssLock();  /*Required at the time of BSS LOCK/UNLOCK 29 Jan 2016 Gaurav Sinha*/ 
	 /*Above function commented for cloud as DSP LOCK_UNLOCK FEATURE not supported in CLOUD BSC 13 Jan 2016 Gaurav Sinha*/
   initiateCellLockDisableforUnlockedCells();

   LOG_PRINT(LOG_INFO,"EXITING bssObjectPerformlockOperation");
} /* bssObjectPerformLockOperation */

void informCellUnLockDisableforUnlckedCellsToBss()
{
/*Changes PCU R2.5 Aricent -- START*/
   GbInterfaceTableApi *gbInterfaceTablePtr = NULL;
   I_U32 outCountGb = 0;
   I_U16 outSizeGb = 0;
   I_S32 ret = CM_FAILURE;
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"ENTERING informCellUnLockDisableforUnlckedCellsToBss");
   /*After successful completion of Cell procedure for the cells,
     CFG will send OAMS_CFG_PCU_LOCK_REQ (Gb Interface) to PCU*/
   if ( TRUE == gDbBssTableApiStorage.gprsEnabled )
   {
/*Changes PCU R2.5 Aricent -- START*/
      LOG_PRINT(LOG_INFO, "GPRS is Enabled.Calling getallGbInterfaceTable()");
      ret = getallGbInterfaceTable(&gbInterfaceTablePtr, &outCountGb, &outSizeGb);
      if (CLIB_SUCCESS == ret)
      {
         if (FR == gbInterfaceTablePtr->transportType)
         {
            LOG_PRINT(LOG_INFO, "getallGbInterfaceTable Passed, transportType is FR. Calling initiateNsvcLockDisableForUnlockedNsvcs");
            /* CFG will execute Lock (Enabled) Nsvc procedure 
               for all the Unlocked and Enabled Nsvcs */
            initiateNsvcLockDisableForUnlockedNsvcs();
         }
         else /* In case of IP */ 
         {
            LOG_PRINT(LOG_INFO, "getallGbInterfaceTable Passed, transportType is IP. Calling informNsvcUnlockDisableForUnlockedNsvcsToBss");
            informNsvcUnlockDisableForUnlockedNsvcsToBss();
         }
         free(gbInterfaceTablePtr);
      }
      else 
      {
         LOG_PRINT(LOG_CRITICAL,"Db Call getallGbInterfaceTable failed, Error Code = [%d]", ret);
      }
/*Changes PCU R2.5 Aricent -- END*/
   }
   else
   {
      LOG_PRINT(LOG_INFO, "GPRS is Disabled.Calling bssObjectSendLinkAdminStateTableToScm");
      bssObjectSendLinkAdminStateTableToScm(UNLOCKED,LOCKED);
   }
   /* bssState remains in the LockInProgress State */

   LOG_PRINT(LOG_INFO,"EXITING informCellUnLockDisableforUnlckedCellsToBss");
} /*informCellUnLockDisableforUnlckedCellsToBss */

void informCellUnLockEnableforUnlockDisabledCellsToBss()
{
   /* Update AdminState of BSS table to UNLOCKED */
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff={0};
   I_S32 ret = CM_FAILURE;
/*Changes PCU R2.5 Aricent -- START*/ 
   OamsCfgPdcBssUnlockInd oamsCfgPdcBssUnlockIndBuff;
/*Changes PCU R2.5 Aricent -- END*/
   gDbBssTableApiStorage.adminState = UNLOCKED;
   
   LOG_PRINT(LOG_INFO,"ENTERING informCellUnLockEnableforUnlockDisabledCellsToBss");

   memset(&OamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));   
   getDbBssTable();

   ret = updateBssAdminState(gDbBssTableApiStorage.bscId,UNLOCKED);

   gBssState = unlocked;
   gBssSubState = noneBssSubState;  

   if(CLIB_SUCCESS == ret )
   {
			/*Latest changes merged for CLOUD R2-BSC ROOT BRANCH GAURAV SINHA 22 DEC 2015*/
      /* As BSS adminState is UNLOCKED, Send LCLS IND to AIFDHM and BSS_UNLOCK_IND to CPHM */
      cfgSendAifdhmLclsInd(gDbBssTableApiStorage.localSwitchingSupport, gDbBssTableApiStorage.bscId);
      cfgSendCphmBssUnlockInd();
			/*Latest changes merged for CLOUD R2-BSC ROOT BRANCH GAURAV SINHA 22 DEC 2015*/
      LOG_PRINT(LOG_INFO,"Value of gCfgStandbyToActive: %u, gUnlockReqFlag: %u",
		gCfgStandbyToActive,gUnlockReqFlag);

      if(gCfgStandbyToActive == I_FALSE)  
      {
				 
          if(gUnlockReqFlag == TRUE)
          {
          LOG_PRINT(LOG_INFO,"BSS Adminstate has been Updated as UNLOCKED");
          /* Send Alarm */
          OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = BSS_UNLOCKED;
          OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_BSS;
          OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
          OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
          
          OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
              sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"BSS [%u] is UNLOCKED",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);
          
          LOG_PRINT(LOG_INFO,"Sending Alarm BSS_UNLOCKED to AFH");
          cfgSendMessage((void *)&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
                 gUnlockReqFlag = FALSE;
          }
          else
          {     
         	LOG_PRINT(LOG_INFO,"Without UnlockReq, BSS Adminstate has been Updated as UNLOCKED");
          }
/*Changes PCU R2.5 Aricent -- START*/      
          /* send OAMS_CFG_PDC_BSS_UNLOCK_IND to PDC */
          LOG_PRINT(LOG_INFO,"Sending message OAMS_CFG_PDC_BSS_UNLOCK_IND");
          cfgSendMessage((void *)&oamsCfgPdcBssUnlockIndBuff, sizeof(OamsCfgPdcBssUnlockInd), ENT_OAM_PDC, OAMS_CFG_PDC_BSS_UNLOCK_IND, 0);
/*Changes PCU R2.5 Aricent -- END*/
      }
      /*changes for mantis #16235 starts */ 
      else 
      {
         LOG_PRINT(LOG_INFO,"For Standby Card gCfgStandbyToActive is true so making it false ");
         gCfgStandbyToActive =I_FALSE;
      }
      /*changes for mantis #16235 Ends */ 
           
   }
   else 
   {
     LOG_PRINT(LOG_CRITICAL,"Db Call updateBssAdminState failed, Error Code = [%d]", ret);
   }
   LOG_PRINT(LOG_INFO,"EXITING informCellUnLockEnableforUnlockDisabledCellsToBss");
} /* informCellUnLockEnableforUnlockDisabledCellsToBss */

/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header********************************
Function Name:       informNsvcUnlockDisableForUnlockedNsvcsToBss()
Parameters:          void
Return type:         void
Purpose:             this function is called from NsvcObjectHandler after
                     All Nsvcs that were Unlocked are disabled during Bss Lock
Other Note:
 ************************************************************************************/
I_Void informNsvcUnlockDisableForUnlockedNsvcsToBss()
{
   LOG_PRINT(LOG_INFO,"Entering informNsvcUnlockDisableForUnlockedNsvcsToBss()");
   if( TRUE == gGbUnlockReqSent)
   {
      /*Changes for Sending PsscmLockReq only if AdminState in Unlocked in gbInterfaceTable 05-Aug-2016 Mantis #31633 #31634 #31639*/
      GbInterfaceTableApi *gbInterfaceTableApi = NULL,*tmpGbInterfaceTableApi = NULL;
      I_U32 outRows = ZERO,i=ZERO;
      I_U16 outSize = ZERO;
      if(CLIB_SUCCESS == getallGbInterfaceTable(&gbInterfaceTableApi, &outRows, &outSize))
			{
				for(i = 0; i < outRows; ++i)
				 {
					 tmpGbInterfaceTableApi = (GbInterfaceTableApi *)((I_U8 *)gbInterfaceTableApi + i * outSize);

					 if(tmpGbInterfaceTableApi->adminState == UNLOCKED)
						{
							LOG_PRINT(DEBUG,"GB_LOCK_UNLOCK: GbInterfaceTableApi adminState is Unlocked will send PsscmLockReq");
              sendPsscmLockReq(OAMS_RSN_OPERATORINITIATED);
						}
            else
			      {
							LOG_PRINT(DEBUG,"GB_LOCK_UNLOCK: GbInterfaceTableApi adminState is Locked will not send PsscmLockReq : WILL proceed for STACK OPERATION");
              bssObjectSendLinkAdminStateTableToScm(UNLOCKED, LOCKED);
            }
				}
				free(gbInterfaceTableApi);
			}
      else
      {
				LOG_PRINT(DEBUG,"GB_LOCK_UNLOCK: DB CALL failed for GbInterfaceTableApi  will not send PsscmLockReq");
      }
      /*Changes for Sending PsscmLockReq only if AdminState in Unlocked in gbInterfaceTable 05-Aug-2016 Mantis #31633 #31634 #31639*/
      //sendPsscmLockReq(OAMS_RSN_OPERATORINITIATED); Changed for 05-Aug-2016
   }
   /* Mantis 13939 Start*/
   else
   {
      bssObjectSendLinkAdminStateTableToScm(UNLOCKED, LOCKED);
   }
   /* Mantis 13939 End*/
   LOG_PRINT(LOG_INFO,"Exiting informNsvcUnlockDisableForUnlockedNsvcsToBss()");
}
/********************************* Function  Header********************************
Function Name:       informNsvcUnlockEnableForUnlockDisabledNsvcsToBss()
Parameters:          void
Return type:         void
Purpose:             this function is called from NsvcObjectHandler after
                     All Nsvcs that were Unlocked are Enabled during Bss Unlock
Other Note:
 ************************************************************************************/
I_Void informNsvcUnlockEnableForUnlockDisabledNsvcsToBss()
{
   LOG_PRINT(LOG_INFO,"Entering informNsvcUnlockEnableForUnlockDisabledNsvcsToBss()");
   initiateCellUnlockEnableforUnlcokedDisabledCells();
   LOG_PRINT(LOG_INFO,"Exiting informNsvcUnlockEnableForUnlockDisabledNsvcsToBss()");
}
/*Changes PCU R2.5 Aricent -- END*/


void sendCellBarAccessToCells(AdminProcedure  adminProc,I_U8 reasonToBeSent )
{
   CellPerTableApi *CellTableApiPtr=NULL;
   CellPerTableApi *origCellTableApiPtr=NULL;
   I_U32 noOfCellCount=0;
   I_U16 cellSize=0;
   I_U32 i;
   I_U16 cellIndex = 0;
   OamsCfgCellhCellBarAccess OamCfgCellhCellBarAccessBuff;
/*Changes PCU R2.5 Aricent -- START*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccessBuff;
/*Changes PCU R2.5 Aricent -- END*/

   LOG_PRINT(LOG_INFO,"ENTERING sendCellBarAccessToCells");
   if ( getallCellPerTable(&CellTableApiPtr,&noOfCellCount,&cellSize) == CLIB_SUCCESS)
   {
      /* store for freeing it afterwards */
      origCellTableApiPtr = CellTableApiPtr;

      for ( i = 0; i < noOfCellCount;i++ )
      {
         getCellIndex(CellTableApiPtr->lac, CellTableApiPtr->cellId, &cellIndex);
         if (( adminProc == LockProcedure)&&
               (CellTableApiPtr->adminState ==UNLOCKED))
         {
            /* Mantis 16053 Fix --Satrt */
            /* We need to send the CellBarAccess with cell Barred even if cell is barred by the operator*/
            /*
            if(CellTableApiPtr->cellBarAccess == TRUE)
            {
               LOG_PRINT(LOG_INFO, "Cell is barred by the operator for Cellid [%u] and lac [%u]", CellTableApiPtr->cellId, CellTableApiPtr->lac);
               //CellTableApiPtr++;
               CellTableApiPtr = (CellPerTableApi*)((I_U8*)origCellTableApiPtr + (i+1)*cellSize);
               continue;
            }
            */
            /* Mantis 16053 Fix --End */


            OamCfgCellhCellBarAccessBuff.cellId = CellTableApiPtr->cellId;
            OamCfgCellhCellBarAccessBuff.lac = CellTableApiPtr->lac;
            OamCfgCellhCellBarAccessBuff.cellIndex = cellIndex;
            OamCfgCellhCellBarAccessBuff.cellBar = CELL_BARRED;
            OamCfgCellhCellBarAccessBuff.reason = reasonToBeSent;
            cfgSendMessage((void *)&OamCfgCellhCellBarAccessBuff, sizeof(OamsCfgCellhCellBarAccess), ENT_OAMS_CELLH, OAMS_CFG_CELLH_CELL_BAR_ACCESS , 0);      
            LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CELLH_CELL_BAR_ACCESS message for Cell [ cellId = %d, lac = %d, cellbar = TRUE ] ", CellTableApiPtr->cellId, CellTableApiPtr->lac);
/*Changes PCU R2.5 Aricent -- START*/            
            /* Send CellBarAccess to PSCH */
            if(I_TRUE == CellTableApiPtr->psAllowed)
            {
                 LOG_PRINT(LOG_INFO,"calling updateDataAvlbltyTblAtAifDown");
                 updateDataAvlbltyTblAtAifDown();
                 oamsCfgPschCellBarAccessBuff.cellId = CellTableApiPtr->cellId;
                 oamsCfgPschCellBarAccessBuff.lac = CellTableApiPtr->lac;
                 oamsCfgPschCellBarAccessBuff.cellIndex = cellIndex;
                 oamsCfgPschCellBarAccessBuff.cellBar = CELL_BARRED;
                 oamsCfgPschCellBarAccessBuff.reason = reasonToBeSent;
                 cfgSendMessage((void *)&oamsCfgPschCellBarAccessBuff, sizeof(OamsCfgPschCellBarAccess), ENT_OAMS_PSCH, OAMS_CFG_PSCH_CELL_BAR_ACCESS , 0);      
                 LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_PSCH_CELL_BAR_ACCESS message for Cell [ cellId = %d, lac = %d, cellbar = TRUE ] ", CellTableApiPtr->cellId, CellTableApiPtr->lac);
            }
/*Changes PCU R2.5 Aricent -- END*/   
             /* R2.4 Change : Start*/
           sendCellOprStateToCbsh(CellTableApiPtr->cellId, CellTableApiPtr->lac, CAUSE_CELL_BARRED);
             /* R2.4 Change : Ends*/
         }
         else
         {
            if (( adminProc == UnlockProcedure)&&
                  (CellTableApiPtr->adminState ==UNLOCKED))
            {
               
                /* Mantis 16053 Fix --Satrt */
                /* We need not to send the CellBarAccess with cell as Barred for the cells which are barred by the operator
                 * Rather we need to send the CellBarAccess with cell as Unbarred for those cells also
                 * which are barred by the operator*/
                /*
               if(CellTableApiPtr->cellBarAccess == TRUE)
               {
                  LOG_PRINT(LOG_INFO, "Cell is barred by the operator for Cellid [%u] and lac [%u]", CellTableApiPtr->cellId, CellTableApiPtr->lac);
                  //CellTableApiPtr++;
                  //Chnages for Cell BARR at the time of reboot 09-Aug-2010  starts
                  //CellTableApiPtr = (CellPerTableApi*)((I_U8*)origCellTableApiPtr + (i+1)*cellSize);
                  OamCfgCellhCellBarAccessBuff.cellId = CellTableApiPtr->cellId;
                  OamCfgCellhCellBarAccessBuff.lac = CellTableApiPtr->lac;
                  OamCfgCellhCellBarAccessBuff.cellIndex = cellIndex;
                  OamCfgCellhCellBarAccessBuff.cellBar = CELL_BARRED;
                  OamCfgCellhCellBarAccessBuff.reason = reasonToBeSent;
                  cfgSendMessage((void *)&OamCfgCellhCellBarAccessBuff, 
                         sizeof(OamsCfgCellhCellBarAccess), ENT_OAMS_CELLH, OAMS_CFG_CELLH_CELL_BAR_ACCESS , 0);      
                  LOG_PRINT(LOG_INFO,
                         "Sending OAMS_CFG_CELLH_CELL_BAR_ACCESS message for Cell [cellId=%d,lac=%d,cellbar=TRUE]", 
                             CellTableApiPtr->cellId, CellTableApiPtr->lac);
                  //Changes PCU R2.5 Aricent -- START            
                  //Send CellBarAccess to PSCH 
                  oamsCfgPschCellBarAccessBuff.cellId = CellTableApiPtr->cellId;
                  oamsCfgPschCellBarAccessBuff.lac = CellTableApiPtr->lac;
                  oamsCfgPschCellBarAccessBuff.cellIndex = cellIndex;
                  oamsCfgPschCellBarAccessBuff.cellBar = CELL_BARRED;
                  oamsCfgPschCellBarAccessBuff.reason = reasonToBeSent;
                  cfgSendMessage((void *)&oamsCfgPschCellBarAccessBuff, sizeof(OamsCfgPschCellBarAccess), 
                       ENT_OAMS_PSCH, OAMS_CFG_PSCH_CELL_BAR_ACCESS , 0);      
                  LOG_PRINT(LOG_INFO,
                      "Sending OAMS_CFG_PSCH_CELL_BAR_ACCESS message for Cell[cellId=%d,lac=%d,cellbar=TRUE]", 
                         CellTableApiPtr->cellId, CellTableApiPtr->lac);
                  //Changes PCU R2.5 Aricent -- END   
                  //R2.4 Change : Start
                  sendCellOprStateToCbsh(CellTableApiPtr->cellId, CellTableApiPtr->lac, CAUSE_CELL_BARRED);
                  //R2.4 Change : Ends
                  //continue;
                  //Chnages for Cell BARR at the time of reboot 09-Aug-2010 Ends
               }
               */
               /* Mantis 16053 Fix --End */
               /* Procedure is LOCK , so send cell barr access to all */
               OamCfgCellhCellBarAccessBuff.cellId = CellTableApiPtr->cellId;
               OamCfgCellhCellBarAccessBuff.lac = CellTableApiPtr->lac;
               OamCfgCellhCellBarAccessBuff.cellIndex = cellIndex;
               OamCfgCellhCellBarAccessBuff.cellBar = CELL_UNBARRED;
               OamCfgCellhCellBarAccessBuff.reason = reasonToBeSent;
               cfgSendMessage((void *)&OamCfgCellhCellBarAccessBuff, sizeof(OamsCfgCellhCellBarAccess), ENT_OAMS_CELLH, OAMS_CFG_CELLH_CELL_BAR_ACCESS , 0);            
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_CELLH_CELL_BAR_ACCESS message for Cell [ cellId = %d, lac = %d, cellbar = FALSE ] ", CellTableApiPtr->cellId, CellTableApiPtr->lac);
/*Changes PCU R2.5 Aricent -- START*/               
            if(I_TRUE == CellTableApiPtr->psAllowed)
            {
                 
                 LOG_PRINT(LOG_INFO,"calling updateDataAvlbltyTblAtAifUp");
                updateDataAvlbltyTblAtAifUp(); 
               /* Send CellBarAccess to PSCH */
               oamsCfgPschCellBarAccessBuff.cellId = CellTableApiPtr->cellId;
               oamsCfgPschCellBarAccessBuff.lac = CellTableApiPtr->lac;
               oamsCfgPschCellBarAccessBuff.cellIndex = cellIndex;
               oamsCfgPschCellBarAccessBuff.cellBar = CELL_UNBARRED;
               oamsCfgPschCellBarAccessBuff.reason = reasonToBeSent;
               cfgSendMessage((void *)&oamsCfgPschCellBarAccessBuff, sizeof(OamsCfgPschCellBarAccess), ENT_OAMS_PSCH, OAMS_CFG_PSCH_CELL_BAR_ACCESS , 0);      
               LOG_PRINT(LOG_INFO,"Sending OAMS_CFG_PSCH_CELL_BAR_ACCESS message for Cell [ cellId = %d, lac = %d, cellbar = FALSE ] ", CellTableApiPtr->cellId, CellTableApiPtr->lac);
            }
/*Changes PCU R2.5 Aricent -- END*/  
               /* R2.4 Change : Start*/
               sendCellOprStateToCbsh(CellTableApiPtr->cellId, CellTableApiPtr->lac, CAUSE_CELL_UNBARRED);
               /* R2.4 Change : Ends*/
            }
         }
         //CellTableApiPtr++;
         CellTableApiPtr = (CellPerTableApi*)((I_U8*)origCellTableApiPtr + (i+1)*cellSize);
      }
      if (origCellTableApiPtr !=NULL)
         free(origCellTableApiPtr);
   }
   LOG_PRINT(LOG_INFO,"EXITING sendCellBarAccessToCells()");
} /* sendCellBarAccessToCells */


void getDbBssTable()
{
   I_S32  retValue=0;
   BssTableApi * bssTableApiDbPtr=NULL;
   I_U32 outPutCount=0;
   I_U16 outSize=0;
   LOG_PRINT(LOG_INFO,"ENTERING getDbBssTable()");
   /* Read the DB and get the database table for the BSS */
   retValue = getallBssTable(&bssTableApiDbPtr,&outPutCount,&outSize);
   if (retValue == CLIB_SUCCESS && bssTableApiDbPtr != NULL)
   {
      //gDbBssTableApiStorage =  (*bssTableApiDbPtr); Remove for to avoid invalid read
      memcpy(&gDbBssTableApiStorage,bssTableApiDbPtr,outSize);
      gBssNcc = bssTableApiDbPtr->ncc;
      LOG_PRINT(LOG_DEBUG,"gBssNcc = %d", gBssNcc);
      free(bssTableApiDbPtr);
   }
   LOG_PRINT(LOG_INFO,"EXITING getDbBssTable()");
} /* getDbBssTable */

void bssObjectHandlerForSSProhibit()
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectHandlerForSSProhibit()");
   if(gSSAReceived == TRUE)
   {
      gSSAReceived = FALSE; /*Mantis 2284*/
      setAinterfaceTableOperationalState(DISABLED);

      /* Send OAMS_CFG_GRHM_LOCK_REQ */
      /*gAinterfaceUPDownFlag = FALSE; commented during fix for 2284 - no use of this updown flag */
      OamsCfgGrhmLockReq OamCfgGrhmLockReqBuff;
      /************* fix for mantis-1797 ***********************/
      memset(&OamCfgGrhmLockReqBuff,0,sizeof(OamsCfgGrhmLockReq));
      /**********************************************************/
      OamCfgGrhmLockReqBuff.objectId=0;
      OamCfgGrhmLockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
      /************ SPR # 206 Start *****************/
      OamCfgGrhmLockReqBuff.reason = OAMS_RSN_AINTERFACEDOWN;  
      /************ SPR # 206 End *****************/
      cfgSendMessage((void *)&OamCfgGrhmLockReqBuff, sizeof(OamsCfgGrhmLockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_LOCK_REQ, 0);
      gAifMsgSentToGrhm = OAMS_CFG_GRHM_LOCK_REQ;
   }
   else if((gBssState == lockInProgress) && (gAifMsgSentToGrhm != OAMS_CFG_GRHM_LOCK_REQ))
   {
      OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff={0};
      /* Update DB state to LOCKED */
      memset(&OamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
      gDbBssTableApiStorage.adminState = LOCKED;
      getDbBssTable();
      if(updateBssAdminState(gDbBssTableApiStorage.bscId,LOCKED)==CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"BSS Admin state has been updated to LOCKED.."); 
         /* Send Alarm */
         OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = BSS_LOCKED;
         OamsCfgAfhSysAlarmBuff.sysAlarm.info3=OAMS_OBJTYPE_BSS;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key1=gDbBssTableApiStorage.bscId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = 
            sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"BSS [%d] is LOCKED",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);
         LOG_PRINT(LOG_INFO,"Sending Alarm BSS_LOCKED to AFH"); 
         cfgSendMessage((void *)&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         gBssState = locked;  
         gBssSubState = noneBssSubState;  
      }
      else
      {
         LOG_PRINT(LOG_MAJOR,"updateBssAdminState DB Call Failed");
      }
      LOG_PRINT(LOG_INFO,"LINK Stop Ack received from SCM.");
   }
   else
   {
      LOG_PRINT(LOG_INFO," Not expected");
   }
   LOG_PRINT(LOG_INFO,"EXITING bssObjectHandlerForSSProhibit()");
} /* bssObjectHandlerForSSProhibit */

void bssObjectHandlerForSSAllowed()
{
   LOG_PRINT(LOG_INFO,"Entering function bssObjectHandlerForSSAllowed()");
   /* Send CFG_GRHM_UNLOCK_REQ  to GRHM */
   /*gAinterfaceUPDownFlag = FALSE;  commented during fix for 2284 - no use of this updown flag */
   OamsCfgGrhmUnlockReq OamCfgGrhmUnlockReqBuff;
   OamCfgGrhmUnlockReqBuff.objectId=0;
   OamCfgGrhmUnlockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
   /************ SPR # 206 Start *****************/
   OamCfgGrhmUnlockReqBuff.reason = OAMS_RSN_STARTUP;  
   /************ SPR # 206 End *****************/
   cfgSendMessage((void *)&OamCfgGrhmUnlockReqBuff, sizeof(OamsCfgGrhmUnlockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_UNLOCK_REQ, 0);
   gAifMsgSentToGrhm = OAMS_CFG_GRHM_UNLOCK_REQ;
   LOG_PRINT(LOG_INFO,"Exiting function bssObjectHandlerForSSAllowed()");
} /* bssObjectHandlerForSSAllowed */

I_Bool checkAndSendLinkActivationRequest()
{
   I_U32 outRows=0;
   I_U16 outSize=0;
   //LinkTableApi       *linkPtr=NULL;
   //LinkTableApi       *tmpLinkPtr=NULL;
   I_U32 cardOprState = 0;
   I_S32 retVal = FALSE;
   /*IP_BSC_STACK*/
   SigtranM3uaLAspConfigTableApi* sigtranM3uaLAspConfigTableApi = NULL,*tmpSigtranM3uaLAspConfigTableApi=NULL;
   /*I_U8 slotId;
   I_U8 chasisFrameId;*/
   /*IP_BSC_STACK*/
   
   LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: checkAndSendLinkActivationRequest: Entering into function");
   if (gStackStatus != SS7_STACK_UP) {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: checkAndSendLinkActivationRequest: Request cannot be send to SCM as Ss7 Stack status is Down");
      return retVal;
   }
   
   /*if (getallLinkTable(&linkPtr,&outRows,&outSize) != CLIB_SUCCESS) {
      LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequest: read getallLinkTable() Failed");
      return retVal;
   }*/ //IP_BSC_STACK: Changes 18 July 2016 Gaurav Sinha
  if(CLIB_SUCCESS != getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outRows,&outSize))
  {
      LOG_PRINT(LOG_INFO, "IP_BSC_STACK: read getallSigtranM3uaLAspConfigTable() Failed");
      return retVal;
  }
      /*Following section changed for IP_BSC_STACK 18 July 2016 Gaurav Sinha*/
   /*retVal = getActiveIccSlotId( &chasisFrameId, &slotId); CHECK FIRST IP_BSC_STACK:
   if ( CLIB_SUCCESS != retVal)
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: getActiveIccSlotId Db call failed ErrorCause: %d",retVal);
      return retVal;
   }
   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   slotId = slotId-2;//Cloud Specific Change
   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: After deduction SlotId [%d] ",slotId);*/
   //LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequest: Total Num of Configured Links = %u", outRows);
   LOG_PRINT(LOG_INFO, "IP_BSC_STACK :checkAndSendLinkActivationRequest: Total Num of Configured ASP in SigtranM3uaLAspConfigTable = %u", outRows);
   while (gLinkMsgSentForBss < outRows) {
     tmpSigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)((I_U8*)sigtranM3uaLAspConfigTableApi + (gLinkMsgSentForBss * outSize));
     gLinkMsgSentForBss++;
     //If the card is not present then try for the next entry
        if (getStateForSlotIdIccTable((tmpSigtranM3uaLAspConfigTableApi->slotId+2),&cardOprState) != CLIB_SUCCESS) {
        LOG_PRINT(LOG_DEBUG, "IP_BSC_STACK: checkAndSendLinkActivationRequest: Received slotId[%d] does not exists in iccCardInfo Table",(tmpSigtranM3uaLAspConfigTableApi->slotId+2));
        //if(tmpSigtranM3uaLAspConfigTableApi->slotId != slotId) CHECK FIRST IP_BSC_STACK:
        //{
        	continue;
        }
     //}
     //if (cardOprState == CARDSTATE_ACTIVE) {
        #if 0
				 //Mantis 9108 start
        if (cardOprState == CARDSTATE_ACTIVE) {
               gReqSentToScm =1;
               LOG_PRINT(LOG_INFO, "checkAndSendLinkActivationRequest: gReqSentToSCM= %d", gReqSentToScm);
        }
		  //mantis 9108 end
        #endif
				//LOG_PRINT(LOG_DEBUG,"CHECK: cardOprState = %d adminState = %d e1State = %d",cardOprState,tmpLinkPtr->adminState,gE1Data[tmpLinkPtr->e1Num].e1State);
				/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
        //if ( (tmpLinkPtr->adminState == UNLOCKED) && 
        //     (gE1Data[tmpLinkPtr->e1Num].e1State == unlocked)) 
				/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
        if (tmpSigtranM3uaLAspConfigTableApi->adminState == UNLOCKED)  
        {
            /*OamScmLinkAdminState linkConfig;
            linkConfig.linkId = tmpLinkPtr->linkId;
            linkConfig.linkSetId = tmpLinkPtr->linksetID;
            linkConfig.adminState = UNLOCKED;*/
            OamScmM3uaLocalAspAdminConfig m3uaLocalAspAdminConfig;
            m3uaLocalAspAdminConfig.localAspId = tmpSigtranM3uaLAspConfigTableApi->localAspId; 
            m3uaLocalAspAdminConfig.adminState = UNLOCKED; 
            /*Changes for R2.3.4 Starts*/ 
            /*if(fillMtp2TimerInfo( &(linkConfig.mtp2TimerConfig),tmpLinkPtr->satFlag ) != I_TRUE)
            {
                LOG_PRINT(MAJOR,"fillMtp2TimerInfo Failed - Not Sending linkAdminConfig to SCM");
            }
            else 
            {*/
            /*Changes for R2.3.4 Ends*/ 
               gIsAllLinkUnlockReqd = TRUE; 
               LOG_PRINT(LOG_INFO, "IP_BSC_STACK: checkAndSendLinkActivationRequest: Setting gIsAllLinkUnlockReqd to TRUE ");
               setStackObject(BSC_API_SET_BSSTABLE, SCM_MODIFY, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG);
               if (cfgSendStackMessage((I_Void *)&m3uaLocalAspAdminConfig, sizeof(OamScmM3uaLocalAspAdminConfig)) == CFG_SUCCESS) 
               {
                  LOG_PRINT(LOG_INFO,"IP_BSC_STACK: checkAndSendLinkActivationRequest: Sending OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG ASPID[%u] to Oil..",tmpSigtranM3uaLAspConfigTableApi->localAspId);
                  gReqSentToScm =1;
                  retVal = TRUE;
               }
            //}//fillMtp2TimerInfo is success IP_BSC_STACK: 
        }
     //}
    /*else {
        LOG_PRINT(LOG_DEBUG,"checkAndSendLinkActivationRequest: Not sending Link Activation Request as Link[%u] not for active card",
                  tmpLinkPtr->linkId);
     }*/
     //If link activation request is sent then return ;
     if (retVal) {
       break;
     }
   }   
   free(sigtranM3uaLAspConfigTableApi);
   LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: checkAndSendLinkActivationRequest: Exiting into function");
   return retVal;
}

void bssObjectSendLinkAdminStateTableToScm(I_U32 admStateToChk, I_U32 admStateToSend )
{
   LOG_PRINT(LOG_INFO,"ENTERING bssObjectSendLinkAdminStateTableToScm()");
#if 0 /* CS4.0 HA Stack Changes */  
   LinkAdminStateTableApi *LinkAdminStateTableApiPtr=NULL; 
   LinkAdminStateTableApi *tempLinkAdminStateTableApiPtr=NULL;
   AbisTimeSlotTableQuatIndices  AbisTimeSlotTableQuatIndicesbuff;
   AbisTimeSlotPerTableApi *timeSlotObjPtr=NULL;
   AbisTimeSlotPerTableApi *t=NULL;
   I_U32 outRowsForTimeSlot = 0;
   I_U16 outSizeForTimeSlot = 0;
   I_U8 E1_AdminState=0;
   I_U8 TimeSlot_AdminState=0; 
#endif    
   OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff={0};
   //I_U8 isReqSentToSCM =0;
   /* CS4.0 HA Stack Changes : Start */
   gLinkMsgSentForBss = 0;
   gReqSentToScm = 0;
   gLinkLockMsgSentForBss = 0;
   memset(&OamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
   if (admStateToSend == UNLOCKED)
   {
      if (checkAndSendLinkActivationRequest() == TRUE)
      {
         //isReqSentToSCM =1;
        LOG_PRINT(LOG_INFO,"IP_BSC_STACK:checkAndSendLinkActivationRequest completed successfully"); 
      }
   }
   else if (admStateToSend == LOCKED)
/* Mantis 8161 changes start */
   {
      if (checkAndSendLinkDeactivationRequest() == TRUE)
      {
         //isReqSentToSCM =1;
        LOG_PRINT(LOG_INFO,"IP_BSC_STACK:checkAndSendLinkDeactivationRequest completed successfully"); 
      }
   }
#if 0
   {
   if (gStackStatus == SS7_STACK_UP)
   {
      if (getallLinkTable(&linkPtr,&outRows,&outSize) == CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO, "Number of rows returned by API getallLinkTable = %d", outRows);
         for (i = 0; i < outRows; i++)
         {
            tmpLinkPtr = (LinkTableApi *)((I_U8*)linkPtr + (i *outSize));

            if ((tmpLinkPtr->adminState == admStateToChk) && 
                  (gE1Data[tmpLinkPtr->e1Num].e1State == unlocked))
            {
               OamScmLinkAdminState linkConfig;
               linkConfig.linkId = tmpLinkPtr->linkId; 
               linkConfig.linkSetId = tmpLinkPtr->linksetID;
               linkConfig.adminState = admStateToSend;  
               setStackObject(BSC_API_SET_BSSTABLE, SCM_LOCK, OAM_SCM_LINK_ADMIN_CONFIG);

               LOG_PRINT(LOG_INFO,"Sending OAM_SCM_LINK_ADMIN_CONFIG to Oil..");
               gLinkMsgSentForBss++;

               if (cfgSendStackMessage((I_Void *)&linkConfig, sizeof(OamScmLinkAdminState)) != CFG_SUCCESS)
               {
                  free(linkPtr);
                  return;
               }
               isReqSentToSCM =1;
            }
         }
         free(linkPtr);
      }
      else 
         LOG_PRINT(LOG_INFO, "INIT : read getallLinkTable() Failed");
   }
   else 
   {
      LOG_PRINT(LOG_DEBUG,"Request cannot be send to SCM as Ss7 Stack status is Down");
   }
   }
#endif

/* Mantis 8161 changes end */

   /* CS4.0 HA Stack Changes : End */
#if 0 /* CS4.0 HA Stack Changes*/
   if ( getallLinkAdminStateTable( &LinkAdminStateTableApiPtr,&outRows,
            &outSize) == CLIB_SUCCESS )
   {

      for ( i = 0; i < outRows;i++ )
      {
         tempLinkAdminStateTableApiPtr =(LinkAdminStateTableApi*)
            ((I_U8*)LinkAdminStateTableApiPtr + (i *outSize));

         if ( tempLinkAdminStateTableApiPtr->linkAdminadminState 
               == admStateToChk)
         {
            tempLinkAdminStateTableApiPtr->linkAdminadminState =  admStateToSend;
            LOG_PRINT(LOG_INFO,"Checking the E1 & TimeSlot Adminstate For this Link..");
            AbisTimeSlotTableQuatIndicesbuff.usageType = SYS_TS_USAGE_MTP2;
            AbisTimeSlotTableQuatIndicesbuff.usingEntity = 0 ;
            AbisTimeSlotTableQuatIndicesbuff.usingEntity = maskBits(AbisTimeSlotTableQuatIndicesbuff.usingEntity,tempLinkAdminStateTableApiPtr-> linkAdminlinkCode,lBYtes);
            AbisTimeSlotTableQuatIndicesbuff.usingEntity = maskBits(AbisTimeSlotTableQuatIndicesbuff.usingEntity,tempLinkAdminStateTableApiPtr->linkAdminlinksetID,16);
            LOG_PRINT(LOG_INFO,"LinkCode + LinksetID : %d",AbisTimeSlotTableQuatIndicesbuff.usingEntity);
            if (getTimeSlotTableQuat(&AbisTimeSlotTableQuatIndicesbuff,&timeSlotObjPtr,&outRowsForTimeSlot,&outSizeForTimeSlot) != CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_CRITICAL, "bssObjectSendLinkAdminStateTableToScm : getTimeSlotTableQuat() Failed");
               return;
            }
            if( outRowsForTimeSlot != 1)
            {
               LOG_PRINT(LOG_MAJOR, "Only one row shall be returned for a combination of link-id/linkset-id Failed");
               free(timeSlotObjPtr); 
               return;
            }
            TimeSlot_AdminState = LOCKED;  
            E1_AdminState = LOCKED;
            t = (AbisTimeSlotPerTableApi*) timeSlotObjPtr; 
            LOG_PRINT(LOG_INFO,"TimeSlot # ID : %d  E1 For This TimeSlot : %d AdminState  %d", t->tsNum,t->e1Num,t->adminState);  

            if(t->adminState == UNLOCKED)
            {
               TimeSlot_AdminState = UNLOCKED;   
               LOG_PRINT(LOG_INFO,"TimeSlot %d is UNLOCKED",t->tsNum); 
            } 
            else
               LOG_PRINT(LOG_INFO,"TimeSlot %d is LOCKED",t->tsNum); 

            if(gE1Data[t->e1Num].e1State == unlocked)
            {  
               LOG_PRINT(LOG_INFO," E1 %d is UNLOCKED",gE1Data[t->e1Num].e1Number); 
               E1_AdminState = UNLOCKED;
            }
            else  
               LOG_PRINT(LOG_INFO," E1 %d is LOCKED",gE1Data[t->e1Num].e1Number); 

            free(timeSlotObjPtr); 
            LOG_PRINT(LOG_INFO," E1LOCKED  %d  TIMESLOT_UNLOCKED %d",E1_AdminState , TimeSlot_AdminState); 

            if(TimeSlot_AdminState == UNLOCKED  && E1_AdminState == UNLOCKED)
            {  
               {

                  LOG_PRINT(LOG_INFO,"Sending Link Request to SCM, As TimeSlot / E1 for this Link is Unlocked"); 
                  sendLinkAdminStateTableReqToScm(tempLinkAdminStateTableApiPtr);
                  isReqSentToSCM =1;
               }      
            }
         }
      }
      free(LinkAdminStateTableApiPtr);
   }
#endif

   /*************************** SKIP A Interface Lock / Unlock ********************************************/ 
   //if( (gReqSentToScm == 0) && (gCfgStandbyToActive != I_TRUE) )
   if( gReqSentToScm == 0 )
   {
      /*Skipping the A Interface unlock/lock procedure..*/
      if (gStackStatus == SS7_STACK_UP)
         LOG_PRINT(LOG_DEBUG,"Link Request Cannot be Send to SCM, As TimeSlot / E1 for this Link is Locked"); 
      /*Check request type is UNLOCK or LOCK*/
      if(admStateToSend == UNLOCKED)
      {
         if(gCfgStandbyToActive == I_TRUE)
         {
            LOG_PRINT(DEBUG,"gCfgStandbyToActive flag is true hence not sending Unlock Req to Cells"); 
            return;
         }

         //if (gDbBssTableApiStorage.gprsEnabled)   Merged for Mantis #31470
         if (gDbBssTableApiStorage.gprsEnabled && (gNseiData.nseiState != locked))
         {

            LOG_PRINT(LOG_INFO,"UNLOCK GB interface towards GB interface");
            /* UNLOCK GB interface towards GB interface */
            sendPsscmUnlockReq(OAMS_RSN_OPERATORINITIATED);	    
            return;
         }
         else
         {
            /* CFG will execute Unlock (Enabled) Cell procedure
               for all the Unlocked and Disabled cells */
            initiateCellUnlockEnableforUnlcokedDisabledCells();
            return;   
         }
      }
      else
      {
         /*admStateToSend == LOCKED*/
         /*Skip A inter face Lock procedure & continue BSS lock procedure..*/  
         /* Update DB state to LOCKED */
         if(gCfgStandbyToActive != I_TRUE)
         { 
            if(updateBssAdminState(gDbBssTableApiStorage.bscId,LOCKED)==CLIB_SUCCESS)
            {
               LOG_PRINT(LOG_INFO,"BSS Admin state has been updated to LOCKED..");
               /* Send Alarm */
               OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = BSS_LOCKED;
               OamsCfgAfhSysAlarmBuff.sysAlarm.info3=OAMS_OBJTYPE_BSS;
               OamsCfgAfhSysAlarmBuff.sysAlarm.key1=gDbBssTableApiStorage.bscId;
               /* Mantis Id 2242 Start */
               OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
               /* Mantis Id 2242 End */
            
               OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"BSS [%d] is LOCKED",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);                                                                                                                        
               LOG_PRINT(LOG_INFO,"Sending Alarm BSS_LOCKED to AFH"); 
               cfgSendMessage((void *)&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            } 
         } 
       
         gCfgStandbyToActive = I_FALSE; 
         gBssState = locked;
         gBssSubState = noneBssSubState;  
         getDbBssTable();
      }   
   }

   LOG_PRINT(LOG_INFO,"EXITING bssObjectSendLinkAdminStateTableToScm()");
   return;   
}



void setAinterfaceTableOperationalState(I_U32 opStateToSet)
{
   LOG_PRINT(LOG_INFO,"ENTERING setAinterfaceTableOperationalState()");
   AInterfaceTableApi *aInterfaceTableApiPtr=NULL;
   I_U32 outRows=0;
   I_U16 outSize=0;
   /* CS4.0 HA Stack Changes : Start */
   AifInterfaceTableApi *aifInterfaceTablePtr=NULL;


   if (getallAInterfaceTable(&aInterfaceTableApiPtr,
            &outRows, &outSize) == CLIB_SUCCESS )
   {
      aInterfaceTableApiPtr->oprState = opStateToSet;
      if( updateAInterfaceTable(aInterfaceTableApiPtr) 
            != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL," udpation AInterfaceTableApi failed ");
      }
      free(aInterfaceTableApiPtr);
   }

   else
   {
      LOG_PRINT(LOG_CRITICAL," getallAInterfaceTable failed ");   
   }
   /* CS4.0 HA Stack Changes : End */


   if (getallAifInterfaceTable(&aifInterfaceTablePtr,
            &outRows, &outSize) == CLIB_SUCCESS )
   {
      aifInterfaceTablePtr->operationalState = opStateToSet;
      if( updateAifInterfaceTable(aifInterfaceTablePtr) != CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_CRITICAL,"updateAifInterfaceTable failed ");
      }
      else
      {
         OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff={0};
         /* Send Alarm */
         memset(&OamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
         if ( opStateToSet == DISABLED)
         { 
            OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = AINTERFACE_DISABLED;
            /************** SPR # 198 Start ***************/
            OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_AIFINTERFACE;
            OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = aifInterfaceTablePtr->interfaceId;
            /* Mantis Id 2242 Start */
            OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CRITICAL;
            /* Mantis Id 2242 End */

            OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"A Interface is Disabled");
            LOG_PRINT(LOG_INFO,"Sending Alarm AINTERFACE_DISABLED to AFH");
            /************** SPR # 198 End ***************/
         }
         else
         {  
            OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = AINTERFACE_ENABLED;
            /************** SPR # 198 Start ***************/
            OamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_AIFINTERFACE;
            OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = aifInterfaceTablePtr->interfaceId;
            /* Mantis Id 2242 Start */
            OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
            /* Mantis Id 2242 End */

            OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"A Interface is Enabled");
            LOG_PRINT(LOG_INFO,"Sending Alarm AINTERFACE_ENABLED to AFH");
            /************** SPR # 198 End ***************/
         }
         cfgSendMessage((void *)&OamsCfgAfhSysAlarmBuff, 
               sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, 
               OAMS_CFG_AFH_ALARM_IND, 0);


      }
      free(aifInterfaceTablePtr); /* Added in CS4.0 HA Stack */
   }
   else
   {
      LOG_PRINT(LOG_CRITICAL," getallAInterfaceTable failed ");   
   }
   LOG_PRINT(LOG_INFO,"EXITING setAinterfaceTableOperationalState()");
}

/********************************* Function  Header*****************************
  Function Name   : isCgiUnqInBss()
Parameters      : I_PVoid  : receivedMsgPtr
I_U8     : cellType
Return type     : I_Bool
Purpose         : It return TRUE if CGI is unique in BSS, otherwise it return FALSE.
When Mcc & Mnc are update in BssTable then CGI of all internal cells
are changed,so this function checks that uniqueness of new CGI in 
external cell table.
Other Note      : Fixed Mantis#6033
 *******************************************************************************/
I_Bool isCgiUnqInBss(I_U16 mcc, I_U16 mnc)
{
   I_U16                      rowSize;
   I_U32                      rowCount;
   I_S32                      retVal;
   I_U32                      index;
   CsExternalCellTableApi     *csExternalCellTableApiPtr = PNULL;
   CsExternalCellTableIndices csExtCellTableInd;
   CellPerTableApi            *cellPerTableApiPtr        = PNULL;
   CellPerTableApi            *tempcellPerTableApiPtr    = PNULL;
	 CsNeighCellsTableApi *csNeighCells=PNULL;
	 I_U32 count =0;
	 I_U16 outSize;
	 CsNeighCellsTableApi *tempCsNeighCellsTableApiPtr=PNULL;
	 CellPerTableApi *cellTable=PNULL;
	 CellPerTableIndices cellTableIndices;
	I_S32 k;

   LOG_PRINT(LOG_INFO,"Entering Function : isCgiUnqInBss");
   LOG_PRINT(LOG_DEBUG,"isCgiUnqInBss : Received mcc : %u, mnc : %u",mcc, mnc);

   /* For all configured cells in CellPerTable check that new CGI is not already 
      configured in CsExternalCellTable */
   retVal = getallCellPerTable(&cellPerTableApiPtr, &rowCount, &rowSize);
   if(DBLIB_SUCCESS == retVal)
   {
      for(index = ZERO; index < rowCount; index++)
      {
         tempcellPerTableApiPtr = (CellPerTableApi *)(((I_U8 *)cellPerTableApiPtr) + (index * rowSize));
         csExtCellTableInd.csExtCellId = tempcellPerTableApiPtr->cellId;
         csExtCellTableInd.lac         = tempcellPerTableApiPtr->lac;
         csExtCellTableInd.mcc         = mcc;
         csExtCellTableInd.mnc         = mnc;
         retVal = getCsExternalCellTable(&csExtCellTableInd, &csExternalCellTableApiPtr);
         if(DBLIB_SUCCESS == retVal)
         {
            free(csExternalCellTableApiPtr);
            free(cellPerTableApiPtr);
            LOG_PRINT(LOG_MAJOR,"CGI with cellId : %d, lac : %d, mcc : %d, mnc : %d already exist in External cell Table",
                  csExtCellTableInd.csExtCellId, csExtCellTableInd.lac, mnc, mcc);
            return FALSE;
         }
         else
         {
            continue;
         }
      }



  	/* 12446*/
   /* To check internal CS Neighbour cells are present in internal Cell Table */
 for(index = ZERO; index < rowCount; index++)
{
	tempcellPerTableApiPtr = NULL;   
	tempcellPerTableApiPtr = (CellPerTableApi *)(((I_U8 *)cellPerTableApiPtr) + (index * rowSize));

	if (getCsInternalNeighCellsForCell(tempcellPerTableApiPtr->cellId,tempcellPerTableApiPtr->lac,&csNeighCells,&count,&outSize)== CLIB_SUCCESS)
  	{
   for (k = 0; k < count; k++)
     {
	    tempCsNeighCellsTableApiPtr = (CsNeighCellsTableApi*)((char*)csNeighCells + (k *outSize));
	    cellTableIndices.cellId = tempCsNeighCellsTableApiPtr->neighborCellId;
	    cellTableIndices.lac = tempCsNeighCellsTableApiPtr->neighborLac;

		  if (getCellPerTable(&cellTableIndices,&cellTable) ==CLIB_SUCCESS)
  		{
 		  	if (tempCsNeighCellsTableApiPtr->neighborMnc !=  mnc || tempCsNeighCellsTableApiPtr->neighborMcc != mcc)
		     {
		       /* Internal CS Neighbor Cell's MNC and MCC not present in BSS table */
		      LOG_PRINT(LOG_CRITICAL,"Internal CS Neighbor Cell's MNC and MCC not present in BSS table");
		      free(csNeighCells); free(cellTable); 
					free(cellPerTableApiPtr);
					return FALSE;
																																																												             } /* End of check for MNC and MCC */
		  } /* End of getCellTable */
			else
			{
																																																												            /* Internal CS Neighbor Cell for the cell not present in Cell table */
			    LOG_PRINT(LOG_CRITICAL,"Internal CS Neighbor Cell for the cell not present in Cell table");
      		free(cellPerTableApiPtr);
					return FALSE;
			}
     } /* End of for loop for count of Internal CS Neighbor Cells */
    free(csNeighCells);
    free(cellTable);
  } /* End if condition for getCsInternalNeighCellsForCell */
} /* End of for loop to check neighbour cell info */
		/*Mantis 12446 End 8th June 2010*/
      free(cellPerTableApiPtr);
   }
   else
   {
      LOG_PRINT(LOG_INFO,"Get on CellPerTable Fail");   
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : isCgiUnqInBss");
   return TRUE;
}

/********************************* Function  Header*****************************
Function Name   : fillAndSendOamsCfgOilBssResetReq()
Parameters      : slotId
Return type     : none
Purpose         : 
Other Note      : 
 *******************************************************************************/
I_Void fillAndSendOamsCfgOilBssResetReq(I_U8 frameId, I_U8 slotId)
{
  OamsCfgOilBssResetReq OamsCfgOilBssResetReqBuf = {0};

  LOG_PRINT(LOG_INFO,"%s: Entering",__func__);
  
  //Payload
  OamsCfgOilBssResetReqBuf.frameId          = frameId;
  OamsCfgOilBssResetReqBuf.slotId           = slotId;
  OamsCfgOilBssResetReqBuf.systemResetFlag  = BPM_FALSE;
  OamsCfgOilBssResetReqBuf.setCardState     = CARDSTATE_OUT_OF_SERVICE;

  cfgSendMessage((void *)&OamsCfgOilBssResetReqBuf, 
               sizeof(OamsCfgOilBssResetReqBuf), ENT_OAM_OIL, 
               OAMS_CFG_OIL_BSS_RESET_REQ, 0); 
  LOG_PRINT(LOG_INFO,"%s: Exit",__func__);
}

/********************************* Function  Header*****************************
Function Name   : fillAndSendOamsCfgOilBssShutdownReq()
Parameters      : frameId, slotId
Return type     : none
Purpose         : 
Other Note      : 
 *******************************************************************************/
I_Void fillAndSendOamsCfgOilBssShutdownReq(I_U8 frameId, I_U8 slotId)
{
  OamsCfgOilBssShutdownReq OamsCfgOilBssShutdownReqBuf = {0};

  LOG_PRINT(LOG_INFO,"%s: Entering",__func__);
  
  //Payload
  OamsCfgOilBssShutdownReqBuf.frameId          = frameId;
  OamsCfgOilBssShutdownReqBuf.slotId           = slotId;
  OamsCfgOilBssShutdownReqBuf.systemShutDownFlag = BPM_FALSE;

  cfgSendMessage((void *)&OamsCfgOilBssShutdownReqBuf, 
               sizeof(OamsCfgOilBssShutdownReqBuf), ENT_OAM_OIL, 
               OAMS_CFG_OIL_BSS_SHUTDOWN_REQ, 0); 
  LOG_PRINT(LOG_INFO,"%s: Exit",__func__);
}

/********************************* Function  Header*****************************
Function Name   : bssResetReqHandler()
Parameters      : Bss Reset Command ( ACTIVE_ICC_CARD_RESET_CMD/STANDBY_ICC_CARD_RESET_CMD)
Return type     : none
Purpose         : Handle the request of BSS Reset from Operator
Other Note      : Support for BssReset from the operator, 12-06-09::09:59, BB
 *******************************************************************************/
I_Void bssResetReqHandler(eBssResetCommand BssResetCommand)
{
   IccCardInfoTableApi *IccCardInfoTableApiDbPtr  = NULL;
   IccCardInfoTableApi *IccCardInfoTableApiTmpPtr = NULL;
   I_U16                rowSize        = ZERO;
   I_U32                rowCount       = ZERO;
   I_U32                i              = ZERO;
   I_S32 ret = 0;
   
   LOG_PRINT(LOG_INFO,"%s: Entering",__func__);

   ret = isActivationInProgressForBscEicDsp();
   if ( ret == I_TRUE )
   {
      LOG_PRINT(LOG_DEBUG,"Activation is in progress for BSC or EIC or DSP or other");
      cfgSendNackToCm(CM_ERR_SW_ACT_IN_PROGRESS);
      return;
   }

   if ( getallIccCardInfoTable(&IccCardInfoTableApiDbPtr, &rowCount, &rowSize) == DBLIB_SUCCESS) {
     for (i=ZERO; i < rowCount; i++) {
       IccCardInfoTableApiTmpPtr = (IccCardInfoTableApi *)(((I_U8 *)IccCardInfoTableApiDbPtr) + i * rowSize);
       switch (IccCardInfoTableApiTmpPtr->cardOperationalState) {
         case CARDSTATE_ACTIVE :
           if (BssResetCommand == ACTIVE_ICC_CARD_RESET_CMD) {
             fillAndSendOamsCfgOilBssResetReq(IccCardInfoTableApiTmpPtr->chasisFrameId,
                                              IccCardInfoTableApiTmpPtr->slotId);
             LOG_PRINT(LOG_INFO,
                       "BssReset rcvd for ACTIVE_CARD frameId[%u] slotId[%u]",
                       IccCardInfoTableApiTmpPtr->chasisFrameId,
                       IccCardInfoTableApiTmpPtr->slotId
                       );
           }
           if (BssResetCommand == ACTIVE_ICC_CARD_SHUTDOWN_CMD)
             {
            fillAndSendOamsCfgOilBssShutdownReq(IccCardInfoTableApiTmpPtr->chasisFrameId,
                                                IccCardInfoTableApiTmpPtr->slotId);
             LOG_PRINT(LOG_INFO,
                       "Bss Shutdown rcvd for ACTIVE_CARD frameId[%u] slotId[%u]",
                       IccCardInfoTableApiTmpPtr->chasisFrameId,
                       IccCardInfoTableApiTmpPtr->slotId
                       ); 
             }
//           free(IccCardInfoTableApiDbPtr);
           break;
         case CARDSTATE_STANDBY:
           if (BssResetCommand == STANDBY_ICC_CARD_RESET_CMD) {
             fillAndSendOamsCfgOilBssResetReq(IccCardInfoTableApiTmpPtr->chasisFrameId,
                                              IccCardInfoTableApiTmpPtr->slotId);
             LOG_PRINT(LOG_INFO,
                       "BssReset rcvd for STANDBY_CARD frameId[%u] slotId[%u]",
                       IccCardInfoTableApiTmpPtr->chasisFrameId,
                       IccCardInfoTableApiTmpPtr->slotId
                       );                                              
           }
           if ( BssResetCommand == STANDBY_ICC_CARD_SHUTDOWN_CMD)
             {
            fillAndSendOamsCfgOilBssShutdownReq(IccCardInfoTableApiTmpPtr->chasisFrameId,
                                                IccCardInfoTableApiTmpPtr->slotId);
             LOG_PRINT(LOG_INFO,
                       "Bss Shutdown rcvd for STANDBY_CARD frameId[%u] slotId[%u]",
                       IccCardInfoTableApiTmpPtr->chasisFrameId,
                       IccCardInfoTableApiTmpPtr->slotId
                       ); 
             }
//           free(IccCardInfoTableApiDbPtr);
           break;
 
           case CARDSTATE_ABSENT :
            if(  (BssResetCommand == STANDBY_ICC_CARD_RESET_CMD) ||
                ( BssResetCommand == STANDBY_ICC_CARD_SHUTDOWN_CMD) )
            {
               LOG_PRINT(DEBUG,"Discarding Request as peer card is not present");
               cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
            } 
           break; 

           default :
               LOG_PRINT(DEBUG,"Error: Invalid Card State"); 
               cfgSendNackToCm(CM_ERR_INVALID_CARD_STATE);
           break; 
       }
     }
     free(IccCardInfoTableApiDbPtr);
   }
   else
   {
   	LOG_PRINT(LOG_CRITICAL,"%s: No IccCard Details present in DB",__func__);
   }
   LOG_PRINT(LOG_INFO,"%s: Exit",__func__);
}


/********************************* Function  Header*****************************
Function Name   : checkAndSendLinkDeactivationRequest()
Parameters      : none 
Return type     : none
Purpose         : Performs Link deactivation on all links which are unlocked.
Other Note      : Fix for Mantis 8161, by Rama Prasad 
 *******************************************************************************/


I_Bool checkAndSendLinkDeactivationRequest()
{
   I_U32 outRows=0;
   I_U16 outSize=0;
   LinkTableApi       *linkPtr=NULL;
   LinkTableApi       *tmpLinkPtr=NULL;
   I_U32 cardOprState = 0;
   I_S32 retVal = FALSE;
   /*IP_BSC_STACK*/
   SigtranM3uaLAspConfigTableApi* sigtranM3uaLAspConfigTableApi = NULL,*tmpSigtranM3uaLAspConfigTableApi=NULL;
   /*I_U8 slotId;
   I_U8 chasisFrameId;*/
   /*IP_BSC_STACK*/
   
   LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:checkAndSendLinkDeactivationRequest: Entering into function");
   if (gStackStatus != SS7_STACK_UP) {
      LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK:checkAndSendLinkDeactivationRequest:Request cannot be send to SCM as Ss7 Stack status is Down");
      return retVal;
   }
   
   /*if (getallLinkTable(&linkPtr,&outRows,&outSize) != CLIB_SUCCESS) {
      LOG_PRINT(LOG_INFO, "checkAndSendLinkDeactivationRequest : read getallLinkTable() Failed");
      return retVal;
   }*/
      
  if(CLIB_SUCCESS != getallSigtranM3uaLAspConfigTable(&sigtranM3uaLAspConfigTableApi,&outRows,&outSize))
  {
      LOG_PRINT(LOG_INFO, "IP_BSC_STACK: read getallSigtranM3uaLAspConfigTable() Failed");
      return retVal;
  }
      /*Following section changed for IP_BSC_STACK 18 July 2016 Gaurav Sinha*/
   /*retVal = getActiveIccSlotId( &chasisFrameId, &slotId); CHECK FISRT IP_BSC_STACK: 
   if ( CLIB_SUCCESS != retVal)
   {
      LOG_PRINT(LOG_INFO,"IP_BSC_STACK: getActiveIccSlotId Db call failed ErrorCause: %d",retVal);
      return retVal;
   }
   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: getActiveIccSlotId Db call returned: SlotId[%d] ChasisFrameId[%d]",slotId,chasisFrameId);
   slotId = slotId-2;//Cloud Specific Change
   LOG_PRINT(LOG_INFO,"IP_BSC_STACK: After deduction SlotId [%d] ",slotId);*/
   //LOG_PRINT(LOG_INFO, "checkAndSendLinkDeactivationRequest: Total Num of Configured Links = %u", outRows);
   LOG_PRINT(LOG_INFO, "IP_BSC_STACK :checkAndSendLinkDeactivationRequest: Total Num of Configured ASP in SigtranM3uaLAspConfigTable = %u", outRows);
   while (gLinkLockMsgSentForBss < outRows) {
     tmpSigtranM3uaLAspConfigTableApi = (SigtranM3uaLAspConfigTableApi *)((I_U8*)sigtranM3uaLAspConfigTableApi + (gLinkLockMsgSentForBss * outSize));
     gLinkLockMsgSentForBss++;
     //If the card is not present then try for the next entry
     if (getStateForSlotIdIccTable((tmpSigtranM3uaLAspConfigTableApi->slotId+2),&cardOprState) != CLIB_SUCCESS) {
        LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: checkAndSendLinkDeactivationRequest: Received slotId[%d] does not exists in iccCardInfo Table",(tmpSigtranM3uaLAspConfigTableApi->slotId));
        //if(tmpSigtranM3uaLAspConfigTableApi->slotId != slotId) CHECK FISRT IP_BSC_STACK:
         continue;
        }  
     #if 0
     //mantis 9108 start
     if (cardOprState == CARDSTATE_ACTIVE) 
				 gReqSentToScm=1;
				 LOG_PRINT(LOG_INFO, "checkAndSendLinkDeactivationRequest: gReqSentToSCM= %d", gReqSentToScm);

	  //Mantis 9108 end
    #endif
				/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
        //if ( (tmpLinkPtr->adminState == UNLOCKED) && 
        //     (gE1Data[tmpLinkPtr->e1Num].e1State == unlocked)) 
				/*Changed for sending Lock_unlock to SCM for  SSA // SSP handling for CLOUD-BSC 11 Jan 2016 Gaurav Sinha*/
        //if(tmpLinkPtr->adminState == UNLOCKED) 
        if (tmpSigtranM3uaLAspConfigTableApi->adminState == UNLOCKED)  
        {
            /*OamScmLinkAdminState linkConfig;
            linkConfig.linkId = tmpLinkPtr->linkId;
            linkConfig.linkSetId = tmpLinkPtr->linksetID;
            linkConfig.adminState = LOCKED;*/
            OamScmM3uaLocalAspAdminConfig m3uaLocalAspAdminConfig;
            m3uaLocalAspAdminConfig.localAspId = tmpSigtranM3uaLAspConfigTableApi->localAspId; 
            m3uaLocalAspAdminConfig.adminState = LOCKED; 
            setStackObject(BSC_API_SET_BSSTABLE, SCM_MODIFY, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG);
            if (cfgSendStackMessage((I_Void *)&m3uaLocalAspAdminConfig, sizeof(OamScmM3uaLocalAspAdminConfig)) == CFG_SUCCESS) 
            {
               LOG_PRINT(LOG_INFO,"IP_BSC_STACK: checkAndSendLinkDeactivationRequest: Sending OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG ASPID[%u] to Oil..",tmpSigtranM3uaLAspConfigTableApi->localAspId);
				       gReqSentToScm=1;
               retVal = TRUE;
            }
        }
     /*else {
        LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: checkAndSendLinkDeactivationRequest: Not sending Link Activation Request as Link[%u] not for active card",
                  tmpLinkPtr->linkId);
     }*/
     //If link de-activation request is sent then return ;
     if (retVal) {
       break;
     }
   }   
   free(sigtranM3uaLAspConfigTableApi);
   LOG_PRINT(LOG_DEBUG,"IP_BSC_STACK: checkAndSendLinkDeactivationRequest: Exiting into function");
   return retVal;
}

/*Changes for R2.3.4 starts*/
/********************************* Function  Header*****************************
Function Name   : fillMtp2TimerInfo()
Parameters      : Mtp2TimerConfig * , I_U32 satFlag 
Return type     : SUCC = I_TRUE/ FAIL= I_FALSE 
Purpose         : To fill mtp2Timer info in OamScmlinkAdminState message
Note            : Added for R2.3.4  
 *******************************************************************************/
I_U8 fillMtp2TimerInfo(I_Void * buffPtr, I_U32 satFlag)
{
   Mtp2TimerTableIndices mtp2TimerTblIndex;
   Mtp2TimerTableApi *outData;

   Mtp2TimerConfig * mtp2TimerConfigPtr = (Mtp2TimerConfig *)buffPtr;

   LOG_PRINT(LOG_DEBUG,"fillMtp2TimerInfo: Entering into function");
  
   mtp2TimerTblIndex.satFlag = (I_U16)satFlag;
  
   if(getMtp2TimerTable(&mtp2TimerTblIndex,&outData) != CLIB_SUCCESS) 
   {
       LOG_PRINT(MAJOR,"getMtp2TimerTable failed for satFlag=%d",mtp2TimerTblIndex.satFlag);
       return I_FALSE; 
   } 
   mtp2TimerConfigPtr->mtp2TimerT1 = outData->timerT1;
   mtp2TimerConfigPtr->mtp2TimerT2 = outData->timerT2;
   mtp2TimerConfigPtr->mtp2TimerT3 = outData->timerT3;
   mtp2TimerConfigPtr->mtp2TimerT4 = outData->timerT4;
   mtp2TimerConfigPtr->mtp2TimerT5 = outData->timerT5;
   mtp2TimerConfigPtr->mtp2TimerT6 = outData->timerT6;
   mtp2TimerConfigPtr->mtp2TimerT7 = outData->timerT7;
   mtp2TimerConfigPtr->mtp2EmrgncyProvngPriod = outData->emergencyProvingPeriod;
   mtp2TimerConfigPtr->mtp2NormalProvngPriod = outData->normalProvingPeriod;
   mtp2TimerConfigPtr->mtp2PCRFlag = outData->pcrFlag;
   mtp2TimerConfigPtr->mtp2RcvOnset = outData->rcOnset;
   mtp2TimerConfigPtr->mtp2RcvAbates = outData->rcAbates;
   mtp2TimerConfigPtr->mtp2TxOnset1 = outData->txOnset1;
   mtp2TimerConfigPtr->mtp2TxOnset2 = outData->txOnset2;
   mtp2TimerConfigPtr->mtp2TxOnset3 = outData->txOnset3;
   mtp2TimerConfigPtr->mtp2TxAbetes1 = outData->txAbates1;
   mtp2TimerConfigPtr->mtp2TxAbetes2 = outData->txAbates2;
   mtp2TimerConfigPtr->mtp2TxAbetes3 = outData->txAbates3;
 
   free(outData);
   LOG_PRINT(LOG_DEBUG,"fillMtp2TimerInfo: Exiting from function");
   return I_TRUE;  
}


/********************************* Function  Header*****************************
Function Name   : bssObjectSendLapdTimerConfigToScm()
Parameters      : 
Return type     : SUCC = I_TRUE/ FAIL= I_FALSE 
Purpose         : To send lapdTimerConfig request to SCM an system startup
Note            : Added for R2.3.4  
*******************************************************************************/
I_U8 bssObjectSendLapdTimerConfigToScm()
{
   I_U32 outRows=0,outRows1=0,outRows2=0,size1 =0,numTs=0,sndSz=0,outRows_bic=0;
   I_U16 outSize=0,outSize1=0,outSize2=0,outSize_bic=0;
   I_S32 retVal=0,i=0,retVal1=0;
   OamScmLapdTimerConfig *scmLapdConfigPtr = NULL;
   BicTableIndices bicTblIndex;
   BicTableApi * bicTblPtr;
   LapdTsDetail *tmpLapdTsDetail;
   LapdTsDetail *lapdTsDetailPtr;
   BicTrxTimeslotUsageTableApi *bicTrxTimeslotUsageTablePtr = NULL;
   BicTrxTimeslotUsageTableApi *bicTrxTimeslotUsageTablePtr_bic = NULL;
   BicTrxTimeslotUsageTableApi *tempBicTrxTimeslotUsageTablePtr = NULL;
   LapdTimerTableApi *lapdTimerTblPtr;
   LapdTimerTableApi *tmpLapdTimerTblPtr;
   MccLinkResourceTableApi *mccLinkResourcePtr = NULL;
   E1StreamMapTableIndices e1StreamMapTblIndx;
   E1StreamMapTableApi *e1StreamTblPtr = NULL;

   LOG_PRINT(DEBUG,"bssObjectSendLapdTimerConfigToScm: Entering in function");

   if (gStackStatus != SS7_STACK_UP) {
      LOG_PRINT(LOG_DEBUG,"bssObjectSendLapdTimerConfigToScm: Request cannot be send to SCM as Ss7 Stack status is Down");
      return I_FALSE;
   }

   retVal = getTerBicTrxTimeslotUsageTable(TS_USAGE_BTS,&bicTrxTimeslotUsageTablePtr,&outRows,&outSize);
   if(retVal != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO, "bssObjectSendLapdTimerConfigToScm: read getTerBicTrxTimeslotUsageTable() for BTS Failed:%d",retVal);
     // return I_FALSE;
   }
  
   retVal1 = getTerBicTrxTimeslotUsageTable(SYS_NODE_TYPE_BIC,&bicTrxTimeslotUsageTablePtr_bic,&outRows_bic,&outSize_bic);
   if(retVal1 != CLIB_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO, "bssObjectSendLapdTimerConfigToScm: read getTerBicTrxTimeslotUsageTable() for BIC Failed:%d",retVal1);
      //free(bicTrxTimeslotUsageTablePtr); 
      //return I_FALSE;
   }
  
   if((retVal != CLIB_SUCCESS) &&
       (retVal1 != CLIB_SUCCESS) )
   {
      LOG_PRINT(DEBUG,"getBicTrxTimeSlotUsage Table failed both for bic and bts");
      return I_FALSE;
   }
   
   size1 = sizeof(OamScmLapdTimerConfig);
   if(retVal == CLIB_SUCCESS)
   {
      size1 +=  (outRows - 1)*sizeof(LapdTsDetail) ;
   }
   if(retVal1 == CLIB_SUCCESS)
   {
      size1 +=  outRows_bic *sizeof(LapdTsDetail) ;
   }

   scmLapdConfigPtr = (OamScmLapdTimerConfig *)AlocOrdBuf(size1);
   if(scmLapdConfigPtr == NULL)
   {
      LOG_PRINT(MAJOR,"AlocOrdBuf failed for size:%d",size1);
      free(bicTrxTimeslotUsageTablePtr_bic); 
      free(bicTrxTimeslotUsageTablePtr); 
      return I_FALSE;
   }   

   if(getallLapdTimerTable(&lapdTimerTblPtr,&outRows1,&outSize1) != CLIB_SUCCESS)
   {
       LOG_PRINT(MAJOR,"getallLapdTimerTable failed");
       free(bicTrxTimeslotUsageTablePtr_bic); 
       free(bicTrxTimeslotUsageTablePtr); 
       DalocOrdBuf(scmLapdConfigPtr);
       return I_FALSE;
   }
   if(outRows1 != 2)
   {
       LOG_PRINT(MAJOR,"getallLapdTimerTable failed as outrows:%d",outRows1);
       free(bicTrxTimeslotUsageTablePtr_bic); 
       free(bicTrxTimeslotUsageTablePtr); 
       DalocOrdBuf(scmLapdConfigPtr);
       return I_FALSE;
   }
   
   for(i=0;i<outRows1;i++)
   {
      tmpLapdTimerTblPtr = (LapdTimerTableApi *)((I_U8 *)lapdTimerTblPtr + i * outSize1 );
      if(tmpLapdTimerTblPtr->satFlag == I_TRUE )
      {
          scmLapdConfigPtr->lapdTimerSatellite.lapdTimerT200 = tmpLapdTimerTblPtr->lapdTimerT200; 
          scmLapdConfigPtr->lapdTimerSatellite.lapdTimerT203 = tmpLapdTimerTblPtr->lapdTimerT203; 
          scmLapdConfigPtr->lapdTimerSatellite.N200 = tmpLapdTimerTblPtr->lapdTimerN200; 
      }
      else
      {
          scmLapdConfigPtr->lapdTimerDefault.lapdTimerT200 = tmpLapdTimerTblPtr->lapdTimerT200; 
          scmLapdConfigPtr->lapdTimerDefault.lapdTimerT203 = tmpLapdTimerTblPtr->lapdTimerT203; 
          scmLapdConfigPtr->lapdTimerDefault.N200 = tmpLapdTimerTblPtr->lapdTimerN200; 
      }
   }
   free(lapdTimerTblPtr);

   lapdTsDetailPtr = scmLapdConfigPtr->lpdTsdetail;

   if(retVal == CLIB_SUCCESS)
   {
      for(numTs=0,i=0;i<outRows;i++)
      {
         tempBicTrxTimeslotUsageTablePtr = (BicTrxTimeslotUsageTableApi *)( (I_U8 *)bicTrxTimeslotUsageTablePtr +i* outSize);
         bicTblIndex.bicId = tempBicTrxTimeslotUsageTablePtr->bicOrTrxId; 
         if(getBicTable(&bicTblIndex,&bicTblPtr) != CLIB_SUCCESS)
         {
             LOG_PRINT(DEBUG,"getBicTable failed gor bicId:%d",bicTblIndex.bicId); 
             continue;
         } 
         tmpLapdTsDetail = ((I_U8 *)lapdTsDetailPtr + (numTs)*sizeof(LapdTsDetail));  
         tmpLapdTsDetail->satFlag = (I_U8)bicTblPtr->satFlag; 
         free(bicTblPtr);
         if(getMccTrunkNumTsUsingExtTrunkNumTs(tempBicTrxTimeslotUsageTablePtr->e1Id,
             tempBicTrxTimeslotUsageTablePtr->lapdTs,&mccLinkResourcePtr,&outRows2,&outSize2)
            != CLIB_SUCCESS)   
         {
            LOG_PRINT(DEBUG,"getMccTrunkNumTsUsingExtTrunkNumTs failed for e1Id:%d timeslot:%d",
                tempBicTrxTimeslotUsageTablePtr->e1Id,tempBicTrxTimeslotUsageTablePtr->lapdTs); 
            continue;
         }  
         e1StreamMapTblIndx.e1Num = mccLinkResourcePtr->mccTrunkNum;
         e1StreamMapTblIndx.e1Ts = mccLinkResourcePtr->mccTrunkTs;
         free(mccLinkResourcePtr); 
         if(getE1StreamMapTable(&e1StreamMapTblIndx,&e1StreamTblPtr) != CLIB_SUCCESS)
         {
            LOG_PRINT(DEBUG,"getE1StreamMapTable failed for MccE1:%d MccTs:%d",
               e1StreamMapTblIndx.e1Num,e1StreamMapTblIndx.e1Ts); 
            continue;
         }
         tmpLapdTsDetail->ts = e1StreamTblPtr->strmTs;  
         free(e1StreamTblPtr);
         numTs++;
      }//for loop
   }
   
   if(retVal1 == CLIB_SUCCESS) 
   { 
      for(i=0;i<outRows_bic;i++)
      {
         tempBicTrxTimeslotUsageTablePtr = (BicTrxTimeslotUsageTableApi *)( (I_U8 *)bicTrxTimeslotUsageTablePtr_bic +i* outSize_bic);
         bicTblIndex.bicId = tempBicTrxTimeslotUsageTablePtr->bicOrTrxId; 
         if(getBicTable(&bicTblIndex,&bicTblPtr) != CLIB_SUCCESS)
         {
             LOG_PRINT(DEBUG,"getBicTable failed gor bicId:%d",bicTblIndex.bicId); 
             continue;
         } 
         tmpLapdTsDetail = ((I_U8 *)lapdTsDetailPtr + (numTs)*sizeof(LapdTsDetail));  
         tmpLapdTsDetail->satFlag = (I_U8)bicTblPtr->satFlag; 
         free(bicTblPtr);
         if(getMccTrunkNumTsUsingExtTrunkNumTs(tempBicTrxTimeslotUsageTablePtr->e1Id,
             tempBicTrxTimeslotUsageTablePtr->lapdTs,&mccLinkResourcePtr,&outRows2,&outSize2)
            != CLIB_SUCCESS)   
         {
            LOG_PRINT(DEBUG,"getMccTrunkNumTsUsingExtTrunkNumTs failed for e1Id:%d timeslot:%d",
                tempBicTrxTimeslotUsageTablePtr->e1Id,tempBicTrxTimeslotUsageTablePtr->lapdTs); 
            continue;
         }  
         e1StreamMapTblIndx.e1Num = mccLinkResourcePtr->mccTrunkNum;
         e1StreamMapTblIndx.e1Ts = mccLinkResourcePtr->mccTrunkTs;
         free(mccLinkResourcePtr); 
         if(getE1StreamMapTable(&e1StreamMapTblIndx,&e1StreamTblPtr) != CLIB_SUCCESS)
         {
            LOG_PRINT(DEBUG,"getE1StreamMapTable failed for MccE1:%d MccTs:%d",
               e1StreamMapTblIndx.e1Num,e1StreamMapTblIndx.e1Ts); 
            continue;
         }
         tmpLapdTsDetail->ts = e1StreamTblPtr->strmTs;  
         free(e1StreamTblPtr);
         numTs++;
      }  
   }
    
   if(bicTrxTimeslotUsageTablePtr != NULL) 
   {
      free(bicTrxTimeslotUsageTablePtr);
   }
   if(bicTrxTimeslotUsageTablePtr_bic != NULL) 
   {
      free(bicTrxTimeslotUsageTablePtr_bic);
   }
   
   if(numTs == 0)
   {
      LOG_PRINT(DEBUG,"No Bic configured and hence no lapdtimer modification required");
      DalocOrdBuf(scmLapdConfigPtr);
      return I_FALSE;
   }

   scmLapdConfigPtr->noOfLapdTs = numTs;
   setStackObject(BSC_API_SET_BSSTABLE, SCM_MODIFY, OAM_SCM_LAPDTIMER_CONFIG);
   sndSz =  sizeof(OamScmLapdTimerConfig) + (numTs - 1) * sizeof(LapdTsDetail);
   if (cfgSendStackMessage((I_Void *)scmLapdConfigPtr, sndSz ) == CFG_SUCCESS) 
   {
      LOG_PRINT(LOG_INFO,"bssObjectSendLapdTimerConfigToScm: Sending OAM_SCM_LAPDTIMER_CONFIG for numTs[%u] to Oil..",
              scmLapdConfigPtr->noOfLapdTs);
      gReqSentToScm =1;
   }
   DalocOrdBuf(scmLapdConfigPtr);
   LOG_PRINT(DEBUG,"bssObjectSendLapdTimerConfigToScm: Exiting from function");
   return I_TRUE; 
}
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
void initiateSwitchoverProcForCloudBscStack()
{
  LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::inside initiateSwitchoverProcForCloudBscStack()");
	AifInterfaceTableApi  *aifInterfaceTableDbPtr = NULL;
  AifInterfaceTableIndices aifInterfaceTableIndex;
  aifInterfaceTableIndex.interfaceId = 1;
  I_S32 retValue = CM_FAILURE;

  /* Check whether row exist in AifInterface Table */
  if(CLIB_SUCCESS != getAifInterfaceTable(&aifInterfaceTableIndex, &aifInterfaceTableDbPtr))
  {
  		LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA:: AifInterface Table does not exists something has gone wrong");
     return;
  }
  if (aifInterfaceTableDbPtr->operationalState == 1)
	{
  		LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA:: Aif was Enabled at previous card going to disable it");
			gSSAReceived = FALSE; 
			/*LINK_TABLE & LINK_SET_TABLE status to be marked as disabled in this case*/
			LOG_PRINT(DEBUG,"CLOUD-BSC-HA::GOING to update LinkSetStatusTable as DISABLED in DATABASE");
      updateOrInsertLinkSetStatusTable(((I_U16)1),DISABLED);
      LOG_PRINT(DEBUG,"CLOUD-BSC-HA::GOING to update LinkStatusTable as DISABLED in DATABASE");
      updateOrInsertLinkStatusTable(((I_U16)1),((I_U16)1),DISABLED);
			/*LINK_TABLE & LINK_SET_TABLE status to be marked as disabled in this case*/
			/*SENDING SSP ALARM TO OMC*/
      LOG_PRINT(DEBUG,"CLOUD-BSC-HA::GOING to send SSP_MSG_RECV_REM_SUBSYSTEM Alarm to OMC");
      OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = SSP_MSG_RECV_REM_SUBSYSTEM;
      OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
      OamsCfgAfhSysAlarmBuff.sysAlarm.alarmReason = SKS_TRAP_EVENT_TYPE_NWSTACK;
			OamsCfgAfhSysAlarmBuff.sysAlarm.info1 = ENT_SKS_NWSTK;
      //OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSS;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = aifInterfaceTableDbPtr->dpc; //MSC_POINT_CODE
      OamsCfgAfhSysAlarmBuff.sysAlarm.key2 = 254;//always the same
			OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Subsystem Prohibited (SSP) message received from remote subsystem: PC %08x SSN %02d.",OamsCfgAfhSysAlarmBuff.sysAlarm.key1,OamsCfgAfhSysAlarmBuff.sysAlarm.key2);
       retValue = cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
			 if (retValue == CFG_FAILURE)
				{
				 	LOG_PRINT(LOG_CRITICAL,"CLOUD-BSC-HA::SSP_MSG_RECV_REM_SUBSYSTEM  :OAMS_CFG_AFH_ALARM_IND send Failed");
				}/*End of if*/
				if (retValue == CFG_SUCCESS)
				{
				 	LOG_PRINT(LOG_INFO,"CLOUD-BSC-HA::SSP_MSG_RECV_REM_SUBSYSTEM :OAMS_CFG_AFH_ALARM_IND  send Success");
				} /*End of if*/

			/*SENDING SSP ALARM TO OMC*/
			setAinterfaceTableOperationalState(DISABLED);
			/* Send OAMS_CFG_GRHM_LOCK_REQ */
			OamsCfgGrhmLockReq OamCfgGrhmLockReqBuff;
			/************* fix for mantis-1797 ***********************/
			memset(&OamCfgGrhmLockReqBuff,0,sizeof(OamsCfgGrhmLockReq));
			/**********************************************************/
			OamCfgGrhmLockReqBuff.objectId=0;
			OamCfgGrhmLockReqBuff.objType = OAMS_OBJTYPE_AINTERFACE;
			/************ SPR # 206 Start *****************/
			OamCfgGrhmLockReqBuff.reason = OAMS_RSN_AINTERFACEDOWN;  
			/************ SPR # 206 End *****************/
			cfgSendMessage((void *)&OamCfgGrhmLockReqBuff, sizeof(OamsCfgGrhmLockReq), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_LOCK_REQ, 0);
			gAifMsgSentToGrhm = OAMS_CFG_GRHM_LOCK_REQ;
	}
	else
	{
    LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::Aif was not up at previous ACT card now checking Bss & Link are Unlock");
	}
	if(aifInterfaceTableDbPtr!=NULL)
	{
		free(aifInterfaceTableDbPtr);
	}
	/*Now checking if BssAdmin State & link Admin State is unlocked... If matched SCM_UNLOCK will be sent again*/
	/////////////////////
	BssTableApi * bssTableApiDbPtr;
	BssTableIndices BssTableIndicesBuff;
	LinkTableApi  *linkTableDbPtr = NULL;
	LinkTableIndices linkTableIndex;
	BssTableIndicesBuff.bscId = 1;
	retValue = getBssTable(&BssTableIndicesBuff,&bssTableApiDbPtr);
  LOG_PRINT(LOG_DEBUG,"retValue=%d",retValue);
  if ( retValue == CLIB_SUCCESS )
  {
		linkTableIndex.linksetID = 1;
  	linkTableIndex.linkId = 1;
   if(CLIB_SUCCESS == getLinkTable(&linkTableIndex, &linkTableDbPtr))
   {
      LOG_PRINT(LOG_INFO, "Row exists in Link Table");
			if((bssTableApiDbPtr->adminState == 1) && (linkTableDbPtr->adminState ==1))
			{
  				LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::Both BSS & link are unlocked initiating Link Unlock Req Again");
					/* Set Stack object data structure */
					/*Mantis #31318 1U BSC VAlidation Gaurav Sinha 02 June 2016*/
  				LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::going to sleep for 5 secs");
					PRIVATE struct timeval timeout;
				  timeout.tv_sec = 5; timeout.tv_usec = 0; /*5 s*/          
					 while(timeout.tv_sec !=0  || timeout.tv_usec != 0)
					select(0, 0, 0, 0, &timeout);	
  				LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::CFG woke up after 5 secs");
					/*Mantis #31318 1U BSC VAlidation Gaurav Sinha 02 June 2016*/
      		setStackObject(BSC_API_SET_LINKTABLE, SCM_UNLOCK, OAM_SCM_LINK_ADMIN_CONFIG);
      		gE1TimeslotData[1][1].e1TimeslotState = unlockInProgress;
      		//LOG_PRINT(LOG_INFO,"Moving to Unlock-In-Progress State");
			 		/* Frame and Send the message to the OIL */
   				OamScmLinkAdminState linkConfig;
   				linkConfig.linkId = 1;
   				linkConfig.linkSetId = 1;
   				linkConfig.adminState = 1;
   				/*Changes for R2.3.4 Starts*/
      			if(fillMtp2TimerInfo(&(linkConfig.mtp2TimerConfig),1) != I_TRUE)
      			{
         			LOG_PRINT(DEBUG,"fillMtp2TimerInfo failed");
         			gE1TimeslotData[1][1].e1TimeslotState = locked;
         			return;
   					}
					 /*Changes for R2.3.4 Ends*/

					 gMsgSentForE1TSNum = 1;
					 gMsgSentForE1TSNum = ((1 << 16)| gMsgSentForE1TSNum);

					 LOG_PRINT(LOG_INFO,"CLOUD-BSC-HA::Sending OAM_SCM_LINK_ADMIN_CONFIG to Oil..");
					 if (cfgSendStackMessage((I_Void *)&linkConfig, sizeof(linkConfig)) != CFG_SUCCESS)
					 {
					 		LOG_PRINT(LOG_INFO,"CLOUD-BSC-HA:: Unable to send OAM_SCM_LINK_ADMIN_CONFIG to Oil..");
							return;
					 }
			}
			else
			{
  				LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::Either BSS or Link is LOCKED Link Unlock Req Can't be sent Again");
			}
   }
   else
   {
     LOG_PRINT(LOG_MAJOR,"Received Link does not exists in DB");
   }
		if(bssTableApiDbPtr!=NULL)
		{
			free(bssTableApiDbPtr);
		}
		if(linkTableDbPtr!=NULL)
		{
			free(linkTableDbPtr);
		}
  }
  else
  {
  	LOG_PRINT(LOG_INFO,"Db call getBssTable failed returned Error Code = [%d] ", retValue);
  	LOG_PRINT(LOG_DEBUG,"CLOUD-BSC-HA::Link Unlock Req Can't be sent Again");
		return;
  	//cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
  }

}
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
/*Changes for R2.3.4 Ends*/
/********************************* Change History ***************************
  Release     Patch       Author         Description
  CS2                     Pratibha       Enum Removal Change

 ************************************** End *********************************/

