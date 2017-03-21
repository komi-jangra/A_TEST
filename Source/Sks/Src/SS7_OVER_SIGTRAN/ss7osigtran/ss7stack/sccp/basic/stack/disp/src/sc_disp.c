/******************************************************************************
**      FUNCTION:
**         Contains display functions for the SCCP module
**
*******************************************************************************
**
**      FILE NAME:
**          sc_disp.c
**
**      DESCRIPTION:
**         This file contains functions to send display information to the SM
**	   related to the SCCP module versions.
**
**       DATE          NAME           REFERENCE            REASON
**       ----          ----           ---------            ------
**
**      07Feb99    Sudipta Nandi                          ORIGINAL
**      22Oct01    Prateek Bidwalkar					  Fixed SPR 6566
**      18Dec01    Ashish Sawalkar 						  Fixed SPR 7490 
**      20Jun02    Suyash Tripathi 			 Fixed SPR 8985 
**      20Jun02    Suyash Tripathi 			 Fixed SPR 9023 
**      08Apr04    Hitesh Sharma 			 Fixed SPR 13344 
**
**
**      Copyright 1999, Hughes Software Systems, Inc.
**
******************************************************************************/

#include "sc_stgl.h"
#include "sc_disp.h"

static void sccp_disp_sm_cmd_resp
        _ARGS_ ((U8bit * p_api, module_version_t version));


/*****************************************************************************
**      FUNCTION :
**            handles SM command category DISPLAY
******************************************************************************
**
**      DESCRIPTION :
**         calls appropriate function to send the DISPLAY response
**
**      NOTE :
**
*****************************************************************************/

void
sccp_display_handle_sm_cmd
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
         U8bit * p_api;
#endif
{
	U8bit cmd;
	return_t ret_val = SS7_SUCCESS;
	error_t  ecode;
        U8bit param = 0;
        Boolean put_param = SS7_FALSE;
	module_version_t version;

/* SPR#6566 : Fix Start */
	pc_t		pc;
	U8bit		ssn;
	U8bit		user_status;

	pc			= 0;
	ssn			= 0;
	user_status = 0;
/* SPR#6566 : Fix End */

	cmd = GET_SM_CMD(p_api);
	
        SC_A_TRC (("SCCP::DISP: SM category DISPLAY\n"));

	switch (cmd) 
	{
		case SS7_SM_DISPLAY_MODULE_VERSION:
                        SC_A_TRC(("SCCP::DISP: Display module version cmd\n"));
			ret_val = sccp_display_module_version(&version, &ecode);
			if(SS7_SUCCESS == ret_val)
			{
        		sccp_disp_sm_cmd_resp (p_api, version);
			}
			break;
/* SPR # 6566 : Fix Start */
		case SS7_SM_DISPLAY_SS_STATUS:
				
				SC_A_TRC(("SCCP::DISP: Display Subsystem status\n"));
				ret_val = sccp_display_parse_ss_status_api(p_api, &pc, &ssn);

				if(SS7_SUCCESS == ret_val)
					ret_val = sccp_display_ss_status(pc, ssn, &user_status,\
													 &ecode);

				if(SS7_SUCCESS == ret_val)
				{
					put_param = SS7_TRUE;
					param = user_status;
					sccp_sm_cmd_std_resp(p_api, ret_val, param, \
										 put_param, ecode);
				}
				break;
/* SPR # 6566 : Fix End */

/* SPR 7490 : Start Fix */ 
		case SS7_SM_DISPLAY_SP_STATUS:
				
				SC_A_TRC(("SCCP::DISP: Display Signalling Point status\n"));
				ret_val = sccp_display_parse_sp_status_api(p_api, &pc);

				if(SS7_SUCCESS == ret_val)
					ret_val = sccp_display_sp_status(pc, &user_status,\
													 &ecode);

				if(SS7_SUCCESS == ret_val)
				{
					put_param = SS7_TRUE;
					param = user_status;
					sccp_sm_cmd_std_resp(p_api, ret_val, param, \
										 put_param, ecode);
				}
				break;
/* SPR 7490 : End Fix */ 
        default:
                SC_A_TRC(("SCCP::DISP: Invalid DISPLAY cmd %d\n",cmd));
                ret_val = SS7_FAILURE;
                ecode = ESS7_INVALID_API_ELEMENT;
                break;
        }

        if (SS7_FAILURE == ret_val)
	{
                SC_A_ERR (ecode);
	        sccp_sm_cmd_std_resp (p_api, ret_val, param, put_param, ecode);
		return;
	}
/* SPR 8985 - Fix Start */
#if 0
	else
        	sccp_disp_sm_cmd_resp (p_api, version);
#endif
/* SPR 8985 - Fix End   */

}

