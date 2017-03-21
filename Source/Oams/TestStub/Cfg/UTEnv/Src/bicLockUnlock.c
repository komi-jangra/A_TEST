#include <includes.h>

CLEANDBTABLEIMPLEMENTATION(TrxTable)
CLEANDBTABLEIMPLEMENTATION(BicTrxTimeslotUsageTable)
CLEANDBTABLEIMPLEMENTATION(AbisTimeSlotNonPerTable)
CLEANDBTABLEIMPLEMENTATION(SwMNodeTable)

I_Void cleanBicDB()
{
  CALLCLEANDBTABLE(MccLinkResourceTable);
  CALLCLEANDBTABLE(BicTable);
  CALLCLEANDBTABLE(TrxTable);
  CALLCLEANDBTABLE(BicTrxTimeslotUsageTable);
  CALLCLEANDBTABLE(AbisTimeSlotPerTable);
  CALLCLEANDBTABLE(AbisTimeSlotNonPerTable);
  CALLCLEANDBTABLE(SwMNodeTable);
}

I_Void addBicReqHandler()	/* For Successfull Result */
{
   OamsCfgBichAddBicReq *oamsCfgBichAddBicReqPtr = NULL;
   OamsBichCfgAddBicResp oamsBichCfgAddBicResp;
   oamsCfgBichAddBicReqPtr = (OamsCfgBichAddBicReq *)RCVD_MSG_PTR;
   LOG_PRINT(INFO,"BIC Id (from Cfg):: %d \n" , oamsCfgBichAddBicReqPtr->bicId);
   oamsBichCfgAddBicResp.bicId = oamsCfgBichAddBicReqPtr->bicId;
   oamsBichCfgAddBicResp.result = OAMS_RSLT_SUCCESS;
   oamsBichCfgAddBicResp.e1Id = oamsCfgBichAddBicReqPtr->e1Id;
   oamsBichCfgAddBicResp.e1Ts = oamsCfgBichAddBicReqPtr->e1Ts;
   cfgStubSendMessage(&oamsBichCfgAddBicResp,sizeof(oamsBichCfgAddBicResp),ENT_OAMS_BICH,OAMS_BICH_CFG_ADD_BIC_RESP,0);
}

I_Void deleteBicReqHandler() /* For Successfull Result */
{
   OamsCfgBichDelBicReq *oamsCfgBichDelBicReqPtr = NULL;
   OamsBichCfgDelBicResp oamsBichCfgDelBicResp;
   oamsCfgBichDelBicReqPtr = (OamsCfgBichDelBicReq *)RCVD_MSG_PTR ;
   LOG_PRINT(INFO,"BIC Id (from Cfg):: %d \n" , oamsCfgBichDelBicReqPtr->bicId);
   oamsBichCfgDelBicResp.bicId = oamsCfgBichDelBicReqPtr->bicId;
   oamsBichCfgDelBicResp.result = OAMS_RSLT_SUCCESS;
   cfgStubSendMessage(&oamsBichCfgDelBicResp,sizeof(oamsBichCfgDelBicResp),ENT_OAMS_BICH,OAMS_BICH_CFG_DEL_BIC_RESP,0);
}

I_Void addTrxReqHandler() /* For Successfull Result */
{
   OamsCfgTrxhAddTrxReq *oamsCfgTrxhAddTrxReqPtr = NULL;
   OamsTrxhCfgAddTrxResp oamsTrxhCfgAddTrxResp;
   oamsCfgTrxhAddTrxReqPtr = (OamsCfgTrxhAddTrxReq *) RCVD_MSG_PTR;
   LOG_PRINT(INFO,"Ptrx Id (from Cfg):: %d \n" , oamsCfgTrxhAddTrxReqPtr->ptrxId);
   oamsTrxhCfgAddTrxResp.ptrxId = oamsCfgTrxhAddTrxReqPtr->ptrxId;
   oamsTrxhCfgAddTrxResp.result = OAMS_RSLT_SUCCESS;
   cfgStubSendMessage(&oamsTrxhCfgAddTrxResp,sizeof(oamsTrxhCfgAddTrxResp),ENT_OAMS_TRXH,OAMS_TRXH_CFG_ADD_TRX_RESP,0);
}

