/****************************************************************************
**
**  FUNCTION:
**  File containing all the global declarations and variables required
**  for SCCP connection control block and the related FSM.
**
****************************************************************************
**
**  FILE NAME:
**    sc_ccb.h
**
**  DESCRIPTION:
**  This file contains the necessary data types and the defined values
**  for the SCCP Connection Oriented Protocol entity of SS7 stack
**
**  Date        Name               Reference     Reason
**  _______________________________________________________________
**  25Jan'03    Suyash Tripathi					Fixed SPR #11112
**  04Mar'02    Sachin bhatia					Fixed SPR #8551
**  26Dec'01    Prateek Bidwalkar				Fixed SPR #7450
**  10Aug'01    Aman Kapoor						Fixed SPR #5929
**  11Sep'01    Prateek Bidwalkar               Fixed SPR 6126
**  28May'01    Rajesh Mehta                     increased conn_id to U32
**                                               AND CORR-ID TO U16 if flag
**                                             SCCP_CONNECTION_ID_CHANGES is defined
**  08Jun'00    Ramu Kandula                     Fixed SPR # 2574
**  18Aug'98    Praneet Khare                    Adding Trace Strings
**  07Jul'98    Praneet Khare      HSS:20800011  Original
**
**  Copyright 1998, Hughes Software Systems, Inc
**
***************************************************************************/

#ifndef __SC_CCB_H
#define __SC_CCB_H

#include "sc_stgl.h"

#define NUM_NODES                  128
#define SCCP_DEFAULT_CREDIT        64
#define SCCP_INVALID_CCB_ID        0xffffffff
/* SPR # 6126 Fix Start */
/*#define MAX_SCCP_CO_HASH_TABLE_SIZE        4096*//* Original value changed by Amaresh as on dated 11-03-16*/
#define MAX_SCCP_CO_HASH_TABLE_SIZE        65535 /*16384*/ /* 2power 14 */
/* SPR # 6126 Fix End */

/***************************************************************************
**
**  The states of the Connection 
**
***************************************************************************/

#define SCCP_MAX_CO_STATES         0x06

#define  SCCP_CONN_IDLE         0x00
#define  SCCP_CONN_START        0x01
#define  SCCP_CONN_ESTABLISHED  0x02
#define  SCCP_CONN_CLOSING      0x03
#define  SCCP_CONN_CLOSED       0x04
#define  SCCP_CONN_RESET        0x05

/***************************************************************************
**
**  The various Events for SCCP Connection Oriented Protocol
**
***************************************************************************/

#define  SCCP_N_CONNECT_REQUEST_EVENT   0x00
#define  SCCP_N_CONNECT_RESPONSE_EVENT  0x01
#define  SCCP_N_DISCONNECT_REQ_EVENT    0x02
#define  SCCP_REQUEST_TYPE_1_EVENT      0x03
#define  SCCP_REQUEST_TYPE_2_EVENT      0x04
#define  SCCP_N_RESET_REQUEST_EVENT     0x05
#define  SCCP_N_RESET_RESPONSE_EVENT    0x06
#define  SCCP_N_DATA_REQUEST_EVENT      0x07
#define  SCCP_N_EXP_DATA_REQUEST_EVENT  0x08
#define  SCCP_CR_EVENT                  0x09
#define  SCCP_CC_EVENT                  0x0A
#define  SCCP_CREF_EVENT                0x0B
#define  SCCP_RLSD_EVENT                0x0C
#define  SCCP_RLC_EVENT                 0x0D
#define  SCCP_RSR_EVENT                 0x0E
#define  SCCP_RSC_EVENT                 0x0F
#define  SCCP_ROUTE_FAIL_EVENT          0x10
#define  SCCP_DT1_EVENT                 0x11
#define  SCCP_DT2_EVENT                 0x12
#define  SCCP_AK_EVENT                  0x13
#define  SCCP_IT_EVENT                  0x14
#define  SCCP_ED_EVENT                  0x15
#define  SCCP_EA_EVENT                  0x16
#define  SCCP_ERR_EVENT                 0x17
#define  SCCP_T_CONNEST_TIME_OUT        0x18
#define  SCCP_T_IAR_TIME_OUT            0x19
#define  SCCP_T_IAS_TIME_OUT            0x1A  
#define  SCCP_T_REL_TIME_OUT            0x1B  
#define  SCCP_T_REPREL_TIME_OUT         0x1C  
#define  SCCP_T_INT_TIME_OUT            0x1D  
#define  SCCP_T_GAURD_TIME_OUT          0x1E  
#define  SCCP_T_RESET_TIME_OUT          0x1F
#define  SCCP_T_REASSEMBLY_TIME_OUT     0x20
#define  SCCP_T_FREEZE_TIME_OUT         0x21

