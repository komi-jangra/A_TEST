#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  33
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
   oamsCfgPsscmUnlockReq.sysHdr.src.prcr = PRCR_CP;
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
   oamsCfgPsscmUnlockReq.sysHdr.src.prcr = PRCR_CP;
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
   oamsCfgPsscmLockReq.sysHdr.src.prcr = PRCR_CP;
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
   oamsCfgPsscmLockReq.sysHdr.src.prcr = PRCR_CP;
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
  memcpy(tempBuffer,buffer,size); 
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
      fail("value of oamsPsscmNsProvLep.sysHdr.dest.clsId is %d , msgType is %d", oamsPsscmNsProvLep.sysHdr.dest.clsId, oamsPsscmNsProvLep.sysHdr.msgType );
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
      fail("value of oamsPsscmNsProvLep.refId is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->ip4Addr == 2887744272))
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.ip4Addr is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->udpPort == 2) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.udpPort is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->sigWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sigWeight is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->dataWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.dataWeight is not correct ");
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
   if(!(lepIpElemInfoPtr->ip4Addr == 2887744272))
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.ip4Addr is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->udpPort == 2) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.udpPort is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->sigWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.sigWeight is not correct ");
      break;
   }
   if(!(lepIpElemInfoPtr->dataWeight == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvLep.dataWeight is not correct ");
      break;
   }
free(tempBuffer);
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
   OamsPsscmBssgpUnprovSigBvc oamsPsscmBssgpUnprovSigBvc;
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
   if(!(oamsPsscmCfgUnlockResp.result == 1) )
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
   if(!(repIpElemInfoPtr->ip4Addr == 2887744272) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.ip4Addr is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->udpPort == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.udpPort is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->sigWeight == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.sigWeight is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->dataWeight == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsProvRep.dataWeight is not correct ");
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
  /* if(!(oamsPsscmCfgUnlockResp.sysHdr.src.clsId == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.src.clsId is not correct ");
      break;
   }
*/
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
/*   if(!(oamsPsscmCfgUnlockResp.sysHdr.dest.clsId == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgUnlockResp.sysHdr.dest.clsId is not correct ");
      break;
   }
*/
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
free(tempBuffer);
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
  /* if(!(oamsPsscmCfgLockResp.sysHdr.src.clsId == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.src.clsId is not correct ");
      break;
   }
*/
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
  /* if(!(oamsPsscmCfgLockResp.sysHdr.dest.clsId == 0) )
   {
      flag = 0;
      fail("value of oamsPsscmCfgLockResp.sysHdr.dest.clsId is not correct ");
      break;
   }
*/
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
   oamsCfgPsscmLockReq.sysHdr.src.prcr = PRCR_CP;
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
   oamsCfgPsscmLockReq.sysHdr.src.prcr = PRCR_CP;
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
   if(!(repIpElemInfoPtr->ip4Addr == 2887744272) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnProvRep.Ip4addr is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->udpPort == 5) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnProvRep.udpPort is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->sigWeight == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnProvRep.sigWeight is not correct ");
      break;
   }
   if(!(repIpElemInfoPtr->dataWeight == 1) )
   {
      flag = 0;
      fail("value of oamsPsscmNsUnProvRep.dataWeight is not correct ");
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


