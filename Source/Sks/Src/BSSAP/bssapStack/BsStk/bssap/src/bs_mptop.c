/*****************************************************************************
**  FILE NAME:
**      bs_mptop.c
**
******************************************************************************
**
**  DESCRIPTION: This files contains the source code of main entry point of BSSAP stack for handelling** 							 all upper Layer,lower layer,Timeout API's.
**
**
**  DATE     NAME             REF#           REASON
**  --------------------------------------------------------------
**  1Dec2013  Amaresh Grahacharya    Original
**
**  Copyright 2013, VNL Software Systems
**
*****************************************************************************/


#include "lbs.h"           /* layer management */
#include "bs.h"
#include "bs_err.h"
#include "bsapp.h"
#include "bssapcom.h"
#include "bs_trace.h"
#include "sysxxx_msgopcode.h"

/* header/extern include files (.x) */

#include "lbs.x"           /* layer management */
#include "bs.x"
#include "bsapp.x"
#include "bssapcom.x"
#include "bs_trace.x"
#include "nw_util.h"
#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <bs_stgl.h>
#include <bs_debug.h>
#include <bssap_port.h>

#define LOGGER_IMR

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


return_t bssap_ret_val;
U8bit bssap_state = UNINITIALIZED;
U8bit bssap_data_state = UNINITIALIZED;

extern BsIntfCb *bsGetIntfPtr(U8bit bscId,S16bit swtch);
S16bit  BsAppProcessSCCPMessage(Data *databuff,U8bit datalen,BsIntfCb *intfCb);
S16bit BsAppProcessBSSAPMessage(Data *databuff,U8bit datalen,BsIntfCb *intfCb);
void bssap_handle_timeout(U8bit * p_api);
void bssap_handle_ll_api(U8bit * p_api);

static return_t sccp_chk_api_id(U8bit api_id);
static return_t sccp_chk_vers_id(U8bit vers_id);

extern unsigned char  bpmCardState;

/*****************************************************************************
**
**  FUNCTION :
**    Entry point to BSSAP stack
**
******************************************************************************
**
**  DESCRIPTION :
**    Handles all messages which come into the stack. This is the main 
**    function for the entry into the stack. This function basically checks
**    the API header to decide whether its an API from the Upper entity or
**    the Lower entity or from the System Management or the Timer Management.
**                    
*****************************************************************************/

return_t bssap_process_mesg
#ifdef ANSI_PROTO
  (pvoid p_msg)
#else
  (p_msg)
  pvoid p_msg;
