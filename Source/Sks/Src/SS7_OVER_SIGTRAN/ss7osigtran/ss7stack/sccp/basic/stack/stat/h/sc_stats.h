/***************************************************************************
**  FILE NAME:
**      sc_stats.h
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
**  08Aug'02 Ashish Sawalkar 	      Fixed SPR # 9525 
**  02Aug'02 Prateek Bidwalkar		  Fixed SPR # 9221
**  04NOV'00 Arun Kumar        -----  Adding TRAFFIC Statistics
**           Sriganesh. Kini   -----  Original
**
**  20Jun'02 Suyash Tripathi  SPR # 8748        changed ssn to ssn-1 
**  Copyright 2000, Hughes Software Systems
***************************************************************************/

#ifndef _SC_STATS_H_
#define _SC_STATS_H_

#include "sc_s7gl.h"

#define MAX_SSN 255

/* DATA TYPE FOR Q.752 PROTOCOL STATISTICS */
typedef struct {
	ss7_event_t	trans_fail_addr_nature;
	ss7_event_t	trans_fail_spec_addr;
	ss7_event_t	pc_unavail;
	ss7_event_t	nw_congestion;
	ss7_event_t	ss_unavail;
	ss7_event_t	ss_congestion;
	ss7_event_t	unequipped_ss;
	ss7_event_t	syntax_error;
	ss7_event_t	routing_fail_reason_unknown;
/* SPR # 9221 Fix Start */
	ss7_event_t t_reass_expired;
	ss7_event_t xudt_seg_out_of_seq;
	ss7_event_t xudt_no_buff_left;
	ss7_event_t hop_count_violation;
	ss7_event_t msg_too_large_for_segmenting;
	ss7_event_t failure_to_rel_conn;
	ss7_event_t sccp_iar_expiry;
	ss7_event_t provider_init_reset;
	ss7_event_t provider_init_rlsd;
	ss7_event_t sccp_seg_failed;
	ss7_event_t sccp_sog_recd;
	ss7_event_t sccp_t_coord_expired;
	count_t 	orig_ludt_xudt_udt [MAX_SSN];
	count_t 	recd_ludt_xudt_udt [MAX_SSN];
/* SPR # 9221 Fix End */
	count_t	orig_msg_class_0 [MAX_SSN];
   	count_t	orig_msg_class_1 [MAX_SSN];
   	count_t	recd_msg_class_0 [MAX_SSN];
   	count_t	recd_msg_class_1 [MAX_SSN];
#ifdef SCCP_INCLUDE_CO_SERVICE
   	count_t	recd_msg_dt1 [MAX_SSN];
	count_t	orig_msg_dt1 [MAX_SSN];
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
   	count_t	recd_msg_dt2 [MAX_SSN];
	count_t	orig_msg_dt2 [MAX_SSN];
   	count_t	recd_msg_ed [MAX_SSN];
	count_t	orig_msg_ed [MAX_SSN];
#endif
#endif
} sccp_stats_proto_q752_t;
     
/* SPR# 4543 Start */
/* DATA TYPE FOR SCCP TRAFFIC RELATED STATISTICS */

typedef struct {
        count_t num_sc_pkt_sent; /* Messages sent successfully to N/W */ 
        count_t num_sc_pkt_recd; /* Messages received successfully by SCCP */
        count_t num_sc_pkt_drop; /* Invalid SC msg received from the TCAP */
        count_t num_sc_pkt_invalid; /* Invalid SC msg received from the N/W */
        count_t num_sc_gtt_tr_fail; /* No of GTT translation failure */
} sccp_stats_traffic_t;

/* SPR# 4543 End */
/**********************************************************************
 * SCCP Statistics handling macros
***********************************************************************/

/* contains the API related statistics of SCCP stack entity */
extern ss7_stats_api_t      sccp_api_stats;

/* contains the error related statistics of SCCP stack entity */
extern ss7_stats_error_t    sccp_error_stats;

/* contains the protocol related statistics (Q.752) of SCCP stack entity */
extern sccp_stats_proto_q752_t    sccp_proto_q752_stats;

