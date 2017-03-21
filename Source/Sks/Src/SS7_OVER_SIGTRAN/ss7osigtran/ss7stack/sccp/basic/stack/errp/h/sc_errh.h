/***************************************************************************
**  FILE NAME:
**      sc_errh.h
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
**           Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_ERRH_H_
#define _SC_ERRH__H_

#include "sc_s7gl.h"


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

#define SC_INVALID_OBJECT_FLAG(obj_id) 	((obj_id != SCCP_SM_OBJECT_SP_FLAG) && \
					 (obj_id != SCCP_SM_OBJECT_SS_FLAG) && \
					 (obj_id != SCCP_SM_OBJECT_CONN_FLAG) && \
					 (obj_id != SCCP_SM_ALL_OBJ_FLAG))

#endif /* _SC_ERRH_H_ */
