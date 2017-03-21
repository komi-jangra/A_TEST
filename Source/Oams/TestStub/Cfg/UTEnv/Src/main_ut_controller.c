/***********************************File Header ***************************
File Name        : main_ut_controller.c
Purpose          : Implementation of the main controller. This is the main interface
                   for executing the testcases in automation methods.
Project          : BSC/UTE
Subsystem        : UTE
Author           : BB/VNL/Gurgaon
************************************* End **********************************/

#include <includes.h>

FILE *DBG_FILE_PTR;

I_U32 TEST_GROUP_ID, TEST_CASE_ID, TEST_RESULT,AUTO_MODE;
I_U8* msgRcvP = NULL;
  
I_S32 LogInit(I_Void)
{
	if ( !( DBG_FILE_PTR = fopen( DBG_FILE_NAME, "w+" ) ) )
	{
	  fprintf(stderr,"Opening Log file:%s failed ,error:%d ",DBG_FILE_NAME,errno);
		exit ( EXIT_FAILURE );
	}	      
  return (EXIT_SUCCESS);
}

I_S32 DbInit(I_Void)
{
  /* Connecting with EDBSERVER */
  if ( DBLIB_SUCCESS != dbConnect() )
  {
    LOG_PRINT(CRITICAL,"Unable to Connect with DB");
    exit(EXIT_FAILURE);
  }
  else
  {
    LOG_PRINT(INFO,"Connected with DB");
  }

  return (EXIT_SUCCESS);
}

I_S32 IpcFrmWrkInit(I_Void)
{
   if ( RegisterWithIpcFrmwrk(ENT_UTE_MC, "UTE_MC") < ZERO)  {
      LOG_PRINT(CRITICAL,"Unable to Register itself with IPC FrameWork");
      exit (EXIT_FAILURE);
   }
   else
   {
      LOG_PRINT(CRITICAL,"Register with IPC FrameWork OK");
   }
  return (EXIT_SUCCESS);
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
      LOG_PRINT(LOG_INFO,"addBssTable : insertBssTable OK");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBssTable : insertBssTable NOK");
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
      LOG_PRINT(LOG_INFO,"addCellPerTable: insertCellPerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addCellPerTable: insertCellPerTable NOK\n");
   }
}

