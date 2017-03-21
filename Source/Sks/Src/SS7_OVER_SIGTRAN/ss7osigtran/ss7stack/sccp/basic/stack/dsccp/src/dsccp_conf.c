/***************************************************************************
**
**  FILE NAME:
**      dsccp_conf.c
**
****************************************************************************
**
**  FUNCTION:
**		Contains functions related to configuration request from a mate SCCP instance which is coming up
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24August 2001 Pawanish Modi            Original
**  24October2001 Prateek Bidwalkar        Fixed SPR 6750
**  05November2001 Pawanish Modi        Added new stats for DSCCP
**  06March2002 Sachin Bhatia        	Fixed SPR 8574
**  18Jun2002   Suyash Tripathi      	Fixed SPR 8985
**  19March2002 Salil Agrawal           Fixed SPR 8923 
**  18Sep2002   Suyash Tripathi      	Fixed SPR 10234
**  Copyright 2001, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#ifdef DISTRIBUTED_SCCP

#include "dsccp.h"
#include "sc_timer.h"
#include "dsccp_proc.h"
#include "sc_reg.h"
#ifdef DSCCP_STATS_ENABLED
#include "dsccp_stats.h"
#endif


/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_conf_request_msg  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_mesg when a 
**    conf request message from mate is received. When a DSCCP instance comes up it sends configuration request to its mate instances for its database updation
** When a configuration req is received, the status of all configured SP, SS
** registered users and all the DSCCP instances is sent to the instance
** which is coming up. This configuration response is sent only by the logical
** manager.
**
**      NOTE :
**
***************************************************************************/

timer_id_t dsccp_conf_timer_id;
timer_id_t dsccp_class1_buffer_timer_id;
Boolean dsccp_conf_timer_running  = SS7_FALSE;


return_t 
dsccp_handle_conf_request_msg
#ifdef ANSI_PROTO
	(dsccp_instance_id_t instance_id, error_t *p_ecode)
