/***************************************************************************
**  FILE NAME:
**      sc_init.c
**
****************************************************************************
**
**  FUNCTION:
**      Contains functional interface for sccp_init, timers init and
**      related functions
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24Feb2004 Hitesh sharma		Fixed SPR 13263 
**  21Nov2003 knaveen          		  Fixed SPR 13075
**  08Sep2003 Salil Agrawal 		  Fixed SPR 12318
**  13Mar2003 Ashish Sawalkar         Fixed SPR 11500, 11508 
**  24Feb2003 Ashish Sawalkar         Fixed SPR MTPSAP 
**  12Feb2003 Ashish Sawalkar         Fixed Spr 11321
**  20Jan2003 Sachin Bhatia           Fixed SPR 11115
**  17Jan2003 Ashish Sawalkar         Fixed Spr 11113
**  18Nov2002 Ashish Sawalkar         Fixed Spr IMP_SPR
**  09Oct2002 Suyash Tripathi         Fixed Spr 10236
**  24Jul2002 Salil Kumar Agrawal     Fixed SPR # 9342 
**  23May2002 Ashish Sawalkar  		  Fixed SPR 8756  
**  23July2002 Suyash Tripathi        Fixed spr 9302-Warning removal
**  16July2002 Salil Agrawal          fixed spr 9243
**  18Jun2002 Suyash Tripathi  		  SPR # 8985 	
**  26junne2002 saagrawal 			  Added sccp-mtp registration 
**  19March2002 Salil Agrawal         fixed spr 8923 
**  20Feb2002 Ashish Sawalkar  		  Changes for MultiThreading	
**  27Feb 2002 Sachin Bhatia		  Adding DeInit Functionality 
**  13Mar 2002 Prateek Bidwalkar	  Fixed SPR 8584
**  22Jan 2002 Prateek Bidwalkar	  Fixed SPR 7470
**  20Dec 2001 Sachin Bhatia		  Added Japanese Variant
**  23Nov 2001 Pawanish Modi		  Fixed SPR 7170
**  24Oct2001 Prateek Bidwalkar       Fixed SPR # 6750
**  11Sep2001 Prateek Bidwalkar       Fixed SPR # 6126
**  12Oct2000 Ramu Kandula            Modified for broadband - added msg 
**                                    priorities for LUDT and LUDTS
**  26Feb2000 Ramu Kandula            Fixed SPR # 2757
**  24Feb2000 Ramu Kandula            Fixed SPR # 2731
**  17Feb2000 Ramu Kandula            Fixed SPR # 2617
**  06Aug'98 Anil K.				  ANSI Connectionless Added.
**  10May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"
#include "sc_reg.h"

/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */

#ifdef SCCP_MT_SAFE
#include "sccp_mtlib.h"
#endif

U8bit sccp_state = UNINITIALIZED;
U8bit sccp_data_state = UNINITIALIZED;

/* added by salil */
/* # spr 9243 starts */
/* U8bit sccp_redn_sub_state ; */
U8bit sccp_redn_sub_state = STACK_STANDBY;
/* # spr 9243 ends */
/* end */

/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
U8bit sccp_my_instance_id;
U8bit dsccp_class1_buff_timer_running;
extern dsccp_class1_buff_node * list_head;
extern dsccp_class1_buff_node * list_tail;
#endif
/* SPR # 6750 Fix End */

/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
extern dsccp_class1_buff_node * dsccp_cls1_buf_inh_list_head ;
extern dsccp_class1_buff_node * dsccp_cls1_buf_inh_list_tail ;
extern U8bit	dsccp_class1_timer_status;
#endif
/* SPR # 7470 Fix End */
/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
/*U32bit   MAX_SP = 500;*/
U32bit MAX_SS = SCCP_MAX_SS_VALUE ;
U32bit MAX_SP = SCCP_MAX_SP_VALUE ;
U32bit MAX_CSS = SCCP_MAX_CSS_VALUE ;
U32bit MAX_CSP = SCCP_MAX_CSP_VALUE ;
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
#ifdef DISTRIBUTED_SCCP
#ifdef SCCP_BROADBAND
sc_opt_t sc_opt = { STACK_ITU, SCCP_DEFAULT_SEG_SIZE, SS7_BROADBAND_NETWORK,0,4  };
#else
sc_opt_t sc_opt = { STACK_ITU, SCCP_DEFAULT_SEG_SIZE, SS7_NARROWBAND_NETWORK,0,4  };
#endif
#else
#ifdef SCCP_BROADBAND
sc_opt_t sc_opt = { STACK_ITU, SCCP_DEFAULT_SEG_SIZE, SS7_BROADBAND_NETWORK  };
#else
sc_opt_t sc_opt = { STACK_ITU, SCCP_DEFAULT_SEG_SIZE, SS7_NARROWBAND_NETWORK  };
#endif
#endif
sccp_timer_t sc_tim;

sccp_cong_t sccp_cong = { 0, 0 };

/** SPR # 2757 Fix Start **/
sp_entry_t sccp_local_sp ; /* not configured  */
/** SPR # 2757 Fix Start **/



