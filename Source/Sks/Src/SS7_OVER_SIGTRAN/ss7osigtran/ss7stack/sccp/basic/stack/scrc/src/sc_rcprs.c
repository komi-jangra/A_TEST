/***************************************************************************
**
**  FILE NAME:
**      sc_rcprs.c
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
**  21Nov2003 Hitesh Sharma           Fixed SPR 12557
**  21Nov2003 Hitesh Sharma           Fixed SPR 12556
**  20Nov2003 Hitesh Sharma           Fixed SPR 12555
**  20Nov2003 Hitesh Sharma           Fixed SPR 12553
**  08Sep2003 Salil Agrawal           Fixed SPR 12319
**  08Sep2003 Salil Agrawal           Fixed SPR 12322
**  08Sep2003 Salil Agrawal           Fixed SPR 12324
**  08Sep2003 Salil Agrawal           Fixed SPR 12499
**  21Nov2002 Ashish Sawalkar         Fixed SPR 10694
**  13Nov2002 Ashish Sawalkar         Fixed SPR IMP_SPR
**  14Oct2002 Ashish Sawalkar         Fixed SPR 10322
**  16Oct2002 Suyash Tripathi         Fixed SPR 9933 
**  24Jul2002 Salil Agrawal           Fixed SPR 9341 
**  03Apr2002 Salil Agrawal           fixed SPR 8530 
**  04Mar2002 Sachin Bhatia           fixed SPR 8554 
**  11Oct2000 Ramu Kandula            Added Broadband functionality - 
**                                    parsing functions for LUDT, LUDTS
**  21Jul2000 Ramu Kandula            Fixed SPR # 3825 
**  09Jun2000 Ramu Kandula            Fixed SPR # 2579 
**  07Jun2000 Ramu Kandula            Fixed SPR # 2613 
**  05Jun2000 Ramu Kandula            Fixed SPR # 3683 
**  10Mar2000 Ramu kandula            Fixed SPR # 2665
**  07Mar2000 Ramu kandula            Fixed SPR # 2731
**  29Feb2000 Ramu kandula            Fixed SPR # 2776
**  23Feb2000 Ramu kandula            Cancelled the fix for SPR # 2591
**  23Feb2000 Ramu Kandula            Fixed SPR 2663
**  16Feb2000 Ramu Kandula            Fixed SPR 2615
**  14Feb2000 Ramu Kandula            Fixed SPR 2604
**  11Feb2000 Ramu Kandula            Fixed SPR 2591 
**  03Sep'99 Sudipta Pattar    -----  Fixed SPR 1771
**  03Sep'99 Sudipta Pattar    -----  Fixed SPR 1768
**  29Apr'99 Sudipta Pattar    -----  Fixed SPR 1496
**  19Feb'99 Sudipta Pattar    -----  Fixed SPR 1347
**  17Feb'99 Sudipta Pattar    -----  Fixed SPR 1346
**  17Feb'99 Sudipta Pattar    -----  Fixed SPR 1345
**  15Feb'99 Sudipta Pattar    -----  Fixed SPR 1323
**  15Feb'99 Sudipta Pattar    -----  Fixed SPR 1289
**  07Feb'99 Sudipta Pattar    -----  Added Ericsson changes
**  12May'98 Sriganesh. Kini   -----  Original
**  25july 2001 Rajesh Mehta   -----  Fixed SPR 5746
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

static return_t sccp_parse_udt
	_ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_udts
	_ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_xudt
	_ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_xudts
	_ARGS_ ((msg_info_t * p_info));

#ifdef SCCP_BROADBAND
static return_t sccp_parse_ludt
	_ARGS_ ((msg_info_t * p_info));
 
static return_t sccp_parse_ludts
	_ARGS_ ((msg_info_t * p_info));
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
static return_t sccp_parse_cr
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_cc
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_cref
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_rlsd
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_rlc
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_err
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_it
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_dt1
  _ARGS_ ((msg_info_t * p_info));

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

static return_t sccp_parse_ak
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_ed
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_ea
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_rsr
  _ARGS_ ((msg_info_t * p_info));

static return_t sccp_parse_rsc
  _ARGS_ ((msg_info_t * p_info));

#endif
#endif

static return_t sccp_decode_proto_class
	_ARGS_ ((msg_info_t * p_info));

/***************************************************************************
**
**      FUNCTION :
**        parses transfer indication API from MTP3
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_m3_transfer_ind_api 
#ifdef ANSI_PROTO
	(U8bit * p_api, msg_info_t * p_info, error_t * p_ecode)
#else
	(p_api, p_info, p_ecode)
	U8bit * p_api ;
	msg_info_t * p_info ;	
	error_t * p_ecode ;
#endif
{
	U8bit * p_elem;
	U16bit api_len;

	p_info->flag = 0;
	p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

	api_len = GET_API_LEN(p_api);

#ifdef SCCP_BROADBAND 
	if (sc_opt.nw_type == SS7_BROADBAND_NETWORK)
	{
		if ((api_len < (API_HEADER_LEN + MTP3_MIN_USER_DATA)) || 
	    	(api_len > (API_HEADER_LEN + MTP3_MAX_USER_DATA_FOR_BROADBAND)))
		{
			SC_A_TRC (("SCCP::SCRC: invalid len %d\n", api_len));
				*p_ecode = ESS7_INVALID_LENGTH;
			return SS7_FAILURE;
		}
	}
	else
#endif
	{
        /* spr #8530 starts - because pointer to optional field is 2 byte now*/
		/* SPR# IMP_SPR : Reverting SPR 8530 Change */
        
		if ((api_len < (API_HEADER_LEN + MTP3_MIN_USER_DATA)) || 
	    	(api_len > (API_HEADER_LEN + MTP3_MAX_USER_DATA)))
            
        /* spr #8530 ends*/
            
		{
			SC_A_TRC (("SCCP::SCRC: invalid len %d\n", api_len));
				*p_ecode = ESS7_INVALID_LENGTH;
			return SS7_FAILURE;
		}
	}

	if ( ! (MTP3_NUM_ELEM_UP_TRANSFER_INDICATION == GET_API_NELEM(p_api)))
	{
		SC_A_TRC (("SCCP::SCRC: invalid num elem %d\n", 
		           GET_API_NELEM(p_api)));
		*p_ecode = ESS7_INVALID_NUM_API_ELEMENTS;
		return SS7_FAILURE;
	}

	p_elem = p_api + API_HEADER_LEN;
	p_info->p_api = p_api;

	p_info->nw_id = DEFAULT_NW_ID;
#if 0
	p_info->nw_id = *p_elem++;
	p_elem += SCCP_ELEM_NW_ID_LEN;
#endif

	/* extract the sio (si + ssf) field */
	p_info->sio.si  = (*p_elem) & 0x0f;
	/** SPR # 2731 Fix Start **/
	p_info->sio.ssf = ((*p_elem) >> 4) & 0x0c;  /*  bits 1 & 2 of ssf are not 
												**	used in ITU and contain the 												**  msg priority in ANSI/BCGR 
												*/
/* SPR 10847 - Fix Start */
/* No Need to look for imp parameter in ANSI & BCGR */
#if 0
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
	/** SPR# 10694 Fix **/
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		p_info->importance = ((*p_elem) >> 4) & 0x03;
		SET_IMPORTANCE_PRESENT(p_info);
	}
#endif
#endif
/* SPR 10847 - Fix End   */
	/** SPR # 2731 Fix End **/
	p_elem += MTP3_LENGTH_SIO;
/* start spr # 9341 */
#ifdef SCCP_CHINESE
	if(COMPARE_CHINESE)
	{
		p_info->dpc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->opc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->sls = *p_elem++;
	}
#endif 
/* #else */

#if  defined(SCCP_ITU) || defined(SCCP_ETSI)
	if ((COMPARE_ITU) || (COMPARE_ETSI))
	{
		p_info->dpc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->opc = (p_elem[-1] >> 6) | (p_elem[0] << 2) |
		              ((p_elem[1] & 0xf) << 10);
		p_elem ++;
		p_info->sls = *p_elem >> 4;
		p_elem++;
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR) 
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		p_info->dpc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->opc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->sls = (*p_elem) % 16;  /* Converting sls to 4 bit value */
		p_elem++;
	}
#endif
#ifdef SCCP_JAPANESE
	if (COMPARE_JAPANESE)
	{
		p_info->dpc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->opc = GET_PC(p_elem);
		p_elem += PC_SIZE;
		p_info->sls = *p_elem++;

		/* we would require only the last 4 bits of this byte */
		/* SPR # 8554 Fix Starts */
		p_info->sls = p_info->sls & 0x0f;
		/* DPR # 8554 Fix Ends */
	}
