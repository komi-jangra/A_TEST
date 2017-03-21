/***************************************************************************
**
**  FILE NAME:
**      sc_rcmsc.c
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
**  27Apr2004 Hitesh Sharma    -----  Fixed SPR # 13422 
**  14Nov2002 Salil Agrawal    -----  Fixed SPR # 12099 
**  14Nov2002 Ashish Sawalkar  -----  Fixed SPR # IMP_SPR
**  09apr2002 salil agrawal    -----  Fixed SPR # 8530
**  14Mar2002 Sachin bhatia    -----  Fixed SPR # 8596
**  04Nov2000 Arun Kumar       -----  Adding TRAFFIC Statistics
**  03Nov200  Vikas                   Fixed SPR # 4524
**  10May2000 Ramu Kandula            Fixed SPR # 3540
**  24Feb2000 Ramu Kandula            Fixed SPR # 2731
**  24Feb2000 Ramu Kandula            Fixed SPR # 2696 
**	20Aug'98 Anil K.		   -----  CR message added.
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 2000, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"
/* spr 8530 starts */
/* was not matched with spec
#define MAX_UNIT_DATA_IMP          4
#define MAX_UNIT_DATA_SERVICE_IMP  3
*/

#define MAX_UNIT_DATA_IMP          6
#define MAX_UNIT_DATA_SERVICE_IMP  7

/* spr 8530 starts */


/***************************************************************************
**
**      FUNCTION :
**         corresponds to C.1/Q.714 sheet 11
****************************************************************************
**
**      DESCRIPTION :
**         Adjusts importance value and performs traffic limitation
**
**      NOTE :
**
***************************************************************************/

Boolean 
sccp_determine_restriction 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	U32bit rand_num;
	Boolean restricted = SS7_FALSE;
	U8bit msg_priority, min_msg_priority, max_msg_priority;
	U8bit scmg_msg_type;
	sp_entry_t *p_sp;

#if defined(SCCP_ITU) || defined(SCCP_JAPANESE) || defined (SCCP_ETSI)
	if ((COMPARE_ITU) || (COMPARE_JAPANESE) || (COMPARE_ETSI))
	{
		if (IS_IMPORTANCE_PRESENT(p_info))
		{

#if 0 /** SPR# IMP_SPR Start Fix **/
			/* Check if importance exceeds permitted maximum
		   	If it does reduce it to permitted max */

			if ((UDT_MSG_TYPE == p_info->msg_type) ||
		    	(XUDT_MSG_TYPE == p_info->msg_type))
			{
				if (p_info->importance > MAX_UNIT_DATA_IMP)
					p_info->importance = MAX_UNIT_DATA_IMP;
			}
			else /* UDTS OR XUDTS msg */
			{
				if (p_info->importance > MAX_UNIT_DATA_SERVICE_IMP)
					p_info->importance = MAX_UNIT_DATA_SERVICE_IMP;
			}
#endif 

			/* Checking if importance value is within the range, adjusting 
			 * if not 
			 */
			min_msg_priority = sccp_get_min_message_priority(p_info->msg_type);
			max_msg_priority = sccp_get_max_message_priority(p_info->msg_type);

			msg_priority = p_info->importance;

			if (msg_priority < min_msg_priority)	
				p_info->importance = min_msg_priority;
			else if (msg_priority > max_msg_priority)
				p_info->importance = max_msg_priority;

		}
		else
		{
			/* Assigning default (mininum) importance */

			p_info->importance = sccp_get_min_message_priority(p_info->msg_type);

#if 0
**			if (p_info->msg_type == UDT_MSG_TYPE) 
**			{
**				if ((p_info->cd_addr.ssn_ind) && 
**					(p_info->cd_addr.ssn==SCMG_SSN))
**				{
**					scmg_msg_type = *(p_info->data.p);
**
**					p_info->importance = 
**					sccp_get_min_scmg_message_priority(scmg_msg_type);
**				}
**			}
#endif
		}

#ifdef SCCP_INCLUDE_CO_SERVICE
		if (sccp_is_co_msg(p_info->msg_type))
		{
			if (p_info->msg_type == CR_MSG_TYPE)
				p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cd_addr.pc);
			else
				p_sp = sccp_db_find_sp(p_info->nw_id, p_info->dpc);
		}
		else
