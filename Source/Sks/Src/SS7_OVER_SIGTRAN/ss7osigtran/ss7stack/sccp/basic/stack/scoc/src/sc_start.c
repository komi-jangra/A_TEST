/*****************************************************************************
**
**  FILE :
**    State Machine Functions for the Connection START state of the 
**    connection
**
******************************************************************************
**
**  FILENAME :
**    sc_start.c
**
**  DESCRIPTION :
**    This file contains all the functions handling the events for the START
**    state of the SCCP connections.
**
**  Date      Name             Reference     Reason
**  _________________________________________________________________________
**  01Jul'02  Suyash Tripathi                Fixed SPR 9126
**  03April'01  Pawanish Modi     Fixed SPR 8619
**  11Aug'01  Aman Kapoor		     Fixed SPR 5846
**  22Oct'01  Prateek Bidwalkar              Fixed SPR 6626
**  03Jul'01  Rajesh Mehta                   Fixed SPR 5527
**  22Nov'00  Hemlata Baudhwar               Fixed SPR 4584
**  06Jul'00  Ramu Kandula                   Fixed SPR 4052
**  08Jun'00  Ramu Kandula                   Fixed SPR 2574
**  15Feb'99  Sudipta Pattar                 Fixed SPR 1328
**  15Feb'99  Sudipta Pattar                 Fixed SPR 1328
**  08Jul'98  Praneet Khare    HSS:20800011  Original
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"

#ifdef SCCP_INCLUDE_CO_SERVICE
#ifdef SCCP_ANSI

/* SPR 9302 - Fix Start */
/* Already declared in sc_stpro.h */
/*extern U8bit sccp_get_min_scmg_message_priority
    _ARGS_((U8bit msg_type));*/
/* SPR 9302 - Fix End   */
#endif


/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-CONNECT.res from the User in the START state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-CONNECT.res from
**    the user in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_INCOMING
**    o then
**      o assign QOS to the incoming connection section
**      o build CC message and forward it to the route and translate
**        functionality of SCRC
**      o start T_inact_rec timer and T_inact_send timer
**      o change state to SCCP_CONN_ESTABLISHED
**
*****************************************************************************/

return_t
sccp_conn_start_n_conn_res
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t   *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_n_conn_res\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got N-CONNECT Response in SCCP_CONN_START State\n")) ;

  p_ccb = p_info->p_ccb;

  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_INCOMING)
  {
    /* Fill p_info related to CCB */
    /* assign QOS to the incoming connection section */

    if (p_info->proto_class < p_ccb->proto_class)
    {
      p_ccb->proto_class = p_info->proto_class ;
    }


    if (IS_CREDIT_IE_PRESENT (p_info))
    {
      if (p_info->credit < p_ccb->credit)
      {
        p_ccb->credit = p_info->credit ;
      }
	  else
	  {
		p_info->credit = p_ccb->credit ;
	  }
    }
	p_ccb->w = p_ccb->credit;

    /* start T_inact_rec timer and T_inact_send timer */
    result = sccp_start_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* 
     * build CC message and forward it to the route and translate
     * functionality of SCRC
     */
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
      ("SCCP::CO:Building CC Message\n")) ;
    p_info->msg_type = CC_MSG_TYPE ;

    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    /* Send the CC message to the SCRC for routing */
    sccp_route_co_msg (p_info) ;

    /* change state to SCCP_CONN_ESTABLISHED */
    sccp_change_state (p_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;

	/* SPR 10862 - Fix */
	p_ccb->l_id = p_info->l_id;
  }
    
  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the N-DISCONNECT.req from the User in the START state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-DISCONNECT.req from
**    the user in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_OUTGOING
**    o then
**      o set the wait for CC flag
**    o else
**      o release resources and local reference
**      o build CREF message and forward it to the route and translate 
**        functionality of SCRC
**      o change state to SCCP_CONN_CLOSED
**
*****************************************************************************/

return_t
sccp_conn_start_n_disc_req
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb ;
  return_t         result ;
#ifdef SCCP_REDN_ENABLED
  extern U8bit sccp_state;