#else
	(instance_id,p_ecode)
	dsccp_instance_id_t instance_id;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
	U8bit *p_elem;
	return_t ret_val;
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];

	dsccp_instance_status_tbl[instance_id] = DSCCP_INSTANCE_STATUS_CONFIG;

	if(dsccp_i_am_manager() == SS7_FALSE)
		return SS7_SUCCESS;

      ret_val = dsccp_build_and_send_sp_conf_info(instance_id, p_ecode);

	if(ret_val == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

      ret_val = dsccp_build_and_send_ss_conf_info(instance_id, p_ecode);

	if(ret_val == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

      ret_val = dsccp_build_and_send_reg_conf_info(instance_id, p_ecode);

	if(ret_val == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

      ret_val = dsccp_build_and_send_instance_status_conf_info(instance_id, p_ecode);

	if(ret_val == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

/** After sending the SS, SP , registered users and instance status config info
send a config end message **/

      p_buffer = (U8bit *)sccp_malloc(DSCCP_CONF_END_MSG_LEN);

	if(p_buffer == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

      sccp_fill_api_header(p_buffer, DSCCP_MATE_API, DSCCP_CONF_END_NELEM, DSCCP_CONF_END_MSG_LEN);

	p_elem = p_buffer + API_HEADER_LEN;

	*p_elem++ = DSCCP_API_CAT_CONFIG;	

	*p_elem = DSCCP_API_CMD_CONFIG_END;	

      ret_val = dsccp_send_to_mate( p_buffer, DSCCP_CONF_END_MSG_LEN,instance_id, p_ecode);

	if(ret_val == SS7_FAILURE)
	{
	   /* increment the error out api to mate */
#ifdef DSCCP_STATS_ENABLED
	   DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
	   return SS7_FAILURE;
	}

	   /* Increment the out api */
#ifdef DSCCP_STATS_ENABLED
	   DSC_STAT_API_INR_OUT_API_MATE();	
#endif

	return ret_val;
}



/***************************************************************************
**
**      FUNCTION :
**      dsccp_build_and_send_sp_conf_info  
**       
****************************************************************************
**
**      DESCRIPTION : This function sends sp status info to mate SCCP which is coming up. This is sent in response to a config req from a mate instance
**
**      NOTE :
**
***************************************************************************/


return_t
dsccp_build_and_send_sp_conf_info
#ifdef ANSI_PROTO
	(dsccp_instance_id_t instance_id, error_t *p_ecode)
#else
	(instance_id,p_ecode)
	dsccp_instance_id_t instance_id;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
      U8bit *p_elem;
      U16bit api_len;
      U32bit i;
      U8bit num_entries = 0;
	U8bit ret_val;
		
	p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
	if(p_buffer == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
      api_len = 8;
      p_elem = p_buffer + 8;

       /** Configuration response is sent only by the manager. The manager is
				 the lowest numbered active instance id */
	if(dsccp_i_am_manager() == SS7_TRUE)
      {
            for(i = 0; i < MAX_SP; i++)
            {
                  if(sccp_db.sp[i].conf_status == SC_CONFIGURED)
                  {
                        api_len = api_len + 11;
                        if(api_len <= DSCCP_MAX_DATA_LEN)
                        {
                              *p_elem++ = (U8bit)i;
                              *p_elem++ = (U8bit)(i >> 8);
					*p_elem++ = (U8bit)(i >> 16);
                              *p_elem++ = (U8bit)(i >> 24);
                              *p_elem++ = sccp_db.sp[i].allowed;
                              *p_elem++ = sccp_db.sp[i].upu_received;
                              *p_elem++ = sccp_db.sp[i].upu_cause;
                              *p_elem++ = (U8bit)sccp_db.sp[i].rl;
                              *p_elem++ = (U8bit)sccp_db.sp[i].rsl;
                              *p_elem++ = (U8bit)sccp_db.sp[i].cls;
                              if(api_len == DSCCP_MAX_DATA_LEN)
                                    *p_elem = (U8bit)sccp_db.sp[i].ril;
                              else
                                    *p_elem++ = (U8bit)sccp_db.sp[i].ril;
                              num_entries++;
                        }
                        else
                        {
				sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_SP_CONF_RES_MSG_NELEM,api_len);
					p_buffer[DSCCP_CAT_OFFSET] = DSCCP_API_CAT_CONFIG;

                              p_buffer[DSCCP_CMD_OFFSET] = DSCCP_API_CMD_CONFIG_SP_INFO;
                              p_buffer[DSCCP_DATA_OFFSET] = num_entries;

                              ret_val = dsccp_send_to_mate( p_buffer, api_len,instance_id, p_ecode);

					if(ret_val == SS7_FAILURE)
					{
						/* increment error api mate api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
						return SS7_FAILURE;
					}

						/* increment out api mate api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif

                              p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
					if(p_buffer == SS7_NULL)
					{
						*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
						return SS7_FAILURE;
					}
                              api_len = 8;
                              num_entries = 0;
                              p_elem = p_buffer + 8;
                              *p_elem++ = (U8bit)i;
                              *p_elem++ = (U8bit)(i >> 8);
                              *p_elem++ = (U8bit)(i >> 16);
                              *p_elem++ = (U8bit)(i >> 24);
                              *p_elem++ = sccp_db.sp[i].allowed;
                              *p_elem++ = sccp_db.sp[i].upu_received;
                              *p_elem++ = sccp_db.sp[i].upu_cause;
                              *p_elem++ = (U8bit)sccp_db.sp[i].rl;
                              *p_elem++ = (U8bit)sccp_db.sp[i].rsl;
                              *p_elem++ = (U8bit)sccp_db.sp[i].cls;
                              *p_elem++ = (U8bit)sccp_db.sp[i].ril;
                              num_entries++;
                              api_len = api_len + 11;
                        }
			} /* end if SC_CONFIGURED */
            }  /* end for loop */

	/* This check is required in case the control never reaches the else 
	part in the for loop */

            if(api_len > 8)
            {
                  sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_SP_CONF_RES_MSG_NELEM,api_len);

                  p_buffer[DSCCP_CAT_OFFSET] = DSCCP_API_CAT_CONFIG;

                  p_buffer[DSCCP_CMD_OFFSET] = DSCCP_API_CMD_CONFIG_SP_INFO;

                  p_buffer[DSCCP_DATA_OFFSET] = num_entries;

                  ret_val = dsccp_send_to_mate( p_buffer, api_len, instance_id, p_ecode);

			  	  if(ret_val == SS7_FAILURE)
				  {
						/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
						return SS7_FAILURE;
				  }

				  /* increment the out api mate*/
#ifdef DSCCP_STATS_ENABLED
				  DSC_STAT_API_INR_OUT_API_MATE();
#endif

            }
            else
            {
                  sccp_free(p_buffer);
            }
      }
	else
	{
      	sccp_free(p_buffer);
	}
	return ret_val;
}
	



/***************************************************************************
**
**      FUNCTION :
**      dsccp_build_and_send_ss_conf_info  
**       
****************************************************************************
**
**      DESCRIPTION : This function sends ss status info to mate SCCP which is coming up. It is sent in response to a config request from a mate instance . Response is sent only by manager
**
**      NOTE :
**
***************************************************************************/

return_t 
dsccp_build_and_send_ss_conf_info
#ifdef ANSI_PROTO
	(dsccp_instance_id_t instance_id, error_t *p_ecode)
#else
	(instance_id, p_ecode)
	dsccp_instance_id_t instance_id;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
      U8bit *p_elem;
      U16bit api_len;
      U32bit i;
      U8bit num_entries = 0;
	return_t ret_val;

      p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
	if(p_buffer == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
      api_len = 8;
      p_elem = p_buffer + DSCCP_DATA_OFFSET +1;

       /** Configuration response is sent only by the manager. The manager is
				 the lowest numbered active instance id */

      if(dsccp_i_am_manager() == SS7_TRUE)
      {
            for(i = 0; i < MAX_SS; i++)
            {
                  if(sccp_db.ss[i].conf_status == SC_CONFIGURED)
                  {
                        api_len = api_len + 6 ;
                        if(api_len <= DSCCP_MAX_DATA_LEN) 
                        {
                              *p_elem++ = (U8bit)i;
                              *p_elem++ = (U8bit)(i >> 8);
                              *p_elem++ = (U8bit)(i >> 16);
					*p_elem++ = (U8bit)(i >> 24);
                              *p_elem++ = sccp_db.ss[i].allowed;
                              if(api_len == DSCCP_MAX_DATA_LEN)
                                    *p_elem = sccp_db.ss[i].sst_instance_id;
                              else
                                    *p_elem++ = sccp_db.ss[i].sst_instance_id;

                              num_entries++;
                        }
				else
                        {
                              sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_SP_CONF_RES_MSG_NELEM,api_len);
                              p_buffer[DSCCP_CAT_OFFSET] = DSCCP_API_CAT_CONFIG;
                              p_buffer[DSCCP_CMD_OFFSET] = DSCCP_API_CMD_CONFIG_SS_INFO;
                              p_buffer[DSCCP_DATA_OFFSET] = num_entries;
                              ret_val = dsccp_send_to_mate(p_buffer, api_len, instance_id, p_ecode);
					if(ret_val == SS7_FAILURE)
					{
						/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
						return SS7_FAILURE;
					}

					/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
					DSC_STAT_API_INR_OUT_API_MATE();
#endif

                              p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
					if(p_buffer == SS7_NULL)
					{
						*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
						return SS7_FAILURE;
					}
                              api_len = 8;
                              num_entries = 0;
                              p_elem = p_buffer + 8;
                              *p_elem++ = (U8bit)i;
                              *p_elem++ = (U8bit)(i >> 8);
                              *p_elem++ = (U8bit)(i >> 16);
					*p_elem++ = (U8bit)(i >> 24);
                              *p_elem++ = sccp_db.ss[i].allowed;
                              *p_elem++ = sccp_db.ss[i].sst_instance_id;
                              num_entries++;
                              api_len = api_len + 6 ;
                        }
                  } /* end if SC_CONFIGURED */
		} /* end for loop */

	/* This check is required in case the control never reaches the else 
	part in the for loop */

		if(api_len > 8)
           	{
                 	sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_SS_CONF_RES_MSG_NELEM,api_len);
                  p_buffer[5] = DSCCP_API_CAT_CONFIG;
                  p_buffer[6] = DSCCP_API_CMD_CONFIG_SS_INFO;
                 	p_buffer[7] = num_entries;
                 	ret_val = dsccp_send_to_mate(p_buffer, api_len,instance_id, p_ecode);
					if(ret_val == SS7_FAILURE)
					{
						/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
						return SS7_FAILURE;
					}

						/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif

           	}
           	else
           	{
                 	sccp_free(p_buffer);
           	}
      }
	else
	{
      	sccp_free(p_buffer);
	}
	return ret_val;

}
/***************************************************************************
**
**      FUNCTION :
**      dsccp_build_and_send_reg_conf_info  
**       
****************************************************************************
**
**      DESCRIPTION : This function sends registered users' status info to mate SCCP which is coming up. It is sent in response to a config request
** from the mate. The response is sent only by the manager. The manager is the  ** lowest numbered active instance id
**
**      NOTE :
**
***************************************************************************/


return_t
dsccp_build_and_send_reg_conf_info
#ifdef ANSI_PROTO
	(dsccp_instance_id_t instance_id, error_t *p_ecode)
#else
	(instance_id, p_ecode)
	dsccp_instance_id_t instance_id;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
      U8bit *p_elem;
      U16bit api_len;
      U32bit i;
      U8bit num_entries = 0;
	U32bit sp_id = 0;
	return_t ret_val;
	extern sc_reg_entry_t sccp_reg_table[MAX_LOCAL_USERS];

      p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
	if(p_buffer == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
      api_len = 8;
      p_elem = p_buffer + DSCCP_DATA_OFFSET + 1;
      if(dsccp_i_am_manager() == SS7_TRUE)
      {
            for(i = 0; i < MAX_LOCAL_USERS; i++)
            {
                  if(sccp_reg_table[i].registered == SS7_TRUE)
                  {
                        api_len = api_len + 7;
                        if(api_len <= DSCCP_MAX_DATA_LEN)
                        {
					sp_id = 0;
					sp_id = (U32bit)(sccp_reg_table[i].p_ss->sp_id);
                              *p_elem++ = (U8bit)sp_id;
                              *p_elem++ = (U8bit)(sp_id >> 8);
                              *p_elem++ = (U8bit)(sp_id >> 16);
					*p_elem++ = (U8bit)(sp_id >> 24);
                              *p_elem++ = sccp_reg_table[i].ssn;
					*p_elem++ = (U8bit)sccp_reg_table[i].uid;
                              if(api_len == DSCCP_MAX_DATA_LEN)
						*p_elem = (U8bit)(sccp_reg_table[i].uid >> 8);
					else
						*p_elem++ = (U8bit)(sccp_reg_table[i].uid >> 8);
                              num_entries++;
				}
				else
                        {
                              sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_REG_CONF_RES_MSG_NELEM,api_len);
                              p_buffer[DSCCP_CAT_OFFSET] = DSCCP_API_CAT_CONFIG;
                              p_buffer[DSCCP_CMD_OFFSET] = DSCCP_API_CMD_CONFIG_REG_INFO;
                              p_buffer[DSCCP_DATA_OFFSET] = num_entries;
                              ret_val = dsccp_send_to_mate(p_buffer, 
											api_len ,instance_id, p_ecode);
							  if(ret_val == SS7_FAILURE)
							  {
									/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
									DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
							  	return SS7_FAILURE;
							  }

									/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
									DSC_STAT_API_INR_OUT_API_MATE();
#endif

                              p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
					if(p_buffer == SS7_NULL)
					{
						*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
						return SS7_FAILURE;
					}
                              api_len = 8;
                              num_entries = 0;
                              p_elem = p_buffer + 8;
					sp_id = 0;
					sp_id = (U32bit)(sccp_reg_table[i].p_ss->sp_id);
                              *p_elem++ = (U8bit)sp_id;
                              *p_elem++ = (U8bit)(sp_id >> 8);
                              *p_elem++ = (U8bit)(sp_id >> 16);
					*p_elem++ = (U8bit)(sp_id >> 24);
                              *p_elem++ = sccp_reg_table[i].ssn;
					*p_elem++ = (U8bit)sccp_reg_table[i].uid;
					*p_elem++ = (U8bit)(sccp_reg_table[i].uid >> 8);
                              num_entries++;
                              api_len = api_len + 7 ;
                        }
			} /* end  if SC_CONFIGURED */
		} /* end for loop */

	/* This check is required in case the control never reaches the else 
	part in the for loop */

		if(api_len > 8)
           	{
                 	sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_REG_CONF_RES_MSG_NELEM,api_len);
                  p_buffer[5] = DSCCP_API_CAT_CONFIG;
                  p_buffer[6] = DSCCP_API_CMD_CONFIG_REG_INFO;
                 	p_buffer[7] = num_entries;
                 	ret_val = dsccp_send_to_mate( p_buffer, api_len, instance_id,p_ecode);
					if(ret_val == SS7_FAILURE)
					{
						/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
						return SS7_FAILURE;
					}

						/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif

           	}
           	else
           	{
                 	sccp_free(p_buffer);
           	}
      }
	else
	{
           	sccp_free(p_buffer);
	}
	return ret_val;

}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_send_conf_request_to_mate  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called to broadcast a conf req to all mate SCCP instances when an instance comes up. A timer is started after sending the request.
**
**      NOTE :
**
***************************************************************************/
return_t
dsccp_send_conf_request_to_mate
#ifdef ANSI_PROTO
	(error_t *p_ecode)
#else
	(p_ecode)
	error_t *p_ecode
#endif
{
	return_t ret_val;
      U8bit *p_api;
/* SPR 8985 - Fix Start */
#if 0
	U8bit *p_buffer;
#endif
/* SPR 8985 - Fix End */
      U16bit api_len;
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
	U8bit conf_timer_buf[DSCCP_CONF_TIMER_BUF_LEN], *p_tmr_buf = conf_timer_buf;

      api_len = DSCCP_CONF_REQUEST_MSG_LEN;

      p_api = (U8bit *)sccp_malloc(api_len);
	if (p_api == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] = 
				DSCCP_INSTANCE_STATUS_CONFIG;
    /* spr # 8923 starts */
#ifdef SCCP_REDN_ENABLED
    {
        extern U8bit sccp_redn_sub_state;
        if (sccp_redn_sub_state == ACTIVE)
        {
            ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_CONFIG | 0x40, SCCP_MODULE_ID);
        }
        else
        {
            if (sccp_redn_sub_state == STACK_STANDBY)
            {
                ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_CONFIG | 0x80, SCCP_MODULE_ID);
            }
            else 
                ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_CONFIG, SCCP_MODULE_ID);
        }

    }