/*****************************************************************************
**      FUNCTION :
**            Sends response to SM DISP category command
******************************************************************************
**
**      DESCRIPTION :
**	      Prepares the API buffer and sends the DISPLAY response to SM
**
**      NOTE :
**
*****************************************************************************/

void
sccp_disp_sm_cmd_resp
#ifdef ANSI_PROTO
        (U8bit             * p_api,
	 module_version_t  version)
#else
        (p_api, version)
         U8bit            * p_api;
	 module_version_t version;

#endif
{

	U8bit *p_buf, *p_elem, nelem, buf_len;
#ifdef SCCP_TRACE_ENABLED
        S8bit * p_trstr =(S8bit *) "display response to SM";
/* start added during CC compilation */
/* string initialiase by S8bit * */
/* end added during CC compilation */ 
#endif


	SC_STAT_API_INR_OUT_API_SM () ;
        SC_A_TRC (("SCCP::DISP: Building %s\n", p_trstr));

	nelem = SS7_SM_API_MIN_NO_ELEM + 5;  /* category, command, trans_id,
		status, major rel no, minor rel no, standard, std_version */   
	buf_len = SS7_SM_API_MIN_LEN + 5;
	
        if (SS7_NULL == (p_buf = sccp_malloc(buf_len)))
        {
                SC_A_TRC (("SCCP::DISP: Cannot build %s\n", p_trstr));
                return;
        }
	
        sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                       		nelem, buf_len);

        p_elem = p_buf + API_HEADER_LEN;
        p_api += API_HEADER_LEN;

	*p_elem = *p_api;		 	/* Category */
	p_elem += SM_CATEGORY_LEN;
	p_api  += SM_CATEGORY_LEN;
	*p_elem = *p_api; 			/* Command */
        p_elem += SM_COMMAND_LEN;
        p_api  += SM_COMMAND_LEN;
        *p_elem = *p_api;            		/* Transaction id */
        p_api  += SM_TRANS_ID_LEN;
        p_elem += SM_TRANS_ID_LEN;
        *p_elem++ = SS7_SUCCESS;	   	/* Status */

	*p_elem++ = version.major_version;      /* Major Rel No */	
	*p_elem++ = version.minor_version;      /* Minor Rel No */ 
	*p_elem++ = version.standard;	       	/* Standard */
	*p_elem   = version.standard_version;  	/* Standard version */

        SC_A_TRC (("SCCP::DISP: Built %s\n", p_trstr));

        sccp_sendto_sm (p_buf);
}


