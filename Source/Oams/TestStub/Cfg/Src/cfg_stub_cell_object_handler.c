#include <oamcfg_includes.h> 

#define CFG_RESET    0xffff

extern int gTestCaseCompleted; 
void addbcchChannelGrp(); 
void addChannelgrp(); 
void addArfcnList(); 
void addLacTable(); 
void addPsCellTable(); 
void addPSExternalCellTable(); 
void addPSInternalCellTable(); 
void addRaTable(); 
void addCSInternalCellTable(); 
void addCSExternalCellTable(); 
void addPcuTable();
void addBSStable();
void removedCelltable(I_U32 cellId,I_U32 lac);

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
   TimeSlotTableApi *TimeSlotTableApiPtr;
   I_U32 count1;
   I_U16 outsize;

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf(" Test Case 1 : \n"); 
      deleteCellTables();

      CellTableIndicesBuff.cellId = 1; 
      CellTableIndicesBuff.lac = 1; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 1 : Celll Table Success Full \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 1; 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 1; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 1 : Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 1 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 0; /* locked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
      free(CellTableApiPtr); 


   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               printf("Test Case 1 :Received Ack Successfully\n"); 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 1:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 1:Ack Receieved \n");
               }

            } 
            break; 
         case OAMS_CFG_CELLH_LOCK_REQ : 
            {    
               printf("Test Case 1 :Received OAMS_CFG_CELLH_LOCK_REQ \n"); 
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_PCUH_LOCK_REQ : 
            { 
               /*      psappPcuCfgAlarmIndBuff.sysAlarm.sysalarmId = PSCell_Disabled; 
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
         case OAMS_CFG_AFH_ALARM_IND: 
            {   //Check alarm receieved 
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf; 
               printf("Test Case 1 :Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId); 
               gTestCaseCompleted = 1; 
               removedCelltable(1,1);
               printf("Test Case 1 : Success\n"); 
            } 
            break; 
         default: 
            printf("Test Case 1 :undefined Message Type\n"); 
      } 


   } 
} 

#if 0 
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
         CellTableApiPtr->lac = 1; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Insert CellTable Unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                     //addChannelgrp(); 

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
                     addPSExternalCellTable(); 
                  } 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
         case OAMS_CFG_PCUH_UNLOCK_REQ: 
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
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ : 
            { 

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf; 
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac); 

            } 
            break; 
         case PSAPP_PCUH_CFG_ALARM_IND : 
            {    
               //PSAPP_PCU_CFG_ALARM_IND alarm received 
            } 
            break; 
      } 


      printf("bssLockTestCase 1 : Success\n"); 
   } 

} 

#endif 

void cellObjHandler2() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 2 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 2; 
      CellTableIndicesBuff.lac = 2; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 2 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 2; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 2; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 2 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 2 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      addBSStable();
      addPcuTable();
      addbcchChannelGrp(); 
      addPsCellTable(2,2);
      addChannelgrp();
      addArfcnList();
      addLacTable(2);
      addRaTable(2,6); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      addPSInternalCellTable();
      addPSExternalCellTable();

      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 2:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 2:Ack Receieved \n");
               }

            } 
            break; 
         case OAMS_CFG_PSSCM_UNLOCK_REQ : 
            { 
               oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf; 
               //memcpy(objectIdList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->lengthOfList); 
               cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_PCUH_UNLOCK_REQ  : 
            { 
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf; 

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0); 
            } 
            break; 
         case OAMS_CFG_CELLH_UNLOCK_REQ  : 
            { 
               SysAlarm sysAlarmBuff; 
               OamsCfgCellhUnlockReq* oamsCfgCellhUnlockReqPtr; 
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);            
               sysAlarmBuff.sysalarmId = CELL_ENABLED; 
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType; 
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId; 
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac; 
               cfgStubSendCellhCfgAlarmInd(sysAlarmBuff); 

               gTestCaseCompleted = 1; 
               printf("Test Case 2 :Success\n"); 

            } 
            break; 
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ : 
            { 

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf; 
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac); 

            } 
            break; 
      } 

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
      printf("Test Case 3 :\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 3; 
      CellTableIndicesBuff.lac = 3; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 3 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 3; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 3; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 3 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 3 :Insert CellTable Unsuccessful \n"); 
         } 
      } 
      addLacTable(3);
      addPsCellTable(3,3);
      addRaTable(3,6);

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 3:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 3:Ack Receieved \n");
               }
            } 
            break; 
         case OAMS_CFG_PSSCM_UNLOCK_REQ : 
            { 
               oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf; 
               //memcpy(objectIdList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->lengthOfList); 
               cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_PCUH_UNLOCK_REQ  : 
            { 
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf; 

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0); 
            } 
            break; 
         case OAMS_CFG_CELLH_UNLOCK_REQ  : 
            { 
               SysAlarm sysAlarmBuff; 
               OamsCfgCellhUnlockReq* oamsCfgCellhUnlockReqPtr; 
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);            
               sysAlarmBuff.sysalarmId = CELL_ENABLED; 
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType; 
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId; 
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac; 
               cfgStubSendCellhCfgAlarmInd(sysAlarmBuff); 

               gTestCaseCompleted = 1; 
               printf("Test Case 3 : Success\n"); 

            } 
            break; 
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ : 
            { 

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf; 
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac); 

            } 
            break; 
      } 

   } 

} 

void cellObjHandler4()
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
   TimeSlotTableApi *TimeSlotTableApiPtr;
   I_U32 count1;
   I_U16 outsize;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("Test Case 4 : \n");
      deleteCellTables();

      CellTableIndicesBuff.cellId = 4;
      CellTableIndicesBuff.lac = 4;

      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->oprState = 1;
         updateCellTable(CellTableApiPtr);
         printf("Test Case 4 : get CelllTable Successfull \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 4;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->oprState = 1;
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 4;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         //CellTableApiPtr->pageStatus = 1;
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
            printf("Test Case 4 : Insert CellTable Successfull \n");
         }
         else
         {
            printf("Test Case 4 : Insert CellTable Unsuccessfull \n");
         }
      }
      /* Send lock Cell */
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 0; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
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
                  printf("Test Case 4:Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  removedCelltable(4,4);
               }
               else
               {
                  printf("Test Case 4:Ack Receieved \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {   
               printf("Test Case 4 :Received OAMS_CFG_CELLH_LOCK_REQ ");
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ :
            {
               /*      psappPcuCfgAlarmIndBuff.sysAlarm.sysalarmId = PSCell_Disabled;

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
         case OAMS_CFG_AFH_ALARM_IND:
            {   //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Test Case 4 :Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId);
               gTestCaseCompleted = 1;
               removedCelltable(4,4);
               printf("Test Case 4 : Success\n");
            }
            break;
         default:
            printf(" Test Case 4 : undefined Message Type");
      }
   }
}


void cellObjHandler5()
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
      printf("Test Case 5 : \n");
      CellTableIndicesBuff.cellId = 5;
      CellTableIndicesBuff.lac = 5;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->oprState =1;
         updateCellTable(CellTableApiPtr);
         printf("Test Case 5 :get CelllTable Successfull \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
         CellTableApiPtr->cellId = 5;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->oprState =1;
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 5;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1;
         CellTableApiPtr->psStatus = 1;
         //CellTableApiPtr->pageStatus = 1;
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
            printf("Test Case 5 :Insert CellTable Successfull \n");
         }
         else
         {
            printf("Test Case 5 :Insert CellTable Unsuccessful \n");
         }
      }
      /* Send lock BSS */
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 2; /* Shutting down */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
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
                  printf("Test Case 5:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 5:Ack Receieved \n");
               }

            }
            break;
         case OAMS_CFG_CELLH_SHUTDOWN_IND :
            {
               printf("Test Case 5 : Cell Shut down indicator received\n");
            }
            break;
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   :
            {
               printf("Test Case 5 : CFG_GRHM_STOP_CHAN_ALLOC indicator received\n");            
            }
            break;
         case OAMS_CFG_PCUH_CELL_SHUTDOWN_IND  :
            {
               printf("Test Case 5 : CFG_PCU_CELL_SHUTDOWN_IND indicator received\n");   
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {   
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ :
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
         case OAMS_CFG_AFH_ALARM_IND:
            {   //Check alarm receieved
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf;
               printf("Test Case 5 : Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId);
               gTestCaseCompleted = 1;
               removedCelltable(5,5);
               printf("Test Case 5 :  Success\n");
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
      printf("Test Case 6: \n"); 
      CellTableIndicesBuff.cellId = 6; 
      CellTableIndicesBuff.lac = 6; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 6:get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 6; 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 6; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 6:Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 6:Insert CellTable Unsuccessful \n"); 
         } 
      } 
      /* Send lock BSS */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 2; /* Shutting down */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 6:Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  removedCelltable(6,6);
               }
               else
               {
                  printf("Test Case 6:Ack Receieved \n");
               }
            } 
            break; 
         case OAMS_CFG_CELLH_SHUTDOWN_IND : 
            { 
               printf("Test Case 6:Cell Shut down indicator received"); 

            } 
            break; 
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   : 
            { 
               printf("Test Case 6: CFG_GRHM_STOP_CHAN_ALLOC indicator received");             
            } 
            break; 
         case OAMS_CFG_PCUH_CELL_SHUTDOWN_IND  : 
            { 
               printf("Test Case 6: CFG_PCUH_CELL_SHUTDOWN_IND indicator received");    
            } 
            break; 
         case OAMS_CFG_CELLH_LOCK_REQ : 
            {    
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_PCUH_LOCK_REQ : 
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
         case OAMS_CFG_AFH_ALARM_IND: 
            {   //Check alarm receieved 
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf; 
               printf("Test Case 6:Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId); 
               gTestCaseCompleted = 1; 
               removedCelltable(6,6);
               printf("Test Case 6: Success\n"); 
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
      printf("Test Case 7: \n"); 
      CellTableIndicesBuff.cellId = 7; 
      CellTableIndicesBuff.lac = 7; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         if(updateCellTable(CellTableApiPtr) == CLIB_SUCCESS) 
         { 
            printf("Test Case 7:get Celll Table Success Full \n"); 
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
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 7:Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 7:Insert CellTable Unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 2; /* Shutting down */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 7:Nack Receieved \n"); 
                  cfgStubSendCmMessage(NULL,0,CFG_RESET);
                  gTestCaseCompleted = 1;                            
                  removedCelltable(7,7);
               } 
               else 
               { 
                  printf("Test Case 7:Ack Receieved \n"); 
               } 
            } 
            break; 
         case OAMS_CFG_CELLH_SHUTDOWN_IND : 
            { 
               printf("Test Case 7: Cell Shut down indicator received"); 
               printf("Test Case 7:Sending the Shutdown Message again for the same cell instance"); 
               CellTableIndicesBuff.cellId = 7; 
               CellTableIndicesBuff.lac = 7; 
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
               { 
                  printf("Test Case 7:get CelllTable Success Full \n"); 
                  CellTableApiPtr->adminState = 2; /* Shutting down */ 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
               } 
            } 
            break; 
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   : 
            { 

            } 
            break; 
         case OAMS_CFG_PCUH_CELL_SHUTDOWN_IND   : 
            { 

            } 
            break; 
      } 
   } 
} 

