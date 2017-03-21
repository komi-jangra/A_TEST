/***********************************File Header ***************************
   File Name        : oamscfg_timer.c
Purpose          : This file contains Timer implementation for CFG
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#include <oamscfg_includes.h>

static timer_t     tid;                // timer ID for timer

void cfgStopTimer()
{
   LOG_PRINT(LOG_INFO," Stopping the Timer ");
   gIsTimerRunning = FALSE;
   StopTimerFrmwrk(tid);
}
#if 0
void *cfgTimeOutHandler()
{
   LOG_PRINT(LOG_INFO," cfg timeOut handler ");
   gMgsOprSts = FALSE;   /* Change For CS2.2 */
   gIsTimerRunning = FALSE;
   /* Bug Fixed - Mantis#3783 : Start */
   if ( gStoredTsiDriverStatusMsg != NULL )
      DalocOrdBuf(gStoredTsiDriverStatusMsg);
   if ( gStoredDspBootMsg != NULL )
      DalocOrdBuf(gStoredDspBootMsg);
   /* Bug Fixed - Mantis#3783 : End */

   if ((( gMgsSmmDspBootFlag == TRUE) &&
            ( gMgsSmmTsiRspFlag == FALSE )) ||
         (gMgsWaitForRspFlg==MGS_WT_FOR_MGS_DSP_INIT_RESP))
   {
      gMgsWaitForRspFlg = MGS_NO_WAIT;

      OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
      OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TRAU_INITIALIZATION_FAILED;
      OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
      OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSS;
      OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
      OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"Trau Init Failed on BSC Id [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);

      cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);

      if (( gMgsSmmDspBootFlag == TRUE) && ( gMgsSmmTsiRspFlag == FALSE ))
      {
         LOG_PRINT(LOG_INFO,"Time out for MGS_BOOT_TEST_MSG");
      }
      else 
      {
         LOG_PRINT(LOG_INFO,"Time out for MGS_WT_FOR_MGS_DSP_INIT_RESP");
         LOG_PRINT(LOG_INFO,"gCfgState is [%d]", gCfgState);
      }
      /* Change For CS2.2 : Start */
     if(gCfgState == CFG_INIT_TSI)
     {
         RELEASE_MUTEX;
         gCfgState = CFG_BPM_INIT;
         LOG_PRINT(LOG_INFO,"CFG is in BPM INIT STATE");
     }
     else if((ZERO == gSentAddBicReqAtInitNum) && 
            (FALSE == gMgsOprSts)
         )
      {
         /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
            sndSwitchConForBicsAtInit();
         /* CS3.0 Changes : Start */
         /* gCfgState = CFG_READY; */
         /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
            if(gCfgState == CFG_START_TRAU)
            {
               sendRequestForAvailableReleases(); 
               gCfgState = CFG_BPM_SW_QUERY;
               LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
            }
         /* CS3.0 Changes : End */
      }
      /* Change For CS2.2 : End */

   }
   else if (gMgsWaitForRspFlg==MGS_WT_FOR_MGS_DSP_INIT_RESP)
   {
      LOG_PRINT(LOG_INFO,"Time out for MGS_WT_FOR_MGS_TRAU_START_RESP");
      if(gCfgState == CFG_INIT_TSI)
     {
         RELEASE_MUTEX;
         gCfgState = CFG_BPM_INIT;
         LOG_PRINT(LOG_INFO,"CFG is in BPM INIT STATE");
     }
     else if((ZERO == gSentAddBicReqAtInitNum) && 
            (FALSE == gMgsOprSts)
         )
      {
         /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
         sndSwitchConForBicsAtInit();
         /* CS3.0 Changes : Start */
         /* gCfgState = CFG_READY; */
         /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
         if(gCfgState == CFG_START_TRAU)
         {
            sendRequestForAvailableReleases(); 
            gCfgState = CFG_BPM_SW_QUERY;
            LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
         }
         /* CS3.0 Changes : End */
      }
   }
   else
      if (( gMgsSmmDspBootFlag == FALSE) &&
            ( gMgsSmmTsiRspFlag == TRUE ))
      {
         gMgsWaitForRspFlg = MGS_NO_WAIT;

         OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
         OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TSI_INITIALIZATION_FAILED;
         OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
         OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSS;
         OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
         OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"TSI Init Failed on BSC Id [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);

         LOG_PRINT(LOG_INFO," Time out for MGS_WT_FOR_MGS_TRAU_DRIVER_INIT_STATUS");
         cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
         /* Change For CS2.2 : Start */
         if(gCfgState == CFG_INIT_TSI)
     {
         RELEASE_MUTEX;
         gCfgState = CFG_BPM_INIT;
         LOG_PRINT(LOG_INFO,"CFG is in BPM INIT STATE");
     }
     else if((ZERO == gSentAddBicReqAtInitNum) && 
               (FALSE == gMgsOprSts)
            )
         {
            /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
            sndSwitchConForBicsAtInit();
            /* CS3.0 Changes : Start */
            /* gCfgState = CFG_READY; */
            /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
            if(gCfgState == CFG_START_TRAU)
            {
               sendRequestForAvailableReleases(); 
               gCfgState = CFG_BPM_SW_QUERY;
               LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
            }
            /* CS3.0 Changes : End */
         }
         /* Change For CS2.2 : End */
      }
      else
         if (( gMgsSmmDspBootFlag== TRUE) && 
               ( gMgsSmmTsiRspFlag == TRUE ))    
         {
            OamsCfgAfhSysAlarm OamsCfgAfhSysAlarmBuff = {0};
            OamsCfgAfhSysAlarmBuff.sysAlarm.sysalarmId =TSI_TRAU_INITIALIZATION_FAILED;
            OamsCfgAfhSysAlarmBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
            OamsCfgAfhSysAlarmBuff.sysAlarm.info3 =OAMS_OBJTYPE_BSS;
            OamsCfgAfhSysAlarmBuff.sysAlarm.key1 = gDbBssTableApiStorage.bscId;
            OamsCfgAfhSysAlarmBuff.sysAlarm.infoStrLen = sprintf(OamsCfgAfhSysAlarmBuff.sysAlarm.infoString,"TSI/Trau Init Failed on BSC Id [%d]",OamsCfgAfhSysAlarmBuff.sysAlarm.key1);
            LOG_PRINT(LOG_INFO," Time out :for TSI_TRAU_INITIALIZATION_FAILED");
            cfgSendMessage(&OamsCfgAfhSysAlarmBuff, sizeof(OamsCfgAfhSysAlarm), ENT_OAM_AFH, OAMS_CFG_AFH_ALARM_IND, 0);
            /* Change For CS2.2 : Start */
            if(gCfgState == CFG_INIT_TSI)
     {
         RELEASE_MUTEX;
         gCfgState = CFG_BPM_INIT;
         LOG_PRINT(LOG_INFO,"CFG is in BPM INIT STATE");
     }
     else if((ZERO == gSentAddBicReqAtInitNum) && 
                  (FALSE == gMgsOprSts)
               )
            {
               /* Send Switching Request for All Timeslot having usageType LAPD_BIC */
               sndSwitchConForBicsAtInit();
               /* CS3.0 Changes : Start */
               /* gCfgState = CFG_READY; */
               /* LOG_PRINT(LOG_INFO,"CFG is in Ready State"); */
               if(gCfgState == CFG_START_TRAU)
               {
                  sendRequestForAvailableReleases(); 
                  gCfgState = CFG_BPM_SW_QUERY;
                  LOG_PRINT(LOG_INFO,"CFG is in BPM QUERY STATE");
               }
               /* CS3.0 Changes : End */
            }
            /* Change For CS2.2 : End */
         }
         else
         {
               LOG_PRINT(LOG_DEBUG,"Timer expired in Invalid State");
               cfgSendNackToCm(CM_ERR_TIMEOUT);
               if (gStoredMsgBufPtr !=NULL)
               {
                  DalocOrdBuf(gStoredMsgBufPtr);
                  gStoredMsgBufPtr=NULL;
               }
        }
}
#endif

