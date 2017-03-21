/***********************************File Header ***************************
   File Name        : oamscfg_cell_object_handler.c
Purpose          : This file contains CFG Cell Handler implementation
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#include <oamscfg_includes.h>

I_U8 cellIndex;
ApplTimer *applTimer=NULL;
void cellObjectHandler(){

   /*   CellDataStruct cellDataStructbuff={0}; */
   I_U8 index = 0;
   LOG_PRINT(LOG_INFO,"Entering cellObjectHandler()");

   index = getCellDataState();

   if(index == 255)
   {
      LOG_PRINT(CRITICAL,"gCellData initialized incorrectly"); 
      return; 
   }

   switch (gCellData[index].CellState)
   {
      case locked:
         cellObjectLockedHandler();
         break;
      case unlockOrEnableInProgress:   
         cellObjectUnlockOrEnableInProgressHandler();
         break;
      case unlockedEnabled:
         cellObjectUnlockedEnabledHandler();
         break;
      case unlockedDisabled:
         cellObjectUnlockedDisabledHandler();
         break;
      case lockeOrDisableInProgress:   
         cellObjectLockOrDisableInProgressHandler();
         break;
      case blockInProgress:
         cellObjectBlockInProgressHandler();
         break;
      default:
         break;
   }

   LOG_PRINT(LOG_INFO,"Exiting cellObjectHandler()");

}

void cellObjectLockedHandler()
{
   I_S32 ret = CM_FAILURE;
   CellPerTableApi *cellTablePtr = PNULL;
   CellPerTableIndices CellPerTableIndices;
   CellPerTableApi *cellTable = PNULL;
   OamsCellhCfgAlarmInd oamsCellhCfgAlarmIndBuff;
   CellNonPerTableApi cellNonPerBuff;
   I_U32 count =0,k=0;
   I_U32 btsRfMaxPwr;
   I_U32 ptrxId[6]={0};

   memset(&(cellNonPerBuff),0,sizeof(CellNonPerTableApi));

   sCmMsg* receivedCmMsgPtr = NULL;
   LOG_PRINT(LOG_INFO,"Entring cellObjectLockedHandler()");
   memset(&oamsCellhCfgAlarmIndBuff, 0, sizeof(OamsCellhCfgAlarmInd));

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE message received for cellid= %d lac = %d,",cellTablePtr->cellId,cellTablePtr->lac);
         CellPerTableIndices.cellId = cellTablePtr->cellId;
         CellPerTableIndices.lac = cellTablePtr->lac;
         ret = getCellPerTable(&CellPerTableIndices,&cellTable);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_CRITICAL,"Requested Cell is not present in DB, Error Code = [%d]", ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);   
            return;
         }   
         if( (cellTable->adminState == LOCKED) && (cellTablePtr->adminState== UNLOCKED)  )
         {
            /* Fails if BcchPwr in Cell is > maxRf Power in corresponding Bts */
            if(getTrxIdListOnAntennaId(cellTable->antennaId, ptrxId, &count) == CLIB_SUCCESS)
            {
              for(k = 0;k <count;k++)
              {
                 LOG_PRINT(LOG_DEBUG,"trxId %d",ptrxId[k]);
                 if(getRfMaxPwrFromBicTrxTable(ptrxId[k],&btsRfMaxPwr) !=CLIB_SUCCESS)
                 {
                    LOG_PRINT(LOG_CRITICAL,"getBicTable failed for trxId %d",ptrxId[k]);
                    cfgSendNackToCm(CM_ERR_CELL_BCCH_PWR_WRONG);
                    LOG_PRINT(LOG_INFO,"Exiting validateCellParamDependency()");
                    free(cellTable);
                    return;
                 }
                 else
                 {
                   if(cellTable->bcchPwr > btsRfMaxPwr)
                   {
                      LOG_PRINT(LOG_CRITICAL,"BcchPwr %d > RfMaxPwr %d in corresponding Bts",
                                cellTable->bcchPwr,btsRfMaxPwr);
                      cfgSendNackToCm(CM_ERR_CELL_BCCH_PWR_WRONG);
                      LOG_PRINT(LOG_INFO,"Exiting validateCellParamDependency()");
                      free(cellTable);
                      return;
                   }
                 }
              }
           }
           else
           {
              LOG_PRINT(LOG_INFO,"No Trx Present with AntennaId %d",cellTablePtr->antennaId);
           }

            if(gBssState == unlocked)
            {
               cellUnlockReq(cellTablePtr->cellId,cellTablePtr->lac,OAMS_RSN_OPERATORINITIATED);
            }
            else 
            {
               /* Fix Bug CS2.2_SSI_003 : Start */
               if (validateCellParamDependency(cellTable) == OAMS_RSLT_FAILURE) /*Check added during changes for Mantis 2284*/
               {
                  cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
                  LOG_PRINT(LOG_INFO,"Exiting validateCellParamDependency()");
                  free(cellTable);
                  return;
               }
               /* Fix Bug CS2.2_SSI_003 : End */
  
               ret = updateCellAdminState(cellTablePtr->cellId,cellTablePtr->lac,UNLOCKED);
               if (CLIB_SUCCESS == ret)
               {
                  updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,unlockedDisabled,OAMS_RSN_OPERATORINITIATED);
                  cfgSendAckToCm();
                  oamsCellhCfgAlarmIndBuff.sysAlarm.sysalarmId = CELL_UNLOCKED;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.info3 = OAMS_OBJTYPE_CELL;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.key2 = cellTablePtr->cellId;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.key1 = cellTablePtr->lac;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.infoStrLen = sprintf(oamsCellhCfgAlarmIndBuff.sysAlarm.infoString,"CELL %d with LAC %d is UNLOCKED",oamsCellhCfgAlarmIndBuff.sysAlarm.key2,oamsCellhCfgAlarmIndBuff.sysAlarm.key1);

                  cfgSendMessage(&oamsCellhCfgAlarmIndBuff, sizeof(OamsCellhCfgAlarmInd), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               }
               else
               {
                  LOG_PRINT(LOG_CRITICAL,"Update Celltable is unsucessfull, Error Code = [%d],  sending Nack", ret);
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);   
               }
            }
         }
         else if(cellTable->adminState == LOCKED && cellTablePtr->adminState == LOCKED )
         {
           if((cellTable->isCellExtended == TRUE && cellTablePtr->isCellExtended == FALSE )||(cellTable->isCellExtended == FALSE && cellTablePtr->isCellExtended == TRUE ))
           {

             LOG_PRINT(LOG_CRITICAL,"The isCellExtended parameter is not modifiable, sending Nack", ret);
             cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);   

           }
             /* Range check of the parameter will be done at Set/Del Module*/
             LOG_PRINT(LOG_INFO,"Parameter Modification for Cell, updating the DB");
           if(updateCellPerTable(cellTablePtr) == CLIB_SUCCESS)
           {
             /* Mantis Fixed - 7744 Starts */
             /*  Updating row in Non per Cell Table */ 
             cellNonPerBuff.cellId =  cellTablePtr->cellId;    
             cellNonPerBuff.lac =  cellTablePtr->lac;   
             cellNonPerBuff.cellIndex = (I_U16) getCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac);
             /*R2.5 cellNonPerBuff.antennaId =  cellTablePtr->antennaId;   */
             ret = updateCellNonPerTable(&cellNonPerBuff);
             /* Mantis Fixed - 7744 Ends */

             if( ret == CLIB_SUCCESS )
             {
               cfgSendAckToCm();
               /* On The Fly Changes : Start */
               if(  (cellTable->bcchArfcn != cellTablePtr->bcchArfcn) ||
                   (cellTable->bcc != cellTablePtr->bcc)  )
               {
                 sndCsNeighCellChangeMsgToCellh(cellTable->cellId, cellTable->lac, 0, 0);
               }
               /* On The Fly Changes : End */
             }
             else
             {
               LOG_PRINT(LOG_CRITICAL,"Update CellNonPertable is unsucessfull, Error Code = [%d],  sending Nack", ret);
               cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);   
             }
           }
           else
           {
             LOG_PRINT(LOG_CRITICAL,"Update Celltable is unsucessfull, Error Code = [%d],  sending Nack", ret);
             cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);   
           }
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"Incorrect Object State : adminState in Db = %u, adminState received = %u, sending nack",
                      cellTable->adminState, cellTablePtr->adminState );
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);
         }
         free(cellTable);
         break;
/*Changes PCU R2.5 Aricent -- START*/
      
      case BSC_API_SET_PSCELLTABLE:
         setPsCellTableHandler();
         break; 
      case BSC_API_DEL_PSCELLTABLE:
         delPsCellTableHandler();
         break; 
      case BSC_API_DEL_CELLPERTABLE:
         delCellTableHandler();
         break;
/*Changes PCU R2.5 Aricent -- END*/
      default:
         break;
   }
   LOG_PRINT(LOG_INFO,"Exiting cellObjectLockedHandler()");
}

void cellObjectUnlockOrEnableInProgressHandler()
{
   /* CellDataStruct cellDataStructbuff; */
/*Changes PCU R2.5 Aricent -- START*/
   OamsPschCfgUnlockResp *oamsPschCfgUnlockRespPtr = NULL;
   I_S32 ret = CM_FAILURE;
/*Changes PCU R2.5 Aricent -- END*/
   OamsCellhCfgUnlockResp *oamsCellhCfgUnlockRespPtr = NULL;
   CellPerTableIndices CellPerTableIndices;
   CellPerTableApi *cellTable = NULL;
   CellPerTableApi *cellTablePtr = NULL; 
   I_U32 sndMsgSize = 0;
   sCmMsg* receivedCmMsgPtr = NULL;
   OamsCellhCfgAlarmInd oamsCellhCfgAlarmIndBuff;
   I_U8 index = 0;

   LOG_PRINT(LOG_INFO,"Entring cellObjectUnlockOrEnableInProgressHandler()");

   memset(&oamsCellhCfgAlarmIndBuff, 0, sizeof(OamsCellhCfgAlarmInd));
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
/*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSCH_CFG_UNLOCK_RESP:
         oamsPschCfgUnlockRespPtr = (OamsPschCfgUnlockResp *)gCfgMsgBuf ;
         LOG_PRINT(LOG_INFO,"OAMS_PSCH_CFG_UNLOCK_RESP message is received for cellId=%u lac = %u",oamsPschCfgUnlockRespPtr->cellId,oamsPschCfgUnlockRespPtr->lac);
         updatePsCellDataState(oamsPschCfgUnlockRespPtr->cellId,oamsPschCfgUnlockRespPtr->lac, FALSE);
         index = getCellDataStruct(oamsPschCfgUnlockRespPtr->cellId,oamsPschCfgUnlockRespPtr->lac);
         /* Temporary Changes for mantis #29876 Need to be reverted once root cause is caught */
         if((I_FALSE == gCfgStandbyToActive) || (gCellData[index].reqType != OAMS_RSN_PARENTOBJECTLOCKED))
         { 
            sendCellUnlockReq(oamsPschCfgUnlockRespPtr->cellId, 
                 oamsPschCfgUnlockRespPtr->lac, gCellData[index].reqType, index);
         }
         else
         {
             gCellEnableSent--;
             updateCellDataStruct(oamsPschCfgUnlockRespPtr->cellId, 
                  oamsPschCfgUnlockRespPtr->lac, unlockedEnabled, OAMS_RSN_PARENTOBJECTLOCKED);
             LOG_PRINT(DEBUG,"In SwithOver Case Val. of gCellEnableSent:%d", gCellEnableSent);  
             if(0 == gCellEnableSent) 
             {  /*changes starts for mantis #16235 for standby card BSS unlock is over here*/
                informCellUnLockEnableforUnlockDisabledCellsToBss();
                LOG_PRINT(DEBUG,"Psch Unlock Resp rcvd for all Cells");
             } 
         }   
         break;
/*Changes PCU R2.5 Aricent -- END*/
      case OAMS_CELLH_CFG_UNLOCK_RESP:
         oamsCellhCfgUnlockRespPtr = (OamsCellhCfgUnlockResp *)gCfgMsgBuf ;
         LOG_PRINT(LOG_INFO,"OAMS_CELLH_CFG_UNLOCK_RESP message is received for cellId=%u lac = %u",oamsCellhCfgUnlockRespPtr->objId,oamsCellhCfgUnlockRespPtr->lac);
         index = getCellDataStruct(oamsCellhCfgUnlockRespPtr->objId,oamsCellhCfgUnlockRespPtr->lac);
         if(gCellData[index].reqType == OAMS_RSN_OPERATORINITIATED)
         {
            /* Fixed Mantis#2768 : Start */
            /* Cell Structure is now updated with unlockedEnabled instead of unlockedDisabled*/
            updateCellDataStruct(oamsCellhCfgUnlockRespPtr->objId,oamsCellhCfgUnlockRespPtr->lac,unlockedEnabled,OAMS_RSN_OPERATORINITIATED);
            /* Fixed Mantis#2768 : End */
            CellPerTableIndices.cellId =  oamsCellhCfgUnlockRespPtr->objId;
            CellPerTableIndices.lac = oamsCellhCfgUnlockRespPtr->lac;
            ret = getCellPerTable(&CellPerTableIndices,&cellTable);
            if(CLIB_SUCCESS != ret)
            {
               LOG_PRINT(LOG_CRITICAL,"Error getting cellTable, Error Code = [%d]", ret);
            }
            cellTable->adminState = 1;
            ret = updateCellPerTable(cellTable);
            if(CLIB_SUCCESS != ret)
            {
               LOG_PRINT(LOG_CRITICAL,"Error updating cellTable, Error Code = [%d]", ret);
               return;
            }
            free(cellTable);
            oamsCellhCfgAlarmIndBuff.sysAlarm.sysalarmId = CELL_UNLOCKED;
            oamsCellhCfgAlarmIndBuff.sysAlarm.info3 = OAMS_OBJTYPE_CELL;
            oamsCellhCfgAlarmIndBuff.sysAlarm.key2 =oamsCellhCfgUnlockRespPtr->objId ;
            oamsCellhCfgAlarmIndBuff.sysAlarm.key1 =oamsCellhCfgUnlockRespPtr->lac ;
            oamsCellhCfgAlarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_CLEARED;
            oamsCellhCfgAlarmIndBuff.sysAlarm.infoStrLen = sprintf(oamsCellhCfgAlarmIndBuff.sysAlarm.infoString,"CELL %d with LAC %d is UNLOCKED",oamsCellhCfgAlarmIndBuff.sysAlarm.key2,oamsCellhCfgAlarmIndBuff.sysAlarm.key1);

            cfgSendMessage(&oamsCellhCfgAlarmIndBuff, sizeof(OamsCellhCfgAlarmInd), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            
                  /*Changes for CS4.0 : Abis E1 Lock/Unlock Start*/
            abisE1LockUnlockAfterCellUnlock(oamsCellhCfgUnlockRespPtr->objId,oamsCellhCfgUnlockRespPtr->lac);
                  /*Changes for CS4.0 : Abis E1 Lock/Unlock Ends*/

         }
         else if (gCellData[index].reqType == OAMS_RSN_PARENTOBJECTLOCKED)
         {
            /* Fixed Mantis#2768 : Start */
            /* Cell Structure is now updated with unlockedEnabled instead of unlockedDisabled*/
            updateCellDataStruct(oamsCellhCfgUnlockRespPtr->objId,oamsCellhCfgUnlockRespPtr->lac,unlockedEnabled,OAMS_RSN_PARENTOBJECTLOCKED);
            /* Fixed Mantis#2768 : End */

            /*************** Code Added by Sanjeev **************************/ 
            if( gBssState == lockInProgress )
            {
               initiateCellLockDisableforUnlockedCells();              
            }   
            else 
               gCellEnableSent--;
            if(gCellEnableSent == 0)
            {
               informCellUnLockEnableforUnlockDisabledCellsToBss();
               LOG_PRINT(DEBUG,"UNLOCK Response is received for every CELL"); 
               if(gSSAReceived != TRUE)
               {
                  sendCellBarAccessToCells(LockProcedure,OAMS_RSN_AINTERFACEDOWN);
               }
            }
            /****************************************************************/ 

         }
         break;
      case BSC_API_SET_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE message is received for cellId=%d lac = %d",cellTablePtr->cellId,cellTablePtr->lac);

         CellPerTableIndices.lac = cellTablePtr->lac;
         CellPerTableIndices.cellId = cellTablePtr->cellId;
         ret = getCellPerTable(&CellPerTableIndices,&cellTable);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_CRITICAL,"Error getting from cellTable, Error Code = [%d]", ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return ;
         }   
         index = getCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac);
         if(gCellData[index].reqType == OAMS_RSN_OPERATORINITIATED)
         {
            cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);

         }
         else if (gCellData[index].reqType == OAMS_RSN_PARENTOBJECTLOCKED)
         {
            if(cellTable->adminState == UNLOCKED  && cellTablePtr->adminState== LOCKED )
            {
/*Changes PCU R2.5 Aricent -- START*/
               I_U8 cellIndex = getCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac);
               cfgSendAckToCm();
               sendCellLockReq(cellTablePtr->cellId, cellTablePtr->lac, OAMS_RSN_OPERATORINITIATED, cellIndex);
/*Changes PCU R2.5 Aricent -- END*/
               updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,lockeOrDisableInProgress,OAMS_RSN_OPERATORINITIATED);
            }
            else if((cellTable->adminState == UNLOCKED  && cellTablePtr->adminState== UNLOCKED) || (cellTable->adminState == LOCKED  && cellTablePtr->adminState== LOCKED))
            {
               cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
            }
         }
         free(cellTable);
         break;   
      case OAMS_PSSCM_CFG_ALARM_IND:
         /* the mesage is handled in Alarmhandler*/
         break;
