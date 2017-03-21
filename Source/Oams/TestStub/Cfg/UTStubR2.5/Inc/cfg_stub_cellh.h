#ifndef _CFG_STUB_CELLH_HANDLER_H_
#define _CFG_STUB_CELLH_HANDLER_H_	1

I_Void e1UnlockReqHandler();
I_Void e1LockReqHandler();
I_Void cellhReqHandler();
I_Void unlockReqHandler();
I_Void lockReqHandler();

I_S32 cfgCellhStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
#endif
