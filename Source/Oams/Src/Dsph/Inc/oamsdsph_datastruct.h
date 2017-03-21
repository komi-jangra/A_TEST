/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamsdsph_datastruct.h
 PURPOSE           :  Contains DSPHandler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  R2.0-BSC Team
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSDSPH_DATASTRUCT_H
#define __OAMSDSPH_DATASTRUCT_H

typedef struct
{
  I_U8 dspId;
  I_U8 trauResource_core0;
  I_U8 abisTsResource_core0;
  I_U8 trauResource_core1;
  I_U8 abisTsResource_core1;
  I_U8 trauResource_core2;
  I_U8 abisTsResource_core2;
  I_U8 trauResource_core3;
  I_U8 abisTsResource_core3;
  I_U8 activeChannels;
  I_U8 swVerInfo[3];
  I_U8 swIdInfo[3];
  I_U8 reasonInLockReq;
  I_U8 reasonInUnlockReq;
  I_U8 dspNonAvailabilityCause;
  I_U8 frameId;
  I_U8 slotId;
  I_U32 coreIp[MAX_NUM_CORES_PER_DSP];                             /*Added for RTP specific*/
}OamsDsphContext;


typedef struct
{
  I_U8  dspId;
  I_U8  coreId;
  I_U8  trauIndex;
  I_U8  ptrxId;
  I_U8  retrans;
  I_U8  ts;
  I_U8  subTs;
  I_U8  msgId;
  I_U16 msgType;
}TrauConfigDeConfigStruct;

typedef struct
{
  I_U8   ts;
  I_U8   subTs;
  I_U8   subSubTs;
  I_U32  retrans;
  I_U8   confTimer;
}DspConfStruct; 

typedef DspConfStruct DspConfTimerStruct[MAX_CORE][MAX_DSP_TRAU_INDEX];

typedef struct
{
  I_U32   retrans;
  I_U8    deconfTimer;
  I_U32   confRespPending;
}DspDeconfStruct;

typedef DspDeconfStruct DspDeconfTimerStruct[MAX_CORE][MAX_DSP_TRAU_INDEX];

#endif   /*__OAMSDSPH_DATASTRUCT_H */
