/***************************************************************************
**
**  FILE NAME:
**      sc_mgbld.c
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
**  08Apr2004 Hitesh Sharma           Fixed SPR # 13344
**  18Dec2002 Suyash Tripathi         Fixed SPR # 10851
**  24Jul2002 Salil Agrawal           Fixed SPR # 9341
**  24Oct2001 Prateek Bidwalkar       Fixed SPR # 6750
**  24Feb2000 Ramu Kandula            Fixed SPR # 2695
**  9May98   Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#include "sc_bcast.h"
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */

#if 0
#define    SIGTRAN_ALRM_LVL_CLEARED    0
#define    SIGTRAN_ALRM_LVL_INFO       1
#define    SIGTRAN_ALRM_LVL_WARN       2
#define    SIGTRAN_ALRM_LVL_MAJR       3
#define    SIGTRAN_ALRM_LVL_MINR       4
#define    SIGTRAN_ALRM_LVL_CRIT       5
#endif

static U8bit * sccp_put_sp_status_elem
	_ARGS_ ((U8bit * p_elem, sp_entry_t * p_sp));

static U8bit * sccp_put_sccp_status_elem
	_ARGS_ ((U8bit * p_elem, sp_entry_t * p_sp));

static U8bit * sccp_put_restr_imp_level_elem
	_ARGS_ ((U8bit * p_elem, sp_entry_t * p_sp));

static U8bit * sccp_put_user_status_elem
	_ARGS_ ((U8bit * p_elem, ss_entry_t * p_ss));


extern void send_alarm_from_sigtran(U16bit alarm_id,U8bit level,U16bit slot_id,U32bit pc,U8bit ssn,U16bit asid,U16bit aspid);

/***************************************************************************
**
**      FUNCTION :
**         builds and sends n_state indicattion API
****************************************************************************
**
**      DESCRIPTION :
**         builds api by filling elements affected subsystem and status
**         and sends it to the user
**
**      NOTE :
**
***************************************************************************/

void 
sccp_send_n_state_ind 
#ifdef ANSI_PROTO
	(ss_entry_t 	* p_ss, 
	 ss_entry_t 	* p_css)
#else
	(p_ss, p_css)
	ss_entry_t     * p_ss ;
	ss_entry_t     * p_css ;
#endif
{
	U8bit * p_api, * p_elem;
	U16bit api_len,alarm_id=0;
	U32bit dpc=0;

	MG_TRC (("SCCP::SCMG: sending n state ind of SSN %d pc %d nw %d "
	         " to conc SSN %d pc %d nw %d",
	        p_ss->ssn, GET_SS_NW_ID(p_ss), GET_SP_PC(GET_SP_OF_SS(p_ss)),
	        p_css->ssn, GET_SS_NW_ID(p_css), 
		GET_SP_PC(GET_SP_OF_SS(p_css))));
		dpc = GET_SP_PC(GET_SP_OF_SS(p_ss));

	/* Allocate memory to build the API */
/* start spr # 9341 */	
    if ((sc_opt.standard == STACK_ANSI) ||
		(sc_opt.standard == STACK_BCGR) ||
        (sc_opt.standard == STACK_CHINESE))
	{
	  api_len = SCCP_ANSI_N_STATE_IND_LEN ;
	}
	else
	{
	  api_len = SCCP_ITU_ETSI_N_STATE_IND_LEN ;
	}
/* #ifdef SCCP_CHINESE */
	/* api_len = SCCP_ANSI_N_STATE_IND_LEN ; */
/* #endif */
/* end spr # 9341 */

	if (SS7_NULL == (p_api = sccp_malloc (api_len)))
	{
		MG_TRC (("SCCP::SCMG: cannot send n_state_ind"));
		return;
	}

	/* Fill the api header */
	sccp_fill_api_header (p_api, SCCP_N_STATE_INDICATION,
	                      SCCP_N_STATE_IND_NELEM,
	                      api_len);

	p_elem = p_api + API_HEADER_LEN;

	/* put mandatory elements */
        /* Put the SSN of the CSS */
        *p_elem++ = p_css->ssn ;
	p_elem = sccp_put_affected_ss_elem (p_elem, p_ss);
	p_elem = sccp_put_user_status_elem (p_elem, p_ss);

/* Added by Amaresh for start sending Alarm to SCM SSA Received */
	if (p_ss->allowed)	
	{
		alarm_id = 443;
	}
	else
	{
			alarm_id = 444;
	}
		MG_TRC (("SCCP::SCMG: [ALARM_SIGTRAN] alarm_id %d to be sent",alarm_id));
		send_alarm_from_sigtran(alarm_id,5,0,dpc,p_ss->ssn,0,0); /* CRIT */
/* Added by Amaresh for start sending Alarm to SCM SSA Received */
	sccp_sendto_tc (p_api, p_css);
}

