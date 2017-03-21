/***********************************File Header ********************************
File Name        : oamscfg_bic_object_handler.h
Purpose          : This file contains functions definitions for CFG
Project          : BSC CS2.2
Subsystem        : Oams
Author           : Kapil Tyagi
CSCI ID          :
Version          :
************************************** End ************************************/

#ifndef  _OAMSCFG_BIC_OBJECT_HANDLER_H_
#define  _OAMSCFG_BIC_OBJECT_HANDLER_H_	1

I_Void updateBicTableHandler(BicTableApi* bicTableApiPtr);
I_Void addBicTableHandler();
I_U8 getBicNumConfiguredForE1(I_U32 e1Id);
I_Bool isTrxAssociatedWithBic(I_U32 bicId);
I_U8 getNumConfiguredTrxForBic(I_U32 bicId);
I_Void addConfiguredBics();
I_Void sndSwitchConForBicsAtInit();
I_S32 prepAndSndSwitchConForBic(I_U32 firstE1, I_U32 firstTs);
I_S32 prepAndSndSwitchDisConForBic(I_U32 firstE1, I_U32 firstTs);
I_S32 getE1TsFromBicTrxTimeslotUsageTable(I_U32 tsUser, I_U32 bicOrTrxId, I_U32* e1Id, I_U32* e1Ts);
I_Void  bicLockUnlockHandler();
I_Void bicLockProcedure(I_U32 bicId);
I_Void bicUnlockProcedure(I_U32 bicId);
I_Void updateStateAndSendBicLockAlarm(I_U32 bicId);
I_Void updateStateAndSendBicUnlockAlarm(I_U32 bicId);
I_S32 updateRowAbisTimeSlotPerTable(I_U32 e1Num, I_U32 tsNum, I_U32 usageType);
I_Void btsResetHandler();
I_Void btsConnectDisConnectHandler();
I_Void btsConnectProcedure(I_U32 bicId);
I_Void btsDisConnectProcedure(I_U32 bicId);
I_U32  getIndex(I_U32 value,I_U32 *index);
/*Changes for R2.3.4 Starts */
I_U8 btsSetSatFlagHandler(BicTableApi *pBtsTable);
I_U8 sendScmLapdTimerConfigReq(I_U32 bicId , I_U32 satFlag,I_U32 btsType);
I_U8 updateSatFlagBicTable(I_U32 bicId , I_U32 satFlag);
/*Changes for R2.3.4 Ends*/
/* LCLS Changes */
I_U8 btsSetClusterIdHandler();
I_U8 updateClusterIdBicTable(I_U32 bicId, I_U16 clusterId);
I_U8 btsSetMaxRfPwrConfHandler(BicTableApi *pBtsTable);
#define  BICHM_ACT_CLID                       1

#define numofTsForBic(btsType,numOfTrx,totalTs) \
{\
if(btsType == BIC)\
  totalTs = 1 + 3*numOfTrx;\
else\
  totalTs = 1 + 2* numOfTrx;\
}

#endif /*_OAMSCFG_BIC_OBJECT_HANDLER_H_ */

/********************************* Change History ******************************
Release     Patch        Author         	Description
CS2.2                  Kapil Tyagi		Initial Draft       		

*************************************** End ***********************************/
