/***************************************************************************
**  FILE NAME:
**      sc_dbadd.c
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   		REASON
**  -------  ----------------  -----  ---------------------------------
**  26Feb2004 Hitesh Sharma                     Fixed SPR # 13263
**  21Nov2003 knaveen                           Fixed SPR # 13075
**  31Dec2002 Hitesh Sharma                     Fixed SPR # 11016
**  07Aug2002 Prateek Bidwalkar                 Fixed SPR # 9502
**  26Feb2000 Ramu Kandula                      Fixed SPR # 2757
**  13sept2001 Pawanish Modi                     Fixed SPR # 6186
**   3/6/98  Sriganesh. Kini   HSS:20800008  	Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

#ifdef BACK_UP_SSN
sccp_db_ssn_back_up sccp_back_up_table[MAX_SSN];

return_t sccp_db_add_back_up_ss(U8bit ssn, pc_t point_code);

void sccp_db_del_back_up_ss(U8bit ssn);

return_t sccp_db_search_back_up_ss(U8bit ssn, pc_t *point_code);
#endif

static return_t sccp_db_chk_sp_conf_info
	_ARGS_ ((db_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode));

static return_t sccp_db_chk_ss_conf_info
	_ARGS_ ((db_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode));

static return_t sccp_db_chk_css_conf_info
	_ARGS_ ((db_css_info_t * p_css_conf_info, error_t * p_ecode));

return_t sccp_db_chk_csp_conf_info
	_ARGS_ ((db_csp_info_t * p_csp_conf_info, error_t * p_ecode));

/*****************************************************************************
**      FUNCTION :
**            Configures a signaling point
******************************************************************************
**
**      DESCRIPTION :
**            This call a function to check the config data.
**            If sp is not configured earlier it initializes the data of
**            the sp and the management subsystem
**
**      NOTE :
**
*****************************************************************************/
return_t
sccp_db_conf_sp
#ifdef ANSI_PROTO
	(db_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode)
#else
	(p_sp_conf_info, p_ecode)
	 db_sp_conf_info_t * p_sp_conf_info;
	 error_t * p_ecode;
