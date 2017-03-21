/***************************************************************************
**
**  FILE NAME:
**      sc_bcast.c
**
****************************************************************************
**
**  FUNCTION:
**      Contains functions related to Local broadcast (LBCS) and
**      Broadcast (BCST)
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  08Apr2004 Hitesh Sharma           Fixed SPR 13344
**  24Feb2004 Hitesh Sharma           Fixed SPR 13263
**  20Nov2002 Ashish Sawalkar         Fixed SPR 10693
**  24Feb2000 Ramu Kandula            Fixed SPR 2695
**  24Feb2000 Ramu Kandula            Fixed SPR 2692
**  03Sep'99 Sudipta Pattar           Fixed SPR 1684
**  10May'99 Sudipta Pattar           Fixed SPR 1593
**  29Apr'99 Sudipta Pattar           Fixed SPR 1503
**  07Feb'99 Sudipta Pattar           Added event alarms
**  08Aug'98 Anil K.				  Connectionless ANSI Added.
**           Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#include "sc_bcast.h"

static void sccp_local_bcast_n_state_ind
	_ARGS_ ((ss_entry_t * p_ss));

static void sccp_local_bcast_n_pcstate_ind
	_ARGS_ ((sp_entry_t * p_sp, U8bit bcast_type));

/***************************************************************************
**
**      FUNCTION :
**         correspondiog to Q.714/D.9/sheet-1 & 2 on getting event
**         'Local broadcast of UIS' or 'Local broadcast of UOS'
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_local_bcast
#ifdef ANSI_PROTO
	(sp_entry_t 	* p_sp, 
	 ss_entry_t 	* p_ss, 
	 U8bit 		bcast_msg_type)
#else
	(p_sp, p_ss, bcast_msg_type)
	sp_entry_t     * p_sp ;
	ss_entry_t     * p_ss ;
	U8bit          bcast_msg_type ;
#endif
{
	U16bit state;

	switch (bcast_msg_type)
	{
		case LBCS_UIS:
		case LBCS_UOS:
			/* send SS alarm to sm */
			state = (p_ss->allowed ? SCCP_USER_IN_SERVICE : 
						 SCCP_USER_OUT_OF_SERVICE);
			SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SS, state, SS7_NULL, p_ss, SS7_NULL);

			sccp_local_bcast_n_state_ind (p_ss);
			break;

		case LBCS_RESUME:
		case LBCS_PAUSE:
		case LBCS_STATUS:
		case LBCS_SCCP_ACCESSIBLE:
		case LBCS_SCCP_INACCESSIBLE:
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
		case LBCS_RIL:
#endif
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
		case LBCS_SP_CONG:
#endif
			/* send SP alarm to sm */
			if ((bcast_msg_type != LBCS_SCCP_ACCESSIBLE)&&
				(bcast_msg_type != LBCS_SCCP_INACCESSIBLE))
			{
			 	if ( ! p_sp->allowed)
			 		state = SP_INACCESSIBLE;
			 	else
			 	{
				/* fix for SPR No: 13344 Start */
			 		if (p_sp->ril > 0)
	
				/* 	if (p_sp->cls > 0)	*/
				/* fix for SPR No: 13344 Stop */
			 			state = SP_CONGESTED;
			 		else
			 			state = SP_ACCESSIBLE;
			 	}
				SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SP, state, p_sp, SS7_NULL, SS7_NULL);
			}
			sccp_local_bcast_n_pcstate_ind (p_sp, bcast_msg_type);
			break;

		default:
			break;
	}
}

/***************************************************************************
**
**      FUNCTION :
**         local broadcast n_state indication to all concerned subsystems
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_local_bcast_n_state_ind 
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	ss_entry_t * p_ss ;
#endif
{
	U8bit 		* p_css_list;
	U32bit 		i;
	ss_entry_t 	* p_css;

	for (i=0, p_css_list = GET_CSS_LIST (p_ss);
	     i < GET_NUM_CSS (p_ss);
	     i++, p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
	{
		p_css = GET_CSS_FROM_LIST(p_css_list);

		/* SPR 1503: check if subsystem is registered */
		if (IS_SS_ALLOWED(p_css) && (p_css->registered))
			sccp_send_n_state_ind (p_ss, p_css);
	}
}

