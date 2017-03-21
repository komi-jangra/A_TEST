/***************************************************************************
**  FILE NAME:
**      sc_timer.h
**
****************************************************************************
**
**  FUNCTION:
**      
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#     REASON
**  -------  ----------------  -----    -------------------------------------
**  06Aug2002 Salil Agrawal             Fixed Spr #9172
**  08Aug2002 Ashish Sawalkar 			Fixed SPR 9524	
**  14Mar2002 Sachin Bhatia   			Added DEINIT Timer Information 
**  22Jan2002 Prateek Bidwalkar ----    Fixed SPR#7470
**  26Dec2001 Prateek Bidwalkar ----    Fixed SPR#7450
**  22Nov2000 Hemlata Baudhwar SPR#4583 Original
**  12May'98 Sriganesh. Kini   -----    Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_TIMER_H_
#define _SC_TIMER_H_

#include "sc_s7gl.h"

#define SCCP_TIMER_ID_BASE    0

/* Timers userd by SCMG */
#define T_A_TIMER_ID          (SCCP_TIMER_ID_BASE + 0)
#define T_D_TIMER_ID          (SCCP_TIMER_ID_BASE + 1)
#define T_CON_TIMER_ID        (SCCP_TIMER_ID_BASE + 2)
#define T_STAT_INFO_TIMER_ID  (SCCP_TIMER_ID_BASE + 3)
#define T_STAT_INFO_END_TIMER_ID  (SCCP_TIMER_ID_BASE + 4)

/* spr 9172 starts */

/* Timers used by SCLC */
#define T_REASSEMBLY_TIMER_ID (SCCP_TIMER_ID_BASE + 5)

#ifdef SCCP_INCLUDE_CO_SERVICE

#define T_CONNEST_TIMER_ID    (SCCP_TIMER_ID_BASE + 6)
#define T_IAS_TIMER_ID        (SCCP_TIMER_ID_BASE + 7)
#define T_IAR_TIMER_ID        (SCCP_TIMER_ID_BASE + 8)
#define T_REL_TIMER_ID        (SCCP_TIMER_ID_BASE + 9)
#define T_REPREL_TIMER_ID     (SCCP_TIMER_ID_BASE + 10)
#define T_INT_TIMER_ID        (SCCP_TIMER_ID_BASE + 11)
#define T_GAURD_TIMER_ID      (SCCP_TIMER_ID_BASE + 12)
#define T_RESET_TIMER_ID      (SCCP_TIMER_ID_BASE + 13)
#define T_FREEZE_TIMER_ID     (SCCP_TIMER_ID_BASE + 14)
/** SPR# 9524 Start Fix **/
#define T_DEINIT_TIMER_ID     (SCCP_TIMER_ID_BASE + 22)
/** SPR# 9524 End Fix **/

#endif
#ifdef DISTRIBUTED_SCCP
#define T_DSCCP_CONF_TIMER_ID     (SCCP_TIMER_ID_BASE + 15)
#define T_REASSEMBLY_QUERY_TIMER_ID (SCCP_TIMER_ID_BASE + 16)
#define T_DSCCP_CLASS1_BUFFER_TIMER_ID (SCCP_TIMER_ID_BASE + 17)
/* SPR # 7450 Fix Start */
#define T_DSCCP_INST_DEACTIVATION_TIMER_ID	(SCCP_TIMER_ID_BASE + 18)
/* SPR # 7450 Fix End */

/* SPR # 7470 Fix Start */
#define T_DSCCP_CLASS1_BUFFER_INHIBIT_ID	(SCCP_TIMER_ID_BASE + 19)
/* SPR # 7470 Fix End */
#endif



/* SPR # 7470 Fix Start */
/* SPR # 7450 Fix Start */

#ifdef BACK_UP_SSN
#define T_COORD_TIMER_ID     (SCCP_TIMER_ID_BASE + 20)
#define T_IGNORE_SST_TIMER_ID     (SCCP_TIMER_ID_BASE + 21)
#endif
/* SPR # 7450 Fix End */
/* SPR # 7470 Fix End */

