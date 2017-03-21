#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  41
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

 TC Description: Send Unlock req to NSVCH
**************************************************************************/
START_TEST (TC_001)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchUnlockReq oamsCfgNsvchUnlockReq;

  /*Receive Message Struct */
   OamsNsvchNsProvFrLink oamsNsvchNsProvFrLink;
   oamsCfgNsvchUnlockReq.sysHdr.src.prcr = PRCR_CP;
   oamsCfgNsvchUnlockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgNsvchUnlockReq.sysHdr.src.clsId = 1;
   oamsCfgNsvchUnlockReq.sysHdr.src.rfu = 0;
   oamsCfgNsvchUnlockReq.sysHdr.src.inst = 0;
   oamsCfgNsvchUnlockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgNsvchUnlockReq.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   oamsCfgNsvchUnlockReq.sysHdr.dest.clsId = 2;
   oamsCfgNsvchUnlockReq.sysHdr.dest.rfu = 0;
   oamsCfgNsvchUnlockReq.sysHdr.dest.inst = 0;
   oamsCfgNsvchUnlockReq.sysHdr.msgType = OAMS_CFG_NSVCH_UNLOCK_REQ;
   oamsCfgNsvchUnlockReq.sysHdr.subType = MSG_SUB_TYPE;
   oamsCfgNsvchUnlockReq.sysHdr.priority = 0;
   oamsCfgNsvchUnlockReq.nsvcId = 5;
   oamsCfgNsvchUnlockReq.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgNsvchUnlockReq,sizeof(OamsCfgNsvchUnlockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsProvFrLink = *((OamsNsvchNsProvFrLink *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsProvFrLink.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.msgType == OAMS_NSVCH_NS_PROV_FR_LINK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.trId == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.trId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.apiId == OAM_NS_PROV_FR_LINKS) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvFrLink.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvFrLink.frChannel is not correct ");
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
 TC Name: TC_002

 TC Description: FR Provisioning successful   
**************************************************************************/
START_TEST (TC_002)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvFrLinkCnf pssksNsNsvchProvFrLinkCnf;

  /*Receive Message Struct */
   OamsNsvchNsProvNsvc oamsNsvchNsProvNsvc;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_FR_LINK_CNF;
   pssksNsNsvchProvFrLinkCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvFrLinkCnf.sysHdr.priority = 0;
   pssksNsNsvchProvFrLinkCnf.bufLen = 0;
   pssksNsNsvchProvFrLinkCnf.trId = 0;
   pssksNsNsvchProvFrLinkCnf.apiId = 0;
   pssksNsNsvchProvFrLinkCnf.frChannel = 5;
   pssksNsNsvchProvFrLinkCnf.result = BSS_SUCCESS;
   pssksNsNsvchProvFrLinkCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvFrLinkCnf,sizeof(PssksNsNsvchProvFrLinkCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsProvNsvc = *((OamsNsvchNsProvNsvc *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsProvNsvc.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.msgType == OAMS_NSVCH_NS_PROV_NSVC) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.apiId == OAM_NS_PROV_NSVCI) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.nsvci is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.dlci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.dlci is not correct ");
      break;
   }
   if(!(oamsNsvchNsProvNsvc.priority == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsProvNsvc.priority is not correct ");
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
 TC Name: TC_003

 TC Description: FR Provisioning successful,with LockReq received before this cnf. 
**************************************************************************/
START_TEST (TC_003)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvFrLinkCnf pssksNsNsvchProvFrLinkCnf;

  /*Receive Message Struct */
   OamsNsvchNsUnprovFrLink oamsNsvchNsUnprovFrLink;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_FR_LINK_CNF;
   pssksNsNsvchProvFrLinkCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvFrLinkCnf.sysHdr.priority = 0;
   pssksNsNsvchProvFrLinkCnf.bufLen = 0;
   pssksNsNsvchProvFrLinkCnf.trId = 0;
   pssksNsNsvchProvFrLinkCnf.apiId = 0;
   pssksNsNsvchProvFrLinkCnf.frChannel = 5;
   pssksNsNsvchProvFrLinkCnf.result = BSS_SUCCESS;
   pssksNsNsvchProvFrLinkCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvFrLinkCnf,sizeof(PssksNsNsvchProvFrLinkCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsUnprovFrLink = *((OamsNsvchNsUnprovFrLink *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.msgType == OAMS_NSVCH_NS_UNPROV_FR_LINK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.priority == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.priority is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.apiId == OAM_NS_UNPROV_FR_LINK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.frChannel is not correct ");
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
 TC Name: TC_004

 TC Description: FR Provisioning Failed
**************************************************************************/
START_TEST (TC_004)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvFrLinkCnf pssksNsNsvchProvFrLinkCnf;

  /*Receive Message Struct */
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockResp;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_FR_LINK_CNF;
   pssksNsNsvchProvFrLinkCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvFrLinkCnf.sysHdr.priority = 0;
   pssksNsNsvchProvFrLinkCnf.bufLen = 0;
   pssksNsNsvchProvFrLinkCnf.trId = 0;
   pssksNsNsvchProvFrLinkCnf.apiId = 0;
   pssksNsNsvchProvFrLinkCnf.frChannel = 5;
   pssksNsNsvchProvFrLinkCnf.result = BSS_FAILURE;
   pssksNsNsvchProvFrLinkCnf.cause = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvFrLinkCnf,sizeof(PssksNsNsvchProvFrLinkCnf));

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
   if(!(oamsNsvchCfgUnlockResp.result == OAMS_RSLT_FAILURE) )
   {
      flag = 0;
      fail("value of oamsNsvchCfgUnlockResp.result is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[4] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[4] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_005

 TC Description: FR Provisioning Failed,with LockReq received before this cnf. 
**************************************************************************/
START_TEST (TC_005)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvFrLinkCnf pssksNsNsvchProvFrLinkCnf;

  /*Receive Message Struct */
   OamsNsvchCfgLockResp oamsNsvchCfgLockResp;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvFrLinkCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_FR_LINK_CNF;
   pssksNsNsvchProvFrLinkCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvFrLinkCnf.sysHdr.priority = 0;
   pssksNsNsvchProvFrLinkCnf.bufLen = 0;
   pssksNsNsvchProvFrLinkCnf.trId = 0;
   pssksNsNsvchProvFrLinkCnf.apiId = 0;
   pssksNsNsvchProvFrLinkCnf.frChannel = 5;
   pssksNsNsvchProvFrLinkCnf.result = BSS_FAILURE;
   pssksNsNsvchProvFrLinkCnf.cause = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvFrLinkCnf,sizeof(PssksNsNsvchProvFrLinkCnf));

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
  }while(0);

   if(0 == flag)
      test_result[5] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[5] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_006

 TC Description: Lock Req received while waiting for FR provisioning cnf.
**************************************************************************/
START_TEST (TC_006)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
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

   if(0 == flag)
      test_result[6] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[6] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_007

 TC Description: NSVC provision successful
**************************************************************************/
START_TEST (TC_007)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvNsvcCnf pssksNsNsvchProvNsvcCnf;

  /*Receive Message Struct */
   OamsNsvchNsAddNsvcToNseiGrp oamsNsvchNsAddNsvcToNseiGrp;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_NSVC_CNF;
   pssksNsNsvchProvNsvcCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvNsvcCnf.sysHdr.priority = 0;
   pssksNsNsvchProvNsvcCnf.bufLen = 0;
   pssksNsNsvchProvNsvcCnf.trId = 0;
   pssksNsNsvchProvNsvcCnf.apiId = 0;
   pssksNsNsvchProvNsvcCnf.nsvci = 5;
   pssksNsNsvchProvNsvcCnf.result = BSS_SUCCESS;
   pssksNsNsvchProvNsvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvNsvcCnf,sizeof(PssksNsNsvchProvNsvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsAddNsvcToNseiGrp = *((OamsNsvchNsAddNsvcToNseiGrp *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.msgType == OAMS_NSVCH_NS_ADD_NSVC_TO_NSEI_GRP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.apiId == OAM_NS_ADD_NSVC_TO_NSEI_GRP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.nsei == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.nsei is not correct ");
      break;
   }
   if(!(oamsNsvchNsAddNsvcToNseiGrp.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsAddNsvcToNseiGrp.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[7] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[7] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_008

 TC Description: NSVC provision successful,with LockReq received before this cnf. 
**************************************************************************/
START_TEST (TC_008)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvNsvcCnf pssksNsNsvchProvNsvcCnf;

  /*Receive Message Struct */
   OamsNsvchNsUnprovNsvc oamsNsvchNsUnprovNsvc;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_NSVC_CNF;
   pssksNsNsvchProvNsvcCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvNsvcCnf.sysHdr.priority = 0;
   pssksNsNsvchProvNsvcCnf.bufLen = 0;
   pssksNsNsvchProvNsvcCnf.trId = 0;
   pssksNsNsvchProvNsvcCnf.apiId = 0;
   pssksNsNsvchProvNsvcCnf.nsvci = 5;
   pssksNsNsvchProvNsvcCnf.result = BSS_SUCCESS;
   pssksNsNsvchProvNsvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvNsvcCnf,sizeof(PssksNsNsvchProvNsvcCnf));

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
      test_result[8] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[8] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_009

 TC Description: NSVC provision Failed
**************************************************************************/
START_TEST (TC_009)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchProvNsvcCnf pssksNsNsvchProvNsvcCnf;

  /*Receive Message Struct */
   OamsNsvchNsUnprovFrLink oamsNsvchNsUnprovFrLink;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.src.inst = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchProvNsvcCnf.sysHdr.msgType = PSSKS_NS_NSVCH_PROV_NSVC_CNF;
   pssksNsNsvchProvNsvcCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchProvNsvcCnf.sysHdr.priority = 0;
   pssksNsNsvchProvNsvcCnf.bufLen = 0;
   pssksNsNsvchProvNsvcCnf.trId = 0;
   pssksNsNsvchProvNsvcCnf.apiId = 0;
   pssksNsNsvchProvNsvcCnf.nsvci = 5;
   pssksNsNsvchProvNsvcCnf.result = BSS_FAILURE;
   pssksNsNsvchProvNsvcCnf.cause = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchProvNsvcCnf,sizeof(PssksNsNsvchProvNsvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsUnprovFrLink = *((OamsNsvchNsUnprovFrLink *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.msgType == OAMS_NSVCH_NS_UNPROV_FR_LINK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.apiId == OAM_NS_UNPROV_FR_LINK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsUnprovFrLink.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsUnprovFrLink.frChannel is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[9] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[9] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_010

 TC Description: Lock Req received while waiting for NSVC provisioning cnf.
**************************************************************************/
START_TEST (TC_010)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
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

   if(0 == flag)
      test_result[10] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[10] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_011

 TC Description: Association of nsvci to nsei group sucessful
**************************************************************************/
START_TEST (TC_011)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchAddNsvcToNseiGrpCnf pssksNsNsvchAddNsvcToNseiGrpCnf;

  /*Receive Message Struct */
   OamsNsvchFrNStartReq oamsNsvchFrNStartReq;
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockResp;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.inst = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.msgType = PSSKS_NS_NSVCH_ADD_NSVC_TO_NSEI_GRP_CNF;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.priority = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.bufLen = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.trId = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.apiId = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.nsvci = 5;
   pssksNsNsvchAddNsvcToNseiGrpCnf.result = BSS_SUCCESS;
   pssksNsNsvchAddNsvcToNseiGrpCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchAddNsvcToNseiGrpCnf,sizeof(PssksNsNsvchAddNsvcToNseiGrpCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchFrNStartReq = *((OamsNsvchFrNStartReq *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchFrNStartReq.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.src.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.msgType == OAMS_NSVCH_FR_N_START_REQ) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.reserved1 == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.reserved1 is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.primCode == N_START_RQ) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.primCode is not correct ");
      break;
   }
   if(!(oamsNsvchFrNStartReq.dataLen == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchFrNStartReq.dataLen is not correct ");
      break;
   }
  }while(0);

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
  }while(0);

   if(0 == flag)
      test_result[11] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[11] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_012

 TC Description: Association of nsvci to nsei group sucessful,with LockReq received before this cnf. 
**************************************************************************/
START_TEST (TC_012)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchAddNsvcToNseiGrpCnf pssksNsNsvchAddNsvcToNseiGrpCnf;

  /*Receive Message Struct */
   OamsNsvchNsRemNsvcNseiGrp oamsNsvchNsRemNsvcNseiGrp;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.inst = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.msgType = PSSKS_NS_NSVCH_ADD_NSVC_TO_NSEI_GRP_CNF;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.priority = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.bufLen = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.trId = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.apiId = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.nsvci = 5;
   pssksNsNsvchAddNsvcToNseiGrpCnf.result = BSS_SUCCESS;
   pssksNsNsvchAddNsvcToNseiGrpCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchAddNsvcToNseiGrpCnf,sizeof(PssksNsNsvchAddNsvcToNseiGrpCnf));

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
      test_result[12] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[12] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_013

 TC Description: Association of nsvci to nsei group Failed
**************************************************************************/
START_TEST (TC_013)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchAddNsvcToNseiGrpCnf pssksNsNsvchAddNsvcToNseiGrpCnf;

  /*Receive Message Struct */
   OamsNsvchNsUnprovNsvc oamsNsvchNsUnprovNsvc;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.src.inst = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.msgType = PSSKS_NS_NSVCH_ADD_NSVC_TO_NSEI_GRP_CNF;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchAddNsvcToNseiGrpCnf.sysHdr.priority = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.bufLen = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.trId = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.apiId = 0;
   pssksNsNsvchAddNsvcToNseiGrpCnf.nsvci = 5;
   pssksNsNsvchAddNsvcToNseiGrpCnf.result = BSS_FAILURE;
   pssksNsNsvchAddNsvcToNseiGrpCnf.cause = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchAddNsvcToNseiGrpCnf,sizeof(PssksNsNsvchAddNsvcToNseiGrpCnf));

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
      test_result[13] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[13] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_014

 TC Description: Lock Req received while waiting for Nsvc add cnf.
**************************************************************************/
START_TEST (TC_014)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
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

   if(0 == flag)
      test_result[14] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[14] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_015

 TC Description: FR comes up (Conn Ind received) after FR/NSVC provisioning for same dlci
**************************************************************************/
START_TEST (TC_015)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNConnInd pssksFrNsvchNConnInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNConnInd oamsNsvchNsNConnInd;
   OamsNsvchNsNsvcReset oamsNsvchNsNsvcReset;
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
      test_result[15] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[15] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_016

 TC Description: FR comes up (Conn Ind received) after FR/NSVC provisioning for some other dlci
**************************************************************************/
START_TEST (TC_016)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNConnInd pssksFrNsvchNConnInd;

  /*Receive Message Struct */
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
   pssksFrNsvchNConnInd.dlci = 7;
   pssksFrNsvchNConnInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNConnInd,sizeof(PssksFrNsvchNConnInd));

   if(0 == flag)
      test_result[16] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[16] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_017

 TC Description: StatusInd(Fr Active) received in UnlockedDisabled state
**************************************************************************/
START_TEST (TC_017)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNsvcReset oamsNsvchNsNsvcReset;
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
      test_result[17] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[17] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_018

 TC Description: StatusInd(Fr Active) received in UnlockedDisabled state-Very initially before any CONN_IND
**************************************************************************/
START_TEST (TC_018)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
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

   if(0 == flag)
      test_result[18] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[18] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_019

 TC Description: StatusInd(Fr InActive) received in UnlockedDisabled state
**************************************************************************/
START_TEST (TC_019)
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
   pssksFrNsvchNStatusInd.cause[0] = PCHAN_NOT_ACTIVE;
   pssksFrNsvchNStatusInd.dlci = 5;
   pssksFrNsvchNStatusInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNStatusInd,sizeof(PssksFrNsvchNStatusInd));

   if(0 == flag)
      test_result[19] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[19] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_020

 TC Description: Lock Req received in UnlockedDisabled state
**************************************************************************/
START_TEST (TC_020)
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
      test_result[20] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[20] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_021

 TC Description: ConnInd received after receipt of statusInd(frActive)
**************************************************************************/
START_TEST (TC_021)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNConnInd pssksFrNsvchNConnInd;

  /*Receive Message Struct */
   OamsNsvchNsNConnInd oamsNsvchNsNConnInd;
   OamsNsvchNsNsvcReset oamsNsvchNsNsvcReset;
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
      test_result[21] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[21] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_022

 TC Description: Nsvch received Reset cnf from NS during Nsvc Reset Procedure
**************************************************************************/
START_TEST (TC_022)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcResetCnf pssksNsNsvchNsvcResetCnf;

  /*Receive Message Struct */
   pssksNsNsvchNsvcResetCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcResetCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcResetCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcResetCnf.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcResetCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcResetCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcResetCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcResetCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcResetCnf.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_RESET_CNF;
   pssksNsNsvchNsvcResetCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcResetCnf.sysHdr.priority = 0;
   pssksNsNsvchNsvcResetCnf.bufLen = 0;
   pssksNsNsvchNsvcResetCnf.trId = 0;
   pssksNsNsvchNsvcResetCnf.apiId = 0;
   pssksNsNsvchNsvcResetCnf.nsvci = 5;
   pssksNsNsvchNsvcResetCnf.result = BSS_SUCCESS;
   pssksNsNsvchNsvcResetCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcResetCnf,sizeof(PssksNsNsvchNsvcResetCnf));

   if(0 == flag)
      test_result[22] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[22] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_023

 TC Description: Nsvch received Reset Ind from NS during Nsvc Reset Procedure
**************************************************************************/
START_TEST (TC_023)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcResetInd pssksNsNsvchNsvcResetInd;

  /*Receive Message Struct */
   OamsNsvchNsNsvcUnblock oamsNsvchNsNsvcUnblock;
   pssksNsNsvchNsvcResetInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcResetInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcResetInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_RESET_IND;
   pssksNsNsvchNsvcResetInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcResetInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcResetInd.bufLen = 0;
   pssksNsNsvchNsvcResetInd.trId = 0;
   pssksNsNsvchNsvcResetInd.apiId = 0;
   pssksNsNsvchNsvcResetInd.nsvci = 5;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcResetInd,sizeof(PssksNsNsvchNsvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNsvcUnblock = *((OamsNsvchNsNsvcUnblock *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_UNBLOCK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.apiId == OAM_NS_UNBLOCK_REQUEST) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[23] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[23] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_024

 TC Description: Lock Req received during Nsvc Reset Procedure.
**************************************************************************/
START_TEST (TC_024)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
   OamsNsvchFrNStopReq oamsNsvchFrNStopReq;
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
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
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FRLINK_DISABLED) )
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
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[24] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[24] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_025

 TC Description: StatusInd(Fr InActive) received during Nsvc Reset Procedure.
**************************************************************************/
START_TEST (TC_025)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
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
   pssksFrNsvchNStatusInd.cause[0] = PCHAN_NOT_ACTIVE;
   pssksFrNsvchNStatusInd.dlci = 5;
   pssksFrNsvchNStatusInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNStatusInd,sizeof(PssksFrNsvchNStatusInd));

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
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FRLINK_DISABLED) )
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
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[25] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[25] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_026

 TC Description: PSSKS_FR_NSVCH_N_DISC_IND received during Nsvc Reset Procedure.
**************************************************************************/
START_TEST (TC_026)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNDiscInd pssksFrNsvchNDiscInd;

  /*Receive Message Struct */
   OamsNsvchNsNDiscInd oamsNsvchNsNDiscInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
   pssksFrNsvchNDiscInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNDiscInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNDiscInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.src.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNDiscInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNDiscInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_DISC_IND;
   pssksFrNsvchNDiscInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNDiscInd.sysHdr.priority = 0;
   pssksFrNsvchNDiscInd.reserved1 = 0;
   pssksFrNsvchNDiscInd.frChannel = 5;
   pssksFrNsvchNDiscInd.primCode = N_DISC_IN;
   pssksFrNsvchNDiscInd.receipt = 0;
   pssksFrNsvchNDiscInd.dataAttrib = 0;
   pssksFrNsvchNDiscInd.ssInfo = 0;
   pssksFrNsvchNDiscInd.connId = 5;
   pssksFrNsvchNDiscInd.dataLen = 0;
   pssksFrNsvchNDiscInd.refNum = 0;
   pssksFrNsvchNDiscInd.cause[2] = 0;
   pssksFrNsvchNDiscInd.dlci = 5;
   pssksFrNsvchNDiscInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNDiscInd,sizeof(PssksFrNsvchNDiscInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNDiscInd = *((OamsNsvchNsNDiscInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.msgType == OAMS_NSVCH_NS_N_DISC_IND) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.reserved1 == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.reserved1 is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.primCode == N_DISC_IN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.primCode is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.connId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.connId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.dlci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.dlci is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[26] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[26] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_027

 TC Description: alarm EVENT_PSSKS_NS_NSVC_RESET_FAILURE is received from NS.
**************************************************************************/
START_TEST (TC_027)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchAlarmInd pssksNsNsvchAlarmInd;

  /*Receive Message Struct */
   OamsNsvchNsNsvcReset oamsNsvchNsNsvcReset;
   pssksNsNsvchAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchAlarmInd.sysHdr.src.entity = 200;
   pssksNsNsvchAlarmInd.sysHdr.src.clsId = 1;
   pssksNsNsvchAlarmInd.sysHdr.src.rfu = 0;
   pssksNsNsvchAlarmInd.sysHdr.src.inst = 0;
   pssksNsNsvchAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchAlarmInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchAlarmInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchAlarmInd.sysHdr.dest.inst = 0;
   pssksNsNsvchAlarmInd.sysHdr.msgType = PSSKS_NS_NSVCH_ALARM_IND;
   pssksNsNsvchAlarmInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchAlarmInd.sysHdr.priority = 0;
   pssksNsNsvchAlarmInd.sysAlarmId = EVENT_PSSKS_NS_NSVC_RESET_FAILURE;
   pssksNsNsvchAlarmInd.alarmSeqNo = 0;
   pssksNsNsvchAlarmInd.alarmTime = 0;
   pssksNsNsvchAlarmInd.alarmLevel = 0;
   pssksNsNsvchAlarmInd.alarmReason = 0;
   pssksNsNsvchAlarmInd.key1 = 5;
   pssksNsNsvchAlarmInd.key2 = 0;
   pssksNsNsvchAlarmInd.key3 = 0;
   pssksNsNsvchAlarmInd.key4 = 0;
   pssksNsNsvchAlarmInd.info1 = 0;
   pssksNsNsvchAlarmInd.info2 = 0;
   pssksNsNsvchAlarmInd.info3 = 0;
   pssksNsNsvchAlarmInd.infostringLen = 0;
   pssksNsNsvchAlarmInd.infostring[150] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchAlarmInd,sizeof(PssksNsNsvchAlarmInd));

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
   if(!(oamsNsvchNsNsvcReset.reason == OAMS_CAUSE_NSVC_RESET_FAILURE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.reason is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[27] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[27] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_028

 TC Description: Nsvch received Unblock cnf from NS during Nsvc Unblock Procedure
**************************************************************************/
START_TEST (TC_028)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcUnblockCnf pssksNsNsvchNsvcUnblockCnf;

  /*Receive Message Struct */
   pssksNsNsvchNsvcUnblockCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_UNBLOCK_CNF;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcUnblockCnf.sysHdr.priority = 0;
   pssksNsNsvchNsvcUnblockCnf.bufLen = 0;
   pssksNsNsvchNsvcUnblockCnf.trId = 0;
   pssksNsNsvchNsvcUnblockCnf.apiId = 0;
   pssksNsNsvchNsvcUnblockCnf.nsvci = 5;
   pssksNsNsvchNsvcUnblockCnf.result = BSS_SUCCESS;
   pssksNsNsvchNsvcUnblockCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcUnblockCnf,sizeof(PssksNsNsvchNsvcUnblockCnf));

   if(0 == flag)
      test_result[28] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[28] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_029

 TC Description: Nsvch received Unblock Ind from NS during NsvcUnblock Procedure
**************************************************************************/
START_TEST (TC_029)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcUnblockInd pssksNsNsvchNsvcUnblockInd;

  /*Receive Message Struct */
   pssksNsNsvchNsvcUnblockInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcUnblockInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcUnblockInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcUnblockInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcUnblockInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcUnblockInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcUnblockInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcUnblockInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcUnblockInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcUnblockInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcUnblockInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_UNBLOCK_IND;
   pssksNsNsvchNsvcUnblockInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcUnblockInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcUnblockInd.bufLen = 0;
   pssksNsNsvchNsvcUnblockInd.trId = 0;
   pssksNsNsvchNsvcUnblockInd.apiId = 0;
   pssksNsNsvchNsvcUnblockInd.nsvci = 5;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcUnblockInd,sizeof(PssksNsNsvchNsvcUnblockInd));
  
   if(0 == flag)
      test_result[29] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[29] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_030

 TC Description: Lock Req received during Nsvc Unblock Procedure.
**************************************************************************/
START_TEST (TC_030)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
   OamsNsvchNsNsvcBlock oamsNsvchNsNsvcBlock;
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
  oamsNsvchNsNsvcBlock = *((OamsNsvchNsNsvcBlock *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_BLOCK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.apiId == OAM_NS_BLOCK_REQUEST) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.nsvci is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.reason == CAUSE_O_AND_M_INTERVENTION) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.reason is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[30] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[30] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_031

 TC Description: StatusInd(Fr InActive) received during Nsvc Unblock Procedure.
**************************************************************************/
START_TEST (TC_031)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
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
   pssksFrNsvchNStatusInd.cause[0] = PCHAN_NOT_ACTIVE;
   pssksFrNsvchNStatusInd.dlci = 5;
   pssksFrNsvchNStatusInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNStatusInd,sizeof(PssksFrNsvchNStatusInd));

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
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FRLINK_DISABLED) )
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
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[31] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[31] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_032

 TC Description: PSSKS_FR_NSVCH_N_DISC_IND received during Nsvc Unblock Procedure.
**************************************************************************/
START_TEST (TC_032)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNDiscInd pssksFrNsvchNDiscInd;

  /*Receive Message Struct */
   OamsNsvchNsNDiscInd oamsNsvchNsNDiscInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
   pssksFrNsvchNDiscInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNDiscInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNDiscInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.src.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNDiscInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNDiscInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_DISC_IND;
   pssksFrNsvchNDiscInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNDiscInd.sysHdr.priority = 0;
   pssksFrNsvchNDiscInd.reserved1 = 0;
   pssksFrNsvchNDiscInd.frChannel = 5;
   pssksFrNsvchNDiscInd.primCode = N_DISC_IN;
   pssksFrNsvchNDiscInd.receipt = 0;
   pssksFrNsvchNDiscInd.dataAttrib = 0;
   pssksFrNsvchNDiscInd.ssInfo = 0;
   pssksFrNsvchNDiscInd.connId = 5;
   pssksFrNsvchNDiscInd.dataLen = 0;
   pssksFrNsvchNDiscInd.refNum = 0;
   pssksFrNsvchNDiscInd.cause[2] = 0;
   pssksFrNsvchNDiscInd.dlci = 5;
   pssksFrNsvchNDiscInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNDiscInd,sizeof(PssksFrNsvchNDiscInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNDiscInd = *((OamsNsvchNsNDiscInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.msgType == OAMS_NSVCH_NS_N_DISC_IND) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.reserved1 == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.reserved1 is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.primCode == N_DISC_IN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.primCode is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.connId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.connId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.dlci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.dlci is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[32] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[32] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_033

 TC Description: Nsvch received Reset Ind from NS (from SGSN) during Nsvc Unblock Procedure
**************************************************************************/
START_TEST (TC_033)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcResetInd pssksNsNsvchNsvcResetInd;

  /*Receive Message Struct */
   pssksNsNsvchNsvcResetInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcResetInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcResetInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_RESET_IND;
   pssksNsNsvchNsvcResetInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcResetInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcResetInd.bufLen = 0;
   pssksNsNsvchNsvcResetInd.trId = 0;
   pssksNsNsvchNsvcResetInd.apiId = 0;
   pssksNsNsvchNsvcResetInd.nsvci = 5;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcResetInd,sizeof(PssksNsNsvchNsvcResetInd));

   if(0 == flag)
      test_result[33] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[33] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_034

 TC Description: Nsvch received Block Ind from NS (Unblock failure) during Nsvc Unblock Procedure
**************************************************************************/
START_TEST (TC_034)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcBlockInd pssksNsNsvchNsvcBlockInd;

  /*Receive Message Struct */
   OamsNsvchNsNsvcUnblock oamsNsvchNsNsvcUnblock;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_BLOCK_IND;
   pssksNsNsvchNsvcBlockInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcBlockInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcBlockInd.bufLen = 0;
   pssksNsNsvchNsvcBlockInd.trId = 0;
   pssksNsNsvchNsvcBlockInd.apiId = 0;
   pssksNsNsvchNsvcBlockInd.nsvci = 5;
   pssksNsNsvchNsvcBlockInd.blockCause = GSAL_UNBLOCK_NSVC_FAILURE;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcBlockInd,sizeof(PssksNsNsvchNsvcBlockInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNsvcUnblock = *((OamsNsvchNsNsvcUnblock *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_UNBLOCK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.apiId == OAM_NS_UNBLOCK_REQUEST) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcUnblock.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcUnblock.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[34] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[34] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_035

 TC Description: Nsvch received Block Ind from NS (SGSN) during Nsvc Unblock Procedure
**************************************************************************/
START_TEST (TC_035)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcBlockInd pssksNsNsvchNsvcBlockInd;

  /*Receive Message Struct */
   pssksNsNsvchNsvcBlockInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_BLOCK_IND;
   pssksNsNsvchNsvcBlockInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcBlockInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcBlockInd.bufLen = 0;
   pssksNsNsvchNsvcBlockInd.trId = 0;
   pssksNsNsvchNsvcBlockInd.apiId = 0;
   pssksNsNsvchNsvcBlockInd.nsvci = 5;
   pssksNsNsvchNsvcBlockInd.blockCause = GSAL_BLOCK_RECVD_FROM_SGSN;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcBlockInd,sizeof(PssksNsNsvchNsvcBlockInd));

   if(0 == flag)
      test_result[35] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[35] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_036

 TC Description: Lock req received when NSVC is fully operational
**************************************************************************/
START_TEST (TC_036)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchLockReq oamsCfgNsvchLockReq;

  /*Receive Message Struct */
   OamsNsvchNsNsvcBlock oamsNsvchNsNsvcBlock;
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
  oamsNsvchNsNsvcBlock = *((OamsNsvchNsNsvcBlock *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_BLOCK) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.apiId == OAM_NS_BLOCK_REQUEST) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.nsvci is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcBlock.reason == CAUSE_O_AND_M_INTERVENTION) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcBlock.reason is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[36] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[36] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_037

 TC Description: PSSKS_FR_NSVCH_N_DISC_IND received when NSVC is fully operational.
**************************************************************************/
START_TEST (TC_037)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNDiscInd pssksFrNsvchNDiscInd;

  /*Receive Message Struct */
   OamsNsvchNsNDiscInd oamsNsvchNsNDiscInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
   pssksFrNsvchNDiscInd.sysHdr.src.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.src.entity = ENT_PSSTK_FRU;
   pssksFrNsvchNDiscInd.sysHdr.src.clsId = 1;
   pssksFrNsvchNDiscInd.sysHdr.src.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.src.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.prcr = PRCR_PP;
   pssksFrNsvchNDiscInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksFrNsvchNDiscInd.sysHdr.dest.clsId = 2;
   pssksFrNsvchNDiscInd.sysHdr.dest.rfu = 0;
   pssksFrNsvchNDiscInd.sysHdr.dest.inst = 0;
   pssksFrNsvchNDiscInd.sysHdr.msgType = PSSKS_FR_NSVCH_N_DISC_IND;
   pssksFrNsvchNDiscInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksFrNsvchNDiscInd.sysHdr.priority = 0;
   pssksFrNsvchNDiscInd.reserved1 = 0;
   pssksFrNsvchNDiscInd.frChannel = 5;
   pssksFrNsvchNDiscInd.primCode = N_DISC_IN;
   pssksFrNsvchNDiscInd.receipt = 0;
   pssksFrNsvchNDiscInd.dataAttrib = 0;
   pssksFrNsvchNDiscInd.ssInfo = 0;
   pssksFrNsvchNDiscInd.connId = 5;
   pssksFrNsvchNDiscInd.dataLen = 0;
   pssksFrNsvchNDiscInd.refNum = 0;
   pssksFrNsvchNDiscInd.cause[2] = 0;
   pssksFrNsvchNDiscInd.dlci = 5;
   pssksFrNsvchNDiscInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNDiscInd,sizeof(PssksFrNsvchNDiscInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNDiscInd = *((OamsNsvchNsNDiscInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.msgType == OAMS_NSVCH_NS_N_DISC_IND) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.reserved1 == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.reserved1 is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.frChannel == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.frChannel is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.primCode == N_DISC_IN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.primCode is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.connId == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.connId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNDiscInd.dlci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNDiscInd.dlci is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP))
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2))
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[37] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[37] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_038

 TC Description: StatusInd(Fr InActive) received when NSVC is fully operational.
