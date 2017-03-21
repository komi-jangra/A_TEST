/***************************************************************************
**
**  FILE NAME:
**      sc_ssmg.c
**
****************************************************************************
**
**  FUNCTION:
**      Contains functions related to subsystem management
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  17Jan2003 Ashish Sawalkar	      Fixed SPR # 11098 
**  08Aug2002 Ashish Sawalkar	      Fixed SPR # 9302 
**  01Aug2002 Prateek Bidwalkar       Fixed SPR # 9221
**  20Aug2002 Prateek Bidwalkar       Fixed SPR # 9502
**  24Oct2001 Prateek Bidwalkar       Fixed SPR # 6750
**  14Jul2000 Ramu K                  Fixed SPR #4047
**  24Feb2000 Ramu K                  Fixed SPR #2691
**  22Feb2000 Ramu K                  Fixed SPR #2662
**  19Feb2000 Ramu K                  Fixed SPR #2638
**  08Aug'98 Anil K.				  Connectionless ANSI added
**  25May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#include "sc_bcast.h"
#include "sc_mgtmr.h"
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */

static void sccp_handle_n_state_req_uis 
	_ARGS_ ((scmg_info_t * p_info));

static void sccp_handle_n_state_req_uos 
	_ARGS_ ((scmg_info_t * p_info));

#ifdef BACK_UP_SSN
void send_sor_message(scmg_info_t *p_info);
void send_sog_message(scmg_info_t *p_info);
void start_t_coord_timer(ss_entry_t *p_ss);

/** SPR 9302 Start Fix **/
#if 0
void sccp_t_coord_timeout(U8bit *p_api);
void sccp_n_coord_request(U8bit *p_api);
void sccp_n_coord_response(U8bit *p_api);
#endif
/** SPR 9302 End Fix **/

extern return_t sccp_parse_n_coord_req_api (U8bit *p_api, scmg_info_t *p_info);
extern return_t sccp_parse_n_coord_response_api (U8bit *p_api, scmg_info_t *p_info);

extern return_t sccp_db_search_back_up_ss(U8bit ssn, pc_t *point_code);
#endif


/***************************************************************************
**
**      FUNCTION :
**         corresponding to D.5/Q.714/sheet-1 on receiving the event
**         'MSG received for unavailable subsystem'
****************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
***************************************************************************/

void
sccp_msg_unavail_system
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	struct msg_info_t * p_info;
#endif
{
/* SPR # 9502 Fix Start */
    msg_info_t info;
    U8bit scmg_buf[MAX_SCMG_MSG_LEN];
/* SPR # 9502 Fix End */
	sp_entry_t * p_src_sp;

	if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
		return;

	if (SS7_NULL == (p_src_sp = sccp_db_find_sp (p_info->nw_id, p_info->opc)))
		return;

	MG_TRC (("SCCP::SCMG: sending SSP to pc %u on nw %d\n",
	         p_info->opc, p_info->nw_id));

/* SPR # 9502 Fix Start */

#if 0
	/* This code needs to be commented out 'coz this function would always
	** send local_pc in the calling party address field of SSA or SSP */

  	/* SPR 1684: Send OPC information to function */
	sccp_send_ssa_or_ssp (p_info->p_ss, p_src_sp, BCST_SSP, p_info);
#endif

    scmg_buf[0] = SCMG_SSP_MSG;
    scmg_buf[1] = p_info->cd_addr.ssn;
    PUT_PC((&scmg_buf[2]), p_info->cd_addr.pc);
    scmg_buf[2+PC_SIZE] = 0; /* mult ind */

    info.flag = 0;
    info.nw_id = p_info->nw_id;
    info.msg_type = UDT_MSG_TYPE;
    info.proto_class = 0;
    info.p_api = p_info->p_api;
    info.dpc = p_info->dpc ;

    /* called addr */
    info.cd_addr.pc_ind = SS7_TRUE;
    info.cd_addr.ssn_ind = SS7_TRUE;
    info.cd_addr.gti = 0;
    info.cd_addr.rout_ind = ROUTE_ON_SSN;
    info.cd_addr.pc = p_info->opc;
    info.cd_addr.ssn = SCMG_SSN;

    /* calling addr */
    info.cg_addr.pc_ind = SS7_TRUE;
    info.cg_addr.ssn_ind = SS7_TRUE;
    info.cg_addr.gti = 0;
    info.cg_addr.rout_ind = ROUTE_ON_SSN;
    info.cg_addr.pc = p_info->dpc;
    info.cg_addr.ssn = SCMG_SSN;

    /* data */
    info.data.len = SCMG_MSG_LEN;
    info.data.p = scmg_buf;

    info.p_sp = p_info->p_sp;
    info.p_ss = p_info->p_ss;

    sccp_m3_transfer_request (&info);
/* SPR # 9502 Fix End */
}

