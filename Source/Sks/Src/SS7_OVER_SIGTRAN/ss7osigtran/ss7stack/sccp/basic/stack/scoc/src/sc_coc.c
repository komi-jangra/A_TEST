/*****************************************************************************
**
**  FILE :
**    Main file for the SCCP connection oriented part
**
******************************************************************************
**
**  FILENAME :
**    sc_coc.c
**
**  DESCRIPTION :
**    This file contains the main function for handling the APIs or the 
**    NPDUs entering the SCCP Connection Oriented Protocol
**
**  Date      Name             Reference     Reason
**  _________________________________________________________________________\
**  02Feb'03  Ashish Sawalkar				Fixed SPR 11180
**  14Oct'02  Ashish Sawalkar				Fixed SPR 10322 
**  06Jul'02  Ashish Sawalkar				Fixed SPR 9165 
**  18Jun'02  Suyash Tripathi            Fixed SPR 8986/9302
**  5April'02   Pawanish Modi            Fixed SPR 8612
**  4Feb'02   Prateek Bidwalkar            Added code for Multi-threading
**  14Mar'02  Sachin Bhatia  ------------  Fixed SPR 8596 
**  04Mar'02  Sachin Bhatia 	------------ Fixed SPR 8551 
**  26Dec'01  Prateek Bidwalkar ------------ Fixed SPR 7450 
**  10Dec'01  Pawanish Modi  ------------  	 Fixed SPR 7410 
**  13Nov'01  Ashish Sawalkar  ------------  Fixed SPR 7052 
**  12Sep'01  Aman Kapoor     -------------  Fixed SPR 5906
**  12Sep'01  Aman Kapoor     -------------  Fixed SPR 5907
**  24Oct'01  Prateek Bidwalkar              Fixed SPR 6750
**  03Oct'01  Ramu Kandula     ------------  SPR # 6367 Fix
**  11Sep'01  Prateek Bidwalkar              Fixed SPR 6126
**  03Jul'01  Pawanish Modi                  Fix SPR 5506 5508
**  03NOV'00  Arun Kumar       ------------  Adding Traffic Statistics
**  09Jun'00  Ramu Kandula     ------------  Fixed SPR 2579 - Change state
**                                           before sending message to SCRC
**  29Apr'99  Sudipta Pattar   ------------  Fixed SPR 1350
**  29Apr'99  Sudipta Pattar   ------------  Fixed SPR 1501 
**  12Oct'98  Praneet Khare    ------------  Adding Error Generation
**  22Sep'98  Praneet Khare    ------------  Adding Comments
**  08Jul'98  Praneet Khare    HSS:20800011  Original
**
**  Copyright 2000, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#ifdef DSCCP_STATS_ENABLED
#include "dsccp_stats.h"
#endif
#endif
/* SPR # 6750 Fix End */

#ifdef SCCP_INCLUDE_CO_SERVICE

#ifdef SCCP_MT_SAFE 
#include "sccp_mtlib_coc.h"
extern U8bit	conn_id_busy_arr[MAX_SCCP_CO_CONNECTIONS];
extern S32bit 	conn_id_arr_sync_sem;
#endif

/*****************************************************************************
**
**  DATA STRUCTURE :
**    Main Data Struture for Connection Control Block
**
******************************************************************************
**
**  DESCRIPTION :
**    This data declaration is for the main connection control block. The 
**    structure itself is defined in sc_ccb.h, but declared here. This is the
**    global data structure containing inforamtion about all the connection 
**    section supported by a particular node.
**
*****************************************************************************/

sccp_ccb_t    sccp_ccb [MAX_SCCP_CO_CONNECTIONS] ;

/*****************************************************************************
**
**  DATA STRUCTURE :
**    The function pointer table for the connection oriented FSM
**
******************************************************************************
**
**  DESCRIPTION :
**    This function pointer table contains the functions specific to the
**    connection oriented fsm of the sccp. The indexing is maintained on
**    the basis of state and the event. Associated with every event in every 
**    state there is a function. This table is defined and initialised in 
**    init module.
**
*****************************************************************************/

extern return_t (*sccp_co_func_ptr_table[SCCP_MAX_CO_STATES][SCCP_MAX_EVENTS])
                      _ARGS_((msg_info_t  *p_info,
                              error_t     *p_ecode)) ;

/*****************************************************************************
**
**  DATA STRUCTURE :
**    Array for Timer duration
**
******************************************************************************
**
**  DESCRIPTION :
**    This structure contains the timer duration to be used for each timer 
**    while starting up the timer in the timer module. The values are used
**    at the time of calling the ss7_start_timer function.
**    The array is initialised with default values, and the values could be 
**    chaged at run time by the system management entity.
**
*****************************************************************************/

/* SPR # 7450 Fix Start */
#if defined (DISTRIBUTED_SCCP) && (SCCP_INCLUDE_CO_SERVICE)
U32bit  sccp_co_timer_dur [MAX_SCCP_CO_TIMERS]=
        {SCCP_T_CONNEST_TIMER_DEF_VALUE,
         SCCP_T_IAS_TIMER_DEF_VALUE,
         SCCP_T_IAR_TIMER_DEF_VALUE,
         SCCP_T_REL_TIMER_DEF_VALUE,
         SCCP_T_REPREL_TIMER_DEF_VALUE,
         SCCP_T_INT_TIMER_DEF_VALUE,
         SCCP_T_GAURD_TIMER_DEF_VALUE,
         SCCP_T_RESET_TIMER_DEF_VALUE,
         SCCP_T_FREEZE_TIMER_DEF_VALUE,
	 /* SPR # 8551 Fix Start */
    		 0,
                 0,
                 DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE,
	 /* SPR # 8551 Fix Ends */
                 DSCCP_T_INST_DEACTIVATION_TIMER_DEF_VAL,
	 /* SPR # 8551 Fix Start */
                 0
	 /* SPR # 8551 Fix Ends */
        } ;
#else
U32bit  sccp_co_timer_dur [MAX_SCCP_CO_TIMERS]=
        {SCCP_T_CONNEST_TIMER_DEF_VALUE,
         SCCP_T_IAS_TIMER_DEF_VALUE,
         SCCP_T_IAR_TIMER_DEF_VALUE,
         SCCP_T_REL_TIMER_DEF_VALUE,
         SCCP_T_REPREL_TIMER_DEF_VALUE,
         SCCP_T_INT_TIMER_DEF_VALUE,
         SCCP_T_GAURD_TIMER_DEF_VALUE,
         SCCP_T_RESET_TIMER_DEF_VALUE,
         SCCP_T_FREEZE_TIMER_DEF_VALUE
        } ;
#endif
/* SPR # 7450 Fix End */
/*****************************************************************************
**
**  DATA STRUCTURE :
**    Mappping for the connection oriented timers
**
******************************************************************************
**
**  DESCRIPTION :
**    This structure contains a one to one mapping for the connection
**    oriented timers, for changing them to the global timer ids from the
**    local SCOC names.
**    Every name has a corresponding timer id associated with it, to be used
**    at the time of starting the timer.
**
*****************************************************************************/

U8bit   sccp_map_co_timer [MAX_SCCP_CO_TIMERS]=
        {T_CONNEST_TIMER_ID,
         T_IAS_TIMER_ID,
         T_IAR_TIMER_ID,
         T_REL_TIMER_ID,
         T_REPREL_TIMER_ID,
         T_INT_TIMER_ID,
         T_GAURD_TIMER_ID,
         T_RESET_TIMER_ID,
         T_FREEZE_TIMER_ID
        } ;

