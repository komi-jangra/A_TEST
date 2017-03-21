/******************************************************************************
**      FUNCTION:
**         Contains variable declarations for sc_debug.c
**
*******************************************************************************
**
**      FILE NAME:
**          sc_debug.c
**
**      DESCRIPTION:
**         This file contains definitions for the trace table and trace level.
**
**       DATE          NAME           REFERENCE            REASON
**       ----          ----           ---------            ------
**
**      24Jan03    Ashish Sawalkar   					  SPR 11120 Fix
**      05Jun98    S. Kini                                SM api included
**      20Jan98    GAURAV.TANEJA     HSS:20800008         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems, Inc.
**
******************************************************************************/


#include "sc_shgl.h"
#include "sc_errh.h"

static void sccp_dbg_sm_cmd_resp
	_ARGS_ ((U8bit * p_api, return_t ret_val, U8bit param,
	         Boolean put_param, error_t ecode));

#ifdef SCCP_TRACE_ENABLED 

/* This array is indexed by trace level
   Each element of the array is a bitmap indicating if the
   particular trace flag is set at that level */
U32bit sccp_trace_table[MAX_TRACE_LEVELS];

/*****************************************************************************
**
**      FUNCTION :
**              Dump the API. 
**
******************************************************************************
**
**      DESCRIPTION :
**              This function dumps all the fields of the api header and
**              dumps in hex all the data bytes
**
******************************************************************************/
void 
sccp_api_detail_trace
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
#define API_DUMP_LINE_SIZE  20
	U16bit i, num_lines, data_buf_len, dump_line_bytes;
	U8bit * p_data_buf;

	SCCP_HEX_DUMP (API_TRACE, DETAILED_TRACE,p_api,GET_API_LEN(p_api));
#if 0
	/* Check if detail trace for API TRACE is set */
/*	if ( ! (sccp_trace_table[DETAILED_TRACE] & SCTC_API_TRACE))
		return;*/

	SC_TRC (("SCCP::DBG:api_id = %d, version = %d, num_elem = %d, len = %d\n",
	         GET_API_ID(p_api), GET_API_VER(p_api), GET_API_NELEM(p_api),
	         GET_API_LEN(p_api)));

	data_buf_len = GET_API_LEN(p_api) - API_HEADER_LEN;

	(data_buf_len % API_DUMP_LINE_SIZE) ?
	(num_lines = (data_buf_len / API_DUMP_LINE_SIZE) + 1) :
	(num_lines = (data_buf_len / API_DUMP_LINE_SIZE));

	for (i=num_lines, p_data_buf = p_api + API_HEADER_LEN;
	     i > 0; i--)
	{
		dump_line_bytes = (U16bit)
		((p_data_buf + API_DUMP_LINE_SIZE) > (p_api + GET_API_LEN(p_api)) ?
		 (p_api + GET_API_LEN(p_api) - p_data_buf) : API_DUMP_LINE_SIZE);
		SCCP_HEX_DUMP (API_TRACE, DETAILED_TRACE,
		              p_data_buf, dump_line_bytes);
		SC_TRC(("\n"));
		p_data_buf += dump_line_bytes;
	}
#endif  /* Commented by Amaresh as on dated 16-09-14 */
 
}

