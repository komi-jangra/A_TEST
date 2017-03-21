/***************************************************************************
**  FILE NAME:
**      sc_clbld.c
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
**  -------  ----------------  -----  -------------------------------------
**  29Jul2003 Sunil Dahiya                      Fixed SPR # 12291
**  10aor2002 Salil Agrawal                     Fixed SPR # 8530
**  22Apr2000 Ramu Kandula                      Fixed SPR # 3094
**  25Mar2000 Ramu Kandula                      Fixed SPR # 3002
**  09Mar2000 Ramu Kandula                      Fixed SPR # 2866
**  24Feb2000 Ramu Kandula                      Fixed SPR # 2731
**  06Aug'98 Anil K.							Connectionless ANSI Added
**  15May98  Sriganesh. Kini   ITU-714/713  	Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/


#include "sc_stgl.h"

/*****************************************************************************
**      FUNCTION :
**         builds the N UNITDATA indication API
******************************************************************************
**
**      DESCRIPTION :
**         calculates length of buf reqd, allocates, encodes and calls
**         sccp_sendto_tc 
**
**      NOTE :
**
*****************************************************************************/

void
sccp_build_n_unitdata_ind_api
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t * p_info;
#endif
{
	U16bit api_len;
	U8bit * p_api, * p_elem, num_elem, * p_len_byte;

	SC_A_TRC (("SCCP::SCLC: building unitdata indication\n"));

	num_elem = SCCP_N_UNITDATA_IND_MIN_NELEM;
	api_len = API_HEADER_LEN;

	/** SPR #3094 Fix Start **/
	/* If the clg addr does not contain a GT and PC is not present, 
	** then insert the OPC from the into clg addr 
	*/
	if ( !(p_info->cg_addr.gti) && !(p_info->cg_addr.pc_ind))
	{
		p_info->cg_addr.pc_ind = SS7_TRUE;
		p_info->cg_addr.pc = p_info->opc;
	}
	/** SPR #3094 Fix End **/

	/* mandatory variable elem length */
	api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_info->cd_addr);
	api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_info->cg_addr);
	api_len += SCCP_ELEM_LEN_LEN + p_info->data.len;

	/* optional elem lengths */
	/* return option */
	if (p_info->proto_class & RET_OPTN_MASK)
	{
		num_elem++;
		api_len += ONE_BYTE_OPT_ELEM_SIZE;
	}

	/* seq control */
	if (p_info->proto_class & 0x1)
	{
		num_elem++;
		api_len += ONE_BYTE_OPT_ELEM_SIZE;
	}

	/* importance */
	/* SPR # 2731 Fix Start */
/*
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI)
*/
	{
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			num_elem++;
			api_len += ONE_BYTE_OPT_ELEM_SIZE;
		}
	}
/* #endif */
	/* SPR # 2731 Fix End */

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			num_elem++;
			api_len += SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN +
			           p_info->isni.len;
		}
	}
#endif

	if (SS7_NULL == (p_api = sccp_malloc (api_len)))
	{
		SC_A_TRC (("SCCP::SCLC: cannot send unitdata ind\n"));
		return;
	}

	sccp_fill_api_header (p_api, SCCP_N_UNITDATA_INDICATION,
	                      num_elem, api_len);

	p_elem = p_api + API_HEADER_LEN;

	p_len_byte = p_elem;
	p_elem = sccp_encode_sccp_addr (p_elem+1, &p_info->cd_addr);
	*p_len_byte = *(p_len_byte + 1);
	*(p_len_byte + 1) = 0;

	p_len_byte = p_elem;
	p_elem = sccp_encode_sccp_addr (p_elem+1, &p_info->cg_addr);
	*p_len_byte = *(p_len_byte + 1);
	*(p_len_byte + 1) = 0;

	PUT_2_BYTE_LE(p_elem, p_info->data.len);
	p_elem += SCCP_ELEM_LEN_LEN;
	sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);
	p_elem += p_info->data.len;

	/* return option */
	if (p_info->proto_class & RET_OPTN_MASK)
	{
		*p_elem++ = SCCP_ELEM_RETURN_OPTION;
		PUT_2_BYTE_LE(p_elem, SCCP_ELEM_RETURN_OPTION_LEN);
		p_elem += SCCP_ELEM_LEN_LEN;
		*p_elem++ = SCCP_RETURN_MSG;
	}

	/* seq control */
	if (p_info->proto_class & 0x1)
	{
		*p_elem++ = SCCP_ELEM_SEQUENCE_CONTROL;
		PUT_2_BYTE_LE(p_elem, SCCP_ELEM_SEQ_CONTROL_LEN);
		p_elem += SCCP_ELEM_LEN_LEN;
		*p_elem++ = p_info->sls;
	}

	/* importance */
	/* SPR # 2731 Fix Start */
