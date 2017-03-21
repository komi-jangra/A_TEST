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
 TC Name: TC_059

 TC Description: status Ind(Fr Inactive) received in UnlockedBlocked state
**************************************************************************/
START_TEST (TC_059)
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
      test_result[1] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[1] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_060

 TC Description: Disc Ind received in state UnlockedBlocked
**************************************************************************/
START_TEST (TC_060)
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
      test_result[2] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[2] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_061

 TC Description: Reset Ind received in state UnlockedBlocked
**************************************************************************/
START_TEST (TC_061)
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
      test_result[3] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[3] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_062

 TC Description: Unblock Ind received in state UnlockedBlocked
**************************************************************************/
START_TEST (TC_062)
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

  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchNsvcUnblockInd,sizeof(PssksNsNsvchNsvcUnblockInd));

   if(0 == flag)
      test_result[4] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[4] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_063

 TC Description: Lock Req received in state UnlockedBlocked
**************************************************************************/
START_TEST (TC_063)
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
      test_result[5] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[5] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_064

 TC Description: get from NSVCTable failed while Unlock prodecure
**************************************************************************/
START_TEST (TC_064)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchUnlockReq oamsCfgNsvchUnlockReq;

  /*Receive Message Struct */
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockResp;
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
      test_result[6] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[6] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_065

 TC Description: get from frLinkTable failed while Unlock prodecure
**************************************************************************/
START_TEST (TC_065)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchUnlockReq oamsCfgNsvchUnlockReq;

  /*Receive Message Struct */
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockResp;
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
      test_result[7] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[7] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_066

 TC Description: get from gbInterfaceTable failed while Unlock prodecure
**************************************************************************/
START_TEST (TC_066)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgNsvchUnlockReq oamsCfgNsvchUnlockReq;

  /*Receive Message Struct */
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockResp;
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
      test_result[8] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[8] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_067

 TC Description: Unprov NSVC received in WaitForNSVCUnprovcnf
**************************************************************************/
START_TEST (TC_067)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   PssksNsNsvchUnprovNsvcCnf pssksNsNsvchUnprovNsvcCnf;

  /*Receive Message Struct */
   OamsNsvchNsUnprovFrLink oamsNsvchNsUnprovFrLink;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.src.prcr = PRCR_PP;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.src.entity = ENT_PSSTK_GSAL;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.src.clsId = 1;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.src.rfu = 0;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.src.inst = 0;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.dest.prcr = PRCR_PP;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.dest.entity = ENT_OAMS_PSSCM;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.dest.clsId = 2;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.dest.rfu = 0;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.dest.inst = 0;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.msgType = PSSKS_NS_NSVCH_UNPROV_NSVC_CNF;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.subType = MSG_SUB_TYPE;
   pssksNsNsvchUnprovNsvcCnf.sysHdr.priority = 0;
   pssksNsNsvchUnprovNsvcCnf.bufLen = 0;
   pssksNsNsvchUnprovNsvcCnf.trId = 0;
   pssksNsNsvchUnprovNsvcCnf.apiId = 0;
   pssksNsNsvchUnprovNsvcCnf.nsvci = 5;
   pssksNsNsvchUnprovNsvcCnf.result = BSS_SUCCESS;
   pssksNsNsvchUnprovNsvcCnf.cause = 0;

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&pssksNsNsvchUnprovNsvcCnf,sizeof(PssksNsNsvchUnprovNsvcCnf));

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
        printf("\n1. Run TC_059");
        printf("\n2. Run TC_060");
        printf("\n3. Run TC_061");
        printf("\n4. Run TC_062");
        printf("\n5. Run TC_063");
        printf("\n6. Run TC_064");
        printf("\n7. Run TC_065");
        printf("\n8. Run TC_066");
        printf("\n9. Run TC_067");
        printf("\nEnter your choice :  ");  
        scanf("%d",&iTCChoice); 
        if(iTCChoice > 0) 
        {
         
         if( 1 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_059);
           printf("\nRunning Test Case TC_059"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 2 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_060);
           printf("\nRunning Test Case TC_060"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 3 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_061);
           printf("\nRunning Test Case TC_061"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 4 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_062);
           printf("\nRunning Test Case TC_062"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 5 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_063);
           printf("\nRunning Test Case TC_063"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 6 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_064);
           printf("\nRunning Test Case TC_064"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 7 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_065);
           printf("\nRunning Test Case TC_065"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 8 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_066);
           printf("\nRunning Test Case TC_066"); 
           suite_add_tcase (s, tc_core);
             RunTestSuite(s);
           }
         
         if( 9 == iTCChoice)  
           {
           tcase_add_test (tc_core, TC_067);
           printf("\nRunning Test Case TC_067"); 
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

