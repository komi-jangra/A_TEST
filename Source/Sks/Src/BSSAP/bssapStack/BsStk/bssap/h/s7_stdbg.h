/*******************************************************************************
**      FILE NAME:
**          s7_stdbg.h
**
**      DESCRIPTION:
**              This file defines the common definitions for debug trace
**              to be used by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _S7_STDBG_H_     /* If this file has not been processed, */
#define _S7_STDBG_H_     /* define it as seen--ref '#endif' below. */

/* MAXIMUM NUMBER OF TRACE LEVELS */
#define MAX_TRACE_LEVELS                4

/* TRACE FLAGS COMMON TO ALL STACK ENTITIES */
#define SCTC_INIT_TRACE        0x1     /* initializion & provisioning trace */ 
#define SCTC_INCOMING_TRACE    0x2     /* incomming message trace */ 
#define SCTC_OUTGOING_TRACE    0x4     /* outgoing message trace */
#define SCTC_API_TRACE         0x8     /* outgoing message trace */
#define SCTC_SYS_ERR_TRACE          0x10   /* system related errors trace   */
#define SCTC_PROTO_EXCEPTION_TRACE  0x20   /* protocol related errors trace */
#define SCTC_INVALID_TRACE         0x0     /* invalid trace flag */

/* macro for checking validity of trace flag */



#ifdef TCAP
#ifdef DISTRIBUTED_TCAP
#define TC_ALL_TRACE (SCTC_INIT_TRACE | SCTC_INCOMING_TRACE | \
	SCTC_OUTGOING_TRACE | SCTC_API_TRACE | SCTC_SYS_ERR_TRACE |\
	SCTC_PROTO_EXCEPTION_TRACE | TCO_TRACE | TSM_TRACE | DCO_TRACE |\
        DSM_TRACE | CCO_TRACE | ISM_TRACE | DB_TRACE | MP_TRACE | \
        ASN_TRACE | UI_TRACE | ERRP_TRACE | REDN_TRACE|DTCAP_TRACE)


#define TC_INVALID_TRACE_FLAG(flag)    ((flag!=SCTC_INIT_TRACE)   &&  \
                                 (flag!=SCTC_INCOMING_TRACE)     &&  \
                                 (flag!=SCTC_OUTGOING_TRACE)        &&  \
				 (flag!=SCTC_API_TRACE)        &&  \
                                 (flag!=SCTC_SYS_ERR_TRACE) &&  \
                                 (flag!=SCTC_PROTO_EXCEPTION_TRACE) && \
                                 (flag!=TCO_TRACE) && \
                                 (flag!=TSM_TRACE) && \
                                 (flag!=DCO_TRACE) && \
                                 (flag!=DSM_TRACE) && \
                                 (flag!=CCO_TRACE) && \
                                 (flag!=ISM_TRACE) && \
                                 (flag!=DB_TRACE) && \
                                 (flag!=MP_TRACE) && \
                                 (flag!=ASN_TRACE) && \
                                 (flag!=UI_TRACE) && \
                                 (flag!=ERRP_TRACE) && \
                                 (flag!=TC_ALL_TRACE) && \
                                 (flag != REDN_TRACE) && \
                                 (flag != DTCAP_TRACE)) 
#else

#define TC_ALL_TRACE (SCTC_INIT_TRACE | SCTC_INCOMING_TRACE | \
	SCTC_OUTGOING_TRACE | SCTC_API_TRACE | SCTC_SYS_ERR_TRACE |\
	SCTC_PROTO_EXCEPTION_TRACE | TCO_TRACE | TSM_TRACE | DCO_TRACE |\
        DSM_TRACE | CCO_TRACE | ISM_TRACE | DB_TRACE | MP_TRACE | \
        ASN_TRACE | UI_TRACE | ERRP_TRACE | REDN_TRACE)


