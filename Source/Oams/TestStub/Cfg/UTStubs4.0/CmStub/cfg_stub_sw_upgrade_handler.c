#include <oamscfg_includes.h>
#include <cfg_stub_sw_upgrade_handler.h>

#define CFG_RESET    0xffff
#define CFG_INIT_MGS_START    0xfffE
extern int gTestCaseCompleted;

void cfgStubSendDSmmMgsuDriverInitStatus(I_U32 );
void cfgStubSendDTrauMgsuDriverInitStatus(I_U32 );
void cfgStubSendDTrauMgsuTrauInitResp();
I_S32 cfgStubSendCmMessage(  void *buff,I_U32 size,I_U32 MessageType );
I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_U16 msgType, I_U8 subType);
void cfgUpdateBssAdminState(I_U32);
void cfgUpdateBicStatusTable(I_U32);
void cfgUpdateTrxTable(I_U32);
void cfgUpdateTrxTsTeiTable(I_U32);
void cfgPopulatePhysicalTrxTable();
void cfgPopulateChnGrpTable(I_U32,I_U32,I_U32);
void cfgDeleteChnGrpTable(I_U32,I_U32);
void cfgPopulateArfcnListTable();



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgTrauHndlr1()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgTrauHndlr1 \n"); 
      testInitiation =0;
      cfgPopulateTrauConfigTable();
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TSM_TSI_DRIVER_INIT_STS:");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_DRIVER_INIT_STATUS:");
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Received OAMS_CFG_AFH_ALARM_IND::");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_UP_ALM)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_UP_ALM");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"Received Incorrect Alarm Id");
               }
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:");
               gTestCaseCompleted = 1; 
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgTrauHndlr2()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgTrauHndlr2:"); 
      testInitiation =0;
      cfgPopulateTrauConfigTable();
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TSM_TSI_DRIVER_INIT_STS:");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_FAILURE);
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_DRIVER_INIT_STATUS:");
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Received OAMS_CFG_AFH_ALARM_IND::");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_UP_ALM)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_UP_ALM");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"Received Incorrect Alarm Id");
               }
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:");
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgTrauHndlr3()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgTrauHndlr3:"); 
      testInitiation =0;
      cfgPopulateTrauConfigTable();
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TSM_TSI_DRIVER_INIT_STS:");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_DRIVER_INIT_STATUS:");
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_FAILURE);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Received OAMS_CFG_AFH_ALARM_IND::");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_UP_ALM)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_UP_ALM");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"Received Incorrect Alarm Id");
               }
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:");
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgTrauHndlr4()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgTrauHndlr4:"); 
      testInitiation =0;
      cfgPopulateTrauConfigTable();
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TSM_TSI_DRIVER_INIT_STS:");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_DRIVER_INIT_STATUS:");
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Not Send MGS_TRAU_INIT_RESP:");
                  //cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Received OAMS_CFG_AFH_ALARM_IND::");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_UP_ALM)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_UP_ALM");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"Received Incorrect Alarm Id");
               }
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:");
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgTrauHndlr5()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgTrauHndlr5:"); 
      testInitiation =0;
      cfgPopulateTrauConfigTable();
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TSM_TSI_DRIVER_INIT_STS:");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  LOG_PRINT(LOG_INFO," Not Send MGS_TRAU_DRIVER_INIT_STATUS:");
                  //cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_FAILURE);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Received OAMS_CFG_AFH_ALARM_IND::");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_UP_ALM)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_UP_ALM");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"Received Incorrect Alarm Id");
               }
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:");
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgTrauHndlr6()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgTrauHndlr6:"); 
      testInitiation =0;
      cfgPopulateTrauConfigTable();
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:");
                  LOG_PRINT(LOG_INFO," Not Send MGS_TSM_TSI_DRIVER_INIT_STS:");
                  //cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_DRIVER_INIT_STATUS:");
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_FAILURE);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_AFH_ALARM_IND:
            {
               OamsCfgAfhSysAlarm *OamsCfgAfhSysAlarmPtr=(OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Received OAMS_CFG_AFH_ALARM_IND::");
               if ( OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TSI_TRAU_INITIALIZATION_FAILED)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TSI_TRAU_INITIALIZATION_FAILED");
               }
               else if (OamsCfgAfhSysAlarmPtr->sysAlarm.sysalarmId == TRAU_UP_ALM)
               {
                  LOG_PRINT(LOG_INFO,"Received Alarm  TRAU_UP_ALM");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"Received Incorrect Alarm Id");
               }
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:");
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeInit2()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */
   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgSwUpgradeInit2 \n"); 
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:\n");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:\n");
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
               OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
               AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)gCfgMsgBuf;
               OamOilCfgAvailableReleasesResp AvailRelRespBuff;
               if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BSC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BSC;
                  AvailRelRespBuff.numVersion = 3;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"123.78.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"123.0.201");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[2],"123.211.0");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-1.0.6",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BIC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BIC;
                  AvailRelRespBuff.numVersion = 3;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"23.8.20");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-2.1.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"111.1.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-2.0.7",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[2],"22.11.110");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-2.0.9",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_TRX:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_TRX;
                  AvailRelRespBuff.numVersion = 3;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"332.28.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-3.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"1.210.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-3.2.7",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[2],"13.231.0");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-3.0.6",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
            }
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeInit3()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */
   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgSwUpgradeInit3 \n"); 
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:\n");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:\n");
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
               OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
               AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)gCfgMsgBuf;
               OamOilCfgAvailableReleasesResp AvailRelRespBuff;
               if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BSC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BSC;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"123.78.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"123.0.201");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BIC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BIC;
                  AvailRelRespBuff.numVersion = 3;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"23.8.20");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-2.1.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"111.1.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-2.0.7",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[2],"22.11.110");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-2.0.9",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_TRX:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_TRX;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"332.28.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-3.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"1.210.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-3.2.7",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
            }
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeInit4()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */
   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgSwUpgradeInit4 \n"); 
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:\n");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:\n");
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
               OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
               AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)gCfgMsgBuf;
               OamOilCfgAvailableReleasesResp AvailRelRespBuff;
               if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BSC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BSC;
                  AvailRelRespBuff.numVersion = 1;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"123.78.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BIC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BIC;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"23.8.20");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-2.1.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"111.1.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-2.0.7",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_TRX:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_TRX;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"332.28.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-3.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"1.210.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-3.2.7",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
            }
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeInit5()
{
   static int testInitiation =1;

   /* TRAU_INIT_RESP */
   /* For this test case we need to run stub first */
   if ( testInitiation )
   {
      LOG_PRINT(LOG_INFO,"Executing CfgSwUpgradeInit5 "); 
      testInitiation =0;
      cfgStubSendCmMessage(NULL,0,CFG_INIT_MGS_START);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case EXT_TSM_MSG :
            {
               MgsuSmmSmmInitTrigger *mgsuSmmSmmInitTriggerPtr = NULL;
               mgsuSmmSmmInitTriggerPtr =(MgsuSmmSmmInitTrigger *)gCfgMsgBuf;
               if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_SMM_INIT_TRIGGER)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_SMM_INIT_TRIGGER:\n");
                  cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
                  cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
               }
               else if(mgsuSmmSmmInitTriggerPtr->messageId == MGS_TRAU_INIT_REQ)
               {
                  LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:");
                  LOG_PRINT(LOG_INFO," Sending MGS_TRAU_INIT_RESP:");
                  cfgStubSendDTrauMgsuTrauInitResp();
               }
               else
                  LOG_PRINT(LOG_INFO,"Incorrect message Id");
            }
            break;
         case BSC_API_GET_CARDINFOTABLE :
            {
               CardInfoTableApi CardInfoTableApiBuff={0};
               LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
               cfgStubSendCmMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),BSC_API_GET_CARDINFOTABLE);
            }
            break;
         case OAMS_CFG_GRHM_START_STATIC_SWITCHING:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_STATIC_SWITCHING:\n");
            }
         case MGS_TRAU_INIT_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived MGS_TRAU_INIT_REQ:\n");
               cfgStubSendDTrauMgsuTrauInitResp();
            }
            break;
         case OAMS_CFG_GRHM_START_CHAN_ALLOC:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_GRHM_START_CHAN_ALLOC:\n");
            }
            break;
         case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
            {
               LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
               OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
               AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)gCfgMsgBuf;
               OamOilCfgAvailableReleasesResp AvailRelRespBuff;
               if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BSC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BSC;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"123.78.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"220.18.110");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.2",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BIC:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BIC;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"23.8.20");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-2.1.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"111.1.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-2.0.7",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
               else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX)
               {
                  LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_TRX:\n");
                  AvailRelRespBuff.nodeType = SYS_NODE_TYPE_TRX;
                  AvailRelRespBuff.numVersion = 2;
                  strcpy(AvailRelRespBuff.availSwVersions[0],"332.28.120");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-3.0.1",CMD_PARAM_MAX_SIZE);
                  strcpy(AvailRelRespBuff.availSwVersions[1],"1.210.1");
                  memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-3.2.7",CMD_PARAM_MAX_SIZE);
                  cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
               }
            }
         default:
            LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) gCfgMsgBuf)->msgType));
            break;
      }
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr1()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr1  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"132.242.5");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr2()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr2  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"132.242.256");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr3()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr3  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"132.2422.25");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr4()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr4  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"132.22");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr5()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr5  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"132.22.21.23");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr6()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr6  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"032.002.23");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr7()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr7  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,".72.23");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr8()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr8  : Sw Offer Request\n");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"10.11.12",0,0);
      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"10.11.12");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

