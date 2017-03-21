/*******************************************************************************
**      FILE NAME:
**          bs_msg.c
**
**      DESCRIPTION:
**              This file defines all the BSSAP protocol Stack message handelling.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/



#include "lbs.h"           /* layer management                             */
#include "bs.h"
#include "bs_err.h"
#include "bsapp.h"
#include "bssapcom.h"
#include "bs_trace.h"

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_api.h"
#include "bs_stgl.h"
#include "bs_debug.h"
#include "bs_prov.h"

#include <pthread.h>
#include <netinet/in.h>

/* header/extern include files (.x) */
#include "lbs.x"           /* layer management                             */
#include "bs.x"
#include "bsapp.x"
#include "bssapcom.x"
#include "bs_trace.x"

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)

SysAddr slfAddr;
#endif
#ifdef LOGGER_ON_SCREEN
#define LOG_PRINT(a,b,args...) printf(b,##args)
#endif

/*
*
*      Fun:  BsFindIE
*
*      Desc:  This function will find IE from IE list
*             
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
BSSAP_IE* BsFindIE
(
BSSAP_IE *ie,
S16bit  iecount,
U8bit  ieParamId
)
#else
BSSAP_IE* BsFindIE(ie,iecount,ieParamId)
BSSAP_IE *ie;
S16bit  iecount;
U8bit  ieParamId;
#endif
{
  U16bit i;
  for(i = 0;i < iecount;i++)
  {
     if(ie[i].param_id == ieParamId)
     {
        return &ie[i];  
     }
  }
  return SS7_NULL;
}
/*
*
*      Fun:  BsProcessAssignmentRequest
*
*      Desc:  This function will process  Assignment Request
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessAssignmentRequest
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessAssignmentRequest(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  BSSAP_IE *ieData = SS7_NULL;
  BSSAP_IE *cdieData = SS7_NULL;
  U16bit cicVal =0; 
  U16bit oldcicVal =0; 
  U8bit cause;
  U8bit speechDataId;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit callState = 0;
  U8bit localState = 0;
  U8bit msgtype = 0;
#ifdef BSSAP_HA
  HashEntry *callIdEntry = NULL;
  CallIdCb *callIdVal = NULL;
  int ret = RFAILED;
#endif

    if(call == SS7_NULL)
    {
      LOG_PRINT(INFO,"BsProcessAssignmentRequest():call null");
      return SS7_FAILURE;	
    }

  bsIntfCb = intfCb; 
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(INFO,"BsProcessAssignmentRequest():Intf null");
    return SS7_FAILURE;	
  }
  /*Refer 48008-880:3.1.5c.1:The Internal Handover Preparation procedure terminates,An ASSIGNMENT REQUEST is received*/
  if(call->timerId == BSSAP_T_25)
  {
    bsStopConTmr(call,BSSAP_T_25);
  }
  cdieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CODEC_LIST);
  if(cdieData)
  {
    ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CALL_ID);
    if(ieData)
    {
      if(ieData->param_data.call_id.callId == 0)
      {
         LOG_PRINT(INFO,"BsProcessAssignmentRequest():CALLID value zero is invalid");
	 cause = C_INVALID_MSG_CONTENT;
         BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
         return SS7_FAILURE;
      }
      call->cic = 0;
#ifdef BSSAP_HA
      /* Search hashlist for callId to check if entry present*/
      LOG_PRINT(INFO,"BsProcessAssignmentRequest():CALLID value[%d] \n",ieData->param_data.call_id.callId);
      ret = HashListTbSearch(intfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId), sizeof(ieData->param_data.call_id.callId),&callIdEntry);
      if((ret == ROK) && (callIdEntry != NULL))
      {
	LOG_PRINT(INFO,"BsProcessAssignmentRequest() :CALLID[%ld] is already in Use \n",ieData->param_data.call_id.callId);
	cause = C_CALL_IDENTIFIER_ALREADY_ALLOCATED;
	BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
	return SS7_FAILURE;
      }
      callIdVal = (CallIdCb *)calloc(1,sizeof(CallIdCb));
      if(callIdVal == SS7_NULL)
      {
	LOG_PRINT(INFO,"BsProcessAssignmentRequest() :could not allocate memory to callIdVal ptr \n");
	return SS7_FAILURE;
      }
	      
      callIdVal->callId = ieData->param_data.call_id.callId;
      callIdVal->callRefId = call->suInstId;
      
      ret = HashListTbInsert(intfCb->callIdList,intfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId),sizeof(ieData->param_data.call_id.callId),callIdVal,sizeof(CallIdCb));
      if(ret != ROK)
      {
	LOG_PRINT(INFO,"BsProcessAssignmentRequest() :HashListTbInsert failed for CALLID[%d]\n",ieData->param_data.call_id.callId);
	cause = C_TERRESTRIAL_RES_UNAVAILABLE;
	BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
	free(callIdVal);
	callIdVal = NULL;
	return SS7_FAILURE;
      }
#endif
      memcpy(&call->callId,&ieData->param_data.call_id.callId,sizeof(BSSAP_CallIdentifier));
      LOG_PRINT(INFO,"BS: BsProcessAssignmentRequest :AOIP callId %ld \n",call->callId);
      call->msgType = BSSAP_MSG_ASSIGN_REQUEST;
      /*Starting BSSAP_T_10 timer*/
      bsStartConTmr(BSSAP_T_10,call,intfCb);
      return SS7_SUCCESS; 
    }
  }

  ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
  if(ieData)
  {

    cicVal = (ieData->param_data.cic.cic[0]<<8)|(ieData->param_data.cic.cic[1]);
    LOG_PRINT(INFO,"BsProcessAssignmentRequest() :ASSIGNMENT REQUEST Received for CIC %d \n",cicVal);
    if((bsIntfCb->cicDataList != NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
    {
      /* CIC found in CIC data  list*/
      BS_GET_CALLSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,callState);
      BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,localState);
      if(callState == CALL_ST_BUSY)
      {
	/* CIC Call state is marked as already BUSY*/
	   LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest() :CALL in BUSY state:cic %d \n",cicVal);
#if 0
	/*Raise Alarm to Stack Manager */
	msgtype = BSSAP_MSG_ASSIGN_REQUEST;
	bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
	    LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
	    LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
	    LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

	bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
	LBS_EVENT_CALL_IN_BUSY_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif   

	cause = C_TERRESTRIAL_CIRCUIT_ALLOCATED;
      }
      else if (localState == CIC_ST_LOCAL_UNBLK)
      {
	if(call->cic > 0)
	{
	  oldcicVal = call->cic;
	  if(bsIntfCb->cicDataList[oldcicVal].cic == oldcicVal) 
	  {
	    BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[oldcicVal].flaglistSet);
	    call->cic = 0;
	  }
	  else
	  {
	    LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest():oldcicVal %d not Match in DB\n",oldcicVal);
	  }
	}
	call->cic = cicVal;
	call->msgType = BSSAP_MSG_ASSIGN_REQUEST;
	/*Starting BSSAP_T_10 timer*/
	bsStartConTmr(BSSAP_T_10,call,intfCb);
        return SS7_SUCCESS;
      }
      else /* CIC_ST_BLOCK */
      {

	LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest():cic block %d ",cicVal);

	cause = C_TERRESTRIAL_RES_UNAVAILABLE; 
	/*Raise Alarm to Stack Manager */
	msgtype = BSSAP_MSG_ASSIGN_REQUEST;
#if 0
	bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
	    LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
	    LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
	    LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

	bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
	    LBS_EVENT_CIC_IN_BLOCK_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

      }
      BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
      if(localState == CIC_ST_LOCAL_BLOCK)
      {
	LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest():Sending BLOCK Message towards MSC as CIC[%d] locally blocked \n",cicVal);
	BsSendCktMsg(BSSAP_MSG_BLOCK,cicVal,SS7_NULL,intfCb);
      }
      else
      {
	      LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest() : Do nothing if cic state is not blocked in  ASSIGNMENT REQUEST \n");
      }
      BsDispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,cicVal,BSSAP_MSG_ASSIGN_REQUEST,intfCb);
      return SS7_FAILURE;
    }
    else
    {
      /* If CIC not found in BSSAP stack the BSSAP stack,thus sending Assignment failure 
	 followed by Unequipckt message towards MSC  */

      LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
      /*Raise Alarm to Stack Manager */
      msgtype = BSSAP_MSG_ASSIGN_REQUEST;
      bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
	  LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
	  LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
	  LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

      bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
	  LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif  

      cause = C_TERRESTRIAL_RES_UNAVAILABLE;
      BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
      BsDispatchErrorToApp(call,BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,cicVal,BSSAP_MSG_ASSIGN_REQUEST,intfCb);
      LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest() :Sending UNEQUIPPED Error to APP \n");
      BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
      return SS7_FAILURE;
    }
  }
  else
  {
      ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CHANNEL_TYPE);
      if(ieData)
      {
	speechDataId = BSSAP_CT_GET_SPEECH_DATA_IND(ieData->param_data.chanl_type);
	/* Added to start for fix Mantis-Id 30762 */
  if(speechDataId == CT_SIGNALING || speechDataId == CT_DATA || speechDataId == CT_SPEECH || speechDataId == CT_SPEECH_CTM_TXT_TELEPHONY)
  {
          return SS7_SUCCESS;
  }
/* Added to stop for fix Mantis-Id 30762 */
	else
	{
	  LOG_PRINT(CRITICAL,"BS: BsProcessAssignmentRequest() :Cic not present and and Invalid BSSAP_IEI_CHANNEL_TYPE\n");
	  cause = C_PROTOCOL_ERROR;
	  BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
          return SS7_FAILURE;
	}
      }
      else
      {
	LOG_PRINT(CRITICAL,"BsProcessAssignmentRequest() :Cic IE and Channel type both are not present \n");
	cause = C_PROTOCOL_ERROR;
	BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,intfCb);
        return SS7_FAILURE;
      }
  } 
        return SS7_SUCCESS;
}
/*
*
*      Fun:  BsProcessAssignmentComplete
*
*      Desc:  This function will process  Assignment Complete
*              coming from  Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessAssignmentComplete
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessAssignmentComplete(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  U16bit cicVal = 0;
  U16bit cicValRecv = 0;
  U32bit callId = 0;
  BsIntfCb *bsIntfCb;
  BSSAP_IE *ieData = SS7_NULL;
  U8bit msgtype = 0;

  msgtype = BSSAP_MSG_ASSIGN_COMPLETE;
  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessAssignmentComplete(): call pointer NULL \n");
    return (SS7_FAILURE);
  }
  cicVal = call->cic;
  callId = call->callId;
  bsIntfCb =  intfCb;
  if(cicVal)
  {
     LOG_PRINT(INFO,"BsProcessAssignmentComplete() : Assign Complete for  cic %d \n",cicVal);
     ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
     if(ieData)
     {
          cicValRecv = (ieData->param_data.cic.cic[0]<<8)|(ieData->param_data.cic.cic[1]);
          LOG_PRINT(INFO,"BsProcessAssignmentComplete() : cic Value in Assign Complete msg is %d  \n",cicValRecv);
          if(cicVal != cicValRecv)
          {
            LOG_PRINT(INFO,"BsProcessAssignmentComplete(): CIC Value recv mismatch with  cic value in the call pointer \n");
             BsDispatchErrorToApp(call,BSSAP_MD_PROTOCOL, BSSAP_EINVMESSAGE,cicValRecv,BSSAP_MSG_ASSIGN_COMPLETE,intfCb);
    	     return (SS7_FAILURE);
              
          }
     }
     else
     {
        LOG_PRINT(CRITICAL,"BsProcessAssignmentComplete() : No cic Value present in Assign Complete msg from App  \n");
             /*RETVALUE(RFAILED);*/
     }
     if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic != cicVal))
     {
        LOG_PRINT(CRITICAL,"BsProcessAssignmentComplete(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
        /*Raise Alarm to Stack Manager */
         bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

         bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif  
         BsDispatchErrorToApp(call,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_ASSIGN_COMPLETE,intfCb);
    	 return (SS7_FAILURE);
     }
     /*STOP Timer BSSAP_T_10 */
     bsStopConTmr(call,BSSAP_T_10);
     LOG_PRINT(INFO,"BsProcessAssignmentComplete(): STOP T10(reason:ASSIGNCOMPLETE CIC [%d]\n",call->cic);
     BS_SET_CALLSTATE_BUSY(bsIntfCb->cicDataList[cicVal].flaglistSet);
     /* By this response we know clearly channel is getting alloted */
     call->channelAlloc = SS7_TRUE;
  }
  else if(callId)
  {
     LOG_PRINT(INFO,"BsProcessAssignmentComplete() : Assign Complete for  call id %ld \n",callId);
     bsStopConTmr(call,BSSAP_T_10);
     call->channelAlloc = SS7_TRUE;
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessAssignmentComplete() : No CIC in Call structure\n");
    return (SS7_FAILURE);
  }
  return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsProcessAssignmentFailure
*
*      Desc:  This function will process Assignment Failure
*              coming from  Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessAssignmentFailure
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessAssignmentFailure(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  U16bit cicVal = 0;
  U32bit callId = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit msgtype = 0;
#ifdef BSSAP_HA
  HashEntry *callIdEntry = NULL;
  CallIdCb *callIdVal = NULL;
  int ret = RFAILED;
#endif


   msgtype = BSSAP_MSG_ASSIGN_FAILURE;
  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessAssignmentFailure():call null");
    return (SS7_FAILURE);
  }

  cicVal = call->cic;
  callId = call->callId;
  bsIntfCb =  intfCb;
  if(cicVal)
  {
    LOG_PRINT(CRITICAL,"BsProcessAssignmentFailure() : Assign failure for cicVal [%d]\n",cicVal);
     if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
     {
        BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[cicVal].flaglistSet);
        call->cic = 0;
        call->msgType = BSSAP_MSG_ASSIGN_FAILURE;
        /*STOP Timer BSSAP_T_10 */  
         bsStopConTmr(call,BSSAP_T_10);
     }
     else
     {
        LOG_PRINT(CRITICAL,"BsProcessAssignmentFailure(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
        /*Raise Alarm to Stack Manager */
         bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

         bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    return (SS7_FAILURE);

     }
  }
  else if(callId)
  {
     LOG_PRINT(CRITICAL,"BsProcessAssignmentFailure() : Assign failure for CallId [%ld]\n",callId);
#ifdef BSSAP_HA
     ret = HashListTbSearch(bsIntfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId),&callIdEntry);
     if(ret != ROK)
     {
       LOG_PRINT(CRITICAL,"BsProcessAssignmentFailure():HashListTbSearch fail,CALLID[%ld] not found  hash list\n",callId);
       return (SS7_FAILURE);
     }
     callIdVal = callIdEntry->data;
     if(callIdVal)
     {
       LOG_PRINT(INFO,"BsProcessAssignmentFailure():Deleting for CALLID[%d] \n",callIdVal->callId);
     }
     ret = HashListTbDelete(bsIntfCb->callIdList,bsIntfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId));
     if(ret != ROK)
     {
       LOG_PRINT(INFO,"BsProcessAssignmentFailure():HashListTbDelete failed for CALLID[%ld]\n",callId);
       return (SS7_FAILURE);
     }
     if(callIdVal)
     {
       free(callIdVal);
       callIdVal = NULL;
     }
