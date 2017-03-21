#include <oamcfg_includes.h> 

#define CFG_RESET    0xffff
#define BSC_API_SET_CELLDATASTRUCT 0

extern int gTestCaseCompleted; 
void addbcchChannelGrp(); 
void addChannelgrp(); 
void addArfcnList(); 
void addLacTable(); 
void addPsCellTable(); 
//void addPSExternalCellTable(); 
//void addPSInternalCellTable(); 
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
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32]; 
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf(" Scenario 1 : Initial State: Locked /  Request Sent: Unlocked /  Pre-Condition:gprsEnabled=TRUE,PSStatus=Allowed\n"); 
      //deleteCellTables();

      CellTableIndicesBuff.cellId = 1; 
      CellTableIndicesBuff.lac = 1; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Scenario 1 : Update Cell Table Success Full \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi)); 
         CellTableApiPtr->cellId = 1; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 1; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Allowed*/
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
            printf("Scenario 1 : Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Scenario 1 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,6); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      
      if(getallBssTable(&bssTablePtr,&count1,&outsize) == CLIB_SUCCESS)
      {
         bssTablePtr->gprsEnabled = ENABLED;
         updateBssTable(bssTablePtr);
      }
      sleep(1);
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_UNLOCK_BSS);
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
               printf("Test Case 1 :Received Ack Successfully\n"); 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 1:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 1:Ack Receieved \n");
               }
               break;
           }
         case OAMS_CFG_PSCH_UNLOCK_REQ:
           {
              printf("Test Case 2 :Received OAMS_CFG_PSCH_UNLOCK_REQ: \n"); 
              oamsCfgPschUnlockReqPtr = (OamsCfgPschUnlockReq *)gCfgMsgBuf; 
              cfgStubSendPschCfgUnlockResp(oamsCfgPschUnlockReqPtr->lac,oamsCfgPschUnlockReqPtr->cellId,oamsCfgPschUnlockReqPtr->cellIndex,oamsCfgPschUnlockReqPtr->bvci);
              break;
           }
         case OAMS_CFG_CELLH_UNLOCK_REQ:
           {
              OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
              printf("Test Case 3 :Received OAMS_CFG_CELLH_UNLOCK_REQ \n"); 
              oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf; 
              cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);   
              break;
           }
         case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Test Case 4 :Received OAMS_CFG_AFH_ALARM_IND \n");
              gTestCaseCompleted = 1;
              break;
           }
      }
     }
}
void cellObjHandler2()
{
   static int testInitiation =1; 

   CellTableApi* CellTableApiPtr; 
   CellTableIndices  CellTableIndicesBuff; 
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32]; 
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf(" Scenario 2 : Initial State: Locked /  Request Sent: Unlocked /  Pre-Condition:gprsEnabled=FALSE,PSStatus=NotAllowed\n"); 
      //deleteCellTables();

      CellTableIndicesBuff.cellId = 1; 
      CellTableIndicesBuff.lac = 1; 
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS ) 
      { 
         CellTableApiPtr->adminState = 0; /* locked */ 
         updateCellTable(CellTableApiPtr); 
         printf("Scenario 2 : Update Cell Table Success Full \n"); 
      } 
      else 
      { 
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi)); 
         CellTableApiPtr->cellId = 1; 
         CellTableApiPtr->adminState = 0; /* locked */ 
         CellTableApiPtr->freqBandBcch = 0; 
         CellTableApiPtr->lac = 1; 
         CellTableApiPtr->bcchArfcn = 34; 
         CellTableApiPtr->bcc = 0; 
         CellTableApiPtr->msTxPwrMax = 10; 
         CellTableApiPtr->msTxPowerMaxCch = 10; 
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 2 : Insert CellTable Successfull \n"); 

         } 
         else 
         { 
            printf("Scenario 2 :Insert CellTable Unsuccessfull \n"); 
         } 
      } 
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,6); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      if(getallBssTable(&bssTablePtr,&count1,&outsize) == CLIB_SUCCESS)
      {
         bssTablePtr->gprsEnabled = DISABLED;
         updateBssTable(bssTablePtr);
      }
      sleep(1);
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_LOCK_BSS);
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
               printf("Test Case 1 :Received Ack Successfully\n"); 
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 1:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 1:Ack Receieved \n");
               }
               break;
           }
         case OAMS_CFG_CELLH_UNLOCK_REQ:
           {
              OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
              printf("Test Case 2 :Received OAMS_CFG_CELLH_UNLOCK_REQ \n");
              oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
              cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac);
              break;
           }
         case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Test Case 3 :Received OAMS_CFG_AFH_ALARM_IND \n");
              gTestCaseCompleted = 1;
              break;
           }
      }
   }
}


