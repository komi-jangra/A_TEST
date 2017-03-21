#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  98
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

 TC Description: UnlockReq
**************************************************************************/
START_TEST (TC_001)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschUnlockReq oamsCfgPschUnlockReq;

  /*Receive Message Struct */
   OamsPschPsscmProvPtpBvc oamsPschPsscmProvPtpBvc1;

   oamsCfgPschUnlockReq.sysHdr.src.prcr = 0;
   oamsCfgPschUnlockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschUnlockReq.sysHdr.src.clsId = 1;
   oamsCfgPschUnlockReq.sysHdr.src.rfu = 0;
   oamsCfgPschUnlockReq.sysHdr.src.inst = 0;
   oamsCfgPschUnlockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschUnlockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschUnlockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschUnlockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschUnlockReq.sysHdr.dest.inst = 0;
   oamsCfgPschUnlockReq.sysHdr.msgType = OAMS_CFG_PSCH_UNLOCK_REQ;
   oamsCfgPschUnlockReq.sysHdr.subType = 0;
   oamsCfgPschUnlockReq.sysHdr.priority = 0;
   oamsCfgPschUnlockReq.lac = 1;
   oamsCfgPschUnlockReq.cellId = 1;
   oamsCfgPschUnlockReq.cellIndex = 1;
   oamsCfgPschUnlockReq.bvci = 2;
   oamsCfgPschUnlockReq.reason = OAMS_RSN_OPERATORINITIATED;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschUnlockReq,sizeof(OamsCfgPschUnlockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmProvPtpBvc1 = *((OamsPschPsscmProvPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmProvPtpBvc1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmProvPtpBvc1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmProvPtpBvc1.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmProvPtpBvc1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmProvPtpBvc1.sysHdr.msgType == OAMS_PSCH_PSSCM_PROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmProvPtpBvc1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmProvPtpBvc1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmProvPtpBvc1.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_002

 TC Description: ProvisionAck
**************************************************************************/
START_TEST (TC_002)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsPsscmPschProvPtpBvcCnf oamsPsscmPschProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPschPsmshCreCellBvcMap oamsPschPsmshCreCellBvcMap1;
   OamsPschCfgUnlockResp oamsPschCfgUnlockResp2;
   GsalMessage gsalMessage3;
   
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.clsId = 1;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.rfu = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.inst = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.clsId = 1;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.inst = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType = OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.subType = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.priority = 0;
   oamsPsscmPschProvPtpBvcCnf.bvci = 2;
   oamsPsscmPschProvPtpBvcCnf.result = 0;
   oamsPsscmPschProvPtpBvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsPsscmPschProvPtpBvcCnf,sizeof(OamsPsscmPschProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshCreCellBvcMap1 = *((OamsPschPsmshCreCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshCreCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_CRE_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.bvci is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.ssb == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.ssb is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgUnlockResp2 = *((OamsPschCfgUnlockResp *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgUnlockResp2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.sysHdr.msgType == OAMS_PSCH_CFG_UNLOCK_RESP) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.lac is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.cellId is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage3 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage3.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage3.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage3.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage3.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_003

 TC Description: ProvisionAck
**************************************************************************/
START_TEST (TC_003)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsPsscmPschProvPtpBvcCnf oamsPsscmPschProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPschCfgUnlockResp oamsPschCfgUnlockResp1;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc2;

   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.clsId = 1;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.rfu = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.inst = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.clsId = 1;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.inst = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType = OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.subType = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.priority = 0;
   oamsPsscmPschProvPtpBvcCnf.bvci = 2;
   oamsPsscmPschProvPtpBvcCnf.result = 0;
   oamsPsscmPschProvPtpBvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsPsscmPschProvPtpBvcCnf,sizeof(OamsPsscmPschProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgUnlockResp1 = *((OamsPschCfgUnlockResp *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgUnlockResp1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp1.sysHdr.msgType == OAMS_PSCH_CFG_UNLOCK_RESP) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.lac is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.cellId is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc2 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_004

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_004)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_005

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_005)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

}
END_TEST


/**************************************************************************
 TC Name: TC_006

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_006)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_007

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_007)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_008

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_008)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;


   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_009

 TC Description: Lock
**************************************************************************/
START_TEST (TC_009)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

}
END_TEST


/**************************************************************************
 TC Name: TC_010

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_010)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_011

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_011)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd3;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled4;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd3 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled4 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_012

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_012)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled3;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled3 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_013

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_013)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_014

 TC Description: PtpBvcResetAck
**************************************************************************/
START_TEST (TC_014)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd3;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled4;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 2;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd3 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled4 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_015

 TC Description: PtpBvcResetAck
**************************************************************************/
START_TEST (TC_015)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled3;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 2;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled3 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_016

 TC Description: PtpBvcResetAck
**************************************************************************/
START_TEST (TC_016)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 2;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_017

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_017)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_018

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_018)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_019

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_019)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_020

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_020)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_021

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_021)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_022

 TC Description: Lock
**************************************************************************/
START_TEST (TC_022)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */
   OamsPschPsmshDelCellBvcMap oamsPschPsmshDelCellBvcMap1;
   GsalMessage gsalMessage2;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc3;

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshDelCellBvcMap1 = *((OamsPschPsmshDelCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc3 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_023

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_023)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_024

 TC Description: OpFailed
**************************************************************************/
START_TEST (TC_024)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailed;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsCfgPschBvcOpFailed.sysHdr.src.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschBvcOpFailed.sysHdr.src.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.src.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschBvcOpFailed.sysHdr.dest.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.dest.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.msgType = OAMS_CFG_PSCH_BVC_OP_FAILED;
   oamsCfgPschBvcOpFailed.sysHdr.subType = 0;
   oamsCfgPschBvcOpFailed.sysHdr.priority = 0;
   oamsCfgPschBvcOpFailed.cellIndex = 1;
   oamsCfgPschBvcOpFailed.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschBvcOpFailed,sizeof(OamsCfgPschBvcOpFailed));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_025

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_025)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd2;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd2 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_026

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_026)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd2;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd2 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_027

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_027)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_028

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_028)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_029

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_029)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_030

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_030)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_031

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_031)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_032

 TC Description: Lock
**************************************************************************/
START_TEST (TC_032)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */
   OamsPschPsmshDelCellBvcMap oamsPschPsmshDelCellBvcMap1;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc2;

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshDelCellBvcMap1 = *((OamsPschPsmshDelCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc2 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_033

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_033)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_034

 TC Description: OpFailed
**************************************************************************/
START_TEST (TC_034)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailed;

  /*Receive Message Struct */

   oamsCfgPschBvcOpFailed.sysHdr.src.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschBvcOpFailed.sysHdr.src.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.src.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschBvcOpFailed.sysHdr.dest.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.dest.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.msgType = OAMS_CFG_PSCH_BVC_OP_FAILED;
   oamsCfgPschBvcOpFailed.sysHdr.subType = 0;
   oamsCfgPschBvcOpFailed.sysHdr.priority = 0;
   oamsCfgPschBvcOpFailed.cellIndex = 1;
   oamsCfgPschBvcOpFailed.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschBvcOpFailed,sizeof(OamsCfgPschBvcOpFailed));

}
END_TEST


/**************************************************************************
 TC Name: TC_035

 TC Description: BlockAck
**************************************************************************/
START_TEST (TC_035)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_BLOCK_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcBlockAck.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_UNBLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcUnblock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcUnblock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_036

 TC Description: BlockAck
**************************************************************************/
START_TEST (TC_036)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_BLOCK_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcBlockAck.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

}
END_TEST


/**************************************************************************
 TC Name: TC_037

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_037)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd4;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled5;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd4 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled5 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_038

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_038)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled4;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled4 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_039

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_039)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_040

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_040)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_041

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_041)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_042

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_042)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_043

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_043)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_044

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_044)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_045

 TC Description: Lock
**************************************************************************/
START_TEST (TC_045)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */
   OamsPschPsmshDelCellBvcMap oamsPschPsmshDelCellBvcMap1;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc2;

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshDelCellBvcMap1 = *((OamsPschPsmshDelCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc2 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_046

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_046)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_047

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_047)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd2;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 1;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd2 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_048

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_048)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd2;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 1;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd2 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_049

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_049)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_050

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_050)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_051

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_051)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_052

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_052)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_053

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_053)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_054

 TC Description: Lock
**************************************************************************/
START_TEST (TC_054)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */
   OamsPschPsmshDelCellBvcMap oamsPschPsmshDelCellBvcMap1;
   GsalMessage gsalMessage2;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc3;

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshDelCellBvcMap1 = *((OamsPschPsmshDelCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc3 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_055

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_055)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_056

 TC Description: OpFailed
**************************************************************************/
START_TEST (TC_056)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailed;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsCfgPschBvcOpFailed.sysHdr.src.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschBvcOpFailed.sysHdr.src.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.src.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschBvcOpFailed.sysHdr.dest.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.dest.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.msgType = OAMS_CFG_PSCH_BVC_OP_FAILED;
   oamsCfgPschBvcOpFailed.sysHdr.subType = 0;
   oamsCfgPschBvcOpFailed.sysHdr.priority = 0;
   oamsCfgPschBvcOpFailed.cellIndex = 1;
   oamsCfgPschBvcOpFailed.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschBvcOpFailed,sizeof(OamsCfgPschBvcOpFailed));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_UNBLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcUnblock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcUnblock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_057

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_057)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd4;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled5;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd4 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled5 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_058

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_058)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled4;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled4 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_059

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_059)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_060

 TC Description: UnblockAck
**************************************************************************/
START_TEST (TC_060)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd3;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled4;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_UNBLOCK_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcUnblockAck.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd3 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd3.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd3.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled4 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_061

 TC Description: UnblockAck
**************************************************************************/
START_TEST (TC_061)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled3;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_UNBLOCK_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcUnblockAck.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled3 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled3.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled3.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_062

 TC Description: UnblockAck
