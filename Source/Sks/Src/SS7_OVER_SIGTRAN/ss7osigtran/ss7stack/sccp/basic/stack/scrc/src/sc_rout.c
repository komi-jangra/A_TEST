/***************************************************************************
**
**  FILE NAME:
**      sc_rout.c
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
**  12May'98 Sriganesh. Kini   -----  Original
**  08Jul'98 Anil K.		   -----  ANSI Connectionless added
**  20Aug'98 Anil K./P. Khare  -----  Connection oriented added
**  15Feb'99 Sudipta Pattar    -----  Fixed SPR 1275
**  29Apr'99 Sudipta Pattar    -----  Fixed SPR 1497
**  29Apr'99 Sudipta Pattar    -----  Fixed SPR 1503
**  18Jun'99 Sudipta Pattar    -----  GR modifications done
**  22Feb2000 Ramu Kandula            Fixed SPR 2661
**  24Feb2000 Ramu Kandula            Fixed SPR 2697
**  24Feb2000 Ramu Kandula            Fixed SPR 2616
**  07Mar2000 Ramu Kandula            Fixed SPR 2816
**  08Mar2000 Ramu Kandula            Fixed SPR 2769
**  30May2000 Ramu Kandula            Fixed SPR 3683
**  06Jul2000 Ramu Kandula            Fixed SPR 4052
**  06Jul2000 Ramu Kandula            Fixed SPR 4046
*   12Oct2000 Ramu Kandula            Modified for broadband
**  04Nov2000 Arun Kumar	      Adding TRAFFIC Statistics
**  03oct2001 Aman Kapoor            Fixed SPR 6347
**  06Jan'02 Ashish Sawalkar   -----  Fixed SPR 7970
**  22Jan2002 Prateek Bidwalkar      Fixed SPR 7470
**  02Feb'02  Ashish Sawalkar		  Changes for MT-Safe functionality 
**  04Feb'02  Prateek Bidwalkar		  Changes for MT-Safe functionality 
**  05Apr'02  Pawanish Modi	       Fixed SPR 8620 8621 and 8623 
**  01May2002 Ashish Sawalkar         Fixed SPR 8677
**  03May2002 Ashish Sawalkar         Fixed SPR 8703
**  21May'02  Suyash Tripathi	      Adding sccp stats		      	 
**  27May2002 Ashish Sawalkar         Fixed SPR 8760 
**  11Jun2002 Ashish Sawalkar		  Fixed SPR 8963
**  14Jun2002 Ashish Sawalkar		  Fixed SPR 8966
**  24Jun2002 Ashish Sawalkar		  Fixed SPR 9066, 9068
**  06Jul2002 Ashish Sawalkar         Fixed SPR 9163, 9164
**  25oct2002 Pawanish Modi         Fixed SPR 10429, 10430
**  30Jul'02  Prateek Bidwalkar		  Fixed SPR # 9221
**  08Aug'02  Ashish Sawalkar		  Fixed SPR # 9302 
**  12Feb'03  Ashish Sawalkar		  Fixed SPR # 11321 
**  27Nov'03  Mahesh Goenka			  Fixed SPR # 13112
**  20Jan2004 Hitesh Sharma          Fixed SPR  13242
**  13May2004 Ganesh                 Fixed SPR  13444
**  
**  Copyright 2000, Hughes Software Systems
**
***************************************************************************/


#include "sc_stgl.h"
#include "sc_sref.h"

/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 7470 Fix End */
#ifdef SCCP_MT_SAFE
#include "sccp_mtlib_coc.h"
#include "sccp_mtlib_proc.h"

extern S32bit	concurrent_count_sem;
extern S32bit	part_concurrent_count_sem;
#endif

static void sccp_determine_restr_fwd_msg
	_ARGS_ ((msg_info_t * p_info));

static void sccp_translate_route_msg
	_ARGS_ ((msg_info_t * p_info));

static void sccp_route_translated_local_msg
	_ARGS_ ((msg_info_t * p_info));

static void sccp_compat_test_fwd_msg
	_ARGS_ ((msg_info_t * p_info));

/* SPR 9302 - Fix Start */
/* Already declared above */
/*static void sccp_determine_restr_fwd_msg
	_ARGS_ ((msg_info_t * p_info));*/
/* SPR 9302 - Fix End   */

/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
extern U8bit	dsccp_class1_timer_status;
#endif
/* SPR # 7470 Fix End */

extern U8bit sccp_state;

int gtt_counter = 0;
t_gt_list gsn_gtt_list[MAX_GTT_LIST];

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.1/sheet-2 on the node 3
****************************************************************************
**
**      DESCRIPTION :
**          handles MTP3 transfer indication
**
**      NOTE :
**
***************************************************************************/

void 
sccp_m3_transfer_ind 
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api ;
#endif
{
	msg_info_t info, * p_info = &info;
	return_t ret_val;
	error_t ecode;
	int found = 0;
	int i,j;

#ifdef SCCP_MT_SAFE 
	/** SPR 9302 Start Fix **/
	U8bit 	msg_type=0, prot_cls=0, pointer=0, addr_ind=0, ssn=0;
	U8bit	*p_elem=SS7_NULL, *p_addr=SS7_NULL;
	U8bit	is_udt_scmg = SS7_FALSE;
	/** SPR 9302 End Fix **/
#endif

	/* SPR # 6347... Fix Starts */	
	ss7_mem_zero(&info,sizeof(msg_info_t));
	/* SPR # 6347... Fix Ends */	

	SC_A_TRC (("SCCP::SCRC : recvd  transfer ind\n"));

	ret_val = sccp_parse_m3_transfer_ind_api (p_api, p_info, &ecode);

#ifdef SCCP_MT_SAFE 
	if(SS7_FAILURE == ret_val)
	{
		/* Parsing the api once again to get the SCCP message type */
	    p_elem = p_api;
	    p_elem += SS7_API_HEADER_LEN; /* for the api header length */
	    p_elem += MTP3_LENGTH_SIO; /* for sio */
	
#if defined (SCCP_CHINESE)
	    if(COMPARE_CHINESE)
	    {
	        p_elem += PC_SIZE;
	        p_elem += PC_SIZE;
	        p_elem++;
	    }
#endif
	        /* advance the pointer by the size of the routing label */
#if defined (SCCP_ITU) || defined(SCCP_ETSI)
	    if (COMPARE_ITU || COMPARE_ETSI)
	    {
	        p_elem += PC_SIZE;
	        p_elem ++;
	        p_elem ++;
	    }
#endif

/* SPR# 8760 :Start Fix */
#if defined (SCCP_JAPANESE)
    if (COMPARE_JAPANESE)
    p_elem += PC_SIZE + PC_SIZE + 1;
#endif
/* SPR# 8760 :End Fix */
	
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
	    if (COMPARE_ANSI || COMPARE_BCGR)
	    {
	        p_elem += PC_SIZE;
	        p_elem += PC_SIZE;
	        p_elem++;
	    }
#endif 
	
		msg_type = *p_elem;
		prot_cls = *(p_elem+1);
	}
	else
	{
		p_elem = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];
		msg_type = *p_elem;
		p_elem = (U8bit *)&p_info->m3_data.p[IDX_PROTO_CLASS_IN_UDT];
		prot_cls = *p_elem;

		/* Checking if the message received is UDT and contains 
		 * a SCMG message
		 */
		p_elem = (U8bit *)&p_info->m3_data.p[IDX_MSG_TYPE_IN_MSG];
		if (UDT_MSG_TYPE == msg_type)
		{
			pointer =  p_elem [IDX_CD_ADDR_PTR_IN_UDT];
			p_addr  = &p_elem [IDX_CD_ADDR_PTR_IN_UDT] + pointer;
			p_addr++;
			addr_ind = *p_addr++;
		}
#ifdef SCCP_BROADBAND
		else if (LUDT_MSG_TYPE == msg_type)
		{
			pointer = ((p_elem[IDX_CG_ADDR_PTR_IN_LUDT]<<0)&0x00ff)|
					  ((p_elem[IDX_CG_ADDR_PTR_IN_LUDT+1]<<8)&0xff00) ;
			p_addr  = &p_elem [IDX_CG_ADDR_PTR_IN_LUDT+1] + pointer;
			p_addr++;

			addr_ind = *p_addr++;
		}		
#endif

/* SPR# 8966 : Start Fix */
#ifdef SCCP_BROADBAND
		if (LUDT_MSG_TYPE == msg_type || UDT_MSG_TYPE == msg_type)
#else
		if (UDT_MSG_TYPE == msg_type)
#endif	
		{
/* SPR# 8966 : End Fix */
/* SPR# 8760 : Start Fix */
#if defined(SCCP_ITU) || defined(SCCP_ETSI) || defined (SCCP_CHINESE) || defined(SCCP_JAPANESE)
			if (COMPARE_ITU || COMPARE_ETSI || COMPARE_CHINESE || COMPARE_JAPANESE)
/* SPR# 8760 : End Fix */
			{
				if (addr_ind & ADDR_IND_PC_MASK)
					p_addr += PC_SIZE;

				if (addr_ind & ADDR_IND_SSN_MASK)
					ssn = *p_addr;
			}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			if ((COMPARE_ANSI) || (COMPARE_BCGR))
			{
				if (addr_ind & ADDR_IND_SSN_MASK)
					ssn = *p_addr++;
			}
#endif
			if (SCMG_SSN == ssn)
				is_udt_scmg = SS7_TRUE;
		}
	}

