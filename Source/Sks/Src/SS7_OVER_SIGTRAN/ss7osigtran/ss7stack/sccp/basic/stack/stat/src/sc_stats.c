/******************************************************************************
**      FUNCTION:
**          Functions for accessing statistics maintained by SCCP stack entity
**
*******************************************************************************
**
**      FILE NAME:
**          sc_stats.c
**      
**      DESCRIPTION:
**          The Statistics Module provides a functional interface for:
**          (1)Initializing the SCCP specific statistics.
**          (3)Getting the SCCP specific statistics.  
**
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**	23Jul02    Suyash Tripathi   SPR#9302           Warning Removal  
**	21May02    Suyash Tripathi   SPR#8748           through memcpy data doesnt go in LE form  
**	14Mar02	   Sachin Bhatia   -----------          Checking State in each function
**	04NOV00	   Arun Kumar	     -----------          Adding STATS
**	15Feb99	   Sudipta Pattar    -----------          Fixed SPR 1278
**	15Feb99	   Sudipta Pattar    -----------          Fixed SPR 1277
**      15May98    Sriganesh Kini    -----------          SM interface
**      15Jan98    GAURAV.TANEJA     -----------          ORIGINAL
**
**      Copyright 1998, Hughes Software Systems, Inc.
******************************************************************************/


#include "sc_stgl.h"
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_stats.h"
#endif
static void sccp_stat_sm_cmd_resp
	_ARGS_ ((U8bit		* p_api,
		 return_t 	ret_val,
		 U8bit 		param,
	         Boolean 	put_param, 
		 error_t 	ecode));

#ifdef SCCP_STATS_ENABLED

/* contains the API related statistics of SCCP stack entity */
ss7_stats_api_t      sccp_api_stats;

/* contains the error related statistics of SCCP stack entity */ 
ss7_stats_error_t    sccp_error_stats;

/* contains the protocol related statistics (Q.752) of SCCP stack entity */ 
sccp_stats_proto_q752_t    sccp_proto_q752_stats;

/* SPR# 4543 Start */
/* contains the traffic related statistics of SCCP stack entity */
sccp_stats_traffic_t    sccp_traffic_stats;
/* SPR# 4543 End */

/* bitmap containing information about statistics type enabled */
U32bit               sccp_stats_flag = 0xffffffffL;