#endif
     call->callId = 0;
     call->msgType = BSSAP_MSG_ASSIGN_FAILURE;
     bsStopConTmr(call,BSSAP_T_10);
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessAssignmentFailure():Neither cic nor Call Id present in call db, passing Assign Failure to Peer");
    //return (SS7_FAILURE);
    return (SS7_SUCCESS);
  }
 return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsProcessHandoverRequest
*
*      Desc:  This function will process Handover Request 
*              coming from MSC 
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessHandoverRequest
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessHandoverRequest(call,ie,iecount,databuff,dataLen,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
  U32bit callrefId = 0;
  BSSAP_IE *ieData = SS7_NULL;
  S16bit cause ;
  U16bit cicVal = 0;
  U16bit oldcicVal = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  BsCallCb *fptr = SS7_NULL;
  U8bit callState = 0;
  U8bit localState = 0;
  U8bit dt1horeq = DT1HOREQ_FALSE;
  U8bit msgtype = 0;
#ifdef BSSAP_HA
  HashEntry *callIdEntry = NULL;
  CallIdCb *callIdVal = NULL;
  int ret = RFAILED;
#endif

  msgtype = BSSAP_MSG_HANDOVER_REQUEST;
   
  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessHandoverRequest(): call pointer NULL \n");
    return (SS7_FAILURE);
  }
  callrefId = call->suInstId;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessHandoverRequest(): Interface pointer NULL \n");
    return (SS7_FAILURE);
  }

  /* find connection */
  fptr = bsFindCall(intfCb,callrefId);
  if(fptr != SS7_NULL)
  {
     BS_GET_DT1HOREQ(fptr->handoverFlagSet,dt1horeq);
  }
  if((fptr == SS7_NULL)|| (dt1horeq == DT1HOREQ_TRUE))
  {
      LOG_PRINT(INFO,"BsProcessHandoverRequest():SCCP-New connection for HO-REQ case(CR)/(DT1) \n");
      ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
      if(ieData)
      {
          cicVal = (ieData->param_data.cic.cic[0]<<8)|(ieData->param_data.cic.cic[1]);
          LOG_PRINT(INFO,"BsProcessHandoverRequest(): HANDOVER REQUEST for CIC[%d]\n",cicVal);
          LOG_PRINT(INFO,"BsProcessHandoverRequest(): HANDOVER REQUEST for CIC[0] %d CIC[1] %d \n",ieData->param_data.cic.cic[0],ieData->param_data.cic.cic[1]);
          if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
          {
             BS_GET_CALLSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,callState);
             BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,localState);
             if(callState == CALL_ST_BUSY)
             {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():CALL in BUSY state \n");
#if 0
                /*Raise Alarm to Stack Manager */
                bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

                bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CALL_IN_BUSY_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

                BsDispatchMapErrToApp(call,BSSAP_ECICCKTALCTD,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
                cause = C_TERRESTRIAL_CIRCUIT_ALLOCATED;
             }
             else if(localState == CIC_ST_LOCAL_UNBLK)
             {
                if(call->cic > 0)
                {
                   oldcicVal = call->cic;
                   if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[oldcicVal].cic == oldcicVal))
                   {
                     BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[oldcicVal].flaglistSet);
                     call->cic = 0;
                   }
                   else
                   {
                      LOG_PRINT(CRITICAL,"BsProcessHandoverRequest() :oldCic val %d not Match in DB\n",oldcicVal);
                   }
                }
                call->cic = cicVal;
                BS_SET_CALLSTATE_BUSY(bsIntfCb->cicDataList[cicVal].flaglistSet);
    		return (SS7_SUCCESS);
             }
             else
             {
                cause = C_TERRESTRIAL_RES_UNAVAILABLE;
                 LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():CIC in BLK state  \n");
#if 0
                /*Raise Alarm to Stack Manager */
                bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

                bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_IN_BLOCK_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

                BsDispatchMapErrToApp(call,BSSAP_ECICCKTUNVL,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
             }
             BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
             if(localState == CIC_ST_LOCAL_BLOCK)
             {
                BsSendCktMsg(BSSAP_MSG_BLOCK,cicVal,SS7_NULL,intfCb);
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():Sending BLOCK Message to MSC as CIC is locally block in HANDOVER REQUEST \n");
             }
             else
             {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():Do nothing if cic localstate is not blocked in  HANDOVER REQUEST  \n");
             }
             return (SS7_FAILURE);
          }
          else
          {
          
	    LOG_PRINT(CRITICAL,"BsProcessHandoverRequest: CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
            /*Raise Alarm to Stack Manager */
            bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

            bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif  

            cause = C_TERRESTRIAL_RES_UNAVAILABLE;
            BsDispatchMapErrToApp(call,C_PROTOCOL_ERROR,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
            BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
            BsDispatchErrorToApp(call,BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,cicVal,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
      LOG_PRINT(CRITICAL,"BsProcessHandoverRequest() :Sending UNEQUIPPED Error to APP \n");
            BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
            return (SS7_FAILURE);
          }
      }
      else
      {
            ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CALL_ID);
            if(ieData)
            {
               call->cic = 0;
#ifdef BSSAP_HA
	       ret = HashListTbSearch(intfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId), sizeof(ieData->param_data.call_id.callId),&callIdEntry);
	       if(ret == ROK)
	       {
		 LOG_PRINT(CRITICAL,"BsProcessHandoverRequest() :CALLID[%ld] is already in Use \n",ieData->param_data.call_id.callId);
		 cause = C_CALL_IDENTIFIER_ALREADY_ALLOCATED;
		 BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
		 return (SS7_FAILURE);
	       }
      
	       callIdVal = (CallIdCb *)calloc(1,sizeof(CallIdCb));
	       if(callIdVal == SS7_NULL)
	       {
		 LOG_PRINT(CRITICAL,"BsProcessHandoverRequest() :could not allocate memory to callIdVal ptr \n");
		 return SS7_FAILURE;
	       }
	       callIdVal->callId = ieData->param_data.call_id.callId;
	       callIdVal->callRefId = call->suInstId;
      
	       ret = HashListTbInsert(intfCb->callIdList,intfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId),sizeof(ieData->param_data.call_id.callId),callIdVal,sizeof(CallIdCb));
	       if(ret != ROK)
	       {
		 LOG_PRINT(CRITICAL,"BsProcessHandoverRequest() :HashListTbInsert failed for CALLID[%d]\n",ieData->param_data.call_id.callId);
		 cause = C_TERRESTRIAL_RES_UNAVAILABLE;
		 BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
		 free(callIdVal);
		 callIdVal = NULL;
		 return SS7_FAILURE;
	       }
#endif
               memcpy(&call->callId,&ieData->param_data.call_id.callId,sizeof(BSSAP_CallIdentifier));
               LOG_PRINT(INFO,"BsProcessHandoverRequest() :AOIP callId %ld \n",call->callId);
               return (SS7_SUCCESS);
            }
            else
            {
              LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():cic not present");
              cause = C_PROTOCOL_ERROR;
              BsDispatchMapErrToApp(call,BSSAP_EPROTOCOLERR,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
              BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
              return (SS7_FAILURE);
            }
      }
      return (SS7_SUCCESS);
  }/*End of SCCP-New connection*/
  else
  {
                            
    LOG_PRINT(INFO,"BsProcessHandoverRequest:Enter same SCCP-Connection: \n");
     ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
     if(ieData)
     {
        cicVal = (ieData->param_data.cic.cic[0]<<8)|(ieData->param_data.cic.cic[1]);

        if((bsIntfCb->cicDataList != NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
        {
            BS_GET_CALLSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,callState);
            BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,localState);
            if(callState == CALL_ST_BUSY)
            {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():CALL in BUSY state in case of same SCCP-Connection with Same CIC\n");
#if 0
                 /*Raise Alarm to Stack Manager */
                bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

                bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CALL_IN_BUSY_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
      		return (SS7_FAILURE);
            }
            else if(localState == CIC_ST_LOCAL_UNBLK)
            {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():CIC Local state is UNBLK in case of same SCCP-Connection with Same CIC\n");
                cause = C_PROTOCOL_ERROR;
                BsDispatchMapErrToApp(call,BSSAP_EPROTOCOLERR,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
                BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,C_PROTOCOL_ERROR,SS7_NULL,0,intfCb);
      		return (SS7_FAILURE);
           
	   }
           else
           {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():CIC Local state is BLK in case of same SCCP-Connection with Same CIC\n");
                 cause = C_TERRESTRIAL_RES_UNAVAILABLE;
#if 0
                /*Raise Alarm to Stack Manager */
                bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

                bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_IN_BLOCK_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
                BsDispatchMapErrToApp(call,BSSAP_ECICCKTUNVL,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
           }
           BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
           if(localState == CIC_ST_LOCAL_BLOCK)
           {
		LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():Sending BLOCK Message to MSC as CIC is locally block in HANDOVER REQUEST \n");
                BsSendCktMsg(BSSAP_MSG_BLOCK,cicVal,SS7_NULL,intfCb);
                  
           }
           else
           {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest():Do nothing if cic localstate is not blocked in  HANDOVER REQUEST  \n");
           }
      	   return (SS7_FAILURE);
        }
        else
        {
          LOG_PRINT(CRITICAL,"BsProcessHandoverRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
            /*Raise Alarm to Stack Manager */
            bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

            bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
            cause = C_TERRESTRIAL_RES_UNAVAILABLE;
            BsDispatchMapErrToApp(call,C_PROTOCOL_ERROR,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
            BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
            BsDispatchErrorToApp(call,BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,cicVal,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
      LOG_PRINT(CRITICAL,"BsProcessHandoverRequest() :Sending UNEQUIPPED Error to APP \n");
            BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
      	    return (SS7_FAILURE);
        }
     }
     else
     {
            ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CALL_ID);
            if(ieData)
            {
               call->cic = 0;
               LOG_PRINT(INFO,"BsProcessHandoverRequest() :AOIP callId in call DB %ld \n",call->callId);
               LOG_PRINT(INFO,"BsProcessHandoverRequest() :AOIP callId in msg %ld \n",ieData->param_data.call_id.callId);               
#ifdef BSSAP_HA
	       ret = HashListTbSearch(intfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId), sizeof(ieData->param_data.call_id.callId),&callIdEntry);
	       if(ret == ROK)
	       {
		 LOG_PRINT(INFO,"BsProcessHandoverRequest() :CALLID[%ld] is already in Use \n",ieData->param_data.call_id.callId);
		 cause = C_CALL_IDENTIFIER_ALREADY_ALLOCATED;
		 BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
		 return (SS7_FAILURE);
	       }
      
	       callIdVal = (CallIdCb *)calloc(1,sizeof(CallIdCb));
	       if(callIdVal == SS7_NULL)
	       {
		 LOG_PRINT(INFO,"BsProcessHandoverRequest() :could not allocate memory to callIdVal ptr \n");
		 return SS7_FAILURE;
	       }
	       callIdVal->callId = ieData->param_data.call_id.callId;
	       callIdVal->callRefId = call->suInstId;
      
	       ret = HashListTbInsert(intfCb->callIdList,intfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId),sizeof(ieData->param_data.call_id.callId),callIdVal,sizeof(CallIdCb));
	       if(ret != ROK)
	       {
		 LOG_PRINT(INFO,"BsProcessHandoverRequest() :HashListTbInsert failed for CALLID[%d]\n",ieData->param_data.call_id.callId);
		 cause = C_TERRESTRIAL_RES_UNAVAILABLE;
		 BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
		 free(callIdVal);
		 callIdVal = NULL;
		 return SS7_FAILURE;
	       }
#endif
	       if(call->callId != ieData->param_data.call_id.callId)
               {
                  ss7_memcpy(&call->callId,&ieData->param_data.call_id.callId,sizeof(BSSAP_CallIdentifier));
                  LOG_PRINT(INFO,"BsProcessHandoverRequest(): Passing msg to APP as call ids differ \n");
      	    	  return (SS7_SUCCESS);
               }
               LOG_PRINT(INFO,"BsProcessHandoverRequest() :Discarding Handover Req on same sccp connection for AOIP callId %ld \n",call->callId);
      	       return (SS7_FAILURE);
            }
            else
            {
                LOG_PRINT(CRITICAL,"BsProcessHandoverRequest(): Neither CIC nor Call Id found in the Handover Request recv \n");
                cause = C_PROTOCOL_ERROR;
                BsDispatchMapErrToApp(call,BSSAP_EPROTOCOLERR,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
                BsSendFailureMsg(SS7_NULL,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
      	        return (SS7_FAILURE);
            }
     }
  }/*End of same SCCP-Connection*/

   return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsProcessHandoverRequired
*
*      Desc:  This function will process Handover Required
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessHandoverRequired
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount
)
#else
S16bit BsProcessHandoverRequired(call,ie,iecount)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
#endif
{
  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessHandoverRequired(): call pointer NULL \n");
    return (SS7_FAILURE);
  }
  call->callType = HO_CALL;
  BS_SET_HANDOVER_TRUE(call->handoverFlagSet);
  BS_SET_HOOLDBSS_TRUE(call->handoverFlagSet);
  return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsProcessHandoverReqAck
*
*      Desc:  This function will process Handover Request Ack
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessHandoverReqAck
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessHandoverReqAck(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  U16bit cicVal = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit msgtype = 0;


  msgtype = BSSAP_MSG_HANDOVER_REQUEST_ACK;

  if(call == SS7_NULL)
  {
    LOG_PRINT(INFO,"BsProcessHandoverReqAck(): call pointer SS7_NULL \n");
    return (SS7_FAILURE);
  }

  cicVal = call->cic;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(INFO,"BsProcessHandoverReqAck(): Interface pointer NULL \n");
    return (SS7_FAILURE);
  }
  if(cicVal)
  {
     if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
     {
       call->channelAlloc = SS7_TRUE; 
     }
     else
     {
         LOG_PRINT(CRITICAL,"BsProcessHandoverReqAck(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
         /*Raise Alarm to Stack Manager */
          bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

          bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    	  return (SS7_FAILURE);
     }
  }
    return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsProcessHandoverFailure
*
*      Desc:  This function will process Handover Failure
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessHandoverFailure
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessHandoverFailure(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  U16bit cicVal = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit handOver = HANDOVER_FALSE;
  U8bit hooldbss = HOOLDBSS_FALSE;
  U8bit honewbss = HONEWBSS_FALSE;
  U32bit callId = 0;
  U8bit msgtype = 0;

  msgtype = BSSAP_MSG_HANDOVER_FAILURE;

  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessHandoverFailure(): call pointer NULL \n");
    return (SS7_FAILURE);	
  }
  
  bsIntfCb = intfCb; 
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessHandoverFailure(): Interface pointer NULL \n");
    return (SS7_FAILURE);	
  }
  BS_GET_HANDOVER(call->handoverFlagSet,handOver);
  BS_GET_HOOLDBSS(call->handoverFlagSet,hooldbss);
  BS_GET_HONEWBSS(call->handoverFlagSet,honewbss); 
   if(handOver == HANDOVER_TRUE)
   {
      if(hooldbss == HOOLDBSS_TRUE)
      {
         LOG_PRINT(CRITICAL,"BsProcessHandoverFailure: HandoverFailure for OldBss from BSC-APP \n");
      }
      else if(honewbss == HONEWBSS_TRUE)
      {
         LOG_PRINT(CRITICAL,"BsProcessHandoverFailure(): HandoverFailure for NewBss from BSC-APP \n");
         BS_SET_HANDOVERFAIL_TRUE(call->handoverFlagSet);
         cicVal = call->cic;
         callId = call->callId;
         if(cicVal)
         {
            if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
            {
                LOG_PRINT(CRITICAL,"BsProcessHandoverFailure(): Setting CIC call state Idle \n");
                BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[cicVal].flaglistSet);
                call->cic = 0;
            }
            else
            {
             LOG_PRINT(CRITICAL,"BsProcessHandoverFailure():HOFailure case: CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
                /*Raise Alarm to Stack Manager */
                bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

                bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    		return (SS7_FAILURE);	
            }
         }
         else if(callId)
         {   
             call->callId = 0;
             LOG_PRINT(CRITICAL,"BsProcessHandoverFailure(): Setting Call Id as zero \n");
         }
         else
         {
           LOG_PRINT(CRITICAL,"BsProcessHandoverFailure():Neither CIC and Call Id are present \n");
    	    return (SS7_FAILURE);	
         }
      }
   }   
   return (SS7_SUCCESS);	
}
/*
*
*      Fun:  BsProcessHandoverPerformed
*
*      Desc:  This function will process Handover Performed
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessHandoverPerformed
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount
)
#else
S16bit BsProcessHandoverPerformed(call,ie,iecount)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
#endif
{

  U8bit mType;
   mType = BSSAP_MSG_HANDOVER_PERFORMED;
  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessHandoverPerformed(): call pointer NULL \n");
    return (SS7_FAILURE);	
  }

   LOG_PRINT(INFO,"BsProcessHandoverPerformed :Setting Calltype as HO_CALL \n"); 
   call->callType = HO_CALL;
return (SS7_SUCCESS);
}


/*
*
*      Fun: BsProcessClearCommand
*
*      Desc:  This function will process Clear Command
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessClearCommand
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessClearCommand(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  U16bit cicVal = 0;
  U8bit cause = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit handOver = HANDOVER_FALSE;
  U8bit hafailure = HANDOVERFAIL_FALSE;
  U8bit hooldbss = HOOLDBSS_FALSE;
  U8bit honewbss = HONEWBSS_FALSE;
  U32bit callId = 0;
  U8bit msgtype = 0;
#ifdef BSSAP_HA
  HashEntry *callIdEntry = NULL;
  CallIdCb *callIdVal = NULL;
  int ret = RFAILED;
#endif

  msgtype = BSSAP_MSG_CLEAR_COMMAND;

  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessClearCommand(): call pointer NULL \n");
    return (SS7_FAILURE);
  }

  LOG_PRINT(INFO,"BsProcessClearCommand(): Clear Command recv \n");
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(INFO,"BsProcessClearCommand(): Interface pointer NULL \n");
    return (SS7_FAILURE);
  }  
  BS_GET_HANDOVERFAIL(call->handoverFlagSet,hafailure);
  BS_GET_HANDOVER(call->handoverFlagSet,handOver);
  BS_GET_HOOLDBSS(call->handoverFlagSet,hooldbss);
  BS_GET_HONEWBSS(call->handoverFlagSet,honewbss);
  if(call)
  {
    if(hafailure == HANDOVERFAIL_TRUE)
    {
      LOG_PRINT(INFO,"BsProcessClearCommand():No need for modify CIC for Handoverfailure case at NewBSC \n");
    }
    else
    {
       cicVal = call->cic;
       callId = call->callId;
       if (cicVal)
       {
           if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
           {
              /* By this we know clearly channel is released */
               LOG_PRINT(INFO,"BsProcessClearCommand():Clearing CIC[%d] from call and channelAlloc as FALSE \n",cicVal);
               call->channelAlloc = SS7_FALSE;
               BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[cicVal].flaglistSet);
               call->cic = 0;
           }
           else
           {
               LOG_PRINT(INFO,"BsProcessClearCommand(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);

#if 0
                /*Raise Alarm to Stack Manager */
                msgtype = BSSAP_MSG_CLEAR_COMMAND;
                bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

                bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

           }
       }
       else if(callId)
       {
          LOG_PRINT(INFO,"BsProcessClearCommand():Clearing CallId[%ld] from call \n",callId);
#ifdef BSSAP_HA
	  ret = HashListTbSearch(bsIntfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId),&callIdEntry);
	  if(ret != ROK)
	  {
            LOG_PRINT(CRITICAL,"BsProcessClearCommand():HashListTbSearch fail,CALLID[%ld] not found  hash list\n",callId);
	    return (SS7_FAILURE);
	  }
	  callIdVal = callIdEntry->data;
	  if(callIdVal)
	  {
	    LOG_PRINT(INFO,"BsProcessClearCommand():Deleting for CALLID[%d] \n",callIdVal->callId);
	  }
          ret = HashListTbDelete(bsIntfCb->callIdList,bsIntfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId));
	  if(ret != ROK)
	  {
	    LOG_PRINT(INFO,"BsProcessClearCommand():HashListTbDelete failed for CALLID[%ld]\n",callId);
	    return (SS7_FAILURE);
	  }
	  if(callIdVal)
	  {
	    free(callIdVal);
	    callIdVal = NULL;
	  }