#endif
/* #endif */
/* end of spr # 9341 */

	/* Check validity of route label */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,
	             p_info->opc)))
	{
		SC_A_TRC (("SCCP::SCRC: M3 OPC %u on nw %d unknown to SCCP\n",
		           p_info->opc, p_info->nw_id));
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return SS7_FAILURE;
	}

	/* Check validity of route label */
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,
	             p_info->dpc)))
	{
		SC_A_TRC (("SCCP::SCRC: M3 DPC %u on nw %d unknown to SCCP\n",
		           p_info->dpc, p_info->nw_id));
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return SS7_FAILURE;
	}

	if (! p_info->p_sp->local)
	{
		SC_A_TRC (("SCCP::SCRC: M3 DPC %d on nw %d not configured as"
		           " local in SCCP\n", p_info->dpc, p_info->nw_id));
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return SS7_FAILURE;
	}

	/* extract Data */
	p_info->m3_data.len = (U16bit)(&p_api[api_len] - p_elem);
	p_info->m3_data.p = p_elem;

	RC_TRC (("SCCP::SCRC: M3 msg nw %d si %d ssf %d dpc %u opc %u sls %d"
	           " data len %d\n",
	           p_info->nw_id, p_info->sio.si, p_info->sio.ssf,
	           p_info->dpc, p_info->opc, p_info->sls, p_info->m3_data.len));

	if ( ! (SCCP_SI == p_info->sio.si))
	{
		SC_A_TRC (("SCCP::SCRC: invalid service indicator %d\n", p_info->sio.si));
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return SS7_FAILURE;
	}

	if ( ! (p_info->sio.ssf == p_info->p_sp->ssf))
	{
		SC_A_TRC (("SCCP::SCRC: invalid sub service indicator %d\n",
		           p_info->sio.ssf));
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**           Parses the message from the network
**
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_nw_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	return_t ret_val;
	U8bit  min_msg_priority, max_msg_priority; /* used for SPR # 3825 fix */
	U8bit  scmg_msg_type; /* used for SPR # 3825 fix */

	p_info->msg_type = p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];

	switch (p_info->msg_type)
	{
		case UDT_MSG_TYPE:
			ret_val = sccp_parse_udt (p_info);
			break;

		case UDTS_MSG_TYPE:
			ret_val = sccp_parse_udts (p_info);
			break;

		case XUDT_MSG_TYPE:
			ret_val = sccp_parse_xudt (p_info);
			break;

		case XUDTS_MSG_TYPE:
			ret_val = sccp_parse_xudts (p_info);
			break;

#ifdef SCCP_BROADBAND
		case LUDT_MSG_TYPE:
			if (sc_opt.nw_type != SS7_BROADBAND_NETWORK) 
			{
				SC_P_TRC (("SCCP::SCRC: unsupported msg type %d\n", 
					p_info->msg_type));
				ret_val = SS7_FAILURE;
				return ret_val;
			}
			else
			{
				ret_val = sccp_parse_ludt (p_info);
				break;
			}
			break;
		
		case LUDTS_MSG_TYPE:
			if (sc_opt.nw_type != SS7_BROADBAND_NETWORK) 
			{
				SC_P_TRC (("SCCP::SCRC: unsupported msg type %d\n", 
					p_info->msg_type));
				ret_val = SS7_FAILURE;
				return ret_val;
			}
			else
			{
				ret_val = sccp_parse_ludts (p_info);
				break;
			}
			break;

#endif /* SCCP_BROADBAND */

#ifdef SCCP_INCLUDE_CO_SERVICE
		case CR_MSG_TYPE:
#if 0
			if (COMPARE_ETSI)
			{
			  SC_P_TRC (("SCCP::SCRC: unsupported msg type %d\n", 
			  	p_info->msg_type));
			  ret_val = SS7_FAILURE;
			  break;
			}
#endif
			ret_val = sccp_parse_cr (p_info);
			p_info->event = SCCP_CR_EVENT ;
			break;

		case CC_MSG_TYPE:
			ret_val = sccp_parse_cc (p_info);
			p_info->event = SCCP_CC_EVENT ;
			break;

		case CREF_MSG_TYPE:
			ret_val = sccp_parse_cref (p_info);
			p_info->event = SCCP_CREF_EVENT ;
			break;

		case RLSD_MSG_TYPE:
			ret_val = sccp_parse_rlsd (p_info);
			p_info->event = SCCP_RLSD_EVENT ;
			break;

		case RLC_MSG_TYPE:
			ret_val = sccp_parse_rlc (p_info);
			p_info->event = SCCP_RLC_EVENT ;
			break;

		case ERR_MSG_TYPE:
			ret_val = sccp_parse_err (p_info);
			p_info->event = SCCP_ERR_EVENT ;
			break;

		case IT_MSG_TYPE:
			ret_val = sccp_parse_it (p_info);
			p_info->event = SCCP_IT_EVENT ;
			break;

		case DT1_MSG_TYPE:
			ret_val = sccp_parse_dt1 (p_info);
			p_info->event = SCCP_DT1_EVENT ;
			break;

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

		case DT2_MSG_TYPE:
			ret_val = sccp_parse_dt2 (p_info);
			p_info->event = SCCP_DT2_EVENT ;
			break;

		case AK_MSG_TYPE:
			ret_val = sccp_parse_ak (p_info);
			p_info->event = SCCP_AK_EVENT ;
			break;

		case ED_MSG_TYPE:
			ret_val = sccp_parse_ed (p_info);
			p_info->event = SCCP_ED_EVENT ;
			break;

		case EA_MSG_TYPE:
			ret_val = sccp_parse_ea (p_info);
			p_info->event = SCCP_EA_EVENT ;
			break;

		case RSR_MSG_TYPE:
			ret_val = sccp_parse_rsr (p_info);
			p_info->event = SCCP_RSR_EVENT ;
			break;

		case RSC_MSG_TYPE:
			ret_val = sccp_parse_rsc (p_info);
			p_info->event = SCCP_RSC_EVENT ;
			break;

#endif  /* SCCP_INCLUDE_CO_SERVICE */
#endif   /* SCCP_INCLUDE_CO_CLASS3_SERVICE */

		default:
			SC_P_TRC (("SCCP::SCRC: unsupported msg type %d\n", 
				p_info->msg_type));
			ret_val = SS7_FAILURE;
			return ret_val;
	}

	/* SPR # 3825 Fix Start */
	/* Check the message priority and adjust it if out of range */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		min_msg_priority = sccp_get_min_message_priority (p_info->msg_type);
		max_msg_priority = sccp_get_max_message_priority (p_info->msg_type);

		if ( (p_info->msg_type == UDT_MSG_TYPE) ||
			(p_info->msg_type == XUDT_MSG_TYPE) )
		{
			if ( (p_info->cd_addr.ssn_ind) && (p_info->cd_addr.ssn==SCMG_SSN) )
			{
				scmg_msg_type = *(p_info->data.p);
				min_msg_priority = sccp_get_min_scmg_message_priority(scmg_msg_type);
				max_msg_priority = sccp_get_max_scmg_message_priority(scmg_msg_type);
			}
		}
	
	
		if (p_info->importance < min_msg_priority)
		{

#if 0 /* Refer SPR 11241 Fix Description */		
			RC_TRC (("SCCP::SCRC: Incoming msg priority invalid. Modified "
					 	"priority from %d to %d\n", 
						p_info->importance, min_msg_priority));
#endif
			p_info->importance = min_msg_priority;
		}
		else if (p_info->importance > max_msg_priority)
		{
#if 0 /* Refer SPR 11241 Fix Description */		
			RC_TRC (("SCCP::SCRC: Incoming msg priority invalid. Modified "
					 	"priority from %d to %d\n", 
						p_info->importance, min_msg_priority));
#endif
			p_info->importance = max_msg_priority;
		}
	}
#endif
	/* SPR # 3825 Fix End */

	return ret_val;
}


/***************************************************************************
**
**      FUNCTION :
**         parses UDT msg
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_udt 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg, pointer, * p_addr, * p_end;
	return_t ret_val;

	if (p_info->m3_data.len < MIN_UDT_MSG_LEN)
	{
		SC_P_TRC (("SCCP::SCRC: udt msg len %d too short\n", 
			p_info->m3_data.len));
		return SS7_FAILURE;
	}

	p_cl_msg = p_info->m3_data.p;
	p_end = p_cl_msg + p_info->m3_data.len;

	p_info->proto_class = p_cl_msg[IDX_PROTO_CLASS_IN_UDT];
	ret_val = sccp_decode_proto_class (p_info);
	if (SS7_FAILURE == ret_val)
	{
		SC_P_TRC (("SCCP::SCRC: invalid protocol class %d\n", 
			p_info->proto_class));
		return SS7_FAILURE;
	}

	pointer = p_cl_msg[IDX_CD_ADDR_PTR_IN_UDT];
	p_addr = &p_cl_msg[IDX_CD_ADDR_PTR_IN_UDT] + pointer;
 	
	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: called addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
	     (! p_info->cd_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid called addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cd_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

	pointer = p_cl_msg[IDX_CG_ADDR_PTR_IN_UDT];
	p_addr = &p_cl_msg[IDX_CG_ADDR_PTR_IN_UDT] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: calling addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
	     (! p_info->cg_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid calling addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

	pointer = p_cl_msg[IDX_DATA_PTR_IN_UDT];
	p_info->data.p = &p_cl_msg[IDX_DATA_PTR_IN_UDT] + pointer;

	/* Added check: if data pointer points to the end of message 
	 */
	if ((p_info->data.p >= p_end) ||
	    ((p_info->data.p + *(p_info->data.p)) > p_end))
	{
		RC_TRC (("SCCP::SCRC: data pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	p_info->data.len = *(p_info->data.p);
	p_info->data.p++;

#if 0 /** SPR# IMP_SPR Start Fix **/

    /* salil - SPR # 8530 starts */
    
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
    if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {

        pointer = p_cl_msg[IDX_OPT_PARAM_PTR_IN_UDT];
        p_opt_param = &p_cl_msg[IDX_OPT_PARAM_PTR_IN_UDT] + pointer;

        done = SS7_FALSE;

        while (!done)
        {
            if (p_opt_param >= p_end)
            {
                RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
                return SS7_FAILURE;
            }
            if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
            {
                if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                            p_end) ||
                        ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                         *(p_opt_param + O_PARAM_TYPE_LEN) >
                         p_end))
                {
                    RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                    return SS7_FAILURE;
                }
            }

            switch (*p_opt_param)
            {
                case IMPORTANCE_PARAM_TYPE:

                    p_opt_param += O_PARAM_TYPE_LEN;
                    len = *p_opt_param;
                    p_opt_param += O_PARAM_LEN_LEN;

                    if (! (len == IMPORTANCE_PARAM_LEN))
                    {
                        RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                    len));
                        return SS7_FAILURE;
                    }

                    p_info->importance = *p_opt_param++;
                    SET_IMPORTANCE_PRESENT(p_info);

                    break;
                case END_OF_OPT_PARAM_TYPE:
                    done = SS7_TRUE;
                    break;

                default:
                    RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                    return SS7_FAILURE;
            }
        }
    }
    
#endif
    
    /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses UDTS msg
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_udts 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
    U8bit * p_cl_msg, pointer, * p_addr,* p_end;
    return_t ret_val;

	if (p_info->m3_data.len < MIN_UDTS_MSG_LEN)
	{
		SC_P_TRC (("SCCP::SCRC: udts msg len %d too short\n", 
			p_info->m3_data.len));
		return SS7_FAILURE;
	}

	p_cl_msg = p_info->m3_data.p;
	p_end = p_cl_msg + p_info->m3_data.len;

        /* Fixed SPR-ID: 1289 
         * This message does not contain protocol class 
         */
	p_info->ret_cause = p_cl_msg[IDX_RET_CAUSE_IN_UDTS];

	pointer = p_cl_msg[IDX_CD_ADDR_PTR_IN_UDTS];
	p_addr = &p_cl_msg[IDX_CD_ADDR_PTR_IN_UDTS] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: called addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
	     (! p_info->cd_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid called addr\n"));
		return SS7_FAILURE;
	}

	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cd_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

	pointer = p_cl_msg[IDX_CG_ADDR_PTR_IN_UDTS];
	p_addr = &p_cl_msg[IDX_CG_ADDR_PTR_IN_UDTS] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: calling addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
		 /** Changes made by SAchin **/ 
