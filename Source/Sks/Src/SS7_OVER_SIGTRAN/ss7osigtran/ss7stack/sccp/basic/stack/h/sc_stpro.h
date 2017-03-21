/***************************************************************************
**  FILE NAME:
**      sc_stpro.h
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
**  24Feb04   Hitesh Sharma		  Fixed SPR 13263
**  13Mar03   Ashish Sawalkar		  Fixed SPR 11500
**  22Jul02   Suyash Tripathi         SPR 9302 - Warning Removal 
**  21Jun02   Salil Agrawal           Added register resp functionality 
**  13Mar02	  Sachin Bhatia		  	  Added Init functionality
**  12Mar02	  Sachin Bhatia		  	  Added DeInit functionality
**  06Mar02	  Sachin Bhatia		  	  Added Deregn functionality
**  19Dec01	  Ashish Sawalkar		  Fixed SPR 7490
**  4Feb02	  Prateek Bidwalkar       Added code for multi-threading
**  22Oct01	  Prateek Bidwalkar		  Fixed SPR 6566
**  04Nov'00  Arun Kumar       -----  Adding TRAFFIC Statistics
**  03Nov'00  Vikas                   SPR4524
**  20May'00 Ramu Kandula             Changed len_t to s7_len_t
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/


#ifndef _SC_STPRO_H_
#define _SC_STPRO_H_

#include "sc_stgl.h"
#include "sc_sref.h"


/* SPR 9302 - Fix Start */ 
#ifndef __FLAG_MEMCPY_FLAG__
#define __FLAG_MEMCPY_FLAG__
/* SPR 9302 - Fix End   */ 
void sccp_memcpy
	_ARGS_ ((U8bit * s1, U8bit * s2, U32bit size));
/* SPR 9302 - Fix Start */ 
#endif

#ifndef __FLAG_MEMMOVE_FLAG__
#define __FLAG_MEMMOVE_FLAG__
/* SPR 9302 - Fix End   */ 
void sccp_memmove
	_ARGS_ ((U8bit * s1, U8bit * s2, U32bit size));
/* SPR 9302 - Fix Start */ 
#endif
/* SPR 9302 - Fix End   */ 


U8bit * sccp_malloc
	_ARGS_ ((U32bit size));

void sccp_free
	_ARGS_ ((U8bit * p_buf));

return_t sccp_start_timer
	_ARGS_ ((U32bit timer_val, U8bit * p_timer_buf,
	             U32bit timer_buf_len, timer_id_t * p_timer_id));

void sccp_stop_timer
	_ARGS_ ((timer_id_t * timer_id));

void sccp_sendto_tc
	_ARGS_ ((U8bit * p_api, ss_entry_t * p_ss));

void sccp_sendto_m3
	_ARGS_ ((U8bit * p_api));

void sccp_sendto_sm
	_ARGS_ ((U8bit * p_api));

void sccp_sendto_rm
	_ARGS_ ((U8bit * p_api));

void sccp_fill_api_header
	_ARGS_ ((U8bit * p_api, U8bit api_id, U8bit num_elem,
                     U16bit api_len));

/* Module db */

/* File sc_dbini.c */

return_t sccp_db_init
	_ARGS_ ((void));

/* File sc_dbadd.c */

return_t sccp_db_conf_sp
	_ARGS_ ((db_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode));

return_t sccp_db_conf_ss
	_ARGS_ ((db_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode));

return_t sccp_db_conf_css
	_ARGS_ ((db_css_info_t * p_css_conf_info, error_t * p_ecode));

return_t sccp_db_conf_csp
	_ARGS_ ((db_csp_info_t * p_csp_conf_info, error_t * p_ecode));

/* File sc_dbdel.c */

return_t sccp_db_del_sp
	_ARGS_ ((U32bit sp_id, Boolean del_ss, Boolean del_csp,
	             error_t * p_ecode));

return_t sccp_db_del_ss
	_ARGS_ ((U32bit ss_id, Boolean del_css, error_t * p_ecode));

