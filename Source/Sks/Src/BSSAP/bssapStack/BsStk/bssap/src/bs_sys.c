/*******************************************************************************
**      FILE NAME:
**          bs_sys.c
**
**      DESCRIPTION:
**              This file defines the OS related functionalities used by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#include "bs_stgl.h"
#include "bs_debug.h"

S8bit * success_str =(S8bit *) "SS7_SUCCESS";
S8bit * failure_str =(S8bit *) "SS7_FAILURE";

extern U8bit bssap_state;	
void sccp_fill_api_header (U8bit * p_api, api_id_t api_id, U8bit nelem, U16bit len);

/*****************************************************************************
**      FUNCTION :
**         allocates memory
******************************************************************************
**
**      DESCRIPTION :
**         calls ss7_mem_get to allocate memory
**
**      NOTE :
**
*****************************************************************************/

U8bit *
bssap_malloc
#ifdef ANSI_PROTO
	(U32bit size)
#else
	(size)
	 U32bit size;
#endif
{
	U8bit * p_buf;

	p_buf = (U8bit *)ss7_mem_get((s7_len_t)size);
	if (SS7_NULL == p_buf)
	{
		 
		SC_R_TRC (("BSSAP::INIT: %s\n", failure_str));
		SC_R_ERR (ESS7_MEMORY_ALLOCATION_FAILURE);
	}
#ifdef MEM_LEAK
	SC_R_TRC (("BSSAP: MALLOC MEM %u\n", size));
#endif

	return p_buf;
}

/*****************************************************************************
**      FUNCTION :
**          frees memory
******************************************************************************
**
**      DESCRIPTION :
**          frees memory by calling ss7_mem_free
**
**      NOTE :
**
*****************************************************************************/

void
bssap_free
#ifdef ANSI_PROTO
	(U8bit * p_buf)
#else
	(p_buf)
	 U8bit *p_buf;
#endif
{

	if (SS7_FAILURE == ss7_mem_free((pvoid)p_buf))
	{
		 
		BS_S_TRC(("BSSAP::INIT: Mem free failed\n"));
		SC_S_ERR (ESS7_MEMORY_DEALLOCATION_FAILURE);
	}
#ifdef MEM_LEAK
	SC_R_TRC (("BSSAP:: FREE MEM \n"));
#endif
}

/*****************************************************************************
**      FUNCTION :
**         starts timer
******************************************************************************
**
**      DESCRIPTION :
**         calls ss7_start_timer to start timer
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_start_timer
#ifdef ANSI_PROTO
	(U32bit 	timer_val,
	 U8bit 		*p_timer_buf,
	 U32bit		buf_len,
	 timer_id_t 	*p_timer_id)
#else
	(timer_val, p_timer_buf, buf_len, p_timer_id)
	 U32bit 	timer_val;
	 U8bit 		*p_timer_buf;
	 U32bit		buf_len;
	 timer_id_t 	*p_timer_id;
#endif
{
	return_t ret_val;
	error_t ecode;

	SC_R_TRC (("SCCP::INIT: starting timer of value %u\n", timer_val));

	if (SS7_FAILURE == (ret_val = ss7_start_timer (timer_val, p_timer_buf,
	                                           buf_len, SCCP_MODULE_ID,
	                                           p_timer_id, &ecode)))
	{
		 
		BS_S_TRC(("SCCP::INIT: Failed to start timer\n"));
		SC_S_ERR (ESS7_FAILURE_TO_START_TIMER);
	}

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         stops a timer
******************************************************************************
**
**      DESCRIPTION :
**         calls ss7_stop_timer to stop a timer
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stop_timer
#ifdef ANSI_PROTO
	(timer_id_t * p_timer_id)
#else
	(p_timer_id)
	 timer_id_t *p_timer_id;
#endif
{
	error_t ecode;

	SC_R_TRC (("SCCP::INIT: stopping timer\n"));

	if (SS7_FAILURE == ss7_stop_timer (*p_timer_id, &ecode))
	{
		BS_S_TRC (("SCCP::INIT: Failed to stop timer\n"));
		/* Define error for stop timer error SC_ERR(); */
	}
}

#ifdef SCCP_UT_DEBUG
/*****************************************************************************
**      FUNCTION :
**         sets the stacks source id
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_set_src_id
#ifdef ANSI_PROTO
	(src_id_t src_id)
#else
	(src_id)
	 src_id_t src_id;
#endif
{
	sccp_src_id = src_id;
	return;
}

/*****************************************************************************
**      FUNCTION :
**         sets module id of stack
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_set_module_id
#ifdef ANSI_PROTO
	(module_id_t module_id)
#else
	(module_id)
	 module_id_t module_id;
#endif
{
	sccp_module_id = module_id;
	return;
}
#endif


/*****************************************************************************
**      FUNCTION :
**         sends a API to SM
******************************************************************************
**
**      DESCRIPTION :
**         calls send_from_sccp to send a message to SM
**
**      NOTE :
**
*****************************************************************************/

