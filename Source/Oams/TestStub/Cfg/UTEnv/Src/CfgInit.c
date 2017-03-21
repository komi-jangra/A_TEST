#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <errno.h>
#include <sysxxx_typedef.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_datastruct.h>
#include <sysxxx_msgopcode.h>
#include <sysxxx_proc.h>
#include <sysxxx_msgstruct.h>
#include <syscmn_hashdefs.h>
#include <syscmn_datastruct.h>
#include <oamxxx_tableapidefs.h>
#include <oamomc_errorcodes.h>
#include <oamsnmp_hashdefs.h>
#include <oamxxx_hashdefs.h>
#include <oamxxx_msgstruct.h>
#include <dbsxxx_commondefs.h>
#include <dbsxxx_commonwrappers.h>
#include <dbsxxx_cfg_dbwrapper.h>
#include <dbsxxx_cellh_dbwrapper.h>
#include <dbsxxx_grhm_dbwrapper.h>
//#if BPM_PRESENT == 1
#include <bpmxxx_commonDef.h>
#include <bpmxxx_OAM_commonDef.h>
//#endif

#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <ipcfrm_msgdef.h>

#include <mgs_common_hashdef.h>
#include <mgs_trau_hashdef.h>
#include <mgs_common_hashdef.h>
#include <mgs_trau_msgstruct.h>
#include <mgs_tsi_msgstruct.h>
#include <oamsxxx_alarmid.h>
#include <oamsxxx_typedef.h>
#include <oamsxxx_hashdef.h>
#include <oamscfg_hashdefs.h>
#include <oamscfg_type.h>
#include <csappxxx_common_datastruct.h>
#include <oamsxxx_msgstruct.h>
#include "oams_msgstruct.h"
#include <oams_hashdefs.h>
#include <oamscfg_objectHandler_header.h>
#include <dsp_global.h>
#include <dsp_pp_com.h>
#include <dsp_com_api.h>
#include <oamscfg_trau_msgstruct.h>
#include <oamscfg_externs.h>
#include <DBLIBError.h>
#include <signal.h>
#include <oamsxxx_listdefs.h>
#include <oamscfg_signal_handler.h>
#include <oamscfg_bss_object_handler.h>
#include <oamscfg_bic_object_handler.h>
#include <oamscfg_msg_handler.h>
#include <oamscfg_responses.h>
#include <oamscfg_trx_object_handler.h>
#include <oamscfg_e1_object_handler.h>
#include <oamscfg_e1timeslot_object_handler.h>
#include <oamscfg_alarm_handler.h>
#include <oamscfg_setdelmsghandler.h>
#include <oamscfg_cell_object_handler.h>
#include <oamscfg_cell_object_consistancy_check.h>
#include <oamscfg_bic_trx_ts_handler.h>
#include <oamscfg_clk_object_handler.h>

#include <ipcfrm_msgqueue.h>
#include <sysxxx_macro.h>
#include <testsuit.h>
#include <sysxxx_alarm.h>
/* Local Values */
#define SYSHDR_MAX_VAL          sizeof(SysHdr)

SysAddr src;
SysAddr dst;
static I_U8 InitAlarmCount;
/*****************End**********************/


I_Void SendMsgToIPC(I_PVoid sndPtr, I_S32 sndMsgSz, I_S8* msgName)
{
  /* Printing message dump */
  LOG_PRINT(DEBUG, "SendMsgToIPC: Printing Hex Dump of SEND message %s of length %d", \
      msgName, sndMsgSz);
#if 0      
  PRINT_HEX_DUMP(DEBUG, sndPtr, sndMsgSz);
#endif 
  /* Sending message */
  if (SendMsg(sndPtr, MSG_ORD_PRIO, sndMsgSz) == SND_FAIL)
  {
    LOG_PRINT(MAJOR,"SendMsgToIPC: Snd. Fail for message %p of msgType %d", \
        sndPtr, ((SysHdr *)sndPtr)->msgType);
    LOG_PRINT(MAJOR,"SendMsgToIPC: Snd. Fail.msgSize %d",sndMsgSz);
  }
  else
  {
    LOG_PRINT(DEBUG,"SendMsgToIPC: Snd. Succ.msgType %d",((SysHdr *)sndPtr)->msgType);
    LOG_PRINT(DEBUG,"SendMsgToIPC: Snd. Succ.msgSize %d",sndMsgSz);
  }//end of SendMsg

  return;
}//end of fillAndSendMsg

