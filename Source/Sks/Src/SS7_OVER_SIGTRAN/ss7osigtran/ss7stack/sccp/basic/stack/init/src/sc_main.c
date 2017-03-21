/*****************************************************************************
**  FILE NAME:
**      sc_main.c
**
******************************************************************************
**
**  FUNCTION:
**      the process message function which calls all other functions
**      depending on API ID
**
**  DESCRIPTION:
**
**
**  DATE     NAME             REF#           REASON
**  --------------------------------------------------------------
**  17May'04 Ganesh Kumar				Fixed SPR # 13444
**  20Oct'03 Ganesh Kumar				Fixed SPR # 12565
**  15Feb'03 Ashish Sawalkar		 	 Fixed SPR # 11321, D-MATE 
**  02Feb'03 Ashish Sawalkar		 	 Fixed SPR # 11180
**  14Jan'03 Salil Agrawal				 Fixed SPR # 11095
**  22July02 Suyash Tripathi             Fixed SPR # 9302       
**  27Jun'02 Ashish Sawalkar             Fixed SPR 9104, 9105
**  21June02 Salil Kumar Agrawal         Added register_resp API
**  18June02 Salil Kumar Agrawal         SET GET state changes
**  01May'02 Ashish Sawalkar        	 Fixed SPR 8676
**  20Feb'02 Sachin Bhatia               De-reg, Deinit API changes 
**  20Feb'02 Sachin Bhatia               De-reg API changes 
**  04Feb'02 Sachin Bhatia                    Fixed SPR # 8553 
**  22Jan'02 Prateek Bidwalkar                Fixed SPR # 7470 
**  26Dec'01 Prateek Bidwalkar                Fixed SPR # 7450 
**  4Feb'02 Prateek Bidwalkar			  Added code for Multi-threading
**  5Nov'01 Pawanish Modi                changes for DSCCP class 1 and 3
**  24Oct'01 Prateek Bidwalkar                Fixed SPR # 6750
**	15Oct'99 Ramu Kandula	  SPR #878	      replaced ss7_mem_free 
**											  with sccp_free
**  22Sep'98 Praneet Khare    ------------    Adding more comments
**  16Jul'98 Praneet Khare    ------------    Adding Connection Oriented Part
**  8May98   Sriganesh. Kini  HSS:20800008    Original
**
**  Copyright 1997, Hughes Software Systems
**
*****************************************************************************/

#include "sc_stgl.h"

/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */
#include "sccp_port.h"
#ifdef SCCP_MT_SAFE

#include "sccp_mtlib_port.h"

/* These semaphore decalarations are used in the MT safe variant of stack */
extern S32bit part_concurrent_count_sem;
extern S32bit concurrent_count_sem;

#endif

/* SPR # 7470 Fix Start */
/* Global variable indication whether the class 1 messages should be buffered
**	or not, until this timer is running.
*/
#ifdef DISTRIBUTED_SCCP
U8bit		dsccp_class1_timer_status ;
timer_id_t	dsccp_cls1_buf_inh_timer_id;
#endif
/* SPR # 7470 Fix End */

int check_flag =0;
extern  bpmCardState_info_t bpmCardState;
/*extern unsigned char  bpmCardState;*/
/****************************************************************************
**
**  The Static declaration for the functions that are used in this file 
**  only
**
****************************************************************************/

static void sccp_handle_timeout
  _ARGS_ ((U8bit * p_api));

static void sccp_handle_sm_api
  _ARGS_ ((U8bit * p_api));

static void sccp_handle_hl_api
  _ARGS_ ((U8bit * p_api));

static void sccp_handle_ll_api
  _ARGS_ ((U8bit * p_api));

static return_t sccp_chk_api_hdr
  _ARGS_ ((U8bit * p_api));

static return_t sccp_chk_api_id
  _ARGS_ ((U8bit api_id));

static return_t sccp_chk_vers_id
  _ARGS_ ((U8bit vers_id));

static void sccp_handle_extended_api
  _ARGS_ ((U8bit * p_api));

extern void connect_to_sg(U8bit trans_id); /* Amaresh for ASP down */
extern unsigned int omc_connect_trans_id,omc_disconnect_trans_id;
/*****************************************************************************
**
**  Global Variable for the Return value
**
*****************************************************************************/

