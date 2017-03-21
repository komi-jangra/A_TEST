/***********************************File Header ***************************
  File Name        : oamscfg_msg_handler.h
Purpose          : This file contains functions definitions for CFG

Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef  __OAMCFG_MSG_HANDLER_H_
#define  __OAMCFG_MSG_HANDLER_H_


void cmMsgHandler();

void oilMsgHandler();         

void grhmMsgHandler();         

void trxhMsgHandler();         

void cellhMsgHandler();         

void scmMsgHandler();

void psscmMsgHandler();

void mgsMsgHandler();

void timerMsgHandler();

void swmhMsgHandler();

void cbsifMsgHandler();

void ccuMsgHandler();

void dsphMsgHandler();

/*Changes PCU R2.5 Aricent -- START*/
void gbhMsgHandler();

void nsvchMsgHandler();
void pschMsgHandler();
void setBssPsTableHandler();
void frMsgHandler();
/*Changes PCU R2.5 Aricent -- STOP*/

void dispachToObjectHandler(I_U8  ObjectType);

I_S32 cfgSendMessage(void *bufPtr, I_U32 size, I_S32 entId,I_U16 msgType, I_U8 subType);
I_S32 cfgSendCmMessage(void *bufPtr, I_U32 size, I_S32 entId,I_U16 msgType, I_U8 subType);

void initiateBssUnlock();
void cfgDspInitWtRspHandler( DSmmMgsBootMsg* DspMgsuBootPtr);
void cfgDspBootHandler();
void cfgTsiDriverInitRespHandler(DSmmMgsuDriverInitStatus *DSmmMgsuDriverInitStatusPtr);

#if 0 /* CS4.0 HA Stack Changes */
I_Bool getTimeSlotTableFromLinkCodeAndLinkset(LinkAdminStateTableApi *linkAdminStateTableApiPtr,
										AbisTimeSlotPerTableApi *currentTimeSlotTableApiPtr);                    
void sendLinkAdminStateTableReqToScm(LinkAdminStateTableApi *LinkAdminStateTableApiPtr);
#endif 

//void cfgTrauInitWtRspHandler( DTrauMgsuDriverInitStatus* DTrauMgsuDriverInitStatusPtr);
/* Changes For CS2.2 : Start */
I_Void bichMsgHandler();
/* Changes For CS2.2 : End */
void mrhmMsgHandler();
typedef enum trauStatus
{
   TRAU_STAUS_UP,
   TRAU_STAUS_DOWN
}trauStatus;

void sendTrauUlStatusUpdateReq(I_U16 trauChannelId,I_U32 action);
void updateTrauUlFrameStatus();

/*******BSC CS4.0: Init Changes Starts***********/
//I_Void updateSystemTypeDetails();
//I_Void updateChasisFrameDetails();
I_Void updateSystemClockDetails();
//I_Void updateDspObjDetails();
I_Void updateTrunkPortDetails();
//I_Void updateEicCardDetails();
//I_Void updateIccCardDetails();
I_Bool sendTrunkStateChangeReq();
I_Bool checkTrunkStateChangeResp();
I_Void sendCardInfoReq(I_U32 cardType);
I_Void sendTrunkStateChangeFailAlarm(I_U8 frameId, I_U8 slotId, I_U16 trunkPortId);
I_Void deleteIccCardDetails();
I_Void deleteEicCardDetails();
I_Void updateCardDetails();

I_Void sendPresentCardInfoReq();
I_Void makeCopyOfAlarm();
I_Void updatePresentCardDetails();
I_Void updateTrunkPorts();
I_Void insertEicDetails();
I_Void insertIccMateCardDetails();
I_Void insertIccSelfCardDetails();
I_Void insertIccCardDetails(sCardObjInfo cardObjInfo);
I_Void insertEicCardDetails(sEicObjInfo cardObjInfo);

/*******BSC CS4.0: Init Changes Ends***********/
/*******BSC CS4.0: Stack  Changes Starts***********/
I_Void sendSwitchConForMccLinkResource();
/*******BSC CS4.0: Stack  Changes Ends***********/
/*BSC CS4.0 HA Changes Starts*/
I_Void sendTrauStartMsg();
I_Void rmMsgHandler();
I_Void stateChangeNotificationHandler();
I_Void copySystemDetails();
 /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
I_Void copySystemDetails1U();
I_Void updateSystemDetails1U();
  I_Void printSystemDetails1U(sCloudCardInfo *sysDetailPtr1U);
