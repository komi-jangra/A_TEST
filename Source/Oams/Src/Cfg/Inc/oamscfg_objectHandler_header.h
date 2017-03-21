/***********************************File Header ***************************
  File Name        : oamscfg_objectHandler_header.h
Purpose          : This file contains object states defined for CFG
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMCFG_OBJECTHANDLER_H_
#define __OAMCFG_OBJECTHANDLER_H_

/********   objectState  ********  Start ****/

typedef enum objectState 
{
   locked,
   lockInProgress,
   unlocked,
   unlockInProgress,
   blockInProgress, /* applicable for Cell and Trx */
   unlockOrEnableInProgress, /* applicable for only cell */
   lockeOrDisableInProgress, /* applicable for only cell */
   unlockedEnabled, /* applicable for only cell */
   ShuttingDown,
   unlockedDisabled, /* applicable for only cell */  
   none,              /* Added in CS4.0 */
   connectInProgress,   /* Added in R2.2 */
   resetInProgress    /* Added in R2.9 ; Applicable for DSP */
}objectState;


typedef enum TrunkPortObject 
{
   Enabled,
   EnableInProgress,
   Disabled,
   DisableInProgress,
   Invalid

}TrunkPortObject;

/********   objectState  ********  End ****/

/******** bss State *****Start *******/
/*objectState gBssState ;*/
/******** bss State *****End  *******/

/********   gCellData ********  Start ****

  1.   Whenever new cell is added, CFG will check Availability and if it is True, then it should be allocated for the cell. CellID will be updated with the CellID of new cell. And Availlability will be set to False.
  2.   When Cell is deleted the Availability in CellData need to be updated as "True".
  3.   Whenever message is received in the cellectHandler() , it need to extract the CellID from the message and traverses the gCellData[18] instances to find out which is the instance it belong to.

  CellState -> State variable for the cell [ default : Locked ]
  Availlability ' True/False [ default : True]
  CellID'CellID [ configured Cell ID number, default: FF]
 */

typedef struct 
{
   I_U32 cellId;
   I_U32 lac; 
}Params;

typedef struct gCellDataStruct
{
   objectState  CellState;  // object state
   I_Bool   Availlability; // available or not available
   I_UL32   CellID; // Cell Identifier
   I_UL32   opState;
   I_UL32   adminState;
   I_U32      lac;
   I_Bool   reqType;
   I_Bool   isReqSentForPS; 
} CellDataStruct;


/*Changes PCU R2.5 Aricent -- START*/
typedef struct gNsvcDataStruct
{
   objectState nsvcState;
   I_Bool availability;
   I_UL32 nsvcId;
   I_Bool   reqType;
} NsvcDataStruct;

typedef struct
{
    I_Bool        isValid;
    I_Bool        isAllocated;
    I_U16         frChnId;
    I_U8          mccE1;
    I_U8          mccE1Ts;
    I_U8          cardNum;
    I_U8          mccStrmTs;
    I_U8          mccStrmId;
    I_U8          frE1;
    I_U8          frE1Ts;
}MccFrResource;

typedef enum bssSubState 
{
   initBssSubState,
   cellsLockInProgress,
   nsvcsLockInProgress,
   gbIfLockInProgress,
   aIfLockInProgress,
   aIfUnlockInProgress,
   gbIfUnlockInProgress,
   nsvcsUnlockInProgress,
   cellsUnlockInProgress,
   noneBssSubState,
}bssSubState;
/* PCU R2.5 Aricent -- END*/

/* #define NUM_OF_CELL_OBJECT_INSTANCES 18 */ /* Change For CS2.2 */
/********   gCellData ********  End ****/