#endif
          call->callId = 0;
       }
       else
       {
         LOG_PRINT(INFO,"BsProcessClearCommand():Neither CIC nor CAll Id present in Call pointer,only passing msg to App \n");
	return SS7_SUCCESS; 
       }
     }
     if(handOver == HANDOVER_TRUE)
     {
         LOG_PRINT(INFO,"BsProcessClearCommand():Handover is found in CALL \n");
         if(hooldbss == HOOLDBSS_TRUE)
         {
             LOG_PRINT(INFO,"BsProcessClearCommand():ClearCommand for OldBss from MSC \n");
             BS_SET_HANDOVER_FALSE(call->handoverFlagSet);
             BS_SET_HOOLDBSS_FALSE(call->handoverFlagSet);
	     return SS7_SUCCESS; 
         }
         else if(honewbss == HONEWBSS_TRUE)
         {
           LOG_PRINT(INFO,"BsProcessClearCommand():ClearCommand for NewBss from MSC \n");
            if(hafailure == HANDOVERFAIL_TRUE)
            {
               LOG_PRINT(INFO,"BsProcessClearCommand():ClearCommand for NewBss from MSC for Hofailure \n");
               BsSendFailureMsg(call,BSSAP_MSG_CLEAR_COMPLETE,cause,SS7_NULL,0,intfCb);
	       return SS7_FAILURE; 
            }
            else
            {
               LOG_PRINT(INFO,"BsProcessClearCommand():ClearCommand for NewBss from MSC No Hofailure \n");
	       return SS7_SUCCESS; 
            }
          }
        }
  }
	       return SS7_SUCCESS; 
}
/*
*
*      Fun: BsProcessClearRequest
*
*      Desc:  This function will process Clear Request
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessClearRequest
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessClearRequest(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
  U16bit cicVal = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U32bit callId = 0;
  U8bit msgtype = 0;
#ifdef BSSAP_HA
  HashEntry *callIdEntry = NULL;
  CallIdCb *callIdVal = NULL;
  int ret = RFAILED;
#endif

  msgtype = BSSAP_MSG_CLEAR_REQUEST;

  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessClearRequest(): call pointer NULL \n");
    return (SS7_FAILURE);	
  }
  cicVal = call->cic;
  callId = call->callId;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessClearRequest(): Interface pointer NULL \n");
    return (SS7_FAILURE);	
  }
  if(cicVal)
  {
     if(bsIntfCb->cicDataList[cicVal].cic == cicVal)
     {
        LOG_PRINT(INFO,"BsProcessClearRequest(): Setting CIC[%d] zero in Call pointer \n",cicVal);
        BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[cicVal].flaglistSet);
        call->cic = 0;
     }
     else
     {
    LOG_PRINT(INFO,"BsProcessClearRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
         /*Raise Alarm to Stack Manager */
         bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

         bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
     }
   }
   else if(callId)
   {
     LOG_PRINT(INFO,"BsProcessClearRequest(): Setting Call Id[%ld] zero in Call pointer \n",callId);
#ifdef BSSAP_HA
     ret = HashListTbSearch(bsIntfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId),&callIdEntry);
     if(ret != ROK)
     {
       LOG_PRINT(CRITICAL,"BsProcessClearRequest():HashListTbSearch fail,CALLID[%ld] not found  hash list\n",callId);
       return (SS7_FAILURE);
     }
     callIdVal = callIdEntry->data;
     if(callIdVal)
     {
       LOG_PRINT(INFO,"BsProcessClearRequest():Deleting for CALLID[%d] \n",callIdVal->callId);
     }
     ret = HashListTbDelete(bsIntfCb->callIdList,bsIntfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId));
     if(ret != ROK)
     {
       LOG_PRINT(INFO,"BsProcessClearRequest():HashListTbDelete failed for CALLID[%ld]\n",callId);
       return (SS7_FAILURE);
     }
     if(callIdVal)
     {
       free(callIdVal);
       callIdVal = NULL;
     }
#endif
     call->callId = 0;
   }
   else
   {
    LOG_PRINT(INFO,"BsProcessClearRequest(): Neither Call Id nor CIC present in Call pointer \n");
   }
   if(call->timerId != BSSAP_INVALID_TMRID)
   {
      /*STOP Timer BSSAP_T_10 */
      bsStopConTmr(call,BSSAP_T_10);
   }
   if(call->callType == HO_CALL)
   {
     LOG_PRINT(INFO,"BsProcessClearRequest():callType is HO_CALL:do nothing \n");
   }
	return (SS7_SUCCESS);
}

/*
*
*      Fun: BsProcessCompleteLayer3Info
*
*      Desc:  This function will process Complete layer3 Info
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCompleteLayer3Info
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
Data *databuf,
MsgLen  datalen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCompleteLayer3Info(call,ie,iecount,databuf,datalen,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
Data *databuf;
MsgLen  datalen;
BsIntfCb *intfCb;
#endif
{
   BSSAP_IE *ieData = SS7_NULL;
   Data      buf[BSSAP_DATA_LEN];
   MsgLen    buflen; 
   U8bit mType = 0;
   S16bit ret;

   if(call == SS7_NULL)
   {
    LOG_PRINT(CRITICAL,"BsProcessCompleteLayer3Info(): call pointer NULL \n");
    return (SS7_FAILURE);
   }
   
   ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_LAYER3_INFORMATION);
   if(!ieData)
   {
     LOG_PRINT(INFO,"BsProcessCompleteLayer3Info(): IEI_LAYER3_INFORMATION Not Found \n");
       call->callType = SS7_FALSE;
       return (SS7_FAILURE);
   }
   memset((U8bit *)buf, 0,  BSSAP_DATA_LEN);
   buflen = ieData->param_length - (sizeof(ieData->param_data.l3_info) - 1);
   ss7_memcpy((U8bit *)buf,(U8bit *)ieData->param_data.l3_info.layer3_info, buflen);
   mType = buf[L3MSG_TYPE_POS];
   LOG_PRINT(INFO,"BsProcessCompleteLayer3Info(): Msg Type for L3 info[%x] \n",buf[L3MSG_TYPE_POS]);
  if (mType == BSSAP_MSG_CM_SERVICE_REQUEST)
  {
      LOG_PRINT(INFO,"BS: MSG TO MSC :callrefId[%lu] appId[%lu] BsProcessCompleteLayer3Info: CM_SERVICE_REQUEST \n",call->suInstId,call->appId);
      call->callType = MO_CALL;
  }
  else if (mType == BSSAP_MSG_PAGING_RESPONSE)
  {
      LOG_PRINT(INFO,"BS: MSG TO MSC :callrefId[%lu] appId[%lu] BsProcessCompleteLayer3Info: PAGING_RESPONSE \n",call->suInstId,call->appId);
      call->callType = MT_CALL;
  }
  else if (mType == BSSAP_MSG_LOCATION_UPDATING_REQUEST)
  {
      LOG_PRINT(INFO,"BS: MSG TO MSC :callrefId[%lu] appId[%lu] BsProcessCompleteLayer3Info: LOCATION_UPDATE REQUEST \n",call->suInstId,call->appId);
      call->callType = LU_CALL;
  }
  else if (mType == BSSAP_MSG_IMSI_DETACH_INDICATION)
  {
      LOG_PRINT(INFO,"BS: MSG TO MSC :callrefId[%lu] appId[%lu] BsProcessCompleteLayer3Info: IMSI_DETACH\n",call->suInstId,call->appId);
      call->callType = IMSI_DETACH;
  }
  else
  { 
     /*UPDATE FOR:Raise Alarm to APP:5116*/
     LOG_PRINT(CRITICAL,"BsProcessCompleteLayer3Info(): Wrong L3 Message:mType[%d]\n",mType);
     call->callType = SS7_FALSE;
     return (SS7_FAILURE);	
  }
  ret = BsSendConReq(databuf,datalen,call->suInstId,intfCb);
  return (ret);
}
/*
*
*      Fun: BsProcessChangeCircuitAck
*
*      Desc:  This function will process ChangeCircuitAck
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessChangeCircuitAck
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessChangeCircuitAck(call,ie,iecount,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 U16bit oldcicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec =  SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit localState = 0;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_CHANGE_CKT_ACK;

 if(call == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessChangeCircuitAck(): call pointer NULL \n");
    return (SS7_FAILURE);
 }
 bsIntfCb = intfCb;
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessChangeCircuitAck():CIC is Not Present\n");
    return (SS7_FAILURE);

 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 if(bsIntfCb->cicDataList != SS7_NULL)
 { 
   crec = &bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    crec = SS7_NULL;
 }
 if((crec != SS7_NULL) && (crec->cic == cicVal))
 {
    BS_GET_LOCALSTATE(crec->flaglistSet,localState);
    if(localState == CIC_ST_LOCAL_BLOCK)
    {
      LOG_PRINT(CRITICAL,"BsProcessChangeCircuitAck():CIC localState is Blocked\n");
    	return (SS7_FAILURE);
    } 
    else if(localState == CIC_ST_LOCAL_UNBLK)
      {
          if(call->cic > 0)
          {
              oldcicVal = call->cic;
              if(bsIntfCb->cicDataList[oldcicVal].cic == oldcicVal)
              {
                  BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[oldcicVal].flaglistSet);
                  call->cic = 0;
              }
              else
              {
                  /*Send Error to App*/
                  LOG_PRINT(CRITICAL,"BsProcessChangeCircuitAck():CIC[%d] is Not Configured\n",oldcicVal);
                  BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,oldcicVal,BSSAP_MSG_CHANGE_CKT_ACK,intfCb);
    		  return (SS7_FAILURE);
              }
          
              call->cic = crec->cic;
              call->msgType = BSSAP_MSG_CHANGE_CKT_ACK;
          }
          else
          {
           /*Report Error to App */
           BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CHANGE_CKT_ACK,intfCb);
           LOG_PRINT(CRITICAL,"BsProcessChangeCircuitAck():CIC is Not allocated to exiting call\n");
    		  return (SS7_FAILURE);
          }       
     } 
 }
 else
 {
     LOG_PRINT(CRITICAL,"BsProcessChangeCircuitAck(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CHANGE_CKT_ACK,intfCb);
    return (SS7_FAILURE);
 } 
    return (SS7_SUCCESS);

}
/*
*
*      Fun: BsProcessOverloadInd
*
*      Desc:  This function will process OverloadInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessOverloadInd
(
BsIntfCb *intfCb
)
#else
S16bit BsProcessOverloadInd(intfCb)
BsIntfCb *intfCb;
#endif
{
 BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit mType;

 mType = BSSAP_MSG_OVERLOAD;
 bsIntfCb = intfCb;
 if(bsIntfCb->Fistoverld == SS7_TRUE)
 {
   bsStartIntfTmr(BSSAP_T_17,bsIntfCb);
   bsStartIntfTmr(BSSAP_T_18,bsIntfCb);
   bsIntfCb->Fistoverld=SS7_FALSE;
 }
else if((bsIntfCb->overloadT17 >0)  && (bsIntfCb->overloadT18 >0 ))
 {
   /*Ignore Overload */
  return (SS7_FAILURE);	
 }