/*****************************************************************************
**
**  DATA STRUCTURE :
**    The strings for the timer names
**
******************************************************************************
**
**  DESCRIPTION :
**    The array contains the trace strings for the connection oriented 
**    timers.
**
*****************************************************************************/

#ifdef  __INSIGHT__
const char      *sccp_co_timer_string [MAX_SCCP_CO_TIMERS] =
#else
S8bit           *sccp_co_timer_string [MAX_SCCP_CO_TIMERS] =
#endif
{
   (S8bit*) "CONNECTION ESTABLISHMENT TIMER",
   (S8bit*) "INACTIVITY SEND TIMER",
   (S8bit*) "INACTIVITY RECEIVE TIMER",
   (S8bit*) "RELEASE TIMER",
   (S8bit*) "REPEAT RELEASE TIMER",
   (S8bit*) "INTERVAL TIMER",
   (S8bit*) "GAURD TIMER",
   (S8bit*) "RESET TIMER",
   (S8bit*) "FREEZE TIMER"
};
/* start added during CC compilation */
/* string initialiasation by S8bit* */
/* end added during CC compilation */

/*****************************************************************************
**
**  DATA STRUCTURE :
**    The strings for the connection state
**
******************************************************************************
**
**  DESCRIPTION :
**    The array contains the trace strings for the connection oriented 
**    states.
**
*****************************************************************************/

#ifdef  __INSIGHT__
const char      *sccp_co_state_string [SCCP_MAX_CO_STATES] =
#else
S8bit           *sccp_co_state_string [SCCP_MAX_CO_STATES] =
#endif
{
   (S8bit*) "SCCP_CONN_IDLE",
   (S8bit*) "SCCP_CONN_START",
   (S8bit*) "SCCP_CONN_ESTABLISHED",
   (S8bit*) "SCCP_CONN_CLOSING",
   (S8bit*) "SCCP_CONN_CLOSED",
   (S8bit*) "SCCP_CONN_RESET"
};
/* start added during CC compilation */
/* string initialiase by S8bit* */
/* end added during CC compilation */

/*****************************************************************************
**
**  DATA STRUCTURE :
**    The strings for the connection oriented events
**
******************************************************************************
**
**  DESCRIPTION :
**    The array contains the trace strings for the connection oriented 
**    events.
**
*****************************************************************************/

#ifdef  __INSIGHT__
const char      *sccp_co_event_name [SCCP_MAX_EVENTS] =
#else
S8bit           *sccp_co_event_name [SCCP_MAX_EVENTS] =
#endif
{
   (S8bit*) "SCCP_N_CONNECT_REQUEST_EVENT",
   (S8bit*) "SCCP_N_CONNECT_RESPONSE_EVENT",
   (S8bit*) "SCCP_N_DISCONNECT_REQ_EVENT",
   (S8bit*) "SCCP_REQUEST_TYPE_1_EVENT",
   (S8bit*) "SCCP_REQUEST_TYPE_2_EVENT",
   (S8bit*) "SCCP_N_RESET_REQUEST_EVENT",
   (S8bit*) "SCCP_N_RESET_RESPONSE_EVENT",
   (S8bit*) "SCCP_N_DATA_REQUEST_EVENT",
   (S8bit*) "SCCP_N_EXP_DATA_REQUEST_EVENT",
   (S8bit*) "SCCP_CR_EVENT",
   (S8bit*) "SCCP_CC_EVENT",
   (S8bit*) "SCCP_CREF_EVENT",
   (S8bit*) "SCCP_RLSD_EVENT",
   (S8bit*) "SCCP_RLC_EVENT",
   (S8bit*) "SCCP_RSR_EVENT",
   (S8bit*) "SCCP_RSC_EVENT",
   (S8bit*) "SCCP_ROUTE_FAIL_EVENT",
   (S8bit*) "SCCP_DT1_EVENT",
   (S8bit*) "SCCP_DT2_EVENT",
   (S8bit*) "SCCP_AK_EVENT",
   (S8bit*) "SCCP_IT_EVENT",
   (S8bit*) "SCCP_ED_EVENT",
   (S8bit*) "SCCP_EA_EVENT",
   (S8bit*) "SCCP_ERR_EVENT",
   (S8bit*) "SCCP_T_CONNEST_TIME_OUT",
   (S8bit*) "SCCP_T_IAR_TIME_OUT",
   (S8bit*) "SCCP_T_IAS_TIME_OUT",
   (S8bit*) "SCCP_T_REL_TIME_OUT",
   (S8bit*) "SCCP_T_REPREL_TIME_OUT",
   (S8bit*) "SCCP_T_INT_TIME_OUT",
   (S8bit*) "SCCP_T_GAURD_TIME_OUT",
   (S8bit*) "SCCP_T_RESET_TIME_OUT",
   (S8bit*) "SCCP_T_REASSEMBLY_TIME_OUT",
   (S8bit*) "SCCP_T_FREEZE_TIME_OUT"
} ;
/* start added during CC compilation */
/* string initialiase by S8bit* */
/* end added during CC compilation */ 

/* SPR # 6126 Fix Start */
/*****************************************************************************
**
**  DATA STRUCTURE :
**   A hash table. 
**
******************************************************************************
**
**  DESCRIPTION :
**    The array acts as a hash table and stores the connections id's 
**
**
*****************************************************************************/
U32bit        sccp_hash_table[MAX_SCCP_CO_HASH_TABLE_SIZE];


/*****************************************************************************
**
**  DATA STRUCTURE :
**   A pointer. 
**
******************************************************************************
**
**  DESCRIPTION :
**    This pointer points to the head of the free list 
**    of connection control blocks.
**
**
*****************************************************************************/
U32bit    sccp_free_ccb_list_head;

/* SPR # 6126 Fix End */

/*****************************************************************************
**
**  Function prototype for the static function defined in the file
**
*****************************************************************************/

static return_t sccp_call_state_event_function
                _ARGS_((msg_info_t      *p_info,
                        error_t         *p_ecode)) ;
/* SPR 8596 Fix Starts */
#endif
return_t
sccp_co_dummy
  _ARGS_ ((void));
#ifdef SCCP_INCLUDE_CO_SERVICE
/* SPR 8596 Fix Ends */


/*****************************************************************************
**
**  FUNCTION :
**    Main entry point for the SCCP connection oriented protocol
**
******************************************************************************
**
**  DESCRIPTION :
**    This function handles the Apis and the NPDUs and after parsing them
**    maps them to the appropriate Event, and calls the appropriate state
**    event function of the FSM for the SCCP connection oriented protocol.
**
*****************************************************************************/

return_t
sccp_handle_co_mesg
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
   msg_info_t *p_info  ;
   error_t    *p_ecode ;
