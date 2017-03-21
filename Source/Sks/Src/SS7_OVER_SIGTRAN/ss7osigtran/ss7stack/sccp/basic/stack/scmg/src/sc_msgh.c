/***************************************************************************
**
**  FILE NAME:
**      sc_msgh.c
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
**  08Aug2002  Ashish Sawalkr 	      Fixed SPR 9302
**  1Aug2002  Prateek Bidwalkar		  Fixed SPR 9221 
**  28Mar2000 Ramu Kandula            Fixed SPR 3042
**  24Feb2000 Ramu Kandula            Fixed SPR 2692
**  29Apr'99 Sudipta Pattar    -----  Fixed SPR 1499
**  07Feb'99 Sudipta Pattar    -----  Added Ericsson changes
**  08Aug'98 Anil K.				  Connectionless ANSI added
**  15May98  Sriganesh. Kini   -----  Original
**  18July 2001  pawanish   -----   Fixed SPR 5666
**  8April2002  pawanish   -----   Fixed SPR 8614
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"
#include "sc_bcast.h"
#include "sc_mgtmr.h"

#ifdef BACK_UP_SSN
void sccp_handle_sog(scmg_info_t *p_info);
void sccp_handle_sor(scmg_info_t *p_info);
void stop_t_coord_timer(ss_entry_t *p_ss);
void start_ignore_sst_timer(ss_entry_t *p_ss);

/** SPR# 9302 Start Fix **/
#ifndef __IGNORE_SST_TMOUT_FLAG__
#define __IGNORE_SST_TMOUT_FLAG__
void sccp_t_ignore_sst_timeout(U8bit *p_api);
#endif
/** SPR# 9302 End Fix **/

#endif

/***************************************************************************
**
**      FUNCTION :
**         handles a scmg message from peer SCCP
****************************************************************************
**
**      DESCRIPTION :
**         for msg SSA/SSP/SST/SSC call appropriate func which handles it
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_scmg_msg 
#ifdef ANSI_PROTO
	(msg_info_t 	* p_info)
#else
	(p_info)
	msg_info_t     * p_info ;
#endif
{
	U8bit scmg_msg_type, * p_scmg_msg;
	scmg_info_t info;
	extern sp_entry_t sccp_local_sp;

	info.nw_id = p_info->nw_id;
	p_scmg_msg = p_info->data.p;
	scmg_msg_type = *p_scmg_msg++;

	switch (scmg_msg_type)
	{
		/* These messages are common to ITU/ETSI/ANSI */
#ifdef BACK_UP_SSN
		case SCMG_SOR_MSG:
			info.ssn = *p_scmg_msg++;
			info.pc = GET_PC(p_scmg_msg);
			p_scmg_msg += PC_SIZE;
			info.ss_mult_ind = *p_scmg_msg;
			info.informing_pc = p_info->opc;
			break;
		case SCMG_SOG_MSG:
			info.ssn = *p_scmg_msg++;
			info.pc = GET_PC(p_scmg_msg);
			p_scmg_msg += PC_SIZE;
			info.ss_mult_ind = *p_scmg_msg;
			info.informing_pc = p_info->opc;
			break;
#endif
			
		case SCMG_SSA_MSG:
		case SCMG_SSP_MSG:
		case SCMG_SST_MSG:
			if (! (SCMG_MSG_LEN == p_info->data.len))
			{
				MG_TRC (("SCCP::SCMG: invalid length %d for"
				         " SCMG msg\n", p_info->data.len));
				return;
			}

			info.ssn = *p_scmg_msg++;
			info.pc = GET_PC(p_scmg_msg);
			p_scmg_msg += PC_SIZE;
			info.ss_mult_ind = *p_scmg_msg;
                        if ((scmg_msg_type == SCMG_SSA_MSG) || (scmg_msg_type == SCMG_SSP_MSG))
                        {
				/** SPR 5666 Fix start **/
				if (info.pc == sccp_local_sp.pc)
				{
					MG_TRC (("SCCP::SCMG: error: affected PC %d is same as own PC %d\n", info.pc, sccp_local_sp.pc));
					return;
				}
				/** SPR 5666 Fix end **/
			}

			/** SPR 2692 Fix Start **/
			/** This check has to be done in the broadcast procedure instead **/
