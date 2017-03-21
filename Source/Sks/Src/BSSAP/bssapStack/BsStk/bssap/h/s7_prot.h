/*******************************************************************************
**      FILE NAME:
**          s7_prot.h
**
**      DESCRIPTION:
**              Contain global type definitions required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _S7_PROT_H_
#define _S7_PROT_H_

#include "s7_typ.h"

/* ss7_bcopy is used because bcopy can clash with some library function */
extern void ss7_bcopy
#ifdef ANSI_PROTO
	(U8bit *,U8bit *,s7_len_t);
#else
	();
#endif
#if 0
extern void bcopyWords
           (char *,char*,s7_len_t); 
#endif

extern return_t ss7_memcpy
#ifdef ANSI_PROTO
       (pvoid dest, pvoid source, s7_len_t len);
#else
       ();
#endif

extern return_t ss7_start_timer
  (U32bit,pvoid,s7_len_t,U8bit,timer_id_t*,error_t*);
extern return_t ss7_stop_timer
  (timer_id_t,error_t*);

#if 0
extern return_t ss7_start_timer
	(U32bit,pvoid,s7_len_t,module_id_t,U8bit,error_t*);

extern return_t ss7_stop_timer
	(timer_id_t,error_t*);
#endif

extern pvoid ss7_mem_get
#ifdef ANSI_PROTO
	(s7_len_t);
#else
	();
#endif

extern return_t ss7_mem_free
#ifdef ANSI_PROTO
	(pvoid);
#else
	();
#endif
        
extern pvoid ss7_mem_zero
#ifdef ANSI_PROTO
	(pvoid , U32bit);
#else
	();
#endif
        
extern return_t ss7_err_handler
#ifdef ANSI_PROTO
	(error_t,module_id_t,pvoid);
#else
	();
#endif

return_t ss7_init_stats
#ifdef ANSI_PROTO
	(module_id_t,stat_type_t,error_t*);
#else
	();
#endif

return_t ss7_get_stats
#ifdef ANSI_PROTO
	(module_id_t,pvoid,stat_type_t,Boolean,error_t*);
#else
	();
#endif

 return_t ss7_disable_stats
#ifdef ANSI_PROTO
	(module_id_t,stat_type_t,error_t*);
#else
	();
#endif

 return_t ss7_enable_stats
#ifdef ANSI_PROTO
	(module_id_t,stat_type_t,error_t*);
#else
	();
#endif

 return_t ss7_get_trace_level
#ifdef ANSI_PROTO
	(module_id_t,U32bit,U8bit*,error_t*);
#else
	();
#endif

 return_t ss7_set_trace_level
#ifdef ANSI_PROTO
	(module_id_t,U32bit,U8bit,error_t*);
#else
	();
#endif

 return_t ss7_get_err_level
#ifdef ANSI_PROTO
	(module_id_t,U32bit,U8bit*,error_t*);
#else
	();
#endif

 return_t ss7_set_err_level
#ifdef ANSI_PROTO
	(module_id_t,U32bit,U8bit,error_t*);
#else
	();
#endif

 U32bit  ss7_rand
#ifdef ANSI_PROTO
	(void);
#else
	();
#endif


extern return_t ss7_get_event_reporting
#ifdef ANSI_PROTO
	(module_id_t,U16bit,U8bit*,error_t*);
#else
	();
#endif

extern return_t ss7_set_event_reporting
#ifdef ANSI_PROTO
	(module_id_t,U16bit,U8bit,error_t*);
#else
	();
#endif

extern void ss7_get_absolute_time 
#ifdef ANSI_PROTO
	(U32bit *);
#else
	();
#endif

extern return_t tcap_dispatch_buffer 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

#ifndef __FLAG_DISPATCH_BUFFER_FLAG__	/* To remove warning */
#define __FLAG_DISPATCH_BUFFER_FLAG__
extern return_t sccp_dispatch_buffer 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
#endif