return_t sccp_ret_val;

/*****************************************************************************
**
**  FUNCTION :
**    Entry point to SCCP stack
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

#ifdef SCCP_MT_SAFE
void
#else
return_t
#endif
sccp_process_mesg
#ifdef ANSI_PROTO
  (pvoid p_msg)
#else
  (p_msg)
  pvoid p_msg;
#endif
{
  U8bit api_id,  *p_api ;
	extern U8bit sccp_state;
    extern U8bit sccp_redn_sub_state;
	error_t ecode;
#ifdef DISTRIBUTED_SCCP
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
#endif

  p_api = (U8bit *)p_msg;

/* Check the state of SIGTRAN added by Amaresh start as on dated 08-02-16 */
  if (bpmCardState.curr_state == SS7_CARD_STATE_STANDBY)
  {
   	SC_I_TRC (("SCCP::Process message in SS7_CARD_STATE_STANDBY state only SCM-MESSAGE.\n"));
	}
/* Check the state of SIGTRAN added by Amaresh stop as on dated 08-02-16 */



#ifdef SCCP_MT_SAFE
	/* Initializing self thread id to be used in stack traces */
	ss7_init_self_thread_id();
#endif


/*  SC_I_TRC (("SCCP::process incoming message %d of file %s (function %s)\n",__LINE__, __FILE__, __func__)); */
  SC_I_TRC (("SCCP::process incoming message\n"));
  SC_A_DTRC (p_api);

  /* Check the API header */
  if (SS7_FAILURE == sccp_chk_api_hdr (p_api))
  {
    sccp_free(p_api);
#ifdef SCCP_MT_SAFE
	return;
#else
    return SS7_FAILURE;
#endif
  }

  sccp_ret_val = SS7_SUCCESS;

  sls_assigned = SS7_FALSE; /* SPR #13444 FIX */

  /* Get the API id */
  api_id = GET_API_ID(p_api);

  if (api_id == MTP3_UP_TRANSFER_INDICATION)
		check_flag ==1;

  if (api_id == SS7_EXTENDED_API)	
  {
    SC_I_TRC (("SCCP::INIT:message SS7_EXTENDED_API\n"));
	sccp_handle_extended_api(p_api);
  }

  else
  if (((api_id >= SCCP_MIN_API_FROM_TC) &&
      (api_id <= SCCP_MAX_API_FROM_TC)) || (api_id==SCCP_DEREGISTER_USER))
  {
    /* API from the Upper Layer i.e. TCAP/EMAP */
    SC_I_TRC (("SCCP::INIT:message from SCCP_MIN_API_FROM_TC/SCCP_MAX_API_FROM_TC\n"));
	if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
	{
    	SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));
    	sccp_free(p_api);
#ifdef SCCP_MT_SAFE
    	return;
#else
    	return SS7_FAILURE;
#endif /* SCCP_MT_SAFE */
	}
#ifdef DISTRIBUTED_SCCP
    if(dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] != DSCCP_INSTANCE_STATUS_ALIVE)
    {
	/** Do not handle user API in non ALIVE state */
    	SC_I_TRC (("SCCP::INIT:message from TCAP in NON ALIVE state\n"));
    	sccp_free(p_api);
#ifdef SCCP_MT_SAFE
	return;
#else
    return SS7_FAILURE;
#endif
    }
#endif
    
    /* changes done by Amaresh  */
#ifdef SCCP_REDN_ENABLED
    if ((sccp_redn_sub_state == STACK_STANDBY) && (api_id != SCCP_REGISTER_USER))
    {
        SC_I_TRC (("SCCP::INIT:message from TCAP/BSSAP in STACK_STANDBY state sccp_handle_hl_api()\n"));
        sccp_free(p_api);
		/** SPR 9302 Start Fix **/
#ifdef SCCP_MT_SAFE
		return ;
#else
        return SS7_FAILURE;
#endif
		/** SPR 9302 End Fix **/
    }
    else
        sccp_handle_hl_api (p_api);
#else
    sccp_handle_hl_api (p_api);
