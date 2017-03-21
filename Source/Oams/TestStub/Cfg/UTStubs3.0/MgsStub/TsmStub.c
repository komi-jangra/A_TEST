#include "oamscfg_includes.h"
#include "ipcfrm_msgqueue.h"
#include "sysxxx_macro.h"

/* Local Values */
#define SYSHDR_MAX_VAL          sizeof(SysHdr)

/*** Global Variable for Stub Entity Id ***/
const I_S32 selfEntIdG = ENT_IPC_TSMIF;
I_S8* msgName = NULL;
SysAddr src;
SysAddr dst;
/*****************End**********************/


I_Void SendMsgToIPC(I_PVoid sndPtr, I_S32 sndMsgSz, I_S8* msgName)
{
  /* Printing message dump */
  LOG_PRINT(DEBUG, "SendMsgToIPC: Printing Hex Dump of SEND message %s of length %d", \
      msgName, sndMsgSz);
  PRINT_HEX_DUMP(DEBUG, sndPtr, sndMsgSz);

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


/* Receiver Thread */
I_PVoid msgRcvr()
{
  I_PVoid rcvPtr = NULL;
  I_S32 msgSize = ZERO;

  while ((rcvPtr = RecvMsg(selfEntIdG, &msgSize)) == NULL)
  {}

  /* Printing message dump */
  LOG_PRINT(DEBUG, "msgRcvr: Printing Hex Dump of RECV message of length %d", \
      msgSize);
  PRINT_HEX_DUMP(DEBUG, rcvPtr, msgSize);
  return rcvPtr;

}//end of msgRcvr


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
  msgName = "TSM TSI DRIVER INIT STATUS";
  FILL_SYS_HDR(DSmmMgsuDriverInitStatusBuff, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)DSmmMgsuDriverInitStatusBuff, sizeof(DSmmMgsuDriverInitStatus), msgName);
}

void cfgStubSendDTrauMgsuDriverInitStatus(I_U32 dspStatus)
{
  DTrauMgsuDriverInitStatus* DTrauMgsuDriverInitStatusBuff= 
    (DTrauMgsuDriverInitStatus*)AlocMsgBuf(sizeof(DTrauMgsuDriverInitStatus));
  DTrauMgsuDriverInitStatusBuff->messageId=MGS_TRAU_DRIVER_INIT_STATUS;
  DTrauMgsuDriverInitStatusBuff->dspStatus = dspStatus;
  msgName = "TRAU DRIVER INIT STATUS";
  FILL_SYS_HDR(DTrauMgsuDriverInitStatusBuff, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)DTrauMgsuDriverInitStatusBuff, sizeof(DTrauMgsuDriverInitStatus), msgName);
}

void cfgStubSendDTrauMgsuTrauInitResp()
{
  DTrauMgsuTrauInitResp* DTrauMgsuTrauInitRespBuff= 
    (DTrauMgsuTrauInitResp*)AlocMsgBuf(sizeof(DTrauMgsuTrauInitResp));
  DTrauMgsuTrauInitRespBuff->messageId=MGS_TRAU_INIT_RESP;
  msgName = "TRAU INIT RESP";
  FILL_SYS_HDR(DTrauMgsuTrauInitRespBuff, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)DTrauMgsuTrauInitRespBuff, sizeof(DTrauMgsuTrauInitResp), msgName);
}

void cfgStubSendDSmmMgsBootMsg(I_U32 dspStatus)
{
	 DSmmMgsBootMsg *dSmmMgsBootMsgPtr = 
		 (DSmmMgsBootMsg*)AlocMsgBuf(sizeof(DSmmMgsBootMsg));
	dSmmMgsBootMsgPtr->hdr.DestId = MGS_DEST_TRAU_APP;
	dSmmMgsBootMsgPtr->trauHdr.MessageID = DSP_BOOT_MSG_ID;
 	 dSmmMgsBootMsgPtr->max_num_trau = 22;
	 dSmmMgsBootMsgPtr->response = dspStatus; 
	 msgName = "DSP_BOOT_MSG_ID";
  FILL_SYS_HDR(dSmmMgsBootMsgPtr, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)dSmmMgsBootMsgPtr, sizeof(DSmmMgsBootMsg), msgName);
}