#if 0
			/* SPR 1499: Start fix 
			 * check if informer point code is equal	
			 * to the affected point code for SSP and SSA messages
			 */
		
                        if ((scmg_msg_type == SCMG_SSA_MSG) ||
                                (scmg_msg_type == SCMG_SSP_MSG))
                        {
				if (info.pc != p_info->opc)
				{
					MG_TRC (("SCCP::SCMG: error:"
					" affected PC %d is different"
				         " from informer PC %d\n", info.pc, p_info->opc));
					return;
				}
			}
			/* SPR 1499: End fix */
#endif

			info.informing_pc = p_info->opc;
			/** SPR #2692 Fix End **/

			break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
		case SCMG_SSC_MSG:

/* Ericsson changes - ssc not supported */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) )  && defined (SCCP_ERICSSON_ITU)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
	{
		MG_TRC (("SCCP::SCMG: unsupported SCMG msg %d\n", 
	     	  		scmg_msg_type));
		return;
	}	
#endif

			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
				if (! (SCMG_SSC_MSG_LEN == p_info->data.len))
				{
					MG_TRC (("SCCP::SCMG: invalid length %d for SCMG msg\n",p_info->data.len));
					return;
				}

				info.ssn = *p_scmg_msg++;
				info.pc = GET_PC(p_scmg_msg);
				p_scmg_msg += PC_SIZE;
				info.ss_mult_ind = *p_scmg_msg++;
				info.sccp_cong_level = *p_scmg_msg;
			}
			else
			{
				MG_TRC (("SCCP::SCMG: unsupported SCMG msg %d\n", 
				         scmg_msg_type));
				return;
			}

			break;

#endif

#if 0 /* These optional messages are not supported now */
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
		case SCMG_SBR_MSG:
		case SCMG_SNR_MSG:
		case SCMG_SRT_MSG:
			if ((COMPARE_ANSI) || (COMPARE_BCGR))
			{
				if (! (SCMG_MSG_LEN == p_info->data.len))
				{
					MG_TRC (("SCCP::SCMG: invalid length %d for"
					         " SCMG msg\n"));
					return;
				}

				info.ssn = *p_scmg_msg++;
				info.pc = GET_PC(p_scmg_msg);
				p_scmg_msg += PC_SIZE;
				info.ss_mult_ind = *p_scmg_msg;
			}
			else
			{
				MG_TRC (("SCCP::SCMG: unsupported SCMG msg %d\n", 
				         scmg_msg_type));
				return;
			}

			break;
#endif
#endif

		default:
			MG_TRC (("SCCP::SCMG: unsupported SCMG msg %d\n", 
			         scmg_msg_type));
			return;
	}

	info.p_msg_info = p_info;
#ifdef BACK_UP_SSN
	if (scmg_msg_type == SCMG_SOR_MSG)
	{
		if ( (SS7_NULL == (info.p_sp = sccp_db_find_sp (info.nw_id, p_info->dpc))))
			return;
		if (SS7_NULL == (info.p_ss = sccp_db_find_ss (info.p_sp, 
		                                               info.ssn)))
		{
			MG_TRC (("SCCP::SCMG: SCMG msg for unknown SSN %d pc %d"
			         " nw %d. dropped\n",
			         info.ssn, info.pc, info.nw_id));
			return;
		}
		sccp_handle_sor(&info);
		return;
	}