/*****************************************************************************
**      FUNCTION :
**	      Function called to get the module version information
**            
******************************************************************************
**
**      DESCRIPTION :
**	      Fills in the version information for the layer in the
**	      struct of type module_version_t
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_display_module_version
#ifdef ANSI_PROTO
        (module_version_t * version,
         error_t          * p_ecode)
#else
        (version, ecode)
         module_version_t * version;
         error_t          * p_ecode;

#endif
{
	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }

	/* Fill in the module version information */
	version->major_version = SCCP_MAJOR_VERSION_NO;
	version->minor_version = SCCP_MINOR_VERSION_NO;
	version->standard = sc_opt.standard;  
	 
	/* Version of the Standard */
	switch (sc_opt.standard)
	{
		case STACK_ITU:
			version->standard_version = 
				SCCP_STANDARD_ITU_VERSION;
			break;
		case STACK_ETSI:
			version->standard_version = 
				SCCP_STANDARD_ETSI_VERSION;
			break;
		case STACK_ANSI:
			version->standard_version = 
				SCCP_STANDARD_ANSI_VERSION;
			break;
		case STACK_BCGR:
			version->standard_version = 
				SCCP_STANDARD_BCGR_VERSION;
			break;
                case STACK_JAPANESE:
                         version->standard_version =
                                SCCP_STANDARD_ITU_VERSION;
                        break;
                case STACK_CHINESE:
                         version->standard_version =
                                SCCP_STANDARD_ITU_VERSION;
                        break;

		default:
                        *p_ecode = ESS7_INVALID_STANDARD;
			return (SS7_FAILURE);
	}
	return (SS7_SUCCESS);		
}

/* SPR # 6566 : Fix Start */

/*****************************************************************************
**      FUNCTION :
**	      Function called to get the sub system status 
**            
******************************************************************************
**
**      DESCRIPTION :
**	      Fills the status of the subsystem in the user_status parameter
**
**      NOTE :
**           The first 3 bits of the user_status are used to indicate the 
**           status of the subsytem
**         [MSB]  Bit->0 = 1 ; Configured
**           	  Bit->0 = 0 ; Unconfigured
**                Bit->1 = 1 ; Registered
**           	  Bit->1 = 0 ; Unregistered
**                Bit->2 = 1 ; Allowed
**                Bit->2 = 0 ; Unallowed
**                Bit->3 to 7 are spare 
**
*****************************************************************************/
return_t
sccp_display_ss_status
#ifdef ANSI_PROTO
	(pc_t 		pc,
	 U8bit 		ssn,
	 U8bit  	*p_user_status,
	 error_t	*p_ecode)
#else
	(pc, ssn, p_user_status, p_ecode)
	 pc_t	 pc;
	 U8bit	 ssn;
	 U8bit   *p_user_status;
	 error_t *p_ecode;
#endif
{
	sp_entry_t	*p_sp;
	ss_entry_t	*p_ss;
 extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }



	p_sp = sccp_db_find_sp(DEFAULT_NW_ID, pc);	
    if(SS7_NULL == p_sp)
	{
		*p_ecode = ESCCP_INVALID_AFFECTED_SUBSYSTEM;
		return SS7_FAILURE;
	}

    p_ss = sccp_db_find_ss(p_sp, ssn);
    if(SS7_NULL == p_ss)
	{
		*p_ecode = ESCCP_INVALID_AFFECTED_SUBSYSTEM;
		return SS7_FAILURE;
	}

	
	/* Check if the subsystem is configured */
	if(IS_SS_CONFIGURED(p_ss))
	{
		*p_user_status |= SCCP_SM_SS_CONFIGURED;
	}

	/* Check if the subsystem is registered */
	if(IS_SS_REGISTERED(p_ss))
	{
		*p_user_status |= SCCP_SM_SS_REGISTERED;
	}

	/* Check if the subsystem is allowed */
	if(IS_SS_ALLOWED(p_ss))
	{
		*p_user_status |= SCCP_SM_SS_ALLOWED;
	}
	return  SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**	      Function called to get the sub system status 
**            
******************************************************************************
**
**      DESCRIPTION :
**	      Fills the status of the subsystem in the user_status parameter
**
**      NOTE :
**
**
*****************************************************************************/
return_t 
sccp_display_parse_ss_status_api
#ifdef ANSI_PROTO
	(U8bit *p_api, pc_t *p_pc, U8bit *p_ssn)
#else
	(p_api, p_pc, p_ssn)
	 U8bit	 *p_api;
	 pc_t    *p_pc;
	 U8bit	 *p_ssn;
