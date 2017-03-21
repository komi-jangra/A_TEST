/***********************************File Header ***************************
       File Name        : oamscfg_alarm_handler.h
       Purpose          : This file contains function prototype for CFG
                          TRX object Handler  methods.
       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/
#ifndef OAMCFG_TRX_OBJHANDLER_H
#define OAMCFG_TRX_OBJHANDLER_H

objectState getPtrxObjectState();
void trxObjectHandler();
void ptrxObjectLockedHandler();
void ptrxObjectLockInProgressHandler();
void ptrxObjectUnlockHandler();
void ptrxObjectUnlockInProgressHandler();
void ptrxObjectPtrxSetTableHandler();
void sendPtrxLockReq();
void sendPtrxUnlockReq();
void oamsTrxhCfgUnlockResp();
void oamsTrxhCfhLockResp();
objectState getPtrxState();

/* Change For CS2.2 : Start */
I_Void addTrxTableHandler();
I_Void updateTrxTableHandler(TrxTableApi* trxTableApiPtr);
I_Void prepAndSndSwitchConForTrx(I_U32 ptrxId);
I_Void addConfiguredTrxs();
I_S32 sendAddTrxReq(I_U32 ptrxId, I_U8 trxType, I_U32 bicId);
I_Void sendDelTrxReq(I_U32 ptrxId);
I_Void prepAndSndSwitchDisConForTrx(I_U32 ptrxId);
I_Void setPtrxInitState(I_U32 ptrxId);
I_Bool isTrxPosAlreadyConfigured(I_U8 trxType, I_U8 trxPos, I_U32 bicId);
I_Void sendPtrxResetReq();
/* Change For CS2.2 : End */
/* Changes For R2.2 : Start */
void trxResetHandler();
void sendIndicationToBic(TrxTableApi* trxTableApiPtr);
void sendPtrxResetReq();
/* Changes For R2.2 : End */

I_Void sendBlockReqForTrx(I_U32 ptrxId);
void ptrxObjectBlockInProgressHandler();

/*Changes PCU R2.5 Aricent --START */ 
I_Void addRowInPsPerformanceCounterTableForTrx(I_U32 ptrxId);
I_Void deleteRowFromPsPerformanceCounterTableForTrx(I_U32 ptrxId);
/*Changes PCU R2.5 Aricent --END */ 

I_Void sndSwitchConForTrxsAtSwitchOver();

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change
   CS2.2		   Kapil Tyagi    New Functions declaration added 
************************************** End *********************************/

#endif /*OAMCFG_TRX_OBJHANDLER_H */
