/***************************************************************************
**  FILE NAME:
**      sc_dbfm.h
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
**  10Jul02      Suyash Tripathi          Fixed SPR 9202  
**  22Oct01	 Prateek Bidwalkar        Changed the IS_SS_REGISTERED macro
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_DBFM_H_
#define _SC_DBFM_H_

#include "sc_s7gl.h"
#include "sc_dbf.h"

/* This file contains macros to access the fields of database
   entries */

#define IS_T_A_RUNNING(p)          ((p)->t_a_running)
/* SPR 9202 - Fix Start */
/*#define IS_T_D_RUNNING(p)          ((p)->t_a_running) */
#define IS_T_D_RUNNING(p)          ((p)->t_d_running)
/* SPR 9202 - Fix Start */
#define IS_T_CON_RUNNING(p)        ((p)->t_con_running)
#define IS_T_STAT_INFO_RUNNING(p)  ((p)->t_stat_info_running)

/* Access by SCMG */
#define IS_SS_ALLOWED(p)	((p)->allowed)
#define IS_SS_PROHIBITED(p)	(!((p)->allowed))
#define MARK_SS_ALLOWED(p)	((p)->allowed = SS7_TRUE)
#define MARK_SS_PROHIBITED(p)	((p)->allowed = SS7_FALSE)

#define IS_SP_ALLOWED(p)	((p)->allowed)
#define IS_SP_PROHIBITED(p)	(!((p)->allowed))
#define MARK_SP_ALLOWED(p)	((p)->allowed = SS7_TRUE)
#define MARK_SP_PROHIBITED(p)	((p)->allowed = SS7_FALSE)

#define IS_SCCP_ALLOWED(p)	((p)->scmg_ss.allowed)
#define IS_SCCP_PROHIBITED(p)	(!((p)->scmg_ss.allowed))
#define MARK_SCCP_ALLOWED(p)	((p)->scmg_ss.allowed = SS7_TRUE)
#define MARK_SCCP_PROHIBITED(p)	((p)->scmg_ss.allowed = SS7_FALSE)

#define IS_UPU_RECEIVED(p)      ((p)->upu_received)
#define MARK_UPU_RECEIVED(p)    ((p)->upu_received = SS7_TRUE)
#define CANCEL_UPU_RECEIVED(p)  ((p)->upu_received = SS7_FALSE)
#define UPU_CAUSE(p)            ((p)->upu_cause)

#define IS_SST_IN_PROGRESS(p)   ((p)->t_stat_info_running)

#define IS_SS_REGISTERED(p_ss)  ((p_ss)->registered)
#define SET_SS_NOT_REGISTERED(p_ss)  ((p_ss)->registered = SS7_FALSE)

#endif /* _SC_DBFM_H_ */