#endif

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_n_disc_req\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got N-DISCONNECT Request in SCCP_CONN_START State\n")) ;

  /* 
   * check for corr_id and l_id IEs, if present the c_id is
   * to be ignored and get the local CCB based on {l_id, corr_id}
   */
  p_ccb = p_info->p_ccb;

  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
  {
	/** SPR # 2574 Fix Start **/
	
	/* CREF must not be sent here as the DLR is not known at this point;
	** we must wait for a message from the peer and initiate release procedure
	** as soon as we get the DLR
	*/

	p_ccb->wait_for_cc_flag = SS7_TRUE;
	SCCP_SEND_SCOC_ENTRY_UPDATE(p_ccb);

#if 0
    /* release resources and local reference */
    sccp_release_resources (p_ccb) ;

    /* 
     * build CREF message and forward it to the route and translate 
     * functionality of SCRC
     */
    p_info->msg_type = CREF_MSG_TYPE ;

    sccp_copy_sccp_addr (&p_ccb->cd_addr, &p_info->cd_addr);
    SET_CD_PRESENT (p_info) ;

    sccp_route_co_msg (p_info) ;

    /* start T_rel */
    result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* change state to SCCP_CONN_CLOSING */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
#endif
	/** SPR # 2574 Fix End **/
    /* SPR 9126 - Fix Start - changing state to idle */ 
    sccp_utl_clr_corr_id(p_ccb->l_id, p_ccb->corr_id);
    /* SPR 9126 - Fix End   */ 
  }
  else
  {
    /* release resources and local reference */
    sccp_release_resources (p_ccb) ;

    /* 
     * build CREF message and forward it to the route and translate 
     * functionality of SCRC
     */
    p_info->msg_type = CREF_MSG_TYPE ;

    sccp_route_co_msg (p_info) ;

    /* change state to SCCP_CONN_CLOSED */
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
**    Handles the CC from the peer in the START state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives CC from
**    the peer in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_INCOMING
**    o then
**      o discard the received message
**    o else
**      o if coupling associated with the local reference 
**      o then
**        o stop T_conn_est timer on the outgoing connection section
**        o start T_inact_rec and T_inact_send timers on the outgoing
**          connection section
**        o assign protocol class, credit, and the assocaited remote 
**          reference to the outgoing connection section
**        o change state to SCCP_CONN_ESTABLISHED
**        o get the associated connection control block
**        o assign local reference, SLS, protocol class, and credit to
**          the incoming connection section
**        o build CC message and forward it to route and translate 
**          functionality of SCRC
**        o start T_inact_rec and T_inact_send timers
**        o change state to SCCP_CONN_ESTABLISHED
**      o else
**        o stop T_conn_est timer
**        o stat T_inact_rec and T_inact_send timers
**        o assign QOS
**        o associate remote reference to the connection section
**        o give N-CONNECT.p_coupled_ccb->creditconf to the user
**        o change state to SCCP_CONN_ESTABLISHED
**
*****************************************************************************/

return_t
sccp_conn_start_cc
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_cc\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got CC in SCCP_CONN_START State\n")) ;

  p_ccb = p_info->p_ccb;

  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_INCOMING) 
  {
/* SPR 1338: Start fix */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
        {
    		/* discard the received message */
    		sccp_discard_message (p_info) ;
	}
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
		result = sccp_conn_start_comm_incoming_ansi (p_info, p_ecode);
		return (result);
	}
