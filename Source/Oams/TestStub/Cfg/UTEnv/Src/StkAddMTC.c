#include <includes.h>

/* CLEANDBTABLEIMPLEMENTATION(AbisInterfaceTable)
CLEANDBTABLEIMPLEMENTATION(BssTable)
CLEANDBTABLEIMPLEMENTATION(Ss7StackConfigTable) 
CLEANDBTABLEIMPLEMENTATION(TrunkGroupTable)
CLEANDBTABLEIMPLEMENTATION(LinksetTable)
CLEANDBTABLEIMPLEMENTATION(TrunkTable) 
CLEANDBTABLEIMPLEMENTATION(CicTable) */
CLEANDBTABLEIMPLEMENTATION(MccLinkResourceTable)
CLEANDBTABLEIMPLEMENTATION(Mtp3TimerTable)
CLEANDBTABLEIMPLEMENTATION(SccpTimerTable)
CLEANDBTABLEIMPLEMENTATION(BssapTimerTable)
CLEANDBTABLEIMPLEMENTATION(LapdTimerTable)
CLEANDBTABLEIMPLEMENTATION(LinksetStatusTable)
CLEANDBTABLEIMPLEMENTATION(LinkStatusTable)
CLEANDBTABLEIMPLEMENTATION(Ss7RouteStatusTable)
CLEANDBTABLEIMPLEMENTATION(AbisTimeSlotPerTable)

I_Void cleanDB()
{
  CALLCLEANDBTABLE(Ss7StackConfigTable);
  CALLCLEANDBTABLE(AifInterfaceTable);
  CALLCLEANDBTABLE(TrunkGroupTable);
  CALLCLEANDBTABLE(TrunkTable);
  CALLCLEANDBTABLE(LinksetTable);
  CALLCLEANDBTABLE(LinkTable);
  CALLCLEANDBTABLE(CicTable);
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(BssTable);
  CALLCLEANDBTABLE(Mtp3TimerTable);
  CALLCLEANDBTABLE(SccpTimerTable);
  CALLCLEANDBTABLE(BssapTimerTable);
  //CALLCLEANDBTABLE(LapdTimerTable);
  CALLCLEANDBTABLE(Ss7RouteTable);
  CALLCLEANDBTABLE(LinksetStatusTable);
  CALLCLEANDBTABLE(LinkStatusTable);
  CALLCLEANDBTABLE(Ss7RouteStatusTable);
  deleteFromLapdTimerTable(2);
  deleteFromLapdTimerTable(0);
}

I_S32 cfgStubSendCmMessage(void *buff, I_U32 size, I_U32 MessageType)
{
   sCmMsg* CmMsgPtr ;

   LOG_PRINT(LOG_INFO,"Calling cfgStubSendCmMessage().....");
   if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(size+sizeof(sCmMsg))) == NULL)
   {
      LOG_PRINT(LOG_INFO,"CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   CmMsgPtr->sHdr.msgType = MessageType;
   CmMsgPtr->sHdr.src.entity =ENT_OAM_CM; 
   CmMsgPtr->sHdr.dest.entity = ENT_OAMS_CFG;
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

I_Void cfgStubSendScmCfgAlarmInd(I_U32 alarmId)
{
   OamsCfgScmCfgAlarmInd OamsCfgScmCfgAlarmIndBuff;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.sysalarmId= alarmId;
   cfgStubSendMessage(&OamsCfgScmCfgAlarmIndBuff,sizeof(OamsCfgScmCfgAlarmInd),ENT_OAM_OIL,OAMS_SCM_CFG_ALARM_IND,0);
}

I_Void cfgStubSendAlarm(I_U32 alarmId,I_U32 key1,I_U32 key2,I_U32 key3,I_U32 key4)
{
   OamsCfgScmCfgAlarmInd OamsCfgScmCfgAlarmIndBuff;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.sysalarmId= alarmId;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.info3 = OAMS_OBJTYPE_BSS;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.key1 = key1; 
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.key2 = key2;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.key3 = key3;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.key4 = key4;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_INFORMATION;
   OamsCfgScmCfgAlarmIndBuff.sysAlarm.infoStrLen = sprintf(OamsCfgScmCfgAlarmIndBuff.sysAlarm.infoString,"Alarm String");
   cfgStubSendMessage(&OamsCfgScmCfgAlarmIndBuff,sizeof(OamsCfgScmCfgAlarmInd),ENT_OAM_OIL,OAM_OIL_CFG_ALARM_IND,0);
}
#if 0
/*----------------------------------TC1---------------------------------------------*/
I_Void  fStkAddMCfgPreTC1() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  AbisInterfaceTableApi abisInterfaceBuff;
  abisInterfaceBuff.interfaceId = 1; 
  abisInterfaceBuff.bicId = INVALID_BIC; 
  memcpy(abisInterfaceBuff.interfaceNameString,"Abis Interface",20);
  abisInterfaceBuff.interfaceType = IF_TYPE_ABIS; 
  abisInterfaceBuff.adminState = UNLOCKED;
 
  cfgStubSendCmMessage(&abisInterfaceBuff, sizeof(AbisInterfaceTableApi), BSC_API_SET_ABISINTERFACETABLE); 
  return ;
}

I_Void  fStkAddMCfgStepsTC1()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SET_OBJ_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }

  return ;
}
I_Void  fStkAddMCfgPostTC1()
{
  return ;
}
I_Void fStkAddMCfgTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC1();
  fStkAddMCfgStepsTC1();
  fStkAddMCfgPostTC1();
  return ;
}

/*----------------------------------TC2---------------------------------------------*/
I_Void  fStkAddMCfgPreTC2() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  cleanDB();

  AbisInterfaceTableApi abisInterfaceBuff;
  abisInterfaceBuff.interfaceId = 1; 
  abisInterfaceBuff.bicId = 1; 
  memcpy(abisInterfaceBuff.interfaceNameString,"Abis Interface",20);
  abisInterfaceBuff.interfaceType = IF_TYPE_ABIS; 
  abisInterfaceBuff.adminState = UNLOCKED;
 
  cfgStubSendCmMessage(&abisInterfaceBuff, sizeof(AbisInterfaceTableApi), BSC_API_SET_ABISINTERFACETABLE); 
  return ;
}
I_Void  fStkAddMCfgStepsTC2()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SET_OBJ_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC2()
{
  return ;
}
I_Void fStkAddMCfgTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC2();
  fStkAddMCfgStepsTC2();
  fStkAddMCfgPostTC2();
  return ;
}

/*----------------------------------TC3---------------------------------------------*/
I_Void  fStkAddMCfgPreTC3() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  cleanDB();
 
  AbisInterfaceTableApi abisInterfaceBuff;
  abisInterfaceBuff.interfaceId = 1; 
  abisInterfaceBuff.bicId = INVALID_BIC; 
  memcpy(abisInterfaceBuff.interfaceNameString,"Abis Interface",20);
  abisInterfaceBuff.interfaceType = IF_TYPE_AIF; 
  abisInterfaceBuff.adminState = UNLOCKED;
 
  cfgStubSendCmMessage(&abisInterfaceBuff, sizeof(AbisInterfaceTableApi), BSC_API_SET_ABISINTERFACETABLE);
  return ;
}

I_Void  fStkAddMCfgStepsTC3()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SET_OBJ_NOT_ALLOWED) 
        {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC3()
{
  return ;
}
I_Void fStkAddMCfgTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC3();
  fStkAddMCfgStepsTC3();
  fStkAddMCfgPostTC3();
  return ;
}
/*----------------------------------TC4---------------------------------------------*/
I_Void  fStkAddMCfgPreTC4() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  cleanDB();

  addAbisInterfaceTable(1,1,IF_TYPE_ABIS);
  AbisInterfaceTableApi abisInterfaceBuff;
  abisInterfaceBuff.interfaceId = 1; 
  abisInterfaceBuff.bicId = INVALID_BIC; 
  memcpy(abisInterfaceBuff.interfaceNameString,"Abis Interface",20);
  abisInterfaceBuff.interfaceType = IF_TYPE_ABIS; 
  abisInterfaceBuff.adminState = UNLOCKED;
 
  cfgStubSendCmMessage(&abisInterfaceBuff, sizeof(AbisInterfaceTableApi), BSC_API_SET_ABISINTERFACETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC4()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SET_OBJ_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC4()
{
  return ;
}
I_Void fStkAddMCfgTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC4();
  fStkAddMCfgStepsTC4();
  fStkAddMCfgPostTC4();
  return ;
}
#endif
/*----------------------------------TC5---------------------------------------------*/
I_Void  fStkAddMCfgPreTC5() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  addRowInBssTable(1, LOCKED);
  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
  return ;

}
I_Void  fStkAddMCfgStepsTC5()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC5()
{
  return ;
}
I_Void fStkAddMCfgTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC5();
  fStkAddMCfgStepsTC5();
  fStkAddMCfgPostTC5();
  return ;
}

/*----------------------------------TC6---------------------------------------------*/
I_Void  fStkAddMCfgPreTC6() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,1,3); 
  addRowInBssTable(1, LOCKED);
  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC6()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC6()
{
  return ;
}
I_Void fStkAddMCfgTC6(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC6();
  fStkAddMCfgStepsTC6();
  fStkAddMCfgPostTC6();
  return ;
}

/*----------------------------------TC7---------------------------------------------*/
I_Void  fStkAddMCfgPreTC7() 
{
  AifInterfaceTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,1,3); 
  requestBuff.interfaceId = 1;
  memcpy(requestBuff.interfaceNameString,"Aif Interface",20) ;
  requestBuff.interfaceType = IF_TYPE_AIF;
  requestBuff.dpc = 2;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.operationalState = ENABLED;
  requestBuff.interfaceAdminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(AifInterfaceTableApi), BSC_API_SET_AIFINTERFACETABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC7()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC7()
{
  return ;
}
I_Void fStkAddMCfgTC7(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC7();
  fStkAddMCfgStepsTC7();
  fStkAddMCfgPostTC7();
  return ;
}