void cfgDeleteCellPerTable()
{
   CellPerTableIndices cellPerTableBuff;
   cellPerTableBuff.lac = 3000;
   cellPerTableBuff.cellId = 3500;
   if(deleteCellPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"cfgDeleteCellPerTable: deleteCellPerTable OK  ");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addCellPerTable: insertCellPerTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addBicTable : insertBicTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTable : insertBicTable OK\n");
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
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable OK\n");
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
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTable : insertTrxTable NOK\n");
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
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable NOK\n");
   }

   abisE1TsMccE1TsMapTableBuff.abisE1Id = 1;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 8;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable NOK\n");
   }

   abisE1TsMccE1TsMapTableBuff.abisE1Id = 2;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 4;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 8;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable NOK\n");
   }

   abisE1TsMccE1TsMapTableBuff.abisE1Id = 50;
   abisE1TsMccE1TsMapTableBuff.abisE1Ts = 0;
   abisE1TsMccE1TsMapTableBuff.mccE1Id = 3;
   abisE1TsMccE1TsMapTableBuff.mccE1Ts = 8;
   if(insertAbisE1TsMccE1TsMapTable(&abisE1TsMccE1TsMapTableBuff) == CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addAbisE1TsMccE1TsMapTable:insertAbisE1TsMccE1TsMapTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable NOK\n");
   }

   e1StreamMapTableBuff.e1Num = 3;  
   e1StreamMapTableBuff.e1Ts = 8;  
   e1StreamMapTableBuff.strmNum = 8;  
   e1StreamMapTableBuff.strmTs = 8;
   if(insertE1StreamMapTable(&e1StreamMapTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1StreamMapTable: insertE1StreamMapTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable NOK\n");
   }

   lapdTEIConfigTableBuff.lapdtimeslot = 8;
   lapdTEIConfigTableBuff.lapdTei = 2;
   lapdTEIConfigTableBuff.applTei = 32;
   if(insertLapdTEIConfigTable(&lapdTEIConfigTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addLapdTEIConfigTable: insertLapdTEIConfigTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable NOK\n");
   }

   trxTsTeiTableBuff.ptrxId = 22;
   trxTsTeiTableBuff.trxTei = 21;
   trxTsTeiTableBuff.e1Id = 1;
   trxTsTeiTableBuff.startTsTraffic = 3;
   trxTsTeiTableBuff.lapdTs = 0;
   trxTsTeiTableBuff.lapdLinkStatus = 1;
   if(insertTrxTsTeiTable(&trxTsTeiTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTrxTsTeiTable : insertTrxTsTeiTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addBicStatusTable : insertBicStatusTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicStatusTable : insertBicStatusTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addBicE1TeiMapTable : insertBicE1TeiMapTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicE1TeiMapTable : insertBicE1TeiMapTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable NOK\n");
   }
   inFrameTrxE1TsTableBuff.trxPos = 2;
   inFrameTrxE1TsTableBuff.e1Id = 50;
   inFrameTrxE1TsTableBuff.startTs = 0;
   if(insertInFrameTrxE1TsTable(&inFrameTrxE1TsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable NOK\n");
   }

   inFrameTrxE1TsTableBuff.trxPos = 3;
   inFrameTrxE1TsTableBuff.e1Id = 51;
   inFrameTrxE1TsTableBuff.startTs = 0;
   if(insertInFrameTrxE1TsTable(&inFrameTrxE1TsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addInFrameTrxE1TsTable : insertInFrameTrxE1TsTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addSwMPreconfigTable: insertSwMPreconfigTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addSwMPreconfigTable: insertSwMPreconfigTable NOK\n");
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
    LOG_PRINT(LOG_INFO,"addCsPwrCtrlPreconfigTable:insertCsPwrCtrlPreconfigTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addCsPwrCtrlPreconfigTable:insertCsPwrCtrlPreconfigTable NOK\n");
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
    LOG_PRINT(LOG_INFO,"addHoCtrlPreconfigTable:insertHoCtrlPreconfigTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addHoCtrlPreconfigTable:insertHoCtrlPreconfigTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addBssapTimerTable:insertBssapTimerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBssapTimerTable:insertBssapTimerTable NOK\n");
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
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable:insertBicTrxTimeslotUsageTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable:insertBicTrxTimeslotUsageTable NOK\n");
   }

   bicTrxTimeslotUsageBuff.tsUser = TS_USAGE_BICTRX;
   bicTrxTimeslotUsageBuff.bicOrTrxId = 21;
   bicTrxTimeslotUsageBuff.e1Id = 1;
   bicTrxTimeslotUsageBuff.startTs = 1;
   bicTrxTimeslotUsageBuff.numTs = 3;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageBuff) == CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable:insertBicTrxTimeslotUsageTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable NOK\n");
   }

   bicTrxTimeslotUsageBuff.tsUser = TS_USAGE_BICTRX;
   bicTrxTimeslotUsageBuff.bicOrTrxId = 22;
   bicTrxTimeslotUsageBuff.e1Id = 1;
   bicTrxTimeslotUsageBuff.startTs = 1;
   bicTrxTimeslotUsageBuff.numTs = 3;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageBuff) == CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable:insertBicTrxTimeslotUsageTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable: insertBicTrxTimeslotUsageTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable NOK\n");
   }

   e1PerTableBuff.e1Num = 2;
   e1PerTableBuff.adminState = 0;
   e1PerTableBuff.usageType = SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4;
   e1PerTableBuff.usingEntity = 0;
   if(insertE1PerTable(&e1PerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable NOK\n");
   }

}
#if 0
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
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable NOK\n");
   }

   timeSlotPerTableBuff.e1Num = 1;
   timeSlotPerTableBuff.tsNum= 3;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_BIC;
   timeSlotPerTableBuff.usingEntity = 4;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable NOK\n");
   }

   timeSlotPerTableBuff.e1Num = 1;
   timeSlotPerTableBuff.tsNum= 2;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_TRX;
   timeSlotPerTableBuff.usingEntity = 0;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable NOK\n");
   }

   timeSlotPerTableBuff.e1Num = 2;
   timeSlotPerTableBuff.tsNum= 2;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_TRX;
   timeSlotPerTableBuff.usingEntity = 0;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable NOK\n");
   }

   timeSlotPerTableBuff.e1Num = 2;
   timeSlotPerTableBuff.tsNum= 4;
   timeSlotPerTableBuff.adminState = 0;
   timeSlotPerTableBuff.usageType = SYS_TS_USAGE_LAPD_BIC;
   timeSlotPerTableBuff.usingEntity = 0;
   if(insertTimeSlotPerTable(&timeSlotPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addTimeSlotPerTable: insertTimeSlotPerTable NOK\n");
   }

}
#endif
void addBicTrxTsTable()
{
   BicTrxTsTableApi bicTrxTsTableBuff;
   bicTrxTsTableBuff.trxPos = 1;
   bicTrxTsTableBuff.startTs = 1;
   if(insertBicTrxTsTable(&bicTrxTsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable NOK\n");
   }

   bicTrxTsTableBuff.trxPos = 2;
   bicTrxTsTableBuff.startTs = 2;
   if(insertBicTrxTsTable(&bicTrxTsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable NOK\n");
   }

   bicTrxTsTableBuff.trxPos = 3;
   bicTrxTsTableBuff.startTs = 3;
   if(insertBicTrxTsTable(&bicTrxTsTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertBicTrxTsTable NOK\n");
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
      LOG_PRINT(LOG_INFO,"insertTrauConfigTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertTrauConfigTable NOK\n");
   }
}

I_Void DbTableInit()
{
   addBssTable();
   addCellPerTable();
   addBicTable();
   addTrxTable();
   //addTimeSlotPerTable();
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

I_S32 LoggingInit(I_Void)
{
  SysAddr slfAddr;
  slfAddr.entity = ENT_UTE_MC;
  /*Initialize logging Utility*/
  if(InitLoggingUtility(slfAddr) < ZERO)
  {
      LOG_PRINT(CRITICAL,"InitLoggingUtility NOK");
      exit(EXIT_FAILURE);
  }    
  else 
  {
    LOG_PRINT(INFO,"InitLoggingUtility OK");
  }
  return (EXIT_SUCCESS);
}

I_Void Init(I_Void) 
{
  (I_Void)IpcFrmWrkInit();
  (I_Void)DbInit();  
  (I_Void)LoggingInit();
}

I_Void MainMenu(I_Void)
{
  if (AUTO_MODE) {
    return ;
  }
  printf("\nMain Menu");  
  printf("\nFollowing are the supported TEST GROUPS");
  printf("\n->%s [%d] : ",
         testGroupId2String(TEST_GROUP_CLK_SRC_CFG),
         TEST_GROUP_CLK_SRC_CFG
        );
  printf("\n->%s [%d] : ",
         testGroupId2String(TEST_GROUP_STK_SRC_CFG),
         TEST_GROUP_STK_SRC_CFG
        );       
  printf("\n->%s [%d] : ",
         testGroupId2String(TEST_GROUP_STK_ADDM_CFG),
         TEST_GROUP_STK_ADDM_CFG
        );       
  printf("\n->%s [%d] : ",
         testGroupId2String(TEST_GROUP_TP_USG_CHG_CFG),
         TEST_GROUP_TP_USG_CHG_CFG
        );
  printf("\n->%s [%d] : ",
         testGroupId2String(TEST_GROUP_TP_ADMN_CHG_CFG),
         TEST_GROUP_TP_ADMN_CHG_CFG
        );
  printf("\n->%s [%d] : ",
         testGroupId2String(TEST_GROUP_BIC_LOCK_UNLOCK_CFG),
         TEST_GROUP_BIC_LOCK_UNLOCK_CFG
        );   
  printf("\n->%s [%d] : ",
         testGroupId2String(ALL_TEST_GROUP),
         ALL_TEST_GROUP
        );
  printf("\n->EXIT UTE [%d] : ",
         EXIT_UTE
        );       
  return ;
}

I_Bool verifyTestGroup(I_U32 testGroupId)
{
  if (testGroupId > TEST_GROUP_START  && testGroupId < TEST_GROUP_END) {
    return TRUE;
  }
  if (ALL_TEST_GROUP == testGroupId ) {
    return TRUE;
  }
  if (EXIT_UTE == testGroupId ) {
    LOG_PRINT(INFO,"User Exists Normally");
    exit (EXIT_SUCCESS);
  }
  
  return FALSE;
}

I_U32 MainMenuInput()
{
  I_PU8 testGroupString = NULL;

  if (AUTO_MODE) {  
    return ALL_TEST_GROUP;
  }
  
  printf("\n<-Please Enter Your Choice :");
  scanf("%d",&TEST_GROUP_ID);
  if ( verifyTestGroup(TEST_GROUP_ID) ) {
    testGroupString = testGroupId2String(TEST_GROUP_ID);
    LOG_PRINT(INFO,"Selected TG [%s][%d]",
              testGroupString,
              TEST_GROUP_ID
             );
    return TEST_GROUP_ID;
  }
  else
  {
    system("clear");
    printf("\n[%d]That was Invalid Input, Try Again",TEST_GROUP_ID);   
    MainMenu();
    TEST_GROUP_ID = MainMenuInput();
  }

  return TEST_GROUP_ID;
}

I_Void SubMenu(I_U32 testGroup)
{
  I_U32 i;

  printf("\nSub Menu");  
  switch (testGroup) {
    case TEST_GROUP_CLK_SRC_CFG:
      printf("\nFollowing are supported TEST CASES for [%s]",
              testGroupId2String(testGroup)
            );
      for (i=TEST_CASE_CLK_SRC_CFG_START+1; i < TEST_CASE_CLK_SRC_CFG_END; i++) {
        printf("\n->%s [%d]",
               testCaseId2Description(testGroup,i), 
               i
              );        
      }   
      printf("\n->%s [%d]",
             testCaseId2Description(testGroup,TEST_CASE_CLK_SRC_CFG_ALL), 
             TEST_CASE_CLK_SRC_CFG_ALL
            );       
      printf("\n->EXIT UTE [%d]",
             EXIT_UTE
            );        
    break;  
    case TEST_GROUP_STK_SRC_CFG:
      printf("\nFollowing are supported TEST CASES for [%s]",
              testGroupId2String(testGroup)
            );
      for (i=TEST_CASE_STK_SRC_CFG_START+1; i < TEST_CASE_STK_SRC_CFG_END; i++) {
        printf("\n->%s [%d]",
               testCaseId2Description(testGroup,i), 
               i
              );        
      }   
      printf("\n->%s [%d]",
             testCaseId2Description(testGroup,TEST_CASE_STK_SRC_CFG_ALL), 
             TEST_CASE_STK_SRC_CFG_ALL
            );       
      printf("\n->EXIT UTE [%d]",
             EXIT_UTE
            );        
    break;     
    case TEST_GROUP_STK_ADDM_CFG:
      printf("\nFollowing are supported TEST CASES for [%s]",
              testGroupId2String(testGroup)
            );
      for (i=TEST_CASE_STK_ADDM_CFG_START+1; i < TEST_CASE_STK_ADDM_CFG_END; i++) {
        printf("\n->%s [%d]",
               testCaseId2Description(testGroup,i), 
               i
              );        
      }   
      printf("\n->%s [%d]",
             testCaseId2Description(testGroup,TEST_CASE_STK_ADDM_CFG_ALL), 
             TEST_CASE_STK_ADDM_CFG_ALL
            );       
      printf("\n->EXIT UTE [%d]",
             EXIT_UTE
            );        
    break; 
    case TEST_GROUP_TP_USG_CHG_CFG:
      printf("\nFollowing are supported TEST CASES for [%s]",
              testGroupId2String(testGroup)
            );
      for (i=TEST_CASE_TP_USG_CHG_CFG_START+1; i < TEST_CASE_TP_USG_CHG_CFG_END; i++) {
        printf("\n->%s [%d]",
               testCaseId2Description(testGroup,i), 
               i
              );        
      }   
      printf("\n->%s [%d]",
             testCaseId2Description(testGroup,TEST_CASE_TP_USG_CHG_CFG_ALL), 
             TEST_CASE_TP_USG_CHG_CFG_ALL
            );       
      printf("\n->EXIT UTE [%d]",
             EXIT_UTE
            );        
    break; 

    case TEST_GROUP_TP_ADMN_CHG_CFG:
      printf("\nFollowing are supported TEST CASES for [%s]",
              testGroupId2String(testGroup)
            );
      for (i=TEST_CASE_TP_ADMN_CHG_CFG_START+1; i < TEST_CASE_TP_ADMN_CHG_CFG_END; i++) {
        printf("\n->%s [%d]",
               testCaseId2Description(testGroup,i), 
               i
              );        
      }   
      printf("\n->%s [%d]",
             testCaseId2Description(testGroup,TEST_CASE_TP_ADMN_CHG_CFG_ALL), 
             TEST_CASE_TP_ADMN_CHG_CFG_ALL
            );       
      printf("\n->EXIT UTE [%d]",
             EXIT_UTE
            );        
    break; 
    case TEST_GROUP_BIC_LOCK_UNLOCK_CFG:
      printf("\nFollowing are supported TEST CASES for [%s]",
              testGroupId2String(testGroup)
            );
      for (i=TEST_CASE_BIC_LOCK_UNLOCK_CFG_START+1; i < TEST_CASE_BIC_LOCK_UNLOCK_CFG_END; i++) {
        printf("\n->%s [%d]",
               testCaseId2Description(testGroup,i), 
               i
              );        
      }   
      printf("\n->%s [%d]",
             testCaseId2Description(testGroup,TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL), 
             TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL
            );       
      printf("\n->EXIT UTE [%d]",
             EXIT_UTE
            );        
    break;
    default :;        
  }        
  return ; 
}

I_Bool verifyTestCase(I_U32 testGroupId, I_U32 testCaseId)
{
  if (EXIT_UTE == testCaseId ) {
    LOG_PRINT(INFO,"User Exists Normally");
    exit (EXIT_SUCCESS);
  }
  switch (testGroupId) {
    case TEST_GROUP_CLK_SRC_CFG:
      if (testCaseId > TEST_CASE_CLK_SRC_CFG_START  && 
          testCaseId < TEST_CASE_CLK_SRC_CFG_END) {
        return TRUE;
      }
      if (TEST_CASE_CLK_SRC_CFG_ALL == testCaseId ) {
        return TRUE;
      }      
      break;
    case TEST_GROUP_STK_SRC_CFG:
      if (testCaseId > TEST_CASE_STK_SRC_CFG_START  && 
          testCaseId < TEST_CASE_STK_SRC_CFG_END) {
        return TRUE;
      }
      if (TEST_CASE_STK_SRC_CFG_ALL == testCaseId ) {
        return TRUE;
      }      
      break;      
    case TEST_GROUP_STK_ADDM_CFG:
      if (testCaseId > TEST_CASE_STK_ADDM_CFG_START  && 
          testCaseId < TEST_CASE_STK_ADDM_CFG_END) {
        return TRUE;
      }
      if (TEST_CASE_STK_ADDM_CFG_ALL == testCaseId ) {
        return TRUE;
      }      
      break;      
    case TEST_GROUP_TP_USG_CHG_CFG:
      if (testCaseId > TEST_CASE_TP_USG_CHG_CFG_START  && 
          testCaseId < TEST_CASE_TP_USG_CHG_CFG_END) {
        return TRUE;
      }
      if (TEST_CASE_TP_USG_CHG_CFG_ALL == testCaseId ) {
        return TRUE;
      }      
      break;      
    case TEST_GROUP_TP_ADMN_CHG_CFG:
      if (testCaseId > TEST_CASE_TP_ADMN_CHG_CFG_START  && 
          testCaseId < TEST_CASE_TP_ADMN_CHG_CFG_END) {
        return TRUE;
      }
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL == testCaseId ) {
        return TRUE;
      }      
      break;      
     case TEST_GROUP_BIC_LOCK_UNLOCK_CFG:
      if (testCaseId > TEST_CASE_BIC_LOCK_UNLOCK_CFG_START  && 
          testCaseId < TEST_CASE_BIC_LOCK_UNLOCK_CFG_END) {
        return TRUE;
      }
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL == testCaseId ) {
        return TRUE;
      }      
      break;
     default: 
      LOG_PRINT(CRITICAL,"Impossible Case");
      exit (EXIT_FAILURE);
  }  
  return FALSE;
}

I_U32 SubMenuInput()
{
  I_PU8 testCaseString = NULL;

  printf("\n<-Please Enter Your Choice :");
  scanf("%d",&TEST_CASE_ID);
  if ( verifyTestCase(TEST_GROUP_ID,TEST_CASE_ID) ) {
    testCaseString = testCaseId2Description(TEST_GROUP_ID,TEST_CASE_ID); 
    LOG_PRINT(INFO,"Selected TC [%s][%d]",
              testCaseString,
              TEST_CASE_ID
             );
    return TEST_CASE_ID;
  }
  else
  {
    system("clear");
    printf("\n[%d]That was Invalid Input, Try Again",TEST_CASE_ID);   
    SubMenu(TEST_GROUP_ID);
    TEST_CASE_ID = SubMenuInput();
  }
  
  return TEST_CASE_ID;
}

I_S32 main(I_S32 argc , I_PU8 argv[]) 
{
  Init();
  system("clear");
  LOG_PRINT(CRITICAL,"UTE is UP");
  if (argc > 1) {
    if ( !strcmp(argv[1],"auto") ) {
      AUTO_MODE = 1;
      LOG_PRINT(CRITICAL,"AUTO MODE is select , Module Under Test is ENT->[%d] ",MUT);
    }
  }    
  if (MUT == ENT_OAMS_CFG) {
    LOG_PRINT(CRITICAL,"-----------------MUT CFG------------------");  
    TestCaseInitCfg();
    LOG_PRINT(CRITICAL,"-----------------CFG Init OK--------------");
  }
  while (TRUE)
  {
    MainMenu();
    TEST_GROUP_ID = MainMenuInput();
    switch (TEST_GROUP_ID) {
      case ALL_TEST_GROUP:
      case TEST_GROUP_CLK_SRC_CFG:
        TEST_GROUP_ID=TEST_GROUP_CLK_SRC_CFG;
        if (AUTO_MODE) {
          TEST_CASE_ID = TEST_CASE_CLK_SRC_CFG_ALL;
        }
        else {
          SubMenu(TEST_GROUP_CLK_SRC_CFG);
          TEST_CASE_ID = SubMenuInput();
        }
        ExecuteTestSuit(TEST_GROUP_ID,TEST_CASE_ID);        
        if (TEST_GROUP_CLK_SRC_CFG == TEST_GROUP_ID) {
          break;   
        }  
      case TEST_GROUP_STK_SRC_CFG:
        TEST_GROUP_ID=TEST_GROUP_STK_SRC_CFG;
        if (AUTO_MODE) {
          TEST_CASE_ID = TEST_CASE_STK_SRC_CFG_ALL;
        }
        else {
          SubMenu(TEST_GROUP_STK_SRC_CFG);
          TEST_CASE_ID = SubMenuInput();
        }
        ExecuteTestSuit(TEST_GROUP_ID,TEST_CASE_ID);        
        if (TEST_GROUP_STK_SRC_CFG == TEST_GROUP_ID) {
          break;   
        }
      case TEST_GROUP_STK_ADDM_CFG:
        TEST_GROUP_ID=TEST_GROUP_STK_ADDM_CFG;
        if (AUTO_MODE) {
          TEST_CASE_ID = TEST_CASE_STK_ADDM_CFG_ALL;
        }
        else {
          SubMenu(TEST_GROUP_STK_ADDM_CFG);
          TEST_CASE_ID = SubMenuInput();
        }
        ExecuteTestSuit(TEST_GROUP_ID,TEST_CASE_ID);        
        if (TEST_GROUP_STK_ADDM_CFG == TEST_GROUP_ID) {
          break;   
        }         
      case TEST_GROUP_TP_USG_CHG_CFG:
        TEST_GROUP_ID=TEST_GROUP_TP_USG_CHG_CFG;
        if (AUTO_MODE) {
          TEST_CASE_ID = TEST_CASE_TP_USG_CHG_CFG_ALL;
        }
        else {
          SubMenu(TEST_GROUP_TP_USG_CHG_CFG);
          TEST_CASE_ID = SubMenuInput();
        }
        ExecuteTestSuit(TEST_GROUP_ID,TEST_CASE_ID);        
        if (TEST_GROUP_TP_USG_CHG_CFG == TEST_GROUP_ID) {
          break;   
        }         
      case TEST_GROUP_TP_ADMN_CHG_CFG:
        TEST_GROUP_ID= TEST_GROUP_TP_ADMN_CHG_CFG;
        if (AUTO_MODE) {
          TEST_CASE_ID = TEST_CASE_TP_ADMN_CHG_CFG_ALL;
        }
        else {
          SubMenu(TEST_GROUP_TP_ADMN_CHG_CFG);
          TEST_CASE_ID = SubMenuInput();
        }
        ExecuteTestSuit(TEST_GROUP_ID,TEST_CASE_ID);        
        if (TEST_GROUP_TP_ADMN_CHG_CFG == TEST_GROUP_ID) {
          break;   
        }         
      case TEST_GROUP_BIC_LOCK_UNLOCK_CFG:
        TEST_GROUP_ID=TEST_GROUP_BIC_LOCK_UNLOCK_CFG;
        if (AUTO_MODE) {
          TEST_CASE_ID = TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL;
        }
        else {
          SubMenu(TEST_GROUP_BIC_LOCK_UNLOCK_CFG);
          TEST_CASE_ID = SubMenuInput();
        }
        ExecuteTestSuit(TEST_GROUP_ID,TEST_CASE_ID);        
        if (TEST_GROUP_BIC_LOCK_UNLOCK_CFG == TEST_GROUP_ID) {
          break;   
        }
    }
    if (AUTO_MODE) {
      exit(EXIT_SUCCESS);
    }
  }  
  // return(EXIT_SUCCESS); Control Never Returns here 
}