#endif
/* SPR 1338: End fix */
  } 
  else
  {
    /* stop T_conn_est timer for the connection section */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

	/** SPR # 2574 Fix Start **/

    p_ccb->dlr = p_info->slr ;
	p_ccb->dpc = p_info->opc ;

	/* Check of disconnect indication is already received */
	if (p_ccb->wait_for_cc_flag)
	{
		p_info->msg_type = RLSD_MSG_TYPE ;
		p_info->rel_cause = SCCP_RLSDC_SCCP_USER_ORIGINATED;
#ifdef SCCP_ANSI
		p_info->importance = sccp_get_min_scmg_message_priority(RLSD_MSG_TYPE);
#endif
		p_info->importance = 0;
		p_info->flag = 0; /* no optional parameters */
		sccp_utl_fill_nw_info (p_info, p_ccb) ;
 
		sccp_route_co_msg (p_info) ;

		/* start T_rel timer */
		result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
		if (result != SS7_SUCCESS)
		{
			/* Error */
		}
 
		/* change state to SCCP_CONN_CLOSING */
		sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;

  		return (SS7_SUCCESS) ;
	}

	/** SPR # 2574 Fix End **/

    /* 
     * start T_inact_rec and T_inact_send timers for the 
     * connection section
     */
    result = sccp_start_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
 
    /* 
     * assign protocol class, credit, and the associated remote 
     * reference to the outgoing connection section
     */
    if (p_info->proto_class < p_ccb->proto_class)
    {
      p_ccb->proto_class = p_info->proto_class ;
    }

 /* SPR 5527 fix starts */
   if (p_info->proto_class >  p_ccb->proto_class)
    {
      p_info->proto_class = p_ccb->proto_class ;
    }
 /* SPR 5527 fix ends */

	if (p_ccb->proto_class == PROTOCOL_CLASS_3)
	{
    	if (IS_CREDIT_IE_PRESENT (p_info))
    	{
      		if (p_info->credit < p_ccb->credit)
      		{
        		p_ccb->credit = p_info->credit ;
      		}
		}
    }
	else
		p_ccb->credit = 0;

	p_ccb->w = p_ccb->credit;

    /* change state to SCCP_CONN_ESTABLISHED */ 
    sccp_change_state (p_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;


    /* if coupling associated with the local reference  */
    if (IS_COUPLING_PRESENT (p_ccb))
    {
      /* get the associated connection control block */
      p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

      /* assign protocol class */
      p_coupled_ccb->proto_class = p_ccb->proto_class ;

      /* assign credit */
      p_coupled_ccb->credit = p_ccb->credit ;
      p_coupled_ccb->w = p_coupled_ccb->credit ;

      /* start T_inact_rec and T_inact_send timers */
      result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_IAR_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      /* change state to SCCP_CONN_ESTABLISHED */
      sccp_change_state (p_coupled_ccb, SCCP_CONN_ESTABLISHED, SS7_NULL) ;

      /*
       * build CC message and forward it to route and translate 
       * functionality of SCRC
       */
      SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building CC Message\n")) ;
      p_info->msg_type = CC_MSG_TYPE ;

      sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

      if (IS_RG_IE_PRESENT (p_info))
      {
			CLR_RG_IE_PRESENT (p_info);
      }
      sccp_route_co_msg (p_info) ;
/* SPR # 6626 : Fix Start */
	  sccp_utl_clr_corr_id(p_ccb->l_id, p_ccb->corr_id);
	  sccp_utl_clr_corr_id(p_coupled_ccb->l_id, p_coupled_ccb->corr_id);
/* SPR # 6626 : Fix End */

    }
    else
    {
      /* give N-CONNECT.conf to the user */
      sccp_build_n_connect_conf_api (p_info, p_ccb) ;
/* SPR # 6626 : Fix Start */
	  sccp_utl_clr_corr_id(p_ccb->l_id, p_ccb->corr_id);
/* SPR # 6626 : Fix End */
    }
  }
  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RLSD message from the peer in the START state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RLSD message from
**    the peer in the connection establishment phase.
**    When invoked it does the following :
**
**    o if substate == SCCP_INCOMING
**    o then
**      o discard the received message
**    o else
**      o if association involveed
**      o then
**        o stop T_conn_est timer
**        o release resources and the local reference number for outgoing 
**          connection section
**        o stop T_inact_rec and T_inact_send timers
**        o build RLC message and forward it to the route and translate 
**          functionallity of SCRC
**        o change state to SCCP_CONN_CLOSED
**        o get the associated connection control block
**        o remove the association
**        o stop T_inact_send and T_inact_rec timers
**        o build RLSD message and forward it to the route and translate
**          functionality of SCRC
**        o start T_rel
**        o change state to SCCP_CONN_CLOSING
**      o else
**	  o send N_DISCONNECT indication to the user
**
*****************************************************************************/

return_t
sccp_conn_start_rlsd
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_rlsd\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got RLSD in SCCP_CONN_START State\n")) ;

  /* get the connection control block for the connection */
  p_ccb = p_info->p_ccb;

  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_INCOMING)
  {
/* SPR 1338: Start fix */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
        {
    		/* discard the received message */
    		sccp_discard_message (p_info) ;
	}
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
		result = sccp_conn_start_rlsd_incoming_ansi (p_info, p_ecode);
	}
#endif
/* SPR 1338: End fix */
  }
  else
  {
    /* stop T_conn_est timer */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* SPR 1338: T_inact_rec and T_inact_send timers not running */

    p_ccb->dpc = p_info->opc ;
	/* SPR 8619 Fix Start **/
    p_ccb->dlr = p_info->slr ;
    /* SPR 8619 Fix end **/


    /* 
     * build RLC message and forward it to the route and translate 
     * functionallity of SCRC
     */
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building RLC Message\n")) ;
    p_info->msg_type = RLC_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    sccp_route_co_msg (p_info) ;

    /* 
     * release resources and the local reference number for outgoing 
     * connection section
     */
    sccp_release_resources (p_ccb) ;

    /* change state to SCCP_CONN_CLOSED */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

    /* start T_freeze */
    result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
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

    /* SPR 1338: T_inact_rec and T_inact_send timers not running */

      /* start T_rel */
      result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_REL_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      /* 
       * build RLSD message and forward it to the route and translate
       * functionality of SCRC
       */
      SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building RLSD Message\n")) ;
      p_info->msg_type = RLSD_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

      /* Send the message to the SCRC */
      sccp_route_co_msg (p_info) ;

      /* change state to SCCP_CONN_CLOSING */
      sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SCCP_OUTGOING) ;
    }
    else
    {
      /* SPR 1338: Start fix 
       * Send N_DISCONNECT indication to user 
       */
      p_info->corr_id = p_ccb->corr_id;
      SET_CORR_ID_PRESENT (p_info);
      p_info->originator = sccp_utl_get_rlsd_originator (p_info->rel_cause) ;
      sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
      /* SPR 1338: End fix */
    }
	
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RouteFail message from the SCRC in the START state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RouteFail message from
**    the SCRC in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_OUTGOING
**    o then
**      o stop T_conn_est
**      o release all resources and local references
**      o change state to SCCP_CONN_CLOSED
**      o remove the association
**      o get the associated connection control block
**      o build CREF message and forward it to the route and translate
**        functionality of SCRC
**      o change state to SCCP_CONN_CLOSED
**
*****************************************************************************/