/*****************************************************************************
**      FUNCTION :
**            initializes q752 stats
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_init_stats_q752
#ifdef ANSI_PROTO
	(void)
#else
	()
#endif
{
	U8bit i;
   	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return ;
    }


	sccp_proto_q752_stats.trans_fail_addr_nature.count = 0;
	sccp_proto_q752_stats.trans_fail_addr_nature.time = 0;
	sccp_proto_q752_stats.trans_fail_spec_addr.count = 0;
	sccp_proto_q752_stats.trans_fail_spec_addr.time = 0;
	sccp_proto_q752_stats.pc_unavail.count = 0;
	sccp_proto_q752_stats.pc_unavail.time = 0;
	sccp_proto_q752_stats.nw_congestion.count = 0;
	sccp_proto_q752_stats.nw_congestion.time = 0;
	sccp_proto_q752_stats.ss_unavail.count = 0;
	sccp_proto_q752_stats.ss_unavail.time = 0;
	sccp_proto_q752_stats.ss_congestion.count = 0;
	sccp_proto_q752_stats.ss_congestion.time = 0;
	sccp_proto_q752_stats.unequipped_ss.count = 0;
	sccp_proto_q752_stats.unequipped_ss.time = 0;
	sccp_proto_q752_stats.syntax_error.count = 0;
	sccp_proto_q752_stats.syntax_error.time = 0;
	sccp_proto_q752_stats.routing_fail_reason_unknown.count = 0;
	sccp_proto_q752_stats.routing_fail_reason_unknown.time = 0;
        sccp_proto_q752_stats.t_reass_expired.count = 0;
        sccp_proto_q752_stats.t_reass_expired.time = 0;
        sccp_proto_q752_stats.xudt_seg_out_of_seq.count = 0;
        sccp_proto_q752_stats.xudt_seg_out_of_seq.time = 0;
        sccp_proto_q752_stats.xudt_no_buff_left.count = 0;
        sccp_proto_q752_stats.xudt_no_buff_left.time = 0;
        sccp_proto_q752_stats.hop_count_violation.count = 0;
        sccp_proto_q752_stats.hop_count_violation.time = 0;
        sccp_proto_q752_stats.msg_too_large_for_segmenting.count = 0;
        sccp_proto_q752_stats.msg_too_large_for_segmenting.time = 0;
        sccp_proto_q752_stats.failure_to_rel_conn.count = 0;
        sccp_proto_q752_stats.failure_to_rel_conn.time = 0;
        sccp_proto_q752_stats.sccp_iar_expiry.count = 0;
        sccp_proto_q752_stats.sccp_iar_expiry.time = 0;
        sccp_proto_q752_stats.provider_init_reset.time = 0;
        sccp_proto_q752_stats.provider_init_reset.count = 0;
        sccp_proto_q752_stats.provider_init_rlsd.count = 0;
        sccp_proto_q752_stats.provider_init_rlsd.time = 0;
        sccp_proto_q752_stats.sccp_seg_failed.count = 0;
        sccp_proto_q752_stats.sccp_seg_failed.time = 0;
        sccp_proto_q752_stats.sccp_sog_recd.count = 0;
        sccp_proto_q752_stats.sccp_sog_recd.time = 0;
        sccp_proto_q752_stats.sccp_t_coord_expired.count = 0;
        sccp_proto_q752_stats.sccp_t_coord_expired.time = 0;

	for (i=0; i < MAX_SSN; i++)
	{
		sccp_proto_q752_stats.orig_msg_class_0[i] = 0;
		sccp_proto_q752_stats.orig_msg_class_1[i] = 0;
		sccp_proto_q752_stats.recd_msg_class_0[i] = 0;
		sccp_proto_q752_stats.recd_msg_class_1[i] = 0;
                sccp_proto_q752_stats.orig_ludt_xudt_udt[i] = 0;
                sccp_proto_q752_stats.recd_ludt_xudt_udt[i] = 0;
#ifdef SCCP_INCLUDE_CO_SERVICE
		sccp_proto_q752_stats.recd_msg_dt1[i] = 0;
		sccp_proto_q752_stats.orig_msg_dt1[i] = 0;
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
		sccp_proto_q752_stats.recd_msg_dt2[i] = 0;
		sccp_proto_q752_stats.orig_msg_dt2[i] = 0;
		sccp_proto_q752_stats.recd_msg_ed[i] = 0;
		sccp_proto_q752_stats.orig_msg_ed[i] = 0;
#endif
#endif
	}
}

/* SPR# 4543 Start */
/******************************************************************************
**  FUNCTION:
**     Initializes the SCCP traffic statistics.
**  DESCRIPTION:
**     This function initializes the SCCP traffic related statistics to
**     zero.
**
******************************************************************************/
void sccp_init_stats_traffic 
#ifdef ANSI_PROTO 
	(void)
#else 
	()
#endif
{
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
    }

	sccp_traffic_stats.num_sc_pkt_sent = 0;
	sccp_traffic_stats.num_sc_pkt_recd = 0;
	sccp_traffic_stats.num_sc_pkt_drop = 0;
	sccp_traffic_stats.num_sc_pkt_invalid = 0;
	sccp_traffic_stats.num_sc_gtt_tr_fail = 0;
}

/* SPR# 4543 End */


/*****************************************************************************
**      FUNCTION :
**            initializes internal stats
******************************************************************************
**
**      DESCRIPTION :
**            currently no internal stats maintained. write this func
**            if and when there will be internal stats
**
**      NOTE :
**
*****************************************************************************/

void
sccp_init_stats_internal
#ifdef ANSI_PROTO
	(void)
#else
	()
#endif
{
#if defined (DISTRIBUTED_SCCP) && defined (DSCCP_STATS_ENABLED)
	extern dsccp_stats_api_t    dsccp_stats_api;
	extern dsccp_stats_sclc_t   dsccp_stats_sclc;
	extern dsccp_stats_scoc_t   dsccp_stats_scoc;

	dsccp_stats_api.in_api_mate = 0;
	dsccp_stats_api.out_api_mate = 0;
	dsccp_stats_api.err_in_api_mate = 0;
	dsccp_stats_api.err_out_api_mate = 0;
	
	dsccp_stats_sclc.sccp_xudt_bcast.time = 0;
	dsccp_stats_sclc.sccp_xudt_bcast.count = 0;
	dsccp_stats_scoc.sccp_n_disconn_req.time = 0;
	dsccp_stats_scoc.sccp_n_disconn_req.count = 0;
#endif
}