#endif /* SCCP_MT_SAFE */

	/* SPR 10868 - Fix Start */
	/*SC_A_TRC (("SCCP::SCRC : parse %s\n", RESULT_STR(ret_val)));*/
	/* SPR 10868 - Fix End   */

	if (SS7_FAILURE == ret_val)
	{
		SC_A_ERR (ecode);
		/* SPR# 4543 Start */
                /* Increment the traffic related statistics */
		SC_STAT_TRAFFIC_INR_PKT_INVALID();
		/* SPR# 4543 End */

#ifdef SCCP_MT_SAFE
		/* for connection oriented messages */
		SCCP_MTLIB_RELEASE_CO_LOCKS
		
		/* for connectionless messages */
#ifdef SCCP_BROADBAND
		if ((msg_type == LUDT_MSG_TYPE || 
			 msg_type == UDT_MSG_TYPE) && is_udt_scmg == SS7_FALSE)
#else
		if (msg_type == UDT_MSG_TYPE && is_udt_scmg == SS7_FALSE)
#endif
		{
			/* SPR# 8703 : Start Fix */
			if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & prot_cls))
			/* SPR# 8703 : End Fix */
				ss7_sem_decr(&part_concurrent_count_sem);
			else
				ss7_sem_decr(&concurrent_count_sem);
		}
		else
		if(msg_type == XUDT_MSG_TYPE)
			ss7_sem_decr(&part_concurrent_count_sem);
		else
		if((msg_type == UDTS_MSG_TYPE) || 
#ifdef SCCP_BROADBAND
		   (msg_type == LUDTS_MSG_TYPE) || 
#endif
		   (msg_type == XUDTS_MSG_TYPE))
		{
			ss7_sem_decr(&concurrent_count_sem);
		}
/* SPR# 9163 : Start Fix */
/* SPR# 8677 : Start Fix */
        if (sccp_is_co_msg(msg_type) && msg_type != CR_MSG_TYPE)
            sccp_mtlib_chk_clr_conn_id(p_info->p_api);
        else
            sccp_mtlib_chk_clr_nw_msg_stream
                (msg_type, prot_cls, p_info->p_api);
/* SPR# 8677 : End Fix */
/* SPR# 9163 : End Fix */
#endif /* SCCP_MT_SAFE */

		return;
	}

	/** SPR # 2697 Fix Start **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
	if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
	{
		if (sccp_cong.level > 0)
			sccp_congested_sp_msg_ind(p_info);	/* Send SSC */
	}
#endif
	/** SPR # 2697 Fix End **/

	ret_val = sccp_parse_nw_msg (p_info);

	if (p_info->msg_type != RLC_MSG_TYPE && (sccp_state == UNINITIALIZED || sccp_state==BLOCKED))
  	{
    	SC_I_TRC (("SCCP::INIT:message in UNINTITALIZED state.\n"));

      	return;
  	}

    /* SPR# 7970 : Start Fix */
    switch(p_info->proto_class)
    {
        case PROTOCOL_CLASS_0:
            SC_STAT_Q752_INR_RECD_MSG_CLASS0(p_info->cd_addr.ssn);
            break;
        case PROTOCOL_CLASS_1:
            SC_STAT_Q752_INR_RECD_MSG_CLASS1(p_info->cd_addr.ssn);
            break;
    }
    /* SPR# 7970 : End Fix */

	/* SPR 10868 - Fix Start */
	/*RC_TRC (("SCCP::SCRC: connectionless msg parse %s\n", 
		RESULT_STR(ret_val)));*/
	RC_TRC (("SCCP::SCRC: Msg parse %s\n", 
		RESULT_STR(ret_val)));
	/* SPR 10868 - Fix End   */

	if (SS7_FAILURE == ret_val)
	{
		SC_STAT_Q752_TS_SYNTAX_ERROR;
		SC_STAT_Q752_INR_SYNTAX_ERROR;

		/* SPR 9675 - Fix Start */
		SC_STAT_ERR_INR_ERR_API();
		/* SPR 9675 - Fix End   */
		/* SPR# 4543 Start */
		/* Increment the traffic related statstics */
		SC_STAT_TRAFFIC_INR_PKT_INVALID();
		/* SPR# 4543 End */

		SC_P_ERR (ESCCP_CL_MSG_SYNTAX_ERR);
#ifdef SCCP_MT_SAFE
		/* for connection oriented messages */
		SCCP_MTLIB_RELEASE_CO_LOCKS	

		/* for connectionless messages */
#ifdef SCCP_BROADBAND
		if ((msg_type == LUDT_MSG_TYPE ||
			 msg_type == UDT_MSG_TYPE) && is_udt_scmg == SS7_FALSE)
#else
		if (msg_type == UDT_MSG_TYPE && is_udt_scmg == SS7_FALSE)
#endif
		{
			/* SPR# 8703 : Start Fix */
			if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & prot_cls))
			/* SPR# 8703 : End Fix */
				ss7_sem_decr(&part_concurrent_count_sem);
			else
				ss7_sem_decr(&concurrent_count_sem);
		}
		else
		if(msg_type == XUDT_MSG_TYPE)
			ss7_sem_decr(&part_concurrent_count_sem);
		else
		if((msg_type == UDTS_MSG_TYPE) || 
#ifdef SCCP_BROADBAND
		   (msg_type == LUDTS_MSG_TYPE) ||
#endif
		   (msg_type == XUDTS_MSG_TYPE))
		{
			ss7_sem_decr(&concurrent_count_sem);
		}
/* SPR# 9164 : Start Fix */
/* SPR# 8677 : Start Fix */
        if (sccp_is_co_msg(msg_type) && msg_type != CR_MSG_TYPE)
            sccp_mtlib_chk_clr_conn_id(p_info->p_api);
        else
            sccp_mtlib_chk_clr_nw_msg_stream
                (msg_type, prot_cls, p_info->p_api);
/* SPR# 8677 : End Fix */
/* SPR# 9164 : End Fix */

#endif /* SCCP_MT_SAFE */
		return;
	}

        /* SPR# 4543 Start */
        else
        { /* Increment the Traffic statistics */
                SC_STAT_TRAFFIC_INR_PKT_RECD();
        }
        /* SPR# 4543  End */

    if ( (p_info->msg_type == UDT_MSG_TYPE)
         || (p_info->msg_type == XUDT_MSG_TYPE)
#ifdef SCCP_BROADBAND
         || (p_info->msg_type == LUDT_MSG_TYPE)
#endif
        )
    {
		SC_STAT_Q752_INR_RECD_LUDT_XUDT_UDT(p_info->cd_addr.ssn);
	}

	/** SPR # 3041 Fix Start **/
	/** SPR # 10430 Fix Start **/
