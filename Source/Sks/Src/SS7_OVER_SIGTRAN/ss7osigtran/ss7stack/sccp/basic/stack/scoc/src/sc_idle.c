/*****************************************************************************
**
**  FILE :
**    State Machine Functions for the IDLE state of the connection
**
******************************************************************************
**
**  FILENAME :
**    sc_idle.c
**
**  DESCRIPTION :
**    This file contains all the functions handling the events for the IDLE
**    state of the SCCP connections.
**
**  Date    Name        Reference    Reason
**  _________________________________________________________________________
**  13May04   Suyash/Ganesh                Fixed SPR 13444
**  30jul02   Suyash Tripathi       Fixed SPR 9404
**  25Sep01   Prateek Bidwalkar     Fixed SPR 6246
**  11Sep01   Prateek Bidwalkar     Fixed SPR 6126
**  25May01   Rajesh Mehta          changed corr id to U16 in case
**                                  SCCP_CONNECTION_ID_CHANGES is defined
**  07Jun'00  Ramu Kandula          Fixed SPR # 2579 - Change state before
**                                  sending message to SCRC
**  12Oct'99  Ramu Kandula          set the p_ss field of p_ccb & 
**                                  p_out_ccb correctly in 
**                                  sccp_conn_idle_req_type_2
**  29Apr'99  Sudipta Pattar                 Fixed SPR 1500
**  15Feb'99  Sudipta Pattar                 Fixed SPR 1337
**  15Feb'99  Sudipta Pattar                 Fixed SPR 1332
**  15Feb'99  Sudipta Pattar                 Fixed SPR 1331
**  07Feb'99  Sudipta Pattar                 Added Ericsson changes
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
**    Handles the N-CONNECT.req from the User in the IDLE state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives N-CONNECT.req from
**    the user in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if resources are available
**    o then
**      o assign local reference 
**      o assign SLS
**      o decide QOS
**      o build CR and call the sccp_route_co_mesg
**      o change the state of the connection to SCCP_CONN_START and
**        substate to SCCP_OUTGOING
**    o else
**      o send N-DISCONNECT.ind to the User
**
*****************************************************************************/

return_t
sccp_conn_idle_n_conn_req
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t   *p_info ;
  error_t      *p_ecode ;
#endif
{
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit       corr_id ;  /* Amaresh Changes U16bit -U32bit */
#else
  U8bit       corr_id ;
#endif
  U16bit      l_user_id ;
  U8bit       protocol_class ;
  sccp_ccb_t  *p_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_n_conn_req\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Got N-CONNECT Request in SCCP_CONN_IDLE State\n")) ;

  corr_id = p_info->corr_id ;
  l_user_id = p_info->l_id ;
  p_ccb = p_info->p_ccb;

  /* Get the sp entry from the database on the basis of logical user id */
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("SCCP::SCOC: Before sccp_utl_get_sp_from_logid\n")) ;
  sccp_utl_get_sp_from_logid (p_info, l_user_id) ;
  if ((p_info->p_sp == (sp_entry_t *)SS7_NULL) ||
      (p_info->p_ss == (ss_entry_t *)SS7_NULL))
  {
    return (SS7_FAILURE) ;
  }

  /* validate the NSU */
  if (IS_SSID_VALID (GET_ID_FROM_SS(p_info->p_ss)))
  {
    if (!IS_SS_CONFIGURED (p_info->p_ss))
      return (SS7_FAILURE) ;
  }
  else
  {
    return (SS7_FAILURE) ;
  }

  /* 
   * Search for the ccb on the basic of logical user id and the correlation 
   * id and the state of the ccb as Start 
   */

#if 0
  if ((sccp_utl_get_ccb (SCCP_CONN_START, l_user_id, corr_id)) 
                                               != (sccp_ccb_t *)SS7_NULL)
  {
    /* It is a duplicate n_connect_request. Ignore it. */
    SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
        ("SCCP::CO: Duplicate N-CONNECT Request LogUId[%d] CorrId[%d]\n",
        l_user_id, corr_id));

    /* release the CCB */
    p_info->p_ccb = (sccp_ccb_t *)SS7_NULL;
    *p_ecode = ESCCP_DUPLICATE_CONN_REQ ;

    /* Generate an ERROR */
    SCCP_ERR (*p_ecode, STACK_PROTOCOL_ERROR, MAJOR_ERROR) ;

    return (SS7_FAILURE);
  }
#endif /* Commented by Amaresh for CCB bcz sccp_ccb not used inside the function & multiple time searching time waist as on dated 11-03-16*/

  p_ccb->l_id = l_user_id;
  p_ccb->p_ss = p_info->p_ss ;
  p_ccb->opc = GET_SP_PC (GET_SP_OF_SS(p_ccb->p_ss));

  /* Clear off the corr_id from the connected CCBs */
  sccp_utl_clr_corr_id (l_user_id, corr_id);

  /* changed: copy corr-id into connection block */
  p_ccb->corr_id = corr_id;


  protocol_class = p_info->proto_class;

  /* Ericsson changes - protocol class 3 not supported */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
  {
      if (protocol_class == PROTOCOL_CLASS_3)
          protocol_class = PROTOCOL_CLASS_2;
  }