void *cfgTimeOutHandler()
{
   LOG_PRINT(LOG_INFO," cfg timeOut handler ");
   gMgsOprSts = FALSE;   /* Change For CS2.2 */
   gIsTimerRunning = FALSE;
   /* Bug Fixed - Mantis#3783 : Start */
   if ( gStoredTsiDriverStatusMsg != NULL )
   {
      DalocOrdBuf(gStoredTsiDriverStatusMsg);
      gStoredTsiDriverStatusMsg = NULL;
   }
   if ( gStoredDspBootMsg != NULL )
   {
      DalocOrdBuf(gStoredDspBootMsg);
      gStoredDspBootMsg = NULL;
   } 
   /* Bug Fixed - Mantis#3783 : End */

   if ((( gMgsSmmDspBootFlag == TRUE) &&
            ( gMgsSmmTsiRspFlag == FALSE )) ||
         (gMgsWaitForRspFlg==MGS_WT_FOR_MGS_DSP_INIT_RESP))
   {
      gMgsWaitForRspFlg = MGS_NO_WAIT;


      if (( gMgsSmmDspBootFlag == TRUE) && ( gMgsSmmTsiRspFlag == FALSE ))
      {
         LOG_PRINT(LOG_INFO,"Time out for MGS_BOOT_TEST_MSG");
      }
      else 
      {
         LOG_PRINT(LOG_INFO,"Time out for MGS_WT_FOR_MGS_DSP_INIT_RESP");
         LOG_PRINT(LOG_INFO,"gCfgState is [%d]", gCfgState);
      }

   }
   else if (gMgsWaitForRspFlg==MGS_WT_FOR_MGS_DSP_INIT_RESP)
   {
      LOG_PRINT(LOG_INFO,"Time out for MGS_WT_FOR_MGS_TRAU_START_RESP");
   }
   else if (( gMgsSmmDspBootFlag == FALSE) &&
            ( gMgsSmmTsiRspFlag == TRUE ))
      {
         gMgsWaitForRspFlg = MGS_NO_WAIT;

         LOG_PRINT(LOG_INFO," Time out for MGS_WT_FOR_MGS_TRAU_DRIVER_INIT_STATUS");
      }
   else
   {
               LOG_PRINT(LOG_DEBUG,"Timer expired in Invalid State");
   }
   if (gStoredMsgBufPtr !=NULL)
   {
      DalocOrdBuf(gStoredMsgBufPtr);
      gStoredMsgBufPtr=NULL;
   }
}

