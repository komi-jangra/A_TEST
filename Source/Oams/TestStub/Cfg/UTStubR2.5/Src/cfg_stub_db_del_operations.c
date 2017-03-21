#include<oamcfg_includes.h>
#include<cfg_stub_dbhndlr.h>
extern int gTestCaseCompleted;

/************************************************************** setDbForBss2()*******************************************/

I_Bool setDbForBss2()
{
   BssTableApi*  bssTableApiBuff = NULL;
   BssTableApi*  bssTableApiPtr = NULL;
   I_S32 errCode = 0;
   I_Bool retVal = FALSE;
   I_S32 count = 0;
   I_U16 size  = 0;

   printf("\n setDbForBss");
   /* First set the required database */
   errCode = getallBssTable(&bssTableApiPtr, &count, &size);
   if (0 == count)
   {
      printf("\n count=%d", count);
      printf("\n getallBssTable, BSS Table has no entry");
   }

   bssTableApiBuff  = (BssTableApi*) calloc(1,sizeof(BssTableApi)); 
   if (NULL == bssTableApiBuff)
   {
      printf("\n malloc failed");
   }
   /*Initialize BSS */
   bssTableApiBuff->bscId =1;
   bssTableApiBuff->gprsEnabled =1;
   bssTableApiBuff->adminState =1; /* UnLocked */
   bssTableApiBuff->attInd = ALLOWED;
   bssTableApiBuff->bssReset = FALSE;
   bssTableApiBuff->callReestablishmentInd =  ALLOWED;
   bssTableApiBuff->t3212 = 20;
   bssTableApiBuff->mcc = 24;
   bssTableApiBuff->mnc = 45;
   bssTableApiBuff->ncc = 5;
   bssTableApiBuff->nccPermitted = 200;
   bssTableApiBuff->dtxDnLinkInd = 1;
   bssTableApiBuff->dtxUpLinkInd = 1;
   bssTableApiBuff->minChannelGap = 3;
   /*bssTableApiBuff->cerPeriodicityTimer = 25;
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
   /* bssTableApiBuff->enBsPctrl = FALSE;
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
   bssTableApiBuff->uRxLevUlP = 5;
   bssTableApiBuff->uRxQualDlP = 1;
   bssTableApiBuff->uRxQualUlP = 7;
   bssTableApiBuff->cicMaster = 1;
   bssTableApiBuff->qlNoofSamplesHigh = 20;
   bssTableApiBuff->qlNoofSamplesLow = 20;
   bssTableApiBuff->qlTotalSamplesHigh = 20;
   bssTableApiBuff->qlTotalSamplesLow = 20; */


   if  (0 != count)
   {

      if  (bssTableApiPtr->adminState != UNLOCK)
      {
         bssTableApiPtr->adminState = UNLOCK;
         printf("\n calling updateBssTable");
         errCode =  updateBssTable(bssTableApiPtr);
      }
   }
   else
   {
      printf("\n calling insertBssTable");
      errCode =  insertBssTable(bssTableApiBuff);
   }

   /* Free BSS Table Pointer */
   free(bssTableApiBuff);
   free(bssTableApiPtr);

   if (errCode != CLIB_SUCCESS)
   {
      printf("\n updateBssTable or insertBssTable Failed");
      return errCode;
   }
   else
   {
      printf("\n BSS Initialse is Success");
      retVal = CLIB_SUCCESS;
   }
   return retVal;

}/* end of setDbForBss2 */

I_S32 bssSetState(I_S32 state) 
{ 
   BssTableApi* bssTableApiPtr = PNULL;
   I_U16 outsize = 0; 
   I_S32 i = 0;          
   /* Check if BSS Admin State is LOCK or not */     
   /*ret = getAllBssTable( &bssTableApiPtr, &i);*/ 

   if (getallBssTable(&bssTableApiPtr,&i,&outsize) != CLIB_SUCCESS) 
   { 
      free(bssTableApiPtr); 
      printf("\n getAllBssTable Failed"); 
      return 0; 
   } 

   if (bssTableApiPtr->adminState == state) 
   {       
      return 1; 
   }  
   else 
   { 
      bssTableApiPtr->adminState = state; 
      if(updateBssTable(bssTableApiPtr) == CLIB_SUCCESS) 
         return 1; 
      else 
      { 
         printf("Updation Failed"); 
         return 0; 
      } 

   } 
   free(bssTableApiPtr); 
} 

/* Start of cfgCmDbHndlr117*/
void cfgCmDbHndlr117()
{
   static int testInitiation =1;

   BssTableApi bssTableApiBuff = {0};
   I_S32    errCode = 0;

   printf("\n cfgCmDbHndlr117 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr117: setDbForBss Failed");
         return ;
      }

      bssTableApiBuff.bscId = 1;
      cfgStubSendCmMessage(&bssTableApiBuff,sizeof(BssTableApi),BSC_API_DEL_BSSTABLE);         }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr117:Failed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr117:Success");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr117: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;

   }
}
/* end of cfgCmDbHndlr117*/

/* Start of cfgCmDbHndlr118*/
void cfgCmDbHndlr118()
{
   static int testInitiation =1;

   CellTableApi cellTableApiBuff = {0};
   CellTableApi* CellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   I_S32    errCode = 0;

   printf("\n cfgCmDbHndlr118 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr118: Cell table Deletion, Cell Locked");
      cellIndex.cellId = 1;
      cellIndex.lac = 1;

      errCode = deleteCellTable(&cellIndex);

      CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
      CellTableApiPtr->cellId = 1;
      CellTableApiPtr->adminState = LOCK; /* Locked */
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
         printf("Test Case 118 : Insert CellTable Successfull \n");

      }
      else
      {
         printf("Test Case 118 :Insert CellTable Unsuccessfull \n");
      }

      cellTableApiBuff.cellId = 1;
      cellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&cellTableApiBuff,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr118: Cell table Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr118:Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr118: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr118*/

/* Start of cfgCmDbHndlr119*/
void cfgCmDbHndlr119()
{
   static int testInitiation =1;

   CellTableApi cellTableApiBuff = {0};
   CellTableApi* CellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr119 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr119: Cell table Deletion, Cell Unlocked");
      cellIndex.cellId = 1;
      cellIndex.lac = 1;

      errCode = deleteCellTable(&cellIndex);

      CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
      CellTableApiPtr->cellId = 1;
      CellTableApiPtr->adminState = UNLOCK; /* Unlocked */
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
         printf("Test Case119:Insert CellTable Successfull \n");
      }
      else
      {
         printf("Test Case 119:Insert CellTable Unsuccessfull \n");
      }

      cellTableApiBuff.cellId = 1;
      cellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&cellTableApiBuff,sizeof(CellTableApi),BSC_API_DEL_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr119: Test case Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr119:Test Case Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr119: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr119*/

