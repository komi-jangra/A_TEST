/******************************************************************************
FILE NAME         :  oamstrxh_trxdspcontroller.c
PURPOSE           :  Source code for TRXH to provide DSP resource to TRX which is waiting 
										 for DSP resources, when any other TRX is down and Resources
										 are free due to this.
PROJECT           :  BSS
SUBSYSTEM         :  OAMS
AUTHOR            :  Nidhi Tomar
CSCI ID           :
VERSION           :  V0.1
 *******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<sysxxx_macro.h>
#include<sysxxx_hashdefs.h>
#include<sysxxx_typedef.h>
#include<sysxxx_msgopcode.h>
#include<sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include<syscmn_hashdefs.h>
#include<sysxxx_datastruct.h>
#include<sysxxx_msgstruct.h>
#include <syscmn_datastruct.h>
#include<sysinst_hashdefs.h>
#include<ipcfrm_syslog.h>
#include<ipcfrm_msgqueue.h>
#include<ipcfrm_extern.h>
#include<ipcinst_dbstruct.h>
#include<ipcinst_extern.h>
#include <dbsxxx_commondefs.h>
#include<csappxxx_common_datastruct.h>
#include<oamxxx_hashdefs.h>
#include<oamsxxx_typedef.h>
#include<oamsxxx_hashdef.h>
#include<oamxxx_msgstruct.h>
#include<msg_struct.h>
#include<oamsxxx_msgstruct.h>
#include <bpmxxx_OAM_commonDef.h>
#include <oamxxx_tableapidefs.h>
#include<msg_struct.h>
#include <oamstrxh_hashdefs.h>
#include "../../../Inc/oams_msgstruct.h"
#include<oamstrxh_datastruct.h>
#include<dsp_pp_com.h>
#include <DBLIBError.h>
#include <CLIB.h>
#include <dbsxxx_commonwrappers.h>
#include <dbsxxx_trxh_dbwrapper.h>


/***********************************************************************************
 *  Function Name   : CreateTrxhDspAvailabilityInd
 *
 *  Args            : 1. trxId 
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            : 
 ***********************************************************************************/


I_S32 CreateTrxhDspAvailabilityInd(I_U8 trxId)
{
	I_U32 sndMsgSize;
  OamsTrxhEnvTrxhAvailabilityInd *msgPtr = NULL;

  LOG_PRINT(DEBUG, "In function CreateTrxhDspAvailabilityInd");

  sndMsgSize = sizeof(OamsTrxhEnvTrxhAvailabilityInd);
  msgPtr     = (OamsTrxhEnvTrxhAvailabilityInd*) AlocMsgBuf(sndMsgSize);

  if (msgPtr == NULL)
	 {
	  LOG_PRINT(CRITICAL,"Memory could not be allocated");
	  return I_FALSE;
	 }
  
	FILL_SYS_HDR(msgPtr,OAMS_TRXHENV_TRXH_DSP_AVAILABILITY_IND, MSG_SUB_TYPE,PRCR_CP,
	             ZERO ,ZERO ,PRCR_CP,ENT_OAMS_TRXH, ZERO);
	
	msgPtr->ptrxId = trxId;
	
	if (SendMsg((I_PVoid)msgPtr,MSG_ORD_PRIO,sndMsgSize) == SND_FAIL)
	  {
	    LOG_PRINT(CRITICAL,"Sending failed in OAMS_TRXHENV_TRXH_DSP_AVAILABILITY_IND");
	    return I_FALSE;
	  }
	else
	    LOG_PRINT(DEBUG,"Sending Success in OAMS_TRXHENV_TRXH_DSP_AVAILABILITY_IND  with msgSize=%d ",sndMsgSize);

		  LOG_PRINT(DEBUG, "Exiting function CreateTrxhDspAvailabilityInd");
		   return I_TRUE;

}


/***********************************************************************************
 *  Function Name   : trxMsgHandler
 *
 *  Args            : 
 *
 *  Returns         : SUCCESS or  FAILURE.
 *
 *  Task            :
 ***********************************************************************************/
I_S32 trxMsgHandler(I_U32 selfTrxId)
{
				I_U16                       rcvdMsgTyp;
    					I_S32                       sndStatus;
#if 0    	
    					I_S32                       errCode;
							PtrxTableApi						 		*ptrxTblOutData;
							I_U32												ptrxTblOutRows;
							I_U32												nPtrxTblRowNum;
							I_U16												ptrxTblOutSize;
							PtrxTableSecIndices		 			inPtrxData;
							PtrxTableApi								*ptrxTblRowData = NULL;
						
      			LOG_PRINT(INFO, "Entering into trxMsgHandler()\n");
					
						inPtrxData.pendingTrauMapStatus=PENDING;						
            
						errCode = getPendingTrxPtrxTable(&inPtrxData, &ptrxTblOutData, &ptrxTblOutRows, &ptrxTblOutSize);
						if (errCode != CLIB_SUCCESS)
   					{
      				LOG_PRINT(INFO, "No Data in PtrxTable for pending Trx : err = %s", clib_strerror(errCode));
      				return I_TRUE;
   					}
						else
						{
      			  LOG_PRINT(INFO, "Value of OutRows=%d and OutSize=%d\n",ptrxTblOutRows,ptrxTblOutSize);
							for (nPtrxTblRowNum=0; nPtrxTblRowNum < ptrxTblOutRows; nPtrxTblRowNum++)
   							{
      						ptrxTblRowData = (PtrxTableApi*)((I_U8*)(ptrxTblOutData) + (nPtrxTblRowNum * ptrxTblOutSize));

      						if ( (ptrxTblRowData->pendingTrauMapStatus == PENDING_TRAU_MAP_STATUS_YES) /*&&
                       (selfTrxId != ptrxTblRowData->ptrxId) */)
     							 {
												sndStatus=CreateTrxhDspAvailabilityInd(ptrxTblRowData->ptrxId);												
												if((sndStatus) != I_TRUE)
    											{
          									LOG_PRINT(INFO," Send Failure for Trx=%d",ptrxTblRowData->ptrxId);

    											}
													else
													{
                            break;	
													}

      						 
										}// end of pendingStatus == PENDING
	
								 }//end of for loop 
								//DalocOrdBuf(inPtrxData);
							  free(ptrxTblOutData);
	}
#endif					   
return I_TRUE;
}
