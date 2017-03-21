/***********************************File Header ***************************
 *   File Name        : oamscfg_sw_upgrade_handler.h
 *   Purpose          : This file contains functions definitions for Software
 *   Upgrade Handler  methods.
 *   Project          : BSC OAM
 *   Subsystem        : Oams
 *   Author           : Aricent 
 *   CSCI ID          :
 *   Version          :
 *    ************************************* End **********************************/

#ifndef __OAMSCFG_SW_UPGRADE_HANDLER_H_
#define __OAMSCFG_SW_UPGRADE_HANDLER_H_


/*swAction */
#define SW_NO_ACTION   0
#define SW_DOWNLOAD    1
#define SW_ACTIVATE    2

/*swStatus */
#define SW_NO_LAST_ACTION           0
#define SW_DOWNLOAD_IN_PROGRESS     1
#define SW_DOWNLOAD_SUCCESS         2
#define SW_DOWNLOAD_FAILED          3
#define SW_ACTIVATION_IN_PROGRESS   4
#define SW_ACTIVATION_SUCCESS       5
#define SW_ACTIVATION_FAILED        6

  /*     Mantis - 28585:
         E1_INVALID value changed 
         from zero to 0xFFFFFFFF 
         as zero is a valid value
   */ 
#define E1_INVALID                  0xFFFFFFFF
  /*     Mantis - 28585  ends*/ 
#define TS_INVALID                  0xFF
#define TRX_LOCATION_IN_FRAME       1

#define MAX_SW_UPGRADE_OFFER_IN_PARALLEL 1
#define MAX_IP_SW_UPGRADE_OFFER_IN_PARALLEL 0x0A 
#define CONNECTED   1 
#define MAX_STRING_LENGTH   100


I_Void setSwMOfferTable();
I_Void setSwMNodeTable();
I_Void setSwMTable();
I_Void setBicTable();
I_Void setTrxTable();
I_Void performBscSwActivationOperation(SwMNodeTableApi *);
I_Void performBicAndTrxSwDownloadOperation(SwMNodeTableApi *);
I_Void performBicAndTrxSwActivationOperation(SwMNodeTableApi *);
I_Void sendSwUpgradeOfferRequest(SwMOfferTableApi *);
I_Void sendSwDeletionRequest(I_U8,I_U8,I_U32, I_S8 *);
I_Void sendSwDownloadRequest(SwMNodeTableApi *,I_U8 *);
I_Void sendSwActivationRequest(SwMNodeTableApi *);
I_Void swOfferRespHandler();
I_Void swActivationRespHandler();
I_Void swDeletionRespHandler();
I_Void swDownloadSuccessHandler();
I_Void swDownloadFailureHandler();
I_Void swActivationSuccessHandler();
I_Void swActivationFailureHandler();
I_Void sendRequestForAvailableReleases();
I_Void availableReleasesRespHandler();
I_Bool checkMaxDownloadAllowed(I_U32,I_U8);
I_Void goToReadyState();
I_Void getStringForSwOfferErrorCause(I_U16,I_U8 *,I_U32,I_U8 *,I_U8,I_U8);
I_Void getStringForSwActErrorCause(I_U32,I_U16,I_U8 *,I_U8,I_U8,I_U8 *);
I_Void getStringForSwDelErrorCause(I_U16,I_U8 *,I_U32,I_U8 *,I_U8,I_U8);
I_Void getStringForSwmhErrorCause(I_U32,I_S8 *,I_U8 *,I_U32,I_U32,I_U8 *);
I_Void cfgInitSwMNodeTable();
I_S32 cfgInsertSwMNodeTableForBic(I_U32,I_U32,I_U32,I_U32);
I_S32 cfgInsertSwMNodeTableForIpBts(I_U32,I_U32);
I_S32 cfgInsertSwMNodeTableForTrx(I_U32,I_U32);
I_Bool delNonExistingAvailRelFromCP(OamOilCfgAvailableReleasesResp *);
I_Bool copyReleaseFromPPToCP(I_U8 *,I_S8 *,I_U32,I_U8 *);
I_Bool deleteReleaseFromCP(OamOilCfgSwDelResp *,I_U8,I_U8);
I_Bool checkUpgradeOfferFailure(OamOilCfgSwDelResp *,I_U8,I_U8,I_U8 *);
/* Added for CS4.0: SwM */
I_Void eicAvailableReleasesRespHandler();
I_Void eicSwOfferRespHandler();
I_Void eicSwActivationRespHandler();
I_Void eicSwDeletionRespHandler();
I_Void performEicSwActivationOperation(SwMNodeTableApi *receiveMsgPtr);
I_Void sendUpgradeAlarm();
I_Void sendRequestForEicAvailableReleases();
I_Void cfgInitEicSwMNodeTable();
I_Void deleteRowsFromEicCardInfo();
I_Void deleteRowsFromSwmNodeTable();
I_S32 make_parent_dir(const I_S8 *);
I_Void sendQuerySetCardOperState(I_U32 cardState,I_U8 slotId);
I_Void sendBscActivationRequest();
I_Void makeCopyOfActReq(SwMNodeTableApi *receiveMsgPtr);
I_Void makeCopyOfActAlarm(OamsCfgAfhSysAlarm *sysAlarmBuff);
I_Void sendActivationAlarm( OamOilCfgAvailableReleasesResp *availableReleasesRespPtr);
I_Void updateEicDataOnEicConnect();
I_Void updateEicDataOnEicEnableDisable();
I_Void sendRequestForSpecificSlotAvailableReleases(NodeType, I_U8, I_U8);
I_Void cfgInsertIccDetails(sCardObjInfo cardObjInfo);

/*BSC R2.0 Changes Starts*/
I_Void sendRequestForDspAvailableReleases();
I_S32 sendRequestForBscAvailableReleases(I_U8 frameId, I_U8 slotId);
I_Void cfgInitSwMNodeTableDelBicTrx();
I_Void sendLoadAbortIndToSWMH(I_U32 nodeType,I_U32 nodeId);
I_Void sendCvActivationRequest(SwMNodeTableApi *receiveMsgPtr);
/*BSC R2.0 Changes Ends*/

/* Added for SW_IP_BTS in R2.8-EXT_ALARM_NEW*/
I_Void performR2BtsIPSwDownloadOperation(SwMNodeTableApi *);
I_Void performR2BtsIPSwActivationOperation(SwMNodeTableApi *);
I_Void sendIpBtsSwDownloadRequest(SwMNodeTableApi *);
I_Void sendSwActivationRequest(SwMNodeTableApi *);

/********************************* Change History ***************************
 *   Release     Patch       Author         Description
 *
 *      ************************************** End *********************************/

#endif /*__OAMSCFG_SW_UPGRADE_HANDLER_H_ */

