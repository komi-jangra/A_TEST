/***********************************File Header ***************************
File Name        : oamscfg_mlppp_object_handler.h
Purpose          : This file contains functions definitions for CFG

Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef  __OAMCFG_MLPPP_OBJECT_HANDLER_H_
#define  __OAMCFG_MLPPP_OBJECT_HANDLER_H_
I_Void addMlpppConfigTableHandler();
I_S32 allocateChannel(MlpppConfigTableApi *receivedMsgPtr, I_U8 slotId, OamsCfgOilMlpppConfigReq *oamsCfgOilMlpppConfigReq );
I_S32 updateMccLinkResource(MccLinkResourceTableApi *mccRow, I_U32 extE1, I_U32 extTs , I_U32 linkStatus);
I_S32 validateMlpppConfigReq();
I_S32 validateTrunkPortAndTs(I_U16 portId, I_U8 timeSlot);
I_Void mlpppConfigRespHandler();
I_Void addMlpppConfigRespHandler();
I_Void populateChannelStatus(I_U32 slotid, I_U32 channel, I_U32 channelStatus, I_U8 *timeslot);
I_Void freeMccLinkResource(I_U8 slotId);
I_S32 updateMlpppConfigInDb();
I_Void sendSwitchConnect(I_U8 slotId);
I_Void modifyMlpppConfigRespHandler();
I_Void mlpppConnectHandler();
I_Void mlpppDisconnectHandler();
I_Void mlpppChanStatusHandler(I_U8 *timeSlot);
I_S32 sendSetOmcIpUsingMlpppConfig();
I_S32 checkForMlpppConfig(I_U16 trunkPortId);
I_Void modifyMlppConfigTable(MlpppConfigTableApi *receivedMsgPtr, MlpppConfigTableApi *mlpppConfigTableDbPtr);
I_S32 disconTsIngMccLinkRes();
I_S32 delAllInvalidMlpppStatusRows();
I_S32 isMlpppStsTrunkPortTsValid(MlpppChannelStatusTableApi *mlpppChannelStatusPtr,MlpppConfigTableApi *mlpppConfigTableDbPtr);
I_S32 updateMccLinkResforAllrows(MccLinkResourceTableApi *mccLinkResourcePtr, I_U32 outRows, I_U16 outSize);
I_S32 resetAllMlppMccTrunkTsRows();
I_S32 isAnyFieldModifiedinMlppp(MlpppConfigTableApi *receivedMsgPtr, MlpppConfigTableApi *mlpppConfigTableDbPtr);
I_Void freegStoreMsgBuff();
I_S32 allocateChannelOnModify(MlpppConfigTableApi *receivedMsgPtr, I_U8 slotId, OamsCfgOilMlpppConfigReq *oamsCfgOilMlpppConfigReq );
I_S32 resetMccTrunkTsRowsforMlppIngBuff();
I_Void sendConfigFailAlarmToAfh(I_U16 errCode);
I_Void mlpppExhaustHandler();
I_S32 disconTsForMlppp();
I_Void insertMlpppChannelStatusforAllRows();
void convertIpToToken(char *s,int *a[]);
#endif