/* SPR# 4543 Start */
/* contains the traffic related statistics of SCCP stack entity */
extern sccp_stats_traffic_t   sccp_traffic_stats;
/* SPR# 4543 End */

/* bitmap containing information about statistics type enabled */
extern U32bit               sccp_stats_flag;


#ifdef SCCP_STATS_ENABLED

/* MACROS FOR INCREMENTING API STATISTICS */

#define SC_STAT_API_INR_IN_API_SU()    if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.in_api_su
#define SC_STAT_API_INR_OUT_API_SU()   if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.out_api_su
#define SC_STAT_API_INR_IN_API_LL()    if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.in_api_ll
#define SC_STAT_API_INR_OUT_API_LL()   if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.out_api_ll
#define SC_STAT_API_INR_IN_API_SM()    if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.in_api_sm
#define SC_STAT_API_INR_OUT_API_SM()   if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.out_api_sm
#define SC_STAT_API_INR_ERR_API_SU()   if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.err_api_su
#define SC_STAT_API_INR_ERR_API_LL()   if(sccp_stats_flag & STATS_API) \
                                         ++sccp_api_stats.err_api_ll

/* MACROS FOR INCREMENTING ERROR STATISTICS */
#define SC_STAT_ERR_INR_ERR_API()      if(sccp_stats_flag & STATS_ERROR) \
                                         ++sccp_error_stats.err_api
#define SC_STAT_ERR_INR_ERR_MSG()      if(sccp_stats_flag & STATS_ERROR) \
                                         ++sccp_error_stats.err_msg
#define SC_STAT_ERR_INR_ERR_SYSTEM()   if(sccp_stats_flag & STATS_ERROR) \
                                         ++sccp_error_stats.err_sys
#define SC_STAT_ERR_INR_ERR_SYSTEM_RES()   if(sccp_stats_flag & STATS_ERROR) \
                                             ++sccp_error_stats.err_system_res

/* SPR# 4543 Start */
/* MACROS FOR INCREMENTING SCCP TRAFFIC STATISTICS */

#define SC_STAT_TRAFFIC_INR_PKT_SENT()     if(sccp_stats_flag & SCTC_STATS_TRAFFIC) \
                                        sccp_traffic_stats.num_sc_pkt_sent++
#define SC_STAT_TRAFFIC_INR_PKT_RECD()     if(sccp_stats_flag & SCTC_STATS_TRAFFIC) \
                                        sccp_traffic_stats.num_sc_pkt_recd++
#define SC_STAT_TRAFFIC_INR_PKT_DROP()     if(sccp_stats_flag & SCTC_STATS_TRAFFIC) \
                                        sccp_traffic_stats.num_sc_pkt_drop++
#define SC_STAT_TRAFFIC_INR_PKT_INVALID()    if(sccp_stats_flag & SCTC_STATS_TRAFFIC) \
                                        sccp_traffic_stats.num_sc_pkt_invalid++
#define SC_STAT_TRAFFIC_INR_GTT_TR_FAIL()    if(sccp_stats_flag & SCTC_STATS_TRAFFIC) \
                                        sccp_traffic_stats.num_sc_gtt_tr_fail++

/* SPR# 4543 End */

/* MACROS FOR INCREMENTING TCAP Q.752 STATISTICS */

#define SC_STAT_Q752_TS_TRFAIL_ADDR_NATURE() if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.trans_fail_addr_nature.time)
#define SC_STAT_Q752_INR_TRFAIL_ADDR_NATURE() if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.trans_fail_addr_nature.count++

#define SC_STAT_Q752_TS_TRFAIL_SPEC_ADDR() if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.trans_fail_spec_addr.time)
#define SC_STAT_Q752_INR_TRFAIL_SPEC_ADDR() if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.trans_fail_spec_addr.count++

#define SC_STAT_Q752_TS_PC_UNAVAIL if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.pc_unavail.time)
#define SC_STAT_Q752_INR_PC_UNAVAIL if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.pc_unavail.count++

#define SC_STAT_Q752_TS_NW_CONGESTION if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.nw_congestion.time)
#define SC_STAT_Q752_INR_NW_CONGESTION if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.nw_congestion.count++

