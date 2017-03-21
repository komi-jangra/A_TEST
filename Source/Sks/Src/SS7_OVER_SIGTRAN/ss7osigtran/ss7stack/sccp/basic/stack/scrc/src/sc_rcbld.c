/***************************************************************************
**
**  FILE NAME:
**      sc_rcbld.c
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
**  08Sep2003 Salil Agrawal           Fixed spr # 12013 
**  13Nov2002 Ashish Sawalkar 		  Fixed SPR IMP_SPR
**  09Aug2002 Ashish Sawalkar 		  Fixed SPR 9543 
**  24Jul2002 Salil Agrawal           Fixed spr # 9341   
**  31Jul2002 Suyash Tripathi         fixed SPR #9404
**  02May2002 Suyash Tripathi         Fixed SPR #8699
**  03Apr2002 Salil Agrawal           fixed SPR #8530
**  04Mar2002 Sachin bhatia           Fixed SPR # 8554
**  06Jan2002 Ashish Sawalkar         Fixed SPR 7970
**  05oct2001 Aman Kapoor             Fixed SPR # 6426
**  11Sep2001 Aman Kapoor			  Fixed SPR # 5929
**  02Nov2001 Pawanish Modi           Modified for DSCCP class 1 and 3 
**  12Oct2000 Ramu Kandula            Modified for broadband - added LUDT 
**                                    and LUDTS messages
**  21Jul2000 Ramu kandula            Fixed SPR # 3825
**  19Jul2000 Ramu kandula            Fixed SPR # 4184
**  01Mar2000 Ramu kandula            Fixed SPR # 2779
**  24Feb2000 Ramu kandula            Fixed SPR # 2731
**  24Feb2000 Ramu Kandula            fixed SPR # 2696
**  17Feb2000 Ramu Kandula            Fixed SPR # 2617
**  15Feb2000 Ramu kandula            Fixed SPR # 2611
**  27Sep'99 Sudipta Pattar    -----  Fixed SPR 1768
**  07Feb'99 Sudipta Pattar    -----  Added Ericsson changes
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"
#ifdef DISTRIBUTED_SCCP
#include "dsccp_proc.h"
#endif

static U32bit sccp_calculate_cl_msg_len
	_ARGS_ ((msg_info_t * p_info));

static U8bit * sccp_fill_m3_trans_req_elem
	_ARGS_ ((U8bit * p_elem, msg_info_t * p_info));

static void sccp_fill_udt_msg_elems
	_ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_udts_msg_elems
	_ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_xudt_msg_elems
	_ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_xudts_msg_elems
	_ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

#ifdef SCCP_BROADBAND
static void sccp_fill_ludt_msg_elems
	_ARGS_ ((U8bit * p_ie, msg_info_t * p_info));
 
static void sccp_fill_ludts_msg_elems
	_ARGS_ ((U8bit * p_ie, msg_info_t * p_info));
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
static void sccp_fill_cr_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_cc_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_cref_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_rlsd_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_rlc_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_dt1_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_err_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_it_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

static void sccp_fill_dt2_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_ak_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_ed_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_ea_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_rsr_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

static void sccp_fill_rsc_msg_elems
  _ARGS_ ((U8bit * p_ie, msg_info_t * p_info));

#endif
#endif

/***************************************************************************
**
**      FUNCTION :
**        builds MTP3 transfer request
****************************************************************************
**
**      DESCRIPTION :
**        calls functions to calculate buf size reqd, fill m3 route label
**        elements and then fills UDT/XUDT/UDTS/XUDTS elements
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_transfer_request 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U32bit msg_len, cl_msg_len;
	U8bit * p_api, * p_elem;
/* SPR 12013 starts */
	U32bit i = 0;
/* SPR 12013 ends */

#ifdef SCCP_INCLUDE_CO_SERVICE
	error_t ecode ;
#endif
#ifdef DISTRIBUTED_SCCP
	extern U8bit dsccp_class1_buff_timer_running;
#endif
/* starts  spr # 9341 */ 
#if 0
    msg_len = API_HEADER_LEN + (((STACK_ANSI == sc_opt.standard) || 
					(STACK_BCGR == sc_opt.standard)) ? 
						MTP3_ANSI_MIN_USER_DATA : MTP3_MIN_USER_DATA);
#ifdef SCCP_CHINESE
	msg_len = API_HEADER_LEN + MTP3_ANSI_MIN_USER_DATA;
#endif
#endif /* end of if 0 */

    msg_len = API_HEADER_LEN + (((STACK_ANSI == sc_opt.standard) || 
                (STACK_BCGR == sc_opt.standard) || (STACK_CHINESE == sc_opt.standard)) ? 
            MTP3_ANSI_MIN_USER_DATA : MTP3_MIN_USER_DATA);

/* end spr # 9341 */    
    
#ifdef SCCP_JAPANESE
	if (COMPARE_JAPANESE)
	{
		msg_len = API_HEADER_LEN + MTP3_JAPANESE_MIN_USER_DATA;
	}
#endif
	cl_msg_len = sccp_calculate_cl_msg_len (p_info);
	msg_len += cl_msg_len;

	if (SS7_NULL == (p_api = sccp_malloc(msg_len)))
	{
		RC_TRC (("SCCP::SCRC: routing failure\n"));

#ifdef SCCP_INCLUDE_CO_SERVICE
    	if (sccp_is_co_msg (p_info->msg_type))
   	 	{
        	p_info->rel_cause = SCCP_RLSDC_NETWORK_CONGESTION;
        	p_info->event = SCCP_ROUTE_FAIL_EVENT;
        	sccp_handle_co_mesg (p_info, &ecode);
    	}
    	else
#endif
    	{
        	p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING;
        	sccp_handle_routing_failure (p_info);
    	}
    	return;
	}

	sccp_fill_api_header (p_api, MTP3_UP_TRANSFER_REQUEST,
	                      MTP3_NUM_ELEM_TRANSFER_REQ, (U16bit)msg_len);

	p_elem = p_api + API_HEADER_LEN;
	p_elem = sccp_fill_m3_trans_req_elem (p_elem, p_info);

	switch (p_info->msg_type)
	{
		case UDT_MSG_TYPE:
			sccp_fill_udt_msg_elems (p_elem, p_info);	
			RC_TRC (("SCCP::SCRC: built UDT msg\n"));
/* spr 12013 starts */
/* removed for performance improvement */
 
			for(i = 0; i< msg_len; i++)
				RC_TRC((" %d ", p_api[i]));

/* spr 12013 ends */
			break;

		case UDTS_MSG_TYPE:
			sccp_fill_udts_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built UDTS msg\n"));
			break;

		case XUDT_MSG_TYPE:
			sccp_fill_xudt_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built XUDT msg\n"));
			break;

		case XUDTS_MSG_TYPE:
			sccp_fill_xudts_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built XUDTS msg\n"));
			break;

#ifdef SCCP_BROADBAND
		case LUDT_MSG_TYPE:
			if (sc_opt.nw_type != SS7_BROADBAND_NETWORK)
			{
				SC_TRC (("SCCP::SCRC: unknown msg type %d in transfer req\n",
			         	p_info->msg_type));
			}
			else
			{
				sccp_fill_ludt_msg_elems (p_elem, p_info);
				RC_TRC (("SCCP::SCRC: built LUDT msg\n"));
			}
			break;
 
		case LUDTS_MSG_TYPE:
			if (sc_opt.nw_type != SS7_BROADBAND_NETWORK)
			{
				SC_TRC (("SCCP::SCRC: unknown msg type %d in transfer req\n",
			         	p_info->msg_type));
			}
			else
			{
				sccp_fill_ludts_msg_elems (p_elem, p_info);
				RC_TRC (("SCCP::SCRC: built LUDTS msg\n"));
			}
			break;
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
		case CR_MSG_TYPE:
			sccp_fill_cr_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built CR msg\n"));
			break;

		case CC_MSG_TYPE:
			sccp_fill_cc_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built CC msg\n"));
			break;

		case CREF_MSG_TYPE:
			sccp_fill_cref_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built CREF msg\n"));
			break;

		case RLSD_MSG_TYPE:
			sccp_fill_rlsd_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built RLSD msg\n"));
			break;

		case RLC_MSG_TYPE:
			sccp_fill_rlc_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built RLC msg\n"));
			break;

		case DT1_MSG_TYPE:
			sccp_fill_dt1_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built DT1 msg\n"));
			break;

		case ERR_MSG_TYPE:
			sccp_fill_err_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built ERR msg\n"));
			break;

		case IT_MSG_TYPE:
			sccp_fill_it_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built IT msg\n"));
			break;

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
		case DT2_MSG_TYPE:
			sccp_fill_dt2_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built DT2 msg\n"));
			break;

		case AK_MSG_TYPE:
			sccp_fill_ak_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built AK msg\n"));
			break;

		case ED_MSG_TYPE:
			sccp_fill_ed_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built ED msg\n"));
			break;

		case EA_MSG_TYPE:
			sccp_fill_ea_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built EA msg\n"));
			break;

		case RSR_MSG_TYPE:
			sccp_fill_rsr_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built RSR msg\n"));
			break;

		case RSC_MSG_TYPE:
			sccp_fill_rsc_msg_elems (p_elem, p_info);
			RC_TRC (("SCCP::SCRC: built RSC msg\n"));
			break;

#endif  /* SCCP_INCLUDE_CO_CLASS3_SERVICE */
#endif  /* SCCP_INCLUDE_CO_SERVICE */

		default:
			SC_TRC (("SCCP::SCRC: unknown msg type %d in transfer req\n",
			         p_info->msg_type));
			break;
	}
#ifdef DISTRIBUTED_SCCP
	if(p_info->p_api != SS7_NULL)
	{
		if(GET_API_ID(p_info->p_api) == SCCP_N_UNITDATA_REQUEST)
		{
			if(((p_info->proto_class & 0x01) == 0x01) && (dsccp_class1_buff_timer_running == SS7_TRUE))
			{
				RC_TRC (("SCCP::SCRC: Buffering Class 1 messages\n"));
				dsccp_buffer_class1_messages(p_api);
				return;
			}
		}
	}
