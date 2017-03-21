#include <includes.h>

CLEANDBTABLEIMPLEMENTATION(TrunkPortTable)

void PRINT_TRUNKPORTTABLE( TrunkPortTableApi *pTbl); 
#if 0  
typedef struct
{
   I_U8    chasisFrameId;
   I_U8    slotId;
   I_U16    trunkPortId;
   I_U32    trunkType;
   I_U32    trunkFramingOption;
   I_U32    encodeType;
   I_U8    sigStrength;
   I_U32    loopType;
   I_U32    loopback;
   I_U32    operatorControlledTrunkState;
   I_U32    adminState;
   I_U32    usageType;
}TrunkPortTableApi;
#endif  


/*---------------------TC---Enable the Trunk Port---------------------------*/
I_Void  fTPAdmnSrcCfgPreTCEnable() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  

  
  CALLCLEANDBTABLE(TrunkPortTable);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->operatorControlledTrunkState = ENABLED;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPAdmnSrcCfgStepsTCEnable()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS)
           {
              TEST_RESULT=1;
           }
          break;
      case OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ:
           LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ [%d] ", OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ);
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND:");
            if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == ALARM_E1_ENABLE_SUCCESS)
           return;
           break;
 
      default :;
    }  
  }
  return ;
}
I_Void  fTPAdmnSrcCfgPostTCEnable()
{
   TrunkPortTableIndices inData = { 0 };
   TrunkPortTableApi *outData;
   E1PerTableApi      e1Data = {0};
   LOG_PRINT(INFO,"%s:",__func__);

   inData.chasisFrameId = 1;
   inData.slotId        = 3;
   inData.trunkPortId   = 0;

   if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
          LOG_PRINT(INFO,"OperatorControlledTrunkState = %d",outData->operatorControlledTrunkState);
     if (outData->operatorControlledTrunkState == ENABLED )
     {
         TEST_RESULT =1;
         LOG_PRINT(INFO,"OperatorControlledTrunkState = ENABLED");
     }
     PRINT_TRUNKPORTTABLE(outData);
     free(outData);
   }
   else 
   {
      LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
   }
   return ;
}

I_Void fTPAdmnSrcCfgTCEnable(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPAdmnSrcCfgPreTCEnable();
  fTPAdmnSrcCfgStepsTCEnable();
  fTPAdmnSrcCfgPostTCEnable();
  return ;
}
/*---------------------TC---Enable the Trunk Port---------------------------*/


/*---------------------TC31---Unlock the (Enabled)Trunk Port---------------------------*/
I_Void  fTPAdmnSrcCfgPreTC31() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;
 
  indata->adminState = UNLOCKED;

  // Trunk Port has to be in enabled state to execute the test case
  indata->operatorControlledTrunkState = ENABLED;

  // Insert data in BSS Table
  addBssTable();


  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPAdmnSrcCfgStepsTC31()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        sleep(2);
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPAdmnSrcCfgPostTC31()
{
  TrunkPortTableIndices inData = { 0 };
  E1PerTableIndices inData1    = { 0 };
  TrunkPortTableApi *outData   = NULL;
  E1PerTableApi     *outData1  = NULL;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  inData1.e1Num        = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) && CLIB_SUCCESS == getE1PerTable( &inData1, &outData1 )) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->adminState == UNLOCKED && outData1->adminState == UNLOCKED )
        TEST_RESULT =1;

    free(outData);
    free(outData1);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable/E1PerTable fails",__func__);
  }
  return ;
}

I_Void fTPAdmnSrcCfgTC31(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPAdmnSrcCfgPreTC31();
  fTPAdmnSrcCfgStepsTC31();
  fTPAdmnSrcCfgPostTC31();
  return ;
}
/*---------------------TC31---Unlock the (Enabled)Trunk Port---------------------------*/