void cellObjHandler3()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 3 : Initial State: Locked /  Request Sent: Locked /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 3 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 3 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 3 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      CellTableApiPtr->adminState = 2; /* Shutdown */
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
               gTestCaseCompleted = 1;
               break;
           }
     }
   }
}

void cellObjHandler4()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   PsCellTableApi psCellTableApiBuff;
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 4 : Initial State: Locked /  Request Sent: Set PS Cell table /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 4 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 4 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 4 :Insert CellTable Unsuccessfull \n");
         }
      }
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,1); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      sleep(1);
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      CellTableApiPtr->adminState = 0; /* locked */
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      psCellTableApiBuff.maxNumPdchCell = 8;
      psCellTableApiBuff.minNumPdchCell = 1;
      psCellTableApiBuff.gprsCsInitial = 1;
      psCellTableApiBuff.gprsCsMax   = 4;
      psCellTableApiBuff.rac = 1;
      psCellTableApiBuff.lac = 1;
      psCellTableApiBuff.bvciId = 5;
      psCellTableApiBuff.raColour = 2;
      psCellTableApiBuff.maxNumTbfPdch = 4;
      psCellTableApiBuff.priorityAccessThr = 4;
      psCellTableApiBuff.ssb = 4;
      psCellTableApiBuff.gprsDlaEnabled = TRUE;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
     }
   }
}

void cellObjHandler5()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   PsCellTableApi psCellTableApiBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 5 : Initial State: Locked /  Request Sent: Delete from Cell Per Table /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 5 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 5 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 5 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      CellTableApiPtr->adminState = 0; /* locked */
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(CellTableApi),BSC_API_DEL_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
     }
   }
}

void cellObjHandler6()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   PsCellTableApi psCellTableApiBuff;
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 6 : Initial State: Locked /  Request Sent: Delete from PS Cell Table /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 6 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 6 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 6 :Insert CellTable Unsuccessfull \n");
         }
      }
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,1); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      sleep(1);
      CellDataStruct cellDataStructBuff;
      cellDataStructBuff.CellState    = locked;/*As required*/
      cellDataStructBuff.Availlability = FALSE;
      cellDataStructBuff.CellID       = 1;
      cellDataStructBuff.adminState= 0;
      cellDataStructBuff.lac= 1;
      cellDataStructBuff.reqType      = OAMS_RSN_OPERATORINITIATED;
      cfgStubSendCmMessage(&cellDataStructBuff, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      CellTableApiPtr->adminState = 0; /* locked */
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(CellTableApi),BSC_API_DEL_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
     }
   }
}

void cellObjHandler7()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 7 : Initial State: Locked /  Intermediate State: UnlockOrEnableInProgress / Final State: UnlockOrEnableProgress / Request Sent: BSC_API_SET_CELLPERTABLE /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 2;
      CellTableIndicesBuff.lac = 2;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 7 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 2;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 2;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 7 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 7 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      /*Update CellData before sending the message*/
      CellDataStruct cellData;
      cellData.CellState = unlockOrEnableInProgress;
      cellData.CellID = 2;
      cellData.Availlability = FALSE;
      cellData.lac = 2;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      CellTableApiPtr->adminState = 1; /* locked */
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }

}