else if((bsIntfCb->overloadT17 == 0)  && (bsIntfCb->overloadT18 >0 ))
 {
   bsStartIntfTmr(BSSAP_T_17,bsIntfCb);
   bsStartIntfTmr(BSSAP_T_18,bsIntfCb);
 /*msg pass to App*/
 } 
  return (SS7_SUCCESS);	
}
/*
*
*      Fun: BsProcessBlockRequest
*
*      Desc:  This function will process BlockRequest
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessBlockRequest
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessBlockRequest(ie,iecount,databuff,dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit localState = 0;
 U8bit statusFlag = 0;
 U8bit msgtype = 0;

  msgtype = BSSAP_MSG_BLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockRequest():Interface pointer bsIntfCb is NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockRequest():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessBlockRequest():BLOCK Received From APP for CIC value[%d]\n",cicVal);
if(cicVal == 0)
 {
    /*Report Error to App */
     LOG_PRINT(CRITICAL,"BsProcessBlockRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_BLOCK,intfCb);
    return (SS7_FAILURE);
 }
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec = &bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockRequest():cic DB NULL");
    return (SS7_FAILURE);
 } 
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockRequest():crec pointer is NULL\n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
 {
    BS_GET_LOCALSTATE(crec->flaglistSet,localState);
    if(localState == CIC_ST_LOCAL_BLOCK)
    {
      LOG_PRINT(INFO,"BsProcessBlockRequest():CIC[%d] localState is Already BLOCK \n",cicVal);
      BS_GET_STATUSFLAG(crec->flaglistSet,statusFlag);
      if(statusFlag == CIC_ST_STATUSFLAG_TRUE)
      {
          BS_SET_STATUSFLAG_FALSE(crec->flaglistSet);
          /*check timer is already running*/
          /*if yes then cancel and start new timer*/
           if(crec->timerId == BSSAP_T_1)
           {
             bsStopCirTmr(crec,BSSAP_T_1);

           }
        /*  bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);*/
      }
    }
    else
    {
     LOG_PRINT(INFO,"BsProcessBlockRequest():CIC[%d] localState is UNBLOCK \n",cicVal);
          /*check timer is already running*/
          /*if yes then cancel and start new timer*/
           if(crec->timerId == BSSAP_T_1)
           {
             bsStopCirTmr(crec,BSSAP_T_1);
           }
      /*     bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb); */

         /*crec->localState = CIC_ST_BLOCK;*/
         BS_SET_LOCALSTATE_BLOCK(crec->flaglistSet); 
     	   LOG_PRINT(INFO,"BsProcessBlockRequest():Setting CIC[%d] localState is BLOCK \n",cicVal);
    }
 }
 else
 {
    /*Report Error to App */
     LOG_PRINT(CRITICAL,"BsProcessBlockRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_BLOCK,intfCb);
    return (SS7_FAILURE);
  }
	crec->databuf = (U8bit *)bssap_malloc(dataLen);
  	if(crec->databuf == SS7_NULL)
  	return (SS7_FAILURE);

   /*Storing Block msg for timeout */
   crec->msgtype = BSSAP_MSG_BLOCK;
   crec->datalen = dataLen;
   ss7_memcpy((U8bit*)crec->databuf,(U8bit*)databuff,dataLen);
   bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);
   LOG_PRINT(INFO,"BsProcessBlockRequest():BLOCK REQ for CIC[%d] process successfully \n",cicVal);
   return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessBlockAckInd
*
*      Desc:  This function will process BlockAckInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessBlockAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessBlockAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit localState = 0;
 U8bit msgtype = 0;

  msgtype = BSSAP_MSG_BLOCK_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckInd():Interface pointer is NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckInd():CIC IE  is Not Present in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessBlockAckInd(): BLOCK ACK received for CIC[%d]\n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
   LOG_PRINT(CRITICAL,"BsProcessBlockAckInd():cic[%d] not configured",cicVal);
   crec = SS7_NULL;
 }
 if((crec != SS7_NULL) && (crec->cic == cicVal))
 {
    BS_GET_LOCALSTATE(crec->flaglistSet,localState);
    if(localState == CIC_ST_LOCAL_BLOCK)
    {
      if(crec->timerId == BSSAP_T_1)
       {
	   bssap_free((Data *)crec->databuf);	/* Added to free of CREC by BSSAP_free */
           crec->databuf = SS7_NULL;
           crec->datalen = 0;/*Mantis 23336 need to set zero in case databuf set to null */
           bsStopCirTmr(crec,BSSAP_T_1);
       }

    }
   else
    {
      BS_SET_STATUSFLAG_TRUE(crec->flaglistSet);
      LOG_PRINT(INFO,"BsProcessBlockAckInd():localState is UnBlock for CIC[%d], therefore Sending Unblock to Peer\n",cicVal);
      BsSendCktMsg(BSSAP_MSG_UNBLOCK,cicVal,SS7_NULL,intfCb);
      return (SS7_FAILURE);
    }
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
    /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_BLOCK_ACK,intfCb);
    /*Send Unequipped to peer*/
      LOG_PRINT(CRITICAL,"BsProcessBlockAckInd() :Sending UNEQUIPPED Error to APP \n");
    BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,crec->cic,SS7_NULL,intfCb);
    return (SS7_FAILURE);
  }
    return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessUnBlockRequest
*
*      Desc:  This function will process UnBlockRequest
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessUnBlockRequest
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUnBlockRequest(ie,iecount,databuff,dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit localState = 0;
 U8bit statusFlag = 0;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_UNBLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockRequest():Interface pointer is NULL\n");
    return (SS7_FAILURE);

 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockRequest():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessUnBlockRequest():UNBLOCK From APP for CIC value[%d]\n",cicVal);
if(cicVal == 0)
 {
     LOG_PRINT(CRITICAL,"BsProcessUnBlockRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_UNBLOCK,intfCb);
    return (SS7_FAILURE);
 }
if(bsIntfCb->cicDataList != SS7_NULL)
{
 crec = &bsIntfCb->cicDataList[cicVal];
}
else
{
    LOG_PRINT(CRITICAL,"BsProcessUnBlockRequest():cic DB NULL");
    return (SS7_FAILURE);
}
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockRequest():crec pointer is NULL\n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
 {
    BS_GET_LOCALSTATE(crec->flaglistSet,localState);
    if(localState == CIC_ST_LOCAL_BLOCK)
    {
       LOG_PRINT(INFO,"BsProcessUnBlockRequest():CIC[%d] localState is BLOCK \n",cicVal);
      if(crec->timerId == BSSAP_T_1)
       {
           bsStopCirTmr(crec,BSSAP_T_1);

       }
 /*     bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);*/
      BS_SET_LOCALSTATE_UNBLOCK(crec->flaglistSet);
     LOG_PRINT(INFO,"BsProcessUnBlockRequest():Setting CIC[%d] localState is UNBLOCK \n",cicVal);

    }
   else
    {
     LOG_PRINT(INFO,"BsProcessUnBlockRequest():CIC[%d] localState is Already UNBLOCK \n",cicVal);
       BS_GET_STATUSFLAG(crec->flaglistSet,statusFlag);
       if(statusFlag == CIC_ST_STATUSFLAG_TRUE)
       {
          /*crec->statusFlag = FALSE;*/
          BS_SET_STATUSFLAG_FALSE(crec->flaglistSet);
         if(crec->timerId == BSSAP_T_1)
         {
           bsStopCirTmr(crec,BSSAP_T_1);
         }
         /*Restart the timer again*/
    /*      bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);*/
       }
      else
       {
            LOG_PRINT(CRITICAL,"BsProcessUnBlockRequest():CIC Already Unblock \n");
    	    return (SS7_FAILURE);
       }
   }
 }
 else
 {
     LOG_PRINT(INFO,"BsProcessUnBlockRequest(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_UNBLOCK,intfCb);
    return (SS7_FAILURE);
}
      crec->databuf = (U8bit *)bssap_malloc(dataLen);
      if(crec->databuf == SS7_NULL)
      return (SS7_FAILURE);
   /*Storing Block msg for timeout */
   crec->msgtype = BSSAP_MSG_UNBLOCK;
   crec->datalen = dataLen;
   ss7_memcpy((U8bit*)crec->databuf,(U8bit*)databuff,dataLen);
	 bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);
   LOG_PRINT(INFO,"BsProcessUnBlockRequest():UNBLOCK REQ for CIC[%d] process successfully \n",cicVal);
  return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessUnBlockAckInd
*
*      Desc:  This function will process UnBlockAckInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessUnBlockAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUnBlockAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit localState = 0;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_UNBLOCK_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd():Interface pointer is NULL\n");
    return (SS7_FAILURE);	
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);	
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessUnBlockAckInd():UNBLOCK ACK received for CIC[%d]\n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
  crec = &bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd():cic DB NULL");
    return (SS7_FAILURE);	
 } 
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd():crec pointer is NULL\n");
    return (SS7_FAILURE);	
 }
 if(crec->cic == cicVal)
  {
    BS_GET_LOCALSTATE(crec->flaglistSet,localState);
    if(localState == CIC_ST_LOCAL_BLOCK)
    {
        /*crec->statusFlag = TRUE;*/
        BS_SET_STATUSFLAG_TRUE(crec->flaglistSet);
         if(crec->timerId == BSSAP_T_1)
         {
	         bssap_free((Data *)crec->databuf);	/* Added  for CREC free databuf */
           crec->databuf = SS7_NULL;
           crec->datalen = 0;/*Mantis 23336 need to set zero in case databuf set to null */
           bsStopCirTmr(crec,BSSAP_T_1);
         }
         bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

      bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_IN_BLOCK_STATE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

        /*Send Block to Peer */
       LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd:localState is BLOCK for CIC[%d],therefore sending BLOCK to peer\n",cicVal);
       BsSendCktMsg(BSSAP_MSG_BLOCK,crec->cic,SS7_NULL,intfCb);
    }
    else
   {
         if(crec->timerId == BSSAP_T_1)
         {
	   			 bssap_free((Data *)crec->databuf);	
           crec->databuf = SS7_NULL;
           crec->datalen = 0;/*Mantis 23336 need to set zero in case databuf set to null */
           bsStopCirTmr(crec,BSSAP_T_1);
         }
         else
         {
               LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd():localState of CIC [%d] Already UnBlock \n",cicVal);
	       return (SS7_FAILURE);	
         }
    }
  }
 else
  {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif 
   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_UNBLOCK_ACK,intfCb);
    /*Send Unequipped to peer*/
      LOG_PRINT(CRITICAL,"BsProcessUnBlockAckInd() :Sending UNEQUIPPED Error to APP \n");
    BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,crec->cic,SS7_NULL,intfCb);
    return (SS7_FAILURE);	
  }
  return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessBlockInd
*
*      Desc:  This function will process BlockInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessBlockInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessBlockInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit remoteState = 0;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_BLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockInd():Interface pointer is NULL\n");
    return (SS7_FAILURE);	
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockInd():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);	
 }
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    LOG_PRINT(INFO,"BsProcessBlockInd():BLOCK Received from PEER for CIC[%d]\n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
  crec = &bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockInd():CIC Not configured \n");
    return (SS7_FAILURE);	
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockInd():crec pointer is NULL\n");
    return (SS7_FAILURE);	
 }
 if(crec->cic == cicVal)
  {
     BS_GET_REMOTESTATE(crec->flaglistSet,remoteState);
     if(remoteState == CIC_ST_REMOTE_BLOCK)
     {
        /*sendBlock Ack */
        LOG_PRINT(CRITICAL,"BsProcessBlockInd():Remote state block sending BLOCK ACK for CIC[%d]\n",cicVal);
        BsSendCktMsg(BSSAP_MSG_BLOCK_ACK,crec->cic,SS7_NULL,intfCb);
        return (SS7_FAILURE);	
     }
     else
     {
         BS_SET_REMOTESTATE_BLOCK(crec->flaglistSet); 
         LOG_PRINT(INFO,"BsProcessBlockInd(): Setting Remote State as BLOCK for cicval[%d]\n",cicVal);
         if(crec->timerId == BSSAP_T_1)
         {
           bsStopCirTmr(crec,BSSAP_T_1);
         }
     }
  }
 else
  {
    LOG_PRINT(CRITICAL,"BsProcessBlockInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_BLOCK,intfCb);
    /*Send Unequipped to peer*/
    LOG_PRINT(CRITICAL,"BsProcessBlockInd():Sending UNEQUIPPED_CKT to Peer \n");
    BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,crec->cic,SS7_NULL,intfCb);
    return (SS7_FAILURE);	
  }
    return (SS7_SUCCESS);	
}
/*
*
*      Fun: BsProcessBlockAckReq
*
*      Desc:  This function will process BlockAckReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessBlockAckReq
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessBlockAckReq(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit remoteState = 0;
 U32bit msgtype = 0;

 msgtype = BSSAP_MSG_BLOCK_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckReq():Interface pointer is NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckReq():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
  LOG_PRINT(INFO,"BsProcessBlockAckReq():BLOCK ACK Received from APP for CIC[%d]\n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
  crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckReq():CIC not configured \n");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckReq():crec pointer is NULL\n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
  {
   BS_GET_REMOTESTATE(crec->flaglistSet,remoteState);
   if(remoteState == CIC_ST_REMOTE_BLOCK)
   {
          /*nothing to do */
    LOG_PRINT(INFO,"BsProcessBlockAckReq():Remote state alraedy BLOCKED , hence do nothing\n");
   }
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessBlockAckReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);

#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_BLOCK_ACK,intfCb);
    return (SS7_FAILURE);
  }
    return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessUnBlockInd
*
*      Desc:  This function will process UnBlockInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessUnBlockInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUnBlockInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit remoteState = 0;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_UNBLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockInd():Interface pointer is NULL\n");
    return (SS7_FAILURE);	
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockInd():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);	
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessUnBlockInd():UNBLOCK received from PEER for CIC[%d]\n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockInd():CIC not configured\n");
    return (SS7_FAILURE);	
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockInd():crec pointer is NULL\n");
    return (SS7_FAILURE);	
 }
 if(crec->cic == cicVal)
  {
   BS_GET_REMOTESTATE(crec->flaglistSet,remoteState);
   if(remoteState == CIC_ST_REMOTE_BLOCK)
   {
     /*crec->remoteState = CIC_ST_UNBLK;*/
     BS_SET_REMOTESTATE_UNBLOCK(crec->flaglistSet);
    LOG_PRINT(INFO,"BsProcessUnBlockInd():Setting RemoteState UNBLOCKED  for CIC[%d]\n",cicVal);
   }
  else
   {
      /*send UnBlock Ack to Peer */
      LOG_PRINT(CRITICAL,"BsProcessUnBlockInd():RemoteState already UNBLOCKED for CIC[%d],sending UNBLOCK ACK to Peer \n",cicVal);
      BsSendCktMsg(BSSAP_MSG_UNBLOCK_ACK,crec->cic,SS7_NULL,intfCb);
      return (SS7_FAILURE);	
   }
  }
 else
  {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
    /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_UNBLOCK,intfCb);
    /*Send Unequipped to peer*/