#define SC_STAT_Q752_TS_SS_UNAVAIL if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.ss_unavail.time)
#define SC_STAT_Q752_INR_SS_UNAVAIL if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.ss_unavail.count++

#define SC_STAT_Q752_TS_SS_CONGESTION if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.ss_congestion.time)
#define SC_STAT_Q752_INR_SS_CONGESTION if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.ss_congestion.count++

#define SC_STAT_Q752_TS_UNEQUIPPED_SS if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.unequipped_ss.time)
#define SC_STAT_Q752_INR_UNEQUIPPED_SS if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.unequipped_ss.count++

#define SC_STAT_Q752_TS_SYNTAX_ERROR if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.syntax_error.time)
#define SC_STAT_Q752_INR_SYNTAX_ERROR if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.syntax_error.count++

#define SC_STAT_Q752_TS_ROUTE_FAIL if(sccp_stats_flag & STATS_PROTO_Q752) \
     ss7_get_absolute_time(&sccp_proto_q752_stats.routing_fail_reason_unknown.time)
#define SC_STAT_Q752_INR_ROUTE_FAIL if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.routing_fail_reason_unknown.count++

/* SPR # 9221 Fix Start */
#define SC_STAT_Q752_TS_T_REASS_EXPIRY if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.t_reass_expired.time)
#define SC_STAT_Q752_INR_T_REASS_EXPIRY if(sccp_stats_flag & STATS_PROTO_Q752) \
	sccp_proto_q752_stats.t_reass_expired.count++ 

#define SC_STAT_Q752_TS_SEG_OUT_OF_SEQ if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.xudt_seg_out_of_seq.time)
#define SC_STAT_Q752_INR_SEG_OUT_OF_SEQ if(sccp_stats_flag & STATS_PROTO_Q752) \
	sccp_proto_q752_stats.xudt_seg_out_of_seq.count++ 

#define SC_STAT_Q752_TS_NO_BUFF_LEFT if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.xudt_no_buff_left.time)
#define SC_STAT_Q752_INR_NO_BUFF_LEFT if(sccp_stats_flag & STATS_PROTO_Q752) \
	sccp_proto_q752_stats.xudt_no_buff_left.count++ 

#define SC_STAT_Q752_TS_HOP_COUNT_VIOLATION if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.hop_count_violation.time)
#define SC_STAT_Q752_INR_HOP_COUNT_VIOLATION if(sccp_stats_flag & \
													STATS_PROTO_Q752) \
	sccp_proto_q752_stats.hop_count_violation.count++ 

#define SC_STAT_Q752_TS_MSG_TOO_LARGE_FOR_SEGMENTING if(sccp_stats_flag & \
														STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.\
										msg_too_large_for_segmenting.time)
#define SC_STAT_Q752_INR_MSG_TOO_LARGE_FOR_SEGMENTING if(sccp_stats_flag & \
														STATS_PROTO_Q752) \
	sccp_proto_q752_stats.msg_too_large_for_segmenting.count++

#define SC_STAT_Q752_TS_FAILURE_TO_REL_CONN if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.failure_to_rel_conn.time)
#define SC_STAT_Q752_INR_FAILURE_TO_REL_CONN if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	sccp_proto_q752_stats.failure_to_rel_conn.count++

#define SC_STAT_Q752_TS_IAR_EXPIRY if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.sccp_iar_expiry.time)
#define SC_STAT_Q752_INR_IAR_EXPIRY if(sccp_stats_flag & STATS_PROTO_Q752) \
	sccp_proto_q752_stats.sccp_iar_expiry.count++

#define SC_STAT_Q752_TS_PROVIDER_INIT_RESET if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.provider_init_reset.time)
#define SC_STAT_Q752_INR_PROVIDER_INIT_RESET if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	sccp_proto_q752_stats.provider_init_reset.count++

#define SC_STAT_Q752_TS_PROVIDER_INIT_RLSD if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.provider_init_rlsd.time)
#define SC_STAT_Q752_INR_PROVIDER_INIT_RLSD if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
	sccp_proto_q752_stats.provider_init_rlsd.count++