return_t sccp_db_del_css
	_ARGS_ ((db_css_info_t * p_css_del_info, error_t * p_ecode));

return_t sccp_db_del_csp
	_ARGS_ ((db_csp_info_t * p_csp_del_info, error_t * p_ecode));

/* File sc_dbloc.c */

sp_entry_t * sccp_db_find_sp
	_ARGS_ ((nw_id_t nw_id, pc_t pc));

ss_entry_t * sccp_db_find_ss
	_ARGS_ ((sp_entry_t * p_sp, U8bit ssn));

ss_entry_t * sccp_db_find_ss_linear
	_ARGS_ ((sp_entry_t * p_sp, U8bit ssn));

return_t sccp_db_find_sp_from_id
	_ARGS_ ((U32bit sp_id, sp_entry_t ** p_sp, error_t * p_ecode));

return_t sccp_db_find_ss_from_id
	_ARGS_ ((U32bit ss_id, ss_entry_t ** p_p_ss, error_t * p_ecode));

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
U32bit sccp_db_find_cluster_list
        _ARGS_ ((scmg_info_t * p_info, sp_id_t * p_sp_list));
#endif


/* File sc_dbmsc.c */

return_t sccp_db_check_pc
	_ARGS_ ((U32bit pc, error_t * p_ecode));

void sccp_db_insert_ss_in_sp
	_ARGS_ ((ss_entry_t * p_ss, sp_entry_t * p_sp));

void sccp_db_del_ss_from_sp
	_ARGS_ ((ss_entry_t * p_ss));

Boolean sccp_db_is_ss_conc
	_ARGS_ ((ss_entry_t * p_css));

Boolean sccp_db_is_sp_conc
	_ARGS_ ((sp_entry_t * p_sp));

void sccp_db_del_all_ss_as_css
	_ARGS_ ((ss_entry_t * p_css));

void sccp_db_del_all_sp_as_csp
	_ARGS_ ((sp_entry_t * p_sp));

ss_entry_t * sccp_db_get_css_from_list
	_ARGS_ ((U8bit * p_byte));

void sccp_db_del_all_ss_of_sp
	_ARGS_ ((sp_entry_t * p_sp));

sp_entry_t * sccp_db_get_csp_from_list
	_ARGS_ ((U8bit * p_byte));

void sccp_db_insert_css
	_ARGS_ ((ss_entry_t * p_ss, ss_entry_t * p_css));

void sccp_db_insert_csp
	_ARGS_ ((ss_entry_t * p_ss, sp_entry_t * p_csp));

/* File sc_dbhsh.c */

void sccp_db_init_hash_table
	_ARGS_ ((void));

void sccp_db_insert_sp_hash_list
	_ARGS_ ((sp_entry_t * p_sp));

void sccp_db_delete_sp_hash_list
	_ARGS_ ((sp_entry_t * p_sp));

sp_entry_t * sccp_db_locate_sp_hash_list
	_ARGS_ ((nw_id_t nw_id, pc_t pc));

U32bit sccp_db_get_hash_key
	_ARGS_ ((U8bit nw_id, pc_t pc));

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
U32bit sccp_db_locate_cluster_hash_list
        _ARGS_ ((scmg_info_t * p_info, sp_id_t * p_sp_list));
#endif


/* Module init */

/* File sc_main.c */

#ifdef SCCP_MT_SAFE
void 	 sccp_process_mesg
#else
return_t sccp_process_mesg
#endif
	_ARGS_ ((pvoid p_msg));
void sccp_t_coord_timeout
      _ARGS_ ((U8bit * p_api)); 

/** SPR# 9302 Start Fix **/
#ifndef __IGNORE_SST_TMOUT_FLAG__
#define __IGNORE_SST_TMOUT_FLAG__
void sccp_t_ignore_sst_timeout
    _ARGS_ ((U8bit * p_api)); 
#endif
/** SPR# 9302 End Fix **/

void sccp_n_coord_request
      _ARGS_ ((U8bit * p_api)); 