#endif
{
  sccp_ccb_t *p_ccb;
  return_t   result ;
  U8bit      *p_timer_buf ;
  U8bit	     error_cause ;
  pc_t       dpc_tmp;
  sp_entry_t *p_opc;
  ss_entry_t *p_ss_entry;
  ss_entry_t *p_temp;
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
  return_t ret_val;
#endif
/* SPR # 6750 Fix End */

  /* SPR# 9165: Start Fix */
#ifdef SCCP_MT_SAFE
   U8bit event_type = p_info->event;
#endif
  /* SPR# 9165: End Fix */
  
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_handle_co_mesg\n")) ;

  /* Initialise the error_code and the result */
  *p_ecode = 0 ;
  result = SS7_SUCCESS;

  /* switch on the basis of the event filled in the p_info->event field */
  switch (p_info->event)
  {
    case SCCP_N_CONNECT_REQUEST_EVENT :
#if 0 
      if (COMPARE_ETSI)
      {
        /* 
         * ETSI does not support N-CONNECT.request primitive so if this 
         * API comes in SCCP(ETSI) this should be rejected 
         */
        result = SS7_FALSE ;
        SCCP_UT_TRACE (("SCCP::UT: Error : Unspecified API\n")) ;
        *p_ecode = ESCCP_UNSPECIFIED_API_FOR_ETSI ;
        break;
      }
#endif

      /* parse the N-CONNECT.request api to get the various information */
      result = sccp_parse_n_connect_request_api (p_info->p_api, p_info) ;
#if 0
#ifdef SCCP_MT_SAFE
	   ADJUST_CONN_ID_BUSY_VAL
#endif
#endif
      if (result == SS7_SUCCESS)
      {
        if ((p_ccb = sccp_utl_get_free_ccb ()) != (sccp_ccb_t *)SS7_NULL)
        {
          /* Associate a free CCB with the connection */
          p_info->p_ccb = p_ccb;
          p_ccb->c_state = SCCP_CONN_IDLE;
/* SPR # 6126 Fix Start */          
          /* Create an entry in the hash table */
          if (sccp_utl_add_ccb_to_hash_tbl(p_ccb->ccb_id, 
                  p_info->l_id, p_info->corr_id) == SS7_FAILURE)
          {
              sccp_free_ccb (p_info->p_ccb);
              *p_ecode = ESCCP_DUPLICATE_CONN_REQ;
              result = SS7_FAILURE;
          }
/* SPR # 6126 Fix End */          
        }
        else
        {
          /* No free CCB found, so refuse the connection */
          p_info->originator = 
                 sccp_utl_get_cref_originator (SCCP_RFC_UNQUALIFIED) ;
          p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;
          /* Send N-DISCONNET.indication to the User */
          sccp_build_n_disconnect_ind_api (p_info, (sccp_ccb_t *)SS7_NULL);
          result = SS7_FAILURE;
        }
      }
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }
      break ;

    case SCCP_N_CONNECT_RESPONSE_EVENT :
      /* Parse the N-CONNECT.response API from the User */
      result = sccp_parse_n_connect_response_api (p_info->p_api, p_info) ;
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if (result == SS7_SUCCESS)
      {
        /* read the CCB associated with the connection section */
        result = sccp_utl_read_ccb (p_info);
      }
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }
	
      break ;

    case SCCP_N_DISCONNECT_REQ_EVENT :
      /* Parse the N-DISCONNECT.request API from the User */
      result = sccp_parse_n_disconnect_request_api (p_info->p_api, p_info) ;
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if (result == SS7_SUCCESS)
      {
        if (IS_CORR_ID_IE_PRESENT (p_info) && IS_LOGUID_IE_PRESENT (p_info))
        {
          /* 
           * Get the CCB associated with the corr_id and the log_uid present 
           * in the API 
           */
          p_info->p_ccb = sccp_utl_get_ccb (SCCP_CONN_START, p_info->l_id, 
                                                     p_info->corr_id); 
        /*  p_info->p_ccb = sccp_utl_get_ccb (SCCP_CONN_ESTABLISHED, p_info->l_id, 
                                                     p_info->corr_id);*/
        }

        if (!(IS_CORR_ID_IE_PRESENT (p_info) || IS_LOGUID_IE_PRESENT (p_info)))
        {
              /* Read the associated CCB with the connection section */
              result = sccp_utl_read_ccb (p_info);
        }

        if (p_info->p_ccb == SS7_NULL)
	  {
            /* 
             * If p_info->ccb == SS7_NULL, this means that there is no ccb 
             * associated with N-DISCONNECT.reuqest API
             */
#ifdef DISTRIBUTED_SCCP
		if(p_info->dsccp_mate_api  != SS7_TRUE)
		{
			ret_val = dsccp_build_and_send_disc_req_to_mate(p_info->p_api, p_ecode);	
			if(ret_val == SS7_FAILURE)
				return SS7_FAILURE;
#ifdef DSCCP_STATS_ENABLED
			DSC_STAT_TS_DISCONN_REQ();
			DSC_STAT_INR_DISCONN_REQ();
#endif
		}
#endif
			
            result = SS7_FAILURE;
	   }
      }
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }

      break ;

    case SCCP_REQUEST_TYPE_1_EVENT :
      /* Parse the Type 1 connection request by the User */
      result = sccp_parse_n_conn_req_type1_api (p_info->p_api, p_info) ;

/* spr 11180 fix */
#if 0
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
#endif
      if (result == SS7_SUCCESS)
      {
        if ((p_ccb = sccp_utl_get_free_ccb ()) != (sccp_ccb_t *)SS7_NULL)
        {
            /* Associate the free ccb with the connection section */
            p_info->p_ccb = p_ccb;
            /* Set the connection state to Idle */
            p_ccb->c_state = SCCP_CONN_IDLE;

/* SPR # 6126 Fix Start */
            /* Create an entry in the hash table */
            if (sccp_utl_add_ccb_to_hash_tbl(p_ccb->ccb_id, 
                  p_info->l_id, p_info->corr_id) == SS7_FAILURE)
            {
              sccp_free_ccb (p_info->p_ccb);
              *p_ecode = ESCCP_DUPLICATE_CONN_REQ;
              result = SS7_FAILURE;
            }
/* SPR # 6126 Fix End */
        }
        else
        {
            /* 
             * Couldn;t get a free cbb, send N-DISCONNECT.ind API to the 
             * User 
             */
            p_info->originator = 
                 sccp_utl_get_cref_originator (SCCP_RFC_UNQUALIFIED) ;
            p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;
            /* Build N-DISCONNECT.indication to the User */
            sccp_build_n_disconnect_ind_api (p_info, (sccp_ccb_t *)SS7_NULL);
          result = SS7_FAILURE;
        }
      }
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }

      break ;

    case SCCP_REQUEST_TYPE_2_EVENT :
      /* Parse the Request Type 2 API from the User */
      result = sccp_parse_n_conn_req_type2_api (p_info->p_api, p_info) ;

/* spr 11180 fix */
#if 0
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
#endif
      if (result == SS7_SUCCESS)
      {
        if ((p_ccb = sccp_utl_get_free_ccb ()) != (sccp_ccb_t *)SS7_NULL)
        {
          /* Associate the free ccb with the connection section */
          p_info->p_ccb = p_ccb;
          /* Set the connection section to Idle state */
          p_ccb->c_state = SCCP_CONN_IDLE;

/* SPR #6126 Fix Start */
          /* Create an entry in the hash table */
          if (sccp_utl_add_ccb_to_hash_tbl(p_ccb->ccb_id, 
                  p_info->l_id, p_info->corr_id) == SS7_FAILURE)
          {
              sccp_free_ccb (p_info->p_ccb);
              *p_ecode = ESCCP_DUPLICATE_CONN_REQ;
              result = SS7_FAILURE;
          }
/* SPR #6126 Fix End */
        }
        else
        {
          /* Couldn't get a free ccb, so refuse the connection */
          p_info->originator = 
                 sccp_utl_get_cref_originator (SCCP_RFC_UNQUALIFIED) ;
          p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;
          /* Build N-DISCONNECT.indication API to the User */
          sccp_build_n_disconnect_ind_api (p_info, (sccp_ccb_t *)SS7_NULL) ;

          /* build CREF message */
          SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
                                ("SCCP::CO:Building CREF Message\n")) ;
          p_info->msg_type = CREF_MSG_TYPE;
          p_info->dlr = p_info->slr ;
          p_info->rel_cause = SCCP_RFC_UNQUALIFIED;
          if (IS_CG_IE_PRESENT (p_info))
          {
            sccp_copy_sccp_addr (&p_info->cg_addr, &p_info->cd_addr);
            SET_RG_PRESENT (p_info);
          }
          sccp_route_co_msg (p_info) ;
          result = SS7_FAILURE;
        }
      }
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }

      break ;

    case SCCP_N_RESET_REQUEST_EVENT :