/* CS4.0 HA Stack Changes : Start */
void scmConfigTimeOutHandler()
{
   setFailCauseInStackObj(CM_ERR_TIMEOUT);
   if (getScmSubProcState() == OAM_SCM_LINK_CONFIG &&
      getScmAction() == SCM_ADD)
   {
      modifyExtTrunkNumTsPeerTrunkNumTsInMccLink(INVALID_E1,INVALID_TS,INVALID_E1,INVALID_TS);
   }
   sendStackProcRespToCm();
}

void   cfgStartTimer(CONST I_S8 *payLoad)
{
   SysAddr slfAddr;
   TmrPayLoad tmrPayLoad;
   gIsTimerRunning = TRUE;
   slfAddr.entity= ENT_OAMS_CFG;
   strcpy(tmrPayLoad.payLoad,payLoad); /* CS4.0 HA Stack Changes*/
   StartTimerFrmwrk(&slfAddr,SCM_CFG_RESP_TIMER,&tmrPayLoad,&tid);
}


void timerTimeoutForBpmCardInfo()
{
   LOG_PRINT(LOG_INFO," Entering timerTimeoutForBpmCardInfo function.... ");
   cfgDbInit();
   LOG_PRINT(LOG_INFO," STARTING CFG INITIALISATION.... ");
   cfgInit();
   startInitializeMGS();
   gCfgState = CFG_INIT_TSI;
   /* Changes For CS2.2 : Start */
   if(gCfgStandbyToActive == I_FALSE)
   { 
      addConfiguredBics();
      addConfiguredTrxs();
   } 
   cfgInitSwMNodeTable();
   sndSwitchConForBicsAtInit();
   if(gCfgStandbyToActive == I_TRUE)
   { 
      sndSwitchConForTrxsAtSwitchOver();
   }
   /* Changes For CS2.2 : End */
   LOG_PRINT(LOG_INFO," Exiting timerTimeoutForBpmCardInfo function.... ");
}