void cellObjHandler8() 
{ 
   static int testInitiation =1; 

   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("Test Case 8 : \n"); 
      CellTableIndicesBuff.cellId = 8; 
      CellTableIndicesBuff.lac = 8; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 8 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 8; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 8; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 8 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 8 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 8 : Nack Receieved \n"); 
                  gTestCaseCompleted = 1; 
                  removedCelltable(8,8);
               } 
               else 
               { 
                  printf("Test Case 8 : Ack Receieved \n"); 
               } 


            } 
            break; 
         case OAMS_CFG_PSSCM_UNLOCK_REQ : 
            { 


               printf("Test Case 8 :CFG_PSSCM_UNLOCK_REQ message received\n"); 
               CellTableIndicesBuff.cellId = 9; 
               CellTableIndicesBuff.lac = 9; 
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
               { 
                  printf("Test Case 8 :get CelllTable Successfull \n"); 
                  CellTableApiPtr->adminState = 1; /* unlocked */ 
                  printf("Test Case 8 :sending the unlock for the same cell"); 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
               } 
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
      printf("Test Case 9 : \n"); 
      CellTableIndicesBuff.cellId = 9; 
      CellTableIndicesBuff.lac = 9; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 9 :get CelllTable Success Full \n"); 
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
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 9 :Insert CellTable Successful \n"); 
         } 
         else 
         { 
            printf("Test Case 9 :Insert CellTable  Unsuccessfull \n"); 
         } 
      } 
      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 0; /* locked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 9 :Nack Receieved \n"); 
                  gTestCaseCompleted = 1; 
                  removedCelltable(9,9);
               } 
               else 
               { 
                  printf("Test Case 9 :Ack Receieved \n"); 
               } 
            } 
            break; 
         case OAMS_CFG_CELLH_LOCK_REQ : 
            { 
               printf("Test Case 9 ::CFG_PSSCM_LOCK_REQ message received"); 
               CellTableIndicesBuff.cellId = 9; 
               CellTableIndicesBuff.lac = 9; 
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
               { 
                  printf(" Test Case 9 : get CelllTable Successfull \n"); 
                  CellTableApiPtr->adminState = 0; /* locked */ 
                  printf("Test Case 9 :sending the lock message for the same cell"); 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
               } 

            } 
            break; 
         case OAMS_CFG_PCUH_LOCK_REQ : 
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