#else
	ret_val = dsccp_notify_self_status(
				DSCCP_INSTANCE_STATUS_CONFIG, SCCP_MODULE_ID);
#endif 
    /* spr # 8923 ends */
      dsccp_build_conf_status_request_api(p_api,api_len);

      ret_val = dsccp_forced_broadcast_to_mates(p_api,api_len,p_ecode);

	if(ret_val == SS7_FAILURE)
		return SS7_FAILURE;


	*p_tmr_buf++ = T_DSCCP_CONF_TIMER_ID;

	*p_tmr_buf = sc_opt.dsccp_local_instance_id;

	if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CONFIG_TIMER_MIN_VAL, conf_timer_buf, 2, &dsccp_conf_timer_id))
	{
		dsccp_conf_timer_running  = SS7_TRUE;
		return SS7_SUCCESS;
	}
	else
	{
		*p_ecode = ESS7_FAILURE_TO_START_TIMER;
		return SS7_FAILURE;
	}
/* SPR FIX 7890 starts */
/*	return SS7_SUCCESS; */
/*SPR FIX 7890 ends */
}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_build_conf_status_request_api  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from 
**       dsccp_send_conf_request_to_mate . It builds a conf request message
**
**      NOTE :
**
***************************************************************************/

void
dsccp_build_conf_status_request_api
#ifdef ANSI_PROTO
	(U8bit *p_api, U16bit api_len)
