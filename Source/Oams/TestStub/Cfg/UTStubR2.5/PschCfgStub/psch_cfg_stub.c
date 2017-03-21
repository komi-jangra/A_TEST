#include <oamscfg_includes.h>
#include "cfg_stub_psch.h"

SysHdr*    sysHdrPtr;
I_S32 srcId;           /* SrcId for the CFG */
void *cfgMsgBuf;       /* Message Pointer for the received message */
I_U32 recvMsgSize;  /* received message size */

void cfgFrmwrkInit(I_S32 srcId)
{
   I_S8 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(srcId, (I_S8*)"CFG_PSCH_STUB");
   printf("\nReturn Value of IPC Registration: %d\n",retVal);
   if (retVal < ZERO)
   {
      printf("Registration failed " );
      exit(0);
   }
   printf("\nCFG: Calling function cfgFrmwrkInit() Exiting");
} /* End of function cfgFrmwrkInit() */

int main()
{
   printf("PSCH CFG Stub \n");
   printf("\n PSCH Configured \n");
   pschReqHandler();
   return 1;
}

void pschReqHandler()
{
   cfgFrmwrkInit(ENT_OAMS_PSCH);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_OAMS_PSCH, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
              case  OAMS_CFG_PSCH_UNLOCK_REQ:
                 printf("Received Msg :  OAMS_CFG_PSCH_UNLOCK_REQ");
	         pschUnlockReqHandler();
      	         break;
              case  OAMS_CFG_PSCH_LOCK_REQ:
                 printf("Received Msg :  OAMS_CFG_PSCH_LOCK_REQ");
	         pschLockReqHandler();
      	         break;
              case OAMS_CFG_PSCH_SHUTDOWN_IND:
                 printf("Received Msg : OAMS_CFG_PSCH_SHUTDOWN_IND");
                 break;
              case OAMS_CFG_PSCH_BVC_OP_FAILED:
                 printf("Received Msg : OAMS_CFG_PSCH_BVC_OP_FAILED");
                 break;
              case OAMS_CFG_PSCH_PTP_BVC_RESET:
                 printf("Received Msg : OAMS_CFG_PSCH_PTP_BVC_RESET");
                 break;
      }
      DalocMsgBuf(cfgMsgBuf);
   }
   
}

void pschUnlockReqHandler()
{
  OamsCfgPschUnlockReq *oamsCfgPschUnlockReqPtr;
  oamsCfgPschUnlockReqPtr = (OamsCfgPschUnlockReq*)cfgMsgBuf;
  cfgStubSendPschCfgUnlockResp(oamsCfgPschUnlockReqPtr->cellId,oamsCfgPschUnlockReqPtr->lac);
}

void pschLockReqHandler()
{
  OamsCfgPschLockReq *oamsCfgPschLockReqPtr;
  oamsCfgPschLockReqPtr = (OamsCfgPschLockReq*)cfgMsgBuf;
  cfgStubSendPschCfgLockResp(oamsCfgPschLockReqPtr->cellId,oamsCfgPschLockReqPtr->lac);
}

void cfgStubSendPschCfgUnlockResp(I_U32 cellId, I_U32 lac)
{
   OamsPschCfgUnlockResp oamsPschCfgUnlockRespBuff;
   printf("\nSending OAMS_PSCH_CFG_UNLOCK_RESP for Cellid = %u, lac = %u",cellId, lac);
   oamsPschCfgUnlockRespBuff.cellId = cellId;
   oamsPschCfgUnlockRespBuff.lac = lac;
   cfgPschStubSendMessage(&oamsPschCfgUnlockRespBuff, sizeof(OamsPschCfgUnlockResp), ENT_OAMS_PSCH, ENT_OAMS_CFG, OAMS_PSCH_CFG_UNLOCK_RESP,0);
}

void cfgStubSendPschCfgLockResp(I_U32 cellId, I_U32 lac)
{
   OamsPschCfgLockResp oamsPschCfgLockRespBuff;
   oamsPschCfgLockRespBuff.cellId = cellId;
   oamsPschCfgLockRespBuff.lac = lac;
   cfgPschStubSendMessage(&oamsPschCfgLockRespBuff, sizeof(OamsPschCfgLockResp), ENT_OAMS_PSCH, ENT_OAMS_CFG, OAMS_PSCH_CFG_LOCK_RESP,0);
}


I_S32 cfgPschStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   printf("\n\t Calling cfgPsscmStubSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      printf("CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   sndPtr->src.entity = SrcEntId;
   sndPtr->dest.entity = DestEntId;
    
   //sndPtr->dest.entity = DESTINATION;


   printf("\n sndPtr->msgType = %d", sndPtr->msgType);
   printf("\n sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   printf("\n sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);
   printf("\n Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      printf("\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   return(1);
}

