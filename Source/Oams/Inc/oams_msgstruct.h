/** ts=3 ******************************************************* File Header **
 FILE NAME         :  oams_msgstruct.h
 PURPOSE           :  Contains structures used for messaging within OAMS  
 PROJECT           :  BSS
 SUBSYSTEM         :  OAMS
 AUTHOR            :  Aricent Team
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMS_MSGSTRUCT_H
#define __OAMS_MSGSTRUCT_H


typedef struct
{
   SysHdr                    sysHdr;
   SysAlarm                  sysAlarm;
}OamsCfgAfhSysAlarm;



/*CFG - CELLH  Interface*/

typedef struct 
{
   SysHdr                    sysHdr;
   OamsObjectType            objType;
   I_U32                     objId;
   I_U32                     lac;
   OamsCellIndex             cellIndex; /*Added in PCU R2.5 Aricent*/ 
  OamsReason                 reason;
}OamsCfgCellhLockReq;

typedef struct 
{
   SysHdr                    sysHdr;
   OamsObjectType            objType;
   I_U32                     objId;
   I_U32                     lac;
   OamsCellIndex             cellIndex; /*Added in PCU R2.5 Aricent*/ 
   OamsReason                reason;
}OamsCfgCellhUnlockReq;

typedef struct 
{
   SysHdr                    sysHdr;
   I_U32                     cellId; 
   I_U32                     lac;
   OamsCellIndex             cellIndex; /*Added in PCU R2.5 Aricent*/ 
   I_Bool                    cellBar;
   OamsReason                reason;
}OamsCfgCellhCellBarAccess;

typedef struct 
{
   SysHdr                    sysHdr;
   I_U32                     objId;
   I_U32                     lac;
   OamsCellIndex             cellIndex; /*Added in PCU R2.5 Aricent*/ 
}OamsCfgCellhBlockInd;

typedef struct 
{
   SysHdr                    sysHdr; 
  OamsObjectType             objType;
   I_U32                     objId;    
   I_U32                     lac;
   OamsCellIndex             cellIndex; /*Added in PCU R2.5 Aricent*/ 
}OamsCellhCfgUnlockResp;

typedef struct 
{
   SysHdr                    sysHdr;
   OamsObjectType            objType;
   I_U32                     objId;
   I_U32                     lac;
   OamsCellIndex             cellIndex; /*Added in PCU R2.5 Aricent*/ 
	 I_U16										 result;/*CM_SUCCESS ,CELL_ENA CELL_DIS */
}OamsCellhCfgLockResp;

typedef struct 
{
   SysHdr                   sysHdr;
   SysAlarm                 sysAlarm;
}OamsCellhCfgAlarmInd;

typedef struct 
{
   SysHdr                   sysHdr;
   I_U32                    cellId;
   I_U32	            lac;
   OamsCellIndex            cellIndex; /*Added in PCU R2.5 Aricent*/ 
}OamsCfgCellhCsNeighCellsChange;

/* CS4.0 : Abis E1 Lock/Unlock Change : Starts */
typedef struct 
{
   SysHdr                   sysHdr;
   I_U32                    objId;
   I_U32	            lac;
   OamsCellIndex            cellIndex; /*Added in PCU R2.5 Aricent*/ 
   I_U32	            e1Id;
}OamsCfgCellhAbisE1UnlockReq;

typedef struct 
{
   SysHdr                   sysHdr;
   I_U32                    objId;
   I_U32	            lac;
   OamsCellIndex            cellIndex; /*Added in PCU R2.5 Aricent*/ 
   I_U32	            e1Id;
}OamsCfgCellhAbisE1LockReq;

typedef struct 
{
   SysHdr                   sysHdr;
   I_U32                    objId;
   I_U32	            lac;
   OamsCellIndex            cellIndex; /*Added in PCU R2.5 Aricent*/ 
   I_U32	            e1Id;
}OamsCellhCfgAbisE1LockResp;

typedef struct 
{
   SysHdr                   sysHdr;
   I_U32                    objId;
   I_U32	            lac;
   OamsCellIndex            cellIndex; /*Added in PCU R2.5 Aricent*/ 
   I_U32	            e1Id;
}OamsCellhCfgAbisE1UnlockResp;

/* CS4.0 : Abis E1 Lock/Unlock Changes : Ends */

/*CFG - TRXH Interface */

