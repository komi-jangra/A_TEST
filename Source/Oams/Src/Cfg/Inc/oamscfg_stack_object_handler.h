/***********************************File Header ***************************
       File Name        : oamscfg_stk_object_handler.h
       Purpose          : This file contains function prototype for CFG
                          Stack Configuration Handler  methods and Objects.
       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Bikram Bhatt (BB)
       CSCI ID          :
       Version          :
************************************* End **********************************/
#ifndef OAMCFG_STK_OBJHANDLER_H
#define OAMCFG_STK_OBJHANDLER_H

#define INVALID_CIC           0
#define INVALID_BIC          0xFFFFFFFF
#define INVALID_E1           0xFF
#define INVALID_TS           0xFF

#define IF_TYPE_AIF           1
#define IF_TYPE_ABIS          2

#define SYS_TS_FREE           0
#define SYS_TS_ALLOCATED      1
#define NATIONAL              0x80
#define INTERNATIONAL         0x0
#define NATIONAL_RESERVED     0xC0
#define INTERNATIONAL_RESERVED         0x40
#define CRC_ENABLE            0x01
#define CRC_DISABLE           0x02
#define TRUNK_E1_TYPE         1
#define TRUNK_T1_TYPE         2
#define ENABLE                1
#define DISABLE               0

#define BSC_API_DEFAULT       0
#define SCM_NOACTION          0
#define OAM_SCM_DEFAULT       0

#define OAM_SCM_APPID                 165
#define DEFAULT_TRANSACTION_ID        0
#define DEFAULT_TGPID                 1
#define SIGNALLING                    1
#define SPEECH                        2
#define RESET                         1
#define NO_RESET                      2
#define SSN_BSSAP                     0xFE
 
#define SS7_STACK_DOWN                0
#define SS7_STACK_UP                  1
typedef struct {
  I_U32 currProc;
  I_U32 action;  //SCM_ADD, SCM_DELETE, SCM_MODIFY, SCM_GET, SCM_LOCK, SCM_UNLOCK
} StackProc;

typedef struct {
  // gStoredMsgBufPtr -> This is already defined and stored the configuration message.
  StackProc   currProc;  // Stores the Current On-going stack procedure name
  I_U32       procState; // Stores the state of on-going stack procedure
  I_U32       failCause; // Store the failure cause if any for current stack procedure.
  I_U8        mccTrunkNum; // Store the MccTrunkNum 
  I_U8        mccTrunkTs; // Store the MccTrunkTs 
  I_U8        cardNum; // Store the CardNum
} stkObjectStruct;

stkObjectStruct gStackObject;

#define fillScmHdr(scmHdrPtr, length) do {\
          scmHdrPtr->appid     = OAM_SCM_APPID; \
          scmHdrPtr->operation = gStackObject.currProc.action; \
          scmHdrPtr->opcode    = gStackObject.procState; \
          scmHdrPtr->trid      = DEFAULT_TRANSACTION_ID; \
          scmHdrPtr->len       = length; \
	      }while (0)
            
#define setStackObject(cProc, Action, pState) do {\
          gStackObject.currProc.currProc = cProc; \
          gStackObject.currProc.action   = Action; \
          gStackObject.procState         = pState; \
        }while (0)

/* Set the failue cause incase it is not already set */
#define setFailCauseInStackObj(err) do {\
          if ( CM_SUCCESS == gStackObject.failCause) {\
            gStackObject.failCause = (I_U32)(err);\
          }\
        } while (0)

#define getFailCauseInStackObj() (gStackObject.failCause)
#define getScmAction()   (gStackObject.currProc.action)
#define getScmOperation()   (gStackObject.currProc.currProc) 
#define getScmSubProcState()   (gStackObject.procState) 

#define resetStackObject() do {\
          gStackObject.currProc.currProc = BSC_API_DEFAULT; \
          gStackObject.currProc.action = SCM_NOACTION; \
          gStackObject.procState = OAM_SCM_DEFAULT; \
          gStackObject.failCause = CM_SUCCESS; \
        }while (0)

//#define isStackRespOK(err) (0 == err)

