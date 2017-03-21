/***************************************************************************
**  FILE NAME:
**      sc_dbf.h
**
****************************************************************************
**
**  FUNCTION:
**      all database structures for signaling point, subsystems and
**      concerned subsystem and signaling point along with macros
**      to access their fields
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**  22Aug'02 Prateek Bidwalkar	      Fixed SPR # 9502
**  21Nov'03 knaveen           -----  Fixed SPR # 13075
**  25Feb'04 Hitesh Sharma     -----  Fixed SPR # 13263
**  08Apr'04 Hitesh Sharma 	      Fixed SPR # 13344
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_DBF_H_
#define _SC_DBF_H_

#include "sc_s7gl.h"
#include "sc_cdef.h"

/* Fix for SPR No : 13263 start */

typedef U32bit ss_id_t;
#define SIZEOF_SS_ID_T 4

typedef U32bit sp_id_t;
#define SIZEOF_SP_ID_T 4

#if 0

#if (MAX_SS < 255)
	typedef U8bit ss_id_t;
	#define SIZEOF_SS_ID_T 1
#elif (MAX_SS < 65535)
	typedef U16bit ss_id_t;
	#define SIZEOF_SS_ID_T 2
#else
	typedef U32bit ss_id_t;
	#define SIZEOF_SS_ID_T 4
#endif

/* Start Spr 13075 Fix */
#if 0
#if (MAX_SP < 255)
	typedef U8bit sp_id_t;
	#define SIZEOF_SP_ID_T 1
#elif (MAX_SP < 65535)
	typedef U16bit sp_id_t;
	#define SIZEOF_SP_ID_T 2
#else
	typedef U32bit sp_id_t;
	#define SIZEOF_SP_ID_T 4
#endif
#endif
/* The default typedef is used since MAX_SP is init time parameter */
typedef U32bit sp_id_t;
#define SIZEOF_SP_ID_T 4
/* Stop Spr 13075 Fix */

#endif
/* Fix for SPR No : 13263 stop */

typedef U8bit nw_id_t;
typedef U16bit cluster_t;   

/* Start Spr 13263 Fix  */
#if 0

/* Start Spr 13075 Fix */
#if 0
#define SIZEOF_C_SS_SP_ARRAY (SIZEOF_SP_ID_T * MAX_CSP + SIZEOF_SS_ID_T * MAX_CSS)

#if   (SIZEOF_C_SS_SP_ARRAY < 255)
	typedef U8bit c_ss_sp_t;
#elif (SIZEOF_C_SS_SP_ARRAY < 65535)
	typedef U16bit c_ss_sp_t;
#else
	typedef U32bit c_ss_sp_t;
#endif
#endif
typedef U32bit c_ss_sp_t;
/* Stop Spr 13075 Fix */

#endif
extern U32bit SIZEOF_C_SS_SP_ARRAY ;


typedef U32bit c_ss_sp_t;
/* Stop Spr 13263 Fix */

typedef struct
{
	U32bit sp_id;
	U8bit nw_id;
	U32bit pc;
	Boolean local;
} db_sp_conf_info_t;

typedef struct
{
	U32bit ss_id;
	U8bit ssn;
	U32bit sp_id;
} db_ss_conf_info_t;

typedef struct
{
	U32bit ss_id;
	U32bit css_id;
} db_css_info_t;

typedef struct
{
	U32bit ss_id;
	U32bit csp_id;
} db_csp_info_t;

#if defined (SCCP_ANSI) || defined (SCCP_BCGR) || defined (SCCP_CHINESE)
	typedef U32bit pc_t;
#else
	typedef U16bit pc_t;
#endif

