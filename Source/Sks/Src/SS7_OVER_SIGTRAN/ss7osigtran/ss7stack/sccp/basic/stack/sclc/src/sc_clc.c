/***************************************************************************
**
**  FILE NAME:
**      sc_clc.c
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION:
**
**
**  DATE     NAME               REF#      REASON
**  -------  ----------------   -----     -------------------------------------
**  13May2004 Suyash/Ganesh                      Fixed SPR 13444 
**  18Oct2002 Ashish Sawalkar             Fixed SPR 10320 
**  06Jul2002 Ashish Sawalkar             Fixed SPR 9166
**  24Jun2002 Ashish Sawalkar			  Fixed SPR 9068 
**  21May2002 Suyash Tripathi   SPR#8748  Adding sccp stats  	
**  03May2002 Ashish Sawalkar			  Fixed SPR 8703
**  4Feb2002  Prateek Bidwalkar			  Added code for multi-threading 
**  21NOV2000 Hemltata Baudhwar SPR#4563  Embedding SCMG in LUDT 
**  03NOV2000 Arun Kumar        SPR#4543  Adding TRAFFIC Statistics
**  12Oct2000 Ramu Kandula                Modified for broadband
**  06Aug'98 Anil K.				      Connectionless ANSI added
**  19May98  Sriganesh. Kini    -----     Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#ifdef SCCP_MT_SAFE
#include "sccp_mtlib_proc.h"

extern S32bit concurrent_count_sem;
extern S32bit part_concurrent_count_sem;
#endif

static void sccp_handle_udt_msg
	_ARGS_ ((msg_info_t * p_info));

static void sccp_handle_udts_msg
	_ARGS_ ((msg_info_t * p_info));

#ifdef SCCP_BROADBAND
static void sccp_handle_ludt_msg
	_ARGS_ ((msg_info_t * p_info));
 
static void sccp_handle_ludts_msg
	_ARGS_ ((msg_info_t * p_info));
#endif

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event 
**         N-UNITDATA request [ User -> SCLC ]
****************************************************************************
**
**      DESCRIPTION :
**         assigns SLS and calls routing function
**
**      NOTE :
**
***************************************************************************/

void
sccp_n_unitdata_req
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
	msg_info_t info;
	return_t ret_val;
	error_t ecode;

/** SPR 9166 Start Fix **/
#ifdef SCCP_MT_SAFE
    U8bit   num_opt_elem, proto_class_1=SS7_FALSE;
    U8bit   *p_elem;
    U16bit  data_len;
