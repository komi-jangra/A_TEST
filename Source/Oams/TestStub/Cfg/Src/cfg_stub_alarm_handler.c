/* Alarm Handler TestCases*/

/*#include <cfg_strub.h>*/
#include <oamcfg_includes.h>

/*extern int gTestCaseCompleted =0;*/
extern int gTestCaseCompleted;
#define FR 0  /*COMP_C */
#define SNS_CONFIG_TIMER_RETRY_FAILURE 1  /*COMP_C */
#define SNS_SIZE_TIMER_RETRY_FAILURE  2


OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff;

OamsCfgGrhmLockReq *OamsCfgGrhmLockReqBuff;
OamsCfgGrhmUnlockReq *OamsCfgGrhmUnlockReqBuff;
OamsCfgPsscmNsvcResetReq *OamsCfgPsscmNsvcResetReqBuff;
OamsCfgPsscmReviveIpLinkReq *OamsCfgPsscmReviveIpLinkReqBuff;
OamsCfgPcuBvcResetReq *OamsCfgPcuBvcResetReqBuff;
OamsCfgPcuFirstNsvcEnabledReq *OamsCfgPcuFirstNsvcEnabledReqBuff;
OamsCfgPcuAllNsvcDisabledReq *OamsCfgPcuAllNsvcDisabledReqBuff;

I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);