void cellObjHandler8()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 8 : Initial State: Locked /  Intermediate State: UnlockOrEnableInProgress / Final State: UnlockOrEnableProgress / Request Sent: BSC_API_SET_CELLPERTABLE /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 2;
      CellTableIndicesBuff.lac = 2;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 8 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 2;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 2;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 8 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 8 :Insert CellTable Unsuccessfull \n");
         }
      }
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
               printf("Test Case 1 :Received Ack Successfully\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 1:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 1:Ack Receieved \n");
               }
               break;
           }
        case OAMS_CFG_CELLH_UNLOCK_REQ:
           {
               SysAlarm sysAlarmBuff;
               printf("Test Case 1 :Received OAMS_CFG_CELLH_UNLOCK_REQ \n");            
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               sysAlarmBuff.sysalarmId = 37;//MAX_BVC_BLOCK_TIMEOUT;
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType;
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId;
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac;
               cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);

               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               sysAlarmBuff.sysalarmId = 39;//BVC_RESET_TIMEOUT;
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType;
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId;
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac;
               cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);
           }
        case OAMS_CFG_PSCH_BVC_OP_FAILED:
           {
              printf("Test Case 2: Received OAMS_CFG_PSCH_BVC_OP_FAILED\n");
             // OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailedBuff;
             // oamsCfgPschBvcOpFailedBuff = *(OamsCfgPschBvcOpFailed*)gCfgMsgBuf;
             // printf("Alarm ID received : %d\n",oamsCfgPschBvcOpFailedBuff.sysAlarm.sysAlarmId);
             //gTestCaseCompleted = 1;
             break;
           }
        case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Received OAMS_CFG_AFH_ALARM_IND\n");
              gTestCaseCompleted = 1;
              break;
           }
      }
   }
}


void cellObjHandler9()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhUnlockReq *oamsCfgCellhUnlockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;

   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 9 : Initial State: Locked /  Intermediate State: UnlockOrEnableInProgress / Final State: UnlockOrEnableProgress / Request Sent: BSC_API_SET_CELLPERTABLE /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 2;
      CellTableIndicesBuff.lac = 2;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 8 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 2;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 2;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 8 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 8 :Insert CellTable Unsuccessfull \n");
         }
      }
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
               printf("Test Case 1 :Received Ack Successfully\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 1:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 1:Ack Receieved \n");
               }
               break;
           }
        case OAMS_CFG_CELLH_UNLOCK_REQ:
           {
               SysAlarm sysAlarmBuff;
               printf("Test Case 1 :Received OAMS_CFG_CELLH_UNLOCK_REQ \n");            
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               sysAlarmBuff.sysalarmId = 39;//BVC_RESET_TIMEOUT;
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType;
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId;
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac;
               cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);
               break;
           }
        case OAMS_CFG_PSCH_BVC_OP_FAILED:
           {
              printf("Test Case 2: Received OAMS_CFG_PSCH_BVC_OP_FAILED\n");
              //OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailedBuff;
              //oamsCfgPschBvcOpFailedBuff = *(OamsCfgPschBvcOpFailed*)gCfgMsgBuf;
              //printf("Alarm ID received : %d\n",oamsCfgPschBvcOpFailedBuff.sysAlarm.sysAlarmId);
              //gTestCaseCompleted = 1;
           }
           break;
        case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Received OAMS_CFG_AFH_ALARM_IND\n");
              gTestCaseCompleted = 1;
              break;
           }
      }
   }
}


