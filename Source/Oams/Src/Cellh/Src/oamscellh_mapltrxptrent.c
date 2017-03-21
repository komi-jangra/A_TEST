/******************************************************************************
FILE NAME         :  oamscellh_mapltrxptrxent.c
PURPOSE           :  Source code for Mapping Ltrx to Ptrx
PROJECT           :  BSS
SUBSYSTEM         :  OAM 
AUTHOR            :  ARICENT
CSCI ID           :
VERSION           :  V0.1
 *******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include "sysxxx_msgopcode.h"
#include "sysxxx_macro.h"
#include "sysxxx_proc.h"
#include "sysxxx_msgstruct.h"
#include "sysinst_hashdefs.h"
#include "sysxxx_prcr.h"
#include "ipcfrm_extern.h"
#include "ipcfrm_syslog.h"
#include "ipcfrm_msgqueue.h"
#include "dbsxxx_commondefs.h" 
#include "csappxxx_common_datastruct.h"
#include "oamomc_hashdefs.h"
#include "oamsxxx_hashdef.h"
#include "oamsxxx_typedef.h"
#include "oamxxx_hashdefs.h"
#include "oamxxx_datastruct.h"
#include "oamxxx_msgstruct.h"
#include "oamsxxx_alarmid.h" //AMR
#include "bpmxxx_OAM_commonDef.h"
#include "msg_struct.h"
#include "syscmn_hashdefs.h"
#include "sysxxx_datastruct.h"
#include "syscmn_datastruct.h"
#include "oams_msgstruct.h"
#include "oamxxx_tableapidefs.h"
#include "DBLIBError.h"
#include "CLIB.h"
#include "dbsxxx_cellh_dbwrapper.h"
#include "dbsxxx_commonwrappers.h"
#include "oamscellh_mapltrxptrent.h"
#include "oamscellh_hashdefs.h"
#include "oams_hashdefs.h"/*Changes for R2.8 */


/***********************************************************************************
 *  Function Name   : PrepareAndSendExtendedCellCapMismatchAlarm
 *
 *  Args            : cellId,lac,ptrxId
 *                    
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Prepares And Send ExtendedCell Cap Mismatch Alarm message to be sent to CFG
 ***********************************************************************************/

void PrepareAndSendExtendedCellCapMismatchAlarm(I_U32 cellId, I_U32 lac,I_U32 ptrxId)
{

  OamsCellhCfgAlarmInd       *msgPtr            = NULL;

  I_U32                      sndMsgSize;
  I_S32                      errCode;

  LOG_PRINT(DEBUG, "In PrepareAndSendExtendedCellCapMismatchAlarm for CellId %d, lac %d, ptrxId %d",
	  cellId,lac,ptrxId);

  sndMsgSize = sizeof(OamsCellhCfgAlarmInd);

  msgPtr     = (OamsCellhCfgAlarmInd*)AlocMsgBuf(sndMsgSize);

  if ( msgPtr == NULL )
  {
	LOG_PRINT(CRITICAL,"Memory could not be allocated");
  }


  FILL_SYS_HDR(msgPtr, OAMS_CELLH_CFG_ALARM_IND,MSG_SUB_TYPE, PRCR_CP,
	  ENT_OAMS_CELLH ,ZERO , PRCR_CP, ENT_OAMS_CFG, ZERO);


  msgPtr->sysAlarm.sysalarmId = EVENT_EXTENDED_CELL_CAPABILITY_MISMATCH;
  msgPtr->sysAlarm.alarmSeqNo = ZERO;
  msgPtr->sysAlarm.alarmTime =  ZERO;
  msgPtr->sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
  msgPtr->sysAlarm.alarmReason = ZERO;
  msgPtr->sysAlarm.info3 = OAMS_OBJTYPE_CELL;
  msgPtr->sysAlarm.key1 = lac;
  msgPtr->sysAlarm.key2 = cellId; 
  sprintf(msgPtr->sysAlarm.infoString,"ExtendedCell Cap mismatch for(Lac:%d CellId:%d) with ptrxId",lac,cellId,ptrxId);
  strcat(msgPtr->sysAlarm.infoString,"\0");

  msgPtr->sysAlarm.infoStrLen = strlen(msgPtr->sysAlarm.infoString);
  LOG_PRINT(INFO,"(CELLH): Alarm String Sent is - %s",msgPtr->sysAlarm.infoString);
  LOG_PRINT(INFO,"(CELLH): Alarm String length is - %d",msgPtr->sysAlarm.infoStrLen);

  if (SendMsg((I_PVoid)msgPtr,MSG_ORD_PRIO,sndMsgSize) == SND_FAIL) 
  {
	LOG_PRINT(CRITICAL,"Send failed in PrepareAndSendExtendedCellCapMismatchAlarm");
  }
  else
	LOG_PRINT(DEBUG,"Send Succ in PrepareAndSendExtendedCellCapMismatchAlarm  with msgSize=%d",sndMsgSize);

}


/***********************************************************************************
 *  Function Name   : PrepareAndSendLclsCapMismatchAlarm
 *
 *  Args            : cellId,lac,ptrxId
 *                    
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Prepares And Send Lcls  Cap Mismatch Alarm message to be sent to CFG
 ***********************************************************************************/

void PrepareAndSendLclsCapMismatchAlarm(I_U32 cellId, I_U32 lac,I_U32 ptrxId)
{

  OamsCellhCfgAlarmInd       *msgPtr            = NULL;

  I_U32                      sndMsgSize;
  I_S32                      errCode;

  LOG_PRINT(DEBUG, "In PrepareAndSendLclsCapMismatchAlarm for CellId %d, lac %d, ptrxId %d",
	  cellId,lac,ptrxId);

  sndMsgSize = sizeof(OamsCellhCfgAlarmInd);

  msgPtr     = (OamsCellhCfgAlarmInd*)AlocMsgBuf(sndMsgSize);

  if ( msgPtr == NULL )
  {
	LOG_PRINT(CRITICAL,"Memory could not be allocated");
  }


  FILL_SYS_HDR(msgPtr, OAMS_CELLH_CFG_ALARM_IND,MSG_SUB_TYPE, PRCR_CP,
	  ENT_OAMS_CELLH ,ZERO , PRCR_CP, ENT_OAMS_CFG, ZERO);


  msgPtr->sysAlarm.sysalarmId = EVENT_LCLS_CAPABILITY_MISMATCH;
  msgPtr->sysAlarm.alarmSeqNo = ZERO;
  msgPtr->sysAlarm.alarmTime =  ZERO;
  msgPtr->sysAlarm.alarmLevel = TRAP_SEVERITY_MAJOR;
  msgPtr->sysAlarm.alarmReason = ZERO;
  msgPtr->sysAlarm.info3 = OAMS_OBJTYPE_CELL;
  msgPtr->sysAlarm.key1 = lac;
  msgPtr->sysAlarm.key2 = cellId; 
  sprintf(msgPtr->sysAlarm.infoString,"LCLS Cap mismatch for(Lac:%d CellId:%d) with ptrxId",lac,cellId,ptrxId);
  strcat(msgPtr->sysAlarm.infoString,"\0");

  msgPtr->sysAlarm.infoStrLen = strlen(msgPtr->sysAlarm.infoString);
  LOG_PRINT(INFO,"(CELLH): Alarm String Sent is - %s",msgPtr->sysAlarm.infoString);
  LOG_PRINT(INFO,"(CELLH): Alarm String length is - %d",msgPtr->sysAlarm.infoStrLen);

  if (SendMsg((I_PVoid)msgPtr,MSG_ORD_PRIO,sndMsgSize) == SND_FAIL) 
  {
	LOG_PRINT(CRITICAL,"Send failed in PrepareAndSendLclsCapMismatchAlarm");
  }
  else
	LOG_PRINT(DEBUG,"Send Succ in PrepareAndSendLclsCapMismatchAlarm  with msgSize=%d",sndMsgSize);

}




/***********************************************************************************
 *  Function Name   : CreateMsgMapentCellhDelMapResp
 *
 *  Args            : 1. ltrx Id (IN)
 *                    
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Prepares the deletion response message to be sent to cell handler
 ***********************************************************************************/

I_S32 CreateMsgMapentCellhDelMapResp(I_U32 ltrxId)
{
  LtrxTableApi               *ltrxTableOutData  = NULL;
  OamsMapentCellhDelMapResp  *msgPtr            = NULL;

  LtrxTableIndices           ltrxTableIndice;
  I_U32                      sndMsgSize;
  I_S32                      errCode;

  LOG_PRINT(DEBUG, "In CreateMsgMapentCellhDelMapResp");
  ltrxTableIndice.ltrxId = ltrxId;  

  errCode = getLtrxTable(&ltrxTableIndice,&ltrxTableOutData);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval failed from LtrxTable for[ltrxId:%d]err=%s",ltrxId,clib_strerror(errCode));
	return I_FALSE;
  }

  sndMsgSize = sizeof(OamsMapentCellhDelMapResp);

  msgPtr     = (OamsMapentCellhDelMapResp*)AlocMsgBuf(sndMsgSize);

  if ( msgPtr == NULL )
  {
	LOG_PRINT(CRITICAL,"Memory could not be allocated");
	return I_FALSE;
  }

  /* 
	 In this case message is being sent to cell handler itself so Source entity 
	 is filled with ZERO
   */
  FILL_SYS_HDR(msgPtr, OAMS_MAPENT_CELLH_DEL_MAP_RESP,MSG_SUB_TYPE, PRCR_CP,
	  ZERO ,ZERO , PRCR_CP, ENT_OAMS_CELLH, ZERO);

  msgPtr->cellId  =  ltrxTableOutData->cellId;
  msgPtr->lac     =  ltrxTableOutData->lac;  


  if (SendMsg((I_PVoid)msgPtr,MSG_ORD_PRIO,sndMsgSize) == SND_FAIL) 
  {
	LOG_PRINT(CRITICAL,"Send failed in CreateMsgMapentCellhDelMapResp");
	free(ltrxTableOutData);  
	return I_FALSE;
  }
  else
	LOG_PRINT(DEBUG,"Send Succ in CreateMsgMapentCellhDelMapResp with msgSize=%d",sndMsgSize);

  /* Success */ 
  free(ltrxTableOutData); 

  /* LOG_PRINT(DEBUG, "Exit func CreateMsgMapentCellhDelMapResp"); */
  return I_TRUE;

}
/***********************************************************************************
 *  Function Name   : CreateMsgMapentTrxhCreLtrxPtrxMappingReq
 *
 *  Args            : 1. Ltrx record pointer (IN)
 *                    2. Channel group table record pointer(IN)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : This method will form the Ltrx->Ptrx mapping request to be 
 sent from the Mapping entity to Trxh.
 ***********************************************************************************/

