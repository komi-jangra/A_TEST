#ifndef __IPCFRM_FUNCS_H__
#define __IPCFRM_FUNCS_H__

typedef void I_Void;

void SendBuffer(I_Void *, int, char *, char *);
void RecvBuffer(int, I_Void *, char *, char *);
void RegisterEntity(int, char *);
void DeallocateBuffer(I_Void *, char *, char *);

#endif
