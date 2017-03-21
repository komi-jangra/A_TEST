#ifndef _CFG_STUB_RM_HANDLER_H_
#define _CFG_STUB_RM_HANDLER_H_	1

I_Void rmReqHandler();
I_Void slotIdReqHandler();
I_Void peerSwitchConnectHandler();

I_S32 cfgRmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
#endif
