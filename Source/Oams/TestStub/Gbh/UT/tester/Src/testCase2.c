#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  12
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

 TC Description: To see the transition when an unsolicited message is received }
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
   oamsCfgPsscmUnlockReq.sysHdr.src.entity = 200;
   oamsCfgPsscmUnlockReq.sysHdr.src.clsId = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.rfu = 0;
   oamsCfgPsscmUnlockReq.sysHdr.src.inst = 0;
   oamsCfgPsscmUnlockReq.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgPsscmUnlockReq.sysHdr.dest.entity = ENT_OAMS_GBH;
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

 }
END_TEST

/**************************************************************************
 TC Name: TC_002

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received. {{Preconfiguration : Set CBL_DISABLED in GbIfStatus Table }}
**************************************************************************/
START_TEST (TC_002)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET_ACK;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = I_FALSE;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_FALSE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == ALARM_GBINTERFACE_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strncmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Enabled", oamsGbhCfgAlarmInd.sysAlarm.infoStrLen) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received.{Preconfiguration : Set CBL_DISABLED in GbIfStatus Table }
**************************************************************************/
START_TEST (TC_003)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET_ACK;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = I_TRUE;
   //gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_TRUE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == ALARM_GBINTERFACE_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Enabled") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
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
 TC Name: TC_004

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received. {Preconfiguration : Set CBL_ENABLED in GbIfStatus Table }
**************************************************************************/
START_TEST (TC_004)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET_ACK;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_FALSE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == ALARM_GBINTERFACE_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Enabled") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received. {Preconfiguration : Set CBL_ENABLED in GbIfStatus Table }
**************************************************************************/
START_TEST (TC_005)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET_ACK;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = I_TRUE;
   //gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] = 4;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_TRUE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == ALARM_GBINTERFACE_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Enabled") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received.
**************************************************************************/
START_TEST (TC_006)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET_ACK;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcResetAck.bvci = 0;
   gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId = I_TRUE;
   //gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] = 4;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_FALSE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == ALARM_GBINTERFACE_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_CLEARED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Enabled") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received. {DB --> CblNegotiated -- ENABLED}