#if 0
	     (! p_info->cd_addr.gti)))
#endif
	     (! p_info->cg_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid calling addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

	pointer = p_cl_msg[IDX_DATA_PTR_IN_UDTS];
	p_info->data.p = &p_cl_msg[IDX_DATA_PTR_IN_UDTS] + pointer;

        /* Added check: if data pointer points to the end of message 
         */

	if ((p_info->data.p >= p_end) ||
	    ((p_info->data.p + *(p_info->data.p)) > p_end))
	{
		RC_TRC (("SCCP::SCRC: data pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	p_info->data.len = *(p_info->data.p);
	p_info->data.p++;

#if 0 /** SPR# IMP_SPR Start Fix **/
    
    /* salil - SPR # 8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
    if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {

        pointer = p_cl_msg[IDX_OPT_PARAM_PTR_IN_UDTS];
        p_opt_param = &p_cl_msg[IDX_OPT_PARAM_PTR_IN_UDTS] + pointer;

        done = SS7_FALSE;

        while (!done)
        {
            if (p_opt_param >= p_end)
            {
                RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
                return SS7_FAILURE;
            }
            if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
            {
                if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                            p_end) ||
                        ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                         *(p_opt_param + O_PARAM_TYPE_LEN) >
                         p_end))
                {
                    RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                    return SS7_FAILURE;
                }
            }

            switch (*p_opt_param)
            {
                case IMPORTANCE_PARAM_TYPE:

                    p_opt_param += O_PARAM_TYPE_LEN;
                    len = *p_opt_param;
                    p_opt_param += O_PARAM_LEN_LEN;

                    if (! (len == IMPORTANCE_PARAM_LEN))
                    {
                        RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                    len));
                        return SS7_FAILURE;
                    }

                    p_info->importance = *p_opt_param++;
                    SET_IMPORTANCE_PRESENT(p_info);

                    break;
                case END_OF_OPT_PARAM_TYPE:
                    done = SS7_TRUE;
                    break;

                default:
                    RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                    return SS7_FAILURE;
            }
        }
    }
    
#endif
    
    /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses XUDT msg
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_xudt 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg, pointer, * p_addr, * p_opt_param, len, * p_end;
	return_t ret_val;
	Boolean done;

	if (p_info->m3_data.len < MIN_XUDT_MSG_LEN)
	{
		SC_P_TRC (("SCCP::SCRC: xudt msg len %d too short\n", 
			p_info->m3_data.len));
		return SS7_FAILURE;
	}

	p_cl_msg = p_info->m3_data.p;
	p_end = p_cl_msg + p_info->m3_data.len;

	p_info->proto_class = p_cl_msg[IDX_PROTO_CLASS_IN_XUDT];
	ret_val = sccp_decode_proto_class (p_info);
	if (SS7_FAILURE == ret_val)
	{
		SC_P_TRC (("SCCP::SCRC: invalid protocol class %d\n", 
			p_info->proto_class));
		return SS7_FAILURE;
	}

	p_info->hop_counter = p_cl_msg[IDX_HOP_CNTR_IN_XUDT];
	/** SPR # 2665 Fix Start **/

	/** SPR # 3683 Fix Start **/
	/* start message return procedure rather than discarding the message;
	*/
#if 0
	if (p_info->hop_counter < 1)
	{
		SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
			p_info->hop_counter));
		return SS7_FAILURE;
	}
#endif
	/** SPR # 3683 Fix End **/

	/* In ITU and ETSI, 1<=hop counter<=15;
	** In ANSI and BCGR, it is only recommended that hop counter <= 15; so we 
	** don't check this in ANSI and BCGR to ensure that our stack can work 
	** with non-HSS SCCPs as peers
	*/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		if (p_info->hop_counter > 15)
		{
			SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
				p_info->hop_counter));
			return SS7_FAILURE;
		}
	}
#endif
	/** SPR # 2665 Fix End **/
	SET_HOP_COUNTER_IE_PRESENT(p_info);

	pointer = p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDT];
	p_addr = &p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDT] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: called addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
	     (! p_info->cd_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid called addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cd_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

	pointer = p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDT];
	p_addr = &p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDT] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: calling addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
	     (! p_info->cg_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid calling addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */


	pointer = p_cl_msg[IDX_DATA_PTR_IN_XUDT];
	p_info->data.p = &p_cl_msg[IDX_DATA_PTR_IN_XUDT] + pointer;

        /* Added check: if data pointer points to the end of message 
         */

	if ((p_info->data.p >= p_end) ||
	    ((p_info->data.p + *(p_info->data.p)) > p_end))
	{
		RC_TRC (("SCCP::SCRC: data pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	p_info->data.len = *(p_info->data.p);
	p_info->data.p++;

	pointer = p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT];
	p_opt_param = &p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT] + pointer;

	done = SS7_FALSE;
	while (!done)
	{
		if (p_opt_param >= p_end)
		{
			RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
			return SS7_FAILURE;
		}
		if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
		{
			if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
		   	     p_end) ||
		   		((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
				 *(p_opt_param + O_PARAM_TYPE_LEN) >
		   		 p_end))
			{
				RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
				return SS7_FAILURE;
			}
		}

		switch (*p_opt_param)
		{
			case SEGMENTATION_PARAM_TYPE:
				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == NW_SEGMENTATION_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid seg param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->segment.rem_seg = (*p_opt_param) & 0x0f;
				p_info->segment.f_bit = (*p_opt_param >> 7);
				/** SPR # 2663 Fix Start **/
				p_info->segment.isdo = (*p_opt_param & 0x40) >> 0x6;
				/** SPR # 2663 Fix End **/
				/** SPR 10882 - Fix Start **/
				p_info->segment.spare_bit = (*p_opt_param & 0x30);
				/** SPR 10882 - Fix End   **/
				p_opt_param ++;
				/** SPR # 2604 Fix Start **/
				p_info->segment.slr = (  p_opt_param [0] & 0x000000ff) |
								( (p_opt_param [1] << 8) & 0x0000ff00 ) |
								( (p_opt_param [2] << 16) & 0x00ff0000 );
				/** SPR # 2604 Fix contd. **/


				RC_TRC (("SCCP::SCRC: segment %d slr %u f_bit %d\n",
				         p_info->segment.rem_seg, p_info->segment.slr,
				         p_info->segment.f_bit));
				p_opt_param += SLR_LEN;
				SET_SEGMENTATION_PRESENT(p_info);

				break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
			case IMPORTANCE_PARAM_TYPE:
				if (! ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE))
				{
					RC_TRC (("SCCP::SCLC: invalid optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == IMPORTANCE_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->importance = *p_opt_param++;
				SET_IMPORTANCE_PRESENT(p_info);

				break;
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			case ISNI_PARAM_TYPE:
				if (!((COMPARE_ANSI) || (COMPARE_BCGR)))
				{
					RC_TRC (("SCCP::SCRC: unknown optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				p_info->isni.len = *p_opt_param++;
				sccp_memcpy (p_info->isni.list, p_opt_param, p_info->isni.len);
				SET_ISNI_PRESENT (p_info);
				p_opt_param += p_info->isni.len;

				break;
#endif

			case END_OF_OPT_PARAM_TYPE:
				done = SS7_TRUE;
				break;

			default:
/** SPR 10854 - Fix Start */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
				{
					RC_TRC (("SCCP::SCRC: invalid optional param\n"));
					return SS7_FAILURE;
				}	
#endif
#if ( defined(SCCP_ANSI) || defined(SCCP_BCGR) ) 
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
				{
					return SS7_SUCCESS;
				}
#endif
/** SPR 10854 - Fix End  */
		}
	}

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses XUDTS msg
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_xudts 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg, pointer, * p_addr, * p_opt_param, len, * p_end;
	return_t ret_val;
	Boolean done;

	if (p_info->m3_data.len < MIN_XUDTS_MSG_LEN)
	{
		SC_P_TRC (("SCCP::SCRC: xudt msg len %d too short\n", 
			p_info->m3_data.len));
		return SS7_FAILURE;
	}

	p_cl_msg = p_info->m3_data.p;
	p_end = p_cl_msg + p_info->m3_data.len;

        /* Fixed SPR-ID: 1289 
	 * p_info->ret_cause field was not set properly.
         * Also, this message does not contain protocol class.
         */
	p_info->ret_cause = p_cl_msg[IDX_RET_CAUSE_IN_XUDTS];

	p_info->hop_counter = p_cl_msg[IDX_HOP_CNTR_IN_XUDTS];
	/** SPR # 2665 Fix Start **/

	/** SPR # 3683 Fix Start **/
	/* start message return procedure rather than discarding the message;
	*/
#if 0
	if (p_info->hop_counter < 1)
	{
		SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
			p_info->hop_counter));
		return SS7_FAILURE;
	}
#endif
	/** SPR # 3683 Fix End **/

	/* In ITU and ETSI, 1<=hop counter<=15;
	** In ANSI and BCGR, it is only recommended that hop counter <= 15; so we don't check
	** do this check in ANSI and BCGR to ensure that our stack can work with non-HSS SCCPs
	** as peers
	*/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		if (p_info->hop_counter > 15)
		{
			SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
				p_info->hop_counter));
			return SS7_FAILURE;
		}
	}
#endif
	/** SPR # 2665 Fix End **/
	SET_HOP_COUNTER_IE_PRESENT(p_info);

	pointer = p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDTS];
	p_addr = &p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDTS] + pointer;

        /* SPR 1345: Start fix 
         * address length/pointer was not being checked properly
         */
        if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
        {
                RC_TRC (("SCCP::SCRC: called addr pointer/len corrupt\n"));
                return SS7_FAILURE;
        }
	/* SPR 1345: End fix */

	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
	     (! p_info->cd_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid called addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cd_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */


	pointer = p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDTS];
	p_addr = &p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDTS] + pointer;

        /* SPR 1345: Start fix 
         * address pointer was not being checked properly
         */
        if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
        {
                RC_TRC (("SCCP::SCRC: calling addr pointer/len corrupt\n"));
                return SS7_FAILURE;
        }
	/* SPR 1345: End fix */

	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
	     (! p_info->cg_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid calling addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */


	pointer = p_cl_msg[IDX_DATA_PTR_IN_XUDTS];
	p_info->data.p = &p_cl_msg[IDX_DATA_PTR_IN_XUDTS] + pointer;

 
        /* Added check: if data pointer points to the end of message
         */
 
        if ((p_info->data.p >= p_end) ||
            ((p_info->data.p + *(p_info->data.p)) > p_end))
        {
                RC_TRC (("SCCP::SCRC: data pointer/len corrupt\n"));
                return SS7_FAILURE;
        }

	p_info->data.len = *(p_info->data.p);
	p_info->data.p++;

	pointer = p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS];
	p_opt_param = &p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS] + pointer;

	done = SS7_FALSE;
	while (!done)
	{
		if (p_opt_param >= p_end)
		{
			RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
			return SS7_FAILURE;
		}
		if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
		{
			if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
		   	     p_end) ||
		   		((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
				 *(p_opt_param + O_PARAM_TYPE_LEN) >
		   		 p_end))
			{
				RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
				return SS7_FAILURE;
			}
		}
		switch (*p_opt_param)
		{
			case SEGMENTATION_PARAM_TYPE:
				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == NW_SEGMENTATION_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid seg param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->segment.rem_seg = (*p_opt_param) & 0x0f;
				p_info->segment.f_bit = (*p_opt_param >> 7);
				/** SPR 10882 - Fix Start **/
				p_info->segment.spare_bit = (*p_opt_param & 0x30);
				/** SPR 10882 - Fix End   **/
				p_opt_param ++;
				/** SPR # 2604 Fix contd. **/
				p_info->segment.slr = (  p_opt_param [0] & 0x000000ff) |
								( (p_opt_param [1] << 8) & 0x0000ff00 ) |
								( (p_opt_param [2] << 16) & 0x00ff0000 );
				/** SPR # 2604 Fix End **/

				RC_TRC (("SCCP::SCRC: segment %d slr %u f_bit %d\n",
				         p_info->segment.rem_seg, p_info->segment.slr,
				         p_info->segment.f_bit));
				p_opt_param += SLR_LEN;
				SET_SEGMENTATION_PRESENT(p_info);

				break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
			case IMPORTANCE_PARAM_TYPE:
				if (! ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE))
				{
					RC_TRC (("SCCP::SCLC: invalid optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == NW_IMPORTANCE_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->importance = *p_opt_param++;
				RC_TRC (("SCCP::SCRC: importance of %d\n", p_info->importance));
				SET_IMPORTANCE_PRESENT(p_info);

				break;
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			case ISNI_PARAM_TYPE:
				if (!((COMPARE_ANSI) || (COMPARE_BCGR)))
				{
					RC_TRC (("SCCP::SCRC: unknown optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				p_info->isni.len = *p_opt_param++;
				sccp_memcpy (p_info->isni.list, p_opt_param, p_info->isni.len);
				SET_ISNI_PRESENT (p_info);
				p_opt_param += p_info->isni.len;

				break;
#endif

			case END_OF_OPT_PARAM_TYPE:
				done = SS7_TRUE;
				break;

			default:
/** SPR 10854 - Fix Start */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
				{
					RC_TRC (("SCCP::SCRC: invalid optional param\n"));
					return SS7_FAILURE;
				}
#endif
#if ( defined(SCCP_ANSI) || defined(SCCP_BCGR) ) 
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
				{
					return SS7_SUCCESS;
				}
#endif
/** SPR 10854 - Fix End  */

		}
	}

	return SS7_SUCCESS;
}


#ifdef SCCP_BROADBAND
/***************************************************************************
**
**      FUNCTION :
**         parses LUDT msg
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_ludt 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg, * p_addr, * p_opt_param, len, * p_end;
	U16bit pointer, data_len;
	return_t ret_val;
	Boolean done;

	if (p_info->m3_data.len < MIN_LUDT_MSG_LEN)
	{
		SC_P_TRC (("SCCP::SCRC: ludt msg len %d too short\n", 
			p_info->m3_data.len));
		return SS7_FAILURE;
	}

	p_cl_msg = p_info->m3_data.p;
	p_end = p_cl_msg + p_info->m3_data.len;

	p_info->proto_class = p_cl_msg[IDX_PROTO_CLASS_IN_LUDT];
	ret_val = sccp_decode_proto_class (p_info);
	if (SS7_FAILURE == ret_val)
	{
		SC_P_TRC (("SCCP::SCRC: invalid protocol class %d\n", 
			p_info->proto_class));
		return SS7_FAILURE;
	}

	p_info->hop_counter = p_cl_msg[IDX_HOP_CNTR_IN_LUDT];
	/** SPR # 2665 Fix Start **/

	/** SPR # 3683 Fix Start **/
	/* start message return procedure rather than discarding the message;
	*/
#if 0
	if (p_info->hop_counter < 1)
	{
		SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
			p_info->hop_counter));
		return SS7_FAILURE;
	}
#endif
	/** SPR # 3683 Fix End **/

	/* In ITU and ETSI, 1<=hop counter<=15;
	** In ANSI and BCGR, it is only recommended that hop counter <= 15; so we 
	** don't check this in ANSI and BCGR to ensure that our stack can work 
	** with non-HSS SCCPs as peers
	*/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		if (p_info->hop_counter > 15)
		{
			SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
				p_info->hop_counter));
			return SS7_FAILURE;
		}
	}