return_t
sccp_conn_start_routefail
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_routefail\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got RouteFail in SCCP_CONN_START State\n")) ;

  /* get the ccb */
  p_ccb = p_info->p_ccb;

  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
  {
	/** SPR # 4052 Fix Start **/

	if (IS_COUPLING_PRESENT (p_ccb))
	{
    	/* get the associated connection control block */
    	p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

   	 	/* remove the association */
    	sccp_remove_association (p_ccb, p_coupled_ccb) ;

    	/* 
     	* build CREF message and forward it to the route and translate
     	* functionality of SCRC
     	*/

		/* SPR # 2579 Fix Start */
    	/* change state to SCCP_CONN_CLOSED */
    	sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
		/* SPR # 2579 Fix End */

    	SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
       	 ("SCCP::CO:Building CREF Message\n")) ;
    	p_info->msg_type = CREF_MSG_TYPE ;
    	p_info->dlr = p_coupled_ccb->dlr ;
    	p_info->dpc = p_coupled_ccb->dpc ;
    	p_info->opc = p_coupled_ccb->opc ;
        CLR_CD_PRESENT (p_info);


    	/* Send the message to the SCRC for routing */
    	sccp_route_co_msg (p_info) ;

    	/* start T_freeze */
    	result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      	/* Error */
    	}
	}
	else
	{
    	p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause) ;
    	sccp_build_n_disconnect_ind_api (p_info, p_ccb);	

    	/* stop T_conn_est */
    	result = sccp_stop_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      	/* Error */
    	}
	
    	/* release all resources and local references */
    	sccp_release_resources (p_ccb) ;
	
    	/* change state to SCCP_CONN_CLOSED */
    	sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
	
    	/* start T_freeze */
    	result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      	/* Error */
    	}
	}

	/** SPR # 4052 Fix End **/
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the CREF message from the peer in the START state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives CREF message from
**    the peer in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_OUTGOING
**    o then
**      o stop T_conn_est
**      o release all resources and local references
**      o change state to SCCP_CONN_CLOSED
**      o get the associated connection control block
**      o remove the association
**      o build CREF message and forward it to the route and translate
**        functionality of SCRC
**      o change state to SCCP_CONN_CLOSED
**    o else
**      o discard message (SPR 1338 - ITU)
**
*****************************************************************************/

return_t
sccp_conn_start_cref
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_cref\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got CREF message in SCCP_CONN_START State\n")) ;

  p_ccb = p_info->p_ccb;
  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING) 
  {
    	/* stop T_conn_est */
    	result = sccp_stop_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      		/* Error */
    	}
	p_info->corr_id = p_ccb->corr_id;
	SET_CORR_ID_PRESENT (p_info);
  }
  /* SPR 1338: Start fix */
  else
  { 
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
		result = sccp_conn_start_comm_incoming_ansi (p_info, p_ecode);
		return (result);
	}