#endif
{
	U8bit 	api_id,  *p_api ;
	error_t ecode;
	U8bit 	src_entity,dst_entity;
	U16bit 	msgType;
	unsigned short int  	msgLen=0;
	unsigned short int  	sccp_data_len=0;
	unsigned short int  	timeout_data_len=0;

	U8bit index=9;
  	Data *databuff = SS7_NULL;
  	U8bit datalen;
  	S16bit ret = SS7_FAILURE;
  	U8bit  appVerNo;
  	BsIntfCb *bsIntfCb = SS7_NULL;
  	static U32bit counter = 0;
  	U8bit bscId;


  p_api = (U8bit *)p_msg;


  if (bssap_state == UNINITIALIZED || bssap_state==BLOCKED)
  {
  	LOG_PRINT(INFO,"bssap_process_mesg():INIT:message in UNINTITALIZED state.");
      	bssap_free(p_api);
	return SS7_FAILURE;
  }
#ifdef PLATFORM_IMR
  if (bpmCardState == BSSAP_CARD_STATE_STANDBY)
  {
  			LOG_PRINT(INFO,"bssap_process_mesg():INIT: Process message in BSSAP_CARD_STATE_STANDBY state.");
      	bssap_free(p_api);
				return SS7_FAILURE;
  }
#endif

/* Start  of Handelling BSSAP-User Data i.e BSC-APP Received */
  if (p_api[1] == ENT_CSAPP_AIFDHM) /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  {
  	/* Check the API header start*/

   	src_entity  = ((SysHdr *)p_api)->src.entity;
   	dst_entity  = ((SysHdr *)p_api)->dest.entity;
   	

/*		src_entity  = ((BsIfHdr *)p_api)->src.entity;
   	dst_entity  = ((BsIfHdr *)p_api)->dest.entity;  */

         /* Check the API header start*/
       msgLen  |= p_api[23];
       msgLen  |= p_api[22] << 8;
       msgLen  |= p_api[21] << 16;
       msgLen  |= p_api[20] << 24;

      printf("bssap_process_mesg():api_len extract from SysHdr is %d",msgLen);       
      msgLen = msgLen + SS7_BSSAP_APP_API_HEADER_LEN; 
	//LOG_PRINT(INFO,"[BSSAP] SysHdr details src_entity  %d,dst_entity %d,msgLen %d \n",src_entity,dst_entity,msgLen);
  if (dst_entity == APP_BSSAP_ENTID)
  {
	LOG_PRINT(INFO,"bssap_process_mesg(): RECEIVED DATA FROM CP(BSC->APP)>>>>>>\n");
	LOG_PRINT(INFO,"bssap_process_mesg(): HEX_DUMP RECEIVED DATA FROM CP(BSC->APP)>>>>>>\n");
	BS_Dump(p_api,msgLen);	
  	
  /* Check the API header stop*/
    bscId = p_api[29];
    LOG_PRINT(INFO,"bssap_process_mesg():Received Message from BSC-APP having bscId[%d]",bscId);
    bsIntfCb = bsGetIntfPtr(bscId,STACK_ITU);
   if(bsIntfCb == SS7_NULL)
    {
      LOG_PRINT(CRITICAL,"bssap_process_mesg():No Interface configured \n");
      return SS7_FAILURE;
    }

    datalen = msgLen - SS7_BSSAP_APP_API_HEADER_LEN;
    databuff = (U8bit *) bssap_malloc(datalen * sizeof(U8bit));
    if(databuff == SS7_NULL)
    {
   	LOG_PRINT(CRITICAL,"bssap_process_mesg():malloc failure for databuff\n");
    	return SS7_FAILURE;
    }
    ss7_memcpy((U8bit *)databuff,(U8bit *)&p_api[SS7_BSSAP_APP_API_HEADER_LEN],datalen);
    
    if (databuff[0] == CP_BSSAP_SCCP_TAG)
    {
      ret = BsAppProcessSCCPMessage(databuff,datalen,bsIntfCb);
      if(ret != SS7_SUCCESS)
      {
        LOG_PRINT(CRITICAL,"bssap_process_mesg():BsAppProcessSCCPMessage failed \n");
      }
    }
    else if (databuff[0] == CP_BSSAP_MSG_TAG)
    {
      ret = BsAppProcessBSSAPMessage(databuff,datalen,bsIntfCb);
      if(ret != SS7_SUCCESS)
      {
        LOG_PRINT(CRITICAL,"bssap_process_mesg():BsAppProcessBSSAPMessage failed \n");
      }
    }
    else
    	{
      		LOG_PRINT(CRITICAL,"bssap_process_mesg():Invaild MSG_TAG:Type[%x]\n",databuff[0]);
    	}
     }
  } /* End of Handelling BSSAP-User Data i.e BSC-APP Received */

  else if (((*p_api >= SCCP_MIN_API_TO_TC) && (*p_api <= SCCP_MAX_API_TO_TC)))
  {
	/* API from the Lower Layer  i.e. SCCP */
	 LOG_PRINT(INFO,"bssap_process_mesg():RECV MSG from SCCP:");
	 sccp_data_len  = GET_API_LEN(p_api);
	 LOG_PRINT(INFO,"bssap_process_mesg():Message HEX_DUMP Received from SCCP");
	 BS_Dump(p_api,sccp_data_len);
	bssap_handle_ll_api (p_api);
  } /* End of Handle SCCP Data Received */
  else if (SS7_TIMER_API_ID == *p_api)
  {
    /* API from the Timer Management */
 	   LOG_PRINT(INFO,"bssap_process_mesg():INIT:timeout message\n");
  	if (bssap_state == UNINITIALIZED)
  	{
      		LOG_PRINT(INFO,"bssap_process_mesg():INIT:Timer message in UNINTITALIZED state.\n");
      		bssap_free(p_api);
  		return SS7_FAILURE;
  	}
	 timeout_data_len  = GET_API_LEN(p_api);
	 LOG_PRINT(INFO,"bssap_process_mesg():TIMEOUT Message HEX_DUMP Received");
	 BS_Dump(p_api,timeout_data_len);
    	bssap_handle_timeout (p_api);
  }	/* End of Handle TIMEOUT of TIMER Data */
 else
  {
    LOG_PRINT(CRITICAL,"bssap_process_mesg():Incorrect ENTITY ID VALUE(not equal to BSSAP_TAGID)\n");
  }
  if(p_api)
  {
  	bssap_free ((U8bit*)p_api);
		p_api = SS7_NULL;
	}
	if(databuff)
  { 
  	bssap_free ((U8bit*)databuff);
		databuff = SS7_NULL;
	}
  if (ret == SS7_SUCCESS)
   return SS7_SUCCESS;
  else
  return SS7_FAILURE; 	
 }/* end of bssap_process_mesg */

