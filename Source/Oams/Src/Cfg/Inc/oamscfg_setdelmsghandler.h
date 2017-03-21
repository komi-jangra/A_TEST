/***********************************File Header ***************************
  File Name        : oamscfg_setdelmsghandler.h
Purpose          : This file contains function prototypes CM
SET/DEL messages
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/


#ifndef __OAMSCFG_SETDELMSGHANDLER_H
#define __OAMSCFG_SETDELMSGHANDLER_H

#define ALLOWED 1
#define NOT_ALLOWED 0
#define LOCK LOCKED 
#define UNLOCK UNLOCKED
/*
#define ENABLED 0
#define DISABLED 1 */
#define ENABLED 1
#define DISABLED 0 

#define CM_FAILURE 0

/* Types 0f si13PbcchLocation */
#define BCCH_NORM 0
#define BCCH_EXT 1

#define BCCH_SDCCH_4 1
#define BCCCH 2

/* Types of Cell */
#define INTERNAL 0
#define EXTERNAL 1

/* Types of Cell Relation */
#define IDLE 0
#define ACTIVE 1
#define ACTIVE_IDLE 2

/* Types of default PS channel coding scheme (only used for GPRS) */
#define CS1 1
#define CS2 2
#define CS3 3
#define CS4 4
#define TLLI_BLK_CS 5

#if 0 /* CS4.0 HA Stack Changes */
/* Types of MTP3 Route Style */
#define DPC_SIO_SSN 0
#define DPC_SIO 1
#endif

/* Status of Point Code */
#define INS 0
#define OOS 1

/* Transport types */

#define  FR                             PCU_GB_TRANSPORT_TYPE_FR
#define  IP_DYNAMIC                     PCU_GB_TRANSPORT_TYPE_IP_DYNAMIC
#define  IP_STATIC                      PCU_GB_TRANSPORT_TYPE_IP_STATIC

#define PNULL NULL


/* Set Table Massage Handlers */

void setBssTableHandler();
void setCellTableHandler();
void setPtrxTableHandler();
void setE1TableHandler();
void setTimeSlotTableHandler();
void setPsCellTableHandler();
void setCsexternalCellTableHandler();
void setLaTableHandler();
void setRaTableHandler();
void setChnGrpTableHandler();
void setCsNeighCellsTableHandler();
void setArfcnListTableHandler();
void setAinterfaceStackTraceConfigTableHandler();         
void setSccpTableHandler();
void setMtp3LinksetTableHandler();
void setMtp3RouteTableHandler(); 
void setMtp3LinkSetAdminStateTableHandler();
void setMtp3LinkTableHandler(); 
void setMtp3RemotePointCodeTableHandler();
void setSccpSsnConfigTableHandler();
void setSccpCSSNConfigTableHandler();
void setGbInterfaceTableHandler();
void setNsvcTableHandler();
void setFrLinkTableHandler();
void setLepInfoTableHandler();         
void setRepInfoTableHandler();
void setSksCommonTableHandler();
void setSksLinkstartTableHandler();
void setSksGenCfgTableHandler();
void setSysOmcRegisterTableHandler();
void setCsExternalCellTableHandler();
void setPtdcConfigTableHandler();
void setAInterfaceTableHandler();
void setSccpSsnConfigTableHandlerScmAck();
void setSccpCssnConfigTableHandlerScmAck();
void setSccpCssnConfigTableHandler();
void setSccpCssnConfigTableHandler();
void setSksCommonTableHandlerScmAck();
void setSksLinkstartTableHandlerScmAck();
void setMtp3LinksetTableHandlerScmAck();
void setMtp3RouteTableHandlerScmAck();
void setMtp3LinkTableHandlerScmAck();
void setMtp3RemotePointCodeTableHandlerScmAck();
void setSksGenCfgTableHandlerScmAck();
void setSysOmcConfigTableHandler();
void setMtp3LinkTableHandlerScmAck();
void setBssapPcSsnConfigTableHandler();
void setBssapPcSsnConfigTableHandlerScmAck();
void setCsPwrCtrlTablehandler();
void setHoCtrlHandler();
void setMtp3LinkSetStsTableHandler();
void setCsPwrCtrlTableHandler();
void setHoCtrlTableHandler();
void setMtp3LinkSetStsTableHandlerScmAck();
I_Void setSwMOfferTableHandler();
I_Void setSwMNodeTableHandler();
I_Void setEicSwMOfferTableHandler();
I_Void setEicSwMNodeTableHandler();

/* Added for SW_UPGRADE for IP_BTS */
I_Void setIpBtsSwMOfferTableHandler();
I_Void setIpBtsSwMNodeTableHandler();