**************************************************************************/
START_TEST (TC_062)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_UNBLOCK_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcUnblockAck.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_063

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_063)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_064

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_064)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_065

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_065)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_UNBLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcUnblock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcUnblock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_066

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_066)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_067

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_067)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_068

 TC Description: Lock
**************************************************************************/
START_TEST (TC_068)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */
   OamsPschPsmshDelCellBvcMap oamsPschPsmshDelCellBvcMap1;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc2;

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshDelCellBvcMap1 = *((OamsPschPsmshDelCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc2 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc2.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc2.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_069

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_069)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_070

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_070)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd4;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled5;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd4 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled5 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_071

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_071)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled4;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled4 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled4.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_072

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_072)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_073

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_073)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd2;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 1;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd2 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_074

 TC Description: UnprovCnf
**************************************************************************/
START_TEST (TC_074)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsPsscmPschUnprovPtpBvcCnf oamsPsscmPschUnprovPtpBvcCnf;

  /*Receive Message Struct */
   OamsPschCfgLockResp oamsPschCfgLockResp1;

   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.prcr = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.clsId = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.rfu = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.src.inst = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.prcr = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.clsId = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.rfu = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.dest.inst = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.msgType = OAMS_PSSCM_PSCH_UNPROV_PTP_BVC_CNF;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.subType = 0;
   oamsPsscmPschUnprovPtpBvcCnf.sysHdr.priority = 0;
   oamsPsscmPschUnprovPtpBvcCnf.bvci = 2;
   oamsPsscmPschUnprovPtpBvcCnf.result = 0;
   oamsPsscmPschUnprovPtpBvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsPsscmPschUnprovPtpBvcCnf,sizeof(OamsPsscmPschUnprovPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgLockResp1 = *((OamsPschCfgLockResp *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgLockResp1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgLockResp1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgLockResp1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgLockResp1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgLockResp1.sysHdr.msgType == OAMS_PSCH_CFG_LOCK_RESP) )
    {
      flag = 0;
      fail("value of oamsPschCfgLockResp1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCfgLockResp1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgLockResp1.lac is not correct ");
      break;
    }
    if(!(oamsPschCfgLockResp1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgLockResp1.cellId is not correct ");
      break;
    }
    if(!(oamsPschCfgLockResp1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgLockResp1.cellIndex is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_075

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_075)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd2;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 1;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd2 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_076

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_076)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled1 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_077

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_077)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd1;
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd1 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled2 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_078

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_078)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd2;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 0;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd2 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd2.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd2.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd2.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd2.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd2.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd2.cellIndex is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_079

 TC Description: CellBar
**************************************************************************/
START_TEST (TC_079)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschCellBarAccess oamsCfgPschCellBarAccess;

  /*Receive Message Struct */
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd1;

   oamsCfgPschCellBarAccess.sysHdr.src.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschCellBarAccess.sysHdr.src.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.src.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.src.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.prcr = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschCellBarAccess.sysHdr.dest.clsId = 1;
   oamsCfgPschCellBarAccess.sysHdr.dest.rfu = 0;
   oamsCfgPschCellBarAccess.sysHdr.dest.inst = 0;
   oamsCfgPschCellBarAccess.sysHdr.msgType = OAMS_CFG_PSCH_CELL_BAR_ACCESS;
   oamsCfgPschCellBarAccess.sysHdr.subType = 0;
   oamsCfgPschCellBarAccess.sysHdr.priority = 0;
   oamsCfgPschCellBarAccess.lac = 1;
   oamsCfgPschCellBarAccess.cellId = 1;
   oamsCfgPschCellBarAccess.cellIndex = 1;
   oamsCfgPschCellBarAccess.cellBar = 1;
   oamsCfgPschCellBarAccess.reason = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschCellBarAccess,sizeof(OamsCfgPschCellBarAccess));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd1 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd1.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_080

 TC Description: PsAllowed
**************************************************************************/
START_TEST (TC_080)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsAllowed oamsTrxhPschPsAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_ALLOWED;
   oamsTrxhPschPsAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsAllowed.lac = 1;
   oamsTrxhPschPsAllowed.cellId = 1;
   oamsTrxhPschPsAllowed.cellIndex = 1;
   oamsTrxhPschPsAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsAllowed,sizeof(OamsTrxhPschPsAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_081

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_081)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

}
END_TEST


/**************************************************************************
 TC Name: TC_082

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_082)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd1;
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   GsalMessage gsalMessage4;

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd1 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled2 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage4 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage4.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage4.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage4.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage4.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_083

 TC Description: PsNotAllowed
**************************************************************************/
START_TEST (TC_083)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsTrxhPschPsNotAllowed oamsTrxhPschPsNotAllowed;

  /*Receive Message Struct */
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   GsalMessage gsalMessage3;

   oamsTrxhPschPsNotAllowed.sysHdr.src.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.entity = ENT_OAMS_TRXH;
   oamsTrxhPschPsNotAllowed.sysHdr.src.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.src.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.src.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.prcr = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.clsId = 1;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.rfu = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.dest.inst = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.msgType = OAMS_TRXH_PSCH_PS_NOT_ALLOWED;
   oamsTrxhPschPsNotAllowed.sysHdr.subType = 0;
   oamsTrxhPschPsNotAllowed.sysHdr.priority = 0;
   oamsTrxhPschPsNotAllowed.lac = 1;
   oamsTrxhPschPsNotAllowed.cellId = 1;
   oamsTrxhPschPsNotAllowed.cellIndex = 1;
   oamsTrxhPschPsNotAllowed.ptrxId = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsTrxhPschPsNotAllowed,sizeof(OamsTrxhPschPsNotAllowed));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled1 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage3 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage3.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage3.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage3.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage3.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_084

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_084)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled1;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd2;
   GsalMessage gsalMessage3;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled1 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled1.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd2 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd2.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage3 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage3.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage3.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage3.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage3.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_085

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_085)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd1;
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   GsalMessage gsalMessage4;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd1 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled2 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage4 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage4.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage4.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage4.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage4.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_086

 TC Description: Lock
