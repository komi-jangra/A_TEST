/***************************************************************************
**  FILE NAME:
**      sc_prov.c
**
****************************************************************************
**
**  FUNCTION:
**      This file contains functions which provision the database.
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  08Apr04  Hitesh Sharma		  Fixed SPR 13344  
**  24Feb04  Hitesh Sharma		  Fixed SPR 13263  
**  06Aug03  Hitesh Sharma		  Fixed SPR 12377 ,CSR No: 1-755190 
**  04Jan03  Suyash Tripathi		  Fixed SPR 10853 
**  24Sep02  Ashish Sawalkar		  Fixed SPR 10068 
**  08Aug02  Ashish Sawalkar		  Fixed SPR 9302 
**  14Mar02  Sachin Bhatia            Checked for Stack State
**  09Aug02  Prateek Bidwalkar        Fixed SPR # 9502
**  14Dec01  Ashish Sawalkar          Fixed SPR 7430 
**  05Jun00  Ramu Kandula             Added Get Prov info APIs
**  20Apr99  Sudipta Pattar    -----  Fixed SPR 1503
**  10Feb99  Sudipta Pattar    -----  Fixed SPR 1272
**  10May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"
#include "sc_reg.h"
#include "sc_smapi.h"
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#endif
extern void sccp_config_tmr_var(int type, unsigned long value);
extern int ss7_over_sigtran_log_print(const char *format, ...);
extern int sp_opc,sp_dpc;
extern sccp_deregister(void);
int sccp_deregister_set=0;
int sp_del_count=0,sp_add_count=0,ss_add_count=0,ss_del_count=0;
int sccp_nw_indicator=0;
static return_t sccp_prov_add_sp_to_db
	_ARGS_ ((sc_sp_conf_info_t * p_sp_prov_info, error_t * p_ecode));

static return_t sccp_prov_del_sp_from_db
	_ARGS_ ((sc_sp_del_info_t * p_sp_del_info, error_t * p_ecode));

static return_t sccp_prov_add_ss_to_db
	_ARGS_ ((sc_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode));

static return_t sccp_prov_del_ss_from_db
	_ARGS_ ((sc_ss_del_info_t * p_ss_del_info, error_t * p_ecode));

static return_t sccp_sm_cmd_init_timer
        _ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_conf_sp
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_sp
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_conf_ss
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_ss
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_conf_css
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_css
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_conf_csp
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_csp
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_timer_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_sp_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_ss_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_css_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_csp_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

/* Adding new functios for provisioning Translation functionality
   i.e. the GTT provisioning APIs
   --Sachin Bhatia
*/

static return_t sccp_sm_cmd_add_mtpsap
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_add_trans_rule
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_add_to_dpc_ssn_table
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_mtpsap
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_trans_rule
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_del_from_dpc_ssn_table
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_mtpsap_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_trans_func_list_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

static return_t sccp_sm_cmd_get_rule_list_per_trans_func_info
	_ARGS_ ((U8bit * p_api, error_t * p_ecode));

/* New functions end here --Sachin Bhatia*/

static void sccp_prov_sm_cmd_resp
	_ARGS_ ((U8bit * p_api, return_t ret_val, U8bit param,
	             Boolean put_param, error_t ecode));


#ifdef DISTRIBUTED_SCCP
static return_t dsccp_sm_cmd_prov_comp_mate_status_info
		_ARGS_((U8bit *, error_t *));
#endif
#ifdef BACK_UP_SSN
return_t sccp_handle_add_back_up_ssn(U8bit *p_api);
extern return_t sccp_db_add_back_up_ss(U8bit ssn, pc_t point_code);
#endif

/*****************************************************************************
**      FUNCTION :
**         sccp_prov_get_timer_info
******************************************************************************
**
**      DESCRIPTION :
**			Files the timer_buffer_t array with the current values of timers
**
*****************************************************************************/
 
return_t
sccp_prov_get_timer_info
#ifdef ANSI_PROTO
        (pvoid *p_p_buf, U8bit *p_num_entries, U8bit *p_entry_size, error_t *p_ecode)
#else
        (p_p_buf, p_num_entries, p_entry_size, p_ecode)
		 pvoid 			*p_p_buf,
		 U8bit			*p_num_entries;
		 U8bit			*p_entry_size;
         error_t        *p_ecode;
