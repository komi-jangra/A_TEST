/*****************************************************************************
**
**  FILE :
**    Utility Functions for the state machine of the connection oriented part
**
******************************************************************************
**
**  FILENAME :
**    sc_coutl.c
**
**  DESCRIPTION :
**
**  Date    Name        Reference    Reason
**  _________________________________________________________________________
**  25Jan2003 Suyash Tripathi  				Fixed SPR 11112
**  12Nov2002 Ashish Sawalkar               Fixed SPR 10692
**  12Nov2002 Ashish Sawalkar               Fixed SPR 10691
**  08Jul2002 Suyash Tripathi  SPR #9126    Check for SCCP_CONN_START state.  
**  08Jul2002 Suyash Tripathi  SPR #9126    Check for SCCP_CONN_START state.  
**  18Jun2002 Suyash Tripathi  SPR #8985    Removal of warnings.
**  18Sep2001 Aman Kapoor      SPR #5272    The trace value of timer is changed.
**  10Aug2001 Pawanish Modi    SPR #5446    A queue was added to maintain the   **					    pending requests.
**  22Oct2001 Prateek Bidwalkar          Fixed SPR 6546
**  11Sep2001 Prateek Bidwalkar          Fixed SPR 6126
**  28May2001 Rajesh Mehta                   increased conn_id to U32 and corr_id to
**                                          U16 if SCCP_CONNECTION_ID_CHANGES is defined
**  18Apr2001 Rajesh Mehta     SPR #5269     deleting the node before checking whether message
**                                            length within credit limit
**  18Apr2001 Rajesh Mehta     SPR #5267     Commenting out assignment of SLR = 0
**  22Nov2000 Hemlata Baudhwar SPR #4584     Set timer status to SCCP_TIMER_NOTRUNNING 
**                                           in sccp_stop_co_timer 
**  16Oct2000 Ramu Kandula     SPR #4483     Replaced sc_opt.seg_size with 
**                                           SCCP_MAX_CO_SEG_SIZE
**  09Jun2000 Ramu Kandula     SPR #2579     Fixed SPR 2579
**  08Jun2000 Ramu Kandula     SPR #2574     Fixed SPR 2574
**  11Feb2000 Ramu Kandula     SPR #2573     Fixed SPR 2573
**  15Oct'99  Ramu Kandula     SPR #878		 replaced ss7_mem_get with sccp_malloc
**											 & ss7_mem_free with sccp_free
**  10Aug'99  Sudipta Pattar                 Fixed SPR 1938
**  10Aug'99  Sudipta Pattar                 Fixed SPR 1773
**  25Jun'99  Sudipta Pattar                 Fixed SPR 1689
**  25Jun'99  Sudipta Pattar                 Fixed SPR 1686
**  29Apr'99  Sudipta Pattar                 Fixed SPR 1362
**  15Feb'99  Sudipta Pattar                 Fixed SPR 1273
**  07Feb'99  Sudipta Pattar                 Added event alarms
**  08Jul'98  Praneet Khare    HSS:20800011  Original
**  04Jul'01  Pawanish Modi                  SPR Fix
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"
#include "sc_reg.h"

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

#ifdef SCCP_CONNECTION_ID_CHANGES
#define DATA_LEN_OFFSET 9
#else
#define DATA_LEN_OFFSET 7
#endif
extern U8bit sccp_state;
#ifdef SCCP_INCLUDE_CO_SERVICE


/*****************************************************************************
**
**  FUNCTION :
**      Search for a matching CCB
**
******************************************************************************
**
**  DESCRIPTION :
**    Search  for a CCB in the sccp connection control block with following
**    attributes :
**      connection state is c_state.
**      associated user's logical user id is l_id,
**      connection instance in the context of user is corr_id.
**
******************************************************************************/
#ifdef SCCP_CONNECTION_ID_CHANGES
sccp_ccb_t *
sccp_utl_get_ccb
#ifdef ANSI_PROTO
  (U8bit   c_state,
   U16bit l_id,
   U32bit   corr_id) /* Amaresh U32bit U16bit */
#else
  (c_state, l_id, corr_id)
   U8bit   c_state ;
   U16bit l_id ;
   U32bit   corr_id ; /* Amaresh U32bit U16bit */
#endif
#else
sccp_ccb_t *
sccp_utl_get_ccb
#ifdef ANSI_PROTO
  (U8bit   c_state,
   U16bit l_id,
   U8bit   corr_id)
#else
  (c_state, l_id, corr_id)
   U8bit   c_state ;
   U16bit l_id ;
   U8bit   corr_id ;
#endif
#endif
{
  sccp_ccb_t  *p_ccb ;
/* SPR # 6126 Fix Start */
#if 0
  U32bit      count ;
  U16bit      count ;
#endif
  U32bit      hash_index;
  U32bit      ccb_id;
/* SPR # 6126 Fix End */


  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_get_ccb\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Searching for a Connection Control Block based on LogUId[%d] CorrId[%d].....",
      l_id, corr_id)) ;

/* SPR # 6126 Fix Start */
#if 0
  /* This linear search is being replaced by a hash based function. */
  /* Linear Search */

  /* Point the p_ccb to the first connection control block */
  p_ccb = &(sccp_ccb [0]) ;

  for (count=0; count<MAX_SCCP_CO_CONNECTIONS ; count++, p_ccb++)
  {
    if ((p_ccb->c_state == c_state) &&
      (p_ccb->l_id  == l_id) &&
      (p_ccb->corr_id  == corr_id))
    {
      SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Found\n")) ;
      return (p_ccb) ;
    }
  }

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("CCB Not Found\n")) ;
  return ((sccp_ccb_t *)SS7_NULL) ;
#endif 

  hash_index = sccp_utl_get_hash_index(l_id,corr_id);
 
  if(sccp_hash_table[hash_index] == SCCP_INVALID_CCB_ID)
  {
        SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("CCB Not Found\n")) ;
        return ((sccp_ccb_t *)SS7_NULL) ;
  }

  ccb_id = sccp_hash_table[hash_index];
  do
  {
	 p_ccb = &sccp_ccb[ccb_id];
     if ((p_ccb->c_state == c_state) &&
         (p_ccb->l_id  == l_id) &&
         (p_ccb->corr_id  == corr_id))
     {
         SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("CCB Found\n")) ;
         return (p_ccb) ;
     }
     
     ccb_id = p_ccb->next_ccb_id;
  }while(ccb_id != SCCP_INVALID_CCB_ID);

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("CCB Not Found\n")) ;
/* SPR # 6126 Fix End */

  return ((sccp_ccb_t *)SS7_NULL) ;
}

/******************************************************************************
**
**  FUNCTION:
**    Read the Connection Control Block associated with a Particular connection
**
*******************************************************************************
**
**  DESCRIPTION:
**    Returns the Connection control block associated with the connection
**    identified on the basis of connection id.
**
******************************************************************************/

return_t
sccp_utl_read_ccb
#ifdef ANSI_PROTO
  (msg_info_t   *p_info)
#else
  (p_info)
   msg_info_t   *p_info ;
#endif
{

  	U8bit max_num_bits,n;

  	SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_read_ccb\n")) ;
  	SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
     ("SCCP::SCOC: Searching for a Connection Control Block based on ConnId[%d]\n",
      p_info->conn_id)) ;

#ifdef SCCP_CONNECTION_ID_CHANGES
     max_num_bits = 24;
#else
     max_num_bits = 16;
#endif

#ifdef DISTRIBUTED_SCCP
      n = sc_opt.num_of_bits_instance_id;
#else
	n = 0;
#endif


#ifdef DISTRIBUTED_SCCP
      if ((p_info->conn_id >> (max_num_bits-n)) != sc_opt.dsccp_local_instance_id)
      {
  		SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
     		("SCCP::SCOC: Non-local ConnId[%d] received\n", p_info->conn_id)) ;
     		return (SS7_FAILURE);
      }
#endif

	if ((p_info->conn_id & (~(0xffffffff << (max_num_bits-n)))) >= 
		MAX_SCCP_CO_CONNECTIONS )
  	{
    		/* error */
    		return (SS7_FAILURE);
  	}

  	p_info->p_ccb = &(sccp_ccb [p_info->conn_id &
				 (~(0xffffffff << (max_num_bits-n)))]) ;

  	return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**  FUNCTION:
**    Get a Free CCB
**
*******************************************************************************
**
**  DESCRIPTION:
**    Gets a free Connection Block from the Global database. It does a Linear
**    search on the database to find the free connection control block.
**
******************************************************************************/

sccp_ccb_t *
sccp_utl_get_free_ccb 
#ifdef ANSI_PROTO
  (void)
#else
  (void)