#else
	(p_api, api_len)
	U8bit *p_api;
	U16bit api_len;
#endif
{
	
      U8bit *p_elem;

      sccp_fill_api_header(p_api, DSCCP_MATE_API, DSCCP_CONF_REQUEST_MSG_NELEM, api_len);

      p_elem = p_api + API_HEADER_LEN;

      *p_elem++ = DSCCP_API_CAT_CONFIG;

      *p_elem++ = DSCCP_API_CMD_CONFIG_REQ;

      *p_elem = sc_opt.dsccp_local_instance_id;
}
	
/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_config_sp_info  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called when a sp configuration message is received from a mate SCCP instance. This message is received in response to a config request message.
**
**      NOTE :
**
***************************************************************************/
void
dsccp_handle_config_sp_info  
#ifdef ANSI_PROTO	
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_elem;
	sp_entry_t *p_sp;
	U32bit temp;
	sp_id_t sp_id;
	U8bit num_entries, count = 0 ;
	U8bit status;
	U8bit upu_cause, upu_received;
	S8bit rl, rsl, cls, ril;

	num_entries = p_api[DSCCP_DATA_OFFSET];

	p_elem = p_api+DSCCP_DATA_OFFSET+1;

	while(count < num_entries)
	{

		temp = (*p_elem)| (*(p_elem+1) << 8) | (*(p_elem+2) << 16) | (*(p_elem +3) << 24);
		p_elem += 4;

		sp_id = (sp_id_t)temp;

		p_sp = GET_SP_FROM_ID(sp_id);

		status = (U8bit)*p_elem++; 

		upu_received = (U8bit)*p_elem++; 

		upu_cause = (U8bit)*p_elem++; 

		rl = (S8bit )*p_elem++;

		rsl = (S8bit )*p_elem++;

		cls = (S8bit )*p_elem++;

		ril = (S8bit )*p_elem++;

		p_sp->allowed = status;	

		p_sp->upu_received = upu_received;

		p_sp->upu_cause = upu_cause;

		p_sp->rl = rl;

		p_sp->rsl = rsl;
		p_sp->cls = cls;

		p_sp->ril = ril;

		count++;
	}
	if(count != num_entries)
	{
		*p_ecode = EAPI_ERROR;
		/* increment the error api stats */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
	}
}