#endif
  }
  /* SPR 1338: End fix */

  if (IS_COUPLING_PRESENT (p_ccb))
  {

    /* release all resources and local references */
    sccp_release_resources (p_ccb) ;

    /* change state to SCCP_CONN_CLOSED */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

    /* start T_freeze */
    result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* get the associated connection control block */
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

    /* remove the association */
    sccp_remove_association (p_ccb, p_coupled_ccb) ;

	if ((p_coupled_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING) 
	{
    	/* stop T_conn_est */
    	result = sccp_stop_co_timer (p_coupled_ccb, SCCP_T_CONNEST_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      		/* Error */
    	}
	}
    /* 
     * build CREF message and forward it to the route and translate
     * functionality of SCRC
     */
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building CREF Message\n")) ;
    p_info->msg_type = CREF_MSG_TYPE ;
    sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

    /* SPR 1328: Start fix 
     * Send the message to the SCRC 
     */
    sccp_route_co_msg (p_info) ;
    /* SPR 1328: End fix */

    /* change state to SCCP_CONN_CLOSED */
    sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

    /* start T_freeze */
    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
  }
  else
  {
	/** SPR # 2574 Fix Start **/
	if (! p_ccb->wait_for_cc_flag)
	{
    	p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause) ;
    	sccp_build_n_disconnect_ind_api (p_info, p_ccb);	
	}
	/** SPR # 2574 Fix End **/

    /* release all resources and local references */
    sccp_release_resources (p_ccb) ;

    /* change state to SCCP_CONN_CLOSED */
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
**    Handles the T_conn_est timeout in the START state of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_conn_est timeout 
**    in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if substate == SCCP_OUTGOING
**    o then
**      o if associated connection control block is there (intermediate node)
**      o then
**        o release all resources and local reference
**        o if request type 2 was used give N-DISCONNECT.ind to the user
**        o build RLSD and forward it to the route and translation 
**          functionality of SCRC
**        o start T_rel
**        o change state to SCCP_CONN_CLOSING
**        o get the associated connection control block
**        o remove the association
**        o build CREF message and forward it to the route and translate
**          functionality of SCRC
**        o change state to SCCP_CONN_CLOSED
**      o else
**        o release resources and local reference
**        o give N-DISCONNECT.ind to the user
**        o change state to SCCP_CONN_CLOSED
**
*****************************************************************************/

return_t
sccp_conn_start_t_connest_tmout
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_t_connest_tmout\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got CONNECTION ESTABLISMENT TIMER Timeout message in SCCP_CONN_START State\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR #4584 Fix Start */  
  if ( p_ccb->sccp_timer[SCCP_T_CONNEST_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_CONNEST_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */  

      if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
      {
	    if ((p_ccb->c_status & SCCP_USER_TYPE_MASK) == SCCP_TYPE_A_USER)
	    {
           /* release all resources and local reference */
           sccp_release_resources (p_ccb) ;

          /* start T_freeze */
          result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
          if (result != SS7_SUCCESS)
          {
            /* Error */
          }

          /* change state to SCCP_CONN_CLOSED */
          sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

          /* get the associated connection control block */
          p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

          /* remove the association */
          sccp_remove_association (p_ccb, p_coupled_ccb) ;

         /* 
          * build CREF message and forward it to the route and translate
          * functionality of SCRC
          */
          SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
            ("SCCP::CO:Building CREF Message\n")) ;
          p_info->rel_cause = SCCP_RFC_CONNECTION_ESTABLISHMENT_TIMER_EXPIERD ;
          p_info->msg_type = CREF_MSG_TYPE ;
          sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
	      p_info->nw_id = DEFAULT_NW_ID ;

          sccp_route_co_msg (p_info) ;

          /* change state to SCCP_CONN_CLOSED */
          sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

          /* start T_freeze */
          result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
          if (result != SS7_SUCCESS)
          {
            /* Error */
          }
          return (SS7_SUCCESS) ;
	    }

	    p_info->opc = p_ccb->opc ;

	   /* SPR GR: CCB does not contain the cd_addr */
#if 0
	   sccp_copy_sccp_addr (&p_ccb->cd_addr, &p_info->cd_addr) ;
	   SET_CD_PRESENT (p_info) ;
#endif

       /* if associated connection control block is there (intermediate node) */
       if (IS_COUPLING_PRESENT (p_ccb))
       {
          /* release all resources and local reference */
          sccp_release_resources (p_ccb) ;

          /* assign release cause */
          p_info->rel_cause = SCCP_RFC_CONNECTION_ESTABLISHMENT_TIMER_EXPIERD ;

         /* SPR GR: Since no dpc or cd_addr is available, dont send RLSD 
          * close connection internally 				    */
#if 0
         /* 
          * build RLSD and forward it to the route and translation 
          * functionality of SCRC
          */
          SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
            ("SCCP::CO:Building RLSD Message\n")) ;
          p_info->msg_type = RLSD_MSG_TYPE ;
          sccp_utl_fill_nw_info (p_info, p_ccb) ;

          sccp_route_co_msg (p_info) ;

          /* start T_rel */
          result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
          if (result != SS7_SUCCESS)
          {
             /* Error */
          }
 
          /* change state to SCCP_CONN_CLOSING */
          sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
#endif

          /* change state to SCCP_CONN_CLOSED */
          sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

          /* start T_freeze */
          result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
          if (result != SS7_SUCCESS)
          {
             /* Error */
          }

          /* get the associated connection control block */
          p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

          /* remove the association */
          sccp_remove_association (p_ccb, p_coupled_ccb) ;

          /* 
           * build CREF message and forward it to the route and translate
           * functionality of SCRC
           */
          SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
             ("SCCP::CO:Building CREF Message\n")) ;
          p_info->msg_type = CREF_MSG_TYPE ;
          sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;

          sccp_route_co_msg (p_info) ;

          /* change state to SCCP_CONN_CLOSED */
          sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

          /* start T_freeze */
          result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
          if (result != SS7_SUCCESS)
          {
            /* Error */
          }
        }
        else
        {
          /* release resources and local reference */
          sccp_release_resources (p_ccb) ;
	  /* SPR 9126 - Fix Start */
	  if ( !(p_ccb->wait_for_cc_flag) )
	  {
	  /* SPR 9126 - Fix End   */
	  /* SPR # 5846 ...Fix Starts */
           /*SPR GR: This refusal cause maps to the release 
           * cause: reset_timer expiry */
           p_info->rel_cause = SCCP_RFC_CONNECTION_ESTABLISHMENT_TIMER_EXPIERD ;
           

          /* p_info->rel_cause = SCCP_RLSDC_UNQUALIFIED ;*/
	  /*SPR # 5846 ....Fix Ends */
	      p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause);

          /* set corr_id field */
          p_info->corr_id = p_ccb->corr_id;
          SET_CORR_ID_PRESENT (p_info);

          /* give N-DISCONNECT.ind to the user */
          sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
	  /* SPR 9126 - Fix Start */
	  }
	  /* SPR 9126 - Fix End   */

          /* change state to SCCP_CONN_CLOSED */
          sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

          /* start T_freeze */
          result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
          if (result != SS7_SUCCESS)
          {
            /* Error */
          }
        }
      }
      return (SS7_SUCCESS) ;
  }
}