#endif
    /* end */
    
  }
  else
  if ((api_id >= MTP3_MIN_API_TO_UP) &&
      (api_id <= MTP3_MAX_API_TO_UP))
  {
    /* API from the Lower Layer i.e. MTP3 */

    SC_I_TRC (("SCCP::INIT:message from Lower Layer MTP3_MIN_API_TO_UP/MTP3_MAX_API_TO_UP\n"));

	/* SPR # 11321 : Start Fix
	 * Moving this check inside MTP3 indication handling functions 
 	 * since RLC needs to be handled in BLOCKED state.
 	 */ 
#if 0
**
**	if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
**	{
**   	SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));
**    	sccp_free(p_api);
**#ifdef SCCP_MT_SAFE
**    	return;
**#else
**    	return SS7_FAILURE;
**#endif /* SCCP_MT_SAFE */ 
**	}
**
#endif
	/* SPR # 11321 : End Fix */

#ifdef DISTRIBUTED_SCCP
    if(dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] != DSCCP_INSTANCE_STATUS_ALIVE)
    {
	/** Do not handle MTP3 API in non ALIVE state */
    	SC_I_TRC (("SCCP::INIT:message from Lower layer in NON ALIVE state\n"));
    	sccp_free(p_api);
#ifdef SCCP_MT_SAFE
		return;
#else
    	return SS7_FAILURE;
#endif
    }
#endif	
    
    /* changes done by Amaresh  for disable redn during start time  */
#ifdef SCCP_REDN_ENABLED  
    if (sccp_redn_sub_state == STACK_STANDBY)
    {
        SC_I_TRC (("SCCP::INIT:message from LOWER LAYER in STACK_STANDBY state sccp_handle_ll_api()\n"));
        sccp_free(p_api);
        /** SPR 9302 Start Fix **/
#ifdef SCCP_MT_SAFE
        return ;
#else
        return SS7_FAILURE;
#endif
        /** SPR 9302 End Fix **/
    }
    else
        sccp_handle_ll_api (p_api);
#else
    sccp_handle_ll_api (p_api);
#endif
    /* end */
  
  }
  else
  if (SS7_TIMER_API_ID == api_id)
  {
    /* API from the Timer Management */
    SC_I_TRC (("SCCP::INIT:timeout message SS7_TIMER_API_ID\n"));
	if (sccp_state == UNINITIALIZED)
	{
    	SC_I_TRC (("SCCP::INIT:Timer message in UNINTITALIZED state.\n"));
    	sccp_free(p_api);
#ifdef SCCP_MT_SAFE
        return;
#else
        return SS7_FAILURE;
#endif /* SCCP_MT_SAFE */ 

	}
    
    /* changes done by Amaresh */
#ifdef SCCP_REDN_ENABLED
    if (sccp_redn_sub_state == STACK_STANDBY)
    {
        SC_I_TRC (("SCCP::INIT: timeout message in STACK_STANDBY state sccp_handle_timeout()\n"));
        sccp_free(p_api);
        /** SPR 9302 Start Fix **/
#ifdef SCCP_MT_SAFE
        return ;
#else
        return SS7_FAILURE;
#endif
        /** SPR 9302 End Fix **/
    }
    else
        sccp_handle_timeout (p_api);
#else
    sccp_handle_timeout (p_api);
#endif
    /* end */

  }
#ifdef DISTRIBUTED_SCCP
  else
  if(api_id == DSCCP_MATE_API)
  {
  	/* SPR D-MATE Fix */
	if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)	
	{
    	SC_I_TRC (("SCCP::INIT:MATE message in UNINTITALIZED state.\n"));
    	sccp_free(p_api);
#ifdef SCCP_MT_SAFE
    	return;
#else
    	return SS7_FAILURE;
#endif /* SCCP_MT_SAFE */
	}
	else
	{
    	SC_I_TRC (("SCCP::INIT:message from MATE SCCP\n"));
    	dsccp_process_mesg (p_api, &ecode);
	}
  }
#endif
  else
  {
    /* API from the System Management */
    SC_I_TRC (("SCCP::INIT:message from SM sccp_handle_sm_api()\n"));
    sccp_handle_sm_api(p_api);
  }

  /* Free up the memory */
