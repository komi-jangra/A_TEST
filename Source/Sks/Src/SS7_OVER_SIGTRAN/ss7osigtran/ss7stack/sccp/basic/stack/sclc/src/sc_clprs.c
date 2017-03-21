/***************************************************************************
**
**  FILE NAME:
**      sc_clprs.c
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
**	06Nov'03  Ganesh Kumar			  Fixed SPR # 13067
**  21oct'03  Ganesh Kumar	      	  Fixed SPR # 12551
**  28July2003 Sunil Dahiya           Fixed SPR # 12291
**  02Aug2002 Prateek Bidwalkar       Fixed SPR # 9442
**  03Nov2000 Arun Kumar     SPR#4543 Adding Traffic Statistics
**  28Feb2000 Ramu Kandula            Fixed SPR # 2770
**  28Feb2000 Ramu Kandula            Fixed SPR # 2760
**  24Feb2000 Ramu Kandula            Fixed SPR # 2731
**  24Feb2000 Ramu Kandula            Fixed SPR # 2693
**  11Feb2001 Ravi Shekhar            Fixed SPR # 8192 
**  28Mar2002 Pawanish Modi           Fixed SPR # 8603 
**	06AUG'98 Anil K.				  Connectionless ANSI added
**  19May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/


#include "sc_stgl.h"


/***************************************************************************
**
**      FUNCTION :
**         parses the n_unitdata request API
****************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
***************************************************************************/

return_t
sccp_parse_n_unitdata_req_api
#ifdef ANSI_PROTO
	(U8bit * p_api, msg_info_t * p_info, error_t * p_ecode)
#else
	(p_api, p_info, p_ecode)
	 U8bit 		* p_api;
	 msg_info_t 	* p_info;
	 error_t 	* p_ecode;
#endif
{
	U8bit * p_elem, num_opt_elem;

	/** Variables for SPR # 2760 Fix **/
	gtt_ip_t	gtt_ip;				
	gtt_op_t	gtt_op; 
	Boolean 	translation_result;
	extern sp_entry_t sccp_local_sp; 
	sp_entry_t *p_sp;
	ss_entry_t *p_ss;

	p_info->flag = 0;
	p_info->p_api = p_api;

	p_info->proto_class = 0; /* Default proto class 0 with no return option */

	p_info->nw_id = DEFAULT_NW_ID;

	p_elem = p_api + API_HEADER_LEN;

	/* Same func is used to decode address from MTP3 and TCAP 
	   So copy length appropriately */
	*(p_elem+1) = *p_elem;
	/*SPR FIX 8192 start */
	if (SS7_FAILURE == sccp_decode_sccp_addr (p_elem+1, &p_info->cd_addr))
	{
		return (SS7_FAILURE);	
	}
	/*SPR FIX 8192 end */
	p_elem += *p_elem + SCCP_ELEM_LEN_LEN;

	*(p_elem+1) = *p_elem;
	/*SPR FIX 8192 start */
	if (SS7_FAILURE == sccp_decode_sccp_addr (p_elem+1, &p_info->cg_addr))
	{
		return (SS7_FAILURE);
	}
	/* SPR FIX 8192 end */
	p_elem += *p_elem + SCCP_ELEM_LEN_LEN;


	/** SPR # 2770 Fix Start **/
	/** This dynamic check must not be done as the same checks are done by SCRC
	*** and routing failure is invoked if required.
	**/
#if 0
	/* dynamic check */
	if (p_info->cd_addr.pc_ind)
	{
		if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id,
		                                            p_info->cd_addr.pc)))
		{
			SC_A_TRC (("SCCP::SCLC: called addr pc %d nw %d "
			           "not know to sccp\n",
			           p_info->cd_addr.pc, p_info->nw_id));
			*p_ecode = ESS7_INVALID_API_ELEMENT;
			return SS7_FAILURE;
		}

		if ((p_info->cd_addr.ssn_ind) &&
		    (SS7_NULL == (p_info->p_ss = sccp_db_find_ss (p_info->p_sp,
		                                             p_info->cd_addr.ssn))))
		{
			SC_A_TRC (("SCCP::SCLC: called addr SSN %d pc %d nw %d "
			           "not know to sccp\n",
			           p_info->cd_addr.ssn, p_info->cd_addr.pc, p_info->nw_id));
			*p_ecode = ESS7_INVALID_API_ELEMENT;
			return SS7_FAILURE;
		}
	}