void cellObjHandler10()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   PsCellTableApi psCellTableApiBuff;
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 10 : Initial State: Locked /  Intermediate State: UnlockOrEnableInProgress / Final State: UnlockOrEnableProgress / Request Sent: BSC_API_SET_CELLPERTABLE /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 10 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 6 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 6 :Insert CellTable Unsuccessfull \n");
         }
      }
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,1); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      sleep(1);
      /*Update CellData before sending the message*/
      CellDataStruct cellData;
      cellData.CellState = unlockOrEnableInProgress;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      CellTableApiPtr->adminState = 1; /* locked */
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler11()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   PsCellTableApi psCellTableApiBuff;
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 11 : Initial State: Locked /  Intermediate State: UnlockOrEnableInProgress / Final State: UnlockOrEnableProgress / Request Sent: BSC_API_DEL_PSCELLTABLE /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 2;
      CellTableIndicesBuff.lac = 2;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 11 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 2;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 2;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 11 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 11 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      CellDataStruct cellData;
      cellData.CellState = unlockOrEnableInProgress;
      cellData.CellID = 2;
      cellData.Availlability = FALSE;
      cellData.lac = 2;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      CellTableApiPtr->adminState = 1; /* locked */
      psCellTableApiBuff.cellId = 2;
      psCellTableApiBuff.lac = 2;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler12()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   PsCellTableApi psCellTableApiBuff;
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 12 : Initial State: Locked /  Intermediate State: UnlockOrEnableInProgress / Final State: UnlockOrEnableProgress / Request Sent: BSC_API_SET_CELLPERTABLE /  Pre-Condition:NA\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 2;
      CellTableIndicesBuff.lac = 2;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 0; /* locked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 12 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 2;
         CellTableApiPtr->adminState = 0; /* locked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 2;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 12 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 12 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      CellDataStruct cellData;
      cellData.CellState = unlockOrEnableInProgress;
      cellData.CellID = 2;
      cellData.Availlability = FALSE;
      cellData.lac = 2;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);

      CellTableApiPtr->adminState = 1; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
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
               gTestCaseCompleted = 1;
               removedCelltable(CellTableApiPtr->cellId, CellTableApiPtr->lac);
               break;
           }
      }
   }
}

/*CellObjectHandler ---- Unlocked-Disabled ----- Start*/
void cellObjHandler13()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 13 : Initial State: Unlocked-Disabled /  Intermediate State: NA / Final State: Unlocked-Disabled / Request Sent: BSC_API_SET_CELLPERTABLE(Modify)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 13 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Not Allowed*/
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
            printf("Scenario 13 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 13 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
//      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedDisabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
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
               printf("Test Case 1 :Received Ack Successfully\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Test Case 1:Nack Receieved \n");
               }
               else
               {
                  printf("Test Case 1:Ack Receieved \n");
               }
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler14()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 14 : Initial State: Unlocked-Disabled /  Intermediate State: NA / Final State: Unlocked-Disabled / Request Sent: BSC_API_SET_CELLPERTABLE(Lock)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 14 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Not Allowed*/
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
            printf("Scenario 14 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 14 :Insert CellTable Unsuccessfull \n");
         }
      }
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,1); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      sleep(1);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedDisabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      cfgStubSendCmMessage(CellTableApiPtr, sizeof(CellTableApi), BSC_API_LOCK_BSS);
      CellTableApiPtr->adminState = 0; /* Locked */
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler15()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 15 : Initial State: Unlocked-Disabled /  Intermediate State: NA / Final State: Unlocked-Disabled / Request Sent: BSC_API_SET_CELLPERTABLE(ShutDown)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 15 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Not Allowed*/
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
            printf("Scenario 15 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 15 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      cellData.CellState = unlockedDisabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 2; /* ShutDown */
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler16()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   PsCellTableApi psCellTableApiBuff;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 16 : Initial State: Unlocked-Disabled /  Intermediate State: NA / Final State: Unlocked-Disabled / Request Sent: BSC_API_SET_PSCELLTABLE\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 16 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Not Allowed*/
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
            printf("Scenario 16 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 16 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
//      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedDisabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 1; /* unlocked */
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler17()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   PsCellTableApi psCellTableApiBuff;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 16 : Initial State: Unlocked-Disabled /  Intermediate State: NA / Final State: Unlocked-Disabled / Request Sent: BSC_API_SET_PSCELLTABLE\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 16 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Not Allowed*/
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
            printf("Scenario 16 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 16 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedDisabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 1; /* unlocked */
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}


void cellObjHandler18()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 15 : Initial State: Unlocked-Disabled /  Intermediate State: NA / Final State: Unlocked-Disabled / Request Sent: BSC_API_SET_CELLPERTABLE(ShutDown)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 15 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Not Allowed*/
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
            printf("Scenario 15 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 15 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedDisabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 2; /* ShutDown */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
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
               gTestCaseCompleted = 1;
               break;
           }
      }
   }
}
/*CellObjectHandler ---- Unlocked-Disabled ----- End*/


