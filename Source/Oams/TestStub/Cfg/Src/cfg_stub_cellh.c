#include <oamcfg_includes.h>



extern int gTestCaseCompleted;
void addbcchChannelGrp();
void addChannelgrp();
void addArfcnList();
void addLacTable();
void addPsCellTable();
void addaddPSExternalCellTable();
void addPSInternalCellTable();
void addRaTable();
void addCSInternalCellTable();
void addCSExternalCellTable();

void cellObjHandler1()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   PsappPcuCfgAlarmInd psappPcuCfgAlarmIndBuff;
   OamsCellhCfgAlarmInd *oamsCellhCfgAlarmIndPtr;

   I_U32 objectIdList[32];

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 1 : cell Lock Request\n");

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 21;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 21;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table UnSuccess Full \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 0; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf("Received Ack Successfully");
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {   
               printf("Received OAMS_CFG_CELLH_LOCK_REQ ");
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCU_LOCK_REQ :
            {
               /*      psappPcuCfgAlarmIndBuff.sysAlarm.alarmId = PSCell_Disabled;
                     psappPcuCfgAlarmIndBuff.sysAlarm.key1 = oamsCfgPcuLockReqPtr->objType;
                     psappPcuCfgAlarmIndBuff.sysAlarm.key2 = oamsCfgPcuLockReqPtr->objId;
                     cfgStubSendPcuCfgAlarmInd(&psappPcuCfgAlarmIndBuff.sysAlarm);
                */
               oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
               cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :    
            {
               oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               //   memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);
            }
            break;
         case AFH_API_ALARM_MSG:
            {   //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.alarmId);
               gTestCaseCompleted = 1;
               printf("bssLockTestCase 1 : Success\n");
            }
            break;
         default:
            printf("undefined Message Type");
      }


   }
}

void cellObjHandler2()
{
   static int testInitiation =1;
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr;
   I_U32 objectIdList[32];
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Unlock Request\n");
      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 21;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");
         }
         else
         {
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      static I_U32 cmApi_response_count =0;

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {

                  if (cmApi_response_count == 0 )
                  {
                     cmApi_response_count++;
                     addbcchChannelGrp();
                     addChannelgrp();

                  }
                  else if(cmApi_response_count ==1)
                  {
                     addArfcnList();
                  }
                  else if(cmApi_response_count ==2)
                  {
                     addLacTable();
                  }
                  else if(cmApi_response_count ==3)
                  {
                     addPsCellTable();
                  }
                  else if(cmApi_response_count ==4)
                  {
                     addRaTable();
                  }
                  else if(cmApi_response_count ==5)
                  {
                     addCSInternalCellTable();
                  }
                  else if(cmApi_response_count ==6)
                  {
                     addCSExternalCellTable();
                  }
                  else if (cmApi_response_count ==7)
                  {                         
                     addPSInternalCellTable();
                  }
                  else if (cmApi_response_count ==7)
                  {                         
                     addaddPSExternalCellTable();
                  }
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
               }


            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {
               oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
               memcpy(objectIdList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCU_UNLOCK_REQ:
            {
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);
               cfgStubSendPcuCfgAlarmInd();
            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);           

            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {
            }
            break;
         case OAMS_CFG_PCU_CELL_ENABLED_REQ :
            {

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;
         case PSAPP_PCU_CFG_ALARM_IND :
            {   
               //PSAPP_PCU_CFG_ALARM_IND alarm received
            }
            break;
      }

      gTestCaseCompleted = 1;

      printf("bssLockTestCase 1 : Success\n");
   }

}

void cellObjHandler3()
{
   static int testInitiation =1;
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr;
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   I_U32 objectIdList[32];
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Unlock Request\n");
      CellTableIndicesBuff.cellId = 11;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 11;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table unsuccess Full \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf("Received Ack Successfully");
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {
               oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
               //memcpy(objectIdList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCU_UNLOCK_REQ  :
            {
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);
            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);           

            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {

            }
            break;
         case OAMS_CFG_PCU_CELL_ENABLED_REQ :
            {

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;
         case PSAPP_PCU_CFG_ALARM_IND :
            {   
               gTestCaseCompleted = 1;
               printf("bssLockTestCase 1 : Success\n");
               //PSAPP_PCU_CFG_ALARM_IND alarm received
            }
            break;
      }

   }

}