if (p_api != SS7_NULL)
	{
		SC_A_DTRC (p_api);
		sccp_free ((U8bit*)p_api); 
   }
/* start added during CC compilation */
/* assign pvoid to U8bit* */ 

/* end added during CC compilation */


#ifdef SCCP_MT_SAFE
	return;
#else
 	 return sccp_ret_val;
#endif
/* SPR 9302 - Fix Start */
ecode = 0;
/*sccp_redn_sub_state = 0;*/
/* sccp_redn_sub_state = ACTIVE;*//* Amaresh commented 19-02-16 */
/* SPR 9302 - Fix Start */
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

void
sccp_handle_timeout
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
  U8bit timer_id;
#ifdef SCCP_INCLUDE_CO_SERVICE
  msg_info_t  info ;
  error_t     ecode ;
  return_t    result = SS7_SUCCESS;
#endif

  /* Get the timer id of the timer that has expired */
  timer_id = GET_TIMER_ID(p_api);

#ifdef SCCP_INCLUDE_CO_SERVICE
  info.flag = 0;
  info.p_api = p_api ;
#endif

  switch (timer_id)
  {
#ifdef BACK_UP_SSN
	case T_COORD_TIMER_ID:
		sccp_t_coord_timeout(p_api);
/* start added during CC compilation */
/* the function mus
t be prototype  */
 

/* end added during CC compilation */

		break;
	case T_IGNORE_SST_TIMER_ID:
		sccp_t_ignore_sst_timeout(p_api);
/* start added during CC compilation */
/* the function mus
t be prototype  */
 

/* end added during CC compilation */

		break;
#endif
#ifdef DISTRIBUTED_SCCP	
	case T_DSCCP_CONF_TIMER_ID:
		dsccp_handle_conf_timeout(p_api, &ecode);
		break;

	case T_REASSEMBLY_QUERY_TIMER_ID:
		dsccp_process_t_reass_query_timer_expiry(p_api);
		break;
	case T_DSCCP_CLASS1_BUFFER_TIMER_ID:
    		SC_I_TRC (("DSCCP::DSCCP_CLASS1_BUFFER TIMER expiry recd.\n"));
		result = dsccp_handle_t_class1_buffer_timer_expiry(p_api, &ecode);
		break;
/* SPR # 7450 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
	case T_DSCCP_INST_DEACTIVATION_TIMER_ID:
		SC_I_TRC (("DSCCP::T_DSCCP_INST_DEACTIVATION TIMER expiry recd. \n"));
		result = dsccp_handle_inst_deactivation_timer_expiry(p_api, &ecode);
		break;
#endif
/* SPR # 7450 Fix End */

/* SPR # 7470 Fix Start */
	case T_DSCCP_CLASS1_BUFFER_INHIBIT_ID:
   		SC_I_TRC (("DSCCP::T_DSCCP_CLASS1_BUFFER_INHIBIT_ID TIMER expiry recd.\n"));
		result = dsccp_handle_cls1_buf_inh_timer_expiry(p_api, &ecode);
		break;
/* SPR # 7470 Fix End */
#endif

    case T_REASSEMBLY_TIMER_ID:
      /* Re-assembly timer timeout */
      sccp_handle_t_reassembly_timeout (p_api);
#ifdef SCCP_MT_SAFE
	  ss7_sem_decr(&part_concurrent_count_sem);
#endif
      break;

    case T_STAT_INFO_TIMER_ID:
      /* Status timer timeout */
      sccp_handle_t_stat_info_timeout (p_api);
      break;

    case T_A_TIMER_ID:
      sccp_handle_ta_timeout (p_api);

	/* SPR# 9104: Start Fix */
#ifdef SCCP_MT_SAFE
      ss7_sem_decr(&concurrent_count_sem);
#endif
	/* SPR# 9104: End Fix */

      break;

    case T_D_TIMER_ID:
      sccp_handle_td_timeout (p_api);

	/* SPR# 9104: Start Fix */
#ifdef SCCP_MT_SAFE
      ss7_sem_decr(&concurrent_count_sem);
#endif 
	/* SPR# 9104: End Fix */

      break;

    case T_CON_TIMER_ID:
      sccp_handle_t_con_timeout (p_api);

	/* SPR# 9105: Start Fix */
#ifdef SCCP_MT_SAFE
      ss7_sem_decr(&concurrent_count_sem);
#endif
	/* SPR# 9105: End Fix */

      break;
		

#ifdef SCCP_INCLUDE_CO_SERVICE
	case T_DEINIT_TIMER_ID:
	  sccp_handle_t_deinit_timeout(p_api);
	  break;

    case T_CONNEST_TIMER_ID :
      /* Connection establishment timer timeout */
      info.event = SCCP_T_CONNEST_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_IAS_TIMER_ID :
      /* Inactivity send timer timeout */
      info.event = SCCP_T_IAS_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_IAR_TIMER_ID :
      /* Inactivity receive timer timeout */
      info.event = SCCP_T_IAR_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_REL_TIMER_ID :
      /* Connection release timer timeout */
      info.event = SCCP_T_REL_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_REPREL_TIMER_ID :
      /* Repeat release timer timeout */
      info.event = SCCP_T_REPREL_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_INT_TIMER_ID :
      /* Interval timer timeout */
      info.event = SCCP_T_INT_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_GAURD_TIMER_ID :
      /* Gaurd timer timeout */
      info.event = SCCP_T_GAURD_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_RESET_TIMER_ID :
      /* Reset timer timeout */
      info.event = SCCP_T_RESET_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case T_FREEZE_TIMER_ID :
      /* Freeze timer timeout */
      info.event = SCCP_T_FREEZE_TIME_OUT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

#endif

    default:
      SC_S_TRC (("SCCP::INIT:invalid timer id %d expires\n", timer_id));
      SC_S_ERR (ESYS_ERROR);
      break;
  }