/*    printf("BsProcessUnBlockInd:Sending UNEQUIPPED_CKT to Peer \n");*/
    LOG_PRINT(CRITICAL,"BsProcessUnBlockInd():Sending UNEQUIPPED_CKT to Peer \n");
    BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,crec->cic,SS7_NULL,intfCb);
    return (SS7_FAILURE);	
  }
    return (SS7_SUCCESS);	
}
/*
*
*      Fun: BsProcessUnBlockAckReq
*
*      Desc:  This function will process UnBlockAckReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
S16bit BsProcessUnBlockAckReq
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUnBlockAckReq(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit remoteState = 0;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_UNBLOCK_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckReq():Interface pointer is NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckReq():CIC IE is Not Presento in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    LOG_PRINT(INFO,"BsProcessUnBlockAckReq():UNBLOCK ACK received from APP for CIC[%d]\n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec = &bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckReq():cic DB NULL");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckReq():crec pointer is NULL\n");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 if(crec->cic == cicVal)
  {
   BS_GET_REMOTESTATE(crec->flaglistSet,remoteState);
   if(remoteState == CIC_ST_REMOTE_BLOCK)
   {
    /*Nothing to do*/
   }

  }
 else
  {
    LOG_PRINT(CRITICAL,"BsProcessUnBlockAckReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif /

   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_UNBLOCK_ACK,intfCb);
    return (SS7_FAILURE);
  }
    return (SS7_SUCCESS);

}
/*
*
*      Fun: BsProcessResetCktReq
*
*      Desc:  This function will process ResetCktReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessResetCktReq
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetCktReq(ie,iecount,databuff,dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_RESET_CIRCUIT;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktReq():No Interface found(bsIntfCb is NULL)\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktReq():CIC IE is Not Present RESET CKT msg\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessResetCktReq(): RESET CIRCUIT recv from APP for CIC[%d] \n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktReq():cic not configured");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktReq():crec pointer is NULL)\n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
 {
    if(crec->timerId != BSSAP_INVALID_TMRID)
    {
       bsStopCirTmr(crec,crec->timerId);
    }
 /*   bsStartCirTmr(BSSAP_T_19,crec,bsIntfCb);*/
    BS_SET_CALLSTATE_IDLE(crec->flaglistSet);
    crec->databuf = (U8bit *)bssap_malloc(dataLen);
    if(crec->databuf == SS7_NULL)
    return (SS7_FAILURE);
      /*Storing Reset msg for timeout */
    crec->msgtype = BSSAP_MSG_RESET_CIRCUIT;
    crec->datalen = dataLen;
    ss7_memcpy((U8bit*)crec->databuf,(U8bit*)databuff,dataLen);
    bsStartCirTmr(BSSAP_T_19,crec,bsIntfCb);
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);

#if 0
    BSCORE(CRITICAL,BSERR_CORE_CICID,DEFAULT,DEFAULT,DEFAULT,DEFAULT,"BsProcessResetCktReq():cic not found",cicVal);
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_RESET_CIRCUIT,intfCb);
    return (SS7_FAILURE);
 }
    return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessResetCktAckInd
*
*      Desc:  This function will process ResetCktAckInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessResetCktAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetCktAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit msgtype = 0;

  msgtype = BSSAP_MSG_RESET_CIRCUIT_ACK;
 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(INFO,"BsProcessResetCktAckInd():Interface pointer is NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(INFO,"BsProcessResetCktAckInd():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessResetCktAckInd(): RESET CIRCUIT ACK recv from PEER for CIC[%d] \n",cicVal);
 if(bsIntfCb->cicDataList != NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckInd():cic not configured \n");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckInd():crec pointer is NULL\n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
  {
      if(crec->timerId == BSSAP_T_19)
      {
         bsStopCirTmr(crec,BSSAP_T_19);
	bssap_free((Data *)crec->databuf);
        crec->databuf = SS7_NULL;
        crec->datalen = 0;
      }
      else
      {
         LOG_PRINT(CRITICAL,"BsProcessResetCktAckInd(): BSSAP_T_19 not running \n");
    	return (SS7_FAILURE);
      }
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif 
    /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_RESET_CIRCUIT_ACK,intfCb);
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckInd():Sending UNEQUIPPED_CKT to PEER\n");
    /*Send Unequipped to peer*/
    BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,crec->cic,SS7_NULL,intfCb);
    return (SS7_FAILURE);
  }
  return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessResetCktInd
*
*      Desc:  This function will process ResetCktInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessResetCktInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetCktInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit msgtype = 0;

  msgtype = BSSAP_MSG_RESET_CIRCUIT;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktInd():No interface found(bsIntfCb is NULL) \n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktInd(): CIC is Not Present RESET CIRCUIT msg \n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(CRITICAL,"BsProcessResetCktInd(): RESET CKT recv from PEER for CIC[%d] \n",cicVal);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktInd():cic not configured \n");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktInd():crec pointer is NULL \n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
  {
     if(crec->timerId != BSSAP_INVALID_TMRID)
     {
       bsStopCirTmr(crec,crec->timerId);
     }
     BS_SET_CALLSTATE_IDLE(crec->flaglistSet);
     BS_SET_REMOTESTATE_UNBLOCK(crec->flaglistSet);
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessResetCktInd: CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    /*Report Error to App */

    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_RESET_CIRCUIT,intfCb);
    LOG_PRINT(CRITICAL,"BsProcessResetCktInd():Sending Unequipped to PEER\n");
    BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,crec->cic,SS7_NULL,intfCb);
    /*Send Unequipped to peer*/
    return (SS7_FAILURE);
  }
    return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessResetCktAckReq
*
*      Desc:  This function will process ResetCktAckReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessResetCktAckReq
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetCktAckReq(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 U8bit msgtype = 0;

 msgtype = BSSAP_MSG_RESET_CIRCUIT_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb ==  SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckReq():No Interface found (bsIntfCb is NULL)\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckReq():CIC is Not Present RESET CIRCUIT ACK msg\n");
    return (SS7_FAILURE);

 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 LOG_PRINT(INFO,"BsProcessResetCktAckReq():RESET CIRCUIT ACK recv from APP for CIC[%d] \n",cicVal);
 if(bsIntfCb->cicDataList != NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckReq():cic not configured");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
   LOG_PRINT(CRITICAL,"BsProcessResetCktAckReq:crec pointer is NULL)\n");
    return (SS7_FAILURE);
 }
 if(crec->cic == cicVal)
 {
    /*Nothing to do*/
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessResetCktAckReq: CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif 
   /*Report Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_RESET_CIRCUIT_ACK,intfCb);
    return (SS7_FAILURE);
 }
    return (SS7_SUCCESS);
}
/*
*
*
*      Fun: BsProcessResetReq
*
*      Desc:  This function will process ResetReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessResetReq
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetReq(ie,iecount,databuff,dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
 U32bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 U8bit mType = 0; 
#ifdef BSSAP_HA
 int ret = RFAILED;
#endif

 mType = BSSAP_MSG_RESET;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetReq(): No Interface found(bsIntfCb is NULL) \n");
    return (SS7_FAILURE);
 }
 BSDEBUGPRINT("BS: RESET Send TO PEER:DPC[%d] INTFID[%d] : GCNID[%d]\n",bsIntfCb->phyDpc,bsIntfCb->intfId,bsIntfCb->bscId);
 if(bsIntfCb->rstSndtimerId != BSSAP_INVALID_TMRID)
 {
    bsStopIntfTmr(bsIntfCb,BSSAP_T_4);/*No meaning of cicval */
    bsIntfCb->rstSndtimerId = BSSAP_INVALID_TMRID;
 }
 if (bsIntfCb->cicDataList != SS7_NULL) 
 {
    LOG_PRINT(INFO,"BsProcessResetReq(): startCic[%ld]  endCic[%ld]\n",bsIntfCb->startCic,bsIntfCb->endCic);
 for(cicVal=bsIntfCb->startCic;cicVal <= bsIntfCb->endCic;cicVal++)
 {
    crec=&bsIntfCb->cicDataList[cicVal];
    if(crec->cic==cicVal)
    {
      BS_SET_CALLSTATE_IDLE(crec->flaglistSet); 
      BS_SET_LOCALSTATE_UNBLOCK(crec->flaglistSet);
      BS_SET_REMOTESTATE_UNBLOCK(crec->flaglistSet);
      crec->datalen = 0; /*Mantis 23336 need to set zero in case databuf set to null */
      if(crec->timerId != BSSAP_INVALID_TMRID)
      {
          LOG_PRINT(INFO,"BsProcessResetReq():STOPPING CIRCUIT Timer for cicval[%d]\n",cicVal);
          bsStopCirTmr(crec,crec->timerId);
      }
    }
 }
 }
     
 bsIntfCb->databuf = (U8bit *)bssap_malloc(dataLen);

 if(bsIntfCb->databuf == SS7_NULL)
 {
   LOG_PRINT(CRITICAL,"BsProcessResetReq(): bssap_malloc Failed for bsIntfCb->databuf \n");
   return (SS7_FAILURE);
 }

   /*Storing Reset msg for timeout */
   bsIntfCb->datalen = dataLen;
   ss7_memcpy((U8bit*)bsIntfCb->databuf,(U8bit*)databuff,dataLen);
   
   bsStartIntfTmr(BSSAP_T_4,bsIntfCb);
   bsIntfCb->rstSndtimerId = BSSAP_T_4;
#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
   if(ret == RFAILED)
   {
     LOG_PRINT(CRITICAL,"BsProcessResetReq(): SendInterfaceAddUpdateToPeer Failed \n");
   }
#endif
   LOG_PRINT(INFO,"BS: BsProcessResetReq(): RESET REQ process successfully\n");
   return (SS7_SUCCESS);
}

/*
*
*      Fun: BsProcessResetAckInd
*
*      Desc:  This function will process ResetAckInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessResetAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 BsIntfCb *bsIntfCb = SS7_NULL;
#ifdef BSSAP_HA
 int ret = RFAILED;
#endif


 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetAckInd(): No interface found(bsIntfCb is NULL) \n");
    return (SS7_FAILURE);
 }
 LOG_PRINT(INFO,"BS: RESET ACK Received FRM PEER: DPC[%d]: INTFID[%d]: GCNID[%d] \n",bsIntfCb->phyDpc,bsIntfCb->intfId,bsIntfCb->bscId);
 LOG_PRINT(INFO,"BS: Reset Ack Received : bsIntfCb->rstSndtimerId[%d] \n",bsIntfCb->rstSndtimerId);
 if(bsIntfCb->rstSndtimerId !=  BSSAP_INVALID_TMRID)
 {
    LOG_PRINT(INFO,"BsProcessResetAckInd(): Going to Stop BSSAP_T_4 \n");
    bsStopIntfTmr(bsIntfCb,BSSAP_T_4);/*No meaning of CIC value*/
    bsIntfCb->rstSndtimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->t4.timer_id_key = SS7_FALSE;
    bssap_free((Data *)bsIntfCb->databuf);
    bsIntfCb->databuf = SS7_NULL;
    bsIntfCb->datalen = 0;
 }
#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
   if(ret == RFAILED)
   {
     LOG_PRINT(CRITICAL,"BsProcessResetAckInd(): SendInterfaceAddUpdateToPeer Failed \n");
   }
#endif
  return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessResetInd
*
*      Desc:  This function will process ResetInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessResetInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 BsIntfCb *bsIntfCb = SS7_NULL;
 U8bit mType = 0; 
 BSSAP_IE *ieData = SS7_NULL;
#ifdef BSSAP_HA
 int ret = RFAILED;
#endif

 mType = BSSAP_MSG_RESET;
 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
   LOG_PRINT(CRITICAL,"BsProcessResetInd(): No Interface found(bsIntfCb is SS7_NULL) \n");
   return (SS7_FAILURE);
 }
  BSDEBUGPRINT("BS: RESET Received FRM PEER: DPC[%d]: INTFId[%d] : GCNID[%d]\n",bsIntfCb->phyDpc,bsIntfCb->intfId,bsIntfCb->bscId);

 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_AIF_SELECTOR);

  /*Refer(48008-880:3.1.4.3.3):Stopping Trbsc timer which may be running for RESET IP procedure:
    when "A-Interface Selector for RESET" indicating IP is present or 
     if the "A-Interface Selector for RESET" is not present in the RESET message */
 if((!ieData)|| ((ieData) && ((ieData->param_data.aif_selector.indicator & 0x02) == 0x02)))
 {
  if(bsIntfCb->TrbsctimerId != BSSAP_INVALID_TMRID)
  {
    bsStopIntfTmr(bsIntfCb,BSSAP_T_RBSC);
    bsIntfCb->TrbsctimerId = BSSAP_INVALID_TMRID;
    bssap_free((Data *)bsIntfCb->databuf); 
    bsIntfCb->databuf = SS7_NULL;
    bsIntfCb->datalen = 0;
  }
 }
  if(bsIntfCb->rstRcvtimerId != BSSAP_INVALID_TMRID)
  {
     bsStopIntfTmr(bsIntfCb,BSSAP_T_13);/*No meaning of cicval */
     bsIntfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;
  }
  LOG_PRINT(INFO,"BsProcessResetInd(): START TIMER T13 for INTFID[%d] : GCNID[%d]\n",bsIntfCb->intfId,bsIntfCb->bscId);
  bsIntfCb->rstRcvtimerId = BSSAP_T_13;
  bsStartIntfTmr(BSSAP_T_13,bsIntfCb);/*No meaning of cicval */
#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
   if(ret == RFAILED)
   {
     LOG_PRINT(CRITICAL,"BsProcessResetAckInd(): SendInterfaceAddUpdateToPeer Failed \n");
   }
