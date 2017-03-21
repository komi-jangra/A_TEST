/******************************************************************************
**      FUNCTION:
**         Contains variable declarations for sc_error.c   
**
*******************************************************************************
**
**      FILE NAME:
**          sc_error.c
**      
**      DESCRIPTION:
**         This file contains definitions for the error table and error level. 
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**           
**      24Jul02    Salil Agrawal                          Fixed SPR # 9341
**      07Feb99    Sudipta Nandi                          Added event alarms
**      16Jan98    GAURAV.TANEJA     HSS:20800008         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems, Inc.
**
******************************************************************************/

#include "sc_stgl.h"

static void sccp_err_sm_cmd_resp
	_ARGS_ ((U8bit * p_api, return_t ret_val, U8bit param,
	             Boolean put_param, error_t ecode));

#ifdef SCCP_ERROR_ENABLED

/* error table indexed by error level 
   At each level a bit-flag for each type of error */
U32bit sccp_error_table[MAX_ERROR_LEVELS];
U8bit sccp_event_table;

U8bit object_map [] = { SCCP_SM_OBJECT_SP_FLAG,
			SCCP_SM_OBJECT_SS_FLAG,
			SCCP_SM_OBJECT_CONN_FLAG,
			SCCP_SM_ALL_OBJ_FLAG};

/*****************************************************************************
**      FUNCTION :
**          calls ss7_err_handler if the error at that level is set
******************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
*****************************************************************************/

void
sccp_err_handler
#ifdef ANSI_PROTO
	(error_t error, U32bit error_type, U8bit error_level)
#else
	(error, error_type, error_level)
	 error_t error;
	 U32bit error_type;
	 U8bit 	error_level;
#endif
{
	sccp_ret_val = SS7_FAILURE;

	if (sccp_error_table[error_level] & error_type)
	{
		if (SS7_FAILURE == ss7_err_handler(error, SCCP_MODULE_ID, SS7_NULL))
		{
			SCCP_STACK_TRACE (SC_ALL_TRACE, BRIEF_TRACE,
			        ("SCCP::ERRP:Failure in calling err handler !!!\n"));
		}
	}
}


/*****************************************************************************
**      FUNCTION :
**          sends event alarms to sm
******************************************************************************
**
**      DESCRIPTION :
**	    prepares the sm response api buffer to send an event alarm to the 
**          sm, and calls send_from_sccp to send it 
**
**      NOTE :
**
*****************************************************************************/


void 
sccp_report_event_to_sm 
#ifdef ANSI_PROTO
	(U16bit 	object_id, 
	 U16bit 	state, 
	 sp_entry_t     * p_sp,
	 ss_entry_t	* p_ss,
	 conn_entry_t	* p_conn)
#else
	(object_id, state, p_info)
	 U16bit 	object_id;
	 U16bit 	state; 
	 sp_entry_t     * p_sp;
	 ss_entry_t	* p_ss;
	 conn_entry_t	* p_conn;