/* R2.2 Changes : Starts */
typedef struct
{
   SysHdr                  sysHdr;
   I_U32                   objId;
}OamsCfgTrxhTrxReset;

typedef struct
{
   SysHdr                  sysHdr;
   I_U32                   objId;
}OamsTrxhCfgTrxResetAck;

typedef struct
{
   SysHdr                  sysHdr;
   I_U32                   objId;
   I_U32                   cause;
}OamsTrxhCfgTrxResetNack;

/* R2.2 Changes : Ends  */

typedef struct 
{
   SysHdr                  sysHdr;
   OamsObjectType          objType;
   I_U32                   objId;
   I_U32                   e1Num;
   OamsReason              reason;
}OamsCfgTrxhLockReq;

typedef struct 
{
   SysHdr                  sysHdr;
   OamsObjectType          objType;
   I_U32                   objId;
   I_U32                   e1Num;
}OamsTrxhCfgLockResp;

typedef struct 
{
   SysHdr                  sysHdr;
   OamsObjectType          objType;
   I_U32                   objId;
   I_U32                   e1Num;
   OamsReason              reason;
}OamsCfgTrxhUnlockReq;

typedef struct 
{
   SysHdr                  sysHdr;
   OamsObjectType          objType;
   I_U32                   objId; 
   I_U32                   e1Num;
}OamsTrxhCfgUnlockResp;

typedef struct 
{
   SysHdr                   sysHdr;
   SysAlarm                 sysAlarm;
}OamsTrxhCfgAlarmInd;

typedef OamsTrxhCfgAlarmInd OamsBichCfgAlarmInd ; /*Changes from CS2.2*/

typedef OamsTrxhCfgAlarmInd OamsCcuhCfgAlarmInd; /*Added for CS4.0 CCU*/

typedef OamsCfgTrxhLockReq OamsCfgTrxhBlockReq; /*Added For PCU R2.5.1*/

typedef OamsTrxhCfgLockResp OamsTrxhCfgBlockResp; /*Added For PCU R2.5.1*/

/* CellH - TRXH interface */
typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
}OamsTrxhMapentInitiateMap;
/* BSC R2.5.5 ABIS HA Changes : Start */
typedef struct
{
   SysHdr            sysHdr;
   PtrxId            ptrxId;
   CellId            cellId;
   Lac               lac;
   I_U16             oprState;
   OptFlag           isBcchTrx;
   I_U8              btsType;
}OamsTrxhCellhOprStateInd;
/* BSC R2.5.5 ABIS HA Changes : End */
/** New 02-Apr-2010 **/
typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   LtrxId                        ltrxId;
   OamsCellIndex                 cellIndex;
   CellId                        cellId;
   Lac                           lac;
   ChgrId                        chgrId;
   Hsn                           hsn;
   FrequencyList                 hfs;
   Maio                          maio;
   I_U32                         tsc;
   I_U32                         band;
   I_U32                         maxPower;
   I_U32                         bcchPower;
   I_U32                         chCombinationId[MAX_CHANNEL_IN_PTRX];
   I_U8                          isCellExtended;
}OamsMapentTrxhCreLtrxPtrxMappingReq;


typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   LtrxId                        ltrxId;
   Lac                           lac;
   CellId                        cellId;
   ChgrId                        chgrId;
}OamsTrxhMapentCreLtrxPtrxMappingResp;


typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   LtrxId                        ltrxId;
   CellId                        cellId;
   Lac                           lac;
   ChgrId                        chgrId;
}OamsTrxhMapentCreLtrxPtrxMappingFailed;


typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   LtrxId                        ltrxId; 
   CellId                        cellId;
   Lac                           lac;
}OamsTrxhMapentDelLtrxPtrxMappingResp;


typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   LtrxId                        ltrxId; 
   CellId                        cellId;
   Lac                           lac;
}OamsMapentTrxhDelLtrxPtrxMappingReq;


typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   Tei                           tei;
   CellId                        cellId;
   Lac                           lac;
}OamsTrxhCellhBcchAvail;