#define  SCCP_MAX_EVENTS                0x22

/***************************************************************************
**
**  The timer information structure
**
***************************************************************************/

/* SPR # 7450 Fix Start */
#if defined (DISTRIBUTED_SCCP) && defined (SCCP_INCLUDE_CO_SERVICE)

/* SPR # 8551 Fix Start */
#if 0
/* SPR # 8551 Fix Ends */

#define MAX_SCCP_CO_TIMERS 0x0a

/* SPR # 8551 Fix Start */
#endif
#define MAX_SCCP_CO_TIMERS 0x0e
/* SPR # 8551 Fix Ends */

#else
#define MAX_SCCP_CO_TIMERS 0x09
#endif
/* SPR # 7450 Fix End */

struct timer_info {
  U8bit    timer_status ;
  timer_id_t  timer_id ;
} ;

typedef struct timer_info  timer_info_t ;


/****** The Timer # defines *******************/

#define SCCP_T_CONNEST_TIMER  0x00
#define SCCP_T_IAS_TIMER      0x01
#define SCCP_T_IAR_TIMER      0x02
#define SCCP_T_REL_TIMER      0x03
#define SCCP_T_REPREL_TIMER   0x04
#define SCCP_T_INT_TIMER      0x05
#define SCCP_T_GAURD_TIMER    0x06
#define SCCP_T_RESET_TIMER    0x07
#define SCCP_T_FREEZE_TIMER   0x08
/* SPR # 7450 Fix Start */
#if defined(DISTRIBUTED_SCCP) && (SCCP_INCLUDE_CO_SERVICE)
#define DSCCP_T_DEACTIVATION_TIMER   0x09
#endif
/* SPR # 7450 Fix End */

#define SCCP_CO_TIMER_NOTRUNNING 0x00
#define SCCP_CO_TIMER_RUNNING    0x01

/***************************************************************************
**
**  The node information structure
**
***************************************************************************/

struct sccp_queue {
  struct sccp_queue *p_next;
  U16bit    len ;
  U8bit		api_id ;
  U8bit 	*p_buf ;
} ;

typedef struct sccp_queue  sc_queue_t ;
#define SCCP_QUEUE_HDR_SIZE (sizeof(struct sccp_queue))
#define GET_QUEUE_DATA_PTR(p_node) ((U8bit *)(p_node + 1))

/* Maximum number of ED's that can be queued */
#define MAX_ED_WAITING   40

/***************************************************************************
**
**  The flags for c_status
**
***************************************************************************/

#define  SCCP_TYPE_A_USER  0x01
#define  SCCP_TYPE_B_USER  0x00

#define  SCCP_COUPLING_DONE  0x02
#define  SCCP_COUPLING_MASK  0x02

#define  SCCP_OUTGOING    0x04
#define  SCCP_INCOMING    0x08
#define  SCCP_SUBSTATE_MASK 0x0C

#define  SCCP_ED_SELECTED 0x10
#define	 SCCP_IGNORE_M_BIT 0x20
#define  SCCP_UNACKED_ED  0x40
/* SPR 5929 Fix Starts */
#define  RELEASE_CAUSE_SET 0x80
/* SPR 5929 Fix Starts */


/***************************************************************************
**
**  The Connection Control Block Structure
**
***************************************************************************/

struct sccp_connection_control_block {
  U8bit      c_state ;

  /* 
   * The c_status byte is basically a flag register maintaining the 
   * status of the connection
   *
   *  the 1st bit  : The type of User 
   *   the 2nd bit : Coupled or not
   *  the 3rd &
   *      4th bit  : Substate of the Connection 
   *  the 5th bit  : Expediated data selected
   *  SPR 5929 Fix Starts :
   *  	The 8th bit is used to determine whether the release cause in the return messages    *    is set.
   *  SPR 5929 Fix Ends :
   */
  U8bit      c_status ;

