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

#define MUT                                   ENT_OAMS_CFG
#define ENT_UTE_MC                            ENT_IPC_TEST1
#define MAX_TEST_GROUP                        1 // Feature
#define MAX_TEST_CASES_IN_TEST_GROUP          6 // Planned testcases in Feature

enum {
      TEST_GROUP_START,
      TEST_GROUP_CLK_SRC_CFG, 
      TEST_GROUP_STK_SRC_CFG,
      TEST_GROUP_STK_ADDM_CFG,
      TEST_GROUP_TP_USG_CHG_CFG,
      TEST_GROUP_TP_ADMN_CHG_CFG,
      TEST_GROUP_BIC_LOCK_UNLOCK_CFG,
      TEST_GROUP_END,
      ALL_TEST_GROUP=254,
      EXIT_UTE=255,
} eTestGroup;

enum {
      TEST_CASE_CLK_SRC_CFG_START,
      TEST_CASE1_CLK_SRC_CFG,
      TEST_CASE2_CLK_SRC_CFG,
      TEST_CASE3_CLK_SRC_CFG,
      TEST_CASE4_CLK_SRC_CFG,
      TEST_CASE5_CLK_SRC_CFG,
      TEST_CASE6_CLK_SRC_CFG,
      TEST_CASE7_CLK_SRC_CFG,
      TEST_CASE8_CLK_SRC_CFG,
      TEST_CASE9_CLK_SRC_CFG,
      TEST_CASE10_CLK_SRC_CFG,
      TEST_CASE11_CLK_SRC_CFG,
      TEST_CASE12_CLK_SRC_CFG,
      TEST_CASE13_CLK_SRC_CFG,
      TEST_CASE14_CLK_SRC_CFG,
      TEST_CASE15_CLK_SRC_CFG,
      TEST_CASE16_CLK_SRC_CFG,
      TEST_CASE17_CLK_SRC_CFG,
      TEST_CASE_CLK_SRC_CFG_END,
      TEST_CASE_CLK_SRC_CFG_ALL = 254,
      RESERVED0=255 // To support EXIT UTE 
} eTestCaseClkSrc;

enum {
      TEST_CASE_STK_SRC_CFG_START,
      TEST_CASE1_STK_SRC_CFG,
      TEST_CASE2_STK_SRC_CFG,
      TEST_CASE3_STK_SRC_CFG,
      TEST_CASE4_STK_SRC_CFG,
      TEST_CASE5_STK_SRC_CFG,
      TEST_CASE6_STK_SRC_CFG,
      TEST_CASE7_STK_SRC_CFG,
      TEST_CASE8_STK_SRC_CFG,
      TEST_CASE9_STK_SRC_CFG,
      TEST_CASE10_STK_SRC_CFG,
      TEST_CASE11_STK_SRC_CFG,
      TEST_CASE12_STK_SRC_CFG,
      TEST_CASE13_STK_SRC_CFG,
      TEST_CASE14_STK_SRC_CFG,
      TEST_CASE15_STK_SRC_CFG,
      TEST_CASE16_STK_SRC_CFG,
      TEST_CASE17_STK_SRC_CFG,
      TEST_CASE18_STK_SRC_CFG,
      TEST_CASE19_STK_SRC_CFG,
      TEST_CASE20_STK_SRC_CFG,
      TEST_CASE21_STK_SRC_CFG,
      TEST_CASE22_STK_SRC_CFG,
      TEST_CASE23_STK_SRC_CFG,
      TEST_CASE24_STK_SRC_CFG,
      TEST_CASE25_STK_SRC_CFG,
      TEST_CASE26_STK_SRC_CFG,
      TEST_CASE27_STK_SRC_CFG,
      TEST_CASE28_STK_SRC_CFG,
      TEST_CASE29_STK_SRC_CFG,
      TEST_CASE30_STK_SRC_CFG,
      TEST_CASE31_STK_SRC_CFG,
      TEST_CASE_STK_SRC_CFG_END,
      TEST_CASE_STK_SRC_CFG_ALL = 254,
      RESERVED1=255 //To support EXIT UTE 
} eTestCaseStkSrc;

