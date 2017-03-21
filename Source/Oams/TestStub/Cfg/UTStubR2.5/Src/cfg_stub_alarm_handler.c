/* Alarm Handler TestCases*/

/*#include <cfg_strub.h>*/
#include <oamcfg_includes.h>

/*extern int gTestCaseCompleted =0;*/
extern int gTestCaseCompleted;
#define FR 0  /*COMP_C */
#define SNS_CONFIG_TIMER_RETRY_FAILURE 1  /*COMP_C */
#define SNS_SIZE_TIMER_RETRY_FAILURE  2
#define BSC_API_LOCK_BSS 2
#define BSC_API_UNLOCK_BSS 3
#define BSC_API_UNLOCKINPROGRESS_BSS 4
#define BSC_API_LOCKINPROGRESS_BSS 5


OamsCfgAfhSysAlarm oamsCfgAfhSysAlarmBuff;

OamsCfgGrhmLockReq *oamsCfgGrhmLockReqBuff;
OamsCfgGrhmUnlockReq *oamsCfgGrhmUnlockReqBuff;

I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);

void cfgAlarmObjHndlr1()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      OamsGbhCfgAlarmInd *oamsGbhCfgAlarmIndBuff;
      oamsGbhCfgAlarmIndBuff = (OamsGbhCfgAlarmInd *)calloc(1,sizeof(OamsGbhCfgAlarmInd));

      cfgStubSendMessage(oamsGbhCfgAlarmIndBuff, sizeof(OamsGbhCfgAlarmInd),ENT_OAMS_GBH,ENT_OAMS_CFG,OAMS_GBH_CFG_ALARM_IND, 0);
      gTestCaseCompleted = 1;
      printf("::gTestCaseCompleted = %d\n",gTestCaseCompleted);
      free(oamsGbhCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, alarmReason %d, ObjType %d, ObjId %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->alarmReason, recAlarmPtr->key1, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 1: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr2()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      OamsNsvchCfgAlarmInd *oamsNsvchCfgAlarmIndBuff;
      oamsNsvchCfgAlarmIndBuff = (OamsNsvchCfgAlarmInd *)calloc(1,sizeof(OamsNsvchCfgAlarmInd));

      cfgStubSendMessage(oamsNsvchCfgAlarmIndBuff, sizeof(OamsNsvchCfgAlarmInd),ENT_OAMS_PSSCM,ENT_OAMS_CFG,OAMS_NSVCH_CFG_ALARM_IND, 0);
      gTestCaseCompleted = 1;
      printf("gTestCaseCompleted = %d\n",gTestCaseCompleted);
      free(oamsNsvchCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, alarmReason %d, ObjType %d, ObjId %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->alarmReason, recAlarmPtr->key1, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 1: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr3()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      OamsPsscmCfgAlarmInd *oamsPsscmCfgAlarmIndBuff;
      oamsPsscmCfgAlarmIndBuff = (OamsPsscmCfgAlarmInd *)calloc(1,sizeof(OamsPsscmCfgAlarmInd));

      cfgStubSendMessage(oamsPsscmCfgAlarmIndBuff, sizeof(OamsPsscmCfgAlarmInd),ENT_OAMS_PSSCM,ENT_OAMS_CFG,OAMS_PSSCM_CFG_ALARM_IND, 0);
      gTestCaseCompleted = 1;
      free(oamsPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, alarmReason %d, ObjType %d, ObjId %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->alarmReason, recAlarmPtr->key1, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 1: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}
/*
void cfgAlarmObjHndlr4()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      OamsScmCfgAlarmIn	 *oamsGbhCfgAlarmIndBuff;
      oamsGbhCfgAlarmIndBuff = (OamsGbhCfgAlarmInd *)calloc(1,sizeof(OamsGbhCfgAlarmInd));

      cfgStubSendMessage(oamsGbhCfgAlarmIndBuff, sizeof(OamsGbhCfgAlarmInd),ENT_OAM_GBH,ENT_OAMS_CFG,OAMS_GBH_CFG_ALARM_IND, 0);
      gTestCaseCompleted = 1;
      free(oamsGbhCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, alarmReason %d, ObjType %d, ObjId %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->alarmReason, recAlarmPtr->key1, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 1: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}*/


void cfgBssHndlr2()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      removeAllFromCellTable();
      removeAllFromBssTable();
      insertIntoBssTable(1,LOCKED);
      updateGprsEnabledInBssTable(1,TRUE);
      insertIntoCellTable(1, 1, UNLOCKED, 1); 
      CsappGrhmCfgUnlockResp csappGrhmCfgUnlockRespBuff;
      cfgStubSendCmMessage(&csappGrhmCfgUnlockRespBuff, sizeof(CsappGrhmCfgUnlockResp), BSC_API_UNLOCKINPROGRESS_BSS);
      csappGrhmCfgUnlockRespBuff.objType = OAMS_OBJTYPE_AINTERFACE;
      cfgStubSendMessage(&csappGrhmCfgUnlockRespBuff, sizeof(CsappGrhmCfgUnlockResp), ENT_CSAPP_GRHM, ENT_OAMS_CFG, CSAPP_GRHM_CFG_UNLOCK_RESP,0);
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}

void cfgBssHndlr1()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      removeAllFromCellTable();
      removeAllFromBssTable();
      insertIntoBssTable(1,LOCKED);
      updateGprsEnabledInBssTable(1,FALSE);
      insertIntoCellTable(1, 1, UNLOCKED, 1); 
      CsappGrhmCfgUnlockResp csappGrhmCfgUnlockRespBuff;
      cfgStubSendCmMessage(&csappGrhmCfgUnlockRespBuff, sizeof(CsappGrhmCfgUnlockResp), BSC_API_UNLOCKINPROGRESS_BSS);
      csappGrhmCfgUnlockRespBuff.objType = OAMS_OBJTYPE_AINTERFACE;
      cfgStubSendMessage(&csappGrhmCfgUnlockRespBuff, sizeof(CsappGrhmCfgUnlockResp), ENT_CSAPP_GRHM, ENT_OAMS_CFG, CSAPP_GRHM_CFG_UNLOCK_RESP,0);
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}

