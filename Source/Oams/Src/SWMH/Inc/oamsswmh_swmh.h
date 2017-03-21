/** ts=3 ********************************************************File Header ** 
 FILE NAME         :  oamsswmh_swmh.h
 PURPOSE           :  Contains SWMH Data struct

 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/
#ifndef __OAMSSWMH_SWMH_H
#define __OAMSSWMH_SWMH_H

#include <sysxxx_typedef.h>
#include <bpmxxx_commonDef.h>
#include <ipcfrm_msgdef.h>

I_Void cardStateChangeHandler(struct sAisParam *);
I_Void activeInProgressStateHandler();
I_Void findLocalPidForEachBic(I_U32 *lclPidPtr, I_S32 *instId, I_U32 bicId);
I_Void activeStateHandler();
I_Void activeStateTransitionHandler();
I_Void findLclPidPtr ( I_U32 refId, I_U8 classId, I_U32 *lclPidPtr, I_U8 entId );
I_U32 getCountAllocatedInst ( I_U32 instCount, I_U8 classId );
I_Void sendLoadDataAbort ( I_U32 nodeType, I_U32 nodeId, I_U32 tei );
I_Void processTimerMsg ( I_PVoid rcvPtr );

#endif   /* __OAMSSWMH_SWMH_H  */

