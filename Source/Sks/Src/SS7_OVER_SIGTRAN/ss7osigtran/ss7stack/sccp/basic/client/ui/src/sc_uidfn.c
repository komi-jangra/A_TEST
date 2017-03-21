/******************************************************************************
**
**      FUNCTION:
**          Definition of all the service user API's of the SCCP stack entity. 
**
*******************************************************************************
**
**      FILE NAME:
**          sc_uidfn.c
**      
**      DESCRIPTION:
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**           
**      06Jul'00   Ramu Kandula                           Fixed SPR # 4046
**      30May'00   Ramu Kandula                           Changed len_t to 
**                                                        s7_len_t
**      11Sep'98   Praneet Khare     ------------         Fixing up the Parsing
**                                                      info for conn.response
**      16Aug'98   Praneet Khare     ------------         Adding UI code for 
**                                                        SCCP ConnOriented
**      12Feb98    GAURAV.TANEJA     HSS:????????         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems, Inc.
**
******************************************************************************/

#include "sc_s7gl.h"

#include "sc_error.h"
#include "sc_api.h"

#include "sc_uiprs.h"
#include "sc_uipro.h"

/* generic API element */
elem_val_t    elem_val; 

#if 0 /* This variable is unused */
/* API function pointer table definition */
return_t      (*api_fptr_table[SCCP_MAX_SU_API-SCCP_MIN_SU_API+1])
                              (buffer_t*, s7_len_t, error_t*);
#endif

/* API element_id information initialization */

elem_info_t sc_reg_user_mf[]=
{ {SCCP_ELEM_SSN,
  	0x3,0x3,
		xtract_U24bit,
		chk_local_ss},
	{SCCP_ELEM_LOG_USER_ID,
  	0x2,0x2,
		xtract_U16bit,
		NULL_func}  
};

elem_info_t sc_ansi_reg_user_mf[]=
{ {SCCP_ELEM_SSN,
  	0x4,0x4,
		xtract_U32bit,
		chk_local_ss},
	{SCCP_ELEM_LOG_USER_ID,
  	0x2,0x2,
		xtract_U16bit,
		NULL_func}  
};

elem_info_t sc_n_unitdata_req_mv[]=
{ {SCCP_ELEM_CALLED_ADDR,
  	0x1,0xff,                        /* SPR # 4046 Fix */
		xtract_vl_elem,
		chk_elem_called_addr},
	{SCCP_ELEM_CALLING_ADDR,
  	0x2,0xff,
		xtract_vl_elem,
		chk_elem_calling_addr},
	{SCCP_ELEM_USER_DATA,
		0x0,0xf6f,
		xtract_vl_elem,
		NULL_func}
};

elem_info_t sc_n_unitdata_req_opt[]=
{ {SCCP_ELEM_SEQUENCE_CONTROL,
  	0x1,0x1,
		xtract_U8bit_opt,
		chk_elem_val_seq_ctrl},
	{SCCP_ELEM_RETURN_OPTION,
  	0x1,0x1,
		xtract_U8bit_opt,
		chk_elem_val_return_opt},
	{SCCP_ELEM_IMPORTANCE,
  	0x1,0x1,
		xtract_U8bit_opt,
		chk_elem_val_importance}
};

elem_info_t sc_n_state_req_mf[]=
{ {SCCP_ELEM_AFFECTED_SUBSYSTEM,
  	0x3,0x3,
		xtract_U24bit,
		chk_elem_aff_ss},
  {SCCP_ELEM_USER_STATUS,
  	0x1,0x1,
		xtract_U8bit,
		chk_elem_val_user_status}
};

elem_info_t sc_ansi_n_state_req_mf[]=
{ {SCCP_ELEM_AFFECTED_SUBSYSTEM,
  	0x4,0x4,
		xtract_U32bit,
		chk_elem_aff_ss},
  {SCCP_ELEM_USER_STATUS,
  	0x1,0x1,
		xtract_U8bit,
		chk_elem_val_user_status}
};


#ifdef SCCP_INCLUDE_CO_SERVICE

elem_info_t sc_n_conn_req_mf []=
{ {SCCP_ELEM_LOG_USER_ID,
	 0x02,0x02,
     xtract_U16bit,
     chk_elem_val_log_uid},
  {SCCP_ELEM_CORR_ID,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_corr_id},
  {SCCP_ELEM_PROTOCOL_CLASS,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_proto_class}    
};