void CfgSwUpgradeHndlr9()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr9  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"10.11.12");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr10()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr10  : Sw Offer Request\n");

      cfgPopulateSwMOfferTable(SYS_NODE_TYPE_BSC,"101.11.12");
      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"10.11.12");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr11()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr11  : Sw Offer Request\n");

      cfgPopulateSwMOfferTable(SYS_NODE_TYPE_BSC,"10.11.12");
      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"10.11.12");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1; 
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1; 
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr12()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr12  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      strcpy(swMOfferTableBuff.upgradeVersion,"100.101.102");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/gur15644/Sw_Rel_SI/Bic/bic321.tar",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      OamOilCfgAvailableReleasesResp AvailRelRespBuff;
      AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BIC;
      AvailRelRespBuff.numVersion = 0;
      //cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_OFFER_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
               OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)gCfgMsgBuf;
               OamOilCfgSwOfferResp swOfferRespBuff;
               swOfferRespBuff.upgradeOfferResult = UPGRADE_OFFER_SUCCESSFUL;
               swOfferRespBuff.nodeType = swOfferReqPtr->nodeType;
               strcpy(swOfferRespBuff.upgradeVersion,swOfferReqPtr->upgradeVersion);
               memcpy(swOfferRespBuff.binaryPath,"/home/gur15644/Sw_Rel_SI/Bic/bic321.tar",CMD_PARAM_MAX_SIZE);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
               cfgStubSendMessage(&swOfferRespBuff,sizeof(OamOilCfgSwOfferResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);    
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr13()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr13  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"200.201.202");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_OFFER_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
               OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)gCfgMsgBuf;
               OamOilCfgSwOfferResp swOfferRespBuff;
               swOfferRespBuff.upgradeOfferResult = UPGRADE_OFFER_SUCCESSFUL;
               swOfferRespBuff.nodeType = swOfferReqPtr->nodeType;
               memcpy(swOfferRespBuff.upgradeVersion,swOfferReqPtr->upgradeVersion,MAX_SW_VERSION_LENGTH);
               memcpy(swOfferRespBuff.binaryPath,"/home/SoftRelease/Rel-1.0.2",CMD_PARAM_MAX_SIZE);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
               cfgStubSendMessage(&swOfferRespBuff,sizeof(OamOilCfgSwOfferResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);    
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr14()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr14  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMOfferTableBuff.upgradeVersion,"50.51.52");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-2.0.1",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_OFFER_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
               OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)gCfgMsgBuf;
               OamOilCfgSwOfferResp swOfferRespBuff;
               swOfferRespBuff.upgradeOfferResult = ERROR_WRITING_TO_FLASH;
               swOfferRespBuff.nodeType = swOfferReqPtr->nodeType;
               strcpy(swOfferRespBuff.upgradeVersion,swOfferReqPtr->upgradeVersion);
               memcpy(swOfferRespBuff.binaryPath,"/home/SoftRelease/Rel-2.0.1",CMD_PARAM_MAX_SIZE);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
               cfgStubSendMessage(&swOfferRespBuff,sizeof(OamOilCfgSwOfferResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);    
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr15()
{
   static int testInitiation =1;
   SwMOfferTableApi swMOfferTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr15  : Sw Offer Request\n");

      swMOfferTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      strcpy(swMOfferTableBuff.upgradeVersion,"150.151.152");
      swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
      memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-2.0.2",CMD_PARAM_MAX_SIZE);
      memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
      memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
      memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
      swMOfferTableBuff.size = 2048;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      cfgStubSendCmMessage(&swMOfferTableBuff,sizeof(SwMOfferTableApi),BSC_API_SET_SWMOFFERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..\n");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_OFFER_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
               OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)gCfgMsgBuf;
               OamOilCfgSwOfferResp swOfferRespBuff;
               swOfferRespBuff.upgradeOfferResult = ERROR_SPACE_UNAVAILABLE;
               swOfferRespBuff.nodeType = swOfferReqPtr->nodeType;
               strcpy(swOfferRespBuff.upgradeVersion,swOfferReqPtr->upgradeVersion);
               memcpy(swOfferRespBuff.binaryPath,"/home/SoftRelease/Rel-2.0.2",CMD_PARAM_MAX_SIZE);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
               cfgStubSendMessage(&swOfferRespBuff,sizeof(OamOilCfgSwOfferResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);    
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr16()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr16  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr17()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr17  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.302");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr18()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr18  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.3020");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr19()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr19  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr20()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr20  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr21()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr21  : Set for SwMNode Table");
      cfgUpdateBssAdminState(1);
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgUpdateBssAdminState(0);
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr22()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr22  : Set for SwMNode Table");
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr23()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr23  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,1);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr24()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr24  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_BSC,1);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr25()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr25  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"50.51.52",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"50.51.52");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"50.51.52");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr26()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr26  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr27()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr27  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,SW_ACTIVATION_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr28()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr28  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_ACT_REQ from Cfg..");
               OamsCfgOilSwActReq *swActReqPtr = (OamsCfgOilSwActReq *)gCfgMsgBuf;
               OamOilCfgSwActResp swActRespBuff;
               swActRespBuff.actResult = ACTIVATION_SUCCESSFUL;
               strcpy(swActRespBuff.actVersion,swActReqPtr->actVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_ACT_RESP..");
               cfgStubSendMessage(&swActRespBuff,sizeof(OamOilCfgSwActResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_ACT_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr29()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr29  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_ACT_REQ from Cfg..");
               OamsCfgOilSwActReq *swActReqPtr = (OamsCfgOilSwActReq *)gCfgMsgBuf;
               OamOilCfgSwActResp swActRespBuff;
               swActRespBuff.actResult = UNABLE_TO_ACTIVATE;
               strcpy(swActRespBuff.actVersion,swActReqPtr->actVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_ACT_RESP..");
               cfgStubSendMessage(&swActRespBuff,sizeof(OamOilCfgSwActResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_ACT_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr30()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr30  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,1,"10.11.12","100.101.102","200.201.202","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      swMNodeTableBuff.nodeIdentity = 1;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_ACT_REQ from Cfg..");
               OamsCfgOilSwActReq *swActReqPtr = (OamsCfgOilSwActReq *)gCfgMsgBuf;
               OamOilCfgSwActResp swActRespBuff;
               swActRespBuff.actResult = ERROR_ACTIVATION_FAILURE;
               strcpy(swActRespBuff.actVersion,swActReqPtr->actVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_ACT_RESP..");
               cfgStubSendMessage(&swActRespBuff,sizeof(OamOilCfgSwActResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_ACT_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"\n Not Expected Message\n");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr31()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr31  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr32()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr32  : Set for SwMNode Table");
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr33()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr33  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,1);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr34()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr34  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_BIC,101);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr35()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr35  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"10.11.12",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"10.11.12");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"10.11.12");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr36()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr36  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr37()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr37  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,SW_ACTIVATION_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr38()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr38  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_BIC,102,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_BIC,102);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr39()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr39  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,10,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,11,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,12,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,13,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,10);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,11);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,12);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,13);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr40()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr40  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,10,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,11,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,12,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,13,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,14,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,15,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,16,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,17,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,18,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,19,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,30,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,31,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,32,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,33,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,34,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,35,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,36,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,37,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,38,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,39,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,40,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,41,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,10);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,11);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,12);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,13);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,14);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,15);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,16);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,17);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,18);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,19);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,30);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,31);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,32);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,33);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,34);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,35);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,36);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,37);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,38);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,39);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,40);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,41);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr41()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr41  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      cfgUpdateBicStatusTable(0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
      cfgUpdateBicStatusTable(1);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr42()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr42  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_DNLD_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_DNLD_REQ from Cfg..");
               OamsCfgSwmhSwDnldReq *swDnldReqPtr = (OamsCfgSwmhSwDnldReq *)gCfgMsgBuf;
               OamsSwmhCfgSwDnldAck swDnldAckBuff;
               swDnldAckBuff.nodeType = swDnldReqPtr->nodeType;
               swDnldAckBuff.nodeIdentity = swDnldReqPtr->nodeIdentity;
               strcpy(swDnldAckBuff.swVersion,swDnldReqPtr->swVersion);
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_DNLD_ACK..");
               cfgStubSendMessage(&swDnldAckBuff,sizeof(OamsSwmhCfgSwDnldAck),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_DNLD_ACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr43()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr43  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_DNLD_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_DNLD_REQ from Cfg..");
               OamsCfgSwmhSwDnldReq *swDnldReqPtr = (OamsCfgSwmhSwDnldReq *)gCfgMsgBuf;
               OamsSwmhCfgSwDnldNack swDnldNackBuff;
               swDnldNackBuff.nodeType = swDnldReqPtr->nodeType;
               swDnldNackBuff.nodeIdentity = swDnldReqPtr->nodeIdentity;
               strcpy(swDnldNackBuff.swVersion,swDnldReqPtr->swVersion);
               swDnldNackBuff.nackCause = CAUSE_RESOURCE_NOT_AVAILABLE;
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_DNLD_NACK..");
               cfgStubSendMessage(&swDnldNackBuff,sizeof(OamsSwmhCfgSwDnldNack),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_DNLD_NACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr44()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr44  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr45()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr45  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_BIC,101);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr46()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr46  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"10.11.12",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"10.11.12");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"10.11.12");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr47()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr47  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr48()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr48  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,SW_ACTIVATION_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr49()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr49  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      cfgUpdateBicStatusTable(0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
      cfgUpdateBicStatusTable(1);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr50()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr50  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_ACT_REQ from Cfg..");
               OamsCfgSwmhSwActReq *swActReqPtr = (OamsCfgSwmhSwActReq *)gCfgMsgBuf;
               OamsSwmhCfgSwActAck swActAckBuff;
               swActAckBuff.nodeType = swActReqPtr->nodeType;
               swActAckBuff.nodeIdentity = swActReqPtr->nodeIdentity;
               strcpy(swActAckBuff.swVersion,swActReqPtr->swVersion);
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_ACT_ACK..");
               cfgStubSendMessage(&swActAckBuff,sizeof(OamsSwmhCfgSwActAck),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_ACT_ACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr51()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr51  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,101,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      swMNodeTableBuff.nodeIdentity = 101;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_ACT_REQ from Cfg..");
               OamsCfgSwmhSwActReq *swActReqPtr = (OamsCfgSwmhSwActReq *)gCfgMsgBuf;
               OamsSwmhCfgSwActNack swActNackBuff;
               swActNackBuff.nodeType = swActReqPtr->nodeType;
               swActNackBuff.nodeIdentity = swActReqPtr->nodeIdentity;
               strcpy(swActNackBuff.swVersion,swActReqPtr->swVersion);
               swActNackBuff.nackCause = OAMS_CAUSE_FILE_SYSTEM_ERROR;  
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_ACT_NACK..");
               cfgStubSendMessage(&swActNackBuff,sizeof(OamsSwmhCfgSwActNack),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_ACT_NACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"200.201.202");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr52()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr52  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr53()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr53  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgUpdateTrxTable(1);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgUpdateTrxTable(0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr54()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr54  : Set for SwMNode Table");
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr55()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr55  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,1);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr56()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr56  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,21);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr57()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr57  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"10.11.12",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"10.11.12");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"10.11.12");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr58()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr58  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr59()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr59  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,SW_ACTIVATION_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr60()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr60  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,25,50,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,36,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,37,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,38,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,39,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,40,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,41,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 25;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,25);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,36);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,37);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,38);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,39);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,40);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,41);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr61()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr61  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,10,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,11,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,12,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,13,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,10);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,11);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,12);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,13);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr62()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr62  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_BIC,102,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,10,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,11,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,12,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_BIC,102);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,10);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,11);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,12);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr63()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr63  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,10,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,11,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,12,1,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,13,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,14,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,15,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,16,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,17,2,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,18,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,19,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,30,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,31,3,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,32,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,33,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,34,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,35,4,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,36,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,37,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,38,50,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,39,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,40,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,41,51,"10.11.12","200.201.202","","",0,SW_DOWNLOAD_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,10);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,11);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,12);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,13);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,14);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,15);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,16);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,17);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,18);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,19);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,30);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,31);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,32);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,33);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,34);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,35);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,36);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,37);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,38);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,39);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,40);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,41);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr64()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr64  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgUpdateTrxTsTeiTable(0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgUpdateTrxTsTeiTable(1);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr65()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr65  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_DNLD_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_DNLD_REQ from Cfg..");
               OamsCfgSwmhSwDnldReq *swDnldReqPtr = (OamsCfgSwmhSwDnldReq *)gCfgMsgBuf;
               OamsSwmhCfgSwDnldAck swDnldAckBuff;
               swDnldAckBuff.nodeType = swDnldReqPtr->nodeType;
               swDnldAckBuff.nodeIdentity = swDnldReqPtr->nodeIdentity;
               memcpy(swDnldAckBuff.swVersion,swDnldReqPtr->swVersion,MAX_SW_VERSION_LENGTH);
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_DNLD_ACK..");
               cfgStubSendMessage(&swDnldAckBuff,sizeof(OamsSwmhCfgSwDnldAck),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_DNLD_ACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr66()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr66  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_DOWNLOAD;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_DNLD_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_DNLD_REQ from Cfg..");
               OamsCfgSwmhSwDnldReq *swDnldReqPtr = (OamsCfgSwmhSwDnldReq *)gCfgMsgBuf;
               OamsSwmhCfgSwDnldNack swDnldNackBuff;
               swDnldNackBuff.nodeType = swDnldReqPtr->nodeType;
               swDnldNackBuff.nodeIdentity = swDnldReqPtr->nodeIdentity;
               swDnldNackBuff.nackCause = OAMS_CAUSE_LOAD_DATA_INIT_ACK_TIMER_EXPIRY;
               strcpy(swDnldNackBuff.swVersion,swDnldReqPtr->swVersion);
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_DNLD_NACK..");
               cfgStubSendMessage(&swDnldNackBuff,sizeof(OamsSwmhCfgSwDnldNack),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_DNLD_NACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr67()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr67  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr68()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr68  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgUpdateTrxTable(1);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
      cfgUpdateTrxTable(0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr69()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr69  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgDeleteSwMNodeTable(SYS_NODE_TYPE_TRX,21);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr70()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr70  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"10.11.12",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"10.11.12");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"10.11.12");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr71()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr71  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"100.101.102");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr72()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr72  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,SW_ACTIVATION_IN_PROGRESS);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr73()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr73  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      cfgUpdateTrxTsTeiTable(0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted = 1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted = 1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
      cfgUpdateTrxTsTeiTable(1);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr74()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr74  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_ACT_REQ from Cfg..");
               OamsCfgSwmhSwActReq *swActReqPtr = (OamsCfgSwmhSwActReq *)gCfgMsgBuf;
               OamsSwmhCfgSwActAck swActAckBuff;
               swActAckBuff.nodeType = swActReqPtr->nodeType;
               swActAckBuff.nodeIdentity = swActReqPtr->nodeIdentity;
               memcpy(swActAckBuff.swVersion,swActReqPtr->swVersion,MAX_SW_VERSION_LENGTH);
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_ACT_ACK..");
               cfgStubSendMessage(&swActAckBuff,sizeof(OamsSwmhCfgSwActAck),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_ACT_ACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr75()
{
   static int testInitiation =1;
   SwMNodeTableApi swMNodeTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr75  : Set for SwMNode Table");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,21,1,"10.11.12","200.201.202","","",0,0);
      swMNodeTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      swMNodeTableBuff.nodeIdentity = 21;
      strcpy(swMNodeTableBuff.swVersionNew,"200.201.202");
      swMNodeTableBuff.swAction = SW_ACTIVATE;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_SWMNODETABLE..");
      cfgStubSendCmMessage(&swMNodeTableBuff,sizeof(SwMNodeTableApi),BSC_API_SET_SWMNODETABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_SWMH_SW_ACT_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_ACT_REQ from Cfg..");
               OamsCfgSwmhSwActReq *swActReqPtr = (OamsCfgSwmhSwActReq *)gCfgMsgBuf;
               OamsSwmhCfgSwActNack swActNackBuff;
               swActNackBuff.nodeType = swActReqPtr->nodeType;
               swActNackBuff.nodeIdentity = swActReqPtr->nodeIdentity;
               strcpy(swActNackBuff.swVersion,swActReqPtr->swVersion);
               swActNackBuff.nackCause = OAMS_CAUSE_ACT_SW_VERSION_MISMATCH;
               LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_ACT_NACK..");
               cfgStubSendMessage(&swActNackBuff,sizeof(OamsSwmhCfgSwActNack),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_ACT_NACK,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"200.201.202");
               break;
            }
         default:
            LOG_PRINT(LOG_INFO," Not Expected Message");
            break;
      }  
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr76()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr76  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr77()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr77  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.501.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr78()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr78  : Del for SwM Table");

      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr79()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr79  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,1);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr80()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr80  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"10.11.12",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"10.11.12");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"10.11.12");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr81()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr81  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,SW_ACTIVATION_IN_PROGRESS);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_BSC,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr82()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr82  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr83()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr83  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",1,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_TRX,"100.101.102");
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr84()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr84  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BIC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BIC,1,1,"10.11.12","100.101.102","200.201.202","",0,SW_ACTIVATION_IN_PROGRESS);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BIC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"TEST CASE PASS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  LOG_PRINT(LOG_INFO,"TEST CASE FAIL");
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteSwMTable(SYS_NODE_TYPE_BIC,"100.101.102");
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr85()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr85  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,1,0,"10.11.12","100.101.102","","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_DEL_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
               OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)gCfgMsgBuf;
               OamOilCfgSwDelResp swDelRespBuff;
               swDelRespBuff.versionDelResult = DELETE_SUCCESSFUL;
               swDelRespBuff.nodeType = swDelReqPtr->nodeType;
               strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
               cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr86()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr86  : Del for SwM Table");

      cfgPopulateSwMOfferTable(SYS_NODE_TYPE_TRX,"100.101.102");
      cfgPopulateSwMTable(SYS_NODE_TYPE_TRX,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_TRX,1,0,"10.11.12","100.101.102","","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_TRX;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_DEL_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
               OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)gCfgMsgBuf;
               OamOilCfgSwDelResp swDelRespBuff;
               swDelRespBuff.versionDelResult = ERROR_VERSION_NOT_PRESENT;
               swDelRespBuff.nodeType = swDelReqPtr->nodeType;
               strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
               cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr87()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr87  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_DEL_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
               OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)gCfgMsgBuf;
               OamOilCfgSwDelResp swDelRespBuff;
               swDelRespBuff.versionDelResult = DELETE_SUCCESSFUL;
               swDelRespBuff.nodeType = swDelReqPtr->nodeType;
               strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
               cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr88()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr88  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"200.201.202",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"200.201.202");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_DEL_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
               OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)gCfgMsgBuf;
               OamOilCfgSwDelResp swDelRespBuff;
               swDelRespBuff.versionDelResult = DELETE_SUCCESSFUL;
               swDelRespBuff.nodeType = swDelReqPtr->nodeType;
               memcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion,MAX_SW_VERSION_LENGTH);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
               cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr89()
{
   static int testInitiation =1;

   SwMTableApi swMTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr89  : Del for SwM Table");

      cfgPopulateSwMTable(SYS_NODE_TYPE_BSC,"100.101.102",0,0);
      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      swMTableBuff.nodeType = SYS_NODE_TYPE_BSC;
      strcpy(swMTableBuff.swVersion,"100.101.102");
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_SWMTABLE..");
      cfgStubSendCmMessage(&swMTableBuff,sizeof(SwMTableApi),BSC_API_DEL_SWMTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
               }
            }
            break;
         case OAMS_CFG_OIL_SW_DEL_REQ:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
               OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)gCfgMsgBuf;
               OamOilCfgSwDelResp swDelRespBuff;
               swDelRespBuff.versionDelResult = ERROR_CONNECTING_UA_CP;
               swDelRespBuff.nodeType = swDelReqPtr->nodeType;
               strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
               LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
               cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
               break;
            }
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"AlarmReason : %d ",sysAlarmPtr->sysAlarm.alarmReason);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr90()
{
   static int testInitiation =1;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr90 : ");

      OamsSwmhCfgAlarmInd alarmIndBuff;
      alarmIndBuff.sysAlarm.sysalarmId = EVENT_SW_VERSION_MISMATCH; 
      alarmIndBuff.sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
      alarmIndBuff.sysAlarm.info3 = SYS_NODE_TYPE_BIC;
      alarmIndBuff.sysAlarm.infoStrLen = sprintf(alarmIndBuff.sysAlarm.infoString,"String as recieved from SWMH");
      LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_ALARM_IND..");
      cfgStubSendMessage(&alarmIndBuff,sizeof(OamsSwmhCfgAlarmInd),ENT_OAMS_SWMH,OAMS_SWMH_CFG_ALARM_IND,0);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)gCfgMsgBuf;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
               break;
            }
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr91()
{
   static int testInitiation =1;

   BicTableApi bicTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr91  : Set for Bic Table");

      bicTableBuff.bicId = 107; 
      bicTableBuff.numTrx = 2;
      bicTableBuff.e1Id = 2;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_BICTABLE..");
      cfgStubSendCmMessage(&bicTableBuff,sizeof(BicTableApi),BSC_API_SET_BICTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr91 : Success");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/

/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr92()
{
   static int testInitiation =1;

   TrxTableApi trxTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr92  : Set for Trx Table");

      trxTableBuff.ptrxId = 20;
      trxTableBuff.adminState = 0;
      trxTableBuff.trxLocation = 2; 
      trxTableBuff.bicId = 107;
      trxTableBuff.antennaID = 100;
      trxTableBuff.trxPos = 2;
      trxTableBuff.rfPathGain = 100;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_TRXTABLE..");
      cfgStubSendCmMessage(&trxTableBuff,sizeof(TrxTableApi),BSC_API_SET_TRXTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr92 : Success");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr93()
{
   static int testInitiation =1;

   TrxTableApi trxTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr93  : Set for Trx Table");

      trxTableBuff.ptrxId = 29;
      trxTableBuff.adminState = 0;
      trxTableBuff.trxLocation = 1; 
      trxTableBuff.bicId = 0;
      trxTableBuff.antennaID = 100;
      trxTableBuff.trxPos = 2;
      trxTableBuff.rfPathGain = 100;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_TRXTABLE..");
      cfgStubSendCmMessage(&trxTableBuff,sizeof(TrxTableApi),BSC_API_SET_TRXTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr93 : Success");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr94()
{
   LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr94  : Del Bic Response");

   OamsBichCfgDelBicResp delBicRespBuff;
   delBicRespBuff.bicId = 107;
	 delBicRespBuff.result = OAMS_RSLT_SUCCESS;
   LOG_PRINT(LOG_INFO,"Sending OAMS_BICH_CFG_DEL_BIC_RESP..");
   cfgStubSendMessage(&delBicRespBuff,sizeof(OamsBichCfgDelBicResp),ENT_OAMS_BICH,OAMS_BICH_CFG_DEL_BIC_RESP,0);
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr95()
{
   LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr95  : Del Trx Response");

   OamsTrxhCfgDelTrxResp delTrxRespBuff;
   delTrxRespBuff.ptrxId = 20;
	 delTrxRespBuff.result = OAMS_RSLT_SUCCESS;
   LOG_PRINT(LOG_INFO,"Sending OAMS_TRXH_CFG_DEL_TRX_RESP..");
   cfgStubSendMessage(&delTrxRespBuff,sizeof(OamsTrxhCfgDelTrxResp),ENT_OAMS_TRXH,OAMS_TRXH_CFG_DEL_TRX_RESP,0);
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr96()
{
   static int testInitiation =1;

   BssTableApi bssTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr96  : Unlock BSS");

      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,SW_ACTIVATION_IN_PROGRESS);
      bssTableBuff.bscId = 1;
      bssTableBuff.adminState = 1;
		  bssTableBuff.gprsEnabled = FALSE;
			bssTableBuff.bssReset = FALSE;
			bssTableBuff.callReestablishmentInd =ALLOWED;
			bssTableBuff.attInd = ALLOWED;
			bssTableBuff.t3212 = 20;
			bssTableBuff.mcc = 33;
			bssTableBuff.mnc = 33;
			bssTableBuff.ncc = 2;
			bssTableBuff.nccPermitted = 111;
			bssTableBuff.dtxDnLinkInd = 0;
			bssTableBuff.dtxUpLinkInd = 0;
			bssTableBuff.minChannelGap = 10;
			bssTableBuff.txInteger = 1;
			bssTableBuff.radioLinkTimeout = 1;
			bssTableBuff.maxRetrans = 1;
			bssTableBuff.shutdownTimer = 10;
			bssTableBuff.cicMaster = 0;
			bssTableBuff.tHandRqd = 5;
			bssTableBuff.bssapTimer8 = 20;
			bssTableBuff.bssapTimer7 = 10;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_BSSTABLE..");
      cfgStubSendCmMessage(&bssTableBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/

#if 0
/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr97()
{
   static int testInitiation =1;

   PhysicalTrxPreconfiguredTableApi physicalTrxPreconfigBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr97  : Unlock TRX");

      cfgPopulatePhysicalTrxTable();
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,4,1,"10.11.12","100.101.102","","",0,SW_DOWNLOAD_IN_PROGRESS);
      physicalTrxPreconfigBuff.ptrxId = 4;
      physicalTrxPreconfigBuff.adminState = 1;
      physicalTrxPreconfigBuff.tei = 2;
      physicalTrxPreconfigBuff.antennaId = 1;
      physicalTrxPreconfigBuff.e1Id =1 ;
      physicalTrxPreconfigBuff.startE1Timeslot = 10;
      physicalTrxPreconfigBuff.rackId = 11;
      physicalTrxPreconfigBuff.slotId = 1;

      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE..");
      cfgStubSendCmMessage(&physicalTrxPreconfigBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr98()
{
   static int testInitiation =1;

   PhysicalTrxPreconfiguredTableApi physicalTrxPreconfigBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr98  : Unlock TRX");

      cfgPopulatePhysicalTrxTable();
      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,4,1,"10.11.12","100.101.102","","",0,SW_ACTIVATION_IN_PROGRESS);
      physicalTrxPreconfigBuff.ptrxId = 4;
      physicalTrxPreconfigBuff.adminState = 1;
      physicalTrxPreconfigBuff.tei = 2;
      physicalTrxPreconfigBuff.antennaId = 1;
      physicalTrxPreconfigBuff.e1Id =1 ;
      physicalTrxPreconfigBuff.startE1Timeslot = 10;
      physicalTrxPreconfigBuff.rackId = 11;
      physicalTrxPreconfigBuff.slotId = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE..");
      cfgStubSendCmMessage(&physicalTrxPreconfigBuff,sizeof(PhysicalTrxPreconfiguredTableApi),BSC_API_SET_PHYSICALTRXPRECONFIGUREDTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/
#endif


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr97()
{
   static int testInitiation =1;

   TrxTableApi trxTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr97  : Unlock TRX");

      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,4,1,"10.11.12","100.101.102","","",0,SW_DOWNLOAD_IN_PROGRESS);
      trxTableBuff.ptrxId = 4;
      trxTableBuff.adminState = 1;
      trxTableBuff.trxLocation = 2;
      trxTableBuff.bicId = 1;
      trxTableBuff.antennaID =100 ;
      trxTableBuff.trxPos = 1;
      trxTableBuff.rfPathGain = 11;

      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_TRXTABLE..");
      cfgStubSendCmMessage(&trxTableBuff,sizeof(TrxTableApi),BSC_API_SET_TRXTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgSwUpgradeHndlr98()
{
   static int testInitiation =1;

   TrxTableApi trxTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgSwUpgradeHndlr98  : Unlock TRX");

      cfgPopulateSwMNodeTable(SYS_NODE_TYPE_TRX,4,1,"10.11.12","100.101.102","","",0,SW_ACTIVATION_IN_PROGRESS);
      trxTableBuff.ptrxId = 4;
      trxTableBuff.adminState = 1;
      trxTableBuff.trxLocation = 2;
      trxTableBuff.bicId = 1;
      trxTableBuff.antennaID =100 ;
      trxTableBuff.trxPos = 1;
      trxTableBuff.rfPathGain = 11;

      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_TRXTABLE..");
      cfgStubSendCmMessage(&trxTableBuff,sizeof(TrxTableApi),BSC_API_SET_TRXTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr1()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr1  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr2()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr2  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 5;
      hoCtrlTableBuff.windowSizeRxQualH =5;
      hoCtrlTableBuff.windowSizeNcell = 5;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr3()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr3  : Set for HoCtrl Table");

      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 5;
      hoCtrlTableBuff.windowSizeRxQualH =5;
      hoCtrlTableBuff.windowSizeNcell = 5;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr4()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr4  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 4;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr5()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr5  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 2;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr6()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr6  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 0;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr7()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr7  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 64;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr8()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr8  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 8;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr9()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr9  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 2;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr10()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr10  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 1;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr11()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr11  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 5;
      hoCtrlTableBuff.windowSizeRxQualH =6;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr12()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr12  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =1;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr13()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr13  : Set for HoCtrl Table");

      addCellPerTable();
      hoCtrlTableBuff.lac = 3000;
      hoCtrlTableBuff.cellId = 3500;
      hoCtrlTableBuff.enHoLev = 1;   //0
      hoCtrlTableBuff.enHoQual = 1;   //0
      hoCtrlTableBuff.enHoPbgt = 1;  //0
      hoCtrlTableBuff.windowSizeRxLevH = 6;
      hoCtrlTableBuff.windowSizeRxQualH =5;
      hoCtrlTableBuff.windowSizeNcell = 6;
      hoCtrlTableBuff.lRxLevDlH = 10;
      hoCtrlTableBuff.lRxLevUlH = 10;
      hoCtrlTableBuff.lRxQualDlH = 4;
      hoCtrlTableBuff.lRxQualUlH = 4;
      hoCtrlTableBuff.hystH = 4;
      hoCtrlTableBuff.multibandReporting = 1;
      hoCtrlTableBuff.enableIncHo = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_SET_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable();
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr14()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr14  : Del for HoCtrl Table");

      cfgPopulateHoCtrlTable(4500,4000);
      cfgPopulateCellPerTable(4500,4000,0);
      cfgPopulateCellNonPerTable(4500,4000,1);
      hoCtrlTableBuff.lac = 4000;
      hoCtrlTableBuff.cellId = 4500;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_DEL_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDelCellPerTable(4500,4000);
      cfgDelCellNonPerTable(4500,4000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr15()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr15  : Del for HoCtrl Table");

      cfgPopulateHoCtrlTable(4500,4000);
      cfgPopulateCellPerTable(4500,4000,1);
      cfgPopulateCellNonPerTable(4500,4000,0);
      hoCtrlTableBuff.lac = 4000;
      hoCtrlTableBuff.cellId = 4500;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_DEL_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDelCellPerTable(4500,4000);
      cfgDelCellNonPerTable(4500,4000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr16()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr16  : Del for HoCtrl Table");

      cfgPopulateHoCtrlTable(4500,4000);
      cfgPopulateCellPerTable(4500,4000,1);
      cfgPopulateCellNonPerTable(4500,4000,1);
      cfgUpdateBssAdminState(1);
      hoCtrlTableBuff.lac = 4000;
      hoCtrlTableBuff.cellId = 4500;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_DEL_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDelCellPerTable(4500,4000);
      cfgDelCellNonPerTable(4500,4000);
      cfgUpdateBssAdminState(0);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr17()
{
   static int testInitiation =1;

   HoCtrlTableApi hoCtrlTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr17  : Del for HoCtrl Table");

      cfgPopulateHoCtrlTable(4500,4000);
      cfgPopulateCellPerTable(4500,4000,1);
      cfgPopulateCellNonPerTable(4500,4000,1);
      hoCtrlTableBuff.lac = 4000;
      hoCtrlTableBuff.cellId = 4500;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_HOCTRLTABLE..");
      cfgStubSendCmMessage(&hoCtrlTableBuff,sizeof(HoCtrlTableApi),BSC_API_DEL_HOCTRLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE ");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDelCellPerTable(4500,4000);
      cfgDelCellNonPerTable(4500,4000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr18()
{
   static int testInitiation =1;

   BssTableApi bssTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr18  : Unlock BSS");

      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      bssTableBuff.bscId = 1;
      bssTableBuff.adminState = 1; 
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_BSSTABLE..");
      cfgStubSendCmMessage(&bssTableBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr19()
{
   static int testInitiation =1;

   BssTableApi bssTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr19  : Unlock BSS");

      cfgUpdateSwMNodeTable(SYS_NODE_TYPE_BSC,1,0,"10.11.12","100.101.102","200.201.202","",0,0);
      bssTableBuff.bscId = 1;
      bssTableBuff.adminState = 1; 
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_BSSTABLE..");
      cfgStubSendCmMessage(&bssTableBuff,sizeof(BssTableApi),BSC_API_SET_BSSTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr20()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr20  : Unlock Cell");

      cfgPopulateCellPerTable(6500,5000,0);
      cfgPopulateLaTable(5000);
      cfgPopulateHoCtrlTable(6500,5000);
      cfgPopulateCsPwrCtrlTable(6500,5000,9,20,3,3);
      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      cellPerTableBuff.adminState = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable(6500,5000);
      cfgDeleteCsPwrCtrlTable(6500,5000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr21()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr21  : Unlock Cell");

      cfgPopulateCellPerTable(6500,5000,0);
      cfgPopulateLaTable(5000);
      cfgPopulateHoCtrlTable(6500,5000);
      cfgPopulateCsPwrCtrlTable(6500,5000,20,9,3,3);
      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      cellPerTableBuff.adminState = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable(6500,5000);
      cfgDeleteCsPwrCtrlTable(6500,5000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr22()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr22  : Unlock Cell");

      cfgPopulateCellPerTable(6500,5000,0);
      cfgPopulateLaTable(5000);
      cfgPopulateHoCtrlTable(6500,5000);
      cfgPopulateCsPwrCtrlTable(6500,5000,20,20,5,3);
      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      cellPerTableBuff.adminState = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable(6500,5000);
      cfgDeleteCsPwrCtrlTable(6500,5000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr23()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr23  : Unlock Cell");

      cfgPopulateCellPerTable(6500,5000,0);
      cfgPopulateLaTable(5000);
      cfgPopulateHoCtrlTable(6500,5000);
      cfgPopulateCsPwrCtrlTable(6500,5000,20,20,3,5);
      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      cellPerTableBuff.adminState = 1;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
      cfgDeleteCellPerTable(6500,5000);
      cfgDeleteCsPwrCtrlTable(6500,5000);
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr24()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr24  : Unlock Cell");

      cfgPopulateCellPerTable(6500,5000,0);
      cfgPopulateHoCtrlTable(6500,5000);
      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_DEL_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_DEL_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr25()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr25:");

      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      cellPerTableBuff.adminState = 0;
      cellPerTableBuff.antennaId = 101;
      cellPerTableBuff.bcchArfcn = 100;
      cellPerTableBuff.freqBandBcch = GSM850;
      cellPerTableBuff.bcc = 0;
      cellPerTableBuff.bcchPwr = 1;
      cellPerTableBuff.msTxPwrMax = 6;
      cellPerTableBuff.msTxPowerMaxCch = 6;
      cellPerTableBuff.fnOffset = 0;
      cellPerTableBuff.psStatus = 0;
      cellPerTableBuff.cellBarAccess = 0;
      cellPerTableBuff.accessCtrlClass = 0;
      cellPerTableBuff.bsAgBlksRes = 0;
      cellPerTableBuff.bsPaMfrms = 0;
      cellPerTableBuff.cellReselectHysteresis = 0;
      cellPerTableBuff.rxLevAccessMin = 10;
      cellPerTableBuff.powerOffset = 0;
      cellPerTableBuff.cbq = 0;
      cellPerTableBuff.cellReselectOffset = 0;
      cellPerTableBuff.tempOffset = 0;
      cellPerTableBuff.penalityTime = 0;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr26()
{
   static int testInitiation =1;

   CellPerTableApi cellPerTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr26:");

      cellPerTableBuff.cellId = 6500;
      cellPerTableBuff.lac = 5000;
      cellPerTableBuff.adminState = 0;
      cellPerTableBuff.antennaId = 101;
      cellPerTableBuff.bcchArfcn = 100;
      cellPerTableBuff.freqBandBcch = GSM1900;
      cellPerTableBuff.bcc = 0;
      cellPerTableBuff.bcchPwr = 1;
      cellPerTableBuff.msTxPwrMax = 6;
      cellPerTableBuff.msTxPowerMaxCch = 6;
      cellPerTableBuff.fnOffset = 0;
      cellPerTableBuff.psStatus = 0;
      cellPerTableBuff.cellBarAccess = 0;
      cellPerTableBuff.accessCtrlClass = 0;
      cellPerTableBuff.bsAgBlksRes = 0;
      cellPerTableBuff.bsPaMfrms = 0;
      cellPerTableBuff.cellReselectHysteresis = 0;
      cellPerTableBuff.rxLevAccessMin = 10;
      cellPerTableBuff.powerOffset = 0;
      cellPerTableBuff.cbq = 0;
      cellPerTableBuff.cellReselectOffset = 0;
      cellPerTableBuff.tempOffset = 0;
      cellPerTableBuff.penalityTime = 0;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CELLPERTABLE..");
      cfgStubSendCmMessage(&cellPerTableBuff,sizeof(CellPerTableApi),BSC_API_SET_CELLPERTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr27()
{
   static int testInitiation =1;

   ChnGrpTableApi  chnGrpTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr27:");

      cfgPopulateCellPerTable(6500,5000,0);

      chnGrpTableBuff.cellId = 6500;
      chnGrpTableBuff.lac = 5000;
      chnGrpTableBuff.chnGrpId = 1;
      chnGrpTableBuff.bcchCcchSdcch4 = 1;
      chnGrpTableBuff.bcchCcch = 1;
      chnGrpTableBuff.sdcch8 = 0;
      chnGrpTableBuff.tch = 6;
      chnGrpTableBuff.pdch = 0;
      chnGrpTableBuff.hsn = 0;
      chnGrpTableBuff.maxTxPwr = 0;
      chnGrpTableBuff.tsc = 0;
      chnGrpTableBuff.band = GSM850;
      chnGrpTableBuff.validArfcns = 1;
      chnGrpTableBuff.arfcn1 = 100;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CHNGRPTABLE..");
      cfgStubSendCmMessage(&chnGrpTableBuff,sizeof(ChnGrpTableApi),BSC_API_SET_CHNGRPTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/



/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr28()
{
   static int testInitiation =1;

   ChnGrpTableApi  chnGrpTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr28:");

      cfgPopulateCellPerTable(6500,5000,0);

      chnGrpTableBuff.cellId = 6500;
      chnGrpTableBuff.lac = 5000;
      chnGrpTableBuff.chnGrpId = 1;
      chnGrpTableBuff.bcchCcchSdcch4 = 1;
      chnGrpTableBuff.bcchCcch = 1;
      chnGrpTableBuff.sdcch8 = 0;
      chnGrpTableBuff.tch = 6;
      chnGrpTableBuff.pdch = 0;
      chnGrpTableBuff.hsn = 0;
      chnGrpTableBuff.maxTxPwr = 0;
      chnGrpTableBuff.tsc = 0;
      chnGrpTableBuff.band = GSM1900;
      chnGrpTableBuff.validArfcns = 1;
      chnGrpTableBuff.arfcn1 = 100;
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CHNGRPTABLE..");
      cfgStubSendCmMessage(&chnGrpTableBuff,sizeof(ChnGrpTableApi),BSC_API_SET_CHNGRPTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr29()
{
   static int testInitiation =1;

   CsExternalCellTableApi csExternalCellTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr29:");

      //         cfgPopulateCellPerTable(6500,5000,0);

      csExternalCellTableBuff.mcc = 3;   
      csExternalCellTableBuff.mnc = 3;   
      csExternalCellTableBuff.lac = 5000;   
      csExternalCellTableBuff.csExtCellId = 6500;   
      csExternalCellTableBuff.bcc = 0;   
      csExternalCellTableBuff.ncc = 0;   
      csExternalCellTableBuff.bcchArfcn = 100;   
      csExternalCellTableBuff.freqBandBcch = GSM850;   
      csExternalCellTableBuff.msTxPwrMax = 5;   
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CSEXTERNALCELLTABLE..");
      cfgStubSendCmMessage(&csExternalCellTableBuff,sizeof(CsExternalCellTableApi),BSC_API_SET_CSEXTERNALCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr30()
{
   static int testInitiation =1;

   CsExternalCellTableApi csExternalCellTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr30:");

      //         cfgPopulateCellPerTable(6500,5000,0);

      csExternalCellTableBuff.mcc = 3;   
      csExternalCellTableBuff.mnc = 3;   
      csExternalCellTableBuff.lac = 5000;   
      csExternalCellTableBuff.csExtCellId = 6500;   
      csExternalCellTableBuff.bcc = 0;   
      csExternalCellTableBuff.ncc = 0;   
      csExternalCellTableBuff.bcchArfcn = 100;   
      csExternalCellTableBuff.freqBandBcch = GSM1900;   
      csExternalCellTableBuff.msTxPwrMax = 5;   
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_CSEXTERNALCELLTABLE..");
      cfgStubSendCmMessage(&csExternalCellTableBuff,sizeof(CsExternalCellTableApi),BSC_API_SET_CSEXTERNALCELLTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr31()
{
   static int testInitiation =1;

   ArfcnListTableApi arfcnListTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr31:");


      arfcnListTableBuff.band = GSM850;
      arfcnListTableBuff.arfcn = 100;   
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_ARFCNLISTTABLE..");
      cfgStubSendCmMessage(&arfcnListTableBuff,sizeof(ArfcnListTableApi),BSC_API_SET_ARFCNLISTTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


/********************************************************************************
   Test Case #;
 *********************************************************************************/
void CfgHandOverHndlr32()
{
   static int testInitiation =1;

   ArfcnListTableApi arfcnListTableBuff;

   if ( testInitiation )
   {
      testInitiation =0;
      LOG_PRINT(LOG_INFO,"CfgHandOverHndlr32:");


      arfcnListTableBuff.band = GSM1900;
      arfcnListTableBuff.arfcn = 100;   
      //cfgStubSendCmMessage(NULL,0,CFG_RESET);
      LOG_PRINT(LOG_INFO,"Sending BSC_API_SET_ARFCNLISTTABLE..");
      cfgStubSendCmMessage(&arfcnListTableBuff,sizeof(ArfcnListTableApi),BSC_API_SET_ARFCNLISTTABLE);
   }
   else
   {
      switch (((SysHdr*) gCfgMsgBuf)->msgType)
      {
         case CM_API_APP_RESPONSE:
            {
               LOG_PRINT(LOG_INFO,"Recieved CM_API_APP_RESPONSE from Cfg..");
               if (((sCmMsg*) gCfgMsgBuf)->cmHdr.status == CM_SUCCESS )
               {
                  LOG_PRINT(LOG_INFO,"CM_SUCCESS");
                  gTestCaseCompleted =1;
               }
               else
               {
                  LOG_PRINT(LOG_INFO,"CM_FAILURE");
                  LOG_PRINT(LOG_INFO,"Status= %d",((sCmMsg*) gCfgMsgBuf)->cmHdr.status);
                  gTestCaseCompleted =1;
               }
            }
            break;
         default:
            LOG_PRINT(LOG_INFO,"Not Expected Message");
            break;
      }   
   }
}
/********************************************************************************/


void cfgPopulateArfcnListTable()
{
   ArfcnListTableApi arfcnListTableBuff;

	 arfcnListTableBuff.band = GSM850;
	 arfcnListTableBuff.arfcn = 100;
   if(insertArfcnListTable(&arfcnListTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertArfcnListTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertArfcnListTable unsuccessfull\n");
   }

	 arfcnListTableBuff.band = GSM1900;
	 arfcnListTableBuff.arfcn = 100;
   if(insertArfcnListTable(&arfcnListTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertArfcnListTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertArfcnListTable unsuccessfull\n");
   }

}


void cfgPopulateChnGrpTable(I_U32 cellId,I_U32 lac,I_U32 band)
{
   ChnGrpTableApi  chnGrpTableBuff;

   chnGrpTableBuff.cellId = cellId;
   chnGrpTableBuff.lac = lac;
   chnGrpTableBuff.chnGrpId = 1;
   chnGrpTableBuff.bcchCcchSdcch4 = 1;
   chnGrpTableBuff.bcchCcch = 0;
   chnGrpTableBuff.sdcch8 = 1;
   chnGrpTableBuff.tch = 6;
   chnGrpTableBuff.pdch = 0;
   chnGrpTableBuff.hsn = 0;
   chnGrpTableBuff.maxTxPwr = 0;
   chnGrpTableBuff.tsc = 0;
   chnGrpTableBuff.band = band;
   chnGrpTableBuff.validArfcns = 1;
   chnGrpTableBuff.arfcn1 = 100;
   if(insertChnGrpTable(&chnGrpTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertChnGrpTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertChnGrpTable unsuccessfull\n");
   }
}

void cfgDeleteChnGrpTable(I_U32 cellId,I_U32 lac)
{
   ChnGrpTableIndices  chnGrpTableBuff;

   chnGrpTableBuff.cellId = cellId;
   chnGrpTableBuff.lac = lac;
   if(deleteChnGrpTable(&chnGrpTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteChnGrpTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteChnGrpTable unsuccessfull\n");
   }
}

void cfgPopulateCsPwrCtrlTable(I_U32 cellId,I_U32 lac,I_U8 lRxLevUlP,I_U8 lRxLevDlP,I_U8 lRxQualUlP,I_U8 lRxQualDlP)
{
   CsPwrCtrlTableApi csPwrCtrlTableBuff;
   csPwrCtrlTableBuff.lac = lac;
   csPwrCtrlTableBuff.cellId = cellId;
   csPwrCtrlTableBuff.enMsPctrl = 1;
   csPwrCtrlTableBuff.enBsPctrl = 1;
   csPwrCtrlTableBuff.lRxLevUlP = lRxLevUlP; //20;
   csPwrCtrlTableBuff.uRxLevUlP = 30;
   csPwrCtrlTableBuff.lRxQualUlP = lRxQualUlP; //3;
   csPwrCtrlTableBuff.uRxQualUlP = 1;
   csPwrCtrlTableBuff.lRxLevDlP = lRxLevDlP; //20;
   csPwrCtrlTableBuff.uRxLevDlP = 30;
   csPwrCtrlTableBuff.lRxQualDlP = lRxQualDlP; //3;
   csPwrCtrlTableBuff.uRxQualDlP = 1;
   if(insertCsPwrCtrlTable(&csPwrCtrlTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertCsPwrCtrlTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertCsPwrCtrlTable unsuccessfull\n");
   }
}

void cfgDeleteCsPwrCtrlTable(I_U32 cellId,I_U32 lac)
{
   CsPwrCtrlTableIndices csPwrCtrlTableBuff;
   csPwrCtrlTableBuff.lac = lac;
   csPwrCtrlTableBuff.cellId = cellId;
   if(deleteCsPwrCtrlTable(&csPwrCtrlTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteCsPwrCtrlTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteCsPwrCtrlTable unsuccessfull\n");
   }
}

void cfgPopulateHoCtrlTable(I_U32 cellId,I_U32 lac)
{
   HoCtrlTableApi hoCtrlTableBuff;
   hoCtrlTableBuff.lac = lac;
   hoCtrlTableBuff.cellId = cellId;
   hoCtrlTableBuff.enHoLev = 1;   //0
   hoCtrlTableBuff.enHoQual = 1;   //0
   hoCtrlTableBuff.enHoPbgt = 1;  //0
   hoCtrlTableBuff.windowSizeRxLevH = 6;
   hoCtrlTableBuff.windowSizeRxQualH =6;
   hoCtrlTableBuff.windowSizeNcell = 6;
   hoCtrlTableBuff.lRxLevDlH = 10;
   hoCtrlTableBuff.lRxLevUlH = 10;
   hoCtrlTableBuff.lRxQualDlH = 4;
   hoCtrlTableBuff.lRxQualUlH = 4;
   hoCtrlTableBuff.hystH = 4;
   hoCtrlTableBuff.multibandReporting = 1;
   hoCtrlTableBuff.enableIncHo = 1;
   if(insertHoCtrlTable(&hoCtrlTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertHoCtrlTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertHoCtrlTable unsuccessfull\n");
   }
}

void cfgPopulateCellPerTable(I_U32 cellId,I_U32 lac,I_U32 adState)
{
   CellPerTableApi cellPerTableBuff;
   cellPerTableBuff.lac = lac;
   cellPerTableBuff.cellId = cellId;
   cellPerTableBuff.adminState = adState;
   cellPerTableBuff.antennaId = 100;
   cellPerTableBuff.bcchArfcn = 124;
   cellPerTableBuff.freqBandBcch = GSM900;
   cellPerTableBuff.bcc = 0;
   cellPerTableBuff.bcchPwr = 0;
   cellPerTableBuff.msTxPwrMax = 10;
   cellPerTableBuff.msTxPowerMaxCch = 10;
   cellPerTableBuff.fnOffset = 1;
   cellPerTableBuff.psStatus = 1;
   cellPerTableBuff.cellBarAccess = 1;
   cellPerTableBuff.accessCtrlClass = 30;
   cellPerTableBuff.bsAgBlksRes = 5;
   cellPerTableBuff.bsPaMfrms = 5;
   cellPerTableBuff.cellReselectHysteresis = 4;
   cellPerTableBuff.rxLevAccessMin = 63;
   cellPerTableBuff.powerOffset = 1;
   cellPerTableBuff.cbq = 0;
   cellPerTableBuff.cellReselectOffset = 1;
   cellPerTableBuff.tempOffset = 1;
   cellPerTableBuff.penalityTime = 3;
   if(insertCellPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertCellPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertCellPerTable unsuccessfull\n");
   }
}

void cfgPopulateLaTable(I_U32 lac)
{
   LaTableApi laTableBuff;
   laTableBuff.lac = lac;
   if(insertLaTable(&laTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertLaTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertLaTable unsuccessfull\n");
   }
}

void cfgPopulateCellNonPerTable(I_U32 cellId,I_U32 lac,I_U32 oprState)
{
   CellNonPerTableApi cellPerTableBuff;
   cellPerTableBuff.lac = lac;
   cellPerTableBuff.cellId = cellId;
   cellPerTableBuff.antennaId = 100;
   cellPerTableBuff.oprState = oprState;
   cellPerTableBuff.ccchConf = 1;
   cellPerTableBuff.bcchChangeMark = 1;
   cellPerTableBuff.siChangeField = 0;
   if(insertCellNonPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertCellNonPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertCellNonPerTable unsuccessfull\n");
   }
}

void cfgDelCellPerTable(I_U32 cellId,I_U32 lac)
{
   CellPerTableIndices cellPerTableBuff;
   cellPerTableBuff.lac = lac;
   cellPerTableBuff.cellId = cellId;
   if(deleteCellPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteCellPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteCellPerTable unsuccessfull\n");
   }
}

void cfgDelCellNonPerTable(I_U32 cellId,I_U32 lac)
{
   CellNonPerTableIndices cellPerTableBuff;
   cellPerTableBuff.lac = lac;
   cellPerTableBuff.cellId = cellId;
   if(deleteCellNonPerTable(&cellPerTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteCellNonPerTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteCellNonPerTable unsuccessfull\n");
   }
}

void cfgPopulateSwMOfferTable(I_U32 nodeType, I_S8 *swVersion)
{
   SwMOfferTableApi swMOfferTableBuff;
   swMOfferTableBuff.nodeType = nodeType;
   strcpy(swMOfferTableBuff.upgradeVersion,swVersion);
   swMOfferTableBuff.ftpServerAddress = 0xAC1F7B27;
   memcpy(swMOfferTableBuff.tarPathName,"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
   memcpy(swMOfferTableBuff.loginName,"gur19999",NAME_SIZE);
   memcpy(swMOfferTableBuff.password,"abc123",NAME_SIZE);
   memcpy(swMOfferTableBuff.checksum,"7353653",NAME_SIZE);
   if(insertSwMOfferTable(&swMOfferTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertSwMOfferTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertSwMOfferTable unsuccessfull\n");
   }
}

void cfgPopulateSwMTable(I_U32 nodeType,I_S8 *swVersion,I_U8 count,I_U8 delInPr)
{
   SwMTableApi swMTableBuff;
   swMTableBuff.nodeType = nodeType;
   strcpy(swMTableBuff.swVersion,swVersion);
   memcpy(swMTableBuff.binaryPath,"/home/SoftRelease/Rel-1.0.2",CMD_PARAM_MAX_SIZE);
   swMTableBuff.swDownloadCount = count;
   swMTableBuff.deletionInProgress = delInPr;
   if(insertSwMTable(&swMTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertSwMTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertSwMTable unsuccessfull\n");
   }
}

void cfgPopulateSwMNodeTable(I_U32 nodeType,I_U32 nodeId,I_U32 e1Id,I_S8 *swVerAc,I_S8 *swVerInAc,I_S8 *swVerDnld,I_S8 *swVerNew,I_U32 swAction,I_U32 swStatus)
{
   SwMNodeTableApi swMNodeTableBuff;
   swMNodeTableBuff.nodeType = nodeType;
   swMNodeTableBuff.nodeIdentity = nodeId;
   swMNodeTableBuff.e1Num = e1Id;
   strcpy(swMNodeTableBuff.swVersionActive,swVerAc); 
   strcpy(swMNodeTableBuff.swVersionInactive,swVerInAc);
   strcpy(swMNodeTableBuff.swVersionDownloaded,swVerDnld);
   strcpy(swMNodeTableBuff.swVersionNew,swVerNew);
   swMNodeTableBuff.swAction = swAction;
   swMNodeTableBuff.swStatus = swStatus;
   if(insertSwMNodeTable(&swMNodeTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertSwMNodeTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertSwMNodeTable unsuccessfull\n");
   }
}

void cfgUpdateSwMNodeTable(I_U32 nodeType,I_U32 nodeId,I_U32 e1Id,I_S8 *swVerAc,I_S8 *swVerInAc,I_S8 *swVerDnld,I_S8 *swVerNew,I_U32 swAction,I_U32 swStatus)
{
   SwMNodeTableApi swMNodeTableBuff;
   swMNodeTableBuff.nodeType = nodeType;
   swMNodeTableBuff.nodeIdentity = nodeId;
   swMNodeTableBuff.e1Num = e1Id;
   swMNodeTableBuff.lapdTs = 0;
   strcpy(swMNodeTableBuff.swVersionActive,swVerAc); 
   strcpy(swMNodeTableBuff.swVersionInactive,swVerInAc);
   strcpy(swMNodeTableBuff.swVersionDownloaded,swVerDnld);
   strcpy(swMNodeTableBuff.swVersionNew,swVerNew);
   swMNodeTableBuff.swAction = swAction;
   swMNodeTableBuff.swStatus = swStatus;
   if(updateSwMNodeTable(&swMNodeTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateSwMNodeTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"updateSwMNodeTable unsuccessfull\n");
   }
}

void cfgDeleteSwMTable(I_U32 nodeType,I_S8 *swVersion)
{
   SwMTableIndices swMTableBuff;
   swMTableBuff.nodeType = nodeType;
   strcpy(swMTableBuff.swVersion,swVersion);
   if(deleteSwMTable(&swMTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteSwMTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteSwMTable unsuccessfull\n");
   }
}

void cfgDeleteSwMNodeTable(I_U32 nodeType,I_U32 nodeId)
{
   SwMNodeTableIndices swMNodeTableBuff;
   swMNodeTableBuff.nodeType = nodeType;
   swMNodeTableBuff.nodeIdentity = nodeId;
   if(deleteSwMNodeTable(&swMNodeTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"deleteSwMNodeTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"deleteSwMNodeTable unsuccessfull\n");
   }
}

void cfgUpdateBssAdminState(I_U32 adminState)
{
   BssTableApi  bssTableApiBuff;
   bssTableApiBuff.bscId =1;
   bssTableApiBuff.adminState = adminState;    

   if(updateBssTable(&bssTableApiBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateBssTable successfull");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"updateBssTable unsuccessfull");
   }
}

void cfgUpdateBicStatusTable(I_U32 state)
{
   BicStatusTableApi bicStatusTableBuff;
   bicStatusTableBuff.bicId = 101;
   bicStatusTableBuff.connectionState = state;
   if(updateBicStatusTable(&bicStatusTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateBicStatusTable successfull");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"updateBicStatusTable unsuccessfull");
   }
}

void cfgUpdateTrxTable(I_U32 state)
{
   TrxTableApi trxTableBuff; 
   trxTableBuff.ptrxId = 21;
   trxTableBuff.adminState = state;
   trxTableBuff.trxLocation = 2; 
   trxTableBuff.bicId = 101;
   trxTableBuff.antennaID = 101;
   trxTableBuff.trxPos = 1;
   trxTableBuff.rfPathGain = 200;
   if(updateTrxTable(&trxTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateTrxTable successfull  ");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"updateTrxTable unsuccessfull  ");
   }
}

void cfgUpdateTrxTsTeiTable(I_U32 status)
{
   TrxTsTeiTableApi trxTsTeiTableBuff;
   trxTsTeiTableBuff.ptrxId = 21;
   trxTsTeiTableBuff.trxTei = 21;
   trxTsTeiTableBuff.e1Id = 1;
   trxTsTeiTableBuff.startTsTraffic = 3;
   trxTsTeiTableBuff.lapdTs = 0;
   trxTsTeiTableBuff.lapdLinkStatus = status;
   if(updateTrxTsTeiTable(&trxTsTeiTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"updateTrxTsTeiTable successfull\n");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"updateTrxTsTeiTable unsuccessfull\n");
   }
}

#if 0
void cfgPopulatePhysicalTrxTable()
{
   PhysicalTrxPreconfiguredTableApi physicalTrxTableBuff;
   physicalTrxTableBuff.ptrxId = 4;
   physicalTrxTableBuff.tei = 2;
   physicalTrxTableBuff.antennaId = 1;
   physicalTrxTableBuff.adminState = 0;
   physicalTrxTableBuff.e1Id =1 ;
   physicalTrxTableBuff.startE1Timeslot = 10;
   physicalTrxTableBuff.rackId = 11;
   physicalTrxTableBuff.slotId = 1;
   if(insertPhysicalTrxPreconfiguredTable(&physicalTrxTableBuff) == CLIB_SUCCESS)
   {
      LOG_PRINT(LOG_INFO,"insertPhysicalTrxPreconfiguredTable successfull  ");
   }
   else
   {
      LOG_PRINT(LOG_INFO,"insertPhysicalTrxPreconfiguredTable unsuccessfull  ");
   }
}
#endif