I_S32 CreateMsgMapentTrxhCreLtrxPtrxMappingReq(LtrxTableApi* ltrxRec, ChnGrpTableApi *chnGrpTableRec)
{                 
  OamsMapentTrxhCreLtrxPtrxMappingReq *sndMsgPtr            = NULL;
  I_U32                               sndMsgSize;
  CellPerTableIndices                    cellPerTableIndices;
  CellPerTableApi                        *cellPerTableRowData        = NULL;
  I_S32																errCode;
  OamsCellIndex                        cellIndex;
  I_S32                                dbResult;
  PtrxTableApi                        *trxData = NULL;
  PtrxTableIndices                    trxIndex;


  LOG_PRINT(DEBUG, "In CreateMsgMapentTrxhCreLtrxPtrxMappingReq");

  sndMsgSize = sizeof(OamsMapentTrxhCreLtrxPtrxMappingReq);
  sndMsgPtr     = (OamsMapentTrxhCreLtrxPtrxMappingReq *)AlocMsgBuf(sndMsgSize);

  if (sndMsgPtr == NULL)
  {
	LOG_PRINT(CRITICAL,"Memory could not be allocated");
	return I_FALSE;
  }

  /* Get the Cell Per Table row data based on the cell id and LAC */
  cellPerTableIndices.cellId = ltrxRec->cellId; //AMR CHANGES
  cellPerTableIndices.lac    = ltrxRec->lac;

  errCode = getCellPerTable(&cellPerTableIndices,&cellPerTableRowData);
  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval failed from CellPerTable for[cellId:%d][lac:%d]err=%s",ltrxRec->cellId,ltrxRec->lac,clib_strerror(errCode));
	return I_FALSE;
  }


  FILL_SYS_HDR(sndMsgPtr,OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_REQ, MSG_SUB_TYPE,PRCR_CP,
	  ENT_OAMS_CELLH ,ZERO , PRCR_CP,ENT_OAMS_TRXH, ZERO);

  LOG_PRINT(DEBUG,"Prepare Ltrx_Ptrx Mapping for [ltrxId: %d][ptrxId:%d]",ltrxRec->ltrxId,ltrxRec->ptrxId);

  sndMsgPtr->ptrxId     = ltrxRec->ptrxId;
  sndMsgPtr->ltrxId     = ltrxRec->ltrxId;
  sndMsgPtr->cellId     = ltrxRec->cellId;
  sndMsgPtr->lac        = ltrxRec->lac;

  dbResult=getCellIndex(ltrxRec->lac,ltrxRec->cellId,&cellIndex);
  if(CLIB_SUCCESS != dbResult)
  {
	LOG_PRINT(CRITICAL,"Error in getting cellIndex from DB");
	return I_FALSE;
  }
  sndMsgPtr->cellIndex  = cellIndex;
  sndMsgPtr->chgrId     = ltrxRec->chnGrpId;
  sndMsgPtr->maio       = ltrxRec->maio;
  sndMsgPtr->hsn        = chnGrpTableRec->hsn;
  sndMsgPtr->tsc        = chnGrpTableRec->tsc;
  sndMsgPtr->band       = chnGrpTableRec->band;
  /* Changes for Extended Cell */
  sndMsgPtr->isCellExtended   = cellPerTableRowData->isCellExtended;

  free(cellPerTableRowData);
  trxIndex.ptrxId = ltrxRec->ptrxId;
  if ( CLIB_SUCCESS != getPtrxTable(&trxIndex, &trxData) )
  {
	LOG_PRINT(CRITICAL,"getPtrxTable failed for TrxId[%d]",ltrxRec->ptrxId);
	return I_FALSE;

  }
  if ( ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4_CBCH && trxData->cbchSupport == I_FALSE)
  {
	LOG_PRINT(INFO,"Updating LtrxRec->channelTypeTs0 as BCCH_CCCH_SDCCH4 as CBCH not supported in TRX");
	ltrxRec->channelTypeTs0 = BCCH_CCCH_SDCCH4;
  }
  if ( ltrxRec->channelTypeTs1 == SDCCH8_CBCH && trxData->cbchSupport == I_FALSE)
  {
	LOG_PRINT(INFO,"Updating LtrxRec->channelTypeTs1 as SDCCH8 as CBCH not supported in TRX");
	ltrxRec->channelTypeTs1 = SDCCH8;
  }
  free(trxData);


  if ((ltrxRec->channelTypeTs0 == BCCH_CCCH) ||
	  (ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4) ||
	  (ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4_CBCH))
  {
	sndMsgPtr->maxPower   = ltrxRec->bcchPwr;
	sndMsgPtr->bcchPower  = ltrxRec->bcchPwr;
  }

  else
  {
	sndMsgPtr->maxPower   = ltrxRec->maxTxPwr;
	sndMsgPtr->bcchPower   = ltrxRec->bcchPwr;
  }


  sndMsgPtr->chCombinationId[0] = ltrxRec->channelTypeTs0;
  sndMsgPtr->chCombinationId[1] = ltrxRec->channelTypeTs1;
  sndMsgPtr->chCombinationId[2] = ltrxRec->channelTypeTs2;
  sndMsgPtr->chCombinationId[3] = ltrxRec->channelTypeTs3;
  sndMsgPtr->chCombinationId[4] = ltrxRec->channelTypeTs4;
  sndMsgPtr->chCombinationId[5] = ltrxRec->channelTypeTs5;
  sndMsgPtr->chCombinationId[6] = ltrxRec->channelTypeTs6;
  sndMsgPtr->chCombinationId[7] = ltrxRec->channelTypeTs7;

  sndMsgPtr->hfs.noOfArfcn   =  chnGrpTableRec->validArfcns;

  sndMsgPtr->hfs.arfcns[0] = chnGrpTableRec->arfcn1;
  sndMsgPtr->hfs.arfcns[1] = chnGrpTableRec->arfcn2;
  sndMsgPtr->hfs.arfcns[2] = chnGrpTableRec->arfcn3;
  sndMsgPtr->hfs.arfcns[3] = chnGrpTableRec->arfcn4;
  sndMsgPtr->hfs.arfcns[4] = chnGrpTableRec->arfcn5;
  sndMsgPtr->hfs.arfcns[5] = chnGrpTableRec->arfcn6;
  sndMsgPtr->hfs.arfcns[6] = chnGrpTableRec->arfcn7;
  sndMsgPtr->hfs.arfcns[7] = chnGrpTableRec->arfcn8;
  sndMsgPtr->hfs.arfcns[8] = chnGrpTableRec->arfcn9;
  sndMsgPtr->hfs.arfcns[9] = chnGrpTableRec->arfcn10;
  sndMsgPtr->hfs.arfcns[10] = chnGrpTableRec->arfcn11;
  sndMsgPtr->hfs.arfcns[11] = chnGrpTableRec->arfcn12;
  sndMsgPtr->hfs.arfcns[12] = chnGrpTableRec->arfcn13;
  sndMsgPtr->hfs.arfcns[13] = chnGrpTableRec->arfcn14;
  sndMsgPtr->hfs.arfcns[14] = chnGrpTableRec->arfcn15;
  sndMsgPtr->hfs.arfcns[15] = chnGrpTableRec->arfcn16;
  sndMsgPtr->hfs.arfcns[16] = chnGrpTableRec->arfcn17;
  //sndMsgPtr->hfs.arfcns[17] = chnGrpTableRec->arfcn18;

  /* Sorting */
  {
	I_U16 i,j, arfcn;
	for (i=0; i<sndMsgPtr->hfs.noOfArfcn; i++) {
	  for (j=i+1; j<sndMsgPtr->hfs.noOfArfcn; j++) {
		if(sndMsgPtr->hfs.arfcns[i] >  sndMsgPtr->hfs.arfcns[j])
		{
		  arfcn = sndMsgPtr->hfs.arfcns[i];
		  sndMsgPtr->hfs.arfcns[i] = sndMsgPtr->hfs.arfcns[j];
		  sndMsgPtr->hfs.arfcns[j] = arfcn; 
		}
	  }
	}
  } /* Sorting */

  if (SendMsg((I_PVoid)sndMsgPtr,MSG_ORD_PRIO,sndMsgSize) == SND_FAIL) 
  {
	LOG_PRINT(CRITICAL,"Send failed in CreateMsgMapentTrxhCreLtrxPtrxMappingReq");
	return I_FALSE;
  }
  else
	LOG_PRINT(DEBUG,"Send Success in CreateMsgMapentTrxhCreLtrxPtrxMappingReq with msgSize=%d",sndMsgSize);

  /* LOG_PRINT(DEBUG, "Exit func CreateMsgMapentTrxhCreLtrxPtrxMappingReq"); */
  return I_TRUE;        
}
/***********************************************************************************
 *  Function Name   : CreateMsgMapentTrxhDelLtrxPtrxMappingReq
 *
 *  Args            : 1. ptrx Id (IN)
 *                    2. ltrx Record pointer (IN)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Prepares the Delete request message to be sent to Trx handler.
 ***********************************************************************************/

I_S32 CreateMsgMapentTrxhDelLtrxPtrxMappingReq(I_U32 ptrxId, LtrxTableApi* ltrxRec)
{
  I_U32                               sndMsgSize;
  OamsMapentTrxhDelLtrxPtrxMappingReq *msgPtr            = NULL;

  LOG_PRINT(DEBUG, "In CreateMsgMapentTrxhDelLtrxPtrxMappingReq");

  sndMsgSize = sizeof(OamsMapentTrxhDelLtrxPtrxMappingReq);
  msgPtr     = (OamsMapentTrxhDelLtrxPtrxMappingReq*) AlocMsgBuf(sndMsgSize);

  if (msgPtr == NULL)
  {
	LOG_PRINT(CRITICAL,"Memory could not be allocated");
	return I_FALSE;
  }

  FILL_SYS_HDR(msgPtr,OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ, MSG_SUB_TYPE,PRCR_CP,
	  ENT_OAMS_CELLH ,ZERO , PRCR_CP,ENT_OAMS_TRXH, ZERO);

  LOG_PRINT(DEBUG,"Preparing Del_Ltrx_Ptrx for [ltrxId:%d][ptrxId:%d]",ltrxRec->ltrxId,ptrxId);
  msgPtr->ptrxId = ptrxId;
  msgPtr->ltrxId = ltrxRec->ltrxId;
  msgPtr->cellId = ltrxRec->cellId;
  msgPtr->lac    = ltrxRec->lac;

  if (SendMsg((I_PVoid)msgPtr,MSG_ORD_PRIO,sndMsgSize) == SND_FAIL)
  {
	LOG_PRINT(CRITICAL,"Send failed in CreateMsgMapentTrxhDelLtrxPtrxMappingReq");
	return I_FALSE;
  } 
  else
	LOG_PRINT(DEBUG,"Send Success in CreateMsgMapentTrxhDelLtrxPtrxMappingReq with msgSize=%d ",sndMsgSize);

  /* LOG_PRINT(DEBUG, "Exit func CreateMsgMapentTrxhDelLtrxPtrxMappingReq"); */
  return I_TRUE;        
}
/***********************************************************************************
 *  Function Name   : FindNotMappableButMappedPtrx
 *
 *  Args            : 1. ptrxId (OUT)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds a Ptrx which has Mapping Status set as mapped and Map 
 Allowed set as False.Returns the Ptrx Id of such a Ptrx.
 ***********************************************************************************/

I_Bool FindNotMappableButMappedPtrx (I_U32 *ptrxId)
{
  I_U32        ptrxTableOutRows;
  I_U16         ptrxTableOutSize;
  PtrxTableApi *ptrxTableOutData;   
  I_U32         nPtrxTableRowNum;
  I_S32         errCode;
  PtrxTableApi *ptrxTableRowData = NULL;
  I_Bool        ptrxRecFound     = I_FALSE;


  LOG_PRINT(DEBUG, "In FindNotMappableButMappedPtrx");

  /*Get all the PTRX entries from PTRX table */
  errCode = getallPtrxTable(&ptrxTableOutData, &ptrxTableOutRows, &ptrxTableOutSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval failed from Ptrx Table for all records: err = %s", clib_strerror(errCode));        
	return I_FALSE;
  }


  for (nPtrxTableRowNum=0; nPtrxTableRowNum < ptrxTableOutRows; nPtrxTableRowNum++)
  {
	ptrxTableRowData = (PtrxTableApi*)((I_U8*)(ptrxTableOutData) + (nPtrxTableRowNum * ptrxTableOutSize));   

	if ( ptrxTableRowData->mapAllowed == I_FALSE && ptrxTableRowData->mappingStatus == MAPPED )
	{
	  *ptrxId = ptrxTableRowData->ptrxId;
	  ptrxRecFound = I_TRUE;

	  LOG_PRINT(DEBUG,"Found Ptrx with MapAllowed=No and MappingStatus=MAPPED,PtrxID=%d",*ptrxId);
	  break;
	}

  }
  if (ptrxRecFound == I_FALSE)
  {
	LOG_PRINT(DEBUG," No Ptrx Found with MapAllowed=No and MappingStatus=MAPPED");
  }

  free(ptrxTableOutData);

  LOG_PRINT(DEBUG, "Exit func FindNotMappableButMappedPtrx");

  return ptrxRecFound;   
}


/***********************************************************************************
 *  Function Name   : FindSuitableUnmappedPtrxWithMapAllowed
 *
 *  Args            : 1. ltrx Record pointer (IN)
 *                    2. Channel Group Table Record pointer (IN)
 *                    3. ptrx Id (OUT)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds a suitable Unmapped Ptrx with MapAllowed set to I_TRUE.
 ***********************************************************************************/