#endif
{
  sccp_ccb_t *p_ccb ;

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_get_free_ccb\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Looking for a free Connection Control Block.....")) ;

/* SPR # 6126 Fix Start */
#if 0
  p_ccb = sccp_ccb;

  for (count=0; count < MAX_SCCP_CO_CONNECTIONS ; count++, p_ccb++)
  {
    if (p_ccb->c_state == SCCP_CONN_IDLE)
    {
      SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Found\n")) ;
      return (p_ccb);
    }
  }

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Not Found\n")) ;
  return ((sccp_ccb_t *)SS7_NULL) ;
#endif
 
LOG_PRINT(CRITICAL,"sccp_utl_get_free_ccb %d\n",sccp_free_ccb_list_head);
  if(sccp_free_ccb_list_head != SCCP_INVALID_CCB_ID)
        p_ccb = &sccp_ccb[sccp_free_ccb_list_head];
  else
  {
        SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Free CCB Not Found\n")) ;
        return ((sccp_ccb_t *)SS7_NULL) ;
				LOG_PRINT(CRITICAL,"sccp_utl_get_free_ccb:Free CCB Not Found\n");
  }

  sccp_free_ccb_list_head = p_ccb->next_ccb_id;
  p_ccb->next_ccb_id = SCCP_INVALID_CCB_ID;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Found\n")) ;

/* SPR # 6126 Fix End */

	LOG_PRINT(CRITICAL,"sccp_utl_get_free_ccb:Found sccp_free_ccb_list_head[%d]\n",sccp_free_ccb_list_head);
  return (p_ccb);

}


/******************************************************************************
**
**  FUNCTION:
**    Initialise the CCB
**
*******************************************************************************
**
**  DESCRIPTION:
**    This function initialises the common variables associated with the 
**    connection in the connection control block.
**
******************************************************************************/

void
sccp_utl_init_ccb
#ifdef ANSI_PROTO
  (sccp_ccb_t    *p_ccb,
   U8bit         protocol_class)
#else
  (p_ccb, protocol_class)
  sccp_ccb_t    *p_ccb ;
  U8bit         protocol_class ;
#endif
{
#ifdef DISTRIBUTED_SCCP
#ifdef SCCP_CONNECTION_ID_CHANGES
  	U32bit mask , id;
#else
  	U16bit mask , id;
#endif
	/** SPR 9302 - Fix Start **/
#if 0
	U8bit j;
	U32bit temp;
#endif
	/** SPR 9302 - Fix End   **/

	mask  = 0;
	id = 0;
#endif
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_init_ccb\n")) ;

  /** SPR # 2574 Fix Start **/
  p_ccb->wait_for_cc_flag = SS7_FALSE;
  /** SPR # 2574 Fix End **/

  /* SPR 1273: Start fix 
   * if class 3 services are not provided 
   */
#ifndef SCCP_INCLUDE_CO_CLASS3_SERVICE
	protocol_class = PROTOCOL_CLASS_2;
#endif
  /* SPR 1273: End fix */

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Initialising the Connection Control Block ConnId[%d] ProtoClass[%d]\n", 
      p_ccb->conn_id, protocol_class)) ;

  /* Fill in the Protocol Class */
  p_ccb->proto_class = protocol_class ;

  /* Fill in the Source Local Reference */
  p_ccb->slr = (U32bit)(p_ccb->conn_id) ;

  /* Fill up the Credit if Class 3 connection */
  if (protocol_class == PROTOCOL_CLASS_3)
  {
	p_ccb->credit = SCCP_DEFAULT_CREDIT;
  }

  /* Initialise the receive queue to SS7_NULL */
  p_ccb->p_recv_queue = (sc_queue_t *)SS7_NULL;
  /* Initialise the transmit queue to SS7_NULL */
  p_ccb->p_trans_queue = (sc_queue_t *)SS7_NULL ;
  /* SPR 1773: Start
   * Initialize transmit queue for ED to SS7_NULL */
  p_ccb->p_ed_trans_queue = (sc_queue_t *)SS7_NULL ;
  /* Initialize number of ED's in queue */
  p_ccb->num_ed_in_queue = 0 ;
  /* SPR 1773: End */
  /* Initialise the send sequence number */
  p_ccb->send_seq = 0 ;
  /* Initialise the send sequence number expected */
  p_ccb->send_seq_x = 0 ;
  /* Initialise the lower window */
  p_ccb->lw_edge = 0 ;
  /* Initialise the send sequence acknowledged */
  /* SPR 1361: initialize send seq ack to 0 */
  p_ccb->send_seq_ack = 0 ;

  /* Initialise the variables associated with the re-assembly */
  p_ccb->seq_seg = 0 ;
  p_ccb->seg_reass = 0;

  return ;
}

/******************************************************************************
**
**   FUCNTION :
**    Changes state of the CCB
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function changes the state of the connection to state and substate
**    passed as the parameter to the function.
**
******************************************************************************/

void
sccp_change_state
#ifdef ANSI_PROTO
  (sccp_ccb_t *p_ccb,
   U8bit      state,
   U8bit      substate)
#else
  (p_ccb, state, substate)
  sccp_ccb_t *p_ccb ;
  U8bit      state ;
  U8bit      substate ;
#endif
{
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_change_state\n")) ;
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Changing state from [%s] to [%s] for ConnId[%d]\n",
      sccp_co_state_string [p_ccb->c_state], 
      sccp_co_state_string [state], p_ccb->conn_id)) ;

  p_ccb->c_state = state ;
  p_ccb->c_status = (p_ccb->c_status & 0xF3) | substate ;

  /** Update the standby if the ccb is entering a stable state. 
  *** The following states are considered as stable states :
  *** 1. IDLe
  *** 2. START
  *** 3. ESTAB
  *** 4. CLOSING
  *** 5. CLOSED
  *** The RESET state is not considered a stable state
  **/

  if ( (state == SCCP_CONN_IDLE) ||
	   (state == SCCP_CONN_START) || 
	   (state == SCCP_CONN_ESTABLISHED) || 
	   (state == SCCP_CONN_CLOSING) || 
	   (state == SCCP_CONN_CLOSED) )
  {
    SCCP_SEND_SCOC_ENTRY_UPDATE(p_ccb);
  }
 return ;
}


/******************************************************************************
**
**  FUNCTION :
**    Start the timer for SCCP Connection Oriented Part
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function fills up the timer buffer for the timers associated with 
**    the connection oriented services, and pass that buffer to the timer 
**    management function.
**
******************************************************************************/

return_t 
sccp_start_co_timer
#ifdef ANSI_PROTO
  (sccp_ccb_t       *p_ccb,
   U8bit            timer_name,
   error_t          *p_ecode)
#else
  (p_ccb, timer_name, p_ecode)
   sccp_ccb_t       *p_ccb ;
   U8bit            timer_name ;
   error_t          *p_ecode ;
#endif
{
  U32bit              timer_val ;
  sccp_co_tim_buf_t   timer_buf ;
  timer_id_t          timer_id ;
  return_t            result ;
 
  /* SPR 5272 ... Fix Starts */
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Starting Timer[%s] Duration[%umillisecs] ConnId[%d]\n",
      sccp_co_timer_string [timer_name], 
      (10*sccp_co_timer_dur [timer_name]), p_ccb->conn_id)) ;
  /* SPR 5272 ... Fix Ends */

  timer_buf.timer_name = sccp_map_co_timer [timer_name] ;
#ifdef SCCP_CONNECTION_ID_CHANGES
  timer_buf.conn_id_l = p_ccb->conn_id & 0x000000ff ;
  timer_buf.conn_id_m = (p_ccb->conn_id >> 8) & 0x000000ff ;
  timer_buf.conn_id_m1 = (p_ccb->conn_id >> 16) & 0x000000ff ;
  timer_buf.conn_id_m2 = (p_ccb->conn_id >> 24) & 0x000000ff ;
#else
  timer_buf.conn_id_l = p_ccb->conn_id & 0x00ff ;
  timer_buf.conn_id_m = (p_ccb->conn_id >> 8) & 0x000000ff ;
#endif

  /* Get timer value in 10s of milisecond */
  timer_val = sccp_co_timer_dur [timer_name] ; 


  result = ss7_start_timer (timer_val, (pvoid)&timer_buf,
               sizeof(sccp_co_tim_buf_t), SCCP_MODULE_ID, &timer_id, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Print Error Trace */
    SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Couldn't start Timer[%s] ConnId[%d]\n",
      sccp_co_timer_string [timer_name], 
      p_ccb->conn_id)) ;
    /* error */
    SCCP_ERR (*p_ecode, STACK_PROTOCOL_ERROR, MAJOR_ERROR) ;
    return (result) ;
  }
  else
  {
    /* Timer stated successfully, so keep the id */
    p_ccb->sccp_timer [timer_name].timer_id = timer_id ;
    /* 
     * Mark the status of the timer in the connection control block as 
     * running
     */
    p_ccb->sccp_timer [timer_name].timer_status = SCCP_CO_TIMER_RUNNING ;
  }

  return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Stops the timer for SCCP Connection Oriented Part
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function stops the timer, identified by the timer name passed in
**    the function call. It gets the timer id out of the connection  control
**    block and sends appropriate indication to the timer management function
**    to stop the timer.
**
******************************************************************************/