/***************************************************************************
**
**      FUNCTION :
**         local broadcast n_pc_state indication to all local concerned
**         subsystems
****************************************************************************
**
**      DESCRIPTION :
**          
**
**      NOTE :
**
***************************************************************************/

void 
sccp_local_bcast_n_pcstate_ind 
#ifdef ANSI_PROTO
	(sp_entry_t 	* p_sp, 
	 U8bit 		bcast_type)
#else
	(p_sp, bcast_type)
	sp_entry_t     * p_sp ;
	U8bit          bcast_type ;
#endif
{
	/* Fix for SPR No: 13263 start */
	U8bit 		* p_css_list; 
	U8bit           *sent_flag;
	ss_entry_t 	* p_ss, * p_css;
	U32bit 		i, j, k;

	sent_flag = (U8bit *)sccp_malloc(MAX_SS);

	/* Fix for SPR No: 13263 end */

	/* SPR 10846 - Fix Start */
	for ( k=0; k< MAX_SS ; k++ )
	{
		sent_flag[k] = SS7_FALSE; 
	}
	/* SPR 10846 - Fix End */
		
	for (i=0, p_ss = GET_SS_LIST_IN_SP(p_sp);
	     i < GET_NUM_SS_IN_SP(p_sp);
	     i++, p_ss = GET_NEXT_SS(p_ss))
	{
		for (j=0, p_css_list = GET_CSS_LIST(p_ss);
		     j < GET_NUM_CSS(p_ss);
		     j++, p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
		{
			p_css = GET_CSS_FROM_LIST(p_css_list);
			/* SPR 1503: check if subsystem is registered */
			/* SPR 10846 - Fix Start */
			if (IS_SS_ALLOWED(p_css) && (p_css->registered)
									&& (!sent_flag[(p_css->ssn)]))
			{
				sccp_send_n_pcstate_ind (p_sp, p_css, 
				                         bcast_type);
				sent_flag[(p_css->ssn)] = SS7_TRUE;

			}
			/* SPR 10846 - Fix End */
		}
	}
	/* Fix for SPR No: 13263 start */
	sccp_free(sent_flag);
	/* Fix for SPR No: 13263 end */
}


/***************************************************************************
**
**      FUNCTION :
**         Sends broadcast to all concerned signaling points
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_broadcast 
#ifdef ANSI_PROTO
	(scmg_info_t 	* p_info, 
	 U8bit 		bcast_type)
#else
	(p_info, bcast_type)
	scmg_info_t    * p_info ;
	U8bit          bcast_type ;
#endif
{
	U8bit 		* p_csp_list;
	U32bit 		i;
	sp_entry_t 	* p_csp;
	ss_entry_t 	* p_ss;

	/** SPR # 2692 Fix Start **/
	if (p_info->pc != p_info->informing_pc)
	{
		MG_TRC (("SCCP::SCMG: affected PC %d is different"
					" from informer PC %d; SSP not Broadcast \n", 
					p_info->pc, p_info->informing_pc));

		return;
	}
	/** SPR # 2692 Fix End **/


	p_ss = p_info->p_ss;
	for (i=0, p_csp_list = GET_CSP_LIST (p_ss);
	     i < GET_NUM_CSP (p_ss);
	     i++, p_csp_list = GET_NEXT_CSP_FROM_LIST(p_csp_list))
	{
		p_csp = GET_CSP_FROM_LIST(p_csp_list);

		/* SPR 1593: If csp is local signalling point, return */
		/* SPR 1684: Send OPC information to function */
		/* SPR 10849 - If SP is Prohibited */
		if ((!p_csp->local) && (p_csp->allowed))
		   sccp_send_ssa_or_ssp (p_ss, p_csp, bcast_type, 
						p_info->p_msg_info);
	}
}

