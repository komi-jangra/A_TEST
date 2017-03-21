/*****************************************************************************
**
**  FILE :
**    State Machine Functions for the Connection ESTABLISHED state of the 
**    connection
**
******************************************************************************
**
**  FILENAME :
**    sc_estab.c
**
**  DESCRIPTION :
**    This file contains all the functions handling the events for the 
**    ESTABLISHED state of the SCCP connections.
**
**  Date    Name        Reference    Reason
**  _________________________________________________________________________
**  07July2003 Hitesh sharma    Fixed 12094 CSR No - 637938 Updated Comments
**  25Jan2003 Suyash Tripathi   Fixed SPR #11109,11112,10879,11104,11243
**  02Aug2002 Prateek Bidwalkar   Fixed SPR # 9221
**  20Jun2002 Suyash Tripathi   Fixed SPR #8985 
**  04mar2002 Sachin Bhatia	Fixed SPR #8552 
**  10Aug2001 Aman Kapoor	SPR #5926 Added a check for class 3
**  26Sep2001 Ramu Kandula         Fixed SPR #6286
**  25May2001 Rajesh Mehta         changed conn_id to U32BIT AND corr_id to U16
**                                 in case SCCP_CONNECTION_ID_CHANGES is defined        
**  22Oct2000 Hemlata Baudhwar SPR #4584  Added a check in sccp_conn_estab_t_iar_tmout 
**                                        and  sccp_conn_estab_t_ias_tmout   
**  16Oct2000 Ramu Kandula     SPR #4483   Replaced sc_opt.seg_size with
**                                           SCCP_MAX_CO_SEG_SIZE
**  19Jul'00  Ramu Kandula           Fixed SPR 4185
**  07Jul'00  Ramu Kandula           Fixed SPR 4050
**  09Jun'00  Ramu Kandula           Fixed SPR 2579 - Change state before
**                                   sending message to SCRC 
**  10Aug'99  Sudipta Pattar		 Fixed SPR 1776 
**  10Aug'99  Sudipta Pattar		 Fixed SPR 1775 
**  10Aug'99  Sudipta Pattar		 Fixed SPR 1774 
**  10Aug'99  Sudipta Pattar		 Fixed SPR 1773 
**  25Jun'99  Sudipta Pattar		 Fixed SPR 1686 
**  29Apr'99  Sudipta Pattar		 Fixed SPR 1361 
**  29Apr'99  Sudipta Pattar		 Fixed SPR 1338
**  15Feb'99  Sudipta Pattar         Fixed SPR 1327 
**  07Feb'99  Sudipta Pattar         Added event alarms
**  08Jul'98  Praneet Khare    HSS:20800011  Original
**  04Jul'01  Pawanish Modi                  SPR 5510 Fix
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"

#ifdef SCCP_INCLUDE_CO_SERVICE

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-DISCONNECT.req from the User in the ESTABLISHED state of 
**    SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-DISCONNECT.req from
**    the user in the connection established phase.
**    When invoked it does the following :
**    
**    o stop T_inact_send and T_inact_rec timer
**    o build RLSD message and forward it to the routing and translation 
**      functionality of SCRC
**    o start T_rel timer
**    o change state to SCCP_CONN_CLOSING
**
*****************************************************************************/

return_t
sccp_conn_estab_n_disc_req
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_n_disc_req\n")) ;

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

  /* 
   * build RLSD message and forward it to the routing and translation 
   * functionality of SCRC
   */

  /* SPR # 2579 Fix Start */
  /* change state to SCCP_CONN_CLOSING */
  sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
  /* SPR # 2579 Fix End */

  p_info->msg_type = RLSD_MSG_TYPE ;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  sccp_route_co_msg (p_info) ;

  /* start T_rel timer */
  result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }


  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-RESET.req from the User in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-RESET.req from
**    the user in the connection established phase.
**    When invoked it does the following :
**
**    o build RSR message and forward it to the routing and translation 
**      functionality of SCRC
**    o start T_reset timer
**    o restart T_inact_send timer
**    o reset variables and discard all the queued and unacked messages
**    o send event alarm to SM
**    o change state to SCCP_CONN_RESET and substate to SCCP_OUTGOING
**
*****************************************************************************/

return_t
sccp_conn_estab_n_reset_req
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  conn_entry_t  conn ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_n_reset_req\n")) ;

  p_ccb = p_info->p_ccb;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    /* SPR 1775: Invoke an Error */
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO: Error - Reset request for class 2 conection\n")) ;

    SC_P_ERR (ESCCP_SERVICE_CLASS_MISMATCH);
    /* SPR 1775: End */

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* 
   * build RSR message and forward it to the routing and translation 
   * functionality of SCRC
   */

  /* SPR # 2579 Fix Start */
  /* change state to SCCP_CONN_RESET and substate to SCCP_OUTGOING */
  sccp_change_state (p_ccb, SCCP_CONN_RESET, SCCP_OUTGOING) ;
  /* SPR # 2579 Fix End */

  p_info->msg_type = RSR_MSG_TYPE ;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;


  /* start T_reset timer */
  result = sccp_start_co_timer (p_ccb, SCCP_T_RESET_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* restart T_inact_send timer */
  result = sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
 	(void)sccp_stop_co_timer (p_ccb,SCCP_T_IAS_TIMER, p_ecode) ;
	 return result;
    /* Error */
  }

  /* reset variables and discard all the queued and unacked messages */
  sccp_reset_variables (p_ccb) ;

  sccp_route_co_msg (p_info) ;

  /* send alarm to sm */
  conn.conn_id = p_info->conn_id;    
  conn.reset_cause = p_info->reset_cause;
  conn.originator = sccp_utl_get_rsr_originator(p_info->reset_cause);
  

  SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, CONN_RESET, SS7_NULL, SS7_NULL, &conn);

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-DATA.req from the User in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-DATA.req from
**    the user in the connection established phase.
**    When invoked it does the following :
**
**
*****************************************************************************/

return_t
sccp_conn_estab_n_data_req
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t *p_ccb;
  msg_info_t info;
  U16bit full_data_len, transmitted_bytes;
  U8bit *p_buf;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_n_data_req\n")) ;

  info.flag = 0;
  p_ccb = p_info->p_ccb;

  sccp_utl_fill_nw_info (p_info, p_ccb);

  if (p_ccb->proto_class == PROTOCOL_CLASS_2)
  {
    p_info->msg_type = DT1_MSG_TYPE;

    full_data_len = p_info->data.len;
    p_buf = p_info->data.p;
    transmitted_bytes = 0;
    /* check if we need to resegment the message */
    do
    {
      if ((full_data_len - transmitted_bytes) > SCCP_MAX_CO_SEG_SIZE)
      {
        p_info->data.len = SCCP_MAX_CO_SEG_SIZE;
        SET_M_BIT_DT1 (p_info);
      }
      else
      {
        p_info->data.len = full_data_len - transmitted_bytes;
        CLR_M_BIT_DT1 (p_info);
      }

      p_info->data.p = p_buf + transmitted_bytes;
      transmitted_bytes += p_info->data.len;
      sccp_route_co_msg (p_info);
	  SC_STAT_Q752_INR_ORIG_MSG_DT1 (p_ccb->p_ss->ssn) ;

      /* restart T_inact_send timer */
      if(sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) !=
                  SS7_SUCCESS)
      {
          /* Error */
      }

    }while (full_data_len != transmitted_bytes);
  }

  if (p_ccb->proto_class == PROTOCOL_CLASS_3)
  {
  /* Added to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

     if (sccp_utl_add_to_tx_queue (p_info, p_ccb)== SS7_FAILURE)
    {
      /* congestion present. keep the message in hold queue and
         reduce the credit to 0.
      */
      return (SS7_FAILURE);
         
    }
    info.p_api = p_info->p_api;
    sccp_utl_fwd_dt2 (&info, p_ccb);