#endif
	/** SPR # 2665 Fix End **/
	SET_HOP_COUNTER_IE_PRESENT(p_info);

	pointer = ((p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDT]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDT+1]<<8)&0xff00);
	p_addr = &p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDT+1] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: called addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
	     (! p_info->cd_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid called addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cd_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

	pointer = ((p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDT]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDT+1]<<8)&0xff00) ;
	p_addr = &p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDT+1] + pointer;

	/* SPR 1345
  	 * address pointer was not being checked properly
	 */
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: calling addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
	     (! p_info->cg_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid calling addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */


	pointer = ((p_cl_msg[IDX_DATA_PTR_IN_LUDT]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_DATA_PTR_IN_LUDT+1]<<8)&0xff00) ;
	p_info->data.p = &p_cl_msg[IDX_DATA_PTR_IN_LUDT+1] + pointer;

        /* Added check: if data pointer points to the end of message 
         */

	data_len = ((((p_info->data.p[0])<<0)&0x00ff) |
				(((p_info->data.p[1])<<8)&0xff00)) ;
	if ((p_info->data.p >= p_end) ||
		((p_info->data.p + data_len) > p_end))
	{
		RC_TRC (("SCCP::SCRC: data pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	p_info->data.len = data_len ;
	p_info->data.p += 2 ;

	pointer = ((p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1]<<8)&0xff00) ;
	p_opt_param = &p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1] + pointer;

	done = SS7_FALSE;
	while (!done)
	{
		if (p_opt_param >= p_end)
		{
			RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
			return SS7_FAILURE;
		}
		if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
		{
			if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
		   	     p_end) ||
		   		((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
				 *(p_opt_param + O_PARAM_TYPE_LEN) >
		   		 p_end))
			{
				RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
				return SS7_FAILURE;
			}
		}

		switch (*p_opt_param)
		{
			case SEGMENTATION_PARAM_TYPE:
				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == NW_SEGMENTATION_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid seg param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->segment.rem_seg = (*p_opt_param) & 0x0f;
				p_info->segment.f_bit = (*p_opt_param >> 7);
				/** SPR # 2663 Fix Start **/
				p_info->segment.isdo = (*p_opt_param & 0x40) >> 0x6;
				/** SPR # 2663 Fix End **/
				p_opt_param ++;
				/** SPR # 2604 Fix Start **/
				p_info->segment.slr = (  p_opt_param [0] & 0x000000ff) |
								( (p_opt_param [1] << 8) & 0x0000ff00 ) |
								( (p_opt_param [2] << 16) & 0x00ff0000 );
				/** SPR # 2604 Fix contd. **/


				RC_TRC (("SCCP::SCRC: segment %d slr %u f_bit %d\n",
				         p_info->segment.rem_seg, p_info->segment.slr,
				         p_info->segment.f_bit));
				p_opt_param += SLR_LEN;
				SET_SEGMENTATION_PRESENT(p_info);

				break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
			case IMPORTANCE_PARAM_TYPE:
				if (! ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE))
				{
					RC_TRC (("SCCP::SCLC: invalid optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == IMPORTANCE_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->importance = *p_opt_param++;
				SET_IMPORTANCE_PRESENT(p_info);

				break;
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			case ISNI_PARAM_TYPE:
				if (!((COMPARE_ANSI) || (COMPARE_BCGR)))
				{
					RC_TRC (("SCCP::SCRC: unknown optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				p_info->isni.len = *p_opt_param++;
				sccp_memcpy (p_info->isni.list, p_opt_param, p_info->isni.len);
				SET_ISNI_PRESENT (p_info);
				p_opt_param += p_info->isni.len;

				break;
#endif

			case END_OF_OPT_PARAM_TYPE:
				done = SS7_TRUE;
				break;

			default:
				RC_TRC (("SCCP::SCRC: invalid optional param\n"));
				return SS7_FAILURE;
		}
	}

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses LUDTS msg
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_ludts 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg, * p_addr, * p_opt_param, len, * p_end;
	U16bit pointer, data_len;
	return_t ret_val;
	Boolean done;

	if (p_info->m3_data.len < MIN_LUDTS_MSG_LEN)
	{
		SC_P_TRC (("SCCP::SCRC: ludt msg len %d too short\n", 
			p_info->m3_data.len));
		return SS7_FAILURE;
	}

	p_cl_msg = p_info->m3_data.p;
	p_end = p_cl_msg + p_info->m3_data.len;

        /* Fixed SPR-ID: 1289 
	 * p_info->ret_cause field was not set properly.
         * Also, this message does not contain protocol class.
         */
	p_info->ret_cause = p_cl_msg[IDX_RET_CAUSE_IN_LUDTS];

	p_info->hop_counter = p_cl_msg[IDX_HOP_CNTR_IN_LUDTS];
	/** SPR # 2665 Fix Start **/

	/** SPR # 3683 Fix Start **/
	/* start message return procedure rather than discarding the message;
	*/
#if 0
	if (p_info->hop_counter < 1)
	{
		SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
			p_info->hop_counter));
		return SS7_FAILURE;
	}
#endif
	/** SPR # 3683 Fix End **/

	/* In ITU and ETSI, 1<=hop counter<=15;
	** In ANSI and BCGR, it is only recommended that hop counter <= 15; so we don't check
	** do this check in ANSI and BCGR to ensure that our stack can work with non-HSS SCCPs
	** as peers
	*/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		if (p_info->hop_counter > 15)
		{
			SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
				p_info->hop_counter));
			return SS7_FAILURE;
		}
	}
