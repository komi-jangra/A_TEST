/***********************************File Header ***************************
       File Name        : oamscfg_e1_object_handler.h
       Purpose          : This file contains functions definitions for CFG
                          Alarm handler  methods.
       Project          :  BSC OAM
       Subsystem        : Oams
       Author           :  Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/
#ifndef __OAMSCFG_E1_OBJECT_HANDLER_H
#define __OAMSCFG_E1_OBJECT_HANDLER_H

#define Ainterface 0 /*Using Entity of E1*/
#define Abis 1       /*Using Entity of E1*/

#define GET_FRINDEX_FROM_TIMESLOTTABLE(t) ((t->usingEntity & 0xff00)>>2)

#define FREnabled 1
#define NSVCEnabled 2
#define NSVCDisabled 3
#define FRDisabled  4
#define INVALID_TRUNK_ID 0xFFFF


#define MAX_TIMESLOT 32

/*BB, Start , CS4.0 */
#define isE1NumOfTypeAIF(E1Num) ( (gE1Data[(E1Num)].usageType) == SYS_E1_USAGE_AIF )
#define isTrunkPortEnable(E1Num) ( (gE1Data[(E1Num)].trunkState) == Enabled )
#define isLOSactive(E1Num) (  gE1Data[(E1Num)].LOS_Active || \
                              gE1Data[(E1Num)].LOS_Active_In_Progress \
                           )
/*BB, End , CS4.0 */

/*BSC R2.3 Changes starts*/
#define isTrunkPortFirstOrSecondOfFramer(E1Num) (  (E1Num == 0) || (E1Num == 1) ||\
                                      (E1Num == 8) || (E1Num == 9) ||\
                                      (E1Num == 16) || (E1Num == 17) ||\
                                      (E1Num == 24) || (E1Num == 25) ||\
                                      (E1Num == 32) || (E1Num == 33)  )
/*BSC R2.3 Changes ends*/

objectState getE1ObjectState(I_U32 e1Num);
objectState getState();
void e1ObjectHandler();
void setTable();
void unlockInProgressHandler();
void lockInProgressHandler();
void setE1Table();
void sendE1MessageToSCM(I_U16 reqType);
void sendE1MessageToGRHM(I_U16 reqType);
void sendE1MessageToPSSCM(I_U16 reqType);
void cfgScmUnlockLinkAdmStTblResp();
void  cfgScmLockLinkAdmStTblResp();
void csappGrhmCfgUnlockRespE1();
void csappGrhmCfgLockRespE1();
void  trxhCfgUnlockRespE1();
void  trxhCfgLockRespE1();
void cfgAlarmHandler();
void csappGrhmCfgAlarmIndE1();
void scmCfgAlarmIndE1();
I_S8  isMtp2ForLock(I_U32);
I_S8  isCicForLock(I_U32);
I_S8  isMtp2ForUnlock(I_U32);
I_S8  isCicForUnlock(I_U32);
I_Bool  isFrTimeslot(I_U32);

I_U32  updateE1TableAST(E1TableIndices *e1TableIndices ,I_U32 ast);
I_U32 updateTimeSlotTableAST(AbisTimeSlotPerTableIndices  *timeSlotTableIndices  ,I_U32 ast);
void  e1ObjectUpdateAdminStateAndSendAlarm(I_U32 admState);
I_Void updateTrunkTableHandler();