/* spr 9172 ends */

/* spr # 9172 starts */
/* commented by salil to fis spr 9172 */
#if 0
/* Timers used by SCLC */
#define T_REASSEMBLY_TIMER_ID (SCCP_TIMER_ID_BASE + 4)

#ifdef SCCP_INCLUDE_CO_SERVICE

#define T_CONNEST_TIMER_ID    (SCCP_TIMER_ID_BASE + 5)
#define T_IAS_TIMER_ID        (SCCP_TIMER_ID_BASE + 6)
#define T_IAR_TIMER_ID        (SCCP_TIMER_ID_BASE + 7)
#define T_REL_TIMER_ID        (SCCP_TIMER_ID_BASE + 8)
#define T_REPREL_TIMER_ID     (SCCP_TIMER_ID_BASE + 9)
#define T_INT_TIMER_ID        (SCCP_TIMER_ID_BASE + 10)
#define T_GAURD_TIMER_ID      (SCCP_TIMER_ID_BASE + 11)
#define T_RESET_TIMER_ID      (SCCP_TIMER_ID_BASE + 12)
#define T_FREEZE_TIMER_ID     (SCCP_TIMER_ID_BASE + 13)
/** SPR# 9524 Start Fix **/
#define T_DEINIT_TIMER_ID     (SCCP_TIMER_ID_BASE + 21)
/** SPR# 9524 End Fix **/

#endif
#ifdef DISTRIBUTED_SCCP
#define T_DSCCP_CONF_TIMER_ID     (SCCP_TIMER_ID_BASE + 14)
#define T_REASSEMBLY_QUERY_TIMER_ID (SCCP_TIMER_ID_BASE + 15)
#define T_DSCCP_CLASS1_BUFFER_TIMER_ID (SCCP_TIMER_ID_BASE + 16)
/* SPR # 7450 Fix Start */
#define T_DSCCP_INST_DEACTIVATION_TIMER_ID	(SCCP_TIMER_ID_BASE + 17)
/* SPR # 7450 Fix End */

/* SPR # 7470 Fix Start */
#define T_DSCCP_CLASS1_BUFFER_INHIBIT_ID	(SCCP_TIMER_ID_BASE + 18)
/* SPR # 7470 Fix End */
#endif



/* SPR # 7470 Fix Start */
/* SPR # 7450 Fix Start */

#ifdef BACK_UP_SSN
#define T_COORD_TIMER_ID     (SCCP_TIMER_ID_BASE + 19)
#define T_IGNORE_SST_TIMER_ID     (SCCP_TIMER_ID_BASE + 20)
#endif
/* SPR # 7450 Fix End */
/* SPR # 7470 Fix End */

#endif 
/* spr #9172 ends */

#ifdef DISTRIBUTED_SCCP


#define SCCP_TIMER_ID_LEN     1

#define T_A_CONFIG_ID                0
#define T_D_CONFIG_ID                1
#define T_CON_CONFIG_ID              2
#define T_STAT_INFO_START_CONFIG_ID  3
#define T_STAT_INFO_END_CONFIG_ID    4
#define T_REASS_CONFIG_ID            5
#ifdef SCCP_INCLUDE_CO_SERVICE

#define T_CONNEST_CONFIG_ID			 6
#define T_IAS_CONFIG_ID			 	 7
#define T_IAR_CONFIG_ID			 	 8
#define T_REL_CONFIG_ID			 	9
#define T_REPREL_CONFIG_ID			10
#define T_INT_CONFIG_ID			 	11
#define T_GAURD_CONFIG_ID			12
#define T_RESET_CONFIG_ID			13
#define T_FREEZE_CONFIG_ID			14
#define T_DSCCP_CONF_CONFIG_ID    		15 
#define T_REASSEMBLY_QUERY_CONFIG_ID    		16 
#define T_DSCCP_CLASS1_BUFFER_CONFIG_ID    		17 
/* SPR # 7450 Fix Start */
#define T_DSCCP_INST_DEACTIVATION_CONFIG_ID		18
/* SPR # 7470 Fix Start */
#define T_DSCCP_CLASS1_INH_MSG_CONFIG_ID		19
/* SPR # 7470 Fix End */

