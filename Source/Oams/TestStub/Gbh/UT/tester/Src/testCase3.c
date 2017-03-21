#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <tester.h>
#include <adap_header.h>


#define totalNoOfTC  7
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

 TC Description: To see the transition when the message OAMS_CFG_GBH_FIRST_NSVC_ENABLED is received.
**************************************************************************/
START_TEST (TC_001)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgGbhFirstNsvcEnabled oamsCfgGbhFirstNsvcEnabled;

  /*Receive Message Struct */
   GsalMessage gsalMessage;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.prcr = PRCR_PP;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.clsId = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.rfu = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.inst = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.entity = ENT_OAMS_GBH;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.clsId = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.rfu = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.inst = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.msgType = OAMS_CFG_GBH_FIRST_NSVC_ENABLED;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.subType = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.priority = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgGbhFirstNsvcEnabled,sizeof(OamsCfgGbhFirstNsvcEnabled));

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
   if(!(gsalMessage.sysHdr.msgType == OAMS_GBH_BSSGP_SIG_BVC_RESET) )
   {
      flag = 0;
      fail("value of gsalMessage.sysHdr.msgType is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.pduType == PDU_BVC_RESET) )
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
   if(!(gsalMessage.bssgpMessage.nsLsp == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsLsp is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.changeIpCause == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.changeIpCause is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nsTrId == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nsTrId is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.nRefId == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.nRefId is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcReset.bvci == 0) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcReset.bvci is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcReset.cause[0] == BSSGP_CAUSE_OAM_INTERVENTION) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcReset.cause[1] is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcReset.isPresentCellId == I_FALSE) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcReset.isPresentCellId is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcReset.isPresentFeatureBitmap == I_TRUE) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcReset.isPresentFeatureBitmap is not correct ");
      break;
   }
   if(!(gsalMessage.bssgpMessage.bvcReset.featureBitmap[0] == 2) )
   {
      flag = 0;
      fail("value of gsalMessage.bssgpMessage.bssgpMsgBvcReset.featureBitmap[1] is not correct ");
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received.
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
//   gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
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
   if(!(oamsGbhPschSigBvcResetInd.cbl == 0) )
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
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(!strcpy(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Enabled") )
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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET is received.
**************************************************************************/
START_TEST (TC_003)
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
   gsalMessage.bssgpMessage.bvcReset.cause[0] = 0;
   gsalMessage.bssgpMessage.bvcReset.isPresentCellId = I_FALSE;
//   gsalMessage.bssgpMessage.bvcReset.cellId[8] = {0,0,0,0,0,0,0};
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
   if(!(oamsGbhCfgAlarmInd.sysHdr.dest.prcr == PRCR_PP) )
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
   if(!(oamsGbhCfgAlarmInd.sysAlarm.info3 == OAMS_OBJTYPE_GBINTERFACE) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.info3 is not correct ");
      break;
   }
   if(!strcpy(oamsGbhCfgAlarmInd.sysAlarm.infoString,"Signaling Bvc Reset is Initiated by SGSN") )
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
   if(!(oamsGbhPschSigBvcResetInd.cbl == 2) )
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
      test_result[3] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[3] = 1;    /* 1 for pass*/

}
END_TEST


/**************************************************************************
 TC Name: TC_004

 TC Description: To see the transition when the message OAMS_CFG_GBH_LAST_NSVC_DISABLED is received.
**************************************************************************/
START_TEST (TC_004)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgGbhLastNsvcDisabled oamsCfgGbhLastNsvcDisabled;

  /*Receive Message Struct */
   OamsGbhCfgAlarmInd oamsGbhCfgAlarmInd;
   OamsGbhPschGbDownInd oamsGbhPschGbDownInd;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.prcr = PRCR_PP;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.clsId = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.rfu = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.inst = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.entity = ENT_OAMS_GBH;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.clsId = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.rfu = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.inst = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.msgType = OAMS_CFG_GBH_LAST_NSVC_DISABLED;
   oamsCfgGbhLastNsvcDisabled.sysHdr.subType = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.priority = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgGbhLastNsvcDisabled,sizeof(OamsCfgGbhLastNsvcDisabled));

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
   if(!(oamsGbhCfgAlarmInd.sysAlarm.sysalarmId == ALARM_GBINTERFACE_DISABLED) )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.sysalarmId is not correct ");
      break;
   }
   if(!(oamsGbhCfgAlarmInd.sysAlarm.alarmLevel == ALRM_LVL_MAJR) )
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
   if(!strcpy(oamsGbhCfgAlarmInd.sysAlarm.infoString,"GB Interface is Disabled") )
   {
      flag = 0;
      fail("value of oamsGbhCfgAlarmInd.sysAlarm.infoString[150] is not correct ");
      break;
   }
  }while(0);

  /*Receiving of Message*/
  AdapMsgRecv(&buffer, &size, ENT_TESTER);
  oamsGbhPschGbDownInd = *((OamsGbhPschGbDownInd *)buffer); 

  /*Post-conditions check*/
  do{
   if(!(oamsGbhPschGbDownInd.sysHdr.src.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschGbDownInd.sysHdr.src.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschGbDownInd.sysHdr.src.entity == ENT_OAMS_GBH) )
   {
      flag = 0;
      fail("value of oamsGbhPschGbDownInd.sysHdr.src.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschGbDownInd.sysHdr.dest.prcr == PRCR_PP) )
   {
      flag = 0;
      fail("value of oamsGbhPschGbDownInd.sysHdr.dest.prcr is not correct ");
      break;
   }
   if(!(oamsGbhPschGbDownInd.sysHdr.dest.entity == 200) )
   {
      flag = 0;
      fail("value of oamsGbhPschGbDownInd.sysHdr.dest.entity is not correct ");
      break;
   }
   if(!(oamsGbhPschGbDownInd.sysHdr.msgType == OAMS_GBH_PSCH_GB_DOWN_IND) )
   {
      flag = 0;
      fail("value of oamsGbhPschGbDownInd.sysHdr.msgType is not correct ");
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

 TC Description: To see the transition when the message OAMS_CFG_GBH_LAST_NSVC_DISABLED is received and DB call fails while processing it.
**************************************************************************/
START_TEST (TC_005)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgGbhLastNsvcDisabled oamsCfgGbhLastNsvcDisabled;

  /*Receive Message Struct */
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.prcr = PRCR_PP;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.clsId = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.rfu = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.src.inst = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.entity = ENT_OAMS_GBH;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.clsId = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.rfu = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.dest.inst = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.msgType = OAMS_CFG_GBH_LAST_NSVC_DISABLED;
   oamsCfgGbhLastNsvcDisabled.sysHdr.subType = 0;
   oamsCfgGbhLastNsvcDisabled.sysHdr.priority = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgGbhLastNsvcDisabled,sizeof(OamsCfgGbhLastNsvcDisabled));

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

 TC Description: To see the transition when the message OAMS_CFG_GBH_FIRST_NSVC_ENABLED is received and DB call fails while processing it.
**************************************************************************/
START_TEST (TC_006)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   OamsCfgGbhFirstNsvcEnabled oamsCfgGbhFirstNsvcEnabled;

  /*Receive Message Struct */
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.prcr = PRCR_PP;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.entity = ENT_OAMS_CFG;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.clsId = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.rfu = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.src.inst = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.prcr = PRCR_PP;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.entity = ENT_OAMS_GBH;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.clsId = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.rfu = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.dest.inst = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.msgType = OAMS_CFG_GBH_FIRST_NSVC_ENABLED;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.subType = 0;
   oamsCfgGbhFirstNsvcEnabled.sysHdr.priority = 0;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&oamsCfgGbhFirstNsvcEnabled,sizeof(OamsCfgGbhFirstNsvcEnabled));

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

 TC Description: To see the transition when the message PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK is received and DB call fails while processing it.
**************************************************************************/
START_TEST (TC_007)
{
int flag = 1;
void *buffer = NULL;
int size = 0;
  /*Send Message Struct */
   GsalMessage gsalMessage;

  /*Receive Message Struct */
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
//   gsalMessage.bssgpMessage.bvcResetAck.cellId[8] = {0,0,0,0,0,0,0,0};
   gsalMessage.bssgpMessage.bvcResetAck.isPresentFeatureBitmap = I_TRUE;
   gsalMessage.bssgpMessage.bvcResetAck.featureBitmap[0] = 2;


/******* Enter Preconfiguration Steps - START *******/


/******* Enter Preconfiguration Steps - END *******/

   usleep(0);
  /*Sending of Message*/
  AdapMsgSend(&gsalMessage,sizeof(GsalMessage));

/******* Enter Verification Steps - START *******/


/******* Enter Verification Steps - END *******/


   if(0 == flag)
      test_result[7] = 2;    /* 2 for fail*/
   if(1 == flag)
      test_result[7] = 1;    /* 1 for pass*/

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
printf("message type printed by arti %d \n",  OAMS_GBH_CFG_ALARM_IND);
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
           printf("\nTC_001 GbhActive->GbhActive");
           printf("\n 1: Run");
           printf("\nPlease enter your choice : ");
           scanf("%d",&iTSSChoice); 
           if( 1 == iTSSChoice)  
             {
                TCase *tc1 = tcase_create("core");
              tcase_add_test(tc1,TC_001);
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


