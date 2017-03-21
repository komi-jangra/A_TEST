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
   I_S8 err;
   I_U32 msgType = 0 ;
   const I_U32 SelfId = (int)ENT_OAM_AFH;
   err=RegisterWithIpcFrmwrk(SelfId, (I_S8 *)"AFH_STUB") ;
   if(err < 0)
   {
      printf("\nAFH_STUB : Unable to Register itself with IPC FrameWork : Exiting\n");
      printf("\nerr=%d\n",err);
      exit(EXIT_FAILURE);
   }

   while (1) {
      if ((rcvPtr = (I_Void *)RecvMsg(SelfId, &msgSize)) != NULL)
      {  
         msgType = ((SysHdr *)(rcvPtr))->msgType;
         printf("AFH_STUB :  Msg. size.(%d)",msgSize);
         printf("AFH_STUB :  Msg. Rcvd.(%d)",msgType);
         printf("AFH_STUB :  src (%d)", ((SysHdr *)(rcvPtr))->src.entity);
         printf("AFH_STUB :  src (%d)", ((SysHdr *)(rcvPtr))->dest.entity);

         switch(msgType)
         {
					 case OAMS_CFG_AFH_ALARM_IND:
            {
               LOG_PRINT(LOG_INFO,"Recieved OAMS_CFG_AFH_ALARM_IND from Cfg..\n");
               OamsCfgAfhSysAlarm *sysAlarmPtr = (OamsCfgAfhSysAlarm *)rcvPtr;
               LOG_PRINT(LOG_INFO,"Alarm Id: %d ",sysAlarmPtr->sysAlarm.sysalarmId);
               LOG_PRINT(LOG_INFO,"Info3 : %d ",sysAlarmPtr->sysAlarm.info3);
               LOG_PRINT(LOG_INFO,"Key1 : %d ",sysAlarmPtr->sysAlarm.key1);
               LOG_PRINT(LOG_INFO,"AlarmLevel : %d ",sysAlarmPtr->sysAlarm.alarmLevel);
               LOG_PRINT(LOG_INFO,"InfoStrLen : %d ",sysAlarmPtr->sysAlarm.infoStrLen);
               LOG_PRINT(LOG_INFO,"InfoString : %s ",sysAlarmPtr->sysAlarm.infoString);
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