#ifdef SCCP_INCLUDE_CO_SERVICE
timer_id_t deinit_timer_id;
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
sc_tim_range_t sc_tim_range_ansi[SCCP_MAX_TIMER_CONFIG_ID+1] =
#ifdef SCCP_INCLUDE_CO_SERVICE
{
	{ T_A_MIN_TIMER_VAL,
	  T_A_MAX_TIMER_VAL,
	  T_A_DEF_TIMER_VAL },
	{ T_D_MIN_TIMER_VAL,
	  T_D_MAX_TIMER_VAL,
	  T_D_DEF_TIMER_VAL },
	{ T_CON_MIN_TIMER_VAL,
	  T_CON_MAX_TIMER_VAL,
	  T_CON_DEF_TIMER_VAL },
	{ T_STAT_INFO_MIN_START_TIMER_VAL,
	  T_STAT_INFO_MAX_START_TIMER_VAL,
	  T_STAT_INFO_DEF_START_TIMER_VAL },
	{ T_STAT_INFO_MIN_END_TIMER_VAL,
	  T_STAT_INFO_MAX_END_TIMER_VAL,
	  T_STAT_INFO_DEF_END_TIMER_VAL },
	{ T_REASSEMBLY_MIN_TIMER_VAL,
	  T_REASSEMBLY_MAX_TIMER_VAL,
	  T_REASSEMBLY_DEF_TIMER_VAL },
    { SCCP_T_CONNEST_TIMER_MIN_VAL_ANSI,
      SCCP_T_CONNEST_TIMER_MAX_VAL_ANSI,
      SCCP_T_CONNEST_TIMER_DEF_VALUE_ANSI },
    { SCCP_T_IAS_TIMER_MIN_VAL,
      SCCP_T_IAS_TIMER_MAX_VAL,
      SCCP_T_IAS_TIMER_DEF_VALUE },
    { SCCP_T_IAR_TIMER_MIN_VAL,
      SCCP_T_IAR_TIMER_MAX_VAL_ANSI,
      SCCP_T_IAR_TIMER_DEF_VALUE },
    { SCCP_T_REL_TIMER_MIN_VAL,
      SCCP_T_REL_TIMER_MAX_VAL,
      SCCP_T_REL_TIMER_DEF_VALUE },
    { SCCP_T_REPREL_TIMER_MIN_VAL,
      SCCP_T_REPREL_TIMER_MAX_VAL,
      SCCP_T_REPREL_TIMER_DEF_VALUE },
    { SCCP_T_INT_TIMER_MIN_VAL,
      SCCP_T_INT_TIMER_MAX_VAL,
      SCCP_T_INT_TIMER_DEF_VALUE },
    { SCCP_T_GAURD_TIMER_MIN_VAL,
      SCCP_T_GAURD_TIMER_MAX_VAL,
      SCCP_T_GAURD_TIMER_DEF_VALUE },
    { SCCP_T_RESET_TIMER_MIN_VAL_ANSI,
      SCCP_T_RESET_TIMER_MAX_VAL_ANSI,
      SCCP_T_RESET_TIMER_DEF_VALUE_ANSI },
#ifdef DISTRIBUTED_SCCP
    { SCCP_T_FREEZE_TIMER_MIN_VAL,
      SCCP_T_FREEZE_TIMER_MAX_VAL,
      SCCP_T_FREEZE_TIMER_DEF_VALUE },
    { DSCCP_T_CONFIG_TIMER_MIN_VAL,
      DSCCP_T_CONFIG_TIMER_MAX_VAL,
      DSCCP_T_CONFIG_TIMER_DEF_VALUE },
    { T_REASS_QUERY_TIMER_MIN_VAL,
      T_REASS_QUERY_TIMER_MAX_VAL,
      T_REASS_QUERY_TIMER_DEF_VALUE },
    { DSCCP_T_CLASS1_BUFFER_TIMER_MIN_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_MAX_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE },
/* SPR # 7450 Fix Start */
    { DSCCP_T_INST_DEACTIVATION_TIMER_MIN_VAL,
      DSCCP_T_INST_DEACTIVATION_TIMER_MAX_VAL,
      DSCCP_T_INST_DEACTIVATION_TIMER_DEF_VAL },
/* SPR # 7450 Fix End */
/* SPR # 7470 Fix Start */
    { DSCCP_T_CLASS1_BUF_INH_MSG_MIN_VAL,
      DSCCP_T_CLASS1_BUF_INH_MSG_MAX_VAL,
      DSCCP_T_CLASS1_BUF_INH_MSG_DEF_VAL }
/* SPR # 7470 Fix End */
#else
    { SCCP_T_FREEZE_TIMER_MIN_VAL,
      SCCP_T_FREEZE_TIMER_MAX_VAL,
      SCCP_T_FREEZE_TIMER_DEF_VALUE }
#endif
};
#else
{
	{ T_A_MIN_TIMER_VAL,
	  T_A_MAX_TIMER_VAL,
	  T_A_DEF_TIMER_VAL },
	{ T_D_MIN_TIMER_VAL,
	  T_D_MAX_TIMER_VAL,
	  T_D_DEF_TIMER_VAL },
	{ T_CON_MIN_TIMER_VAL,
	  T_CON_MAX_TIMER_VAL,
	  T_CON_DEF_TIMER_VAL },
	{ T_STAT_INFO_MIN_START_TIMER_VAL,
	  T_STAT_INFO_MAX_START_TIMER_VAL,
	  T_STAT_INFO_DEF_START_TIMER_VAL },
	{ T_STAT_INFO_MIN_END_TIMER_VAL,
	  T_STAT_INFO_MAX_END_TIMER_VAL,
	  T_STAT_INFO_DEF_END_TIMER_VAL },
#ifdef DISTRIBUTED_SCCP
	{ T_REASSEMBLY_MIN_TIMER_VAL,
	  T_REASSEMBLY_MAX_TIMER_VAL,
	  T_REASSEMBLY_DEF_TIMER_VAL },
    { DSCCP_T_CONFIG_TIMER_MIN_VAL,
      DSCCP_T_CONFIG_TIMER_MAX_VAL,
      DSCCP_T_CONFIG_TIMER_DEF_VALUE },
    { T_REASS_QUERY_TIMER_MIN_VAL,
      T_REASS_QUERY_TIMER_MAX_VAL,
      T_REASS_QUERY_TIMER_DEF_VALUE },
    { DSCCP_T_CLASS1_BUFFER_TIMER_MIN_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_MAX_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE }
#else
	{ T_REASSEMBLY_MIN_TIMER_VAL,
	  T_REASSEMBLY_MAX_TIMER_VAL,
	  T_REASSEMBLY_DEF_TIMER_VAL }
#endif
};

#endif 
#endif  /* #ifdefined ANSI .....   */

sc_tim_range_t sc_tim_range[SCCP_MAX_TIMER_CONFIG_ID+1] =
#ifdef SCCP_INCLUDE_CO_SERVICE
{
        { T_A_MIN_TIMER_VAL,
          T_A_MAX_TIMER_VAL,
          T_A_DEF_TIMER_VAL },
        { T_D_MIN_TIMER_VAL,
          T_D_MAX_TIMER_VAL,
          T_D_DEF_TIMER_VAL },
        { T_CON_MIN_TIMER_VAL,
          T_CON_MAX_TIMER_VAL,
          T_CON_DEF_TIMER_VAL },
        { T_STAT_INFO_MIN_START_TIMER_VAL,
          T_STAT_INFO_MAX_START_TIMER_VAL,
          T_STAT_INFO_DEF_START_TIMER_VAL },
        { T_STAT_INFO_MIN_END_TIMER_VAL,
          T_STAT_INFO_MAX_END_TIMER_VAL,
          T_STAT_INFO_DEF_END_TIMER_VAL },
        { T_REASSEMBLY_MIN_TIMER_VAL,
          T_REASSEMBLY_MAX_TIMER_VAL,
          T_REASSEMBLY_DEF_TIMER_VAL },
    { SCCP_T_CONNEST_TIMER_MIN_VAL,
      SCCP_T_CONNEST_TIMER_MAX_VAL,
      SCCP_T_CONNEST_TIMER_DEF_VALUE },
    { SCCP_T_IAS_TIMER_MIN_VAL,
      SCCP_T_IAS_TIMER_MAX_VAL,
      SCCP_T_IAS_TIMER_DEF_VALUE },
    { SCCP_T_IAR_TIMER_MIN_VAL,
      SCCP_T_IAR_TIMER_MAX_VAL,
      SCCP_T_IAR_TIMER_DEF_VALUE },
    { SCCP_T_REL_TIMER_MIN_VAL,
      SCCP_T_REL_TIMER_MAX_VAL,
      SCCP_T_REL_TIMER_DEF_VALUE },
    { SCCP_T_REPREL_TIMER_MIN_VAL,
      SCCP_T_REPREL_TIMER_MAX_VAL,
      SCCP_T_REPREL_TIMER_DEF_VALUE },
    { SCCP_T_INT_TIMER_MIN_VAL,
      SCCP_T_INT_TIMER_MAX_VAL,
      SCCP_T_INT_TIMER_DEF_VALUE },
    { SCCP_T_GAURD_TIMER_MIN_VAL,
      SCCP_T_GAURD_TIMER_MAX_VAL,
      SCCP_T_GAURD_TIMER_DEF_VALUE },
    { SCCP_T_RESET_TIMER_MIN_VAL,
      SCCP_T_RESET_TIMER_MAX_VAL,
SCCP_T_RESET_TIMER_DEF_VALUE },
#ifdef DISTRIBUTED_SCCP
    { SCCP_T_FREEZE_TIMER_MIN_VAL,
      SCCP_T_FREEZE_TIMER_MAX_VAL,
      SCCP_T_FREEZE_TIMER_DEF_VALUE },
    { DSCCP_T_CONFIG_TIMER_MIN_VAL,
      DSCCP_T_CONFIG_TIMER_MAX_VAL,
      DSCCP_T_CONFIG_TIMER_DEF_VALUE },
    { T_REASS_QUERY_TIMER_MIN_VAL,
      T_REASS_QUERY_TIMER_MAX_VAL,
      T_REASS_QUERY_TIMER_DEF_VALUE },
    { DSCCP_T_CLASS1_BUFFER_TIMER_MIN_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_MAX_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE },
/* SPR # 7450 Fix Start */
    { DSCCP_T_INST_DEACTIVATION_TIMER_MIN_VAL,
      DSCCP_T_INST_DEACTIVATION_TIMER_MAX_VAL,
      DSCCP_T_INST_DEACTIVATION_TIMER_DEF_VAL },
/* SPR # 7450 Fix End */
/* SPR # 7470 Fix Start */
    { DSCCP_T_CLASS1_BUF_INH_MSG_MIN_VAL,
      DSCCP_T_CLASS1_BUF_INH_MSG_MAX_VAL,
      DSCCP_T_CLASS1_BUF_INH_MSG_DEF_VAL }
/* SPR # 7470 Fix End */
#else
    { SCCP_T_FREEZE_TIMER_MIN_VAL,
      SCCP_T_FREEZE_TIMER_MAX_VAL,
      SCCP_T_FREEZE_TIMER_DEF_VALUE }
#endif
};
#else
{
        { T_A_MIN_TIMER_VAL,
          T_A_MAX_TIMER_VAL,
          T_A_DEF_TIMER_VAL },
        { T_D_MIN_TIMER_VAL,
          T_D_MAX_TIMER_VAL,
          T_D_DEF_TIMER_VAL },
        { T_CON_MIN_TIMER_VAL,
          T_CON_MAX_TIMER_VAL,
          T_CON_DEF_TIMER_VAL },
        { T_STAT_INFO_MIN_START_TIMER_VAL,
          T_STAT_INFO_MAX_START_TIMER_VAL,
          T_STAT_INFO_DEF_START_TIMER_VAL },
        { T_STAT_INFO_MIN_END_TIMER_VAL,
          T_STAT_INFO_MAX_END_TIMER_VAL,
T_STAT_INFO_DEF_END_TIMER_VAL },
#ifdef DISTRIBUTED_SCCP
        { T_REASSEMBLY_MIN_TIMER_VAL,
          T_REASSEMBLY_MAX_TIMER_VAL,
          T_REASSEMBLY_DEF_TIMER_VAL },
    { DSCCP_T_CONFIG_TIMER_MIN_VAL,
      DSCCP_T_CONFIG_TIMER_MAX_VAL,
      DSCCP_T_CONFIG_TIMER_DEF_VALUE },
    { T_REASS_QUERY_TIMER_MIN_VAL,
      T_REASS_QUERY_TIMER_MAX_VAL,
      T_REASS_QUERY_TIMER_DEF_VALUE },
    { DSCCP_T_CLASS1_BUFFER_TIMER_MIN_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_MAX_VAL,
      DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE }
#else
        { T_REASSEMBLY_MIN_TIMER_VAL,
          T_REASSEMBLY_MAX_TIMER_VAL,
          T_REASSEMBLY_DEF_TIMER_VAL }
#endif
};

