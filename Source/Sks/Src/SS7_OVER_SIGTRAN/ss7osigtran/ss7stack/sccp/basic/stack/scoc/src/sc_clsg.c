/*****************************************************************************
**
**  FILE :
**    State Machine Functions for the Connection CLOSING state of the 
**    connection
**
******************************************************************************
**
**  FILENAME :
**    sc_clsg.c
**
**  DESCRIPTION :
**    This file contains all the functions handling the events for the 
**    CLOSING state of the SCCP connections.
**
**  Date    Name        Reference    Reason
**  _________________________________________________________________________
**  18Jun'02  Suyash  Tripathi     Fixed SPR 8985 
**  22Nov'00  Hemlata Baudhwar     Fixed SPR 4584 
**  29APr'99  Sudipta Pattar	   Fixed SPR 1338
**  15Feb'99  Sudipta Pattar       Fixed SPR 1336
**  15Feb'99  Sudipta Pattar       Fixed SPR 1335
**  08Jul'98  Praneet Khare    HSS:20800011  Original
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"

#ifdef SCCP_INCLUDE_CO_SERVICE

/* SPR 1338: Made this function common for RLC, RLSD and ERR messages */
/*****************************************************************************
**
**  FUNCTION :
**    Handles the RLC, RLSD and ERR messages from the peer in the CLOSING 
**    state of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives RLC, RLSD or ERR from
**    the peer in the connection closing phase.
**    When invoked it does the following :
**    
**    o release resoruces and local reference for connection section
**    o stop T_rel timer
**    o stop T_int timer
**    o change state to SCCP_CONN_CLOSED
**    o start timer freeze
**
*****************************************************************************/

return_t
sccp_conn_closing_rlc_rlsd_err
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t   *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t   *p_ccb ;
  return_t     result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_closing_rlc_rlsd_err\n")) ;

  /* Get the ccb */
  p_ccb = p_info->p_ccb;

  /* release resoruces and local reference for connection section */
  sccp_release_resources (p_ccb) ;

  /* stop T_rel time */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }
 
  /* stop T_int timer */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_INT_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }
 
  result = sccp_stop_co_timer (p_ccb, SCCP_T_REPREL_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* change state to SCCP_CONN_CLOSED */
  sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

  /* Start T_freeze */
  result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  return (SS7_SUCCESS) ;
}

/*****************************************************************************
**
**  FUNCTION :
**    Handles the T_rel timeout in the CLOSING state of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_rel timeout 
**    in the connection closing phase.
**    When invoked it does the following :
**    
**    o build RLSD message and forward it to the route and translate 
**      functionality of SCRC
**    o start T_int timer
**    o start T_reprel timer
**
*****************************************************************************/

return_t
sccp_conn_closing_t_rel_tmout
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
  return_t      result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_closing_t_rel_tmout\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR #4584 Fix Start */
  if ( p_ccb->sccp_timer[SCCP_T_REL_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_REL_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */

      /* 
       * build RLSD message and forward it to the route and translate 
       * functionality of SCRC
       */
       /* SPR 1336: Start fix 
       * message type was not set correctly
       */
      p_info->msg_type = RLSD_MSG_TYPE ;
      /* SPR 1336: End fix */
      sccp_utl_fill_nw_info (p_info, p_ccb) ;

      p_info->nw_id = DEFAULT_NW_ID; 

      sccp_route_co_msg (p_info) ;

      /* start T_int timer */
      result = sccp_start_co_timer (p_ccb, SCCP_T_INT_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      /* start T_reprel timer */
      result = sccp_start_co_timer (p_ccb, SCCP_T_REPREL_TIMER, p_ecode) ;
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
**    Handles the T_reprel timeout in the CLOSING state of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_reprel timeout 
**    in the connection closing phase.
**    When invoked it does the following :
**    
**    o build RLSD message and forward it to the route and translate 
**      functionality of SCRC
**    o restart T_reprel timer
**
*****************************************************************************/

return_t
sccp_conn_closing_t_reprel_tmout
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
  return_t      result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_closing_t_reprel_tmout\n")) ;

  p_ccb = p_info->p_ccb;

  /* SPR #4584 Fix Start */ 
  if ( p_ccb->sccp_timer[SCCP_T_REPREL_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_REPREL_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */

     /* 
      * build RLSD message and forward it to the route and translate 
      * functionality of SCRC
      */
      p_info->msg_type = RLSD_MSG_TYPE ;
      sccp_utl_fill_nw_info (p_info, p_ccb) ; 

      p_info->nw_id = DEFAULT_NW_ID; 

      sccp_route_co_msg (p_info) ;

      /* restart T_reprel timer */
      result = sccp_restart_co_timer (p_ccb, SCCP_T_REPREL_TIMER, p_ecode) ;
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
**    Handles the T_int timeout in the CLOSING state of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_int timeout 
**    in the connection closing phase.
**    When invoked it does the following :
**    
**    o inform maintanence
**    o release resources and local reference for the connection section
**    o stop T_rel and T_int timers
**    o change state to SCCP_CONN_IDLE
**
*****************************************************************************/

return_t
sccp_conn_closing_t_int_tmout
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
  return_t      result ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_closing_t_int_tmout\n")) ;

  /* read the CCb */
  p_ccb = p_info->p_ccb;


  /* SPR #4584 Fix Start */
  if ( p_ccb->sccp_timer[SCCP_T_INT_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_INT_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */

      /* release resources and local reference for the connection section */
      sccp_release_resources (p_ccb) ;

      /* stop T_rel and T_int timers */
      result = sccp_stop_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      result = sccp_stop_co_timer (p_ccb, SCCP_T_REPREL_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
         /* Error */
      }

      result = sccp_stop_co_timer (p_ccb, SCCP_T_INT_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
         /* Error */
      }

      result = sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode) ;
      if (result != SS7_SUCCESS)
      {
        /* Error */
      }

      /* change state to SCCP_CONN_IDLE */
      sccp_change_state (p_ccb, SCCP_CONN_CLOSED, SS7_NULL) ;

      return (SS7_SUCCESS) ;
  }
}


/* SPR 1335 taken care of in function sccp_conn_closing_rlc_rlsd_err */

/* SPR 1338: Start fix */
/*****************************************************************************
**
**  FUNCTION :
**    Handles the Common action to be taken for certain messages
**
******************************************************************************
**
**  DESCRIPTION :
**    When invoked it discards the message
**
*****************************************************************************/
 
return_t
sccp_conn_closing_comm_func
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{

  /* discard the received message */
  sccp_discard_message (p_info) ;
  
/* SPR 8985 - Fix Start */
/* This code is added to remove the "unused parameter" warning */
  p_ecode = 0;
/* SPR 8985 - Fix End  */
  return (SS7_SUCCESS) ;
}

/* SPR 1338: End fix */

#else

/*****************************************************************************
**	This extern declaration is required as BCC reports error if the 
** source file is empty after preprocessing. This declaration enables compilation
** without SCCP_INCLUDE_CO_SERVICE flag using BCC.
**
*****************************************************************************/

extern return_t sccp_co_dummy _ARGS_ ((void));

#endif