typedef struct
{
	U8bit conf_status; /* Not-configured, Configured */

	U8bit ssn;

	sp_id_t sp_id;

	ss_id_t  next_ss_id; /* Next ss in the linked list of ss for this sp */

	c_ss_sp_t num_css;
	c_ss_sp_t css_list_idx;

	c_ss_sp_t num_csp;
	c_ss_sp_t csp_list_idx;

	/* Other information related to the Subsystem */
	Boolean allowed;
        Boolean registered;

	U32bit prev_t_stat_info_timer_val;
	Boolean t_stat_info_running;
	timer_id_t t_stat_info_timer_id;

	/* Same as logical user id given in register message */
	dst_id_t dst_id;
#ifdef DISTRIBUTED_SCCP
	U8bit sst_instance_id;
#endif
#ifdef BACK_UP_SSN
	Boolean t_coord_timer_running;
	Boolean waiting_for_grant;
	U32bit t_coord_timer_val;
	timer_id_t t_coord_timer_id;
	Boolean t_ignore_sst_timer_running;
	U32bit t_ignore_sst_timer_val;
	timer_id_t t_ignore_sst_timer_id;
	Boolean ignore_sst_mark;
#endif
	
	
} ss_entry_t;


typedef struct
{
	U8bit conf_status; /* Not-configured, Configured */
	U8bit active;

	nw_id_t nw_id;
	pc_t pc;
	Boolean local;
	U8bit ssf;

	sp_id_t next_sp_id;

	ss_entry_t scmg_ss;

	U8bit num_ss;
	ss_id_t ss_id_list;

	/* Other information related to the Signaling Point */
	Boolean allowed;

	/* Status of the User part (SCCP) of the signaling point */
	Boolean upu_received;
	U8bit upu_cause;
	/* Fix for SPR No: 13344 Start */
	U8bit cong_cause; 
	/* Fix for SPR No: 13344 Start */
	S8bit   rlm;
	S8bit   rslm;
	S8bit	cls; /* Congestion level */

	S8bit	rl;  /* Restriction level */
	S8bit	rsl; /* Restriction sub level */
	U8bit	ril; /* Restricted importance level */

	/* SP related timers */
	Boolean t_con_running;
	timer_id_t t_con_timer_id;

	Boolean t_a_running;
	timer_id_t t_a_timer_id;

	Boolean t_d_running;
	timer_id_t t_d_timer_id;

} sp_entry_t;


typedef struct
{
/* Start Spr 13263 Fix */
#if 0
/* Start Spr 13075 Fix */
/*  sp_entry_t sp[MAX_SP]; */
	sp_entry_t *sp;
/* Stop Spr 13075 Fix */
	ss_entry_t ss[MAX_SS];

	c_ss_sp_t end_conc_ss_sp;
/* Start Spr 13075 Fix */
/*	U8bit conc_ss_sp_list[SIZEOF_C_SS_SP_ARRAY]; */
	U8bit *conc_ss_sp_list;
/* Stop Spr 13075 Fix */
#endif
    sp_entry_t  *sp;
    ss_entry_t  *ss;

    c_ss_sp_t end_conc_ss_sp;
    U8bit *conc_ss_sp_list ;
/* Stop Spr 13263 Fix */


} sccp_db_t;

typedef struct {
		Boolean used;
		U8bit ssn;
		pc_t point_code;
	}sccp_db_ssn_back_up;

#ifdef BACK_UP_SSN
extern sccp_db_ssn_back_up sccp_back_up_table[];
#endif

extern sccp_db_t sccp_db;

#define SC_NOT_CONFIGURED 0
#define SC_CONFIGURED 1

/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
/* This hash define is replaced by value at all places */
 #define IS_SPID_VALID(sp_id)  ((sp_id) < MAX_SP) 
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
#define IS_SSID_VALID(ss_id)  ((ss_id) < MAX_SS)

#define GET_SP_FROM_ID(sp_id) (&sccp_db.sp[(sp_id_t)sp_id])
#define GET_ID_FROM_SP(p_sp)  ((sp_id_t)((p_sp) - GET_SP_FROM_ID(0)))
#define GET_SS_FROM_ID(ss_id) (&sccp_db.ss[(ss_id_t)(ss_id)])
#define GET_ID_FROM_SS(p_ss)  ((ss_id_t)((p_ss) - GET_SS_FROM_ID(0)))