void sccp_n_coord_response
       _ARGS_ ((U8bit * p_api)); 
/* start added during CC compilation */
/* the sccp_t_coord_timeout,sccp_t_ignore_sst_timeout,sccp_n_coord_request,sccp_n_coord_response function be prototype .*/
/* end added during CC compilation */


/* File sc_sys.c */

void sccp_set_src_id
	_ARGS_ ((src_id_t src_id));

void sccp_set_module_id
	_ARGS_ ((module_id_t module_id));

/* SPR 9302 - Fix Start */
#ifndef __FLAG_SCCP_SM_CMD_STD_RESP_FLAG__
#define __FLAG_SCCP_SM_CMD_STD_RESP_FLAG__
/* SPR 9302 - Fix End   */
void sccp_sm_cmd_std_resp
	_ARGS_ ((U8bit * p_api, return_t ret_val, U8bit param,
	             Boolean put_param, error_t ecode));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

/* File sc_prov.c */

return_t sccp_prov_add_sp
	_ARGS_ ((sc_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode));

return_t sccp_prov_del_sp
	_ARGS_ ((sc_sp_del_info_t * p_sp_del_info, error_t * p_ecode));

return_t sccp_prov_add_ss
	_ARGS_ ((sc_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode));

return_t sccp_prov_del_ss
	_ARGS_ ((sc_ss_del_info_t * p_ss_del_info, error_t * p_ecode));

return_t sccp_prov_add_css
	_ARGS_ ((sc_css_info_t * p_css_info, error_t * p_ecode));

return_t sccp_prov_del_css
	_ARGS_ ((sc_css_info_t * p_css_info, error_t * p_ecode));

return_t sccp_prov_add_csp
	_ARGS_ ((sc_csp_info_t * p_csp_info, error_t * p_ecode));

return_t sccp_prov_del_csp
	_ARGS_ ((sc_csp_info_t * p_csp_info, error_t * p_ecode));

return_t sccp_prov_get_timer_info
	_ARGS_ ((pvoid *p_p_buf, U8bit *p_num_entries, U8bit *p_entry_size, error_t *p_ecode));
	/* fix for SPR No : 13263 start */

return_t sccp_prov_get_sp_info
	_ARGS_ ((pvoid *p_p_buf, U32bit *p_num_entries, U8bit *p_entry_size, error_t *p_ecode));

return_t sccp_prov_get_ss_info
	_ARGS_ ((pvoid *p_p_buf, U32bit *p_num_entries, U8bit *p_entry_size, error_t *p_ecode));

return_t sccp_prov_get_css_info
	_ARGS_ ((ss_id_t ss_id, 
			pvoid *p_p_buf, U32bit *p_num_entries, U8bit *p_entry_size, 
			error_t *p_ecode));

return_t sccp_prov_get_csp_info
	_ARGS_ ((ss_id_t ss_id, 
			pvoid *p_p_buf, U32bit *p_num_entries, U8bit *p_entry_size, 
			error_t *p_ecode));
	/* fix for SPR No : 13263 end */

/* New APIS added for trans function abstraction  --Sachin Bhatia*/
return_t sccp_prov_add_mtpsap
	_ARGS_ ((sccp_mtpsap_t mtpsap, error_t *p_ecode));

/* Note : We do not have add SP and SS as SCCP direstly uses them already */

return_t sccp_prov_del_mtpsap
	_ARGS_ ((sccp_mtpsap_t mtpsap, 
		error_t *p_ecode));

return_t sccp_prov_add_trans_rule
	_ARGS_ ((sccp_gti_t 	gti,
		sccp_trans_fun_entry_t trans_func, 
		sccp_count_t no_of_actions, 
		sccp_action_t action_array[], 
		sccp_trans_rule_id_t *trans_rule_id,  
		error_t *p_ecode));

return_t sccp_prov_del_trans_rule
	_ARGS_ ((sccp_gti_t gti,
		sccp_trans_fun_entry_t trans_func,
		sccp_trans_rule_id_t trans_rule_id,
		error_t *p_ecode));