#endif     /* #ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE */
  }
  return (SS7_SUCCESS);
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-EXPEDITED-DATA.req from the User in the ESTABLISHED state 
**    of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-EXPEDITED-DATA.req 
**    from the user in the connection established phase.  
**    When invoked it does the following :
**
**
*****************************************************************************/

return_t
sccp_conn_estab_n_expdata_req
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t    *p_ccb ;
  msg_info_t  	info;


  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_n_expdata_req\n")) ;

  p_ccb = p_info->p_ccb;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    /* SPR 1770: Invoke error handler */
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO: Error - Exp. data request for class 2 conection\n")) ;

    SC_P_ERR (ESCCP_SERVICE_CLASS_MISMATCH);
    /* SPR 1770: End */

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* SPR 1773: Start */
  /* Queue up the ED message */
  if (sccp_utl_add_to_ed_tx_queue(p_info, p_ccb) == SS7_FAILURE)
  {
	/* Error */
  }

  if (!(SCCP_IS_UNACK_ED (p_ccb)))
  {
	/* send ED message */
	info.p_api = p_info->p_api;
	sccp_utl_fwd_ed (&info, p_ccb, p_ecode);
  }

#if 0
  if (SCCP_IS_UNACK_ED (p_ccb))
  {
    /* Queue up the ED message */
    if (sccp_utl_add_to_ed_tx_queue(p_info, p_ccb) == SS7_FAILURE)
    {
	/* Error */
    }
  }
  else
  {
    /* restart T_inact_send */
    result = sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
    p_info->msg_type = ED_MSG_TYPE ;
    sccp_route_co_msg (p_info) ;
	SC_STAT_Q752_INR_ORIG_MSG_ED (p_ccb->p_ss->ssn) ;
    SCCP_SET_UNACK_ED (p_ccb) ;
  }
#endif
  /* SPR 1773: End */

  return (SS7_SUCCESS) ;
}
/* Fix for SPR No : 12094 , CSR No : 1 - 637938  Starts*/

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RLSD from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RLSD from
**    the peer in the connection established phase.
**    When invoked it does the following :
**
**    o if association involved
**    o then
**      o get the associated connection control block.
**      o stop T_inact_rec and T_inact_send timers.
**      o start T_rel timer.
**      o change state to SCCP_CONN_CLOSING.
**      o build RLSD message and forward it to route and translate
**        functionality of SCRC.
**      o remove the association.
**    o else
**      o give N-DISCONNECT.ind to the user.
**      o
**    o stop T_inact_rec and T_inact_send timers.
**    o build RLC message and forward it to route and translate
**      functionality of SCRC.
**    o change state to SCCP_CONN_CLOSED.
**    o release resources and the local reference.
**    o start T_freze timer.
**
*****************************************************************************/
/* Fix for SPR No : 12094 , CSR No : 1 - 637938  Ends */

return_t
sccp_conn_estab_rlsd
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_rlsd\n")) ;

/* SPR # 9221 Fix Start */
  SC_STAT_Q752_TS_PROVIDER_INIT_RLSD;
  SC_STAT_Q752_INR_PROVIDER_INIT_RLSD;
/* SPR # 9221 Fix End */

  p_ccb = p_info->p_ccb;

  if (IS_COUPLING_PRESENT (p_ccb))
  {
    /* get the associated connection control block */
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

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

	/* SPR # 2579 Fix */
    /* change state to SCCP_CONN_CLOSING */
    sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
    /* SPR # 2579 Fix End */

    /* 
     * build RLSD message and forward it to route and translate 
     * functionality of SCRC
     */
    p_info->msg_type = RLSD_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

    /* remove the association */
    sccp_remove_association (p_ccb, p_coupled_ccb) ;

    sccp_route_co_msg (p_info) ;

  }
  else
  {
  	p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
    /* give N-DISCONNECT.ind to the user */
    sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
  }

  /* stop T_inact_rec and T_inact_send timers */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* 
   * build RLC message and forward it to route and translate 
   * functionality of SCRC
   */

  /* SPR # 2579 Fix Start */
  /* change state to SCCP_CONN_CLOSED */
  sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
  /* SPR # 2579 Fix End */

  p_info->msg_type = RLC_MSG_TYPE ;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;


  /* SPR 1327: Start fix 
   * Release resources after sending RLC message
   */
  /* release resources and local reference */
  sccp_release_resources (p_ccb) ;
  /* SPR 1327: End fix */

  sccp_route_co_msg (p_info) ;

    /* start T_freeze */
    result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
/* SPR # 9221 Fix Start */
		SC_STAT_Q752_TS_FAILURE_TO_REL_CONN;
		SC_STAT_Q752_INR_FAILURE_TO_REL_CONN;
/* SPR # 9221 Fix End */
      /* Error */
    }


  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RSR message from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RSR message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**
**    o restart T_inact_rec timer
**    o give N-RESET.ind to the user
**    o reset variables and discard all queued and unacked messages
**    o send event alarm to SM
**    o change state to SCCP_CONN_RESET and substate to SCCP_INGOING
**
*****************************************************************************/

return_t
sccp_conn_estab_rsr
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t    *p_ccb ;

/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  return_t      result ;
  sccp_ccb_t    *p_coupled_ccb ;
  conn_entry_t  conn ;
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_rsr\n")) ;

  p_ccb = p_info->p_ccb;

  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif


    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

  /* restart T_inact_rec timer */
  result = sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* reset variables and discard all queued and unacked messages */
  sccp_reset_variables (p_ccb) ;

  if (IS_COUPLING_PRESENT (p_ccb))
  {

    /* SPR 1776: Start
     * Send RSC on connection section */
    p_info->msg_type = RSC_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* restart T_inact_send timer */
    result = sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
    /* SPR 1776: End */

    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb); 

    /* reset variables and discard all queued and unacked messages */
    sccp_reset_variables (p_coupled_ccb) ;

    /* start T_reset timer */
    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_RESET_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
 
    /* restart T_inact_send timer */
    result = sccp_restart_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* send RSR on the coupled section */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_RESET and substate to SCCP_OUTGOING */
    sccp_change_state (p_coupled_ccb, SCCP_CONN_RESET, SCCP_OUTGOING) ;
    /* SPR # 2579 Fix End */

    sccp_utl_fill_nw_info (p_info, p_coupled_ccb);
    p_info->msg_type = RSR_MSG_TYPE;
    sccp_route_co_msg (p_info);
  }
  else
  {
    /* give N-RESET.ind to the user */
    sccp_build_n_reset_ind_api (p_info, p_ccb) ;

    /* change state to SCCP_CONN_RESET and substate to SCCP_INCOMING */
    sccp_change_state (p_ccb, SCCP_CONN_RESET, SCCP_INCOMING) ;
  }

  /* send alarm to sm */
  conn.conn_id = p_info->conn_id;    
  conn.reset_cause = p_info->reset_cause;
  conn.originator = sccp_utl_get_rsr_originator(p_info->reset_cause);