void cellObjHandler10() 
{ 
   static int testInitiation =1; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("Test Case 10 :  \n"); 
      CellTableIndicesBuff.cellId = 10; 
      CellTableIndicesBuff.lac = 10; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 10 : get Celll Table Success Full \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 10; 
         CellTableApiPtr->lac =10; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = GSM_850; 
         CellTableApiPtr->bcchArfcn = 190; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 10 :Insert CellTable Successfull \n"); 
         } 
         else 
         { 
            printf("Test Case 10 :Insert CellTable unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->msTxPwrMax = 9;   /*Parameter Modification*/ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 10 :Nack Receieved \n"); 
               } 
               else 
               { 
                  printf("Test Case 10 :Ack Receieved \n"); 
                  gTestCaseCompleted = 1; 
                  removedCelltable(10,10);
                  printf("Test Case 10 : Success\n"); 
               } 
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
      printf("Test Case 11 : \n"); 
      CellTableIndicesBuff.cellId = 11; 
      CellTableIndicesBuff.lac = 11; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 11: CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 11; 
         CellTableApiPtr->lac =11; 
         CellTableApiPtr->adminState = 1; /* Unlocked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 11 : Insert CellTable Successfull \n"); 
         } 
         else 
         { 
            printf("Test Case 11 : Insert CellTable Unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->msTxPwrMax = 9;   /*Parameter Modification*/ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 11 :Nack Receieved \n"); 
                  gTestCaseCompleted = 1; 
                  removedCelltable(11,11);
                  printf("Test Case 11 : Success\n"); 
               } 
               else 
               { 
                  printf("Test Case 11 :Ack Receieved \n"); 
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
      printf("Test Case 12 : \n"); 
      /* First set the required database */ 
      CellTableIndicesBuff.cellId = 12; 
      CellTableIndicesBuff.lac = 12; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /*locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 12 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 12; 
         CellTableApiPtr->lac =12; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 12 :Insert CellTable Successfull \n"); 
         } 
         else 
         { 
            printf("Test Case 12 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 1; /* Unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 12 :Nack Receieved \n"); 
                  gTestCaseCompleted = 1; 
                  removedCelltable(12,12);
                  printf("Test Case 12 :Success\n"); 
               } 
               else 
               { 
                  printf("Test Case 12 :Ack Receieved \n"); 
               } 
            } 
            break; 
         case OAMS_CFG_PSSCM_UNLOCK_REQ : 
            { 


               printf("Test Case 12 :CFG_PSSCM_UNLOCK_REQ message received\n"); 
               CellTableIndicesBuff.cellId = 12; 
               CellTableIndicesBuff.lac = 12; 
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
               { 
                  printf("Test Case 12 :get CelllTable Successfull \n"); 
                  CellTableApiPtr->msTxPwrMax = 8; /* Parameter Modification */ 
                  printf("Test Case 12 :sending the parameter Modification for the same cell"); 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
               } 
            } 
            break; 
      } 
   } 
} 

void cellObjHandler13() 
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
      printf("Test Case 13 : \n"); 
      /* First set the required database */ 
      CellTableIndicesBuff.cellId = 13; 
      CellTableIndicesBuff.lac = 13; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         printf("Test Case 13 :get CelllTable Successfull \n"); 
         CellTableApiPtr->adminState = 0; /*locked */ 
         updateCellTable(CellTableApiPtr); 
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
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 13 :Insert Cell Table Success Full \n"); 
         } 
         else 
         { 
            printf("Test Case 13 :Insert CellTable unsuccessfull \n"); 
         } 
      } 
      addLacTable(13);
      addPsCellTable(13,13);
      addRaTable(13,6);

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 1; /* Unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 13 :Nack Receieved \n"); 
               } 
               else 
               { 
                  printf("Test Case 13 :Ack Receieved \n"); 
               } 
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
         case OAMS_CFG_PCUH_UNLOCK_REQ  : 
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
               CellTableIndicesBuff.cellId = 13; 
               CellTableIndicesBuff.lac = 13; 
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
               { 
                  printf("Test Case 13 :get CelllTable Successfull \n"); 
                  CellTableApiPtr->adminState = 0; /* unlocked */ 
                  printf("Test Case 13 :sending the lock for the same cell"); 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
               } 
            } 
            break; 
         case OAMS_CFG_CELLH_LOCK_REQ : 
            { 
               OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr; 
               printf("Test Case 13 :Received OAMS_CFG_CELLH_LOCK_REQ "); 
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_PCUH_LOCK_REQ : 
            { 
               /*              psappPcuCfgAlarmIndBuff.sysAlarm.sysalarmId = PSCell_Disabled; 
                     psappPcuCfgAlarmIndBuff.sysAlarm.key1 = oamsCfgPcuLockReqPtr->objType; 
                     psappPcuCfgAlarmIndBuff.sysAlarm.key2 = oamsCfgPcuLockReqPtr->objId; 
                     cfgStubSendPcuCfgAlarmInd(&psappPcuCfgAlarmIndBuff.sysAlarm); 
                */ 
               OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr ; 
               oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf; 
               cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_PSSCM_LOCK_REQ : 
            { 
               OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ; 
               oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf; 
               //      memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList); 
               cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac); 
               gTestCaseCompleted = 1; 
               removedCelltable(13,13);
               printf("Test Case 13 : Success\n"); 
            } 
            break; 

      } 
   } 
} 