#endif

	if (! (SS7_NULL == (info.p_sp = sccp_db_find_sp (info.nw_id, info.pc))))
	{
#if 0
		if (! info.p_sp->local)
		{
			MG_TRC (("SCCP::SCMG: SCMG msg for non local pc %d"
			         " on nw %d. dropped\n",
			         info.pc, info.nw_id));
			return;
		}
#endif

		if (SCMG_SSN == info.ssn)
		{
			info.p_ss = &(info.p_sp->scmg_ss);
		}
		else if (SS7_NULL == (info.p_ss = sccp_db_find_ss (info.p_sp, 
		                                               info.ssn)))
		{
			MG_TRC (("SCCP::SCMG: SCMG msg for unknown SSN %d pc %d"
			         " nw %d. dropped\n",
			         info.ssn, info.pc, info.nw_id));
			return;
		}

		/** SPR # 3042 Fix Start **/
		/** SPR # 8614 Fix Start **/
		if(info.ssn != SCMG_SSN)
		{
			if ((info.p_sp->local) && (! info.p_ss->registered))
			{
				MG_TRC (("SCCP::SCMG: SCMG msg for unequipped SSN %d pc %d"
			         	" nw %d. dropped\n",
			         	info.ssn, info.pc, info.nw_id));
					/*	info.p_ss->registered = SS7_TRUE; */
				return; /* Set registered the p_ss by Amaresh commented return */
			}
		}
		/** SPR # 8614 Fix End **/
		/** SPR # 3042 Fix End **/
	}
	else
	{
		MG_TRC (("SCCP::SCMG: unknown nw %d pc %u in SCMG msg\n", 
		         info.nw_id, info.pc));
		return;
	}

	switch (scmg_msg_type)
	{
		case SCMG_SSA_MSG:
			sccp_handle_ssa (&info);
			break;

		case SCMG_SSP_MSG:
			sccp_handle_ssp (&info);
			break;

		case SCMG_SST_MSG:
			sccp_handle_sst (&info);
			break;

		case SCMG_SSC_MSG:
			sccp_handle_ssc (&info);
			break;

#if 0 /* ANSI optional msg procedures not defined now */
		case SCMG_SBR_MSG:
			sccp_handle_sbr (&info);
			break;

		case SCMG_SNR_MSG:
			sccp_handle_snr (&info);
			break;

		case SCMG_SRT_MSG:
			sccp_handle_srt (&info);
			break;
#endif
#ifdef BACK_UP_SSN
		case SCMG_SOG_MSG:
			sccp_handle_sog(&info);
			break;
#endif
		default:
			MG_TRC (("SCCP::SCMG: unsupported SCMG msg %d\n", 
			         scmg_msg_type));
			return;
	}
}


/***************************************************************************
**
**      FUNCTION :
**         handles a scmg SOG message from peer SCCP
****************************************************************************
**
**      DESCRIPTION :
**         IF waiting for grant flag is true for the subsystem, then it
**	     gives N-COORD confirm to the user else ignores the message
**
**      NOTE :
**
***************************************************************************/

#ifdef BACK_UP_SSN
void sccp_handle_sog
#ifdef ANSI_PROTO
	(scmg_info_t *p_info)
#else
	(p_info)
	scmg_info_t *p_info;
#endif
{
        U8bit *p_api, *p_elem;
        U16bit api_len;
		
		/** SPR 9302 Start Fix **/
		extern U8bit sccp_state;		
		/** SPR 9302 End Fix **/

        api_len = SCCP_N_COORD_CONFIRM_LEN;
        if(p_info->p_ss->waiting_for_grant == SS7_TRUE)
        {
                stop_t_coord_timer(p_info->p_ss);
                if (SS7_NULL == (p_api = sccp_malloc(api_len)))
                {
                        MG_TRC (("SCCP::SCMG: MALLOC FAIL cannot send n_coord_ind"));
                        return;
                }
                sccp_fill_api_header (p_api, SCCP_N_COORD_CONFIRM, 2, api_len);
                p_elem = p_api + API_HEADER_LEN;

                /* put mandatory elements */
                p_elem = sccp_put_affected_ss_elem (p_elem, p_info->p_ss);
                *p_elem =  p_info->ss_mult_ind;
                start_ignore_sst_timer(p_info->p_ss);
		sccp_sendto_tc(p_api, p_info->p_ss);
		MARK_SS_PROHIBITED(p_info->p_ss);
		sccp_inform_trans_func(p_info->p_sp, p_info->p_ss);
		SCCP_SEND_SS_ENTRY_UPDATE(p_info->p_ss);
		sccp_broadcast(p_info, BCST_SSP);
/* SPR # 9221 Fix Start */
		SC_STAT_Q752_TS_SCCP_SOG_RECV;
		SC_STAT_Q752_INR_SCCP_SOG_RECV;
/* SPR # 9221 Fix End */
        }
	else
	{
		MG_TRC (("SCCP::SCMG: WAITING FOR GRANT FALSE"));
        }
        return;

}