extern return_t isup_dispatch_buffer 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t mtp3_dispatch_buffer 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif


extern return_t mtp2_dispatch_buffer 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t bisup_dispatch_buffer 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t send_from_tcap 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
extern return_t send_from_sccp 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t send_from_isup 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t send_from_mtp3 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t send_from_mtp2 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t send_from_bisup
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t send_to_tcap 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

/* SPR 5586 fix begins */
/* If send_to_tcap_sm is being used as the SM library function,
 * define its prototype. Otherwise, the above prototype
 * serves both UI and SM lib functions .
 */
#ifdef TCAP_DIFFERENT_SEND_TO_FN
extern return_t TCAP_SEND_TO_TCAP_SM
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
#endif
/* SPR 5586 fix ends */
        
/* SPR 9302 - Fix Start */
#ifndef __FLAG_SENDTOSCCP_FLAG__
#define __FLAG_SENDTOSCCP_FLAG__
/* SPR 9302 - Fix End   */
extern return_t send_to_sccp 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

/* SPR 5586 fix begins */
/* If send_to_sccp_sm is being used as the SM library function,
 * define its prototype. Otherwise, the above prototype
 * serves both UI and SM lib functions .
 */
#ifdef SCCP_DIFFERENT_SEND_TO_FN
extern return_t SCCP_SEND_TO_SCCP_SM
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
#endif
/* SPR 5586 fix ends */                
        
extern return_t send_to_isup 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
        
/* SPR 5586 fix begins */
/* If send_to_isup_sm is being used as the SM library function,
 * define its prototype. Otherwise, the above prototype
 * serves both UI and SM lib functions .
 */
#ifdef ISUP_DIFFERENT_SEND_TO_FN
extern return_t ISUP_SEND_TO_ISUP_SM
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif
#endif
/* SPR 5586 fix ends */
        
extern return_t send_to_mtp3 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

/* SPR 5586 fix begins */
#ifdef MTP3_DIFFERENT_SEND_TO_FN
extern return_t MTP3_SEND_TO_MTP3_SM
#ifdef ANSI_PROTO
        (buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
        ();
#endif
#endif
/* SPR 5586 fix ends */        
        
extern return_t send_to_mtp2 
#ifdef ANSI_PROTO
	(buffer_t *, s7_len_t, src_id_t, dst_id_t, error_t *);
#else
	();
#endif

extern return_t ss7_request_active
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U8bit 		type_of_data, 
	 pvoid 		p_redn_options,
	 s7_len_t 	*p_msg_len,
	 pvoid 		p_redn_msg,
	 pvoid 		*p_p_seg_info,
	 error_t* 	p_ecode);
#else
	();
#endif

extern return_t ss7_receive_update
#ifdef  ANSI_PROTO
	(module_id_t 	module_id,
	 U8bit 		type_of_data, 
	 s7_len_t 		msg_len,
	 pvoid 		p_redn_msg,
 	 error_t* 	p_ecode);
#else
	() ;
#endif

extern return_t ss7_init_redn_data
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 Boolean 	event_reporting,
	 error_t* 	p_ecode);
#else
	() ;
#endif

extern return_t ss7_activate_module
#ifdef ANSI_PROTO
	(module_id_t    module_id,
	 error_t*   p_ecode);
#else
	();
#endif

extern return_t
ss7_redn_build_api
#ifdef ANSI_PROTO
    (module_id_t    module_id,
     U8bit      type_of_data,
     pvoid      p_redn_data,
     s7_len_t   redn_data_len,
     pvoid      *p_redn_api,
     error_t*   p_ecode);
#else
	();
#endif

extern return_t
ss7_send_update
#ifdef ANSI_PROTO
    (module_id_t    module_id,
     U8bit      type_of_data,
     s7_len_t   msg_len,
     pvoid      p_redn_data,
     error_t*   p_ecode);
#else
	();
#endif



#endif  /* end of _S7_PROT_H_ */
