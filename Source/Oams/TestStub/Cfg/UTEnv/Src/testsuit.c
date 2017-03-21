/***********************************File Header ***************************
File Name        : testsuit.c
Purpose          : This file has the list of testcases and groups.
                   Allocate and Add the testcase to this file. 
Project          : BSC/UTE
Subsystem        : UTE
Author           : BB/VNL/Gurgaon
************************************* End **********************************/

#include<includes.h>

sTestSuitElem testSuitList[MAX_TEST_GROUP][MAX_TEST_CASES_IN_TEST_GROUP]  ;

I_PU8 testGroupId2String(I_U32 testGroupId)
{
  switch (testGroupId) {
    case ALL_TEST_GROUP :
      return "ALL GROUPs";
    case TEST_GROUP_CLK_SRC_CFG :
      return "Clock Source Configuration";
    case TEST_GROUP_STK_SRC_CFG :
      return "HA Stack DELETE Configuration";      
    case TEST_GROUP_STK_ADDM_CFG :
      return "HA Stack ADD/MODIFY Configuration";      
    case TEST_GROUP_TP_USG_CHG_CFG :
      return "TrunkPort Usage Type Change Configuration";      
    case TEST_GROUP_TP_ADMN_CHG_CFG :
      return "TrunkPort Admin State Change Configuration";      
    case TEST_GROUP_BIC_LOCK_UNLOCK_CFG :
      return "Bic ADD/DEL/LOCK/UNLOCK Configuration"; 
    default : ;  
  }
  return NULL;
}

I_PU8 testCaseId2Description(I_U32 testGroupId, I_U32 testCaseId)
{
  switch (testGroupId) {
    case TEST_GROUP_CLK_SRC_CFG:
      return clkSrcTestCaseDescription(testCaseId);
    case TEST_GROUP_STK_SRC_CFG:
      return stkSrcTestCaseDescription(testCaseId);
    case TEST_GROUP_STK_ADDM_CFG:
      return stkAddModTestCaseDescription(testCaseId);
    case TEST_GROUP_TP_USG_CHG_CFG:
      return TpUsgTestCaseDescription(testCaseId);
    case TEST_GROUP_TP_ADMN_CHG_CFG:
      return TpAdmnTestCaseDescription(testCaseId);
    case TEST_GROUP_BIC_LOCK_UNLOCK_CFG:
      return bicLockUnlockTestCaseDescription(testCaseId);
    default :;  
  }  
  return NULL;
}

I_Void ExecuteTestSuit(I_U32 testGroupId, I_U32 testCaseId)
{
  LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
  TEST_RESULT=0;
  switch (testGroupId) {
    case TEST_GROUP_CLK_SRC_CFG :
      ExecuteClkGroup(testCaseId);
      break;   
    case TEST_GROUP_STK_SRC_CFG :
      ExecuteStkGroup(testCaseId);
      break;         
    case TEST_GROUP_STK_ADDM_CFG :
      ExecuteStkAddModGroup(testCaseId);
      break;         
    case TEST_GROUP_TP_USG_CHG_CFG:
      ExecuteTpUsgGroup(testCaseId);
      break;         
    case TEST_GROUP_TP_ADMN_CHG_CFG:
      ExecuteTpAdmnGroup(testCaseId);
      break;         
    case TEST_GROUP_BIC_LOCK_UNLOCK_CFG :
      ExecuteBicLockUnlockGroup(testCaseId);
      break;  
  }
  return ;
}

I_PVoid msgRcvr(I_Void)
{
  I_PVoid rcvPtr = NULL;
  I_S32 msgSize = ZERO;

  while ((rcvPtr = RecvMsg(ENT_UTE_MC, &msgSize)) == NULL) {
    msgSize = msgSize; //Just to show that loop 
  }

  return rcvPtr;
}