I_Void deleteTrxReqHandler()      /* For Successfull Result */
{
   OamsCfgTrxhDelTrxReq *oamsCfgTrxhDelTrxReqPtr = NULL;
   OamsTrxhCfgDelTrxResp oamsTrxhCfgDelTrxResp;
   oamsCfgTrxhDelTrxReqPtr = (OamsCfgTrxhDelTrxReq *) RCVD_MSG_PTR ;
   LOG_PRINT(INFO,"Ptrx Id (from Cfg):: %d \n" , oamsCfgTrxhDelTrxReqPtr->ptrxId);
   oamsTrxhCfgDelTrxResp.ptrxId = oamsCfgTrxhDelTrxReqPtr->ptrxId;
   oamsTrxhCfgDelTrxResp.result = OAMS_RSLT_SUCCESS;
   cfgStubSendMessage(&oamsTrxhCfgDelTrxResp,sizeof(oamsTrxhCfgDelTrxResp),ENT_OAMS_TRXH,OAMS_TRXH_CFG_DEL_TRX_RESP,0);
}

/*----------------------------------TC1---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC1() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  addMccLinkResTable(32,4,SYS_TS_FREE,1,INVALID_E1,INVALID_TS);
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 2;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC1()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
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
I_Void  fBicLockUnlockCfgPostTC1()
{
  return ;
}
I_Void fBicLockUnlockCfgTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC1();
  fBicLockUnlockCfgStepsTC1();
  fBicLockUnlockCfgPostTC1();
  return ;
}

/*----------------------------------TC2---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC2() 
{
  TrunkPortTableApi trunkBuff = {1,1,5,1,1,1,1,0,0,0,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10};
  LOG_PRINT(INFO,"%s:",__func__);
  addTrunkPortTable(5);
  addMccLinkResGenericTable(32,4,SYS_TS_FREE,ICCSELFCARD,INVALID_E1,INVALID_TS);
  addMccLinkResGenericTable(32,6,SYS_TS_FREE,ICCMATECARD,INVALID_E1,INVALID_TS);
  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,5,2,1);   


  cfgStubSendCmMessage(&trunkBuff, sizeof(TrunkPortTableApi), BSC_API_SET_TRUNKPORTTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC2()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(INFO, "Rcvd  CM_SUCCESS" );
           TEST_RESULT=1;
           return;  
           }
           break;
      case OAMS_CFG_BICH_ADD_BIC_REQ:
	    LOG_PRINT(INFO,"Received Msg : OAMS_CFG_BICH_ADD_BIC_REQ");
	    addBicReqHandler();
	    break;
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC2()
{
  return ;
}
I_Void fBicLockUnlockCfgTC2(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC2();
  fBicLockUnlockCfgStepsTC2();
  fBicLockUnlockCfgPostTC2();
  return ;
}

/*----------------------------------TC3---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC3() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  //addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 2;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC3()
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
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC3()
{
  return ;
}
I_Void fBicLockUnlockCfgTC3(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC3();
  fBicLockUnlockCfgStepsTC3();
  fBicLockUnlockCfgPostTC3();
  return ;
}

/*----------------------------------TC4---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC4() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC4()
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
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC4()
{
  return ;
}
I_Void fBicLockUnlockCfgTC4(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC4();
  fBicLockUnlockCfgStepsTC4();
  fBicLockUnlockCfgPostTC4();
  return ;
}

/*----------------------------------TC5---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC5() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 3;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC5()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_REQUEST) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC5()
{
  return ;
}
I_Void fBicLockUnlockCfgTC5(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC5();
  fBicLockUnlockCfgStepsTC5();
  fBicLockUnlockCfgPostTC5();
  return ;
}

/*----------------------------------TC6---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC6() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  //addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC6()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_E1_NOT_PRESENT_IN_DB) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC6()
{
  return ;
}
I_Void fBicLockUnlockCfgTC6(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC6();
  fBicLockUnlockCfgStepsTC6();
  fBicLockUnlockCfgPostTC6();
  return ;
}

/*----------------------------------TC7---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC7() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  //addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC7()
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
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC7()
{
  return ;
}
I_Void fBicLockUnlockCfgTC7(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC7();
  fBicLockUnlockCfgStepsTC7();
  fBicLockUnlockCfgPostTC7();
  return ;
}

/*----------------------------------TC8---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC8() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  //addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC8()
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
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC8()
{
  return ;
}
I_Void fBicLockUnlockCfgTC8(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC8();
  fBicLockUnlockCfgStepsTC8();
  fBicLockUnlockCfgPostTC8();
  return ;
}

/*----------------------------------TC9---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC9() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  //addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC9()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC9()
{
  return ;
}
I_Void fBicLockUnlockCfgTC9(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC9();
  fBicLockUnlockCfgStepsTC9();
  fBicLockUnlockCfgPostTC9();
  return ;
}

/*----------------------------------TC10---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC10() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  //addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC10()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC10()
{
  return ;
}
I_Void fBicLockUnlockCfgTC10(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC10();
  fBicLockUnlockCfgStepsTC10();
  fBicLockUnlockCfgPostTC10();
  return ;
}

/*----------------------------------TC11---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC11() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1); 
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC11()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
       case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_FAIL;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_UNKNOWN) {
           TEST_RESULT=1;
           return;
           }
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC11()
{
  return;
}
I_Void fBicLockUnlockCfgTC11(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC11();
  fBicLockUnlockCfgStepsTC11();
  fBicLockUnlockCfgPostTC11();
  return;
}

/*----------------------------------TC12---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC12() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_1,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC12()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"Recieved CM_SUCCES..");
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
           if (sysAlarmPtr->sysAlarm.sysalarmId == ALARM_BIC_UNLOCK_COMPLETED) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC12()
{
  return ;
}
I_Void fBicLockUnlockCfgTC12(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC12();
  fBicLockUnlockCfgStepsTC12();
  fBicLockUnlockCfgPostTC12();
  return ;
}

/*----------------------------------TC13---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC13() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,5,0);
  addRowInBicTable(2,2,5,0);
  addBicTrxTimeSlotUsageTable(1,5,1);
  addBicTrxTimeSlotUsageTable(2,5,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,5,1);
  addAbisTimeSlotTable(5,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 5;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC13()
{
  BicTableApi requestBuff;
  requestBuff.bicId = 2;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 5;
  requestBuff.adminState = 1;
  I_S32 bit =0;
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"Recieved CM_SUCCES..");
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
           if (sysAlarmPtr->sysAlarm.sysalarmId == ALARM_BIC_UNLOCK_COMPLETED) {
           if (bit == 0)
           {
           cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
           bit = 1;
           }
           else 
           {
           TEST_RESULT=1;
           return;  
           }
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC13()
{
  return ;
}
I_Void fBicLockUnlockCfgTC13(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC13();
  fBicLockUnlockCfgStepsTC13();
  fBicLockUnlockCfgPostTC13();
  return ;
}

/*----------------------------------TC14---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC14() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_STANDALONE_BIC_TS_MAX_BIC_4,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,1);
  addBicTrxTimeSlotUsageTable(1,4,1);
  //addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC14()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC14()
{
  return ;
}
I_Void fBicLockUnlockCfgTC14(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC14();
  fBicLockUnlockCfgStepsTC14();
  fBicLockUnlockCfgPostTC14();
  return ;
}

/*----------------------------------TC15---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC15() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,1);
  addBicTrxTimeSlotUsageTable(1,4,1);
  //addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC15()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_INVALID_OR_MISSING_PRECONFIGDATA) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC15()
{
  return ;
}
I_Void fBicLockUnlockCfgTC15(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC15();
  fBicLockUnlockCfgStepsTC15();
  fBicLockUnlockCfgPostTC15();
  return ;
}

/*----------------------------------TC16---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC16() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,1);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC16()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"Recieved CM_SUCCES..");
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
           if (sysAlarmPtr->sysAlarm.sysalarmId == ALARM_BIC_LOCK_COMPLETED) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC16()
{
  return ;
}
I_Void fBicLockUnlockCfgTC16(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC16();
  fBicLockUnlockCfgStepsTC16();
  fBicLockUnlockCfgPostTC16();
  return ;
}

/*----------------------------------TC17---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC17() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,2,1);
  addRowInBicTable(2,2,2,1);
  addBicTrxTimeSlotUsageTable(1,2,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,2,1);
  addAbisTimeSlotTable(2,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 2;
  requestBuff.adminState = 0;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC17()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(LOG_INFO,"Recieved CM_SUCCES..");
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
           if (sysAlarmPtr->sysAlarm.sysalarmId == ALARM_BIC_LOCK_COMPLETED) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC17()
{
  return ;
}
I_Void fBicLockUnlockCfgTC17(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC17();
  fBicLockUnlockCfgStepsTC17();
  fBicLockUnlockCfgPostTC17();
  return ;
}

/*----------------------------------TC18---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC18() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addRowInBicTable(2,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addBicTrxTimeSlotUsageTable(2,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 4;
  requestBuff.adminState = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  requestBuff.bicId = 2;
  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC18()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_UNLOCK_IN_PROGRESS) {
           TEST_RESULT=1;
           return;  
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
           if (sysAlarmPtr->sysAlarm.sysalarmId == ALARM_BIC_UNLOCK_COMPLETED) {
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC18()
{
  return ;
}
I_Void fBicLockUnlockCfgTC18(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC18();
  fBicLockUnlockCfgStepsTC18();
  fBicLockUnlockCfgPostTC18();
  return ;
}

/*----------------------------------TC19---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC19() 
{
  BicTableIndices requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,1);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
 
  requestBuff.bicId = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableIndices), BSC_API_DEL_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC19()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_BIC_NOT_LOCKED_IN_DB) {
           TEST_RESULT=1;
           return;  
           }
           break; 
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC19()
{
  return ;
}
I_Void fBicLockUnlockCfgTC19(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC19();
  fBicLockUnlockCfgStepsTC19();
  fBicLockUnlockCfgPostTC19();
  return ;
}

/*----------------------------------TC20---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC20() 
{
  BicTableIndices requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,0);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResTable(32,4,SYS_TS_ALLOCATED,1,4,1);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);
  cfgPopulateSwMNodeTable(SYS_NODE_TYPE_BIC,1,4,"10.11.12","100.101.102","200.201.202","",0,0);

 
  requestBuff.bicId = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableIndices), BSC_API_DEL_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC20()
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
           return;  
           }
           break;
      case OAMS_CFG_BICH_DEL_BIC_REQ:
	    LOG_PRINT(INFO,"Received Msg : OAMS_CFG_BICH_DEL_BIC_REQ");
	    deleteBicReqHandler();
	    break;
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC20()
{
  return ;
}
I_Void fBicLockUnlockCfgTC20(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC20();
  fBicLockUnlockCfgStepsTC20();
  fBicLockUnlockCfgPostTC20();
  return ;
}

/*----------------------------------TC21---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC21() 
{
  TrxTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(4);
  addRowInE1PerTable(4,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,4,1);
  addBicTrxTimeSlotUsageTable(1,4,1);
  addMccLinkResGenericTable(32,4,SYS_TS_FREE,ICCMATECARD,INVALID_E1,INVALID_TS);
  addAbisTimeSlotTable(4,1,SYS_TS_USAGE_LAPD_BIC);

 
  requestBuff.ptrxId = 1;
  requestBuff.adminState = 0;
  requestBuff.trxLocation = 2;
  requestBuff.bicId = 1;
  requestBuff.antennaID = 100;
  requestBuff.trxPos = 1;
  requestBuff.rfPathGain = 2;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrxTableApi), BSC_API_SET_TRXTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC21()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_ERR_BIC_NOT_LOCKED_IN_DB) {
           TEST_RESULT=1;
           return;  
           }
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC21()
{
  return ;
}
I_Void fBicLockUnlockCfgTC21(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC21();
  fBicLockUnlockCfgStepsTC21();
  fBicLockUnlockCfgPostTC21();
  return ;
}

/*----------------------------------TC22---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC22() 
{
  BicTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  addTrunkPortTable(5);
  addMccLinkResGenericTable(32,4,SYS_TS_FREE,ICCSELFCARD,INVALID_E1,INVALID_TS);
  addMccLinkResGenericTable(32,6,SYS_TS_FREE,ICCMATECARD,INVALID_E1,INVALID_TS);
  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,5,2,1);   

  requestBuff.bicId = 1;
  requestBuff.numTrx = 2;
  requestBuff.e1Id = 5;
  requestBuff.adminState = 0;
  cfgStubSendCmMessage(&requestBuff, sizeof(BicTableApi), BSC_API_SET_BICTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC22()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           LOG_PRINT(INFO, "Rcvd  CM_SUCCESS" );
           }
           break;
      case OAMS_CFG_BICH_ADD_BIC_REQ:
	    LOG_PRINT(INFO,"Received Msg : OAMS_CFG_BICH_ADD_BIC_REQ");
	    addBicReqHandler();
            TEST_RESULT=1;
            return;  
	    break;
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC22()
{
  return ;
}
I_Void fBicLockUnlockCfgTC22(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC22();
  fBicLockUnlockCfgStepsTC22();
  fBicLockUnlockCfgPostTC22();
  return ;
}


/*----------------------------------TC23---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC23() 
{
  TrxTableApi requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,5,0);
  addInBicStatusTable(1);
  addBicTrxTimeSlotUsageTable(1,5,1);
  addMccLinkResGenericTable(32,4,SYS_TS_FREE,ICCMATECARD,INVALID_E1,INVALID_TS);
  addAbisTimeSlotTable(5,1,SYS_TS_USAGE_LAPD_BIC);

 
  requestBuff.ptrxId = 1;
  requestBuff.adminState = 0;
  requestBuff.trxLocation = 2;
  requestBuff.bicId = 1;
  requestBuff.antennaID = 100;
  requestBuff.trxPos = 1;
  requestBuff.rfPathGain = 2;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrxTableApi), BSC_API_SET_TRXTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC23()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           LOG_PRINT(INFO, "Status: %d",((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status);
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
           }
           break;
      case OAMS_CFG_GRHM_SWITCH_CONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           TEST_RESULT=1;
           return;  
           break;
      case OAMS_CFG_TRXH_ADD_TRX_REQ:
	    LOG_PRINT(INFO,"Received Msg : OAMS_CFG_TRXH_ADD_TRX_REQ:");
	    addTrxReqHandler();
	    break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC23()
{
  return ;
}
I_Void fBicLockUnlockCfgTC23(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC23();
  fBicLockUnlockCfgStepsTC23();
  fBicLockUnlockCfgPostTC23();
  return ;
}

/*----------------------------------TC24---------------------------------------------*/
I_Void  fBicLockUnlockCfgPreTC24() 
{
  TrxTableIndices requestBuff;
  LOG_PRINT(INFO,"%s:",__func__);
  
  deleteRowFromE1PerTable(5);
  addRowInE1PerTable(5,0,SYS_E1_USAGE_ABISIF_SHARED_BIC_TS_MAX_BIC_10,INVALID_TRUNK_ID,2,1);   
  addRowInBicTable(1,2,5,0);
  addInBicStatusTable(1);
  addBicTrxTimeSlotUsageTable(1,5,1);
  addMccLinkResGenericTable(32,4,SYS_TS_ALLOCATED,ICCMATECARD,5,1);
  addAbisTimeSlotTable(5,1,SYS_TS_USAGE_LAPD_BIC);
  addInTrxTable(1,1);
  cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,1,5,"10.11.12","100.101.102","200.201.202","",0,0);
 
  requestBuff.ptrxId = 1;

  cfgStubSendCmMessage(&requestBuff, sizeof(TrxTableIndices), BSC_API_DEL_TRXTABLE);
  return ;
}
I_Void  fBicLockUnlockCfgStepsTC24()
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
           return;  
           }
           break;
      case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
           switchConnResp = ALL_OK;
           ExecuteGrhmAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_TRXH_DEL_TRX_REQ:
	    LOG_PRINT(INFO,"Received Msg : OAMS_CFG_TRXH_ADD_TRX_REQ:");
	    deleteTrxReqHandler();
	    break;
      default :;
    }  
  }
  return ;
}
I_Void  fBicLockUnlockCfgPostTC24()
{
  return ;
}
I_Void fBicLockUnlockCfgTC24(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fBicLockUnlockCfgPreTC24();
  fBicLockUnlockCfgStepsTC24();
  fBicLockUnlockCfgPostTC24();
  return ;
}