#endif
		{
			p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cd_addr.pc);
		}

		if (p_sp == SS7_NULL)
		{
			restricted = SS7_TRUE;
			return (restricted);
		}
	
		if (p_info->importance < p_sp->rl)
			restricted = SS7_TRUE;
		else
		{
			if (p_info->importance == p_sp->rl)
			{
					rand_num = ss7_rand ();
	
				switch (p_sp->rsl)
				{
					case 0:
						restricted = SS7_FALSE;   /* 0 % discarded */
						break;
	
					case 1:
						if (0 == (rand_num & 0x3)) /* Discard 25 % */
							restricted = SS7_TRUE;
	
						break;
	
					case 2:
						if (0 == (rand_num & 0x1)) /* Discard 50 % */
							restricted = SS7_TRUE;
	
						break;
	
					case 3:
						if (! (0 == (rand_num & 0x3))) /* Discard 75 % */
							restricted = SS7_TRUE;
	
						break;
	
					default:
						break;
				}
	
				if (restricted)
					RC_TRC (("SCCP::SCRC: restriction due to traffic "
				         	"limitation\n"));
			}
			else
				restricted = SS7_FALSE;
		}
	}
#endif

	/** SPR # 2696 Fix Contd. **/
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

		msg_priority = min_msg_priority;

		/** SPR # 2731 Fix Start **/
		if (IS_IMPORTANCE_PRESENT(p_info))
		{
			if ( (p_info->importance < min_msg_priority) || 
				 (p_info->importance > max_msg_priority) )
			{
				/* Cannot send the message with this priority */
				restricted = SS7_TRUE;
				return restricted;
			}

			msg_priority = p_info->importance;
		}
		/** SPR # 2731 Fix End **/
		
		/** SPR # 3540 Fix Start **/
		p_sp = SS7_NULL;
		/* SPR # 8596 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
		/* SPR # 8596 Fix Ends */
		if (sccp_is_co_msg(p_info->msg_type) )
		{
			if (p_info->msg_type == CR_MSG_TYPE)
				p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cd_addr.pc);
			else
				p_sp = sccp_db_find_sp(p_info->nw_id, p_info->dpc);
		}
		else
		/* SPR # 8596 Fix Start */
#endif
		/* SPR # 8596 Fix Ends */
		{
			/* Connection-less message */
			p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cd_addr.pc);
		}
		/** SPR # 3540 Fix End **/
		
		if (p_sp != SS7_NULL)
		{
			if (msg_priority < p_sp->cls)
				restricted = SS7_TRUE;
		}
		else
		{
			/** trying to send the message to an unknown dpc !! **/
			restricted = SS7_TRUE;
		}
	}
#endif
	/** SPR # 2696 Fix End **/
	
	return restricted;
}

/***************************************************************************
**
**      FUNCTION :
**         sccp_process_hop_counter
****************************************************************************
**
**      DESCRIPTION :
**          This function assigns the configured initial value of the hop
**          counter to a locally generated packet
**
**      NOTE :
**
***************************************************************************/

void 
sccp_process_hop_counter 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	if (MTP3_UP_TRANSFER_INDICATION == GET_API_ID(p_info->p_api)) 
		return;

#ifdef SCCP_INCLUDE_CO_SERVICE
	if (CR_MSG_TYPE == p_info->msg_type)
	{
		p_info->hop_counter = INITIAL_HOP_COUNTER_VALUE;
		SET_HOP_COUNTER_PRESENT (p_info);
	}
#endif
	if ( (XUDT_MSG_TYPE == p_info->msg_type)
#ifdef SCCP_BROADBAND
		|| (LUDT_MSG_TYPE == p_info->msg_type)
#endif
		)
	{
		p_info->hop_counter = INITIAL_HOP_COUNTER_VALUE;
	}
}

/***************************************************************************
**
**      FUNCTION :
**          interfaces with the porting title translation function
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

return_t 
sccp_translate 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	return_t translation_result;
	gtt_ip_t gtt_ip;
	gtt_op_t gtt_op;
#ifdef SCCP_INCLUDE_CO_SERVICE
	U8bit event;
#endif
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
    U8bit count ;
#endif

	/* Fill the input structure from called address */
#ifdef SCCP_INCLUDE_CO_SERVICE
	event = p_info->event;
#endif
	gtt_ip.ssn_ind = p_info->cd_addr.ssn_ind;
	if (p_info->cd_addr.ssn_ind)
		gtt_ip.ssn = p_info->cd_addr.ssn;
	else
		gtt_ip.ssn = 0;

	gtt_ip.gti = p_info->cd_addr.gti;
	if (p_info->cd_addr.gti)
	{
		gtt_ip.gt_len = p_info->cd_addr.gt_len;
		sccp_memcpy (&gtt_ip.gt[0], &(p_info->cd_addr.gt[0]), gtt_ip.gt_len);
	}

	RC_TRC (("SCCP::SCRC: GTT input : gtt_ip.\n"));

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if (IS_ISNI_PRESENT(p_info))
	{
	  gtt_ip.isni.len = p_info->isni.len ;
      for (count = 0; count < MAX_ISNI_LEN; count++)
	      gtt_ip.isni.list [count] = p_info->isni.list [count] ;
	}
