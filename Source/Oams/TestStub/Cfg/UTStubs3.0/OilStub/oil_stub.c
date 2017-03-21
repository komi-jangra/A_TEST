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
   const I_U32 SelfId = (int)ENT_OAM_OIL;
   err=RegisterWithIpcFrmwrk(SelfId, (I_S8 *)"OIL_STUB") ;
   if(err < 0)
   {
      printf("\nOIL_STUB : Unable to Register itself with IPC FrameWork : Exiting\n");
      printf("\nerr=%d\n",err);
      exit(EXIT_FAILURE);
   }

   while (1) {
      if ((rcvPtr = (I_Void *)RecvMsg(SelfId, &msgSize)) != NULL)
      {  
         msgType = ((SysHdr *)(rcvPtr))->msgType;
         printf("OIL_STUB :  Msg. size.(%d)",msgSize);
         printf("OIL_STUB :  Msg. Rcvd.(%d)",msgType);
         printf("OIL_STUB :  src (%d)", ((SysHdr *)(rcvPtr))->src.entity);
         printf("OIL_STUB :  src (%d)", ((SysHdr *)(rcvPtr))->dest.entity);

         switch(msgType)
         {
            case BSC_API_GET_CARDINFOTABLE :
               {
                  CardInfoTableApi CardInfoTableApiBuff={0};
                  LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
                  cfgStubSendMessage(&CardInfoTableApiBuff,sizeof(CardInfoTableApi),ENT_OAM_OIL,BSC_API_GET_CARDINFOTABLE,0);
                  break;
               }

            case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
               {
                  LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
                  OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
                  AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)rcvPtr;
                  OamOilCfgAvailableReleasesResp AvailRelRespBuff;
                  if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC)
                  {
                     LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BSC:\n");
                     AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BSC;
                     AvailRelRespBuff.numVersion = 0;
                     /*strcpy(AvailRelRespBuff.availSwVersions[0],"123.78.120");
                     memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                     strcpy(AvailRelRespBuff.availSwVersions[1],"123.0.201");
                     memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                     strcpy(AvailRelRespBuff.availSwVersions[2],"123.211.0");
                     memcpy(AvailRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-1.0.6",CMD_PARAM_MAX_SIZE);*/
                     cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
                  }
                  else if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC)
                  {
                     LOG_PRINT(LOG_INFO," Recived Releases req for SYS_NODE_TYPE_BIC:\n");
                     AvailRelRespBuff.nodeType = SYS_NODE_TYPE_BIC;
                     AvailRelRespBuff.numVersion = 0;
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
                     AvailRelRespBuff.numVersion = 0;
                     strcpy(AvailRelRespBuff.availSwVersions[0],"332.28.120");
                     memcpy(AvailRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-3.0.1",CMD_PARAM_MAX_SIZE);
                     strcpy(AvailRelRespBuff.availSwVersions[1],"1.210.1");
                     memcpy(AvailRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-3.2.7",CMD_PARAM_MAX_SIZE);
                     strcpy(AvailRelRespBuff.availSwVersions[2],"13.231.0");
                     memcpy(AvailRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-3.0.6",CMD_PARAM_MAX_SIZE);
                     cfgStubSendMessage(&AvailRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
                  }
                  break;
               }

            case OAMS_CFG_OIL_SW_OFFER_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
                  OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)rcvPtr;
                  OamOilCfgSwOfferResp swOfferRespBuff;
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  swOfferRespBuff.upgradeOfferResult = UPGRADE_OFFER_SUCCESSFUL;
                  else
                  swOfferRespBuff.upgradeOfferResult = ERROR_SPACE_UNAVAILABLE;
                  swOfferRespBuff.nodeType = swOfferReqPtr->nodeType;
                  strcpy(swOfferRespBuff.upgradeVersion,swOfferReqPtr->upgradeVersion);
                  memcpy(swOfferRespBuff.binaryPath,"/home/gur15644/Sw_Rel_SI/Bic/bic321.tar",CMD_PARAM_MAX_SIZE);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
                  cfgStubSendMessage(&swOfferRespBuff,sizeof(OamOilCfgSwOfferResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
                  break;
               }

            case OAMS_CFG_OIL_SW_ACT_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_ACT_REQ from Cfg..");
                  OamsCfgOilSwActReq *swActReqPtr = (OamsCfgOilSwActReq *)rcvPtr;
                  OamOilCfgSwActResp swActRespBuff;
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
									swActRespBuff.actResult = ACTIVATION_SUCCESSFUL;
                  else
									swActRespBuff.actResult = UNABLE_TO_ACTIVATE;
                  strcpy(swActRespBuff.actVersion,swActReqPtr->actVersion);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_ACT_RESP..");
                  cfgStubSendMessage(&swActRespBuff,sizeof(OamOilCfgSwActResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_ACT_RESP,0);
                  break;
               }

            case OAMS_CFG_OIL_SW_DEL_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
                  OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)rcvPtr;
                  OamOilCfgSwDelResp swDelRespBuff;
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  swDelRespBuff.versionDelResult = DELETE_SUCCESSFUL;
                  else
                  swDelRespBuff.versionDelResult = ERROR_VERSION_NOT_PRESENT;
                  swDelRespBuff.nodeType = swDelReqPtr->nodeType;
                  strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
                  cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
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