/***************************************************************************
**
**      FUNCTION :
**         handles a scmg SOR message from peer SCCP
****************************************************************************
**
**      DESCRIPTION :
**	     It gives N-COORD ind. to the user 
**
**      NOTE :
**
**************************************************************************/
void sccp_handle_sor
#ifdef ANSI_PROTO
	(scmg_info_t *p_info)
#else
	(p_info)
	scmg_info_t *p_info;
#endif
{
        U8bit *p_api, *p_elem;
        U16bit api_len;

        api_len = SCCP_N_COORD_IND_LEN;
        if (SS7_NULL == (p_api = sccp_malloc (api_len)))
        {
                MG_TRC (("SCCP::SCMG: cannot send n_coord_confirm"));
                return;
        }
        sccp_fill_api_header (p_api, SCCP_N_COORD_INDICATION, 2, api_len);
        p_elem = p_api + API_HEADER_LEN;

        /* put mandatory elements */
	PUT_PC(p_elem, p_info->pc);
	p_elem += PC_SIZE;
	*p_elem++ = p_info->ssn;
        *p_elem =  p_info->ss_mult_ind;

        sccp_sendto_tc (p_api, p_info->p_ss);
}

/***************************************************************************
**
**      FUNCTION :
**         it stops the t coord timer 
****************************************************************************
**
**      DESCRIPTION :
**	     When a SOR message is sent tcoord timer is started. When an SOG 
**	     message is received, then the timer is stopped
**
**      NOTE :
**
**************************************************************************/

void stop_t_coord_timer
#ifdef ANSI_PROTO
	(ss_entry_t *p_ss)
#else
	(p_ss)
	ss_entry_t *p_ss;
