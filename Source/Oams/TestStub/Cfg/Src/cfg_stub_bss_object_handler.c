#include <oamcfg_includes.h>

extern int gTestCaseCompleted ;
extern BssTableApi gBssTableApiBuff;

#define CFG_RESET    0xffff

void deleteCellTables()
{
   CellTableIndices CellTableIndicesBuff;
   CellTableIndicesBuff.lac=1;
   CellTableIndicesBuff.cellId=1;
   if ( deleteCellTable(&CellTableIndicesBuff) == CLIB_SUCCESS )
   {
      printf( " Delete Cells is success ful\n");
   }

   CellTableIndicesBuff.lac=2;
   CellTableIndicesBuff.cellId=2;
   if ( deleteCellTable(&CellTableIndicesBuff) == CLIB_SUCCESS )
   {
      printf( " Delete Cells is success ful\n");
   }
   CellTableIndicesBuff.lac=3;
   CellTableIndicesBuff.cellId=3;
   if ( deleteCellTable(&CellTableIndicesBuff) == CLIB_SUCCESS )
   {
      printf( " Delete Cells is success ful\n");
   }
   CellTableIndicesBuff.lac=4;
   CellTableIndicesBuff.cellId=4;
   if ( deleteCellTable(&CellTableIndicesBuff) == CLIB_SUCCESS )
   {
      printf( " Delete Cells is success ful\n");
   }

   CellTableIndicesBuff.lac=21;
   CellTableIndicesBuff.cellId=1;
   if ( deleteCellTable(&CellTableIndicesBuff) == CLIB_SUCCESS )
   {
      printf( " Delete Cells is success ful\n");
   }
   cfgStubSendCmMessage(NULL,0,CFG_RESET);
}
void insertPsCellTables()
{
   CellTableApi *CellTableApiBuffPtr=NULL;
   CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));

   CellTableApiBuffPtr->cellId =2;
   CellTableApiBuffPtr->lac =2;
   CellTableApiBuffPtr->psStatus =1;
   CellTableApiBuffPtr->oprState =1;
   CellTableApiBuffPtr->adminState = 1; /* Unlocked */ 
   CellTableApiBuffPtr->freqBandBcch = GSM_1800;
   CellTableApiBuffPtr->bcchArfcn = 534;
   CellTableApiBuffPtr->bcc = 0;
   CellTableApiBuffPtr->msTxPowerMaxCch = 10;
   //CellTableApiBuffPtr->csStatus = ALLOWED;
   //CellTableApiBuffPtr->pageStatus = ALLOWED;
   CellTableApiBuffPtr->cellBarAccess = 1;
   CellTableApiBuffPtr->accessCtrlClass = 30;
   CellTableApiBuffPtr->bsAgBlksRes = 5;
   CellTableApiBuffPtr->bsPaMfrms = 5;
   CellTableApiBuffPtr->cellReselectHysteresis = 4;
   CellTableApiBuffPtr->rxLevAccessMin = 63;
   CellTableApiBuffPtr->powerOffset = 1;
   CellTableApiBuffPtr->msTxPwrMax = 10;


   insertCellTable( CellTableApiBuffPtr);

   /* Cell Unlock enable settings psstatus = enabled*/
   CellTableApiBuffPtr->cellId =3;
   CellTableApiBuffPtr->lac =3;
   CellTableApiBuffPtr->psStatus =1;
   CellTableApiBuffPtr->oprState =0;
   CellTableApiBuffPtr->adminState = 1; /* Unlocked */
   CellTableApiBuffPtr->freqBandBcch = GSM_1800;
   CellTableApiBuffPtr->bcchArfcn = 534;
   CellTableApiBuffPtr->bcc = 0;
   CellTableApiBuffPtr->msTxPowerMaxCch = 10;
   //CellTableApiBuffPtr->csStatus = ALLOWED;
   //CellTableApiBuffPtr->pageStatus = ALLOWED;
   CellTableApiBuffPtr->cellBarAccess = 1;
   CellTableApiBuffPtr->accessCtrlClass = 30;
   CellTableApiBuffPtr->bsAgBlksRes = 5;
   CellTableApiBuffPtr->bsPaMfrms = 5;
   CellTableApiBuffPtr->cellReselectHysteresis = 4;
   CellTableApiBuffPtr->rxLevAccessMin = 63;
   CellTableApiBuffPtr->powerOffset = 1;
   CellTableApiBuffPtr->msTxPwrMax = 10;


   insertCellTable( CellTableApiBuffPtr);
   addPcuTable();
   addLacTable(2);
   addLacTable(3);
   addPsCellTable(2,2);
   addPsCellTable(3,3);
   addRaTable(2,6);
   addRaTable(3,6);
   free(CellTableApiBuffPtr);
   cfgStubSendCmMessage(NULL,0,CFG_RESET);
}
void insertCellTables()
{
   /* Insert two Cell table */
   CellTableApi *CellTableApiBuffPtr=NULL;

   CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
   CellTableApiBuffPtr->cellId =1;
   CellTableApiBuffPtr->psStatus =0;
   CellTableApiBuffPtr->lac =1;
   CellTableApiBuffPtr->oprState =1;
   CellTableApiBuffPtr->adminState = 1; /* Unlocked */
   CellTableApiBuffPtr->freqBandBcch = GSM_1800;
   CellTableApiBuffPtr->bcchArfcn = 534;
   CellTableApiBuffPtr->bcc = 0;
   CellTableApiBuffPtr->msTxPowerMaxCch = 10;
   //CellTableApiBuffPtr->csStatus = ALLOWED;
   //CellTableApiBuffPtr->pageStatus = ALLOWED;
   CellTableApiBuffPtr->cellBarAccess = 1;
   CellTableApiBuffPtr->accessCtrlClass = 30;
   CellTableApiBuffPtr->bsAgBlksRes = 5;
   CellTableApiBuffPtr->bsPaMfrms = 5;
   CellTableApiBuffPtr->cellReselectHysteresis = 4;
   CellTableApiBuffPtr->rxLevAccessMin = 63;
   CellTableApiBuffPtr->powerOffset = 1;
   CellTableApiBuffPtr->msTxPwrMax = 10;


   insertCellTable( CellTableApiBuffPtr);



   /* Cell Unlock enable settings psstatus = disbled*/
   CellTableApiBuffPtr->cellId =4;
   CellTableApiBuffPtr->lac =4;
   CellTableApiBuffPtr->psStatus =0;
   CellTableApiBuffPtr->oprState =0;
   CellTableApiBuffPtr->adminState = 1; /* Unlocked */
   CellTableApiBuffPtr->freqBandBcch = GSM_1800;
   CellTableApiBuffPtr->bcchArfcn = 534;
   CellTableApiBuffPtr->bcc = 0;
   CellTableApiBuffPtr->msTxPowerMaxCch = 10;
   //CellTableApiBuffPtr->csStatus = ALLOWED;
   //CellTableApiBuffPtr->pageStatus = ALLOWED;
   CellTableApiBuffPtr->cellBarAccess = 1;
   CellTableApiBuffPtr->accessCtrlClass = 30;
   CellTableApiBuffPtr->bsAgBlksRes = 5;
   CellTableApiBuffPtr->bsPaMfrms = 5;
   CellTableApiBuffPtr->cellReselectHysteresis = 4;
   CellTableApiBuffPtr->rxLevAccessMin = 63;
   CellTableApiBuffPtr->powerOffset = 1;
   CellTableApiBuffPtr->msTxPwrMax = 10;


   insertCellTable( CellTableApiBuffPtr);
   addLacTable(1);
   addLacTable(4);

   free(CellTableApiBuffPtr);
   cfgStubSendCmMessage(NULL,0,CFG_RESET);

}

void  insertLARATable()
{
   LaTableApi *LaTablePtr;
   RaTableApi *RaTablePtr;

   LaTablePtr=(LaTableApi *)malloc(sizeof(LaTableApi));
   LaTablePtr->lac = 1;
   if ( insertLaTable(LaTablePtr) == CLIB_SUCCESS)
   {
      printf(" insert RA table is SUCCESS \n");
   }
   free(LaTablePtr);

   RaTablePtr=(RaTableApi *)malloc(sizeof(RaTableApi));
   RaTablePtr->lac = 1;
   RaTablePtr->rac = 1;
   if (insertRaTable(RaTablePtr) == CLIB_SUCCESS)
   {
      printf(" insert RA table is SUCCESS \n");
   }
   free(RaTablePtr);
}
I_Bool cfgUpdateBssTableToDb()
{
   BssTableApi* BssTableApiPtr;
   I_Bool   retVal;
   BssTableApiPtr = ( BssTableApi *)calloc(1 ,sizeof(BssTableApi));


   (* BssTableApiPtr) = gBssTableApiBuff;

   if ( updateBssTable(BssTableApiPtr) == CLIB_SUCCESS )
   {
      printf("update BSS Table Success Full \n");   
      retVal = TRUE;
   }
   else
   {
      printf("updation BSS Table Failed \n");   
      retVal = FALSE;
   }
   free(BssTableApiPtr );
   return retVal;
}

