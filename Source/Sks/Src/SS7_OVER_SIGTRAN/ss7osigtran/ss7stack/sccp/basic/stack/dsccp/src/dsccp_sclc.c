/***************************************************************************
**
**  FILE NAME:
**      dsccp_sclc.c
**
****************************************************************************
**
**  FUNCTION:
**		1. Contains functions to handle SCLC category APIs for mate DSCCPs
**		2. Contains functions needed to handle the modified DSCCP reassembly 
**		   procedure. 
**		3. Contains functions to build and send SCLC category APIs to mates
**
**  DESCRIPTION:
**
**
**  DATE      NAME              REF#   REASON
**  -------   ----------------  -----  -------------------------------------
**  24Aug2001 Ramu Kandula             Original
**  24October2001 Prateek Bidwalkar        Fixed SPR 6750
**  31October2001 Pawanish Modi        changes for CLass 1 and 3
**  05Nov2001 Pawanish Modi        Added new stats for DSCCP
**  22Jan2002 Prateek Bidwalkar		Fixed SPR 7470
**  19Jun2002 Suyash Tripathi  		Fixed SPR 9001/8985
**
**  Copyright 2001, Hughes Software Systems
**
***************************************************************************/

/* SPR # 6750 Fix Start */
#include "sc_stgl.h"
/* SPR # 6750 Fix End */

#ifdef DISTRIBUTED_SCCP
/* SPR # 6750 Fix Start */
#if 0
#include "sc_stgl.h"
#endif
/* SPR # 6750 Fix End */

#include "sc_sref.h"
#include "dsccp.h"
#include "dsccp_proc.h"
#ifdef DSCCP_STATS_ENABLED
#include "dsccp_stats.h"
#endif

/* SPR # 7470 Fix Start */
dsccp_class1_buff_node * dsccp_cls1_buf_inh_list_head ;
dsccp_class1_buff_node * dsccp_cls1_buf_inh_list_tail ;
extern U8bit	dsccp_class1_timer_status;
/* SPR # 7470 Fix End */

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_process_sclc_cat_msg
**       
****************************************************************************
**
**	DESCRIPTION:
**	This is the top level function for processing SCLC category messages
**	received from mate DSCCP instances.
**
**	NOTE :
**
***************************************************************************/

return_t 
dsccp_process_sclc_cat_msg
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	return_t	result = SS7_SUCCESS;
	U8bit		command;

	command = p_api[DSCCP_CMD_OFFSET];
	switch (command)
	{
	case DSCCP_API_CMD_SCLC_REASS_INFO_REQ:
		result = dsccp_process_reass_info_req(p_api);
		break;

	case DSCCP_API_CMD_SCLC_REASS_INFO_RESP:
		result = dsccp_process_reass_info_resp(p_api);
		break;

	case DSCCP_API_CMD_SCLC_XUDT:
		result = dsccp_process_xudt_from_mate (p_api);
		break;
	default:
		result = SS7_FAILURE;
		break;
	}

	return result;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_process_reass_info_req
**       
****************************************************************************
**
**	DESCRIPTION:
**	This funcion handles the DSCCP_API_CMD_SCLC_REASS_INFO_REQ command from
**	a mate instance. It searchs the reassembly table and if it finds an 
**	entry that corresponds to the data contained in the command, then it
**	responds to this API by sending the DSCCP_API_CMD_SCLC_REASS_INFO_RESP
**	command.
**
**	NOTE :
**
***************************************************************************/