/********   gPtrxData ********  Start ****
  1.   Whenever new cell is added, CFG will check Availability and if it is True, then it should be allocated for the cell. CellID will be updated with the CellID of new cell. And Availlability will be set to False.
  2.   When Cell is deleted the Availability in CellData need to be updated as "True".
  3.   Whenever message is received in the cellectHandler() , it need to extract the CellID from the message and traverses the gCellData[18] instances to find out which is the instance it belong to.

  "   PTRXObjectHandler Maintains the state machine for all the TRXes configured in the BSS. This will be achieved by having 18 instances of gPtrxData. gPtrxData struct is given below:
  ptrxState -> State variable for the PTRX [ default : Locked ]
  Availlability ' True/False [ default : True]
  PTRXID'PTRXID [ configured PTRX ID number, default: FF]

  1.   gPtrxData [] should be initialized with the corresponding [ptrxID] .
  2.   gPtrxData [] is invoked directly by indexing the with received [ptrxID].  */

typedef struct gPtrxDataStruct
{
   objectState ptrxState;  // object state
   I_UL32        CellID;
   I_UL32      PTRXID; // PTRX Identifier
} PtrxDataStruct;

/********   gPtrxData ********  End  ****/

/********   E1TimeslotObjectHandler  ********  Start  ****

  E1TimeslotObjectHandler maintains the state machine for the E1Timeslots configured in the BSS. This will be achieved by having 40*I_UL32 instances of gE1TimeslotData. gE1TimeslotData  struct is given below:
  e1TimeslotState -> State variable for the Timeslot [ default : Locked ]
  E1Number -> e1 Number for the timeslot
  e1TimeslotID' [ tsnum, default: FF]

  1.   e1TimeSlotData[][] should be initialized with the corresponding [e1][tsNum] .
  2.   e1TimeSlotData [][] is invoked directly by indexing the with received [e1][tsNum]. */
typedef struct gE1TimeslotDataStruct
{
   objectState e1TimeslotState;  // object state
   I_UL32      e1Number;
   I_UL32      e1TimeslotID; // e1Timeslot Identifier
} E1TimeslotDataStruct;

#define NUM_OF_E1_OBJECT_INSTANCES 40
#define NUM_OF_E1_TS_OBJECT_INSTANCES 32

/********   E1TimeslotObjectHandler  ********  End  ****/

/********   E1ObjectHandler  ********  Start ****
  E1ObjectHandler maintains the state machine for the E1Timeslots configured in the BSS. This will be achieved by having 40*I_UL32 instances of gE1TimeslotData. gE1TimeslotData  struct is given below:
  e1State -> State variable for the E1[ default : Locked ]
  E1Number -> e1 Number for the timeslot

  1.   gE1Data[][] should be initialized with the corresponding [e1].
  2..   gE1Data [][] is invoked directly by indexing the with received [e1].
 *******************************************************************/

typedef struct gE1DataStruct
{

   // CS 4.0 Harsh
   TrunkPortObject        trunkState;  
   I_U8                   LOS_Active;
   I_U8                   LOS_Active_In_Progress;
   I_U8                   LOS_Active_Pending;
   I_U8                   LOS_Clear_In_Progress;
   I_U8                   LOS_Clear_Pending;
   I_U8                   LOS_Frame;
   I_U8                   LOS_Signal;
   I_U8                   LOS_Signal_detect;
   // CS 4.0 Harsh

   objectState e1State;  // object state
   I_UL32      e1Number;
   I_U32 	     msgsSentForE1;

   /*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/
   I_U32        waitingForCellUnlockRespCounter;
   I_U32       e1CellLockReqSent;
   I_U32       e1CellUnlockReqSent;
   I_U32       usageType;
   /*BSC CS4.0 : Abis E1 Lock/Unlock changes Starts*/

} E1DataStruct ;


/********   E1TimeslotObjectHandler  ********  End  ****/

/********   Clock Source Object Handler  ********  Start  ****/

typedef enum clkSrcProcState{
  clkSrcCfgNone,
  clkSrcCfgOngoing
} clkSrcProcState;

typedef OamOilCfgSetClkSrcResp clkSrcCfgInfo;

typedef struct clkSrcCfgData {
  clkSrcProcState enumClkSrcProcState;
  clkSrcCfgInfo   clkSrcCfg;
  I_U16           dbIndex; 
} clkSrcCfgData;

/********   Clock Source Object Handler  ********  End    ****/
 
