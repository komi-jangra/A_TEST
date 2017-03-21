/***********************************File Header ***************************
File Name        : testsuit.c
Purpose          : This file has the list of testcases and groups.
                   Allocate and Add the testcase to this file. 
Project          : BSC/UTE
Subsystem        : UTE
Author           : BB/VNL/Gurgaon
************************************* End **********************************/

#include<includes.h>

I_U32 TESTCASE_ID , TESTGROUP_ID , TESTCASE_STATE;

I_PU8 testGroupId2String(I_U32 testGroupId)
{
  switch (testGroupId) {
    case ALL_TEST_GROUP :
      return "ALL GROUPs";
    case TEST_GROUP_ADD_BICH :
      return "Clock Source Configuration";
    default : ;  
  }
  return NULL;
}

I_PU8 testCaseId2Description(I_U32 testGroupId, I_U32 testCaseId)
{
  switch (testGroupId) {
    case TEST_GROUP_ADD_BICH:
      return addBichTestCaseDescription(testCaseId);
    default :;  
  }  
  return NULL;
}

I_Void ExecuteTestSuit(I_U32 testGroupId, I_U32 testCaseId)
{
  LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);
  tcResult=0;
  switch (testGroupId) {
    case TEST_GROUP_ADD_BICH :
      ExecuteAddBichGroup(testCaseId);
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