#ifdef SCCP_ETSI
      if (COMPARE_ETSI)
      {
        /* 
         * ETSI SCCP does not support Class 3 functionality, so this API 
         * should be rejected 
         */
        result = SS7_FALSE ;
        SCCP_UT_TRACE (("SCCP::UT: Error : Unspecified API\n")) ;
        *p_ecode = ESCCP_UNSPECIFIED_API_FOR_ETSI ;
        break;
      }
#endif

      /* Parse the N-RESET.request API from the User */
      result = sccp_parse_n_reset_request_api (p_info->p_api, p_info) ;
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if (result == SS7_SUCCESS)
        result = sccp_utl_read_ccb (p_info);
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }
      break ;

    case SCCP_N_RESET_RESPONSE_EVENT :
#ifdef SCCP_ETSI
      if (COMPARE_ETSI)
      {
        /*
         * ETSI does not support Class 3 functionality, so this API 
         * should be rejected
         */
        result = SS7_FALSE ;
        SCCP_UT_TRACE (("SCCP::UT: Error : Unspecified API\n")) ;
        *p_ecode = ESCCP_UNSPECIFIED_API_FOR_ETSI ;
        break;
      }
#endif


      /* Parse the N-RESET.response API from the User */
      result = sccp_parse_n_reset_resp_api (p_info->p_api, p_info) ;
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if (result == SS7_SUCCESS)
        /* Read the ccb associated with the connection */
        result = sccp_utl_read_ccb (p_info);
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
      }
      break ;

    case SCCP_N_DATA_REQUEST_EVENT :
      /* Parse the N-DATA.request API from the User */
      result = sccp_parse_n_data_request_api (p_info->p_api, p_info) ;
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if (result == SS7_SUCCESS)
        /* Read the ccb associated with the connection */
        result = sccp_utl_read_ccb (p_info);
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
        /* SPR# 4543 Start */
        /* Increment the Traffic Related Statistics */
        SC_STAT_TRAFFIC_INR_PKT_DROP();
        /* SPR# 4543 End */
      }
      break ;

    case SCCP_N_EXP_DATA_REQUEST_EVENT :
#ifdef SCCP_ETSI
      if (COMPARE_ETSI)
      {
        /* 
         * ETSI SCCP does not support Class 3 functionality, so this API 
         * should be rejected 
         */
        result = SS7_FALSE ;
        SCCP_UT_TRACE (("SCCP::UT: Error : Unspecified API\n")) ;
        *p_ecode = ESCCP_UNSPECIFIED_API_FOR_ETSI ;
        break;
      }
#endif

      /* Parse the N-EXPDATA.request API from the User */
      result = sccp_parse_n_ed_data_request_api (p_info->p_api, p_info) ;
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if (result == SS7_SUCCESS)
      {
        /* Read the ccb associated with the connection */
        result = sccp_utl_read_ccb (p_info);
      }
      else
      {
        /* Error */
        *p_ecode = EAPI_ERROR ;
        /* SPR# 4543 Start */
        /* Increment the Traffic Related Statistics */
        SC_STAT_TRAFFIC_INR_PKT_DROP();
        /* SPR# 4543 End */
      }
      break ;

    case SCCP_CR_EVENT :
      /* Get a free ccb */
      if ((p_ccb = sccp_utl_get_free_ccb ()) != (sccp_ccb_t *)SS7_NULL)
      {
        /* Associate the free cbb with the connection section */
        p_info->p_ccb = p_ccb;
        /* Set the connection state to Idle */
        p_ccb->c_state = SCCP_CONN_IDLE;
      }
      else
      {
        /* No free ccb found, so rrefuse the connection */
        /* build CREF message */
        SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building CREF Message\n")) ;
        p_info->msg_type = CREF_MSG_TYPE;
        p_info->dlr = p_info->slr ;
        p_info->rel_cause = SCCP_RFC_UNQUALIFIED;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(CREF_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/



	/* SPR ATS-ITU: Start fix 
	 * interchange opc and dpc values
	 */
	dpc_tmp = p_info->dpc;
	p_info->dpc = p_info->opc;
   	p_info->opc = dpc_tmp;
	/* SPR ATS-ITU: End fix */

        sccp_route_co_msg (p_info) ;
        result = SS7_FAILURE;
      }

      break ;

    /*
     * The ETSI SCCP doesn't support Class 3 services, so the reset 
     * procedures, expidited data transfer, and flow control mechanism are 
     * not supported in ETSI
     * So if SCCP is functioning as ETSI_SCCP then these messages should be
     * dropped
     */
    case SCCP_RSR_EVENT :
    case SCCP_RSC_EVENT :
    case SCCP_ED_EVENT :
    case SCCP_EA_EVENT :
    case SCCP_DT2_EVENT :
    case SCCP_AK_EVENT :
#ifdef SCCP_ETSI
      if (COMPARE_ETSI)
      {
        /* 
         * ETSI SCCP does not support Class 3 functionality, so these events 
         * should be rejected 
         */
        result = SS7_FALSE ;
        SCCP_UT_TRACE (("SCCP::UT: Error : Unspecified API\n")) ;
        *p_ecode = ESCCP_UNSPECIFIED_API_FOR_ETSI ;
        break;
      }
#endif

    case SCCP_CC_EVENT :
    case SCCP_CREF_EVENT :
    case SCCP_RLSD_EVENT :
    case SCCP_RLC_EVENT :
    case SCCP_DT1_EVENT :
    case SCCP_IT_EVENT :
    case SCCP_ERR_EVENT :
#ifdef SCCP_CONNECTION_ID_CHANGES
      p_info->conn_id = sccp_utl_map_lref_cid_motorola (p_info->dlr) ;
#else
      p_info->conn_id = sccp_utl_map_lref_cid (p_info->dlr) ;
#endif
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      if ((SS7_SUCCESS != sccp_utl_read_ccb (p_info)) ||
		(p_info->p_ccb->c_state == SCCP_CONN_IDLE))	
      {
	/* SPR 1350: Start fix */
	/* coding for Table B-2/Q.714 - unassigned dlr
	 */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
	   	sccp_itu_unassigned_dlr (p_info) ;
	   	result = SS7_FAILURE ;
	}
#endif

	/* coding for Table B-2/T1.112.4 - unassigned dlr
	 */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
	   	error_cause = 
			SCCP_ERRC_LRN_MISMATCH_UNASSIGNED_DLRN ;
	   	sccp_ansi_info_mismatch (p_info, error_cause) ;
	   	result = SS7_FAILURE ;
	}
#endif
	break ;
      }