#endif
/** SPR 9166 End Fix **/

	SC_A_TRC (("SCCP::SCLC: revcd N-unitdata req\n"));

	ret_val = sccp_parse_n_unitdata_req_api (p_api, &info, &ecode);

	CL_TRC (("SCCP::SCLC: parse %s\n", RESULT_STR(ret_val)));

	if (SS7_FAILURE == ret_val)
	{
		SC_A_ERR (ecode);
		/* SPR# 4543 Start */
		/* Increment the Traffic Statistics */
		SC_STAT_TRAFFIC_INR_PKT_DROP();
		/* SPR# 4543 End */

#ifdef SCCP_MT_SAFE
/** SPR 9166 Start Fix **/

        /* Protocol Class in info structure may be erroneous as parsing
         * has failed. Parse the message once again as it was done in
         * MTlib.
         */
        p_elem = p_api;
        num_opt_elem = GET_API_NELEM(p_api) - SCCP_N_UNITDATA_REQ_MIN_NELEM;
        if(num_opt_elem > 0)
        {
            /* calculate the offset for the optional parameters */
            p_elem += API_HEADER_LEN;
            p_elem += *p_elem + SCCP_ELEM_LEN_LEN;
            p_elem += *p_elem + SCCP_ELEM_LEN_LEN;

            data_len = GET_2_BYTE_LE (p_elem);
            p_elem += SCCP_ELEM_LEN_LEN;
            p_elem += data_len;

            while(num_opt_elem--)
            {
                switch(*p_elem++)
                {
                     case SCCP_ELEM_SEQUENCE_CONTROL:
                         proto_class_1 = SS7_TRUE;
                         num_opt_elem = 0;
                         break;
                     case SCCP_ELEM_RETURN_OPTION:
                     case SCCP_ELEM_IMPORTANCE:
                         p_elem += SCCP_ELEM_LEN_LEN;
                         p_elem++;
                      break;

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
                    case SCCP_ELEM_ISNI:
                         if ((COMPARE_ANSI) || (COMPARE_BCGR))
                            {
                                p_elem += SCCP_ELEM_LEN_LEN;
                                p_elem++;
                            }
                        break;

#endif
            }/* end switch */
        } /* end while */
    } /* end if */


/* SPR# 8703 : Start Fix */
/* SPR# 9068 : Start Fix */
	/* Fixes for 8703, 9068 were removed to fix 9166 */
/* SPR# 9068 : End Fix */
/* SPR# 8703 : End Fix */

        if (proto_class_1 == SS7_TRUE)
            ss7_sem_decr(&part_concurrent_count_sem);
        else
			ss7_sem_decr(&concurrent_count_sem);

        /* Clear the up message stream index previously set in MTLib */
        sccp_mt_clear_up_mesg_stream(p_api);

/** SPR 9166 End Fix **/

#endif
		return;
	}
	/*SPR 9404 - Fix Start */ 
	/*info.sls = sccp_assign_sls (&info.cd_addr, &info.cg_addr, info.sls,
	                            info.proto_class & 0xf);*/
	/*SPR 13444 - Fix Start */
	/*info.sls = sccp_assign_sls (&info.cd_addr, &info.cg_addr, info.sls,
	                            (U8bit)(info.proto_class & 0xf)); */
    /*    info.sls = sccp_assign_sls (&info.cg_addr, &info.cd_addr, info.sls,
                                    (U8bit)(info.proto_class & 0xf));*/
	/*SPR 13444 - Fix Stop */

	/*SPR 9404 - Fix End   */ 
	CL_TRC (("SCCP::SCLC: assigned SLS %d\n", info.sls));

	info.msg_type = UDT_MSG_TYPE;
	
	/* SPR - stats incrementing twice */
#if 0
	/* SPR 8748 - Fix Start */			
	if((PROTOCOL_CLASS_0 == (info.proto_class & 0xf)))
	{
		SC_STAT_Q752_INR_ORIG_MSG_CLASS0(info.cg_addr.ssn);
	}
	else if((PROTOCOL_CLASS_1 == (info.proto_class & 0xf)))
	{
		SC_STAT_Q752_INR_ORIG_MSG_CLASS1(info.cg_addr.ssn);
	}
	/* SPR 8748 - Fix End */			
#endif
	/* SPR - stats incrementing twice */

	sccp_route_cl_msg (&info);

#ifdef SCCP_MT_SAFE
/* SPR# 8703 : Start Fix */
		if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & info.proto_class))
			ss7_sem_decr(&part_concurrent_count_sem);
		else
		if(PROTOCOL_CLASS_0 == (~RET_OPTN_MASK & info.proto_class))
/* SPR# 8703 : End Fix */
			ss7_sem_decr(&concurrent_count_sem);
#endif
}

/***************************************************************************
**
**      FUNCTION :
**         Q.714/C.12/sheet-1 on the event 
**         connectionless message [ SCRC -> SCLC ]
****************************************************************************
**
**      DESCRIPTION :
**         for UDT/UDTS send it to user for segmented XUDT/XUDTS reassemble
**
**      NOTE :
**
***************************************************************************/