enum {
      TEST_CASE_STK_ADDM_CFG_START,
      TEST_CASE1_STK_ADDM_CFG,
      TEST_CASE2_STK_ADDM_CFG,
      TEST_CASE3_STK_ADDM_CFG,
      TEST_CASE4_STK_ADDM_CFG,
      TEST_CASE5_STK_ADDM_CFG,
      TEST_CASE6_STK_ADDM_CFG,
      TEST_CASE7_STK_ADDM_CFG,
      TEST_CASE8_STK_ADDM_CFG,
      TEST_CASE9_STK_ADDM_CFG,
      TEST_CASE10_STK_ADDM_CFG,
      TEST_CASE11_STK_ADDM_CFG,
      TEST_CASE12_STK_ADDM_CFG,
      TEST_CASE13_STK_ADDM_CFG,
      TEST_CASE14_STK_ADDM_CFG,
      TEST_CASE15_STK_ADDM_CFG,
      TEST_CASE16_STK_ADDM_CFG,
      TEST_CASE17_STK_ADDM_CFG,
      TEST_CASE18_STK_ADDM_CFG,
      TEST_CASE19_STK_ADDM_CFG,
      TEST_CASE20_STK_ADDM_CFG,
      TEST_CASE21_STK_ADDM_CFG,
      TEST_CASE22_STK_ADDM_CFG,
      TEST_CASE23_STK_ADDM_CFG,
      TEST_CASE24_STK_ADDM_CFG,
      TEST_CASE25_STK_ADDM_CFG,
      TEST_CASE26_STK_ADDM_CFG,
      TEST_CASE27_STK_ADDM_CFG,
      TEST_CASE28_STK_ADDM_CFG,
      TEST_CASE29_STK_ADDM_CFG,
      TEST_CASE30_STK_ADDM_CFG,
      TEST_CASE31_STK_ADDM_CFG,
      TEST_CASE32_STK_ADDM_CFG,
      TEST_CASE33_STK_ADDM_CFG,
      TEST_CASE34_STK_ADDM_CFG,
      TEST_CASE35_STK_ADDM_CFG,
      TEST_CASE36_STK_ADDM_CFG,
      TEST_CASE37_STK_ADDM_CFG,
      TEST_CASE38_STK_ADDM_CFG,
      TEST_CASE39_STK_ADDM_CFG,
      TEST_CASE40_STK_ADDM_CFG,
      TEST_CASE41_STK_ADDM_CFG,
      TEST_CASE42_STK_ADDM_CFG,
      TEST_CASE43_STK_ADDM_CFG,
      TEST_CASE44_STK_ADDM_CFG,
      TEST_CASE45_STK_ADDM_CFG,
      TEST_CASE46_STK_ADDM_CFG,
      TEST_CASE47_STK_ADDM_CFG,
      TEST_CASE48_STK_ADDM_CFG,
      TEST_CASE49_STK_ADDM_CFG,
      TEST_CASE50_STK_ADDM_CFG,
      TEST_CASE51_STK_ADDM_CFG,
      TEST_CASE52_STK_ADDM_CFG,
      TEST_CASE53_STK_ADDM_CFG,
      TEST_CASE54_STK_ADDM_CFG,
      TEST_CASE55_STK_ADDM_CFG,
      TEST_CASE56_STK_ADDM_CFG,
      TEST_CASE57_STK_ADDM_CFG,
      TEST_CASE58_STK_ADDM_CFG,
      TEST_CASE59_STK_ADDM_CFG,
      TEST_CASE60_STK_ADDM_CFG,
      TEST_CASE61_STK_ADDM_CFG,
      TEST_CASE62_STK_ADDM_CFG,
      TEST_CASE63_STK_ADDM_CFG,
      TEST_CASE64_STK_ADDM_CFG,
      TEST_CASE65_STK_ADDM_CFG,
      TEST_CASE66_STK_ADDM_CFG,
      TEST_CASE67_STK_ADDM_CFG,
      TEST_CASE68_STK_ADDM_CFG,
      TEST_CASE69_STK_ADDM_CFG,
      TEST_CASE70_STK_ADDM_CFG,
      TEST_CASE71_STK_ADDM_CFG,
      TEST_CASE72_STK_ADDM_CFG,
      TEST_CASE73_STK_ADDM_CFG,
      TEST_CASE74_STK_ADDM_CFG,
      TEST_CASE75_STK_ADDM_CFG,
      TEST_CASE76_STK_ADDM_CFG,
      TEST_CASE77_STK_ADDM_CFG,
      TEST_CASE78_STK_ADDM_CFG,
      TEST_CASE79_STK_ADDM_CFG,
      TEST_CASE80_STK_ADDM_CFG,
      TEST_CASE81_STK_ADDM_CFG,
      TEST_CASE82_STK_ADDM_CFG,
      TEST_CASE83_STK_ADDM_CFG,
      TEST_CASE84_STK_ADDM_CFG,
      TEST_CASE85_STK_ADDM_CFG,
      TEST_CASE86_STK_ADDM_CFG,
      TEST_CASE87_STK_ADDM_CFG,
      TEST_CASE88_STK_ADDM_CFG,
      TEST_CASE89_STK_ADDM_CFG,
      TEST_CASE90_STK_ADDM_CFG,
      TEST_CASE91_STK_ADDM_CFG,
      TEST_CASE92_STK_ADDM_CFG,
      TEST_CASE93_STK_ADDM_CFG,
      TEST_CASE94_STK_ADDM_CFG,
      TEST_CASE95_STK_ADDM_CFG,
      TEST_CASE96_STK_ADDM_CFG,
      TEST_CASE97_STK_ADDM_CFG,
      TEST_CASE98_STK_ADDM_CFG,
      TEST_CASE99_STK_ADDM_CFG,
      TEST_CASE100_STK_ADDM_CFG,
      TEST_CASE101_STK_ADDM_CFG,
      TEST_CASE102_STK_ADDM_CFG,
      TEST_CASE103_STK_ADDM_CFG,
      TEST_CASE104_STK_ADDM_CFG,
      TEST_CASE105_STK_ADDM_CFG,
      TEST_CASE_STK_ADDM_CFG_END,
      TEST_CASE_STK_ADDM_CFG_ALL = 254,
      RESERVED2=255 //To support EXIT UTE 
} eTestCaseStkAddMod;

