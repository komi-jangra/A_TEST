#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  87
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
 TC Name: TC_002

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_UNLOCK_REQ is received in PsscmIdle state and Db call for populating local context fails .
**************************************************************************/
START_TEST (TC_002)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmUnlockReq oamsCfgPsscmUnlockReq;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

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
      test_result[3] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[3] = 1;    /* 1 for pass*/

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
      test_result[4] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[4] = 1;    /* 1 for pass*/

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
      test_result[5] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[5] = 1;    /* 1 for pass*/

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[6] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[6] = 1;    /* 1 for pass*/

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[7] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[7] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_008

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF is received in WaitForNsProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_008)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvSigBvcCnf pssksNsPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmBssgpProvSigBvc oamsPsscmBssgpProvSigBvc;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF;
   pssksNsPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmProvSigBvcCnf.bufLen = 0;
   pssksNsPsscmProvSigBvcCnf.trId = 0;
   pssksNsPsscmProvSigBvcCnf.apiId = 0;
   pssksNsPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvSigBvcCnf,sizeof(PssksNsPsscmProvSigBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmBssgpProvSigBvc = *((OamsPsscmBssgpProvSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_BSSGP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.sysHdr.msgType == OAMS_PSSCM_BSSGP_PROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[8] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[8] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_009

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF is received in WaitForNsProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_009)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvSigBvcCnf pssksNsPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovSigBvc oamsPsscmNsUnprovSigBvc;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF;
   pssksNsPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmProvSigBvcCnf.bufLen = 0;
   pssksNsPsscmProvSigBvcCnf.trId = 0;
   pssksNsPsscmProvSigBvcCnf.apiId = 0;
   pssksNsPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvSigBvcCnf,sizeof(PssksNsPsscmProvSigBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovSigBvc = *((OamsPsscmNsUnprovSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[9] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[9] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_010

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF is received in WaitForNsProvSigBvcCnf state. Preconfiguration : {result = BSS_FAILURE}
**************************************************************************/
START_TEST (TC_010)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvSigBvcCnf pssksNsPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovNsei oamsPsscmNsUnprovNsei;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF;
   pssksNsPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmProvSigBvcCnf.bufLen = 0;
   pssksNsPsscmProvSigBvcCnf.trId = 0;
   pssksNsPsscmProvSigBvcCnf.apiId = 0;
   pssksNsPsscmProvSigBvcCnf.result = BSS_FAILURE;
   pssksNsPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvSigBvcCnf,sizeof(PssksNsPsscmProvSigBvcCnf));

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
      test_result[10] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[10] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_011

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForNsProvSigBvcCnf state.
**************************************************************************/
START_TEST (TC_011)
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
      test_result[11] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[11] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_012

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForBssgpProvSigBvcCnf state.
**************************************************************************/
START_TEST (TC_012)
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
      test_result[12] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[12] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_013

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = IP_STATIC, dbResult = CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_013)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsProvLep oamsPsscmNsProvLep;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

  /*Receiving of Message*/
                             
 AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvLep = *((OamsPsscmNsProvLep *)buffer);
  I_U8 *tempBuffer;
  tempBuffer = (I_U8 *)malloc(sizeof(OamsPsscmNsProvLep) + sizeof(LepIpElemInfo));
  memcpy(tempBuffer,buffer, size);
  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvLep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.msgType == OAMS_PSSCM_NS_PROV_LEP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.msgType is not correct ");
                                                                                                                          break;
   }
   if(!(oamsPsscmNsProvLep.apiId == OAM_NS_PROV_LOCAL_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.listType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.numIp == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   LepIpElemInfo * lepIpElemInfoPtr;
   lepIpElemInfoPtr = (((OamsPsscmNsProvLep *)tempBuffer)->lepIpElemInfo);
   if(!(lepIpElemInfoPtr->refId == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->ip4Addr == 1))
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->udpPort == 2) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
  if(!(lepIpElemInfoPtr->sigWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->dataWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
/*   if(!(oamsPsscmNsProvLep.lepIpElemInfo[0].refId == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.lepIpElemInfo[0].ip4Addr == 1))
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.lepIpElemInfo[0].udpPort == 2) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.lepIpElemInfo[0].sigWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.lepIpElemInfo[0].dataWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }*/
  }while(0);
free(tempBuffer);
/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[13] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[13] = 1;    /* 1 for pass*/

}
END_TEST







/**************************************************************************
 TC Name: TC_014

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = IP_STATIC, dbResult != CLIB_SUCCESS} ie. when Db call to prepare prov LEP message fails
**************************************************************************/
START_TEST (TC_014)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[14] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[14] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_015

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = IP_DYNAMIC, dbResult = CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_015)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsProvLep oamsPsscmNsProvLep;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvLep = *((OamsPsscmNsProvLep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvLep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.sysHdr.msgType == OAMS_PSSCM_NS_PROV_LEP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.apiId == OAM_NS_PROV_LOCAL_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.listType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvLep.numIp == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[15] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[15] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_016

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = IP_DYNAMIC, dbResult != CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_016)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[16] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[16] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_017

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_017)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovSigBvc oamsPsscmNsUnprovSigBvc;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovSigBvc = *((OamsPsscmNsUnprovSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_BSSGP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.msgType == OAMS_PSSCM_BSSGP_UNPROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.apiId == BSSGP_UNPROVISION_BVC_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[17] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[17] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_018

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_FAILURE}
**************************************************************************/
START_TEST (TC_018)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovSigBvc oamsPsscmNsUnprovSigBvc;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_FAILURE;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovSigBvc = *((OamsPsscmNsUnprovSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_BSSGP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.msgType == OAMS_PSSCM_BSSGP_UNPROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.apiId == BSSGP_UNPROVISION_BVC_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[18] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[18] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_019

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF is received in WaitForBssgpProvSigBvcCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = FR}
**************************************************************************/
START_TEST (TC_019)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvSigBvcCnf pssksBssgpPsscmProvSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvSigBvcCnf.trId = 0;
   pssksBssgpPsscmProvSigBvcCnf.apiId = 0;
   pssksBssgpPsscmProvSigBvcCnf.bvci = 0;
   pssksBssgpPsscmProvSigBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvSigBvcCnf,sizeof(PssksBssgpPsscmProvSigBvcCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgUnlockResp.result == OAMS_RSLT_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[19] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[19] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_020

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_LEP_CNF is received in WaitForNsProvLepCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, dbResult = CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_020)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvLepCnf pssksNsPsscmProvLepCnf;

  /*Receive Message Struct */
   OamsPsscmNsProvRep oamsPsscmNsProvRep;
   pssksNsPsscmProvLepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvLepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvLepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_LEP_CNF;
   pssksNsPsscmProvLepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvLepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvLepCnf.bufLen = 0;
   pssksNsPsscmProvLepCnf.trId = 0;
   pssksNsPsscmProvLepCnf.apiId = 0;
   pssksNsPsscmProvLepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvLepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvLepCnf,sizeof(PssksNsPsscmProvLepCnf));

  /*Receiving of Message*/
                                                                                             
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvRep = *((OamsPsscmNsProvRep *)buffer);

  I_U8 *tempBuffer;
  tempBuffer = (I_U8 *)malloc(sizeof(OamsPsscmNsProvRep) + sizeof(RepIpElemInfo));
  memcpy(tempBuffer,buffer, size);
  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.sysHdr.msgType == OAMS_PSSCM_NS_PROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.apiId == OAM_NS_PROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.listType is not correct ");
      break;
   }

   RepIpElemInfo * repIpElemInfoPtr;
   repIpElemInfoPtr = (((OamsPsscmNsProvRep *)tempBuffer)->repIpElemInfo);
   if(!(repIpElemInfoPtr->ip4Addr == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->udpPort == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->sigWeight == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->dataWeight == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
                                                                  break;
   }
free(tempBuffer);
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[20] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[20] = 1;    /* 1 for pass*/

}
END_TEST




/**************************************************************************
 TC Name: TC_021

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_LEP_CNF is received in WaitForNsProvLepCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_021)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvLepCnf pssksNsPsscmProvLepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksNsPsscmProvLepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvLepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvLepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_LEP_CNF;
   pssksNsPsscmProvLepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvLepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvLepCnf.bufLen = 0;
   pssksNsPsscmProvLepCnf.trId = 0;
   pssksNsPsscmProvLepCnf.apiId = 0;
   pssksNsPsscmProvLepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvLepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvLepCnf,sizeof(PssksNsPsscmProvLepCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[21] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[21] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_022

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_LEP_CNF is received in WaitForNsProvLepCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS, dbResult = CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_022)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvLepCnf pssksNsPsscmProvLepCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovLep oamsPsscmNsUnprovLep;
   pssksNsPsscmProvLepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvLepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvLepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_LEP_CNF;
   pssksNsPsscmProvLepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvLepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvLepCnf.bufLen = 0;
   pssksNsPsscmProvLepCnf.trId = 0;
   pssksNsPsscmProvLepCnf.apiId = 0;
   pssksNsPsscmProvLepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvLepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvLepCnf,sizeof(PssksNsPsscmProvLepCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovLep = *((OamsPsscmNsUnprovLep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_LEP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.apiId == OAM_NS_UNPROV_LOCAL_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.listType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.refId[0] == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.refId[0] is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[22] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[22] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_023

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_LEP_CNF is received in WaitForNsProvLepCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS}
**************************************************************************/
START_TEST (TC_023)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvLepCnf pssksNsPsscmProvLepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmProvLepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvLepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvLepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_LEP_CNF;
   pssksNsPsscmProvLepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvLepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvLepCnf.bufLen = 0;
   pssksNsPsscmProvLepCnf.trId = 0;
   pssksNsPsscmProvLepCnf.apiId = 0;
   pssksNsPsscmProvLepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvLepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvLepCnf,sizeof(PssksNsPsscmProvLepCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[23] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[23] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_024

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_LEP_CNF is received in WaitForNsProvLepCnf state. Preconfiguration : {result = BSS_FAILURE}
**************************************************************************/
START_TEST (TC_024)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvLepCnf pssksNsPsscmProvLepCnf;

  /*Receive Message Struct */
   OamsPsscmBssgpUnprovSigBvc oamsPsscmBssgpUnprovSigBvc;
   pssksNsPsscmProvLepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvLepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvLepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvLepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvLepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvLepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_LEP_CNF;
   pssksNsPsscmProvLepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvLepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvLepCnf.bufLen = 0;
   pssksNsPsscmProvLepCnf.trId = 0;
   pssksNsPsscmProvLepCnf.apiId = 0;
   pssksNsPsscmProvLepCnf.result = BSS_FAILURE;
   pssksNsPsscmProvLepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvLepCnf,sizeof(PssksNsPsscmProvLepCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmBssgpUnprovSigBvc = *((OamsPsscmBssgpUnprovSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_BSSGP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.msgType == OAMS_PSSCM_BSSGP_UNPROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.apiId == BSSGP_UNPROVISION_BVC_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[24] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[24] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_025

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForNsProvLepCnf state. 
**************************************************************************/
START_TEST (TC_025)
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
      test_result[25] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[25] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_026

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForNsProvRepCnf state. 
**************************************************************************/
START_TEST (TC_026)
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

  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPsscmLockReq,sizeof(OamsCfgPsscmLockReq));

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[26] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[26] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_027

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = IP_STATIC }
**************************************************************************/
START_TEST (TC_027)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   OamsPsscmNsTestEnable oamsPsscmNsTestEnable;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgUnlockResp.result == OAMS_RSLT_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.result is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsTestEnable = *((OamsPsscmNsTestEnable *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsTestEnable.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.msgType == OAMS_PSSCM_NS_TEST_ENABLE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.apiId == OAM_NS_TEST_ENABLE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.apiId is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[27] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[27] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_028

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS, transportType = IP_DYNAMIC }
**************************************************************************/
START_TEST (TC_028)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   OamsPsscmNsAutoConfig oamsPsscmNsAutoConfig;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgUnlockResp.result == OAMS_RSLT_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.result is not correct ");
      break;
   }
/*   if(!(oamsPsscmCfgUnlockResp.cause == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.cause is not correct ");
      break;
   }
*/
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsAutoConfig = *((OamsPsscmNsAutoConfig *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.msgType == OAMS_PSSCM_NS_AUTO_CONFIG) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.apiId == OAM_NS_AUTO_CONFIG_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.resetFlag == ZERO) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.resetFlag is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.maxNsvc == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.maxNsvc is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[28] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[28] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_029

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_029)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer);

  I_U8 *tempBuffer;
  tempBuffer = (I_U8 *)malloc(sizeof(OamsPsscmNsUnprovRep) + sizeof(RepIpElemInfo));
  memcpy(tempBuffer,buffer, size);
  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
{
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }

   RepIpElemInfo * repIpElemInfoPtr;
   repIpElemInfoPtr = (((OamsPsscmNsUnprovRep *)tempBuffer)->repIpElemInfo);
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->ip4Addr == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->udpPort == 2) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->sigWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->dataWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.numIp is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[29] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[29] = 1;    /* 1 for pass*/

}
END_TEST



