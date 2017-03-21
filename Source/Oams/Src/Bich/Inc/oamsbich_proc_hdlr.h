/** ts=3 ******************************************************** File Header **
 FILE NAME         :  oamsbich_proc_hdlr.h
 PURPOSE           :  Contains BICHandler Data struct
 PROJECT           :  BSS
 SUBSYSTEM         :  System
 AUTHOR            :  VNL/BB
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSBICH_PROC_HDLR_H
#define __OAMSBICH_PROC_HDLR_H

#define SET_BICH_CNTX_PTR(OamsBichContextPtr) (gOamsBichContextPtr = OamsBichContextPtr)
#define SET_NEXT_STATE(newState)              (gOamsBichContextPtr->actProcState.procResult.nextState = newState) 
#define GET_NEXT_STATE()                      (gOamsBichContextPtr->actProcState.procResult.nextState) 
#define GET_ACTIVE_STATE()                    (gOamsBichContextPtr->activeState) 
#define GET_MSG_SENDER()                      (gOamsBichContextPtr->msgSender)
#define GET_MSG_TYPE()                        (gOamsBichContextPtr->msgType)
#define GET_BTS_ID()                          (gOamsBichContextPtr->bicId)
#define SET_BTS_ID(btsId)                     (gOamsBichContextPtr->bicId = btsId)
#define GET_BTS_TYPE()                        (gOamsBichContextPtr->btsType)
#define SET_BTS_TYPE(bType)                   (gOamsBichContextPtr->btsType = bType)
#define GET_BTS_TRUNK()                       (gOamsBichContextPtr->e1Id)
#define SET_BTS_TRUNK(trunkId)                (gOamsBichContextPtr->e1Id = trunkId)
#define GET_BTS_TRUNK_TS()                    (gOamsBichContextPtr->e1Ts)
#define SET_BTS_TRUNK_TS(trunkTs)             (gOamsBichContextPtr->e1Ts = trunkTs)
#define GET_RCVD_MSG_PTR()                    (gOamsBichContextPtr->rcvMsgPtr)
#define GET_SEND_MSG_PTR()                    (gOamsBichContextPtr->sendMsgPtr)
#define GET_SEND_MSG_SIZE()                   (gOamsBichContextPtr->sendMsgSize)
#define GET_PROC_RESULT_SRC()                 (gOamsBichContextPtr->actProcState.procResult.result.eSrc)
#define GET_PROC_RESULT_CODE()                (gOamsBichContextPtr->actProcState.procResult.result.eCode)
#define SET_PROC_DONE(isDone)                 (gOamsBichContextPtr->actProcState.procResult.isProcDone = isDone)
#define GET_PROC_DONE_STATUS(isDone)          (gOamsBichContextPtr->actProcState.procResult.isProcDone)
#define GET_ACTIVE_PROC()                     (gOamsBichContextPtr->actProcState.ActiveProc) 
#define SET_ACTIVE_PROC(ActProc)              (gOamsBichContextPtr->actProcState.ActiveProc = ActProc) 
#define IS_ANY_PROC_ONGOING()                 (gOamsBichContextPtr->actProcState.ActiveProc != eNoProc) 
#define GET_CHILD_TRX_ID(pos)                 (gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].trxId)
#define GET_CHILD_TRX_OPR_STATE(pos)          (gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].oprState)
#define SET_CHILD_TRX_OPR_STATE(pos,opr)      (gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].oprState=opr)
#define ALLOC_IPC_MSG_BUF(sz)                 (gOamsBichContextPtr->sendMsgSize = sz,\
                                               gOamsBichContextPtr->sendMsgPtr = AlocMsgBuf(sz))
#define GET_BTS_ADMIN_STATE()                 (gOamsBichContextPtr->adminState)
#define SET_BTS_ADMIN_STATE(admState)         (gOamsBichContextPtr->adminState = admState)
#define GET_BTS_TEI()                         (gOamsBichContextPtr->bicTei)
#define SET_BTS_TEI(btsTei)                   (gOamsBichContextPtr->bicTei = btsTei)
#define GET_BTS_MAX_STEPS_SIZE()              (gOamsBichContextPtr->maxStepsSize)
#define GET_BTS_CLOCK_SOURCE()                (gOamsBichContextPtr->clockSource)
#define SET_BTS_MAX_STEPS_SIZE(maxStpSz)      (gOamsBichContextPtr->maxStepsSize = maxStpSz)
#define SET_BTS_CLOCK_SOURCE(clkSrc)          (gOamsBichContextPtr->clockSource = clkSrc)
/*Added for R3 BTS starts*/
/*#define LSB_MASK                              0X000000FF 
#define SET_BTS_IP(btsIp){\
    gOamsBichContextPtr->IpAdd.AAA = ((btsIp >> 24) & (LSB_MASK));\
    gOamsBichContextPtr->IpAdd.BBB = ((btsIp >> 16) & (LSB_MASK));\
    gOamsBichContextPtr->IpAdd.CCC = ((btsIp >> 8) & (LSB_MASK));\
    gOamsBichContextPtr->IpAdd.DDD = (btsIp) & (LSB_MASK);\
}*/
/*Added for R3 BTS ends*/    
#define SET_BTS_LAPD_OPR_STATE(oprState)      (gOamsBichContextPtr->btsLapdOprState = oprState)
#define GET_BTS_LAPD_OPR_STATE()              (gOamsBichContextPtr->btsLapdOprState)
/* PCU REL 2.5 CHANGES START*/
#define SET_IP_OPR_STATE(oprState)            (gOamsBichContextPtr->IpOprState = oprState)
#define GET_IP_OPR_STATE()                    (gOamsBichContextPtr->IpOprState)
/* PCU REL 2.5 CHANGES END*/