#endif
	/** SPR # 2665 Fix End **/
	SET_HOP_COUNTER_IE_PRESENT(p_info);

	pointer = ((p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDTS]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDTS+1]<<8)&0xff00) ;
	p_addr = &p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDTS+1] + pointer;

	/* SPR 1345: Start fix 
	* address length/pointer was not being checked properly
	*/
	if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
	{
		RC_TRC (("SCCP::SCRC: called addr pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
	/* SPR 1345: End fix */

	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
	     (! p_info->cd_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid called addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cd_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */


	pointer = ((p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDTS]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDTS+1]<<8)&0xff00) ;
	p_addr = &p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDTS+1] + pointer;

        /* SPR 1345: Start fix 
         * address pointer was not being checked properly
         */
        if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
        {
                RC_TRC (("SCCP::SCRC: calling addr pointer/len corrupt\n"));
                return SS7_FAILURE;
        }
	/* SPR 1345: End fix */

	ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);
	if ((SS7_FAILURE == ret_val) ||
	    ((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
	     (! p_info->cg_addr.gti)))
	{
		/* Routing indicator contradicts address information */
		SC_P_TRC (("SCCP::SCRC: invalid calling addr\n"));
		return SS7_FAILURE;
	}
	/* SPR 1323: Start Fix
	 * Check if address length is correct 
         */
        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */


	pointer = ((p_cl_msg[IDX_DATA_PTR_IN_LUDTS]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_DATA_PTR_IN_LUDTS+1]<<8)&0xff00) ;
	p_info->data.p = &p_cl_msg[IDX_DATA_PTR_IN_LUDTS+1] + pointer;

 
	data_len = ((((p_info->data.p[0])<<0)&0x00ff) |
				(((p_info->data.p[1])<<8)&0xff00)) ;
	/* SPR ITU-ATS: Start fix
	* check if data pointer points to the end of message
	*/
	if ((p_info->data.p >= p_end) ||
		((p_info->data.p + data_len) > p_end))
	{
		RC_TRC (("SCCP::SCRC: data pointer/len corrupt\n"));
		return SS7_FAILURE;
	}
 
	p_info->data.len = data_len ;
	p_info->data.p += 2 ;

	pointer = ((p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS]<<0)&0x00ff)|
			  ((p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1]<<8)&0xff00) ;
	p_opt_param = &p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1] + pointer;

	done = SS7_FALSE;
	while (!done)
	{
		if (p_opt_param >= p_end)
		{
			RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
			return SS7_FAILURE;
		}
		if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
		{
			if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
		   	     p_end) ||
		   		((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
				 *(p_opt_param + O_PARAM_TYPE_LEN) >
		   		 p_end))
			{
				RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
				return SS7_FAILURE;
			}
		}
		switch (*p_opt_param)
		{
			case SEGMENTATION_PARAM_TYPE:
				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == NW_SEGMENTATION_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid seg param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->segment.rem_seg = (*p_opt_param) & 0x0f;
				p_info->segment.f_bit = (*p_opt_param >> 7);
				p_opt_param ++;
				/** SPR # 2604 Fix contd. **/
				p_info->segment.slr = (  p_opt_param [0] & 0x000000ff) |
								( (p_opt_param [1] << 8) & 0x0000ff00 ) |
								( (p_opt_param [2] << 16) & 0x00ff0000 );
				/** SPR # 2604 Fix End **/

				RC_TRC (("SCCP::SCRC: segment %d slr %u f_bit %d\n",
				         p_info->segment.rem_seg, p_info->segment.slr,
				         p_info->segment.f_bit));
				p_opt_param += SLR_LEN;
				SET_SEGMENTATION_PRESENT(p_info);

				break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
			case IMPORTANCE_PARAM_TYPE:
				if (! ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE))
				{
					RC_TRC (("SCCP::SCLC: invalid optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				len = *p_opt_param;
				p_opt_param += O_PARAM_LEN_LEN;

				if (! (len == NW_IMPORTANCE_PARAM_LEN))
				{
					RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
					          len));
					return SS7_FAILURE;
				}

				p_info->importance = *p_opt_param++;
				RC_TRC (("SCCP::SCRC: importance of %d\n", p_info->importance));
				SET_IMPORTANCE_PRESENT(p_info);

				break;
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			case ISNI_PARAM_TYPE:
				if (!((COMPARE_ANSI) || (COMPARE_BCGR)))
				{
					RC_TRC (("SCCP::SCRC: unknown optional param %d\n",
					         *p_opt_param));
					return SS7_FAILURE;
				}

				p_opt_param += O_PARAM_TYPE_LEN;
				p_info->isni.len = *p_opt_param++;
				sccp_memcpy (p_info->isni.list, p_opt_param, p_info->isni.len);
				SET_ISNI_PRESENT (p_info);
				p_opt_param += p_info->isni.len;

				break;
#endif

			case END_OF_OPT_PARAM_TYPE:
				done = SS7_TRUE;
				break;

			default:
				RC_TRC (("SCCP::SCRC: invalid optional param\n"));
				return SS7_FAILURE;

		}
	}

	return SS7_SUCCESS;
}
#endif /* ifdef SCCP_BROADBAND */

/***************************************************************************
**
**      FUNCTION :
**           decodes SCCP address
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_decode_sccp_addr 
#ifdef ANSI_PROTO
	(U8bit * p_addr, sccp_addr_t * p_sc_addr)
#else
	(p_addr, p_sc_addr)
	U8bit * p_addr ;
	sccp_addr_t * p_sc_addr ;
#endif
{
	U8bit min_len = 0, addr_len, addr_ind, * p_byte;

	/** SPR # 2776 Fix Start **/
	p_sc_addr->pc_ind = SS7_FALSE;
	p_sc_addr->ssn_ind = SS7_FALSE;
	p_sc_addr->gti = 0;
	p_sc_addr->pc = 0;
	p_sc_addr->ssn = 0;
	p_sc_addr->gt_len = 0;
	/** SPR # 2776 Fix End **/

	p_byte = p_addr;
	addr_len = *p_byte++;
	addr_ind = *p_byte++;
	/* SPR GR: Include length of address indicator */
	min_len++;

	/* Check the length of the address */
	if (addr_ind & ADDR_IND_PC_MASK)
		min_len += PC_SIZE;

	if (addr_ind & ADDR_IND_SSN_MASK)
		min_len++;

	if (min_len > addr_len)
	{
		/* Address length does not conform to the address indicator
		   indicated length */
		return SS7_FAILURE;
	}

        /* SPR 1347: Start fix
         * if routing on ssn, check if ssn present
         */
         if (ROUTE_ON_SSN == ((addr_ind >> 6) & 0x1)) /* routing on SSN */
         {
           if (!(addr_ind & ADDR_IND_SSN_MASK))
           {
                /* SSN absent - invalid address */
                return SS7_FAILURE;
           }

         }

       /* SPR 1347: End fix */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		if (addr_ind & ADDR_IND_PC_MASK)
		{
			p_sc_addr->pc_ind = SS7_TRUE;
			p_sc_addr->pc = GET_PC(p_byte);
			p_byte += PC_SIZE;
		}
		else p_sc_addr->pc_ind = SS7_FALSE;

		if (addr_ind & ADDR_IND_SSN_MASK)
		{
			p_sc_addr->ssn_ind = SS7_TRUE;
			p_sc_addr->ssn = *p_byte++;
		}
		else p_sc_addr->ssn_ind = SS7_FALSE;
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (addr_ind & ADDR_IND_SSN_MASK)
		{
			p_sc_addr->ssn_ind = SS7_TRUE;
			p_sc_addr->ssn = *p_byte++;
		}
		else p_sc_addr->ssn_ind = SS7_FALSE;

		if (addr_ind & ADDR_IND_PC_MASK)
		{
			p_sc_addr->pc_ind = SS7_TRUE;
			p_sc_addr->pc = GET_PC(p_byte);
			p_byte += PC_SIZE;
		}
		else p_sc_addr->pc_ind = SS7_FALSE;
	}
#endif

	if (addr_ind & ADDR_IND_GTI_MASK)
	{
		p_sc_addr->gti = (addr_ind & ADDR_IND_GTI_MASK) >> 2;

/* Ericsson changes - check if gti is not 0100 */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
	{
                if (!(p_sc_addr->gti & 0x4)) 
                      return SS7_FAILURE;
	}
#endif

#if 0
	/* This SPR has been cancelled; It is assumed that the GT translation
	** function checks for this condition
	*/

	/** SPR #2591 Fix Start **/
	/** GTI must be 0010 for ANSI and Bellcore **/
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (!(p_sc_addr->gti & 0x2))
			return SS7_FAILURE;
	}
#endif
	/** SPR #2591 Fix End **/
#endif

		p_sc_addr->gt_len = (U8bit)((p_addr + *p_addr + 1) - p_byte);

		/* SPR GR: Check if gl is present */
		if (p_sc_addr->gt_len == 0)
			return SS7_FAILURE;

		/* SPR #872: check GT size */ 
		if (p_sc_addr->gt_len >= MAX_GT_LEN)
			return SS7_FAILURE;
		/* SPR #872 fix end */

		sccp_memcpy (p_sc_addr->gt, p_byte, p_sc_addr->gt_len);
	}
	else p_sc_addr->gti = 0;

	p_sc_addr->rout_ind = (addr_ind >> 6) & 0x1;
	p_sc_addr->nat_ind = (addr_ind >> 7) & 0x1;

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         decodes protocol class
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_decode_proto_class 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	if ((p_info->proto_class & 0xf) > 1)
	{
		SC_P_TRC (("SCCP::SCRC: unsupported proto class %d\n",
		           p_info->proto_class & 0xf));
		return SS7_FAILURE;
	}

	/** SPR # 2615 Fix START **/
	/** check return option **/
	if ( (p_info->proto_class & 0x70) != 0 )
	{
		SC_P_TRC (("SCCP::SCRC: Spare bits in Return option are not set to 0 (0x%2x)\n",
		           p_info->proto_class & 0xf0));
		return SS7_FAILURE;
	}
	/** SPR # 2615 Fix END **/

	return SS7_SUCCESS;
}