#endif

  p_info->p_ccb = p_ccb;
  /* Initialise the Connection Control Block */
  sccp_utl_init_ccb (p_ccb, protocol_class);

  /* Get the Called address parameter */
  sccp_copy_sccp_addr (&p_info->cd_addr, &p_ccb->cd_addr);

  /* SPR # 6246 Fix Start */
  /* p_info->sls contains junk; So sls must be assigned using sccp_assign_sls()
  ** function instead;
  */
  /* NOTE :: cg addr and sls does not contain valid information and must 
  ** not be used inside sccp_assign_sls() function for computing sls in 
  ** case of class 2 and class 3; 
  */
  /* SPR 9404 - Fix Start */
  /*p_ccb->sls = sccp_assign_sls (&p_info->cd_addr, 
            &p_info->cg_addr, p_info->sls, p_ccb->proto_class & 0xf);*/
 /* SPR 13444 - Fix Start */
 /* p_ccb->sls = sccp_assign_sls (&p_info->cd_addr, 
            &p_info->cg_addr, p_info->sls, (U8bit)(p_ccb->proto_class & 0xf));*/
  /*p_ccb->sls = sccp_assign_sls (&p_info->cg_addr,
            &p_info->cd_addr, p_info->sls, (U8bit)(p_ccb->proto_class & 0xf));*/
  /* SPR 13444 - Fix stop */

  /* SPR 9404 - Fix End   */

	

  /* p_ccb->sls = p_info->sls; -- Obsolete Code -- prior to fix #6246  */

  /* SPR # 6246 Fix End */

  /* 
   * SCCP selected protocol class may be different then
   * the NSU proposed class due to resource limitations.
   * Adjust the proto_class.
   */
  p_info->proto_class = p_ccb->proto_class;

  /* Fill in the network info */
  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
       ("SCCP::CO: Building CR Message\n")) ;
  p_info->msg_type = CR_MSG_TYPE;

  /* CD addr is already in p_info */
  SET_CD_PRESENT (p_info);

  /* mtp_nw_id associated with the logical user */
  p_info->nw_id = sccp_utl_get_mtp_nw_id (l_user_id);

  /* Adjust the negotiable parameters */
  if (p_ccb->proto_class == PROTOCOL_CLASS_3)
  {
    if (IS_CREDIT_IE_PRESENT (p_info))
    {
      if (p_info->credit < p_ccb->credit)
          p_ccb->credit = p_info->credit;
      else
          p_info->credit = p_ccb->credit;
    }
    else
    {
      SET_CREDIT_PRESENT (p_info);
      p_info->credit = SCCP_DEFAULT_CREDIT;
    }

    if (IS_ED_SELECTION_PRESENT (p_info))
      p_ccb->c_status |= SCCP_ED_SELECTED;
  }

  /* start up the connection establishment timer */
  if (SS7_SUCCESS != sccp_start_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode))
  {
    /* release the connection */
    /* release resources and local reference */
    sccp_release_resources (p_ccb) ;

    /*
     * build CREF message and forward it to the route and translate
     * functionality of SCRC
     */
 
    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSED */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
    /* SPR # 2579 Fix End */
 
    p_info->msg_type = CREF_MSG_TYPE ;
 
    sccp_route_co_msg (p_info) ;

    /* start T_freeze */
    (void)sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;

    return (SS7_SUCCESS) ;
  }
 
  /** SPR # 2579 Fix Start **/
  /* Change the state to Connection start and sub state to out going */
  sccp_change_state (p_ccb, SCCP_CONN_START, SCCP_OUTGOING) ;
  /** SPR # 2579 Fix End **/
  
  /*  invoke scrc function */
  sccp_route_co_msg (p_info) ;


  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the Request Type 1 from the User in the IDLE state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives request Type 1 from
**    the user in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if resources are available
**    o then
**      o assign local reference 
**      o assign SLS
**      o decide QOS
**      o build CR and forward its information elements to the SCCP user 
**        thru Reply primitive
**      o change the state of the connection to SCCP_CONN_START and
**        substate to SCCP_OUTGOING
**    o else
**      o send N-DISCONNECT.ind to the User
**
*****************************************************************************/

return_t
sccp_conn_idle_req_type_1
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit        corr_id ; /* Amaresh U16 U32 */
#else
  U8bit        corr_id ;