/***************************************************************************
**
**      FUNCTION :
**         builds and sends n pc state indication
****************************************************************************
**
**      DESCRIPTION :
**         fills mandatory elem affected sp and sp status. optional elem
**         sccp status and RIL and sends to the conc ss
**
**      NOTE :
**
***************************************************************************/

void 
sccp_send_n_pcstate_ind 
#ifdef ANSI_PROTO
	(sp_entry_t 	* p_sp, 
	 ss_entry_t 	* p_css,
	 U8bit 		bcast_type)
#else
	(p_sp, p_css, bcast_type)
	sp_entry_t     * p_sp ;
	ss_entry_t     * p_css ;
	U8bit          bcast_type ;
#endif
{
	U8bit 	* p_api, * p_elem;
	U8bit 	num_elem;
	U16bit 	api_len;

	MG_TRC (("SCCP::SCMG: sending n-pc-state ind of pc %d nw %d to "
	        "conc SSN %d nw %d pc %d\n",
	        GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp),
	        p_css->ssn, GET_SS_NW_ID(p_css), 
		GET_SP_PC(GET_SP_OF_SS(p_css))));
/* start spr # 9341 */
	/* Allocate memory to build the API */
	if ((sc_opt.standard == STACK_ANSI) ||
		(sc_opt.standard == STACK_BCGR) ||
        (sc_opt.standard == STACK_CHINESE))
	{
	  api_len = SCCP_ANSI_N_PCSTATE_IND_MIN_LEN ;
	}
	else
	{
	  api_len = SCCP_ITU_ETSI_N_PCSTATE_IND_MIN_LEN ;
	}
/* #if defined (SCCP_CHINESE) */
	  /* api_len = SCCP_ANSI_N_PCSTATE_IND_MIN_LEN ; */
/* #endif */
/* end spr # 9341 */
	num_elem = SCCP_N_PCSTATE_IND_MIN_NELEM;


	/** SPR # 2695 Fix Start **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{

		/* Calculate the length of the buffer required and the number of
	   		api elements based on the optional elements to be put in */
	
		if ( (LBCS_STATUS == bcast_type) 
	     	|| (LBCS_RIL == bcast_type) 
			)
		{
			api_len += SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN +
		           	SCCP_ELEM_REMOTE_SCCP_STATUS_LEN;
			num_elem ++;
		}
	
		if (LBCS_RIL == bcast_type)  
		{
			api_len += SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN +
		           	SCCP_ELEM_RESTR_IMP_LEVEL_LEN;
			num_elem ++;
		}
	}