/*
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI)
*/
	{
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			*p_elem++ = SCCP_ELEM_IMPORTANCE;
			PUT_2_BYTE_LE(p_elem, SCCP_ELEM_IMPORTANCE_LEN);
			p_elem += SCCP_ELEM_LEN_LEN;
			*p_elem++ = p_info->importance;
		}
	}
/* #endif */
	/* SPR # 2731 Fix End */

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			*p_elem++ = SCCP_ELEM_ISNI;
			PUT_2_BYTE_LE(p_elem, p_info->isni.len);
			p_elem += SCCP_ELEM_LEN_LEN;
			sccp_memcpy(p_elem, p_info->isni.list, p_info->isni.len);
			p_elem += p_info->isni.len;
		}
	}
#endif

	SC_A_TRC (("SCCP:SCLC: built unitdata indication\n"));
	
	sccp_sendto_tc (p_api, p_info->p_ss);
}

/*****************************************************************************
**      FUNCTION :
**         builds the n-notice indication api
******************************************************************************
**
**      DESCRIPTION :
**         calculates length of buf reqd, allocates, encodes and calls
**         sccp_sendto_tc 
**
**      NOTE :
**
*****************************************************************************/

void
sccp_build_n_notice_ind_api
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t *p_info;
#endif
{

	U16bit api_len;
	U8bit * p_api, * p_elem, num_elem, * p_len_byte;

        /* Start SPR 12291 Fix */
#if defined GTT_CALLING_CHANGES
        if ((SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api)) && (p_info->cg_addr.gti))
        {
	    /* Don't send the n_notice_ind if responding to unitdata request with
               ROUTE_ON_GT in the calling party
                  */
           SC_A_TRC (("SCCP:SCLC: discarding n-notice indication\n")); 
           return;	
        }
#endif
		/* Stop SPR 12291 Fix */

        SC_A_TRC (("SCCP:SCLC: building n-notice indication\n")); 
	
	/** SPR # 3002 Fix Start **/
	/* If the calling addr is a GT, then mark the SSN and PC indicators as 
	** present; These fields were already filled while parsing the 
	** N-Unitdata request 
	*/
	if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
	{
		if (p_info->cg_addr.gti)
		{
			p_info->cg_addr.pc_ind = SS7_TRUE;
			p_info->cg_addr.ssn_ind = SS7_TRUE;
		}
	}
	/** SPR # 3002 Fix End **/

	/** SPR # 3094 Fix Start **/
	if (MTP3_UP_TRANSFER_INDICATION == GET_API_ID(p_info->p_api))
	{
		/* If the clg addr does not contain a GT and PC is not present, 
		** then insert the OPC from the into clg addr 
		*/
		if ( !(p_info->cg_addr.gti) && !(p_info->cg_addr.pc_ind))
		{
			p_info->cg_addr.pc_ind = SS7_TRUE;
			p_info->cg_addr.pc = p_info->opc;
		}
	}
	/** SPR # 3094 Fix End **/

	num_elem = SCCP_N_NOTICE_IND_MIN_NELEM;
	api_len = API_HEADER_LEN;
	api_len += SCCP_ELEM_REASON_FOR_RETURN_LEN;
	api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_info->cd_addr);
	api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_info->cg_addr);
	api_len += SCCP_ELEM_LEN_LEN + p_info->data.len;

    /* spr # 8530 fix starts */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {	
        U8bit msg_importance; 
        U8bit default_msg_importance, max_msg_importance; 

        default_msg_importance = sccp_get_min_message_priority(p_info->msg_type);
        max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
        msg_importance =  default_msg_importance ;

        if (IS_IMPORTANCE_PRESENT(p_info))
        {
            if (p_info->importance > max_msg_importance)
                p_info->importance = max_msg_importance;
        }
        else
        {
            p_info->importance = msg_importance;
            SET_IMPORTANCE_PRESENT(p_info); 
        }
    }