/*CellObjectHandler ---- Unlocked-Enabled ----- Start*/
void cellObjHandler19()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 19 : Initial State: Unlocked-Enabled /  Intermediate State: LockOrDisableInProgress / Final State: Locked / Request Sent: BSC_API_SET_CELLPERTABLE(Lock)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->psAllowed = 1; /*Allowed*/
         updateCellTable(CellTableApiPtr);
         printf("Scenario 19 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 1; /*Allowed*/
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
            printf("Scenario 19 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 19 :Insert CellTable Unsuccessfull \n");
         }
      }
      if(getallBssTable(&bssTablePtr,&count1,&outsize) == CLIB_SUCCESS)
      {
         bssTablePtr->gprsEnabled = ENABLED;
         updateBssTable(bssTablePtr);
      }
      setBssPsPreConfigTable();
      addBSStable();
      addbcchChannelGrp(); 
      addPsCellTable(1,1);
      addChannelgrp();
      addArfcnList();
      addLacTable(1);
      addRaTable(1,1); 
      addCSInternalCellTable();
      addCSExternalCellTable();
      sleep(1);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedEnabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
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
               break;
           }
         case OAMS_CFG_CELLH_LOCK_REQ:
           {
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
           break;
           }
        case OAMS_CFG_PSCH_LOCK_REQ:
           {
              printf("Test Case 2 :Received OAMS_CFG_PSCH_LOCK_REQ: \n");
              oamsCfgPschLockReqPtr = (OamsCfgPschLockReq *)gCfgMsgBuf;
              cfgStubSendPschCfgLockResp(oamsCfgPschLockReqPtr->lac,oamsCfgPschLockReqPtr->cellId,oamsCfgPschLockReqPtr->cellIndex);
              break;
           }
        case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Test Case 3 :Received OAMS_CFG_AFH_ALARM_IND \n");
              gTestCaseCompleted = 1;
              break;
           }
      }
   }
}

void cellObjHandler20()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 20 : Initial State: Unlocked-Enabled /  Intermediate State: LockOrDisableInProgress / Final State: Locked / Request Sent: BSC_API_SET_CELLPERTABLE(Lock)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
         updateCellTable(CellTableApiPtr);
         printf("Scenario 20 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 20 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 20 :Insert CellTable Unsuccessfull \n");
         }
      }
      if(getallBssTable(&bssTablePtr,&count1,&outsize) == CLIB_SUCCESS)
      {
         bssTablePtr->gprsEnabled = DISABLED;
         updateBssTable(bssTablePtr);
      }
      sleep(1);
//      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedEnabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
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
               break;
           }
         case OAMS_CFG_CELLH_LOCK_REQ:
           {
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
           break;
           }
        case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Test Case 3 :Received OAMS_CFG_AFH_ALARM_IND \n");
              gTestCaseCompleted = 1;
              break;
           }
      }
   }
}

void cellObjHandler21()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
   CellDataStruct cellData;
 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 21 : Initial State: Unlocked-Enabled /  Intermediate State: NA / Final State: ShutdownInProgress / Request Sent: BSC_API_SET_CELLPERTABLE(Shutdown)\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 21 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 21 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 21 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
//      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedEnabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 2; /* Shutdown */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
      free(CellTableApiPtr);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_CELLH_BLOCK_IND :
         case OAMS_CFG_PSCH_SHUTDOWN_IND:
            {
               printf("Message received : %d", ((SysHdr*) gCfgMsgBuf)->msgType);
            }
            gTestCaseCompleted = 1;
            break;
      }
   }
}


void cellObjHandler22()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
   CellDataStruct cellData;
   PsCellTableApi psCellTableApiBuff;
   OamsPschCfgAlarmInd oamsPschCfgAlarmIndBuff; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 22 : Initial State: Unlocked-Enabled /  Intermediate State: NA / Final State: Unlocked-Enabled / Request Sent: BSC_API_SET_PSCELLTABLE, BSC_API_DEL_PSCELLTABLE, BSC_API_DEL_CELLPERTABLE\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 22 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 22 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 22 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      /*Update CellData before sending the data*/
      cellData.CellState = unlockedEnabled;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);

      SysAlarm sysAlarm;
      cfgStubSendPschCfgAlarmInd(sysAlarm);
      sysAlarm.sysalarmId = EVENT_PSSKS_BSSGP_MAX_BVC_UNBLOCK_TIMEOUT;
      cfgStubSendPsscmCfgAlarmInd(sysAlarm);
      sysAlarm.sysalarmId = EVENT_PSSKS_BSSGP_MAX_BVC_RESET_TIMEOUT;
      cfgStubSendPsscmCfgAlarmInd(sysAlarm);
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
               break;
           }
         case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Received OAMS_CFG_AFH_ALARM_IND\n");
              break;
           }
         case OAMS_CFG_PSCH_BVC_OP_FAILED:
           {
              printf("Received OAMS_CFG_PSCH_BVC_OP_FAILED\n");
              testInitiation--;
              if (testInitiation == -2)
              {
                 gTestCaseCompleted = 1;
              }
              break;
           }
      }
   }
}
/*CellObjectHandler ---- Unlocked-Enabled ----- End*/