#if 0
#define SCCP_MAX_TIMER_CONFIG_ID     T_DSCCP_CLASS1_BUFFER_CONFIG_ID
#endif

/* SPR # 7470 Fix Start */
#if 0
#define SCCP_MAX_TIMER_CONFIG_ID     T_DSCCP_INST_DEACTIVATION_CONFIG_ID
#endif
#define SCCP_MAX_TIMER_CONFIG_ID     T_DSCCP_CLASS1_INH_MSG_CONFIG_ID
/* SPR # 7470 Fix End */
/* SPR # 7450 Fix End */

#else
#define T_DSCCP_CONF_CONFIG_ID    		6 
#define T_REASSEMBLY_QUERY_CONFIG_ID    		7 
#define T_DSCCP_CLASS1_BUFFER_CONFIG_ID    		8 
#define SCCP_MAX_TIMER_CONFIG_ID     T_DSCCP_CLASS1_BUFFER_CONFIG_ID
#endif

#else
#define SCCP_TIMER_ID_LEN     1

#define T_A_CONFIG_ID                0
#define T_D_CONFIG_ID                1
#define T_CON_CONFIG_ID              2
#define T_STAT_INFO_START_CONFIG_ID  3
#define T_STAT_INFO_END_CONFIG_ID    4
#define T_REASS_CONFIG_ID            5
#ifdef SCCP_INCLUDE_CO_SERVICE

#define T_CONNEST_CONFIG_ID			 6
#define T_IAS_CONFIG_ID			 	 7
#define T_IAR_CONFIG_ID			 	 8
#define T_REL_CONFIG_ID			 	 9
#define T_REPREL_CONFIG_ID			10
#define T_INT_CONFIG_ID			 	11
#define T_GAURD_CONFIG_ID			12
#define T_RESET_CONFIG_ID			13
#define T_FREEZE_CONFIG_ID			14


#define SCCP_MAX_TIMER_CONFIG_ID     T_FREEZE_CONFIG_ID
#else
#define SCCP_MAX_TIMER_CONFIG_ID     T_REASS_CONFIG_ID
#endif

#endif

typedef struct {
	U8bit  timer_index; /* Config IDs as defined above */
	U32bit timer_value; /* Value is in 10s of mill seconds */
} tmr_buffer_t;

/* All timer values are in 10s of milliseconds */

/* Minimum and maximum for all timers */
#define T_A_MIN_TIMER_VAL                 6L      /* 60 ms */
#define T_A_MAX_TIMER_VAL                 60L     /* 600 ms */
#define T_D_MIN_TIMER_VAL                 100L    /* 1 sec */
#define T_D_MAX_TIMER_VAL                 1000L   /* 10 sec */
#define T_CON_MIN_TIMER_VAL               100L    /* 1 sec */
#define T_CON_MAX_TIMER_VAL               1000L   /* 10 sec */
#define T_STAT_INFO_MIN_START_TIMER_VAL   500L    /* 5 sec */
#define T_STAT_INFO_MAX_START_TIMER_VAL   1000L   /* 10 sec */
#define T_COORD_MIN_TIMER_VAL   6000L   /* 1 min */
#define T_COORD_MAX_TIMER_VAL   12000L   /* 2 min */
#define T_IGNORE_SST_TIMER_VAL   12000L   /* 2 min */

/* Fix SPR#4583 Start */
/* Replaced 600000L with 60000L 10min = 60000L in 10's of milliseconds */
/* Replaced 1200000L with 120000L 20min = 120000L in 10's of milliseconds */
#define T_STAT_INFO_MIN_END_TIMER_VAL     60000L /* 10 min */
#define T_STAT_INFO_MAX_END_TIMER_VAL    120000L /* 20 min */
/* Fix SPR#4583 End */
#define T_REASSEMBLY_MIN_TIMER_VAL        1000L   /* 10 sec */
#define T_REASSEMBLY_MAX_TIMER_VAL        2000L   /* 20 sec */