#endif

/*	if(p_info->cd_addr.pc_ind)
	{
		  if(p_info->cg_addr.ssn_ind)
			gsn_gtt_list[gtt_counter].ssn = p_info->cg_addr.ssn;
		else
	  		gsn_gtt_list[gtt_counter].ssn = 0;
	
		if (p_info->cg_addr.gti)
		{
			gsn_gtt_list[gtt_counter].gt_len = p_info->cg_addr.gt_len;
			sccp_memcpy (&gsn_gtt_list[gtt_counter].input[0], &(p_info->cg_addr.gt[0]),gsn_gtt_list[gtt_counter].gt_len);
		}

		gsn_gtt_list[gtt_counter].pc = p_info->dpc;

		if(p_info->cg_addr.rout_ind == ROUTE_ON_GT)
	  		gsn_gtt_list[gtt_counter].output[0] = '*';
		else
	 	 gsn_gtt_list[gtt_counter].output[0] = '-';

		gtt_counter++;
	}
*/	
	

	translation_result = sccp_global_title_translate (&gtt_ip, &gtt_op);
	SET_TRANSLATION_DONE(p_info);

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if (IS_ISNI_PRESENT(p_info))
	{
	  p_info->isni.len = gtt_op.isni.len ;
      for (count = 0; count < MAX_ISNI_LEN; count++)
	      p_info->isni.list [count] = gtt_op.isni.list [count] ;
	}
#endif

	if (SS7_FAILURE == translation_result)
	{
		switch (gtt_op.err_reason)
		{
			case SCCP_NO_TRANSLATION_ADDR_OF_SUCH_NATURE:
				SC_STAT_Q752_TS_TRFAIL_ADDR_NATURE();
				SC_STAT_Q752_INR_TRFAIL_ADDR_NATURE();
#ifdef SCCP_INCLUDE_CO_SERVICE
                                p_info->rel_cause = SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE;
#endif
				p_info->ret_cause = SCCP_NO_TRANSLATION_ADDR_OF_SUCH_NATURE;
				break;

			case SCCP_NO_TRANSLATION_FOR_SPECIFIC_ADDR:
				SC_STAT_Q752_TS_TRFAIL_SPEC_ADDR();
				SC_STAT_Q752_INR_TRFAIL_SPEC_ADDR();
				p_info->ret_cause = SCCP_NO_TRANSLATION_FOR_SPECIFIC_ADDR;
				break;

                        case SCCP_SUBSYSTEM_CONGESTION:
#ifdef SCCP_INCLUDE_CO_SERVICE
                                 p_info->rel_cause = SCCP_RFC_SUBSYSTEM_CONGESTION;
#endif
				p_info->ret_cause = SCCP_SUBSYSTEM_CONGESTION;
                                break;

                        case SCCP_SUBSYSTEM_FAILURE:
#ifdef SCCP_INCLUDE_CO_SERVICE
                               p_info->rel_cause = SCCP_RFC_SUBSYSTEM_FAILURE;
#endif
							/* SPR 9934 - Fix Start */
							SC_STAT_Q752_TS_SS_UNAVAIL;
							SC_STAT_Q752_INR_SS_UNAVAIL;
							/* SPR 9934 - Fix End   */
							p_info->ret_cause = SCCP_SUBSYSTEM_FAILURE ;
							break;

                        case SCCP_UNEQUIPPED_USER:
#ifdef SCCP_INCLUDE_CO_SERVICE
                              p_info->rel_cause = SCCP_RFC_UNEQUIPPED_USER;
#endif
						 	  p_info->ret_cause = SCCP_UNEQUIPPED_USER;
                              break;

                        case SCCP_MTP_FAILURE:
#ifdef SCCP_INCLUDE_CO_SERVICE
                              p_info->rel_cause = SCCP_RFC_DESTINATION_INACCESSIBLE;
#endif
							/* SPR 9934 - Fix Start */
							SC_STAT_Q752_TS_PC_UNAVAIL;
							SC_STAT_Q752_INR_PC_UNAVAIL;
							/* SPR 9934 - Fix End   */
						  	p_info->ret_cause = SCCP_MTP_FAILURE;
							break;

                        case SCCP_NETWORK_CONGESTION:
#ifdef SCCP_INCLUDE_CO_SERVICE
                             p_info->rel_cause = SCCP_RFC_ACCESS_CONGESTION;
#endif
							p_info->ret_cause = SCCP_NETWORK_CONGESTION;
							break;

                        case SCCP_UNQUALIFIED:
#ifdef SCCP_INCLUDE_CO_SERVICE
                             p_info->rel_cause = SCCP_RFC_UNQUALIFIED;
#endif
							 p_info->ret_cause = SCCP_UNQUALIFIED;
                             break;   

			default:
				p_info->ret_cause = SCCP_NO_TRANSLATION_ADDR_OF_SUCH_NATURE;
				break;
		}
		/* SPR 10852 - Ret reason to be assigned above */
		/*p_info->ret_cause = gtt_op.err_reason;*/
                /* SPR# 4543 Start  */
                /* Increment the Traffic(GTT Translation Failure) statistics */
                SC_STAT_TRAFFIC_INR_GTT_TR_FAIL();
                /* SPR# 4543 End */
		return translation_result;
	}

	if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp (p_info->nw_id, gtt_op.pc)))
	{
		RC_TRC (("SCCP::SCRC: GTT returns unknown pc %u\n", gtt_op.pc));
		p_info->ret_cause = gtt_op.err_reason;
		return SS7_FAILURE;
	}

	/* SPR-GR: Check for validity of subsystem also */
	if ((ROUTE_ON_SSN == gtt_op.rout_ind) && (p_info->p_sp->local))
	{

          if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss (p_info->p_sp, gtt_op.ssn)))
	  {
		RC_TRC (("SCCP::SCRC: GTT returns unknown subsystem %d on pc %u\n", 
					gtt_op.ssn, gtt_op.pc));
		p_info->ret_cause = gtt_op.err_reason;
		return SS7_FAILURE;
	  }
	}


	/* copy the output to called party address */
    	p_info->received_rout_ind = p_info->cd_addr.rout_ind;
	p_info->cd_addr.rout_ind = gtt_op.rout_ind;