I_Bool FindSuitableUnmappedPtrxWithMapAllowed (I_U32 *ptrxId, 
	LtrxTableApi *ltrxRec, 
	ChnGrpTableApi *chnGrpTableRec)
{
  I_S32          errCode;
  I_U32          ptrxTableOutRows;
  I_U16          ptrxTableOutSize;
  PtrxTableApi  *ptrxTableOutData;   
  I_U32          nPtrxTableRowNum;
  I_S32          isPtrxSuitable;
  PtrxTableApi  *ptrxTableRowData   = NULL; 
  I_Bool         ptrxRecFound       = I_FALSE;
  I_Bool         e1Status           = I_FALSE;


  LOG_PRINT(DEBUG, "In FindSuitableUnmappedPtrxWithMapAllowed");

  /*Get all the PTRX entries from PTRX table */
  errCode = getallPtrxTable(&ptrxTableOutData, &ptrxTableOutRows, &ptrxTableOutSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval failed from PTRX Table for all records: err = %s", clib_strerror(errCode));
	return I_FALSE;
  }

  for (nPtrxTableRowNum=0; nPtrxTableRowNum < ptrxTableOutRows; nPtrxTableRowNum++)
  {
	ptrxTableRowData = (PtrxTableApi*)((I_U8*)ptrxTableOutData + (nPtrxTableRowNum * ptrxTableOutSize));

	if (ptrxTableRowData->mapAllowed == I_TRUE && ptrxTableRowData->mappingStatus == UNMAPPED )
	{
	  LOG_PRINT(DEBUG, "Ptrx[%d] found in DB with mappAllowed=YES and mappingStatus=UNMAPPED::Now,ValidateOfPtrx",ptrxTableRowData->ptrxId );

	  /* CS4.0 : ABIS_E1_LOCK_UNLOCK Changes : Starts */
	  /*
		 LOG_PRINT(DEBUG, "Validate E1 of the fetched Record ");
	   */
	  e1Status = ValidateE1OfPtrx( ptrxTableRowData->ptrxId );

	  if (e1Status == I_TRUE)
	  {  
		/*
		   LOG_PRINT(INFO, "**********************Validity checks PASS for this Record.************************");      
		 */
		isPtrxSuitable = GetPtrxSuitability(ptrxTableRowData->ptrxId, ltrxRec,chnGrpTableRec );

		if (isPtrxSuitable)
		{
		  *ptrxId      = ptrxTableRowData->ptrxId;
		  ptrxRecFound = I_TRUE;
		  LOG_PRINT(DEBUG, "Suitable Ptrx found in FindSuitableUnmappedPtrxWithMapAllowed,[ptrxId:%d][ltrxId:%d] ",*ptrxId,ltrxRec->ltrxId );
		  break;
		}
	  }
	  else
	  {
		LOG_PRINT(INFO, "Validity checks Fails for this Record");
	  }              
	  /* CS4.0 : ABIS_E1_LOCK_UNLOCK Changes : Ends */

	}
  }

  free(ptrxTableOutData);

  /* LOG_PRINT(DEBUG, "Exit func FindSuitableUnmappedPtrxWithMapAllowed"); */
  return ptrxRecFound;   
}


/***********************************************************************************
 *  Function Name   : GetPtrxSuitability
 *
 *  Args            : 1. ptrxId (IN)
 *                    2. ltrxRec (IN)
 *                    3. chnGrpTableRec (IN)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds a Ptrx which is suitable to be mapped with the Ltrx record 
 sent as an argument to the function.                     
 ***********************************************************************************/

I_S32 GetPtrxSuitability( I_U32 ptrxId, LtrxTableApi *ltrxRec, ChnGrpTableApi *chnGrpTableRec )
{
  //PhysicalTrxPreconfiguredTableIndices   physicalTrxTableIndice;
  CellTableIndices                       cellTableindice;
  CellPerTableIndices										cellPerTableIndices;
  I_S32                                  errCode;
  PtrxTableIndices                       ptrxTableIndice;
  PtrxTableApi                           *ptrxTableRowData        = NULL;
  CellTableApi                           *cellTableRowData        = NULL;
  CellPerTableApi                        *cellPerTableRowData        = NULL;
  // PhysicalTrxPreconfiguredTableApi       *physicalTrxTableRowData = NULL;
  TrxTableIndices                        trxTableIndices;
  TrxTableApi                            *physicalTrxTableRowData = NULL;
  BicTableApi                            *btsTableOutData =NULL;
  BicTableIndices                         btsTableIndices;
  /*
	 LOG_PRINT(DEBUG, "In function GetPtrxSuitability");
   */

  /* Get the Physical TRX table row data based on the PTRX Id specified */

  /*Changes in CS2.2*/

  // physicalTrxTableIndice.ptrxId = ptrxId;
  trxTableIndices.ptrxId = ptrxId ;
  errCode = getTrxTable(&trxTableIndices, &physicalTrxTableRowData);
  // errCode = getPhysicalTrxPreconfiguredTable(&physicalTrxTableIndice, &physicalTrxTableRowData);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "GetPtrxSuitability::Retrieval fail from TrxTable for [ptrxId:%d]err=%s",ptrxId,clib_strerror(errCode));
	return I_FALSE;
  }

  /*Changes in CS2.2*/
  /* Get the Ptrx table row data based on Ptrx Id specified */
  ptrxTableIndice.ptrxId = ptrxId;

  errCode = getPtrxTable(&ptrxTableIndice, &ptrxTableRowData);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "GetPtrxSuitability::Retrieval fail from PtrxTable for [ptrxId:%d]err=%s",ptrxId,clib_strerror(errCode));
	return I_FALSE;
  }


  /* Get the Cell Table row data based on the cell id and LAC */
  cellTableindice.cellId = ltrxRec->cellId;
  cellTableindice.lac    = ltrxRec->lac;

  errCode = getCellTable(&cellTableindice,&cellTableRowData);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "GetPtrxSuitability::Retrieval fail from CellTable for [cellId: %d][lac: %d]err=%s",ltrxRec->cellId,ltrxRec->lac,clib_strerror(errCode));
	return I_FALSE;
  }

  /* R2.4 Changes : Starts */

  /*
	 Check whether AMR is supported in both Cell and Trx or not.
	 If it is enabled in Cell then it should be enabled in TRX also but vice-versa is not true.
	 If any Mismatch occurs then that Trx is not suitable for mapping. 
   */
  if ( (cellTableRowData->amrSupport == I_TRUE) && (ptrxTableRowData->amrSupport == I_FALSE) )
  {
	LOG_PRINT(INFO,"GetPtrxSuitability::AMR supported in Cell but not in TRX. Mismatch. cellTableRowData->amrSupport=%d,ptrxTableRowData->amrSupport=%d",cellTableRowData->amrSupport, ptrxTableRowData->amrSupport );
	free(physicalTrxTableRowData);
	free(cellTableRowData);
	free(ptrxTableRowData);

	LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability :Suitable Ptrx not found ");
	return I_FALSE;
  }

  /* R2.4 Changes : Ends   */



  /* Extended Cell Changes
	 Check whether Extended Cell  is supported in both Cell and Trx or not.
	 If it is enabled in Cell then it should be enabled in TRX also but vice-versa is not true.
	 If any Mismatch occurs then that Trx is not suitable for mapping. 
   */
  if ( (cellTableRowData->isCellExtended == I_TRUE) && (ptrxTableRowData->extCellSupport == I_FALSE) )
  {
	LOG_PRINT(INFO,"GetPtrxSuitability:: ExtendedCell supported in Cell but not in TRX. Mismatch. cellTableRowData->isCellExtended=%d,ptrxTableRowData->extCellSupport=%d",cellTableRowData->isCellExtended, ptrxTableRowData->extCellSupport );
	PrepareAndSendExtendedCellCapMismatchAlarm(cellTableindice.cellId,cellTableindice.lac,ptrxId);
	free(physicalTrxTableRowData);
	free(cellTableRowData);
	free(ptrxTableRowData);

	LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability :Suitable Ptrx not found ");
	return I_FALSE;
  }

  btsTableIndices.bicId = physicalTrxTableRowData->bicId ;
  errCode = getBicTable(&btsTableIndices,&btsTableOutData);
  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "GetPtrxSuitability::Retrieval fail from BicTable for [bicId:%d]err=%s",physicalTrxTableRowData->bicId,clib_strerror(errCode));
	free(physicalTrxTableRowData);
	free(ptrxTableRowData);
	free(cellTableRowData);
	LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability :Suitable Ptrx not found ");
	return I_FALSE;
  }
  /* LCLS Changes
	 Check whether LCLS  is supported in both Cell and Trx or not.
	 If it is enabled in Cell then it should be enabled in TRX also but vice-versa is not true.
	 If any Mismatch occurs then that Trx is not suitable for mapping. 
   */
  if (cellTableRowData->localSwitchingSupport == I_TRUE)    
  {

	/* Implicitly TDM BTS doesn't support LCLS whereas IP BTS supports LCLS */
	if ((btsTableOutData->btsType == BIC) || (btsTableOutData->btsType == R2_BTS))
	{  
	  LOG_PRINT(INFO,"GetPtrxSuitability:: LCLS Mismatch. Cell level LCLS: %u, BtsType: %u is TDM based",
		  cellTableRowData->localSwitchingSupport, btsTableOutData->btsType);
	  PrepareAndSendLclsCapMismatchAlarm(cellTableindice.cellId,cellTableindice.lac,ptrxId);
	  free(physicalTrxTableRowData);
	  free(cellTableRowData);
	  free(ptrxTableRowData);
	  free(btsTableOutData);

	  LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability :Suitable Ptrx not found ");
	  return I_FALSE;
	}
  }

  /* Get the Cell Per Table row data based on the cell id and LAC */
  cellPerTableIndices.cellId = ltrxRec->cellId; //AMR CHANGES
  cellPerTableIndices.lac    = ltrxRec->lac;

  errCode = getCellPerTable(&cellPerTableIndices,&cellPerTableRowData);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval fail from CellPerTable for [cellId:%d][lac:%d]err=%s",ltrxRec->cellId,ltrxRec->lac,clib_strerror(errCode));
	free(physicalTrxTableRowData);
	free(cellTableRowData);
	free(ptrxTableRowData);
	free(btsTableOutData);
	return I_FALSE;
  }
  /* 
	 Check if the antenna Id of cell, band and power capability of the Ptrx to be mapped is suitable
	 for this ltrx
   */

  if ( ltrxRec->channelTypeTs0 == BCCH_CCCH || ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4 || ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4_CBCH)
  {

	if ((cellTableRowData->antennaId == physicalTrxTableRowData->antennaID) &&
		((btsTableOutData->maxRfPwrConf - ltrxRec->bcchPwr ) <= MAX_POWER_REDUCTION ) &&
		((btsTableOutData->maxRfPwrConf - ltrxRec->bcchPwr ) >= MIN_POWER_REDUCTION ) &&
		(chnGrpTableRec->band == ptrxTableRowData->bandCapability))
	{
	  free(physicalTrxTableRowData);
	  free(cellTableRowData);
	  free(ptrxTableRowData);
	  free(cellPerTableRowData);
	  free(btsTableOutData);
	  LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability: Suitable Ptrx found ");
	  return I_TRUE;
	}
  }

  else 
  {
	if ((cellTableRowData->antennaId == physicalTrxTableRowData->antennaID) &&
		(( btsTableOutData->maxRfPwrConf - ltrxRec->maxTxPwr ) <= MAX_POWER_REDUCTION ) &&
		(( btsTableOutData->maxRfPwrConf - ltrxRec->maxTxPwr ) >= MIN_POWER_REDUCTION ) &&
		(chnGrpTableRec->band == ptrxTableRowData->bandCapability))
	{
	  free(physicalTrxTableRowData);
	  free(cellTableRowData);
	  free(ptrxTableRowData);
	  free(cellPerTableRowData);
	  free(btsTableOutData);

	  LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability: Suitable Ptrx found ");
	  return I_TRUE;
	}

  }


  /* Suitable Ptrx not found */ 
  if (cellTableRowData->antennaId != physicalTrxTableRowData->antennaID )
  {

	//LOG_PRINT(DEBUG, "cellTbl->antnId=%d != trxTbl->antnId=%d -Exit Func"
	//              "-GetPtrxSuitblty:Suitabl Ptrx not fnd", cellTableRowData->antennaId, 
	//              physicalTrxTableRowData->antennaID );
	/*
	   LOG_PRINT(DEBUG, " Antenna Id of Cell and Pre configured physical Ptrx are not equal ");
	 */
  }

  if ( ltrxRec->channelTypeTs0 == BCCH_CCCH || ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4 || ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4_CBCH )
  {
	if(ltrxRec->bcchPwr > btsTableOutData->maxRfPwrConf)
	{
	  //LOG_PRINT(DEBUG, "ltrxRec->bcchPwr=%d,ptrxTableRowData->pwrCapability=%d ",ltrxRec->bcchPwr,ptrxTableRowData->pwrCapability);
	  LOG_PRINT(DEBUG, "Bcch Pwr of Ltrx(%d) > Bts RF MAX Power (%d). NOTE:(bts_maxRfPwr - "
		  "Cell_BcchPwr)<=12::Exiting Func-GetPtrxSuitability:Suitable Ptrx not found",
		  ltrxRec->bcchPwr,btsTableOutData->maxRfPwrConf);
	}
  }
  else 
  {
	if(ltrxRec->maxTxPwr >btsTableOutData->maxRfPwrConf )
	{
	  //LOG_PRINT(DEBUG,"ltrxRec->maxTxPwr=%d,ptrxTableRowData->pwrCapability=%d",ltrxRec->maxTxPwr,ptrxTableRowData->pwrCapability );
	  LOG_PRINT(DEBUG,"Max Tx Pwr of Ltrx(%d) > Bts RF MAX Power  (%d). "
		  "NOTE:(Bts_maxRfPwr - Cell_MaxTxPwr)<=12::Exiting Func-GetPtrxSuitability:"
		  "Suitable Ptrx not found",ltrxRec->maxTxPwr,btsTableOutData->maxRfPwrConf);
	}
  }

  if (chnGrpTableRec->band != ptrxTableRowData->bandCapability)
  {
	//LOG_PRINT(DEBUG,"chnGrpTableRec->band=%d,ptrxTableRowData->bandCapability=%d",chnGrpTableRec->band,ptrxTableRowData->bandCapability);
	LOG_PRINT(DEBUG,"Channel Group band(%d) != Ptrx Band capability(%d)."
		" Exiting Func-GetPtrxSuitability:Suitable Ptrx not found",
		chnGrpTableRec->band,ptrxTableRowData->bandCapability);
  }

  if ( ltrxRec->channelTypeTs0 == BCCH_CCCH || ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4 ||  ltrxRec->channelTypeTs0 == BCCH_CCCH_SDCCH4_CBCH)
  {
	if ( ((I_S32)(btsTableOutData->maxRfPwrConf - ltrxRec->bcchPwr)) > MAX_POWER_REDUCTION  )
	{
	  //LOG_PRINT(DEBUG, "ltrxRec->bcchPwr=%d,ptrxTableRowData->pwrCapability=%d",ltrxRec->bcchPwr,ptrxTableRowData->pwrCapability);
	  LOG_PRINT(DEBUG, "ltrxRec->bcchPwr=%d,btsTableOutData->maxRfPwrConf=%d "
		  "NOTE:(Bts_maxRfPwr - Cell_BcchPwr)<=12::Exiting "
		  "Func-GetPtrxSuitability:Suitable Ptrx not found",
		  ltrxRec->bcchPwr,btsTableOutData->maxRfPwrConf);
	}
  }
  else 
  {
	if ( ((I_S32)(btsTableOutData->maxRfPwrConf - ltrxRec->maxTxPwr)) > MAX_POWER_REDUCTION  )
	{
	  //LOG_PRINT(DEBUG,"ltrxRec->maxTxPwr=%d,ptrxTableRowData->pwrCapability=%d",ltrxRec->maxTxPwr,ptrxTableRowData->pwrCapability );
	  LOG_PRINT(DEBUG,"ltrxRec->maxTxPwr=%d,btsTableOutData->maxRfPwrConf=%d "
		  "NOTE:(Bts_maxRfPwr - Cell_MaxTxPwr)<=12::Exiting "
		  "Func-GetPtrxSuitability:Suitable Ptrx not found",
		  ltrxRec->maxTxPwr,btsTableOutData->maxRfPwrConf);
	}
  }


  free(physicalTrxTableRowData);
  free(cellTableRowData);
  free(ptrxTableRowData);
  free(cellPerTableRowData);
  free(btsTableOutData);

  /*
	 LOG_PRINT(DEBUG, "Exiting Func-GetPtrxSuitability: Suitable Ptrx not found ");
   */
  return I_FALSE;
}