#define isScmRespValid(scmHdr)  ( \
                                  ((scmHdr).operation == gStackObject.currProc.action ) && \
                                  (convertMsgOpCodeFromResp2Req() == gStackObject.procState ) && \
                                  ((scmHdr).trid      == DEFAULT_TRANSACTION_ID ) \
                                )


I_Void setSs7StackTableHandler();
I_Void modifySs7StackTable(Ss7StackConfigTableApi *receivedMsgPtr, Ss7StackConfigTableApi *ss7StackTableDbPtr);
I_Void setAifInterfaceTableHandler();
I_Void setAbisInterfaceTableHandler();
I_Void setLinkSetTableHandler();
I_Void setTrunkTableHandler();
I_Void setLinkTableHandler();
I_S32 findFreeMccTrunkNumMccTrunkTs();
I_Void modifyLinkTable(LinkTableApi *receivedMsgPtr, LinkTableApi *linkTableDbPtr);
I_Void setSs7RouteTableHandler();
I_Void linkLockUnlockHandler(LinkTableApi *receivedMsgPtr, LinkTableApi *linkTableDbPtr);
I_Void setCicTableHandler();
I_Void cicLockReqHandler(CicTableApi *receivedMsgPtr);
I_Void cicUnlockReqHandler(CicTableApi *receivedMsgPtr);
I_Void sendCicLockUnlockRequestToGrhm(I_U16 reqType);
I_S32 checkUniqueCicFromCicTable(I_U32 startCic, I_U32 endCic);
I_S32 getCicForTimeSlots(I_U32 startCic, I_U32 endCic, I_U32 tsCicMap, I_U32 *timeSlotCicMap);
I_S32 isTimeSlotNotUsedForCicOrLink(AiftrunkTableApi *receivedMsgPtr);
I_Bool ss7StackRangeChk(Ss7StackConfigTableApi *receivedMsgPtr);
I_Bool trunkRangeChk(AiftrunkTableApi *receivedMsgPtr);
I_Bool linkSetRangeChk(LinksetTableApi *receivedMsgPtr);
I_Bool linkRangeChk(LinkTableApi *receivedMsgPtr);
I_Bool ss7RouteRangeChk(Ss7RouteTableApi *receivedMsgPtr);
I_Bool storeReceivedMsgBuffer(I_Void *receivedMsgPtr, I_U32 len);
I_Void addSs7StackScmRespHandler();
I_Void modifySs7StackScmRespHandler();
I_Void addInterfaceScmRespHandler();
I_Void addLinkScmRespHandler();
I_Void addSs7RouteScmRespHandler();
I_Void sendStackProcRespToCm();
I_S32 cfgSendStackMessage(I_Void *bufPtr, I_U32 size);
I_Bool isDelSs7StackTableAllowed(I_Void);
I_Bool fillAndSendOamScmSs7StackConfig(I_Void);
I_Void delSs7StackTableHandler(I_Void);
I_Void delSs7StackScmRespHandler(I_Void);
I_Void Ss7StackScmRespHandler(I_Void);
I_Bool isDelAifInterfaceTableAllowed(I_Void);
I_Bool fillAndSendOamScmInterfaceConfig(I_Void);
I_Void delAifInterfaceTableHandler(I_Void);
I_Void delAifInterfaceScmRespHandler(I_Void);
I_Void AifInterfaceScmRespHandler(I_Void);
I_Bool isDelLinkSetTableAllowed(I_Void);
I_Bool fillAndSendOamScmLinkSetConfig(I_Void);
I_Void delLinkSetTableHandler(I_Void);
I_Void delLinkSetScmRespHandler(I_Void);
I_Void LinkSetScmRespHandler(I_Void);
I_Bool isDelLinkTableAllowed(I_Void);
I_Bool fillAndSendOamScmLinkConfig(I_Void);
I_Void delLinkTableHandler(I_Void);
I_Void delLinkScmRespHandler(I_Void);
I_Void LinkScmRespHandler(I_Void);
I_Bool isDelTrunkTableAllowed(I_Void);
I_Bool fillAndSendOamScmTrunkCicConfig(I_Void);
I_Void delTrunkTableHandler(I_Void);
I_Void delTrunkScmRespHandler(I_Void);
I_Void TrunkScmRespHandler(I_Void);
I_Bool isDelSs7RouteTableAllowed(I_Void);
I_Bool fillAndSendOamScmSs7RouteConfig(I_Void);
I_Void delSs7RouteTableHandler(I_Void);
I_Void delSs7RouteScmRespHandler(I_Void);
I_Void Ss7RouteScmRespHandler(I_Void);
I_U32 convertMsgOpCodeFromResp2Req(I_Void);
I_Void ScmRespHandler(I_Void);
I_Bool aifInterfaceRangeChk(AifInterfaceTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmMtp3TimerConfig(I_Void);
I_Void sendE1UnlockReqToGrhm(I_U32 e1Num);
I_Void sendSwitchConnectReqToGrhm();
I_Bool sendSwitchDisconnectReqToGrhm(LinkTableApi *linkTablePtr);
I_Bool fillAndSendOamScmSccpTimerConfig(I_Void);
I_Bool fillAndSendOamScmBssapTimerConfig(I_Void);
I_Bool fillAndSendOamScmLapdTimerConfig(I_Void);
I_Void unblockCicsRespHandler();
I_Void linkSwitchConnectAckHandler();
I_Void linkSwitchConnectNackHandler();
I_Void modifySs7RouteTable(Ss7RouteTableApi *receivedMsgPtr, Ss7RouteTableApi *ss7RouteTableDbPtr);
I_Void sendCicLockAlarm(CicTableApi *receivedMsgPtr);
I_Void sendCicUnlockAlarm(CicTableApi *receivedMsgPtr);
I_Void sendLinkLockAlarm(LinkTableApi *receivedMsgPtr);
I_Void sendLinkUnlockAlarm(LinkTableApi *receivedMsgPtr);
I_S32 validateE1AndTimeSlot(LinkTableApi *receivedMsgPtr);
I_Void modifyExtTrunkNumTsPeerTrunkNumTsInMccLink(I_U32 e1Num, I_U8 timeSlot,I_U32 peerTrunkNum, I_U32 peerTs);
I_Void updateStackTableStatus();
I_Void linkLockUnlockScmRespHandler();
I_Void setMtp3TimerTable();
I_Void setSccpTimerTable();
I_Void setBssapTimerTable();
I_Void setLapdTimerTable();
I_Void cicLockRespHandler();
I_Void cicUnlockRespHandler();
I_Void sendLinkActivationRequest();
I_Bool mtp3TimerRangeChk(Mtp3TimerTableApi *receivedMsgPtr);
I_Bool sccpTimerRangeChk(SccpTimerTableApi *receivedMsgPtr);
I_Bool bssapTimerRangeChk(BssapTimerTableApi *receivedMsgPtr);
I_Bool lapdTimerRangeChk(LapdTimerTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmAlarmModify(I_Void);
I_Void sendSwitchConnectReqToRm(LinkTableApi *linkTablePtr);
I_Bool isStackRespOK(I_S16 err);
I_Void updateOrInsertLinkSetStatusTable(I_U16 linkSetId,I_U32 status);
/* PCU R2.5 Aricent --START*/
I_Bool  isTimeslotAllocatedForFr(I_U16 e1Num, I_U8 timeslot);
/* PCU R2.5 Aricent --END*/

/*Changes for HA*/
I_Void sendPeerSwitchConnectReqToGrhm(LinkTableApi *linkTablePtr);
I_S32 sendBpmSwitchInfoForPeerCard( I_U8 slotId);
I_Void sendSwitchReqToPeerCfg(I_U16 extTrunkNum, I_U8 extTs, I_U32 action, I_U8 subType);
I_Void sendPeerSwitchDisconnectReqToGrhm(LinkTableApi *linkTablePtr);  

/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
I_Void setBssapInterfaceTable(BssapIntfConfigTableApi *receivedCmMsgPtr);	
I_Void delBssapInterfaceTable(BssapIntfConfigTableApi *receivedCmMsgPtr);
I_Void setSccpSpConfigTable(SigtranSccpSPConfigTableApi *receivedMsgPtr);	
I_Void delSccpSpConfigTable(SigtranSccpSPConfigTableApi *receivedMsgPtr);	
I_Void setSccpSsConfigTable(SigtranSccpSSConfigTableApi *receivedMsgPtr);	
I_Void delSccpSsConfigTable(SigtranSccpSSConfigTableApi *receivedMsgPtr);	
I_Void setSccpCssConfigTable(SigtranSccpCSSConfigTableApi *receivedMsgPtr);	
I_Void delSccpCssConfigTable(SigtranSccpCSSConfigTableApi *receivedMsgPtr);	
I_Void setSccpCspConfigTable(SigtranSccpCSPConfigTableApi *receivedMsgPtr);	
I_Void delSccpCspConfigTable(SigtranSccpCSPConfigTableApi *receivedMsgPtr);	
I_Void setM3uaLocalAspConfigTable();	
I_Void delM3uaLocalAspConfigTable();	
I_Void setM3uaRemoteAspConfigTable();	
I_Void delM3uaRemoteAspConfigTable();	
I_Void setM3uaLocalAsConfigTable();	
I_Void delM3uaLocalAsConfigTable();	
I_Void setM3uaRemoteAsConfigTable();	
I_Void delM3uaRemoteAsConfigTable();	
I_Void setSctpConfigTable();	
I_Void delSctpConfigTable();	
I_Void setSigtranBssapTimerTable();	
//I_Void delSigtranBssapTimerTable();	
I_Void setSigtranSccpTimerTable();	
//I_Void delSigtranSccpTimerTable();	
I_Void setSigtranM3uaTimerTable();	
//I_Void delSigtranM3uaTimerTable();	
I_Void setSigtranSctpTimerTable();	
//I_Void delSigtranSctpTimerTable();
/*SCM_RESP*/	
I_Void BssapInterfaceScmRespHandler();
I_Void SccpSpConfigScmRespHandler();	
I_Void SccpSsConfigScmRespHandler();
I_Void SccpCssConfigScmRespHandler();
I_Void SccpCspConfigScmRespHandler();
I_Void M3uaLocalAspConfigScmRespHandler();	
I_Void M3uaRemoteAspConfigScmRespHandler();	
I_Void M3uaLocalAsConfigScmRespHandler();	
I_Void M3uaRemoteAsConfigScmRespHandler();	
I_Void SctpConfigScmRespHandler();	
I_Void SigtranBssapTimerScmRespHandler();	
I_Void SigtranSccpTimerScmRespHandler();	
I_Void SigtranM3uaTimerScmRespHandler();	
I_Void SigtranSctpTimerScmRespHandler();	
/*SCM_RESP*/	
/*SCM_RESP-NESTED*/	
I_Void addBssapInterfaceScmRespHandler();	
I_Void delBssapInterfaceScmRespHandler();	
I_Void addSccpSpConfigScmRespHandler();	
I_Void delSccpSpConfigScmRespHandler();	
I_Void addSccpSsConfigScmRespHandler();	
I_Void delSccpSsConfigScmRespHandler();	
I_Void addSccpCssConfigScmRespHandler();	
I_Void delSccpCssConfigScmRespHandler();	
I_Void addSccpCspConfigScmRespHandler();	
I_Void delSccpCspConfigScmRespHandler();	
I_Void addM3uaLocalAspConfigScmRespHandler();	
I_Void modifyM3uaLocalAspConfigScmRespHandler();	
I_Void delM3uaLocalAspConfigScmRespHandler();	
I_Void addM3uaRemoteAspConfigScmRespHandler();	
I_Void delM3uaRemoteAspConfigScmRespHandler();	
I_Void addM3uaLocalAsConfigScmRespHandler();	
I_Void delM3uaLocalAsConfigScmRespHandler();	
I_Void addM3uaRemoteAsConfigScmRespHandler();	
I_Void delM3uaRemoteAsConfigScmRespHandler();	
I_Void addSctpConfigScmRespHandler();	
I_Void modifySctpConfigScmRespHandler();	
I_Void addBssapTimerScmRespHandler();	
I_Void modifyBssapTimerConfigScmRespHandler();
//I_Void delBssapTimerScmRespHandler();	
I_Void addSigtranSccpTimerScmRespHandler();	
I_Void modifySigtranSccpTimerScmRespHandler();
//I_Void delSigtranSccpTimerScmRespHandler();	
I_Void addSigtranM3uaTimerScmRespHandler();	
I_Void modifySigtranM3uaTimerScmRespHandler();
//I_Void delSigtranM3uaTimerScmRespHandler();	
I_Void addSigtranSctpTimerScmRespHandler();	
I_Void modifySigtranSctpTimerScmRespHandler();	
//I_Void delSigtranSctpTimerScmRespHandler();	
I_Bool bssapTmrConfigRangeChk(BssapTmrConfigTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmBsTimerConfig(I_Void);
I_Bool sccpTmrConfigRangeChk(SigtranSccpTimerTableApi *receivedMsgPtr);
I_Bool m3uaTmrConfigRangeChk(M3uaTmrConfigTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmSccpTmrConfig(I_Void);
I_Bool fillAndSendOamScmM3uaTimerConfig(I_Void);
I_Bool sctpTmrConfigRangeChk(SigtranSctpTimerTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmSctpTimerConfig(I_Void);
I_Bool sctpConfigRangeChk(SigtranSctpConfigTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmSctpConfig(I_Void);
I_Bool bssapIntfConfigRangeChk(BssapIntfConfigTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmBsInterfaceConfig(I_Void);
I_Bool sccpSpConfigRangeChk(SigtranSccpSPConfigTableApi *receivedMsgPtr);
I_Bool fillAndSendOamScmSccpSpConfig(I_Void);
I_Bool fillAndSendOamScmSccpSsConfig(I_Void);
I_Bool fillAndSendOamScmSccpCssConfig(I_Void);
I_Bool fillAndSendOamScmSccpCspConfig(I_Void);
I_Bool fillAndSendOamScmM3uaLocalAspConfig(I_Void);
I_Bool fillAndSendOamScmM3uaLocalAspAdminConfig(I_U16 adminState);
I_Bool fillAndSendOamScmM3uaRemoteAspConfig(I_Void);
I_Bool fillAndSendOamScmM3uaLocalAsConfig(I_Void);
I_Bool fillAndSendOamScmM3uaRemoteAsConfig(I_Void);
I_Void aspLockUnlockHandler();
//I_Void isDelBssapTimerConfigTableAllowed();	
/*SCM_RESP-NESTED*/
#define SS7 1
#define SIGTRAN 2
#define INTERNATIONAL_00 0
#define INTERNATIONAL_01 1
#define NATIONAL_10 2
#define NATIONAL_01 3
#define ITU 1
#define ANSI 2 
#define PC_AOIP_REMOTE 0
#define PC_AOIP_LOCAL 1	
/*IP_BSC_STACK: 18 JULY 2016 Gaurav Sinha*/
/*IP_BSC_STACK: Initializing SigtranM3uaLAspConfigTableApi OperationalState Gaurav Sinha 29-09-2016*/
I_Void initSigtranM3UALocalAspOperStateAtStartUp(I_Void);
/*IP_BSC_STACK: Initializing SigtranM3uaLAspConfigTableApi OperationalState Gaurav Sinha 29-09-2016*/
/*Added for mantis #32112 #32021 Gaurav Sinha 04-10-2016*/
I_Void checkAndSendAspUnlock(I_U32 aspId);
I_U32 getAspIdFromSlotId(I_U32 slotId);
/*Added for mantis #32112 #32021 Gaurav Sinha 04-10-2016*/
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
I_S32 getFreeIndexAspStatus(I_Void);
I_Void freeIndexfromgStructAspStatusVar(I_U16 localAspId);
#define STK_REQUEST 1
#define STK_RESPONSE 2
#define STK_FAILURE 3
I_Void setStatusAspLocal(I_U16 localAspId,I_U16 adminState,I_U32 operation);
I_S32 getIndexFromAspId(I_U16 localAspId);
I_Void initGlobalDsForAspStatusAtStartup(I_Void);
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS4.0                   BB             Created 

************************************** End *********************************/

#endif /*OAMCFG_STK_OBJHANDLER_H */
