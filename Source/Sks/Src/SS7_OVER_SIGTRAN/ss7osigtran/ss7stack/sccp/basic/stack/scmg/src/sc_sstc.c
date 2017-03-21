/***************************************************************************
**
**  FILE NAME:
**      sc_sstc.c
**
****************************************************************************
**
**  FUNCTION:
**			 Contain functions related to subsystem test.
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  03Feb2003 Suyash Tripathi         Fixed SPR # 10848
**  20Nov2002 Ashish Sawalkar         Fixed SPR # 10693
**  26Feb2000 Ramu Kandula            Fixed SPR # 2757
**  24Feb2000 Ramu Kandula            Fixed SPR # 2694
**  08Aug'98 Anil K.				  Connectionless ANSI added
**  19May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"
#include "sc_bcast.h"
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
#include "sc_mgtmr.h"

void sccp_send_sst_msg
	_ARGS_ ((ss_entry_t * p_ss));

/***************************************************************************
**
**      FUNCTION :
**         conducts subsystem test for a subsystem or the management subsys
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_start_sst 
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	ss_entry_t * p_ss ;
#endif
{
	sp_entry_t * p_sp;
	U8bit sst_tmr_buf[SCMG_TIMER_BUF_LEN], * p_tmr_buf = sst_tmr_buf;

	p_sp = GET_SP_OF_SS(p_ss);
	if(p_sp->local == SS7_TRUE)
		return ;
	MG_TRC (("SCCP::SCMG: starting subsystem test for SSN %d  pc %u nw %d\n",
	         GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
 
	if ( ! IS_SST_IN_PROGRESS(p_ss))
	{
#ifdef DISTRIBUTED_SCCP
		p_ss->sst_instance_id = sc_opt.dsccp_local_instance_id;
#endif
		/* Fill buffer to start Ta timer */
		*p_tmr_buf = T_STAT_INFO_TIMER_ID;
		p_tmr_buf += SCCP_TIMER_ID_LEN;
		*p_tmr_buf++ = p_sp->nw_id;
		PUT_PC(p_tmr_buf, p_sp->pc);
		p_tmr_buf += PC_SIZE;
		*p_tmr_buf = p_ss->ssn;
	
		if (SS7_SUCCESS == sccp_start_timer(p_ss->prev_t_stat_info_timer_val,
		                                sst_tmr_buf, SCMG_TIMER_BUF_LEN,
		                                &p_ss->t_stat_info_timer_id))
		{
			p_ss->t_stat_info_running = SS7_TRUE;
		}
	}
	else
	{
		MG_TRC (("SCCP::SCMG: subsystem test already in progress\n"));
	}
}