return_t sccp_prov_add_to_dpc_ssn_table
	_ARGS_ ((U8bit	table_mask,
		U8bit 	value[],
		U8bit 	ssn,
		sccp_count_t	dpc_count,
		sccp_mtpsap_t mtpsaps[],
		U32bit	dpcs[],	
		error_t *p_ecode));

return_t sccp_prov_del_from_dpc_ssn_table
	_ARGS_ ((U8bit table_mask,
		U8bit value [],	
		error_t *p_ecode));

return_t sccp_prov_get_mtpsap_list
	_ARGS_ ((sccp_count_t	*no_of_mtpsaps,
		sccp_mtpsap_t 	**mtpsap_list,
		error_t 	*p_ecode));

return_t sccp_prov_get_trans_func_list
	_ARGS_ ((sccp_gti_t	gti,
		sccp_count_t 	*no_of_trans_func, 
		sccp_trans_fun_entry_t **fn_list, 
		error_t 	*p_ecode));


return_t sccp_prov_get_rules_per_trans_func
	_ARGS_ ((sccp_gti_t	gti,
		sccp_trans_fun_entry_t trans_func, 
		sccp_count_t	*no_of_rules,
		sccp_get_trans_rule_t **trans_func_list,
		error_t 	*p_ecode));

/* End of new trans prov functions */

return_t sccp_handle_sm_activate_instance 
      _ARGS_(( error_t *p_ecode));


void sccp_init_sp
	_ARGS_ ((sp_entry_t * p_sp));

void sccp_stop_ss
	_ARGS_ ((ss_entry_t * p_ss));

void sccp_stop_sp
	_ARGS_ ((sp_entry_t * p_sp));

void sccp_stop_sp_timers
	_ARGS_ ((sp_entry_t * p_sp));

void sccp_stop_ss_timers
	_ARGS_ ((ss_entry_t * p_ss));

void sccp_init_ss
	_ARGS_ ((ss_entry_t * p_ss));

void sccp_prov_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));


/* File sc_ctrl.c */

void sccp_ctrl_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));

/* SPR 9302 - Fix Start */
/* Already declared above */
/*return_t sccp_handle_sm_activate_instance
	_ARGS_ ((error_t *p_ecode));*/
/* SPR 9302 - Fix End   */


return_t sccp_handle_sm_init_instance
	_ARGS_ ((U8bit * p_api, error_t *p_ecode));

return_t sccp_handle_sm_deinit_instance
	_ARGS_ ((error_t *p_ecode));

void
sccp_ctrl_sm_cmd_resp
	_ARGS_ ((U8bit   *p_api, 
	return_t   ret_val,
	U8bit      param,
	Boolean    put_param,
	error_t    ecode));


/* File sc_init.c */

return_t sccp_init
	_ARGS_ ((sc_init_opt_t * p_sc_init_opt, error_t * p_ecode));

return_t sccp_deinit
	_ARGS_ ((error_t * p_ecode));

return_t sccp_handle_t_deinit_timeout
	_ARGS_ ((U8bit * p_api));

return_t sccp_default_init_data
	_ARGS_ ((error_t * p_ecode));

return_t sccp_config_default_timers
	_ARGS_ ((error_t * p_ecode));

return_t sccp_init_timers
	_ARGS_ ((U8bit num_timers, tmr_buffer_t * timers, error_t * p_ecode));

/** SPR 11500 Start Fix **/
return_t sccp_init_flush_db
        _ARGS_ ((error_t *p_ecode));
/** SPR 11500 End Fix **/


/* Module stats */

/* File sc_stats.c */

void sccp_init_stats_q752
        _ARGS_ ((void));

/* SPR# 4543 Start */
void sccp_init_stats_traffic
        _ARGS_ ((void));
/* SPR# 4543 End */
void sccp_init_stats_internal
        _ARGS_ ((void));

void sccp_get_stats_q752
        _ARGS_ ((pvoid p_stat_ptr));

