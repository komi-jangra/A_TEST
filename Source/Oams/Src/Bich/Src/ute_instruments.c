#include <sysxxx_typedef.h>
#include <sysxxx_proc.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_msgstruct.h>


I_S32 SendMsg(I_Void *snd_ptr, I_SL32 priority, I_S32 _length);

I_S32 UteSendMsg(I_Void *snd_ptr, I_SL32 priority, I_S32 _length) 
{
  ((SysHdr*)snd_ptr)->dest.entity = ENT_IPC_TEST1;
  return SendMsg(snd_ptr,priority,_length);
}