#endif
   
#if defined(SCCP_ANSI) || defined(SCCP_BCGR) 
/** SPR # 2731 Fix Start **/
/** Defined min and max priorities **/
#ifdef SCCP_BROADBAND
sccp_message_priority_t sccp_message_priority [LUDTS_MSG_TYPE] =
#else
sccp_message_priority_t sccp_message_priority [XUDTS_MSG_TYPE] =
#endif

#if defined (SCCP_ANSI) || defined(SCCP_BCGR) 
{ 
    {CR_MSG_TYPE, 0, 1},
    {CC_MSG_TYPE, 1, 1},
    {CREF_MSG_TYPE, 1, 1},
    {RLSD_MSG_TYPE, 2, 2},
    {RLC_MSG_TYPE, 2, 2},
    {DT1_MSG_TYPE, 0, 1},
    {DT2_MSG_TYPE, 0, 1},
    {AK_MSG_TYPE, 0, 1},
    {UDT_MSG_TYPE, 0, 2},
    {UDTS_MSG_TYPE, 0, 2},
    {ED_MSG_TYPE, 1, 1},
    {EA_MSG_TYPE, 1, 1},
    {RSR_MSG_TYPE, 1, 1},
    {RSC_MSG_TYPE, 1, 1},
    {ERR_MSG_TYPE, 1, 1},
    {IT_MSG_TYPE, 1, 1},
    {XUDT_MSG_TYPE, 0, 2},
    {XUDTS_MSG_TYPE, 0, 2},
#ifdef SCCP_BROADBAND
    {LUDT_MSG_TYPE, 0, 2},
    {LUDTS_MSG_TYPE, 0, 2}
#endif
};

#endif 

/** SPR # 2617 Fix Start **/
sccp_message_priority_t sccp_scmg_message_priority [0x10] =
{
	{SCMG_SSA_MSG, 3, 3},
	{SCMG_SSP_MSG, 3, 3},
	{SCMG_SST_MSG, 2, 2}
};
/** SPR # 2617 Fix End **/
/** SPR # 2731 Fix End **/
#endif


#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)

/** Defined default and max priorities **/

/* SPR# IMP_SPR Fix : Modified importance values according to Table 2/Q.714 */

#ifdef SCCP_BROADBAND
sccp_message_priority_t sccp_message_priority_itu [LUDTS_MSG_TYPE] =
#else
sccp_message_priority_t sccp_message_priority_itu [XUDTS_MSG_TYPE] =
#endif
{
    {CR_MSG_TYPE, 2, 4},
    {CC_MSG_TYPE, 3, 4},
    {CREF_MSG_TYPE, 2, 4},
    {RLSD_MSG_TYPE, 6, 6},
    {RLC_MSG_TYPE, 4, 4}, 
    {DT1_MSG_TYPE, 4, 6},
    {DT2_MSG_TYPE, 4, 6},
    {AK_MSG_TYPE, 6, 6}, 
    {UDT_MSG_TYPE, 4, 6},
    {UDTS_MSG_TYPE, 3, 3}, 
    {ED_MSG_TYPE, 7, 7},
    {EA_MSG_TYPE, 7, 7},
    {RSR_MSG_TYPE, 6, 6}, 
    {RSC_MSG_TYPE, 6, 6}, 
    {ERR_MSG_TYPE, 7, 7},
    {IT_MSG_TYPE, 6, 6}, 
    {XUDT_MSG_TYPE, 4, 6},
    {XUDTS_MSG_TYPE, 3, 3}, 
#ifdef SCCP_BROADBAND
    {LUDT_MSG_TYPE, 4, 6},
    {LUDTS_MSG_TYPE, 3, 3} 
#endif
}; 
#endif


#ifdef SCCP_INCLUDE_CO_SERVICE
/* SPR 9302 - Fix Start */
/* Already declared in sc_ccb.h */
#if 0
extern sccp_ccb_t    sccp_ccb [MAX_SCCP_CO_CONNECTIONS] ;

/* SPR # 6126 Fix Start */
extern U32bit        sccp_hash_table[MAX_SCCP_CO_HASH_TABLE_SIZE];
extern U32bit        sccp_free_list_ccb_head;
/* SPR # 6126 Fix End */
#endif
/* SPR 9302 - Fix Start */

/* SPR 8985 - Fix Start */
 /*void          sccp_init_co_service */
 /* can't be static; has to be used again */
/*static void          sccp_init_co_service */  
 void          sccp_init_co_service 
/* SPR 8985 - Fix End  */
                     _ARGS_((U8bit   standard)) ;
#endif

#ifdef DISTRIBUTED_SCCP
#define SCCP_UMR_INIT_SIZE 	9
#define SCCP_DMR_INIT_SIZE	9
#define SCCP_UMR_DEINIT_SIZE	7
#define SCCP_DMR_DEINIT_SIZE	7
static return_t sccp_update_umr_dmr_on_deinit _ARGS_((error_t *)) ;
static return_t sccp_update_umr_dmr_on_init _ARGS_((error_t *)) ;
#endif



/*****************************************************************************
**      FUNCTION :
**         function called from encapsulating shell 
******************************************************************************
**
**      DESCRIPTION :
** 			This is the one time init function which should be 
**			called at the beginning before any msg goes thru stack
**      NOTE :
**
*****************************************************************************/

return_t
sccp_init
#ifdef ANSI_PROTO
	(sc_init_opt_t * p_sc_init_opt, error_t * p_ecode)
#else
	(p_sc_init_opt, p_ecode)
	 sc_init_opt_t 	*p_sc_init_opt;
	 error_t 	*p_ecode;