/* SPR# 4543 Start */
void sccp_get_stats_traffic
        _ARGS_ ((pvoid p_stat_ptr));
/* SPR# 4543 End */
void sccp_get_stats_internal
	_ARGS_ ((pvoid p_stats));

void sccp_stat_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));

void sccp_retrieve_stats
	_ARGS_ ((U8bit * p_api));

/* Module errp */

/* File sc_err.c */

/* SPR 9302 - Fix Start */
#ifndef __FLAG_SCCP_ERR_HANDLER_FLAG__
#define __FLAG_SCCP_ERR_HANDLER_FLAG__
/* SPR 9302 - Fix End   */
void sccp_err_handler
	_ARGS_ ((error_t error, U32bit error_type, U8bit error_level));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

void sccp_err_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));

void sccp_report_event_to_sm
	_ARGS_ ((U16bit object_id, U16bit state, sp_entry_t *p_sp, 
		ss_entry_t *p_ss, conn_entry_t *p_conn));

return_t sccp_get_event_reporting
        _ARGS_ ((U16bit object_id, U8bit *p_current_level, error_t *p_ecode));

return_t sccp_set_event_reporting
        _ARGS_ ((U16bit object_id, U8bit p_current_level, error_t *p_ecode));


/* Module scmg */

/* File sc_spmg.c */

void sccp_m3_pause_ind
	_ARGS_ ((U8bit * p_api));

void sccp_m3_resume_ind
	_ARGS_ ((U8bit * p_api));

void sccp_m3_status_ind
	_ARGS_ ((U8bit * p_api));

void sccp_scmg_spac_bcast
	_ARGS_ ((sp_entry_t * p_sp, Boolean resume_recvd));

void sccp_handle_ta_timeout
	_ARGS_ ((U8bit * p_api));

void sccp_handle_td_timeout
	_ARGS_ ((U8bit * p_api));

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
void sccp_m3_pause_cluster_ind
        _ARGS_ ((U8bit * p_api));

void sccp_m3_resume_cluster_ind
        _ARGS_ ((U8bit * p_api));
#endif

/* File sc_ssmg.c */

void sccp_msg_unavail_system
	_ARGS_ ((msg_info_t * p_info));

void sccp_n_state_req
	_ARGS_ ((U8bit * p_api));

void sccp_handle_ssp
	_ARGS_ ((scmg_info_t * p_info));

void sccp_handle_ssa
	_ARGS_ ((scmg_info_t * p_info));

/* File sc_mgbld.c */

void sccp_send_n_state_ind
	_ARGS_ ((ss_entry_t * p_ss, ss_entry_t * p_css));

void sccp_send_n_pcstate_ind
	_ARGS_ ((sp_entry_t * p_ss, ss_entry_t * p_css, U8bit bcast_type));

U8bit * sccp_put_affected_sp_elem
        _ARGS_ ((U8bit * p_elem, sp_entry_t * p_sp));

U8bit * sccp_put_affected_ss_elem
        _ARGS_ ((U8bit * p_elem, ss_entry_t * p_ss));


/* file sc_mgprs.c */

return_t sccp_parse_n_state_req_api
	_ARGS_ ((U8bit * p_api, scmg_info_t * p_info));

return_t sccp_parse_m3_pause_ind_api
	_ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));

return_t sccp_parse_m3_resume_ind_api
	_ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));

return_t sccp_parse_m3_status_ind_api
	_ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));

return_t sccp_parse_sccp_reg_api
	_ARGS_ ((U8bit * p_api, scmg_info_t * p_info));

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
return_t sccp_parse_m3_pause_cluster_ind_api
        _ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));

return_t sccp_parse_m3_resume_cluster_ind_api
        _ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));
#endif



/* File sc_sstc.c */

void sccp_start_sst
	_ARGS_ ((ss_entry_t * p_ss));

void sccp_stop_sst
	_ARGS_ ((ss_entry_t * p_ss));

void sccp_handle_t_stat_info_timeout
	_ARGS_ ((U8bit * p_api));

void sccp_handle_sst
	_ARGS_ ((scmg_info_t * p_info));