elem_info_t sc_n_conn_req_mv []=
{ {SCCP_ELEM_CALLED_ADDR,
  	 0x1,0xff,                    /* SPR # 4046 Fix */
     xtract_vl_elem,
     chk_elem_called_addr}
};

elem_info_t sc_n_conn_req_opt []=
{ {SCCP_ELEM_CREDIT,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_credit},
  {SCCP_ELEM_EXPEDIATE_DATA_SELECTION,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_exp_data},
  {SCCP_ELEM_USER_DATA,
     0x0,0xf6f,
     xtract_vl_elem,
     NULL_func},
  {SCCP_ELEM_IMPORTANCE,
     0x1,0x1,
     xtract_U8bit_opt,
     chk_elem_val_importance}
};

elem_info_t sc_n_conn_res_mf []=
{ {SCCP_ELEM_LOG_USER_ID,
	 0x02,0x02,
     xtract_U16bit,
     chk_elem_val_log_uid},
  {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func},
  {SCCP_ELEM_PROTOCOL_CLASS,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_proto_class}    
} ;

elem_info_t sc_n_conn_res_opt []=
{ {SCCP_ELEM_RESPONDING_ADDR,
  	 0x2,0xff,
     xtract_vl_elem,
     chk_elem_calling_addr},
  {SCCP_ELEM_CREDIT,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_credit},
  {SCCP_ELEM_EXPEDIATE_DATA_SELECTION,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_exp_data},
  {SCCP_ELEM_USER_DATA,
     0x0,0xf6f,
     xtract_vl_elem,
     NULL_func},
  {SCCP_ELEM_IMPORTANCE,
     0x1,0x1,
     xtract_U8bit_opt,
     chk_elem_val_importance}
} ;

elem_info_t sc_n_conn_req_type1_mf []=
{ {SCCP_ELEM_LOG_USER_ID,
	 0x02,0x02,
     xtract_U16bit,
     chk_elem_val_log_uid},
  {SCCP_ELEM_CORR_ID,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_corr_id},
  {SCCP_ELEM_PROTOCOL_CLASS,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_proto_class}    
};

elem_info_t sc_n_conn_req_type1_opt []=
{ {SCCP_ELEM_CREDIT,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_credit},
  {SCCP_ELEM_EXPEDIATE_DATA_SELECTION,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_exp_data}
};

elem_info_t sc_n_conn_req_type2_mf []=
{ {SCCP_ELEM_LOG_USER_ID,
	 0x02,0x02,
     xtract_U16bit,
     chk_elem_val_log_uid},
  {SCCP_ELEM_CORR_ID,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_corr_id},
  {SCCP_ELEM_PROTOCOL_CLASS,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_proto_class},
  {SCCP_ELEM_OPC,
     0x02, 0x02,
     xtract_U16bit,
     NULL_func},
  {SCCP_ELEM_SLR_NUMBER,
     0x03,0x03,
     xtract_U24bit,
     NULL_func}
};

elem_info_t sc_n_conn_req_type2_mf_ansi []=
{ {SCCP_ELEM_LOG_USER_ID,
	 0x02,0x02,
     xtract_U16bit,
     chk_elem_val_log_uid},
  {SCCP_ELEM_CORR_ID,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_corr_id},
  {SCCP_ELEM_PROTOCOL_CLASS,
     0x01,0x01,
     xtract_U8bit,
     chk_elem_val_proto_class},
  {SCCP_ELEM_OPC,
     0x03, 0x03,
     xtract_U24bit,
     NULL_func},
  {SCCP_ELEM_SLR_NUMBER,
     0x03,0x03,
     xtract_U24bit,
     NULL_func}
};


elem_info_t sc_n_conn_req_type2_opt []=
{ {SCCP_ELEM_CREDIT,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_credit},
  {SCCP_ELEM_RPLY_REQ_INDICATOR,
     0x01, 0x01,
     xtract_U8bit_opt,
     NULL_func},
  {SCCP_ELEM_REFUSAL_REASON,
     0x01, 0x01,
     xtract_U8bit_opt,
     NULL_func},
  {SCCP_ELEM_LOG_USER_ID_O,
	 0x02,0x02,
     xtract_U16bit_opt,
     chk_elem_val_log_uid}
};

elem_info_t sc_n_data_req_mf []=
{ {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func}
};

elem_info_t sc_n_data_req_mv []=
{ {SCCP_ELEM_USER_DATA,
     0x0,0xf6f,
     xtract_vl_elem,
     NULL_func}
};