return_t 
dsccp_process_reass_info_req
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	return_t	result = SS7_SUCCESS;
	dsccp_instance_id_t		instance_id;
	msg_info_t	info;
	U8bit		offset;
	U8bit		i;
	U32bit		src_ref; 
	struct seg_ref	*p_seg_ref;
	
	/** Extract the elems from the command **/

	offset = DSCCP_DATA_OFFSET;

	instance_id = p_api [offset++];

	/* DSCCP seg ref at the sending instance; this will be copied to the 
	** response */
	src_ref = p_api [offset] |
		  (p_api [offset+1] << 8) | 
		  (p_api [offset+2] << 16) | 
		  (p_api [offset+3] << 24);
	offset += 4;
	info.opc = p_api [offset] |
		  (p_api [offset+1] << 8) | 
		  (p_api [offset+2] << 16) | 
		  (p_api [offset+3] << 24);
	offset += 4;

	info.dpc = p_api [offset] |
		  (p_api [offset+1] << 8) | 
		  (p_api [offset+2] << 16) | 
		  (p_api [offset+3] << 24);
	offset += 4;

	info.sls = p_api [offset++];

	info.segment.slr = p_api [offset] |
		  (p_api [offset+1] << 8) | 
		  (p_api [offset+2] << 16);
	offset += 3;

	info.cg_addr.pc_ind = p_api[offset++];
	info.cg_addr.ssn_ind = p_api[offset++];
	info.cg_addr.gti = p_api[offset++];
	info.cg_addr.rout_ind = p_api[offset++];
	if (info.cg_addr.pc_ind)
	{
		info.cg_addr.pc = p_api [offset] |
		  	(p_api [offset+1] << 8) | 
		  	(p_api [offset+2] << 16) | 
		  	(p_api [offset+3] << 24);
	    offset += 4;
	}
	if (info.cg_addr.ssn_ind)
		info.cg_addr.ssn = p_api [offset++];
	if (info.cg_addr.gti)
	{
		info.cg_addr.gt_len = p_api [offset++];
		for (i=0; i<info.cg_addr.gt_len; ++i)
			info.cg_addr.gt[i] = p_api [offset++];
	}

	/* Search for Segment reference and send Reass-Info-Resp if corresponding
	** segment reference is found
	*/
	if ((p_seg_ref = sccp_locate_seg_ref(&info)) != SS7_NULL)
	{
		if (p_seg_ref->dsccp_seg_ref)
		{
			/* Do not respond if the segment reference is a dsccp seg ref
			** as the reassembly is not being done here but in some other
			** instance; This case would occur in the extremely rare scenario
			** in which there is more that one change-over in MTP3 links in 
			** quick succession.
			*/
		}
		else
		{
			dsccp_build_and_send_reass_info_resp (instance_id, src_ref);
		}
	}
	return result;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_process_reass_info_resp
**       
****************************************************************************
**
**	DESCRIPTION:
**	This funcion handles the DSCCP_API_CMD_SCLC_REASS_INFO_RESP command from
**	a mate instance. It sends all the buffered XUDT segments to the mate that
**	has sent the command
**
**	NOTE :
**
***************************************************************************/

return_t 
dsccp_process_reass_info_resp
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	return_t	result = SS7_SUCCESS;
	dsccp_instance_id_t		instance_id;
	U8bit		offset;
	struct seg_ref *p_seg_ref;
	
	/** Extract the elems from the command **/
	offset = DSCCP_DATA_OFFSET;
	instance_id = p_api [offset++]; /* responding instance id */
	p_seg_ref = (struct seg_ref*)(Ulong)((p_api[offset] |
					(p_api [offset+1] << 8) | 
					(p_api [offset+2] << 16) | 
					(p_api [offset+3] << 24)));
    offset +=4 ;
	if ((p_seg_ref->busy) && (p_seg_ref->dsccp_seg_ref))
	{
		p_seg_ref->dest_inst_id = instance_id;
		sccp_stop_timer(&(p_seg_ref->reass_tim));
		dsccp_build_and_send_all_buffered_xudt (instance_id, p_seg_ref);
	}
	
	return result;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_process_xudt_from_mate
**       
****************************************************************************
**
**	DESCRIPTION:
**	This function handles the XUDT messages sent by the mate. The mate sends
**	these segments on receiving the DSCCP_API_CMD_SCLC_REASS_INFO_RESP cmd
**	from this instance. 
**
**	NOTE :
**
***************************************************************************/