#ifdef SCCP_INCLUDE_CO_SERVICE

/***************************************************************************
**
**      FUNCTION :
**         parses CR msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, slr, proto_class
**    V elements : cd_addr
**    O elements : credit, cg_addr, data, hop_counter,
**           In ITU importance
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_cr 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg, pointer, *p_addr, *p_end, *p_opt_param ;
  return_t ret_val ;
  Boolean done ;
  U16bit  len ;

  if (p_info->m3_data.len < MIN_CR_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: CR msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  p_end = p_info->m3_data.p + p_info->m3_data.len ;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* protocol class */
  p_info->proto_class = *p_co_msg++;
  if ((p_info->proto_class != PROTOCOL_CLASS_2) &&
    (p_info->proto_class != PROTOCOL_CLASS_3))

  {
    SC_P_TRC (("SCCP::SCRC: invalid protocol class in MSG CR %d\n", 
      p_info->proto_class));
    return SS7_FAILURE;
  }

  /* Mandatory variable part */
  pointer = *p_co_msg;

  p_addr = p_co_msg + pointer;

  /* SPR 1345
   * address pointer was not being checked properly
   */
  if ((p_addr >= p_end) || ((p_addr + *p_addr) > p_end))
  {
    RC_TRC (("SCCP::RC: called addr pointer/len corrupt\n"));
    return SS7_FAILURE;
  }

  ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cd_addr);

  /* SPR 1323: Start Fix
   * Check if GT present as per routing indicator 
   */

  if ((SS7_FAILURE == ret_val) ||
      ((ROUTE_ON_GT == p_info->cd_addr.rout_ind) &&
      (! p_info->cd_addr.gti)))
  {
    SC_P_TRC (("SCCP :: SCRC : invalid called addr\n"));
    return SS7_FAILURE;
  }
  /* Check if address length is correct */

  if (*p_addr != sccp_addr_len (&p_info->cd_addr))
  {
    /* Incorrectly coded address */
    RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
    return (SS7_FAILURE) ;
  }
  /* SPR 1323: End fix */


  p_co_msg++; /* skip the pointer */

  /* Optional part */
  if (*p_co_msg == END_OF_OPT_PARAM_TYPE)
  {
    return SS7_SUCCESS;
  }

  pointer = *p_co_msg;
  p_opt_param = p_co_msg + pointer;

  done = SS7_FALSE;
  while (!done)
  {
        /* check if pointer points beyond the end of the message */
        if (p_opt_param >= p_end)
        {
                /* Short message */
                RC_TRC (("SCCP:SCRC:Short message.\n"));
                return SS7_FAILURE;
        }


        if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
        {
    	if ((*(p_opt_param + O_PARAM_TYPE_LEN) + p_opt_param) > p_end) 
    	{
      		/* Short message */
      		RC_TRC (("SCCP:SCRC:Short message.\n"));
      		return SS7_FAILURE;
	}
	}
    switch (*p_opt_param)
    {
      case CREDIT_PARAM_TYPE:

        if (p_info->proto_class != PROTOCOL_CLASS_3)

        /* Ericsson changes - ignore unsupported optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
	{
       	  if (p_info->proto_class == PROTOCOL_CLASS_2)
	  {
         	/* Skip parameter name, length and whole parameter */
         	p_opt_param += O_PARAM_TYPE_LEN;
	 	p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
	 	break;
	  }
	}
#else
	{
          RC_TRC (("SCCP::SCRC:CREDIT_PARAM_TYPE in CLASS 2.\n"));
          return SS7_FAILURE ;
        }
#endif

        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

		len = GET_2_BYTE_LE (p_opt_param) ;
        if (! (*p_opt_param == CREDIT_PARAM_LEN))
        {
          RC_TRC (("SCCP::SCRC: invalid credit len %d\n", len));
          return SS7_FAILURE;
        }

        p_info->credit = *(p_opt_param + O_PARAM_LEN_LEN);

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_CREDIT_PRESENT (p_info);

        break;

      case CG_PARAM_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_addr = p_opt_param;
        ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);

  	/* SPR 1323: Start Fix
   	 * Check if GT present as per routing indicator 
   	 */

  	if ((SS7_FAILURE == ret_val) ||
      		((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
      		(! p_info->cg_addr.gti)))
        {
          RC_TRC (("SCCP::SCRC: Invalid calling address.\n"));
          return SS7_FAILURE;
        }
	/* Check if address length is correct */

        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Calling address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);

        SET_CG_PRESENT (p_info);

        break;

      case DATA_PARAMETER_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_info->data.len = *p_opt_param;

	/* Fix for SPR # 12553 start */
/* spr 12319 change of maximum data length from 130 to 128 */
	  if(p_info->data.len > 128)
        {
          RC_TRC (("SCCP::SCRC: DATA EXCEEDS 128 bytes.\n"));
                return SS7_FAILURE;
        }
	/* Fix for SPR # 12553 End */

        p_info->data.p = (p_opt_param + O_PARAM_LEN_LEN);

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_DATA_PRESENT(p_info);

        break;

      case HOP_COUNTER_PARAM_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        if (*p_opt_param != HOP_COUNTER_PARAM_LEN)
        {
          RC_TRC (("SCCP::SCRC: Invalid hop counter len.\n"));

          return SS7_FAILURE;
        }

        p_info->hop_counter = *(p_opt_param + O_PARAM_LEN_LEN);
		/** SPR # 2665 Fix Start **/

		/** SPR # 3683 Fix Start **/
		/* start message return procedure rather than discarding the message;
		*/
#if 0
		if (p_info->hop_counter < 1)
		{
			SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
				p_info->hop_counter));
			return SS7_FAILURE;
		}
#endif
	/** SPR # 3683 Fix End **/

		/* In ITU and ETSI, 1<=hop counter<=15;
		** In ANSI and BCGR, it is only recommended that hop counter <= 15; so we don't check
		** do this check in ANSI and BCGR to ensure that our stack can work with non-HSS SCCPs
		** as peers
		*/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
		if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
		{
			if (p_info->hop_counter > 15)
			{
				SC_P_TRC (("SCCP::SCRC: invalid Hop Counter (%d)\n", 
					p_info->hop_counter));
				return SS7_FAILURE;
			}
		}
#endif
		/** SPR # 2665 Fix End **/

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_HOP_COUNTER_PRESENT(p_info);
        break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
#ifndef SCCP_ERICSSON_ITU	/* Ericsson changes */
      case IMPORTANCE_PARAM_TYPE:
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_CHINESE)
        {
          p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

          if (*p_opt_param != IMPORTANCE_PARAM_LEN)
          {
            RC_TRC (("SCCP::SCRC: Invalid importance len.\n"));

            return SS7_FAILURE;
          }

          p_info->importance = *(p_opt_param + O_PARAM_LEN_LEN);

          /* Skip length and whole parameter */
          p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
          SET_IMPORTANCE_PRESENT(p_info);
          break;
        }
        else
        {
          RC_TRC (("SCCP::SCRC: invalid optional param\n"));
          return SS7_FAILURE;
        }
#endif
#endif
        
      case END_OF_OPT_PARAM_TYPE:
        done = SS7_TRUE;
        break;

      default:
        RC_TRC (("SCCP::SCRC: invalid optional param\n"));
        return SS7_FAILURE;
    }
  }
  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses CC msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, slr, proto_class
**    V elements : NONE
**    O elements : credit, cd_addr, data
**           In ITU importance
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_cc 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg, pointer, *p_addr, *p_end;
  U8bit *p_opt_param ;
  return_t ret_val;
  Boolean done;
  U16bit len ;

  if (p_info->m3_data.len < MIN_CC_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: CC msg len %d too short\n", 
      p_info->m3_data.len));
    return SS7_FAILURE;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;

  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];
  p_end = p_info->m3_data.p + p_info->m3_data.len;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* protocol class */
  p_info->proto_class = *p_co_msg++;
  if ((p_info->proto_class != PROTOCOL_CLASS_2) &&
    (p_info->proto_class != PROTOCOL_CLASS_3))

  {
    /* SPR 1346: Start fix
       Changed the message type in the trace from CR to CC
     */

    SC_P_TRC (("SCCP::SCRC: invalid protocol class in MSG CC %d\n", 
      p_info->proto_class));
    /* SPR 1346: End fix */
    return SS7_FAILURE;
  }

  /* No Mandatory variable part */

  /* Optional part */
  if (*p_co_msg == END_OF_OPT_PARAM_TYPE)
  {
    return SS7_SUCCESS;
  }

  pointer = *p_co_msg;
  p_opt_param = p_co_msg + pointer;

  done = SS7_FALSE;
  while (!done)
  {
	/* check if pointer points beyond the end of the message */
	if (p_opt_param >= p_end)
	{
	        /* Short message */
                RC_TRC (("SCCP:SCRC:Short message.\n"));
                return SS7_FAILURE;
	}

        if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
        {
    	if ((*(p_opt_param + O_PARAM_TYPE_LEN) + p_opt_param) > p_end) 
    	{
      		/* Short message */
      		RC_TRC (("SCCP:SCRC:Short message.\n"));
      		return SS7_FAILURE;
	}
	}
    switch (*p_opt_param)
    {
      case CREDIT_PARAM_TYPE:

        if (p_info->proto_class != PROTOCOL_CLASS_3)
        {
          RC_TRC (("SCCP::SCRC:CREDIT_PARAM_TYPE in CLASS 2.\n"));
          return SS7_FAILURE ;
        }
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

		len = GET_2_BYTE_LE (p_opt_param) ;
        if (! (*p_opt_param == CREDIT_PARAM_LEN))
        {
          RC_TRC (("SCCP::SCRC: invalid credit len %d\n", len));
          return SS7_FAILURE;
        }

        p_info->credit = *(p_opt_param + O_PARAM_LEN_LEN);

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_CREDIT_PRESENT (p_info);

        break;

      case CD_PARAM_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_addr = p_opt_param;
        ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);

  	/* SPR 1323: Start Fix
   	 * Check if GT present as per routing indicator 
   	 */

  	if ((SS7_FAILURE == ret_val) ||
      		((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
      		(! p_info->cg_addr.gti)))
        {
          RC_TRC (("SCCP::SCRC: Invalid called address.\n"));
          return SS7_FAILURE;
        }
	/* Check if address length is correct */

        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);

        SET_RG_PRESENT (p_info);

        break;

      case DATA_PARAMETER_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_info->data.len = *p_opt_param;
	/* Fix for SPR # 12555 Start  */
/* spr 12322 change of maximum data length from 130 to 128 */
	  if(p_info->data.len > 128)
        {
          RC_TRC (("SCCP::SCRC: DATA EXCEEDS 128 bytes.\n"));
                return SS7_FAILURE;
        }
	/* Fix for SPR # 12555 End  */

        p_info->data.p = (p_opt_param + O_PARAM_LEN_LEN);

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_DATA_PRESENT(p_info);

        break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
      case IMPORTANCE_PARAM_TYPE:

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) )  && defined (SCCP_ERICSSON_ITU)	/* Ericsson changes */
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
		{
          RC_TRC (("SCCP::CL: invalid optional param\n"));
          return SS7_FAILURE;
        }