/***********************************************************************************
 *  Function Name   : GetSortedGenUnmappedLtrxList
 *
 *  Args            : 1. sortedGenUnmappedLtrxList(OUT)
 *                    2. totalSortedGenUnMappedLtrxRecs(OUT)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds the total no of Generated and Unmapped Ltrx records in DB.
 *                    Sorts the ltrx records on basis of priority and stores it in the buffer                     
 **************************************************************************************/
I_Bool GetSortedGenUnmappedLtrxList( LtrxTableApi **sortedGenUnmappedLtrxList,I_U32 *totalSortedGenUnMappedLtrxRecs )
{
  I_U32         ltrxTableOutRows;
  I_U16         ltrxTableOutSize;
  LtrxTableApi  *ltrxTableOutData          = NULL;
  LtrxTableApi  *ltrxTableCurrRec          = NULL;
  LtrxTableApi  *ltrxTableRec              = NULL;
  LtrxTableApi  *firstRecOfSortedLtrxList  = NULL;
  LtrxTableApi  *tempLtrxRec               = NULL;
  I_U32          ltrxPriority              = 0;
  I_U32          prevLtrxPriority          = 0;
  I_U32          genUnmappedLtrxRecCnt     = 0; 
  I_S32          errCode;
  I_U32          nLtrxTableRowNum;
  I_U32          ltrxCurrRecPostion;

  LOG_PRINT(INFO, "In GetSortedGenUnmappedLtrxList " );

  errCode = getallLtrxTable(&ltrxTableOutData,&ltrxTableOutRows,&ltrxTableOutSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval all failed from LtrxTable:err=%s", clib_strerror(errCode));
	return I_FALSE;
  }

  for (nLtrxTableRowNum = 0; nLtrxTableRowNum < ltrxTableOutRows ; nLtrxTableRowNum++)
  { 
	ltrxTableCurrRec = (LtrxTableApi*)((I_U8*)ltrxTableOutData + (nLtrxTableRowNum * ltrxTableOutSize));

	if ( ltrxTableCurrRec->mappingStatus == UNMAPPED && 
		ltrxTableCurrRec->generationStatus == GENERATED )
	{
	  genUnmappedLtrxRecCnt++;
	}

  }
  LOG_PRINT(DEBUG, "genUnmappedLtrxRecCnt=%d (if 0, return)",genUnmappedLtrxRecCnt);

  if (genUnmappedLtrxRecCnt == ZERO)
  {
	free(ltrxTableOutData);
	//LOG_PRINT(DEBUG, "No Generated and Unmapped Ltrx Records found");
	return I_FALSE;
  }

  *sortedGenUnmappedLtrxList = (LtrxTableApi*)malloc(genUnmappedLtrxRecCnt * sizeof(LtrxTableApi));

  firstRecOfSortedLtrxList = *sortedGenUnmappedLtrxList;

  for (nLtrxTableRowNum = 0; nLtrxTableRowNum < ltrxTableOutRows ; nLtrxTableRowNum++)
  {
	ltrxTableCurrRec = (LtrxTableApi*)((I_U8*)ltrxTableOutData + (nLtrxTableRowNum * ltrxTableOutSize));

	if ( ltrxTableCurrRec->mappingStatus == UNMAPPED && 
		ltrxTableCurrRec->generationStatus == GENERATED
	   )
	{
	  ltrxCurrRecPostion = 0 ;
	  prevLtrxPriority   = 0;

	  while ( ltrxCurrRecPostion < ltrxTableOutRows )
	  {              
		ltrxTableRec = (LtrxTableApi*)((I_U8*)ltrxTableOutData + (ltrxCurrRecPostion * ltrxTableOutSize));

		ltrxPriority = ltrxTableRec->ltrxPriority;

		if (ltrxTableRec->mappingStatus == UNMAPPED && 
			ltrxTableRec->generationStatus == GENERATED &&
			ltrxTableRec->ltrxPriority != ZERO )
		{
		  if ( ltrxPriority >= prevLtrxPriority )
		  {
			tempLtrxRec = ltrxTableRec;                 
			prevLtrxPriority = ltrxTableRec->ltrxPriority;
		  } 
		}
		ltrxCurrRecPostion++;
	  }

	  memcpy(*sortedGenUnmappedLtrxList,tempLtrxRec,sizeof(LtrxTableApi));
	  tempLtrxRec->ltrxPriority = 0;
	  *sortedGenUnmappedLtrxList = (LtrxTableApi*)((I_U8*)(*sortedGenUnmappedLtrxList) +  sizeof(LtrxTableApi));       
	}

  }
  *sortedGenUnmappedLtrxList = firstRecOfSortedLtrxList;
  *totalSortedGenUnMappedLtrxRecs = genUnmappedLtrxRecCnt;

  free(ltrxTableOutData);
  /*
	 LOG_PRINT(INFO, " Exit func GetSortedGenUnmappedLtrxList " );  
   */
  return I_TRUE;
}

/***********************************************************************************
 *  Function Name   : FindLtrxWithSuitablePtrx
 *
 *  Args            : 1. Ptrx Id (OUT)
 *                    2. Generated and Unmapped Ltrx record (OUT)
 *                    3. Lower priority ltrx record (OUT)
 *                    4. Channel group record (OUT)
 *                    5. Ptrx is Unmapped or Mapped (OUT)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds a Ltrx with highest priority which is in generated state
 *                    but is not mapped to any Ptrx and can be mapped to set of the 
 *                    available unmapped Ptrx or the set of the Ptrx which are in the 
 *                    mapped state.
 ***********************************************************************************/
I_Bool FindLtrxWithSuitablePtrx ( I_U32 *ptrxId, LtrxTableApi *genUnamppedLtrxRec, LtrxTableApi **lowerPrtLtrxRec,
	ChnGrpTableApi **chnGrpTableRec,I_Bool *IsUnmappedPtrx ) 
{
  I_S32              errCode;
  I_U32              isFound;
  I_U32              nLtrxTableRowNum;
  I_U32              sortedGenUnmappedLtrxRecsNum  = 0;
  LtrxTableApi       *sortedGenUnmappedLtrxList    = NULL;
  LtrxTableApi       *currLtrxRec                  = NULL;
  ChnGrpTableIndices chnGrpTableIndice;
  I_U32              suitablePtrxId;
  LtrxTableApi       *tmpLtrxRec                   = NULL;
  I_U32              tmpRecCnt, tmpCnt;
  I_U16              tmpRecSize;


  LOG_PRINT(DEBUG, "In FindLtrxWithSuitablePtrx ");

  GetSortedGenUnmappedLtrxList(&sortedGenUnmappedLtrxList,&sortedGenUnmappedLtrxRecsNum);

  for (nLtrxTableRowNum = 0; nLtrxTableRowNum < sortedGenUnmappedLtrxRecsNum ; nLtrxTableRowNum++)
  {
	currLtrxRec = (LtrxTableApi*)((I_U8*)sortedGenUnmappedLtrxList + (nLtrxTableRowNum * sizeof(LtrxTableApi)) );
	//LOG_PRINT(DEBUG,"currLtrxRec->ltrxId=%d",currLtrxRec->ltrxId);

	/* Create the channel group indice */ 
	chnGrpTableIndice.chnGrpId = currLtrxRec->chnGrpId ;
	chnGrpTableIndice.cellId = currLtrxRec->cellId;
	chnGrpTableIndice.lac = currLtrxRec->lac;

	errCode = getAllLtrxForCellH(currLtrxRec->cellId, currLtrxRec->lac, &tmpLtrxRec, &tmpRecCnt, &tmpRecSize);

	/* if (errCode != CLIB_SUCCESS)  Intentionally done*/ 
	for(tmpCnt=0; tmpCnt<tmpRecCnt; ++tmpCnt)
	{
	  if((currLtrxRec->ltrxId != tmpLtrxRec[tmpCnt].ltrxId) && 
		  (tmpLtrxRec[tmpCnt].mappingStatus != MAPPED) && 
		  (currLtrxRec->ltrxPriority < tmpLtrxRec[tmpCnt].ltrxPriority) )
	  {
		LOG_PRINT(DEBUG,"currLtrxId=%d,currLtrxPrio=%d,tmpLtrx[%d].ltrxId=%d,tmpLtrx[%d].mappingStatus=%d,tmpLtrx[%d].ltrxPriority=%d",currLtrxRec->ltrxId, currLtrxRec->ltrxPriority, tmpCnt, tmpLtrxRec[tmpCnt].ltrxId, tmpCnt, tmpLtrxRec[tmpCnt].mappingStatus,  tmpCnt, tmpLtrxRec[tmpCnt].ltrxPriority );
		break;
	  }
	}//for
	free(tmpLtrxRec);

	if(tmpCnt == tmpRecCnt)
	{
	  /* Retrieve the chn grp record for the indice created */
	  errCode = getChnGrpTable(&chnGrpTableIndice,chnGrpTableRec);

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(INFO, "Retrieval fail from Channel Group Table:err=%s", clib_strerror(errCode));             
		free(sortedGenUnmappedLtrxList);
		return I_FALSE;
	  }

	  /* Finding the Ptrx whose MapAllowed="yes" but that is not mapped to any Ltrx. */
	  isFound = FindSuitableUnmappedPtrxWithMapAllowed(&suitablePtrxId,currLtrxRec,*chnGrpTableRec);

	  if (isFound)
	  {             
		*ptrxId = suitablePtrxId;
		memcpy(genUnamppedLtrxRec,currLtrxRec,sizeof(LtrxTableApi));

		free(sortedGenUnmappedLtrxList);
		*IsUnmappedPtrx = I_TRUE;             

		LOG_PRINT(DEBUG, "Exiting Func-FindLtrxWithSuitablePtrx:Found Unmapped Ptrx with PtrxId=%d for LtrxId=%d",*ptrxId,genUnamppedLtrxRec->ltrxId);
		return I_TRUE;
	  }

	  else /*No Unmapped Ptrx found */
	  {
		isFound = IsDemappingAlreadyInitiated(currLtrxRec,*chnGrpTableRec);
		if(isFound == I_TRUE)
		{
		  LOG_PRINT(INFO,"Suitable [ltrxId:%d] with status UNMAPINITIATED found for mapping",currLtrxRec->ltrxId);
		  free(*chnGrpTableRec);
		  continue;
		}

		/*
		   Finding out mapped Ltrx (complete LtrxTable Record) which has lower priority than current                                  Ltrx.In case more than 1 Ltrx is found it will choose the lowest priority Ltrx.  This will
		   also make sure that the returned Ltrx record which is attached to the Ptrx and is suitable
		   for current Ltrx requirement. 
		 */

		*lowerPrtLtrxRec = (LtrxTableApi*)malloc(sizeof(LtrxTableApi));

		isFound = FindGenMappedLowestPriorityLtrxRecord(currLtrxRec,*lowerPrtLtrxRec,*chnGrpTableRec) ;

		if(isFound)
		{
		  memcpy(genUnamppedLtrxRec,currLtrxRec,sizeof(LtrxTableApi));
		  free(sortedGenUnmappedLtrxList);
		  *IsUnmappedPtrx = I_FALSE;                             
		  LOG_PRINT(DEBUG, "Exiting Func-FindLtrxWithSuitablePtrx:Found Mapped PtrxId=%d for LtrxId=%d",(*lowerPrtLtrxRec)->ptrxId,currLtrxRec->ltrxId);
		  return I_TRUE;
		}

		/* Fix Mantis - 5833 : starts */
		free(*chnGrpTableRec);
		free(*lowerPrtLtrxRec);
	  }
	}//if 
  }
  if (sortedGenUnmappedLtrxRecsNum > 0)
  {
	free(sortedGenUnmappedLtrxList);
  }
  LOG_PRINT(DEBUG, "Exit func FindLtrxWithSuitablePtrx ");
  return I_FALSE;

}