typedef struct
{
   SysHdr                        sysHdr;
   PtrxId                        ptrxId;
   Tei                           tei;
   CellId                        cellId;
   Lac                           lac;
}OamsTrxhCellhBcchUnAvail;
/* PCU Rel 2.5 Changes : Starts */
typedef struct
{
   SysHdr                    sysHdr;
   I_U32                     ptrxId;
}OamsCellhTrxhUpdatePsCellAttr;
/* PCU Rel 2.5 Changes : Ends*/
typedef struct
{
   SysHdr                        sysHdr;
   CellId                        cellId;
   Lac                           lac;
   I_U8                          isCellExtended;
}OamsCellhMapentCreMapReq;

typedef struct
{
   SysHdr                        sysHdr;
   CellId                        cellId;
   Lac                           lac;
}OamsCellhMapentDelMapReq;


typedef struct
{
   SysHdr                        sysHdr;
   CellId                        cellId;
   Lac                           lac;
}OamsMapentCellhDelMapResp;

typedef struct
{
   SysHdr                        sysHdr;
   CellId                        cellId;
   Lac                           lac;
   PtrxId                        ptrxId;
   Tei                           tei;
}OamsTrxhCellhSendSacchInfo;

/* For SWMH CS3.0 */

typedef struct
{
   SysHdr                   sysHdr;
   SysAlarm                 sysAlarm;
}OamsSwmhCfgAlarmInd;

/*BSC CS4.0 HA CHanges Starts*/
typedef struct
{
   SysHdr                  sysHdr;
}OamsCfgSelfMsg;
/*BSC CS4.0 HA CHanges Ends*/

/*****************************************************/
/********* Messages from CFG to DSPH starts **********/
/*****************************************************/

typedef struct OamsCfgDsphDspAvailStatus
{
  SysHdr  sysHdr;
  I_U8    frameId;
  I_U8    slotId; 
  I_U8    dspId;
  I_U8    physicalPresenceState; 
}OamsCfgDsphDspAvailStatus;

typedef struct OamsCfgDsphDspDownInfo
{
  SysHdr  sysHdr;
  I_U8    frameId;
  I_U8    slotId; 
  I_U8    dspId;
  I_U8    cause; /*will be received from OIL hasdefines needs to be fixed*/  
}OamsCfgDsphDspDownInfo;

typedef OamsCfgDsphDspDownInfo OamsCfgDsphDspResetFailInfo;

typedef struct OamsCfgDsphDspResetReq
{
  SysHdr  sysHdr;
  I_U8    frameId;
  I_U8    slotId; 
  I_U8    cardType;
  I_U8    dspId;
}OamsCfgDsphDspResetReq;

typedef struct OamsCfgDsphDspLockReq
{
  SysHdr      sysHdr;
  I_U8        frameId;
  I_U8        slotId; 
  I_U8        dspId;
  OamsReason  reason;
}OamsCfgDsphDspLockReq;

typedef struct OamsCfgDsphDspUnlockReq
{
  SysHdr      sysHdr;
  I_U8        frameId;
  I_U8        slotId; 
  I_U8        dspId;
  OamsReason  reason;
}OamsCfgDsphDspUnlockReq;

typedef struct OamsCfgDsphBssAdminStateInd
{
  SysHdr  sysHdr;
  I_U8    frameId;
  I_U8    slotId; 
  I_U8    dspId;
  I_U8    bssAdminState; /*BSS_LOCK/BSS_UNLOCK */  
}OamsCfgDsphBssAdminStateInd;

/*****************************************************/
/********* Messages from CFG to DSPH ends ************/
/*****************************************************/

/*****************************************************/
/********* Messages from DSPH to CFG starts **********/
/*****************************************************/

typedef struct OamsDsphCfgDspLockResp
{
  SysHdr      sysHdr;
  I_U8        frameId;
  I_U8        slotId; 
  I_U8        dspId;
  OamsReason  reason; /*hadefs in oamsxxx_hashdef.h*/
  OamsResult  result; /*OAMS_RSLT_SUCCESS/OAMS_RSLT_FAILURE*/
  I_U32       errCause;
}OamsDsphCfgDspLockResp;

typedef struct OamsDsphCfgDspUnlockResp
{
  SysHdr      sysHdr;
  I_U8        frameId;
  I_U8        slotId; 
  I_U8        dspId;
  OamsReason  reason;
  OamsResult  result; /*OAMS_RSLT_SUCCESS/OAMS_RSLT_FAILURE*/
  I_U32       errCause;
}OamsDsphCfgDspUnlockResp;