#if 0
	if ( (p_info->msg_type == UDT_MSG_TYPE)
		 || (p_info->msg_type == UDTS_MSG_TYPE)
		 || (p_info->msg_type == XUDT_MSG_TYPE)
		 || (p_info->msg_type == XUDTS_MSG_TYPE) 
#ifdef SCCP_BROADBAND
		 || (p_info->msg_type == LUDT_MSG_TYPE)
		 || (p_info->msg_type == LUDTS_MSG_TYPE) 
#endif
		)
	{
		/* Check if the length of the received segment can be
		** supported; if not, then truncate the segment  and 
		** return the message
		*/
		if (sccp_perform_compat_test(p_info) == SS7_TRUE)
		{
			p_info->data.len = sc_opt.seg_size;
			p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING;
			sccp_handle_routing_failure (p_info);
#ifdef SCCP_MT_SAFE
#ifdef SCCP_BROADBAND
			if ((p_info->msg_type == LUDT_MSG_TYPE ||
				 p_info->msg_type == UDT_MSG_TYPE) && is_udt_scmg == SS7_FALSE)
#else
			if (p_info->msg_type == UDT_MSG_TYPE && is_udt_scmg == SS7_FALSE)
#endif
			{
				/* SPR# 8703 : Start Fix */
				if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & prot_cls))
				/* SPR# 8703 : End Fix */
					ss7_sem_decr(&part_concurrent_count_sem);
				else
					ss7_sem_decr(&concurrent_count_sem);
			}
        	else
        	if(msg_type == XUDT_MSG_TYPE)
           	 	ss7_sem_decr(&part_concurrent_count_sem);
        	else
	        if((msg_type == UDTS_MSG_TYPE) ||
#ifdef SCCP_BROADBAND
   	        (msg_type == LUDTS_MSG_TYPE) ||
#endif
   	        (msg_type == XUDTS_MSG_TYPE))
   		     {
   		         ss7_sem_decr(&concurrent_count_sem);
   		     }
/* SPR# 8677 : Start Fix */
        sccp_mtlib_chk_clr_nw_msg_stream(msg_type, prot_cls, p_info->p_api);
/* SPR# 8677 : End Fix */

#endif /* SCCP_MT_SAFE */
			return;
		}
	}
#endif
	/** SPR # 10430 Fix ends **/
	/** SPR # 3041 Fix End **/

/*review comments 23feb*/
    if(gtt_counter == 0)
        memset (&gsn_gtt_list, 0 , (sizeof(t_gt_list) * MAX_GTT_LIST));

	/********** Making a list to store the Address coming from the HLR ******************/
	for(i=0;i<gtt_counter;i++)
	{
		for(j=0;j<gsn_gtt_list[i].gt_len;j++)
		{
		  if(gsn_gtt_list[i].input[j] == p_info->cg_addr.gt[j])
		  {
				found = 1;
				continue;
		  }
		  else
			{
				found = 0;
				break;
			}

		 }

		if (found == 1)
		{
			RC_TRC(("HLR Number already in the list\n"));
		  	break;
		}
		  else
			continue;
	}

	if(found == 0)
	{
	
		if(p_info->cg_addr.ssn_ind)
	  		gsn_gtt_list[gtt_counter].ssn = p_info->cg_addr.ssn;
		else
		  	gsn_gtt_list[gtt_counter].ssn = 0;



		if(p_info->cg_addr.gti)
		{
	  		gsn_gtt_list[gtt_counter].gt_len = p_info->cg_addr.gt_len;
			sccp_memcpy (&gsn_gtt_list[gtt_counter].input[0], &(p_info->cg_addr.gt[0]),gsn_gtt_list[gtt_counter].gt_len);
            
            gsn_gtt_list[gtt_counter].pc = p_info->opc;
		
		    gsn_gtt_list[gtt_counter].rout_ind =  p_info->cg_addr.rout_ind;

            gtt_counter++;
		}
        
         /*review comments 23feb - placed the increment in if*/ 
		/*gsn_gtt_list[gtt_counter].pc = p_info->opc;
		
		gsn_gtt_list[gtt_counter].rout_ind =  p_info->cg_addr.rout_ind;
		*/
		/*gtt_counter++;*/
	}
	
	/******************************************/

	if (ROUTE_ON_GT == p_info->cd_addr.rout_ind)
	{
		if (IS_HOP_COUNTER_IE_PRESENT(p_info))
		{
			/** SPR # 3683 Fix Start **/
			if (p_info->hop_counter > 0)
				p_info->hop_counter--;
			/** SPR # 3683 Fix End **/

			if (p_info->hop_counter <= 0) /* SPR 2661 Fix: Changed '<' to '<=' */
			{
				/* Indicate routing failure to OMAP */

/* SPR # 9221 Fix Start */
				SC_STAT_Q752_TS_HOP_COUNT_VIOLATION;
				SC_STAT_Q752_INR_HOP_COUNT_VIOLATION;
/* SPR # 9221 Fix End */

#ifdef SCCP_INCLUDE_CO_SERVICE
				if (sccp_is_co_msg (p_info->msg_type))
				{
					p_info->rel_cause = SCCP_RFC_HOP_COUNTER_VIOLATION;
					p_info->event = SCCP_ROUTE_FAIL_EVENT;
					sccp_handle_co_mesg (p_info, &ecode);
#ifdef SCCP_MT_SAFE
					SCCP_MTLIB_RELEASE_CO_LOCKS
#endif /* SCCP_MT_SAFE */
				}
				else
#endif
				{
					p_info->ret_cause = SCCP_HOP_COUNTER_VIOLATION;
					sccp_handle_routing_failure (p_info);
#ifdef SCCP_MT_SAFE
#ifdef SCCP_BROADBAND
					if ((p_info->msg_type == LUDT_MSG_TYPE  || 
						 p_info->msg_type == UDT_MSG_TYPE)  && 
											is_udt_scmg == SS7_FALSE)
#else
					if (p_info->msg_type == UDT_MSG_TYPE && 
											is_udt_scmg == SS7_FALSE)
#endif
					{
						/* SPR# 8703 : Start Fix */
						if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & prot_cls))
						/* SPR# 8703 : End Fix */
							ss7_sem_decr(&part_concurrent_count_sem);
						else
							ss7_sem_decr(&concurrent_count_sem);
					}
		        	else
		        	if(msg_type == XUDT_MSG_TYPE)
		           	 	ss7_sem_decr(&part_concurrent_count_sem);
		        	else
			        if((msg_type == UDTS_MSG_TYPE) ||
#ifdef SCCP_BROADBAND
		   	        (msg_type == LUDTS_MSG_TYPE) ||
#endif
		   	        (msg_type == XUDTS_MSG_TYPE))
		   		     {
		   		         ss7_sem_decr(&concurrent_count_sem);
		   		     }
/* SPR# 8677 : Start Fix */
        			 sccp_mtlib_chk_clr_nw_msg_stream(msg_type, 
												prot_cls, p_info->p_api);
/* SPR# 8677 : End Fix */

#endif /* SCCP_MT_SAFE */
				}
				return;
			}
		}
  
		/* SPR 1497: Start fix 
		 * no protocol class for UDTS and XUDTS and LUDTS messages 
		 */
	 	if ((p_info->msg_type == UDTS_MSG_TYPE) 
           	|| (p_info->msg_type == XUDTS_MSG_TYPE )
#ifdef SCCP_BROADBAND
           	|| (p_info->msg_type == LUDTS_MSG_TYPE )
#endif
			)
		{
                        /* Assign SLS randomly */
			/* Fix for SPR No: 13112 Start */
                        /*        p_info->sls = sccp_assign_sls(&p_info->cd_addr,
                                              &p_info->cg_addr,
                                              p_info->sls,
                                              PROTOCOL_CLASS_0);
                        RC_TRC (("SCCP::SCRC: assigned SLS %d\n", p_info->sls)); */
			/* Fix for SPR No: 13112 Stop */

		  	sccp_translate_route_msg (p_info);
#ifdef SCCP_MT_SAFE
				ss7_sem_decr(&concurrent_count_sem);
#endif /* SCCP_MT_SAFE */
			return;
		}
		/* SPR 1497: end fix */


		RC_TRC (("SCCP::SCRC: class %d msg\n", p_info->proto_class & 0xf));

		if ((PROTOCOL_CLASS_0 == (p_info->proto_class & 0xf)) ||
			(PROTOCOL_CLASS_1 == (p_info->proto_class & 0xf)))
		{
			/* Assign SLS. For class 0 assign randomly. For class 1
		   		map input SLS to output SLS */
			/* SPR 9404 - Fix Start */
				/*********
				p_info->sls = sccp_assign_sls(&p_info->cd_addr,
		                              &p_info->cg_addr,
		                              p_info->sls,
		                              p_info->proto_class & 0xf);**********/
				/****** SPR 13112 *****
				p_info->sls = sccp_assign_sls(&p_info->cd_addr,
		                              &p_info->cg_addr,
		                              p_info->sls,
		                              (U8bit)(p_info->proto_class & 0xf));

				****** SPR 13112 ******/
			/* SPR 9404 - Fix End   */
			RC_TRC (("SCCP::SCRC: assigned SLS %d\n", p_info->sls));
		}
		else
		{
#ifdef SCCP_INCLUDE_CO_SERVICE
			if ((PROTOCOL_CLASS_2 != (p_info->proto_class & 0xf)) &&
				(PROTOCOL_CLASS_3 != (p_info->proto_class & 0xf)))
#endif
			{
				RC_TRC (("SCCP::SCRC: unknown protocol class. dropped\n"));
				SC_P_ERR(0);
#ifdef SCCP_MT_SAFE
				SCCP_MTLIB_RELEASE_CO_LOCKS
        		if(msg_type == XUDT_MSG_TYPE)
           	 		ss7_sem_decr(&part_concurrent_count_sem);
				else
				if (!sccp_is_co_msg (p_info->msg_type))
						ss7_sem_decr(&concurrent_count_sem);
#endif /* SCCP_MT_SAFE */
				return;
			}
		}

		sccp_translate_route_msg (p_info);
	}
	else /* route indicator = PC+SSN */
	{
		sccp_route_translated_local_msg (p_info);

	}
