/***********************************File Header ***************************
File Name        : testsuit.h
Purpose          : This file has definitons used for testcases and groups.
                   Allocate and Add the testcase to this file. 
Project          : BSC/UTE
Subsystem        : UTE
Author           : BB/VNL/Gurgaon
************************************* End **********************************/
#ifndef __TESTSUIT_H_
#define __TESTSUIT_H_

#define MUT                                   ENT_OAMS_BICH
#define ENT_UTE_MC                            ENT_IPC_TEST1

enum {
      TEST_GROUP_START,
      TEST_GROUP_ADD_BICH, 
      TEST_GROUP_END,
      ALL_TEST_GROUP=254,
      EXIT_UTE=255,
} eTestGroup;

enum {
      TEST_CASE_ADD_BICH_START,
      TEST_CASE1_ADD_BICH,
      TEST_CASE_ADD_BICH_END,
      TEST_CASE_ADD_BICH_ALL=254,
      RESERVED0=255 // To support EXIT UTE 
} eTestCaseClkSrc;

/* 
** PreTestCaseAction
** This implements the action that needs to be executed before the actual testcase
** can be executed. This basically sets the preconditions required by the testcase

** TestCaseSteps
** This implements the steps of the testcases basically sending the messages

** PostTestCaseAction
** This implement the post testcase action like printing the values of DB/Internal state
*/
#define PreTestCaseActionIdx                     0
#define TestCaseStepsIdx                         1
#define PostTestCaseActionIdx                    2

#define DBG_FILE_NAME         "UTElog.log"
#define DBG_FILE_PTR          fp_log
#define DBG(DbgString)        fprintf(fp_log,"\n"DbgString)


#define FALSE                 0
#define TRUE                  1

#define PASS                  1
#define FAIL                  0

#define PARTIAL_OK            0
#define ALL_OK                1
#define ALL_FAIL              2
#define mkstr(str)  #str
#define CALLCLEANDBTABLE(xxxTypeTable) clean##xxxTypeTable()
#define CLEANDBTABLEIMPLEMENTATION(xxxTypeTable) \
I_Void clean##xxxTypeTable (I_Void) \
{                                   \
    xxxTypeTable##Api *outData;     \
    I_U32 outRows;                  \
    I_U32 index;                    \
    I_U16 outSize;                  \
    if ( getall##xxxTypeTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {  \
       for (index=0;index<outRows;index++) {                                      \
          if ( delete##xxxTypeTable( (xxxTypeTable##Indices *)((I_U8 *)outData + (index*outSize)))  \
               != CLIB_SUCCESS) {                                                                   \
            LOG_PRINT(LOG_CRITICAL,"delete DB call Failed for "mkstr(xxxTypeTable));                \
          }                                                                                         \
       }                                                                                            \
    }                                                                                               \
    LOG_PRINT(LOG_INFO,"Cleanup OK for "mkstr(xxxTypeTable));                                       \
}

#define ISTABLEEMPTY(xxxTypeTable)  do {                                                  \
    xxxTypeTable##Api *outData;                                                           \
    I_U32 outRows;                                                                        \
    I_U32 index;                                                                          \
    I_U16 outSize;                                                                        \
    if ( getall##xxxTypeTable(  &outData, &outRows, &outSize) == CLIB_SUCCESS) {          \
      LOG_PRINT(LOG_CRITICAL,"Not Empty "mkstr(xxxTypeTable));                            \
      TEST_RESULT=0;                                                                      \
    }                                                                                     \
} while (0)


I_PU8 testGroupId2String(I_U32);
I_PU8 testCaseId2Description(I_U32,I_U32);
I_PU8 addBichTestCaseDescription(I_U32);
I_Void ExecuteAddBichGroup(I_U32);
I_Void ExecuteTestSuit(I_U32,I_U32);
I_PVoid msgRcvr(I_Void);
I_Void displaySubMenu();
I_Void displayMainMenu();
I_Void ExecuteTestSuite();
  


extern I_U32 TEST_GROUP_ID, TEST_CASE_ID, TEST_RESULT;
extern I_PU8 msgRcvP ;
extern I_PVoid sndMsgP ;
/* Prototypes for functions of the testcases */

//TestCases
I_Void addBichTC1(I_Void);
I_U32 getMsgOpCode(const char * const mName);
//Macro Section
#define READ_MSG_FROM_QUEUE() msgRcvP =  msgRcvr()
#define READ_MSG_TYPE() (((SysHdr*) msgRcvP)->msgType)
#define READ_MSG_SRC() ( ((SysHdr*) msgRcvP)->src.entity)
#define READ_MSG_DST() ( ((SysHdr*) msgRcvP)->dest.entity)
#define RCVD_MSG_PTR   (msgRcvP)
#define PRINT_TEST_RESULT() do {\
          if (TEST_RESULT) {LOG_PRINT(CRITICAL,"Verdict Pass:TG[%d]TC[%d]",TEST_GROUP_ID,TEST_CASE_ID);} \
          else {LOG_PRINT(CRITICAL,"Verdict Fail:TG[%d]TC[%d]",TEST_GROUP_ID,TEST_CASE_ID);} \
        } while (0)  
/*******************************/
extern I_U32 gTrxId, gBtsId, gE1Id, gTsVal,gBtsType,gLapdLinkStatus,gOprState,gAdminState, gTei,gTrxOpr;
I_PVoid sndMsg( I_PU8 msgName);
I_Void receiveMsg();

#endif /* __TESTSUIT_H_ */