typedef struct OamsDsphCfgDspResetResp
{
  SysHdr      sysHdr;
  I_U8        frameId;
  I_U8        slotId; 
  I_U8        cardType;
  I_U8        dspId;
  OamsResult  result; /*OAMS_RSLT_SUCCESS/OAMS_RSLT_FAILURE*/
  I_U32       errCause;
}OamsDsphCfgDspResetResp;

typedef struct OamsDsphCfgDspInitTrauSucc
{
  SysHdr  sysHdr;
  I_U8    frameId;
  I_U8    slotId; 
  I_U8    dspId;
}OamsDsphCfgDspInitTrauSucc;

typedef struct OamsDsphCfgDspInitTrauFail
{
  SysHdr  sysHdr;
  I_U8    frameId;
  I_U8    slotId; 
  I_U8    dspId;
  I_U8    cause; /*hashdefines needs to be fixed*/     
}OamsDsphCfgDspInitTrauFail;

/*****************************************************/
/********* Messages from DSPH to CFG Ends ***********/
/*****************************************************/

/************************************
 Msg. structure from DSPH to TSM
************************************/

typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t   trauHdr;
  I_U8           law;
}__attribute__((packed)) DTrauMgsDspInitReq;


typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t  trauHdr;
  I_U8           law;
  I_U8           jitterBuffer;
  I_U16          minDelay;
  I_U16          nomDelay;
  I_U16          maxDelay;
}__attribute__((packed)) DTrauMgsRtpDspInitReq;


typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t   trauHdr;
}__attribute__((packed))  DTrauMgsTrauStartReq;


typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t   trauHdr;
}__attribute__((packed)) DTrauMgsDspTriggerReq;

/***********************************
 Msg. structure from TSM to DSPH 
***********************************/

typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t   trauHdr;
  I_U8           response;
}__attribute__((packed)) DTrauMgsDspInitResp;


typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t   trauHdr;
  I_U8           response;
}__attribute__((packed)) DTrauMgsTrauStartResp;


typedef struct
{
  SysHdr         sysHdr;
  tHdr           hdr;
  message_hdr_t   trauHdr;
  I_U8           response;
}__attribute__((packed)) DTrauMgsDspTriggerResp;

/*Changes PCU R2.5 Aricent --Start*/
/*CFG - PSSCM  Interface*/
typedef struct
{
   SysHdr                    sysHdr;
   OamsReason                reason;
}OamsCfgPsscmUnlockReq;

typedef struct
{
   SysHdr                    sysHdr;
   OamsReason                reason;
}OamsCfgPsscmLockReq;

typedef struct
{
   SysHdr                    sysHdr;
   OamsResult                result;
   OamsCause                 cause;
}OamsPsscmCfgUnlockResp;

typedef struct
{
   SysHdr                    sysHdr;
   OamsResult                result;
   OamsCause                 cause;
}OamsPsscmCfgLockResp;

typedef struct
{
   SysHdr                    sysHdr;
   SysAlarm                  sysAlarm;
}OamsPsscmCfgAlarmInd;

/*CFG - GBH  Interface*/
typedef struct
{
   SysHdr                    sysHdr;
}OamsCfgGbhFirstNsvcEnabled;

typedef struct
{
   SysHdr                    sysHdr;
}OamsCfgGbhLastNsvcDisabled;

typedef struct
{
   SysHdr                    sysHdr;
   SysAlarm                  sysAlarm;
}OamsGbhCfgAlarmInd;

typedef struct
{
   SysHdr                     sysHdr;
}OamsCfgGbhSigBvcResetFailed;

/*CFG - NSVCH  Interface*/
typedef struct
{
   SysHdr                    sysHdr;
   I_U32                     nsvcId;
   OamsReason                reason;
}OamsCfgNsvchUnlockReq;

typedef struct
{
   SysHdr                    sysHdr;
   I_U32                     nsvcId;
   OamsReason                reason;
}OamsCfgNsvchLockReq;

typedef struct
{
   SysHdr                    sysHdr;
   I_U32                     nsvcId;
   OamsResult                result;
   OamsCause                 cause;
}OamsNsvchCfgUnlockResp;

typedef struct
{
   SysHdr                    sysHdr;
   I_U32                     nsvcId;
   OamsResult                result;
   OamsCause                 cause;
}OamsNsvchCfgLockResp;

typedef struct
{
   SysHdr                    sysHdr;
   SysAlarm                  sysAlarm;
}OamsNsvchCfgAlarmInd;