/*
*
*      Fun:  BsAppProcessSCCPMessage
*
*      Desc:  This function will process SCCP REQUEST Msgs buffer from APP
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsAppProcessSCCPMessage
(
Data *databuff,
U8bit datalen,
BsIntfCb *intfCb
)
#else
S16bit  BsAppProcessSCCPMessage(databuff,datalen,intfCb)
Data *databuff;
U8bit datalen;
BsIntfCb *intfCb;
#endif
{
  U8bit index = 3;
  S16bit ret = SS7_TRUE;
  U32bit callrefId = 0,nb_callrefId=0,nb_appId=0;
  U32bit appId = 0;
  SpConId ConId;
  BsCallCb *call = SS7_NULL;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U32bit ConnId = 0;
  bsIntfCb = intfCb;
  if(bsIntfCb == SS7_NULL)
  {
       LOG_PRINT(CRITICAL,"BsAppProcessSCCPMessage():No Interface found(Interface pointer NULL)\n"); 
     return (SS7_FAILURE);
  }
 /* Call ref id */
  nb_callrefId  |= databuff[index++];
  nb_callrefId  |= databuff[index++] << 8;
  nb_callrefId  |= databuff[index++] << 16;
  nb_callrefId  |= databuff[index++] << 24;
  callrefId = ntohl(nb_callrefId);
  LOG_PRINT(INFO,"BsAppProcessSCCPMessage() : Call Reference id = %ld\n",callrefId);

 /* App Id*/
  nb_appId  |= databuff[index++];
  nb_appId  |= databuff[index++] << 8;
  nb_appId  |= databuff[index++] << 16;
  nb_appId  |= databuff[index++] << 24;
  appId = ntohl(nb_appId); 
  if(callrefId > 0)
  {
   LOG_PRINT(INFO,"BsAppProcessSCCPMessage() : calling bsFindCall for Callref Value[%ld] \n",callrefId);
   call = bsFindCall(bsIntfCb,callrefId);
  }
  else
  {
     LOG_PRINT(INFO,"BsAppProcessSCCPMessage() : Callref Value zero recv from App \n");
     LOG_PRINT(INFO,"BsAppProcessSCCPMessage() : calling bsFindCallForAbnormalRLSD for appId Value[%ld] \n",appId);
     call = bsFindCallForAbnormalRLSD(bsIntfCb,appId);
  }
     if (call == SS7_NULL)
     {
       LOG_PRINT(INFO,"BsAppProcessSCCPMessage():Cannot find the Call pointer in Call list\n"); 
         return (SS7_FAILURE);
     }
     memset((U8bit*)&ConId,'\0',sizeof(SpConId));
     ConId.suId = 0; /*sCb->suId;commented by Amaresh default value 0 */
     ConId.spId = 0; /*sCb->spId; commented by Amaresh default value 0 */
     ConId.suInstId = call->suInstId;
     ConId.spInstId = call->spInstId;
      
     /*Send Disconnect Request to SCCP */
     LOG_PRINT(INFO,"BsAppProcessSCCPMessage():Sending DISCONNECT REQ primitive to SCCP \n");
     ret = BsSendDisReq(&ConId,SCCP_MSG_RLSD,bsIntfCb);
     if(ret != SS7_SUCCESS)
     {
       LOG_PRINT(INFO,"BsAppProcessSCCPMessage():Unable to send Disconnect Request to SCCP\n");
       return (SS7_FAILURE);
     }
     /*Free CIC for this call */
    if(call->cic > 0)
    {
      if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[call->cic].cic == call->cic))
      {
         BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[call->cic].flaglistSet);
      }
      call->cic = 0;
    }
     /*Deallocate call reference */
      ret = bsDeallocateConRef(call);
      if(ret == SS7_SUCCESS)
      {
         call = SS7_NULL;
         LOG_PRINT(INFO,"BsAppProcessSCCPMessage():Call deallocated successfully on RLSD \n");
      }
      else
      {
         /*printf("BsAppProcessSCCPMessage:Unable to deallocated Call from call DB  on RLSD  from APP\n");*/
         LOG_PRINT(INFO,"BsAppProcessSCCPMessage():fail to DeallocateConRef on RLSD From App"); 
      }
  return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsAppProcessBSSAPMessage
*
*      Desc:  This function will process BSSAP REQUEST Msgs buffer from APP
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsAppProcessBSSAPMessage
(
Data *databuff,
U8bit datalen,
BsIntfCb *intfCb
)
#else
 S16bit BsAppProcessBSSAPMessage(databuff,datalen,intfCb)
Data *databuff;
U8bit datalen;
BsIntfCb *intfCb;
#endif
{
  BSSAPData bd;
  U8bit index = 1;
  U8bit len = 0;
  S16bit ret = SS7_TRUE;
  U32bit nb_callrefId=0,nb_appId=0;

  memset((U8bit *)&bd, '\0',sizeof(BSSAPData));

  
  /* BSC Id */
  bd.bssId = databuff[index++];

 /* Call ref id */
  nb_callrefId  |= databuff[index++];
  nb_callrefId  |= databuff[index++] << 8;
  nb_callrefId  |= databuff[index++] << 16;
  nb_callrefId  |= databuff[index++] << 24;
  bd.callrefId = ntohl(nb_callrefId);
  LOG_PRINT(INFO,"BsAppProcessBSSAPMessage() : Call Reference id = %ld\n", bd.callrefId);

 /* App Id*/
  nb_appId  |= databuff[index++];
  nb_appId  |= databuff[index++] << 8;
  nb_appId  |= databuff[index++] << 16;
  nb_appId  |= databuff[index++] << 24;

  bd.appId = ntohl(nb_appId);
  LOG_PRINT(INFO,"BsAppProcessBSSAPMessage() : APP Id = %ld\n", bd.appId);
  /* Message Discriminator */
  bd.mssgDisc = databuff[index++];

  /* BSSAP Message name */
  bd.mssgType = databuff[index++];

  /* BSSAP Message length */
  len = databuff[index++];

  if (bd.mssgDisc == BSSAP_MD_BSSMAP)/*to check if it is a BSSMAP or DTAP Msg*/
  {
    ss7_memcpy((U8bit *)bd.u.MAPdata.mapMsg,(U8bit *)&databuff[index],len);    
    bd.u.MAPdata.len = len;
  }
  else
  {
    ss7_memcpy((U8bit *)bd.u.DTAPdata.dtapMsg,(U8bit *)&databuff[index],len);    
    bd.u.DTAPdata.len = len;
  }
  LOG_PRINT(INFO,"BsAppProcessBSSAPMessage() : MSG RECV from APP for AppId[%lu] \n",bd.appId); 
  ret = BsProcessOutBSSAPMessage(&bd,intfCb);
  if(ret != SS7_SUCCESS)
  {
    LOG_PRINT(INFO,"BsAppProcessBSSAPMessage():BsProcessOutBSSAPMessage failed \n");
    return SS7_FAILURE;   
  }
    return SS7_SUCCESS;   
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles a timeout message
**
******************************************************************************
**
**  DESCRIPTION :
**    Calls appropriate function depending on which timer has expired. This
**    function checks the timer id to decide which entity should be called up
**    to handle time out message. For connectionless timers it directly calls
**    the appropriate function. And for Connection oriented timers it sets the
**    event and then calls the main entry point for the connection oriented 
**    stack "sccp_handle_co_mesg".
**
*****************************************************************************/
void bssap_handle_timeout
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
  U8bit timer_id;
  error_t     ecode ;
  return_t    result = SS7_SUCCESS;
  U8bit * p_tmr_buf;
  S16bit  event;

  /* Get the timer id of the timer that has expired */
  timer_id = GET_TIMER_ID(p_api);
  event = timer_id;
  p_tmr_buf = p_api + API_HEADER_LEN;
  p_tmr_buf += SCCP_TIMER_ID_LEN;
 
  switch (timer_id)
  {
   case BSSAP_T_1:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_1  EXPIRES \n");
          bsHandleBlkUnBlkTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_4:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_4  EXPIRES \n");
          bsHandleResetTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_7:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_7  EXPIRES \n");
      break;
     case BSSAP_T_8:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_8  EXPIRES \n");
      break;
     case BSSAP_T_10:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_10  EXPIRES \n");
          bsHandleAssignReqTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_11:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_11  EXPIRES \n");
      break;
     case BSSAP_T_13:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_13  EXPIRES \n");
          bsHandleResetGuardTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_17:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_17  EXPIRES \n");
      break;
     case BSSAP_T_18:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_18  EXPIRES \n");
      break;
     case BSSAP_T_19:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_19  EXPIRES \n");
          bsHandleResetCktTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_20:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_20  EXPIRES \n");
          bsHandleCktGrpBlkUnBlkTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_RBSC:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_RBSC  EXPIRES \n");
          bsHandleResetIPTimeout(p_tmr_buf, event);
      break;
     case BSSAP_T_25:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): BSSAP_T_25  EXPIRES \n");
      break;
    default:
          LOG_PRINT(CRITICAL,"bssap_handle_timeout(): invalid timer id %d EXPIRES\n",timer_id);
      return ;	
     }
      return ;	
}