void cfgStubSendDSmmMgsuDriverInitStatus(I_U32 tsiStatus)
{
  DSmmMgsuDriverInitStatus* DSmmMgsuDriverInitStatusBuff = 
    (DSmmMgsuDriverInitStatus*)AlocMsgBuf(sizeof(DSmmMgsuDriverInitStatus));
  memset((I_PVoid)DSmmMgsuDriverInitStatusBuff, 
      ZERO, 
      sizeof(DSmmMgsuDriverInitStatus));
	DSmmMgsuDriverInitStatusBuff->hdr.DestId = MGS_DEST_TSI_APP;
  DSmmMgsuDriverInitStatusBuff->messageId= MGS_TSM_TSI_DRIVER_INIT_STS;
  DSmmMgsuDriverInitStatusBuff->tsiStatus = tsiStatus;
  FILL_SYS_HDR(DSmmMgsuDriverInitStatusBuff, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)DSmmMgsuDriverInitStatusBuff, 
               sizeof(DSmmMgsuDriverInitStatus),
               "TSM TSI DRIVER INIT STATUS"
              );
}

void cfgStubSendDTrauMgsuDriverInitStatus(I_U32 dspStatus)
{
  DTrauMgsuDriverInitStatus* DTrauMgsuDriverInitStatusBuff= 
    (DTrauMgsuDriverInitStatus*)AlocMsgBuf(sizeof(DTrauMgsuDriverInitStatus));
  DTrauMgsuDriverInitStatusBuff->messageId=MGS_TRAU_DRIVER_INIT_STATUS;
  DTrauMgsuDriverInitStatusBuff->dspStatus = dspStatus;
  FILL_SYS_HDR(DTrauMgsuDriverInitStatusBuff, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)DTrauMgsuDriverInitStatusBuff, 
               sizeof(DTrauMgsuDriverInitStatus), 
               "TRAU DRIVER INIT STATUS"
              );
}

void cfgStubSendDTrauMgsuTrauInitResp()
{
  DTrauMgsuTrauInitResp* DTrauMgsuTrauInitRespBuff= 
    (DTrauMgsuTrauInitResp*)AlocMsgBuf(sizeof(DTrauMgsuTrauInitResp));
  DTrauMgsuTrauInitRespBuff->messageId=MGS_TRAU_INIT_RESP;
  FILL_SYS_HDR(DTrauMgsuTrauInitRespBuff, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)DTrauMgsuTrauInitRespBuff, 
               sizeof(DTrauMgsuTrauInitResp), 
               "TRAU INIT RESP");
}

void cfgStubSendDSmmMgsBootMsg(I_U32 dspStatus)
{
	 DSmmMgsBootMsg *dSmmMgsBootMsgPtr = 
		 (DSmmMgsBootMsg*)AlocMsgBuf(sizeof(DSmmMgsBootMsg));
	dSmmMgsBootMsgPtr->hdr.DestId = MGS_DEST_TRAU_APP;
	dSmmMgsBootMsgPtr->trauHdr.MessageID = DSP_BOOT_MSG_ID;
 	 dSmmMgsBootMsgPtr->max_num_trau = 22;
	 dSmmMgsBootMsgPtr->response = dspStatus; 
  FILL_SYS_HDR(dSmmMgsBootMsgPtr, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)dSmmMgsBootMsgPtr, sizeof(DSmmMgsBootMsg), "DSP_BOOT_MSG_ID");
}

void cfgStubSendDSmmDspInitResMsg(I_U32 dspStatus)
{
	 DSmmDspInitResMsg *dSmmDspInitResMsgPtr = 
		 (DSmmDspInitResMsg*)AlocMsgBuf(sizeof(DSmmDspInitResMsg));
	dSmmDspInitResMsgPtr->hdr.DestId = MGS_DEST_TRAU_APP;
	dSmmDspInitResMsgPtr->trauHdr.MessageID = DSP_INIT;
	 dSmmDspInitResMsgPtr->response = dspStatus; 
  FILL_SYS_HDR(dSmmDspInitResMsgPtr, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)dSmmDspInitResMsgPtr, sizeof(DSmmDspInitResMsg), "DSP_INIT");
}

void cfgStubSendDSmmTrauStartResMsg(I_U32 dspStatus)
{
	 DSmmTrauStartResMsg *dSmmTrauStartResMsgPtr = 
		 (DSmmTrauStartResMsg*)AlocMsgBuf(sizeof(DSmmTrauStartResMsg));
	dSmmTrauStartResMsgPtr->hdr.DestId = MGS_DEST_TRAU_APP;
	dSmmTrauStartResMsgPtr->trauHdr.MessageID = TRAU_START;
	 dSmmTrauStartResMsgPtr->response = dspStatus; 
  FILL_SYS_HDR(dSmmTrauStartResMsgPtr, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)dSmmTrauStartResMsgPtr, sizeof(DSmmTrauStartResMsg), "TRAU_START");
}