/*****************************************************************************
**      FUNCTION :
**            gets q752 stats
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_get_stats_q752
#ifdef ANSI_PROTO
	(pvoid p_stat_ptr)
#else
	(p_stat_ptr)
	pvoid p_stat_ptr;
#endif
{
	sccp_stats_proto_q752_t * p_stats = (sccp_stats_proto_q752_t *)p_stat_ptr;
	U8bit i;
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
    }


	p_stats->trans_fail_addr_nature.count =
		sccp_proto_q752_stats.trans_fail_addr_nature.count;
	p_stats->trans_fail_addr_nature.time =
		sccp_proto_q752_stats.trans_fail_addr_nature.time;
	p_stats->trans_fail_spec_addr.count =
		sccp_proto_q752_stats.trans_fail_spec_addr.count;
	p_stats->trans_fail_spec_addr.time =
		sccp_proto_q752_stats.trans_fail_spec_addr.time;
	p_stats->pc_unavail.count =
		sccp_proto_q752_stats.pc_unavail.count;
	p_stats->pc_unavail.time =
		sccp_proto_q752_stats.pc_unavail.time;
	p_stats->nw_congestion.count =
		sccp_proto_q752_stats.nw_congestion.count;
	p_stats->nw_congestion.time =
		sccp_proto_q752_stats.nw_congestion.time;
	p_stats->ss_unavail.count =
		sccp_proto_q752_stats.ss_unavail.count;
	p_stats->ss_unavail.time =
		sccp_proto_q752_stats.ss_unavail.time;
	p_stats->ss_congestion.count =
		sccp_proto_q752_stats.ss_congestion.count;
	p_stats->ss_congestion.time =
		sccp_proto_q752_stats.ss_congestion.time;
	p_stats->unequipped_ss.count =
		sccp_proto_q752_stats.unequipped_ss.count;
	p_stats->unequipped_ss.time =
		sccp_proto_q752_stats.unequipped_ss.time;
	p_stats->syntax_error.count =
		sccp_proto_q752_stats.syntax_error.count;
	p_stats->syntax_error.time =
		sccp_proto_q752_stats.syntax_error.time;
	p_stats->routing_fail_reason_unknown.count =
		sccp_proto_q752_stats.routing_fail_reason_unknown.count;
	p_stats->routing_fail_reason_unknown.time =
		sccp_proto_q752_stats.routing_fail_reason_unknown.time;
        p_stats->t_reass_expired.count =
                sccp_proto_q752_stats.t_reass_expired.count;
        p_stats->t_reass_expired.time =
                sccp_proto_q752_stats.t_reass_expired.time;
        p_stats->xudt_seg_out_of_seq.count =
                sccp_proto_q752_stats.xudt_seg_out_of_seq.count;
        p_stats->xudt_seg_out_of_seq.time =
                sccp_proto_q752_stats.xudt_seg_out_of_seq.time;
        p_stats->xudt_no_buff_left.count =
                sccp_proto_q752_stats.xudt_no_buff_left.count;
        p_stats->xudt_no_buff_left.time = 
                sccp_proto_q752_stats.xudt_no_buff_left.time;
        p_stats->hop_count_violation.count = 
                sccp_proto_q752_stats.hop_count_violation.count;
        p_stats->hop_count_violation.time =
                sccp_proto_q752_stats.hop_count_violation.time;
        p_stats->msg_too_large_for_segmenting.count =
                sccp_proto_q752_stats.msg_too_large_for_segmenting.count;
        p_stats->msg_too_large_for_segmenting.time =
                sccp_proto_q752_stats.msg_too_large_for_segmenting.time;
        p_stats->failure_to_rel_conn.count =
                sccp_proto_q752_stats.failure_to_rel_conn.count;
        p_stats->failure_to_rel_conn.time = 
                sccp_proto_q752_stats.failure_to_rel_conn.time;
        p_stats->sccp_iar_expiry.count =
                sccp_proto_q752_stats.sccp_iar_expiry.count;
        p_stats->sccp_iar_expiry.time =
                sccp_proto_q752_stats.sccp_iar_expiry.time;
        p_stats->provider_init_reset.time = 
                sccp_proto_q752_stats.provider_init_reset.time;
        p_stats->provider_init_reset.count =
                sccp_proto_q752_stats.provider_init_reset.count;
        p_stats->provider_init_rlsd.count = 
                sccp_proto_q752_stats.provider_init_rlsd.count;
        p_stats->provider_init_rlsd.time = 
                sccp_proto_q752_stats.provider_init_rlsd.time ;
        p_stats->sccp_seg_failed.count =
                sccp_proto_q752_stats.sccp_seg_failed.count;
        p_stats->sccp_seg_failed.time =
                sccp_proto_q752_stats.sccp_seg_failed.time ;
        p_stats->sccp_sog_recd.count =
                sccp_proto_q752_stats.sccp_sog_recd.count ;
        p_stats->sccp_sog_recd.time =
                sccp_proto_q752_stats.sccp_sog_recd.time;
        p_stats->sccp_t_coord_expired.count =
                sccp_proto_q752_stats.sccp_t_coord_expired.count;
        p_stats->sccp_t_coord_expired.time =
                sccp_proto_q752_stats.sccp_t_coord_expired.time; 
   
       

	for (i=0; i < MAX_SSN; i++)
	{
		p_stats->orig_msg_class_0[i] =
			sccp_proto_q752_stats.orig_msg_class_0[i];
		p_stats->orig_msg_class_1[i] =
			sccp_proto_q752_stats.orig_msg_class_1[i];
		p_stats->recd_msg_class_0[i] =
			sccp_proto_q752_stats.recd_msg_class_0[i];
		p_stats->recd_msg_class_1[i] =
			sccp_proto_q752_stats.recd_msg_class_1[i];
                p_stats->orig_ludt_xudt_udt[i] =
                        sccp_proto_q752_stats.orig_ludt_xudt_udt[i];
                p_stats->recd_ludt_xudt_udt[i] = 
                        sccp_proto_q752_stats.recd_ludt_xudt_udt[i];
#ifdef SCCP_INCLUDE_CO_SERVICE
		p_stats->orig_msg_dt1[i] =
			sccp_proto_q752_stats.orig_msg_dt1[i];
		p_stats->recd_msg_dt1[i] =
			sccp_proto_q752_stats.recd_msg_dt1[i];
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
		p_stats->orig_msg_dt2[i] =
			sccp_proto_q752_stats.orig_msg_dt2[i];
		p_stats->recd_msg_dt2[i] =
			sccp_proto_q752_stats.recd_msg_dt2[i];
		p_stats->orig_msg_ed[i] =
			sccp_proto_q752_stats.orig_msg_ed[i];
		p_stats->recd_msg_ed[i] =
			sccp_proto_q752_stats.recd_msg_ed[i];
#endif
#endif
	}
}

/* SPR# 4543 Start*/
/******************************************************************************
**  FUNCTION:
**     Gets the SCCP Traffic Related Statistics
**  DESCRIPTION:
**     This function copies the traffic statistics into the location
**     pointed to by p_stats.
**
******************************************************************************/

