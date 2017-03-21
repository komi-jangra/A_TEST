/***************************************************************************
**
**  FILE NAME:
**      dsccp_hm.c
**
****************************************************************************
**
**  FUNCTION:
**		
**
**  DESCRIPTION: This file contain functions for handling Health Manager APIs
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24August 2001 Pawanish Modi            Original
**  24October2001 Prateek Bidwalkar        Fixed SPR 6750
**  06November2001 Pawanish Modi        Added new stats for DSCCP
**  26December2001 Prateek Bidwalkar    Fixed SPR 7450
**  08October2002 Suyash Tripathi    	Fixed SPR 10277
**  17Jan2003 	Ashish Sawalkar    		Fixed SPR 11097
**  31Jan2003 	Ashish Sawalkar    		Fixed SPR 11101
**  08Sep2003 	Salil Agrawal           Fixed SPR 12318
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
#include "sc_dbf.h"
#include "dsccp_proc.h"
#ifdef DSCCP_STATS_ENABLED
#include "dsccp_stats.h"
#endif
/* SPR # 7450 Fix Start */
#include "sc_reg.h"
/* SPR # 7450 Fix End */

U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];

/* SPR # 7450 Fix Start */
extern	sc_reg_entry_t	sccp_reg_table[MAX_LOCAL_USERS];
extern  U32bit  sccp_co_timer_dur [MAX_SCCP_CO_TIMERS];
/* SPR # 7450 Fix End */

/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_mate_status_change  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_mesg when
**	  a message from health manager regarding the status of a instance is 
**	  received
**
**      NOTE :
**
***************************************************************************/

void 
dsccp_handle_mate_status_change
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	U8bit status;
	U8bit *p_elem;
	dsccp_instance_id_t instance_id;
	U32bit i = 0;
	ss_entry_t *p_ss;
	U8bit dsccp_class1_timer_buf[DSCCP_CONF_TIMER_BUF_LEN], *p_tmr_buf = dsccp_class1_timer_buf;
	U8bit prev_status;
	extern U8bit dsccp_class1_buff_timer_running;
	extern timer_id_t dsccp_class1_buffer_timer_id;
/* SPR # 7450 Fix Start */
	error_t  ecode;
/* SPR # 7450 Fix End */


	p_elem = p_api + DSCCP_DATA_OFFSET;	

	instance_id = *p_elem++;

	status = *p_elem;
	if(instance_id == DSCCP_INVALID_INSTANCE_ID)
		return;
      if(dsccp_instance_status_tbl[instance_id] == status)
		return;

	prev_status = dsccp_instance_status_tbl[instance_id];

/* SPR 10277 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	/* In case of Distribution and Redundancy the code in the else part is not needed */
#else
/* SPR 10277 - Fix End   */
/* SPR # 7450 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
	if(prev_status != DSCCP_INSTANCE_STATUS_DEAD && status ==\
						DSCCP_INSTANCE_STATUS_DEAD)
	{
		dsccp_instance_status_tbl[instance_id] = \
											DSCCP_INSTANCE_STATUS_DEACTIVATED;
		if(SS7_SUCCESS != dsccp_handle_instance_deactivation(instance_id, \
																&ecode))
			return ;
	}
	else if((prev_status >= DSCCP_INSTANCE_STATUS_DEACTIVATED && prev_status\
						 <= DSCCP_INSTANCE_STATUS_REACTIVATED) && status == \
							DSCCP_INSTANCE_STATUS_UNCONFIG)
	{
		dsccp_instance_status_tbl[instance_id] = \
									DSCCP_INSTANCE_STATUS_DEACTIVATED_UNCONFIG;
	}
	else if((prev_status >= DSCCP_INSTANCE_STATUS_DEACTIVATED && prev_status\
						 <= DSCCP_INSTANCE_STATUS_REACTIVATED) && status == \
							DSCCP_INSTANCE_STATUS_CONFIG)
	{
		dsccp_instance_status_tbl[instance_id] = \
									DSCCP_INSTANCE_STATUS_DEACTIVATED_CONFIG;

	}
	else if((prev_status >= DSCCP_INSTANCE_STATUS_DEACTIVATED && prev_status\
						 <= DSCCP_INSTANCE_STATUS_REACTIVATED) && status == \
							DSCCP_INSTANCE_STATUS_ALIVE)
	{
		dsccp_instance_status_tbl[instance_id] = \
											DSCCP_INSTANCE_STATUS_REACTIVATED;

	}
	else
#endif
/* SPR 10277 - Fix Start */
#endif
/* SPR 10277 - Fix End   */
/* SPR # 7450 Fix End */
	dsccp_instance_status_tbl[instance_id] = status;
	
	if(prev_status == DSCCP_INSTANCE_STATUS_UNCONFIG)
		return;