return_t 
sccp_stop_co_timer
#ifdef ANSI_PROTO
  (sccp_ccb_t       *p_ccb,
   U8bit            timer_name,
   error_t          *p_ecode)
#else
  (p_ccb, timer_name, p_ecode)
   sccp_ccb_t       *p_ccb ;
   U8bit            timer_name ;
   error_t          *p_ecode ;
#endif
{
  timer_id_t  timer_id ;
  return_t    result ;

  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Stopping Timer[%s] ConnId[%d]\n",
      sccp_co_timer_string [timer_name], p_ccb->conn_id)) ;

  if (p_ccb->sccp_timer [timer_name].timer_status != SCCP_CO_TIMER_RUNNING)
  {
    /* Error : Trying to stop a non-running timer */
    SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Trying to stop a non-running Timer[%s] ConnId[%d]\n",
      sccp_co_timer_string [timer_name], 
      p_ccb->conn_id)) ;
    return(SS7_FAILURE);
  }

  timer_id = p_ccb->sccp_timer [timer_name].timer_id ;

  result = ss7_stop_timer (timer_id, p_ecode) ;
  if (result != SS7_SUCCESS)
  {
    SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: Couldn't stop Timer[%s] ConnId[%d]\n",
      sccp_co_timer_string [timer_name], 
      p_ccb->conn_id)) ;
    /* Error : Unable to stop the timer */
    SCCP_ERR (*p_ecode, STACK_PROTOCOL_ERROR, MINOR_ERROR) ;
    return(SS7_FAILURE);
  }
  /* SPR #4584 Fix Start  */
  else
  {
    /* 
     * Mark the status of the timer in the connection control block as 
     * notrunning
     */
    p_ccb->sccp_timer [timer_name].timer_status = SCCP_CO_TIMER_NOTRUNNING ;
  }
  /* SPR #4584 Fix End  */

  return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Mark the Date Transfer phase as started.
**
*******************************************************************************
**
**  DESCRIPTION :
**    After reset phase the data transfer is started again, so mark the 
**    status bit associated with the data transfer status on the 
**    connection.
**
******************************************************************************/

void
sccp_resume_data_transfer
#ifdef ANSI_PROTO
  (sccp_ccb_t   *p_ccb)
#else
  (p_ccb)
  sccp_ccb_t    *p_ccb ;