return_t 
dsccp_process_xudt_from_mate
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	return_t	result = SS7_SUCCESS;
	dsccp_instance_id_t		instance_id;
	msg_info_t	info;
	U8bit		offset;
	U8bit		*p_nw_api;
	error_t	ecode;
	
	/** Extract the elems from the command **/

	offset = DSCCP_DATA_OFFSET;
	instance_id = p_api [offset++];
	p_nw_api = p_api + offset;

	/* parse the nw API; no need to check return value of the parsing and
	** we also need not perform compatibility check or apply any other check
	** as the message would have passed through all these stages in the
	** mate itself and the message would not have reached here at all if it	
	** any of the checks failed there !!
	*/
	sccp_parse_m3_transfer_ind_api (p_nw_api, &info, &ecode);
	sccp_parse_nw_msg (&info);
	info.dsccp_mate_api = SS7_TRUE;


	/* SPR 9001 - Fix Start */
	/*sccp_handle_cl_msg(&info);*/

	info.p_ss = sccp_db_find_ss (info.p_sp, info.cd_addr.ssn);
	if ((info.p_ss) && (info.p_ss->registered))  /* SS equipped */
	{
		if (info.p_ss->allowed)
		{
			sccp_handle_cl_msg(&info);
		}
		else
			return SS7_FAILURE;
			
	}
	else
		return SS7_FAILURE;
	/* SPR 9001 - Fix End   */

	return result;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_process_t_reass_query_timer_expiry
**       
****************************************************************************
**
**	DESCRIPTION:
**	This function handles the expiry of T-Reass-Query Timer. The expiry of
**	this timer before none of the mates respond to DSCCP_API_CMD_SCLC_REASS
**	_INFO_REQ means that the XUDTs buffered in this reass seg ref have
**	arrived out of sequence. So this the message return procedure is initiated 
**	for the 1st XUDT in the buffer and the rest of the segments are discarded. 
**	The reass-segment-ref is released.
**
**	NOTE :
**
***************************************************************************/

return_t 
dsccp_process_t_reass_query_timer_expiry
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	return_t	result = SS7_SUCCESS;
	msg_info_t	info;
	U32bit seg_ref_id;
	struct seg_ref * p_seg_ref;
	U8bit	*p_nw_api;
	error_t ecode;

	p_api += API_HEADER_LEN;
	
	seg_ref_id = (p_api[1] | (p_api[2] << 8) |
			(p_api[3] << 16) | (p_api[4] << 24));
	p_seg_ref = SCCP_GET_SEG_REF_FROM_ID(seg_ref_id);

	if ((!p_seg_ref->busy) || (!p_seg_ref->dsccp_seg_ref))
		return result;

	if (p_seg_ref->dest_inst_id == DSCCP_INVALID_INSTANCE_ID)
	{
		/* No response received from mates; invoke a reassembly failure proc
		*/
		p_nw_api = p_seg_ref->xudt_buffer[0];
		sccp_parse_m3_transfer_ind_api (p_nw_api, &info, &ecode);
		sccp_parse_nw_msg (&info);
		info.ret_cause = SCCP_ERR_IN_MESSAGE_TRANSPORT;
		sccp_handle_reass_failure (&info, p_seg_ref, REL_SEG_REF);
	}
	else
	{
		sccp_release_seg_ref(p_seg_ref);
	}
	
	return result;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_process_xudt_from_nw
**       
****************************************************************************
**
**	DESCRIPTION:
**	This function is invoked when a non-1st XUDT segment is received from the 
**	network and no corresponding reass segment reference is found. The 
**	following actions are performed in this case:
**	1. Create a reass segment reference and buffer the XUDT;
**	2. Broadcast a DSCCP_API_CMD_SCLC_REASS_INFO_REQ to all its mates
**	3. Start T-Reass-Query timer. If some other instance has the reassembly
**	   segment reference, it is expected to respond before this timer expires
**
**	NOTE :
**
***************************************************************************/

return_t 
dsccp_process_xudt_from_nw
#ifdef ANSI_PROTO
	(msg_info_t * p_info, struct seg_ref *p_seg_ref)
#else
	(p_info, p_seg_ref)
	msg_info_t * p_info;
	struct seg_ref *p_seg_ref;