void cellObjHandler14() 
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
      printf("Test Case 14 : \n"); 
      /* First set the required database */ 
      CellTableIndicesBuff.cellId = 14; 
      CellTableIndicesBuff.lac = 14 ;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         printf("Test Case 14 : get CelllTable Successfull \n"); 
         CellTableApiPtr->adminState = 0; /*locked */ 
         updateCellTable(CellTableApiPtr); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 14; 
         CellTableApiPtr->lac =14; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 14 : Insert CellTable Successfull \n"); 
         } 
         else 
         { 
            printf("Test Case 14 : Insert CellTable unsuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 1; /* Unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 14 :Nack Receieved \n"); 
                  gTestCaseCompleted = 1; 
                  removedCelltable(14,14);
               } 
               else 
               { 
                  printf("Test Case 14 :Ack Receieved \n"); 
               } 
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
         case OAMS_CFG_PCUH_UNLOCK_REQ  : 
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
               CellTableIndicesBuff.cellId = 14; 
               CellTableIndicesBuff.lac = 14; 
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
               { 
                  printf("Test Case 14 :get CelllTable Successfull \n"); 
                  CellTableApiPtr->adminState = 1; /* unlocked */ 
                  printf("Test Case 14 :sending the unlock for the same cell"); 
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
               } 
            } 
            break; 
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ : 
            { 

               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf; 
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac); 

            } 
            break; 
      } 
   } 
} 

void cellObjHandler15() 
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
      printf("Test Case 15 : \n"); 
      CellTableIndicesBuff.cellId = 15; 
      CellTableIndicesBuff.lac = 15; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /*unlocked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 15 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 15; 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 15; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 0; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 15 :Insert CellTable Successfull \n"); 
         } 
         else 
         { 
            printf("Test Case 15 :Insert CellTable UnSuccessfull \n"); 
         } 
      } 

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 0; /* locked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 15:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 15:Ack Receieved \n");
               }


            } 
            break; 
         case OAMS_CFG_CELLH_LOCK_REQ : 
            {    
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_AFH_ALARM_IND: 
            {       //Check alarm receieved 
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf; 
               printf("Test Case 15 :Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId); 
               gTestCaseCompleted = 1; 
               removedCelltable(15,15);
               printf("Test Case 15 : Success\n"); 
            } 
            break; 
      } 
   } 
} 

void cellObjHandler16() 
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
      printf("Test Case 16 : \n"); 
      CellTableIndicesBuff.cellId = 16; 
      CellTableIndicesBuff.lac = 16; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /*locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 16 :get CelllTable Successful \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 16; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 16; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 0; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 16 :Insert CellTable Successful \n"); 
         } 
         else 
         { 
            printf("Test Case 16 :Insert CellTable UnSuccessful \n"); 
         } 
      } 
      addLacTable(16);

      /* Send lock Cell */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 16:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 16:Ack Receieved \n");
               }


            } 
            break; 
         case OAMS_CFG_CELLH_UNLOCK_REQ  : 
            { 
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);            

            } 
            break; 
         case OAMS_CFG_AFH_ALARM_IND: 
            {       //Check alarm receieved 
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf; 
               printf("Test Case 16 :Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId); 
               gTestCaseCompleted = 1; 
               removedCelltable(16,16);
               printf("Test Case 16 : Success\n"); 
            } 
            break; 
      } 
   } 
} 

void cellObjHandler17() 
{ 
   static int testInitiation =1; 
   I_U32 objectIdList[32]; 
   OamsCellhCfgAlarmInd *oamsCellhCfgAlarmIndPtr; 
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;

   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 


   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("Test Case 17 \n"); 
      /* First set the required database */ 
      CellTableIndicesBuff.cellId = 17; 
      CellTableIndicesBuff.lac = 17; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 1; /*unlocked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 17 : get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi)); 
         CellTableApiPtr->cellId = 17; 
         CellTableApiPtr->adminState = 1; /* unlocked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 17; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 0; 
         CellTableApiPtr->psStatus = 0; 
         //CellTableApiPtr->pageStatus = 0; 
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
            printf("Test Case 17 :Insert CellTable Success Full \n"); 
         } 
         else 
         { 
            printf("Test Case 17 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      /* Send lock BSS */ 
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET); 
      CellTableApiPtr->adminState = 2; /* Shutting down */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
      free(CellTableApiPtr); 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               printf("Test Case 17 : Received CM_API_APP_RESPONSE successfully\n"); 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 17:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 17:Ack Receieved \n");
               }

            } 
            break; 
         case OAMS_CFG_CELLH_SHUTDOWN_IND : 
            { 
               printf("Test Case 17 :Cell Shut down indicator received"); 
            } 
            break; 
         case OAMS_CFG_GRHM_STOP_CHAN_ALLOC   : 
            { 
               printf("Test Case 17 : OAMS_CFG_GRHM_STOP_CHAN_ALLOC indicator received"); 

            } 
            break; 
         case OAMS_CFG_CELLH_LOCK_REQ : 
            {    
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf; 
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac); 
            } 
            break; 
         case OAMS_CFG_AFH_ALARM_IND: 
            {   //Check alarm receieved 
               oamsCellhCfgAlarmIndPtr = (OamsCellhCfgAlarmInd *)gCfgMsgBuf; 
               printf("Test Case 17 :Alarms Id %d\n",oamsCellhCfgAlarmIndPtr->sysAlarm.sysalarmId); 

               gTestCaseCompleted = 1; 
               removedCelltable(17,17);
               printf("Test Case 17 : Success\n"); 
            } 
            break; 
      } 
   } 
} 


void cellObjHandler18() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 18 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 18; 
      CellTableIndicesBuff.lac = 18; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 18 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 18; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 18; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 2 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 2 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      addBSStable();
      addPcuTable();
      addbcchChannelGrp(); 
      addChannelgrp();
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 18:Nack Receieved \n");
                  printf("Test Case 18: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(18,18);
               }
               else
               {
                  printf("Test Case 18:Ack Receieved \n");
               }

            } 
            break; 
      } 

   } 

} 

void cellObjHandler19() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 19 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 19; 
      CellTableIndicesBuff.lac = 19; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 19 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 19; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 19; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 19 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 19 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      addBSStable();
      addPcuTable();
      addbcchChannelGrp(); 
      addChannelgrp();
      addLacTable(19);
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 19:Nack Receieved \n");
                  printf("Test Case 19: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(19,19);
               }
               else
               {
                  printf("Test Case 19:Ack Receieved \n");
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
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 2 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 20; 
      CellTableIndicesBuff.lac = 20; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 20 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 20; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 20; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 20 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 20 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      addBSStable();
      addPcuTable();
      addbcchChannelGrp(); 
      addChannelgrp();
      addPsCellTable(20,20);
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 20:Nack Receieved \n");
                  printf("Test Case 20: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(20,20);
               }
               else
               {
                  printf("Test Case 20:Ack Receieved \n");
               }

            } 
            break; 
      } 

   } 

} 

