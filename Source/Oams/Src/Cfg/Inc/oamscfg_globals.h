/***********************************File Header ***************************
  File Name        : oamscfg_globals.h
Purpose          : This file contains functions definitions for CFG
global variables
Project          :  BSC OAM
Subsystem        : Oams
Author           :  Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#ifndef __OAMCFG_GLOBALS_H_
#define __OAMCFG_GLOBALS_H_


I_U8 gNoLinkActivation;

I_S32 gSrcId;           /* SrcId for the CFG */
void *gCfgMsgBuf;       /* Message Pointer for the received message */
I_S32 gRecvMsgSize;  /* received message size */

I_Bool gCellLockDisProcForBssLock;
I_Bool gCellUnLockEnableProcForBssUnLock;
BssTableApi gDbBssTableApiStorage;
I_Bool gAinterfaceUPDownFlag = FALSE;


hist *gHistBufPtr;
hist *gHistRunPtr;
I_S32 gLogFlag;
FILE *gErrFname;

/*BssTableApi gDbBssTableApiStorage;*/
I_Bool gFirstBSSTableStorageUpdation=FALSE;
I_Bool gPsUnlockCellsProgressFlgForBSS = FALSE;

I_U32 gCellEnableSent ;
I_U32 gCellDisableSent;

/*Changes PCU R2.5 Aricent -- START*/
I_U32 gBssSubState;
I_Bool gGbUnlockReqSent;
/*Changes PCU R2.5 Aricent -- END*/

MgsWtForRsp gMgsWaitForRspFlg= MGS_NO_WAIT;

void* gStoredMsgBufPtr;
void* gMlpppStoredMsgBufPtr;
I_U32  gTimerId;
I_U32 gCmTrasId;
Params gThreadParams;

I_U8 gMgsSmmTsiRspFlag;
I_U8 gMgsSmmDspBootFlag;
DSmmMgsuDriverInitStatus *gStoredTsiDriverStatusMsg;
DSmmMgsBootMsg           *gStoredDspBootMsg;

timer_t     bpmTimerId;  /* Mantis # 2269 */ 

I_Bool     gSSAReceived;  /* Mantis # 2284 */ 
I_U32     gAifMsgSentToGrhm;  /* Mantis # 2768 */ 



/*********************/
/* Change For CS2.2 : Start */
#if 0
#define NUM_OF_PTRX_OBJECT_INSTANCES 18
PtrxDataStruct gPtrxData[NUM_OF_PTRX_OBJECT_INSTANCES];

#define NUM_OF_CELL_OBJECT_INSTANCES 18
CellDataStruct gCellData[NUM_OF_CELL_OBJECT_INSTANCES];

#define NUM_OF_E1_OBJECT_INSTANCES 40
#define NUM_OF_E1_TS_OBJECT_INSTANCES 32

E1TimeslotDataStruct gE1TimeslotData[NUM_OF_E1_OBJECT_INSTANCES][NUM_OF_E1_TS_OBJECT_INSTANCES];



E1DataStruct  gE1Data [NUM_OF_E1_OBJECT_INSTANCES];
#endif

PtrxDataStruct gPtrxData[CFG_MAX_NUM_TRX + 1];
CellDataStruct gCellData[CFG_MAX_NUM_CELLS];
/*Changes PCU R2.5 Aricent -- START*/
NsvcDataStruct gNsvcData[OAMS_CFG_MAX_NUM_NSVCS + 1];
/*Changes PCU R2.5 Aricent -- END*/ 
E1TimeslotDataStruct gE1TimeslotData[CFG_MAX_NUM_E1][CFG_MAX_NUM_E1_TS];
E1DataStruct  gE1Data[CFG_MAX_NUM_E1]; 
/*BB, Start , CS4.0 , Clock Source Configuration */
clkSrcCfgData gclkSrcCfgData;
/*BB, End , CS4.0 , Clock Source Configuration */
DspDataStruct gDspData[MAX_NUM_DSP_TOTAL];

I_U32   gSentAddBicReqAtInitNum;
I_Bool   gMgsOprSts;
I_U32   gMaxCellsNum;

/* Change For CS2.2 : End */

cfgStateEnum gCfgState;  /* cfg State varable */

I_U32 gMsgSentForE1Num;
I_U32 gMsgSentForE1TSNum;

objectState gBssState;
I_U32 gAvailReleaseRspFlag;  /*Added for CS3.0 */
I_U8  gBssNcc;          /* Added for CS3.0 */
/* Fixed Mantis #5384 : Start */
I_U32 gLacOfRcvReq;   /* This variable store the value of Lac received in SET request on CellPerTable */
I_U32 gCellIdOfRcvReq;   /* This variable store the value of Lac received in SET request on CellPerTable */
/* Fixed Mantis #5384 : End */
/*BSC CS4.0: Alarm Handling Changes starts*/
I_PVoid gCfgAlarmBuf;
I_PVoid gCfgActAlarmBuf;
I_U32 gSwActStatus = SW_NO_LAST_ACTION;
/*BSC CS4.0 Alarm Handling Changes ends*/
/*CS4.0 HA Stack changes : Start */
//stkObjectStruct gStackObject; 
I_U32 gStackStatus;
I_U32 gLinkMsgSentForBss;
I_U32 gReqSentToScm;
I_Bool gIsAllLinkUnlockReqd;
I_U32 gLinkLockMsgSentForBss;
I_Bool gIsAllLinkLockReqd;
/*CS4.0 HA Stack changes : End */