/* FIle sc_bcast.c */

void sccp_local_bcast
	_ARGS_ ((sp_entry_t * p_sp, ss_entry_t * p_ss, U8bit bcast_msg_type));

void sccp_broadcast
	_ARGS_ ((scmg_info_t * p_info, U8bit bcast_type));

void sccp_send_ssa_or_ssp
	_ARGS_ ((ss_entry_t * p_ss, sp_entry_t * p_csp, U8bit bcast_type,
						   msg_info_t * p_info));

/* File sc_cong.c */

void sccp_changed_cong_level
	_ARGS_ ((U8bit level));

void sccp_congested_sp_msg_ind
	_ARGS_ ((msg_info_t * p_info));

void sccp_handle_t_con_timeout
	_ARGS_ ((U8bit * p_api));

void sccp_handle_ssc
	_ARGS_ ((scmg_info_t * p_info));

void sccp_process_cong_param
	_ARGS_ ((sp_entry_t * p_sp));

/* file sc_msgh.c */

void sccp_handle_scmg_msg
	_ARGS_ ((msg_info_t * p_info));

/* file sc_reg.c */
/* changes done by salil for register response to user */
/* void sccp_register_user 
	_ARGS_ ((U8bit * p_api));
*/
return_t sccp_register_user
	_ARGS_ ((U8bit * p_api, error_t *p_ecode));

void sccp_register_resp
    _ARGS_ ((U8bit p_api, return_t ret_val, error_t p_ecode));
/* end */
/* added by salil to register sccp-mtp3 */
return_t sccp_mtp3_register_req
	_ARGS_ ((U8bit sio, U32bit log_user_id));
void sccp_deregister_user
	_ARGS_ ((U8bit * p_api));



/* Module scrc */

/* File sc_rout.c */

void sccp_m3_transfer_ind
	_ARGS_ ((U8bit * p_api));

void sccp_route_cl_msg
	_ARGS_ ((msg_info_t * p_info));

void sccp_route_co_msg
	_ARGS_ ((msg_info_t * p_info));

/* File sc_rcprs.c */

return_t sccp_parse_m3_transfer_ind_api
	_ARGS_ ((U8bit * p_api, msg_info_t * p_info, error_t * p_ecode));

return_t sccp_parse_nw_msg
	_ARGS_ ((msg_info_t * p_info));

return_t sccp_parse_dt2
  _ARGS_ ((msg_info_t * p_info));

return_t sccp_decode_sccp_addr
	_ARGS_ ((U8bit * p_addr, sccp_addr_t * p_sc_addr));

/* File sc_rcbld.c */

void sccp_m3_transfer_request
	_ARGS_ ((msg_info_t * p_info));

U8bit * sccp_encode_sccp_addr
	_ARGS_ ((U8bit * p_elem, sccp_addr_t * p_addr));

U8bit sccp_addr_len
	_ARGS_ ((sccp_addr_t * p_addr));

void sccp_copy_sccp_addr
	_ARGS_ ((sccp_addr_t * p_addr1, sccp_addr_t * p_addr2));

/** SPR 9302 Start Fix **/
#if defined(SCCP_ANSI) || defined(SCCP_BCGR) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
extern U8bit sccp_get_min_message_priority
    _ARGS_((U8bit msg_type));
extern U8bit sccp_get_max_message_priority
    _ARGS_((U8bit msg_type));
#endif

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
/** SPR 9302 End Fix **/
extern U8bit sccp_get_min_scmg_message_priority
    _ARGS_((U8bit msg_type));
extern U8bit sccp_get_max_scmg_message_priority
    _ARGS_((U8bit msg_type));
#endif

/* File sc_rcmsc.c */

Boolean sccp_determine_restriction
	_ARGS_ ((msg_info_t * p_info));

void sccp_process_hop_counter
	_ARGS_ ((msg_info_t * p_info));

return_t sccp_translate
	_ARGS_ ((msg_info_t * p_info));

Boolean sccp_perform_compat_test
	_ARGS_ ((msg_info_t * p_info));