#endif
  U16bit       l_user_id ;
  U8bit        protocol_class ;
  sccp_ccb_t   *p_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_req_type_1\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO: Got REQUEST TYPE 1 in SCCP_CONN_IDLE State\n")) ;

  corr_id = p_info->corr_id ;
  l_user_id = p_info->l_id ;
  p_ccb = p_info->p_ccb;

  /* get the sp pointer from the database from the logical user id */
  sccp_utl_get_sp_from_logid (p_info, l_user_id) ;
  if ((p_info->p_sp == (sp_entry_t *)SS7_NULL) ||
      (p_info->p_ss == (ss_entry_t *)SS7_NULL))
  {
    return (SS7_FAILURE) ;
  }

  /* validate the NSU */
  if (IS_SSID_VALID (GET_ID_FROM_SS(p_info->p_ss)))
  {
    if (!IS_SS_CONFIGURED (p_info->p_ss))
    return (SS7_FAILURE) ;
  }
  else
  {
    return (SS7_FAILURE) ;
  }

  /* 
   * Search for a ccb based on logical user id and the correlation id and 
   * connection state as Start
   */
  if ((sccp_utl_get_ccb (SCCP_CONN_START, l_user_id, corr_id)) 
      != (sccp_ccb_t *)SS7_NULL)
  {
    /* It is a duplicate n_connect_request. Ignore it. */
    SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
        ("SCCP::CO: Duplicate REQUEST Type 1 LogUId[%d] CorrId[%d]\n",
        l_user_id, corr_id));
    
    /* Generate an ERROR */
    SCCP_ERR (ESCCP_DUPLICATE_CONN_REQ, STACK_PROTOCOL_ERROR, MAJOR_ERROR) ;

    p_info->p_ccb = (sccp_ccb_t *)SS7_NULL;
    *p_ecode = ESCCP_DUPLICATE_CONN_REQ ;
    return (SS7_FAILURE);
  }
/* Commented  removed by Amaresh for TEMPORARY sccp_utl_get_ccb calling sccp_conn_idle_req_type_1 */
  /* Clear off corr_id */
  sccp_utl_clr_corr_id (l_user_id, corr_id);

  p_ccb->corr_id = corr_id;
  p_ccb->l_id = l_user_id;
  p_ccb->p_ss = p_info->p_ss ;
  p_ccb->opc = GET_SP_PC (GET_SP_OF_SS(p_ccb->p_ss));

  protocol_class = p_info->proto_class;
  p_info->p_ccb = p_ccb;
  p_info->conn_id = p_ccb->conn_id ;

  /* Initialise the CCB based on the Protocol class */
  sccp_utl_init_ccb (p_ccb, protocol_class);

  /* Fill in the SLS */
  p_ccb->sls = p_info->sls;


  /* 
   * SCCP selected protocol class may be different then
   * the NSU proposed class due to resource limitations.
   */
  sccp_utl_fill_nw_info (p_info, p_ccb) ;

  SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
      ("SCCP::CO:Building CR Message\n")) ;
  p_info->msg_type = CR_MSG_TYPE;

  /* Get the Called address parameter */
  sccp_copy_sccp_addr (&p_info->cd_addr, &p_ccb->cd_addr);

  /* mtp_nw_id associated with the logical user */
  p_info->nw_id = sccp_utl_get_mtp_nw_id (l_user_id);

  /* Adjust the negotiable parameters */
  if (p_ccb->proto_class == PROTOCOL_CLASS_3)
  {
    if (IS_CREDIT_IE_PRESENT (p_info))
    {
      if (p_info->credit < p_ccb->credit)
        p_ccb->credit = p_info->credit;
      else
        p_info->credit = p_ccb->credit;
    }
    else
    {
      SET_CREDIT_PRESENT (p_info);
      p_info->credit = SCCP_DEFAULT_CREDIT;
    }

    if (IS_ED_SELECTION_PRESENT (p_info))
      p_ccb->c_status |= SCCP_ED_SELECTED;
  }

  /* Build a N-CONNECT.reply to the User */
  sccp_build_n_connect_reply_api (p_info, p_ccb);

  /* Start connection establishment timer */
  if (SS7_SUCCESS != sccp_start_co_timer (p_ccb, SCCP_T_CONNEST_TIMER, p_ecode))
  {
    /* release the connection */
    /* release resources and local reference */
    sccp_release_resources (p_ccb) ;

    /*
     * build CREF message and forward it to the route and translate
     * functionality of SCRC
     */

    /* SPR # 2579 Fix Start */
    /* change state to SCCP_CONN_CLOSED */
    sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;
    /* SPR # 2579 Fix End */
 
    p_info->msg_type = CREF_MSG_TYPE ;
 
    sccp_route_co_msg (p_info) ;
 
    /* start T_freeze */
    (void)sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;

    return (SS7_SUCCESS) ;
  }

  /* change state to connection start and the sub state to outgoing */
  sccp_change_state (p_ccb, SCCP_CONN_START, SCCP_OUTGOING) ;

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the Request Type 2 from the User in the IDLE state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives request Type 2 from
**    the user in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if conn refusal indicator is set
**    o then
**      o build CREF message and forward it to the route and translate
**        functionality of SCRC
**    o else
**      o if resources are available
**      o then
**        o assign local reference number and SLS to the incoming conn sect
**        o assign the protocol class 
**        o assign initial credit
**        o change the state to SCCP_CONN_START and substate to SCCP_INCOMING
**        o if reply request required is set
**        o then
**          o get another free ccb
**          o make association between the two nodes
**          o assign Local reference number and SLS to the outgoing conn
**          o assign protocol class and credit
**          o build reply message back to the user
**          o start T_conn_est timer
**          o change state to SCCP_CONN_START and substate to SCCP_OUTGOING
**        o else
**          o give N-CONNECT.ind to the user
**      o else
**        o give N-DISCONNECT.ind to the user
**        o build CREF message and forward it to the route and translate
**          functionality of SCRC
**
*****************************************************************************/

