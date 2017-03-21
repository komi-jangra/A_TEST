#include <oamscfg_includes.h>
#include "cfg_stub_grhm.h"

SysHdr*    sysHdrPtr;
I_S32 srcId;           /* SrcId for the CFG */
void *cfgMsgBuf;       /* Message Pointer for the received message */
I_U32 recvMsgSize;  /* received message size */


I_S32 cfgGrhmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   printf("\n\t Calling cfgGrhmStubSendMessage().....");

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

void sendLockResptoCFG() 
{
    I_Void * msgBuffer;
    I_S32 msgSize;
    msgSize = sizeof(CsappGrhmCfgLockResp);
    msgBuffer = AlocMsgBuf(msgSize);
    memset(msgBuffer, 0,msgSize);
    ((CsappGrhmCfgLockResp*) msgBuffer)->objType =OAMS_OBJTYPE_AINTERFACE ;
    ((CsappGrhmCfgLockResp *)msgBuffer)->objectId = 0;
   printf("sending Lock Resp to CFG\n");
   cfgGrhmStubSendMessage((CsappGrhmCfgLockResp *)msgBuffer, sizeof(CsappGrhmCfgLockResp), ENT_CSAPP_GRHM,ENT_OAMS_CFG, CSAPP_GRHM_CFG_LOCK_RESP,0);
}

void sendUnlockResptoCFG() 
{
    I_Void * msgBuffer;
    I_S32 msgSize;
    msgSize = sizeof(CsappGrhmCfgUnlockResp);
    msgBuffer = AlocMsgBuf(msgSize);
    memset(msgBuffer, 0,msgSize);
    ((CsappGrhmCfgUnlockResp*) msgBuffer)->objType =OAMS_OBJTYPE_AINTERFACE ;
    ((CsappGrhmCfgUnlockResp *)msgBuffer)->objectId = 0;
   printf("sending UnLock Resp to CFG\n");
   cfgGrhmStubSendMessage((CsappGrhmCfgUnlockResp *)msgBuffer, sizeof(CsappGrhmCfgUnlockResp), ENT_CSAPP_GRHM,ENT_OAMS_CFG, CSAPP_GRHM_CFG_UNLOCK_RESP,0);
}
void cfgFrmwrkInit(I_S32 srcId)
{
   I_S8 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(srcId, (I_S8*)"CFG_GRHM_STUB");
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
   printf("GRHM CFG Stub \n");
   printf("\n GRHM Configured \n");
   grhmReqHandler();
   return 1;
}

void grhmReqHandler()
{
   cfgFrmwrkInit(ENT_CSAPP_GRHM);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_CSAPP_GRHM, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
              case  OAMS_CFG_GRHM_SWITCH_CONNECT:
                 printf("Received Msg :  OAMS_CFG_GRHM_SWITCH_CONNECT");
	         //switchConnectHandler();
      	         break;
              case  OAMS_CFG_GRHM_SWITCH_DISCONNECT:
                 printf("Received Msg :  OAMS_CFG_GRHM_SWITCH_DISCONNECT");
                 break;
              case  OAMS_CFG_GRHM_UNLOCK_REQ:
                 printf("Received Msg :  OAMS_CFG_GRHM_UNLOCK_REQ");
                 sendUnlockResptoCFG();
                 break;
              case  OAMS_CFG_GRHM_LOCK_REQ:
                 printf("Received Msg :  OAMS_CFG_GRHM_LOCK_REQ");
                 sendLockResptoCFG();
	         //switchDisconnectHandler();
      	         break;
      }
      DalocMsgBuf(cfgMsgBuf);
   }
   
}