/*BSC CS4.0 HA Changes Starts*/
I_U32 gCurrentCardState;
I_U32 gNextCardState;
I_Bool gIsTimerRunning;
I_U32   gSentAddTrxReqAtInitNum;
sSystemCardInfo *gSystemDetails = NULL;
/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
sCloudCardInfo *gCloudCardInfo = NULL;
/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
DEFINE_MUTEX;
I_U8 gMySlotId;
I_U8 gPeerSlotId;
I_U8 gMyFrameId;
I_U32 gFirstEicAvailResp = FALSE;
I_U32 updateEicDetail = FALSE;
I_U32 gLinkMsgSentForE1;

/*BSC CS4.0 HA Changes Ends*/

/*BSC CS4.0 MLPPP Changes Starts*/
I_U32 gCurrentConnectivityMode;
I_U32 gIsListCreated;
I_U32 gMlpppLinkStatus;
MccLinkResourceTableApi *gMccLinkResourcePtr;
I_U32 gMccOutCount;
I_U16 gMccOutSize;
/*BSC CS4.0 MLPPP Changes Ends*/

/*BSC R2.0 Changes Starts*/
sDspObjInfo gDspInfo[MAX_DSP];
I_U32 gCfgAlarmIdRcvd;
I_U32 updateDspDetail = FALSE;
I_U32 gFirstDspAvailResp = FALSE;
OamsCfgOilSwActReq gSwActBuff;
I_U32 gSendSwActReq;
I_U32 gSwActReqSent;
I_U32 gTrunkPortStsReqSent;
I_U32 gEnabledEicSlotId;
/*BSC R2.0 Changes Ends*/

/* Change for R2.2 */
BtsDataStruct gBtsData[CFG_MAX_NUM_BTS + 1];

/* R2.4 changes */
I_U32  gCbsTimerId;
I_U32  breakRespAwaited;

CbsRespTimer cbsRespTimer[MAX_CBS_SERVER];
CbsRepeatTimer cbsRepeatTimer[MAX_CBS_SERVER];

/*Fix for MantisId 12905 */
I_U8 gDspBootInfoSent[MAX_DSP];
/*Fix for MantisId 12905 */

I_U32 gCfgStandbyToActive;
I_U32 gCfgStandbySlotId;  

I_U32 gSetNeIpRcvd;
I_U32 gSetOmcIpReqSent;
I_U32 gdummyIndexRNATbl; /* added For KPI PHASE -II implementation */
I_U32 gdummyIndexDataATbl; /* added For KPI PSCELL 150implementation */
/* Changes For E1-T1*/
I_U32 gBscTrunkType;
/*BSC-R2.5.5 Diagnostic Changes Start*/
I_U32 gCfgInitDiagLibSucc;
DiagDataStruct gCfgDiagData;
I_U32 gCfgDiagBpmRespTimerId; 
I_U32 gCfgDiagIntervalTimerId; 
I_U32 gCfgDiagTimerRunning; 
/*BSC-R2.5.5 Diagnostic Changes End*/

/*Mantis Fix: 0015398 start*/
AipLinkAlarmData gAipLinkAlarmData[8];
AipLinkSetAlarmData gAipLinkSetAlarmData;
I_U8 gAipPauseRcvd;
I_U8 gAipResumeRcvd;
I_U8 gAipSSARcvd;
I_U8 gAipSSPRcvd;
I_U32 gAipResumeRcvdPc;
/*Mantis Fix: 0015398 end*/
I_U32 gCfgStandbyToActiveforCbsh;/*changes for matis 16678 */
I_U8 gGbTransportType;
I_U32 gUnlockReqFlag = FALSE; //R2.9 merge 14 JUNE 2016 Gaurav Sinha
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
I_U8 gSwicthoverCloudTrigger=0;
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
/*Merger for Mantis #31470*/
I_U32 gNseLockUnlockProc=I_FALSE;
NseiDataStruct gNseiData;
/*Merger for Mantis #31470*/
//Mantis 31749
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
I_U8 gCardPlatformType=0;
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
//Mantis 31749
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
//gStructAspStatus gStructAspStatusVar[2]={0};
StructAspStatus gStructAspStatusVar[2]={0};
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/

#endif /*__OAMCFG_GLOBALS_H_ */

/********************************* Change History ***************************
  Release     Patch       Author         Description

 ************************************** End *********************************/

