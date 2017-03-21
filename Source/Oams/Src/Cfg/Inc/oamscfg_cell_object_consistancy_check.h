/***********************************File Header ***************************
  File Name        : oamscfg_cell_object_consistancy_check.h
Purpose          : This file contains functions definitions for CFG
Alarm handler  methods.
Project          :  BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef _OAMCFG_CELL_OBJECT_CONSISTANCY_CHECK_H_
#define _OAMCFG_CELL_OBJECT_CONSISTANCY_CHECK_H_


I_U8 validateCellParamDependency(CellPerTableApi *cellTablePtr);
I_U32 checkBCCHConsistency(CellPerTableApi *cellTable,ChnGrpTableApi *chnGrp,I_U32 bcchType , I_U32 numContiguousPdch);
I_U8 validateCsPwrCtrlparameters(CsPwrCtrlTableApi *recievedMsg);
I_Bool chkConsistencyForCsNeighCellTable(CsNeighCellsTableApi *rcvdMsgPtr);
I_Bool isCellUnBarred(I_U32 cellId, I_U32 lac);
I_Void sndCsNeighCellChangeMsgToCellh(I_U32 cellId, I_U32 lac, I_U16 mcc, I_U16 mnc);
I_Bool isCellReferenceByNeighbours(I_U32 cellId, I_U32 lac, I_U16 mcc, I_U16 mnc);
I_Bool isRefFoundForArfcnBsicOfNeigh(CsNeighCellsTableApi *rcvMsgPtr);
I_Bool isArfcnBsicFound(CsNeighCellsTableApi* rcvMsgPtr, I_U32 bcc, I_U32 ncc, I_U32 arfcn);
I_Bool isArfcnBsicFoundInNeighTree(I_U32 lac, I_U32 cellId, I_U32 bcc, I_U32 ncc, I_U32 arfcn, I_Bool nccChange);
I_Bool isArfcnBsicFoundInNeighTable(I_PVoid rcvPtr, I_U8 reqType, I_Bool nccChange);
I_Bool chkArfcnBsicForNccChange();
I_Bool isArfcnBsicFoundInNeigh(CsNeighCellsTableApi* rcvMsgPtr, I_U32 bcc, I_U32 ncc, I_U32 arfcn);
I_Bool chkCnstForHoCtrlTable(CsNeighCellsTableApi *receivedMsgPtr);
I_Bool isCgiUnqInExtAndIntCellTable(I_PVoid receivedMsgPtr, I_U8 cellType);

/*Changes PCU R2.5 Aricent -- START*/
I_U32 doConsistencyChecksOnSetOnPSCellTable(PsCellTableApi *receivedMsgPtr, I_Bool isAdd);
/*Changes PCU R2.5 Aricent -- END*/
/* Added For WCDMA-GSM HO Feature */
I_Bool getCountValueForWcdma(CsNeighCellsTableApi *recvPtr, I_U32 wcdmaBand  );
/********************************* Change History ***************************
  Release     Patch       Author         Description
  CS2                     Pratibha       Enum Removal Change

 ************************************** End *********************************/


#endif /*_OAMCFG_CELL_OBJECT_CONSISTANCY_CHECK_H_ */ 