/* Start of cfgCmDbHndlr120*/
void cfgCmDbHndlr120()
{
   static int testInitiation =1;
   PsCellTableApi psCellTableApiBuff= {0};
   PsCellTableIndices psCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   CellTableApi* CellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   printf("\n cfgCmDbHndlr120 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr120: PsCell table Deletion, Cell locked");
      cellIndex.cellId = 1;
      cellIndex.lac = 1;

      errCode = deleteCellTable(&cellIndex);

      CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
      CellTableApiPtr->cellId = 1;
      CellTableApiPtr->adminState = LOCK; /* locked */
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
         printf("Test Case120 : Insert CellTable Successfull \n");
      }
      else
      {
         printf("Test Case120 :Insert CellTable Unsuccessfull \n");
      }

      psCellIndex.cellId =  20;
      psCellIndex.lac = 1;

      printf("\n cfgCmDbHndlr120: PsCell Update Request- Initiation");

      ret == deletePsCellTable(&psCellIndex);

      /* Set DB for PsCell Table*/
      psCellTableApiBuff.cellId = 20;
      psCellTableApiBuff.cellBarAccess2 = 1;
      psCellTableApiBuff.raColour = 2;
      psCellTableApiBuff.lac = 1;
      psCellTableApiBuff.pb = FALSE;
      psCellTableApiBuff.rac = 6;
      psCellTableApiBuff.bvciId = 3;
      psCellTableApiBuff.alpha = 10;
      psCellTableApiBuff.tAvgT= 20;
      psCellTableApiBuff.tAvgW = 20;
      psCellTableApiBuff.pb = 0;
      psCellTableApiBuff.pcMeasChan = 1;
      psCellTableApiBuff.panInc = 2;
      psCellTableApiBuff.panDec = 1;
      psCellTableApiBuff.panMax = 7;
      psCellTableApiBuff.priorityAccessThr = 5;
      psCellTableApiBuff.psiCountHr = 8;
      psCellTableApiBuff.psiCountLr = 2;
      psCellTableApiBuff.accContrClass = 1;
      psCellTableApiBuff.maxRetrans1 = 1;
      psCellTableApiBuff.maxRetrans2 = 2;
      psCellTableApiBuff.maxRetrans3 = 4;
      psCellTableApiBuff.maxRetrans4 = 7;
      psCellTableApiBuff.s = 20;
      psCellTableApiBuff.txint = 2;
      psCellTableApiBuff.persistenceLevel = 12;
      psCellTableApiBuff.bsPccRel = 0;
      psCellTableApiBuff.bsPbcchBlks = 1;
      psCellTableApiBuff.bsPagBlksRes = 2;
      psCellTableApiBuff.bsPrachBlks = 3;
      psCellTableApiBuff.intMeasChannelListAvail = 1;
      psCellTableApiBuff.nAvgI = 5;
      psCellTableApiBuff.persistLevel1 = 5;
      psCellTableApiBuff.persistLevel2 = 7;
      psCellTableApiBuff.persistLevel3 = 10;
      psCellTableApiBuff.persistLevel4 = 14;
      psCellTableApiBuff.rflNumber = 3;
      psCellTableApiBuff.cellBarAccess2 = 1;
      psCellTableApiBuff.excAcc = 0;
      psCellTableApiBuff.gprsRxlevAccessMin = 25;
      psCellTableApiBuff.gprsMsTxPwrMaxCch = 30;
      psCellTableApiBuff.gprsGeneralCellReselectHysteresis = 5;
      psCellTableApiBuff.c31Hyst = 0;
      psCellTableApiBuff.c32Qual = 0;
      psCellTableApiBuff.randomAccessRetry = 1;
      psCellTableApiBuff.tresel = 250;
      psCellTableApiBuff.raReselectHysteresis = 1;
      psCellTableApiBuff.psi1RepeatPeriod = 12;
      psCellTableApiBuff.pacchPsiMsgBitMap = 48;
      psCellTableApiBuff.pbcchPsiMsgBitMap = 53;
      psCellTableApiBuff.pccchPsiMsgBitMap = 50;
      //psCellTableApiBuff.btsPwrCtrlMode = 1;
      psCellTableApiBuff.prMode = 1;
      psCellTableApiBuff.dlBtsPwrCtrlEnabled = ENABLED ;
      psCellTableApiBuff.p0 = 2;
      psCellTableApiBuff.numOfPccchInCell = 7;
      psCellTableApiBuff.pccchBitMap = 7;

      errCode =  insertPsCellTable(&psCellTableApiBuff);

      if (CLIB_SUCCESS != errCode)
      {
         printf("\n cfgCmDbHndlr120: PsCell Delete Request- insertPsCellTable failed");
      }

      psCellTableApiBuff.cellId = 20;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr120:Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr120:Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr120: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr120*/

/* Start of cfgCmDbHndlr121*/
void cfgCmDbHndlr121()
{
   static int testInitiation =1;
   PsCellTableApi psCellTableApiBuff= {0};
   PsCellTableIndices psCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   CellTableApi* CellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   printf("\n cfgCmDbHndlr121 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr121: PsCell table Deletion, Cell Unlocked");
      cellIndex.cellId = 1;
      cellIndex.lac = 1;

      errCode = deleteCellTable(&cellIndex);

      CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(BssTableApi));
      CellTableApiPtr->cellId = 1;
      CellTableApiPtr->adminState = UNLOCK; /* Unocked */
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
         printf("Test Case121 : Insert CellTable Successfull \n");
      }
      else
      {
         printf("Test Case121 :Insert CellTable Unsuccessfull \n");
      }

      psCellIndex.cellId =  20;
      psCellIndex.lac = 1;

      printf("\n cfgCmDbHndlr121: PsCell Update Request- Initiation");

      ret == deletePsCellTable(&psCellIndex);

      /* Set DB for PsCell Table*/
      psCellTableApiBuff.cellId = 20;
      psCellTableApiBuff.cellBarAccess2 = 1;
      psCellTableApiBuff.raColour = 2;
      psCellTableApiBuff.lac = 1;
      psCellTableApiBuff.pb = FALSE;
      psCellTableApiBuff.rac = 6;
      psCellTableApiBuff.bvciId = 3;
      psCellTableApiBuff.alpha = 10;
      psCellTableApiBuff.tAvgT= 20;
      psCellTableApiBuff.tAvgW = 20;
      psCellTableApiBuff.pb = 0;
      psCellTableApiBuff.pcMeasChan = 1;
      psCellTableApiBuff.panInc = 2;
      psCellTableApiBuff.panDec = 1;
      psCellTableApiBuff.panMax = 7;
      psCellTableApiBuff.priorityAccessThr = 5;
      psCellTableApiBuff.psiCountHr = 8;
      psCellTableApiBuff.psiCountLr = 2;
      psCellTableApiBuff.accContrClass = 1;
      psCellTableApiBuff.maxRetrans1 = 1;
      psCellTableApiBuff.maxRetrans2 = 2;
      psCellTableApiBuff.maxRetrans3 = 4;
      psCellTableApiBuff.maxRetrans4 = 7;
      psCellTableApiBuff.s = 20;
      psCellTableApiBuff.txint = 2;
      psCellTableApiBuff.persistenceLevel = 12;
      psCellTableApiBuff.bsPccRel = 0;
      psCellTableApiBuff.bsPbcchBlks = 1;
      psCellTableApiBuff.bsPagBlksRes = 2;
      psCellTableApiBuff.bsPrachBlks = 3;
      psCellTableApiBuff.intMeasChannelListAvail = 1;
      psCellTableApiBuff.nAvgI = 5;
      psCellTableApiBuff.persistLevel1 = 5;
      psCellTableApiBuff.persistLevel2 = 7;
      psCellTableApiBuff.persistLevel3 = 10;
      psCellTableApiBuff.persistLevel4 = 14;
      psCellTableApiBuff.rflNumber = 3;
      psCellTableApiBuff.cellBarAccess2 = 1;
      psCellTableApiBuff.excAcc = 0;
      psCellTableApiBuff.gprsRxlevAccessMin = 25;
      psCellTableApiBuff.gprsMsTxPwrMaxCch = 30;
      psCellTableApiBuff.gprsGeneralCellReselectHysteresis = 5;
      psCellTableApiBuff.c31Hyst = 0;
      psCellTableApiBuff.c32Qual = 0;
      psCellTableApiBuff.randomAccessRetry = 1;
      psCellTableApiBuff.tresel = 250;
      psCellTableApiBuff.raReselectHysteresis = 1;
      psCellTableApiBuff.psi1RepeatPeriod = 12;
      psCellTableApiBuff.pacchPsiMsgBitMap = 48;
      psCellTableApiBuff.pbcchPsiMsgBitMap = 53;
      psCellTableApiBuff.pccchPsiMsgBitMap = 50;
      //psCellTableApiBuff.btsPwrCtrlMode = 1;
      psCellTableApiBuff.prMode = 1;
      psCellTableApiBuff.dlBtsPwrCtrlEnabled = ENABLED ;
      psCellTableApiBuff.p0 = 2;
      psCellTableApiBuff.numOfPccchInCell = 7;
      psCellTableApiBuff.pccchBitMap = 7;

      errCode =  insertPsCellTable(&psCellTableApiBuff);

      if (CLIB_SUCCESS != errCode)
      {
         printf("\n cfgCmDbHndlr121: PsCell Delete Request- insertPsCellTable failed");
      }

      psCellTableApiBuff.cellId = 1;
      psCellTableApiBuff.lac = 1;
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_DEL_PSCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr121: Test Case Passed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr121: Test Case Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr121: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr121*/