elem_info_t sc_n_data_req_opt []=
{ {SCCP_ELEM_IMPORTANCE,
     0x1,0x1,
     xtract_U8bit_opt,
     chk_elem_val_importance}
};

elem_info_t sc_n_disc_req_mf []=
{ {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func},
  {SCCP_ELEM_DISCONNECT_REASON,
     0x01, 0x01,
     xtract_U8bit,
     NULL_func},
};

elem_info_t sc_n_disc_req_opt []=
{ {SCCP_ELEM_RESPONDING_ADDR,
  	 0x2,0xff,
     xtract_vl_elem,
     chk_elem_calling_addr},
  {SCCP_ELEM_USER_DATA,
     0x0,0xf6f,
     xtract_vl_elem,
     NULL_func},
  {SCCP_ELEM_LOG_USER_ID,
	 0x02,0x02,
     xtract_U16bit_opt,
     chk_elem_val_log_uid},
  {SCCP_ELEM_CORR_ID,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_corr_id},
  {SCCP_ELEM_IMPORTANCE,
     0x1,0x1,
     xtract_U8bit_opt,
     chk_elem_val_importance}
};

elem_info_t sc_n_inform_req_mf []=
{ {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func},
  {SCCP_ELEM_INF_REASON,
     0x01, 0x01,
     xtract_U8bit,
     NULL_func},
};

elem_info_t sc_n_inform_req_opt []=
{  {SCCP_ELEM_PROTOCOL_CLASS,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_proto_class},
  {SCCP_ELEM_CREDIT,
     0x01,0x01,
     xtract_U8bit_opt,
     chk_elem_val_credit}
};

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

elem_info_t sc_n_ed_data_req_mf []=
{ {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func}
};

/* SPR 1771: Data length can be max. 32 octets */
elem_info_t sc_n_ed_data_req_mv []=
{ {SCCP_ELEM_USER_DATA,
     0x0,0x20,
     xtract_vl_elem,
     NULL_func}
};

elem_info_t sc_n_reset_req_mf []=
{ {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func},
  {SCCP_ELEM_RESET_REASON,
     0x01, 0x01,
     xtract_U8bit,
     NULL_func},
};

elem_info_t sc_n_reset_res_mf []=
{ {SCCP_ELEM_CONNECTION_ID,
	 0x02,0x02,
     xtract_U16bit,
     NULL_func}
};

#endif /* SCCP_INCLUDE_CO_CLASS3_SERVICE */

#endif /* SCCP_INCLUDE_CO_SERVICE */

/* API information table definition:indexed on api_id */