return_t
sccp_conn_idle_req_type_2
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit        corr_id ;/* Amaresh U16 U32 */
#else
  U8bit        corr_id ;
#endif
  U16bit       l_user_id ;
  U8bit        protocol_class ;
  sccp_ccb_t   *p_ccb, *p_out_ccb ;
  return_t     result ;
  
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_req_type_2\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO: Got REQUEST TYPE 2 in SCCP_CONN_IDLE State\n")) ;

  corr_id = p_info->corr_id ;
  l_user_id = p_info->l_id ;
  p_ccb = p_info->p_ccb;

  sccp_utl_get_sp_from_logid (p_info, l_user_id) ;
  if (p_info->p_sp == (sp_entry_t *)SS7_NULL)
  {
    return (SS7_FAILURE) ;
  }

  p_ccb->opc = GET_SP_PC (p_info->p_sp) ;

  if ((sccp_utl_get_ccb (SCCP_CONN_START, l_user_id, corr_id)) 
      != (sccp_ccb_t *)SS7_NULL)
  {
    /* It is a duplicate n_connect_request. Ignore it. */
    SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
        ("SCCP::CO: Duplicate REQUEST Type 1 LogUId[%d] CorrId[%d]\n",
        l_user_id, corr_id));
    
    /* Generate an ERROR */
    SCCP_ERR (ESCCP_DUPLICATE_CONN_REQ, STACK_PROTOCOL_ERROR, MAJOR_ERROR) ;

    p_info->p_ccb = (sccp_ccb_t *)SS7_NULL;

    *p_ecode = ESCCP_DUPLICATE_CONN_REQ ;
    return (SS7_FAILURE);
  }

  p_ccb->c_status |= SCCP_TYPE_A_USER;
  /* if conn refusal indicator is set */
  if (IS_REF_IND_PRESENT (p_info))
  {
    /* assign the protocol class */
    protocol_class = p_info->proto_class ;

    /* assign local reference number and SLS to the incoming conn sect */
    sccp_utl_init_ccb (p_ccb, protocol_class) ;

    p_ccb->dlr = p_info->slr ;
    p_ccb->dpc = p_info->opc ;

    /* build CREF message */
    sccp_utl_fill_nw_info (p_info, p_ccb) ;

    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
        ("SCCP::CO:Building CREF Message\n")) ;
    p_info->msg_type = CREF_MSG_TYPE;

    if (IS_CG_IE_PRESENT (p_info))
    {
      sccp_copy_sccp_addr (&p_info->cg_addr, &p_info->cd_addr);
      SET_RG_PRESENT (p_info);
    }
    p_info->p_ccb = (sccp_ccb_t *)SS7_NULL;

    /* forward it to the route and translate functionality of SCRC */
    sccp_route_co_msg (p_info) ;
  }
  else
  {
    /* Clear off corr_id */
    sccp_utl_clr_corr_id (l_user_id, corr_id);

    /* assign the protocol class */
    protocol_class = p_info->proto_class ;

    /* assign local reference number and SLS to the incoming conn sect */
    sccp_utl_init_ccb (p_ccb, protocol_class) ;

    p_ccb->dlr = p_info->slr ;
    p_ccb->dpc = p_info->opc ;
  	p_ccb->p_ss = p_info->p_ss ;

    p_info->conn_id = p_ccb->conn_id ;
    p_info->proto_class = protocol_class ;

    /* assign initial credit */
    if (p_ccb->proto_class == PROTOCOL_CLASS_3)
    {
      if (IS_CREDIT_IE_PRESENT (p_info))
      {
        if (p_info->credit < p_ccb->credit)
          p_ccb->credit = p_info->credit;
        else
          p_info->credit = p_ccb->credit;
      }
      else
      {
        SET_CREDIT_PRESENT (p_info);
        p_info->credit = SCCP_DEFAULT_CREDIT;
      }
    }

    /* change the state to SCCP_CONN_START and substate to SCCP_INCOMING */
    sccp_change_state (p_ccb, SCCP_CONN_START, SCCP_INCOMING) ;

    /* if reply request required is set */
    if (IS_REPLY_REQ_IND_PRESENT (p_info))
    {
      /* get another free ccb */
      if ((p_out_ccb = sccp_utl_get_free_ccb ()) != (sccp_ccb_t *)SS7_NULL)
      {
        sccp_utl_get_sp_from_logid (p_info, p_info->l_id_o) ;
        if (p_info->p_sp == (sp_entry_t *)SS7_NULL)
        {
          /* build CREF message */

          /* SPR # 2579 Fix Start */
          sccp_change_state (p_ccb, SCCP_CONN_IDLE, SS7_NULL) ;
          /* SPR # 2579 Fix End */

          p_info->p_ccb = (sccp_ccb_t *)SS7_NULL ;
          p_info->rel_cause = SCCP_RFC_UNEQUIPPED_USER;
          sccp_utl_fill_nw_info (p_info, p_ccb) ;

          SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
              ("SCCP::CO:Building CREF Message\n")) ;
          p_info->msg_type = CREF_MSG_TYPE;

          if (IS_CG_IE_PRESENT (p_info))
          {
            sccp_copy_sccp_addr (&p_info->cg_addr, &p_info->cd_addr);
            SET_RG_PRESENT (p_info);
          }
          sccp_route_co_msg (p_info) ;
          p_info->originator = 
                sccp_utl_get_cref_originator (p_info->rel_cause);
          sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

          sccp_release_resources (p_ccb) ;

/* SPR # 6126 Fix Start */
	    sccp_free_ccb(p_ccb);
/* SPR # 6126 Fix End */

          return (SS7_SUCCESS) ;
        }

        p_out_ccb->opc = GET_SP_PC (p_info->p_sp) ;
		p_out_ccb->p_ss = p_info->p_ss;

        protocol_class = p_ccb->proto_class ;

        /* assign Local reference number and SLS to the outgoing conn */
        sccp_utl_init_ccb (p_out_ccb, protocol_class) ;

        /* make association between the two nodes */
        p_out_ccb->coupled_ccb_id = p_ccb->ccb_id ;
        p_ccb->coupled_ccb_id = p_out_ccb->ccb_id ;
        SCCP_SET_COUPLING_PRESENT (p_ccb) ;
        SCCP_SET_COUPLING_PRESENT (p_out_ccb) ;
        p_out_ccb->c_status |= SCCP_TYPE_A_USER;

  	/* SPR 9404 - Fix Start */
        /*p_out_ccb->sls = sccp_assign_sls (&p_info->cd_addr, 
            &p_info->cg_addr, p_info->sls, p_info->proto_class & 0xf);*/
	/* SPR 13444 - Fix Start */
        /* p_out_ccb->sls = sccp_assign_sls (&p_info->cd_addr, 
            &p_info->cg_addr, p_info->sls,(U8bit)(p_info->proto_class & 0xf));*/
    /*    p_out_ccb->sls = sccp_assign_sls (&p_info->cg_addr,
            &p_info->cd_addr, p_info->sls,(U8bit)(p_info->proto_class & 0xf));*/
	/* SPR 13444 - Fix stop */

  	/* SPR 9404 - Fix End   */

        /* assign protocol class and credit */
        p_info->proto_class = p_ccb->proto_class ;
         
        sccp_utl_fill_nw_info (p_info, p_out_ccb) ;
        if (p_info->proto_class == PROTOCOL_CLASS_3)
        {
          p_info->credit = p_ccb->credit ;
        }

        p_info->conn_id = p_out_ccb->conn_id ;

        /* build reply message back to the user */
        sccp_build_n_connect_reply_api (p_info, p_out_ccb) ;

        /* start T_conn_est timer */
        result = sccp_start_co_timer (p_out_ccb, SCCP_T_CONNEST_TIMER, 
           p_ecode) ;
        if (result != SS7_SUCCESS)
        {
          /* Error */
        }

        /* change state to SCCP_CONN_START and substate to SCCP_OUTGOING */
        sccp_change_state (p_out_ccb, SCCP_CONN_START, SCCP_OUTGOING) ;
      }
      else
      {
        p_info->rel_cause = SCCP_RFC_UNEQUIPPED_USER;
        p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause);
        /* give N-DISCONNECT.ind to the user */
        sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;

        /* build CREF message */

        /* SPR # 2579 Fix Start */
        sccp_change_state (p_ccb, SCCP_CONN_IDLE, SS7_NULL);
        /* SPR # 2579 Fix End */

        SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE,
            ("SCCP::CO:Building CREF Message\n")) ;
        p_info->msg_type = CREF_MSG_TYPE;
        p_info->dlr = p_info->slr ;

        if (IS_CG_IE_PRESENT (p_info))
        {
          sccp_copy_sccp_addr (&p_info->cg_addr, &p_info->cd_addr);
          SET_RG_PRESENT (p_info);
        }

        /* forward it to the route and translate functionality of SCRC */
        sccp_route_co_msg (p_info) ;

        /* Release resources */
        sccp_release_resources (p_ccb) ;

        /* Free the taken up CCB */
        sccp_free_ccb (p_ccb) ;
        p_info->p_ccb = (sccp_ccb_t *)SS7_NULL;
      }
    }
    else
    {
      if (p_info->p_ss != (ss_entry_t *)SS7_NULL)
      {
        if (IS_SS_ALLOWED (p_info->p_ss))
        {
          p_ccb->corr_id = corr_id;
          SET_CORR_ID_PRESENT (p_info);
          p_ccb->l_id = l_user_id;
          /* Provide the called addr */
          p_info->cd_addr.rout_ind = ROUTE_ON_SSN ;
          p_info->cd_addr.pc_ind = SS7_TRUE;
          p_info->cd_addr.gti = SS7_NULL;
          p_info->cd_addr.ssn_ind = SS7_TRUE;
          p_info->cd_addr.ssn = GET_SS_SSN (p_info->p_ss);
          p_info->cd_addr.pc = p_ccb->opc ;
          /* give N-CONNECT.ind to the user */
          sccp_build_n_connect_ind_api (p_info, p_ccb) ;
          return (SS7_SUCCESS);
        }
        else
        {
          p_info->rel_cause = SCCP_RFC_SUBSYSTEM_FAILURE;
        }
      }
      else
        p_info->rel_cause = SCCP_RFC_UNEQUIPPED_USER;
      sccp_utl_fill_nw_info (p_info, p_ccb) ;
      p_info->originator = sccp_utl_get_cref_originator (p_info->rel_cause);
      sccp_build_n_disconnect_ind_api (p_info, p_ccb) ;
      p_info->msg_type = CREF_MSG_TYPE;
      sccp_route_co_msg (p_info) ;
    }
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the CR message from the peer in the IDLE state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives CR message from
**    the peer in the connection establishment phase.
**    When invoked it does the following :
**    
**    o if resources are available
**    o then
**      o if coupling required
**      o then
**        o associate remote reference to the incoming connection section
**        o change state of the incoming connec tion section to 
**          SCCP_CONN_START and substate to SCCP_INCOMING
**        o assign SLS and local reference number to the outgoing connection 
**          section
**        o make association between the incoming connection section and 
**          the outgoing connection section
**        o determine proposed class and credit
**        o build CR message and forward it to the route and translate 
**          functionality of SCRC
** 	  o SPR 1500: start T_conn_est for associated section 
**        o change state of the outgoing connec tion section to 
**          SCCP_CONN_START and substate to SCCP_OUTGOING
**      o else
**        o assign local reference and SLS to the incoming connection section
**        o associate remote reference to the connection section
**        o determine QOS
**        o give N-CONNECT.ind to the user
**        o change state to SCCP_CONN_START and substate  to SCCP_INCOMING
**    o else
**      o build CREF message and forward it the route and translate 
**        functionality of SCRC
**
*****************************************************************************/