/* SPR # 9221 Fix Start */
  SC_STAT_Q752_TS_PROVIDER_INIT_RESET;
  SC_STAT_Q752_INR_PROVIDER_INIT_RESET;
/* SPR # 9221 Fix End */

  SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, CONN_RESET, SS7_NULL, SS7_NULL, &conn);

/* SPR 8985 - Fix Start */
#if 0
  return (SS7_SUCCESS) ;
#endif
#endif    /* for class 3 services */
  return (SS7_SUCCESS) ;
/* SPR 8985 - Fix End   */
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RouteFail message from the SCRC in the ESTABLSIHED state of 
**    SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RouteFail message from
**    the SCRC in the connection established phase.
**    When invoked it does the following :
**    
**    o if association involved
**    o then
**      o stop T_inact_rec and T_inact_send timer
**   	o if destination is accessible
**        o build RLSD message and forward it to route and translate 
**          functionality of SCRC
**        o start T_rel timer
**        o change state to SCCP_CONN_CLOSING
**      o else
**        o change state to SCCP_CONN_CLOSED
**      o get the associated connection control block 
**      o remove the association
**      o stop T_inact_rec and T_inact_send timer
**      o build RLSD message and forward it to route and translate 
**        functionality of SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**    o else
**      o give N-DISCONNECT.ind to the user
**      o stop T_inact_rec and T_inact_send timer
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**
*****************************************************************************/

return_t
sccp_conn_estab_routefail
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_routefail\n")) ;

  p_ccb = p_info->p_ccb;

  /* if association involved */
  if (IS_COUPLING_PRESENT (p_ccb))
  {
    /* get the associated connection control block  */
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

    /* remove the association */
    sccp_remove_association (p_ccb, p_coupled_ccb) ;

    /* stop T_inact_rec and T_inact_send timer */
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
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
    sccp_route_co_msg (p_info) ;

  }
  else
  {
    p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
    /* give N-DISCONNECT.ind to the user */
    sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
  }

  /* stop T_inact_rec and T_inact_send timer */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* GR changes -
   * Send RLSD on connection section only if destination is accessible 
   */
  
  if ((p_info->rel_cause != SCCP_RLSDC_MTP_FAILURE) && 
	(p_info->rel_cause != SCCP_RLSDC_SCCP_FAILURE))
  {
    	/* start T_rel timer */
    	result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      	/* Error */
    	}

    	/* 
     	* build RLSD message and forward it to route and translate 
     	* functionality of SCRC
     	*/
  		sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ; /* SPR 2579 Fix */

    	p_info->msg_type = RLSD_MSG_TYPE ;
    	/* rel cause is indiacted by SCRC */
    	sccp_utl_fill_nw_info (p_info, p_ccb) ;
    	sccp_route_co_msg (p_info) ;
  }
  /* else close connection */
  else 
  {
	sccp_release_resources (p_ccb) ;
	sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
	/* start T_freeze */
	result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
	if (result != SS7_SUCCESS)
	{
		/* Error */
	}
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the DT1 message from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives DT1 message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**    o Reset the T_inact_rec timer
**    o if M bit is 1 then the recevied data is put in receive queue for
**      reassembly.
**    o if M bit is 0 then the NSDU is constructed  by combining all data
**      in receive queue and a N-DATA.ind api is constructed.
**
*****************************************************************************/

return_t
sccp_conn_estab_dt1
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t    *p_ccb, *p_coupled_ccb ;
  U16bit full_data_len, transmitted_bytes;
  U8bit org_seg_reass, *p_buf;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_dt1\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR 1686: Increment statistics if p_ss exists */
  if (p_ccb->p_ss)
  	SC_STAT_Q752_INR_RECD_MSG_DT1 (p_ccb->p_ss->ssn) ;

  if(sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode)!= SS7_SUCCESS)
  {
    /* Error */
  }
  if (p_ccb->proto_class == PROTOCOL_CLASS_3)
  {
    /* protocol error, generate an error message */

    /* Corrected the Mesg type */
    p_info->msg_type = ERR_MSG_TYPE ;

    sccp_utl_fill_nw_info (p_info, p_ccb);
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif

    sccp_route_co_msg (p_info);
    return (SS7_SUCCESS);
  }
  if (IS_COUPLING_PRESENT (p_ccb))
  {
    p_coupled_ccb = SCCP_GET_COUPLED_CCB(p_ccb);
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb);

    full_data_len = p_info->data.len;
    p_buf = p_info->data.p;
    transmitted_bytes = 0;
    org_seg_reass = p_info->seg_reass;
    /* check if we need to resegment the message */
    do
    {
      if ((full_data_len - transmitted_bytes) > SCCP_MAX_CO_SEG_SIZE)
      {
        p_info->data.len = SCCP_MAX_CO_SEG_SIZE;
        SET_M_BIT_DT1 (p_info);
      }
      else
      {
        p_info->data.len = full_data_len - transmitted_bytes;
        p_info->seg_reass = org_seg_reass;
      }

      p_info->data.p = p_buf + transmitted_bytes;
      transmitted_bytes += p_info->data.len;
      sccp_route_co_msg (p_info);

    }while (full_data_len != transmitted_bytes);

    if (sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode)!= SS7_SUCCESS) 
    {
      /* Error */
    }

    return (SS7_SUCCESS);
  }
  else
    return (sccp_handle_reassembly (p_info, p_ccb));
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the DT2 message from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives DT2 message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**    
**    o Reset the T_inact_rec timer
**
*****************************************************************************/

return_t
sccp_conn_estab_dt2
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t *p_ccb;
  msg_info_t info;