#endif
	sccp_sendto_m3(p_api);

    /* SPR# 7970 : Start Fix */
    /*switch (p_info->proto_class)*/
    switch ((p_info->proto_class) & 0x0f)
    {
        case PROTOCOL_CLASS_0:
            SC_STAT_Q752_INR_ORIG_MSG_CLASS0(p_info->cg_addr.ssn);
			/* SPR - Stats not incrementing */
			SC_STAT_Q752_INR_ORIG_LUDT_XUDT_UDT(p_info->cg_addr.ssn);
			/* SPR - Stats not incrementing */
            break;
        case PROTOCOL_CLASS_1:
            SC_STAT_Q752_INR_ORIG_MSG_CLASS1(p_info->cg_addr.ssn);
			/* SPR - Stats not incrementing */
			SC_STAT_Q752_INR_ORIG_LUDT_XUDT_UDT(p_info->cg_addr.ssn);
			/* SPR - Stats not incrementing */
            break;
    }
    /* SPR# 7970 : End Fix */

}

/***************************************************************************
**
**      FUNCTION :
**         calculates message size required to send transfer request to MTP3
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U32bit 
sccp_calculate_cl_msg_len 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U32bit msg_len = 0;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) && defined (SCCP_ERICSSON_ITU)  /* Ericsson changes */
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE)) 
         CLR_IMPORTANCE_PRESENT(p_info);
#endif
	/* Calculate length of the buffer required */
	switch (p_info->msg_type)
	{
		case UDT_MSG_TYPE:
		case UDTS_MSG_TYPE:
			msg_len += MIN_UDT_MSG_LEN;
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cd_addr);
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cg_addr);
			msg_len += V_PARAM_LEN_LEN + p_info->data.len;

    /* SPR# IMP_SPR Start Fix */
#if 0
    /* salil - spr 8530 starts */
	/* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
					              IMPORTANCE_PARAM_LEN;
			}
#endif
			
            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
    /* salil - spr 8530 ends */
#endif
    /* SPR# IMP_SPR End Fix */
			break;

		case XUDT_MSG_TYPE:
		case XUDTS_MSG_TYPE:
			msg_len += MIN_XUDT_MSG_LEN;
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cd_addr);
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cg_addr);
			msg_len += V_PARAM_LEN_LEN + p_info->data.len;

			/* Optional parameters */
			if (IS_SEGMENTATION_IE_PRESENT(p_info))
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
				              NW_SEGMENTATION_PARAM_LEN;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr # 8530 starts */
				if (IS_IMPORTANCE_PRESENT(p_info))
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
					              IMPORTANCE_PARAM_LEN;
                /* spr #8530 ends */
			}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			if ((COMPARE_ANSI) || (COMPARE_BCGR))
			{
				if (IS_ISNI_PRESENT(p_info))
				{
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
					              p_info->isni.len;
				}
			}
#endif

			/* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr # 8530 starts */
                   if (IS_SEGMENTATION_IE_PRESENT(p_info) || 
                   IS_IMPORTANCE_PRESENT(p_info))
                	msg_len++;
                /* spr # 8530 ends */
            }
#endif
    
/** SPR # 2611 Fix START **/
#if defined(SCCP_ANSI) || defined (SCCP_BCGR)
			if ((COMPARE_ANSI) || (COMPARE_BCGR))
/** SPR # 2611 Fix END **/
			{
				if (IS_SEGMENTATION_IE_PRESENT(p_info) || 
					IS_ISNI_PRESENT(p_info))
					msg_len++;
			}
#endif
			break;


#ifdef SCCP_BROADBAND
		case LUDT_MSG_TYPE:
		case LUDTS_MSG_TYPE:
			msg_len += MIN_LUDT_MSG_LEN ;
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cd_addr) ;
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cg_addr) ;
			msg_len += LONG_V_PARAM_LEN_LEN + p_info->data.len ;

			/* Optional parameters */
			if (IS_SEGMENTATION_IE_PRESENT (p_info))
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
								NW_SEGMENTATION_PARAM_LEN ;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr # 8530 starts */
				if (IS_IMPORTANCE_PRESENT(p_info))
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
					              IMPORTANCE_PARAM_LEN;
                /* spr # 8530 ends */    
			}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			if ((COMPARE_ANSI) || (COMPARE_BCGR))
			{
				if (IS_ISNI_PRESENT(p_info))
				{
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
					              p_info->isni.len;
				}
			}
#endif

			/* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr #8530 starts */
				if (IS_SEGMENTATION_IE_PRESENT(p_info) || 
					IS_IMPORTANCE_PRESENT(p_info))
					msg_len++;
			}
#endif

#if defined(SCCP_ANSI) || defined (SCCP_BCGR)
			if ((COMPARE_ANSI) || (COMPARE_BCGR))
			{
				if (IS_SEGMENTATION_IE_PRESENT(p_info) || 
					IS_ISNI_PRESENT(p_info))
					msg_len++;
			}
#endif
			break ;

#endif /* SCCP_BROADBAND */


#ifdef SCCP_INCLUDE_CO_SERVICE
		case CR_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_CR_MSG_LEN;

			/* Mandatory variable part */
			msg_len += V_PARAM_LEN_LEN + sccp_addr_len(&p_info->cd_addr);

			/* Optional part */

			if ((p_info->proto_class == PROTOCOL_CLASS_3) &&
				(IS_CREDIT_IE_PRESENT(p_info)))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
				CREDIT_PARAM_LEN;
			}
			
			if (IS_CG_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
				sccp_addr_len(&p_info->cg_addr);
			}
			
			if (IS_DATA_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							p_info->data.len;
			}
			if (IS_HOP_COUNTER_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
								HOP_COUNTER_PARAM_LEN;
			}
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined(SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr # 8530 starts */
				if (IS_IMPORTANCE_IE_PRESENT(p_info))
				{
                    msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							IMPORTANCE_PARAM_LEN;
				}
                /* spr # 8530 ends */
			}
#endif
			/* spr # 8530 starts */
            if (((p_info->proto_class == PROTOCOL_CLASS_3)&&
				(IS_CREDIT_IE_PRESENT(p_info)))   ||
				(IS_CG_IE_PRESENT(p_info))    ||
				(IS_DATA_IE_PRESENT(p_info))  ||
				(IS_HOP_COUNTER_IE_PRESENT(p_info)) ||
				(IS_IMPORTANCE_IE_PRESENT(p_info)))
			{
				/* End of optional parameter byte */
				msg_len += O_PARAM_TYPE_LEN;
			}
			break;

		case CC_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_CC_MSG_LEN;

			/* No Mandatory variable part */

			/* Optional part */
			
			if ((p_info->proto_class == PROTOCOL_CLASS_3) &&
				(IS_CREDIT_IE_PRESENT(p_info)))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
								CREDIT_PARAM_LEN;
			}

			if (IS_RG_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							sccp_addr_len(&p_info->cg_addr);
			}

			if (IS_DATA_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							p_info->data.len;
			}
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
			if ( COMPARE_ITU || COMPARE_JAPANESE || COMPARE_ETSI || COMPARE_CHINESE)
            {
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr 8530 starts */
                   if (IS_IMPORTANCE_IE_PRESENT(p_info))
                   {
                        msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                            IMPORTANCE_PARAM_LEN;
                   }
            }
#endif
            /* spr # 8530 starts */
			if (((p_info->proto_class == PROTOCOL_CLASS_3) &&
				(IS_CREDIT_IE_PRESENT(p_info)))   ||
				/*(IS_CG_IE_PRESENT(p_info))    ||*/  /* SPR 10688 */
				(IS_RG_IE_PRESENT(p_info))    ||
				(IS_DATA_IE_PRESENT(p_info))  ||
				(IS_IMPORTANCE_IE_PRESENT(p_info)))
			{
				/* End of optional parameter byte */
				msg_len += O_PARAM_TYPE_LEN;
			}
			break;

		case CREF_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_CREF_MSG_LEN;

			/* No Mandatory variable part */

			/* Optional part */
			if (IS_CD_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							sccp_addr_len(&p_info->cd_addr);
			}
			/* SPR # 6426 fix starts */
			else
			{
			   if (IS_RG_IE_PRESENT(p_info))
			   {
			   	msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							sccp_addr_len(&p_info->cg_addr);
			   }
		  	}
			/* SPR # 6426 fix ends */

			if (IS_DATA_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
							p_info->data.len;
			}
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr #8530 starts */
				if (IS_IMPORTANCE_IE_PRESENT(p_info))
				{
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
								IMPORTANCE_PARAM_LEN;
				}
                /* spr # 8530 ends */
			}
#endif
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr #8530 starts */
				/* SPR #8613 starts */
			if ((IS_CD_IE_PRESENT(p_info))    ||
				(IS_DATA_IE_PRESENT(p_info))  ||
				(IS_IMPORTANCE_IE_PRESENT(p_info)))
			{
				/* End of optional parameter byte */
				msg_len += O_PARAM_TYPE_LEN;
			}
				/* SPR # 8613 ends */
                /* spr # 8530 ends */
			break;

		case RLSD_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_RLSD_MSG_LEN;

			/* No Mandatory variable part */
			/* Optional part */
			if (IS_DATA_IE_PRESENT(p_info))
			{
				msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
								p_info->data.len;
			}
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
			if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
			{
                /* SPR IMP_SPR : Reverting SPR 8530 Change */
                /* spr # 8530 starts */
				if (IS_IMPORTANCE_IE_PRESENT(p_info))
				{
					msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                        IMPORTANCE_PARAM_LEN;
                }
                /* spr # 8530 ends */    
			}
#endif
            /* SPR IMP_SPR : Reverting SPR 8530 Change */
            /* spr # 8530 starts */
			/* SPR # 8618 starts */
			if ((IS_DATA_IE_PRESENT(p_info))  ||
				(IS_IMPORTANCE_IE_PRESENT(p_info)))
			{
				/* End of optional parameter byte */
				msg_len += O_PARAM_TYPE_LEN;
			}
			/* SPR # 8618 ends */
            /* spr # 8530 ends */    
            
			break;

		case RLC_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_RLC_MSG_LEN;

			/* No Mandatory variable part */
    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif

            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

		case ERR_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_ERR_MSG_LEN;

			/* No Mandatory variable part */

    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif
#endif
    		/* SPR# IMP_SPR End Fix */

            /* End of opt params byte */
			/* In ITU - one pointer to optional parameter is required although it is NULL */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */

			break;

		case IT_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_IT_MSG_LEN;

			/* No Mandatory variable part */
            
    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif

            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

		case DT1_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_DT1_MSG_LEN;

			/* Mandatory variable part */
			msg_len += V_PARAM_LEN_LEN + p_info->data.len;

    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            /* Optional parameters */
            
            
               
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
{
msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
IMPORTANCE_PARAM_LEN;
}
#endif

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
{
msg_len++;
}
#endif
             
            
            /* salil - spr 8530 ends */
#endif
   			/* SPR# IMP_SPR End Fix */
            
            /* No Optional part */

			break;

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
		case DT2_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_DT2_MSG_LEN;

			/* Mandatory variable part */
			msg_len += V_PARAM_LEN_LEN + p_info->data.len;

    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif
            
            /* End of opt params byte */          


#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif

            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

		case AK_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_AK_MSG_LEN;

			/* No Mandatory variable part */
            
    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif

            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

		case RSR_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_RSR_MSG_LEN;

			/* No Mandatory variable part */
    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif
#endif
    		/* SPR# IMP_SPR End Fix */

            /* End of opt params byte */
			/* In case of ITU one pointer to optional parameter is required although it is NULL */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */

			break;

		case RSC_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_RSC_MSG_LEN;

            /* No Mandatory variable part */

    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */

            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif

            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif

            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

		case ED_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_ED_MSG_LEN;

			/* Mandatory variable part */
			msg_len += V_PARAM_LEN_LEN + p_info->data.len;

    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif

            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

		case EA_MSG_TYPE:
			/* Fixed part and pointers */
			msg_len += MIN_EA_MSG_LEN;

			/* No Mandatory variable part */
            
    		/* SPR# IMP_SPR Start Fix */
#if 0
            /* salil - spr 8530 starts */
            
            /* Optional parameters */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                    IMPORTANCE_PARAM_LEN;
            }
#endif

            /* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
            if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
            {
                msg_len++;
            }
#endif
            
            /* salil - spr 8530 ends */
#endif
    		/* SPR# IMP_SPR End Fix */

			break;

#endif /* SCCP_INCLUDE_CO_CLASS3_SERVICE */
#endif  /* SCCP_INCLUDE_CO_SERVICE */

		default:
			break;
	}

	return msg_len;
}

/***************************************************************************
**
**      FUNCTION :
**          fills MTP3 header info
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_fill_m3_trans_req_elem 
#ifdef ANSI_PROTO
	(U8bit * p_elem, msg_info_t * p_info)
#else
	(p_elem, p_info)
	U8bit * p_elem ;
	msg_info_t * p_info ;
#endif
{
	pc_t opc;
	U8bit scmg_msg_type; 
	U8bit msg_priority; /** Used for fixing SPR # 2617 **/
	U8bit min_msg_priority, max_msg_priority; /** Used for fixing SPR # 3825 **/

	if (p_info->p_api &&
		(SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api)))
	{
		opc = p_info->cg_addr.pc;
		p_info->dpc = p_info->cd_addr.pc;
	}
	else
	{
#ifdef SCCP_INCLUDE_CO_SERVICE
		if (sccp_is_co_msg (p_info->msg_type))
		{
			opc = p_info->opc;
			if (IS_CD_IE_PRESENT (p_info))
				p_info->dpc = p_info->cd_addr.pc;
		}
		else
#endif
		{
		/*	opc = p_info->dpc; *//* original Change by Amaresh for access opc value */
			/* Added by Amaresh start */
		        opc = p_info->cg_addr.pc;
			p_info->opc = p_info->cg_addr.pc;
			/* Added by Amaresh stop */
			p_info->dpc = p_info->cd_addr.pc;
		}
	}

	/* SIO */
	*p_elem = SCCP_SI;
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		*p_elem++ |= (U8bit)((p_info->p_sp->ssf & 0xf) << 4);
	}
#endif
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/** SPR # 3825 Fix Start **/
		/* Check the importance parameter before setting the msg priority */

		/** SPR # 2617 Fix Start **/
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

		msg_priority = min_msg_priority;
		
		/** SPR # 2731 Fix Start **/
		if (IS_IMPORTANCE_PRESENT(p_info))
		{

			if (p_info->importance < min_msg_priority)
				p_info->importance = min_msg_priority;
			else if (p_info->importance > max_msg_priority)
				p_info->importance = max_msg_priority;

			msg_priority = p_info->importance;
		}
		/** SPR # 2731 Fix End **/

		*p_elem |= (U8bit)((p_info->p_sp->ssf & 0xc) << 4);
		*p_elem++ |= (U8bit)((msg_priority & 0x3) << 4);

		/** SPR # 2617 Fix End **/
		/** SPR # 3825 Fix End **/
	}
#endif
/* spr 9342 starts */

   /* SPR# IMP_SPR Start Fix */
#if 0
   /* spr #8530 starts */ 
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
    /* spr #8530 ends */
#endif
    /* SPR# IMP_SPR End Fix */

#ifdef SCCP_CHINESE
	if(COMPARE_CHINESE)
	{
		PUT_PC(p_elem, p_info->dpc);
		p_elem += PC_SIZE;

		/* OPC */
		PUT_PC(p_elem, opc);
		p_elem += PC_SIZE;

		/* SLS */
		*p_elem++ = p_info->sls;
	}
#endif /* removed #else to fis spr 9341 */
    
#if defined(SCCP_ITU) ||  defined(SCCP_ETSI)
	if ((COMPARE_ITU) || (COMPARE_ETSI))
	{
		/* DPC */
		*p_elem++ = (U8bit)p_info->dpc; /* 8bits of dpc */
		*p_elem   = (U8bit)((p_info->dpc >> 8) & 0x3f); /* 6bits of dpc */

		/* OPC */
		*p_elem++ |= ((U8bit)(opc << 6) & 0xc0); /* 2bits of OPC */
		*p_elem++  = ((U8bit)(opc >> 2) & 0xff); /* 8bits of OPC */
		*p_elem    = ((U8bit)(opc >> 10) & 0x0f); /* 4bits of opc */

		/* SLS */
		*p_elem |= ((U8bit)((p_info->sls) << 4) & 0xf0);
		p_elem++;
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/* DPC */
		PUT_PC(p_elem, p_info->dpc);
		p_elem += PC_SIZE;

		/* OPC */
		PUT_PC(p_elem, opc);
		p_elem += PC_SIZE;

		/* SLS */
		*p_elem++ = p_info->sls;
	}
#endif
#ifdef SCCP_JAPANESE 
	if (COMPARE_JAPANESE)
	{
		/* DPC */
		PUT_PC(p_elem, p_info->dpc);
		p_elem += PC_SIZE;

		/* OPC */
		PUT_PC(p_elem, opc);
		p_elem += PC_SIZE;

		/* SLS */
		/* SPR # 8554 Starts */
		*p_elem++ = p_info->sls & 0x0f;
		/* SPR # 8554 Ends */
	}
#endif
/* removed #endif to fix spr 9341 */
/* end spr #9341 */
	return p_elem;
}

#if defined(SCCP_ANSI) || defined(SCCP_BCGR) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)

/***************************************************************************
**  FUNCTION:
**    Finds the priority of the mssage
**
****************************************************************************
**
**  DESCRIPTION:
**    It finds the message priority
**
***************************************************************************/

U8bit
sccp_get_min_message_priority
#ifdef ANSI_PROTO
  (U8bit msg_type)
#else
  (msg_type)
  U8bit msg_type;
#endif
{
/* SPR 8699 Fix Start */
U8bit priority_val = 0;
/* SPR 8699 Fix End */

/** SPR# 9543 Start Fix **/
#if (defined SCCP_ANSI || defined SCCP_BCGR)
    if ((COMPARE_ANSI) || (COMPARE_BCGR))
		/* SPR 8699 Fix Start */
        /* return (sccp_message_priority [msg_type-1].min_priority) ;*/
		priority_val=sccp_message_priority [msg_type-1].min_priority;			
		/* SPR 8699 Fix End */
#endif

  /* else */

#if (defined SCCP_ITU || defined SCCP_JAPANESE || SCCP_ETSI || SCCP_CHINESE)
    if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
		/* SPR 8699 Fix Start */
        /* return (sccp_message_priority_itu [msg_type-1].min_priority);*/
		priority_val=sccp_message_priority_itu [msg_type-1].min_priority;	
		/* SPR 8699 Fix End */
#endif
/** SPR# 9543 Start Fix **/

/* SPR 8699 Fix Start */
return priority_val;
/* SPR 8699 Fix End */
}

/***************************************************************************
**  FUNCTION:
**    Finds the priority of the mssage
**
****************************************************************************
**
**  DESCRIPTION:
**    It finds the message priority
**
***************************************************************************/

U8bit
sccp_get_max_message_priority
#ifdef ANSI_PROTO
  (U8bit msg_type)
#else
  (msg_type)
  U8bit msg_type;
