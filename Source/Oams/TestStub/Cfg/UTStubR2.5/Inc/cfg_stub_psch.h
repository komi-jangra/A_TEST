#ifndef _CFG_STUB_PSCH_HANDLER_H_
#define _CFG_STUB_PSCH_HANDLER_H_	1

void pschReqHandler();
void pschUnlockReqHandler();
void pschLockReqHandler();
void cfgStubSendPschCfgUnlockResp(I_U32 cellId, I_U32 lac);
void cfgStubSendPschCfgLockResp(I_U32 cellId, I_U32 lac);
I_S32 cfgPschStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
#endif