/*CFG - PSCH  Interface*/

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;  
   I_U16                      bvci;
   OamsReason                 reason;
}OamsCfgPschUnlockReq;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;
   OamsReason                 reason;
}OamsCfgPschLockReq;


typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;
   I_U16                      bvci;
   OamsResult                 result;
   OamsCause                  cause;
}OamsPschCfgUnlockResp;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;
   OamsResult                 result;
   OamsCause                  cause;
}OamsPschCfgLockResp;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;
}OamsCfgPschShutdownInd;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;
   I_Bool                     cellBar;
   OamsReason                 reason;
}OamsCfgPschCellBarAccess;

typedef struct
{
   SysHdr                     sysHdr;
   OamsCellIndex              cellIndex;
   I_U16                      bvci;
}OamsCfgPschBvcOpFailed;

typedef struct
{
   SysHdr                    sysHdr;
   OamsCellIndex             cellIndex;
   I_U16                     bvci;
}OamsCfgPschPtpBvcReset;

typedef struct
{
   SysHdr                    sysHdr;
   SysAlarm                  sysAlarm;
}OamsPschCfgAlarmInd;

/* PSCH-CELLH Interface */
typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
}OamsPschCellhPsCellEnabled;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
}OamsPschCellhPsCellDisabled;

/* BICH-TRXH */
typedef struct
{
   SysHdr                     sysHdr;
   I_U32                      ptrxId;
}OamsBichTrxhIpLinkUp;

typedef struct
{
   SysHdr                     sysHdr;
   I_U32                      ptrxId;
}OamsBichTrxhIpLinkDown;

typedef struct
{
   SysHdr                    sysHdr;
   I_U16					 nsei;
}OamsCfgPschNseUnlockReq;

typedef struct
{
   SysHdr                    sysHdr;
   I_U16					 nsei;
}OamsCfgPschNseLockReq;

typedef struct
{
   SysHdr                    sysHdr;
   I_U16					 nsei;
}OamsPschCfgNseUnlockResp;

typedef struct
{
   SysHdr                    sysHdr;
   I_U16					 nsei;
}OamsPschCfgNseLockResp;
/*PSCH-GBH Interface*/

typedef struct
{
   SysHdr                     sysHdr;
   I_U8                       cbl;
   I_Bool                     isCblChanged; 
}OamsGbhPschSigBvcResetInd;

typedef struct
{
   SysHdr                    sysHdr;
}OamsGbhPschGbDownInd;

/*PSCH-PSSCM Interface */
typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      bvci;
}OamsPschPsscmProvPtpBvc;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      bvci;
}OamsPschPsscmUnprovPtpBvc;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      bvci;
   I_U16                      result;
   I_U16                      cause;
}OamsPsscmPschProvPtpBvcCnf;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      bvci;
   I_U16                      result;
   I_U16                      cause;
}OamsPsscmPschUnprovPtpBvcCnf;

/*PSSCM-NSVCH Interface */
typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      nsei;
   I_U16                      nsvci;
   I_U8                      cause;
}OamsNsvchPsscmNsvcDisabledInd;

typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      nsei;
   I_U16                      nsvci;
}OamsNsvchPsscmNsvcEnabledInd;
/* Psch-Trxh Interface*/
typedef struct
{
   SysHdr                     sysHdr;
   I_U16                      lac;
   I_U16                      cellId;
   OamsCellIndex              cellIndex;
   I_U32                      ptrxId;
   I_U8                       egprsAllowed; /* EGPRS Changes */
}OamsTrxhPschPsAllowed;

typedef struct
{
  SysHdr                     sysHdr;
  I_U16                      lac;
  I_U16                      cellId;
  OamsCellIndex              cellIndex;
  I_U32                      ptrxId;
}OamsTrxhPschPsNotAllowed;



typedef struct
{
   SysHdr                     sysHdr;
   I_U32                      ptrxId;
   I_U8                       cbl;
}OamsPschTrxhPsAttrChangeInd;

/*Changes PCU R2.5 Aricent --End*/

/*
Added in R2.5.5 (ABIS HA)
Dated: 22-Sep-2010
*/
typedef struct
{
   SysHdr                     sysHdr;
}OamsTrxhmRmAipResp;

typedef struct
{
   SysHdr                     sysHdr;
}OamsCfgTbReadyStateInd;


#endif