#else
		/* SPR # 2613 Fix: added COMPARE_BCGR */
		if (COMPARE_ANSI || COMPARE_BCGR)  
        {
          RC_TRC (("SCCP::CL: invalid optional param\n"));
          return SS7_FAILURE;
        }
        else
        {
          p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

          if (*p_opt_param != IMPORTANCE_PARAM_LEN)
          {
            RC_TRC (("SCCP::SCRC: Invalid importance len.\n"));

            return SS7_FAILURE;
          }

          p_info->importance = *(p_opt_param + O_PARAM_LEN_LEN);

          /* Skip length and whole parameter */
          p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
          SET_IMPORTANCE_PRESENT(p_info);
          break;
        }
#endif
#endif
        
      case END_OF_OPT_PARAM_TYPE:
        done = SS7_TRUE;
        break;

      default:
        RC_TRC (("SCCP::CL: invalid optional param\n"));
        return SS7_FAILURE;
    }
  }
  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses CREF msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, ref_cause 
**    V elements : NONE
**    O elements : cd_addr, data
**           In ITU importance
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_cref
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg, pointer, *p_addr, *p_end;
  U8bit *p_opt_param ;
  return_t ret_val;
  Boolean done;

  if (p_info->m3_data.len < MIN_CREF_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: CREF msg len %d too short\n", 
      p_info->m3_data.len));
    return SS7_FAILURE;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;
  
  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];
  p_end = p_info->m3_data.p + p_info->m3_data.len;

  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* refusal cause */
  p_info->rel_cause = *p_co_msg++;

  /* No Mandatory variable part */

  /* Optional part */
  if (*p_co_msg == END_OF_OPT_PARAM_TYPE)
  {
    return SS7_SUCCESS;
  }

  pointer = *p_co_msg;
  p_opt_param = p_co_msg + pointer;

  done = SS7_FALSE;
  while (!done)
  {

        /* check if pointer points beyond the end of the message */
        if (p_opt_param >= p_end)
        {
                /* Short message */
                RC_TRC (("SCCP:SCRC:Short message.\n"));
                return SS7_FAILURE;
        }

        if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
        {
    	if ((*(p_opt_param + O_PARAM_TYPE_LEN) + p_opt_param) > p_end)
    	{
      		/* Short message */
      		RC_TRC (("SCCP:SCRC:Short message.\n"));
      		return SS7_FAILURE;
    	}
	}
    switch (*p_opt_param)
    {
      case CD_PARAM_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_addr = p_opt_param;

	/* SPR 1496: Start fix 
	 * store the parameter in the cg_addr field of p_info
	 * do SET_RG_PRESENT 
	 */

        ret_val = sccp_decode_sccp_addr (p_addr, &p_info->cg_addr);

  	/* SPR 1323: Start Fix
   	 * Check if GT present as per routing indicator 
   	 */

  	if ((SS7_FAILURE == ret_val) ||
      		((ROUTE_ON_GT == p_info->cg_addr.rout_ind) &&
      		(! p_info->cg_addr.gti)))
        {
          RC_TRC (("SCCP::SCRC: Invalid called address.\n"));
          return SS7_FAILURE;
        }
	/* Check if address length is correct */

        if (*p_addr != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          RC_TRC (("SCCP::SCRC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }
	/* SPR 1323: End fix */

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);

        SET_RG_PRESENT (p_info);
	
	/* SPR 1496: End fix */

        break;

      case DATA_PARAMETER_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_info->data.len = *p_opt_param;
	/*Fix for SPR # 12556 Start */
/* spr 12324 change of maximum data length from 130 to 128 */
	  if(p_info->data.len > 128)
        {
          RC_TRC (("SCCP::SCRC: DATA EXCEEDS 128 bytes.\n"));
                return SS7_FAILURE;
        }
	/*Fix for SPR # 12556 End */

        p_info->data.p = (p_opt_param + O_PARAM_LEN_LEN);

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_DATA_PRESENT(p_info);

        break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
      case IMPORTANCE_PARAM_TYPE:

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)	/* Ericsson changes */
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
	{
          RC_TRC (("SCCP::CL: invalid optional param\n"));
          return SS7_FAILURE;
	}
#else
		/* SPR # 2613 Fix: added COMPARE_BCGR */
		if (COMPARE_ANSI || COMPARE_BCGR)  
        {
          RC_TRC (("SCCP::SCRC: invalid optional param\n"));
          return SS7_FAILURE;
        }
        else
        {
          p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

          if (*p_opt_param != IMPORTANCE_PARAM_LEN)
          {
            RC_TRC (("SCCP::SCRC: Invalid importance len.\n"));

            return SS7_FAILURE;
          }

          p_info->importance = *(p_opt_param + O_PARAM_LEN_LEN);

          /* Skip length and whole parameter */
          p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
          SET_IMPORTANCE_PRESENT(p_info);
          break;
        }
#endif
#endif
        
      case END_OF_OPT_PARAM_TYPE:
        done = SS7_TRUE;
        break;

      default:
        RC_TRC (("SCCP::SCRC: invalid optional param\n"));
        return SS7_FAILURE;
    }
  }
  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses RLSD msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, slr, rel_cause 
**    V elements : NONE
**    O elements : data
**           In ITU importance
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_rlsd 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg, pointer, *p_end ;
  U8bit *p_opt_param ;
  Boolean done;

  if (p_info->m3_data.len < MIN_RLSD_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: RLSD msg len %d too short\n", 
      p_info->m3_data.len));
    return SS7_FAILURE;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;

  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];
  p_end = p_info->m3_data.p + p_info->m3_data.len;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* release cause */
  p_info->rel_cause = *p_co_msg++;

  /* No Mandatory variable part */

  /* Optional part */
  if (*p_co_msg == END_OF_OPT_PARAM_TYPE)
  {
    return SS7_SUCCESS;
  }

  pointer = *p_co_msg;
  p_opt_param = p_co_msg + pointer;

  done = SS7_FALSE;
  while (!done)
  {

        /* check if pointer points beyond the end of the message */
        if (p_opt_param >= p_end)
        {
                /* Short message */
                RC_TRC (("SCCP:SCRC:Short message.\n"));
                return SS7_FAILURE;
        }

        if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
        {
    	if ((*(p_opt_param + O_PARAM_TYPE_LEN) + p_opt_param) > p_end)
    	{
      		/* Short message */
      		RC_TRC (("SCCP:SCRC:Short message.\n"));
      		return SS7_FAILURE;
    	}
	}
    switch (*p_opt_param)
    {
      case DATA_PARAMETER_TYPE:
        p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

        p_info->data.len = *p_opt_param;
	/* Fix for SPR # 12557 start */
/* spr 12499 change of maximum data length from 130 to 128 */
	  if(p_info->data.len > 128)
        {
          RC_TRC (("SCCP::SCRC: DATA EXCEEDS 128 bytes.\n"));
                return SS7_FAILURE;
        }
	/* Fix for SPR # 12557 end */

        p_info->data.p = (p_opt_param + O_PARAM_LEN_LEN);

        /* Skip length and whole parameter */
        p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
        SET_DATA_PRESENT(p_info);

        break;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
      case IMPORTANCE_PARAM_TYPE:

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)	/* Ericsson changes */
        if ( (COMPARE_ITU) || (COMPARE_JAPANESE))
	{
          RC_TRC (("SCCP::CL: invalid optional param\n"));
          return SS7_FAILURE;
	}
#else
		/* SPR # 2613 Fix: added COMPARE_BCGR */
		if (COMPARE_ANSI || COMPARE_BCGR)  
        {
          RC_TRC (("SCCP::SCRC: invalid optional param\n"));
          return SS7_FAILURE;
        }
        else
        {
          p_opt_param += O_PARAM_TYPE_LEN; /* Skip parameter name */

          if (*p_opt_param != IMPORTANCE_PARAM_LEN)
          {
            RC_TRC (("SCCP::SCRC: Invalid importance len.\n"));
            return SS7_FAILURE;
          }

          p_info->importance = *(p_opt_param + O_PARAM_LEN_LEN);

          /* Skip length and whole parameter */
          p_opt_param += (*p_opt_param + O_PARAM_LEN_LEN);
          SET_IMPORTANCE_PRESENT(p_info);
          break;
        }
#endif
#endif

      case END_OF_OPT_PARAM_TYPE:
        done = SS7_TRUE;
        break;

      default:
        RC_TRC (("SCCP::SCRC: invalid optional param\n"));
        return SS7_FAILURE;
    }
  }
  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses RLC msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, slr
**    V elements : NONE
**    O elements : NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_rlc 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg;

  if (p_info->m3_data.len < MIN_RLC_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: RLC msg len %d too short\n", 
      p_info->m3_data.len));
    return SS7_FAILURE;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];
  /*p_end = p_info->m3_data.p + p_info->m3_data.len ;*/ /* reverting spr #8530 */

  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* No Optional part */

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_RLC];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_RLC] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {

              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif 
  /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses DT1 msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, seg_reass
**    V elements : data
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_dt1 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
    U8bit *p_co_msg, pointer, *p_addr, *p_end;

  if (p_info->m3_data.len < MIN_DT1_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: DT1 msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;

  /* spr fix 5746 starts */
  p_info->cd_addr.ssn           = SS7_NULL;
/* spr fix 5746 ends  */


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  p_end = p_info->m3_data.p + p_info->m3_data.len ;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* Destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* Segmentation/reassembly */
  p_info->seg_reass = *p_co_msg++;

  /* Mandatory variable part */
  pointer = *p_co_msg;

  p_addr = p_co_msg + pointer;

  if ((p_addr > p_end) || ((p_addr + *p_addr) > p_end))
  {
    RC_TRC (("SCCP::RC: Data pointer/len corrupt\n"));
    return SS7_FAILURE;
  }
  p_info->data.len = *p_addr;

  p_info->data.p = (p_addr + O_PARAM_LEN_LEN);

#if 0 /** SPR# IMP_SPR Start Fix **/
  
/* salil - SPR # 8530 starts */
  

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      p_co_msg = p_info->m3_data.p ;
      opt_pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1] * 0x100 + p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1 + 1] ;
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1] + opt_pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {
              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }

#endif 
  /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses ERR msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, error_cause
**    V elements : NONE
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_err 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  /* SPR 9302 - Fix Start-initialising p_end */
  U8bit *p_co_msg, *p_end = SS7_NULL;
  /* SPR 9302 - Fix Start */

  if (p_info->m3_data.len < MIN_ERR_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: ERR msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;

	/* SPR 9933 - Fix Start */ 	
  p_end = p_info->m3_data.p + p_info->m3_data.len ;
	/* SPR 9933 - Fix End   */ 	
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* Error cause */
  p_info->error_cause = *p_co_msg++;

  /* No Mandatory variable part */

/*spr fix 9635 starts */
#if 0

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
    /* One optional pointer included */
    if (!(*p_co_msg == END_OF_OPT_PARAM_TYPE))
    {
      SC_P_TRC (("SCCP::SCRC: Pointer to optional part missing.\n" ));
      return SS7_FAILURE ;
    }
  }
#endif

#endif /* if 0 */

/* spr fix 9635 ends */

#if 0 /** SPR# IMP_SPR Start Fix **/

	/* Even though ERR contains a pointer to optional parameter, it points to nothing */

  /* spr #8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_ERR];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_ERR] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {

              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;

              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
  
#endif

  /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses IT msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, slr, proto_class, seq_seg, credit
**    V elements : NONE
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_it 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  /* spr #8530 starts */
  U8bit *p_co_msg;
  /* spr #8530 ends */

  if (p_info->m3_data.len < MIN_IT_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: IT msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;

  /*p_end = p_info->m3_data.p + p_info->m3_data.len ;*/ /*reverting spr#8530*/

  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* protocol class */
  p_info->proto_class = *p_co_msg++;

  /* Sequencing/segmenting */
  p_info->seq_seg = *p_co_msg++;
  p_info->seq_seg |= (*p_co_msg++)<<0x08;

  /* Credit */
  p_info->credit = *p_co_msg++;

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_IT];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_IT] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {

              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;

              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif

  /* salil - SPR # 8530 end */
#endif /* if 0 */ /** SPR# IMP_SPR End Fix */
  return SS7_SUCCESS;
}

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/***************************************************************************
**
**      FUNCTION :
**         parses DT2 msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, seq_seg
**    V elements : data
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_dt2 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
    U8bit *p_co_msg, pointer, *p_addr, *p_end ;

  if (p_info->m3_data.len < MIN_DT2_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: DT2 msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  p_end = p_info->m3_data.p + p_info->m3_data.len ;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* Destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* Sequencing/segmenting */
  p_info->seq_seg = GET_2_BYTE_LE (p_co_msg);
  p_co_msg += 2;

  /* Mandatory variable part */
  pointer = *p_co_msg;

  p_addr = p_co_msg + pointer;

  if ((p_addr > p_end) || ((p_addr + *p_addr) > p_end))
  {
    RC_TRC (("SCCP::RC: Data pointer/len corrupt\n"));
    return SS7_FAILURE;
  }
  p_info->data.len = *p_addr;

  p_info->data.p = (p_addr + O_PARAM_LEN_LEN);

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* salil - SPR # 8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
      p_co_msg = p_info->m3_data.p ;
      opt_pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2] * 0x100 + p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2 + 1] ;
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2] + opt_pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {

              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }

#endif

  /* salil - SPR # 8530 end */
#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses AK msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, rsn, credit
**    V elements : NONE
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_ak 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg;

  if (p_info->m3_data.len < MIN_AK_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: AK msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  /* p_end = p_info->m3_data.p + p_info->m3_data.len ; */ /* reverting spr #8530 */

  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* Received sequence number */
  p_info->rsn = (*p_co_msg >> 1);
  p_co_msg++ ;

  /* credit */
  p_info->credit = *p_co_msg++;

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_AK];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_AK] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {
              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif
      
  /* salil - SPR # 8530 end */
#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses ED msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr
**    V elements : data
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/
return_t 
sccp_parse_ed 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
    U8bit *p_co_msg, pointer, *p_addr, *p_end ;

  if (p_info->m3_data.len < MIN_ED_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: ED msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  p_end = p_info->m3_data.p + p_info->m3_data.len ;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* Destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* Mandatory variable part */
  pointer = *p_co_msg;

  p_addr = p_co_msg + pointer;

  if ((p_addr > p_end) || ((p_addr + *p_addr) > p_end))
  {
    RC_TRC (("SCCP::RC: Data pointer/len corrupt\n"));
    return SS7_FAILURE;
  }
  p_info->data.len = *p_addr;
 
  /* SPR 1771: start 
   * maximum ED data length is 32 */
  if (p_info->data.len > MAX_ED_DATA_LEN)
  {
    RC_TRC (("SCCP::RC: ED Data len too long\n"));
    return SS7_FAILURE;
  }
  /* SPR 1771: End */

  p_info->data.p = (p_addr + O_PARAM_LEN_LEN);

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* salil - SPR # 8530 starts */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_ED];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_ED] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {
              case IMPORTANCE_PARAM_TYPE:

                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);

                  break;

              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif
      
  /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses EA msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr
**    V elements : NONE
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_ea 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg;

  if (p_info->m3_data.len < MIN_EA_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: EA msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  /*p_end = p_info->m3_data.p + p_info->m3_data.len ;*/ /* reverting spr#8530 */

  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */
  
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_EA];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_EA] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {
              case IMPORTANCE_PARAM_TYPE:
                  
                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);
                  break;
                  
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif

  /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses RSR msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, slr, reset_cause
**    V elements : NONE
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_rsr 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg;

  if (p_info->m3_data.len < MIN_RSR_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: RSR msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  
  p_info->msg_type =  *p_co_msg++; /* message type code */
  
  /*p_end = p_info->m3_data.p + p_info->m3_data.len ;*/ /*reverting spr #8530 */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  p_info->reset_cause = *p_co_msg++;
  /* No Mandatory variable part */

  /* SPR 1768: End of opt param not necessary */
  
#if 0 /** SPR# IMP_SPR Start Fix **/

/* spr #8530 starts */
  
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_RSR];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_RSR] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {
              case IMPORTANCE_PARAM_TYPE:
                  
                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);
                  break;
                  
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif

  /* salil - SPR # 8530 end */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         parses RSC msg
****************************************************************************
**
**      DESCRIPTION :
**    F elements : msg_type, dlr, slr
**    V elements : NONE
**    O elements :  NONE
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_parse_rsc 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  U8bit *p_co_msg;

  
  if (p_info->m3_data.len < MIN_RSC_MSG_LEN)
  {
    SC_P_TRC (("SCCP::SCRC: RSC msg len %d too short\n", 
      p_info->m3_data.len)) ;
    return SS7_FAILURE ;
  }

  p_info->cd_addr.pc_ind 	= SS7_NULL;
  p_info->cd_addr.ssn_ind 	= SS7_NULL;
  p_info->cd_addr.gti 		= SS7_NULL;
  p_info->cd_addr.rout_ind	= ROUTE_ON_SSN;


  p_co_msg = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG] ;
  /*p_end = p_info->m3_data.p + p_info->m3_data.len ;*/ /*reverting spr #8530 */

  p_info->msg_type =  *p_co_msg++; /* message type code */

  /* destination local refernce */
  p_info->dlr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->dlr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

  /* source local refernce */
  p_info->slr = (U32bit)(*p_co_msg++ & 0x000000FFL);
  p_info->slr |= (U32bit)((*p_co_msg++ << 8) & 0x0000FF00L);
  p_info->slr |= (U32bit)((*p_co_msg++ << 16) & 0x00FF0000L);

#if 0 /** SPR# IMP_SPR Start Fix **/
  
  /* spr #8530 starts */
  
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      /* No mandatory mariable part */

      /* for optional part */
      p_co_msg = p_info->m3_data.p ;
      pointer = p_co_msg[IDX_OPT_PARAM_PTR_IN_RSC];
      p_opt_param = &p_co_msg[IDX_OPT_PARAM_PTR_IN_RSC] + pointer;

      done = SS7_FALSE;

      while (!done)
      {
          if (p_opt_param >= p_end)
          {
              RC_TRC (("SCCP::SCRC: optional param pointer corrupt\n"));
              return SS7_FAILURE;
          }
          if (*p_opt_param != END_OF_OPT_PARAM_TYPE)
          {
              if (((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) >
                          p_end) ||
                      ((p_opt_param + O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN) +
                       *(p_opt_param + O_PARAM_TYPE_LEN) >
                       p_end))
              {
                  RC_TRC (("SCCP::SCRC: one of the param len corrupt\n"));
                  return SS7_FAILURE;
              }
          }

          switch (*p_opt_param)
          {
              case IMPORTANCE_PARAM_TYPE:
                  
                  p_opt_param += O_PARAM_TYPE_LEN;
                  len = *p_opt_param;
                  p_opt_param += O_PARAM_LEN_LEN;

                  if (! (len == IMPORTANCE_PARAM_LEN))
                  {
                      RC_TRC (("SCCP::SCRC: invalid imp param len %d\n",
                                  len));
                      return SS7_FAILURE;
                  }

                  p_info->importance = *p_opt_param++;
                  SET_IMPORTANCE_PRESENT(p_info);
                  break;
                  
              case END_OF_OPT_PARAM_TYPE:
                  done = SS7_TRUE;
                  break;

              default:
                  RC_TRC (("SCCP::SCRC: invalid optional param\n"));
                  return SS7_FAILURE;
          }
      }
  }
#endif

  /* salil - SPR # 8530 end */
#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return SS7_SUCCESS;
}

#endif
#endif
