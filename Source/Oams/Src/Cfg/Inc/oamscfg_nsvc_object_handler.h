/***********************************File Header ***************************
File Name        : oamscfg_nsvc_object_handler.h
Purpose          : This file contains CFG Nsvc Handler declarations
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef _OAMSCFG_NSVC_OBJECT_HANDLER_H_
#define _OAMSCFG_NSVC_OBJECT_HANDLER_H_


I_Void nsvcObjectHandler();
I_Void nsvcObjectLockedHandler();
I_Void nsvcObjectUnlockOrEnableInProgressHandler();
I_Void nsvcObjectUnlockedEnabledHandler();
I_Void nsvcObjectUnlockedDisabledHandler();
I_Void nsvcObjectLockOrDisableInProgressHandler();
I_Void updateNsvcDataStruct(I_U32 nsvcId, I_S32 state,I_Bool reqType);
I_Void initiateNsvcLockDisableForUnlockedNsvcs();
I_Void initiateNsvcUnlockEnableForUnlockedDisabledNsvcs();

/*Mantis 13733 Start*/
I_Bool initiateNsvcLockDisableForUnlockedNsvcsForE1();
I_Bool initiateNsvcUnlockEnableForUnlockedDisabledNsvcsForE1();
/*Mantis 13733 End*/

I_Void informNsvcUnlockDisableForUnlockedNsvcsToBss();
I_Void informNsvcUnlockEnableForUnlockDisabledNsvcsToBss();
I_Void populateFrLinkExtE1TsMccE1TsMapTable(I_U16 frChnId);

I_U8 getNsvcDataState();
I_U8 getNsvcDataStruct(I_U32 NsvcId);

I_Void resetNsvcDataStruct(I_U16 nsvcId);
I_Void initNsvcDataStruct(I_U16 nsvcId);
I_Void nsvcUnlockReq(I_U16 nsvcId, I_U8 reason);
I_Void nsvcLockReq(I_U16 nsvcId, I_U8 reason);
I_Void sendSwitchConnect2Grhm(I_U32 frE1Id, I_U32 frE1Ts, I_U32 mccE1Id, I_U32 mccE1Ts);
I_Void sendSwitchDisconnect2Grhm(I_U32 frE1Id, I_U32 frE1Ts, I_U32 mccE1Id, I_U32 mccE1Ts);
I_U32 getEnableInProgressNsvcsCount();
I_U32 getDisableInProgressNsvcsCount();

#endif