#endif
    /* spr # 8530 fix ends*/
    
	/* imp */
	/* SPR # 2731 Fix Start */
/*
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI)
*/
	{
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			num_elem++;
			api_len += ONE_BYTE_OPT_ELEM_SIZE;
		}
	}
/* #endif */
	/* SPR # 2731 Fix End */

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			num_elem++;
			api_len += SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN +
			           p_info->isni.len;
		}
	}
#endif

	if (SS7_NULL == (p_api = sccp_malloc (api_len)))
	{
		SC_A_TRC (("SCCP::SCLC: cannot send notice ind\n"));
		return;
	}

	sccp_fill_api_header (p_api, SCCP_N_NOTICE_INDICATION,
	                      num_elem, api_len);

	p_elem = p_api + API_HEADER_LEN;

	*p_elem++ = p_info->ret_cause;

	/** Fixed SPR # 2866 Start **/
	if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
	{
		/** Routing Failed for N-UNITDATA_Req ;
		*** cld addr and clg addr must be swapped 
		**/

		/* cld addr */
		p_len_byte = p_elem;
		p_elem = sccp_encode_sccp_addr ((p_elem+1), &p_info->cg_addr);
		*p_len_byte = *(p_len_byte + 1);
		*(++p_len_byte) = 0;
	
		/* clg addr */
		p_len_byte = p_elem;
		p_elem = sccp_encode_sccp_addr ((p_elem+1), &p_info->cd_addr);
		*p_len_byte = *(p_len_byte + 1);
		*(++p_len_byte) = 0;

		p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cg_addr.pc);
		if(p_info->p_sp)
		{
			p_info->p_ss = sccp_db_find_ss (p_info->p_sp, p_info->cg_addr.ssn);
		}
		else
		{
			SC_A_TRC (("SCCP:SCLC: Memory allocation Failed\n"));
		    sccp_free(p_api);
			return;
		}
	}
	else
	{
		/** UDTS or XUDTS received from MTP3 **/
		/* cld addr */
		p_len_byte = p_elem;
		p_elem = sccp_encode_sccp_addr ((p_elem+1), &p_info->cd_addr);
		*p_len_byte = *(p_len_byte + 1);
		*(++p_len_byte) = 0;
	
		/* clg addr */
		p_len_byte = p_elem;
		p_elem = sccp_encode_sccp_addr ((p_elem+1), &p_info->cg_addr);
		*p_len_byte = *(p_len_byte + 1);
		*(++p_len_byte) = 0;
	}
	/** Fixed SPR # 2866 End **/

	PUT_2_BYTE_LE(p_elem, p_info->data.len);
	p_elem += SCCP_ELEM_LEN_LEN;
	sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);
	p_elem += p_info->data.len;

	/* importance */
	/* SPR # 2731 Fix Start */
/*
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI)
*/
	{
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			*p_elem++ = SCCP_ELEM_IMPORTANCE;
			PUT_2_BYTE_LE(p_elem, SCCP_ELEM_IMPORTANCE_LEN);
			p_elem += SCCP_ELEM_LEN_LEN;
			*p_elem++ = p_info->importance;
		}
	}
/* #endif */
	/* SPR # 2731 Fix End */

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			*p_elem++ = SCCP_ELEM_ISNI;
			PUT_2_BYTE_LE(p_elem, p_info->isni.len);
			p_elem += SCCP_ELEM_LEN_LEN;
			sccp_memcpy(p_elem, p_info->isni.list, p_info->isni.len);
			p_elem += p_info->isni.len;
		}
	}
#endif

	SC_A_TRC (("SCCP:SCLC: built n-notice indication\n"));

	if(p_info->p_ss)
	sccp_sendto_tc (p_api, p_info->p_ss);
	else 
	{
		SC_A_TRC (("SCCP:SCLC: Memory allocation failed\n"));
		sccp_free(p_api);	
		return;
	}
}