return_t
sccp_conn_idle_cr
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  U8bit           protocol_class ;
  sccp_ccb_t      *p_ccb ;
  sccp_ccb_t      *p_out_ccb ;
  sccp_nsdu_org_t nsdu_org;
  return_t     	  result ;
  
  *p_ecode = 0;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_cr\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got CR Message in SCCP_CONN_IDLE State\n")) ;

  p_ccb = p_info->p_ccb ;

  /* Get the Protocol Class */
  protocol_class = p_info->proto_class ;

  /* initialise the connection control block based on the protocol class */
  sccp_utl_init_ccb (p_ccb, protocol_class) ;

  if (p_ccb->proto_class < p_info->proto_class)
  {
    p_info->proto_class = p_ccb->proto_class ;
  }

  if (p_ccb->proto_class == PROTOCOL_CLASS_3)
  {
    if (IS_CREDIT_IE_PRESENT (p_info))
	{
		if (p_info->credit < p_ccb->credit)
			p_ccb->credit = p_info->credit ;
	}
	SET_CREDIT_PRESENT (p_info);
    p_info->credit = p_ccb->credit;
  }

  /* assign local reference and SLS to the incoming connection section */
  /* SPR 9404 - Fix Start */
  /*p_ccb->sls = sccp_assign_sls (&p_info->cd_addr, &p_info->cg_addr, 
        p_info->sls, p_info->proto_class & 0xf);*/
  /* SPR 13444 - Fix Start */
  /* p_ccb->sls = sccp_assign_sls (&p_info->cd_addr, &p_info->cg_addr, 
        p_info->sls,(U8bit)(p_info->proto_class & 0xf));*/
  p_ccb->sls = sccp_assign_sls (&p_info->cg_addr, &p_info->cd_addr,
        p_info->sls,(U8bit)(p_info->proto_class & 0xf));
	/* SPR 13444 - Fix Stop */

  /* SPR 9404 - Fix End   */


  /* p_ccb->slr = p_ccb->ccb_id ; */
  p_info->conn_id = p_ccb->conn_id;

  /* associate the remote reference to the connection section */
  p_ccb->dlr = p_info->slr ;
  p_ccb->dpc = p_info->opc ;
  p_ccb->opc = p_info->dpc ;
  p_ccb->p_ss = p_info->p_ss ;

  /* 
   * change state of the incoming connec tion section to 
   * SCCP_CONN_START and substate to SCCP_INCOMING
   */
  sccp_change_state (p_ccb, SCCP_CONN_START, SCCP_INCOMING) ;

  nsdu_org.opc = p_ccb->opc ;
  nsdu_org.nw_id = DEFAULT_NW_ID ;

  /* if coupling required then */
  if (sccp_is_relay_coupling_node (&p_info->cd_addr, &nsdu_org))
  {
    /* Get a free CCB for the outgoing connection section */
    if ((p_out_ccb = sccp_utl_get_free_ccb ()) != (sccp_ccb_t *)SS7_NULL)
    {
      protocol_class = p_ccb->proto_class;

      sccp_utl_init_ccb (p_out_ccb, protocol_class);

      /* 
       * make association between the incoming connection section and 
       * the outgoing connection section
       */
      p_out_ccb->coupled_ccb_id = p_ccb->ccb_id ;
      p_ccb->coupled_ccb_id = p_out_ccb->ccb_id ;
      SCCP_SET_COUPLING_PRESENT (p_ccb) ;
      SCCP_SET_COUPLING_PRESENT (p_out_ccb) ;

      /* 
       * assign SLS and local reference number to the outgoing connection 
       * section
       */
	/* SPR 9404 - Fix Start */
      /*p_out_ccb->sls = sccp_assign_sls (&p_info->cd_addr, &p_info->cg_addr, 
            p_info->sls, p_info->proto_class & 0xf);*/
	 /* SPR 13444 - Fix Start */
      /* p_out_ccb->sls = sccp_assign_sls (&p_info->cd_addr, &p_info->cg_addr, 
            p_info->sls, (U8bit)(p_info->proto_class & 0xf));*/
         p_out_ccb->sls = sccp_assign_sls (&p_info->cg_addr, &p_info->cd_addr,
            p_info->sls, (U8bit)(p_info->proto_class & 0xf));
	/* SPR 13444 - Fix Stop */

	/* SPR 9404 - Fix End   */

      p_out_ccb->opc = p_info->dpc ;

      /* SPR 1500: start conn est timer for associated section */

      result = sccp_start_co_timer (p_out_ccb, SCCP_T_CONNEST_TIMER,
         	p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }
      /* SPR 1500: End fix */

      /* 
       * change state of the outgoing connec tion section to 
       * SCCP_CONN_START and substate to SCCP_OUTGOING
       */
      sccp_change_state (p_out_ccb, SCCP_CONN_START, SCCP_OUTGOING) ;

      /* 
       * build CR message and forward it to the route and translate 
       * functionality of SCRC
       */
      SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
      ("SCCP::CO:Building CR Message\n")) ;
      p_info->msg_type = CR_MSG_TYPE ;

      SET_RELAY_MSG (p_info) ;

      /* Called Address has been filled by the Previous node */
      SET_CD_PRESENT (p_info) ;

      /* 
       * Proposed class
       */
      p_info->proto_class = p_out_ccb->proto_class;

      p_info->slr = p_out_ccb->slr;
      p_info->opc = p_out_ccb->opc;

      if (p_ccb->proto_class == PROTOCOL_CLASS_3)
      {
        if (IS_CREDIT_IE_PRESENT (p_info))
        {
          if (p_info->credit < p_ccb->credit)
              p_ccb->credit = p_info->credit;
          else
              p_info->credit = p_ccb->credit;
        }
      }

      /*  
       * forward the message to the route and translate functionality 
       * of SCRC 
       */
      sccp_route_co_msg (p_info) ;
    }
    else
    {
      /* Error couldn't get a free ccb */
      /* Send CREF on incomming connection section */
      SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
      ("SCCP::CO:Building CREF Message\n")) ;
      p_info->msg_type = CREF_MSG_TYPE ;
      p_info->dlr = p_ccb->dlr ;
      p_info->rel_cause = SCCP_RFC_UNQUALIFIED ;

      if (IS_CG_IE_PRESENT (p_info))
          sccp_copy_sccp_addr (&p_info->cg_addr, &p_info->cd_addr);
     

      /* 
       * forward the message to the route and translate functionality 
       * of SCRC 
       */
      sccp_route_co_msg (p_info) ;

      /* Free incoming CCB (without freezing) */
      sccp_free_ccb (p_ccb) ;
    }
  }  /* End of if coupling required */
  else
  {
    /* give N-CONNECT.ind to the user */
    sccp_build_n_connect_ind_api (p_info, p_ccb) ;
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RLSD message from the peer in the IDLE state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RLSD message from
**    the peer in the connection establishment phase.
**    When invoked it does the following :
**    
**    o build RLC message and forward it to the route and translate 
**      fuctionality of SCRC
**
*****************************************************************************/

return_t
sccp_conn_idle_rlsd
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t   *p_ccb ;
  pc_t		dpc_val;
  U32bit        slr_tmp ;

  *p_ecode = 0;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_rlsd\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got RLSD Message in SCCP_CONN_IDLE State\n")) ;

  p_ccb = p_info->p_ccb ;

  /* 
   * build RLC message and forward it to the route and translate 
   * fuctionality of SCRC
   */
  SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
       ("SCCP::CO:Building RLC Message\n")) ;
  p_info->msg_type = RLC_MSG_TYPE ;

  /* SPR 1332: Start fix */
  /* Interchange slr and dlr values */
  slr_tmp = p_info->slr;
  p_info->slr = p_info->dlr;
  p_info->dlr = slr_tmp;

  /* Fill in opc and dpc values */
  dpc_val = p_info->dpc;
  p_info->dpc = p_info->opc;
  p_info->opc = dpc_val;
  /* SPR 1332: End fix */

  /* forward it to the Route and Translate function of SCRC */
  sccp_route_co_msg (p_info) ;

  /* Free incoming CCB */
  sccp_free_ccb (p_ccb) ;

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the RouteFail message from the SCRC in the IDLE state of SCCP
**    connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RouteFail message from
**    the SCRC in the connection establishment phase.
**    When invoked it does the following :
**    
**    o build CREF message and forward it to the route and translate 
**      fuctionality of SCRC
**
*****************************************************************************/

