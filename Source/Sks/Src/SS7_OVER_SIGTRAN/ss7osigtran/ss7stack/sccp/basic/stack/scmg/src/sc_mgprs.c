/***************************************************************************
**
**  FILE NAME:
**      sc_bcast.c
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
**  18Jun2002 Suyash Tripathi         Fixed SPR # 8985
**  29Feb2000 Ramu Kandula            Fixed SPR # 2692
**  18June'99 Sudipta Pattar	      Added code for GR
**           Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#include "sc_bcast.h"

#ifdef BACK_UP_SSN
return_t sccp_parse_n_coord_req_api (U8bit *p_api, scmg_info_t 	*p_info);
return_t sccp_parse_n_coord_response_api(U8bit	*p_api, scmg_info_t *p_info);
#endif

/***************************************************************************
**
**      FUNCTION :
**        parses n_state request api
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_n_state_req_api 
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info)
#else
	(p_api, p_info)
	U8bit 		* p_api ;
	scmg_info_t 	* p_info ;
#endif
{
	U8bit * p_elem = p_api + API_HEADER_LEN;
	extern sp_entry_t sccp_local_sp; /** For SPR # 2692 Fix **/

	SC_A_TRC (("SCCP::SCMG: parsing N-state ind\n"));

#if 0
	p_info->nw_id = *p_elem;
	p_elem += SCCP_ELEM_NW_ID_LEN;
#endif
	p_info->nw_id = DEFAULT_NW_ID;
	p_info->pc = GET_PC(p_elem);
	p_elem += PC_SIZE;
	p_info->ssn = *p_elem; p_elem++;
	p_info->status = *p_elem;

	/** SPR # 2692 Fix Start **/
	p_info->informing_pc = sccp_local_sp.pc;
	/** SPR # 2692 Fix End **/

	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**        parses n_coord request api
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

#ifdef BACK_UP_SSN
return_t 
sccp_parse_n_coord_req_api 
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info)
#else
	(p_api, p_info)
	U8bit 		* p_api ;
	scmg_info_t 	* p_info ;
#endif
{
	U8bit * p_elem = p_api + API_HEADER_LEN;
	extern sp_entry_t sccp_local_sp; /** For SPR # 2692 Fix **/

	SC_A_TRC (("SCCP::SCMG: parsing N-coord req\n"));

	p_info->nw_id = DEFAULT_NW_ID;
	p_info->pc = GET_PC(p_elem);
	p_elem += PC_SIZE;
	p_info->ssn = *p_elem; p_elem++;
	p_info->ss_mult_ind = *p_elem;

	p_info->informing_pc = sccp_local_sp.pc;
	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**        parses n_coord response api
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_n_coord_response_api 
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info)
#else
	(p_api, p_info)
	U8bit 		* p_api ;
	scmg_info_t 	* p_info ;
#endif
{
	U8bit * p_elem = p_api + API_HEADER_LEN;
	extern sp_entry_t sccp_local_sp; /** For SPR # 2692 Fix **/

	SC_A_TRC (("SCCP::SCMG: parsing N-coord RESPONSE\n"));

	p_info->nw_id = DEFAULT_NW_ID;
	p_info->pc = GET_PC(p_elem);
	p_elem += PC_SIZE;
	p_info->ssn = *p_elem; p_elem++;
	p_info->ss_mult_ind = *p_elem;

	p_info->informing_pc = sccp_local_sp.pc;
	return SS7_SUCCESS;
}

#endif


