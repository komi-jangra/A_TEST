/***********************************File Header ***************************
  File Name        : oamscfg_externs.h
Purpose          : This file contains functions definitions for CFG
Extern global variables
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

/* Extern global variables */
#ifndef __OAMSCFG_EXTERNS_H_
#define __OAMSCFG_EXTERNS_H_
extern I_S32 gSrcId;      /* SrcId for the CFG */
extern void *gCfgMsgBuf;   /* Message Pointer for the received message */
extern I_S32 gRecvMsgSize;  /* received message size */
extern I_U32 gSwActStatus; /* Sw Activation status */

extern I_Bool gCellLockDisProcForBssLock;
extern I_Bool  gCellUnLockEnableProcForBssUnLock;
extern BssTableApi gDbBssTableApiStorage;
extern I_Bool  gAinterfaceUPDownFlag ;


extern hist *gHistBufPtr;
extern hist *gHistRunPtr;
extern I_S32 gLogFlag;
extern FILE *gErrFname;

extern I_U32 gCellEnableSent ;
extern I_U32 gCellDisableSent;
extern void* gStoredMsgBufPtr;
extern void* gMlpppStoredMsgBufPtr;
/*Changes PCU R2.5 Aricent -- START*/
extern I_U32 gBssSubState;
extern I_Bool gGbUnlockReqSent;
/*Changes PCU R2.5 Aricent --END*/
extern MgsWtForRsp gMgsWaitForRspFlg;
extern I_U8 gMgsSmmTsiRspFlag;
extern I_U8 gMgsSmmDspBootFlag;
extern DSmmMgsuDriverInitStatus * gStoredTsiDriverStatusMsg;
extern  DSmmMgsBootMsg * gStoredDspBootMsg;
extern I_U32 gTimerId;
extern I_U32 gCmTrasId;
extern Params gThreadParams;
extern objectState gBssState ;
extern I_U32 gMsgSentForE1Num;
extern I_U32 gMsgSentForE1TSNum;
extern  timer_t     bpmTimerId;  /* Mantis # 2269 */ 
extern  I_Bool     gSSAReceived;  /* Mantis # 2284 */ 
extern  I_U32     gAifMsgSentToGrhm;  /* Mantis # 2768 */ 
extern I_PVoid gCfgAlarmBuf;
extern I_PVoid gCfgActAlarmBuf;

/******BSC CS4.0 HA Changes Starts**********/
extern I_U32 gCurrentCardState;
extern I_U32 gNextCardState;
extern I_Bool gIsTimerRunning;
/******BSC CS4.0 HA Changes Ends**********/
/*********************/
typedef enum 

{

   CFG_BPM_INIT,
   CFG_INIT,
   CFG_INIT_TSI,
   CFG_BPM_SW_QUERY,
   CFG_READY,
   CFG_STANDBY
}cfgStateEnum;

typedef enum{
CFG_REJECT, 	/* rejects the incoming signal */
CFG_NOSIG, 		/* accept the request, update the DB and no signalling */
CFG_DOSIG     /* accept the request, update the DB and further signalling */
}CfgActionType;

extern I_U32 gAvailReleaseRspFlag;  /*Added for CS3.0 */
extern I_U8 gBssNcc;		    /* Added for CS3.0 */

extern cfgStateEnum gCfgState;  /* cfg State varable */

/* Change For CS2.2 : Start */
#if 0
#define NUM_OF_PTRX_OBJECT_INSTANCES 18
extern PtrxDataStruct gPtrxData[NUM_OF_PTRX_OBJECT_INSTANCES];


#define NUM_OF_CELL_OBJECT_INSTANCES 18
extern CellDataStruct gCellData[NUM_OF_CELL_OBJECT_INSTANCES];

#define NUM_OF_E1_OBJECT_INSTANCES 40
#define NUM_OF_E1_TS_OBJECT_INSTANCES 32

extern E1TimeslotDataStruct gE1TimeslotData[NUM_OF_E1_OBJECT_INSTANCES][NUM_OF_E1_TS_OBJECT_INSTANCES];



extern E1DataStruct  gE1Data [NUM_OF_E1_OBJECT_INSTANCES];
#endif

extern PtrxDataStruct gPtrxData[CFG_MAX_NUM_TRX+1];
extern CellDataStruct gCellData[CFG_MAX_NUM_CELLS];
/*Changes PCU R2.5 Aricent -- START*/
extern NsvcDataStruct gNsvcData[OAMS_CFG_MAX_NUM_NSVCS+1];
/*Changes PCU R2.5 Aricent -- END*/
extern E1DataStruct  gE1Data[CFG_MAX_NUM_E1]; 
extern E1TimeslotDataStruct gE1TimeslotData[CFG_MAX_NUM_E1][CFG_MAX_NUM_E1_TS];

extern I_U32	gSentAddBicReqAtInitNum;
extern I_Bool	gMgsOprSts;
extern I_U32	gMaxCellsNum;
/* Change For CS2.2 : End */
/* Fixed Mantis #5384 : Start */
extern I_U32 gLacOfRcvReq;	/* This variable store the value of Lac received in SET request on CellPerTable */
extern I_U32 gCellIdOfRcvReq;	/* This variable store the value of Lac received in SET request on CellPerTable */
/* Fixed Mantis #5384 : End */