/*---------------------TC33---Lock the (Enabled)Trunk Port---------------------------*/
I_Void  fTPAdmnSrcCfgPreTC33() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;
 
  indata->adminState = LOCKED;
  indata->operatorControlledTrunkState = ENABLED;

  // Insert data in BSS Table
  addBssTable();


  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPAdmnSrcCfgStepsTC33()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS) {
          TEST_RESULT=1;
        }
        sleep(2);
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPAdmnSrcCfgPostTC33()
{
  TrunkPortTableIndices inData = { 0 };
  E1PerTableIndices inData1    = { 0 };
  TrunkPortTableApi *outData   = NULL;
  E1PerTableApi     *outData1  = NULL;
  LOG_PRINT(INFO,"%s:",__func__);

  inData.chasisFrameId = 1;
  inData.slotId        = 3;
  inData.trunkPortId   = 0;

  inData1.e1Num        = 0;

  if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) && CLIB_SUCCESS == getE1PerTable( &inData1, &outData1 )) {
    PRINT_TRUNKPORTTABLE(outData);
    if (outData->adminState == LOCKED && outData1->adminState == LOCKED )
        TEST_RESULT =1;

    free(outData);
    free(outData1);
  }
  else 
  {
    LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable/E1PerTable fails",__func__);
  }
  return ;
}

I_Void fTPAdmnSrcCfgTC33(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPAdmnSrcCfgPreTC33();
  fTPAdmnSrcCfgStepsTC33();
  fTPAdmnSrcCfgPostTC33();
  return ;
}
/*---------------------TC33---Lock the (Enabled)Trunk Port---------------------------*/


/*---------------------TC---Disable the Trunk Port---------------------------*/
I_Void  fTPAdmnSrcCfgPreTCDisable() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  

  
  CALLCLEANDBTABLE(TrunkPortTable);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;
  indata->operatorControlledTrunkState = ENABLED;
 
  dbStatus = insertTrunkPortTable(indata);
  if(dbStatus != DBLIB_SUCCESS) 
  {
     LOG_PRINT(LOG_INFO,"UsageType change Procedure Ends");        
    return;
  }
  
  indata->operatorControlledTrunkState = DISABLED;

  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPAdmnSrcCfgStepsTCDisable()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
           LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
           if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == CM_SUCCESS)
           {
              TEST_RESULT=1;
           }
          break;
      case OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ:
           LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ [%d] ", OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ);
           ExecuteOilAction(RCVD_MSG_PTR);
           break;
      case OAMS_CFG_AFH_ALARM_IND:
           LOG_PRINT(INFO, "Msg Rcvd OAMS_CFG_AFH_ALARM_IND:");
            if ( ((OamsCfgAfhSysAlarm *)RCVD_MSG_PTR)->sysAlarm.sysalarmId == ALARM_E1_DISABLE_SUCCESS)
           return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPAdmnSrcCfgPostTCDisable()
{
   TrunkPortTableIndices inData = { 0 };
   TrunkPortTableApi *outData;
   E1PerTableApi      e1Data = {0};
   LOG_PRINT(INFO,"%s:",__func__);

   inData.chasisFrameId = 1;
   inData.slotId        = 3;
   inData.trunkPortId   = 0;

   if (CLIB_SUCCESS == getTrunkPortTable( &inData, &outData) ) {
     PRINT_TRUNKPORTTABLE(outData);
     if (outData->operatorControlledTrunkState == DISABLED )
         TEST_RESULT =1;

     free(outData);
   }
   else 
   {
      LOG_PRINT(CRITICAL," [%s]:getTrunkPortTable fails",__func__);
   }
   return ;
}

I_Void fTPAdmnSrcCfgTCDisable(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPAdmnSrcCfgPreTCDisable();
  fTPAdmnSrcCfgStepsTCDisable();
  fTPAdmnSrcCfgPostTCDisable();
  return ;
}
/*---------------------TC---Disable the Trunk Port---------------------------*/


