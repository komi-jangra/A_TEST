/***************************************************************************
**  FILE NAME:
**      sc_sys.c
**
****************************************************************************
**
**  FUNCTION:
**      interfaces for SCCP to the functions of ss7stack
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   		REASON
**  -------  ----------------  ----------   ---------------------------------
**  28Jan03  Ashish Sawalkar   ----------	SPR 10862
**  26Jul01  Rajesh Mehta      SPR# 5766    Fixing spr 5766
**  03NOV00  Arun Kumar	       SPR# 4543    Adding TRAFFIC Statistics
**  10May99  Sudipta Pattar    -----------  Fixed SPR 1596
**  15May98  Sriganesh. Kini   HSS20800008  Original
**
**  Copyright 2000, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

S8bit * success_str =(S8bit *) "SS7_SUCCESS";
S8bit * failure_str =(S8bit *) "SS7_FAILURE";
/* start added during CC compilation */
/* string initialization for SS7_SUCCESS and SS7_FAILURE */
/* end added during CC compilation */
#ifdef SCCP_UT_DEBUG
src_id_t sccp_src_id = SCCP_MODULE_ID;
module_id_t sccp_module_id = SCCP_MODULE_ID;
dst_id_t m3_dst_id = MTP3_MODULE_ID;
#endif

extern U8bit sccp_state;	/* spr 10862 fix */

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
sccp_malloc
#ifdef ANSI_PROTO
	(U32bit size)
#else
	(size)
	 U32bit size;
#endif
{
	U8bit * p_buf;

	p_buf = (U8bit *)ss7_mem_get((s7_len_t)size);

	SC_R_TRC (("SCCP::INIT: mallocing %u\n", size));

	if (SS7_NULL == p_buf)
	{
		SC_STAT_ERR_INR_ERR_SYSTEM_RES();
		SC_R_TRC (("SCCP::INIT: %s\n", failure_str));
		SC_R_ERR (ESS7_MEMORY_ALLOCATION_FAILURE);
	}

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
sccp_free
#ifdef ANSI_PROTO
	(U8bit * p_buf)
#else
	(p_buf)
	 U8bit *p_buf;
#endif
{
	SC_R_TRC (("SCCP::INIT: Freeing memory\n"));

	if (SS7_FAILURE == ss7_mem_free((pvoid)p_buf))
	{
		SC_STAT_ERR_INR_ERR_SYSTEM();
		SC_S_TRC(("SCCP::INIT: Mem free failed\n"));
		SC_S_ERR (ESS7_MEMORY_DEALLOCATION_FAILURE);
	}
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
		SC_STAT_ERR_INR_ERR_SYSTEM_RES();
		SC_S_TRC(("SCCP::INIT: Failed to start timer\n"));
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
		SC_STAT_ERR_INR_ERR_SYSTEM ();
		SC_S_TRC (("SCCP::INIT: Failed to stop timer\n"));
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
**         sends a API to RM module
******************************************************************************
**
**      DESCRIPTION :
**         calls send_from_sccp to send a message to RM
**
**      NOTE :Created by Amaresh for REDN update o SCCP data.
**
*****************************************************************************/

void
sccp_sendto_rm
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

	if (SS7_FAILURE == (ret_val = send_from_sccp (p_api, GET_API_LEN(p_api),
	                                          SCCP_MODULE_ID, SCCP_RM_MODULE_ID,
	                                          &ecode)))
	{
/* commenting out sccp_free call spr 5766 */
/*		sccp_free (p_api);        */
/*     spr 5766 fix ends  */
		SC_S_ERR (ecode);
	}

	SC_O_TRC (("SCCP::SEND DATA UPDATE: %s to RM\n",
	           (ret_val == SS7_SUCCESS) ? "Sent msg" : "Failed send"));
  /*Amaresh Commented code 22-02-16 */

#if 0
/* Added by Amaresh start as on dated 15-09-16 for REDUNDANCY UPDATE STANDBY CARD free memory leak */
     if(p_api)
    {
        sccp_free (p_api);
        SC_O_TRC (("SCCP::INIT:Free Memory in function sccp_sendto_rm from send_from_sccp \n"));
    }
/* Added by Amaresh stop as on dated 29-04-15 for REDUNDANCY UPDATE STANDBY CARD free memory leak */
#endif
}


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

	if (SS7_FAILURE == (ret_val = send_from_sccp (p_api, GET_API_LEN(p_api),
	                                          SCCP_MODULE_ID, SYS_MGMT_MODULE_ID,
	                                          &ecode)))
	{
/* commenting out sccp_free call spr 5766 */
/*		sccp_free (p_api);        */
/*     spr 5766 fix ends  */
		SC_S_ERR (ecode);
	}

	SC_O_TRC (("SCCP::INIT: %s to SM\n",
	           (ret_val == SS7_SUCCESS) ? "Sent msg" : "Failed send"));

/* Added by Amaresh start as on dated 15-09-16 for REDUNDANCY UPDATE STANDBY CARD free memory leak */
     if(p_api)
    {
        sccp_free (p_api);
        SC_O_TRC (("SCCP::INIT:Free Memory in function sccp_sendto_sm  from send_from_sccp \n"));
    }
/* Added by Amaresh stop as on dated 29-04-15 for REDUNDANCY UPDATE STANDBY CARD free memory leak */

  /*Amaresh Commented code 22-02-16 */
}