void
sccp_handle_cl_msg
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	switch(p_info->msg_type)
	{
		case UDT_MSG_TYPE:
			sccp_handle_udt_msg (p_info);
			break;

		case UDTS_MSG_TYPE:
#ifdef SCCP_ETSI
      		if (COMPARE_ETSI)
      		{
				/* UDTS not supported in ETSI */
				SCCP_UT_TRACE(("SCCP::UT: Error : Unspecified API\n"));
				break;
			}
#endif
			sccp_handle_udts_msg (p_info);
			break;

		case XUDT_MSG_TYPE:
			if ( ! IS_SEGMENTATION_IE_PRESENT(p_info))
				sccp_handle_udt_msg (p_info);
			else
			{
				if (p_info->segment.f_bit &&
				    (p_info->segment.rem_seg == 0))
				{
					/* single segment */
					sccp_handle_udt_msg (p_info);
				}
				else
					sccp_reassemble (p_info);
			}
			break;

		case XUDTS_MSG_TYPE:
			if ( ! IS_SEGMENTATION_IE_PRESENT(p_info))
				sccp_handle_udts_msg (p_info);
			else
			{
				if (p_info->segment.f_bit &&
				    (p_info->segment.rem_seg == 0))
					sccp_handle_udts_msg (p_info);
				else if (p_info->segment.f_bit) /* only first segment return */
					sccp_handle_udts_msg (p_info);
			}

			break;

#ifdef SCCP_BROADBAND
		case LUDT_MSG_TYPE:
			if ( ! IS_SEGMENTATION_IE_PRESENT(p_info))
				sccp_handle_ludt_msg (p_info) ;
			else
			{
				if (p_info->segment.f_bit &&
					(p_info->segment.rem_seg == 0))
				{
					/* Single segment */
					sccp_handle_ludt_msg (p_info) ;
				}
				else
				{
					/* reassemble */
					sccp_reassemble (p_info);
				}
			}
			break;

		case LUDTS_MSG_TYPE:
#ifdef SCCP_ETSI
            if (COMPARE_ETSI)
            {
                /* LUDTS not supported in ETSI */
                SCCP_UT_TRACE(("SCCP::UT: Error : Unspecified API\n"));
                break;
            }
#endif
			if ( ! IS_SEGMENTATION_IE_PRESENT(p_info))
				sccp_handle_ludts_msg (p_info) ;
			else
			{
				if (p_info->segment.f_bit &&
					(p_info->segment.rem_seg == 0))
				{
					/* Single segment */
					sccp_handle_ludts_msg (p_info) ;
				}
				else if (p_info->segment.f_bit)
				{
					/* return only the first segment and ignore all the 
					** subsequent segments
					*/
					sccp_handle_ludts_msg (p_info) ;
				}
			}
			break;
#endif
		default:
			CL_TRC (("SCCP::SCLC: invalid msg type\n"));
			break;
	}
}

/***************************************************************************
**
**      FUNCTION :
**         handles UDT msg
****************************************************************************
**
**      DESCRIPTION :
**         routes msg on SCMG_SSN to SCMG else sends API to subsystem
**
**      NOTE :
**
***************************************************************************/

void
sccp_handle_udt_msg
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t * p_info;
#endif
{
	if (SCMG_SSN == p_info->cd_addr.ssn)
	{
		CL_TRC (("SCCP::SCLC: msg for SCMG\n"));
		sccp_handle_scmg_msg (p_info);
		return;
	}

	sccp_build_n_unitdata_ind_api (p_info);
}

/***************************************************************************
**
**      FUNCTION :
**         handles UDTS msg
****************************************************************************
**
**      DESCRIPTION :
**        
**
**      NOTE :
**
***************************************************************************/

void
sccp_handle_udts_msg
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t * p_info;
#endif
{
	sccp_build_n_notice_ind_api (p_info);
}

#ifdef SCCP_BROADBAND
/***************************************************************************
**
**      FUNCTION :
**         handles LUDT msg
****************************************************************************
**
**      DESCRIPTION :
**         sends API to subsystem
**
**      NOTE :
**
***************************************************************************/

void
sccp_handle_ludt_msg
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t * p_info;
#endif
{
	/* SPR# 4563 Start */
	if (SCMG_SSN == p_info->cd_addr.ssn)
	{
		CL_TRC (("SCCP::SCLC: msg for SCMG\n"));
		sccp_handle_scmg_msg (p_info);
		return;
	}
	/* SPR# 4563 End */

	sccp_build_n_unitdata_ind_api (p_info);
}

/***************************************************************************
**
**      FUNCTION :
**         handles LUDTS msg
****************************************************************************
**
**      DESCRIPTION :
**        
**
**      NOTE :
**
***************************************************************************/

void
sccp_handle_ludts_msg
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t * p_info;
#endif
{
	sccp_build_n_notice_ind_api (p_info);
}
#endif /* SCCP_BROAD_BAND */