/***************************************************************************
**
**      FUNCTION :
**          stops subsystem test for a subsystem
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_stop_sst 
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	ss_entry_t * p_ss ;
#endif
{
	sp_entry_t * p_sp;

	p_sp = GET_SP_OF_SS(p_ss);
	MG_TRC (("SCCP::SCMG: stopping subsystem test for SSN %d  pc %u nw %d\n",
	         GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
 
	if (IS_SST_IN_PROGRESS(p_ss))
	{
#ifdef DISTRIBUTED_SCCP
		p_ss->sst_instance_id = DSCCP_INVALID_INSTANCE_ID;
#endif
		sccp_stop_timer (&p_ss->t_stat_info_timer_id);
		p_ss->t_stat_info_running = SS7_FALSE;
		CANCEL_UPU_RECEIVED(p_sp);
	}
	else
	{
		MG_TRC (("SCCP::SCMG: subsystem test not running\n"));
	}
}


/***************************************************************************
**
**      FUNCTION :
**         handles timer stat info timeout
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void sccp_handle_t_stat_info_timeout (U8bit * p_api)
{
	U8bit * p_tmr_buf;
	scmg_info_t info, * p_info = &info;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	p_tmr_buf = p_api + API_HEADER_LEN;
	p_tmr_buf += SCCP_TIMER_ID_LEN;

	p_info->nw_id = *p_tmr_buf++;
	p_info->pc = GET_PC(p_tmr_buf);
	p_tmr_buf += PC_SIZE;
	p_info->ssn = *p_tmr_buf;

	MG_TRC (("SCCP::SCMG: T stat info expires for SSN %d pc %u nw %d\n",
	         p_info->ssn, p_info->pc, p_info->nw_id));

	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, p_info->pc)))
	{
		MG_TRC (("SCCP::SCMG: could not find signaling point\n"));
		return;
	}
	else
	{
		if ( ( ! (SCMG_SSN == p_info->ssn)) &&
		    (SS7_NULL == (p_info->p_ss = sccp_db_find_ss (p_info->p_sp, p_info->ssn))))
		{
			MG_TRC (("SCCP::SCMG: could not find subsystem\n"));
			return;
		}
	}
	
	if(p_info->p_sp->local == SS7_TRUE)
		return ;


	if (SCMG_SSN == p_info->ssn)
	{
		p_info->p_ss = &p_info->p_sp->scmg_ss;
		/** SPR # 2694 Fix Start **/
		if ( ! p_info->p_ss->t_stat_info_running)
		{
			/** Timer already stopped ; Ignore timeout msg **/
			return;
		}
		/** SPR # 2694 Fix End **/

		p_info->p_ss->t_stat_info_running = SS7_FALSE;
		if (IS_UPU_RECEIVED(p_info->p_sp))
		{
			CANCEL_UPU_RECEIVED(p_info->p_sp);
			if ( ! (MTP3_CAUSE_USER_PART_UNAV_UNEQUIP_REMOTE_USER ==
			        UPU_CAUSE(p_info->p_sp)))
			{
				sccp_send_sst_msg (p_info->p_ss);

				/* adjust the t stat info timer */
				p_info->p_ss->prev_t_stat_info_timer_val +=
					T_STAT_INFO_TIMER_STEP_VALUE;
				if (p_info->p_ss->prev_t_stat_info_timer_val >
				    sc_tim.t_stat_info_end_timer_val)
					p_info->p_ss->prev_t_stat_info_timer_val =
					    sc_tim.t_stat_info_end_timer_val;

				sccp_start_sst (p_info->p_ss);
			}
		}
		else
		{
                  MARK_SCCP_ALLOWED(p_info->p_sp);
				  sccp_scmg_spac_bcast (p_info->p_sp, SS7_FALSE);
#ifdef DISTRIBUTED_SCCP
                dsccp_send_scmg_status_to_mate(p_info->p_sp);
#endif
                     SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
                     MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: comes up\n",
                         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

				/** SPR 10883 - Blocking the repetitive pc_state **
				 ** indication.LBCS_SCCP_ACCESSIBLE has already  ** 
				 ** been broadcasted in sccp_scmg_spac_bcast.	 **
				 **/  
               /*sccp_local_bcast(p_info->p_sp, SS7_NULL, LBCS_SCCP_ACCESSIBLE);*/
               SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SP, SP_ACCESSIBLE, p_info->p_sp,
                                        SS7_NULL, SS7_NULL);

		}
	}
	else
	{
		/** SPR # 2694 Fix Start **/
		if ( ! p_info->p_ss->t_stat_info_running)
		{
			/** Timer already stopped ; Ignore timeout msg **/
			return;
		}
		/** SPR # 2694 Fix End **/

		p_info->p_ss->t_stat_info_running = SS7_FALSE;
		sccp_send_sst_msg (p_info->p_ss);

		/* adjust the t stat info timer */
		p_info->p_ss->prev_t_stat_info_timer_val +=
			T_STAT_INFO_TIMER_STEP_VALUE;
		if (p_info->p_ss->prev_t_stat_info_timer_val >
		    sc_tim.t_stat_info_end_timer_val)
			p_info->p_ss->prev_t_stat_info_timer_val =
			    sc_tim.t_stat_info_end_timer_val;

		sccp_start_sst (p_info->p_ss);
	}
}

/***************************************************************************
**
**      FUNCTION :
**        handles a subsystem test message
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_sst 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
	msg_info_t info;
	U8bit scmg_buf[MAX_SCMG_MSG_LEN];

#ifdef BACK_UP_SSN
	if(p_info->p_ss->ignore_sst_mark == SS7_TRUE)
	{
		MG_TRC (("IGNORE SST TIMER RUNNING IGNORING SST\n"));
		return ;
	}
#endif
	scmg_buf[0] = SCMG_SSA_MSG;
	scmg_buf[1] = p_info->ssn;
	PUT_PC((&scmg_buf[2]), p_info->pc);
	scmg_buf[2+PC_SIZE] = 0; /* mult ind */

	MG_TRC (("SCCP::SCMG: recvd SST for SSN %d pc %u nw_id %d\n",
	         p_info->ssn, p_info->pc, p_info->nw_id));

	if ( ! IS_SS_ALLOWED(p_info->p_ss))
	{
		MG_TRC (("SCCP::SCMG: subsystem is prohibited\n"));
		return;
	}

	MG_TRC (("SCCP::SCMG: subsystem is allowed. sending SSA\n"));
	/* SPR 10848 - Fix Start */
	ss7_mem_zero(&info,sizeof(msg_info_t));
	/* SPR 10848 - Fix End */

	info.flag = 0;
	info.nw_id = p_info->nw_id;
	info.msg_type = UDT_MSG_TYPE;
	info.proto_class = 0;
	info.p_api = p_info->p_msg_info->p_api;
	info.dpc = p_info->p_msg_info->dpc ;

	/* called addr */
	info.cd_addr.pc_ind = SS7_TRUE;
	info.cd_addr.ssn_ind = SS7_TRUE;
	info.cd_addr.gti = 0;
	info.cd_addr.rout_ind = ROUTE_ON_SSN;
	info.cd_addr.pc = p_info->p_msg_info->opc;
	info.cd_addr.ssn = SCMG_SSN;
	/* SPR 10848 - Fix Start */
	/** Taking out 4th bit from ssf  to determine nat_ind **/
	info.cd_addr.nat_ind = (((p_info->p_msg_info->sio.ssf) & 0x08 ) >> 3 );
	/* SPR 10848 - Fix End */

	/* calling addr */
	info.cg_addr.pc_ind = SS7_TRUE;
	info.cg_addr.ssn_ind = SS7_TRUE;
	info.cg_addr.gti = 0;
	info.cg_addr.rout_ind = ROUTE_ON_SSN;
	info.cg_addr.pc = p_info->p_msg_info->dpc;
	info.cg_addr.ssn = SCMG_SSN;
	/* SPR 10848 - Fix Start */
	/** Taking out 4th bit from ssf to determine nat_ind **/
	info.cg_addr.nat_ind = (((p_info->p_msg_info->sio.ssf) & 0x08 ) >> 3 );
	/* SPR 10848 - Fix End */

	/* data */
	info.data.len = SCMG_MSG_LEN;
	info.data.p = scmg_buf;

	info.p_sp = p_info->p_sp;
	info.p_ss = p_info->p_ss;

	sccp_m3_transfer_request (&info);
}


