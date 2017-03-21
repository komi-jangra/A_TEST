#include <includes.h>



/*----------------------------------TC1---------------------------------------------*/

I_Void addBichPreTC1(I_Void)
{
  sCmMsg* CmMsgPtr = NULL;
  ClkSourceConfigTableApi *pClkSrcCfgTblApiRcvdPtr = NULL;     
  LOG_PRINT(INFO,"%s:",__func__);

  if ((CmMsgPtr = (sCmMsg *)AlocMsgBuf(sizeof(ClkSourceConfigTableApi)+sizeof(sCmMsg))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }

  FILL_SYS_HDR( &CmMsgPtr->sHdr, 
                1, 
                0, 
                0, 
                ENT_OAM_CM, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  CmMsgPtr->cmHdr.size = sizeof(ClkSourceConfigTableApi);

  pClkSrcCfgTblApiRcvdPtr = (ClkSourceConfigTableApi *)(CmMsgPtr+1);
  
  
  return ;
}

I_Void addBichStepsTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  while (TRUE) {
    READ_MSG_FROM_QUEUE();
    switch ( READ_MSG_TYPE() ) {    
      case CM_API_APP_RESPONSE: 
        LOG_PRINT(INFO, "Msg Rcvd CM_API_APP_RESPONSE " );
        if (((sCmMsg *) RCVD_MSG_PTR)->cmHdr.status == 1) {
          tcResult=1;
        }
        return;
      default :;
    }  
  }
  return ;
}

I_Void addBichPostTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  return ;
}

I_Void addBichTC1(I_Void)
{
  LOG_PRINT(INFO,"%s:",__func__);
  addBichPreTC1();
  addBichStepsTC1();
  addBichPostTC1();
  return ;
}

/*-----------------------------------------------------------------------*/
I_PU8 addBichTestCaseDescription(I_U32 testCaseId) {
  switch (testCaseId) {
    case TEST_CASE_ADD_BICH_ALL:
      return "ALL CLK SRC CFG TCs";
    case TEST_CASE1_ADD_BICH:
      return "ADD BICH ";
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    
  }
  return NULL;
}

I_Void ExecuteAddBichGroup(I_U32 testCaseId) 
{
  switch (testCaseId) {
    default: 
      LOG_PRINT(CRITICAL,"Please Implement the testcase branch %s",__func__);
    case TEST_CASE_ADD_BICH_ALL:
    case TEST_CASE1_ADD_BICH:    
      LOG_PRINT(CRITICAL,"****************************************************");
      TEST_CASE_ID = TEST_CASE1_ADD_BICH;
      tcResult=PASS;      
      LOG_PRINT(CRITICAL,"Executing TG[%d],TC[%d]",TEST_GROUP_ID, TEST_CASE_ID);      
      addBichTC1();
      PRINT_TEST_RESULT();      
      if (TEST_CASE_ADD_BICH_ALL != testCaseId ) {
        break;
      }
  }
  return ;
}

