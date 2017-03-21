#include<oamcfg_includes.h>
extern int gTestCaseCompleted;
/* Function to Set/Initailize Bss Parameters */
I_Bool setDbForBss()
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
   bssTableApiBuff->adminState = LOCK; /* Locked */   
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
   bssTableApiBuff->lRxLevUlP = 5;
   bssTableApiBuff->lRxQualDlP = 5;
   bssTableApiBuff->lRxQualUlP = 5; */
   bssTableApiBuff->maxRetrans = 4;
   /* bssTableApiBuff->timerTraceLog = 40; */
   bssTableApiBuff->txInteger = 12;
   bssTableApiBuff->radioLinkTimeout = 6;
   bssTableApiBuff->shutdownTimer = 231;
   bssTableApiBuff->cicMaster = 1;      
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
   bssTableApiBuff->rxAveraginNo = 1;      
   bssTableApiBuff->qlNoofSamplesHigh = 20;
   bssTableApiBuff->qlNoofSamplesLow = 20; 
   bssTableApiBuff->qlTotalSamplesHigh = 20;
   bssTableApiBuff->qlTotalSamplesLow = 20; */

   if  (0 != count) 
   {

      if  (bssTableApiPtr->adminState != LOCK) 
      {
         bssTableApiPtr->adminState = LOCK;
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

}/* end of setDbForBss */


void cfgCmDbHndlr1()
{
   static int testInitiation =1;

   BssTableApi bssTableApiBuff= {0};
   BssTableApi*  bssTableApiPtr = NULL;
   BssTableIndices bssIndex = {0};
   I_S32 i = 0;
   I_U16 size = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr1: Bss Update Request- Initiation");

      ret = getallBssTable (&bssTableApiPtr, &i, &size);

      /* First set the required database */
      bssTableApiBuff.bscId =1;
      bssTableApiBuff.gprsEnabled =1;   
      bssTableApiBuff.adminState = LOCK; /* Locked */   
      bssTableApiBuff.attInd = ALLOWED;
      bssTableApiBuff.bssReset = FALSE;
      bssTableApiBuff.callReestablishmentInd =  ALLOWED;
      bssTableApiBuff.t3212 = 20;
      bssTableApiBuff.mcc = 24;
      bssTableApiBuff.mnc = 45;
      bssTableApiBuff.ncc = 5;
      bssTableApiBuff.nccPermitted = 200;
      bssTableApiBuff.dtxDnLinkInd = 1;
      bssTableApiBuff.dtxUpLinkInd = 1;
      bssTableApiBuff.minChannelGap = 3;
      /* bssTableApiBuff.cerPeriodicityTimer = 25;
         bssTableApiBuff.periodicCsAppTimer = 25;
         bssTableApiBuff.periodicCsStackTimer = 25;
         bssTableApiBuff.periodicPcuStackTimer = 25;
         bssTableApiBuff.periodicPlatformTimer = 25;
         bssTableApiBuff.periodicPsAppTimer = 25; 
      bssTableApiBuff.lRxLevDlP = 41;
      bssTableApiBuff.lRxLevUlP = 5;
      bssTableApiBuff.lRxQualDlP = 5;
      bssTableApiBuff.lRxQualUlP = 5; 
      bssTableApiBuff.maxRetrans = 4; 
      bssTableApiBuff.rxAveraginNo = 4; */
      /* bssTableApiBuff.timerTraceLog = 40; */
      bssTableApiBuff.txInteger = 12;
      bssTableApiBuff.radioLinkTimeout = 6;
      bssTableApiBuff.shutdownTimer = 231;
      bssTableApiBuff.cicMaster = 1;
      /* bssTableApiBuff.enBsPctrl = FALSE;
      bssTableApiBuff.enMsPctrl = FALSE;
      bssTableApiBuff.rxDecStepSize = 1;
      bssTableApiBuff.rxIncrStepSize = 1;
      bssTableApiBuff.pConInterval = 31;
      bssTableApiBuff.qlAveraginNo = 29;
      bssTableApiBuff.rxTotalSamplesHigh = 21;
      bssTableApiBuff.rxTotalSamplesLow = 11;
      bssTableApiBuff.rxNoofSamplesLow = 11;
      bssTableApiBuff.rxNoOfSamplesHigh = 21;
      bssTableApiBuff.uRxLevDlP = 31;
      bssTableApiBuff.uRxLevUlP = 5;
      bssTableApiBuff.uRxQualDlP = 1;
      bssTableApiBuff.uRxQualUlP = 7;
      bssTableApiBuff.qlNoofSamplesHigh = 20;
      bssTableApiBuff.qlNoofSamplesLow = 20; 
      bssTableApiBuff.qlTotalSamplesHigh = 20;
      bssTableApiBuff.qlTotalSamplesLow = 20; */

      /*( if BSS Table is empty, then Insert */
      if (NULL == bssTableApiPtr)
      {
         if (CLIB_SUCCESS != insertBssTable(&bssTableApiBuff))
         {
            printf("\n cfgCmDbHndlr1:  insertBssTable failed");
            return;
         }
      }
      else  /*( if BSS Table has entry, then Update */
      {
         bssIndex.bscId = bssTableApiPtr->bscId;
         free(bssTableApiPtr);
         if (CLIB_SUCCESS != deleteBssTable(&bssIndex))
         {
            printf("\n cfgCmDbHndlr1: deleteBssTable failed");
            return;
         }
         if (CLIB_SUCCESS != insertBssTable(&bssTableApiBuff))
         {
            printf("\n cfgCmDbHndlr1:  insertBssTable failed");
            return;
         }
      } /* end of Else */

      /* Send Parameter Modification for BSS */
      bssTableApiBuff.bscId =1;
      bssTableApiBuff.mcc = 99;
      bssTableApiBuff.mnc = 99;
      bssTableApiBuff.ncc = 5;
      bssTableApiBuff.nccPermitted = 200;
      /*bssTableApiBuff.enBsPctrl = TRUE;
      bssTableApiBuff.enMsPctrl = TRUE; */

      printf("\n cfgCmDbHndlr1: Bss Update Request- Sending Parameter Modified Msg to BSS");
      cfgStubSendCmMessage(&bssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr1: Successfully Updated");                             
                  printf("In cfgCmDbHndlr1: Success\n");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("\n cfgCmDbHndlr1: Updation Failed");

               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr1: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr1 */

void cfgCmDbHndlr2()
{
   static int testInitiation =1;
   BssTableApi bssTableApiBuff= {0};
   BssTableApi* bssTableApiPtr = NULL;
   BssTableIndices bssIndex = {0};
   I_S32 i = 0;
   I_U16 size = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation = 0;
      printf("\n cfgCmDbHndlr2:Bss set add row Request-BSS is empty");

      ret = getallBssTable (&bssTableApiPtr, &i, &size);

      /* First set the required database */
      bssTableApiBuff.bscId =1;
      bssTableApiBuff.gprsEnabled =1;   
      bssTableApiBuff.adminState = UNLOCK; /* Unlocked */
      bssTableApiBuff.attInd = ALLOWED;
      bssTableApiBuff.bssReset = FALSE;
      bssTableApiBuff.callReestablishmentInd = ALLOWED;
      bssTableApiBuff.t3212 = 20;
      bssTableApiBuff.mcc = 55;
      bssTableApiBuff.mnc = 55;
      bssTableApiBuff.ncc = 5;
      bssTableApiBuff.nccPermitted = 200;
      bssTableApiBuff.dtxDnLinkInd = 1;
      bssTableApiBuff.dtxUpLinkInd = 1;
      bssTableApiBuff.minChannelGap = 3;
      /* bssTableApiBuff.rxAveraginNo = 4;
       bssTableApiBuff.cerPeriodicityTimer = 25;
         bssTableApiBuff.periodicCsAppTimer = 25;
         bssTableApiBuff.periodicCsStackTimer = 25;
         bssTableApiBuff.periodicPcuStackTimer = 25;
         bssTableApiBuff.periodicPlatformTimer = 25;
         bssTableApiBuff.periodicPsAppTimer = 25; 
      bssTableApiBuff.lRxLevDlP = 41;
      bssTableApiBuff.lRxLevUlP = 2;
      bssTableApiBuff.lRxQualDlP = 5;
      bssTableApiBuff.lRxQualUlP = 5;
      bssTableApiBuff.maxRetrans = 4; */
      /* bssTableApiBuff.timerTraceLog = 40; */
      bssTableApiBuff.txInteger = 12;
      bssTableApiBuff.radioLinkTimeout = 6;
      bssTableApiBuff.shutdownTimer = 231;
      bssTableApiBuff.cicMaster = 1;   
      /* bssTableApiBuff.enBsPctrl = TRUE;
      bssTableApiBuff.enMsPctrl = TRUE;
      bssTableApiBuff.rxDecStepSize = 1;
      bssTableApiBuff.rxIncrStepSize = 1;
      bssTableApiBuff.pConInterval = 31;
      bssTableApiBuff.qlAveraginNo = 29;
      bssTableApiBuff.rxTotalSamplesHigh = 21;
      bssTableApiBuff.rxTotalSamplesLow = 11;
      bssTableApiBuff.rxNoofSamplesLow = 11;
      bssTableApiBuff.rxNoOfSamplesHigh = 21;
      bssTableApiBuff.uRxLevDlP = 31;
      bssTableApiBuff.uRxLevUlP = 5;
      bssTableApiBuff.uRxQualDlP = 1;
      bssTableApiBuff.uRxQualUlP = 7;
      bssTableApiBuff.qlNoofSamplesHigh = 20;
      bssTableApiBuff.qlNoofSamplesLow = 20; 
      bssTableApiBuff.qlTotalSamplesHigh = 20;
      bssTableApiBuff.qlTotalSamplesLow = 20; */

      /*( if BSS Table has entry, then first delete */
      if (NULL != bssTableApiPtr)
      {
         bssIndex.bscId = bssTableApiPtr->bscId;
         free(bssTableApiPtr);
         if (CLIB_SUCCESS != deleteBssTable(&bssIndex))
         {
            printf("\n cfgCmDbHndlr2: deleteBssTable failed");
            return;
         }
      } /* end of if (NULL != bssTableApiPtr) */

      printf("\n cfgCmDbHndlr2: Bss set Request- BSS is empty, Sending");
      cfgStubSendCmMessage(&bssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status== CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr2: Successfully Added Row in BSS");
                  gTestCaseCompleted = 1;
                  printf("In cfgCmDbHndlr1: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr2: Addition of Row Failed");
                  gTestCaseCompleted = 1;
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr2: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr2 */

void cfgCmDbHndlr3()
{
   static int testInitiation =1;

   BssTableApi bssTableApiBuff= {0};
   BssTableApi* bssTableApiPtr = NULL;
   BssTableIndices bssIndex = {0}; 
   I_S32 i = 0;
   I_U16 size  = 0;
   I_S32 ret = 1;

   if ( testInitiation )
   {
      testInitiation =0;      

      /* Check if BSS has an entry or not */ 
      ret = getallBssTable (&bssTableApiPtr, &i, &size);             

      bssTableApiBuff.bscId =1;
      bssTableApiBuff.gprsEnabled =1;   
      bssTableApiBuff.adminState =LOCK; /* Locked */   
      bssTableApiBuff.attInd = ALLOWED;
      bssTableApiBuff.bssReset = FALSE;
      bssTableApiBuff.callReestablishmentInd = ALLOWED;
      bssTableApiBuff.t3212 = 20;
      bssTableApiBuff.mcc = 99;
      bssTableApiBuff.mnc = 99;
      bssTableApiBuff.ncc = 5;
      bssTableApiBuff.nccPermitted = 200;
      bssTableApiBuff.dtxDnLinkInd = 1;
      bssTableApiBuff.dtxUpLinkInd = 1;
      bssTableApiBuff.minChannelGap = 3;
      /* bssTableApiBuff.rxAveraginNo = 4;
       bssTableApiBuff.cerPeriodicityTimer = 25;
         bssTableApiBuff.periodicCsAppTimer = 25;
         bssTableApiBuff.periodicCsStackTimer = 25;
         bssTableApiBuff.periodicPcuStackTimer = 25;
         bssTableApiBuff.periodicPlatformTimer = 25;
         bssTableApiBuff.periodicPsAppTimer = 25; 
      bssTableApiBuff.lRxLevDlP = 41;
      bssTableApiBuff.lRxLevUlP = 20;
      bssTableApiBuff.lRxQualDlP = 5;
      bssTableApiBuff.lRxQualUlP = 5; */
      bssTableApiBuff.maxRetrans = 4;
      /*   bssTableApiBuff.timerTraceLog = 40; */
      bssTableApiBuff.txInteger = 12;
      bssTableApiBuff.radioLinkTimeout = 6;
      bssTableApiBuff.shutdownTimer = 231;
      bssTableApiBuff.cicMaster = 1;
      /* bssTableApiBuff.enBsPctrl = TRUE;
      bssTableApiBuff.enMsPctrl = TRUE;
      bssTableApiBuff.rxDecStepSize = 1;
      bssTableApiBuff.rxIncrStepSize = 1;
      bssTableApiBuff.pConInterval = 31;
      bssTableApiBuff.qlAveraginNo = 29;
      bssTableApiBuff.rxTotalSamplesHigh = 21;
      bssTableApiBuff.rxTotalSamplesLow = 11;
      bssTableApiBuff.rxNoofSamplesLow = 11;
      bssTableApiBuff.rxNoOfSamplesHigh = 21;
      bssTableApiBuff.uRxLevDlP = 31;
      bssTableApiBuff.uRxLevUlP = 5;
      bssTableApiBuff.uRxQualDlP = 1;
      bssTableApiBuff.uRxQualUlP = 7;
      bssTableApiBuff.qlNoofSamplesHigh = 20;
      bssTableApiBuff.qlNoofSamplesLow = 20; 
      bssTableApiBuff.qlTotalSamplesHigh = 20;
      bssTableApiBuff.qlTotalSamplesLow = 20; */

      /*( if BSS Table is empty, then Insert */   
      if (NULL == bssTableApiPtr) 
      {
         if (CLIB_SUCCESS != insertBssTable(&bssTableApiBuff))
         {
            printf("\n cfgCmDbHndlr3:  insertBssTable failed");
            return;
         }
      }
      else  /*( if BSS Table has entry, then Update */
      {
         bssIndex.bscId = bssTableApiPtr->bscId;
         free(bssTableApiPtr);
         if (CLIB_SUCCESS != deleteBssTable(&bssIndex))
         {
            printf("\n cfgCmDbHndlr3: deleteBssTable failed");
            return;
         }
         if (CLIB_SUCCESS != insertBssTable(&bssTableApiBuff))
         {
            printf("\n cfgCmDbHndlr3:  insertBssTable failed");
            return;
         }
      }    
      printf("\n cfgCmDbHndlr3: Bss set Request-Same parameter values as in DB");
      cfgStubSendCmMessage(&bssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }       
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr3: Successfull Operation: Addition of same Row Failed");
                  gTestCaseCompleted = 1;
                  printf("In cfgCmDbHndlr1: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr3: Operation Failed");
                  gTestCaseCompleted = 1;
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */ 

         default:
            {
               printf("\n In cfgCmDbHndlr3: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/
}/* end of cfgCmDbHndlr3 */

void cfgCmDbHndlr4()
{
   static int testInitiation =1;

   BssTableApi bssTableApiBuff= {0};
   BssTableApi* bssTableApiPtr = NULL;
   BssTableIndices bssIndex = {0};
   I_S32 i = 0;
   I_U16 size  = 0;   
   I_S32 ret = 1;

   if ( testInitiation )
   {
      testInitiation =0;

      /* Check if BSS has an entry or not */  
      ret = getallBssTable (&bssTableApiPtr, &i, &size);

      printf("\n cfgCmDbHndlr4: Bss Update Request with out of range Parameters- Initiation\n");
      /* First set the required database */
      bssTableApiBuff.bscId =1;
      bssTableApiBuff.gprsEnabled =1;   
      bssTableApiBuff.adminState = 0; /* Locked */   
      bssTableApiBuff.attInd = ALLOWED;
      bssTableApiBuff.bssReset = FALSE;
      bssTableApiBuff.callReestablishmentInd =  ALLOWED;
      bssTableApiBuff.t3212 = 20;
      bssTableApiBuff.mcc = 99;
      bssTableApiBuff.mnc = 99;
      bssTableApiBuff.ncc = 5;
      bssTableApiBuff.nccPermitted = 200;
      bssTableApiBuff.dtxDnLinkInd = 1;
      bssTableApiBuff.dtxUpLinkInd = 1;
      bssTableApiBuff.minChannelGap = 3;
      /* bssTableApiBuff.rxAveraginNo = 4;
         bssTableApiBuff.cerPeriodicityTimer = 25;
         bssTableApiBuff.periodicCsAppTimer = 25;
         bssTableApiBuff.periodicCsStackTimer = 25;
         bssTableApiBuff.periodicPcuStackTimer = 25;
         bssTableApiBuff.periodicPlatformTimer = 25;
         bssTableApiBuff.periodicPsAppTimer = 25; 
      bssTableApiBuff.lRxLevDlP = 41;
      bssTableApiBuff.lRxLevUlP = 20;
      bssTableApiBuff.lRxQualDlP = 5;
      bssTableApiBuff.lRxQualUlP = 5; */
      bssTableApiBuff.maxRetrans = 4;
      /*      bssTableApiBuff.timerTraceLog = 40; */
      bssTableApiBuff.txInteger = 12;
      bssTableApiBuff.radioLinkTimeout = 6;
      bssTableApiBuff.shutdownTimer = 231;
      bssTableApiBuff.cicMaster = 1;
      /* bssTableApiBuff.enBsPctrl = TRUE;
      bssTableApiBuff.enMsPctrl = TRUE;
      bssTableApiBuff.rxDecStepSize = 1;
      bssTableApiBuff.rxIncrStepSize = 1;
      bssTableApiBuff.pConInterval = 31;
      bssTableApiBuff.qlAveraginNo = 29;
      bssTableApiBuff.rxTotalSamplesHigh = 21;
      bssTableApiBuff.rxTotalSamplesLow = 11;
      bssTableApiBuff.rxNoofSamplesLow = 11;
      bssTableApiBuff.rxNoOfSamplesHigh = 21;
      bssTableApiBuff.uRxLevDlP = 31;
      bssTableApiBuff.uRxLevUlP = 50;
      bssTableApiBuff.uRxQualDlP = 1;
      bssTableApiBuff.uRxQualUlP = 7;
      bssTableApiBuff.qlNoofSamplesHigh = 20;
      bssTableApiBuff.qlNoofSamplesLow = 20; 
      bssTableApiBuff.qlTotalSamplesHigh = 20;
      bssTableApiBuff.qlTotalSamplesLow = 20; */

      if (NULL != bssTableApiPtr)
      {
         bssIndex.bscId = bssTableApiPtr->bscId;
         free(bssTableApiPtr);
         if (CLIB_SUCCESS != deleteBssTable(&bssIndex))
         {
            printf("\n cfgCmDbHndlr4: deleteBssTable failed");
            return;
         }
      }
      printf("\n cfgCmDbHndlr4: Bss set Request with out of range parameter values");
      cfgStubSendCmMessage(&bssTableApiBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr4: Successfully handled");
                  printf("In cfgCmDbHndlr4: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr4: problem in handling, chk code");
               }         
               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr4: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr4 */

void cfgCmDbHndlr5()
{
   static int testInitiation =1;

   CellTableApi cellTableApiBuff= {0};
   CellTableIndices apiCellIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr5: Inserting row in Cell table with CellId not in DB- Initiation\n");

      apiCellIndex.cellId =  20;
      apiCellIndex.lac = 1;

      ret = deleteCellTable(&apiCellIndex);

      /* Send Cell Update Request - with CellId not in DB for Cell */
      cellTableApiBuff.cellId = 20; 
      cellTableApiBuff.adminState = LOCK;  /* LOCK = 0 */
      cellTableApiBuff.freqBandBcch = GSM_1800;
      cellTableApiBuff.lac = 1;
      cellTableApiBuff.bcchArfcn = 534;
      cellTableApiBuff.bcc = 0;
      cellTableApiBuff.msTxPowerMaxCch = 10;
      //cellTableApiBuff.csStatus = ALLOWED;
      cellTableApiBuff.psStatus = ALLOWED;
      ////cellTableApiBuff.pageStatus = ALLOWED;
      cellTableApiBuff.cellBarAccess = 1;
      cellTableApiBuff.accessCtrlClass = 30;
      cellTableApiBuff.bsAgBlksRes = 5;
      cellTableApiBuff.bsPaMfrms = 5;
      cellTableApiBuff.cellReselectHysteresis = 4;
      cellTableApiBuff.rxLevAccessMin = 63;
      cellTableApiBuff.powerOffset = 1;
      cellTableApiBuff.msTxPwrMax = 10;         

      printf("\n cfgCmDbHndlr5: Cell Update Request- with CellId not in DB sending");
      cfgStubSendCmMessage(&cellTableApiBuff,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr5: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr5: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr5: problem in handling, chk code");
               }

               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr5: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr5 */

void cfgCmDbHndlr6()
{
   static int testInitiation =1;

   CellTableApi cellTableApiBuff= {0};
   CellTableIndices apiCellIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      apiCellIndex.cellId =  20;
      apiCellIndex.lac = 1;

      ret = deleteCellTable(&apiCellIndex);

      printf("\n cfgCmDbHndlr6: Cell set Request-Same parameter values as in DB- Initiation\n");

      /* First set the required database */ 
      cellTableApiBuff.cellId = 20; 
      cellTableApiBuff.adminState = LOCK;  /* LOCK = 0 */
      cellTableApiBuff.freqBandBcch = GSM_1800;
      cellTableApiBuff.lac = 1;
      cellTableApiBuff.bcchArfcn = 534;
      cellTableApiBuff.bcc = 0;
      cellTableApiBuff.msTxPowerMaxCch = 10;
      //cellTableApiBuff.csStatus = ALLOWED;
      cellTableApiBuff.psStatus = ALLOWED;
      //cellTableApiBuff.pageStatus = ALLOWED;
      cellTableApiBuff.cellBarAccess = 1;
      cellTableApiBuff.accessCtrlClass = 30;
      cellTableApiBuff.bsAgBlksRes = 5;
      cellTableApiBuff.bsPaMfrms = 5;
      cellTableApiBuff.cellReselectHysteresis = 4;
      cellTableApiBuff.rxLevAccessMin = 63;
      cellTableApiBuff.powerOffset = 1;
      cellTableApiBuff.msTxPwrMax = 10;   

      printf("\n cfgCmDbHndlr6: Cell set Request-Same parameter values as in DB\n");
      if (CLIB_SUCCESS != insertCellTable(&cellTableApiBuff))
      {
         printf("\n cfgCmDbHndlr6: Cell set Request-Same parameter values as in DB, Insertion Failed");
         return;         
      }

      printf("\n cfgCmDbHndlr6: Cell set Request-Same parameter values as in DB sending");
      cfgStubSendCmMessage(&cellTableApiBuff,
            sizeof(CellTableApi),
            BSC_API_SET_CELLPERTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr6: Successfully handled");
                  printf("In cfgCmDbHndlr6: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr6: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr6: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr6 */


void cfgCmDbHndlr7()
{
   static int testInitiation =1;

   CellTableApi cellTableApiBuff= {0};
   CellTableIndices apiCellIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      apiCellIndex.cellId =  20;
      apiCellIndex.lac = 1;

      ret = deleteCellTable(&apiCellIndex);

      printf("\n cfgCmDbHndlr7: Cell Update Request with out of range Parameters- Initiation");

      /* First set the required database */ 
      cellTableApiBuff.cellId = 20; 
      cellTableApiBuff.adminState = LOCK;  /* LOCK = 0 */
      cellTableApiBuff.freqBandBcch = GSM_1800;
      cellTableApiBuff.lac = 1;
      cellTableApiBuff.bcchArfcn = 34;
      cellTableApiBuff.bcc = 0;
      cellTableApiBuff.msTxPowerMaxCch = 10;
      //cellTableApiBuff.csStatus = ALLOWED;
      cellTableApiBuff.psStatus = ALLOWED;
      //cellTableApiBuff.pageStatus = ALLOWED;
      cellTableApiBuff.cellBarAccess = 1;
      cellTableApiBuff.accessCtrlClass = 30;
      cellTableApiBuff.bsAgBlksRes = 5;
      cellTableApiBuff.bsPaMfrms = 5;
      cellTableApiBuff.cellReselectHysteresis = 4;
      cellTableApiBuff.rxLevAccessMin = 63;
      cellTableApiBuff.powerOffset = 1;
      cellTableApiBuff.msTxPwrMax = 10;   

      printf("\n cfgCmDbHndlr7: Cell set Request-with out of range Parameters");
      if (CLIB_SUCCESS != insertCellTable(&cellTableApiBuff))
      {
         printf("\n cfgCmDbHndlr7: Cell set Request-with out of range Parameters, Insertion Failed");
         return;         
      }              
      cellTableApiBuff.cellId = 20; 
      cellTableApiBuff.adminState = LOCK;  /* LOCK = 0 */
      cellTableApiBuff.freqBandBcch = GSM_1800;
      cellTableApiBuff.lac = 1;
      cellTableApiBuff.cellBarAccess = 6;
      cellTableApiBuff.accessCtrlClass = 30;
      cellTableApiBuff.msTxPwrMax = 200;      

      printf("\n cfgCmDbHndlr7: Cell Update Request- Sending Param Mod Out of range Msg to cell");
      cfgStubSendCmMessage(&cellTableApiBuff,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
   }/* End of if ( testInitiation ) */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr7: Successfully handled");
                  printf("In cfgCmDbHndlr7: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr6: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr7: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr7 */


void cfgCmDbHndlr8()
{
   static int testInitiation =1;

   CellTableApi cellTableApiBuff= {0};
   CellTableIndices apiCellIndex = {0};   
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      apiCellIndex.cellId =  20;
      apiCellIndex.lac = 1;

      ret = deleteCellTable(&apiCellIndex);

      printf("\n cfgCmDbHndlr8: Cell Update Request- Initiation");

      /* First set the required database */ 
      cellTableApiBuff.cellId = 20; 
      cellTableApiBuff.adminState = LOCK;  /* LOCK = 0 */
      cellTableApiBuff.freqBandBcch = GSM_1800;
      cellTableApiBuff.lac = 1;
      cellTableApiBuff.bcchArfcn = 534;
      cellTableApiBuff.bcc = 0;
      cellTableApiBuff.msTxPowerMaxCch = 10;
      //cellTableApiBuff.csStatus = ALLOWED;
      cellTableApiBuff.psStatus = ALLOWED;
      //cellTableApiBuff.pageStatus = ALLOWED;
      cellTableApiBuff.cellBarAccess = 1;
      cellTableApiBuff.accessCtrlClass = 30;
      cellTableApiBuff.bsAgBlksRes = 5;
      cellTableApiBuff.bsPaMfrms = 5;
      cellTableApiBuff.cellReselectHysteresis = 4;
      cellTableApiBuff.rxLevAccessMin = 63;
      cellTableApiBuff.powerOffset = 1;
      cellTableApiBuff.msTxPwrMax = 10;   

      printf("\n cfgCmDbHndlr8: Cell set Request-Parameter Updation");
      if (CLIB_SUCCESS != insertCellTable(&cellTableApiBuff))
      {
         printf("\n cfgCmDbHndlr8: Insertion Failed");
         return;         
      }               

      cellTableApiBuff.cellId = 20; 
      cellTableApiBuff.adminState = LOCK;  /* LOCK = 0 */
      cellTableApiBuff.freqBandBcch = GSM_1800;
      cellTableApiBuff.lac = 1;
      cellTableApiBuff.bcchArfcn = 534;
      cellTableApiBuff.bcc = 0;
      cellTableApiBuff.msTxPowerMaxCch = 10;
      //cellTableApiBuff.csStatus = NOT_ALLOWED;
      cellTableApiBuff.psStatus = NOT_ALLOWED;
      //cellTableApiBuff.pageStatus = NOT_ALLOWED;
      cellTableApiBuff.cellBarAccess = 0;   

      printf("\n cfgCmDbHndlr8: Cell Update Request- Sending Parameter Modified Msg to cell");
      cfgStubSendCmMessage(NULL,0,255);
      cfgStubSendCmMessage(&cellTableApiBuff,sizeof(CellTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else /* Execution Of Test Case */
   {
      printf("\n cfgCmDbHndlr8: ");
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr8: Successfully Updated");
                  printf("In cfgCmDbHndlr8: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr8: problem in handling, chk code");
               }         
               break;   
            } /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr8: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr8 */

void cfgCmDbHndlr900()
{
   static int testInitiation =1;
   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   PsCellTableApi psCellTableApiBuff= {0};
   PsCellTableIndices psCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      psCellIndex.cellId =  20;
      psCellIndex.lac = 1;

      printf("\n cfgCmDbHndlr9: PsCell Insert Request- Initiation");

      ret = deletePsCellTable(&psCellIndex);

      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr9: PsCell Update Request- No entry in Cell table");

         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 534;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         cellTableApiPtr->msTxPwrMax = 10; 

         errCode =  insertCellTable(cellTableApiPtr);

         if (CLIB_SUCCESS != errCode)
         {
            printf("\n cfgCmDbHndlr9: PsCell Update Request- insertCellTable failed");
            free(cellTableApiPtr);
            return;
         }
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }
      free(cellTableApiPtr);

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
      psCellTableApiBuff.pbcchPsiMsgBitMap = 50;
      psCellTableApiBuff.pccchPsiMsgBitMap = 50;
      //psCellTableApiBuff.btsPwrCtrlMode = 1;
      psCellTableApiBuff.prMode = 1;
      psCellTableApiBuff.dlBtsPwrCtrlEnabled = ENABLED ;
      psCellTableApiBuff.p0 = 2;
      psCellTableApiBuff.numOfPccchInCell = 7;
      psCellTableApiBuff.pccchBitMap = 7;    

      printf("\n cfgCmDbHndlr900: Sending Msg to CFG for inserting row in Pscell table");
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);

   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr9: Successfully Updated");
                  printf("In cfgCmDbHndlr9: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr9: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr9: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr9 */

void cfgCmDbHndlr9()
{
   static int testInitiation =1;
   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   PsCellTableApi psCellTableApiBuff= {0};
   PsCellTableIndices psCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      psCellIndex.cellId =  20;
      psCellIndex.lac = 1;

      printf("\n cfgCmDbHndlr9: PsCell Update Request- Initiation");

      ret == deletePsCellTable(&psCellIndex);
      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if ((errCode != CLIB_SUCCESS) ||(NULL == cellTableApiPtr))
      {
         printf("\n cfgCmDbHndlr9: PsCell Update Request- getCellTable Failed");

         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 534;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         cellTableApiPtr->msTxPwrMax = 10; 

         errCode =  insertCellTable(cellTableApiPtr);

         if (CLIB_SUCCESS != errCode)
         {
            printf("\n cfgCmDbHndlr9: PsCell Update Request- insertCellTable failed");
            free(cellTableApiPtr);
            return;
         }
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }
      free(cellTableApiPtr);

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
         printf("\n cfgCmDbHndlr9: PsCell Update Request- insertPsCellTable failed");
         return;
      }

      /* Set update request */
      psCellTableApiBuff.cellId = 20; 
      psCellTableApiBuff.cellBarAccess2 = 0;
      psCellTableApiBuff.raColour = 1;

      printf("\n cfgCmDbHndlr9: PsCell Update Request- Sending Parameter Modified Msg to Pscell");
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr9: Successfully Updated");
                  printf("In cfgCmDbHndlr9: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr9: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr9: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr9 */


void cfgCmDbHndlr10()
{
   static int testInitiation =1;
   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   PsCellTableApi psCellTableApiBuff= {0};
   PsCellTableIndices psCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      psCellIndex.cellId =  20;
      psCellIndex.lac = 1;

      printf("\n cfgCmDbHndlr10: PsCell set Request-Same parameter values as in DB");

      ret == deletePsCellTable(&psCellIndex);

      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr10: PsCell Update Request- Inserting in Cell table");
         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 534;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         errCode =  insertCellTable(cellTableApiPtr);
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }
      free(cellTableApiPtr);

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
      psCellTableApiBuff.pbcchPsiMsgBitMap = 57;
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
         printf("\n cfgCmDbHndlr10: PsCell set Request-Same parameter values as in DB- insertPsCellTable failed");
         return;
      }

      /* Send  same update request */      
      printf("\n cfgCmDbHndlr10: PsCell set Request-Same parameter values as in DB, Sending");
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr   10: Successfull Operation: Addition of same Row Failed");
                  printf("In cfgCmDbHndlr10: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr10: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr10: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr10 */

void cfgCmDbHndlr11()
{
   static int testInitiation =1;
   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   PsCellTableApi psCellTableApiBuff= {0};
   PsCellTableIndices psCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      psCellIndex.cellId =  20;
      psCellIndex.lac = 1;

      printf("\n cfgCmDbHndlr11: PsCell Update Request with out of range Parameters- Initiation");

      ret == deletePsCellTable(&psCellIndex);
      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr10: PsCell Update Request- Inserting in Cell table");
         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 534;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         errCode =  insertCellTable(cellTableApiPtr);
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }
      free(cellTableApiPtr);

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
      psCellTableApiBuff.pbcchPsiMsgBitMap = 57;
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
         printf("\n cfgCmDbHndlr11: PsCell set Request-Same parameter values as in DB- insertPsCellTable failed");
         return;
      }

      /* Send  out of range update request */         
      psCellTableApiBuff.cellId = 20; 
      psCellTableApiBuff.cellBarAccess2 = 1;
      psCellTableApiBuff.raColour = 2;
      psCellTableApiBuff.lac = 1;   
      psCellTableApiBuff.numOfPccchInCell = 10;

      printf("\n cfgCmDbHndlr11: PsCell Update Request- Sending Param Mod Out of range Msg to PsCell");
      cfgStubSendCmMessage(&psCellTableApiBuff,sizeof(PsCellTableApi),BSC_API_SET_PSCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr   11: Successfully handled");
                  printf("In cfgCmDbHndlr11: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr11: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr11: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr11 */


void cfgCmDbHndlr12()
{
   static int testInitiation =1;
   CsExternalCellTableApi csExtnCellTblApiBuff = {0};
   CsExternalCellTableIndices csExtnCellIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr12: CsExternalCellTable Update Request - with CellId not in DB- Initiation\n");          

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr13: setDbForBss Failed");
         return ;
      }

      csExtnCellIndex.csExtCellId =  10;
      csExtnCellIndex.lac =  10;
      csExtnCellIndex.mnc =  99;
      csExtnCellIndex.mcc =  99;

      errCode = deleteCsExternalCellTable(&csExtnCellIndex);

      /* Send CsExternalCellTable Update Request - with CellId not in DB */
      csExtnCellTblApiBuff.csExtCellId = 10; 
      csExtnCellTblApiBuff.lac = 10;
      csExtnCellTblApiBuff.bcchArfcn = 530;
      csExtnCellTblApiBuff.freqBandBcch = GSM_1800;
      csExtnCellTblApiBuff.mcc = 99;
      csExtnCellTblApiBuff.mnc = 99;
      csExtnCellTblApiBuff.ncc = 4;
      csExtnCellTblApiBuff.bcc = 5;

      printf("\n cfgCmDbHndlr12: CsExternalCellTable Update Request - with CellId not in DB, sending");
      cfgStubSendCmMessage(&csExtnCellTblApiBuff, sizeof(CsExternalCellTableApi),BSC_API_SET_CSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr12: Successfully handled");
                  printf("In cfgCmDbHndlr12: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr12: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr12: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr12 */


void cfgCmDbHndlr13()
{
   static int testInitiation =1;
   CsExternalCellTableApi csExtnCellTblApiBuff = {0};
   CsExternalCellTableIndices csExtnCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr13: CsExternalCellTable Update Request- Sending Param Modified Msg- Initiation\n");

      /* First set the BSS - precondition */
      errCode = setDbForBss();
      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr13: setDbForBss Failed");
         return;
      }

      csExtnCellIndex.csExtCellId =  10;
      csExtnCellIndex.lac =  10;
      csExtnCellIndex.mnc =  99;
      csExtnCellIndex.mcc =  99;

      ret = deleteCsExternalCellTable(&csExtnCellIndex);

      csExtnCellTblApiBuff.csExtCellId = 10; 
      csExtnCellTblApiBuff.lac = 10;
      csExtnCellTblApiBuff.bcchArfcn = 530;
      csExtnCellTblApiBuff.freqBandBcch = GSM_1800;
      csExtnCellTblApiBuff.mcc = 99;
      csExtnCellTblApiBuff.mnc = 99;
      csExtnCellTblApiBuff.ncc = 4;
      csExtnCellTblApiBuff.bcc = 5;

      if (CLIB_SUCCESS == insertCsExternalCellTable(&csExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr13: CsExternalCell set Request-Param Modified Msg, Insertion is FIne");
      }  
      else
      {
         if ( updateCsExternalCellTable(&csExtnCellTblApiBuff) != CLIB_SUCCESS )
            printf(" Updation failed ");
         return ;
      }

      /* Send CsExternalCellTable Update Request - Sending Parameter Modified Msg */
      csExtnCellTblApiBuff.bcchArfcn = 535;

      printf("\n cfgCmDbHndlr13: CsExternalCellTable Update Request - Sending Parameter Modified Msg");
      cfgStubSendCmMessage(&csExtnCellTblApiBuff, sizeof(CsExternalCellTableApi),BSC_API_SET_CSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr13: Successfully Updated");
                  printf("In cfgCmDbHndlr13: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr13: Updation Failed");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr13: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr13 */

void cfgCmDbHndlr14()
{
   static int testInitiation =1;
   CsExternalCellTableApi csExtnCellTblApiBuff= {0};
   CsExternalCellTableIndices csExtnCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr14: CsExternalCellTable Update Request- out of range Parameter- Initiation\n");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr14: setDbForBss Failed");
         return;
      }

      csExtnCellIndex.csExtCellId =  10;
      csExtnCellIndex.lac =  10;
      csExtnCellIndex.mnc =  99;
      csExtnCellIndex.mcc =  99;

      ret = deleteCsExternalCellTable(&csExtnCellIndex);

      csExtnCellTblApiBuff.csExtCellId = 10; 
      csExtnCellTblApiBuff.lac = 10;
      csExtnCellTblApiBuff.bcchArfcn = 530;
      csExtnCellTblApiBuff.freqBandBcch = GSM_1800;
      csExtnCellTblApiBuff.mcc = 99;
      csExtnCellTblApiBuff.mnc = 99;
      csExtnCellTblApiBuff.ncc = 4;
      csExtnCellTblApiBuff.bcc = 5;

      if (CLIB_SUCCESS != insertCsExternalCellTable(&csExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr14: CsExternalCell set Request-out of range Param, Insertion Failed");
         return;         
      } 

      /* Send CsExternalCellTable Update Request with out of range Parameters */
      csExtnCellTblApiBuff.csExtCellId = 10; 
      csExtnCellTblApiBuff.lac = 10;      
      csExtnCellTblApiBuff.ncc = 9;
      csExtnCellTblApiBuff.bcc = 10;

      printf("\n cfgCmDbHndlr14: CsExternalCellTable Update Request - Sending out of range Parameters Msg");
      cfgStubSendCmMessage(&csExtnCellTblApiBuff, sizeof(CsExternalCellTableApi),BSC_API_SET_CSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr14: Successfully Handled");
                  printf("In cfgCmDbHndlr14: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr14: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr14: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr14 */

void cfgCmDbHndlr15()
{
   static int testInitiation =1;
   CsExternalCellTableApi csExtnCellTblApiBuff= {0};
   CsExternalCellTableIndices csExtnCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr15: CsExternalCellTable Update Req- Same parameter values as in DB- Initiation\n");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr13: setDbForBss Failed");
         return;
      }

      csExtnCellIndex.csExtCellId =  10;
      csExtnCellIndex.lac =  10;
      csExtnCellIndex.mnc =  99;
      csExtnCellIndex.mcc =  99;

      ret = deleteCsExternalCellTable(&csExtnCellIndex);

      csExtnCellTblApiBuff.csExtCellId = 10; 
      csExtnCellTblApiBuff.lac = 10;
      csExtnCellTblApiBuff.bcchArfcn = 530;
      csExtnCellTblApiBuff.freqBandBcch = GSM_1800;
      csExtnCellTblApiBuff.mcc = 99;
      csExtnCellTblApiBuff.mnc = 99;
      csExtnCellTblApiBuff.ncc = 4;
      csExtnCellTblApiBuff.bcc = 5;

      if (CLIB_SUCCESS != insertCsExternalCellTable(&csExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr13: CsExternalCell set Request-Param Modified Msg, Insertion Failed");
         return;         
      } 

      /* Send CsExternalCellTable Update Request - Same parameter values as in DB */            
      printf("\n cfgCmDbHndlr15: CsExternalCellTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&csExtnCellTblApiBuff, sizeof(CsExternalCellTableApi),BSC_API_SET_CSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr15: Successfull Operation: Addition of same Row Failed");
                  printf("In cfgCmDbHndlr15: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr15: Operation Failed");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr15: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr15 */

void cfgCmDbHndlr16()
{
   static int testInitiation =1;
   PsExternalCellTableApi psExtnCellTblApiBuff= {0};
   PsExternalCellTableIndices psExtnCellIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr16: PsExternalCellTable Update Request - with CellId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr16: setDbForBss Failed");
         return;
      }

      psExtnCellIndex.psExtCellId =  10;
      psExtnCellIndex.lac =  10;
      psExtnCellIndex.mcc =  120;
      psExtnCellIndex.mnc =  99;

      errCode = deletePsExternalCellTable(&psExtnCellIndex);

      /* Send PsExternalCellTable Update Request - with CellId not in DB */
      psExtnCellTblApiBuff.psExtCellId = 10; 
      psExtnCellTblApiBuff.lac = 10;
      psExtnCellTblApiBuff.pbcchArfcn = 530;
      psExtnCellTblApiBuff.mnc = 99;
      psExtnCellTblApiBuff.mcc = 120;
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

      printf("\n cfgCmDbHndlr16: PsExternalCellTable Update Request - with CellId not in DB, sending");
      cfgStubSendCmMessage(&psExtnCellTblApiBuff, sizeof(PsExternalCellTableApi),BSC_API_SET_PSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr16: Successfully handled");
                  printf("In cfgCmDbHndlr16: Success\n");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  printf("\n cfgCmDbHndlr16: problem in handling, chk code");
                  gTestCaseCompleted = 1;
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr16: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr16 */

void cfgCmDbHndlr17()
{
   static int testInitiation =1;
   PsExternalCellTableApi psExtnCellTblApiBuff= {0};
   PsExternalCellTableIndices psExtnCellIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr17: PsExternalCellTable Update Request- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr17: setDbForBss Failed");
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
         printf("\n cfgCmDbHndlr17: PsExternalCell set Request-Param Modified Msg, Insertion Failed");
         return;         
      }     
      /* Send CsExternalCellTable Update Request - Sending Parameter Modified Msg  */
      psExtnCellTblApiBuff.gprsMsTxPwrMaxCch = 30;
      psExtnCellTblApiBuff.gprsRxLevAccessMin = 61;
      psExtnCellTblApiBuff.si13PbcchLocation = TN2;
      psExtnCellTblApiBuff.pbcchArfcn = 999;

      printf("\n cfgCmDbHndlr17: PsExternalCellTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&psExtnCellTblApiBuff, sizeof(PsExternalCellTableApi),BSC_API_SET_PSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr17: Successfully Updated");
                  printf("In cfgCmDbHndlr17: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr17: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr17: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr17 */


void cfgCmDbHndlr18()
{
   static int testInitiation =1;
   PsExternalCellTableApi psExtnCellTblApiBuff= {0};
   PsExternalCellTableIndices psExtnCellIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr18: PsExternalCellTable Update Request -with out of range Parameters- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr18: setDbForBss Failed");
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
      psExtnCellTblApiBuff.gprsReselectOffset = 2;
      psExtnCellTblApiBuff.psi1RepeatPeriod = 16;
      psExtnCellTblApiBuff.si13PbcchLocation = TN1;
      psExtnCellTblApiBuff.pbcchArfcn = 1024;

      if (CLIB_SUCCESS != insertPsExternalCellTable(&psExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr18: PsExternalCell set Request-Out of range, Insertion Failed");
         return;         
      } 

      /* Send CsExternalCellTable Update Request - with out of range Parameters */
      psExtnCellTblApiBuff.psExtCellId = 10; 
      psExtnCellTblApiBuff.lac = 10;
      psExtnCellTblApiBuff.gprsPenaltyTime = 320;
      psExtnCellTblApiBuff.gprsReselectOffset = 300;
      psExtnCellTblApiBuff.pbcchArfcn = 1030;

      printf("\n cfgCmDbHndlr18: PsExternalCellTable Update Request - Sending Param Mod Out of range Msg ");
      cfgStubSendCmMessage(&psExtnCellTblApiBuff, sizeof(PsExternalCellTableApi),BSC_API_SET_PSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr18: Successfully handled");
                  printf("In cfgCmDbHndlr18: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr18: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr18: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr18 */

void cfgCmDbHndlr19()
{
   static int testInitiation =1;
   PsExternalCellTableApi psExtnCellTblApiBuff= {0};
   PsExternalCellTableIndices psExtnCellIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr19: PsExternalCellTable Update Request - Same parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr19: setDbForBss Failed");
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
      psExtnCellTblApiBuff.gprsMsTxPwrMaxCch = 30;
      psExtnCellTblApiBuff.gprsRxLevAccessMin = 61;
      psExtnCellTblApiBuff.gprsTemporaryOffset = 5;
      psExtnCellTblApiBuff.gprsPenaltyTime = 320;
      psExtnCellTblApiBuff.gprsReselectOffset = 5;
      psExtnCellTblApiBuff.psi1RepeatPeriod = 16;
      psExtnCellTblApiBuff.si13PbcchLocation = TN2;
      psExtnCellTblApiBuff.pbcchArfcn = 999;

      if (CLIB_SUCCESS != insertPsExternalCellTable(&psExtnCellTblApiBuff))
      {
         printf("\n cfgCmDbHndlr19: PsExternalCell set Req-Same parameter values as in DB, Insertion Failed");
         return;         
      }                   
      /* Send CsExternalCellTable Update Request - Same parameter values as in DB */   

      printf("\n cfgCmDbHndlr19: PsExternalCellTable Update Request - Same parameter values as in DB, Sending");
      cfgStubSendCmMessage(&psExtnCellTblApiBuff, sizeof(PsExternalCellTableApi),BSC_API_SET_PSEXTERNALCELLTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr19: Successfull Operation: Addition of same Row Failed");
                  printf("In cfgCmDbHndlr19: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr19: Operation Failed");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr19: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr19 */

void cfgCmDbHndlr20()
{
   static int testInitiation =1;
   LaTableApi laTblApiBuff= {0};
   LaTableIndices laIndex= {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr20: LaTable Update Request - with LAC not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr16: setDbForBss Failed");
         return ;
      }

      laIndex.lac = 1;

      errCode = deleteLaTable(&laIndex);
      /* Send LaTable Update Request - with LAC not in DB */
      laTblApiBuff.lac= 1;

      printf("\n cfgCmDbHndlr20: LaTable Update Request - with LAC not in DB, sending");
      cfgStubSendCmMessage(&laTblApiBuff, sizeof(LaTableApi),BSC_API_SET_LATABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr20: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr20: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr20: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr20: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr20 */

void cfgCmDbHndlr21()
{
   static int testInitiation = 1;
   LaTableApi laTblApiBuff = {0};
   LaTableIndices laTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr21: LaTable Set Request with out of range Parameter- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr21: setDbForBss Failed");
         return ;
      }

      laTblIndex.lac = 65570;

      errCode = deleteLaTable(&laTblIndex);

      /* Send LaTable set Request- out of range lac */
      laTblApiBuff.lac= 65570;

      printf("\n cfgCmDbHndlr21: LaTable Set Request - with out of range Parameter, sending");
      cfgStubSendCmMessage(&laTblApiBuff, sizeof(LaTableApi),BSC_API_SET_LATABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr21: Successfully handled");
                  printf("In cfgCmDbHndlr21: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr21: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr20: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr21 */

void cfgCmDbHndlr22()
{
   static int testInitiation =1;
   LaTableApi laTblApiBuff= {0};
   LaTableIndices laTblIndex = {0};
   I_S32 errCode = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr22: LaTable Update Request - Same parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr16: setDbForBss Failed");
         return ;
      }

      laTblIndex.lac = 1;

      errCode = deleteLaTable(&laTblIndex);

      laTblApiBuff.lac= 1;        
      if (CLIB_SUCCESS != insertLaTable(&laTblApiBuff))
      {
         printf("\n cfgCmDbHndlr21: LaTable set Request-Out of range, Insertion Failed");
         return;         
      }   

      /* Send LaTable Update Request - Same parameter values as in DB */
      laTblApiBuff.lac= 1;      
      printf("\n cfgCmDbHndlr22: LaTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&laTblApiBuff, sizeof(LaTableApi),BSC_API_SET_LATABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr22: Successfully handled");
                  printf("In cfgCmDbHndlr22: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr22: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr22: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr22 */

void cfgCmDbHndlr23()
{
   static int testInitiation =1;
   RaTableApi raTblApiBuff= {0};
   RaTableIndices raIndex= {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr23: RaTable Update Request - with RAC not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr23: setDbForBss Failed");
         return ;
      }

      raIndex.rac = 1;
      raIndex.lac= 1;

      errCode = deleteRaTable(&raIndex);

      /* Send RaTable Update Request - with RAC not in DB */
      raTblApiBuff.rac = 1;
      raTblApiBuff.lac= 1;

      printf("\n cfgCmDbHndlr23: RaTable Update Request - with RAC not in DB, sending");
      cfgStubSendCmMessage(&raTblApiBuff, sizeof(RaTableApi),BSC_API_SET_RATABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr23: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr23: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr23: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr23: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr23 */

void cfgCmDbHndlr24()
{
   static int testInitiation =1;
   RaTableApi raTblApiBuff= {0};
   RaTableIndices raTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr24: RaTable Set Request with out of range Parameter- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr24: setDbForBss Failed");
         return ;
      }

      raTblIndex.lac = 1;
      raTblIndex.rac = 1;

      errCode = deleteRaTable(&raTblIndex);
      raTblApiBuff.lac = 1;
      raTblApiBuff.rac = 1;           
      if (CLIB_SUCCESS != insertRaTable(&raTblApiBuff))
      {
         printf("\n cfgCmDbHndlr24: RaTable set Request-out of range Param , Insertion Failed");
         return;         
      }

      /* Send LaTable set Request- out of range lac */
      raTblApiBuff.lac = 65570;
      raTblApiBuff.rac = 8;      
      printf("\n cfgCmDbHndlr24: RaTable Set Request - with out of range Parameter, sending");
      cfgStubSendCmMessage(&raTblApiBuff, sizeof(RaTableApi),BSC_API_SET_RATABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr24: Successfully handled");
                  printf("In cfgCmDbHndlr24: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr24: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr24: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr24 */

void cfgCmDbHndlr25()
{
   static int testInitiation =1;
   RaTableApi raTblApiBuff= {0};
   RaTableIndices raTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr25: RaTable Update Request - Same parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr25: setDbForBss Failed");
         return ;
      }

      raTblIndex.lac = 1;
      raTblIndex.rac = 1;

      errCode = deleteRaTable(&raTblIndex);

      raTblApiBuff.lac = 1;
      raTblApiBuff.rac = 1;           
      if (CLIB_SUCCESS != insertRaTable(&raTblApiBuff))
      {
         printf("\n cfgCmDbHndlr25: RaTable set Request-Same parameter values as in DB, Insertion Failed");
         return;         
      }

      /* Send RaTable Update Request - Same parameter values as in DB */
      raTblApiBuff.lac = 1;
      raTblApiBuff.rac = 1;      
      printf("\n cfgCmDbHndlr25: RaTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&raTblApiBuff, sizeof(RaTableApi),BSC_API_SET_RATABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr25: Successfully handled");
                  printf("In cfgCmDbHndlr25: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr25: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr25: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr25 */

void cfgCmDbHndlr26()
{
   static int testInitiation =1;

   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   ChnGrpTableApi chnGrpTblApiBuff= {0};
   ChnGrpTableIndices chnGrpIndex= {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;                  
      printf("\n cfgCmDbHndlr26: chnGrpTable Update Request - with ChnGrpId not in DB- Initiation");

      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr26: chnGrpTable Update Request- getCellTable Failed");
         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));

         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 34;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         cellTableApiPtr->msTxPwrMax = 10; 

         errCode =  insertCellTable(cellTableApiPtr);

         if (CLIB_SUCCESS != errCode)
         {
            printf("\n cfgCmDbHndlr9: PsCell Update Request- insertCellTable failed");
            free(cellTableApiPtr);
            return;
         }
         else
         {
            if (cellTableApiPtr->adminState != LOCK)
            {
               cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
               errCode =  updateCellTable(cellTableApiPtr);
            }
         }
      }

      free(cellTableApiPtr);

      chnGrpIndex.cellId = 20;
      chnGrpIndex.lac = 1;

      errCode = deleteChnGrpTable(&chnGrpIndex);

      /* Send chnGrpTable Update Request - with ChnGrpId not in DB */
      chnGrpTblApiBuff.cellId = 20;
      chnGrpTblApiBuff.lac = 1;
      chnGrpTblApiBuff.bcchCcchSdcch4 = 1;
      chnGrpTblApiBuff.bcchCcch = 1;
      chnGrpTblApiBuff.sdcch8 = 2;
      chnGrpTblApiBuff.tch = 47;
      chnGrpTblApiBuff.pdch = 47;
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

      printf("\n cfgCmDbHndlr26: chnGrpTable Update Request - with ChnGrpId  not in DB, sending");
      cfgStubSendCmMessage(&chnGrpTblApiBuff, sizeof(ChnGrpTableApi),BSC_API_SET_CHNGRPTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr26: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr26: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr26: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr26: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr26 */

void cfgCmDbHndlr27()
{
   static int testInitiation =1;

   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   ChnGrpTableApi chnGrpTblApiBuff= {0};
   ChnGrpTableIndices chnGrpTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;                  
      printf("\n cfgCmDbHndlr27: chnGrpTable Update Request -Initiation");

      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr27: chnGrpTable Update Request- getCellTable Failed");

         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 34;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         cellTableApiPtr->msTxPwrMax = 10; 

         errCode =  insertCellTable(cellTableApiPtr);

         if (CLIB_SUCCESS != errCode)
         {
            printf("\n cfgCmDbHndlr27: ChnGrpTable Update Request- insertCellTable failed");
            free(cellTableApiPtr);
            return;
         }
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }

      free(cellTableApiPtr);

      chnGrpTblIndex.cellId =  20;
      chnGrpTblIndex.lac = 1;

      errCode = deleteChnGrpTable(&chnGrpTblIndex);
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
         printf("\n cfgCmDbHndlr27: ChnGrpTable set Request-Param Modified Msg, Insertion Failed");
         return;         
      }     

      /* Send chnGrpTable Update Request  */
      chnGrpTblApiBuff.cellId = 20;
      chnGrpTblApiBuff.lac = 1;
      chnGrpTblApiBuff.tch = 40;
      chnGrpTblApiBuff.pdch = 40;   

      printf("\n cfgCmDbHndlr27: chnGrpTable Update Request - Sending Parameter Modified Msg");
      cfgStubSendCmMessage(&chnGrpTblApiBuff, sizeof(ChnGrpTableApi),BSC_API_SET_CHNGRPTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr27: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr27: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr27: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr27: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr27 */

void cfgCmDbHndlr28()
{
   static int testInitiation =1;

   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   ChnGrpTableApi chnGrpTblApiBuff= {0};
   ChnGrpTableIndices chnGrpTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;                  
      printf("\n cfgCmDbHndlr28: chnGrpTable Update Request -with out of range Parameters- Initiation");

      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr28: chnGrpTable Update Request- getCellTable Failed");

         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 34;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         cellTableApiPtr->msTxPwrMax = 10; 

         errCode =  insertCellTable(cellTableApiPtr);

         if (CLIB_SUCCESS != errCode)
         {
            printf("\n cfgCmDbHndlr28: ChnGrpTable Update Request- insertCellTable failed");
            free(cellTableApiPtr);
            return;
         }
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }

      free(cellTableApiPtr);

      chnGrpTblIndex.cellId =  20;
      chnGrpTblIndex.lac = 1;

      errCode = deleteChnGrpTable(&chnGrpTblIndex);
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
         printf("\n cfgCmDbHndlr28: ChnGrpTable set Request-out of range Param, Insertion Failed");
         return;         
      }     


      /* Send chnGrpTable Update Request - out of range Parameters */
      chnGrpTblApiBuff.cellId = 20;
      chnGrpTblApiBuff.tch = 50;
      chnGrpTblApiBuff.pdch = 55;   

      printf("\n cfgCmDbHndlr28: chnGrpTable Update Request - Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&chnGrpTblApiBuff, sizeof(ChnGrpTableApi),BSC_API_SET_CHNGRPTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr28: CM_ERR_END: Successfully handled");
                  printf("In cfgCmDbHndlr28: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr28: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr28: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr28 */

void cfgCmDbHndlr29()
{
   static int testInitiation =1;

   CellTableApi* cellTableApiPtr = NULL;
   CellTableIndices cellIndex = {0};
   ChnGrpTableApi chnGrpTblApiBuff= {0};
   ChnGrpTableIndices chnGrpIndex= {0};
   I_S32 errCode;
   if ( testInitiation )
   {
      testInitiation =0;                  
      printf("\n cfgCmDbHndlr29: chnGrpTable Update Request - Same parameter values as in DB- Initiation");

      /* Set DB for Cell */                 
      cellIndex.cellId = (I_U32)20;
      cellIndex.lac    = (I_U32)1;

      errCode = getCellTable(&cellIndex, &cellTableApiPtr);

      if (NULL == cellTableApiPtr)
      {
         printf("\n cfgCmDbHndlr28: chnGrpTable Update Request- getCellTable Failed");

         cellTableApiPtr = (CellTableApi *)calloc(1, sizeof(CellTableApi));
         cellTableApiPtr->cellId = 20; 
         cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
         cellTableApiPtr->freqBandBcch = GSM_1800;
         cellTableApiPtr->lac = 1;
         cellTableApiPtr->bcchArfcn = 34;
         cellTableApiPtr->bcc = 0;
         cellTableApiPtr->msTxPowerMaxCch = 10;
         //cellTableApiPtr->csStatus = ALLOWED;
         cellTableApiPtr->psStatus = ALLOWED;
         //cellTableApiPtr->pageStatus = ALLOWED;
         cellTableApiPtr->cellBarAccess = 1;
         cellTableApiPtr->accessCtrlClass = 30;
         cellTableApiPtr->bsAgBlksRes = 5;
         cellTableApiPtr->bsPaMfrms = 5;
         cellTableApiPtr->cellReselectHysteresis = 4;
         cellTableApiPtr->rxLevAccessMin = 63;
         cellTableApiPtr->powerOffset = 1;
         cellTableApiPtr->msTxPwrMax = 10; 

         errCode =  insertCellTable(cellTableApiPtr);

         if (CLIB_SUCCESS != errCode)
         {
            printf("\n cfgCmDbHndlr29: ChnGrpTable Update Request- insertCellTable failed");
            free(cellTableApiPtr);
            return;
         }
      }
      else
      {
         if (cellTableApiPtr->adminState != LOCK)
         {
            cellTableApiPtr->adminState = LOCK;  /* LOCK = 0 */
            errCode =  updateCellTable(cellTableApiPtr);
         }
      }
      free(cellTableApiPtr);

      chnGrpIndex.cellId =  20;
      chnGrpIndex.lac = 1;

      errCode = deleteChnGrpTable(&chnGrpIndex);

      chnGrpTblApiBuff.cellId = 20;
      chnGrpTblApiBuff.lac = 1;
      chnGrpTblApiBuff.bcchCcchSdcch4 = 1;
      chnGrpTblApiBuff.bcchCcch = 1;
      chnGrpTblApiBuff.sdcch8 = 2;
      chnGrpTblApiBuff.tch = 40;
      chnGrpTblApiBuff.pdch = 40;   
      chnGrpTblApiBuff.hsn = 30;
      chnGrpTblApiBuff.maxTxPwr = 20000;
      chnGrpTblApiBuff.tsc = 5;
      chnGrpTblApiBuff.band = GSM_900;
      chnGrpTblApiBuff.validArfcns = 18;
      chnGrpTblApiBuff.arfcn1 = 124;
      chnGrpTblApiBuff.arfcn2 = 124;
      chnGrpTblApiBuff.arfcn3 = 124;
      chnGrpTblApiBuff.arfcn4 = 124;
      chnGrpTblApiBuff.arfcn5 = 124;         
      chnGrpTblApiBuff.arfcn6 = 124;
      chnGrpTblApiBuff.arfcn7 = 124;
      chnGrpTblApiBuff.arfcn8 = 124;
      chnGrpTblApiBuff.arfcn9 = 124;
      chnGrpTblApiBuff.arfcn10 = 124;         
      chnGrpTblApiBuff.arfcn11 = 124;
      chnGrpTblApiBuff.arfcn12 = 124;
      chnGrpTblApiBuff.arfcn13 = 124;
      chnGrpTblApiBuff.arfcn14 = 124;
      chnGrpTblApiBuff.arfcn15 = 124;         
      chnGrpTblApiBuff.arfcn16 = 124;
      chnGrpTblApiBuff.arfcn17 = 124;
      //chnGrpTblApiBuff.arfcn18 = 124;

      if (CLIB_SUCCESS != insertChnGrpTable(&chnGrpTblApiBuff))
      {
         printf("\n cfgCmDbHndlr29: ChnGrpTable set Request-out of range Param, Insertion Failed");
         return;         
      }     
      /* Send chnGrpTable Update Request - Same parameter values as in DB */
      printf("\n cfgCmDbHndlr29: chnGrpTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&chnGrpTblApiBuff, sizeof(ChnGrpTableApi),BSC_API_SET_CHNGRPTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr29: CM_ERR_END: Successfully handled");
                  printf("In cfgCmDbHndlr29: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr29: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr29: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr29 */

void cfgCmDbHndlr30()
{
   static int testInitiation =1;
   BssTableApi* bssTableApiPtr = NULL;
   CsNeighCellsTableApi csNeighCellsTblApiBuff= {0};
   CsNeighCellsTableIndices csNeighCellIndex = {0};
   I_S32 errCode = 0;
   I_S32 count = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr30: CsNeighCellsTable Update Request - with CellId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
         return ;
      }

      csNeighCellIndex.cellId =  2;
      csNeighCellIndex.lac =  1;
      //csNeighCellIndex.cellType =  INTERNAL;
      csNeighCellIndex.neighborCellId =  2;

      errCode = deleteCsNeighCellsTable(&csNeighCellIndex);

      /* Send CsNeighCellsTable Update Request - with CellId not in DB */
      csNeighCellsTblApiBuff.cellId = 2;
      csNeighCellsTblApiBuff.lac = 1;
      csNeighCellsTblApiBuff.cellType = INTERNAL;
      csNeighCellsTblApiBuff.neighborCellId = 2;
      csNeighCellsTblApiBuff.neighborLac = 1;
      csNeighCellsTblApiBuff.neighborMcc = 91;
      csNeighCellsTblApiBuff.neighborMnc = 91;
      csNeighCellsTblApiBuff.relationType = ACTIVE;      

      printf("\n cfgCmDbHndlr30: CsNeighCellsTable Update Request - with cellId not in DB, sending");
      cfgStubSendCmMessage(&csNeighCellsTblApiBuff, sizeof(CsNeighCellsTableApi),BSC_API_SET_CSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr30: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr30: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr30: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr30: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr30 */

void cfgCmDbHndlr31()
{
   static int testInitiation =1;
   CsNeighCellsTableApi csNeighCellsTblApiBuff= {0};
   CsNeighCellsTableIndices csNeighCellsIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr31: CsNeighCellsTable Update Request - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
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
         printf("\n cfgCmDbHndlr31: CsNeighCells set Request-Param Modified Msg, Insertion Failed");
         return;         
      }     

      /* Send CsNeighCellsTable Update Request - Parameter Modified Msg  */
      csNeighCellsTblApiBuff.neighborMcc = 95;
      csNeighCellsTblApiBuff.neighborMnc = 95;
      csNeighCellsTblApiBuff.relationType = IDLE;

      printf("\n cfgCmDbHndlr31: CsNeighCellsTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&csNeighCellsTblApiBuff, sizeof(CsNeighCellsTableApi),BSC_API_SET_CSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr31: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr31: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr31: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr31: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr31 */

void cfgCmDbHndlr32()
{
   static int testInitiation =1;
   CsNeighCellsTableApi csNeighCellsTblApiBuff= {0};
   CsNeighCellsTableIndices csNeighCellsIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr32: CsNeighCellsTable Update Request - with out of range Parameters- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
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
         printf("\n cfgCmDbHndlr32: CsNeighCells set Request-Out of range, Insertion Failed");
         return;         
      }                     

      /* Send CsNeighCellsTable Update Request - with with out of range Parameters */
      csNeighCellsTblApiBuff.cellId = 2;
      csNeighCellsTblApiBuff.lac = 1;
      csNeighCellsTblApiBuff.cellType = INTERNAL;
      csNeighCellsTblApiBuff.neighborMnc = 1000;

      printf("\n cfgCmDbHndlr32: CsNeighCellsTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&csNeighCellsTblApiBuff, sizeof(CsNeighCellsTableApi),BSC_API_SET_CSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr32: CM_ERR_END: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr32: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr32: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr32: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr32 */

void cfgCmDbHndlr33()
{
   static int testInitiation =1;
   CsNeighCellsTableApi csNeighCellsTblApiBuff= {0};
   CsNeighCellsTableIndices csNeighCellsIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr33: CsNeighCellsTable Update Request - Same parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();
      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
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
      csNeighCellsTblApiBuff.neighborMcc = 95;
      csNeighCellsTblApiBuff.neighborMnc = 95;
      csNeighCellsTblApiBuff.relationType = ACTIVE;

      if (CLIB_SUCCESS != insertCsNeighCellsTable(&csNeighCellsTblApiBuff))
      {
         printf("\n cfgCmDbHndlr33: CsNeighCells set Request-Same param values as in DB, Insertion Failed");
         return;         
      }     

      /* Send CsNeighCellsTable Update Request -Same parameter values as in DB */
      printf("\n cfgCmDbHndlr33: CsNeighCellsTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&csNeighCellsTblApiBuff,
            sizeof(CsNeighCellsTableApi),
            BSC_API_SET_CSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr33: CM_ERR_END: Successfully handled");
                  printf("In cfgCmDbHndlr33: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr33: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr33: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr33 */

void cfgCmDbHndlr34()
{
   static int testInitiation =1;
   PsNeighCellsTableApi psNeighCellsTblApiBuff= {0};
   PsNeighCellsTableIndices psNeighCellsIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr34: PsNeighCellsTable Update Request - with CellId not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
         return ;
      }

      psNeighCellsIndex.psCellId = 2;
      psNeighCellsIndex.lac = 1;
      psNeighCellsIndex.cellType = INTERNAL;
      psNeighCellsIndex.psNeighborCellId = 2;
      psNeighCellsIndex.psNeighborLac = 1;

      errCode = deletePsNeighCellsTable(&psNeighCellsIndex);

      /* Send PsNeighCellsTable Update Request - with CellId not in DB */
      psNeighCellsTblApiBuff.psCellId = 2;
      psNeighCellsTblApiBuff.lac = 1;
      psNeighCellsTblApiBuff.cellType = INTERNAL;
      psNeighCellsTblApiBuff.psNeighborCellId = 2;
      psNeighCellsTblApiBuff.psNeighborLac = 1;
      psNeighCellsTblApiBuff.psNeighborMcc = 91;
      psNeighCellsTblApiBuff.psNeighborMnc = 91;
      psNeighCellsTblApiBuff.relationType = ACTIVE_IDLE;      

      printf("\n cfgCmDbHndlr34: PsNeighCellsTable Update Request - with cellId not in DB, sending");
      cfgStubSendCmMessage(&psNeighCellsTblApiBuff, sizeof(PsNeighCellsTableApi),BSC_API_SET_PSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr34: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr34: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr34: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr34: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr34 */

void cfgCmDbHndlr35()
{
   static int testInitiation =1;
   PsNeighCellsTableApi psNeighCellsTblApiBuff= {0};
   PsNeighCellsTableIndices psNeighCellsIndex = {0};
   I_S32 errCode = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr35: PsNeighCellsTable Update Request - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
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
         printf("\n cfgCmDbHndlr35: PsNeighCells set Request-Param Mod Msg, Insertion Failed");
         return;         
      } 

      /* Send PsNeighCellsTable Update Request - Parameter Modified Msg  */

      psNeighCellsTblApiBuff.psCellId = 2;
      psNeighCellsTblApiBuff.lac = 1;
      psNeighCellsTblApiBuff.cellType = INTERNAL;
      psNeighCellsTblApiBuff.psNeighborCellId = 2;
      psNeighCellsTblApiBuff.psNeighborLac = 1;
      psNeighCellsTblApiBuff.psNeighborMcc = 50;
      psNeighCellsTblApiBuff.psNeighborMnc = 55;      

      printf("\n cfgCmDbHndlr35: PsNeighCellsTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&psNeighCellsTblApiBuff, sizeof(PsNeighCellsTableApi),BSC_API_SET_PSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr35: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr35: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr35: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr35: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr35 */

void cfgCmDbHndlr36()
{
   static int testInitiation =1;
   PsNeighCellsTableApi psNeighCellsTblApiBuff= {0};
   PsNeighCellsTableIndices psNeighCellsIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr36: PsNeighCellsTable Update Request - with out of range Parameters- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
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
         printf("\n cfgCmDbHndlr36: PsNeighCells set Request-Out of range, Insertion Failed");
         return;         
      }               

      /* Send PsNeighCellsTable Update Request - with with out of range Parameters */
      psNeighCellsTblApiBuff.psNeighborMnc = 1000;
      psNeighCellsTblApiBuff.relationType = 7;

      printf("\n cfgCmDbHndlr36: PsNeighCellsTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&psNeighCellsTblApiBuff, sizeof(PsNeighCellsTableApi),BSC_API_SET_PSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr36: CM_ERR_END: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr36: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr36: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr36: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr36 */

void cfgCmDbHndlr37()
{
   static int testInitiation =1;
   PsNeighCellsTableApi psNeighCellsTblApiBuff= {0};
   PsNeighCellsTableIndices psNeighCellsIndex = {0};
   I_S32 errCode = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr37: PsNeighCellsTable Update Request - Same parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
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
      psNeighCellsTblApiBuff.relationType = 2;      

      if (CLIB_SUCCESS != insertPsNeighCellsTable(&psNeighCellsTblApiBuff))
      {
         printf("\n cfgCmDbHndlr37: PsNeighCells set Request-Same param values as in DB, Insertion Failed");
         return;         
      }               

      /* Send PsNeighCellsTable Update Request -Same parameter values as in DB */
      printf("\n cfgCmDbHndlr37: PsNeighCellsTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&psNeighCellsTblApiBuff, sizeof(PsNeighCellsTableApi),BSC_API_SET_PSNEIGHCELLSTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr37: CM_ERR_END: Successfully handled");
                  printf("In cfgCmDbHndlr37: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr37: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr37: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr37 */

void cfgCmDbHndlr38()
{
   static int testInitiation =1;
   ArfcnListTableApi arfcnListTblApiBuff= {0};
   ArfcnListTableIndices arfcnListIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr38: ArfcnListTable Update Request - with band not in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
         return ;
      }

      arfcnListIndex.band = GSM_1900;
      arfcnListIndex.arfcn = 810;      

      errCode = deleteArfcnListTable(&arfcnListIndex);

      /* Send ArfcnListTable Update Request - with band not in DB */
      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 810;      

      printf("\n cfgCmDbHndlr38: ArfcnListTable Update Request - with band not in DB, sending");
      cfgStubSendCmMessage(&arfcnListTblApiBuff, sizeof(ArfcnListTableApi),BSC_API_SET_ARFCNLISTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr38: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr38: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr38: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr38: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr38 */

void cfgCmDbHndlr39()
{
   static int testInitiation =1;
   ArfcnListTableApi arfcnListTblApiBuff= {0};
   ArfcnListTableIndices arfcnTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr39: ArfcnListTable Update Request - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
         return;
      }

      arfcnTblIndex.band = GSM_1900;
      arfcnTblIndex.arfcn = 512;

      errCode = deleteArfcnListTable(&arfcnTblIndex);

      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 512;      

      if (CLIB_SUCCESS != insertArfcnListTable(&arfcnListTblApiBuff))
      {
         printf("\n cfgCmDbHndlr39: ArfcnList set Request-Param Mod Msg, Insertion Failed");
         return;         
      } 

      /* Send ArfcnListTable Update Request - Parameter Modified Msg  */
      arfcnTblIndex.band = GSM_1900;
      arfcnTblIndex.arfcn = 540;

      errCode = deleteArfcnListTable(&arfcnTblIndex);

      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 540;      
      printf("\n cfgCmDbHndlr39: ArfcnListTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&arfcnListTblApiBuff, sizeof(ArfcnListTableApi),BSC_API_SET_ARFCNLISTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr39: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr39: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr39: problem in handling, chk code");
               }   
               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr39: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr39 */

void cfgCmDbHndlr40()
{
   static int testInitiation =1;
   ArfcnListTableApi arfcnListTblApiBuff= {0};
   ArfcnListTableIndices arfcnTblIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr40: ArfcnListTable Update Request - with out of range Parameters- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
         return ;
      }

      arfcnTblIndex.band = GSM_1900;
      arfcnTblIndex.arfcn = 512;

      errCode = deleteArfcnListTable(&arfcnTblIndex);

      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 512;      

      if (CLIB_SUCCESS != insertArfcnListTable(&arfcnListTblApiBuff))
      {
         printf("\n cfgCmDbHndlr40: ArfcnList set Request-out of range, Insertion Failed");
         return;         
      } 

      /* Send ArfcnListTable Update Request - with with out of range Parameters */
      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 500;  /* valid range is 512-810  for  GSM_1900 */            
      printf("\n cfgCmDbHndlr40: ArfcnListTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&arfcnListTblApiBuff,
            sizeof(ArfcnListTableApi),
            BSC_API_SET_ARFCNLISTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr40: CM_ERR_END: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr40: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr40: problem in handling, chk code");
               }         
               break;   
            } /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr40: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr40 */

void cfgCmDbHndlr41()
{
   static int testInitiation =1;
   ArfcnListTableApi arfcnListTblApiBuff= {0};
   ArfcnListTableIndices arfcnTblIndex = {0};
   I_S32 errCode = 0;   

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr41: ArfcnListTable Update Request - Same parameter values as in DB- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n setDbForBss Failed");
         return ;
      }

      arfcnTblIndex.band = GSM_1900;
      arfcnTblIndex.arfcn = 512;

      errCode = deleteArfcnListTable(&arfcnTblIndex);

      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 512;      

      if (CLIB_SUCCESS != insertArfcnListTable(&arfcnListTblApiBuff))
      {
         printf("\n cfgCmDbHndlr41: ArfcnList set Request-Same paramvalues as in DB, Insertion Failed");
         return;         
      } 
      /* Send ArfcnListTable Update Request -Same parameter values as in DB */
      arfcnListTblApiBuff.band = GSM_1900;
      arfcnListTblApiBuff.arfcn = 512;      
      printf("\n cfgCmDbHndlr41: ArfcnListTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&arfcnListTblApiBuff,
            sizeof(ArfcnListTableApi),
            BSC_API_SET_ARFCNLISTTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status !=CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr41: CM_ERR_END: Successfully handled");
                  printf("In cfgCmDbHndlr41: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr41: problem in handling, chk code");
               }         
               break;   
            } /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr41: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr41 */

void cfgCmDbHndlr42()
{
   static int testInitiation =1;

   TrauConfigTableApi trauConfigTblApiBuff= {0};   

   if ( testInitiation )
   {
      testInitiation =0;

      /* Send TrauTable Update Request - with band not in DB */
      trauConfigTblApiBuff.trauDspId = 1;
      trauConfigTblApiBuff.trauNumSpeechChannels = 1;

      printf("\n cfgCmDbHndlr42: TrauTable Update Request Sending ");
      cfgStubSendCmMessage(&trauConfigTblApiBuff, sizeof(TrauConfigTableApi), BSC_API_SET_TRAUCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr42: CM_ERR_END: Successfully handled as read only table");
                  printf("In cfgCmDbHndlr42: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr42: problem in handling, chk code");
               }         
               break;   
            } /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr42: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr42 */

void cfgCmDbHndlr43()
{
   static int testInitiation =1;

   AInterfaceTableApi aIntTblApiBuff= {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr43: AInterfaceTable Update Request-  Initiation");          

      /* Send AInterfaceTable Update Request - with band not in DB */
      aIntTblApiBuff.dummyIndex= 1;
      aIntTblApiBuff.oprState = ENABLED;

      printf("\n cfgCmDbHndlr43: AInterfaceTable Update Request Sending");
      cfgStubSendCmMessage(&aIntTblApiBuff, sizeof(AInterfaceTableApi),BSC_API_SET_AINTERFACETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_ERR_END)
               {
                  printf("\n cfgCmDbHndlr43: CM_ERR_END: Successfully handled as read only table");
                  printf("In cfgCmDbHndlr43: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr43: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr43: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr43 */

void cfgCmDbHndlr179()
{
   static int testInitiation =1;
   TimeSlotTableApi TimeSlotTableApiBuff = {0};
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr179: E1 TimeSlot Table - initailization");

      TimeSlotTableApiBuff.e1Num = 11;
      TimeSlotTableApiBuff.tsNum = 12;
      TimeSlotTableApiBuff.adminState = LOCK ; /* locked */
      TimeSlotTableApiBuff.oprState = 0;/*disabled */
      TimeSlotTableApiBuff.usageType = 1;/*Asumed FR as 1 */
      TimeSlotTableApiBuff.usingEntity = 17;/*FR Index value(16-199)*/

      if (CLIB_SUCCESS != insertTimeSlotTable(&TimeSlotTableApiBuff))
      {
         printf("\n cfgCmDbHndlr179:  insertTimeSlotTable failed");
      }

      TimeSlotTableApiBuff.usingEntity = 2;

      printf("\n cfgCmDbHndlr179: Set for TimeSlotTable: Param Modified");
      cfgStubSendCmMessage(&TimeSlotTableApiBuff,
            sizeof(TimeSlotTableApi),
            BSC_API_SET_TIMESLOTPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr179: Successfully handled");                           
                  printf("In cfgCmDbHndlr179: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr179: prob in handling,Chk code");
               }                    
            }
            break;   /* end of case CM_API_APP_RESPONSE */ 

         default:
            {
               printf("\n In cfgCmDbHndlr179: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* end of cfgCmDbHndlr179 */

void cfgCmDbHndlr178()
{
   static int testInitiation =1;
   E1TableApi E1TableApiBuff ={0};
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr178: E1 Table values setting in DB\n");

      E1TableApiBuff.e1Num = 1;
      E1TableApiBuff.adminState = LOCK;
      E1TableApiBuff.oprState = 1; /* Enabled */
      E1TableApiBuff.usingEntity = 1; /* Assumed AIF as 1 */

      if (CLIB_SUCCESS != insertE1Table(&E1TableApiBuff))
      {
         printf("\n cfgCmDbHndlr178:  insertE1Table failed");
      }

      E1TableApiBuff.usingEntity = 2;

      printf("\n cfgCmDbHndlr178: Set for E1Table: Param Modified");
      cfgStubSendCmMessage(&E1TableApiBuff, sizeof(E1TableApi),
            BSC_API_SET_E1PERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr178: Successfully handled");
                  printf("In cfgCmDbHndlr178: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr178: prob in handling,Chk code");
                  printf("In cfgCmDbHndlr178: Failed\n");
               }                    
            }
            break; /* end of case CM_API_APP_RESPONSE */ 

         default:
            {
               printf("\n In cfgCmDbHndlr178: Msg Discarded ");
               printf("In cfgCmDbHndlr178: Failed\n");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }
} /* end of cfgCmDbHndlr178 */

#if 0
void cfgCmDbHndlr177()
{
   static int testInitiation =1;
   PhysicalTrxPreconfiguredTableApi PhysicalTrxPreconfiguredTableApiBuff = {0};
   PhysicalTrxPreconfiguredTableIndices PhysicalTrxPreconfiguredTableIndicesBuff;
   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr177: Ptrx Values setting in DB\n");
      PhysicalTrxPreconfiguredTableIndicesBuff.ptrxId=1;

      deletePhysicalTrxPreconfiguredTable(&PhysicalTrxPreconfiguredTableIndicesBuff);
      PhysicalTrxPreconfiguredTableApiBuff.ptrxId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.tei = 2; 
      PhysicalTrxPreconfiguredTableApiBuff.adminState = LOCK;
      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 1; /* enabled */
      PhysicalTrxPreconfiguredTableApiBuff.e1Id = TRUE;
      PhysicalTrxPreconfiguredTableApiBuff.rackId = 1;
      /*PhysicalTrxPreconfiguredTableApiBuff.trxHwVersionId = 1;*/
      PhysicalTrxPreconfiguredTableApiBuff.slotId = 1;
      PhysicalTrxPreconfiguredTableApiBuff.startE1Timeslot = 1;/* enum */

      if (CLIB_SUCCESS != insertPhysicalTrxPreconfiguredTable(& PhysicalTrxPreconfiguredTableApiBuff))
      {
         printf("\n cfgCmDbHndlr177:  insertPhysicalTrxPreconfiguredTable failed");
      }

      PhysicalTrxPreconfiguredTableApiBuff.antennaId = 2; 

      printf("\n cfgCmDbHndlr177: Set for PtrxTable: Param Modified");
      cfgStubSendCmMessage(&PhysicalTrxPreconfiguredTableApiBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               gTestCaseCompleted = 1;
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\ncfgCmDbHndlr177: Successfully handled");
                  printf("In cfgCmDbHndlr177: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr177: Prob in handling, chk code");
                  printf("In cfgCmDbHndlr177: Failed\n");
               }                    
            }
            break; /* end of case CM_API_APP_RESPONSE */ 

         default:
            printf("\n In cfgCmDbHndlr177: Msg Discarded ");
            printf("In cfgCmDbHndlr177: Failed\n");
      } /* end of Switch */

   }
} /* end of cfgCmDbHndlr177 */
#endif

//*******************************************************************************************************
/* start of cfgCmDbHndlr77 */
void cfgCmDbHndlr77() 
{

   static int testInitiation =1;
   I_S32 errCode = 0;
   GbInterfaceTableApi gbInterfaceTableApiBuff = {0};
   GbInterfaceTableIndices apiGbIfIndex = {0};
   apiGbIfIndex.dummyIndex = 1;

   printf("\n I am here in 77 \n");   
   if ( testInitiation )
   { 
      testInitiation=0;          
      printf("\n cfgCmDbHndlr77: GbInterfaceTable Update Request - with params not in DB");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr77: setDbForBss Failed");
      }

      /*deleting the row ,if already exist...*/  
      deleteGbInterfaceTable(&apiGbIfIndex);

      /* Send GbInterfaceTable Update Request - with params not in DB */
      gbInterfaceTableApiBuff.dummyIndex = 1; /*key */
      gbInterfaceTableApiBuff.oprState= 1;
      gbInterfaceTableApiBuff.nsei= 1;
      gbInterfaceTableApiBuff.maxNumNsvcs= 1;
      gbInterfaceTableApiBuff.maxNumLeps= 1;
      gbInterfaceTableApiBuff.maxNumReps= 1;
      gbInterfaceTableApiBuff.transportType= 1;

      printf("\n cfgCmDbHndlr77: GbInterfaceTable Update Request - with params not in DB, sending");
      cfgStubSendCmMessage(&gbInterfaceTableApiBuff, sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr77: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr77: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr77: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr77: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr77*/

/* start of cfgCmDbHndlr78 */
void cfgCmDbHndlr78()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   GbInterfaceTableApi gbInterfaceTableApiBuff = {0};

   GbInterfaceTableIndices apiGbIfIndex = {0};
   apiGbIfIndex.dummyIndex = 1;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr78: param Update Request - Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr78: setDbForBss Failed");
         return ;
      }
      /*deleting the row ,if already exist...*/  
      deleteGbInterfaceTable(&apiGbIfIndex);

      gbInterfaceTableApiBuff.dummyIndex = 1; /*key */
      gbInterfaceTableApiBuff.oprState= 1;
      gbInterfaceTableApiBuff.nsei= 1;
      gbInterfaceTableApiBuff.maxNumNsvcs= 1;
      gbInterfaceTableApiBuff.maxNumLeps= 1;
      gbInterfaceTableApiBuff.maxNumReps= 1;
      gbInterfaceTableApiBuff.transportType= 1;

      insertGbInterfaceTable(&gbInterfaceTableApiBuff);

      /* Send GbInterfaceTableUpdate Request - Parameter Modified Msg  */
      gbInterfaceTableApiBuff.nsei= 2;

      printf("\n cfgCmDbHndlr78: GbInterfaceTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&gbInterfaceTableApiBuff, sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr78: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr78: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr78: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr78: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr78*/

/* Start of cfgCmDbHndlr79 */
void cfgCmDbHndlr79()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   GbInterfaceTableApi gbInterfaceTableApiBuff = {0};
   GbInterfaceTableIndices apiGbIfIndex = {0};
   apiGbIfIndex.dummyIndex = 1;


   if ( testInitiation )
   {
      /* First set the BSS - precondition */
      testInitiation=0;
      printf("\n cfgCmDbHndlr79: GbInterfaceTable Update Request - Param Mod Out of range Msg");
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr79: setDbForBss Failed");
         return ;
      }
      /*deleting the row ,if already exist...*/
      deleteGbInterfaceTable(&apiGbIfIndex);

      gbInterfaceTableApiBuff.dummyIndex = 1; /*key */
      gbInterfaceTableApiBuff.oprState= 1;
      gbInterfaceTableApiBuff.nsei= 1;
      gbInterfaceTableApiBuff.maxNumNsvcs= 1;
      gbInterfaceTableApiBuff.maxNumLeps= 1;
      gbInterfaceTableApiBuff.maxNumReps= 1;
      gbInterfaceTableApiBuff.transportType= 1;

      insertGbInterfaceTable(&gbInterfaceTableApiBuff);

      /* Send GbInterfaceTable Update Request - with with out of range Parameters */
      gbInterfaceTableApiBuff.nsei= 67232;

      printf("\n cfgCmDbHndlr79: GbInterfaceTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&gbInterfaceTableApiBuff, sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr79: CM_FAILURE: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr79: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr79: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr79: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr79*/

/* Start of cfgCmDbHndlr80 */
void cfgCmDbHndlr80()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   GbInterfaceTableApi gbInterfaceTableApiBuff = {0};

   GbInterfaceTableIndices apiGbIfIndex = {0};
   apiGbIfIndex.dummyIndex = 1;

   if ( testInitiation )
   {         
      testInitiation=0;
      printf("\n cfgCmDbHndlr80: GbInterfaceTable Update Request - Same parameter values as in DB, ");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr80: setDbForBss Failed");
         return ;
      }
      /*deleting the row ,if already exist...*/
      deleteGbInterfaceTable(&apiGbIfIndex);


      gbInterfaceTableApiBuff.dummyIndex = 1; /*key */
      gbInterfaceTableApiBuff.oprState= 1;
      gbInterfaceTableApiBuff.nsei= 1;
      gbInterfaceTableApiBuff.maxNumNsvcs= 1;
      gbInterfaceTableApiBuff.maxNumLeps= 1;
      gbInterfaceTableApiBuff.maxNumReps= 1;
      gbInterfaceTableApiBuff.transportType= 1;

      insertGbInterfaceTable(&gbInterfaceTableApiBuff);

      /* Send GbInterfaceTable Update Request -Same parameter values as in DB */

      printf("\n cfgCmDbHndlr80: GbInterfaceTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&gbInterfaceTableApiBuff, sizeof(GbInterfaceTableApi),BSC_API_SET_GBINTERFACETABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr80: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr80: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr80: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr80: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr80*/

/* start of cfgCmDbHndlr81 */
void cfgCmDbHndlr81()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   NsvcTableApi nsvcTableApiBuff = {0};
   NsvcTableIndices apiNsvcIndex = {0};


   if ( testInitiation )
   {
      testInitiation=0; 
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr81: setDbForBss Failed");
         return ;
      }

      /*Deleting the row if already exist*/
      apiNsvcIndex.nsvcId=1;
      /* apiNsvcIndex.frIndex=16;*/
      deleteNsvcTable(&apiNsvcIndex);

      nsvcTableApiBuff.nsvcId = 1; /*key */
      nsvcTableApiBuff.frIndex= 16; /*key */

      printf("\n cfgCmDbHndlr81: NsvcTableUpdate Request - with params not in DB, sending");
      cfgStubSendCmMessage(&nsvcTableApiBuff, sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr81: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr81: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr81: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr81: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr81*/

/* start of cfgCmDbHndlr82 */
void cfgCmDbHndlr82()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   NsvcTableApi nsvcTableApiBuff = {0};
   NsvcTableIndices apiNsvcIndex = {0};

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr82: param Update Request - Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr82: setDbForBss Failed");
         return ;
      }
      /*Deleting the row if already exist*/
      apiNsvcIndex.nsvcId=1;
      /*apiNsvcIndex.frIndex=1;*/
      deleteNsvcTable(&apiNsvcIndex);


      nsvcTableApiBuff.nsvcId = 1; /*key */
      nsvcTableApiBuff.frIndex= 16; /*key */
      nsvcTableApiBuff.oprState= 1;

      insertNsvcTable(&nsvcTableApiBuff);

      /* Send NsvcTable Update Request - Parameter Modified Msg  */
      nsvcTableApiBuff.oprState= 2;

      printf("\n cfgCmDbHndlr82: NsvcTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&nsvcTableApiBuff, sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr82: CM_SUCCESS: Should not come");
                  printf("In cfgCmDbHndlr82: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr82: Returned NAK as RO parameter modification was sent");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr82: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr82*/

/* Start of cfgCmDbHndlr83 */
void cfgCmDbHndlr83()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   NsvcTableApi nsvcTableApiBuff = {0};
   NsvcTableIndices apiNsvcIndex = {0};

   if ( testInitiation )
   {     
      testInitiation=0;         
      printf("\n cfgCmDbHndlr83: NsvcTable Update Request - Param Mod Out of range Msg");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr83: setDbForBss Failed");
         return ;
      }
      /*Deleting the row if already exist*/
      apiNsvcIndex.nsvcId=1;
      /*apiNsvcIndex.frIndex=1;*/
      deleteNsvcTable(&apiNsvcIndex);

      nsvcTableApiBuff.nsvcId = 1; /*key */
      nsvcTableApiBuff.frIndex= 16; /*key*/ 

      insertNsvcTable(&nsvcTableApiBuff);

      /* Send NsvcTable Update Request - with out of range Parameters */
      nsvcTableApiBuff.frIndex= 1; /*key*/ 

      printf("\n cfgCmDbHndlr83: NsvcTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&nsvcTableApiBuff, sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr83: CM_FAILURE: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr83: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr83: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr83: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr83*/

/* Start of cfgCmDbHndlr84 */
void cfgCmDbHndlr84()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   NsvcTableApi nsvcTableApiBuff = {0};

   NsvcTableIndices apiNsvcIndex = {0};

   if ( testInitiation )
   {
      testInitiation=0;
      printf("\n cfgCmDbHndlr84: NsvcTable Update Request - Same parameter values as in DB");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr84: setDbForBss Failed");
         return ;
      }

      /*Deleting the row if already exist*/
      apiNsvcIndex.nsvcId=1;
      /* apiNsvcIndex.frIndex=16; */
      deleteNsvcTable(&apiNsvcIndex);

      nsvcTableApiBuff.nsvcId = 1; /*key */
      nsvcTableApiBuff.frIndex= 16; /*key */
      insertNsvcTable(&nsvcTableApiBuff);

      /* Send NsvcTable Table Update Request -Same parameter values as in DB */

      printf("\n cfgCmDbHndlr84: NsvcTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&nsvcTableApiBuff, sizeof(NsvcTableApi),BSC_API_SET_NSVCTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr84: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr84: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr84: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr84: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr84*/

/* start of cfgCmDbHndlr85 */
void cfgCmDbHndlr85()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   FrLinkTableApi frLinkTableApiBuff = {0};
   FrLinkTableIndices apiFrLinkIndex ={0};

   if ( testInitiation )
   {
      testInitiation=0;
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr85: setDbForBss Failed");
         return ;
      }

      /*delete row, if already exist..*/
      //apiFrLinkIndex.frIndex=17;
      deleteFrLinkTable(&apiFrLinkIndex) ;

      /* Send params Update Request - with params not in DB */
      frLinkTableApiBuff.frIndex= 17; /*key */
      frLinkTableApiBuff.priority= 1;
      frLinkTableApiBuff.e1= 1;
      frLinkTableApiBuff.ts= 1;
      frLinkTableApiBuff.oprState= 1;

      printf("\n cfgCmDbHndlr85: FrLinkTable Request - with params not in DB, sending");
      cfgStubSendCmMessage(&frLinkTableApiBuff, sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr85: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr85: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr85: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr85: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr85*/

/* start of cfgCmDbHndlr86 */
void cfgCmDbHndlr86()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   FrLinkTableApi frLinkTableApiBuff = {0};
   FrLinkTableIndices apiFrLinkIndex ={0};


   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr86: param Update Request - Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr86: setDbForBss Failed");
         return ;
      }
      /*delete row, if already exist..*/
      //apiFrLinkIndex.frIndex=17;
      deleteFrLinkTable(&apiFrLinkIndex) ;

      frLinkTableApiBuff.frIndex= 17; /*key */
      frLinkTableApiBuff.priority= 1;
      frLinkTableApiBuff.e1= 1;
      frLinkTableApiBuff.ts= 1;

      insertFrLinkTable(&frLinkTableApiBuff);

      /* Send FrLinkTable Update Request - Parameter Modified Msg  */
      frLinkTableApiBuff.priority= 3;

      printf("\n cfgCmDbHndlr86: FrLinkTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&frLinkTableApiBuff, sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr86: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr86: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr86: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr86: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr86*/

/* Start of cfgCmDbHndlr87 */
void cfgCmDbHndlr87()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   FrLinkTableApi frLinkTableApiBuff = {0};
   FrLinkTableIndices apiFrLinkIndex ={0};

   if ( testInitiation )
   {
      testInitiation=0;
      printf("\n cfgCmDbHndlr87: FrLinkTable Update Request - Param Mod Out of range Msg");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr87: setDbForBss Failed");
         return ;
      }
      /*delete row, if already exist..*/
      //apiFrLinkIndex.frIndex=17;
      deleteFrLinkTable(&apiFrLinkIndex) ;

      frLinkTableApiBuff.frIndex= 17; /*key */
      frLinkTableApiBuff.priority= 1;
      frLinkTableApiBuff.e1= 1;
      frLinkTableApiBuff.ts= 1;
      frLinkTableApiBuff.oprState= 1;

      insertFrLinkTable(&frLinkTableApiBuff);

      /* Send FrLinkTable Update Request - with out of range Parameters */
      frLinkTableApiBuff.frIndex= 1; /*key */

      printf("\n cfgCmDbHndlr87: FrLinkTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&frLinkTableApiBuff, sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr87: CM_FAILURE: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr87: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr87: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr87: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr87*/

/* Start of cfgCmDbHndlr88 */
void cfgCmDbHndlr88()
{
   static int testInitiation =1;
   I_S32 errCode = 0;
   FrLinkTableApi frLinkTableApiBuff = {0};

   FrLinkTableIndices apiFrLinkIndex ={0};

   if ( testInitiation )
   {
      testInitiation=0;    
      printf("\n cfgCmDbHndlr88: FrLinkTable Update Request - Same parameter values as in DB");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr88: setDbForBss Failed");
         return ;
      }
      /*delete row, if already exist..*/
      //apiFrLinkIndex.frIndex=17;
      deleteFrLinkTable(&apiFrLinkIndex) ;


      frLinkTableApiBuff.frIndex= 17; /*key */
      frLinkTableApiBuff.priority= 1;
      frLinkTableApiBuff.e1= 1;
      frLinkTableApiBuff.ts= 1;

      insertFrLinkTable(&frLinkTableApiBuff);

      /* Send FrLinkTable Table Update Request -Same parameter values as in DB */

      printf("\n cfgCmDbHndlr88: FrLinkTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&frLinkTableApiBuff, sizeof(FrLinkTableApi),BSC_API_SET_FRLINKTABLE );
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr88: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr88: Success\n");
               } 
               else
               {
                  printf("\n cfgCmDbHndlr88: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr88: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr88*/

/* start of cfgCmDbHndlr89 */
void cfgCmDbHndlr89()
{
   static int testInitiation =1;
   PcuTableApi pcuTblApiBuff = {0};
   PcuTableIndices pcuTableIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr89: PcuTable Update Request - with entry not in DB- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr89: setDbForBss Failed");
         return ;
      }
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

      printf("\n cfgCmDbHndlr89: PcuTable Update Request - with entry not in DB, Sending");
      cfgStubSendCmMessage(&pcuTblApiBuff, sizeof(PcuTableApi),BSC_API_SET_PCUTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr89: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr89: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr89: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr89: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/
}
/* end of cfgCmDbHndlr89 */

/* start of cfgCmDbHndlr90 */
void cfgCmDbHndlr90()
{
   static int testInitiation =1;
   PcuTableApi pcuTblApiBuff = {0};
   PcuTableIndices pcuTableIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr90: PcuTable Update Request - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr90: setDbForBss Failed");
         return;
      }

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
         printf("\n cfgCmDbHndlr90: PcuTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      /* Send PcuTable Update Request - Parameter Modified Msg  */

      pcuTblApiBuff.numContiguousPdch= 2;

      printf("\n cfgCmDbHndlr90: PcuTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&pcuTblApiBuff, sizeof(PcuTableApi),BSC_API_SET_PCUTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr90: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr90: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr90: problem in handling, chk code");
               }

               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr90: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr90 */

/* Start of cfgCmDbHndlr91 */
void cfgCmDbHndlr91()
{
   static int testInitiation =1;
   PcuTableApi pcuTblApiBuff = {0};
   PcuTableIndices pcuTableIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr91: PCUTable Update Request - with out of range Parameters- Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr91: setDbForBss Failed");
         return;
      }

      pcuTableIndex.dummyIndex = 1;

      errCode = deletePcuTable(&pcuTableIndex);

      pcuTblApiBuff.dummyIndex= 1;
      //pcuTblApiBuff.rrbpFlag= 1;
      pcuTblApiBuff.tcVal = 4;
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
         printf("\n cfgCmDbHndlr91: PcuTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      /* Send PcuTable Update Request - with with out of range Parameters */
      //pcuTblApiBuff.rrbpFlag=3;

      printf("\n cfgCmDbHndlr91: PCUTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&pcuTblApiBuff, sizeof(PcuTableApi),BSC_API_SET_PCUTABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr91: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr91: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr91: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr91: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr91 */

/* Start of cfgCmDbHndlr92 */
void cfgCmDbHndlr92()
{
   static int testInitiation =1;
   PcuTableApi pcuTblApiBuff = {0};
   PcuTableIndices pcuTableIndex = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr92: PCUTable Update Request - Same parameter values as in DB- Initiation");      
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr92: setDbForBss Failed");
         return;
      }

      pcuTableIndex.dummyIndex = 1;

      errCode = deletePcuTable(&pcuTableIndex);

      //pcuTblApiBuff.rrbpFlag= 1;
      pcuTblApiBuff.dummyIndex= 1;
      pcuTblApiBuff.tcVal = 4;
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
         printf("\n cfgCmDbHndlr92: PcuTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      printf("\n cfgCmDbHndlr92: PCUTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&pcuTblApiBuff, sizeof(PcuTableApi),BSC_API_SET_PCUTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr92: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr92: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr92: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr92: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr92 */

/* start of cfgCmDbHndlr93 */
void cfgCmDbHndlr93()
{
   static int testInitiation =1;
   LepInfoTableApi lepInfoTblApiBuff = {0};
   LepInfoTableIndices lepInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation=0; 
      printf("\n cfgCmDbHndlr93: LepInfoTable Update Request - with lep and lepPort not in DB");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr93: setDbForBss Failed");
         return ;
      }

      lepInfoTableIndices.lep=1;

      errCode = deleteLepInfoTable(&lepInfoTableIndices);

      /* Send LepInfoTable Update Request - with lep and lepPort not in DB */
      lepInfoTblApiBuff.lep = 1; /*key */
      lepInfoTblApiBuff.lepPort = 1;
      lepInfoTblApiBuff.signallingWt= 1;
      lepInfoTblApiBuff.dataWt= 1;

      printf("\n cfgCmDbHndlr93: LepInfoTable Update Request - with lep and lepPort not in DB, sending");
      cfgStubSendCmMessage(&lepInfoTblApiBuff, sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr93: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr93: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr93: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr93: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr93 */

/* start of cfgCmDbHndlr94 */
void cfgCmDbHndlr94()
{
   static int testInitiation =1;
   LepInfoTableApi lepInfoTblApiBuff = {0};
   LepInfoTableIndices lepInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr94: LepInfoTable Update Request - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr94: setDbForBss Failed");
         return;
      }

      lepInfoTableIndices.lep=1;

      errCode = deleteLepInfoTable(&lepInfoTableIndices);

      lepInfoTblApiBuff.lep = 1; /*key */
      lepInfoTblApiBuff.lepPort = 1;
      lepInfoTblApiBuff.signallingWt= 1;
      lepInfoTblApiBuff.dataWt= 1;

      if(CLIB_SUCCESS != insertLepInfoTable(&lepInfoTblApiBuff))
      {
         printf("\n cfgCmDbHndlr94: PcuTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      /* Send LepInfoTable Update Request - Parameter Modified Msg  */
      lepInfoTblApiBuff.lepPort = 55;

      printf("\n cfgCmDbHndlr94: LepInfoTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&lepInfoTblApiBuff, sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr94: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr94: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr94: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr94: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/
}
/* end of cfgCmDbHndlr94 */

/* Start of cfgCmDbHndlr95 */
void cfgCmDbHndlr95()
{
   static int testInitiation =1;
   LepInfoTableApi lepInfoTblApiBuff = {0};
   LepInfoTableIndices lepInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr95: PcuTable set Request- Out of range Param");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr95: setDbForBss Failed");
         return;
      }

      lepInfoTableIndices.lep=1;

      errCode = deleteLepInfoTable(&lepInfoTableIndices);

      lepInfoTblApiBuff.lep = 1; /*key */
      lepInfoTblApiBuff.lepPort = 1;
      lepInfoTblApiBuff.signallingWt= 1;
      lepInfoTblApiBuff.dataWt= 1;

      if(CLIB_SUCCESS != insertLepInfoTable(&lepInfoTblApiBuff))
      {
         printf("\n cfgCmDbHndlr95: Lep  set Request- Out of range Param, Insertion failed");
         return;
      }

      /* Send LepInfoTable Update Request - with with out of range Parameters */

      lepInfoTblApiBuff.ipType= 3;
      printf("\n cfgCmDbHndlr95: LepInfoTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&lepInfoTblApiBuff, sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr95: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr95: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr95: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr95: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr95 */

/* Start of cfgCmDbHndlr96 */
void cfgCmDbHndlr96()
{
   static int testInitiation =1;
   LepInfoTableApi lepInfoTblApiBuff = {0};
   LepInfoTableIndices lepInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation=0;  
      printf("\n cfgCmDbHndlr96: LepInfoTable Update Request - Same parameter values as in DB");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr96: setDbForBss Failed");
         return;
      }

      lepInfoTableIndices.lep=1;

      errCode = deleteLepInfoTable(&lepInfoTableIndices);

      lepInfoTblApiBuff.lep= 1; /*key */
      lepInfoTblApiBuff.lepPort = 1;
      lepInfoTblApiBuff.signallingWt= 1;
      lepInfoTblApiBuff.dataWt= 1;

      if(CLIB_SUCCESS != insertLepInfoTable(&lepInfoTblApiBuff))
      {
         printf("\n cfgCmDbHndlr96: LepInfoTable Update Request - Same parameter values as in DB, Insertion failed");
         return;
      }

      /* Send LepInfoTable Update Request -Same parameter values as in DB */
      printf("\n cfgCmDbHndlr96: LepInfoTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&lepInfoTblApiBuff, sizeof(LepInfoTableApi),BSC_API_SET_LEPINFOTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr96: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr96: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr96: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr96: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr96 */

/* start ofcfgCmDbHndlr97 */
void cfgCmDbHndlr97()
{
   static int testInitiation =1;
   RepInfoTableApi repInfoTblApiBuff = {0};
   RepInfoTableIndices repInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   { 
      testInitiation=0;
      printf("\ncfgCmDbHndlr97: RepInfoTable Update Request - with entry not in DB");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\ncfgCmDbHndlr97: setDbForBss Failed");
         return ;
      }

      repInfoTableIndices.rep=1;

      errCode = deleteRepInfoTable(&repInfoTableIndices);

      /* Send RepInfoTable Update Request - with rep and repPort not in DB */
      repInfoTblApiBuff.rep = 1; /*key */
      repInfoTblApiBuff.repPort = 1;
      repInfoTblApiBuff.signallingWt= 1;
      repInfoTblApiBuff.dataWt= 1;
      repInfoTblApiBuff.ipType= 0;

      printf("\ncfgCmDbHndlr97: RepInfoTable Update Request - with entry not in DB, sending");
      cfgStubSendCmMessage(&repInfoTblApiBuff, sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\ncfgCmDbHndlr97: CM_SUCCESS: Successfully handled- Row added");
                  printf("IncfgCmDbHndlr97: Success\n");
               }
               else
               {
                  printf("\ncfgCmDbHndlr97: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n IncfgCmDbHndlr97: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end ofcfgCmDbHndlr97 */

/* start of cfgCmDbHndlr98 */
void cfgCmDbHndlr98()
{
   static int testInitiation =1;
   RepInfoTableApi repInfoTblApiBuff = {0};
   RepInfoTableIndices repInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr98: RepInfoTable Update Request - Initiation");

      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr98: setDbForBss Failed");
         return;
      }

      repInfoTableIndices.rep=1;

      errCode = deleteRepInfoTable(&repInfoTableIndices);

      repInfoTblApiBuff.rep = 1; /*key */
      repInfoTblApiBuff.repPort = 1;
      repInfoTblApiBuff.signallingWt= 1;
      repInfoTblApiBuff.dataWt= 1;

      if(CLIB_SUCCESS != insertRepInfoTable(&repInfoTblApiBuff))
      {
         printf("\n cfgCmDbHndlr98: RepINfo set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      /* Send RepInfoTable Update Request - Parameter Modified Msg  */
      repInfoTblApiBuff.repPort = 2;

      printf("\n cfgCmDbHndlr98: RepInfoTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&repInfoTblApiBuff, sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr98: CM_SUCCESS: Successfully handled");
                  printf("In cfgCmDbHndlr98: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr98: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr98: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/
}
/* end of cfgCmDbHndlr98 */

/* Start of cfgCmDbHndlr99 */
void cfgCmDbHndlr99()
{
   static int testInitiation =1;
   RepInfoTableApi repInfoTblApiBuff = {0};
   RepInfoTableIndices repInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation=0; 
      printf("\n cfgCmDbHndlr99: RepInfoTable Update Request -Param Mod Out of range Msg");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr99: setDbForBss Failed");
         return;
      }

      repInfoTableIndices.rep=1;

      errCode = deleteRepInfoTable(&repInfoTableIndices);

      repInfoTblApiBuff.rep = 1; /*key */
      repInfoTblApiBuff.repPort = 1;
      repInfoTblApiBuff.signallingWt= 1;
      repInfoTblApiBuff.dataWt= 1;

      if(CLIB_SUCCESS != insertRepInfoTable(&repInfoTblApiBuff))
      {
         printf("\n cfgCmDbHndlr99: RepINfoTable set Request-Out of Range Param Msg, Insertion Failed");
         return;
      }

      /* Send RepInfoTable Update Request - with with out of range Parameters */
      repInfoTblApiBuff.ipType=3;

      printf("\n cfgCmDbHndlr99: RepInfoTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&repInfoTblApiBuff, sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr99: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr99: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr99: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr99: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr99 */

/* Start of cfgCmDbHndlr100 */
void cfgCmDbHndlr100()
{
   static int testInitiation =1;
   RepInfoTableApi repInfoTblApiBuff = {0};
   RepInfoTableIndices repInfoTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation=0; 
      printf("\n cfgCmDbHndlr100: RepInfoTable Update Request - Same parameter values as in DB");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr100: setDbForBss Failed");
         return;
      }

      repInfoTableIndices.rep=1;
      errCode = deleteRepInfoTable(&repInfoTableIndices);

      repInfoTblApiBuff.rep = 1; /*key */
      repInfoTblApiBuff.repPort = 1;
      repInfoTblApiBuff.signallingWt= 1;
      repInfoTblApiBuff.dataWt= 1;

      if(CLIB_SUCCESS != insertRepInfoTable(&repInfoTblApiBuff))
      {
         printf("\n cfgCmDbHndlr100: RepInfoTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      /* Send RepInfoTable Update Request -Same parameter values as in DB */
      printf("\n cfgCmDbHndlr100: RepInfoTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&repInfoTblApiBuff, sizeof(RepInfoTableApi),BSC_API_SET_REPINFOTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr100: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr100: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr100: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr100: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/
}
/* end of cfgCmDbHndlr100 */

/* start of cfgCmDbHndlr101 */
void cfgCmDbHndlr101()
{
   static int testInitiation =1;
   RlcMacConfigTableApi rlcMacConfigTblApiBuff = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr101: RlcMacConfigTable Update Request - with entry not in DB- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr101: setDbForBss Failed");
         return ;
      }

      /* Send RlcMacConfigTable Update Request - with dlPktPollGap and ulPktAckGap not in DB */
      rlcMacConfigTblApiBuff.dummyIndex= 1; /*key */
      rlcMacConfigTblApiBuff.dlPktPollGap = 1;
      rlcMacConfigTblApiBuff.ulPktAckGap= 1;
      rlcMacConfigTblApiBuff.ulChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.ulChanCodePar7= 1;
      rlcMacConfigTblApiBuff.dlChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.dlChanCodePar7= 1;

      printf("\n cfgCmDbHndlr101: RlcMacConfigTable Update Request - with dlPktPollGap and ulPktAckGap not in DB, sending");
      cfgStubSendCmMessage(&rlcMacConfigTblApiBuff, sizeof(RlcMacConfigTableApi),BSC_API_SET_RLCMACCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr101: CM_SUCCESS: Successfully handled- Row added");
                  printf("In cfgCmDbHndlr101: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr101: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr101: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/
}
/* end of cfgCmDbHndlr101 */

/* start of cfgCmDbHndlr102 */
void cfgCmDbHndlr102()
{
   static int testInitiation =1;
   RlcMacConfigTableApi rlcMacConfigTblApiBuff = {0};
   RlcMacConfigTableIndices rlcMacConfigTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr102: RlcMacConfigTable Update Request - Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr102: setDbForBss Failed");
         return;
      }

      rlcMacConfigTableIndices.dummyIndex = 1;

      errCode = deleteRlcMacConfigTable(&rlcMacConfigTableIndices);

      /* Send RlcMacConfigTable Update Request - with entry not in DB */
      rlcMacConfigTblApiBuff.dummyIndex= 1; /*key */
      rlcMacConfigTblApiBuff.dlPktPollGap = 1;
      rlcMacConfigTblApiBuff.ulPktAckGap= 1;
      rlcMacConfigTblApiBuff.ulChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.ulChanCodePar7= 1;
      rlcMacConfigTblApiBuff.dlChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.dlChanCodePar7= 1;

      if(CLIB_SUCCESS != insertRlcMacConfigTable(&rlcMacConfigTblApiBuff))
      {
         printf("\n cfgCmDbHndlr102: RlcMacInfoTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      /* Send RlcMacConfigTable Update Request - Parameter Modified Msg  */
      rlcMacConfigTblApiBuff.dlPktPollGap = 5;

      printf("\n cfgCmDbHndlr102: RlcMacConfigTable Update Request - Sending Parameter Modified Msg ");
      cfgStubSendCmMessage(&rlcMacConfigTblApiBuff, sizeof(RlcMacConfigTableApi),BSC_API_SET_RLCMACCONFIGTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr102: CM_SUCCESS: Successfully handled");                                  
                  printf("In cfgCmDbHndlr102: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr102: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr102: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr102*/

/* Start of cfgCmDbHndlr103 */
void cfgCmDbHndlr103()
{
   static int testInitiation =1;
   RlcMacConfigTableApi rlcMacConfigTblApiBuff = {0};
   RlcMacConfigTableIndices rlcMacConfigTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr103: RlcMacConfigTable Update Request - with out of range Parameters- Initiation");
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr103: setDbForBss Failed");
         return;
      }

      rlcMacConfigTableIndices.dummyIndex=1;
      errCode = deleteRlcMacConfigTable(&rlcMacConfigTableIndices);

      rlcMacConfigTblApiBuff.dummyIndex= 1; /*key */
      rlcMacConfigTblApiBuff.dlPktPollGap = 1;
      rlcMacConfigTblApiBuff.ulPktAckGap= 1;
      rlcMacConfigTblApiBuff.ulChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.ulChanCodePar7= 1;
      rlcMacConfigTblApiBuff.dlChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.dlChanCodePar7= 1;

      if(CLIB_SUCCESS != insertRlcMacConfigTable(&rlcMacConfigTblApiBuff))
      {
         printf("\n cfgCmDbHndlr103: RlcMacInfoTable set Request-Out of range Msg, Insertion Failed");
         return;
      }

      /* Send RlcMacConfigTable Update Request - with with out of range Parameters */
      rlcMacConfigTblApiBuff.dlPktPollGap = 64;

      printf("\n cfgCmDbHndlr103: RlcMacConfigTable Update Request -Sending Param Mod Out of range Msg");
      cfgStubSendCmMessage(&rlcMacConfigTblApiBuff, sizeof(RlcMacConfigTableApi),BSC_API_SET_RLCMACCONFIGTABLE);
   } /* End of test Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr103: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr103: Success\n");
               } 
               else
               {
                  printf("\n cfgCmDbHndlr103: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr103: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/* end of cfgCmDbHndlr103*/

/* Start of cfgCmDbHndlr104 */
void cfgCmDbHndlr104()
{
   static int testInitiation =1;
   RlcMacConfigTableApi rlcMacConfigTblApiBuff = {0};
   RlcMacConfigTableIndices rlcMacConfigTableIndices = {0};
   I_S32 errCode = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr104: RlcMacConfigTable Update Request - Same parameter values as in DB- Initiation");      
      /* First set the BSS - precondition */
      errCode = setDbForBss();

      if (errCode != CLIB_SUCCESS)
      {
         printf("\n cfgCmDbHndlr104: setDbForBss Failed");
         return;
      }

      rlcMacConfigTableIndices.dummyIndex=1; 
      errCode   = deleteRlcMacConfigTable(&rlcMacConfigTableIndices);

      /* Send RlcMacConfigTable Update Request -Same parameter values as in DB */
      rlcMacConfigTableIndices.dummyIndex=1; 
      rlcMacConfigTblApiBuff.dummyIndex= 1; /*key */
      rlcMacConfigTblApiBuff.dlPktPollGap = 1;
      rlcMacConfigTblApiBuff.ulPktAckGap= 1;
      rlcMacConfigTblApiBuff.ulChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.ulChanCodePar7= 1;
      rlcMacConfigTblApiBuff.dlChanCodeAdj= 1;
      rlcMacConfigTblApiBuff.dlChanCodePar7= 1;

      if(CLIB_SUCCESS != insertRlcMacConfigTable(&rlcMacConfigTblApiBuff))
      {
         printf("\n cfgCmDbHndlr104: RlcMacInfoTable set Request-Param Modified Msg, Insertion Failed");
         return;
      }

      printf("\n cfgCmDbHndlr104: RlcMacConfigTable Update Request - Same parameter values as in DB, sending");
      cfgStubSendCmMessage(&rlcMacConfigTblApiBuff, sizeof(RlcMacConfigTableApi),BSC_API_SET_RLCMACCONFIGTABLE);
   }/* End of Initiation */
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status != CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr104: CM_FAILURE: Successfully handled");
                  printf("In cfgCmDbHndlr104: Success\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr104: problem in handling, chk code");
               }         
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr104: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
   }/* end of Else-Execution Part*/

}
/******************** Testcase for new requirements *************/


void cfgCmDbHndlr180()
{
   static int testInitiation =1;

   SysOmcRegisterTableApi SysOmcRegisterTableApiBuff= {0};
   SysOmcRegisterTableIndices apiOmcRegIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr180: Inserting row in SYSOMCREG table with SYSOMCREGId not in DB- Initiation\n");

      apiOmcRegIndex.sysOmcIndex[0] =  20;

      ret = deleteSysOmcRegisterTable(&apiOmcRegIndex);

      /* Send SYSOMCREG Update Request - with SYSOMCREGId not in DB for SYSOMCREG */
      SysOmcRegisterTableApiBuff.sysOmcIndex[0] = 20; 
      SysOmcRegisterTableApiBuff.sysOmcRegisterprofileId[0] = 1; 

      printf("\n cfgCmDbHndlr180: SYSOMCREG Update Request- with SYSOMCREGId not in DB sending");
      cfgStubSendCmMessage(&SysOmcRegisterTableApiBuff,sizeof(SysOmcRegisterTableApi),BSC_API_SET_SYSOMCREGISTERTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr180: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr180: Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr180: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr180: Failed \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr180: Msg Discarded ");
            }
      } /* end of Switch */

      gTestCaseCompleted = 1;
      printf("In cfgCmDbHndlr180: Success\n");
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr180 */

void cfgCmDbHndlr181()
{
   static int testInitiation =1;

   SysOmcRegisterTableApi SysOmcRegisterTableApiBuff= {0};
   SysOmcRegisterTableIndices apiOmcRegIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr181: Inserting row in SYSOMCREG table with SYSOMCREGId not in DB- Initiation\n");

      apiOmcRegIndex.sysOmcIndex[0] =  20;

      ret = deleteSysOmcRegisterTable(&apiOmcRegIndex);

      /* Send SYSOMCREG Update Request - with SYSOMCREGId not in DB for SYSOMCREG */
      SysOmcRegisterTableApiBuff.sysOmcIndex[0] = 20; 
      SysOmcRegisterTableApiBuff.sysOmcRegisterprofileId[0] = 1; 


      ret = insertSysOmcRegisterTable(&SysOmcRegisterTableApiBuff);
      /* Change the parameter */
      SysOmcRegisterTableApiBuff.sysOmcRegisterprofileId[0] = 2; 

      printf("\n cfgCmDbHndlr181: SYSOMCREG Update Request- with SYSOMCREGId not in DB sending");
      cfgStubSendCmMessage(&SysOmcRegisterTableApiBuff,sizeof(SysOmcRegisterTableApi),BSC_API_SET_SYSOMCREGISTERTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr181: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr181: Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr181: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr181: Failed \n");
               }          
               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr181: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr181 */

void cfgCmDbHndlr182()
{
   static int testInitiation =1;

   SysOmcRegisterTableApi SysOmcRegisterTableApiBuff= {0};
   SysOmcRegisterTableIndices apiOmcRegIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr182: Inserting row in SYSOMCREG table with SYSOMCREGId not in DB- Initiation\n");

      apiOmcRegIndex.sysOmcIndex[0] =  20;

      ret = deleteSysOmcRegisterTable(&apiOmcRegIndex);

      /* Send SYSOMCREG Update Request - with SYSOMCREGId not in DB for SYSOMCREG */
      SysOmcRegisterTableApiBuff.sysOmcIndex[0] = 20; 
      SysOmcRegisterTableApiBuff.sysOmcRegisterprofileId[0] = 1; 


      ret = insertSysOmcRegisterTable(&SysOmcRegisterTableApiBuff);
      /* Don't Change the parameter */
      /* SysOmcRegisterTableApiBuff.sysOmcRegisterprofileId[0] = 2;  */

      printf("\n cfgCmDbHndlr182: SYSOMCREG Update Request- with SYSOMCREGId not in DB sending");
      cfgStubSendCmMessage(&SysOmcRegisterTableApiBuff,sizeof(SysOmcRegisterTableApi),BSC_API_SET_SYSOMCREGISTERTABLE);
   }
   else /* Execution Of Test Case */
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE :
            {
               if (((sCmMsg*)gCfgMsgBuf)->cmHdr.status == CM_SUCCESS)
               {
                  printf("\n cfgCmDbHndlr182: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr182: Failed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr182: PASSED \n");
               }          
               gTestCaseCompleted = 1;
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr182: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr182 */

void cfgCmDbHndlr183()
{
   static int testInitiation =1;

   SysOmcConfigTableApi SysOmcConfigTableApiBuff= {0};
   SysOmcConfigTableIndices apiOmcCfgIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr183: Inserting row in SYSOMCCFG table with SYSOMCCFGId not in DB- Initiation\n");

      apiOmcCfgIndex.sysOmcConfigactiveCardHwId[0] =  20;

      ret = deleteSysOmcConfigTable(&apiOmcCfgIndex);

      /* Send SYSOMCCFG Update Request - with SYSOMCCFGId not in DB for SYSOMCCFG */
      SysOmcConfigTableApiBuff.sysOmcConfigactiveCardHwId[0] = 20; 
      SysOmcConfigTableApiBuff.sysOmcConfignumOfE1c[0] = 1; 

      printf("\n cfgCmDbHndlr183: SYSOMCCFG Update Request- with SYSOMCCFGId not in DB sending");
      cfgStubSendCmMessage(&SysOmcConfigTableApiBuff,sizeof(SysOmcConfigTableApi),BSC_API_SET_SYSOMCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr183: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr183: Passed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr183: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr183: Failed \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr183: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr183 */

void cfgCmDbHndlr184()
{
   static int testInitiation =1;

   SysOmcConfigTableApi SysOmcConfigTableApiBuff= {0};
   SysOmcConfigTableIndices apiOmcCfgIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr184: Inserting row in SYSOMCCFG table with SYSOMCCFGId not in DB- Initiation\n");

      apiOmcCfgIndex.sysOmcConfigactiveCardHwId[0] =  20;

      ret = deleteSysOmcConfigTable(&apiOmcCfgIndex);

      /* Send SYSOMCCFG Update Request - with SYSOMCCFGId not in DB for SYSOMCCFG */
      SysOmcConfigTableApiBuff.sysOmcConfigactiveCardHwId[0] = 20; 
      SysOmcConfigTableApiBuff.sysOmcConfignumOfE1c[0] = 1; 

      ret = insertSysOmcConfigTable(&SysOmcConfigTableApiBuff);
      /* Modify the value */
      SysOmcConfigTableApiBuff.sysOmcConfignumOfE1c[0] = 2; 

      printf("\n cfgCmDbHndlr184: SYSOMCCFG Update Request- with SYSOMCCFGId not in DB sending");
      cfgStubSendCmMessage(&SysOmcConfigTableApiBuff,sizeof(SysOmcConfigTableApi),BSC_API_SET_SYSOMCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr184: Successfully handled- Row added");
                  printf("\n cfgCmDbHndlr184: Passed\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr184: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr184: Failed\n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr184: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr184 */

void cfgCmDbHndlr185()
{
   static int testInitiation =1;

   SysOmcConfigTableApi SysOmcConfigTableApiBuff= {0};
   SysOmcConfigTableIndices apiOmcCfgIndex = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr185: Inserting row in SYSOMCCFG table with SYSOMCCFGId not in DB- Initiation\n");

      apiOmcCfgIndex.sysOmcConfigactiveCardHwId[0] =  20;

      ret = deleteSysOmcConfigTable(&apiOmcCfgIndex);

      /* Send SYSOMCCFG Update Request - with SYSOMCCFGId not in DB for SYSOMCCFG */
      SysOmcConfigTableApiBuff.sysOmcConfigactiveCardHwId[0] = 20; 
      SysOmcConfigTableApiBuff.sysOmcConfignumOfE1c[0] = 1; 

      ret = insertSysOmcConfigTable(&SysOmcConfigTableApiBuff);
      /* DOn't modify the value */
      /* SysOmcConfigTableApiBuff.sysOmcConfignumOfE1c[0] = 2; */
      printf("\n cfgCmDbHndlr185: SYSOMCCFG Update Request- with SYSOMCCFGId not in DB sending");
      cfgStubSendCmMessage(&SysOmcConfigTableApiBuff,sizeof(SysOmcConfigTableApi),BSC_API_SET_SYSOMCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr185: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr185: Failed\n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr185: PASSED \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr185: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr185 */

void cfgCmDbHndlr186()
{
   static int testInitiation =1;

   PtdcConfigTableApi PtdcConfigTableApiBuff= {0};
   PtdcConfigTableIndices PtdcConfigTableIndicesBuff = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr186: Inserting row in PdtcConfig table with PdtcConfigId not in DB- Initiation\n");

      PtdcConfigTableIndicesBuff.ptdcCfgCfgIndex =  1;

      setDbForBss();

      ret = deletePtdcConfigTable(&PtdcConfigTableIndicesBuff);

      /* Send PdtcConfig Update Request - with PdtcConfigId not in DB for PdtcConfig */
      PtdcConfigTableApiBuff.ptdcCfgCfgIndex =  1;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 600; 
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicPSAppTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSStackTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicPSStackTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicPlatformTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCERTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicTraceTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicAlarmTimer=600;
      //PtdcConfigTableApiBuff.pdcCfgCERFileMaxSize=600 ;

      /*ret = insertPtdcConfigTable(&PtdcConfigTableIndicesBuff); */
      /* DOn't modify the value */
      /* PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 601; */
      printf("\n cfgCmDbHndlr186: PdtcConfig Update Request- with PdtcConfigId not in DB sending");
      cfgStubSendCmMessage(&PtdcConfigTableApiBuff,sizeof(PtdcConfigTableApi),BSC_API_SET_PTDCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr186: PASSED \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr186: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr186: Failed \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr186: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr186 */

void cfgCmDbHndlr187()
{
   static int testInitiation =1;

   PtdcConfigTableApi PtdcConfigTableApiBuff= {0};
   PtdcConfigTableIndices PtdcConfigTableIndicesBuff = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr187: Inserting row in PdtcConfig table with PdtcConfigId not in DB- Initiation\n");

      PtdcConfigTableIndicesBuff.ptdcCfgCfgIndex =  1;

      setDbForBss();

      ret = deletePtdcConfigTable(&PtdcConfigTableIndicesBuff);

      /* Send PdtcConfig Update Request - with PdtcConfigId not in DB for PdtcConfig */
      PtdcConfigTableApiBuff.ptdcCfgCfgIndex =  1;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 600; 
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 600; 
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicPSAppTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSStackTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicPSStackTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicPlatformTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCERTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicTraceTimer=600;
      PtdcConfigTableApiBuff.pdcCfgPeriodicAlarmTimer=600;
      //PtdcConfigTableApiBuff.pdcCfgCERFileMaxSize=600 ;

      ret = insertPtdcConfigTable(&PtdcConfigTableApiBuff); 
      /*  modify the value */
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 601; 
      printf("\n cfgCmDbHndlr187: PdtcConfig Update Request- with PdtcConfigId not in DB sending");
      cfgStubSendCmMessage(&PtdcConfigTableApiBuff,sizeof(PtdcConfigTableApi),BSC_API_SET_PTDCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr187: PASSED \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr187: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr187: Failed \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr187: Msg Discarded ");
            }
      } /* end of Switch */

      printf("In cfgCmDbHndlr187: Success\n");
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr187 */

void cfgCmDbHndlr188()
{
   static int testInitiation =1;

   PtdcConfigTableApi PtdcConfigTableApiBuff= {0};
   PtdcConfigTableIndices PtdcConfigTableIndicesBuff = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr188: Inserting row in PdtcConfig table with PdtcConfigId not in DB- Initiation\n");

      PtdcConfigTableIndicesBuff.ptdcCfgCfgIndex =  1;

      setDbForBss();

      ret = deletePtdcConfigTable(&PtdcConfigTableIndicesBuff);

      /* Send PdtcConfig Update Request - with PdtcConfigId not in DB for PdtcConfig */
      PtdcConfigTableApiBuff.ptdcCfgCfgIndex =  1;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 600; 

      ret = insertPtdcConfigTable(&PtdcConfigTableApiBuff); 
      /*  Don't modify the value */
      /* PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 601; */
      printf("\n cfgCmDbHndlr188: PdtcConfig Update Request- with PdtcConfigId not in DB sending");
      cfgStubSendCmMessage(&PtdcConfigTableApiBuff,sizeof(PtdcConfigTableApi),BSC_API_SET_PTDCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr188: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr188: Failed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr188: PASSED \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr188: Msg Discarded ");
            }
      } /* end of Switch */

      printf("In cfgCmDbHndlr188: Success\n");
   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr188 */

void cfgCmDbHndlr189()
{
   static int testInitiation =1;

   PtdcConfigTableApi PtdcConfigTableApiBuff= {0};
   PtdcConfigTableIndices PtdcConfigTableIndicesBuff = {0};
   I_S32 ret = 0;

   if ( testInitiation )
   {
      testInitiation =0;
      printf("\n cfgCmDbHndlr189: Inserting row in PdtcConfig table with PdtcConfigId not in DB- Initiation\n");

      PtdcConfigTableIndicesBuff.ptdcCfgCfgIndex =  1;

      setDbForBss();

      ret = deletePtdcConfigTable(&PtdcConfigTableIndicesBuff);

      /* Send PdtcConfig Update Request - with PdtcConfigId not in DB for PdtcConfig */
      PtdcConfigTableApiBuff.ptdcCfgCfgIndex =  1;
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 600; 

      ret = insertPtdcConfigTable(&PtdcConfigTableApiBuff); 
      /* Send out of range value  */
      PtdcConfigTableApiBuff.pdcCfgPeriodicCSAppTimer = 2000; 
      printf("\n cfgCmDbHndlr189: PdtcConfig Update Request- with PdtcConfigId not in DB sending");
      cfgStubSendCmMessage(&PtdcConfigTableApiBuff,sizeof(PtdcConfigTableApi),BSC_API_SET_PTDCCONFIGTABLE);
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
                  printf("\n cfgCmDbHndlr189: problem in handling, chk code");
                  printf("\n cfgCmDbHndlr189: Failed \n");
               }
               else
               {
                  printf("\n cfgCmDbHndlr189: PASSED \n");
               }          
               break;   
            }    /* end of case CM_API_APP_RESPONSE */       
         default:
            {
               printf("\n In cfgCmDbHndlr189: Msg Discarded ");
            }
      } /* end of Switch */

   }/* end of Else-Execution Part*/

}/* end of cfgCmDbHndlr189 */
