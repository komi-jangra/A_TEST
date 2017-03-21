/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamstrxh_datasruct.h
 PURPOSE           :  Contains TrxHandler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSTRXH_DATASTRUCT_H
#define __OAMSTRXH_DATASTRUCT_H

typedef struct
{
   OptFlag                        isInactiveSwDesPresent;
   OptFlag                        isBtsIdPresent;
   OptFlag                        isGprsSupportPresent;
   /* EGPRS Start */
   OptFlag                        isEgprsSupportPresent;
   /* EGPRS End */
   PtrxId                         ptrxId;
   LtrxId                         ltrxId;
   I_U8                           tei;
   Tei                            nwTei; /* Added in PCU R2.5 */
   OamsCellIndex                  cellIndex;/* Added in PCU R2.5 */
   CellId                         cellId;
   Lac                            lac;
   I_U8                           objectType;
   I_U32                          trxhAdmnState;
   I_U32                          trxhOpState;
   OnmProtocolVersion             onmProtocolVersion;
   HwCap                          hwCapability;
//   HwDes                          hwDescription; removed in CS3.0
   SwDes                          swDescription;
   InactiveSwDes                  inactiveSwDes;
//   I_PVoid		          bssCsConfPtr;    removed in CS3.0
   I_U32			  e1Num ;
   ChgrId                         chgrId;
   I_U32                          trxLocation ;
   I_U32                          rfPathGain ;
   I_U32                          bicId;  /* Added in R2.2 */
   I_U8                           trxPos; /* Added in R2.2 */
   I_U8                           ulCodingScheme; /* Added in R2.2 */
   I_U8                           dlCodingScheme; /* Added in R2.2 */
   /* EGPRS Start */
   I_U8                           dlMsbCodingScheme;
   I_U8                           dlLsbCodingScheme;
   I_U8                           ulMsbCodingScheme;
   I_U8                           ulLsbCodingScheme;
   /* EGPRS End */
   Tei                            btsApplTei; /* Added in PCU R2.5 */
   I_U16                          cbchSupported; /* Added in R2.4 */
   I_U16                          amrSupportedInTrx; /* Added in R2.4 */
   I_U32                          amrCodecRate; /* Added in R2.4 */
	 I_S32													instanceId;
   I_U16                          localSwitchingSupported;  /*Added in R2.8*/
   I_U16                          idleMeasurementSupported; /*Added in R2.8*/
   I_U16                          dynamicSdcchSupported;  /*Added in R2.8*/
   I_U16                          isExtendedCellSupported; /* Extended Cell Changes */
   I_U8                           isCellExtended; /* Extended Cell Changes */
   I_U32                          satFlag; /* Added for handling AMR-FR codec in Satellite BTS - 2.9 */
   I_U8                           actualPwrCap;/*Added for RF PWR UPDATE at UNLOCK*/
/* R2.9 Changes Starts */
/* I_U32                        btsIpLinkStatus;
   I_U16                          transitionViaStandby;
   I_U8                           mapAllowed;
   I_U8                           linkEstablished;
   I_U8                           parentStatus;
   I_U8                           omlLapdLinkStatus;
   I_U8                           rslLapdLinkStatus;
   I_U8                           isThisBcchTrx;
   I_U8                           bcchAvail;
   I_U8                           lockReceived;
   I_U8                           unLockReceived;
   I_U16                          delChanRequiredFlag;
   I_U16                          trxhState;*/
 /* R2.9 Changes Ends */
}OamsTrxhContext;

/* Added for BSC R2.0 (High Capacity BSC) */
typedef struct 
{
   I_U16		trauAbisTs;
	 I_U16		trauAbisSubTs;
	 I_U16		trauIndex;
}OamsTrxhTrauPcmData;
typedef struct
{
   I_U32    	      	 dspId;
	 I_U32								coreId;
   OamsTrxhTrauPcmData	trauTsPcmIndex[MAX_CHAN_IN_PTRX];
}OamsTrxhTrauChanPcmIndexMapData;

