/***************************************************************************
**
**  FILE NAME:
**      sc_routf.c
**
****************************************************************************
**
**  FUNCTION:
**      Handles failure of SCCP routing
**
**  DESCRIPTION:
**      Contains functions to create an appropriate service message
**      and calls routing function to route it
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  13May2004 Suyash/Ganesh                  Fixed SPR # 13444 
**  12Oct2000 Ramu kandula            Modified for broadband
**  15Mar2000 Ramu Kandula            Fixed SPR # 2731
**  19May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

static void sccp_return_service_msg
	_ARGS_ ((msg_info_t * p_info));

/***************************************************************************
**
**      FUNCTION :
**         corresponds to  Q.714/C.12/sheet-8 on the event
**          Routing failure [ SCRC -> SCLC ]
****************************************************************************
**
**      DESCRIPTION :
**         ignores a service message. else if return option is set
**         initiates message return
**
**      NOTE :
**
***************************************************************************/

void
sccp_handle_routing_failure
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info;
#endif
{
	CL_TRC (("SCCP::SCLC: handling routing failure\n"));

	switch (p_info->msg_type)
	{
		case UDTS_MSG_TYPE:
		case XUDTS_MSG_TYPE:
#ifdef SCCP_BROADBAND
		case LUDTS_MSG_TYPE:
#endif
			CL_TRC (("SCCP:SCLC: service msg. ignore\n"));
			return;

		case UDT_MSG_TYPE:
			if (! (p_info->proto_class & RET_OPTN_MASK))
			{
				CL_TRC (("SCCP::SCLC: return option not set in UDT\n"));
				return;
			}

			CL_TRC (("SCCP::SCLC: return option set in UDT\n"));

			if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
			{
				sccp_build_n_notice_ind_api (p_info);
			}
			else
			{
				sccp_return_service_msg (p_info);
			}
			break;


		case XUDT_MSG_TYPE:
			if (! (p_info->proto_class & RET_OPTN_MASK))
			{
				CL_TRC (("SCCP::SCLC: return option not set in XUDT\n"));
				return;
			}

			CL_TRC (("SCCP::SCLC: return option set in XUDT\n"));

			if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
			{
				sccp_build_n_notice_ind_api (p_info);
			}
			else
			{
				sccp_return_service_msg (p_info);
			}
			break;

#ifdef SCCP_BROADBAND
		case LUDT_MSG_TYPE:
			if (! (p_info->proto_class & RET_OPTN_MASK))
			{
				CL_TRC (("SCCP::SCLC: return option not set in LUDT\n"));
				return;
			}

			CL_TRC (("SCCP::SCLC: return option set in LUDT\n"));

			if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
			{
				sccp_build_n_notice_ind_api (p_info);
			}
			else
			{
				sccp_return_service_msg (p_info);
			}
			break;
#endif

		default:
			break;
	}
}

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-9 node 11
****************************************************************************
**
**      DESCRIPTION :
**         initiates message return
**
**      NOTE :
**
***************************************************************************/

void
sccp_return_service_msg
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	 msg_info_t * p_info;
#endif
{
	msg_info_t info;
	pc_t remote_pc;

	info.flag = 0x00;
	info.nw_id = p_info->nw_id;
	info.p_api = p_info->p_api;

	info.opc = p_info->opc;
	info.dpc = p_info->dpc;

	info.sls = p_info->sls;

	/** SPR # 2731 Start Fix **/
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
	if ((COMPARE_ANSI) || (COMPARE_BCGR))
	{
		/** Copy the importance parameter **/
		info.importance = p_info->importance;
		SET_IMPORTANCE_PRESENT(&info);
	}
#endif
	/** SPR # 2731 End Fix **/

	/* swap addresses */

	sccp_copy_sccp_addr (&p_info->cg_addr, &info.cd_addr);
	sccp_copy_sccp_addr (&p_info->cd_addr, &info.cg_addr);

	if (info.cd_addr.pc_ind) remote_pc = info.cd_addr.pc;
	else remote_pc = info.dpc;

	if (SS7_NULL == (info.p_sp = sccp_db_find_sp (info.nw_id,remote_pc)))
	{
		CL_TRC (("SCCP::SCLC: Unknown remote pc %u\n", remote_pc));
		return;
	}

	info.p_ss = SS7_NULL;
	info.ret_cause = p_info->ret_cause;
	info.data.p = p_info->data.p;
	info.data.len = p_info->data.len;

	/* SPR 9404 - Fix Start */
	/*info.sls = sccp_assign_sls (&info.cd_addr, &info.cg_addr,
	                            info.sls, info.proto_class & 0xf);*/
	/* SPR 13444 - fix Start */ 
	/* info.sls = sccp_assign_sls (&info.cd_addr, &info.cg_addr,
	                            info.sls, (U8bit)(info.proto_class & 0xf));*/
    /*    info.sls = sccp_assign_sls (&info.cg_addr, &info.cd_addr,
                                    info.sls, (U8bit)(info.proto_class & 0xf));*/
	/* SPR 13444 - fix Stop */ 
	/* SPR 9404 - Fix End   */
	CL_TRC (("SCCP::SCLC: assigned SLS %d\n", info.sls));

	switch (p_info->msg_type)
	{
		case UDT_MSG_TYPE:
			info.msg_type = UDTS_MSG_TYPE;
			break;

		case XUDT_MSG_TYPE:
			info.hop_counter = INITIAL_HOP_COUNTER_VALUE;
			info.msg_type = XUDTS_MSG_TYPE;
			break;

#ifdef SCCP_BROADBAND
		case LUDT_MSG_TYPE:
			info.hop_counter = INITIAL_HOP_COUNTER_VALUE;
			info.msg_type = LUDTS_MSG_TYPE;
			break;
#endif

		default:
			break;
	}

	sccp_route_cl_msg (&info);
}