#if defined (SCCP_ITU) || defined (SCCP_ETSI)
api_info_t    api_itu_etsi_info_table[SCCP_MAX_SU_API-SCCP_MIN_SU_API+1] = {
  {0xa,0xa,
        0x2,0x2,
		0x2,sc_reg_user_mf,
        0x0,SS7_NULL,
        0x0,SS7_NULL},
  {0x5,0xffff,
        0x3,0x6,
		0x0,SS7_NULL,
        0x3,sc_n_unitdata_req_mv,
        0x3,sc_n_unitdata_req_opt},
#ifdef SCCP_INCLUDE_CO_SERVICE
  {0x9,0x9,
        0x2,0x2,
		0x2,sc_n_state_req_mf,
        0x0,SS7_NULL,
        0x0,SS7_NULL},
  {0x09, 0xffff,
        0x04, 0x08,
        0x03, sc_n_conn_req_mf,
        0x01, sc_n_conn_req_mv,
        0x04, sc_n_conn_req_opt},
  {0x0a, 0xffff,
        0x03, 0x08,
        0x03, sc_n_conn_res_mf,
        0x00, SS7_NULL,
        0x05, sc_n_conn_res_opt},
  {0x09, 0x12,
        0x03, 0x05,
        0x03, sc_n_conn_req_type1_mf,
        0x00, SS7_NULL,
        0x02, sc_n_conn_req_type1_opt},
  {0x0E, 0x21,
        0x05, 0x09,
        0x05, sc_n_conn_req_type2_mf,
        0x00, SS7_NULL,
        0x04, sc_n_conn_req_type2_opt},
  {0x07, 0xffff,
        0x02, 0x03,
        0x01, sc_n_data_req_mf,
        0x01, sc_n_data_req_mv,
        0x01, sc_n_data_req_opt},
  {0x08, 0xffff,
        0x02, 0x07,
        0x02, sc_n_disc_req_mf,
        0x00, SS7_NULL,
        0x05, sc_n_disc_req_opt},
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  {0x08, 0x11,
        0x02, 0x04,
        0x02, sc_n_inform_req_mf,
        0x00, SS7_NULL,
        0x02, sc_n_inform_req_opt},
  {0x07, 0xffff,
        0x02, 0x02,
        0x01, sc_n_ed_data_req_mf,
        0x01, sc_n_ed_data_req_mv,
        0x00, SS7_NULL},
  {0x08, 0x08,
        0x02, 0x02,
        0x02, sc_n_reset_req_mf,
        0x00, SS7_NULL,
        0x00, SS7_NULL},
  {0x07, 0x07,
        0x01, 0x01,
        0x01, sc_n_reset_res_mf,
        0x00, SS7_NULL,
        0x00, SS7_NULL}
#else
  {0x08, 0x11,
        0x02, 0x04,
        0x02, sc_n_inform_req_mf,
        0x00, SS7_NULL,
        0x02, sc_n_inform_req_opt}
#endif
#else
  {0x9,0x9,
        0x2,0x2,
		0x2,sc_n_state_req_mf,
        0x0,SS7_NULL,
        0x0,SS7_NULL}
#endif
};
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
api_info_t    api_ansi_info_table[SCCP_MAX_SU_API-SCCP_MIN_SU_API+1] = {
  {0xb,0xb,
        0x2,0x2,
		0x2,sc_ansi_reg_user_mf,
        0x0,SS7_NULL,
        0x0,SS7_NULL},
  {0x5,0xffff,
        0x3,0x6,
		0x0,SS7_NULL,
        0x3,sc_n_unitdata_req_mv,
        0x3,sc_n_unitdata_req_opt},
#ifdef SCCP_INCLUDE_CO_SERVICE
  {0xa,0xa,
        0x2,0x2,
		0x2,sc_ansi_n_state_req_mf,
        0x0,SS7_NULL,
        0x0,SS7_NULL},
  {0x09, 0xffff,
        0x04, 0x08,
        0x03, sc_n_conn_req_mf,
        0x01, sc_n_conn_req_mv,
        0x04, sc_n_conn_req_opt},
  {0x0a, 0xffff,
        0x03, 0x08,
        0x03, sc_n_conn_res_mf,
        0x00, SS7_NULL,
        0x05, sc_n_conn_res_opt},
  {0x09, 0x12,
        0x03, 0x05,
        0x03, sc_n_conn_req_type1_mf,
        0x00, SS7_NULL,
        0x02, sc_n_conn_req_type1_opt},
  {0x0E, 0x21,
        0x05, 0x09,
        0x05, sc_n_conn_req_type2_mf_ansi,
        0x00, SS7_NULL,
        0x04, sc_n_conn_req_type2_opt},
  {0x07, 0xffff,
        0x02, 0x03,
        0x01, sc_n_data_req_mf,
        0x01, sc_n_data_req_mv,
        0x01, sc_n_data_req_opt},
  {0x08, 0xffff,
        0x02, 0x07,
        0x02, sc_n_disc_req_mf,
        0x00, SS7_NULL,
        0x05, sc_n_disc_req_opt},
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
  {0x08, 0x11,
        0x02, 0x04,
        0x02, sc_n_inform_req_mf,
        0x00, SS7_NULL,
        0x02, sc_n_inform_req_opt},
  {0x07, 0xffff,
        0x02, 0x02,
        0x01, sc_n_ed_data_req_mf,
        0x01, sc_n_ed_data_req_mv,
        0, SS7_NULL},
  {0x08, 0x08,
        0x02, 0x02,
        0x02, sc_n_reset_req_mf,
        0x00, SS7_NULL,
        0x00, SS7_NULL},
  {0x07, 0x07,
        0x01, 0x01,
        0x01, sc_n_reset_res_mf,
        0x00, SS7_NULL,
        0x00, SS7_NULL}
#else
  {0x08, 0x11,
        0x02, 0x04,
        0x02, sc_n_inform_req_mf,
        0x00, SS7_NULL,
        0x02, sc_n_inform_req_opt}
#endif
#else
  {0xa,0xa,
        0x2,0x2,
		0x2,sc_ansi_n_state_req_mf,
        0x0,SS7_NULL,
        0x0,SS7_NULL}
#endif
};
#endif