void cellObjHandler21() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 2 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 21; 
      CellTableIndicesBuff.lac = 21; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 21 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 21; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 21; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 21 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 21 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      addBSStable();
      addPcuTable();
      addPsCellTable(21,21);
      addArfcnList();
      addLacTable(21);

      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 21:Nack Receieved \n");
                  printf("Test Case 21: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(21,21);
               }
               else
               {
                  printf("Test Case 21:Ack Receieved \n");
               }

            } 
            break; 
      }
   } 
} 

void cellObjHandler22() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 
   CsNeighCellsTableApi *csNeighCellsTableApiPtr; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 22 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 22; 
      CellTableIndicesBuff.lac = 22; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 22 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 22; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 22; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 22 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 22 :Insert CellTable Unsuccessfull \n"); 
         } 

         csNeighCellsTableApiPtr = ( CsNeighCellsTableApi *)calloc(1,sizeof(CsNeighCellsTableApi)); 

         csNeighCellsTableApiPtr->cellId = 22; 
         csNeighCellsTableApiPtr->lac = 22; 
         csNeighCellsTableApiPtr->cellType = 0; 
         csNeighCellsTableApiPtr->neighborCellId = 122; 
         csNeighCellsTableApiPtr->neighborLac = 33; 
         csNeighCellsTableApiPtr->neighborMcc = 91; 
         csNeighCellsTableApiPtr->neighborMnc = 51; 
         csNeighCellsTableApiPtr->relationType = 0;    

         if ( insertCsNeighCellsTable(csNeighCellsTableApiPtr) == CLIB_SUCCESS ) 
         { 
            printf("Insert Cell Table Success Full \n"); 
            free(csNeighCellsTableApiPtr); 
         } 
         else 
            free(csNeighCellsTableApiPtr); 
      } 
      addBSStable();
      addPcuTable();
      addPsCellTable(22,22);
      addLacTable(22);
      addRaTable(22,6); 
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 22:Nack Receieved \n");
                  printf("Test Case 22: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(22,22);
               }
               else
               {
                  printf("Test Case 22:Ack Receieved \n");
               }

            } 
            break; 
      } 
   } 
} 

void cellObjHandler23() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 
   CsNeighCellsTableApi *csNeighCellsTableApiPtr; 
   CsExternalCellTableApi *csExternalCellTableApiPtr; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 23 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 23; 
      CellTableIndicesBuff.lac = 23; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 23 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 23; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 23; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 23 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 23 :Insert CellTable Unsuccessfull \n"); 
         } 

         csNeighCellsTableApiPtr = ( CsNeighCellsTableApi *)calloc(1,sizeof(CsNeighCellsTableApi)); 
         csNeighCellsTableApiPtr->cellId = 23; 
         csNeighCellsTableApiPtr->lac = 23; 
         csNeighCellsTableApiPtr->cellType = 1; 
         csNeighCellsTableApiPtr->neighborCellId = 44; 
         csNeighCellsTableApiPtr->neighborLac = 44; 
         csNeighCellsTableApiPtr->neighborMcc = 91; 
         csNeighCellsTableApiPtr->neighborMnc = 91; 
         csNeighCellsTableApiPtr->relationType = 0;    

         if ( insertCsNeighCellsTable(csNeighCellsTableApiPtr) == CLIB_SUCCESS ) 
         { 
            printf("Insert Cell Table Success Full \n"); 
            free(csNeighCellsTableApiPtr); 

         } 
         else 
            free(csNeighCellsTableApiPtr); 
      } 
      addBSStable();
      addPcuTable();
      addPsCellTable(23,23);
      addLacTable(23);
      addRaTable(23,6); 
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 23:Nack Receieved \n");
                  printf("Test Case 23: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(23,23);
               }
               else
               {
                  printf("Test Case 23:Ack Receieved \n");
               }
            } 
            break; 
      } 
   } 
} 

void cellObjHandler24() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 
   CsNeighCellsTableApi *csNeighCellsTableApiPtr; 
   CsExternalCellTableApi *csExternalCellTableApiPtr; 
   PsNeighCellsTableApi *psNeighCellsTableApiPtr; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 24 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 24; 
      CellTableIndicesBuff.lac = 24; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 24 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 24; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 24; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 24 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 24 :Insert CellTable Unsuccessfull \n"); 
         } 


         psNeighCellsTableApiPtr = ( PsNeighCellsTableApi *)calloc(1,sizeof(PsNeighCellsTableApi)); 
         psNeighCellsTableApiPtr->psCellId = 24; 
         psNeighCellsTableApiPtr->lac = 24; 
         psNeighCellsTableApiPtr->cellType = 0; 
         psNeighCellsTableApiPtr->psNeighborCellId = 24; 
         psNeighCellsTableApiPtr->psNeighborLac = 24; 
         psNeighCellsTableApiPtr->psNeighborCellRac = 6; 
         psNeighCellsTableApiPtr->psNeighborMcc = 9; 
         psNeighCellsTableApiPtr->psNeighborMnc = 9; 
         psNeighCellsTableApiPtr->relationType = 0; 
         if ( insertPsNeighCellsTable(psNeighCellsTableApiPtr) == CLIB_SUCCESS ) 
         { 
            printf("Insert csExternalCellTable Table Success Full \n"); 
            free(psNeighCellsTableApiPtr);          
         } 
         else 
            free(psNeighCellsTableApiPtr); 

      } 
      addBSStable();
      addPcuTable();
      addPsCellTable(24,24);
      addLacTable(24);
      addRaTable(24,6); 
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 24:Nack Receieved \n");
                  printf("Test Case 24: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(24,24);
               }
               else
               {
                  printf("Test Case 24:Ack Receieved \n");
               }
            } 
            break; 
      } 
   } 
} 