/***********************************************************************************
 *  Function Name   : FindGenMappedLowestPriorityLtrxRecord
 *
 *  Args            : 1. Ltrx Record pointer (IN)
 *                    2. Lower priority ltrx record pointer (OUT)
 *                    3. Channel group table pointer (IN) 
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds a generated and mapped lower priority ltrx record in
 comparsion with the ltrx record that is currently generated and 
 *                    unmapped. 
 ***********************************************************************************/

I_Bool FindGenMappedLowestPriorityLtrxRecord (LtrxTableApi *ltrxCurrRec, 
	LtrxTableApi* ltrxLowerPriorityRec,
	ChnGrpTableApi     *chnGrpTableRec 
	) 
{
  LtrxTableApi     *ltrxTableOutData;

  I_U32            nLtrxTableRowNum;
  I_U32            ltrxTableOutRows;
  I_U16            ltrxTableOutSize;
  I_S32            isPtrxSuitable;
  I_S32            errCode;
  I_Bool           ltrxRecFound          = I_FALSE;
  I_U32            currLtrxPriority          = 0;   
  I_U32            ltrxRowDataPriority       = 0;   
  LtrxTableApi     *ltrxTableRowData     = NULL;


  LOG_PRINT(DEBUG, "In FindGenMappedLowestPriorityLtrxRecord");

  currLtrxPriority = ltrxCurrRec->ltrxPriority;

  /* Get all the rows from the ltrx table */
  errCode = getallLtrxTable(&ltrxTableOutData, &ltrxTableOutRows, &ltrxTableOutSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval all failed from LtrxTable:err=%s", clib_strerror(errCode));
	return I_FALSE;
  }

  for( nLtrxTableRowNum =0; nLtrxTableRowNum < ltrxTableOutRows ; nLtrxTableRowNum++ )
  {

	ltrxTableRowData = (LtrxTableApi*)((I_U8*)ltrxTableOutData + (nLtrxTableRowNum * ltrxTableOutSize ));

	if ( ltrxTableRowData->mappingStatus == MAPPED && ltrxTableRowData->generationStatus == GENERATED )
	{
	  ltrxRowDataPriority = ltrxTableRowData->ltrxPriority;

	  if (ltrxRowDataPriority < MAX_PRIORITY && ltrxRowDataPriority < currLtrxPriority)
	  {    
		//isPtrxSuitable = GetPtrxSuitability(ltrxCurrRec->ptrxId, ltrxTableRowData,chnGrpTableRec);
		isPtrxSuitable = GetPtrxSuitability(ltrxTableRowData->ptrxId,ltrxCurrRec,chnGrpTableRec); 

		if ( isPtrxSuitable )
		{
		  /*  Code added to find lowest priority record   */
		  currLtrxPriority = ltrxRowDataPriority ;
		  /* End of change to find lowest priority record  */
		  memcpy(ltrxLowerPriorityRec ,ltrxTableRowData, sizeof(LtrxTableApi));

		  LOG_PRINT(INFO, "Ltrx record found in FindGenMappedLowestPriorityLtrxRecord,LtrxId=%d",ltrxLowerPriorityRec->ltrxId );
		  ltrxRecFound = I_TRUE;
		}
	  }            
	}
  }   
  /*
	 LOG_PRINT(DEBUG, "Exit func FindGenMappedLowestPriorityLtrxRecord");
   */
  free(ltrxTableOutData);
  return ltrxRecFound;   
}
/***********************************************************************************
 *  Function Name   : FindMappedCleaningDownLtrx
 *
 *  Args            : 1.Ltrx Record pointer (IN)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Finds a ltrx which is in mapped and clean down state.
 ***********************************************************************************/

I_Bool FindMappedCleaningDownLtrx ( LtrxTableApi* ltrxRec )
{
  I_U32        ltrxTableOutRows;
  I_U16        ltrxTableOutSize;
  LtrxTableApi *ltrxTableRowData  = NULL;
  LtrxTableApi *ltrxTableOutData;
  I_U32         nLtrxTableRowNum;
  I_S32         errCode;


  LOG_PRINT(DEBUG, "In FindMappedCleaningDownLtrx");
  errCode = getallLtrxTable (&ltrxTableOutData, &ltrxTableOutRows,&ltrxTableOutSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval all failed from LtrxTable:err=%s", clib_strerror(errCode));
	return I_FALSE;
  }

  for( nLtrxTableRowNum = 0; nLtrxTableRowNum < ltrxTableOutRows ; nLtrxTableRowNum++ )
  {
	ltrxTableRowData = (LtrxTableApi*)((I_U8*)ltrxTableOutData + (nLtrxTableRowNum * ltrxTableOutSize));

	//if ( ltrxTableRowData->mappingStatus == MAPPED && ltrxTableRowData->generationStatus ==  CLEAN_DOWN )
	if ( ((ltrxTableRowData->mappingStatus == MAPPED) || (ltrxTableRowData->mappingStatus == CREATE_IN_PROGRESS)) && 
		ltrxTableRowData->generationStatus ==  CLEAN_DOWN )
	{
	  //ltrxRec = (LtrxTableApi*)malloc(sizeof(LtrxTableApi));
	  memcpy(ltrxRec ,ltrxTableRowData, sizeof(LtrxTableApi));
	  LOG_PRINT(INFO, "Exiting Func-FindMappedCleaningDownLtrx:Ltrx record found in FindMappedCleaningDownLtrx, LtrxId=%d",ltrxRec->ltrxId );

	  free(ltrxTableOutData);
	  return I_TRUE;
	}      
  }

  LOG_PRINT(DEBUG, "Exiting Func-FindMappedCleaningDownLtrx: Ltrx record not found ");
  free(ltrxTableOutData);
  return I_FALSE;   
}

/***********************************************************************************
 *  Function Name   : IsLtrxCleaningDown
 *
 *  Args            : 1. ltrx Id (IN)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Checks whether the given ltrx is in clean down state or not.
 ***********************************************************************************/

I_Bool IsLtrxCleaningDown( I_U32 ltrxId )
{
  LtrxTableIndices ltrxIdIndice;
  LtrxTableApi     *ltrxIdRowData;
  I_S32            errCode;

  LOG_PRINT(DEBUG, "In IsLtrxCleaningDown");

  /* Fill the ltrx id for which the record has to be retreived */
  ltrxIdIndice.ltrxId = ltrxId;

  /* Get the Ltrx record for the specified Ltrx Id */
  errCode = getLtrxTable (&ltrxIdIndice, &ltrxIdRowData );

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Retrieval fail from LtrxTable:err=%s", clib_strerror(errCode));
	return I_FALSE;
  }

  if (ltrxIdRowData->generationStatus == CLEAN_DOWN)
  {
	free(ltrxIdRowData);
	LOG_PRINT(DEBUG, "Exiting Func-IsLtrxCleaningDown:Found ltrx record in cleaning down state");
	return I_TRUE;
  }
  else
  {
	free(ltrxIdRowData);

	LOG_PRINT(DEBUG, "Exiting Func-IsLtrxCleaningDown: Not found ltrx record in cleaning down state");
	return I_FALSE;
  }
}
/***********************************************************************************
 *  Function Name   : GetAssociatedLtrx
 *
 *  Args            : 1. ptrx Id (IN)
 *                    2. ltrx record pointer (OUT)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Retrieves the Ltrx record for a given ptrx. 
 ***********************************************************************************/

I_Bool GetAssociatedLtrx(I_U32 ptrxId, LtrxTableApi **ltrxRec1)
{
  LtrxTableTerIndices ltrxTableTerIndice;
  I_U32               errCode;
  I_U32               outCount;
  I_U16               outSize;
  I_U32               i;
  I_U32               mappedCount=0;
  LtrxTableApi 			 *ltrxRec;


  LOG_PRINT(DEBUG, "In GetAssociatedLtrx");

  ltrxTableTerIndice.ptrxId = ptrxId;

  errCode = getTerLtrxTable(&ltrxTableTerIndice, &ltrxRec, &outCount,&outSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "Exiting Func-GetAssociatedLtrx:Retrieval fail from LtrxTable:err=%s", clib_strerror(errCode));
	return I_FALSE;
  }
  *ltrxRec1 = (LtrxTableApi *) malloc(sizeof(LtrxTableApi));
  if(outCount >= 1)
  {

	for(i=0;i<outCount;++i)
	{
	  if((ltrxRec)[i].mappingStatus == MAPPED)
	  {
		memcpy(*ltrxRec1, &(ltrxRec[i]), sizeof(LtrxTableApi));
		mappedCount++; 
		LOG_PRINT(INFO,"1.ptrxId=%d ltrxId=%d MAPPED(%d)",ptrxId,(ltrxRec)[i].ltrxId,(ltrxRec)[i].mappingStatus);
	  }
	  else
	  {
		LOG_PRINT(INFO,"1.ptrxId=%d ltrxId=%d NOTMAPPED(%d)",ptrxId,(ltrxRec)[i].ltrxId,(ltrxRec)[i].mappingStatus);
	  }
	}
	free(ltrxRec);
	ltrxRec = NULL;
	if(mappedCount > 1)
	{
	  LOG_PRINT(DEBUG, "1.Exit func GetAssociatedLtrx1 mappedCount(%d)",mappedCount);
	  LOG_PRINT(DEBUG, "Exiting CELLH Module");
	  exit(0);
	}

  }//if

  /*
	 LOG_PRINT(DEBUG, " Exit func GetAssociatedLtrx");
   */

  return I_TRUE; 
}