/* SPR 8985 - Fix Start  */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  sccp_ccb_t *p_coupled_ccb;
  U8bit send_seq, recv_seq;
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_dt2\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR 1686: Increment statistics if p_ss exists */
  if (p_ccb->p_ss)
  	SC_STAT_Q752_INR_RECD_MSG_DT2 (p_ccb->p_ss->ssn) ;
  info.flag = 0;

  if (p_ccb->proto_class == PROTOCOL_CLASS_2)
  {
    /* message is not supported in CLASS 2 */
    p_info->msg_type = ERR_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_ccb);
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif

    sccp_route_co_msg (p_info);
    return (SS7_SUCCESS);
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

  /* restart inactivity receive timer */
  if (sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) != SS7_SUCCESS)
  {
    /* Error */
  }


  send_seq = GET_SEND_SEQ_NUM (p_info);
  recv_seq = GET_RECV_SEQ_NUM (p_info);

  /* send sequence number should be the one expected from  
      other node.
  */
  if (send_seq != p_ccb->send_seq_x)
  {
    p_info->reset_cause = SCCP_RSC_INCORRECT_PS;
    sccp_utl_reset_conn (p_info) ;
	/* SPR 10881 - Fix Start */
	SC_STAT_Q752_TS_PROVIDER_INIT_RESET;
	SC_STAT_Q752_INR_PROVIDER_INIT_RESET;
	/* SPR 10881 - Fix End  */
    return (SS7_SUCCESS);
  }

  /* receive sequence number should fall in the
     send window.
  */

  /* SPR No 1361: recv_seq indicates the next 'send
   * seq number' expected at the remote node
   */

  /* SPR 1769: Added the condition:
   * When lw_edge == send_seq 
   */

  if (((p_ccb->lw_edge < p_ccb->send_seq) &&
     ((recv_seq >  p_ccb->send_seq) ||
     (recv_seq < p_ccb->lw_edge))) ||
    ((p_ccb->lw_edge > p_ccb->send_seq) &&
     ((recv_seq > p_ccb->send_seq) &&
     (recv_seq < p_ccb->lw_edge))) ||
    ((p_ccb->lw_edge == p_ccb->send_seq) &&
     (recv_seq != p_ccb->send_seq)))
  {
    /* received sequence number does not fall in
       in the window.
    */

    /* start reset procedure */
    p_info->reset_cause = SCCP_RSC_INCORRECT_PR ;
    sccp_utl_reset_conn (p_info);
	/* SPR 10881 - Fix Start */
	SC_STAT_Q752_TS_PROVIDER_INIT_RESET;
	SC_STAT_Q752_INR_PROVIDER_INIT_RESET;
	/* SPR 10881 - Fix End  */
    return (SS7_SUCCESS);
  }

  /* SPR 1361: Start fix 
   * send_seq_ack should be the seq number 
   * of next expected mesg 
   */

  p_ccb->send_seq_x = INC_SEQ_NUM(send_seq);
  p_ccb->send_seq_ack = p_ccb->send_seq_x;

  /** SPR 11112 - Fix Start **/
  /* Update seq_seg field in corresoponding ccb */
  UPDATE_SEQ_SEG_IN_CCB(p_ccb);
  /** SPR 11112 - Fix End  **/

  /* lw_edge now becomes recv_seq */
  p_ccb->lw_edge = recv_seq ;
  /* SPR 1361: End fix */


  if (IS_COUPLING_PRESENT (p_ccb))
  {
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb);
    if (sccp_utl_add_to_tx_queue (p_info, p_coupled_ccb) == SS7_FAILURE)
    {
      /* error message */
    }

    /* try to send data on outgoing conection section */
    info.p_api = p_info->p_api;
    sccp_utl_fwd_dt2 (&info, p_coupled_ccb);
  }
  else
  {
    sccp_handle_reassembly (p_info, p_ccb);
  }

  /* try to send data on incoming conection section */
  info.p_api = p_info->p_api;
  if (sccp_utl_fwd_dt2 (&info, p_ccb) == SS7_FAILURE)
  {
    /* No messages was send, so send an AK */
    sccp_utl_fill_nw_info (p_info, p_ccb);
    p_info->msg_type = AK_MSG_TYPE;
    p_info->rsn = p_ccb->send_seq_ack;

    /*   credit should be change if congestion or
         some other constraints are presents.
     */
    p_info->credit = p_ccb->credit;
    sccp_route_co_msg (p_info);


    /* restart T_inact_send timer */
    if (sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) != SS7_SUCCESS)
    {
      /* Error */
    }

    return (SS7_SUCCESS);
  }

/* SPR 8985 - Fix Start */
#if 0
  return (SS7_SUCCESS);
#endif
#endif    /* for class 3 services */
  return (SS7_SUCCESS);
/* SPR 8985 - Fix End   */
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the AK message from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives DT2 message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**    
**    o Reset the T_inact_rec timer
**
*****************************************************************************/

return_t
sccp_conn_estab_ak
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  msg_info_t info;
  sccp_ccb_t *p_ccb;
  sp_entry_t *p_cong_sp;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  U8bit  recv_seq;
  /* SPR 9302 - Warning removal */		
#if 0
  U8bit scmg_status;
  U8bit upu_cause;
#endif
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_ak\n")) ;

  p_ccb = p_info->p_ccb;
  info.flag = 0;

  p_cong_sp = sccp_db_find_sp(p_info->nw_id, p_info->opc);
  if (p_ccb->proto_class == PROTOCOL_CLASS_2)
  {
    /* message is not supported in CLASS 2 */
    p_info->msg_type = ERR_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_ccb);
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif

    sccp_route_co_msg (p_info);
    return (SS7_SUCCESS);
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

  /* restart inactivity receive timer */
  if (sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) != SS7_SUCCESS)
  {
    /* Error */
  }

 
  /* SPR No 1361: recv seq indicates the value of the 
   * next 'send seq number' expected at the remote node
   */

  recv_seq = p_info->rsn; 

  /* receive sequence number should fall in the
     send window.
  */
  /* SPR 1769: Added the condition:
   * When lw_edge == send_seq 
   */

  if (((p_ccb->lw_edge < p_ccb->send_seq) &&
     ((recv_seq > p_ccb->send_seq) ||
     (recv_seq < p_ccb->lw_edge))) ||
    ((p_ccb->lw_edge > p_ccb->send_seq) &&
     ((recv_seq > p_ccb->send_seq) &&
     (recv_seq < p_ccb->lw_edge))) ||
    ((p_ccb->lw_edge == p_ccb->send_seq) &&
     (recv_seq != p_ccb->send_seq)))
  {
    /* received sequence number does not fall in
       in the window.
    */

    /* start reset procedure */
    p_info->reset_cause = SCCP_RSC_INCORRECT_PR ;
    sccp_utl_reset_conn (p_info);
    return (SS7_SUCCESS);
  }