#endif
{
/* SPR 8699 Fix Start */
U8bit priority_val = 0;
/* SPR 8699 Fix End */

/** SPR# 9543 Start Fix **/
#if (defined SCCP_ANSI || defined SCCP_BCGR)
    if ((COMPARE_ANSI) || (COMPARE_BCGR))
		/* SPR 8699 Fix Start */
        /*return (sccp_message_priority [msg_type-1].max_priority) ;*/
		priority_val=sccp_message_priority [msg_type-1].max_priority;			
		/* SPR 8699 Fix End */
#endif

    /* else */

#if (defined SCCP_ITU || defined SCCP_JAPANESE || SCCP_ETSI || SCCP_CHINESE)
    if ((COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
		/* SPR 8699 Fix Start */
        /*return (sccp_message_priority_itu [msg_type-1].max_priority) ;*/
		/* SPR IMP_SPR Fix Start */
		priority_val=sccp_message_priority_itu [msg_type-1].max_priority;
		/* SPR IMP_SPR Fix End */
		/* SPR 8699 Fix End */
#endif
/** SPR# 9543 End Fix **/

/* SPR 8699 Fix Start */
return priority_val;
/* SPR 8699 Fix End */
}
#endif /** SPR 9543 Fix **/

#if defined(SCCP_ANSI) || defined(SCCP_BCGR) /** SPR 9543 Fix **/
/***************************************************************************
**  FUNCTION:
**    Finds the priority of the SCMG message
**
****************************************************************************
**
**  DESCRIPTION:
**    It finds the message priority of the SCMG message
**
***************************************************************************/


U8bit
sccp_get_min_scmg_message_priority
#ifdef ANSI_PROTO
  (U8bit msg_type)
#else
  (msg_type)
  U8bit msg_type;
#endif
{
  return (sccp_scmg_message_priority [msg_type-1].min_priority) ;
}

/***************************************************************************
**  FUNCTION:
**    Finds the priority of the SCMG message
**
****************************************************************************
**
**  DESCRIPTION:
**    It finds the message priority of the SCMG message
**
***************************************************************************/

U8bit
sccp_get_max_scmg_message_priority
#ifdef ANSI_PROTO
  (U8bit msg_type)
#else
  (msg_type)
  U8bit msg_type;
#endif
{
  return (sccp_scmg_message_priority [msg_type-1].max_priority) ;
}

#endif

/***************************************************************************
**
**      FUNCTION :
**         fills UDT elems
****************************************************************************
**
**      DESCRIPTION :
**         fills F elem msg_type, proto_class and 
**         fill  V elem called party, calling party and data
**
**      NOTE :
**
***************************************************************************/

void 
sccp_fill_udt_msg_elems 
#ifdef ANSI_PROTO
	(U8bit 		* p_ie, 
	 msg_info_t 	* p_info)
#else
	(p_ie, p_info)
	U8bit          * p_ie ;
	msg_info_t     * p_info ;
#endif
{
    U8bit * p_cl_msg = p_ie;

#if 0	
     U8bit msg_importance; /** Used for fixing SPR # 8530 **/
        U8bit default_msg_importance, max_msg_importance;
#endif

    /* Fill fixed params */
	*p_ie++ = UDT_MSG_TYPE;
	*p_ie++ = p_info->proto_class;

	p_ie += NUM_MAND_VAR_IES_IN_UDT; /* Leave space for pointers */

	/* fill variable params */
	/* Called party address */
	/* Set the pointer */
	p_cl_msg[IDX_CD_ADDR_PTR_IN_UDT] = (U8bit)(p_ie -
	                                   (&p_cl_msg[IDX_CD_ADDR_PTR_IN_UDT]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);

	/* Calling party address */
	/* Set the pointer */
	p_cl_msg[IDX_CG_ADDR_PTR_IN_UDT] = (U8bit)(p_ie -
	                                   (&p_cl_msg[IDX_CG_ADDR_PTR_IN_UDT]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cg_addr);

	/* Data */
	/* Set the pointer */
	p_cl_msg[IDX_DATA_PTR_IN_UDT] = (U8bit)(p_ie -
	                                (&p_cl_msg[IDX_DATA_PTR_IN_UDT]));

	/* SPR 9404 - Fix Start */
	/**p_ie++ = p_info->data.len;*/
	*p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
	sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
	p_ie += p_info->data.len;

	/** SPR# IMP_SPR : Start Fix **/
#if 0

    /* salil - spr 8530 starts */
    /* Set the optional param pointer */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {	
        default_msg_importance = sccp_get_min_message_priority(p_info->msg_type);
        max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
        msg_importance =  default_msg_importance ;
        if (IS_IMPORTANCE_PRESENT(p_info))
        {
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_UDT] = (U8bit)(p_ie -
                    (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_UDT]));
            *p_ie++ = IMPORTANCE_PARAM_TYPE;
            *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
            if (p_info->importance > max_msg_importance)
				p_info->importance = max_msg_importance;
            *p_ie++ = p_info->importance;
        }
    }
#endif
	/* End of opt params */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_IMPORTANCE_PRESENT(p_info))
			*p_ie = END_OF_OPT_PARAM_TYPE;
	}
#endif
    /* salil - spr 8530 ends */

#endif
	/** SPR# IMP_SPR End Fix **/
}

/***************************************************************************
**
**      FUNCTION :
**         fills UDTS elem
****************************************************************************
**
**      DESCRIPTION :
**         fills F elem msg_type, ret cause
**         fills V elem called party, calling party, data
**
**      NOTE :
**
***************************************************************************/

void 
sccp_fill_udts_msg_elems 
#ifdef ANSI_PROTO
	(U8bit 		* p_ie, 
	 msg_info_t 	* p_info)
#else
	(p_ie, p_info)
	U8bit          * p_ie ;
	msg_info_t     * p_info ;
#endif
{
	U8bit * p_cl_msg = p_ie;

	/* Fill fixed params */
	*p_ie++ = UDTS_MSG_TYPE;
	*p_ie++ = p_info->ret_cause;

	p_ie += NUM_MAND_VAR_IES_IN_UDTS; /* Leave space for pointers */

	/* fill variable params */
	/* Called party address */
	/* Set the pointer */
	p_cl_msg[IDX_CD_ADDR_PTR_IN_UDTS] = (U8bit)(p_ie -
	                                    (&p_cl_msg[IDX_CD_ADDR_PTR_IN_UDTS]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);

	/* Calling party address */
	/* Set the pointer */
	p_cl_msg[IDX_CG_ADDR_PTR_IN_UDTS] = (U8bit)(p_ie -
	                                    (&p_cl_msg[IDX_CG_ADDR_PTR_IN_UDTS]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cg_addr);

	/* Data */
	/* Set the pointer */
	p_cl_msg[IDX_DATA_PTR_IN_UDTS] = (U8bit)(p_ie -
	                                 (&p_cl_msg[IDX_DATA_PTR_IN_UDTS]));

	/* SPR 9404 - Fix Start */
	/**p_ie++ = p_info->data.len;*/
	*p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
	sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);	
    
}

/***************************************************************************
**
**      FUNCTION :
**        fills XUDT elem
****************************************************************************
**
**      DESCRIPTION :
**       fills F elem msg_type, proto_class, hop counter
**       fills V elem called party, calling party, data
**       fills O elem semgentation, importance and optional param end
**
**      NOTE :
**
***************************************************************************/

void 
sccp_fill_xudt_msg_elems 
#ifdef ANSI_PROTO
	(U8bit 		* p_ie, 
	 msg_info_t 	* p_info)
#else
	(p_ie, p_info)
	U8bit          * p_ie ;
	msg_info_t     * p_info ;
#endif
{
	U8bit * p_cl_msg = p_ie;
        U8bit  max_msg_importance;
        Boolean opt_para_present = SS7_FALSE;

	/* Fill fixed params */
	*p_ie++ = XUDT_MSG_TYPE;
	/** SPR # 2779 Fix Start **/
	/* If the XUDT is locally originated and the segmentation parameter is 
	** present, the always fill the protocol class as 1
	*/
	if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
	{
		if (IS_SEGMENTATION_IE_PRESENT(p_info))
		{
			*p_ie++ = (p_info->proto_class & RET_OPTN_MASK) | PROTOCOL_CLASS_1;
		}
		else
		{
			*p_ie++ = p_info->proto_class;
		}
	}
	else
	{
		*p_ie++ = p_info->proto_class;
	}
	/** SPR # 2779 Fix End **/
	*p_ie++ = p_info->hop_counter;

	p_ie += NUM_MAND_VAR_IES_IN_XUDT; /* Leave space for pointers */

	/* fill variable params */
	/* Called party address */
	/* Set the pointer */
	p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDT] = (U8bit)(p_ie -
	                                    (&p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDT]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);

	/* Calling party address */
	/* Set the pointer */
	p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDT] = (U8bit)(p_ie -
	                                    (&p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDT]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cg_addr);

	/* Data */
	/* Set the pointer */
	p_cl_msg[IDX_DATA_PTR_IN_XUDT] = (U8bit)(p_ie -
	                                 (&p_cl_msg[IDX_DATA_PTR_IN_XUDT]));

	/* SPR 9404 - Fix Start */
	/**p_ie++ = p_info->data.len;*/
	*p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
	sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
	p_ie += p_info->data.len;

	/* Set the optional param pointer */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined ( SCCP_CHINESE )
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI  || COMPARE_CHINESE )
	{
	   if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_IMPORTANCE_PRESENT(p_info))
		{
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT] = (U8bit)(p_ie -
			                          (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT]));
                opt_para_present = SS7_TRUE;
		}
		else
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT] = 0;
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/* Importance */
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_ISNI_PRESENT(p_info))
		{
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT] = (U8bit)(p_ie -
			                          (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT]));
                opt_para_present = SS7_TRUE;
		}
		else
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT] = 0;
	}
#endif

	/* Segmentation param */
	if (IS_SEGMENTATION_IE_PRESENT(p_info))
	{
		*p_ie++ = SEGMENTATION_PARAM_TYPE;
		*p_ie++ = NW_SEGMENTATION_PARAM_LEN;
		/* SPR 10882 - Fix Start */
		/** SPR # 2779 Fix Start **/
		*p_ie++ = (p_info->segment.f_bit << 7) | 
				((((p_info->proto_class & 0x0f)==PROTOCOL_CLASS_1)?1:0) << 6) |
			 	(p_info->segment.rem_seg & 0x0f) | 
				(p_info->segment.spare_bit & 0x30) ;
		/** SPR # 2779 Fix End **/
		/* SPR 10882 - Fix End   */
		*p_ie++ = (U8bit)(p_info->segment.slr);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 8);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 16);
                 opt_para_present = SS7_TRUE;
	}

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) )
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
	{
		/* Importance */
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			*p_ie++ = IMPORTANCE_PARAM_TYPE;
			*p_ie++ = NW_IMPORTANCE_PARAM_LEN;
                         max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
                         if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
			*p_ie++ = p_info->importance;
                         opt_para_present = SS7_TRUE;
		}

	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			*p_ie++ = ISNI_PARAM_TYPE;
			*p_ie++ = p_info->isni.len;
			sccp_memcpy (p_ie, p_info->isni.list, p_info->isni.len);
			p_ie += p_info->isni.len;
                        opt_para_present = SS7_TRUE;
		}
	}
#endif

	/* End of opt params */


if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDT] = (U8bit)SS7_NULL;
  }

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills XUDTS elem
****************************************************************************
**
**      DESCRIPTION :
**       fills F elem msg_type, ret_cause, hop counter
**       fills V elem called party, calling party, data
**       fills O elem semgentation, importance and optional param end
**
**      NOTE :
**
***************************************************************************/