void
sccp_get_stats_traffic
#ifdef ANSI_PROTO
	(pvoid p_stats)
#else
	(p_stat_ptr)
	pvoid p_stats;
#endif
{

    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
    }

  *((sccp_stats_traffic_t *) p_stats) =  sccp_traffic_stats;
}
/* SPR# 4543 End */

#if 0
/*****************************************************************************
**      FUNCTION :
**            gets internal stats
******************************************************************************
**
**      DESCRIPTION :
**            currently no internal stats maintained. write this func
**            if and when there will be internal stats
**      NOTE :
**
*****************************************************************************/

void
sccp_get_stats_internal
#ifdef ANSI_PROTO
	(pvoid p_stats)
#else
	(p_stats)
	pvoid p_stats;
#endif
{
	/* Currently, empty function. To be updated later, if needed */
}
#endif

/*****************************************************************************
**      FUNCTION :
**            handles SM command category STAT
******************************************************************************
**
**      DESCRIPTION :
**         calls appropriate function depending on STAT command
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stat_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	U8bit cmd;
	return_t ret_val;
	error_t ecode;
	stat_type_t stat_type;
	U8bit param = 0; Boolean put_param = SS7_FALSE;

	cmd = GET_SM_CMD(p_api);
	stat_type = GET_SM_STAT_TYPE(p_api);

	SC_A_TRC (("SCCP::STAT: SM category STAT\n"));

	switch (cmd)
	{
		case SS7_SM_INIT_STATS:
			SC_A_TRC (("SCCP::STAT: init stats cmd\n"));
			ret_val = sctc_init_stats (SCCP_MODULE_ID, stat_type,
			                           &ecode);
			break;

		case SS7_SM_GET_STATS:
			SC_A_TRC (("SCCP::STAT: get stat cmd\n"));
			sccp_retrieve_stats (p_api);
			return;

		case SS7_SM_DISABLE_STATS:
			SC_A_TRC (("SCCP::STAT: disable stat cmd\n"));
			ret_val = sctc_disable_stats (SCCP_MODULE_ID, stat_type,
			                              &ecode);
			break;

		case SS7_SM_ENABLE_STATS:
			SC_A_TRC (("SCCP::STAT: enable stat cmd\n"));
			ret_val = sctc_enable_stats (SCCP_MODULE_ID, stat_type,
			                             &ecode);
			break;

		default:
			SC_A_TRC (("SCCP::STAT: invalid stat cmd %d\n", cmd));
			ret_val = SS7_FAILURE;
			ecode = ESS7_INVALID_API_ELEMENT;
			break;
	}

	if (SS7_FAILURE == ret_val)
		SC_A_ERR (ecode);

	sccp_stat_sm_cmd_resp (p_api, ret_val, param, put_param, ecode);
}

/*****************************************************************************
**      FUNCTION :
**            gets internal stats
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_retrieve_stats
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	stat_type_t stat_type;
	U32bit mem_size;
	U8bit param = 0; Boolean put_param = SS7_FALSE;
	U8bit * p_elem, * p_stat_buf, reset_flag;
        U8bit num_data_fields;
	/* SPR 9302 - Fix Start */
        /*return_t ret_val;*/
        return_t ret_val = 0;
	/* SPR 9302 - Fix End   */
        error_t ecode = 0;
	
	/* SPR 8748 - Fix Start */
	U32bit i;
	/* SPR 8748 - Fix End */