#ifdef SCCP_MT_SAFE
	if (sccp_is_co_msg (p_info->msg_type))
			SCCP_MTLIB_RELEASE_CO_LOCKS
	else
#ifdef SCCP_BROADBAND
	if ((p_info->msg_type == LUDT_MSG_TYPE ||
		 p_info->msg_type == UDT_MSG_TYPE) && is_udt_scmg == SS7_FALSE)
#else
	if (p_info->msg_type == UDT_MSG_TYPE && is_udt_scmg == SS7_FALSE)
#endif
    {
		/* SPR# 8703 : Start Fix */
         if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & prot_cls))
		/* SPR# 8703 : End Fix */
               ss7_sem_decr(&part_concurrent_count_sem);
          else
                ss7_sem_decr(&concurrent_count_sem);
     }
     else
     if(msg_type == XUDT_MSG_TYPE)
             ss7_sem_decr(&part_concurrent_count_sem);
     else
     if((msg_type == UDTS_MSG_TYPE) ||
#ifdef SCCP_BROADBAND
       (msg_type == LUDTS_MSG_TYPE) ||
#endif
       (msg_type == XUDTS_MSG_TYPE))
      {
          ss7_sem_decr(&concurrent_count_sem);
      }

/* SPR# 8677 : Start Fix */
	sccp_mtlib_chk_clr_nw_msg_stream(msg_type, prot_cls, p_info->p_api);
/* SPR# 8677 : End Fix */

#endif /* SCCP_MT_SAFE */

}

/***************************************************************************
**
**      FUNCTION :
**          corresponds to Q.714/C.1/sheet-1 on the event 
**          Connectionless message [ SCLC -> SCRC ]
****************************************************************************
**
**      DESCRIPTION :
**         Routes a connectionless message
**         determines routing indicator depending on called address and
**         calls appropriate routing function
**
**      NOTE :
**
***************************************************************************/

void 
sccp_route_cl_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	if ((UDT_MSG_TYPE == p_info->msg_type) 
	    || (XUDT_MSG_TYPE == p_info->msg_type)
#ifdef SCCP_BROADBAND 
	    || (LUDT_MSG_TYPE == p_info->msg_type)
#endif
		)
	{
		/* SPR Fix Start - stats incrementing twice */
		/*SC_STAT_Q752_INR_ORIG_LUDT_XUDT_UDT(p_info->cg_addr.ssn);*/
		/* SPR Fix End - stats incrementing twice */
		if (IS_TRANSLATION_DONE(p_info))
		{
			sccp_determine_restr_fwd_msg (p_info);
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
            if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & p_info->proto_class))
                sccp_mt_clear_up_mesg_stream(p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
			return;
		}
	}
	else /* UDTS or XUDTS or LUDTS message */
	{
		if (ROUTE_ON_SSN == p_info->cd_addr.rout_ind)
		{
			/* SPR 1275: Start fix
			 * check if PC is accessible and SCCP is not-probihited 
 			 */
			if (IS_SP_PROHIBITED(p_info->p_sp) ||
				IS_SCCP_PROHIBITED(p_info->p_sp))
			{
				SC_STAT_Q752_TS_PC_UNAVAIL;
				SC_STAT_Q752_INR_PC_UNAVAIL;
				RC_TRC (("SCCP::SCRC: SCCP (pc %d, nw_id %d) "
               			"not accessible.  msg dropped\n", p_info->cd_addr.pc, 
							      p_info->nw_id));
				return;
			}
			/* SPR 1275: End fix */

			sccp_compat_test_fwd_msg (p_info);
			return;
		}
	}

	if (p_info->cd_addr.pc_ind)
	{
		/* GT + DPC */
		if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,
		                                             p_info->cd_addr.pc)))
		{
			/** SPR # 2616 Fix Start **/
#if 0
			RC_TRC (("SCCP::SCRC: pc %d nw %d unknown in called addr unknown"
			         " msg dropped\n", p_info->cd_addr.pc, p_info->nw_id));
#endif

			SC_STAT_Q752_TS_ROUTE_FAIL;
			SC_STAT_Q752_INR_ROUTE_FAIL;

			p_info->ret_cause = SCCP_MTP_FAILURE;
			sccp_handle_routing_failure (p_info);
			/** SPR # 2616 Fix End **/
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
            if(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & p_info->proto_class))
                sccp_mt_clear_up_mesg_stream(p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
			return;
		}

		if (p_info->p_sp->local)
		{
			if (p_info->cd_addr.ssn_ind)
			{
				if (p_info->cd_addr.gti > 0)
				{
					/* This is outside the scope of the
					   recommendataion. We will route on SSN here */
					sccp_route_translated_local_msg (p_info);
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                    if(UDT_MSG_TYPE == p_info->msg_type && \
                    	(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
							p_info->proto_class)))
                        		sccp_mt_clear_up_mesg_stream( \
                            		p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
				}
				else
				{
					sccp_route_translated_local_msg (p_info);
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                    if(UDT_MSG_TYPE == p_info->msg_type && \
                    (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
						p_info->proto_class)))
                        	sccp_mt_clear_up_mesg_stream( \
                            	p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
				}
			}
			else
			{
				p_info->cd_addr.rout_ind = ROUTE_ON_GT;
				sccp_translate_route_msg (p_info);
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                if(UDT_MSG_TYPE == p_info->msg_type && \
                	(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
						p_info->proto_class)))
                 			sccp_mt_clear_up_mesg_stream
								( p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
			}
		}
		else
		{
			/* Set the routing indicator */
			/** SPR # 2769 Fix Start **/
			/* RI must be set to GT only when GT is present and SSN in absent 
			** or SSN = 0 
			*/
			if (p_info->cd_addr.gti)
			{
				/* Start SPR : 13242 Fix */
#ifndef GTT_DPC_SSN_CHANGES
				if ( ! p_info->cd_addr.ssn_ind )
				{
					p_info->cd_addr.rout_ind = ROUTE_ON_GT;
				}
				else
				{
					if (p_info->cd_addr.ssn == 0)
						p_info->cd_addr.rout_ind = ROUTE_ON_GT;
					else
						p_info->cd_addr.rout_ind = ROUTE_ON_SSN;
				}
#endif
				/* Ends SPR :13242 Fix */
			}
			else
			{
				if (p_info->cd_addr.ssn_ind)
					p_info->cd_addr.rout_ind = ROUTE_ON_SSN;
				else
				{

					SC_STAT_Q752_TS_ROUTE_FAIL;
					SC_STAT_Q752_INR_ROUTE_FAIL;

					/* neither GT nor SSN present in the cld addr */
					p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING;
					sccp_handle_routing_failure (p_info);
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                if(UDT_MSG_TYPE == p_info->msg_type && \
                (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
					p_info->proto_class)))
                 		sccp_mt_clear_up_mesg_stream( p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
					return;
				}
			}
			/** SPR # 2769 Fix End **/

			/* SPR 1275: Start fix
			 * check if PC is accessible and SCCP is not-probihited 
			 */
			/** SPR # 2616 Fix Start **/
			if (IS_SP_PROHIBITED(p_info->p_sp)) 
			{
				SC_STAT_Q752_TS_PC_UNAVAIL;
				SC_STAT_Q752_INR_PC_UNAVAIL;
				p_info->ret_cause = SCCP_MTP_FAILURE;
				sccp_handle_routing_failure (p_info);
/* SPR# 8677 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                if(UDT_MSG_TYPE == p_info->msg_type && \
                (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
					p_info->proto_class)))
                 		sccp_mt_clear_up_mesg_stream( p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
/* SPR# 8677 : End Fix */
				return;
			}	

			if (IS_SCCP_PROHIBITED(p_info->p_sp))
			{
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
				if ((COMPARE_ANSI) || (COMPARE_BCGR))
				{
					p_info->ret_cause = SCCP_NETWORK_CONGESTION;
				}
#endif
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
				if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
				{
					p_info->ret_cause = SCCP_FAILURE;
				}
#endif
				SC_STAT_Q752_TS_PC_UNAVAIL;
				SC_STAT_Q752_INR_PC_UNAVAIL;
				sccp_handle_routing_failure (p_info);
/* SPR# 8677 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                if(UDT_MSG_TYPE == p_info->msg_type && \
                (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
					p_info->proto_class)))
                 		sccp_mt_clear_up_mesg_stream( p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
/* SPR# 8677 : End Fix */
				return;
			}	

			/** SPR # 2616 Fix end **/
           	/* SPR 1275: End fix */

			/* GR changes: Start
			* if ROUTE_ON_SSN and SSN is present, check if subsys is available
			*/
					
			if ((p_info->cd_addr.ssn_ind) &&
				(p_info->cd_addr.rout_ind == ROUTE_ON_SSN))
			{
				if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss
                               	(p_info->p_sp, p_info->cd_addr.ssn)))
				{
					RC_TRC (("SCCP::SCRC: Subsystem (pc %d, ssn %d) "
								"unequipped.\n", p_info->cd_addr.pc,
								p_info->cd_addr.ssn));
					SC_STAT_Q752_TS_UNEQUIPPED_SS;
					SC_STAT_Q752_INR_UNEQUIPPED_SS;

					p_info->ret_cause = SCCP_UNEQUIPPED_USER;
					sccp_handle_routing_failure (p_info);
/* SPR# 8677 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                    if(UDT_MSG_TYPE == p_info->msg_type && \
                    (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
						p_info->proto_class)))
                        	sccp_mt_clear_up_mesg_stream( \
                                   p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
/* SPR# 8677 : End Fix */
					return;
				}
	
				if (IS_SS_PROHIBITED(p_info->p_ss))
				{
					RC_TRC (("SCCP::SCRC: Subsystem (pc %d, ssn %d) "
								"not available.\n", p_info->cd_addr.pc,
							p_info->cd_addr.ssn));
					p_info->ret_cause = SCCP_SUBSYSTEM_FAILURE;
					SC_STAT_Q752_TS_SS_UNAVAIL;
					SC_STAT_Q752_INR_SS_UNAVAIL;
					sccp_handle_routing_failure (p_info);
/* SPR# 8677 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
                    if(UDT_MSG_TYPE == p_info->msg_type && \
                    (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
						p_info->proto_class)))
                        	sccp_mt_clear_up_mesg_stream( \
                             	p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
/* SPR# 8677 : End Fix */
					return;
				}
			}

			/* GR changes: End */
 
			sccp_compat_test_fwd_msg (p_info);