#endif
	/** SPR # 2695 Fix End **/

	/* SPR 10851 - Fix Start */	
		if (LBCS_SCCP_INACCESSIBLE == bcast_type) 
		{
			api_len += SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN +
		           	SCCP_ELEM_REMOTE_SCCP_STATUS_LEN;
			num_elem ++;
		}
	/* SPR 10851 - Fix End  */	
		if (LBCS_SCCP_ACCESSIBLE == bcast_type) 
		{
			api_len += SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN +
		           	SCCP_ELEM_REMOTE_SCCP_STATUS_LEN;
			num_elem ++;
		}

	/* Allocate memory to build the API */
	if (SS7_NULL == (p_api = sccp_malloc (api_len)))
	{
		MG_TRC (("SCCP::SCMG: Cannot send n_pcstate_ind\n"));
		return;
	}

	p_elem = p_api + API_HEADER_LEN;

	/* put mandatory elements */
        *p_elem++ = p_css->ssn ;
	p_elem = sccp_put_affected_sp_elem (p_elem, p_sp);
	p_elem = sccp_put_sp_status_elem (p_elem, p_sp);

	/** SPR # 2695 Fix Start **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{

		/* put optional elements */
		/* put Remote SCCP status element */

		if ( (LBCS_STATUS == bcast_type) ||
	     	(LBCS_RIL == bcast_type) )
		{
			p_elem = sccp_put_sccp_status_elem (p_elem, p_sp);
		}
	
		/* put Restricted importance level element */
		if (LBCS_RIL == bcast_type) 
		{
			p_elem = sccp_put_restr_imp_level_elem (p_elem, p_sp);
		}
	}
#endif
	/** SPR # 2695 Fix End **/

	/* SPR 10851 - Fix Start */
	/* When PAUSE is received then remote sccp status should **   
	** also be sent **
	** ITU Q.714 section 5.2.2 , ANSI T1.112.4-31 **/
	if (LBCS_SCCP_INACCESSIBLE == bcast_type)
	{
		/* put element id */
		*p_elem = SCCP_ELEM_REMOTE_SCCP_STATUS;	
		p_elem += SCCP_ELEM_ID_LEN;

		/* put element length */
		PUT_SCCP_ELEM_LEN (p_elem, SCCP_ELEM_REMOTE_SCCP_STATUS_LEN);
		p_elem += SCCP_ELEM_LEN_LEN;

		/* put element value */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
		if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
		{
			*p_elem++ = SCCP_REMOTE_SCCP_UNAVAILABLE;
		}		
#endif
#if ( defined(SCCP_ANSI) || defined(SCCP_BCGR) ) 
		if ( (COMPARE_ANSI) || (COMPARE_BCGR))  
		{
			*p_elem++ = SCCP_REMOTE_SCCP_INACCESIBLE;
		}
#endif

	}
	/* SPR 10851 - Fix End   */

	/* When RESUME or subsystem allowed or tstat info expiry is
	**received then remote sccp status should **   
	** also be sent **
	** ITU Q.714 section 5.2.3 , ANSI T1.112.4-33 **/
	if (LBCS_SCCP_ACCESSIBLE == bcast_type)
	{
		/* put element id */
		*p_elem = SCCP_ELEM_REMOTE_SCCP_STATUS;	
		p_elem += SCCP_ELEM_ID_LEN;

		/* put element length */
		PUT_SCCP_ELEM_LEN (p_elem, SCCP_ELEM_REMOTE_SCCP_STATUS_LEN);
		p_elem += SCCP_ELEM_LEN_LEN;

		/* put element value */

			*p_elem++ = SCCP_REMOTE_SCCP_AVAILABLE;

	}
	

	sccp_fill_api_header (p_api, SCCP_N_PCSTATE_INDICATION, num_elem,
	                      api_len);

	sccp_sendto_tc (p_api, p_css);
}

/***************************************************************************
**
**      FUNCTION :
**         puts affected sp elem
****************************************************************************
**
**      DESCRIPTION :
**         this is a fixed elem
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_put_affected_sp_elem 
#ifdef ANSI_PROTO
	(U8bit 		* p_elem, 
	 sp_entry_t 	* p_sp)
#else
	(p_elem, p_sp)
	U8bit          * p_elem ;
	sp_entry_t     * p_sp ;
#endif
{
	PUT_PC (p_elem, p_sp->pc);
	p_elem += PC_SIZE;

	return p_elem;
}

/***************************************************************************
**
**      FUNCTION :
**         puts sp status elem
****************************************************************************
**
**      DESCRIPTION :
**         this is a fixed elem
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_put_sp_status_elem 
#ifdef ANSI_PROTO
	(U8bit 		* p_elem, 
	 sp_entry_t 	* p_sp)
#else
	(p_elem, p_sp)
	U8bit          * p_elem ;
	sp_entry_t     * p_sp ;
#endif
{
	/* Fill in Signaling point status parameter */
	if ( ! p_sp->allowed)
		*p_elem = SP_INACCESSIBLE;
	else
	{
	/* Fix for SPR : 13344 Start */
		if (p_sp->ril > 0)
	/*	if (p_sp->cls > 0)	*/
	/* Fix for SPR : 13344 Stop */
			*p_elem = SP_CONGESTED;
		else
			*p_elem = SP_ACCESSIBLE;
	}

	return (p_elem + SCCP_ELEM_SIG_POINT_STATUS_LEN);
}