/* Macros to set fields of signaling points */
#define SET_SP_CONFIGURED(p_sp)      ((p_sp)->conf_status = SC_CONFIGURED)
#define IS_SP_CONFIGURED(p_sp)       (SC_CONFIGURED == (p_sp)->conf_status)
#define SET_SP_NOT_CONFIGURED(p_sp)  ((p_sp)->conf_status = SC_NOT_CONFIGURED)

#define SET_SP_NW_ID(p_sp, network_id)  ((p_sp)->nw_id = (nw_id_t)(network_id))
#define SET_SP_PC(p_sp, point_code)  ((p_sp)->pc = (pc_t)(point_code))
#define SET_SP_LOCAL_FLAG(p_sp, local_flag)  ((p_sp)->local = (Boolean)(local_flag))
#define SET_NUM_SS_IN_SP(p_sp, num_subsys)  ((p_sp)->num_ss = (U8bit)num_subsys)
#define SET_SS_LIST_IN_SP(p_sp, p_ss)   ((p_sp)->ss_id_list = GET_ID_FROM_SS(p_ss))
#define SET_NEXT_SP_HASH_BUCKET(p_sp, p_next_sp)  ((p_sp)->sp_id = GET_ID_FROM_SP(p_next_sp))
#define SET_NEXT_SP(p_sp, p_next_sp)    ((p_sp)->next_sp_id = GET_ID_FROM_SP(p_next_sp))

/* Macros to get fields of signaling points */
#define GET_SP_NW_ID(p_sp)   ((p_sp)->nw_id)
#define GET_SP_PC(p_sp)      ((p_sp)->pc)
#define IS_SP_LOCAL(p_sp)    ((p_sp)->local)
#define GET_NUM_SS_IN_SP(p_sp)  ((p_sp)->num_ss)
#define GET_SS_LIST_IN_SP(p_sp)  (GET_SS_FROM_ID((p_sp)->ss_id_list))
#define GET_NEXT_SP(p_sp)    (GET_SP_FROM_ID((p_sp)->next_sp_id))
/* SPR 10855 - Fix Start */
/*#define GET_SP_CLUSTER(p_sp) (((GET_SP_PC(p_sp)) >> 8) & 0xffff) */   
#define GET_SP_CLUSTER(p_sp) (((GET_SP_PC(p_sp)) >> 8) & 0x00ff)   
/* SPR 10855 - Fix End  */


#define BYTEID_FROM_PTR(p_byte)   ((c_ss_sp_t)((p_byte) - &sccp_db.conc_ss_sp_list[0]))

#define PTR_FROM_BYTEID(c_ss_sp_id) \
	((U8bit *)(&sccp_db.conc_ss_sp_list[(c_ss_sp_id_t)c_ss_sp_id]))
#define END_OF_BYTE_ARRAY()  \
	((U8bit *)(&sccp_db.conc_ss_sp_list[sccp_db.end_conc_ss_sp]))

/* Macros to set fields of subsystems */
#define SET_SS_CONFIGURED(p_ss)  ((p_ss)->conf_status = SC_CONFIGURED)
#define IS_SS_CONFIGURED(p_ss)   (SC_CONFIGURED == (p_ss)->conf_status)
#define SET_SS_NOT_CONFIGURED(p_ss)  ((p_ss)->conf_status = SC_NOT_CONFIGURED)
#define SET_SP_OF_SS(p_ss, p_sp)     ((p_ss)->sp_id = (sp_id_t)GET_ID_FROM_SP(p_sp))
#define SET_SS_SSN(p_ss, subsystem_number)  ((p_ss)->ssn = (subsystem_number))
#define SET_NEXT_SS(p_ss, p_next_ss)  ((p_ss)->next_ss_id = GET_ID_FROM_SS(p_next_ss))
#define SET_CSS_LIST(p_ss, p_byte)    ((p_ss)->css_list_idx = BYTEID_FROM_PTR(p_byte))
#define SET_CSP_LIST(p_ss, p_byte)    ((p_ss)->csp_list_idx = BYTEID_FROM_PTR(p_byte))
#define SET_NUM_CSS(p_ss, num_conc_ss)  ((p_ss)->num_css = (ss_id_t)(num_conc_ss))
#define SET_NUM_CSP(p_ss, num_conc_sp)  ((p_ss)->num_csp = (sp_id_t)(num_conc_sp))