/*----------------------------------TC8---------------------------------------------*/
I_Void  fStkAddMCfgPreTC8() 
{
  AifInterfaceTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  cleanDB(); 
  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  requestBuff.interfaceId = 1;
  memcpy(requestBuff.interfaceNameString,"Aif Interface",20) ;
  requestBuff.interfaceType = IF_TYPE_AIF;
  requestBuff.dpc = 2;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.operationalState = ENABLED;
  requestBuff.interfaceAdminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(AifInterfaceTableApi), BSC_API_SET_AIFINTERFACETABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC8()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC8()
{
  return ;
}
I_Void fStkAddMCfgTC8(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC8();
  fStkAddMCfgStepsTC8();
  fStkAddMCfgPostTC8();
  return ;
}
/*----------------------------------TC9---------------------------------------------*/
I_Void  fStkAddMCfgPreTC9() 
{
  LinksetTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  requestBuff.linksetID = 10;
  memcpy(requestBuff.displayString,"LinkSet",20) ;
  requestBuff.interfaceId = 1;
  requestBuff.adjacentPointCode = 3;
  requestBuff.networkIndicator = NATIONAL;
  requestBuff.adminstate = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinksetTableApi), BSC_API_SET_LINKSETTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC9()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC9()
{
  return ;
}
I_Void fStkAddMCfgTC9(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC9();
  fStkAddMCfgStepsTC9();
  fStkAddMCfgPostTC9();
  return ;
}
/*----------------------------------TC10---------------------------------------------*/
I_Void  fStkAddMCfgPreTC10() 
{
  LinksetTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  cleanDB(); 
  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addLinksetTable(10,1,3,NATIONAL);
  requestBuff.linksetID = 10;
  memcpy(requestBuff.displayString,"LinkSet",20) ;
  requestBuff.interfaceId = 1;
  requestBuff.adjacentPointCode = 3;
  requestBuff.networkIndicator = NATIONAL;
  requestBuff.adminstate = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinksetTableApi), BSC_API_SET_LINKSETTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC10()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC10()
{
  return ;
}
I_Void fStkAddMCfgTC10(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC10();
  fStkAddMCfgStepsTC10();
  fStkAddMCfgPostTC10();
  return ;
}
/*----------------------------------TC11---------------------------------------------*/
I_Void  fStkAddMCfgPreTC11() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  cleanDB(); 
  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC11()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC11()
{
  return ;
}
I_Void fStkAddMCfgTC11(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC11();
  fStkAddMCfgStepsTC11();
  fStkAddMCfgPostTC11();
  return ;
}

/*----------------------------------TC12---------------------------------------------*/
I_Void  fStkAddMCfgPreTC12() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
 
  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC12()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC12()
{
  return ;
}
I_Void fStkAddMCfgTC12(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC12();
  fStkAddMCfgStepsTC12();
  fStkAddMCfgPostTC12();
  return ;
}

/*----------------------------------TC13---------------------------------------------*/
I_Void  fStkAddMCfgPreTC13() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,LOCKED);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,0,16);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 18;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC13()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC13()
{
  return ;
}
I_Void fStkAddMCfgTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC13();
  fStkAddMCfgStepsTC13();
  fStkAddMCfgPostTC13();
  return ;
}

/*----------------------------------TC14---------------------------------------------*/
I_Void  fStkAddMCfgPreTC14() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  cleanDB();
  
  addLinksetTable(1,1,3,NATIONAL);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,LOCKED);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,0,16);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC14()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
        }
        break;
      case OAMS_CFG_AFH_ALARM_IND:
         LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
         OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
         LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
         LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
         LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
         LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
         LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
         LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
         TEST_RESULT=1;
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC14()
{
  return ;
}
I_Void fStkAddMCfgTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC14();
  fStkAddMCfgStepsTC14();
  fStkAddMCfgPostTC14();
  return ;
}

/*----------------------------------TC15---------------------------------------------*/
I_Void  fStkAddMCfgPreTC15() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  cleanDB();
  
  addLinksetTable(1,1,3,NATIONAL);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,UNLOCKED);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,0,16);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC15()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
        }
        break;
      case OAMS_CFG_AFH_ALARM_IND:
         LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
         OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
         LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
         LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
         LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
         LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
         LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
         LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
         TEST_RESULT=1;
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC15()
{
  return ;
}
I_Void fStkAddMCfgTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC15();
  fStkAddMCfgStepsTC15();
  fStkAddMCfgPostTC15();
  return ;
}

/*----------------------------------TC16---------------------------------------------*/
I_Void  fStkAddMCfgPreTC16() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC16()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_LINKSET_OBJ_NOT_PRESENT) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC16()
{
  return ;
}
I_Void fStkAddMCfgTC16(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC16();
  fStkAddMCfgStepsTC16();
  fStkAddMCfgPostTC16();
  return ;
}

/*----------------------------------TC17---------------------------------------------*/
I_Void  fStkAddMCfgPreTC17() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 20;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC17()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC17()
{
  return ;
}
I_Void fStkAddMCfgTC17(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC17();
  fStkAddMCfgStepsTC17();
  fStkAddMCfgPostTC17();
  return ;
}

/*----------------------------------TC18---------------------------------------------*/
I_Void  fStkAddMCfgPreTC18() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC18()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ACTION_NOT_ALLOWED_IN_UNLOCKED_STATE) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC18()
{
  return ;
}
I_Void fStkAddMCfgTC18(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC18();
  fStkAddMCfgStepsTC18();
  fStkAddMCfgPostTC18();
  return ;
}

/*----------------------------------TC19---------------------------------------------*/
I_Void  fStkAddMCfgPreTC19() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 6;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC19()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_NOT_PRESENT_IN_DB) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC19()
{
  return ;
}
I_Void fStkAddMCfgTC19(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC19();
  fStkAddMCfgStepsTC19();
  fStkAddMCfgPostTC19();
  return ;
}

/*----------------------------------TC20---------------------------------------------*/
I_Void  fStkAddMCfgPreTC20() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 2;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC20()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_E1_TYPE) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC20()
{
  return ;
}
I_Void fStkAddMCfgTC20(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC20();
  fStkAddMCfgStepsTC20();
  fStkAddMCfgPostTC20();
  return ;
}

/*----------------------------------TC21---------------------------------------------*/
I_Void  fStkAddMCfgPreTC21() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addLinkTable(2,1,1,0,16,1,CRC_ENABLE,LOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC21()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_LINK_EXISTS_ON_RCVD_E1TS) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC21()
{
  return ;
}
I_Void fStkAddMCfgTC21(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC21();
  fStkAddMCfgStepsTC21();
  fStkAddMCfgPostTC21();
  return ;
}

/*----------------------------------TC22---------------------------------------------*/
I_Void  fStkAddMCfgPreTC22() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addCicTable(1,1,0,16,10,UNLOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC22()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CIC_EXISTS_ON_RCVD_E1TS) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC22()
{
  return ;
}
I_Void fStkAddMCfgTC22(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC22();
  fStkAddMCfgStepsTC22();
  fStkAddMCfgPostTC22();
  return ;
}

/*----------------------------------TC23---------------------------------------------*/
I_Void  fStkAddMCfgPreTC23() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_ALLOCATED,1,INVALID_E1,INVALID_TS);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC23()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_NO_FREE_MCC_TRUNKNUM_TRUNKTS) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC23()
{
  return ;
}
I_Void fStkAddMCfgTC23(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC23();
  fStkAddMCfgStepsTC23();
  fStkAddMCfgPostTC23();
  return ;
}

/*----------------------------------TC24---------------------------------------------*/
I_Void  fStkAddMCfgPreTC24() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC24()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break;  
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC24()
{
  return ;
}
I_Void fStkAddMCfgTC24(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC24();
  fStkAddMCfgStepsTC24();
  fStkAddMCfgPostTC24();
  return ;
}

/*----------------------------------TC25---------------------------------------------*/
I_Void  fStkAddMCfgPreTC25() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC25()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_FAIL;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SWITCH_CONNECT_NACK) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC25()
{
  return ;
}
I_Void fStkAddMCfgTC25(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC25();
  fStkAddMCfgStepsTC25();
  fStkAddMCfgPostTC25();
  return ;
}

/*----------------------------------TC26---------------------------------------------*/
I_Void  fStkAddMCfgPreTC26() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC26()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TIMEOUT) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC26()
{
  return ;
}
I_Void fStkAddMCfgTC26(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC26();
  fStkAddMCfgStepsTC26();
  fStkAddMCfgPostTC26();
  return ;
}

/*----------------------------------TC27---------------------------------------------*/
I_Void  fStkAddMCfgPreTC27() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,LOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 2;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC27()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC27()
{
  return ;
}
I_Void fStkAddMCfgTC27(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC27();
  fStkAddMCfgStepsTC27();
  fStkAddMCfgPostTC27();
  return ;
}

/*----------------------------------TC28---------------------------------------------*/
I_Void  fStkAddMCfgPreTC28() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,LOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC28()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC28()
{
  return ;
}
I_Void fStkAddMCfgTC28(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC28();
  fStkAddMCfgStepsTC28();
  fStkAddMCfgPostTC28();
  return ;
}

/*----------------------------------TC29---------------------------------------------*/
I_Void  fStkAddMCfgPreTC29() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,LOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 17;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC29()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC29()
{
  return ;
}
I_Void fStkAddMCfgTC29(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC29();
  fStkAddMCfgStepsTC29();
  fStkAddMCfgPostTC29();
  return ;
}

/*----------------------------------TC30---------------------------------------------*/
I_Void  fStkAddMCfgPreTC30() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,UNLOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 17;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC30()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OBJECT_NOT_LOCKED) {
           TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC30()
{
  return ;
}
I_Void fStkAddMCfgTC30(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC30();
  fStkAddMCfgStepsTC30();
  fStkAddMCfgPostTC30();
  return ;
}

/*----------------------------------TC31---------------------------------------------*/
I_Void  fStkAddMCfgPreTC31() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetTable(1,1,3,NATIONAL);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,LOCKED);
  addMccLinkResTable(3,12,SYS_TS_FREE,1,0,16);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 1;
  requestBuff.slc = 1;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 18;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC31()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_FAIL;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SWITCH_CONNECT_NACK) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC31()
{
  return ;
}
I_Void fStkAddMCfgTC31(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC31();
  fStkAddMCfgStepsTC31();
  fStkAddMCfgPostTC31();
  return ;
}

