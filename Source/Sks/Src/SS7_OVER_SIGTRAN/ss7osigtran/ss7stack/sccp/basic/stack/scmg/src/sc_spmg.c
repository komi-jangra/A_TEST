/***************************************************************************
**
**  FILE NAME:
**      sc_spmg.c
**
****************************************************************************
**
**  FUNCTION:
**     Contains functions for signaling point management
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  08Apr2004  Hitesh Sharma          SPR# 13344
**  27Feb2004 Hitesh Sharma           SPR# 13263
**  21Nov2003 knaveen                 SPR# 13075
**  10Nov2003  Hitesh Sharma          SPR# 13073
**  25July2003 Sunil Dahiya           SPR# 12290
**  02July2003 Hitesh Sharma          Fixed SPR # 12135  CSR No : 1 - 652585
**  12Feb2003  Ashish Sawalkar         Fixed SPR # 11321
**  10Jul2002 Suyash Tripathi         SPR # 9201/9583
**  24Jun2002 Sachin Bhatia           Fixed SPR # 9064
**  20Jun2002 Suyash Tripathi         SPR # 9022
**  20May2002 Salil K Agrawal         Fixed SPR # 8744
**  24Oct2001 Prateek Bidwalkar       Fixed SPR # 6750
**  25Feb2000 Ramu Kandula            Fixed SPR # 2756
**  25Feb2000 Ramu Kandula            Fixed SPR # 2754
**  25Feb2000 Ramu Kandula            Fixed SPR # 2752
**  25Feb2000 Ramu Kandula            Fixed SPR # 2751
**  24Feb2000 Ramu Kandula            Fixed SPR # 2965
**  18Jun'99 Sudipta Pattar	      GR modifications added
**  08Aug'98 Anil K.				  Connectionless ANSI added
**  4May98   Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"
#include <sl.h>  /* Added  as on dated 16-02-17 Mantis Id 32333 */

#include "sc_bcast.h"
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */
#define MARK_SS_PROHIBITED_ON_RESUME
static void sccp_handle_upu 
	_ARGS_ ((scmg_info_t * p_info));

static void sccp_initiate_node_cong_proc
	_ARGS_ ((sp_entry_t * p_sp));

extern U8bit sccp_state;
extern sl_module_t ss7_sccp_mid;  /* Added  as on dated 16-02-17 Mantis Id 32333 */

/***************************************************************************
**
**      FUNCTION :
**         corresponding to Q.714/D.2/Sheet-1 & 2 ongetting MTP3 pause ind
****************************************************************************
**
**      DESCRIPTION :
**         makes the signaling-point & SCCP prohibited 
**         and makes all associated subsystems prohibited
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_pause_ind 
#ifdef ANSI_PROTO
	(U8bit 	* p_api)
#else
	(p_api)
	U8bit  * p_api ;
#endif
{
	U32bit 		i, num_ss;
	scmg_info_t 	info, * p_info = &info;
	ss_entry_t 	* p_ss;
	error_t 	ecode;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	SC_A_TRC (("SCCP::SCMG: recvd  pause ind\n"));

    /* spr # 11321 start fix */
    if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
    {
        SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));

        return;
    }
    /* spr # 11321 end fix */

	if (SS7_FAILURE == sccp_parse_m3_pause_ind_api (p_api, p_info, &ecode))
	{
		SC_A_TRC (("SCCP::SCMG : API PARSE ERR\n"));
		SC_STAT_API_INR_ERR_API_LL();
		SC_A_ERR (ecode);
	/* Fix for SPR No :12135, CSR No : 1 - 652585  Starts */
		 return; 
	/* Fix for SPR No :12135, CSR No : 1 - 652585  Ends */

	}

	SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	/* Search database for the signaling point */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, 
					p_info->pc)))
	{
		SC_A_TRC (("SCCP::SCMG: pc %u nw %d unknown to SCCP\n", 
				p_info->pc, p_info->nw_id));
		SC_STAT_API_INR_ERR_API_LL ();
		SC_A_ERR (ESS7_INVALID_API_ELEMENT);
		return;	
	}

	if (IS_SP_PROHIBITED(p_info->p_sp))
	{
		MG_TRC (("SCCP::SCMG: pc %u nw_id %d: already down\n",
		         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));
		return;
	}

	MARK_SP_PROHIBITED (p_info->p_sp);
	SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
	sccp_send_sp_status_to_mate(p_info->p_sp);
#endif
	MG_TRC (("SCCP::SCMG: pc %u nw_id %d: goes down\n",
	         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

/* SPR 10846 - Fix Start */
#if 0
/* This portion has been commented as it does not send any useful or specific information and proves to be just another copy of pc-state indication */
	/** SPR # 2752 Fix Start **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		sccp_local_bcast (p_info->p_sp, SS7_NULL, LBCS_PAUSE);
	}
#endif
	/** SPR # 2752 Fix End **/
#endif  /* end of if 0 */
/* SPR 10846 - Fix Start */

/* SPR 9022 - Fix Start */
/* Raise an Event alarm when a pause ind is received */
	SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SP, SP_INACCESSIBLE, p_info->p_sp,
				SS7_NULL, SS7_NULL);
/* SPR 9022 - Fix End   */

	if (IS_SCCP_PROHIBITED(p_info->p_sp))
	{
		/* For SSN = "SCMG" */
		sccp_stop_sst (&p_info->p_sp->scmg_ss);
		/** SPR # 2754 Fix Start **/
		return;
		/** SPR # 2754 Fix End **/
	}
	else
	{
		MARK_SCCP_PROHIBITED (p_info->p_sp);
		SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
		sccp_send_sp_status_to_mate(p_info->p_sp);
#endif
		MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: goes down\n",
		         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

		sccp_local_bcast (p_info->p_sp, SS7_NULL, LBCS_SCCP_INACCESSIBLE);
		sccp_inform_trans_func(p_info->p_sp, SS7_NULL);
	}
	
	for (i=0, num_ss = GET_NUM_SS_IN_SP(p_info->p_sp),
	     p_ss = GET_SS_LIST_IN_SP (p_info->p_sp);
	     i < num_ss; i++, p_ss = GET_NEXT_SS(p_ss))
	{
		if (IS_SS_PROHIBITED(p_ss))
		{
			MG_TRC (("SCCP::SCMG: SSN %d on pc %u nw %d already down\n",
			          GET_SS_SSN(p_ss), GET_SP_PC(p_info->p_sp),
			          GET_SP_NW_ID(p_info->p_sp)));

			sccp_stop_sst(p_ss);
		}
		else
		{
			MARK_SS_PROHIBITED(p_ss);
			SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
			MG_TRC (("SCCP::SCMG: SSN %d on pc %u nw %d goes down\n",
			          GET_SS_SSN(p_ss), GET_SP_PC(p_info->p_sp),
			          GET_SP_NW_ID(p_info->p_sp)));

			sccp_local_bcast (SS7_NULL, p_ss, LBCS_UOS);
			sccp_inform_trans_func (p_info->p_sp, p_ss);
		}

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
		/* Send SBR */
		if ((COMPARE_ANSI) || (COMPARE_BCGR))
		{
			;
		}
#endif
	}

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	/* Request traffic mix */
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		;
	}