/* SPR 11107 - Fix Start */
#if 0
/*** SPR 5510 Fix starts***/
  if(p_info->credit == 0)
  {
                if(p_cong_sp != SS7_NULL)
                {
                        p_cong_sp->cls = 0;
                        upu_cause = p_cong_sp->upu_cause;
                        p_cong_sp->upu_cause = 3;
                        scmg_status = p_cong_sp->scmg_ss.allowed;
                        p_cong_sp->scmg_ss.allowed = 0;
                        sccp_send_n_pcstate_ind(p_cong_sp, p_ccb->p_ss, 0x07);
                        p_cong_sp->cls = 1;
                        p_cong_sp->scmg_ss.allowed = scmg_status;
                        p_cong_sp->upu_cause = upu_cause;
                }
                else
		{
                        SCCP_UT_TRACE(("SCCP CANNOT find SP\n")) ;
		}
   }
   if(p_info->credit !=0 && p_cong_sp->cls > 0)
   {
              p_cong_sp->cls = 0;
              scmg_status = p_cong_sp->scmg_ss.allowed;
              p_cong_sp->scmg_ss.allowed = 1;
              sccp_send_n_pcstate_ind(p_cong_sp, p_ccb->p_ss, 0x07);
              p_cong_sp->scmg_ss.allowed = scmg_status;
   }
/*** SPR 5510 Fix ends***/
#endif
/* SPR 11107 - Fix End   */

  /* verify the credit value */
  if (((p_info->credit != 0) && (p_info->credit == p_ccb->credit))||
    (p_info->credit == 0))
  {
    p_ccb->w = p_info->credit;
    /* SPR 1361: 
     * lw_edge now becomes recv_seq 
     */
    p_ccb->lw_edge = recv_seq ;
  }
  else
  {
    /* start reset procedure */
    p_info->reset_cause = SCCP_RSC_RPE_GENERAL ;
    sccp_utl_reset_conn (p_info);
    return (SS7_SUCCESS);
  }

  /* try to send data on incoming conection section */
  info.p_api = p_info->p_api;
  sccp_utl_fwd_dt2 (&info, p_ccb);

/* SPR 8985 - Fix Start */
#if 0
  return (SS7_SUCCESS);
#endif
#endif    /* for class 3 services */
  return (SS7_SUCCESS);
/* SPR 8985 - Fix End   */
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the ED message from the peer in the ESTABLISHED state of SCCP
**    Connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives ED message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**
**
*****************************************************************************/

return_t
sccp_conn_estab_ed
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t   *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t    *p_ccb ;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  return_t      result ;
  sccp_ccb_t    *p_coupled_ccb ;
  msg_info_t 	info ;
  s7_len_t      ed_req_api_len, offset;
#endif
/* SPR 8985 - Fix End   */


  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_ed\n")) ;

  p_ccb = p_info->p_ccb ;
  
  /* SPR 1686: Increment statistics if p_ss exists */
  if (p_ccb->p_ss)
   	SC_STAT_Q752_INR_RECD_MSG_ED (p_ccb->p_ss->ssn) ;

  sccp_utl_fill_nw_info (p_info, p_ccb);

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif

    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

  /* restart T_inact_rec */
  result = sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
	  
	sccp_stop_co_timer (p_ccb,  SCCP_T_IAR_TIMER, p_ecode) ;
	return SS7_FAILURE;
  
    /* Error */
  }

  /** SPR # 4185 Fix Start **/
#if 0  /* Send EA only if there is no coupling */
  p_info->msg_type = EA_MSG_TYPE ;
  sccp_route_co_msg (p_info) ;
#endif
  /** SPR # 4185 Fix End **/

  if (IS_COUPLING_PRESENT (p_ccb))
  {
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

    /* SPR 1773: Start */
    /* Queue up the ED message */

	/** SPR # 4050 Fix Start **/
	/** Cannot Q the ED message directly - Construct N-Exp-Data-Req
	*** and Q this request
    **/

	/* Construct N-Exp-Data-Req */
	ed_req_api_len = API_HEADER_LEN + SCCP_N_ED_REQUEST_MIN_LEN + 
					p_info->data.len + SCCP_ELEM_LEN_LEN;
	if ( SS7_NULL == (info.p_api = (U8bit*) sccp_malloc(ed_req_api_len)))
/* start added during CC compilation */
/* assign pvoid to U8bit* */
/* end added during CC compilation */
	{
		return SS7_FAILURE;
		/* Error */
	}

	offset = 0;

	/* Fill API Header */
	info.p_api[offset ++] = SCCP_N_EXPEDIATE_DATA_REQUEST;
	info.p_api[offset ++] = SCCP_VERSION_ID;
	info.p_api[offset ++] = SCCP_N_ED_DATA_IND_NELEM;
	info.p_api[offset ++] = (U8bit) ed_req_api_len;
	info.p_api[offset ++] = (U8bit) (ed_req_api_len >> 8);

	/* Fill Conn Id */
#ifdef SCCP_CONNECTION_ID_CHANGES
        info.p_api[offset ++] = (U8bit) (p_coupled_ccb->conn_id);
        info.p_api[offset ++] = (U8bit) (p_coupled_ccb->conn_id >> 8);
        info.p_api[offset ++] = (U8bit) (p_coupled_ccb->conn_id >> 16);
        info.p_api[offset ++] = (U8bit) (p_coupled_ccb->conn_id >> 24);
#else
	info.p_api[offset ++] = (U8bit) (p_coupled_ccb->conn_id);
	info.p_api[offset ++] = (U8bit) (p_coupled_ccb->conn_id >> 8);
#endif

	/* Fill Data */
	info.p_api[offset ++] = (U8bit) (p_info->data.len);
	info.p_api[offset ++] = (U8bit) (p_info->data.len >> 8);
	sccp_memcpy(info.p_api + offset, p_info->data.p, ed_req_api_len);

    if (sccp_utl_add_to_ed_tx_queue(&info, p_coupled_ccb) == SS7_FAILURE)
    {
        /* Error */
    }

    if (!(SCCP_IS_UNACK_ED (p_coupled_ccb)))
    {
        /* if all previous EDs have been acknowledged, send ED message */
#if 0
    	info.p_api = p_info->p_api; /* Use Newly constructed API */
#endif
        sccp_utl_fwd_ed (&info, p_coupled_ccb, p_ecode);
    }

	/** SPR # 4050 Fix End **/

    /* SPR 1773: End */

  }
  else
  {
    /** SPR # 4185 Fix Start **/
    p_info->msg_type = EA_MSG_TYPE ;
    sccp_route_co_msg (p_info) ;
    /** SPR # 4185 Fix End **/

    sccp_build_n_expediate_data_ind_api (p_info, p_ccb) ;
  }

/* SPR 8985 - Fix Start */
#if 0
  return (SS7_SUCCESS) ;
#endif
#endif         /* For class 3 services */
  return (SS7_SUCCESS) ;
/* SPR 8985 - Fix End   */
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the EA message from the peer in the ESTABLISHED state of SCCP
**    Connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives EA message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**
**
*****************************************************************************/

return_t
sccp_conn_estab_ea
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t   *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  sccp_ccb_t    *p_coupled_ccb ;
  msg_info_t 	info ;
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_ea\n")) ;

  p_ccb = p_info->p_ccb ;

  sccp_utl_fill_nw_info (p_info, p_ccb);

  /* restart T_inact_rec */
  result = sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(ERR_MSG_TYPE);
        }