/* SPR 1338: Function added */
/*****************************************************************************
**
**  FUNCTION :
**
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it does the following :
**    
**    o if substate == SCCP_OUTGOING
**    o then
**      o stop T_conn_est
**	o if slr present in message (and if coupled node - ITU-T)
**	  o send RLSD message 
**	  o start T_rel timer
**	  o change state to SCCP_CONN_CLOSING
**	  o if association present
**	    o remove association
**	    o send RLSD on associated section
**	    o start T_rel timer
**	    o change state to SCCP_CONN_CLOSING
**	  o else
**	    o send N_DISCONNECT indication to user
**    	o else if slr not present (or if end node - ITU-T)
**	  o release resources 
**	  o start T_freeze timer
**	  o change state to SCCP_CONN_CLOSED
**	  o if association present
**	    o remove association
**	    o send CREF on associated section
**	    o change state to SCCP_CONN_CLOSED
**	  o else
**	    o send N_DISCONNECT indication to user
**    o else if substate = SCCP_INCOMING
**      o discard the received message - ITU-T
**	o call function to process message - ANSI
**
*****************************************************************************/

return_t
sccp_conn_start_comm_func
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result = SS7_SUCCESS ;
  Boolean	   itu_end_node = SS7_FALSE;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_comm_func\n")) ;

  p_ccb = p_info->p_ccb;

  if ((p_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
  { 
    /* stop T_conn_est */
    result = sccp_stop_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }

    /* if SLR present in message */


#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
	if (!(IS_COUPLING_PRESENT (p_ccb)))
    		itu_end_node = SS7_TRUE;
  }
  
#endif 

    /* if slr is present in the message, or
     * for ITU-T, if it is a coupling node 
     */

    if (is_slr_present(p_info->event) &&
	(!itu_end_node))
    {
       	/* build RLSD message */

      	SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
      	 ("SCCP::CO:Building RLSD Message\n")) ;
      	p_info->msg_type = RLSD_MSG_TYPE ;
	p_ccb->dlr = p_info->slr ;
	p_ccb->dpc = p_info->opc ;
        SC_STAT_Q752_TS_PROVIDER_INIT_RLSD;
        SC_STAT_Q752_INR_PROVIDER_INIT_RLSD;
	p_info->rel_cause = SCCP_RLSDC_REMOTE_PROCEDURE_ERROR ;
      	sccp_utl_fill_nw_info (p_info, p_ccb) ;

      	/* Send the message to the SCRC */
      	sccp_route_co_msg (p_info) ;

 
      	/* start T_rel */
      	result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
      	if (result != SS7_SUCCESS)
      	{
       	 /* Error */
      	}

      	/* change state to SCCP_CONN_CLOSING */
      	sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SCCP_OUTGOING) ;
	
   	if (IS_COUPLING_PRESENT (p_ccb))
    	{
      	    /* get the associated connection control block */
      	    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
 
      	    /* remove the association */
      	    sccp_remove_association (p_ccb, p_coupled_ccb) ;

    	    /* start T_rel timer */
    	    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_REL_TIMER, 
								p_ecode) ;
    	    if (result != SS7_SUCCESS)
    	    {
      	    /* Error */
    	    }
 
    	    /*
     	    * build RLSD message and forward it to translate and route
     	    * functionality of SCRC
     	    */
      	    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        	("SCCP::CO:Building RLSD Message\n")) ;

    	    p_info->msg_type = RLSD_MSG_TYPE ;
    	    sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
 
    	    sccp_route_co_msg (p_info) ;
 
    	    /* change state to SCCP_CONN_CLOSING */
    	    sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;
	}		/* is coupling present */
	else
	{
	    /* set corr id field */
	    p_info->corr_id = p_ccb->corr_id;
	    SET_CORR_ID_PRESENT (p_info);

	    /* Send N_DISCONECT indication to user */
    	    p_info->originator = sccp_utl_get_cref_originator 
						(p_info->rel_cause) ;
    	    sccp_build_n_disconnect_ind_api (p_info, p_ccb);

	}

    }		/* is slr present or if coupled node */
    else
    {

    	/* release resources and local reference */
    	sccp_release_resources (p_ccb) ;
	
    	/* change state to SCCP_CONN_CLOSED */
    	sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
    	/* start T_freeze */
    	result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
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

     	   /* build CREF message and forward it to the route and translate
     	    * functionality of SCRC
     	    */
    	   SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        		("SCCP::CO:Building CREF Message\n")) ;
    	   p_info->msg_type = CREF_MSG_TYPE ;
    	   sccp_utl_fill_nw_info (p_info, p_coupled_ccb) ;
 
    	   sccp_route_co_msg (p_info) ;
 
    	   /* change state to SCCP_CONN_CLOSED */
    	   sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
    	   /* start T_freeze */
    	   result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, 
							p_ecode) ;
    	   if (result != SS7_SUCCESS)
    	   {
      	   /* Error */
    	   }
	}     	/* is coupling present */
	else
	{
	    /* Send N_DISCONECT indication to user */
	    p_info->corr_id = p_ccb->corr_id;
	    SET_CORR_ID_PRESENT (p_info);
	    p_info->rel_cause = SCCP_RLSDC_REMOTE_PROCEDURE_ERROR ;
            SC_STAT_Q752_TS_PROVIDER_INIT_RLSD;
            SC_STAT_Q752_INR_PROVIDER_INIT_RLSD;
    	    p_info->originator = sccp_utl_get_cref_originator 
							(p_info->rel_cause) ;
    	    sccp_build_n_disconnect_ind_api (p_info, p_ccb);
	}
    } 		/* slr not present */    

  }		/* substate = outgoing */
  else
  {
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
        {
    		/* discard the received message */
    		sccp_discard_message (p_info);
	}
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
        if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
		result = sccp_conn_start_comm_incoming_ansi (p_info, p_ecode);
	}