#define SC_STAT_Q752_TS_SEG_FAILED if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.sccp_seg_failed.time)
#define SC_STAT_Q752_INR_SEG_FAILED if(sccp_stats_flag & STATS_PROTO_Q752) \
	sccp_proto_q752_stats.sccp_seg_failed.count++

#define SC_STAT_Q752_TS_SCCP_SOG_RECV if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.sccp_sog_recd.time)
#define SC_STAT_Q752_INR_SCCP_SOG_RECV if(sccp_stats_flag & STATS_PROTO_Q752) \
	sccp_proto_q752_stats.sccp_sog_recd.count++

/** SPR# 9525 Start Fix **/
#define SC_STAT_Q752_TS_T_COORD_EXPIRED if(sccp_stats_flag & STATS_PROTO_Q752) \
	ss7_get_absolute_time(&sccp_proto_q752_stats.sccp_t_coord_expired.time)

#define SC_STAT_Q752_INR_T_COORD_EXPIRED if(sccp_stats_flag & STATS_PROTO_Q752)\
	sccp_proto_q752_stats.sccp_t_coord_expired.count++
/** SPR# 9525 End Fix **/

#define SC_STAT_Q752_INR_ORIG_LUDT_XUDT_UDT(ssn) if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
		sccp_proto_q752_stats.orig_ludt_xudt_udt[(ssn-1)]++

#define SC_STAT_Q752_INR_RECD_LUDT_XUDT_UDT(ssn) if(sccp_stats_flag & \
												STATS_PROTO_Q752) \
		sccp_proto_q752_stats.recd_ludt_xudt_udt[(ssn-1)]++
/* SPR # 9221 Fix End */

/* SPR 8748 - Fix Start */
/* Changed ssn to ssn-1 because the array elements are from 0 to
** (MAX_SSN - 1)  */
#define SC_STAT_Q752_INR_ORIG_MSG_CLASS0(ssn) if(sccp_stats_flag & STATS_PROTO_Q752) \
     sccp_proto_q752_stats.orig_msg_class_0[(ssn-1)]++
#define SC_STAT_Q752_INR_ORIG_MSG_CLASS1(ssn)  if(sccp_stats_flag & STATS_PROTO_Q752) \
       sccp_proto_q752_stats.orig_msg_class_1[(ssn-1)]++
#define SC_STAT_Q752_INR_RECD_MSG_CLASS0(ssn) if(sccp_stats_flag & STATS_PROTO_Q752) \
       sccp_proto_q752_stats.recd_msg_class_0[(ssn-1)]++
#define SC_STAT_Q752_INR_RECD_MSG_CLASS1(ssn)       if(sccp_stats_flag & STATS_PROTO_Q752) \
       sccp_proto_q752_stats.recd_msg_class_1[(ssn-1)]++

#ifdef SCCP_INCLUDE_CO_SERVICE

#define SC_STAT_Q752_INR_ORIG_MSG_DT1(ssn) \
			if(sccp_stats_flag & STATS_PROTO_Q752) \
				sccp_proto_q752_stats.orig_msg_dt1[(ssn-1)]++

#define SC_STAT_Q752_INR_RECD_MSG_DT1(ssn) \
			if(sccp_stats_flag & STATS_PROTO_Q752) \
				sccp_proto_q752_stats.recd_msg_dt1[(ssn-1)]++

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

#define SC_STAT_Q752_INR_ORIG_MSG_DT2(ssn) \
			if(sccp_stats_flag & STATS_PROTO_Q752) \
				sccp_proto_q752_stats.orig_msg_dt2[(ssn-1)]++

#define SC_STAT_Q752_INR_RECD_MSG_DT2(ssn) \
			if(sccp_stats_flag & STATS_PROTO_Q752) \
				sccp_proto_q752_stats.recd_msg_dt2[(ssn-1)]++

#define SC_STAT_Q752_INR_ORIG_MSG_ED(ssn) \
			if(sccp_stats_flag & STATS_PROTO_Q752) \
				sccp_proto_q752_stats.orig_msg_ed[(ssn-1)]++