/* SPR 7052 : Start Fix */
    if ((p_info->p_ccb->p_ss) && (p_info->p_ccb->p_ss->registered))  

        {
            if (!p_info->p_ccb->p_ss->allowed)
              {
		  p_opc = sccp_db_find_sp(p_info->nw_id, p_info->opc);
		  if(p_opc == SS7_NULL)
		  {
                  	RC_TRC (("SCCP::SCOC: Cannot find Point code  %d\n", p_info->opc));
                  	result = SS7_FAILURE;
				break;
		   }
		  p_ss_entry = sccp_db_find_ss(p_opc, p_info->p_ccb->cd_addr.ssn);
		  if(p_ss_entry == SS7_NULL)
		  {
                  	RC_TRC (("SCCP::SCOC: Cannot find Subsystem  %d\n", p_info->p_ccb->cd_addr.ssn));
                  	result = SS7_FAILURE;
				break;
		   }
                  RC_TRC (("SCCP::SCOC: subsytem %d on pc  nw %d unavailable\n",
                                 p_info->p_ccb->p_ss->ssn, p_info->nw_id));
			if(!IS_SS_LOCAL(p_ss_entry))
			{
				p_temp = p_info->p_ss;
				p_info->p_ss = p_info->p_ccb->p_ss;
				sccp_msg_unavail_system(p_info);
				p_info->p_ss = p_temp;
			}
			else
				sccp_send_n_state_ind(p_ss_entry, p_info->p_ccb->p_ss);
			
				
                  result = SS7_FAILURE;
              }
        }
/* SPR 7052 : End Fix */

      /* if connection state is connection pending - outgoing 
       * do not check for slr and opc values 
       */

      if ((p_info->p_ccb->c_state == SCCP_CONN_START) && 
		((p_info->p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING))
	break;


      /* check if slr value is correct */
      if (SS7_SUCCESS != sccp_utl_check_slr (p_info))
      {
	/* coding for Table B-2/Q.714 - incorrect slr 
	 */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
	   	sccp_itu_incorrect_slr (p_info, p_ecode) ;
	   	result = SS7_FAILURE ;
	}
#endif

	/* coding for Table B-2/T1.112.4 
	 */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
	   	error_cause = 
			SCCP_ERRC_LRN_MISMATCH_INCONSISTENT_SLRN ;
	   	sccp_ansi_info_mismatch (p_info, error_cause) ;
	   	result = SS7_FAILURE ;
	}
#endif
        /* free incoming CCB */
/*** SPR No 5506 and 5508 Fix Start
        sccp_free_ccb (p_info->p_ccb) ;
SPR SS06 5508 fix ends***/
	break ;
      }	

      /* check opc value of message received */
      if (SS7_SUCCESS != sccp_utl_check_opc (p_info))
      {
	/* coding for Table B-2/Q.714 - incorrect opc
	 */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
	  	sccp_itu_incorrect_opc (p_info) ;
	  	result = SS7_FAILURE ;
	}
#endif
	/* coding for Table B-2/T1.112.4 
 	 */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
	   	error_cause = SCCP_ERRC_POINT_CODE_MISMATCH ;
	   	sccp_ansi_info_mismatch (p_info, error_cause) ;
	   	result = SS7_FAILURE ;
	}
#endif
	/* SPR # 5906 Fix Starts */
	/* SPR # 5907 Fix Starts */

        /* free incoming CCB */
        /* sccp_free_ccb (p_info->p_ccb) ; */

	/* SPR # 5906 Fix Ends */
	/* SPR # 5907 Fix Ends */
      }
      /* SPR 1350: End fix */
   
  /* spr 5507 fix starts  */
  	/* SPR 7052 : Start Fix */
		/* Moved code for SPR 5507 fix to above */ 
  	/* SPR 7052 : End Fix */
   /* SPR 5507 fix ends */
      break ;

    case SCCP_ROUTE_FAIL_EVENT :

    if ((MTP3_UP_TRANSFER_INDICATION == GET_API_ID(p_info->p_api)) &&
         (!(IS_RELAY_MSG(p_info))))
	{
    	/* The message is coming from the peer for a local subsystem */

      	/* SPR 1501: CR mesg will not have a DLR */
		if (p_info->msg_type == CR_MSG_TYPE)
		{

		/** SPR 9165 Start Fix **/
#ifdef SCCP_MT_SAFE

		/* Dont mark the conn id as busy for route fail events arising
		 * in SCRC as p_info doesnt contain dlr or conn_id for CR
		 */	 

		if((p_info->rel_cause != SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE)&&
		   (p_info->rel_cause != SCCP_RFC_UNEQUIPPED_USER) &&
		   (p_info->rel_cause != SCCP_RFC_SUBSYSTEM_FAILURE) &&
		   (p_info->rel_cause != SCCP_RFC_HOP_COUNTER_VIOLATION))
		{
				ADJUST_CONN_ID_BUSY_VAL
		}
#endif
		/** SPR 9165 End Fix **/

			/** SPR # 6367 Fix Start **/
			if (p_info->route_failure_flag)
			{
				SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
				("SCCP::CO: Multiple Route Fail messages related to "
				"Unknown connection - Ignoring !!\n")) ;

        		result = SS7_FAILURE;
				break;
			}
			
			p_info->route_failure_flag = SS7_TRUE;
			/** SPR # 6367 Fix End **/
			
			/* build CREF message 
            */

            SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
                  ("SCCP::CO:Building CREF Message\n")) ;
            p_info->msg_type = CREF_MSG_TYPE;
            p_info->dlr = p_info->slr ;
            p_info->nw_id = DEFAULT_NW_ID ;
			/* SPR 10330 - Fix Start */
            /*p_info->rel_cause = SCCP_RFC_END_USER_FAILURE;*/
			/* SPR 10330 - Fix End   */
            dpc_tmp = p_info->dpc;
            p_info->dpc = p_info->opc ;
            p_info->opc = dpc_tmp;