#endif

}
/* Added start as on dated 16-02-17 Mantis Id 32333*/
/***************************************************************************
**
**      FUNCTION :
**         corresponding to Q.714/D.3/Sheet-1 & 2 on getting MTP3 resume ind Check
****************************************************************************
**
**      DESCRIPTION :
**         Makes SP and SCCP as allowed. restarts all subsystems
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_resume_ind_check 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	scmg_info_t info, * p_info = &info;
	error_t ecode;
	U8bit num_ss_sp = 0;
	ss_entry_t * p_ss;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	SC_A_TRC (("SCCP :: SCMG : recvd  resume ind Check when Stanby to Active\n"));

    /* spr # 11321 start fix */
    if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
    {
        SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));

        return;
    }
    /* spr # 11321 end fix */

	if (SS7_FAILURE == sccp_parse_m3_resume_ind_api (p_api, p_info, &ecode))
	{
		SC_A_TRC (("SCCP::SCMG: API PARSE ERR\n"));
		SC_STAT_API_INR_ERR_API_LL();
		SC_A_ERR (ecode);
	/* Fix for SPR No :12135, CSR No : 1 - 652585  Starts */
                 return;
	/* Fix for SPR No :12135, CSR No : 1 - 652585  Ends */
	}

	SC_A_TRC (("SCCP::SCMG: parse sccp_m3_resume_ind_check  SUCCESS\n"));

	/* Search database for the signaling point */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, p_info->pc)))
	{
		SC_A_TRC (("SCCP::SCMG : sccp_m3_resume_ind_check pc %u nw %d unknown to SCCP\n", 
			p_info->pc, p_info->nw_id));
		SC_STAT_API_INR_ERR_API_LL ();
		SC_A_ERR (ESS7_INVALID_API_ELEMENT);
		return;
	}
	if (IS_SCCP_ALLOWED(p_info->p_sp))
  {
		num_ss_sp = GET_NUM_SS_IN_SP(p_info->p_sp);
		p_ss = GET_SS_LIST_IN_SP(p_info->p_sp);	
		SC_A_TRC (("SCCP::SCMG: parse sccp_m3_resume_ind_check num_ss_sp %d p_ss_allowed%d\n",num_ss_sp,p_ss->allowed));
		if (IS_SS_PROHIBITED(p_ss))
		{
				SC_A_TRC (("SCCP::SCMG: Calling sccp_m3_resume_ind \n"));
				LOG_PRINT(INFO,"[M3UA->SCCP]send_from_m3ua SS7_CARD_STATE_ACTIVE same card process\n");
        sl_mq_send (ss7_sccp_mid, 0, p_api); /* Amaresh */				
		}
		else
		{
			SC_A_TRC (("SCCP::SCMG: parse sccp_m3_resume_ind_check  SST Send/Receive done\n"));
		}
	}
	else
	{
				SC_A_TRC (("SCCP::SCMG: Calling sccp_m3_resume_ind !IS_SCCP_ALLOWED\n"));
				LOG_PRINT(INFO,"[M3UA->SCCP]send_from_m3ua SS7_CARD_STATE_ACTIVE same card process\n");
        sl_mq_send (ss7_sccp_mid, 0, p_api); /* Amaresh */				
	}	
}

/* Added stop as on dated 16-02-17 Mantis Id 32333*/

/***************************************************************************
**
**      FUNCTION :
**         corresponding to Q.714/D.3/Sheet-1 & 2 on getting MTP3 resume ind
****************************************************************************
**
**      DESCRIPTION :
**         Makes SP and SCCP as allowed. restarts all subsystems
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_resume_ind 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	scmg_info_t info, * p_info = &info;
	error_t ecode;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	SC_A_TRC (("SCCP :: SCMG : recvd  resume ind\n"));

    /* spr # 11321 start fix */
    if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
    {
        SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));

        return;
    }
    /* spr # 11321 end fix */

	if (SS7_FAILURE == sccp_parse_m3_resume_ind_api (p_api, p_info, &ecode))
	{
		SC_A_TRC (("SCCP::SCMG: API PARSE ERR\n"));
		SC_STAT_API_INR_ERR_API_LL();
		SC_A_ERR (ecode);
	/* Fix for SPR No :12135, CSR No : 1 - 652585  Starts */
                 return;
	/* Fix for SPR No :12135, CSR No : 1 - 652585  Ends */
	}

	SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	/* Search database for the signaling point */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, p_info->pc)))
	{
		SC_A_TRC (("SCCP::SCMG : pc %u nw %d unknown to SCCP\n", 
			p_info->pc, p_info->nw_id));
		SC_STAT_API_INR_ERR_API_LL ();
		SC_A_ERR (ESS7_INVALID_API_ELEMENT);
		return;
	}

	MARK_SP_ALLOWED(p_info->p_sp);
	MG_TRC (("SCCP::SCMG: pc %u nw_id %d: comes up\n",
	         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

	MARK_SCCP_ALLOWED(p_info->p_sp);
	MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: comes up\n",
	         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

	SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
	sccp_send_sp_status_to_mate(p_info->p_sp);
#endif

	/* for SSN = "SCMG" */
	sccp_stop_sst(&p_info->p_sp->scmg_ss);

	/* Clear SP congestion */
	p_info->p_sp->cls = 0;
	 /* SPR 13344 -Fix Start */
	p_info->p_sp->rlm = 0; 
	p_info->p_sp->rslm = 0;
	 /* SPR 13344 -Fix Stop */
	if (IS_T_A_RUNNING(p_info->p_sp))
	{
		sccp_stop_timer(&p_info->p_sp->t_a_timer_id);
		/* SPR 9583 - Fix Start */
		p_info->p_sp->t_a_running = SS7_FALSE;
		/* SPR 9583 - Fix End   */
	}

	if (IS_T_D_RUNNING(p_info->p_sp))
	{
		sccp_stop_timer(&p_info->p_sp->t_d_timer_id);
		/* SPR 9583 - Fix Start */
		p_info->p_sp->t_d_running = SS7_FALSE;
		/* SPR 9583 - Fix End   */
	}

	if (IS_T_CON_RUNNING(p_info->p_sp))
	{
		sccp_stop_timer(&p_info->p_sp->t_con_timer_id);
		/* SPR 9583 - Fix Start */
		p_info->p_sp->t_con_running = SS7_FALSE;
		/* SPR 9583 - Fix End   */
	}
	p_info->p_sp->active = SS7_FALSE;

 	sccp_scmg_spac_bcast (p_info->p_sp, SS7_TRUE);  /* SS7_TRUE indicates
	                                               'RESUME received' */

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	/* Start SRT */
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
	}
#endif
}