I_Bool GetAssociatedLtrx1(I_U32 ptrxId, LtrxTableApi **ltrxRec)
{
  LtrxTableTerIndices ltrxTableTerIndice;
  I_U32               errCode;
  I_U32               outCount;
  I_U32               mappedCount=0;
  I_U16               outSize;
  I_S32               i;


  LOG_PRINT(DEBUG, "In GetAssociatedLtrx1");

  ltrxTableTerIndice.ptrxId = ptrxId;

  errCode = getTerLtrxTable(&ltrxTableTerIndice, ltrxRec, &outCount,&outSize);

  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(INFO, "1.Retrieval fail from LtrxTable:err=%s", clib_strerror(errCode));

	LOG_PRINT(DEBUG, "1.Exit func GetAssociatedLtrx1");
	return I_FALSE;
  }
  if(outCount > 1)
  {
	for(i=0;i<outCount;++i)
	{
	  if((*ltrxRec)[i].mappingStatus == MAPPED)
	  {
		mappedCount++; 
		LOG_PRINT(INFO,"1.ptrxId=%d ltrxId=%d MAPPED(%d)",ptrxId,(*ltrxRec)[i].ltrxId,(*ltrxRec)[i].mappingStatus);
	  }
	  else
	  {
		LOG_PRINT(INFO,"1.ptrxId=%d ltrxId=%d NOTMAPPED(%d)",ptrxId,(*ltrxRec)[i].ltrxId,(*ltrxRec)[i].mappingStatus);
	  }
	}
	if(mappedCount > 1)
	{
	  LOG_PRINT(DEBUG, "1.Exit func GetAssociatedLtrx1 mappedCount(%d)",mappedCount);
	  exit(0);
	}
  }
  /* LOG_PRINT(DEBUG, " Exit func GetAssociatedLtrx"); */

  return I_TRUE; 
}
/***********************************************************************************
 *  Function Name   : IsDemappingAlreadyInitiated
 *
 *  Args            : 1. Ltrx Record (IN)
 *
 *  Returns         : Demap Initiated Record Fourd or Not Found.
 *
 *  Task            : Checks if mapping Algo has already Initiated De-mapping of lower
 priority Ltrx in order to get Unmapped Ptrx for higher priority
 Ltrx.
 ***********************************************************************************/

I_Bool IsDemappingAlreadyInitiated(LtrxTableApi *ltrxRec,ChnGrpTableApi *chnGrpTableRec)
{
  LtrxTableApi     *ltrxTableOutData     = NULL;
  LtrxTableApi     *ltrxTableRowData     = NULL;
  I_U8              mapAllowed           = I_FALSE;
  I_U32             nLtrxTableRowNum     = 0;
  I_U32             ltrxTableOutRows     = 0;
  I_U16             ltrxTableOutSize     = 0;
  I_S32             isPtrxSuitable       = I_FALSE;
  I_S32             errCode              = 0;

  LOG_PRINT(INFO,"In IsDemappingAlreadyInitiated");

  errCode = getallLtrxTable(&ltrxTableOutData,&ltrxTableOutRows,&ltrxTableOutSize);
  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(MAJOR,"Get all Ltrx Table call failed:Exiting Func-IsDemappingAlreadyInitiated");
	return I_FALSE ;
  }

  for(nLtrxTableRowNum = 0 ; nLtrxTableRowNum < ltrxTableOutRows ; nLtrxTableRowNum++)
  {
	ltrxTableRowData = (LtrxTableApi *)( ((I_U8 *)ltrxTableOutData + nLtrxTableRowNum * ltrxTableOutSize) ) ;

	if(ltrxTableRowData->mappingStatus == UNMAPINITIATED)
	{
	  errCode = getPtrxMappableStatus(ltrxTableRowData->ptrxId, &mapAllowed) ;
	  if(errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exiting Func-IsDemappingAlreadyInitiated:Couldn't retrieve Ptrx Record from Db for [ptrxId:%d]",ltrxTableRowData->ptrxId);
		free(ltrxTableOutData);
		return I_FALSE;
	  }
	  if(mapAllowed == I_TRUE)
	  {
		isPtrxSuitable = GetPtrxSuitability(ltrxTableRowData->ptrxId,ltrxRec,chnGrpTableRec);

		if(isPtrxSuitable == I_TRUE)
		{
		  LOG_PRINT(INFO,"Exiting Func-IsDemappingAlreadyInitiated:Found UNMAPINITIATED [ltrxId:%d] mapped with [ptrxId:%d]",ltrxTableRowData->ltrxId, ltrxTableRowData->ptrxId); 
		  free(ltrxTableOutData);
		  return I_TRUE ;
		}
	  }
	}
  }
  free(ltrxTableOutData);
  /*
	 LOG_PRINT(INFO,"Exiting Function IsDemappingAlreadyInitiated");
   */
  return I_FALSE ;
}

/* CS4.0 : ABIS_E1_LOCK_UNLOCK Change : Starts */

/***********************************************************************************
 *  Function Name   : ValidateE1OfPtrx
 *
 *  Args            : 1. Ptrx Id (IN)
 *
 *  Returns         : On Successful Validation returns TRUE or FALSE
 *
 *  Task            : This function validates E1 of the Ptrx getting Mapped.
 ***********************************************************************************/
I_Bool ValidateE1OfPtrx( I_U32 ptrxId )
{
  I_S32  errCode  = 0;
  I_U32  ptrxE1InDb = INVALID_E1;
  I_U32  ptrxE1StatusInDb = INVALID_E1;
  TrxTableIndices                        trxTableIndices;
  TrxTableApi                            *trxTableRowData = NULL;

  LOG_PRINT(INFO,"In ValidateE1OfPtrx");

  trxTableIndices.ptrxId=ptrxId; /*Changes for R2.8*/ 
  errCode = getTrxTable(&trxTableIndices, &trxTableRowData);
  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(MAJOR,"Exiting Func-ValidateE1OfPtrx:getTrxTable Call Failed");
	return I_FALSE ;
  }
  else
  {
	if((trxTableRowData->trxLocation==TRX_LOCATION_R2_BTS_IP)||(trxTableRowData->trxLocation==TRX_LOCATION_R3_BTS))
	{
	  LOG_PRINT(DEBUG,"TRX is R2_BTS_IP/R3_BTS type with ptrx ID %d ",ptrxId);
	  free(trxTableRowData);  
	  return I_TRUE;  
	}  
  }  

  errCode = getE1ofSuitablePtrx(ptrxId,&ptrxE1InDb,&ptrxE1StatusInDb);
  if (errCode != CLIB_SUCCESS)
  {
	LOG_PRINT(MAJOR,"Exiting Func-ValidateE1OfPtrx:getE1OfSuitablePtrx Call Failed");
	return I_FALSE ;
  }
  if ( ptrxE1InDb == INVALID_E1 || ptrxE1StatusInDb == INVALID_E1 )
  {
	LOG_PRINT(INFO,"Exiting Func-ValidateE1OfPtrx:PTRX-Id[%d] does not lie on any configured E1 or in Transient E1Status Table",ptrxId);
	return I_FALSE; 
  }
  else
  {
	if ( ptrxE1StatusInDb == UNLOCKED || ptrxE1StatusInDb == UNLOCKINPROGRESS ) 
	{
	  LOG_PRINT(INFO,"Exiting Func-ValidateE1OfPtrx:PTRX-Id[%d] is mapped on E1-Id[%d] which is either in UNLOCKED or UNLOCK-IN-PROGRESS state",ptrxId,ptrxE1InDb);         
	  return I_TRUE;          
	}
	else
	{
	  LOG_PRINT(INFO,"Exiting Func-ValidateE1OfPtrx:PTRX-Id[%d] is mapped on E1-Id[%d] which is either in LOCKED or LOCK-IN-PROGRESS state",ptrxId,ptrxE1InDb);         
	  return I_FALSE;          
	} 
  } 
  /* CS4.0 : ABIS_E1_LOCK_UNLOCK Change : Ends */
}

/***********************************************************************************
 *  Function Name   : MappingLtrxPtrxEntity
 *
 *  Args            : 1. invocation mode (IN) 
 *                    2. message pointer (IN)
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : Performs the core functionality of mapping a Ltrx to a ptrx.
 ***********************************************************************************/