#define GET_MSG_RCVR()                        ((SysHdr *)gOamsBichContextPtr->rcvMsgPtr)->src.entity

#define GET_STATE_NAME(stateNr)               (((stateNr) >= eStateCount) ? mapStateNumToStateName[eInvalidState] :\
                                                mapStateNumToStateName[(stateNr)])

#define GET_PROC_NAME(procNr)                 (((procNr) >= eProcCount) ? mapProcNumToProcName[eNoProc] :\
                                                mapProcNumToProcName[(procNr)])

#define SET_ACTIVE_STATE(actState)            do {\
    if ((eStarState != actState ) && (eSameState != actState ) ) {\
      gOamsBichContextPtr->activeState = (actState);\
    }\
   } while (0)

#define FREE_IPC_MSG_BUF()                  do {\
     if ( gOamsBichContextPtr->rcvMsgPtr )  DalocMsgBuf( gOamsBichContextPtr->rcvMsgPtr ); \
     gOamsBichContextPtr->sendMsgSize = 0;\
     gOamsBichContextPtr->sendMsgPtr  = NULL;\
   }while (0)

#define ADD_CHILD_TRX(pos,_trxId)             do {\
     gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].trxId = _trxId;\
     gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].oprState = DISABLED;\
   } while (0)  

#define DEL_CHILD_TRX(pos)                    do {\
     gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].trxId = 0;\
     gOamsBichContextPtr->childTrxCntxt.ChildTrxInfo[pos].oprState = DISABLED;\
   } while (0)  

#define SET_MSG_TYPE_N_MSG_SENDER()            do {\
     gOamsBichContextPtr->msgType   = ((SysHdr *)gOamsBichContextPtr->rcvMsgPtr)->msgType;\
     gOamsBichContextPtr->msgSender = ((SysHdr *)gOamsBichContextPtr->rcvMsgPtr)->dest.entity;\
   } while (0)

#define RESET_ACTIVE_PROC_STATE()             do {\
     memset(&gOamsBichContextPtr->actProcState,0x00,sizeof (procState__t));\
   } while (0)

#define SET_PROC_RESULT(Src,Rslt)              do {\
     gOamsBichContextPtr->actProcState.procResult.result.eSrc  = Src;\
     gOamsBichContextPtr->actProcState.procResult.result.eCode = Rslt;\
   }while (0)

#define OUTPUT_MSG(sendMsgType,rcvrEntId)   outputMsg(sendMsgType, rcvrEntId, #sendMsgType, #rcvrEntId)

