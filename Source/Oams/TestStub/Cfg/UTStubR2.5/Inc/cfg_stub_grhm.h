#ifndef _CFG_STUB_GRHM_HANDLER_H_
#define _CFG_STUB_GRHM_HANDLER_H_	1

void grhmReqHandler();
I_S32 cfgGrhmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
#endif
