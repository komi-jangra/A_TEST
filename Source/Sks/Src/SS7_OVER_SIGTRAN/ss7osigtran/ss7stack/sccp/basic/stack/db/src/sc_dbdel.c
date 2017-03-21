/***************************************************************************
**  FILE NAME:
**      sc_dbdel.c
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
**  -------  ----------------  -------------   ----------------------------
**   3/6/98  Sriganesh. Kini  HSS:20800008	Original
**   17/7/02 Prateek Bidwalkar              Fixed SPR # 9285
**   08/8/02 Prateek Bidwalkar				Fixed SPR # 9502
**   17/10/03 Sunil Dahiya                  Fixed SPR # 13006
**  21/11/03 knaveen         				Fixed SPR # 13075
**  26/02/04 Hitesh Sharma         			Fixed SPR # 13263
**
**  Copyright 1998, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

/*****************************************************************************
**      FUNCTION :
**         deletes a signaling point
******************************************************************************
**
**      DESCRIPTION :
**         check that the signaling point is is configured. If subsystems
**         are present and del_ss is not set then SS7_FAILURE. if del_csp is not
**         set and sp exists as csp then SS7_FAILURE. Else all subsystems of this
**         sp are deleted and all instances of this sp as csp are also deleted
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_del_sp
#ifdef ANSI_PROTO
	(U32bit sp_id,
	 Boolean del_ss,
	 Boolean del_csp,
	 error_t *p_ecode)
#else
	(sp_id, del_ss, del_csp, p_ecode)
	 U32bit sp_id;
	 Boolean del_ss;
	 Boolean del_csp;
	 error_t * p_ecode;
#endif
{
	sp_entry_t * p_sp;

/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if ( ! IS_SPID_VALID(sp_id)) 
/*	if ( ! ((sp_id) < MAX_SP))	*/
/* Stop Spr 13075 Fix */
/* Stop Spr 13263 Fix */
	{
		*p_ecode = ESCCP_INVALID_SP_ID;
		return SS7_FAILURE;
	}

	p_sp = GET_SP_FROM_ID (sp_id);

	if ( ! IS_SP_CONFIGURED(p_sp))
	{
		return SS7_SUCCESS;
	}

	if ( (! del_ss) && (GET_NUM_SS_IN_SP(p_sp) > 0) )
	{
		*p_ecode = ESCCP_SS_DEFINED_FOR_SP;
		return SS7_FAILURE;
	}

	if ( (! del_csp) && sccp_db_is_sp_conc (p_sp))
	{
		*p_ecode = ESCCP_SP_IS_CSP;
		return SS7_FAILURE;
	}

	sccp_db_del_all_sp_as_csp (p_sp);
/* SPR # 9502 Fix Start */
	if(GET_ID_FROM_SP(p_sp) == (GET_SS_LIST_IN_SP(p_sp))->sp_id)
		sccp_db_del_all_ss_of_sp (p_sp);
/* SPR # 9502 Fix End */
	sccp_db_delete_sp_hash_list (p_sp);

	SET_SP_NOT_CONFIGURED(p_sp);

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**          deletes a subsystem
******************************************************************************
**
**      DESCRIPTION :
**          checks that this subsystem is configured. Also if del_css
**          is set then all instances of this ss as css is deleted.
**          if this ss has css or csp then SS7_FAILURE. Else delete this
**          subsystem as css and then delete this subsystem
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_del_ss
#ifdef ANSI_PROTO
	(U32bit ss_id,
	 Boolean del_css,
	 error_t *p_ecode)
#else
	(ss_id, del_css, p_ecode)
	 U32bit ss_id;
	 Boolean del_css;
	 error_t * p_ecode;