/*Changes PCU R2.5 Aricent -- START*/
      /* sending CM_ERR_UNLOCK_IN_PROGRESS 
         in all these cases */
      case BSC_API_SET_PSCELLTABLE:
      case BSC_API_DEL_PSCELLTABLE:
      case BSC_API_DEL_CELLPERTABLE:
         LOG_PRINT(LOG_INFO,"Cell is in UnlockOrEnableInProgress, Sending Nack");
         cfgSendNackToCm(CM_ERR_UNLOCK_IN_PROGRESS);
         break;
/*Changes PCU R2.5 Aricent -- END*/
      default :
         break;
   }//end switch sysHdrPtr->msgType
   LOG_PRINT(LOG_INFO,"Exiting cellObjectUnlockOrEnableInProgressHandler()");
}

void cellObjectUnlockedEnabledHandler()
{
   CellPerTableApi *cellTablePtr=NULL;
   /* CellDataStruct cellDataStructbuff; */
   CellPerTableIndices CellPerTableIndices;
   CellPerTableApi *cellTable=NULL;
   sCmMsg* receivedCmMsgPtr=NULL;
/*Changes PCU R2.5 Aricent -- START*/   
   I_U8 cellIndex = ZERO;
   I_S32 ret = CM_FAILURE;
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"Entering cellObjectUnlockedEnabledHandler()");
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE message is received for cellId = %d lac = %d",cellTablePtr->cellId,cellTablePtr->lac);

         CellPerTableIndices.lac = cellTablePtr->lac;
         CellPerTableIndices.cellId = cellTablePtr->cellId;
         ret = getCellPerTable(&CellPerTableIndices,&cellTable);
         if(CLIB_SUCCESS != ret)
         {
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);   
            return;
         }   
         
         /*Changes PCU R2.5 Aricent -- START*/
         cellIndex = getCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac);
         /*Changes PCU R2.5 Aricent -- END*/
         
         if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== LOCKED )
         {
            
            /*Changes PCU R2.5 Aricent -- START*/
            /*BUG FIX: will send ack after Rcving ack from Cellh in Cell Lock case only*/
            //cfgSendAckToCm();
            sendCellLockReq(cellTablePtr->cellId, cellTablePtr->lac, OAMS_RSN_OPERATORINITIATED, cellIndex);
            /*Changes PCU R2.5 Aricent -- END*/
            updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,lockeOrDisableInProgress,OAMS_RSN_OPERATORINITIATED);
         }
         else if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState == BLOCK)
         {
            sendCellBlockReq(cellTablePtr->cellId,cellTablePtr->lac, cellIndex);
         }
/*Changes R2.5.2: START*/
         else if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState == UNLOCKED)
         {
            if(TRUE == isOnlyFrToHrPerctModified(cellTable, cellTablePtr))
            {
               if(CLIB_SUCCESS == updateCellPerTable(cellTablePtr))
               {
                  LOG_PRINT(LOG_INFO,"Cell Table updated successfully for frToHrPerct Change");
                  sendCellInfoUpdInd(cellIndex); 
                  cfgSendAckToCm();
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"DB Operation failed..");
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED); 
               }
            }
/*Changes R2.5.2: END*/
            else
            {
               LOG_PRINT(LOG_MAJOR, "Modification of Parameters other than frToHrPerct is not allowed in Cell Unlocked State");

               /****Mantis 15378 Fix Start****/
               //cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);   
               cfgSendAckToCm();  
               /****Mantis 15378 Fix End****/
            }
         }
         else
            cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);   
         free(cellTable);
         break;
/*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSCH_CFG_ALARM_IND:
          /* the mesage is handled in Alarmhandler*/
         break;
      case OAMS_CELLH_CFG_ALARM_IND :      
          /* the mesage is handled in Alarmhandler*/
         break;
      case OAMS_PSSCM_CFG_ALARM_IND:
          /* the mesage is handled in Alarmhandler*/
         break;
         
      /* sending CM_ERR_INCORRECT_OBJ_STATE 
         in all these cases */
      case BSC_API_SET_PSCELLTABLE:
      case BSC_API_DEL_PSCELLTABLE:
      case BSC_API_DEL_CELLPERTABLE:
         LOG_PRINT(LOG_MAJOR,"Cell is in Unlocked, Sending Nack");
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);   
         break;
     
/*Changes PCU R2.5 Aricent -- END*/
      default :
         break;
   }//end switch sysHdrPtr->msgType
   LOG_PRINT(LOG_INFO,"Exiting cellObjectUnlockedEnabledHandler()");
}

void cellObjectUnlockedDisabledHandler()
{
   CellPerTableApi *cellTablePtr=NULL;
   CellPerTableIndices CellPerTableIndices;
   CellPerTableApi *cellTable=NULL;
   /* CellDataStruct cellDataStructbuff; */
   sCmMsg* receivedCmMsgPtr = NULL;
   OamsCellhCfgAlarmInd oamsCellhCfgAlarmIndBuff;
/*Changes PCU R2.5 Aricent -- START*/   
   I_U8 cellIndex = ZERO;
   I_S32 ret = CM_FAILURE;
/*Changes PCU R2.5 Aricent -- END*/

   LOG_PRINT(LOG_INFO,"Entering cellObjectUnlockedDisabledHandler()");
   memset(&oamsCellhCfgAlarmIndBuff, 0, sizeof(OamsCellhCfgAlarmInd));
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE message is received for cellId=%d lac = %d",cellTablePtr->cellId,cellTablePtr->lac);
         CellPerTableIndices.lac = cellTablePtr->lac;
         CellPerTableIndices.cellId = cellTablePtr->cellId;
         ret = getCellPerTable(&CellPerTableIndices,&cellTable);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_CRITICAL,"Error geeting Cell table from DB, Error Code = [%d]", ret);   
         }   
         
         /*Changes PCU R2.5 Aricent -- START*/
         cellIndex = getCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac);
         /*Changes PCU R2.5 Aricent -- END*/
         
         if(gBssState == unlocked)
         {
            if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== LOCKED )
            {
               /*Changes PCU R2.5 Aricent -- START*/
               /*BUG FIX: will send ack after Rcving ack from Cellh in Cell Lock case only*/
               //cfgSendAckToCm();
               sendCellLockReq(cellTablePtr->cellId, cellTablePtr->lac, OAMS_RSN_OPERATORINITIATED, cellIndex);
               /*Changes PCU R2.5 Aricent -- END*/
               updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,lockeOrDisableInProgress, 
                     OAMS_RSN_OPERATORINITIATED);

            }
            else if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== BLOCK)
            {
               sendCellBlockReq(cellTablePtr->cellId, cellTablePtr->lac, cellIndex);
            }
            else
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);         
         }
         else 
         {
            if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== LOCKED )
            {
               ret = updateCellAdminState(cellTable->cellId,cellTable->lac,LOCKED);
               if (CLIB_SUCCESS == ret)
               {
                  updateCellDataStruct(cellTable->cellId,cellTable->lac,locked,OAMS_RSN_OPERATORINITIATED);
                  cfgSendAckToCm();

                  /* Code change for Mantis Id 1903*/
                  oamsCellhCfgAlarmIndBuff.sysAlarm.sysalarmId = CELL_LOCKED;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.info3 = OAMS_OBJTYPE_CELL;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.key1 = cellTable->lac;
                  oamsCellhCfgAlarmIndBuff.sysAlarm.key2 = cellTable->cellId;
                  /* Mantis Id 2242 Start */
                  oamsCellhCfgAlarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
                  /* Mantis Id 2242 End */
                  oamsCellhCfgAlarmIndBuff.sysAlarm.infoStrLen = sprintf(oamsCellhCfgAlarmIndBuff.sysAlarm.infoString,"CELL %d with LAC %d is LOCKED",oamsCellhCfgAlarmIndBuff.sysAlarm.key1,oamsCellhCfgAlarmIndBuff.sysAlarm.key2);

                  cfgSendMessage(&oamsCellhCfgAlarmIndBuff, sizeof(OamsCellhCfgAlarmInd), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

                  /* End of Code change for Mantis Id 1903 */
               }
               else
               {
                  LOG_PRINT(LOG_CRITICAL,"Update Celltable is unsucessfull, Error Code = %d", ret);
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);   
               }
            }
            /*Changes PCU R2.5 Aricent -- START*/
            else if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== BLOCK)
            {
               ret = updateCellAdminState(cellTable->cellId, cellTable->lac, LOCKED);
               if (CLIB_SUCCESS == ret)
               {
                  updateCellDataStruct(cellTable->cellId, cellTable->lac, locked, OAMS_RSN_OPERATORINITIATED);
                  cfgSendAckToCm();
               }
               else
               {
                  LOG_PRINT(LOG_CRITICAL,"Update Cell Admin State is unsucessfull, Error Code = %d", ret);
                  cfgSendNackToCm(CM_ERR_UPDATE_DB_OPER_FAILED);   
               }
            }
            /*Changes PCU R2.5 Aricent -- END*/
            else
            {
               LOG_PRINT(LOG_MAJOR, "Incorrect Object State, adminState in DB = %u, adminState received = %u",
                         cellTable->adminState, cellTablePtr->adminState); 
               cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);         
            }
         }
         free(cellTable);
         break;
/*Changes PCU R2.5 Aricent -- START*/
      /* sending CM_ERR_INCORRECT_OBJ_STATE 
         in all these cases */
      case BSC_API_SET_PSCELLTABLE:
      case BSC_API_DEL_PSCELLTABLE:
      case BSC_API_DEL_CELLPERTABLE:
         LOG_PRINT(LOG_INFO,"Cell is in Unlocked, Sending Nack");
         cfgSendNackToCm(CM_ERR_INCORRECT_OBJ_STATE);         
         break;