/***************************************************************************
**
**      FUNCTION :
**         handles the n-state request API
****************************************************************************
**
**      DESCRIPTION :
**         calls appropriate function for user coming in service or
**         going out of service
**
**      NOTE :
**
***************************************************************************/

void 
sccp_n_state_req 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	scmg_info_t info, * p_info = &info;

	SC_A_TRC (("SCCP::SCMG: recvd N-STATE req\n"));

	sccp_parse_n_state_req_api (p_api, p_info);

	SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	if ((SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->pc))) ||
	    (SS7_NULL == (p_info->p_ss = sccp_db_find_ss(p_info->p_sp, p_info->ssn))))
	{
		MG_TRC (("SCCP::SCMG: unequipped user SSN %d nw %d pc %d sends API"
		         " ignored\n", p_info->ssn, p_info->nw_id, p_info->pc));
		SC_P_ERR (ESCCP_UNEQUIPPED_USER);
		return;
	}

	/** SPR # 2691 Fix Start **/
	if ( ! p_info->p_ss->registered )
	{
		MG_TRC (("SCCP::SCMG: unequipped user SSN %d nw %d pc %d sends API"
		         " ignored\n", p_info->ssn, p_info->nw_id, p_info->pc));
		SC_P_ERR (ESCCP_UNEQUIPPED_USER);
		return;
	}
	/** SPR # 2691 Fix Start **/

	if (SCCP_USER_IN_SERVICE == p_info->status)
	{
		sccp_handle_n_state_req_uis (p_info);
	}
	else
	{
		sccp_handle_n_state_req_uos (p_info);
	}
#ifdef DISTRIBUTED_SCCP
      sccp_send_ss_status_to_mate(p_info->p_ss);
#endif


}



/***************************************************************************
**
**      FUNCTION :
**         handles the n-coord request API
****************************************************************************
**
**      DESCRIPTION :
**         calls appropriate function for user wanting to go in service or
**         going out of service
**
**      NOTE :
**
***************************************************************************/
#ifdef BACK_UP_SSN
void 
sccp_n_coord_request 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	scmg_info_t info, * p_info = &info;

	SC_A_TRC (("SCCP::SCMG: recvd N-COORD req\n"));

	sccp_parse_n_coord_req_api (p_api, p_info);

	SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	if ((SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->pc))) || (SS7_NULL == (p_info->p_ss = sccp_db_find_ss(p_info->p_sp, p_info->ssn))))
	{
		MG_TRC (("SCCP::SCMG: unequipped user SSN %d nw %d pc %d sends API" " ignored\n", p_info->ssn, p_info->nw_id, p_info->pc));
		SC_P_ERR (ESCCP_UNEQUIPPED_USER);
		return;
	}

	if ( ! p_info->p_ss->registered )
	{
		MG_TRC (("SCCP::SCMG: unequipped user SSN %d nw %d pc %d sends API" " ignored\n", p_info->ssn, p_info->nw_id, p_info->pc));
		SC_P_ERR (ESCCP_UNEQUIPPED_USER);
		return;
	}
	send_sor_message(p_info);
}



/***************************************************************************
**
**      FUNCTION :
**         handles the n-coord response API
****************************************************************************
**
**      DESCRIPTION :
**         calls appropriate function for user wanting to go in service or
**         going out of service
**
**      NOTE :
**
***************************************************************************/