void cellObjHandler25() 
{ 
   static int testInitiation =1; 
   OamsCfgPsscmUnlockReq *oamsCfgPsscmUnlockReqPtr; 
   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   I_U32 objectIdList[32]; 
   OamsCfgPcuUnlockReq *oamsCfgPcuUnlockReqPtr; 
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr; 
   OamsCfgPcuCellEnabledReq *oamsCfgPcuCellEnabledReqPtr; 
   static I_U32 cmApi_response_count =0; 
   CsNeighCellsTableApi *csNeighCellsTableApiPtr; 
   CsExternalCellTableApi *csExternalCellTableApiPtr; 
   PsNeighCellsTableApi *psNeighCellsTableApiPtr; 

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("cellLockTestCase 25 : cell Unlock Request\n"); 
      deleteCellTables();
      CellTableIndicesBuff.cellId = 25; 
      CellTableIndicesBuff.lac = 25; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Test Case 25 :get CelllTable Successfull \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
         CellTableApiPtr->cellId = 25; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 25; 
         CellTableApiPtr->bcchArfcn = 124; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psStatus = 1; 
         //CellTableApiPtr->pageStatus = 1; 
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
            printf("Test Case 25 :Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Test Case 25 :Insert CellTable Unsuccessfull \n"); 
         } 


         psNeighCellsTableApiPtr = ( PsNeighCellsTableApi *)calloc(1,sizeof(PsNeighCellsTableApi)); 
         psNeighCellsTableApiPtr->psCellId = 25; 
         psNeighCellsTableApiPtr->lac = 25; 
         psNeighCellsTableApiPtr->cellType = 1; 
         psNeighCellsTableApiPtr->psNeighborCellId = 54; 
         psNeighCellsTableApiPtr->psNeighborLac = 54; 
         psNeighCellsTableApiPtr->psNeighborCellRac = 6; 
         psNeighCellsTableApiPtr->psNeighborMcc = 9; 
         psNeighCellsTableApiPtr->psNeighborMnc = 9; 
         psNeighCellsTableApiPtr->relationType = 0; 
         if ( insertPsNeighCellsTable(psNeighCellsTableApiPtr) == CLIB_SUCCESS ) 
         { 
            printf("Insert csExternalCellTable Table Success Full \n"); 
            free(psNeighCellsTableApiPtr);          
         } 
         else 
            free(psNeighCellsTableApiPtr); 

      } 
      addBSStable();
      addPcuTable();
      addPsCellTable(25,25);
      addLacTable(25);
      addRaTable(25,6); 
      sleep(1);
      /* Send lock Cell */ 
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      CellTableApiPtr->adminState = 1; /* unlocked */ 
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE); 
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
                  printf("Test Case 25:Nack Receieved \n");
                  printf("Test Case 25: Success \n");
                  gTestCaseCompleted = 1; 
                  removedCelltable(25,25);
               }
               else
               {
                  printf("Test Case 25:Ack Receieved \n");
               }
            } 
            break; 
      } 
   } 
} 
void addbcchChannelGrp() 
{ 
   ChnGrpTableApi* ChnGrpTableApiPtr; 
   ChnGrpTableIndices  chnGrpTableIndices; 

   chnGrpTableIndices.cellId=2; 
   chnGrpTableIndices.lac=2; 
   chnGrpTableIndices.chnGrpId = 1;

   if ( getChnGrpTable(&chnGrpTableIndices, &ChnGrpTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("addbcchChannelGrp : get Channel Group Table Success Full \n"); 
   } 
   else 
   { 
      ChnGrpTableApiPtr = ( ChnGrpTableApi *)calloc(1,sizeof(ChnGrpTableApi)); 
      ChnGrpTableApiPtr->chnGrpId = 1; 
      ChnGrpTableApiPtr->cellId = 2; 
      ChnGrpTableApiPtr->lac = 2; 
      ChnGrpTableApiPtr->bcchCcchSdcch4 = 0; 
      ChnGrpTableApiPtr->bcchCcch = 1; 
      ChnGrpTableApiPtr->sdcch8 = 2; 
      ChnGrpTableApiPtr->tch = 47; 
      ChnGrpTableApiPtr->pdch = 5; 
      ChnGrpTableApiPtr->hsn = 30; 
      ChnGrpTableApiPtr->maxTxPwr = 20000; 
      ChnGrpTableApiPtr->tsc = 5; 
      ChnGrpTableApiPtr->band = 0; 
      ChnGrpTableApiPtr->validArfcns = 1; 
      ChnGrpTableApiPtr->arfcn1 = 124; 

      if ( insertChnGrpTable(ChnGrpTableApiPtr) == CLIB_SUCCESS ) 
      { 
         printf("addbcchChannelGrp :Insert Channel Group Table Success Full \n"); 
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
   ChnGrpTableIndices.cellId=2; 
   ChnGrpTableIndices.lac=2; 
   ChnGrpTableIndices.chnGrpId =2;


   if ( getChnGrpTable(&ChnGrpTableIndices, &ChnGrpTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("addbcchChannelGrp :get Channel Group Table Success Full \n"); 
   } 
   else 
   { 
      ChnGrpTableApiPtr = ( ChnGrpTableApi *)calloc(1,sizeof(ChnGrpTableApi)); 

      ChnGrpTableApiPtr->chnGrpId = 2; 
      ChnGrpTableApiPtr->cellId = 2; 
      ChnGrpTableApiPtr->lac =2;
      ChnGrpTableApiPtr->bcchCcchSdcch4 = 0; 
      ChnGrpTableApiPtr->bcchCcch = 0; 
      ChnGrpTableApiPtr->sdcch8 = 0; 
      ChnGrpTableApiPtr->tch = 47; 
      ChnGrpTableApiPtr->pdch = 48; 
      ChnGrpTableApiPtr->hsn = 30; 
      ChnGrpTableApiPtr->maxTxPwr = 20000; 
      ChnGrpTableApiPtr->tsc = 5; 
      ChnGrpTableApiPtr->band = 0; 
      ChnGrpTableApiPtr->validArfcns = 18; 
      ChnGrpTableApiPtr->arfcn1 = 150; 
      ChnGrpTableApiPtr->arfcn2 = 155; 
      ChnGrpTableApiPtr->arfcn3 = 165; 
      ChnGrpTableApiPtr->arfcn4 = 175; 
      ChnGrpTableApiPtr->arfcn5 = 185; 
      ChnGrpTableApiPtr->arfcn6 = 195; 
      ChnGrpTableApiPtr->arfcn7 = 145; 
      ChnGrpTableApiPtr->arfcn8 = 135; 
      ChnGrpTableApiPtr->arfcn9 = 125; 
      ChnGrpTableApiPtr->arfcn10 = 115; 
      ChnGrpTableApiPtr->arfcn11 = 105; 
      ChnGrpTableApiPtr->arfcn12 = 35; 
      ChnGrpTableApiPtr->arfcn13 = 45; 
      ChnGrpTableApiPtr->arfcn14 = 55; 
      ChnGrpTableApiPtr->arfcn15 = 65; 
      ChnGrpTableApiPtr->arfcn16 = 75; 
      ChnGrpTableApiPtr->arfcn17 = 85; 
      //ChnGrpTableApiPtr->arfcn18= 95; 


      if ( insertChnGrpTable(ChnGrpTableApiPtr) == CLIB_SUCCESS ) 
      { 
         printf("addbcchChannelGrp : Insert Channel Group Table Success Full \n"); 
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
      chnGrpTableApiPtr->bcchCcchSdcch4 = 1; 
      chnGrpTableApiPtr->bcchCcch = 0; 
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
   } 
   free(arfcnListTableApiPtr); 

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi)); 
   arfcnListTableApiPtr->band = 0; 
   arfcnListTableApiPtr->arfcn = 150; 
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("Insert Arfcn Group Table Success Full \n"); 

   } 
   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi)); 

   arfcnListTableApiPtr->band = 0; 
   arfcnListTableApiPtr->arfcn = 155; 
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("Insert Arfcn Table Success Full \n"); 
   } 
   free(arfcnListTableApiPtr); 

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi)); 
   arfcnListTableApiPtr->band = 0; 
   arfcnListTableApiPtr->arfcn = 165; 
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("Insert Channel Group Table Success Full \n"); 
   } 

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 175;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 185;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 195;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 145;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 135;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 125;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 115;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 105;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 35;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 45;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 55;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 65;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 75;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 85;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }

   arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));
   arfcnListTableApiPtr->band = 0;
   arfcnListTableApiPtr->arfcn = 95;
   if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
   {
      printf("Insert Channel Group Table Success Full \n");
   }
} 

