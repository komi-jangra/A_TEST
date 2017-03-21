#include <oamscfg_includes.h>
#include "cfg_stub_rm.h"

SysHdr*    sysHdrPtr;
I_S32 srcId;           /* SrcId for the CFG */
I_Void *cfgMsgBuf;       /* Message Pointer for the received message */
I_U32 recvMsgSize;  /* received message size */

I_Void cfgFrmwrkInit(I_S32 srcId)
{
   I_S8 retVal;
   printf("\nCFG: Calling function cfgFrmwrkInit()");
   retVal = RegisterWithIpcFrmwrk(srcId, (I_S8*)"CFG_RM_STUB");
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
   printf("RM CFG Stub \n");
   printf("\n RM Configured \n");
   rmReqHandler();
   return 1;
}
 
void rmReqHandler()
{
   cfgFrmwrkInit(ENT_OAMS_RM);
   while(1)
   {
      cfgMsgBuf = (void *)RecvMsg(ENT_OAMS_RM, &recvMsgSize);
      if (cfgMsgBuf == NULL)
      {
         continue;
      }
      sysHdrPtr =  (SysHdr *) cfgMsgBuf;
      switch( sysHdrPtr->msgType)
      {
      	case OAMS_CFG_RM_SLOTID_REQ:
            printf("Received Msg : OAMS_CFG_RM_SLOTID_REQ");
	         slotIdReqHandler();
      	   break;
	      case OAMS_CFG_RM_PEER_SWITCH_CONNECT:
	         printf("Recieved Msg : OAMS_CFG_RM_PEER_SWITCH_CONNECT");
	         peerSwitchConnectHandler();
	         break;
      }
      DalocMsgBuf(cfgMsgBuf);
   }
   
}

void slotIdReqHandler() 
{
   OamsRmCfgSlotIdResp oamsRmCfgSlotIdResp;
   printf("RM SlotId Request\n");
   printf("Enterh My SlotId");
   scanf("%d", &oamsRmCfgSlotIdResp.mySlotId);
   printf("Enter Peer SlotId");
   scanf("%d", &oamsRmCfgSlotIdResp.peerSlotId);
   cfgRmStubSendMessage(&oamsRmCfgSlotIdResp, sizeof(OamsRmCfgSlotIdResp), ENT_OAMS_RM, ENT_OAMS_CFG, OAMS_RM_CFG_SLOTID_RESP,0);
}

void peerSwitchConnectHandler() 
{
   OamsCfgRmPeerSwitchConnect *oamsCfgRmPeerSwitchConnectPtr = NULL;
   OamsRmCfgPeerSwitchConnectAck oamsRmCfgPeerSwitchConnectAck;
   OamsRmCfgPeerSwitchConnectNack oamsRmCfgPeerSwitchConnectNack;
   I_U8 ch;
   oamsCfgRmPeerSwitchConnectPtr = (OamsCfgRmPeerSwitchConnect *) cfgMsgBuf;
   printf("\nEnter Your Choice ACK 0/NACK 1:: ");
   scanf("%c", ch);
   if ( ch == 1)
   {
      oamsRmCfgPeerSwitchConnectNack.srcE1 = oamsCfgRmPeerSwitchConnectPtr->srcE1;
      oamsRmCfgPeerSwitchConnectNack.srcTs = oamsCfgRmPeerSwitchConnectPtr->srcTs;
      oamsRmCfgPeerSwitchConnectNack.cause = 1;
      cfgRmStubSendMessage(&oamsRmCfgPeerSwitchConnectNack, sizeof(oamsRmCfgPeerSwitchConnectNack), ENT_OAMS_RM, ENT_OAMS_CFG, OAMS_RM_CFG_PEER_SWITCH_NACK,0);
   }
   else if(ch == 0)
   {
      oamsRmCfgPeerSwitchConnectAck.srcE1 = oamsCfgRmPeerSwitchConnectPtr->srcE1;
      oamsRmCfgPeerSwitchConnectAck.srcTs = oamsCfgRmPeerSwitchConnectPtr->srcTs;
      cfgRmStubSendMessage(&oamsRmCfgPeerSwitchConnectAck, sizeof(oamsRmCfgPeerSwitchConnectAck), ENT_OAMS_RM, ENT_OAMS_CFG, OAMS_RM_CFG_PEER_SWITCH_ACK,0);
   }
   else
      printf("Wrong Choice");
   
}


I_S32 cfgRmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType)
{
   SysHdr   *sndPtr;
   I_S16  sndMsgSize;
   sndMsgSize = 0;
   printf("\n\t Calling cfgRmStubSendMessage().....");

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
