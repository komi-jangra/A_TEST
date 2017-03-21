/***************************************************************************
**  FILE NAME:
**      sc_debug.h
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
**  12May'98 Sriganesh. Kini   -----  Original
**  10Aug'98 Tarang Gupta      ----- Adding Trace macros
**  28Jan'02 Ashish Sawalkar   ----- Changes for MT-Safe SCCP
**  18Jun'02 Suyash Tripathi   ----- Renamed SS7_STACK_TRACE to SC_SS7_STACK_TRACE 
**  26Jan'03 Ashish Sawalkar   ----- fixed spr 11120 
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_DEBUG_H_
#define _SC_DEBUG_H_

#include "sc_s7gl.h"

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

/*			if(sccp_trace_table[trace_level] & trace_flag) \*//* 16-09-14 by Amaresh SCM implement */
/* MACRO FOR HEX DUMP */
#ifdef SCCP_TRACE_ENABLED
#ifdef LOGGER_IMR
#define SCCP_HEX_DUMP(trace_flag,trace_level,p_buf,noctets) \
		{ \
			PRINT_HEX_DUMP(DEBUG,p_buf,noctets); \
		}
#else
#define SCCP_HEX_DUMP(trace_flag,trace_level,p_buf,noctets) \
		{ \
			if(sccp_trace_table[trace_level] & trace_flag) \
			SS7_HEX_DUMP (p_buf, noctets);\
}
#endif
#else
#define SCCP_HEX_DUMP(trace_flag,trace_level,p_buf,noctets)
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
/*	if(sccp_trace_table[trace_level] & trace_flag) \
  	STACK_PRINT(debug_info)*/
#endif
#else
#define SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info) \
  STACK_PRINT debug_info
/*if(sccp_trace_table[trace_level] & trace_flag) \*/
 /* STACK_PRINT debug_info*/
#endif
#else
#define SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info)
#endif

/* SPR 8985 - Fix End */

/* MACRO FOR LOGGING UT TRACE MESSAGES; */

#ifdef SS7_UT_ENABLED
/* SPR 8985 - Fix Start */
/**********SS7_STACK_TRACE is renamed as SC_SS7_STACK_TRACE ****/
/****
#define SS7_UT_TRACE(trace_flag, trace_level, debug_info) \
SS7_STACK_TRACE(trace_flag,trace_level,debug_info)  ****/ 

#define SS7_UT_TRACE(trace_flag, trace_level, debug_info) \
SC_SS7_STACK_TRACE(trace_flag,trace_level,debug_info)

/* SPR 8985 - Fix End */

#else
#define SS7_UT_TRACE(trace_flag, trace_level, debug_info)
#endif

/* --<end of paste>--- */

#ifdef UT_TRACE_ENABLED
#ifdef SCCP_MT_SAFE
#define SCCP_UT_TRACE(x)    STACK_PRINT(x)
#else
#define SCCP_UT_TRACE(x)    STACK_PRINT x
#endif
#else
#define SCCP_UT_TRACE(x)
#endif


#ifdef LOGGER_IMR
#define SCCP_STACK_TRACE(trace_flag,trace_level,debug_info) \
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

#endif


#if 0
#ifdef SCCP_TRACE_ENABLED

/* SPR 8985 - Fix Start */
/**********SS7_STACK_TRACE is renamed as SC_SS7_STACK_TRACE ****/
/****
#define SCCP_STACK_TRACE(trace_flag, trace_level, string) \
	SS7_STACK_TRACE(trace_flag, trace_level, string) ****/
#define SCCP_STACK_TRACE(trace_flag, trace_level, string) \
	SC_SS7_STACK_TRACE(trace_flag, trace_level, string) 
/* SPR 8985 - Fix End */

#else

#define SCCP_STACK_TRACE(trace_flag, trace_level, string)

#endif
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
/*#define SC_A_TRC(x)      SCCP_STACK_TRACE (SCTC_API_TRACE, \
                                        SCCP_API_DEF_TRC_LEVEL, x)
*/



#define SC_A_TRC(x)				LOG_PRINT_INFO x
#ifdef SCCP_TRACE_ENABLED
#define SC_A_DTRC(p_api)     (sccp_api_detail_trace(p_api))
#else
#define SC_A_DTRC(p_api)
#endif

#define SCCP_INIT_DEF_TRC_LEVEL        BRIEF_TRACE
#define SC_IN_TRC(x)     SCCP_STACK_TRACE (SCTC_INIT_TRACE, \
                                        SCCP_API_DEF_TRC_LEVEL, x)

#define SCCP_SYS_ERR_DEF_TRC_LEVEL     BRIEF_TRACE
#define SC_S_TRC(x)  SCCP_STACK_TRACE (SCTC_SYS_ERR_TRACE, \
                                       SCCP_SYS_ERR_DEF_TRC_LEVEL, x)

#define SCCP_PROTO_EXCP_DEF_TRC_LEVEL  BRIEF_TRACE
#define SC_P_TRC(x)  SCCP_STACK_TRACE (SCTC_PROTO_EXCEPTION_TRACE, \
                                       SCCP_PROTO_EXCP_DEF_TRC_LEVEL, x)

#define SCCP_SYS_RESOURCE_DEF_TRC_LEVEL  MEDIUM_TRACE
#define SC_R_TRC(x)  SCCP_STACK_TRACE (SCTC_PROTO_EXCEPTION_TRACE, \
                                       SCCP_PROTO_EXCP_DEF_TRC_LEVEL, x)

#define SCCP_SCLC_DEF_TRC_LEVEL         MEDIUM_TRACE
#define CL_TRC(x)    SCCP_STACK_TRACE (SCLC_TRACE, \
                                       SCCP_SCLC_DEF_TRC_LEVEL, x)

#define SCCP_SCRC_DEF_TRC_LEVEL         MEDIUM_TRACE
#define RC_TRC(x)    SCCP_STACK_TRACE (SCRC_TRACE, \
                                       SCCP_SCRC_DEF_TRC_LEVEL, x)

#define SCCP_SCMG_DEF_TRC_LEVEL         BRIEF_TRACE
#define MG_TRC(x)    SCCP_STACK_TRACE (SCMG_TRACE, \
                                       SCCP_SCMG_DEF_TRC_LEVEL, x)

#define SCCP_REDN_DEF_TRC_LEVEL			BRIEF_TRACE
/*#define SC_REDN_TRC(x) SCCP_STACK_TRACE (SCREDN_TRACE, \
                                       SCCP_SCMG_DEF_TRC_LEVEL, x)
*/

#define SC_REDN_TRC(x)	 LOG_PRINT_INFO x 
/* spr 11120 fix */
typedef struct
{
	U8bit 		info_id;
	U8bit		info_cat;
    U8bit       sccp_gtt_trace_level;
    U32bit      sccp_gtt_trace_flag;
    error_t     ecode;
} sccp_gtt_trace_level_info_t;

return_t sccp_update_gtt_dbg_info
    _ARGS_ ((sccp_gtt_trace_level_info_t *gtt_trace_info));

#endif /* _SC_DEBUG_H_ */