/*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/
void abisE1LockUnlock(TrunkTableApi *e1ObjPtr);
I_Bool isE1RequestValid(I_U32 e1Num);
void updateAbisE1StateInDBAndSendAlarm(I_U32 e1Num, I_U32 adminState);
I_Void e1UnlockForBssUnlocked(I_U32 e1Num);
I_Void e1UnlockForBssUnlockInProgress(I_U32 e1Num);
I_Void sendAbisE1UnlockReq(I_U32 e1Num, I_UL32 cellId, I_U32 lac, I_U16 cellIndex);
I_Void e1LockForBssUnlocked(I_U32 e1Num);
I_Void e1LockForBssUnlockInProgress(I_U32 e1Num);
I_Void sendAbisE1LockReq(I_U32 e1Num, I_UL32 cellId, I_U32 lac, I_U16 cellIndex);
I_Void abisE1LockUnlockAfterCellUnlock(I_U32 cellId, I_U32 lacId);
I_Void abisE1LockAfterCellUnlock(I_U32 e1Num, I_U32 cellId, I_U32 lac);
I_Void abisE1UnlockAfterCellUnlock(I_U32 e1Num, I_U32 cellId, I_U32 lac);

/*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/

// CS 4.0 Harsh
I_U32 gE1NumberMapToTrunk;
I_U32 gTrunkAdminStateinDB;
I_U8  g_card_in_standby_mode;
I_U8  g_card_in_recovery_mode;
TrunkPortTableApi g_TrunkPortDb;
I_U16             g_trunkid;
I_U32             g_e1num;
// CS 4.0 Harsh

void EnableInProgressHandler();
void SendAlarm( I_U32 alarmId, I_U32 alarmlevel, I_U8 info, I_U32 e1num );
void setTrunkPortTable();
void DisableInProgressHandler();
void E1TrunkMap( TrunkTableApi *receivedMsgPtr, TrunkTableApi *e1TableApiPtr ); 
void EnableInProgressHandler( I_U32 *e1num );
void DisableInProgressHandler( I_U32 *e1num );
void setTrunkPortTableHandler();
void TrunkPortObjectHandler();
TrunkPortObject getTrunkState( I_U32 *e1num );
TrunkPortObject  getTrunkObjectState(I_U32 e1Num);
void PlatformAlarmHandler( I_U32 AlarmId, I_U32 *e1num );
I_U8 FindState( I_U32 adminstate, I_U32 e1num );
I_U8 IsE1ForCIC( I_U32 e1Num );
I_U8 IsMultipleMTP2LinkActive( I_U32 e1Num); 
I_U8 GetE1numByTrunkId( I_U16 trunkid, I_U32 *e1num );
// CS 4.0 Harsh

//Alarm Changes
I_U8 ChkActiveCardAlarm( I_U32 frameId, I_U32 slotId );

/* CS4.0 Trunk UsageType Changes : Starts */

I_S32 updateUsageTypeAbisToFree(I_U32 usageType);
I_S32 updateUsageTypeFreeToAbis();
I_S32 performValidityCheck(TrunkPortTableApi* TrunkPortTableApiPtr);
I_U32 populateAbisTimeSlotTable();
I_U32 delAbisTimeSlotTable(I_U32 usageTypeInDB);
I_U32 updateFreeLAPDEntriesAsBusy(MccLinkResourceTableApi *mccLinkTablePtrSelf,MccLinkResourceTableApi
      *mccLinkTablePtrMate,I_U16 sizeSelf,I_U16 sizeMate, I_U32 reqEntries);
I_S32 updateUsageTypeFreeToAif();
I_S32 updateUsageTypeAifToFree();
I_U32 validityCheckFreeToAbis(MccLinkResourceTableApi **mccLinkTablePtrSelf, MccLinkResourceTableApi
      **mccLinkTablePtrMate,I_U16 *sizeSelf, I_U16 *sizeMate,I_U32 * reqEntries);
I_U32 validityCheckAbisToFree();
I_S32 E1UsageTypeChangeHandler(TrunkPortTableApi* TrunkPortTableApiPtr);
I_S32 validityChecksAifToFree();
I_U32 validityCheckAbisToAbis(I_U32 DbUsageType, I_U32 RcvdUsageType);

/*Changes PCU R2.5 Aricent -- START*/
I_Void informNsvcUnlockDisableForUnlockedNsvcsToE1();
I_Void informNsvcUnlockEnableForUnlockDisabledNsvcsToE1();
/*Changes PCU R2.5 Aricent -- END*/
typedef struct
{
   sCmMsg         msg;
   TrunkTableApi  e1tbl;
}E1Tbl;

E1Tbl g_e1tbl ;

void prepareE1Tblptr( I_U32 adminState );

/* CS4.0 Trunk UsageType Changes : Ends */
I_S32 checkAndSendLinkActivationRequestForE1(I_U16 reqType); /* HA Stack Changes */

/*BSC R2.0 Changes Starts*/
void SendTrunkPortEnableAlarm( I_U8 frameId, I_U8 slotId, I_U16 portId );
void SendTrunkPortDisableAlarm( I_U8 frameId, I_U8 slotId, I_U16 portId );
/*BSC R2.0 Changes Ends*/

I_Void SendClearAlarms(I_U32 e1Num );

/********************************* Change History ***************************
   Release     Patch       Author         Description

************************************** End *********************************/

#endif /*__OAMSCFG_E1_OBJECT_HANDLER_H */