#if 0
/*****************************************************************************
**
**  FUNCTION :
**    Handles a api from SM
**
******************************************************************************
**
**  DESCRIPTION :
**    Calls appropriate function depending on SM category. The called function
**    then call the appropriate command handling functions based on the
**    SM command.
**
*****************************************************************************/

void
sccp_handle_sm_api
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
  U8bit category;
  U8bit param = 0;
  extern U8bit sccp_state;
  Boolean put_param = SS7_FALSE;

  /* Get the category */
  category = GET_SM_CAT(p_api);

#ifdef SCCP_REDN_ENABLED
	if (sccp_state!=STACK_INITIALIZED && category != SS7_SM_CTRL && category!=SS7_SM_REDN)
#else
	if (sccp_state!=STACK_INITIALIZED && category != SS7_SM_CTRL )
#endif
	{
		SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));
		sccp_sm_cmd_std_resp (p_api, SS7_FAILURE, param, put_param,
                            ESS7_INVALID_STATE);
		return ;	
	}

  switch (category)
  {
    case SS7_SM_PROV:
      /* Provisioning command from System Management */
      sccp_prov_handle_sm_cmd (p_api);
      break;

    case SS7_SM_CTRL:
      /* Control command from System Management */
      sccp_ctrl_handle_sm_cmd (p_api);
      break;

    case SS7_SM_STATS:
      /* Statistics command from System Management */
      sccp_stat_handle_sm_cmd (p_api);
      break;

#ifdef SCCP_TRACE_ENABLED
    case SS7_SM_DEBUG:
      /* Debug command from System Management */
      sccp_dbg_handle_sm_cmd (p_api);
      break;
#endif

    case SS7_SM_ERROR:
      /* Error command from the System Management */
      sccp_err_handle_sm_cmd (p_api);
      break;
#ifdef SCCP_REDN_ENABLED

    case SS7_SM_REDN:
      /* Redn command from the System Management */
      sccp_redn_handle_sm_cmd (p_api);
      break;
#endif

    case SS7_SM_DISP:
      /* Display command from the System Management */
      sccp_display_handle_sm_cmd (p_api);
      break;

    default:
      SC_A_TRC (("SCCP::INIT:invalid SM category %d\n", category));
      SC_A_ERR (ESS7_INVALID_API_ELEMENT);
      sccp_sm_cmd_std_resp (p_api, SS7_FAILURE, param, put_param,
                            ESS7_INVALID_API_ELEMENT);
      break;
  }
}