void 
sccp_fill_xudts_msg_elems 
#ifdef ANSI_PROTO
	(U8bit * p_ie, msg_info_t * p_info)
#else
	(p_ie, p_info)
	U8bit * p_ie ;
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg = p_ie;
        U8bit  max_msg_importance;
        Boolean opt_para_present = SS7_FALSE;

	/* Fill fixed params */
	*p_ie++ = XUDTS_MSG_TYPE;
	*p_ie++ = p_info->ret_cause;
	*p_ie++ = p_info->hop_counter;

	p_ie += NUM_MAND_VAR_IES_IN_XUDTS; /* Leave space for pointers */

	/* fill variable params */
	/* Called party address */
	/* Set the pointer */
	p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDTS] = (U8bit)(p_ie -
	                                     (&p_cl_msg[IDX_CD_ADDR_PTR_IN_XUDTS]));

	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);

	/* Calling party address */
	/* Set the pointer */
	p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDTS] = (U8bit)(p_ie -
	                                     (&p_cl_msg[IDX_CG_ADDR_PTR_IN_XUDTS]));
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cg_addr);

	/* Data */
	/* Set the pointer */
	p_cl_msg[IDX_DATA_PTR_IN_XUDTS] = (U8bit)(p_ie -
	                                  (&p_cl_msg[IDX_DATA_PTR_IN_XUDTS]));

	/* SPR 9404 - Fix Start */
	/**p_ie++ = p_info->data.len;*/
	*p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
	sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
	p_ie += p_info->data.len;

	/* Set the optional param pointer */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_IMPORTANCE_PRESENT(p_info))
		{
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS] = (U8bit)(p_ie -
			                          (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS]));
		}
		else
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS] = 0;
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/* Importance */
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_ISNI_PRESENT(p_info))
		{
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS] = (U8bit)(p_ie -
			                          (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS]));
		}
		else
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS] = 0;
	}
#endif

	/* Segmentation param */
	if (IS_SEGMENTATION_IE_PRESENT(p_info))
	{
		*p_ie++ = SEGMENTATION_PARAM_TYPE;
		*p_ie++ = NW_SEGMENTATION_PARAM_LEN;
		/** SPR 10882 - Fix Start **/
		*p_ie++ = ((p_info->segment.f_bit & 0x1) << 7) |
		          (p_info->segment.rem_seg & 0xf ) |
				  (p_info->segment.spare_bit & 0x30);
		/** SPR 10882 - Fix End   **/
		*p_ie++ = (U8bit)(p_info->segment.slr);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 8);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 16);
                 opt_para_present = SS7_TRUE;
	}

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) 
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
	{
		/* Importance */
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			*p_ie++ = IMPORTANCE_PARAM_TYPE;
			*p_ie++ = NW_IMPORTANCE_PARAM_LEN;
                        max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
                        if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
			*p_ie++ = p_info->importance;
                        opt_para_present = SS7_TRUE;
		}

	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			*p_ie++ = ISNI_PARAM_TYPE;
			*p_ie++ = p_info->isni.len;
			sccp_memcpy (p_ie, p_info->isni.list, p_info->isni.len);
			p_ie += p_info->isni.len;
                        opt_para_present = SS7_TRUE;
		}
	}
#endif

 if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_cl_msg[IDX_OPT_PARAM_PTR_IN_XUDTS] = (U8bit)SS7_NULL;
  }

  return;
}

#ifdef SCCP_BROADBAND
/***************************************************************************
**
**      FUNCTION :
**        fills LUDT elem
****************************************************************************
**
**      DESCRIPTION :
**       fills F elem msg_type, proto_class, hop counter
**       fills V elem called party, calling party, data
**       fills O elem semgentation, importance and optional param end
**
**      NOTE :
**
***************************************************************************/

void 
sccp_fill_ludt_msg_elems 
#ifdef ANSI_PROTO
	(U8bit 		* p_ie, 
	 msg_info_t 	* p_info)
#else
	(p_ie, p_info)
	U8bit          * p_ie ;
	msg_info_t     * p_info ;
#endif
{
	U8bit * p_cl_msg = p_ie;
	U16bit length;
        U8bit  max_msg_importance;
        Boolean opt_para_present = SS7_FALSE;

	/* Fill fixed params */
	*p_ie++ = LUDT_MSG_TYPE;
	*p_ie++ = p_info->proto_class;
	*p_ie++ = p_info->hop_counter;

	/* Leave space for pointers */
	p_ie += NUM_MAND_VAR_IES_IN_LUDT * LONG_V_PARAM_LEN_LEN; 

	/* fill variable params */
	/* Called party address */
	/* Set the pointer */
	length = (U16bit)(p_ie - (&p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDT+1])) ;
	p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDT]   = (U8bit)((length&0x00ff)>>0) ;
	p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDT+1] = (U8bit)((length&0xff00)>>8) ;
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);

	/* Calling party address */
	/* Set the pointer */
	length = (U16bit)(p_ie - (&p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDT+1])) ;
	p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDT]   = (U8bit)((length&0x00ff)>>0) ;
	p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDT+1] = (U8bit)((length&0xff00)>>8) ;
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cg_addr);

	/* Data */
	/* Set the pointer */
	length = (U16bit)(p_ie - (&p_cl_msg[IDX_DATA_PTR_IN_LUDT+1])) ;
	p_cl_msg[IDX_DATA_PTR_IN_LUDT]   = (U8bit)((length&0x00ff)>>0) ;
	p_cl_msg[IDX_DATA_PTR_IN_LUDT+1] = (U8bit)((length&0xff00)>>8) ;
	/* Fill length of the data parameter */
	*p_ie++ = ((p_info->data.len) & 0x00ff)>>0 ;
	*p_ie++ = ((p_info->data.len) & 0xff00)>>8 ;
	sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
	p_ie += p_info->data.len;

	/* Set the optional param pointer */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_IMPORTANCE_PRESENT(p_info))
		{
			length = (U16bit)(p_ie - (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1])) ;
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT]   = (U8bit)((length&0x00ff)>>0);
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1] = (U8bit)((length&0xff00)>>8);
		}
		else
		{
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT]   = 0;
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1] = 0;
		}
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_ISNI_PRESENT(p_info))
		{
			length = (U16bit)(p_ie - (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1])) ;
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT]   = (U8bit)((length&0x00ff)>>0);
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1] = (U8bit)((length&0xff00)>>8);
		}
		else
		{
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT]   = 0;
			p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1] = 0;
		}
	}
#endif

	/* Segmentation param */
	if (IS_SEGMENTATION_IE_PRESENT(p_info))
	{
		*p_ie++ = SEGMENTATION_PARAM_TYPE;
		*p_ie++ = NW_SEGMENTATION_PARAM_LEN;
		/** SPR # 2779 Fix Start **/
		*p_ie++ = (p_info->segment.f_bit << 7) | 
				((((p_info->proto_class & 0x0f)==PROTOCOL_CLASS_1)?1:0) << 6) |
			 	(p_info->segment.rem_seg & 0x0f);
		/** SPR # 2779 Fix End **/
		*p_ie++ = (U8bit)(p_info->segment.slr);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 8);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 16);
                opt_para_present = SS7_TRUE;
	}

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) 
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
	{
           max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
		/* Importance */
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			*p_ie++ = IMPORTANCE_PARAM_TYPE;
			*p_ie++ = NW_IMPORTANCE_PARAM_LEN;
                         max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
                         if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;  
			*p_ie++ = p_info->importance;
                         opt_para_present = SS7_TRUE;
		}
 
	}
#endif

 if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT] = (U8bit)SS7_NULL;
    p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDT+1] = (U8bit)SS7_NULL;
  }


	return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills LUDTS elem
****************************************************************************
**
**      DESCRIPTION :
**       fills F elem msg_type, ret_cause, hop counter
**       fills V elem called party, calling party, data
**       fills O elem semgentation, importance and optional param end
**
**      NOTE :
**
***************************************************************************/

void 
sccp_fill_ludts_msg_elems 
#ifdef ANSI_PROTO
	(U8bit * p_ie, msg_info_t * p_info)
#else
	(p_ie, p_info)
	U8bit * p_ie ;
	msg_info_t * p_info ;
#endif
{
	U8bit * p_cl_msg = p_ie;
        U8bit  max_msg_importance;
	U16bit length;
        Boolean opt_para_present = SS7_FALSE;

	/* Fill fixed params */
	*p_ie++ = LUDTS_MSG_TYPE;
	*p_ie++ = p_info->ret_cause;
	*p_ie++ = p_info->hop_counter;

	/* Leave space for pointers */
	p_ie += NUM_MAND_VAR_IES_IN_LUDTS * LONG_V_PARAM_LEN_LEN; 

	/* fill variable params */
	/* Called party address */
	/* Set the pointer */
	length = (U16bit)(p_ie - (&p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDTS+1])) ;
	p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDTS]   = (U8bit)((length&0x00ff)>>0) ;
	p_cl_msg[IDX_CD_ADDR_PTR_IN_LUDTS+1] = (U8bit)((length&0xff00)>>8) ;
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);
 
	/* Calling party address */
	/* Set the pointer */
	length = (U16bit)(p_ie - (&p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDTS+1])) ;
	p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDTS]   = (U8bit)((length&0x00ff)>>0) ;
	p_cl_msg[IDX_CG_ADDR_PTR_IN_LUDTS+1] = (U8bit)((length&0xff00)>>8) ;
	p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cg_addr);

	/* Data */
	/* Set the pointer */
	length = (U16bit)(p_ie - (&p_cl_msg[IDX_DATA_PTR_IN_LUDTS+1])) ;
	p_cl_msg[IDX_DATA_PTR_IN_LUDTS]   = (U8bit)((length&0x00ff)>>0) ;
	p_cl_msg[IDX_DATA_PTR_IN_LUDTS+1] = (U8bit)((length&0xff00)>>8) ;
	/* Fill length of the data parameter */
	*p_ie++ = ((p_info->data.len) & 0x00ff)>>0 ;
	*p_ie++ = ((p_info->data.len) & 0xff00)>>8 ;
	sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
	p_ie += p_info->data.len;

	/* Set the optional param pointer */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
        if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_IMPORTANCE_PRESENT(p_info))
        {
            length = (U16bit)(p_ie - (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1])) ;
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS]  = (U8bit)((length&0x00ff)>>0);
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1] =
			                                        (U8bit)((length&0xff00)>>8);
        }
        else
        {
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS]   = 0;
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1] = 0;
        }

	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/* Importance */
		if (IS_SEGMENTATION_IE_PRESENT(p_info) || IS_ISNI_PRESENT(p_info))
		{
            length = (U16bit)(p_ie - (&p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1])) ;
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS]  = (U8bit)((length&0x00ff)>>0);
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1] =
			                                        (U8bit)((length&0xff00)>>8);
		}
		else
        {
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS]   = 0;
            p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1] = 0;
        }
	}