I_Bool cfgUpdateBssTableToLocalBuffer()
{
   BssTableApi* BssTableApiPtr;
   BssTableIndices  BssTableIndicesBuff;

   /* delete if any entry existis with bscId = 0 */
   BssTableIndicesBuff.bscId = 0;
   deleteBssTable(&BssTableIndicesBuff);
   BssTableIndicesBuff.bscId = 1;
   deleteBssTable(&BssTableIndicesBuff);

   BssTableIndicesBuff.bscId = 1;
   if ( getBssTable(&BssTableIndicesBuff, &BssTableApiPtr) == CLIB_SUCCESS )
   {
      printf("get BSS Table Success Full \n");
      gBssTableApiBuff = (*BssTableApiPtr);
      return TRUE;
   }
   else
   {
      BssTableApiPtr = ( BssTableApi *)calloc(1,sizeof(BssTableApi));
      BssTableApiPtr->bscId = 1;
      BssTableApiPtr->gprsEnabled =1;   
      BssTableApiPtr->adminState = LOCK; /* Locked */   
      BssTableApiPtr->attInd = ALLOWED;
      BssTableApiPtr->bssReset = FALSE;
      BssTableApiPtr->callReestablishmentInd =  ALLOWED;
      BssTableApiPtr->t3212 = 20;
      BssTableApiPtr->mcc = 24;
      BssTableApiPtr->mnc = 45;
      BssTableApiPtr->ncc = 5;
      BssTableApiPtr->nccPermitted = 200;
      BssTableApiPtr->dtxDnLinkInd = 1;
      BssTableApiPtr->dtxUpLinkInd = 1;
      BssTableApiPtr->minChannelGap = 3;
      /*BssTableApiPtr->cerPeriodicityTimer = 25;
         BssTableApiPtr->periodicCsAppTimer = 25;
         BssTableApiPtr->periodicCsStackTimer = 25;
         BssTableApiPtr->periodicPcuStackTimer = 25;
         BssTableApiPtr->periodicPlatformTimer = 25;
         BssTableApiPtr->periodicPsAppTimer = 25; 
         BssTableApiPtr->lRxLevDlP = 41;
         BssTableApiPtr->lRxLevUlP = 7;
         BssTableApiPtr->lRxQualDlP = 5;
         BssTableApiPtr->lRxQualUlP = 5; */
      BssTableApiPtr->maxRetrans = 4;
      /* BssTableApiPtr->timerTraceLog = 40; */
      BssTableApiPtr->txInteger = 12;
      BssTableApiPtr->radioLinkTimeout = 6;
      BssTableApiPtr->shutdownTimer = 231;
      BssTableApiPtr->cicMaster = 1;      
      /*BssTableApiPtr->enBsPctrl = FALSE;
         BssTableApiPtr->enMsPctrl = FALSE;
         BssTableApiPtr->rxDecStepSize = 1;
         BssTableApiPtr->rxIncrStepSize = 1;
         BssTableApiPtr->pConInterval = 31;
         BssTableApiPtr->qlAveraginNo = 29;
         BssTableApiPtr->rxTotalSamplesHigh = 21;
         BssTableApiPtr->rxTotalSamplesLow = 11;
         BssTableApiPtr->rxNoofSamplesLow = 11;
         BssTableApiPtr->rxNoOfSamplesHigh = 21;
         BssTableApiPtr->uRxLevDlP = 31;
         BssTableApiPtr->uRxLevUlP = 5;
         BssTableApiPtr->uRxQualDlP = 1;
         BssTableApiPtr->uRxQualUlP = 7;
         BssTableApiPtr->qlNoofSamplesHigh = 20;
         BssTableApiPtr->qlNoofSamplesLow = 20; 
         BssTableApiPtr->qlTotalSamplesHigh = 20;
         BssTableApiPtr->qlTotalSamplesLow = 20;
         BssTableApiPtr->rxAveraginNo = 20; */
      if ( insertBssTable(BssTableApiPtr) == CLIB_SUCCESS )
      {
         printf("Insert BSS Table Success Full \n");
         gBssTableApiBuff = (*BssTableApiPtr);   
         free(BssTableApiPtr);
         return TRUE;
      }
      else
         free(BssTableApiPtr);
   }

   return FALSE;
}
void cfgSendBscApiSetBssTable()
{

   printf(" Sendig BSC_API_SET_BSSTABLE Req to CFG \n");
   gBssTableApiBuff.bscId =1;
   gBssTableApiBuff.adminState = 1; /* unlocked */
   cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   /* Send lock BSS */
   gBssTableApiBuff.bscId =1;
   gBssTableApiBuff.adminState = 1; /* unlocked */
   cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);


}

void CfgInitHndlr2()
{
   CellTableApi *CellTableApiBuffPtr=NULL;
   static I_U32 testInitiation=1;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CfgInitHndlr2 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be unlocked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 1;  
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CfgInitHndlr2 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* delete  Cell table */
      deleteCellTables();
      /* Insert  LA-RA table */
      insertLARATable();
      /**********   preCondition ******* End *************/

   }
   else
   {

      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               printf("\n Received OAMS_CFG_SCM_UNLOCK_REQ\n");
               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  printf("  CFG_INIT_HNDLR_1 PASSED \n");
                  gTestCaseCompleted = 1;                  

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_INIT_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         default:
            break;
      }
   }

}
void CfgBssObjHndlr1()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  

      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* delete  Cell table */
      deleteCellTables();
      insertPsCellTables();
      /* Insert  LA-RA table */
      insertLARATable();

      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               printf("\n Received OAMS_CFG_SCM_UNLOCK_REQ\n");
               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  printf(" Sent  SCM_UNLOCK_RESP \n");
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);
                  printf(" Sent  SCM_ALRAM_IND \n");

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               printf("\n Received OAMS_CFG_GRHM_UNLOCK_REQ:\n");
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */
               printf("\n Sent OAMS_CFG_GRHM_UNLOCK_RESP:\n");

               printf("\n Sending UNLOCK_COMPLETE (GRHM )Alarm:\n");
               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmUnlockReq *OamsCfgPsscmUnlockReqPtr = ( OamsCfgPsscmUnlockReq * )gCfgMsgBuf;
               printf("\n Received OAMS_CFG_PSSCM_UNLOCK_REQ:\n");
               if ( OamsCfgPsscmUnlockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmUnlockReqPtr->ObjType, 0, objectIdList ,0, 0, 0, 0);

                  printf(" Sending PSAPP_PSSCM_CFG_LEP_ENABLED \n");
                  cfgStubSendMessage(NULL,0,ENT_OAM_OIL,
                        ENT_OAMS_CFG,
                        PSAPP_PSSCM_CFG_LEP_ENABLED,0);     

               }
               else 
                  if ( OamsCfgPsscmUnlockReqPtr->ObjType ==OAMS_OBJTYPE_CELL  )
                  {
                     OamsCfgPsscmUnlockReq* oamsCfgPsscmUnlockReqPtr;
                     oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
                     cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);


                  }
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED)
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
                  /* gTestCaseCompleted = 1; */
                  gTestCaseCompleted = 1; 
                  printf("  CFG_BSS_OBJ_HNDLR_1 PASSED \n");
               }
            }
            break;
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
            {
               cfgStubSendPcuCfgFirstNsvcEnabledResp();
            }
            break;
         case OAMS_CFG_PCUH_UNLOCK_REQ  :
            {
               OamsCfgPcuUnlockReq* oamsCfgPcuUnlockReqPtr;
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

            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {
            }

            break;
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ :
            {
               OamsCfgPcuCellEnabledReq* oamsCfgPcuCellEnabledReqPtr;
               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;

         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr2()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_2 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = FALSE;
      gBssTableApiBuff.adminState = 0;  
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_2 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* delete  Cell table */
      deleteCellTables();
      insertCellTables();
      /* Insert  LA-RA table */
      insertLARATable();


      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_2 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */

               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_2 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;

         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {
               printf("  Received OAMS_CFG_PSSCM_UNLOCK_REQ FAILED \n");
               gTestCaseCompleted = 1;   
               printf("  CFG_BSS_OBJ_HNDLR_2 FAILED \n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED )
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
                  printf("  CFG_BSS_OBJ_HNDLR_2 PASSED \n");
                  gTestCaseCompleted = 1;   
               }
            }
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

            }
            break;
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr3()
{
   /* Trigger Parameter Modification for BSS Table when BSS
       is in Locked state (Case: Success) */
   //static int qlAveraginNo            ;
   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_3\n");

   if ( testInitiation )
   {
      testInitiation =0;
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_3 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.adminState = 0; 

      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_3 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /*   Send the same DB row with parameter modification
             CFG should send back the SUCCESS resonse for this test case */
      gBssTableApiBuff.gprsEnabled =1; /* Modified Attribute */
      /* if ( gBssTableApiBuff.qlAveraginNo == 31 )
          gBssTableApiBuff.qlAveraginNo =  0;
          else
          gBssTableApiBuff.qlAveraginNo++;

          qlAveraginNo = gBssTableApiBuff.qlAveraginNo; */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
            {
               BssTableApi* BssTableApiPtr;
               BssTableIndices  BssTableIndicesBuff;

               printf("  CFG_BSS_OBJ_HNDLR_3 received CM_API_APP_RESPONSE  \n");

               BssTableIndicesBuff.bscId = 1;

               if ( getBssTable(&BssTableIndicesBuff, &BssTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get BSS Table Success Full \n");
               }


               if (( BssTableApiPtr->gprsEnabled == 1))   
               {
                  printf(" Updatoin is successful \n");
                  printf("  CFG_BSS_OBJ_HNDLR_3 PASSED \n");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_3 FAILED Failed to update Database \n");
                  gTestCaseCompleted = 1;      
               }

            }
            else
            {
               printf(" Updatoin is Failed \n");
               printf("  CFG_BSS_OBJ_HNDLR_3 FAILED \n");
               gTestCaseCompleted = 1;         
            }
            break;

         default:
            break;
      }
   }

}

void CfgBssObjHndlr4()
{
   /* Trigger Parameter Modification for BSS Table 
       with BSSReset= True when BSS is in Locked state*/

   static int testInitiation =1;


   printf("CFG_BSS_OBJ_HNDLR_4\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      /* First make the state to be Locked */
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_3 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;
         return;
      }
      gBssTableApiBuff.bscId =1;
      gBssTableApiBuff.adminState = 0; /* locked */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

      /* Now update the required content  into the 
          BSS table */



   }
   else
   {
      static I_U32 cmApi_response_count =0;
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
            {

               if (cmApi_response_count == 0 )
               {
                  cmApi_response_count++;
                  /* Send the Modifiecation fro the table */
                  gBssTableApiBuff.bscId =1;
                  gBssTableApiBuff.bssReset =1;
                  gBssTableApiBuff.adminState = 0; /* locked */
                  cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
               }
               else
               {
                  printf(" Bss reset  is successful \n");
                  printf("  CFG_BSS_OBJ_HNDLR_4 PASSED \n");
                  gTestCaseCompleted = 1;
               }

            }
            else
            {
               printf(" Updatoin is Failed \n");
               printf("  CFG_BSS_OBJ_HNDLR_4 FAILED \n");
               gTestCaseCompleted = 1;         
            }

         default:
            break;
      }
   }

}


