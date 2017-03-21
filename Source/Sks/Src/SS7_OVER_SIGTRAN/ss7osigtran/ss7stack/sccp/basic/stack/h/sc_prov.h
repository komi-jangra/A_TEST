/***************************************************************************
**  FILE NAME:
**      sc_prov.h
**
****************************************************************************
**
**  FUNCTION:
**      
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24Feb'04 Hitesh Sharma           -----  Fixed SPR 13263
**  21Nov'03 knaveen           -----  Fixed SPR 13075
**  06Aug2003 Hitesh Sharma            Fixed SPR # 12377,CSR No: 1-755190
**  13MAR2002 Prateek Bidwalkar        Fixed SPR # 8579
**  22MAR2001 Ashish Pathak            Fixed SPR # 4726
**  16Oct2000 Ramu Kandula            Fixed SPR # 4483
**  10Oct2000 Ramu Kandula            Modified for Broadband
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_PROV_H_
#define _SC_PROV_H_

#include "sc_s7gl.h"

typedef struct
{
	U8bit standard;         /* Standard to be followed */
#ifdef DISTRIBUTED_SCCP	
	U8bit dsccp_local_instance_id;
	U8bit num_of_bits_instance_id;
#endif
/* Start Spr 13075 Fix */
/* Start SPR 13263 Fix */
/* Added for init time parameter max Sp */
	U32bit  max_sp;
        U32bit   max_ss;
        U32bit   max_css ;
        U32bit   max_csp ;
/* Stop SPR 13263 Fix */
/* Stop Spr 13075 Fix */
} sc_init_opt_t;

typedef struct
{
	U8bit standard;
	U16bit seg_size;       /* Segmentation parameter */ 
	U8bit nw_type;         /* Broadband or Narrowband */
#ifdef DISTRIBUTED_SCCP	
	U8bit dsccp_local_instance_id;
	U8bit num_of_bits_instance_id;
#endif
} sc_opt_t;

extern sc_opt_t sc_opt;

#define MAX_CONG_CNTR_VAL 8
#define MAX_SCCP_CONG_LEVEL 8
typedef struct
{
	U8bit level;
	U8bit counter;
} sccp_cong_t;

extern sccp_cong_t sccp_cong;

typedef struct
{
	U32bit sp_id;
	U8bit nw_id;
	U32bit pc;
	Boolean local;
	U8bit ssf;
} sc_sp_conf_info_t;

typedef struct
{
	U32bit sp_id;
	Boolean del_ss;
	Boolean del_csp;

} sc_sp_del_info_t;

typedef struct
{
	U32bit ss_id;
	U32bit sp_id;
	U8bit ssn;
} sc_ss_conf_info_t;

typedef struct
{
	U32bit ss_id;
	Boolean del_css;
} sc_ss_del_info_t;

typedef struct
{
	U32bit ss_id;
	U32bit css_id;
} sc_css_info_t;

typedef struct
{
	U32bit ss_id;
	U32bit csp_id;
} sc_csp_info_t;


/* SPR # 8579 Fix Start */
#ifdef SCCP_BROADBAND
#define SCCP_DEFAULT_SEG_SIZE 2560
#else
#define SCCP_DEFAULT_SEG_SIZE 160 
#endif
/* SPR # 8579 Fix End */

#define SCCP_MAX_XUDT_SEG_SIZE 254
#define SCCP_MAX_CO_SEG_SIZE 255  /* SPR # 4483 Fix, SPR 4726 fix  */
 
typedef struct
{
	U32bit min;
	U32bit max;
	U32bit def;
} sc_tim_range_t;

/****************
* Adding the structures and definitions for sccp_prov_trans_func.
* The structure  sccp_prov_trans_info_t will contain all fields that 
* can be needed to provision Translation function [i.e. GTT].
* --Sachin Bhatia
****************/ 

#define SCCP_MAX_RULES_PER_TRANS_FUN 10 
#define SCCP_MAX_ACTIONS_PER_RULE 255
#define SCCP_MAX_GT_DIGITS 255
#define SCCP_MAX_DPCS_PER_GT 255
#define SCCP_MAX_TRANS_FUNS 255
#define SCCP_MAX_MTPSAPS 255
#define SCCP_TRANS_USED 1
#define SCCP_TRANS_UNUSED 0xff
#define SCCP_FF	0xff

typedef U8bit sccp_mtpsap_t ;
typedef U8bit sccp_gti_t ;
typedef U32bit sccp_count_t	;
typedef U32bit sccp_trans_rule_id_t;

typedef struct
{
	Boolean	used;
	U8bit	tt;
	U8bit	np;
	U8bit	nai;
	U8bit	es;
	Boolean	escape_used;
	U8bit	escape_code;
	/* Fix for SPR No: 12377 , CSR No : 1-755190 starts */
	U8bit	array_trans_rules[SCCP_MAX_RULES_PER_TRANS_FUN];
	/* sccp_count_t	array_trans_rules[SCCP_MAX_RULES_PER_TRANS_FUN];*/
	/* Array of indices to translation rules */
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */
}sccp_trans_fun_entry_t;

typedef  struct 
{
	U8bit    operation_code;
	U8bit    min_digits;
	U8bit    max_digits;
	U8bit    skip_digits;
	U8bit    escape_code;
	U8bit    value[SCCP_MAX_GT_DIGITS];   /*  The length of this value is to considered */
}sccp_action_t;