#endif
	/** SPR # 2770 Fix End **/

	/* data */
	p_info->data.len = GET_2_BYTE_LE (p_elem);
	/* SPR 12551 FIX Start */
	if( p_info->data.len<MIN_DATA_LEN)
	{
		*p_ecode = ESS7_INVALID_API_ELEMENT;
		return(SS7_FAILURE);
	}
	/* SPR 12551 FIX Start */
	p_info->data.p   = p_elem + SCCP_ELEM_LEN_LEN;
	p_elem += SCCP_ELEM_LEN_LEN;
	p_elem += p_info->data.len;

	num_opt_elem = GET_API_NELEM(p_api) - SCCP_N_UNITDATA_REQ_MIN_NELEM;

	while (num_opt_elem--)
	{
		switch (*p_elem++)
		{
			case SCCP_ELEM_SEQUENCE_CONTROL:
				p_elem += SCCP_ELEM_LEN_LEN;
				p_info->proto_class |= 1;
				p_info->sls = *p_elem++;
				CL_TRC (("SCCP::SCLC: sequence control elem %d\n",
				           p_info->sls));
				break;

			case SCCP_ELEM_RETURN_OPTION:
				CL_TRC (("SCCP::SCLC: return option present\n"));
				p_elem += SCCP_ELEM_LEN_LEN;
				if (SCCP_RETURN_MSG == *p_elem)
				{
					CL_TRC (("SCCP::SCLC: return option set\n"));
					p_info->proto_class |= RET_OPTN_MASK;
				}
				else
					CL_TRC (("SCCP::SCLC: return option not set\n"));
				p_elem++;
				break;

			/** SPR # 2731 Fix Start **/
			/** Importance parameter is used in ANSI and GR also **/
/* #if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) */
			case SCCP_ELEM_IMPORTANCE:
				/* if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI) */
				{
					p_elem += SCCP_ELEM_LEN_LEN;
					p_info->importance = *p_elem++;
					SET_IMPORTANCE_PRESENT(p_info);
					CL_TRC (("SCCP::SCLC: importance %d\n",
					           p_info->importance));
				}
				break;
/* #endif */
			/** SPR # 2731 Fix End **/

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			case SCCP_ELEM_ISNI:
				if ((COMPARE_ANSI) || (COMPARE_BCGR))
				{
					p_info->isni.len = GET_2_BYTE_LE(p_elem);
					p_elem += SCCP_ELEM_LEN_LEN;
					sccp_memcpy (p_info->isni.list, p_elem, p_info->isni.len);
					SET_ISNI_PRESENT(p_info);
				}

				break;
#endif

			default:
				/* static check ensures we dont come here */
				break;
		}
	}

	/** SPR # 2760 Fix Start **/
	/** 1. If PC is not present in the clg addr, set PC to own PC as PC is 
	***	   is used later to fill OPC and therefore must not be left blank
	*** 2. This check is required only when Return Option is set 
	***    Ref: GR-246-CORE T1.112.4 - 2.1 (last para);
	***         ITU-T Q.714 - 2.1 (last para)
	***
	*** NOTE:: 1. The checks for ITU/ETSI may be more elaborate and are 
	*** 		  yet to be implemented - Ref: ITU-T Q.714 - 2.3.2, 2.7
	**/

	/* dynamic check */

	/* if PC is not present, set the PC  to local PC */
	if ( !(p_info->cg_addr.pc_ind) )
	{
		p_info->cg_addr.pc = sccp_local_sp.pc;
		p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cg_addr.pc);
	}
	
	if (p_info->proto_class & RET_OPTN_MASK)
	{

		if (p_info->cg_addr.rout_ind == ROUTE_ON_GT)
		{
/* SPR 12291 starts */

#if defined GTT_CALLING_CHANGES

#else
			/** Route on GT **/
	
			if ( !(p_info->cg_addr.gti) )
			{
				SC_A_TRC (("SCCP::SCLC: calling addr does not contain GT but RI "
		           		" is set to Route-on-GT \n"));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
				return SS7_FAILURE;
			}
	
			/** Translate the CG addr and verify that it is local 
			**/
			gtt_ip.ssn_ind = p_info->cg_addr.ssn_ind;
			if (p_info->cg_addr.ssn_ind)
				gtt_ip.ssn = p_info->cg_addr.ssn;
			else
				gtt_ip.ssn = 0;

			gtt_ip.gti = p_info->cg_addr.gti;
			if (p_info->cg_addr.gti)
			{
				gtt_ip.gt_len = p_info->cg_addr.gt_len;
				sccp_memcpy (&gtt_ip.gt[0], &(p_info->cg_addr.gt[0]), gtt_ip.gt_len);
			}

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			if (IS_ISNI_PRESENT(p_info))
			{
				/* ISNI must be used only while translation of CD addr;
				** GTT will now use neither constrained nor suggested
				** ISNI routing but shall directly translate the CG addr
				*/
				gtt_ip.isni.len = 0;
			}
#endif

			translation_result = sccp_global_title_translate (&gtt_ip, &gtt_op);
			if (translation_result == SS7_TRUE)
			{
				p_info->cg_addr.pc = gtt_op.pc;
				p_info->cg_addr.ssn = gtt_op.ssn;
	
				if (gtt_op.rout_ind  != ROUTE_ON_SSN)
				{
                	SC_A_TRC (("SCCP::SCLC: calling addr GT of a non-local SSN\n"));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
				}

				if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id,
                                                        gtt_op.pc)))
            	{
                	SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not known"
                        	" to sccp\n",
                        	gtt_op.pc, p_info->nw_id));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
            	}
            	else if ( ! p_info->p_sp->local)
            	{
                	SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not a local"
                        	" pointcode\n",
                        	gtt_op.pc, p_info->nw_id));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
            	}

				if (!gtt_op.ssn_ind)
				{
                	SC_A_TRC (("SCCP::SCLC: calling addr GT translation did not"
                        	" return a valid SSN\n"));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
				}

				if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss (p_info->p_sp,
	                                             		gtt_op.ssn)))
				{
                	SC_A_TRC (("SCCP::SCLC: calling addr GT translation did not"
                        	" return a valid SSN\n"));
					*p_ecode = ESS7_INVALID_API_ELEMENT;
					return SS7_FAILURE;
				}
		
				/** SPR # 2693 Fix Start **/
				if (! p_info->p_ss->registered)
				{
					SC_A_TRC (("SCCP::SCLC: calling addr SSN %d pc %d nw %d "
	           			" is unequipped\n",
	           			gtt_op.ssn, gtt_op.pc, p_info->nw_id));
						*p_ecode = ESS7_INVALID_API_ELEMENT;
						return SS7_FAILURE;
				}
				/** SPR # 2693 Fix End **/
	
			}
		 	else
			{
				SC_A_TRC (("SCCP::SCLC: calling addr GT translation failed\n"));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
                		/* SPR# 4543 Start  */
               	 /* Increment the Traffic(GTT Translation Failure) statistics */
               			 SC_STAT_TRAFFIC_INR_GTT_TR_FAIL();
                		/* SPR# 4543 End */

				return SS7_FAILURE;
			}