#endif

	/* Segmentation param */
	if (IS_SEGMENTATION_IE_PRESENT(p_info))
	{
		*p_ie++ = SEGMENTATION_PARAM_TYPE;
		*p_ie++ = NW_SEGMENTATION_PARAM_LEN;
		*p_ie++ = ((p_info->segment.f_bit & 0x1) << 7) |
		          (p_info->segment.rem_seg & 0xf );
		*p_ie++ = (U8bit)(p_info->segment.slr);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 8);
		*p_ie++ = (U8bit)(p_info->segment.slr >> 16);
                 opt_para_present = SS7_TRUE;
	}

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) 
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
	{

		/* Importance */
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			*p_ie++ = IMPORTANCE_PARAM_TYPE;
			*p_ie++ = NW_IMPORTANCE_PARAM_LEN;
                         max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
                         if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
			*p_ie++ = p_info->importance;
                        opt_para_present = SS7_TRUE;
		}

	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (IS_ISNI_PRESENT(p_info))
		{
			*p_ie++ = ISNI_PARAM_TYPE;
			*p_ie++ = p_info->isni.len;
			sccp_memcpy (p_ie, p_info->isni.list, p_info->isni.len);
			p_ie += p_info->isni.len;
                        opt_para_present = SS7_TRUE;
		}
	}
#endif

 if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS] = (U8bit)SS7_NULL;
    p_cl_msg[IDX_OPT_PARAM_PTR_IN_LUDTS+1] = (U8bit)SS7_NULL;
  }


	return;
}

#endif /* SCCP_BROADBAND */


/***************************************************************************
**
**      FUNCTION :
**         calculates SCCP address length
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit 
sccp_addr_len 
#ifdef ANSI_PROTO
	(sccp_addr_t * p_addr)
#else
	(p_addr)
	sccp_addr_t * p_addr ;
#endif
{
	U8bit len = ADDR_IND_LEN;

	if (p_addr->ssn_ind) len++;
	if (p_addr->pc_ind)  len += PC_SIZE;
	if (p_addr->gti)     len += p_addr->gt_len;

	return len;
}

/***************************************************************************
**
**      FUNCTION :
**         copies one sccp address to another
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void sccp_copy_sccp_addr
#ifdef ANSI_PROTO
	(sccp_addr_t * p_addr1, sccp_addr_t * p_addr2)
#else
	(p_addr1, p_addr2)
	sccp_addr_t * p_addr1;
	sccp_addr_t * p_addr2;
#endif
{
	p_addr2->pc_ind = p_addr1->pc_ind;
	p_addr2->ssn_ind = p_addr1->ssn_ind;
	p_addr2->gti = p_addr1->gti;
	p_addr2->rout_ind = p_addr1->rout_ind;
	p_addr2->nat_ind = p_addr1->nat_ind;

	if (p_addr1->pc_ind) p_addr2->pc = p_addr1->pc;

	if (p_addr1->ssn_ind) p_addr2->ssn = p_addr1->ssn;

	if (p_addr1->gti)
	{
		p_addr2->gt_len = p_addr1->gt_len;
		sccp_memcpy (&(p_addr2->gt[0]), &(p_addr1->gt[0]), p_addr1->gt_len);
	}
}

/***************************************************************************
**
**      FUNCTION :
**         encodes sccp address
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

U8bit * 
sccp_encode_sccp_addr 
#ifdef ANSI_PROTO
	(U8bit * p_elem, sccp_addr_t * p_addr)
#else
	(p_elem, p_addr)
	U8bit * p_elem ;
	sccp_addr_t * p_addr ;
#endif
{
	U8bit len = ADDR_IND_LEN, * p_len;
	U8bit addr_ind = 0, * p_addr_ind;

	p_len = p_elem; p_elem++;
	p_addr_ind = p_elem; p_elem++;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	{
		if (p_addr->pc_ind)
		{
			PUT_PC(p_elem, p_addr->pc);
			p_elem += PC_SIZE;
			len += PC_SIZE;
			addr_ind |= ADDR_IND_PC_MASK;
		}

		if (p_addr->ssn_ind)
		{
			*p_elem++ = p_addr->ssn;
			len++;
			addr_ind |= ADDR_IND_SSN_MASK;
		}
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		if (p_addr->ssn_ind)
		{
			*p_elem++ = p_addr->ssn;
			len++;
			addr_ind |= ADDR_IND_SSN_MASK;
		}

		if (p_addr->pc_ind)
		{
			PUT_PC(p_elem, p_addr->pc);
			p_elem += PC_SIZE;
			len += PC_SIZE;
			addr_ind |= ADDR_IND_PC_MASK;
		}
	}
#endif

	if (p_addr->gti)
	{
		sccp_memcpy (p_elem, &p_addr->gt[0], p_addr->gt_len);
		p_elem += p_addr->gt_len;
		len += p_addr->gt_len;
		addr_ind |= (p_addr->gti & 0xf) << 2;
	}

	addr_ind |= (p_addr->rout_ind & 0x1) << 6;
	addr_ind |= (p_addr->nat_ind & 0x1) << 7;

	*p_len = len;
	*p_addr_ind = addr_ind;

	return p_elem;
}

#ifdef SCCP_INCLUDE_CO_SERVICE

/***************************************************************************
**
**      FUNCTION :
**        fills CR message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, slr, proto_class
**       fills V elements : called party
**       fills O elements : credit, calling party, data, hop_counter
**              and for ITU-T importance.
**
**      NOTE :
**        Required in CLASS 2/3 services.
**        Message not supported in ETSI
***************************************************************************/

void 
sccp_fill_cr_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;
  Boolean opt_para_present;
  U8bit  max_msg_importance;

  p_co_msg = p_ie;
  opt_para_present = SS7_FALSE;

  /* Fill fixed params */
  *p_ie++ = CR_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 16) & 0x000000FFL);
  *p_ie++ = p_info->proto_class;

  p_ie += (NUM_MAND_VAR_IES_IN_CR + 1); /* Leave space for pointers */

  /* fill variable params */
  /* Called party address */
  /* Set the pointer */
  p_co_msg[IDX_CD_ADDR_PTR_IN_CR] = (U8bit)(p_ie -
                                    (&p_co_msg[IDX_CD_ADDR_PTR_IN_CR]));

  p_ie = sccp_encode_sccp_addr(p_ie, &p_info->cd_addr);


  /* Set the pointer for optional part */
  p_co_msg[IDX_OPT_PARAM_PTR_IN_CR] = (U8bit)(p_ie -
                                    (&p_co_msg[IDX_OPT_PARAM_PTR_IN_CR]));

  if (p_info->proto_class == PROTOCOL_CLASS_3)
  {
    if (IS_CREDIT_IE_PRESENT (p_info))
    {
      /* credit */
      *p_ie++ = CREDIT_PARAM_TYPE;
      *p_ie++ = CREDIT_PARAM_LEN;
      *p_ie++ = p_info->credit;
      opt_para_present = SS7_TRUE;
    }
  }

  if (IS_CG_IE_PRESENT (p_info))
  {
    /* calling party address */
    *p_ie++ = CG_PARAM_TYPE;
    p_ie = sccp_encode_sccp_addr (p_ie, &p_info->cg_addr);
    opt_para_present = SS7_TRUE;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    /* data */
    *p_ie++ = DATA_PARAMETER_TYPE;
    /* SPR 9404 - Fix Start */
    /**p_ie++ = p_info->data.len;*/
    *p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
    sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
    p_ie += p_info->data.len;
    opt_para_present = SS7_TRUE;
  }

  if (IS_HOP_COUNTER_IE_PRESENT (p_info))
  {
    /* hop counter */
    *p_ie++ = HOP_COUNTER_PARAM_TYPE;
    *p_ie++ = HOP_COUNTER_PARAM_LEN;
    *p_ie++ = p_info->hop_counter;
    opt_para_present = SS7_TRUE;
  }

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
  {
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      /* importance */
       max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = IMPORTANCE_PARAM_LEN;
       if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
      *p_ie++ = p_info->importance;
      opt_para_present = SS7_TRUE;
    }
  }
#endif

  if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_co_msg[IDX_OPT_PARAM_PTR_IN_CR] = (U8bit)SS7_NULL;
  }

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills CC message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, slr, proto_class
**       fills V elements : NONE
**       fills O elements : credit, called party, data
**              and for ITU-T importance.
**
**      NOTE :
**        Required in CLASS 2/3 services.
***************************************************************************/

void 
sccp_fill_cc_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;
  Boolean opt_para_present;
 
    U8bit  max_msg_importance;

  p_co_msg = p_ie;
  opt_para_present = SS7_FALSE;

  /* Fill fixed params */
  *p_ie++ = CC_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 16) & 0x000000FFL);

  *p_ie++ = p_info->proto_class;

  p_ie += (NUM_MAND_VAR_IES_IN_CC + 1); /* Leave space for pointers */

  /* No variable mandatory parameter */


  /* Set the pointer for optional part */
  p_co_msg[IDX_OPT_PARAM_PTR_IN_CC] = (U8bit)(p_ie -
                                    (&p_co_msg[IDX_OPT_PARAM_PTR_IN_CC]));

  if (p_info->proto_class == PROTOCOL_CLASS_3)
  {
    if (IS_CREDIT_IE_PRESENT (p_info))
    {
      /* credit */
      *p_ie++ = CREDIT_PARAM_TYPE;
      *p_ie++ = CREDIT_PARAM_LEN;
      *p_ie++ = p_info->credit;
      opt_para_present = SS7_TRUE;
    }
  }

  if (IS_RG_IE_PRESENT (p_info))
  {
    /* called party address */
    *p_ie++ = CD_PARAM_TYPE;
    p_ie = sccp_encode_sccp_addr (p_ie, &p_info->cg_addr);
    opt_para_present = SS7_TRUE;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    /* data */
    *p_ie++ = DATA_PARAMETER_TYPE;
    /* SPR 9404 - Fix Start */
    /**p_ie++ = p_info->data.len;*/
    *p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
    sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
    p_ie += p_info->data.len;
    opt_para_present = SS7_TRUE;
  }

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) 

  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
  {
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      /* importance */
       max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = IMPORTANCE_PARAM_LEN;
       if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
      *p_ie++ = p_info->importance;
      opt_para_present = SS7_TRUE;
    }
  }
 
