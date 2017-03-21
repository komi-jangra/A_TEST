/***************************************************************************
**  FILE NAME:
**      dsccp_proc.h
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION: This file contains the prototyopes of functions defined for DSCCP
**
**
**  DATE     NAME              REF#     REASON
**  -------  ----------------  -----    -------------------------------------
**  21May'2002 Salil K Agrawal   ----    Fixed SPR # 8744
**  22Jan'2002 Prateek Bidwalkar ----    Fixed SPR # 7470
**  26dec'2001 Prateek Bidwalkar ----    Fixed SPR # 7450
**  25Feb'2002 Sachin Bhatia 	----   	   Deregistration Prototypes	 
**  26aug'2001 Pawanish Kumar Modi ----    Original
**
**  Copyright 2001, Hughes Software Systems
***************************************************************************/

#ifndef _DSCCP_PROC_H_
#define _DSCCP_PROC_H_

#ifdef DISTRIBUTED_SCCP

#include "sc_stgl.h"
#include "sc_sref.h"


return_t dsccp_handle_conf_request_msg
		_ARGS_((dsccp_instance_id_t, error_t *));

return_t dsccp_build_and_send_sp_conf_info
		_ARGS_((dsccp_instance_id_t, error_t *));

return_t dsccp_build_and_send_ss_conf_info
		_ARGS_((dsccp_instance_id_t, error_t *));

return_t dsccp_build_and_send_reg_conf_info
		_ARGS_((dsccp_instance_id_t, error_t *));

return_t dsccp_send_conf_request_to_mate
		_ARGS_((error_t *));

void dsccp_build_conf_status_request_api
		_ARGS_((U8bit *p_api, 
			U16bit api_len));

void dsccp_handle_config_sp_info
		_ARGS_((U8bit *, error_t *));

void dsccp_handle_config_ss_info
		_ARGS_((U8bit *, error_t *));

void dsccp_handle_config_reg_info
		_ARGS_((U8bit *, error_t *));

return_t dsccp_build_and_send_instance_status_conf_info
		_ARGS_((dsccp_instance_id_t, error_t *));

return_t dsccp_handle_config_end
		_ARGS_((U8bit *, error_t *));

return_t dsccp_handle_conf_timeout
		_ARGS_((U8bit *, error_t *));

void dsccp_handle_mate_status_change
		_ARGS_((U8bit *));

return_t dsccp_handle_comp_mate_status_info
		_ARGS_((U8bit *, error_t *));

return_t dsccp_i_am_manager
		_ARGS_((void));

return_t dsccp_broadcast_to_mates
		_ARGS_((U8bit *, 
			U16bit ,
			error_t *));

return_t dsccp_forced_broadcast_to_mates
		_ARGS_((U8bit *, 
			U16bit ,
			error_t *));

return_t dsccp_process_mesg
		_ARGS_((U8bit *, error_t *));

void dsccp_scmg_handle_sp_status
		_ARGS_((U8bit *));

void dsccp_scmg_handle_ss_status
		_ARGS_((U8bit *));

void dsccp_scmg_handle_reg_status
		_ARGS_((U8bit *));

void dsccp_scmg_handle_dereg_status
		_ARGS_((U8bit *));


void sccp_send_sp_status_to_mate
      _ARGS_((sp_entry_t *));

void sccp_send_ss_status_to_mate
      _ARGS_((ss_entry_t *));

void sccp_build_sp_status_message
      _ARGS_((U8bit *p_api, sp_entry_t *p_sp, U16bit api_len));

void sccp_build_ss_status_message
      _ARGS_((U8bit *p_api, ss_entry_t *p_ss, U16bit api_len));


return_t dsccp_handle_mate_n_disc_req
		_ARGS_((U8bit *, error_t *));
return_t dsccp_process_sclc_cat_msg
		_ARGS_((U8bit *));

return_t dsccp_process_reass_info_req
		_ARGS_((U8bit *));

return_t dsccp_process_reass_info_resp
		_ARGS_((U8bit *));

return_t dsccp_process_xudt_from_mate
		_ARGS_((U8bit *));

return_t dsccp_process_t_reass_query_timer_expiry
		_ARGS_((U8bit *));

return_t dsccp_process_xudt_from_nw
		_ARGS_((msg_info_t * p_info,
      		struct seg_ref *p_seg_ref));

void dsccp_build_reass_info_req
		_ARGS_((U8bit *p_buf,
      		struct seg_ref *p_seg_ref));

void dsccp_build_and_send_reass_info_resp
		_ARGS_(( U8bit dest_inst_id,
      		U32bit src_seg_ref));

void dsccp_build_and_send_xudt_to_mate
		_ARGS_((U8bit dest_inst_id,
      		U8bit *p_api));

void dsccp_build_and_send_all_buffered_xudt
		_ARGS_((U8bit dest_inst_id,
      		struct seg_ref *p_seg_ref));

void dsccp_bcast_reass_info_req_to_all
	_ARGS_((struct seg_ref *p_seg_ref));

void dsccp_buffer_class1_messages
	_ARGS_((U8bit *p_api));

return_t dsccp_handle_t_class1_buffer_timer_expiry
	_ARGS_((U8bit *p_api, error_t *p_ecode));

void dsccp_scmg_handle_scmg_status
	_ARGS_((U8bit *p_api));

void dsccp_send_scmg_status_to_mate
      _ARGS_((sp_entry_t *p_sp));

/* spr #8744 starts here */
void dsccp_scmg_handle_cong_status(U8bit *);
void dsccp_send_cong_status_to_mate(void);
void dsccp_build_cong_status_api(U8bit *,U16bit);
/* spr #8744 ends here */

/* SPR # 7450 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
return_t dsccp_handle_instance_deactivation
	 _ARGS_((dsccp_instance_id_t inst_id, error_t *p_ecode));

return_t dsccp_handle_inst_deactivation_timer_expiry
	 _ARGS_((U8bit *p_api, error_t *p_ecode));

void dsccp_change_deactivated_inst_status
	_ARGS_((dsccp_instance_id_t inst_id));

return_t dsccp_broadcast_deactivation_timer_expiry
	_ARGS_((dsccp_instance_id_t inst_id, error_t *p_ecode));

return_t dsccp_handle_deactivated_mate_status
	_ARGS_((U8bit *p_api, error_t *p_ecode));

return_t dsccp_update_umr_and_dmr
    _ARGS_((dsccp_instance_id_t inst_id, error_t *p_ecode));

#endif
/* SPR # 7450 Fix End */

/* SPR # 7470 Fix Start */
return_t dsccp_handle_cls1_buf_inh_timer_expiry
	_ARGS_((U8bit *p_api, error_t *p_ecode));

return_t dsccp_store_class1_messages
	_ARGS_((U8bit *p_api));
/* SPR # 7470 Fix End */

#endif /* DISTRIBUTED_SCCP */

#endif /* _DSCCP_PROC_H_ */