#define FILL_ABIS_HDR_FOR_BIC(msgPtr)  do {\
      msgPtr->placementInd              = PLACEMENT_IND;\
      msgPtr->seqNum                    = SEQUENCE_NUM;\
      msgPtr->objClass                  = (GET_BTS_TYPE() == BIC ? OBJ_CLASS_BIC : OBJ_CLASS_BM) ;\
      msgPtr->objInstance.bicObjInst[0] = OBJECT_INST_OCTET1;\
      msgPtr->objInstance.bicObjInst[1] = OBJECT_INST_OCTET2;\
      msgPtr->objInstance.bicObjInst[2] = OBJECT_INST_OCTET3;\
   }while (0)

#define FILL_ABIS_HDR_FOR_BTS(msgPtr)  do {\
      msgPtr->placementInd              = PLACEMENT_IND;\
      msgPtr->seqNum                    = SEQUENCE_NUM;\
      msgPtr->objClass                  = (GET_BTS_TYPE() == BIC ? OBJ_CLASS_BIC : OBJ_CLASS_BM) ;\
      msgPtr->objInstance.btsObjInst[0] = OBJECT_INST_OCTET1;\
      msgPtr->objInstance.btsObjInst[1] = OBJECT_INST_OCTET2;\
      msgPtr->objInstance.btsObjInst[2] = OBJECT_INST_OCTET3;\
   }while (0)

I_Void resetBichContext(I_Void);
I_U32 getOprState(I_Void);
I_Void outputMsg(I_U32 sendMsgType, I_U32 rcvrEntId, I_PU8 msgName, I_PU8 rcvrName);
I_Void updBichContxtFromAddBicReq(I_Void);
I_Void addBtsInStatusTable(I_Void);
I_Void fillAndSendAddBtsResp(I_Void);
state__e findNextStateBasedOnAdminAndOprState(I_Void);
I_Void handleAddBtsProc(I_Void);
I_U32  getProcResult(I_Void);
/* PCU REL 2.5 CHANGES BEGIN */
I_U32  getIpAddr(I_Void);
/* Mantis 14848 --Start*/
 I_Void getIpAddrAsString(I_S8 *ipAddr);
/* Mantis 14848 --End*/
/* PCU REL 2.5 CHANGES END */

/************************************Procedure Speicfic ProtoType *********/
I_Void delBtsFromStatusTable(I_Void);
I_Void handleAbisLinkEstabProc(I_Void);
I_Void handleAbisLinkDownProc(I_Void);
I_Void handleLockProc(I_Void);
I_Void fillAndSendDelBtsResp(I_Void);
I_Void handleUnlockProc(I_Void);
I_Void handleAddChildTrxProc(I_Void);
I_Void handleResetBtsProc(I_Void);
I_Void handleDelChildTrxProc(I_Void);
I_Void sendBicParentNotAvail(I_U32 bicId);
I_Void delTsNodeFromAbisChain(OamsBichContext *rcvPtr);
I_Void fillAndSendBichCfgAlarmInd(I_U32 alarmId, I_U32 alarmLevel, I_U8 alarmString[]);
/* PCU REL 2.5 CHANGES BEGIN */
I_Void fillAndSendDelBtsIpToTB(I_Void);
I_Void fillAndSendAddBtsIpToTB(I_Void);
I_Void fillAndSendIpLinkDownToTB(I_Void);
I_Void fillAndSendIpLinkUpToTrxh(I_Void);
I_Void fillAndSendIpDownToTrxh(I_Void);
I_Void fillAndSendIpLinkDownToAbihm(I_Void);
/* PCU REL 2.5 CHANGES END */
/*R2.8 Changes Start*/
I_Void fillAndSendLapdDiscIndToTrxh(I_Void);
I_Void fillAndSendLapdDiscIndForBts(BicTei bicTei);
/*R2.8 Changes End*/
/* R2.9 changes starts */
I_Void updateBtsDataFromContext();   
/* R2.9 changes ends */
/************************************Procedure Speicfic ProtoType *********/
#endif //__OAMSBICH_PROC_HDLR_H  