#endif
{
  p_ccb->c_status = (p_ccb->c_status & 0x7F) ; /* Mark 8th bit as 0 */
  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    Frees the buffer in the queue
**
*******************************************************************************
**
**  DESCRIPTION :
**    Free up the buffers associated with the queue pointed to by p_queue
**
******************************************************************************/

void
sccp_free_queue
#ifdef ANSI_PROTO
  (sc_queue_t   *p_queue)
#else
  (p_queue)
   sc_queue_t   *p_queue ;
#endif
{
  sc_queue_t *p_tmp_buf ;

  /* Free the buffer allocated for the queues */
  while (p_queue != ((sc_queue_t *) SS7_NULL))
  {
    p_tmp_buf = p_queue->p_next ;
    sccp_free ((U8bit *)p_queue) ;
    p_queue = p_tmp_buf ;
  }
  return ;
}

/******************************************************************************
**
**  FUNCTION :
**   Free up the connection control block associated with the connection
**
*******************************************************************************
**
**  DESCRIPTION :
**    Free up the variables associated with the connection
**
******************************************************************************/

void
sccp_free_ccb
#ifdef ANSI_PROTO
  (sccp_ccb_t   *p_ccb)
#else
  (p_ccb)
   sccp_ccb_t   *p_ccb ;
#endif
{
  U8bit i;

  /* Clear status register */
  p_ccb->c_status = 0x00 ;
  /* Free receive queue */
  sccp_free_queue (p_ccb->p_recv_queue) ;
  p_ccb->p_recv_queue = (sc_queue_t *)SS7_NULL ;
  /* Free transmit queue */
  sccp_free_queue (p_ccb->p_trans_queue) ;
  p_ccb->p_trans_queue = (sc_queue_t *)SS7_NULL ;

  /* SPR 1773: Start 
   * Free ED transmit queue */
  sccp_free_queue (p_ccb->p_ed_trans_queue) ;
  p_ccb->p_ed_trans_queue = (sc_queue_t *)SS7_NULL ;
  /* SPR 1773: End */

  /* Clear the timers status */
  for (i = 0; i < MAX_SCCP_CO_TIMERS; i++)
  {
    p_ccb->sccp_timer [i].timer_status = SCCP_CO_TIMER_NOTRUNNING ;
  }

/*  SPR # 6126 Fix Start */
  /* Remove the CCB from hash table (if req) and Add the freed ccb to the 
  ** free list of ccb's and move the head pointer to the just freed node.
  */
  if (p_ccb->corr_id != 0)
  {
    sccp_utl_del_ccb_from_hash_tbl(p_ccb->c_state, p_ccb->l_id, p_ccb->corr_id);
  }
  p_ccb->next_ccb_id = sccp_free_ccb_list_head;
  sccp_free_ccb_list_head = p_ccb->ccb_id;
/* SPR # 6126 Fix End */
 
  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    Release the resources associated with the connection
**
*******************************************************************************
**
**  DESCRIPTION :
**    Frees up the resources associated with the connection, which is the
**    source local reference.
**
******************************************************************************/

void
sccp_release_resources
#ifdef ANSI_PROTO
  (sccp_ccb_t  *p_ccb)
#else
  (p_ccb)
   sccp_ccb_t  *p_ccb ;
#endif
{
  /* Mark the SLR as available */
/* SPR #5267 Starts */
/* SPR #5267 Starts */
  p_ccb->slr = 0x00; 
/* SPR #5267 fix ends */
  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    SS7_NULL function for the state machine table
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function does nothing. It is just put to make the state machine 
**    table complete. 
**
******************************************************************************/

return_t
sccp_do_nothing
#ifdef ANSI_PROTO
  (msg_info_t   *p_info,
   error_t      *p_ecode)
#else
  (p_info, p_ecode)
   msg_info_t   *p_info ;
   error_t      *p_ecode ;
#endif
{
  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_do_nothing\n"));
/* SPR 8985 - Fix Start */
/* This code is added just to remove the "unused parameter" warning */
  p_info = 0;
  p_ecode = 0;
/* SPR 8985 - Fix End  */

  return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Reset the variable associated with a connection section
**
*******************************************************************************
**
**  DESCRIPTION :
**    Resets the variables associated with the connection section. namely
**    the P(s), P(r) etc.
**
******************************************************************************/

void
sccp_reset_variables
#ifdef ANSI_PROTO
  (sccp_ccb_t   *p_ccb)
#else
  (p_ccb)
   sccp_ccb_t   *p_ccb ;
#endif
{
  p_ccb->send_seq = 0 ;
  p_ccb->send_seq_x = 0 ;
  p_ccb->lw_edge = 0 ;
 
  /* SPR 1773: Start 
   * Discard ED messages in queue */
  sccp_free_queue (p_ccb->p_ed_trans_queue) ;
  p_ccb->p_ed_trans_queue = (sc_queue_t *)SS7_NULL ;
  p_ccb->num_ed_in_queue = 0 ;
  /* SPR 1773: End */

  /* SPR 1938: Discard other messages in transmit queue */
  sccp_free_queue (p_ccb->p_trans_queue) ;
  p_ccb->p_trans_queue = (sc_queue_t *)SS7_NULL ;

  /* SPR 1361: initialize send seq ack to 0 */
  p_ccb->send_seq_ack = 0 ;

  p_ccb->w = p_ccb->credit ;

  return ; 
}

/******************************************************************************
**
**  FUNCTION :
**    Remove the association between two connection sections.
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function removes the association between the two connection 
**    sections pointed to by p_ccb, and p_coupled_ccb
**
******************************************************************************/

void
sccp_remove_association
#ifdef ANSI_PROTO
  (sccp_ccb_t   *p_ccb,
   sccp_ccb_t   *p_coupled_ccb)
#else
  (p_ccb, p_coupled_ccb)
   sccp_ccb_t   *p_ccb ;
   sccp_ccb_t   *p_coupled_ccb ;
#endif
{
  p_ccb->coupled_ccb_id = SCCP_INVALID_CCB_ID ;
  p_coupled_ccb->coupled_ccb_id = SCCP_INVALID_CCB_ID ;
  SCCP_RESET_COUPLING_PRESENT (p_ccb) ;
  SCCP_RESET_COUPLING_PRESENT (p_coupled_ccb) ;

  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    Clear the Correlation id
**
*******************************************************************************
**
**  DESCRIPTION :
**   This fucntion clears up the correlation id associated with the connection
**   if its found to be matching with some connection already in connection 
**    established state and with the same logical user id
**
******************************************************************************/

#ifdef SCCP_CONNECTION_ID_CHANGES
void
sccp_utl_clr_corr_id
#ifdef ANSI_PROTO
  (U16bit   l_uid,
   U32bit    corr_id) /* Amaresh U16 U32 */
#else
  (l_uid, corr_id)
   U16bit   l_uid ;
   U32bit    corr_id ; /* Amaresh U16 U32 */
#endif
#else
void
sccp_utl_clr_corr_id
#ifdef ANSI_PROTO
  (U16bit   l_uid,
   U8bit    corr_id)
#else
  (l_uid, corr_id)
   U16bit   l_uid ;
   U8bit    corr_id ;
#endif
#endif
{
#if 0
  ccp_ccb_t  *p_ccb ;
  U32bit      hash_index;
  U32bit      ccb_id;
#endif

  SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_clr_corr_id\n")) ;

/* SPR # 6126 Fix Start */
  /* This linear search is being replaced by a hash table based search */
#if 0
  p_ccb = &(sccp_ccb [0]) ;
  
  for (count=0; count<MAX_SCCP_CO_CONNECTIONS ; count++, p_ccb++)
  {
    if ((p_ccb->c_state == SCCP_CONN_ESTABLISHED) &&
      (p_ccb->l_id  == l_uid) &&
      (p_ccb->corr_id  == corr_id))
    {
      SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Found matching l_id, \
	  and corr_id \n")) ;
	  p_ccb->corr_id = 0;
    }
  }
#endif
  
  if (corr_id != 0)
  {
	sccp_utl_del_ccb_from_hash_tbl(SCCP_CONN_ESTABLISHED, l_uid, corr_id);
  }
  else
  {
    /* corr id already cleared */
    return;
  }
  
/* SPR # 6126 Fix End */

  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    Discard the Message
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function frees up the memory used up the message, and discards it
**
******************************************************************************/

void
sccp_discard_message
#ifdef ANSI_PROTO
  (msg_info_t    *p_info)
#else
  (p_info)
   msg_info_t    *p_info ;
#endif
{
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: Discarding message\n")) ;

  /** SPR # 2573 Fix Start ***
  *** sccp_free must not be called as p_info is not malloc'ed 
  *** but statically allocated from the call stack
  **/
#if 0
  sccp_free ((pvoid)p_info) ;
#endif
  /** SPR # 2573 Fix End **/

/* SPR 8985 - Fix Start */
/* This code is added just to remove the "unused parameter" warning */
  p_info = 0;
/* SPR 8985 - Fix End  */

  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    Get MTP network id
**
*******************************************************************************
**
**  DESCRIPTION :
**   This function returns the network id associated with the network
**
******************************************************************************/

U8bit
sccp_utl_get_mtp_nw_id
#ifdef ANSI_PROTO
  (U16bit    l_uid)
#else
  (l_uid)
   U16bit    l_uid ;
#endif
{
/* SPR 8985 - Fix Start */
/* This line of code is added just to remove the "unused parameter" warning */
  l_uid = 0;
/* SPR 8985 - Fix End  */

  return (DEFAULT_NW_ID) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Map logical reference number to connection id
**
*******************************************************************************
**
**  DESCRIPTION :
**    Thsi function provides a mapping for the logical reference number to the 
**    connection id. Currently this is directly mapped onto connection id.
**
******************************************************************************/

U16bit
sccp_utl_map_lref_cid
#ifdef ANSI_PROTO
  (U32bit  lref)
#else
  (lref)
  U32bit   lref ;
#endif
{
  return ((U16bit)lref) ;
}

/******************************************************************************
**
**  FUNCTION :
**  Map logical reference number to connection id in case connection id = 32bit
**
*******************************************************************************
**
**  DESCRIPTION :
**    Thsi function provides a mapping for the logical reference number to the
**    connection id. Currently this is directly mapped onto connection id.
**
******************************************************************************/
#ifdef SCCP_CONNECTION_ID_CHANGES
U32bit
sccp_utl_map_lref_cid_motorola
#ifdef ANSI_PROTO
  (U32bit  lref)
#else
  (lref)
  U32bit   lref ;
#endif
{
  return (lref) ;
}

#endif
/******************************************************************************
**
**  FUNCTION :
**    Checks whether the message is connection oriented message or not.
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function checks the msg type to determine whether the message is
**    connection oriented or not.
**
******************************************************************************/

Boolean
sccp_is_co_msg
#ifdef ANSI_PROTO
  (U8bit msg_type)
#else
  (msg_type)
  U8bit msg_type;
#endif
{
  if ((msg_type == CR_MSG_TYPE)   ||
      (msg_type == CC_MSG_TYPE)   ||
      (msg_type == CREF_MSG_TYPE) ||
      (msg_type == RLSD_MSG_TYPE) ||
      (msg_type == RLC_MSG_TYPE)  ||
      (msg_type == DT1_MSG_TYPE)  ||
      (msg_type == IT_MSG_TYPE)   ||
      (msg_type == ERR_MSG_TYPE)
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
                                  ||
      (msg_type == RSR_MSG_TYPE)  ||
      (msg_type == RSC_MSG_TYPE)  ||
      (msg_type == DT2_MSG_TYPE)  ||
      (msg_type == AK_MSG_TYPE)   ||
      (msg_type == ED_MSG_TYPE)   ||
      (msg_type == EA_MSG_TYPE)
#endif
                               )
      return (SS7_TRUE);
  else
      return (SS7_FALSE);
}

/******************************************************************************
**
**  FUNCTION :
**    Fill the network related information
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function fills the network related parameters like originating point
**    code, destination point code, source local reference, destination local 
**    reference, network id
**
******************************************************************************/

void
sccp_utl_fill_nw_info
#ifdef ANSI_PROTO
  (msg_info_t *p_info, sccp_ccb_t *p_ccb)
#else
  (p_info, p_ccb)
  msg_info_t *p_info;
  sccp_ccb_t *p_ccb;
#endif
{
  p_info->proto_class = p_ccb->proto_class;
  p_info->opc = p_ccb->opc;
  p_info->dpc = p_ccb->dpc;
  p_info->slr = p_ccb->slr;
  p_info->dlr = p_ccb->dlr;
  p_info->nw_id = DEFAULT_NW_ID ;
  p_info->p_ss = p_ccb->p_ss ;

/* SPR # 6546 : Fix Start */
  p_info->sls = p_ccb->sls;
/* SPR # 6546 : Fix End */
  return;
}

/******************************************************************************
**
**  FUNCTION :
**    Restart the connection oriented timer
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function restarts the timer identified by the timer name 
**
******************************************************************************/

return_t
sccp_restart_co_timer
#ifdef ANSI_PROTO
	(sccp_ccb_t *p_ccb, U8bit timer_name, error_t *p_ecode)
#else
	(p_ccb, timer_name, p_ecode)
	 sccp_ccb_t *p_ccb;
	 U8bit timer_name;
	 error_t *p_ecode;
#endif
{
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
      ("SCCP::SCOC: ReStarting Timer[%s]\n",
      sccp_co_timer_string [timer_name])) ;
  (void)sccp_stop_co_timer (p_ccb, timer_name, p_ecode) ;
  return(sccp_start_co_timer (p_ccb, timer_name, p_ecode));
}


/* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE 

/******************************************************************************
**
**  FUNCTION :
**    Forward DT2 message
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function sends out DT2 on the network
**
******************************************************************************/

return_t
sccp_utl_fwd_dt2 
#ifdef ANSI_PROTO
  (msg_info_t *p_info, 
   sccp_ccb_t *p_ccb)
#else
  (p_info, p_ccb)
  msg_info_t *p_info;
  sccp_ccb_t *p_ccb;
#endif
{
  U16bit   full_data_len, transmitted_bytes ;
  U16bit new_data_len, new_api_len, j;
  U8bit	   num_segs, uw_edge, num_nsdu_can_send, i = 0;
  sc_queue_t *p_tmp;
  U8bit    *p_buf;
  return_t result = SS7_FAILURE ;
  error_t  ecode ;

  while (p_ccb->p_trans_queue)
  {
    if (MTP3_UP_TRANSFER_INDICATION == p_ccb->p_trans_queue->api_id)
    {
      p_info->m3_data.len = p_ccb->p_trans_queue->len;
      p_info->m3_data.p = p_ccb->p_trans_queue->p_buf;
      sccp_parse_dt2 (p_info);
    }

    if (SCCP_N_DATA_REQUEST == p_ccb->p_trans_queue->api_id)
    {
      sccp_parse_n_data_request_api (p_ccb->p_trans_queue->p_buf, p_info);
    }

    /* SPR 1362: check if p_ccb->w == 0 */
    if (p_ccb->w == 0)
      break;

	/** SPR# 10691 Fix **/
	p_info->p_ccb = p_ccb;

    num_segs =  p_info->data.len / SCCP_MAX_CO_SEG_SIZE;
    num_segs += (p_info->data.len % SCCP_MAX_CO_SEG_SIZE)?1:0;

    /* check if window permits to add this many segments */
    uw_edge = (p_ccb->lw_edge + p_ccb->w) % 128;
    num_nsdu_can_send = (uw_edge - p_ccb->send_seq) % 128;
  
    /* delete the node from queue */
   /* SPR #5269 Fix starts     */
    p_tmp = p_ccb->p_trans_queue;
/** SPR 5526 FIX
    p_ccb->p_trans_queue =  p_tmp->p_next;
***/

    if (num_segs > num_nsdu_can_send)
    {
      SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
       ("SCCP::SCOC: Message exceeds credit limit\n"));
    }
  /* SPR #5269 Fix ends */
 
    result = SS7_SUCCESS ;

    p_info->msg_type = DT2_MSG_TYPE;
    sccp_utl_fill_nw_info (p_info, p_ccb) ;
    full_data_len = p_info->data.len;
    p_buf = p_info->data.p;
    transmitted_bytes = 0;
	if(num_nsdu_can_send == 0)
		return SS7_SUCCESS;
    do
    {
      p_info->seq_seg = 0 ;
      if ((full_data_len - transmitted_bytes) > SCCP_MAX_CO_SEG_SIZE)
      {
        p_info->data.len = SCCP_MAX_CO_SEG_SIZE;
        SET_M_BIT_DT2 (p_info);
      }
      else
      {
        p_info->data.len = full_data_len - transmitted_bytes;
        CLR_M_BIT_DT2 (p_info);
      }
      p_info->data.p = p_buf + transmitted_bytes;
      transmitted_bytes += p_info->data.len;
      PUT_PS_PR (p_info, p_ccb);
      sccp_route_co_msg (p_info);

      /* SPR 1689: Increment statistics only if p_ss exists */
      if (p_ccb->p_ss)
      	SC_STAT_Q752_INR_ORIG_MSG_DT2 (p_ccb->p_ss->ssn) ;

      p_ccb->send_seq = INC_SEQ_NUM (p_ccb->send_seq);
	  /** SPR 11112 - Fix Start **/
	  /* Update seq_seg field in corresoponding ccb */
	  UPDATE_SEQ_SEG_IN_CCB(p_ccb);
	  /** SPR 11112 - Fix End  **/
      /* restart T_inact_send timer */
      if (sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, &ecode) != SS7_SUCCESS)
      {
        /* Error */
      }
	/**** SPR 5509 5446  Fix starts ****/
	i++;
	if ((i == num_nsdu_can_send) && (full_data_len > transmitted_bytes))
        {
                new_api_len = p_ccb->p_trans_queue->p_buf[3] | (p_ccb->p_trans_queue->p_buf[4] << 8);
                new_api_len = new_api_len - transmitted_bytes;
                p_ccb->p_trans_queue->p_buf[3] = (U8bit)new_api_len;
                p_ccb->p_trans_queue->p_buf[4] = (U8bit)(new_api_len >> 8);


#ifdef SCCP_CONNECTION_ID_CHANGES
                new_data_len = p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET] | (p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET+1] << 8);
                new_data_len = new_data_len - transmitted_bytes;
                p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET] = (U8bit)new_data_len;
                p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET+1] = (U8bit)(new_data_len >> 8);
#else
                new_data_len = p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET] | (p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET+1] << 8);
                new_data_len = new_data_len - transmitted_bytes;
                p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET] = (U8bit)new_data_len;
                p_ccb->p_trans_queue->p_buf[DATA_LEN_OFFSET+1] = (U8bit)(new_data_len >> 8);
#endif


                for (j = 0 ; j < full_data_len-transmitted_bytes; j++)
#ifdef SCCP_CONNECTION_ID_CHANGES
                        p_ccb->p_trans_queue->p_buf[11+j] = p_ccb->p_trans_queue->p_buf[11+j+transmitted_bytes];
#else
                        p_ccb->p_trans_queue->p_buf[9+j] = p_ccb->p_trans_queue->p_buf[9+j+transmitted_bytes];
#endif
                return SS7_SUCCESS;
        }
	/**** SPR 5509 5446 Fix ends ****/

    }while (full_data_len != transmitted_bytes);
    p_ccb->p_trans_queue =  p_tmp->p_next;
    sccp_free ((U8bit *) p_tmp);
  }
  p_info->p_api = (U8bit *)SS7_NULL;
  return (result) ;
}

