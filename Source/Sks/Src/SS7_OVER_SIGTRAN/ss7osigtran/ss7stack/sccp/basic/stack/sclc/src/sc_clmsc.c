/***************************************************************************
**  FILE NAME:
**      sc_clmsc.c
**
****************************************************************************
**
**  FUNCTION:
**      This file contains miscellaneous functions required by SCLC
**
**  DESCRIPTION:
**      It contains functions related to
**      1. Allocation/Deallocation/Search of segment reference
**      2. Assigning SLR
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24Oct'01 Prateek B. 			  Fixed SPR 6750
**  06Aug'98 Anil K.				  Connectionless ANSI added
**           Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

#include "sc_sref.h"

extern U8bit sccp_state; 
/*****************************************************************************
**
**      FUNCTION : sccp_locate_seg_ref
**            
******************************************************************************
**
**      DESCRIPTION :
**          This function does a linear search for the desired segment
**          reference
**      
**      RETURNS :
**          Address of the segment reference if it is found. SS7_NULL otherwise.
**
*****************************************************************************/
struct seg_ref *
sccp_locate_seg_ref 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info;
#endif
{
	U8bit i;

	for (i=0; i < MAX_SEG_REFS; i++)
	{
		if ( ! seg_ref_table[i].busy) continue;

		if ((p_info->opc == seg_ref_table[i].opc) &&
		    (p_info->dpc == seg_ref_table[i].dpc) &&
		    (p_info->sls == seg_ref_table[i].sls) &&
		    (p_info->segment.slr == seg_ref_table[i].slr))
		{

			/* compare calling address */
			if ((p_info->cg_addr.pc_ind == seg_ref_table[i].cg_addr.pc_ind) &&
			    (p_info->cg_addr.ssn_ind == seg_ref_table[i].cg_addr.ssn_ind) &&
			    (p_info->cg_addr.gti == seg_ref_table[i].cg_addr.gti))
			{
				if ((p_info->cg_addr.pc_ind) &&
				    (! (p_info->cg_addr.pc == seg_ref_table[i].cg_addr.pc)))
					continue;

				if ((p_info->cg_addr.ssn_ind) &&
				    (! (p_info->cg_addr.ssn == seg_ref_table[i].cg_addr.ssn)))
					continue;

				/* compare gt */

				return &seg_ref_table[i];
			}
		}
	}

	return (struct seg_ref *)SS7_NULL;
}

/*****************************************************************************
**
**      FUNCTION : sccp_allocate_seg_ref
**            
******************************************************************************
**
**      DESCRIPTION :
**          The 
**      
**      RETURNS :
**          Address of the segment reference if a free segment reference is
**          found. SS7_NULL if none is found.
**
*****************************************************************************/
struct seg_ref *
sccp_allocate_seg_ref
#ifdef ANSI_PROTO
	(void)
#else
 	()
#endif
{
	U8bit i;

	for (i=0; i < MAX_SEG_REFS; i++)
	{
		if ( ! seg_ref_table[i].busy)
			return &seg_ref_table[i];
	}

	return (struct seg_ref *)SS7_NULL;
}

/*****************************************************************************
**
**      FUNCTION : sccp_init_seg_ref_table
**            
******************************************************************************
**
**      DESCRIPTION :
**          The 
**      
**      RETURNS :
**          Iniitalizes the segment reference table.
**
*****************************************************************************/
void
sccp_init_seg_ref_table
#ifdef ANSI_PROTO
	(void)
#else
	()
#endif
{
	U8bit i;

	for (i=0; i < MAX_SEG_REFS; i++)
	{
		seg_ref_table[i].busy = SS7_FALSE;
	}
}

/*****************************************************************************
**
**      FUNCTION : sccp_release_seg_ref
**            
******************************************************************************
**
**      DESCRIPTION :
**          The 
**      
**      RETURNS :
**          Turns off the busy bit of the segment reference.
**
*****************************************************************************/
void
sccp_release_seg_ref 
#ifdef ANSI_PROTO
	(struct seg_ref * p_seg_ref)
#else
	(p_seg_ref)
	struct seg_ref * p_seg_ref;
#endif
{
#ifdef DISTRIBUTED_SCCP
	U8bit i;
#endif

	p_seg_ref->busy = SS7_FALSE;

#ifdef DISTRIBUTED_SCCP
	if (p_seg_ref->dsccp_seg_ref)
	{
		for (i=0; i<p_seg_ref->num_xudt_buffered; ++i)
		{
			sccp_free (p_seg_ref->xudt_buffer[i]);
			p_seg_ref->xudt_buffer[i] = SS7_NULL;
		}
		p_seg_ref->num_xudt_buffered = 0;
		p_seg_ref->dsccp_seg_ref = SS7_FALSE;
	}
#endif
}

/*****************************************************************************
**
**      FUNCTION : sccp_assign_slr
**            
******************************************************************************
**
**      DESCRIPTION :
**          The 
**      
**      RETURNS :
**          The newly allocated SLR
**
*****************************************************************************/
U32bit
sccp_assign_slr 
#ifdef ANSI_PROTO
	(void)
#else
	()
#endif
{
	/*static U32bit slr = 0; 
	** Using the global variable segmentation_local_ref instead
	*/

extern U32bit segmentation_local_ref; /* defined in sc_segm.c */

/* SPR # 6750 Fix Start */
#if 0
	U32bit tmp_slr;
	U32bit slr_mask;
	U8bit  nbits;
	U8bit  instance_id;

	extern U32bit segmentation_local_ref; /* defined in sc_segm.c */

#ifdef DISTRIBUTED_SCCP
	nbits = sc_opt.num_of_bits_instance_id;
	instance_id = sc_opt.dsccp_local_instance_id;
#else
	nbits = 0;
	instance_id = 0;
#endif

	slr_mask = ~(0xffffffff << (24 - nbits));
	tmp_slr = (segmentation_local_ref+1) & slr_mask;
	segmentation_local_ref = tmp_slr | (instance_id << (24 - nbits));
#endif /*if 0 */




#ifdef DISTRIBUTED_SCCP
	U32bit tmp_slr;
	U32bit slr_mask;
	U8bit  nbits;
	U8bit  instance_id;

	nbits = sc_opt.num_of_bits_instance_id;
	instance_id = sc_opt.dsccp_local_instance_id;

	slr_mask = ~(0xffffffff << (24 - nbits));
	tmp_slr = (segmentation_local_ref+1) & slr_mask;
	segmentation_local_ref = tmp_slr | (instance_id << (24 - nbits));
#else
	U32bit slr;

	slr = segmentation_local_ref;
	segmentation_local_ref ++;
	if(segmentation_local_ref > 0x00ffffffL)
			segmentation_local_ref  = 0;
#endif
/* SPR # 6750 Fix End */

	CL_TRC (("SCCP::SCLC: assigned SLR %u\n", segmentation_local_ref));
	SCCP_SEND_SCLC_ENTRY_UPDATE(segmentation_local_ref);

	return segmentation_local_ref;
}
