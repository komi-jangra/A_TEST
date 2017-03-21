#ifndef _CFG_STUB_PSSCM_HANDLER_H_
#define _CFG_STUB_PSSCM_HANDLER_H_	1

void psscmReqHandler();
void nsvchUnlockReqHandler();
void nsvchLockReqHandler();
void cfgStubSendNsvchCfgUnlockResp(I_U32 nsvcId);
void cfgStubSendNsvchCfgLockResp(I_U32 nsvcId);
I_S32 cfgPsscmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
#endif