#endif

    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

  /* SPR 1774: Start
   * if an unexpected EA message arrives */
  if (!(SCCP_IS_UNACK_ED(p_ccb)))
  { 

   /* For ITU-T and ETSI */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
  	/* discard the received message */
  	sccp_discard_message (p_info) ;
  	return (SS7_SUCCESS) ;
  }
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
/** SPR 11109 - Fix Start **/
#if 0
        /* start reset procedure */
        p_info->reset_cause = SCCP_RSC_RPE_GENERAL ;
        sccp_utl_reset_conn (p_info);
#endif
  	/* discard the received message - ANSI Table B-5/T1.112.4 */
  	sccp_discard_message (p_info) ;
/** SPR 11109 - Fix End  **/
        return (SS7_SUCCESS);
  }
#endif
  }
  /* SPR 1774: End */

  SCCP_RESET_UNACK_ED (p_ccb) ;

  /* SPR 1773: Start */
  /* Send next ED message in queue */
  info.p_api = p_info->p_api;
  sccp_utl_fwd_ed (&info, p_ccb, p_ecode);
  /* SPR 1773: End */

  	/** SPR # 4050 Fix Start **/
	/** Forward the EA on Coupled Connection Section **/
	if (IS_COUPLING_PRESENT (p_ccb))
	{
		p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
		/* Build EA msg and forward it */
		p_info->msg_type = EA_MSG_TYPE;
		sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
		sccp_route_co_msg(p_info);
	}
  	/** SPR # 4050 Fix End **/


#if 0
  if (p_ccb->send_Q != (sc_queue_t *)SS7_NULL)
  {
    /* restart T_inact_send */
    result = sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* send out the ED message queued */
    p_info->msg_type = ED_MSG_TYPE ;

    /* Attach the data and data len */

    SCCP_SET_UNACK_ED (p_ccb) ;
  }
#endif
/* SPR 8985 - Fix Start */
#if 0
  return (SS7_SUCCESS) ;
#endif
#endif    /* for class 3 services */
  return (SS7_SUCCESS) ;
/* SPR 8985 - Fix End   */
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the ERR message from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives ERR message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**
**    o if association involved
**    o then
**      o stop T_inact_rec and T_inact_send timers
**      o build RLSD and forward it to route and translate functionality of
**        SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**      o get the associated connection control block
**      o remove the association
**      o stop T_inact_rec and T_inact_send timers
**      o build RLSD and forward it to route and translate functionality of
**        SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**    o else
**      o if service class mismatch
**      o then
**        o give N-DISCONNECT.ind to the user
**        o stop T_inact_send and T_inact_rec timers
**        o build RLSD and forward it to route and translate functionality of
**          SCRC
**        o start T_rel timer
**        o change state to SCCP_CONN_CLOSING
**      o else
**        o release resources and local reference
**        o give N-DISCONNECT.ind to the user
**        o stop T_inact_send and T_inact_rec timers
**        o change state to SCCP_CONN_CLOSED
**
*****************************************************************************/

return_t
sccp_conn_estab_err
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_err\n")) ;

  p_ccb = p_info->p_ccb;

  if (IS_COUPLING_PRESENT (p_ccb))
  {
    /* stop T_inact_rec and T_inact_send timers */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
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

    /* 
     * build RLSD and forward it to route and translate functionality of
     * SCRC
     */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSING */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
    /* SPR # 2579 Fix End */

    p_info->msg_type = RLSD_MSG_TYPE ;
    p_info->rel_cause = SCCP_RLSDC_REMOTE_PROCEDURE_ERROR;
    sccp_utl_fill_nw_info (p_info, p_ccb);
	p_info->importance = sccp_get_min_message_priority(p_info->msg_type);

    /* get the associated connection control block */
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

    /* remove the association */
    sccp_remove_association (p_ccb, p_coupled_ccb) ;

    sccp_route_co_msg (p_info) ;

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
     * build RLSD and forward it to route and translate functionality of
     * SCRC
     */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSING */
    sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
    /* SPR # 2579 Fix End */

    p_info->msg_type = RLSD_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb);
	p_info->importance = sccp_get_min_message_priority(p_info->msg_type);
    sccp_route_co_msg (p_info) ;
  }
  else
  {
    /* stop T_inact_send and T_inact_rec timers */
      result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
        /* Error */
    }

    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    if (p_info->error_cause == SCCP_ERRC_SERVICE_CLASS_MISMATCH)
    {
     p_info->rel_cause = SCCP_RLSDC_REMOTE_PROCEDURE_ERROR;
    p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
      /* give N-DISCONNECT.ind to the user */
      sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

      /* start T_rel timer */
      result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      /* 
       * build RLSD and forward it to route and translate functionality of
       * SCRC
       */

  	  /* SPR # 2579 Fix Start */
      /* change state to SCCP_CONN_CLOSING */
      sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
      /* SPR # 2579 Fix End */

      p_info->msg_type = RLSD_MSG_TYPE ;
      p_info->rel_cause = SCCP_RLSDC_REMOTE_PROCEDURE_ERROR;
      sccp_utl_fill_nw_info (p_info, p_ccb);
	  p_info->importance = sccp_get_min_message_priority(p_info->msg_type);

      sccp_route_co_msg (p_info);
    }
    else
    {
      /* release resources and local reference */
      sccp_release_resources (p_ccb) ;

    /* RLSD message should not be sent */

      /* give N-DISCONNECT.ind to the user */
    if ((p_info->error_cause == SCCP_ERRC_LRN_MISMATCH_UNASSIGNED_DLRN) ||
      (p_info->error_cause == SCCP_ERRC_LRN_MISMATCH_INCONSISTENT_SLRN) ||
      (p_info->error_cause == SCCP_ERRC_POINT_CODE_MISMATCH))
	  /* SPR 10884 - Fix Start */
      /*p_info->rel_cause =  SCCP_RLSDC_ACCESS_FAILURE ;*/
      p_info->rel_cause =  SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA ;
	  /* SPR 10884 - Fix End */
    else
      p_info->rel_cause =  SCCP_RLSDC_UNQUALIFIED ;
    

    p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause);
      sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

      /* change state to SCCP_CONN_CLOSED */
      sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

      /* start T_freeze timer */
      result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }
    }
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the IT message from the peer in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives IT message from
**    the peer in the connection established phase.
**    When invoked it does the following :
**
**    o if dlr is not matching with slr or proto_class is not matching
**    o then
**      o connection is released
**      o build RLSD and forward it to route and translate functionality of
**        SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**      o if coupling is performed on the node
**      o then
**        o remove the association
**        o stop T_inact_rec and T_inact_send timers
**        o build RLSD and forward it to route and translate functionality of
**          SCRC
**        o start T_rel timer
**        o change state to SCCP_CONN_CLOSING
**      o else
**        o give n-disconnect.in to the upper layer
**    o in case of class 3 protocol if seq_seg or credit is not matching
**    o then
**      o connection is reset
**      o build RSR message and forward it to the routing and translation 
**        functionality of SCRC
**      o start T_reset timer
**      o restart T_inact_send timer
**      o reset variables and discard all the queued and unacked messages
**      o change state to SCCP_CONN_RESET 
**      o if coupling is performed on the node
**      o then
**        o get the coupled node
**        o build RSR message and forward it to the routing and translation 
**          functionality of SCRC
**        o start T_reset timer
**        o restart T_inact_send timer
**        o reset variables and discard all the queued and unacked messages
**        o change state to SCCP_CONN_RESET 
**      o give n_reset.ind to the upper layer
**
*****************************************************************************/