/** SPR Fix 7410 start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        	if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  	{
			p_info->importance = sccp_get_min_message_priority(CREF_MSG_TYPE);
        	}
#endif
/** SPR Fix 7410 End **/
            sccp_route_co_msg (p_info) ;
            result = SS7_FAILURE;
            break; 
		}
		/* SPR 1501: End fix */
 		else
		{
#ifdef SCCP_CONNECTION_ID_CHANGES
          	p_info->conn_id = sccp_utl_map_lref_cid_motorola (p_info->dlr) ;
#else
          	p_info->conn_id = sccp_utl_map_lref_cid (p_info->dlr) ;
#endif
#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif

			/* SPR # 6367 Fix Start */
			if (SS7_SUCCESS != sccp_utl_read_ccb (p_info))
			{
        		/* 
         		* If there is no ccb associated with the connection, then error 
         		* message should be sent to the peer
         		*/

				if (p_info->route_failure_flag)
				{
					SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
					("SCCP::CO: Multiple Route Fail messages related to "
					"Unknown connection - Ignoring !!\n")) ;

        			result = SS7_FAILURE;
					break;
				}
			
				p_info->route_failure_flag = SS7_TRUE;
			
        		/* build ERR message */
        		SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        		("SCCP::CO:Building CREF Message\n")) ;
        		p_info->msg_type = ERR_MSG_TYPE;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 end **/
        		p_info->dlr = p_info->slr ;
				p_info->error_cause = SCCP_ERRC_LRN_MISMATCH_UNASSIGNED_DLRN;
        		sccp_route_co_msg (p_info) ;
        		result = SS7_FAILURE;
      		}
			/* SPR # 6367 Fix End */
		}
      }
      else
      {
        	/* The message is coming from SCOC */

/* SPR 8986 - Fix Start */
#ifdef SCCP_CONNECTION_ID_CHANGES
        	p_info->conn_id = sccp_utl_map_lref_cid_motorola (p_info->slr) ;
#else
/* SPR 8986 - Fix End  */
        	p_info->conn_id = sccp_utl_map_lref_cid (p_info->slr) ;
/* SPR 8986 - Fix Start */
#endif
/* SPR 8986 - Fix End  */

#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      }

	/* SPR # 6367 Fix Start 
 	** This code has been moved above. It will be executed only in case the 
	** message is received from MTP3 interface
	*/
#if 0
      if (SS7_SUCCESS != sccp_utl_read_ccb (p_info))
      {
        /* 
         * If there is no ccb associated with the connection, then error 
         * message should be sent to the peer
         */
        /* build ERR message */
        SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building CREF Message\n")) ;
        p_info->msg_type = CREF_MSG_TYPE;
        p_info->dlr = p_info->slr ;
        sccp_route_co_msg (p_info) ;
        result = SS7_FAILURE;
      }
#endif
	/* SPR # 6367 Fix Ent  */
      break ;

    case SCCP_T_CONNEST_TIME_OUT :
    case SCCP_T_IAR_TIME_OUT :
    case SCCP_T_IAS_TIME_OUT :
    case SCCP_T_REL_TIME_OUT :
    case SCCP_T_REPREL_TIME_OUT :
    case SCCP_T_INT_TIME_OUT :
    case SCCP_T_GAURD_TIME_OUT :
    case SCCP_T_RESET_TIME_OUT :
    case SCCP_T_REASSEMBLY_TIME_OUT :
    case SCCP_T_FREEZE_TIME_OUT :
      /* The time out events */
      p_timer_buf = p_info->p_api + API_HEADER_LEN ;
      p_timer_buf++ ;
      p_info->conn_id = *p_timer_buf ; 
      p_timer_buf++ ;
      p_info->conn_id |= (*p_timer_buf << 8) & 0xff00 ; 
      p_timer_buf++ ;
#ifdef SCCP_CONNECTION_ID_CHANGES
      p_info->conn_id |= (*p_timer_buf << 16) & 0xff0000 ; 
      p_timer_buf++ ;
      p_info->conn_id |= (*p_timer_buf << 24) & 0xff000000 ; 
      p_timer_buf++ ;
#endif

#ifdef SCCP_MT_SAFE
       ADJUST_CONN_ID_BUSY_VAL
#endif
      	
     /* 
     ** SPR # 6368 Fix Start
     ** The following case occurs only in case of spurious timeouts; It this
	 ** case, SLR value will most likely contain some junk value and so it is 
     ** not correct to send ERR message to the peer. 
     */
      if (SS7_SUCCESS != sccp_utl_read_ccb (p_info))
      {
#if 0
        /* 
         * If there is no ccb associated with the connection, then error 
         * message should be sent to the peer
         */
        /* build ERR message */
        SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
        p_info->msg_type = ERR_MSG_TYPE;
        p_info->dlr = p_info->slr ;
        p_info->rel_cause = SCCP_RFC_UNQUALIFIED;
        sccp_route_co_msg (p_info) ;
#endif
        result = SS7_FAILURE;
      }
      /* SPR # 6368 Fix End */

      break ;

    default :
#ifdef SCCP_MT_SAFE
	if (p_info->conn_id < MAX_SCCP_CO_CONNECTIONS)
	{
		ss7_sem_lock (&conn_id_arr_sync_sem);
	  	conn_id_busy_arr [p_info->conn_id]--;
		ss7_sem_unlock (&conn_id_arr_sync_sem);
	}
#endif
      return (SS7_FAILURE) ;
  }

  if (result == SS7_SUCCESS)
  {
    /* call the state event functions for the SCCP */
    result = sccp_call_state_event_function (p_info, p_ecode) ;
  }

  if (result != SS7_SUCCESS)
  {
    /* generate appropriate error */
    SCCP_ERR (*p_ecode, STACK_PROTOCOL_ERROR, MAJOR_ERROR) ;
  }

#ifdef SCCP_MT_SAFE
	/* SPR# 9165: Start Fix */

	/* 	Mark conn id free only when :
	 * 	1. The event wasnt a conn request from user or peer 
	 * 	2. Event processed was Route fail event NOT generated by -
	 *    	2.1 GT translation failure in CR message processing or
	 *    	2.2 Unequipped user error during CR msg processing. 
	 */

	switch(event_type)
	{
		case SCCP_N_CONNECT_REQUEST_EVENT:
		case SCCP_REQUEST_TYPE_1_EVENT :	/* SPR # 11180 Fix */
		case SCCP_REQUEST_TYPE_2_EVENT :
		case SCCP_CR_EVENT:
		break;

		default:

		switch(p_info->event)
		{
			case SCCP_ROUTE_FAIL_EVENT:

			if((p_info->msg_type == CREF_MSG_TYPE) &&
				(p_info->rel_cause == SCCP_RFC_END_USER_FAILURE))
								break;

			default:
				if (p_info->conn_id < MAX_SCCP_CO_CONNECTIONS)
				{
					ss7_sem_lock (&conn_id_arr_sync_sem);
	  				conn_id_busy_arr [p_info->conn_id]--;
					ss7_sem_unlock (&conn_id_arr_sync_sem);
				}
		}			
	}

	/* SPR# 9165: End Fix */
#endif
  return (result) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    The State Event function
**
******************************************************************************
**
**  DESCRIPTION :
**    This function calls the appropriate state event function after looking
**    up the function pointer table
**
*****************************************************************************/

return_t
sccp_call_state_event_function
#ifdef ANSI_PROTO
  (msg_info_t      *p_info,
   error_t         *p_ecode)
#else
  (p_info, p_ecode)
   msg_info_t      *p_info ;
   error_t         *p_ecode ;
#endif
{
  return_t result ;
  U8bit state = p_info->p_ccb->c_state ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_call_state_event_function\n")) ;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Got Event[%s] in State[%s]\n",
    sccp_co_event_name [p_info->event], sccp_co_state_string [state])) ;
    
  /* call the function from the function pointer table */
  result = (* sccp_co_func_ptr_table [state][p_info->event])(p_info, p_ecode) ;  
  return (result) ; 
}

/* SPR 1350: Start fix */
/*****************************************************************************
**
**  FUNCTION :
**    The function to handle messages with unassigned dlr values.
**
******************************************************************************
**
**  DESCRIPTION :
**    The following actions are taken on receiving messages with an unassigned
**    destination local reference number: 
**
**    Received CC, RSC or RSR message: Send ERR message 
**    Received RLSD message 	     : Send RLC message
**    Received any other message     : Discard message
**
*****************************************************************************/

void
sccp_itu_unassigned_dlr
#ifdef ANSI_PROTO
  (msg_info_t	*p_info)
#else
  (p_info)
  msg_info_t	*p_info;
#endif   
{
   pc_t    dpc_tmp;
   U32bit  slr_tmp;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_itu_unassigned_dlr\n")) ;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Got Event[%s] with unassigned 'dlr' value\n",
    sccp_co_event_name [p_info->event])) ;

   switch (p_info->event)  
   {
    	case SCCP_CC_EVENT:
    	case SCCP_RSR_EVENT:
    	case SCCP_RSC_EVENT:
  
           /* build ERR message */

           SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
           ("SCCP::CO:Building ERR Message\n"));

           p_info->msg_type = ERR_MSG_TYPE;
           p_info->dlr = p_info->slr;
    	   p_info->error_cause = SCCP_ERRC_LRN_MISMATCH_UNASSIGNED_DLRN;

   	   /* fill opc and dpc values from the received message */
	   dpc_tmp = p_info->dpc;
	   p_info->dpc = p_info->opc;
	   p_info->opc = dpc_tmp;
	   CLR_CD_PRESENT(p_info);
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/

	   /* forward mesg to translate and route function of SCRC */
           sccp_route_co_msg (p_info);
	   return;

    	case SCCP_RLSD_EVENT :
		
  	   /* build RLC message */

  	   SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
       	   ("SCCP::CO:Building RLC Message\n")) ;
  	   p_info->msg_type = RLC_MSG_TYPE ;
 
   	   /* fill slr and dlr values from the received message */
  	   slr_tmp = p_info->slr;
  	   p_info->slr = p_info->dlr;
  	   p_info->dlr = slr_tmp;
 
   	   /* fill opc and dpc values from the received message */
  	   dpc_tmp = p_info->dpc;
  	   p_info->dpc = p_info->opc;
  	   p_info->opc = dpc_tmp;
 
  	   /* forward it to the translate and route function of SCRC */
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(RLC_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/
  	   sccp_route_co_msg (p_info) ;
	   return;
	
    	default: 

	   /* discard message */
	   sccp_discard_message (p_info);
	   return;
   }
}


