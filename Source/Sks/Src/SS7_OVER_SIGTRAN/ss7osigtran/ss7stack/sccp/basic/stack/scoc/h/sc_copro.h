/******************************************************************************
**
**  Prototypes for the SCCP Connection Oriented Part
**
******************************************************************************/

#ifndef _SC_COPRO_H
#define _SC_COPRO_H

#include "sc_stgl.h"

return_t sccp_handle_co_mesg
         _ARGS_((msg_info_t *p_info,
                 error_t    *p_ecode)) ;

void sccp_itu_unassigned_dlr
     	 _ARGS_((msg_info_t      *p_info)) ;
 
void sccp_itu_incorrect_slr
	 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;
 
void sccp_itu_incorrect_opc
     	 _ARGS_((msg_info_t      *p_info)) ;
 
void sccp_ansi_info_mismatch
     	 _ARGS_((msg_info_t      *p_info,
             	 U8bit           error_cause)) ;

void sccp_itu_incorrect_slr_it
	 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

void sccp_init_co_function_table
     _ARGS_((void)) ;

return_t sccp_conn_idle_n_conn_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_req_type_1
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_req_type_2
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_cr
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_rlsd
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_routefail
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_comm_function
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_n_conn_res
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_n_disc_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_cc
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_rlsd_itu
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_rlsd
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_routefail
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_cref
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_t_connest_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_comm_func
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_comm_incoming_ansi
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_start_rlsd_incoming_ansi
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_n_disc_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_n_reset_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_n_data_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_n_expdata_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_rlsd
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_rsr
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_routefail
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_dt1
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_dt2
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_ak
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_ed
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_ea
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_it
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_err
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_t_iar_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_t_ias_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_comm_func_itu
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_comm_func_ansi
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_estab_rsc
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_reset_n_reset_req
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_reset_n_reset_res
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_reset_rlsd
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_reset_rsc
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

/** SPR # 4051 Fix Start **/
return_t sccp_conn_reset_rpe
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;
/** SPR # 4051 Fix End **/

return_t sccp_conn_reset_rsr
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_reset_err
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_reset_t_reset_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_closing_rlc_rlsd_err
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_closing_t_rel_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_closing_t_reprel_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_closing_t_int_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_closing_comm_func
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;


return_t sccp_conn_closed_t_freeze_tmout
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_do_nothing
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;

return_t sccp_conn_idle_comm_func
		 _ARGS_((msg_info_t       *p_info, 
                 error_t          *p_ecode)) ;


/******** Function Protos from sc_coutl.c *********/
#ifdef SCCP_CONNECTION_ID_CHANGES
sccp_ccb_t  *sccp_utl_get_ccb
            _ARGS_((U8bit       c_state, 
                    U16bit      l_id, 
                    U32bit       corr_id)) ;/* Amaresh U16 U32 */
#else
sccp_ccb_t  *sccp_utl_get_ccb
            _ARGS_((U8bit       c_state,
                    U16bit      l_id,
                    U8bit       corr_id)) ;
#endif

#ifdef SCCP_CONNECTION_ID_CHANGES
U32bit sccp_utl_map_lref_cid_motorola
       _ARGS_((U32bit lref));
#endif

sccp_ccb_t   *sccp_utl_get_free_ccb 
             _ARGS_((void)) ;

void sccp_utl_init_ccb
     _ARGS_((sccp_ccb_t    *p_ccb, 
             U8bit         protocol_class)) ;

void sccp_change_state
     _ARGS_((sccp_ccb_t   *p_ccb, 
             U8bit        state, 
             U8bit        substate)) ;

return_t sccp_utl_read_ccb
           _ARGS_((msg_info_t   *p_info)) ;

Boolean   sccp_is_co_msg 
             _ARGS_((U8bit)) ;

void sccp_resume_data_transfer
     _ARGS_((sccp_ccb_t   *p_ccb)) ;

void sccp_free_queue
     _ARGS_((sc_queue_t   *p_queue)) ;

void sccp_free_ccb
     _ARGS_((sccp_ccb_t   *p_ccb)) ;

void sccp_release_resources
     _ARGS_((sccp_ccb_t  *p_ccb)) ;

/* SPR 9302 - Fix Start - suyash  */
/*return_t sccp_do_nothing
         _ARGS_((msg_info_t   *p_info,
                 error_t      *p_ecode)) ;*/
/* SPR 9302 - Fix End  */

U16bit sccp_utl_map_lref_cid
       _ARGS_((U32bit  lref)) ;

void sccp_reset_variables
     _ARGS_((sccp_ccb_t   *p_ccb)) ;

void sccp_remove_association
     _ARGS_((sccp_ccb_t   *p_ccb,
             sccp_ccb_t   *p_coupled_ccb)) ;
#ifdef SCCP_CONNECTION_ID_CHANGES
void sccp_utl_clr_corr_id
     _ARGS_((U16bit   l_uid,
             U32bit    corr_id)) ;/* Amaresh U16 U32 */
#else
void sccp_utl_clr_corr_id
     _ARGS_((U16bit   l_uid,
             U8bit    corr_id)) ;
#endif

/* SPR # 6126 Fix Start */
return_t
sccp_utl_add_ccb_to_hash_tbl
#ifdef SCCP_CONNECTION_ID_CHANGES
  _ARGS_((U32bit ccb_id, U16bit l_id, U32bit corr_id));/* Amaresh U16 U32 */