#endif
  }
  return (result);
}



/* SPR 1338: Function added */
/*****************************************************************************
**
**  FUNCTION :
**	Handles messsages when substate = SCCP_INCOMING for ANSI
**	
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it does the following :
**
**    o if coupled node
**       o send CREF message
**       o release resources, and freeze local ref
**       o change CONN to CONN_CLOSED
**       o get coupled section
**       o stop conn est timer for coupled section
**       o release resuorces and freeze ref
**       o change state to CONN_CLOSED
**    o else
**       o send RLSD
**       o start rel 
**       o change state to CONN_CLOSING
**       o send n_disc_ind to user
**
**
*****************************************************************************/



return_t
sccp_conn_start_comm_incoming_ansi
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_comm_incoming_ansi\n")) ;

  p_ccb = p_info->p_ccb;

  /* if coupling present */
  if (IS_COUPLING_PRESENT (p_ccb))
  {
    	/*
      	 * build CREF message and forward it to the route and translate
         * functionality of SCRC
     	 */
    	p_info->msg_type = CREF_MSG_TYPE ;
	p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;
      	sccp_utl_fill_nw_info (p_info, p_ccb) ;

    	sccp_route_co_msg (p_info) ;

        /* release all resources and local reference */
        sccp_release_resources (p_ccb) ;

       /* change state to SCCP_CONN_CLOSED */
       sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
       /* start T_freeze */
       result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
       if (result != SS7_SUCCESS)
       {
         /* Error */
       }

       /* get the associated connection control block */
       p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
 
       /* remove the association */
       sccp_remove_association (p_ccb, p_coupled_ccb) ;
 
       if ((p_coupled_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
       {
        	/* stop T_conn_est */
        	result = sccp_stop_co_timer (p_coupled_ccb, 
					SCCP_T_CONNEST_TIMER, p_ecode) ;
        	if (result != SS7_SUCCESS)
        	{
               	 /* Error */
        	}
        }

    	/* change state to SCCP_CONN_CLOSED */
    	sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
    	/* start T_freeze */
    	result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, 
								p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      		/* Error */
    	}
  }		/* is coupled node */
  else
  {
	/*
         * build RLSD and forward it to the route and translation
         * functionality of SCRC
         */
      	SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
       	 ("SCCP::CO:Building RLSD Message\n")) ;
      	p_info->msg_type = RLSD_MSG_TYPE ;
	p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;
      	sccp_utl_fill_nw_info (p_info, p_ccb) ;
 
      	sccp_route_co_msg (p_info) ;
 
      	/* start T_rel */
      	result = sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
      	if (result != SS7_SUCCESS)
      	{
        /* Error */
      	}
 
      	/* change state to SCCP_CONN_CLOSING */
      	sccp_change_state (p_ccb, SCCP_CONN_CLOSING, SS7_NULL) ;

        p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause);
	p_info->corr_id = p_ccb->corr_id;
	SET_CORR_ID_PRESENT (p_info);

      	/* give N-DISCONNECT.ind to the user */
      	sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

  }
  return (SS7_SUCCESS);
}


