/*******************************************************************************
**      FILE NAME:
**          bs_dbf.h
**
**      DESCRIPTION:
**              This files defines all the database structures for signaling point, subsystems and
**      concerned subsystem and signaling point along with macros to access their fields macros common**      definitions to be used by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _BS_DBF_H_
#define _BS_DBF_H_

#include "bs_s7gl.h"
#include "bs_cdef.h"


typedef U32bit ss_id_t;
#define SIZEOF_SS_ID_T 4

typedef U32bit sp_id_t;
#define SIZEOF_SP_ID_T 4

typedef U8bit nw_id_t;
typedef U16bit cluster_t;   

extern U32bit SIZEOF_C_SS_SP_ARRAY ;


typedef U32bit c_ss_sp_t;

#if defined (SCCP_ANSI) || defined (SCCP_BCGR) || defined (SCCP_CHINESE)
	typedef U32bit pc_t;
#else
	typedef U16bit pc_t;
#endif

#define SC_NOT_CONFIGURED 0
#define SC_CONFIGURED 1



 #define IS_SPID_VALID(sp_id)  ((sp_id) < MAX_SP) 
#define IS_SSID_VALID(ss_id)  ((ss_id) < MAX_SS)

#define GET_SP_FROM_ID(sp_id) (&sccp_db.sp[(sp_id_t)sp_id])
#define GET_ID_FROM_SP(p_sp)  ((sp_id_t)((p_sp) - GET_SP_FROM_ID(0)))
#define GET_SS_FROM_ID(ss_id) (&sccp_db.ss[(ss_id_t)(ss_id)])
#define GET_ID_FROM_SS(p_ss)  ((ss_id_t)((p_ss) - GET_SS_FROM_ID(0)))

/* Macros to set fields of signaling points */
#define SET_SP_CONFIGURED(p_sp)      ((p_sp)->conf_status = SC_CONFIGURED)
#define IS_SP_CONFIGURED(p_sp)       (SC_CONFIGURED == (p_sp)->conf_status)
#define SET_SP_NOT_CONFIGURED(p_sp)  ((p_sp)->conf_status = SC_NOT_CONFIGURED)

#define SET_SP_NW_ID(p_sp, network_id)  ((p_sp)->nw_id = (nw_id_t)(network_id))
#define SET_SP_PC(p_sp, point_code)  ((p_sp)->pc = (pc_t)(point_code))
#define SET_SP_LOCAL_FLAG(p_sp, local_flag)  ((p_sp)->local = (Boolean)(local_flag))
#define SET_NUM_SS_IN_SP(p_sp, num_subsys)  ((p_sp)->num_ss = (U8bit)num_subsys)
#define SET_SS_LIST_IN_SP(p_sp, p_ss)   ((p_sp)->ss_id_list = GET_ID_FROM_SS(p_ss))
#define SET_NEXT_SP_HASH_BUCKET(p_sp, p_next_sp)  ((p_sp)->sp_id = GET_ID_FROM_SP(p_next_sp))
#define SET_NEXT_SP(p_sp, p_next_sp)    ((p_sp)->next_sp_id = GET_ID_FROM_SP(p_next_sp))

/* Macros to get fields of signaling points */
#define GET_SP_NW_ID(p_sp)   ((p_sp)->nw_id)
#define GET_SP_PC(p_sp)      ((p_sp)->pc)
#define IS_SP_LOCAL(p_sp)    ((p_sp)->local)
#define GET_NUM_SS_IN_SP(p_sp)  ((p_sp)->num_ss)
#define GET_SS_LIST_IN_SP(p_sp)  (GET_SS_FROM_ID((p_sp)->ss_id_list))
#define GET_NEXT_SP(p_sp)    (GET_SP_FROM_ID((p_sp)->next_sp_id))
#define GET_SP_CLUSTER(p_sp) (((GET_SP_PC(p_sp)) >> 8) & 0x00ff)   


#define BYTEID_FROM_PTR(p_byte)   ((c_ss_sp_t)((p_byte) - &sccp_db.conc_ss_sp_list[0]))

#define PTR_FROM_BYTEID(c_ss_sp_id) \
	((U8bit *)(&sccp_db.conc_ss_sp_list[(c_ss_sp_id_t)c_ss_sp_id]))
#define END_OF_BYTE_ARRAY()  \
	((U8bit *)(&sccp_db.conc_ss_sp_list[sccp_db.end_conc_ss_sp]))

