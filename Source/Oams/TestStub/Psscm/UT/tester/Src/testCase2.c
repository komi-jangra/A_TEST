#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  6
int test_result[totalNoOfTC];
void setup (void)
{
  /* Setup Procedure to be written (if any)*/
}


void teardown (void)
{
  /* TearDown Procedure to be written (if any)*/
}


/**************************************************************************
 TC Name: TC_001

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_UNLOCK_REQ is received in PsscmIdle state.
**************************************************************************/
START_TEST (TC_001)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmUnlockReq oamsCfgPsscmUnlockReq;

  /*Receive Message Struct */
   OamsPsscmNsProvNsei oamsPsscmNsProvNsei;
   oamsCfgPsscmUnlockReq.sysHdr.src.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPsscmUnlockReq.sysHdr.src.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsCfgPsscmUnlockReq.sysHdr.dest.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.msgType = OAMS_CFG_PSSCM_UNLOCK_REQ;
   oamsCfgPsscmUnlockReq.sysHdr.subType = 0;
   oamsCfgPsscmUnlockReq.sysHdr.priority = 0;
   oamsCfgPsscmUnlockReq.reason = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPsscmUnlockReq,sizeof(OamsCfgPsscmUnlockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvNsei = *((OamsPsscmNsProvNsei *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvNsei.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.sysHdr.msgType == OAMS_PSSCM_NS_PROV_NSEI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvNsei.type == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvNsei.type is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_003

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForProvNseiCnf state.
**************************************************************************/
START_TEST (TC_003)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmLockReq oamsCfgPsscmLockReq;

  /*Receive Message Struct */
   oamsCfgPsscmLockReq.sysHdr.src.prcr = PRCR_PP;
   oamsCfgPsscmLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPsscmLockReq.sysHdr.src.clsId = 0;
   oamsCfgPsscmLockReq.sysHdr.src.rfu = 0;
   oamsCfgPsscmLockReq.sysHdr.src.inst = 0;
   oamsCfgPsscmLockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgPsscmLockReq.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsCfgPsscmLockReq.sysHdr.dest.clsId = 0;
   oamsCfgPsscmLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPsscmLockReq.sysHdr.dest.inst = 0;
   oamsCfgPsscmLockReq.sysHdr.msgType = OAMS_CFG_PSSCM_LOCK_REQ;
   oamsCfgPsscmLockReq.sysHdr.subType = 0;
   oamsCfgPsscmLockReq.sysHdr.priority = 0;
   oamsCfgPsscmLockReq.reason = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPsscmLockReq,sizeof(OamsCfgPsscmLockReq));

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_004

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_NSEI_CNF is received in WaitForProvNseiCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_004)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvNseiCnf pssksNsPsscmProvNseiCnf;

  /*Receive Message Struct */
   OamsPsscmNsProvSigBvc oamsPsscmNsProvSigBvc;
   pssksNsPsscmProvNseiCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvNseiCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_NSEI_CNF;
   pssksNsPsscmProvNseiCnf.sysHdr.subType = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.priority = 0;
   pssksNsPsscmProvNseiCnf.bufLen = 0;
   pssksNsPsscmProvNseiCnf.trId = 0;
   pssksNsPsscmProvNseiCnf.apiId = 0;
   pssksNsPsscmProvNseiCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvNseiCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvNseiCnf,sizeof(PssksNsPsscmProvNseiCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvSigBvc = *((OamsPsscmNsProvSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.sysHdr.msgType == OAMS_PSSCM_NS_PROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[3] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[3] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_005

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_NSEI_CNF is received in WaitForProvNseiCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_005)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvNseiCnf pssksNsPsscmProvNseiCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovNsei oamsPsscmNsUnprovNsei;
   pssksNsPsscmProvNseiCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvNseiCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_NSEI_CNF;
   pssksNsPsscmProvNseiCnf.sysHdr.subType = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.priority = 0;
   pssksNsPsscmProvNseiCnf.bufLen = 0;
   pssksNsPsscmProvNseiCnf.trId = 0;
   pssksNsPsscmProvNseiCnf.apiId = 0;
   pssksNsPsscmProvNseiCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvNseiCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvNseiCnf,sizeof(PssksNsPsscmProvNseiCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovNsei = *((OamsPsscmNsUnprovNsei *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovNsei.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_NSEI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovNsei.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.nsei is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[4] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[4] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_006

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_NSEI_CNF is received in WaitForProvNseiCnf state. Preconfiguration : {result = BSS_FAILURE, ongoingAction = UNLOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_006)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvNseiCnf pssksNsPsscmProvNseiCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksNsPsscmProvNseiCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvNseiCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_NSEI_CNF;
   pssksNsPsscmProvNseiCnf.sysHdr.subType = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.priority = 0;
   pssksNsPsscmProvNseiCnf.bufLen = 0;
   pssksNsPsscmProvNseiCnf.trId = 0;
   pssksNsPsscmProvNseiCnf.apiId = 0;
   pssksNsPsscmProvNseiCnf.result = BSS_FAILURE;
   pssksNsPsscmProvNseiCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvNseiCnf,sizeof(PssksNsPsscmProvNseiCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgUnlockResp = *((OamsPsscmCfgUnlockResp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgUnlockResp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.msgType == OAMS_PSSCM_CFG_UNLOCK_RESP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[5] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[5] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_007

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_NSEI_CNF is received in WaitForProvNseiCnf state. Preconfiguration : {result = BSS_FAILURE, ongoingAction = LOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_007)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvNseiCnf pssksNsPsscmProvNseiCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmProvNseiCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvNseiCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_NSEI_CNF;
   pssksNsPsscmProvNseiCnf.sysHdr.subType = 0;
   pssksNsPsscmProvNseiCnf.sysHdr.priority = 0;
   pssksNsPsscmProvNseiCnf.bufLen = 0;
   pssksNsPsscmProvNseiCnf.trId = 0;
   pssksNsPsscmProvNseiCnf.apiId = 0;
   pssksNsPsscmProvNseiCnf.result = BSS_FAILURE;
   pssksNsPsscmProvNseiCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvNseiCnf,sizeof(PssksNsPsscmProvNseiCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgLockResp = *((OamsPsscmCfgLockResp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgLockResp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.msgType == OAMS_PSSCM_CFG_LOCK_RESP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[6] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[6] = 1;    /* 1 for pass*/

}
END_TEST


 
int RunTestSuite(Suite * s)
{
   int number_failed;
   SRunner *sr = srunner_create(s);
   srunner_set_log(sr,"result.txt");
   srunner_set_fork_status(sr, CK_NOFORK);
   srunner_run_all(sr,CK_NORMAL);
   number_failed = srunner_ntests_failed (sr);
   srunner_free(sr);
   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
 
 
void ExecuteTestSuite(void)
{
   int iChoice; 
   int iTCChoice; 
   int iTSChoice; 
   int iTSSChoice; 
   do{
 
      system("clear");
      printf("\n0: Exit ");  
      printf("\n1: Run Elementary Test case(s) ");  
      printf("\n2: Run Test Suite(s) ");  
      printf("\nEnter your choice :  ");  
      scanf("%d",&iChoice); 
      if(1 == iChoice)
      { 
        do{
       Suite *s = suite_create ("CFG");
       /* Core test case */
       TCase *tc_core = tcase_create ("Core");
       tcase_add_checked_fixture (tc_core, setup, teardown);
        system("clear");
        printf("\n0 : Previous Menu");
        printf("\n1. Run TC_001");
        printf("\n2. Run TC_003");
        printf("\n3. Run TC_004");
        printf("\n4. Run TC_005");
        printf("\n5. Run TC_006");
        printf("\n6. Run TC_007");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_001);
           printf("\nRunning Test Case TC_001"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 3 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_003);
           printf("\nRunning Test Case TC_003"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 4 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_004);
           printf("\nRunning Test Case TC_004"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 5 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_005);
           printf("\nRunning Test Case TC_005"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 6 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_006);
           printf("\nRunning Test Case TC_006"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 7 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_007);
           printf("\nRunning Test Case TC_007"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
        }
           }while(iTCChoice != 0);
      }
    if(2 == iChoice)
     {
      do{
       Suite *s = suite_create ("CFG");
        system("clear");
        printf("\n0 : Previous Menu");
        printf("\n 100: Run all Test Suits");
        printf("\nPlease enter your choice : ");
        scanf("%d",&iTSChoice); 
         if( 100 == iTSChoice)  
         {
               printf("Running all Test Suites...");
               RunTestSuite(s);
         }
         }while(iTSChoice != 0);
      }
 
     }while(iChoice!=0);
    printf("\nExiting...");
    system("clear");
}


