/*****************************************************************************
**
**  FILE :
**    State Machine Functions for the Connection RESET state of the 
**    connection
**
******************************************************************************
**
**  FILENAME :
**    sc_reset.c
**
**  DESCRIPTION :
**    This file contains all the functions handling the events for the 
**    RESET state of the SCCP connections.
**
**  Date      Name             Reference     Reason
**  _________________________________________________________________________
**  20Jun'02  Suyash Tripathi                Fixed SPR 8985 
**  10Jul'00  Ramu Kandula  		     Fixed SPR 4051 
**  09Jun'00  Ramu Kandula  		     Fixed SPR 2579 - Change state before
**                                       sending the message to SCRC
**  19Feb'99  Sudipta Pattar		     Fixed SPR 1364
**  07Feb'99  Sudipta Pattar                 Added event alarms
**  08Jul'98  Praneet Khare    HSS:20800011  Original
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"

#ifdef SCCP_INCLUDE_CO_SERVICE

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-RESET.req from the User in the RESET state of 
**    SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-RESET.req from
**    the user in the connection reset phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_INCOMING
**    o then
**      o build RSC message and forward it to route and translate
**        functionality of SCRC
**      o restart T_inact_send timer
**      o give N-RESET.conf primitive to the user
**      o resume data transfer
**	o send event alarm to SM
**      o change state to SCCP_CONN_ESTABLISHED
**
*****************************************************************************/

return_t
sccp_conn_reset_n_reset_req
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SPR 8985 - Fix End   */
  return_t          result ;
  conn_entry_t      conn;
/* SPR 8985 - Fix Start */
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_n_reset_req\n")) ;

  p_ccb = p_info->p_ccb;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE   

  /* if substate == SCCP_INCOMING */
  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_INCOMING)
  {
    /* restart T_inact_send timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* give N-RESET.conf primitive to the user */
    sccp_build_n_reset_conf_api (p_info, p_ccb) ;

    /* resume data transfer */
    sccp_resume_data_transfer (p_ccb) ;

    /* 
     * build RSC message and forward it to route and translate
     * functionality of SCRC
     */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_ESTABLISHED */
    sccp_change_state (p_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;
    /* SPR # 2579 Fix End */

     p_info->msg_type = RSC_MSG_TYPE ;
     sccp_utl_fill_nw_info (p_info, p_ccb) ;

     sccp_route_co_msg (p_info) ;

    /* send alarm to sm */
    conn.conn_id = p_info->conn_id;    
    SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, RESUME_DATA, SS7_NULL, SS7_NULL, 
							&conn);
  }
  else
  {
    /* Discard the message */
    sccp_discard_message (p_info) ;
  }
#endif   /* for class 3 servies */

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-RESET.res from the User in the ESTABLISHED state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-RESET.res from
**    the user in the connection established phase.
**    When invoked it does the following :
**
**    o if substate == SCCP_INCOMING
**    o then
**      o build RSC message and forward it to the route and translate 
**        functionality of SCRC
**      o restart T_inact_send timer
**      o give N-RESET.conf primitive to the user
**      o resume data transfer
** 	o send event alarm to SM
**      o change state to SCCP_CONN_ESTABLISHED
**
*****************************************************************************/

return_t
sccp_conn_reset_n_reset_res
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SPR 8985 - Fix End   */
  return_t          result ;
  conn_entry_t      conn;
/* SPR 8985 - Fix Start */
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_n_reset_res\n")) ;

  p_ccb = p_info->p_ccb;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE   

  /* if substate == SCCP_INCOMING */
  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_INCOMING)
  {
    /* restart T_inact_send timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* give N-RESET.conf primitive to the user */
    sccp_build_n_reset_conf_api (p_info, p_ccb) ;

    /* Call send_from_sccp */

    /* resume data transfer */
    sccp_resume_data_transfer (p_ccb) ;

    /* 
     * build RSC message and forward it to route and translate
     * functionality of SCRC
     */

     /* SPR # 2579 Fix Start */
     /* change state to SCCP_CONN_ESTABLISHED */
     sccp_change_state (p_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;
     /* SPR # 2579 Fix End */

     p_info->msg_type = RSC_MSG_TYPE ;
     sccp_utl_fill_nw_info (p_info, p_ccb) ;

     sccp_route_co_msg (p_info) ;

    /* send alarm to sm */
    conn.conn_id = p_info->conn_id;    
    SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, RESUME_DATA, SS7_NULL, SS7_NULL, 
							&conn);
  }
  else
  {
    /* Discard the message */
    sccp_discard_message (p_info) ;
  }

