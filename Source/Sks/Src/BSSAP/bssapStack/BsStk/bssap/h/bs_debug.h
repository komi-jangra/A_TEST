/*******************************************************************************
**      FILE NAME:
**          bs_debug.h
**
**      DESCRIPTION:
**              This files defines the macros common definitions to be used by
**              by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _BS_DEBUG_H_
#define _BS_DEBUG_H_

#include "bs_s7gl.h"
#include "bs_debug.h"

#define LOGGER_IMR
#ifdef LOGGER_IMR
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include <sysxxx_msgstruct.h>
#include "ipcfrm_syslog.h"
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

extern S8bit * success_str;
extern S8bit * failure_str;
extern int ss7_over_sigtran_log_print(const char *format, ...);

/* MACRO FOR HEX DUMP */
#ifdef SCCP_TRACE_ENABLED
#ifdef LOGGER_IMR
#define BSSAP_HEX_DUMP(trace_flag,trace_level,p_buf,noctets) \
		{ \
			if(bssap_trace_table[trace_level] & trace_flag) \
			PRINT_HEX_DUMP(DEBUG,p_buf,noctets); \
		}
#else
#define BSSAP_HEX_DUMP(trace_flag,trace_level,p_buf,noctets) \
		{ \
			if(bssap_trace_table[trace_level] & trace_flag) \
			SS7_HEX_DUMP (p_buf, noctets);\
}
#endif
#else
#define BSSAP_HEX_DUMP(trace_flag,trace_level,p_buf,noctets)
#endif

#define RESULT_STR(ret_val) ((ret_val == SS7_SUCCESS) ? success_str : failure_str)


#if defined (SCCP_TRACE_ENABLED)
#ifndef SCCP_MT_SAFE
#ifdef LOGGER_IMR
#define SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info) \
			if(trace_level ==  3) \
      {\
        LOG_PRINT_DEBUG debug_info;\
      }\
			if(trace_level ==  1) \
      {\
        LOG_PRINT_INFO debug_info;\
      }\
			if(trace_level ==  2) \
      {\
        LOG_PRINT_INFO debug_info;\
      }
#else	
#define SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info) LOG_PRINT_INFO debug_info;
#endif
#else
#define SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info) \
  STACK_PRINT debug_info
#endif
#else
#define SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info)
#endif

/* MACRO FOR LOGGING UT TRACE MESSAGES; */

#ifdef SS7_UT_ENABLED

#define SS7_UT_TRACE(trace_flag, trace_level, debug_info) \
SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info)


#else
#define SS7_UT_TRACE(trace_flag, trace_level, debug_info)
#endif


#ifdef UT_TRACE_ENABLED
#ifdef SCCP_MT_SAFE
#define SCCP_UT_TRACE(x)    STACK_PRINT(x)
#else
#define SCCP_UT_TRACE(x)    STACK_PRINT x
#endif
#else
#define SCCP_UT_TRACE(x)
#endif


#ifdef SCCP_TRACE_ENABLED

#define SCCP_STACK_TRACE(trace_flag, trace_level, string) \
	SC_SS7_STACK_TRACE(trace_flag, trace_level, string) 

#else

#define SCCP_STACK_TRACE(trace_flag, trace_level, string)

#endif

#define SCCP_ANY_TRACE_DEF_TRC_LEVEL   BRIEF_TRACE
#define SC_TRC(x)        SCCP_STACK_TRACE (SC_ALL_TRACE, \
                                        SCCP_ANY_TRACE_DEF_TRC_LEVEL, x)

#define SCCP_INCOM_DEF_TRC_LEVEL       BRIEF_TRACE
#define SC_I_TRC(x)      SCCP_STACK_TRACE (SCTC_INCOMING_TRACE, \
                                        SCCP_INCOM_DEF_TRC_LEVEL, x)

#define SCCP_OUTG_DEF_TRC_LEVEL        BRIEF_TRACE
#define SC_O_TRC(x)      SCCP_STACK_TRACE (SCTC_OUTGOING_TRACE, \
                                        SCCP_OUTG_DEF_TRC_LEVEL, x)

#define SCCP_API_DEF_TRC_LEVEL         DETAILED_TRACE
#define BS_A_TRC(x)      SCCP_STACK_TRACE (SCTC_API_TRACE, \
                                        SCCP_API_DEF_TRC_LEVEL, x)

#ifdef SCCP_TRACE_ENABLED
#define SC_A_DTRC(p_api)     (sccp_api_detail_trace(p_api))
#else
#define SC_A_DTRC(p_api)
#endif

