#include <oamscfg_includes.h>
#include <cfg_stub_sw_upgrade_handler.h>
#include <bpmxxx_OAM_commonDef.h>
#define PLATFORM  20

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

int main()
{
   I_PVoid rcvPtr = NULL;
   I_U32 msgSize;
	 I_S32 choice;
   I_S8 err;
   I_U32 msgType = 0 ;
   I_S32 dbStatus;
   I_U32 index;
   I_U32 ch = 0;
   EicCardInfoTableApi eicData;
   memset(&eicData,0,sizeof(EicCardInfoTableApi));
   err = dbConnect();
   for(index=0;index<1;index++)
   {
      eicData.chasisFrameId=1;
      eicData.slotId=index;
      dbStatus=insertEicCardInfoTable(&eicData);
      if(dbStatus!=CLIB_SUCCESS)
      {
         LOG_PRINT(LOG_INFO,"Insertion in EicCardInfoTable failed ");
      }
   }
   
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
            case BSC_API_GET_ICCCARDINFOTABLE :
               {
                  IccCardInfoTableApi CardInfoTableApiBuff={0};
                  LOG_PRINT(LOG_INFO," Recived BSC_API_GET_CARDINFOTABLE:\n");
                  cfgStubSendMessage(&CardInfoTableApiBuff,sizeof(IccCardInfoTableApi),ENT_OAM_OIL,BSC_API_GET_ICCCARDINFOTABLE,0);
                  break;
               }

            case OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:
               {
                  LOG_PRINT(LOG_INFO," Recived OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ:\n");
                  OamsCfgOilAvailableReleasesReq *AvailRelReqPtr =NULL;
                  AvailRelReqPtr = (OamsCfgOilAvailableReleasesReq *)rcvPtr;
                  OamOilCfgAvailableReleasesResp availRelRespBuff;
                  OamOilCfgInfoAvailableVersion bpmAvailVersion;
                  I_U32 ch = 3;
                  strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[0],"");
                  strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[1],"");
                  strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[2],"");

                  LOG_PRINT(LOG_INFO," Recieved NodeType: %d", AvailRelReqPtr->nodeType);
                  if(AvailRelReqPtr->nodeType == SYS_NODE_TYPE_EIC || AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC || AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX || AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BSC)
                  {
                     bpmAvailVersion.nodeInfo.chasisFrameId = 1;
                     bpmAvailVersion.nodeInfo.slotId = 0;
                     bpmAvailVersion.nodeInfo.nodeType = AvailRelReqPtr->nodeType;
/*                     printf("\n\nEnter choice for No. of releases:\n(1) All the three versions\n(2) Only Two Versions\n(3) Only one Verison\n"); 
                     scanf("%d",&ch);*/
                     availRelRespBuff.nodeType = AvailRelReqPtr->nodeType;
                     availRelRespBuff.numVersion = 3;
                     availRelRespBuff.numVersion = 0;
                     if( ch == 1 || ch == 2 || ch == 3)
                     {
                        strcpy(availRelRespBuff.availSwVersions[0],"123.78.120");
                        memcpy(availRelRespBuff.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                        strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[0],"123.78.120");
                        memcpy(bpmAvailVersion.swMAvailResp.availSwBinaryPath[0],"/home/SoftRelease/Rel-1.0.1",CMD_PARAM_MAX_SIZE);
                        if( ch == 1 || ch == 2)
                        {
                           strcpy(availRelRespBuff.availSwVersions[1],"123.0.201");
                           memcpy(availRelRespBuff.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                           strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[1],"123.0.201");
                           memcpy(bpmAvailVersion.swMAvailResp.availSwBinaryPath[1],"/home/SoftRelease/Rel-1.0.7",CMD_PARAM_MAX_SIZE);
                           if( ch == 1)
                           {
                              strcpy(availRelRespBuff.availSwVersions[2],"123.211.0");
                              memcpy(availRelRespBuff.availSwBinaryPath[2],"/home/SoftRelease/Rel-1.0.6",CMD_PARAM_MAX_SIZE);
                              strcpy(bpmAvailVersion.swMAvailResp.availSwVersions[2],"123.211.0");
                              memcpy(bpmAvailVersion.swMAvailResp.availSwBinaryPath[2],"/home/SoftRelease/Rel-1.0.6",CMD_PARAM_MAX_SIZE);
                           }
                        }
                     }
                     else
                     {
                        printf("Invalid Choice");
                        break;
                     }
                     cfgStubSendMessage(&availRelRespBuff,sizeof(OamOilCfgAvailableReleasesResp),ENT_OAM_OIL,OAM_OIL_CFG_AVAILABLE_RELEASES_RESP,0);
                     bpmAvailVersion.moduleName = PLATFORM;
                     bpmAvailVersion.alarmLevel = TRAP_SEVERITY_INFORMATION;
                     bpmAvailVersion.alarmId = EVENT_SW_AVAILABLE_VERSION_IND;
                     bpmAvailVersion.swMAvailResp.nodeType = AvailRelReqPtr->nodeType;
                     bpmAvailVersion.swMAvailResp.numVersion = 3;
                      if(  AvailRelReqPtr->nodeType == SYS_NODE_TYPE_BIC || AvailRelReqPtr->nodeType == SYS_NODE_TYPE_TRX)
                        bpmAvailVersion.swMAvailResp.numVersion = 0;
                     cfgStubSendMessage(&bpmAvailVersion,sizeof(OamOilCfgInfoAvailableVersion),ENT_OAM_OIL,OAM_OIL_CFG_INFO_AVAILABLE_VERSION,0);
                  }
                  else
                     LOG_PRINT(LOG_MAJOR,"Invalid NodeId received in OAMS_CFG_OIL_AVAILABLE_RELEASES_REQ");   
                  break;
               }

            case OAMS_CFG_OIL_SW_OFFER_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_OFFER_REQ from Cfg..\n");
                  OamsCfgOilSwOfferReq *swOfferReqPtr = (OamsCfgOilSwOfferReq *)rcvPtr;
                  OamOilCfgInfoSwDwnldResult bpmDwnldResult;
                  
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_OFFER_RESP..");
                  cfgStubSendMessage(NULL,sizeof(SysHdr),ENT_OAM_OIL,OAM_OIL_CFG_SW_OFFER_RESP,0);
                  LOG_PRINT(LOG_INFO,"Sending INFO_BPM_SW_UPGRADE_OFFER.. Software Offer is in progress...");
                  bpmDwnldResult.nodeInfo.chasisFrameId = 1;
                  bpmDwnldResult.nodeInfo.slotId = 0;
                  bpmDwnldResult.nodeInfo.nodeType = swOfferReqPtr->nodeType;
                  bpmDwnldResult.moduleName = PLATFORM;
                  bpmDwnldResult.alarmId = EVENT_SW_UPGRADE_OFFER_IN_PROGRESS;
                  bpmDwnldResult.alarmLevel = TRAP_SEVERITY_INFORMATION;

                  bpmDwnldResult.swMOfferResp.nodeType = swOfferReqPtr->nodeType;
                  strcpy(bpmDwnldResult.swMOfferResp.upgradeVersion,swOfferReqPtr->upgradeVersion);
                  cfgStubSendMessage(&bpmDwnldResult,sizeof(OamOilCfgInfoSwDwnldResult),ENT_OAM_OIL,OAM_OIL_CFG_INFO_SW_UPGRADE_OFFER,0);

                  bpmDwnldResult.moduleName = PLATFORM;

                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  {
                     bpmDwnldResult.swMOfferResp.upgradeOfferResult = UPGRADE_OFFER_SUCCESSFUL;
                     bpmDwnldResult.alarmId = EVENT_SW_UPGRADE_OFFER_COMPLETED;
                     bpmDwnldResult.alarmLevel = TRAP_SEVERITY_INFORMATION;

                  }
                  else
		  {
                      printf("\nERROR CAUSE\tSpace unavailable (1)/ Error Writing to flash (2)");
                      printf("\nEnter your choice : ");
		      scanf("%d", &choice);
                      if(choice == 1)
                         bpmDwnldResult.swMOfferResp.upgradeOfferResult = ERROR_SPACE_UNAVAILABLE;
                      else
                         bpmDwnldResult.swMOfferResp.upgradeOfferResult = ERROR_WRITING_TO_FLASH;
                     bpmDwnldResult.alarmId = EVENT_SW_UPGRADE_OFFER_FAILED;
                     bpmDwnldResult.alarmLevel = TRAP_SEVERITY_MAJOR;
                  }
                  bpmDwnldResult.swMOfferResp.nodeType = swOfferReqPtr->nodeType;
                  strcpy(bpmDwnldResult.swMOfferResp.upgradeVersion,swOfferReqPtr->upgradeVersion);
                  memcpy(bpmDwnldResult.swMOfferResp.binaryPath,"/home/geetanjali/Sw_Rel_SI/Bic/bic321.tar",CMD_PARAM_MAX_SIZE);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_INFO_SW_UPGRADE_OFFER..");
                  cfgStubSendMessage(&bpmDwnldResult,sizeof(OamOilCfgInfoSwDwnldResult),ENT_OAM_OIL,OAM_OIL_CFG_INFO_SW_DWNLD_RESULT,0);
                  break;
               }

            case OAMS_CFG_OIL_SW_ACT_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_ACT_REQ from Cfg..");
                  OamsCfgOilSwActReq *swActReqPtr = (OamsCfgOilSwActReq *)rcvPtr;
                  OamOilCfgInfoSwActResult bpmActResult;


                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_ACT_RESP..");
                  cfgStubSendMessage(NULL,sizeof(SysHdr),ENT_OAM_OIL,OAM_OIL_CFG_SW_ACT_RESP,0);
                 
                  bpmActResult.nodeInfo.chasisFrameId = 1;
                  bpmActResult.nodeInfo.slotId = 0;
                  bpmActResult.nodeInfo.nodeType = swActReqPtr->nodeType;

                  bpmActResult.moduleName = PLATFORM;
                  bpmActResult.alarmId = EVENT_SW_ACT_STARTED;
                  bpmActResult.alarmLevel = TRAP_SEVERITY_INFORMATION;

                  bpmActResult.swMActResp.nodeType = swActReqPtr->nodeType;
                  strcpy(bpmActResult.swMActResp.actVersion,swActReqPtr->actVersion);

                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_INFO_BPM_SW_ACT_STARTED..");
                  cfgStubSendMessage(&bpmActResult,sizeof(OamOilCfgInfoSwActResult),ENT_OAM_OIL,OAM_OIL_CFG_INFO_SW_ACT_STARTED,0);
        
                  bpmActResult.moduleName = PLATFORM;

                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  if(choice ==1)
                  {
		     bpmActResult.swMActResp.actResult = ACTIVATION_SUCCESSFUL;
                     bpmActResult.alarmLevel = TRAP_SEVERITY_INFORMATION;
                     bpmActResult.alarmId = EVENT_SW_ACT_COMPLETED;
                  }

                  else
                  {
                      printf("\nERROR CAUSE\tUnable to activate (1)/ Error Activation Failure (2)");
                      printf("\nEnter your choice : ");
		      scanf("%d", &choice);
                      if(choice == 1)
                         bpmActResult.swMActResp.actResult = UNABLE_TO_ACTIVATE;
                      else
                         bpmActResult.swMActResp.actResult = ERROR_ACTIVATION_FAILURE;
                     bpmActResult.alarmLevel = TRAP_SEVERITY_MAJOR;
                     bpmActResult.alarmId = EVENT_SW_ACT_FAILED;
                  }

	          bpmActResult.swMActResp.nodeType = swActReqPtr->nodeType;
                  strcpy(bpmActResult.swMActResp.actVersion,swActReqPtr->actVersion);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_INFO_BPM_SW_ACT_SUCCESS..");
                  cfgStubSendMessage(&bpmActResult,sizeof(OamOilCfgInfoSwActResult),ENT_OAM_OIL,OAM_OIL_CFG_INFO_SW_ACT_RESULT,0);
                  break;
               }

            case OAMS_CFG_OIL_SW_DEL_REQ:
               {
                  LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_SW_DEL_REQ from Cfg..");
                  OamsCfgOilSwDelReq *swDelReqPtr = (OamsCfgOilSwDelReq *)rcvPtr;
                  OamOilCfgSwDelResp swDelRespBuff;
                  OamOilCfgInfoDelResult bpmDelResult;
                  LOG_PRINT(LOG_INFO,"NodeType:%d",swDelReqPtr->nodeType);
                  LOG_PRINT(LOG_INFO,"NodeType:%s",swDelReqPtr->delVersion);
                  printf("\n\n 1.SUCCESS\t2.FAILURE\n Enter your choice:");
                  scanf("%d",&choice);
                  bpmDelResult.nodeInfo.chasisFrameId = 1;
                  bpmDelResult.nodeInfo.slotId = 0;
                  bpmDelResult.nodeInfo.nodeType = swDelReqPtr->nodeType;

                  bpmDelResult.moduleName = PLATFORM;
                  if(choice ==1)
                  {
                     swDelRespBuff.versionDelResult = DELETE_SUCCESSFUL;
                     bpmDelResult.alarmLevel = TRAP_SEVERITY_INFORMATION;
                     bpmDelResult.alarmId = EVENT_SW_DEL_COMPLETED;
                     bpmDelResult.swMDelResp.versionDelResult = DELETE_SUCCESSFUL;
                  }
                  else
                  {
                     swDelRespBuff.versionDelResult = ERROR_CONNECTING_UA_CP;
                     bpmDelResult.alarmLevel = TRAP_SEVERITY_MAJOR;
                     bpmDelResult.alarmId = EVENT_SW_DEL_FAILED;
                     bpmDelResult.swMDelResp.versionDelResult = ERROR_CONNECTING_UA_CP;
                  }
                  swDelRespBuff.nodeType = swDelReqPtr->nodeType;
                  bpmDelResult.swMDelResp.nodeType = swDelReqPtr->nodeType;
                  strcpy(swDelRespBuff.delVersion,swDelReqPtr->delVersion);
                  strcpy(bpmDelResult.swMDelResp.delVersion,swDelReqPtr->delVersion);
                  LOG_PRINT(LOG_INFO,"Sending OAM_OIL_CFG_SW_DEL_RESP..");
                  cfgStubSendMessage(&swDelRespBuff,sizeof(OamOilCfgSwDelResp),ENT_OAM_OIL,OAM_OIL_CFG_SW_DEL_RESP,0);
                  cfgStubSendMessage(&bpmDelResult,sizeof(OamOilCfgInfoDelResult),ENT_OAM_OIL,OAM_OIL_CFG_INFO_DEL_VERSION_RESULT,0);
                  break;
               }
                        /*BSC CS4.0 : Init Changes starts*/
            case OAMS_CFG_OIL_BPM_DB_INITIALIZED:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_OIL_BPM_DB_INITIALIZED from Cfg..");
               LOG_PRINT(LOG_INFO,"Sending  OAM_OIL_CFG_SYSTEM_DETAILS from Cfg..");
               sendBpmDbInit();
               break;
            }
            case OAMS_CFG_OIL_TRUNK_STATE_CHANGE_REQ:
            {
               OamsCfgOilE1EnableReq *oamsCfgOilE1EnableReq = (OamsCfgOilE1EnableReq *)rcvPtr;
               sendTrunkStateChangeResp(oamsCfgOilE1EnableReq);
               break;
            }
            case OAMS_CFG_OIL_SET_CLK_SRC_REQ:
            {
               OamsCfgOilSetClkSrcReq *oamsCfgOilSetClkSrcReq = (OamsCfgOilSetClkSrcReq *)rcvPtr;
               sendClockSourceResp(oamsCfgOilSetClkSrcReq);
               break;
            }
                        /*BSC CS4.0 : Init Changes Ends*/
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