void CfgBssObjHndlr5()
{
   /* Trigger Parameter Modification for BSS Table
       when BSS is in Locked state 
       (Case: Failure, No change in parameter value) */


   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_5\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_5 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.adminState = 0; 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_5 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      /**********   preCondition ******* End *************/
      /* Send the same DB row again , and CFG Should send back Nack
          for this test case */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
            {

               printf("  CFG_BSS_OBJ_HNDLR_5 PASSED \n");
               gTestCaseCompleted = 1;

            }
            else
            {
               printf("  CFG_BSS_OBJ_HNDLR_5 FAILED \n");
               gTestCaseCompleted = 1;         
            }
            break;

         default:
            printf(" Invalid message received \n");
            break;
      }
   }

}

void CfgBssObjHndlr6()
{
   /* Trigger BSS Unlock Table when BSS is 
       in Unlocked state */


   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_6\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_6 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /*  Pecondition : First make the state to be UnlLocked */
      gBssTableApiBuff.adminState = 1; 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_6 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      /**********   preCondition ******* End *************/
      /* Send the Unlock command 
          and CFG Should send back Nack
          for this test case */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
            {
               printf(" CM return CM_ERROR_END\n");
               printf("  CFG_BSS_OBJ_HNDLR_6 PASSED \n");
               gTestCaseCompleted = 1;

            }
            else
            {
               printf("  CFG_BSS_OBJ_HNDLR_6 FAILED \n");
               gTestCaseCompleted = 1;         
            }

            break;
         default:

            printf(" Invalid message received \n");
            break;
      }
   }

}

void CfgBssObjHndlr7()
{
   static int testInitiation =1;



   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be unLocked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 1;  /* Unlocked */ 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      deleteCellTables();
      insertCellTables();

      /**********   preCondition ******* End *************/
      cfgStubSendCmMessage(NULL,0,CFG_RESET);

      /* Now Send BSS LOCK to the CFG message */
      gBssTableApiBuff.adminState = 0;  

      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ:
            {
               if (((( OamsCfgPcuLockReq *)gCfgMsgBuf)->objType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
                  oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
                  cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);

               }
               else
               {
                  /* PCU will set the operational state of Gb to "Disabled" in DB 
                      and send Alarm Ind for state change to CFG. CFG will forward 
                      these alarms to OMC.*/
                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = GBINTERFACE_DISABLED;
                  cfgStubSendPcuCfgAlarmInd(sysAlarmBuff); 
                  /* Send PSAPP_CFG_PCU_LOCK_RESP  to CFG */
                  cfgStubSendPcuCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, 0);
               }

            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :
            {

               if ((( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
                  oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
                  //      memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
                  cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);

               }
               else
               {
                  /* . It will set NSVC and FR operational state as "Disabled" in DB 
                      and will send Alarm (SCN: NSVC, OST=Disabled) and 
                      Alarm (SCN: FR, OST=Disabled) to CFG to be forwarded to OMC. */

                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = NSVC_DISABLED;

                  cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);    
                  sysAlarmBuff.sysalarmId = FRLINK_DISABLED;

                  cfgStubSendPsscmCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, objectIdList, 0,0);
               }
            }
            break;
         case OAMS_CFG_SCM_LOCK_REQ :
            {
               /*CFG will send OAMS_CFG_SCM_LOCK_REQ (A Interface) to SCM via OIL.
                  All MTP3 link should be de-activated and SSP will be sent to MSC. 
                  SCM will mark operational state of MTP2 Link as "Disabled" in DB. 
                  If all MTP2 links are disabled, SCM will mark operational state of Linkset as
                  "Disabled" in DB.SCM gets SCCP_SCMG_SS_PROHIBIT alarm from BSSAP.
                  It will mark A Interface operational state as "Disabled" in DB and will send 
                  alarm to CFG. SCM will also forward SCCP_SCMG_SS_PROHIBIT alarm to CFG. */

               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_PROHIBITED);


            }
            break;
         case OAMS_CFG_GRHM_LOCK_REQ :
            {
               /* After getting SCCP_SCMG_SS_PROHIBIT alarm from SCM via OIL, 
                   CFG will send OAMS_CFG_GRHM_LOCK_REQ (A Interface) to GRHM.  */
               cfgStubSendGrhmCfgLockResp(OAMS_OBJTYPE_AINTERFACE, 0);
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm * OamsCfgAfhSysAlarmPtr = ( OamsCfgAfhSysAlarm * )gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED)
               {
                  printf(" BSS LOCKING PROCEDURE is success ful \n");
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = LOCK_COMPLETE;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);
                  printf("  CFG_BSS_OBJ_HNDLR_7 PASSED \n");
                  gTestCaseCompleted = 1;   

               }

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessPtr = ( OamsCfgCellhCellBarAccess * )gCfgMsgBuf;
               if (( OamsCfgCellhCellBarAccessPtr->cellBar == TRUE ) && (OamsCfgCellhCellBarAccessPtr->reason = OAMS_RSN_AINTERFACEDOWN))
               {
                  printf(" Received Cell BarrAccess \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ  :
            {
               OamsCfgCellhLockReq * oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr8()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("  CFG_BSS_OBJ_HNDLR_8 Started  ) \n");
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_8 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be unLocked */
      gBssTableApiBuff.gprsEnabled = FALSE;
      gBssTableApiBuff.adminState = 1;  /* Unlocked */ 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_8 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      deleteCellTables();
      insertCellTables();

      cfgStubSendCmMessage(NULL,0,CFG_RESET);


#if 0
      /* Insert two Cell table */

      CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
      CellTableApiBuffPtr->cellId =1;
      CellTableApiBuffPtr->lac =1;
      CellTableApiBuffPtr->adminState = 1; /* Unlocked */

      insertCellTable( CellTableApiBuffPtr);

      CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
      CellTableApiBuffPtr->cellId =2;
      CellTableApiBuffPtr->lac =2;
      CellTableApiBuffPtr->adminState = 1; /* Unlocked */          

      insertCellTable( CellTableApiBuffPtr);
      free (CellTableApiBuffPtr);
#endif
      /*       deleteCellTables(); */


      /**********   preCondition ******* End *************/

      /* Now Send BSS LOCK to the CFG message */
      gBssTableApiBuff.adminState = 0;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
#if 0            
         case OAMS_CFG_PCUH_LOCK_REQ:
            {
               if ((( (oamsCfgPcuLockReq *)gCfgMsgBuf)->objType) == OAMS_OBJTYPE_CELLCELL )
               {
                  cellObjHandler1();
               }
               else
               {
                  /* PCU will set the operational state of Gb to "Disabled" in DB 
                      and send Alarm Ind for state change to CFG. CFG will forward 
                      these alarms to OMC.*/
                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = gbInterface_disabled ;
                  cfgStubSendPcuCfgAlarmInd(sysAlarmBuff); 
                  /* Send PSAPP_CFG_PCU_LOCK_RESP  to CFG */
                  cfgStubSendPcuCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, 0);
               }

            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :
            {

               if ((( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->objType) == OAMS_OBJTYPE_CELL )
               {
                  cellObjHandler1();
               }
               else
               {
                  /* . It will set NSVC and FR operational state as "Disabled" in DB 
                      and will send Alarm (SCN: NSVC, OST=Disabled) and 
                      Alarm (SCN: FR, OST=Disabled) to CFG to be forwarded to OMC. */

                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = NSVC_DISABLED;

                  cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);    
                  sysAlarmBuff.sysalarmId = FR_Disabled;

                  cfgStubSendPsscmCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, objectIdList, 0.0);
               }
            }
            break;
#endif            
         case OAMS_CFG_SCM_LOCK_REQ :
            {
               /*CFG will send OAMS_CFG_SCM_LOCK_REQ (A Interface) to SCM via OIL.
                  All MTP3 link should be de-activated and SSP will be sent to MSC. 
                  SCM will mark operational state of MTP2 Link as "Disabled" in DB. 
                  If all MTP2 links are disabled, SCM will mark operational state of Linkset as
                  "Disabled" in DB.SCM gets SCCP_SCMG_SS_PROHIBIT alarm from BSSAP.
                  It will mark A Interface operational state as "Disabled" in DB and will send 
                  alarm to CFG. SCM will also forward SCCP_SCMG_SS_PROHIBIT alarm to CFG. */

               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_PROHIBITED);


            }
            break;
         case OAMS_CFG_GRHM_LOCK_REQ :
            {
               /* After getting SCCP_SCMG_SS_PROHIBIT alarm from SCM via OIL, 
                   CFG will send OAMS_CFG_GRHM_LOCK_REQ (A Interface) to GRHM.  */
               cfgStubSendGrhmCfgLockResp(OAMS_OBJTYPE_AINTERFACE, 0);
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm * OamsCfgAfhSysAlarmPtr = ( OamsCfgAfhSysAlarm * )gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED)
               {
                  printf(" BSS LOCKING PROCEDURE is success ful \n");
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = LOCK_COMPLETE;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);
                  printf("\n  CFG_BSS_OBJ_HNDLR_8 PASSED \n");
                  gTestCaseCompleted = 1;   

               }


            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessPtr = ( OamsCfgCellhCellBarAccess * )gCfgMsgBuf;
               if (( OamsCfgCellhCellBarAccessPtr->cellBar == TRUE ) && (OamsCfgCellhCellBarAccessPtr->reason = OAMS_RSN_AINTERFACEDOWN))
               {
                  printf("\n Recevied OAMS_CFG_CELLH_CELL_BAR_ACCESS\n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ  :
            {
               OamsCfgCellhLockReq * oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;

         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}
void CfgBssObjHndlr9()
{
   /* Trigger BSC_API_SET_BSSTABLE with adminState = Unlocked
       and with changed parameter value compared to the value stored in DB,
       When BSS adminState is "Unlocked" in DB*/

   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_9\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_9 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Unocked */
      gBssTableApiBuff.adminState = 1; 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_9 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      /**********   preCondition ******* End *************/
      /*   Send the same DB row with parameter modification
             CFG should send back the SUCCESS resonse for this test case */
      gBssTableApiBuff.gprsEnabled =~gBssTableApiBuff.gprsEnabled; /* Modified Attribute */

      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END )
            {
               printf(" CFG returned CM_ERR_END  \n");
               printf("  CFG_BSS_OBJ_HNDLR_9 PASSED \n");
               gTestCaseCompleted = 1;

            }
            else
            {
               printf("  CFG_BSS_OBJ_HNDLR_9 FAILED \n");
               gTestCaseCompleted = 1;         
            }
            break;

         default:
            break;
      }
   }

}

