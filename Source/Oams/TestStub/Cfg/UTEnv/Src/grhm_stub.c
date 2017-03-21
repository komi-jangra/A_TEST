#include <includes.h>

I_U32 switchConnResp;
I_Void ExecuteGrhmAction(I_PVoid rcvPtr)
{
   I_U32 msgType = 0 ;
   msgType = ((SysHdr *)(rcvPtr))->msgType;

   switch(msgType)
   {
            case OAMS_CFG_GRHM_UNLOCK_REQ:
            {
               OamsCfgGrhmUnlockReq *grhmUnlockReq;
               grhmUnlockReq = (OamsCfgGrhmUnlockReq *)rcvPtr;
               // Send response from stub to CFG.
               LOG_PRINT(LOG_INFO,"\n Sending OAMS_CFG_GRHM_UNLOCK_RESP \n");
               CsappGrhmCfgUnlockResp CsappGrhmCfgUnlockRespBuff;
               CsappGrhmCfgUnlockRespBuff.objType = grhmUnlockReq->objType;
               CsappGrhmCfgUnlockRespBuff.objectId = grhmUnlockReq->objectId;
               CsappGrhmCfgUnlockRespBuff.reason = grhmUnlockReq->reason;
               cfgStubSendMessage(&CsappGrhmCfgUnlockRespBuff,sizeof(CsappGrhmCfgUnlockResp),ENT_CSAPP_GRHM, CSAPP_GRHM_CFG_UNLOCK_RESP,0);
            }
            break; 
            case OAMS_CFG_GRHM_LOCK_REQ:
            {
               OamsCfgGrhmLockReq *grhmLockReq;
               grhmLockReq = (OamsCfgGrhmUnlockReq *)rcvPtr;
               // Send response from stub to CFG.
               LOG_PRINT(LOG_INFO,"\n Sending OAMS_CFG_GRHM_LOCK_RESP \n");
               CsappGrhmCfgLockResp CsappGrhmCfgLockRespBuff;
               CsappGrhmCfgLockRespBuff.objType = grhmLockReq->objType;
               CsappGrhmCfgLockRespBuff.objectId = grhmLockReq->objectId;
               CsappGrhmCfgLockRespBuff.reason = grhmLockReq->reason;
               cfgStubSendMessage(&CsappGrhmCfgLockRespBuff,sizeof(CsappGrhmCfgLockResp),ENT_CSAPP_GRHM, CSAPP_GRHM_CFG_LOCK_RESP,0);
            }
            break; 
            case OAMS_CFG_GRHM_SWITCH_CONNECT:
            {
               LOG_PRINT(LOG_INFO,"\n Received OAMS_CFG_GRHM_SWITCH_CONNECT \n");
               OamsCfgGrhmSwitchConnect *oamsCfgGrhmSwitchConnectPtr = NULL;
               CsappGrhmCfgSwitchConnectAck csappGrhmCfgSwitchConnectAck;
               CsappGrhmCfgSwitchConnectNack csappGrhmCfgSwitchConnectNack;
               oamsCfgGrhmSwitchConnectPtr = (OamsCfgGrhmSwitchConnect *)rcvPtr;
               if (switchConnResp == ALL_OK)
               { 
                  csappGrhmCfgSwitchConnectAck.firstE1Num = oamsCfgGrhmSwitchConnectPtr->firstE1Num;
                  csappGrhmCfgSwitchConnectAck.firstTimeSlotNum = oamsCfgGrhmSwitchConnectPtr->firstTimeSlotNum;
                  cfgStubSendMessage(&csappGrhmCfgSwitchConnectAck,sizeof(CsappGrhmCfgSwitchConnectAck),ENT_CSAPP_GRHM,CSAPP_GRHM_CFG_SWITCH_CONNECT_ACK ,0);
               }
               else
               {
                  csappGrhmCfgSwitchConnectNack.firstE1Num = oamsCfgGrhmSwitchConnectPtr->firstE1Num;
                  csappGrhmCfgSwitchConnectNack.firstTimeSlotNum = oamsCfgGrhmSwitchConnectPtr->firstTimeSlotNum;
                  csappGrhmCfgSwitchConnectNack.cause = 4;
                  cfgStubSendMessage(&csappGrhmCfgSwitchConnectNack,sizeof(CsappGrhmCfgSwitchConnectNack),ENT_CSAPP_GRHM,CSAPP_GRHM_CFG_SWITCH_CONNECT_NACK ,0);
               }
            }
            break;  
            case OAMS_CFG_GRHM_SWITCH_DISCONNECT:
            {
               LOG_PRINT(LOG_INFO,"\n Received OAMS_CFG_GRHM_SWITCH_DISCONNECT \n");

            }
            break;  
   } 
}