#endif     /* for class 3 services */
  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RLSD from the peer in the RESET state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RLSD from
**    the peer in the connection reset phase.
**    When invoked it does the following :
**    
**    o release resources and local reference
**    o stop T_inact_send and T_inact_rec timers
**    o send RLC
**    o send event alarm to SM
**    o if there is a associated node
**    o then
**      o remove association between the nodes
**      o change state to SCCP_CONN_CLOSED for the ccb
**      o send RLSD on the associated section
**      o start T_rel for the associated section
**      o change state to SCCP_CONN_CLOSING for the associated ccb
**    o else
**      o give N-DISCONNECT.ind to the user
**      o change state to SCCP_CONN_CLOSED
**
*****************************************************************************/

return_t
sccp_conn_reset_rlsd
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;
  sccp_ccb_t        *p_coupled_ccb ;
  return_t          result ;
  conn_entry_t 	    conn ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_rlsd\n")) ;

  p_ccb = p_info->p_ccb;

  /* release resources and local reference */
  sccp_release_resources (p_ccb) ;

  /* stop T_inact_send and T_inact_rec timers */
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

  result = sccp_stop_co_timer (p_ccb, SCCP_T_RESET_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* SPR # 2579 Fix Start */
  /* change state to SCCP_CONN_CLOSED for the ccb */
  sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
  /* SPR # 2579 Fix End */

  /* send RLC */
  /* SPR 1364: change mesg type to RLC_MSG_TYPE */
  p_info->msg_type = RLC_MSG_TYPE ;
  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  sccp_route_co_msg (p_info) ;

  /* send alarm to sm */
  conn.conn_id = p_info->conn_id;    
  SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, CONN_CLOSE, SS7_NULL, SS7_NULL, &conn);

  /* if there is a associated node */
  if (IS_COUPLING_PRESENT (p_ccb))
  {
    /* Start T freeze timer */
    result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* Get the Coupled CCB */
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

    /* remove association between the nodes */
    sccp_remove_association (p_ccb, p_coupled_ccb) ;

    /* send RLSD on the associated section */
    
    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSING for the associated ccb */
    sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
    /* SPR # 2579 Fix End */

    p_info->msg_type = RLSD_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* start T_rel for the associated section */
    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_REL_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
  }
  else
  {
	p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
    /* give N-DISCONNECT.ind to the user */
    sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

    /* Start T_freeze */
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
**    Handles the RSC message from the peer in the RESET state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RSC message from
**    the peer in the connection reset phase.
**    When invoked it does the following :
**
**    o if substate != SCCP_INCOMING 
**    o then
**      o stop T_reset timer
**      o restart T_inact_rec
**      o resume data transfer
**	o send event alarm to SM
**      o change state to SCCP_CONN_ESTABLISHED
**      o if coupling present
**      o then
**        o send RSC on the coupled section
**        o start T_inact_send timer
**        o resume data transfer
**        o change state to SCCP_CONN_ESTABLISHED
**      o else
**        o give N-RESET.conf to the user
**
*****************************************************************************/

return_t
sccp_conn_reset_rsc
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SPR 8985 - Fix End   */
  sccp_ccb_t        *p_coupled_ccb ;
  return_t          result ;
  conn_entry_t 	    conn ;
/* SPR 8985 - Fix Start */
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_rsc\n")) ;

  p_ccb = p_info->p_ccb;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE   

  /* if substate != SCCP_INCOMING  */
  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) != SCCP_INCOMING)
  {
    /* stop T_reset timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_RESET_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* restart T_inact_rec */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_start_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* resume data transfer */
    sccp_resume_data_transfer (p_ccb) ;

    /* send alarm to sm */
    conn.conn_id = p_info->conn_id;    
    SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, RESUME_DATA, SS7_NULL, SS7_NULL, 
							&conn);

    /* change state to SCCP_CONN_ESTABLISHED */
    sccp_change_state (p_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;

    /* if coupling present */
    if (IS_COUPLING_PRESENT (p_ccb))
    {
      p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
  
      /* SPR 1776: RSC has already been sent */
#if 0
      /* send RSC on the coupled section */
      p_info->msg_type = RSC_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

      sccp_route_co_msg (p_info) ;

      /* start T_inact_send timer */
      result = sccp_stop_co_timer (p_coupled_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }
#endif

      /* resume data transfer */
      sccp_resume_data_transfer (p_coupled_ccb) ;

      /* change state to SCCP_CONN_ESTABLISHED */
      sccp_change_state (p_coupled_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;
    }
    else
    {
      /* give N-RESET.conf to the user */
      sccp_build_n_reset_conf_api (p_info, p_ccb) ;
    }
  }
  else
  {
	/** SPR # 4051 Fix Start **/
#if 0
    /* Discard the message */
    sccp_discard_message (p_info) ;
#endif
	/* RSC Message is Not expected on an Incoming connection section - 
	** Therefore, in accordance with Table B.4/Q.714 and Table B-4/T1.112.4,
	** a RSR must be sent instead of just discarding the message */
	
	p_info->reset_cause = SCCP_RSC_RPE_GENERAL;
	sccp_utl_reset_conn(p_info);
	return (SS7_SUCCESS);

	/** SPR # 4051 Fix End **/
  }

#endif    /* for class 3 services */
  return (SS7_SUCCESS) ;
}