/* SPR# 8677 : Start Fix */
#ifdef SCCP_MT_SAFE
/* SPR# 9066 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_BROADBAND
            if((LUDT_MSG_TYPE==p_info->msg_type || 
				XUDT_MSG_TYPE==p_info->msg_type) &&
					(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & \
						p_info->proto_class)))
#else
            if((UDT_MSG_TYPE==p_info->msg_type || 
				XUDT_MSG_TYPE==p_info->msg_type) && 
					(PROTOCOL_CLASS_1==(~RET_OPTN_MASK & \
						p_info->proto_class)))
/* SPR# 9068 : End Fix */
/* SPR# 9066 : End Fix */
#endif
                	sccp_mt_clear_up_mesg_stream(p_info->p_api);
#endif
/* SPR# 8677 : End Fix */
		}
	}
	else
	{	
		/* SPR 8192 Fix start */
		if (p_info->cd_addr.gti)
		{
		/* SPR 8192 Fix end */

		 	/* GT only or GT + SSN */
			sccp_translate_route_msg (p_info);
/* SPR# 8677 : Start Fix */
#ifdef SCCP_MT_SAFE
/* SPR# 9066 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_BROADBAND
            if((LUDT_MSG_TYPE==p_info->msg_type ||
				XUDT_MSG_TYPE==p_info->msg_type) && 
					(PROTOCOL_CLASS_1 == (~RET_OPTN_MASK &\
						p_info->proto_class)))
#else
            if((UDT_MSG_TYPE==p_info->msg_type || 
				XUDT_MSG_TYPE==p_info->msg_type) && 
					(PROTOCOL_CLASS_1==(~RET_OPTN_MASK &\
						p_info->proto_class)))
#endif
/* SPR# 9068 : End Fix */
/* SPR# 9066 : End Fix */
                sccp_mt_clear_up_mesg_stream( p_info->p_api);
#endif
/* SPR# 8677 : End Fix */
		/* SPR 8192 Fix start */
		}
		else
		{

			SC_STAT_Q752_TS_ROUTE_FAIL;
			SC_STAT_Q752_INR_ROUTE_FAIL;

			/* SPR 10852 - Fix Start */
			p_info->ret_cause = SCCP_UNQUALIFIED;
			/* SPR 10852 - Fix Start */

			sccp_handle_routing_failure(p_info);	
/* SPR# 8677 : Start Fix */
/* SPR# 9068 : Start Fix */
#ifdef SCCP_MT_SAFE
            if(UDT_MSG_TYPE == p_info->msg_type && \
            (PROTOCOL_CLASS_1 == (~RET_OPTN_MASK & p_info->proto_class)))
                 sccp_mt_clear_up_mesg_stream( p_info->p_api);
#endif
/* SPR# 9068 : End Fix */
/* SPR# 8677 : End Fix */
		}
		/* SPR 8192 Fix end */
	}
}

#ifdef SCCP_INCLUDE_CO_SERVICE

/***************************************************************************
**
**      FUNCTION :
**          corresponds to Q.714/C.1/sheet-1 on the event 
**          Connectionoriented message [ SCOC -> SCRC ]
**
****************************************************************************
**
**      DESCRIPTION :
**         Routes a connectionoriented message
**         determines routing indicator depending on called address and
**         calls appropriate routing function
**
**      NOTE :
**
***************************************************************************/

void 
sccp_route_co_msg 
#ifdef ANSI_PROTO
  (msg_info_t * p_info)
#else
  (p_info)
  msg_info_t * p_info ;