/* Start of cfgCmDbHndlr122*/
void cfgCmDbHndlr122()
{
   static int testInitiation =1;
   CsExternalCellTableApi csExtnCellTblApiBuff = {0};
   CsExternalCellTableIndices csExtnCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   printf("\n cfgCmDbHndlr122 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr122: CsExternalCells table Deletion: BSS Locked");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr122: setDbForBss Failed");
      }

      csExtnCellIndex.csExtCellId = 1;
      csExtnCellIndex.lac = 1;
      csExtnCellIndex.mnc = 1;
      csExtnCellIndex.mcc = 1;

      ret = deleteCsExternalCellTable(&csExtnCellIndex);

      csExtnCellTblApiBuff.csExtCellId = 1;
      csExtnCellTblApiBuff.lac = 1;
      csExtnCellTblApiBuff.bcchArfcn = 530;
      csExtnCellTblApiBuff.freqBandBcch = GSM_1800;
      csExtnCellTblApiBuff.mcc = 1;
      csExtnCellTblApiBuff.mnc = 1;
      csExtnCellTblApiBuff.ncc = 4;
      csExtnCellTblApiBuff.bcc = 5;

      if (CLIB_SUCCESS != insertCsExternalCellTable(&csExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr122: insertCsExternalCelltable- Insertion Failed");
      }

      cfgStubSendCmMessage(&csExtnCellTblApiBuff,sizeof(CsExternalCellTableApi),BSC_API_DEL_CSEXTERNALCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr122:Deletion Success");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("\n cfgCmDbHndlr122:Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr122: Msg Discarded ");
            }
      } /* end of Switch */

   }
} /* End of cfgCmDbHndlr122*/