#ifdef SCCP_MT_SAFE

  /* Unlocking the connection oriented locks held perviously */
  switch(timer_id)
  {
#ifdef SCCP_INCLUDE_CO_SERVICE
		case T_CONNEST_TIMER_ID:
		case T_IAS_TIMER_ID:
		case T_IAR_TIMER_ID:
		case T_REL_TIMER_ID:
		case T_REPREL_TIMER_ID:
		case T_INT_TIMER_ID:
		case T_GAURD_TIMER_ID:
		case T_RESET_TIMER_ID:
			ss7_sem_decr(&part_concurrent_count_sem);
			break;

		case T_FREEZE_TIMER_ID:
			ss7_sem_decr(&concurrent_count_sem);
			break;
#endif
		default:
			break;
  }
#endif /* SCCP_MT_SAFE */

#ifdef SCCP_INCLUDE_CO_SERVICE
  if (result != SS7_SUCCESS)
  {
    /* Error */
    SCCP_UT_TRACE (("SCCP::UT: Error in parsing of SCCP CO timer timeout\n"));
  }
#endif

}

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

  SC_STAT_API_INR_IN_API_SM();
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

/*****************************************************************************
**
**  FUNCTION :
**    Handles a lower layer (MTP3) api
**
******************************************************************************
**
**  DESCRIPTION :
**    Calls appropriate function to handle a lower layer API
**
*****************************************************************************/

void
sccp_handle_ll_api
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
  U8bit api_id;
  U8bit tran_id=10;

/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
	U8bit	dsccp_class1_timer_buf [DSCCP_CONF_TIMER_BUF_LEN];
#endif
/* SPR # 7470 Fix End */

  SC_STAT_API_INR_IN_API_LL();
  api_id = GET_API_ID (p_api);


  switch (api_id)
  {
    case MTP3_UP_TRANSFER_INDICATION:
/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
	if(DSCCP_VERSION_ID == GET_API_VER(p_api))
	{
		/* buffer the message and start the timer */

		dsccp_class1_timer_buf[0] = T_DSCCP_CLASS1_BUFFER_INHIBIT_ID;
		dsccp_class1_timer_buf[1] = sc_opt.dsccp_local_instance_id;

		if(SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUF_INH_MSG_DEF_VAL,\
				dsccp_class1_timer_buf, 2, &dsccp_cls1_buf_inh_timer_id))
		{
			dsccp_class1_timer_status = SS7_TRUE;
			if(SS7_FAILURE == dsccp_store_class1_messages(p_api))
			{
      			sccp_m3_transfer_ind (p_api);
			}
		}
		else
      		sccp_m3_transfer_ind (p_api);
	}
	else