**************************************************************************/
START_TEST (TC_038)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
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
   pssksFrNsvchNStatusInd.cause[0] = PCHAN_NOT_ACTIVE;
   pssksFrNsvchNStatusInd.dlci = 5;
   pssksFrNsvchNStatusInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNStatusInd,sizeof(PssksFrNsvchNStatusInd));

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
   if(!(oamsNsvchCfgAlarmInd.sysAlarm.sysalarmId == ALARM_FRLINK_DISABLED) )
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
  oamsNsvchNsNsvcDown = *((OamsNsvchNsNsvcDown *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.entity == ENT_OAMS_PSSCM) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.clsId == 2) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.src.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.src.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.clsId == 1) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.clsId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.rfu == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.rfu is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.dest.inst == 0) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.dest.inst is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.msgType == OAMS_NSVCH_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.sysHdr.subType == MSG_SUB_TYPE) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.sysHdr.subType is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.apiId == OAM_NS_NSVC_DOWN) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.apiId is not correct ");
      break;
   }
   if(!(oamsNsvchNsNsvcDown.nsvci == 5) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcDown.nsvci is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[38] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[38] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_039

 TC Description: alarm MAX_RETRIES_EXHAUSTED received when NSVC is fully operational. 
**************************************************************************/
START_TEST (TC_039)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchAlarmInd pssksNsNsvchAlarmInd;

  /*Receive Message Struct */
   OamsNsvchNsNsvcReset oamsNsvchNsNsvcReset;
   pssksNsNsvchAlarmInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchAlarmInd.sysHdr.src.entity = 200;
   pssksNsNsvchAlarmInd.sysHdr.src.clsId = 1;
   pssksNsNsvchAlarmInd.sysHdr.src.rfu = 0;
   pssksNsNsvchAlarmInd.sysHdr.src.inst = 0;
   pssksNsNsvchAlarmInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchAlarmInd.sysHdr.dest.entity =ENT_OAMS_PSSCM;
   pssksNsNsvchAlarmInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchAlarmInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchAlarmInd.sysHdr.dest.inst = 0;
   pssksNsNsvchAlarmInd.sysHdr.msgType = PSSKS_NS_NSVCH_ALARM_IND;
   pssksNsNsvchAlarmInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchAlarmInd.sysHdr.priority = 0;
   pssksNsNsvchAlarmInd.sysAlarmId = EVENT_PSSKS_NS_MAX_TIMER_RETRIES_EXHAUSTED;
   pssksNsNsvchAlarmInd.alarmSeqNo = 0;
   pssksNsNsvchAlarmInd.alarmTime = 0;
   pssksNsNsvchAlarmInd.alarmLevel = 0;
   pssksNsNsvchAlarmInd.alarmReason = 0;
   pssksNsNsvchAlarmInd.key1 = 5;
   pssksNsNsvchAlarmInd.key2 = 0;
   pssksNsNsvchAlarmInd.key3 = 0;
   pssksNsNsvchAlarmInd.key4 = 0;
   pssksNsNsvchAlarmInd.info1 = 0;
   pssksNsNsvchAlarmInd.info2 = 0;
   pssksNsNsvchAlarmInd.info3 = 0;
   pssksNsNsvchAlarmInd.infostringLen = 0;
   pssksNsNsvchAlarmInd.infostring[150] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchAlarmInd,sizeof(PssksNsNsvchAlarmInd));

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
   if(!(oamsNsvchNsNsvcReset.reason == OAMS_CAUSE_MAX_TIMER_RETRIES_EXHAUSTED) )
   {
      flag = 0;
      fail("value of oamsNsvchNsNsvcReset.reason is not correct ");
      break;
   }
  }while(0);

   if(0 == flag)
      test_result[39] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[39] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_040

 TC Description: Block Ind recevied when NSVC is fully operational.