return_t
sccp_conn_estab_it
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  conn_entry_t  conn ;
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_it\n")) ;

  p_ccb = p_info->p_ccb;

  if ((p_info->dlr != p_ccb->slr) || 
  (p_info->proto_class != p_ccb->proto_class))
  {

	/* SPR 11104 - Fix  */
    p_info->rel_cause = SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA ;

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
       * build RLSD and forward it to route and translate functionality of
       * SCRC
       */

      /* SPR # 2579 Fix Start */
      /* change state to SCCP_CONN_CLOSING */
      sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SCCP_OUTGOING) ;
      /* SPR # 2579 Fix End */

      p_info->msg_type = RLSD_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_coupled_ccb);

      sccp_route_co_msg (p_info) ;
    }
    else
    {
       p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause);
       /* give N-DISCONNECT.ind to the user */
       sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
    }

	/* SPR 11104 - Fix - moving it above */
    /*p_info->rel_cause = SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA ;*/

    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
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

    /* 
     * build RLSD and forward it to route and translate functionality of
     * SCRC
     */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSING */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SCCP_OUTGOING) ;
    /* SPR # 2579 Fix End */

    p_info->msg_type = RLSD_MSG_TYPE ;

    sccp_utl_fill_nw_info (p_info, p_ccb);
    sccp_route_co_msg (p_info) ;

	/* SPR 10879 - Fix Start */
	SC_STAT_Q752_TS_PROVIDER_INIT_RLSD;
	SC_STAT_Q752_INR_PROVIDER_INIT_RLSD;
	/* SPR 10879 - Fix End   */
    /* SPR GR: Return from function */
    return (SS7_SUCCESS);
  }

  if ((p_ccb->proto_class == PROTOCOL_CLASS_3) &&
     ((p_info->credit != p_ccb->credit) ||
	 /* SPR 11112 - Fix Start */
     (((p_info->seq_seg & 0x00ff ) >> 1) != (((p_ccb->seq_seg)>>9)& 0x00ff))))
	 /*(p_info->seq_seg != p_ccb->seq_seg)))*/
	 /** SPR 11112 - Fix Start */
  {
    /* Added this condition to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

	/* SPR 11243 - Fix */
    p_info->reset_cause = SCCP_RSC_RPE_GENERAL ;

    if (IS_COUPLING_PRESENT (p_ccb))
    {
      p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

      /* reset variables and discard all the queued and unacked messages */
      sccp_reset_variables (p_coupled_ccb) ;

      /* 
       * build RSR message and forward it to the routing and translation 
       * functionality of SCRC
       */

      /* SPR # 2579 Fix Start */
      /* change state to SCCP_CONN_RESET and substate to SCCP_OUTGOING */
      sccp_change_state (p_coupled_ccb, SCCP_CONN_RESET, SCCP_OUTGOING) ;
      /* SPR # 2579 Fix End */

      p_info->msg_type = RSR_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_coupled_ccb);
      sccp_route_co_msg (p_info) ;

      /* start T_reset timer */
      result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_RESET_TIMER,
                    p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      /* restart T_inact_send timer */
      result = sccp_stop_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }
      /* SPR 1338: Start fix
       * Start T_inact_send timer
       */
      result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }
      /* SPR 1338: End fix */

    }
    else
    {
      sccp_build_n_reset_ind_api (p_info, p_ccb) ;
    }

    /* reset variables and discard all the queued and unacked messages */
    sccp_reset_variables (p_ccb) ;

	/* SPR 11243 - moving it above */
    /*p_info->reset_cause = SCCP_RSC_RPE_GENERAL ;*/

    /* 
     * build RSR message and forward it to the routing and translation 
     * functionality of SCRC
     */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_RESET and substate to SCCP_OUTGOING */
    sccp_change_state (p_ccb, SCCP_CONN_RESET, SCCP_OUTGOING) ;
    /* SPR # 2579 Fix End */

    p_info->msg_type = RSR_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_ccb);
    sccp_route_co_msg (p_info) ;

    /* start T_reset timer */
    result = sccp_start_co_timer (p_ccb, SCCP_T_RESET_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* restart T_inact_send timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
    /* SPR 1338: Start fix
     * Start T_inact_send timer
     */
    result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
        /* Error */
    }
    /* SPR 1338: End fix */


  /* send alarm to sm */
  conn.conn_id = p_info->conn_id;    
  conn.reset_cause = p_info->reset_cause;
  conn.originator = sccp_utl_get_rsr_originator(p_info->reset_cause);

  SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, CONN_RESET, SS7_NULL, SS7_NULL, &conn);
#endif
  }

  /* SPR # 6286 Fix start */
  /* restart T_inact_rec timer */
  result = sccp_restart_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
	  return result;
       /* Error */
  }
  /* SPR # 6286 Fix End */

  return (SS7_SUCCESS) ;
}
/*****************************************************************************
**
**  FUNCTION :
**    Handles the T_inact_sen timeout in the ESTABLISHED state of SCCP 
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_inact_sen timeout 
**    in the connection established phase.
**    When invoked it does the following :
**    
**      o build IT and forward it to route and translate functionality of
**        SCRC
**      o re-startT_inact_sen
**
*****************************************************************************/

return_t
sccp_conn_estab_t_ias_tmout
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_t_ias_tmout\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR #4584 Fix Start */
  if ( p_ccb->sccp_timer[SCCP_T_IAS_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_IAS_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */

     /* 
      * build IT and forward it to route and translate functionality of
      * SCRC
      */
      p_info->msg_type = IT_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_ccb);
      p_info->nw_id = DEFAULT_NW_ID ;

      p_info->seq_seg = p_ccb->seq_seg;

      p_info->credit = p_ccb->credit;

      sccp_route_co_msg (p_info) ;

      /* start T_ias timer */
      result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
          /* Error */
      }

      return (SS7_SUCCESS) ;
  }
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the T_inact_rec timeout in the ESTABLISHED state of SCCP 
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_inact_rec timeout 
**    in the connection established phase.
**    When invoked it does the following :
**    
**    o if association involved
**    o then
**      o stop T_inact_rec and T_inact_send timers
**      o build RLSD and forward it to route and translate functionality of
**        SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**      o get the associated connection control block
**      o remove the association
**      o stop T_inact_rec and T_inact_send timers
**      o build RLSD and forward it to route and translate functionality of
**        SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**    o else
**      o give N-DISCONNECT.ind to the user
**      o stop T_inact_send timer
**      o build RLSD and forward it to route and translate functionality of
**        SCRC
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**
*****************************************************************************/