#endif
{
	return_t	result = SS7_SUCCESS;
	error_t ecode;
	U8bit reass_tmr_buf[T_REASS_TMR_BUF_LEN];
	U32bit seg_ref_id;
	s7_len_t	nw_api_len;

	if (p_seg_ref == SS7_NULL)
	{
		/* dsccp Segment reference does not exist for buffering this XUDT;
		** Create a dsccp segment reference 
		*/
		p_seg_ref = sccp_allocate_seg_ref ();
		if (SS7_NULL == p_seg_ref)
		{
			/* Failed to allocate seg ref */
			SC_STAT_Q752_TS_NW_CONGESTION;
			SC_STAT_Q752_INR_NW_CONGESTION;
			p_info->ret_cause = SCCP_NETWORK_CONGESTION;
			sccp_handle_reass_failure (p_info, SS7_NULL, 0);
			return SS7_FAILURE;
		}
		p_seg_ref->busy = SS7_TRUE;
		sccp_copy_sccp_addr (&p_info->cg_addr, &p_seg_ref->cg_addr);
		sccp_copy_sccp_addr (&p_info->cd_addr, &p_seg_ref->cd_addr);
		p_seg_ref->slr = p_info->segment.slr;
		p_seg_ref->opc = p_info->opc;
		p_seg_ref->dpc = p_info->dpc;
		p_seg_ref->sls = p_info->sls;
		if (p_info->proto_class & RET_OPTN_MASK)
			p_seg_ref->ret_optn_set = SS7_TRUE;
		else
			p_seg_ref->ret_optn_set = SS7_FALSE;
		p_seg_ref->p_data = SS7_NULL;

		seg_ref_id = (U32bit)SCCP_GET_SEG_REF_ID(p_seg_ref);
		reass_tmr_buf[0] = T_REASSEMBLY_QUERY_TIMER_ID;
		reass_tmr_buf[1] = (U8bit)seg_ref_id;
		reass_tmr_buf[2] = (U8bit)(seg_ref_id >> 8);
		reass_tmr_buf[3] = (U8bit)(seg_ref_id >> 16);
		reass_tmr_buf[4] = (U8bit)(seg_ref_id >> 24);
		if (SS7_FAILURE == ss7_start_timer (T_REASS_QUERY_TIMER_DEF_VALUE,
			reass_tmr_buf, 5, SCCP_MODULE_ID, 
			&p_seg_ref->reass_tim, &ecode))
		{
			SC_STAT_Q752_TS_NW_CONGESTION;
			SC_STAT_Q752_INR_NW_CONGESTION;
			p_info->ret_cause = SCCP_NETWORK_CONGESTION;
			sccp_handle_reass_failure (p_info, p_seg_ref, REL_SEG_REF);
			return SS7_FAILURE;
		}

		p_seg_ref->dsccp_seg_ref = SS7_TRUE;
		p_seg_ref->dest_inst_id = DSCCP_INVALID_INSTANCE_ID;

		/* Buffer the XUDT */
		p_seg_ref->num_xudt_buffered = 1;
		nw_api_len = GET_API_LEN(p_info->p_api);
		p_seg_ref->xudt_buffer[0] = sccp_malloc(nw_api_len);
		if (p_seg_ref->xudt_buffer[0] == SS7_NULL)
		{
			SC_STAT_Q752_TS_NW_CONGESTION;
			SC_STAT_Q752_INR_NW_CONGESTION;
			p_info->ret_cause = SCCP_NETWORK_CONGESTION;
			sccp_handle_reass_failure (p_info, p_seg_ref, 
						REL_SEG_REF | STOP_TIMER);
			return SS7_FAILURE;
		}
		sccp_memcpy(p_seg_ref->xudt_buffer[0], p_info->p_api, nw_api_len);

		/* Broadcast REASS INFO REQ */
		dsccp_bcast_reass_info_req_to_all (p_seg_ref);
		return result;
	}
	else
	{
		/* DSCCP Segment reference already exists; Buffer the XUDT if the 
		** destination instance where the reassembly is happening is NOT known;
		** forward the XUDT to destination instance otherwise;
		*/
		if (p_seg_ref->dest_inst_id != DSCCP_INVALID_INSTANCE_ID)
		{
			/* Forward the XUDT */
			dsccp_build_and_send_xudt_to_mate (p_seg_ref->dest_inst_id, 
												p_info->p_api);
		}
		else
		{
			/* Buffer the XUDT */
			nw_api_len = GET_API_LEN(p_info->p_api);
			p_seg_ref->xudt_buffer[p_seg_ref->num_xudt_buffered] = 
						sccp_malloc(nw_api_len);
			if (p_seg_ref->xudt_buffer[p_seg_ref->num_xudt_buffered] 
				== SS7_NULL)
			{
				SC_STAT_Q752_TS_NW_CONGESTION;
				SC_STAT_Q752_INR_NW_CONGESTION;
				p_info->ret_cause = SCCP_NETWORK_CONGESTION;
				sccp_handle_reass_failure (p_info, p_seg_ref, 
							REL_SEG_REF | STOP_TIMER);
				return SS7_FAILURE;
			}
			p_seg_ref->num_xudt_buffered++;
			sccp_memcpy(p_seg_ref->xudt_buffer[0], p_info->p_api, nw_api_len);
		}
	}

	return result;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_build_reass_info_req
**       
****************************************************************************
**
**	DESCRIPTION:
**	construct and send a Reass Info Req command to the indicated instance
**
**	NOTE :
**
***************************************************************************/

void 
dsccp_build_reass_info_req
#ifdef ANSI_PROTO
	(U8bit *p_buf, struct seg_ref *p_seg_ref)
#else
	(p_buf, p_seg_ref)
	U8bit *p_buf;
	struct seg_ref *p_seg_ref;
#endif
{
	s7_len_t	offset;
	U8bit		nelems;
	U8bit		i;
	U32bit		p_seg_ref_int;

	offset = API_HEADER_LEN;
	nelems = 0;

	/* fill Category */
	p_buf[offset++] = DSCCP_API_CAT_SCLC;
	nelems ++;

	/* fill Command */
	p_buf[offset++] = DSCCP_API_CMD_SCLC_REASS_INFO_REQ;
	nelems ++;

	/* fill self instance ID */
	p_buf[offset++] = sc_opt.dsccp_local_instance_id;
	nelems ++;

	/* fill the seg ref pointer; this will be returned in the response */
	p_seg_ref_int =  (U32bit)((Ulong)p_seg_ref);
	p_buf[offset++] = (U8bit) p_seg_ref_int;
	p_buf[offset++] = (U8bit) (p_seg_ref_int >> 8);
	p_buf[offset++] = (U8bit) (p_seg_ref_int >> 16);
	p_buf[offset++] = (U8bit) (p_seg_ref_int >> 24);
	nelems ++;

	/* fill OPC */
	p_buf[offset++] = (U8bit) p_seg_ref->opc;
	p_buf[offset++] = (U8bit) (p_seg_ref->opc >> 8);
	p_buf[offset++] = (U8bit) (p_seg_ref->opc >> 16);
	p_buf[offset++] = (U8bit) (p_seg_ref->opc >> 24);
	nelems ++;

	/* fill DPC */
	p_buf[offset++] = (U8bit) p_seg_ref->dpc;
	p_buf[offset++] = (U8bit) (p_seg_ref->dpc >> 8);
	p_buf[offset++] = (U8bit) (p_seg_ref->dpc >> 16);
	p_buf[offset++] = (U8bit) (p_seg_ref->dpc >> 24);
	nelems ++;

	/* fill SLS */
	p_buf[offset++] = (U8bit) p_seg_ref->sls;
	nelems ++;

	/* fill SLR */
	p_buf[offset++] = (U8bit) p_seg_ref->slr;
	p_buf[offset++] = (U8bit) (p_seg_ref->slr >> 8);
	p_buf[offset++] = (U8bit) (p_seg_ref->slr >> 16);
	nelems ++;

	/* fill calling address */
	p_buf[offset++] = (U8bit) p_seg_ref->cg_addr.pc_ind;
	p_buf[offset++] = (U8bit) p_seg_ref->cg_addr.ssn_ind;
	p_buf[offset++] = (U8bit) p_seg_ref->cg_addr.gti;
	p_buf[offset++] = (U8bit) p_seg_ref->cg_addr.rout_ind;
	if (p_seg_ref->cg_addr.pc_ind)
	{
		p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.pc);
		p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.pc >> 8);
		p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.pc >> 16);
		p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.pc >> 24);
	}
	if (p_seg_ref->cg_addr.ssn_ind)
		p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.ssn);
	if (p_seg_ref->cg_addr.gti)
	{
		p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.gt_len);
		for (i=0; i<p_seg_ref->cg_addr.gt_len; ++i)
			p_buf[offset++] = (U8bit) (p_seg_ref->cg_addr.gt[i]);
	}
	nelems++;
	
	/* fill API Header */
	sccp_fill_api_header(p_buf, DSCCP_MATE_API, nelems, offset);
	
	return;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_build_and_send_reass_info_resp
