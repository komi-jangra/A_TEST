#include <oamscfg_includes.h>
#include <cfg_stub_sw_upgrade_handler.h>

I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;

   sndMsgSize = 0;

   LOG_PRINT(LOG_INFO,"\n\t Calling cfgStubSendMessage().....");

   if (bufPtr != NULL)
      sndMsgSize = size;
   else
      sndMsgSize = sizeof(SysHdr);

   if ((sndPtr = (SysHdr *)AlocMsgBuf(sndMsgSize)) == NULL)
   {
      LOG_PRINT(LOG_INFO,"CFG_SEND_ALLOC_FAIL");
      return -1; 
   }

   memset(sndPtr,0,sndMsgSize) ;
   if (bufPtr != NULL)
      memcpy(((I_U8 *)sndPtr), (I_U8*)bufPtr, size);

   sndPtr->msgType = msgType;
   sndPtr->src.entity = SrcEntId;
   /* sndPtr->dest.entity = DestEntId;
   */
   sndPtr->dest.entity = ENT_OAMS_CFG;


   LOG_PRINT(LOG_INFO,"\n sndPtr->msgType = %d", sndPtr->msgType);
   LOG_PRINT(LOG_INFO,"\n sndPtr->sHdr.src.entity = %d", sndPtr->src.entity);
   LOG_PRINT(LOG_INFO,"\n sndPtr->sHdr.dest.entity = %d", sndPtr->dest.entity);

   LOG_PRINT(LOG_INFO,"\n Sending message ...........");

   fflush(stdin);
   if (SendMsg(sndPtr, 1, sndMsgSize) < 0)
   {
      LOG_PRINT(LOG_INFO,"\nCFG: In func cfgSendMessage() - msg sending failed");
      DalocMsgBuf((I_PVoid) sndPtr);
      return(-1);
   }
   return(1);
}

main()
{
   I_PVoid rcvPtr = NULL;
   I_U32 msgSize;
   I_S32 choice;
   I_S8 err;
   I_U32 msgType = 0 ;
   const I_U32 SelfId = (int)ENT_OAMS_SWMH;
   err=RegisterWithIpcFrmwrk(SelfId, (I_S8 *)"SWMH_STUB") ;
   if(err < 0)
   {
      printf("\nSWMH_STUB : Unable to Register itself with IPC FrameWork : Exiting\n");
      printf("\nerr=%d\n",err);
      exit(EXIT_FAILURE);
   }

   while (1) {
      if ((rcvPtr = (I_Void *)RecvMsg(SelfId, &msgSize)) != NULL)
      {  
         msgType = ((SysHdr *)(rcvPtr))->msgType;
         printf("SWMH_STUB :  Msg. size.(%d)",msgSize);
         printf("SWMH_STUB :  Msg. Rcvd.(%d)",msgType);
         printf("SWMH_STUB :  src (%d)", ((SysHdr *)(rcvPtr))->src.entity);
         printf("SWMH_STUB :  src (%d)", ((SysHdr *)(rcvPtr))->dest.entity);

         switch(msgType)
         {
            case OAMS_CFG_SWMH_SW_DNLD_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_DNLD_REQ from Cfg..");
                  OamsCfgSwmhSwDnldReq *swDnldReqPtr = (OamsCfgSwmhSwDnldReq *)rcvPtr;
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  {
                     OamsSwmhCfgSwDnldAck swDnldAckBuff;
                     swDnldAckBuff.nodeType = swDnldReqPtr->nodeType;
                     swDnldAckBuff.nodeIdentity = swDnldReqPtr->nodeIdentity;
                     strcpy(swDnldAckBuff.swVersion,swDnldReqPtr->swVersion);
                     LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_DNLD_ACK..");
                     cfgStubSendMessage(&swDnldAckBuff,sizeof(OamsSwmhCfgSwDnldAck),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_DNLD_ACK,0);
                  }
                  else
                  {
                     OamsSwmhCfgSwDnldNack swDnldNackBuff;
                     swDnldNackBuff.nodeType = swDnldReqPtr->nodeType;
                     swDnldNackBuff.nodeIdentity = swDnldReqPtr->nodeIdentity;
                     strcpy(swDnldNackBuff.swVersion,swDnldReqPtr->swVersion);
                     swDnldNackBuff.nackCause = CAUSE_RESOURCE_NOT_AVAILABLE;
                     LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_DNLD_NACK..");
                     cfgStubSendMessage(&swDnldNackBuff,sizeof(OamsSwmhCfgSwDnldNack),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_DNLD_NACK,0);                                                                                                       
                  }
                  break;
               }

            case OAMS_CFG_SWMH_SW_ACT_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_SWMH_SW_ACT_REQ from Cfg..");
                  OamsCfgSwmhSwActReq *swActReqPtr = (OamsCfgSwmhSwActReq *)rcvPtr;
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  {
                     OamsSwmhCfgSwActAck swActAckBuff;
                     swActAckBuff.nodeType = swActReqPtr->nodeType;
                     swActAckBuff.nodeIdentity = swActReqPtr->nodeIdentity;
                     strcpy(swActAckBuff.swVersion,swActReqPtr->swVersion);
                     LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_ACT_ACK..");
                     cfgStubSendMessage(&swActAckBuff,sizeof(OamsSwmhCfgSwActAck),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_ACT_ACK,0);
                  }
                  else
                  {
                     OamsSwmhCfgSwActNack swActNackBuff;
                     swActNackBuff.nodeType = swActReqPtr->nodeType;
                     swActNackBuff.nodeIdentity = swActReqPtr->nodeIdentity;
                     strcpy(swActNackBuff.swVersion,swActReqPtr->swVersion);
                     swActNackBuff.nackCause = OAMS_CAUSE_FILE_SYSTEM_ERROR;  
                     LOG_PRINT(LOG_INFO,"Sending OAMS_SWMH_CFG_SW_ACT_NACK..");
                     cfgStubSendMessage(&swActNackBuff,sizeof(OamsSwmhCfgSwActNack),ENT_OAMS_SWMH,OAMS_SWMH_CFG_SW_ACT_NACK,0);
                  }
                  break;
               }

            default:
               {
                  LOG_PRINT(LOG_INFO," No Message handling for the message Type : %d \n",(((SysHdr*) rcvPtr)->msgType));
                  break;
               }
         }//switch
         DalocMsgBuf(rcvPtr);
      }//if ((rcvPtr = (I_Void *)RecvMsg(SelfId, &msgSize)) != NULL)
   }//while(1)
}   