#endif

  if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_co_msg[IDX_OPT_PARAM_PTR_IN_CC] = (U8bit)SS7_NULL;
  }

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills CREF message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, ref_cause
**       fills V elements : NONE
**       fills O elements : called party, data
**              and for ITU-T importance.
**
**      NOTE :
**        Required in CLASS 2/3 services.
***************************************************************************/

void 
sccp_fill_cref_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;
  Boolean opt_para_present;
    U8bit  max_msg_importance;

  p_co_msg = p_ie;
  opt_para_present = SS7_FALSE;

  /* Fill fixed params */
  *p_ie++ = CREF_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = p_info->rel_cause;

  p_ie += (NUM_MAND_VAR_IES_IN_CREF + 1); /* Leave space for pointers */

  /* No variable mandatory parameter */


  /* Set the pointer for optional part */
  p_co_msg[IDX_OPT_PARAM_PTR_IN_CREF] = (U8bit)(p_ie -
                                    (&p_co_msg[IDX_OPT_PARAM_PTR_IN_CREF]));

  if (IS_CD_IE_PRESENT (p_info))
  {
    /* called party address */
    *p_ie++ = CD_PARAM_TYPE;
    p_ie = sccp_encode_sccp_addr (p_ie, &p_info->cd_addr);
    opt_para_present = SS7_TRUE;
  }
  /* SPR #6426 Fix Starts */
  else
  {
 	if(IS_RG_IE_PRESENT(p_info))
	{
	  *p_ie++ = CD_PARAM_TYPE;
           p_ie = sccp_encode_sccp_addr (p_ie, &p_info->cg_addr);
          opt_para_present = SS7_TRUE;
	}
  }
  /* SPR #6426 Fix Ends */

  if (IS_DATA_IE_PRESENT (p_info))
  {
    /* data */
    *p_ie++ = DATA_PARAMETER_TYPE;
    /* SPR 9404 - Fix Start */
    /**p_ie++ = p_info->data.len;*/
    *p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
    sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
    p_ie += p_info->data.len;
    opt_para_present = SS7_TRUE;
  }

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) 
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI )
  {
    max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      /* importance */
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = IMPORTANCE_PARAM_LEN;
      max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
      if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
      *p_ie++ = p_info->importance;
      opt_para_present = SS7_TRUE;
    }

  }
#endif

  if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_co_msg[IDX_OPT_PARAM_PTR_IN_CREF] = (U8bit)SS7_NULL;
  }

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills RLSD message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, slr, rel_cause
**       fills V elements : NONE
**       fills O elements : data
**              and for ITU-T importance.
**
**      NOTE :
**        Required in CLASS 2/3 services.
***************************************************************************/

void 
sccp_fill_rlsd_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;
  Boolean opt_para_present;
  U8bit  max_msg_importance;
  
  opt_para_present=SS7_FALSE;
  p_co_msg = p_ie;
  /* Fill fixed params */
  *p_ie++ = RLSD_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 16) & 0x000000FFL);

  /* SPR 5929 . Fix Starts */
  if(p_info->p_ccb != SS7_NULL)
  {
	if((p_info->p_ccb->c_status & RELEASE_CAUSE_SET) != RELEASE_CAUSE_SET)
	{
		p_info->p_ccb->c_status |= RELEASE_CAUSE_SET;
  		*p_ie++ = p_info->rel_cause;
		p_info->p_ccb->rel_cause = p_info->rel_cause;
	}
	else
	{
		*p_ie++ = p_info->p_ccb->rel_cause;
	}
  }	
  else
  {
	*p_ie++ = p_info->rel_cause;
  }
  /* SPR 5929 . Fix Ends */
  p_ie += (NUM_MAND_VAR_IES_IN_RLSD + 1); /* Leave space for pointers */

  /* No variable mandatory parameter */


  /* Set the pointer for optional part */
  p_co_msg[IDX_OPT_PARAM_PTR_IN_RLSD] = (U8bit)(p_ie -
                                    (&p_co_msg[IDX_OPT_PARAM_PTR_IN_RLSD]));

  if (IS_DATA_IE_PRESENT (p_info))
  {
    /* data */
    *p_ie++ = DATA_PARAMETER_TYPE;
    /* SPR 9404 - Fix Start */
    /**p_ie++ = p_info->data.len;*/
    *p_ie++ = (U8bit)p_info->data.len;
	/* SPR 9404 - Fix End   */
    sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);
    p_ie += p_info->data.len;
    opt_para_present = SS7_TRUE;
  }

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) 
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI  )
  {
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      /* importance */
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = IMPORTANCE_PARAM_LEN;
      max_msg_importance = sccp_get_max_message_priority(p_info->msg_type);
      if (p_info->importance > max_msg_importance)
                                p_info->importance = max_msg_importance;
      *p_ie++ = p_info->importance;
      opt_para_present = SS7_TRUE;
    }

  }
#endif

  if (opt_para_present)
  {
    /* at least one optional parameter is included.
       put the end of optional parameter */
    *p_ie = END_OF_OPT_PARAM_TYPE;
  }
  else
  {
    /* None of the optional parameter included.
       Set the pointer for optional part to SS7_NULL */
    p_co_msg[IDX_OPT_PARAM_PTR_IN_RLSD] = (U8bit)SS7_NULL;
  }

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills RLC message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, slr
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 2/3 services.
***************************************************************************/

void 
sccp_fill_rlc_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{

#if 0
    /* spr # 8530 starts */
    U8bit   *p_co_msg = p_ie;
    /* spr # 8530 ends */
#endif

  /* Fill fixed params */
  *p_ie++ = RLC_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 16) & 0x000000FFL);

  /* No variable mandatory parameter */

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */
  
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
      p_ie = p_ie + NUM_MAND_VAR_IES_IN_RLC;
      p_co_msg[IDX_OPT_PARAM_PTR_IN_RLC] = (U8bit)(p_ie -
              (&p_co_msg[IDX_OPT_PARAM_PTR_IN_RLC]));
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
      *p_ie++ = p_info->importance;
      /* End of opt params */
      *p_ie = END_OF_OPT_PARAM_TYPE;
  }
#endif

 /* spr #8530 ends */ 

#endif /* if 0 */ /** SPR# IMP_SPR  End Fix **/

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills ERR message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, error_cause
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 2/3 services.
***************************************************************************/

void 
sccp_fill_err_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{ 
    /* spr # 8530 starts */
    U8bit   *p_co_msg = p_ie;
    /* spr # 8530 ends */

  p_co_msg = p_ie;

  /* Fill fixed params */
  *p_ie++ = ERR_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = p_info->error_cause;

  /* No variable mandatory parameter */

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

/*spr fix 9670 starts */ 
/*      p_ie++;   */
/* spr fix 9670 ends */
      p_ie = p_ie + NUM_MAND_VAR_IES_IN_ERR;
      p_co_msg[IDX_OPT_PARAM_PTR_IN_ERR] = (U8bit)(p_ie -
              (&p_co_msg[IDX_OPT_PARAM_PTR_IN_ERR]));
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
      *p_ie++ = p_info->importance;
      /* End of opt params */
      *p_ie = END_OF_OPT_PARAM_TYPE;
  }
#endif

  /* spr #8530 ends */
#endif /* if 0 */ 

	/** SPR# IMP_SPR End Fix **/

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
	p_co_msg[IDX_OPT_PARAM_PTR_IN_ERR] = SS7_NULL;
#endif


  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills IT message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, slr, proto_class, seq_seg, credit
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 2/3 services.
***************************************************************************/

void 
sccp_fill_it_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
    /* spr # 8530 starts */
    /* U8bit   *p_co_msg = p_ie; */ /* SPR# IMP_SPR Fix */
    /* spr # 8530 ends */

  /* Fill fixed params */
  *p_ie++ = IT_MSG_TYPE;
  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 16) & 0x000000FFL);

  *p_ie++ = p_info->proto_class;

  if (p_info->proto_class == PROTOCOL_CLASS_3)
  {
    *p_ie++ = (U8bit)(p_info->seq_seg & 0x000000FFL);
    *p_ie++ = (U8bit)((p_info->seq_seg >> 8) & 0x000000FFL);

    *p_ie   = p_info->credit;
  }
  else
  {
    *p_ie++ = (U8bit)SS7_NULL;
    *p_ie++ = (U8bit)SS7_NULL;
    *p_ie   = (U8bit)SS7_NULL;
  }

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      p_ie++;
      p_ie = p_ie + NUM_MAND_VAR_IES_IN_IT;
      p_co_msg[IDX_OPT_PARAM_PTR_IN_IT] = (U8bit)(p_ie -
              (&p_co_msg[IDX_OPT_PARAM_PTR_IN_IT]));
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
      *p_ie++ = p_info->importance;
      /* End of opt params */
      *p_ie = END_OF_OPT_PARAM_TYPE;
  }
#endif

  /* spr #8530 ends */

#endif /* if 0 */ /* SPR# IMP_SPR End fix */
  
  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills DT1 message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, seg_reass
**       fills V elements : data
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 2 services.
***************************************************************************/