#define GET_SP_OF_SS(p_ss)     (GET_SP_FROM_ID((p_ss)->sp_id))
#define GET_SS_NW_ID(p_ss)     (GET_SP_NW_ID(GET_SP_OF_SS(p_ss)))
#define IS_SS_LOCAL(p_ss)      (IS_SP_LOCAL(GET_SP_OF_SS(p_ss)))
#define GET_SS_SSN(p_ss)       ((p_ss)->ssn)
#define GET_NEXT_SS(p_ss)      (GET_SS_FROM_ID((p_ss)->next_ss_id))
#define GET_CSS_LIST(p_ss)     ((U8bit *)(&sccp_db.conc_ss_sp_list[(p_ss)->css_list_idx]))
#define GET_CSS_FROM_LIST(p_byte) (sccp_db_get_css_from_list(p_byte))
#define GET_NEXT_CSS_FROM_LIST(p_byte) (p_byte + SIZEOF_SS_ID_T)
#define GET_CSP_FROM_LIST(p_byte)  (sccp_db_get_csp_from_list(p_byte))
#define GET_NEXT_CSP_FROM_LIST(p_byte) (p_byte + SIZEOF_SP_ID_T)
#define GET_CSP_LIST(p_ss)     ((U8bit *)(&sccp_db.conc_ss_sp_list[(p_ss)->csp_list_idx]))
#define GET_NUM_CSS(p_ss)      ((p_ss)->num_css)
#define GET_NUM_CSP(p_ss)      ((p_ss)->num_csp)
#define GET_CSS(p_byte)

#define MIN_VALID_SSN 2

/* Start Spr 13075 Fix */
/* The macros will be replaced by the values at all places */
/* Start Spr 13263 Fix */
#define CSS_SPACE_EXISTS()    ((sccp_db.end_conc_ss_sp + SIZEOF_SS_ID_T) < \
                               SIZEOF_C_SS_SP_ARRAY)

#define CSP_SPACE_EXISTS()    ((sccp_db.end_conc_ss_sp + SIZEOF_SP_ID_T) < \
                               SIZEOF_C_SS_SP_ARRAY)
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */

#define ITU_T_14_BIT_PC  1
#define ANSI_24_BIT_PC   2
#define JAPANESE_16_BIT_PC  3

#define ITU_T_PC_NUM_BITS  14
#define JAPANESE_PC_NUM_BITS  16
#define ANSI_PC_NUM_BITS  24

#define ITU_T_14_BIT_PC_MASK  0x3fff
#define JAPANESE_16_BIT_PC_MASK  0xffff
#define ANSI_24_BIT_PC_MASK   0xffffffL

#define GET_PC_SIZE(nw_id)   ITU_T_14_BIT_PC

#define ITU_T_14_BIT_PC_MAX_VAL 0x3fff
#define ANSI_24_BIT_PC_MAX_VAL  0xffffffL
#define JAPANESE_16_BIT_PC_MAX_VAL  0xffff

/* SPR # 9502 Fix Start */
#define SC_REMOTE_SP   0
#define SC_PRIMARY_SP	1
#define SC_CAPABILITY_SP	2
#define SC_SECONDARY_SP	3
/* SPR # 9502 Fix End */

#endif /* _SC_DBF_H_ */