#ifdef SCCP_INCLUDE_CO_SERVICE

/* spr fix 9715 starts */
#define SCCP_T_CONNEST_TIMER_MIN_VAL         6000L 
#define SCCP_T_CONNEST_TIMER_MIN_VAL_ANSI    18000L   
#define SCCP_T_CONNEST_TIMER_MAX_VAL         12000L
#define SCCP_T_CONNEST_TIMER_MAX_VAL_ANSI     36000L
#define SCCP_T_IAS_TIMER_MIN_VAL     30000L   /* 5 min */
#define SCCP_T_IAS_TIMER_MAX_VAL     60000L   /* 10 min */
#define SCCP_T_IAR_TIMER_MIN_VAL     66000L   /* 11 min */
#define SCCP_T_IAR_TIMER_MAX_VAL     126000L 
#define SCCP_T_IAR_TIMER_MAX_VAL_ANSI   132000L
#define SCCP_T_REL_TIMER_MIN_VAL     1000L    /* 10 sec */
#define SCCP_T_REL_TIMER_MAX_VAL     2000L    /* 20 sec */
#define SCCP_T_REPREL_TIMER_MIN_VAL  1000L    /* 10 sec */
#define SCCP_T_REPREL_TIMER_MAX_VAL  2000L    /* 20 sec */
#define SCCP_T_INT_TIMER_MIN_VAL     5000L    /* 50 sec */
#define SCCP_T_INT_TIMER_MAX_VAL     6000L    /* 1 min */
#define SCCP_T_GAURD_TIMER_MIN_VAL   138000L  /* 23 min */
#define SCCP_T_GAURD_TIMER_MAX_VAL   150000L  /* 25 min */
#define SCCP_T_RESET_TIMER_MIN_VAL    1000L  
#define SCCP_T_RESET_TIMER_MIN_VAL_ANSI  2000L 
#define SCCP_T_RESET_TIMER_MAX_VAL     2000L 
#define SCCP_T_RESET_TIMER_MAX_VAL_ANSI   4000L 
/* spr fix 9715 ends */
#define SCCP_T_FREEZE_TIMER_MIN_VAL  500L    /* 6000L 1 min Change by Amaresh as on dated 11-03-16*/ 
#define SCCP_T_FREEZE_TIMER_MAX_VAL  6000L    /* 1 min */
#endif

#ifdef DISTRIBUTED_SCCP

#define DSCCP_T_CONFIG_TIMER_MIN_VAL 1000L
#define DSCCP_T_CONFIG_TIMER_MAX_VAL 6000L
#define DSCCP_T_CONFIG_TIMER_DEF_VALUE DSCCP_T_CONFIG_TIMER_MIN_VAL

#define DSCCP_T_CLASS1_BUFFER_TIMER_MIN_VAL 2500L
#define DSCCP_T_CLASS1_BUFFER_TIMER_MAX_VAL 4500L
#define DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE DSCCP_T_CLASS1_BUFFER_TIMER_MIN_VAL

#define T_REASS_QUERY_TIMER_MIN_VAL T_REASSEMBLY_MIN_TIMER_VAL
#define T_REASS_QUERY_TIMER_MAX_VAL T_REASSEMBLY_MAX_TIMER_VAL
#define T_REASS_QUERY_TIMER_DEF_VALUE T_REASS_QUERY_TIMER_MIN_VAL