/* Delete Table Massage Handlers */
void delBssTableHandler();         
void delCellTableHandler();
void delPtrxTableHandler();
void delE1TableHandler();
void delTimeSlotTableHandler();
void delPsCellTableHandler();         
void delCsExternalCellTableHandler();
void delLaTableHandler();         
void delRaTableHandler();         
void delChnGrpTableHandler();         
void delCsNeighCellTableHandler();         
void delArfcnListTableHandler();      
void delAInterfaceTableHandler();
void delSccpTableHandler();
void delMtp3LinksetTableHandler();
void delMtp3RouteTableHandler(); 
void delMtp3LinkSetAdminStateTableHandler();
void delMtp3LinkTableHandler(); 
void delLinkAdminStateTableHandler(); 
void delMtp3RemotePointCodeTableHandler();
void delSccpSsnConfigTableHandler();
void delSccpCSSNConfigTableHandler();
void delGbInterfaceTableHandler();
void delNsvcTableHandler();
void delFrLinkTableHandler();
void delLepInfoTableHandler();
void delRepInfoTableHandler();
void delRlcMacConfigTableHandler();
void delSksCommonTableHandler();
void delSksLinkstartTableHandler();
void delSksGenCfgTableHandler();
void delMtp3LinksetTableHandlerScmAck();
void delMtp3RouteTableHandlerScmAck();
void delMtp3LinkTableHandlerScmAck();
void delLinkAdminStateTableHandlerScmAck();
void delMtp3RemotePointCodeTableHandlerScmAck();
void delSccpSsnConfigTableHandlerScmAck();
void delSccpCSSNConfigTableHandlerScmAck();
void delSksCommonTableHandlerScmAck();
void delSksLinkstartTableHandlerScmAck();
void delSksGenCfgTableHandlerScmAck();
void delTrauConfigTableHandler();
void delBssapPcSsnConfigTableHandler();
void delBssapPcSsnConfigTableHandlerScmAck();
void delPwrCtrlTablehandler();
void delHoCtrlTableHandler();
void  delCsPwrCtrlTableHandler();
void delMtp3LinksetStsTableHandler();
void delMtp3LinksetStsTableHandlerScmAck();
I_Void delSwMTableHandler();
I_Void eicDelSwMTableHandler();

/* Range Check Table Massage Handlers */

I_Bool bssTableRangeChk(BssTableApi * rcvdMsgPtr);
I_Bool cellTableRangeChk(CellPerTableApi * rcvdMsgPtr);
I_Bool psCellTableRangeChk(PsCellTableApi * rcvdMsgPtr);
I_Bool csExternalCellTableRangeChk(CsExternalCellTableApi * rcvdMsgPtr);
I_Bool laTableRangeChk(LaTableApi * rcvdMsgPtr);
I_Bool raTableRangeChk(RaTableApi * rcvdMsgPtr);
I_Bool chnGrpTableRangeChk(ChnGrpTableApi * rcvdMsgPtr);
I_Bool csNeighCellsTableRangeChk(CsNeighCellsTableApi * rcvdMsgPtr);
I_Bool arfcnListTableRangeChk(ArfcnListTableApi * rcvdMsgPtr);
I_Bool gbInterfaceTableRangeChk(GbInterfaceTableApi* rcvdMsgPtr);
I_Bool nsvcTableRangeChk(NsvcTableApi* rcvdMsgPtr);
I_Bool frLinkTableRangeChk(FrLinkTableApi* rcvdMsgPtr);
I_Bool lepInfoTableRangeChk(LepInfoTableApi* rcvdMsgPtr);
I_Bool repInfoTableRangeChk(RepInfoTableApi* rcvdMsgPtr);
I_U32 ptdcCfgTableRangeChk(PtdcConfigTableApi* rcvdMsgPtr);
I_Bool csPwrCtrlTableRangeChk(CONST CsPwrCtrlTableApi* rcvdMsgPtr);
I_Bool hoCtrlTableRangeChk(HoCtrlTableApi *receivedMsgPtr);
I_Bool hoCtrlTablePerformConsistencyCheck(HoCtrlTableApi *recieveMsgPtr);
/*Changes PCU R2.5 Aricent -- START*/
I_Void sendBssUpdateInd2GrhmAndPsmsh();
I_Void sendBssUpdateInd2Psmsh();
I_Void deleteRowFromPsPerformanceCounterTablesForCell(I_U16 cellId, I_U16 lac);
I_Void insertRowInPsPerformanceCounterTablesForCell(I_U16 cellId, I_U16 lac);
I_Bool bssPsTableRangeChk(BssPsTableApi* rcvdMsgPtr);
/*Changes PCU R2.5 Aricent -- END*/
/********************************************************************
  Method to check if parameters received in Table Modification
  messages have change in parameter value from the existing values.
 *******************************************************************/
I_Bool compareRcvdMsgAndDbEntry(void* rcvdMsgPtr, void * dbEntryPtr,I_U32 size);


/********************************************************************
  Method to check if BSS is locked or not.
 *******************************************************************/
I_Bool bssLock();

/* Changes For CS2.2 : Start */
I_Void delTrxTableHandler();
I_Void delBicTableHandler();
I_Void setBicTableHandler();
I_Void setTrxTableHandler();
I_Bool bicTableRangeChk(BicTableApi* rcvdMsgPtr);
I_Bool trxTableRangeChk(TrxTableApi* rcvdMsgPtr);
/* Changes For CS2.2 : End */

/*BB, Start , CS4.0 , Clock Source Configuration */
I_Void setClkSrcTblHdlr(void);
/*BB, End , CS4.0 , Clock Source Configuration */
void copyAndFreeStoredMsgBuff(void *ptr, I_U32 size);

/*BSC CS4.0 HA Changes Starts*/
I_Void setCardStateChangeTableHandler();
/*BSC CS4.0 HA Changes Ends*/
/*BSC CS4.0 MLPPP Changes starts*/
I_Void setMlpppConfigTableHandler();
I_Void setBscDateTimeTableHandler();
/*BSC CS4.0 MLPPP Changes ends*/

I_S32 areAllDspLockedOnCard(I_U8 slotId);
/*Changes for configure CallEndTimerConfigTable Starts*/
I_Void setCallEndTimerConfigTable(); 
I_Bool callEndTableTimerRangeCheck(CallEndTimerConfigTableApi* rcvdMsgPtr); 
/*Changes for configure CallEndTimerConfigTable Ends*/
#endif /*__OAMSCFG_SETDELMSGHANDLER_H*/