#endif
{
	/* Fix for SPR No: 13263 start */
	/* extern 	sccp_db_t 		sccp_db;*/
	/* Fix for SPR No: 13263 stop */
	return_t ret_val = SS7_SUCCESS;
    sccp_gtt_sm_info_t      gtt_sm_info;

/* SPR 8985 - Fix Start */
#if defined(SCCP_ITU) && defined (SCCP_ETSI) && defined (SCCP_ANSI) && defined (SCCP_BCGR) && defined (SCCP_JAPANESE) && defined (SCCP_CHINESE)
#else
/* SPR 8985 - Fix End  */
	S8bit * p_err_str1 =(S8bit *) "standard not included at compile time";
/* start added during CC compilation */
/* string initialization  (S8bit *) "standard not included at compil
e time";*/

/* end added during CC compilation */ 
/* SPR 8985 - Fix Start */
#endif
/* SPR 8985 - Fix End  */

#ifdef SCCP_MT_SAFE
	sccp_mtlib_init_opt_t mt_init_opt;
#endif

#ifdef DISTRIBUTED_SCCP
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
	U8bit i;
#endif

	if (STACK_INITIALIZED == sccp_state)
	{
		SC_IN_TRC (("SCCP::INIT:Already initialized. cannot init again\n"));
		*p_ecode = ESCCP_ALREADY_INIT;
		return SS7_FAILURE;
	}
	else if (BLOCKED == sccp_state)
	{
		SC_IN_TRC (("SCCP::INIT:Stack in Blocked State Ignoring Message.\n"));
		*p_ecode = ESS7_INVALID_STATE;
		return SS7_FAILURE;
	}	

	/** SPR 11500 Start Fix */

	if (SS7_FAILURE == sccp_init_flush_db(p_ecode))
		return SS7_FAILURE;

	/** SPR 11500 End Fix */
/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if (p_sc_init_opt->max_sp != 0 )
		MAX_SP = p_sc_init_opt->max_sp;

    if(p_sc_init_opt->max_ss != 0)
        MAX_SS = p_sc_init_opt->max_ss ;

    if(p_sc_init_opt->max_css != 0)
        MAX_CSS = p_sc_init_opt->max_css ;

    if(p_sc_init_opt->max_csp != 0)
        MAX_CSP = p_sc_init_opt->max_csp ;

#if 0
    /* memory Allocation at run time. */
    sccp_db.sp = (sp_entry_t*)(void*)sccp_malloc(MAX_SP * sizeof(sp_entry_t));
    if( sccp_db.sp == SS7_NULL )
    {
        SC_A_TRC (("SCCP::INIT: malloc failure\n"));
        return SS7_FAILURE;
    }
    sccp_db.conc_ss_sp_list = (U8bit*)sccp_malloc((SIZEOF_SP_ID_T * MAX_SP + SIZEOF_SS_ID_T * MAX_CSS) * sizeof(U8bit));
    if( sccp_db.conc_ss_sp_list == SS7_NULL )
    {
        SC_A_TRC (("SCCP::INIT: malloc failure\n"));
        return SS7_FAILURE;
    }
/* Stop Spr 13075 Fix */
#endif
/* Stop Spr 13263 Fix */

	switch (p_sc_init_opt->standard)
	{
		case STACK_ITU:
#ifndef SCCP_ITU
			SC_IN_TRC (("SCCP::INIT: ITU %s\n", p_err_str1));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
#else
			SC_IN_TRC (("SCCP::INIT: ITU initialized\n"));
			break;
#endif

		case STACK_ETSI:
#ifndef SCCP_ETSI
			SC_IN_TRC (("SCCP::INIT: ETSI %s\n", p_err_str1));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
#else
			SC_IN_TRC (("SCCP::INIT: ETSI initialized\n"));
			break;
#endif

		case STACK_ANSI:
#ifndef SCCP_ANSI
			SC_IN_TRC (("SCCP::INIT: ANSI %s\n", p_err_str1));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
#else
			SC_IN_TRC (("SCCP::INIT: ANSI initialized\n"));
			break;
#endif

		case STACK_BCGR:
#ifndef SCCP_BCGR
			SC_IN_TRC (("SCCP::INIT: BCGR %s\n", p_err_str1));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
#else
			SC_IN_TRC (("SCCP::INIT: BCGR initialized\n"));
			break;
#endif
			/* Changed by Sachin for JAPANESE Variant */
		case STACK_JAPANESE:
#ifndef SCCP_JAPANESE
			SC_IN_TRC (("SCCP::INIT: JAPANESE %s\n", p_err_str1));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
#else
			SC_IN_TRC (("SCCP::INIT: JAPANESE initialized\n"));
			break;
#endif

/* SPR# 8756 : Start Fix */
		case STACK_CHINESE:
#ifndef SCCP_CHINESE
			SC_IN_TRC (("SCCP::INIT: CHINESE %s\n", p_err_str1));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
#else
			SC_IN_TRC (("SCCP::INIT: CHINESE initialized\n"));
			break;
#endif
/* SPR# 8756 : End Fix */

		default:
			SC_IN_TRC (("SCCP::INIT: %d standard unknown",
			            p_sc_init_opt->standard));
			*p_ecode = ESS7_INVALID_STANDARD;
			return SS7_FAILURE;
	}

	/** SPR # 2757 Fix Start **/
	sccp_local_sp.conf_status = SC_NOT_CONFIGURED ; /* not configured  */
	/** SPR # 2757 Fix Start **/
	sccp_state = STACK_INITIALIZED;
	sc_opt.standard = p_sc_init_opt->standard;
#ifdef DISTRIBUTED_SCCP


	dsccp_class1_buff_timer_running = SS7_FALSE;

	/** SPR 11508 Start Fix **/
	if (p_sc_init_opt->dsccp_local_instance_id != DSCCP_INVALID_INSTANCE_ID)
		sc_opt.dsccp_local_instance_id = p_sc_init_opt->dsccp_local_instance_id;
	/** SPR 11508 End Fix **/

	list_head = SS7_NULL;
	list_tail = SS7_NULL;
/* SPR # 7470 Fix Start */
	dsccp_cls1_buf_inh_list_head = SS7_NULL;
	dsccp_cls1_buf_inh_list_tail = SS7_NULL;
	dsccp_class1_timer_status = SS7_FALSE;
/* SPR # 7470 Fix End */

	/** SPR 11508 Start Fix **/
	if (p_sc_init_opt->num_of_bits_instance_id > 0)
		sc_opt.num_of_bits_instance_id = p_sc_init_opt->num_of_bits_instance_id;
	/** SPR 11508 End Fix **/

/* SPR 10236 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	for(i=0; i < DSCCP_MAX_INSTANCES; i++)
		dsccp_instance_status_tbl[i] = DSCCP_INSTANCE_STATUS_DEAD;
		
	/* Making only self state UNCONFIG */
	dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id]=DSCCP_INSTANCE_STATUS_UNCONFIG ;	
#else
	for(i=0; i < DSCCP_MAX_INSTANCES; i++)
		dsccp_instance_status_tbl[i] = DSCCP_INSTANCE_STATUS_UNCONFIG;
#endif
/* SPR 10236 - Fix End   */


	/* Update DMR and UMR --Sachin Bhatia */
	if (SS7_FAILURE == sccp_update_umr_dmr_on_init(p_ecode))
		SC_A_TRC (("SCCP::INIT: Unable to Update UMR DMR on Init.\n"));


/* SPR # 8584 Fix Start */
     /* spr # 8923 starts */
#ifdef SCCP_REDN_ENABLED
    {
        extern U8bit sccp_redn_sub_state;
        if (sccp_redn_sub_state == ACTIVE)
        {
            dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_UNCONFIG | 0x40, SCCP_MODULE_ID);
        }
        else
        {
            if (sccp_redn_sub_state == STACK_STANDBY)
            {
                dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_UNCONFIG | 0x80, SCCP_MODULE_ID);
            }
            else 
                dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_UNCONFIG, SCCP_MODULE_ID);
        }

    }
#else
	dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_UNCONFIG, SCCP_MODULE_ID);
#endif
    /* spr # 8923 ends */
    /* SPR # 8584 Fix End */

#endif

	if (UNINITIALIZED == sccp_data_state)
	{
		ret_val = sccp_default_init_data(p_ecode);
	}

	SC_IN_TRC (("SCCP::INIT:init %s\n", RESULT_STR(ret_val)));

#ifdef SCCP_INCLUDE_CO_SERVICE
	SC_IN_TRC (("SCCP::BEFORE CALLING sccp_init_co_service"));
    sccp_init_co_service (p_sc_init_opt->standard) ;
	SC_IN_TRC (("SCCP::AFTER CALLING sccp_init_co_service"));
#endif

	/* SPR 11115 fix : Moved add mtpsap code to after sccp_init_complete_indication call */

   SCCP_SEND_INIT_ENTRY_UPDATE(p_sc_init_opt->standard);