/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_config_ss_info  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called when a ss configuration message is received from a mate SCCP instance
**
**      NOTE :
**
***************************************************************************/
void
dsccp_handle_config_ss_info  
#ifdef ANSI_PROTO	
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_elem;
	ss_entry_t *p_ss;
	U32bit temp;
	ss_id_t ss_id;
	U8bit num_entries, count = 0 ;
	U8bit status;
	dsccp_instance_id_t instance_id;

	num_entries = p_api[DSCCP_DATA_OFFSET];

	p_elem = p_api+DSCCP_DATA_OFFSET+1;

	while(count < num_entries)
	{
		temp = (*p_elem)| (*(p_elem+1) << 8) | (*(p_elem+2) << 16) | (*(p_elem +3) << 24);

		p_elem += 4;

		status = (U8bit )*p_elem++;

		instance_id = (U8bit )*p_elem++;

		ss_id = (ss_id_t)temp;

		p_ss = GET_SS_FROM_ID(ss_id);

		p_ss->allowed = status;

		p_ss->sst_instance_id = instance_id;

		count++;
	}
	if(count != num_entries)
	{
		*p_ecode = EAPI_ERROR;
		/* increment the error api stats */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
	}
}


/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_config_reg_info  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called when a register ss configuration message is received from a mate SCCP instance
**
**      NOTE :
**
***************************************************************************/
void
dsccp_handle_config_reg_info  
#ifdef ANSI_PROTO	
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api,p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_elem;
	ss_entry_t *p_ss;
	sp_entry_t *p_sp;
	U32bit temp;
	sp_id_t sp_id;
	U8bit count, num_entries, num_count = 0 ;
	Boolean found = SS7_FALSE;
	sc_reg_entry_t *p_sccp_reg;
	U8bit ssn;
	U16bit log_user_id;