/*****************************************************************************
**
**      FUNCTION :
**           Debug category command handler.	
**
******************************************************************************
**
**      DESCRIPTION :
**			Default handler for debug category commands for the
**			case when traces are included at compile time.
**
******************************************************************************/
void
sccp_dbg_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
	U8bit cmd, trc_level;
	return_t ret_val;
	U32bit trc_flag;
	error_t ecode = 0;
	U8bit param = 0; 
	Boolean put_param = SS7_FALSE;
	sccp_gtt_trace_level_info_t gtt_trace_info;

	cmd = GET_SM_CMD(p_api);
	trc_flag = GET_SM_TRC_FLAG(p_api);

	SC_A_TRC (("SCCP::DBG:SM category DEBUG\n"));

	switch (cmd)
	{
		case SS7_SM_GET_TRACE_LEVEL:
			SC_A_TRC (("SCCP::DBG:get trace cmd\n"));

			/* spr 11120 fix : checking and handling GTT get trace level cmd */
			if (!(trc_flag & SCRC_GTT_TRACE))
			{
				ret_val = sctc_get_trace_level(SCCP_MODULE_ID, trc_flag,
			                     &trc_level, &ecode);
                        if (ret_val == SS7_SUCCESS)
                         {  
		        	param = trc_level; 
		        	put_param = SS7_TRUE;
                         }
			}
			else
			{
				gtt_trace_info.info_cat	= SS7_SM_DEBUG;
				gtt_trace_info.info_id	= SS7_SM_GET_TRACE_LEVEL;
				gtt_trace_info.sccp_gtt_trace_flag = trc_flag ;
				gtt_trace_info.sccp_gtt_trace_level = SS7_NULL;
				
				ret_val = sccp_update_gtt_dbg_info(&gtt_trace_info);
				if (ret_val == SS7_SUCCESS)
				{
					param = gtt_trace_info.sccp_gtt_trace_level;
					put_param = SS7_TRUE;
				}			
				else
					ecode = (error_t)(gtt_trace_info.ecode);
			}
			break;

		case SS7_SM_SET_TRACE_LEVEL:
			SC_A_TRC (("SCCP::DBG:set trace cmd\n"));
			trc_level = GET_SM_TRC_LEVEL(p_api);
			/* spr 11120 fix : checking and handling GTT get trace level cmd */

			if (!(trc_flag & SCRC_GTT_TRACE))
			{
				ret_val = sctc_set_trace_level(SCCP_MODULE_ID, trc_flag,
			                               trc_level, &ecode);
                        if (ret_val == SS7_SUCCESS)
                         {  
                            param =  trc_level;
                            put_param = SS7_TRUE;
                         }
			}
			else
			{
				ss7_mem_zero((void *) (&gtt_trace_info), sizeof(sccp_gtt_trace_level_info_t));
				gtt_trace_info.info_cat	= SS7_SM_DEBUG;
				gtt_trace_info.info_id	= SS7_SM_SET_TRACE_LEVEL;
				gtt_trace_info.sccp_gtt_trace_level = trc_level;
				gtt_trace_info.sccp_gtt_trace_flag = trc_flag ;

				ret_val = sccp_update_gtt_dbg_info(&gtt_trace_info);

				if (ret_val == SS7_SUCCESS)
				{
					param = trc_level;
					put_param = SS7_TRUE;
				}			
				else
					ecode = (error_t)(gtt_trace_info.ecode);
			}
			break;

		default:
			SC_A_TRC (("SCCP::DBG:invalid command %d\n", cmd));
			ecode = ESS7_INVALID_API_ELEMENT;
			ret_val = SS7_FAILURE;
			break;
	}

	if (SS7_FAILURE == ret_val)
		SC_A_ERR (ecode);

	sccp_dbg_sm_cmd_resp (p_api, ret_val, param, put_param, ecode);
}

#else 

/*****************************************************************************
**
**      FUNCTION :
**           Debug category command handler.	
**
******************************************************************************
**
**      DESCRIPTION :
**			Default handler for debug category commands for the
**			case when traces are disabled at compile time.
**
******************************************************************************/
void
sccp_dbg_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
	U8bit param = 0; 
	Boolean put_param = SS7_FALSE;

	sccp_dbg_sm_cmd_resp (p_api, SS7_FAILURE, param, put_param,
	                      ESS7_TRACES_DISABLED);
}

#endif  

/*****************************************************************************
**
**      FUNCTION :
**           	Prepare the debug command response to SM 
**
******************************************************************************
**
**      DESCRIPTION :
**              calls function to prepare the standard response to the
**              SM command
**
******************************************************************************/
void
sccp_dbg_sm_cmd_resp
#ifdef ANSI_PROTO
	(U8bit 		*p_api,
	 return_t 	ret_val,
	 U8bit 		param,
         Boolean 	put_param,
	 error_t 	ecode)
#else
	(p_api, ret_val, param,	put_param, ecode)
	 U8bit 		*p_api;
	 return_t 	ret_val;
	 U8bit 		param;
         Boolean 	put_param;
	 error_t 	ecode;
#endif
{
	sccp_sm_cmd_std_resp (p_api, ret_val, param, put_param, ecode);
}

