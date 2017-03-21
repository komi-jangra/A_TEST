/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oams_bich_msgstruct.h
 PURPOSE           :  Contains BICHandler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  Aricent
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMS_BICH_MSGSTRUCT_H
#define __OAMS_BICH_MSGSTRUCT_H

#define MAX_NUM_OF_CHILD_TRX                  2U

typedef enum 
{
  eIdle,
  eLockedDisabled,
  eUnlockedDisabled,
  eUnlockedEnabled,
  eWaitForLinkEstab,
  eWaitForChildTrxDisc,
  eSameState,
  eStarState,
  eInvalidState, 
  eStateCount //Keep it last as it givies the count
} state__e;

typedef enum 
{
  eNoProc,
  eAddBtsProc,
  eDelBtsProc,
  eLockProc,
  eUnlockProc,
  eLapdDownProc,
  eLapdLinkEstabProc,
  eAddChildTrxProc,
  eDelChildTrxProc,
  eResetBtsProc,
  eProcCount //Keep it last as it givies the count
} proc__e;

typedef enum 
{
  eNoSrc,
  eInternal,
  eDbs
} eSrc__e;

/* timerList__t
** This list has the timer which should be started by TAU Model before making the state transition
** n -> no of timers to be started , if *zero* then no timer to be started 
*/
typedef struct 
{
  I_U8 n;
  I_U8 timer[1];
} timerList__t; 

typedef struct 
{
  eSrc__e  eSrc; //Source incase of failure
  I_U32    eCode; //Success(0) incase of OK and error incase of failure
} result__t;

typedef struct 
{
  state__e     nextState;     //Indicates the next state which should be moved by the TAU Model
  timerList__t timersToStart; //Indicates the timer to be started before making state change. n=0, no timer to start 
  I_Bool       isProcDone;    //Indicates to TAU Model that procedure is done , so that it data can be reset  
  result__t    result;        //This will store the result of the procedure and error code incase of failure
} procResult__t;

typedef struct 
{
  proc__e       ActiveProc;  
  procResult__t procResult;
} procState__t;

typedef struct
{
  I_U32 trxId;
  I_U32 oprState;  
} ChildTrxInfo__t;

typedef struct 
{
  ChildTrxInfo__t ChildTrxInfo[MAX_NUM_OF_CHILD_TRX]; /* 08-09-09::14:01 , Maximum Count of Child Trx is 2 in R2 BTS or BIC */
} ChildTrxCntxt__t;

/* R22 end , 08-09-09::14:03 */   

typedef struct
{
   OptFlag                         isBicSwDesInActiveSwPresent;
   I_U32                           e1Id;
   I_U32                           e1Ts;
   BicIdentifier                   bicId;
   BicTei                         bicTei;
   BicIdentifier                   parentBicId;
   I_U8                            upStreamPort;/*parent Bic DS Port*/
   SwDes                           swDes;
   InactiveSwDes                   inactiveSwDes; 
/* R22 start , 08-09-09::14:03 */    
   state__e                        activeState;
   I_PVoid                         rcvMsgPtr; //rcvd message pointer
   I_PVoid                         sendMsgPtr; //Send message pointer
   I_U32                           sendMsgSize; //Send message pointer
   I_U32                           msgType; //rcvd message type
   I_U32                           msgSender; //rcvd message sender   
   SysBtsType                      btsType;   
   procState__t                    actProcState;    
   ChildTrxCntxt__t                childTrxCntxt; 
   I_U32                           adminState;
   I_U32                           btsLapdOprState;
   I_S32                           InstNr; 
/* R22 end , 08-09-09::14:03 */   
   /* PCU REL 2.5 CHANGES BEGIN*/
   I_U32                           IpOprState;  
   BtsIpAddrV4                     IpAdd;
   I_U16                           UdpPort;
   /* PCU REL 2.5 CHANGES END*/
   /* R2.8 Changes Start */
   I_U8                            numberOfTrx;
   I_U8                            localSwitchingSupport;
   I_U8                            maxStepsSize;
   I_U8                            clockSource;
   /*R2.8 Changes End */
}OamsBichContext;

   /* changes for HA ABIS BSC-R2.5.5 Start*/
typedef struct
{
   OptFlag                         isBicSwDesInActiveSwPresent;
   I_U32                           e1Id;
   I_U32                           e1Ts;
   BicIdentifier                   bicId;
   BicTei                          bicTei;
   BicIdentifier                   parentBicId;
   I_U8                            upStreamPort;
   SwDes                           swDes;
   InactiveSwDes                   inactiveSwDes; 
   state__e                        activeState;
   I_U32                           btsType;   
   I_U32                           adminState;
   I_U32                           btsLapdOprState;
   BtsIpAddrV4                     IpAdd;
   I_U16                           UdpPort;
   /* R2.9 changes starts */
   state__e                        nextState;
   proc__e                         activeProc;    
   ChildTrxCntxt__t                childTrxCntxt; 
  /* R2.9 changes ends */ 
}OamsBichStandbyCardContext;
 /* changes for HA ABIS BSC-R2.5.5 End*/


I_Void BICH_INPUT(I_PU8 msgName, state__e stateName, I_PU8 senderName,OamsBichContext *OamsBichContextPtr);
state__e BICH_NEXTSTATE(I_Void);
I_Void logPrintBichContextFromTau(OamsBichContext *OamsBichContextPtr);
I_Void logPrintStateNameFromTau(state__e stateNr);
/* State Machine handling functions */
//*********************IDLE START*************
I_Void handleIdleStateMsgs(I_Void);
//*********************IDLE END  *************

//*********************WaitForLinkEstab START*************
I_Void handleWaitForLinkEstabStateMsgs(I_Void);
//*********************WaitForLinkEstab END*************

//*********************LockedDisabled START*************
I_Void handleLockedDisabledStateMsgs(I_Void);
//*********************LockedDisabled END  *************


//*********************UnlockedDisabled START*************
I_Void handleUnlockedDisabledStateMsgs(I_Void);
//*********************UnlockedDisabled END  *************

//*********************UnlockedEnabled START*************
I_Void handleUnlockedEnabledStateMsgs (I_Void);
//*********************UnlockedEnabled END  *************

//*********************WaitForChildTrxDisc START*************
I_Void handleWaitForChildTrxDiscStateMsgs (I_Void);
//*********************WaitForChildTrxDisc END  *************

//*********************(Start -*) START*************
I_Void handleStarStateMsgs(I_Void);
I_Void handleCardStateChangeNotification(OamsBichContext *OamsBichContextPtr);
//*********************(Start -*) End*************

#define SET_TAU_INST_NR(bicContext) do {\
 SDL_PId pid = (SDL_PId)SDL_SELF;\
 (bicContext).InstNr = pid.LocalPId->InstNr;\
} while (0)
#define GET_TAU_INST_NR()         (gOamsBichContextPtr->InstNr)

#endif   /* __OAMS_BICH_MSGSTRUCT_H */
