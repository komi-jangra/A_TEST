#include <oamscfg_includes.h>
#include <cfg_stub_sw_upgrade_handler.h>

#define DESTINATION ENT_OAMS_CFG
#define MAX_GROUP_ID 4
#define MAX_TEST_CASES 100
void cfgStubFrmwrkInit();
void populateCfgDb();
typedef  void (*swUpgradeTestCaseFunc)();
swUpgradeTestCaseFunc swUpTestCase[MAX_GROUP_ID][MAX_TEST_CASES] = {
   {
      CfgTrauHndlr1,
      CfgTrauHndlr2,
      CfgTrauHndlr3,
      CfgTrauHndlr4,
      CfgTrauHndlr5,
      CfgTrauHndlr6
   }, 
   {
      NULL,
      CfgSwUpgradeInit2,
      CfgSwUpgradeInit3, 
      CfgSwUpgradeInit4, 
      CfgSwUpgradeInit5
   }, 
   {
      CfgSwUpgradeHndlr1,
      CfgSwUpgradeHndlr2,
      CfgSwUpgradeHndlr3,
      CfgSwUpgradeHndlr4,
      CfgSwUpgradeHndlr5,
      CfgSwUpgradeHndlr6,
      CfgSwUpgradeHndlr7,
      CfgSwUpgradeHndlr8,
      CfgSwUpgradeHndlr9,
      CfgSwUpgradeHndlr10,
      CfgSwUpgradeHndlr11,
      CfgSwUpgradeHndlr12,
      CfgSwUpgradeHndlr13,
      CfgSwUpgradeHndlr14,
      CfgSwUpgradeHndlr15,
      CfgSwUpgradeHndlr16,
      CfgSwUpgradeHndlr17,
      CfgSwUpgradeHndlr18,
      CfgSwUpgradeHndlr19,
      CfgSwUpgradeHndlr20,
      CfgSwUpgradeHndlr21,
      CfgSwUpgradeHndlr22,
      CfgSwUpgradeHndlr23,
      CfgSwUpgradeHndlr24,
      CfgSwUpgradeHndlr25,
      CfgSwUpgradeHndlr26,
      CfgSwUpgradeHndlr27,
      CfgSwUpgradeHndlr28,
      CfgSwUpgradeHndlr29,
      CfgSwUpgradeHndlr30,
      CfgSwUpgradeHndlr31,
      CfgSwUpgradeHndlr32,
      CfgSwUpgradeHndlr33,
      CfgSwUpgradeHndlr34,
      CfgSwUpgradeHndlr35,
      CfgSwUpgradeHndlr36,
      CfgSwUpgradeHndlr37,
      CfgSwUpgradeHndlr38,
      CfgSwUpgradeHndlr39,
      CfgSwUpgradeHndlr40,
      CfgSwUpgradeHndlr41, 
      CfgSwUpgradeHndlr42, 
      CfgSwUpgradeHndlr43, 
      CfgSwUpgradeHndlr44, 
      CfgSwUpgradeHndlr45, 
      CfgSwUpgradeHndlr46, 
      CfgSwUpgradeHndlr47, 
      CfgSwUpgradeHndlr48, 
      CfgSwUpgradeHndlr49, 
      CfgSwUpgradeHndlr50, 
      CfgSwUpgradeHndlr51,  
      CfgSwUpgradeHndlr52,  
      CfgSwUpgradeHndlr53,  
      CfgSwUpgradeHndlr54,  
      CfgSwUpgradeHndlr55,  
      CfgSwUpgradeHndlr56,  
      CfgSwUpgradeHndlr57,  
      CfgSwUpgradeHndlr58,  
      CfgSwUpgradeHndlr59,  
      CfgSwUpgradeHndlr60,  
      CfgSwUpgradeHndlr61,  
      CfgSwUpgradeHndlr62,  
      CfgSwUpgradeHndlr63,  
      CfgSwUpgradeHndlr64,  
      CfgSwUpgradeHndlr65,  
      CfgSwUpgradeHndlr66,   
      CfgSwUpgradeHndlr67,   
      CfgSwUpgradeHndlr68,   
      CfgSwUpgradeHndlr69,   
      CfgSwUpgradeHndlr70,   
      CfgSwUpgradeHndlr71,   
      CfgSwUpgradeHndlr72,   
      CfgSwUpgradeHndlr73,   
      CfgSwUpgradeHndlr74,   
      CfgSwUpgradeHndlr75,    
      CfgSwUpgradeHndlr76,    
      CfgSwUpgradeHndlr77,    
      CfgSwUpgradeHndlr78,    
      CfgSwUpgradeHndlr79,    
      CfgSwUpgradeHndlr80,    
      CfgSwUpgradeHndlr81,    
      CfgSwUpgradeHndlr82,    
      CfgSwUpgradeHndlr83,    
      CfgSwUpgradeHndlr84,    
      CfgSwUpgradeHndlr85,    
      CfgSwUpgradeHndlr86,     
      CfgSwUpgradeHndlr87,     
      CfgSwUpgradeHndlr88,     
      CfgSwUpgradeHndlr89,     
      CfgSwUpgradeHndlr90,     
      CfgSwUpgradeHndlr91,     
      CfgSwUpgradeHndlr92,     
      CfgSwUpgradeHndlr93,     
      CfgSwUpgradeHndlr94,     
      CfgSwUpgradeHndlr95,     
      CfgSwUpgradeHndlr96,     
      CfgSwUpgradeHndlr97,     
      CfgSwUpgradeHndlr98     
   },
   {
      CfgHandOverHndlr1,
      CfgHandOverHndlr2,
      CfgHandOverHndlr3,
      CfgHandOverHndlr4,
      CfgHandOverHndlr5,
      CfgHandOverHndlr6,
      CfgHandOverHndlr7,
      CfgHandOverHndlr8,
      CfgHandOverHndlr9,
      CfgHandOverHndlr10,
      CfgHandOverHndlr11,
      CfgHandOverHndlr12,
      CfgHandOverHndlr13,
      CfgHandOverHndlr14,
      CfgHandOverHndlr15,
      CfgHandOverHndlr16,
      CfgHandOverHndlr17,
      CfgHandOverHndlr18,
      CfgHandOverHndlr19,
      CfgHandOverHndlr20,
      CfgHandOverHndlr21,
      CfgHandOverHndlr22,
      CfgHandOverHndlr23,
      CfgHandOverHndlr24,
      CfgHandOverHndlr25,
      CfgHandOverHndlr26,
      CfgHandOverHndlr27,
      CfgHandOverHndlr28,
      CfgHandOverHndlr29,
      CfgHandOverHndlr30,
      CfgHandOverHndlr31,
      CfgHandOverHndlr32
   }
};