#if defined (DISTRIBUTED_SCCP) && defined (DSCCP_STATS_ENABLED)
	extern dsccp_stats_api_t    dsccp_stats_api;
	extern dsccp_stats_sclc_t   dsccp_stats_sclc;
	extern dsccp_stats_scoc_t   dsccp_stats_scoc;
#endif


	stat_type = GET_SM_STAT_TYPE(p_api);
	/* SPR 1277: Get reset flag */
	reset_flag = GET_SM_RESET_FLAG(p_api);

	/* Allocate buffer to fill stats */
	switch (stat_type)
	{
		case STATS_API:
			mem_size = SCCP_API_STAT_BUF_SIZE;
			break;

		case STATS_PROTO_Q752:
			mem_size = SCCP_Q752_STAT_BUF_SIZE;
			break;

		/* SPR# 4543 Start */
		case STATS_TRAFFIC:
			mem_size = SCCP_TRAFFIC_STAT_BUF_SIZE;
			break;
		/* SPR# 4543 End */

		case STATS_ERROR:
			mem_size = SCCP_ERROR_STAT_BUF_SIZE;
			break;
#if defined (DISTRIBUTED_SCCP) && defined (DSCCP_STATS_ENABLED)
		case STATS_PROTO_INTERNAL:
			mem_size = SCCP_INTERNAL_STAT_SIZE;
			break;
#endif
		default:
			SC_A_TRC (("SCCP::STAT: Invalid Stats Type\n"));
			sccp_stat_sm_cmd_resp (p_api, SS7_FAILURE, param, put_param,
	                       ESS7_INVALID_STATS_TYPE);
			return;
	}

	if (SS7_NULL == (p_stat_buf = sccp_malloc(mem_size)))
	{
		sccp_stat_sm_cmd_resp (p_api, SS7_FAILURE, param, put_param,
		                       ESS7_MEMORY_ALLOCATION_FAILURE);
		return;
	}

	p_elem = p_stat_buf + API_HEADER_LEN;
	p_api += API_HEADER_LEN;
	*p_elem++ = *p_api++;
	*p_elem++ = *p_api++;
	*p_elem++ = *p_api++;
	*p_elem++ = SS7_SUCCESS;

	/* Encode the statistics into the buffer */
	switch (stat_type)
	{
		case STATS_API:
			
			PUT_4_BYTE_LE (p_elem, sccp_api_stats.in_api_su);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE (p_elem, sccp_api_stats.out_api_su);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE (p_elem, sccp_api_stats.in_api_ll);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE (p_elem, sccp_api_stats.out_api_ll);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE (p_elem, sccp_api_stats.in_api_sm);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE (p_elem, sccp_api_stats.out_api_sm);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_api_stats.err_api_su);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_api_stats.err_api_ll);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_api_stats.err_api_sm);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_api_stats.err_out_api_ll);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_api_stats.err_api_misc);
			p_elem += sizeof(count_t);

			break;

		case STATS_PROTO_Q752:
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.trans_fail_addr_nature.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.trans_fail_addr_nature.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.trans_fail_spec_addr.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.trans_fail_spec_addr.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.pc_unavail.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.pc_unavail.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.nw_congestion.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.nw_congestion.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.ss_unavail.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.ss_unavail.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.ss_congestion.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.ss_congestion.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.unequipped_ss.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.unequipped_ss.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.syntax_error.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.syntax_error.time);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.routing_fail_reason_unknown.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem,
			sccp_proto_q752_stats.routing_fail_reason_unknown.time);
			p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                        sccp_proto_q752_stats.t_reass_expired.count);
                        p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                        sccp_proto_q752_stats.t_reass_expired.time);
                        p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                        sccp_proto_q752_stats.xudt_seg_out_of_seq.count);
                        p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                        sccp_proto_q752_stats.xudt_seg_out_of_seq.time);
                        p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                        sccp_proto_q752_stats.xudt_no_buff_left.count);
                         p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.xudt_no_buff_left.time);
                       p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.hop_count_violation.count);
                       p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.hop_count_violation.time);
                       p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.msg_too_large_for_segmenting.count);
                       p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.msg_too_large_for_segmenting.time);
                       p_elem += sizeof(count_t);
                    
                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.failure_to_rel_conn.count);
                       p_elem += sizeof(count_t);

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.failure_to_rel_conn.time);
                       p_elem += sizeof(count_t); 

                        PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_iar_expiry.count);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_iar_expiry.time);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.provider_init_reset.time);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.provider_init_reset.count);
                       p_elem += sizeof(count_t);
  
                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.provider_init_rlsd.count);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.provider_init_rlsd.time);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_seg_failed.count);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_seg_failed.time);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_sog_recd.count);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_sog_recd.time);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_t_coord_expired.count);
                       p_elem += sizeof(count_t);

                       PUT_4_BYTE_LE(p_elem,
                       sccp_proto_q752_stats.sccp_t_coord_expired.time);
                       p_elem += sizeof(count_t);                    
		
			/* SPR 1278: Start fix
			 * wrong size was passed to sccp_memcpy
			 */ 