/***************************************************************************
**
**      FUNCTION :
**          broadcast subsystem allowed information to conc subsystem and sp
****************************************************************************
**
**      DESCRIPTION :
**         for all subsystems at this signaling point broadcast allowed info
**         for this sp a local broadcast of SCCP accessible and resume
**
**      NOTE :
**
***************************************************************************/

void 
sccp_scmg_spac_bcast 
#ifdef ANSI_PROTO
	(sp_entry_t 	* p_sp, 
	 Boolean 	resume_recvd)
#else
	(p_sp, resume_recvd)
	sp_entry_t     * p_sp ;
	Boolean        resume_recvd ;
#endif
{
	U32bit i;
	ss_entry_t * p_ss;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

	sccp_inform_trans_func (p_sp, SS7_NULL);

	for (i=0, p_ss = GET_SS_LIST_IN_SP(p_sp);
	     i < GET_NUM_SS_IN_SP(p_sp); i++, p_ss = GET_NEXT_SS(p_ss))
	{
#ifdef MARK_SS_PROHIBITED_ON_RESUME
		/** SPR # 2756 Fix Start **/
		MARK_SS_PROHIBITED (p_ss);
		SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
        sccp_inform_trans_func (p_sp, p_ss);
		/** SPR # 2756 Fix End **/
		p_ss->prev_t_stat_info_timer_val = sc_tim.t_stat_info_start_timer_val;

		sccp_start_sst (p_ss);
#else
		/** SPR # 2751 Fix Start **/
		/** SST must always be started on Resume in case of BCGR **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_ANSI) || defined (SCCP_CHINESE)
		if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_ANSI) || (COMPARE_CHINESE))
		{
			MARK_SS_ALLOWED (p_ss);
			SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
			MG_TRC (("SCCP::SCMG : SSN %d on pc %u nw %d comes up\n",
		          	GET_SS_SSN(p_ss), GET_SP_PC(p_sp),
		          	GET_SP_NW_ID(p_sp)));
	
			sccp_stop_sst (p_ss);
			sccp_local_bcast (SS7_NULL, p_ss, LBCS_UIS);
        	/* SPR GR - inform translation function for SS */
        	sccp_inform_trans_func (p_sp, p_ss);
		}
#endif
#if defined (SCCP_BCGR)
		if (COMPARE_BCGR)
		{
			MARK_SS_PROHIBITED (p_ss);
			SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
        	sccp_inform_trans_func (p_sp, p_ss);
			p_ss->prev_t_stat_info_timer_val = 
				sc_tim.t_stat_info_start_timer_val;
			sccp_start_sst (p_ss);
		}
#endif
		/** SPR # 2751 Fix End **/
#endif
	}

	sccp_local_bcast (p_sp, SS7_NULL, LBCS_SCCP_ACCESSIBLE);

/* SPR 10846 - Fix Start */
#if 0
/* This portion has been commented as it does not send any useful or specific information and proves to be just another copy of pc-state indication */
	/** SPR # 2752 Fix Start **/
	/** Resume is not broadcast in ANSI and GR **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		if (resume_recvd)
			sccp_local_bcast (p_sp, SS7_NULL, LBCS_RESUME);
	}
#endif
	/** SPR # 2752 Fix End **/
#endif
/* SPR 10846 - Fix End   */

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		;
	}
#endif

/* SPR 9022 - Fix Start */
	if(resume_recvd)
		SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SP, SP_ACCESSIBLE, p_sp, \
					SS7_NULL, SS7_NULL);

/* SPR 9022 - Fix End   */
}

/** SPR 8744 Starts here **/
/***************************************************************************
**
**      FUNCTION : check whether sp is local sp or not.
**         
****************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
***************************************************************************/

extern sp_entry_t sccp_local_sp;
int sccp_is_local_sp(sp_entry_t * p_sp)
{
    if (p_sp->pc == sccp_local_sp.pc)
    {
        return SS7_SUCCESS;
    }
    else
    {
        return SS7_FAILURE;
    }
}
/** SPR 8744 ends here **/