#endif
  return (SS7_SUCCESS); 
}
/*
*
*      Fun: BsProcessResetAckReq
*
*      Desc:  This function will process ResetAckReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessResetAckReq
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetAckReq(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 BsIntfCb *bsIntfCb = SS7_NULL;
#ifdef BSSAP_HA
 int ret = RFAILED;
#endif

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessResetAckReq():Interface pointer bsIntfCb is Null");
    return (SS7_FAILURE);
 }
 LOG_PRINT(INFO,"BS: RESET ACK Received FRM APP: DPC[%d]: INTFID[%d]: GCNID[%d] \n",bsIntfCb->phyDpc,bsIntfCb->intfId,bsIntfCb->bscId);
 if(bsIntfCb->rstRcvtimerId != BSSAP_INVALID_TMRID)
 {
      bsStopIntfTmr(bsIntfCb,BSSAP_T_13);
      bsIntfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;
      bsIntfCb->t13.timer_id_key = SS7_FALSE;
 }
#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
   if(ret == RFAILED)
   {
     LOG_PRINT(CRITICAL,"BsProcessResetAckReq(): SendInterfaceAddUpdateToPeer Failed \n");
   }
#endif
  return (SS7_SUCCESS);
}
/*
*
*
*      Fun: BsProcessUnequippedCktReq
*
*      Desc:  This function will process UnequippedCktReq
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessUnequippedCktReq
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUnequippedCktReq(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ielistData = SS7_NULL;
 U8bit range =0;
 U16bit flag;
 U16bit cic = 0;
 U8bit msgtype = 0;
 
  msgtype = BSSAP_MSG_UNEQUIPPED_CKT;
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq(): UNEQUIPPED CKT RECV from APP\n");
 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq():Interface pointer is NULL \n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
 }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 if(bsIntfCb->cicDataList != SS7_NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
   LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq():cic not configured");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq():crec pointer is NULL \n");
    return (SS7_FAILURE);
 }
 if(crec->cic==cicVal)
 {
    /*crec->remoteState = CIC_ST_BLOCK;*/
    BS_SET_REMOTESTATE_BLOCK(crec->flaglistSet);
    if(crec->timerId != BSSAP_INVALID_TMRID)
    {
       bsStopCirTmr(crec,crec->timerId);
    }
 }
 else
 {
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

    bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

    /*Send Error to App */
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_UNEQUIPPED_CKT,intfCb);
    return (SS7_FAILURE);
 }
  ielistData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
  if(ielistData == SS7_NULL)
  {
    LOG_PRINT(INFO,"BsProcessUnequippedCktReq():CIC is Not Present\n");
    return (SS7_SUCCESS);
  }
  range=CCL_GET_RANGE(ielistData->param_data.cic_list);
  range+=crec->cic;
  for(cic = (crec->cic +1) ; cic < range ;cic++)
  {
   flag=SS7_FALSE;
   flag= BsGetStatusBit(crec->cic,cic,ielistData);
   if(flag == SS7_TRUE)
    {
        crec = &bsIntfCb->cicDataList[cic];
        if(crec->cic==cic)
        {
           /*crec->remoteState = CIC_ST_BLOCK;*/
           BS_SET_REMOTESTATE_BLOCK(crec->flaglistSet);
           if(crec->timerId != BSSAP_INVALID_TMRID)
           {
             bsStopCirTmr(crec,crec->timerId);
           }
        }
       else
        {
           LOG_PRINT(CRITICAL,"BsProcessUnequippedCktReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
           /*Raise Alarm to Stack Manager */
           bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

           bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
            /*Send Error to App */
            BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_UNEQUIPPED_CKT,intfCb);
        }
    }
   }
    return (SS7_SUCCESS);
}
/*
*
*
*      Fun: BsProcessUnequippedCktInd
*
*      Desc:  This function will process UnequippedCktInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessUnequippedCktInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUnequippedCktInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ielistData = SS7_NULL;
 U8bit range =0;
 U16bit flag = SS7_FALSE;
 U16bit cic = 0;
 U8bit msgtype = 0;
  
 msgtype = BSSAP_MSG_UNEQUIPPED_CKT;
 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktInd():Interface pointer is NULL \n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessUnequippedCktInd():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
  }
 cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
 if(bsIntfCb->cicDataList != NULL)
 {
   crec=&bsIntfCb->cicDataList[cicVal];
 }
 else
 {
   LOG_PRINT(CRITICAL,"BsProcessUnequippedCktInd():cic not configured");
    return (SS7_FAILURE);
 }
 if(crec == SS7_NULL)
 {
   LOG_PRINT(INFO,"BsProcessUnequippedCktInd():crec pointer is NULL \n");
    return (SS7_FAILURE);
 }
 if(crec->cic==cicVal)
  {
    /*crec->remoteState = CIC_ST_BLOCK;*/
    BS_SET_REMOTESTATE_BLOCK(crec->flaglistSet);
    if(crec->timerId != BSSAP_INVALID_TMRID)
    {
       bsStopCirTmr(crec,crec->timerId);
    }
  }
 else
  {
    return (SS7_FAILURE);
  }
  ielistData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
  if(ielistData == SS7_NULL)
  {
    LOG_PRINT(INFO,"BsProcessUnequippedCktInd():CIC LIST  IE is Not Present in message\n");
    return (SS7_SUCCESS);
  }
  range=CCL_GET_RANGE(ielistData->param_data.cic_list);
  range+=crec->cic;
  for(cic = (crec->cic +1) ; cic < range ;cic++)
  {
   flag=SS7_FALSE;
   flag= BsGetStatusBit(crec->cic,cic,ielistData);
   if(flag == SS7_TRUE)
    {
        crec = &bsIntfCb->cicDataList[cic];
        if(crec->cic==cic)
        {
           /*crec->remoteState = CIC_ST_BLOCK;*/
           BS_SET_REMOTESTATE_BLOCK(crec->flaglistSet);
           if(crec->timerId != BSSAP_INVALID_TMRID)
           {
             bsStopCirTmr(crec,crec->timerId);
           }
        }
       else
        {
	  LOG_PRINT(CRITICAL,"BsProcessUnequippedCktInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
           /*Raise Alarm to Stack Manager */
           bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

           bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
            /*Send Error to App */
            BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_UNEQUIPPED_CKT,intfCb);
        }
    }
   }
    return (SS7_SUCCESS);
}


/*
*
*
*      Fun: BsProcessResetIPReq
*
*      Desc:  This function will process ResetIP
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessResetIPReq
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetIPReq(ie,iecount,Data *databuff,MsgLen dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{

  BsIntfCb *bsIntfCb = SS7_NULL;
  U8bit mType = 0; 

  mType = BSSAP_MSG_RESET_IP; 
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessResetIPReq(): Interface not found(Interface pointer NULL) \n");
    return (SS7_FAILURE);
  }

  if(bsIntfCb->rstSndtimerId != BSSAP_INVALID_TMRID)
  {
     /*drop the message and error reurned to App*/
    LOG_PRINT(CRITICAL,"BsProcessResetIPReq(): RESET already Send : rstSndtimerId > 0 \n");
    return (SS7_FAILURE);
  }
  bsStartIntfTmr(BSSAP_T_RBSC,bsIntfCb);
  bsIntfCb->TrbsctimerId = BSSAP_T_RBSC;

	bsIntfCb->databuf = (U8bit *)bssap_malloc(dataLen);
        if(bsIntfCb->databuf == SS7_NULL)
        return (SS7_FAILURE);

#if 0  
if (ROK != SGetSBuf(bsCb.init.region, bsCb.init.pool, (Data **) &bsIntfCb->databuf,
                         dataLen))
  {
       BSDBGP(BSDBGMASK_CERR, (bsCb.init.prntBuf,
                      "In BsProcessResetIPReq():SGetSBuf   failed   \n"));
#if (ERRCLASS & ERRCLS_INT_PAR)
       BSLOGERROR(ERRCLS_INT_PAR, EBS088, (ErrVal)0,
                 "In BsProcessResetIPReq,SGetSBuf   failed \n");
#endif
    BSCORE(CRITICAL,BSERR_CORE_NONE,DEFAULT,DEFAULT,DEFAULT,DEFAULT,"BsProcessResetIPReq():SGetSBuf:databuf",DEFAULT);
    return (SS7_FAILURE);
   }
#ifdef MEM_LEAK
    else
    {
     printf("MEM ALLOCATED:SGetSBuf BsProcessResetIPReq\n")
    }
#endif
#endif

   /*Storing Reset msg for timeout */
   bsIntfCb->datalen = dataLen;
   ss7_memcpy((U8bit*)bsIntfCb->databuf,(U8bit*)databuff,dataLen);
   return (SS7_SUCCESS);
}
/*
*
*
*      Fun: BsProcessResetIPAckInd
*
*      Desc:  This function will process ResetIPAck
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI
S16bit BsProcessResetIPAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessResetIPAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;

   LOG_PRINT(INFO,"BsProcessResetIPAckInd(): RESET IP ACK recv \n");
   bsIntfCb = intfCb;
  
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessResetIPAckInd(): No interface found(bsIntfCb is NULL) \n");
    return (SS7_FAILURE);
  }
  if(bsIntfCb->TrbsctimerId != BSSAP_INVALID_TMRID)
  {
    bsStopIntfTmr(bsIntfCb,BSSAP_T_RBSC);
    bsIntfCb->TrbsctimerId = BSSAP_INVALID_TMRID;
    bssap_free((Data *)bsIntfCb->databuf);
    bsIntfCb->databuf = SS7_NULL;
    bsIntfCb->datalen = 0;
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessResetIPAckInd(): TrbsctimerId  timer not running\n");
    return (SS7_FAILURE);
  }
    return (SS7_SUCCESS);
}

/*
*
*
*      Fun: BsProcessInternalHandoverRequired
*
*      Desc:  This function will process InternalHandoverRequired
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessInternalHandoverRequired
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessInternalHandoverRequired(call,ie,iecount,databuff,dataLen,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
  U32bit callrefId = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;

  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverRequired(): call pointer NULL \n");
    return (SS7_FAILURE);	
  }
  callrefId = call->suInstId;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverRequired(): Interface pointer NULL \n");
    return (SS7_FAILURE);	
  }
  LOG_PRINT(INFO,"BsProcessInternalHandoverRequired(): Internal handover Required recv from APP  for Callref[%ld]\n",callrefId);

  if(call->timerId == BSSAP_T_25)
  {
   /*Handover procedure is already running and error report to App*/
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverRequired(): Handover procedure is already running and error report to App \n");
    BsDispatchAOIPProtocolErrToApp(call,BSSAP_MD_PROTOCOL,BSSAP_EINVMESSAGE,&call->callId,4,BSSAP_MSG_INTERNAL_HANDOVER_COMMAND,bsIntfCb);
    return (SS7_FAILURE);	
  }
  LOG_PRINT(INFO,"BsProcessInternalHandoverRequired(): Going to Start T25 Timer \n");
  bsStartConTmr(BSSAP_T_25,call,intfCb);
  LOG_PRINT(INFO,"BsProcessInternalHandoverRequired(): call->timerId[%d] \n",call->timerId);
  return (SS7_SUCCESS);	
}
/*
*
*
*      Fun: BsProcessInternalHandoverRequiredReject
*
*      Desc:  This function will process InternalHandoverRequiredReject
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessInternalHandoverRequiredReject
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessInternalHandoverRequiredReject(call,ie,iecount,databuff,dataLen,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
  U32bit callrefId = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;

  callrefId = call->suInstId;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverRequiredReject(): Interface pointer NULL \n");
    return (SS7_FAILURE);
  }
  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverRequiredReject(): call pointer NULL \n");
    return (SS7_FAILURE);
  }
  if(call->timerId == BSSAP_T_25)
  {
     /*To be verify whether to stop T10 here or not*/
      /*bsStopConTmr(call,BSSAP_T_10);*/
      bsStopConTmr(call,BSSAP_T_25);
  }
  else
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverRequiredReject(): BSSAP_T_25 not running \n");
    return (SS7_FAILURE);
  }
    return (SS7_SUCCESS);
}
/*
*
*
*      Fun: BsProcessInternalHandoverCmd
*
*      Desc:  This function will process InternalHandoverCmd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessInternalHandoverCmd
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessInternalHandoverCmd(call,ie,iecount,databuff,dataLen,intfCb)
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsNSAPCb *sCb;
BsIntfCb *intfCb;
#endif
{
  U32bit callrefId = 0;
  BsIntfCb *bsIntfCb = SS7_NULL;
  BSSAP_IE *ieData = SS7_NULL;
  U16bit cicVal  = 0;
  U16bit oldcicVal  = 0;
  U8bit msgtype = 0;
#ifdef BSSAP_HA
  U8bit cause;
  HashEntry *callIdEntry = NULL;
  CallIdCb *callIdVal = NULL;
  int ret = RFAILED;
#endif

   msgtype = BSSAP_MSG_INTERNAL_HANDOVER_COMMAND;

  if(call == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd(): call pointer NULL \n");
    return (SS7_FAILURE);
  }
  callrefId = call->suInstId;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd():Interface pointer NULL \n");
    return (SS7_FAILURE);
  }

  LOG_PRINT(INFO,"BsProcessInternalHandoverCmd(): Internal Handover Cmd recv for Callref[%ld]\n",callrefId);
  
  ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
  if(ieData)
  {
     cicVal = (ieData->param_data.cic.cic[0]<<8)|(ieData->param_data.cic.cic[1]);  
     LOG_PRINT(INFO,"BsProcessInternalHandoverCmd(): CIC [%d] recv in Internal Handover Cmd \n",cicVal);
     if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cicVal].cic == cicVal))
     {
        LOG_PRINT(INFO,"BsProcessInternalHandoverCmd(): CIC [%d] in call pointer \n",call->cic);
        if(call->cic != cicVal)
          {
             if(call->cic > 0)
             {
              oldcicVal = call->cic;
              if(bsIntfCb->cicDataList[oldcicVal].cic == oldcicVal)
              {
                  BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[oldcicVal].flaglistSet);
                  call->cic = 0;
              }
              else
              {
                 LOG_PRINT(INFO,"BsProcessInternalHandoverCmd() :oldcicVal %d not found \n",oldcicVal);
              }
             }
             call->cic = cicVal;
          }
          if(call->timerId == BSSAP_T_25)
          {
             /*To be verify whether to stop T10 here or not*/
             /* bsStopConTmr(call,BSSAP_T_10);*/
             bsStopConTmr(call,BSSAP_T_25);
          }
          else
          {
             LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd() : BSSAP_T_25 is not running \n");
             return (SS7_FAILURE);
          }
     }
     else
     {
           LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
           /*Raise Alarm to Stack Manager */
           bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

           bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

       BsDispatchErrorToApp(call,BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,cicVal,BSSAP_MSG_INTERNAL_HANDOVER_COMMAND,bsIntfCb);
       LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd() :Sending UNEQUIPPED CKT Msg to PEER \n");
       BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
       return (SS7_FAILURE);
     }    
  }
  else
  {
      ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CALL_ID);
      if(ieData)
      {
         call->cic = 0;
#ifdef BSSAP_HA
      /* Search hashlist for callId to check if entry present*/
      LOG_PRINT(INFO,"BsProcessInternalHandoverCmd():CALLID value[%d] \n",ieData->param_data.call_id.callId);
      ret = HashListTbSearch(intfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId), sizeof(ieData->param_data.call_id.callId),&callIdEntry);
      if((ret == ROK) && (callIdEntry != NULL))
      {
	LOG_PRINT(INFO,"BsProcessInternalHandoverCmd() :CALLID[%ld] is already in Use \n",ieData->param_data.call_id.callId);
	cause = C_TERRESTRIAL_RES_UNAVAILABLE;
	BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
	return SS7_FAILURE;
      }
      callIdVal = (CallIdCb *)calloc(1,sizeof(CallIdCb));
      if(callIdVal == SS7_NULL)
      {
	LOG_PRINT(INFO,"BsProcessInternalHandoverCmd() :could not allocate memory to callIdVal ptr \n");
	return SS7_FAILURE;
      }
	      
      callIdVal->callId = ieData->param_data.call_id.callId;
      callIdVal->callRefId = call->suInstId;
      
      ret = HashListTbInsert(intfCb->callIdList,intfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(ieData->param_data.call_id.callId),sizeof(ieData->param_data.call_id.callId),callIdVal,sizeof(CallIdCb));
      if(ret != ROK)
      {
	LOG_PRINT(INFO,"BsProcessInternalHandoverCmd() :HashListTbInsert failed for CALLID[%d]\n",ieData->param_data.call_id.callId);
	cause = C_TERRESTRIAL_RES_UNAVAILABLE;
	BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,cause,SS7_NULL,0,intfCb);
	free(callIdVal);
	callIdVal = NULL;
	return SS7_FAILURE;
      }