/*****************************************************************************
**
**  FUNCTION :
**    The function to handle messages with inconsistent slr values.
**
******************************************************************************
**
**  DESCRIPTION :
**    The following actions are taken on receiving a message with source 
**    local reference number not equal to the one stored locally
**
**    Received RLSD, RSR or RSC message: Send ERR message 
**    Received IT message 	       : Send first RLSD message containing 
**					   information from received message
**				         Send second RLSD message containing
**					   information stored locally.
**    Received RLC message     	       : Discard message
**
*****************************************************************************/

void 
sccp_itu_incorrect_slr
#ifdef ANSI_PROTO
  (msg_info_t	*p_info,
   error_t         *p_ecode)
#else
  (p_info, p_ecode)
   msg_info_t      *p_info ;
   error_t         *p_ecode ;
#endif
{
   pc_t 	dpc_tmp;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_itu_incorrect_slr\n")) ;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Got Event[%s] with incorrect 'slr' value\n",
    sccp_co_event_name [p_info->event])) ;

   switch (p_info->event)
   {
    	case SCCP_RLSD_EVENT:
    	case SCCP_RSR_EVENT:
    	case SCCP_RSC_EVENT:
  
           /* build ERR message */

           SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
           ("SCCP::CO:Building ERR Message\n"));

           p_info->msg_type = ERR_MSG_TYPE;
           p_info->dlr = p_info->slr;
    	   p_info->error_cause = SCCP_ERRC_LRN_MISMATCH_INCONSISTENT_SLRN;

   	   /* fill opc and dpc values from the received message */
	   dpc_tmp = p_info->dpc;
	   p_info->dpc = p_info->opc;
	   p_info->opc = dpc_tmp;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 end **/

	   /* forward mesg to translate and route function of SCRC */
           sccp_route_co_msg (p_info);
	   return;

    	case SCCP_IT_EVENT:

	   sccp_itu_incorrect_slr_it (p_info, p_ecode);
	   return;

    	case SCCP_RLC_EVENT:

	   /* discard message */
	   sccp_discard_message (p_info);
	   return;

    	default:

	   /* not applicable */
	   return;
   }	  

}

/*****************************************************************************
**
**  FUNCTION :
**    The function to handle messages with incorrect opc values.
**
******************************************************************************
**
**  DESCRIPTION :
**    The following actions are taken on receiving a message with originating
**    point code value not equal to the PC stored locally
**
**    Received RLSD, RSR or RSC message		  : Send ERR message 
**    Received RLC, DT1, DT2, AK, ED, EA, ERR, IT : discard message
**
*****************************************************************************/

void 
sccp_itu_incorrect_opc
#ifdef ANSI_PROTO
  (msg_info_t	*p_info)
#else
  (p_info)
  msg_info_t	*p_info;
#endif   
{
   pc_t    dpc_tmp;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_itu_incorrect_opc\n")) ;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Got Event[%s] with incorrect 'opc' value\n",
    sccp_co_event_name [p_info->event])) ;

   switch (p_info->event)
   {
    	case SCCP_RLSD_EVENT:
    	case SCCP_RSR_EVENT:
    	case SCCP_RSC_EVENT:
		
           /* build ERR message */

           SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
           ("SCCP::CO:Building ERR Message\n"));

           p_info->msg_type = ERR_MSG_TYPE;
           p_info->dlr = p_info->slr;
    	   p_info->error_cause = SCCP_ERRC_POINT_CODE_MISMATCH;

   	   /* fill opc and dpc values from the received message */
	   dpc_tmp = p_info->dpc;
	   p_info->dpc = p_info->opc;
	   p_info->opc = dpc_tmp;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 end **/

	   /* forward mesg to translate and route function of SCRC */
           sccp_route_co_msg (p_info);
	   return;

 	case SCCP_CR_EVENT:
 	case SCCP_CC_EVENT:
 	case SCCP_CREF_EVENT:

	   /* not applicable */
	   return;
	
  	default:

	   /* discard message */
	   sccp_discard_message (p_info);
	   return;
   }
}
		
/*****************************************************************************
**
**  FUNCTION :
**    The function to handle messages containing mismatch information of the
**    following types:
**    - unassigned dlr
**    - incorrect opc value
**    - inconsistent slr value
**
******************************************************************************
**
**  DESCRIPTION :
**    The following actions are taken on receiving a message with:
**      - unassigned destination local reference number, or
**      - originating point code not equal to the remote PC, or 
**      - source local reference number not equal to the one stored locally
**
**    Received RLSD, RSR or RSC message		 : Send ERR message 
**    Received RLC, DT1, DT2, AK, ED, EA, ERR, IT: discard message
**
*****************************************************************************/

void 
sccp_ansi_info_mismatch
#ifdef ANSI_PROTO
  (msg_info_t	*p_info,
   U8bit	error_cause)
#else
  (p_info, error_cause)
  msg_info_t	*p_info;
  U8bit		error_cause;
#endif   
{
   pc_t    dpc_tmp;
   U32bit  slr_tmp;
   /* SPR XXXXX - Fix Start */
   /*error_t *p_ecode = SS7_NULL ;*/
   /* SPR XXXXX - Fix End */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_ansi_info_mismatch\n")) ;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Got Event[%s] with mismatch information\n",
    sccp_co_event_name [p_info->event])) ;

   switch (p_info->event)
   {
     	case SCCP_RLSD_EVENT:

  	   /* build RLC message */

  	   SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
       	   ("SCCP::CO:Building RLC Message\n")) ;
  	   p_info->msg_type = RLC_MSG_TYPE ;
 
   	   /* fill slr and dlr values from the received message */
  	   slr_tmp = p_info->slr;
  	   p_info->slr = p_info->dlr;
  	   p_info->dlr = slr_tmp;
 
   	   /* fill opc and dpc values from the received message */
  	   dpc_tmp = p_info->dpc;
  	   p_info->dpc = p_info->opc;
  	   p_info->opc = dpc_tmp;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(RLC_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/
 
  	   /* forward it to the translate and route function of SCRC */
  	   sccp_route_co_msg (p_info) ;
	   return;

    	case SCCP_RLC_EVENT:

	   /* discard message */
	   sccp_discard_message (p_info);
	   return;

	case SCCP_IT_EVENT:

		/** SPR XXXXX - Fix Start **/
		/** Table B-2/T1.112.4 **/
#if 0
	   if (error_cause == SCCP_ERRC_LRN_MISMATCH_INCONSISTENT_SLRN)
	   {
		/* Release connection */
           	sccp_itu_incorrect_slr_it (p_info, p_ecode);
		return;
	   }
	   else
	   {
#endif
		/** SPR XXXXX - Fix End **/
           	/* build ERR message */

           	SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
           	("SCCP::CO:Building ERR Message\n"));

           	p_info->msg_type = ERR_MSG_TYPE;
           	p_info->dlr = p_info->slr;
    	   	p_info->error_cause = error_cause;

   	   	/* fill opc and dpc values from the received message */
	   	dpc_tmp = p_info->dpc;
	   	p_info->dpc = p_info->opc;
	   	p_info->opc = dpc_tmp;
    	   	CLR_CD_PRESENT (p_info);
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/

	   	/* forward mesg to translate and route function of SCRC */
           	sccp_route_co_msg (p_info);
	   	return;
/** SPR XXXXX - Fix Start **/
#if 0
	   }