void cfgStubSendDSmmDspInitResMsg(I_U32 dspStatus)
{
	 DSmmDspInitResMsg *dSmmDspInitResMsgPtr = 
		 (DSmmDspInitResMsg*)AlocMsgBuf(sizeof(DSmmDspInitResMsg));
	dSmmDspInitResMsgPtr->hdr.DestId = MGS_DEST_TRAU_APP;
	dSmmDspInitResMsgPtr->trauHdr.MessageID = DSP_INIT;
	 dSmmDspInitResMsgPtr->response = dspStatus; 
	 msgName = "DSP_INIT";
  FILL_SYS_HDR(dSmmDspInitResMsgPtr, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)dSmmDspInitResMsgPtr, sizeof(DSmmDspInitResMsg), msgName);
}

void cfgStubSendDSmmTrauStartResMsg(I_U32 dspStatus)
{
	 DSmmTrauStartResMsg *dSmmTrauStartResMsgPtr = 
		 (DSmmTrauStartResMsg*)AlocMsgBuf(sizeof(DSmmTrauStartResMsg));
	dSmmTrauStartResMsgPtr->hdr.DestId = MGS_DEST_TRAU_APP;
	dSmmTrauStartResMsgPtr->trauHdr.MessageID = TRAU_START;
	 dSmmTrauStartResMsgPtr->response = dspStatus; 
	 msgName = "TRAU_START";
  FILL_SYS_HDR(dSmmTrauStartResMsgPtr, ENT_MGS_TSM, 0, 0, ENT_IPC_TSMIF, 0, 0, ENT_OAMS_CFG, 0);
  SendMsgToIPC((I_PVoid)dSmmTrauStartResMsgPtr, sizeof(DSmmTrauStartResMsg), msgName);
}

/*** MAIN ***/
I_S32 main()
{
  I_S8 retVal;
  I_U8* msgRcvP = NULL;
  /* System Paramters */
  I_S8* const prcName = "TSMStub";

  /* Registering with LOG Utility */
  memset((I_PVoid)&src,ZERO, sizeof(SysAddr));
  src.entity = selfEntIdG;
  LOG_INIT(retVal, src);
  if(retVal < ZERO)
  {
    LOG_PRINT(CRITICAL, "main: InitLoggingUtility Failed");
  }

  /* Registering with IPC FRMWRK */
  if (RegisterWithIpcFrmwrk(selfEntIdG, prcName) < ZERO)
  {
    LOG_PRINT(CRITICAL,"main: Unable to Register itself with IPC FrameWork. Exiting...");
    exit(EXIT_FAILURE);
  }

  /*LOG_PRINT(INFO, "** SystemName=%s, ModuleName=%s, Version=%s **",
      SYSTEM_NAME, prcName, VERSION); */

  printf("----------TSM SIMULATOR---------\n");

  while(ONE)
  {
    msgRcvP =  msgRcvr();
    if ( (((SysHdr*) msgRcvP)->msgType)==EXT_TSM_MSG)
    {
			tHdr *hdr = (tHdr*)(msgRcvP + sizeof(SysHdr));
			if(hdr->DestId == MGS_DEST_TRAU)
			{
				 msg_header_t *trauHdr = (msg_header_t*)(msgRcvP + sizeof(SysHdr) + sizeof(tHdr));
				 switch (trauHdr->MessageID)
         {
           case  DSP_INIT:
					 {
						  cfgStubSendDSmmDspInitResMsg(DSP_SUCCESS);
							break;
					 }
           case  TRAU_START:
					 {
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
            msgName = "SWITCH MAKE RESP";
            SendMsgToIPC((I_PVoid)msgBuffer, sndMsgSz, msgName);
          }
          break;
        default:
          LOG_PRINT(MAJOR, "No Message handling for the message type: %#d", msgId);
          break;
      }
		}
    } // End of if ( (((SysHdr*) msgRcvP)->msgType)==EXT_TSM_MSG)
    else
    {
      printf("This is not a valid message type");
    }// End of else

    DalocMsgBuf(msgRcvP);
  }//end of while(ONE)
  return 0;
}