/* 
   Added for R2.5 (HA-No LAPD Down Feature)
   Dated: 03-Aug-2010
*/
typedef struct 
{
   PtrxId   ptrxId;
   I_U8     isInactiveSwDesPresent;
   I_U8     isBtsIdPresent;
   I_U8     isGprsSupportPresent;
   /* EGPRS Start */
   I_U8     isEgprsSupportPresent;
   /* EGPRS End */
   I_U32    ltrxId;
   I_U16    cellIndex;
   I_U32    cellId;
   I_U16    lac;
   I_U8     objectType;
   I_U32    trxAdminState;
   I_U32    trxOpState;
   /* OnmProtocolVersion */
   I_U8     versionx;
   I_U8     versiony;
   /* HwCap */
   I_U8     freqHoppSupport;
   I_U8     diversitySupport;
   I_U8     powerClassCapability;
   I_U8     bandSupport;
   I_U8     lsclAvailable;
   I_U8     memCapability;
   /* SwDes */
   I_U8     swLen;
   I_U8     swFileVersion[25];
   /* Inactive Sw Version */
   I_U8     inactiveSwLen;
   I_U8     inactiveSwFileVersion[25];
   I_U32    e1Num;
   I_U32    chgrId;
   I_U32    ulCodingScheme;
   I_U32    dlCodingScheme;
   /* EGPRS Start */
   I_U8                           dlMsbCodingScheme;
   I_U8                           dlLsbCodingScheme;
   I_U8                           ulMsbCodingScheme;
   I_U8                           ulLsbCodingScheme;
   /* EGPRS End */
   /* Hot Standby changes -starts*/
   I_U32      currentState;
   I_U8       linkEstablished;
   I_U8       sapi;
   I_U8       parentStatus;
   I_U8       oamsResult;
   I_U8       isThisBcchTrx;
   I_U32      subState;
   SysBtsType btsType;
   I_U8       isCellExtended;
   I_U16      channelNumber;
   I_U16      delOrLockReq;
   I_U8       maxNoRetransmission;
   I_U8       lockReceived;
   I_U8       unLockReceived;
   I_U16      delChanRequiredFlag;
   I_U8       blockTimer;   
   I_U8       opStopAckReceived;
   I_U16      tmHelloCntinUE;
   I_U32      satFlag;
   I_U8       actualPwrCap;/*Added for RF PWR UPDATE at UNLOCK*/

   
   /*Hot Standby changes ends*/
}OamsTrxhContxtReplica;

/*Hot Standby changes-starts*/
#define  TRXH_CURRENT_STATE_INIT                1
#define  TRXH_CURRENT_STATE_LOCKED_DISABLED     2
#define  TRXH_CURRENT_STATE_UNLOCKED_DISABLED   3
#define  TRXH_CURRENT_STATE_UNLOCKED_ENABLED    4
#define  TRXH_CURRENT_STATE_CRE_CHN_ACK         5
#define  TRXH_CURRENT_STATE_DEL_CHN_ACK         6
#define  TRXH_CURRENT_STATE_BTS_ATTR_RESP       7
#define  TRXH_CURRENT_STATE_CHAN_ATTR_RESP      8
#define  TRXH_CURRENT_STATE_PS_ATTR_RESP        9
#define  TRXH_CURRENT_STATE_OPSTOP_RESP         10
#define  TRXH_CURRENT_STATE_OPSTART_RESP        11
#define  TRXH_CURRENT_STATE_LAPD_ESTABLISHING   12
/*Hot Standby changes-ends*/

typedef struct
{
   SysHdr              sysHdr;
   I_U32               ptrxId;
}OamsTrxhEnvTrxhAvailabilityInd;
#endif   /* __OAMSTRXH_DATASTRUCT_H */