I_Bool MappingLtrxPtrxEntity(I_U16 invocationMode, I_PVoid dataPtr)
{
  ChnGrpTableApi     *chnGrpTableRec        = NULL;
  LtrxTableApi       *ltrxRec               = NULL;
  LtrxTableApi       *ltrxRec1              = NULL;
  LtrxTableApi       *lowerPrtLtrxRec       = NULL;

  I_U8                ptrxMappingStatus ;
  I_U8                ltrxMappingStatus ;
  I_S32               msgCreStatus;
  I_S32               running ;
  I_S32               isCleaning;
  I_U32               ltrxId;
  I_U32               isFound;
  I_U32               ptrxId;
  I_Bool              IsUnmappedPtrx;
  I_S32               errCode              = 0;
  PtrxTableIndices    tmpPtrxTableIndices;
  PtrxTableApi        *tmpPtrxTableApi;
  I_U32               tmpStatus,tmpLtrxSts,tmpPtrx; 


  LOG_PRINT(INFO,"Mapping Algorithm Invoked");

  /* Handling of  OAMS_MAPENT_CELLH_DEL_MAP_RESP for the both the cases (either due to Ptrx going down or Cell Lock */
  if (invocationMode == OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP)         
  {         

	LOG_PRINT(DEBUG,"Rcvd the msg OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP");
	if ( dataPtr != NULL )
	{
	  tmpPtrxTableIndices.ptrxId = ((OamsTrxhMapentDelLtrxPtrxMappingResp*)(dataPtr))->ptrxId;
	  errCode = getPtrxTable(&tmpPtrxTableIndices, &tmpPtrxTableApi);
	  ltrxId = ((OamsTrxhMapentDelLtrxPtrxMappingResp*)(dataPtr))->ltrxId;
	  if(errCode == CLIB_SUCCESS)
	  {
		tmpStatus =  tmpPtrxTableApi->mappingStatus;
		free(tmpPtrxTableApi);
		/* START Only for R2.3.3. Static Mapping Code: Ptrx initialized, Ltrx Unmapinitiated */
		LtrxTableIndices       ltrxTableIndice;
		ltrxTableIndice.ltrxId = ltrxId;
		errCode = getLtrxTable(&ltrxTableIndice,&ltrxRec);
		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"getLtrxTable failed : err = %s ltrxId(%d) ptrxId(%d)",
			  clib_strerror(errCode),ltrxId,tmpPtrxTableIndices.ptrxId);
		}
		else
		{
		  tmpLtrxSts = ltrxRec->mappingStatus;
		  tmpPtrx = ltrxRec->ptrxId;
		  free(ltrxRec);
		  ltrxRec = NULL;
		  LOG_PRINT(DEBUG,"ltrxId(%d) tltrxMapSts(%d) tptrxId(%d) ptrxId(%d) tPtrxSts(%d)",
			  ltrxId, tmpLtrxSts, tmpPtrx, tmpPtrxTableIndices.ptrxId, tmpStatus);
		}
		/* END Only for R2.3.3. Static Mapping Code  : Ptrx initialized, Ltrx Unmapinitiated */
		if((tmpStatus == DELETE_IN_PROGRESS) && ((tmpLtrxSts == UNMAPINITIATED)  && (tmpPtrx == tmpPtrxTableIndices.ptrxId)))
		{
		  ltrxMappingStatus = UNMAPPED ;
		  ltrxId = ((OamsTrxhMapentDelLtrxPtrxMappingResp*)(dataPtr))->ltrxId;
		  errCode = updateLtrxMappingStatus(ltrxId, ltrxMappingStatus) ;

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"UpdateLtrxMappingStatus call failed : err = %s",clib_strerror(errCode));
			return I_FALSE ;
		  }

		  LOG_PRINT(DEBUG, "LtrxId Unmapped is=%d",ltrxId);
		  ptrxMappingStatus = UNMAPPED ;
		  ptrxId = ((OamsTrxhMapentDelLtrxPtrxMappingResp*)(dataPtr))->ptrxId;
		  //Temporarily uncommented for testing
		  errCode = updatePtrxMappingStatus(ptrxId, ptrxMappingStatus) ;

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"Exit Func MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
			return I_FALSE ;
		  }

		  GetAssociatedLtrx1(ptrxId, &ltrxRec1);
		  free(ltrxRec1);
		  ltrxRec1 = NULL;

		  /* Putting the PtrxId in Ltrx Record in LtrxTable. */
		  errCode = updatePtrxIdInLtrxTable(INVALID_PTRXID,ltrxId);

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"Exit Func MappingLtrxPtrxEntity:UpdatePtrxIdInLtrxTable call failed:err=%s", clib_strerror(errCode));
			return I_FALSE ;
		  }

		  LOG_PRINT(DEBUG, "PtrxId Unmapped is=%d",ptrxId);

		  DalocMsgBuf(dataPtr);
		}
		else
		{
		  LOG_PRINT(MAJOR,"Consistency check failed while handling DEL_LTRX_PTRX_MAPPING_RESP");
		}
	  }
	}
	else
	{                   
	  LOG_PRINT(CRITICAL,"Exiting Mapping Algo:DataPtr is NULL in OAMS_TRXH_MAPENT_DEL_LTRX_PTRX_MAPPING_RESP");
	  return I_FALSE;
	}

	/* 
	   Checking if delete was initiated because of Cell Lock or Ptrx going Down.
	   In case of CellLock Mapping Status should be "Cleaning" 
Note: In case of Cell Shutdown no separate message is received by mapping entity
algo
	 */
	isCleaning = IsLtrxCleaningDown(ltrxId) ;

	if (isCleaning)
	{
	  msgCreStatus = CreateMsgMapentCellhDelMapResp(ltrxId);

	  if (msgCreStatus != MSG_SUCCESS)                   
	  {         
		LOG_PRINT(CRITICAL, "Exiting Mapping Algo:Creation of OAMS_MAPENT_CELLH_DEL_MAP_RESP failed");         
		return I_FALSE;
	  }         
	}
  }
  else if (invocationMode ==OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED)
  {
	LOG_PRINT(DEBUG,"Rcvd the msg OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED");

	LtrxTableIndices       ltrxTableIndice;
	I_S32                  errCode;

	ltrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ltrxId;

	ltrxTableIndice.ltrxId = ltrxId;

	errCode = getLtrxTable(&ltrxTableIndice,&ltrxRec);

	if (errCode != CLIB_SUCCESS)
	{
	  LOG_PRINT(MAJOR, "Retrieval fail from LtrxTable for [ltrxId:%d]err=%s",ltrxId,clib_strerror(errCode));
	  /* Required only for R2.3.3 static mapping START */
	  tmpPtrxTableIndices.ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
	  errCode = getPtrxTable(&tmpPtrxTableIndices, &tmpPtrxTableApi);
	  if(errCode == CLIB_SUCCESS)
	  {
		tmpStatus =  tmpPtrxTableApi->mappingStatus;
		free(tmpPtrxTableApi);
		if(tmpStatus == CREATE_IN_PROGRESS)
		{
		  ptrxMappingStatus = UNMAPPED ;
		  ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
		  errCode = updatePtrxMappingStatus(ptrxId, ptrxMappingStatus) ;

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"CRE-FAIL-NO-LTRX UpdatePtrxMappingStatus call failed:err=%s EXIT MappingLtrxPtrxEntity",clib_strerror(errCode));
			DalocMsgBuf(dataPtr);
			return I_FALSE ;
		  }
		  LOG_PRINT(DEBUG, "CRE-FAIL-NO-LTRX PtrxId Unmapped is=%d ",ptrxId);
		}//if(tmpStatus == CREATE_IN_PROGRESS)
	  }
	  /* Required only for R2.3.3 static mapping ENDS */
	  DalocMsgBuf(dataPtr);
	  return I_FALSE;
	}

	if(ltrxRec->mappingStatus == UNMAPINITIATED)
	{ 
	  LOG_PRINT(INFO,"Found [ltrxId:%d]record with UNMAPINITIATED for which OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_FAILED is rcvd",ltrxId);   
	  /* Temp changes for reverting intermediate status of 
	   * ptrx.mappingStatus=5 , in case CreateLtrxPtrxMapp failed . 
	   * This intermediate status is set at the time of unmapping lower priority ltrx.
	   * Note that , del ltrx ptrx is sent during unmapping of low priority trx but it is not handled at trxh when create is failed. */
	  tmpPtrxTableIndices.ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
	  errCode = getPtrxTable(&tmpPtrxTableIndices, &tmpPtrxTableApi);
	  if(errCode == CLIB_SUCCESS)
	  {
		tmpStatus =  tmpPtrxTableApi->mappingStatus;
		free(tmpPtrxTableApi);
		if(tmpStatus == DELETE_IN_PROGRESS)
		{
		  ltrxMappingStatus = UNMAPPED ;
		  errCode = updateLtrxMappingStatus(ltrxId, ltrxMappingStatus) ;      

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"A. Exit Func MappingLtrxPtrxEntity:UpdateLtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
			return I_FALSE ;
		  }

		  LOG_PRINT(DEBUG, "A. LtrxId Unmapped is=%d",ltrxId);
		  ptrxMappingStatus = UNMAPPED ;
		  ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
		  errCode = updatePtrxMappingStatus(ptrxId, ptrxMappingStatus) ;

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"A. Exit Func MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
			return I_FALSE ;
		  }

		  GetAssociatedLtrx1(ptrxId, &ltrxRec1);
		  free(ltrxRec1);
		  ltrxRec1 = NULL;
		  /* Putting the PtrxId in Ltrx Record in LtrxTable. */
		  errCode = updatePtrxIdInLtrxTable(INVALID_PTRXID,ltrxId);

		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"A. Exit Func MappingLtrxPtrxEntity:UpdatePtrxIdInLtrxTable call failed:err=%s",clib_strerror(errCode));
			//LOG_PRINT(INFO,"A. Exiting Function MappingLtrxPtrxEntity");
			return I_FALSE ;
		  }

		  LOG_PRINT(DEBUG, "A. PtrxId Unmapped is=%d",ptrxId);
		}
	  }
	}
	else if(ltrxRec->mappingStatus == CREATE_IN_PROGRESS)
	{
	  ltrxMappingStatus = UNMAPPED ;
	  errCode = updateLtrxMappingStatus(ltrxId, ltrxMappingStatus) ;      
	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"UpdateLtrxMappingStatus call failed:err=%s EXIT MappingLtrxPtrxEntity",clib_strerror(errCode));
		free(ltrxRec);
		ltrxRec = NULL;
		DalocMsgBuf(dataPtr);
		return I_FALSE ;
	  }
	  LOG_PRINT(DEBUG, "CIP:LtrxId Unmapped is=%d",ltrxId);

	  tmpPtrxTableIndices.ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
	  errCode = getPtrxTable(&tmpPtrxTableIndices, &tmpPtrxTableApi);
	  if(errCode == CLIB_SUCCESS)
	  { 
		tmpStatus =  tmpPtrxTableApi->mappingStatus;
		free(tmpPtrxTableApi);
		if(tmpStatus == CREATE_IN_PROGRESS)
		{
		  ptrxMappingStatus = UNMAPPED ;
		  //ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
		  errCode = updatePtrxMappingStatus(tmpPtrxTableIndices.ptrxId, ptrxMappingStatus) ;
		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"UpdatePtrxMappingStatus call failed:err=%s EXIT MappingLtrxPtrxEntity",clib_strerror(errCode));
			free(ltrxRec);
			ltrxRec = NULL;
			DalocMsgBuf(dataPtr);
			return I_FALSE ;
		  }
		  LOG_PRINT(DEBUG, "CIP:PtrxId Unmapped is=%d",tmpPtrxTableIndices.ptrxId);
		}//if(tmpStatus == CREATE_IN_PROGRESS)
	  }

	  errCode = updatePtrxIdInLtrxTable(INVALID_PTRXID,ltrxId);

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"UpdatePtrxIdInLtrxTable call failed:err=%s EXIT MappingLtrxPtrxEntity",clib_strerror(errCode));
		free(ltrxRec);
		ltrxRec = NULL;
		DalocMsgBuf(dataPtr);
		return I_FALSE ;
	  }
	  LOG_PRINT(DEBUG, "CIP:Updated PtrxId=%d in LtrxTable(Ltrx=%d)",tmpPtrxTableIndices.ptrxId,ltrxId);

	}//if(ltrxRec->mappingStatus == CREATE_IN_PROGRESS)
	else
	{
	  /* 
		 Revert backing the Mapping status of Ptrx & Ltrx to UNMAPPED which was set to 
		 MAPPED when OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_IND was sent 
	   */
	  ltrxMappingStatus = UNMAPPED ;
	  errCode = updateLtrxMappingStatus(ltrxId, ltrxMappingStatus) ;      

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdateLtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		return I_FALSE ;
	  }

	  LOG_PRINT(DEBUG, "LtrxId Unmapped is =%d",ltrxId);
	  ptrxMappingStatus = UNMAPPED ;
	  ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
	  errCode = updatePtrxMappingStatus(ptrxId, ptrxMappingStatus) ;

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		return I_FALSE ;
	  }

	  GetAssociatedLtrx1(ptrxId, &ltrxRec1);
	  free(ltrxRec1);
	  ltrxRec1 = NULL;
	  /* Putting the PtrxId in Ltrx Record in LtrxTable. */
	  errCode = updatePtrxIdInLtrxTable(INVALID_PTRXID,ltrxId);

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdatePtrxIdInLtrxTable call failed:err=%s",clib_strerror(errCode));
		return I_FALSE ;
	  }

	  LOG_PRINT(DEBUG, "PtrxId Unmapped is=%d ",ptrxId);
	}//else
	free(ltrxRec);
	//Temp change due to CELLH crash
	ltrxRec = NULL;
	DalocMsgBuf(dataPtr);
  }
  /* Added on 23-Jun-2010 Only for R2.3.3 Static Mapping */
  else if (invocationMode ==OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP)
  {
	LOG_PRINT(DEBUG,"Rcvd the msg OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP");

	LtrxTableIndices       ltrxTableIndice;
	I_S32                  errCode;

	ltrxId = ((OamsTrxhMapentCreLtrxPtrxMappingResp*)(dataPtr))->ltrxId;

	ltrxTableIndice.ltrxId = ltrxId;

	errCode = getLtrxTable(&ltrxTableIndice,&ltrxRec);

	if (errCode != CLIB_SUCCESS)
	{
	  LOG_PRINT(MAJOR, "Retrieval fail from LtrxTable for [ltrxId:%d]err=%s",ltrxId,clib_strerror(errCode));
	  DalocMsgBuf(dataPtr);
	  return I_FALSE;
	}

	if(ltrxRec->mappingStatus == CREATE_IN_PROGRESS)
	{
	  ltrxMappingStatus = MAPPED ;
	  errCode = updateLtrxMappingStatus(ltrxId, ltrxMappingStatus) ;      
	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"UpdateLtrxMappingStatus call failed:err=%s EXIT MappingLtrxPtrxEntity",clib_strerror(errCode));
		DalocMsgBuf(dataPtr);
		free(ltrxRec);
		ltrxRec = NULL;
		return I_FALSE ;
	  }
	  LOG_PRINT(DEBUG, "C-RESP:LtrxId Mapped is=%d",ltrxId);

	  tmpPtrxTableIndices.ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingResp*)(dataPtr))->ptrxId;
	  errCode = getPtrxTable(&tmpPtrxTableIndices, &tmpPtrxTableApi);
	  if(errCode == CLIB_SUCCESS)
	  { 
		tmpStatus =  tmpPtrxTableApi->mappingStatus;
		free(tmpPtrxTableApi);
		if(tmpStatus == CREATE_IN_PROGRESS)
		{
		  ptrxMappingStatus = MAPPED ;
		  //ptrxId = ((OamsTrxhMapentCreLtrxPtrxMappingFailed*)(dataPtr))->ptrxId;
		  errCode = updatePtrxMappingStatus(tmpPtrxTableIndices.ptrxId, ptrxMappingStatus) ;
		  if (errCode != CLIB_SUCCESS)
		  {
			LOG_PRINT(MAJOR,"UpdatePtrxMappingStatus call failed:err=%s EXIT MappingLtrxPtrxEntity",clib_strerror(errCode));
			DalocMsgBuf(dataPtr);
			free(ltrxRec);
			ltrxRec = NULL;
			return I_FALSE ;
		  }
		  LOG_PRINT(DEBUG, "C-RESP:PtrxId Mapped is=%d",tmpPtrxTableIndices.ptrxId);
		}//if(tmpStatus == CREATE_IN_PROGRESS)
	  }

#if 0
	  errCode = updatePtrxIdInLtrxTable(INVALID_PTRXID,ltrxId);

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"UpdatePtrxIdInLtrxTable call failed : err = %s",clib_strerror(errCode));
		LOG_PRINT(INFO,"Exiting Function MappingLtrxPtrxEntity");
		return I_FALSE ;
	  }
	  LOG_PRINT(DEBUG, "C-RESP:Updated PtrxId = %d in LtrxTable (Ltrx = %d )",tmpPtrxTableIndices.ptrxId,ltrxId);
