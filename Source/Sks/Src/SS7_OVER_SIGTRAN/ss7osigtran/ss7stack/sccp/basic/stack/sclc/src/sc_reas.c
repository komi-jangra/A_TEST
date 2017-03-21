/***************************************************************************
**  FILE NAME:
**      sc_reas.c
**
****************************************************************************
**
**  FUNCTION:
**      Handles reassembly functionality and reassembly failure (including
**      reassembly timer timeout)
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#             REASON
**  -------  ----------------  --------------  ----------------------------
**  13May2004 Suyash/Ganesh                            Fixed SPR # 13444
**  01Aug2002 Prateek Bidwalkar                 Fixed SPR # 9221
**  28Aug2001 Ramu Kandula                      Modified for DSCCP
**  28Aug2001 Ramu Kandula                      Fixed SPR #6026
**  12Oct2000 Ramu Kandula                      Modified for broadband
**  14Mar2000 Ramu Kandula                      Fixed SPR #2896
**  24Feb2000 Ramu Kandula                      Fixed SPR #2663
**  24Feb2000 Ramu Kandula                      Fixed SPR #2664
**  18Feb2000 Ramu Kandula                      Fixed SPR #2633
**  16Feb2000 Ramu Kandula                      Fixed SPR #2616
**  12Feb2000 Ramu Kandula     SPR #2592		Fixed SPR #2592
**	15Oct'99 Ramu Kandula	   SPR #878			replaced ss7_mem_free with
**												sccp_free
**  29/4/99  Sudipta Pattar    ----------       Fixed SPR 1498
**  3/6/98   Sriganesh. Kini   ITU-714/713      Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/


#include "sc_stgl.h"
#include "sc_sref.h"
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */

/*****************************************************************************
**
** DATA STRUCTURE : seg_ref_table
**
*****************************************************************************/

struct seg_ref seg_ref_table[MAX_SEG_REFS];


#if 0 /* These definitions have been moved to sc_sref.h */
#define REL_SEG_REF	0x1
#define REL_BUF		0x2
#define STOP_TIMER	0x4

#define T_REASS_TMR_VALUE    (sc_tim.t_reassmbly_timer_val)
#define T_REASS_TMR_BUF_LEN   5
#endif