/* SPR 10234 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
/* SPR 10234 - Fix End   */


	num_entries = p_api[DSCCP_DATA_OFFSET];

	p_elem = p_api+DSCCP_DATA_OFFSET+1;

	while(num_count < num_entries)
	{

		temp = (*p_elem)| (*(p_elem+1) << 8) | (*(p_elem+2) << 16) | (*(p_elem +3) << 24);
		p_elem += 4;

		sp_id = (sp_id_t)temp;

		ssn = *p_elem++ ; 

		log_user_id = GET_2_BYTE_LE(p_elem);

		p_elem += 2;

		p_sp = GET_SP_FROM_ID(sp_id);

		for (count = 0; count < MAX_LOCAL_USERS; count++)
      	{
            	p_sccp_reg = &sccp_reg_table [count] ;

            	if ((p_sccp_reg->uid == log_user_id) && (p_sccp_reg->registered == SS7_TRUE))
            	{
                  	if (p_sccp_reg->ssn == ssn)
                  	{
                        	MG_TRC(("SCCP::SCMG: " "User LogUid[%d] already registered with SSN[%d]\n", log_user_id, ssn));
							/* increment the error api stats */
#ifdef DSCCP_STATS_ENABLED
							DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
                        	return;
                  	}
            	}
      	}

/* search for a free entry in the registry table */

		for (count = 0; count < MAX_LOCAL_USERS; count++)
      	{
            	p_sccp_reg = &sccp_reg_table [count] ;

            	if (p_sccp_reg->registered != SS7_TRUE)
            	{
                  	found = SS7_TRUE;
                  	break ;
            	}
      	}


		if (found == SS7_FALSE)
      	{
            	MG_TRC(("SCCP::SCMG: Max Limit reached. Could not register. " "User LogUid[%d] unable to registered with SSN[%d]\n", log_user_id, ssn));
				/* increment the error api stats */
#ifdef DSCCP_STATS_ENABLED
				DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
            	return;
      	}
		if (ssn != 0x00)
      	{
            	if (SS7_NULL == (p_ss = sccp_db_find_ss(p_sp, ssn)))
            	{
                  	MG_TRC(("SCCP :: SCMG : Unequipped user SSN %d PC %d registers ." " ignored\n", ssn,p_sp->pc ));
                  	SC_A_ERR (ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE);
					/* increment the error api stats */
#ifdef DSCCP_STATS_ENABLED
					DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif

                  	return;
            	}
            	p_ss->dst_id = log_user_id;

            	p_ss->registered = SS7_TRUE;
				
				/* SPR # 8574 Fix Start */
				MARK_SS_ALLOWED(p_ss);
				/* SPR 8574 Fix ends */

            	sccp_inform_trans_func (p_sp, p_ss);
      	}
		p_sccp_reg->registered = SS7_TRUE;
      	p_sccp_reg->ssn        = ssn;

      	p_sccp_reg->uid        = log_user_id;

      	p_sccp_reg->p_sp       = p_sp;
      	if (ssn != 0x00)
            	p_sccp_reg->p_ss = p_ss;
      	else
            	p_sccp_reg->p_ss = (ss_entry_t *)SS7_NULL;

      	SCCP_SEND_REG_ENTRY_UPDATE (p_sccp_reg);
		num_count++;
	}
	if(num_count != num_entries)
	{
		*p_ecode = EAPI_ERROR;
		/* increment the error api stats */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_ERR_IN_API_MATE();
#endif
	}
	return;
}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_build_and_send_instance_status_conf_info
**       
****************************************************************************
**
**      DESCRIPTION : This function is called to send status of all the instances to the mate SCCP instance which is coming up. When an instance comes up it
** needs to know which DSCCP instances are active
**
**      NOTE :
**
***************************************************************************/
return_t
dsccp_build_and_send_instance_status_conf_info
#ifdef ANSI_PROTO
	(dsccp_instance_id_t instance_id, error_t *p_ecode)