/*----------------------------------TC32---------------------------------------------*/
I_Void  fStkAddMCfgPreTC32() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  addTrunkTable(1,DEFAULT_TGPID,0,30,61,TRUNK_E1_TYPE,0xFFFEFFFF);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC32()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC32()
{
  return ;
}
I_Void fStkAddMCfgTC32(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC32();
  fStkAddMCfgStepsTC32();
  fStkAddMCfgPostTC32();
  return ;
}

/*----------------------------------TC33---------------------------------------------*/
I_Void  fStkAddMCfgPreTC33() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC33()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TRUNKGROUP_OBJ_NOT_PRESENT) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC33()
{
  return ;
}
I_Void fStkAddMCfgTC33(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC33();
  fStkAddMCfgStepsTC33();
  fStkAddMCfgPostTC33();
  return ;
}

/*----------------------------------TC34---------------------------------------------*/
I_Void  fStkAddMCfgPreTC34() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 9;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC34()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC34()
{
  return ;
}
I_Void fStkAddMCfgTC34(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC34();
  fStkAddMCfgStepsTC34();
  fStkAddMCfgPostTC34();
  return ;
}

/*----------------------------------TC35---------------------------------------------*/
I_Void  fStkAddMCfgPreTC35() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 6;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC35()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_NOT_PRESENT_IN_DB) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC35()
{
  return ;
}
I_Void fStkAddMCfgTC35(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC35();
  fStkAddMCfgStepsTC35();
  fStkAddMCfgPostTC35();
  return ;
}

/*----------------------------------TC36---------------------------------------------*/
I_Void  fStkAddMCfgPreTC36() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 2;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC36()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_E1_TYPE) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC36()
{
  return ;
}
I_Void fStkAddMCfgTC36(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC36();
  fStkAddMCfgStepsTC36();
  fStkAddMCfgPostTC36();
  return ;
}

/*----------------------------------TC37---------------------------------------------*/
I_Void  fStkAddMCfgPreTC37() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID);
  addRowInE1PerTable(4,1,SYS_E1_USAGE_AIF,INVALID_TRUNK_ID,2,1); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 4;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC37()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_MAP_NOT_CREATED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC37()
{
  deleteRowFromE1PerTable(4);
  return ;
}
I_Void fStkAddMCfgTC37(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC37();
  fStkAddMCfgStepsTC37();
  fStkAddMCfgPostTC37();
  return ;
}

/*----------------------------------TC38---------------------------------------------*/
I_Void  fStkAddMCfgPreTC38() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = ~0;
  requestBuff.endCic = INVALID_CIC;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC38()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_CIC_RCVD) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC38()
{
  return ;
}
I_Void fStkAddMCfgTC38(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC38();
  fStkAddMCfgStepsTC38();
  fStkAddMCfgPostTC38();
  return ;
}

/*----------------------------------TC39---------------------------------------------*/
I_Void  fStkAddMCfgPreTC39() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID); 
  addCicTable(1,1,0,16,10,UNLOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC39()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CIC_ALREADY_EXISTS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC39()
{
  return ;
}
I_Void fStkAddMCfgTC39(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC39();
  fStkAddMCfgStepsTC39();
  fStkAddMCfgPostTC39();
  return ;
}

/*----------------------------------TC40---------------------------------------------*/
I_Void  fStkAddMCfgPreTC40() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID);
  addLinkTable(1,1,1,0,10,1,CRC_ENABLE,LOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC40()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_LINK_EXISTS_ON_RCVD_E1TS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC40()
{
  return ;
}
I_Void fStkAddMCfgTC40(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC40();
  fStkAddMCfgStepsTC40();
  fStkAddMCfgPostTC40();
  return ;
}

/*----------------------------------TC41---------------------------------------------*/
I_Void  fStkAddMCfgPreTC41() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID);
  addCicTable(1,1,0,30,35,UNLOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC41()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_CIC_EXISTS_ON_RCVD_E1TS) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC41()
{
  return ;
}
I_Void fStkAddMCfgTC41(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC41();
  fStkAddMCfgStepsTC41();
  fStkAddMCfgPostTC41();
  return ;
}

/*----------------------------------TC42---------------------------------------------*/
I_Void  fStkAddMCfgPreTC42() 
{
  TrunkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  addTrunkGroupTable(1,DEFAULT_TGPID);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.startCic = 1;
  requestBuff.endCic = 31;
  requestBuff.trunkType = TRUNK_E1_TYPE;
  requestBuff.trunkAdminState = UNLOCKED;
  requestBuff.trunkReset = NO_RESET;
  requestBuff.operationalState = ENABLED;
  requestBuff.tsCicMap = 0xFFFEFFFF;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrunkTableApi), BSC_API_SET_TRUNKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC42()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC42()
{
  return ;
}
I_Void fStkAddMCfgTC42(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC42();
  fStkAddMCfgStepsTC42();
  fStkAddMCfgPostTC42();
  return ;
}

/*----------------------------------TC43---------------------------------------------*/
I_Void  fStkAddMCfgPreTC43() 
{
  LinksetTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  requestBuff.linksetID = 10;
  memcpy(requestBuff.displayString,"LinkSet",20) ;
  requestBuff.interfaceId = 1;
  requestBuff.adjacentPointCode = 3;
  requestBuff.networkIndicator = NATIONAL;
  requestBuff.adminstate = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinksetTableApi), BSC_API_SET_LINKSETTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC43()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_AIFINTERFACE_OBJ_NOT_PRESENT) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC43()
{
  return ;
}
I_Void fStkAddMCfgTC43(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC43();
  fStkAddMCfgStepsTC43();
  fStkAddMCfgPostTC43();
  return ;
}

/*----------------------------------TC44---------------------------------------------*/
I_Void  fStkAddMCfgPreTC44() 
{
  LinksetTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  requestBuff.linksetID = 10;
  memcpy(requestBuff.displayString,"LinkSet",20) ;
  requestBuff.interfaceId = 1;
  requestBuff.adjacentPointCode = 4;
  requestBuff.networkIndicator = NATIONAL;
  requestBuff.adminstate = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinksetTableApi), BSC_API_SET_LINKSETTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC44()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_REQUEST) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC44()
{
  return ;
}
I_Void fStkAddMCfgTC44(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC44();
  fStkAddMCfgStepsTC44();
  fStkAddMCfgPostTC44();
  return ;
}

/*----------------------------------TC45---------------------------------------------*/
I_Void  fStkAddMCfgPreTC45() 
{
  LinksetTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  requestBuff.linksetID = 10;
  memcpy(requestBuff.displayString,"LinkSet",20) ;
  requestBuff.interfaceId = 1;
  requestBuff.adjacentPointCode = 3;
  requestBuff.networkIndicator = 55;
  requestBuff.adminstate = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinksetTableApi), BSC_API_SET_LINKSETTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC45()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC45()
{
  return ;
}
I_Void fStkAddMCfgTC45(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC45();
  fStkAddMCfgStepsTC45();
  fStkAddMCfgPostTC45();
  return ;
}

/*----------------------------------TC46---------------------------------------------*/
I_Void  fStkAddMCfgPreTC46() 
{
  LinksetTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addAifInterfaceTable(1, IF_TYPE_AIF,3 ,1); 
  requestBuff.linksetID = 10;
  memcpy(requestBuff.displayString,"LinkSet",20) ;
  requestBuff.interfaceId = 1;
  requestBuff.adjacentPointCode = 3;
  requestBuff.networkIndicator = NATIONAL;
  requestBuff.adminstate = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinksetTableApi), BSC_API_SET_LINKSETTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC46()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC46()
{
  return ;
}
I_Void fStkAddMCfgTC46(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC46();
  fStkAddMCfgStepsTC46();
  fStkAddMCfgPostTC46();
  return ;
}

/*----------------------------------TC47---------------------------------------------*/
I_Void  fStkAddMCfgPreTC47() 
{
  AifInterfaceTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  requestBuff.interfaceId = 1;
  memcpy(requestBuff.interfaceNameString,"Aif Interface",20) ;
  requestBuff.interfaceType = IF_TYPE_AIF;
  requestBuff.dpc = 2;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.operationalState = ENABLED;
  requestBuff.interfaceAdminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(AifInterfaceTableApi), BSC_API_SET_AIFINTERFACETABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC47()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_SS7STACK_OBJ_NOT_PRESENT) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC47()
{
  return ;
}
I_Void fStkAddMCfgTC47(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC47();
  fStkAddMCfgStepsTC47();
  fStkAddMCfgPostTC47();
  return ;
}

/*----------------------------------TC48---------------------------------------------*/
I_Void  fStkAddMCfgPreTC48() 
{
  AifInterfaceTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,1,3); 
  requestBuff.interfaceId = 1;
  memcpy(requestBuff.interfaceNameString,"Aif Interface",20) ;
  requestBuff.interfaceType = 22;
  requestBuff.dpc = 2;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.operationalState = ENABLED;
  requestBuff.interfaceAdminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(AifInterfaceTableApi), BSC_API_SET_AIFINTERFACETABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC48()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC48()
{
  return ;
}
I_Void fStkAddMCfgTC48(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC48();
  fStkAddMCfgStepsTC48();
  fStkAddMCfgPostTC48();
  return ;
}

/*----------------------------------TC49---------------------------------------------*/
I_Void  fStkAddMCfgPreTC49() 
{
  AifInterfaceTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,1,3); 
  requestBuff.interfaceId = 1;
  memcpy(requestBuff.interfaceNameString,"Aif Interface",20) ;
  requestBuff.interfaceType = IF_TYPE_AIF;
  requestBuff.dpc = 2;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.operationalState = ENABLED;
  requestBuff.interfaceAdminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(AifInterfaceTableApi), BSC_API_SET_AIFINTERFACETABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC49()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC49()
{
  return ;
}
I_Void fStkAddMCfgTC49(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC49();
  fStkAddMCfgStepsTC49();
  fStkAddMCfgPostTC49();
  return ;
}