/*****************************************************************************
**
**      FUNCTION : sccp_reassemble
**            
******************************************************************************
**
**      DESCRIPTION :
**          The processing in this function corresponds to
**          Q.714/C.12/sheet-2 on the node 2
**      
**          This function does the following :
**          (1) Finds calling segment reference
**          (2) If segment reference is idle and the segment is the first
**              segment;
**              a. Allocate the segment reference
**              b. Allocate space for reassembly
**              c. Start reassembly timer for the segment reference
**          (3) If segment reference is busy then store the message
**              If the last segment has been received call
**              sccp_build_n_unitdata_ind_api to send SCCP_N_UNITDATA_INDICATION
**              api to higher layer.
**          (4) For all error cases call sccp_handle_reass_failure
**          
**      RETURNS :
**          SS7_SUCCESS/SS7_FAILURE depending whether reassembly succeeded or failed
**
*****************************************************************************/
void
sccp_reassemble 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info;
#endif
{
	struct seg_ref * p_seg_ref = SS7_NULL;
	error_t ecode;
	U8bit reass_tmr_buf[T_REASS_TMR_BUF_LEN];
	U32bit seg_ref_id;

#ifdef SCCP_BROADBAND
	/* Reassembly of LUDT is not supported - Initiate message 
	** procedure  if segmented LUDT is received
	*/
	if (LUDT_MSG_TYPE == p_info->msg_type)
	{
		CL_TRC (("SCCP::SCLC: Reassembly of LUDT not supported !! \n"));
/* SPR # 9221 Fix Start */
		SC_STAT_Q752_TS_SEG_FAILED;
		SC_STAT_Q752_INR_SEG_FAILED;
/* SPR # 9221 Fix End */
		if (p_info->segment.f_bit)
		{	
			CL_TRC (("SCCP::SCLC: 1st segment - invoking msg return proc !\n"));
			p_info->ret_cause = SCCP_DESTN_CANNOT_PERFORM_REASSEMBLY;
			sccp_handle_reass_failure (p_info, p_seg_ref, 0);
		}
		else
		{
			CL_TRC (("SCCP::SCLC: not 1st segment - discarding msg !\n"));
		}
		return;
	}
#endif

	/** SPR # 2592 Fix Start **/
	/** XUDT msgs with protocol class != 1 must be discarded or 
	*** returned
	**/
	
	if (PROTOCOL_CLASS_1 != (p_info->proto_class & 0xf))
	{
		CL_TRC (("SCCP::SCLC: XUDT msg with protocol class != 1;"
		         " Reassembly failed\n"));
		/** SPR #2616 Fix Start **/
		p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
		/** SPR #2616 Fix End **/
		sccp_handle_reass_failure (p_info, p_seg_ref, 0);
		return;
	}
	/** SPR # 2592 Fix End **/

	p_seg_ref = sccp_locate_seg_ref (p_info);

	if (SS7_NULL == p_seg_ref)
	{
		/* Segment reference Idle */

		/** SPR #2633 Fix Start **/
		if ( ! (1 == p_info->segment.f_bit))
		{
#ifdef DISTRIBUTED_SCCP
			if (p_info->dsccp_mate_api == SS7_FALSE)
			{
				dsccp_process_xudt_from_nw(p_info, SS7_NULL);
				return;
			}
			else 
			{
			/*	message received from mate is out-of-sequence; most probably
			**	T-Reass timer had expired and the seg ref was released !
			**	invoking reass-failure procedure as in the normal SCCP 
			*/
#endif
            	CL_TRC (("SCCP::SCLC: error in "
               			"message - F bit not set\n"));
                                /* spr fix 9688 starts */
                                SC_STAT_Q752_TS_SEG_OUT_OF_SEQ;
                                SC_STAT_Q752_INR_SEG_OUT_OF_SEQ;
                                /* spr fix 9688 ends */

				p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
				sccp_handle_reass_failure (p_info, p_seg_ref, 0);
				return;
#ifdef DISTRIBUTED_SCCP
			}
#endif
		}
		/** SPR #2633 Fix Contd. **/

		/* Allocate seg ref */
		p_seg_ref = sccp_allocate_seg_ref ();
		/* Failed to allocate seg ref */
		if (SS7_NULL == p_seg_ref)
		{
			CL_TRC (("SCCP::SCLC: failed to "
			         "allocated segment reference\n"));
			/** SPR #2616 Fix Start **/
                        SC_STAT_Q752_TS_NO_BUFF_LEFT;
                        SC_STAT_Q752_INR_NO_BUFF_LEFT;
			p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING;
			/** SPR #2616 Fix End **/
			sccp_handle_reass_failure (p_info, p_seg_ref, 0);
			return;
		}

		p_seg_ref->busy = SS7_TRUE;
		/* copy fields into seg ref */
		p_seg_ref->max_data_len = p_info->data.len *
		                          (p_info->segment.rem_seg + 1);
		p_seg_ref->rem_seg_exp = p_info->segment.rem_seg - 1;

		p_seg_ref->p_cur_data = p_info->data.p;

		/* Copy calling addr */
		sccp_copy_sccp_addr (&p_info->cg_addr, &p_seg_ref->cg_addr);

		/* copy called addr */
		sccp_copy_sccp_addr (&p_info->cd_addr, &p_seg_ref->cd_addr);

		p_seg_ref->slr = p_info->segment.slr;

		/* MTP routing label */
		p_seg_ref->opc = p_info->opc;
		p_seg_ref->dpc = p_info->dpc;
		p_seg_ref->sls = p_info->sls;

		/* SPR 9404  - Fix Start */
		/*p_seg_ref->first_seg_len = p_info->data.len;*/
		p_seg_ref->first_seg_len = (U8bit)p_info->data.len;
		/* SPR 9404  - Fix End   */

		if (p_info->proto_class & RET_OPTN_MASK)
			p_seg_ref->ret_optn_set = SS7_TRUE;
		else
			p_seg_ref->ret_optn_set = SS7_FALSE;

		/** SPR # 2633 Fix Contd. **/
		/* Moved this code up so the f-bit is checked before seg_ref is alloctated
		** and hence there is no need to release  the segref in case of failure
		*/
#if 0
		if ( ! (1 == p_info->segment.f_bit))
		{
                        CL_TRC (("SCCP::SCLC: error in "
                                 "message - F bit not set\n"));

			p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
			sccp_handle_reass_failure (p_info, p_seg_ref,
			                           REL_SEG_REF);
			return;
		}
#endif
		/** SPR # 2633 Fix End **/

		if (0 == p_info->segment.rem_seg)
		{
			/** SPR # 2663 Fix Start **/
			if (p_info->segment.isdo)
				p_info->proto_class = PROTOCOL_CLASS_1;
			else
				p_info->proto_class = PROTOCOL_CLASS_0;
			if (p_seg_ref->ret_optn_set)
				p_info->proto_class |= RET_OPTN_MASK;
			/** SPR # 2663 Fix End **/
			sccp_build_n_unitdata_ind_api(p_info);
			sccp_release_seg_ref(p_seg_ref);
		}

		/* Reserve space for reassembly */
		if (SS7_NULL == (p_seg_ref->p_data = sccp_malloc
		    (p_info->data.len * (p_info->segment.rem_seg + 1))))
		{
                        SC_STAT_Q752_TS_NO_BUFF_LEFT;
                        SC_STAT_Q752_INR_NO_BUFF_LEFT;
			p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
			sccp_handle_reass_failure
				(p_info, p_seg_ref, REL_SEG_REF);
			return;
		}

		sccp_memcpy (p_seg_ref->p_data, p_info->data.p,
		             p_info->data.len);
		p_seg_ref->cur_data_size = p_info->data.len;
		p_seg_ref->p_cur_data = p_seg_ref->p_data + p_info->data.len;

		seg_ref_id = (U32bit)SCCP_GET_SEG_REF_ID(p_seg_ref);
		reass_tmr_buf[0] = T_REASSEMBLY_TIMER_ID;
		reass_tmr_buf[1] = (U8bit)seg_ref_id;
		reass_tmr_buf[2] = (U8bit)(seg_ref_id >> 8);
		reass_tmr_buf[3] = (U8bit)(seg_ref_id >> 16);
		reass_tmr_buf[4] = (U8bit)(seg_ref_id >> 24);

		if (SS7_FAILURE == ss7_start_timer (T_REASS_TMR_VALUE,
		    reass_tmr_buf, 5, SCCP_MODULE_ID,
		    &p_seg_ref->reass_tim, &ecode))
		{
			/* SPR #6026 Fix Start */
			/* This code has been removed because p_seg_ref->p_data is
			** is needed in sccp_handle_reass_failure() subsequently and
			** p_seg_ref is released in sccp_handle_reass_failure()
			*/
#if 0
			/* Release buf */
			sccp_free (p_seg_ref->p_data);
			sccp_release_seg_ref(p_seg_ref);
#endif
			/* SPR #6026 Fix End */

			SC_STAT_Q752_TS_NW_CONGESTION;
			SC_STAT_Q752_INR_NW_CONGESTION;

			p_info->ret_cause = SCCP_NETWORK_CONGESTION;
			sccp_handle_reass_failure (p_info, p_seg_ref,
			                           REL_SEG_REF | REL_BUF);
		}
	}
	else
	{
		/* Segment reference Busy */
#ifdef DISTRIBUTED_SCCP
		if (p_seg_ref->dsccp_seg_ref == SS7_TRUE)
		{
			dsccp_process_xudt_from_nw(p_info, p_seg_ref);
			return;
		}
#endif

		/* Check if segment order is correct */
		if (p_info->segment.rem_seg != p_seg_ref->rem_seg_exp)
		{
			p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;

/* SPR # 9221 Fix Start */
			SC_STAT_Q752_TS_SEG_OUT_OF_SEQ;
			SC_STAT_Q752_INR_SEG_OUT_OF_SEQ;
/* SPR # 9221 Fix End */
			sccp_handle_reass_failure (p_info, p_seg_ref,
			             REL_SEG_REF | REL_BUF | STOP_TIMER);
            return;
		}

		/* Check if F bit is incorrect */
		if (1 == p_info->segment.f_bit)
		{
                       CL_TRC (("SCCP::SCLC: error in "
                                 "message - F bit set\n"));
                       /* spr fix 9674 starts */
                        SC_STAT_Q752_TS_SEG_OUT_OF_SEQ;
                        SC_STAT_Q752_INR_SEG_OUT_OF_SEQ;
                       /* spr fix 9674 ends */
			p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
			sccp_handle_reass_failure (p_info, p_seg_ref,
			        REL_SEG_REF | REL_BUF | STOP_TIMER);
            return ;
		}

		/* Check if space is available in buffer */
		if ((p_seg_ref->p_cur_data + p_info->data.len) >
		    (p_seg_ref->p_data + (U16bit)p_seg_ref->max_data_len))
		{
			p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;

/* SPR # 9221 Fix Start */
			SC_STAT_Q752_TS_NO_BUFF_LEFT;
			SC_STAT_Q752_INR_NO_BUFF_LEFT;
/* SPR # 9221 Fix End */

			sccp_handle_reass_failure (p_info, p_seg_ref,
			          REL_SEG_REF | REL_BUF | STOP_TIMER);
            return;
		}

		sccp_memcpy (p_seg_ref->p_cur_data, p_info->data.p,
		             p_info->data.len);
		p_seg_ref->cur_data_size += p_info->data.len;

		p_seg_ref->p_cur_data += p_info->data.len;

		p_seg_ref->rem_seg_exp --;

		if (0 == p_info->segment.rem_seg)
		{
			ss7_stop_timer (p_seg_ref->reass_tim, &ecode);
			p_info->data.len = p_seg_ref->cur_data_size;
			p_info->data.p = p_seg_ref->p_data;
			/** SPR # 2663 Fix Start **/
			if (p_info->segment.isdo)
				p_info->proto_class = PROTOCOL_CLASS_1;
			else
				p_info->proto_class = PROTOCOL_CLASS_0;
			if (p_seg_ref->ret_optn_set)
				p_info->proto_class |= RET_OPTN_MASK;
			/** SPR # 2663 Fix End **/
			sccp_build_n_unitdata_ind_api(p_info);
			sccp_free(p_seg_ref->p_data);
			sccp_release_seg_ref(p_seg_ref);
		}
	}
}