/* Macros to set fields of subsystems */
#define SET_SS_CONFIGURED(p_ss)  ((p_ss)->conf_status = SC_CONFIGURED)
#define IS_SS_CONFIGURED(p_ss)   (SC_CONFIGURED == (p_ss)->conf_status)
#define SET_SS_NOT_CONFIGURED(p_ss)  ((p_ss)->conf_status = SC_NOT_CONFIGURED)
#define SET_SP_OF_SS(p_ss, p_sp)     ((p_ss)->sp_id = (sp_id_t)GET_ID_FROM_SP(p_sp))
#define SET_SS_SSN(p_ss, subsystem_number)  ((p_ss)->ssn = (subsystem_number))
#define SET_NEXT_SS(p_ss, p_next_ss)  ((p_ss)->next_ss_id = GET_ID_FROM_SS(p_next_ss))
#define SET_CSS_LIST(p_ss, p_byte)    ((p_ss)->css_list_idx = BYTEID_FROM_PTR(p_byte))
#define SET_CSP_LIST(p_ss, p_byte)    ((p_ss)->csp_list_idx = BYTEID_FROM_PTR(p_byte))
#define SET_NUM_CSS(p_ss, num_conc_ss)  ((p_ss)->num_css = (ss_id_t)(num_conc_ss))
#define SET_NUM_CSP(p_ss, num_conc_sp)  ((p_ss)->num_csp = (sp_id_t)(num_conc_sp))

#define GET_SP_OF_SS(p_ss)     (GET_SP_FROM_ID((p_ss)->sp_id))
#define GET_SS_NW_ID(p_ss)     (GET_SP_NW_ID(GET_SP_OF_SS(p_ss)))
#define IS_SS_LOCAL(p_ss)      (IS_SP_LOCAL(GET_SP_OF_SS(p_ss)))
#define GET_SS_SSN(p_ss)       ((p_ss)->ssn)
#define GET_NEXT_SS(p_ss)      (GET_SS_FROM_ID((p_ss)->next_ss_id))
#define GET_CSS_LIST(p_ss)     ((U8bit *)(&sccp_db.conc_ss_sp_list[(p_ss)->css_list_idx]))
#define GET_CSS_FROM_LIST(p_byte) (sccp_db_get_css_from_list(p_byte))
#define GET_NEXT_CSS_FROM_LIST(p_byte) (p_byte + SIZEOF_SS_ID_T)
#define GET_CSP_FROM_LIST(p_byte)  (sccp_db_get_csp_from_list(p_byte))
#define GET_NEXT_CSP_FROM_LIST(p_byte) (p_byte + SIZEOF_SP_ID_T)
#define GET_CSP_LIST(p_ss)     ((U8bit *)(&sccp_db.conc_ss_sp_list[(p_ss)->csp_list_idx]))
#define GET_NUM_CSS(p_ss)      ((p_ss)->num_css)
#define GET_NUM_CSP(p_ss)      ((p_ss)->num_csp)
#define GET_CSS(p_byte)

#define MIN_VALID_SSN 2

#define CSS_SPACE_EXISTS()    ((sccp_db.end_conc_ss_sp + SIZEOF_SS_ID_T) < \
                               SIZEOF_C_SS_SP_ARRAY)

#define CSP_SPACE_EXISTS()    ((sccp_db.end_conc_ss_sp + SIZEOF_SP_ID_T) < \
                               SIZEOF_C_SS_SP_ARRAY)

#define ITU_T_14_BIT_PC  1
#define ANSI_24_BIT_PC   2
#define JAPANESE_16_BIT_PC  3

#define ITU_T_PC_NUM_BITS  14
#define JAPANESE_PC_NUM_BITS  16
#define ANSI_PC_NUM_BITS  24

#define ITU_T_14_BIT_PC_MASK  0x3fff
#define JAPANESE_16_BIT_PC_MASK  0xffff
#define ANSI_24_BIT_PC_MASK   0xffffffL

#define GET_PC_SIZE(nw_id)   ITU_T_14_BIT_PC

#define ITU_T_14_BIT_PC_MAX_VAL 0x3fff
#define ANSI_24_BIT_PC_MAX_VAL  0xffffffL
#define JAPANESE_16_BIT_PC_MAX_VAL  0xffff

#define SC_REMOTE_SP   0
#define SC_PRIMARY_SP	1
#define SC_CAPABILITY_SP	2
#define SC_SECONDARY_SP	3

#endif /* _BS_DBF_H_ */