#endif
{
	ss_entry_t * p_ss;

	if ( ! IS_SSID_VALID(ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_ss = GET_SS_FROM_ID (ss_id);

	if ( ! IS_SS_CONFIGURED(p_ss))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	if ( (! del_css) && sccp_db_is_ss_conc(p_ss))
	{
		*p_ecode = ESCCP_SS_IS_CSS;
		return SS7_FAILURE;
	}

/* Start SPR 13006 Fix */
/* num_css may be 0 in a valid scenario */
#if 0
      if ((GET_NUM_CSS(p_ss) > 0) || (GET_NUM_CSP(p_ss) > 0))
	{
/* SPR # 9285 Fix Start */
		sccp_db_del_all_ss_as_css (p_ss);
       }
#endif
       sccp_db_del_all_ss_as_css (p_ss);
/* Stop SPR 13006 Fix */

	sccp_db_del_ss_from_sp (p_ss);
	SET_SS_NOT_CONFIGURED(p_ss);
        /*if ( IS_SS_LOCAL(p_ss) )
        SET_SS_NOT_REGISTERED(p_ss);*/
/* SPR # 9285 Fix End */

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**          deletes a concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**          checks if config info is valid. if valid deletes this concerned
**          subsystem from the list and adjusts indices of all other
**          conc sp list and conc ss list.
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_del_css
#ifdef ANSI_PROTO
	(db_css_info_t * p_css_del_info, error_t * p_ecode)
#else
	(p_css_del_info, p_ecode)
	 db_css_info_t 	*p_css_del_info; 
	 error_t 	*p_ecode;
#endif
{
	ss_entry_t * p_ss, * p_css, * p_tmp_css, * p_tmp_ss;
	U32bit i;
	U8bit * p_css_list;
	Boolean found;

	if ( ! IS_SSID_VALID(p_css_del_info->ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_ss = GET_SS_FROM_ID (p_css_del_info->ss_id);

	if ( ! IS_SS_CONFIGURED (p_ss))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	if ( ! IS_SSID_VALID(p_css_del_info->css_id))
	{
		*p_ecode = ESCCP_INVALID_CSS_ID;
		return SS7_FAILURE;
	}

	p_css = GET_SS_FROM_ID(p_css_del_info->css_id);

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

	if ( ! found)
	{
		*p_ecode = ESCCP_INVALID_CSS_ID;
		return SS7_FAILURE;
	}

	/* delete the css */
	sccp_memmove (p_css_list, p_css_list + SIZEOF_SS_ID_T,
	              END_OF_BYTE_ARRAY() - (p_css_list + SIZEOF_SS_ID_T));
	SET_NUM_CSS(p_ss, GET_NUM_CSS(p_ss) - 1);
	sccp_db.end_conc_ss_sp -= SIZEOF_SS_ID_T;

	/* Adjust the indices of all other ss */
	p_tmp_ss = GET_SS_FROM_ID (0);
	for (i=0; i < MAX_SS; i++, p_tmp_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_ss)) continue;

		if (p_tmp_ss == p_ss)
		{
			if ((GET_NUM_CSP(p_tmp_ss) > 0) &&
			    (GET_CSP_LIST(p_tmp_ss) > GET_CSS_LIST(p_ss)))
			{
				SET_CSP_LIST(p_tmp_ss,
				             GET_CSP_LIST(p_tmp_ss) - SIZEOF_SS_ID_T);
			}
			continue;
		}

		if ((GET_NUM_CSS(p_tmp_ss) > 0) &&
		    (GET_CSS_LIST(p_tmp_ss) > GET_CSS_LIST(p_ss)))
		{
			SET_CSS_LIST(p_tmp_ss,
			             GET_CSS_LIST(p_tmp_ss) - SIZEOF_SS_ID_T);
		}

		if ((GET_NUM_CSP(p_tmp_ss) > 0) &&
		    (GET_CSP_LIST(p_tmp_ss) > GET_CSS_LIST(p_ss)))
		{
			SET_CSP_LIST(p_tmp_ss,
			             GET_CSP_LIST(p_tmp_ss) - SIZEOF_SS_ID_T);
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**        deletes a concerned signaling point
******************************************************************************
**
**      DESCRIPTION :
**        checks config info. then deletes the csp from list and adjusts
**        the css_list and csp_list of all other subsystems
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_del_csp
#ifdef ANSI_PROTO
	(db_csp_info_t * p_csp_del_info, error_t * p_ecode)
#else
	(p_csp_del_info, p_ecode)
	 db_csp_info_t 	*p_csp_del_info;
	 error_t 	*p_ecode;
#endif
{
	ss_entry_t * p_ss, * p_tmp_ss;
	sp_entry_t * p_csp, * p_tmp_csp;
	U32bit i;
	U8bit * p_csp_list;
	Boolean found;

	if ( ! IS_SSID_VALID(p_csp_del_info->ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	p_ss = GET_SS_FROM_ID (p_csp_del_info->ss_id);

	if ( ! IS_SS_CONFIGURED (p_ss))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}
/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if ( ! IS_SPID_VALID(p_csp_del_info->csp_id)) 
/*	if ( ! ((p_csp_del_info->csp_id) < MAX_SP))	*/
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
	{
		*p_ecode = ESCCP_INVALID_CSP_ID;
		return SS7_FAILURE;
	}

	p_csp = GET_SP_FROM_ID(p_csp_del_info->csp_id);

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

	if ( ! found)
	{
		*p_ecode = ESCCP_INVALID_CSP_ID;
		return SS7_FAILURE;
	}

	/* delete the css */
	sccp_memmove (p_csp_list, p_csp_list + SIZEOF_SP_ID_T,
	              END_OF_BYTE_ARRAY() - (p_csp_list + SIZEOF_SP_ID_T));
	SET_NUM_CSP (p_ss, GET_NUM_CSP(p_ss) - 1);
	sccp_db.end_conc_ss_sp -= SIZEOF_SP_ID_T;

	/* Adjust the indices of all other ss */
	p_tmp_ss = GET_SS_FROM_ID (0);
	for (i=0; i < MAX_SS; i++, p_tmp_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_ss)) continue;

		if (p_tmp_ss == p_ss)
		{
			if ((GET_NUM_CSS(p_tmp_ss) > 0) &&
			    (GET_CSS_LIST(p_tmp_ss) > GET_CSP_LIST(p_ss)))
			{
				SET_CSS_LIST(p_tmp_ss,
			             GET_CSS_LIST(p_tmp_ss) - SIZEOF_SP_ID_T);
			}
			continue;
		}

		if ((GET_NUM_CSS(p_tmp_ss) > 0) &&
		    (GET_CSS_LIST(p_tmp_ss) > GET_CSP_LIST(p_ss)))
		{
			SET_CSS_LIST(p_tmp_ss,
			             GET_CSS_LIST(p_tmp_ss) - SIZEOF_SP_ID_T);
		}

		if ((GET_NUM_CSP(p_tmp_ss) > 0) &&
		    (GET_CSP_LIST(p_tmp_ss) > GET_CSP_LIST(p_ss)))
		{
			SET_CSP_LIST(p_tmp_ss,
			             GET_CSP_LIST(p_tmp_ss) - SIZEOF_SP_ID_T);
		}
	}

	return SS7_SUCCESS;
}

