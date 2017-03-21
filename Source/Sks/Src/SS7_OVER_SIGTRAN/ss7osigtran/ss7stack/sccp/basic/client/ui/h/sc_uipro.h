/*****************************************************************************
**  FUNCTION:
**      Declaration of function prototypes for the SCCP stack entity
*******************************************************************************
**
**  FILE NAME:
**      tc_uipro.h
**  DESCRIPTION:
**      This file contains the function prototypes for TCAP stack entity.
**
**
**         DATE          NAME           REFERENCE         REASON
**         ----          ----           ---------         ------
**
**        07Jun'00    Ramu Kandula                       Changed gen_parse_fn to 
**                                                       sccp_gen_parse_fn
**        20May'00    Ramu Kandula                       Changed len_t to 
**                                                       s7_len_t
**        20Aug'98    Praneet Khare                      Adding Conn Orinted UI
**        13Jan98     GAURAV.TANEJA    HSS:????????      ORIGINAL
**
**
**        Copyright 1998, Hughes Software Systems, Inc.
**
******************************************************************************/

#ifdef ANSI_PROTO
#define        _ARGS_(x)        x
#else
#define        _ARGS_(x)
#endif

return_t sccp_init_su_client
         _ARGS_((U8bit standard)) ;


void xtract_U8bit
        _ARGS_((buffer_t     **p_buffer, 
                elem_val_t   *p_val));

void xtract_U16bit
        _ARGS_((buffer_t    **p_buffer, 
                elem_val_t  *p_val));

void xtract_U24bit
        _ARGS_((buffer_t    **p_buffer, 
                elem_val_t  *p_val));

void xtract_U32bit
        _ARGS_((buffer_t    **p_buffer, 
                elem_val_t  *p_val));

void xtract_vl_elem
        _ARGS_((buffer_t   **p_buffer, 
                elem_val_t *p_val));

void xtract_U8bit_opt
        _ARGS_((buffer_t     **p_buffer, 
                elem_val_t   *p_val));

void xtract_U16bit_opt
        _ARGS_((buffer_t    **p_buffer, 
                elem_val_t  *p_val));

return_t NULL_func
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_local_ss
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_called_addr
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_calling_addr
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_seq_ctrl
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_return_opt
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_credit
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_importance
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_user_status
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_aff_sig_pt
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_aff_ss
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_log_uid
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_corr_id
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_proto_class
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t chk_elem_val_exp_data
        _ARGS_((elem_val_t  *p_val,
                error_t     *p_ecode));

return_t sccp_gen_parse_fn
        _ARGS_((buffer_t  *p_buffer,
             s7_len_t  noctets,
             error_t   *p_ecode)); 

return_t send_to_sccp
        _ARGS_((buffer_t    *p_buffer,
             s7_len_t    noctets,
             src_id_t    src_id,
             dst_id_t    dst_id,
             error_t     *p_ecode));

return_t sccp_dispatch_buffer
        _ARGS_((buffer_t  *p_buffer,
                s7_len_t  noctets,
                src_id_t  src_id,
                dst_id_t  dst_id,
                error_t   *p_ecode));