void cellObjHandler6()
{
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr ;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
   I_U32 objectIdList[32];
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCellhCfgAlarmInd *oamsCellhCfgAlarmIndPtr;  

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Shutdown Request\n");
      CellTableIndicesBuff.cellId = 41;
      CellTableIndicesBuff.lac = 41;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 41;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 41;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table unsuccessful \n");
         }
      }
      /* Send lock BSS */
      CellTableApiPtr->adminState = 2; /* Shutting down */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf("CM_API_APP_RESPONSE received");            

            }
            break;
         case OAMS_CFG_CELLH_SHUTDOWN_IND :
            {
               printf("CELLH STUB:Cell Shut down indicator received");

            }
            break;
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   :
            {
               printf("GRHM STUB: CFG_GRHM_STOP_CHAN_ALLOC indicator received");            
            }
            break;
         case OAMS_CFG_PCU_CELL_SHUTDOWN_IND  :
            {
               printf("PCU STUB: CFG_PCU_CELL_SHUTDOWN_IND indicator received");   
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {   
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCU_LOCK_REQ :
            {
               oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
               cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :    
            {
               oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               //   memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);
            }
            break;
         case AFH_API_ALARM_MSG:
            {   //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.alarmId);
               gTestCaseCompleted = 1;
               printf("Cell Object handler Test case 6 : Success\n");
            }
            break;

      }

   }

}

void cellObjHandler7()
{
   static int testInitiation =1;
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Shutdown Request\n");
      CellTableIndicesBuff.cellId = 7;
      CellTableIndicesBuff.lac = 7;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         if(updateCellTable(CellTableApiPtr) == CLIB_SUCCESS)
         {
            printf("get Celll Table Success Full \n");
         }
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 7;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 7;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table Unsuccessfull \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 2; /* Shutting down */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {   
                  printf("NAck Receieved \n");
                  gTestCaseCompleted = 1;                           
               }
               else
               {
                  printf("Ack Receieved \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_SHUTDOWN_IND :
            {
               printf("CELLH STUB:Cell Shut down indicator received");
               printf("Sending the Shutdown Message again for the same cell instance");
               CellTableIndicesBuff.cellId = 7;
               CellTableIndicesBuff.lac = 7;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 2; /* Shutting down */
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
               }
            }
            break;
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   :
            {

            }
            break;
         case OAMS_CFG_PCU_CELL_SHUTDOWN_IND   :
            {

            }
            break;
      }

   }

}

void cellObjHandler9()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 9 : cell Unlock Request\n");
      CellTableIndicesBuff.cellId = 9;
      CellTableIndicesBuff.lac = 9;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 9;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 9;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table Unsuccessfull \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("Ack Receieved \n");
               }


            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {


               printf("cellObjHandler9:CFG_PSSCM_UNLOCK_REQ message received\n");
               CellTableIndicesBuff.cellId = 9;
               CellTableIndicesBuff.lac = 9;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 1; /* unlocked */
                  printf("cellObjHandler9:sending the unlock for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
               }
            }
            break;
      }

   }

}

void cellObjHandler10()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 1 : cell Lock Request\n");
      CellTableIndicesBuff.cellId = 9;
      CellTableIndicesBuff.lac = 9;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 9;
         CellTableApiPtr->lac =9;
         CellTableApiPtr->adminState = 1; /* Unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell  Unsuccessfull \n");
         }
      }
      /* Send lock Cell */
      CellTableApiPtr->adminState = 0; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("Ack Receieved \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {
               printf("cellObjHandler10:CFG_PSSCM_LOCK_REQ message received");
               CellTableIndicesBuff.cellId = 9;
               CellTableIndicesBuff.lac = 9;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 0; /* locked */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
               }

            }
            break;
         case OAMS_CFG_PCU_LOCK_REQ :
            {
               cfgStubSendPcuCfgLockResp();
               cfgStubSendPcuCfgAlarmInd();
            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :
            {
               cfgStubSendPsscmCfgLockResp();
            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {   //Check alarm receieved
            }
            break;
      }
   }
}

void cellObjHandler11()
{
   static int testInitiation =1;
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 11 :   \n");
      CellTableIndicesBuff.cellId = 18;
      CellTableIndicesBuff.lac = 18;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 18;
         CellTableApiPtr->lac =18;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");
         }
         else
         {
            printf("Insert CellTable unsuccessfull \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->msTxPwrMax = 9;   /*Parameter Modification*/
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("Ack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 11 : Success\n");
               }
            }
            break;
      }
   }
}


void cellObjHandler12()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 1 : cell Lock Request\n");
      CellTableIndicesBuff.cellId = 19;
      CellTableIndicesBuff.lac = 19;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 19;
         CellTableApiPtr->lac =19;
         CellTableApiPtr->adminState = 1; /* Unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert CellTable unsuccessfull \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->msTxPwrMax = 9;   /*Parameter Modification*/
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 12 : Success\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }
            }
            break;
      }
   }
}


