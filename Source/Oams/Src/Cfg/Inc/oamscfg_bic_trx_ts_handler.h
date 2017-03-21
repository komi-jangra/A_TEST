/***********************************File Header ***************************
  File Name        : oamscfg_bic_trx_ts_handler.h
Purpose          : This file contains functions definitions for BIC TRX timeslot.
Project          :  BSC OAM
Subsystem        : Oams
Author           :  Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/
#ifndef __OAMSCFG_BIC_TRX_TS_HANDLER_H_
#define __OAMSCFG_BIC_TRX_TS_HANDLER_H_

//#define MALLOC		AlocOrdBuf
#define MALLOC		malloc
typedef struct
{
   I_U8 timeSlot;
   I_U8 tsType;		/* LAPD_BIC or LAPD_TRX */
   I_Bool status;
}TimeSlotUsage;

typedef struct E1TimeSlot
{
/* Changes for R2.2 : Start */
   //OamsList e1List;
/* Changes for R2.2 : End */
   I_U32 e1Id;
   I_U32 numTs;
   I_U8 e1Type;
   I_Bool isSharedAbisTsSwitched;
   TimeSlotUsage timeSlotUsage[0];
}E1TimeSlot;

I_S32 populateTrxTsTeiTable(TrxTableApi *trxTablePtr, I_U32 e1Num,I_U32 *allocatedTs);
I_S32 populateTrxTsTeiTableOnReboot(TrxTableApi *trxTablePtr);
I_Void populateBicTeiE1MapTable();
I_Void initAbisE1TsList();
I_Void delTrxTsTeiTable(I_U32 trxId);
I_Bool isTimeslotAvailable(I_U32 e1Id, I_U8 tsType);
I_S32 getMccE1Ts(I_U32 firstE1, I_U32 firstTs, I_U32 *secondE1, I_U32 *secondTs);
I_U32 getNumTrxPerE1(I_U32 E1Id);
I_S32 addE1DataBicTeiE1MapTable(I_U32 E1Id);
I_Void deleteE1DataBicTeiE1MapTable(I_U32 E1Id);
I_U32 allocateTsForBic(I_U32 E1Id, I_U8 e1UsageType);
I_S32 addE1InAbisE1TsList(I_U32 e1Id, I_U8 e1UsageType);
I_Void delE1InAbisE1TsList(I_U32 e1Id);
I_S32 getUsedLapdBicTsForE1(I_U32 e1Id, I_U32 *e1TsList, I_U32 *tsListCount);
I_Void getListValue();
I_Void fetchE1AndInsertInBicTeiMapTable(I_U8 e1Type);
I_S32 markE1TsBusyInAbisList(I_U32 E1Id, I_U8 startTs, I_U32 usage);
I_S32 getE1TsForTrx(I_U32 ptrxId, I_U8 trxType, I_U32 bicId, I_U32* e1Id, I_U32* e1Ts);
I_S32 getE1TsForInFrameTrx(I_U32 ptrxId, I_U32* e1Id, I_U32* e1Ts);
I_U8 getTimeslotUsage(I_U32 e1Id, I_U8 e1Ts);
I_U8 getE1TypeFrmList(I_U32 e1Id);
/* Changes for R2.2 : Start */
//I_Bool isSharedAbisTsSwitched(I_U32 e1Id);
/* Changes for R2.2 : End */
I_Void toggleSharedAbisTsSwitchedVar(I_U32 e1Id);
I_S32 insertRowInBicTrxTimeslotUsageTable(I_U32 trxId, I_U32 e1Id, I_U32 startTs);
I_Void markTsStatusFreeInAbisList(I_U32 e1Id, I_U32 e1Ts);
I_U32 getMaxTrxNumFrmAbisList();

/* Trunk UsageType Changes : Starts */
I_S32 getLapdTsForTrx(I_U32 *trxLapdTs);
I_Void traverseAbisList();
/* Trunk UsageType Changes : Ends */
/* Changes for R2.2 : start */
I_S32 markFreeAbisTimeSlotTable(I_U32 ptrxId);
/* Changes for R2.2 : End */

#define TRXH_ACT_CLID   1

#endif /* __OAMSCFG_BIC_TRX_TS_HANDLER_H_*/