typedef struct
{
	Boolean     used;
	sccp_count_t       no_of_actions;
	sccp_action_t      action_list[SCCP_MAX_ACTIONS_PER_RULE];
} sccp_trans_rule_t;

typedef struct
{
	sccp_count_t      rule_id;
	sccp_trans_rule_t trans_rule;
} sccp_get_trans_rule_t;

/* Structures for sccp_gtt_sm_info function */
typedef struct
{
	sccp_mtpsap_t   mtpsap;
	U32bit          dpc;
	U8bit   	local_remote_flag;
	error_t         *p_ecode;
}sccp_gtt_add_sp_info_t;

typedef struct
{
	sccp_mtpsap_t   mtpsap;
	U32bit          dpc;
	error_t         *p_ecode;
}sccp_gtt_del_sp_info_t;

typedef struct
{
	sccp_mtpsap_t   mtpsap;
	U32bit          dpc;
	U8bit           ssn;
	error_t         *p_ecode;
}sccp_gtt_add_ss_info_t;

typedef struct
{
	sccp_mtpsap_t   mtpsap;
	U32bit          dpc;
	U8bit           ssn;
	error_t         *p_ecode;
}sccp_gtt_del_ss_info_t;

typedef struct
{
	sccp_mtpsap_t   mtpsap;
	error_t         *p_ecode;
}sccp_gtt_add_mtpsap_info_t;

typedef struct
{
	sccp_mtpsap_t   mtpsap;
	error_t         *p_ecode;
}sccp_gtt_del_mtpsap_info_t;

typedef struct
{
	sccp_count_t    *no_of_mtpsaps;
	sccp_mtpsap_t   **mtpsap_list;
	error_t         *p_ecode;
}sccp_gtt_get_mtpsap_info_t;

typedef struct
{
	sccp_gti_t              gti;
	sccp_trans_fun_entry_t  trans_func;
	sccp_count_t            no_of_actions;
	sccp_action_t           action_array[SCCP_MAX_ACTIONS_PER_RULE];
	sccp_trans_rule_id_t    *trans_rule_id;
	error_t                 *p_ecode;
} sccp_gtt_add_trans_rule_info_t;

typedef struct
{
	sccp_gti_t              gti;
	sccp_trans_fun_entry_t  trans_func;
	sccp_trans_rule_id_t    trans_rule_id;
	error_t                 *p_ecode;
} sccp_gtt_del_trans_rule_info_t;

typedef struct
{
	sccp_gti_t              gti;
	sccp_count_t            *no_of_trans_func;
	sccp_trans_fun_entry_t  **fn_list;
	error_t                 *p_ecode;
} sccp_gtt_get_trans_func_list_info_t;

typedef struct
{
	U8bit           table_mask;
	U8bit           value[SCCP_MAX_GT_DIGITS];
	U8bit           ssn;
	sccp_count_t    dpc_count;
	sccp_mtpsap_t   mtpsaps[SCCP_MAX_MTPSAPS];
	U32bit          dpcs[SCCP_MAX_DPCS_PER_GT];
	error_t         *p_ecode;
} sccp_gtt_add_to_dpc_ssn_table_info_t;

typedef struct
{
	U8bit           table_mask;
	U8bit           value[SCCP_MAX_GT_DIGITS];
	error_t         *p_ecode;
} sccp_gtt_del_from_dpc_ssn_table_info_t;

typedef struct
{
	sccp_gti_t              gti;
	sccp_trans_fun_entry_t  trans_func;
	sccp_count_t            *no_of_rules;
	sccp_get_trans_rule_t   **trans_func_list;
	error_t                 *p_ecode;
} sccp_gtt_get_rules_per_trans_func_info_t;


typedef struct
{
	U8bit info_id;
	sccp_gtt_add_sp_info_t*                 sccp_gtt_add_sp_info;
	sccp_gtt_del_sp_info_t*                 sccp_gtt_del_sp_info;
	sccp_gtt_add_ss_info_t*                 sccp_gtt_add_ss_info;
	sccp_gtt_del_ss_info_t*                 sccp_gtt_del_ss_info;
	sccp_gtt_add_mtpsap_info_t*             sccp_gtt_add_mtpsap_info;
	sccp_gtt_del_mtpsap_info_t*             sccp_gtt_del_mtpsap_info;
	sccp_gtt_get_mtpsap_info_t*             sccp_gtt_get_mtpsap_info;
	sccp_gtt_add_trans_rule_info_t*         sccp_gtt_add_trans_rule_info;
	sccp_gtt_del_trans_rule_info_t*         sccp_gtt_del_trans_rule_info;
	sccp_gtt_get_trans_func_list_info_t*    gtt_get_trans_func_list_info;
	sccp_gtt_add_to_dpc_ssn_table_info_t*   gtt_add_to_dpc_ssn_tbl_info;
	sccp_gtt_del_from_dpc_ssn_table_info_t* gtt_del_from_dpc_ssn_tbl_info;
	sccp_gtt_get_rules_per_trans_func_info_t* gtt_get_rules_per_trans_func_info;
} sccp_gtt_sm_info_t;



#endif /* _SC_PROV_H_ */