void cellObjHandler13()
{
   static int testInitiation =1;
   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 1 : cell Lock Request\n");
      /* First set the required database */
      CellTableIndicesBuff.cellId = 13;
      CellTableIndicesBuff.lac = 13;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /*locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 13;
         CellTableApiPtr->lac =13;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert CellTable Successfull \n");

         }
         else
         {
            printf("Insert CellTable Unsuccessfull \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* Unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 13 : Success\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {


               printf("cellObjHandler9:CFG_PSSCM_UNLOCK_REQ message received\n");
               CellTableIndicesBuff.cellId = 13;
               CellTableIndicesBuff.lac = 13;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->msTxPwrMax = 8; /* Parameter Modification */
                  printf("cellObjHandler9:sending the parameter Modification for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
               }
            }
            break;
      }
   }
}

void cellObjHandler20()
{
   static int testInitiation =1;
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr;
   I_U32 objectIdList[32];
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Unlock Request\n");
      /* First set the required database */
      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /*locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->lac =1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 21;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");
            free(CellTableApiPtr);

         }
         else
            free(CellTableApiPtr);
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* Unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {

            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {
               oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
               memcpy(objectIdList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCU_UNLOCK_REQ  :
            {
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);
               cfgStubSendPcuCfgAlarmInd();
            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND  :
            {
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);           
               CellTableApiPtr->adminState = 0; /* locked */
               cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);


            }
            break;
         case OAMS_CFG_PCU_CELL_ENABLED_REQ :
            {

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;
         case PSAPP_PCU_CFG_ALARM_IND :
            {   
               //PSAPP_PCU_CFG_ALARM_IND alarm received
            }
            break;
      }

      gTestCaseCompleted = 1;

      printf("bssLockTestCase 1 : Success\n");
   }

}

void cellObjHandler21()
{
   static int testInitiation =1;
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr;
   I_U32 objectIdList[32];
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Unlock Request\n");
      /* First set the required database */
      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         printf("get Celll Table Success Full \n");
         CellTableApiPtr->adminState = 0; /*locked */
         updateCellTable(CellTableApiPtr);
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->lac =1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 21;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");
            free(CellTableApiPtr);

         }
         else
            free(CellTableApiPtr);
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* Unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {

            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {
               oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
               memcpy(objectIdList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType,
                     oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num,
                     0,0,oamsCfgPsscmUnlockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCU_UNLOCK_REQ  :
            {
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);
               cfgStubSendPcuCfgAlarmInd();
            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);           
               CellTableApiPtr->adminState = 1; /* locked */
               cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);


            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {
            }
            break;
         case OAMS_CFG_PCU_CELL_ENABLED_REQ :
            {

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;
         case PSAPP_PCU_CFG_ALARM_IND :
            {   
               //PSAPP_PCU_CFG_ALARM_IND alarm received
            }
            break;
      }

      gTestCaseCompleted = 1;

      printf("bssLockTestCase 1 : Success\n");
   }

}

void cellObjHandler22()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   I_U32 objectIdList[32];
   OamsCellhCfgAlarmInd *oamsCellhCfgAlarmIndPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 1 : cell Lock Request\n");
      CellTableIndicesBuff.cellId = 12;
      CellTableIndicesBuff.lac = 21;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /*unlocked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 12;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 21;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 0;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table UnSuccess Full \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 0; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {

            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {   
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case AFH_API_ALARM_MSG:
            {       //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.alarmId);
               gTestCaseCompleted = 1;
               printf("Cell Obj Handler Test case 22 : Success\n");
            }
            break;

      }
   }
}

void cellObjHandler23()
{
   static int testInitiation =1;
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr;
   I_U32 objectIdList[32];
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCellhCfgAlarmInd *oamsCellhCfgAlarmIndPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Unlock Request\n");
      CellTableIndicesBuff.cellId = 31;
      CellTableIndicesBuff.lac = 31;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /*locked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 31;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 31;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 0;
         CellTableApiPtr->pageStatus = 1;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");
         }
         else
         {
            printf("Insert Cell Table UnSuccess Full \n");
         }
      }

      /* Send lock Cell */
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);


   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {

            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);           

            }
            break;
         case AFH_API_ALARM_MSG:
            {       //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.alarmId);
               gTestCaseCompleted = 1;
               printf("Cell Obj Handler Test case 23 : Success\n");
            }
            break;
      }



   }

}