#endif
/** SPR XXXXX - Fix End **/

	default:
	
	   if (!is_slr_present (p_info->event))
	   {
	   	/* discard message */
	   	sccp_discard_message (p_info);
	   	return;
	   }
	   else
	   {
           	/* build ERR message */

           	SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
           	("SCCP::CO:Building ERR Message\n"));

           	p_info->msg_type = ERR_MSG_TYPE;
           	p_info->dlr = p_info->slr;
    	   	p_info->error_cause = error_cause;

   	   	/* fill opc and dpc values from the received message */
	   	dpc_tmp = p_info->dpc;
	   	p_info->dpc = p_info->opc;
	   	p_info->opc = dpc_tmp;
    	   	CLR_CD_PRESENT (p_info);
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/

	   	/* forward mesg to translate and route function of SCRC */
           	sccp_route_co_msg (p_info);
	   	return;
	   }
   }
}
	

/*****************************************************************************
**
**  FUNCTION :
**    The function to handle IT messages with inconsistent slr values.
**
******************************************************************************
**
**  DESCRIPTION :
**    The following actions are taken on receiving an IT  message with source
**    local reference number not equal to the one stored locally
**
**    o send first RLSD message containing information from received message
**    o send second RLSD message containing information stored locally.
**    o stop T_inact_send and T_inact_rec timers on the conn section
**    o start T_rel timer
**    o change state to CONN_CLOSING
**    o if association involved
**    	o remove the association
**  	o stop T_inact_send and T_inact_rec timers on associated section
**  	o start T_rel 
**	o send RLSD message on associated section
**	o change state to CONN_CLOSING
**    o else
**	o send N_DISCONNECT indication to user
**
*****************************************************************************/
 
void
sccp_itu_incorrect_slr_it
#ifdef ANSI_PROTO
  (msg_info_t   *p_info,
   error_t         *p_ecode)
#else
  (p_info, p_ecode)
   msg_info_t      *p_info ;
   error_t         *p_ecode ;
#endif
{
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;
  pc_t 		dpc_tmp;
  U32bit 	slr_tmp;
  return_t      result ;

   if ((p_info->p_ccb->c_state != SCCP_CONN_START) && 
	(p_info->p_ccb->c_state != SCCP_CONN_ESTABLISHED))
   {
  	/* discard the received message */
  	sccp_discard_message (p_info) ;
	return;
   }

   /* Build RLSD message based on information in the received message */

   SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
         ("SCCP::CO: Building RLSD Message\n"));

   p_info->msg_type = RLSD_MSG_TYPE ;
   p_info->rel_cause = SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA;

   /* fill opc and dpc values from the received message */
   dpc_tmp = p_info->dpc;
   p_info->dpc = p_info->opc;
   p_info->opc = dpc_tmp;
	   	
   /* fill slr and dlr values from the received message */
   slr_tmp = p_info->slr;
   p_info->slr = p_info->dlr;
   p_info->dlr = slr_tmp;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(RLSD_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/

  /* forward mesg to translate and route function of SCRC */
   sccp_route_co_msg (p_info) ;

  /* get the connection block */
  p_ccb = p_info->p_ccb;
 
  /* stop T_inact_send and T_inact_rec timer */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
     /* Error */
  }
 
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
     /* Error */
  }

  /* start T_rel timer */
  result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* Build RLSD message based on information stored locally */

  SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
             ("SCCP::CO:Building RLSD Message\n"));

  /* SPR # 2579 Fix Start */
  /* change state to SCCP_CONN_CLOSING */
  sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
  /* SPR # 2579 Fix End */

  p_info->msg_type = RLSD_MSG_TYPE ;
  p_info->rel_cause = SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;

/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(RLSD_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 End **/
  /* forward mesg to translate and route function of SCRC */
  sccp_route_co_msg (p_info) ;

 
  /* if association present */

  if (IS_COUPLING_PRESENT (p_ccb))
  {
    /* get the associated connection control block */
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
 
    /* remove the association */
    sccp_remove_association (p_ccb, p_coupled_ccb) ;
 
    /* stop T_inact_rec and T_inact_send timers */
    result = sccp_stop_co_timer (p_coupled_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
 
    result = sccp_stop_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
 
    /* start T_rel timer */
    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_REL_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
 
    /*
     * build RLSD message and forward it to route and translate
     * functionality of SCRC
     */

	/* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSING */
    sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
	/* SPR # 2579 Fix End */

    p_info->msg_type = RLSD_MSG_TYPE ;
/** SPR Fix 7410 Start **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
     	  {
		p_info->importance = sccp_get_min_message_priority(RLSD_MSG_TYPE);
        }
#endif
/** SPR Fix 7410 end **/
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
 
    sccp_route_co_msg (p_info) ;

  }
  else
  {
  p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
    /* give N-DISCONNECT.ind to the user */
    sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
  }
}


/* SPR 1350: End fix */
#ifdef DISTRIBUTED_SCCP
/*****************************************************************************
**
**  FUNCTION :
**    The function sends Disconnect request to mates when a CCB is not found
**
******************************************************************************
**
**  DESCRIPTION :
**	This function sends N_DISCONNECT request to all other mate instances. 
**
*****************************************************************************/
return_t
dsccp_build_and_send_disc_req_to_mate
#ifdef ANSI_PROTO
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api,p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
	U8bit *p_elem;
	U16bit api_len;
	U16bit len;
	/* SPR 9302 - Fix Start */
	/*error_t ecode;*/
	/* SPR 9302 - Fix End   */
	return_t ret_val;
	
	len = GET_API_LEN(p_api);
	api_len = len + 7;

	p_buffer = (U8bit *)sccp_malloc(api_len);
	p_elem = p_buffer + API_HEADER_LEN;
	sccp_fill_api_header(p_buffer, DSCCP_MATE_API, 3, api_len);
	*p_elem++ = DSCCP_API_CAT_SCOC;
	*p_elem++ = DSCCP_API_CMD_SCOC_DISC_REQ;
	sccp_memcpy(p_elem, p_api,len);	
	ret_val = dsccp_broadcast_to_mates(p_buffer, api_len, p_ecode);
	return ret_val;
}
#endif /* End of DISTRIBUTED_SCCP */	


#else

/*****************************************************************************
**
**  FUNCTION :
**    The function to handle IT messages with inconsistent slr values.
**
******************************************************************************
**
**  DESCRIPTION :
**	This function definition is required as BCC reports error if the 
** source file is empty after preprocessing. This definition enables compilation
** without SCCP_INCLUDE_CO_SERVICE flag using BCC.
**
*****************************************************************************/

return_t 
sccp_co_dummy
#ifdef ANSI_PROTO
  (void)
#else
  ()
#endif
{
	return SS7_SUCCESS;
}

#endif /* End of SCCP_INCLUDE_CO_SERVICE */
