#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  9
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
 TC Name: TC_042

 TC Description: Block cnf received during NSVC Block procedure.
**************************************************************************/
START_TEST (TC_042)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcBlockCnf pssksNsNsvchNsvcBlockCnf;

  /*Receive Message Struct */
   pssksNsNsvchNsvcBlockCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchNsvcBlockCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchNsvcBlockCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchNsvcBlockCnf.sysHdr.src.inst = 0;
   pssksNsNsvchNsvcBlockCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchNsvcBlockCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchNsvcBlockCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchNsvcBlockCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchNsvcBlockCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchNsvcBlockCnf.sysHdr.msgType = PSSKS_NS_NSVCH_NSVC_BLOCK_CNF;
   pssksNsNsvchNsvcBlockCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchNsvcBlockCnf.sysHdr.priority = 0;
   pssksNsNsvchNsvcBlockCnf.bufLen = 0;
   pssksNsNsvchNsvcBlockCnf.trId = 0;
   pssksNsNsvchNsvcBlockCnf.apiId = 0;
   pssksNsNsvchNsvcBlockCnf.nsvci = 5;
   pssksNsNsvchNsvcBlockCnf.result = BSS_SUCCESS;
   pssksNsNsvchNsvcBlockCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcBlockCnf,sizeof(PssksNsNsvchNsvcBlockCnf));

   if(0 == flag)
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_043

 TC Description: Block Ind received during NSVC Block procedure.
**************************************************************************/
START_TEST (TC_043)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcBlockInd pssksNsNsvchNsvcBlockInd;

  /*Receive Message Struct */
   OamsNsvchFrNStopReq oamsNsvchFrNStopReq;
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
   OamsNsvchNsNsvcDown oamsNsvchNsNsvcDown;
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
   pssksNsNsvchNsvcBlockInd.blockCause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcBlockInd,sizeof(PssksNsNsvchNsvcBlockInd));

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
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_044

 TC Description: PSSKS_FR_NSVCH_N_DISC_IND received during NSVC Block procedure
**************************************************************************/
START_TEST (TC_044)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNDiscInd pssksFrNsvchNDiscInd;

  /*Receive Message Struct */
   OamsNsvchFrNStopReq oamsNsvchFrNStopReq;
   OamsNsvchCfgAlarmInd oamsNsvchCfgAlarmInd;
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
      test_result[3] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[3] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_045

 TC Description: StatusInd(Fr InActive) received during NSVC Block procedure
**************************************************************************/
START_TEST (TC_045)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNStatusInd pssksFrNsvchNStatusInd;

  /*Receive Message Struct */
   OamsNsvchFrNStopReq oamsNsvchFrNStopReq;
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
      test_result[4] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[4] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_046

 TC Description: NSVC Down cnf is received 
**************************************************************************/
START_TEST (TC_046)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchNsvcDownCnf pssksNsNsvchNsvcDownCnf;

  /*Receive Message Struct */
   OamsNsvchNsRemNsvcNseiGrp oamsNsvchNsRemNsvcNseiGrp;
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
 TC Name: TC_047

 TC Description: StatusInd(Fr InActive) received when when NSVC Lock procedure is going on
**************************************************************************/
START_TEST (TC_047)
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
      test_result[6] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[6] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_048

 TC Description: StatusInd(Fr Active) received when when NSVC Lock procedure is going on
**************************************************************************/
START_TEST (TC_048)
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
 TC Name: TC_049

 TC Description: FR_CONN_IND received when when NSVC Lock procedure is going on
**************************************************************************/
START_TEST (TC_049)
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
   pssksFrNsvchNConnInd.dlci = 5;
   pssksFrNsvchNConnInd.dataOffset = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksFrNsvchNConnInd,sizeof(PssksFrNsvchNConnInd));

   if(0 == flag)
      test_result[8] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[8] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_050

 TC Description: FR_DISC_IND received when when NSVC Lock procedure is going on
**************************************************************************/
START_TEST (TC_050)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksFrNsvchNDiscInd pssksFrNsvchNDiscInd;

  /*Receive Message Struct */
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

   if(0 == flag)
      test_result[9] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[9] = 1;    /* 1 for pass*/

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
        printf("\n1. Run TC_042");
        printf("\n2. Run TC_043");
        printf("\n3. Run TC_044");
        printf("\n4. Run TC_045");
        printf("\n5. Run TC_046");
        printf("\n6. Run TC_047");
        printf("\n7. Run TC_048");
        printf("\n8. Run TC_049");
        printf("\n9. Run TC_050");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_042);
           printf("\nRunning Test Case TC_042"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 2 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_043);
           printf("\nRunning Test Case TC_043"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 3 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_044);
           printf("\nRunning Test Case TC_044"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 4 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_045);
           printf("\nRunning Test Case TC_045"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 5 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_046);
           printf("\nRunning Test Case TC_046"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 6 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_047);
           printf("\nRunning Test Case TC_047"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 7 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_048);
           printf("\nRunning Test Case TC_048"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 8 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_049);
           printf("\nRunning Test Case TC_049"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 9 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_050);
           printf("\nRunning Test Case TC_050"); 
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