/*---------------------TC35---Unlock the (Disabled)Trunk Port---------------------------*/
I_Void  fTPAdmnSrcCfgPreTC35() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;
 
  indata->adminState = UNLOCKED;

  // Trunk Port has to be in disabled state to execute the test case
  indata->operatorControlledTrunkState = DISABLED;

  // Insert data in BSS Table
  addBssTable();


  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPAdmnSrcCfgStepsTC35()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=1;
        }
        sleep(2);
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPAdmnSrcCfgPostTC35()
{
  return ;
}

I_Void fTPAdmnSrcCfgTC35(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPAdmnSrcCfgPreTC35();
  fTPAdmnSrcCfgStepsTC35();
  fTPAdmnSrcCfgPostTC35();
  return ;
}
/*---------------------TC35---Unlock the (Disabled)Trunk Port---------------------------*/


/*---------------------TC36---Lock the (Disabled)Trunk Port---------------------------*/
I_Void  fTPAdmnSrcCfgPreTC36() 
{
  LOG_PRINT(INFO,"%s:",__func__);
  
  sCmMsg* CmMsgPtr = NULL;
  TrunkPortTableApi   *indata = NULL ;
  I_U32               dbStatus = 0;
  
  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(TrunkPortTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                BSC_API_SET_TRUNKPORTTABLE, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(TrunkPortTableApi);

  indata = (TrunkPortTableApi *)(CmMsgPtr+1);
  

  indata->chasisFrameId = 1;
  indata->slotId        = 3;
  indata->trunkPortId   = 0;
  indata->usageType     = SYS_E1_USAGE_AIF;
 
  // Though we have to send LOCKED, but in previous test case, state will never be updated to UNLOCKED
  indata->adminState = UNLOCKED;
  indata->operatorControlledTrunkState = DISABLED;

  // Insert data in BSS Table
  addBssTable();


  SendMsgToIPC( 
                (I_PVoid)CmMsgPtr,
                (sizeof(TrunkPortTableApi) + sizeof(sCmMsg)), 
                ""
              );
  return ;
}

I_Void  fTPAdmnSrcCfgStepsTC36()
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {   
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status != CM_SUCCESS) {
          TEST_RESULT=1;
        }
        sleep(2);
        return;
      default :;
    }  
  }
  return ;
}
I_Void  fTPAdmnSrcCfgPostTC36()
{
  return ;
}

I_Void fTPAdmnSrcCfgTC36(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  fTPAdmnSrcCfgPreTC36();
  fTPAdmnSrcCfgStepsTC36();
  fTPAdmnSrcCfgPostTC36();
  return ;
}
/*---------------------TC36---Lock the (Disabled)Trunk Port---------------------------*/

I_PU8 TpAdmnTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
     case TEST_CASEENABLE_TP_ADMN_CHG_CFG:
      return "Trunk Port Admn TCENABLE";
     case TEST_CASE31_TP_ADMN_CHG_CFG:
      return "Trunk Port Admn TC31";
     case TEST_CASE32_TP_ADMN_CHG_CFG:
      return "Trunk Port Admn TC32";
     case TEST_CASE33_TP_ADMN_CHG_CFG:
      return "Trunk Port Admn TC33";
     case TEST_CASEDISABLE_TP_ADMN_CHG_CFG:
      return "Trunk Port Usage TCDISABLE";
     case TEST_CASE35_TP_ADMN_CHG_CFG:
      return "Trunk Port Admn TC35";
     case TEST_CASE36_TP_ADMN_CHG_CFG:
      return "Trunk Port Admn TC36";
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    
  }
  return NULL;
}