#endif /* Commented SM API */

/*****************************************************************************
**
**  FUNCTION :
**    Handle Lower Layer (SCCP) API
**
******************************************************************************
**
**  DESCRIPTION :
**    Calls the appropriate function to handle an API from SCCP. For 
**    Connection less Service it directly calls the appropriate functions. But 
**    for connection Oriented service it maps the apis on to events and then 
**    calls the entry point function for the connection oriented services.
**
*****************************************************************************/

void
bssap_handle_ll_api
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
  U8bit api_id;
  return_t    result ;
  result = SS7_SUCCESS;
  api_id = GET_API_ID(p_api);

  LOG_PRINT (INFO,"bssap_handle_ll_api():SCCP mesg:%s\n",PRINT_SCCP_MSG(api_id))
  switch (api_id)
  {
    case SCCP_N_UNITDATA_INDICATION:
      result = sccp_n_unitdata_ind (p_api);
      break;

    case SCCP_N_STATE_INDICATION:
      result = sccp_n_state_ind (p_api);
      break;
    case SCCP_N_PCSTATE_INDICATION:
      result = sccp_n_pcstate_ind (p_api);
      break;
#ifdef SCCP_INCLUDE_CO_SERVICE
    case SCCP_N_CONNECT_INDICATION :
       result = sccp_n_connect_ind (p_api) ;
      break ;

    case SCCP_N_CONNECT_CONFIRM :
      result = sccp_n_connect_cnf (p_api) ;
      break ;

    case SCCP_N_DATA_INDICATION :
       result = sccp_n_data_ind(p_api);
      break ;

    case SCCP_N_DISCONNECT_INDICATION :
         result = sccp_n_disconnect_ind(p_api);
      break ;
#endif
      default:
      break;
  }
  if (result != SS7_SUCCESS)
  {
    LOG_PRINT(CRITICAL,"bssap_handle_ll_api():Error Failure in Processing of Lower Layer SCCP mesg\n");
    return;
  }
}

/*****************************************************************************
**
**  FUNCTION :
**    sccp_handle_extended_api
**
******************************************************************************
**
**  DESCRIPTION :
**    Handles the Extended Api 
**
**
**
*****************************************************************************/

void
sccp_handle_extended_api
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
	U8bit	extended_api_id;
	extern U8bit sccp_state;
#ifdef DISTRIBUTED_SCCP
   	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
#endif

	if (bssap_state == UNINITIALIZED)
    {
        LOG_PRINT(CRITICAL,"sccp_handle_extended_api():INIT:message in UNINTITALIZED state.\n");
        bssap_free(p_api);
        return ;
    }