/* SPR # 7450 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
#define DSCCP_T_INST_DEACTIVATION_TIMER_MIN_VAL (SCCP_T_IAR_TIMER_MIN_VAL + \
												SCCP_T_FREEZE_TIMER_MIN_VAL)
#define DSCCP_T_INST_DEACTIVATION_TIMER_MAX_VAL (SCCP_T_IAR_TIMER_MAX_VAL + \
												SCCP_T_FREEZE_TIMER_MAX_VAL)
#define DSCCP_T_INST_DEACTIVATION_TIMER_DEF_VAL (DSCCP_T_INST_DEACTIVATION_TIMER_MIN_VAL)
#endif
/* SPR # 7450 Fix End */

/* SPR # 7470 Fix Start */
#define DSCCP_T_CLASS1_BUF_INH_MSG_MIN_VAL 2500L
#define DSCCP_T_CLASS1_BUF_INH_MSG_MAX_VAL 4500L
#define DSCCP_T_CLASS1_BUF_INH_MSG_DEF_VAL DSCCP_T_CLASS1_BUF_INH_MSG_MIN_VAL
/* SPR # 7470 Fix End */

#endif


/* Default values for all timers */
#define T_A_DEF_TIMER_VAL                 T_A_MIN_TIMER_VAL
#define T_D_DEF_TIMER_VAL                 T_D_MIN_TIMER_VAL
#define T_CON_DEF_TIMER_VAL               T_CON_MIN_TIMER_VAL
#define T_STAT_INFO_DEF_START_TIMER_VAL   T_STAT_INFO_MIN_START_TIMER_VAL
#define T_STAT_INFO_DEF_END_TIMER_VAL     T_STAT_INFO_MIN_END_TIMER_VAL
#define T_REASSEMBLY_DEF_TIMER_VAL        T_REASSEMBLY_MIN_TIMER_VAL

#ifdef SCCP_INCLUDE_CO_SERVICE

/********** timer values in miliseconds ***********************/
#define SCCP_T_CONNEST_TIMER_DEF_VALUE 6000L    /* 1 min */
#define SCCP_T_CONNEST_TIMER_DEF_VALUE_ANSI 18000L
#define SCCP_T_IAS_TIMER_DEF_VALUE     30000L   /* 5 min */
#define SCCP_T_IAR_TIMER_DEF_VALUE     66000L   /* 11 min */
#define SCCP_T_REL_TIMER_DEF_VALUE     1000L    /* 10 sec */
#define SCCP_T_REPREL_TIMER_DEF_VALUE  1000L    /* 10 sec */
#define SCCP_T_INT_TIMER_DEF_VALUE     5000L    /* 50 sec */
#define SCCP_T_GAURD_TIMER_DEF_VALUE   138000L  /* 23 min */
#define SCCP_T_RESET_TIMER_DEF_VALUE   1000L    /* 10 sec */
#define SCCP_T_RESET_TIMER_DEF_VALUE_ANSI 2000L
#define SCCP_T_FREEZE_TIMER_DEF_VALUE  6000L    /* 1 min 6000L */

/* The DEINIT Timeout waits for all connections to be released propely */
#define SCCP_T_DEINIT_TIMER_DEF_VAL    (SCCP_T_REL_TIMER_DEF_VALUE + \
										SCCP_T_INT_TIMER_DEF_VALUE + \
										SCCP_T_FREEZE_TIMER_DEF_VALUE + \
										6000L)

#endif

//Based on Iwave requirement, changed the following value to 5 sec from 100 sec.
#define T_STAT_INFO_TIMER_STEP_VALUE      500 /* 5 sec */

typedef struct
{
	U32bit t_a_timer_val;
	U32bit t_d_timer_val;
	U32bit t_con_timer_val;
	U32bit t_stat_info_start_timer_val;
	U32bit t_stat_info_end_timer_val;

	U32bit t_reassmbly_timer_val;
#ifdef DISTRIBUTED_SCCP
	U32bit t_reass_query_timer_val;
	U32bit t_class1_buffer_timer_val;
/* SPR # 7470 Fix Start */
	U32bit	t_class1_inh_msg_timer_val;
/* SPR # 7470 Fix End */
#endif
} sccp_timer_t;

extern sccp_timer_t sc_tim;

#endif /* _SC_TIMER_H_ */