void 
sccp_n_coord_response 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	scmg_info_t info, * p_info = &info;

	SC_A_TRC (("SCCP::SCMG: recvd N-COORD response\n"));

	sccp_parse_n_coord_response_api (p_api, p_info);

	SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	if ((SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->pc))) || (SS7_NULL == (p_info->p_ss = sccp_db_find_ss(p_info->p_sp, p_info->ssn))))
	{
		MG_TRC (("SCCP::SCMG: unequipped user SSN %d nw %d pc %d sends API" " ignored\n", p_info->ssn, p_info->nw_id, p_info->pc));
		SC_P_ERR (ESCCP_UNEQUIPPED_USER);
		return;
	}
#if 0
	if ( ! p_info->p_ss->registered )
	{
		MG_TRC (("SCCP::SCMG: unequipped user SSN %d nw %d pc %d sends API" " ignored\n", p_info->ssn, p_info->nw_id, p_info->pc));
		SC_P_ERR (ESCCP_UNEQUIPPED_USER);
		return;
	}
#endif
	send_sog_message(p_info);
}
#endif

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/D.5/sheet-1
****************************************************************************
**
**      DESCRIPTION :
**          handles user going out of service
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_n_state_req_uos 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	MG_TRC (("SCCP::SCMG: UOS request for SSN %d nw %d pc %u\n",
	         p_info->p_ss->ssn, GET_SP_NW_ID(p_info->p_sp),
	         GET_SP_PC(p_info->p_sp)));

	if ( ! IS_SS_ALLOWED(p_info->p_ss))
	{
		MG_TRC (("SCCP::SCMG: subsystem already out of service\n"));
		return;
	}

	/* Everything related to SOG/SOR is deleted */

	MARK_SS_PROHIBITED(p_info->p_ss);
	SCCP_SEND_SS_ENTRY_UPDATE (p_info->p_ss);
	MG_TRC (("SCCP::SCMG: subsystem goes out of service\n"));

	sccp_inform_trans_func (p_info->p_sp, p_info->p_ss);
	sccp_local_bcast (SS7_NULL, p_info->p_ss, LBCS_UOS);
	p_info->p_msg_info = SS7_NULL;
	sccp_broadcast (p_info, BCST_SSP);
}


/***************************************************************************
**
**      FUNCTION :
**          corresponds to Q.714/D.6/sheet-1
****************************************************************************
**
**      DESCRIPTION :
**          handles user coming into service
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_n_state_req_uis 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
#ifdef SCCP_REDN_ENABLED
          extern U8bit sccp_state;
#endif

	MG_TRC (("SCCP::SCMG: UIS request for SSN %d nw %d pc %u\n",
	         p_info->p_ss->ssn, GET_SP_NW_ID(p_info->p_sp),
	         GET_SP_PC(p_info->p_sp)));

	if ( ! IS_SS_PROHIBITED(p_info->p_ss))
	{
		MG_TRC (("SCCP::SCMG: subsystem already in service\n"));
		return;
	}

	MARK_SS_ALLOWED(p_info->p_ss);
	SCCP_SEND_SS_ENTRY_UPDATE (p_info->p_ss);
	MG_TRC (("SCCP::SCMG: subsystem comes into service\n"));

	p_info->p_msg_info = SS7_NULL;

	sccp_inform_trans_func (p_info->p_sp, p_info->p_ss);
	sccp_broadcast (p_info, BCST_SSA);
	sccp_local_bcast (SS7_NULL, p_info->p_ss, LBCS_UIS);
}


/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.715/D.5/sheet-1
****************************************************************************
**
**      DESCRIPTION :
**         handles a subsystem prohibited message. sends local broadcast
**         to css and broadcasts SSP to csp
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_ssp 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	MG_TRC (("SCCP::SCMG: SSP for SSN %d pc %u nw_id %d\n",
	         p_info->ssn, p_info->pc, p_info->p_sp->nw_id));

	if (SCMG_SSN == p_info->ssn)
		return;

	if (IS_SS_ALLOWED(p_info->p_ss))
	{
		p_info->p_ss->prev_t_stat_info_timer_val =
			sc_tim.t_stat_info_start_timer_val;

		/** SPR # 2662 Fix Start **/
		/* This check must not be done */
		/* if (GET_NUM_CSS(p_info->p_ss) > 0) */
		/** SPR # 2662 Fix End **/

			sccp_start_sst (p_info->p_ss);
	}
	else
	{
		MG_TRC (("SCCP::SCMG: subsystem already out of service\n"));
		/** SPR # 2638 Fix START **/
		/** SPR # 4047 Fix Start - SPR # 2638 applies to ITU also **/
#if 0
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
    	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI)
			sccp_broadcast (p_info, BCST_SSP);