#ifdef SCCP_INCLUDE_CO_SERVICE
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
                        num_data_fields = 12 ;   /* class 0,class 1,dt1,dt2,ed mesgs */
#else
                        num_data_fields = 8 ;    /* class 0, class 1, dt1 mesgs */
#endif
#else
                        num_data_fields = 6 ;    /* class 0 and class 1 mesgs */
#endif

/** SPR 8748 - Fix Start **/
#if 0
/* The memcpy needs to be commented because if we do memcpy we are not sending 
** data in LE form
*/
			sccp_memcpy ((U8bit *)p_elem, 
			(U8bit *)(&sccp_proto_q752_stats.orig_msg_class_0 [0]),
			MAX_SSN * sizeof (count_t) * num_data_fields) ;
			/* SPR 1278: End fix */
#endif

                        for(i=0;i<MAX_SSN;i++)
                        {
                                PUT_4_BYTE_LE(p_elem,
                                                        sccp_proto_q752_stats.orig_ludt_xudt_udt[i]);
                                p_elem += sizeof(count_t);
                        }
                        for(i=0;i<MAX_SSN;i++)
                        {
                                PUT_4_BYTE_LE(p_elem,
                                                        sccp_proto_q752_stats.recd_ludt_xudt_udt[i]);
                                p_elem += sizeof(count_t);
                        }
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.orig_msg_class_0[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.orig_msg_class_1[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.recd_msg_class_0[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.recd_msg_class_1[i]);
				p_elem += sizeof(count_t);
			}
#if 0
/* This portion is being moved above to keep consistency with **
** structure defined in sc_stats.h **/
                        for(i=0;i<MAX_SSN;i++)
                        {
                                PUT_4_BYTE_LE(p_elem,
                                                        sccp_proto_q752_stats.orig_ludt_xudt_udt[i]);
                                p_elem += sizeof(count_t);
                        }
                        for(i=0;i<MAX_SSN;i++)
                        {
                                PUT_4_BYTE_LE(p_elem,
                                                        sccp_proto_q752_stats.recd_ludt_xudt_udt[i]);
                                p_elem += sizeof(count_t);
                        }
#endif /* end of if 0 */

#ifdef SCCP_INCLUDE_CO_SERVICE
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.recd_msg_dt1[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.orig_msg_dt1[i]);
				p_elem += sizeof(count_t);
			}
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE			
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.recd_msg_dt2[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.orig_msg_dt2[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.recd_msg_ed[i]);
				p_elem += sizeof(count_t);
			}
			for(i=0;i<MAX_SSN;i++)
			{
				PUT_4_BYTE_LE(p_elem,
							sccp_proto_q752_stats.orig_msg_ed[i]);
				p_elem += sizeof(count_t);
			}
