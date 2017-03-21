#ifndef _CFG_STUB_BPM_H_
#define _CFG_STUB_BPM_H_	1

#define BPM_STUB_CFG_NOTIFICATION 10000
I_S32 cfgBpmStubSendMessage(void *bufPtr, I_U32 size, I_S32 SrcEntId,I_S32 DestEntId,I_U16 msgType, I_U8 subType);
typedef struct
{
   SysHdr sHdr;
   sAisParam param; 
}BpmStubCfgNotification;
#endif