/*Changes PCU R2.5 Aricent -- END*/
      default:
         break;
   }//end switch sysHdrPtr->msgType
   LOG_PRINT(LOG_INFO,"Exiting cellObjectUnlockedDisabledHandler()");

}

void cellObjectLockOrDisableInProgressHandler()
{
   /*   CellDataStruct cellDataStructbuff; */
   CellPerTableApi *cellTablePtr =NULL;
   CellPerTableApi *cellTable =NULL;;
   CellPerTableIndices cellTableIndices;
   OamsPschCfgLockResp *oamsPschCfgLockRespPtr = NULL;;
   OamsCellhCfgLockResp *oamsCellhCfgLockRespPtr = NULL;;
   OamsCfgAfhSysAlarm oamsCfgAfhSysAlarmBuff;
   sCmMsg* receivedCmMsgPtr = 0;
   I_U8 index = 0;    
/*Changes PCU R2.5 Aricent -- START*/   
   BssTableApi *bssTable = NULL;
   I_S32 ret = CM_FAILURE;
   I_U32 count = 0;
   I_U16 outSize = 0; 
/*Changes PCU R2.5 Aricent -- END*/
   LOG_PRINT(LOG_INFO,"Entering cellObjectLockOrDisableInProgressHandler()");

   memset(&oamsCfgAfhSysAlarmBuff, 0, sizeof(OamsCfgAfhSysAlarm));
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case OAMS_CELLH_CFG_LOCK_RESP:
         oamsCellhCfgLockRespPtr = (OamsCellhCfgLockResp *)gCfgMsgBuf ;
         LOG_PRINT(LOG_INFO,"OAMS_CELLH_CFG_LOCK_RESP message is received for cellId=%d lac = %d",oamsCellhCfgLockRespPtr->objId,oamsCellhCfgLockRespPtr->lac);
         index = getCellDataStruct(oamsCellhCfgLockRespPtr->objId,oamsCellhCfgLockRespPtr->lac);
         /* Get the row for the cell to check the psStatus */
         cellTableIndices.cellId = oamsCellhCfgLockRespPtr->objId;
         cellTableIndices.lac = oamsCellhCfgLockRespPtr->lac;
         ret = getCellPerTable(&cellTableIndices,&cellTablePtr);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_CRITICAL,"Error getting from CellTable, Error Code = [%d]", ret);
         }

/*Changes PCU R2.5 Aricent -- START*/
         ret = getallBssTable(&bssTable,&count,&outSize);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR,"Error getting BSS Table, Error Code = [%d] ", ret);
            return;
         }
         
/*Changes PCU R2.5 Aricent -- END*/

         if( (gCellData[index].reqType == OAMS_RSN_OPERATORINITIATED) ||
              (gCellData[index].reqType == OAMS_RSN_CELLBLOCKTIMEREXPIRY) || 
              (gCellData[index].reqType == OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK)  )
         {

            /*BUG FIX: will send ack after Rcving ack from Cellh in Cell Lock case only*/
            if(CM_SUCCESS != oamsCellhCfgLockRespPtr->result )
            {
                LOG_PRINT(DEBUG,"Cellh has given Nack in Lock Response err:%d",oamsCellhCfgLockRespPtr->result );  
                updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,unlockedEnabled,gCellData[index].reqType);
                cfgSendNackToCm(oamsCellhCfgLockRespPtr->result);  
            } 
/*Changes PCU R2.5 Aricent -- START*/
            else if(PS_ALLOWED == cellTablePtr->psAllowed && ENABLED == bssTable->gprsEnabled )
            {
               cfgSendAckToCm(); 
               sendPsCellLockReq(oamsCellhCfgLockRespPtr->objId, oamsCellhCfgLockRespPtr->lac, gCellData[index].reqType, index);
/*Changes PCU R2.5 Aricent -- END*/
            }
            else
            {
               cfgSendAckToCm(); 
               ret = updateCellAdminState(cellTablePtr->cellId,cellTablePtr->lac,LOCKED);
               if (CLIB_SUCCESS == ret)
               {
                  updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,locked,gCellData[index].reqType);
               }
               else
               {
                  LOG_PRINT(LOG_MAJOR,"Error updating Cell AdminState, Error Code = [%d] ", ret);
               }
               oamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = CELL_LOCKED;
               oamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CELL;
               oamsCfgAfhSysAlarmBuff.sysAlarm.key2 = oamsCellhCfgLockRespPtr->objId;
               oamsCfgAfhSysAlarmBuff.sysAlarm.key1 = oamsCellhCfgLockRespPtr->lac;
               /* Mantis Id 2242 Start */
               oamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
               /* Mantis Id 2242 End */

               oamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(oamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"CELL %d with LAC %d is LOCKED",oamsCfgAfhSysAlarmBuff.sysAlarm.key2,oamsCfgAfhSysAlarmBuff.sysAlarm.key1);

               cfgSendMessage(&oamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
               if(OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK == gCellData[index].reqType )
               {
                  gCellDisableSent--;
                  if(gCellDisableSent == 0)
                  {
                     informCellUnLockDisableforUnlckedCellsToBss();
                  }
               }  
            }
         }
         else if(gCellData[index].reqType == OAMS_RSN_PARENTOBJECTLOCKED || gCellData[index].reqType == OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK)
         {
            if(cellTablePtr->psAllowed == PS_ALLOWED && ENABLED == bssTable->gprsEnabled)
            {
/*Changes PCU R2.5 Aricent -- START*/
	       sendPsCellLockReq(oamsCellhCfgLockRespPtr->objId, oamsCellhCfgLockRespPtr->lac, gCellData[index].reqType, index);
/*Changes PCU R2.5 Aricent -- END*/
            }
            else
            {
               updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,unlockedDisabled, OAMS_RSN_PARENTOBJECTLOCKED);
               gCellDisableSent--;
               if(gCellDisableSent == 0)
               {
                  informCellUnLockDisableforUnlckedCellsToBss();
               }
            }
         }
         free(bssTable);
         free(cellTablePtr);
         break;
/*Changes PCU R2.5 Aricent -- START*/
      case OAMS_PSCH_CFG_LOCK_RESP:
         oamsPschCfgLockRespPtr = (OamsPschCfgLockResp *)gCfgMsgBuf ;
         LOG_PRINT(LOG_INFO,"OAMS_PSCH_CFG_LOCK_RESP message is received for cellId=%d lac = %d",
                   oamsPschCfgLockRespPtr->cellId, oamsPschCfgLockRespPtr->lac);
         updatePsCellDataState(oamsPschCfgLockRespPtr->cellId,oamsPschCfgLockRespPtr->lac, FALSE);
         
         index = getCellDataStruct(oamsPschCfgLockRespPtr->cellId, oamsPschCfgLockRespPtr->lac);
         LOG_PRINT(LOG_INFO,"index = %u, gCellData[index].cellId = %u, gCellData[index].lac = %u, gCellData[index].reqType = %u", index, gCellData[index].CellID, gCellData[index].lac, gCellData[index].reqType);
          /*Mantis Fix 0013659 */
         if (OAMS_RSN_OPERATORINITIATED == gCellData[index].reqType ||OAMS_RSN_CELLBLOCKTIMEREXPIRY == gCellData[index].reqType || OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK == gCellData[index].reqType)
         {
            LOG_PRINT(LOG_INFO," for operator initiated Cell Lock");
            ret = updateCellAdminState(oamsPschCfgLockRespPtr->cellId,oamsPschCfgLockRespPtr->lac,LOCKED);
            if (CLIB_SUCCESS == ret)
            {
              updateCellDataStruct(oamsPschCfgLockRespPtr->cellId,oamsPschCfgLockRespPtr->lac,locked,gCellData[index].reqType);
            }
            else
            {
               LOG_PRINT(LOG_MAJOR,"Error updating Cell AdminState, Error Code = [%d] ", ret);
            }
            oamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId = CELL_LOCKED;
            oamsCfgAfhSysAlarmBuff.sysAlarm.info3 = OAMS_OBJTYPE_CELL;
            oamsCfgAfhSysAlarmBuff.sysAlarm.key2 = oamsPschCfgLockRespPtr->cellId;
            oamsCfgAfhSysAlarmBuff.sysAlarm.key1 = oamsPschCfgLockRespPtr->lac;
            oamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   
            oamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(oamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"CELL %d with LAC %d is LOCKED",
                                                                 oamsCfgAfhSysAlarmBuff.sysAlarm.key2,oamsCfgAfhSysAlarmBuff.sysAlarm.key1);
            LOG_PRINT(LOG_INFO,"sending CELL_LOCKED alarm to AFH for Cell [ cellId = %d, lac = %d ] ", 
                      oamsPschCfgLockRespPtr->cellId, oamsPschCfgLockRespPtr->lac);
            cfgSendMessage(&oamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            /*Mantis Fix 0013659 */
            if(lockInProgress == gBssState || OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK == gCellData[index].reqType)
            {
               LOG_PRINT(LOG_INFO,"BSS Lock-In-Progress");
               LOG_PRINT(LOG_INFO,"gCellDisableSent = %u", gCellDisableSent);
               gCellDisableSent--;
               if(gCellDisableSent == 0)
               {
                  LOG_PRINT(LOG_INFO,"calling informCellUnLockDisableforUnlckedCellsToBss()");
                  informCellUnLockDisableforUnlckedCellsToBss();
               }
            }
         }
         else if(OAMS_RSN_PARENTOBJECTLOCKED == gCellData[index].reqType) 
         {
            LOG_PRINT(LOG_INFO," for Cell Lock due to BSS Lock");
            updateCellDataStruct(oamsPschCfgLockRespPtr->cellId, oamsPschCfgLockRespPtr->lac,unlockedDisabled, OAMS_RSN_PARENTOBJECTLOCKED);
            LOG_PRINT(LOG_INFO,"gCellDisableSent = %u", gCellDisableSent);
            gCellDisableSent--;
            if(gCellDisableSent == 0)
            {
               LOG_PRINT(LOG_INFO,"calling informCellUnLockDisableforUnlckedCellsToBss()");
               informCellUnLockDisableforUnlckedCellsToBss();
            }
         }
         break;
/*Changes PCU R2.5 Aricent -- END*/
      case BSC_API_SET_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE message is received for cellId=%d lac = %d",cellTablePtr->cellId,cellTablePtr->lac);

         cellTableIndices.lac = cellTablePtr->lac;
         cellTableIndices.cellId = cellTablePtr->cellId;
         ret = getCellPerTable(&cellTableIndices,&cellTable);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR,"Error getting Cell data , Error Code = [%d], sending Nack ", ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return ;
         }   
         index = getCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac);
         if(gCellData[index].reqType == OAMS_RSN_OPERATORINITIATED)
         {
            cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);

         }
         else if (gCellData[index].reqType == OAMS_RSN_PARENTOBJECTLOCKED)
         {
            if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== LOCKED )
            {
               cfgSendAckToCm();
               updateCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac,lockeOrDisableInProgress,OAMS_RSN_OPERATORINITIATED);
            }
            else if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== UNLOCKED )
            {
               cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
            }
            else
               cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);

         }
         free(cellTable);   
         break;
/*Changes PCU R2.5 Aricent -- START*/
       /* sending CM_ERR_LOCK_IN_PROGRESS 
        * in all these cases */
      case BSC_API_SET_PSCELLTABLE:
      case BSC_API_DEL_PSCELLTABLE:
      case BSC_API_DEL_CELLPERTABLE:
         LOG_PRINT(LOG_INFO,"Cell is in LockOrDisableInProgress, Sending Nack");
         cfgSendNackToCm(CM_ERR_LOCK_IN_PROGRESS);
         break;
/*Changes PCU R2.5 Aricent -- END*/
      default :
         break;
   }//end switch sysHdrPtr->msgType
   LOG_PRINT(LOG_INFO,"Exiting cellObjectLockOrDisableInProgressHandler()");
}

void cellObjectBlockInProgressHandler()
{
   CellPerTableApi *cellTablePtr=NULL;
   sCmMsg* receivedCmMsgPtr=NULL;
   CellPerTableApi *cellTable=NULL;
   CellPerTableIndices cellTableIndices;
   I_U8 index = 0;
   I_S32 ret = CM_FAILURE;
   /* CellDataStruct cellDataStructbuff; */

   LOG_PRINT(LOG_INFO,"Entering cellObjectBlockInProgressHandler()");
   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE message is received for cellId=%d lac = %d",cellTablePtr->cellId,cellTablePtr->lac);

         cellTableIndices.lac = cellTablePtr->lac;
         cellTableIndices.cellId = cellTablePtr->cellId;

         ret = getCellPerTable(&cellTableIndices,&cellTable);
         if(CLIB_SUCCESS != ret)
         {
            LOG_PRINT(LOG_MAJOR,"Error getting Cell data , Error Code = [%d], sending Nack ", ret);
            cfgSendNackToCm(CM_ERR_GET_DB_OPER_FAILED);
            return ;
         }
         index = getCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac);
         if(cellTable->adminState == UNLOCKED && cellTablePtr->adminState== LOCKED )
         {
            cfgSendAckToCm();
            StopTimerFrmwrk(gTimerId);
            sendCellLockReq(cellTablePtr->cellId,cellTablePtr->lac,OAMS_RSN_OPERATORINITIATED, index);
         }
         else
         {
            LOG_PRINT(LOG_MAJOR,"Cell Shutdown in progress, sending Nack ");
            cfgSendNackToCm(CM_ERR_CELL_BLOCK_IN_PROGRESS);
         }      
         free(cellTable);
         break; 
      case IPC_TIMER:
         /*Code Added for */
         applTimer = (ApplTimer *) gCfgMsgBuf;
