/***************************************************************************
**
**  FILE NAME:
**      sc_cong.c
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
**  08Aug2004 Hitesh Sharma            Fixed SPR # 13344
**  28Aug2003 Salil Agrawal            Fixed SPR # 12567
**  28Jun2002 Suyash Tripathi          Fixed SPR # 9101
**  24Jun@002 Sachin Bhatia            Fixed SPR # 9063
**  21May2002 Salil Agrawal            Fixed SPR # 8744
**  16May2002 Salil Agrawal            Fixed SPR # 8738
**  07Jul2000 Ramu Kandula             Fixed SPR # 4048
**  24Feb2000 Ramu Kandula             Fixed SPR # 2695
**  20May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#include "sc_mgtmr.h"
#include "sc_bcast.h"

/* SPR # 8744 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR 8744 fix end */
#define T_CON_TMR_BUF_LEN	5	

static void sccp_send_ssc_msg
	_ARGS_ ((msg_info_t * p_info));

/***************************************************************************
**
**      FUNCTION :
**         in congested sp condition sends SSC to source
****************************************************************************
**
**      DESCRIPTION :
**         SSC message is sent for every 8th msg recvd in congested
**         condition
**
**      NOTE :
**
***************************************************************************/

void 
sccp_congested_sp_msg_ind 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
    sccp_cong.counter ++;
#ifdef DISTRIBUTED_SCCP
	dsccp_send_cong_status_to_mate();
#endif
	
    if (MAX_CONG_CNTR_VAL <= sccp_cong.counter)
	{
		sccp_send_ssc_msg(p_info);
		sccp_cong.counter = 0;
	}
}

/***************************************************************************
**
**      FUNCTION :
**         sets congestion level of the local SCCP
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_changed_cong_level 
#ifdef ANSI_PROTO
	(U8bit level)
#else
	(level)
	U8bit level ;
#endif
{
	if (level > MAX_SCCP_CONG_LEVEL)
		sccp_cong.level = MAX_SCCP_CONG_LEVEL;
	else
		sccp_cong.level = level;

	MG_TRC (("SCCP :: SCMG : set local cong level to %d\n", 
		sccp_cong.level));
}

/***************************************************************************
**
**      FUNCTION :
**         handles a SSC message
****************************************************************************
**
**      DESCRIPTION :
**         on receiving SSC starts Tcon. also computation of
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_ssc 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
	/*U8bit tcon_timer_buf[T_CON_TMR_BUF_LEN];*/
	U8bit tcon_timer_buf[SCMG_TIMER_BUF_LEN];

	MG_TRC (("SCCP :: SCMG : recv SSC for pc %u nw %d with level %d\n",
	         p_info->pc, p_info->nw_id, p_info->sccp_cong_level));