I_Void ExecuteTpAdmnGroup(I_U32 testCaseId) 
{
  switch (testCaseId)
  {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
   case TEST_CASEENABLE_TP_ADMN_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASEENABLE_TP_ADMN_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPAdmnSrcCfgTCEnable();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE31_TP_ADMN_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      if ( TEST_CASE_TP_ADMN_CHG_CFG_ALL !=testCaseId )	
      {
         TEST_CASE_ID = TEST_CASEENABLE_TP_ADMN_CHG_CFG;
         TEST_RESULT=0;
         fTPAdmnSrcCfgTCEnable();
      }
      if( TEST_RESULT == 0 )
      {
         LOG_PRINT(INFO,"TEST_CASEENABLE_TP_ADMN_CHG_CFG Failed:: Cannot execute TEST_CASE31_TP_ADMN_CHG_CFG");
         return;
      }
      TEST_RESULT=0;
      TEST_CASE_ID = TEST_CASE31_TP_ADMN_CHG_CFG;
      fTPAdmnSrcCfgTC31();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE33_TP_ADMN_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      if ( TEST_CASE_TP_ADMN_CHG_CFG_ALL !=testCaseId)	
      {
         TEST_CASE_ID = TEST_CASEENABLE_TP_ADMN_CHG_CFG;
         fTPAdmnSrcCfgTCEnable();
         TEST_RESULT=0;
         TEST_CASE_ID = TEST_CASE31_TP_ADMN_CHG_CFG;
         fTPAdmnSrcCfgTC31();
      }
      TEST_RESULT=0;
      TEST_CASE_ID = TEST_CASE33_TP_ADMN_CHG_CFG;
      fTPAdmnSrcCfgTC33();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASEDISABLE_TP_ADMN_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASEDISABLE_TP_ADMN_CHG_CFG;
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      fTPAdmnSrcCfgTCDisable();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE35_TP_ADMN_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      if ( TEST_CASE_TP_ADMN_CHG_CFG_ALL !=testCaseId )	
      {
         TEST_CASE_ID = TEST_CASEDISABLE_TP_ADMN_CHG_CFG;
         TEST_RESULT=0;
         fTPAdmnSrcCfgTCDisable();
      }
      TEST_RESULT=0;
      TEST_CASE_ID = TEST_CASE35_TP_ADMN_CHG_CFG;
      fTPAdmnSrcCfgTC35();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL != testCaseId ) {
        break;
      }
   case TEST_CASE36_TP_ADMN_CHG_CFG:
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_RESULT=0;
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
      if ( TEST_CASE_TP_ADMN_CHG_CFG_ALL !=testCaseId)	
      {
         TEST_CASE_ID = TEST_CASEDISABLE_TP_ADMN_CHG_CFG;
         fTPAdmnSrcCfgTCDisable();
      }
      TEST_RESULT=0;
      TEST_CASE_ID = TEST_CASE36_TP_ADMN_CHG_CFG;
      fTPAdmnSrcCfgTC36();
      PRINT_TEST_RESULT();
      if (TEST_CASE_TP_ADMN_CHG_CFG_ALL != testCaseId ) {
        break;
      }
  }
  return ;
}



void PRINT_TRUNKPORTTABLE( TrunkPortTableApi *pTbl) 
{
          LOG_PRINT(INFO,"ChasisFrameId                = %d",pTbl->chasisFrameId); 
          LOG_PRINT(INFO,"SlotId                       = %d",pTbl->slotId);
          LOG_PRINT(INFO,"TrunkPortId                  = %d",pTbl->trunkPortId);
          LOG_PRINT(INFO,"TrunkType                    = %d",pTbl->trunkType);
          LOG_PRINT(INFO,"TrunkFramingOption           = %d",pTbl->trunkFramingOption);
          LOG_PRINT(INFO,"EncodeType                   = %d",pTbl->encodeType); 
          LOG_PRINT(INFO,"SigStrength                  = %d",pTbl->sigStrength);
          LOG_PRINT(INFO,"LoopType                     = %d",pTbl->loopType);
          LOG_PRINT(INFO,"Loopback                     = %d",pTbl->loopback); 
          LOG_PRINT(INFO,"AdminState                   = %d",pTbl->adminState);
          LOG_PRINT(INFO,"UsageType                    = %d",pTbl->usageType); 
          LOG_PRINT(INFO,"OperatorControlledTrunkState = %d",pTbl->operatorControlledTrunkState);
} 