/* SPR # 7450 Fix Start */
	if(prev_status == DSCCP_INSTANCE_STATUS_DEACTIVATED_UNCONFIG)
		return;
/* SPR # 7450 Fix End */
	if(status == DSCCP_INSTANCE_STATUS_ALIVE)
	{
		*p_tmr_buf++ = T_DSCCP_CLASS1_BUFFER_TIMER_ID;
    		*p_tmr_buf = sc_opt.dsccp_local_instance_id;
		if(dsccp_class1_buff_timer_running == SS7_FALSE)
		{
			if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE, dsccp_class1_timer_buf, 2, &dsccp_class1_buffer_timer_id))
    			{
        			dsccp_class1_buff_timer_running = SS7_TRUE;
    			}
    			else
    			{
        			return ;
    			}
		}
		else
		{
			sccp_stop_timer(&dsccp_class1_buffer_timer_id);
			if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE, dsccp_class1_timer_buf, 2, &dsccp_class1_buffer_timer_id))
    			{
        			dsccp_class1_buff_timer_running = SS7_TRUE;
    			}
    			else
    			{
        			return ;
    			}
		}
	}


	if(status == DSCCP_INSTANCE_STATUS_DEAD)
	{
		*p_tmr_buf++ = T_DSCCP_CLASS1_BUFFER_TIMER_ID;
    		*p_tmr_buf = sc_opt.dsccp_local_instance_id;

		if(dsccp_class1_buff_timer_running == SS7_FALSE)
		{
			if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE, dsccp_class1_timer_buf, 2, &dsccp_class1_buffer_timer_id))
    			{
        			dsccp_class1_buff_timer_running = SS7_TRUE;
    			}
    			else
    			{
        			return ;
    			}
		}
		else  /* If timer is already running, restart the timer */
		{
			sccp_stop_timer(&dsccp_class1_buffer_timer_id);
			if (SS7_SUCCESS == sccp_start_timer(DSCCP_T_CLASS1_BUFFER_TIMER_DEF_VALUE, dsccp_class1_timer_buf, 2, &dsccp_class1_buffer_timer_id))
    			{
        			dsccp_class1_buff_timer_running = SS7_TRUE;
    			}
    			else
    			{
        			return ;
    			}
			
		}

		if(dsccp_i_am_manager() == SS7_TRUE)
		{
			for(i = 0; i < MAX_SS; i++)	
			{
				if((sccp_db.ss[i].sst_instance_id == instance_id) && (sccp_db.ss[i].sst_instance_id != DSCCP_INVALID_INSTANCE_ID))
				{
					p_ss = &sccp_db.ss[i];
				
					p_ss->prev_t_stat_info_timer_val = 
						 sc_tim.t_stat_info_start_timer_val;

					sccp_start_sst(p_ss);	
				}
			}
		}
	}
	/* SPR 9302 - Fix Start */
	ecode = 0;
	/* SPR 9302 - Fix End  */
}


/***************************************************************************
**
**      FUNCTION :
**       dsccp_handle_comp_mate_status_info 
**       
****************************************************************************
**
**      DESCRIPTION :This function is called from the dsccp_process_mesg when a 
**      message regarding the status of all the instances  is received
**	  This message can be sent by Health Manager or by a mate instance 
**	  during the configuartion in response to a config request. 
**
**      NOTE :
**
***************************************************************************/

