/*****************************************************************************
**
**	FILE	:
**		Parses the APIs from the System management
**
******************************************************************************
**
**	FILE NAME :
**		sc_sys.c
**
**	DESCRIPTION :
**		This file contains all the functions that are required
**              to parse the APIs received from the system management
**		and the functions that receive these APIs
**
**
**	DATE		NAME		REFERENCE	REASON
**	----		----		---------	------
**  20May'00    Ramu Kandula            Changed len_t to 
**                                      s7_len_t
**  15Feb2000   Ramu Kandula            Fixed SPR # 2606
**  7Feb'99     Sudipta Nandi           Added event alarms
**	17Jun'98    Praneet Khare  HSS:	    Original
**
**	Copyright 1998, Hughes Software Systems, Inc.
**
*****************************************************************************/

#include "sc_clgl.h"


#define SCCP_VERSION_NUMBER 1

#ifdef SCCP_INCLUDE_CO_SERVICE
#define SCCP_MAX_TIMER_CONFIG_ID    14
#else
#define SCCP_MAX_TIMER_CONFIG_ID    5 
#endif

/** SPR # 2606 fix START **/

/*****************************************************************************
**
** Data Structure : sccp_sm_client_standard
**
** Description :
** This data structure stores the standard during initialization
**
******************************************************************************/
 
U8bit sccp_sm_client_standard = STACK_ITU ;

/** SPR # 2606 fix Contd. **/
	

static return_t sccp_handle_sccp_sm_request_api
     _ARGS_ ((buffer_t              *p_buffer ,
	          error_t                 *p_error_code));

static return_t handle_sccp_init_timer
        _ARGS_ ((buffer_t               *p_buffer,
                 error_t                *p_error_code));

static return_t handle_sccp_conf_sp
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_conf_ss
	_ARGS_ ((buffer_t		*p_buffer,
 			 error_t		*p_error_code));

static return_t handle_sccp_conf_css
	_ARGS_ ((buffer_t		*p_buffer,
			 error_t		*p_error_code));

static return_t handle_sccp_conf_csp
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_del_sp
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_del_ss
	_ARGS_ ((buffer_t		*p_buffer,
	  error_t		*p_error_code));

static return_t handle_sccp_del_csp
	_ARGS_ ((buffer_t		*p_buffer,
	  error_t		*p_error_code));

static return_t handle_sccp_del_css
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_timer_info
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_sp_info
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_ss_info
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_css_info
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_csp_info
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_init_stats
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_stats
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_disable_stats
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_enable_stats
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_trace_level
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_set_trace_level
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_error_level
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_set_error_level
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_get_event_reporting
        _ARGS_ ((buffer_t               *p_buffer,
         	error_t                *p_error_code));

static return_t handle_sccp_set_event_reporting
        _ARGS_ ((buffer_t               *p_buffer,
         	error_t                *p_error_code));

static return_t handle_sccp_init_redn_data
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_redn_req_act
	_ARGS_ ((buffer_t		*p_buffer,
		 error_t		*p_error_code));

static return_t handle_sccp_redn_recv_update
	_ARGS_ ((buffer_t		*p_buffer,
	 error_t		*p_error_code));

static return_t handle_sccp_activate_module
	_ARGS_ ((buffer_t		*p_buffer,
	 error_t		*p_error_code));

static return_t handle_sccp_display_module_version
	_ARGS_ ((buffer_t		*p_buffer,
	 error_t		*p_error_code));


/******************************************************************************
**
**      FUNCTION :
**              Handle the request from the system management
**
*******************************************************************************
**
**      DESCRIPTION :
**              This function takes the buffer from the system management
**              entity, and parses it.
**              After calling the appropriate function for handling the
**              system management request, the response api is formed and
**              sent back to the system managment.
**
******************************************************************************/

return_t
sccp_handle_sccp_sm_request_api
#ifdef ANSI_PROTO
        (buffer_t              *p_buffer ,
        error_t                 *p_error_code )