#endif
{
	/* SPR 9302 - Fix Start */
	/*U16bit mem_size, var_info_len;*/
	U16bit mem_size, var_info_len=0;
	/* SPR 9302 - Fix End   */
	U8bit *p_buf, *p_elem, nelem;
	U8bit object_flag;
	error_t ecode;
#ifdef SCCP_TRACE_ENABLED
        S8bit * p_trstr =(S8bit *) "event reporting to SM";
/* start added during CC compilation */

/* string initialiase by S8bit * */
/* end added during CC compilation */
#endif

	/* check if event reporting is disabled*/

	object_flag = object_map[object_id];
	if (!(sccp_event_table & object_flag))
		return;

        SC_STAT_API_INR_OUT_API_SM () ;

	nelem = SS7_SM_API_MIN_NO_ELEM + 2; 	   /* add object id + state */ 

	mem_size = SS7_SM_API_MIN_LEN + 4;	   /* add object_id len + state len */

	
	switch (object_id) 
	{
		case SCCP_SM_OBJECT_SP: 
        		SC_A_TRC (("SCCP::ERRP: Building %s %s\n", "SP",p_trstr));
/* starts spr # 9341 */			
            if ((sc_opt.standard == STACK_ANSI) ||
				(sc_opt.standard == STACK_BCGR) ||
                (sc_opt.standard == STACK_CHINESE)) 
				var_info_len = SCCP_ELEM_ANSI_AFFECTED_SP_LEN;
			else
				var_info_len = SCCP_ELEM_ITU_ETSI_AFFECTED_SP_LEN;
/* #ifdef SCCP_CHINESE */
	/* var_info_len = SCCP_ELEM_ANSI_AFFECTED_SP_LEN; */
/* #endif */
/* end spr # 9341 */
			nelem++;
			break;

		case SCCP_SM_OBJECT_SS:
        		SC_A_TRC (("SCCP::ERRP: Building %s %s\n", "SS",p_trstr));
/* starts spr # 9341 */
            if ((sc_opt.standard == STACK_ANSI) ||
				(sc_opt.standard == STACK_BCGR) ||
                (sc_opt.standard == STACK_CHINESE)) 
				var_info_len = SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN;
			else
				var_info_len = SCCP_ELEM_ITU_ETSI_AFFECTED_SUBSYSTEM_LEN;
/* #ifdef SCCP_CHINESE */
	/* var_info_len = SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN; */
/* #endif */
/* end spr #9341 */
			nelem++;
			break;

		case SCCP_SM_OBJECT_CONN:
        		SC_A_TRC (("SCCP::ERRP: Building %s %s\n", "CONN",p_trstr));
			var_info_len = SCCP_ELEM_CONNECTION_ID_LEN;
			nelem += 1;
			if (state == CONN_RESET)
			{
				var_info_len += SCCP_ELEM_RESET_CAUSE_LEN + 1;
				nelem += 2;	/* reset cause len+originator len */
			}
			break;
	}

	mem_size += var_info_len;

        if (SS7_NULL != (p_buf = sccp_malloc(mem_size)))
	{
		sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                               nelem, mem_size);

		p_elem = p_buf + SS7_API_HEADER_LEN;

		*p_elem++ = SS7_SM_ERROR;		/* include category */
		*p_elem++ = SS7_SM_SCCP_STATUS;		/* include command */
		*p_elem++ = 0;				/* include transaction id */

		PUT_2_BYTE_LE (p_elem, object_id);	/* include object id */
		p_elem += 2;
		PUT_2_BYTE_LE (p_elem, state);		/* include state */
		p_elem += 2;
		
		/* include variable information */
		switch (object_id)
		{
			case SCCP_SM_OBJECT_SP:
				p_elem = sccp_put_affected_sp_elem (p_elem, p_sp);
				break;	
			case SCCP_SM_OBJECT_SS:
			        p_elem = sccp_put_affected_ss_elem (p_elem, p_ss);
				break;
			case SCCP_SM_OBJECT_CONN:
                             #ifdef SCCP_CONNECTION_ID_CHANGES
                                PUT_4_BYTE_LE (p_elem, p_conn->conn_id);
                             #else
				PUT_2_BYTE_LE (p_elem, p_conn->conn_id);
                             #endif
			  	p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

				if (state == CONN_RESET)
				{
					*p_elem = p_conn->reset_cause;
					p_elem += SCCP_ELEM_RESET_CAUSE_LEN;
					*p_elem = p_conn->originator;
					p_elem++;
				}
		}

        	SC_A_TRC (("SCCP::ERRP: Built %s\n", p_trstr));

		sccp_sendto_sm (p_buf);
		return;
	}
	else
	{
		ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		SC_A_ERR (ecode);
	}
}


/*****************************************************************************
**      FUNCTION :
** 	    Gets the event reporting level associated with the specified
**	    object id        
******************************************************************************
**
**      DESCRIPTION :
**          Gets the event reporting level (set or clear)  of the object from 
**          the event table and fills it into p_current_level 
**
**      NOTE :
**
*****************************************************************************/
 

return_t
sccp_get_event_reporting
#ifdef ANSI_PROTO
	(U16bit 	object_id,
	 U8bit 		*p_current_level,
	 error_t 	*p_ecode)
#else
	(object_id, p_current_level, p_ecode)
	U16bit 		object_id;
	U8bit 		*p_current_level;
	error_t 	*p_ecode;
#endif
{
	U8bit object_flag;

	object_flag = object_map [object_id];

	/* check validity of object id */
	if (SCCP_INVALID_OBJECT_FLAG(object_flag)) {
		*p_ecode = ESCCP_INVALID_OBJECT_ID_FLAG;
		return SS7_FAILURE;
	}
	
	if (object_flag == (sccp_event_table & object_flag))
	    	*p_current_level = SCCP_EVENT_RPT;	/* set */
	else
	    	*p_current_level = SCCP_NO_EVENT_RPT;	/* not set */
	
	return SS7_SUCCESS;
}