void cellObjHandler24()
{
   static int testInitiation =1;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr ;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
   I_U32 objectIdList[32];
   OamsCellhCfgAlarmInd *oamsCellhCfgAlarmIndPtr;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("cellLockTestCase 2 : cell Unlock Request\n");
      /* First set the required database */
      CellTableIndicesBuff.cellId = 51;
      CellTableIndicesBuff.lac = 51;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /*unlocked */
         updateCellTable(CellTableApiPtr);
         printf("get Celll Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 51;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 51;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->txPwrMaxRed = 10;
         CellTableApiPtr->msTxPowerMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         CellTableApiPtr->csStatus = 0;
         CellTableApiPtr->psStatus = 0;
         CellTableApiPtr->pageStatus = 0;
         CellTableApiPtr->cellBarAccess = 1;
         CellTableApiPtr->accessCtrlClass = 30;
         CellTableApiPtr->bsAgBlksRes = 5;
         CellTableApiPtr->bsPaMfrms = 5;
         CellTableApiPtr->cellReselectHysteresis = 4;
         CellTableApiPtr->rxLevAccessMin = 63;
         CellTableApiPtr->powerOffset = 1;
         CellTableApiPtr->msTxPwrMax = 10;      
         if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Cell Table Success Full \n");

         }
         else
         {
            printf("Insert Cell Table Unsuccessfull \n");
         }
      }
      /* Send lock BSS */
      CellTableApiPtr->adminState = 2; /* Shutting down */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf("CELLH STUB : Received CM_API_APP_RESPONSE successfully\n");
            }
            break;
         case OAMS_CFG_CELLH_SHUTDOWN_IND :
            {
               printf("CELLH STUB:Cell Shut down indicator received");
            }
            break;
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   :
            {
               printf("CELLH STUB:Cell  OAMS_CFG_GRHM_STOP_CHAN_ALLOC indicator received");

            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {   
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case AFH_API_ALARM_MSG:
            {   //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.alarmId);
               gTestCaseCompleted = 1;
               printf("Cell Object handler Test case 24 : Success\n");
            }
            break;

      }
   }

}


void addbcchChannelGrp()
{
   ChnGrpTableApi* ChnGrpTableApiPtr;
   ChnGrpTableIndices  chnGrpTableIndices;
   chnGrpTableIndices.cellId=1;
   chnGrpTableIndices.lac=1;


   if ( getChnGrpTable(&chnGrpTableIndices, &ChnGrpTableApiPtr) == CLIB_SUCCESS )
   {
      printf("get Channel Group Table Success Full \n");
   }
   else
   {
      ChnGrpTableApiPtr = ( ChnGrpTableApi *)calloc(1,sizeof(ChnGrpTableApi));
      ChnGrpTableApiPtr->chnGrpId = 1;
      ChnGrpTableApiPtr->cellId = 1;
      ChnGrpTableApiPtr->bcchSdcch4 = 0;
      ChnGrpTableApiPtr->bcch = 1;
      ChnGrpTableApiPtr->sdcch8 = 2;
      ChnGrpTableApiPtr->tch = 47;
      ChnGrpTableApiPtr->pdch = 47;
      ChnGrpTableApiPtr->hsn = 30;
      ChnGrpTableApiPtr->maxTxPwr = 20000;
      ChnGrpTableApiPtr->tsc = 5;
      ChnGrpTableApiPtr->band = 0;
      ChnGrpTableApiPtr->validArfcns = 1;
      ChnGrpTableApiPtr->arfcn1 = 124;

      if ( insertChnGrpTable(ChnGrpTableApiPtr) == CLIB_SUCCESS )
      {
         printf("Insert Channel Group Table Success Full \n");
         free(ChnGrpTableApiPtr);

      }
      else
         free(ChnGrpTableApiPtr);
   }
}

void addChannelgrp()
{
   ChnGrpTableApi* ChnGrpTableApiPtr;
   ChnGrpTableIndices  ChnGrpTableIndices;
   ChnGrpTableIndices.cellId=1;
   ChnGrpTableIndices.lac=1;


   if ( getChnGrpTable(&ChnGrpTableIndices, &ChnGrpTableApiPtr) == CLIB_SUCCESS )
   {
      printf("get Channel Group Table Success Full \n");
   }
   else
   {
      ChnGrpTableApiPtr = ( ChnGrpTableApi *)calloc(1,sizeof(ChnGrpTableApi));

      ChnGrpTableApiPtr->chnGrpId = 1;
      ChnGrpTableApiPtr->cellId = 1;
      ChnGrpTableApiPtr->bcchSdcch4 = 1;
      ChnGrpTableApiPtr->bcch = 1;
      ChnGrpTableApiPtr->sdcch8 = 2;
      ChnGrpTableApiPtr->tch = 47;
      ChnGrpTableApiPtr->pdch = 47;
      ChnGrpTableApiPtr->hsn = 30;
      ChnGrpTableApiPtr->maxTxPwr = 20000;
      ChnGrpTableApiPtr->tsc = 5;
      ChnGrpTableApiPtr->band = 0;
      ChnGrpTableApiPtr->validArfcns = 3;
      ChnGrpTableApiPtr->arfcn1 = 150;
      ChnGrpTableApiPtr->arfcn2 = 129;
      ChnGrpTableApiPtr->arfcn3 = 135;


      if ( insertChnGrpTable(ChnGrpTableApiPtr) == CLIB_SUCCESS )
      {
         printf("Insert Channel Group Table Success Full \n");
         free(ChnGrpTableApiPtr);

      }
      else
         free(ChnGrpTableApiPtr);
   }
}