/*****************************************************************************
**      FUNCTION :
**         sends a api to TCAP
******************************************************************************
**
**      DESCRIPTION :
**         calls send_from_sccp to send a message to tcap
**
**      NOTE :
**
*****************************************************************************/

void
sccp_sendto_tc
#ifdef ANSI_PROTO
	(U8bit * p_api, ss_entry_t * p_ss)
#else
	(p_api, p_ss)
	 U8bit 		* p_api;
	 ss_entry_t 	*p_ss;
#endif
{
	error_t ecode;
	return_t ret_val;

	SC_A_DTRC (p_api);
	SC_STAT_API_INR_OUT_API_SU();

/* Added by Amaresh for EMAP/BSSAP Handelling by checking ssn start only One user can connect i.e EMAP or BSSAP */
	if((p_ss->ssn == 32) || (p_ss->ssn == 254))
	{
			if (SS7_FAILURE == (ret_val = send_from_sccp (p_api, GET_API_LEN(p_api),
                                            SCCP_MODULE_ID, BSSAP_MODULE_ID,
                                            &ecode)))
			{
					SC_S_ERR (ecode);
			}
	}
/* Added by Amaresh for EMAP/BSSAP  Handelling by checking ssn stop */
  else
	{
			/* SPR 1717: Send buffer to destination id as in p_ss */
			if (SS7_FAILURE == (ret_val = send_from_sccp (p_api, GET_API_LEN(p_api),
	                                          SCCP_MODULE_ID, p_ss->dst_id,
	                                          &ecode)))
			{
								/* spr 5766 fix starts  */
								/*		sccp_free (p_api);  */
								/* spr 5766 fix ends               */		
           SC_S_ERR (ecode);   
			}
	}
	/*
	SC_O_TRC (("SCCP::INIT: %s to subsystem %d of pc %d of nw %d\n",
	           (ret_val == SS7_SUCCESS) ? "Sent msg" : "Failed send",
	           GET_SS_SSN(p_ss),
	           GET_SP_PC(GET_SP_OF_SS(p_ss)), GET_SS_NW_ID(p_ss)));
		*/

/* Added by Amaresh start as on dated 29-04-15 for memory leak */
     if(p_api)
    {
        sccp_free (p_api);
        SC_O_TRC (("SCCP::INIT:Free Memory from send_from_sccp \n"));
    }
/* Added by Amaresh stop as on dated 29-04-15 for memory leak */

}

/*****************************************************************************
**      FUNCTION :
**         sends a api to MTP3
******************************************************************************
**
**      DESCRIPTION :
**         calls send_to_mtp3 to send a API to mtp3
**      NOTE :
**
*****************************************************************************/

void
sccp_sendto_m3
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit *p_api;
#endif
{
	error_t ecode;
	return_t ret_val;
  U32bit len = 0;

	/* spr 10862 fix */
	/* Dropping message for MTP3 if the stack is in BLOCKED state */
	if (sccp_state == BLOCKED)
	{
		SC_O_TRC (("SCCP::INIT: SCCP in BLOCKED state. Message Dropped\n"));
		sccp_free(p_api);
		return;
	}

	SC_A_DTRC (p_api);
	SC_STAT_API_INR_OUT_API_LL();


	if (SS7_FAILURE == (ret_val = send_to_mtp3 (p_api, GET_API_LEN(p_api),
	                                        SCCP_MODULE_ID, MTP3_MODULE_ID,
	                                        &ecode)))
	{
		sccp_free (p_api);
		SC_S_ERR (ecode);
	}
	/* SPR# 4543 Start */
	else
	{ /* Increment the Traffic related statistics */
		SC_STAT_TRAFFIC_INR_PKT_SENT();
	}	
	/* SPR# 4543 End */
	SC_O_TRC (("SCCP::INIT: %s to lower layer\n",
	           (ret_val == SS7_SUCCESS) ? "Sent msg" : "Failed send"));

/* Added by Amaresh Start for remove memory leak xudt message */
  if(p_api)
{
  len = GET_API_LEN(p_api);
  if (len >= SCCP_DEFAULT_SEG_SIZE && len <= SCCP_MAX_XUDT_SEG_SIZE)
  {
    sccp_free (p_api);
    SC_O_TRC (("SCCP::INIT:Free Memory Segmented message having len 160 to 254\n"));
  }
}
/* Added by Amaresh Stop for remove memory leak xudt message */

}

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

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building %s\n", p_trstr));

	/* SPR 1596: Start fix
	 * Calculate the buffer length required 
	 */
        if (ret_val == SS7_FAILURE)
                buff_len = SCCP_SM_STD_RESP_LEN + 2;
        else
                buff_len = SCCP_SM_STD_RESP_LEN;
	if (put_param)
		buff_len++;

	if (SS7_NULL == (p_buf = sccp_malloc(buff_len)))
	{
		SC_A_TRC (("SCCP::INIT: Cannot %s\n", p_trstr));
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

	SC_A_TRC (("SCCP::INIT: Built %s\n", p_trstr));

   SCCP_HEX_DUMP(INIT_TRACE, DETAILED_TRACE, p_buf, (U32bit)buff_len);/* Commented by Amaresh 26-09-14*/

	sccp_sendto_sm (p_buf);
}

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