/* spr 13422 starts */
#ifdef GTT_DPC_SSN_CHANGES
        if (!((ROUTE_ON_GT == gtt_op.rout_ind) && (SS7_FALSE == p_info->cd_addr.pc_ind)))
                p_info->cd_addr.pc_ind = SS7_TRUE;
#endif

/* spr 12099 starts */
#ifdef SCCP_GTT_CALLED_PARTY_ADDRESS_CHANGE
    if (ROUTE_ON_GT == gtt_op.rout_ind)
        p_info->cd_addr.pc_ind = SS7_FALSE;
    else
        p_info->cd_addr.pc_ind = SS7_TRUE;
#else
#ifndef GTT_DPC_SSN_CHANGES
    p_info->cd_addr.pc_ind = SS7_TRUE;
#endif
#endif
/* spr 12099 ends */
/* spr 13422 stops */

	p_info->cd_addr.pc = gtt_op.pc;
	p_info->cd_addr.ssn_ind = gtt_op.ssn_ind;
	if (gtt_op.ssn_ind)
		p_info->cd_addr.ssn = gtt_op.ssn;
	p_info->cd_addr.gti = gtt_op.gti;
	if (gtt_op.gti)
	{
		p_info->cd_addr.gt_len = gtt_op.gt_len;
		sccp_memcpy (&p_info->cd_addr.gt[0], &gtt_op.gt[0], gtt_op.gt_len);
	}
/* SPR 8596 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
/* SPR 8596 Fix Ends */ 
    event = p_info->event;
/* SPR 8596 Fix Start */
#endif
/* SPR 8596 Fix Ends */ 


	return translation_result;
}

/***************************************************************************
**
**      FUNCTION :
**         checks if segmentatiion is required
****************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE : SPR Fix 4524. In case of broadband , we just can check
**         this based on seg_size. In case of non-local data, we can check
**          this based on seg_size (As "Y" (according to Table19/Q.713)
**             is anyway >= data len). 
**          If it is local data, we need to check that data len <= MIN(Y,seg_size)
**
***************************************************************************/

Boolean 
sccp_perform_compat_test 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info ;
#endif
{
	/* See if the message has to be segmented */
    U16bit     max_data;

#ifdef SCCP_BROADBAND
  if (sc_opt.nw_type == SS7_BROADBAND_NETWORK)
  {
      max_data = sc_opt.seg_size;
  }
  else
#endif
  {
      /* We come here in case of narroband only */
      if (SCCP_N_UNITDATA_REQUEST != GET_API_ID(p_info->p_api))
      {
          /* Non local data */
          max_data = sc_opt.seg_size;
      }
      else
      {
          /* We come here only for locally originated data */
          /* Assume no segm and see if the data can fit in an XUDT */
          max_data  = sccp_calc_max_y (p_info, SS7_FALSE);
          if (max_data > sc_opt.seg_size)
              max_data = sc_opt.seg_size;
      }
   }

   if (p_info->data.len > max_data)
		return SS7_TRUE;
   else
		return SS7_FALSE;
}