#endif
#endif
		/** SPR # 4047 Fix End **/
		/** SPR # 2638 Fix END **/
		return;
	}

	MARK_SS_PROHIBITED(p_info->p_ss);
	sccp_inform_trans_func (p_info->p_sp, p_info->p_ss);

	SCCP_SEND_SS_ENTRY_UPDATE (p_info->p_ss);
	MG_TRC (("SCCP::SCMG: subsystem goes out of service\n"));
	sccp_local_bcast (SS7_NULL, p_info->p_ss, LBCS_UOS);
	sccp_broadcast (p_info, BCST_SSP);
#ifdef DISTRIBUTED_SCCP
		sccp_send_ss_status_to_mate(p_info->p_ss);
#endif
}

/***************************************************************************
**
**      FUNCTION :
**          corresponds to Q.714/D.6/sheet-1
****************************************************************************
**
**      DESCRIPTION :
**          handles subsystem allowed message. changes state and
**          sends local broadcast to css and broadcast SSA to csp
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_ssa 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	MG_TRC (("SCCP::SCMG: SSA for SSN %d pc %u nw_id %d\n",
	         p_info->ssn, p_info->pc, p_info->p_sp->nw_id));

	if ( ! IS_SP_ALLOWED(p_info->p_sp))
	{
		return;
	}

	if (IS_SCCP_ALLOWED(p_info->p_sp))
	{
		if (SCMG_SSN == p_info->ssn)
		{
			MG_TRC (("SCCP::SCMG: SCCP already up\n"));
			return;
		}

		if ( ! IS_SS_PROHIBITED(p_info->p_ss))
		{
			MG_TRC (("SCCP::SCMG: subsystem already in service\n"));
			return;
		}

		sccp_stop_sst (p_info->p_ss);
		MARK_SS_ALLOWED(p_info->p_ss);
		/* SPR GR: inform translation function */
		sccp_inform_trans_func (p_info->p_sp, p_info->p_ss);
		SCCP_SEND_SS_ENTRY_UPDATE (p_info->p_ss);
		MG_TRC (("SCCP::SCMG: subsystem comes into service\n"));
		sccp_broadcast (p_info, BCST_SSA);
		sccp_local_bcast (SS7_NULL, p_info->p_ss, LBCS_UIS);
#ifdef DISTRIBUTED_SCCP
		sccp_send_ss_status_to_mate(p_info->p_ss);
		/* SPR 11098 - Fix Start */
		p_info->p_ss->sst_instance_id = DSCCP_INVALID_INSTANCE_ID;
		/* SPR 11098 - Fix End  */
#endif
	}
	else
	{
		MARK_SS_ALLOWED (&p_info->p_sp->scmg_ss);
#ifdef DISTRIBUTED_SCCP
		dsccp_send_scmg_status_to_mate(p_info->p_sp);
#endif

		sccp_scmg_spac_bcast (p_info->p_sp, SS7_FALSE);

		MG_TRC (("SCCP::SCMG: subsystem comes into service\n"));
		sccp_stop_sst (&p_info->p_sp->scmg_ss);
	}
}
#ifdef DISTRIBUTED_SCCP
void sccp_send_ss_status_to_mate
#ifdef ANSI_PROTO
	(ss_entry_t *p_ss)