**************************************************************************/
START_TEST (TC_086)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschLockReq oamsCfgPschLockReq;

  /*Receive Message Struct */
   OamsPschPsmshDelCellBvcMap oamsPschPsmshDelCellBvcMap1;
   GsalMessage gsalMessage2;
   OamsPschPsscmUnprovPtpBvc oamsPschPsscmUnprovPtpBvc3;

   oamsCfgPschLockReq.sysHdr.src.prcr = 0;
   oamsCfgPschLockReq.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschLockReq.sysHdr.src.clsId = 1;
   oamsCfgPschLockReq.sysHdr.src.rfu = 0;
   oamsCfgPschLockReq.sysHdr.src.inst = 0;
   oamsCfgPschLockReq.sysHdr.dest.prcr = 0;
   oamsCfgPschLockReq.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschLockReq.sysHdr.dest.clsId = 1;
   oamsCfgPschLockReq.sysHdr.dest.rfu = 0;
   oamsCfgPschLockReq.sysHdr.dest.inst = 0;
   oamsCfgPschLockReq.sysHdr.msgType = OAMS_CFG_PSCH_LOCK_REQ ;
   oamsCfgPschLockReq.sysHdr.subType = 0;
   oamsCfgPschLockReq.sysHdr.priority = 0;
   oamsCfgPschLockReq.lac = 1;
   oamsCfgPschLockReq.cellId = 1;
   oamsCfgPschLockReq.cellIndex = 1;
   oamsCfgPschLockReq.reason = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschLockReq,sizeof(OamsCfgPschLockReq));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshDelCellBvcMap1 = *((OamsPschPsmshDelCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshDelCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshDelCellBvcMap1.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcBlock.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsscmUnprovPtpBvc3 = *((OamsPschPsscmUnprovPtpBvc *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.dest.entity == ENT_OAMS_PSSCM) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.sysHdr.msgType == OAMS_PSCH_PSSCM_UNPROV_PTP_BVC) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsscmUnprovPtpBvc3.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsscmUnprovPtpBvc3.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_087

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_087)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd1;

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd1 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellIndex is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_088

 TC Description: Shutdown
**************************************************************************/
START_TEST (TC_088)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschShutdownInd oamsCfgPschShutdownInd;

  /*Receive Message Struct */

   oamsCfgPschShutdownInd.sysHdr.src.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschShutdownInd.sysHdr.src.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.src.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.src.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.prcr = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschShutdownInd.sysHdr.dest.clsId = 1;
   oamsCfgPschShutdownInd.sysHdr.dest.rfu = 0;
   oamsCfgPschShutdownInd.sysHdr.dest.inst = 0;
   oamsCfgPschShutdownInd.sysHdr.msgType = OAMS_CFG_PSCH_SHUTDOWN_IND;
   oamsCfgPschShutdownInd.sysHdr.subType = 0;
   oamsCfgPschShutdownInd.sysHdr.priority = 0;
   oamsCfgPschShutdownInd.lac = 1;
   oamsCfgPschShutdownInd.cellId = 1;
   oamsCfgPschShutdownInd.cellIndex = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschShutdownInd,sizeof(OamsCfgPschShutdownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_089

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_089)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd4;
   OamsPschCellhPsCellEnabled oamsPschCellhPsCellEnabled5;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd4 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd4.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd4.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellEnabled5 = *((OamsPschCellhPsCellEnabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_ENABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellEnabled5.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellEnabled5.cellId is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_090

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_090)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;
   GsalMessage gsalMessage2;
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd = *((OamsPschGrhmCrsInd *)buffer);
  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);


  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled.lac == 1) )
    {
      flag = 0;
fail("value of oamsPschCellhPsCellDisabled.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled.cellId is not correct ");
      break;
    }
  }while(0);
  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);
  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage2 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage2.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_BLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage2.bssgpMessage.bvcBlock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage2.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_091

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_091)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */
   OamsPschGrhmCrsInd oamsPschGrhmCrsInd1;
   OamsPschCellhPsCellDisabled oamsPschCellhPsCellDisabled2;
   OamsPschCfgAlarmInd oamsPschCfgAlarmInd3;
   GsalMessage gsalMessage4;
   OamsPschTrxhPsAttrChangeInd oamsPschTrxhPsAttrChangeInd5;

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 1;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschGrhmCrsInd1 = *((OamsPschGrhmCrsInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschGrhmCrsInd1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.dest.entity == ENT_CSAPP_GRHM) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.sysHdr.msgType == OAMS_PSCH_GRHM_CRS_IND) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.lac is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellId is not correct ");
      break;
    }
    if(!(oamsPschGrhmCrsInd1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschGrhmCrsInd1.cellIndex is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCellhPsCellDisabled2 = *((OamsPschCellhPsCellDisabled *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.dest.entity == ENT_OAMS_CELLH) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.sysHdr.msgType == OAMS_PSCH_CELLH_PS_CELL_DISABLED) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.lac is not correct ");
      break;
    }
    if(!(oamsPschCellhPsCellDisabled2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCellhPsCellDisabled2.cellId is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgAlarmInd3 = *((OamsPschCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgAlarmInd3.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgAlarmInd3.sysHdr.msgType == OAMS_PSCH_CFG_ALARM_IND) )
    {
      flag = 0;
      fail("value of oamsPschCfgAlarmInd3.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage4 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage4.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage4.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage4.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET) )
    {
      flag = 0;
      fail("value of gsalMessage4.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage4.bssgpMessage.bvcReset.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage4.bssgpMessage.bvcReset.bvci is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschTrxhPsAttrChangeInd5 = *((OamsPschTrxhPsAttrChangeInd *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschTrxhPsAttrChangeInd5.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd5.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd5.sysHdr.dest.entity == ENT_OAMS_TRXH) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd5.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschTrxhPsAttrChangeInd5.sysHdr.msgType == OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND) )
    {
      flag = 0;
      fail("value of oamsPschTrxhPsAttrChangeInd5.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_092

 TC Description: FlowCtrlAck
**************************************************************************/
START_TEST (TC_092)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_FLOW_CTRL_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.flowControlBvcAck.tag[1] = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

}
END_TEST


/**************************************************************************
 TC Name: TC_093

 TC Description: ActPdchInd
**************************************************************************/
START_TEST (TC_093)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   CsappGrhmPschActPdchInd csappGrhmPschActPdchInd;

  /*Receive Message Struct */

   csappGrhmPschActPdchInd.sysHdr.src.prcr = 0;
   csappGrhmPschActPdchInd.sysHdr.src.entity = ENT_CSAPP_GRHM;
   csappGrhmPschActPdchInd.sysHdr.src.clsId = 0;
   csappGrhmPschActPdchInd.sysHdr.src.rfu = 0;
   csappGrhmPschActPdchInd.sysHdr.src.inst = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.prcr = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   csappGrhmPschActPdchInd.sysHdr.dest.clsId = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.rfu = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.inst = 0;
   csappGrhmPschActPdchInd.sysHdr.msgType = CSAPP_GRHM_PSCH_ACT_PDCH_IND;
   csappGrhmPschActPdchInd.sysHdr.subType = 0;
   csappGrhmPschActPdchInd.sysHdr.priority = 0;
   csappGrhmPschActPdchInd.cellIndex = 1;
   csappGrhmPschActPdchInd.numActivePDCH = 1;
   csappGrhmPschActPdchInd.numTrxUsedForPs = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&csappGrhmPschActPdchInd,sizeof(CsappGrhmPschActPdchInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_094

 TC Description: ActPdchInd
**************************************************************************/
START_TEST (TC_094)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   CsappGrhmPschActPdchInd csappGrhmPschActPdchInd;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   csappGrhmPschActPdchInd.sysHdr.src.prcr = 0;
   csappGrhmPschActPdchInd.sysHdr.src.entity = ENT_CSAPP_GRHM;
   csappGrhmPschActPdchInd.sysHdr.src.clsId = 0;
   csappGrhmPschActPdchInd.sysHdr.src.rfu = 0;
   csappGrhmPschActPdchInd.sysHdr.src.inst = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.prcr = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   csappGrhmPschActPdchInd.sysHdr.dest.clsId = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.rfu = 0;
   csappGrhmPschActPdchInd.sysHdr.dest.inst = 0;
   csappGrhmPschActPdchInd.sysHdr.msgType = CSAPP_GRHM_PSCH_ACT_PDCH_IND;
   csappGrhmPschActPdchInd.sysHdr.subType = 0;
   csappGrhmPschActPdchInd.sysHdr.priority = 0;
   csappGrhmPschActPdchInd.cellIndex = 1;
   csappGrhmPschActPdchInd.numActivePDCH = 1;
   csappGrhmPschActPdchInd.numTrxUsedForPs = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&csappGrhmPschActPdchInd,sizeof(CsappGrhmPschActPdchInd));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_095

 TC Description: ProvisionAck
**************************************************************************/
START_TEST (TC_095)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsPsscmPschProvPtpBvcCnf oamsPsscmPschProvPtpBvcCnf;

  /*Receive Message Struct */
   OamsPschPsmshCreCellBvcMap oamsPschPsmshCreCellBvcMap1;
   OamsPschCfgUnlockResp oamsPschCfgUnlockResp2;

   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.prcr = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.entity = ENT_OAMS_PSSCM;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.clsId = 1;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.rfu = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.src.inst = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.prcr = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.clsId = 1;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.rfu = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.dest.inst = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.msgType = OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.subType = 0;
   oamsPsscmPschProvPtpBvcCnf.sysHdr.priority = 0;
   oamsPsscmPschProvPtpBvcCnf.bvci = 2;
   oamsPsscmPschProvPtpBvcCnf.result = 0;
   oamsPsscmPschProvPtpBvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsPsscmPschProvPtpBvcCnf,sizeof(OamsPsscmPschProvPtpBvcCnf));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschPsmshCreCellBvcMap1 = *((OamsPschPsmshCreCellBvcMap *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschPsmshCreCellBvcMap1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.sysHdr.dest.entity == ENT_PSAPP_PSMSH) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.sysHdr.msgType == OAMS_PSCH_PSMSH_CRE_CELL_BVC_MAP) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.bvci is not correct ");
      break;
    }
    if(!(oamsPschPsmshCreCellBvcMap1.ssb == 1) )
    {
      flag = 0;
      fail("value of oamsPschPsmshCreCellBvcMap1.ssb is not correct ");
      break;
    }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsPschCfgUnlockResp2 = *((OamsPschCfgUnlockResp *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(oamsPschCfgUnlockResp2.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.sysHdr.dest.entity == ENT_OAMS_CFG) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.sysHdr.msgType == OAMS_PSCH_CFG_UNLOCK_RESP) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.sysHdr.msgType is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.lac == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.lac is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.cellId == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.cellId is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.cellIndex == 1) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.cellIndex is not correct ");
      break;
    }
    if(!(oamsPschCfgUnlockResp2.bvci == 2) )
    {
      flag = 0;
      fail("value of oamsPschCfgUnlockResp2.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


/**************************************************************************
 TC Name: TC_096

 TC Description: ProvisionAck
**************************************************************************/
START_TEST (TC_096)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;


   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 1;
   oamsGbhPschSigBvcResetInd.isCblChanged = 1;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));
}
END_TEST


/**************************************************************************
 TC Name: TC_097

 TC Description: Gbdown
**************************************************************************/
START_TEST (TC_097)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;

  /*Receive Message Struct */

   oamsGbhPschGbDownInd.sysHdr.src.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschGbDownInd.sysHdr.src.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.src.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.src.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.prcr = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschGbDownInd.sysHdr.dest.clsId = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.rfu = 0;
   oamsGbhPschGbDownInd.sysHdr.dest.inst = 0;
   oamsGbhPschGbDownInd.sysHdr.msgType = OAMS_GBH_PSCH_GB_DOWN_IND;
   oamsGbhPschGbDownInd.sysHdr.subType = 0;
   oamsGbhPschGbDownInd.sysHdr.priority = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschGbDownInd,sizeof(OamsGbhPschGbDownInd));

}
END_TEST


/**************************************************************************
 TC Name: TC_098

 TC Description: SigBvcReset
**************************************************************************/
START_TEST (TC_098)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;

  /*Receive Message Struct */

   oamsGbhPschSigBvcResetInd.sysHdr.src.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.entity = ENT_OAMS_GBH;
   oamsGbhPschSigBvcResetInd.sysHdr.src.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.src.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.src.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.clsId = 1;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.rfu = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.dest.inst = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.msgType = OAMS_GBH_PSCH_SIG_BVC_RESET_IND;
   oamsGbhPschSigBvcResetInd.sysHdr.subType = 0;
   oamsGbhPschSigBvcResetInd.sysHdr.priority = 0;
   oamsGbhPschSigBvcResetInd.cbl = 0;
   oamsGbhPschSigBvcResetInd.isCblChanged = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsGbhPschSigBvcResetInd,sizeof(OamsGbhPschSigBvcResetInd));

}
END_TEST
/**************************************************************************
 TC Name: TC_099

 TC Description: OpFailed
**************************************************************************/
START_TEST (TC_099)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   OamsCfgPschBvcOpFailed oamsCfgPschBvcOpFailed;

  /*Receive Message Struct */
  GsalMessage gsalMessage1;
   oamsCfgPschBvcOpFailed.sysHdr.src.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgPschBvcOpFailed.sysHdr.src.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.src.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.src.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.prcr = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.entity = ENT_OAMS_PSCH;
   oamsCfgPschBvcOpFailed.sysHdr.dest.clsId = 1;
   oamsCfgPschBvcOpFailed.sysHdr.dest.rfu = 0;
   oamsCfgPschBvcOpFailed.sysHdr.dest.inst = 0;
   oamsCfgPschBvcOpFailed.sysHdr.msgType = OAMS_CFG_PSCH_BVC_OP_FAILED;
   oamsCfgPschBvcOpFailed.sysHdr.subType = 0;
   oamsCfgPschBvcOpFailed.sysHdr.priority = 0;
   oamsCfgPschBvcOpFailed.cellIndex = 1;
   oamsCfgPschBvcOpFailed.bvci = 2;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgPschBvcOpFailed,sizeof(OamsCfgPschBvcOpFailed));
  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_UNBLOCK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcUnblock.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcUnblock.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST

/**************************************************************************
 TC Name: TC_100

 TC Description: PtpBvcReset
**************************************************************************/
START_TEST (TC_100)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct*/
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   GsalMessage gsalMessage1;

   gsalMessage.sysHdr.src.prcr = 0;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = 0;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_PSCH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_PSCH_PTP_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = 0;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 0;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.isMsIdPresent = 0;
   gsalMessage.bssgpMessage.msId = 0;
   gsalMessage.bssgpMessage.isTlliIndexPresent = 0;
   gsalMessage.bssgpMessage.tlliIndex = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 2;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = 0;
   gsalMessage.bssgpMessage.bvcReset.cellId[8] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = 0;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[1] = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage1 = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
    if(!(gsalMessage1.sysHdr.src.entity == ENT_OAMS_PSCH) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.src.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.dest.entity == ENT_PSSTK_GSAL) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.dest.entity is not correct ");
      break;
    }
    if(!(gsalMessage1.sysHdr.msgType == OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK) )
    {
      flag = 0;
      fail("value of gsalMessage1.sysHdr.msgType is not correct ");
      break;
    }
    if(!(gsalMessage1.bssgpMessage.bvcResetAck.bvci == 2) )
    {
      flag = 0;
      fail("value of gsalMessage1.bssgpMessage.bvcResetAck.bvci is not correct ");
      break;
    }
  }while(0);

}
END_TEST


 
int RunTestSuite(Suite * s)
{
   int number_failed;
   SRunner *sr = srunner_create(s);
   srunner_set_log(sr,"Model.txt");
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
   int iResult = 1; 
   GbIfStatusTableApi gbIfTableRef;
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
       Suite *s = suite_create ("PSCH");
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
        printf("\n85. Run TC_085");
        printf("\n86. Run TC_086");
        printf("\n87. Run TC_087");
        printf("\n88. Run TC_088");
        printf("\n89. Run TC_089");
        printf("\n90. Run TC_090");
        printf("\n91. Run TC_091");
        printf("\n92. Run TC_092");
        printf("\n93. Run TC_093");
        printf("\n94. Run TC_094");
        printf("\n95. Run TC_095");
        printf("\n96. Run TC_096");
        printf("\n97. Run TC_097");
        printf("\n98. Run TC_098");
        printf("\n99. Run TC_099");
        printf("\n100. Run TC_100");
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
         
         if( 88 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_088);
           printf("\nRunning Test Case TC_088"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 89 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_089);
           printf("\nRunning Test Case TC_089"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 90 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_090);
           printf("\nRunning Test Case TC_090"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 91 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_091);
           printf("\nRunning Test Case TC_091"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 92 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_092);
           printf("\nRunning Test Case TC_092"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 93 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_093);
           printf("\nRunning Test Case TC_093"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 94 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_094);
           printf("\nRunning Test Case TC_094"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 95 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_095);
           printf("\nRunning Test Case TC_095"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 96 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_096);
           printf("\nRunning Test Case TC_096"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 97 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_097);
           printf("\nRunning Test Case TC_097"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 98 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_098);
           printf("\nRunning Test Case TC_098"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         if( 99 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_099);
           printf("\nRunning Test Case TC_099"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         if( 100 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_100);
           printf("\nRunning Test Case TC_100"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
        }
           }while(iTCChoice != 0);
      }
    if(2 == iChoice)
     {
      do{
         Suite *s = suite_create ("PSCH");
         system("clear");
         printf("\n0 : Previous Menu");
         printf("\n1: ");
         printf(" TS_1 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n2: ");
         printf(" TS_2 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n3: ");
         printf(" TS_3 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->GbDown ");
         printf(" GbDown->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n4: ");
         printf(" TS_4 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" PSAllowed->Enabled ");
         printf(" Enabled->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n5: ");
         printf(" TS_5 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n6: ");
         printf(" TS_6 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n7: ");
         printf(" TS_7 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n8: ");
         printf(" TS_8 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n9: ");
         printf(" TS_9 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->GbDown ");
         printf(" GbDown->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n10: ");
         printf(" TS_10 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->GbDown ");
         printf(" GbDown->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" PSAllowed->Enabled ");
         printf(" Enabled->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" PSAllowed->Enabled ");
         printf(" Enabled->GbDown ");
         printf(" GbDown->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n11: ");
         printf(" TS_11 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->GbDown ");
         printf(" GbDown->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" PSAllowed->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->GbDown ");
         printf(" GbDown->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n12: ");
         printf(" TS_12 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->Enabled ");
         printf(" Enabled->GbDown ");
         printf(" GbDown->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n13: ");
         printf(" TS_13 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcResetAck ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSNotAllowed ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->WaitingBvcResetAck ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->PSAllowed ");
         printf(" WaitingBvcUnblockAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->Blocked ");
         printf(" Blocked->PSNotAllowed ");
         printf(" Blocked->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n14: ");
         printf(" TS_14 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" PSAllowed->Enabled ");
         printf(" Enabled->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->PSAllowed ");
         printf(" WaitingBvcUnblockAck->PSNotAllowed ");
         printf(" WaitingBvcUnblockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->Enabled ");
         printf(" Enabled->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n15: ");
         printf(" TS_15 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->PSAllowed ");
         printf(" Enabled->PSAllowed ");
         printf(" Enabled->PSNotAllowed ");
         printf(" Enabled->GbDown ");
         printf(" GbDown->GbDown ");
         printf(" GbDown->GbDown ");
         printf(" GbDown->GbDown ");
         printf(" GbDown->GbDown ");
         printf(" GbDown->GbDown ");
         printf(" GbDown->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n16: ");
         printf(" TS_16 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->GbDown ");
         printf(" GbDown->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->GbDown ");
         printf(" GbDown->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" PSAllowed->Enabled ");
         printf(" Enabled->WaitingBvcUnprovisionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("  ");
         printf("\n17: ");
         printf(" TS_17 : ");
         printf(" CellIdle->WaitingBvcProvisioningAck ");
         printf(" WaitingBvcProvisioningAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSAllowed ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->Enabled ");
         printf(" Enabled->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->Enabled ");
         printf(" Enabled->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->PSNotAllowed ");
         printf(" WaitingBvcUnblockAck->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->Blocked ");
         printf(" Blocked->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->Blocked ");
         printf(" Blocked->WaitingBvcResetAck ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->WaitingBvcResetAck ");
         printf(" WaitingBvcResetAck->PSNotAllowed ");
         printf(" PSNotAllowed->WaitingBvcBlockAck ");
         printf(" WaitingBvcBlockAck->PSAllowed ");
         printf(" WaitingBvcBlockAck->WaitingBvcUnblockAck ");
         printf(" WaitingBvcUnblockAck->GbDown ");
         printf(" GbDown->WaitingBvcUnprovosionAck ");
         printf(" WaitingBvcUnprovisionAck->CellIdle ");
         printf("\n 100: Run all Test Suits");
         printf("\nPlease enter your choice : ");
         scanf("%d",&iTSChoice); 
         if( 1 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_01 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_009 WaitingBvcProvisioningAck->WaitingBvcProvisioningAck");
            printf("(3). ");
            printf("\nTC_003 WaitingBvcProvisioningAck->WaitingBvcUnprovisionAck");
            printf("(4). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc1 = tcase_create("core");
               tcase_add_test(tc1,TC_001);
               tcase_add_test(tc1,TC_009);
               tcase_add_test(tc1,TC_003);
               tcase_add_test(tc1,TC_074);
               suite_add_tcase(s,tc1);
               RunTestSuite(s);
           }
         }
         if( 2 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_02 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_022 WaitingBvcResetAck->WaitingBvcUnprovisionAck");
            printf("(4). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc2 = tcase_create("core");
               tcase_add_test(tc2,TC_001);
               tcase_add_test(tc2,TC_002);
               tcase_add_test(tc2,TC_022);
               tcase_add_test(tc2,TC_074);
               suite_add_tcase(s,tc2);
               RunTestSuite(s);
           }
         }
         if( 3 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_03 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_017 WaitingBvcResetAck->GbDown");
            printf("(4). ");
            printf("\nTC_045 GbDown->WaitingBvcUnprovisionAck");
            printf("(5). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc3 = tcase_create("core");
               tcase_add_test(tc3,TC_001);
               tcase_add_test(tc3,TC_002);
               tcase_add_test(tc3,TC_017);
               tcase_add_test(tc3,TC_045);
               tcase_add_test(tc3,TC_074);
               suite_add_tcase(s,tc3);
               RunTestSuite(s);
           }
         }
         if( 4 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_04 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(4). ");
            printf("\nTC_011 PSAllowed->Enabled");
            printf("(5). ");
            printf("\nTC_086 Enabled->WaitingBvcUnprovisionAck");
            printf("(6). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc4 = tcase_create("core");
               tcase_add_test(tc4,TC_001);
               tcase_add_test(tc4,TC_002);
               tcase_add_test(tc4,TC_019);
               tcase_add_test(tc4,TC_011);
               tcase_add_test(tc4,TC_086);
               tcase_add_test(tc4,TC_074);
               suite_add_tcase(s,tc4);
               RunTestSuite(s);
           }
         }
         if( 5 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_05 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_032 WaitingBvcBlockAck->WaitingBvcUnprovisionAck");
            printf("(6). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc5 = tcase_create("core");
               tcase_add_test(tc5,TC_001);
               tcase_add_test(tc5,TC_002);
               tcase_add_test(tc5,TC_020);
               tcase_add_test(tc5,TC_013);
               tcase_add_test(tc5,TC_032);
               tcase_add_test(tc5,TC_074);
               suite_add_tcase(s,tc5);
               RunTestSuite(s);
           }
         }
         if( 6 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_06 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(6). ");
            printf("\nTC_035 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(7). ");
            printf("\nTC_054 WaitingBvcUnblockAck->WaitingBvcUnprovisionAck");
            printf("(8). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc6 = tcase_create("core");
               tcase_add_test(tc6,TC_001);
               tcase_add_test(tc6,TC_002);
               tcase_add_test(tc6,TC_020);
               tcase_add_test(tc6,TC_013);
               tcase_add_test(tc6,TC_029);
               tcase_add_test(tc6,TC_035);
               tcase_add_test(tc6,TC_054);
               tcase_add_test(tc6,TC_074);
               suite_add_tcase(s,tc6);
               RunTestSuite(s);
           }
         }
         if( 7 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_07 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_034 WaitingBvcBlockAck->Blocked");
            printf("(6). ");
            printf("\nTC_068 Blocked->WaitingBvcUnprovisionAck");
            printf("(7). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc7 = tcase_create("core");
               tcase_add_test(tc7,TC_001);
               tcase_add_test(tc7,TC_002);
               tcase_add_test(tc7,TC_020);
               tcase_add_test(tc7,TC_013);
               tcase_add_test(tc7,TC_034);
               tcase_add_test(tc7,TC_068);
               tcase_add_test(tc7,TC_074);
               suite_add_tcase(s,tc7);
               RunTestSuite(s);
           }
         }
         if( 8 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_08 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_034 WaitingBvcBlockAck->Blocked");
            printf("(6). ");
            printf("\nTC_067 Blocked->WaitingBvcResetAck");
            printf("(7). ");
            printf("\nTC_022 WaitingBvcResetAck->WaitingBvcUnprovisionAck");
            printf("(8). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc8 = tcase_create("core");
               tcase_add_test(tc8,TC_001);
               tcase_add_test(tc8,TC_002);
               tcase_add_test(tc8,TC_020);
               tcase_add_test(tc8,TC_013);
               tcase_add_test(tc8,TC_034);
               tcase_add_test(tc8,TC_067);
               tcase_add_test(tc8,TC_022);
               tcase_add_test(tc8,TC_074);
               suite_add_tcase(s,tc8);
               RunTestSuite(s);
           }
         }
         if( 9 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_09 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_034 WaitingBvcBlockAck->Blocked");
            printf("(6). ");
            printf("\nTC_067 Blocked->WaitingBvcResetAck");
            printf("(7). ");
            printf("\nTC_017 WaitingBvcResetAck->GbDown");
            printf("(8). ");
            printf("\nTC_045 GbDown->WaitingBvcUnprovisionAck");
            printf("(9). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc9 = tcase_create("core");
               tcase_add_test(tc9,TC_001);
               tcase_add_test(tc9,TC_002);
               tcase_add_test(tc9,TC_020);
               tcase_add_test(tc9,TC_013);
               tcase_add_test(tc9,TC_034);
               tcase_add_test(tc9,TC_067);
               tcase_add_test(tc9,TC_017);
               tcase_add_test(tc9,TC_045);
               tcase_add_test(tc9,TC_074);
               suite_add_tcase(s,tc9);
               RunTestSuite(s);
           }
         }
         if( 10 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_010 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_036 WaitingBvcBlockAck->Blocked");
            printf("(6). ");
            printf("\nTC_063 Blocked->GbDown");
            printf("(7). ");
            printf("\nTC_044 GbDown->WaitingBvcResetAck");
            printf("(8). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(9). ");
            printf("\nTC_014 PSAllowed->Enabled");
            printf("(10). ");
            printf("\nTC_082 Enabled->WaitingBvcBlockAck");
            printf("(11). ");
            printf("\nTC_031 WaitingBvcBlockAck->WaitingBvcResetAck");
            printf("(12). ");
            printf("\nTC_023 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(13). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(14). ");
            printf("\nTC_015 PSAllowed->Enabled");
            printf("(15). ");
            printf("\nTC_076 Enabled->GbDown");
            printf("(16). ");
            printf("\nTC_045 GbDown->WaitingBvcUnprovisionAck");
            printf("(17). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc10 = tcase_create("core");
               tcase_add_test(tc10,TC_001);
               tcase_add_test(tc10,TC_002);
               tcase_add_test(tc10,TC_020);
               tcase_add_test(tc10,TC_013);
               tcase_add_test(tc10,TC_036);
               tcase_add_test(tc10,TC_063);
               tcase_add_test(tc10,TC_044);
               tcase_add_test(tc10,TC_019);
               tcase_add_test(tc10,TC_014);
               tcase_add_test(tc10,TC_082);
               tcase_add_test(tc10,TC_031);
               tcase_add_test(tc10,TC_023);
               tcase_add_test(tc10,TC_019);
               tcase_add_test(tc10,TC_015);
               tcase_add_test(tc10,TC_076);
               tcase_add_test(tc10,TC_045);
               tcase_add_test(tc10,TC_074);
               suite_add_tcase(s,tc10);
               RunTestSuite(s);
           }
         }
         if( 11 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_011 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_005 WaitingBvcProvisioningAck->WaitingBvcProvisioningAck");
            printf("(3). ");
            printf("\nTC_006 WaitingBvcProvisioningAck->WaitingBvcProvisioningAck");
            printf("(4). ");
            printf("\nTC_007 WaitingBvcProvisioningAck->WaitingBvcProvisioningAck");
            printf("(5). ");
            printf("\nTC_008 WaitingBvcProvisioningAck->WaitingBvcProvisioningAck");
            printf("(6). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(7). ");
            printf("\nTC_016 WaitingBvcResetAck->WaitingBvcBlockAck");
            printf("(8). ");
            printf("\nTC_027 WaitingBvcBlockAck->GbDown");
            printf("(9). ");
            printf("\nTC_047 GbDown->WaitingBvcResetAck");
            printf("(10). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(11). ");
            printf("\nTC_012 PSAllowed->Enabled");
            printf("(12). ");
            printf("\nTC_093 Enabled->Enabled");
            printf("(13). ");
            printf("\nTC_092 Enabled->Enabled");
            printf("(14). ");
            printf("\nTC_088 Enabled->Enabled");
            printf("(15). ");
            printf("\nTC_100 Enabled->Enabled");
            printf("(16). ");
            printf("\nTC_076 Enabled->GbDown");
            printf("(17). ");
            printf("\nTC_045 GbDown->WaitingBvcUnprovisionAck");
            printf("(18). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc11 = tcase_create("core");
               tcase_add_test(tc11,TC_001);
               tcase_add_test(tc11,TC_005);
               tcase_add_test(tc11,TC_006);
               tcase_add_test(tc11,TC_007);
               tcase_add_test(tc11,TC_008);
               tcase_add_test(tc11,TC_002);
               tcase_add_test(tc11,TC_016);
               tcase_add_test(tc11,TC_027);
               tcase_add_test(tc11,TC_047);
               tcase_add_test(tc11,TC_019);
               tcase_add_test(tc11,TC_012);
               tcase_add_test(tc11,TC_093);
               tcase_add_test(tc11,TC_092);
               tcase_add_test(tc11,TC_088);
               tcase_add_test(tc11,TC_100);
               tcase_add_test(tc11,TC_076);
               tcase_add_test(tc11,TC_045);
               tcase_add_test(tc11,TC_074);
               suite_add_tcase(s,tc11);
               RunTestSuite(s);
           }
         }
         if( 12 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_012 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_021 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(4). ");
            printf("\nTC_023 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(5). ");
            printf("\nTC_024 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(6). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(7). ");
            printf("\nTC_029 WaitingBvcBlockAck->WaitingBvcBlockAck");
            printf("(8). ");
            printf("\nTC_030 WaitingBvcBlockAck->WaitingBvcBlockAck");
            printf("(9). ");
            printf("\nTC_029 WaitingBvcBlockAck->WaitingBvcBlockAck");
            printf("(10). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(11). ");
            printf("\nTC_099 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(12). ");
            printf("\nTC_058 WaitingBvcUnblockAck->Enabled");
            printf("(13). ");
            printf("\nTC_076 Enabled->GbDown");
            printf("(14). ");
            printf("\nTC_047 GbDown->WaitingBvcResetAck");
            printf("(15). ");
            printf("\nTC_022 WaitingBvcResetAck->WaitingBvcUnprovisionAck");
            printf("(16). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc12 = tcase_create("core");
               tcase_add_test(tc12,TC_001);
               tcase_add_test(tc12,TC_002);
               tcase_add_test(tc12,TC_021);
               tcase_add_test(tc12,TC_023);
               tcase_add_test(tc12,TC_024);
               tcase_add_test(tc12,TC_013);
               tcase_add_test(tc12,TC_029);
               tcase_add_test(tc12,TC_030);
               tcase_add_test(tc12,TC_029);
               tcase_add_test(tc12,TC_019);
               tcase_add_test(tc12,TC_099);
               tcase_add_test(tc12,TC_058);
               tcase_add_test(tc12,TC_076);
               tcase_add_test(tc12,TC_047);
               tcase_add_test(tc12,TC_022);
               tcase_add_test(tc12,TC_074);
               suite_add_tcase(s,tc12);
               RunTestSuite(s);
           }
         }
         if( 13 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_013 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(4). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(5). ");
            printf("\nTC_021 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(6). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(7). ");
            printf("\nTC_031 WaitingBvcBlockAck->WaitingBvcResetAck");
            printf("(8). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(9). ");
            printf("\nTC_030 WaitingBvcBlockAck->PSNotAllowed");
            printf("(10). ");
            printf("\nTC_034 WaitingBvcBlockAck->Blocked");
            printf("(11). ");
            printf("\nTC_067 Blocked->WaitingBvcResetAck");
            printf("(12). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(13). ");
            printf("\nTC_036 WaitingBvcBlockAck->Blocked");
            printf("(14). ");
            printf("\nTC_065 Blocked->PSAllowed");
            printf("(15). ");
            printf("\nTC_048 WaitingBvcUnblockAck->WaitingBvcResetAck");
            printf("(16). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(17). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(18). ");
            printf("\nTC_036 WaitingBvcBlockAck->Blocked");
            printf("(19). ");
            printf("\nTC_064 Blocked->Blocked");
            printf("(20). ");
            printf("\nTC_066 Blocked->PSNotAllowed");
            printf("(21). ");
            printf("\nTC_068 Blocked->WaitingBvcUnprovisionAck");
            printf("(22). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc13 = tcase_create("core");
               tcase_add_test(tc13,TC_001);
               tcase_add_test(tc13,TC_002);
               tcase_add_test(tc13,TC_019);
               tcase_add_test(tc13,TC_020);
               tcase_add_test(tc13,TC_021);
               tcase_add_test(tc13,TC_013);
               tcase_add_test(tc13,TC_031);
               tcase_add_test(tc13,TC_013);
               tcase_add_test(tc13,TC_030);
               tcase_add_test(tc13,TC_034);
               tcase_add_test(tc13,TC_067);
               tcase_add_test(tc13,TC_013);
               tcase_add_test(tc13,TC_036);
               tcase_add_test(tc13,TC_065);
               tcase_add_test(tc13,TC_048);
               tcase_add_test(tc13,TC_020);
               tcase_add_test(tc13,TC_013);
               tcase_add_test(tc13,TC_036);
               tcase_add_test(tc13,TC_064);
               tcase_add_test(tc13,TC_066);
               tcase_add_test(tc13,TC_068);
               tcase_add_test(tc13,TC_074);
               suite_add_tcase(s,tc13);
               RunTestSuite(s);
           }
         }
         if( 14 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_014 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(4). ");
            printf("\nTC_016 PSNotAllowed->WaitingBvcBlockAck");
            printf("(5). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(6). ");
            printf("\nTC_037 PSAllowed->Enabled");
            printf("(7). ");
            printf("\nTC_091 Enabled->WaitingBvcResetAck");
            printf("(8). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(9). ");
            printf("\nTC_013 PSNotAllowed->WaitingBvcBlockAck");
            printf("(10). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(11). ");
            printf("\nTC_035 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(12). ");
            printf("\nTC_051 WaitingBvcUnblockAck->PSAllowed");
            printf("(13). ");
            printf("\nTC_052 WaitingBvcUnblockAck->PSNotAllowed");
            printf("(14). ");
            printf("\nTC_055 WaitingBvcUnblockAck->WaitingBvcUnblockAck");
            printf("(15). ");
            printf("\nTC_056 WaitingBvcUnblockAck->WaitingBvcUnblockAck");
            printf("(16). ");
            printf("\nTC_050 WaitingBvcUnblockAck->WaitingBvcUnblockAck");
            printf("(17). ");
            printf("\nTC_058 WaitingBvcUnblockAck->Enabled");
            printf("(18). ");
            printf("\nTC_086 Enabled->WaitingBvcUnprovisionAck");
            printf("(19). ");
            printf("\nTC_097 WaitingBvcUnprovisionAck->WaitingBvcUnprovisionAck");
            printf("(20). ");
            printf("\nTC_098 WaitingBvcUnprovisionAck->WaitingBvcUnprovisionAck");
            printf("(21). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc14 = tcase_create("core");
               tcase_add_test(tc14,TC_001);
               tcase_add_test(tc14,TC_002);
               tcase_add_test(tc14,TC_020);
               tcase_add_test(tc14,TC_016);
               tcase_add_test(tc14,TC_029);
               tcase_add_test(tc14,TC_037);
               tcase_add_test(tc14,TC_091);
               tcase_add_test(tc14,TC_020);
               tcase_add_test(tc14,TC_013);
               tcase_add_test(tc14,TC_029);
               tcase_add_test(tc14,TC_035);
               tcase_add_test(tc14,TC_051);
               tcase_add_test(tc14,TC_052);
               tcase_add_test(tc14,TC_055);
               tcase_add_test(tc14,TC_056);
               tcase_add_test(tc14,TC_050);
               tcase_add_test(tc14,TC_058);
               tcase_add_test(tc14,TC_086);
               tcase_add_test(tc14,TC_097);
               tcase_add_test(tc14,TC_098);
               tcase_add_test(tc14,TC_074);
               suite_add_tcase(s,tc14);
               RunTestSuite(s);
           }
         }
         if( 15 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_015 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_010 WaitingBvcProvisioningAck->WaitingBvcProvisioningAck");
            printf("(3). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(4). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(5). ");
            printf("\nTC_018 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(6). ");
            printf("\nTC_012 WaitingBvcResetAck->Enabled");
            printf("(7). ");
            printf("\nTC_080 Enabled->PSAllowed");
            printf("(8). ");
            printf("\nTC_080 Enabled->PSAllowed");
            printf("(9). ");
            printf("\nTC_081 Enabled->PSNotAllowed");
            printf("(10). ");
            printf("\nTC_076 Enabled->GbDown");
            printf("(11). ");
            printf("\nTC_040 GbDown->GbDown");
            printf("(12). ");
            printf("\nTC_041 GbDown->GbDown");
            printf("(13). ");
            printf("\nTC_043 GbDown->GbDown");
            printf("(14). ");
            printf("\nTC_042 GbDown->GbDown");
            printf("(15). ");
            printf("\nTC_046 GbDown->GbDown");
            printf("(16). ");
            printf("\nTC_045 GbDown->WaitingBvcUnprovisionAck");
            printf("(17). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
               TCase *tc15 = tcase_create("core");
               tcase_add_test(tc15,TC_001);
               tcase_add_test(tc15,TC_010);
               tcase_add_test(tc15,TC_002);
               tcase_add_test(tc15,TC_019);
               tcase_add_test(tc15,TC_018);
               tcase_add_test(tc15,TC_012);
               tcase_add_test(tc15,TC_080);
               tcase_add_test(tc15,TC_080);
               tcase_add_test(tc15,TC_081);
               tcase_add_test(tc15,TC_076);
               tcase_add_test(tc15,TC_040);
               tcase_add_test(tc15,TC_041);
               tcase_add_test(tc15,TC_043);
               tcase_add_test(tc15,TC_042);
               tcase_add_test(tc15,TC_046);
               tcase_add_test(tc15,TC_045);
               tcase_add_test(tc15,TC_074);
               suite_add_tcase(s,tc15);
               RunTestSuite(s);
           }
         }
         if( 16 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_016 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_095 WaitingBvcProvisioningAck->GbDown");
            printf("(3). ");
            printf("\nTC_044 GbDown->WaitingBvcResetAck");
            printf("(4). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(5). ");
            printf("\nTC_014 WaitingBvcResetAck->Enabled");
            printf("(6). ");
            printf("\nTC_100 Enabled->Enabled");
            printf("(7). ");
            printf("\nTC_091 Enabled->WaitingBvcResetAck");
            printf("(8). ");
            printf("\nTC_014 WaitingBvcResetAck->Enabled");
            printf("(9). ");
            printf("\nTC_077 Enabled->GbDown");
            printf("(10). ");
            printf("\nTC_047 GbDown->WaitingBvcResetAck");
            printf("(11). ");
            printf("\nTC_023 WaitingBvcResetAck->WaitingBvcResetAck");
            printf("(12). ");
            printf("\nTC_015 WaitingBvcResetAck->Enabled");
            printf("(13). ");
            printf("\nTC_084 Enabled->WaitingBvcResetAck");
            printf("(14). ");
            printf("\nTC_015 WaitingBvcResetAck->Enabled");
            printf("(15). ");
            printf("\nTC_083 Enabled->WaitingBvcBlockAck");
            printf("(16). ");
            printf("\nTC_033 WaitingBvcBlockAck->WaitingBvcBlockAck");
            printf("(17). ");
            printf("\nTC_028 WaitingBvcBlockAck->WaitingBvcBlockAck");
            printf("(18). ");
            printf("\nTC_026 WaitingBvcBlockAck->WaitingBvcResetAck");
            printf("(19). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(20). ");
            printf("\nTC_016 PSNotAllowed->WaitingBvcBlockAck");
            printf("(21). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(22). ");
            printf("\nTC_038 PSAllowed->Enabled");
            printf("(23). ");
            printf("\nTC_086 Enabled->WaitingBvcUnprovisionAck");
            printf("(24). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
	       gbIfTableRef.gbIfIndex = 1;
	       gbIfTableRef.oprState = 0;
	       gbIfTableRef.cblNegotiated = 1;
               iResult = updateGbIfStatusTable(&gbIfTableRef);
	       if(iResult == DBLIB_SUCCESS)
	       {
                  printf("\nDB call for GbIfStatus table successful\n");
	          TCase *tc16 = tcase_create("core");
                  tcase_add_test(tc16,TC_001);
                  tcase_add_test(tc16,TC_095);
                  tcase_add_test(tc16,TC_044);
                  tcase_add_test(tc16,TC_019);
                  tcase_add_test(tc16,TC_014);
                  tcase_add_test(tc16,TC_090);
                  tcase_add_test(tc16,TC_091);
                  tcase_add_test(tc16,TC_014);
                  tcase_add_test(tc16,TC_077);
                  tcase_add_test(tc16,TC_047);
                  tcase_add_test(tc16,TC_023);
                  tcase_add_test(tc16,TC_015);
                  tcase_add_test(tc16,TC_084);
                  tcase_add_test(tc16,TC_015);
                  tcase_add_test(tc16,TC_083);
                  tcase_add_test(tc16,TC_033);
                  tcase_add_test(tc16,TC_028);
                  tcase_add_test(tc16,TC_026);
                  tcase_add_test(tc16,TC_020);
                  tcase_add_test(tc16,TC_016);
                  tcase_add_test(tc16,TC_029);
                  tcase_add_test(tc16,TC_038);
                  tcase_add_test(tc16,TC_086);
                  tcase_add_test(tc16,TC_074);
                  suite_add_tcase(s,tc16);
                  RunTestSuite(s);
	       }
	       else 
	       {
                  printf("\n Failed: Db call for GbIfStatus Table\n"); 
	       }
           }
         }
         if( 17 == iTSChoice)  
         {
            system("clear");
            printf("\n 0 : Previous Menu");
            printf("\n TS_017 will run following TestCases:");
            printf("(1). ");
            printf("\nTC_001 CellIdle->WaitingBvcProvisioningAck");
            printf("(2). ");
            printf("\nTC_002 WaitingBvcProvisioningAck->WaitingBvcResetAck");
            printf("(3). ");
            printf("\nTC_019 WaitingBvcResetAck->PSAllowed");
            printf("(4). ");
            printf("\nTC_014 WaitingBvcResetAck->Enabled");
            printf("(5). ");
            printf("\nTC_085 Enabled->WaitingBvcResetAck");
            printf("(6). ");
            printf("\nTC_014 WaitingBvcResetAck->Enabled");
            printf("(7). ");
            printf("\nTC_078 Enabled->Enabled");
            printf("(8). ");
            printf("\nTC_087 Enabled->Enabled");
            printf("(9). ");
            printf("\nTC_079 Enabled->Enabled");
            printf("(10). ");
            printf("\nTC_085 Enabled->WaitingBvcResetAck");
            printf("(11). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(12). ");
            printf("\nTC_016 PSNotAllowed->WaitingBvcBlockAck");
            printf("(13). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(14). ");
            printf("\nTC_099 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(15). ");
            printf("\nTC_061 WaitingBvcUnblockAck->Enabled");
            printf("(16). ");
            printf("\nTC_083 Enabled->WaitingBvcBlockAck");
            printf("(17). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(18). ");
            printf("\nTC_035 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(19). ");
            printf("\nTC_052 WaitingBvcUnblockAck->PSNotAllowed");
            printf("(20). ");
            printf("\nTC_062 WaitingBvcUnblockAck->WaitingBvcBlockAck");
            printf("(21). ");
            printf("\nTC_036 WaitingBvcBlockAck->Blocked");
            printf("(22). ");
            printf("\nTC_069 Blocked->Blocked");
            printf("(23). ");
            printf("\nTC_072 Blocked->WaitingBvcBlockAck");
            printf("(24). ");
            printf("\nTC_036 WaitingBvcBlockAck->Blocked");
            printf("(25). ");
            printf("\nTC_073 Blocked->WaitingBvcResetAck");
            printf("(26). ");
            printf("\nTC_016 PSNotAllowed->WaitingBvcBlockAck");
            printf("(27). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(28). ");
            printf("\nTC_035 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(29). ");
            printf("\nTC_048 WaitingBvcUnblockAck->WaitingBvcResetAck");
            printf("(30). ");
            printf("\nTC_020 WaitingBvcResetAck->PSNotAllowed");
            printf("(31). ");
            printf("\nTC_016 PSNotAllowed->WaitingBvcBlockAck");
            printf("(32). ");
            printf("\nTC_029 WaitingBvcBlockAck->PSAllowed");
            printf("(33). ");
            printf("\nTC_035 WaitingBvcBlockAck->WaitingBvcUnblockAck");
            printf("(34). ");
            printf("\nTC_049 WaitingBvcUnblockAck->GbDown");
            printf("(35). ");
            printf("\nTC_045 GbDown->WaitingBvcUnprovosionAck");
            printf("(36). ");
            printf("\nTC_074 WaitingBvcUnprovisionAck->CellIdle");
            printf("\n 1: Run");
            printf("\nPlease enter your choice : ");
            scanf("%d",&iTSSChoice); 
            if( 1 == iTSSChoice)  
            {
	       gbIfTableRef.gbIfIndex = 1;
	       gbIfTableRef.oprState = 1;
	       gbIfTableRef.cblNegotiated = 1;
               iResult = updateGbIfStatusTable(&gbIfTableRef);
	       if(iResult == DBLIB_SUCCESS)
	       {
	          printf("\n Db Call for GbIf Status table successful");	       
                  TCase *tc17 = tcase_create("core");
                  tcase_add_test(tc17,TC_001);
                  tcase_add_test(tc17,TC_002);
                  tcase_add_test(tc17,TC_019);
                  tcase_add_test(tc17,TC_014);
                  tcase_add_test(tc17,TC_085);
                  tcase_add_test(tc17,TC_014);
                  tcase_add_test(tc17,TC_078);
                  tcase_add_test(tc17,TC_087);
                  tcase_add_test(tc17,TC_079);
                  tcase_add_test(tc17,TC_085);
                  tcase_add_test(tc17,TC_020);
                  tcase_add_test(tc17,TC_016);
                  tcase_add_test(tc17,TC_029);
                  tcase_add_test(tc17,TC_099);
                  tcase_add_test(tc17,TC_061);
                  tcase_add_test(tc17,TC_083);
                  tcase_add_test(tc17,TC_029);
                  tcase_add_test(tc17,TC_035);
                  tcase_add_test(tc17,TC_052);
                  tcase_add_test(tc17,TC_062);
                  tcase_add_test(tc17,TC_036);
                  tcase_add_test(tc17,TC_069);
                  tcase_add_test(tc17,TC_072);
                  tcase_add_test(tc17,TC_036);
                  tcase_add_test(tc17,TC_073);
                  tcase_add_test(tc17,TC_016);
                  tcase_add_test(tc17,TC_029);
                  tcase_add_test(tc17,TC_035);
                  tcase_add_test(tc17,TC_048);
                  tcase_add_test(tc17,TC_020);
                  tcase_add_test(tc17,TC_016);
                  tcase_add_test(tc17,TC_029);
                  tcase_add_test(tc17,TC_035);
                  tcase_add_test(tc17,TC_049);
                  tcase_add_test(tc17,TC_045);
                  tcase_add_test(tc17,TC_074);
                  suite_add_tcase(s,tc17);
                  RunTestSuite(s);
	       }
	       else
	       {
                  printf("\nFailed Db Call for GbIf Status Table\n");
	       }
           }
         }
         if( 100 == iTSChoice)  
         {
            TCase *tc1 = tcase_create("core");
            tcase_add_test(tc1,TC_001);
            tcase_add_test(tc1,TC_009);
            tcase_add_test(tc1,TC_003);
            tcase_add_test(tc1,TC_074);
            suite_add_tcase(s,tc1);
            TCase *tc2 = tcase_create("core");
            tcase_add_test(tc2,TC_001);
            tcase_add_test(tc2,TC_002);
            tcase_add_test(tc2,TC_022);
            tcase_add_test(tc2,TC_074);
            suite_add_tcase(s,tc2);
            TCase *tc3 = tcase_create("core");
            tcase_add_test(tc3,TC_001);
            tcase_add_test(tc3,TC_002);
            tcase_add_test(tc3,TC_017);
            tcase_add_test(tc3,TC_045);
            tcase_add_test(tc3,TC_074);
            suite_add_tcase(s,tc3);
            TCase *tc4 = tcase_create("core");
            tcase_add_test(tc4,TC_001);
            tcase_add_test(tc4,TC_002);
            tcase_add_test(tc4,TC_019);
            tcase_add_test(tc4,TC_011);
            tcase_add_test(tc4,TC_086);
            tcase_add_test(tc4,TC_074);
            suite_add_tcase(s,tc4);
            TCase *tc5 = tcase_create("core");
            tcase_add_test(tc5,TC_001);
            tcase_add_test(tc5,TC_002);
            tcase_add_test(tc5,TC_020);
            tcase_add_test(tc5,TC_013);
            tcase_add_test(tc5,TC_032);
            tcase_add_test(tc5,TC_074);
            suite_add_tcase(s,tc5);
            TCase *tc6 = tcase_create("core");
            tcase_add_test(tc6,TC_001);
            tcase_add_test(tc6,TC_002);
            tcase_add_test(tc6,TC_020);
            tcase_add_test(tc6,TC_013);
            tcase_add_test(tc6,TC_029);
            tcase_add_test(tc6,TC_035);
            tcase_add_test(tc6,TC_054);
            tcase_add_test(tc6,TC_074);
            suite_add_tcase(s,tc6);
            TCase *tc7 = tcase_create("core");
            tcase_add_test(tc7,TC_001);
            tcase_add_test(tc7,TC_002);
            tcase_add_test(tc7,TC_020);
            tcase_add_test(tc7,TC_013);
            tcase_add_test(tc7,TC_034);
            tcase_add_test(tc7,TC_068);
            tcase_add_test(tc7,TC_074);
            suite_add_tcase(s,tc7);
            TCase *tc8 = tcase_create("core");
            tcase_add_test(tc8,TC_001);
            tcase_add_test(tc8,TC_002);
            tcase_add_test(tc8,TC_020);
            tcase_add_test(tc8,TC_013);
            tcase_add_test(tc8,TC_034);
            tcase_add_test(tc8,TC_067);
            tcase_add_test(tc8,TC_022);
            tcase_add_test(tc8,TC_074);
            suite_add_tcase(s,tc8);
            TCase *tc9 = tcase_create("core");
            tcase_add_test(tc9,TC_001);
            tcase_add_test(tc9,TC_002);
            tcase_add_test(tc9,TC_020);
            tcase_add_test(tc9,TC_013);
            tcase_add_test(tc9,TC_034);
            tcase_add_test(tc9,TC_067);
            tcase_add_test(tc9,TC_017);
            tcase_add_test(tc9,TC_045);
            tcase_add_test(tc9,TC_074);
            suite_add_tcase(s,tc9);
            TCase *tc10 = tcase_create("core");
            tcase_add_test(tc10,TC_001);
            tcase_add_test(tc10,TC_002);
            tcase_add_test(tc10,TC_020);
            tcase_add_test(tc10,TC_013);
            tcase_add_test(tc10,TC_036);
            tcase_add_test(tc10,TC_063);
            tcase_add_test(tc10,TC_044);
            tcase_add_test(tc10,TC_019);
            tcase_add_test(tc10,TC_014);
            tcase_add_test(tc10,TC_082);
            tcase_add_test(tc10,TC_031);
            tcase_add_test(tc10,TC_023);
            tcase_add_test(tc10,TC_019);
            tcase_add_test(tc10,TC_015);
            tcase_add_test(tc10,TC_076);
            tcase_add_test(tc10,TC_045);
            tcase_add_test(tc10,TC_074);
            suite_add_tcase(s,tc10);
            TCase *tc11 = tcase_create("core");
            tcase_add_test(tc11,TC_001);
            tcase_add_test(tc11,TC_005);
            tcase_add_test(tc11,TC_006);
            tcase_add_test(tc11,TC_007);
            tcase_add_test(tc11,TC_008);
            tcase_add_test(tc11,TC_002);
            tcase_add_test(tc11,TC_016);
            tcase_add_test(tc11,TC_027);
            tcase_add_test(tc11,TC_047);
            tcase_add_test(tc11,TC_019);
            tcase_add_test(tc11,TC_012);
            tcase_add_test(tc11,TC_093);
            tcase_add_test(tc11,TC_092);
            tcase_add_test(tc11,TC_088);
            tcase_add_test(tc11,TC_100);
            tcase_add_test(tc11,TC_076);
            tcase_add_test(tc11,TC_045);
            tcase_add_test(tc11,TC_074);
            suite_add_tcase(s,tc11);
            TCase *tc12 = tcase_create("core");
            tcase_add_test(tc12,TC_001);
            tcase_add_test(tc12,TC_002);
            tcase_add_test(tc12,TC_021);
            tcase_add_test(tc12,TC_023);
            tcase_add_test(tc12,TC_024);
            tcase_add_test(tc12,TC_013);
            tcase_add_test(tc12,TC_029);
            tcase_add_test(tc12,TC_030);
            tcase_add_test(tc12,TC_029);
            tcase_add_test(tc12,TC_019);
            tcase_add_test(tc12,TC_099);
            tcase_add_test(tc12,TC_058);
            tcase_add_test(tc12,TC_076);
            tcase_add_test(tc12,TC_047);
            tcase_add_test(tc12,TC_022);
            tcase_add_test(tc12,TC_074);
            suite_add_tcase(s,tc12);
            TCase *tc13 = tcase_create("core");
            tcase_add_test(tc13,TC_001);
            tcase_add_test(tc13,TC_002);
            tcase_add_test(tc13,TC_019);
            tcase_add_test(tc13,TC_020);
            tcase_add_test(tc13,TC_021);
            tcase_add_test(tc13,TC_013);
            tcase_add_test(tc13,TC_031);
            tcase_add_test(tc13,TC_013);
            tcase_add_test(tc13,TC_030);
            tcase_add_test(tc13,TC_034);
            tcase_add_test(tc13,TC_067);
            tcase_add_test(tc13,TC_013);
            tcase_add_test(tc13,TC_036);
            tcase_add_test(tc13,TC_065);
            tcase_add_test(tc13,TC_048);
            tcase_add_test(tc13,TC_020);
            tcase_add_test(tc13,TC_013);
            tcase_add_test(tc13,TC_036);
            tcase_add_test(tc13,TC_064);
            tcase_add_test(tc13,TC_066);
            tcase_add_test(tc13,TC_068);
            tcase_add_test(tc13,TC_074);
            suite_add_tcase(s,tc13);
            TCase *tc14 = tcase_create("core");
            tcase_add_test(tc14,TC_001);
            tcase_add_test(tc14,TC_002);
            tcase_add_test(tc14,TC_020);
            tcase_add_test(tc14,TC_016);
            tcase_add_test(tc14,TC_029);
            tcase_add_test(tc14,TC_037);
            tcase_add_test(tc14,TC_091);
            tcase_add_test(tc14,TC_020);
            tcase_add_test(tc14,TC_013);
            tcase_add_test(tc14,TC_029);
            tcase_add_test(tc14,TC_035);
            tcase_add_test(tc14,TC_051);
            tcase_add_test(tc14,TC_052);
            tcase_add_test(tc14,TC_055);
            tcase_add_test(tc14,TC_056);
            tcase_add_test(tc14,TC_050);
            tcase_add_test(tc14,TC_058);
            tcase_add_test(tc14,TC_086);
            tcase_add_test(tc14,TC_097);
            tcase_add_test(tc14,TC_098);
            tcase_add_test(tc14,TC_074);
            suite_add_tcase(s,tc14);
            TCase *tc15 = tcase_create("core");
            tcase_add_test(tc15,TC_001);
            tcase_add_test(tc15,TC_010);
            tcase_add_test(tc15,TC_002);
            tcase_add_test(tc15,TC_019);
            tcase_add_test(tc15,TC_018);
            tcase_add_test(tc15,TC_012);
            tcase_add_test(tc15,TC_080);
            tcase_add_test(tc15,TC_080);
            tcase_add_test(tc15,TC_081);
            tcase_add_test(tc15,TC_076);
            tcase_add_test(tc15,TC_040);
            tcase_add_test(tc15,TC_041);
            tcase_add_test(tc15,TC_043);
            tcase_add_test(tc15,TC_042);
            tcase_add_test(tc15,TC_046);
            tcase_add_test(tc15,TC_045);
            tcase_add_test(tc15,TC_074);
            suite_add_tcase(s,tc15);
            sleep(5);
            TCase *tc16 = tcase_create("core");
            sleep(2);
            gbIfTableRef.gbIfIndex = 1;
            gbIfTableRef.oprState = 0;
            gbIfTableRef.cblNegotiated = 1;
            iResult = updateGbIfStatusTable(&gbIfTableRef);
            if(iResult == DBLIB_SUCCESS)
            {
               printf("\n Db Call for GbIf Status table successful");
               tcase_add_test(tc16,TC_001);
               tcase_add_test(tc16,TC_004);
               tcase_add_test(tc16,TC_095);
               tcase_add_test(tc16,TC_044);
               tcase_add_test(tc16,TC_019);
               tcase_add_test(tc16,TC_014);
               tcase_add_test(tc16,TC_100);
               tcase_add_test(tc16,TC_091);
               tcase_add_test(tc16,TC_014);
               tcase_add_test(tc16,TC_077);
               tcase_add_test(tc16,TC_047);
               tcase_add_test(tc16,TC_023);
               tcase_add_test(tc16,TC_015);
               tcase_add_test(tc16,TC_084);
               tcase_add_test(tc16,TC_015);
               tcase_add_test(tc16,TC_083);
               tcase_add_test(tc16,TC_033);
               tcase_add_test(tc16,TC_028);
               tcase_add_test(tc16,TC_026);
               tcase_add_test(tc16,TC_020);
               tcase_add_test(tc16,TC_016);
               tcase_add_test(tc16,TC_029);
               tcase_add_test(tc16,TC_038);
               tcase_add_test(tc16,TC_086);
               tcase_add_test(tc16,TC_074);
               suite_add_tcase(s,tc16);
            }
            else
            {
               printf("\n[ERROR] Db Call for GbIf Status table failed");
               exit(0);
            }
            TCase *tc17 = tcase_create("core");
            gbIfTableRef.gbIfIndex = 1;
            gbIfTableRef.oprState = 1;
            gbIfTableRef.cblNegotiated = 1;
            iResult = updateGbIfStatusTable(&gbIfTableRef);
            if(iResult == DBLIB_SUCCESS)
            {
               printf("\n Db Call for GbIf Status table successful");
            }
            else
            {
              printf("\n TC_002-Failed DbCall for GbIf Status table\n");
              exit(0);
            }

            tcase_add_test(tc17,TC_001);
            tcase_add_test(tc17,TC_002);
            tcase_add_test(tc17,TC_019);
            tcase_add_test(tc17,TC_014);
            tcase_add_test(tc17,TC_085);
            tcase_add_test(tc17,TC_014);
            tcase_add_test(tc17,TC_078);
            tcase_add_test(tc17,TC_087);
            tcase_add_test(tc17,TC_079);
            tcase_add_test(tc17,TC_085);
            tcase_add_test(tc17,TC_020);
            tcase_add_test(tc17,TC_016);
            tcase_add_test(tc17,TC_029);
            tcase_add_test(tc17,TC_099);
            tcase_add_test(tc17,TC_061);
            tcase_add_test(tc17,TC_083);
            tcase_add_test(tc17,TC_029);
            tcase_add_test(tc17,TC_035);
            tcase_add_test(tc17,TC_052);
            tcase_add_test(tc17,TC_062);
            tcase_add_test(tc17,TC_036);
            tcase_add_test(tc17,TC_069);
            tcase_add_test(tc17,TC_072);
            tcase_add_test(tc17,TC_036);
            tcase_add_test(tc17,TC_073);
            tcase_add_test(tc17,TC_016);
            tcase_add_test(tc17,TC_029);
            tcase_add_test(tc17,TC_035);
            tcase_add_test(tc17,TC_048);
            tcase_add_test(tc17,TC_020);
            tcase_add_test(tc17,TC_016);
            tcase_add_test(tc17,TC_029);
            tcase_add_test(tc17,TC_035);
            tcase_add_test(tc17,TC_049);
            tcase_add_test(tc17,TC_045);
            tcase_add_test(tc17,TC_074);
            suite_add_tcase(s,tc17);
            printf("Running all Test Suites...");
            RunTestSuite(s);
         }
        }while(iTSChoice != 0);
      }
 
   }while(iChoice!=0);
    printf("\nExiting...");
    system("clear");
}