/*BB, Start , CS40 , Clock Source Configuratio */
extern clkSrcCfgData gclkSrcCfgData;
/*BB, End , CS40 , Clock Source Configuratio */

/*CS4.0 HA Stack changes : Start */
extern I_U32 gStackStatus;
extern I_U32 gLinkMsgSentForBss;
extern I_U32	gSentAddTrxReqAtInitNum;
extern sSystemCardInfo *gSystemDetails;
/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
extern sCloudCardInfo *gCloudCardInfo;
/*1U CLOUD BSC NEW INVENTORY CHNAGES 24-MAY-2016 GAURAV SINHA*/
DECLARE_MUTEX;
extern I_U8 gMySlotId;
extern I_U8 gPeerSlotId;
extern I_U8 gMyFrameId;
extern I_U32 gFirstEicAvailResp;
extern I_U32 updateEicDetail;
extern I_Bool gIsAllLinkUnlockReqd;
extern I_U32 gLinkLockMsgSentForBss;
extern I_Bool gIsAllLinkLockReqd;
extern I_U32 gLinkMsgSentForE1;
/*CS4.0 HA Stack changes : End */
/*BSC CS4.0 MLPPP Changes Starts*/
extern I_U32 gCurrentConnectivityMode;
extern I_U32 gMlpppLinkStatus;
extern MccLinkResourceTableApi *gMccLinkResourcePtr;
extern I_U32 gMccOutCount;
extern I_U16 gMccOutSize;
extern I_U32 gIsListCreated;
extern I_U32 gReqSentToScm;

/*BSC CS4.0 MLPPP Changes Ends*/

/*BSC R2.0 Changes Starts*/
extern sDspObjInfo gDspInfo[MAX_DSP];
extern I_U32 gCfgAlarmIdRcvd;
extern I_U32 updateDspDetail;
extern I_U32 gFirstDspAvailResp ;
extern OamsCfgOilSwActReq gSwActBuff;
extern I_U32 gSendSwActReq;
extern I_U32 gSwActReqSent;
extern I_U32 gTrunkPortStsReqSent;
extern I_U32 gEnabledEicSlotId;
/*BSC R2.0 Changes Ends*/

 /* Changes For R2.2  */
extern BtsDataStruct gBtsData[CFG_MAX_NUM_BTS+1];
extern DspDataStruct gDspData[MAX_NUM_DSP_TOTAL];

/* R2.4 changes */
extern I_U32 gCbsTimerId;
extern I_U32 breakRespAwaited;
extern CbsRespTimer cbsRespTimer[MAX_CBS_SERVER];
extern CbsRepeatTimer cbsRepeatTimer[MAX_CBS_SERVER];

/*Fix for MantisId 12905 */
extern I_U8 gDspBootInfoSent[MAX_DSP];
/*Fix for MantisId 12905 */

extern I_U32 gCfgStandbyToActive;
extern I_U32 gCfgStandbySlotId;

extern I_U32 gSetNeIpRcvd;
extern I_U32 gSetOmcIpReqSent;
extern I_U32 gdummyIndexRNATbl;
extern I_U32 gdummyIndexDataATbl;
/* Changes For E1-T1*/
extern I_U32 gBscTrunkType;

/*BSC-R2.5.5 Diagnostic Changes Start*/
extern I_U32 gCfgInitDiagLibSucc;
extern DiagDataStruct gCfgDiagData;
extern I_U32 gCfgDiagBpmRespTimerId; 
extern I_U32 gCfgDiagIntervalTimerId; 
extern I_U32 gCfgDiagTimerRunning;
extern I_U32 * gCfgRepCnt;
/*BSC-R2.5.5 Diagnostic Changes End*/

/*Mantis Fix: 0015398 start*/
extern AipLinkAlarmData gAipLinkAlarmData[8];
extern AipLinkSetAlarmData gAipLinkSetAlarmData;
extern I_U8 gAipPauseRcvd;
extern I_U8 gAipResumeRcvd;
extern I_U8 gAipSSARcvd;
extern I_U8 gAipSSPRcvd;
extern I_U32 gAipResumeRcvdPc;
extern I_U8 gGbTransportType;
/*Mantis Fix: 0015398 end*/
I_U32 gCfgStandbyToActiveforCbsh;/*changes for matis 16678 */
extern I_U32 gUnlockReqFlag;  /*changes for mantis 30968 Merged R2.9 14 JUNE 2016 Gaurav Sinha*/
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
extern I_U8 gSwicthoverCloudTrigger;
/*Changes for CLOUD-BSC-HA 12-Feb-2016 Gaurav Sinha*/
/*Merger for issue #0031470*/
extern I_U32 gNseLockUnlockProc;
extern NseiDataStruct gNseiData;
/*Merger for issue #0031470*/
//Mantis 31749
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
extern I_U8 gCardPlatformType;
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
extern StructAspStatus gStructAspStatusVar[2];
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
//Mantis 31749

/************************************************************ Change History ***
  Release     Patch       Author         Description

 ********************************************************************** End ***/

#endif /*__OAMCFG_EXTERNS_H_*/