/***************************************************************************
**
**      FUNCTION :
**         corresponding to Q.714/D.4/Sheet-2
****************************************************************************
**
**      DESCRIPTION :
**         for status=congested start congestion control procedures
**         else handle user part unavailable procedures.
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_status_ind 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	scmg_info_t info, * p_info = &info;
	error_t ecode;

	SC_A_TRC (("SCCP::SCMG: recvd  status ind\n"));

    /* spr # 11321 start fix */
    if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
    {
        SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));

        return;
    }
    /* spr # 11321 end fix */

	if (SS7_FAILURE == sccp_parse_m3_status_ind_api (p_api, p_info, &ecode))
	{
		SC_A_TRC (("SCCP::SCMG : API PARSE ERR\n"));
		SC_STAT_API_INR_ERR_API_LL ();
		SC_A_ERR (ecode);
        /* Fix for SPR No :12135, CSR No : 1 - 652585  Starts */
                 return;
        /* Fix for SPR No :12135, CSR No : 1 - 652585  Ends */
	}

	SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	/* Search database for the signaling point */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, 
				p_info->pc)))
	{
		SC_A_TRC (("SCCP::SCMG: pc %u nw %d unknown to SCCP\n", 
			p_info->pc, p_info->nw_id));
		SC_STAT_API_INR_ERR_API_LL ();
		SC_A_ERR (ESS7_INVALID_API_ELEMENT);
		return;
	}


	switch (p_info->cause)
	{
		case MTP3_CAUSE_SIG_NETWORK_CONGESTION:

			 /* SPR 13344 - Fix Start */
			p_info->p_sp->cong_cause = MTP3_CAUSE_SIG_NETWORK_CONGESTION;
#if defined (MTP3_NATIONAL_VARIANT)
	        if(p_info->cong_level == 0)
                {
                        p_info->p_sp->rlm = 0;
                        p_info->p_sp->rslm = 0;
                }

		if(p_info->cong_level == 1)
		{
			p_info->p_sp->rlm = 2;
			p_info->p_sp->rslm = 0;
		}
                if(p_info->cong_level == 2)
                {
                        p_info->p_sp->rlm = 5;
                        p_info->p_sp->rslm = 0;
                }
                if(p_info->cong_level == 3)
                {
                        p_info->p_sp->rlm = 8;
                        p_info->p_sp->rslm = 0;
                }
#endif
			/** SPR # 2695 Fix Start **/
			/** SPR # 13073  Fix Start **/

#if defined(SCCP_ANSI) || defined(SCCP_BCGR) 
                        if ((COMPARE_ANSI) || (COMPARE_BCGR))

			{
				p_info->p_sp->cls = p_info->cong_level;			
			}
#endif
            /** SPR #2695 Fix End **/
            /** SPR #13073 Fix End **/
	    /* SPR 13344 - Fix End */
            
            /** SPR 8744 Starts here **/
            /* set the value of sccp_cong.level to the p_info->cong_level 
             * if the received sp is local sp */
            if (SS7_SUCCESS == sccp_is_local_sp(p_info->p_sp))
            {
                sccp_cong.level=p_info->cong_level ;
#ifdef DISTRIBUTED_SCCP
                dsccp_send_cong_status_to_mate();
#endif
            }

            /** SPR 8744 Ends here **/
			
            sccp_initiate_node_cong_proc (p_info->p_sp);
			break;

		case MTP3_CAUSE_USER_PART_UNAV_UNKNOWN:
		case MTP3_CAUSE_USER_PART_UNAV_UNEQUIP_REMOTE_USER:
		case MTP3_CAUSE_USER_PART_UNAV_INACCESS_REMOTE_USER:

			sccp_handle_upu (p_info);
			break;

		default:
			break;
	}
}