/***************************************************************************
**
**      FUNCTION :
**         create  msg_info_t structure of the SSA/SSP msg to be sent
**         and calls SCRC function to send it.
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_send_ssa_or_ssp 
#ifdef ANSI_PROTO
	(ss_entry_t 	* p_ss, 
	 sp_entry_t 	* p_csp, 
	 U8bit 		bcast_type,
	 msg_info_t	* p_info)
#else
	(p_ss, p_csp, bcast_type, p_info)
	ss_entry_t     * p_ss ;
	sp_entry_t     * p_csp ;
	U8bit          bcast_type ;
        msg_info_t     * p_info ;

#endif
{
	msg_info_t 	info;
	U8bit 		scmg_buf[MAX_SCMG_MSG_LEN], * p_scmg_buf;

	MG_TRC (("SCCP::SCMG: broadcasting %s of SSN %d pc %d nw %d"
	         " to signaling point pc %d nw %d\n",
	         ((BCST_SSA == bcast_type) ? "SSA" : "SSP"),
	         p_ss->ssn, GET_SP_PC(GET_SP_OF_SS(p_ss)),
	         GET_SS_NW_ID(p_ss), GET_SP_PC(p_csp), GET_SP_NW_ID(p_csp)));
	/* SPR 10848 - Fix Start */
	ss7_mem_zero(&info,sizeof(msg_info_t));
	/* SPR 10848 - Fix Start */

	info.p_api = (U8bit *)SS7_NULL;
	info.flag = 0;
	info.nw_id = GET_SP_NW_ID(p_csp);
	info.msg_type = UDT_MSG_TYPE;
	info.proto_class = 0;

	/* information for routing */
	info.p_sp = GET_SP_OF_SS(p_ss);
	info.dpc = GET_SP_PC (info.p_sp);

	/* SPR 1684: If affected subsystem is not 
 	 * local, fill in info.dpc with local pc 
	 */
	if (!IS_SS_LOCAL(p_ss))
		info.dpc = p_info->dpc;

	/* called addr */
	info.cd_addr.pc_ind = SS7_TRUE;
	info.cd_addr.ssn_ind = SS7_TRUE;
	info.cd_addr.gti = 0;
	info.cd_addr.rout_ind = ROUTE_ON_SSN;
	info.cd_addr.pc = p_csp->pc;
	info.cd_addr.ssn = SCMG_SSN;
	/* SPR 10848 - Fix Start */
	/** Taking out 4th bit from ssf of csp to determine nat_ind **/
	info.cd_addr.nat_ind = (((p_csp->ssf) & 0x08 ) >> 3 );
	/* SPR 10848 - Fix Start */

	/* calling addr */
	info.cg_addr.pc_ind = SS7_TRUE;
	info.cg_addr.ssn_ind = SS7_TRUE;
	info.cg_addr.gti = 0;
	info.cg_addr.rout_ind = ROUTE_ON_SSN;
	info.cg_addr.pc = GET_SP_PC(GET_SP_OF_SS(p_ss));
	info.cg_addr.ssn = SCMG_SSN;
	/* SPR 10848 - Fix Start */
	/** Taking out 4th bit from ssf of csp to determine nat_ind **/
	info.cg_addr.nat_ind = (((p_csp->ssf) & 0x08 ) >> 3 );
	/* SPR 10848 - Fix Start */

	/* data */
	info.data.len = SCMG_MSG_LEN;
	info.data.p = &scmg_buf[0];

	p_scmg_buf =  &scmg_buf[0];
	*p_scmg_buf++ = ((BCST_SSA == bcast_type) ? SCMG_SSA_MSG : SCMG_SSP_MSG);
	*p_scmg_buf++ = p_ss->ssn;
	PUT_PC(p_scmg_buf, GET_SP_PC(GET_SP_OF_SS(p_ss)));
	p_scmg_buf += PC_SIZE;
	*p_scmg_buf = 0; /* multiplicity indicator */

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