/** SPR # 4051 Fix Start **/
/* According to Table B.4/Q.714 and Table B-4/T1.112.4, If the substate is
** Outgoing, a RSR must be sent instead of just discarding an unexpected
** message from peer */

/*****************************************************************************
**
**  FUNCTION :
**    Handles the Unexpected  messages from the peer in the RESET state of SCCP
**    connection (i.e Handles remote procedure error in RESET state)
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives unexpected message from
**    the peer in the connection reset phase.
**    When invoked it does the following :
**
**    o if substate != SCCP_INCOMING 
**    o then
**        o Discard message
**    o else
**        o Send RSR to peer with cause as Remote Procedure Error - General
**
*****************************************************************************/

return_t
sccp_conn_reset_rpe
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_rsc\n")) ;

  p_ccb = p_info->p_ccb;

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE   

  /* if substate != SCCP_INCOMING  */
  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) != SCCP_INCOMING)
  {
    /* Discard the message */
    sccp_discard_message (p_info) ;
  }
  else
  {
	p_info->reset_cause = SCCP_RSC_RPE_GENERAL;
	sccp_utl_reset_conn(p_info);
  }

#endif    /* for class 3 services */
  return (SS7_SUCCESS) ;

  /* SPR 9302 - Fix Start */
  p_ecode = 0;
  /* SPR 9302 - Fix End   */
}

/** SPR # 4051 Fix End **/

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RSR message from the peer in the RESET state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RSR message from
**    the peer in the connection reset phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_INCOMING
**    o then
**      o stop T_reset timer
**      o restart T_inact_rec timer
**      o resume data tranfer
**	o send event alarm to SM
**      o change state to SCCP_CONN_ESTABLISHED
**      o if coupling present
**      o then
**        o send RSC on the coupled section
**        o start T_inact_send timer
**        o resume data transfer
**        o change state to SCCP_CONN_ESTABLISHED
**      o else
**        o give N-RESET.conf to the user
**
*****************************************************************************/

return_t
sccp_conn_reset_rsr
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;
/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SPR 8985 - Fix End   */
  sccp_ccb_t        *p_coupled_ccb ;
  return_t          result ;
  conn_entry_t      conn ;
/* SPR 8985 - Fix Start */
#endif
/* SPR 8985 - Fix End   */

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_rsr\n")) ;

  p_ccb = p_info->p_ccb;

  if (p_ccb->proto_class != PROTOCOL_CLASS_3)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* Error */
    return (SS7_SUCCESS) ;
  }

  /* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE   

  /* if substate == SCCP_OUTGOING */
  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
  {
    /* stop T_reset timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_RESET_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* restart T_inact_rec timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_start_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* resume data tranfer */
    sccp_resume_data_transfer (p_ccb) ;

    /* send alarm to sm */
    conn.conn_id = p_info->conn_id;    
    SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, RESUME_DATA, SS7_NULL, SS7_NULL, 
							&conn);

    /* change state to SCCP_CONN_ESTABLISHED */
    sccp_change_state (p_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;

    /* if coupling present */
    if (IS_COUPLING_PRESENT (p_ccb))
    {
	  p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

      /* SPR 1776: RSC has already been sent */
#if 0
      /* send RSC on the coupled section */
      p_info->msg_type = RSC_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

      sccp_route_co_msg (p_info) ;

      /* start T_inact_send timer */
      result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }
#endif

      /* resume data transfer */
      sccp_resume_data_transfer (p_coupled_ccb) ;

      /* change state to SCCP_CONN_ESTABLISHED */
      sccp_change_state (p_coupled_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;
    }
    else
    {
      /* give N-RESET.conf to the user */
      sccp_build_n_reset_conf_api (p_info, p_ccb) ;
    }
  }
  else
  {
    /* Discard the message */
    sccp_discard_message (p_info) ;
  }