#define SCCP_INIT_DEF_TRC_LEVEL        BRIEF_TRACE
#define SC_IN_TRC(x)     SCCP_STACK_TRACE (SCTC_INIT_TRACE, \
                                        SCCP_API_DEF_TRC_LEVEL, x)

#define SCCP_SYS_ERR_DEF_TRC_LEVEL     BRIEF_TRACE
#define BS_S_TRC(x)  SCCP_STACK_TRACE (SCTC_SYS_ERR_TRACE, \
                                       SCCP_SYS_ERR_DEF_TRC_LEVEL, x)

#define SCCP_PROTO_EXCP_DEF_TRC_LEVEL  BRIEF_TRACE
#define SC_P_TRC(x)  SCCP_STACK_TRACE (SCTC_PROTO_EXCEPTION_TRACE, \
                                       SCCP_PROTO_EXCP_DEF_TRC_LEVEL, x)

#define SCCP_SYS_RESOURCE_DEF_TRC_LEVEL  MEDIUM_TRACE
#define SC_R_TRC(x)  SCCP_STACK_TRACE (SCTC_PROTO_EXCEPTION_TRACE, \
                                       SCCP_PROTO_EXCP_DEF_TRC_LEVEL, x)

#define SCCP_SCLC_DEF_TRC_LEVEL         MEDIUM_TRACE
#define BS_CL_TRC(x)    SCCP_STACK_TRACE (SCLC_TRACE, \
                                       SCCP_SCLC_DEF_TRC_LEVEL, x)

#define SCCP_SCRC_DEF_TRC_LEVEL         MEDIUM_TRACE
#define RC_TRC(x)    SCCP_STACK_TRACE (SCRC_TRACE, \
                                       SCCP_SCRC_DEF_TRC_LEVEL, x)

#define SCCP_SCMG_DEF_TRC_LEVEL         BRIEF_TRACE
#define MG_TRC(x)    SCCP_STACK_TRACE (SCMG_TRACE, \
                                       SCCP_SCMG_DEF_TRC_LEVEL, x)

#define SCCP_REDN_DEF_TRC_LEVEL			BRIEF_TRACE
#define SC_REDN_TRC(x) SCCP_STACK_TRACE (SCREDN_TRACE, \
                                       SCCP_SCMG_DEF_TRC_LEVEL, x)

#ifdef SCCP_ERROR_ENABLED
#define SCCP_ERR(err_code, err_type, err_level) \
        sccp_err_handler (err_code, err_type, err_level)
#else
#define SCCP_ERR(err_code, err_type, err_level)
#endif

#ifdef SCCP_ERROR_ENABLED
#define SCCP_EVENT_ALARM(object_id, state, p_sp, p_ss, p_conn) \
  sccp_report_event_to_sm (object_id, state, p_sp, p_ss, p_conn)
#else
#define SCCP_EVENT_ALARM(object_id, state, p_sp, p_ss, p_conn)
#endif

#define SCCP_PROTO_ERR_DEF_LEVEL    MINOR_ERROR
#define SC_P_ERR(ecode)  SCCP_ERR(ecode, STACK_PROTOCOL_ERROR, \
                                  SCCP_PROTO_ERR_DEF_LEVEL)

#define SCCP_SYS_ERR_DEF_LEVEL      CRITICAL_ERROR
#define SC_S_ERR(ecode)  SCCP_ERR (ecode, SYSTEM_ERROR, \
                                   SCCP_SYS_ERR_DEF_LEVEL)

#define SCCP_SYS_RES_ERR_DEF_LEVEL  MAJOR_ERROR
#define SC_R_ERR(ecode)  SCCP_ERR (ecode, SYSTEM_RES_ERROR, \
                                   SCCP_SYS_RES_ERR_DEF_LEVEL)

#define SCCP_API_ERR_DEF_LEVEL    MINOR_ERROR
#define SC_A_ERR(ecode)  SCCP_ERR (ecode, API_ERROR, \
                                   SCCP_API_ERR_DEF_LEVEL)

#define SC_INVALID_OBJECT_FLAG(obj_id)  ((obj_id != SCCP_SM_OBJECT_SP_FLAG) && \
           (obj_id != SCCP_SM_OBJECT_SS_FLAG) && \
           (obj_id != SCCP_SM_OBJECT_CONN_FLAG) && \
           (obj_id != SCCP_SM_ALL_OBJ_FLAG))


#endif /* _BS_DEBUG_H_ */