/*CellObjectHandler ---- LockOrDisableInProgress ----- End*/
void cellObjHandler23()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
   CellDataStruct cellData;
   PsCellTableApi psCellTableApiBuff;
   OamsPschCfgAlarmInd oamsPschCfgAlarmIndBuff; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 23 : Initial State: LockOrDisableInProgress /  Intermediate State: NA / Final State: LockOrDisableInProgress or Unlocked-Enabled / Request Sent: BSC_API_SET_PSCELLTABLE, BSC_API_DEL_PSCELLTABLE, BSC_API_DEL_CELLPERTABLE\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 1;
      CellTableIndicesBuff.lac = 1;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 23 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 1;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 1;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 23 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 23 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
      /*Update CellData before sending the data*/
      cellData.CellState = lockeOrDisableInProgress;
      cellData.CellID = 1;
      cellData.Availlability = FALSE;
      cellData.lac = 1;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 2; /* shutdown */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
      CellTableApiPtr->adminState = 0; /* locked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);

      SysAlarm sysAlarm;
      cfgStubSendPschCfgAlarmInd(sysAlarm);
      sysAlarm.sysalarmId = EVENT_PSSKS_BSSGP_MAX_BVC_BLOCK_TIMEOUT;
      cfgStubSendPsscmCfgAlarmInd(sysAlarm);
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
               break;
           }
         case OAMS_CFG_AFH_ALARM_IND:
           {
              printf("Received OAMS_CFG_AFH_ALARM_IND\n");
              break;
           }
         case OAMS_CFG_PSCH_BVC_OP_FAILED:
           {
              printf("Received OAMS_CFG_PSCH_BVC_OP_FAILED\n");
              gTestCaseCompleted = 1;
              break;
           }
      }
   }
}


/*CellObjectHandler ---- ShutdownInProgress ----- End*/
void cellObjHandler24()
{
   static int testInitiation =1;

   CellTableApi* CellTableApiPtr;
   CellTableIndices  CellTableIndicesBuff;
   OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
   OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
   SysAlarm *sysAlarm;
   OamsCfgAfhSysAlarm *oamsCfgAfhSysAlarmPtr;
   BssTableApi *bssTablePtr;
   I_U32 count1;
   I_U16 outsize;
   I_U32 objectIdList[32];
   //TimeSlotTableApi *TimeSlotTableApiPtr;
   OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
   CellDataStruct cellData;
   PsCellTableApi psCellTableApiBuff;
   OamsPschCfgAlarmInd oamsPschCfgAlarmIndBuff; 
   if ( testInitiation )
   {
      testInitiation =0;
      printf(" Scenario 24 : Initial State: ShutdownInProgress /  Intermediate State: NA / Final State: ShutdownInProgress / Request Sent: BSC_API_SET_PSCELLTABLE, BSC_API_DEL_PSCELLTABLE, BSC_API_DEL_CELLPERTABLE\n");
//      deleteCellTables();

      CellTableIndicesBuff.cellId = 7;
      CellTableIndicesBuff.lac = 7;
      if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
      {
         CellTableApiPtr->adminState = 1; /* unlocked */
         updateCellTable(CellTableApiPtr);
         printf("Scenario 24 : Update Cell Table Success Full \n");
      }
      else
      {
         CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
         CellTableApiPtr->cellId = 7;
         CellTableApiPtr->adminState = 1; /* unlocked */
         CellTableApiPtr->freqBandBcch = 0;
         CellTableApiPtr->lac = 7;
         CellTableApiPtr->bcchArfcn = 34;
         CellTableApiPtr->bcc = 0;
         CellTableApiPtr->msTxPwrMax = 10;
         CellTableApiPtr->msTxPowerMaxCch = 10;
         //CellTableApiPtr->csStatus = 1; 
         CellTableApiPtr->psAllowed = 0; /*Not Allowed*/
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
            printf("Scenario 24 : Insert CellTable Successfull \n");

         }
         else
         {
            printf("Scenario 24 :Insert CellTable Unsuccessfull \n");
         }
      }
      sleep(1);
//      cfgStubSendCmMessage(NULL,0,CFG_RESET);
      /*Update CellData before sending the data*/
      cellData.CellState = blockInProgress;
      cellData.CellID = 7;
      cellData.Availlability = FALSE;
      cellData.lac = 7;
      cellData.reqType = OAMS_RSN_OPERATORINITIATED;
      cellData.adminState = 1;
      cfgStubSendCmMessage(&cellData, sizeof(CellDataStruct), BSC_API_SET_CELLDATASTRUCT);
      CellTableApiPtr->adminState = 1; /* unlocked */
      cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
      psCellTableApiBuff.cellId = 7;
      psCellTableApiBuff.lac = 7;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);

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
               testInitiation--;
               if (testInitiation == -3)
               {
                  gTestCaseCompleted = 1;
               }
               break;
           }
      }
   }
}