**       
****************************************************************************
**
**	DESCRIPTION:
**	construct and send a Reass Info Resp command to the indicated instance
**
**	NOTE :
**
***************************************************************************/

void 
dsccp_build_and_send_reass_info_resp
#ifdef ANSI_PROTO
	(dsccp_instance_id_t dest_inst_id, U32bit src_seg_ref)
#else
	(dest_inst_id, src_seg_ref)
	U8bit dest_inst_id;
	U32bit src_seg_ref;
#endif
{
	U8bit		*p_buf;
	s7_len_t	offset;
	U8bit		nelems;
	error_t		ecode;

	p_buf = (U8bit *) sccp_malloc(DSCCP_MAX_DATA_LEN);
	if (p_buf == SS7_NULL)
	{
		SC_A_TRC (("SCCP::SCLC: malloc failure; cannot send reass info "
					"resp to mate \n"));
		return;
	}

	offset = API_HEADER_LEN;
	nelems = 0;

	/* fill Category */
	p_buf[offset++] = DSCCP_API_CAT_SCLC;
	nelems ++;

	/* fill Command */
	p_buf[offset++] = DSCCP_API_CMD_SCLC_REASS_INFO_RESP;
	nelems ++;

	/* fill self instance ID */
	p_buf[offset++] = sc_opt.dsccp_local_instance_id;
	nelems ++;

	/* Copy the dsccp seg ref that was present in the 
	** DSCCP_API_CMD_SCLC_REASS_INFO_REQ command */
	p_buf[offset++] = (U8bit) src_seg_ref;
	p_buf[offset++] = (U8bit) (src_seg_ref >> 8);
	p_buf[offset++] = (U8bit) (src_seg_ref >> 16);
	p_buf[offset++] = (U8bit) (src_seg_ref >> 24);
	nelems ++;

	/* fill API Header */
	sccp_fill_api_header(p_buf, DSCCP_MATE_API, nelems, offset);
	
	/* Send the API to mate */
	if(SS7_FAILURE == dsccp_send_to_mate (p_buf, offset, dest_inst_id, &ecode))
	{
		/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
	}
	else
	{
		/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_OUT_API_MATE();
#endif
	}

	return;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_build_and_send_xudt_to_mate
**       
****************************************************************************
**
**	DESCRIPTION:
**	construct and send a Reass Info Resp command to the indicated instance
**
**	NOTE :
**
***************************************************************************/

void 
dsccp_build_and_send_xudt_to_mate
#ifdef ANSI_PROTO
	(dsccp_instance_id_t dest_inst_id, U8bit *p_api)
#else
	(dest_inst_id, p_api)
	U8bit dest_inst_id;
	U8bit *p_api;
#endif
{
	U8bit		*p_buf;
	s7_len_t	offset;
	s7_len_t	nw_api_len;
	U8bit		nelems;
	error_t		ecode;

	p_buf = (U8bit *) sccp_malloc(DSCCP_MAX_DATA_LEN);
	if (p_buf == SS7_NULL)
	{
		SC_A_TRC (("SCCP::SCLC: malloc failure; cannot send reass info "
					"resp to mate \n"));
		return;
	}

	offset = API_HEADER_LEN;
	nelems = 0;

	/* fill Category */
	p_buf[offset++] = DSCCP_API_CAT_SCLC;
	nelems ++;

	/* fill Command */
	p_buf[offset++] = DSCCP_API_CMD_SCLC_XUDT;
	nelems ++;

	/* fill self instance ID */
	p_buf[offset++] = sc_opt.dsccp_local_instance_id;
	nelems ++;

	/* Copy the XUDT api */
	nw_api_len = GET_API_LEN (p_api);
	sccp_memcpy (p_buf + offset, p_api, nw_api_len);
	offset += nw_api_len;
	nelems ++;

	/* fill API Header */
	sccp_fill_api_header(p_buf, DSCCP_MATE_API, nelems, offset);
	
	/* Send the API to mate */
	if(SS7_FAILURE == dsccp_send_to_mate (p_buf, offset, dest_inst_id, &ecode))
	{
		/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
	}
	else
	{
		/* increment the mate out api */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_OUT_API_MATE();
#endif
	}

	return;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_build_and_send_all_buffered_xudt
**       
****************************************************************************
**
**	DESCRIPTION:
**	Send all the buffered XUDT segments to the mate 
**
**	NOTE :
**
***************************************************************************/

void 
dsccp_build_and_send_all_buffered_xudt
#ifdef ANSI_PROTO
	(dsccp_instance_id_t dest_inst_id, struct seg_ref *p_seg_ref)
#else
	(dest_inst_id, p_seg_ref)
	U8bit dest_inst_id;
	struct seg_ref *p_seg_ref;
#endif
{
	U8bit		i;

	for (i=0; i<p_seg_ref->num_xudt_buffered; ++i)
	{
		dsccp_build_and_send_xudt_to_mate(dest_inst_id, 
				p_seg_ref->xudt_buffer[i]);
	}

	return;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_bcast_reass_info_req_to_all
**       
****************************************************************************
**
**	DESCRIPTION:
**	Broadcast the Reass Info Req to the mates 
**
**	NOTE :
**
***************************************************************************/

void 
dsccp_bcast_reass_info_req_to_all
#ifdef ANSI_PROTO
	(struct seg_ref *p_seg_ref)
#else
	(p_seg_ref)
	struct seg_ref *p_seg_ref;
#endif
{
	error_t		ecode;
	U8bit *p_buf;

	p_buf = (U8bit *) sccp_malloc(DSCCP_MAX_DATA_LEN);
	if (p_buf == SS7_NULL)
	{
		SC_A_TRC (("SCCP::SCLC: malloc failure; cannot send reass info "
					"resp to mate \n"));
		return;
	}

	dsccp_build_reass_info_req(p_buf, p_seg_ref);
	dsccp_broadcast_to_mates(p_buf, GET_API_LEN(p_buf), &ecode);
#ifdef DSCCP_STATS_ENABLED
	DSC_STAT_TS_XUDT_BCAST();
	DSC_STAT_INR_XUDT_BCAST();
#endif

	return;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_buffer_class1_messages
**       
****************************************************************************
**
**	DESCRIPTION:
**	Buffers the class 1 messages if DSCCP_T_CLASSS1_BUFFER timer is running  
**
**	NOTE :
**
***************************************************************************/
void 
dsccp_buffer_class1_messages
#ifdef ANSI_PROTO
	(U8bit *p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	dsccp_class1_buff_node * tmp_node = SS7_NULL;
	extern dsccp_class1_buff_node * list_head;
	extern dsccp_class1_buff_node * list_tail;

	tmp_node = (dsccp_class1_buff_node *)sccp_malloc(sizeof(dsccp_class1_buff_node));
	if(tmp_node == SS7_NULL)
	{
		SC_A_TRC (("DSCCP::SCLC: malloc failure\n"));
		return;
	}
	tmp_node->next_node = SS7_NULL;
	tmp_node->p_api = p_api;
	if(list_head == SS7_NULL)
	{
		list_head = tmp_node;
		list_tail = tmp_node; 
	}
	else
	{
		list_tail->next_node = tmp_node ;
		list_tail = tmp_node;
	}	

}


/***************************************************************************
**
**	FUNCTION :
** 	dsccp_handle_t_class1_buffer_timer_expiry
**       
****************************************************************************
**
**	DESCRIPTION:
**	Flushes out the Class1 message to MTP-3  and frees the linked list 
**
**	NOTE :
**
***************************************************************************/
return_t 
dsccp_handle_t_class1_buffer_timer_expiry
#ifdef ANSI_PROTO
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	dsccp_class1_buff_node * tmp_node = SS7_NULL;
	dsccp_class1_buff_node * temp = SS7_NULL;
	extern dsccp_class1_buff_node * list_head;
	extern dsccp_class1_buff_node * list_tail;
	extern U8bit dsccp_class1_buff_timer_running;


	dsccp_class1_buff_timer_running = SS7_FALSE;
	tmp_node = list_head;
	temp = list_head;
	
	while(tmp_node != SS7_NULL)
	{
		SC_A_TRC (("DSCCP::SCLC: Sending messages to MTP-3\n"));
		sccp_sendto_m3(tmp_node->p_api);
		tmp_node = tmp_node->next_node;
		sccp_free((void *)temp);
		temp = tmp_node;
	}
	list_head = SS7_NULL;
	list_tail = SS7_NULL;
/* SPR 8985 - Fix Start */
/* This line of code is added to remove the unused parameter warning */
	p_api = 0;
/* SPR 8985 - Fix End   */
	return SS7_SUCCESS;
}

/* SPR # 7470 Fix Start */
/***************************************************************************
**
**	FUNCTION :
** 	dsccp_handle_cls1_buf_inh_timer_expiry
**       
****************************************************************************
**
**	DESCRIPTION:
**	Flushes out the Class1 message to the USER  and frees the linked list 
**
**	NOTE :
**
***************************************************************************/
return_t 
dsccp_handle_cls1_buf_inh_timer_expiry
#ifdef ANSI_PROTO
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	dsccp_class1_buff_node * tmp_node = SS7_NULL;
	dsccp_class1_buff_node * temp = SS7_NULL;


	dsccp_class1_timer_status = SS7_FALSE;
	tmp_node = dsccp_cls1_buf_inh_list_head;
	temp = dsccp_cls1_buf_inh_list_head;
	
	while(tmp_node != SS7_NULL)
	{
		SC_A_TRC (("DSCCP::SCLC: Sending messages to USER\n"));
		sccp_m3_transfer_ind(tmp_node->p_api);
		sccp_free(tmp_node->p_api);
		tmp_node = tmp_node->next_node;
		sccp_free((void *)temp);
		temp = tmp_node;
	}
	dsccp_cls1_buf_inh_list_head = SS7_NULL;
	dsccp_cls1_buf_inh_list_tail = SS7_NULL;
/* SPR 8985 - Fix Start */
/* This line of code is added to remove the unused parameter warning */
	p_api = 0;
	p_ecode = 0;
/* SPR 8985 - Fix End   */
	return SS7_SUCCESS;
}

/***************************************************************************
**
**	FUNCTION :
** 	dsccp_store_class1_messages
**       
****************************************************************************
**
**	DESCRIPTION:
**	Buffers the class 1 messages if DSCCP_T_CLASSS1_BUFFER timer is running  
**
**	NOTE :
**
***************************************************************************/
return_t 
dsccp_store_class1_messages
#ifdef ANSI_PROTO
	(U8bit *p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	U8bit *p_buf;
	s7_len_t buf_len;
	dsccp_class1_buff_node * tmp_node = SS7_NULL;

	buf_len = GET_API_LEN(p_api);

	tmp_node = (dsccp_class1_buff_node *)sccp_malloc(sizeof(dsccp_class1_buff_node));
	if(tmp_node == SS7_NULL)
	{
		SC_A_TRC (("DSCCP::SCLC: malloc failure\n"));
		return SS7_FAILURE;
	}
	
	p_buf = (U8bit *) sccp_malloc(buf_len * sizeof(U8bit));
	if(p_buf == SS7_NULL)
	{
		SC_A_TRC (("DSCCP::SCLC: malloc failure \n"));
		sccp_free((void *)tmp_node);
		return SS7_FAILURE;
	}

	ss7_memcpy(p_buf, p_api, buf_len);

	tmp_node->next_node = SS7_NULL;
	tmp_node->p_api = p_buf;
	if(dsccp_cls1_buf_inh_list_head == SS7_NULL)
	{
		dsccp_cls1_buf_inh_list_head = tmp_node;
		dsccp_cls1_buf_inh_list_tail = tmp_node; 
	}
	else
	{
		dsccp_cls1_buf_inh_list_tail->next_node = tmp_node ;
		dsccp_cls1_buf_inh_list_tail = tmp_node;
	}	
	return SS7_SUCCESS;
}

/* SPR # 7470 Fix End */

#endif /* end DISTRIBBUTED SCCP */