#endif
{
        sp_entry_t * p_sp;

        p_sp = GET_SP_OF_SS(p_ss);
 /* SPR FIX 7890 start */
        MG_TRC (("SCCP::SCMG: stopping T Coord Timer for SSN %d  pc %u nw %d\n", GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
/*SPR FIX 7890 end */

        if (p_ss->t_coord_timer_running == SS7_TRUE)
        {
                sccp_stop_timer (&p_ss->t_coord_timer_id);
                p_ss->t_coord_timer_running = SS7_FALSE;
                p_ss->waiting_for_grant = SS7_FALSE;
        }
        else
        {
                MG_TRC (("SCCP::SCMG: T Coord Timer not running\n"));
        }
}

/***************************************************************************
**
**      FUNCTION :
**         it starts ignore sst timer 
****************************************************************************
**
**      DESCRIPTION :
**	     When a SOG message is received ignore sst timer is started. If any
**	     SST message for the subsystem is received during this time
**		it is ignored
**
**      NOTE :
**
**************************************************************************/

void start_ignore_sst_timer
#ifdef ANSI_PROTO
	(ss_entry_t *p_ss)
#else
	(p_ss)
	ss_entry_t *p_ss;
#endif
{
        sp_entry_t *p_sp;
        U8bit sst_tmr_buf[SCMG_TIMER_BUF_LEN], * p_tmr_buf = sst_tmr_buf;
        p_sp = GET_SP_OF_SS(p_ss);
/* SPR FIX 7890 starts */
        MG_TRC (("SCCP::SCMG: starting Ignore SST Timer for SSN %d  pc %u nw %d\n ", GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
/*SPR FIX 7890 ends */

        if(p_ss->t_ignore_sst_timer_running == SS7_FALSE)
        {
                *p_tmr_buf = T_IGNORE_SST_TIMER_ID;
                p_tmr_buf += SCCP_TIMER_ID_LEN;
                *p_tmr_buf++ = p_sp->nw_id;
                PUT_PC(p_tmr_buf, p_sp->pc);
                p_tmr_buf += PC_SIZE;
                *p_tmr_buf = p_ss->ssn;
                if (SS7_SUCCESS == sccp_start_timer(T_IGNORE_SST_TIMER_VAL, sst_tmr_buf, SCMG_TIMER_BUF_LEN, &p_ss->t_coord_timer_id))
                {
                        p_ss->t_ignore_sst_timer_running = SS7_TRUE;
                        p_ss->ignore_sst_mark = SS7_TRUE;
                }
	}
        else
        {
                MG_TRC(("SCCP::SCMG:Ignore SST already in progress\n"));
        }
}

/***************************************************************************
**
**      FUNCTION :
**         sccp_t_ignore_sst_timeout 
****************************************************************************
**
**      DESCRIPTION :
**	     This functiuon handles the ignore sst timer timeout. When this
**	     timeout occurs the SST messages are not ignored
**
**      NOTE :
**
**************************************************************************/

void sccp_t_ignore_sst_timeout
#ifdef ANSI_PROTO
	(U8bit *p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
        U8bit * p_tmr_buf;
        scmg_info_t info, * p_info = &info;

        p_tmr_buf = p_api + API_HEADER_LEN;
        p_tmr_buf += SCCP_TIMER_ID_LEN;

        p_info->nw_id = *p_tmr_buf++;
        p_info->pc = GET_PC(p_tmr_buf);
        p_tmr_buf += PC_SIZE;
        p_info->ssn = *p_tmr_buf;
/* SPR FIX 7890 starts */
	MG_TRC (("SCCP::SCMG: T  Ignore SST Timer expires for SSN %d pc %u nw %d\n", p_info->ssn, p_info->pc, p_info->nw_id));
/*SPR FIX 7890 ends */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->pc)))
        {
                MG_TRC (("SCCP::SCMG: could not find signaling point\n"));
                return;
        }
        else
        {
                   if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss(p_info->p_sp,p_info->ssn)))
                {
                        MG_TRC (("SCCP::SCMG: could not find subsystem\n"));
                        return;
                }
        }
	if(p_info->p_ss->t_ignore_sst_timer_running == SS7_FALSE)
        {
                return;
        }
        else
        {
                p_info->p_ss->t_ignore_sst_timer_running = SS7_FALSE;
                p_info->p_ss->ignore_sst_mark = SS7_FALSE;
                return;
        }
}
#endif

#if 0
void sccp_t_coord_timeout(U8bit *p_api)
{
        U8bit * p_tmr_buf;
        scmg_info_t info, * p_info = &info;

        p_tmr_buf = p_api + API_HEADER_LEN;
        p_tmr_buf += SCCP_TIMER_ID_LEN;

        p_info->nw_id = *p_tmr_buf++;
        p_info->pc = GET_PC(p_tmr_buf);
        p_tmr_buf += PC_SIZE;
        p_info->ssn = *p_tmr_buf;
	MG_TRC (("SCCP::SCMG: T Coord Timer expires for SSN %d pc %lu nw %d\n", p_info->ssn, p_info->pc, p_info->nw_id));
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, p_info->pc)))
        {
                MG_TRC (("SCCP::SCMG: could not find signaling point\n"));
                return;
        }
        else
        {
                   if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss (p_info->p_sp,p_info->ssn)))
                {
                        MG_TRC (("SCCP::SCMG: could not find subsystem\n"));
                        return;
                }
        }
	if(p_info->p_ss->t_coord_timer_running == SS7_FALSE)
        {
                return;
        }
        else
        {
                p_info->p_ss->waiting_for_grant = SS7_FALSE;
                p_info->p_ss->t_coord_timer_running = SS7_FALSE;
                return;
        }
}
#endif