/*****************************************************************************
**
**      FUNCTION : sccp_handle_reass_failure
**            
******************************************************************************
**
**      DESCRIPTION :
**          The processing in this function corresponds to
**          Q.714/C.12/sheet-3 on the node 4
**      
**          This function does the following :
**          (1) If return option is set select user data to return and
**              call sccp_route_CL_msg to send the XUDTS message
**          (2) Release resources (segment reference and memory) and
**              stop T reassembly timer.
**          (3) Indicate to OMAP about Re-assembly failure
**          
**      RETURNS :
**          SS7_SUCCESS/SS7_FAILURE depending on the values returned by the function
**          it calls.
**
*****************************************************************************/
void
sccp_handle_reass_failure
#ifdef ANSI_PROTO
	(msg_info_t 	* p_info,
	 struct seg_ref * p_seg_ref,
	 U8bit 		status)
#else
	(p_info, p_seg_ref, status)
	msg_info_t 	* p_info;
	struct seg_ref 	* p_seg_ref;
	U8bit 		status;
#endif
{
	Boolean msg_ret;


	if(p_seg_ref == SS7_NULL)
	{
	    CL_TRC (("SCCP::SCLC: Checking whether p_seg_ref is NULL\n"));
		return;
	}
	if (status & REL_SEG_REF)
		msg_ret = p_seg_ref->ret_optn_set;
	else
	{
		(p_info->proto_class & RET_OPTN_MASK) ? (msg_ret = SS7_TRUE) :
		                                        (msg_ret = SS7_FALSE);
	}

	/* Select user data to return */
	if (status & REL_BUF)
	{
		p_info->data.p = p_seg_ref->p_data;
#ifdef RETURN_FULL_MSG
		p_info->data.len = p_seg_ref->p_cur_data - p_seg_ref->p_data;
#else /* Return only first segment */
		p_info->data.len = p_seg_ref->first_seg_len;
#endif
	}

	if (msg_ret)
	{
		sccp_addr_t tmp_addr;

		/* Swap addresses */
		sccp_copy_sccp_addr (&p_info->cd_addr, &tmp_addr);
		sccp_copy_sccp_addr (&p_info->cg_addr, &p_info->cd_addr);
		sccp_copy_sccp_addr (&tmp_addr, &p_info->cg_addr);

		/* SPR 9404 - Fix Start */
		/******
		p_info->sls = sccp_assign_sls (&p_info->cg_addr,
		                               &p_info->cd_addr, p_info->sls,
		                               p_info->proto_class & 0xf);*****/
		/* Fix for SPR No: 13444 start */
		/*p_info->sls = sccp_assign_sls (&p_info->cg_addr,
		                               &p_info->cd_addr, p_info->sls,
		                               (U8bit)(p_info->proto_class & 0xf));*/
		/* Fix for SPR No: 13444 stop */
		/* SPR 9404 - Fix End   */
#ifdef SCCP_BROADBAND
		if (LUDT_MSG_TYPE == p_info->msg_type)
		{
			p_info->msg_type = LUDTS_MSG_TYPE;
			p_info->segment.slr = sccp_assign_slr() ;
			p_info->segment.rem_seg = 0 ;
			p_info->segment.f_bit = 1 ;
			SET_SEGMENTATION_PRESENT (p_info) ;
		}
		else
#endif
		{
			p_info->msg_type = XUDTS_MSG_TYPE;
                  if (status & REL_BUF)
                  {
                        /* Set 1st bit since we are returning 1st bit */
                        p_info->segment.f_bit = 1;
                  }
		}

		/** SPR # 2664 Fix Start **/
		p_info->hop_counter = INITIAL_HOP_COUNTER_VALUE;
		/** SPR # 2664 Fix end **/

		sccp_route_cl_msg (p_info);
	}
	else
                CL_TRC (("SCCP::SCLC: Return option not set\n"));


	if (status & REL_SEG_REF)
	{
 
	
		if (status & REL_BUF)	/* This line is added to fix SPR #6026 */
			sccp_free(p_seg_ref->p_data);
		if (status & STOP_TIMER)
			sccp_stop_timer (&p_seg_ref->reass_tim);
		sccp_release_seg_ref (p_seg_ref);
	}
}