#define TC_INVALID_TRACE_FLAG(flag)    ((flag!=SCTC_INIT_TRACE)   &&  \
                                 (flag!=SCTC_INCOMING_TRACE)     &&  \
                                 (flag!=SCTC_OUTGOING_TRACE)        &&  \
				 (flag!=SCTC_API_TRACE)        &&  \
                                 (flag!=SCTC_SYS_ERR_TRACE) &&  \
                                 (flag!=SCTC_PROTO_EXCEPTION_TRACE) && \
                                 (flag!=TCO_TRACE) && \
                                 (flag!=TSM_TRACE) && \
                                 (flag!=DCO_TRACE) && \
                                 (flag!=DSM_TRACE) && \
                                 (flag!=CCO_TRACE) && \
                                 (flag!=ISM_TRACE) && \
                                 (flag!=DB_TRACE) && \
                                 (flag!=MP_TRACE) && \
                                 (flag!=ASN_TRACE) && \
                                 (flag!=UI_TRACE) && \
                                 (flag!=ERRP_TRACE) && \
                                 (flag!=TC_ALL_TRACE) && \
                                 (flag != REDN_TRACE)) 
#endif
#endif

#ifdef SCCP
#define SC_ALL_TRACE (SCTC_INIT_TRACE | SCTC_INCOMING_TRACE | \
	SCTC_OUTGOING_TRACE | SCTC_API_TRACE | SCTC_SYS_ERR_TRACE |\
	SCTC_PROTO_EXCEPTION_TRACE | SCMG_TRACE | SCRC_TRACE |\
	SCOC_TRACE | SCLC_TRACE | SCREDN_TRACE)


#define SC_INVALID_TRACE_FLAG(flag)    ((flag!=SCTC_INIT_TRACE)     && \
                                        (flag!=SCTC_INCOMING_TRACE) && \
                                        (flag!=SCTC_OUTGOING_TRACE) && \
		       	                        (flag!=SCTC_API_TRACE)      && \
                                        (flag!=SCTC_SYS_ERR_TRACE)  && \
                                        (flag!=SCTC_PROTO_EXCEPTION_TRACE) && \
                                        (flag!=SCMG_TRACE) && \
                                        (flag!=SCRC_TRACE) && \
                                        (flag!=SCOC_TRACE) && \
                                        (flag!=SCLC_TRACE) && \
                                        (flag!=SCREDN_TRACE) && \
                                        (flag!=SC_ALL_TRACE)) 
#endif

/* MACRO FOR LOGGING TRACE MESSAGES */

/*
 * these macros have been moved into the stack code to avoid redefinition
 * of TRACE_TABLE when common code is compiled with both SCCP and TCAP turned
 * on 
 */


#ifdef TCAP
extern U32bit tcap_trace_table[];
/*
#define TRACE_TABLE tcap_trace_table
*/
#endif

#ifdef SCCP
extern U32bit bssap_trace_table[];
/* 
#define TRACE_TABLE bssap_trace_table
*/
#endif

/*
#if defined (TCAP_TRACE_ENABLED) || defined (SCCP_TRACE_ENABLED)
#define SS7_STACK_TRACE(trace_flag,trace_level,debug_info) \
                       if(TRACE_TABLE[trace_level] & trace_flag) \
                         STACK_PRINT debug_info
#else
#define SS7_STACK_TRACE(trace_flag,trace_level,debug_info)
#endif
*/


/* MACRO FOR LOGGING UT TRACE MESSAGES; */
/* moved into the stack code, because it requires SS7_STACK_TRACE */
/*
#ifdef SS7_UT_ENABLED
#define SS7_UT_TRACE(trace_flag, trace_level, debug_info) \
	SS7_STACK_TRACE(trace_flag,trace_level,debug_info)
#else
#define SS7_UT_TRACE(trace_flag, trace_level, debug_info)
#endif
*/
			                
/* macro for checking validity of error level */
#define SS7_INVALID_TRACE_LEV(lev)     ((lev!=NO_TRACE)          &&  \
                                 (lev!=BRIEF_TRACE)    &&  \
                                 (lev!=MEDIUM_TRACE)       &&  \
                                 (lev!=DETAILED_TRACE))

#endif /* _S7_STDBG_H_       -- This MUST appear after all code! */
