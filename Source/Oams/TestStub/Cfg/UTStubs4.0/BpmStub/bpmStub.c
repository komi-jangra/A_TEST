#include "oamscfg_includes.h"
#include "cfg_bpm_stub.h"


BpmStubCfgNotification bpmStubCfgNotification;

I_Void *recvMsgBuf = NULL;
I_Void *sendBuff = NULL;
int main()
{    

   I_U32 choice = 0;
   
   I_U32 msgSize;
   if (RegisterWithIpcFrmwrk(ENT_BPM_STUB, (I_S8*)"BPM_STUB") < ZERO )
   {
      LOG_PRINT(INFO,"\n\nNot register with IPC\n\n ");
   }
   else
   {
      LOG_PRINT(INFO,"\n\nRegister with IPC\n ");
   }
   while(1)
   {
      printf("\n Enter Choice to State Notification");
      printf("\n 0:: Exit");
      printf("\n 1:: CARDSTATE_INIT");
      printf("\n 2:: CARDSTATE_PLATFORM_INS");
      printf("\n 3:: CARDSTATE_IN_SERVICE");
      printf("\n 4:: CARDSTATE_ACTIVE");
      printf("\n 5:: CARDSTATE_ACTIVE_IN_PROGRESS");
      printf("\n 6:: CARDSTATE_STANDBY");
      printf("\n 7:: CARDSTATE_OUT_OF_SERVICE");
      printf("\n 8:: CARDSTATE_RECOVERY");
      printf("\n 9:: CARDSTATE_FAIL");
      printf("\n 10:: CARDSTATE_TEST");
      printf("\n 11:: CARDSTATE_ABSENT");
      printf("\n Enter the Notification:: ");
      fflush(stdin);
      scanf("%d",&choice);
      switch(choice)
      {
         case 0:
            exit(0);
         case 1:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_INIT;
            break;
          case 2:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_PLATFORM_INS;
            break;
         case 3:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_IN_SERVICE;
            break;
         case 4:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_ACTIVE;
            break;
         case 5:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_ACTIVE_IN_PROGRESS;
            break;
         case 6:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_STANDBY;
            break;
         case 7:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_OUT_OF_SERVICE;
            break;
         case 8:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_RECOVERY;
            break;
         case 9:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_FAIL;
            break;
         case 10:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_TEST;
            break;
         case 11:
            bpmStubCfgNotification.param.messageId = BPM_SELFCARD_STATE_CHANGE;
            bpmStubCfgNotification.param.cardState = CARDSTATE_ABSENT;
            break;
         default :
            LOG_PRINT(INFO,"\nEnter right choice");
            break;        
      }
      cfgBpmStubSendMessage(&bpmStubCfgNotification, sizeof(BpmStubCfgNotification), ENT_BPM_STUB, ENT_CFG_THREAD, BPM_STUB_CFG_NOTIFICATION,0);


   }
}

I_S32 cfgBpmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   printf("\n\t Calling cfgBpmStubSendMessage().....");

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