#endif
         ss7_memcpy(&call->callId,&ieData->param_data.call_id.callId,sizeof(BSSAP_CallIdentifier));
         LOG_PRINT(INFO,"BsProcessInternalHandoverCmd() :AOIP callId %ld call->timerId[%d]\n",call->callId,call->timerId);
         if(call->timerId == BSSAP_T_25)
         {
             /*To be verify whether to stop T10 here or not*/
            /* bsStopConTmr(call,BSSAP_T_10);*/
             bsStopConTmr(call,BSSAP_T_25);
         }
         else
         {
             LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd() : BSSAP_T_25 is not running \n");
       		return (SS7_FAILURE);
         }
      }
      else
      {
             LOG_PRINT(CRITICAL,"BsProcessInternalHandoverCmd() : Neither CIC nor Call Id are present \n");
	     /*Note : CIC/CALL_ID is optional so pass data to APP */
       		return (SS7_SUCCESS);
      }
  }
       		return (SS7_SUCCESS);

}

/*
*
*      Fun: BsProcessCktGroupBlockReq
*
*      Desc:  This function will process Circuit Group BlockRequest
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCktGroupBlockReq
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCktGroupBlockReq(ie,iecount,databuff,dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BsCirCb *creclist = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ieCicList = SS7_NULL;
 U8bit localState = 0;
 U8bit msgtype = 0;
 U32bit range = 0;
 U16bit startCIC = 0,cic = 0;
 U8bit flag = SS7_FALSE; 

  msgtype = BSSAP_MSG_CKT_GROUP_BLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb ==  SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockReq():Interface pointer is SS7_NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockReq():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);

 }
 if(ieData)
 {
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    startCIC = cicVal ;
    if(cicVal ==0)
      {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);
       bsGenAlarmNew(&bsCb.init.lmPst,LCM_CATEGORY_PROTOCOL,LBS_EVENT_CIC_CONTEXT_NOT_FOUND,LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GROUP_BLOCK,intfCb);
       return (SS7_FAILURE);
      }
    LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():CKT GROUP BLOCK Received From APP for CIC value[%d]\n",cicVal);
    if(bsIntfCb->cicDataList != SS7_NULL)
    {
      crec = &bsIntfCb->cicDataList[cicVal];
    }
    else
    {
        LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():cic DB NULL");
        crec = SS7_NULL;
    }
    if((crec != SS7_NULL) && (crec->cic == cicVal))
    {
        BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,localState);
        if(localState == CIC_ST_LOCAL_BLOCK)
        {
           LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockReq():CIC[%d] localState is Already BLOCK \n",cicVal);
           /*Discarding msg if Start CIC is already blocked */
       	   return (SS7_FAILURE);
        }
        else
        {
           if(crec->timerId == BSSAP_T_1)
           {   
              bsStopCirTmr(crec,BSSAP_T_1);
           }
/*           bsStartCirTmr(BSSAP_T_20,crec,bsIntfCb);*/
        
           LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():Setting LOCAL STATE as BLOCKED for CIC value[%d]\n",cicVal);
           BS_SET_LOCALSTATE_BLOCK(crec->flaglistSet);
        }
    }
    else
    {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GROUP_BLOCK,intfCb);
       return (SS7_FAILURE);
    }
 }
 ieCicList = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
 if(ieCicList == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockReq():CIC List is Not Present\n");
    return (SS7_FAILURE);

 }
 if(ieCicList)
 {
    BS_GET_CICLIST_RANGE(ieCicList->param_data.cic_list,range);
    range += startCIC;
    for (cic = startCIC; cic < range; cic++)
    {
       flag = SS7_FALSE;
       flag = BsGetStatusBit(startCIC,cic,ieCicList);
       if (flag && (startCIC != cic))
       {
          if(bsIntfCb->cicDataList != SS7_NULL)
          {
            creclist = &bsIntfCb->cicDataList[cic];
          }
          else
          {
              LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():cic DB NULL");
             creclist = SS7_NULL;
          }
          if((creclist != SS7_NULL) && (creclist->cic == cic))
          {
              BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cic].flaglistSet,localState);
              if(localState == CIC_ST_LOCAL_BLOCK)
              {
                 LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():CIC[%d] localState is Already BLOCK \n",cic);
              }
              else
              {
                 LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():Setting LOCAL STATE as BLOCKED for CIC value[%d]\n",cic);
                 BS_SET_LOCALSTATE_BLOCK(creclist->flaglistSet);
              }
          }
          else
          {
            LOG_PRINT(INFO,"BsProcessCktGroupBlockReq: CIC[%d] not found CICDB,Hence not configured \n",cic);
#if 0
             /*Raise Alarm to Stack Manager */
             bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

             bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
             BsDispatchErrorToApp(SS7_NULL,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_CKT_GROUP_BLOCK,intfCb);
          } 
       }

    }
 }
    crec->databuf = (U8bit *)bssap_malloc(dataLen);
    if(crec->databuf == SS7_NULL)
    return (SS7_FAILURE);

   /*Storing Block msg for timeout */
   crec->msgtype = BSSAP_MSG_CKT_GROUP_BLOCK;
   crec->datalen = dataLen;
   ss7_memcpy((U8bit*)crec->databuf,(U8bit*)databuff,dataLen);
   bsStartCirTmr(BSSAP_T_20,crec,bsIntfCb);
   LOG_PRINT(INFO,"BsProcessCktGroupBlockReq():CKT GROUP BLOCK REQ for CIC[%d] process successfully \n",cicVal);
   return (SS7_SUCCESS);

}
/*
*
*      Fun: BsProcessCktGroupUnblockReq
*
*      Desc:  This function will process Circuit Group UnBlockRequest
*              coming from Application
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCktGroupUnblockReq
(
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCktGroupUnblockReq(ie,iecount,databuff,dataLen,intfCb)
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BsCirCb *creclist = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ieCicList = SS7_NULL;
 U8bit msgtype = 0;
 U32bit range = 0;
 U16bit startCIC = 0,cic = 0;
 U8bit flag = SS7_FALSE;

  msgtype = BSSAP_MSG_CKT_GRP_UNBLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq():Interface pointer is NULL\n");
    /*Discard the msg */
    return (SS7_FAILURE); 	
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq():CIC IE is Not Present in message\n");
    /*Discard the msg */
    return (SS7_FAILURE); 	

 }
 if(ieData)
 {
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    startCIC = cicVal ;
    LOG_PRINT(INFO,"BsProcessCktGroupUnblockReq():CKT GROUP UNBLOCK Received From APP for CIC value[%d]\n",cicVal);
    if(cicVal ==0)
     {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GRP_UNBLOCK,intfCb);
       /*Discard the msg */
    	return (SS7_FAILURE); 	
     }
    if(bsIntfCb->cicDataList != SS7_NULL)
    {
      crec = &bsIntfCb->cicDataList[cicVal];
    }
    else
    {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq():cic not configured");
      crec == SS7_NULL;
    }
    if((crec != SS7_NULL) && (crec->cic == cicVal))
    {
       if(crec->timerId == BSSAP_T_1)
       {
          bsStopCirTmr(crec,BSSAP_T_1);
       }
     /*  bsStartCirTmr(BSSAP_T_20,crec,bsIntfCb);*/
       BS_SET_LOCALSTATE_UNBLOCK(crec->flaglistSet);
    }
    else
    {
     LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GRP_UNBLOCK,intfCb);
       /*Discard the msg */
    	return (SS7_FAILURE); 	
    }
 }

 ieCicList = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
 if(ieCicList == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq():CIC List is Not Present\n");
    /*Discard the msg */
  return (SS7_FAILURE); 	

 }
 if(ieCicList)
 {
    BS_GET_CICLIST_RANGE(ieCicList->param_data.cic_list,range);
    range += startCIC;
    for (cic = startCIC; cic < range; cic++)
    {
       flag = SS7_FALSE;
       flag = BsGetStatusBit(startCIC,cic,ieCicList);
       if (flag && (startCIC != cic))
       {
          if(bsIntfCb->cicDataList != SS7_NULL)
          {
            creclist = &bsIntfCb->cicDataList[cic];
          }
          else
          {
            LOG_PRINT(INFO,"BsProcessCktGroupUnblockReq():cic DB NULL");
             creclist = SS7_NULL;
          }
          if((creclist != SS7_NULL) && (creclist->cic == cic))
          {
              LOG_PRINT(INFO,"BsProcessCktGroupUnblockReq():Setting LOCAL STATE as UNBLOCKED for CIC value[%d]\n",cicVal);
              BS_SET_LOCALSTATE_UNBLOCK(creclist->flaglistSet);
          }
          else
          {
            LOG_PRINT(CRITICAL,"BsProcessCktGroupUnblockReq(): CIC[%d] not found CICDB,Hence not configured \n",cic);
#if 0
             /*Raise Alarm to Stack Manager */
             bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

             bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
             BsDispatchErrorToApp(SS7_NULL,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_CKT_GRP_UNBLOCK,intfCb);
          }
       }

    }
 }
	crec->databuf = (U8bit *)bssap_malloc(dataLen);
  if(crec->databuf == SS7_NULL)
  return (SS7_FAILURE);
  /*Storing Circuit Group UnBlock msg for timeout */
  crec->msgtype = BSSAP_MSG_CKT_GRP_UNBLOCK;
  crec->datalen = dataLen;
  ss7_memcpy((U8bit*)crec->databuf,(U8bit*)databuff,dataLen);
	bsStartCirTmr(BSSAP_T_20,crec,bsIntfCb);
  LOG_PRINT(INFO,"BsProcessCktGroupUnblockReq():CKT GROUP UNBLOCK REQ for CIC[%d] process successfully \n",cicVal);

  return (SS7_SUCCESS); 	
}
/*
*
*      Fun: BsProcessCktGroupBlockInd
*
*      Desc:  This function will process Circuit Group BlockInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCktGroupBlockInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCktGroupBlockInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BsCirCb *creclist = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ieCicList = SS7_NULL;
 U8bit msgtype = 0;
 U32bit range = 0;
 U16bit startCIC = 0,cic = 0;
 U8bit flag = SS7_FALSE;
 U8bit remoteState = 0;
 U8bit sendCktGrpBlockAckFlag = 0;

  msgtype = BSSAP_MSG_CKT_GROUP_BLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd():Interface pointer is NULL\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
     LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd():CIC IE is Not Present in message\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 if(ieData)
 {
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    startCIC = cicVal ;
    LOG_PRINT(INFO,"BsProcessCktGroupBlockInd():CKT GROUP BLOCK Received From MSC for CIC value[%d]\n",cicVal);
    if(bsIntfCb->cicDataList != SS7_NULL)
    {
      crec = &bsIntfCb->cicDataList[cicVal];
    }
    else
    {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd():cic not configured");
       crec = SS7_NULL;
    }
    if((crec != SS7_NULL) && (crec->cic == cicVal))
    {
       BS_GET_REMOTESTATE(crec->flaglistSet,remoteState);
       if(remoteState != CIC_ST_REMOTE_BLOCK)
       {
         LOG_PRINT(INFO,"BsProcessCktGroupBlockInd(): Setting Remote State as BLOCKED for cicval[%d]\n",cicVal);
         BS_SET_REMOTESTATE_BLOCK(crec->flaglistSet);
       }
       else
       {
	LOG_PRINT(INFO,"BsProcessCktGroupBlockInd(): Recv CKT GROUP BLOCK for CIC[%d] Remote state in already BLOCKED state\n",cicVal);
        /*sendBlock Ack */
         sendCktGrpBlockAckFlag = SS7_TRUE;
       }
    }
    else
    {
      LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GROUP_BLOCK,intfCb);
/*       printf("BsProcessCktGroupBlockInd :Sending EUNEQUIP CKT Msg to PEER \n");*/
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
       BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
       /*Discard the msg */
       return (SS7_FAILURE);
    }
 }
 ieCicList = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
 if(ieCicList == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd():CIC List is Not Present\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 if(ieCicList)
 {
    BS_GET_CICLIST_RANGE(ieCicList->param_data.cic_list,range);
    range += startCIC;
    for (cic = startCIC; cic < range; cic++)
    {
       flag = SS7_FALSE;
       flag = BsGetStatusBit(startCIC,cic,ieCicList);
       if (flag && (startCIC != cic))
       {
          if(bsIntfCb->cicDataList != SS7_NULL)
          {
            creclist = &bsIntfCb->cicDataList[cic];
          }
          else
          {
            LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd():cic not configured");
            creclist = SS7_NULL;
          }
          if((creclist != SS7_NULL) && (creclist->cic == cic))
          {
             BS_GET_REMOTESTATE(creclist->flaglistSet,remoteState);
             if(remoteState != CIC_ST_REMOTE_BLOCK)
             {
                LOG_PRINT(INFO,"BsProcessCktGroupBlockInd(): Setting Remote State as BLOCKED for cicval[%d]\n",cic);
                BS_SET_REMOTESTATE_BLOCK(creclist->flaglistSet);
             }
             else
             {
               /*sendBlock Ack */
             LOG_PRINT(INFO,"BsProcessCktGroupBlockInd(): Recv CKT GROUP BLOCK for CIC[%d] Remote state in already BLOCKED state\n",cicVal);
                sendCktGrpBlockAckFlag = SS7_TRUE;
             }
          }
          else
          {
           LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd(): CIC[%d] not found CICDB,Hence not configured \n",cic);
#if 0
              /*Raise Alarm to Stack Manager */
             bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

             bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
             BsDispatchErrorToApp(SS7_NULL,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_CKT_GROUP_BLOCK,intfCb);
             LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
             BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cic,SS7_NULL,intfCb);
          }

       }
    }/*end of for loop */
#if 0
    /*Commented : As delivering  the msg to application in case if some of the cic are already blocked*/
    if(sendCktGrpBlockAckFlag == TRUE)
    {
       /*sendBlock Ack */
      printf("BsProcessCktGroupBlockInd:Remote state block sending CIRCUIT GROUP BLOCK ACK \n");
      BsSendCktMsg(BSSAP_MSG_CKT_GRP_BLK_ACK,startCIC,ieCicList,sCb,intfCb);
      /*Discard the msg */
      RETVALUE(RFAILED);
    }
#endif
 }