**************************************************************************/
START_TEST (TC_040)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcBlockInd pssksNsNsvchNsvcBlockInd;

  /*Receive Message Struct */
   pssksNsNsvchNsvcBlockInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcBlockInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_BLOCK_IND;
   pssksNsNsvchNsvcBlockInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcBlockInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcBlockInd.bufLen = 0;
   pssksNsNsvchNsvcBlockInd.trId = 0;
   pssksNsNsvchNsvcBlockInd.apiId = 0;
   pssksNsNsvchNsvcBlockInd.nsvci = 5;
   pssksNsNsvchNsvcBlockInd.blockCause = GSAL_BLOCK_RECVD_FROM_SGSN;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcBlockInd,sizeof(PssksNsNsvchNsvcBlockInd));

   if(0 == flag)
      test_result[40] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[40] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_041

 TC Description: Reset Ind is received when NSVC is fully operational.
**************************************************************************/
START_TEST (TC_041)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcResetInd pssksNsNsvchNsvcResetInd;

  /*Receive Message Struct */
   pssksNsNsvchNsvcResetInd.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetInd.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcResetInd.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcResetInd.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcResetInd.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_RESET_IND;
   pssksNsNsvchNsvcResetInd.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcResetInd.sysHdr.priority = 0;
   pssksNsNsvchNsvcResetInd.bufLen = 0;
   pssksNsNsvchNsvcResetInd.trId = 0;
   pssksNsNsvchNsvcResetInd.apiId = 0;
   pssksNsNsvchNsvcResetInd.nsvci = 5;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcResetInd,sizeof(PssksNsNsvchNsvcResetInd));

   if(0 == flag)
      test_result[41] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[41] = 1;    /* 1 for pass*/

}
END_TEST


 
int RunTestSuite(Suite * s)
{
   int number_failed;
   SRunner *sr = srunner_create(s);
   srunner_set_log(sr, "NSVCH.txt");
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