/*-----------------------------------------------------------------------*/
I_PU8 bicLockUnlockTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
    case TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL:
      return "ALL HA STK CFG TCs";
    case TEST_CASE1_BIC_LOCK_UNLOCK_CFG:
      return "BIC Add rejected in Unlock state: TC 1";
    case TEST_CASE2_BIC_LOCK_UNLOCK_CFG:
      return "UsageType Change from Free to Abis: TC 2";
    case TEST_CASE3_BIC_LOCK_UNLOCK_CFG:
      return "BIC Mod Param other than adminState: TC 3";
    case TEST_CASE4_BIC_LOCK_UNLOCK_CFG:
      return "BIC Mod Same Param as in DB: TC 4";
    case TEST_CASE5_BIC_LOCK_UNLOCK_CFG:
      return "BIC Mod with wrong value of adminState: TC 5";
    case TEST_CASE6_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock with E1 Not Present: TC 6";
    case TEST_CASE7_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock with no row in BicTrxTimeslot: TC 7";
    case TEST_CASE8_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock with no row in AbisTimeslot: TC 8";
    case TEST_CASE9_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock(Standalone) with no Free MccLinkResource: TC 9";
    case TEST_CASE10_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock(Shared) with no Free MccLinkResource: TC 10";
    case TEST_CASE11_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock(Shared) and Switch Connect Nack: TC 11";
    case TEST_CASE12_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock(Standalone) Success: TC 12";
    case TEST_CASE13_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock(Shared) with 2 Bic Success: TC 13";
    case TEST_CASE14_BIC_LOCK_UNLOCK_CFG:
      return "BIC Lock(Standalone) with no Free MccLinkResource: TC 14";
    case TEST_CASE15_BIC_LOCK_UNLOCK_CFG:
      return "BIC Lock(Shared) with no Free MccLinkResource: TC 15";
    case TEST_CASE16_BIC_LOCK_UNLOCK_CFG:
      return "BIC Lock(Shared) Success: TC 16";
    case TEST_CASE17_BIC_LOCK_UNLOCK_CFG:
      return "BIC Lock(Shared) with 2 Bic Success: TC 17";
    case TEST_CASE18_BIC_LOCK_UNLOCK_CFG:
      return "BIC Unlock with Bic Unlock Ongoing: TC 18";
    case TEST_CASE19_BIC_LOCK_UNLOCK_CFG:
      return "BIC Delete with Bic state Unlock in DB: TC 19";
    case TEST_CASE20_BIC_LOCK_UNLOCK_CFG:
      return "BIC Delete Success: TC 20";
    case TEST_CASE21_BIC_LOCK_UNLOCK_CFG:
      return "Add Trx with its Bic in Unlocked State: TC 21";
    case TEST_CASE22_BIC_LOCK_UNLOCK_CFG:
      return "BIC Add Success: TC 22";
    case TEST_CASE23_BIC_LOCK_UNLOCK_CFG:
      return "Add Trx Success: TC 23";
    case TEST_CASE24_BIC_LOCK_UNLOCK_CFG:
      return "Del Trx Success: TC 24";
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
  }
  return NULL;
}