#endif
/* SPR 12291 ends */
		}
		else
		{
			/** Route on SSN **/
	
			if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id,
	                                            		p_info->cg_addr.pc)))
			{
				SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not known"
		           		" to sccp\n",
		           		p_info->cg_addr.pc, p_info->nw_id));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
				return SS7_FAILURE;
			}
			else if ( ! p_info->p_sp->local)
			{
				SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not a local"
		           		" pointcode\n",
		           		p_info->cg_addr.pc, p_info->nw_id));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
				return SS7_FAILURE;
			}
	
			if (p_info->cg_addr.ssn_ind) 
			{
				if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss (p_info->p_sp,
	                                             		p_info->cg_addr.ssn)))
				{
					SC_A_TRC (("SCCP::SCLC: calling addr SSN %d pc %d nw %d "
		           			" not know to sccp\n",
		           			p_info->cg_addr.ssn, p_info->cg_addr.pc, p_info->nw_id));
					*p_ecode = ESS7_INVALID_API_ELEMENT;
					return SS7_FAILURE;
				}
		
				/** SPR # 2693 Fix Start **/
				if ((p_info->cg_addr.ssn_ind) && (! p_info->p_ss->registered))
				{
					SC_A_TRC (("SCCP::SCLC: calling addr SSN %d pc %d nw %d "
	           			" is unequipped\n",
	           			p_info->cg_addr.ssn, p_info->cg_addr.pc, p_info->nw_id));
						*p_ecode = ESS7_INVALID_API_ELEMENT;
						return SS7_FAILURE;
				}
				/** SPR # 2693 Fix End **/
			}
			else
			{
				SC_A_TRC (("SCCP::SCLC: SSN is required n the calling addr as "
							"RI is set to Route-on-SSN \n"));
					*p_ecode = ESS7_INVALID_API_ELEMENT;
					return SS7_FAILURE;
			}
		}
	}
	else
	{
		/*** SPR 8603 Fix starts **/
		if (p_info->cg_addr.rout_ind == ROUTE_ON_GT)
		{
/* SPR 12291 starts */
#if defined GTT_CALLING_CHANGES

#else
			/** Route on GT **/
	
			if ( !(p_info->cg_addr.gti) )
			{
				SC_A_TRC (("SCCP::SCLC: calling addr does not contain GT but RI "
		           		" is set to Route-on-GT \n"));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
				return SS7_FAILURE;
			}
	
			/** Translate the CG addr and verify that it is local 
			**/
			gtt_ip.ssn_ind = p_info->cg_addr.ssn_ind;
			if (p_info->cg_addr.ssn_ind)
				gtt_ip.ssn = p_info->cg_addr.ssn;
			else
				gtt_ip.ssn = 0;

			gtt_ip.gti = p_info->cg_addr.gti;
			if (p_info->cg_addr.gti)
			{
				gtt_ip.gt_len = p_info->cg_addr.gt_len;
				sccp_memcpy (&gtt_ip.gt[0], &(p_info->cg_addr.gt[0]), gtt_ip.gt_len);
			}

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
			if (IS_ISNI_PRESENT(p_info))
			{
				/* ISNI must be used only while translation of CD addr;
				** GTT will now use neither constrained nor suggested
				** ISNI routing but shall directly translate the CG addr
				*/
				gtt_ip.isni.len = 0;
			}
#endif

			translation_result = sccp_global_title_translate (&gtt_ip, &gtt_op);
			if (translation_result == SS7_TRUE)
			{
	
				if (gtt_op.rout_ind  != ROUTE_ON_SSN)
				{
                	SC_A_TRC (("SCCP::SCLC: calling addr GT of a non-local SSN\n"));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
				}

				if (SS7_NULL == (p_sp = sccp_db_find_sp(p_info->nw_id,
                                                        gtt_op.pc)))
            	{
                	SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not known"
                        	" to sccp\n",
                        	gtt_op.pc, p_info->nw_id));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
            	}
            	else if ( ! p_sp->local)
            	{
                	SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not a local"
                        	" pointcode\n",
                        	gtt_op.pc, p_info->nw_id));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
            	}

				if (!gtt_op.ssn_ind)
				{
                	SC_A_TRC (("SCCP::SCLC: calling addr GT translation did not"
                        	" return a valid SSN\n"));
                	*p_ecode = ESS7_INVALID_API_ELEMENT;
                	return SS7_FAILURE;
				}

				if (SS7_NULL == (p_ss = sccp_db_find_ss (p_sp,
	                                             		gtt_op.ssn)))
				{
                	SC_A_TRC (("SCCP::SCLC: calling addr GT translation did not"
                        	" return a valid SSN\n"));
					*p_ecode = ESS7_INVALID_API_ELEMENT;
					return SS7_FAILURE;
				}
		
				/** SPR # 2693 Fix Start **/
				if (! p_ss->registered)
				{
					SC_A_TRC (("SCCP::SCLC: calling addr SSN %d pc %d nw %d "
	           			" is unequipped\n",
	           			gtt_op.ssn, gtt_op.pc, p_info->nw_id));
						*p_ecode = ESS7_INVALID_API_ELEMENT;
						return SS7_FAILURE;
				}
				/** SPR # 2693 Fix End **/
	
			}
		 	else
			{
				SC_A_TRC (("SCCP::SCLC: calling addr GT translation failed\n"));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
                		/* SPR# 4543 Start  */
               	 /* Increment the Traffic(GTT Translation Failure) statistics */
               			 SC_STAT_TRAFFIC_INR_GTT_TR_FAIL();
                		/* SPR# 4543 End */

				return SS7_FAILURE;
			}