return_t
sccp_conn_idle_routefail
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t   *p_ccb ;
  pc_t 		dpc_val;

  *p_ecode = 0;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_routefail\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::CO:Got RouteFail Message in SCCP_CONN_IDLE State\n")) ;

  p_ccb = p_info->p_ccb ;

  /* SPR # 2579 Fix Start */
  if (p_info->route_failure_flag)
  {
  	SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
   	 ("SCCP::CO: Multiple Route Fail  messages in SCCP_CONN_IDLE State - Ignoring !!\n")) ;
	
  	/* Free incoming CCB */
  	sccp_free_ccb (p_ccb) ;

	return SS7_SUCCESS;
  }
  /* SPR # 2579 Fix End */


  /* 
   * build CREF message and forward it to the route and translate 
   * fuctionality of SCRC
   */
  SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
       ("SCCP::CO:Building CREF Message\n")) ;
  p_info->msg_type = CREF_MSG_TYPE ;

  /* SPR 1331: Start fix
   * fill opc and dpc values in outgoing message
   */
  dpc_val = p_info->dpc;
  p_info->dpc = p_info->opc ;
  p_info->opc = dpc_val;
  /* SPR 1331: End fix */

  p_info->dlr = p_info->slr ;
  p_info->nw_id = DEFAULT_NW_ID ;
  p_info->rel_cause = SCCP_RFC_END_USER_FAILURE ;

  /* forward it to the Route and Translate function of SCRC */
  p_info->route_failure_flag = SS7_TRUE;
  sccp_route_co_msg (p_info) ;

  /* Free incoming CCB */
  sccp_free_ccb (p_ccb) ;

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the Common action to be taken in certain states
**
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it does the following :
**    
**    o if source reference
**    o then
**      o build ERR message and forward it to the route and translate 
**        fucntionality of SCRC
**
*****************************************************************************/