/***************************************************************************
**
**      FUNCTION :
**        parses MTP3 pause indication
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_m3_pause_ind_api
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info, 
	 error_t 	* p_ecode)
#else
	(p_api, p_info, p_ecode)
	U8bit          * p_api ;
	scmg_info_t    * p_info ;
	error_t        * p_ecode ;
#endif
{
	U8bit * p_elem = p_api + API_HEADER_LEN;

	SC_A_TRC (("SCCP::SCMG: parsing  pause ind\n"));

	if (GET_API_LEN(p_api) < MTP3_LEN_UP_PAUSE_INDICATION)
	{
		*p_ecode = ESS7_INVALID_LENGTH;
		return SS7_FAILURE;
	}

	if ( ! (GET_API_NELEM(p_api) == MTP3_NUM_ELEM_UP_PAUSE_INDICATION))
	{
		*p_ecode = ESS7_INVALID_NUM_API_ELEMENTS;
		return SS7_FAILURE;
	}

#if 0
	p_info->nw_id = *p_elem;
	p_elem += SCCP_ELEM_NW_ID_LEN;
#endif
	p_info->nw_id = DEFAULT_NW_ID;
	p_info->pc = GET_PC(p_elem);

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses MTP3 resume indication 
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_m3_resume_ind_api
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info, 
	 error_t 	* p_ecode)
#else
	(p_api, p_info, p_ecode)
	U8bit          * p_api ;
	scmg_info_t    * p_info ;
	error_t        * p_ecode ;
#endif
{
	U8bit * p_elem = p_api + API_HEADER_LEN;

	SC_A_TRC (("SCCP::SCMG: parsing  resume req\n"));

	if (GET_API_LEN(p_api) < MTP3_LEN_UP_RESUME_INDICATION)
	{
		SC_A_TRC (("SCCP::SCMG: invalid len %d\n", 
			GET_API_LEN(p_api)));
		*p_ecode = ESS7_INVALID_LENGTH;
		return SS7_FAILURE;
	}

	if ( ! (GET_API_NELEM(p_api) == MTP3_NUM_ELEM_UP_RESUME_INDICATION))
	{
		SC_A_TRC (("SCCP::SCMG: num elem %d invalid\n", 
			GET_API_NELEM(p_api)));
		*p_ecode = ESS7_INVALID_NUM_API_ELEMENTS;
		return SS7_FAILURE;
	}

#if 0
	p_info->nw_id = *p_elem;
	p_elem += SCCP_ELEM_NW_ID_LEN;
#endif
	p_info->nw_id = DEFAULT_NW_ID;
	p_info->pc = GET_PC(p_elem);

	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**        parses MTP3 status indication
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_m3_status_ind_api
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info, 
	 error_t 	* p_ecode)
#else
	(p_api, p_info, p_ecode)
	U8bit          * p_api ;
	scmg_info_t    * p_info ;
	error_t        * p_ecode ;
#endif
{
	U8bit * p_elem = p_api + API_HEADER_LEN;

	SC_A_TRC (("SCCP::SCMG: parsing  status ind\n"));

	if (GET_API_LEN(p_api) < MTP3_LEN_UP_STATUS_INDICATION)
	{
		SC_A_TRC (("SCCP::SCMG: len %d invalid\n", 
			GET_API_LEN(p_api)));
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return SS7_FAILURE;
	}

	if ( ! (GET_API_NELEM(p_api) == MTP3_NUM_ELEM_UP_STATUS_INDICATION))
	{
		SC_A_TRC (("SCCP::SCMG: num elem %d invalid\n", 
			GET_API_NELEM(p_api)));
		*p_ecode = ESS7_INVALID_NUM_API_ELEMENTS;
		return SS7_FAILURE;
	}

#if 0
	p_info->nw_id = *p_elem;
	p_elem += SCCP_ELEM_NW_ID_LEN;
#endif

	p_info->nw_id = DEFAULT_NW_ID;

	p_info->cause = *p_elem & MTP3_CAUSE_MASK;
	p_elem += MTP3_LENGTH_CAUSE;

	p_info->pc = GET_PC(p_elem);
	p_elem += PC_SIZE;

/* SPR 8985 - Fix Start */
	/*p_info->cong_level = *p_elem & MTP3_CONG_LEVEL_MASK; */
	p_info->cong_level = *p_elem & SCCP_MTP3_CONG_LEVEL_MASK;
/* SPR 8985 - Fix End  */

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**           parses the user register API
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_sccp_reg_api 
#ifdef ANSI_PROTO
	(U8bit 		* p_api, 
	 scmg_info_t 	* p_info)
#else
	(p_api, p_info)
	U8bit          * p_api ;
	scmg_info_t    * p_info ;
#endif
{
	U8bit * p_elem;

	p_elem = p_api + API_HEADER_LEN;

#if 0
	p_info->nw_id = *p_elem++;
#endif
	p_info->nw_id = DEFAULT_NW_ID;

	p_info->pc = GET_PC(p_elem);
	p_elem += PC_SIZE;
	p_info->ssn = *p_elem++;
	p_info->uid = GET_2_BYTE_LE(p_elem);
/* Added by Amaresh start for set userId in Register message having ssn 32 specially for EMAP */
	if (p_info->ssn == 0x20)
	{
			p_info->uid = 0x04;
	}
/* Added by Amaresh stop for set userId in Register message having ssn 32 specially for EMAP */

	return SS7_SUCCESS;
}


