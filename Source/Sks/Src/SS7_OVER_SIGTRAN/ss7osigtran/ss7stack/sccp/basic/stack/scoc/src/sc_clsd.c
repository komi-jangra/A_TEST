/*****************************************************************************
**
**  FILE :
**    State Machine Functions for the Connection CLOSED state of the 
**    connection
**
******************************************************************************
**
**  FILENAME :
**    sc_clsd.c
**
**  DESCRIPTION :
**    This file contains all the functions handling the events for the 
**    CLOSED state of the SCCP connections.
**
**  Date    Name        Reference    Reason
**  _________________________________________________________________________
**  18jun'02  Suyash Tripathi  SPR# 8985 Fixed  
**  22Nov'00  Hemlata Baudhwar SPR# 4584 Fixed  
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
**    Handles the T_freeze timeout in the CLOSING state of SCCP connection
**
******************************************************************************
**
**  DESCRIPTION :
**    This function is invoked when the SCCP receives T_rel timeout 
**    in the connection closing phase.
**    When invoked it does the following :
**    
**    o mark the Connection Control Block as available
**
*****************************************************************************/

return_t
sccp_conn_closed_t_freeze_tmout
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   error_t    *p_ecode)
#else
  (p_info, p_ecode)
  msg_info_t    *p_info ;
  error_t      *p_ecode ;
#endif
{
  sccp_ccb_t  *p_ccb;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_conn_closed_t_freeze_tmout\n")) ;

  SCCP_UT_TRACE (("SCCP::UT: Connection released. CCB Free\n")) ;

  p_ccb = p_info->p_ccb ;

/* SPR 8985 - Fix Start */
/* This line is added to remove the "unused parameter" warning */
  p_ecode = 0;
/* SPR 8985 - Fix End  */

  /* SPR #4584 Fix Start */
  if ( p_ccb->sccp_timer[SCCP_T_FREEZE_TIMER].timer_status != SCCP_CO_TIMER_RUNNING)
  {
      return SS7_SUCCESS;  /* timer not running so ignore time out */
  }
  else
  {
      p_ccb->sccp_timer[SCCP_T_FREEZE_TIMER].timer_status = SCCP_CO_TIMER_NOTRUNNING;
  /* SPR #4584 Fix End */

     /* Mark the CCB as avaialble */
     sccp_free_ccb (p_ccb) ;

     /* Change the state of the CCB to IDLE */
     sccp_change_state (p_ccb, SCCP_CONN_IDLE, SS7_NULL) ;

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