//         cellIndex = applTimer->tmrPayLoad.payLoad[0];
         memcpy(&(cellIndex),&(applTimer->tmrPayLoad.payLoad[1]),sizeof(I_U8));
         sendCellLockReq( gCellData[cellIndex].CellID,gCellData[cellIndex].lac, OAMS_RSN_CELLBLOCKTIMEREXPIRY, cellIndex);
         break;   

/*Changes PCU R2.5 Aricent -- START*/
      /* sending CM_ERR_BLOCK_IN_PROGRESS 
         in all these cases */
      case BSC_API_SET_PSCELLTABLE:
      case BSC_API_DEL_PSCELLTABLE:
      case BSC_API_DEL_CELLPERTABLE:
         LOG_PRINT(LOG_INFO,"Cell is in BlockInProgress, Sending Nack");
         cfgSendNackToCm(CM_ERR_CELL_BLOCK_IN_PROGRESS);
         break;
/*Changes PCU R2.5 Aricent -- END*/
      default:
         LOG_PRINT(LOG_CRITICAL,"Unexpected Message is received");
   }/*end of switch (((SysHdr*) gCfgMsgBuf)->msgType)*/
   LOG_PRINT(LOG_INFO,"Exiting cellObjectBlockInProgressHandler()");
}

I_U8 getCellDataState()
{
   CellPerTableApi *cellTablePtr=NULL;
   PsCellTableApi *psCellTablePtr = NULL;  
   sCmMsg* receivedCmMsgPtr = 0;

   OamsCellhCfgUnlockResp *oamsCellhCfgUnlockRespPtr=NULL;
   OamsCellhCfgLockResp *oamsCellhCfgLockRespPtr=NULL;
   OamsPschCfgUnlockResp *oamsPschCfgUnlockRespPtr = NULL;
   OamsPschCfgLockResp *oamsPschCfgLockRespPtr = NULL;

   I_U8 index = 0;

   LOG_PRINT(LOG_INFO,"Entering getCellDataState()");

   switch (((SysHdr*) gCfgMsgBuf)->msgType)
   {
      case BSC_API_SET_CELLPERTABLE :
   			 LOG_PRINT(LOG_INFO,"BSC_API_SET_CELLPERTABLE");
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         index = getCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac);   
         break;
      case BSC_API_SET_PSCELLTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         psCellTablePtr = (PsCellTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         index = getCellDataStruct(psCellTablePtr->cellId,psCellTablePtr->lac);   
         break;
      case BSC_API_DEL_CELLPERTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         cellTablePtr = (CellPerTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         index = getCellDataStruct(cellTablePtr->cellId,cellTablePtr->lac);   
         break;
      case BSC_API_DEL_PSCELLTABLE :
         receivedCmMsgPtr = ( sCmMsg* )gCfgMsgBuf;
         psCellTablePtr = (PsCellTableApi *)(((I_U8 *)receivedCmMsgPtr) +sizeof(sCmMsg));
         index = getCellDataStruct(psCellTablePtr->cellId,psCellTablePtr->lac);   
         break;
      case OAMS_CELLH_CFG_LOCK_RESP:
   			 LOG_PRINT(LOG_INFO,"OAMS_CELLH_CFG_LOCK_RESP:");
         oamsCellhCfgLockRespPtr = (OamsCellhCfgLockResp *)gCfgMsgBuf ;
         index = getCellDataStruct(oamsCellhCfgLockRespPtr->objId,oamsCellhCfgLockRespPtr->lac);
         break;
      case OAMS_CELLH_CFG_UNLOCK_RESP:
   			 LOG_PRINT(LOG_INFO,"OAMS_CELLH_CFG_UNLOCK_RESP:");
         oamsCellhCfgUnlockRespPtr = (OamsCellhCfgUnlockResp *)gCfgMsgBuf ;
         index = getCellDataStruct(oamsCellhCfgUnlockRespPtr->objId,oamsCellhCfgUnlockRespPtr->lac);
         break;

      case OAMS_PSCH_CFG_UNLOCK_RESP:
         oamsPschCfgUnlockRespPtr = (OamsPschCfgUnlockResp *)gCfgMsgBuf ;
         index = getCellDataStruct(oamsPschCfgUnlockRespPtr->cellId,oamsPschCfgUnlockRespPtr->lac);
         break;
      case OAMS_PSCH_CFG_LOCK_RESP:
         oamsPschCfgLockRespPtr = (OamsPschCfgLockResp *)gCfgMsgBuf ;
         index = getCellDataStruct(oamsPschCfgLockRespPtr->cellId,oamsPschCfgLockRespPtr->lac);
         break;

      case OAMS_CELLH_CFG_ALARM_IND:
         {
            OamsCellhCfgAlarmInd *OamsCellhCfgAlarmIndPtr;
            OamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;

            index = getCellDataStruct(OamsCellhCfgAlarmIndPtr->sysAlarm.key2,OamsCellhCfgAlarmIndPtr->sysAlarm.key1);
         }
         break;

      case IPC_TIMER:
         /*Code Added for */
         applTimer = (ApplTimer *) gCfgMsgBuf;
//         cellIndex = applTimer->tmrPayLoad.payLoad[0];
         memcpy(&(cellIndex),&(applTimer->tmrPayLoad.payLoad[1]),sizeof(I_U8));
         index = cellIndex ;
      default :
         break;
   }//end switch SysHderPtr->msgType
   LOG_PRINT(LOG_INFO,"Exiting getCellDataState()");
   return index;
}

I_U8 getCellDataStruct(I_U32 cellId,I_U32 lac)
{
   I_U8 i=0;
   LOG_PRINT(LOG_INFO,"Entering getCellDataStruct()");
   LOG_PRINT(LOG_INFO,"CellId = %u, Lac = %u", cellId, lac);
   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {

      if (gCellData[i].CellID == cellId && gCellData[i].lac == lac)
      {
         LOG_PRINT(LOG_INFO,"Index = %u",i);
         return i;          
      }
   }
   LOG_PRINT(LOG_INFO,"Exiting getCellDataStruct()");
   return 255;
}

void updateCellDataStruct(I_U32 cellId,I_U32 lac,I_S32 state,I_Bool reqType)
{
   I_U8 i=0;
   LOG_PRINT(LOG_INFO,"Entering updateCellDataStruct() with cellId = %d, Lac = %d, state = %d, reqType = %d",cellId,lac,state,reqType);

   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {
      if (gCellData[i].CellID == cellId && gCellData[i].lac ==  lac)
      {
   			LOG_PRINT(LOG_INFO,"updated gcelldata  gCellData[%d],state=%d",i,state);
         gCellData[i].CellState = state;
         gCellData[i].reqType = reqType;
      }
   }
   LOG_PRINT(LOG_INFO,"Exiting updateCellDataStruct()");
}
/*Changes PCU R2.5 Aricent --START*/
I_Void updatePsCellDataState(I_U32 cellId,I_U32 lac,I_Bool state)
{
   I_U8 i=0;
   LOG_PRINT(LOG_INFO,"Entering updatePsCellDataState()");

   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {
      if (gCellData[i].CellID == cellId && gCellData[i].lac ==  lac)
      {
         LOG_PRINT(LOG_INFO,"Updating the state at index = %d", i);
         gCellData[i].isReqSentForPS = state;
      }
   }
   LOG_PRINT(LOG_INFO,"Exiting updatePsCellDataState()");
}
/*Changes PCU R2.5 Aricent --END*/

void cellUnlockReq(I_U32 cellId,I_U32 lac,I_U32 reason)
{
   CellPerTableIndices cellTableIndices;
   CellPerTableApi *cellTablePtr = PNULL;
   LOG_PRINT(LOG_INFO,"Entering cellUnlockReq()");
   cellTableIndices.cellId = cellId;
   cellTableIndices.lac = lac;

/*Changes PCU R2.5 Aricent -- START*/
   BssTableApi *bssTableApiPtr = NULL;
   I_U32 count = 0;
   I_U16 outSize;
   I_U8 cellIndex = 0;
   I_S32 ret = CM_FAILURE;

   cellIndex = getCellDataStruct(cellId, lac);
/*Changes PCU R2.5 Aricent -- END*/
   if (getCellPerTable(&cellTableIndices,&cellTablePtr) != CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_CRITICAL,"cellUnlockReq getCellPerTable DB call is getting failed.."); 
      return;
   }

   if (validateCellParamDependency(cellTablePtr) !=OAMS_RSLT_FAILURE)
   {
      LOG_PRINT(LOG_INFO,"Entering validateCellParamDependency()");
      if ( reason != OAMS_RSN_PARENTOBJECTLOCKED )
         cfgSendAckToCm();
      LOG_PRINT(LOG_INFO,"Exiting validateCellParamDependency()");
   }
   else 
   {
      LOG_PRINT(LOG_INFO,"validateCellParamDependency(cellTablePtr) ==OAMS_RSLT_FAILURE ");
      if ( reason != OAMS_RSN_PARENTOBJECTLOCKED )
      {
         cfgSendNackToCm(CM_ERR_CELL_CONSIST_CHECK_FAILED);
      }
      free(cellTablePtr);
      return;
   }

/*Changes PCU R2.5 Aricent -- START*/
   ret = getallBssTable(&bssTableApiPtr,&count,&outSize);
   if( CLIB_SUCCESS != ret )
   {
      LOG_PRINT(LOG_CRITICAL,"cellUnlockReq getallBssTable DB call is getting failed, Error Code = [%d]", ret);
      free(cellTablePtr);
      return;
   }
   if ((PS_ALLOWED == cellTablePtr->psAllowed) &&  (ENABLED == bssTableApiPtr->gprsEnabled) )
   {
      LOG_PRINT(LOG_INFO,"psStatus == PS_ALLOWED for Cell [%d] Lac [%d]",cellId,lac);
      if(gCfgStandbyToActive == I_FALSE)  
      {
         /*Send OAMS_CFG_PSCH_UNLOCK_REQ*/
         sendPsCellUnlockReq(cellId, lac, reason, cellIndex);
         updateCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac, unlockOrEnableInProgress, reason);
         if ( reason == OAMS_RSN_PARENTOBJECTLOCKED )
            gCellEnableSent++;
      } 
      else
      {
         LOG_PRINT(DEBUG,"Cell Unlcok request sent To PSCH as SO case");
         sendPsCellUnlockReq(cellId, lac, reason, cellIndex);
         gCellEnableSent++;
         updateCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac, unlockOrEnableInProgress, reason);
         //updateCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac, unlockedEnabled, reason);
      } 
   }
   else
   {
      LOG_PRINT(LOG_INFO,"psStatus == %d, gprsEnabled = %d for Cell [%d] Lac [%d], calling sendCellUnlockReq()",
                cellTablePtr->psAllowed, bssTableApiPtr->gprsEnabled, cellId, lac );
      if(gCfgStandbyToActive == I_FALSE)  
      {
         /*Changes PCU R2.5 Aricent -- END*/
         sendCellUnlockReq(cellTablePtr->cellId, cellTablePtr->lac,reason, cellIndex);
         updateCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac, unlockOrEnableInProgress, reason);
         if ( reason == OAMS_RSN_PARENTOBJECTLOCKED )
            gCellEnableSent++;
      } 
      else
      {
         LOG_PRINT(DEBUG,"Cell Unlcok request Not sent To Cellh as SO case");
         updateCellDataStruct(cellTablePtr->cellId, cellTablePtr->lac, unlockedEnabled, reason);
      } 
   }
   free(bssTableApiPtr);

   free(cellTablePtr);
   LOG_PRINT(LOG_INFO,"Exiting cellUnlockReq()");
}

