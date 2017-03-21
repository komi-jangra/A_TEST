/***************************************************************************
**  FILE NAME:
**      sc_portf.h
**
****************************************************************************
**
**  FUNCTION:
**      prototypes for functions to be ported for SCCP
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**  21Aug'98 Praneet Khare            Adding porting func for SCCP conn 
**                                    orient part 
**  31Aug'99 Sudipta pattar           Removed prototype for ss7_rand
**  04Feb'02 Prateek Bidwalkar		  Added code for Multi-threading
**  06Mar'02 Prateek Bidwalkar        Fixed SPR 8573
**  22Jul'02 Suyash Tripathi          Fixed SPR 9302 
**  24Feb'04 Hitesh Sharma            Fixed SPR 13263 
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_PORTF_H_
#define _SC_PORTF_H_

#include "sc_prov.h"
/** SPR# 9302 Start Fix **/ 
#ifdef SCCP_MT_SAFE
#include "sccp_mtlib_port.h"
#endif
/** SPR# 9302 End Fix **/ 

U8bit sccp_assign_sls
	_ARGS_ ((const sccp_addr_t * p_cg_addr,
	         const sccp_addr_t * p_cd_addr,
	         U8bit incom_sls,
	         U8bit proto_class));

/* SPR 11115 Fix Start   -Sabhatia */
/* This function is called from the stack whenever 
   stack initializes */
void sccp_init_complete_indication 
        _ARGS_ ((sc_init_opt_t * p_sc_init_opt ));
/* SPR 11115 Fix End   -Sabhatia */

	/* Fix for SPR No : 13263 start */
return_t sccp_deinit_complete_indication
        _ARGS_ ((void));
	/* Fix for SPR No : 13263 end */


return_t sccp_global_title_translate
	_ARGS_ ((gtt_ip_t * p_gt_input,
	         gtt_op_t * p_gt_output));

void sccp_compute_cong_params
	_ARGS_ ((const sp_entry_t * p_sp, S8bit * p_rl, S8bit * p_rsl, U8bit * p_ril));

void sccp_inform_trans_func
	_ARGS_ ((const sp_entry_t * p_sp, const ss_entry_t * p_ss));

/* SPR 9302 - Fix Start */
#ifndef __FLAG_MEMCPY_FLAG__
#define __FLAG_MEMCPY_FLAG__
/* SPR 9302 - Fix Start */
void sccp_memcpy
        _ARGS_ ((U8bit * s1, U8bit * s2, U32bit size));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */


/* SPR 9302 - Fix Start */
#ifndef __FLAG_MEMMOVE_FLAG__
#define __FLAG_MEMMOVE_FLAG__
/* SPR 9302 - Fix Start */
void sccp_memmove
        _ARGS_ ((U8bit * s1, U8bit * s2, U32bit size));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

Boolean sccp_is_relay_coupling_node
        _ARGS_((sccp_addr_t      *p_sccp_addr,
                sccp_nsdu_org_t  *p_nsdu_org));

#ifdef DISTRIBUTED_SCCP
return_t dsccp_send_to_mate
      _ARGS_((U8bit *p_api, U16bit api_len, 
		U8bit instance_id, error_t *p_ecode));

return_t dsccp_notify_self_status
      _ARGS_((U8bit instance_id, module_id_t));

/* SPR # 8573 Fix Start */
return_t dsccp_comp_mate_info_req
	  _ARGS_((U8bit self_inst_id));
/* SPR # 8573 Fix End */

#endif

/** SPR# 9302 Start Fix **/
#if 0
#ifdef SCCP_MT_SAFE
S32bit ss7_sem_create
    _ARGS_((S32bit key, U32bit initval));

void ss7_sem_rm
    _ARGS_((S32bit *id));

void ss7_sem_lock
    _ARGS_((S32bit  *sem_id));

void ss7_sem_unlock
    _ARGS_((S32bit  *sem_id));

void ss7_sem_incr
    _ARGS_((S32bit  *sem_id));

void ss7_sem_decr
    _ARGS_((S32bit  *sem_id));

void ss7_sem_wait_for_zero
    _ARGS_((S32bit  *sem_id));

return_t ss7_create_thread
    _ARGS_((void *(*p_entry_function)(void *),\
										 void *p_buffer, U32bit *p_thread_id));

#endif /* SCCP_MT_SAFE */
#endif	/* if 0 */
/** SPR# 9302 Start Fix **/


/* Adding sccp_gtt_sm_info function */
/* This function will bw called whenever sccp gets some GTT SM API or a SS / SP is added */

return_t sccp_update_gtt_sm_info
	_ARGS_ ((sccp_gtt_sm_info_t *gtt_sm_info));


#endif