return_t 
dsccp_handle_comp_mate_status_info
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit status;
	U8bit *p_elem;
	dsccp_instance_id_t instance_id;
	U8bit num_entries, count = 0;
	

	num_entries = p_api[DSCCP_DATA_OFFSET];

	p_elem = p_api + DSCCP_DATA_OFFSET + 1;

	while(count < num_entries)
	{
		instance_id = *p_elem++;

		status = *p_elem++;
		
		if(instance_id > DSCCP_MAX_INSTANCES)
		{
			*p_ecode = ESCCP_INVALID_INSTANCE_ID;
			return SS7_FAILURE;
		}

		dsccp_instance_status_tbl[instance_id] = status;

		count++;
	}		
	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**       dsccp_i_am_manager
**      
****************************************************************************
**
**      DESCRIPTION : This function is called  to find out whether local sccp
**      instance is manager or not. A manager is  lowest numbered active SCCP
**	  Instance. 
**
**      NOTE :
**
***************************************************************************/
return_t
dsccp_i_am_manager(void)
{
	U16bit count;
	Boolean found = SS7_FALSE;

	for(count = 0; count < DSCCP_MAX_INSTANCES ; count++)
	{
		if(dsccp_instance_status_tbl[count] == DSCCP_INSTANCE_STATUS_ALIVE)
		{
			found = SS7_TRUE;
			break;
		}
	}
	if(found == SS7_TRUE)
	{
		if(count == sc_opt.dsccp_local_instance_id)
		{
			MG_TRC (("DSCCP:: I AM MANAGER %d %d\n",count, sc_opt.dsccp_local_instance_id));
			return SS7_TRUE;
		}
		else
			return SS7_FALSE;
	}	
	else
		return SS7_FALSE;
}


/***************************************************************************
**
**      FUNCTION :
**       dsccp_broadcast_to_mates
**      
****************************************************************************
**
**      DESCRIPTION : This function is called  to broadcast a  mate API 
**	  message to all mate sccp instances
**
**      NOTE :
**
***************************************************************************/

return_t
dsccp_broadcast_to_mates
#ifdef ANSI_PROTO
	(U8bit *p_api, U16bit api_len,error_t *p_ecode)
#else
	(p_api, api_len, p_ecode)
	U8bit *p_api;
	U16bit api_len;
	error_t *p_ecode;
