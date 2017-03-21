/***********************************File Header ***************************
       File Name        : oamscfg_cell_object_handler.h
       Purpose          : This file contains functions prototypes for CFG
                          Cell Handler  
       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/

#ifndef _OAMCFG_CELL_OBJECT_HANDLER_H_
#define _OAMCFG_CELL_OBJECT_HANDLER_H_
void cellUnlockReq(I_U32 cellId,I_U32 lac,I_U32 reason);
void cellObjectHandler();
void cellObjectLockedHandler();
void cellObjectUnlockOrEnableInProgressHandler();
void sendcellAlarm(I_U32 AlarmId);
void startTimer(I_U32 cellId,I_U32 lac);
I_Void sendPsscmLockReq(I_U32 reason);
void sendGrhmStopChanAllocReq(I_U32 cellId,I_U32 lac);
I_Void sendPsscmUnlockReq(I_U32 reason);
/*Changes PCU R2.5 Aricent -- START*/
I_Void sendPsCellShutdownInd(I_U32 cellId, I_U32 lac, I_U8 cellIndex);
I_Void sendCellBlockReq(I_U32 cellId, I_U32 lac, I_U8 cellIndex);
I_Void sendCellUnlockReq(I_U32 cellId,I_U32 lac,I_U32 reason,I_U8 cellIndex);
I_Void sendCellLockReq(I_U32 cellId,I_U32 lac,I_U32 reason,I_U8 cellIndex);
I_Void sendPsCellLockReq(I_U32 cellId, I_U32 lac, I_U32 reason, I_U8 cellIndex);
I_Void sendPsCellUnlockReq(I_U32 cellId, I_U32 lac, I_U32 reason, I_U8 cellIndex);
I_Void updatePsCellDataState(I_U32 cellId,I_U32 lac,I_Bool state);
/*Changes PCU R2.5 Aricent -- END*/
void cellObjectUnlockedEnabledHandler();
void cellObjectUnlockedDisabledHandler();
void cellObjectLockOrDisableInProgressHandler();
void cellObjectBlockInProgressHandler();
I_U8 getCellDataState();
I_U8 getCellDataStruct(I_U32 cellId,I_U32 lac);
void updateCellDataStruct(I_U32 cellId,I_U32 lac,I_S32 state,I_Bool reqType);
void sendGrhmStartChanAllocReq(I_U32 cellId,I_U32 lac);
I_Void initCellDataStruct(I_U32 cellId, I_U32 lac,I_U16 *cellArrayIndex);//MANTIS 16723 FIX
I_Void resetCellDataStruct(I_U32 cellId, I_U32 lac);
/*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts**/
I_Void e1UnlockRespHandler();
I_Void e1LockRespHandler();
/*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/
/*Changes R2.5.2: Start*/
I_U8 isOnlyFrToHrPerctModified(CellPerTableApi *cellTable,CellPerTableApi *cellTablePtr);
void sendCellInfoUpdInd(I_U8 cellIndex);
/*Changes R2.5.2: End*/
/*Merger for Mantis #31470*/
I_Void sendPschNseLockReq(I_U16 nsei);
I_Void sendPschNseUnlockReq(I_U16 nsei);
/*Merger for Mantis #31470*/
#define CELLHM_HANDLER        1
#endif /*_OAMCFG_CELL_OBJECT_HANDLER_H_ */ 