#ifdef SCCP_MT_SAFE
	sccp_mtlib_init (&mt_init_opt);
	SC_IN_TRC (("SCCP::INIT: MTLIB Initialized\n"));
#endif

    /* SPR 11115 Fix Start -Sabhatia */
    /* We call a porting function called sccp_init_complete_indication
       , so that user can do whatever other initializations (GTT etc)
       through this function */
    /* We do not have return value here as stack is not expected 
       to take any action on Failure */

    sccp_init_complete_indication(p_sc_init_opt);

	/* In the GTT database mtpsap must be configured before any SP
   	provisioning can be done. So here we are adding default mtpsap = 0
   	to the gtt database so that when provisioning SP etc later on in GTT
   	database, the provisioning shall not fail because no mtpsap is configured in
   	gtt database */

   	/* Zero out the structure */
   	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
   	gtt_sm_info.info_id = SCCP_SM_ADD_MTPSAP;
   	gtt_sm_info.sccp_gtt_add_mtpsap_info = 
         (sccp_gtt_add_mtpsap_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_mtpsap_info_t));
   	if (SS7_NULL == gtt_sm_info.sccp_gtt_add_mtpsap_info) /* Memory Allocation Failure */
                {
                        *(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
                        return(SS7_FAILURE);
                }
   	gtt_sm_info.sccp_gtt_add_mtpsap_info->mtpsap = 0;
   	gtt_sm_info.sccp_gtt_add_mtpsap_info->p_ecode = p_ecode;

   	/* Now call the porting func */
   	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

    /* SPR 11115 Fix End   -Sabhatia */

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         De-initializes the Stack 
******************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
*****************************************************************************/
return_t
sccp_deinit
#ifdef ANSI_PROTO
    (error_t * p_ecode)
#else
    (p_ecode)
     error_t * p_ecode;
#endif
{
  	return_t ret_val = SS7_SUCCESS;
    int count, buff_len, nelem;
    sc_reg_entry_t *p_sccp_reg;
    U8bit * p_dereg_api, * p_buffer, * p_dereg_ind, *p_elem;
    /* Already declared globally */
    /*extern U8bit sccp_state, sccp_data_state;*/
    /* sccp_gtt_sm_info_t      gtt_sm_info; */
#ifdef SCCP_INCLUDE_CO_SERVICE
	error_t * p_errcode = SS7_NULL;
	U8bit * deinit_timer_buffer;
#endif

#ifdef SCCP_REDN_ENABLED
	/* Reject the message if stack is in Standby mode */
	if (sccp_redn_sub_state == STACK_STANDBY) 
	{
		SC_A_TRC (("SCCP::INIT: Trying to DEINIT in STB MODE.\n"));
		return (SS7_FAILURE);
	}
#endif
	
	if(sccp_state == UNINITIALIZED || sccp_state == BLOCKED)
	{
		SC_A_TRC (("SCCP::INIT: Trying to DE-INIT in UNINITIALIZED State.\n"));
                *p_ecode = ESCCP_NOT_IN_INITIALIZED_STATE;
		ret_val = SS7_FAILURE;
	}
	else
	{
		/* Mark the stack as deinitalizing */
		sccp_state = DEINITIALIZING;
		SC_A_TRC (("SCCP::INIT: Stack De-Initializing.\n"));

#ifdef SCCP_REDN_ENABLED
		/* Update on STB Side */
		SCCP_SEND_DEINIT_ENTRY_UPDATE(sccp_state);
#endif

#ifdef DISTRIBUTED_SCCP
		/* Update the DMR and UMR on Deinit */
		if (SS7_FAILURE == sccp_update_umr_dmr_on_deinit(p_ecode))
			SC_A_TRC (("SCCP::INIT: Unable to Update UMR DMR on Deinit.\n"));
#endif

		
			/* Deregister all registered users */
			p_dereg_api = (U8bit *)sccp_malloc(11);

/* SPR 12318 starts */
			if(p_dereg_api == SS7_NULL)
      		{
            	return SS7_FAILURE;
      		}
/* SPR 12318 starts */

			p_buffer = p_dereg_api;

			/* Form the API buffer */
            /* starts spr # 9342 */
			*p_dereg_api++ = SCCP_DEREGISTER_USER;     /* API Id */
			/* *p_dereg_api = SCCP_DEREGISTER_USER; */    /* API Id     */ 
            /* end spr # 9342 */
			*p_dereg_api++ = 0x01;                  /* Version ID */
			*p_dereg_api++ = 0x02;                  /* Num Elements */

#if (defined(SCCP_ITU) || defined(SCCP_JAPANESE))
			if((COMPARE_ITU) || (COMPARE_JAPANESE))
			{
					*p_dereg_api++ = 0x0a; /* LSB Length */
					*p_dereg_api++ = 0x00; /* MSB Length */
					*p_dereg_api++ = 0x00; /* Dummy Point Code LSB */
					*p_dereg_api++ = 0x00; /* Dummy Point Code MSB */
					*p_dereg_api++ = 0x00; /* Dummy SSN */
					*p_dereg_api++ = 0x00; /* Dummy Log User ID LSB  */
					*p_dereg_api++ = 0x00; /* Dummy Log User ID MSB */
			}
#endif

#if defined(SCCP_CHINESE) || defined(SCCP_ANSI)
			if(COMPARE_CHINESE || COMPARE_ANSI)
			{
					*p_dereg_api++ = 0x0b; /* LSB Length */
					*p_dereg_api++ = 0x00; /* MSB Length */
					*p_dereg_api++ = 0x00; /* Dummy Point Code LSB */
					*p_dereg_api++ = 0x00; /* Dummy Point Code MSB */
					*p_dereg_api++ = 0x00; /* Dummy Point Code MSB */
					*p_dereg_api++ = 0x00; /* Dummy SSN */
					*p_dereg_api++ = 0x00; /* Dummy Log User ID LSB  */
					*p_dereg_api++ = 0x00; /* Dummy Log User ID MSB */
			}
#endif



			SC_A_TRC (("SCCP::INIT: Creating Deregister for all registered Users, and sending to Self.\n"));
			for (count = 0; count < MAX_LOCAL_USERS; count++)
			{
					p_sccp_reg = &sccp_reg_table [count] ;
					if(p_sccp_reg->registered == SS7_TRUE)
					{
							/* We have such a user Registered with us */
							/* Create a deregister API and send it to self */

#if (defined(SCCP_ITU) || defined(SCCP_JAPANESE) || defined(SCCP_ETSI))
							if((COMPARE_ITU) || (COMPARE_JAPANESE) || (COMPARE_ETSI))
							{
									p_buffer[SS7_API_HEADER_LEN] = (U8bit)(p_sccp_reg->p_sp->pc);
									p_buffer[SS7_API_HEADER_LEN + 1] = (U8bit)((p_sccp_reg->p_sp->pc)>>8);
									p_buffer[SS7_API_HEADER_LEN + 2] = (U8bit)(p_sccp_reg->ssn);
									p_buffer[SS7_API_HEADER_LEN + 3] = (U8bit)(p_sccp_reg->uid);
									p_buffer[SS7_API_HEADER_LEN + 4] = (U8bit)((p_sccp_reg->uid)>>8);
							}
#endif
#if defined(SCCP_CHINESE) || defined(SCCP_ANSI) || defined(SCCP_BCGR)
							if(COMPARE_CHINESE || COMPARE_ANSI || COMPARE_BCGR)
							{
									p_buffer[SS7_API_HEADER_LEN] = (U8bit)(p_sccp_reg->p_sp->pc); 
									p_buffer[SS7_API_HEADER_LEN + 1] = (U8bit)((p_sccp_reg->p_sp->pc)>>8);
									p_buffer[SS7_API_HEADER_LEN + 2] = (U8bit)((p_sccp_reg->p_sp->pc)>>16);
									p_buffer[SS7_API_HEADER_LEN + 3] = (U8bit)(p_sccp_reg->ssn);
									p_buffer[SS7_API_HEADER_LEN + 4] = (U8bit)(p_sccp_reg->uid);
									p_buffer[SS7_API_HEADER_LEN + 5] = (U8bit)((p_sccp_reg->uid)>>8);
							}
#endif
							sccp_deregister_user(p_buffer);

							/* Send Dereg Indication to this User --Sachin*/

							buff_len = SCCP_DEREG_INDICATION_SIZE;
							nelem = NUM_ELEMS_SCCP_DEREG_INDICATION;

							if (SS7_NULL == (p_dereg_ind = sccp_malloc(buff_len)))
							{
								SC_A_TRC (("SCCP::INIT: Cannot allocate memory\n"));
								/* return SS7_FAILURE; */
							}
							else
							{
								sccp_fill_api_header (p_dereg_ind, SS7_EXTENDED_API,nelem,buff_len);
								p_elem = p_dereg_ind + API_HEADER_LEN;

								PUT_2_BYTE_LE (p_elem, SCCP_DEREGISTER_INDICATION);
								p_elem+=2;

								*p_elem++ = STACK_DEINITIALIZING;

					/* SPR 10859 - Fix Start */
					/* Commented so as to prevent SCCP from sending **
					** Invalid API Id to User. */
#if 0
								if (SS7_FAILURE == send_from_sccp(p_dereg_ind,GET_API_LEN(p_dereg_ind),SCCP_MODULE_ID,p_sccp_reg->uid,p_ecode))
								{
#endif
									sccp_free(p_dereg_ind);
#if 0
									return SS7_FAILURE;
								}
#endif
					/* SPR 10859 - Fix End   */
							}


					}
			}


			SC_A_TRC (("SCCP::INIT: DeRegistration Process Over.\n"));
			/* Deregistration Over */


			/* Now Change Stack State */
#ifdef SCCP_INCLUDE_CO_SERVICE
			sccp_state = BLOCKED;
			SC_A_TRC (("SCCP::INIT: Stack Blocked.\n"));

			/* starting SCCP_DEINIT_TIMER */
			/* This is to make sure connections are fully released before next init */
			deinit_timer_buffer = (U8bit *)sccp_malloc(sizeof(U8bit));
			*(deinit_timer_buffer) = T_DEINIT_TIMER_ID;
			
			ret_val=ss7_start_timer(SCCP_T_DEINIT_TIMER_DEF_VAL, deinit_timer_buffer, 1, SCCP_MODULE_ID,  &deinit_timer_id, p_errcode );
		 if (ret_val != SS7_SUCCESS)
         return ret_val;

			SC_A_TRC (("SCCP::INIT: Wait for SCCP_DEINIT_TIMER to Expire.\n"));
			SCCP_SEND_DEINIT_ENTRY_UPDATE(sccp_state);
#else
			sccp_state = UNINITIALIZED;
			SC_A_TRC (("SCCP::INIT: Stack De-Initialized.\n"));
			SCCP_SEND_DEINIT_ENTRY_UPDATE(sccp_state);
#endif
	}
	sccp_data_state = UNINITIALIZED;

/* Fix for SPR No: 13263 start */
sccp_free((U8bit *)sccp_db.sp);
sccp_free((U8bit *)sccp_db.ss);
sccp_free((U8bit *)sccp_db.conc_ss_sp_list);

sccp_db.sp = 0;
sccp_db.ss = 0;
sccp_db.conc_ss_sp_list = 0;

/* Call the sccp_deinit_complete_indication porting
*  function to deinit GTT */
sccp_deinit_complete_indication();

/* Fix for SPR No : 13263 end */

#if 0 /* SPR MTPSAP fix */
**
** /* In the GTT database mtpsap = 0 was configured
**    So here we are deleting default mtpsap = 0
**    from the gtt database. */
**
**    /* Zero out the structure */
**    ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
**    gtt_sm_info.info_id = SCCP_SM_DEL_MTPSAP;
**    gtt_sm_info.sccp_gtt_del_mtpsap_info =
**          (sccp_gtt_del_mtpsap_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_del_mtpsap_info_t));
**    if (SS7_NULL == gtt_sm_info.sccp_gtt_del_mtpsap_info) /* Memory Allocation Failure */
**                 {
**                         *(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
**                         return(SS7_FAILURE);
**                 }
**    gtt_sm_info.sccp_gtt_del_mtpsap_info->mtpsap = 0;
**    gtt_sm_info.sccp_gtt_del_mtpsap_info->p_ecode = p_ecode;
**    /* Now call the porting func */
**    ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
**     SC_IN_TRC (("SCCP::INIT:DEL MTPSAP 0,  %s\n",
**                                  RESULT_STR(ret_val)));
**
**
#endif

	/* SPR 9302 - Fix Start */
	p_ecode = 0;
	/* SPR 9302 - Fix End   */

    return ret_val;
}

#ifdef  DISTRIBUTED_SCCP
/*****************************************************************************
 **      FUNCTION :
 **		sccp_update_umr_dmr_on_deinit
 ******************************************************************************
 **
 **      DESCRIPTION :
 **         Handles Deinit Updation to UMR and DMR  
 **        
 **
 **      NOTE :
 **
 *****************************************************************************/
return_t
sccp_update_umr_dmr_on_deinit
#ifdef ANSI_PROTO
    (error_t * p_ecode)
#else
	    (p_ecode)
	     error_t * p_ecode;
#endif
{
	return_t ret_val=SS7_SUCCESS;
	U8bit *p_buf_dmr, *p_buf_umr, * p_elem;
	U32bit nelem, buff_len;

	/* Send Dereg Indication to this User --Sachin*/

	buff_len = SCCP_UMR_DEINIT_SIZE;
	nelem = 1 ; /* Extended API Id only  */

	if (SS7_NULL == (p_buf_umr = sccp_malloc(buff_len)))
	{
		SC_A_TRC (("SCCP::INIT: Cannot allocate memory\n"));
		return(SS7_FAILURE);
	}
	else
	{
		sccp_fill_api_header (p_buf_umr, SS7_EXTENDED_API,nelem,buff_len);
		p_elem = p_buf_umr + API_HEADER_LEN;

		PUT_2_BYTE_LE (p_elem, SCCP_UMR_DEINIT);
		p_elem+=2;

		if (SS7_FAILURE == send_from_sccp(p_buf_umr,GET_API_LEN(p_buf_umr),SCCP_MODULE_ID,SCCP_UMR_ID,p_ecode))
		{
			sccp_free(p_buf_umr);
		}
	}

	/* Now to DMR */
	buff_len = SCCP_DMR_DEINIT_SIZE;
	nelem = 1 ; /* Extended API Id only  */

	if (SS7_NULL == (p_buf_dmr = sccp_malloc(buff_len)))
	{
		SC_A_TRC (("SCCP::INIT: Cannot allocate memory\n"));
		return(SS7_FAILURE);
	}
	else
	{
		sccp_fill_api_header (p_buf_dmr, SS7_EXTENDED_API,nelem,buff_len);
		p_elem = p_buf_dmr + API_HEADER_LEN;

		PUT_2_BYTE_LE (p_elem, SCCP_DMR_DEINIT);
		p_elem+=2;

		if (SS7_FAILURE == send_from_sccp(p_buf_dmr,GET_API_LEN(p_buf_dmr),SCCP_MODULE_ID,SCCP_DMR_ID,p_ecode))
		{
			sccp_free(p_buf_umr);
		}
	}

	return(ret_val);

}




/*****************************************************************************
 **      FUNCTION :
 **		sccp_update_umr_dmr_on_init
 ******************************************************************************
 **
 **      DESCRIPTION :
 **         Handles init Updation to UMR and DMR  
 **        
 **
 **      NOTE :
 **
 *****************************************************************************/
return_t
sccp_update_umr_dmr_on_init
#ifdef ANSI_PROTO
    (error_t * p_ecode)
#else
	    (p_ecode)
	     error_t * p_ecode;
#endif
{
	return_t ret_val=SS7_SUCCESS;
	U8bit *p_buf_dmr, *p_buf_umr, *p_elem;
	U32bit nelem, buff_len;

	/* Send Dereg Indication to this User --Sachin*/

	buff_len = SCCP_UMR_INIT_SIZE;
	nelem = 2 ; /* Extended API Id only  */

	if (SS7_NULL == (p_buf_umr = sccp_malloc(buff_len)))
	{
		SC_A_TRC (("SCCP::INIT: Cannot allocate memory\n"));
		return(SS7_FAILURE);
	}
	else
	{
		sccp_fill_api_header (p_buf_umr, SS7_EXTENDED_API,nelem,buff_len);
		p_elem = p_buf_umr + API_HEADER_LEN;

		PUT_2_BYTE_LE (p_elem, SCCP_UMR_DEINIT);
		p_elem+=2;

		*p_elem++ = sc_opt.standard;
		*p_elem++ = sc_opt.num_of_bits_instance_id;

		if (SS7_FAILURE == send_from_sccp(p_buf_umr,GET_API_LEN(p_buf_umr),SCCP_MODULE_ID,SCCP_UMR_ID,p_ecode))
		{
			sccp_free(p_buf_umr);
		}
	}

	/* Now to DMR */
	buff_len = SCCP_DMR_INIT_SIZE;
	nelem = 3 ; /* Extended API Id only  */

	if (SS7_NULL == (p_buf_dmr = sccp_malloc(buff_len)))
	{
		SC_A_TRC (("SCCP::INIT: Cannot allocate memory\n"));
		return(SS7_FAILURE);
	}
	else
	{
		sccp_fill_api_header (p_buf_dmr, SS7_EXTENDED_API,nelem,buff_len);
		p_elem = p_buf_dmr + API_HEADER_LEN;

		PUT_2_BYTE_LE (p_elem, SCCP_DMR_INIT);
		p_elem+=2;

		*p_elem++ = sc_opt.standard;
		*p_elem++ = sc_opt.num_of_bits_instance_id;

		if (SS7_FAILURE == send_from_sccp(p_buf_dmr,GET_API_LEN(p_buf_dmr),SCCP_MODULE_ID,SCCP_DMR_ID,p_ecode))
		{
			sccp_free(p_buf_umr);
		}
	}

	return(ret_val);

}
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
/*****************************************************************************
 **      FUNCTION :
 **         Handles Deinit Timeout 
 ******************************************************************************
 **
 **      DESCRIPTION :
 **        
 **
 **      NOTE :
 **
 *****************************************************************************/
return_t
sccp_handle_t_deinit_timeout
#ifdef ANSI_PROTO
(U8bit * p_api)
#else
(p_api)
	U8bit * p_api);