/* SPR 9101 - Fix Start */
	/*if (p_info->p_sp->cls <= p_info->sccp_cong_level)*/
	if (p_info->p_sp->cls < p_info->sccp_cong_level)
	{
		if (IS_T_CON_RUNNING(p_info->p_sp))
		{
			sccp_stop_timer(&p_info->p_sp->t_con_timer_id);
			p_info->p_sp->t_con_running = SS7_FALSE;
		}
/* SPR 9101 - Fix - shifting the fix 4048 to the else part */
		/** SPR # 4048 Fix Start **/
#if 0

		if (IS_T_CON_RUNNING(p_info->p_sp))
		{
			sccp_stop_timer(&p_info->p_sp->t_con_timer_id);
			p_info->p_sp->t_con_running = SS7_FALSE;
		}
		
		tcon_timer_buf[0] = T_CON_TIMER_ID;
		tcon_timer_buf[1] = p_info->p_sp->nw_id;
		PUT_PC((&tcon_timer_buf[2]), p_info->p_sp->pc);

		if (SS7_SUCCESS == sccp_start_timer (sc_tim.t_con_timer_val,
		                                 tcon_timer_buf, SCMG_TIMER_BUF_LEN,
		                                 &(p_info->p_sp->t_con_timer_id)))
		{
			p_info->p_sp->t_con_running = SS7_TRUE;
			p_info->p_sp->active = SS7_TRUE;
		}
		/** SPR # 4048 Fix End **/
#endif
/* SPR 9101 - Fix End  */

/* SPR 9101 - Fix Start */
#if 0
		if (p_info->p_sp->cls < p_info->cong_level)
		{
			MG_TRC (("SCCP :: SCMG : congestion level increases\n"));
			p_info->p_sp->cls = p_info->cong_level;

			sccp_process_cong_param (p_info->p_sp);
		}
		else
		{
			MG_TRC (("SCCP :: SCMG : congestion level remains same\n"));
		}			
#endif
			MG_TRC (("SCCP :: SCMG : congestion level increases\n"));
			p_info->p_sp->cls = p_info->sccp_cong_level;
			/* Fix for SPR No : 13344 Start */
			p_info->p_sp->cong_cause = SCCP_CAUSE_SIG_CONGESTION;
			/* Fix for SPR No : 13344 Stop */
			sccp_process_cong_param (p_info->p_sp);
/* start SPR 12567 */
#ifdef DISTRIBUTED_SCCP
			dsccp_send_scmg_status_to_mate(p_info->p_sp);
#endif
/* end SPR 12567 */
/* SPR 9101 - Fix End  */

	}
	/* SPR 9101 - Fix Start */
	else
	{
		/** SPR # 4048 Fix Start **/

		if (IS_T_CON_RUNNING(p_info->p_sp))
		{
			sccp_stop_timer(&p_info->p_sp->t_con_timer_id);
			p_info->p_sp->t_con_running = SS7_FALSE;
		}
		
		tcon_timer_buf[0] = T_CON_TIMER_ID;
		tcon_timer_buf[1] = p_info->p_sp->nw_id;
		PUT_PC((&tcon_timer_buf[2]), p_info->p_sp->pc);

		if (SS7_SUCCESS == sccp_start_timer (sc_tim.t_con_timer_val,
		                                 tcon_timer_buf, SCMG_TIMER_BUF_LEN,
		                                 &(p_info->p_sp->t_con_timer_id)))
		{
			p_info->p_sp->t_con_running = SS7_TRUE;
			p_info->p_sp->active = SS7_TRUE;
		}

		/** SPR # 4048 Fix End **/
	}
	/* SPR 9101 - Fix End   */

	p_info->p_sp->active = SS7_TRUE;
}

/***************************************************************************
**
**      FUNCTION :
**         handles T congestion timeout
****************************************************************************
**
**      DESCRIPTION :
**         decreeases cls. recomputes restriction levels
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_t_con_timeout 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	U8bit * p_tmr_buf;
	scmg_info_t info;

	p_tmr_buf = p_api + API_HEADER_LEN;
	p_tmr_buf += SCCP_TIMER_ID_LEN;

	info.nw_id = *p_tmr_buf++;
	info.pc = GET_PC(p_tmr_buf);
	p_tmr_buf += PC_SIZE;

	MG_TRC (("SCCP :: SCMG : T con expires for pc %u nw %d\n", 
		info.pc, info.nw_id));

	if (SS7_NULL == (info.p_sp = sccp_db_find_sp (info.nw_id, info.pc)))
	{
		MG_TRC (("SCCP :: SCMG : cannot locate pc\n"));
		return;
	}

	/** SPR # 4048 Fix Start **/
	if (! IS_T_CON_RUNNING(info.p_sp))
	{
		/* T-Con already stopped */
		return;
	}

	info.p_sp->t_con_running = SS7_FALSE;
	/** SPR # 4048 Fix End **/

	info.p_sp->cls --;
	MG_TRC (("SCCP :: SCMG : cong level decremented to %d\n", 
		info.p_sp->cls));

	if (info.p_sp->cls > 0)
	{
		/* fix for SPR No: 13344 Start */
		info.p_sp->cong_cause = SCCP_CAUSE_SIG_CONGESTION;
		/* fix for SPR No: 13344 Stop */
		sccp_process_cong_param (info.p_sp);
/* start SPR 12567 */
#ifdef DISTRIBUTED_SCCP
		dsccp_send_scmg_status_to_mate(info.p_sp);
#endif
/* end SPR 12567 */

        /* Fix SPR 9063 start -- Sachin Bhatia */
        /* The buffer was incorrectly pointing */
        p_tmr_buf = p_api + API_HEADER_LEN;
        /* Fix SPR 9063 Ends -- Sachin Bhatia */

		if (SS7_SUCCESS == sccp_start_timer (sc_tim.t_con_timer_val,
		                                 p_tmr_buf, SCMG_TIMER_BUF_LEN,
		                                 &(info.p_sp->t_con_timer_id)))
		{
			info.p_sp->t_con_running = SS7_TRUE;
			info.p_sp->active = SS7_TRUE;
		}
	}
	else
	{
		MG_TRC (("SCCP :: SCMG : node out of congestion\n"));
		/* Fix for SPR No: 13344 Start */
		info.p_sp->cong_cause = SCCP_CAUSE_SIG_CONGESTION;
		/* Fix for SPR No: 13344 Stop */
		sccp_process_cong_param (info.p_sp);
/* start SPR 12567 */
#ifdef DISTRIBUTED_SCCP
		dsccp_send_scmg_status_to_mate(info.p_sp);
#endif
/* end SPR 12567 */
		info.p_sp->active = SS7_FALSE;
	}
}

