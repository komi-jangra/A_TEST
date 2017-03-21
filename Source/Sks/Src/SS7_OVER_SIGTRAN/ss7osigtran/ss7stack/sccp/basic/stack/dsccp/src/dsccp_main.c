/***************************************************************************
**
**  FILE NAME:
**      dsccp_main.c
**
****************************************************************************
**
**  FUNCTION:
**		Contains functions related to DSCCP  processing function dsccp_process_mesg(). This function is called from sccp_process_mesg when an API from mate is received
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24August 2001  Pawanish Modi            Original
**  24October2001  Prateek Bidwalkar        Fixed SPR 6750 
**  26December2001 Prateek Bidwalkar        Fixed SPR 7450 
**  06March2002   Sachin bhatia            Dereg Functionality
**  Copyright 2001, Hughes Software Systems
**
***************************************************************************/

/* SPR # 6750 Fix Start */
#include "sc_stgl.h"
/* SPR # 6750 Fix End */

#ifdef DISTRIBUTED_SCCP


#include "dsccp.h"

/* SPR # 6750 Fix Start */
#if 0
#include "sc_stgl.h"
#endif
/* SPR # 6750 Fix End */

#include "dsccp_proc.h"
#ifdef DSCCP_STATS_ENABLED
#include "dsccp_stats.h"
#endif


/***************************************************************************
**
**      FUNCTION :
**      dsccp_process_mesg  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the sccp_process_mesg when a 
**      message from mate is received. The category and command are extracted
**      from the API  which are then handled appropriately
**
**      NOTE :
**
***************************************************************************/


return_t 
dsccp_process_mesg
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t *p_ecode)
#else
	(p_api,p_ecode)
	U8bit *p_api;
	error_t *p_ecode
#endif
{
	U8bit command;
	U8bit category;
	dsccp_instance_id_t instance_id;
	return_t ret_val;



	category = p_api[DSCCP_CAT_OFFSET];
	command = p_api[DSCCP_CMD_OFFSET];

	
	switch(category)
	{
		case DSCCP_API_CAT_CONFIG:
#ifdef DSCCP_STATS_ENABLED
			/* Incriment the stats for incoming mate api */
			DSC_STAT_API_INR_IN_API_MATE();
#endif
			switch(command)
			{
			case DSCCP_API_CMD_CONFIG_REQ:
				instance_id = p_api[DSCCP_DATA_OFFSET];

				ret_val = dsccp_handle_conf_request_msg(instance_id,p_ecode);
				return ret_val;

			case DSCCP_API_CMD_CONFIG_SP_INFO:
				dsccp_handle_config_sp_info(p_api,p_ecode);

				break;

			case DSCCP_API_CMD_CONFIG_SS_INFO:

				dsccp_handle_config_ss_info(p_api,p_ecode);
				break;

			case DSCCP_API_CMD_CONFIG_REG_INFO:
				dsccp_handle_config_reg_info(p_api,p_ecode);
				break;

			case DSCCP_API_CMD_CONFIG_END:
				ret_val = dsccp_handle_config_end(p_api,p_ecode);

				if(ret_val == SS7_FAILURE)
					return SS7_FAILURE;
				break;

			case DSCCP_API_CMD_COMP_MATE_STATUS_INFO:
				ret_val = dsccp_handle_comp_mate_status_info(p_api, p_ecode);
				break;
/* SPR # 7450 Fix Start */
			case DSCCP_API_CMD_DEACTIVATED_MATE_STATUS:
				ret_val = dsccp_handle_deactivated_mate_status(p_api, p_ecode);
				break;
/* SPR # 7450 Fix End */
			default:
#ifdef DSCCP_STATS_ENABLED

				DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif

				*p_ecode =  ESCCP_INVALID_MATE_COMMAND; 
				return SS7_FAILURE;
			}
			return ret_val;
			break;

		case DSCCP_API_CAT_SCMG:
#ifdef DSCCP_STATS_ENABLED
			/* Incriment the stats for incoming mate api */
			DSC_STAT_API_INR_IN_API_MATE();
#endif
			switch(command)
			{
				case	DSCCP_API_CMD_SCMG_SP_STATUS:
					dsccp_scmg_handle_sp_status(p_api);
					break;

				case	DSCCP_API_CMD_SCMG_SS_STATUS:
					dsccp_scmg_handle_ss_status(p_api);
					break;

				case	DSCCP_API_CMD_SCMG_REG_STATUS:
					dsccp_scmg_handle_reg_status(p_api);
					break;
				case	DSCCP_API_CMD_SCMG_DEREG_STATUS:
					dsccp_scmg_handle_dereg_status(p_api);
					break;
				case DSCCP_API_CMD_SCMG_SCCP_STATUS:
					dsccp_scmg_handle_scmg_status(p_api);
					break;	

				default: 
#ifdef DSCCP_STATS_ENABLED
					DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
					*p_ecode =  ESCCP_INVALID_MATE_COMMAND; 
					return SS7_FAILURE;
			}	
			break;
				
		case DSCCP_API_CAT_SCOC:
#ifdef DSCCP_STATS_ENABLED
			/* Incriment the stats for incoming mate api */
			DSC_STAT_API_INR_IN_API_MATE();
#endif
			switch(command)
			{

				case DSCCP_API_CMD_SCOC_DISC_REQ:
					ret_val = dsccp_handle_mate_n_disc_req(p_api, p_ecode);
					if(ret_val == SS7_FAILURE)
						return SS7_FAILURE;
					break;
				default:
#ifdef DSCCP_STATS_ENABLED
					DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
					*p_ecode =  ESCCP_INVALID_MATE_COMMAND; 
					return SS7_FAILURE;
			}
			break;

		case DSCCP_API_CAT_SCLC:
#ifdef DSCCP_STATS_ENABLED
				/* Incriment the stats for incoming mate api */
				DSC_STAT_API_INR_IN_API_MATE();
#endif
				ret_val = dsccp_process_sclc_cat_msg(p_api);
				return ret_val;
			break;

		case DSCCP_API_CAT_HM:
			switch(command)
			{

				case DSCCP_API_CMD_MATE_STATUS_CHANGE:
					dsccp_handle_mate_status_change(p_api);
					break;

				case DSCCP_API_CMD_COMP_MATE_STATUS_INFO:
					ret_val = dsccp_handle_comp_mate_status_info(p_api, p_ecode);
					break;

				default:
#ifdef DSCCP_STATS_ENABLED
					DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
					*p_ecode =  ESCCP_INVALID_MATE_COMMAND; 
					return SS7_FAILURE;
			}
			break;

		default:

#ifdef DSCCP_STATS_ENABLED
			DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
			*p_ecode =  ESCCP_INVALID_MATE_CATEGORY; 
			return SS7_FAILURE;
	}
	return SS7_SUCCESS;
}

#else /* DISTRIBUTED_SCCP */
#if 0

/*****************************************************************************
**  This extern declaration is required as ANSI C does not allow an empty 
**  source file. This declaration enables compilation without DISTRIBURTED_SCCP 
**  flag .
*****************************************************************************/

return_t dsccp_dummy
#ifdef ANSI_PROTO
   (void)
#else
   ()
#endif
{
    return SS7_SUCCESS;
}

#endif
#endif /* end DISTRIBUTED_SCCP */