void addbcchChannelGrp() 
{ 
   ChnGrpTableApi* ChnGrpTableApiPtr; 
   ChnGrpTableIndices  chnGrpTableIndices; 

   chnGrpTableIndices.cellId=1; 
   chnGrpTableIndices.lac=1; 
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
      //ChnGrpTableApiPtr->tch = 47; 
      //ChnGrpTableApiPtr->pdch = 5; 
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
   ChnGrpTableIndices.cellId=1; 
   ChnGrpTableIndices.lac=1; 
   ChnGrpTableIndices.chnGrpId =1;


   if ( getChnGrpTable(&ChnGrpTableIndices, &ChnGrpTableApiPtr) == CLIB_SUCCESS ) 
   { 
      printf("addbcchChannelGrp :get Channel Group Table Success Full \n"); 
   } 
   else 
   { 
      ChnGrpTableApiPtr = ( ChnGrpTableApi *)calloc(1,sizeof(ChnGrpTableApi)); 

      ChnGrpTableApiPtr->chnGrpId = 1; 
      ChnGrpTableApiPtr->cellId = 1; 
      ChnGrpTableApiPtr->lac =1;
      ChnGrpTableApiPtr->bcchCcchSdcch4 = 0; 
      ChnGrpTableApiPtr->bcchCcch = 0; 
      ChnGrpTableApiPtr->sdcch8 = 0; 
      //ChnGrpTableApiPtr->tch = 47; 
      //ChnGrpTableApiPtr->pdch = 48; 
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
      //chnGrpTableApiPtr->tch = 47; 
      //chnGrpTableApiPtr->pdch = 47; 
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

/*Changes R2.5 Aricent -- Start*/
void addPsCellTable(I_U32 lac, I_U32 cellId)
{
   PsCellTableApi psCellTableApiBuff;
   psCellTableApiBuff.lac = lac;
   psCellTableApiBuff.cellId = cellId;
   psCellTableApiBuff.rac = 1;
   psCellTableApiBuff.raColour = 2;
   psCellTableApiBuff.bvciId = 3;
   psCellTableApiBuff.maxNumPdchCell = 8;
   psCellTableApiBuff.minNumPdchCell = 0;
   psCellTableApiBuff.maxNumTbfPdch = 8;
   psCellTableApiBuff.ssb = 0;
   psCellTableApiBuff.priorityAccessThr = 5;
   psCellTableApiBuff.gprsDlaEnabled = 0;
   psCellTableApiBuff.gprsCsMax = 8;
   psCellTableApiBuff.gprsCsInitial = 0;
   if (insertPsCellTable(&psCellTableApiBuff) == CLIB_SUCCESS)
   {
      printf("Insert PsCellTable successfull\n");
   } 
}
#if 0
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
#endif
/*Changes R2.5 Aricent -- End*/
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
   CellTableApiPtr->psAllowed = 1; 
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
#if 0
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
/* 
 I_U8    maxNumPdchCell;
   I_U8    minNumPdchCell;
   I_U8    maxNumTbfPdch;
   I_U8    ssb;
   I_U32    gprsDlaEnabled;
   I_U8    gprsCsMax;
   I_U8    gprsCsInitial;
*/
   psCellTableApiPtr->cellId = 1;  
   //psCellTableApiPtr->cellBarAccess2 = 1; 
   psCellTableApiPtr->raColour = 2; 
   psCellTableApiPtr->lac = 1; 
   //psCellTableApiPtr->pb = FALSE; 
   psCellTableApiPtr->rac = 6; 
   psCellTableApiPtr->bvciId = 3; 
   //psCellTableApiPtr->alpha = 10; 
   //psCellTableApiPtr->tAvgT= 20; 
   //psCellTableApiPtr->tAvgW = 20; 
   //psCellTableApiPtr->pb = 0; 
   //psCellTableApiPtr->pcMeasChan = 1; 
   //psCellTableApiPtr->panInc = 2; 
   //psCellTableApiPtr->panDec = 1; 
   //psCellTableApiPtr->panMax = 7; 
   psCellTableApiPtr->priorityAccessThr = 5; 
   //psCellTableApiPtr->psiCountHr = 8; 
   //psCellTableApiPtr->psiCountLr = 2; 
   //psCellTableApiPtr->accContrClass = 1; 
   //psCellTableApiPtr->maxRetrans1 = 1; 
   //psCellTableApiPtr->maxRetrans2 = 2; 
   //psCellTableApiPtr->maxRetrans3 = 4; 
   //psCellTableApiPtr->maxRetrans4 = 7; 
   //psCellTableApiPtr->s = 20; 
   //psCellTableApiPtr->txint = 2; 
   //psCellTableApiPtr->persistenceLevel = 12; 
   //psCellTableApiPtr->bsPccRel = 0; 
   //psCellTableApiPtr->bsPbcchBlks = 1; 
   //psCellTableApiPtr->bsPagBlksRes = 2; 
   //psCellTableApiPtr->bsPrachBlks = 3; 
   //psCellTableApiPtr->intMeasChannelListAvail = 1; 
   //psCellTableApiPtr->nAvgI = 5; 
   //psCellTableApiPtr->persistLevel1 = 5; 
   //psCellTableApiPtr->persistLevel2 = 7; 
   //psCellTableApiPtr->persistLevel3 = 10; 
   //psCellTableApiPtr->persistLevel4 = 14; 
   //psCellTableApiPtr->rflNumber = 3; 
   //psCellTableApiPtr->cellBarAccess2 = 1; 
   //psCellTableApiPtr->excAcc = 0; 
   //psCellTableApiPtr->gprsRxlevAccessMin = 25; 
   //psCellTableApiPtr->gprsMsTxPwrMaxCch = 30; 
   //psCellTableApiPtr->gprsGeneralCellReselectHysteresis = 5; 
   //psCellTableApiPtr->c31Hyst = 0; 
   //psCellTableApiPtr->c32Qual = 0; 
   //psCellTableApiPtr->randomAccessRetry = 1; 
   //psCellTableApiPtr->tresel = 250; 
   //psCellTableApiPtr->raReselectHysteresis = 1; 
   //psCellTableApiPtr->psi1RepeatPeriod = 12; 
   //psCellTableApiPtr->pacchPsiMsgBitMap = 48; 
   //psCellTableApiPtr->pbcchPsiMsgBitMap = 32; 
   //psCellTableApiPtr->pccchPsiMsgBitMap = 100; 
   //psCellTableApiPtr->btsPwrCtrlMode = 1; 
   //psCellTableApiPtr->prMode = 1; 
   //psCellTableApiPtr->dlBtsPwrCtrlEnabled = 0 ; 
   //psCellTableApiPtr->p0 = 2; 
   //psCellTableApiPtr->numOfPccchInCell = 7; 
   //psCellTableApiPtr->pccchBitMap = 7;       

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
/*Changes R2.5 Aricent -- Start*/
/*Changes R2.5 Aricent -- End*/
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

#endif
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
      bssTableApiBuff->tWaitCellBlock = 231;
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