/***************************************************************************
**
**      FUNCTION :
**          handles UPU according to  Q.714/D.4/Sheet-2
****************************************************************************
**
**      DESCRIPTION :
**          marks SCCP prohibited and broadcasts to all concerned sp & ss
**          makes all subsystems as prohibited and local broadcasts info
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_upu 
#ifdef ANSI_PROTO
	(scmg_info_t * p_info)
#else
	(p_info)
	scmg_info_t * p_info ;
#endif
{
	U32bit i, num_ss;
	ss_entry_t * p_ss;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
	MG_TRC (("SCCP::SCMG: upu recvd\n"));

	switch (p_info->cause)
	{
		case MTP3_CAUSE_USER_PART_UNAV_INACCESS_REMOTE_USER: /* UP Inaccessble */
		case MTP3_CAUSE_USER_PART_UNAV_UNKNOWN: /* Unknown */

			MARK_UPU_RECEIVED(p_info->p_sp);
			SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
			if (IS_SCCP_PROHIBITED(p_info->p_sp)) return;

			MARK_SCCP_PROHIBITED(p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
      		dsccp_send_scmg_status_to_mate(p_info->p_sp);
#endif
			SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
			MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: comes up\n",
			         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

			sccp_local_bcast(p_info->p_sp, SS7_NULL, LBCS_SCCP_INACCESSIBLE);

			p_info->p_sp->scmg_ss.prev_t_stat_info_timer_val =
				sc_tim.t_stat_info_start_timer_val;

			/* For SSN = "SCMG" */
			sccp_start_sst (&p_info->p_sp->scmg_ss);

			break;

		case MTP3_CAUSE_USER_PART_UNAV_UNEQUIP_REMOTE_USER: /* Unequipped */

			MARK_UPU_RECEIVED(p_info->p_sp);
			SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
      		sccp_send_sp_status_to_mate(p_info->p_sp);
#endif
			if (IS_SCCP_PROHIBITED(p_info->p_sp)) return;

			MARK_SCCP_PROHIBITED (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
      		dsccp_send_scmg_status_to_mate(p_info->p_sp);
#endif
			SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
			MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: comes up\n",
		         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

			sccp_local_bcast (p_info->p_sp, SS7_NULL, LBCS_SCCP_INACCESSIBLE);

			break;

		default:
			/* The info elem check ensures we never come here */
			break;
	}

	sccp_inform_trans_func (p_info->p_sp, SS7_NULL);

	/* Select subsystem */
	for (i=0, p_ss = GET_SS_LIST_IN_SP (p_info->p_sp),
	     num_ss = GET_NUM_SS_IN_SP(p_info->p_sp);
	     i < num_ss; i++, p_ss = GET_NEXT_SS(p_ss))
	{
		if (IS_SS_PROHIBITED(p_ss))
		{
			sccp_stop_sst(p_ss);
		}
		else
		{
			MARK_SS_PROHIBITED(p_ss);
			SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
			MG_TRC (("SCCP::SCMG: SSN %d pc %u nw %d goes down\n",
			         GET_SS_SSN(p_ss),
			         GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

			sccp_local_bcast(p_info->p_sp, p_ss, LBCS_UOS);
			sccp_inform_trans_func (p_info->p_sp, p_ss);
		}
	}
}


/***************************************************************************
**
**      FUNCTION :
**         Initiates remote node congestion procedures
****************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
***************************************************************************/

void 
sccp_initiate_node_cong_proc 
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	sp_entry_t * p_sp ;
#endif
{
#define T_A_TMR_BUF_LEN 5
#define T_D_TMR_BUF_LEN 5
/* SPR 9201 - Fix Start */
/* #define M 8
#define N 4 */
#define M 4
#define N 8

/* SPR 13344 - Fix Start */
#if defined (MTP3_NATIONAL_VARIANT) 

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{

                sccp_process_cong_param (p_sp);
                sccp_inform_trans_func(p_sp, SS7_NULL);
                p_sp->active = SS7_TRUE;
                SCCP_SEND_SP_ENTRY_UPDATE (p_sp);
	}
#endif

#else 

/* SPR 9201 - Fix End   */

	U8bit ta_timer_buf[T_A_TMR_BUF_LEN];
	U8bit td_timer_buf[T_D_TMR_BUF_LEN];
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		if (IS_T_A_RUNNING (p_sp))
		{
			MG_TRC (("SCCP::SCMG: ta running for pc %d nw %d. m3 status"
			         " ignored\n", p_sp->pc, p_sp->nw_id));
		return;
		}

		/* Start timer Ta */
		ta_timer_buf[0] = T_A_TIMER_ID;
		ta_timer_buf[1] = p_sp->nw_id;
		PUT_PC((&ta_timer_buf[2]), p_sp->pc);

		if (SS7_SUCCESS == sccp_start_timer (sc_tim.t_a_timer_val, ta_timer_buf,
		                                 T_A_TMR_BUF_LEN, &p_sp->t_a_timer_id))
		{
			MG_TRC (("SCCP::SCMG: attack timer started for pc %u of nw %d\n",
			         p_sp->pc, p_sp->nw_id));
			p_sp->t_a_running = SS7_TRUE;
		}
		else
		{
			p_sp->active = SS7_FALSE;
			return;
		}

		td_timer_buf[0] = T_D_TIMER_ID;
		td_timer_buf[1] = p_sp->nw_id;
		PUT_PC((&td_timer_buf[2]), p_sp->pc);

		/* SPR 9201 - Fix Start */
		if (IS_T_D_RUNNING (p_sp))
		{
			sccp_stop_timer(&p_sp->t_d_timer_id);
			MG_TRC (("SCCP::SCMG: decay timer stopped for pc %u of nw %d\n",
			         p_sp->pc, p_sp->nw_id));
		}
		/* SPR 9201 - Fix End   */

		if (SS7_SUCCESS == sccp_start_timer (sc_tim.t_d_timer_val, td_timer_buf,
		                                 T_D_TMR_BUF_LEN, &p_sp->t_d_timer_id))
		{
			MG_TRC (("SCCP::SCMG: decay timer started for pc %u of nw %d\n",
			         p_sp->pc, p_sp->nw_id));
			p_sp->t_d_running = SS7_TRUE;
		}
		else
		{
			p_sp->active = SS7_FALSE;
			return;
		}

		if (p_sp->rlm == N) return;

		p_sp->rslm ++;

		if (M == p_sp->rslm)
		{
			p_sp->rslm = 0;
			p_sp->rlm ++;
		}

		sccp_process_cong_param (p_sp);
		sccp_inform_trans_func(p_sp, SS7_NULL);
		p_sp->active = SS7_TRUE;
		SCCP_SEND_SP_ENTRY_UPDATE (p_sp);
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/* send SP congested API */
		/** SPR # 2695 Fix Start **/
		sccp_local_bcast (p_sp, SS7_NULL, LBCS_SP_CONG);
		SCCP_SEND_SP_ENTRY_UPDATE (p_sp);
		sccp_inform_trans_func(p_sp, SS7_NULL);
		/** SPR # 2695 Fix End **/
	}
#endif

#endif 
/* SPR 13344 Fix End */
}

/***************************************************************************
**
**      FUNCTION :
**         Handles timeout of attack timer Ta
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_ta_timeout 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	U8bit * p_tmr_buf, nw_id;
	pc_t pc;
	sp_entry_t * p_sp;
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
	p_tmr_buf = p_api + API_HEADER_LEN;

	p_tmr_buf++;  /* timer id */
	nw_id = *p_tmr_buf++;
	pc = GET_PC(p_tmr_buf);

	MG_TRC (("SCCP::SCMG: ta expires for pc %u nw %d\n", pc, nw_id));

	if (SS7_NULL == (p_sp = sccp_db_find_sp (nw_id, pc)))
	{
		MG_TRC (("SCCP::SCMG: cannot locate pc %u for nw %d", pc, nw_id));
		return;
	}

    /* Fix 9064 Start --Sachin Bhatia */
    /* This timer should be marked stopped */
    p_sp->t_a_running = SS7_FALSE;
    /* Fix 9064 Ends --Sachin Bhatia */

	p_sp->active = SS7_TRUE;
	SCCP_SEND_SP_ENTRY_UPDATE (p_sp);
}