#else
        (p_buffer, p_error_code)
        buffer_t                *p_buffer ;
        error_t                 *p_error_code ;
#endif
{
	return_t	return_value ;
	U8bit		command ;
	U8bit		category ;

	category = GET_SM_CAT (p_buffer) ;
	command = GET_SM_CMD (p_buffer) ;

	switch (category)
	{
		case SS7_SM_PROV:
			switch (command)
			{
				/* SPR 1272: Start fix */
				case SCCP_SM_INIT_TIMER:
					return_value =
						handle_sccp_init_timer
						(p_buffer, p_error_code) ;
					break ;
				/* SPR 1272: End fix */

				case SCCP_SM_ADD_SP:
					return_value = 
						handle_sccp_conf_sp
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_ADD_SS:
					return_value = 
						handle_sccp_conf_ss
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_ADD_CSS:
					return_value = 
						handle_sccp_conf_css
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_ADD_CSP:
					return_value = 
						handle_sccp_conf_csp
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_DEL_SP:
					return_value = 
						handle_sccp_del_sp
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_DEL_SS:
					return_value = 
						handle_sccp_del_ss
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_DEL_CSS:
					return_value = 
						handle_sccp_del_css
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_DEL_CSP:
					return_value = 
						handle_sccp_del_csp
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_GET_TIMER_INFO:
					return_value = 
						handle_sccp_get_timer_info
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_GET_SP_INFO:
					return_value = 
						handle_sccp_get_sp_info
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_GET_SS_INFO:
					return_value = 
						handle_sccp_get_ss_info
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_GET_CSS_INFO:
					return_value = 
						handle_sccp_get_css_info
						(p_buffer, p_error_code) ;
					break ;

				case SCCP_SM_GET_CSP_INFO:
					return_value = 
						handle_sccp_get_csp_info
						(p_buffer, p_error_code) ;
					break ;

				default:
					return_value = SS7_FAILURE ;
					*p_error_code=ESCCP_INVALID_SM_COMMAND ;
					break ;
			}
			break ;

		case SS7_SM_CTRL:
			return_value = SS7_FAILURE ;
			*p_error_code=ESCCP_INVALID_SM_COMMAND ;
			break ;

		case SS7_SM_STATS:
			switch (command)
			{
				case SS7_SM_INIT_STATS:
					return_value = 
						handle_sccp_init_stats
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_GET_STATS:
					return_value = 
						handle_sccp_get_stats
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_DISABLE_STATS:
					return_value = 
						handle_sccp_disable_stats
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_ENABLE_STATS:
					return_value = 
						handle_sccp_enable_stats
						(p_buffer, p_error_code) ;
					break ;

				default:
					return_value = SS7_FAILURE ;
					*p_error_code=ESCCP_INVALID_SM_COMMAND ;
					break ;
			}
			break ;

		case SS7_SM_DEBUG:
			switch (command)
			{
				case SS7_SM_GET_TRACE_LEVEL:
					return_value = 
						handle_sccp_get_trace_level
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_SET_TRACE_LEVEL:
					return_value = 
						handle_sccp_set_trace_level
						(p_buffer, p_error_code) ;
					break ;

				default:
					return_value = SS7_FAILURE ;
					*p_error_code=ESCCP_INVALID_SM_COMMAND ;
					break ;
			}
			break ;

		case SS7_SM_ERROR:
			switch (command)
			{
				case SS7_SM_GET_ERR_LEVEL:
					return_value = 
						handle_sccp_get_error_level
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_SET_ERR_LEVEL:
					return_value = 
						handle_sccp_set_error_level
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_GET_EVENT_REPORTING: 
					return_value =	
						handle_sccp_get_event_reporting
						(p_buffer, p_error_code);
					break;
	
				case SS7_SM_SET_EVENT_REPORTING:
					return_value =	
						handle_sccp_set_event_reporting
						(p_buffer, p_error_code);
					break;

				default:
					return_value = SS7_FAILURE ;
					*p_error_code = ESCCP_INVALID_SM_COMMAND ;
					break ;
			}
			break ;

		case SS7_SM_REDN:
			switch (command)
			{
				case SS7_SM_INIT_REDN_DATA:
					return_value = 
						handle_sccp_init_redn_data
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_REDN_REQ_ACT:
					return_value = 
						handle_sccp_redn_req_act
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_REDN_RECV_UPDATE:
					return_value = 
						handle_sccp_redn_recv_update
						(p_buffer, p_error_code) ;
					break ;

				case SS7_SM_ACTIVATE_MODULE:
					return_value = 
						handle_sccp_activate_module
						(p_buffer, p_error_code) ;
					break ;

				default:
					return_value = SS7_FAILURE ;
					*p_error_code = ESCCP_INVALID_SM_COMMAND ;
					break ;
			}
			break ;

		case SS7_SM_DISP:
			switch (command) 
			{
				case SS7_SM_DISPLAY_MODULE_VERSION:
					return_value = 
					    handle_sccp_display_module_version
					    (p_buffer, p_error_code) ;
					break ;
						
				default:
					return_value = SS7_FAILURE ;
					*p_error_code = ESCCP_INVALID_SM_COMMAND;
					break ;
			}
			break ;

		default:
			return_value = SS7_FAILURE ;
			*p_error_code = ESCCP_INVALID_SM_CATEGORY ;
			break ;
	}

	return (return_value) ;
}