  /** SPR # 2574 Fix Start **/
  Boolean  	 wait_for_cc_flag; /* used to indicate the connection has been
							   ** released by the originator before CC has 
							   ** arrived from the other side 
							   */
  /** SPR # 2574 Fix End **/

  /* Connection Id */
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit    conn_id ;
#else
   U16bit    conn_id ;
#endif

  /* CCB id */
  U32bit    ccb_id ;

  /* logical user id */
  U16bit    l_id;

  /* correlation_id */
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit      corr_id;
#else
  U8bit      corr_id;
#endif

  /* Protocol Class       */
  U8bit      proto_class ;

  U16bit 	seq_seg ;
  U8bit     seg_reass ;
  /* The window size      */
  U8bit      credit ;
  U8bit      w ;

  /* The reference numbers */
  U32bit    slr ;
  U32bit    dlr ;

  /* The Signaling link selection */
  U8bit      sls ;

  /* Called Party Address   */
  pc_t 			opc;
  ss_entry_t	*p_ss;
  sccp_addr_t    cd_addr ;

  /* Calling Party Address   */
  pc_t 			dpc;
  sccp_addr_t    cg_addr ;

  /* The id of the coupled connection control block */
  U32bit      coupled_ccb_id ; 

  /* Timer related info which are currenlty running  */
  timer_info_t  sccp_timer [MAX_SCCP_CO_TIMERS] ;

  /* The send sequence number */
  U8bit      send_seq ;

  /* The send sequence number expected */
  U8bit      send_seq_x ;

  /* Sequence number last acked */
  U8bit		send_seq_ack;

  /* Lower edge of the window */
  U8bit      lw_edge ;

  /* The transmssion queue  */
  sc_queue_t      *p_trans_queue ;
  
  /* Transmission queue for ED */
  sc_queue_t	  *p_ed_trans_queue ;
  U8bit		  num_ed_in_queue ;

  /* The queue where reassembly is done, if  required */
  sc_queue_t      *p_recv_queue ;

  /* SPR 5929 Fix Starts */
  U8bit rel_cause;
  /* SPR 5929 Fix Ends */

/* SPR # 6126 Fix Start */
  /* These indices are used in hash table and free ccb list */
  U32bit next_ccb_id;
  U32bit prev_ccb_id;
/* SPR # 6126 Fix End */

} ;

typedef struct sccp_connection_control_block  sccp_ccb_t ;

/* SPR # 6126 Fix Start */
extern U32bit sccp_free_ccb_list_head;
extern U32bit sccp_hash_table[MAX_SCCP_CO_HASH_TABLE_SIZE];
/* SPR # 6126 Fix End */

/***************************************************************************
**
**  The extern definitions 
**
***************************************************************************/

extern sccp_ccb_t      sccp_ccb [MAX_SCCP_CO_CONNECTIONS] ;
extern U32bit          sccp_co_timer_dur [MAX_SCCP_CO_TIMERS] ;
extern U8bit           sccp_map_co_timer [MAX_SCCP_CO_TIMERS] ;

#ifdef  __INSIGHT__
extern const char      *sccp_co_state_string [SCCP_MAX_CO_STATES] ;
#else
extern S8bit           *sccp_co_state_string [SCCP_MAX_CO_STATES] ;
#endif

#ifdef  __INSIGHT__
extern const char      *sccp_co_event_name [SCCP_MAX_EVENTS] ;
#else
extern S8bit           *sccp_co_event_name [SCCP_MAX_EVENTS] ;
#endif

#ifdef  __INSIGHT__
extern const char      *sccp_co_timer_string [MAX_SCCP_CO_TIMERS] ;
#else
extern S8bit           *sccp_co_timer_string [MAX_SCCP_CO_TIMERS] ;
#endif

struct sccp_co_tim_buf {
  U8bit             timer_name ;
#ifdef SCCP_CONNECTION_ID_CHANGES
  U8bit        		conn_id_l ;
  U8bit        		conn_id_m ;
  U8bit                 conn_id_m1;
  U8bit                 conn_id_m2;
#else
  U8bit                 conn_id_l ;
  U8bit                 conn_id_m ;
#endif
  U8bit				pad;
} ;