enum {
      TEST_CASE_TP_USG_CHG_CFG_START,
      TEST_CASE1_TP_USG_CHG_CFG,
      TEST_CASE2_TP_USG_CHG_CFG,
      TEST_CASE3_TP_USG_CHG_CFG,
      TEST_CASE4_TP_USG_CHG_CFG,
      TEST_CASE5_TP_USG_CHG_CFG,
      TEST_CASE6_TP_USG_CHG_CFG,
      TEST_CASE7_TP_USG_CHG_CFG,
      TEST_CASE8_TP_USG_CHG_CFG,
      TEST_CASE9_TP_USG_CHG_CFG,
      TEST_CASE10_TP_USG_CHG_CFG,
      TEST_CASE11_TP_USG_CHG_CFG,
      TEST_CASE12_TP_USG_CHG_CFG,
      TEST_CASE13_TP_USG_CHG_CFG,
      TEST_CASE14_TP_USG_CHG_CFG,
      TEST_CASE15_TP_USG_CHG_CFG,
      TEST_CASE16_TP_USG_CHG_CFG,
      TEST_CASE17_TP_USG_CHG_CFG,
      TEST_CASE18_TP_USG_CHG_CFG,
      TEST_CASE19_TP_USG_CHG_CFG,
      TEST_CASE20_TP_USG_CHG_CFG,
      TEST_CASE21_TP_USG_CHG_CFG,
      TEST_CASE22_TP_USG_CHG_CFG,
      TEST_CASE23_TP_USG_CHG_CFG,
      TEST_CASE24_TP_USG_CHG_CFG,
      TEST_CASE25_TP_USG_CHG_CFG,
      TEST_CASE26_TP_USG_CHG_CFG,
      TEST_CASE27_TP_USG_CHG_CFG,
      TEST_CASE28_TP_USG_CHG_CFG,
      TEST_CASE29_TP_USG_CHG_CFG,
      TEST_CASE30_TP_USG_CHG_CFG,
      TEST_CASE_TP_USG_CHG_CFG_END,
      TEST_CASE_TP_USG_CHG_CFG_ALL = 254,
      RESERVED3=255 //To support EXIT UTE 
} eTestCaseTpUsageChange;

enum {
      TEST_CASE_TP_ADMN_CHG_CFG_START,
      TEST_CASEENABLE_TP_ADMN_CHG_CFG,
      TEST_CASE31_TP_ADMN_CHG_CFG,
      TEST_CASE32_TP_ADMN_CHG_CFG,
      TEST_CASE33_TP_ADMN_CHG_CFG,
      TEST_CASEDISABLE_TP_ADMN_CHG_CFG,
      TEST_CASE35_TP_ADMN_CHG_CFG,
      TEST_CASE36_TP_ADMN_CHG_CFG,
      TEST_CASE_TP_ADMN_CHG_CFG_END,
      TEST_CASE_TP_ADMN_CHG_CFG_ALL = 254,
      RESERVED4=255 //To support EXIT UTE 
} eTestCaseTpAdmnChange;