/* SPR 1338: Function added */
/*****************************************************************************
**
**  FUNCTION :
**	Handles the RLSD messsage when substate = SCCP_INCOMING
**	
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it does the following :
**
**    o if coupled node
**       o send CREF to incoming section
**       o release resources, and freeze local ref
**       o change CONN to CONN_CLOSED
**       o get coupled section
**       o stop conn est timer for coupled section
**       o release resuorces and freeze ref
**       o change state to CONN_CLOSED
**    o else
**       o send RLC
**       o release resources
**       o change state to SCCP_CONN_CLOSED
**	 o start T_freeze
**       o n_disc_ind to user
**
**
*****************************************************************************/



return_t
sccp_conn_start_rlsd_incoming_ansi
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t       *p_ccb, *p_coupled_ccb ;
  return_t         result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_start_rlsd_incoming_ansi\n")) ;

  p_ccb = p_info->p_ccb;

  /* if coupling present */
  if (IS_COUPLING_PRESENT (p_ccb))
  {
    	/*
      	 * build CREF message and forward it to the route and translate
         * functionality of SCRC
     	 */
    	p_info->msg_type = CREF_MSG_TYPE ;
	p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;
      	sccp_utl_fill_nw_info (p_info, p_ccb) ;

    	sccp_route_co_msg (p_info) ;

        /* release all resources and local reference */
        sccp_release_resources (p_ccb) ;

       /* change state to SCCP_CONN_CLOSED */
       sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
       /* start T_freeze */
       result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
       if (result != SS7_SUCCESS)
       {
         /* Error */
       }

       /* get the associated connection control block */
       p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
 
       /* remove the association */
       sccp_remove_association (p_ccb, p_coupled_ccb) ;
 
       if ((p_coupled_ccb->c_status & SCCP_SUBSTATE_MASK) == SCCP_OUTGOING)
       {
        	/* stop T_conn_est */
        	result = sccp_stop_co_timer (p_coupled_ccb, 
						SCCP_T_CONNEST_TIMER, p_ecode) ;
        	if (result != SS7_SUCCESS)
        	{
               	 /* Error */
        	}
        }

    	/* change state to SCCP_CONN_CLOSED */
    	sccp_change_state (p_coupled_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
    	/* start T_freeze */
    	result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_FREEZE_TIMER, 
								p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      		/* Error */
    	}
  }		/* is coupled node */
  else
  {
   	/*
     	 * build RLC message and forward it to the route and translate
         * functionallity of SCRC
         */
    	SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
       	 ("SCCP::CO:Building RLC Message\n")) ;
    	p_info->msg_type = RLC_MSG_TYPE ;
    	sccp_utl_fill_nw_info (p_info, p_ccb) ;
 
    	sccp_route_co_msg (p_info) ;

    	/*
         * release resources and the local reference number for outgoing
         * connection section
         */
    	sccp_release_resources (p_ccb) ;

    	/* change state to SCCP_CONN_CLOSED */
    	sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
 
    	/* start T_freeze */
    	result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
    	if (result != SS7_SUCCESS)
    	{
      	/* Error */
    	}
 
	p_info->corr_id = p_ccb->corr_id;
	SET_CORR_ID_PRESENT (p_info);
        p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause);

      	/* give N-DISCONNECT.ind to the user */
      	sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

  }
  return (SS7_SUCCESS);
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