**************************************************************************/
START_TEST (TC_007)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
//   GsalMessage gsalMessage;
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 0;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = I_FALSE;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == EVENT_SIGNALING_BVC_RESET) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_INFO) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(gsalMessage.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.pduType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsBvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsBvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsNsei == 1) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsNsei is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_TRUE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received. {DB --> CblNegotiated -- DISABLED}
**************************************************************************/
START_TEST (TC_008)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   //GsalMessage gsalMessage;
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 0;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = I_FALSE;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == EVENT_SIGNALING_BVC_RESET) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_INFO) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(gsalMessage.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.pduType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsBvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsBvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsNsei == 1) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsNsei is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_FALSE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received. {DB --> cblNegotiated -- CBL_DISABLED}
**************************************************************************/
START_TEST (TC_009)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   //GsalMessage gsalMessage;
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 0;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == EVENT_SIGNALING_BVC_RESET) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_INFO) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(gsalMessage.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.pduType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsBvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsBvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsNsei == 1) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsNsei is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcResetAck.isPresentCellId == I_FALSE) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcResetAck.isPresentCellId is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap == I_TRUE) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcResetAck.isPresentFeatureBitmap is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] == 2) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcResetAck.featureBitmap[1] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_TRUE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received. {DB --> cblNegotiated -- CBL_ENABLED}
**************************************************************************/
START_TEST (TC_010)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   //GsalMessage gsalMessage;
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 0;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == EVENT_SIGNALING_BVC_RESET) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_INFO) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(gsalMessage.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.pduType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsBvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsBvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsNsei == 1) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsNsei is not correct ");
      break;
   }
  
   if(!(gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] == 2) )
   {
      flag = 0;
      fail("value of featureBitmap is not correct ");
      break;
   }
}while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_ENABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_FALSE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received.
**************************************************************************/
START_TEST (TC_011)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   //GsalMessage gsalMessage;
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 0;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] = 4;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == EVENT_SIGNALING_BVC_RESET) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_INFO) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(gsalMessage.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.pduType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsBvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsBvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsNsei == 1) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsNsei is not correct ");
      break;
   }

   if(!(gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] == 2) )
   {
      flag = 0;
      fail("value of featureBitmap is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_TRUE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received.
**************************************************************************/
START_TEST (TC_012)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   //GsalMessage gsalMessage;
   OamsGbhPschSigBvcResetInd oamsGbhPschSigBvcResetInd;
   gsalMessage.sysHdr.src.prcr = PRCR_PP;
   gsalMessage.sysHdr.src.entity = ENT_PSSTK_GSAL;
   gsalMessage.sysHdr.src.clsId = 0;
   gsalMessage.sysHdr.src.rfu = 0;
   gsalMessage.sysHdr.src.inst = 0;
   gsalMessage.sysHdr.dest.prcr = PRCR_PP;
   gsalMessage.sysHdr.dest.entity = ENT_OAMS_GBH;
   gsalMessage.sysHdr.dest.clsId = 0;
   gsalMessage.sysHdr.dest.rfu = 0;
   gsalMessage.sysHdr.dest.inst = 0;
   gsalMessage.sysHdr.msgType = PSSKS_BSSGP_GBH_SIG_BVC_RESET;
   gsalMessage.sysHdr.subType = 0;
   gsalMessage.sysHdr.priority = 0;
   gsalMessage.bssgpMessage.pduType = PDU_BVC_RESET;
   gsalMessage.bssgpMessage.nsBvci = 0;
   gsalMessage.bssgpMessage.nsNsei = 1;
   gsalMessage.bssgpMessage.nsLsp = 0;
   gsalMessage.bssgpMessage.changeIpCause = 0;
   gsalMessage.bssgpMessage.nsTrId = 0;
   gsalMessage.bssgpMessage.nRefId = 0;
   gsalMessage.bssgpMessage.reserved1 = 0;
   gsalMessage.bssgpMessage.reserved2 = 0;
   gsalMessage.bssgpMessage.reserved3 = 0;
   gsalMessage.bssgpMessage.reserved4 = 0;
   gsalMessage.bssgpMessage.bvcReset.bvci = 0;
   gsalMessage.bssgpMessage.bvcReset.cause[1] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
   //gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] = 4;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhCfgAlarmInd = *((OamsGbhCfgAlarmInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_CP) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysHdr.msgType == OAMS_GBH_CFG_ALARM_IND) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == EVENT_SIGNALING_BVC_RESET) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_INFO) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.alarmLevel is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.key1 == 0) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.key1 is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_BSSNODE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(strcmp(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  gsalMessage = *((GsalMessage *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(gsalMessage.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET_ACK) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.pduType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsBvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsBvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsNsei == 1) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsNsei is not correct ");
      break;
   }

   if(!(gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] == 2) )
   {
      flag = 0;
      fail("value of featureBitmap is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschSigBvcResetInd = *((OamsGbhPschSigBvcResetInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.sysHdr.msgType == OAMS_GBH_PSCH_SIG_BVC_RESET_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.sysHdr.msgType is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.cbl == CBL_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.cbl is not correct ");
      break;
   }
   if(!(oamsGbhPschSigBvcResetInd.isCblChanged == I_FALSE) )
   {
      flag = 0;
      fail("value of oamsGbhPschSigBvcResetInd.isCblChanged is not correct ");
      break;
   }
  }while(0);

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[12] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[12] = 1;    /* 1 for pass*/

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
        }
           }while(iTCChoice != 0);
      }
    if(2 == iChoice)
     {
      do{
       Suite *s = suite_create ("CFG");
        system("clear");
        printf("\n0 : Previous Menu");
       printf("\n1: ");
       printf(" TS_1 : ");
       printf(" GbhActive->GbhActive ");
        printf("\n 100: Run all Test Suits");
        printf("\nPlease enter your choice : ");
        scanf("%d",&iTSChoice); 
         if( 1 == iTSChoice)  
          {
             system("clear");
             printf("\n 0 : Previous Menu");
             printf("\n TS_01 will run following TestCases:");
           printf("(1). ");
           printf("\nTC_002 GbhActive->GbhActive");
           printf("\n 1: Run");
           printf("\nPlease enter your choice : ");
           scanf("%d",&iTSSChoice); 
           if( 1 == iTSSChoice)  
             {
                TCase *tc1 = tcase_create("core");
              tcase_add_test(tc1,TC_002);
                suite_add_tcase(s,tc1);
                RunTestSuite(s);
            }
          }
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