/**************************************************************************
 TC Name: TC_030

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_030)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[30] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[30] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_031

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_FAILURE, dbResult = CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_031)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovLep oamsPsscmNsUnprovLep;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_FAILURE;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovLep = *((OamsPsscmNsUnprovLep *)buffer);

  I_U8 *tempBuffer;
  tempBuffer = (I_U8 *)malloc(sizeof(OamsPsscmNsUnprovLep) + sizeof(I_U16));
  memcpy(tempBuffer,buffer, size);
  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
   flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_LEP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.apiId == OAM_NS_UNPROV_LOCAL_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.listType is not correct ");
      break;
   }

   I_U16 *ptr;
   ptr = (((OamsPsscmNsUnprovLep *)tempBuffer)->refId);
   if(!(*ptr == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.refId[0] is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[31] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[31] = 1;    /* 1 for pass*/

}
END_TEST


                                                         











/**************************************************************************
 TC Name: TC_032

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_FAILURE, dbResult != LIB_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_032)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_FAILURE;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.src.entity == ENT_OAMS_CFG) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[32] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[32] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_033

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_REP_CNF is received in WaitForNsProvRepCnf state. Preconfiguration : { result = BSS_FAILURE, dbResult != CLIB_SUCCESS, ongoingAction = LOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_033)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvRepCnf pssksNsPsscmProvRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmProvRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_REP_CNF;
   pssksNsPsscmProvRepCnf.sysHdr.subType = 0;
   pssksNsPsscmProvRepCnf.sysHdr.priority = 0;
   pssksNsPsscmProvRepCnf.bufLen = 0;
   pssksNsPsscmProvRepCnf.trId = 0;
   pssksNsPsscmProvRepCnf.apiId = 0;
   pssksNsPsscmProvRepCnf.result = BSS_FAILURE;
   pssksNsPsscmProvRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvRepCnf,sizeof(PssksNsPsscmProvRepCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.src.entity == ENT_OAMS_CFG) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[33] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[33] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_034

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_AUTO_CONFIG_CNF is received in WaitForAutoConfigCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_034)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAutoConfigCnf pssksNsPsscmAutoConfigCnf;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.msgType = PSSKS_NS_PSSCM_AUTO_CONFIG_CNF;
   pssksNsPsscmAutoConfigCnf.sysHdr.subType = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.priority = 0;
   pssksNsPsscmAutoConfigCnf.bufLen = 0;
   pssksNsPsscmAutoConfigCnf.trId = 0;
   pssksNsPsscmAutoConfigCnf.apiId = 0;
   pssksNsPsscmAutoConfigCnf.result = BSS_SUCCESS;
   pssksNsPsscmAutoConfigCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAutoConfigCnf,sizeof(PssksNsPsscmAutoConfigCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[34] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[34] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_035

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_AUTO_CONFIG_CNF is received in WaitForAutoConfigCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS, dbResult = CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_035)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAutoConfigCnf pssksNsPsscmAutoConfigCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.msgType = PSSKS_NS_PSSCM_AUTO_CONFIG_CNF;
   pssksNsPsscmAutoConfigCnf.sysHdr.subType = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.priority = 0;
   pssksNsPsscmAutoConfigCnf.bufLen = 0;
   pssksNsPsscmAutoConfigCnf.trId = 0;
   pssksNsPsscmAutoConfigCnf.apiId = 0;
   pssksNsPsscmAutoConfigCnf.result = BSS_SUCCESS;
   pssksNsPsscmAutoConfigCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAutoConfigCnf,sizeof(PssksNsPsscmAutoConfigCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[35] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[35] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_036

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_AUTO_CONFIG_CNF is received in WaitForAutoConfigCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_036)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAutoConfigCnf pssksNsPsscmAutoConfigCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.msgType = PSSKS_NS_PSSCM_AUTO_CONFIG_CNF;
   pssksNsPsscmAutoConfigCnf.sysHdr.subType = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.priority = 0;
   pssksNsPsscmAutoConfigCnf.bufLen = 0;
   pssksNsPsscmAutoConfigCnf.trId = 0;
   pssksNsPsscmAutoConfigCnf.apiId = 0;
   pssksNsPsscmAutoConfigCnf.result = BSS_SUCCESS;
   pssksNsPsscmAutoConfigCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAutoConfigCnf,sizeof(PssksNsPsscmAutoConfigCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[36] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[36] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_037

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_AUTO_CONFIG_CNF is received in WaitForAutoConfigCnf state. Preconfiguration : { result = BSS_FAILURE, ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_037)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAutoConfigCnf pssksNsPsscmAutoConfigCnf;

  /*Receive Message Struct */
   pssksNsPsscmAutoConfigCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.msgType = PSSKS_NS_PSSCM_AUTO_CONFIG_CNF;
   pssksNsPsscmAutoConfigCnf.sysHdr.subType = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.priority = 0;
   pssksNsPsscmAutoConfigCnf.bufLen = 0;
   pssksNsPsscmAutoConfigCnf.trId = 0;
   pssksNsPsscmAutoConfigCnf.apiId = 0;
   pssksNsPsscmAutoConfigCnf.result = BSS_FAILURE;
   pssksNsPsscmAutoConfigCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAutoConfigCnf,sizeof(PssksNsPsscmAutoConfigCnf));

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[37] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[37] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_038

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_AUTO_CONFIG_CNF is received in WaitForAutoConfigCnf state. Preconfiguration : { result = BSS_FAILURE, ongoingAction = LOCK_IN_PROGRESS, dbResult = CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_038)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAutoConfigCnf pssksNsPsscmAutoConfigCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.msgType = PSSKS_NS_PSSCM_AUTO_CONFIG_CNF;
   pssksNsPsscmAutoConfigCnf.sysHdr.subType = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.priority = 0;
   pssksNsPsscmAutoConfigCnf.bufLen = 0;
   pssksNsPsscmAutoConfigCnf.trId = 0;
   pssksNsPsscmAutoConfigCnf.apiId = 0;
   pssksNsPsscmAutoConfigCnf.result = BSS_FAILURE;
   pssksNsPsscmAutoConfigCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAutoConfigCnf,sizeof(PssksNsPsscmAutoConfigCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[38] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[38] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_039

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_AUTO_CONFIG_CNF is received in WaitForAutoConfigCnf state. Preconfiguration : { result = BSS_FAILURE, ongoingAction = LOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_039)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAutoConfigCnf pssksNsPsscmAutoConfigCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.src.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.msgType = PSSKS_NS_PSSCM_AUTO_CONFIG_CNF;
   pssksNsPsscmAutoConfigCnf.sysHdr.subType = 0;
   pssksNsPsscmAutoConfigCnf.sysHdr.priority = 0;
   pssksNsPsscmAutoConfigCnf.bufLen = 0;
   pssksNsPsscmAutoConfigCnf.trId = 0;
   pssksNsPsscmAutoConfigCnf.apiId = 0;
   pssksNsPsscmAutoConfigCnf.result = BSS_FAILURE;
   pssksNsPsscmAutoConfigCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAutoConfigCnf,sizeof(PssksNsPsscmAutoConfigCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[39] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[39] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_040

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in WaitForAutoConfigCnf state. Preconfiguration : { info3 = OAMS_OBJTYPE_GBINTERFACE }
**************************************************************************/
START_TEST (TC_040)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   OamsPsscmNsAutoConfig oamsPsscmNsAutoConfig;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = OAMS_OBJTYPE_GBINTERFACE;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsAutoConfig = *((OamsPsscmNsAutoConfig *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.msgType == OAMS_PSSCM_NS_AUTO_CONFIG) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.apiId == OAM_NS_AUTO_CONFIG_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.resetFlag == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.resetFlag is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.maxNsvc == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.maxNsvc is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[40] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[40] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_041

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in WaitForAutoConfigCnf state. Preconfiguration : { info3 != OAMS_OBJTYPE_GBINTERFACE }
**************************************************************************/
START_TEST (TC_041)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = 0;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = 0;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = 0;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[41] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[41] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_042

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForAutoConfigCnf state.
**************************************************************************/
START_TEST (TC_042)
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
      test_result[42] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[42] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_043

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForTestEnableCnf state.
**************************************************************************/
START_TEST (TC_043)
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
      test_result[43] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[43] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_044

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_TEST_ENABLE_CNF is received in WaitForTestEnableCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_044)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmTestEnableCnf pssksNsPsscmTestEnableCnf;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmTestEnableCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.msgType = PSSKS_NS_PSSCM_TEST_ENABLE_CNF;
   pssksNsPsscmTestEnableCnf.sysHdr.subType = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.priority = 0;
   pssksNsPsscmTestEnableCnf.bufLen = 0;
   pssksNsPsscmTestEnableCnf.trId = 0;
   pssksNsPsscmTestEnableCnf.apiId = 0;
   pssksNsPsscmTestEnableCnf.result = BSS_SUCCESS;
   pssksNsPsscmTestEnableCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmTestEnableCnf,sizeof(PssksNsPsscmTestEnableCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[44] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[44] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_045

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_TEST_ENABLE_CNF is received in WaitForTestEnableCnf state. Preconfiguration : {result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS}
**************************************************************************/
START_TEST (TC_045)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmTestEnableCnf pssksNsPsscmTestEnableCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmTestEnableCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.msgType = PSSKS_NS_PSSCM_TEST_ENABLE_CNF;
   pssksNsPsscmTestEnableCnf.sysHdr.priority = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.subType = 0;
   pssksNsPsscmTestEnableCnf.bufLen = 0;
   pssksNsPsscmTestEnableCnf.trId = 0;
   pssksNsPsscmTestEnableCnf.apiId = 0;
   pssksNsPsscmTestEnableCnf.result = BSS_SUCCESS;
   pssksNsPsscmTestEnableCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmTestEnableCnf,sizeof(PssksNsPsscmTestEnableCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[45] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[45] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_046

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_TEST_ENABLE_CNF is received in WaitForTestEnableCnf state. Preconfiguration : { result = BSS_SUCCESS, ongoingAction = LOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_046)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmTestEnableCnf pssksNsPsscmTestEnableCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmTestEnableCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.msgType = PSSKS_NS_PSSCM_TEST_ENABLE_CNF;
   pssksNsPsscmTestEnableCnf.sysHdr.priority = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.subType = 0;
   pssksNsPsscmTestEnableCnf.trId = 0;
   pssksNsPsscmTestEnableCnf.apiId = 0;
   pssksNsPsscmTestEnableCnf.result = BSS_SUCCESS;
   pssksNsPsscmTestEnableCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmTestEnableCnf,sizeof(PssksNsPsscmTestEnableCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[46] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[46] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_047

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_TEST_ENABLE_CNF is received in WaitForTestEnableCnf state. Preconfiguration : { result = BSS_FAILURE, ongoingAction = LOCK_IN_PROGRESS, dbResult = CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_047)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmTestEnableCnf pssksNsPsscmTestEnableCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
   
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmTestEnableCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.msgType = PSSKS_NS_PSSCM_TEST_ENABLE_CNF;
   pssksNsPsscmTestEnableCnf.sysHdr.priority = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.subType = 0;
   pssksNsPsscmTestEnableCnf.bufLen = 0;
   pssksNsPsscmTestEnableCnf.trId = 0;
   pssksNsPsscmTestEnableCnf.apiId = 0;
   pssksNsPsscmTestEnableCnf.result = BSS_FAILURE;
   pssksNsPsscmTestEnableCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmTestEnableCnf,sizeof(PssksNsPsscmTestEnableCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[47] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[47] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_048

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_TEST_ENABLE_CNF is received in WaitForTestEnableCnf state. Preconfiguration : { result = BSS_FAILURE, ongoingAction = LOCK_IN_PROGRESS, dbResult != CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_048)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmTestEnableCnf pssksNsPsscmTestEnableCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmTestEnableCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.msgType = PSSKS_NS_PSSCM_TEST_ENABLE_CNF;
   pssksNsPsscmTestEnableCnf.sysHdr.priority = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.subType = 0;
   pssksNsPsscmTestEnableCnf.apiId = 0;
   pssksNsPsscmTestEnableCnf.result = BSS_FAILURE;
   pssksNsPsscmTestEnableCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmTestEnableCnf,sizeof(PssksNsPsscmTestEnableCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[48] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[48] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_049

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_TEST_ENABLE_CNF is received in WaitForTestEnableCnf state. Preconfiguration : { result = BSS_FAILURE, ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_049)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmTestEnableCnf pssksNsPsscmTestEnableCnf;

  /*Receive Message Struct */
   pssksNsPsscmTestEnableCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmTestEnableCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.src.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.msgType = PSSKS_NS_PSSCM_TEST_ENABLE_CNF;
   pssksNsPsscmTestEnableCnf.sysHdr.priority = 0;
   pssksNsPsscmTestEnableCnf.sysHdr.subType = 0;
   pssksNsPsscmTestEnableCnf.bufLen = 0;
   pssksNsPsscmTestEnableCnf.trId = 0;
   pssksNsPsscmTestEnableCnf.apiId = 0;
   pssksNsPsscmTestEnableCnf.result = BSS_FAILURE;
   pssksNsPsscmTestEnableCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmTestEnableCnf,sizeof(PssksNsPsscmTestEnableCnf));

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[49] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[49] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_050

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in WaitForTestEnableCnf state. Preconfiguration : { info3 = OAMS_OBJTYPE_GBINTERFACE }
**************************************************************************/
START_TEST (TC_050)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   OamsPsscmNsTestEnable oamsPsscmNsTestEnable;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = OAMS_OBJTYPE_GBINTERFACE;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmReason == OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmReason is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsTestEnable = *((OamsPsscmNsTestEnable *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsTestEnable.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.msgType == OAMS_PSSCM_NS_TEST_ENABLE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.apiId == OAM_NS_TEST_ENABLE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.apiId is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[50] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[50] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_051

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in WaitForTestEnableCnf state. Preconfiguration : { info3 != OAMS_OBJTYPE_GBINTERFACE }
**************************************************************************/
START_TEST (TC_051)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = 0;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmReason == OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmReason is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[51] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[51] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_052

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForUnprovRepCnf state.
**************************************************************************/
START_TEST (TC_052)
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
      test_result[52] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[52] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_053

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_REP_CNF is received in WaitForUnprovRepCnf state. Preconfiguration : { dbResult = CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_053)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovRepCnf pssksNsPsscmUnprovRepCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovLep oamsPsscmNsUnprovLep;


   pssksNsPsscmUnprovRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.entity = ENT_OAMS_CFG;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_REP_CNF;
   pssksNsPsscmUnprovRepCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovRepCnf.bufLen = 0;
   pssksNsPsscmUnprovRepCnf.trId = 0;
   pssksNsPsscmUnprovRepCnf.apiId = 0;
   pssksNsPsscmUnprovRepCnf.result = BSS_SUCCESS;
   pssksNsPsscmUnprovRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovRepCnf,sizeof(PssksNsPsscmUnprovRepCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovLep = *((OamsPsscmNsUnprovLep *)buffer); 

  I_U8 *tempBuffer;
  tempBuffer = (I_U8 *)malloc(sizeof(OamsPsscmNsUnprovLep) + sizeof(I_U16));
  memcpy(tempBuffer,buffer, size);
  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_LEP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.apiId == OAM_NS_UNPROV_LOCAL_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovLep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.listType is not correct ");
      break;
   }

   I_U16 *ptr;
   ptr = (((OamsPsscmNsUnprovLep *)tempBuffer)->refId);
   if(!(*ptr == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovLep.refId[0] is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[53] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[53] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_054

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_REP_CNF is received in WaitForUnprovRepCnf state. Preconfiguration : { dbResult != CLIB_SUCCESS, ongoingAction = LOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_054)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovRepCnf pssksNsPsscmUnprovRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.entity = ENT_OAMS_CFG;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_REP_CNF;
   pssksNsPsscmUnprovRepCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovRepCnf.bufLen = 0;
   pssksNsPsscmUnprovRepCnf.trId = 0;
   pssksNsPsscmUnprovRepCnf.apiId = 0;
   pssksNsPsscmUnprovRepCnf.result = BSS_SUCCESS;
   pssksNsPsscmUnprovRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovRepCnf,sizeof(PssksNsPsscmUnprovRepCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[54] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[54] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_055

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_REP_CNF is received in WaitForUnprovRepCnf state. Preconfiguration : { dbResult != CLIB_SUCCESS, ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_055)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovRepCnf pssksNsPsscmUnprovRepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.entity = ENT_OAMS_CFG;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_REP_CNF;
   pssksNsPsscmUnprovRepCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovRepCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovRepCnf.bufLen = 0;
   pssksNsPsscmUnprovRepCnf.trId = 0;
   pssksNsPsscmUnprovRepCnf.apiId = 0;
   pssksNsPsscmUnprovRepCnf.result = 0;
   pssksNsPsscmUnprovRepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovRepCnf,sizeof(PssksNsPsscmUnprovRepCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
      test_result[55] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[55] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_056

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForBssgpUnprovSigBvcCnf state. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_056)
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
      test_result[56] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[56] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_057

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_UNPROV_SIG_BVC_CNF is received in WaitForBssgpUnprovSigBvcCnf state. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_057)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmUnprovSigBvcCnf pssksBssgpPsscmUnprovSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovSigBvc oamsPsscmNsUnprovSigBvc;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.src.entity = ENT_OAMS_CFG;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_UNPROV_SIG_BVC_CNF;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.bufLen = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.trId = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.apiId = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.bvci = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.result = 0;
   pssksBssgpPsscmUnprovSigBvcCnf.cause = 0;
/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmUnprovSigBvcCnf,sizeof(PssksBssgpPsscmUnprovSigBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovSigBvc = *((OamsPsscmNsUnprovSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.apiId == OAM_NS_UNPROV_BVCI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovSigBvc.bvci is not correct ");
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
 TC Name: TC_058

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForNsUnprovSigBvcCnf state. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_058)
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
      test_result[58] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[58] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_059

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_SIG_BVC_CNF is received in WaitForNsUnprovSigBvcCnf state. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_059)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovSigBvcCnf pssksNsPsscmUnprovSigBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovNsei oamsPsscmNsUnprovNsei;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_SIG_BVC_CNF;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovSigBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovSigBvcCnf.bufLen = 0;
   pssksNsPsscmUnprovSigBvcCnf.trId = 0;
   pssksNsPsscmUnprovSigBvcCnf.apiId = 0;
   pssksNsPsscmUnprovSigBvcCnf.result = 0;
   pssksNsPsscmUnprovSigBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovSigBvcCnf,sizeof(PssksNsPsscmUnprovSigBvcCnf));

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
   if(!(oamsPsscmNsUnprovNsei.sysHdr.src.clsId == ONE) )
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
   if(!(oamsPsscmNsUnprovNsei.apiId == OAM_NS_UNPROV_NSEI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovNsei.apiId is not correct ");
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
      test_result[59] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[59] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_060

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForUnprovNseiCnf state. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_060)
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
      test_result[60] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[60] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_061

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_NSEI_CNF is received in WaitForUnprovNseiCnf state. Preconfiguration : { ongoingAction = LOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_061)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovNseiCnf pssksNsPsscmUnprovNseiCnf;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_NSEI_CNF;
   pssksNsPsscmUnprovNseiCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovNseiCnf.bufLen = 0;
   pssksNsPsscmUnprovNseiCnf.trId = 0;
   pssksNsPsscmUnprovNseiCnf.apiId = 0;
   pssksNsPsscmUnprovNseiCnf.result = 0;
   pssksNsPsscmUnprovNseiCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovNseiCnf,sizeof(PssksNsPsscmUnprovNseiCnf));

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
   if(!(oamsPsscmCfgLockResp.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.dest.clsId is not correct ");
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
      test_result[61] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[61] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_062

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_NSEI_CNF is received in WaitForUnprovNseiCnf state. Preconfiguration : { ongoingAction = UNLOCK_IN_PROGRESS }
**************************************************************************/
START_TEST (TC_062)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovNseiCnf pssksNsPsscmUnprovNseiCnf;

  /*Receive Message Struct */
   OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockResp;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_NSEI_CNF;
   pssksNsPsscmUnprovNseiCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovNseiCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovNseiCnf.bufLen = 0;
   pssksNsPsscmUnprovNseiCnf.trId = 0;
   pssksNsPsscmUnprovNseiCnf.apiId = 0;
   pssksNsPsscmUnprovNseiCnf.result = 0;
   pssksNsPsscmUnprovNseiCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovNseiCnf,sizeof(PssksNsPsscmUnprovNseiCnf));

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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.dest.clsId is not correct ");
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
      test_result[62] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[62] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_063

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in PsscmActive. Preconfiguration : { transportType = IP_STATIC  }
**************************************************************************/
START_TEST (TC_063)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmLockReq oamsCfgPsscmLockReq;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
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

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[63] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[63] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_064

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in PsscmActive. Preconfiguration : { transportType = IP_DYNAMIC  }
**************************************************************************/
START_TEST (TC_064)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmLockReq oamsCfgPsscmLockReq;

  /*Receive Message Struct */
   OamsPsscmNsUnprovRep oamsPsscmNsUnprovRep;
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

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovRep = *((OamsPsscmNsUnprovRep *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_REP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.apiId == OAM_NS_UNPROV_REMOTE_END_POINT) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovRep.listType == SNS_IP4_ADDRESS_TYPE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovRep.listType is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[64] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[64] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_065

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in PsscmActive. Preconfiguration : { transportType = FR  }
**************************************************************************/
START_TEST (TC_065)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmLockReq oamsCfgPsscmLockReq;

  /*Receive Message Struct */
   OamsPsscmBssgpUnprovSigBvc oamsPsscmBssgpUnprovSigBvc;
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

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmBssgpUnprovSigBvc = *((OamsPsscmBssgpUnprovSigBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_BSSGP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.msgType == OAMS_PSSCM_BSSGP_UNPROV_SIG_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.apiId == BSSGP_UNPROVISION_BVC_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovSigBvc.bvci == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[65] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[65] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_066

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in PsscmActive. Preconfiguration : { transportType = IP_STATIC, dbResult != CLIB_SUCCESS  }
**************************************************************************/
START_TEST (TC_066)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgPsscmLockReq oamsCfgPsscmLockReq;

  /*Receive Message Struct */
   OamsPsscmCfgLockResp oamsPsscmCfgLockResp;
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
   if(!(oamsPsscmCfgLockResp.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsPsscmCfgLockResp.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.sysHdr.msgType == OAMS_PSSCM_CFG_LOCK_RESP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgLockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[66] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[66] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_067

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in PsscmActive. Preconfiguration : { info3 = GBINTERFACE, transportType = IP_DYNAMIC, alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY }
**************************************************************************/
START_TEST (TC_067)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   OamsPsscmNsAutoConfig oamsPsscmNsAutoConfig;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = OAMS_OBJTYPE_GBINTERFACE;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsAutoConfig = *((OamsPsscmNsAutoConfig *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.sysHdr.msgType == OAMS_PSSCM_NS_AUTO_CONFIG) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.apiId == OAM_NS_AUTO_CONFIG_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.resetFlag == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.resetFlag is not correct ");
      break;
   }
   if(!(oamsPsscmNsAutoConfig.maxNsvc == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsAutoConfig.maxNsvc is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[67] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[67] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_068

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in PsscmActive. Preconfiguration : { info3 = GBINTERFACE, transportType = IP_STATIC, alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY }
**************************************************************************/
START_TEST (TC_068)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   OamsPsscmNsTestEnable oamsPsscmNsTestEnable;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = OAMS_OBJTYPE_GBINTERFACE;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmReason == OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmReason is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsTestEnable = *((OamsPsscmNsTestEnable *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsTestEnable.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.sysHdr.msgType == OAMS_PSSCM_NS_TEST_ENABLE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsTestEnable.apiId == OAM_NS_TEST_ENABLE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsTestEnable.apiId is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[68] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[68] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_069

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in PsscmActive. Preconfiguration : { info3 = GBINTERFACE, transportType = IP_DYNAMIC, alarmReason != OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY }
**************************************************************************/
START_TEST (TC_069)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = 123;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = OAMS_OBJTYPE_GBINTERFACE;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmReason == 123) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmReason is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[69] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[69] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_070

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_ALARM_IND is received in PsscmActive. Preconfiguration : { info3 = GBINTERFACE, transportType = IP_STATIC, alarmReason != OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY }
**************************************************************************/
START_TEST (TC_070)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmAlarmInd pssksNsPsscmAlarmInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   pssksNsPsscmAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmAlarmInd.sysHdr.src.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.src.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmAlarmInd.sysHdr.dest.clsId = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsPsscmAlarmInd.sysHdr.dest.inst = 0;
   pssksNsPsscmAlarmInd.sysHdr.msgType = PSSKS_NS_PSSCM_ALARM_IND;
   pssksNsPsscmAlarmInd.sysHdr.subType = 0;
   pssksNsPsscmAlarmInd.sysHdr.priority = 0;
   pssksNsPsscmAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsPsscmAlarmInd.alarmSeqNo = 0;
   pssksNsPsscmAlarmInd.alarmTime = 0;
   pssksNsPsscmAlarmInd.alarmLevel = 0;
   pssksNsPsscmAlarmInd.alarmReason = 123;
   pssksNsPsscmAlarmInd.key1 = 0;
   pssksNsPsscmAlarmInd.key2 = 0;
   pssksNsPsscmAlarmInd.key3 = 0;
   pssksNsPsscmAlarmInd.key4 = 0;
   pssksNsPsscmAlarmInd.info1 = 0;
   pssksNsPsscmAlarmInd.info2 = 0;
   pssksNsPsscmAlarmInd.info3 = OAMS_OBJTYPE_GBINTERFACE;
   pssksNsPsscmAlarmInd.infoStringLen = 0;
   pssksNsPsscmAlarmInd.infoString[150] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmAlarmInd,sizeof(PssksNsPsscmAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmReason == 123) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmReason is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[70] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[70] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_071

 TC Description: To see the transition when the message OAMS_PSCH_PSSCM_UNPROV_PTP_BVC is received in PsscmActive. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_071)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc;

  /*Receive Message Struct */
   OamsPsscmBssgpUnprovPtpBvc oamsPsscmBssgpUnprovPtpBvc;
   oamsPschPsscmUnprovPtpBvc.sysHdr.src.prcr = PRCR_PP;
   oamsPschPsscmUnprovPtpBvc.sysHdr.src.entity = ENT_OAMS_PSCH;
   oamsPschPsscmUnprovPtpBvc.sysHdr.src.clsId = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.src.rfu = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.src.inst = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.dest.prcr = PRCR_PP;
   oamsPschPsscmUnprovPtpBvc.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsPschPsscmUnprovPtpBvc.sysHdr.dest.clsId = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.dest.rfu = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.dest.inst = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.msgType = OAMS_PSCH_PSSCM_UNPROV_PTP_BVC;
   oamsPschPsscmUnprovPtpBvc.sysHdr.subType = 0;
   oamsPschPsscmUnprovPtpBvc.sysHdr.priority = 0;
   oamsPschPsscmUnprovPtpBvc.bvci = 1;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsPschPsscmUnprovPtpBvc,sizeof(OamsPschPsscmUnprovPtpBvc));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmBssgpUnprovPtpBvc = *((OamsPsscmBssgpUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_BSSGP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.sysHdr.msgType == OAMS_PSSCM_BSSGP_UNPROV_PTP_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.apiId == BSSGP_UNPROVISION_BVC_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpUnprovPtpBvc.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovPtpBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[71] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[71] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_072

 TC Description: To see the transition when the message OAMS_PSCH_PSSCM_PROV_PTP_BVC is received in PsscmActive. Preconfiguration : {  }
**************************************************************************/
START_TEST (TC_072)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsPschPsscmProvPtpBvc oamsPschPsscmProvPtpBvc;

  /*Receive Message Struct */
   OamsPsscmNsProvPtpBvc oamsPsscmNsProvPtpBvc;
   oamsPschPsscmProvPtpBvc.sysHdr.src.prcr = PRCR_PP;
   oamsPschPsscmProvPtpBvc.sysHdr.src.entity = ENT_OAMS_PSCH;
   oamsPschPsscmProvPtpBvc.sysHdr.src.clsId = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.src.rfu = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.src.inst = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.dest.prcr = PRCR_PP;
   oamsPschPsscmProvPtpBvc.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsPschPsscmProvPtpBvc.sysHdr.dest.clsId = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.dest.rfu = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.dest.inst = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.msgType = OAMS_PSCH_PSSCM_PROV_PTP_BVC;
   oamsPschPsscmProvPtpBvc.sysHdr.subType = 0;
   oamsPschPsscmProvPtpBvc.sysHdr.priority = 0;
   oamsPschPsscmProvPtpBvc.bvci = 1;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsPschPsscmProvPtpBvc,sizeof(OamsPschPsscmProvPtpBvc));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsProvPtpBvc = *((OamsPsscmNsProvPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.sysHdr.msgType == OAMS_PSSCM_NS_PROV_PTP_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.apiId == OAM_NS_PROV_BVCI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsProvPtpBvc.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvPtpBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[72] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[72] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_073

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { result = BSS_SUCCESS }
**************************************************************************/
START_TEST (TC_073)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvPtpBvcCnf pssksNsPsscmProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmBssgpProvPtpBvc oamsPsscmBssgpProvPtpBvc;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmProvPtpBvcCnf.bufLen = 0;
   pssksNsPsscmProvPtpBvcCnf.trId = 0;
   pssksNsPsscmProvPtpBvcCnf.apiId = 0;
   pssksNsPsscmProvPtpBvcCnf.bvci = 1;
   pssksNsPsscmProvPtpBvcCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvPtpBvcCnf,sizeof(PssksNsPsscmProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmBssgpProvPtpBvc = *((OamsPsscmBssgpProvPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.sysHdr.msgType == OAMS_PSSCM_NS_PROV_PTP_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.apiId == BSSGP_PROVISION_BVC_REQUEST) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmBssgpProvPtpBvc.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpProvPtpBvc.bvci is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[73] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[73] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_074

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { result = BSS_SUCCESS, dbResult != CLIB_SUCCESS }
**************************************************************************/
START_TEST (TC_074)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvPtpBvcCnf pssksNsPsscmProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovPtpBvc oamsPsscmNsUnprovPtpBvc;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmProvPtpBvcCnf.bufLen = 0;
   pssksNsPsscmProvPtpBvcCnf.trId = 0;
   pssksNsPsscmProvPtpBvcCnf.apiId = 0;
   pssksNsPsscmProvPtpBvcCnf.bvci = 1;
   pssksNsPsscmProvPtpBvcCnf.result = BSS_SUCCESS;
   pssksNsPsscmProvPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvPtpBvcCnf,sizeof(PssksNsPsscmProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovPtpBvc = *((OamsPsscmNsUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_PTP_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.apiId == OAM_NS_UNPROV_BVCI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.unprovReason == CAUSE_PTP_BVC_PROVISION_FAILED) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.unprovReason is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[74] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[74] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_075

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { result = BSS_FAILURE }
**************************************************************************/
START_TEST (TC_075)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmProvPtpBvcCnf pssksNsPsscmProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmPschProvPtpBvcCnf oamsPsscmPschProvPtpBvcCnf;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmProvPtpBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmProvPtpBvcCnf.bufLen = 0;
   pssksNsPsscmProvPtpBvcCnf.trId = 0;
   pssksNsPsscmProvPtpBvcCnf.apiId = 0;
   pssksNsPsscmProvPtpBvcCnf.bvci = 1;
   pssksNsPsscmProvPtpBvcCnf.result = BSS_FAILURE;
   pssksNsPsscmProvPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmProvPtpBvcCnf,sizeof(PssksNsPsscmProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmPschProvPtpBvcCnf = *((OamsPsscmPschProvPtpBvcCnf *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType == OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.result == BSS_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[75] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[75] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_076

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { result = BSS_SUCCESS }
**************************************************************************/
START_TEST (TC_076)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvPtpBvcCnf pssksBssgpPsscmProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmPschProvPtpBvcCnf oamsPsscmPschProvPtpBvcCnf;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_PTP_BVC_CNF;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvPtpBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvPtpBvcCnf.trId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.apiId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.bvci = 1;
   pssksBssgpPsscmProvPtpBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmProvPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvPtpBvcCnf,sizeof(PssksBssgpPsscmProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmPschProvPtpBvcCnf = *((OamsPsscmPschProvPtpBvcCnf *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType == OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.result == BSS_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[76] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[76] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_077

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_PROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { result = BSS_FAILURE }
**************************************************************************/
START_TEST (TC_077)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmProvPtpBvcCnf pssksBssgpPsscmProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovPtpBvc oamsPsscmNsUnprovPtpBvc;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_PROV_PTP_BVC_CNF;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmProvPtpBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmProvPtpBvcCnf.bufLen = 0;
   pssksBssgpPsscmProvPtpBvcCnf.trId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.apiId = 0;
   pssksBssgpPsscmProvPtpBvcCnf.bvci = 1;
   pssksBssgpPsscmProvPtpBvcCnf.result = BSS_FAILURE;
   pssksBssgpPsscmProvPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmProvPtpBvcCnf,sizeof(PssksBssgpPsscmProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovPtpBvc = *((OamsPsscmNsUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_PTP_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.apiId == OAM_NS_UNPROV_BVCI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.unprovReason == CAUSE_PTP_BVC_PROVISION_FAILED) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.unprovReason is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[77] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[77] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_078

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_UNPROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { result = BSS_SUCCESS }
**************************************************************************/
START_TEST (TC_078)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksBssgpPsscmUnprovPtpBvcCnf pssksBssgpPsscmUnprovPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmNsUnprovPtpBvc oamsPsscmNsUnprovPtpBvc;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.src.inst = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.msgType = PSSKS_BSSGP_PSSCM_UNPROV_PTP_BVC_CNF;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.subType = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.sysHdr.priority = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.bufLen = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.trId = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.apiId = 0;
   pssksBssgpPsscmUnprovPtpBvcCnf.bvci = 1;
   pssksBssgpPsscmUnprovPtpBvcCnf.result = BSS_SUCCESS;
   pssksBssgpPsscmUnprovPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksBssgpPsscmUnprovPtpBvcCnf,sizeof(PssksBssgpPsscmUnprovPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmNsUnprovPtpBvc = *((OamsPsscmNsUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.src.clsId == ONE) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.dest.clsId == GSAL_ACT_CLID_NS) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.sysHdr.msgType == OAMS_PSSCM_NS_UNPROV_PTP_BVC) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.apiId == OAM_NS_UNPROV_BVCI) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.apiId is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.nsei == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.nsei is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmNsUnprovPtpBvc.unprovReason == NORMAL_SCENARIO_UNPROVISIONING) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnprovPtpBvc.unprovReason is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[78] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[78] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_079

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { unprovReason = NORMAL_SCENARIO_UNPROVISIONING }
**************************************************************************/
START_TEST (TC_079)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovPtpBvcCnf pssksNsPsscmUnprovPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmPschUnprovPtpBvcCnf oamsPsscmPschUnprovPtpBvcCnf;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_PTP_BVC_CNF;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovPtpBvcCnf.bufLen = 0;
   pssksNsPsscmUnprovPtpBvcCnf.trId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.apiId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.bvci = 1;
   pssksNsPsscmUnprovPtpBvcCnf.unprovReason = NORMAL_SCENARIO_UNPROVISIONING;
   pssksNsPsscmUnprovPtpBvcCnf.result = BSS_SUCCESS;
   pssksNsPsscmUnprovPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovPtpBvcCnf,sizeof(PssksNsPsscmUnprovPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmPschUnprovPtpBvcCnf = *((OamsPsscmPschUnprovPtpBvcCnf *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschUnprovPtpBvcCnf.sysHdr.msgType == OAMS_PSSCM_PSCH_UNPROV_PTP_BVC_CNF) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmPschUnprovPtpBvcCnf.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmPschUnprovPtpBvcCnf.result == BSS_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsPsscmPschUnprovPtpBvcCnf.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[79] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[79] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_080

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_PTP_BVC_CNF is received in PsscmActive. Preconfiguration : { unprovReason = CAUSE_PTP_BVC_PROVISION_FAILED }
**************************************************************************/
START_TEST (TC_080)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovPtpBvcCnf pssksNsPsscmUnprovPtpBvcCnf;

  /*Receive Message Struct */
   OamsPsscmPschProvPtpBvcCnf oamsPsscmPschProvPtpBvcCnf;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_PTP_BVC_CNF;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovPtpBvcCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovPtpBvcCnf.bufLen = 0;
   pssksNsPsscmUnprovPtpBvcCnf.trId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.apiId = 0;
   pssksNsPsscmUnprovPtpBvcCnf.bvci = 1;
   pssksNsPsscmUnprovPtpBvcCnf.unprovReason = CAUSE_PTP_BVC_PROVISION_FAILED;
   pssksNsPsscmUnprovPtpBvcCnf.result = BSS_SUCCESS;
   pssksNsPsscmUnprovPtpBvcCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovPtpBvcCnf,sizeof(PssksNsPsscmUnprovPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmPschProvPtpBvcCnf = *((OamsPsscmPschProvPtpBvcCnf *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType == OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.bvci == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.bvci is not correct ");
      break;
   }
   if(!(oamsPsscmPschProvPtpBvcCnf.result == BSS_FAILURE) )
   {
      flag = 0;
      fail("value of oamsPsscmPschProvPtpBvcCnf.result is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[80] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[80] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_081

 TC Description: To see the transition when the message OAMS_NSVCH_PSSCM_NSVC_DISABLED_IND is received in PsscmActive. Preconfiguration : { numNsvcEnabled is zero }
**************************************************************************/
START_TEST (TC_081)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsNsvchPsscmNsvcDisabledInd oamsNsvchPsscmNsvcDisabledInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.clsId = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.rfu = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.inst = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.clsId = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.rfu = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.inst = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.msgType = OAMS_NSVCH_PSSCM_NSVC_DISABLED_IND;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.subType = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.priority = 0;
   oamsNsvchPsscmNsvcDisabledInd.nsei = 1;
   oamsNsvchPsscmNsvcDisabledInd.nsvci = 1;
   oamsNsvchPsscmNsvcDisabledInd.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsNsvchPsscmNsvcDisabledInd,sizeof(OamsNsvchPsscmNsvcDisabledInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == ALARM_LAST_NSVC_DISABLED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_MAJR) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[81] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[81] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_082

 TC Description: To see the transition when the message OAMS_NSVCH_PSSCM_NSVC_DISABLED_IND is received in PsscmActive. Preconfiguration : { numNsvcEnabled is one (greater than zero) }
**************************************************************************/
START_TEST (TC_082)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsNsvchPsscmNsvcDisabledInd oamsNsvchPsscmNsvcDisabledInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.clsId = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.rfu = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.src.inst = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.clsId = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.rfu = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.dest.inst = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.msgType = OAMS_NSVCH_PSSCM_NSVC_DISABLED_IND;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.subType = 0;
   oamsNsvchPsscmNsvcDisabledInd.sysHdr.priority = 0;
   oamsNsvchPsscmNsvcDisabledInd.nsei = 1;
   oamsNsvchPsscmNsvcDisabledInd.nsvci = 1;
   oamsNsvchPsscmNsvcDisabledInd.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsNsvchPsscmNsvcDisabledInd,sizeof(OamsNsvchPsscmNsvcDisabledInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == ALARM_NSVC_DISABLED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_MAJR) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_NSVC) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[82] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[82] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_083

 TC Description: To see the transition when the message OAMS_NSVCH_PSSCM_NSVC_ENABLED_IND is received in PsscmActive. Preconfiguration : { numNsvcEnabled = ONE  }
**************************************************************************/
START_TEST (TC_083)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsNsvchPsscmNsvcEnabledInd oamsNsvchPsscmNsvcEnabledInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.clsId = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.rfu = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.inst = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.clsId = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.rfu = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.inst = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.msgType = OAMS_NSVCH_PSSCM_NSVC_ENABLED_IND;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.subType = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.priority = 0;
   oamsNsvchPsscmNsvcEnabledInd.nsei = 1;
   oamsNsvchPsscmNsvcEnabledInd.nsvci = 1;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsNsvchPsscmNsvcEnabledInd,sizeof(OamsNsvchPsscmNsvcEnabledInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FIRST_NSVC_ENABLED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[83] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[83] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_084

 TC Description: To see the transition when the message OAMS_NSVCH_PSSCM_NSVC_DISABLED_IND is received in PsscmActive. Preconfiguration : { numNsvcEnabled = TWO (ie greater than ONE) }
**************************************************************************/
START_TEST (TC_084)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsNsvchPsscmNsvcEnabledInd oamsNsvchPsscmNsvcEnabledInd;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.clsId = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.rfu = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.src.inst = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.prcr = PRCR_PP;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.clsId = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.rfu = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.dest.inst = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.msgType = OAMS_NSVCH_PSSCM_NSVC_ENABLED_IND;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.subType = 0;
   oamsNsvchPsscmNsvcEnabledInd.sysHdr.priority = 0;
   oamsNsvchPsscmNsvcEnabledInd.nsei = 1;
   oamsNsvchPsscmNsvcEnabledInd.nsvci = 1;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsNsvchPsscmNsvcEnabledInd,sizeof(OamsNsvchPsscmNsvcEnabledInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == ALARM_NSVC_ENABLED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_NSVC) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[84] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[84] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_085

 TC Description: To see the transition when the message PSSKS_BSSGP_PSSCM_ALARM_IND is received in PsscmActive. 
**************************************************************************/
START_TEST (TC_085)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
 //  PssksBssgpPsscmAlarmInd pssksBssgpPsscmAlarmInd;
    OamAfhAlarmInd oamAfhAlarmInd;
  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   oamAfhAlarmInd.sysHdr.src.prcr = PRCR_PP;
   oamAfhAlarmInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   oamAfhAlarmInd.sysHdr.src.clsId = 0;
   oamAfhAlarmInd.sysHdr.src.rfu = 0;
   oamAfhAlarmInd.sysHdr.src.inst = 0;
   oamAfhAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   oamAfhAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamAfhAlarmInd.sysHdr.dest.clsId = 0;
   oamAfhAlarmInd.sysHdr.dest.rfu = 0;
   oamAfhAlarmInd.sysHdr.dest.inst = 0;
   oamAfhAlarmInd.sysHdr.msgType = PSSKS_BSSGP_PSSCM_ALARM_IND;
   oamAfhAlarmInd.sysHdr.subType = 0;
   oamAfhAlarmInd.sysHdr.priority = 0;
   oamAfhAlarmInd.sysAlarm.sysalarmId = 0;
   oamAfhAlarmInd.sysAlarm.alarmSeqNo = 0;
   oamAfhAlarmInd.sysAlarm.alarmTime = 0;
   oamAfhAlarmInd.sysAlarm.alarmLevel = 0;
   oamAfhAlarmInd.sysAlarm.alarmReason = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY;
   oamAfhAlarmInd.sysAlarm.key1 = 0;
   oamAfhAlarmInd.sysAlarm.key2 = 0;
   oamAfhAlarmInd.sysAlarm.key3 = 0;
   oamAfhAlarmInd.sysAlarm.key4 = 0;
   oamAfhAlarmInd.sysAlarm.info1 = 0;
   oamAfhAlarmInd.sysAlarm.info2 = 0;
  oamAfhAlarmInd.sysAlarm.info3 = OAMS_OBJTYPE_GBINTERFACE;
  oamAfhAlarmInd.sysAlarm.infoStrLen = 0;
  oamAfhAlarmInd.sysAlarm.infoString[150] = 0;

/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamAfhAlarmInd,sizeof(OamAfhAlarmInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
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
 TC Name: TC_086

 TC Description: To see the transition when the message OAMS_CFG_PSSCM_LOCK_REQ is received in WaitForUnprovLepCnf. 
**************************************************************************/
START_TEST (TC_086)
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
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_087

 TC Description: To see the transition when the message PSSKS_NS_PSSCM_UNPROV_LEP_CNF is received in WaitForUnprovLepCnf. 
**************************************************************************/
START_TEST (TC_087)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsPsscmUnprovLepCnf pssksNsPsscmUnprovLepCnf;

  /*Receive Message Struct */
   OamsPsscmCfgAlarmInd oamsPsscmCfgAlarmInd;
   OamsPsscmBssgpUnprovSigBvc oamsPsscmBssgpUnprovSigBvc;
   pssksNsPsscmUnprovLepCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsPsscmUnprovLepCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsPsscmUnprovLepCnf.sysHdr.src.clsId = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.src.rfu = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.src.inst = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsPsscmUnprovLepCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsPsscmUnprovLepCnf.sysHdr.dest.clsId = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.dest.rfu = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.dest.inst = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.msgType = PSSKS_NS_PSSCM_UNPROV_LEP_CNF;
   pssksNsPsscmUnprovLepCnf.sysHdr.subType = 0;
   pssksNsPsscmUnprovLepCnf.sysHdr.priority = 0;
   pssksNsPsscmUnprovLepCnf.bufLen = 0;
   pssksNsPsscmUnprovLepCnf.trId = 0;
   pssksNsPsscmUnprovLepCnf.apiId = 0;
   pssksNsPsscmUnprovLepCnf.result = 0;
   pssksNsPsscmUnprovLepCnf.cause = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsPsscmUnprovLepCnf,sizeof(PssksNsPsscmUnprovLepCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmBssgpUnprovSigBvc = *(( OamsPsscmBssgpUnprovSigBvc*)buffer);

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmBssgpUnprovSigBvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmBssgpUnprovSigBvc.sysHdr.src.prcr is not correct ");
      break;
   }
  }while(0);


 /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPsscmCfgAlarmInd = *((OamsPsscmCfgAlarmInd *)buffer);

  /*Post-conditions check*/
  do{
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysHdr.msgType == OAMS_PSSCM_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId == ALARM_LAST_NSVC_DISABLED) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_MAJR) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsPsscmCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
  }while(0);


/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

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
        printf("\n2. Run TC_002");
        printf("\n3. Run TC_003");
        printf("\n4. Run TC_004");
        printf("\n5. Run TC_005");
        printf("\n6. Run TC_006");
        printf("\n7. Run TC_007");
        printf("\n8. Run TC_008");
        printf("\n9. Run TC_009");
        printf("\n10. Run TC_010");
        printf("\n11. Run TC_011");
        printf("\n12. Run TC_012");
        printf("\n13. Run TC_013");
        printf("\n14. Run TC_014");
        printf("\n15. Run TC_015");
        printf("\n16. Run TC_016");
        printf("\n17. Run TC_017");
        printf("\n18. Run TC_018");
        printf("\n19. Run TC_019");
        printf("\n20. Run TC_020");
        printf("\n21. Run TC_021");
        printf("\n22. Run TC_022");
        printf("\n23. Run TC_023");
        printf("\n24. Run TC_024");
        printf("\n25. Run TC_025");
        printf("\n26. Run TC_026");
        printf("\n27. Run TC_027");
        printf("\n28. Run TC_028");
        printf("\n29. Run TC_029");
        printf("\n30. Run TC_030");
        printf("\n31. Run TC_031");
        printf("\n32. Run TC_032");
        printf("\n33. Run TC_033");
        printf("\n34. Run TC_034");
        printf("\n35. Run TC_035");
        printf("\n36. Run TC_036");
        printf("\n37. Run TC_037");
        printf("\n38. Run TC_038");
        printf("\n39. Run TC_039");
        printf("\n40. Run TC_040");
        printf("\n41. Run TC_041");
        printf("\n42. Run TC_042");
        printf("\n43. Run TC_043");
        printf("\n44. Run TC_044");
        printf("\n45. Run TC_045");
        printf("\n46. Run TC_046");
        printf("\n47. Run TC_047");
        printf("\n48. Run TC_048");
        printf("\n49. Run TC_049");
        printf("\n50. Run TC_050");
        printf("\n51. Run TC_051");
        printf("\n52. Run TC_052");
        printf("\n53. Run TC_053");
        printf("\n54. Run TC_054");
        printf("\n55. Run TC_055");
        printf("\n56. Run TC_056");
        printf("\n57. Run TC_057");
        printf("\n58. Run TC_058");
        printf("\n59. Run TC_059");
        printf("\n60. Run TC_060");
        printf("\n61. Run TC_061");
        printf("\n62. Run TC_062");
        printf("\n63. Run TC_063");
        printf("\n64. Run TC_064");
        printf("\n65. Run TC_065");
        printf("\n66. Run TC_066");
        printf("\n67. Run TC_067");
        printf("\n68. Run TC_068");
        printf("\n69. Run TC_069");
        printf("\n70. Run TC_070");
        printf("\n71. Run TC_071");
        printf("\n72. Run TC_072");
        printf("\n73. Run TC_073");
        printf("\n74. Run TC_074");
        printf("\n75. Run TC_075");
        printf("\n76. Run TC_076");
        printf("\n77. Run TC_077");
        printf("\n78. Run TC_078");
        printf("\n79. Run TC_079");
        printf("\n80. Run TC_080");
        printf("\n81. Run TC_081");
        printf("\n82. Run TC_082");
        printf("\n83. Run TC_083");
        printf("\n84. Run TC_084");
  

        printf("\n84. Run TC_085");
	printf("\n86. Run TC_086");
        printf("\n87. Run TC_087");


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
         
         if( 2 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_002);
           printf("\nRunning Test Case TC_002"); 
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
         
         if( 8 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_008);
           printf("\nRunning Test Case TC_008"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 9 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_009);
           printf("\nRunning Test Case TC_009"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 10 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_010);
           printf("\nRunning Test Case TC_010"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 11 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_011);
           printf("\nRunning Test Case TC_011"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 12 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_012);
           printf("\nRunning Test Case TC_012"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 13 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_013);
           printf("\nRunning Test Case TC_013"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 14 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_014);
           printf("\nRunning Test Case TC_014"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 15 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_015);
           printf("\nRunning Test Case TC_015"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 16 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_016);
           printf("\nRunning Test Case TC_016"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 17 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_017);
           printf("\nRunning Test Case TC_017"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 18 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_018);
           printf("\nRunning Test Case TC_018"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 19 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_019);
           printf("\nRunning Test Case TC_019"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 20 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_020);
           printf("\nRunning Test Case TC_020"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 21 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_021);
           printf("\nRunning Test Case TC_021"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 22 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_022);
           printf("\nRunning Test Case TC_022"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 23 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_023);
           printf("\nRunning Test Case TC_023"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 24 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_024);
           printf("\nRunning Test Case TC_024"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 25 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_025);
           printf("\nRunning Test Case TC_025"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 26 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_026);
           printf("\nRunning Test Case TC_026"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 27 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_027);
           printf("\nRunning Test Case TC_027"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 28 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_028);
           printf("\nRunning Test Case TC_028"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 29 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_029);
           printf("\nRunning Test Case TC_029"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 30 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_030);
           printf("\nRunning Test Case TC_030"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 31 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_031);
           printf("\nRunning Test Case TC_031"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 32 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_032);
           printf("\nRunning Test Case TC_032"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 33 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_033);
           printf("\nRunning Test Case TC_033"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 34 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_034);
           printf("\nRunning Test Case TC_034"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 35 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_035);
           printf("\nRunning Test Case TC_035"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 36 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_036);
           printf("\nRunning Test Case TC_036"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 37 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_037);
           printf("\nRunning Test Case TC_037"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 38 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_038);
           printf("\nRunning Test Case TC_038"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 39 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_039);
           printf("\nRunning Test Case TC_039"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 40 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_040);
           printf("\nRunning Test Case TC_040"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 41 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_041);
           printf("\nRunning Test Case TC_041"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 42 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_042);
           printf("\nRunning Test Case TC_042"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 43 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_043);
           printf("\nRunning Test Case TC_043"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 44 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_044);
           printf("\nRunning Test Case TC_044"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 45 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_045);
           printf("\nRunning Test Case TC_045"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 46 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_046);
           printf("\nRunning Test Case TC_046"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 47 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_047);
           printf("\nRunning Test Case TC_047"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 48 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_048);
           printf("\nRunning Test Case TC_048"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 49 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_049);
           printf("\nRunning Test Case TC_049"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 50 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_050);
           printf("\nRunning Test Case TC_050"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 51 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_051);
           printf("\nRunning Test Case TC_051"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 52 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_052);
           printf("\nRunning Test Case TC_052"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 53 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_053);
           printf("\nRunning Test Case TC_053"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 54 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_054);
           printf("\nRunning Test Case TC_054"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 55 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_055);
           printf("\nRunning Test Case TC_055"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 56 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_056);
           printf("\nRunning Test Case TC_056"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 57 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_057);
           printf("\nRunning Test Case TC_057"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 58 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_058);
           printf("\nRunning Test Case TC_058"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 59 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_059);
           printf("\nRunning Test Case TC_059"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 60 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_060);
           printf("\nRunning Test Case TC_060"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 61 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_061);
           printf("\nRunning Test Case TC_061"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 62 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_062);
           printf("\nRunning Test Case TC_062"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 63 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_063);
           printf("\nRunning Test Case TC_063"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 64 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_064);
           printf("\nRunning Test Case TC_064"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 65 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_065);
           printf("\nRunning Test Case TC_065"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 66 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_066);
           printf("\nRunning Test Case TC_066"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 67 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_067);
           printf("\nRunning Test Case TC_067"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 68 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_068);
           printf("\nRunning Test Case TC_068"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 69 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_069);
           printf("\nRunning Test Case TC_069"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 70 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_070);
           printf("\nRunning Test Case TC_070"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 71 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_071);
           printf("\nRunning Test Case TC_071"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 72 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_072);
           printf("\nRunning Test Case TC_072"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 73 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_073);
           printf("\nRunning Test Case TC_073"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 74 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_074);
           printf("\nRunning Test Case TC_074"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 75 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_075);
           printf("\nRunning Test Case TC_075"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 76 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_076);
           printf("\nRunning Test Case TC_076"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 77 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_077);
           printf("\nRunning Test Case TC_077"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 78 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_078);
           printf("\nRunning Test Case TC_078"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 79 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_079);
           printf("\nRunning Test Case TC_079"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 80 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_080);
           printf("\nRunning Test Case TC_080"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 81 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_081);
           printf("\nRunning Test Case TC_081"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 82 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_082);
           printf("\nRunning Test Case TC_082"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 83 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_083);
           printf("\nRunning Test Case TC_083"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 84 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_084);
           printf("\nRunning Test Case TC_084"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }

         if( 85 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_085);
           printf("\nRunning Test Case TC_085"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
	 if( 86 == iTCChoice)
           {
           tcase_add_test (tc_core, TC_086);
           printf("\nRunning Test Case TC_086");
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }

         if( 87 == iTCChoice)
           {
           tcase_add_test (tc_core, TC_087);
           printf("\nRunning Test Case TC_087");
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