#endif
/* SPR # 7470 Fix End */
      sccp_m3_transfer_ind (p_api);
      break;

    case MTP3_UP_PAUSE_INDICATION:
      sccp_m3_pause_ind (p_api);
			if (omc_disconnect_trans_id != 0xffff || omc_disconnect_trans_id == 0)
      {
#if 0
				 LOG_PRINT(INFO,"[ENCAPS::NIB_CLIENT]M3UA:Sending connect_to_sg again from SCCP\n");
					connect_to_sg(0);
#endif /* Commented by Amaresh due to SCM should try */
			}
      break;

    case MTP3_UP_RESUME_INDICATION:
      sccp_m3_resume_ind (p_api);
      break;

    case MTP3_UP_STATUS_INDICATION:
      sccp_m3_status_ind (p_api);
      break;

    /* GR changes: two new APIs added for cluster based routing */

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)

    case MTP3_ANSI_UP_CLUSTER_PAUSE_INDICATION:
   	if ((COMPARE_ANSI) || (COMPARE_BCGR))
   	{
        	sccp_m3_pause_cluster_ind (p_api);
	}
        	break;
    case MTP3_ANSI_UP_CLUSTER_RESUME_INDICATION:
   	if ((COMPARE_ANSI) || (COMPARE_BCGR))
   	{
        	sccp_m3_resume_cluster_ind (p_api);
	}
        break;
#endif

    default:
      break;
  }
}

/*****************************************************************************
**
**  FUNCTION :
**    Handle higher layer (TCAP) API
**
******************************************************************************
**
**  DESCRIPTION :
**    Calls the appropriate function to handle an API from TCAP. For 
**    Connection less Service it directly calls the appropriate functions. But 
**    for connection Oriented service it maps the apis on to events and then 
**    calls the entry point function for the connection oriented services.
**
*****************************************************************************/