/***************************************************************************
**
**      FUNCTION :
**         builds and sends ssc message
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_send_ssc_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	msg_info_t 	info;
	U8bit 		scmg_buf[SCMG_SSC_MSG_LEN], * p_scmg_buf;

	info.flag = 0;

	info.p_api = SS7_NULL;
	info.nw_id = p_info->nw_id;
	info.msg_type = UDT_MSG_TYPE;
	info.proto_class = 0;

	/* called addr */
	info.cd_addr.pc_ind = SS7_TRUE;
	info.cd_addr.ssn_ind = SS7_TRUE;
	info.cd_addr.pc = p_info->opc;
	info.cd_addr.ssn = SCMG_SSN;
	info.cd_addr.gti = 0;
      info.cd_addr.rout_ind = ROUTE_ON_SSN;

	/* calling addr */
	info.cg_addr.pc_ind = SS7_TRUE;
	info.cg_addr.ssn_ind = SS7_TRUE;
	info.cg_addr.pc = p_info->dpc;
	info.cg_addr.ssn = SCMG_SSN;
	info.cg_addr.gti = 0;
      info.cg_addr.rout_ind = ROUTE_ON_SSN;
	info.p_sp = p_info->p_sp;

	/* data */
	info.data.len = SCMG_SSC_MSG_LEN;
	info.data.p = &scmg_buf[0];
	p_scmg_buf = &scmg_buf[0];
	*p_scmg_buf++ = SCMG_SSC_MSG;
	*p_scmg_buf++ = SCMG_SSN;
	PUT_PC(p_scmg_buf, info.cg_addr.pc);
	p_scmg_buf += PC_SIZE;
	*p_scmg_buf++ = 0;
	*p_scmg_buf = sccp_cong.level;
	info.dpc = p_info->dpc;

	MG_TRC (("SCCP :: SCMG : sending SSC to nw %d pc %u\n",
	         info.nw_id, info.cd_addr.pc));

	sccp_m3_transfer_request (&info);
}

/***************************************************************************
**
**      FUNCTION :
**         processse congestion params
****************************************************************************
**
**      DESCRIPTION :
** 
**
**      NOTE :
**
***************************************************************************/
void 
sccp_process_cong_param 
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	sp_entry_t * p_sp ;
#endif
{
/* fix spr 8738 */
	S8bit rl=0, rsl=0;
	U8bit ril=0;
/* end fix 8738 */

	U8bit * p_css_list;
	U32bit i, j;
	ss_entry_t * p_ss, * p_css;

	/** SPR # 2695 Fix Start **/
	/* This procedure is applicable only in the case of ITU and ETSI */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		sccp_compute_cong_params (p_sp, &rl, &rsl, &ril);
		p_sp->rl = rl;
		p_sp->rsl = rsl;
	
		if ( ! (p_sp->ril == ril))
		{
			MG_TRC (("SCCP::SCMG: RIL changed for pc %d nw %d from "
		         	"%d to %d\n", p_sp->pc, p_sp->nw_id, p_sp->ril, ril));
	
			p_sp->ril = ril;
	
			for (i=0, p_ss = GET_SS_LIST_IN_SP(p_sp);
		     	i < GET_NUM_SS_IN_SP(p_sp); i++, p_ss = GET_NEXT_SS(p_ss))
			{
				
				for (j=0, p_css_list = GET_CSS_LIST(p_ss);
			     	j < GET_NUM_CSS(p_ss);
			     	j++, p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
				{
					p_css = GET_CSS_FROM_LIST(p_css_list);
					sccp_local_bcast (p_sp, p_css, LBCS_RIL);
				}
			}
		}
	}
#endif
	/** SPR # 2695 Fix Start **/
}