/***************************************************************************
**
**      FUNCTION :
**         builds and sends a subsystem test message
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_send_sst_msg 
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	ss_entry_t * p_ss ;
#endif
{
	sp_entry_t * p_sp;
	msg_info_t info;
	U8bit scmg_buf[MAX_SCMG_MSG_LEN];
	U8bit tmp_buf[1];
	extern sp_entry_t sccp_local_sp; /** For SPR # 2757 Fix **/

	p_sp = GET_SP_OF_SS(p_ss);

	scmg_buf[0] = SCMG_SST_MSG;
	scmg_buf[1] = p_ss->ssn;
	PUT_PC((&scmg_buf[2]), p_sp->pc);
	scmg_buf[2+PC_SIZE] = 0; /* multi ind */

	MG_TRC (("SCCP::SCMG : sending SST for SSN %d pc %u nw_id %d\n",
	         p_ss->ssn, p_sp->pc, p_sp->nw_id));
    	/* SPR 10848 - Fix Start */
	ss7_mem_zero(&info,sizeof(msg_info_t));
	/* SPR 10848 - Fix End */


	info.flag = 0;
	info.nw_id = p_sp->nw_id;
	info.msg_type = UDT_MSG_TYPE;
	info.proto_class = 0;
	info.p_api = SS7_NULL;

	/* called addr */
	info.cd_addr.pc_ind = SS7_TRUE;
	info.cd_addr.ssn_ind = SS7_TRUE;
	info.cd_addr.gti = 0;
	info.cd_addr.rout_ind = ROUTE_ON_SSN;
	info.cd_addr.pc = p_sp->pc;
	info.cd_addr.ssn = SCMG_SSN;
   	/* SPR 10848 - Fix Start */
	/** Taking out 4th bit from ssf of sp to determine nat_ind **/
	info.cd_addr.nat_ind = (((p_sp->ssf) & 0x08 ) >> 3 );
	/* SPR 10848 - Fix End */


	/* calling addr */
	info.cg_addr.pc_ind = SS7_TRUE;
	info.cg_addr.ssn_ind = SS7_TRUE;
	info.cg_addr.gti = 0;
	info.cg_addr.rout_ind = ROUTE_ON_SSN;
	/** SPR # 2757 Fix Start **/
	/* info.cg_addr.pc = GET_SP_OF_SS(GET_CSS_FROM_LIST(GET_CSS_LIST(p_ss)))->pc; */
	info.cg_addr.pc = sccp_local_sp.pc;
	/** SPR # 2757 Fix End **/
	info.cg_addr.ssn = SCMG_SSN;
    	/* SPR 10848 - Fix Start */
	/** Taking out 4th bit from ssf of sp to determine nat_ind **/
	info.cg_addr.nat_ind = (((p_sp->ssf) & 0x08 ) >> 3 );
	/* SPR 10848 - Fix End */


	/* data */
	info.data.len = SCMG_MSG_LEN;
	info.data.p = scmg_buf;

	info.p_sp = p_sp;
	tmp_buf[0] = SCCP_N_UNITDATA_REQUEST;
	info.p_api = tmp_buf; /* Indicate that it is message generated
                                 from upper layer */

	/* SPR 10693 Fix: Checking DPC Congestion */
	if (sccp_determine_restriction(&info) == SS7_TRUE)
	{
		RC_TRC (("SCCP::SCRC: Traffic limitation. msg dropped\n"));
	}
	else
	{
		sccp_m3_transfer_request (&info);
	}
}