I_Void sendSs7StackUpAlarm(I_Void)
{
  SysHdr *SysHdrPtr = NULL;

  if ((SysHdrPtr = (SysHdr *)AlocMsgBuf(sizeof(SysAlarm)+sizeof(SysHdr))) == NULL) {
      LOG_PRINT(LOG_CRITICAL,"%s:AlocMsgBuf Fail",__func__);
      return ; 
  }
  FILL_SYS_HDR( SysHdrPtr, 
                OAM_OIL_CFG_ALARM_IND, 
                0, 
                0, 
                ENT_OAM_OIL, 
                0, 
                0, 
                ENT_OAMS_CFG, 
                0
              );
  (( SysAlarm* )(SysHdrPtr + 1))->sysalarmId = ALARM_ID_MSC_SS7_UP;  

  SendMsgToIPC( 
                (I_PVoid)SysHdrPtr,
                (sizeof(SysAlarm) + sizeof(SysHdr)), 
                "SS7 Stack UP Alarm"
              );
   
}

I_Void TestCaseInitCfg(I_Void) 
{
  I_U8* msgRcvP = NULL;
  I_S32 dbStatus;
  I_U32 index;  
  EicCardInfoTableApi eicData;

  memset(&eicData,0,sizeof(EicCardInfoTableApi));

  for(index=0;index<2;index++) {
     eicData.chasisFrameId=1;
     eicData.slotId=index;
     dbStatus=insertEicCardInfoTable(&eicData);
     if(dbStatus!=CLIB_SUCCESS) {
        LOG_PRINT(LOG_INFO,"Insertion in EicCardInfoTable failed ");
     }
  }
  LOG_PRINT(LOG_INFO,"Initialisation of EicCardInfoTable OK");
  { 
    // Clean SWM Table    
    SwMNodeTableApi *outData;
    SwMNodeTableApi *tempswMNodeTableBuf;
    SwMNodeTableIndices swMNodeTableBuf;
    I_U32 outRows;
    I_U16 outSize;
    if (getallSwMNodeTable( &outData, &outRows, &outSize) == CLIB_SUCCESS) {
      for (index=0;index<outRows;index++) {
        tempswMNodeTableBuf = (SwMNodeTableApi *) ((I_U8 *)outData + (index*outSize));
        swMNodeTableBuf.nodeType = tempswMNodeTableBuf->nodeType;
        swMNodeTableBuf.nodeIdentity = tempswMNodeTableBuf->nodeIdentity;

        if (deleteSwMNodeTable(&swMNodeTableBuf) != CLIB_SUCCESS) {
          LOG_PRINT(LOG_INFO,"deleteSwMNodeTable DB call Failed");
        }  
      }
    }
    LOG_PRINT(LOG_INFO,"Initialisation of SwMNodeTable OK ");
  }
  // Clean Trunk Port Table
  {
    TrunkPortTableApi *outData;
    I_U32 outRows, i; 
    I_U16 outSize;
    TrunkPortTableIndices key;
  
    if (CLIB_SUCCESS == getallTrunkPortTable(&outData,&outRows,&outSize) ) {
      for (i=0 ; i < outRows; i++ ) {
        key.chasisFrameId = ((TrunkPortTableApi *) (outData + i*outSize))->chasisFrameId;
        key.slotId = ((TrunkPortTableApi *) (outData + i*outSize))->slotId;
        key.trunkPortId = ((TrunkPortTableApi *) (outData + i*outSize))->trunkPortId;
        deleteTrunkPortTable(&key);
      }
      free(outData);
    }   
  } 
    // Clean Clock Table
  {
    ClkSourceConfigTableApi *outData;
    I_U32 outRows, i; 
    I_U16 outSize;
    ClkSourceConfigTableIndices key;
  
    if (CLIB_SUCCESS == getallClkSourceConfigTable(&outData,&outRows,&outSize) ) {
      for (i=0 ; i < outRows; i++ ) {
          if ( deleteClkSourceConfigTable( (ClkSourceConfigTableIndices *)((I_U8 *)outData + (i*outSize)))
               != CLIB_SUCCESS) {                                                                  
            LOG_PRINT(LOG_CRITICAL,"delete DB call Failed for ClkSourceConfigTable");                
          }          
      }
      free(outData);
    }   
  }
  // Clean SWM Node Table
  {
    SwMTableApi *outData;
    SwMTableApi *tempswMTableBuf;
    SwMTableIndices swMTableBuf;
    I_U32 outRows;
    I_U16 outSize;
    if (getallSwMTable( &outData, &outRows, &outSize) == CLIB_SUCCESS) {
       for (index=0;index<outRows;index++) {
          tempswMTableBuf = (SwMTableApi *)
              ((I_U8 *)outData + (index*outSize));
          swMTableBuf.nodeType = tempswMTableBuf->nodeType;
          strcpy(swMTableBuf.swVersion,tempswMTableBuf->swVersion);

          if (deleteSwMTable(&swMTableBuf) != CLIB_SUCCESS) {
            LOG_PRINT(LOG_CRITICAL,"deleteSwMTable DB call Failed");
          }  
       }
    } 
    LOG_PRINT(LOG_INFO,"Initialisation of SwMTable OK ");
  }
  while(TRUE)
  {
    msgRcvP =  msgRcvr();
    switch ( (((SysHdr*) msgRcvP)->msgType)) {
    case OAMS_CFG_OIL_BPM_DB_INITIALIZED: 
    case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
    case OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ:
      ExecuteOilAction(msgRcvP);
      InitAlarmCount=0;
    break;
    case OAMS_CFG_AFH_ALARM_IND :
      InitAlarmCount++;
      if (4 == InitAlarmCount ) {
        LOG_PRINT(LOG_INFO,"Sending SS7_STACK_UP Alarm..");
        sendSs7StackUpAlarm();
        return;
      }
      break;
    case EXT_TSM_MSG: {
      tHdr *hdr = (tHdr*)(msgRcvP + sizeof(SysHdr));
      LOG_PRINT(LOG_INFO,"Recieved EXT_TSM_MSG from Cfg..");
			if(hdr->DestId == MGS_DEST_TRAU)
			{
				 msg_header_t *trauHdr = (msg_header_t*)(msgRcvP + sizeof(SysHdr) + sizeof(tHdr));
				 switch (trauHdr->MessageID)
         {
           case  DSP_INIT:
					 {
               LOG_PRINT(LOG_INFO,"Recieved DSP_INIT from Cfg..");
						  cfgStubSendDSmmDspInitResMsg(DSP_SUCCESS);
							break;
					 }
           case  TRAU_START:
					 {
               LOG_PRINT(LOG_INFO,"Recieved TRAU_START from Cfg..");
						  cfgStubSendDSmmTrauStartResMsg(DSP_SUCCESS);
							break;
					 }
				}
			}
			else
			{
      I_U8 msgId = *(I_U8*)(msgRcvP + sizeof(SysHdr) + sizeof(tHdr));
      switch(msgId)
      {
        case MGS_SMM_INIT_TRIGGER :
          {
            LOG_PRINT(LOG_INFO,"Recieved MGS_SMM_INIT_TRIGGER from Cfg..");
            cfgStubSendDSmmMgsuDriverInitStatus(MGS_SMM_SUCCESS);
            //cfgStubSendDTrauMgsuDriverInitStatus(MGS_SMM_SUCCESS);
						cfgStubSendDSmmMgsBootMsg(DSP_SUCCESS);
          }
          break;
        /*case MGS_TRAU_INIT_REQ:
          {
            cfgStubSendDTrauMgsuTrauInitResp(MGS_SMM_SUCCESS);
          }
          break; */
        case MGS_TSM_SWITCH_MAKE_REQ:
          {
            I_U8* msgBuffer;
            I_S32 sndMsgSz;
#ifdef WITH_NACK_TSM
            I_U16 option;
            printf("1) MGS_TSM_SWITCH_MAKE_RESP\n");
            printf("2) MGS_TSM_SWITCH_MAKE_NACK\n");
            printf("Enter The Message Number: ");
            scanf("%hu", &option);
#endif
            sndMsgSz = 28;
            msgBuffer = (I_U8*)AlocMsgBuf(sndMsgSz);
            memset((I_PVoid)msgBuffer, ZERO, sndMsgSz);
            FILL_SYS_HDR(msgBuffer, MGS_TSM_GRHM_DATA_IND, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_CSAPP_GRHM, 0);
#ifdef PFS_2
            *(msgBuffer + 20) = MGS_DEST_TSI_APP;
#else
            *(msgBuffer + 20) = MGS_DEST_TCM;
#endif
            *(msgBuffer + 21) = *(msgRcvP + 21);
            *(msgBuffer + 22) = MGS_TSM_SWITCH_MAKE_RESP;
#ifdef WITH_NACK_TSM
            *(msgBuffer + 23) = (option==1 ?  MGS_SMM_SUCCESS : MGS_SMM_FAILURE);
#else
            *(msgBuffer + 23) = MGS_SMM_SUCCESS;
#endif
            *(msgBuffer + 24) = *(msgRcvP + 24);
            *(msgBuffer + 25) = *(msgRcvP + 25);
            *(msgBuffer + 26) = *(msgRcvP + 26);
            *(msgBuffer + 27) = *(msgRcvP + 27);
            SendMsgToIPC((I_PVoid)msgBuffer, sndMsgSz, "SWITCH MAKE RESP");
          }
          break;
        default:
          LOG_PRINT(MAJOR, "No Message handling for the message type: %#d", msgId);
          break;
      }
		}
    break;
    }
    default :;
    }// End of Switch

    DalocMsgBuf(msgRcvP);
  }//end of while(ONE)
  return ;
}