#endif     /* #ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE */

/******************************************************************************
**
**  FUNCTION :
**    Handles reassembly
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function handles the reassembly of the messages
**
******************************************************************************/

return_t
sccp_handle_reassembly
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   sccp_ccb_t    *p_ccb)
#else
  (p_info, p_ccb)
  msg_info_t    *p_info ;
  sccp_ccb_t    *p_ccb ;
#endif
{
  sc_queue_t *p_recv_queue, *p_tmp_node;

  if (SCCP_GET_M_BIT(p_ccb, p_info))
  {
    /* More data is expected for the M bit sequence */

    /* Are we ignoring some M bit sequence */
    if (!SCCP_IS_IGNORE_M_BIT_SEQ (p_ccb))
    {
      if (sccp_utl_add_to_rx_queue (p_info, p_ccb) == SS7_FAILURE)
      {
        p_recv_queue = p_ccb->p_recv_queue;
        SCCP_SET_IGNORE_M_BIT_SEQ (p_ccb);
        while (p_recv_queue != (sc_queue_t *)SS7_NULL)
        {
          p_tmp_node = p_recv_queue;
          p_recv_queue = p_recv_queue->p_next;
          sccp_free ((U8bit *) p_tmp_node);
        }
        p_ccb->p_recv_queue = (sc_queue_t *) SS7_NULL;
        return (SS7_FAILURE);
      }
    }
  }
  else
  {
    if (!SCCP_IS_IGNORE_M_BIT_SEQ (p_ccb))
    {
      /* 
       * A valid NSDU can be now assembled. last segment will be picked from
       * p_info. 
       */
      sccp_build_n_data_ind_api (p_info, p_ccb);
    }
    SCCP_CLR_IGNORE_M_BIT_SEQ (p_ccb);
  }
  return (SS7_SUCCESS);
}

/* Added this to enable compiling without class 3 services */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

/******************************************************************************
**
**  FUNCTION :
**    Reset the Connection
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function builds up the Reset request and sends it on the network
**
******************************************************************************/

void
sccp_utl_reset_conn
#ifdef ANSI_PROTO
  (msg_info_t  *p_info)
#else
  (p_info)
  msg_info_t   *p_info;
#endif
{
  sccp_ccb_t *p_ccb, *p_coupled_ccb ;
  return_t result ;
  error_t	ecode ;
  conn_entry_t  conn ;

  p_ccb = p_info->p_ccb ;
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
  result = sccp_start_co_timer (p_ccb, SCCP_T_RESET_TIMER, &ecode) ;
  if (result != SS7_SUCCESS)
  {
    /* Error */
  }

  /* restart T_inact_send timer */
  result = sccp_stop_co_timer (p_ccb, SCCP_T_IAS_TIMER, &ecode) ;
  if (result != SS7_SUCCESS)
  {
   	/* Error */
  }

  /* SPR 1338: Start fix 
   * Start T_inact_send timer 
   */
  result = sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, &ecode) ;
  if (result != SS7_SUCCESS)
  {
	/* Error */
  }
  /* SPR 1338: End fix */

  /* reset variables and discard all the queued and unacked messages */
  sccp_reset_variables (p_ccb) ;

  /* send CONN alarm to sm */
  conn.conn_id = p_info->conn_id;    
  conn.reset_cause = p_info->reset_cause;
  conn.originator = sccp_utl_get_rsr_originator(p_info->reset_cause);
  
  SCCP_EVENT_ALARM (SCCP_SM_OBJECT_CONN, CONN_RESET, SS7_NULL, SS7_NULL, &conn);

  if (IS_COUPLING_PRESENT (p_ccb))
  {
    p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;

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
    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_RESET_TIMER, &ecode) ;
    if (result != SS7_SUCCESS)
    {
        /* Error */
    }

    /* restart T_inact_send timer */
    result = sccp_stop_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, &ecode) ;
    if (result != SS7_SUCCESS)
    {
        /* Error */
    }
    /* SPR 1338: Start fix
     * Start T_inact_send timer
     */
    result = sccp_start_co_timer (p_coupled_ccb, SCCP_T_IAS_TIMER, &ecode) ;
    if (result != SS7_SUCCESS)
    {
      /* Error */
    }
    /* SPR 1338: End fix */

    /* reset variables and discard all the queued and unacked messages */
    sccp_reset_variables (p_coupled_ccb) ;
  }
  else
  {
    sccp_build_n_reset_ind_api (p_info, p_ccb) ;
  }

}
#endif    /* #ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE */

/******************************************************************************
**
**  FUNCTION :
**    Add to the Transmit queue
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function adds the buffer to the transmit queue
**
******************************************************************************/

return_t
sccp_utl_add_to_tx_queue
#ifdef ANSI_PROTO
  (msg_info_t	*p_info,
  sccp_ccb_t *p_ccb)
#else
  (p_info, p_ccb)
  msg_info_t *p_info;
  sccp_ccb_t *p_ccb;
#endif
{
  sc_queue_t  *p_aloc_node, *p_tmp_node ;

  /* Allocate memory for the node to be attached */
  p_aloc_node = (sc_queue_t *) (void *) sccp_malloc (SCCP_QUEUE_HDR_SIZE+ 
      GET_API_LEN(p_info->p_api));
  /* Couldn't get memory so return Failure */
  if (p_aloc_node == (sc_queue_t *)SS7_NULL)
    return (SS7_FAILURE) ;

  /* Get API id */
  p_aloc_node->api_id = GET_API_ID (p_info->p_api);

  if (p_aloc_node->api_id == SCCP_N_DATA_REQUEST)
    p_aloc_node->len = GET_API_LEN (p_info->p_api);
  else
    p_aloc_node->len = p_info->m3_data.len;

  p_aloc_node->p_buf = GET_QUEUE_DATA_PTR (p_aloc_node); 

  if (p_aloc_node->api_id == SCCP_N_DATA_REQUEST)
    sccp_memcpy (p_aloc_node->p_buf, p_info->p_api, p_aloc_node->len);
  else
    sccp_memcpy (p_aloc_node->p_buf, p_info->m3_data.p, p_aloc_node->len);

  p_aloc_node->p_next = (sc_queue_t *)SS7_NULL ;

  if (p_ccb->p_trans_queue == SS7_NULL)
  {
    p_ccb->p_trans_queue = p_aloc_node;
  }
  else
  {
    p_tmp_node = p_ccb->p_trans_queue;
    while (p_tmp_node->p_next != SS7_NULL)
    {
      p_tmp_node = p_tmp_node->p_next;
    }
    p_tmp_node->p_next = p_aloc_node;
  }
  return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Add to the Receive queue
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function copies the data portion from the p_info to the queue node
**
******************************************************************************/

return_t
sccp_utl_add_to_rx_queue
#ifdef ANSI_PROTO
  (msg_info_t    *p_info,
   sccp_ccb_t	 *p_ccb)
#else
  (p_info, p_ccb)
  msg_info_t    *p_info ;
  sccp_ccb_t	 *p_ccb ;
#endif
{
  sc_queue_t  *p_aloc_node ;
  sc_queue_t  *p_tmp_node ;

  /* Allocate memory for the node to be attached to the queue */
  p_aloc_node = (sc_queue_t *) (void *) sccp_malloc (p_info->data.len + 
      SCCP_QUEUE_HDR_SIZE);
  /* Couldn't allocate memory, so return SS7_FAILURE */
  if (p_aloc_node == (sc_queue_t *)SS7_NULL)
    return (SS7_FAILURE) ;

  /* fill the data len */
  p_aloc_node->len = p_info->data.len;
  /* Get the data pointer */
  p_aloc_node->p_buf = GET_QUEUE_DATA_PTR (p_aloc_node); 
  p_aloc_node->p_next = (sc_queue_t *)SS7_NULL;

  /* Copy the data from the p_info to the p_aloc_node */
  sccp_memcpy (p_aloc_node->p_buf, p_info->data.p, p_info->data.len);

  /* first node */
  if (p_ccb->p_recv_queue == SS7_NULL)
  {
    p_ccb->p_recv_queue = p_aloc_node;
  }
  else
  {
    /* attach the buffer at the end */
    p_tmp_node = p_ccb->p_recv_queue;
    while (p_tmp_node->p_next != SS7_NULL)
    {
      p_tmp_node = p_tmp_node->p_next;
    }
    p_tmp_node->p_next = p_aloc_node;
  }

  return (SS7_SUCCESS);
}

/******************************************************************************
**
**  FUNCTION :
**    Get SP entry from the Logical user id
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function fills up the SS entry and the SP entry in the p_info
**    structure based on the logical user id passed to it.
**
******************************************************************************/

void
sccp_utl_get_sp_from_logid
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   U16bit     l_id)
#else
  (p_info, l_id)
  msg_info_t  *p_info;
  U16bit      l_id;
#endif
{
  U8bit                  count ;
  sc_reg_entry_t   *p_sccp_reg ;

  /* Search for the registry entry on the basis of logical user id */
  for (count = 0; count < MAX_LOCAL_USERS; count++)
  {
    p_sccp_reg = &sccp_reg_table [count] ;
    if ((p_sccp_reg->uid == l_id) &&
        (p_sccp_reg->registered == SS7_TRUE))
    {
      /* Associate the SP and the SS entry with the p_info */
      p_info->p_sp = p_sccp_reg->p_sp ;
      p_info->p_ss = p_sccp_reg->p_ss ;
      return ;
    }
  }
 
  SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
    ("SCCP::SCOC: LogUId[%d] Not registered\n", 
      l_id)) ;
  /* Not found : so return SS7_NULL */
  p_info->p_sp = (sp_entry_t *)SS7_NULL;
  p_info->p_ss = (ss_entry_t *)SS7_NULL;
  return ;
}

/******************************************************************************
**
**  FUNCTION :
**    Get the CREF Originator.
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function gets the CREF originator on the basis of reason which is
**    passed to it as a parameter.
**
******************************************************************************/

U8bit
sccp_utl_get_cref_originator
#ifdef ANSI_PROTO
  (U8bit       reason)
#else
  (reason)
  U8bit        reason;