int gSrcId =36;  //55;      /* SrcId for the CFG */
void *gCfgMsgBuf;   /* Message Pointer for the received message */
unsigned int gRcvMsgSize;  /* received message size */
int gTestCaseCompleted =0;

void main()
{
   char  testCaseOptonString[80];
   int testCaseNum;
   int testCaseGroupId;
   printf("Before DBInit \n");
   //cfgDbInit();
   printf("%d",dbConnect());
   printf("After DBInit \n");
   cfgStubFrmwrkInit();  /*register with the IPC Framework.. */
   printf("Before Populating DB \n");
   populateCfgDb(); 
   printf("After Populating DB \n");
   printf("\n**********CFG UNIT TEST CASE EXECUTION FOR CS3.0************\n");
	 while(1)
	 {
   printf("  Enter TestGrpId   : ");
   scanf("%d",&testCaseGroupId);
   //scanf("%s",testCaseOptonString);
   //testCaseGroupId=atoi(testCaseOptonString);
   printf("\n Please Enter Test Case Number to be executed : ");
   scanf( "%d",&testCaseNum);
   //cfgStubSendCmMessage(NULL,0,CFG_RESET);
   if (  (*swUpTestCase[testCaseGroupId-1][testCaseNum-1]) == NULL )
   {
      printf("\n Test case Does not exits \n");
      return;
   }

   for (;;)
   {
      LOG_PRINT(LOG_INFO,"\n cleaning  the  message queue....");
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRcvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         break;
      }
      LOG_PRINT(LOG_INFO,"\n Message recieved msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRcvMsgSize);
      DalocMsgBuf((I_Void *)gCfgMsgBuf);
   }

   (*swUpTestCase[testCaseGroupId-1][testCaseNum-1])();
   gTestCaseCompleted =0;
   /* receive messages */
   for (;;)
   {
      static I_U8 waitingFlag = 0;
      if (gTestCaseCompleted)
      {
         getchar();
         getchar();
         break;
      }
      /* receive message */
      gCfgMsgBuf = (void *)RecvMsg(gSrcId, &gRcvMsgSize); 
      if (gCfgMsgBuf == NULL)
      {
         if ( waitingFlag == 0 )
         {
            waitingFlag=1;
         }
         else
            fflush(NULL);
         continue; 
      }
      else
         LOG_PRINT(LOG_INFO,"\n Message recieved successfully from CFG msgType = %d of size = %d\n", (((SysHdr*) gCfgMsgBuf)->msgType),gRcvMsgSize);

      waitingFlag=0;
      (*swUpTestCase[testCaseGroupId-1][testCaseNum-1])();      
      DalocMsgBuf((I_Void *)gCfgMsgBuf);
   }
	 }
}