#endif
{
	tmr_buffer_t		*p_tmp;
	s7_len_t			buf_len;
 	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	p_tmp = SS7_NULL;
	*p_p_buf = SS7_NULL;
	*p_num_entries = SCCP_MAX_TIMER_CONFIG_ID + 1;
	*p_entry_size = sizeof (tmr_buffer_t);
	
	buf_len = (*p_num_entries) * (*p_entry_size);
	if ((p_tmp = (tmr_buffer_t *) (pvoid) sccp_malloc (buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	
	*p_p_buf = (pvoid) p_tmp;

	p_tmp->timer_index = T_A_CONFIG_ID;
	p_tmp->timer_value = sc_tim.t_a_timer_val;
	p_tmp ++;

	p_tmp->timer_index = T_D_CONFIG_ID;
	p_tmp->timer_value = sc_tim.t_d_timer_val;
	p_tmp ++;

	p_tmp->timer_index = T_CON_CONFIG_ID;
	p_tmp->timer_value = sc_tim.t_con_timer_val;
	p_tmp ++;

	p_tmp->timer_index = T_STAT_INFO_START_CONFIG_ID;
	p_tmp->timer_value = sc_tim.t_stat_info_start_timer_val;
	p_tmp ++;

	p_tmp->timer_index = T_STAT_INFO_END_CONFIG_ID;
/* spr fix 9792 starts */
	p_tmp->timer_value = sc_tim.t_stat_info_end_timer_val;
/* spr fix 9792 ends */
	p_tmp ++;

	p_tmp->timer_index = T_REASS_CONFIG_ID;
	p_tmp->timer_value = sc_tim.t_reassmbly_timer_val;
	p_tmp ++;

#ifdef SCCP_INCLUDE_CO_SERVICE

	p_tmp->timer_index = T_CONNEST_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_CONNEST_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_IAS_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_IAS_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_IAR_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_IAR_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_REL_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_REL_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_REPREL_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_REPREL_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_INT_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_INT_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_GAURD_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_GAURD_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_RESET_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_RESET_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

	p_tmp->timer_index = T_FREEZE_CONFIG_ID;
	p_tmp->timer_value = sccp_co_timer_dur [T_FREEZE_CONFIG_ID-T_REASS_CONFIG_ID-1];
	p_tmp ++;

#endif /* #ifdef SCCP_INCLUDE_CO_SERVICE */

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         configure a signaling point in the SCCP network
******************************************************************************
**
**      DESCRIPTION :
**         this function can be called from encapsulating shell to
**         configure a signaling point to the SCCP network
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_add_sp
#ifdef ANSI_PROTO
	(sc_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode)
#else
	(p_sp_conf_info, p_ecode)
	 sc_sp_conf_info_t 	*p_sp_conf_info;
	 error_t 		*p_ecode;
#endif
{
	return_t ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }

	ret_val = sccp_prov_add_sp_to_db (p_sp_conf_info, p_ecode);

	/* If Success ful add to GTT also */
	if (ret_val == SS7_SUCCESS)
	{

		/* Zero out the structure */
		ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
		gtt_sm_info.info_id = SCCP_SM_ADD_SP; /* Command ID */
		/** SPR# 9302 Start Fix **/
		gtt_sm_info.sccp_gtt_add_sp_info = 
			(sccp_gtt_add_sp_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_sp_info_t));
		/** SPR# 9302 End Fix **/

		if (SS7_NULL == gtt_sm_info.sccp_gtt_add_sp_info) /* Memory Allocation Failure */
		{
			*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
			return(SS7_FAILURE);	
		}
		/* This has been hard-coded coz' currently 
		   MTPSAP is taken to be zero -- Sachin Bhatia*/
		gtt_sm_info.sccp_gtt_add_sp_info->mtpsap = 0;
		gtt_sm_info.sccp_gtt_add_sp_info->dpc = (U32bit)sccp_db.sp[p_sp_conf_info->sp_id].pc;
		gtt_sm_info.sccp_gtt_add_sp_info->p_ecode = p_ecode;

		/** SPR 10068 Fix **/
		gtt_sm_info.sccp_gtt_add_sp_info->local_remote_flag=
									(U8bit)sccp_db.sp[p_sp_conf_info->sp_id].local;

		/* Now call the porting func */
		ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
		if (ret_val == SS7_FAILURE )
		{
			/* We reach here is SCCP added SP successfully, 
			   but it was not added in GTT successfully 
			   we'll ROLLBACK later currently we just return error --Sachin Bhatia */
			
		}
	}

	SC_IN_TRC (("SCCP::INIT:Add Signaling point %u. %s\n", 
               p_sp_conf_info->sp_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         interfaces with DB module to add a signaling point to SCCP network
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_add_sp_to_db
#ifdef ANSI_PROTO
	(sc_sp_conf_info_t * p_sp_conf_info, error_t * p_ecode)
#else
	(p_sp_conf_info, p_ecode)
	 sc_sp_conf_info_t 	*p_sp_conf_info;
	 error_t 		*p_ecode;
#endif
{
	sp_entry_t * p_sp;
	db_sp_conf_info_t sp_info;

	sp_info.sp_id = p_sp_conf_info->sp_id;
	sp_info.nw_id = p_sp_conf_info->nw_id;
	sp_info.pc    = p_sp_conf_info->pc;
	sp_info.local = p_sp_conf_info->local;

	if(sp_info.local == 1)
	{
		sp_opc = sp_info.pc;
	}
	else
	{
		sp_dpc = sp_info.pc;
	}
	SC_IN_TRC (("SCCP::INIT:Add Signaling point %u. sp_opc %d sp_dpc %d\n", 
               p_sp_conf_info->sp_id,sp_opc,sp_dpc));

	if (SS7_FAILURE == sccp_db_conf_sp (&sp_info, p_ecode))
		return SS7_FAILURE;

	p_sp = sccp_db_find_sp (sp_info.nw_id, sp_info.pc);
	if(!p_sp)
		return SS7_FAILURE;
#ifdef SCCP_UT_DEBUG
	if (SS7_NULL == p_sp)
	{
		*p_ecode = ESCCP_DB_SERIOUS_ERR;
		return SS7_FAILURE;
	}
#endif

	sccp_init_sp (p_sp);
	p_sp->ssf = p_sp_conf_info->ssf;

/* SPR # 9288 Fix Start */
	SCCP_EVENT_ALARM (SCCP_SM_OBJECT_SP, SP_ACCESSIBLE, p_sp, 
										SS7_NULL, SS7_NULL);
/* SPR # 9288 Fix End */
	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         deletes a signaling point from SCCP network
******************************************************************************
**
**      DESCRIPTION :
**         function can be called from encapsulating shell to delete
**         a signaling point from SCCP network
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_del_sp
#ifdef ANSI_PROTO
	(sc_sp_del_info_t * p_sp_del_info, error_t * p_ecode)
#else
	(p_sp_del_info, p_ecode)
	 sc_sp_del_info_t 	*p_sp_del_info;
	 error_t 		*p_ecode;
#endif
{
	return_t ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	ret_val = sccp_prov_del_sp_from_db (p_sp_del_info, p_ecode);

	/* If Success delete from GTT also */
	if (ret_val == SS7_SUCCESS)
	{

		/* Zero out the structure */
		ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
		gtt_sm_info.info_id = SCCP_SM_DEL_SP; /* Command ID */
		/** SPR# 9302 Start Fix **/
		gtt_sm_info.sccp_gtt_del_sp_info = 
			(sccp_gtt_del_sp_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_del_sp_info_t));
		/** SPR# 9302 End Fix **/

		if (SS7_NULL == gtt_sm_info.sccp_gtt_del_sp_info) /* Memory Allocation Failure */
		{
			*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
			return(SS7_FAILURE);	
		}
		/* This has been hard-coded coz' currently 
		   MTPSAP is taken to be zero -- Sachin Bhatia*/
		gtt_sm_info.sccp_gtt_del_sp_info->mtpsap = 0;
		gtt_sm_info.sccp_gtt_del_sp_info->dpc = (U32bit)sccp_db.sp[p_sp_del_info->sp_id].pc;
		gtt_sm_info.sccp_gtt_del_sp_info->p_ecode = p_ecode;

		/* Now call the porting func */
		ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
		if (ret_val == SS7_FAILURE )
		{
			/* We reach here is SCCP deleted SP successfully, 
			   but it was not deleted from GTT successfully 
			   we'll ROLLBACK later currently we just return error --Sachin Bhatia */
			
		}
	}
	SC_IN_TRC (("SCCP::INIT:Del Signaling point %u. %s\n", 
               p_sp_del_info->sp_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**        interfaces with DB module to delete a signaling point
******************************************************************************
**
**      DESCRIPTION :
**        stop timers first and then delete signaling point
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_del_sp_from_db
#ifdef ANSI_PROTO
	(sc_sp_del_info_t * p_sp_del_info, error_t * p_ecode)
#else
	(p_sp_del_info, p_ecode)
	 sc_sp_del_info_t 	*p_sp_del_info;
	 error_t 		*p_ecode;
#endif
{
	sp_entry_t * p_sp;
        sc_reg_entry_t          *p_sccp_reg;
        int count;

	if (SS7_FAILURE == sccp_db_find_sp_from_id(p_sp_del_info->sp_id,
	                                       &p_sp, p_ecode))
		return SS7_FAILURE;

/* SPR # 9502 Fix Start */
	if((GET_SS_LIST_IN_SP(p_sp))->sp_id == p_sp_del_info->sp_id)
	{
/* SPR # 9502 Fix End */
		if (p_sp_del_info->del_ss)
		{
			U32bit i, num_ss;
			ss_entry_t * p_ss;

			num_ss = GET_NUM_SS_IN_SP (p_sp);
			for (i=0, p_ss = GET_SS_LIST_IN_SP(p_sp); i < num_ss;
			     i++, p_ss = GET_NEXT_SS(p_ss))
			{
				sccp_stop_ss (p_ss);
			}
		}
		else if (GET_NUM_SS_IN_SP(p_sp) > 0)
		{
			*p_ecode = ESCCP_SS_DEFINED_FOR_SP;
			return SS7_FAILURE;
		}
/* SPR # 9502 Fix Start */
	}
/* SPR # 9502 Fix End */
	sccp_stop_sp (p_sp);

	/* SPR 7430: Start Fix */
	if (SS7_FAILURE == sccp_db_del_sp(p_sp_del_info->sp_id, 
									p_sp_del_info->del_ss, 
									p_sp_del_info->del_csp, 
									p_ecode))
	{
		return SS7_FAILURE;
	}
	/* SPR 7430: End Fix */
         /* Since now the sp has been deleted , mark all the users
        of sp to not registered in case sp deleted is local */
        if ( IS_SP_LOCAL(p_sp) == SS7_TRUE )
            {
               for (count = 0; count < MAX_LOCAL_USERS; count++)
                        {
                           p_sccp_reg = &sccp_reg_table [count] ;
                         /*  p_sccp_reg->registered = SS7_FALSE;*/
                        }
            }


	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         sccp_prov_get_sp_info
******************************************************************************
**
**      DESCRIPTION :
**			Files the sc_sp_conf_info_t array with the currently configured 
**	    SPs
**
*****************************************************************************/
 
return_t
sccp_prov_get_sp_info
#ifdef ANSI_PROTO
        (pvoid *p_p_buf, U32bit *p_num_entries, U8bit *p_entry_size, error_t *p_ecode)
#else
        (p_p_buf, p_num_entries, p_entry_size, p_ecode)
		 pvoid 			*p_p_buf,
		 U32bit			*p_num_entries;
		 U8bit			*p_entry_size;
         error_t        *p_ecode;
#endif
{
	sc_sp_conf_info_t	*p_tmp;
	s7_len_t			buf_len;
	/* Fix for SPR No: 13263 start */
	U32bit				num_entries;
	/*	U16bit				num_entries; */
	/* Fix for SPR No: 13263 end */
	U8bit				entry_size;
	sp_id_t				sp_id;
	sp_entry_t		 	*p_sp;
 	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	p_tmp = SS7_NULL;
	*p_p_buf = SS7_NULL;

	/* Compute the number of entries */
	num_entries = 0;
	for (sp_id = 0; sp_id<MAX_SP; ++sp_id)
	{
		p_sp = GET_SP_FROM_ID(sp_id);
		if (IS_SP_CONFIGURED(p_sp))
			num_entries ++;
	}
	
	entry_size = sizeof (sc_sp_conf_info_t);

	buf_len = num_entries * entry_size;
	if ((p_tmp = (sc_sp_conf_info_t *) (pvoid) sccp_malloc (buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	
	/* SPR 9404 - Fix Start */
	/**p_num_entries = num_entries;*/  
	/* Fix for SPR No : 13263  Start     */
	/* *p_num_entries = (U8bit)num_entries;   */
	/* Fix for SPR No : 13263  End     */
	
	*p_num_entries = num_entries;   
	/* SPR 9404 - Fix End   */
	*p_entry_size = entry_size;
	*p_p_buf = (pvoid) p_tmp;

	/* Flll SP entries */
	for (sp_id = 0; sp_id<MAX_SP; ++sp_id)
	{
		p_sp = GET_SP_FROM_ID(sp_id);
		if (IS_SP_CONFIGURED(p_sp))
		{
			p_tmp->sp_id = sp_id;
			p_tmp->nw_id = p_sp->nw_id;
			p_tmp->pc = p_sp->pc;
			p_tmp->local = p_sp->local;
			p_tmp->ssf = p_sp->ssf;

			p_tmp ++;
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         adds a subsystem in the SCCP network
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_add_ss
#ifdef ANSI_PROTO
	(sc_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode)
#else
	(p_ss_conf_info, p_ecode)
	 sc_ss_conf_info_t 	*p_ss_conf_info;
	 error_t 		*p_ecode;
#endif
{
	return_t ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
	extern U8bit sccp_state;
	if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
	{
		SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		return SS7_FAILURE;
	}



	ret_val = sccp_prov_add_ss_to_db (p_ss_conf_info, p_ecode);

	/* If Success ful add to GTT also */
	if (ret_val == SS7_SUCCESS)
	{
		/* Zero out the structure */
		ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
		gtt_sm_info.info_id = SCCP_SM_ADD_SS; /* Command ID */
		/** SPR# 9302 Start Fix **/
		gtt_sm_info.sccp_gtt_add_ss_info = 
			(sccp_gtt_add_ss_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_ss_info_t));
		/** SPR# 9302 End Fix **/

		if (SS7_NULL == gtt_sm_info.sccp_gtt_add_ss_info) /* Memory Allocation Failure */
		{
			*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
			return(SS7_FAILURE);	
		}
		/* This has been hard-coded coz' currently 
		   MTPSAP is taken to be zero -- Sachin Bhatia*/
		gtt_sm_info.sccp_gtt_add_ss_info->mtpsap = 0;
		gtt_sm_info.sccp_gtt_add_ss_info->dpc = 
			(U32bit)sccp_db.sp[sccp_db.ss[p_ss_conf_info->ss_id].sp_id].pc;
		gtt_sm_info.sccp_gtt_add_ss_info->ssn = (U8bit)sccp_db.ss[p_ss_conf_info->ss_id].ssn;
		gtt_sm_info.sccp_gtt_add_ss_info->p_ecode = p_ecode;

		/* Now call the porting func */
		ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
		if (ret_val == SS7_FAILURE )
		{
			/* We reach here is SCCP added SS successfully, 
			   but it was not Addede to  GTT successfully 
			   we'll ROLLBACK later currently we just return error --Sachin Bhatia */
			
		}
	}
	SC_IN_TRC (("SCCP::INIT: Add Subsystem %u. %s\n", 
               p_ss_conf_info->ss_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**        interfaces with DB module to add a subsystem to SCCP network
******************************************************************************
**
**      DESCRIPTION :
**        adds a subsystem and initializes it
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_add_ss_to_db
#ifdef ANSI_PROTO
	(sc_ss_conf_info_t * p_ss_conf_info, error_t * p_ecode)
#else
	(p_ss_conf_info, p_ecode)
	 sc_ss_conf_info_t 	*p_ss_conf_info;
	 error_t 		*p_ecode;
#endif
{
	ss_entry_t * p_ss;
	db_ss_conf_info_t ss_info;

	ss_info.ss_id = p_ss_conf_info->ss_id;
	ss_info.ssn = p_ss_conf_info->ssn;
	ss_info.sp_id = p_ss_conf_info->sp_id;

	if (SS7_FAILURE == sccp_db_conf_ss (&ss_info, p_ecode))
		return SS7_FAILURE;

	p_ss = GET_SS_FROM_ID (ss_info.ss_id);
	sccp_init_ss (p_ss);
/* SPR # 9288 Fix Start */
	SCCP_EVENT_ALARM(SCCP_SM_OBJECT_SS, SCCP_USER_IN_SERVICE, SS7_NULL,\
							p_ss, SS7_NULL);
/* SPR # 9288 Fix End */
	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         deletes a subsystem
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_del_ss
#ifdef ANSI_PROTO
	(sc_ss_del_info_t * p_ss_del_info, error_t * p_ecode)
#else
	(p_ss_del_info, p_ecode)
	 sc_ss_del_info_t 	*p_ss_del_info;
	 error_t 		*p_ecode;
#endif
{
	return_t ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
	extern U8bit sccp_state;
	if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
	{
		SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		return SS7_FAILURE;
	}


	ret_val = sccp_prov_del_ss_from_db (p_ss_del_info, p_ecode);

	/* If Success ful add to GTT also */
	if (ret_val == SS7_SUCCESS)
	{
		/* Zero out the structure */
		ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
		gtt_sm_info.info_id = SCCP_SM_DEL_SS; /* Command ID */
		/** SPR# 9302 Start Fix **/
		gtt_sm_info.sccp_gtt_del_ss_info = 
			(sccp_gtt_del_ss_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_del_ss_info_t));
		/** SPR# 9302 End Fix **/

		if (SS7_NULL == gtt_sm_info.sccp_gtt_del_ss_info) /* Memory Allocation Failure */
		{
			*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
			return(SS7_FAILURE);	
		}
		/* This has been hard-coded coz' currently 
		   MTPSAP is taken to be zero -- Sachin Bhatia*/
		gtt_sm_info.sccp_gtt_del_ss_info->mtpsap = 0;
		gtt_sm_info.sccp_gtt_del_ss_info->dpc = 
			(U32bit)sccp_db.sp[sccp_db.ss[p_ss_del_info->ss_id].sp_id].pc;
		gtt_sm_info.sccp_gtt_del_ss_info->ssn = (U8bit)sccp_db.ss[p_ss_del_info->ss_id].ssn;
		gtt_sm_info.sccp_gtt_del_ss_info->p_ecode = p_ecode;

		/* Now call the porting func */
		ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
		if (ret_val == SS7_FAILURE )
		{
			/* We reach here is SCCP added SS successfully, 
			   but it was not Addede to  GTT successfully 
			   we'll ROLLBACK later currently we just return error --Sachin Bhatia */
			
		}
	}

	SC_IN_TRC (("SCCP::INIT: Del Subsystem %u. %s\n", 
               p_ss_del_info->ss_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**          interfaces with db module to delete subsystem
******************************************************************************
**
**      DESCRIPTION :
**          stops timers before deleting subsystem
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_del_ss_from_db
#ifdef ANSI_PROTO
	(sc_ss_del_info_t * p_ss_del_info, error_t * p_ecode)
#else
	(p_ss_del_info, p_ecode)
	 sc_ss_del_info_t 	*p_ss_del_info;
	 error_t 		*p_ecode;
#endif
{
	ss_entry_t * p_ss;
        sc_reg_entry_t          *p_sccp_reg;
        int count;

	if (SS7_FAILURE == sccp_db_find_ss_from_id (p_ss_del_info->ss_id, &p_ss, p_ecode))
		return SS7_FAILURE;

	sccp_stop_ss (p_ss);

	/* SPR 7430: Start Fix */
	if (SS7_FAILURE == sccp_db_del_ss (p_ss_del_info->ss_id, 
									p_ss_del_info->del_css, 
									p_ecode))
	{
		return SS7_FAILURE;
	}
	/* SPR 7430: End Fix */

         /* Since now the ss has been deleted , mark the user
        as not registered in case ss deleted is local */
        if ( IS_SS_LOCAL(p_ss) == SS7_TRUE )
            {
               for (count = 0; count < MAX_LOCAL_USERS; count++)
                        {
                           p_sccp_reg = &sccp_reg_table [count] ;
                           if (p_ss->ssn == p_sccp_reg->ssn)
													 {
													 }
 
                          /* p_sccp_reg->registered = SS7_FALSE;*/
                        }
            }


	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         sccp_prov_get_ss_info
******************************************************************************
**
**      DESCRIPTION :
**			Files the sc_ss_conf_info_t array with the currently configured 
**	    SSs
**
*****************************************************************************/
/* Fix for SPR No: 13263 Start */ 
return_t
sccp_prov_get_ss_info
#ifdef ANSI_PROTO
        (pvoid *p_p_buf, U32bit *p_num_entries, U8bit *p_entry_size, error_t *p_ecode)
#else
        (p_p_buf, p_num_entries, p_entry_size, p_ecode)
		 pvoid 			*p_p_buf,
		 U32bit			*p_num_entries;
		 U8bit			*p_entry_size;
         error_t        *p_ecode;
#endif
/* Fix for SPR No: 13263 End */ 
{
	sc_ss_conf_info_t	*p_tmp;
	s7_len_t			buf_len;
	U32bit				num_entries;
	/* Fix for SPR No: 13263 Start */
	/*	U16bit				num_entries;*/
	/* Fix for SPR No: 13263 End */
	U8bit				entry_size;
	ss_id_t				ss_id;
	ss_entry_t		 	*p_ss;
 extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	p_tmp = SS7_NULL;
	*p_p_buf = SS7_NULL;

	/* Compute the number of entries */
	num_entries = 0;
	for (ss_id = 0; ss_id<MAX_SS; ++ss_id)
	{
		p_ss = GET_SS_FROM_ID(ss_id);
		if (IS_SS_CONFIGURED(p_ss))
			num_entries ++;
	}
	
	entry_size = sizeof (sc_ss_conf_info_t);

	buf_len = num_entries * entry_size;
	if ((p_tmp = (sc_ss_conf_info_t *) (pvoid) sccp_malloc (buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	
	/* SPR 9404 - Fix Start */
	/**p_num_entries = num_entries;*/  
	*p_num_entries = num_entries;   
	/* Fix for SPR No: 13263 Start */
	/* *p_num_entries = (U8bit)num_entries;   */
	/* Fix for SPR No: 13263 End */
	/* SPR 9404 - Fix End   */
	*p_entry_size = entry_size;
	*p_p_buf = (pvoid) p_tmp;

	/* Flll SS entries */
	for (ss_id = 0; ss_id<MAX_SS; ++ss_id)
	{
		p_ss = GET_SS_FROM_ID(ss_id);
		if (IS_SS_CONFIGURED(p_ss))
		{
			p_tmp->ss_id = ss_id;
			p_tmp->sp_id = p_ss->sp_id;
			p_tmp->ssn = p_ss->ssn;

			p_tmp ++;
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         adds concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_add_css
#ifdef ANSI_PROTO
	(sc_css_info_t * p_css_info, error_t * p_ecode)
#else
	(p_css_info, p_ecode)
	 sc_css_info_t 	*p_css_info;
	 error_t 	*p_ecode;
#endif
{
	return_t ret_val;
	db_css_info_t css_info;
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	css_info.ss_id = p_css_info->ss_id;
	css_info.css_id = p_css_info->css_id;

	ret_val = sccp_db_conf_css (&css_info, p_ecode);

	SC_IN_TRC (("SCCP::INIT: add concerned Subsystem %u %u. %s\n", 
               p_css_info->ss_id, p_css_info->css_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**          interfaces with db module to delete conc subsystem
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_del_css
#ifdef ANSI_PROTO
	(sc_css_info_t * p_css_info, error_t * p_ecode)
#else
	(p_css_info, p_ecode)
	 sc_css_info_t 	*p_css_info;
	 error_t 	*p_ecode;
#endif
{
	return_t ret_val;
	db_css_info_t css_info;
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	css_info.ss_id = p_css_info->ss_id;
	css_info.css_id = p_css_info->css_id;
	ret_val =  sccp_db_del_css (&css_info, p_ecode);

	SC_IN_TRC (("SCCP::INIT: Del concerned Subsystem %u %u. %s\n", 
               p_css_info->ss_id, p_css_info->css_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         sccp_prov_get_css_info
******************************************************************************
**
**      DESCRIPTION :
**			Files the ss_id_t array with the currently configured CSSs for the 
**	    specified SS
**
*****************************************************************************/
/* Fix for SPR No: 13263 Start */ 
return_t
sccp_prov_get_css_info
#ifdef ANSI_PROTO
        (ss_id_t ss_id, 
		pvoid *p_p_buf, 
		U32bit *p_num_entries, 
		U8bit *p_entry_size, 
		error_t *p_ecode)
#else
        (p_p_buf, p_num_entries, p_entry_size, p_ecode)
		 pvoid 			*p_p_buf,
		 U32bit			*p_num_entries;
		 U8bit			*p_entry_size;
         error_t        *p_ecode;
#endif
	/* Fix for SPR No: 13263 End */
{
	ss_id_t				*p_tmp;
	s7_len_t			buf_len;
	U32bit				num_entries;
	/* Fix for SPR No: 13263 Start */
	/* U16bit				num_entries;*/
	/* Fix for SPR No: 13263 End */
	U8bit				entry_size;
	ss_entry_t			*p_ss;
	U8bit				* p_css_list;
	U32bit				i;
	ss_entry_t			* p_css;

	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	p_tmp = SS7_NULL;
	*p_p_buf = SS7_NULL;

	p_ss = GET_SS_FROM_ID (ss_id);
	if ( ! IS_SS_CONFIGURED(p_ss) )
	{
		*p_ecode = ESCCP_SS_NOT_CONFIGURED;
		return SS7_FAILURE;
	}

	num_entries = GET_NUM_CSS(p_ss);
	entry_size = sizeof (ss_id_t);

	buf_len = num_entries * entry_size;
	if ((p_tmp = (ss_id_t *) (pvoid) sccp_malloc (buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	
	/* SPR 9404 - Fix Start */
	/**p_num_entries = num_entries;*/  
	/* Fix for SPR No: 13263 start */
	*p_num_entries = num_entries;   
	/* *p_num_entries = (U8bit)num_entries;   */
	/* Fix for SPR No:13263 End */
	/* SPR 9404 - Fix End   */
	*p_entry_size = entry_size;
	*p_p_buf = (pvoid) p_tmp;

	/* Flll CSS entries */
	for (i=0, p_css_list = GET_CSS_LIST (p_ss);
		i < GET_NUM_CSS (p_ss);
		i++, p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
	{
		p_css = GET_CSS_FROM_LIST(p_css_list);
		*p_tmp = GET_ID_FROM_SS(p_css);
		p_tmp ++;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         adds concerned signaling point
******************************************************************************
**
**      DESCRIPTION :
**        
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_add_csp
#ifdef ANSI_PROTO
	(sc_csp_info_t * p_csp_info, error_t * p_ecode)
#else
	(p_csp_info, p_ecode)
	 sc_csp_info_t 	*p_csp_info;
	 error_t 	*p_ecode;
#endif
{
	return_t ret_val;
	db_csp_info_t csp_info;
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	csp_info.ss_id = p_csp_info->ss_id;
	csp_info.csp_id = p_csp_info->csp_id;

	ret_val = sccp_db_conf_csp (&csp_info, p_ecode);

	SC_IN_TRC (("SCCP::INIT: Add concerned Signaling point %u %u. %s\n",
	           p_csp_info->ss_id, p_csp_info->csp_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         interfaces with db module to delete conc signaling point
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_prov_del_csp
#ifdef ANSI_PROTO
	(sc_csp_info_t * p_csp_info, error_t * p_ecode)
#else
	(p_csp_info, p_ecode)
	 sc_csp_info_t 	*p_csp_info;
	 error_t 	*p_ecode;
#endif
{
	return_t ret_val;
	db_csp_info_t csp_info;
	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	csp_info.ss_id = p_csp_info->ss_id;
	csp_info.csp_id = p_csp_info->csp_id;

	ret_val = sccp_db_del_csp (&csp_info, p_ecode);

	SC_IN_TRC (("SCCP::INIT: Del concerned Signaling point %u %u. %s\n",
	           p_csp_info->ss_id, p_csp_info->csp_id, RESULT_STR(ret_val)));

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         sccp_prov_get_csp_info
******************************************************************************
**
**      DESCRIPTION :
**			Files the sp_id_t array with the currently configured CSPs for the 
**	    specified SS
**
*****************************************************************************/
	/* Fix for SPR No: 13263 start */
 
return_t
sccp_prov_get_csp_info
#ifdef ANSI_PROTO
        (ss_id_t ss_id, 
		pvoid *p_p_buf, 
		U32bit *p_num_entries, 
		U8bit *p_entry_size, 
		error_t *p_ecode)
#else
        (p_p_buf, p_num_entries, p_entry_size, p_ecode)
		 pvoid 			*p_p_buf,
		 U32bit			*p_num_entries;
		 U8bit			*p_entry_size;
         error_t        *p_ecode;
#endif
	/* Fix for SPR No: 13263 End */
{
	sp_id_t				*p_tmp;
	s7_len_t			buf_len;
	/* Fix for SPR No: 13263 start */
	U32bit				num_entries;
	/* U16bit				num_entries;*/
	/* Fix for SPR No: 13263  End */
	U8bit				entry_size;
	ss_entry_t			*p_ss;
	U8bit				* p_csp_list;
	U32bit				i;
	sp_entry_t			* p_csp;
	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
	    SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
        return SS7_FAILURE;
    }


	p_tmp = SS7_NULL;
	*p_p_buf = SS7_NULL;

	p_ss = GET_SS_FROM_ID (ss_id);
	if ( ! IS_SS_CONFIGURED(p_ss) )
	{
		*p_ecode = ESCCP_SS_NOT_CONFIGURED;
		return SS7_FAILURE;
	}

	num_entries = GET_NUM_CSP(p_ss);
	entry_size = sizeof (sp_id_t);

	buf_len = num_entries * entry_size;
	if ((p_tmp = (sp_id_t *) (pvoid) sccp_malloc (buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}
	
	/* SPR 9404 - Fix Start */
	/**p_num_entries = num_entries;*/  
	/* Fix for SPR No: 13263  start*/
	*p_num_entries = num_entries;   
	/* *p_num_entries = (U8bit)num_entries;   */
	/* Fix for SPR No: 13263 End */
	/* SPR 9404 - Fix End   */
	*p_entry_size = entry_size;
	*p_p_buf = (pvoid) p_tmp;

	/* Flll CSP entries */
	for (i=0, p_csp_list = GET_CSP_LIST (p_ss);
		i < GET_NUM_CSP (p_ss);
		i++, p_csp_list = GET_NEXT_CSP_FROM_LIST(p_csp_list))
	{
		p_csp = GET_CSP_FROM_LIST(p_csp_list);
		*p_tmp = GET_ID_FROM_SP(p_csp);
		p_tmp ++;
	}

	return SS7_SUCCESS;
}

/* New Functional [GTT Integration] APIs defined here --Sachin Bhatia*/

/*****************************************************************************
**      FUNCTION :
**         Adds a MTPSAP to the translation function
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_add_mtpsap
#ifdef ANSI_PROTO
        (sccp_mtpsap_t mtpsap, 
	 error_t *p_ecode)
#else
	(mtpsap, p_ecode)
        sccp_mtpsap_t mtpsap ;
	error_t *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_ADD_MTPSAP; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.sccp_gtt_add_mtpsap_info = 
		(sccp_gtt_add_mtpsap_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_mtpsap_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.sccp_gtt_add_mtpsap_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}
	gtt_sm_info.sccp_gtt_add_mtpsap_info->mtpsap = mtpsap;
	gtt_sm_info.sccp_gtt_add_mtpsap_info->p_ecode = p_ecode;

	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

	SC_IN_TRC (("SCCP::INIT:ADD MTPSAP %u,  %s\n", 
				mtpsap, RESULT_STR(ret_val)));

	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**         sccp_prov_del_mtpsap
******************************************************************************
**
**      DESCRIPTION :
**         Deletes a MTPSAP from the translation function
**
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_del_mtpsap
#ifdef ANSI_PROTO
        (sccp_mtpsap_t mtpsap, 
	 error_t *p_ecode)
#else
	(mtpsap, p_ecode)
        sccp_mtpsap_t mtpsap ;
	error_t *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));

	gtt_sm_info.info_id = SCCP_SM_DEL_MTPSAP; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.sccp_gtt_del_mtpsap_info = 
		(sccp_gtt_del_mtpsap_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_del_mtpsap_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.sccp_gtt_del_mtpsap_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}

	gtt_sm_info.sccp_gtt_del_mtpsap_info->mtpsap = mtpsap;
	gtt_sm_info.sccp_gtt_del_mtpsap_info->p_ecode = p_ecode;

	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

	SC_IN_TRC (("SCCP::INIT:DEL MTPSAP %u,  %s\n", 
				mtpsap, RESULT_STR(ret_val)));
	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**	sccp_prov_get_mtpsap_list
******************************************************************************
**
**      DESCRIPTION :
**         gets MTPSAP info from the translation function
**
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_get_mtpsap_list
#ifdef ANSI_PROTO
	(sccp_count_t   *no_of_mtpsaps,
	 sccp_mtpsap_t   **mtpsap_list,
	 error_t         *p_ecode)
#else
	(no_of_mtpsaps, mtpsap_list, p_ecode)
	sccp_count_t   *no_of_mtpsaps;
	 sccp_mtpsap_t   **mtpsap_list;
	 error_t         *p_ecode)
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_GET_MTPSAP_INFO; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.sccp_gtt_get_mtpsap_info = 
		(sccp_gtt_get_mtpsap_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_get_mtpsap_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.sccp_gtt_get_mtpsap_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}
	gtt_sm_info.sccp_gtt_get_mtpsap_info->no_of_mtpsaps = no_of_mtpsaps;
	gtt_sm_info.sccp_gtt_get_mtpsap_info->mtpsap_list = mtpsap_list;
	gtt_sm_info.sccp_gtt_get_mtpsap_info->p_ecode = p_ecode;

	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

	SC_IN_TRC (("SCCP::INIT:Get MTPSAPs  %s\n", 
				RESULT_STR(ret_val)));

	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**        sccp_prov_add_trans_rule
******************************************************************************
**
**      DESCRIPTION :
**         adds a translation rule from the translation function [GTT]
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_add_trans_rule
#ifdef ANSI_PROTO
	(sccp_gti_t     gti,
	 sccp_trans_fun_entry_t trans_func,
	 sccp_count_t	no_of_actions,
	 sccp_action_t	action_array[],
	 sccp_trans_rule_id_t *trans_rule_id,
	 error_t *p_ecode)
#else
	(gti, trans_func, no_of_actions, action_array, trans_rule_id, p_ecode)
	sccp_gti_t     gti;
	sccp_trans_fun_entry_t trans_func;
	 sccp_count_t	no_of_actions,
	 sccp_action_t	action_array[],
	sccp_trans_rule_id_t *trans_rule_id;
	error_t *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
	U32bit	counter;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_ADD_TRANS_RULE; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.sccp_gtt_add_trans_rule_info = 
		(sccp_gtt_add_trans_rule_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_trans_rule_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.sccp_gtt_add_trans_rule_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}

	gtt_sm_info.sccp_gtt_add_trans_rule_info->gti = gti;;
	gtt_sm_info.sccp_gtt_add_trans_rule_info->trans_func =  trans_func;
	gtt_sm_info.sccp_gtt_add_trans_rule_info->no_of_actions = no_of_actions;

	/* Copy these many actions */
	for(counter = 0 ; counter < no_of_actions ; counter++)
	{
		gtt_sm_info.sccp_gtt_add_trans_rule_info->action_array[counter] = action_array[counter];
	}

	gtt_sm_info.sccp_gtt_add_trans_rule_info->trans_rule_id = trans_rule_id;
	gtt_sm_info.sccp_gtt_add_trans_rule_info->p_ecode = p_ecode;


	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
        if ( ret_val == SS7_SUCCESS )
        *trans_rule_id = *(gtt_sm_info.sccp_gtt_add_trans_rule_info->trans_rule_id);

	SC_IN_TRC (("SCCP::INIT:Add Trans Rule %d  %s\n", 
				(U32bit)(*trans_rule_id), RESULT_STR(ret_val)));

	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**        sccp_prov_del_trans_rule
******************************************************************************
**
**      DESCRIPTION :
**         deletes a translation rule from the translation function [GTT]
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_del_trans_rule
#ifdef ANSI_PROTO
	(sccp_gti_t     gti,
	 sccp_trans_fun_entry_t trans_func,
	 sccp_trans_rule_id_t trans_rule_id,
	 error_t *p_ecode)
#else
	(gti, trans_func, trans_rule_id, p_ecode)
	sccp_gti_t     gti;
	sccp_trans_fun_entry_t trans_func;
	sccp_trans_rule_id_t trans_rule_id;
	error_t *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_DEL_TRANS_RULE; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.sccp_gtt_del_trans_rule_info = 
		(sccp_gtt_del_trans_rule_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_del_trans_rule_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.sccp_gtt_del_trans_rule_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}
	gtt_sm_info.sccp_gtt_del_trans_rule_info->gti = gti;
        gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.used = trans_func.used; 
	gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.tt =  trans_func.tt;
        gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.np = trans_func.np;
        gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.nai = trans_func.nai;
        gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.es = trans_func.es;
        gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.escape_used = trans_func.escape_used;
        gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_func.escape_code = trans_func.escape_code;
	gtt_sm_info.sccp_gtt_del_trans_rule_info->trans_rule_id = trans_rule_id;
	gtt_sm_info.sccp_gtt_del_trans_rule_info->p_ecode = p_ecode;


	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

	SC_IN_TRC (("SCCP::INIT:Del Trans Rule %d  %s\n", 
				(U32bit)(trans_rule_id), RESULT_STR(ret_val)));

	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**        sccp_prov_get_trans_func_list
******************************************************************************
**
**      DESCRIPTION :
**         Get translation function list [GTT]
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_get_trans_func_list
#ifdef ANSI_PROTO
	(sccp_gti_t     gti,
	 sccp_count_t    *no_of_trans_func,
	 sccp_trans_fun_entry_t **fn_list,
	 error_t         *p_ecode)
#else
	(gti, no_of_trans_func, fn_list, p_ecode)
	 sccp_gti_t     gti;
	 sccp_count_t    *no_of_trans_func;
	 sccp_trans_fun_entry_t **fn_list;
	 error_t         *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_GET_TRANS_FUNC_LIST_INFO; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.gtt_get_trans_func_list_info = 
		(sccp_gtt_get_trans_func_list_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_get_trans_func_list_info_t));
	/** SPR# 9302 End Fix **/


	if (SS7_NULL == gtt_sm_info.gtt_get_trans_func_list_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}
	gtt_sm_info.gtt_get_trans_func_list_info->gti = gti;
	gtt_sm_info.gtt_get_trans_func_list_info->no_of_trans_func =  no_of_trans_func;
	/* gtt_sm_info.gtt_get_trans_func_list_info->fn_list = fn_list; */
	gtt_sm_info.gtt_get_trans_func_list_info->p_ecode = p_ecode;


	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Starts */
	/* fn_list = gtt_sm_info.gtt_get_trans_func_list_info->fn_list; */
	*fn_list = *(gtt_sm_info.gtt_get_trans_func_list_info->fn_list); 
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */

	SC_IN_TRC (("SCCP::INIT:Get Trans func %d  %s\n", 
				(U32bit)(*no_of_trans_func), RESULT_STR(ret_val)));

	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**        sccp_prov_add_to_dpc_ssn_table
******************************************************************************
**
**      DESCRIPTION :
**         Add Entry to DPC SSN Table 
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_add_to_dpc_ssn_table
#ifdef ANSI_PROTO
	(U8bit  table_mask,
	 U8bit   value[],
	 U8bit   ssn,
	 sccp_count_t    dpc_count,
	 sccp_mtpsap_t mtpsaps[],
	 U32bit  dpcs[],
	 error_t *p_ecode)
#else
	(table_mask, value, ssn, dpc_count, mtpsaps[], dpcs, p_ecode)
	U8bit  table_mask;
	U8bit   value[];
	U8bit   ssn;
	sccp_count_t    dpc_count;
	sccp_mtpsap_t mtpsaps[];
	U32bit  dpcs[];
	error_t *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
	U32bit	counter;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_ADD_TO_DPC_SSN_TABLE; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info = 
		(sccp_gtt_add_to_dpc_ssn_table_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_to_dpc_ssn_table_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}

	gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->table_mask = table_mask ;
	for (counter = 0 ; counter < SCCP_MAX_GT_DIGITS ; counter++)
	{
		gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->value[counter] = value[counter];
	}

	gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->dpc_count = dpc_count;
	for (counter = 0 ; counter < dpc_count ; counter++)
	{
		gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->mtpsaps[counter] = mtpsaps[counter];
		gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->dpcs[counter] = dpcs[counter];
	}

	gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->ssn=ssn;

	gtt_sm_info.gtt_add_to_dpc_ssn_tbl_info->p_ecode = p_ecode;


	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

	SC_IN_TRC (("SCCP::INIT:Add to DPC SSN Table  %s\n", RESULT_STR(ret_val)));

	return(ret_val);
}


/*****************************************************************************
**      FUNCTION :
**        sccp_prov_del_from_dpc_ssn_table
******************************************************************************
**
**      DESCRIPTION :
**         Delete Entry from DPC SSN Table 
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_del_from_dpc_ssn_table
#ifdef ANSI_PROTO
	(U8bit  table_mask,
	 U8bit   value[],
	 error_t *p_ecode)
#else
	(table_mask, value, p_ecode)
	U8bit  table_mask;
	U8bit   value[];
	error_t *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;
	U32bit	counter;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_DEL_FROM_DPC_SSN_TABLE; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.gtt_del_from_dpc_ssn_tbl_info = 
		(sccp_gtt_del_from_dpc_ssn_table_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_del_from_dpc_ssn_table_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.gtt_del_from_dpc_ssn_tbl_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}

	gtt_sm_info.gtt_del_from_dpc_ssn_tbl_info->table_mask = table_mask ;
	for (counter = 0 ; counter < SCCP_MAX_GT_DIGITS ; counter++)
	{
		gtt_sm_info.gtt_del_from_dpc_ssn_tbl_info->value[counter] = value[counter];
	}

	gtt_sm_info.gtt_del_from_dpc_ssn_tbl_info->p_ecode = p_ecode;


	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);

	SC_IN_TRC (("SCCP::INIT:Del from DPC SSN Table  %s\n", 
			 			RESULT_STR(ret_val)));

	return(ret_val);
}

/*****************************************************************************
**      FUNCTION :
**        sccp_prov_get_rules_per_trans_func
******************************************************************************
**
**      DESCRIPTION :
**         Gets rules corrosponding to a trans function
**      NOTE :
**
*****************************************************************************/
return_t sccp_prov_get_rules_per_trans_func
#ifdef ANSI_PROTO
	(sccp_gti_t     	gti,
	 sccp_trans_fun_entry_t trans_func,
	 sccp_count_t    	*no_of_rules,
	 sccp_get_trans_rule_t 	**trans_func_list,
	 error_t         	*p_ecode)
#else
	(gti, trans_func, no_of_rules, trans_func_list, p_ecode)
	sccp_gti_t     gti;
	sccp_trans_fun_entry_t trans_func;
	sccp_count_t    *no_of_rules;
	sccp_get_trans_rule_t **trans_func_list;
	error_t         *p_ecode;
#endif
{
	return_t  ret_val;
	sccp_gtt_sm_info_t	gtt_sm_info;

	/* Zero out the structure */
	ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
	gtt_sm_info.info_id = SCCP_SM_GET_RULE_LIST_PER_TRANS_FUNC_INFO; /* Command ID */
	/** SPR# 9302 Start Fix **/
	gtt_sm_info.gtt_get_rules_per_trans_func_info = 
		(sccp_gtt_get_rules_per_trans_func_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_get_rules_per_trans_func_info_t));
	/** SPR# 9302 End Fix **/

	if (SS7_NULL == gtt_sm_info.gtt_get_rules_per_trans_func_info) /* Memory Allocation Failure */
	{
		*(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
		return(SS7_FAILURE);	
	}
	gtt_sm_info.gtt_get_rules_per_trans_func_info->gti = gti;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.used = trans_func.used;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.tt =  trans_func.tt;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.np = trans_func.np;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.nai = trans_func.nai;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.es = trans_func.es;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.escape_used = trans_func.escape_used;
        gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func.escape_code = trans_func.escape_code;  
	gtt_sm_info.gtt_get_rules_per_trans_func_info->no_of_rules = no_of_rules;
	gtt_sm_info.gtt_get_rules_per_trans_func_info->trans_func_list = trans_func_list;
	gtt_sm_info.gtt_get_rules_per_trans_func_info->p_ecode = p_ecode;


	/* Now call the porting func */
	ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
        no_of_rules =  gtt_sm_info.gtt_get_rules_per_trans_func_info->no_of_rules;

	SC_IN_TRC (("SCCP::INIT:Get Rule per func  %s\n", 
				RESULT_STR(ret_val)));

	return(ret_val);
}

/* New Functional [GTT Integration] APIs End here --Sachin Bhatia*/

/*****************************************************************************
**      FUNCTION :
**         initializes state of a sp
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_init_sp
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t * p_sp;
#endif
{
	/* Initialise the state of the signaling point */
	p_sp->allowed = SS7_TRUE;

	p_sp->active = SS7_FALSE;
	p_sp->upu_received = SS7_FALSE;
	p_sp->upu_cause = 0;
	/* Fix for SPR No: 13344 Start */
	p_sp->cong_cause = 0; 
	/* Fix for SPR No: 13344 Stop */

	/* Initialize restriction and congestion levels */
	p_sp->rlm = 0;
	p_sp->rslm = 0;
	p_sp->cls = 0;

	p_sp->rl = 0;
	p_sp->rsl = 0;
	p_sp->ril = 0;

	/* Initialize Timers */
	p_sp->t_con_running = SS7_FALSE;
	p_sp->t_a_running = SS7_FALSE;
	p_sp->t_d_running = SS7_FALSE;

	sccp_init_ss (&p_sp->scmg_ss);
}

/*****************************************************************************
**      FUNCTION :
**
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_init_ss
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	 ss_entry_t *p_ss;
#endif
{
	/* SPR 10845 - Fix Start */
	/* Initialise the state of the subsystem */
	if (SS7_TRUE == IS_SS_LOCAL(p_ss) && GET_SS_SSN(p_ss) != SCMG_SSN)
		p_ss->allowed = SS7_FALSE;
	else
		p_ss->allowed = SS7_TRUE;
	/* SPR 10845 - Fix End  */

	/* SPR 1503: Initialize SS to unregistered */
	p_ss->registered = SS7_FALSE;

	/* Initialise timers */
	p_ss->t_stat_info_running = SS7_FALSE;

}

/*****************************************************************************
**      FUNCTION :
**        stops a sp 
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stop_sp
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t *p_sp;
#endif
{
	sccp_stop_sp_timers (p_sp);
}

/*****************************************************************************
**      FUNCTION :
**        stops all timers of a sp
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stop_sp_timers
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t *p_sp;
#endif
{
	if (p_sp->t_a_running)
		sccp_stop_timer (&p_sp->t_a_timer_id);

	if (p_sp->t_d_running)
		sccp_stop_timer (&p_sp->t_d_timer_id);

	if (p_sp->t_con_running)
		sccp_stop_timer (&p_sp->t_con_timer_id);
}

/*****************************************************************************
**      FUNCTION :
**         stops a subsystem
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stop_ss
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	 ss_entry_t *p_ss;
#endif
{
	sccp_stop_ss_timers (p_ss);
}

/*****************************************************************************
**      FUNCTION :
**        stops all timers of a subsystem
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_stop_ss_timers
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	 ss_entry_t *p_ss;
#endif
{
/* SPR # 9289 Fix Start */
#ifdef DISTRIBUTED_SCCP
	if(p_ss->sst_instance_id != sc_opt.dsccp_local_instance_id)
		return;
#endif
/* SPR # 9289 Fix End */
	if (p_ss->t_stat_info_running)
		sccp_stop_timer (&p_ss->t_stat_info_timer_id);
}

/*****************************************************************************
**      FUNCTION :
**        handles sm api command category PROV
******************************************************************************
**
**      DESCRIPTION :
**         calls appropriate func depending on the command
**
**      NOTE :
**
*****************************************************************************/

void
sccp_prov_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit *p_api;
#endif
{
	U8bit cmd;
	return_t ret_val;
#ifdef SCCP_TRACE_ENABLED
	S8bit * p_trstr1 =(S8bit *) "cmd configure";

	S8bit * p_trstr2 =(S8bit *) "cmd delete";

	S8bit * p_trstr3 =(S8bit *) "cmd query";

#endif
	U8bit param = 0; Boolean put_param = SS7_FALSE;
	error_t ecode;

	cmd = GET_SM_CMD(p_api);

	SC_A_TRC (("SCCP::INIT:SM category PROV\n"));

	switch (cmd)
	{
		/* SPR 1272: Start fix 
		 * Message based timer initialization
		 */
		case SCCP_SM_INIT_TIMER:
                        SC_A_TRC (("SCCP::INIT: Initialising Timers\n"));
                        ret_val = sccp_sm_cmd_init_timer (p_api, &ecode);
                        break;
		/* SPR 1272: End fix */

		case SCCP_SM_ADD_SP:
			SC_A_TRC (("SCCP::INIT: %s signaling point\n", p_trstr1));
			ret_val = sccp_sm_cmd_conf_sp (p_api, &ecode);
			sp_add_count=sp_add_count+1;
      SC_A_TRC (("SCCP::INIT:SCCP_SM_ADD_SP sp_add_count %d \n",sp_add_count));
			break;

		case SCCP_SM_ADD_SS:
			SC_A_TRC (("SCCP::INIT: %s subsystem\n", p_trstr1));
			ret_val = sccp_sm_cmd_conf_ss (p_api, &ecode);
			ss_add_count=ss_add_count+1;
      SC_A_TRC (("SCCP::INIT:SCCP_SM_ADD_SS ss_add_count %d \n",ss_add_count));
			break;

		case SCCP_SM_ADD_CSS:
			SC_A_TRC (("SCCP::INIT: %s concerned subsystem\n", p_trstr1));
			ret_val = sccp_sm_cmd_conf_css (p_api, &ecode);
			break;

		case SCCP_SM_ADD_CSP:
			SC_A_TRC (("SCCP::INIT: %s concerned signaling point\n", p_trstr1));
			ret_val = sccp_sm_cmd_conf_csp (p_api, &ecode);
			break;

		case SCCP_SM_DEL_SP:
			SC_A_TRC (("SCCP::INIT: %s signaling point\n", p_trstr2));
			ret_val = sccp_sm_cmd_del_sp (p_api, &ecode);
			sp_add_count=sp_add_count-1;
      SC_A_TRC (("SCCP::INIT:SCCP_SM_DEL_SP sp_add_count %d \n",sp_add_count));
			if(sp_add_count == 0 && ss_add_count == 0)
			{
				SC_A_TRC (("SCCP::INIT:Calling sccp_deregister()\n"));
				sccp_deregister();
				sccp_deregister_set = 1;
			}

			break;

		case SCCP_SM_DEL_SS:
			SC_A_TRC (("SCCP::INIT: %s subsystem\n", p_trstr2));
			ret_val = sccp_sm_cmd_del_ss (p_api, &ecode);
			ss_add_count=ss_add_count-1;
      SC_A_TRC (("SCCP::INIT:SCCP_SM_DEL_SS ss_add_count %d \n",ss_add_count));
			break;

		case SCCP_SM_DEL_CSS:
			SC_A_TRC (("SCCP::INIT: %s concerned subsystem\n", p_trstr2));
			ret_val = sccp_sm_cmd_del_css (p_api, &ecode);
			break;

		case SCCP_SM_DEL_CSP:
			SC_A_TRC (("SCCP::INIT: %s concerned signaling point\n", p_trstr2));
			ret_val = sccp_sm_cmd_del_csp (p_api, &ecode);
			break;

		case SCCP_SM_GET_TIMER_INFO:
			SC_A_TRC (("SCCP::INIT: %s timer info\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_timer_info (p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		case SCCP_SM_GET_SP_INFO:
			SC_A_TRC (("SCCP::INIT: %s SP provisioning info\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_sp_info (p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		case SCCP_SM_GET_SS_INFO:
			SC_A_TRC (("SCCP::INIT: %s SS provisioning info\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_ss_info (p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		case SCCP_SM_GET_CSS_INFO:
			SC_A_TRC (("SCCP::INIT: %s concerned subsystem info\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_css_info (p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		case SCCP_SM_GET_CSP_INFO:
			SC_A_TRC (("SCCP::INIT: %s concerned signalling poing info\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_csp_info (p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;
#ifdef DISTRIBUTED_SCCP
		case DSCCP_SM_CONF_NEW_INSTANCE:
			SC_A_TRC(("DSCCP::INIT DSCCP_SM_CONF_NEW_INSTANCE received\n"));
			ret_val = dsccp_sm_cmd_prov_comp_mate_status_info(p_api, &ecode);
			break;
#endif
#ifdef BACK_UP_SSN
		case SCCP_SM_ADD_BACKUP_SSN:
			SC_A_TRC(("BACKUP SSN received\n"));
				ret_val = sccp_handle_add_back_up_ssn(p_api);
				break;
#endif

		/* The following cases are for provisioning the translation function i.e. GTT*/		
		/* --Sachin Bhatia */

		case SCCP_SM_ADD_MTPSAP:
			SC_A_TRC (("SCCP::INIT: %s MTPSAP\n", p_trstr1));
			ret_val = sccp_sm_cmd_add_mtpsap(p_api, &ecode);
			break;

		case SCCP_SM_ADD_TRANS_RULE:
			SC_A_TRC (("SCCP::INIT: %s Translation Rule \n", p_trstr1));
			ret_val = sccp_sm_cmd_add_trans_rule(p_api, &ecode);

                        if ( ret_val == SS7_SUCCESS )
	                return;
                        break;	

		case SCCP_SM_ADD_TO_DPC_SSN_TABLE:
			SC_A_TRC (("SCCP::INIT: %s DPC SSN table\n", p_trstr1));
			ret_val = sccp_sm_cmd_add_to_dpc_ssn_table(p_api, &ecode);
			break;

		case SCCP_SM_DEL_MTPSAP:
			SC_A_TRC (("SCCP::INIT: %s MTPSAP\n", p_trstr2));
			ret_val = sccp_sm_cmd_del_mtpsap(p_api, &ecode);
			break;

		case SCCP_SM_DEL_TRANS_RULE:
			SC_A_TRC (("SCCP::INIT: %s Translation Rule\n", p_trstr2));
			ret_val = sccp_sm_cmd_del_trans_rule(p_api, &ecode);
			break;

		case SCCP_SM_DEL_FROM_DPC_SSN_TABLE:
			SC_A_TRC (("SCCP::INIT: %s DPC SSN table\n", p_trstr2)); 
			ret_val = sccp_sm_cmd_del_from_dpc_ssn_table(p_api, &ecode);
			break;

		case SCCP_SM_GET_MTPSAP_INFO:
			SC_A_TRC (("SCCP::INIT: %s MTPSAP\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_mtpsap_info(p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		case SCCP_SM_GET_TRANS_FUNC_LIST_INFO:
			SC_A_TRC (("SCCP::INIT: %s Translation Function\n", p_trstr3));
			ret_val = sccp_sm_cmd_get_trans_func_list_info(p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		case SCCP_SM_GET_RULE_LIST_PER_TRANS_FUNC_INFO:
			SC_A_TRC (("SCCP::INIT: %s Translation Rule Info \n", p_trstr3));
			ret_val = sccp_sm_cmd_get_rule_list_per_trans_func_info(p_api, &ecode);
			if (ret_val == SS7_SUCCESS)
				return;
			break;

		/* End of new functions --Sachin Bhatia*/


		default:
			SC_A_TRC (("SCCP::INIT: Invalid provisioning command %d\n", cmd));
			ret_val = SS7_FAILURE;
			ecode = ESS7_INVALID_API_ELEMENT;
			break;
	}

	sccp_prov_sm_cmd_resp (p_api, ret_val, param, put_param, ecode);
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
sccp_prov_sm_cmd_resp
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


/* SPR 1272: Start fix */
/*****************************************************************************
**      FUNCTION :
**         handles the initialisation of timers
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to init
**         timers
**
*****************************************************************************/
 
return_t
sccp_sm_cmd_init_timer
#ifdef ANSI_PROTO
        (U8bit * p_api, error_t * p_ecode)
#else
        (p_api, p_ecode)
         U8bit          *p_api;
         error_t        *p_ecode;
#endif
{
        tmr_buffer_t    timers [SCCP_MAX_TIMER_CONFIG_ID+1];
        U8bit           num_timers ;
        U8bit           *p_elem ;
        U8bit           count ;
 
        p_elem = p_api + SS7_SM_API_MIN_LEN ;
        num_timers = *p_elem ;
        p_elem += SCCP_SM_NUM_TIMER_LEN ;
        for (count = 0; count < num_timers; count++)
        {
                timers [count].timer_index = *p_elem++ ;
                timers [count].timer_value = GET_4_BYTE_LE (p_elem) ;
                p_elem += SCCP_SM_TIMER_DUR_LEN ;
        }
 
        return (sccp_init_timers (num_timers, timers, p_ecode)) ;
 
}
/* SPR 1272: End fix */

/*****************************************************************************
**      FUNCTION :
**         handles the get timer info API
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to get timer
**         info
**
*****************************************************************************/
 
return_t
sccp_sm_cmd_get_timer_info
#ifdef ANSI_PROTO
        (U8bit * p_api, error_t * p_ecode)
#else
        (p_api, p_ecode)
         U8bit          *p_api;
         error_t        *p_ecode;
#endif
{
	tmr_buffer_t    *timers = SS7_NULL;
	U8bit           num_entries;
	U8bit			entry_size;
	U8bit			nelem;
	s7_len_t		buf_len;
	U8bit			*p_buf = SS7_NULL;
	U8bit			*p_elem = SS7_NULL;
	U8bit			i;


	if ( sccp_prov_get_timer_info ((pvoid *) &timers, &num_entries, 
								  &entry_size, p_ecode)
			 == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get timer Info\n"));

	/* calculate the buffer length required */
	entry_size = SCCP_SM_TIMER_CONF_INFO_LEN;
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
				SCCP_ELEM_NUM_ENTRIES_LEN +
				SCCP_ELEM_ENTRY_SIZE_LEN +
				num_entries * entry_size;
	if (buf_len > SS7_MAX_BUFFER_SIZE)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	nelem = SCCP_SM_STD_RESP_MIN_NELEM + 3;
	/* SPR 9404 - Fix Start */
	/*sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);*/
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, (U8bit)buf_len);
	/* SPR 9404 - Fix End   */
				
	p_elem = p_buf + API_HEADER_LEN;
	p_api += API_HEADER_LEN;

	/* SM Header */
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
	*p_elem++ = SS7_SUCCESS;


	/* Timer Entries */

	*p_elem ++ = num_entries;
	*p_elem ++ = entry_size;
	
	for (i=0; i<num_entries; ++i)
	{
		*p_elem ++ = timers[i].timer_index;
		PUT_4_BYTE_LE(p_elem, timers[i].timer_value);
		p_elem += SCCP_SM_TIMER_DUR_LEN;
	}

	sccp_free ((buffer_t*)timers);
/* start added during CC compilation */
/* assign pvoid to buffe
r_t*  */
/* end added during CC compilation */

	sccp_sendto_sm(p_buf);

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         handles the configure signaling point command
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to add sp
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_conf_sp
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_sp_conf_info_t sp_info;
	U8bit * p_elem;
	return_t ret_val;
  U8bit SSF = 0;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	sp_info.sp_id = GET_BYTE_CODED_SP_ID(p_elem);
	p_elem += SCCP_SM_SP_ID_LEN;
	sp_info.nw_id = DEFAULT_NW_ID; /* sp_info.nw_id = *p_elem; */
/* Added by Amaresh start for value  NW-ID */	
	sp_info.nw_id = *p_elem; /* sp_info.nw_id = *p_elem; */
	sccp_nw_indicator = sp_info.nw_id;	
	SC_A_TRC (("SCCP::INIT: sccp_sm_cmd_conf_sp sp_info.nw_id %d sccp_nw_indicator %d\n",sp_info.nw_id,sccp_nw_indicator));
/* Added by Amaresh stop for value  NW-ID */	
	p_elem += SCCP_SM_NW_ID_LEN;
	
	sp_info.local = *p_elem;/* Local=1/Remote=0 */
	p_elem += 1;
		
	sp_info.pc = GET_BYTE_CODED_SM_PC(p_elem);
	p_elem += SCCP_SM_PC_LEN;

/* Added by Amaresh start for find SSF value from NW-ID */
	if(sp_info.nw_id == 0)
  {
      SSF = 0x00;
  }
  else if(sp_info.nw_id == 1)
  {
      SSF = 0x04;
  }
  else if(sp_info.nw_id == 2)
  {
      SSF = 0x08;
  }
  else if(sp_info.nw_id == 3)
  {
      SSF = 0x0c;
  }
/* Added by Amaresh stop for find SSF value from NW-ID */	

	sp_info.ssf = SSF; /**p_elem; Commented by Amaresh*/
	sp_info.nw_id = DEFAULT_NW_ID; /* sp_info.nw_id = *p_elem; */
	SC_A_TRC (("SCCP::INIT: sccp_sm_cmd_conf_sp sp_info.ssf %d sp_info.local %d sp_info.pc %d sp_info.nw_id %d \n",sp_info.ssf,sp_info.local,sp_info.pc,sp_info.nw_id));

	ret_val = sccp_prov_add_sp(&sp_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**        handles SM api to delete a signaling point
******************************************************************************
**
**      DESCRIPTION :
**         parses a command to and calls func to delete signaling point
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_del_sp
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_sp_del_info_t sp_info;
	U8bit * p_elem;
	U8bit flags;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	sp_info.sp_id = GET_BYTE_CODED_SP_ID(p_elem);
	p_elem += SCCP_SM_SP_ID_LEN;

	flags = *p_elem;
	(flags & DEL_SS_OF_SP_MASK) ? (sp_info.del_ss = SS7_TRUE) :
	                              (sp_info.del_ss = SS7_FALSE);

	(flags & DEL_SP_AS_CSP_MASK)? (sp_info.del_csp = SS7_TRUE) :
	                              (sp_info.del_csp = SS7_FALSE);

	ret_val = sccp_prov_del_sp (&sp_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         handles the get SP info API
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to get SP
**         info
**
*****************************************************************************/
/* Fix for SPR No: 13263  Start */
 
return_t
sccp_sm_cmd_get_sp_info
#ifdef ANSI_PROTO
        (U8bit * p_api, error_t * p_ecode)
#else
        (p_api, p_ecode)
         U8bit          *p_api;
         error_t        *p_ecode;
#endif
{
	sc_sp_conf_info_t    *sp_list = SS7_NULL;
	/* Fix for SPR No: 13263  Start */
	U32bit           num_entries;
	/* U8bit           num_entries;*/
	/* Fix for SPR No: 13263  end */
	U8bit			entry_size;
	U8bit			nelem;
	s7_len_t		buf_len;
	U8bit			*p_buf = SS7_NULL;
	U8bit			*p_elem = SS7_NULL;
	/* Fix for SPR No: 13263  Start */
    	U16bit                  i, no_of_segments;
    	U16bit                  max_buf_count;
    	U16bit                  num_entries_in_this_buf, j;
    	U32bit                  rem_num_entries;
    	U32bit                  entry_start_index=0, entry_num=0;
    	U8bit                   *p_temp_api;
	/* Fix for SPR No: 13263  end */




	if ( sccp_prov_get_sp_info ((pvoid *) &sp_list, &num_entries, 
								  &entry_size, p_ecode)
			 == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get SP Info\n"));

	/* calculate the buffer length required */
	entry_size = SCCP_SM_SP_CONF_INFO_LEN;
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
				SCCP_ELEM_NUM_ENTRIES_LEN +
				SCCP_ELEM_ENTRY_SIZE_LEN + 3 +
				num_entries * entry_size;

	/* Fix for SPR No: 13263  Start */

        if(((num_entries * entry_size ) % (SS7_MAX_BUFFER_SIZE -
                         (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                         + SCCP_ELEM_ENTRY_SIZE_LEN )))  == 0)
        {
                max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )));
                        if(num_entries == 0)
                                max_buf_count=1;
        }
        else
        {
                max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))) + 1 ;
        }
        rem_num_entries=num_entries;

        for(i=0;i< max_buf_count; i++)
        {
                if(i != max_buf_count -1 )
                {

                        num_entries_in_this_buf = ((SS7_MAX_BUFFER_SIZE -
                                                        (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))/entry_size);

                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (num_entries_in_this_buf * entry_size);
                        if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }
                        rem_num_entries = rem_num_entries - num_entries_in_this_buf;
                        entry_start_index = entry_num;
		}
                else
                {
                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (rem_num_entries * entry_size);

                        if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }

                        num_entries_in_this_buf = rem_num_entries;
                        entry_start_index = entry_num ;
                }

		p_temp_api = p_api;
		nelem = SCCP_SM_STD_RESP_MIN_NELEM + 3;

	/* SPR 9404 - Fix Start */
	/*sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);*/
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);
	/* SPR 9404 - Fix End   */
				
	p_elem = p_buf + API_HEADER_LEN;
	p_temp_api += API_HEADER_LEN;

	/* SM Header */
	*p_elem = *p_temp_api;            /* Category */
	p_temp_api  += SM_CATEGORY_LEN;
	p_elem += SM_CATEGORY_LEN;
	*p_elem = *p_temp_api;            /* Command */
	p_temp_api  += SM_COMMAND_LEN;
	p_elem += SM_COMMAND_LEN;
	*p_elem = *p_temp_api;            /* transaction id */
	p_temp_api  += SM_TRANS_ID_LEN;
	p_elem += SM_TRANS_ID_LEN;
	/* result of executing the SM command */
	*p_elem++ = SS7_SUCCESS;

                /* No of segments */
                no_of_segments = max_buf_count - i - 1; /* how many more segments to come */
                PUT_2_BYTE_LE(p_elem, no_of_segments);
                p_elem += 2;

                /* sp Entries */

                PUT_2_BYTE_LE(p_elem, num_entries_in_this_buf); /* num of entries in this buffer */
                p_elem += 2;

                *p_elem ++ = entry_size;  /* entry size*/

                for (j = (entry_start_index); j< (entry_start_index + num_entries_in_this_buf); ++j)
                {
                        PUT_4_BYTE_LE(p_elem, sp_list[j].sp_id);
                        p_elem += 4;
                        *p_elem ++ = sp_list[j].nw_id;
                        PUT_4_BYTE_LE(p_elem, sp_list[j].pc);
                        p_elem += 4;
                        *p_elem ++ = sp_list[j].local;
                        *p_elem ++ = sp_list[j].ssf;
                        entry_num ++;
                }

                sccp_sendto_sm(p_buf);

	}
	/* Fix for SPR No: 13263  end */

	if (sp_list != SS7_NULL)
		sccp_free ((buffer_t*)sp_list);
/* start added during CC compilation */
/* assign pvoid
 to buffer_t* */
/* end added during CC compilation */


	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         handles SM command to configure a subsystem
******************************************************************************
**
**      DESCRIPTION :
**         parse sm delete subsystem command and call function to configure
**         subsystem
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_conf_ss
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_ss_conf_info_t ss_info;
	U8bit * p_elem;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	ss_info.ss_id = GET_BYTE_CODED_SS_ID(p_elem);
	p_elem += SCCP_SM_SS_ID_LEN;
	ss_info.sp_id = GET_BYTE_CODED_SP_ID(p_elem);
	p_elem += SCCP_SM_SP_ID_LEN;
	ss_info.ssn = *p_elem;

	ret_val = sccp_prov_add_ss (&ss_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         handles SM command to delete a subsystem
******************************************************************************
**
**      DESCRIPTION :
**         parses the SM command and calls prov function to delete subsystem
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_del_ss
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_ss_del_info_t ss_info;
	U8bit * p_elem;
	U8bit flags;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	ss_info.ss_id = GET_BYTE_CODED_SS_ID(p_elem);
	p_elem += SCCP_SM_SS_ID_LEN;
	flags = *p_elem;

	(flags & DEL_SS_AS_CSS_MASK) ? (ss_info.del_css = SS7_TRUE) :
	                               (ss_info.del_css = SS7_FALSE);

	ret_val = sccp_prov_del_ss (&ss_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         handles the get SS info API
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to get SS
**         info
**
*****************************************************************************/
 
return_t
sccp_sm_cmd_get_ss_info
#ifdef ANSI_PROTO
        (U8bit * p_api, error_t * p_ecode)
#else
        (p_api, p_ecode)
         U8bit          *p_api;
         error_t        *p_ecode;
#endif
{
	sc_ss_conf_info_t    *ss_list = SS7_NULL;
	/* Fix for SPR No: 13263 start */
	U32bit           num_entries;
	/* U8bit           num_entries;*/
	/* Fix for SPR No: 13263 end */
	U8bit			entry_size;
	U8bit			nelem;
	s7_len_t		buf_len;
	U8bit			*p_buf = SS7_NULL;
	U8bit			*p_elem = SS7_NULL;
	/* Fix for SPR No: 13263 start */
    	U16bit                  no_of_segments, i;
        U16bit          	max_buf_count;
        U16bit                  num_entries_in_this_buf;
        U32bit                  rem_num_entries, j;
        U32bit                  entry_start_index=0,entry_num=0;
        U8bit                   *p_temp_api;
	/* Fix for SPR No: 13263 end */


	if ( sccp_prov_get_ss_info ((pvoid *) &ss_list, &num_entries, 
								  &entry_size, p_ecode)
			 == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get SS Info\n"));

	/* calculate the buffer length required */
	entry_size = SCCP_SM_SS_CONF_INFO_LEN;
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
				SCCP_ELEM_NUM_ENTRIES_LEN +
				SCCP_ELEM_ENTRY_SIZE_LEN + 3 +
				num_entries * entry_size;

        if(((num_entries * entry_size ) % (SS7_MAX_BUFFER_SIZE -
                                        (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3  
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )))  == 0)
        {
                max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )));
                if(num_entries == 0)
                        max_buf_count = 1;
        }
        else
        {
        max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))) + 1 ;
        }
        rem_num_entries=num_entries;

        for(i=0;i< max_buf_count; i++)
        {
        if(i != max_buf_count -1)
                {

            num_entries_in_this_buf = ((SS7_MAX_BUFFER_SIZE -
                                  (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                  + SCCP_ELEM_ENTRY_SIZE_LEN ))/entry_size);

                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (num_entries_in_this_buf * entry_size);
                        if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }
                        rem_num_entries = rem_num_entries - num_entries_in_this_buf;
                        entry_start_index = entry_num;

                }
                else
                {
                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (rem_num_entries * entry_size);

            		if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
            		{
                		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                		return SS7_FAILURE;
            		}

                        num_entries_in_this_buf = rem_num_entries;
                        entry_start_index = entry_num;

       		}

	
	p_temp_api = p_api;
	nelem = SCCP_SM_STD_RESP_MIN_NELEM + 3;
				
	/* SPR 9404 - Fix Start */
	/*sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);*/
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);

	/* SPR 9404 - Fix End   */
	p_elem = p_buf + API_HEADER_LEN;
	p_temp_api += API_HEADER_LEN;

	/* SM Header */
	*p_elem = *p_temp_api;            /* Category */
	p_temp_api  += SM_CATEGORY_LEN;
	p_elem += SM_CATEGORY_LEN;
	*p_elem = *p_temp_api;            /* Command */
	p_temp_api  += SM_COMMAND_LEN;
	p_elem += SM_COMMAND_LEN;
	*p_elem = *p_temp_api;            /* transaction id */
	p_temp_api  += SM_TRANS_ID_LEN;
	p_elem += SM_TRANS_ID_LEN;
	/* result of executing the SM command */
	*p_elem++ = SS7_SUCCESS;



        /* No of segments */
        no_of_segments = max_buf_count - i - 1; /* how many more segments to come */
	/* ss Entries */
        PUT_2_BYTE_LE(p_elem, no_of_segments);
        p_elem += 2;

        /* sp Entries */

        PUT_2_BYTE_LE(p_elem, num_entries_in_this_buf); /* num of entries in this buffer*/
        p_elem += 2;

        *p_elem ++ = entry_size;  /* entry size*/

            for (j = (entry_start_index); j< (entry_start_index + num_entries_in_this_buf); ++j)
            {
                    PUT_4_BYTE_LE(p_elem, ss_list[j].ss_id);
                    p_elem += 4;
                    PUT_4_BYTE_LE(p_elem, ss_list[j].sp_id);
                    p_elem += 4;
                    *p_elem ++ = ss_list[j].ssn;
                    entry_num++;
            }

	sccp_sendto_sm(p_buf);

	}


	if (ss_list != SS7_NULL)
		sccp_free ((buffer_t*)ss_list);
/* start added during CC compilation */
/* assign pvoid to buffe
r_t*  */
/* end added during CC compilation */

	/* Fix for SPR No: 13263 end */

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         handles SM command to configure a concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**         parse SM command and calls function to configure a concerned
**         subsystem

**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_conf_css
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_css_info_t css_info;
	U8bit * p_elem;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	css_info.ss_id = GET_BYTE_CODED_SS_ID(p_elem);
	p_elem += SCCP_SM_SS_ID_LEN;
	css_info.css_id = GET_BYTE_CODED_SS_ID(p_elem);

	ret_val = sccp_prov_add_css (&css_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         handles sm command to delete a concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**         parse SM command and call function to delete conc subsystem
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_del_css
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_css_info_t css_info;
	U8bit * p_elem;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	css_info.ss_id = GET_BYTE_CODED_SS_ID(p_elem);
	p_elem += SCCP_SM_SS_ID_LEN;
	css_info.css_id = GET_BYTE_CODED_SS_ID(p_elem);

	ret_val = sccp_prov_del_css (&css_info, p_ecode);

	return ret_val;	
}

/*****************************************************************************
**      FUNCTION :
**         handles the get CSS info API
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to get CSS
**         info
**
*****************************************************************************/
 
return_t
sccp_sm_cmd_get_css_info
#ifdef ANSI_PROTO
        (U8bit * p_api, error_t * p_ecode)
#else
        (p_api, p_ecode)
         U8bit          *p_api;
         error_t        *p_ecode;
#endif
{
	ss_id_t    		*css_list = SS7_NULL;
	/* Fix for SPR No: 13263 start */
	U32bit           num_entries;
	/* U8bit           num_entries; */
	/* Fix for SPR No: 13263 end*/
	U8bit			entry_size;
	U8bit			nelem;
	s7_len_t		buf_len;
	U8bit			*p_buf = SS7_NULL;
	U8bit			*p_elem = SS7_NULL;
	/* Fix for SPR No: 13263 start */
    	U16bit                  no_of_segments, i;
        U16bit          	max_buf_count;
        U16bit                  num_entries_in_this_buf;
        U32bit                  rem_num_entries, j;
        U32bit                  entry_start_index=0,entry_num=0;
        U8bit                   *p_temp_api;
	/* Fix for SPR No: 13263 end*/
	ss_id_t			ss_id;

	/* Extract ss id */
	p_elem = p_api + SS7_SM_API_MIN_LEN;
	ss_id = GET_4_BYTE_LE(p_elem);

	if ( sccp_prov_get_css_info (ss_id, (pvoid *) &css_list, &num_entries, 
								  &entry_size, p_ecode)
			 == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get CSS Info\n"));

	/* calculate the buffer length required */
	entry_size = SCCP_SM_CSS_CONF_INFO_LEN;
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
				SCCP_ELEM_NUM_ENTRIES_LEN +
				SCCP_ELEM_ENTRY_SIZE_LEN + 3 +
				num_entries * entry_size;
	/* Fix for SPR No: 13263 start */

            if(((num_entries * entry_size ) % (SS7_MAX_BUFFER_SIZE -
                                        (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )))  == 0)
        {
                max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )));
                if(num_entries == 0)
                                max_buf_count=1;
        }
        else
        {
        max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))) + 1 ;
        }
        rem_num_entries=num_entries;
        for(i=0;i< max_buf_count; i++)
        {
                if(i != max_buf_count -1)
                {

                        num_entries_in_this_buf = ((SS7_MAX_BUFFER_SIZE -
                                                        (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))/entry_size);

                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (num_entries_in_this_buf * entry_size);
                        if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }
                        rem_num_entries = rem_num_entries - num_entries_in_this_buf;
                        entry_start_index = entry_num;

                }
                else
                {
                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (rem_num_entries * entry_size);
                if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }

                        num_entries_in_this_buf = rem_num_entries;
                        entry_start_index = entry_num;

                }

	p_temp_api = p_api;
	nelem = SCCP_SM_STD_RESP_MIN_NELEM + 3;
				
	/* SPR 9404 - Fix Start */
	/*sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);*/
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);
	/* SPR 9404 - Fix End   */
	p_elem = p_buf + API_HEADER_LEN;
	p_temp_api += API_HEADER_LEN;

	/* SM Header */
	*p_elem = *p_temp_api;            /* Category */
	p_temp_api  += SM_CATEGORY_LEN;
	p_elem += SM_CATEGORY_LEN;
	*p_elem = *p_temp_api;            /* Command */
	p_temp_api  += SM_COMMAND_LEN;
	p_elem += SM_COMMAND_LEN;
	*p_elem = *p_temp_api;            /* transaction id */
	p_temp_api  += SM_TRANS_ID_LEN;
	p_elem += SM_TRANS_ID_LEN;
	/* result of executing the SM command */
	*p_elem++ = SS7_SUCCESS;

	/* No of segments */
	    	no_of_segments = max_buf_count - i - 1; /* how many more segments to come */
    		PUT_2_BYTE_LE(p_elem, no_of_segments);
    		p_elem += 2;

    		PUT_2_BYTE_LE(p_elem, num_entries_in_this_buf); /* num of entries in this buffer */
    		p_elem += 2;

		/* entry size*/
		*p_elem ++ = entry_size;
        /* No of segments  */

        for (j = (entry_start_index); j< (entry_start_index + num_entries_in_this_buf); ++j)
        {
                PUT_4_BYTE_LE(p_elem, css_list[j]);
                p_elem += 4;
                entry_num++;
        }
	
	sccp_sendto_sm(p_buf);

	}

	if (css_list != SS7_NULL)
		sccp_free ((buffer_t*)css_list);
/* start added during CC compilation */
/* assign pvoid to buffe
r_t*  */
/* end added during CC compilation */

	/* Fix for SPR No: 13263 end */

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**        handles SM command to configure concerned signaling point
******************************************************************************
**
**      DESCRIPTION :
**        parses SM command and calls prov func to configure conc sig. point
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_conf_csp
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_csp_info_t csp_info;
	U8bit * p_elem;
	return_t ret_val;
	U32bit t_reass,t_stat_info,t_cong_att,t_cong_dec,t_seg_param_z;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	csp_info.ss_id = GET_BYTE_CODED_SS_ID(p_elem);
	p_elem += SCCP_SM_SS_ID_LEN;
	csp_info.csp_id = GET_BYTE_CODED_SP_ID(p_elem);
	p_elem += SCCP_SM_SP_ID_LEN;
/* Added by Amaresh start as on dated 05_10_16 for Timer Update in CSP message */

	t_reass =  GET_4_BYTE_LE (p_elem); 
	p_elem += SCCP_SM_TIMER_DUR_LEN;

	t_stat_info =  GET_4_BYTE_LE (p_elem); 
	p_elem += SCCP_SM_TIMER_DUR_LEN;

	t_cong_att =  GET_4_BYTE_LE (p_elem); 
	p_elem += SCCP_SM_TIMER_DUR_LEN;

	t_cong_dec =  GET_4_BYTE_LE (p_elem); 
	p_elem += SCCP_SM_TIMER_DUR_LEN;

	t_seg_param_z =  GET_4_BYTE_LE (p_elem); 
	p_elem += SCCP_SM_TIMER_DUR_LEN;


		SC_IN_TRC (("SCCP::INIT: sccp_sm_cmd_conf_csp t_reass %d t_stat_info %d t_cong_att %d t_cong_dec %d t_seg_param_z %d ", t_reass,t_stat_info,t_cong_att,t_cong_dec,t_seg_param_z));


	  sccp_config_tmr_var(1, t_reass);
    sccp_config_tmr_var(2, t_stat_info);
    sccp_config_tmr_var(3, t_cong_att);
    sccp_config_tmr_var(4, t_cong_dec);
    sccp_config_tmr_var(5, t_seg_param_z);

/* Added by Amaresh stop as on dated 05_10_16 for Timer Update in CSP message */

	ret_val = sccp_prov_add_csp (&csp_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**        handles SM command to delete a concerned signaling point
******************************************************************************
**
**      DESCRIPTION :
**         parses SM command and calls function to delete conc sig point
**      NOTE :
**
*****************************************************************************/

return_t
sccp_sm_cmd_del_csp
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t * p_ecode)
#else
	(p_api, p_ecode)
	 U8bit 		*p_api;
	 error_t 	*p_ecode;
#endif
{
	sc_csp_info_t csp_info;
	U8bit * p_elem;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	csp_info.ss_id = GET_BYTE_CODED_SS_ID(p_elem);
	p_elem += SCCP_SM_SS_ID_LEN;
	csp_info.csp_id = GET_BYTE_CODED_SP_ID(p_elem);

	ret_val = sccp_prov_del_csp (&csp_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         handles the get CSP info API
******************************************************************************
**
**      DESCRIPTION :
**         parse the command into a structure and call function to get CSP
**         info
**
*****************************************************************************/
 
return_t
sccp_sm_cmd_get_csp_info
#ifdef ANSI_PROTO
        (U8bit * p_api, error_t * p_ecode)
#else
        (p_api, p_ecode)
         U8bit          *p_api;
         error_t        *p_ecode;
#endif
{
	sp_id_t    		*csp_list = SS7_NULL;
	/* Fix for SPR No: 13263 start */
	U32bit           num_entries;
	/* U8bit           num_entries;*/
	/* Fix for SPR No: 13263 end */
	U8bit			entry_size;
	U8bit			nelem;
	s7_len_t		buf_len;
	U8bit			*p_buf = SS7_NULL;
	U8bit			*p_elem = SS7_NULL;
	/* Fix for SPR No: 13263 start */
    	U16bit                  no_of_segments, i;
        U16bit          	max_buf_count;
        U16bit                  num_entries_in_this_buf;
        U32bit                  rem_num_entries, j;
        U32bit                  entry_start_index=0,entry_num=0;
        U8bit                   *p_temp_api;
	/* Fix for SPR No: 13263 end */
	ss_id_t			ss_id;

	/* Extract ss id */
	p_elem = p_api + SS7_SM_API_MIN_LEN;
	ss_id = GET_4_BYTE_LE(p_elem);


	if ( sccp_prov_get_csp_info (ss_id, (pvoid *) &csp_list, &num_entries, 
								  &entry_size, p_ecode)
			 == SS7_FAILURE)
	{
		return SS7_FAILURE;
	}

	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get CSP Info\n"));

	/* calculate the buffer length required */
	entry_size = SCCP_SM_CSP_CONF_INFO_LEN;
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
				SCCP_ELEM_NUM_ENTRIES_LEN +
				SCCP_ELEM_ENTRY_SIZE_LEN + 3 +
				num_entries * entry_size;
	/* Fix for SPR No: 13263 start */

            if(((num_entries * entry_size ) % (SS7_MAX_BUFFER_SIZE -
                                        (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )))  == 0)
        {
                max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN )));
                if(num_entries  == 0)
                        max_buf_count=1;
        }
        else
        {
        max_buf_count = ((num_entries*entry_size)/(SS7_MAX_BUFFER_SIZE -
                                                (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))) + 1 ;
        }
        rem_num_entries=num_entries;

        for(i=0;i< max_buf_count; i++)
        {
                if(i != max_buf_count - 1)
                {

                        num_entries_in_this_buf = ((SS7_MAX_BUFFER_SIZE -
                                                        (SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3
                                                        + SCCP_ELEM_ENTRY_SIZE_LEN ))/entry_size);

                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (num_entries_in_this_buf * entry_size);
                        if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }
                        rem_num_entries = rem_num_entries - num_entries_in_this_buf;
                        entry_start_index = entry_num;

                }
                else
		{
                        buf_len = SCCP_SM_STD_RESP_LEN + SCCP_ELEM_NUM_ENTRIES_LEN + 3 + SCCP_ELEM_ENTRY_SIZE_LEN + (rem_num_entries * entry_size);

                if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
                        {
                                *p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
                                return SS7_FAILURE;
                        }

                        num_entries_in_this_buf = rem_num_entries;
                        entry_start_index = entry_num;

                }

        p_temp_api = p_api;
	nelem = SCCP_SM_STD_RESP_MIN_NELEM + 3;
				
	/* SPR 9404 - Fix Start */
	/*sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);*/
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);
	/* SPR 9404 - Fix End   */
	p_elem = p_buf + API_HEADER_LEN;
	p_temp_api += API_HEADER_LEN;

	/* SM Header */
	*p_elem = *p_temp_api;            /* Category */
	p_temp_api  += SM_CATEGORY_LEN;
	p_elem += SM_CATEGORY_LEN;
	*p_elem = *p_temp_api;            /* Command */
	p_temp_api  += SM_COMMAND_LEN;
	p_elem += SM_COMMAND_LEN;
	*p_elem = *p_temp_api;            /* transaction id */
	p_temp_api  += SM_TRANS_ID_LEN;
	p_elem += SM_TRANS_ID_LEN;
	/* result of executing the SM command */
	*p_elem++ = SS7_SUCCESS;

    	no_of_segments = max_buf_count - i - 1; /* how many more segments to come */
    	PUT_2_BYTE_LE(p_elem, no_of_segments);
    	p_elem += 2;

    	/* csp Entries */

    	PUT_2_BYTE_LE(p_elem, num_entries_in_this_buf); /* num of entries in this buffer */
    	p_elem += 2;
	/* entry size*/
	*p_elem ++ = entry_size;

        for (j = (entry_start_index); j< (entry_start_index + num_entries_in_this_buf); ++j)
        {
                PUT_4_BYTE_LE(p_elem, csp_list[j]);
                p_elem += 4;
                entry_num++;
        }
		sccp_sendto_sm(p_buf);
	}

	if (csp_list != SS7_NULL)
		sccp_free ((buffer_t*)csp_list);
/* start added during CC compilation */
/* assign pvoid to buffe
r_t*  */
/* end added during CC compilation */

	/* Fix for SPR No: 13263 end */

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**        sccp_handle_add_back_up_ssn 
******************************************************************************
**
**      DESCRIPTION :
**         Configures the Back up of a sub system
**
*****************************************************************************/
#ifdef BACK_UP_SSN
return_t 
sccp_handle_add_back_up_ssn
#ifdef ANSI_PROTO
	(U8bit *p_api)
#else
	(p_api)
	U8bit *p_api;
#endif
{
	U8bit *pelem;
	U8bit nw_id;
	pc_t point_code;
	U8bit ssn;

	/** SPR 9302 Start Fix **/
	/* Boolean local; */
	/** SPR 9302 End Fix **/
	sp_entry_t *p_sp;
	

	pelem = p_api + SS7_SM_API_MIN_LEN;
	nw_id = *pelem;
	pelem++;
	point_code = GET_BYTE_CODED_SM_PC(pelem);
	pelem += 4;
	ssn = *pelem;
	pelem++;
	/*local = *pelem;*/
	p_sp = sccp_db_find_sp(nw_id, point_code);
	
	if(p_sp == SS7_NULL)
	{
/* SPR FIX 7890 start */
		SC_IN_TRC (("SCCP::INIT: Signaling point Not provisioned in database %u.", point_code));
/*SPR FIX 7890 end */
		return SS7_FAILURE;
	}
	else
	{
		if( (sccp_db_add_back_up_ss(ssn, point_code) == SS7_FAILURE))
			return SS7_FAILURE;
		return SS7_SUCCESS;
	}
}	
#endif
/*****************************************************************************
**      FUNCTION :
**         dsccp_sm_cmd_prov_comp_mate_status_info
******************************************************************************
**
**      DESCRIPTION :
**         When an instance comes up, SM sends it the status of all other
**	     DSCCP instances
**
*****************************************************************************/
#ifdef DISTRIBUTED_SCCP
return_t
dsccp_sm_cmd_prov_comp_mate_status_info
#ifdef ANSI_PROTO
	(U8bit *p_api, error_t *p_ecode)
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
	U8bit temp;
	extern U8bit dsccp_instance_status_tbl[DSCCP_MAX_INSTANCES];

	p_elem = p_api + DSCCP_DATA_OFFSET;
	temp = *p_elem++; 	
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
#endif

/* New Provisioning Functions --Sachin Bhatia */

/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_add_mtpsap
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_add_mtpsap
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	sccp_mtpsap_t mtpsap_info;
	U8bit * p_elem;
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	mtpsap_info = *p_elem; /* MTPSAP is one byte */

	ret_val = sccp_prov_add_mtpsap(mtpsap_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_del_mtpsap
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_del_mtpsap
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		        error_t *p_ecode;
#endif
{
	sccp_mtpsap_t mtpsap_info;
	U8bit * p_elem; 
	return_t ret_val;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	mtpsap_info = *p_elem; /* MTPSAP is one byte */

	ret_val = sccp_prov_del_mtpsap(mtpsap_info, p_ecode);

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**        sccp_sm_cmd_get_mtpsap_info
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_get_mtpsap_info
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	sccp_count_t   no_of_mtpsaps;
	sccp_mtpsap_t   *mtpsap_list;
	s7_len_t		buf_len;
	return_t ret_val;
	U8bit			*p_buf = SS7_NULL;
	U8bit			*p_elem = SS7_NULL;
	U8bit			i;
	U8bit			nelem;

	ret_val = sccp_prov_get_mtpsap_list (&no_of_mtpsaps, &mtpsap_list, p_ecode);
	if (ret_val == SS7_FAILURE)
	{
		return (SS7_FAILURE);
	}


	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get MTPSAP Info\n"));

	/* calculate the buffer length required */
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
				SCCP_ELEM_NUM_ENTRIES_LEN +
				(U8bit)(no_of_mtpsaps) ; /* 9 + num of mtpsap */
	if (buf_len > SS7_MAX_BUFFER_SIZE)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	nelem = SCCP_SM_STD_RESP_MIN_NELEM + 2;
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);
				
	p_elem = p_buf + API_HEADER_LEN;
	p_api += API_HEADER_LEN;

	/* SM Header */
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
	*p_elem++ = SS7_SUCCESS;


	/* MTP sap Entries */

	*p_elem ++ = (U8bit)no_of_mtpsaps ; /* MSB Contains the Result */
	
	for (i=0; i<no_of_mtpsaps; ++i)
	{
		*p_elem = mtpsap_list[i];
		p_elem += 1;
	}

	if (mtpsap_list != SS7_NULL)
		sccp_free ((buffer_t*)mtpsap_list);

	sccp_sendto_sm(p_buf);

	return ret_val;                    
}


/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_add_trans_rule
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_add_trans_rule
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	sccp_gti_t     gti;
	sccp_trans_fun_entry_t trans_func;
	sccp_count_t no_of_actions;
	sccp_action_t action_array[SCCP_MAX_ACTIONS_PER_RULE];
	sccp_trans_rule_id_t trans_rule_id;
	U8bit * p_elem; 
	U32bit index;
	/* SPR 9302 - Fix Start */
	/*sccp_count_t digit_length;*/
	U8bit digit_length;
	/*U8bit i, pos, var;*/
	U8bit i, pos;
	/* SPR 9302 - Fix End   */
        return_t ret_val;
        U8bit param = 0;
        Boolean put_param = SS7_FALSE;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	gti = *p_elem; 
	p_elem++;
	trans_func.tt = *p_elem; 
	p_elem++;
	trans_func.np = *p_elem; 
	p_elem++;
	trans_func.nai = *p_elem; 
	p_elem++;
	trans_func.es = *p_elem; 
	p_elem++;
	trans_func.escape_used = *p_elem; 
	p_elem++;
	trans_func.escape_code = *p_elem; 
	p_elem++;

	no_of_actions = *p_elem;
	p_elem++;


	trans_func.used = SCCP_TRANS_USED;
	for (index = 0; index < SCCP_MAX_RULES_PER_TRANS_FUN; index++)
		trans_func.array_trans_rules[index] = SCCP_TRANS_UNUSED;

	if (no_of_actions> SCCP_MAX_ACTIONS_PER_RULE)
	{
		/* *p_ecode = EGTT_ACTION_ARRAY_OVERFLOW; */ /* Set error here */
		return SCCP_FAILURE;
	}

	for (index = 0; index < no_of_actions; index++)
	{
		action_array[index].operation_code = *p_elem;
		p_elem++;
		action_array[index].min_digits = *p_elem;
		p_elem++;
		action_array[index].max_digits = *p_elem;
		p_elem++;
		action_array[index].skip_digits = *p_elem;
		p_elem++;
		action_array[index].escape_code = *p_elem;
		p_elem++;

		/* Mark the digits as invalid. */
		for (pos = 0; pos < SCCP_MAX_GT_DIGITS; pos++)
		{
			action_array[index].value[pos] = SCCP_FF;
		}

		/* Extracting digits for this rule now */
		/* It is not necessary that each rule has corrosponding 
		   digits with it. If a rule does not need digits,
		   this field should contain 0 --Sachin Bhatia*/


	       	/* Start extracting Value */
		digit_length = *p_elem;
		p_elem++;

		/*  If we have too many digits, fail */
/*		if (digit_length > SCCP_MAX_GT_DIGITS)
		{*/
			/* *p_ecode = EGTT_INVALID_NUMBER_OF_GT_DIGITS; */ /* Check Error Here */
		/*	return SCCP_FAILURE;
		}*/

		i = 0;
		/* SPR 10853 - Fix Start */
		action_array[index].value[i++] = digit_length;

		for (pos = 0; pos < ((digit_length + 1)/2); pos = pos + 1)
		{
			action_array[index].value[i++] = *(p_elem++);
		}
#if 0
		for (pos = 0; pos + 1 < digit_length; pos = pos + 2)
		{
			var = *p_elem;
			p_elem++;
			action_array[index].value[i++] = var & 0x0F;
			action_array[index].value[i++] = ((var & 0xF0) >> 4);
		}

		/* If the length is odd, we have one nibble left */
		if ((digit_length % 2) != 0)
		{
			var = *p_elem;
			p_elem++;
			action_array[index].value[i++] = var & 0x0F;
		}
#endif
		/* SPR 10853 - Fix End   */
	}


	ret_val = sccp_prov_add_trans_rule
		(gti, trans_func, no_of_actions, action_array, &trans_rule_id, p_ecode);
       if ( ret_val == SS7_SUCCESS )
            {
              put_param = SS7_TRUE;
              param = trans_rule_id;
              sccp_sm_cmd_std_resp(p_api, ret_val, param, put_param, *p_ecode);
            }

        

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_del_trans_rule
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_del_trans_rule
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	sccp_gti_t     gti;
	sccp_trans_fun_entry_t trans_func;
	sccp_trans_rule_id_t trans_rule_id;
	U8bit * p_elem; 

	memset(&trans_func,0,sizeof(sccp_trans_fun_entry_t));
	p_elem = p_api + SS7_SM_API_MIN_LEN;
	gti = *p_elem; 
	p_elem++;
	trans_func.tt = *p_elem; 
	p_elem++;
	trans_func.np = *p_elem; 
	p_elem++;
	trans_func.nai = *p_elem; 
	p_elem++;
	trans_func.es = *p_elem; 
	p_elem++;
	trans_func.escape_used = *p_elem; 
	p_elem++;
	trans_func.escape_code = *p_elem; 
	p_elem++;

	trans_rule_id = *p_elem;
	p_elem++;

	return (sccp_prov_del_trans_rule
		( gti, trans_func, trans_rule_id, p_ecode));
}

/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_get_trans_func_list_info
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_get_trans_func_list_info
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	sccp_gti_t     gti;
	sccp_count_t   no_of_trans_func;
	/* SPR 9302 - Fix Start */
	/*sccp_trans_fun_entry_t **fn_list;*/ /* Sachin - call memfree */
	sccp_trans_fun_entry_t **fn_list=SS7_NULL; /* Sachin - call memfree */
        /* Fix for SPR No: 12377 , CSR No : 1-755190 starts */
	sccp_trans_fun_entry_t *tmp_fn_list=SS7_NULL;
        /* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */
	/*int ** test;*/ /* Sachin test */
	/* SPR 9302 - Fix End   */
	U8bit *p_elem, *p_buf; 
	return_t ret_val;
	U8bit i, nelem;
	U32bit buf_len;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	gti = *p_elem; 
	p_elem++;

	/* Fix for SPR No: 12377 , CSR No : 1-755190 starts */
	no_of_trans_func = 0;

	fn_list = &tmp_fn_list;
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */

	ret_val = sccp_prov_get_trans_func_list
		(gti, &no_of_trans_func, fn_list, p_ecode);


	/* Fix for SPR No: 12377 , CSR No : 1-755190 starts */

	if (ret_val == SS7_FAILURE)
	{
                if (*fn_list != SS7_NULL)
                {
#if 0
		if (fn_list != SS7_NULL)
		{
			/* Check this Code --sachin bhatia */
			for (i=0; i<no_of_trans_func; ++i)
				sccp_free((buffer_t *)fn_list[i]);
			sccp_free((buffer_t *)fn_list);
		}
#endif
                        sccp_free((buffer_t *)*fn_list);
                }

		return (SS7_FAILURE);
	}
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */


	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get TRANS FUNC Info\n"));
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Starts */
#if 0
	/* calculate the buffer length required */
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
			SCCP_ELEM_NUM_ENTRIES_LEN +
			1 + /* for count */
			no_of_trans_func * sizeof(sccp_trans_fun_entry_t); 
#endif

        /* The buffer length required can be calculated by multiplying  no_of_trans_func with 6 
        *  The Magic figure 6 comes from length of translation_type ,Numbering_plan
        *  Nature_of_address_indicator , Encoding_scheme , Escape_used and Escape_code
        */
        buf_len =       SCCP_SM_STD_RESP_LEN +
                        SCCP_ELEM_NUM_ENTRIES_LEN +
                        (no_of_trans_func * 6);



	if (buf_len > SS7_MAX_BUFFER_SIZE)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
               if (*fn_list != SS7_NULL)
                {
#if 0
		if (fn_list != SS7_NULL)
		{
			/* Check this Code --sachin bhatia */
			for (i=0; i<no_of_trans_func; ++i)
				sccp_free((buffer_t *)fn_list[i]);
			sccp_free((buffer_t *)fn_list);
#endif
                        sccp_free((buffer_t *)*fn_list);
		}
		return SS7_FAILURE;
	}

	if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		if (*fn_list != SS7_NULL)
		{
#if 0
		if (fn_list != SS7_NULL)
		{
			/* Check this Code --sachin bhatia */
			for (i=0; i<no_of_trans_func; ++i)
				sccp_free((buffer_t *)fn_list[i]);
			sccp_free((buffer_t *)fn_list);
#endif
			sccp_free((buffer_t *)*fn_list);
		}
		return SS7_FAILURE;
	}
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */

	nelem = SCCP_SM_STD_RESP_MIN_NELEM + 2; /* 2 elements */
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          nelem, buf_len);
				
	p_elem = p_buf + API_HEADER_LEN;
	p_api += API_HEADER_LEN;

	/* SM Header */
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
	*p_elem++ = SS7_SUCCESS;


	/* MTP sap Entries */

	*p_elem ++ = no_of_trans_func;

	/* Fix for SPR No: 12377 , CSR No : 1-755190 Starts */
#if 0
	/* Put all the entries in the buffer */
	for (i=0; i<no_of_trans_func; ++i)
	{
		*p_elem = fn_list[i]->tt;
		p_elem++;
		*p_elem = fn_list[i]->np;
		p_elem++;
		*p_elem = fn_list[i]->es;
		p_elem++;
		*p_elem = fn_list[i]->nai;
		p_elem++;
		*p_elem = fn_list[i]->escape_used;
		p_elem++;
		*p_elem = fn_list[i]->escape_code;
		p_elem++;
	}
#endif
        /* Put all the entries in the buffer */
        for (i=0; i<no_of_trans_func; ++i)
        {
                *p_elem = (*fn_list + i)->tt;
                p_elem++;
                *p_elem = (*fn_list + i)->np;
                p_elem++;
                *p_elem = (*fn_list + i)->nai;
                p_elem++;
                *p_elem = (*fn_list + i)->es;
                p_elem++;
                *p_elem = (*fn_list + i)->escape_used;
                p_elem++;
                *p_elem = (*fn_list + i)->escape_code;
                p_elem++;
        }


	if (*fn_list != SS7_NULL)
	{
#if 0
	if (fn_list != SS7_NULL)
	{
		/* Check this Code --sachin bhatia */
		for (i=0; i<no_of_trans_func; ++i)
			sccp_free((buffer_t *)fn_list[i]);
		sccp_free((buffer_t *)fn_list);
#endif
		sccp_free((buffer_t *)*fn_list);
	}
	/* Fix for SPR No: 12377 , CSR No : 1-755190 Ends */

	sccp_sendto_sm(p_buf);

	return SS7_SUCCESS;
}


/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_add_to_dpc_ssn_table
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_add_to_dpc_ssn_table
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	U8bit  table_mask;
	U8bit   value[SCCP_MAX_GT_DIGITS];
	U8bit   ssn;
	sccp_count_t    dpc_count;
	sccp_mtpsap_t mtpsaps[SCCP_MAX_DPCS_PER_GT];
	U32bit  temp_dpc, dpcs[SCCP_MAX_DPCS_PER_GT];
	U8bit * p_elem;
	sccp_count_t digit_length;
	U8bit i, pos, var; 


	p_elem = p_api + SS7_SM_API_MIN_LEN;
	table_mask = *p_elem;
	p_elem++;


	/* Mark the digits as invalid. */
	for (pos = 0; pos < SCCP_MAX_GT_DIGITS; pos++)
	{
		value[pos] = SCCP_FF;
	}

	/* Extracting digits now */
	/* Start extracting Value */
	digit_length = *p_elem;
	p_elem++;

	/*  If we have too many digits, fail */
	if (digit_length > SCCP_MAX_GT_DIGITS)
	{
		/* *p_ecode = EGTT_INVALID_NUMBER_OF_GT_DIGITS; */ /* Check Error Here */
		return SCCP_FAILURE;
	}


	i = 0;
	value[i++] = digit_length;

	for (pos = 0; pos < ((digit_length + 1)/2); pos = pos + 1)
	{
		value[i++] = *(p_elem++);
	}
#if 0
	for (pos = 0; pos + 1 < digit_length; pos = pos + 2)
	{
		var = *p_elem;
		p_elem++;
		value[i++] = var & 0x0F;
		value[i++] = ((var & 0xF0) >> 4);
	}

	/* If the length is odd, we have one nibble left */
	if ((digit_length % 2) != 0)
	{
		var = *p_elem;
		p_elem++;
		value[i++] = var & 0x0F;
	}
#endif
	
	if(table_mask!=1)
	{
		/* Getting the DPC count */
		dpc_count = *p_elem;
		p_elem++;
	}
	else
	{
	dpc_count = 0;
	}

	for (pos = 0; pos < dpc_count; pos++)
	{
		mtpsaps[pos] = *p_elem;
		p_elem++;
		temp_dpc = GET_4_BYTE_LE(p_elem);
		dpcs[pos] = (U32bit)temp_dpc;
		p_elem+= sizeof(U32bit);
	}

	/* Now geeting the SSN */
	/* Note : this will be taken even if only DPC table is being used */
	ssn = *p_elem;
	p_elem++;

	return(sccp_prov_add_to_dpc_ssn_table
		(  table_mask, value, ssn, dpc_count, mtpsaps, dpcs, p_ecode));
	/* SPR 9302 - Fix Start */
	var = 0;
	/* SPR 9302 - Fix End   */
}


/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_del_from_dpc_ssn_table
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_del_from_dpc_ssn_table
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	U8bit  table_mask;
	U8bit   value[SCCP_MAX_GT_DIGITS];
	U8bit * p_elem;
	sccp_count_t digit_length;
	U8bit i, pos, var;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	table_mask = *p_elem;
	p_elem++;

	/* Mark the digits as invalid. */
	for (pos = 0; pos < SCCP_MAX_GT_DIGITS; pos++)
	{
		value[pos] = SCCP_FF;
	}

	/* Extracting digits now */
	/* Start extracting Value */
	digit_length = *p_elem;
	p_elem++;

	/*  If we have too many digits, fail */
	if (digit_length > SCCP_MAX_GT_DIGITS)
	{
		/* *p_ecode = EGTT_INVALID_NUMBER_OF_GT_DIGITS; */ /* Check Error Here */
		return SCCP_FAILURE;
	}

	i = 0;
	value[i++] = digit_length;

	for (pos = 0; pos < ((digit_length + 1)/2); pos = pos + 1)
	{
		value[i++] = *(p_elem++);
	}

#if 0
	for (pos = 0; pos + 1 < digit_length; pos = pos + 2)
	{
		var = *p_elem;
		p_elem++;
		value[i++] = var & 0x0F;
		value[i++] = ((var & 0xF0) >> 4);
	}

	/* If the length is odd, we have one nibble left */
	if ((digit_length % 2) != 0)
	{
		var = *p_elem;
		p_elem++;
		value[i++] = var & 0x0F;
	}
#endif


	return(sccp_prov_del_from_dpc_ssn_table
			(  table_mask, value, p_ecode));

	/* SPR 9302 - Fix Start */
	var = 0;
	/* SPR 9302 - Fix End   */

}

/*****************************************************************************
**      FUNCTION :
**       sccp_sm_cmd_get_rule_list_per_trans_func_info
******************************************************************************
**
**      DESCRIPTION :
**      Parses and calls appropriate function. 
**        
**
*****************************************************************************/
return_t
sccp_sm_cmd_get_rule_list_per_trans_func_info
#ifdef ANSI_PROTO
        (U8bit *p_api, error_t *p_ecode)
#else
	        (p_api, p_ecode)
	        U8bit *p_api;
		error_t *p_ecode;
#endif
{
	sccp_gti_t     gti;
	sccp_trans_fun_entry_t trans_func;
	sccp_count_t   no_of_rules = 0;
	sccp_get_trans_rule_t **trans_rule_list=SS7_NULL;
	U8bit *p_elem, *p_buf; 
	return_t ret_val;
	U8bit i, j, n_elem;
	U32bit buf_len;

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	gti = *p_elem; 
	p_elem++;
	memset(&trans_func,0,sizeof(sccp_trans_fun_entry_t));
	trans_func.tt = *p_elem;
	p_elem++;
	trans_func.np = *p_elem;
	p_elem++;
	trans_func.nai = *p_elem;
	p_elem++;
	trans_func.es = *p_elem;
	p_elem++;
	trans_func.escape_used = *p_elem;
	p_elem++;
	trans_func.escape_code = *p_elem;
	p_elem++;


	ret_val =  sccp_prov_get_rules_per_trans_func
		( gti, trans_func, &no_of_rules, trans_rule_list, p_ecode);


	if (ret_val == SS7_FAILURE)
	{
		return (SS7_FAILURE);
	}


	/* Build and send the response buffer */

	SC_STAT_API_INR_OUT_API_SM () ;
	SC_A_TRC (("SCCP::INIT: Building Response to Get RULES Info\n"));

	/* calculate the buffer length required */
	buf_len = 	SCCP_SM_STD_RESP_LEN + 
			SCCP_ELEM_NUM_ENTRIES_LEN +
			1 + /* for count */
			no_of_rules * sizeof(sccp_trans_rule_t); 

	if (buf_len > SS7_MAX_BUFFER_SIZE)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	if ((p_buf = sccp_malloc(buf_len)) == SS7_NULL)
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_FAILURE;
	}

	n_elem = SCCP_SM_STD_RESP_MIN_NELEM + 2; /* 2 elements */
	sccp_fill_api_header (p_buf, SCCP_SM_RESPONSE_API,
                          n_elem, buf_len);
				
	p_elem = p_buf + API_HEADER_LEN;
	p_api += API_HEADER_LEN;

	/* SM Header */
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
	*p_elem++ = SS7_SUCCESS;


	/* MTP sap Entries */

	*p_elem = no_of_rules;
	p_elem++;

    if(trans_rule_list != SS7_NULL) {
        for (i = 0; i < no_of_rules; i++)
        {
            /* Here we have to put one action_array element */
            *p_elem = trans_rule_list[i]->rule_id;
            p_elem++;

            /* Here we have to put one action_array element */
            /* Put action_count */
            *p_elem = trans_rule_list[i]->trans_rule.no_of_actions;
            p_elem++;

            /* Put action_list */
            for (j = 0; j < trans_rule_list[i]->trans_rule.no_of_actions; j++)
            {
                /* Put an element of action_list i.e. action */
                *p_elem = trans_rule_list[i]->trans_rule.action_list[j].operation_code;
                p_elem++;
                *p_elem = trans_rule_list[i]->trans_rule.action_list[j].min_digits;
                p_elem++;
                *p_elem = trans_rule_list[i]->trans_rule.action_list[j].max_digits;
                p_elem++;
                *p_elem = trans_rule_list[i]->trans_rule.action_list[j].skip_digits;
                p_elem++;
                *p_elem = trans_rule_list[i]->trans_rule.action_list[j].escape_code;
                p_elem++;
                sccp_memcpy(p_elem, trans_rule_list[i]->trans_rule.action_list[j].value, SCCP_MAX_GT_DIGITS);
                p_elem += SCCP_MAX_GT_DIGITS;
            }
        }
    }

	sccp_sendto_sm(p_buf);

	if (trans_rule_list !=SS7_NULL)
	{
		for (i = 0; i < no_of_rules; i++)
	        {
			sccp_free((buffer_t * )(trans_rule_list[i])); /* Check this Sachin Bhatia */
		}
		sccp_free((buffer_t *)trans_rule_list);
	}

	return SS7_SUCCESS;
}

/* New Provisioning funcs end here --Sachin Bhatia */