#endif
{
  U8bit originator;

  switch (reason)
  {
    case SCCP_RFC_END_USER_ORIGINATED :
    case SCCP_RFC_END_USER_CONGESTION :
    case SCCP_RFC_END_USER_FAILURE :
    case SCCP_RFC_SCCP_USER_ORIGINATED :
    case SCCP_RFC_ACCESS_FAILURE :
    case SCCP_RFC_ACCESS_CONGESTION :
    case SCCP_RFC_INCOMPATIBLE_USER_DATA :
        originator = SCCP_NETWORK_SERVICE_USER ;
        break ;
    case SCCP_RFC_DESTINATION_ADDRESS_UNKNOWN :
    case SCCP_RFC_DESTINATION_INACCESSIBLE :
    case SCCP_RFC_NR_QOS_NOT_AVAILABLE_NON_TRANSIENT :
    case SCCP_RFC_NR_QOS_NOT_AVAILABLE_TRANSIENT :
    case SCCP_RFC_SUBSYSTEM_FAILURE :
    case SCCP_RFC_CONNECTION_ESTABLISHMENT_TIMER_EXPIERD :
    case SCCP_RFC_HOP_COUNTER_VIOLATION :
    case SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE :
    case SCCP_RFC_UNEQUIPPED_USER :
        originator = SCCP_NETWORK_SERVICE_PROVIDER ;
        break ;
    default :
        originator = SCCP_ORIGINATOR_UNDEFINED ;
        break ;
  }
  return (originator) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Get the RLSD Originator
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function returns the originator based on the reason passed to this
**    function as a parameter.
**
******************************************************************************/

U8bit
sccp_utl_get_rlsd_originator
#ifdef ANSI_PROTO
  (U8bit       reason)
#else
  (reason)
  U8bit        reason;
#endif
{
  U8bit originator;

  switch (reason)
  {
    case SCCP_RLSDC_END_USER_ORIGINATED :
    case SCCP_RLSDC_END_USER_CONGESTED :
    case SCCP_RLSDC_END_USER_FAILURE :
    case SCCP_RLSDC_SCCP_USER_ORIGINATED :
    case SCCP_RLSDC_ACCESS_FAILURE :
    case SCCP_RLSDC_ACCESS_CONGESTION :
    case SCCP_RLSDC_SUBSYSTEM_CONGESTION :
        originator = SCCP_NETWORK_SERVICE_USER ;
        break ;
    case SCCP_RLSDC_REMOTE_PROCEDURE_ERROR :
    case SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA :
    case SCCP_RLSDC_SUBSYSTEM_FAILURE :
    case SCCP_RLSDC_MTP_FAILURE :
    case SCCP_RLSDC_NETWORK_CONGESTION :
    case SCCP_RLSDC_RESET_TIMER_EXPIRED :
    case SCCP_RLSDC_IT_TIMER_EXPIRED :
    case SCCP_RLSDC_SCCP_FAILURE :
        originator = SCCP_NETWORK_SERVICE_PROVIDER ;
        break ;
    default :
        originator = SCCP_ORIGINATOR_UNDEFINED ;
        break ;
  }
  return (originator) ;
}

/******************************************************************************
**
**  FUNCTION :
**    Get the RSR Originator.
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function gets the Reset Request originator. On the basis of reason
**    it assigns a originator which is returned to the caller.
**
******************************************************************************/

U8bit
sccp_utl_get_rsr_originator
#ifdef ANSI_PROTO
  (U8bit        reason)
#else
  (reason)
  U8bit        reason;
#endif
{
  U8bit originator;

  switch (reason)
  {
    case SCCP_RSC_END_USER_ORIGINATED :
    case SCCP_RSC_SCCP_USER_ORIGINATED :
    case SCCP_RSC_REMOTE_END_UESR_OPERATIONAL :
    case SCCP_RSC_ACCESS_OPERATIONAL :
      originator = SCCP_NETWORK_SERVICE_USER ;
      break ;
    case SCCP_RSC_INCORRECT_PS :
    case SCCP_RSC_INCORRECT_PR :
    case SCCP_RSC_RPE_MSG_OUT_OF_WINDOW :
    case SCCP_RSC_RPE_INCORRECT_PS :
    case SCCP_RSC_RPE_GENERAL :
    case SCCP_RSC_NETWORK_OPERATIONAL :
    case SCCP_RSC_NETWORK_CONGESTION :
      originator = SCCP_NETWORK_SERVICE_PROVIDER ;
      break ;
    default :
      originator = SCCP_ORIGINATOR_UNDEFINED ;
      break ;
  }
  return (originator) ;
}


/* SPR 1350: Start */

/******************************************************************************
**
**  FUNCTION :
**    Checks the slr value of the received message
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function checks if the source local reference number in the received 
**    message matches with the one stored locally.
**
******************************************************************************/

return_t
sccp_utl_check_slr 
#ifdef ANSI_PROTO
  (msg_info_t   *p_info)
#else
  (p_info)
   msg_info_t   *p_info;
#endif
{
  return_t 	result = SS7_FAILURE;
  sccp_ccb_t 	*p_ccb;
   
  p_ccb = p_info->p_ccb;
  switch (p_info->event)
  {
    case SCCP_RSR_EVENT:
    case SCCP_RSC_EVENT:
    case SCCP_RLSD_EVENT:
    case SCCP_RLC_EVENT:
    case SCCP_IT_EVENT:
       	if (p_info->slr == p_ccb->dlr)
	  result = SS7_SUCCESS; 
   	break;	

    default: 
	result = SS7_SUCCESS;    
        break;
  }
  return (result);
}

/******************************************************************************
**
**  FUNCTION :
**    Checks the opc value of the received message
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function checks if the originating point code value in the received 
**    message matches with the one stored locally.
**
******************************************************************************/

return_t
sccp_utl_check_opc 
#ifdef ANSI_PROTO
  (msg_info_t   *p_info)
#else
  (p_info)
   msg_info_t   *p_info;
#endif
{
  return_t 	result = SS7_FAILURE;
  sccp_ccb_t 	*p_ccb;

  p_ccb = p_info->p_ccb;
  switch (p_info->event)
  {
   case SCCP_CR_EVENT:
   case SCCP_CC_EVENT:
   case SCCP_CREF_EVENT:
    	result = SS7_SUCCESS;
	break;

  default: 
      	if (p_ccb->dpc == p_info->opc)
    	  result = SS7_SUCCESS;
	break;
  }

  return (result);
}


/******************************************************************************
**
**  FUNCTION :
**    Checks if message contains SLR
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function returns SS7_SUCCESS if the message received contains SLR value
**
******************************************************************************/

return_t
is_slr_present 
#ifdef ANSI_PROTO
  (U8bit   event)
#else
  (event)
   U8bit   event;
#endif
{

  switch (event)
  {
   case SCCP_CR_EVENT:
   case SCCP_CC_EVENT:
   case SCCP_RLSD_EVENT:
   case SCCP_RLC_EVENT:
   case SCCP_RSR_EVENT:
   case SCCP_RSC_EVENT:
   case SCCP_IT_EVENT:
	return (SS7_SUCCESS);

  default: 
	return (SS7_FAILURE);
  }
}

/* SPR 1350: End */

/* SPR 1773: Start */
/* Added two new functions */
/******************************************************************************
**
**  FUNCTION :
**    Forward ED message
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function sends out ED on the network
**
******************************************************************************/

return_t
sccp_utl_fwd_ed
#ifdef ANSI_PROTO
  (msg_info_t *p_info,
   sccp_ccb_t *p_ccb,
   error_t    *p_ecode)
#else
  (p_info, p_ccb)
  msg_info_t *p_info;
  sccp_ccb_t *p_ccb;
  error_t    *p_ecode;
#endif
{
  sc_queue_t	*p_tmp_node;
  return_t      result; 

	SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_fwd_ed \n")) ;

	if ((p_ccb->p_ed_trans_queue) && (p_ccb->num_ed_in_queue > 0))
	{
		sccp_parse_n_ed_data_request_api(p_ccb->p_ed_trans_queue->p_buf,
						 p_info);

		/* Remove first node from the queue */
		p_tmp_node = p_ccb->p_ed_trans_queue;
		p_ccb->p_ed_trans_queue = p_tmp_node->p_next;	
		p_ccb->num_ed_in_queue--;

		/* Build ED message */
		p_info->msg_type = ED_MSG_TYPE;
	    	sccp_utl_fill_nw_info (p_info, p_ccb) ;

		/** SPR# 10692 Fix **/
		p_info->p_ccb = p_ccb;

		sccp_route_co_msg (p_info);
		if (p_ccb->p_ss)
        		SC_STAT_Q752_INR_ORIG_MSG_ED (p_ccb->p_ss->ssn) ;
		SCCP_SET_UNACK_ED (p_ccb) ;

		/* Restart T_inact_send timer */
    		result = sccp_restart_co_timer (p_ccb, SCCP_T_IAS_TIMER, 
								p_ecode) ;
/* SPR 8985 - Fix Start */
#if 0
/* SPR 8985 - Fix End  */
    		if (result != SS7_SUCCESS)
    		{
      			/* Error */
    		}
/* SPR 8985 - Fix Start */
#endif
/* SPR 8985 - Fix End  */
		
		sccp_free ((U8bit *) p_tmp_node);
	}
	p_info->p_api = (U8bit *) SS7_NULL;
	return (SS7_SUCCESS);
}

/******************************************************************************
**
**  FUNCTION :
**    Add to the ED Transmit queue
**
*******************************************************************************
**
**  DESCRIPTION :
**    This function adds the buffer to the transmit queue for ED messages
**
******************************************************************************/
 
return_t
sccp_utl_add_to_ed_tx_queue
#ifdef ANSI_PROTO
  (msg_info_t   *p_info,
  sccp_ccb_t *p_ccb)
#else
  (p_info, p_ccb)
  msg_info_t *p_info;
  sccp_ccb_t *p_ccb;
#endif
{
  sc_queue_t	*p_new_node, *p_tmp_node;

  	SCCP_UT_TRACE (("SCCP::UT: Inside sccp_utl_add_to_ed_tx_queue\n"));

	if (p_ccb->num_ed_in_queue >= MAX_ED_WAITING)
  	{
		/* Error */
  		SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
               	     ("SCCP::SCOC: ED queue is full - discarding message\n")); 
		return(SS7_FAILURE);
	}

  	/* Allocate memory for the new node to be attached */
	p_new_node = (sc_queue_t *) (void *)sccp_malloc (SCCP_QUEUE_HDR_SIZE +
				GET_API_LEN(p_info->p_api)); 

	if (p_new_node == (sc_queue_t *) SS7_NULL)
		return (SS7_FAILURE);

  	SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE,
               ("SCCP::SCOC: Adding to ED tx queue\n")); 

	/* Fill in queue header details */
	p_new_node->api_id = GET_API_ID (p_info->p_api);
	p_new_node->len = GET_API_LEN (p_info->p_api);
	p_new_node->p_buf = GET_QUEUE_DATA_PTR (p_new_node);
	p_new_node->p_next = (sc_queue_t *) SS7_NULL;
	
	/* Fill in data */
	sccp_memcpy (p_new_node->p_buf, p_info->p_api, p_new_node->len);

	/* Add node to the end of the ED transmit queue */
	if (p_ccb->p_ed_trans_queue == ((sc_queue_t *) SS7_NULL))
		p_ccb->p_ed_trans_queue = p_new_node;
	else
	{
		p_tmp_node = p_ccb->p_ed_trans_queue;
		while (p_tmp_node->p_next != (sc_queue_t *)SS7_NULL)
			p_tmp_node = p_tmp_node->p_next;
		p_tmp_node->p_next = p_new_node;
	}
	p_ccb->num_ed_in_queue++;
	return (SS7_SUCCESS);
}
/* SPR 1773: End */


/* SPR # 6126 Fix Start */