void
sccp_handle_hl_api
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit *p_api;
#endif
{
  U8bit api_id;
#ifdef SCCP_INCLUDE_CO_SERVICE
  msg_info_t  info ;
  error_t     ecode ;
  return_t    result ;
 /* SPR # 8553... Fix Starts */
#if 0
 /* SPR # 8553... Fix Ends */
  info.p_api = p_api ;
 /* SPR # 8553... Fix Starts */
#endif
 /* SPR # 8553.. Fix Ends */
  result = SS7_SUCCESS;
#endif

 /* SPR # 8553... Fix Starts */
#ifdef SCCP_INCLUDE_CO_SERVICE
  ss7_mem_zero(&info,sizeof(msg_info_t));
  info.p_api = p_api ;
#endif
 /* SPR # 8553... Fix Ends */



  SC_STAT_API_INR_IN_API_SU();
  api_id = GET_API_ID(p_api);


  switch (api_id)
  {
    case SCCP_N_UNITDATA_REQUEST:
      sccp_n_unitdata_req (p_api);
      break;

    case SCCP_N_STATE_REQUEST:
      sccp_n_state_req (p_api);
      break;
#ifdef BACK_UP_SSN
	case SCCP_N_COORD_REQUEST:
		sccp_n_coord_request(p_api);
/* start added during CC compilation */
/* the function mus
t be prototype  */
 

/* end added during CC compilation */

		break;
	case SCCP_N_COORD_RESPONSE:
		sccp_n_coord_response(p_api);
/* start added during CC compilation */
/* the function mus
t be prototype  */
 

/* end added during CC compilation */

		break;
#endif

    case SCCP_REGISTER_USER:
        
        /* changes done by salil for register response to user */
        {
            return_t ret_val;
            error_t p_ecode;
            ret_val = sccp_register_user (p_api,&p_ecode);
/*            sccp_register_resp(p_api,ret_val,p_ecode); 
*/        }
        /* end */
        
        break;

    case SCCP_DEREGISTER_USER:
      sccp_deregister_user (p_api);
      break;

#ifdef SCCP_INCLUDE_CO_SERVICE
    case SCCP_N_CONNECT_REQUEST :
      info.event = SCCP_N_CONNECT_REQUEST_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_CONNECT_RESPONSE :
      info.event = SCCP_N_CONNECT_RESPONSE_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_CONNECT_REQUEST_TYPE1 :
      info.event = SCCP_REQUEST_TYPE_1_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_CONNECT_REQUEST_TYPE2 :
      info.event = SCCP_REQUEST_TYPE_2_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_DATA_REQUEST :
      info.event = SCCP_N_DATA_REQUEST_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_DISCONNECT_REQUEST :
      info.event = SCCP_N_DISCONNECT_REQ_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_INFORM_REQUEST :
      break ;

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
    case SCCP_N_EXPEDIATE_DATA_REQUEST :
      info.event = SCCP_N_EXP_DATA_REQUEST_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_RESET_REQUEST :
      info.event = SCCP_N_RESET_REQUEST_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;

    case SCCP_N_RESET_RESPONSE :
      info.event = SCCP_N_RESET_RESPONSE_EVENT ;
      result = sccp_handle_co_mesg (&info, &ecode) ;
      break ;
#endif
#endif

    default:
      break;
  }

#ifdef SCCP_MT_SAFE

  /* Unlocking the connection oriented locks held previously */
  switch(api_id)
  {
#ifdef SCCP_INCLUDE_CO_SERVICE
		case SCCP_N_CONNECT_REQUEST:
		case SCCP_N_CONNECT_REQUEST_TYPE1: /* spr 11180 fix */
		case SCCP_N_CONNECT_REQUEST_TYPE2:
		/* SPR# 8676 : Start Fix */
			/* ss7_sem_decr(&concurrent_count_sem); */
		/* SPR# 8676 : End Fix */
			break;
		case SCCP_N_CONNECT_RESPONSE:
		case SCCP_N_DATA_REQUEST:
		case SCCP_N_DISCONNECT_REQUEST:
		case SCCP_N_INFORM_REQUEST:
			ss7_sem_decr(&part_concurrent_count_sem);
			break;
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
		case SCCP_N_EXPEDIATE_DATA_REQUEST:
		case SCCP_N_RESET_REQUEST:
		case SCCP_N_RESET_RESPONSE:
			ss7_sem_decr(&part_concurrent_count_sem);
			break;
#endif
#endif
		default:
		break;
  }/* end switch */

#endif /* SCCP_MT_SAFE */

#ifdef SCCP_INCLUDE_CO_SERVICE
  if (result != SS7_SUCCESS)
  {
    /* Error */
    SCCP_UT_TRACE (("SCCP::UT:Error Failure in Processing of CO mesg\n")) ;
    return ;
  }
#endif
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

	if (sccp_state == UNINITIALIZED)
    {
        SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));
        sccp_free(p_api);
        return ;
    }


#ifdef DISTRIBUTED_SCCP
    if(dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] != DSCCP_INSTANCE_STATUS_ALIVE)
   	{
   		/** Do not handle user API in non ALIVE state */
		/* Replaced TCAP with UPPER LAYER in following line as per SPR #13067 FIX */
      	SC_I_TRC (("SCCP::INIT:message from UPPER LAYER in NON ALIVE state\n"));
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
			SC_I_TRC (("SCCP::INIT: INVALID EXTENDED API ID RECEIVED\n"));
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

return_t
sccp_chk_api_hdr
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
   U8bit * p_api;
#endif
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
    SC_A_TRC (("SCCP::INIT:api len invalid %d\n", api_len));
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

return_t
sccp_chk_api_id
#ifdef ANSI_PROTO
  (U8bit api_id)
#else
  (api_id)
   U8bit api_id;
#endif
{
/* SPR - 11095 */
	if(api_id == SS7_EXTENDED_API)
	{
		SC_A_TRC(("SCCP::INIT: Extended API not yet supported"));
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
    SC_A_TRC (("SCCP::INIT:unknown API id %d\n", api_id));
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
    SC_A_TRC (("SCCP::INIT:invalid version id %d\n", vers_id));
    SC_A_ERR (EVERSION_ID);
    return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}