void sendCellLockReq(I_U32 cellId, I_U32 lac, I_U32 reason, I_U8 cellIndex)
{

   OamsCfgCellhLockReq sndBuf;
   LOG_PRINT(LOG_INFO,"Entering sendCellLockReq()");

   sndBuf.objType = OAMS_OBJTYPE_CELL;
   sndBuf.objId = cellId;
   sndBuf.lac = lac;
   sndBuf.reason = reason;
   /*Changes PCU R2.5 Aricent -- START*/
   sndBuf.cellIndex = cellIndex;
   /*Changes PCU R2.5 Aricent -- END*/

   updateCellDataStruct(cellId,lac,lockeOrDisableInProgress,reason);
   cfgSendMessage(&sndBuf, sizeof(OamsCfgCellhLockReq), ENT_OAMS_CELLH, OAMS_CFG_CELLH_LOCK_REQ, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendCellLockReq()");
}

void sendCellUnlockReq(I_U32 cellId, I_U32 lac, I_U32 reason, I_U8 cellIndex)
{
   OamsCfgCellhUnlockReq sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendCellUnlockReq()");

   sndPtr.objId = cellId;
   sndPtr.objType = OAMS_OBJTYPE_CELL;
   sndPtr.lac = lac;
   sndPtr.reason = reason;   
   /*Changes PCU R2.5 Aricent -- START*/
   sndPtr.cellIndex = cellIndex;   
   /*Changes PCU R2.5 Aricent -- END*/

   cfgSendMessage(&sndPtr, sizeof(OamsCfgCellhUnlockReq), ENT_OAMS_CELLH, OAMS_CFG_CELLH_UNLOCK_REQ, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendCellUnlockReq()");      
}

/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header*****************************
Function Name   : sendPsCellLockReq()
Parameters      : cellId : cellIdentifier
                  lac : Location Area Code
                  reason : Reson for PsCell Unlock
                  cellIndex : Application used cell identifier
Return type     : void
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
void sendPsCellLockReq(I_U32 cellId, I_U32 lac, I_U32 reason, I_U8 cellIndex)
{

   OamsCfgPschLockReq oamsCfgPschLockReqBuff;

   oamsCfgPschLockReqBuff.lac = lac;
   oamsCfgPschLockReqBuff.cellId = cellId;
   oamsCfgPschLockReqBuff.cellIndex = cellIndex;
   oamsCfgPschLockReqBuff.reason = reason;   

   LOG_PRINT(LOG_INFO,"sending OAMS_CFG_PSCH_LOCK_REQ for Cell [%d] Lac [%d]", cellId, lac);
   cfgSendMessage(&oamsCfgPschLockReqBuff, sizeof(OamsCfgPschUnlockReq), ENT_OAMS_PSCH, OAMS_CFG_PSCH_LOCK_REQ, 0);
   updatePsCellDataState(cellId, lac, TRUE);
}

/********************************* Function  Header*****************************
Function Name   : sendPsCellUnlockReq()
Parameters      : cellId : cellIdentifier
                  lac : Location Area Code
                  reason : Reson for PsCell Unlock
                  cellIndex : Application used cell identifier
Return type     : void
Purpose         : It return CM_SUCCESS if all consisteny checks passes, otherwise 
                  it returns the error code.
Other Note      : 
 *******************************************************************************/
void sendPsCellUnlockReq(I_U32 cellId, I_U32 lac, I_U32 reason, I_U8 cellIndex)
{
   OamsCfgPschUnlockReq oamsCfgPschUnlockReqBuff;
   I_U16 bvcId;
   I_S32 ret = CM_FAILURE;

   oamsCfgPschUnlockReqBuff.lac = lac;
   oamsCfgPschUnlockReqBuff.cellId = cellId;
   oamsCfgPschUnlockReqBuff.cellIndex = cellIndex;
   ret = getBvciIdFromPsCellTable(lac, cellId, &bvcId);
   if(CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_CRITICAL, "Db call getBvciIdFromPsCellTable failed Error Code = [%d]", ret);
      return;
   }
   oamsCfgPschUnlockReqBuff.bvci = bvcId;
   oamsCfgPschUnlockReqBuff.reason = reason;   

   LOG_PRINT(LOG_INFO,"sending OAMS_CFG_PSCH_UNLOCK_REQ for Cell [%d] Lac [%d]", cellId, lac);
   cfgSendMessage(&oamsCfgPschUnlockReqBuff, sizeof(OamsCfgPschUnlockReq), ENT_OAMS_PSCH, OAMS_CFG_PSCH_UNLOCK_REQ, 0);
   updatePsCellDataState(cellId, lac, TRUE);
}
/*Changes PCU R2.5 Aricent -- END*/

I_Void sendPsscmUnlockReq(I_U32 reason) 
{
   OamsCfgPsscmUnlockReq sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendPsscmUnlockReq()");

   sndPtr.reason = reason;
   cfgSendMessage(&sndPtr, sizeof(OamsCfgPsscmUnlockReq), ENT_OAMS_PSSCM, OAMS_CFG_PSSCM_UNLOCK_REQ, 0);
   gGbUnlockReqSent = TRUE;
   LOG_PRINT(LOG_INFO,"Exiting sendPsscmUnlockReq()");
}
/*Changes R2.5.2: Start*/
void sendCellInfoUpdInd(I_U8 cellIndex)
{
   OamsCfgGrhmCellInfoUpdInd sndPtr;
   LOG_PRINT(LOG_INFO, "Entering sendCellInfoUpdInd()");
   sndPtr.cellIndex = cellIndex;
   /* Mantis Fix 14387 */  
   cfgSendMessage(&sndPtr, sizeof(OamsCfgGrhmCellInfoUpdInd), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_CELL_INFO_UPD_IND, 0);
   LOG_PRINT(LOG_INFO, "Exiting sendCellInfoUpdInd()");
}
/*Changes R2.5.2: End*/

void sendCellBlockReq(I_U32 cellId, I_U32 lac, I_U8 cellIndex)
{
   OamsCfgCellhBlockInd sndPtr;
   CellPerTableIndices cellTableIndices;
   CellPerTableApi *cellTablePtr=NULL;

   LOG_PRINT(LOG_INFO,"Entering sendCellBlockReq()");
   cfgSendAckToCm();
   sndPtr.objId = cellId;
   sndPtr.lac = lac;
   /*Changes PCU R2.5 Aricent -- START*/
   sndPtr.cellIndex = cellIndex;
   BssTableApi *bssTable = NULL;
   I_S32 ret = CM_FAILURE;
   I_U32 count = 0;
   I_U16 outSize = 0; 
   /*Changes PCU R2.5 Aricent -- END*/
   cfgSendMessage(&sndPtr, sizeof(OamsCfgCellhBlockInd), ENT_OAMS_CELLH, OAMS_CFG_CELLH_BLOCK_IND, 0);

   sendGrhmStopChanAllocReq(cellId,lac);
   cellTableIndices.cellId = cellId;
   cellTableIndices.lac = lac;

   ret = getallBssTable(&bssTable,&count,&outSize);
   if(CLIB_SUCCESS != ret)
   {
      LOG_PRINT(LOG_MAJOR,"Error getting BSS Table, Error Code = [%d] ", ret);
      return;
   }

   if (getCellPerTable(&cellTableIndices,&cellTablePtr) == CLIB_SUCCESS)
   {
      if(cellTablePtr->psAllowed == PS_ALLOWED && ENABLED == bssTable->gprsEnabled)
      {
/*Changes PCU R2.5 Aricent -- START*/
         LOG_PRINT(LOG_INFO,"PsStatus is enabled , Sending PS Cell Block Indication");
	 sendPsCellShutdownInd(cellId, lac, cellIndex);
         free(cellTablePtr);
/*Changes PCU R2.5 Aricent -- END*/
      }
   }
   free(bssTable);
   updateCellDataStruct(cellId,lac,blockInProgress,OAMS_RSN_OPERATORINITIATED);
   startTimer(cellId,lac);
   LOG_PRINT(LOG_INFO,"Exiting sendCellBlockReq()");
}

void sendGrhmStopChanAllocReq(I_U32 cellId,I_U32 lac)
{

   OamsCfgGrhmStopChanAlloc sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendGrhmStopChanAllocReq()");

   sndPtr.cmdStatus = OAMS_RSN_CELLBLOCK ;
   sndPtr.cellId = cellId;
   //sndPtr.isCellIdPresent = 1;
   sndPtr.lac = lac;
  // sndPtr.isLacPresent = 1;
   /* sndPtr.reason = OAMS_RSN_CELLSHUTDOWN;*/
   sndPtr.reason = OAMS_RSN_OPERATORINITIATED;

   cfgSendMessage(&sndPtr, sizeof(OamsCfgGrhmStopChanAlloc), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_STOP_CHAN_ALLOC, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendGrhmStopChanAllocReq()");
}

void sendGrhmStartChanAllocReq(I_U32 cellId,I_U32 lac)
{

   OamsCfgGrhmStartChanAlloc sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendGrhmStartChanAllocReq()");

   sndPtr.cellId = cellId;
   //sndPtr.isCellIdPresent = 1;
   sndPtr.lac = lac;
   //sndPtr.isLacPresent = 1;
   sndPtr.reason = OAMS_RSN_CELLUP;

   cfgSendMessage(&sndPtr, sizeof(OamsCfgGrhmStartChanAlloc), ENT_CSAPP_GRHM, OAMS_CFG_GRHM_START_CHAN_ALLOC, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendGrhmStartChanAllocReq()");
}

/*Changes PCU R2.5 Aricent -- START*/
/********************************* Function  Header********************************
Function Name:       sendPsCellShutdownInd()
Parameters:          cellId : Cell Identifier
                     lac : Location Area Code
                     cellIndex : Application used cell identifier
Return type:         void
Purpose:             to fetch the state of requested NsvcHandler and call the appropriate 
                     handler acording to its state
Other Note:
 ************************************************************************************/
I_Void sendPsCellShutdownInd(I_U32 cellId, I_U32 lac, I_U8 cellIndex)
{
   OamsCfgPschShutdownInd oamsCfgPschShutdownIndBuf;
   LOG_PRINT(LOG_INFO,"Entering sendPsCellShutdownInd()");

   oamsCfgPschShutdownIndBuf.cellId = cellId;
   oamsCfgPschShutdownIndBuf.lac = lac;   
   oamsCfgPschShutdownIndBuf.cellIndex = cellIndex;
   
   cfgSendMessage(&oamsCfgPschShutdownIndBuf, sizeof(OamsCfgPschShutdownInd), ENT_OAMS_PSCH, OAMS_CFG_PSCH_SHUTDOWN_IND, 0);

   LOG_PRINT(LOG_INFO,"Exiting sendPsCellShutdownInd()");
}

/*Changes PCU R2.5 Aricent -- END*/


I_Void sendPsscmLockReq(I_U32 reason)
{
   OamsCfgPsscmLockReq sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendPsscmLockReq()");
   sndPtr.reason = reason; 

   cfgSendMessage(&sndPtr, sizeof(OamsCfgPsscmLockReq), ENT_OAMS_PSSCM, OAMS_CFG_PSSCM_LOCK_REQ, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendPsscmLockReq()");
}

/*Merger for Mantis #31470*/
I_Void sendPschNseLockReq(I_U16 nsei)
{
   OamsCfgPschNseLockReq sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendPschNseLockReq()");
   sndPtr.nsei = nsei; 

   cfgSendMessage(&sndPtr, sizeof(OamsCfgPschNseLockReq), ENT_OAMS_PSCH, OAMS_CFG_PSCH_NSE_LOCK_REQ, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendPschNseLockReq()");
}

I_Void sendPschNseUnlockReq(I_U16 nsei)
{
   OamsCfgPschNseLockReq sndPtr;
   LOG_PRINT(LOG_INFO,"Entering sendPschNseUnLockReq()");
   sndPtr.nsei = nsei; 

   cfgSendMessage(&sndPtr, sizeof(OamsCfgPschNseUnlockReq), ENT_OAMS_PSCH, OAMS_CFG_PSCH_NSE_UNLOCK_REQ, 0);
   LOG_PRINT(LOG_INFO,"Exiting sendPschNseUnLockReq()");
}
/*Merger for Mantis #31470*/
void initiateCellLockDisableforUnlockedCells()
{
   I_U32 i;
   OamsCfgCellhLockReq oamsCfgCellhLockReqBuf;
   LOG_PRINT(LOG_INFO,"Entering initiateCellLockDisableforUnlockedCells()");
   gCellDisableSent=0;

   gBssSubState = cellsLockInProgress;

   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {

      if (( gCellData[i].Availlability == FALSE ) && (gCellData[i].CellState == unlockedEnabled ))
      {
         oamsCfgCellhLockReqBuf.objType = OAMS_OBJTYPE_CELL;
         oamsCfgCellhLockReqBuf.objId=gCellData[i].CellID;
         oamsCfgCellhLockReqBuf.lac=gCellData[i].lac;
         oamsCfgCellhLockReqBuf.cellIndex = i;
         oamsCfgCellhLockReqBuf.reason = OAMS_RSN_PARENTOBJECTLOCKED;

         cfgSendMessage((void *)&oamsCfgCellhLockReqBuf, sizeof(OamsCfgCellhLockReq), ENT_OAMS_CELLH, OAMS_CFG_CELLH_LOCK_REQ , 0);
         gCellData[i].CellState = lockeOrDisableInProgress;   
         gCellData[i].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
         gCellDisableSent++;
      }
      else if(( gCellData[i].Availlability == FALSE ) && (gCellData[i].CellState == blockInProgress ))
      {
         StopTimerFrmwrk(gTimerId);
         sendCellLockReq(gCellData[i].CellID,gCellData[i].lac,OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK, i);

         gCellData[i].CellState = lockeOrDisableInProgress;   
         gCellData[i].reqType = OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK;
         gCellDisableSent++;
      }
      else if (( gCellData[i].Availlability == FALSE ) && (gCellData[i].CellState == lockeOrDisableInProgress )) 
         /* Mantis 2284 - now this function can be called multiple times */ 
      {
         //removed to not increment counter,
         //gCellDisableSent++;
         LOG_PRINT(DEBUG,"Cell Lock is in progress already: not sending req, cellId:%d,lac:%d",
             gCellData[i].CellID,gCellData[i].lac );
      }
/*Changes PCU R2.5 Aricent --START*/
      /* If BSS Unlock in Progress and PS Cell Unlock Req is sent to PSCH, and BSS Lock is recived this time then
       * send PS Cell Lock Req for those cell immediately and update cellState to lockeOrDisableInProgress */
      //else if (( gCellData[i].Availlability == FALSE ) && (gCellData[i].CellState == unlockOrEnableInProgress) && ( TRUE == gCellData[i].isReqSentForPS ))
      else if (( gCellData[i].Availlability == FALSE ) && (gCellData[i].CellState == unlockOrEnableInProgress) )
      {
         //sendPsCellLockReq(gCellData[i].CellID, gCellData[i].lac, OAMS_RSN_PARENTOBJECTLOCKED, i); 
         LOG_PRINT(DEBUG,"Cell UnLock is in progress sending req, cellId:%d,lac:%d",
             gCellData[i].CellID,gCellData[i].lac );
         sendCellLockReq(gCellData[i].CellID,gCellData[i].lac,OAMS_RSN_BSSLOCKED_DURINGCELLBLOCK, i);
         gCellData[i].CellState = lockeOrDisableInProgress;   
         gCellData[i].reqType = OAMS_RSN_PARENTOBJECTLOCKED;
         gCellDisableSent++;
      }
/*Changes PCU R2.5 Aricent --END*/
   }
   if ( gCellDisableSent == 0 )
   {
      informCellUnLockDisableforUnlckedCellsToBss();
   }
   LOG_PRINT(LOG_INFO,"Exiting initiateCellLockDisableforUnlockedCells()");
}

void initiateCellUnlockEnableforUnlcokedDisabledCells()
{
   I_U32 i;
   CellPerTableIndices CellPerTableIndices;
   CellPerTableApi *cellTable;
   LOG_PRINT(LOG_INFO,"Entering initiateCellUnlockEnableforUnlcokedDisabledCells()");
   gBssSubState = cellsUnlockInProgress;
   gCellEnableSent = 0;
   for ( i = 0; i < CFG_MAX_NUM_CELLS;i++ )
   {
      if ( gCellData[i].CellState == unlockedDisabled)
      {
         CellPerTableIndices.cellId = gCellData[i].CellID;
         CellPerTableIndices.lac = gCellData[i].lac;
         if(getCellPerTable(&CellPerTableIndices,&cellTable) == CLIB_SUCCESS)
         {
            cellUnlockReq(cellTable->cellId,cellTable->lac,OAMS_RSN_PARENTOBJECTLOCKED);
            free(cellTable);
         }
      }
   }
   if ( gCellEnableSent == 0 )
   {
      informCellUnLockEnableforUnlockDisabledCellsToBss();
   }
   LOG_PRINT(LOG_INFO,"Exiting initiateCellUnlockEnableforUnlcokedDisabledCells()");
}


void startTimer(I_U32 cellId,I_U32 lac)
{

   SysAddr slfAddr;
   TmrPayLoad tmrPayLoad;
   BssTableApi *bssTableApiPtr=NULL;
   I_U16 outSize=0;
   I_U32 rowCount=0;
   I_U32 cellBlockTimer;
   LOG_PRINT(LOG_INFO,"Entering startTimer()");
   if(getallBssTable(&bssTableApiPtr,&rowCount,&outSize) == CLIB_SUCCESS)
   {
      cellBlockTimer = bssTableApiPtr->tWaitCellBlock;
      free(bssTableApiPtr);
   }

   /* Create Timer after the time out it will execute cell lock procedure*/
   LOG_PRINT(LOG_INFO,"Value of Cell Block Timer - %d",cellBlockTimer);
   slfAddr.entity= ENT_OAMS_CFG;
   cellIndex = getCellDataStruct(cellId,lac);
//   tmrPayLoad.payLoad[0] = cellIndex;
   tmrPayLoad.payLoad[0] = CELL_BLOCK;
   memcpy(&(tmrPayLoad.payLoad[1]),&(cellIndex),sizeof(I_U8));
   StartTimerFrmwrk(&slfAddr,cellBlockTimer,&tmrPayLoad,&gTimerId);
   LOG_PRINT(LOG_INFO,"Exiting startTimer()");

}

/********************************* Function  Header*****************************
Function Name	: resetCellDataStruct()
Parameters   	: I_U32 : cellId
	 	  I_U32 : lac
Return type   	: I_Void
Purpose      	: This function reset the global data structure of a cell with 
		  the default value 0 corresponding to the received cellId & lac.
Other Note   	: 
********************************************************************************/
I_Void resetCellDataStruct(I_U32 cellId, I_U32 lac)
{
   I_U8 i = 0;

   LOG_PRINT(LOG_INFO,"Entering Function : resetCellDataStruct");
   LOG_PRINT(LOG_DEBUG,"Received cellId = %u, lac = %u", cellId, lac);

   for(i = 0; i < CFG_MAX_NUM_CELLS; i++)
   {
      if((gCellData[i].CellID == cellId) && 
	 (gCellData[i].lac ==  lac)
	)
      {
	 gCellData[i].CellID 		= ZERO;
	 gCellData[i].lac 		= ZERO;
		/*change for Mantis 12800 */
	 //gCellData[i].Availlability	= ZERO;
	 gCellData[i].Availlability	= TRUE;
		/*change for Mantis 12800 ENDS*/
	 gCellData[i].opState		= ZERO;
	 gCellData[i].adminState	= ZERO;
         gCellData[i].CellState 	= ZERO;
         gCellData[i].reqType 		= ZERO;
         gCellData[i].isReqSentForPS    =  FALSE; //MANTIS 16723 CHANGES 
      }
   }

   LOG_PRINT(LOG_INFO,"Exiting Function : resetCellDataStruct");
}

/********************************* Function  Header*****************************
Function Name	: initCellDataStruct()
Parameters   	: I_U32 : cellId
	 	  I_U32 : lac
      I_U16*: cellArrayIndex
Return type   	: I_Void
Purpose      	: This function initialize the global data structure of a cell with 
		  the default values corresponding to the received cellId & lac.
Other Note   	: 
********************************************************************************/
I_Void initCellDataStruct(I_U32 cellId, I_U32 lac, I_U16* cellArrayIndex)
{
   CellPerTableApi *CellTableApiPtr = NULL;
   I_U32 rowCount = ZERO;
   I_U16 outSize = ZERO;
	 I_U16 i=0;
   /*MANTIS 16723 CHANGES STARTS */
   LOG_PRINT(LOG_DEBUG,"Entering Function : initCellDataStruct,Received cellId = %u, lac = %u", cellId, lac);

	/*For Mantis 12800 START */
	for(i = 0 ; i < CFG_MAX_NUM_CELLS; i++)	
	{
	 if(gCellData[i].Availlability == TRUE)	
		{
			gCellData[i].Availlability	=  FALSE;
      gCellData[i].CellState      	=  locked;
      gCellData[i].CellID 	  	=  cellId;
      gCellData[i].adminState	=  locked;
      gCellData[i].lac 		=  lac;
      gCellData[i].reqType		=  ZERO;         
      gCellData[i].isReqSentForPS    =  FALSE; 
      *cellArrayIndex=i;  
			break;
		}
   /*MANTIS 16723 CHANGES ENDS */

	}
   		LOG_PRINT(LOG_INFO,"Exiting Function : initCellDataStruct with cellArrayIndex %d",*cellArrayIndex);
      free(CellTableApiPtr);
		/*For Mantis 12800 ENDS */
   }


                  /*Changes for CS4.0 : Abis E1 Lock/Unlock Start*/
/********************************* Function  Header*****************************
Function Name	: e1LockRespHandler()
Parameters   	: 
Return type   	: I_Void
Purpose      	: This function handel the Abis E1 Lock response from CellH.
Other Note   	: 
********************************************************************************/

I_Void e1LockRespHandler()
{
   OamsCellhCfgAbisE1LockResp *oamsCellhCfgAbisE1LockRespPtr = NULL;
   oamsCellhCfgAbisE1LockRespPtr = (OamsCellhCfgAbisE1LockResp *)( ((I_U8 *)gCfgMsgBuf));   
   LOG_PRINT(LOG_INFO,"e1LockRespHandler: Entering in Function ");
   gE1Data[oamsCellhCfgAbisE1LockRespPtr->e1Id].e1CellLockReqSent--;
   if(gE1Data[oamsCellhCfgAbisE1LockRespPtr->e1Id].e1CellLockReqSent == 0 &&
         gE1Data[oamsCellhCfgAbisE1LockRespPtr->e1Id].waitingForCellUnlockRespCounter == 0)
   {
      updateAbisE1StateInDBAndSendAlarm(oamsCellhCfgAbisE1LockRespPtr->e1Id, LOCKED);
   }
   LOG_PRINT(LOG_INFO,"e1LockRespHandler: Exiting from Function ");
   
}

/********************************* Function  Header*****************************
Function Name	: e1UnlockRespHandler()
Parameters   	: 
Return type   	: I_Void
Purpose      	: This function handel the Abis E1 Unlock response from CellH.
Other Note   	: 
********************************************************************************/

I_Void e1UnlockRespHandler()
{
   OamsCellhCfgAbisE1UnlockResp *oamsCellhCfgAbisE1UnlockRespPtr = NULL;
   oamsCellhCfgAbisE1UnlockRespPtr = (OamsCellhCfgAbisE1UnlockResp *)( ((I_U8 *)gCfgMsgBuf));   
   LOG_PRINT(LOG_INFO,"e1UnlockRespHandler: Entering in Function ");
   gE1Data[oamsCellhCfgAbisE1UnlockRespPtr->e1Id].e1CellUnlockReqSent--;
   LOG_PRINT(LOG_DEBUG,"e1CellUnlockReqSent:: %d,  waitingForCellUnlockRespCounter:: %d",gE1Data[oamsCellhCfgAbisE1UnlockRespPtr->e1Id].e1CellUnlockReqSent,  gE1Data[oamsCellhCfgAbisE1UnlockRespPtr->e1Id].waitingForCellUnlockRespCounter);
   if(gE1Data[oamsCellhCfgAbisE1UnlockRespPtr->e1Id].e1CellUnlockReqSent == 0 &&
         gE1Data[oamsCellhCfgAbisE1UnlockRespPtr->e1Id].waitingForCellUnlockRespCounter == 0)
   {
      LOG_PRINT(LOG_DEBUG,"e1UnlockRespHandler: Updating E1 State ");
      updateAbisE1StateInDBAndSendAlarm(oamsCellhCfgAbisE1UnlockRespPtr->e1Id, UNLOCKED);
   }
   LOG_PRINT(LOG_INFO,"e1UnlockRespHandler: Exiting from Function ");
   
}

                  /*Changes for CS4.0 : Abis E1 Lock/Unlock Ends*/
/*Changes R2.5.2 : Start*/
I_U8 isOnlyFrToHrPerctModified(CellPerTableApi *cellTable,CellPerTableApi *cellTablePtr)
{
   if(cellTable->antennaId != cellTablePtr->antennaId)
   {
      LOG_PRINT(LOG_INFO,"Antenna ID cannot be changed :: Antenna ID in DB--%u Antenna ID Received--%u",cellTable->antennaId,cellTablePtr->antennaId);
      return FALSE;
   }
   if(cellTable->bcchArfcn != cellTablePtr->bcchArfcn)
   {
      LOG_PRINT(LOG_INFO,"Bcch Arfcn cannot be changed :: Bcch Arfcn in DB--%u Bcch Arfcn Received--%u",cellTable->bcchArfcn,cellTablePtr->bcchArfcn);
      return FALSE;
   }
   if(cellTable->freqBandBcch != cellTablePtr->freqBandBcch)
   {
      LOG_PRINT(LOG_INFO,"Band cannot be changed :: Band in DB--%u Band Received--%u",cellTable->freqBandBcch,cellTablePtr->freqBandBcch);
      return FALSE;
   }
   if(cellTable->bcc != cellTablePtr->bcc)
   {
      LOG_PRINT(LOG_INFO,"Bcc cannot be changed :: bcc in DB--%u bcc Received--%u",cellTable->bcc,cellTablePtr->bcc);
      return FALSE;
   }
   if(cellTable->bcchPwr != cellTablePtr->bcchPwr)
   {
      LOG_PRINT(LOG_INFO,"bcchPwr cannot be changed :: bcchPwr in DB--%u bcchPwr Received--%u",cellTable->bcchPwr,cellTablePtr->bcchPwr);
      return FALSE;
   }
   if(cellTable->msTxPwrMax != cellTablePtr->msTxPwrMax)
   {
      LOG_PRINT(LOG_INFO,"msTxPwrMax cannot be changed :: msTxPwrMax in DB--%u msTxPwrMax Received--%u",cellTable->msTxPwrMax,cellTablePtr->msTxPwrMax);
      return FALSE;
   }
   if(cellTable->msTxPowerMaxCch != cellTablePtr->msTxPowerMaxCch)
   {
      LOG_PRINT(LOG_INFO,"msTxPowerMaxCch cannot be changed :: msTxPowerMaxCch in DB--%u msTxPowerMaxCch Received--%u",cellTable->msTxPowerMaxCch,cellTablePtr->msTxPowerMaxCch);
      return FALSE;
   }
   if(cellTable->fnOffset != cellTablePtr->fnOffset)
   {
      LOG_PRINT(LOG_INFO,"fnOffset cannot be changed :: fnOffset in DB--%u fnOffset Received--%u",cellTable->fnOffset,cellTablePtr->fnOffset);
      return FALSE;
   }
   if(cellTable->psAllowed != cellTablePtr->psAllowed)
   {
      LOG_PRINT(LOG_INFO,"psAllowed cannot be changed :: psAllowed in DB--%u psAllowed Received--%u",cellTable->psAllowed,cellTablePtr->psAllowed);
      return FALSE;
   }
   if(cellTable->cellBarAccess != cellTablePtr->cellBarAccess)
   {
      LOG_PRINT(LOG_INFO,"cellBarAccess cannot be changed :: cellBarAccess in DB--%u LAC Received--%u",cellTable->cellBarAccess,cellTablePtr->cellBarAccess);
      return FALSE;
   }
   if(cellTable->accessCtrlClass != cellTablePtr->accessCtrlClass)
   {
      LOG_PRINT(LOG_INFO,"accessCtrlClass cannot be changed :: accessCtrlClass in DB--%u accessCtrlClass Received--%u",cellTable->accessCtrlClass,cellTablePtr->accessCtrlClass);
      return FALSE;
   }
   if(cellTable->bsAgBlksRes != cellTablePtr->bsAgBlksRes)
   {
      LOG_PRINT(LOG_INFO,"bsAgBlksRes cannot be changed :: bsAgBlksRes in DB--%u bsAgBlksRes Received--%u",cellTable->bsAgBlksRes,cellTablePtr->bsAgBlksRes);
      return FALSE;
   }
   if(cellTable->bsPaMfrms != cellTablePtr->bsPaMfrms)
   {
      LOG_PRINT(LOG_INFO,"bsPaMfrms cannot be changed :: bsPaMfrms in DB--%u bsPaMfrms Received--%u",cellTable->bsPaMfrms,cellTablePtr->bsPaMfrms);
      return FALSE;
   }
   if(cellTable->cellReselectHysteresis != cellTablePtr->cellReselectHysteresis)
   {
      LOG_PRINT(LOG_INFO,"cellReselectHysteresis cannot be changed :: cellReselectHysteresis in DB--%u cellReselectHysteresis Received--%u",cellTable->cellReselectHysteresis,cellTablePtr->cellReselectHysteresis);
      return FALSE;
   }
   if(cellTable->rxLevAccessMin != cellTablePtr->rxLevAccessMin)
   {
      LOG_PRINT(LOG_INFO,"rxLevAccessMin cannot be changed :: rxLevAccessMin in DB--%u rxLevAccessMin Received--%u",cellTable->rxLevAccessMin,cellTablePtr->rxLevAccessMin);
      return FALSE;
   }
   if(cellTable->powerOffset != cellTablePtr->powerOffset)
   {
      LOG_PRINT(LOG_INFO,"powerOffset cannot be changed :: powerOffset in DB--%u powerOffset Received--%u",cellTable->powerOffset,cellTablePtr->powerOffset);
      return FALSE;
   }
   if(cellTable->cbq != cellTablePtr->cbq)
   {
      LOG_PRINT(LOG_INFO,"cbq cannot be changed :: cbq in DB--%u cbq Received--%u",cellTable->cbq,cellTablePtr->cbq);
      return FALSE;
   }
   if(cellTable->cellReselectOffset != cellTablePtr->cellReselectOffset)
   {
      LOG_PRINT(LOG_INFO,"cellReselectOffset cannot be changed :: cellReselectOffset in DB--%u cellReselectOffset Received--%u",cellTable->cellReselectOffset,cellTablePtr->cellReselectOffset);
      return FALSE;
   }
   if(cellTable->tempOffset != cellTablePtr->tempOffset)
   {
      LOG_PRINT(LOG_INFO,"tempOffset cannot be changed :: tempOffset in DB--%u tempOffset Received--%u",cellTable->tempOffset,cellTablePtr->tempOffset);
      return FALSE;
   }
   if(cellTable->penalityTime != cellTablePtr->penalityTime)
   {
      LOG_PRINT(LOG_INFO,"penalityTime cannot be changed :: penalityTime in DB--%u penalityTime Received--%u",cellTable->penalityTime,cellTablePtr->penalityTime);
      return FALSE;
   }
   if(0 != memcmp(cellTable->cellName, cellTablePtr->cellName,25))
   {
      LOG_PRINT(LOG_INFO,"cellName cannot be changed :: cellName in DB--%s cellName Received--%s",cellTable->cellName,cellTablePtr->cellName);
      return FALSE;
   }
   if(cellTable->amrSupport != cellTablePtr->amrSupport)
   {
      LOG_PRINT(LOG_INFO,"amrSupport cannot be changed :: amrSupport in DB--%u amrSupport Received--%u",cellTable->amrSupport,cellTablePtr->amrSupport);
      return FALSE;
   }
   if(cellTable->initialAmrCodecRate != cellTablePtr->initialAmrCodecRate)
   {
      LOG_PRINT(LOG_INFO,"initialAmrCodecRate cannot be changed :: initialAmrCodecRate in DB--%u initialAmrCodecRate Received--%u",cellTable->initialAmrCodecRate,cellTablePtr->initialAmrCodecRate);
      return FALSE;
   }
   if(cellTable->frToHrSwitchPerct == cellTablePtr->frToHrSwitchPerct)
   {
      LOG_PRINT(LOG_INFO,"frToHrSwitchPerct has not changed :: frToHrSwitchPerct in DB--%u frToHrSwitchPerct Received--%u",cellTable->frToHrSwitchPerct,cellTablePtr->frToHrSwitchPerct);
      return FALSE;
   }
   return TRUE;
}
/*Changes R2.5.2 : End*/


/* KPI PHASE-II Changes Starts*/

 /******************************* Function  Header*****************************
   Function Name :  updateRadioNwAvlbltyTblAtSysStartup()
Parameters    : None
Return type   : I_Void
Purpose       : update RadioNetworkAvalabilityPMTable for all the Cells configured at 
StartUp
Other Note    : Added For KPI Phase II 
*****************************************************************************/
I_Void updateRadioNwAvlbltyTblAtSysStartup()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     CellPerTableApi                  *cellTableData;
     CellPerTableApi                  *tempcellTableData;
     RadioNwAvalabilityPMTableApi     radioNwAvlbltyTable;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     time_t                           currTime;
     I_Bool                           insertStatus=I_FALSE;
     I_U16 lac_i = 0;
     I_U32 cellDownStartTime;
     

     retCode = getallCellPerTable( &cellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating RadioNetworkAvalabilityTable at StartUp");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallCellPerTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
             tempcellTableData = (CellPerTableApi*)((I_U8*)cellTableData + index*outSize);
             retCode=getRadioNwAvalabilityPmTableOnSecIndices((I_U16)tempcellTableData->lac,
             tempcellTableData->cellId);
             if(retCode==CLIB_SUCCESS)
             {
              LOG_PRINT(LOG_DEBUG,"Entry Already Exist for Cell %d Lac %d so not doing again",
              tempcellTableData->cellId,tempcellTableData->lac);
             }
             else
             {

              /*Mantis:0015409 fix start */ 
              lac_i = (I_U16)tempcellTableData->lac;
              currTime=time(NULL);
              cellDownStartTime = (I_U32) currTime;
              retCode = insertCellDownStartTime(lac_i,tempcellTableData->cellId,
                 cellDownStartTime, &gdummyIndexRNATbl);
              LOG_PRINT(DEBUG,"insertCellDownStartTime has ret:%d", retCode); 
               
#if 0
             radioNwAvlbltyTable.dummyIndex=++gdummyIndexRNATbl;
             radioNwAvlbltyTable.cellId=tempcellTableData->cellId;
             radioNwAvlbltyTable.lac=(I_U16)tempcellTableData->lac;
             currTime=time(NULL);
             radioNwAvlbltyTable.cellDownStartTime=(I_U32)(currTime);
             radioNwAvlbltyTable.cellDownEndTime=ZERO;
             insertStatus=I_FALSE;
             while (insertStatus==I_FALSE)
              {             
             retCode=insertRadioNwAvalabilityPMTable(&radioNwAvlbltyTable);
             if(retCode != CLIB_SUCCESS)
                {
                if(retCode==DBLIBERR_DIO_UNIQUENESS_FAILED)
                  {
                   LOG_PRINT(LOG_DEBUG,"DB insert Failed at index %d, trying again at index %d",gdummyIndexRNATbl,(gdummyIndexRNATbl+1));
                  radioNwAvlbltyTable.dummyIndex=++gdummyIndexRNATbl;
                  }
                  else
                  {
                  LOG_PRINT(LOG_CRITICAL,"DB insert Failed with err %s",clib_strerror(retCode));
                  insertStatus=I_TRUE;
                  }
                }  
             else
               {
                   LOG_PRINT(LOG_DEBUG,"DB insert Success  for Cell %d, lac %d at index %d",
                   radioNwAvlbltyTable.cellId,radioNwAvlbltyTable.lac,gdummyIndexRNATbl);
                   insertStatus=I_TRUE;
               }
              }

#endif             
              /*Mantis:0015409 fix end*/ 
             }  
           }
        free(cellTableData);
             
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       

 /******************************* Function  Header*****************************
   Function Name :  updateRadioNwAvlbltyTblAtAifDown()
Parameters    : None
Return type   : I_Void
Purpose       : update RadioNetworkAvalabilityPMTable for all the Cells configured at Aif Down
Other Note    : Added For KPI Phase II 
*****************************************************************************/
I_Void updateRadioNwAvlbltyTblAtAifDown()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     CellNonPerTableApi               *cellTableData;
     CellNonPerTableApi               *tempcellTableData;
     RadioNwAvalabilityPMTableApi     radioNwAvlbltyTable;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     time_t                           currTime;
     I_Bool                           insertStatus=I_FALSE;
     I_U16 lac_i = 0;
     I_U32 cellDownStartTime;

     retCode = getallCellNonPerTable( &cellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating RadioNetworkAvalabilityTable at Aif Down");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallCellNonPerTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
             tempcellTableData = (CellNonPerTableApi*)((I_U8*)cellTableData + index*outSize);
             if(tempcellTableData->oprState!=ENABLED)
             {
             LOG_PRINT(LOG_DEBUG,"Cell %d Lac %d is disabled,Entry Already done,not doing again",
                tempcellTableData->cellId,tempcellTableData->lac);
             } 
             else
             {  
              /*Mantis:0015409 fix start */ 
              lac_i = (I_U16)tempcellTableData->lac;
              currTime=time(NULL);
              cellDownStartTime = (I_U32) currTime;
              retCode = insertCellDownStartTime(lac_i,tempcellTableData->cellId,
                 cellDownStartTime, &gdummyIndexRNATbl);
              LOG_PRINT(DEBUG,"insertCellDownStartTime has ret:%d", retCode); 
#if 0
             radioNwAvlbltyTable.dummyIndex=++gdummyIndexRNATbl;
             radioNwAvlbltyTable.cellId=tempcellTableData->cellId;
             radioNwAvlbltyTable.lac=(I_U16)tempcellTableData->lac;
             currTime=time(NULL);
             radioNwAvlbltyTable.cellDownStartTime=(I_U32)(currTime);
             radioNwAvlbltyTable.cellDownEndTime=ZERO;
             insertStatus=I_FALSE;
             while (insertStatus==I_FALSE)
              {             
             retCode=insertRadioNwAvalabilityPMTable(&radioNwAvlbltyTable);
             if(retCode != CLIB_SUCCESS)
                {
                if(retCode==DBLIBERR_DIO_UNIQUENESS_FAILED)
                  {
                   LOG_PRINT(LOG_DEBUG,"DB insert Failed at index %d, trying again at index %d",gdummyIndexRNATbl,(gdummyIndexRNATbl+1));
                  radioNwAvlbltyTable.dummyIndex=++gdummyIndexRNATbl;
                  }
                  else
                  {
                  LOG_PRINT(LOG_CRITICAL,"DB insert Failed with err %s",clib_strerror(retCode));
                  insertStatus=I_TRUE;
                  }
                }  
             else
               {
                   LOG_PRINT(LOG_DEBUG,"DB insert Success  for Cell %d, lac %d at index %d",
                   radioNwAvlbltyTable.cellId,radioNwAvlbltyTable.lac,gdummyIndexRNATbl);
                   insertStatus=I_TRUE;
               }
              }  
#endif 
              /*Mantis:0015409 fix end*/ 
             }
            }/*end of For Loop*/ 
        free(cellTableData);
             
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       

/******************************* Function  Header*****************************
Function Name : updateRadioNwAvlbltyTblAtCellEnableUnbarred()
Parameters    : None
Return type   : I_Void
Purpose       : update RadioNetworkAvalabilityPMTable for Enabled/Unbarred Cell 
Other Note    : Added For KPI Phase II
*****************************************************************************/
I_Void updateRadioNwAvlbltyTblAtCellEnableUnbarred(I_U32 cellId, I_U32 lac)
{
     LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
     
     I_S32                            retCode;
     time_t                           currTime;
     
     currTime=time(NULL);
     retCode = updateCellDownEndTime((I_U16)lac,cellId,(I_U32) currTime);
     if( retCode != CLIB_SUCCESS)
       {
       if(retCode==DBLIBERR_BASEDAO_NO_INDEX_ENTRY)
         {
         LOG_PRINT(LOG_MAJOR,"No Entry found in DB RadioNetworkAvalabilityTable for cell %d, lac %d",
             cellId, lac);
         }
       else
         {
         LOG_PRINT(LOG_CRITICAL,"DB call updateCellDownEndTime Failed for Cell %d Lac %d, err %s ",
             cellId,lac,clib_strerror(retCode));
         }
       }
     else
       {
       LOG_PRINT(LOG_DEBUG,"DB call updateCellDownEndTime Success for Cell %d, lac %d ",cellId,
           lac);
       }
     
         LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}


 /******************************* Function  Header*****************************
   Function Name :  updateRadioNwAvlbltyTblAtCellDisable()
Parameters    : None
Return type   : I_Void
Purpose       : update RadioNetworkAvalabilityPMTable for Disabled  Cell
Other Note    : Added For KPI Phase II 
*****************************************************************************/
I_Void updateRadioNwAvlbltyTblAtCellDisable(I_U32 cellId, I_U32 lac)
{
    LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
    RadioNwAvalabilityPMTableApi     radioNwAvlbltyTable;
    I_S32                            retCode;
    time_t                           currTime;
    I_Bool                           insertStatus=I_FALSE;
    I_U16 lac_i;
    I_U32 cellDownStartTime;  
    
    lac_i = (I_U16) lac;
    currTime=time(NULL);
    cellDownStartTime = (I_U32) currTime;

    /*Mantis:0015409 fix start */ 
    retCode = insertCellDownStartTime(lac_i,cellId,cellDownStartTime, &gdummyIndexRNATbl);
    LOG_PRINT(DEBUG,"insertCellDownStartTime has ret:%d", retCode); 
 
#if 0
     radioNwAvlbltyTable.dummyIndex=++gdummyIndexRNATbl;
     radioNwAvlbltyTable.cellId=cellId;
     radioNwAvlbltyTable.lac=(I_U16)lac;
     currTime=time(NULL);
     radioNwAvlbltyTable.cellDownStartTime=(I_U32)(currTime);
     radioNwAvlbltyTable.cellDownEndTime=ZERO;
     while(insertStatus==I_FALSE)
          {             
          retCode=insertRadioNwAvalabilityPMTable(&radioNwAvlbltyTable);
          if(retCode != CLIB_SUCCESS)
            {
            if(retCode==DBLIBERR_DIO_UNIQUENESS_FAILED)
              {
              LOG_PRINT(LOG_DEBUG,"DB insert Failed at index %d, trying again at index %d",
              gdummyIndexRNATbl,(gdummyIndexRNATbl+1));
              radioNwAvlbltyTable.dummyIndex=++gdummyIndexRNATbl;
              }
            else
              {
              LOG_PRINT(LOG_CRITICAL,"DB insert Failed with err %s",clib_strerror(retCode));
              insertStatus=I_TRUE;
              }
            }  
          else
            {
            LOG_PRINT(LOG_DEBUG,"DB insert Success  for Cell %d, lac %d at index %d",
            radioNwAvlbltyTable.cellId,radioNwAvlbltyTable.lac,gdummyIndexRNATbl);
            insertStatus=I_TRUE;
            }
          }  
#endif
    /*Mantis:0015409 fix end*/ 
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       
 
 /******************************* Function  Header*****************************
   Function Name :  updateRadioNwAvlbltyTblAtAifUp()
Parameters    : None
Return type   : I_Void
Purpose       : update RadioNetworkAvalabilityPMTable for all the Cells configured at 
Aif Up
Other Note    : Added For KPI Phase II 
*****************************************************************************/
I_Void updateRadioNwAvlbltyTblAtAifUp()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     CellNonPerTableApi               *cellTableData;
     CellNonPerTableApi               *tempcellTableData;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     

     retCode = getallCellNonPerTable( &cellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating RadioNetworkAvalabilityTable at Aif Up");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallCellNonPerTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
               tempcellTableData = (CellNonPerTableApi*)((I_U8*)cellTableData + index*outSize);
               if(tempcellTableData->oprState!=ENABLED)
               {
               LOG_PRINT(LOG_DEBUG,"Cell %d Lac %d is disabled,not updating CelldownEndTime",
               tempcellTableData->cellId,tempcellTableData->lac);
               }
               else
               {
               LOG_PRINT(LOG_DEBUG,"calling fn updateRadioNwAvlbltyTblAtCellEnableUnbarred for Cell                %d, lac %d",tempcellTableData->cellId,tempcellTableData->lac);
               updateRadioNwAvlbltyTblAtCellEnableUnbarred(tempcellTableData->cellId,
               (I_U32)tempcellTableData->lac);
               }
             }
        free(cellTableData); 
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}
/* KPI PHASE-II Changes Ends*/
/* KPI  PSCELL Changes Starts*/

 /******************************* Function  Header*****************************
   Function Name : updateDataAvlbltyTblAtSysStartup()
   Parameters    : None
   Return type   : I_Void
   Purpose       : updateDataAvalabilityPMTable for all the Cells configured at 
   StartUp
   Other Note    : Added For KPI PSCELL 
*****************************************************************************/
I_Void updateDataAvlbltyTblAtSysStartup()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     CellPerTableApi                  *cellTableData;
     CellPerTableApi                  *tempcellTableData;
     DataAvalabilityPMTableApi     dataAvlbltyTable;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     time_t                           currTime;
     I_Bool                           insertStatus=I_FALSE;
     I_U16 lac_i = 0;
     I_U32 pscellDownStartTime;
     

     retCode = getallCellPerTable( &cellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System at StartUp");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallCellPerTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
             tempcellTableData = (CellPerTableApi*)((I_U8*)cellTableData + index*outSize);
             if(PS_ALLOWED == tempcellTableData->psAllowed){
                LOG_PRINT(LOG_DEBUG,"tempcellTableData->lac = %d ,tempcellTableData->cellId =%d",tempcellTableData->lac, tempcellTableData->cellId);
                retCode=getDataAvalabilityPmTableOnSecIndices((I_U16)tempcellTableData->lac,
                tempcellTableData->cellId);
                if(retCode==CLIB_SUCCESS)
                {
                   LOG_PRINT(LOG_DEBUG,"Entry Already Exist for Cell %d Lac %d so not doing again",
                   tempcellTableData->cellId,tempcellTableData->lac);
                }
               else
               {
                  lac_i = (I_U16)tempcellTableData->lac;
                  currTime=time(NULL);
                  pscellDownStartTime = (I_U32) currTime;
                  retCode = insertPsCellDownStartTime(lac_i,tempcellTableData->cellId,
                  pscellDownStartTime, &gdummyIndexDataATbl);
                  LOG_PRINT(DEBUG,"insertPsCellDownStartTime has ret:%d", retCode); 
               
               }
             }//end PS_ALLOWED
           }//end for loop outCount
        free(cellTableData);
             
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       

 /******************************* Function  Header*****************************
   Function Name :  updateDataAvlbltyTblAtGbDown()
   Parameters    : None
   Return type   : I_Void
   Purpose       : update DataAvalabilityPMTable for all the PsCells configured at Gb Down
*****************************************************************************/
I_Void updateDataAvlbltyTblAtGbDown()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     PsCellStatusTableApi               *pscellTableData;
     PsCellStatusTableApi               *tempcellTableData;
     DataAvalabilityPMTableApi        dataAvlbltyTable;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     time_t                           currTime;
     I_Bool                           insertStatus=I_FALSE;
     I_U16 lac_i = 0;
     I_U32 pscellDownStartTime;

     retCode = getallPsCellStatusTable( &pscellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating DataAvalabilityTable at Gb Down");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallPsCellStatusTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
             tempcellTableData = (PsCellStatusTableApi*)((I_U8*)pscellTableData + index*outSize);
             if(tempcellTableData->oprState!=ENABLED)
             {
             LOG_PRINT(LOG_DEBUG,"Cell %d Lac %d is disabled,Entry Already done,not doing again",
                tempcellTableData->cellId,tempcellTableData->lac);
             } 
             else
             {  
              lac_i = (I_U16)tempcellTableData->lac;
              currTime=time(NULL);
              pscellDownStartTime = (I_U32) currTime;
              retCode = insertPsCellDownStartTime(lac_i,tempcellTableData->cellId,
                 pscellDownStartTime, &gdummyIndexDataATbl);
              LOG_PRINT(DEBUG,"insertPsCellDownStartTime has ret:%d", retCode); 
             }
            }/*end of For Loop*/ 
        free(pscellTableData);
             
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       

/******************************* Function  Header*****************************
Function Name : updateDataAvlbltyTblAtPsCellEnableUnbarred()
Parameters    : None
Return type   : I_Void
Purpose       : update DataAvalabilityPMTable for Enabled/Unbarred PsCell 
Other Note    : Added For KPI Phase II
*****************************************************************************/
I_Void updateDataAvlbltyTblAtPsCellEnableUnbarred(I_U32 cellId, I_U32 lac)
{
     LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
     
     I_S32                            retCode;
     time_t                           currTime;
     
     currTime=time(NULL);
     retCode = updatePsCellDownEndTime((I_U16)lac,cellId,(I_U32) currTime);
     if( retCode != CLIB_SUCCESS)
       {
       if(retCode==DBLIBERR_BASEDAO_NO_INDEX_ENTRY)
         {
         LOG_PRINT(LOG_MAJOR,"No Entry found in DB DataAvalabilityTable for cell %d, lac %d",
             cellId, lac);
         }
       else
         {
         LOG_PRINT(LOG_CRITICAL,"DB call updatePsCellDownEndTime Failed for Cell %d Lac %d, err %s ",
             cellId,lac,clib_strerror(retCode));
         }
       }
     else
       {
       LOG_PRINT(LOG_DEBUG,"DB call updatePsCellDownEndTime Success for Cell %d, lac %d ",cellId,
           lac);
       }
     
         LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}


 /******************************* Function  Header*****************************
   Function Name :  updateDataAvlbltyTblAtPsCellDisable()
Parameters    : None
Return type   : I_Void
Purpose       : update DataAvalabilityPMTable for Disabled  Cell
*****************************************************************************/
I_Void updateDataAvlbltyTblAtPsCellDisable(I_U32 cellId, I_U32 lac)
{
    LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
    DataAvalabilityPMTableApi     dataAvlbltyTable;
    I_S32                            retCode;
    time_t                           currTime;
    I_Bool                           insertStatus=I_FALSE;
    I_U16 lac_i;
    I_U32 pscellDownStartTime;  
    
    lac_i = (I_U16) lac;
    currTime=time(NULL);
    pscellDownStartTime = (I_U32) currTime;

    retCode = insertPsCellDownStartTime(lac_i,cellId,pscellDownStartTime, &gdummyIndexDataATbl);
    LOG_PRINT(DEBUG,"insertPsCellDownStartTime has ret:%d", retCode); 
 
   LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       
 
 /******************************* Function  Header*****************************
   Function Name :  updateDataAvlbltyTblAtGbifUp()
   Parameters    : None
   Return type   : I_Void
   Purpose       : update DataAvalabilityPMTable for all the PsCells configured at 
   Gbif Up
*****************************************************************************/
I_Void updateDataAvlbltyTblAtGbifUp()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     PsCellStatusTableApi               *pscellTableData;
     PsCellStatusTableApi               *tempcellTableData;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     

     retCode = getallPsCellStatusTable( &pscellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating DataAvalabilityTable at GbIf Up");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallPsCellStatusTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
               tempcellTableData = (PsCellStatusTableApi*)((I_U8*)pscellTableData + index*outSize);
               if(tempcellTableData->oprState!=ENABLED)
               {
               LOG_PRINT(LOG_DEBUG,"Cell %d Lac %d is disabled,not updating PsCelldownEndTime",
               tempcellTableData->cellId,tempcellTableData->lac);
               }
               else
               {
               LOG_PRINT(LOG_DEBUG,"calling fn updateDataAvlbltyTblAtPsCellEnableUnbarred for Cell                %d, lac %d",tempcellTableData->cellId,tempcellTableData->lac);
               updateDataAvlbltyTblAtPsCellEnableUnbarred(tempcellTableData->cellId,
               (I_U32)tempcellTableData->lac);
               }
             }
        free(pscellTableData); 
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}

 /******************************* Function  Header*****************************
   Function Name :  updateDataAvlbltyTblAtAifDown()
   Parameters    : None
   Return type   : I_Void
   Purpose       : update DataAvalabilityPMTable for all the PsCells configured at Gb Down
*****************************************************************************/
I_Void updateDataAvlbltyTblAtAifDown()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     PsCellStatusTableApi               *pscellTableData;
     PsCellStatusTableApi               *tempcellTableData;
     DataAvalabilityPMTableApi        dataAvlbltyTable;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     time_t                           currTime;
     I_Bool                           insertStatus=I_FALSE;
     I_U16 lac_i = 0;
     I_U32 pscellDownStartTime;

     retCode = getallPsCellStatusTable( &pscellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating DataAvalabilityTable at Aif Down");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallPsCellStatusTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
                 tempcellTableData = (PsCellStatusTableApi*)((I_U8*)pscellTableData + index*outSize);
                if(tempcellTableData->oprState!=ENABLED)
                {
                LOG_PRINT(LOG_DEBUG,"Cell %d Lac %d is disabled,Entry Already done,not doing again",
                    tempcellTableData->cellId,tempcellTableData->lac);
                } 
                else
                {  
                    lac_i = (I_U16)tempcellTableData->lac;
                    currTime=time(NULL);
                    pscellDownStartTime = (I_U32) currTime;
                    retCode = insertPsCellDownStartTime(lac_i,tempcellTableData->cellId,
                    pscellDownStartTime, &gdummyIndexDataATbl);
                    LOG_PRINT(DEBUG,"insertPsCellDownStartTime has ret:%d", retCode); 
                }  
            }/*end of For Loop*/ 
        free(pscellTableData);
             
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
}       
 /******************************* Function  Header*****************************
   Function Name :  updateDataAvlbltyTblAtAifUp()
   Parameters    : None
   Return type   : I_Void
   Purpose       : update DataAvalabilityPMTable for all the PsCells configured at 
   Gbif Up
*****************************************************************************/
I_Void updateDataAvlbltyTblAtAifUp()
{
   LOG_PRINT(LOG_INFO,"%s: Entering in function", __func__);
   
     PsCellStatusTableApi               *pscellTableData;
     PsCellStatusTableApi               *tempcellTableData;
     I_U32                            outCount;
     I_U16                            outSize;
     I_S32                            retCode;
     I_U32                            index = ZERO;
     

     retCode = getallPsCellStatusTable( &pscellTableData, &outCount, &outSize);
     if ( retCode != CLIB_SUCCESS)
        {
        if(retCode==DBLIBERR_PTOPAGE_HAS_NO_ROWS)
          {  
          LOG_PRINT(LOG_DEBUG,"No Cell Exists in the System,Not updating DataAvalabilityTable at AIf Up");
          }
        else
          {  
          LOG_PRINT(LOG_CRITICAL,"getallPsCellStatusTable Failed, err %s ",clib_strerror(retCode));
          }
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);
        return;
        }
        for( index=0; index < outCount; index++ )
             {
               tempcellTableData = (PsCellStatusTableApi*)((I_U8*)pscellTableData + index*outSize);
               if(tempcellTableData->oprState!=ENABLED)
               {
               LOG_PRINT(LOG_DEBUG,"Cell %d Lac %d is disabled,not updating PsCelldownEndTime",
               tempcellTableData->cellId,tempcellTableData->lac);
               }
               else
               {
               LOG_PRINT(LOG_DEBUG,"calling fn  updateDataAvlbltyTblAtAifUp for Cell                %d, lac %d",tempcellTableData->cellId,tempcellTableData->lac);
               updateDataAvlbltyTblAtPsCellEnableUnbarred(tempcellTableData->cellId,
               (I_U32)tempcellTableData->lac);
               }
             }
        free(pscellTableData); 
        LOG_PRINT(LOG_INFO,"%s: Exiting from function", __func__);

}
/* KPI PSCELL Changes Ends*/

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change

 ************************************** End *********************************/









