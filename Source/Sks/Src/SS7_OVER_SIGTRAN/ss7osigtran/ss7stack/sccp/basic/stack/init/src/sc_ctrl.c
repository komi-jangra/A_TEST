/***************************************************************************
**  FILE NAME:
**      sc_ctrl.c
**
****************************************************************************
**
**  FUNCTION:
**      This file contains functions which control the execution of SCCP. There is only one ctrl command viz. SS7_ACTIVATE_MODULE
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  26Aug2001  Pawanish Modi   -----  Original
**  13Mar2002  Sachin Bhatia  -----  Added Init API from SME
**  12Mar2002  Sachin Bhatia  -----  Added De-init APi from SME
**  26Aug2001  Pawanish Modi  -----  Original
**  06Mar2002  Prateek Bidwalkar      Fixed SPR # 8573
**  23Jul2002  Suyash Tripathi        Fixed SPR # 9302
**  08Oct2002  Suyash Tripathi        Fixed SPR # 10231
**  24Feb2004  Hitesh Sharma          Fixed SPR # 13263
**
**  Copyright 2001, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"
#include "sc_smapi.h"
#include "sc_reg.h"
#ifdef DISTRIBUTED_SCCP
#include "dsccp_proc.h"
#endif


/* SPR 9302 - Fix Start */
/** Prototypes already present in sc_stpro.h **/
/*void sccp_ctrl_handle_sm_cmd
	            _ARGS_((U8bit *p_api));

void sccp_ctrl_sm_cmd_resp (U8bit *p_api, return_t ret_val, U8bit param, Boolean put_param, error_t  ecode);*/
/* SPR 9302 - Fix End   */

/*****************************************************************************
**      FUNCTION :
**         sccp_ctrl_handle_sm_cmd
******************************************************************************
**
**      DESCRIPTION :
**	Handles the DSCCP_SM_ACTIVATE_INSTANCE command from the SM
**
*****************************************************************************/

void
sccp_ctrl_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit *p_api;
#endif
{
	U8bit cmd;
	return_t ret_val = SS7_FAILURE;
	U8bit param = 0; Boolean put_param = SS7_FALSE;
	error_t ecode=0;

	cmd = GET_SM_CMD(p_api);

	SC_A_TRC (("SCCP::INIT:SM category CTRL\n"));

	switch (cmd)
	{
		case SCCP_SM_ACTIVATE_INSTANCE:
                        SC_A_TRC (("SCCP::INIT: ACtivate module received\n"));
                        ret_val = sccp_handle_sm_activate_instance(&ecode);
                        break;
		case SCCP_SM_INIT_INSTANCE:
						SC_A_TRC (("SCCP::INIT: Init API received\n"));
                        ret_val = sccp_handle_sm_init_instance(p_api, &ecode);
                        break;
		case SCCP_SM_DEINIT_INSTANCE:
						SC_A_TRC (("SCCP::INIT: De-Init API received\n"));
                        ret_val = sccp_handle_sm_deinit_instance(&ecode);
                        break;
		default:
                  SC_A_TRC (("SCCP::INIT: Unknown Control command\n"));
			ret_val = SS7_FAILURE;
			break;
	}
	sccp_ctrl_sm_cmd_resp(p_api, ret_val, param, put_param, ecode);	
	return;
}

/*****************************************************************************
**      FUNCTION :
**        sccp_handle_sm_activate_instance
******************************************************************************
**
**      DESCRIPTION :
**		When DSCCP_SM_ACTIVATE_INSTANCE is received from SM, send config
**	      requests to the mates
**
**      NOTE :
**
*****************************************************************************/
return_t
sccp_handle_sm_activate_instance
#ifdef ANSI_PROTO
	(error_t *p_ecode)
#else
	(p_ecode)
	error_t *p_ecode;
#endif
{
	return_t ret_val = SS7_SUCCESS;

#ifdef DISTRIBUTED_SCCP

/* SPR 10231 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	{
		extern U8bit sccp_redn_sub_state;
		if (sccp_redn_sub_state == ACTIVE)
#endif
/* SPR 10231 - Fix End   */
			ret_val = dsccp_send_conf_request_to_mate (p_ecode);

/* SPR 10231 - Fix Start */
 #ifdef SCCP_REDN_ENABLED
		else 
			return SS7_FAILURE; 
	}
#endif
/* SPR 10231 - Fix End   */