void CfgBssObjHndlr10()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_10 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_10 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* Insert two Cell table */
      deleteCellTables();

#if 0
      CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
      CellTableApiBuffPtr->cellId =1;
      CellTableApiBuffPtr->lac =1;
      CellTableApiBuffPtr->adminState = 1; /* Unlocked */

      insertCellTable( CellTableApiBuffPtr);

      CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
      CellTableApiBuffPtr->cellId =2;
      CellTableApiBuffPtr->lac =2;
      CellTableApiBuffPtr->adminState = 1; /* Unlocked */          

      insertCellTable( CellTableApiBuffPtr);
      free (CellTableApiBuffPtr);
#endif


      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_10 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */

               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_10 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmLockReq *OamsCfgPsscmLockReqPtr = ( OamsCfgPsscmLockReq * )gCfgMsgBuf;
               if ( OamsCfgPsscmLockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  SysAlarm sysAlarmbuff;
                  NsvcTableApi *nsvcTablePtr;
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmLockReqPtr->ObjType, 0, objectIdList,0, 0, 0, 0);

                  /*    a.   If Transport type is NS/FR, PS-SCM will start Unblock 
                           NSVC procedure. After Unblock NSVC procedure, SCM will mark 
                           NSVC and FR Opstate as "Enabled" in DB. It will send NSVC Enabled 
                           alarm to CFG via OIL after NSVC Unblock procedure towards peer is 
                           completed. It will also send FR Enabled alarm to CFG via OIL. . */

                  /* Insert NSVC in to the table */
                  nsvcTablePtr = (NsvcTableApi *)malloc(sizeof(NsvcTableApi));
                  nsvcTablePtr->nsvcId=1;
                  nsvcTablePtr->frIndex=16;
                  nsvcTablePtr->oprState =1 ;
                  if ( insertNsvcTable(nsvcTablePtr) != CLIB_SUCCESS )
                     if (updateNsvcTable(nsvcTablePtr) != CLIB_SUCCESS)
                     {
                        gTestCaseCompleted = 1;   
                        printf("  CFG_BSS_OBJ_HNDLR_10 FAILED \n");
                        return;
                     }

                  sysAlarmbuff.sysalarmId = NSVC_ENABLED;
                  cfgStubSendPsscmCfgAlarmInd(sysAlarmbuff);
               }
            }
            break;
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
            {
               gTestCaseCompleted = 1;   
               cfgStubSendPcuCfgFirstNsvcEnabledResp();
               printf(" Got OAMS_CFG_PCU_FIRST_NSVC_ENABLED_REQ for NSVC Alarm \n");
               printf("  CFG_BSS_OBJ_HNDLR_10 PASSED \n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED )
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
               }
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr11()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_11 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_11 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

#if 0
      /* Insert two Cell table */

      CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
      CellTableApiBuffPtr->cellId =1;
      CellTableApiBuffPtr->lac =1;
      CellTableApiBuffPtr->adminState = 1; /* Unlocked */

      insertCellTable( CellTableApiBuffPtr);

      CellTableApiBuffPtr = ( CellTableApi*)calloc(1,sizeof(CellTableApi));
      CellTableApiBuffPtr->cellId =2;
      CellTableApiBuffPtr->lac =2;
      CellTableApiBuffPtr->adminState = 1; /* Unlocked */          

      insertCellTable( CellTableApiBuffPtr);
      free (CellTableApiBuffPtr);

#endif

      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_11 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */

               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_11 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmLockReq *OamsCfgPsscmLockReqPtr = ( OamsCfgPsscmLockReq * )gCfgMsgBuf;
               if ( OamsCfgPsscmLockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmLockReqPtr->ObjType, 0, objectIdList ,0, 0, 0, 0);

                  /*    If Gb Interface TransportType is "IP_STATIC/IP_DYNAMIC", 
                           PS-SCM will Add Lep for all provisioned LEPs and will send 
                           PSAPP_PSSCM_CFG_LEP_ENABLED message to CFG. */
                  cfgStubSendPsscmCfgLepEnabled();
               }
            }
            break;
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
            {
               cfgStubSendPcuCfgFirstNsvcEnabledResp();
               printf(" \n Got OAMS_CFG_PCU_FIRST_NSVC_ENABLED_REQ for LEP ENABLED mesage \n"); 
               printf("  CFG_BSS_OBJ_HNDLR_11 PASSED \n");
               gTestCaseCompleted = 1;   
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED )
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
               }
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}
void CfgBssObjHndlr12()
{
   /*  During BSS UnlockInProgress i.e before
         sending response for Unlock message either for 
         SCM, GRHM etc, trigger BSC_API_SET_BSSTABLE 
         with adminState = Locked and with changed parameter 
         value compared to the value stored in DB*/


   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_12\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_12 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /*  Pecondition : First make the state to be Locked */
      gBssTableApiBuff.adminState = 0;  /* Locked  */
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_12 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      /**********   preCondition ******* End *************/

      /* Send the unLock command so that CFG would initiate
          UnLock procedure and bssState would move on to the unlockInProgress */
      gBssTableApiBuff.adminState = 1;  /* UnLocked  */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      static I_U8 cmAppApiResponseCount =0;
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if ( cmAppApiResponseCount == 0 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)

               {
                  cmAppApiResponseCount++;
               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_12 FAILED \n");
                  gTestCaseCompleted = 1;         
               }
            }
            else if ( cmAppApiResponseCount == 1 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  cmAppApiResponseCount++;

                  printf("  CFG_BSS_OBJ_HNDLR_12 PASSED \n");
                  gTestCaseCompleted = 1;

               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_12 FAILED \n");
                  gTestCaseCompleted = 1;         
               }            
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               /* Now BssState is in UnlockInProgress,
                   Send once again a Lock command
                   */
               printf(" Received OAMS_CFG_SCM_UNLOCK_REQ, Now initiating LOCK procedure ..\n");
               gBssTableApiBuff.adminState = 0;  /* Locked  */
               cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
            }
            break;


         default:
            printf(" Invalid message received \n");
            break;
      }
   }

}
void CfgBssObjHndlr13()
{
   /* During BSS LockInProgress i.e before sending response for
       Lock message either for SCM, GRHM etc, trigger BSC_API_SET_BSSTABLE 
       with adminState = Unlocked and with changed parameter value compared
       to the value stored in DB*/


   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_13\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_13 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /*  Pecondition : First make the state to be UnlLocked */
      gBssTableApiBuff.adminState = 1;  /* UnLocked  */
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_13 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      insertCellTables();
      /**********   preCondition ******* End *************/
      /* Send the Lock command so that CFG would initiate
          Lock procedure and bssState would move on to the lockInProgress */
      gBssTableApiBuff.adminState = 0;  /* Locked  */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      static I_U8 cmAppApiResponseCount =0;
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            if ( cmAppApiResponseCount == 0 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)

               {
                  cmAppApiResponseCount++;
               }
               else
               {
                  printf(" BSS Lock Procedure Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_13 FAILED \n");
                  gTestCaseCompleted = 1;         
               }
            }
            else if ( cmAppApiResponseCount == 1 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  cmAppApiResponseCount++;

                  printf("  CFG_BSS_OBJ_HNDLR_13 PASSED \n");
                  gTestCaseCompleted = 1;

               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_13 FAILED \n");
                  gTestCaseCompleted = 1;         
               }            
            }
            break;
            /*  case OAMS_CFG_SCM_LOCK_REQ: */
         case OAMS_CFG_CELLH_LOCK_REQ:
            {
               /* Now Send once again a LOCKED when 
                   already LockIsInProgress */
               printf("\n Received the CELL LOCK REQ \n");
               gBssTableApiBuff.adminState = 1;  /* UnLocked  */
               cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

            }
            break;

         default:
            printf(" Invalid message received \n");
            break;
      }
   }

}