#endif
{
	sp_entry_t * p_sp;
	extern sp_entry_t sccp_local_sp; /** For SPR # 2757 **/

	if (SS7_FAILURE == sccp_db_chk_sp_conf_info(p_sp_conf_info, p_ecode))
		return SS7_FAILURE;

	p_sp = GET_SP_FROM_ID(p_sp_conf_info->sp_id);

	/* Configure the signaling point */
	SET_SP_CONFIGURED(p_sp);

	/* Set all relevant data for the signaling point */
	SET_SP_LOCAL_FLAG (p_sp, p_sp_conf_info->local);
	SET_SP_NW_ID (p_sp, p_sp_conf_info->nw_id);
	SET_SP_PC (p_sp, p_sp_conf_info->pc);

	/** SPR #2757 Fix Start **/
/* SPR # 9502 Fix Start */
#if 0
	if (p_sp_conf_info->local)
#endif
	if (p_sp_conf_info->local == SC_PRIMARY_SP)
/* SPR # 9502 Fix End */
	{
		SET_SP_CONFIGURED(&sccp_local_sp);
		SET_SP_LOCAL_FLAG (&sccp_local_sp, p_sp_conf_info->local);
		SET_SP_NW_ID (&sccp_local_sp, p_sp_conf_info->nw_id);
		SET_SP_PC (&sccp_local_sp, p_sp_conf_info->pc);
	}
	/** SPR #2757 Fix End **/

	/* Setup hash table entry */
	sccp_db_insert_sp_hash_list (p_sp);

	/* Initialize the number of subsystems */
	SET_NUM_SS_IN_SP (p_sp, 0);

	/* initialize management subsystem */
	SET_SS_SSN(&(p_sp->scmg_ss), SCMG_SSN);
	SET_SP_OF_SS (&(p_sp->scmg_ss), p_sp);
	SET_NUM_CSS (&(p_sp->scmg_ss), 0);
	SET_NUM_CSP (&(p_sp->scmg_ss), 0);

	/* SPR # 6186 start */

	if (p_sp_conf_info->local)
	{
		p_sp->scmg_ss.registered = SS7_TRUE;
	}

	/* SPR # 6186 end */

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**           configures a subsystem
******************************************************************************
**
**      DESCRIPTION :
**          Calls a function to check the config param. if it succeeds it
**          configures the subsystem by attaching it to the signaling point
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_conf_ss
#ifdef ANSI_PROTO
	(db_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode)
#else
	(p_ss_conf_info, p_ecode)
	 db_ss_conf_info_t 	*p_ss_conf_info;
	 error_t 		*p_ecode;
#endif
{
	ss_entry_t * p_ss;
	sp_entry_t * p_sp;

	if (SS7_FAILURE == sccp_db_chk_ss_conf_info (p_ss_conf_info, p_ecode))
		return SS7_FAILURE;

	p_ss = GET_SS_FROM_ID (p_ss_conf_info->ss_id);
	p_sp = GET_SP_FROM_ID (p_ss_conf_info->sp_id);

	/* Configure the Subsystem */
	SET_SS_CONFIGURED (p_ss);

	/* set relevant data of the ss */
	SET_SS_SSN (p_ss, p_ss_conf_info->ssn);

/* SPR # 9502 Fix Start */	
	if((SC_PRIMARY_SP == p_sp->local) || (SC_REMOTE_SP == p_sp->local))
/* SPR # 9502 Fix End */
		SET_SP_OF_SS (p_ss, p_sp);

	/* Insert the subsystem in the list of subsystems */
	sccp_db_insert_ss_in_sp (p_ss, p_sp);

        /* SPR # 11016 Fix Start */
        if((SC_PRIMARY_SP == p_sp->local) || (SC_REMOTE_SP == p_sp->local))
        {
	/* Initialize num_css and num_csp of the ss */
	SET_NUM_CSS (p_ss, 0);
	SET_NUM_CSP (p_ss, 0);
        }
        /* SPR # 11016 Fix Ends */
	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**           configures a concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**           calls a function to check the config data and then inserts
**           the css in the list of css. css and csp list indices of all other
**           subsystems are also adjusted appropriately
**
**      NOTE :
**
*****************************************************************************/
return_t
sccp_db_conf_css
#ifdef ANSI_PROTO
	(db_css_info_t * p_css_conf_info, error_t * p_ecode)
#else
	(p_css_conf_info, p_ecode)
	 db_css_info_t 	*p_css_conf_info;
	 error_t 	*p_ecode;
#endif
{
	ss_entry_t * p_ss, * p_css, * p_tmp_ss;
	U32bit i;

	if (SS7_FAILURE == sccp_db_chk_css_conf_info(p_css_conf_info, p_ecode))
		return SS7_FAILURE;

	p_ss  = GET_SS_FROM_ID (p_css_conf_info->ss_id);
	p_css = GET_SS_FROM_ID (p_css_conf_info->css_id);

	sccp_db_insert_css (p_ss, p_css);

	/* Adjust css and csp indices of other subsystems */
	p_tmp_ss = GET_SS_FROM_ID (0);
	for (i=0; i < MAX_SS; i++, p_tmp_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_tmp_ss)) continue;

		if (p_tmp_ss == p_ss)
		{
			if ((GET_NUM_CSP(p_tmp_ss) > 0) &&
			    (GET_CSP_LIST(p_tmp_ss) > GET_CSS_LIST(p_ss)))
			{
				SET_CSP_LIST(p_tmp_ss, GET_CSP_LIST(p_tmp_ss) + SIZEOF_SS_ID_T);
			}
			continue;
		}

		if ((GET_NUM_CSS(p_tmp_ss) > 0) &&
		    (GET_CSS_LIST(p_tmp_ss) > GET_CSS_LIST(p_ss)))
		{
			SET_CSS_LIST(p_tmp_ss, GET_CSS_LIST(p_tmp_ss) + SIZEOF_SS_ID_T);
		}

		if ((GET_NUM_CSP(p_tmp_ss) > 0) &&
		    (GET_CSP_LIST(p_tmp_ss) > GET_CSS_LIST(p_ss)))
		{
			SET_CSP_LIST(p_tmp_ss, GET_CSP_LIST(p_tmp_ss) + SIZEOF_SS_ID_T);
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**          configures a concerned signaling point
******************************************************************************
**
**      DESCRIPTION :
**         call a function to check the input configuration. Then attaches
**         this csp in the list of csp's for the subsystem
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_conf_csp
#ifdef ANSI_PROTO
	(db_csp_info_t * p_csp_conf_info, error_t * p_ecode)
#else
	(p_csp_conf_info, p_ecode)
	 db_csp_info_t 	*p_csp_conf_info;
	 error_t 	*p_ecode;
#endif
{
	ss_entry_t * p_ss, * p_tmp_ss;
	sp_entry_t * p_csp;
	U32bit i;

	if (SS7_FAILURE == sccp_db_chk_csp_conf_info (p_csp_conf_info, p_ecode))
		return SS7_FAILURE;

	p_ss  = GET_SS_FROM_ID(p_csp_conf_info->ss_id);
	p_csp = GET_SP_FROM_ID(p_csp_conf_info->csp_id);

	sccp_db_insert_csp (p_ss, p_csp);

	/* Adjust the indices of csp and css of all other subsystems */
	p_tmp_ss = GET_SS_FROM_ID (0);
	for (i=0; i < MAX_SS; i++, p_tmp_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_tmp_ss))
			continue;

		if (p_tmp_ss == p_ss)
		{
			if ((GET_NUM_CSS(p_tmp_ss) > 0) &&
			    (GET_CSS_LIST(p_tmp_ss) > GET_CSP_LIST(p_ss)))
			{
				SET_CSS_LIST(p_tmp_ss, GET_CSS_LIST(p_tmp_ss) + SIZEOF_SP_ID_T);
			}
			continue;
		}

		if ((GET_NUM_CSS(p_tmp_ss) > 0) &&
		    (GET_CSS_LIST(p_tmp_ss) > GET_CSP_LIST(p_ss)))
		{
			SET_CSS_LIST(p_tmp_ss, GET_CSS_LIST(p_tmp_ss) + SIZEOF_SP_ID_T);
		}

		if ((GET_NUM_CSP(p_tmp_ss) > 0) &&
		    (GET_CSP_LIST(p_tmp_ss) > GET_CSP_LIST(p_ss)))
		{
			SET_CSP_LIST(p_tmp_ss, GET_CSP_LIST(p_tmp_ss) + SIZEOF_SP_ID_T);
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**          checks the input for configuring a sp
******************************************************************************
**
**      DESCRIPTION :
**         checks that the sp_id is not already configured and also that the
**         same point code does not exist in this network
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_chk_sp_conf_info
#ifdef ANSI_PROTO
	(db_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode)
#else
	(p_sp_conf_info, p_ecode)
	 db_sp_conf_info_t 	*p_sp_conf_info;
	 error_t 		*p_ecode;
#endif
{
	sp_entry_t * p_sp;

#if 0
	if (SS7_FAILURE == sccp_db_chk_nw_id (p_sp_conf_info->nw_id, p_ecode))
		return SS7_FAILURE;
#endif

	if (SS7_FAILURE == sccp_db_check_pc (p_sp_conf_info->pc, p_ecode))
		return SS7_FAILURE;

/* Start Spr 13075 Fix */
/* Start Spr 13263 fix */
	if ( ! IS_SPID_VALID(p_sp_conf_info->sp_id)) 
/* 	if ( ! ((p_sp_conf_info->sp_id)< MAX_SP))	*/
/* Stop Spr 13075 Fix */
/* Stop Spr 13263 Fix */
	{
		*p_ecode = ESCCP_INVALID_SP_ID;
		return SS7_FAILURE;
	}

	p_sp = GET_SP_FROM_ID (p_sp_conf_info->sp_id);

	if (IS_SP_CONFIGURED(p_sp))
	{
		*p_ecode = ESCCP_SP_ALREADY_CONFIGURED;
		return SS7_FAILURE;
	}

	if (! (SS7_NULL == sccp_db_find_sp (p_sp_conf_info->nw_id, p_sp_conf_info->pc)))
	{
		*p_ecode = ESCCP_SP_ALREADY_CONFIGURED;
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**          checks the subsystem configuration information
******************************************************************************
**
**      DESCRIPTION :
**         checks that the subsystem id is not already configured and
**         the signalin point is configured and this subsystem does not
**         already exist for this signaling point
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_chk_ss_conf_info
#ifdef ANSI_PROTO
	(db_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode)
#else
	(p_ss_conf_info, p_ecode)
	db_ss_conf_info_t 	*p_ss_conf_info;
	error_t 		*p_ecode;
#endif
{
	ss_entry_t * p_ss;
	sp_entry_t * p_sp;

	if ( ! IS_SSID_VALID(p_ss_conf_info->ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_ss = GET_SS_FROM_ID (p_ss_conf_info->ss_id);

/* SPR # 9502 Fix Start */
#if 0
	if (IS_SS_CONFIGURED(p_ss))
	{
		*p_ecode = ESCCP_SS_ALREADY_CONFIGURED;
		return SS7_FAILURE;
	}
#endif
/* SPR # 9502 Fix End */

 
    /* Check the value of the SSN */
    if (p_ss_conf_info->ssn < MIN_VALID_SSN)
    {
        *p_ecode = ESCCP_INVALID_SSN;
        return SS7_FAILURE;
    }

	/* Check that sp_id is valid and configured */
/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if ( ! IS_SPID_VALID(p_ss_conf_info->sp_id)) 
/*	if ( ! ((p_ss_conf_info->sp_id)< MAX_SP))	*/
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
	{
		*p_ecode = ESCCP_INVALID_SP_ID;
		return SS7_FAILURE;
	}

	p_sp = GET_SP_FROM_ID(p_ss_conf_info->sp_id);
	if ( ! (SS7_NULL == sccp_db_find_ss (p_sp, p_ss_conf_info->ssn)))
	{
		*p_ecode = ESCCP_SS_ALREADY_CONFIGURED;
		return SS7_FAILURE;
	}


	p_sp = GET_SP_FROM_ID (p_ss_conf_info->sp_id);
	if ( ! IS_SP_CONFIGURED(p_sp))
	{
		*p_ecode = ESCCP_INVALID_SP_ID;
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}


/*****************************************************************************
**      FUNCTION :
**        checks the configuration information of a concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**        checks that the subsystem and the concerned subsystem is configured
**        and that the concerned subsystem is not already configured as a
**        concerned subsystem
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_chk_css_conf_info
#ifdef ANSI_PROTO
	(db_css_info_t * p_css_conf_info, error_t * p_ecode)
#else
	(p_css_conf_info, p_ecode)
	 db_css_info_t 	*p_css_conf_info;
	 error_t 	*p_ecode;
#endif
{
	ss_entry_t * p_ss, * p_css, * p_tmp_css;
	Boolean found;
	U8bit * p_css_list;
	U32bit i;

	if ( ! IS_SSID_VALID(p_css_conf_info->ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_ss  = GET_SS_FROM_ID(p_css_conf_info->ss_id);

	if ( ! IS_SS_CONFIGURED(p_ss))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	if ( ! IS_SSID_VALID(p_css_conf_info->css_id))
	{
		*p_ecode = ESCCP_INVALID_CSS_ID;
		return SS7_FAILURE;
	}

	p_css = GET_SS_FROM_ID (p_css_conf_info->css_id);

	if ( ! IS_SS_CONFIGURED(p_css))
	{
		*p_ecode = ESCCP_INVALID_CSS_ID;
		return SS7_FAILURE;
	}

	if ( ! IS_SS_LOCAL(p_css))
	{
		*p_ecode = ESCCP_INVALID_CSS_ID;
		return SS7_FAILURE;
	}

	/* Check if the css_id already occurs as a css of the ss */
	found = SS7_FALSE;
	p_css_list = GET_CSS_LIST(p_ss);
	for (i=0; i < GET_NUM_CSS(p_ss); i++,
	     p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
	{
		p_tmp_css = GET_CSS_FROM_LIST(p_css_list);

		if (p_tmp_css == p_css)
		{
			found = SS7_TRUE; break;
		}
	}

	if (found)
	{
		*p_ecode = ESCCP_INVALID_CSS_ID;
		return SS7_FAILURE;
	}

/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if ( ! CSS_SPACE_EXISTS ())  /* Macro replace by value */
/*	if ( !((sccp_db.end_conc_ss_sp + SIZEOF_SP_ID_T) < (SIZEOF_SP_ID_T * MAX_SP + SIZEOF_SS_ID_T * MAX_CSS))) */
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
	{
		*p_ecode = ESCCP_DB_CSS_NO_SPACE;
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**        checks the config info for a concerned signaling point
******************************************************************************
**
**      DESCRIPTION :
**          checks that the subsystem and the signaling point are configured
**          and that the conc sp is not already configured as a concerned sp
**          for the subsystem
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_chk_csp_conf_info
#ifdef ANSI_PROTO
	(db_csp_info_t * p_csp_conf_info, error_t * p_ecode)
#else
	(p_csp_conf_info, p_ecode)
	 db_csp_info_t 	*p_csp_conf_info;
	 error_t 	*p_ecode;
#endif
{
	ss_entry_t * p_ss;
	sp_entry_t * p_sp, * p_csp, * p_tmp_csp;
	Boolean found;
	U8bit * p_csp_list;
	U32bit i;

	if ( ! IS_SSID_VALID(p_csp_conf_info->ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_ss = GET_SS_FROM_ID (p_csp_conf_info->ss_id);
	p_sp = GET_SP_FROM_ID (p_ss->sp_id);

	if ( ! IS_SS_CONFIGURED(p_ss))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_csp = GET_SP_FROM_ID (p_csp_conf_info->csp_id);

	if ( ! IS_SP_CONFIGURED(p_csp))
	{
		*p_ecode = ESCCP_INVALID_CSP_ID;
		return SS7_FAILURE;
	}

	/* Check that sp of the ss is not the same as the csp */
	if (p_sp == p_csp)
	{
		*p_ecode = ESCCP_INVALID_CSP_ID;
		return SS7_FAILURE;
	}

	/* Check that csp belongs to the same network as ss */
	if ( ! (p_sp->nw_id == p_csp->nw_id))
	{
		*p_ecode = ESCCP_INVALID_CSP_ID;
		return SS7_FAILURE;
	}

	/* Check that the csp_id is not already a csp of the ss */
	found = SS7_FALSE;
	p_csp_list = GET_CSP_LIST(p_ss);
	for (i=0; i < GET_NUM_CSP(p_ss); i++,
	     p_csp_list = GET_NEXT_CSP_FROM_LIST(p_csp_list))
	{
		p_tmp_csp = GET_CSP_FROM_LIST(p_csp_list);

		if (p_tmp_csp == p_csp)
		{
			found = SS7_TRUE; break;
		}
	}

	if (found)
	{
		return SS7_SUCCESS;
		/* Commented by Amaresh start as on dated 05-10-16 due to ADD CSP command also for timer Modify used so in found case return success */ 
#if 0
		*p_ecode = ESCCP_SP_IS_CSP;
		return SS7_FAILURE;
#endif /* Orig Code */
		/* Commented by Amaresh start as on dated 05-10-16 due to ADD CSP command also for timer Modify used so in found case return success */ 
	}

/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if ( ! CSP_SPACE_EXISTS ())  /* Macro replace by value */
/*	if ( !((sccp_db.end_conc_ss_sp + SIZEOF_SP_ID_T) < (SIZEOF_SP_ID_T * MAX_SP + SIZEOF_SS_ID_T * MAX_CSS)))*/
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
	{
		*p_ecode = ESCCP_DB_CSP_NO_SPACE;
		return SS7_FAILURE;
	}


	return SS7_SUCCESS;
}

#ifdef BACK_UP_SSN

return_t sccp_db_add_back_up_ss(U8bit ssn, pc_t point_code)
{
	SC_A_TRC (("ssn = %d, pc= %d\n", ssn, point_code));
	if(sccp_back_up_table[ssn].used == SS7_FALSE)
	{
		sccp_back_up_table[ssn].used = SS7_TRUE;
		sccp_back_up_table[ssn].ssn = ssn;
		sccp_back_up_table[ssn].point_code = point_code;
		SC_A_TRC (("DB:ADD_BACK_UP: REturning TRUE\n"));
		return SS7_SUCCESS;
	}
	else
	{
		SC_A_TRC (("DB:ADD_BACK_UP: REturning FALSE\n"));
		return SS7_FAILURE;
	}
}
	
void sccp_db_del_back_up_ss(U8bit ssn)
{
	sccp_back_up_table[ssn].used = SS7_FALSE;
}

return_t sccp_db_search_back_up_ss(U8bit ssn, pc_t *point_code)
{
	SC_A_TRC (("ssn = %d\n", ssn));
	if(sccp_back_up_table[ssn].used == SS7_TRUE)
	{
		*point_code = sccp_back_up_table[ssn].point_code;	
		SC_A_TRC (("pc = %d\n", *point_code));
		SC_A_TRC (("DB:SEARCH_BACK_UP: REturning TRUE\n"));
		return SS7_SUCCESS;
	}
	else
	{
		SC_A_TRC (("DB:SEARCH_BACK_UP: REturning FAILURE\n"));
		return SS7_FAILURE;
	}
}
#endif