void cfgStubFrmwrkInit()
{
   I_U32 retVal;
   LOG_PRINT(LOG_INFO,"\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(gSrcId, "CFG_STUB");
   LOG_PRINT(LOG_INFO,"\nReturn Value of IPC Registration: %d\n",retVal);
   if (retVal < ZERO)
      cfgPanic(CFG_REGD_IPC_FAIL);
   LOG_PRINT(LOG_INFO,"\nCFG: Calling function cfgFrmwrkInit() Exiting");

} /* End of function cfgFrmwrkInit() */

I_S32 cfgStubSendCmMessage(void *buff, I_U32 size, I_U32 MessageType)
{
   sCmMsg* CmMsgPtr ;

   LOG_PRINT(LOG_INFO,"\n\t Calling cfgStubSendCmMessage().....");
   if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(size+sizeof(sCmMsg))) == NULL)
   {
      LOG_PRINT(LOG_INFO,"CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   CmMsgPtr->sHdr.msgType = MessageType;
   CmMsgPtr->sHdr.src.entity =gSrcId; 
   CmMsgPtr->sHdr.dest.entity = DESTINATION;
   CmMsgPtr->cmHdr.size = size;
   memcpy((((I_U8 *)CmMsgPtr)+sizeof(sCmMsg)),(I_U8*)buff,size);

   LOG_PRINT(LOG_INFO,"\n CmMsgPtr->sHdr.msgType = %d", CmMsgPtr->sHdr.msgType);
   LOG_PRINT(LOG_INFO,"\n CmMsgPtr->sHdr.src.entity = %d", CmMsgPtr->sHdr.src.entity);
   LOG_PRINT(LOG_INFO,"\n CmMsgPtr->sHdr.dest.entity = %d", CmMsgPtr->sHdr.dest.entity);

   LOG_PRINT(LOG_INFO,"\n Sending message ...........");

   if (SendMsg(CmMsgPtr, 1, (size+sizeof(sCmMsg))) < 0)
   {
      LOG_PRINT(LOG_INFO,"\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) CmMsgPtr);
      return(-1);
   }
   return(1);
}

I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;

   sndMsgSize = 0;

   LOG_PRINT(LOG_INFO,"\n\t Calling cfgStubSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      LOG_PRINT(LOG_INFO,"CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   sndPtr->src.entity = gSrcId;
   /* sndPtr->dest.entity = DestEntId;
   */
   sndPtr->dest.entity = DESTINATION;


   LOG_PRINT(LOG_INFO,"\n sndPtr->msgType = %d", sndPtr->msgType);
   LOG_PRINT(LOG_INFO,"\n sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   LOG_PRINT(LOG_INFO,"\n sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);

   LOG_PRINT(LOG_INFO,"\n Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      LOG_PRINT(LOG_INFO,"\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   return(1);
}

void cfgStubSendDSmmMgsuDriverInitStatus(I_U32 tsiStatus)
{
   DSmmMgsuDriverInitStatus DSmmMgsuDriverInitStatusBuff;
   DSmmMgsuDriverInitStatusBuff.messageId= MGS_TSM_TSI_DRIVER_INIT_STS;
   DSmmMgsuDriverInitStatusBuff.tsiStatus = tsiStatus;
   cfgStubSendMessage(&DSmmMgsuDriverInitStatusBuff,sizeof(DSmmMgsuDriverInitStatus),ENT_MGS_TSM, MGS_TSM_TSI_DRIVER_INIT_STS,0);

}

void cfgStubSendDTrauMgsuDriverInitStatus(I_U32 dspStatus)
{
   DTrauMgsuDriverInitStatus DTrauMgsuDriverInitStatusBuff;
   DTrauMgsuDriverInitStatusBuff.messageId=MGS_TRAU_DRIVER_INIT_STATUS;
   DTrauMgsuDriverInitStatusBuff.dspStatus = dspStatus;
   cfgStubSendMessage(&DTrauMgsuDriverInitStatusBuff,sizeof(DSmmMgsuDriverInitStatus),ENT_MGS_TSM, MGS_TRAU_DRIVER_INIT_STATUS,0);

}
void cfgStubSendDTrauMgsuTrauInitResp()
{
   DTrauMgsuTrauInitResp DTrauMgsuTrauInitRespBuff;
   DTrauMgsuTrauInitRespBuff.messageId=MGS_TRAU_INIT_RESP;
   cfgStubSendMessage(&DTrauMgsuTrauInitRespBuff,sizeof(DTrauMgsuTrauInitResp),ENT_MGS_TSM, MGS_TRAU_INIT_RESP,0);

}

void cfgPopulateTrauConfigTable()
{
   TrauConfigTableApi trauConfigTableBuff;
   trauConfigTableBuff.trauDspId = 1; 
   trauConfigTableBuff.trauCodingFormat = MGS_TRAU_MU_LAW;
   trauConfigTableBuff.trauNumSpeechChannels = 22;
   if(insertTrauConfigTable(&trauConfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertTrauConfigTable successfull");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertTrauConfigTable unsuccessfull");
   }

}
void addBssTable()
{
   BssTableApi  bssTableApiBuff;
   bssTableApiBuff.bscId =1;
   bssTableApiBuff.adminState = 0; /* Locked */   
   bssTableApiBuff.bssReset = FALSE;
   bssTableApiBuff.gprsEnabled =1;   
   bssTableApiBuff.callReestablishmentInd =  0;
   bssTableApiBuff.attInd = 0;
   bssTableApiBuff.t3212 = 20;
   bssTableApiBuff.mcc = 91;
   bssTableApiBuff.mnc = 91;
   bssTableApiBuff.ncc = 5;
   bssTableApiBuff.nccPermitted = 200;
   bssTableApiBuff.dtxDnLinkInd = 1;
   bssTableApiBuff.dtxUpLinkInd = 1;
   bssTableApiBuff.minChannelGap = 3;
   bssTableApiBuff.txInteger = 12;
   bssTableApiBuff.radioLinkTimeout = 6;
   bssTableApiBuff.maxRetrans = 2;
   bssTableApiBuff.shutdownTimer = 231;
   bssTableApiBuff.cicMaster = 1;       
   bssTableApiBuff.tHandRqd = 1;       

   if(insertBssTable(&bssTableApiBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBssTable : insertBssTable successfull");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBssTable : insertBssTable unsuccessfull");
   }
}

void addCellPerTable()
{
   CellPerTableApi cellPerTableBuff;
   cellPerTableBuff.lac = 3000;
   cellPerTableBuff.cellId = 3500;
   cellPerTableBuff.adminState = 0;
   cellPerTableBuff.antennaId = 100;
   cellPerTableBuff.bcchArfcn = 124;
   cellPerTableBuff.freqBandBcch = 0;
   cellPerTableBuff.bcc = 0;
   cellPerTableBuff.bcchPwr = 0;
   cellPerTableBuff.msTxPwrMax = 10;
   cellPerTableBuff.msTxPowerMaxCch = 10;
   cellPerTableBuff.fnOffset = 1;
   cellPerTableBuff.psStatus = 1;
   cellPerTableBuff.cellBarAccess = 1;
   cellPerTableBuff.accessCtrlClass = 30;
   cellPerTableBuff.bsAgBlksRes = 5;
   cellPerTableBuff.bsPaMfrms = 5;
   cellPerTableBuff.cellReselectHysteresis = 4;
   cellPerTableBuff.rxLevAccessMin = 63;
   cellPerTableBuff.powerOffset = 1;
   cellPerTableBuff.cbq = 0;
   cellPerTableBuff.cellReselectOffset = 1;
   cellPerTableBuff.tempOffset = 1;
   cellPerTableBuff.penalityTime = 3;
   if(insertCellPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addCellPerTable: insertCellPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addCellPerTable: insertCellPerTable unsuccessfull\n");
   }
}

void cfgDeleteCellPerTable()
{
   CellPerTableIndices cellPerTableBuff;
   cellPerTableBuff.lac = 3000;
   cellPerTableBuff.cellId = 3500;
   if(deleteCellPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgDeleteCellPerTable: deleteCellPerTable successfull  ");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addCellPerTable: insertCellPerTable unsuccessfull\n");
   }
}

void addBicTable()
{
   BicTableApi bicTableBuff;
   bicTableBuff.bicId = 101; 
   bicTableBuff.numTrx = 2;
   bicTableBuff.e1Id = 1;
   if(insertBicTable(&bicTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicTable : insertBicTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTable : insertBicTable unsuccessfull\n");
   }
}

void addTrxTable()
{
   TrxTableApi trxTableBuff; 
   trxTableBuff.ptrxId = 21;
   trxTableBuff.adminState = 0;
   trxTableBuff.trxLocation = 2; 
   trxTableBuff.bicId = 101;
   trxTableBuff.antennaID = 101;
   trxTableBuff.trxPos = 1;
   trxTableBuff.rfPathGain = 200;
   if(insertTrxTable(&trxTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable unsuccessfull\n");
   }

   trxTableBuff.ptrxId = 22;
   trxTableBuff.adminState = 0;
   trxTableBuff.trxLocation = 2; 
   trxTableBuff.bicId = 101;
   trxTableBuff.antennaID = 102;
   trxTableBuff.trxPos = 3;
   trxTableBuff.rfPathGain = 300;
   if(insertTrxTable(&trxTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable unsuccessfull\n");
   }

   trxTableBuff.ptrxId = 25;
   trxTableBuff.adminState = 0;
   trxTableBuff.trxLocation = 1; 
   trxTableBuff.bicId = 0;
   trxTableBuff.antennaID = 102;
   trxTableBuff.trxPos = 1;
   trxTableBuff.rfPathGain = 200;
   if(insertTrxTable(&trxTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable unsuccessfull\n");
   }

}

void addAbisE1TsMccE1TsMapTable()
{
   AbisE1TsMccE1TsMapTableApi abisE1TsMccE1TsMapTableBuff;
   abisE1TsMccE1TsMapTableBuff.abisE1Id = 1;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 1;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 2;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 7;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable unsuccessfull\n");
   }

   abisE1TsMccE1TsMapTableBuff.abisE1Id = 1;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 8;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable unsuccessfull\n");
   }

   abisE1TsMccE1TsMapTableBuff.abisE1Id = 2;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 4;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 8;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable unsuccessfull\n");
   }

   abisE1TsMccE1TsMapTableBuff.abisE1Id = 50;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 0;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 8;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable: insertAbisE1TsMccE1TsMapTable unsuccessfull\n");
   }

}

void addE1StreamMapTable()
{
   E1StreamMapTableApi e1StreamMapTableBuff;
   e1StreamMapTableBuff.e1Num = 2;  
   e1StreamMapTableBuff.e1Ts = 7;  
   e1StreamMapTableBuff.strmNum = 7;  
   e1StreamMapTableBuff.strmTs = 7;
   if(insertE1StreamMapTable(&e1StreamMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable unsuccessfull\n");
   }

   e1StreamMapTableBuff.e1Num = 3;  
   e1StreamMapTableBuff.e1Ts = 8;  
   e1StreamMapTableBuff.strmNum = 8;  
   e1StreamMapTableBuff.strmTs = 8;
   if(insertE1StreamMapTable(&e1StreamMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable unsuccessfull\n");
   }

}

void addLapdTEIConfigTable()
{
   LapdTEIConfigTableApi lapdTEIConfigTableBuff;   
   lapdTEIConfigTableBuff.lapdtimeslot = 7;
   lapdTEIConfigTableBuff.lapdTei = 1;
   lapdTEIConfigTableBuff.applTei = 30;
   if(insertLapdTEIConfigTable(&lapdTEIConfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable unsuccessfull\n");
   }

   lapdTEIConfigTableBuff.lapdtimeslot = 8;
   lapdTEIConfigTableBuff.lapdTei = 2;
   lapdTEIConfigTableBuff.applTei = 32;
   if(insertLapdTEIConfigTable(&lapdTEIConfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable unsuccessfull\n");
   }
}

void addTrxTsTeiTable()
{
   TrxTsTeiTableApi trxTsTeiTableBuff;
   trxTsTeiTableBuff.ptrxId = 21;
   trxTsTeiTableBuff.trxTei = 21;
   trxTsTeiTableBuff.e1Id = 1;
   trxTsTeiTableBuff.startTsTraffic = 3;
   trxTsTeiTableBuff.lapdTs = 0;
   trxTsTeiTableBuff.lapdLinkStatus = 1;
   if(insertTrxTsTeiTable(&trxTsTeiTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable unsuccessfull\n");
   }

   trxTsTeiTableBuff.ptrxId = 22;
   trxTsTeiTableBuff.trxTei = 21;
   trxTsTeiTableBuff.e1Id = 1;
   trxTsTeiTableBuff.startTsTraffic = 3;
   trxTsTeiTableBuff.lapdTs = 0;
   trxTsTeiTableBuff.lapdLinkStatus = 1;
   if(insertTrxTsTeiTable(&trxTsTeiTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable unsuccessfull\n");
   }
}

void addBicStatusTable()
{
   BicStatusTableApi bicStatusTableBuff;
   bicStatusTableBuff.bicId = 101;
   bicStatusTableBuff.connectionState = 1;
   bicStatusTableBuff.parentBicId = 0;
   bicStatusTableBuff.parentBicPortNum = 0;
   if(insertBicStatusTable(&bicStatusTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicStatusTable : insertBicStatusTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicStatusTable : insertBicStatusTable unsuccessfull\n");
   }
}

void addBicE1TeiMapTable()
{
   BicE1TeiMapTableApi bicE1TeiMapTableBuff;
   bicE1TeiMapTableBuff.bicTei = 30;
   bicE1TeiMapTableBuff.e1Id = 1;
   bicE1TeiMapTableBuff.e1Ts = 1;
   if(insertBicE1TeiMapTable(&bicE1TeiMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicE1TeiMapTable : insertBicE1TeiMapTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicE1TeiMapTable : insertBicE1TeiMapTable unsuccessfull\n");
   }
}

void addInFrameTrxE1TsTable()
{
   InFrameTrxE1TsTableApi inFrameTrxE1TsTableBuff;
   inFrameTrxE1TsTableBuff.trxPos = 1;
   inFrameTrxE1TsTableBuff.e1Id = 50;
   inFrameTrxE1TsTableBuff.startTs = 0;
   if(insertInFrameTrxE1TsTable(&inFrameTrxE1TsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable unsuccessfull\n");
   }
   inFrameTrxE1TsTableBuff.trxPos = 2;
   inFrameTrxE1TsTableBuff.e1Id = 50;
   inFrameTrxE1TsTableBuff.startTs = 0;
   if(insertInFrameTrxE1TsTable(&inFrameTrxE1TsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable unsuccessfull\n");
   }

   inFrameTrxE1TsTableBuff.trxPos = 3;
   inFrameTrxE1TsTableBuff.e1Id = 51;
   inFrameTrxE1TsTableBuff.startTs = 0;
   if(insertInFrameTrxE1TsTable(&inFrameTrxE1TsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable unsuccessfull\n");
   }
}

void addSwMPreconfigTable()
{
   SwMPreconfigTableApi swMPreconfigTableBuff;
   swMPreconfigTableBuff.dummyIndex = 0;
   /*   swMPreconfigTableBuff.maxBicSwDownloadsPerE1 = 1;
          swMPreconfigTableBuff.maxExternalTrxSwDownloadsPerE1 = 4;
          swMPreconfigTableBuff.maxBicAndExternalTrxDownloadsPerE1 = 4;
          swMPreconfigTableBuff.maxInternalTrxSwDownloads = 6; */
   swMPreconfigTableBuff.maxSwDownloadsPerSharedTs = 1;
   swMPreconfigTableBuff.maxSwDownloadsTotal = 2;
   swMPreconfigTableBuff.windowSizeLoadDataSeg = 10;
   swMPreconfigTableBuff.tLoadDataInitAck = 5;
   swMPreconfigTableBuff.tLoadDataSegAck = 5;
   swMPreconfigTableBuff.tLoadDataEndAck = 5;
   if(insertSwMPreconfigTable(&swMPreconfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addSwMPreconfigTable: insertSwMPreconfigTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addSwMPreconfigTable: insertSwMPreconfigTable unsuccessfull\n");
   }
}

void addCsPwrCtrlPreconfigTable()
{
   CsPwrCtrlPreconfigTableApi csPwrCtrlPreconfigTableBuff;
   csPwrCtrlPreconfigTableBuff.dummyIndex = 1;
   csPwrCtrlPreconfigTableBuff.windowSizeRxLevP = 2;
   csPwrCtrlPreconfigTableBuff.windowSizeRxQualP = 2;
   csPwrCtrlPreconfigTableBuff.incrStepSizeP = 2;
   csPwrCtrlPreconfigTableBuff.decrStepSizeP = 1;
   csPwrCtrlPreconfigTableBuff.safetyMarginP = 1;
   csPwrCtrlPreconfigTableBuff.tPcBlocked = 2;
   csPwrCtrlPreconfigTableBuff.epiSacchCount = 3;
   if(insertCsPwrCtrlPreconfigTable(&csPwrCtrlPreconfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addCsPwrCtrlPreconfigTable: insertCsPwrCtrlPreconfigTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addCsPwrCtrlPreconfigTable: insertCsPwrCtrlPreconfigTable unsuccessfull\n");
   }
}

void addHoCtrlPreconfigTable()
{
   HoCtrlPreconfigTableApi hoCtrlPreconfigTableBuff;
   hoCtrlPreconfigTableBuff.dummyIndex = 1;
   hoCtrlPreconfigTableBuff.maxRxLevVal = 63;
   hoCtrlPreconfigTableBuff.minRxLevVal = 0;
   hoCtrlPreconfigTableBuff.maxRxQualVal = 0;
   hoCtrlPreconfigTableBuff.fadingMargin = 4;
   hoCtrlPreconfigTableBuff.unsuccHoPenalty = 128;
   hoCtrlPreconfigTableBuff.tHandUnsucc = 10;  //0;
   hoCtrlPreconfigTableBuff.t3105Tch = 0x0A;
   hoCtrlPreconfigTableBuff.t3105Sdcch = 0x16;
   hoCtrlPreconfigTableBuff.ny1Tch = 2;
   hoCtrlPreconfigTableBuff.ny1Sdcch = 2;
   hoCtrlPreconfigTableBuff.tHoSeiz = 8;  //16;
   if(insertHoCtrlPreconfigTable(&hoCtrlPreconfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addHoCtrlPreconfigTable: insertHoCtrlPreconfigTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addHoCtrlPreconfigTable: insertHoCtrlPreconfigTable unsuccessfull\n");
   }
}

void addBssapTimerTable()
{
   BssapTimerTableApi bssapTimerTableBuff;
   bssapTimerTableBuff.bssapTimerT1 = 2;
   bssapTimerTableBuff.bssapTimerT4 = 4;
   //bssapTimerTableBuff.bssapTimerT7 = 10;
   //bssapTimerTableBuff.bssapTimerT8 = 15;
   bssapTimerTableBuff.bssapTimerT10 = 25;
   bssapTimerTableBuff.bssapTimerT11 = 5;
   bssapTimerTableBuff.bssapTimerT13 = 10;
   bssapTimerTableBuff.bssapTimerT17 = 5;
   bssapTimerTableBuff.bssapTimerT18 = 5;
   bssapTimerTableBuff.bssapTimerT19 = 5;
   bssapTimerTableBuff.bssapTimerT20 = 10;
   if(insertBssapTimerTable(&bssapTimerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBssapTimerTable: insertBssapTimerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBssapTimerTable: insertBssapTimerTable unsuccessfull\n");
   }
}

void addBicTrxTimeslotUsageTable()
{
   BicTrxTimeslotUsageTableApi bicTrxTimeslotUsageBuff;
   bicTrxTimeslotUsageBuff.tsUser = TS_USAGE_BIC;
   bicTrxTimeslotUsageBuff.bicOrTrxId = 101;
   bicTrxTimeslotUsageBuff.e1Id = 1;
   bicTrxTimeslotUsageBuff.startTs = 1;
   bicTrxTimeslotUsageBuff.numTs = 1;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable unsuccessfull\n");
   }

   bicTrxTimeslotUsageBuff.tsUser = TS_USAGE_BICTRX;
   bicTrxTimeslotUsageBuff.bicOrTrxId = 21;
   bicTrxTimeslotUsageBuff.e1Id = 1;
   bicTrxTimeslotUsageBuff.startTs = 1;
   bicTrxTimeslotUsageBuff.numTs = 3;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable unsuccessfull\n");
   }

   bicTrxTimeslotUsageBuff.tsUser = TS_USAGE_BICTRX;
   bicTrxTimeslotUsageBuff.bicOrTrxId = 22;
   bicTrxTimeslotUsageBuff.e1Id = 1;
   bicTrxTimeslotUsageBuff.startTs = 1;
   bicTrxTimeslotUsageBuff.numTs = 3;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable unsuccessfull\n");
   }
}

void addE1PerTable()
{
   E1PerTableApi e1PerTableBuff;
   e1PerTableBuff.e1Num = 1;
   e1PerTableBuff.adminState = 0;
   e1PerTableBuff.usageType = SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10;
   e1PerTableBuff.usingEntity = 0;
   if(insertE1PerTable(&e1PerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable unsuccessfull\n");
   }

   e1PerTableBuff.e1Num = 2;
   e1PerTableBuff.adminState = 0;
   e1PerTableBuff.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;
   e1PerTableBuff.usingEntity = 0;
   if(insertE1PerTable(&e1PerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable unsuccessfull\n");
   }

}

void addTimeSlotPerTable()
{
   TimeSlotPerTableApi timeSlotPerTableBuff;
   timeSlotPerTableBuff.e1Num = 1;
   timeSlotPerTableBuff.tsNum= 1;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_BIC;
   timeSlotPerTableBuff.usingEntity = 4;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable unsuccessfull\n");
   }

   timeSlotPerTableBuff.e1Num = 1;
   timeSlotPerTableBuff.tsNum= 3;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_BIC;
   timeSlotPerTableBuff.usingEntity = 4;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable unsuccessfull\n");
   }

   timeSlotPerTableBuff.e1Num = 1;
   timeSlotPerTableBuff.tsNum= 2;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_TRX;
   timeSlotPerTableBuff.usingEntity = 0;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable unsuccessfull\n");
   }

   timeSlotPerTableBuff.e1Num = 2;
   timeSlotPerTableBuff.tsNum= 2;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_TRX;
   timeSlotPerTableBuff.usingEntity = 0;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable unsuccessfull\n");
   }

   timeSlotPerTableBuff.e1Num = 2;
   timeSlotPerTableBuff.tsNum= 4;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_BIC;
   timeSlotPerTableBuff.usingEntity = 0;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable unsuccessfull\n");
   }

}

void addBicTrxTsTable()
{
   BicTrxTsTableApi bicTrxTsTableBuff;
   bicTrxTsTableBuff.trxPos = 1;
   bicTrxTsTableBuff.startTs = 1;
   if(insertBicTrxTsTable(&bicTrxTsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable unsuccessfull\n");
   }

   bicTrxTsTableBuff.trxPos = 2;
   bicTrxTsTableBuff.startTs = 2;
   if(insertBicTrxTsTable(&bicTrxTsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable unsuccessfull\n");
   }

   bicTrxTsTableBuff.trxPos = 3;
   bicTrxTsTableBuff.startTs = 3;
   if(insertBicTrxTsTable(&bicTrxTsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable unsuccessfull\n");
   }

}

void addTrauConfigTable()
{
   TrauConfigTableApi trauConfigTableBuff;
   trauConfigTableBuff.trauDspId = 0;
   trauConfigTableBuff.trauCodingFormat = 2;
   trauConfigTableBuff.trauNumSpeechChannels = 22;
   if(insertTrauConfigTable(&trauConfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertTrauConfigTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertTrauConfigTable unsuccessfull\n");
   }
}

void populateCfgDb()
{
   addBssTable();
   //addCellPerTable();
   addBicTable();
   addTrxTable();
   addTimeSlotPerTable();
   addAbisE1TsMccE1TsMapTable();
   addE1StreamMapTable();
   addLapdTEIConfigTable();
   addTrxTsTeiTable(); 
   addBicStatusTable();
   addBicE1TeiMapTable();
   addInFrameTrxE1TsTable();
   addSwMPreconfigTable();
   addCsPwrCtrlPreconfigTable();
   addHoCtrlPreconfigTable();
   addBssapTimerTable();
   addBicTrxTimeslotUsageTable();
   addE1PerTable();
   addBicTrxTsTable(); 
   addTrauConfigTable();
}