void CfgBssObjHndlr14()
{
   /* Trigger BSC_API_SET_BSSTABLE with adminState = Locked"
       When BSS LockInProgress*/


   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_14\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_14 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /*  Pecondition : First make the state to be unLocked */
      gBssTableApiBuff.adminState = 1;  /* UnLocked  */
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_14 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      insertCellTables();

      /**********   preCondition ******* End *************/
      /* Send the Lock command so that CFG would initiate
          Lock procedure and bssState would move on to the lockInProgress */
      gBssTableApiBuff.adminState = 0;  /* Locked  */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      static I_U8 cmAppApiResponseCount =0;
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            printf(" \n received CM_API_APP_RESPONSE \n");
            if ( cmAppApiResponseCount == 0 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)

               {
                  cmAppApiResponseCount++;
               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_14 FAILED \n");
                  gTestCaseCompleted = 1;         
               }
            }
            else if ( cmAppApiResponseCount == 1 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  cmAppApiResponseCount++;

                  printf("  CFG_BSS_OBJ_HNDLR_14 PASSED \n");
                  gTestCaseCompleted = 1;

               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_14 FAILED \n");
                  gTestCaseCompleted = 1;         
               }            
            }
            break;
            /*   case OAMS_CFG_SCM_LOCK_REQ: */
         case OAMS_CFG_CELLH_LOCK_REQ:
            {
               /* Now Send once again a LOCKED when 
                   already LockIsInProgress */
               gBssTableApiBuff.adminState = 0;  /* Locked  */
               cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

            }
            break;

         default:
            printf(" Invalid message received \n");
            break;
      }
   }

}

void CfgBssObjHndlr15()
{
   /*  Trigger BSC_API_SET_BSSTABLE with adminState = Unlocked",
         When BSS UnlockInProgress*/


   static int testInitiation =1;

   printf("CFG_BSS_OBJ_HNDLR_15\n");

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_15 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /*  Pecondition : First make the state to be Locked */
      gBssTableApiBuff.adminState = 0;  /* Locked  */
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_15 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* Set LA Table and RA Table */
      insertLARATable();
      /**********   preCondition ******* End *************/
      /* Send the UnLock command so that CFG would initiate
          UnLock procedure and bssState would move on to the unlockInProgress */
      gBssTableApiBuff.adminState = 1;  /* UnLocked  */
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      static I_U8 cmAppApiResponseCount =0;
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case CM_API_APP_RESPONSE :
            printf("\n received CM_API_APP_RESPONSE \n");
            if ( cmAppApiResponseCount == 0 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)

               {
                  cmAppApiResponseCount++;
               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_15 FAILED \n");
                  gTestCaseCompleted = 1;         
               }
            }
            else if ( cmAppApiResponseCount == 1 )
            {
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  cmAppApiResponseCount++;

                  printf("  CFG_BSS_OBJ_HNDLR_15 PASSED \n");
                  gTestCaseCompleted = 1;

               }
               else
               {
                  printf(" Updatoin is Failed \n");
                  printf("  CFG_BSS_OBJ_HNDLR_15 FAILED \n");
                  gTestCaseCompleted = 1;         
               }            
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               /* Now Send once again a UnLOCKED when 
                   already LockIsInProgress */
               gBssTableApiBuff.adminState = 1;  /* UnLocked  */
               printf(" Received SCM_UNLOCK_REQ \n");
               cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

            }
            break;

         default:
            printf(" Invalid message received \n");
            break;
      }
   }

}


void CfgBssObjHndlr16()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_16 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_16 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      deleteCellTables();
      insertPsCellTables();


      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_16 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */

               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_16 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmLockReq *OamsCfgPsscmLockReqPtr = ( OamsCfgPsscmLockReq * )gCfgMsgBuf;
               if ( OamsCfgPsscmLockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  /* Sending UNLOCK RESPONSE Failure to CFG */
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmLockReqPtr->ObjType, 0, objectIdList ,0, OAMS_RSLT_FAILURE, 0, 0);

               }
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == GBINTERFACE_INIT_FAILED )
               {
                  printf(" Got GBINTERFACE_Init_Failed Alarm\n");
                  printf("  CFG_BSS_OBJ_HNDLR_16 PASSED \n");
                  gTestCaseCompleted = 1;   
               }
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}