/***************************************************************************
**
**      FUNCTION :
**         Handles timeout of decay timer
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_handle_td_timeout 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	U8bit * p_tmr_buf, nw_id;
	pc_t pc;
	sp_entry_t * p_sp;
	U8bit td_timer_buf[T_D_TMR_BUF_LEN];

	p_tmr_buf = p_api + API_HEADER_LEN;

	p_tmr_buf++;  /* timer id */
	nw_id = *p_tmr_buf++;
	pc = GET_PC(p_tmr_buf);

	MG_TRC (("SCCP::SCMG: td expires for pc %u nw %d\n", pc, nw_id));

	if (SS7_NULL == (p_sp = sccp_db_find_sp (nw_id, pc)))
	{
		MG_TRC (("SCCP::SCMG: cannot locate pc"));
		return;
	}

        /* Start SPR 11867 Fix */
        p_sp->t_d_running = SS7_FALSE;
        /* Stop SPR 11867 Fix */
 
	if ((0 == p_sp->rlm) && (1 == p_sp->rslm))
	{
		p_sp->rslm = 0;
        /* Start SPR 13344 Fix */
		p_sp->cong_cause = MTP3_CAUSE_SIG_NETWORK_CONGESTION; 
        /* Stop SPR 13344 Fix */
		sccp_process_cong_param (p_sp);
		p_sp->active = SS7_FALSE;
	}
	else
	{
		if (p_sp->rslm > 0)
		{
			p_sp->rslm--;
			MG_TRC (("SCCP::SCMG: restr sublevel decreases to %d for pc %d"
			         " nw %d when restr level is %d\n",
			         p_sp->rslm, p_sp->pc, p_sp->nw_id, p_sp->rlm));
		}
		else
		{
			p_sp->rlm --;
                        /* Start SPR 12290 Fix */
			p_sp->rslm = M - 1;
                        /* Stop SPR 12290 Fix */
			MG_TRC (("SCCP::SCMG: restr level decreases to %d for pc %u"
                     " nw %d\n", p_sp->rlm, p_sp->pc, p_sp->nw_id));
		}

		/* Restart Td */
		td_timer_buf[0] = T_D_TIMER_ID;
		td_timer_buf[1] = p_sp->nw_id;
		PUT_PC((&td_timer_buf[2]), p_sp->pc);

		if (SS7_SUCCESS == sccp_start_timer (sc_tim.t_d_timer_val, td_timer_buf,
		                                 T_D_TMR_BUF_LEN, &p_sp->t_d_timer_id))
		{
			MG_TRC (("SCCP::SCMG: decay timer started for pc %u of nw %d\n",
			         p_sp->pc, p_sp->nw_id));
			p_sp->t_d_running = SS7_TRUE;
		}
		else
		{
			p_sp->active = SS7_FALSE;
			return;
		}
		/*  SPR Fix 13344 Start */
		p_sp->cong_cause = MTP3_CAUSE_SIG_NETWORK_CONGESTION;
		/*  SPR Fix 13344 Stop */
		sccp_process_cong_param (p_sp);
		p_sp->active = SS7_TRUE;
	}
}

/* GR changes: Begin */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)

/***************************************************************************
**
**      FUNCTION :
**		sccp_m3_pause_cluster_ind
**   
****************************************************************************
**
**      DESCRIPTION :
**  
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_pause_cluster_ind 
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api ;
#endif
{
        scmg_info_t     info, *p_info = &info;
        error_t         ecode;
        U32bit          num_sp = 0, count, i, num_ss;
        ss_entry_t      * p_ss;
/* Start Spr 13263 Fix */
/*      sp_id_t         p_sp_list[MAX_SP]; */
	sp_id_t           *p_sp_list;
#ifdef SCCP_REDN_ENABLED
    	extern U8bit sccp_state;
#endif
/* Start Spr 13075 Fix */
#if 0
    static U16bit			max_sp;  /* To store max sp value */
    static sp_id_t          *p_sp_list;

    if( max_sp  != MAX_SP )
    {
		max_sp = MAX_SP;
		if(p_sp_list != SS7_NULL)
        {
           /* memory freed in case of de-init and allocated with new value.*/
			ss7_mem_free(p_sp_list);
        }    
        /* memory allcated when function called first time. */
        p_sp_list =
            (sp_id_t*)(void*)sccp_malloc((MAX_SP)*sizeof(sp_id_t));
        if( p_sp_list == SS7_NULL )
        {
            SC_A_TRC (("SCCP::SCMG: malloc failure\n"));
            return;
        }
    }
/* Stop Spr 13075 Fix */