void 
sccp_fill_dt1_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;

  p_co_msg = p_ie;

  /* Fill fixed params */
  *p_ie++ = DT1_MSG_TYPE;

  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = p_info->seg_reass;

  p_ie += (NUM_MAND_VAR_IES_IN_DT1); /* Leave space for pointers */



  /* Set the pointer for mandatory variable part */
  p_co_msg[IDX_DATA_PTR_IN_DT1] = (U8bit)(p_ie -
                                       (&p_co_msg[IDX_DATA_PTR_IN_DT1]));

  /* data */
  /* SPR 9404 - Fix Start */
  /**p_ie++ = p_info->data.len;*/
  *p_ie++ = (U8bit)p_info->data.len;
  /* SPR 9404 - Fix End   */
  sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      if (IS_IMPORTANCE_PRESENT(p_info))
      {
          p_ie += p_info->data.len;
          p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1] = (U8bit)((p_ie -
                      (&p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1]))>>8);
          p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1+1] = (U8bit)((p_ie -
                      (&p_co_msg[IDX_OPT_PARAM_PTR_IN_DT1])));
          *p_ie++ = IMPORTANCE_PARAM_TYPE;
          *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
          *p_ie++ = p_info->importance;
          *p_ie = END_OF_OPT_PARAM_TYPE;
      }
  }
#endif
  /* spr #8530 ends */
          /* End of opt params */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return;
}

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/***************************************************************************
**
**      FUNCTION :
**        fills DT2 message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, seq_seg
**       fills V elements : data
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 3 services.
***************************************************************************/

void 
sccp_fill_dt2_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;

  p_co_msg = p_ie;

  /* Fill fixed params */
  *p_ie++ = DT2_MSG_TYPE;

  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (U8bit)(p_info->seq_seg & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->seq_seg >> 8) & 0x000000FFL);

  p_ie += (NUM_MAND_VAR_IES_IN_DT2); /* Leave space for pointers */



  /* Set the pointer for mandatory variable part */
  p_co_msg[IDX_DATA_PTR_IN_DT2] = (U8bit)(p_ie -
                                       (&p_co_msg[IDX_DATA_PTR_IN_DT2]));

  /* data */
  /* SPR 9404 - Fix Start */
  /**p_ie++ = p_info->data.len;*/
  *p_ie++ = (U8bit)p_info->data.len;
  /* SPR 9404 - Fix End   */
  sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      if (IS_IMPORTANCE_PRESENT(p_info))
      {
          p_ie += p_info->data.len; 
          p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2] = (U8bit)((p_ie -
                      (&p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2]))>>8);
          p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2+1] = (U8bit)((p_ie -
                      (&p_co_msg[IDX_OPT_PARAM_PTR_IN_DT2])));
          *p_ie++ = IMPORTANCE_PARAM_TYPE;
          *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
          *p_ie++ = p_info->importance;
          
          /* End of opt params */
          *p_ie = END_OF_OPT_PARAM_TYPE;
      }
  }
#endif

  /* spr #8530 ends */
#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/
  
  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills AK message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, rsn, credit
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 3 services.
***************************************************************************/

void 
sccp_fill_ak_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
#if 0
    /* spr # 8530 starts */
    U8bit   *p_co_msg = p_ie;
    /* spr # 8530 ends */
#endif

  /* Fill fixed params */
  *p_ie++ = AK_MSG_TYPE;

  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (p_info->rsn << 1) & 0xFE ;
  *p_ie++ = p_info->credit;

  /* No variable mandatory parameter */

#if 0 /** SPR# IMP_SPR Start Fix **/
  /* spr #8530 starts */
  
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

      p_ie = p_ie + NUM_MAND_VAR_IES_IN_AK;
      p_co_msg[IDX_OPT_PARAM_PTR_IN_AK] = (U8bit)(p_ie -
              (&p_co_msg[IDX_OPT_PARAM_PTR_IN_AK]));
      *p_ie++ = IMPORTANCE_PARAM_TYPE;
      *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
      *p_ie++ = p_info->importance;
      /* End of opt params */
      *p_ie = END_OF_OPT_PARAM_TYPE;
  }

#endif
  
  /* spr #8530 ends */
#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/


  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills ED message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr
**       fills V elements : data
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 3 services.
***************************************************************************/

void 
sccp_fill_ed_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;

  p_co_msg = p_ie;

  /* Fill fixed params */
  *p_ie++ = ED_MSG_TYPE;

  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);


  p_ie += (NUM_MAND_VAR_IES_IN_ED); /* Leave space for pointers */



  /* Set the pointer for mandatory variable part */
  p_co_msg[IDX_DATA_PTR_IN_ED] = (U8bit)(p_ie -
                                       (&p_co_msg[IDX_DATA_PTR_IN_ED]));

  /* data */
  /* SPR 9404 - Fix Start */
  /**p_ie++ = p_info->data.len;*/
  *p_ie++ = (U8bit)p_info->data.len;
  /* SPR 9404 - Fix End   */
  sccp_memcpy (p_ie, p_info->data.p, p_info->data.len);

#if 0 /** SPR# IMP_SPR Start Fix **/
  
  /* spr #8530 starts */
  
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
      if (IS_IMPORTANCE_PRESENT(p_info))
      {
          p_ie += p_info->data.len;
          p_co_msg[IDX_OPT_PARAM_PTR_IN_ED] = (U8bit)(p_ie -
                  (&p_co_msg[IDX_OPT_PARAM_PTR_IN_ED]));
          *p_ie++ = IMPORTANCE_PARAM_TYPE;
          *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
          *p_ie++ = p_info->importance;
          /* End of opt params */
          *p_ie = END_OF_OPT_PARAM_TYPE;
      }
  }
#endif
    /* spr #8530 ends */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills EA message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 3 services.
***************************************************************************/

void 
sccp_fill_ea_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
#if 0
    /* spr # 8530 starts */
    U8bit   *p_co_msg = p_ie;
    /* spr # 8530 ends */
#endif

    /* Fill fixed params */
    *p_ie++ = EA_MSG_TYPE;

    *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
    *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
    *p_ie   = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

    /* No variable mandatory parameter */

    /* No optional parameter */

#if 0 /** SPR# IMP_SPR Start Fix **/

    /* spr #8530 starts */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {
        p_ie++;
        p_ie = p_ie + NUM_MAND_VAR_IES_IN_EA;
        p_co_msg[IDX_OPT_PARAM_PTR_IN_EA] = (U8bit)(p_ie -
                (&p_co_msg[IDX_OPT_PARAM_PTR_IN_EA]));
        *p_ie++ = IMPORTANCE_PARAM_TYPE;
        *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
        *p_ie++ = p_info->importance;
        /* End of opt params */
        *p_ie = END_OF_OPT_PARAM_TYPE;
    }
    
#endif
    /* spr #8530 ends */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

    return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills RSR message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, slr, reset_cause
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 3 services.
***************************************************************************/

void 
sccp_fill_rsr_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
  U8bit   *p_co_msg = p_ie;

  p_co_msg = p_ie;

  /* Fill fixed params */
  *p_ie++ = RSR_MSG_TYPE;

  *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

  *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
  *p_ie++ = (U8bit)((p_info->slr >> 16) & 0x000000FFL);

  *p_ie++ = p_info->reset_cause;

  /* No variable mandatory parameter */

#if 0 /** SPR# IMP_SPR Start Fix **/

  /* spr #8530 starts */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {
        p_ie = p_ie + NUM_MAND_VAR_IES_IN_RSR;
        p_co_msg[IDX_OPT_PARAM_PTR_IN_RSR] = (U8bit)(p_ie -
                (&p_co_msg[IDX_OPT_PARAM_PTR_IN_RSR]));
        *p_ie++ = IMPORTANCE_PARAM_TYPE;
        *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
        *p_ie++ = p_info->importance;
        /* End of opt params */
        *p_ie = END_OF_OPT_PARAM_TYPE;
    }

#endif
    /* spr #8530 ends */

#endif /* if 0 */ 

	/** SPR# IMP_SPR End Fix **/

  /* SPR 1768: Min. length of RSR is 8 */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    	p_co_msg [IDX_OPT_PARAM_PTR_IN_RSR] = (U8bit)SS7_NULL;
#endif


  return;
}

/***************************************************************************
**
**      FUNCTION :
**        fills RSC message elements
****************************************************************************
**
**      DESCRIPTION :
**       fills F elements : msg_type, dlr, slr
**       fills V elements : NONE
**       fills O elements : NONE
**
**      NOTE :
**        Required in CLASS 3 services.
***************************************************************************/

void 
sccp_fill_rsc_msg_elems 
#ifdef ANSI_PROTO
  (U8bit       *p_ie, 
   msg_info_t   *p_info)
#else
  (p_ie, p_info)
  U8bit          *p_ie ;
  msg_info_t     *p_info ;
#endif
{
#if 0
    /* spr # 8530 starts */
    U8bit   *p_co_msg = p_ie;
    /* spr # 8530 ends */
#endif

    /* Fill fixed params */
    *p_ie++ = RSC_MSG_TYPE;

    *p_ie++ = (U8bit)(p_info->dlr & 0x000000FFL);
    *p_ie++ = (U8bit)((p_info->dlr >> 8) & 0x000000FFL);
    *p_ie++ = (U8bit)((p_info->dlr >> 16) & 0x000000FFL);

    /* SPR # 4184 Fix Start */
    /* Changed 'dlr' to 'slr' */
    *p_ie++ = (U8bit)(p_info->slr & 0x000000FFL);
    *p_ie++ = (U8bit)((p_info->slr >> 8) & 0x000000FFL);
    *p_ie   = (U8bit)((p_info->slr >> 16) & 0x000000FFL);
    /* SPR # 4184 Fix End */

    /* No variable mandatory parameter */

#if 0 /** SPR# IMP_SPR Start Fix **/
    
    /* spr #8530 starts */
    
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {
        p_ie++;
        p_ie = p_ie + NUM_MAND_VAR_IES_IN_RSC;
        p_co_msg[IDX_OPT_PARAM_PTR_IN_RSC] = (U8bit)(p_ie -
                (&p_co_msg[IDX_OPT_PARAM_PTR_IN_RSC]));
        *p_ie++ = IMPORTANCE_PARAM_TYPE;
        *p_ie++ = NW_IMPORTANCE_PARAM_LEN;
        *p_ie++ = p_info->importance;
        /* End of opt params */
        *p_ie = END_OF_OPT_PARAM_TYPE;
    }
    
#endif
    
    /* spr #8530 ends */

#endif /* if 0 */ /** SPR# IMP_SPR End Fix **/

    return;
}
#endif
#endif