#endif
{
  error_t	 ecode;

  if (IS_CD_IE_PRESENT (p_info))
  {
      /** SPR # 4046 Fix Start **/
      /** Check whether the called addr contains sufficient information 
      *** for routing -  This was earlier done while parsing
	  **/
      if (p_info->cd_addr.pc_ind)
      {
        if (! ( (p_info->cd_addr.gti) || 
                (p_info->cd_addr.ssn_ind && (p_info->cd_addr.ssn != 0)) ) )
        {

            SC_STAT_Q752_TS_TRFAIL_SPEC_ADDR();
            SC_STAT_Q752_INR_TRFAIL_SPEC_ADDR();

          RC_TRC (("SCCP::SCRC: Called Addr contains insufficient information -"
               " Routing failed\n"));
          p_info->rel_cause = SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE;
          p_info->event = SCCP_ROUTE_FAIL_EVENT;
          if ((p_info->p_ccb != SS7_NULL) && 
              (IS_COUPLING_PRESENT (p_info->p_ccb)))
                SET_RELAY_MSG (p_info) ;
          sccp_handle_co_mesg (p_info, &ecode);
          return;
        }
      }
      else
      {
        if (! p_info->cd_addr.gti)
        {

          SC_STAT_Q752_TS_TRFAIL_SPEC_ADDR();
          SC_STAT_Q752_INR_TRFAIL_SPEC_ADDR();

          RC_TRC (("SCCP::SCRC: Called Addr contains insufficient information -"
               " Routing failed\n"));
          p_info->rel_cause = SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE;
          p_info->event = SCCP_ROUTE_FAIL_EVENT;
          if ((p_info->p_ccb != SS7_NULL) && 
              (IS_COUPLING_PRESENT (p_info->p_ccb)))
                SET_RELAY_MSG (p_info) ;
          sccp_handle_co_mesg (p_info, &ecode);
          return;
        } 
      }
      /** SPR # 4046 Fix End **/

      if (p_info->cd_addr.pc_ind)
      {
        /* GT + DPC */
        if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,
                                                 p_info->cd_addr.pc)))
        {

		  SC_STAT_Q752_TS_ROUTE_FAIL;
		  SC_STAT_Q752_INR_ROUTE_FAIL;

		  /** SPR # 4052 Fix Start **/
          RC_TRC (("SCCP::SCRC: pc %d nw %d unknown in called addr unknown - "
               " Routing failed\n", p_info->cd_addr.pc, p_info->nw_id));
          /** SPR # 9672 Fix Start **/
          p_info->rel_cause = SCCP_RFC_DESTINATION_ADDRESS_UNKNOWN;
          /** SPR # 9672 Fix end **/
          p_info->event = SCCP_ROUTE_FAIL_EVENT;
          if ((p_info->p_ccb != SS7_NULL) && 
              (IS_COUPLING_PRESENT (p_info->p_ccb)))
                SET_RELAY_MSG (p_info) ;
          sccp_handle_co_mesg (p_info, &ecode);
		  /** SPR # 4052 Fix End **/
          return;
        }

        if (p_info->p_sp->local)
        {
          if (p_info->cd_addr.ssn_ind)
          {
              sccp_route_translated_local_msg (p_info);
          }
          else
          {
            p_info->cd_addr.rout_ind = ROUTE_ON_GT;
            sccp_translate_route_msg (p_info);
          }
        }
        else
        {
          /* Set the routing indicator */
          if (p_info->cd_addr.gti)
            p_info->cd_addr.rout_ind = ROUTE_ON_GT;
          else
            p_info->cd_addr.rout_ind = ROUTE_ON_SSN;

	  /* SPR 1275: Start fix
	   * check if PC is accessible and SCCP is not-probihited 
	   */
	  if (IS_SP_PROHIBITED(p_info->p_sp)) 
	  {
		RC_TRC (("SCCP::SCRC: SP (pc %u, nw_id %d) "
               		"not accessible.\n", p_info->p_sp->pc, 
					      p_info->p_sp->nw_id));
		SC_STAT_Q752_TS_PC_UNAVAIL;
		SC_STAT_Q752_INR_PC_UNAVAIL;
#ifdef SCCP_INCLUDE_CO_SERVICE
		if (p_info->msg_type == CR_MSG_TYPE)  
			p_info->rel_cause = SCCP_RFC_ACCESS_FAILURE;
		else 
                	p_info->rel_cause = SCCP_RLSDC_MTP_FAILURE;
                p_info->event = SCCP_ROUTE_FAIL_EVENT;
                if ((p_info->p_ccb != SS7_NULL) && 
			(IS_COUPLING_PRESENT (p_info->p_ccb)))
                      SET_RELAY_MSG (p_info) ;

#endif
                sccp_handle_co_mesg (p_info, &ecode);
		return;
	  }
	  if (IS_SCCP_PROHIBITED(p_info->p_sp))
	  {
		RC_TRC (("SCCP::SCRC: SCCP (pc %u, nw_id %d) "
               		"not accessible.\n", p_info->p_sp->pc, 
					      p_info->p_sp->nw_id));

		SC_STAT_Q752_TS_PC_UNAVAIL;
		SC_STAT_Q752_INR_PC_UNAVAIL;

#ifdef SCCP_INCLUDE_CO_SERVICE
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_BCGR) || defined(SCCP_CHINESE)
        if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_BCGR) || (COMPARE_CHINESE))
        	{
			if (p_info->msg_type == CR_MSG_TYPE)
			  p_info->rel_cause = SCCP_RFC_SCCP_FAILURE;
			else 
                	  p_info->rel_cause = SCCP_RLSDC_SCCP_FAILURE;
		}
#endif

#if defined(SCCP_ANSI) 
	if (COMPARE_ANSI) 
        	{
			if (p_info->msg_type == CR_MSG_TYPE)
			  p_info->rel_cause = SCCP_RFC_ACCESS_FAILURE;
			else 
                	  p_info->rel_cause = SCCP_RLSDC_MTP_FAILURE;
		}
#endif

                p_info->event = SCCP_ROUTE_FAIL_EVENT;
                if ((p_info->p_ccb != SS7_NULL) && 
                       (IS_COUPLING_PRESENT (p_info->p_ccb)))
                      SET_RELAY_MSG (p_info) ;

#endif
                sccp_handle_co_mesg (p_info, &ecode);
		return;
	  }

	  /* SPR 1275: End fix */
 
          /* GR changes: Start
           * if mesg type is CR_MSG_TYPE and ROUTE_ON_SSN and 
           * SSN ind is set, check if subsystem is available
           */
 
#ifdef SCCP_INCLUDE_CO_SERVICE
          if ((p_info->msg_type == CR_MSG_TYPE) &&
				(p_info->p_ccb != SS7_NULL) &&  
                (!IS_COUPLING_PRESENT (p_info->p_ccb)) &&
		    (p_info->cd_addr.ssn_ind) &&
                        (p_info->cd_addr.rout_ind == ROUTE_ON_SSN))
          {
 
                if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss
                        (p_info->p_sp, p_info->cd_addr.ssn)))
 
                {

					SC_STAT_Q752_TS_UNEQUIPPED_SS;
					SC_STAT_Q752_INR_UNEQUIPPED_SS;

                   RC_TRC (("SCCP::SCRC: Subsystem (pc %u, ssn %d) "
                        "unequipped.\n", p_info->cd_addr.pc,
                                              p_info->cd_addr.ssn));
                   p_info->rel_cause = SCCP_RFC_UNEQUIPPED_USER;
                   p_info->event = SCCP_ROUTE_FAIL_EVENT;
                   if (	(IS_COUPLING_PRESENT (p_info->p_ccb)))
                      SET_RELAY_MSG (p_info) ;
                   sccp_handle_co_mesg (p_info, &ecode);
                   return;
                }
 
                if (IS_SS_PROHIBITED(p_info->p_ss))
                {
                   RC_TRC (("SCCP::SCRC: Subsystem (pc %u, ssn %d) "
                        "not available.\n", p_info->cd_addr.pc,
                                              p_info->cd_addr.ssn));
                   p_info->rel_cause = SCCP_RFC_SUBSYSTEM_FAILURE;
                   p_info->event = SCCP_ROUTE_FAIL_EVENT;
                  if ((p_info->p_ccb != SS7_NULL) && 
                   	(IS_COUPLING_PRESENT (p_info->p_ccb)))
                      SET_RELAY_MSG (p_info) ;

					SC_STAT_Q752_TS_SS_UNAVAIL;
					SC_STAT_Q752_INR_SS_UNAVAIL;

                   sccp_handle_co_mesg (p_info, &ecode);
                   return;
                }
           }