#else
	(instance_id,p_ecode)
	dsccp_instance_id_t instance_id;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
      U8bit *p_elem;
      U16bit api_len;
      U32bit i;
      U8bit num_entries = 0;
	return_t ret_val;
		


	p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);

	if(p_buffer == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

      api_len = 8;
      p_elem = p_buffer + DSCCP_DATA_OFFSET + 1;

      if(dsccp_i_am_manager() == SS7_TRUE)
      {
		for(i = 0; i < DSCCP_MAX_INSTANCES; i++)
		{
			if(DSCCP_INSTANCE_STATUS_UNCONFIG != dsccp_instance_status_tbl[i])
			{
                        api_len = api_len + 2;

                        if(api_len <= DSCCP_MAX_DATA_LEN)
                        {
					*p_elem++ = (U8bit)i;

                        	if(api_len == DSCCP_MAX_DATA_LEN)

						*p_elem = dsccp_instance_status_tbl[i];
					else
						*p_elem++ = dsccp_instance_status_tbl[i];
					num_entries++;
				}
				else
				{
					sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_INSTANCE_STATUS_CONF_RES_MSG_NELEM, api_len);

					p_buffer[DSCCP_CAT_OFFSET] = DSCCP_API_CAT_CONFIG;
                              p_buffer[DSCCP_CMD_OFFSET] = DSCCP_API_CMD_COMP_MATE_STATUS_INFO;
                              p_buffer[DSCCP_DATA_OFFSET] = num_entries;

                              ret_val = dsccp_send_to_mate(p_buffer, api_len, instance_id, p_ecode);

							  if(ret_val == SS7_FAILURE)
							  {
									/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
									DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
									return SS7_FAILURE;
							  }

									/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
									DSC_STAT_API_INR_OUT_API_MATE();
#endif


                              p_buffer = (U8bit *)sccp_malloc(DSCCP_MAX_DATA_LEN);
					if(p_buffer == SS7_NULL)
					{
						*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
						return SS7_FAILURE;
					}

                              api_len = 8;
                              num_entries = 0;

                              p_elem = p_buffer + 8;

                              *p_elem++ = (U8bit)i;

					*p_elem++ = dsccp_instance_status_tbl[i];
					num_entries++;
                        	api_len = api_len + 2;
				}
			} /* end if SC_CONFIGURED */
		} /* end for loop */
            if(api_len > 8)
            {
                  sccp_fill_api_header(p_buffer,DSCCP_MATE_API, DSCCP_INSTANCE_STATUS_CONF_RES_MSG_NELEM,api_len);

                  p_buffer[DSCCP_CAT_OFFSET] = DSCCP_API_CAT_CONFIG;

                  p_buffer[DSCCP_CMD_OFFSET] = DSCCP_API_CMD_COMP_MATE_STATUS_INFO;
                  p_buffer[DSCCP_DATA_OFFSET] = num_entries;

                  ret_val = dsccp_send_to_mate( p_buffer, api_len,instance_id, p_ecode);

				 if(ret_val == SS7_FAILURE)
				 {
						/* increment the error out api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
						return SS7_FAILURE;
				 }

						/* increment the out mate api */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif

            }
            else
            {
                  sccp_free(p_buffer);
            }
	}
	else
	{
      	sccp_free(p_buffer);
	}
	return SS7_SUCCESS;
}
/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_config_end
**       
****************************************************************************
**
**      DESCRIPTION : This function is called when a config end message is received from  mate DSCCP instance. It sends self status(ALIVE) message to encaps.
**
**
**      NOTE :
**
***************************************************************************/

