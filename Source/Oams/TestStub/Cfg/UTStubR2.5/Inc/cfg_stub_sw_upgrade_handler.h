#ifndef _CFG_STUB_SW_UPGRADE_HANDLER_H_
#define _CFG_STUB_SW_UPGRADE_HANDLER_H_

#define CFG_RESET    0xffff
#define ENT_OAMS_CFGSTUB 0x8888 /* some number */
I_S32 cfgStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_U16 msgType, I_U8 subType);
I_Void sendClockSourceResp(OamsCfgOilSetClkSrcReq *oamsCfgOilSetClkSrcReq);
I_Void sendTrunkStateChangeResp(OamsCfgOilE1EnableReq *oamsCfgOilE1EnableReq);
I_Void sendBpmDbInit();

#endif