/* Module sclc */

/* File sc_lcprs.c */

return_t sccp_parse_n_unitdata_req_api
	_ARGS_ ((U8bit * p_api, msg_info_t * p_info, error_t * p_ecode));

/* File sc_clc.c */

void sccp_n_unitdata_req
	_ARGS_ ((U8bit * p_api));

void sccp_handle_cl_msg	
	_ARGS_ ((msg_info_t * p_info));

/* File sc_lcbld.c */

void sccp_build_n_unitdata_ind_api
	_ARGS_ ((msg_info_t * p_info));

void sccp_build_n_notice_ind_api
	_ARGS_ ((msg_info_t * p_info));

/* file sc_reas.c */

void sccp_reassemble 
	_ARGS_ ((msg_info_t * p_info));

void sccp_handle_reass_failure
      _ARGS_((msg_info_t * p_info,
            struct seg_ref * p_seg_ref,
              U8bit status));

void sccp_handle_t_reassembly_timeout
	_ARGS_ ((U8bit * p_api));

/* file sc_clmsc.c */

void sccp_init_seg_ref_table
	_ARGS_ ((void));

/* file sc_segm.c */

void sccp_handle_changes_needed 
	_ARGS_ ((msg_info_t * p_info));

/*   Added  for SPR4524 */
U16bit sccp_calc_max_y
    _ARGS_ ((msg_info_t * p_info,
             Boolean      segm_needed));


/* file sc_routf.c */

void sccp_handle_routing_failure
	_ARGS_ ((msg_info_t * p_info));

/* module dbg */

/* file sc_debug.c */

/* SPR 9302 - Fix Start */
#ifndef __FLAG_SCCP_DBG_HANDLE_FLAG__
#define __FLAG_SCCP_DBG_HANDLE_FLAG__
/* SPR 9302 - Fix End   */
void sccp_dbg_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

/* Module redn */

/* File sc_redn.c */

/* SPR 9302 -Fix Start - Warning Removal */
/*  protoypes are already present in s7_stpro.h*/

#if 0
return_t sccp_init_redn_data
        _ARGS_((Boolean        event_reporting,
         	error_t*       p_ecode)) ;

return_t sccp_request_active
        _ARGS_((U8bit          type_of_data,
         	pvoid          p_redn_opt,
         	s7_len_t          *p_msg_len,
         	pvoid          p_redn_msg,
			pvoid          *p_p_segment_info, 
         	error_t*       p_ecode)) ;

return_t sccp_receive_update
        _ARGS_((U8bit          type_of_data,
         	s7_len_t          msg_len,
         	pvoid          p_redn_msg,
         	error_t*       p_ecode)) ; 
#endif

/* SPR 9302 - Fix End  */


return_t sccp_redn_send_update
        _ARGS_((U8bit          type_of_data,
         	s7_len_t          msg_len,
         	pvoid          p_redn_msg,
         	error_t*       p_ecode)) ;

return_t sccp_send_ss_entry_update
        _ARGS_((ss_id_t        ss_id));

return_t sccp_send_sp_entry_update
        _ARGS_((sp_id_t        sp_id));

void sccp_redn_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));

/* Module disp */

/* File sc_disp.c */

void sccp_display_handle_sm_cmd
	_ARGS_ ((U8bit * p_api)) ;

return_t sccp_display_module_version
	_ARGS_((module_version_t * version,
         	error_t          * ecode)) ;

/* SPR # 6566 : Fix Start */
return_t sccp_display_ss_status
	_ARGS_((pc_t  	pc,
			U8bit	ssn,
			U8bit	*p_user_status,
			error_t	*p_ecode)) ;
/* SPR # 6566 : Fix End */

/* SPR 7490 : Start Fix */
return_t sccp_display_sp_status
	_ARGS_((pc_t  	pc,
			U8bit	*p_sp_status,
			error_t	*p_ecode)) ;
/* SPR 7490 : End Fix */


#endif /* _SC_STPRO_H_ */