#endif     /* SCCP_INCLUDE_CO_SERVICE */
           /* GR changes: End */

          sccp_compat_test_fwd_msg (p_info);
        }
      }
      else
      {  /* GT only or GT + SSN */
        sccp_translate_route_msg (p_info);
      }

      return;
  }
  else
  {
	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,
                                                 p_info->dpc)))
	{

		SC_STAT_Q752_TS_ROUTE_FAIL;
		SC_STAT_Q752_INR_ROUTE_FAIL;

		RC_TRC (("SCCP::SCRC: pc %d nw %d unknown" 
				" msg dropped\n", p_info->dpc, p_info->nw_id)); 
		return;
	 }

	/* check if PC is accessible and SCCP is not-probihited */
	if (IS_SP_PROHIBITED(p_info->p_sp))
	{
		RC_TRC (("SCCP::SCRC: SCCP (pc %u, nw_id %d) "
               		"not accessible.\n", p_info->cd_addr.pc, 
					      p_info->nw_id));
		SC_STAT_Q752_TS_PC_UNAVAIL;
		SC_STAT_Q752_INR_PC_UNAVAIL;
#ifdef SCCP_INCLUDE_CO_SERVICE
		if (p_info->msg_type == CR_MSG_TYPE)
			p_info->rel_cause = SCCP_RFC_ACCESS_FAILURE;
		else 
                	p_info->rel_cause = SCCP_RLSDC_MTP_FAILURE;
                p_info->event = SCCP_ROUTE_FAIL_EVENT;
                if ((p_info->p_ccb != SS7_NULL) && 
                  	(IS_COUPLING_PRESENT (p_info->p_ccb)))
                      SET_RELAY_MSG (p_info) ;
#endif
                sccp_handle_co_mesg (p_info, &ecode);
		return;
	}
	if (IS_SCCP_PROHIBITED(p_info->p_sp))
	{
		RC_TRC (("SCCP::SCRC: SCCP (pc %u, nw_id %d) "
               		"not accessible.\n", p_info->cd_addr.pc, 
					      p_info->nw_id));

		SC_STAT_Q752_TS_PC_UNAVAIL;
		SC_STAT_Q752_INR_PC_UNAVAIL;

#ifdef SCCP_INCLUDE_CO_SERVICE
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined(SCCP_BCGR) || defined(SCCP_CHINESE)
        if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_BCGR) || (COMPARE_CHINESE))
        {
		if (p_info->msg_type == CR_MSG_TYPE)
			p_info->rel_cause = SCCP_RFC_SCCP_FAILURE;
		else 
                	p_info->rel_cause = SCCP_RLSDC_SCCP_FAILURE;
		}
#endif

#if defined(SCCP_ANSI) 
	if (COMPARE_ANSI)
    {
		if (p_info->msg_type == CR_MSG_TYPE)
			p_info->rel_cause = SCCP_RFC_ACCESS_FAILURE;
		else 
                	p_info->rel_cause = SCCP_RLSDC_MTP_FAILURE;
	}
#endif
                p_info->event = SCCP_ROUTE_FAIL_EVENT;
                if ((p_info->p_ccb != SS7_NULL) && 
                	(IS_COUPLING_PRESENT (p_info->p_ccb)))
                      SET_RELAY_MSG (p_info) ;
#endif
                sccp_handle_co_mesg (p_info, &ecode);
		return;
	}

	sccp_determine_restr_fwd_msg (p_info);
  }
}
#endif /* #ifdef SCCP_INCLUDE_CO_SERVICE */

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.1/sheet-3/node-9
****************************************************************************
**
**      DESCRIPTION :
**         calls translate function and forwards message 
**
**      NOTE :
**
***************************************************************************/

void 
sccp_translate_route_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	return_t translation_result;
#ifdef SCCP_INCLUDE_CO_SERVICE
	error_t	 ecode;
#endif

	RC_TRC (("SCCP::SCRC: routing on title. translating ..\n"));

	translation_result = sccp_translate(p_info);

	if (SS7_SUCCESS == translation_result)
	{
		RC_TRC (("SCCP::SCRC: translation success\n"));

		if (ROUTE_ON_SSN == p_info->cd_addr.rout_ind)
		{
			RC_TRC (("SCCP::SCRC: routing on SSN\n"));
			if (p_info->p_sp->local)
			{
				RC_TRC (("SCCP::SCRC: routing to local pc %u nw %d\n:",
				         p_info->p_sp->pc, p_info->p_sp->nw_id));

                		/* CSR: 1-8230160 */
				p_info->cd_addr.rout_ind = p_info->received_rout_ind;

                                /* SPR GR: UDTS/XUDTS does not contain protocol class */
			        if ((p_info->msg_type == UDTS_MSG_TYPE) ||
   					(p_info->msg_type == XUDTS_MSG_TYPE))
						/* Local message. SCRC -> SCLC */
						sccp_handle_cl_msg (p_info);
				else
				{
				   switch (p_info->proto_class & 0x0f)
				   {
					case  PROTOCOL_CLASS_0 :
/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
						sccp_handle_cl_msg (p_info);
						/** SPR Fix 8623 starts **/
						break;
						/** SPR Fix 8623 fix ends **/
#endif
/* SPR # 7470 Fix End */
					case PROTOCOL_CLASS_1 :
						/* Local message. SCRC -> SCLC */
/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
						if(( 
#ifdef SCCP_BROADBAND
						(LUDT_MSG_TYPE == p_info->msg_type) || 
#endif
						(UDT_MSG_TYPE == p_info->msg_type))&& \
						(SS7_TRUE == dsccp_class1_timer_status))
						{
							dsccp_store_class1_messages(p_info->p_api);
						}
						else
#endif
/* SPR # 7470 Fix End */
						sccp_handle_cl_msg (p_info);
						break;
#ifdef SCCP_INCLUDE_CO_SERVICE
					case PROTOCOL_CLASS_2 :
					case PROTOCOL_CLASS_3 :
						/* Local message. SCRC->SCOC */
						sccp_handle_co_mesg (p_info, &ecode);
						break;
#endif
					default :
						break;
				   }
				}
			}
			else
			{
				/* Availability already checked by translation function */
				RC_TRC (("SCCP::SCRC: routing to remote pc %u nw %d\n:",
				         p_info->p_sp->pc, p_info->p_sp->nw_id));

				sccp_compat_test_fwd_msg (p_info);
			}
		}
		else
		{
			sccp_compat_test_fwd_msg (p_info);
		}
	}
	else
	{
		RC_TRC (("SCCP::SCRC: translation failed\n"));


#ifdef SCCP_INCLUDE_CO_SERVICE
		if (sccp_is_co_msg (p_info->msg_type))
		{
/*			p_info->rel_cause = SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE;*/
			p_info->event = SCCP_ROUTE_FAIL_EVENT;
			sccp_handle_co_mesg (p_info, &ecode);
		}
		else
#endif
			sccp_handle_routing_failure (p_info);
	}
}

/***************************************************************************
**
**      FUNCTION :
**          Q.714/C.1/sheet-3/node-6
****************************************************************************
**
**      DESCRIPTION :
**          routes a message destined for a local subsystem
**
**      NOTE :
**
***************************************************************************/

void 
sccp_route_translated_local_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	pc_t local_pc;
#ifdef SCCP_INCLUDE_CO_SERVICE
	error_t ecode;
#endif

	p_info->cd_addr.rout_ind = ROUTE_ON_SSN;

	/* SCMG message may not contain PC in the called party address */
	if (SCMG_SSN == p_info->cd_addr.ssn)
	{
		p_info->p_ss = &p_info->p_sp->scmg_ss;
		sccp_handle_cl_msg (p_info);
		return;
	}

	if (p_info->cd_addr.pc_ind) local_pc = p_info->cd_addr.pc;
	else local_pc = p_info->dpc;

	if ((SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id,
	              local_pc))) ||
	    (!p_info->p_sp->local))
	{
		RC_TRC (("Unknown local pc %u\n", local_pc));
		/** SPR # 2816 Fix Start **/
		p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING;
#ifdef SCCP_INCLUDE_CO_SERVICE
                p_info->rel_cause = SCCP_RFC_DESTINATION_ADDRESS_UNKNOWN;
                p_info->event = SCCP_ROUTE_FAIL_EVENT;
#endif
                SC_STAT_Q752_TS_ROUTE_FAIL;
                SC_STAT_Q752_INR_ROUTE_FAIL;
		sccp_handle_routing_failure (p_info);
		/** SPR # 2816 Fix End **/
		return;
	}

#ifdef SCCP_INCLUDE_CO_SERVICE
	/* routing is required for CR message only */
	if (sccp_is_co_msg (p_info->msg_type) && (p_info->msg_type != CR_MSG_TYPE))
	{
		sccp_handle_co_mesg (p_info, &ecode);
		return;
	}