/*-----------------------------------------------------------------------*/
I_Void ExecuteBicLockUnlockGroup(I_U32 testCaseId) 
{
  switch (testCaseId) {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    case TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL:
    case TEST_CASE1_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE1_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC1();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE2_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE2_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC2();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE3_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE3_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC3();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE4_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE4_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC4();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE5_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE5_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC5();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE6_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE6_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC6();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE7_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE7_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC7();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE8_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE8_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC8();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE9_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE9_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC9();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE10_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE10_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC10();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE11_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE11_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC11();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE12_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE12_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC12();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE13_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE13_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC13();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE14_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE14_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC14();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE15_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE15_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC15();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE16_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE16_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC16();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE17_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE17_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC17();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE18_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE18_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC18();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE19_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE19_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC19();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE20_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE20_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC20();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE21_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE21_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC21();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE22_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE22_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC22();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE23_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE23_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC23();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
    case TEST_CASE24_BIC_LOCK_UNLOCK_CFG:    
      LOG_PRINT(CRITICAL,"****************************************************");
      cleanBicDB();
      TEST_CASE_ID = TEST_CASE24_BIC_LOCK_UNLOCK_CFG;
      TEST_RESULT=0;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID); 
      fBicLockUnlockCfgTC24();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL != testCaseId ) {
        break;
      }
   }
  return ;
}