#endif
{
    /* SPR 9302 - Fix Start */
    /*return_t ret_val;*/
    return_t ret_val = 0;
    /* SPR 9302 - Fix End   */

	if (sccp_state==BLOCKED)
	{
		SC_IN_TRC (("SCCP : DEINIT TIMEOUT Stack Uninitialized \n"));
		sccp_state=UNINITIALIZED;
		SCCP_SEND_DEINIT_ENTRY_UPDATE(sccp_state);
		ret_val = SS7_SUCCESS;
	}
	else
	{
		SC_IN_TRC (("SCCP : DEINIT TIMEOUT ... in unblocked state Ignoring  \n"));
	}
	return(ret_val);
	/* SPR 9302 - Fix Start */
	p_api = 0;
	/* SPR 9302 - Fix End   */
}
#endif



/*****************************************************************************
 **      FUNCTION :
 **         initializes all data structures to default
 ******************************************************************************
 **
 **      DESCRIPTION :
 **        database tables, trace, stats and timers are initialized
 **
 **      NOTE :
 **
 *****************************************************************************/
return_t
sccp_default_init_data
#ifdef ANSI_PROTO
(error_t * p_ecode)
#else
(p_ecode)
	error_t * p_ecode;
#endif
{
	return_t ret_val;

	if (STACK_INITIALIZED == sccp_data_state)
	{
		SC_IN_TRC (("SCCP : Data initialized. cannot init again\n"));
		return SS7_FAILURE;
	}

	sccp_data_state = STACK_INITIALIZED;

	if ((SS7_FAILURE == sccp_config_default_timers(p_ecode)) ||
			(SS7_FAILURE == sccp_db_init ()) 
			/* SPR XXXX Fix Starts */
#ifdef SCCP_STATS_ENABLED
	  ||  (SS7_FAILURE == ss7_init_stats (SCCP_MODULE_ID, STATS_ALL, p_ecode))
#endif
	/* SPR XXXX Fix Starts */
	)
	{
		ret_val = SS7_FAILURE;
	}
	else
	{
		sccp_init_seg_ref_table ();
		sccp_data_state = STACK_INITIALIZED;
		ret_val = SS7_SUCCESS;
	}

	SC_IN_TRC (("SCCP::INIT:init default data of sccp %s\n",
	            RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         configures default values for timers
******************************************************************************
**
**      DESCRIPTION :
**        all timers of SCCP are initialised to default values
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_config_default_timers
#ifdef ANSI_PROTO
	(error_t * p_ecode)
#else
	(p_ecode)
	 error_t * p_ecode;
#endif
{
	U8bit i=0;
	tmr_buffer_t sc_def_tim[SCCP_MAX_TIMER_CONFIG_ID + 1];

	/** SPR # 11113 : Start Fix **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)	
    if ((sc_opt.standard == STACK_ANSI) ||
                (sc_opt.standard == STACK_BCGR))
        { 
	  for (i=0; i < (SCCP_MAX_TIMER_CONFIG_ID + 1); i++)
	    {
		sc_def_tim[i].timer_index = i;
		sc_def_tim[i].timer_value = sc_tim_range_ansi[i].def;
	     }
         }
#endif
		if (!((sc_opt.standard == STACK_ANSI) || (sc_opt.standard == STACK_BCGR)))
        {
           for (i=0; i < (SCCP_MAX_TIMER_CONFIG_ID + 1); i++)
            {
                sc_def_tim[i].timer_index = i;
                sc_def_tim[i].timer_value = sc_tim_range[i].def;
             }
         }
	/** SPR # 11113 : End Fix **/


	if (SS7_FAILURE == sccp_init_timers (i, sc_def_tim, p_ecode))
	{
		SC_IN_TRC (("SCCP::INIT:Failed to set default timers\n"));
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         sets timers to desired values
******************************************************************************
**
**      DESCRIPTION :
**        function can be called from encapsulating shell to set timers
**        to desired value
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_init_timers
#ifdef ANSI_PROTO
	(U8bit num_timers, tmr_buffer_t * timers, error_t * p_ecode)
#else
	(num_timers, timers, p_ecode)
	 U8bit 		num_timers;
	 tmr_buffer_t 	*timers;
	 error_t 	*p_ecode;
#endif
{
	U8bit i, timer_config_id;
	U32bit timer_value;

	/* SPR 9302 - Fix Start */
	/* commenting the declaration.Already declared globally */
	/*extern U8bit sccp_state;*/
	/* SPR 9302 - Fix End   */

	if (sccp_state != STACK_INITIALIZED )
	{
		return SS7_FAILURE;
	}

	for (i=0; i < num_timers; i++)
	{
		timer_config_id = timers[i].timer_index;
		timer_value = timers[i].timer_value;

		if (timer_config_id > SCCP_MAX_TIMER_CONFIG_ID)
		{
			SC_IN_TRC (("SCCP::INIT:timer config id %d invalid\n",
			            timer_config_id)); 
			*p_ecode = ESCCP_INVALID_TIMER_CONFIG_ID;
			return SS7_FAILURE;
		}

	/** SPR # 11113 : Start Fix **/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
                if ((sc_opt.standard == STACK_ANSI) ||
                    (sc_opt.standard == STACK_BCGR))
                     {
		       if ((timer_value < sc_tim_range_ansi[timer_config_id].min) ||
		           (timer_value > sc_tim_range_ansi[timer_config_id].max))
		             {
			          SC_IN_TRC (("SCCP::INIT:Invalid timer val %u for timer %d\n",
			            timer_value, timer_config_id));
		               	*p_ecode = ESCCP_INVALID_TIMER_VAL;
		                  return SS7_FAILURE;
		             }
                      }
#endif
                if (!((sc_opt.standard == STACK_ANSI) ||
                    (sc_opt.standard == STACK_BCGR)))
                    {
                       if ((timer_value < sc_tim_range[timer_config_id].min) ||
                           (timer_value > sc_tim_range[timer_config_id].max))
                             {
                                  SC_IN_TRC (("SCCP::INIT:Invalid timer val %u for timer %d\n",timer_value, timer_config_id));
                                *p_ecode = ESCCP_INVALID_TIMER_VAL;
                                  return SS7_FAILURE;
                             }
                      }
	/** SPR # 11113 : End Fix **/


		switch (timer_config_id)
		{
			case T_A_CONFIG_ID:
				sc_tim.t_a_timer_val = timer_value;
				break;

			case T_D_CONFIG_ID:
				sc_tim.t_d_timer_val = timer_value;
				break;

			case T_CON_CONFIG_ID:
				sc_tim.t_con_timer_val = timer_value;
				break;

			case T_STAT_INFO_START_CONFIG_ID:
				sc_tim.t_stat_info_start_timer_val = timer_value;
				break;

			case T_STAT_INFO_END_CONFIG_ID:
				sc_tim.t_stat_info_end_timer_val = timer_value;
				break;

			case T_REASS_CONFIG_ID:
				sc_tim.t_reassmbly_timer_val = timer_value;
				break;
#ifdef DISTRIBUTED_SCCP
			case T_DSCCP_CLASS1_BUFFER_CONFIG_ID:
				sc_tim.t_class1_buffer_timer_val = timer_value;
				break;
/* SPR # 7470 Fix Start */
			case T_DSCCP_CLASS1_INH_MSG_CONFIG_ID:
				sc_tim.t_class1_inh_msg_timer_val = timer_value;
				break;
/* SPR # 7470 Fix End */
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
            case T_CONNEST_CONFIG_ID:

                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_IAS_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_IAR_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_REL_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_REPREL_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_INT_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_GAURD_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_RESET_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;

            case T_FREEZE_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;
/* SPR # 7450 Fix Start */
#ifdef DISTRIBUTED_SCCP
			case T_DSCCP_INST_DEACTIVATION_CONFIG_ID:
                sccp_co_timer_dur [timer_config_id-T_REASS_CONFIG_ID-1]
                                            = timer_value ;
                break;
#endif
/* SPR # 7450 Fix End */
#endif

			default:
				break;
		}
	}

#ifdef DISTRIBUTED_SCCP
	sc_tim.t_reass_query_timer_val = sc_tim.t_reassmbly_timer_val;
#endif

	return SS7_SUCCESS;
}

#ifdef SCCP_INCLUDE_CO_SERVICE

/*****************************************************************************
**
**  FUNCTION :
**
******************************************************************************
**
**  DESCRIPTION :
**
*****************************************************************************/

void
sccp_init_co_service
#ifdef ANSI_PROTO
  (U8bit    standard)
#else
  (standard)
   U8bit    standard ;
#endif
{
#ifdef SCCP_CONNECTION_ID_CHANGES
  U32bit       count;
#else
  U16bit       count ;
#endif
  U16bit       i ;
  sccp_ccb_t   *p_ccb ;
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
  U8bit 	   max_num_bits;
  U8bit 	   n;
  U8bit instance_id;
#endif
/* SPR # 6750 Fix End */

/* SPR # 6126 Fix Start */
  /* Initialise the global free ccb list head which is pointing to the first 
     block of ccb array */
  sccp_free_ccb_list_head = 0;
/* SPR # 6126 Fix End */

  /* Initialise the data base depending on the Standard */
  for (count = 0; count < MAX_SCCP_CO_CONNECTIONS; count++) /* orig code 0  */
  {
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#ifdef SCCP_CONNECTION_ID_CHANGES
    max_num_bits = 24;
#else
    max_num_bits = 16;
#endif
#endif
/* SPR # 6750 Fix End */

#ifdef DISTRIBUTED_SCCP
	n = sc_opt.num_of_bits_instance_id;
	instance_id = sc_opt.dsccp_local_instance_id;

#else
/* SPR # 6750 Fix Start */
#if 0
	n = 0;
	instance_id = 0;
#endif
/* SPR # 6750 Fix End */
#endif


/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
    /* number of CCB blocks per instance cannot be more than 
    ** 2^(max_num_bits - n) as the 'n' most significant bits will contain the 
    ** instance ID in case of DSCCP; If Distribution logic is not used, then 
    ** 'n' = 0; i.e. 0 bits are used for instance ID 
    */ 

    if  (count >= ~(0xffffffff << (max_num_bits - n)))
          break;
#endif
/* SPR # 6750 Fix End */

    p_ccb = &sccp_ccb [count] ;

    p_ccb->c_state = SCCP_CONN_IDLE ;
    p_ccb->c_status = 0x00 ;
#ifdef SCCP_CONNECTION_ID_CHANGES
    p_ccb->conn_id = p_ccb->ccb_id = (U32bit)count ;
#else
	p_ccb->conn_id = p_ccb->ccb_id = (U16bit)count ;
#endif

/* SPR # 7170 Fix Start */
	p_ccb->p_trans_queue = (sc_queue_t *)SS7_NULL;
	p_ccb->p_recv_queue = (sc_queue_t *)SS7_NULL;
	p_ccb->p_ed_trans_queue = (sc_queue_t *)SS7_NULL;

/* SPR # 7170 Fix end */


/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
    p_ccb->conn_id = p_ccb->conn_id  | 
		(instance_id << (max_num_bits - n));
#endif
/* SPR # 6750 Fix End */

/* SPR # 6126 Fix Start */
    /*create a link list of ccb's with each node pointing to it's next. */
    if(count == MAX_SCCP_CO_CONNECTIONS -1)
        p_ccb->next_ccb_id = SCCP_INVALID_CCB_ID; 
    else
        p_ccb->next_ccb_id = count + 1;


    p_ccb->prev_ccb_id = SCCP_INVALID_CCB_ID; 
/* SPR # 6126 Fix End */


    for (i = 0; i < MAX_SCCP_CO_TIMERS; i++)
    {
      p_ccb->sccp_timer [i].timer_status = SCCP_CO_TIMER_NOTRUNNING ;
    }

  }

/* SPR # 6126 Fix Start */
  /* Initialize the hash table */
  for (count = 0; count < MAX_SCCP_CO_HASH_TABLE_SIZE; count++)
	sccp_hash_table[count] = SCCP_INVALID_CCB_ID;
/* SPR # 6126 Fix End */
  

  sccp_init_co_function_table () ;

/* SPR 8985 - Fix Start */
/* This line of code is added to remove "unused parameter" warning */
  standard = 0;
/* SPR 8985 - Fix End   */
  return ;
}

#endif

/** SPR 11500 Start Fix **/
/*****************************************************************************
**      FUNCTION :
**         Clears SCCP Database on Initialization
******************************************************************************
**
**      DESCRIPTION :
**        Clears SCCP Structures that form the database and sets the value
**        to Zero. 
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_init_flush_db
#ifdef ANSI_PROTO
  (error_t	*p_ecode)
#else
  (standard)
   error_t	*p_ecode;
#endif
{
	extern 	sccp_db_t 		sccp_db;
	extern	sc_reg_entry_t 	sccp_reg_table[MAX_LOCAL_USERS];

#ifdef SCCP_ERROR_ENABLED
	extern	U8bit 			sccp_event_table;
	extern	U32bit 			sccp_error_table[MAX_ERROR_LEVELS];
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
	extern	timer_id_t 		deinit_timer_id;
	extern	sccp_ccb_t 		sccp_ccb[MAX_SCCP_CO_CONNECTIONS];
#endif

	ss7_mem_zero((void *) &sccp_db, sizeof(sccp_db));
	ss7_mem_zero((void *) &sccp_reg_table, sizeof(sccp_reg_table));

#ifdef SCCP_ERROR_ENABLED
	ss7_mem_zero((void *) &sccp_error_table, sizeof(sccp_error_table));
	sccp_event_table = SS7_FALSE;
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
	ss7_mem_zero((void *) &sccp_ccb, sizeof(sccp_ccb));
	deinit_timer_id = SS7_FALSE;
#endif

	return SS7_SUCCESS;
}
/** SPR 11500 Start Fix **/