#endif
	p_info->p_ss = sccp_db_find_ss (p_info->p_sp, p_info->cd_addr.ssn);

	/* SPR 1503: Check if subsystem is registered */
	if ((p_info->p_ss) && (p_info->p_ss->registered))  /* SS equipped */
	{
		if (p_info->p_ss->allowed) 
		{
#ifdef SCCP_INCLUDE_CO_SERVICE
			if (p_info->msg_type == CR_MSG_TYPE)
				sccp_handle_co_mesg (p_info, &ecode);
			else
#endif
/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
			if((
#ifdef SCCP_BROADBAND
				(LUDT_MSG_TYPE == p_info->msg_type) || 
#endif
				(UDT_MSG_TYPE == p_info->msg_type))&& \

   				(SS7_TRUE == dsccp_class1_timer_status))
   			{
   				dsccp_store_class1_messages(p_info->p_api);
   			}
   			else
#endif
/* SPR # 7470 Fix End */

				sccp_handle_cl_msg (p_info);
			return;
		}
		else
		{
			RC_TRC (("SCCP::SCRC: subsytem %d on pc %u nw %d unavailable\n",
			         p_info->p_ss->ssn, local_pc, p_info->nw_id));

			sccp_msg_unavail_system (p_info);
			SC_STAT_Q752_TS_SS_UNAVAIL;
			SC_STAT_Q752_INR_SS_UNAVAIL;

			p_info->ret_cause = SCCP_SUBSYSTEM_FAILURE;
#ifdef SCCP_INCLUDE_CO_SERVICE
			 p_info->rel_cause = SCCP_RFC_SUBSYSTEM_FAILURE;
			 p_info->event = SCCP_ROUTE_FAIL_EVENT;
#endif
		}
	}
	else
	{
		SC_STAT_Q752_TS_UNEQUIPPED_SS;
		SC_STAT_Q752_INR_UNEQUIPPED_SS;

		RC_TRC (("SCCP::SCRC: subsystem %d on pc %u nw %d unequipped\n", 
		         p_info->cd_addr.ssn, local_pc, p_info->nw_id));

		/* Inform Routing failure to OMAP */
		p_info->ret_cause = SCCP_UNEQUIPPED_USER;


#ifdef SCCP_INCLUDE_CO_SERVICE
			 p_info->rel_cause = SCCP_RFC_UNEQUIPPED_USER;
			 p_info->event = SCCP_ROUTE_FAIL_EVENT;
#endif
	}
#ifdef SCCP_INCLUDE_CO_SERVICE
	if (p_info->msg_type == CR_MSG_TYPE)
		sccp_handle_co_mesg (p_info, &ecode);
	else
#endif
	{
		/* sccp_build_n_notice_ind_api (p_info); */
		sccp_handle_routing_failure (p_info);
	}

	return;
}

/***************************************************************************
**
**      FUNCTION :
**        Corresponds to Q.714/C.1/sheet-4/node-7
****************************************************************************
**
**      DESCRIPTION :
**         does compatibility check. if changes are not needed then the
**         msg is forwarded else the chanes are handled
**
**      NOTE :
**
***************************************************************************/

void 
sccp_compat_test_fwd_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{

	Boolean          changes_needed;
#ifdef SCCP_INCLUDE_CO_SERVICE
	error_t          ecode;
    sccp_nsdu_org_t  nsdu_org;
#endif
	/* Fix for SPR No: 13444 start */
	if (!sls_assigned)
		if (!((p_info->msg_type == UDTS_MSG_TYPE) || (p_info->msg_type == XUDTS_MSG_TYPE)))
			p_info->sls = sccp_assign_sls(&p_info->cd_addr,
										&p_info->cg_addr,
										p_info->sls,
										(p_info->proto_class & 0x0f));
	sls_assigned = SS7_TRUE;
	/* Fix for SPR No: 13444 stop */

	/* check the netowrk restrictions for outgoing n/w */
	/* In case of CLASS-2 and CLASS-3, if n/w restrictions
	   mismatch then a copuled connection is performed and
	   SCCP will do the relay node functionality.
	*/
#ifdef SCCP_INCLUDE_CO_SERVICE
	if (sccp_is_co_msg (p_info->msg_type))
	{
		/* If message is received from n/w then see if this node
		   is a relay node where coupling is required.
		 */

		if (MTP3_UP_TRANSFER_INDICATION == GET_API_ID(p_info->p_api))	
		{
            nsdu_org.opc = p_info->dpc;
            nsdu_org.nw_id = DEFAULT_NW_ID;
			if (!IS_RELAY_MSG(p_info) && sccp_is_relay_coupling_node (&p_info->cd_addr, &nsdu_org))
			{
				sccp_handle_co_mesg (p_info, &ecode);
				return;
			}
		}
	}
	else
#endif
	{
#ifdef SCCP_BROADBAND
        /* If Broadband Network supported below LUDT should go */
        if ((sc_opt.nw_type == SS7_BROADBAND_NETWORK) &&
            (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api)) &&
            (p_info->msg_type == UDT_MSG_TYPE))
        {
            /* Data request from User; Should send LUDT on Broadband n/w */
            p_info->msg_type = LUDT_MSG_TYPE ;
            /*
             * With LUDT message segmentation parameter should always
             * be present
             */
            p_info->segment.slr = sccp_assign_slr() ;
            p_info->segment.rem_seg = 0 ;
            p_info->segment.f_bit = 1 ;
			/** SPR 10882 - Fix Start **/
			p_info->segment.spare_bit = 0;
			/** SPR 10882 - Fix End  **/
            SET_SEGMENTATION_PRESENT (p_info) ;
        }
#endif

    	changes_needed = sccp_perform_compat_test(p_info);

    	if (changes_needed)
    	{
			/** SPR # 3041 Fix Start **/
			/* Conversion of UDT->XUDT, XUDT->XUDT is not supported
			** Segment the message only if it is locally originated;
			** otherwise, truncate the data and return the message
			** NOTE:: the api id of locally originated service 
			** messages will not be N_UDT_REQ but in this case
			** the control will never reach here because of the
			** check for data segment length after parsing the
			** nw msg
			*/
			if (SCCP_N_UNITDATA_REQUEST != GET_API_ID(p_info->p_api))
			{
				p_info->data.len = sc_opt.seg_size;
				p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING;
				sccp_handle_routing_failure (p_info);
				return;
			}
			/** SPR # 3041 Fix End **/

      		sccp_handle_changes_needed (p_info);
      		return;
    	}
	}

    sccp_determine_restr_fwd_msg (p_info);

  return ;
}

/***************************************************************************
**
**      FUNCTION :
**        Corresponds to Q.714/C.1/sheet-4/node-12
****************************************************************************
**
**      DESCRIPTION :
**        determines restriction
**
**      NOTE :
**
***************************************************************************/

void 
sccp_determine_restr_fwd_msg 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	Boolean restricted;
#ifdef SCCP_INCLUDE_CO_SERVICE
	error_t ecode;
#endif

	restricted = sccp_determine_restriction (p_info);

	if (restricted)
	{
		RC_TRC (("SCCP::SCRC: Traffic limitation. msg dropped"));

		SC_STAT_Q752_TS_NW_CONGESTION;
		SC_STAT_Q752_INR_NW_CONGESTION;

		SC_STAT_Q752_TS_SS_CONGESTION;
		SC_STAT_Q752_INR_SS_CONGESTION;

#ifdef SCCP_INCLUDE_CO_SERVICE
		if (sccp_is_co_msg (p_info->msg_type))
		{
/** SPR Fix 8621 fix start **/
			if(p_info->msg_type == CR_MSG_TYPE)
            {
                p_info->rel_cause = SCCP_RFC_NR_QOS_NOT_AVAILABLE_NON_TRANSIENT;
            }
            else
            {
                p_info->rel_cause = SCCP_RLSDC_NETWORK_CONGESTION;
            }
/** SPR Fix 8621 fix end **/

			p_info->event = SCCP_ROUTE_FAIL_EVENT;
			sccp_handle_co_mesg (p_info, &ecode);
		}
		else
#endif
		{
			p_info->ret_cause = SCCP_NETWORK_CONGESTION;
			sccp_handle_routing_failure (p_info);
		}
		return;
	}

	sccp_process_hop_counter (p_info);
	sccp_m3_transfer_request (p_info);
}