#endif

        SC_A_TRC (("SCCP::SCMG: recvd  pause cluster ind\n"));

	    /* spr # 11321 start fix */
	    if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
	    {
	        SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));
	
	        return;
	    }
	    /* spr # 11321 end fix */

        if (SS7_FAILURE == sccp_parse_m3_pause_cluster_ind_api (p_api, p_info, &ecode))
        {
                SC_A_TRC (("SCCP::SCMG: API PARSE ERROR \n"));
                SC_STAT_API_INR_ERR_API_LL();
                SC_A_ERR (ecode);
        /* Fix for SPR No :12135, CSR No : 1 - 652585  Starts */
                 return;
        /* Fix for SPR No :12135, CSR No : 1 - 652585  Ends */
        }

        SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

	/* fix for SPR No : 13263 start */ 

	/*p_sp_list = (sp_id_t)(void *) sccp_malloc ((MAX_SP) * sizeof (sp_id_t)) ;*/
	p_sp_list = (sp_id_t *) sccp_malloc ((MAX_SP) * sizeof (sp_id_t)) ;

	if( p_sp_list == SS7_NULL )
        {
            SC_A_TRC (("SCCP::SCMG: malloc failure\n"));
            return;
        }

        /* get the list of signalling points belonging to this cluster */       

        num_sp = sccp_db_find_cluster_list (p_info, p_sp_list);
        if (num_sp == 0)
        {
                SC_A_TRC (("SCCP::SCMG: cluster %u nw %d unknown to SCCP\n",
                            p_info->cluster, p_info->nw_id));
                SC_STAT_API_INR_ERR_API_LL ();
                SC_A_ERR (ESS7_INVALID_API_ELEMENT);
	/* fix for SPR No: 13263 start */
		sccp_free((U8bit *)p_sp_list);
	/* fix for SPR No: 13263 stop */
                return;
        }
                
        for (count=0; count<num_sp; count++)
        {
                p_info->p_sp = GET_SP_FROM_ID (p_sp_list[count]);

                if (IS_SP_PROHIBITED (p_info->p_sp))
                {
                        MG_TRC (("SCCP::SCMG: pc %u nw_id %d: already down\n",
                                 GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));
	/* fix for SPR No: 13263 start */
		sccp_free((U8bit *)p_sp_list);
	/* fix for SPR No: 13263 stop */
                        return;
                }
 
                /* actions on SP */

                MARK_SP_PROHIBITED (p_info->p_sp);
                SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
      		sccp_send_sp_status_to_mate(p_info->p_sp);
#endif
                MG_TRC (("SCCP::SCMG: pc %u nw_id %d: goes down\n",
                        GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

/* SPR 9022 - Fix Start */
/* Raise an Event alarm when a pause ind is received */
	SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SP, SP_INACCESSIBLE, p_info->p_sp,
				SS7_NULL, SS7_NULL);
/* SPR 9022 - Fix End   */
				/* SPR 10854 - Fix Start */
/* This portion has been commented as it does not send any useful or specific information and proves to be just another copy of pc-state indication */
                /*sccp_local_bcast (p_info->p_sp, SS7_NULL, LBCS_PAUSE);*/
				/* SPR 10854 - Fix End  */

                /* actions on SCCP */

                if (IS_SCCP_PROHIBITED(p_info->p_sp))
                {
                        /* For SSN = "SCMG" */
                        sccp_stop_sst (&p_info->p_sp->scmg_ss);
                }
                else
                {
                        MARK_SCCP_PROHIBITED (p_info->p_sp);
                        MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: goes down\n",
                                 GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

                        sccp_local_bcast (p_info->p_sp, SS7_NULL, LBCS_SCCP_INACCESSIBLE);
                		SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
      			sccp_send_sp_status_to_mate(p_info->p_sp);
#endif
                        sccp_inform_trans_func(p_info->p_sp, SS7_NULL);
                }
        
                /* actions on the subsystems */

                for (i=0, num_ss = GET_NUM_SS_IN_SP(p_info->p_sp),
                        p_ss = GET_SS_LIST_IN_SP (p_info->p_sp);
                        i < num_ss; i++, p_ss = GET_NEXT_SS(p_ss))
                {
                        if (IS_SS_PROHIBITED(p_ss))
                        {
                          MG_TRC (("SCCP::SCMG: SSN %d on pc %u nw %d already down\n",
                                  GET_SS_SSN(p_ss), GET_SP_PC(p_info->p_sp),
                                  GET_SP_NW_ID(p_info->p_sp)));

                          sccp_stop_sst(p_ss);
                        }
                        else
                        {
                          MARK_SS_PROHIBITED(p_ss);
                          SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
                          MG_TRC (("SCCP::SCMG: SSN %d on pc %u nw %d goes down\n",
                                  GET_SS_SSN(p_ss), GET_SP_PC(p_info->p_sp),
                                  GET_SP_NW_ID(p_info->p_sp)));

                          sccp_local_bcast (SS7_NULL, p_ss, LBCS_UOS);
                          sccp_inform_trans_func (p_info->p_sp, p_ss);
                        }

                /* Send SBR */
		if ((COMPARE_ANSI) || (COMPARE_BCGR))
                {
                        ;
                }
                }       /* end of subsystem loop */

        /* Request traffic mix */
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
                ;
        }
        }       /* end of signalling point loop */

	/* fix for SPR No: 13263 start */

	sccp_free((U8bit *)p_sp_list);

	/* fix for SPR No: 13263 stop */

}

                
/***************************************************************************
**
**      FUNCTION :
**   
****************************************************************************
**
**      DESCRIPTION :
**  
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_resume_cluster_ind 
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api ;
#endif
{
        scmg_info_t     info, *p_info = &info;
        error_t         ecode;
        U32bit          num_sp = 0, count;
/*      sp_id_t         p_sp_list[MAX_SP]; */
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
/* Start Spr 13075 Fix */
    static U16bit			max_sp;  /* To store max sp value */
    static sp_id_t          *p_sp_list;

    if( max_sp  != MAX_SP )
    {
		max_sp = MAX_SP;
		if(p_sp_list != SS7_NULL)
        {
           /* memory freed in case of de-init and allocated with new value.*/
			ss7_mem_free(p_sp_list);
        }    
        /* memory allcated when function called first time. */
        p_sp_list =
            (sp_id_t*)(void*)sccp_malloc((MAX_SP)*sizeof(sp_id_t));
        if( p_sp_list == SS7_NULL )
        {
            SC_A_TRC (("SCCP::SCMG: malloc failure\n"));
            return;
        }
    }