void addbcchSdccchChannelGrp()
{
   ChnGrpTableApi* chnGrpTableApiPtr;
   ChnGrpTableIndices  chnGrpTableIndices;
   chnGrpTableIndices.cellId=1;
   chnGrpTableIndices.lac=1;


   if ( getChnGrpTable(&chnGrpTableIndices, &chnGrpTableApiPtr) == CLIB_SUCCESS )
   {
      printf("get Channel Group Table Success Full \n");
   }
   else
   {
      chnGrpTableApiPtr = ( ChnGrpTableApi *)calloc(1,sizeof(ChnGrpTableApi));

      chnGrpTableApiPtr->chnGrpId = 1;
      chnGrpTableApiPtr->cellId = 1;
      chnGrpTableApiPtr->bcchSdcch4 = 1;
      chnGrpTableApiPtr->bcch = 0;
      chnGrpTableApiPtr->sdcch8 = 2;
      chnGrpTableApiPtr->tch = 47;
      chnGrpTableApiPtr->pdch = 47;
      chnGrpTableApiPtr->hsn = 30;
      chnGrpTableApiPtr->maxTxPwr = 20000;
      chnGrpTableApiPtr->tsc = 5;
      chnGrpTableApiPtr->band = 0;
      chnGrpTableApiPtr->validArfcns = 1;
      chnGrpTableApiPtr->arfcn1 = 124;

      if ( insertChnGrpTable(chnGrpTableApiPtr) == CLIB_SUCCESS )
      {
         printf("Insert Channel Group Table Success Full \n");
         free(chnGrpTableApiPtr);

      }
      else
         free(chnGrpTableApiPtr);
   }
}

void addArfcnList()
{
   ArfcnListTableIndices arfcnListTableIndices;
   ArfcnListTableApi *arfcnListTableApiPtr;

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 124;


   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Arfcn Table Success Full \n");
      free(arfcnListTableApiPtr);

   }
   else
      free(arfcnListTableApiPtr);

   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 150;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Arfcn Group Table Success Full \n");
      free(arfcnListTableApiPtr);

   }
   else
      free(arfcnListTableApiPtr);

   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 129;

   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Arfcn Table Success Full \n");
      free(arfcnListTableApiPtr);

   }
   else
      free(arfcnListTableApiPtr);

   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 135;

   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
      free(arfcnListTableApiPtr);

   }
   else
      free(arfcnListTableApiPtr);

}