#ifdef DISTRIBUTED_SCCP
    if(dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] != DSCCP_INSTANCE_STATUS_ALIVE)
   	{
   		/** Do not handle user API in non ALIVE state */
		/* Replaced TCAP with UPPER LAYER in following line as per SPR #13067 FIX */
      	LOG_PRINT(CRITICAL,"sccp_handle_extended_api():INIT:message from UPPER LAYER in NON ALIVE state\n");
	/* SPR 12565 FIX Start */
	sccp_free(p_api);
	/* SPR 12565 FIX End */
      	return ;
	}
#endif

	extended_api_id = GET_EXTENDED_API_ID(p_api);

	switch(extended_api_id)
	{
		default:
		{
			LOG_PRINT(INFO,"ccp_handle_extended_api()INIT: INVALID EXTENDED API ID RECEIVED\n");
		}
	}
	return;
}




/*****************************************************************************
**
**  FUNCTION :
**    Minimal check of api header
**
******************************************************************************
**
**  DESCRIPTION :
**    Check only if api Id is valid and version is proper. It also puts up
**    a check on the length of the API to ensure that it is atleast 
**    greater than the header length. 
**
*****************************************************************************/

return_t sccp_chk_api_hdr (U8bit * p_api)
{
  U8bit api_id, vers_id;
  U16bit api_len;

  /* read the API id */
  api_id  = GET_API_ID (p_api);
  /* Read the version id */
  vers_id = GET_API_VER(p_api);
  /* Read the API length */
  api_len = GET_API_LEN(p_api);

  if (SS7_FAILURE == sccp_chk_api_id(api_id))
    return SS7_FAILURE;

  if (SS7_FAILURE == sccp_chk_vers_id(vers_id))
    return SS7_FAILURE;

  if (api_len < API_HEADER_LEN)
  {
    LOG_PRINT(CRITICAL,"sccp_chk_api_hdr():INIT:api len invalid %d\n", api_len);
    SC_A_ERR (ESS7_INVALID_LENGTH);
    return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}



/*****************************************************************************
**
**  FUNCTION :
**    Check if api is is valid
**
******************************************************************************
**
**  DESCRIPTION :
**    Check if api id is from timer, SM , tcap or mtp3.
**
*****************************************************************************/

return_t sccp_chk_api_id (U8bit api_id)
{
/* SPR - 11095 */
	if(api_id == SS7_EXTENDED_API)
	{
		LOG_PRINT(CRITICAL,"sccp_chk_api_id():INIT: Extended API not yet supported");
		SC_A_ERR(ESS7_INVALID_API_ID);
		return SS7_FAILURE;
	}
/* SPR - 11095 */

#ifdef DISTRIBUTED_SCCP
	if(api_id == DSCCP_MATE_API)
  		return SS7_SUCCESS;
#endif
  if ( ! ((SS7_TIMER_API_ID == api_id) ||
          (SCCP_SM_REQUEST_API == api_id) ||
          ((api_id >= MTP3_MIN_API_TO_UP) &&
           (api_id <= MTP3_MAX_API_TO_UP))    ||
          ((api_id >= SCCP_MIN_API_FROM_TC) &&
           (api_id <= SCCP_MAX_API_FROM_TC)) ||
		  (api_id == SCCP_DEREGISTER_USER)))
  {
    LOG_PRINT(CRITICAL,"sccp_chk_api_id():INIT:unknown API id %d\n", api_id);
    SC_A_ERR (ESS7_INVALID_API_ID);
    return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}

/*****************************************************************************
**
**  FUNCTION :
**    Version id check
**
******************************************************************************
**
**  DESCRIPTION :
**    Check if the version id is valid
**
*****************************************************************************/

return_t
sccp_chk_vers_id
#ifdef ANSI_PROTO
  (U8bit vers_id)
#else
  (vers_id)
   U8bit vers_id;
#endif
{
/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
	if( DSCCP_VERSION_ID == vers_id)
		return SS7_SUCCESS;
#endif
/* SPR # 7470 Fix End */
  if ( ! (SCCP_VERSION_ID == vers_id))
  {
    LOG_PRINT(CRITICAL,"sccp_chk_vers_id():INIT:invalid version id %d\n", vers_id);
    SC_A_ERR (EVERSION_ID);
    return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}