/* Stop Spr 13075 Fix */

        SC_A_TRC (("SCCP::SCMG: recvd  resume cluster ind\n"));

        /* spr # 11321 start fix */
        if (sccp_state == UNINITIALIZED || sccp_state==BLOCKED)
        {
            SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));
    
            return;
        }
        /* spr # 11321 end fix */

        if (SS7_FAILURE == sccp_parse_m3_resume_cluster_ind_api (p_api, p_info, &ecode))
        {
                SC_A_TRC (("SCCP::SCMG: API PARSE ERROR \n"));
                SC_STAT_API_INR_ERR_API_LL();
                SC_A_ERR (ecode);
        /* Fix for SPR No :12135, CSR No : 1 - 652585  Starts */
                 return;
        /* Fix for SPR No :12135, CSR No : 1 - 652585  Ends */
        }

        SC_A_TRC (("SCCP::SCMG: parse SUCCESS\n"));

        /* get the list of signalling points belonging to this cluster */       

        num_sp = sccp_db_find_cluster_list (p_info, p_sp_list);
        if (num_sp == 0)
        {
                SC_A_TRC (("SCCP::SCMG: cluster %u nw %d unknown to SCCP\n",
                            p_info->cluster, p_info->nw_id));
                SC_STAT_API_INR_ERR_API_LL ();
                SC_A_ERR (ESS7_INVALID_API_ELEMENT);
                return;
        }
                
        for (count=0; count<num_sp; count++)
        {
                p_info->p_sp = GET_SP_FROM_ID (p_sp_list[count]);

                /* actions on the SP */

                MARK_SP_ALLOWED(p_info->p_sp);
                MG_TRC (("SCCP::SCMG: pc %u nw_id %d: comes up\n",
                        GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

                /* actions on the SCCP */

                MARK_SCCP_ALLOWED(p_info->p_sp);
                MG_TRC (("SCCP::SCMG: SCCP on pc %u nw_id %d: comes up\n",
                        GET_SP_PC(p_info->p_sp), GET_SP_NW_ID(p_info->p_sp)));

                SCCP_SEND_SP_ENTRY_UPDATE (p_info->p_sp);
#ifdef DISTRIBUTED_SCCP
      		sccp_send_sp_status_to_mate(p_info->p_sp);
#endif

                /* for SSN = "SCMG" */
                sccp_stop_sst(&p_info->p_sp->scmg_ss);

                /* Clear SP congestion */
                p_info->p_sp->cls = 0;
                if (IS_T_A_RUNNING(p_info->p_sp))
                        sccp_stop_timer(&p_info->p_sp->t_a_timer_id);

                if (IS_T_D_RUNNING(p_info->p_sp))
                        sccp_stop_timer(&p_info->p_sp->t_d_timer_id);

                if (IS_T_CON_RUNNING(p_info->p_sp))
                        sccp_stop_timer(&p_info->p_sp->t_con_timer_id);
                p_info->p_sp->active = SS7_FALSE;

                /* actions on the subsystems */

                sccp_scmg_spac_bcast (p_info->p_sp, SS7_TRUE);  /* SS7_TRUE indicates
                                                       'RESUME received' */

        /* Start SRT */
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
        {
        }
        }       /* end of loop for signalling points in the cluster */


}

#endif          /* SCCP_BCGR */
/* GR changes: End */


#ifdef DISTRIBUTED_SCCP
/***************************************************************************
**
**      FUNCTION :
**   
****************************************************************************
**
**      DESCRIPTION :
**  
**
**      NOTE :
**
***************************************************************************/
void 
sccp_send_sp_status_to_mate
#ifdef ANSI_PROTO
	(sp_entry_t *p_sp)
#else
	(p_sp)
	sp_entry_t *p_sp;
#endif
{
	U8bit * p_api;
      U16bit api_len;
	error_t ecode;
	return_t ret_val;

     	api_len = DSCCP_SP_STATUS_LEN ;
      p_api= (U8bit *)sccp_malloc(api_len);
	if(p_api == SS7_NULL)
		return;
      sccp_build_sp_status_message(p_api,p_sp,api_len);
      ret_val = dsccp_broadcast_to_mates(p_api,api_len,&ecode);
}

/***************************************************************************
**
**      FUNCTION :
**   
****************************************************************************
**
**      DESCRIPTION :
**  
**
**      NOTE :
**
***************************************************************************/
void 
dsccp_send_scmg_status_to_mate
#ifdef ANSI_PROTO
	(sp_entry_t *p_sp)
#else
	(p_sp)
	sp_entry_t *p_sp;
#endif
{
	U8bit * p_api;
	U8bit *p_elem;
      U16bit api_len;
	error_t ecode;
	return_t ret_val;
	sp_id_t sp_id;
	U32bit temp;

     	api_len = DSCCP_SCCP_STATUS_LEN ;
      p_api= (U8bit *)sccp_malloc(api_len);
	if(p_api == SS7_NULL)
		return;
	sccp_fill_api_header (p_api, DSCCP_MATE_API,
                            DSCCP_SCCP_STATUS_NELEM,
                            api_len);

      p_elem = p_api + API_HEADER_LEN;
	*p_elem++ = DSCCP_API_CAT_SCMG;
      *p_elem++ = DSCCP_API_CMD_SCMG_SCCP_STATUS;
      sp_id = GET_ID_FROM_SP(p_sp);
      temp = (U32bit)sp_id;
      *p_elem++ = (U8bit)temp;
      *p_elem++ = (U8bit)(temp >> 8);
      *p_elem++ = (U8bit)(temp >> 16);
      *p_elem++ = (U8bit)(temp >> 24);
	*p_elem++ = p_sp->scmg_ss.allowed;
	*p_elem++ = p_sp->upu_received;
	*p_elem++ = sc_opt.dsccp_local_instance_id;

      ret_val = dsccp_broadcast_to_mates(p_api,api_len,&ecode);
}

/** SPR 8744 Starts here **/

/***************************************************************************
**
**      FUNCTION :
**   
****************************************************************************
**
**      DESCRIPTION :
**  
**
**      NOTE :
**
***************************************************************************/
void 
dsccp_send_cong_status_to_mate
#ifdef ANSI_PROTO
	()
#else
	()
#endif
{
    U8bit * p_api;
    U16bit api_len;
    error_t ecode;
    return_t ret_val;

    api_len = DSCCP_CONG_STATUS_LEN;
    p_api= (U8bit *)sccp_malloc(api_len);
    if(p_api == SS7_NULL)
        return;
    dsccp_build_cong_status_api(p_api,api_len);
    ret_val   = dsccp_broadcast_to_mates(p_api,api_len,&ecode);
}

void
dsccp_build_cong_status_api
#ifdef ANSI_PROTO
    (U8bit *p_api,U16bit api_len)
#else
    (p_api,api_len)
    U8bit *p_api;
    U16bit api_len;
#endif
{
    U8bit *p_elem;
    sccp_fill_api_header (p_api, DSCCP_MATE_API,
            DSCCP_SCCP_STATUS_NELEM,
            api_len);
    p_elem = p_api + API_HEADER_LEN;
    *p_elem++ = DSCCP_API_CAT_SCMG;
    *p_elem++ = DSCCP_API_CMD_SCMG_CONG_STATUS;
    *p_elem++ = sccp_cong.level  ;
    *p_elem++ = sccp_cong.counter;
}
 

/** SPR 8744 ends here **/

#endif


#if 0
#ifdef DISTRIBUTED_SCCP

void 
sccp_send_sp_status_to_mate
#ifdef ANSI_PROTO
      (sp_entry_t *p_sp)
#else
      (p_sp)
      sp_entry_t *p_sp;
#endif
{
	U8bit * p_api;
      U16bit api_len;

      api_len = DSCCP_SP_STATUS_LEN ;
      p_api= (U8bit *)sccp_malloc(api_len);
      sccp_build_sp_status_message(p_api,p_ss,api_len);
      sccp_broadcast_to_mates(p_api,api_len);
}

#endif
#endif