/* GR changes: start */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)

/***************************************************************************
**
**      FUNCTION :
**        parses MTP3 pause cluster indication
****************************************************************************
*
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_m3_pause_cluster_ind_api
#ifdef ANSI_PROTO
        (U8bit          * p_api, 
         scmg_info_t    * p_info, 
         error_t        * p_ecode)
#else
        (p_api, p_info, p_ecode)
        U8bit          * p_api ;
        scmg_info_t    * p_info ;
        error_t        * p_ecode ;
#endif
{
        U8bit * p_elem = p_api + API_HEADER_LEN;

        SC_A_TRC (("SCCP::SCMG: parsing  pause cluster indication\n"));

        if (GET_API_LEN(p_api) != MTP3_LEN_UP_PAUSE_CLUSTER_INDICATION)
        {
                SC_A_TRC (("SCCP::SCMG: invalid len %d\n", 
                        GET_API_LEN(p_api)));
                *p_ecode = ESS7_INVALID_LENGTH;
                return SS7_FAILURE;
        }

        /* number of elements in this API will be the same as that of
         * the regular pause API 
         */
        if ( ! (GET_API_NELEM(p_api) == MTP3_ANSI_NUM_ELEM_UP_CLUSTER_PAUSE_IND))
        {
                SC_A_TRC (("SCCP::SCMG: num elem %d invalid\n", 
                        GET_API_NELEM(p_api)));
                *p_ecode = ESS7_INVALID_NUM_API_ELEMENTS;
                return SS7_FAILURE;
        }

#if 0
        p_info->nw_id = *p_elem;
        p_elem += SCCP_ELEM_NW_ID_LEN;
#endif
        p_info->nw_id = DEFAULT_NW_ID;
		/* SPR 10855 - Fix Start */
        p_elem += SCCP_ELEM_NW_ID_LEN;
		/* SPR 10855 - Fix End   */
        p_info->cluster = GET_CLUSTER(p_elem);

        return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses MTP3 resume cluster indication 
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_m3_resume_cluster_ind_api
#ifdef ANSI_PROTO
        (U8bit          * p_api, 
         scmg_info_t    * p_info, 
         error_t        * p_ecode)
#else
        (p_api, p_info, p_ecode)
        U8bit          * p_api ;
        scmg_info_t    * p_info ;
        error_t        * p_ecode ;
#endif
{
        U8bit * p_elem = p_api + API_HEADER_LEN;

        SC_A_TRC (("SCCP::SCMG: parsing  resume cluster indication\n"));

        if (GET_API_LEN(p_api) != MTP3_LEN_UP_RESUME_CLUSTER_INDICATION)
        {
                SC_A_TRC (("SCCP::SCMG: invalid len %d\n", 
                        GET_API_LEN(p_api)));
                *p_ecode = ESS7_INVALID_LENGTH;
                return SS7_FAILURE;
        }

        /* number of elements in this API will be the same as that of
         * the regular resume API 
         */
        if ( ! (GET_API_NELEM(p_api) == MTP3_ANSI_NUM_ELEM_UP_CLUSTER_RESUME_IND))
        {
                SC_A_TRC (("SCCP::SCMG: num elem %d invalid\n", 
                        GET_API_NELEM(p_api)));
                *p_ecode = ESS7_INVALID_NUM_API_ELEMENTS;
                return SS7_FAILURE;
        }

#if 0
        p_info->nw_id = *p_elem;
        p_elem += SCCP_ELEM_NW_ID_LEN;
#endif
        p_info->nw_id = DEFAULT_NW_ID;
		/* SPR 10855 - Fix Start */
        p_elem += SCCP_ELEM_NW_ID_LEN;
		/* SPR 10855 - Fix End   */
        p_info->cluster = GET_CLUSTER(p_elem);

        return SS7_SUCCESS;
}
#endif		/* SCCP_ANSI || SCCP_BCGR */
/* GR changes: End */