return_t
sccp_conn_idle_comm_func
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  U8bit error_cause ;

  *p_ecode = 0;
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_idle_comm_function\n")) ;

  /* SPR 1350: Start fix */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
     sccp_itu_unassigned_dlr (p_info) ;
  }
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
     error_cause = SCCP_ERRC_LRN_MISMATCH_UNASSIGNED_DLRN ;
     sccp_ansi_info_mismatch (p_info, error_cause) ;
  }
#endif

  /* SPR 1350: End fix */



#if 0
  /* 
   * if source reference
   * then
   */
  if (IS_SOURCE_REF_PRESENT (p_info))
  {
    /* 
      * build ERR message and forward it to the route and translate 
      * fucntionality of SCRC
      */
    SCCP_STACK_TRACE (SCOC_TRACE, MEDIUM_TRACE, 
       ("SCCP::CO:Building ERR Message\n")) ;
    p_info->msg_type = ERR_MSG_TYPE ;
    p_info->dlr = p_info->slr ;
    p_info->error_cause = SCCP_ERRC_UNQUALIFIED ;

    /* SPR 1337: Start fix 
     * Remove copying of called addr field from p_ccb to p_info 
     * Clear called addr field in p_info instead.
     * Fill the opc and dpc values in p_info
     */
    CLR_CD_PRESENT (p_info);
    dpc_val = p_info->dpc;
    p_info->dpc = p_info->opc;
    p_info->opc = dpc_val;

   /* SPR 1337: End fix */
    /* forward it to the Route and Translate function of SCRC */
    sccp_route_co_msg (p_info) ;
  }
#endif

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