/*****************************************************************************
**
**      FUNCTION : sccp_handle_t_reassembly_timeout
**            
******************************************************************************
**
**      DESCRIPTION :
**          The processing in this function corresponds to
**          Q.714/C.12/sheet-5 on the event 
**          T_reassembly
**      
**          This function does the following :
**          (1) Call sccp_parse_n_unitdata_req_api to parse the API
**          (2) Assigns the SLS
**          (3) Calls the SCRC function sccp_route_CL_msg to route the message.
**          
**      RETURNS :
**          SS7_SUCCESS/SS7_FAILURE depending on the values returned by the function
**          it calls.
**
*****************************************************************************/
void
sccp_handle_t_reassembly_timeout
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
	U32bit seg_ref_id;
	struct seg_ref * p_seg_ref;
	msg_info_t info, * p_info = &info;

	p_info->flag = 0;
	p_info->p_api = p_api;

	p_api += API_HEADER_LEN;

	CL_TRC (("SCCP::SCLC: T reassembly timeout\n"));

	seg_ref_id = (p_api[1] | (p_api[2] << 8) |
	             (p_api[3] << 16) | (p_api[4] << 24));
	p_seg_ref = SCCP_GET_SEG_REF_FROM_ID(seg_ref_id);

	if (! p_seg_ref->busy) return;

	if (p_seg_ref->ret_optn_set)
	{
		/* p_info to be built here */
		p_info->msg_type = XUDTS_MSG_TYPE;
		sccp_copy_sccp_addr (&p_seg_ref->cg_addr, &p_info->cd_addr);
		sccp_copy_sccp_addr (&p_seg_ref->cd_addr, &p_info->cg_addr);
		p_info->opc = p_seg_ref->opc;
		p_info->dpc = p_seg_ref->dpc;
		/** SPR # 2896 Fix Start **/
		p_info->nw_id = DEFAULT_NW_ID;
		/** SPR # 2896 Fix End **/
               /** SPR # 9669 Fix Start **/ 
		p_info->ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
               /** SPR # 9669 Fix ends  **/ 
	 	
		/* SPR 1498: fill hop counter value */
                p_info->hop_counter = INITIAL_HOP_COUNTER_VALUE;

		if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (DEFAULT_NW_ID, p_info->opc)))
		{
			CL_TRC (("SCCP::SCLC: Unknown pc %u\n", p_info->opc));
			sccp_free (p_seg_ref->p_data);
			sccp_release_seg_ref (p_seg_ref);
			return;
		}

		/* SPR 9404 - Fix Start */
		/*****
		p_info->sls = sccp_assign_sls (&p_info->cd_addr,
		                               &p_info->cg_addr, p_info->sls,
		                               p_info->proto_class & 0xf);*********/
		/* SPR 13444 - fix Start */
		/*p_info->sls = sccp_assign_sls (&p_info->cd_addr,
		                               &p_info->cg_addr, p_info->sls,
		                               (U8bit)(p_info->proto_class & 0xf));*/
        /*        p_info->sls = sccp_assign_sls (&p_info->cg_addr,
                                               &p_info->cd_addr, p_info->sls,
                                               (U8bit)(p_info->proto_class & 0xf));*/
		/* SPR 13444 - fix Stop */

		/* SPR 9404 - Fix End   */

		p_info->data.p = p_seg_ref->p_data;

#ifdef RETURN_FULL_MSG
		p_info->data.len = p_seg_ref->cur_data_size;
#else
		p_info->data.len = p_seg_ref->first_seg_len;
#endif

		sccp_route_cl_msg (p_info);
	}

/* SPR # 9221 Fix Start */
	SC_STAT_Q752_TS_T_REASS_EXPIRY;
	SC_STAT_Q752_INR_T_REASS_EXPIRY;
/* SPR # 9221 Fix End */

	sccp_free (p_seg_ref->p_data);
	sccp_release_seg_ref (p_seg_ref);
}