/* Start of cfgCmDbHndlr123*/
void cfgCmDbHndlr123()
{
   static int testInitiation =1;
   CsExternalCellTableApi csExtnCellTblApiBuff = {0};
   CsExternalCellTableIndices csExtnCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;
   printf("\n cfgCmDbHndlr123 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr123: CsExternalCells table Deletion: BSS Unlocked");
      /* First set the BSS - precondition */
      errCode = setDbForBss2(); /* for setting admin state to UNLOCK */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr123: setDbForBss for Bss Unlock Failed");
      }

      csExtnCellIndex.csExtCellId = 1;
      csExtnCellIndex.lac = 1;
      csExtnCellIndex.mnc = 1;
      csExtnCellIndex.mcc = 1;

      ret = deleteCsExternalCellTable(&csExtnCellIndex);

      csExtnCellTblApiBuff.csExtCellId = 1;
      csExtnCellTblApiBuff.lac = 1;
      csExtnCellTblApiBuff.bcchArfcn = 530;
      csExtnCellTblApiBuff.freqBandBcch = GSM_1800;
      csExtnCellTblApiBuff.mcc = 1;
      csExtnCellTblApiBuff.mnc = 1;
      csExtnCellTblApiBuff.ncc = 4;
      csExtnCellTblApiBuff.bcc = 5;

      if (CLIB_SUCCESS != insertCsExternalCellTable(&csExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr123: insertCsExternalCelltable- Insertion Failed");
      }
      cfgStubSendCmMessage(&csExtnCellTblApiBuff,sizeof(CsExternalCellTableApi),BSC_API_DEL_CSEXTERNALCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr123: Test case passed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr123: Test case Failed");           }
                  break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr123: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr123*/

/* Start of cfgCmDbHndlr124*/
void cfgCmDbHndlr124()
{
   static int testInitiation =1;
   PsExternalCellTableApi psExtnCellTblApiBuff= {0};
   PsExternalCellTableIndices psExtnCellIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr124 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr124: PsExternalCells table Deletion: BSS Locked");
      /* First set the BSS - precondition */
      errCode = setDbForBss(); /* for  setting admin state to lock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr124: setDbForBss Failed");
      }

      psExtnCellIndex.psExtCellId =  10;
      psExtnCellIndex.lac =  10;
      psExtnCellIndex.mnc =  120;
      psExtnCellIndex.mcc =  99;

      errCode = deletePsExternalCellTable(&psExtnCellIndex);

      psExtnCellTblApiBuff.psExtCellId = 10;
      psExtnCellTblApiBuff.lac = 10;
      psExtnCellTblApiBuff.pbcchArfcn = 530;
      psExtnCellTblApiBuff.mnc = 120;
      psExtnCellTblApiBuff.mcc = 99;
      psExtnCellTblApiBuff.bsic = 1;
      psExtnCellTblApiBuff.rac = 15;
      psExtnCellTblApiBuff.cellBarAccess2 = 1; /* 1-Barred */
      psExtnCellTblApiBuff.gprsMsTxPwrMaxCch = 24;
      psExtnCellTblApiBuff.gprsRxLevAccessMin = 63;
      psExtnCellTblApiBuff.gprsTemporaryOffset = 5;
      psExtnCellTblApiBuff.gprsPenaltyTime = 320;
      psExtnCellTblApiBuff.gprsReselectOffset = 5;
      psExtnCellTblApiBuff.psi1RepeatPeriod = 16;
      psExtnCellTblApiBuff.si13PbcchLocation = TN1;
      psExtnCellTblApiBuff.pbcchArfcn = 1024;

      if (CLIB_SUCCESS != insertPsExternalCellTable(&psExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr124: PsExternalCell Insertion Failed");
      }

      cfgStubSendCmMessage(&psExtnCellTblApiBuff,sizeof(PsExternalCellTableApi),BSC_API_DEL_PSEXTERNALCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr124: PsexternalCells Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr124: Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr124: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr124*/

/* Start of cfgCmDbHndlr125*/
void cfgCmDbHndlr125()
{
   static int testInitiation =1;
   PsExternalCellTableApi psExtnCellTblApiBuff= {0};
   PsExternalCellTableIndices psExtnCellIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr125 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr125: PsExternalCells table Deletion: BSS Unlocked");
      /* First set the BSS - precondition */
      errCode = setDbForBss2(); /* for  setting admin state to UNLOCK */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr125: setDbForBss Failed");
         return ;
      }

      psExtnCellIndex.psExtCellId =  10;
      psExtnCellIndex.lac =  10;
      psExtnCellIndex.mnc =  120;
      psExtnCellIndex.mcc =  99;

      errCode = deletePsExternalCellTable(&psExtnCellIndex);

      psExtnCellTblApiBuff.psExtCellId = 10;
      psExtnCellTblApiBuff.lac = 10;
      psExtnCellTblApiBuff.pbcchArfcn = 530;
      psExtnCellTblApiBuff.mnc = 120;
      psExtnCellTblApiBuff.mcc = 99;
      psExtnCellTblApiBuff.bsic = 1;
      psExtnCellTblApiBuff.rac = 15;
      psExtnCellTblApiBuff.cellBarAccess2 = 1; /* 1-Barred */
      psExtnCellTblApiBuff.gprsMsTxPwrMaxCch = 24;
      psExtnCellTblApiBuff.gprsRxLevAccessMin = 63;
      psExtnCellTblApiBuff.gprsTemporaryOffset = 5;
      psExtnCellTblApiBuff.gprsPenaltyTime = 320;
      psExtnCellTblApiBuff.gprsReselectOffset = 5;
      psExtnCellTblApiBuff.psi1RepeatPeriod = 16;
      psExtnCellTblApiBuff.si13PbcchLocation = TN1;
      psExtnCellTblApiBuff.pbcchArfcn = 1024;

      if (CLIB_SUCCESS != insertPsExternalCellTable(&psExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr125: PsExternalCell Insertion Failed");
      }

      cfgStubSendCmMessage(&psExtnCellTblApiBuff,sizeof(PsExternalCellTableApi),BSC_API_DEL_PSEXTERNALCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr125: Test Case Passed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr125:Test Case Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr125: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr125*/

/* Start of cfgCmDbHndlr126*/
void cfgCmDbHndlr126()
{
   static int testInitiation =1;
   LaTableApi laTblApiBuff= {0};
   LaTableIndices laTblIndex= {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr126 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr126: La table Deletion: BSS Locked");

      /* First set the BSS - precondition */
      errCode = setDbForBss(); /* for  setting admin state to lock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr126: setDbForBss Failed");
         return ;
      }

      laTblIndex.lac = 1;

      errCode = deleteLaTable(&laTblIndex);

      laTblApiBuff.lac= 1;
      if (CLIB_SUCCESS != insertLaTable(&laTblApiBuff))
      {
         printf("\n cfgCmDbHndlr126: LaTable Insertion Failed");
      }

      cfgStubSendCmMessage(&laTblApiBuff, sizeof(LaTableApi),
            BSC_API_DEL_LATABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr126: La Table Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr126: La Table Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr126: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr126*/

/* Start of cfgCmDbHndlr127*/
void cfgCmDbHndlr127()
{
   static int testInitiation =1;
   LaTableApi laTblApiBuff= {0};
   LaTableIndices laTblIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr127 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr127: La table Deletion: BSS Unlocked");
      /* First set the BSS - precondition */
      errCode = setDbForBss2(); /* for  setting admin state to unlock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr127: setDbForBss Failed");
         return ;
      }

      laTblIndex.lac = 1;

      errCode = deleteLaTable(&laTblIndex);

      laTblApiBuff.lac= 1;
      if (CLIB_SUCCESS != insertLaTable(&laTblApiBuff))
      {
         printf("\n cfgCmDbHndlr127: LaTable Insertion Failed");
      }

      cfgStubSendCmMessage(&laTblApiBuff, sizeof(LaTableApi),
            BSC_API_DEL_LATABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr127: Test case Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr127: test case Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr127: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
}
/* End of cfgCmDbHndlr127*/

/* Start of cfgCmDbHndlr128*/
void cfgCmDbHndlr128()
{
   static int testInitiation =1;
   RaTableApi raTblApiBuff= {0};
   RaTableIndices raTblIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr128 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr128: La table Deletion: BSS Locked");
      /* First set the BSS - precondition */
      errCode = setDbForBss(); /* for  setting admin state to lock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr128: setDbForBss Failed");
      }

      raTblIndex.lac = 1;
      raTblIndex.rac = 1;

      errCode = deleteRaTable(&raTblIndex);

      raTblApiBuff.lac = 1;
      raTblApiBuff.rac = 1;

      if (CLIB_SUCCESS != insertRaTable(&raTblApiBuff))
      {
         printf("\n cfgCmDbHndlr128: RaTable Insertion Failed");
      }

      cfgStubSendCmMessage(&raTblApiBuff,sizeof(RaTableApi),BSC_API_DEL_RATABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr128:Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr128:Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr128: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr128*/

/* Start of cfgCmDbHndlr129 */
void cfgCmDbHndlr129()
{
   static int testInitiation =1;
   RaTableApi raTblApiBuff= {0};
   RaTableIndices raTblIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr129 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr129: La table Deletion: BSS Unocked");
      /* First set the BSS - precondition */
      errCode = setDbForBss2(); /* for  setting admin state to unlock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr129: setDbForBss Failed");
      }

      raTblIndex.lac = 1;
      raTblIndex.rac = 1;

      errCode = deleteRaTable(&raTblIndex);

      raTblApiBuff.lac = 1;
      raTblApiBuff.rac = 1;

      if (CLIB_SUCCESS != insertRaTable(&raTblApiBuff))
      {
         printf("\n cfgCmDbHndlr129: RaTable Insertion Failed");
         return;
      }

      cfgStubSendCmMessage(&raTblApiBuff,sizeof(RaTableApi),BSC_API_DEL_RATABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr129: Test case Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr129: test case Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr129: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr129 */

/* Start of cfgCmDbHndlr130*/
void cfgCmDbHndlr130()
{
   static int testInitiation =1;
   CellTableApi* CellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   ChnGrpTableApi chnGrpTblApiBuff= {0};
   ChnGrpTableIndices chnGrpIndex= {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr130 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr130: ChnGrp Table Deletion: Cell Locked");

      cellIndex.cellId = 1;
      cellIndex.lac = 1;

      errCode = deleteCellTable(&cellIndex);

      CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
      CellTableApiPtr->cellId = 1;
      CellTableApiPtr->adminState = LOCK; /* Locked */
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
         printf("TestCase 130: Insert CellTable Successfull");
      }
      else
      {
         printf("TestCase 130: Insert CellTable Unsuccessfull");
      }

      chnGrpIndex.cellId =  20;
      chnGrpIndex.lac = 1;

      errCode = deleteChnGrpTable(&chnGrpIndex);

      chnGrpTblApiBuff.cellId = 20;
      chnGrpTblApiBuff.lac = 1;
      chnGrpTblApiBuff.tch = 30;
      chnGrpTblApiBuff.pdch = 30;
      chnGrpTblApiBuff.bcchCcchSdcch4 = 1;
      chnGrpTblApiBuff.bcchCcch = 1;
      chnGrpTblApiBuff.sdcch8 = 2;
      chnGrpTblApiBuff.hsn = 30;
      chnGrpTblApiBuff.maxTxPwr = 20000;
      chnGrpTblApiBuff.tsc = 5;
      chnGrpTblApiBuff.band = GSM_900;
      chnGrpTblApiBuff.validArfcns = 5;
      chnGrpTblApiBuff.arfcn1 = 124;
      chnGrpTblApiBuff.arfcn2 = 124;
      chnGrpTblApiBuff.arfcn3 = 124;
      chnGrpTblApiBuff.arfcn4 = 124;
      chnGrpTblApiBuff.arfcn5 = 124;

      if (CLIB_SUCCESS != insertChnGrpTable(&chnGrpTblApiBuff))
      {
         printf("\n cfgCmDbHndlr130: ChnGrpTable Insertion Failed");
      }

      cfgStubSendCmMessage(&chnGrpTblApiBuff,
            sizeof(ChnGrpTableApi ),
            BSC_API_DEL_CHNGRPTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr130: ChnGrp table Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr130: ChnGrp Table Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr130: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* End of cfgCmDbHndlr130*/

/* Start of cfgCmDbHndlr131 */
void cfgCmDbHndlr131()
{
   static int testInitiation =1;
   CellTableApi* CellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   ChnGrpTableApi chnGrpTblApiBuff= {0};
   ChnGrpTableIndices chnGrpTblIndex= {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr131 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr131: ChnGrp Table Deletion: Cell UnLocked");

      cellIndex.cellId = 1;
      cellIndex.lac = 1;

      errCode = deleteCellTable(&cellIndex);

      CellTableApiPtr = ( CellTableApi *)calloc(1,sizeof(CellTableApi));
      CellTableApiPtr->cellId = 1;
      CellTableApiPtr->adminState = UNLOCK; /* Unlocked */
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
         printf("TestCase 131: Insert CellTable Successfull");
      }
      else
      {
         printf("TestCase 131: Insert CellTable Unsuccessfull");
      }

      chnGrpTblIndex.cellId =  1;
      chnGrpTblIndex.lac = 1;
      chnGrpTblIndex.chnGrpId = 1;

      errCode = deleteChnGrpTable(&chnGrpTblIndex);

      chnGrpTblApiBuff.cellId = 1;
      chnGrpTblApiBuff.lac = 1;
      chnGrpTblApiBuff.chnGrpId = 1;
      chnGrpTblApiBuff.tch = 30;
      chnGrpTblApiBuff.pdch = 30;
      chnGrpTblApiBuff.bcchCcchSdcch4 = 1;
      chnGrpTblApiBuff.bcchCcch = 1;
      chnGrpTblApiBuff.sdcch8 = 2;
      chnGrpTblApiBuff.hsn = 30;
      chnGrpTblApiBuff.maxTxPwr = 20000;
      chnGrpTblApiBuff.tsc = 5;
      chnGrpTblApiBuff.band = GSM_900;
      chnGrpTblApiBuff.validArfcns = 5;
      chnGrpTblApiBuff.arfcn1 = 124;
      chnGrpTblApiBuff.arfcn2 = 124;
      chnGrpTblApiBuff.arfcn3 = 124;
      chnGrpTblApiBuff.arfcn4 = 124;
      chnGrpTblApiBuff.arfcn5 = 124;

      if (CLIB_SUCCESS != insertChnGrpTable(&chnGrpTblApiBuff))
      {
         printf("\n cfgCmDbHndlr131: ChnGrpTable Insertion Failed");
      }

      cfgStubSendCmMessage(&chnGrpTblApiBuff,
            sizeof(ChnGrpTableApi ),
            BSC_API_DEL_CHNGRPTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr131:Test Case Failed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr131:Test case Success");
               }

               gTestCaseCompleted = 1;
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr131: Msg Discarded ");
            }
      } /* end of Switch */

   }
} /* End of cfgCmDbHndlr131*/



/* Start of cfgCmDbHndlr132*/
void cfgCmDbHndlr132()
{
   static int testInitiation =1;
   CsNeighCellsTableApi csNeighCellsTblApiBuff= {0};
   CsNeighCellsTableIndices csNeighCellsIndex = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr132 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      /* First set the BSS - precondition */
      errCode = setDbForBss(); /* for  setting admin state to lock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr132: setDbForBss Failed");
      }

      csNeighCellsIndex.cellId = 2;
      csNeighCellsIndex.lac = 1;
      //csNeighCellsIndex.cellType = INTERNAL;
      csNeighCellsIndex.neighborCellId = 2;

      errCode = deleteCsNeighCellsTable(&csNeighCellsIndex);

      csNeighCellsTblApiBuff.cellId = 2;
      csNeighCellsTblApiBuff.lac = 1;
      csNeighCellsTblApiBuff.cellType = INTERNAL;
      csNeighCellsTblApiBuff.neighborCellId = 2;
      csNeighCellsTblApiBuff.neighborLac = 1;
      csNeighCellsTblApiBuff.neighborMcc = 91;
      csNeighCellsTblApiBuff.neighborMnc = 91;
      csNeighCellsTblApiBuff.relationType = ACTIVE;

      if (CLIB_SUCCESS != insertCsNeighCellsTable(&csNeighCellsTblApiBuff))
      {
         printf("\n cfgCmDbHndlr132: Insert failed");
      }

      cfgStubSendCmMessage(&csNeighCellsTblApiBuff,sizeof(CsNeighCellsTableApi),BSC_API_DEL_CSNEIGHCELLSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr132:Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr132:Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr132: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
}
/* End of cfgCmDbHndlr132*/

/* Start of cfgCmDbHndlr133*/
void cfgCmDbHndlr133()
{
   static int testInitiation =1;
   CsNeighCellsTableApi csNeighCellsTblApiBuff= {0};
   CsNeighCellsTableIndices csNeighCellsIndex = {0};
   I_S32 errCode=0;

   printf("\n cfgCmDbHndlr133 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      /* First set the BSS - precondition */
      errCode = setDbForBss2(); /* for  setting admin state to unlock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr133: setDbForBss Failed");
         return ;
      }
      csNeighCellsIndex.cellId = 2;
      csNeighCellsIndex.lac = 1;
      //csNeighCellsIndex.cellType = INTERNAL;
      csNeighCellsIndex.neighborCellId = 2;

      errCode = deleteCsNeighCellsTable(&csNeighCellsIndex);

      csNeighCellsTblApiBuff.cellId = 2;
      csNeighCellsTblApiBuff.lac = 1;
      csNeighCellsTblApiBuff.cellType = INTERNAL;
      csNeighCellsTblApiBuff.neighborCellId = 2;
      csNeighCellsTblApiBuff.neighborLac = 1;
      csNeighCellsTblApiBuff.neighborMcc = 91;
      csNeighCellsTblApiBuff.neighborMnc = 91;
      csNeighCellsTblApiBuff.relationType = ACTIVE;

      if (CLIB_SUCCESS != insertCsNeighCellsTable(&csNeighCellsTblApiBuff))
      {
         printf("\n cfgCmDbHndlr133: Insert failed");
      }

      cfgStubSendCmMessage(&csNeighCellsTblApiBuff,sizeof(CsNeighCellsTableApi),BSC_API_DEL_CSNEIGHCELLSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status!= CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr133: Testcase Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr133:Testcase Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr133: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
}
/* End of cfgCmDbHndlr133*/

/* Start of cfgCmDbHndlr134*/
void cfgCmDbHndlr134()
{
   static int testInitiation =1;
   PsNeighCellsTableApi psNeighCellsTblApiBuff= {0};
   PsNeighCellsTableIndices psNeighCellsIndex = {0};
   I_S32 errCode=0;

   printf("\n cfgCmDbHndlr134 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      /* First set the BSS - precondition */
      errCode = setDbForBss(); /* for  setting admin state to lock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr134: setDbForBss Failed");
         return ;
      }

      psNeighCellsIndex.psCellId = 2;
      psNeighCellsIndex.lac = 1;
      psNeighCellsIndex.cellType = INTERNAL;
      psNeighCellsIndex.psNeighborCellId = 2;
      psNeighCellsIndex.psNeighborLac = 1;

      errCode = deletePsNeighCellsTable(&psNeighCellsIndex);

      psNeighCellsTblApiBuff.psCellId = 2;
      psNeighCellsTblApiBuff.lac = 1;
      psNeighCellsTblApiBuff.cellType = INTERNAL;
      psNeighCellsTblApiBuff.psNeighborCellId = 2;
      psNeighCellsTblApiBuff.psNeighborLac = 1;
      psNeighCellsTblApiBuff.psNeighborCellRac = 1;
      psNeighCellsTblApiBuff.psNeighborMcc = 99;
      psNeighCellsTblApiBuff.psNeighborMnc = 99;
      psNeighCellsTblApiBuff.relationType = ACTIVE;

      if (CLIB_SUCCESS != insertPsNeighCellsTable(&psNeighCellsTblApiBuff))
      {
         printf("\n cfgCmDbHndlr134: PsNeighCells set Request-Param Mod Msg, Insertion Failed");
      }

      cfgStubSendCmMessage(&psNeighCellsTblApiBuff,sizeof(PsNeighCellsTableApi),BSC_API_DEL_PSNEIGHCELLSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr134:Deletion Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr134:Deletion Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr134: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
}
/* End of cfgCmDbHndlr134*/

/* Start of cfgCmDbHndlr135*/
void cfgCmDbHndlr135()
{
   static int testInitiation =1;
   PsNeighCellsTableApi psNeighCellsTblApiBuff= {0};
   PsNeighCellsTableIndices psNeighCellsIndex = {0};
   I_S32 errCode=0;

   printf("\n cfgCmDbHndlr135 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      /* First set the BSS - precondition */
      errCode = setDbForBss2(); /* for  setting admin state to unlock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr135: setDbForBss Failed");
      }

      psNeighCellsIndex.psCellId = 2;
      psNeighCellsIndex.lac = 1;
      psNeighCellsIndex.cellType = INTERNAL;
      psNeighCellsIndex.psNeighborCellId = 2;
      psNeighCellsIndex.psNeighborLac = 1;

      errCode = deletePsNeighCellsTable(&psNeighCellsIndex);

      psNeighCellsTblApiBuff.psCellId = 2;
      psNeighCellsTblApiBuff.lac = 1;
      psNeighCellsTblApiBuff.cellType = INTERNAL;
      psNeighCellsTblApiBuff.psNeighborCellId = 2;
      psNeighCellsTblApiBuff.psNeighborLac = 1;
      psNeighCellsTblApiBuff.psNeighborCellRac = 1;
      psNeighCellsTblApiBuff.psNeighborMcc = 99;
      psNeighCellsTblApiBuff.psNeighborMnc = 99;
      psNeighCellsTblApiBuff.relationType = ACTIVE;

      if (CLIB_SUCCESS != insertPsNeighCellsTable(&psNeighCellsTblApiBuff))
      {
         printf("\n cfgCmDbHndlr135: PsNeighCells set Request-Param Mod Msg, Insertion Failed");
      }

      cfgStubSendCmMessage(&psNeighCellsTblApiBuff,sizeof(PsNeighCellsTableApi),BSC_API_DEL_PSNEIGHCELLSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status!= CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr135:Testcase Success");
               }
               else
               {
                  printf("\n cfgCmDbHndlr135:Testcase Failed");
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr135: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
}
/* End of cfgCmDbHndlr135*/

/* Start of cfgCmDbHndlr136*/
void cfgCmDbHndlr136()
{
   static int testInitiation =1;
   ArfcnListTableApi arfcnListTblApiBuff= {0};
   ArfcnListTableIndices arfcnTblIndex = {0};
   I_S32 errCode=0;

   printf("\n cfgCmDbHndlr136 Started: ");
   if ( testInitiation )
   {
      testInitiation =0;
      /* First set the BSS - precondition */
      errCode = setDbForBss(); /* for  setting admin state to lock */

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr136: setDbForBss Failed");
      }
      arfcnTblIndex.band = GSM_1900;
      arfcnTblIndex.arfcn = 512;

      errCode = deleteArfcnListTable(&arfcnTblIndex);

      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 512;

      if (CLIB_SUCCESS != insertArfcnListTable(&arfcnListTblApiBuff))
      {
         printf("\n cfgCmDbHndlr136: ArfcnList delete request, Insertion Failed");
      }

      cfgStubSendCmMessage(&arfcnListTblApiBuff,sizeof(ArfcnListTableApi),BSC_API_DEL_ARFCNLISTTABLE );
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status!= CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr136:Failed");
               }
               else
               {
                  printf("\n cfgCmDbHndlr136:Success");
                  gTestCaseCompleted = 1;
               }
               break;
            }   /* end of case CM_API_APP_RESPONSE */
         default:
            {
               printf("\n In cfgCmDbHndlr136: Msg Discarded ");
            }
      } /* end of Switch */


   }
} /* End of cfgCmDbHndlr136*/

/* Start of cfgCmDbHndlr176*/ 
void cfgCmDbHndlr176() 
{ 
   //frlink   DB Unlocked 
   static int testInitiation =1;    
   FrLinkTableApi frLinkTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0;
      printf("\n cfgCmDbHndlr176 started :FrLinkTableApi ");       
      if (bssSetState(1) ==1)      //Set DB to Required State (Pre-Condition)              
      { 
         frLinkTableApiBuff.frIndex= 17; /*key */
         frLinkTableApiBuff.priority= 1;
         frLinkTableApiBuff.e1= 1;
         frLinkTableApiBuff.ts= 1;
         frLinkTableApiBuff.oprState= 1;

         insertFrLinkTable(&frLinkTableApiBuff);

         printf("\nSending BSC_API_DEL_FRLINKTABLE" ); 
         cfgStubSendCmMessage(&frLinkTableApiBuff,sizeof(FrLinkTableApi),BSC_API_DEL_FRLINKTABLE ); 
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr176: Failure");

               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr176: Success");
                  gTestCaseCompleted = 1; 
                  printf("In cfgCmDbHndlr176:Completed Successfully\n"); 
               }          

            }   break; /* end of case CM_APP_API_RESPONSE */       
         default: 
            { 
               printf("\n In cfgCmDbHndlr176: Msg Discarded ");
               printf("In cfgCmDbHndlr176:Failed\n"); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr176*/ 

/* Start of cfgCmDbHndlr175*/ 
void cfgCmDbHndlr175() 
{//frlink DB locked 

   static int testInitiation =1;    
   FrLinkTableApi frLinkTableApiBuff = {0}; 
   if ( testInitiation ) 
   { 
      testInitiation =0;
      printf("\n cfgCmDbHndlr175 started :FrLinkTableApi ");          
      if (bssSetState(0) ==1)      //Set DB to Required State (Pre-Condition)              
      { 
         frLinkTableApiBuff.frIndex= 17; /*key */
         frLinkTableApiBuff.priority= 1;
         frLinkTableApiBuff.e1= 1;
         frLinkTableApiBuff.ts= 1;
         frLinkTableApiBuff.oprState= 1;

         insertFrLinkTable(&frLinkTableApiBuff);

         printf("\nSending BSC_API_DEL_FRLINKTABLE" ); 
         cfgStubSendCmMessage(&frLinkTableApiBuff,sizeof(FrLinkTableApi),BSC_API_DEL_FRLINKTABLE ); 
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE: 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr175: Deletion Successful");
                  gTestCaseCompleted = 1; 
                  printf("In cfgCmDbHndlr175 :Completed Successfully\n"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr175 Deletion Failed"); 
               }          

            }break;    /* end of case CM_APP_API_RESPONSE */    
         default: 
            { 
               printf("\n In cfgCmDbHndlr175 Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr175*/ 

/* Start of cfgCmDbHndlr174*/ 
void cfgCmDbHndlr174() 
{ 
   //nsvc DB Unlocked 
   static int testInitiation =1;    
   NsvcTableApi nsvcTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0;
      printf("\n cfgCmDbHndlr174 started : NSVC Table");       
      if (bssSetState(1) ==1)      //Set DB to Required State (Pre-Condition)              
      { 
         nsvcTableApiBuff.nsvcId = 1; /*key */
         nsvcTableApiBuff.frIndex= 1; /*key */
         nsvcTableApiBuff.oprState= 1;

         insertNsvcTable(&nsvcTableApiBuff);

         printf("\nSending BSC_API_DEL_NSVCTABLE"); 
         cfgStubSendCmMessage(&nsvcTableApiBuff,sizeof(NsvcTableApi),BSC_API_DEL_NSVCTABLE ); 
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE: 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr174: Failure"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr174: Success");
                  gTestCaseCompleted = 1; 
                  printf("In cfgCmDbHndlr174:Completed Successfully\n"); 
               }          

            }break;    /* end of case CM_APP_API_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr174: Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr174*/ 

/* Start of cfgCmDbHndlr173*/ 
void cfgCmDbHndlr173() 
{ 
   //nsvc DB Locked 

   static int testInitiation =1;    
   NsvcTableApi nsvcTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0;
      printf("\n cfgCmDbHndlr173 started : ");       
      if (bssSetState(0) == 1)      //Set DB to Required State (Pre-Condition)              
      { 
         nsvcTableApiBuff.nsvcId = 1; /*key */
         nsvcTableApiBuff.frIndex= 1; /*key */
         nsvcTableApiBuff.oprState= 1;

         insertNsvcTable(&nsvcTableApiBuff);

         printf("\nSending BSC_API_DEL_NSVCTABLE"); 
         cfgStubSendCmMessage(&nsvcTableApiBuff,sizeof(NsvcTableApi),BSC_API_DEL_NSVCTABLE ); 
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr173: Deletion Successful");
                  gTestCaseCompleted = 1; 
                  printf("In cfgCmDbHndlr173:Completed Successfully\n"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr173: Deletion Failed"); 
               }          

            }break;    /* end of case CM_APP_API_RESPONSE  */       
         default: 
            { 
               printf("\n In cfgCmDbHndlr173: Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr173*/ 

/* Start of cfgCmDbHndlr172*/ 
void cfgCmDbHndlr172() 
{ 
   //gb interface DB Unlocked 
   static int testInitiation =1;    
   GbInterfaceTableApi gbInterfaceTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0;
      printf("\n cfgCmDbHndlr172 started :GB Interface ");       
      if (bssSetState(1) == 1)      //Set DB to Required State (Pre-Condition)              
      { 
         gbInterfaceTableApiBuff.dummyIndex = 1; /*key */
         gbInterfaceTableApiBuff.oprState= 1;
         gbInterfaceTableApiBuff.nsei= 1;
         gbInterfaceTableApiBuff.maxNumNsvcs= 1;
         gbInterfaceTableApiBuff.maxNumLeps= 1;
         gbInterfaceTableApiBuff.maxNumReps= 1;
         gbInterfaceTableApiBuff.transportType= 1;

         insertGbInterfaceTable(&gbInterfaceTableApiBuff);

         printf("\nSending BSC_API_DEL_GBINTERFACETABLE"); 
         cfgStubSendCmMessage(&gbInterfaceTableApiBuff,sizeof(GbInterfaceTableApi),BSC_API_DEL_GBINTERFACETABLE ); 
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr172: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr172: SUCCESS");
                  gTestCaseCompleted = 1; 
                  printf("In cfgCmDbHndlr172:Completed Successfully\n"); 
               }          

            }break;    /* end of case CM_APP_API_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr172: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/* End of cfgCmDbHndlr172*/ 

/* Start of cfgCmDbHndlr171*/ 
void cfgCmDbHndlr171() 
{ 
   //gb interface DB locked 
   static int testInitiation =1;    
   GbInterfaceTableApi gbInterfaceTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0;
      printf("\n cfgCmDbHndlr171 started :gb interface ");       
      if (bssSetState(0) == 1)      //Set DB to Required State (Pre-Condition)              
      { 
         gbInterfaceTableApiBuff.dummyIndex = 1; /*key */
         gbInterfaceTableApiBuff.oprState= 1;
         gbInterfaceTableApiBuff.nsei= 1;
         gbInterfaceTableApiBuff.maxNumNsvcs= 1;
         gbInterfaceTableApiBuff.maxNumLeps= 1;
         gbInterfaceTableApiBuff.maxNumReps= 1;
         gbInterfaceTableApiBuff.transportType= 1;

         insertGbInterfaceTable(&gbInterfaceTableApiBuff);


         cfgStubSendCmMessage(&gbInterfaceTableApiBuff,sizeof(GbInterfaceTableApi),BSC_API_DEL_GBINTERFACETABLE ); 
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE: 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr171: Success");
                  gTestCaseCompleted = 1; 
                  printf("In cfgCmDbHndlr171:Completed Successfully\n"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr171: Failed"); 
               }          

            }break;    /* end of case CM_APP_API_RESPONSE*/         
         default: 
            { 
               printf("\n In cfgCmDbHndlr171: Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr171*/ 

/* Start of cfgCmDbHndlr164*/ 
void cfgCmDbHndlr164() 
{ 
   static int testInitiation =1; 

   RlcMacConfigTableApi RlcMacConfigTableApiBuff = {0}; 
   printf("\n cfgCmDbHndlr164 Started: "); 

   if ( testInitiation ) 
   { 
      testInitiation =0; 

      RlcMacConfigTableApiBuff.dummyIndex = (I_U32)10;//value TB clarified
      insertRlcMacConfigTable(&RlcMacConfigTableApiBuff);

      printf("\nSending BSC_API_DEL_RLCMACCONFIGTABLE"); 
      cfgStubSendCmMessage(&RlcMacConfigTableApiBuff,sizeof(RlcMacConfigTableApi),BSC_API_DEL_RLCMACCONFIGTABLE ); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr164: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr164: Success");
                  printf("\nCompleted Successfully"); 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr164: Msg Discarded "); 
            } 
      } /* end of Switch */ 

      gTestCaseCompleted = 1; 
   } 
}/* End of cfgCmDbHndlr164*/ 

/* Start of cfgCmDbHndlr163*/ 
void cfgCmDbHndlr163() 
{ 
   static int testInitiation =1; 
   PcuTableApi pcuTblApiBuff = {0};
   PcuTableIndices pcuTableIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation ) 
   { 
      testInitiation =0; 
      printf("\n cfgCmDbHndlr163 Started: "); 

      pcuTableIndex.dummyIndex = 1;

      errCode = deletePcuTable(&pcuTableIndex);

      pcuTblApiBuff.dummyIndex= 1;
      //pcuTblApiBuff.rrbpFlag= 1;
      pcuTblApiBuff.tcVal = 1;
      //pcuTblApiBuff.tFlowCtrlAck= 1;
      //pcuTblApiBuff.pcuTimerRetries= 1;
      pcuTblApiBuff.numContiguousPdch= 1;
      pcuTblApiBuff.defaultChanCoding= 1;
      pcuTblApiBuff.tlliBlkCoding= 1;
      pcuTblApiBuff.maxUlAllocLength= 1;
      pcuTblApiBuff.onePhSize = 1;
      pcuTblApiBuff.globPwrCtrlFlag= 1;

      if(CLIB_SUCCESS != insertPcuTable(&pcuTblApiBuff))
      {
         printf("\n cfgCmDbHndlr163: PcuTable delete request, Insertion Failed");
      }

      printf("\nSending BSC_API_DEL_PCUTABLE"); 
      cfgStubSendCmMessage(&pcuTblApiBuff,sizeof(PcuTableApi),BSC_API_DEL_PCUTABLE ); 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr163: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr163: Success"); 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr163: Msg Discarded "); 
            } 
      } /* end of Switch */ 

      gTestCaseCompleted = 1; 

   } 
}/* End of cfgCmDbHndlr163*/ 

/* Start of cfgCmDbHndlr158*/ 
void cfgCmDbHndlr158() 
{ 
   static int testInitiation =1;  

   TimeSlotTableApi TimeSlotTableApiBuff = {0}; 
   printf("\n cfgCmDbHndlr158 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0;       
      TimeSlotTableApiBuff.e1Num = 10;
      insertTimeSlotTable(&TimeSlotTableApiBuff);

      printf("\nSending BSC_API_DEL_TIMESLOTPERTABLE"); 
      cfgStubSendCmMessage(&TimeSlotTableApiBuff,sizeof(TimeSlotTableApi),BSC_API_DEL_TIMESLOTPERTABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr158: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr158:Success");
                  gTestCaseCompleted = 1; 
                  printf("Completed Successfully"); 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr158: Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr158*/ 

/* Start of cfgCmDbHndlr157*/ 
void cfgCmDbHndlr157() 
{ 
   static int testInitiation =1;  

   E1TableApi E1TableApiBuff = {0}; 
   printf("\n cfgCmDbHndlr157 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0;       
      E1TableApiBuff.e1Num = 1;
      insertE1Table(&E1TableApiBuff);

      printf("\nSending BSC_API_DEL_E1PERTABLE"); 
      cfgStubSendCmMessage(&E1TableApiBuff,sizeof(E1TableApi),BSC_API_DEL_E1PERTABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr157: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr157:Success");
                  gTestCaseCompleted = 1; 
                  printf("Completed Successfully"); 
               }          

            }   break; /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr157: Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr157*/ 

/* Start of cfgCmDbHndlr156*/ 
void cfgCmDbHndlr156() 
{ 
   static int testInitiation =1;  

   PtrxTableApi PtrxTableApiBuff = {0}; 
   printf("\n cfgCmDbHndlr156 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0;       
      PtrxTableApiBuff.ptrxId = 1;
      insertPtrxTable(&PtrxTableApiBuff);

      printf("\nSending BSC_API_DEL_PTRXSLOTPRECONFIGTABLE"); 
      //cfgStubSendCmMessage(&PtrxTableApiBuff,sizeof(PtrxTableApi),BSC_API_DEL_PHYSICALTRXPRECONFIGUREDTABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr156: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr156:Success");
                  gTestCaseCompleted = 1; 
                  printf("\nCompleted Successfully"); 
               }          

            }   break; /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr156: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/* End of cfgCmDbHndlr156*/ 

/* Start of cfgCmDbHndlr155*/ 
void cfgCmDbHndlr155() 
{ 
   static int testInitiation =1;     
   RepInfoTableApi repInfoTblApiBuff = {0};
   RepInfoTableIndices repInfoTableIndices = {0};
   I_S32 errCode = 0;

   printf("\n cfgCmDbHndlr155 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0; 
      if (bssSetState(1) ==1)      //Set DB to Required State (Pre-Condition)   
      {          
         repInfoTableIndices.rep=1;

         errCode = deleteRepInfoTable(&repInfoTableIndices);

         repInfoTblApiBuff.rep = 1; /*key */
         repInfoTblApiBuff.repPort = 1;
         repInfoTblApiBuff.signallingWt= 1;
         repInfoTblApiBuff.dataWt= 1;

         if(CLIB_SUCCESS != insertRepInfoTable(&repInfoTblApiBuff))
         {
            printf("\n cfgCmDbHndlr155: RepINfo del Request-, Insertion Failed");
         }

         printf("\nSending BSC_API_DEL_REPINFOTABLE"); 
         cfgStubSendCmMessage(&repInfoTblApiBuff,sizeof(RepInfoTableApi),BSC_API_DEL_REPINFOTABLE); 
      } 
      else 
      { 
         printf("DB Operation Failed"); 
      } 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr155: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr155:Success");
                  printf("Completed Successfully"); 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr155: Msg Discarded "); 
            } 
      } /* end of Switch */ 

      gTestCaseCompleted = 1; 

   } 
}/* End of cfgCmDbHndlr155*/ 

/* Start of cfgCmDbHndlr154*/ 
void cfgCmDbHndlr154() 
{ 
   static int testInitiation =1;     
   RepInfoTableApi repInfoTblApiBuff = {0}; 
   RepInfoTableIndices repInfoTableIndices = {0};
   I_S32  errCode = 0;

   printf("\n cfgCmDbHndlr154 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0; 
      if (bssSetState(0) ==1)      //Set DB to Required State (Pre-Condition)   
      {         

         repInfoTableIndices.rep=1;

         errCode = deleteRepInfoTable(&repInfoTableIndices);

         repInfoTblApiBuff.rep = 1; /*key */
         repInfoTblApiBuff.ipType = 1; /*key */
         repInfoTblApiBuff.repPort = 1;
         repInfoTblApiBuff.signallingWt= 1;
         repInfoTblApiBuff.dataWt= 1;

         if(CLIB_SUCCESS != insertRepInfoTable(&repInfoTblApiBuff))
         {
            printf("\n cfgCmDbHndlr154: RepINfo del Request, Insertion Failed");
         }

         printf("\n Sending BSC_API_DEL_REPINFOTABLE"); 
         cfgStubSendCmMessage(&repInfoTblApiBuff,sizeof(RepInfoTableApi),BSC_API_DEL_REPINFOTABLE); 
      } 
      else 
      { 
         printf("DB Operation Failed"); 
      } 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr154: Deletion Success");
                  gTestCaseCompleted = 1; 
                  printf("Completed Successfully"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr154:Deletion Failed"); 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr154: Msg Discarded "); 
            } 
      } /* end of Switch */ 
   } 
}/* End of cfgCmDbHndlr154*/ 

/* Start of cfgCmDbHndlr153*/ 
void cfgCmDbHndlr153() 
{ 
   static int testInitiation =1;     
   LepInfoTableApi lepInfoTblApiBuff = {0}; 
   printf("\n cfgCmDbHndlr153  Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0; 
      if (bssSetState(1) ==1)      //Set DB to Required State (Pre-Condition)   
      {        
         lepInfoTblApiBuff.lep = 19; /*key */
         lepInfoTblApiBuff.ipType = 1;
         lepInfoTblApiBuff.lepPort = 20;
         lepInfoTblApiBuff.signallingWt= 1;
         lepInfoTblApiBuff.dataWt= 1;

         if(CLIB_SUCCESS != insertLepInfoTable(&lepInfoTblApiBuff))
         {
            printf("\n cfgCmDbHndlr153: PcuTable del Request, Insertion Failed");
         }

         printf("\nSending BSC_API_DEL_LEPINFOTABLE "); 
         cfgStubSendCmMessage(&lepInfoTblApiBuff,sizeof(LepInfoTableApi),BSC_API_DEL_LEPINFOTABLE ); 
      } 
      else 
      { 
         printf("DB Operation Failed"); 
         return ; 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr153: Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr153:Success");
                  printf("Completd Successfully"); 
                  gTestCaseCompleted = 1; 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr153: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/* End of cfgCmDbHndlr153*/ 

/* Start of cfgCmDbHndlr152*/ 
void cfgCmDbHndlr152() 
{ 
   static int testInitiation =1;     
   LepInfoTableApi LepInfoTableApiBuff = {0}; 
   LepInfoTableApi lepInfoTblApiBuff = {0};
   printf("\n cfgCmDbHndlr152 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0; 
      if (bssSetState(0) ==1)      //Set DB to Required State (Pre-Condition)   
      {           
         lepInfoTblApiBuff.lep = 19; /*key */
         lepInfoTblApiBuff.ipType = 1;
         lepInfoTblApiBuff.lepPort = 20;
         lepInfoTblApiBuff.signallingWt= 1;
         lepInfoTblApiBuff.dataWt= 1;

         if(CLIB_SUCCESS != insertLepInfoTable(&lepInfoTblApiBuff))
         {
            printf("\n cfgCmDbHndlr152: Lep Table del Request, Insertion Failed");
         }

         printf("\nSending BSC_API_DEL_LEPINFOTABLE "); 
         cfgStubSendCmMessage(&lepInfoTblApiBuff,sizeof(LepInfoTableApi),BSC_API_DEL_LEPINFOTABLE ); 
      } 
      else 
      { 
         printf("DB Operation Failed"); 
      } 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr152: Deletion Success");
                  printf("Complted Successfully"); 
                  gTestCaseCompleted = 1; 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr152:Deletion Failed"); 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr152: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/* End of cfgCmDbHndlr152*/ 

/* Start of cfgCmDbHndlr139*/
void cfgCmDbHndlr139() 
{ 
   static int testInitiation =1;  

   AInterfaceTableApi AInterfaceTableApiBuff = {0}; 

   if ( testInitiation ) 
   { 
      testInitiation =0;    
      printf("\n cfgCmDbHndlr139 Started: "); 
      AInterfaceTableApiBuff.dummyIndex = 1;

      insertAInterfaceTable(&AInterfaceTableApiBuff);

      printf("\nSending BSC_API_DEL_AINTERFACETABLE");          
      cfgStubSendCmMessage(&AInterfaceTableApiBuff,sizeof(AInterfaceTableApi),BSC_API_DEL_AINTERFACETABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr139:Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr139:Success"); 
                  gTestCaseCompleted = 1; 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr139: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/*End of cfgCmDbHndlr139*/ 


/* Start of cfgCmDbHndlr138*/
void cfgCmDbHndlr138() 
{ 
   static int testInitiation =1;  

   TrauConfigTableApi trauConfigTblApiBuff = {0}; 
   printf("\n cfgCmDbHndlr138 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0;           

      /* Send TrauTable Update Request - with band not in DB */
      trauConfigTblApiBuff.trauDspId = 1;
      trauConfigTblApiBuff.trauNumSpeechChannels = 1;

      insertTrauConfigTable(&trauConfigTblApiBuff);

      printf("\nSending BSC_API_DEL_TRAUCONFIGTABLE");          
      cfgStubSendCmMessage(&trauConfigTblApiBuff,sizeof(TrauConfigTableApi),BSC_API_DEL_TRAUCONFIGTABLE); 

   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr138:Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr138:Success"); 
                  gTestCaseCompleted = 1; 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr138: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/* End of cfgCmDbHndlr138 */ 

/* Start of cfgCmDbHndlr137*/
void cfgCmDbHndlr137() 
{ 
   static int testInitiation =1; 

   ArfcnListTableApi *arfcnListTableApiPtr;
   printf("\n cfgCmDbHndlr137 Started: "); 
   if ( testInitiation ) 
   { 
      testInitiation =0; 
      if (bssSetState(1) ==1)      //Set DB to Required State (Pre-Condition)   
      {       

         arfcnListTableApiPtr = ( ArfcnListTableApi *)calloc(1,sizeof(ArfcnListTableApi));

         arfcnListTableApiPtr->band = GSM_1800; 
         arfcnListTableApiPtr->arfcn = 124;
         if ( insertArfcnListTable(arfcnListTableApiPtr) == CLIB_SUCCESS )
         {
            printf("Insert Arfcn Table Success Full \n");
         }
         printf("\nSending BSC_API_DEL_ARFCNLISTTABLE "); 
         cfgStubSendCmMessage(arfcnListTableApiPtr,sizeof(ArfcnListTableApi),BSC_API_DEL_ARFCNLISTTABLE ); 
         free(arfcnListTableApiPtr);
      } 
      else 
      { 
         printf("\nDB Operation Failed"); 
      } 
   } 
   else 
   { 
      switch (((SysHdr*) gCfgMsgBuf)->msgType) 
      { 
         case CM_API_APP_RESPONSE : 
            { 
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS) 
               { 
                  printf("\n cfgCmDbHndlr137:Failed"); 
               } 
               else 
               { 
                  printf("\n cfgCmDbHndlr137:Sucess");
                  printf("\nCompleted Successfully"); 
                  gTestCaseCompleted = 1; 
               }          

            }break;    /* end of case CM_API_APP_RESPONSE */        
         default: 
            { 
               printf("\n In cfgCmDbHndlr135: Msg Discarded "); 
            } 
      } /* end of Switch */ 


   } 
}/*End of cfgCmDbHndlr137*/ 

void cfgCmDbHndlr190()
{
   static int testInitiation =1;

   SysOmcRegisterTableApi SysOmcRegisterTableApiBuff= {0};
   SysOmcRegisterTableIndices apiOmcRegIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;

      SysOmcRegisterTableApiBuff.sysOmcRegisterprofileId[0] = 2; 

      cfgStubSendCmMessage(&SysOmcRegisterTableApiBuff,sizeof(SysOmcRegisterTableApi),BSC_API_DEL_SYSOMCREGISTERTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr190: FAILED \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr190: PASSED \n");
               }          
               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr190: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr190 */

void cfgCmDbHndlr191()
{
   static int testInitiation =1;

   SysOmcConfigTableApi SysOmcConfigTableApiBuff= {0};
   SysOmcConfigTableIndices apiOmcCfgIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      SysOmcConfigTableApiBuff.sysOmcConfigactiveCardHwId[0] = 20; 
      SysOmcConfigTableApiBuff.sysOmcConfignumOfE1c[0] = 1; 

      cfgStubSendCmMessage(&SysOmcConfigTableApiBuff,sizeof(SysOmcConfigTableApi),BSC_API_DEL_SYSOMCCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr191: FAILED \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr191: PASSED \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr191: Msg Discarded ");
            }
      } /* end of Switch */

      printf("In cfgCmDbHndlr191: Success\n");
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr191 */


void cfgCmDbHndlr192()
{
   static int testInitiation =1;

   PtdcConfigTableApi PtdcConfigTableApiBuff= {0};
   PtdcConfigTableIndices PtdcConfigTableIndicesBuff = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;

      PtdcConfigTableApiBuff.ptdcCfgCfgIndex =  1;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 600; 

      cfgStubSendCmMessage(&PtdcConfigTableApiBuff,sizeof(PtdcConfigTableApi),BSC_API_DEL_PTDCCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr192: problem in handling, chk code");
               }
               else
               {
                  printf("\n cfgCmDbHndlr192: PASSED \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr192: Msg Discarded ");
            }
      } /* end of Switch */

      printf("In cfgCmDbHndlr192: Success\n");
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr192 */