typedef struct sccp_co_tim_buf  sccp_co_tim_buf_t ;

/**************************************************************************
**
**  Macros for the CCB
**
**************************************************************************/

#define GET_CCB_FROM_ID(ccb_id) 	(&sccp_ccb[(ccb_id)])
#define GET_ID_FROM_CCB(p_ccb) 		((p_ccb) - &(sccp_ccb[0]))

#define IS_COUPLING_PRESENT(p_ccb)  (((p_ccb->c_status & SCCP_COUPLING_MASK) \
                                      == SCCP_COUPLING_DONE) ? SS7_TRUE : SS7_FALSE)
#define SCCP_GET_COUPLED_CCB(p_ccb) (&(sccp_ccb [p_ccb->coupled_ccb_id]))
#define SCCP_SET_COUPLING_PRESENT(p_ccb) (p_ccb->c_status |= \
                                            SCCP_COUPLING_DONE)
#define SCCP_RESET_COUPLING_PRESENT(p_ccb) (p_ccb->c_status &= \
                                               ~SCCP_COUPLING_DONE)

#define SCCP_SET_UNACK_ED(p_ccb)     (p_ccb->c_status |= SCCP_UNACKED_ED)
#define SCCP_RESET_UNACK_ED(p_ccb)   (p_ccb->c_status &= ~SCCP_UNACKED_ED)
#define SCCP_IS_UNACK_ED(p_ccb)      (((p_ccb->c_status & 0x40) \
									   == SCCP_UNACKED_ED) ? SS7_TRUE : SS7_FALSE)

#define IS_SOURCE_REF_PRESENT(p_info) SS7_TRUE

#define IS_SERVICE_CLASS_MISMATCH(p_info, p_ccb) \
               ((p_info->proto_class == p_ccb->proto_class) ? SS7_FALSE : SS7_TRUE)

#define SET_M_BIT_DT1(p_info) (p_info->seg_reass = 0x01)
#define CLR_M_BIT_DT1(p_info) (p_info->seg_reass &= 0xfe)
#define GET_M_BIT_DT1(p_info) (p_info->seg_reass & 0x01)
#define SET_M_BIT_DT2(p_info) (p_info->seq_seg |= 0x0100)
#define CLR_M_BIT_DT2(p_info) (p_info->seq_seg &= 0xfeff)
#define GET_M_BIT_DT2(p_info) (((U8bit)(p_info->seq_seg >> 8))&0x01)
#define PUT_PS_PR(p_info, p_ccb) p_info->seq_seg |= \
									((p_ccb->send_seq<<1)&0xfe); \
								  p_info->seq_seg |= \
									((p_ccb->send_seq_ack<<9)&0xfe00)

/** SPR 11112 - Fix Start - suyash**/
#define UPDATE_SEQ_SEG_IN_CCB(p_ccb) p_ccb->seq_seg = \
									((p_ccb->send_seq<<1)&0xfe);  \
									p_ccb->seq_seg |= \
									((p_ccb->send_seq_ack<<9)&0xfe00)
/** SPR 11112 - Fix End    **/
#define GET_SEND_SEQ_NUM(p_info)	((U8bit)((p_info->seq_seg & 0x00fe)>>1))
#define GET_RECV_SEQ_NUM(p_info)	((U8bit)((p_info->seq_seg & 0xfe00)>>9))
#define SCCP_GET_M_BIT(p_ccb, p_info) \
			((p_ccb->proto_class == PROTOCOL_CLASS_3)?\
			 GET_M_BIT_DT2(p_info):GET_M_BIT_DT1(p_info))
#define SCCP_IS_IGNORE_M_BIT_SEQ(p_ccb) (p_ccb->c_status & SCCP_IGNORE_M_BIT)
#define SCCP_SET_IGNORE_M_BIT_SEQ(p_ccb) (p_ccb->c_status |= SCCP_IGNORE_M_BIT)
#define SCCP_CLR_IGNORE_M_BIT_SEQ(p_ccb) (p_ccb->c_status &= ~SCCP_IGNORE_M_BIT)
#define INC_SEQ_NUM(x) 	((x+1)%128)
#define SCCP_USER_TYPE_MASK	0x01
#endif /*__SC_CCB_H */