#endif    /* for class 3 services */

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the T_reset time out message from the peer in the RESET state 
**    of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_reset Timeout message 
**    from the peer in the connection reset phase.
**    When invoked it does the following :
**
**    o release resources and local reference
**    o build RLSD message and forward it to the route and translate
**      functionality of SCRC
**    o stop T_inact_send and T_inact_rec timers
**    o start T_rel timer
**    o send event alarm to SM
**    o if coupling present
**    o then
**      o change state to SCCP_CONN_CLOSING
**      o remove the association
**      o send RLSD on the associated conn section
**      o start T_rel timer
**      o change state to SCCP_CONN_CLOSING
**    o else
**      o give N-DISCONNECT.ind to the user
**      o change state to SCCP_CONN_CLOSING
**
*****************************************************************************/

return_t
sccp_conn_reset_t_reset_tmout
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t        *p_ccb ;
  sccp_ccb_t        *p_coupled_ccb ;
  return_t          result ;
  conn_entry_t 	    conn ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_reset_t_reset_tmout\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR #4584 Fix Start */
  if ( p_ccb->sccp_timer[SCCP_T_RESET_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
     return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_RESET_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
      /* SPR #4584 Fix End */  
 
		/** SPR 11179 - Fix Start **/		
#if 0
      /* release resources and local reference */
      sccp_release_resources (p_ccb) ;
#endif
		/** SPR 11179 - Fix End   **/		

      if (p_ccb->proto_class != PROTOCOL_CLASS_3)
      {
        SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
            ("SCCP::CO:Building ERR Message\n")) ;
        p_info->msg_type = ERR_MSG_TYPE ;
        p_info->error_cause = SCCP_ERRC_SERVICE_CLASS_MISMATCH ;
        sccp_utl_fill_nw_info (p_info, p_ccb) ;

        sccp_route_co_msg (p_info) ;

        /* Error */
        return (SS7_SUCCESS) ;
      }

     /* 
     * build RLSD message and forward it to the route and translate
     * functionality of SCRC
     */

     /* SPR # 2579 Fix Start */
     /* change state to SCCP_CONN_CLOSING */
     sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
     /* SPR # 2579 Fix End */

     p_info->msg_type = RLSD_MSG_TYPE ;
     p_info->rel_cause = SCCP_RLSDC_RESET_TIMER_EXPIRED;
     sccp_utl_fill_nw_info (p_info, p_ccb) ;

     sccp_route_co_msg (p_info) ;
		/** SPR 11179 - Fix Start **/		
      /* release resources and local reference */
      sccp_release_resources (p_ccb) ;
		/** SPR 11179 - Fix End   **/		

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

     /* start T_rel timer */
     result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
     if (result != SS7_SUCCESS)
     {
       /* Error */
     }

     /* send alarm to sm */
     conn.conn_id = p_info->conn_id;    
     SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, CONN_CLOSE, SS7_NULL, SS7_NULL, &conn);

     /* if coupling present */
     if (IS_COUPLING_PRESENT (p_ccb))
     {
       /* Get the coupled node */
       p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

       /* remove the association */
       sccp_remove_association (p_ccb, p_coupled_ccb) ;

       /* send RLSD on the associated conn section */
       p_info->msg_type = RLSD_MSG_TYPE ;
       p_info->rel_cause = SCCP_RLSDC_RESET_TIMER_EXPIRED;
       sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

       sccp_route_co_msg (p_info) ;

       /* start T_rel timer */
       result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_REL_TIMER, p_ecode) ;
       if (result != SS7_SUCCESS)
       {
         /* Error */
       }

       /* change state to SCCP_CONN_CLOSING */
       sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
     }
     else
     {
   	   p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
       /* give N-DISCONNECT.ind to the user */
       p_info->rel_cause = SCCP_RLSDC_RESET_TIMER_EXPIRED;
       sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
     }

    return (SS7_SUCCESS) ;
  }
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
