#include <includes.h>

#if 0
I_Void addAbisInterfaceTable(I_U16 ifId, I_U32 bicId, I_U32 ifType)
{
  AbisInterfaceTableApi AbisInterfaceTableApiBuff = {ifId, bicId, "Abis Interface", ifType, UNLOCKED};

  if (CLIB_SUCCESS != insertAbisInterfaceTable( &AbisInterfaceTableApiBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAbisInterfaceTable Fail",__func__);  
  }
 
}
#endif
I_Void addSs7StackConfigTable(I_U32 opc, I_U32 family, I_U32 alarmLevel)
{
  Ss7StackConfigTableApi ss7StackConfigBufff = {1,opc, family, alarmLevel};

  if (CLIB_SUCCESS != insertSs7StackConfigTable( &ss7StackConfigBufff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7StackConfigTable Fail",__func__);  
  }
}

I_Void addAifInterfaceTable(I_U16 ifId,I_U32 ifType,I_U32 dpc,I_U32 tgpId)
{
  AifInterfaceTableApi AifInterfaceBuff = {ifId, "Aif Interface",ifType,dpc,tgpId,ENABLED,UNLOCKED };

  if (CLIB_SUCCESS != insertAifInterfaceTable( &AifInterfaceBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAifInterfaceTable Fail",__func__);  
  }
}

I_Void addLinksetTable(I_U16 linkSetId,I_U16 ifId,I_U32 apc,I_U32 ni)
{
  LinksetTableApi tableBuff = {linkSetId,"LinkSet",ifId, apc,ni,UNLOCKED };

  if (CLIB_SUCCESS != insertLinksetTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinksetTable Fail",__func__);  
  }
}

I_Void addLinkTable(I_U16 linkSetId,I_U16 linkId,I_U16 slc,I_U32 e1Num,I_U8 ts,I_U32 cardNum,I_U32 crcFlag,I_U32 adminState)
{
  LinkTableApi tableBuff = {linkSetId,linkId,slc,e1Num,ts,cardNum,crcFlag,adminState};

  if (CLIB_SUCCESS != insertLinkTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkTable Fail",__func__);  
  }
}

I_Void addTrunkTable(I_U16 interfaceId,I_U16 tgpId,I_U32 e1Num,I_U32 startCic,I_U32 endCic,I_U32 trunkType,I_U32 tsCicMap)
{
  TrunkTableApi tableBuff = {interfaceId,tgpId,e1Num,startCic,endCic,
          trunkType,UNLOCKED,NO_RESET,ENABLED,tsCicMap};

  if (CLIB_SUCCESS != insertTrunkTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkTable Fail",__func__);  
  }
}

I_Void addCicTable(I_U16 interfaceId,I_U16 tgpId,I_U32 e1Num,I_U8 timeSlot,I_U32 cicId,I_U32 adminState)
{
  CicTableApi tableBuff = {interfaceId,tgpId,e1Num,timeSlot,cicId,
          SIGNALLING,adminState,NO_RESET};

  if (CLIB_SUCCESS != insertCicTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertCicTable Fail",__func__);  
  }
}

I_Void addTrunkGroupTable(I_U16 interfaceId,I_U16 tgpId)
{
  TrunkGroupTableApi tableBuff = {interfaceId,tgpId,UNLOCKED,ENABLED};

  if (CLIB_SUCCESS != insertTrunkGroupTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkGroupTable Fail",__func__);  
  }
}

I_Void addMccLinkResTable(I_U8 mccTrunkNum,I_U8 mccTrunkTs,I_U32 mccLinkStatus,I_U8 cardNum,I_U32 extTrunkNum,I_U32 extTrunkTs)
{
   MccLinkResourceTableApi  tableBuff = {mccTrunkNum,mccTrunkTs,SYS_TS_USAGE_MTP2,
      mccLinkStatus,cardNum,extTrunkNum,extTrunkTs};
   if (CLIB_SUCCESS != insertMccLinkResourceTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Fail",__func__);  
   }
}

I_Void addMccLinkResGenericTable(I_U8 mccTrunkNum,I_U8 mccTrunkTs,I_U32 mccLinkStatus,I_U8 cardNum,I_U32 extTrunkNum,I_U32 extTrunkTs)
{
   MccLinkResourceTableApi  tableBuff = {mccTrunkNum,mccTrunkTs,SYS_TS_USAGE_ABIS_GENERIC,
      mccLinkStatus,cardNum,extTrunkNum,extTrunkTs};
   if (CLIB_SUCCESS != insertMccLinkResourceTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Fail",__func__);  
   }
}
I_Void addRowInBssTable(I_U32 bscId,I_U32 adminState)
{
   BssTableApi  bssTableApiBuff;
   bssTableApiBuff.bscId =bscId;
   bssTableApiBuff.adminState = adminState;
   bssTableApiBuff.bssReset = FALSE;
   bssTableApiBuff.gprsEnabled =0;   
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
   bssTableApiBuff.bssapTimer8 = 16;       
   bssTableApiBuff.bssapTimer7 = 10;       

   if(insertBssTable(&bssTableApiBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBssTable : insertBssTable OK");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBssTable : insertBssTable NOK");
   }
}

void addRowInE1PerTable(I_U32 e1Num,I_U32 adminState,I_U32 usageType,I_U16 trunkPortId,
   I_U32 mapAction,I_U32 e1Category)
{
   E1PerTableApi e1PerTableBuff;
   e1PerTableBuff.e1Num = e1Num;
   e1PerTableBuff.adminState = adminState;
   e1PerTableBuff.usageType = usageType;
   e1PerTableBuff.usingEntity = 0;
   e1PerTableBuff.trunkPortId = trunkPortId;
   e1PerTableBuff.mapAction = mapAction;
   e1PerTableBuff.e1Category = e1Category;
   if(insertE1PerTable(&e1PerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addE1PerTable: insertE1PerTable unsuccessfull\n");
   }
}

I_Void addMtp3TimerTable(I_U16 dummyIndex, I_U16 mtp3Timermtp3_T1, I_U16 mtp3Timermtp3_T2, I_U16 mtp3Timermtp3_T3)
{
   Mtp3TimerTableApi tableBuff = {dummyIndex,mtp3Timermtp3_T1, mtp3Timermtp3_T2,
   mtp3Timermtp3_T3,9,9,9,12,10,0,400,410,11,12,25,25,15,14,413,680,600,640,2000,2000,4,330,130,30,50,640,340,50,50,400,50};
   if (CLIB_SUCCESS != insertMtp3TimerTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertMtp3TimerTable Fail",__func__);  
   }
}

I_Void addSccpTimerTable(I_U16 dummyIndex, I_U16 sccpTimerstatInfo,I_U16    sccpTimercoordChg, I_U16    sccpTimerig0reSST )
{
   SccpTimerTableApi tableBuff={dummyIndex, sccpTimerstatInfo, sccpTimercoordChg, sccpTimerig0reSST,30,90,10,20,300,660,240,10,30,10 };
   if (CLIB_SUCCESS != insertSccpTimerTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSccpTimerTable Fail",__func__);  
   }
}

I_Void addInBssapTimerTable(I_U16 index, I_U16 bssapTimerT1, I_U16 bssapTimerT4, I_U16 bssapTimerT10)
{
   BssapTimerTableApi tableBuff={index, bssapTimerT1, bssapTimerT4, bssapTimerT10, 5, 10, 5, 5, 5, 10 };
   if (CLIB_SUCCESS != insertBssapTimerTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertBssapTimerTable Fail",__func__);  
   }
}

I_Void addLapdTimerTable(I_U16 lapdTimerT200, I_U16 lapdTimerT201, I_U16    lapdTimerT202, I_U16 lapdTimerT203, I_U16 lapdTimerDUMMYIndex)
{
   LapdTimerTableApi tableBuff = {lapdTimerT200, lapdTimerT201, lapdTimerT202,lapdTimerT203,  lapdTimerDUMMYIndex };
   if (CLIB_SUCCESS != insertLapdTimerTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLapdTimerTable Fail",__func__);  
   }
}

I_Void deleteFromLapdTimerTable(I_U16 lapdTimerDUMMYIndex)
{
   LapdTimerTableIndices tableBuff;
   tableBuff.lapdTimerDUMMYIndex = lapdTimerDUMMYIndex;
   if (CLIB_SUCCESS != deleteLapdTimerTable(&tableBuff) ) 
   {
      LOG_PRINT(LOG_INFO,"%s:deleteLapdTimerTable Fail",__func__);  
   }
}

void addSwMNodeTable(I_U32 nodeId)
{
   SwMNodeTableApi swMNodeTableBuff;
   swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
   swMNodeTableBuff.nodeIdentity = nodeId;
   swMNodeTableBuff.e1Num = 2;
   swMNodeTableBuff.lapdTs = 0;
   strcpy(swMNodeTableBuff.swVersionActive,"10.11.12"); 
   strcpy(swMNodeTableBuff.swVersionInactive,"100.101.102");
   strcpy(swMNodeTableBuff.swVersionDownloaded,"200.201.202");
   strcpy(swMNodeTableBuff.swVersionNew,"");
   swMNodeTableBuff.swAction = 0;
   swMNodeTableBuff.swStatus = 0;
   if(insertSwMNodeTable(&swMNodeTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertSwMNodeTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertSwMNodeTable unsuccessfull\n");
   }
}

void deleteRowFromE1PerTable(I_U32 e1Num)
{
   E1PerTableIndices e1PerTableBuff;
   e1PerTableBuff.e1Num = e1Num;
   if(deleteE1PerTable(&e1PerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteRowFromE1PerTable: deleteE1PerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteRowFromE1PerTable: deleteE1PerTable unsuccessfull\n");
   }
}

I_Void addToSs7RouteTable( I_U16 linksetID, I_U16 routeID )
{
   Ss7RouteTableApi tableBuff = { linksetID, routeID,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4, 0xFE, 0xFE, INTERNATIONAL, DISABLE, UNLOCKED };
   if (CLIB_SUCCESS != insertSs7RouteTable( &tableBuff) )
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7RouteTable Fail",__func__);
   }
}

I_Void addLinksetStatusTable(I_U16 linkSetId,I_U32 oprState)
{
  LinksetStatusTableApi tableBuff = {linkSetId,oprState};

  if (CLIB_SUCCESS != insertLinksetStatusTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinksetStatusTable Fail",__func__);  
  }
}

I_Void addLinkStatusTable(I_U16 linkSetId,I_U16 linkId,I_U32 oprState)
{
  LinkStatusTableApi tableBuff = {linkSetId,linkId,oprState};

  if (CLIB_SUCCESS != insertLinkStatusTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertLinkStatusTable Fail",__func__);  
  }
}

I_Void addSs7RouteStatusTable(I_U16 linkSetId,I_U16 routeId,I_U32 oprState)
{
  Ss7RouteStatusTableApi tableBuff = {linkSetId,routeId,oprState};

  if (CLIB_SUCCESS != insertSs7RouteStatusTable( &tableBuff) ) 
  {
      LOG_PRINT(LOG_CRITICAL,"%s:insertSs7routeStatusTable Fail",__func__);  
  }
}

I_Void populateMccLinkResourceTable(I_U32 insertRows)
{
  MccLinkResourceTableApi tableBuff = {0};
  I_U32 count;
  for (count=2; count<insertRows+2; count++)
  {
     tableBuff.mccTrunkNum = 32;
     tableBuff.mccTrunkTs  = count;
     tableBuff.mccLinkType = SYS_TS_USAGE_ABIS_GENERIC;
     tableBuff.mccLinkStatus = SYS_TS_FREE;
     tableBuff.extTrunkNum = 0xFF;
     tableBuff.extTrunkTs = 0xFF;
     if(count > ((insertRows/2)+2))
        tableBuff.cardNum = 4;
     else
        tableBuff.cardNum = 3;
     if (CLIB_SUCCESS != insertMccLinkResourceTable( &tableBuff) ) 
     {
        LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Fail",__func__);  
     }
  }
  LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Pass",__func__);  
}

I_Void populateMccLinkResourceTableMTP2(I_U32 insertRows)
{
  MccLinkResourceTableApi tableBuff = {0};
  I_U32 count;
  for (count=2; count<insertRows+2; count++)
  {
     tableBuff.mccTrunkNum = 34;
     tableBuff.mccTrunkTs  = count;
     tableBuff.mccLinkType = SYS_TS_USAGE_MTP2;
     tableBuff.mccLinkStatus = SYS_TS_FREE;
     tableBuff.extTrunkNum = 0xFF;
     tableBuff.extTrunkTs = 0xFF;
     if(count > ((insertRows/2)+2))
        tableBuff.cardNum = 4;
     else
        tableBuff.cardNum = 3;
     if (CLIB_SUCCESS != insertMccLinkResourceTable( &tableBuff) ) 
     {
        LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Fail",__func__);  
     }
  }
  LOG_PRINT(LOG_CRITICAL,"%s:insertMccLinkResourceTable Pass",__func__);  
}

void addRowInBicTable(I_U32 bicId,I_U8 numTrx,I_U32 e1Id,I_U32 adminState)
{
   BicTableApi bicTableBuff;
   bicTableBuff.bicId = bicId; 
   bicTableBuff.numTrx = numTrx;
   bicTableBuff.e1Id = e1Id;
   bicTableBuff.adminState = adminState;
   if(insertBicTable(&bicTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"addBicTable : insertBicTable OK\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"addBicTable : insertBicTable Failed\n");
   }
}

void addBicTrxTimeSlotUsageTable(I_U32 bicId,I_U32 e1Id,I_U8 ts)
{
   BicTrxTimeslotUsageTableApi bicTrxTimeslotUsageBuff;
   bicTrxTimeslotUsageBuff.tsUser = TS_USAGE_BIC;
   bicTrxTimeslotUsageBuff.bicOrTrxId = bicId;
   bicTrxTimeslotUsageBuff.e1Id = e1Id;
   bicTrxTimeslotUsageBuff.startTs = ts;
   bicTrxTimeslotUsageBuff.numTs = 1;
   if(insertBicTrxTimeslotUsageTable(&bicTrxTimeslotUsageBuff) == CLIB_SUCCESS)
   {
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable:insertBicTrxTimeslotUsageTable OK\n");
   }
   else
   {
    LOG_PRINT(LOG_INFO,"addBicTrxTimeslotUsageTable:insertBicTrxTimeslotUsageTable NOK\n");
   }
}

I_Void addAbisTimeSlotTable(I_U32 e1Num,I_U32 tsNum,I_U32 usageType)
{
   AbisTimeSlotPerTableApi tableBuff = {e1Num,tsNum,0,usageType};
   AbisTimeSlotNonPerTableApi tableBuff1 = {e1Num,tsNum,0,usageType,0};
   if (CLIB_SUCCESS != insertAbisTimeSlotPerTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAbisTimeSlotPerTable Fail",__func__);  
   }
   if (CLIB_SUCCESS != insertAbisTimeSlotNonPerTable( &tableBuff1) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertAbisTimeSlotNonPerTable Fail",__func__);  
   }
}

void cfgPopulateSwMNodeTable(I_U32 nodeType,I_U32 nodeId,I_U32 e1Id,I_S8 *swVerAc,I_S8 *swVerInAc,I_S8 *swVerDnld,I_S8 *swVerNew,I_U32 swAction,I_U32 swStatus)
{
   SwMNodeTableApi swMNodeTableBuff;
   swMNodeTableBuff.nodeType = nodeType;
   swMNodeTableBuff.nodeIdentity = nodeId;
   swMNodeTableBuff.e1Num = e1Id;
   strcpy(swMNodeTableBuff.swVersionActive,swVerAc); 
   strcpy(swMNodeTableBuff.swVersionInactive,swVerInAc);
   strcpy(swMNodeTableBuff.swVersionDownloaded,swVerDnld);
   strcpy(swMNodeTableBuff.swVersionNew,swVerNew);
   swMNodeTableBuff.swAction = swAction;
   swMNodeTableBuff.swStatus = swStatus;
   if(insertSwMNodeTable(&swMNodeTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertSwMNodeTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertSwMNodeTable unsuccessfull\n");
   }
}

I_Void addTrunkPortTable(I_U32 trId)
{
   TrunkPortTableApi tableBuff = {1,1,trId,1,1,1,1,0,0,0,0,SYS_E1_USAGE_NONE};
   if (CLIB_SUCCESS != insertTrunkPortTable( &tableBuff) ) 
   {
      LOG_PRINT(LOG_CRITICAL,"%s:insertTrunkPortTable Fail",__func__);  
   }
}

I_Void addInBicStatusTable(I_U32 bicId)
{
   BicStatusTableApi tableBuff = {bicId,0,0,0};
   if (CLIB_SUCCESS != insertBicStatusTable( &tableBuff) ) 
   {
      LOG_PRINT(INFO,"%s:insertBicStatusTable Fail",__func__);  
   }
}

I_Void addInTrxTable(I_U32 ptrxId,I_U32 bicId)
{
   TrxTableApi tableBuff = {ptrxId,0,2,bicId,100,1,2};
   if (CLIB_SUCCESS != insertTrxTable( &tableBuff) ) 
   {
      LOG_PRINT(INFO,"%s:insertTrxTable Fail",__func__);  
   }
}

