/***************************************************************************
**  FILE NAME:
**      sc_mgst.h
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
**  24Jul2002 Salil Agrawal           fixed Spr 9341 
**  28May2001 Rajesh Mehta            increased conn_id to U32Bit if
**                                    SCCP_CONNECTION_ID_CHANGES is defined 
**  24Feb2000 Ramu Kandula            Fixed SPR # 2692
**	06Aug'98 Anil K.				  ANSI Connectionless addedd
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_MGST_H_
#define _SC_MGST_H_

#include "sc_s7gl.h"
#include "sc_dbf.h"
#include "sc_msgst.h"

typedef struct
{
	U8bit nw_id;

	/* Parameters which came from MTP3 in PAUSE/RESUME/STATUS */
	U8bit status;
	U8bit cause;
	U8bit cong_level;
        cluster_t cluster;   /* affected cluster - for GR */


	/* Parameters which are parsed from the SCMG message
	   SSA/SSP, SST, SSC */
	U8bit scmg_msg_type; /* SCMG format identifier (Message type code) */
	U8bit ssn;           /* affected SSN */
	pc_t  pc;            /* affected PC */
	U8bit ss_mult_ind;   /* Subsystem multiplicity indicator */
	U8bit sccp_cong_level; /* Congestion level */

	/* Some extra fields which come in APIs to SCMG */
	U16bit uid;
	/** SPR # 2692 Fix Start **/
	pc_t   informing_pc;
	/** SPR # 2692 Fix End **/

	msg_info_t * p_msg_info;

	sp_entry_t * p_sp;
	ss_entry_t * p_ss;
} scmg_info_t;

#define SCMG_SSN      	   1
/* starts spr 9341 */
#if 0
#ifdef SCCP_CHINESE
#define SCMG_MSG_LEN   6
#else
#define SCMG_MSG_LEN  (( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE) ? 5 : 6)
#endif
#endif /* end of if 0 */

#define SCMG_MSG_LEN  (( (COMPARE_ITU) || (COMPARE_JAPANESE) || (COMPARE_ETSI) ) ? 5 : 6)

/* end spr # 9341 */

#define SCMG_SSC_MSG_LEN   6
#define MAX_SCMG_MSG_LEN   6

#define SCMG_SSA_MSG       1
#define SCMG_SSP_MSG       2
#define SCMG_SST_MSG       3
#define SCMG_SOR_MSG       4
#define SCMG_SOG_MSG       5
#define SCMG_SSC_MSG       6

/* Additional Message supported in ANSI */
#define SCMG_SBR_MSG    0xfd
#define SCMG_SNR_MSG    0xfe
#define SCMG_SRT_MSG    0xff

/* Defines for event alarms */

#define SCCP_SM_OBJECT_SP_FLAG 		0x01
#define SCCP_SM_OBJECT_SS_FLAG 		0x02
#define SCCP_SM_OBJECT_CONN_FLAG 	0x04

#define SCCP_SM_ALL_OBJ_FLAG	(SCCP_SM_OBJECT_SP_FLAG | \
				 SCCP_SM_OBJECT_SS_FLAG | \
				 SCCP_SM_OBJECT_CONN_FLAG)

/* Additional state for object: SP */
#define SP_RESTART              0x00

/* States for object: Connection */
#define CONN_RESET              0x00
#define RESUME_DATA             0x01
#define CONN_CLOSE              0x02

#if 0
/* SPR # 6566 : Fix Start */
/* States for subsystem status */
#define  SCCP_SM_SS_CONFIGURED  0x80
#define  SCCP_SM_SS_REGISTERED	0x40
#define  SCCP_SM_SS_ALLOWED     0x20
/* SPR # 6566 : Fix End */
#endif

/* This structure is used while sending event alarms to SM */

typedef struct
{
#ifdef SCCP_CONNECTION_ID_CHANGES
        U32bit    conn_id;
#else
	U16bit    conn_id;
#endif
    	U8bit     reset_cause;
   	U8bit     originator;
} conn_entry_t;



#define SCCP_INVALID_OBJECT_FLAG(flag) 	((flag != SCCP_SM_OBJECT_SP_FLAG) && \
					 (flag != SCCP_SM_OBJECT_SS_FLAG) && \
					 (flag != SCCP_SM_OBJECT_CONN_FLAG) && \
					  (flag != SCCP_SM_ALL_OBJ_FLAG))

#endif /* _SC_MGST_H_ */
