/***********************************File Header ***************************
File Name        : oamscfg_cbs_handler.h
Purpose          : This file contains functions definitions for CFG
                   cell broadcast feature
Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent 
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef __OAMSCFG_CBS_HANDLER_H
#define __OAMSCFG_CBS_HANDLER_H

#define CONFIG_CP_CBS_PORT 2232 
#define INVALID_CBS 0xFFFF

I_Void sendAddCbCellToCbsh( I_U32 cellId, I_U32 lac);
I_Void getStringForBindFailErrorCause(I_U16 cbsId, I_U8 reason, I_U8 *string);
I_Bool cbsConfigRangeCheck(CbsConfigurationTableApi *receiveMsgPtr);
I_Bool cbsConfigRangeIpPortCheck(CbsConfigurationTableApi *receiveMsgPtr);
I_Void sendAddCbServerToCbsh( CbsConfigurationTableApi *cbsConfigData);
I_Void sendBreakCbsipAddressReqToCm(CbsConfigurationTableApi *cbsConfigData );
I_Void sendIntfUpToCbsh(I_U16 cbsId);
I_Void sendIntfDownToCbsh(I_U16 cbsId);
I_Bool checkParamModifiedCbsConfigReq(CbsConfigurationTableApi *receiveMsgPtr,CbsConfigurationTableApi *cbsConfigData);
I_Void sendDelCbCellToCbsh( I_U32 cellId, I_U32 lac);
I_Void sendAddCbServerForAllServersToCbsh();
I_Void sendAddCbCellForAllCellsToCbsh();
I_Void sendBreakCbsipAddressReqForAllServerToCbsIf();
I_Void cbsifConnectionDownHandler();
I_Void cbsifConnectionDownHandler();
I_Void cbsifBindConfirmHandler(I_PVoid outputMsg);
I_Void cbsifBindFailHandler(I_PVoid outputMsg);
I_Void cbsifUnBindHandler(I_PVoid outputMsg);
I_Void sendConfigCbsReqForAllServerToCbsIf(CbsConfigurationTableApi *cbsConfigData );
I_Void sendDelCbsServerToCbsh(I_U16 cbsId, I_U32 externalCbsServer);
I_Void sendIntfUpForInternalCbsToCbsh();
I_Void sendIntfDownForInternalCbsToCbsh();
I_Void setCbsConfigurationHandler();
I_Void delCbsConfigurationHandler();
I_Void cbsBindRespTimeOutHandler(I_U16 cbsId);
I_Void cbsBindRepeatTimeOutHandler(I_U16 cbsId);
I_Void cbsifDeleteConfigCbsResp();
I_Void cbsifConnectionUpHandler();
I_Void sendCellOprStateToCbsh(I_U32 cellId, I_U32 lac, I_U8 oprState);
I_U32 getIndexOfCbsRepeat(I_U16 value,I_U16 *index);
I_U32 getIndexOfCbsResp(I_U16 value,I_U16 *index);

#endif /*__OAMSCFG_CBS_HANDLER_H */