/********   gBtsData ********  Start ****
  1.   Whenever new bic is added, CFG will check Availability and if it is True, then it should be allocated for the bic. BTSID will be updated with the BicID of new Bic/Bts. And Availlability will be set to False.
  2.   When Bic is deleted the Availability in BtsData need to be updated as "True".
  3.   Whenever message is received in the cellectHandler() , it need to extract the BTSID from the message and traverses the gBtsData[56] instances to find out which is the instance it belong to.

  "   PTRXObjectHandler Maintains the state machine for all the TRXes configured in the BSS. This will be achieved by having 18 instances of gPtrxData. gPtrxData struct is given below:
  btsState -> State variable for the BTS [ default : Locked ]
  Availlability ' True/False [ default : True]
  BTSID'BTSID [ configured BTS ID number, default: FF]

  1.   gBtsData [] should be initialized with the corresponding [BTSID] .
  2.   gBtsData [] is invoked directly by indexing the with received [BTSID].  */

typedef struct gBtsDataStruct
{
   objectState   btsState;  // object state
   I_U32        BTSID; // BTS Identifier
   I_U32         btsType;
   objectState   connectivityState;  // object state
} BtsDataStruct;

/********   gBtsData ********  End  ****/


/********   gAipLinkAlarmData ********  Start  ****/
typedef struct AipLinkAlarmData
{
   I_U16        flag; //TRUE/FALSE 
   I_U16        linkSetId; 
   I_U16        linkId; 
   I_U32        oprState; //OOS/INS
}AipLinkAlarmData;

typedef struct AipLinkSetAlarmData
{
   I_U16        flag; //TRUE/FALSE 
   I_U16        linkSetId; 
   I_U32        oprState; //OOS/INS
}AipLinkSetAlarmData;

/********   gAipLinkAlarmData ********  End****/
/* This Struct is defined to maintain the state of dsp's. If any dsp is in any invalid state then the switchover should not be successful */
typedef struct gDspDataStruct
{
  objectState dspState;
  I_U32       dspId;
}DspDataStruct;

/*Merger for Mantis #31470*/
typedef struct
{
  objectState nseiState;
  I_U32 nsei;
}NseiDataStruct;
/*Merger for Mantis #31470*/

void cfgFrmwrkInit();
void cfgHistInit();
void cfgDbInit();
void cfgSigInit();
void cfgPanic(I_S8);
void cfgInit();
void  cfgBpmInit();
void startInitializeMGS();
void sendFetchreqBcardInfo();
void cfgObjectHandlerInit();
void  cfgStartTimer(CONST I_S8 *payLoad);
void cfgStopTimer();
void   cfgInitRadioClokTable();
void  cfgInitAinterfaceTable();
void cfgInitTrauTable();
/* Change For CS2.2 : Start */
I_Void stopMgsTimer();
I_Void startMgsTimer();
I_Void goToReadyState();
I_Void initGlobalMaxCellNumVar();
/* Change For CS2.2 : End */

/*BSC CS4.0 HA changes statrts*/
I_Void cfgCleanUpResources();
I_Void cfgCleanTransientTable();
I_Void cfgCleanGlobalData();
I_Void cfgCleanBuffer();
I_Void cfgInitAfterDbRw();
I_Void sendStateChangeReqToRm(I_S8 cardState);
I_Void sendSlotIdQueryToRm();
/*BSC CS4.0 HA changes ends*/
/*Changes PCU R 2.5 Aricent -- START */
I_Void psPerformanceCounterTableIntialization();
I_Void populateCellIndices();
/*Changes PCU R 2.5 Aricent -- END */

I_Void generateResetAfterSwitchOver();
//Mantis 31749
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
I_Void updateCardPlatformTypeInContext();
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
//Mantis 31749
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
typedef struct StructAspStatus 
{
   I_U16        localAspId; 
   objectState  gAdminState;
   I_U16        status; 
}StructAspStatus;
/*Added for Mantis #0032201 Gaurav Sinha 12-Oct-2016*/
/********************************* Change History ***************************
  Release     Patch       Author         Description

 ************************************** End *********************************/

#endif /*__OAMCFG_OBJECTHANDLER_H_*/