#define SC_STAT_Q752_INR_RECD_MSG_ED(ssn) \
			if(sccp_stats_flag & STATS_PROTO_Q752) \
				sccp_proto_q752_stats.recd_msg_ed[(ssn-1)]++

#endif /* end SCCP_INCLUDE_CO_CLASS3_SERVICE */
#endif /* end SCCP_INCLUDE_CO_SERVICE */

/* SPR 8748 - Fix End   */

#else

/* MACROS FOR INCREMENTING API STATISTICS */

#define SC_STAT_API_INR_IN_API_SU()   
#define SC_STAT_API_INR_OUT_API_SU() 
#define SC_STAT_API_INR_IN_API_LL() 
#define SC_STAT_API_INR_OUT_API_LL()
#define SC_STAT_API_INR_IN_API_SM() 
#define SC_STAT_API_INR_OUT_API_SM()
#define SC_STAT_API_INR_ERR_API_SU()
#define SC_STAT_API_INR_ERR_API_LL()

/* MACROS FOR INCREMENTING ERROR STATISTICS */

#define SC_STAT_ERR_INR_ERR_API()  
#define SC_STAT_ERR_INR_ERR_MSG() 
#define SC_STAT_ERR_INR_ERR_SYSTEM() 
#define SC_STAT_ERR_INR_ERR_SYSTEM_RES()

/* SPR# 4543 Start */
/* MACROS FOR INCREMENTING TRAFFIC STATISTICS */

#define SC_STAT_TRAFFIC_INR_PKT_SENT() 
#define SC_STAT_TRAFFIC_INR_PKT_RECD() 
#define SC_STAT_TRAFFIC_INR_PKT_DROP() 
#define SC_STAT_TRAFFIC_INR_PKT_INVALID() 
#define SC_STAT_TRAFFIC_INR_GTT_TR_FAIL() 

/* SPR# 4543 End */

/* MACROS FOR INCREMENTING TCAP Q.752 STATISTICS */

#define SC_STAT_Q752_TS_TRFAIL_ADDR_NATURE()
#define SC_STAT_Q752_INR_TRFAIL_ADDR_NATURE()

#define SC_STAT_Q752_TS_TRFAIL_SPEC_ADDR()
#define SC_STAT_Q752_INR_TRFAIL_SPEC_ADDR()

#define SC_STAT_Q752_TS_PC_UNAVAIL
#define SC_STAT_Q752_INR_PC_UNAVAIL

#define SC_STAT_Q752_TS_NW_CONGESTION 
#define SC_STAT_Q752_INR_NW_CONGESTION 

#define SC_STAT_Q752_TS_SS_UNAVAIL
#define SC_STAT_Q752_INR_SS_UNAVAIL 

#define SC_STAT_Q752_TS_SS_CONGESTION 
#define SC_STAT_Q752_INR_SS_CONGESTION 

#define SC_STAT_Q752_TS_UNEQUIPPED_SS
#define SC_STAT_Q752_INR_UNEQUIPPED_SS 

#define SC_STAT_Q752_TS_SYNTAX_ERROR
#define SC_STAT_Q752_INR_SYNTAX_ERROR 

#define SC_STAT_Q752_TS_ROUTE_FAIL
#define SC_STAT_Q752_INR_ROUTE_FAIL 

/* SPR # 9221 Fix Start */
#define SC_STAT_Q752_TS_T_REASS_EXPIRY
#define SC_STAT_Q752_INR_T_REASS_EXPIRY 

#define SC_STAT_Q752_TS_SEG_OUT_OF_SEQ 
#define SC_STAT_Q752_INR_SEG_OUT_OF_SEQ

#define SC_STAT_Q752_TS_NO_BUFF_LEFT 
#define SC_STAT_Q752_INR_NO_BUFF_LEFT 

#define SC_STAT_Q752_TS_HOP_COUNT_VIOLATION 
#define SC_STAT_Q752_INR_HOP_COUNT_VIOLATION 