#endif
{

#if defined(SCCP_CHINESE) || defined(SCCP_ANSI) || defined(SCCP_BCGR)
    if(COMPARE_CHINESE || COMPARE_ANSI || COMPARE_BCGR)
	{
		/* SPR 9023 - Fix Start */
		/* calculate the point code */
		*p_pc = p_api[SS7_SM_DISPLAY_SS_OFFSET];
		*p_pc |= p_api[SS7_SM_DISPLAY_SS_OFFSET+1]<<8;
		*p_pc |= p_api[SS7_SM_DISPLAY_SS_OFFSET+2]<<16;

		*p_ssn = p_api[SS7_SM_DISPLAY_SS_OFFSET+3];
		/* SPR 9023 - Fix End   */
	}
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) )
	if( (COMPARE_ITU) || (COMPARE_JAPANESE))
	{
		*p_pc = p_api[SS7_SM_DISPLAY_SS_OFFSET]; 
		*p_pc |= p_api[SS7_SM_DISPLAY_SS_OFFSET+1]<<8; 

		*p_ssn = p_api[SS7_SM_DISPLAY_SS_OFFSET+2];
	}
#endif



	return SS7_SUCCESS;
}
/* SPR # 6566 : Fix End */

/* SPR 7490 : Start Fix */
/*****************************************************************************
**      FUNCTION :
**        Function called to get the signalling point status
**
******************************************************************************
**
**      DESCRIPTION :
**        Returns the status of the signalling point (local or remote) in 
** 		  the user_status parameter
**
**      NOTE :
**			Returns the following values in user_status parameter -	
**					
**				SP_INACCESSIBLE 
**				SP_CONGESTED
**				SP_ACCESSIBLE 
**
*****************************************************************************/
return_t
sccp_display_sp_status
#ifdef ANSI_PROTO
	(pc_t		pc,
	 U8bit		*p_sp_status,
	 error_t 	*p_ecode)
#else
	(pc, p_user_status, p_ecode)
	 pc_t		pc;
	 U8bit		*p_sp_status;
	 error_t	*p_ecode;
#endif
{
	sp_entry_t	*p_sp;

	p_sp = sccp_db_find_sp(DEFAULT_NW_ID, pc);
	if(SS7_NULL == p_sp)
	{
		*p_ecode = ESCCP_INVALID_POINT_CODE;
		return SS7_FAILURE;
	}

	if(!p_sp->allowed)
		*p_sp_status = SP_INACCESSIBLE;
	else
	{
	/* Fix for SPR No: 13344 Start */ 
		if(p_sp->ril > 0)
	/*	if(p_sp->cls > 0)	*/
	/* Fix for SPR No: 13344 Stop */ 
			*p_sp_status = SP_CONGESTED;
		else
			*p_sp_status = SP_ACCESSIBLE;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**        Function called to parse the SP Status API received. 
**       
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
**
*****************************************************************************/
return_t
sccp_display_parse_sp_status_api
#ifdef ANSI_PROTO
	(U8bit *p_api, pc_t *p_pc)
#else
	(p_api, p_pc)
	 U8bit	*p_api;
	 pc_t	*p_pc;
#endif
{
#if defined(SCCP_CHINESE) || defined(SCCP_ANSI) || defined(SCCP_BCGR)
    if(COMPARE_CHINESE || COMPARE_ANSI || COMPARE_BCGR)
    {
	/* SPR 9023 - Fix Start */
        /* calculate the point code */
	*p_pc = p_api[SS7_SM_DISPLAY_SS_OFFSET];
	*p_pc |= p_api[SS7_SM_DISPLAY_SS_OFFSET+1]<<8;
	*p_pc |= p_api[SS7_SM_DISPLAY_SS_OFFSET+2]<<16;
	/* SPR 9023 - Fix End   */
    }
#endif

#if  defined(SCCP_ITU) || defined(SCCP_JAPANESE)
	if(COMPARE_ITU || COMPARE_JAPANESE)
	{
		*p_pc = p_api[SS7_SM_DISPLAY_SS_OFFSET];
		*p_pc |= p_api[SS7_SM_DISPLAY_SS_OFFSET+1]<<8;
	}
#endif

	return SS7_SUCCESS;

}

/* SPR 7490 : End Fix */
