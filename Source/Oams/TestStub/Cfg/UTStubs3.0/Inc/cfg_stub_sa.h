#ifndef _CFG_STUB_SA_HANDLER_H_
#define _CFG_STUB_SA_HANDLER_H_	1

void trxhReqHandler();
void bichReqHandler();
void grhmReqHandler();
void addBicReqHandler();
void deleteBicReqHandler();
void addTrxReqHandler();
void deleteTrxReqHandler();
void switchConnectHandler();
void lockTrxReqHandler();
void unlockTrxReqHandler();

I_S32 cfgBichStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
#endif