/*----------------------------------TC50---------------------------------------------*/
I_Void  fStkAddMCfgPreTC50() 
{
  AifInterfaceTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,1,3); 
  requestBuff.interfaceId = 1;
  memcpy(requestBuff.interfaceNameString,"Aif Interface",20) ;
  requestBuff.interfaceType = IF_TYPE_AIF;
  requestBuff.dpc = 2;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.operationalState = ENABLED;
  requestBuff.interfaceAdminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(AifInterfaceTableApi), BSC_API_SET_AIFINTERFACETABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC50()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TIMEOUT) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC50()
{
  return ;
}
I_Void fStkAddMCfgTC50(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC50();
  fStkAddMCfgStepsTC50();
  fStkAddMCfgPostTC50();
  return ;
}

/*----------------------------------TC51---------------------------------------------*/
I_Void  fStkAddMCfgPreTC51() 
{
  Mtp3TimerTableApi requestBuff = {1,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
  21,22,23,24,25,26,27,28,29,30,31,32,33,34};
  LOG_PRINT(INFO,"%s:",__func__);

  cfgStubSendCmMessage(&requestBuff, sizeof(Mtp3TimerTableApi), BSC_API_SET_MTP3TIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC51()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
 	   TEST_RESULT = 1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC51()
{
  return ;
}
I_Void fStkAddMCfgTC51(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC51();
  fStkAddMCfgStepsTC51();
  fStkAddMCfgPostTC51();
  return ;
}

/*----------------------------------TC52---------------------------------------------*/
I_Void  fStkAddMCfgPreTC52() 
{
  Mtp3TimerTableApi requestBuff = {1,10,10,10,10,9,9,12,10,0,400,410,11,12,25,25,15,14,413,680,600,640,2000,2000,4,330,130,30,50,640,340,50,50,400,50};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addMtp3TimerTable(1,5,6,7);

  cfgStubSendCmMessage(&requestBuff, sizeof(Mtp3TimerTableApi), BSC_API_SET_MTP3TIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC52()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC52()
{
  return ;
}
I_Void fStkAddMCfgTC52(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC52();
  fStkAddMCfgStepsTC52();
  fStkAddMCfgPostTC52();
  return ;
}

/*----------------------------------TC53---------------------------------------------*/
I_Void  fStkAddMCfgPreTC53() 
{
  Mtp3TimerTableApi requestBuff = {1,10,10,10,10,9,9,12,10,0,400,410,11,12,25,25,15,14,413,680,600,640,2000,2000,4,330,130,30,50,640,340,50,50,400,50};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addMtp3TimerTable(1,5,6,7);

  cfgStubSendCmMessage(&requestBuff, sizeof(Mtp3TimerTableApi), BSC_API_SET_MTP3TIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC53()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC53()
{
  return ;
}
I_Void fStkAddMCfgTC53(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC53();
  fStkAddMCfgStepsTC53();
  fStkAddMCfgPostTC53();
  return ;
}

/*----------------------------------TC54---------------------------------------------*/
I_Void  fStkAddMCfgPreTC54() 
{
  Mtp3TimerTableApi requestBuff = {1,10,10,10,10,9,9,12,10,0,400,410,11,12,25,25,15,14,413,680,600,640,2000,2000,4,330,130,30,50,640,340,50,50,400,50};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addMtp3TimerTable(1,5,6,7);

  cfgStubSendCmMessage(&requestBuff, sizeof(Mtp3TimerTableApi), BSC_API_SET_MTP3TIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC54()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TIMEOUT) {
           LOG_PRINT(LOG_INFO,"CM_ERR_TIMEOUT");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC54()
{
  return ;
}
I_Void fStkAddMCfgTC54(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC54();
  fStkAddMCfgStepsTC54();
  fStkAddMCfgPostTC54();
  return ;
}

/*----------------------------------TC55---------------------------------------------*/
I_Void  fStkAddMCfgPreTC55()
{
  SccpTimerTableApi requestBuff = {2,30,90,30,30,90,10,20,300,660,240,10,30,10};
  LOG_PRINT(INFO,"%s:",__func__);

  cfgStubSendCmMessage(&requestBuff, sizeof(SccpTimerTableApi), BSC_API_SET_SCCPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC55()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
 	   TEST_RESULT = 1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC55()
{
  return ;
}
I_Void fStkAddMCfgTC55(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC55();
  fStkAddMCfgStepsTC55();
  fStkAddMCfgPostTC55();
  return ;
}

/*----------------------------------TC56---------------------------------------------*/
I_Void  fStkAddMCfgPreTC56() 
{
  SccpTimerTableApi requestBuff = {2,30,90,30,30,90,10,20,300,660,240,10,30,10};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addSccpTimerTable(2,15,60,60);

  cfgStubSendCmMessage(&requestBuff, sizeof(SccpTimerTableApi), BSC_API_SET_SCCPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC56()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           LOG_PRINT(LOG_INFO,"CM_ERR_STACK_CONFIG_FAIL");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC56()
{
  return ;
}
I_Void fStkAddMCfgTC56(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC56();
  fStkAddMCfgStepsTC56();
  fStkAddMCfgPostTC56();
  return ;
}

/*----------------------------------TC57---------------------------------------------*/
I_Void  fStkAddMCfgPreTC57() 
{
  SccpTimerTableApi requestBuff = {2,30,90,30,30,90,10,20,300,660,240,10,30,10};
  LOG_PRINT(INFO,"%s:",__func__);
 
  addSccpTimerTable(2,15,60,60);
  cfgStubSendCmMessage(&requestBuff, sizeof(SccpTimerTableApi), BSC_API_SET_SCCPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC57()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC57()
{
  return ;
}
I_Void fStkAddMCfgTC57(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC57();
  fStkAddMCfgStepsTC57();
  fStkAddMCfgPostTC57();
  return ;
}

/*----------------------------------TC58---------------------------------------------*/
I_Void  fStkAddMCfgPreTC58() 
{
  SccpTimerTableApi requestBuff = {2,30,90,30,30,90,10,20,300,660,240,10,30,10};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addSccpTimerTable(2,15,60,60);
  cfgStubSendCmMessage(&requestBuff, sizeof(SccpTimerTableApi), BSC_API_SET_SCCPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC58()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TIMEOUT) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC58()
{
  return ;
}
I_Void fStkAddMCfgTC58(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC58();
  fStkAddMCfgStepsTC58();
  fStkAddMCfgPostTC58();
  return ;
}

/*----------------------------------TC59---------------------------------------------*/
I_Void  fStkAddMCfgPreTC59() 
{
  BssapTimerTableApi requestBuff = {2,2,4,25,5,10,5,5,5,10};
  LOG_PRINT(INFO,"%s:",__func__);

  cfgStubSendCmMessage(&requestBuff, sizeof(BssapTimerTableApi), BSC_API_SET_BSSAPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC59()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
 	   TEST_RESULT = 1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC59()
{
  return ;
}
I_Void fStkAddMCfgTC59(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC59();
  fStkAddMCfgStepsTC59();
  fStkAddMCfgPostTC59();
  return ;
}

/*----------------------------------TC60---------------------------------------------*/
I_Void  fStkAddMCfgPreTC60() 
{
  BssapTimerTableApi requestBuff = {2,2,4,25,5,10,5,5,5,10};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addInBssapTimerTable(2,7,8,9);
  cfgStubSendCmMessage(&requestBuff, sizeof(BssapTimerTableApi), BSC_API_SET_BSSAPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC60()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC60()
{
  return ;
}
I_Void fStkAddMCfgTC60(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC60();
  fStkAddMCfgStepsTC60();
  fStkAddMCfgPostTC60();
  return ;
}

/*----------------------------------TC61---------------------------------------------*/
I_Void  fStkAddMCfgPreTC61() 
{
  BssapTimerTableApi requestBuff = {2,2,4,25,5,10,5,5,5,10};
  LOG_PRINT(INFO,"%s:",__func__);
  

  addInBssapTimerTable(2,7,8,9);
  cfgStubSendCmMessage(&requestBuff, sizeof(BssapTimerTableApi), BSC_API_SET_BSSAPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC61()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC61()
{
  return ;
}
I_Void fStkAddMCfgTC61(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC61();
  fStkAddMCfgStepsTC61();
  fStkAddMCfgPostTC61();
  return ;
}

/*----------------------------------TC62---------------------------------------------*/
I_Void  fStkAddMCfgPreTC62() 
{
  BssapTimerTableApi requestBuff = {2,2,4,25,5,10,5,5,5,10};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addInBssapTimerTable(2,7,8,9);
  cfgStubSendCmMessage(&requestBuff, sizeof(BssapTimerTableApi), BSC_API_SET_BSSAPTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC62()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TIMEOUT) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC62()
{
  return ;
}
I_Void fStkAddMCfgTC62(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC62();
  fStkAddMCfgStepsTC62();
  fStkAddMCfgPostTC62();
  return ;
}

/*----------------------------------TC63---------------------------------------------*/
I_Void  fStkAddMCfgPreTC63() 
{
  LapdTimerTableApi requestBuff = {3,3,3,100,2};
  LOG_PRINT(INFO,"%s:",__func__);

  cfgStubSendCmMessage(&requestBuff, sizeof(LapdTimerTableApi), BSC_API_SET_LAPDTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC63()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
 	   TEST_RESULT = 1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC63()
{
  return ;
}
I_Void fStkAddMCfgTC63(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC63();
  fStkAddMCfgStepsTC63();
  fStkAddMCfgPostTC63();
  return ;
}

/*----------------------------------TC64---------------------------------------------*/
I_Void  fStkAddMCfgPreTC64() 
{
  LapdTimerTableApi requestBuff = {3,3,3,100,2};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addLapdTimerTable(1,4,5,7,2);

  cfgStubSendCmMessage(&requestBuff, sizeof(LapdTimerTableApi), BSC_API_SET_LAPDTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC64()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           LOG_PRINT(LOG_INFO,"CM_ERR_STACK_CONFIG_FAIL");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC64()
{
  return ;
}
I_Void fStkAddMCfgTC64(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC64();
  fStkAddMCfgStepsTC64();
  fStkAddMCfgPostTC64();
  return ;
}

/*----------------------------------TC65---------------------------------------------*/
I_Void  fStkAddMCfgPreTC65() 
{
  LapdTimerTableApi requestBuff = {3,3,3,100,2};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addLapdTimerTable(1,4,5,7,2);
  cfgStubSendCmMessage(&requestBuff, sizeof(LapdTimerTableApi), BSC_API_SET_LAPDTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC65()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC65()
{
  return ;
}
I_Void fStkAddMCfgTC65(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC65();
  fStkAddMCfgStepsTC65();
  fStkAddMCfgPostTC65();
  return ;
}

/*----------------------------------TC66---------------------------------------------*/
I_Void  fStkAddMCfgPreTC66() 
{
  LapdTimerTableApi requestBuff = {3,3,3,100,2};
  LOG_PRINT(INFO,"%s:",__func__);
  
  addLapdTimerTable(1,4,5,7,2);
  cfgStubSendCmMessage(&requestBuff, sizeof(LapdTimerTableApi), BSC_API_SET_LAPDTIMERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC66()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_TIMEOUT) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC66()
{
  return ;
}
I_Void fStkAddMCfgTC66(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC66();
  fStkAddMCfgStepsTC66();
  fStkAddMCfgPostTC66();
  return ;
}

/*----------------------------------TC67---------------------------------------------*/
I_Void  fStkAddMCfgPreTC67() 
{
  Ss7RouteTableApi requestBuff = {1, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_ABIS, 4,0xFE,0xFE, INTERNATIONAL, ENABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(1,1,3,INTERNATIONAL);
  
  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC67()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC67()
{
  return ;
}
I_Void fStkAddMCfgTC67(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC67();
  fStkAddMCfgStepsTC67();
  fStkAddMCfgPostTC67();
  return ;
}

/*----------------------------------TC68---------------------------------------------*/
I_Void  fStkAddMCfgPreTC68() 
{
  Ss7RouteTableApi requestBuff = {1, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4,0xF,0xFE, INTERNATIONAL, ENABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(1,1,3,INTERNATIONAL);
  
  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC68()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
           LOG_PRINT(LOG_INFO,"NACK: CM_ERR_PARAM_OUT_OF_RANGE");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC68()
{
  return ;
}
I_Void fStkAddMCfgTC68(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC68();
  fStkAddMCfgStepsTC68();
  fStkAddMCfgPostTC68();
  return ;
}

/*----------------------------------TC69---------------------------------------------*/
I_Void  fStkAddMCfgPreTC69() 
{
  Ss7RouteTableApi requestBuff = {1, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4,0xFE,0xFE, INTERNATIONAL, ENABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(2,1,3,NATIONAL);
  
  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC69()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_LINKSET_OBJ_NOT_PRESENT) {
           LOG_PRINT(LOG_INFO,"NACK: CM_ERR_LINKSET_OBJ_NOT_PRESENT");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC69()
{
  return ;
}
I_Void fStkAddMCfgTC69(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC69();
  fStkAddMCfgStepsTC69();
  fStkAddMCfgPostTC69();
  return ;
}

/*----------------------------------TC70---------------------------------------------*/
I_Void  fStkAddMCfgPreTC70() 
{
  Ss7RouteTableApi requestBuff = {51, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4,0xFE,0xFE, INTERNATIONAL, DISABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(51,1,3,NATIONAL);
  
  addToSs7RouteTable(51,1);

  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC70()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC70()
{
  return ;
}
I_Void fStkAddMCfgTC70(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC70();
  fStkAddMCfgStepsTC70();
  fStkAddMCfgPostTC70();
  return ;
}

/*----------------------------------TC71---------------------------------------------*/
I_Void  fStkAddMCfgPreTC71() 
{
  Ss7RouteTableApi requestBuff = {25, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4,0xFE,0xFE, INTERNATIONAL, ENABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(25,1,3,NATIONAL);
  
  addToSs7RouteTable(25,1);

  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC71()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC71()
{
  return ;
}
I_Void fStkAddMCfgTC71(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC71();
  fStkAddMCfgStepsTC71();
  fStkAddMCfgPostTC71();
  return ;
}

/*----------------------------------TC72---------------------------------------------*/
I_Void  fStkAddMCfgPreTC72() 
{
  Ss7RouteTableApi requestBuff = {25, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 3,0xFE,0xFE, INTERNATIONAL, ENABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(25,1,3,INTERNATIONAL);
  
  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC72()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"ACK: CM_SUCCESS");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC72()
{
  return ;
}
I_Void fStkAddMCfgTC72(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC72();
  fStkAddMCfgStepsTC72();
  fStkAddMCfgPostTC72();
  return ;
}

/*----------------------------------TC73---------------------------------------------*/
I_Void  fStkAddMCfgPreTC73() 
{
  Ss7RouteTableApi requestBuff = {25, 2,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 3,0xFE,0xFE, NATIONAL, DISABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(25,1,3,NATIONAL);
  
  addToSs7RouteTable(25,2);

  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC73()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
           LOG_PRINT(LOG_INFO,"NACK: CM_ERR_OPERATION_NOT_ALLOWED");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC73()
{
  return ;
}
I_Void fStkAddMCfgTC73(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC73();
  fStkAddMCfgStepsTC73();
  fStkAddMCfgPostTC73();
  return ;
}

/*----------------------------------TC74---------------------------------------------*/
I_Void  fStkAddMCfgPreTC74() 
{
  Ss7RouteTableApi requestBuff = {25, 2,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 3,0xFE,0xFE, NATIONAL, DISABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(25,1,3,NATIONAL);
  
  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC74()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           LOG_PRINT(LOG_INFO,"ACK: CM_ERR_STACK_CONFIG_FAIL");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC74()
{
  return ;
}
I_Void fStkAddMCfgTC74(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC74();
  fStkAddMCfgStepsTC74();
  fStkAddMCfgPostTC74();
  return ;
}

/*----------------------------------TC75---------------------------------------------*/
I_Void  fStkAddMCfgPreTC75() 
{
  Ss7RouteTableApi requestBuff = {25, 2,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4,0xFE,0xFE, INTERNATIONAL, ENABLE,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(25,1,3,NATIONAL);
  
  addToSs7RouteTable(25,2);

  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC75()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {  
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
           LOG_PRINT(LOG_INFO,"ACK: CM_ERR_STACK_CONFIG_FAIL");
           TEST_RESULT = 1;
        }
        return;
        default:;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC75()
{
  return ;
}
I_Void fStkAddMCfgTC75(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC75();
  fStkAddMCfgStepsTC75();
  fStkAddMCfgPostTC75();
  return ;
}

/*----------------------------------TC76---------------------------------------------*/
I_Void  fStkAddMCfgPreTC76() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  addRowInBssTable(1, UNLOCKED);
  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC76()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_BSS_NOT_LOCKED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC76()
{
  return ;
}
I_Void fStkAddMCfgTC76(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC76();
  fStkAddMCfgStepsTC76();
  fStkAddMCfgPostTC76();
  return ;
}

/*----------------------------------TC77---------------------------------------------*/
I_Void  fStkAddMCfgPreTC77() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  addRowInBssTable(1, LOCKED);
  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC77()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC77()
{
  return ;
}
I_Void fStkAddMCfgTC77(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC77();
  fStkAddMCfgStepsTC77();
  fStkAddMCfgPostTC77();
  return ;
}

/*----------------------------------TC78---------------------------------------------*/
I_Void  fStkAddMCfgPreTC78() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,1,3); 
  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 1;

  addRowInBssTable(1, LOCKED);

  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC78()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC78()
{
  return ;
}
I_Void fStkAddMCfgTC78(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC78();
  fStkAddMCfgStepsTC78();
  fStkAddMCfgPostTC78();
  return ;
}

/*----------------------------------TC79---------------------------------------------*/
I_Void  fStkAddMCfgPreTC79() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,2,3); 
  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  addRowInBssTable(1, LOCKED);

  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC79()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC79()
{
  return ;
}
I_Void fStkAddMCfgTC79(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC79();
  fStkAddMCfgStepsTC79();
  fStkAddMCfgPostTC79();
  return ;
}

/*----------------------------------TC80---------------------------------------------*/
I_Void  fStkAddMCfgPreTC80() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7StackConfigTable(1,2,3); 
  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 2;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  addRowInBssTable(1, LOCKED);

  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC80()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_FAIL;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_STACK_CONFIG_FAIL) {
          TEST_RESULT=1;
        }
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC80()
{
  return ;
}
I_Void fStkAddMCfgTC80(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC80();
  fStkAddMCfgStepsTC80();
  fStkAddMCfgPostTC80();
  return ;
}

/*----------------------------------TC81---------------------------------------------*/
I_Void  fStkAddMCfgPreTC81() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addCicTable(1,1,0,16,10,LOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 10;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = UNLOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC81()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC81()
{
  return ;
}
I_Void fStkAddMCfgTC81(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC81();
  fStkAddMCfgStepsTC81();
  fStkAddMCfgPostTC81();
  return ;
}

/*----------------------------------TC82---------------------------------------------*/
I_Void  fStkAddMCfgPreTC82() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addCicTable(1,1,0,16,10,UNLOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 0;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 10;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = LOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC82()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC82()
{
  return ;
}
I_Void fStkAddMCfgTC82(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC82();
  fStkAddMCfgStepsTC82();
  fStkAddMCfgPostTC82();
  return ;
}

/*----------------------------------TC83---------------------------------------------*/
I_Void  fStkAddMCfgPreTC83() 
{
  BssTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInBssTable(1,0); 
  addSwMNodeTable(1);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,UNLOCKED);

  requestBuff.bscId = 1;
  requestBuff.adminState = 1;
  requestBuff.bssReset = 0;
  requestBuff.gprsEnabled = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BssTableApi), BSC_API_SET_BSSTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC83()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           cfgStubSendScmCfgAlarmInd(SSA_MSG_RECV_REM_SUBSYSTEM);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(INFO, "Rcvd  CM_SUCCESS" );
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           if (sysAlarmPtr->sysAlarm.sysalarmId == BSS_UNLOCKED) {
           TEST_RESULT=1;
           return;  
           }
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC83()
{
  return ;
}
I_Void fStkAddMCfgTC83(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC83();
  fStkAddMCfgStepsTC83();
  fStkAddMCfgPostTC83();
  return ;
}

/*----------------------------------TC84---------------------------------------------*/
I_Void  fStkAddMCfgPreTC84() 
{
  BssTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInBssTable(1,1); 
  addSwMNodeTable(1);
  addLinkTable(1,1,1,0,16,1,CRC_ENABLE,UNLOCKED);

  requestBuff.bscId = 1;
  requestBuff.adminState = 0;
  requestBuff.bssReset = 0;
  requestBuff.gprsEnabled = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BssTableApi), BSC_API_SET_BSSTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC84()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           cfgStubSendScmCfgAlarmInd(SSP_MSG_RECV_REM_SUBSYSTEM);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_GRHM_LOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(INFO, "Rcvd  CM_SUCCESS" );
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           if (sysAlarmPtr->sysAlarm.sysalarmId == BSS_LOCKED) {
           TEST_RESULT=1;
           return;  
           }
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC84()
{
  return ;
}
I_Void fStkAddMCfgTC84(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC84();
  fStkAddMCfgStepsTC84();
  fStkAddMCfgPostTC84();
  return ;
}

/*----------------------------------TC85---------------------------------------------*/
I_Void  fStkAddMCfgPreTC85() 
{
  E1PerTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,0,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addLinkTable(1,1,1,5,16,1,CRC_ENABLE,UNLOCKED);
  addCicTable(1,1,5,11,10,UNLOCKED);
  addCicTable(1,1,5,12,11,UNLOCKED);
  addCicTable(1,1,5,13,12,UNLOCKED);
  addCicTable(1,1,5,14,13,UNLOCKED);
  addCicTable(1,1,5,15,14,UNLOCKED);
  requestBuff.e1Num = 5;
  requestBuff.adminState = 1;
  requestBuff.usageType = SYS_E1_USAGE_AIF;
  requestBuff.usingEntity = INVALID;
  requestBuff.mapAction = 2;
  requestBuff.e1Category = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(E1PerTableApi), BSC_API_SET_E1PERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC85()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(INFO, "Rcvd  CM_SUCCESS" );
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           if (sysAlarmPtr->sysAlarm.sysalarmId == E1_UNLOCKED) {
           TEST_RESULT=1;
           return;  
           }
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC85()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC85(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC85();
  fStkAddMCfgStepsTC85();
  fStkAddMCfgPostTC85();
  return ;
}

/*----------------------------------TC86---------------------------------------------*/
I_Void  fStkAddMCfgPreTC86() 
{
  E1PerTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addLinkTable(1,1,1,5,16,1,CRC_ENABLE,UNLOCKED);
  addCicTable(1,1,5,11,10,UNLOCKED);
  addCicTable(1,1,5,12,11,UNLOCKED);
  addCicTable(1,1,5,13,12,UNLOCKED);
  addCicTable(1,1,5,14,13,UNLOCKED);
  addCicTable(1,1,5,15,14,UNLOCKED);
  requestBuff.e1Num = 5;
  requestBuff.adminState = 0;
  requestBuff.usageType = SYS_E1_USAGE_AIF;
  requestBuff.usingEntity = 0;
  requestBuff.mapAction = 2;
  requestBuff.e1Category = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(E1PerTableApi), BSC_API_SET_E1PERTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC86()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_GRHM_LOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(INFO, "Rcvd  CM_SUCCESS" );
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           if (sysAlarmPtr->sysAlarm.sysalarmId == E1_LOCKED) {
           TEST_RESULT=1;
           return;  
           }
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC86()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC86(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC86();
  fStkAddMCfgStepsTC86();
  fStkAddMCfgPostTC86();
  return ;
}

/*----------------------------------TC87---------------------------------------------*/
I_Void  fStkAddMCfgPreTC87() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addLinkTable(1,20,1,5,16,1,CRC_ENABLE,LOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 20;
  requestBuff.slc = 1;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = UNLOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC87()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
        }
        break;
      case OAMS_CFG_AFH_ALARM_IND:
         LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
         OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
         LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
         LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
         LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
         LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
         LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
         LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
         TEST_RESULT=1;
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC87()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC87(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC87();
  fStkAddMCfgStepsTC87();
  fStkAddMCfgPostTC87();
  return ;
}

/*----------------------------------TC88---------------------------------------------*/
I_Void  fStkAddMCfgPreTC88() 
{
  LinkTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addLinkTable(1,21,1,5,16,1,CRC_ENABLE,UNLOCKED);
  requestBuff.linksetID = 1;
  requestBuff.linkId = 21;
  requestBuff.slc = 1;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cardNum = 1;
  requestBuff.crcFlag = CRC_ENABLE;
  requestBuff.adminState = LOCKED;

  cfgStubSendCmMessage(&requestBuff, sizeof(LinkTableApi), BSC_API_SET_LINKTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC88()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_OIL_SCM_MSG_REQ:
           scmRespAction = ALL_OK;
           ExecuteOilAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"CM_SUCCESS");
        }
        break;
      case OAMS_CFG_AFH_ALARM_IND:
         LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
         OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
         LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
         LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
         LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
         LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
         LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
         LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
         TEST_RESULT=1;
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC88()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC88(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC88();
  fStkAddMCfgStepsTC88();
  fStkAddMCfgPostTC88();
  return ;
}

/*----------------------------------TC89---------------------------------------------*/
I_Void  fStkAddMCfgPreTC89() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addCicTable(1,1,5,16,21,LOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 21;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = UNLOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC89()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC89()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC89(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC89();
  fStkAddMCfgStepsTC89();
  fStkAddMCfgPostTC89();
  return ;
}

/*----------------------------------TC90---------------------------------------------*/
I_Void  fStkAddMCfgPreTC90() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addCicTable(1,1,5,16,20,UNLOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 20;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = LOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC90()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_LOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           }
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC90()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC90(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC90();
  fStkAddMCfgStepsTC90();
  fStkAddMCfgPostTC90();
  return ;
}

/*----------------------------------TC91---------------------------------------------*/
I_Void  fStkAddMCfgPreTC91() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetStatusTable(10,ENABLED);
  cfgStubSendAlarm(ALARM_ID_MSC_LINKSET_OOS,10,0,0,0);
  return ;
}
I_Void  fStkAddMCfgStepsTC91()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) { 
       case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"Key2 : %d ",sysAlarmPtr->sysAlarm.key2);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);  
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC91()
{
  return ;
}
I_Void fStkAddMCfgTC91(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC91();
  fStkAddMCfgStepsTC91();
  fStkAddMCfgPostTC91();
  return ;
}

/*----------------------------------TC92---------------------------------------------*/
I_Void  fStkAddMCfgPreTC92() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  addLinksetStatusTable(10,DISABLED);
  cfgStubSendAlarm(ALARM_ID_MSC_LINKSET_INS,10,0,0,0);
  return ;
}
I_Void  fStkAddMCfgStepsTC92()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) { 
       case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"Key2 : %d ",sysAlarmPtr->sysAlarm.key2);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);  
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC92()
{
  return ;
}
I_Void fStkAddMCfgTC92(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC92();
  fStkAddMCfgStepsTC92();
  fStkAddMCfgPostTC92();
  return ;
}

/*----------------------------------TC93---------------------------------------------*/
I_Void  fStkAddMCfgPreTC93() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  addLinkStatusTable(10,20,ENABLED);
  cfgStubSendAlarm(ALARM_ID_MSC_LINK_OOS,10,20,0,0);
  return ;
}
I_Void  fStkAddMCfgStepsTC93()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) { 
       case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"Key2 : %d ",sysAlarmPtr->sysAlarm.key2);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);  
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC93()
{
  return ;
}
I_Void fStkAddMCfgTC93(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC93();
  fStkAddMCfgStepsTC93();
  fStkAddMCfgPostTC93();
  return ;
}

/*----------------------------------TC94---------------------------------------------*/
I_Void  fStkAddMCfgPreTC94() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  addLinkStatusTable(10,20,DISABLED);
  cfgStubSendAlarm(ALARM_ID_MSC_LINK_INS,10,20,0,0);
  return ;
}
I_Void  fStkAddMCfgStepsTC94()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) { 
       case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"Key2 : %d ",sysAlarmPtr->sysAlarm.key2);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);  
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC94()
{
  return ;
}
I_Void fStkAddMCfgTC94(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC94();
  fStkAddMCfgStepsTC94();
  fStkAddMCfgPostTC94();
  return ;
}

/*----------------------------------TC95---------------------------------------------*/
I_Void  fStkAddMCfgPreTC95() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7RouteStatusTable(10,20,ENABLED);
  addSs7RouteStatusTable(10,30,ENABLED);
  addToSs7RouteTable(10,20);
  addToSs7RouteTable(10,30);
  cfgStubSendAlarm(ALARM_ID_DEST_UNAVAILABLE_MTP3_PAUSE,1331,0,0,0);
  return ;
}
I_Void  fStkAddMCfgStepsTC95()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) { 
       case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"Key2 : %d ",sysAlarmPtr->sysAlarm.key2);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);  
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC95()
{
  return ;
}
I_Void fStkAddMCfgTC95(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC95();
  fStkAddMCfgStepsTC95();
  fStkAddMCfgPostTC95();
  return ;
}

/*----------------------------------TC96---------------------------------------------*/
I_Void  fStkAddMCfgPreTC96() 
{
  LOG_PRINT(INFO,"%s:",__func__);

  addSs7RouteStatusTable(10,20,DISABLED);
  addSs7RouteStatusTable(10,30,DISABLED);
  addToSs7RouteTable(10,20);
  addToSs7RouteTable(10,30);
  cfgStubSendAlarm(ALARM_ID_DEST_AVAILABLE_MTP3_RESUME,1331,0,0,0);
  return ;
}
I_Void  fStkAddMCfgStepsTC96()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) { 
       case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
           OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)RCVD_MSG_PTR;
           LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
           LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
           LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
           LOG_PRINT(LOG_INFO,"Key2 : %d ",sysAlarmPtr->sysAlarm.key2);
           LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
           LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
           LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);  
           TEST_RESULT=1;
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC96()
{
  return ;
}
I_Void fStkAddMCfgTC96(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC96();
  fStkAddMCfgStepsTC96();
  fStkAddMCfgPostTC96();
  return ;
}

/*----------------------------------TC97---------------------------------------------*/
I_Void  fStkAddMCfgPreTC97() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 0;
  //requestBuff.interfaceId = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC97()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC97()
{
  return ;
}
I_Void fStkAddMCfgTC97(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC97();
  fStkAddMCfgStepsTC97();
  fStkAddMCfgPostTC97();
  return ;
}

/*----------------------------------TC98---------------------------------------------*/
#if 0
I_Void  fStkAddMCfgPreTC98() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  addAbisInterfaceTable(1,1,IF_TYPE_ABIS);
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 0;
  //requestBuff.interfaceId = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
#endif
I_Void  fStkAddMCfgStepsTC98()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_VALID_BIC_IN_ABIS_INTERFACE) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC98()
{
  return ;
}
I_Void fStkAddMCfgTC98(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  //fStkAddMCfgPreTC98();
  //fStkAddMCfgStepsTC98();
  //fStkAddMCfgPostTC98();
  return ;
}

/*----------------------------------TC99---------------------------------------------*/
I_Void  fStkAddMCfgPreTC99() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 21;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = UNLOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC99()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_ENTRY_NOT_PRES_IN_DB) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC99()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC99(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC99();
  fStkAddMCfgStepsTC99();
  fStkAddMCfgPostTC99();
  return ;
}

/*----------------------------------TC100---------------------------------------------*/
I_Void  fStkAddMCfgPreTC100() 
{
  Ss7RouteTableApi requestBuff = {1, 1,"Ss7 Route", DPC_SIO, 1331, IF_TYPE_AIF, 4,0xFE,0xFE, INTERNATIONAL, 7,UNLOCKED};
  LOG_PRINT(INFO,"%s:",__func__);
  addLinksetTable(1,1,3,INTERNATIONAL);
  addToSs7RouteTable(51,1);
  cfgStubSendCmMessage(&requestBuff, sizeof(Ss7RouteTableApi), BSC_API_SET_SS7ROUTETABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC100()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC100()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC100(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC100();
  fStkAddMCfgStepsTC100();
  fStkAddMCfgPostTC100();
  return ;
}

/*----------------------------------TC101---------------------------------------------*/
I_Void  fStkAddMCfgPreTC101() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addCicTable(1,1,5,16,21,LOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 21;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = 3;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC101()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_REQUEST) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC101()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC101(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC101();
  fStkAddMCfgStepsTC101();
  fStkAddMCfgPostTC101();
  return ;
}

/*----------------------------------TC102---------------------------------------------*/
I_Void  fStkAddMCfgPreTC102() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInE1PerTable(5,1,SYS_E1_USAGE_AIF,INVALID,2,0); 
  addCicTable(1,1,5,16,21,LOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 23;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = LOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC102()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_OPERATION_NOT_ALLOWED) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC102()
{
  deleteRowFromE1PerTable(5);
  return ;
}
I_Void fStkAddMCfgTC102(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC102();
  fStkAddMCfgStepsTC102();
  fStkAddMCfgPostTC102();
  return ;
}

/*----------------------------------TC103---------------------------------------------*/
I_Void  fStkAddMCfgPreTC103() 
{
  CicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);

  deleteRowFromE1PerTable(5);
  addCicTable(1,1,5,16,21,LOCKED);
  requestBuff.interfaceId = 1;
  requestBuff.tgpId = DEFAULT_TGPID;
  requestBuff.e1Num = 5;
  requestBuff.timeSlot = 16;
  requestBuff.cicId = 21;
  requestBuff.usage = SIGNALLING;
  requestBuff.adminState = UNLOCKED;
  requestBuff.reset = NO_RESET;

  cfgStubSendCmMessage(&requestBuff, sizeof(CicTableApi), BSC_API_SET_CICTABLE);
  return ;
}
I_Void  fStkAddMCfgStepsTC103()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_UNLOCK_REQ:
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break; 
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_NOT_PRESENT_IN_DB) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC103()
{
  return ;
}
I_Void fStkAddMCfgTC103(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC103();
  fStkAddMCfgStepsTC103();
  fStkAddMCfgPostTC103();
  return ;
}

/*----------------------------------TC104---------------------------------------------*/
I_Void  fStkAddMCfgPreTC104() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 1;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC104()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_GET_DB_OPER_FAILED) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC104()
{
  return ;
}
I_Void fStkAddMCfgTC104(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC104();
  fStkAddMCfgStepsTC104();
  fStkAddMCfgPostTC104();
  return ;
}

/*----------------------------------TC105---------------------------------------------*/
I_Void  fStkAddMCfgPreTC105() 
{
  Ss7StackConfigTableApi Ss7StackConfigTableApiBuf;
  LOG_PRINT(INFO,"%s:",__func__);

  addRowInBssTable(1, LOCKED);
  Ss7StackConfigTableApiBuf.index = 1;
  Ss7StackConfigTableApiBuf.sksCommonopc = 0;
  Ss7StackConfigTableApiBuf.sksCommonfamily = 1;
  Ss7StackConfigTableApiBuf.alarmLevel = 2;

  cfgStubSendCmMessage(&Ss7StackConfigTableApiBuf, sizeof(Ss7StackConfigTableApi), BSC_API_SET_SS7STACKCONFIGTABLE);
 return ;
}
I_Void  fStkAddMCfgStepsTC105()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_PARAM_OUT_OF_RANGE) {
           TEST_RESULT=1;
           }
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fStkAddMCfgPostTC105()
{
  return ;
}
I_Void fStkAddMCfgTC105(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fStkAddMCfgPreTC105();
  fStkAddMCfgStepsTC105();
  fStkAddMCfgPostTC105();
  return ;
}

/*-----------------------------------------------------------------------*/
I_PU8 stkAddModTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
    case TEST_CASE_STK_ADDM_CFG_ALL:
      return "ALL HA STK CFG TCs";
    case TEST_CASE1_STK_ADDM_CFG:
      return "HA STK CFG TC 1";
    case TEST_CASE2_STK_ADDM_CFG:
      return "HA STK CFG TC 2";
    case TEST_CASE3_STK_ADDM_CFG:
      return "HA STK CFG TC 3";
    case TEST_CASE4_STK_ADDM_CFG:
      return "HA STK CFG TC 4";      
    case TEST_CASE5_STK_ADDM_CFG:
      return "HA STK CFG TC 5"; 
    case TEST_CASE6_STK_ADDM_CFG:
      return "HA STK CFG TC 6";    
    case TEST_CASE7_STK_ADDM_CFG:
      return "HA STK CFG TC 7";    
    case TEST_CASE8_STK_ADDM_CFG:
      return "HA STK CFG TC 8";        
    case TEST_CASE9_STK_ADDM_CFG:
      return "HA STK CFG TC 9";    
    case TEST_CASE10_STK_ADDM_CFG:
      return "HA STK CFG TC10";     
    case TEST_CASE11_STK_ADDM_CFG:
      return "HA STK CFG TC11";        
    case TEST_CASE12_STK_ADDM_CFG:
      return "HA STK CFG TC12";        
    case TEST_CASE13_STK_ADDM_CFG:
      return "HA STK CFG TC13";        
    case TEST_CASE14_STK_ADDM_CFG:
      return "HA STK CFG TC14";        
    case TEST_CASE15_STK_ADDM_CFG:
      return "HA STK CFG TC15";        
    case TEST_CASE16_STK_ADDM_CFG:
      return "HA STK CFG TC16";        
    case TEST_CASE17_STK_ADDM_CFG:
      return "HA STK CFG TC17";        
    case TEST_CASE18_STK_ADDM_CFG:
      return "HA STK CFG TC18";        
    case TEST_CASE19_STK_ADDM_CFG:
      return "HA STK CFG TC19";        
    case TEST_CASE20_STK_ADDM_CFG:
      return "HA STK CFG TC20";        
    case TEST_CASE21_STK_ADDM_CFG:
      return "HA STK CFG TC21";        
    case TEST_CASE22_STK_ADDM_CFG:
      return "HA STK CFG TC22";        
    case TEST_CASE23_STK_ADDM_CFG:
      return "HA STK CFG TC23";        
    case TEST_CASE24_STK_ADDM_CFG:
      return "HA STK CFG TC24";        
    case TEST_CASE25_STK_ADDM_CFG:
      return "HA STK CFG TC25";        
    case TEST_CASE26_STK_ADDM_CFG:
      return "HA STK CFG TC26";        
    case TEST_CASE27_STK_ADDM_CFG:
      return "HA STK CFG TC27";        
    case TEST_CASE28_STK_ADDM_CFG:
      return "HA STK CFG TC28";        
    case TEST_CASE29_STK_ADDM_CFG:
      return "HA STK CFG TC29";        
    case TEST_CASE30_STK_ADDM_CFG:
      return "HA STK CFG TC30";        
    case TEST_CASE31_STK_ADDM_CFG:
      return "HA STK CFG TC31";        
    case TEST_CASE32_STK_ADDM_CFG:
      return "HA STK CFG TC32";        
    case TEST_CASE33_STK_ADDM_CFG:
      return "HA STK CFG TC33";        
    case TEST_CASE34_STK_ADDM_CFG:
      return "HA STK CFG TC34";        
    case TEST_CASE35_STK_ADDM_CFG:
      return "HA STK CFG TC35";        
    case TEST_CASE36_STK_ADDM_CFG:
      return "HA STK CFG TC36";        
    case TEST_CASE37_STK_ADDM_CFG:
      return "HA STK CFG TC37";        
    case TEST_CASE38_STK_ADDM_CFG:
      return "HA STK CFG TC38";        
    case TEST_CASE39_STK_ADDM_CFG:
      return "HA STK CFG TC39";        
    case TEST_CASE40_STK_ADDM_CFG:
      return "HA STK CFG TC40";        
    case TEST_CASE41_STK_ADDM_CFG:
      return "HA STK CFG TC41";        
    case TEST_CASE42_STK_ADDM_CFG:
      return "HA STK CFG TC42";        
    case TEST_CASE43_STK_ADDM_CFG:
      return "HA STK CFG TC43";        
    case TEST_CASE44_STK_ADDM_CFG:
      return "HA STK CFG TC44";        
    case TEST_CASE45_STK_ADDM_CFG:
      return "HA STK CFG TC45";        
    case TEST_CASE46_STK_ADDM_CFG:
      return "HA STK CFG TC46";        
    case TEST_CASE47_STK_ADDM_CFG:
      return "HA STK CFG TC47";        
    case TEST_CASE48_STK_ADDM_CFG:
      return "HA STK CFG TC48";        
    case TEST_CASE49_STK_ADDM_CFG:
      return "HA STK CFG TC49";        
    case TEST_CASE50_STK_ADDM_CFG:
      return "HA STK CFG TC50";
    case TEST_CASE51_STK_ADDM_CFG:
      return "HA STK CFG TC51"; 
    case TEST_CASE52_STK_ADDM_CFG:
      return "HA STK CFG TC52";
    case TEST_CASE53_STK_ADDM_CFG:
      return "HA STK CFG TC53";
    case TEST_CASE54_STK_ADDM_CFG:
      return "HA STK CFG TC54";        
    case TEST_CASE55_STK_ADDM_CFG:
      return "HA STK CFG TC55"; 
    case TEST_CASE56_STK_ADDM_CFG:
      return "HA STK CFG TC56"; 
    case TEST_CASE57_STK_ADDM_CFG:
      return "HA STK CFG TC57";
    case TEST_CASE58_STK_ADDM_CFG:
      return "HA STK CFG TC58";
    case TEST_CASE59_STK_ADDM_CFG:
      return "HA STK CFG TC59"; 
    case TEST_CASE60_STK_ADDM_CFG:
      return "HA STK CFG TC60"; 
    case TEST_CASE61_STK_ADDM_CFG:
      return "HA STK CFG TC61";
    case TEST_CASE62_STK_ADDM_CFG:
      return "HA STK CFG TC62";
    case TEST_CASE63_STK_ADDM_CFG:
      return "HA STK CFG TC63"; 
    case TEST_CASE64_STK_ADDM_CFG:
      return "HA STK CFG TC64"; 
    case TEST_CASE65_STK_ADDM_CFG:
      return "HA STK CFG TC65";
    case TEST_CASE66_STK_ADDM_CFG:
      return "HA STK CFG TC66";        
    case TEST_CASE67_STK_ADDM_CFG:
      return "HA STK CFG TC67";
    case TEST_CASE68_STK_ADDM_CFG:
      return "HA STK CFG TC68";
    case TEST_CASE69_STK_ADDM_CFG:
      return "HA STK CFG TC69"; 
    case TEST_CASE70_STK_ADDM_CFG:
      return "HA STK CFG TC70"; 
    case TEST_CASE71_STK_ADDM_CFG:
      return "HA STK CFG TC71";
    case TEST_CASE72_STK_ADDM_CFG:
      return "HA STK CFG TC72";
    case TEST_CASE73_STK_ADDM_CFG:
      return "HA STK CFG TC73";
    case TEST_CASE74_STK_ADDM_CFG:
      return "HA STK CFG TC74";
    case TEST_CASE75_STK_ADDM_CFG:
      return "HA STK CFG TC75";
    case TEST_CASE76_STK_ADDM_CFG:
      return "HA STK CFG TC76";
    case TEST_CASE77_STK_ADDM_CFG:
      return "HA STK CFG TC77";
    case TEST_CASE78_STK_ADDM_CFG:
      return "HA STK CFG TC78";
    case TEST_CASE79_STK_ADDM_CFG:
      return "HA STK CFG TC79";
    case TEST_CASE80_STK_ADDM_CFG:
      return "HA STK CFG TC80";
    case TEST_CASE81_STK_ADDM_CFG:
      return "HA STK CFG TC81"; 
    case TEST_CASE82_STK_ADDM_CFG:
      return "HA STK CFG TC82";
    case TEST_CASE83_STK_ADDM_CFG:
      return "HA STK CFG TC83";
    case TEST_CASE84_STK_ADDM_CFG:
      return "HA STK CFG TC84";        
    case TEST_CASE85_STK_ADDM_CFG:
      return "HA STK CFG TC85"; 
    case TEST_CASE86_STK_ADDM_CFG:
      return "HA STK CFG TC86"; 
    case TEST_CASE87_STK_ADDM_CFG:
      return "HA STK CFG TC87";
    case TEST_CASE88_STK_ADDM_CFG:
      return "HA STK CFG TC88";
    case TEST_CASE89_STK_ADDM_CFG:
      return "HA STK CFG TC89"; 
    case TEST_CASE90_STK_ADDM_CFG:
      return "HA STK CFG TC90";  
    case TEST_CASE91_STK_ADDM_CFG:
      return "HA STK CFG TC91"; 
    case TEST_CASE92_STK_ADDM_CFG:
      return "HA STK CFG TC92";
    case TEST_CASE93_STK_ADDM_CFG:
      return "HA STK CFG TC93";
    case TEST_CASE94_STK_ADDM_CFG:
      return "HA STK CFG TC94";        
    case TEST_CASE95_STK_ADDM_CFG:
      return "HA STK CFG TC95"; 
    case TEST_CASE96_STK_ADDM_CFG:
      return "HA STK CFG TC96"; 
    case TEST_CASE97_STK_ADDM_CFG:
      return "HA STK CFG TC97";
    case TEST_CASE98_STK_ADDM_CFG:
      return "HA STK CFG TC98";
    case TEST_CASE99_STK_ADDM_CFG:
      return "HA STK CFG TC99"; 
    case TEST_CASE100_STK_ADDM_CFG:
      return "HA STK CFG TC100";  
    case TEST_CASE101_STK_ADDM_CFG:
      return "HA STK CFG TC101";  
    case TEST_CASE102_STK_ADDM_CFG:
      return "HA STK CFG TC102";  
    case TEST_CASE103_STK_ADDM_CFG:
      return "HA STK CFG TC103";  
    case TEST_CASE104_STK_ADDM_CFG:
      return "HA STK CFG TC104";  
    case TEST_CASE105_STK_ADDM_CFG:
      return "HA STK CFG TC105";  
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    
  }
  return NULL;
}

I_Void ExecuteStkAddModGroup(I_U32 testCaseId) 
{
  switch (testCaseId) {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    case TEST_CASE_STK_ADDM_CFG_ALL:
    case TEST_CASE1_STK_ADDM_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE1_STK_ADDM_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);      
      // fStkAddMCfgTC1();
      //PRINT_TEST_RESULT();      
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE2_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE2_STK_ADDM_CFG;  
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC2();    
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE3_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE3_STK_ADDM_CFG;   
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC3();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE4_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE4_STK_ADDM_CFG;    
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      // fStkAddMCfgTC4();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }       
    case TEST_CASE5_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE5_STK_ADDM_CFG;
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC5();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }    
    case TEST_CASE6_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE6_STK_ADDM_CFG;    
      TEST_RESULT=0;   
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC6();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE7_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE7_STK_ADDM_CFG;  
      TEST_RESULT=0; 
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC7();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }        
    case TEST_CASE8_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE8_STK_ADDM_CFG;  
      TEST_RESULT=0;   
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC8();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }     
    case TEST_CASE9_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE9_STK_ADDM_CFG;   
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC9();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }      
    case TEST_CASE10_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE10_STK_ADDM_CFG;    
      TEST_RESULT=0;  
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC10();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE11_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE11_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC11();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
    case TEST_CASE12_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE12_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC12();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      } 
     case TEST_CASE13_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE13_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC13();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
     case TEST_CASE14_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE14_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC14();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE15_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE15_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC15();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE16_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE16_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC16();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE17_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE17_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC17();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE18_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE18_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC18();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE19_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE19_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC19();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE20_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE20_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC20();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE21_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE21_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC21();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE22_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE22_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC22();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE23_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE23_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC23();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE24_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE24_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC24();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE25_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE25_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC25();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE26_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE26_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC26();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE27_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE27_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC27();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE28_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE28_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC28();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE29_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE29_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC29();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE30_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE30_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC30();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE31_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE31_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC31();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE32_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE32_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC32();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE33_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE33_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC33();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE34_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE34_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC34();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE35_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE35_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC35();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE36_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE36_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC36();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE37_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE37_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC37();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE38_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE38_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC38();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE39_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE39_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC39();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE40_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE40_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC40();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE41_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE41_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC41();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE42_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE42_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC42();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE43_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE43_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC43();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE44_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE44_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC44();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE45_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE45_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC45();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE46_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE46_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC46();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE47_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE47_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC47();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE48_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE48_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC48();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE49_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE49_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC49();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE50_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE50_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC50();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE51_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE51_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC51();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE52_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE52_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC52();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE53_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE53_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC53();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE54_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE54_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC54();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE55_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE55_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC55();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE56_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE56_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC56();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE57_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE57_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC57();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE58_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE58_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC58();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE59_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE59_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC59();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE60_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE60_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC60();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE61_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE61_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC61();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE62_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE62_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC62();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE63_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE63_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC63();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE64_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE64_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC64();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE65_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE65_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC65();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE66_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE66_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC66();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE67_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE67_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC67();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE68_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE68_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC68();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE69_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE69_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC69();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE70_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE70_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC70();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE71_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE71_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC71();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE72_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE72_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC72();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE73_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE73_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC73();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE74_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE74_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC74();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE75_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE75_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC75();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE76_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE76_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC76();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE77_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE77_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC77();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE78_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE78_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC78();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE79_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE79_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC79();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE80_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE80_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC80();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE81_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE81_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC81();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE82_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE82_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC82();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE83_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE83_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC83();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE84_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE84_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC84();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE85_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE85_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC85();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE86_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE86_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC86();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE87_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE87_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC87();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE88_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE88_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC88();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE89_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE89_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC89();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE90_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE90_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC90();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE91_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE91_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC91();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE92_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE92_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC92();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE93_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE93_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC93();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE94_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE94_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC94();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE95_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE95_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC95();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE96_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE96_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC96();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }  
      case TEST_CASE97_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE97_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC97();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE98_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE98_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Removed TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      //fStkAddMCfgTC98();
      //PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }
      case TEST_CASE99_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE99_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC99();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE100_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE100_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC100();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE101_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE101_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC101();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE102_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE102_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC102();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE103_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE103_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC103();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE104_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE104_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC104();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
      case TEST_CASE105_STK_ADDM_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanDB();
      TEST_CASE_ID = TEST_CASE105_STK_ADDM_CFG;  
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fStkAddMCfgTC105();
      PRINT_TEST_RESULT();
      if (TEST_CASE_STK_ADDM_CFG_ALL != testCaseId ) {
        break;
      }   
  }
  return ;
}

