#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  8
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
 TC Name: TC_051

 TC Description: Rem Nsvc Cnf received while deassociation of NSVC from Nsei group
**************************************************************************/
START_TEST (TC_051)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchRemNsvcToNseiGrpCnf pssksNsNsvchRemNsvcToNseiGrpCnf;

  /*Receive Message Struct */
   OamsNsvchNsUnprovNsvc oamsNsvchNsUnprovNsvc;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.src.inst = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.msgType = PSSKS_NS_NSVCH_REM_NSVC_NSEI_GRP_CNF;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchRemNsvcToNseiGrpCnf.sysHdr.priority = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.bufLen = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.trId = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.apiId = 0;
   pssksNsNsvchRemNsvcToNseiGrpCnf.nsvci = 5;
   pssksNsNsvchRemNsvcToNseiGrpCnf.result = BSS_SUCCESS;
   pssksNsNsvchRemNsvcToNseiGrpCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchRemNsvcToNseiGrpCnf,sizeof(PssksNsNsvchRemNsvcToNseiGrpCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsUnprovNsvc = *((OamsNsvchNsUnprovNsvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.msgType == OAMS_NSVCH_NS_UNPROV_NSVC) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.apiId == OAM_NS_UNPROV_NSVCI) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovNsvc.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovNsvc.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_052

 TC Description: FR Unprovision failed during Unlock procedure
**************************************************************************/
START_TEST (TC_052)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchUnprovFrLinkCnf pssksNsNsvchUnprovFrLinkCnf;

  /*Receive Message Struct */
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockResp;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.inst = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.msgType = PSSKS_NS_NSVCH_UNPROV_FR_LINK_CNF;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.priority = 0;
   pssksNsNsvchUnprovFrLinkCnf.bufLen = 0;
   pssksNsNsvchUnprovFrLinkCnf.trId = 0;
   pssksNsNsvchUnprovFrLinkCnf.apiId = 0;
   pssksNsNsvchUnprovFrLinkCnf.frChannel = 5;
   pssksNsNsvchUnprovFrLinkCnf.result = BSS_FAILURE;
   pssksNsNsvchUnprovFrLinkCnf.cause = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchUnprovFrLinkCnf,sizeof(PssksNsNsvchUnprovFrLinkCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchCfgUnlockResp = *((OamsNsvchCfgUnlockResp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchCfgUnlockResp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.msgType == OAMS_NSVCH_CFG_UNLOCK_RESP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.sysHdr.priority == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.sysHdr.priority is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.nsvcId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.nsvcId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.result == OAMS_RSLT_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.result is not correct ");
      break;
   }
   if(!(oamsNsvchCfgUnlockResp.cause == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.cause is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_053

 TC Description: FR Unprovision failed during Lock procedure
**************************************************************************/
START_TEST (TC_053)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchUnprovFrLinkCnf pssksNsNsvchUnprovFrLinkCnf;

  /*Receive Message Struct */
   OamsNsvchCfgLockResp oamsNsvchCfgLockResp;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.src.inst = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.msgType = PSSKS_NS_NSVCH_UNPROV_FR_LINK_CNF;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchUnprovFrLinkCnf.sysHdr.priority = 0;
   pssksNsNsvchUnprovFrLinkCnf.bufLen = 0;
   pssksNsNsvchUnprovFrLinkCnf.trId = 0;
   pssksNsNsvchUnprovFrLinkCnf.apiId = 0;
   pssksNsNsvchUnprovFrLinkCnf.frChannel = 5;
   pssksNsNsvchUnprovFrLinkCnf.result = BSS_FAILURE;
   pssksNsNsvchUnprovFrLinkCnf.cause = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchUnprovFrLinkCnf,sizeof(PssksNsNsvchUnprovFrLinkCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchCfgLockResp = *((OamsNsvchCfgLockResp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchCfgLockResp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.msgType == OAMS_NSVCH_CFG_LOCK_RESP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.sysHdr.priority == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.sysHdr.priority is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.nsvcId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.nsvcId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.result == OAMS_RSLT_SUCCESS) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.result is not correct ");
      break;
   }
   if(!(oamsNsvchCfgLockResp.cause == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgLockResp.cause is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[3] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[3] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_054

 TC Description: NSVC Down cnf received in WaitForNSVCIndDownCnf state(with no FR active/conn Ind in between)
**************************************************************************/
START_TEST (TC_054)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcDownCnf pssksNsNsvchNsvcDownCnf;

  /*Receive Message Struct */
   pssksNsNsvchNsvcDownCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_DOWN_CNF;
   pssksNsNsvchNsvcDownCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcDownCnf.sysHdr.priority = 0;
   pssksNsNsvchNsvcDownCnf.bufLen = 0;
   pssksNsNsvchNsvcDownCnf.trId = 0;
   pssksNsNsvchNsvcDownCnf.apiId = 0;
   pssksNsNsvchNsvcDownCnf.nsvci = 5;
   pssksNsNsvchNsvcDownCnf.result = BSS_SUCCESS;
   pssksNsNsvchNsvcDownCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcDownCnf,sizeof(PssksNsNsvchNsvcDownCnf));

   if(0 == flag)
      test_result[4] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[4] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_055

 TC Description: Lock Req received in WaitForNSVCIndDownCnf state
**************************************************************************/
START_TEST (TC_055)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
   OamsNsvchFrNStopReq oamsNsvchFrNStopReq;
   OamsNsvchNsRemNsvcNseiGrp oamsNsvchNsRemNsvcNseiGrp;
   oamsCfgNsvchLockReq.sysHdr.src.prcr = PRCR_CP;
   oamsCfgNsvchLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgNsvchLockReq.sysHdr.src.clsId = 1;
   oamsCfgNsvchLockReq.sysHdr.src.rfu = 0;
   oamsCfgNsvchLockReq.sysHdr.src.inst = 0;
   oamsCfgNsvchLockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgNsvchLockReq.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsCfgNsvchLockReq.sysHdr.dest.clsId = 2;
   oamsCfgNsvchLockReq.sysHdr.dest.rfu = 0;
   oamsCfgNsvchLockReq.sysHdr.dest.inst = 0;
   oamsCfgNsvchLockReq.sysHdr.msgType = OAMS_CFG_NSVCH_LOCK_REQ;
   oamsCfgNsvchLockReq.sysHdr.subType = MSG_SUB_TYPE;
   oamsCfgNsvchLockReq.sysHdr.priority = 0;
   oamsCfgNsvchLockReq.nsvcId = 5;
   oamsCfgNsvchLockReq.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgNsvchLockReq,sizeof(OamsCfgNsvchLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchFrNStopReq = *((OamsNsvchFrNStopReq *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchFrNStopReq.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.msgType == OAMS_NSVCH_FR_N_STOP_REQ) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.reserved1 == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.reserved1 is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.primCode == N_STOP_RQ) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.primCode is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStopReq.connId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStopReq.connId is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsRemNsvcNseiGrp = *((OamsNsvchNsRemNsvcNseiGrp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.msgType == OAMS_NSVCH_NS_REM_NSVC_NSEI_GRP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.bufLen == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.bufLen is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.trId == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.trId is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.apiId == OAM_NS_REM_NSVC_NSEI_GRP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsRemNsvcNseiGrp.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsRemNsvcNseiGrp.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[5] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[5] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_056

 TC Description: FR came UP(ConnInd received) in state WaitForNSVCIndDownCnf state
**************************************************************************/
START_TEST (TC_056)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNConnInd pssksFrNsvchNConnInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNConnInd oamsNsvchNsNConnInd;
   pssksFrNsvchNConnInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNConnInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNConnInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNConnInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNConnInd.sysHdr.src.inst = 0;
   pssksFrNsvchNConnInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNConnInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNConnInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNConnInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNConnInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNConnInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_CONN_IND;
   pssksFrNsvchNConnInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNConnInd.sysHdr.priority = 0;
   pssksFrNsvchNConnInd.reserved1 = 0;
   pssksFrNsvchNConnInd.frChannel = 5;
   pssksFrNsvchNConnInd.primCode = N_CONN_IN;
   pssksFrNsvchNConnInd.receipt = 0;
   pssksFrNsvchNConnInd.dataAttrib = 0;
   pssksFrNsvchNConnInd.ssInfo = 0;
   pssksFrNsvchNConnInd.connId = 5;
   pssksFrNsvchNConnInd.dataLen = 0;
   pssksFrNsvchNConnInd.refNum = 0;
   pssksFrNsvchNConnInd.cause[2] = 0;
   pssksFrNsvchNConnInd.dlci = 5;
   pssksFrNsvchNConnInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNConnInd,sizeof(PssksFrNsvchNConnInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchCfgAlarmInd = *((OamsNsvchCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.msgType == OAMS_NSVCH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FRLINK_ENABLED) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.key1 == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.infoStrLen != 0) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgAlarmInd.sysAlarm.infoStrLen is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNConnInd = *((OamsNsvchNsNConnInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNConnInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.msgType == OAMS_NSVCH_NS_N_CONN_IND) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.reserved1 == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.reserved1 is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.primCode == N_CONN_IN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.primCode is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.connId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.connId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNConnInd.dlci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNConnInd.dlci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[6] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[6] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_057

 TC Description: status Ind(Fr Active) received in WaitForNSVCIndDownCnf state & connId is invalid
**************************************************************************/
START_TEST (TC_057)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   pssksFrNsvchNStatusInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNStatusInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNStatusInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNStatusInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNStatusInd.sysHdr.src.inst = 0;
   pssksFrNsvchNStatusInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNStatusInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNStatusInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNStatusInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNStatusInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNStatusInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_STATUS_IND;
   pssksFrNsvchNStatusInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNStatusInd.sysHdr.priority = 0;
   pssksFrNsvchNStatusInd.reserved1 = 0;
   pssksFrNsvchNStatusInd.frChannel = 5;
   pssksFrNsvchNStatusInd.primCode = NS_OAM_STATUS_IND;
   pssksFrNsvchNStatusInd.receipt = 0;
   pssksFrNsvchNStatusInd.dataAttrib = 0;
   pssksFrNsvchNStatusInd.ssInfo = 0;
   pssksFrNsvchNStatusInd.connId = 5;
   pssksFrNsvchNStatusInd.dataLen = 0;
   pssksFrNsvchNStatusInd.refNum = 0;
   pssksFrNsvchNStatusInd.cause[0] = PCHAN_ACTIVE;
   pssksFrNsvchNStatusInd.dlci = 5;
   pssksFrNsvchNStatusInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNStatusInd,sizeof(PssksFrNsvchNStatusInd));

   if(0 == flag)
      test_result[7] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[7] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_058

 TC Description: NSVC Down cnf received in WaitForNSVCIndDownCnf state(with connInd in between)
**************************************************************************/
START_TEST (TC_058)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcDownCnf pssksNsNsvchNsvcDownCnf;

  /*Receive Message Struct */
   OamsNsvchNsNsvcReset oamsNsvchNsNsvcReset;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcDownCnf.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_DOWN_CNF;
   pssksNsNsvchNsvcDownCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcDownCnf.sysHdr.priority = 0;
   pssksNsNsvchNsvcDownCnf.bufLen = 0;
   pssksNsNsvchNsvcDownCnf.trId = 0;
   pssksNsNsvchNsvcDownCnf.apiId = 0;
   pssksNsNsvchNsvcDownCnf.nsvci = 5;
   pssksNsNsvchNsvcDownCnf.result = BSS_SUCCESS;
   pssksNsNsvchNsvcDownCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcDownCnf,sizeof(PssksNsNsvchNsvcDownCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNsvcReset = *((OamsNsvchNsNsvcReset *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcReset.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_RESET) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.apiId == OAM_NS_RESET_REQUEST) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.nsvci is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcReset.reason == OAMS_CAUSE_FRLINK_AVAILABLE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.reason is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[8] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[8] = 1;    /* 1 for pass*/

}
END_TEST


 
int RunTestSuite(Suite * s)
{
   int number_failed;
   SRunner *sr = srunner_create(s);
   //srunner_set_log(sr,log_fname);
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
       Suite *s = suite_create ("NSVCH");
       /* Core test case */
       TCase *tc_core = tcase_create ("Core");
       tcase_add_checked_fixture (tc_core, setup, teardown);
        system("clear");
        printf("\n0 : Previous Menu");
        printf("\n1. Run TC_051");
        printf("\n2. Run TC_052");
        printf("\n3. Run TC_053");
        printf("\n4. Run TC_054");
        printf("\n5. Run TC_055");
        printf("\n6. Run TC_056");
        printf("\n7. Run TC_057");
        printf("\n8. Run TC_058");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_051);
           printf("\nRunning Test Case TC_051"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 2 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_052);
           printf("\nRunning Test Case TC_052"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 3 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_053);
           printf("\nRunning Test Case TC_053"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 4 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_054);
           printf("\nRunning Test Case TC_054"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 5 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_055);
           printf("\nRunning Test Case TC_055"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 6 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_056);
           printf("\nRunning Test Case TC_056"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 7 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_057);
           printf("\nRunning Test Case TC_057"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 8 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_058);
           printf("\nRunning Test Case TC_058"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
        }
           }while(iTCChoice != 0);
      }
    if(2 == iChoice)
     {
      do{
       Suite *s = suite_create ("NSVCH");
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