/* SPR 1272: Start fix */
/*****************************************************************************
**
**      FUNCTION :
**              Process the SCCP_SM_INIT_TIMER API from the System
**              Management
**
******************************************************************************
**
**      DESCRIPTION :
**
*****************************************************************************/
 
return_t
handle_sccp_init_timer
#ifdef ANSI_PROTO
        (buffer_t               *p_buffer,
         error_t                *p_error_code)
#else
        (p_buffer, p_error_code)
        buffer_t               *p_buffer ;
        error_t                *p_error_code ;
#endif
{
        return_t        return_value = SS7_SUCCESS ;
        U8bit           nelements ;
        s7_len_t           length ;
        U8bit           num_timers ;
 
        /* check the length of the buffer */
        length = GET_API_LEN(p_buffer);
 
        if (length < SCCP_SM_INIT_TIMER_LEN)
        {
                *p_error_code = ESS7_INVALID_LENGTH ;
                return_value = SS7_FAILURE ;
        }
 
 
        if (return_value != SS7_FAILURE)
        {
                /* get the number of elements */
                nelements = GET_API_NELEM (p_buffer) ;
                if (nelements < SCCP_SM_INIT_TIMER_NELEM)
                {
                        *p_error_code = ESS7_INVALID_NUM_API_ELEMENTS ;
                        return_value = SS7_FAILURE ;
                }
        }
 
        if (return_value != SS7_FAILURE)
        {
                num_timers = p_buffer [SS7_SM_API_MIN_LEN] ;
                if (num_timers > SCCP_MAX_TIMER_CONFIG_ID+1)
                {
                        *p_error_code = ESCCP_INVALID_NUM_TIMERS ;
                        return_value = SS7_FAILURE ;
                }
        }
 
        return (return_value) ;
}
/* SPR 1272: End fix */

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_ADD_SP API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_conf_sp
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		sp_id ;
	U32bit		pc ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SCCP_SM_ADD_SP_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_ADD_SP_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		sp_id = GET_BYTE_CODED_SP_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (sp_id >= MAX_SP)
		{
			*p_error_code = ESCCP_INVALID_SP_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		pc = GET_BYTE_CODED_SM_PC (&(p_buffer [SS7_SM_API_MIN_LEN +
		                                       SCCP_SM_SP_ID_LEN +
		                                       SCCP_SM_NW_ID_LEN] )) ;

		/** SPR # 2606 fix Contd. **/
		if ((sccp_sm_client_standard == STACK_ITU) || 	
			(sccp_sm_client_standard == STACK_ETSI) )
		{
			if (pc > 0x3fff) /* max val for 14 bits */
			{
				*p_error_code = ESCCP_INVALID_PC_VALUE ;
				return_value = SS7_FAILURE ;
			}
		}
		else if (( sccp_sm_client_standard == STACK_ANSI) ||
				 ( sccp_sm_client_standard == STACK_BCGR) )
		{
			if (pc > 0xffffff) /* max val for 3 octets */
			{
				*p_error_code = ESCCP_INVALID_PC_VALUE ;
				return_value = SS7_FAILURE ;
			}
		}
		
		/** SPR # 2606 fix END **/
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_ADD_SS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_conf_ss
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		sp_id ;
	U32bit		ss_id ;
	U8bit		ssn ;

	/* check the length of the buffer */
	length = GET_API_LEN (p_buffer);

	if (length < SCCP_SM_ADD_SS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_ADD_SS_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ss_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (ss_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_SS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		sp_id = GET_BYTE_CODED_SP_ID (&(p_buffer [SS7_SM_API_MIN_LEN+
							 					SCCP_SM_SS_ID_LEN])) ;
		if (sp_id >= MAX_SP)
		{
			*p_error_code = ESCCP_INVALID_SP_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ssn = p_buffer [SS7_SM_API_MIN_LEN + SCCP_SM_SS_ID_LEN + SCCP_SM_SP_ID_LEN] ;
     
		if (ssn < 2)
		{
			*p_error_code = ESCCP_INVALID_SSN ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_ADD_CSS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_conf_css
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		css_id ;
	U32bit		ss_id ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_ADD_CSS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_ADD_CSS_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ss_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (ss_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_SS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		css_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN+
		                                           SCCP_SM_SS_ID_LEN])) ;
		if (css_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_CSS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_ADD_CSP API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_conf_csp
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		csp_id ;
	U32bit		ss_id ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SCCP_SM_ADD_CSP_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_ADD_CSP_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ss_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (ss_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_SS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		csp_id = GET_BYTE_CODED_SP_ID (&(p_buffer [SS7_SM_API_MIN_LEN+
												SCCP_SM_SS_ID_LEN])) ;
		if (csp_id >= MAX_SP)
		{
			*p_error_code = ESCCP_INVALID_CSP_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_DEL_SP API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_del_sp
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		sp_id ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_DEL_SP_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_DEL_SP_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		sp_id = GET_BYTE_CODED_SP_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (sp_id >= MAX_SP)
		{
			*p_error_code = ESCCP_INVALID_SP_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_DEL_SS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_del_ss
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		ss_id ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_DEL_SS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_DEL_SS_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ss_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (ss_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_SS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_DEL_CSP API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_del_csp
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		csp_id ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_DEL_CSP_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_DEL_CSP_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		csp_id = GET_BYTE_CODED_SP_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (csp_id >= MAX_SP)
		{
			*p_error_code = ESCCP_INVALID_CSP_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_DEL_CSS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_del_css
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		css_id ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SCCP_SM_DEL_CSS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_DEL_CSS_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		css_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (css_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_CSS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_TIMER_INFO API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_timer_info
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_GET_TIMER_INFO_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_GET_TIMER_INFO_NLEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_SP_INFO API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_sp_info
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_GET_SP_INFO_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_GET_SP_INFO_NLEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_SS_INFO API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_ss_info
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_GET_SS_INFO_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_GET_SS_INFO_NLEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_CSS_INFO API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_css_info
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		ss_id;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_GET_CSS_INFO_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_GET_CSS_INFO_NLEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ss_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (ss_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_SS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_CSP_INFO API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_csp_info
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;
	U32bit		ss_id;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_GET_CSP_INFO_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        nelements = GET_API_NELEM (p_buffer) ;
		if (nelements != SCCP_SM_GET_CSP_INFO_NLEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		ss_id = GET_BYTE_CODED_SS_ID (&(p_buffer [SS7_SM_API_MIN_LEN])) ;
		if (ss_id >= MAX_SS)
		{
			*p_error_code = ESCCP_INVALID_SS_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_INIT_STATS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_init_stats
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		stats_type ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_INIT_STATS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_INIT_STATS_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	stats_type = GET_SM_STAT_TYPE(p_buffer);
	if (return_value != SS7_FAILURE)
	{
		if ((stats_type != STATS_API) &&
			(stats_type != STATS_PROTO_Q752) &&
			(stats_type != STATS_ERROR) &&
			(stats_type != STATS_ALL))
		{
			*p_error_code = ESS7_INVALID_STATS_TYPE;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_STATS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_stats
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		stats_type ;
	Boolean		reset_flag ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_GET_STATS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_GET_STATS_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	stats_type = GET_SM_STAT_TYPE(p_buffer);
	if (return_value != SS7_FAILURE)
	{
		if ((stats_type != STATS_API) &&
			(stats_type != STATS_PROTO_Q752) &&
			(stats_type != STATS_ERROR) &&
			(stats_type != STATS_ALL))
		{
			*p_error_code = ESS7_INVALID_STATS_TYPE;
			return_value = SS7_FAILURE ;
		}
	}

	reset_flag = p_buffer[SM_STAT_TYPE_OFFSET+1];
	if (return_value != SS7_FAILURE)
	{
		if ((reset_flag != SS7_TRUE) && (reset_flag != SS7_FALSE))
		{
			*p_error_code = ESS7_INVALID_API_ELEMENT ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_DISABLE_STATS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_disable_stats
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		stats_type ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_DISABLE_STATS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_DISABLE_STATS_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	stats_type = GET_SM_STAT_TYPE(p_buffer);
	if (return_value != SS7_FAILURE)
	{
		if ((stats_type != STATS_API) &&
			(stats_type != STATS_PROTO_Q752) &&
			(stats_type != STATS_ERROR) &&
			(stats_type != STATS_ALL))
		{
			*p_error_code = ESS7_INVALID_STATS_TYPE ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_ENABLE_STATS API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_enable_stats
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		stats_type ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_ENABLE_STATS_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_ENABLE_STATS_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	stats_type = GET_SM_STAT_TYPE(p_buffer);
	if (return_value != SS7_FAILURE)
	{
		if ((stats_type != STATS_API) &&
			(stats_type != STATS_PROTO_Q752) &&
			(stats_type != STATS_ERROR) &&
			(stats_type != STATS_ALL))
		{
			*p_error_code = ESS7_INVALID_STATS_TYPE ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_TRACE_LEVEL API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_trace_level
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U32bit		trace_flag ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_GET_TRACE_LEVEL_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_GET_TRACE_LEVEL_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		trace_flag = GET_SM_TRC_FLAG(p_buffer);

		/* changed SC_ALL_TRACE to ALL_TRACE */
		if (!(((trace_flag >= INCOMING_TRACE) &&
			  (trace_flag <= PROTO_EXCEPTION_TRACE)) ||
		      (trace_flag == SCMG_TRACE) ||
		      (trace_flag == SCRC_TRACE) ||
		      (trace_flag == SCLC_TRACE) ||
		      (trace_flag == ALL_TRACE)))           
		{
			*p_error_code = ESS7_INVALID_TRACE_FLAG ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_SET_TRACE_LEVEL API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_set_trace_level
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		desired_level ;
	U32bit		trace_flag ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_SET_TRACE_LEVEL_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_SET_TRACE_LEVEL_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		trace_flag = GET_SM_TRC_FLAG(p_buffer);

		if (!(((trace_flag >= INCOMING_TRACE) &&
			  (trace_flag <= PROTO_EXCEPTION_TRACE)) ||
		      (trace_flag == SCMG_TRACE) ||
		      (trace_flag == SCRC_TRACE) ||
		      (trace_flag == SCLC_TRACE) ||
		      (trace_flag == ALL_TRACE)))
		{
			*p_error_code = ESS7_INVALID_TRACE_FLAG ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		desired_level = GET_SM_TRC_LEVEL(p_buffer);
		if (desired_level > DETAILED_TRACE)
		{
			*p_error_code = ESS7_INVALID_TRACE_LEVEL ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_ERROR_LEVEL API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_error_level
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U32bit		error_flag ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SS7_SM_GET_ERR_LEVEL_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_GET_ERR_LEVEL_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		error_flag = GET_SM_ERR_FLAG(p_buffer);

		if ((error_flag < STACK_PROTOCOL_ERROR) ||
			(error_flag > ALL_ERROR))
		{
			*p_error_code = ESS7_INVALID_ERROR_FLAG ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_SET_ERROR_LEVEL API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_set_error_level
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		desired_level ;
	U32bit		error_flag ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SS7_SM_SET_ERR_LEVEL_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_SET_ERR_LEVEL_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		error_flag = GET_SM_ERR_FLAG(p_buffer);

		if ((error_flag < STACK_PROTOCOL_ERROR) ||
			(error_flag > ALL_ERROR))
		{
			*p_error_code = ESS7_INVALID_ERROR_FLAG ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		desired_level = GET_SM_ERR_LEVEL(p_buffer);
		if (!(desired_level <= MINOR_ERROR))
		{
			*p_error_code = ESS7_INVALID_ERROR_LEVEL ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_GET_EVENT_REPORTING API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_get_event_reporting
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U16bit		object_id ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SS7_SM_GET_EVENT_REPORTING_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_GET_EVENT_REPORTING_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		object_id = GET_SCCP_SM_OBJECT_ID(p_buffer);

		if (object_id > SCCP_SM_ALL_OBJECTS)
		{
			*p_error_code = ESS7_INVALID_EVENT_OBJ_ID ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_SET_EVENT_REPORTING API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_set_event_reporting
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	U8bit		desired_level ;
	U16bit		object_id ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SS7_SM_SET_EVENT_REPORTING_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_SET_EVENT_REPORTING_NO_ELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		object_id = GET_SCCP_SM_OBJECT_ID(p_buffer);

		if (object_id > SCCP_SM_ALL_OBJECTS)
		{
			*p_error_code = ESS7_INVALID_EVENT_OBJ_ID ;
			return_value = SS7_FAILURE ;
		}
	}

	if (return_value != SS7_FAILURE)
	{
		desired_level = GET_SCCP_SM_OBJECT_LEVEL(p_buffer);
		if ((desired_level != SCCP_NO_EVENT_RPT) && 
			(desired_level != SCCP_EVENT_RPT))
		{
			*p_error_code = ESS7_INVALID_EVENT_LEVEL ;
			return_value = SS7_FAILURE ;
		}
	}
	
	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_SET_ERROR_LEVEL API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
******************************************************************************
**
**	FUNCTION :
**		Process the SS7_SM_INIT_REDN_DATA API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_init_redn_data
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SCCP_SM_INIT_REDN_DATA_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SCCP_SM_INIT_REDN_DATA_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
	}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SS7_SM_REDN_REQ_ACT API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_redn_req_act
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length != SCCP_SM_REDN_REQ_ACT_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SCCP_SM_REDN_REQ_ACT_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SS7_SM_REDN_RECV_UPDATE API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_redn_recv_update
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SCCP_SM_REDN_RECV_UPDATE_MIN_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SCCP_SM_REDN_RECV_UPDATE_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
		}
	}

	return (return_value) ;
}

/*****************************************************************************
**
**	FUNCTION :
**		Process the SCCP_SM_REDN_ACTIVATE API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
******************************************************************************
**
**	FUNCTION :
**		Process the SCCP_SM_REDN_ACTIVATE API from the System 
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_activate_module
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements ;
	s7_len_t		length ;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);

	if (length < SCCP_SM_ACTIVATE_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH ;
		return_value = SS7_FAILURE ;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
        	nelements = GET_API_NELEM(p_buffer);
		if (nelements != SCCP_SM_ACTIVATE_NELEM)
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS  ;
			return_value = SS7_FAILURE ;
	}
	}

	return (return_value) ;
}


/*****************************************************************************
**
**	FUNCTION :
**		Process the SS7_SM_DISPLAY_MODULE_VERSION from System
**		Management
**
******************************************************************************
**
**	DESCRIPTION :
**
*****************************************************************************/

return_t
handle_sccp_display_module_version
#ifdef ANSI_PROTO
	(buffer_t		*p_buffer,
	 error_t		*p_error_code)
#else
	(p_buffer, p_error_code)
	buffer_t               *p_buffer ;
	error_t                *p_error_code ;
#endif
{
	return_t	return_value = SS7_SUCCESS ;
	U8bit		nelements;
	s7_len_t		length;

	/* check the length of the buffer */
	length = GET_API_LEN(p_buffer);
	
	if (length != SS7_SM_DISPLAY_MODULE_VERSION_LEN)
	{
		*p_error_code = ESS7_INVALID_LENGTH;
		return_value = SS7_FAILURE;
	}

	if (return_value != SS7_FAILURE)
	{
		/* get the number of elements */
		nelements = GET_API_NELEM(p_buffer);
		if (nelements != SS7_SM_DISPLAY_MODULE_VERSION_NO_ELEM)	
		{
			*p_error_code = ESS7_INVALID_NUM_API_ELEMENTS;
			return_value = SS7_FAILURE;
		}
	}

	return (return_value);
}


/***********************************************************************
**     Parse buffer as per the API_ID and call dispatch_buffer. 
**  DESCRIPTION:
**     The function performs the following tasks:
**     (1) Checks API_ID range and its version.
**     (2) Checks source and destination ids.
**     (3) Uses API_ID as an index into api_fptr_table to call the 
**         appropriate API parsing function.
**     (4) Returns error,if call to the parsing function fails,otherwise
**         it calls the dispatch_buffer function. 
**  NOTE:
**     This function must be called after initialization of api_fptr_table
**     by call to sccp_api_fptr_table_init.  
**
*****************************************************************************/

return_t
send_to_sccp
#ifdef ANSI_PROTO
	(buffer_t    *p_buffer,
   s7_len_t    noctets,
   src_id_t    src_id,
   dst_id_t    dst_id,
   error_t     *p_ecode)
#else
	(p_buffer, noctets, src_id, dst_id, p_ecode)
	buffer_t    *p_buffer;
	s7_len_t    noctets;
	src_id_t    src_id;
	dst_id_t    dst_id;
	error_t     *p_ecode;
#endif
{
 
	/* API_ID range check */ 
  if((*p_buffer) != SCCP_SM_REQUEST_API)
    {
    *p_ecode=ESS7_INVALID_API_ID;
    return EAPI_ERROR;                     
  }
  
	/* API version ID check */
  if(*(p_buffer+1)!=SCCP_VERSION_NUMBER) {
    *p_ecode=EVERSION_ID;
    return EAPI_ERROR;
  } 

	/* call to appropriate API parsing function as per API_ID  */    
  if(sccp_handle_sccp_sm_request_api(p_buffer,p_ecode)==SS7_FAILURE)
    return EAPI_ERROR;

	/* call to dispatch_buffer */
  if(sccp_dispatch_buffer(p_buffer,noctets,src_id,dst_id,p_ecode)==SS7_FAILURE) 
    return ESYS_ERROR; 

	/* no API or system related errors */
  return SS7_SUCCESS;
}