return_t 
dsccp_handle_config_end
#ifdef ANSI_PROTO
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api,p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
	return_t ret_val;
	U8bit dsccp_class1_timer_buf[DSCCP_CONF_TIMER_BUF_LEN], *p_tmr_buf = dsccp_class1_timer_buf;
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
	extern U8bit dsccp_class1_buff_timer_running;	
	
	/* Dummy line to Avoid a compiler warning */
	p_buffer = p_api;

	if(dsccp_conf_timer_running  == SS7_TRUE)
	{
		sccp_stop_timer(&dsccp_conf_timer_id);
		dsccp_conf_timer_running = SS7_FALSE;
	}		

	dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] = DSCCP_INSTANCE_STATUS_ALIVE;


	*p_tmr_buf++ = T_DSCCP_CLASS1_BUFFER_TIMER_ID;

	*p_tmr_buf = sc_opt.dsccp_local_instance_id;

	if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE, dsccp_class1_timer_buf, 2, &dsccp_class1_buffer_timer_id))
	{
		dsccp_class1_buff_timer_running = SS7_TRUE;
	}
	else
	{
		*p_ecode = ESS7_FAILURE_TO_START_TIMER;
	} 

    /* spr # 8923 starts */
#ifdef SCCP_REDN_ENABLED
    {
        extern U8bit sccp_redn_sub_state;
        if (sccp_redn_sub_state == ACTIVE)
        {
            ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_ALIVE | 0x40, SCCP_MODULE_ID);
        }
        else
        {
            if (sccp_redn_sub_state == STACK_STANDBY)
            {
                ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_ALIVE | 0x80, SCCP_MODULE_ID);
            }
            else 
                ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_ALIVE, SCCP_MODULE_ID);
        }

    }
#else
	ret_val = dsccp_notify_self_status(
			DSCCP_INSTANCE_STATUS_ALIVE,SCCP_MODULE_ID);
#endif
     /* spr # 8923 ends */

    if(ret_val == SS7_SUCCESS)
		return SS7_SUCCESS;
	else
	{
		*p_ecode = ESCCP_UNABLE_TO_NOTIFY_SELF_STATUS;
		return SS7_FAILURE;
	}

}


/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_conf_timeout
**       
****************************************************************************
**
**      DESCRIPTION : This function is called when a config timer expires.
**	  This timer is started when a DSCCP instance sends a config request to
**	  all the mate SCCP instances. It sends self status(ALIVE) message to HM
**
**      NOTE :
**
***************************************************************************/
return_t
dsccp_handle_conf_timeout
#ifdef ANSI_PROTO
	(U8bit *p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
	return_t ret_val;
	U8bit dsccp_class1_timer_buf[DSCCP_CONF_TIMER_BUF_LEN], *p_tmr_buf = dsccp_class1_timer_buf;
	extern U8bit dsccp_class1_buff_timer_running;	
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];
	
	/* Dummy line to Avoid a compiler warning */
	p_buffer = p_api;

	if(dsccp_conf_timer_running  == SS7_TRUE)
	{
		dsccp_conf_timer_running = SS7_FALSE;
	}		

	dsccp_instance_status_tbl[sc_opt.dsccp_local_instance_id] = DSCCP_INSTANCE_STATUS_ALIVE;

	*p_tmr_buf++ = T_DSCCP_CLASS1_BUFFER_TIMER_ID;

	*p_tmr_buf = sc_opt.dsccp_local_instance_id;

	if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE, dsccp_class1_timer_buf, 2, &dsccp_class1_buffer_timer_id))
	{
		dsccp_class1_buff_timer_running = SS7_TRUE;
	}
	else
	{
		*p_ecode = ESS7_FAILURE_TO_START_TIMER;
	}

    /* spr # 8923 starts */
#ifdef SCCP_REDN_ENABLED
    {
        extern U8bit sccp_redn_sub_state;
        if (sccp_redn_sub_state == ACTIVE)
        {
            ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_ALIVE | 0x40, SCCP_MODULE_ID);
        }
        else
        {
            if (sccp_redn_sub_state == STACK_STANDBY)
            {
                ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_ALIVE | 0x80, SCCP_MODULE_ID);
            }
            else 
                ret_val = dsccp_notify_self_status(DSCCP_INSTANCE_STATUS_ALIVE, SCCP_MODULE_ID);
        }

    }
#else
	ret_val = dsccp_notify_self_status(
			DSCCP_INSTANCE_STATUS_ALIVE, SCCP_MODULE_ID);
#endif
 /* spr # 8923 ends */

    if(ret_val == SS7_SUCCESS)
		return SS7_SUCCESS;
	else
	{
		*p_ecode = ESCCP_UNABLE_TO_NOTIFY_SELF_STATUS;
		return SS7_FAILURE;
	}
}


#else /* DISTRIBUTED_SCCP */

/*****************************************************************************
**  This extern declaration is required as ANSI C does not allow an empty 
**  source file. This declaration enables compilation without DISTRIBURTED_SCCP
**  flag .
*****************************************************************************/

extern return_t dsccp_dummy _ARGS_((void));


#endif /* end DISTRIBUTED_SCCP */
