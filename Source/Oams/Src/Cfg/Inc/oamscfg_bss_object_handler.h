/***********************************File Header ***************************
  File Name        : oamscfg_bss_object_handler.h
Purpose          : This file contains functions definitions for CFG
BSS Object Handler  methods.
Project          :  BSC OAM
Subsystem        : Oams
Author           :  Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMCFG_BSS_OBJECT_HANDLER_H_
#define __OAMCFG_BSS_OBJECT_HANDLER_H_

#include<oamscfg_includes.h>
#define isBssLocked() (gBssState == locked)

typedef enum  {
  ACTIVE_ICC_CARD_RESET_CMD  = 0x01,
  STANDBY_ICC_CARD_RESET_CMD = 0x02,
  ACTIVE_ICC_CARD_SHUTDOWN_CMD  = 0x03,
  STANDBY_ICC_CARD_SHUTDOWN_CMD = 0x04,
  NO_RESET_CMD               = 0xFF,
} eBssResetCommand;

typedef enum adminProcedure
{
   LockProcedure,
   UnlockProcedure
}AdminProcedure;


typedef enum interfaceType
{
   AInterfaceType,
   GbInterfaceType
}InterfaceType;

extern BssTableApi gDbBssTableApiStorage;
extern I_Bool gFirstBSSTableStorageUpdation;
extern I_Bool gPsUnlockCellsProgressFlgForBSS;

I_Void bssResetReqHandler(eBssResetCommand BssResetCommand);
void initiateCellUnlockEnableforUnlcokedDisabledCells();
void bssObjectHandler();
void bssObjectLockedHandler();
void bssObjectLockInProgressHandler();
void bssObjectUnockHandler();
void bssObjectUnLockInProgressHandler();
void bssObjectBssSetTableHandler();
void initiateCellLockDisableforUnlckedCells();
void initiateCellUnLockEnableforUnlckedDisabledCells();
void informCellUnLockDisableforUnlckedCellsToBss();
void informCellUnLockEnableforUnlockDisabledCellsToBss();
void sendCellBarAccessToCells(AdminProcedure  adminProc,I_U8 reasonToBeSent );
void getDbBssTable();
void bssObjectHandlerForSSProhibit();
void initiatePsUnlockCellsForBSS();
void  bssObjectPerformOperationOnBssTable(BssTableApi* bssTableApiRcvdPtr, BssTableApi* bssTableApiDbPtr);
void initiateCellLockDisableforUnlockedCells();
void bssObjectPerformUpdateOperation(BssTableApi* bssTableApiRcvdPtr);
void bssObjectPerformUnlockOperation(BssTableApi* bssTableApiRcvdPtr);
void bssObjectPerformLockOperation(BssTableApi* bssTableApiRcvdPtr);
void bssObjectHandlerForSSAllowed();
void bssObjectSendLinkAdminStateTableToScm(I_U32 admStateToChk, I_U32 admStateToSend );
void setAinterfaceTableOperationalState(I_U32 opStateToSet);
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
void initiateSwitchoverProcForCloudBscStack();
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
/*SPR - Start *****/
void StartUpTimerTimeoutHandler();
/*SPR - End *****/
/*Mantis # Start..*/
void timerTimeoutForBpmCardInfo();
/* Mantis # End ..*/
I_Bool isCgiUnqInBss(I_U16 mcc, I_U16 mnc);
I_Bool checkAndSendLinkDeactivationRequest();

/* Changes for R2.3.4 Starts */
I_Bool fillMtp2TimerInfo(I_Void * mtp2TimerConfigPtr, I_U32 satFlag);
/*Changes for R2.3.4 Ends*/



/*Changes PCU R2.5 Aricent -- START*/
I_Void informNsvcUnlockDisableForUnlockedNsvcsToBss();
I_Void informNsvcUnlockEnableForUnlockDisabledNsvcsToBss();
/*Changes PCU R2.5 Aricent -- END*/

/********************************* Change History ***************************
  Release     Patch       Author         Description
  CS2                     Pratibha       Enum Removal Change

 ************************************** End *********************************/

#endif /*__OAMCFG_BSS_OBJECT_HANDLER_H_ */