/***************************************************************************
**
**      FUNCTION :
**         puts sccp status elem
****************************************************************************
**
**      DESCRIPTION :
**         this is a optional elem
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_put_sccp_status_elem 
#ifdef ANSI_PROTO
	(U8bit 		* p_elem, 
	 sp_entry_t 	* p_sp)
#else
	(p_elem, p_sp)
	U8bit          * p_elem ;
	sp_entry_t     * p_sp ;
#endif
{

	/* put element id */
	*p_elem = SCCP_ELEM_REMOTE_SCCP_STATUS;
	p_elem += SCCP_ELEM_ID_LEN;

	/* put element length */
	PUT_SCCP_ELEM_LEN (p_elem, SCCP_ELEM_REMOTE_SCCP_STATUS_LEN);
	p_elem += SCCP_ELEM_LEN_LEN;

	/* Fix for SPR No : 13344 Start */ 
	        /* put element value */
	if (! p_sp->cong_cause) 
	{
        if (p_sp->scmg_ss.allowed)
                *p_elem++ = SCCP_REMOTE_SCCP_AVAILABLE;
        else   
        {
		switch (UPU_CAUSE(p_sp))
		{
			case MTP3_CAUSE_USER_PART_UNAV_UNKNOWN:
				*p_elem++ = SCCP_REMOTE_SCCP_UNAVAILABLE;
				break;

			case MTP3_CAUSE_USER_PART_UNAV_UNEQUIP_REMOTE_USER:
				*p_elem++ = SCCP_REMOTE_SCCP_UNEQUIPPED;
				break;

			case MTP3_CAUSE_USER_PART_UNAV_INACCESS_REMOTE_USER:
				*p_elem++ = SCCP_REMOTE_SCCP_INACCESIBLE;
				break;

			default:
                                MG_TRC (("SCCP::SCMG: Invalid UPU cause\n"));
				break;
		}
	}
	}
	else if(p_sp->cong_cause == SCCP_CAUSE_SIG_CONGESTION ) 
		*p_elem++ = SCCP_REMOTE_SCCP_CONGESTED;	
	/* Fix for SPR No : 13344 Stop */ 

	return p_elem;
}

/***************************************************************************
**
**      FUNCTION :
**         puts restricted imp level elem
****************************************************************************
**
**      DESCRIPTION :
**         This is a optional elem
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_put_restr_imp_level_elem 
#ifdef ANSI_PROTO
	(U8bit 		* p_elem, 
	 sp_entry_t 	* p_sp)
#else
	(p_elem, p_sp)
	U8bit          * p_elem ;
	sp_entry_t     * p_sp ;
#endif
{

	/* Put element id */
	*p_elem = SCCP_ELEM_RESTR_IMPORTANCE_LEVEL;
	p_elem += SCCP_ELEM_ID_LEN;

	/* Put element length */
	PUT_SCCP_ELEM_LEN (p_elem, SCCP_ELEM_RESTR_IMP_LEVEL_LEN);
	p_elem += SCCP_ELEM_LEN_LEN;

	/* Put element value */
	*p_elem = p_sp->ril;
	p_elem += SCCP_ELEM_RESTR_IMP_LEVEL_LEN;

	return p_elem;
}

