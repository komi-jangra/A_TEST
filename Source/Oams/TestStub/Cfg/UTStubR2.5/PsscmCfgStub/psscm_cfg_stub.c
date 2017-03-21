#include <oamscfg_includes.h>
#include "cfg_stub_psscm.h"

SysHdr*    sysHdrPtr;
I_S32 srcId;           /* SrcId for the CFG */
void *cfgMsgBuf;       /* Message Pointer for the received message */
I_U32 recvMsgSize;  /* received message size */

void cfgFrmwrkInit(I_S32 srcId)
{
   I_S8 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(srcId, (I_S8*)"CFG_PSSCM_STUB");
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
   printf("PSSCM CFG Stub \n");
   printf("\n PSSCM Configured \n");
   psscmReqHandler();
   return 1;
}

void psscmReqHandler()
{
   cfgFrmwrkInit(ENT_OAMS_PSSCM);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_OAMS_PSSCM, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
              case  OAMS_CFG_NSVCH_UNLOCK_REQ:
                 printf("Received Msg :  OAMS_CFG_NSVCH_UNLOCK_REQ");
	         nsvchUnlockReqHandler();
      	         break;
              case  OAMS_CFG_NSVCH_LOCK_REQ:
                 printf("Received Msg :  OAMS_CFG_NSVCH_LOCK_REQ");
	         nsvchLockReqHandler();
      	         break;
              case  OAMS_NSVCH_CFG_ALARM_IND:
                 printf("Received Msg :  OAMS_NSVCH_CFG_ALARM_IND");
      	         break;
      }
      DalocMsgBuf(cfgMsgBuf);
   }
   
}

void nsvchUnlockReqHandler()
{
  OamsCfgNsvchUnlockReq *oamsCfgNsvchUnlockReqPtr;
  oamsCfgNsvchUnlockReqPtr = (OamsCfgNsvchUnlockReq*)cfgMsgBuf;
  cfgStubSendNsvchCfgUnlockResp(oamsCfgNsvchUnlockReqPtr->nsvcId);
}

void nsvchLockReqHandler()
{
  OamsCfgNsvchLockReq *oamsCfgNsvchLockReqPtr;
  oamsCfgNsvchLockReqPtr = (OamsCfgNsvchLockReq*)cfgMsgBuf;
  cfgStubSendNsvchCfgLockResp(oamsCfgNsvchLockReqPtr->nsvcId);
}

void cfgStubSendNsvchCfgUnlockResp(I_U32 nsvcId)
{
   OamsNsvchCfgUnlockResp oamsNsvchCfgUnlockRespBuff;
   oamsNsvchCfgUnlockRespBuff.nsvcId = nsvcId;
   cfgPsscmStubSendMessage(&oamsNsvchCfgUnlockRespBuff, sizeof(OamsNsvchCfgUnlockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_NSVCH_CFG_UNLOCK_RESP,0);
}

void cfgStubSendNsvchCfgLockResp(I_U32 nsvcId)
{
   OamsNsvchCfgLockResp oamsNsvchCfgLockRespBuff;
   oamsNsvchCfgLockRespBuff.nsvcId = nsvcId;
   cfgPsscmStubSendMessage(&oamsNsvchCfgLockRespBuff, sizeof(OamsNsvchCfgLockResp), ENT_OAMS_PSSCM, ENT_OAMS_CFG, OAMS_NSVCH_CFG_LOCK_RESP,0);
}


I_S32 cfgPsscmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
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

