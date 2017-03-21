/***************************************************************************
**  FILE NAME:
**      sc_sref.h
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
**  02/07/03 Hitesh Sharma            SPR No : 12095 CSR No : 1-621466
**
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_SREF_H_
#define _SC_SREF_H_

#include "sc_stgl.h"
/* Fix for SPR No :12095   CSR No : 1 - 621466 Starts */

#define MAX_SEG_REFS 128 
/* #define MAX_SEG_REFS 10 */

/* Fix for SPR No :12095  CSR No : 1 - 621466  Ends */
#define MAX_SEG      16

struct seg_ref
{
	Boolean busy;

	U8bit * p_data;
	U8bit * p_cur_data;

	U32bit max_data_len; /* Size of p_data which is the allocated buffer */
	U32bit cur_data_size; /* size of currently reassembled data */

	Boolean ret_optn_set;
	U8bit first_seg_len; /* Used to return message */
	pc_t dpc;
	pc_t opc;
	U8bit sls;

	timer_id_t reass_tim; 
	U32bit slr;
	U8bit rem_seg_exp;
	sccp_addr_t cg_addr;
	sccp_addr_t cd_addr;

#ifdef DISTRIBUTED_SCCP
	Boolean	dsccp_seg_ref;

	/* This flag indicates that this segment reference ** is used only to buffer the XUDTs the actual ** reassembly is happening at a mate instance */

	dsccp_instance_id_t dest_inst_id; /* instance where the segments are being
                                      ** being reassembled */
	U8bit	num_xudt_buffered;
	U8bit	*xudt_buffer[14];  /* not more than 14 segments need to 
                                ** be buffered */
#endif

};

extern struct seg_ref seg_ref_table[MAX_SEG_REFS];

#define SCCP_GET_SEG_REF_ID(p_seg_ref) ((p_seg_ref) - &seg_ref_table[0])
#define SCCP_GET_SEG_REF_FROM_ID(seg_ref_id) (&seg_ref_table[(seg_ref_id)])

#define REL_SEG_REF 0x1
#define REL_BUF     0x2
#define STOP_TIMER  0x4

#define T_REASS_TMR_VALUE    (sc_tim.t_reassmbly_timer_val)
#define T_REASS_TMR_BUF_LEN   5

#ifdef DISTRIBUTED_SCCP
#define T_REASS_QUERY_TMR_VALUE    (sc_tim.t_reassmbly_timer_val)
#define T_REASS_QUERY_TMR_BUF_LEN   5
#endif

struct seg_ref * sccp_allocate_seg_ref
	_ARGS_ ((void));

struct seg_ref * sccp_locate_seg_ref 
	_ARGS_ ((msg_info_t * p_info));

void sccp_release_seg_ref 
	_ARGS_ ((struct seg_ref * p_seg_ref));

U32bit sccp_assign_slr 
	_ARGS_ ((void));


#endif /* _SC_SREF_H_ */