I_Void send1UCardInfoReqToOil();
I_Void UpdateOrInsertObmCardInfoTableApi(sObmCardInfo var);
I_Void UpdateOrInsertPowerSupplyTable(sPowerSupplyInfo var);
I_Void UpdateOrInsertFanFilterIdTableApi(sFanFilterInfo var);
I_Void UpdateOrInsertChasisFrameTableApi();
I_Void updateFanStatusInObmCardInfoTableApi(SysAlarm* recAlarmPtr,I_U8 value);
I_Void updatePhysicalPresenceStateInObmCardInfoTableApi(SysAlarm *recAlarmPtr);
I_Void deleteEntryFromObmCardInfoTableApi(SysAlarm *recAlarmPtr);
I_Void updatePhysicalPresenceStateOrDelEntryInPowerSupplyTableApi(SysAlarm *recAlarmPtr,I_U8 value);
I_Void UpdateFanFilterIdTableApi(SysAlarm *recAlarmPtr);
 /*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
I_Void UpdatePowerStatusObmMateCard(SysAlarm *recAlarmPtr,I_U8 value);
I_Void UpdateTemperatureObmCard(SysAlarm *recAlarmPtr,I_U8 module);
/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
I_Void updateSystemDetails();
I_Void updateSystemTypeDetails(I_U8 systemType);
I_Void updateChasisFrameDetails(I_U16 totalNumCards, I_U16 numRemoteCards, I_U8 chasisFrameId);
I_Void updateSystemClock(sSysClockInfo sysClkInfo);
I_Void updateDspObjDetails(sDspObjInfo *dspInfo, I_U8 dspCount);
I_Void sendSwitchConForSelf(I_U8 slotId);
I_Void sendSwitchConForMate(I_U8 slotId);
I_Void updateTrunkPortDetails(sTrunkPortDetails portInfo);
I_Void cardSetOperConStateRespHandler(I_U8 slotId, I_U32 cardState, I_U16 result);
I_Void selfSlotIdReqHandler();
I_Void selfSlotIdRespHandler();
I_Void populateCardStateChangeTable(SysAlarm *alarmBuf);
I_Void sendSetOmcipAddressReqToCm(I_S8 *ipAddr, I_U32 port);
I_Void sendSetOmcipAddressReqToCmInActive();
I_Void sendBreakOmcipAddressReqToCm();
I_Void sendNeipReq();
I_Void sendBpmDbInitialized();
I_Void cfgCleanAbisE1TsList();
I_Void initializingCfg();
I_Void updateCardStateChange(I_U8 frameId, I_U8 SlotId, I_U32 operState);
I_Void sendBpmEicTrunkPortStsReq(I_U8 slotId);
I_Void updateChasisFrameTbl();
I_Void chkNupdateMccLinkResourceTable();

/*BSC CS4.0 HA Changes Ends*/

/*BSC R2.0 Changes Starts*/
I_Void sendDsphAvailSts(DspStatusTableApi *dspStsPtr);
I_Void sendDsphBootInfo(sDspObjInfo* dspInfoPtr);
I_Void sendDsphBssAdminStateInd(DspStatusTableApi *dspStsPtr);
I_Void sendDspLockReqToDsph(I_U8 frameId, I_U8 slotId, I_U8 dspId, I_U8 reason);
I_Void sendDspUnlockReqToDsph(I_U8 frameId, I_U8 slotId, I_U8 dspId, I_U8 reason);
I_Void updateDspInfo();
I_S32 markEicCardNotPresent(I_U8 frameId, I_U8 slotId);
I_S32 markEicTrunkPortsNotPresentDisabled(I_U8 frameId, I_U8 slotId);
I_S32 markEicClockSourcePending(I_U8 frameId, I_U8 slotId);
I_Void SendClkSrcPendingAlarm(I_U8 frameId, I_U8 slotId, I_U16 portId);
I_S32 markDspNotPresent(I_U8 frameId, I_U8 slotId);
I_S32 markEicTrunkPortDisabled(I_U8 frameId, I_U8 slotId);
I_S32 markDspDisabled(I_U8 frameId, I_U8 slotId);
I_Void sendDsphDspDown(DspStatusTableApi *dspStsPtr ,I_U32 cause );
I_Void swOfferAckNackHandler();
I_S32 isClkConfiguredOnSlotId(I_U8 slotId);
I_S32 markEicCardDisable(I_U8 frameId, I_U8 slotId);
/*BSC R2.0 Changes Ends*/

/*Changes for R2.3.4 Starts*/
I_Void insertPsuCardDetails(sPowerSupplyObjInfo cardObjInfo);
I_Void insertFanTrayDetails(sFanTrayObjInfo fanTrayObjInfo);
I_S32 markPsuCardNotPresent(PowerSupplyInfoTableIndices *psuCardIndex, I_U8 flag);
I_Void deletePsuCardDetails();
I_S32 markFanTrayNotPresent(FanTrayInfoTableIndices *fanTrayIndex);
I_Void deleteFanTrayDetails();
I_S32 markFanRunning();
/*Changes for R2.3.4 End*/

I_Void sendingInitAbisE1();
I_Void  trunkPortStatusRespHandler();
I_Void  setSystmeTimeRespHandler();
I_Void sendDspBootInfoAlarm(sDspObjInfo *dspInfoPtr);
I_Void sendBpmIccEicTrunkPortStsReq(I_U8);
void  cfgPeerCfgSwitchInfoHandler();
void peerSwitchInfoRespHandler();

/* Changes For E1-T1 */
I_S32 checkBscTrunkTypeAndDspTrauCoding();

/* Changes for LCLS */
I_U32 clusterTableRangeCheck(ClusterTableApi *pClusterTable);
void setClusterTableHandler();
I_Void delClusterTableHandler();
I_S32 cfgSendAifdhmLclsInd(I_Bool localSwitchingSupport,I_U32 bscId);
/*Merger for Mantis #31470*/
I_Void sendNseLockUnlockAlarm(I_U16 nsei, I_U32 adminState);
/*Merger for Mantis #31470*/
/********************************* Change History ***************************
  Release     Patch       Author         Description
  CS2                     Pratibha       Enum Removal Change

 ************************************** End *********************************/

#endif /*__OAMCFG_MSG_HANDLER_H_*/