return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessCktGroupBlockAckInd
*
*      Desc:  This function will process Circuit Group BlockAckInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCktGroupBlockAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCktGroupBlockAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BsCirCb *creclist = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ieCicList = SS7_NULL;
 U8bit msgtype = 0;
 U32bit range = 0;
 U16bit startCIC = 0,cic = 0;
 U8bit flag = SS7_FALSE;
 U8bit sendCktGrpUnblockFlag = SS7_FALSE;
 U8bit localState = 0;
 BSSAP_IE ieUnblockCicList;
 U8bit bit_position = 0;


  msgtype = BSSAP_MSG_CKT_GRP_BLK_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd():Interface pointer is NULL\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd():CIC IE is Not Present in message\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 if(ieData)
 {
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    startCIC = cicVal ;
    LOG_PRINT(INFO,"BsProcessCktGroupBlockAckInd():CKT GROUP BLOCK ACK Received From MSC for CIC value[%d]\n",cicVal);
    if(bsIntfCb->cicDataList != SS7_NULL)
    {
      crec = &bsIntfCb->cicDataList[cicVal];
    }
    else
    {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd():cic not configured");
       crec = SS7_NULL;
    }
    if((crec != SS7_NULL) && (crec->cic == cicVal))
    {
        BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,localState);
        if(localState == CIC_ST_LOCAL_BLOCK)
        {
           LOG_PRINT(INFO,"BsProcessCktGroupBlockAckInd():CIC[%d] localState is BLOCK \n",cicVal);
           if(crec->timerId != BSSAP_INVALID_TMRID)
           {
              bsStopCirTmr(crec,crec->timerId);
           }
     
        }
        else
        {
           LOG_PRINT(INFO,"BsProcessCktGroupBlockAckInd(): Recv CKT GROUP BLOCK ACK for CIC[%d] localstate state in already UNBLOCKED state\n",cicVal);
           sendCktGrpUnblockFlag = SS7_TRUE; 
        }
    }
    else
    {
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GRP_BLK_ACK,intfCb);
       LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
       BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
       /*Discard the msg */
      return (SS7_FAILURE);
    }

 }
 ieCicList = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
 if(ieCicList == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockInd():CIC List is Not Present\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 memset((U8bit*)&ieUnblockCicList,'\0',sizeof(BSSAP_IE));
 ss7_memcpy((U8bit*)&ieUnblockCicList,(U8bit*)ieCicList,sizeof(BSSAP_IE));
 if(sendCktGrpUnblockFlag)
 {
   bit_position = 0;
   BsSetStatusBit(&ieUnblockCicList,SS7_TRUE,bit_position); 
 }
 if(ieCicList)
 {
    BS_GET_CICLIST_RANGE(ieCicList->param_data.cic_list,range);
    range += startCIC;
    for (cic = startCIC; cic < range; cic++)
    {
       flag = SS7_FALSE;
       flag = BsGetStatusBit(startCIC,cic,ieCicList);
       if (flag && (startCIC != cic))
       {
          if(bsIntfCb->cicDataList != SS7_NULL)
          {
            creclist = &bsIntfCb->cicDataList[cic];
          }
          else
          {
             LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd():cic not configured");
            creclist = SS7_NULL;
          }
          if((creclist != SS7_NULL) && (creclist->cic == cic))
          {
             BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cic].flaglistSet,localState);
             if(localState == CIC_ST_LOCAL_BLOCK)
             {
                LOG_PRINT(INFO,"BsProcessCktGroupBlockAckInd():CIC[%d] localState is BLOCK \n",cic);
                if(creclist->timerId != BSSAP_INVALID_TMRID)
                {
                   bsStopCirTmr(creclist,creclist->timerId);
                }
                bit_position = (cic - startCIC) % 8;
                BsSetStatusBit(&ieUnblockCicList,SS7_FALSE,bit_position); 
             }
             else
             {
                LOG_PRINT(INFO,"BsProcessCktGroupBlockAckInd(): Recv CKT GROUP BLOCK ACK for CIC[%d] localstate state in already UNBLOCKED state\n",cicVal);
                
                bit_position = (cic - startCIC) % 8;
                BsSetStatusBit(&ieUnblockCicList,SS7_TRUE,bit_position); 
               sendCktGrpUnblockFlag = SS7_TRUE;
             }
          }
          else
          {
             LOG_PRINT(CRITICAL,"BsProcessCktGroupBlockAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cic);
#if 0
              /*Raise Alarm to Stack Manager */
             bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

             bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
             BsDispatchErrorToApp(SS7_NULL,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_CKT_GRP_BLK_ACK,intfCb);
             LOG_PRINT(INFO,"BsProcessCktGroupBlockAckInd :Sending UNEQUIPPED CKT Msg to PEER \n");
             BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cic,SS7_NULL,intfCb);
          }

       }
   }/*end of for loop*/
#if 0
/*Commented : As delivering  the msg to application in case if some of the cic are already unblocked*/
   if(sendCktGrpUnblockFlag == TRUE)
   {
       /*send UnBlock */
      printf("BsProcessCktGroupBlockAckInd:Local state is unblock sending CIRCUIT GROUP UNBLOCK to PEER \n");
      BsSendCktMsg(BSSAP_MSG_CKT_GRP_UNBLOCK,startCIC,&ieUnblockCicList,sCb,intfCb);
   }
#endif
 }
    return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessCktGroupUnBlockInd
*
*      Desc:  This function will process Circuit Group UnBlockInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCktGroupUnBlockInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCktGroupUnBlockInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BsCirCb *creclist = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ieCicList = SS7_NULL;
 U8bit msgtype = 0;
 U32bit range = 0;
 U16bit startCIC = 0,cic = 0;
 U8bit flag = SS7_FALSE;
 U8bit remoteState = 0;
 U8bit sendCktGrpUnBlockAckFlag = 0;

  msgtype = BSSAP_MSG_CKT_GRP_UNBLOCK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd():Interface pointer is NULL\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd():CIC IE is Not Present in message\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 if(ieData)
 {
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    startCIC = cicVal ;
    LOG_PRINT(INFO,"BsProcessCktGroupUnBlockInd():CKT GROUP UNBLOCK Received From MSC for CIC value[%d]\n",cicVal);
    if(bsIntfCb->cicDataList != SS7_NULL)
    {
      crec = &bsIntfCb->cicDataList[cicVal];
    }
    else
    {
      LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd():cic not configured \n");
      crec = SS7_NULL;
    }
    if((crec != SS7_NULL) && (crec->cic == cicVal))
    {
       BS_GET_REMOTESTATE(crec->flaglistSet,remoteState);
       if(remoteState != CIC_ST_REMOTE_UNBLK)
       {
         LOG_PRINT(INFO,"BsProcessCktGroupUnBlockInd(): Setting Remote State as UNBLOCKED for cicval[%d]\n",cicVal);
         BS_SET_REMOTESTATE_UNBLOCK(crec->flaglistSet);
       }
       else
       {
          LOG_PRINT(INFO,"BsProcessCktGroupUnBlockInd(): Recv CKT GROUP UNBLOCK for CIC[%d] Remote state in already UNBLOCKED state\n",cicVal);
          sendCktGrpUnBlockAckFlag = SS7_TRUE;
       }
    }
    else
    {
      LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif 

      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GRP_UNBLOCK,intfCb);
      LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
       BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
       /*Discard the msg */
       return (SS7_FAILURE);
    }

 }
 ieCicList = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
 if(ieCicList == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd():CIC List is Not Present\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 if(ieCicList)
 {
    BS_GET_CICLIST_RANGE(ieCicList->param_data.cic_list,range);
    range += startCIC;
    for (cic = startCIC; cic < range; cic++)
    {
       flag = SS7_FALSE;
       flag = BsGetStatusBit(startCIC,cic,ieCicList);
       if (flag && (startCIC != cic))
       {
          if(bsIntfCb->cicDataList != SS7_NULL)
          {
            creclist = &bsIntfCb->cicDataList[cic];
          }
          else
          {
             LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd():cic not configured \n");
            creclist = SS7_NULL;
          }
          if((creclist != SS7_NULL) && (creclist->cic == cic))
          {
             BS_GET_REMOTESTATE(creclist->flaglistSet,remoteState);
             if(remoteState != CIC_ST_REMOTE_UNBLK)
             {
                LOG_PRINT(INFO,"BsProcessCktGroupUnBlockInd(): Setting Remote State as UNBLOCKED for cicval[%d]\n",cic);
                BS_SET_REMOTESTATE_UNBLOCK(creclist->flaglistSet);
             }
             else
             {
               /*send UnBlock Ack */
                LOG_PRINT(INFO,"BsProcessCktGroupUnBlockInd(): Recv CKT GROUP UNBLOCK for CIC[%d] Remote state in already UNBLOCKED state\n",cicVal);
                sendCktGrpUnBlockAckFlag = SS7_TRUE;
             }
          }
          else
          {
             LOG_PRINT(INFO,"BsProcessCktGroupUnBlockInd(): CIC[%d] not found CICDB,Hence not configured \n",cic);
#if 0
              /*Raise Alarm to Stack Manager */
             bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

             bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);

#endif
             BsDispatchErrorToApp(SS7_NULL,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_CKT_GRP_UNBLOCK,intfCb);
             LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
             BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cic,SS7_NULL,intfCb);
          }

       }
    }/*end of for loop */
#if 0
   /*Commented : As delivering  the msg to application in case if some of the cic are already unblocked*/
    if(sendCktGrpUnBlockAckFlag == TRUE)
    {
       /*send UnBlock Ack */
      printf("BsProcessCktGroupUnBlockInd:Remote state Unblock sending CIRCUIT GROUP UNBLOCK ACK \n");
      BsSendCktMsg(BSSAP_MSG_CKT_GRP_UNBLKING_ACK,startCIC,ieCicList,sCb,intfCb);
      /*Discard the msg */
      RETVALUE(RFAILED);
    }
#endif
 }          
 return (SS7_SUCCESS);
}
/*
*
*      Fun: BsProcessCktGroupUnBlockAckInd
*
*      Desc:  This function will process Circuit Group UnBlockAckInd
*              coming from MSC
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI
S16bit BsProcessCktGroupUnBlockAckInd
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCktGroupUnBlockAckInd(ie,iecount,intfCb)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
#endif
{
 U16bit cicVal =0;
 BsIntfCb *bsIntfCb = SS7_NULL;
 BsCirCb *crec = SS7_NULL;
 BsCirCb *creclist = SS7_NULL;
 BSSAP_IE *ieData = SS7_NULL;
 BSSAP_IE *ieCicList = SS7_NULL;
 U8bit msgtype = 0;
 U32bit range = 0;
 U16bit startCIC = 0,cic = 0;
 U8bit flag = SS7_FALSE;
 U8bit sendCktGrpblockFlag = SS7_FALSE;
 U8bit localState = 0;
 BSSAP_IE ieblockCicList;
 U8bit bit_position = 0;


  msgtype = BSSAP_MSG_CKT_GRP_UNBLKING_ACK;

 bsIntfCb = intfCb;
 if(bsIntfCb == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd():Interface pointer is NULL\n");
    return (SS7_FAILURE);
 }
 ieData = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
 if(ieData == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd():CIC IE is Not Present in message\n");
    return (SS7_FAILURE);
 }
 if(ieData)
 {
    cicVal = (ieData->param_data.cic.cic[0] << 8)|(ieData->param_data.cic.cic[1]);
    startCIC = cicVal ;
    LOG_PRINT(INFO,"BsProcessCktGroupUnBlockAckInd():CKT GROUP BLOCK ACK Received From MSC for CIC value[%d]\n",cicVal);
    if(bsIntfCb->cicDataList != SS7_NULL)
    {
      crec = &bsIntfCb->cicDataList[cicVal];
    }
    else
    {
      LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd():cic not configured \n");
      crec = SS7_NULL;
    }
    if((crec != SS7_NULL) && (crec == SS7_NULL))
    {
    LOG_PRINT(INFO,"BsProcessCktGroupUnBlockAckInd():crec pointer is NULL\n");
    return (SS7_FAILURE);
    }
    if(crec->cic == cicVal)
    {
        BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cicVal].flaglistSet,localState);
        if(localState != CIC_ST_LOCAL_BLOCK)
        {
           LOG_PRINT(INFO,"BsProcessCktGroupUnBlockAckInd():CIC[%d] localState is UNBLOCK \n",cicVal);
           if(crec->timerId != BSSAP_INVALID_TMRID)
           {
              bsStopCirTmr(crec,crec->timerId);
           }
        }
        else
        {
           LOG_PRINT(INFO,"BsProcessCktGroupUnBlockAckInd(): Recv CKT GROUP UNBLOCK ACK for CIC[%d] localstate state in already BLOCKED state\n",cicVal);
           sendCktGrpblockFlag = SS7_TRUE;
        }

    }
    else
    {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cicVal);
#if 0
       /*Raise Alarm to Stack Manager */
       bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cicVal,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

       bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

      /*Report Error to App */
       BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cicVal,BSSAP_MSG_CKT_GRP_UNBLKING_ACK,intfCb);
       LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
       BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cicVal,SS7_NULL,intfCb);
       /*Discard the msg */
    	return (SS7_FAILURE);
    }

  }

 ieCicList = (BSSAP_IE*)BsFindIE(ie,iecount,BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
 if(ieCicList == SS7_NULL)
 {
    LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd():CIC List is Not Present\n");
    /*Discard the msg */
    return (SS7_FAILURE);
 }
 memset((U8bit*)&ieblockCicList,'\0',sizeof(BSSAP_IE));
 ss7_memcpy((U8bit*)&ieblockCicList,(U8bit*)ieCicList,sizeof(BSSAP_IE));
 if(sendCktGrpblockFlag)
 {
   bit_position = 0;
   BsSetStatusBit(&ieblockCicList,SS7_TRUE,bit_position);
 }
 if(ieCicList)
 {
    BS_GET_CICLIST_RANGE(ieCicList->param_data.cic_list,range);
    range += startCIC;
    for (cic = startCIC; cic < range; cic++)
    {
       flag = SS7_FALSE;
       flag = BsGetStatusBit(startCIC,cic,ieCicList);
       if (flag && (startCIC != cic))
       {
          if(bsIntfCb->cicDataList != SS7_NULL)
          {
            creclist = &bsIntfCb->cicDataList[cic];
          }
          else
          {
             LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd():cic not configured");
            creclist = SS7_NULL;
          }
          if((creclist != SS7_NULL) && (creclist->cic == cic))
          {
             BS_GET_LOCALSTATE(bsIntfCb->cicDataList[cic].flaglistSet,localState);
             if(localState != CIC_ST_LOCAL_BLOCK)
             {
                LOG_PRINT(INFO,"BsProcessCktGroupUnBlockAckInd():CIC[%d] localState is UNBLOCK \n",cic);
                if(creclist->timerId != BSSAP_INVALID_TMRID)
                {
                   bsStopCirTmr(creclist,creclist->timerId);
                }
                bit_position = (cic - startCIC) % 8;
                BsSetStatusBit(&ieblockCicList,SS7_FALSE,bit_position);
             }
             else
             {
                LOG_PRINT(INFO,"BsProcessCktGroupUnBlockAckInd(): Recv CKT GROUP UNBLOCK ACK for CIC[%d] localstate state in already BLOCKED state\n",cicVal);

                bit_position = (cic - startCIC) % 8;
                BsSetStatusBit(&ieblockCicList,SS7_TRUE,bit_position);
               sendCktGrpblockFlag = SS7_TRUE;
             }
          }
          else
          {
             LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd(): CIC[%d] not found CICDB,Hence not configured \n",cic);
#if 0
              /*Raise Alarm to Stack Manager */
             bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &intfCb->phyDpc);

             bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

             BsDispatchErrorToApp(SS7_NULL,BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,cic,BSSAP_MSG_CKT_GRP_UNBLKING_ACK,intfCb);
             LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd() :Sending UNEQUIPPED CKT Msg to PEER \n");
	     BsSendCktMsg(BSSAP_MSG_UNEQUIPPED_CKT,cic,SS7_NULL,intfCb);
		  }

	       }
	   }/*end of for loop*/
	#if 0
	/*Commented : As delivering  the msg to application in case if some of the cic are already blocked*/
	   if(sendCktGrpblockFlag == TRUE)
	   {
	       /*send Block */
	       LOG_PRINT(CRITICAL,"BsProcessCktGroupUnBlockAckInd():Local state is block sending CIRCUIT GROUP BLOCK to PEER \n");
	      BsSendCktMsg(BSSAP_MSG_CKT_GROUP_BLOCK,startCIC,&ieblockCicList,sCb,intfCb);
	   }
	#endif
	 }
	  return (SS7_SUCCESS);
}