void addLacTable(I_U32 lac) 
{ 
   LaTableApi *laTableApiPtr; 

   laTableApiPtr = ( LaTableApi *)calloc(1,sizeof(LaTableApi)); 
   laTableApiPtr->lac =lac; 
   if ( insertLaTable(laTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("Insert Channel Group Table Success Full \n"); 
      free(laTableApiPtr); 
   } 
   else 
      free(laTableApiPtr); 
} 


void addPsCellTable(I_U32 cellId, I_U32 lac) 
{ 
   PsCellTableApi *psCellTableApiPtr; 
   psCellTableApiPtr = ( PsCellTableApi *)calloc(1,sizeof(PsCellTableApi)); 

   psCellTableApiPtr->cellId = cellId;  
   psCellTableApiPtr->cellBarAccess2 = 1; 
   psCellTableApiPtr->raColour = 2; 
   psCellTableApiPtr->lac = lac; 
   psCellTableApiPtr->pbcchPres = 1; 
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
   //psCellTableApiPtr->btsPwrCtrlMode = 1; 
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

void addRaTable(I_U32 lac,I_U32 rac) 
{ 
   RaTableApi *raTableApiPtr; 
   raTableApiPtr = ( RaTableApi *)calloc(1,sizeof(RaTableApi)); 

   raTableApiPtr->lac = lac; 
   raTableApiPtr->rac = rac; 
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
   csNeighCellsTableApiPtr->neighborCellId = 3; 
   csNeighCellsTableApiPtr->neighborLac = 3; 
   csNeighCellsTableApiPtr->neighborMcc = 91; 
   csNeighCellsTableApiPtr->neighborMnc = 91; 
   csNeighCellsTableApiPtr->relationType = 0;    

   if ( insertCsNeighCellsTable(csNeighCellsTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("Insert Cell Table Success Full \n"); 
      free(csNeighCellsTableApiPtr); 
   } 
   else 
      free(csNeighCellsTableApiPtr); 


   CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi)); 
   CellTableApiPtr->cellId = 3; 
   CellTableApiPtr->lac =3; 
   CellTableApiPtr->adminState = 1; /* unlocked */ 
   CellTableApiPtr->freqBandBcch = 0; 
   CellTableApiPtr->bcchArfcn = 34; 
   CellTableApiPtr->bcc = 0; 
   CellTableApiPtr->msTxPwrMax = 10; 
   CellTableApiPtr->msTxPowerMaxCch = 10; 
   //CellTableApiPtr->csStatus = 1; 
   CellTableApiPtr->psStatus = 1; 
   //CellTableApiPtr->pageStatus = 1; 
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
   csNeighCellsTableApiPtr->cellId = 2; 
   csNeighCellsTableApiPtr->lac = 2; 
   csNeighCellsTableApiPtr->cellType = 1; 
   csNeighCellsTableApiPtr->neighborCellId = 4; 
   csNeighCellsTableApiPtr->neighborLac = 4; 
   csNeighCellsTableApiPtr->neighborMcc = 91; 
   csNeighCellsTableApiPtr->neighborMnc = 91; 
   csNeighCellsTableApiPtr->relationType = 0;    

   if ( insertCsNeighCellsTable(csNeighCellsTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("Insert Cell Table Success Full \n"); 
      free(csNeighCellsTableApiPtr); 

   } 
   else 
      free(csNeighCellsTableApiPtr); 

   csExternalCellTableApiPtr = ( CsExternalCellTableApi *)calloc(1,sizeof(CsExternalCellTableApi)); 
   csExternalCellTableApiPtr->csExtCellId = 4;  
   csExternalCellTableApiPtr->lac = 4; 
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
   psNeighCellsTableApiPtr->psCellId = 2; 
   psNeighCellsTableApiPtr->lac = 2; 
   psNeighCellsTableApiPtr->cellType = 0; 
   psNeighCellsTableApiPtr->psNeighborCellId = 1; 
   psNeighCellsTableApiPtr->psNeighborLac = 1; 
   psNeighCellsTableApiPtr->psNeighborCellRac = 6; 
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
   psCellTableApiPtr->pbcchPsiMsgBitMap = 32; 
   psCellTableApiPtr->pccchPsiMsgBitMap = 100; 
   //psCellTableApiPtr->btsPwrCtrlMode = 1; 
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

void addPSExternalCellTable() 
{ 

   PsNeighCellsTableApi *psNeighCellsTableApiPtr; 
   PsExternalCellTableApi *PsExternalCellTableApiPtr; 

   psNeighCellsTableApiPtr = ( PsNeighCellsTableApi *)calloc(1,sizeof(PsNeighCellsTableApi)); 
   psNeighCellsTableApiPtr->psCellId = 2; 
   psNeighCellsTableApiPtr->lac = 2; 
   psNeighCellsTableApiPtr->cellType = 1; 
   psNeighCellsTableApiPtr->psNeighborCellId =33; 
   psNeighCellsTableApiPtr->psNeighborLac = 33; 
   psNeighCellsTableApiPtr->psNeighborCellRac = 33; 
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

   PsExternalCellTableApiPtr->psExtCellId = 33;  
   PsExternalCellTableApiPtr->lac = 33; 
   PsExternalCellTableApiPtr->pbcchArfcn = 530; 
   PsExternalCellTableApiPtr->mnc = 91; 
   PsExternalCellTableApiPtr->mcc = 91; 
   PsExternalCellTableApiPtr->bsic = 1; 
   PsExternalCellTableApiPtr->rac = 33; 
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

void addPcuTable()
{
   PcuTableApi * pcuTblApiBuff;
   PcuTableIndices pcuTableIndices;

   pcuTableIndices.dummyIndex = 1;
   if ( getPcuTable(&pcuTableIndices,&pcuTblApiBuff) == CLIB_SUCCESS )
   {
      printf("get getPcuTable  Success Full \n");
   }
   else
   {
      pcuTblApiBuff = ( PcuTableApi *)calloc(1,sizeof(PcuTableApi)); 

      pcuTblApiBuff->dummyIndex=(I_U16) 1;
      //pcuTblApiBuff->rrbpFlag= (I_U8)1;
      pcuTblApiBuff->tcVal = (I_U32)1;
      //pcuTblApiBuff->tFlowCtrlAck= (I_U32) 1;
      //pcuTblApiBuff->pcuTimerRetries=(I_U32) 1;
      pcuTblApiBuff->numContiguousPdch= (I_U32)4;
      pcuTblApiBuff->defaultChanCoding= (I_U32)1;
      pcuTblApiBuff->tlliBlkCoding= (I_U32)1;
      pcuTblApiBuff->maxUlAllocLength= (I_U32)1;
      pcuTblApiBuff->onePhSize = (I_U8)1;
      pcuTblApiBuff->globPwrCtrlFlag= (I_U32)1;

      if(insertPcuTable(pcuTblApiBuff) == CLIB_SUCCESS)
      {
         printf("addPcuTable : insertPcuTable successfull\n");
      }
      else
      {
         printf("addPcuTable : insertPcuTable unsuccessfull\n");
      }
   }
}

void addBSStable()
{
   /*Initialize BSS */
   BssTableApi *bssTableApiBuff;
   BssTableIndices bssTableIndices; 
   bssTableIndices.bscId = 1;
   if(deleteBssTable(&bssTableIndices) == CLIB_SUCCESS)
   {
      printf("Delet BSS Table Successful\n");
   }   
   if ( getBssTable(&bssTableIndices,&bssTableApiBuff) == CLIB_SUCCESS )
   {
      printf("get getBssTable  Success Full \n");
   }
   else
   {
      bssTableApiBuff = (BssTableApi *)calloc(1,sizeof(BssTableApi));
      bssTableApiBuff->bscId =1;
      bssTableApiBuff->gprsEnabled =1;   
      bssTableApiBuff->adminState = 0; /* Locked */   
      bssTableApiBuff->attInd = 0;
      bssTableApiBuff->bssReset = FALSE;
      bssTableApiBuff->callReestablishmentInd =  0;
      bssTableApiBuff->t3212 = 20;
      bssTableApiBuff->mcc = 91;
      bssTableApiBuff->mnc = 91;
      bssTableApiBuff->ncc = 5;
      bssTableApiBuff->nccPermitted = 200;
      bssTableApiBuff->dtxDnLinkInd = 1;
      bssTableApiBuff->dtxUpLinkInd = 1;
      bssTableApiBuff->minChannelGap = 3;
      /* bssTableApiBuff->cerPeriodicityTimer = 25;
         bssTableApiBuff->periodicCsAppTimer = 25;
         bssTableApiBuff->periodicCsStackTimer = 25;
         bssTableApiBuff->periodicPcuStackTimer = 25;
         bssTableApiBuff->periodicPlatformTimer = 25;
         bssTableApiBuff->periodicPsAppTimer = 25; 
      bssTableApiBuff->lRxLevDlP = 41;
      bssTableApiBuff->lRxLevUlP = 20;
      bssTableApiBuff->lRxQualDlP = 5;
      bssTableApiBuff->lRxQualUlP = 5; */
      bssTableApiBuff->maxRetrans = 4;
      /* bssTableApiBuff->timerTraceLog = 40; */
      bssTableApiBuff->txInteger = 12;
      bssTableApiBuff->radioLinkTimeout = 6;
      bssTableApiBuff->shutdownTimer = 231;
      /*bssTableApiBuff->enBsPctrl = FALSE;
      bssTableApiBuff->enMsPctrl = FALSE;
      bssTableApiBuff->rxDecStepSize = 1;
      bssTableApiBuff->rxIncrStepSize = 1;
      bssTableApiBuff->pConInterval = 31;
      bssTableApiBuff->qlAveraginNo = 29;
      bssTableApiBuff->rxTotalSamplesHigh = 21;
      bssTableApiBuff->rxTotalSamplesLow = 11;
      bssTableApiBuff->rxNoofSamplesLow = 11;
      bssTableApiBuff->rxNoOfSamplesHigh = 21;
      bssTableApiBuff->uRxLevDlP = 31;
      bssTableApiBuff->uRxLevUlP = 50;
      bssTableApiBuff->uRxQualDlP = 1;
      bssTableApiBuff->uRxQualUlP = 7; */
      bssTableApiBuff->cicMaster = 1;       

      if(insertBssTable(bssTableApiBuff) == CLIB_SUCCESS)
      {
         printf("addPcuTable : insertPcuTable successfull\n");
      }
      else
      {
         printf("addPcuTable : insertPcuTable unsuccessfull\n");
      }
   }
}

void removedCelltable(I_U32 cellId,I_U32 lac)
{
   CellTableIndices CellTableIndicesBuff ;
   CellTableIndicesBuff.cellId = cellId; 
   CellTableIndicesBuff.lac = lac; 
   if ( deleteCellTable(&CellTableIndicesBuff) == CLIB_SUCCESS ) 
   {
      printf("Delete Cell Table succesful\n");
   }
}