enum {
      TEST_CASE_BIC_LOCK_UNLOCK_CFG_START,
      TEST_CASE1_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE2_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE3_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE4_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE5_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE6_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE7_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE8_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE9_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE10_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE11_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE12_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE13_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE14_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE15_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE16_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE17_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE18_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE19_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE20_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE21_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE22_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE23_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE24_BIC_LOCK_UNLOCK_CFG,
      TEST_CASE_BIC_LOCK_UNLOCK_CFG_END,
      TEST_CASE_BIC_LOCK_UNLOCK_CFG_ALL = 254,
      RESERVED5=255 //To support EXIT UTE 
} eTestCaseBicLockUnlock;


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

#define E1_TRUNK_TYPE         1
#define T1_TRUNK_TYPE         2

#define OPERATOR_DISABLE      0
#define OPERATOR_ENABLE       1

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

typedef I_Void (*ActionFuncPtr) (I_Void) ;

typedef struct {
  ActionFuncPtr TestCase;
} sTestSuitElem;

extern sTestSuitElem testSuitList[MAX_TEST_GROUP][MAX_TEST_CASES_IN_TEST_GROUP];
extern I_U32 TEST_GROUP_ID, TEST_CASE_ID, TEST_RESULT;
extern I_PU8 msgRcvP ;
extern I_U32 scmRespAction;
extern I_U32 switchConnResp;
/* Prototypes for functions of the testcases */

I_PU8 stkSrcTestCaseDescription(I_U32);
I_PU8 clkSrcTestCaseDescription(I_U32);
I_Void TestCaseInitCfg(I_Void);

I_PU8 testGroupId2String(I_U32);
I_PU8 testCaseId2Description(I_U32,I_U32);
I_Void ExecuteTestSuit(I_U32,I_U32);
I_Void ExecuteClkGroup(I_U32);
I_Void ExecuteStkGroup(I_U32);
I_Void TestCaseInitCfg(I_Void);
I_PVoid msgRcvr(I_Void);
I_U8 ExecuteOilAction(I_PVoid rcvPtr);
I_Void SendMsgToIPC(I_PVoid sndPtr, I_S32 sndMsgSz, I_S8* msgName);
I_Void addAbisInterfaceTable(I_U16 ifId, I_U32 bicId, I_U32 ifType);
I_Void addSs7StackConfigTable(I_U32 opc, I_U32 family, I_U32 alarmLevel);
I_Void addAifInterfaceTable(I_U16 ifId,I_U32 ifType,I_U32 dpc,I_U32 tgpId);
I_Void addLinksetTable(I_U16 linkSetId,I_U16 ifId,I_U32 apc,I_U32 ni);
I_Void addTrunkTable(I_U16 interfaceId,I_U16 tgpId,I_U32 e1Num,I_U32 startCic,I_U32 endCic,I_U32 trunkType,I_U32 tsCicMap);
I_Void addLinkTable(I_U16 linkSetId,I_U16 linkId,I_U16 slc,I_U32 e1Num,I_U8 ts,I_U32 cardNum,I_U32 crcFlag,I_U32 adminState);
I_Void addCicTable(I_U16 interfaceId,I_U16 tgpId,I_U32 e1Num,I_U8 timeSlot,I_U32 cicId,I_U32 adminState);
I_Void addTrunkGroupTable(I_U16 interfaceId,I_U16 tgpId);
I_S32 cfgStubSendCmMessage(void *buff, I_U32 size, I_U32 MessageType);
I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_U16 msgType,I_U8 subType);
I_Void ExecuteGrhmAction(I_PVoid rcvPtr);

I_PU8 bicLockUnlockTestCaseDescription(I_U32);
I_Void ExecuteBicLockUnlockGroup(I_U32);

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
#define IsImplementaionExist(TEST_GROUP_ID,TEST_CASE_ID) (testSuitList[(TEST_GROUP_ID)][(TEST_CASE_ID)] != NULL)
#endif /* __TESTSUIT_H_ */