/***************************************************************************
**
**      FUNCTION :
**         puts affected subsystem elem
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_put_affected_ss_elem 
#ifdef ANSI_PROTO
	(U8bit 		* p_elem, 
	 ss_entry_t 	* p_ss)
#else
	(p_elem, p_ss)
	U8bit          * p_elem ;
	ss_entry_t     * p_ss ;
#endif
{
	sp_entry_t * p_sp = GET_SP_OF_SS(p_ss);

#if 0
	*p_elem++ = GET_SS_NW_ID(p_ss);
#endif
	PUT_PC(p_elem, p_sp->pc);
	p_elem += PC_SIZE;
	*p_elem++ = p_ss->ssn;

	return p_elem;
}

/***************************************************************************
**
**      FUNCTION :
**          puts user status element
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_put_user_status_elem 
#ifdef ANSI_PROTO
	(U8bit 		* p_elem, 
	 ss_entry_t 	* p_ss)
#else
	(p_elem, p_ss)
	U8bit          * p_elem ;
	ss_entry_t     * p_ss ;
#endif
{
	*p_elem++ = (p_ss->allowed ? SCCP_USER_IN_SERVICE :
                                     SCCP_USER_OUT_OF_SERVICE);

	return p_elem;
}

/***************************************************************************
**
**      FUNCTION :
**          builds a SSN status message
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/
#ifdef DISTRIBUTED_SCCP
void
sccp_build_ss_status_message
#ifdef ANSI_PROTO
	(U8bit *p_api, ss_entry_t *p_ss, U16bit api_len)
#else
	(p_api,p_ss,api_len)
	U8bit *p_api;
	ss_entry_t *p_ss;
	U16bit api_len;
#endif
{
	U8bit *p_elem;
	U32bit temp;
	ss_id_t ss_id;
	
	sccp_fill_api_header (p_api, DSCCP_MATE_API,
	                      DSCCP_SS_STATUS_NELEM,
	                      api_len);

	p_elem = p_api + API_HEADER_LEN;
	*p_elem++ = DSCCP_API_CAT_SCMG;
	*p_elem++ = DSCCP_API_CMD_SCMG_SS_STATUS;
	*p_elem++ = sc_opt.dsccp_local_instance_id;
	ss_id = GET_ID_FROM_SS(p_ss);
	temp = (U32bit)ss_id;
	*p_elem++ = (U8bit)temp;
	*p_elem++ = (U8bit)(temp >> 8);
	*p_elem++ = (U8bit)(temp >> 16);
	*p_elem++ = (U8bit)(temp >> 24);
	*p_elem = (p_ss->allowed ? SCCP_USER_IN_SERVICE : SCCP_USER_OUT_OF_SERVICE);
}


/***************************************************************************
**
**      FUNCTION :
**          builds a SP status message
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/
void
sccp_build_sp_status_message
#ifdef ANSI_PROTO
	(U8bit *p_api, sp_entry_t *p_sp, U16bit api_len)
#else
	(p_api,p_sp,api_len)
	U8bit *p_api;
	sp_entry_t *p_sp;
	U16bit api_len;
#endif
{
	U8bit *p_elem;
	sp_id_t sp_id;
	U32bit temp;
	
	sccp_fill_api_header (p_api, DSCCP_MATE_API,
	                      DSCCP_SP_STATUS_NELEM,
	                      api_len);

	p_elem = p_api + API_HEADER_LEN;

	*p_elem++ = DSCCP_API_CAT_SCMG;
	*p_elem++ = DSCCP_API_CMD_SCMG_SP_STATUS;
	sp_id = GET_ID_FROM_SP(p_sp);
	temp = (U32bit)sp_id;
	*p_elem++ = (U8bit)temp;
	*p_elem++ = (U8bit)(temp >> 8);
	*p_elem++ = (U8bit)(temp >> 16);
	*p_elem++ = (U8bit)(temp >> 24);
	p_elem = sccp_put_sp_status_elem (p_elem, p_sp);
	*p_elem++ = p_sp->upu_received;
	*p_elem++ = p_sp->upu_cause;
	*p_elem++ = (U8bit)p_sp->rl;
	*p_elem++ = (U8bit)p_sp->rsl;
	*p_elem++ = (U8bit)p_sp->cls;
	*p_elem = (U8bit)p_sp->ril;
}
#endif