return_t
sccp_conn_estab_t_iar_tmout
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_t_iar_tmout\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR #4584 Fix Start */
  if ( p_ccb->sccp_timer[SCCP_T_IAR_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_IAR_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */

      result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
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

      /* 
       * build RLSD and forward it to route and translate functionality of
       * SCRC
       */

      /* SPR # 2579 Fix Start */
      /* change state to SCCP_CONN_CLOSING */
      sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
      /* SPR # 2579 Fix End */

      p_info->msg_type = RLSD_MSG_TYPE ;
      p_info->rel_cause = SCCP_RLSDC_IT_TIMER_EXPIRED;
      sccp_utl_fill_nw_info (p_info, p_ccb);
      p_info->nw_id = DEFAULT_NW_ID;
      sccp_route_co_msg (p_info) ;

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
        * build RLSD and forward it to route and translate functionality of
        * SCRC
        */

        /* SPR # 2579 Fix Start */
        /* change state to SCCP_CONN_CLOSING */
        sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
        /* SPR # 2579 Fix End */

        p_info->msg_type = RLSD_MSG_TYPE ;
        sccp_utl_fill_nw_info (p_info, p_coupled_ccb);

        sccp_route_co_msg (p_info) ;
      }
      else
      {
        p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause);
       /* give N-DISCONNECT.ind to the user */
        sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
      }

/* SPR # 9221 Fix Start */
	  SC_STAT_Q752_TS_IAR_EXPIRY;
	  SC_STAT_Q752_INR_IAR_EXPIRY;
/* SPR # 9221 Fix End */
		/* SPR 10879 - Fix Start */
		SC_STAT_Q752_TS_PROVIDER_INIT_RLSD;
		SC_STAT_Q752_INR_PROVIDER_INIT_RLSD;
		/* SPR 10879 - Fix End   */


      return (SS7_SUCCESS) ;
  }
}


/* SPR 1338: Added function */
/*****************************************************************************
**
**  FUNCTION :
**    Handles the Common action to be taken for certain messages
**    as per ITU specifications
**
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it discards the message
**
*****************************************************************************/
 
return_t
sccp_conn_estab_comm_func_itu
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  return_t   result;

  /* restart T_inact_rec timer */
  result = sccp_restart_co_timer (p_info->p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
       /* Error */
  }

  /* discard the received message */
  sccp_discard_message (p_info) ;
  return (SS7_SUCCESS) ;
}


/* SPR 1338:  Added function */
/*****************************************************************************
**
**  FUNCTION :
**    Handles the Common action to be taken for certain messages
**    as per ANSI specifications
**
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it does the following:
**	
**    o stop inactivity timers
**    o send RLSD message on the connection section
**    o start T_rel timer
**    o change state to SCCP_CONN_CLOSING
**    o if association involved
**    o then
**    	o remove the association
**    	o stop inactivity timers
**	o send RLSD message on the connection section
**	o start T_rel timer
**	o change state to SCCP_CONN_CLOSING
**    o else
**	o send N_DISCONNECT indication to user
**
*****************************************************************************/
 
return_t
sccp_conn_estab_comm_func_ansi
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{

  return_t      result ;
  sccp_ccb_t    *p_ccb ;
  sccp_ccb_t    *p_coupled_ccb ;
 
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_estab_comm_func_ansi\n")) ;
 
  p_ccb = p_info->p_ccb;
 
  /* stop T_inact_rec and T_inact_send timers */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }
 
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /*
   * build RLSD message and forward it to the translate and route
   * functions of SCRC
   */

  /* SPR # 2579 Fix Start */
  /* change state to SCCP_CONN_CLOSING */
  sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
  /* SPR # 2579 Fix End */

  p_info->msg_type = RLSD_MSG_TYPE ;
  p_info->rel_cause = SCCP_RLSDC_REMOTE_PROCEDURE_ERROR;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
        p_info->importance = sccp_get_min_message_priority(RLSD_MSG_TYPE);
  }
#endif

 
  sccp_route_co_msg (p_info) ;
 
  /* start T_rel timer */
  result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }
 
 
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
 
    	/*
     	 * build RLSD message and forward it to route and translate
     	 * functionality of SCRC
     	 */

        /* SPR # 2579 Fix Start */
    	/* change state to SCCP_CONN_CLOSING */
    	sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
        /* SPR # 2579 Fix End */

    	p_info->msg_type = RLSD_MSG_TYPE ;
    	sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
            p_info->importance = sccp_get_min_message_priority(RLSD_MSG_TYPE);
        }
#endif

 
    	sccp_route_co_msg (p_info) ;
 
    	/* start T_rel timer */
    	result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_REL_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      	/* Error */
    	}
  }
  else
  {
    	/* give N-DISCONNECT.ind to the user */
     	p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
     	sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
  }

  return (SS7_SUCCESS) ;
}


/* SPR 1338: Added function */
/*****************************************************************************
**
**  FUNCTION :
**    Handles the RSC message in the ESTABLISHED state of SCCP connection
**    as per ITU specifications.
**
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it resets the conection.
**
*****************************************************************************/
 
return_t
sccp_conn_estab_rsc
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  return_t result;
  /* SPR # 11110 - Fix Start */	
  sccp_ccb_t    *p_ccb ;
  /* SPR # 11110 - Fix End  */	
#endif
/* SPR 8985 - Fix End   */

  /* Added this to enable compiling without class 3 services */
  /* SPR 5926...Fix Starts */
 /* SPR # 8552 Fix starts*/
  #ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE 
 /* SPR # 8552 Fix ends */

	/* SPR 11110 - Fix Start */
	p_ccb = p_info->p_ccb;

  /*#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE */
    /*if(p_info->proto_class == 3)*/
    if(p_ccb->proto_class == PROTOCOL_CLASS_3)
	/* SPR 11110 - Fix End  */
    {

    	/* restart T_inact_rec timer */
    	result = sccp_restart_co_timer (p_info->p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
			(void)sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
			return result;
       		/* Error */
    	}

    	/* start reset procedure */
    	p_info->reset_cause = SCCP_RSC_RPE_GENERAL ;
    	sccp_utl_reset_conn (p_info);
    }

	/* SPR 10881 - Fix Start */
	SC_STAT_Q752_TS_PROVIDER_INIT_RESET;
	SC_STAT_Q752_INR_PROVIDER_INIT_RESET;
	/* SPR 10881 - Fix End  */

 /* SPR # 8552 Fix starts*/
  #endif     /* for class 3 services */
 /* SPR # 8552 Fix ends */
 /* #endif     for class 3 services */
 /* SPR 5926 ... Fix Ends */

    return (SS7_SUCCESS) ;
}

#else

/*****************************************************************************
**	This extern declaration is required as BCC reports error if the 
** source file is empty after preprocessing. This declaration enables compilation
** without SCCP_INCLUDE_CO_SERVICE flag using BCC.
**
*****************************************************************************/

extern return_t sccp_co_dummy _ARGS_ ((void));

#endif