#endif
/* SPR 12291 ends */
		}
		else
		{
			/** Route on SSN **/
	
			if (SS7_NULL == (p_sp = sccp_db_find_sp(p_info->nw_id,
	                                            		p_info->cg_addr.pc)))
			{
				SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not known"
		           		" to sccp\n",
		           		p_info->cg_addr.pc, p_info->nw_id));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
				return SS7_FAILURE;
			}
			else if ( ! p_sp->local)
			{
				SC_A_TRC (("SCCP::SCLC: calling addr pc %d nw %d not a local"
		           		" pointcode\n",
		           		p_info->cg_addr.pc, p_info->nw_id));
				*p_ecode = ESS7_INVALID_API_ELEMENT;
				return SS7_FAILURE;
			}
	
			if (p_info->cg_addr.ssn_ind) 
			{
				if (SS7_NULL == (p_ss = sccp_db_find_ss (p_sp,
	                                             		p_info->cg_addr.ssn)))
				{
					SC_A_TRC (("SCCP::SCLC: calling addr SSN %d pc %d nw %d "
		           			" not know to sccp\n",
		           			p_info->cg_addr.ssn, p_info->cg_addr.pc, p_info->nw_id));
					*p_ecode = ESS7_INVALID_API_ELEMENT;
					return SS7_FAILURE;
				}
		
				/** SPR # 2693 Fix Start **/
				if ((p_info->cg_addr.ssn_ind) && (! p_ss->registered))
				{
					SC_A_TRC (("SCCP::SCLC: calling addr SSN %d pc %d nw %d "
	           			" is unequipped\n",
	           			p_info->cg_addr.ssn, p_info->cg_addr.pc, p_info->nw_id));
						*p_ecode = ESS7_INVALID_API_ELEMENT;
						return SS7_FAILURE;
				}
				/** SPR # 2693 Fix End **/
			}
			else
			{
				SC_A_TRC (("SCCP::SCLC: SSN is required n the calling addr as "
							"RI is set to Route-on-SSN \n"));
					*p_ecode = ESS7_INVALID_API_ELEMENT;
					return SS7_FAILURE;
			}
		}
		/*** SPR 8603 Fix ends **/
/* SPR # 9442 Fix Start */
#if 0
		p_info->cg_addr.pc = sccp_local_sp.pc;
#endif
/* SPR # 9442 Fix End */
		p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->cg_addr.pc);
	}
	
	/** SPR # 2760 Fix End **/

	return SS7_SUCCESS;
}