I_Void sendClockSourceResp(OamsCfgOilSetClkSrcReq *oamsCfgOilSetClkSrcReq)
{
   I_U32 count;
   OamOilCfgSetClkSrcResp oamOilCfgSetClkSrcResp;
   I_U32 maxClkConfig;
   I_U32 frameId;
   I_U32 slotId;
   I_U32 trunkPortId;
   I_U32 priority;
   
   printf("\nSending Clock Source Resp");
   while(1)
   {
      printf("\nEnter number of Clock Source (<= 5):: "); 
      scanf("%d" , &maxClkConfig);
      oamOilCfgSetClkSrcResp.maxClkConfig = maxClkConfig;
      if(oamOilCfgSetClkSrcResp.maxClkConfig <= 5)
         break;
      else
         printf("\nInvalid Input");
   
   }
   oamOilCfgSetClkSrcResp.result = 0;
   for(count = 0 ; count < oamOilCfgSetClkSrcResp.maxClkConfig ; count++)
   {
      printf("\nEnter Frame Id::  ");
      scanf("%d" ,&frameId );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].frameId =frameId;
      printf("\nEnter Slot Id::  ");
      scanf("%d" ,&slotId );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].slotId =slotId;
      printf("\nEnter Trunk Port Id::  ");
      scanf("%d" ,&trunkPortId );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].trunkPortId =trunkPortId;
      printf("\nEnter Priority::  ");
      scanf("%d" ,&priority );
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].priority =priority;
      oamOilCfgSetClkSrcResp.clkSrcPriorityResult[count].result = 0;
   }
   cfgStubSendMessage(&oamOilCfgSetClkSrcResp, sizeof(OamOilCfgSetClkSrcResp),ENT_OAM_OIL,OAM_OIL_CFG_SET_CLK_SRC_RESP,0);
   
}
I_Void sendTrunkStateChangeResp(OamsCfgOilE1EnableReq *oamsCfgOilE1EnableReq)
{
   OamOilCfgE1EnableResp oamOilCfgE1EnableResp;
   I_U32 count;
   printf("\nTrunk State Change Resp.........");
   oamOilCfgE1EnableResp.numPorts = oamsCfgOilE1EnableReq->numPorts;
   oamOilCfgE1EnableResp.transactionId = oamsCfgOilE1EnableReq->transactionId;
   oamOilCfgE1EnableResp.result = 0;
   for(count = 0 ; count < oamsCfgOilE1EnableReq->numPorts ; count++)
   {
      oamOilCfgE1EnableResp.portResult[count].frameId = oamsCfgOilE1EnableReq->portDetail[count].frameId;
      oamOilCfgE1EnableResp.portResult[count].slotId = oamsCfgOilE1EnableReq->portDetail[count].slotId;
      oamOilCfgE1EnableResp.portResult[count].trunkPortId = oamsCfgOilE1EnableReq->portDetail[count].trunkPortId;
      oamOilCfgE1EnableResp.portResult[count].result = 0;
   }
   cfgStubSendMessage(&oamOilCfgE1EnableResp, sizeof(OamOilCfgE1EnableResp),ENT_OAM_OIL,OAM_OIL_CFG_TRUNK_STATE_CHANGE_RESP,0);
   
}
I_Void sendBpmDbInit()
{
   OamOilCfgBpmDbInitResp oamOilCfgBpmDbInitResp;
   I_U32 count;
   
   memset(&oamOilCfgBpmDbInitResp.cardInfo, 0, sizeof(OamOilCfgBpmDbInitResp));

   //Filling System Type Details
   oamOilCfgBpmDbInitResp.cardInfo.systemType = 1;

   //Filling numOfTrumkPort
   oamOilCfgBpmDbInitResp.cardInfo.numTrunkPort = 8;

   //Filling TotalNumOfCard
   oamOilCfgBpmDbInitResp.cardInfo.totalNumCards = 4;

   //Filling TotalNumOfRemoteCard
   oamOilCfgBpmDbInitResp.cardInfo.numRemoteCards = 2;

   //Filling SelfCardInfo
   oamOilCfgBpmDbInitResp.cardInfo.selfInfo.frameID = 1;
   oamOilCfgBpmDbInitResp.cardInfo.selfInfo.slotID = 3;
   oamOilCfgBpmDbInitResp.cardInfo.selfInfo.peerCardPresence = 1;
   
   //Filling MateCardInfo
   oamOilCfgBpmDbInitResp.cardInfo.mateInfo.frameID = 1;
   oamOilCfgBpmDbInitResp.cardInfo.mateInfo.slotID = 4;
   oamOilCfgBpmDbInitResp.cardInfo.mateInfo.peerCardPresence = 1;
   
   //Filling EicCardInfo
   oamOilCfgBpmDbInitResp.cardInfo.eicInfo[0].frameID = 1;
   oamOilCfgBpmDbInitResp.cardInfo.eicInfo[0].slotID = 5;
   oamOilCfgBpmDbInitResp.cardInfo.eicInfo[1].frameID = 1;
   oamOilCfgBpmDbInitResp.cardInfo.eicInfo[1].slotID = 6;
   
   //Filling DspInfo
   oamOilCfgBpmDbInitResp.cardInfo.dspInfo.frameID = 1;
   oamOilCfgBpmDbInitResp.cardInfo.dspInfo.slotID = 3;

   //Filling TrunkPortInfo
   oamOilCfgBpmDbInitResp.cardInfo.portInfo.numOfPort = 8;
   for(count = 0 ; count < 8 ; count++)
   {
      oamOilCfgBpmDbInitResp.cardInfo.portInfo.portInfo[count].frameID = 1;
      oamOilCfgBpmDbInitResp.cardInfo.portInfo.portInfo[count].slotID = 3;
      oamOilCfgBpmDbInitResp.cardInfo.portInfo.portInfo[count].portID = count;
   }
   
   //Filling SystemClockInfo
   oamOilCfgBpmDbInitResp.cardInfo.sysClkInfo.clockReference = REFERENCE_INTERNAL_CLK;

   cfgStubSendMessage(&oamOilCfgBpmDbInitResp, sizeof(OamOilCfgBpmDbInitResp), ENT_OAM_OIL, OAM_OIL_CFG_BPM_DB_INIT_RESP, 0);
}
               
   