/* SPR # 8573 Fix Start */
	  if(SS7_SUCCESS == ret_val)
	  {
			ret_val = dsccp_comp_mate_info_req(sc_opt.dsccp_local_instance_id);
	  }
/* SPR # 8573 Fix End */

#endif

	return ret_val;
	/* SPR 9302 - Fix Start */
	p_ecode = 0;
	/* SPR 9302 - Fix End   */
}

/*****************************************************************************
**      FUNCTION :
**        sccp_handle_sm_deinit_instance
******************************************************************************
**
**      DESCRIPTION :
**      When DSCCP_SM_DEINIT_INSTANCE is received from SM,
**		All Users are deregistered and Stack status is Non-Alive
**
**      NOTE :
**
*****************************************************************************/
return_t
sccp_handle_sm_deinit_instance
#ifdef ANSI_PROTO
    (error_t *p_ecode)
#else
    (p_ecode)
    error_t *p_ecode;
#endif
{
    return_t ret_val = SS7_SUCCESS;
	
	/* Call the Function which is used to handle this API */
	ret_val = sccp_deinit(p_ecode);
    return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**        sccp_handle_sm_init_instance
******************************************************************************
**
**      DESCRIPTION :
**      When DSCCP_SM_INIT_INSTANCE is received from SM,
**
**
**      NOTE :
**
*****************************************************************************/
return_t
sccp_handle_sm_init_instance
#ifdef ANSI_PROTO
    (U8bit * p_api, error_t *p_ecode)
#else
    (p_api, p_ecode)
	U8bit * p_api;
    error_t *p_ecode;
#endif
{
    return_t ret_val = SS7_SUCCESS;
	/* Start SPR No : 13263 start */
	sc_init_opt_t       sccp_init_param = {0};
	/* Start SPR No : 13263 stop */
	U8bit * p_elem;
	/* Fix for SPR No: 13263 start */
	U32bit tmp_value = 0;
        U16bit api_len =0;

        api_len = GET_API_LEN(p_api) ;

	/* Fix for SPR No: 13263 start */


	/* SPR 10843 - Fix Start */	
	/* Parse the parameters here */
	/*p_elem = p_api + SS7_SM_API_MIN_LEN - 1;*/
	p_elem = p_api + SS7_SM_API_MIN_LEN ;
	/* SPR 10843 - Fix End  */	

/* Added by Amaresh start for SCCP_INIT Configuration */
								tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_sp = tmp_value ;
                p_elem += 4;
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_ss = tmp_value ;
                p_elem += 4;
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_css = tmp_value ;
                p_elem += 4;
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_csp = tmp_value ;
                p_elem += 4;
							  sccp_init_param.standard = (U8bit)(*p_elem);

/* Added by Amaresh stop for SCCP_INIT Configuration */

#if 0
	/* Fill The Init Options Here */
	sccp_init_param.standard = (U8bit)(*p_elem);

	/* Fix for SPR No: 13263 start */
        /* Check if the the api buffer  has 2 * SIZEOF_SS_ID_T + 2 * SIZEOF_SP_ID_T *
        *  more bytes. These bytes will contain the value of Max SS,SP,CSS,CSP . If *
        *  these values are present then get them and insert them in the structure  */

        if((p_elem + (2 * SIZEOF_SS_ID_T) + (2 * SIZEOF_SP_ID_T))  == (p_api + api_len))
        {
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_ss = tmp_value ;
                p_elem += 4;
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_sp = tmp_value ;
                p_elem += 4;
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_css = tmp_value ;
                p_elem += 4;
                tmp_value = GET_4_BYTE_LE(p_elem);
                if(tmp_value != 0)
                        sccp_init_param.max_csp = tmp_value ;
                p_elem += 4;
        }
	/* Fix for SPR No: 13263 end */

#endif /* Commented by Amaresh Original code */


    /* Call the Function which is used to handle this API */
    ret_val = sccp_init(&sccp_init_param, p_ecode);
    return ret_val;
}


/*****************************************************************************
**      FUNCTION :
**        sends response to a SM, PROV command
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_ctrl_sm_cmd_resp
#ifdef ANSI_PROTO
      (U8bit            *p_api,
       return_t   ret_val,
       U8bit            param,
       Boolean    put_param,
       error_t    ecode)
#else
      (p_api, ret_val, param, put_param, ecode)
       U8bit            *p_api;
       return_t   ret_val;
       U8bit            param;
       Boolean    put_param;
       error_t    ecode;
#endif
{
      sccp_sm_cmd_std_resp (p_api, ret_val, param, put_param, ecode);
}