#else
	(p_ss)
	ss_entry_t *p_ss;
#endif
{
	U8bit * p_api;
	U16bit api_len;
	return_t ret_val;
	error_t ecode;


      api_len = DSCCP_SS_STATUS_LEN ;
	p_api= (U8bit *)sccp_malloc(api_len);
	if(p_api == SS7_NULL)
		return;

	sccp_build_ss_status_message(p_api,p_ss,api_len);
	ret_val = dsccp_broadcast_to_mates(p_api,api_len, &ecode);	
	return ;
}

#endif


#ifdef BACK_UP_SSN
/***************************************************************************
**
**      FUNCTION :
**         send_sor_message
****************************************************************************
**
**      DESCRIPTION :
**         This function sends the SOR message to the peer
**
**      NOTE :
**
***************************************************************************/

void send_sor_message
#ifdef ANSI_PROTO
	(scmg_info_t *p_info)
#else
	(p_info);
	scmg_info_t *p_info;
#endif
{
	sp_entry_t *p_sp;
        msg_info_t info;
        U8bit scmg_buf[MAX_SCMG_MSG_LEN];
        U8bit tmp_buf[1];
	pc_t pc;
        extern sp_entry_t sccp_local_sp;

        p_sp = GET_SP_OF_SS(p_info->p_ss);
	scmg_buf[0] = SCMG_SOR_MSG;
        scmg_buf[1] = p_info->ssn;
        PUT_PC((&scmg_buf[2]), p_info->pc);
        scmg_buf[2+PC_SIZE] = p_info->ss_mult_ind; /* multi ind */
	MG_TRC (("SCCP::SCMG : sending SOR for SSN %d pc %u nw_id %d\n", p_info->ssn, p_sp->pc, p_sp->nw_id));

	info.flag = 0;
        info.nw_id = p_sp->nw_id;
        info.msg_type = UDT_MSG_TYPE;
        info.proto_class = 0;
	/* called addr */
        info.cd_addr.pc_ind = SS7_TRUE;
        info.cd_addr.ssn_ind = SS7_TRUE;
        info.cd_addr.gti = 0;
        info.cd_addr.rout_ind = ROUTE_ON_SSN;
	
	MG_TRC (("SCCP::SCMG : finding back up point code"));
        if (sccp_db_search_back_up_ss(p_info->ssn, &pc) == SS7_FAILURE)
		return;
	MG_TRC (("SCCP::SCMG : found backup SSN for SSN %d  pc %u \n", p_info->ssn, pc));
        info.cd_addr.pc = pc;
        info.cd_addr.ssn = SCMG_SSN;

        /* calling addr */
        info.cg_addr.pc_ind = SS7_TRUE;
        info.cg_addr.ssn_ind = SS7_TRUE;
        info.cg_addr.gti = 0;
        info.cg_addr.rout_ind = ROUTE_ON_SSN;
        info.cg_addr.pc = sccp_local_sp.pc;
        info.cg_addr.ssn = SCMG_SSN;

        /* data */
        info.data.len = SCMG_MSG_LEN;
        info.data.p = scmg_buf;
	info.p_sp = p_sp;
        tmp_buf[0] = SCCP_N_UNITDATA_REQUEST;
        info.p_api = tmp_buf;
	if(p_info->p_ss->t_coord_timer_running == SS7_FALSE)
		start_t_coord_timer(p_info->p_ss);
	else
	{
		MG_TRC (("COORD CHANGE ALREADY IN PROGRESS\n"));
		return;
	}
		
	MG_TRC (("SCCP::SCMG : Sending N UNITDATA REQUEST\n"));
	sccp_m3_transfer_request (&info);
}

/***************************************************************************
**
**      FUNCTION :
**         send_sog_message
****************************************************************************
**
**      DESCRIPTION :
**         This function sends the SOG message to the peer
**
**      NOTE :
**
***************************************************************************/
void send_sog_message
#ifdef ANSI_PROTO
	(scmg_info_t *p_info)