void cfgAlarmObjHndlr1()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      OamsCfgScmCfgAlarmInd *OamsCfgScmCfgAlarmIndBuff;
      OamsCfgScmCfgAlarmIndBuff = (OamsCfgScmCfgAlarmInd *)calloc(1,sizeof(OamsCfgScmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 1\n");

      OamsCfgScmCfgAlarmIndBuff->sysAlarm.sysalarmId = SCCP_SCMG_SS_PROHIBITED;
      OamsCfgScmCfgAlarmIndBuff->sysAlarm.key1 = OAMS_OBJTYPE_AINTERFACE; /*obj type */
      OamsCfgScmCfgAlarmIndBuff->sysAlarm.key2 = 0; /* obj Id */

      cfgStubSendMessage(OamsCfgScmCfgAlarmIndBuff, sizeof(OamsCfgScmCfgAlarmInd),ENT_OAM_OIL,ENT_OAMS_CFG,OAMS_SCM_CFG_ALARM_IND, 0);
      free(OamsCfgScmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_GRHM_LOCK_REQ:
            OamsCfgGrhmLockReqBuff = (OamsCfgGrhmLockReq *) gCfgMsgBuf;
            printf("LOCK_REQ contents are: ObjId: %d, ObjType %d, Reason %d\n",OamsCfgGrhmLockReqBuff->objectId, OamsCfgGrhmLockReqBuff->objType, OamsCfgGrhmLockReqBuff->reason);
            break;
            /*case CSAPP_GRHM_CFG_ALARM_IND:*/
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
      OamsCfgScmCfgAlarmInd *OamsCfgScmCfgAlarmIndBuff;
      OamsCfgScmCfgAlarmIndBuff = (OamsCfgScmCfgAlarmInd *)calloc(1,sizeof(OamsCfgScmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 2\n");

      OamsCfgScmCfgAlarmIndBuff->sysAlarm.sysalarmId = SCCP_SCMG_SS_ALLOWED;
      OamsCfgScmCfgAlarmIndBuff->sysAlarm.key1 = OAMS_OBJTYPE_AINTERFACE; /*obj type */
      OamsCfgScmCfgAlarmIndBuff->sysAlarm.key2 = 0; /* obj Id */

      cfgStubSendMessage(OamsCfgScmCfgAlarmIndBuff, sizeof(OamsCfgScmCfgAlarmInd),ENT_OAM_OIL,ENT_OAMS_CFG,OAMS_SCM_CFG_ALARM_IND, 0);
      free(OamsCfgScmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReqBuff = (OamsCfgGrhmUnlockReq *) gCfgMsgBuf;
               printf("UNLOCK_REQ contents are: ObjId %d, ObjType %d, Reason %d\n",OamsCfgGrhmUnlockReqBuff->objectId, OamsCfgGrhmUnlockReqBuff->objType, OamsCfgGrhmUnlockReqBuff->reason);
            }
            break;
            /*case CSAPP_GRHM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, alarmReason %d, ObjType %d, ObjId %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->alarmReason, recAlarmPtr->key1, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 2: Success\n");
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
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 3\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=0;
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=0;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key1 = OAMS_OBJTYPE_GBINTERFACE;/* obj type */
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      //PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd),ENT_OAM_OIL,ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_PSSCM_NSVC_RESET_REQ:
            {
               OamsCfgPsscmNsvcResetReqBuff = (OamsCfgPsscmNsvcResetReq *) gCfgMsgBuf;
               printf("NSVC Rest Request contents are: NSVC ID %d\n", OamsCfgPsscmNsvcResetReqBuff->nsvcId);
            }
            break;
            /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, ObjType %d, nsvc id %d, cause %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key1, recAlarmPtr->key2, recAlarmPtr->info1);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 3: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr4()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 4\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=1;/*IP_STATIC*/
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=1;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      //PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_PSSCM_REVIVE_IP_LINK_REQ:
            OamsCfgPsscmReviveIpLinkReqBuff = (OamsCfgPsscmReviveIpLinkReq *) gCfgMsgBuf;
            printf("Revive IP Link Request contents are: message type %d\n",OamsCfgPsscmReviveIpLinkReqBuff->sysHdr.msgType);
            break;
            /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, nsvc id %d, cause %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key2, recAlarmPtr->info1);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 4: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr5()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 5\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=2;/*IP_DYNAMIC*/
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=2;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      //PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = OAMS_CAUSE_NS_ALIVE_TIMER_RETRIES_EXPIRY; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_PSSCM_REVIVE_IP_LINK_REQ:
            OamsCfgPsscmReviveIpLinkReqBuff = (OamsCfgPsscmReviveIpLinkReq *) gCfgMsgBuf;
            printf("Revive IP Link Request contents are: message type %d\n",OamsCfgPsscmReviveIpLinkReqBuff->sysHdr.msgType);
            break;
            /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, nsvc id %d, cause %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key2, recAlarmPtr->info1);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 5: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr6()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 6\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=1;/*IP_STATIC*/
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=1;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = SNS_SIZE_TIMER_RETRY_FAILURE; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, nsvc id %d, cause %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key2, recAlarmPtr->info1);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 6: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr7()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 7\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=2;/*IP_DYNAMIC*/
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=2;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = SNS_SIZE_TIMER_RETRY_FAILURE; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         default:
            printf("Error Case !!! No action will be taken ! No alarm will be sent !!!\n");
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 7: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr8()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 8\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=1;/*IP_STATIC*/
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=1;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = SNS_CONFIG_TIMER_RETRY_FAILURE; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, nsvc id %d, cause %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key2, recAlarmPtr->info1);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 8: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr9()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      GbInterfaceTableApi *gbInterfaceTablePtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 9\n");

      ret = getallGbInterfaceTable(&gbInterfaceTablePtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("GbInterface Table is not empty. Directly updating !!! \n");
         gbInterfaceTablePtr->transportType=2;/*IP_DYNAMIC*/
         updateGbInterfaceTable(gbInterfaceTablePtr);
      }
      else
      {
         gbInterfaceTablePtr = (GbInterfaceTableApi *)calloc(1,sizeof(GbInterfaceTableApi));
         printf("GbInterface Table is empty !!! Values to be inserted !!! \n");
         gbInterfaceTablePtr->dummyIndex=0;
         gbInterfaceTablePtr->transportType=2;
         ret = insertGbInterfaceTable(gbInterfaceTablePtr);
         if (ret == CLIB_SUCCESS)
         {
            printf("GbInterfaceTable inserted properly \n");
         }
      }
      free(gbInterfaceTablePtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_MAX_TIMER_RETRIES_EXHAUSTED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc Id -> for testing purpose!!! */
      PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = SNS_CONFIG_TIMER_RETRY_FAILURE; /* cause */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_OAM_OIL, ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         default:
            printf("Error Case !!! No action will be taken ! No alarm will be sent !!!\n");
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 9: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr10()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 10\n");

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_CAUSE_NS_VC_BLOCKED;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc id ... for testing */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd),ENT_OAM_OIL,ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_PSSCM_NSVC_RESET_REQ:
            {
               OamsCfgPsscmNsvcResetReqBuff = (OamsCfgPsscmNsvcResetReq *) gCfgMsgBuf;
               printf("NSVC RESET REQ contents are: nsvcId %d\n",OamsCfgPsscmNsvcResetReqBuff->nsvcId);
            }
            break;
            /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, nsvc Id %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 10: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr11()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 11\n");

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_CAUSE_NS_VC_UNKNOWN;
      PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1; /* nsvc id ... for testing purpose */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd),ENT_OAM_OIL,ENT_OAMS_CFG,PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_PSSCM_NSVC_RESET_REQ:
            {
               OamsCfgPsscmNsvcResetReqBuff = (OamsCfgPsscmNsvcResetReq *) gCfgMsgBuf;
               printf("NSVC RESET REQ contents are: nsvcId %d\n",OamsCfgPsscmNsvcResetReqBuff->nsvcId);
            }
            break;
            /*case PSAPP_PSSCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, nsvc id %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->key2);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 11: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr12()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 12\n");

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NS_CAUSE_BVCI_UNKNOWN;

      /* cell id, lac and bvci ... for testing purpose */
      /*PsappPsscmCfgAlarmIndBuff->sysAlarm.key2 = 1;
        PsappPsscmCfgAlarmIndBuff->sysAlarm.key3 = 1;*/
      PsappPsscmCfgAlarmIndBuff->sysAlarm.info1 = 1; /* bvci */

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {

         case OAMS_CFG_PCUH_BVC_RESET_REQ:
            {
               /*               printf("OAMS_CFG_PCUH_BVC_RESET_REQ contents are: nsei %d\n",PsappPsscmCfgAlarmIndBuff.nsei);*/
               OamsCfgPcuBvcResetReqBuff = (OamsCfgPcuBvcResetReq *) gCfgMsgBuf;
               printf("OAMS_CFG_PCU_BVC_RESET_REQ received...bvci %d\n",OamsCfgPcuBvcResetReqBuff->bvci);
            }
            break;
            /*   case PSAPP_PCU_CFG_ALARM_IND: */
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d, bvci id %d \n",recAlarmPtr->sysalarmId, recAlarmPtr->info1);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 12: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr13()
{
   static int testInitiation =1;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      NsvcTableApi *NsvcTableApiPtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 13\n");

      ret = getallNsvcTable(&NsvcTableApiPtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      if (ret == CLIB_SUCCESS)
      {
         printf("NSVC Table is not empty. Directly updating !!! \n");
         NsvcTableApiPtr->oprState=1;
         NsvcTableApiPtr->nsvcId=1;
         updateNsvcTable(NsvcTableApiPtr);
      }
      else
      {
         NsvcTableApiPtr = ( NsvcTableApi *)calloc(1,sizeof(NsvcTableApi));

         NsvcTableApiPtr->oprState = 1;
         NsvcTableApiPtr->nsvcId = 1; /* key */
         NsvcTableApiPtr->frIndex = 1; /* key */

         insertNsvcTable( NsvcTableApiPtr );
         if (ret == CLIB_SUCCESS)
         {
            printf("NsvcTable inserted properly \n");
         }
      }
      free(NsvcTableApiPtr);

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NSVC_ENABLED;

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ:
            printf("first nsvc enabled req received\n");
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 13: Success\n");
            break;
         default:
            printf("No action taken !\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr14()
{
   static int testInitiation =1;
   static int count =0;
   I_U32 outRows=0;
   I_U16 outSize=0;
   I_S32 ret=0;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      NsvcTableApi *NsvcTableApiPtr;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 14\n");

      ret = getallNsvcTable(&NsvcTableApiPtr,&outRows,&outSize);
      printf ("return value from DB is= %d !!!!!!!!!!! \n",ret);

      /* Insert two NSVC table */
      /*      if (ret == CLIB_SUCCESS)
            {
            printf("NSVC Table is not empty. Directly updating !!! \n");
            NsvcTableApiPtr->oprState=1;
            NsvcTableApiPtr->nsvcId=1;
            NsvcTableApiPtr->frIndex = 1;
            updateNsvcTable(NsvcTableApiPtr);
            NsvcTableApiPtr->oprState=1;
            NsvcTableApiPtr->nsvcId=2;
            NsvcTableApiPtr->frIndex = 2;
            updateNsvcTable(NsvcTableApiPtr);
            }
       */
      if (ret == CLIB_SUCCESS)
      {
         printf ("return value from DB is= %d... So first deleting the table to insert 2 rows with opstate Enabled !!! \n",ret);
         //deleteNsvcTable(NsvcTableApiPtr);
      }
      /*      else
            {
       */

      /*NsvcTableApiPtr = ( NsvcTableApi *)calloc(1,sizeof(NsvcTableApi));*/
      NsvcTableApiPtr = ( NsvcTableApi *)calloc(2,sizeof(NsvcTableApi));
      NsvcTableApiPtr->nsvcId = 1; /* key */
      NsvcTableApiPtr->frIndex = 1; /* key */
      NsvcTableApiPtr->oprState = 1;
      insertNsvcTable( NsvcTableApiPtr );
      /*free(NsvcTableApiPtr);
        NsvcTableApiPtr = ( NsvcTableApi *)calloc(1,sizeof(NsvcTableApi));*/
      NsvcTableApiPtr->nsvcId = 2; /* key */
      NsvcTableApiPtr->frIndex = 2; /* key */
      NsvcTableApiPtr->oprState = 1;
      insertNsvcTable( NsvcTableApiPtr );
      free(NsvcTableApiPtr);
      /*      }
       */

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NSVC_ENABLED;

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_PCUH_FIRST_NSVC_ENABLED_REQ:
            count = 0;
            if (count == 0)
               printf("first time the first nsvc enabled req received!!!\n");
            else
               printf("ERROR!!!! second time the first nsvc enabled req received!!!\n");
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            if (count == 0)
            {
               printf("Alarm for the First occurence of nsvc reset req!!! sysalarmId %d \n",recAlarmPtr->sysalarmId);
               count++;
            }
            else
            {
               printf("Alarm for the Second occurence of nsvc reset req!!! sysalarmId %d \n",recAlarmPtr->sysalarmId);
               gTestCaseCompleted = 1;
               printf("CFG Alarm Object Handler Test Case 14: Success\n");
            }
            break;
      }
   }
}

void cfgAlarmObjHndlr15()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {

      NsvcTableApi *NsvcTableApiPtr;

      testInitiation =0;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 15\n");

      /* Insert one NSVC table */
      NsvcTableApiPtr = ( NsvcTableApi *)calloc(1,sizeof(NsvcTableApi));
      NsvcTableApiPtr->oprState = 0;
      NsvcTableApiPtr->nsvcId = 1;

      if (insertNsvcTable( NsvcTableApiPtr ) != CLIB_SUCCESS)
         updateNsvcTable( NsvcTableApiPtr );

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NSVC_DISABLED;

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(NsvcTableApiPtr);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_PCUH_LOCK_REQ:
            printf("nsvc disabled req received! This is Error !!! \n");
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 15: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr16()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {

      NsvcTableApi *NsvcTableApiPtr;

      testInitiation =0;
      PsappPsscmCfgAlarmInd *PsappPsscmCfgAlarmIndBuff;
      PsappPsscmCfgAlarmIndBuff = (PsappPsscmCfgAlarmInd *)calloc(1,sizeof(PsappPsscmCfgAlarmInd));
      printf("CFG Alarm Object Handler Test Case 16\n");

      /* Insert two NSVC table */
      NsvcTableApiPtr = ( NsvcTableApi *)calloc(1,sizeof(NsvcTableApi));
      NsvcTableApiPtr->oprState = 0;
      NsvcTableApiPtr->nsvcId = 1;

      insertNsvcTable( NsvcTableApiPtr );

      NsvcTableApiPtr = ( NsvcTableApi *)calloc(1,sizeof(NsvcTableApi));
      NsvcTableApiPtr->oprState = 0;
      NsvcTableApiPtr->nsvcId = 2;

      insertNsvcTable( NsvcTableApiPtr );

      PsappPsscmCfgAlarmIndBuff->sysAlarm.sysalarmId = NSVC_DISABLED;

      cfgStubSendMessage(PsappPsscmCfgAlarmIndBuff, sizeof(PsappPsscmCfgAlarmInd), ENT_PSAPP_PCUH, ENT_OAMS_CFG, PSAPP_PSSCM_CFG_ALARM_IND, 0);
      free(NsvcTableApiPtr);
      free(PsappPsscmCfgAlarmIndBuff);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_PCUH_LOCK_REQ:
            printf("Error!!! nsvc disabled req received!! \n");
            break;
            /*case PSAPP_PCU_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 16: Success\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr17()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CFG Alarm Object Handler Test Case 17\n");

      cfgStubSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_CSAPP_GRHM, ENT_OAMS_CFG, CSAPP_GRHM_CFG_ALARM_IND, 0);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /*case CSAPP_GRHM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            /*OamsCfgAfhSysAlarmBuff = (OamsCfgAfhSysAlarm *) gCfgMsgBuf;
              printf("Alarm Contents to CFG are: sysalarmId %d,\n",OamsCfgAfhSysAlarmBuff->sysAlarm.sysalarmId);*/
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 17: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr18()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CFG Alarm Object Handler Test Case 18\n");

      cfgStubSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),ENT_OAMS_CELLH, ENT_OAM_AFH, OAMS_CELLH_CFG_ALARM_IND, 0);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /*case OAMS_CELLH_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            /*OamsCfgAfhSysAlarmBuff = (OamsCfgAfhSysAlarm *) gCfgMsgBuf;
              printf("Sys Alarm sent to AFH %d,\n");*/
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 18 Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr19()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CFG Alarm Object Handler Test Case 19\n");

      cfgStubSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),ENT_OAMS_TRXH, ENT_OAM_AFH, OAMS_TRXH_CFG_ALARM_IND, 0);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /*case OAMS_TRXH_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            /*OamsCfgAfhSysAlarmBuff = (OamsCfgAfhSysAlarm *) gCfgMsgBuf;
              printf("Sys Alarm sent to AFH %d,\n");*/
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 19 Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}

void cfgAlarmObjHndlr20()
{
   static int testInitiation =1;
   SysAlarm* recAlarmPtr = ( SysAlarm* )(gCfgMsgBuf+sizeof(SysHdr));

   if ( testInitiation )
   {
      testInitiation =0;
      printf("CFG Alarm Object Handler Test Case 20\n");

      cfgStubSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm),ENT_OAM_OIL, ENT_OAM_AFH, OAMS_SCM_CFG_ALARM_IND, 0);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         /*case OAMS_SCM_CFG_ALARM_IND:*/
         case OAMS_CFG_AFH_ALARM_IND:
            /*OamsCfgAfhSysAlarmBuff = (OamsCfgAfhSysAlarm *) gCfgMsgBuf;*/
            /*printf("Sys Alarm sent to AFH %d,\n");*/
            printf("Alarm Contents to CFG are: sysalarmId %d \n",recAlarmPtr->sysalarmId);
            gTestCaseCompleted = 1;
            printf("CFG Alarm Object Handler Test Case 20: Success\n");
            break;
         default:
            printf("No action taken by CFG!!!\n");
            break;
      }
   }
}