#define SC_STAT_Q752_TS_MSG_TOO_LARGE_FOR_SEGMENTING 
#define SC_STAT_Q752_INR_MSG_TOO_LARGE_FOR_SEGMENTING

#define SC_STAT_Q752_TS_FAILURE_TO_REL_CONN 
#define SC_STAT_Q752_INR_FAILURE_TO_REL_CONN 

#define SC_STAT_Q752_TS_IAR_EXPIRY
#define SC_STAT_Q752_INR_IAR_EXPIRY 

#define SC_STAT_Q752_TS_PROVIDER_INIT_RESET 
#define SC_STAT_Q752_INR_PROVIDER_INIT_RESET 

#define SC_STAT_Q752_TS_PROVIDER_INIT_RLSD 
#define SC_STAT_Q752_INR_PROVIDER_INIT_RLSD 

#define SC_STAT_Q752_TS_PROVIDER_INIT_DISCONN 
#define SC_STAT_Q752_INR_PROVIDER_INIT_DISCONN 

#define SC_STAT_Q752_TS_SEG_FAILED 
#define SC_STAT_Q752_INR_SEG_FAILED 

#define SC_STAT_Q752_TS_SCCP_SOG_RECV 
#define SC_STAT_Q752_INR_SCCP_SOG_RECV 

#define SC_STAT_Q752_TS_T_COORD_EXPIRED 
#define SC_STAT_Q752_INR_T_COORD_EXPIRED 

#define SC_STAT_Q752_INR_ORIG_LUDT_XUDT_UDT(ssn) 
#define SC_STAT_Q752_INR_RECD_LUDT_XUDT_UDT(ssn) 
/* SPR # 9221 Fix End */

#define SC_STAT_Q752_INR_ORIG_MSG_CLASS0(ssn) 
#define SC_STAT_Q752_INR_ORIG_MSG_CLASS1(ssn)
#define SC_STAT_Q752_INR_RECD_MSG_CLASS0(ssn)
#define SC_STAT_Q752_INR_RECD_MSG_CLASS1(ssn)

#ifdef SCCP_INCLUDE_CO_SERVICE
#define SC_STAT_Q752_INR_RECD_MSG_DT1(ssn)
#define SC_STAT_Q752_INR_ORIG_MSG_DT1(ssn) 
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
#define SC_STAT_Q752_INR_RECD_MSG_DT2(ssn)
#define SC_STAT_Q752_INR_ORIG_MSG_DT2(ssn) 
#define SC_STAT_Q752_INR_RECD_MSG_ED(ssn)
#define SC_STAT_Q752_INR_ORIG_MSG_ED(ssn) 
#endif
#endif

#endif

#ifndef SCCP_INCLUDE_CO_SERVICE
#define SC_STAT_Q752_INR_RECD_MSG_DT1(ssn)
#define SC_STAT_Q752_INR_ORIG_MSG_DT1(ssn) 
#endif
#ifndef SCCP_INCLUDE_CO_CLASS3_SERVICE
#define SC_STAT_Q752_INR_RECD_MSG_DT2(ssn)
#define SC_STAT_Q752_INR_ORIG_MSG_DT2(ssn) 
#define SC_STAT_Q752_INR_RECD_MSG_ED(ssn)
#define SC_STAT_Q752_INR_ORIG_MSG_ED(ssn) 
#endif


#define SCCP_API_STAT_BUF_SIZE        (SS7_SM_API_MIN_LEN + 1 + 44)
#define SCCP_Q752_STAT_BUF_SIZE \
		(SS7_SM_API_MIN_LEN + 1 + sizeof (sccp_stats_proto_q752_t))
#define SCCP_ERROR_STAT_BUF_SIZE      (SS7_SM_API_MIN_LEN + 1 + 16)
/* SPR# 4543 Start */
#define SCCP_TRAFFIC_STAT_BUF_SIZE      (SS7_SM_API_MIN_LEN + 1 + 20) 
/* SPR# 4543 End */
#ifdef DISTRIBUTED_SCCP
#define SCCP_INTERNAL_STAT_SIZE  41
#endif


#endif /* _SC_STATS_H */