void CfgBssObjHndlr17()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_17 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_17 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      deleteCellTables();
      insertPsCellTables();


      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_17 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */

               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_17 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmLockReq *OamsCfgPsscmLockReqPtr = ( OamsCfgPsscmLockReq * )gCfgMsgBuf;
               if ( OamsCfgPsscmLockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {

                  /* Hold the response ,DOn't send it to CFG ,
                      Without this response also , CFG should move
                      BSS UNLOKED */
                  /*   cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmLockReqPtr->ObjType, 0, objectIdList ,0, Failure, 0, 0)*/

               }
               else 
                  if ( OamsCfgPsscmLockReqPtr->ObjType == OAMS_OBJTYPE_CELL )
                  {
                     OamsCfgPsscmUnlockReq* oamsCfgPsscmUnlockReqPtr;
                     oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
                     cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);
                  }
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED )
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
                  printf("  CFG_BSS_OBJ_HNDLR_17 PASSED \n");
                  gTestCaseCompleted = 1;   
               }
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

            }
            break;
         case OAMS_CFG_PCUH_UNLOCK_REQ  :
            {
               OamsCfgPcuUnlockReq* oamsCfgPcuUnlockReqPtr;
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);

            }
            break;

         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr19()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  

      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* delete  Cell table */
      deleteCellTables();
      insertPsCellTables();
      /* Insert  LA-RA table */
      insertLARATable();
      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 11 : Success\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }

            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               printf("\n Received OAMS_CFG_SCM_UNLOCK_REQ\n");
               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  printf(" Sent  SCM_UNLOCK_RESP \n");
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);
                  printf(" Sent  SCM_ALRAM_IND \n");

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               printf("\n Received OAMS_CFG_GRHM_UNLOCK_REQ:\n");
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */
               printf("\n Sent OAMS_CFG_GRHM_UNLOCK_RESP:\n");

               printf("\n Sending UNLOCK_COMPLETE (GRHM )Alarm:\n");
               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmUnlockReq *OamsCfgPsscmUnlockReqPtr = ( OamsCfgPsscmUnlockReq * )gCfgMsgBuf;
               printf("\n Received OAMS_CFG_PSSCM_UNLOCK_REQ:\n");
               if ( OamsCfgPsscmUnlockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmUnlockReqPtr->ObjType, 0, objectIdList ,0, 0, 0, 0);

                  printf(" Sending PSAPP_PSSCM_CFG_LEP_ENABLED \n");
                  cfgStubSendMessage(NULL,0,ENT_OAM_OIL,
                        ENT_OAMS_CFG,
                        PSAPP_PSSCM_CFG_LEP_ENABLED,0);     

               }
               else 
                  if ( OamsCfgPsscmUnlockReqPtr->ObjType ==OAMS_OBJTYPE_CELL) 
                  {
                     OamsCfgPsscmUnlockReq* oamsCfgPsscmUnlockReqPtr;
                     oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
                     cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);


                  }
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED)
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
                  /* gTestCaseCompleted = 1; */
                  gTestCaseCompleted = 1; 
                  printf("  CFG_BSS_OBJ_HNDLR_1 PASSED \n");
               }
            }
            break;
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
            {
               cfgStubSendPcuCfgFirstNsvcEnabledResp();
            }
            break;
         case OAMS_CFG_PCUH_UNLOCK_REQ  :
            {
               OamsCfgPcuUnlockReq* oamsCfgPcuUnlockReqPtr;
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);

            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               SysAlarm sysAlarmBuff;
               OamsCfgCellhUnlockReq* oamsCfgCellhUnlockReqPtr;
               CellTableIndices CellTableIndicesBuff;
               CellTableApi *CellTableApiPtr;
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               CellTableIndicesBuff.cellId = oamsCfgCellhUnlockReqPtr->objId;
               CellTableIndicesBuff.lac =  oamsCfgCellhUnlockReqPtr->lac;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 1; /* unlocked */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
               }


               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac); 
               sysAlarmBuff.sysalarmId = CELL_ENABLED;
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType;
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId;
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac;
               cfgStubSendCellhCfgAlarmInd(sysAlarmBuff);

            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {
            }

            break;
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ :
            {
               OamsCfgPcuCellEnabledReq* oamsCfgPcuCellEnabledReqPtr;
               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;

         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr18()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  

      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* delete  Cell table */
      deleteCellTables();
      insertPsCellTables();
      /* Insert  LA-RA table */
      insertLARATable();
      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 11 : Success\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }

            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               printf("\n Received OAMS_CFG_SCM_UNLOCK_REQ\n");
               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  printf(" Sent  SCM_UNLOCK_RESP \n");
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);
                  printf(" Sent  SCM_ALRAM_IND \n");

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               printf("\n Received OAMS_CFG_GRHM_UNLOCK_REQ:\n");
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */
               printf("\n Sent OAMS_CFG_GRHM_UNLOCK_RESP:\n");

               printf("\n Sending UNLOCK_COMPLETE (GRHM )Alarm:\n");
               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmUnlockReq *OamsCfgPsscmUnlockReqPtr = ( OamsCfgPsscmUnlockReq * )gCfgMsgBuf;
               printf("\n Received OAMS_CFG_PSSCM_UNLOCK_REQ:\n");
               if ( OamsCfgPsscmUnlockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmUnlockReqPtr->ObjType, 0, objectIdList ,0, 0, 0, 0);

                  printf(" Sending PSAPP_PSSCM_CFG_LEP_ENABLED \n");
                  cfgStubSendMessage(NULL,0,ENT_OAM_OIL,
                        ENT_OAMS_CFG,
                        PSAPP_PSSCM_CFG_LEP_ENABLED,0);     

               }
               else 
                  if ( OamsCfgPsscmUnlockReqPtr->ObjType == OAMS_OBJTYPE_CELL )
                  {
                     OamsCfgPsscmUnlockReq* oamsCfgPsscmUnlockReqPtr;
                     oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
                     cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);


                  }
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED)
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
                  /* gTestCaseCompleted = 1; */
                  gTestCaseCompleted = 1; 
                  printf("  CFG_BSS_OBJ_HNDLR_1 PASSED \n");
               }
            }
            break;
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
            {
               cfgStubSendPcuCfgFirstNsvcEnabledResp();
            }
            break;
         case OAMS_CFG_PCUH_UNLOCK_REQ  :
            {
               OamsCfgPcuUnlockReq* oamsCfgPcuUnlockReqPtr;
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);

            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               SysAlarm sysAlarmBuff;
               OamsCfgCellhUnlockReq* oamsCfgCellhUnlockReqPtr;
               CellTableIndices CellTableIndicesBuff;
               CellTableApi *CellTableApiPtr;
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               CellTableIndicesBuff.cellId = oamsCfgCellhUnlockReqPtr->objId;
               CellTableIndicesBuff.lac =  oamsCfgCellhUnlockReqPtr->lac;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 0; /* locked */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
               }


               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac); 
               sysAlarmBuff.sysalarmId = CELL_ENABLED;
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType;
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId;
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac;
               cfgStubSendCellhCfgAlarmInd(sysAlarmBuff);

            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {
            }

            break;
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ :
            {
               OamsCfgPcuCellEnabledReq* oamsCfgPcuCellEnabledReqPtr;
               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ :
            {
               OamsCfgCellhLockReq *oamsCfgCellhLockReqPtr;
               printf("Received OAMS_CFG_CELLH_LOCK_REQ ");
               oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ :
            {
               /*              psappPcuCfgAlarmIndBuff.sysAlarm.sysalarmId = PSCell_Disabled;
                                       psappPcuCfgAlarmIndBuff.sysAlarm.k1 = oamsCfgPcuLockReqPtr->objType;
                                       psappPcuCfgAlarmIndBuff.sysAlarm.k2 = oamsCfgPcuLockReqPtr->objId;
                                       cfgStubSendPcuCfgAlarmInd(&psappPcuCfgAlarmIndBuff.sysAlarm);
                                       */
               OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
               oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
               cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);
            }
            break;

         case OAMS_CFG_PSSCM_LOCK_REQ :
            {
               OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr;
               oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
               //      memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
               cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);
               gTestCaseCompleted = 1;
               printf("bssTestCase 18 : Success\n");
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr20()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be Locked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 0;  

      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_1 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }

      /* delete  Cell table */
      deleteCellTables();
      insertPsCellTables();
      /* Insert  LA-RA table */
      insertLARATable();
      /**********   preCondition ******* End *************/

      /* Now Send BSS UNLOCK to the CFG message */
      gBssTableApiBuff.adminState = 1;  
      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 11 : Success\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }

            }
            break;
         case OAMS_CFG_SCM_UNLOCK_REQ:
            {
               OamsCfgScmUnlockReq *OamsCfgScmUnlockReqPtr=((OamsCfgScmUnlockReq *)gCfgMsgBuf) ;  ;


               printf("\n Received OAMS_CFG_SCM_UNLOCK_REQ\n");
               if ( OamsCfgScmUnlockReqPtr->ObjType == OAMS_OBJTYPE_AINTERFACE )
               {
                  SysAlarm SysAlarmBuff;

                  cfgStubSendCfgScmUnLockResp(OamsCfgScmUnlockReqPtr->ObjType, 0, objectIdList, 0,0);
                  printf(" Sent  SCM_UNLOCK_RESP \n");
                  /* Also Initiate A interface UP Alaram towards the CFG */
                  cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_ALLOWED);
                  printf(" Sent  SCM_ALRAM_IND \n");

               }
               else
               {
                  printf(" Object ID received is Wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }

            }
            break;
         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqPtr;
               oamsCfgGrhmUnlockReqPtr = (( OamsCfgGrhmUnlockReq *)gCfgMsgBuf);
               printf("\n Received OAMS_CFG_GRHM_UNLOCK_REQ:\n");
               cfgStubSendGrhmCfgUnlockResp(oamsCfgGrhmUnlockReqPtr->objType,oamsCfgGrhmUnlockReqPtr->objectId);

               /* Also Send the UNLOCK complete Alarm */
               printf("\n Sent OAMS_CFG_GRHM_UNLOCK_RESP:\n");

               printf("\n Sending UNLOCK_COMPLETE (GRHM )Alarm:\n");
               SysAlarm SysAlarmBuff;
               //SysAlarmBuff.sysalarmId = UNLOCK_COMPLETE;
               cfgStubSendGrhmCfgAlarmInd(SysAlarmBuff);

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessptr=((OamsCfgCellhCellBarAccess *)gCfgMsgBuf) ;  ;
               if (( OamsCfgCellhCellBarAccessptr->reason == OAMS_RSN_AINTERFACEUP ) && ( OamsCfgCellhCellBarAccessptr->cellBar == 0 ))
               {
                  printf( " received CELL_BAR_ACCESS \n");
               }
               else
               {
                  printf(" OAMS_CFG_CELLH_CELL_BAR_ACCESS content wrong \n");
                  printf("  CFG_BSS_OBJ_HNDLR_1 FAILED \n");
                  gTestCaseCompleted = 1;      
               }               
            }
            break;
         case OAMS_CFG_PSSCM_UNLOCK_REQ :
            {

               OamsCfgPsscmUnlockReq *OamsCfgPsscmUnlockReqPtr = ( OamsCfgPsscmUnlockReq * )gCfgMsgBuf;
               printf("\n Received OAMS_CFG_PSSCM_UNLOCK_REQ:\n");
               if ( OamsCfgPsscmUnlockReqPtr->ObjType == OAMS_OBJTYPE_GBINTERFACE )
               {
                  cfgStubSendPsscmCfgUnlockResp(OamsCfgPsscmUnlockReqPtr->ObjType, 0, objectIdList ,0, 0, 0, 0);

                  printf(" Sending PSAPP_PSSCM_CFG_LEP_ENABLED \n");
                  cfgStubSendMessage(NULL,0,ENT_OAM_OIL,
                        ENT_OAMS_CFG,
                        PSAPP_PSSCM_CFG_LEP_ENABLED,0);     

               }
               else 
                  if ( OamsCfgPsscmUnlockReqPtr->ObjType == OAMS_OBJTYPE_CELL )
                  {
                     OamsCfgPsscmUnlockReq* oamsCfgPsscmUnlockReqPtr;
                     oamsCfgPsscmUnlockReqPtr = (OamsCfgPsscmUnlockReq *) gCfgMsgBuf;
                     cfgStubSendPsscmCfgUnlockResp(oamsCfgPsscmUnlockReqPtr->ObjType, oamsCfgPsscmUnlockReqPtr->lengthOfList,oamsCfgPsscmUnlockReqPtr->objectIdList,oamsCfgPsscmUnlockReqPtr->e1Num, 0,0,oamsCfgPsscmUnlockReqPtr->lac);


                  }
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               printf("\n Received OAMS_CFG_AFH_ALARM_IND::\n");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED)
               {
                  printf(" Got BSS UNLOCKE Alarm \n");
                  /* gTestCaseCompleted = 1; */
                  gTestCaseCompleted = 1; 
                  printf("  CFG_BSS_OBJ_HNDLR_1 PASSED \n");
               }
            }
            break;
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ :
            {
               cfgStubSendPcuCfgFirstNsvcEnabledResp();
            }
            break;
         case OAMS_CFG_PCUH_UNLOCK_REQ  :
            {
               OamsCfgPcuUnlockReq* oamsCfgPcuUnlockReqPtr;
               oamsCfgPcuUnlockReqPtr = (OamsCfgPcuUnlockReq *)gCfgMsgBuf;

               cfgStubSendPcuCfgUnlockResp(oamsCfgPcuUnlockReqPtr->ObjType,oamsCfgPcuUnlockReqPtr->objId, oamsCfgPcuUnlockReqPtr->lac,0,0);

            }
            break;
         case OAMS_CFG_CELLH_UNLOCK_REQ  :
            {
               SysAlarm sysAlarmBuff;
               OamsCfgCellhUnlockReq* oamsCfgCellhUnlockReqPtr;
               CellTableIndices CellTableIndicesBuff;
               CellTableApi *CellTableApiPtr;
               oamsCfgCellhUnlockReqPtr =(OamsCfgCellhUnlockReq *)gCfgMsgBuf;
               CellTableIndicesBuff.cellId = oamsCfgCellhUnlockReqPtr->objId;
               CellTableIndicesBuff.lac =  oamsCfgCellhUnlockReqPtr->lac;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->msTxPwrMax = 9; /* Parameter Modification */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
               }


               cfgStubSendCellhCfgUnlockResp(oamsCfgCellhUnlockReqPtr->objType,oamsCfgCellhUnlockReqPtr->objId,oamsCfgCellhUnlockReqPtr->lac); 
               sysAlarmBuff.sysalarmId = CELL_ENABLED;
               sysAlarmBuff.key1 = oamsCfgCellhUnlockReqPtr->objType;
               sysAlarmBuff.key2 = oamsCfgCellhUnlockReqPtr->objId;
               sysAlarmBuff.key3 = oamsCfgCellhUnlockReqPtr->lac;
               cfgStubSendCellhCfgAlarmInd(sysAlarmBuff);

            }
            break;
         case OAMS_CELLH_CFG_ALARM_IND:
            {
            }

            break;
         case OAMS_CFG_PCUH_CELL_ENABLED_REQ :
            {
               OamsCfgPcuCellEnabledReq* oamsCfgPcuCellEnabledReqPtr;
               oamsCfgPcuCellEnabledReqPtr = (OamsCfgPcuCellEnabledReq *)gCfgMsgBuf;
               cfgStubSendCfgPcuCellEnabledResp(0,oamsCfgPcuCellEnabledReqPtr->objId,oamsCfgPcuCellEnabledReqPtr->lac);

            }
            break;

         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr21()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be unLocked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 1;  /* Unlocked */ 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      deleteCellTables();
      insertCellTables();

      /**********   preCondition ******* End *************/
      cfgStubSendCmMessage(NULL,0,CFG_RESET);

      /* Now Send BSS LOCK to the CFG message */
      gBssTableApiBuff.adminState = 0;  

      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 21 : Success\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }

            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ:
            {
               if (((( OamsCfgPcuLockReq *)gCfgMsgBuf)->objType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
                  oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
                  cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);

               }
               else
               {
                  /* PCU will set the operational state of Gb to "Disabled" in DB 
                      and send Alarm Ind for state change to CFG. CFG will forward 
                      these alarms to OMC.*/
                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = GBINTERFACE_DISABLED;
                  cfgStubSendPcuCfgAlarmInd(sysAlarmBuff); 
                  /* Send PSAPP_CFG_PCU_LOCK_RESP  to CFG */
                  cfgStubSendPcuCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, 0);
               }

            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :
            {

               if ((( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
                  oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
                  //      memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
                  cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);

               }
               else
               {
                  /* . It will set NSVC and FR operational state as "Disabled" in DB 
                      and will send Alarm (SCN: NSVC, OST=Disabled) and 
                      Alarm (SCN: FR, OST=Disabled) to CFG to be forwarded to OMC. */

                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = NSVC_DISABLED;

                  cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);    
                  sysAlarmBuff.sysalarmId = FRLINK_DISABLED;

                  cfgStubSendPsscmCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, objectIdList, 0,0);
               }
            }
            break;
         case OAMS_CFG_SCM_LOCK_REQ :
            {
               /*CFG will send OAMS_CFG_SCM_LOCK_REQ (A Interface) to SCM via OIL.
                  All MTP3 link should be de-activated and SSP will be sent to MSC. 
                  SCM will mark operational state of MTP2 Link as "Disabled" in DB. 
                  If all MTP2 links are disabled, SCM will mark operational state of Linkset as
                  "Disabled" in DB.SCM gets SCCP_SCMG_SS_PROHIBIT alarm from BSSAP.
                  It will mark A Interface operational state as "Disabled" in DB and will send 
                  alarm to CFG. SCM will also forward SCCP_SCMG_SS_PROHIBIT alarm to CFG. */

               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_PROHIBITED);


            }
            break;
         case OAMS_CFG_GRHM_LOCK_REQ :
            {
               /* After getting SCCP_SCMG_SS_PROHIBIT alarm from SCM via OIL, 
                   CFG will send OAMS_CFG_GRHM_LOCK_REQ (A Interface) to GRHM.  */
               cfgStubSendGrhmCfgLockResp(OAMS_OBJTYPE_AINTERFACE, 0);
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm * OamsCfgAfhSysAlarmPtr = ( OamsCfgAfhSysAlarm * )gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED)
               {
                  printf(" BSS LOCKING PROCEDURE is success ful \n");
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = LOCK_COMPLETE;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);
                  printf("  CFG_BSS_OBJ_HNDLR_7 PASSED \n");
                  gTestCaseCompleted = 1;   

               }

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessPtr = ( OamsCfgCellhCellBarAccess * )gCfgMsgBuf;
               if (( OamsCfgCellhCellBarAccessPtr->cellBar == TRUE ) && (OamsCfgCellhCellBarAccessPtr->reason = OAMS_RSN_AINTERFACEDOWN))
               {
                  printf(" Received Cell BarrAccess \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ  :
            {
               CellTableIndices CellTableIndicesBuff;
               CellTableApi *CellTableApiPtr;
               OamsCfgCellhLockReq * oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               CellTableIndicesBuff.cellId = oamsCfgCellhLockReqPtr->objId;
               CellTableIndicesBuff.lac =  oamsCfgCellhLockReqPtr->lac;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 1; /* Unlocked */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
               }
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}


void CfgBssObjHndlr22()
{
   static int testInitiation =1;
   static int testcase22 =0;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be unLocked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 1;  /* Unlocked */ 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      deleteCellTables();
      insertCellTables();

      /**********   preCondition ******* End *************/
      cfgStubSendCmMessage(NULL,0,CFG_RESET);

      /* Now Send BSS LOCK to the CFG message */
      gBssTableApiBuff.adminState = 0;  

      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  printf("TestCase 21 : Success\n");
               }
               else
               {
                  if(testcase22 ==1 )
                  {
                     printf("Ack Receieved \n");
                     gTestCaseCompleted = 1;
                  }
               }

            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ:
            {
               if (((( OamsCfgPcuLockReq *)gCfgMsgBuf)->objType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
                  oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
                  cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);

               }
               else
               {
                  /* PCU will set the operational state of Gb to "Disabled" in DB 
                      and send Alarm Ind for state change to CFG. CFG will forward 
                      these alarms to OMC.*/
                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = GBINTERFACE_DISABLED;
                  cfgStubSendPcuCfgAlarmInd(sysAlarmBuff); 
                  /* Send PSAPP_CFG_PCU_LOCK_RESP  to CFG */
                  cfgStubSendPcuCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, 0);
               }

            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :
            {

               if ((( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
                  oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
                  //      memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
                  cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);

               }
               else
               {
                  /* . It will set NSVC and FR operational state as "Disabled" in DB 
                      and will send Alarm (SCN: NSVC, OST=Disabled) and 
                      Alarm (SCN: FR, OST=Disabled) to CFG to be forwarded to OMC. */

                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = NSVC_DISABLED;

                  cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);    
                  sysAlarmBuff.sysalarmId = FRLINK_DISABLED;

                  cfgStubSendPsscmCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, objectIdList, 0,0);
               }
            }
            break;
         case OAMS_CFG_SCM_LOCK_REQ :
            {
               /*CFG will send OAMS_CFG_SCM_LOCK_REQ (A Interface) to SCM via OIL.
                  All MTP3 link should be de-activated and SSP will be sent to MSC. 
                  SCM will mark operational state of MTP2 Link as "Disabled" in DB. 
                  If all MTP2 links are disabled, SCM will mark operational state of Linkset as
                  "Disabled" in DB.SCM gets SCCP_SCMG_SS_PROHIBIT alarm from BSSAP.
                  It will mark A Interface operational state as "Disabled" in DB and will send 
                  alarm to CFG. SCM will also forward SCCP_SCMG_SS_PROHIBIT alarm to CFG. */

               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_PROHIBITED);


            }
            break;
         case OAMS_CFG_GRHM_LOCK_REQ :
            {
               /* After getting SCCP_SCMG_SS_PROHIBIT alarm from SCM via OIL, 
                   CFG will send OAMS_CFG_GRHM_LOCK_REQ (A Interface) to GRHM.  */
               cfgStubSendGrhmCfgLockResp(OAMS_OBJTYPE_AINTERFACE, 0);
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm * OamsCfgAfhSysAlarmPtr = ( OamsCfgAfhSysAlarm * )gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED)
               {
                  printf(" BSS LOCKING PROCEDURE is success ful \n");
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = LOCK_COMPLETE;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);
                  printf("  CFG_BSS_OBJ_HNDLR_7 PASSED \n");
                  gTestCaseCompleted = 1;   

               }

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessPtr = ( OamsCfgCellhCellBarAccess * )gCfgMsgBuf;
               if (( OamsCfgCellhCellBarAccessPtr->cellBar == TRUE ) && (OamsCfgCellhCellBarAccessPtr->reason = OAMS_RSN_AINTERFACEDOWN))
               {
                  printf(" Received Cell BarrAccess \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ  :
            {
               CellTableIndices CellTableIndicesBuff;
               CellTableApi *CellTableApiPtr;
               OamsCfgCellhLockReq * oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               CellTableIndicesBuff.cellId = oamsCfgCellhLockReqPtr->objId;
               CellTableIndicesBuff.lac =  oamsCfgCellhLockReqPtr->lac;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->adminState = 0; /* locked */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
                  testcase22 =1;
               }
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}

void CfgBssObjHndlr23()
{
   static int testInitiation =1;


   CellTableApi *CellTableApiBuffPtr=NULL;

   if ( testInitiation )
   {
      testInitiation =0;
      /**********   preCondition ******* Start *************/      
      if ( cfgUpdateBssTableToLocalBuffer() == FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( reading DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;
      }

      /* First make the state to be unLocked */
      gBssTableApiBuff.gprsEnabled = TRUE;
      gBssTableApiBuff.adminState = 1;  /* Unlocked */ 
      if ( cfgUpdateBssTableToDb()== FALSE )
      {
         printf("  CFG_BSS_OBJ_HNDLR_7 FAILED ( Updation of DB for BSS Table Failed ) \n");
         gTestCaseCompleted = 1;      
         return;      
      }
      deleteCellTables();
      insertCellTables();

      /**********   preCondition ******* End *************/
      cfgStubSendCmMessage(NULL,0,CFG_RESET);

      /* Now Send BSS LOCK to the CFG message */
      gBssTableApiBuff.adminState = 0;  

      cfgStubSendCmMessage(&gBssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);

   }
   else
   {
      I_U32 objectIdList[32];
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               printf (" got CM_API_APP_RESPONSE \n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status != CM_SUCCESS )
               {
                  printf("Nack Receieved \n");
                  gTestCaseCompleted = 1;
                  printf("TestCase 23 : Success\n");
                  printf("********************\n");
               }
               else
               {
                  printf("Ack Receieved \n");
               }

            }
            break;
         case OAMS_CFG_PCUH_LOCK_REQ:
            {
               if (((( OamsCfgPcuLockReq *)gCfgMsgBuf)->objType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPcuLockReq *oamsCfgPcuLockReqPtr;
                  oamsCfgPcuLockReqPtr = (OamsCfgPcuLockReq *) gCfgMsgBuf;
                  cfgStubSendPcuCfgLockResp(oamsCfgPcuLockReqPtr->objType,oamsCfgPcuLockReqPtr->objId,oamsCfgPcuLockReqPtr->lac);

               }
               else
               {
                  /* PCU will set the operational state of Gb to "Disabled" in DB 
                      and send Alarm Ind for state change to CFG. CFG will forward 
                      these alarms to OMC.*/
                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = GBINTERFACE_DISABLED;
                  cfgStubSendPcuCfgAlarmInd(sysAlarmBuff); 
                  /* Send PSAPP_CFG_PCU_LOCK_RESP  to CFG */
                  cfgStubSendPcuCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, 0);
               }

            }
            break;
         case OAMS_CFG_PSSCM_LOCK_REQ :
            {

               if ((( (OamsCfgPsscmLockReq *)gCfgMsgBuf)->ObjType) == OAMS_OBJTYPE_CELL )
               {
                  OamsCfgPsscmLockReq *oamsCfgPsscmLockReqPtr ;
                  oamsCfgPsscmLockReqPtr = (OamsCfgPsscmLockReq *)gCfgMsgBuf;
                  //      memcpy(objectIdList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->lengthOfList);
                  cfgStubSendPsscmCfgLockResp(oamsCfgPsscmLockReqPtr->ObjType,oamsCfgPsscmLockReqPtr->lengthOfList,oamsCfgPsscmLockReqPtr->ObjId,oamsCfgPsscmLockReqPtr->e1Num,oamsCfgPsscmLockReqPtr->lac);

               }
               else
               {
                  /* . It will set NSVC and FR operational state as "Disabled" in DB 
                      and will send Alarm (SCN: NSVC, OST=Disabled) and 
                      Alarm (SCN: FR, OST=Disabled) to CFG to be forwarded to OMC. */

                  SysAlarm sysAlarmBuff;
                  sysAlarmBuff.sysalarmId = NSVC_DISABLED;

                  cfgStubSendPsscmCfgAlarmInd(sysAlarmBuff);    
                  sysAlarmBuff.sysalarmId = FRLINK_DISABLED;

                  cfgStubSendPsscmCfgLockResp(OAMS_OBJTYPE_GBINTERFACE, 0, objectIdList, 0,0);
               }
            }
            break;
         case OAMS_CFG_SCM_LOCK_REQ :
            {
               /*CFG will send OAMS_CFG_SCM_LOCK_REQ (A Interface) to SCM via OIL.
                  All MTP3 link should be de-activated and SSP will be sent to MSC. 
                  SCM will mark operational state of MTP2 Link as "Disabled" in DB. 
                  If all MTP2 links are disabled, SCM will mark operational state of Linkset as
                  "Disabled" in DB.SCM gets SCCP_SCMG_SS_PROHIBIT alarm from BSSAP.
                  It will mark A Interface operational state as "Disabled" in DB and will send 
                  alarm to CFG. SCM will also forward SCCP_SCMG_SS_PROHIBIT alarm to CFG. */

               cfgStubSendScmCfgAlarmInd(AINTERFACE_DISABLED);
               cfgStubSendScmCfgAlarmInd(SCCP_SCMG_SS_PROHIBITED);


            }
            break;
         case OAMS_CFG_GRHM_LOCK_REQ :
            {
               /* After getting SCCP_SCMG_SS_PROHIBIT alarm from SCM via OIL, 
                   CFG will send OAMS_CFG_GRHM_LOCK_REQ (A Interface) to GRHM.  */
               cfgStubSendGrhmCfgLockResp(OAMS_OBJTYPE_AINTERFACE, 0);
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm * OamsCfgAfhSysAlarmPtr = ( OamsCfgAfhSysAlarm * )gCfgMsgBuf;
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED)
               {
                  printf(" BSS LOCKING PROCEDURE is success ful \n");
                  SysAlarm sysAlarmBuff;
                  //sysAlarmBuff.sysalarmId = LOCK_COMPLETE;
                  cfgStubSendGrhmCfgAlarmInd(sysAlarmBuff);
                  printf("  CFG_BSS_OBJ_HNDLR_7 PASSED \n");
                  gTestCaseCompleted = 1;   

               }

            }
            break;
         case OAMS_CFG_CELLH_CELL_BAR_ACCESS :
            {
               OamsCfgCellhCellBarAccess *OamsCfgCellhCellBarAccessPtr = ( OamsCfgCellhCellBarAccess * )gCfgMsgBuf;
               if (( OamsCfgCellhCellBarAccessPtr->cellBar == TRUE ) && (OamsCfgCellhCellBarAccessPtr->reason = OAMS_RSN_AINTERFACEDOWN))
               {
                  printf(" Received Cell BarrAccess \n");
               }
            }
            break;
         case OAMS_CFG_CELLH_LOCK_REQ  :
            {
               CellTableIndices CellTableIndicesBuff;
               CellTableApi *CellTableApiPtr;
               OamsCfgCellhLockReq * oamsCfgCellhLockReqPtr = (OamsCfgCellhLockReq *)gCfgMsgBuf;
               CellTableIndicesBuff.cellId = oamsCfgCellhLockReqPtr->objId;
               CellTableIndicesBuff.lac =  oamsCfgCellhLockReqPtr->lac;
               if ( getCellTable(&CellTableIndicesBuff, &CellTableApiPtr) == CLIB_SUCCESS )
               {
                  printf("get Celll Table Success Full \n");
                  CellTableApiPtr->msTxPwrMax = 9; /* Parameter Modification */
                  printf("cellObjHandler10:sending the lock message for the same cell");
                  cfgStubSendCmMessage(CellTableApiPtr,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
               }
               cfgStubSendCellhCfgLockResp(oamsCfgCellhLockReqPtr->objType,oamsCfgCellhLockReqPtr->objId,oamsCfgCellhLockReqPtr->lac);
            }
            break;
         default :
            printf(" No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));


      }

   }
}