/*****************************************************************************
**      FUNCTION :
**          Sets or clears the event reporting level associated with the 
**          specified object id. 
******************************************************************************
**
**      DESCRIPTION :
**          Sets or clears the event reporting level of the object in the event
**          table as specified by the parameter 'set_level'
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_set_event_reporting
#ifdef ANSI_PROTO
	(U16bit 	object_id,
	 U8bit 		set_level,
	 error_t 	*p_ecode)
#else
	(object_id, p_current_level, p_ecode)
	U16bit 		object_id;
	U8bit 		set_level;
	error_t 	*p_ecode;
#endif
{
	U8bit object_flag;

	object_flag = object_map [object_id];

	/* check validity of object id */
	if (SCCP_INVALID_OBJECT_FLAG(object_flag)) {
		*p_ecode = ESCCP_INVALID_OBJECT_ID_FLAG;
		return SS7_FAILURE;
	}
	
	/* disable event reporting for object */
	sccp_event_table &= ~object_flag;		
	
	/* set event reporting for the object */
	
	if (set_level == SCCP_EVENT_RPT)
		sccp_event_table |= object_flag;
	
	return SS7_SUCCESS;
}


/*****************************************************************************
**      FUNCTION :
**          handle SM command of category ERROR
******************************************************************************
**
**      DESCRIPTION :
**         calls appropriate function depending on error command
**
**      NOTE :
**
*****************************************************************************/

void
sccp_err_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	U8bit cmd;
	return_t ret_val;
	error_t ecode;
	U32bit err_flag;
	U16bit object_id;
	U8bit err_level, event_level;
	U8bit param = 0;
	Boolean put_param = SS7_FALSE;

	cmd = GET_SM_CMD(p_api);

	SC_A_TRC (("SCCP::ERRP:SM category ERROR\n"));

	switch (cmd)
	{
		case SS7_SM_GET_ERR_LEVEL:
			SC_A_TRC (("SCCP::ERRP:get err level cmd\n"));
			err_flag = GET_SM_ERR_FLAG(p_api);
			ret_val = sctc_get_error_level(SCCP_MODULE_ID,
			                               err_flag, &err_level,
			                               &ecode);
                        if ( ret_val == SS7_SUCCESS )
                         {
			param = err_level; put_param = SS7_TRUE;
                         } 
			break;

		case SS7_SM_SET_ERR_LEVEL:
			SC_A_TRC (("SCCP::ERRP:set err level cmd\n"));
			err_flag = GET_SM_ERR_FLAG(p_api);
			err_level = GET_SM_ERR_LEVEL(p_api);
			ret_val = sctc_set_error_level(SCCP_MODULE_ID,
			                               err_flag, err_level,
			                               &ecode);
			break ;

		case SS7_SM_GET_EVENT_REPORTING:
			SC_A_TRC (("SCCP::ERRP:get event reporting level cmd\n"));
			object_id = GET_SCCP_SM_OBJECT_ID(p_api);	
			ret_val = sccp_get_event_reporting(object_id, &event_level, 
							   &ecode);
                        if ( ret_val == SS7_SUCCESS )
                        {
			param = event_level; put_param = SS7_TRUE;
                        }
			break;
			
		case SS7_SM_SET_EVENT_REPORTING:
			SC_A_TRC (("SCCP::ERRP:get event reporting level cmd\n"));
			object_id = GET_SCCP_SM_OBJECT_ID(p_api);	
			event_level = GET_SCCP_SM_OBJECT_LEVEL(p_api);
			ret_val = sccp_set_event_reporting(object_id, event_level, 
							   &ecode);
			break;

		default:
			SC_A_TRC (("SCCP::ERRP:Invalid ERROR cmd %d\n", cmd));
			ret_val = SS7_FAILURE;
			ecode = ESS7_INVALID_API_ELEMENT;
			break;
	}

	if (SS7_FAILURE == ret_val)
		SC_A_ERR (ecode);

	sccp_err_sm_cmd_resp (p_api, ret_val, param, put_param, ecode);
}

#else
/*****************************************************************************
**      FUNCTION :
**          in case ERROR is disabled handles SM command
******************************************************************************
**
**      DESCRIPTION :
**         sends an error response
**
**      NOTE :
**
*****************************************************************************/

void
sccp_err_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit *p_api;
#endif
{
	U8bit param = 0;
	Boolean put_param = SS7_FALSE;

	sccp_err_sm_cmd_resp (p_api, SS7_FAILURE, param, put_param,
	                      ESS7_ERRORS_DISABLED);
}

#endif /* #ifdef SCCP_ERROR_ENABLED */

/*****************************************************************************
**      FUNCTION :
**          sends a response to sm command category ERROR
******************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
*****************************************************************************/

void
sccp_err_sm_cmd_resp
#ifdef ANSI_PROTO
	(U8bit 		*p_api,
	 return_t 	ret_val,
	 U8bit 		param,
	 Boolean 	put_param,
	 error_t 	ecode)
#else
	(p_api, ret_val, param, put_param, ecode)
	 U8bit 		*p_api;
	 return_t 	ret_val;
	 U8bit 		param;
	 Boolean 	put_param;
	 error_t 	ecode;
#endif
{
	sccp_sm_cmd_std_resp (p_api, ret_val, param, put_param, ecode);
}