void addLacTable()
{
   LaTableApi *laTableApiPtr;

   laTableApiPtr = ( LaTableApi *)calloc(1,sizeof(LaTableApi));

   laTableApiPtr->lac =1;

   if ( insertLaTable(laTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
      free(laTableApiPtr);

   }
   else
      free(laTableApiPtr);
}


void addPsCellTable()
{
   PsCellTableApi *psCellTableApiPtr;
   psCellTableApiPtr = ( PsCellTableApi *)calloc(1,sizeof(PsCellTableApi));

   psCellTableApiPtr->cellId = 1; 
   psCellTableApiPtr->cellBarAccess2 = 1;
   psCellTableApiPtr->raColour = 2;
   psCellTableApiPtr->lac = 1;
   psCellTableApiPtr->pb = FALSE;
   psCellTableApiPtr->rac = 6;
   psCellTableApiPtr->bvciId = 3;
   psCellTableApiPtr->alpha = 10;
   psCellTableApiPtr->tAvgT= 20;
   psCellTableApiPtr->tAvgW = 20;
   psCellTableApiPtr->pb = 0;
   psCellTableApiPtr->pcMeasChan = 1;
   psCellTableApiPtr->panInc = 2;
   psCellTableApiPtr->panDec = 1;
   psCellTableApiPtr->panMax = 7;
   psCellTableApiPtr->priorityAccessThr = 5;
   psCellTableApiPtr->psiCountHr = 8;
   psCellTableApiPtr->psiCountLr = 2;
   psCellTableApiPtr->accContrClass = 1;
   psCellTableApiPtr->maxRetrans1 = 1;
   psCellTableApiPtr->maxRetrans2 = 2;
   psCellTableApiPtr->maxRetrans3 = 4;
   psCellTableApiPtr->maxRetrans4 = 7;
   psCellTableApiPtr->s = 20;
   psCellTableApiPtr->txint = 2;
   psCellTableApiPtr->persistenceLevel = 12;
   psCellTableApiPtr->bsPccRel = 0;
   psCellTableApiPtr->bsPbcchBlks = 1;
   psCellTableApiPtr->bsPagBlksRes = 2;
   psCellTableApiPtr->bsPrachBlks = 3;
   psCellTableApiPtr->intMeasChannelListAvail = 1;
   psCellTableApiPtr->nAvgI = 5;
   psCellTableApiPtr->persistLevel1 = 5;
   psCellTableApiPtr->persistLevel2 = 7;
   psCellTableApiPtr->persistLevel3 = 10;
   psCellTableApiPtr->persistLevel4 = 14;
   psCellTableApiPtr->rflNumber = 3;
   psCellTableApiPtr->cellBarAccess2 = 1;
   psCellTableApiPtr->excAcc = 0;
   psCellTableApiPtr->gprsRxlevAccessMin = 25;
   psCellTableApiPtr->gprsMsTxPwrMaxCch = 30;
   psCellTableApiPtr->gprsGeneralCellReselectHysteresis = 5;
   psCellTableApiPtr->c31Hyst = 0;
   psCellTableApiPtr->c32Qual = 0;
   psCellTableApiPtr->randomAccessRetry = 1;
   psCellTableApiPtr->tresel = 250;
   psCellTableApiPtr->raReselectHysteresis = 1;
   psCellTableApiPtr->psi1RepeatPeriod = 12;
   psCellTableApiPtr->pacchPsiMsgBitMap = 48;
   psCellTableApiPtr->pbcchPsiMsgBitMap = 68;
   psCellTableApiPtr->pccchPsiMsgBitMap = 100;
   psCellTableApiPtr->btsPwrCtrlMode = 1;
   psCellTableApiPtr->prMode = 1;
   psCellTableApiPtr->dlBtsPwrCtrlEnabled = 1 ;
   psCellTableApiPtr->p0 = 2;
   psCellTableApiPtr->numOfPccchInCell = 7;
   psCellTableApiPtr->pccchBitMap = 7;      

   if ( insertPsCellTable(psCellTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Ps cell Table Success Full \n");
      free(psCellTableApiPtr);
   }
   else
      free(psCellTableApiPtr);
}

void addRaTable()
{
   RaTableApi *raTableApiPtr;

   raTableApiPtr->lac = 1;
   raTableApiPtr->rac = 8;
   if ( insertRaTable(raTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Ps cell Table Success Full \n");
      free(raTableApiPtr);
   }
   else
      free(raTableApiPtr);
}

void addCSInternalCellTable()
{   
   CsNeighCellsTableApi *csNeighCellsTableApiPtr;
   CellTableApi* CellTableApiPtr;

   csNeighCellsTableApiPtr = ( CsNeighCellsTableApi *)calloc(1,sizeof(CsNeighCellsTableApi));

   csNeighCellsTableApiPtr->cellId = 2;
   csNeighCellsTableApiPtr->lac = 2;
   csNeighCellsTableApiPtr->cellType = 0;
   csNeighCellsTableApiPtr->neighborCellId = 11;
   csNeighCellsTableApiPtr->neighborLac = 11;
   csNeighCellsTableApiPtr->neighborMcc = 91;
   csNeighCellsTableApiPtr->neighborMnc = 91;
   csNeighCellsTableApiPtr->RelationType = 0;   

   if ( insertCsNeighCellsTable(csNeighCellsTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Cell Table Success Full \n");
      free(csNeighCellsTableApiPtr);

   }
   else
      free(csNeighCellsTableApiPtr);


   CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
   CellTableApiPtr->cellId = 11;
   CellTableApiPtr->lac =11;
   CellTableApiPtr->adminState = 1; /* unlocked */
   CellTableApiPtr->freqBandBcch = 0;
   CellTableApiPtr->lac = 21;
   CellTableApiPtr->bcchArfcn = 34;
   CellTableApiPtr->bcc = 0;
   CellTableApiPtr->txPwrMaxRed = 10;
   CellTableApiPtr->msTxPowerMax = 10;
   CellTableApiPtr->msTxPowerMaxCch = 10;
   CellTableApiPtr->csStatus = 1;
   CellTableApiPtr->psStatus = 1;
   CellTableApiPtr->pageStatus = 1;
   CellTableApiPtr->cellBarAccess = 1;
   CellTableApiPtr->accessCtrlClass = 30;
   CellTableApiPtr->bsAgBlksRes = 5;
   CellTableApiPtr->bsPaMfrms = 5;
   CellTableApiPtr->cellReselectHysteresis = 4;
   CellTableApiPtr->rxLevAccessMin = 63;
   CellTableApiPtr->powerOffset = 1;
   CellTableApiPtr->msTxPwrMax = 10;      
   if ( insertCellTable(CellTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Cell Table Success Full \n");
      free(CellTableApiPtr);

   }
   else
      free(CellTableApiPtr);

}


void addCSExternalCellTable()
{

   CsNeighCellsTableApi *csNeighCellsTableApiPtr;

   CsExternalCellTableApi *csExternalCellTableApiPtr;

   csNeighCellsTableApiPtr = ( CsNeighCellsTableApi *)calloc(1,sizeof(CsNeighCellsTableApi));

   csNeighCellsTableApiPtr->cellId = 22;
   csNeighCellsTableApiPtr->lac = 22;
   csNeighCellsTableApiPtr->cellType = 1;
   csNeighCellsTableApiPtr->neighborCellId = 2;
   csNeighCellsTableApiPtr->neighborLac = 1;
   csNeighCellsTableApiPtr->neighborMcc = 91;
   csNeighCellsTableApiPtr->neighborMnc = 91;
   csNeighCellsTableApiPtr->RelationType = 0;   

   if ( insertCsNeighCellsTable(csNeighCellsTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Cell Table Success Full \n");
      free(csNeighCellsTableApiPtr);

   }
   else
      free(csNeighCellsTableApiPtr);

   csExternalCellTableApiPtr->csExtCellId = 22; 
   csExternalCellTableApiPtr->lac = 22;
   csExternalCellTableApiPtr->mnc = 91;
   csExternalCellTableApiPtr->mcc = 91;
   csExternalCellTableApiPtr->bcc = 1030;
   csExternalCellTableApiPtr->ncc=100;
   csExternalCellTableApiPtr->bcchArfcn = 12;
   csExternalCellTableApiPtr->freqBandBcch = 10;

   if ( insertCsExternalCellTable(csExternalCellTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert csExternalCellTable Table Success Full \n");
      free(csExternalCellTableApiPtr);

   }
   else
      free(csExternalCellTableApiPtr);
}

void addPSInternalCellTable()
{
   PsNeighCellsTableApi *psNeighCellsTableApiPtr;
   PsCellTableApi *psCellTableApiPtr;


   psNeighCellsTableApiPtr = ( PsNeighCellsTableApi *)calloc(1,sizeof(PsNeighCellsTableApi));
   psNeighCellsTableApiPtr->psCellId = 11;
   psNeighCellsTableApiPtr->lac = 11;
   psNeighCellsTableApiPtr->cellType = 0;
   psNeighCellsTableApiPtr->psNeighborCellId = 1;
   psNeighCellsTableApiPtr->psNeighborLac = 1;
   psNeighCellsTableApiPtr->psNeighborMcc = 91;
   psNeighCellsTableApiPtr->psNeighborMnc = 91;
   psNeighCellsTableApiPtr->relationType = 0;
   if ( insertPsNeighCellsTable(psNeighCellsTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert csExternalCellTable Table Success Full \n");
      free(psNeighCellsTableApiPtr);         
   }
   else
      free(psNeighCellsTableApiPtr);

   psCellTableApiPtr = ( PsCellTableApi *)calloc(1,sizeof(PsCellTableApi));

   psCellTableApiPtr->cellId = 11; 
   psCellTableApiPtr->cellBarAccess2 = 11;
   psCellTableApiPtr->raColour = 2;
   psCellTableApiPtr->lac = 1;
   psCellTableApiPtr->pb = FALSE;
   psCellTableApiPtr->rac = 6;
   psCellTableApiPtr->bvciId = 3;
   psCellTableApiPtr->alpha = 10;
   psCellTableApiPtr->tAvgT= 20;
   psCellTableApiPtr->tAvgW = 20;
   psCellTableApiPtr->pb = 0;
   psCellTableApiPtr->pcMeasChan = 1;
   psCellTableApiPtr->panInc = 2;
   psCellTableApiPtr->panDec = 1;
   psCellTableApiPtr->panMax = 7;
   psCellTableApiPtr->priorityAccessThr = 5;
   psCellTableApiPtr->psiCountHr = 8;
   psCellTableApiPtr->psiCountLr = 2;
   psCellTableApiPtr->accContrClass = 1;
   psCellTableApiPtr->maxRetrans1 = 1;
   psCellTableApiPtr->maxRetrans2 = 2;
   psCellTableApiPtr->maxRetrans3 = 4;
   psCellTableApiPtr->maxRetrans4 = 7;
   psCellTableApiPtr->s = 20;
   psCellTableApiPtr->txint = 2;
   psCellTableApiPtr->persistenceLevel = 12;
   psCellTableApiPtr->bsPccRel = 0;
   psCellTableApiPtr->bsPbcchBlks = 1;
   psCellTableApiPtr->bsPagBlksRes = 2;
   psCellTableApiPtr->bsPrachBlks = 3;
   psCellTableApiPtr->intMeasChannelListAvail = 1;
   psCellTableApiPtr->nAvgI = 5;
   psCellTableApiPtr->persistLevel1 = 5;
   psCellTableApiPtr->persistLevel2 = 7;
   psCellTableApiPtr->persistLevel3 = 10;
   psCellTableApiPtr->persistLevel4 = 14;
   psCellTableApiPtr->rflNumber = 3;
   psCellTableApiPtr->cellBarAccess2 = 1;
   psCellTableApiPtr->excAcc = 0;
   psCellTableApiPtr->gprsRxlevAccessMin = 25;
   psCellTableApiPtr->gprsMsTxPwrMaxCch = 30;
   psCellTableApiPtr->gprsGeneralCellReselectHysteresis = 5;
   psCellTableApiPtr->c31Hyst = 0;
   psCellTableApiPtr->c32Qual = 0;
   psCellTableApiPtr->randomAccessRetry = 1;
   psCellTableApiPtr->tresel = 250;
   psCellTableApiPtr->raReselectHysteresis = 1;
   psCellTableApiPtr->psi1RepeatPeriod = 12;
   psCellTableApiPtr->pacchPsiMsgBitMap = 48;
   psCellTableApiPtr->pbcchPsiMsgBitMap = 32;
   psCellTableApiPtr->pccchPsiMsgBitMap = 100;
   psCellTableApiPtr->btsPwrCtrlMode = 1;
   psCellTableApiPtr->prMode = 1;
   psCellTableApiPtr->dlBtsPwrCtrlEnabled = 0 ;
   psCellTableApiPtr->p0 = 2;
   psCellTableApiPtr->numOfPccchInCell = 7;
   psCellTableApiPtr->pccchBitMap = 7;      

   if ( insertPsCellTable(psCellTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Ps cell Table Success Full \n");
      free(psCellTableApiPtr);
   }
   else
      free(psCellTableApiPtr);

}

void addaddPSExternalCellTable()
{

   PsNeighCellsTableApi *psNeighCellsTableApiPtr;
   PsExternalCellTableApi *PsExternalCellTableApiPtr;

   psNeighCellsTableApiPtr = ( PsNeighCellsTableApi *)calloc(1,sizeof(PsNeighCellsTableApi));
   psNeighCellsTableApiPtr->psCellId = 22;
   psNeighCellsTableApiPtr->lac = 22;
   psNeighCellsTableApiPtr->cellType = 0;
   psNeighCellsTableApiPtr->psNeighborCellId =33;
   psNeighCellsTableApiPtr->psNeighborLac = 33;
   psNeighCellsTableApiPtr->psNeighborMcc = 91;
   psNeighCellsTableApiPtr->psNeighborMnc = 91;
   psNeighCellsTableApiPtr->relationType = 0;
   if ( insertPsNeighCellsTable(psNeighCellsTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert csExternalCellTable Table Success Full \n");
      free(psNeighCellsTableApiPtr);         
   }
   else
      free(psNeighCellsTableApiPtr);

   PsExternalCellTableApiPtr = ( PsExternalCellTableApi *)calloc(1,sizeof(PsExternalCellTableApi));

   PsExternalCellTableApiPtr->psExtCellId = 10; 
   PsExternalCellTableApiPtr->lac = 10;
   PsExternalCellTableApiPtr->pbcchArfcn = 530;
   PsExternalCellTableApiPtr->mnc = 120;
   PsExternalCellTableApiPtr->mcc = 99;
   PsExternalCellTableApiPtr->bsic = 1;
   PsExternalCellTableApiPtr->rac = 15;
   PsExternalCellTableApiPtr->cellBarAccess2 = 1; /* 1-Barred */
   PsExternalCellTableApiPtr->gprsMsTxPwrMaxCch = 24;
   PsExternalCellTableApiPtr->gprsRxLevAccessMin = 63;
   PsExternalCellTableApiPtr->gprsTemporaryOffset = 5;
   PsExternalCellTableApiPtr->gprsPenaltyTime = 320;
   PsExternalCellTableApiPtr->gprsReselectOffset = -52;
   PsExternalCellTableApiPtr->psi1RepeatPeriod = 16;
   PsExternalCellTableApiPtr->si13PbcchLocation = 0;
   PsExternalCellTableApiPtr->pbcchArfcn = 1024;

   if ( insertPsExternalCellTable(PsExternalCellTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert csExternalCellTable Table Success Full \n");
      free(PsExternalCellTableApiPtr);         
   }
   else
      free(PsExternalCellTableApiPtr);


}
void cellObjHandler4(){}
void cellObjHandler5(){}
void cellObjHandler8(){}
void cellObjHandler14(){}
void cellObjHandler15(){}
void cellObjHandler16(){}
void cellObjHandler17(){}
void cellObjHandler18(){}
void cellObjHandler19(){}