void
sccp_sendto_sm
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	error_t ecode;
	return_t ret_val;

	SC_A_DTRC (p_api);
#if 0
	if (SS7_FAILURE == (ret_val = send_from_sccp (p_api, GET_API_LEN(p_api),
	                                          SCCP_MODULE_ID, SYS_MGMT_MODULE_ID,
	                                          &ecode)))
	{
/* commenting out bssap_free call spr 5766 */
/*		bssap_free (p_api);        */
/*     spr 5766 fix ends  */
		SC_S_ERR (ecode);
	}
#endif /* Amaresh not to do */

	SC_O_TRC (("SCCP::INIT: %s to SM\n",
	           (ret_val == SS7_SUCCESS) ? "Sent msg" : "Failed send"));
}

#if 0

/*****************************************************************************
**      FUNCTION :
**         sends  standard response to a SM command
******************************************************************************
**
**      DESCRIPTION :
**         prepares teh api buf to send the standard response to SM command
**         and calls send_from_sccp to send it
**
**      NOTE :
**
*****************************************************************************/

void
sccp_sm_cmd_std_resp
#ifdef ANSI_PROTO
	(U8bit 		*p_api,
	 return_t 	ret_val,
	 U8bit 		param,
	 Boolean 	put_param,
	 error_t 	ecode)
#else
	(p_api, ret_val, param, put_param, ecode)
	(U8bit 		*p_api,
	 return_t 	ret_val,
	 U8bit 		param,
	 Boolean 	put_param,
	 error_t 	ecode)
#endif
{
	U8bit * p_buf, * p_elem, nelem, buff_len;
#ifdef SCCP_TRACE_ENABLED
	S8bit * p_trstr = (S8bit *)"response to SM"; 
/* start added during CC compilation */
/* string  for initialisaation (S8bit *)"response to SM" */
/* end added during CC compilation */



#endif

	BS_A_TRC (("SCCP::INIT: Building %s\n", p_trstr));

	/* SPR 1596: Start fix
	 * Calculate the buffer length required 
	 */
        if (ret_val == SS7_FAILURE)
                buff_len = SCCP_SM_STD_RESP_LEN + 2;
        else
                buff_len = SCCP_SM_STD_RESP_LEN;
	if (put_param)
		buff_len++;

	if (SS7_NULL == (p_buf = bssap_malloc(buff_len)))
	{
		BS_A_TRC (("SCCP::INIT: Cannot %s\n", p_trstr));
		return;
	}
        /* SPR 1596: End fix */

	nelem = SCCP_SM_STD_RESP_MIN_NELEM;

	if (put_param) nelem++;
	if (ret_val == SS7_FAILURE) nelem ++; /* error code parameter */

        /* SPR 1596: Fill api header with correct buffer length */
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
	                      nelem, buff_len);


	p_elem = p_buf + API_HEADER_LEN;
	p_api += API_HEADER_LEN;

	/* SM header */
	*p_elem = *p_api;            /* Category */
	p_api  += SM_CATEGORY_LEN;
	p_elem += SM_CATEGORY_LEN;
	*p_elem = *p_api;            /* Command */
	p_api  += SM_COMMAND_LEN;
	p_elem += SM_COMMAND_LEN;
	*p_elem = *p_api;            /* transaction id */
	p_api  += SM_TRANS_ID_LEN;
	p_elem += SM_TRANS_ID_LEN;
	/* result of executing the SM command */
	*p_elem++ = ret_val;

	if (put_param)
		*p_elem++ = param;

	if (SS7_FAILURE == ret_val)
	{
		*p_elem++ = (U8bit)ecode;
		*p_elem++ = (U8bit)(ecode >> 8);
	}

	BS_A_TRC (("SCCP::INIT: Built %s\n", p_trstr));
#if 0
   SCCP_HEX_DUMP(INIT_TRACE, DETAILED_TRACE, p_buf, (U32bit)buff_len);

	sccp_sendto_sm (p_buf);
#endif /* Amaresh */
}
#endif

/*****************************************************************************
**      FUNCTION :
**        fills the API header of 
******************************************************************************
**
**      DESCRIPTION :
**         fills api_id, version id, num elems and length of an API
**
**      NOTE :
**
*****************************************************************************/

void
sccp_fill_api_header
#ifdef ANSI_PROTO
	(U8bit * p_api, api_id_t api_id, U8bit nelem, U16bit len)
#else
	(p_api, api_id, nelem, len)
	 U8bit 		*p_api;
	 api_id_t 	api_id;
	 U8bit 		nelem;
	 U16bit 	len;
#endif

{
	p_api[API_ID_OFFSET] = api_id;
	p_api[API_VER_OFFSET] = SCCP_VERSION_ID;
	p_api[API_NELEM_OFFSET] = nelem;
	p_api[API_LEN_LSB] = (U8bit)len;
	p_api[API_LEN_MSB] = (U8bit)(len >> 8);
}