#endif
#endif
/** SPR 8748 - Fix End **/

			break;

		case STATS_ERROR:
			PUT_4_BYTE_LE(p_elem, sccp_error_stats.err_api);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_error_stats.err_msg);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_error_stats.err_sys);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_error_stats.err_system_res);
			p_elem += sizeof(count_t);

			break;
		/* SPR# 4543 Start */
		case STATS_TRAFFIC:
			PUT_4_BYTE_LE(p_elem, sccp_traffic_stats.num_sc_pkt_sent);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_traffic_stats.num_sc_pkt_recd);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_traffic_stats.num_sc_pkt_drop);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_traffic_stats.num_sc_pkt_invalid);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, sccp_traffic_stats.num_sc_gtt_tr_fail);
			p_elem += sizeof(count_t);
			break;
		/* SPR# 4543  End */
#if defined (DISTRIBUTED_SCCP) && defined (DSCCP_STATS_ENABLED)
		case STATS_PROTO_INTERNAL:
			PUT_4_BYTE_LE(p_elem, dsccp_stats_api.in_api_mate);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_api.out_api_mate);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_api.err_in_api_mate);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_api.err_out_api_mate);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_sclc.sccp_xudt_bcast.time);
			p_elem += sizeof(ss7_time_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_sclc.sccp_xudt_bcast.count);
			p_elem += sizeof(count_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_scoc.sccp_n_disconn_req.time);
			p_elem += sizeof(ss7_time_t);
			PUT_4_BYTE_LE(p_elem, dsccp_stats_scoc.sccp_n_disconn_req.count);

			break;
#endif
			
		default:
			break;
	}

	sccp_fill_api_header (p_stat_buf, SCCP_SM_RESPONSE_API,
	                      SS7_SM_API_MIN_NO_ELEM + 2, (U16bit)mem_size);
	sccp_sendto_sm (p_stat_buf);

        /* SPR 1277: Start fix 
         * reset statistics
         */
	if (reset_flag)
		ret_val = sctc_init_stats (SCCP_MODULE_ID, stat_type,
                                                   &ecode);
        if (SS7_FAILURE == ret_val)
                SC_A_ERR (ecode);


	/* SPR 1277: End fix */
}

#else

/*****************************************************************************
**      FUNCTION :
**           handles SM command category STAT if STATS is compile time disabled
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stat_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	U8bit param = 0; Boolean put_param = SS7_FALSE;

	sccp_stat_sm_cmd_resp (p_api, SS7_FAILURE, param, put_param,
	                       ESS7_STATS_DISABLED);

}

#endif /* #ifdef SCCP_STATS_ENABLED */

/*****************************************************************************
**      FUNCTION :
**            sends response to SM STAT category command
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stat_sm_cmd_resp
#ifdef ANSI_PROTO
	(U8bit 		* p_api,
	 return_t 	ret_val,
	 U8bit 		param,
         Boolean 	put_param,
	 error_t 	ecode)
#else
	(p_api, ret_val, param, put_param, ecode)
	 U8bit 		* p_api;
	 return_t 	ret_val;
	 U8bit 		param;
         Boolean 	put_param;
	 error_t 	ecode;

#endif
{
	sccp_sm_cmd_std_resp (p_api, ret_val, param, put_param, ecode);
}

