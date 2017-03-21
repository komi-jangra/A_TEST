/*******************************************************************************
**      FILE NAME:
**          bssap_port.h
**
**      DESCRIPTION:
**              Defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
******************************************************************************/

#ifndef _BSSAP_PORT_H
#define _BSSAP_PORT_H

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

/*#include "common_type.h" */

#ifndef MAX_HOSTNAME_LEN
#define MAX_HOSTNAME_LEN      GSN_MAX_HOSTNAME_LEN
#endif

/* BSSAP - general */
#define BSSAP_BUF_SIZE               4068 
#define BSSAP_NBUF                4068


typedef unsigned char  U8BIT;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UInt32;
typedef unsigned int   UBITS;



#define SIGTRAN_MAX_SSN_PER_PC 7
/*#define SIGTRAN_MAX_SSN_PER_PC 6 */
#define GSN_MAX_VLR_SUPPORTED 5
#define MAP_MAX_SS7_ADDR_LEN 20
#define	GSN_NULL_SSN		0xFF
#define SGSN_SSN    		149
#define	GSN_NULL_PC		0xFFFF

#define BS_MAX_NMB_INTF_ID 33 /*16 */ 
#define MAX_CALL_REF   65535 /*65535*/ /*1048576*/ /*1048576  *2^20 call ref value *//* 32766 old value */  /* Max call reference supported at BSSAP */
#define MAX_CIRCUIT_CIC   65535 /*65535 */


/* Miscellaneous macros */
#ifdef SINGLE_THREAD
#define SL_MUTEX_DEF(name)
#define SL_MUTEX_INIT(mutex)
#define SL_MUTEX_LOCK(mutex)
#define SL_MUTEX_UNLOCK(mutex)

/* friendly alternate names (?!? :) */
#define SL_LOCK_DEF(name)
#define SL_LOCK_INIT(mutex)
#define SL_LOCK(mutex)
#define SL_UNLOCK(mutex)



#define OM_ELEMENT_SCCP_T_REASS 1
#define OM_ELEMENT_SCCP_T_STAT_INFO 2
#define OM_ELEMENT_SCCP_T_CONG_ATTACK 3
#define OM_ELEMENT_SCCP_T_CONG_DECAY 4
#define OM_ELEMENT_SCCP_SEG_PAR_Z 5


#define MAX_SP_DATA_LIST   20

#define SCCP_MAX-SP 64
#define SCCP_MAX-SS  32
#define SCCP_MAX-CSP 16
#define SCCP_MAX-CSS 16 
#define SS7_API_HEADER_LEN      5
#define API_LEN_LSB  3
#define API_LEN_MSB  4
#define GET_API_LEN(p_api)    (p_api[API_LEN_LSB] | (p_api[API_LEN_MSB] << 8))

#define SCCP_NM_SET_TIMER_REQ_BUF(type, value) \
{\
    error_t ecode;\
	U8bit num_timers = 1;\
	tmr_buffer_t timers[1];\
	timers[0].timer_index = type;\
	timers[0].timer_value = (U32bit)value;\
	if(sccp_init_timers(num_timers, timers, &ecode) == SS7_FAILURE)\
	{\
    LOG_PRINT(DEBUG,"[ENCAPS:: ] -> SCCP TIMER REQ from SCCP_NM_SET_TIMER_REQ_BUF Failed"); \
	}\
	else\
	{\
    LOG_PRINT(DEBUG,"[ENCAPS:: ] -> SCCP TIMER REQ from SCCP_NM_SET_TIMER_REQ_BUF Succeeded"); \
	}\
}


#endif
#endif