/******************************************************************************
  **
  **  FUNCTION :
  **   Calculate the hash index. 
  **
  *******************************************************************************
  **
  **  DESCRIPTION :
  **    This function calculates the hash index based on the logical user id
  **    and the correlation id. The hash table stores the connection ids. 
  **
  ******************************************************************************/
 
#ifdef SCCP_CONNECTION_ID_CHANGES
U16bit
sccp_utl_get_hash_index
#ifdef ANSI_PROTO
  (U16bit log_id,
   U32bit  corr_id) /* Amaresh U16 U32 */
#else
  (log_id, corr_id)
  U16bit log_id;
  U32bit  corr_id;  /* Amaresh U16 U32 */
#endif

{

        U32bit  hash_index;/* Changed by Amaresh hash index from U16bit to U32bit as on dated 11-03-16 */

        hash_index = 0x0000;

        hash_index = ((log_id ^ corr_id) % MAX_SCCP_CO_HASH_TABLE_SIZE);

        return hash_index;
}

#else

U16bit
sccp_utl_get_hash_index
#ifdef ANSI_PROTO
  (U16bit log_id,
   U8bit  corr_id)
#else
  (log_id, corr_id)
  U16bit log_id;
  U8bit  corr_id;
#endif

{

    U32bit  hash_index;/* Changed by Amaresh hash index from U16bit to U32bit as on dated 11-03-16 */

    hash_index = 0;

    hash_index = ((log_id ^ corr_id) % MAX_SCCP_CO_HASH_TABLE_SIZE);

    return hash_index;
}

#endif

/******************************************************************************
**
**  FUNCTION :
**    Add CCB to the hash table
**
*******************************************************************************
**
**  DESCRIPTION :
**         This function creates an entry for the newly allocated ccb block
**         in the hash table. In case there is collision in the hash table
**         linear chaining is used to resolve the clash.
**
******************************************************************************/

return_t
sccp_utl_add_ccb_to_hash_tbl
#ifdef ANSI_PROTO
  (U32bit ccb_id, U16bit l_id, 
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit corr_id)
#else
  U8bit corr_id)
#endif
#else
  (ccb_id, l_id, corr_id)
  U32bit ccb_id;
  U16bit l_id;
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit corr_id; /* Amaresh U16 U32 */
#else
  U8bit corr_id;
#endif
#endif
{
  U32bit      hash_index;
  U32bit      temp_ccb_id;

  /* Create an entry in the hash table */
  hash_index = sccp_utl_get_hash_index(l_id, corr_id);
LOG_PRINT(CRITICAL,"sccp_utl_add_ccb_to_hash_tbl:corr_id[%d] log_id[%d] ccb_id[%d] hash_index[%d]\n",corr_id,l_id,ccb_id,hash_index);
  if(sccp_hash_table[hash_index] == SCCP_INVALID_CCB_ID)
  {
    sccp_hash_table[hash_index] = ccb_id;
		LOG_PRINT(CRITICAL,"sccp_utl_add_ccb_to_hash_tbl:SS7_SUCCESS");
    return SS7_SUCCESS;
  }
  else
  {
    temp_ccb_id = sccp_hash_table[hash_index];
    while(sccp_ccb[temp_ccb_id].next_ccb_id != SCCP_INVALID_CCB_ID)
	{
      if ( (sccp_ccb[temp_ccb_id].l_id == l_id) && 
           (sccp_ccb[temp_ccb_id].corr_id == corr_id))
      {
					LOG_PRINT(CRITICAL,"sccp_utl_add_ccb_to_hash_tbl:SS7_FAILURE");
          /* Duplicate Corr ID */
          return  SS7_FAILURE;
      }
      temp_ccb_id = sccp_ccb[temp_ccb_id].next_ccb_id;
			LOG_PRINT(CRITICAL,"sccp_utl_add_ccb_to_hash_tbl:temp_ccb_id[%d]",temp_ccb_id);
	}

    sccp_ccb[ccb_id].prev_ccb_id = temp_ccb_id;
    sccp_ccb[temp_ccb_id].next_ccb_id = ccb_id;
		LOG_PRINT(CRITICAL,"sccp_utl_add_ccb_to_hash_tbl:SS7_SUCCESS ccb_id[%d]",ccb_id);
    return SS7_SUCCESS;
  }
  
}

/******************************************************************************
**
**  FUNCTION :
**    Remove CCB from the hash table
**
*******************************************************************************
**
**  DESCRIPTION :
**		Remove the CCB from the CCB chain; if CCB chain becomes 
**  empty, then set hash table entry to SCCP_INVALID_CCB_ID
**
******************************************************************************/

void
sccp_utl_del_ccb_from_hash_tbl
#ifdef ANSI_PROTO
  (U8bit c_state, U16bit l_id, 
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit corr_id)
#else
  U8bit corr_id)
#endif
#else
  (c_state, l_id, corr_id)
  U8bit c_state;
  U16bit l_id;
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit corr_id; /* Amaresh U16 U32 */
#else
  U8bit corr_id;
#endif
#endif
{
  U32bit hash_index;
  U32bit ccb_id;
  sccp_ccb_t *p_ccb;

  hash_index = sccp_utl_get_hash_index(l_id,corr_id);
  ccb_id = sccp_hash_table[hash_index];
LOG_PRINT(CRITICAL,"sccp_utl_del_ccb_from_hash_tbl:corr_id[%d] log_id[%d] ccb_id[%d] hash_index[%d]\n",corr_id,l_id,ccb_id,hash_index);
  while(ccb_id != SCCP_INVALID_CCB_ID)
  {
  	p_ccb = &(sccp_ccb[ccb_id]);
    /* SPR 9126 - Fix Start */ 
    /*if ((p_ccb->c_state == c_state) && */
    if (((p_ccb->c_state == c_state) || (p_ccb->c_state == SCCP_CONN_START )) &&
    /* SPR 9126 - Fix End  */
      (p_ccb->l_id  == l_id) &&
      (p_ccb->corr_id  == corr_id))
    {
					LOG_PRINT(CRITICAL,"sccp_utl_del_ccb_from_hash_tbl:Found matching l_id,corr_id");
      SCCP_STACK_TRACE (SCOC_TRACE, BRIEF_TRACE, ("Found matching l_id, \
	  and corr_id \n")) ;
	  p_ccb->corr_id = 0;

      /* Remove CCB from Hash Table */

      if(p_ccb->next_ccb_id == SCCP_INVALID_CCB_ID && \
         p_ccb->prev_ccb_id == SCCP_INVALID_CCB_ID)
      {
         /* This node is the only node in the list */
         sccp_hash_table[hash_index] = SCCP_INVALID_CCB_ID;
         break ;
      }

      if(p_ccb->next_ccb_id == SCCP_INVALID_CCB_ID && \
         p_ccb->prev_ccb_id != SCCP_INVALID_CCB_ID)
      {
         /* This is the last node in the link list of ccb */
         sccp_ccb[p_ccb->prev_ccb_id].next_ccb_id = SCCP_INVALID_CCB_ID;
         p_ccb->prev_ccb_id = SCCP_INVALID_CCB_ID;
         break ;
      }   
      if(p_ccb->next_ccb_id != SCCP_INVALID_CCB_ID && \
         p_ccb->prev_ccb_id != SCCP_INVALID_CCB_ID)
      {
         /* This is a middle node in the link list */
         sccp_ccb[p_ccb->prev_ccb_id].next_ccb_id = p_ccb->next_ccb_id;
         sccp_ccb[p_ccb->next_ccb_id].prev_ccb_id = p_ccb->prev_ccb_id;
         p_ccb->next_ccb_id = SCCP_INVALID_CCB_ID;
         p_ccb->prev_ccb_id = SCCP_INVALID_CCB_ID;
         break ;
      }
      if(p_ccb->next_ccb_id !=  SCCP_INVALID_CCB_ID && \
         p_ccb->prev_ccb_id == SCCP_INVALID_CCB_ID)
      {
         /* This is the first node in the link list, therefore we need to 
         ** change the entries in the hash table also
         */
         sccp_ccb[p_ccb->next_ccb_id].prev_ccb_id = SCCP_INVALID_CCB_ID;
         sccp_hash_table[hash_index] = sccp_ccb[p_ccb->next_ccb_id].ccb_id;
         p_ccb->next_ccb_id = SCCP_INVALID_CCB_ID;
         p_ccb->prev_ccb_id = SCCP_INVALID_CCB_ID;
         break;
      }
      
      break;
    }

	ccb_id = p_ccb->next_ccb_id;
  }
}

/* SPR # 6126 Fix End */

#else

/*****************************************************************************
**	This extern declaration is required as BCC reports error if the 
** source file is empty after preprocessing. This declaration enables compilation
** without SCCP_INCLUDE_CO_SERVICE flag using BCC.
**
*****************************************************************************/

extern return_t sccp_co_dummy _ARGS_ ((void));

#endif