void cfgBssHndlr3()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      removeAllFromGbInterfaceTable();
      insertIntoGbInterfaceTable(1, IP_STATIC); 
      OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockRespBuff;
      cfgStubSendCmMessage(&oamsPsscmCfgUnlockRespBuff, sizeof(OamsPsscmCfgUnlockResp), BSC_API_UNLOCKINPROGRESS_BSS);
      cfgStubSendMessage(&oamsPsscmCfgUnlockRespBuff, sizeof(OamsPsscmCfgUnlockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_PSSCM_CFG_UNLOCK_RESP,0);
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}

void cfgBssHndlr4()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      removeAllFromGbInterfaceTable();
      insertIntoGbInterfaceTable(1, FR); 
      OamsPsscmCfgUnlockResp oamsPsscmCfgUnlockRespBuff;
      cfgStubSendCmMessage(&oamsPsscmCfgUnlockRespBuff, sizeof(OamsPsscmCfgUnlockResp), BSC_API_UNLOCKINPROGRESS_BSS);
      cfgStubSendMessage(&oamsPsscmCfgUnlockRespBuff, sizeof(OamsPsscmCfgUnlockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_PSSCM_CFG_UNLOCK_RESP,0);
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}

void cfgBssHndlr5()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      removeAllFromGbInterfaceTable();
      insertIntoGbInterfaceTable(1, FR); 
      OamsPsscmCfgLockResp oamsPsscmCfgLockRespBuff;
      cfgStubSendCmMessage(&oamsPsscmCfgLockRespBuff, sizeof(OamsPsscmCfgLockResp), BSC_API_LOCKINPROGRESS_BSS);
      cfgStubSendMessage(&oamsPsscmCfgLockRespBuff, sizeof(OamsPsscmCfgLockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_PSSCM_CFG_LOCK_RESP,0);
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}

void cfgBssHndlr6()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      CsappGrhmCfgLockResp csappGrhmCfgLockRespBuff;
      csappGrhmCfgLockRespBuff.objType = OAMS_OBJTYPE_AINTERFACE;
      cfgStubSendCmMessage(&csappGrhmCfgLockRespBuff, sizeof(CsappGrhmCfgLockResp), BSC_API_LOCKINPROGRESS_BSS);
      cfgStubSendMessage(&csappGrhmCfgLockRespBuff, sizeof(CsappGrhmCfgLockResp), ENT_CSAPP_GRHM, ENT_OAMS_CFG, CSAPP_GRHM_CFG_LOCK_RESP,0);
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}

void cfgBssHndlr7()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));
   if ( testInitiation )
   {
      testInitiation = 0;
      OamsCfgScmCfgAlarmInd oamsCfgScmCfgAlarmIndBuff;
      cfgStubSendCmMessage(&oamsCfgScmCfgAlarmIndBuff, sizeof(OamsCfgScmCfgAlarmInd), BSC_API_LOCKINPROGRESS_BSS);
      cfgStubSendMessage(&oamsCfgScmCfgAlarmIndBuff, sizeof(OamsCfgScmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,OAMS_SCM_CFG_ALARM_IND,0 );
      
      gTestCaseCompleted = 1;
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
      }
   }
}