#endif

	}//if(ltrxRec->mappingStatus == CREATE_IN_PROGRESS)
	free(ltrxRec);
	//Temp change due to CELLH crash
	ltrxRec = NULL;
	DalocMsgBuf(dataPtr);
  }//if (invocationMode ==OAMS_TRXH_MAPENT_CRE_LTRX_PTRX_MAPPING_RESP)
  else 
  {     
	/* De-allocate memory for the data ptr */
	if (dataPtr != NULL )
	{
	  DalocMsgBuf(dataPtr);
	}
  }


  /* Loop keep on running until exit condition occurs */
  running = I_TRUE ;

  LOG_PRINT(INFO,"Entering while loop");
  while (running)
  {      

	/* 
	   This is the case when Ptrx is going down due to Ptrx_Lock or 
	   LAPD_Down or State_Change_Event.  Ptrx sets the MapAllowed="No"                 
	   and sends Initiate_Map() to invoke the Algo 
	 */
	isFound = FindNotMappableButMappedPtrx(&ptrxId) ; 

	if (isFound)
	{
	  LOG_PRINT(INFO,"Ptrx Found [ptrxid:%d] with MappedAllowed NO and Mapping Status MAPPED",ptrxId);
	  GetAssociatedLtrx(ptrxId, &ltrxRec);
	  /* 
		 Sending Del_Ltrx_Ptrx_Mapping_Req to Trxh to delete the channels 
		 (by requesting GRHM) and OpStop the PTRX. 
	   */

	  if (ltrxRec != NULL)
	  {
		//Temporarily changed for testing
		//ptrxMappingStatus = UNMAPPED ;
		ptrxMappingStatus = DELETE_IN_PROGRESS ;
		errCode = updatePtrxMappingStatus(ptrxId, ptrxMappingStatus);

		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"Exit Func MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed : err = %s",clib_strerror(errCode));
		  return I_FALSE ;
		}


		//LOG_PRINT(DEBUG, "Ptrx Id [ptrxId: %d] is now marked as UNMAPPED",ptrxId);
		LOG_PRINT(INFO,"[ltrxId:%d] mapped with [ptrxId:%d] to be de-mapped",ltrxRec->ltrxId,ptrxId); 
		msgCreStatus = CreateMsgMapentTrxhDelLtrxPtrxMappingReq(ptrxId,ltrxRec);

	  }
	  else
	  {
		LOG_PRINT(CRITICAL,"Exiting Mapping Algo:Ltrx Record not retrieved from DB for associated [ptrxId:%d]", ptrxId);
		return I_FALSE;
	  }


	  /* Setting the status of Ptrx as UNMAPPED */
	  if ( msgCreStatus == MSG_SUCCESS )
	  {                       
		ltrxMappingStatus = UNMAPINITIATED;
		errCode = updateLtrxMappingStatus(ltrxRec->ltrxId,ltrxMappingStatus);   

		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdateLtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		  return I_FALSE ;
		}

		LOG_PRINT(DEBUG, "[ltrxId:%d] is now marked as UNMAPINITIATED",ltrxRec->ltrxId);

		free(ltrxRec);
		ltrxRec = NULL;
		continue ;
	  } 
	  else
	  {
		LOG_PRINT(CRITICAL,"Exiting Func-MappingLtrxPtrxEntity: Creation of OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ failed for PtrxId[%d],LtrxId[%d]",ptrxId,ltrxRec->ltrxId);   

		free(ltrxRec);
		//Temp changes
		ltrxRec = NULL;
		return I_FALSE;  
	  }
	}

	/* 
	   Finding the highest priority Ltrx that is Generated but Could not be mapped because 
	   of unavailability of suitable Ptrx. 
	 */

	ltrxRec = (LtrxTableApi*)malloc(sizeof(LtrxTableApi));

	LOG_PRINT(INFO,"Finding Generated Ltrx for Mapping with Ptrx");

	isFound = FindLtrxWithSuitablePtrx(&ptrxId,ltrxRec,&lowerPrtLtrxRec,&chnGrpTableRec,&IsUnmappedPtrx);

	if (isFound && IsUnmappedPtrx)
	{
	  LOG_PRINT(INFO,"One Unmapped high priority [ltrxId:%d] found with one suitable Unmapped [ptrxId:%d]",ltrxRec->ltrxId,ptrxId);
	  ltrxRec->ptrxId = ptrxId;

	  /* Send Cre_Ltrx_Ptrx_Mapping_Req to Trxh to Start the Ptrx */

	  //LOG_PRINT(INFO,"Create Ltrx_Ptrx Mapping will be attempted for Ltrx [ltrxId: %d] to map with Ptrx [ptrxId: %d]",ltrxRec->ltrxId,ltrxRec->ptrxId);

	  msgCreStatus = CreateMsgMapentTrxhCreLtrxPtrxMappingReq(ltrxRec,chnGrpTableRec);

	  if ( msgCreStatus == MSG_SUCCESS )
	  {               
		ltrxMappingStatus = CREATE_IN_PROGRESS;
		ptrxMappingStatus = CREATE_IN_PROGRESS;

		LOG_PRINT(DEBUG, "[ltrxId:%d] is now marked as MAPPED",ltrxRec->ltrxId);
		errCode = updateLtrxMappingStatus(ltrxRec->ltrxId, ltrxMappingStatus);

		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdateLtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		  return I_FALSE ;
		}

		LOG_PRINT(DEBUG, "[ptrxId:%d] is now marked as MAPPED",ltrxRec->ptrxId);
		errCode = updatePtrxMappingStatus(ltrxRec->ptrxId, ptrxMappingStatus);

		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		  return I_FALSE ;
		}

		GetAssociatedLtrx1(ptrxId, &ltrxRec1);
		free(ltrxRec1);
		ltrxRec1 = NULL;
		/* Putting the PtrxId in Ltrx Record in LtrxTable. */
		errCode = updatePtrxIdInLtrxTable(ptrxId,ltrxRec->ltrxId);

		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdatePtrxIdInLtrxTable call failed:err=%s",clib_strerror(errCode));
		  return I_FALSE ;
		}

		LOG_PRINT(DEBUG,"[ptrxId:%d] is updated in Ltrx Record of [ltrxId:%d]",ptrxId,ltrxRec->ltrxId); 

		free(ltrxRec);
		ltrxRec = NULL;
		free(chnGrpTableRec);
		continue ;
	  }
	  else
	  {

		LOG_PRINT(CRITICAL, "Exiting Mapping Algo:Creation of OAMS_MAPENT_TRXH_CRE_LTRX_PTRX_MAPPING_REQ failed for [ltrxId:%d][ptrxId:%d]",ltrxRec->ltrxId,ltrxRec->ptrxId);                          

		free(ltrxRec);
		ltrxRec = NULL;
		free(chnGrpTableRec);
		return I_FALSE;  
	  }
	}
	/* Mapped Ptrx found */
	else if (isFound && !IsUnmappedPtrx)    
	{
	  //LOG_PRINT(DEBUG, "Found an Unmapped high priority [ltrxId:%d] but no Unmapped Ptrx found to be mapped.",ltrxRec->ltrxId);   
	  LOG_PRINT(DEBUG,"High Prio Unmapped LtrxId(%d) found. Algo will De-map Lower priority [ltrxId:%d] mapped with [ptrxId:%d]",ltrxRec->ltrxId,lowerPrtLtrxRec->ltrxId,lowerPrtLtrxRec->ptrxId);

	  /***********************/
	  //Temporarily changed for testing
	  ptrxMappingStatus = DELETE_IN_PROGRESS ;
	  //ptrxMappingStatus = UNMAPPED ;
	  ptrxId = lowerPrtLtrxRec->ptrxId;
	  errCode = updatePtrxMappingStatus(ptrxId, ptrxMappingStatus) ;

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exit Func MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		return I_FALSE ;
	  }
	  /***********************/
	  /* Send Del_Ltrx_Ptrx_Mapping_Req to Trxh to Demap the Ltrx and Ptrx */ 
	  msgCreStatus = CreateMsgMapentTrxhDelLtrxPtrxMappingReq(lowerPrtLtrxRec->ptrxId,lowerPrtLtrxRec);

	  if ( msgCreStatus == MSG_SUCCESS )
	  {                     
		LOG_PRINT(DEBUG, "[ptrxId:%d] is just UNMAPPED in DB",lowerPrtLtrxRec->ptrxId);
		ltrxMappingStatus = UNMAPINITIATED ;
		errCode = updateLtrxMappingStatus(lowerPrtLtrxRec->ltrxId,ltrxMappingStatus) ;

		if (errCode != CLIB_SUCCESS)
		{
		  LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdateLtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		  return I_FALSE ;
		}

		LOG_PRINT(DEBUG, "[ltrxId:%d] is now marked as UNMAPINITIATED",lowerPrtLtrxRec->ltrxId);

		free(ltrxRec);
		ltrxRec = NULL;
		free( lowerPrtLtrxRec);
		free(chnGrpTableRec);
		continue ;
	  }
	  else
	  {
		LOG_PRINT(CRITICAL, "Exiting Mapping Algo:Creation of OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ failed for [ltrxId:%d][ptrxId:%d]",lowerPrtLtrxRec->ltrxId,lowerPrtLtrxRec->ptrxId);           

		free(ltrxRec);
		ltrxRec = NULL;
		free(chnGrpTableRec);
		free(lowerPrtLtrxRec);
		return I_FALSE;
	  }
	}

	else
	{
	  LOG_PRINT(INFO," \n Gen Unmapped Ltrx with highest priority not retrieved ");
	}

	/*
	   Finding out all the Mapped Ltrx which are in Cleaning Down state (updated by Cellhandler)
	   in case of Cell Lock
Note: In case of Cell ShutDown mapping entity algo does not receive any separate message
	 */         
	isFound = FindMappedCleaningDownLtrx(ltrxRec) ;

	if (isFound)
	{
	  /* 
		 Setting the Mapping Status as UNMAPINITIATED to avoid redundancy of
		 Del_Ltrx_Ptrx Request to Trx Handler 
	   */
	  LOG_PRINT(INFO,"One Mapped [ltrxId:%d] found with status CLEANING_DOWN and is mapped with [ptrxId:%d]",ltrxRec->ltrxId,ltrxRec->ptrxId);
	  ltrxMappingStatus = UNMAPINITIATED ;
	  errCode = updateLtrxMappingStatus(ltrxRec->ltrxId, ltrxMappingStatus) ;

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exiting Func-MappingLtrxPtrxEntity:UpdateLtrxMappingStatus call failed:err=%s",clib_strerror(errCode));
		return I_FALSE ;
	  }

	  LOG_PRINT(INFO,"[ltrxId:%d] is now marked as UNMAPINITIATED in DB",ltrxRec->ltrxId);
	  /*********Changes for BSS lock start****************************/
	  //Temporarily changed for testing
	  ptrxMappingStatus = DELETE_IN_PROGRESS ;
	  //         ptrxMappingStatus = UNMAPPED ;
	  errCode = updatePtrxMappingStatus(ltrxRec->ptrxId, ptrxMappingStatus) ;

	  if (errCode != CLIB_SUCCESS)
	  {
		LOG_PRINT(MAJOR,"Exit Func MappingLtrxPtrxEntity:UpdatePtrxMappingStatus call failed : err = %s",clib_strerror(errCode));
		return I_FALSE ;
	  }
	  LOG_PRINT(INFO,"[ptrxId:%d] is just marked as DEL_IN_PROGRESS in DB",ltrxRec->ptrxId);
	  /**********Changes for BSS lock ends***************************/

	  msgCreStatus = CreateMsgMapentTrxhDelLtrxPtrxMappingReq(ltrxRec->ptrxId, ltrxRec);         

	  if ( msgCreStatus == MSG_SUCCESS )
	  {                          
		free(ltrxRec);
		ltrxRec = NULL;
		continue ;
	  }

	  else
	  {
		LOG_PRINT(CRITICAL, "Exiting Mapping Algo:Creation of OAMS_MAPENT_TRXH_DEL_LTRX_PTRX_MAPPING_REQ failed for [ltrxId:%d][ptrxId:%d]",ltrxRec->ltrxId,ltrxRec->ptrxId);

		free(ltrxRec);
		ltrxRec = NULL;
		return I_FALSE;
	  }
	}

	else
	{
	  /* No more action to do.  Exit from the Algorithm. */
	  LOG_PRINT(DEBUG, "No more action for Algo to do:Reset Global Variables:Exiting Mapping Algoritm");
	  running = I_FALSE;

	  continue ;
	}
  }

  if (ltrxRec != NULL)
  {
	free(ltrxRec);
	ltrxRec = NULL;
  }

  return I_TRUE ;
}     