#else
	(p_info)
	scmg_info_t *p_info;
#endif
{
        sp_entry_t *p_sp;
        msg_info_t info;
        U8bit scmg_buf[MAX_SCMG_MSG_LEN];
        U8bit tmp_buf[1];
        extern sp_entry_t sccp_local_sp;

        p_sp = GET_SP_OF_SS(p_info->p_ss);
	scmg_buf[0] = SCMG_SOG_MSG;
        scmg_buf[1] = p_info->ssn;
        PUT_PC((&scmg_buf[2]), p_info->pc);
        scmg_buf[2+PC_SIZE] = p_info->ss_mult_ind; /* multi ind */
	MG_TRC (("SCCP::SCMG : sending SOG for SSN %d pc %u nw_id %d\n", p_info->ssn, p_sp->pc, p_sp->nw_id));

	info.flag = 0;
        info.nw_id = p_sp->nw_id;
        info.msg_type = UDT_MSG_TYPE;
        info.proto_class = 0;

        /* called addr */
        info.cd_addr.pc_ind = SS7_TRUE;
        info.cd_addr.ssn_ind = SS7_TRUE;
        info.cd_addr.gti = 0;
        info.cd_addr.rout_ind = ROUTE_ON_SSN;
        info.cd_addr.pc = p_info->pc;
        info.cd_addr.ssn = SCMG_SSN;

	/* calling addr */
        info.cg_addr.pc_ind = SS7_TRUE;
        info.cg_addr.ssn_ind = SS7_TRUE;
        info.cg_addr.gti = 0;
        info.cg_addr.rout_ind = ROUTE_ON_SSN;
        info.cg_addr.pc = sccp_local_sp.pc;
        info.cg_addr.ssn = SCMG_SSN;

        /* data */
        info.data.len = SCMG_MSG_LEN;
        info.data.p = scmg_buf;

        info.p_sp = p_sp;
        tmp_buf[0] = SCCP_N_UNITDATA_REQUEST;
        info.p_api = tmp_buf;
	sccp_m3_transfer_request (&info);
}

/***************************************************************************
**
**      FUNCTION :
**         start_t_coord_timer
****************************************************************************
**
**      DESCRIPTION :
**         This function starts t coord timer. This timer is started when
**		a SOR message is sent. 
**
**      NOTE :
**
***************************************************************************/

void start_t_coord_timer
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
	  MG_TRC (("SCCP::SCMG: starting TCoord Timer for SSN %d  pc %u nw %d\n " , GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
	if(p_ss->t_coord_timer_running == SS7_FALSE)
        {
                *p_tmr_buf = T_COORD_TIMER_ID;
                p_tmr_buf += SCCP_TIMER_ID_LEN;
                *p_tmr_buf++ = p_sp->nw_id;
                PUT_PC(p_tmr_buf, p_sp->pc);
                p_tmr_buf += PC_SIZE;
                *p_tmr_buf = p_ss->ssn;
                if (SS7_SUCCESS == sccp_start_timer(T_COORD_MAX_TIMER_VAL, sst_tmr_buf, SCMG_TIMER_BUF_LEN, &p_ss->t_coord_timer_id))
                {
                        p_ss->t_coord_timer_running = SS7_TRUE;
                        p_ss->waiting_for_grant = SS7_TRUE;
                }
	}
        else
        {
                MG_TRC(("SCCP::SCMG:Coord state Change already in progress\n"));
        }
}


/***************************************************************************
**
**      FUNCTION :
**         sccp_t_coord_timeout
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/
void sccp_t_coord_timeout
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
        MG_TRC (("SCCP::SCMG: T Coord Timer expires for SSN %d pc %u nw %d\n", p_info->ssn, p_info->pc, p_info->nw_id));
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,p_info->pc)))
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
/* SPR # 9221 Fix Start*/
				SC_STAT_Q752_TS_T_COORD_EXPIRED;
				SC_STAT_Q752_INR_T_COORD_EXPIRED;
/* SPR # 9221 Fix End*/
                return;
        }
}
#endif