#else
  _ARGS_((U32bit ccb_id, U16bit l_id, U8bit corr_id));
#endif

void
sccp_utl_del_ccb_from_hash_tbl
#ifdef SCCP_CONNECTION_ID_CHANGES
  _ARGS_((U8bit c_state, U16bit l_id, U32bit corr_id));/* Amaresh U16 U32 */
#else
  _ARGS_((U8bit c_state, U16bit l_id, U8bit corr_id));
#endif
/* SPR # 6126 Fix End */

void sccp_discard_message
     _ARGS_((msg_info_t    *p_info)) ;

U8bit sccp_utl_get_mtp_nw_id
      _ARGS_((U16bit    l_uid)) ;

void sccp_utl_fill_nw_info
	_ARGS_((msg_info_t *p_info,
			sccp_ccb_t *p_ccb));

return_t sccp_stop_co_timer
	_ARGS_((sccp_ccb_t *p_ccb,
			U8bit timer_name,
			error_t *p_ecode));

return_t sccp_start_co_timer
	_ARGS_((sccp_ccb_t *p_ccb,
			U8bit timer_name,
			error_t *p_ecode));

return_t sccp_restart_co_timer
	_ARGS_((sccp_ccb_t *p_ccb,
			U8bit timer_name,
			error_t *p_ecode));

return_t sccp_utl_fwd_dt2
	_ARGS_((msg_info_t    *p_info,
			sccp_ccb_t    *p_ccb));

return_t sccp_handle_reassembly
	_ARGS_((msg_info_t    *p_info,
			sccp_ccb_t    *p_ccb));

void sccp_utl_reset_conn
	_ARGS_((msg_info_t *p_info));

return_t sccp_utl_add_to_tx_queue
	_ARGS_((msg_info_t    *p_info,
			sccp_ccb_t    *p_ccb));

return_t sccp_utl_add_to_rx_queue
	_ARGS_((msg_info_t    *p_info,
			sccp_ccb_t     *p_ccb));

void sccp_utl_get_sp_from_logid
     _ARGS_((msg_info_t *p_info,
             U16bit     l_id));

U8bit sccp_utl_get_rlsd_originator
      _ARGS_((U8bit        reason)) ;

U8bit sccp_utl_get_cref_originator
      _ARGS_((U8bit        reason)) ;

U8bit sccp_utl_get_rsr_originator
      _ARGS_((U8bit        reason)) ;

return_t sccp_utl_check_slr
      _ARGS_((msg_info_t   *p_info)) ;

return_t sccp_utl_check_opc
      _ARGS_((msg_info_t   *p_info)) ;

return_t is_slr_present
      _ARGS_((U8bit   event)) ;

return_t sccp_utl_fwd_ed
	_ARGS_((msg_info_t    *p_info,
			sccp_ccb_t    *p_ccb, 
			error_t *p_ecode));

return_t sccp_utl_add_to_ed_tx_queue
	_ARGS_((msg_info_t    *p_info,
			sccp_ccb_t    *p_ccb));

/* SPR # 6126 Fix Start */
#ifdef SCCP_CONNECTION_ID_CHANGES
U16bit  sccp_utl_get_hash_index
        _ARGS_((U16bit log_id,
                U32bit corr_id)); /* Amaresh U16 U32 */
#else
U16bit  sccp_utl_get_hash_index
        _ARGS_((U16bit log_id,
                U8bit corr_id));
#endif
/* SPR # 6126 Fix End */


/********** Timer Related Function ****************/

/* SPR 9302 - Fix Start - suyash */
/* These functions are already declared above
return_t sccp_start_co_timer
         _ARGS_((sccp_ccb_t       *p_ccb,
                 U8bit            timer_name,
                 error_t          *p_ecode)) ;

return_t sccp_stop_co_timer
         _ARGS_((sccp_ccb_t       *p_ccb,
                 U8bit            timer_name,
                 error_t          *p_ecode)) ;*/
/* SPR 9302 - Fix End   */

/********** Connection Oriented Message Building Fucntions ***********/
/********** from sc_cobld.c ******************************************/

U8bit * sccp_encode_optional_ie
      _ARGS_((U8bit       *p_elem, 
              U8bit       param_id, 
              U16bit      param_len, 
              U8bit       *p_param)) ;

void sccp_build_n_connect_ind_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_connect_conf_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_connect_reply_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_data_ind_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_expediate_data_ind_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_reset_ind_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_reset_conf_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

void sccp_build_n_disconnect_ind_api
     _ARGS_((msg_info_t   *p_info, 
             sccp_ccb_t   *p_ccb)) ;

/********** Connection Oriented Message Building Fucntions ***********/
/********** from sc_cobld.c ******************************************/

return_t sccp_parse_n_connect_request_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_connect_response_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_conn_req_type1_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_conn_req_type2_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_data_request_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_ed_data_request_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_reset_request_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_reset_resp_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_disconnect_request_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

return_t sccp_parse_n_inform_request_api
         _ARGS_((U8bit       *p_api,
                 msg_info_t  *p_info));

#ifdef DISTRIBUTED_SCCP
return_t dsccp_build_and_send_disc_req_to_mate
            _ARGS_((U8bit *p_api,
                  error_t *p_ecode));
#endif

#endif