#endif
{
	U16bit count;
	return_t retval;
	U8bit *p_buffer;
	U8bit prev_alive_inst_id = DSCCP_INVALID_INSTANCE_ID;

      /** dsccp_send_to_mate will free the p_api everytime it is called 
      *** So the buffer needs to be allocated and copied for each 'send' call
      **/
		
	for(count = 0; count < DSCCP_MAX_INSTANCES; count++)
	{
		/* spr 11101 fix : added reactivated state check */
		if((dsccp_instance_status_tbl[count] == DSCCP_INSTANCE_STATUS_ALIVE) ||
		   (dsccp_instance_status_tbl[count] == DSCCP_INSTANCE_STATUS_REACTIVATED))
		{
			if (count != sc_opt.dsccp_local_instance_id)
			{
				if (prev_alive_inst_id != DSCCP_INVALID_INSTANCE_ID)
				{
					p_buffer = (U8bit *)sccp_malloc(api_len);

					if(p_buffer == SS7_NULL)
					{
						*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE; 
						return SS7_FAILURE;
					}

					sccp_memcpy(p_buffer, p_api, api_len);
					retval = dsccp_send_to_mate(p_buffer, 
						api_len, prev_alive_inst_id, p_ecode ); 
					if(SS7_FAILURE == retval)
					{
						/* increment the error api for mate */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
					}
					else
					{
						/* increment the out api for mate */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif
					}
				}
				prev_alive_inst_id = count;
			}
		}
	}

	if (prev_alive_inst_id != DSCCP_INVALID_INSTANCE_ID)
	{
		retval = dsccp_send_to_mate(p_api, 
			api_len, prev_alive_inst_id, p_ecode ); 
					if(SS7_FAILURE == retval)
					{
						/* increment the error api for mate */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
					}
					else
					{
						/* increment the out api for mate */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif
					}
	}
	else
	{
		sccp_free(p_api);
	}

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**       dsccp_forced_broadcast_to_mates
**      
****************************************************************************
**
**      DESCRIPTION : This function is called  to do a forced broadcast 
**	  of config request to mates when a DSCCP instance comes  up.
**	  this is required because when a instance comes up it does not
**	  which instances are alive
**      NOTE :
**
***************************************************************************/

return_t
dsccp_forced_broadcast_to_mates
#ifdef ANSI_PROTO
	(U8bit *p_api, U16bit api_len,error_t *p_ecode)
#else
	(p_api, api_len, p_ecode)
	U8bit *p_api;
	U16bit api_len;
	error_t *p_ecode;
#endif
{
	U16bit count;
	U8bit *p_buffer;

      /** dsccp_send_to_mate will free the p_api everytime it is called 
      *** So the buffer needs to be allocated and copied for each 'send' call
      **/
		
	for(count = 0; count < DSCCP_MAX_INSTANCES - 1; count++)
	{
		if (count != sc_opt.dsccp_local_instance_id)
		{
			p_buffer = (U8bit *)sccp_malloc(api_len);

			if(p_buffer == SS7_NULL)
			{
				*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE; 
				return SS7_FAILURE;
			}

			sccp_memcpy(p_buffer, p_api, api_len);
			if(SS7_FAILURE == dsccp_send_to_mate(p_buffer, 
												 api_len, count, p_ecode))
			{
						/* increment the error api for mate */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
			}
			else
			{
						/* increment the out api for mate */
#ifdef DSCCP_STATS_ENABLED
						DSC_STAT_API_INR_OUT_API_MATE();
#endif
			}
		}
	}
	
	if(SS7_FAILURE == dsccp_send_to_mate(p_api, api_len, DSCCP_MAX_INSTANCES-1,p_ecode))
	{
		/* increment the error api for mate */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_ERR_OUT_API_MATE();
#endif
	}
	else
	{
		/* increment the out api for mate */
#ifdef DSCCP_STATS_ENABLED
		DSC_STAT_API_INR_OUT_API_MATE();
#endif
	}

	return SS7_SUCCESS;
}

/* SPR # 7450 Fix Start */
#ifdef SCCP_INCLUDE_CO_SERVICE
/***************************************************************************
**
**      FUNCTION :
**       dsccp_handle_instance_deactivation
**
****************************************************************************
**
**      DESCRIPTION : This function checks if it is the MANAGER instance, and
**                    if it is then it will start the timer
**                    T_DSCCP_INST_DEACTIVATION_TIMER.
**      NOTE :
**
***************************************************************************/
return_t dsccp_handle_instance_deactivation
#ifdef ANSI_PROTO
		(dsccp_instance_id_t	inst_id,
		 error_t				*p_ecode)
#else
		(inst_id)
		 dsccp_instance_id_t	inst_id;
#endif
{

	U8bit		timer_buf[2];
	timer_id_t 	timer_id;


	timer_buf[0] = T_DSCCP_INST_DEACTIVATION_TIMER_ID;
	timer_buf[1] = inst_id;

	if(SS7_TRUE == dsccp_i_am_manager())
	{
	  	if(SS7_FAILURE == sccp_start_timer(\
								sccp_co_timer_dur[DSCCP_T_DEACTIVATION_TIMER],\
                                timer_buf, 2, &timer_id))
		{
			*p_ecode = ESS7_FAILURE_TO_START_TIMER;
			return SS7_FAILURE;
		}
	  return SS7_SUCCESS;
	}
	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**       dsccp_handle_inst_deactivation_timer_expiry
**
****************************************************************************
**
**      DESCRIPTION : This function is called when DSCCP_INST_DEACTIVATION
**                    timer expires. This function will broadcast a message 
**                    to all other active instances about this timer.
**      NOTE :
**
***************************************************************************/
return_t dsccp_handle_inst_deactivation_timer_expiry
#ifdef ANSI_PROTO
		(U8bit		*p_api,
		 error_t	*p_ecode)
#else
		(p_api, p_ecode)
		 U8bit		*p_api;
		 error_t	*p_ecode;
#endif
{
	dsccp_instance_id_t	inst_id;
	
	inst_id = p_api[API_HEADER_LEN+1];
	dsccp_change_deactivated_inst_status(inst_id);
	if(SS7_FAILURE == dsccp_broadcast_deactivation_timer_expiry \
															(inst_id, p_ecode))
	{
		return SS7_FAILURE;
	}

    /********* INFORM UMR AND DMR **********/
	if(SS7_FAILURE == dsccp_update_umr_and_dmr(inst_id, p_ecode))
	{
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**       dsccp_change_deactivated_inst_status
**
****************************************************************************
**
**      DESCRIPTION : This function changed the state of the given instance
**                    from the DEACTIVATED states to their corresponding 
**                    NORMAL states.
**      NOTE :
**
***************************************************************************/
void dsccp_change_deactivated_inst_status
#ifdef ANSI_PROTO
		(dsccp_instance_id_t	inst_id)
#else
		(inst_id)
		 dsccp_instance_id_t	inst_id;
#endif
{

	switch (dsccp_instance_status_tbl[inst_id])
	{
		case DSCCP_INSTANCE_STATUS_DEACTIVATED:
		{
			dsccp_instance_status_tbl[inst_id] = DSCCP_INSTANCE_STATUS_DEAD;
			break;
		}
		case DSCCP_INSTANCE_STATUS_DEACTIVATED_UNCONFIG:
		{
			dsccp_instance_status_tbl[inst_id] = DSCCP_INSTANCE_STATUS_UNCONFIG;
			break;
		}
		case DSCCP_INSTANCE_STATUS_DEACTIVATED_CONFIG:
		{
			dsccp_instance_status_tbl[inst_id] = DSCCP_INSTANCE_STATUS_CONFIG;
			break;
		}
		case DSCCP_INSTANCE_STATUS_REACTIVATED:
		{
			dsccp_instance_status_tbl[inst_id] = DSCCP_INSTANCE_STATUS_ALIVE;
			break;
		}
/* SPR 7450 fix Start */
#if 0
/* SPR 7450 fix End */
		default:
			dsccp_instance_status_tbl[inst_id] = DSCCP_INSTANCE_STATUS_DEAD;
/* SPR 7450 fix Start */
#endif
/* SPR 7450 fix End */
	}

}

/***************************************************************************
**
**      FUNCTION :
**       dsccp_broadcast_deactivation_timer_expiry
**
****************************************************************************
**
**      DESCRIPTION : This function changed the state of the given instance
**                    from the DEACTIVATED states to their corresponding 
**                    NORMAL states.
**      NOTE :
**
***************************************************************************/
return_t dsccp_broadcast_deactivation_timer_expiry
#ifdef ANSI_PROTO
		(dsccp_instance_id_t	inst_id, error_t	*p_ecode)
#else
		(inst_id, p_ecode)
		 dsccp_instance_id_t	inst_id;
		 error_t				*p_ecode;
#endif
{
	U8bit	*p_api;
	U8bit	api_len, offset;

	api_len = API_HEADER_LEN + 
			  2 +      					/* Category and Command */
			  sizeof(dsccp_instance_id_t);

	/* This buffer will be freed in the function dsccp_forced_broadcast_to_mates
	** so it should not be freed in this function
	*/
	p_api = (U8bit *)sccp_malloc(api_len);
	if(SS7_NULL == p_api)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE; 
		return	SS7_FAILURE;
	}

	sccp_fill_api_header(p_api, DSCCP_MATE_API,
								DSCCP_DEACTIVATED_MATE_STATUS_NELEM,
								api_len);

	offset = API_HEADER_LEN;

	p_api[offset++] = DSCCP_API_CAT_CONFIG;
	p_api[offset++] = DSCCP_API_CMD_DEACTIVATED_MATE_STATUS;
	
	p_api[offset] = inst_id;
	
	if(SS7_FAILURE == dsccp_forced_broadcast_to_mates(p_api, \
												GET_API_LEN(p_api), p_ecode))
	{
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**       dsccp_handle_deacitvated_mate_status
**
****************************************************************************
**
**      DESCRIPTION : This function changed the state of the given instance
**                    from the DEACTIVATED states to their corresponding 
**                    NORMAL states.
**      NOTE :
**
***************************************************************************/
return_t dsccp_handle_deactivated_mate_status
#ifdef ANSI_PROTO
		(U8bit		*p_api,
		 error_t	*p_ecode)
#else
		(inst_id, p_ecode)
		 dsccp_instance_id_t	inst_id;
		 error_t				*p_ecode;
#endif
{
	dsccp_instance_id_t		inst_id;

	inst_id = p_api[API_HEADER_LEN+2];

	dsccp_change_deactivated_inst_status(inst_id);
	
	/***** INFORM THE UMR AND DMR ******/
	if(SS7_FAILURE == dsccp_update_umr_and_dmr(inst_id, p_ecode))
	{
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}


/***************************************************************************
**
**      FUNCTION :
**       dsccp_update_umr_and_dmr
**
****************************************************************************
**
**      DESCRIPTION : This function updates the UMR and DMR libraries
**      NOTE :
**
***************************************************************************/
return_t dsccp_update_umr_and_dmr
#ifdef ANSI_PROTO
		(dsccp_instance_id_t	inst_id,
		 error_t				*p_ecode)
#else
		(inst_id, p_ecode)
		 dsccp_instance_id_t	inst_id;
		 error_t				*p_ecode;
#endif
{
	buffer_t	*p_api;
	buffer_t	*p_buffer;
	U8bit		api_len, offset;
	/* SPR 9302 - Fix Start */
	/*U8bit		count;*/
	/* SPR 9302 - Fix End  */
	error_t		err;

	api_len = API_HEADER_LEN + 
			  2 + 				/* Command and Category */
			  sizeof(dsccp_instance_id_t);
	
	p_api = (buffer_t *)sccp_malloc(api_len);
	/** SPR 8622 fix starts **/
	p_buffer = (buffer_t *)sccp_malloc(api_len);
	if(SS7_NULL == p_api)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	/* spr 12318 starts */
	if(SS7_NULL == p_buffer)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	/* spr 12318 ends */
	sccp_fill_api_header(p_api, DSCCP_UPDATE_API, 
						 DSCCP_UPDATE_DEACTIVATED_MATE_STATUS_NELEM, api_len);

	offset = API_HEADER_LEN;
	
	p_api[offset++] = DSCCP_API_CAT_CONFIG;
	p_api[offset++] = DSCCP_API_CMD_UPDATE_DEACTIVATED_MATE_STATUS;
	p_api[offset]   = inst_id;

	/** SPR # 11097  : Fix **/
	/* Sending the updates to DMR and UMR which have separate id's from 
	 * SCCP User and MTP3. The update need not be sent to SCCP User or
	 * MTP3. Refer to SPR 9968 for additional information.
	 */

#if 0	
** 	/* Send the message to UMR running with MTP3 layer */
** 	sccp_memcpy(p_buffer, p_api, api_len);
** 	sccp_sendto_m3((U8bit *)p_api);
**
** 	/* Send the message to all the registered users */	
** 	for(count=0; count < MAX_LOCAL_USERS; count++)
** 	{
** 		if(sccp_reg_table[count].registered == SS7_TRUE)
** 		{
** 			p_api = (buffer_t *)sccp_malloc(api_len);
** 			sccp_memcpy(p_api, p_buffer, api_len);
** 			sccp_sendto_tc(p_api, sccp_reg_table[count].p_ss);
** 		}
** 	}
** 	sccp_free(p_buffer);
**
#endif	

	sccp_memcpy(p_buffer, p_api, api_len);
	/* Sending to DMR */
	send_from_sccp(p_api, api_len, SCCP_MODULE_ID, SCCP_DMR_ID, &err);	
	/* Sending to UMR */
	send_from_sccp(p_buffer, api_len, SCCP_MODULE_ID, SCCP_UMR_ID, &err);	

	/** SPR 8622 fix ends **/
	/* SPR 11097 - Fix End */

	return SS7_SUCCESS;
}
#endif /* end SCCP_INCLUDE_CO_SERVICE */
/* SPR # 7450 Fix End */
#endif /* end DISTRIBUTED_SCCP */
