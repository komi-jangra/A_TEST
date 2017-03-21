/***************************************************************************
**
**  FILE NAME:
**      dsccp_scmg.c
**
****************************************************************************
**
**  FUNCTION:
**		Contains functions for handling the SCMG messages from mate 
**		SCCP instances
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24August 2001 Pawanish Modi            Original
**  24October2001 Prateek Bidwalkar        Fixed SPR 6750
**  16November2001 Pawanish Modi        Fixed SPR 7090 and 7091
**  06March   2002 Sachin Bhatia        Added DEREG Functionality
**  03April   2002 Pawanish Modi        Fixed SPR 8615
**  18September	2002 Suyash Tripathi    Fixed SPR 10234
**  08September	2003 Salil Agrawal      Fixed SPR 12318
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

#include "dsccp_proc.h"

#include "sc_reg.h"

U8bit  dereg_mate_flag;


/***************************************************************************
**
**      FUNCTION :
**      dsccp_scmg_handle_sp_status  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_msg when a 
**      SCMG message for an SP from mate is received. It updates the status of
**	  an signalling point. If the status of SP is prohhibited, all the
**	  subsystems on the SP are also marked prohibited 
**
**      NOTE :
**
***************************************************************************/


void  
dsccp_scmg_handle_sp_status
#ifdef ANSI_PROTO
	(U8bit * p_info)
#else
	(p_info)
	U8bit *p_info;
#endif
{
	U8bit  * p_scmg_msg;
      U8bit  status;
	U32bit temp;
	sp_id_t sp_id;
      sp_entry_t *p_sp;
      U32bit i, num_ss;
      ss_entry_t *p_ss;
	U8bit upu_received, upu_cause;
	S8bit rl, rsl, cls, ril;
/* SPR 10234 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
/* SPR 10234 - Fix End   */


      p_scmg_msg = p_info+DSCCP_DATA_OFFSET;

	temp = (*p_scmg_msg )|(*(p_scmg_msg+1) << 8)| (*(p_scmg_msg+2) << 16) | (*(p_scmg_msg+3) << 24);

	/** SPR Fix 7090 Fix start **/

	sp_id = (sp_id_t)temp;

	/** SPR Fix 7090 Fix end **/

      p_scmg_msg += 4;

      status = *p_scmg_msg++;

	upu_received = *p_scmg_msg++;

	upu_cause = *p_scmg_msg++;

	rl = (S8bit)*p_scmg_msg++;

	rsl = (S8bit)*p_scmg_msg++;

	cls = (S8bit)*p_scmg_msg++;

	ril = (S8bit)*p_scmg_msg;

	p_sp = GET_SP_FROM_ID(sp_id);

      if ( SS7_NULL == p_sp )
            return;

      if(status == SP_INACCESSIBLE)
      {

            MARK_SP_PROHIBITED (p_sp);
#ifdef SCCP_REDN_ENABLED
		SCCP_SEND_SP_ENTRY_UPDATE(p_sp);
#endif

		if (! IS_SCCP_PROHIBITED(p_sp))
            {
                  MARK_SCCP_PROHIBITED (p_sp);
#ifdef SCCP_REDN_ENABLED
		SCCP_SEND_SP_ENTRY_UPDATE(p_sp);
#endif
/* SPR FIX 7890 starts */
                  MG_TRC (("SCCP::SCCP on pc %u nw_id %d: goes down\n",
                     GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
/*SPR FIX 7890 ends */

                  sccp_inform_trans_func(p_sp, SS7_NULL);
            }
			/** SPR Fix 8615 Start **/
			else
			{
				sccp_stop_sst (&p_sp->scmg_ss);
			}
			/** SPR Fix 8615 end **/

            for (i=0, num_ss = GET_NUM_SS_IN_SP(p_sp), p_ss = GET_SS_LIST_IN_SP(p_sp); i < num_ss; i++, p_ss = GET_NEXT_SS(p_ss))
            {
/* SPR FIX 7890 starts */

                  if (IS_SS_PROHIBITED(p_ss))
                  {
                        MG_TRC (("SCCP:: SSN %d on pc %u nw %d already down\n",GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
/*SPR FIX 7890 ends */
			/** SPR Fix 8615 Start **/
						sccp_stop_sst(p_ss);
			/** SPR Fix 8615 end **/

                  }
                  else
                  {
                        MARK_SS_PROHIBITED(p_ss);
#ifdef SCCP_REDN_ENABLED
				SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
#endif
/* SPR FIX 7890 starts */

                        MG_TRC (("SCCP:: SSN %d on pc %u nw %d goes down\n", GET_SS_SSN(p_ss), GET_SP_PC(p_sp), GET_SP_NW_ID(p_sp)));
/*SPR FIX 7890 ends */

				sccp_inform_trans_func (p_sp, p_ss);
                  }
            }
      }
      else
      {
		p_sp->upu_cause = upu_cause;
		p_sp->upu_received = upu_received;
		p_sp->rl = (S8bit)rl;
		p_sp->rsl = (S8bit)rsl;
		p_sp->cls = (S8bit)cls;
		p_sp->ril = (S8bit)ril;
            MARK_SP_ALLOWED(p_sp);
            MARK_SCCP_ALLOWED(p_sp);
#ifdef SCCP_REDN_ENABLED
		SCCP_SEND_SP_ENTRY_UPDATE(p_sp);
#endif
		/** SPR 7091 Fix start */
            sccp_inform_trans_func(p_sp, SS7_NULL);
		/** SPR 7091 Fix end */
		for (i=0, p_ss = GET_SS_LIST_IN_SP(p_sp); i < GET_NUM_SS_IN_SP(p_sp); i++, p_ss = GET_NEXT_SS(p_ss))
      	{
#ifdef MARK_SS_PROHIBITED_ON_RESUME
            	MARK_SS_PROHIBITED (p_ss);
            	SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
        		sccp_inform_trans_func (p_sp, p_ss);
            	p_ss->prev_t_stat_info_timer_val = sc_tim.t_stat_info_start_timer_val;

            	sccp_start_sst (p_ss);
#else
            	/** SST must always be started on Resume in case of BCGR **/
#if defined (SCCP_ITU) || defined(SCCP_JAPANESE)|| defined (SCCP_ETSI) || defined (SCCP_ANSI) || defined (SCCP_CHINESE)
            	if ((COMPARE_ITU) ||(COMPARE_JAPANESE)|| (COMPARE_ETSI) || (COMPARE_ANSI) || (COMPARE_CHINESE))
            	{
                  	MARK_SS_ALLOWED (p_ss);
                  	SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
                  	MG_TRC (("SCCP::SCMG : SSN %d on pc %u nw %d comes up\n",
                        	GET_SS_SSN(p_ss), GET_SP_PC(p_sp),
					GET_SP_NW_ID(p_sp)));
     
                  	sccp_stop_sst (p_ss);
            		/* SPR GR - inform translation function for SS */
            		sccp_inform_trans_func (p_sp, p_ss);
            	}
#endif
#if defined (SCCP_BCGR)
            	if (COMPARE_BCGR)
            	{
                  	MARK_SS_PROHIBITED (p_ss);
                  	SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
            		sccp_inform_trans_func (p_sp, p_ss);
                  	p_ss->prev_t_stat_info_timer_val =
                        	sc_tim.t_stat_info_start_timer_val;
                  	sccp_start_sst (p_ss);
            	}
#endif
#endif
      	}


      }

}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_scmg_handle_ss_status  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_msg when a 
**      SCMG message for an SS from mate is received The status of the
**	  Subsystem is updated. If the status is prohibited, then instance_id
**	  of the sending instance is stored in sst_instance_flag 
**
**      NOTE :
**
***************************************************************************/
void  
dsccp_scmg_handle_ss_status
#ifdef ANSI_PROTO
	(U8bit * p_info)
#else
	(p_info)
	U8bit *p_info;
#endif
{
	U8bit  * p_scmg_msg;
	dsccp_instance_id_t  instance_id;
	U32bit temp;
	ss_id_t ss_id;
	sp_id_t sp_id;
      U8bit  status;
      sp_entry_t *p_sp;
      ss_entry_t *p_ss;
	extern sc_opt_t sc_opt;
/* SPR 10234 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
/* SPR 10234 - Fix End   */

      p_scmg_msg = p_info+DSCCP_DATA_OFFSET;

	instance_id = (U8bit)*p_scmg_msg++;

	temp = (*p_scmg_msg )|(*(p_scmg_msg+1) << 8)| (*(p_scmg_msg+2) << 16) | (*(p_scmg_msg+3) << 24);

      p_scmg_msg += 4;

      status = *p_scmg_msg;

	ss_id = (ss_id_t)temp;

	p_ss = GET_SS_FROM_ID(ss_id);

	sp_id = p_ss->sp_id;

	p_sp = GET_SP_FROM_ID(sp_id);

	if(status == SCCP_USER_IN_SERVICE)
	{
            MARK_SS_ALLOWED(p_ss);
#ifdef SCCP_REDN_ENABLED
		SCCP_SEND_SS_ENTRY_UPDATE(p_ss);
#endif
		if (p_ss->sst_instance_id == sc_opt.dsccp_local_instance_id)
			sccp_stop_sst(p_ss);

	/** The field sst_instance_id contains the  DSCCP instance id which is doing a SST for the subsystem*/
		p_ss->sst_instance_id = DSCCP_INVALID_INSTANCE_ID;

	}
      else
	{
            MARK_SS_PROHIBITED(p_ss);
#ifdef SCCP_REDN_ENABLED
		SCCP_SEND_SS_ENTRY_UPDATE (p_ss);
#endif
		p_ss->sst_instance_id = instance_id;
	}
      sccp_inform_trans_func(p_sp, p_ss);
}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_scmg_handle_reg_status  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_msg when a 
**      Register user message for an SS from mate is received. Whenaver
**	  a user registers with a DSCCP instance, it informs all other DSCCP
**	  instances.
**
**      NOTE :
**
***************************************************************************/
void 
dsccp_scmg_handle_reg_status
#ifdef ANSI_PROTO
	(U8bit * p_info)
#else
	(p_info)
	U8bit *p_info;
#endif
{
	sp_id_t sp_id;
	U8bit ssn;
	U16bit log_user_id;
	U32bit temp;
	U8bit *p_elem;
	sp_entry_t *p_sp;
	ss_entry_t *p_ss;
	Boolean found = SS7_FALSE;
	sc_reg_entry_t *p_sccp_reg;
  	U8bit         count ;
/* SPR 10234 - Fix Start */
#ifdef SCCP_REDN_ENABLED
	extern U8bit sccp_state;
#endif
/* SPR 10234 - Fix End   */

	

	p_elem = p_info + DSCCP_DATA_OFFSET;

	temp = (*p_elem )|(*(p_elem+1) << 8)| (*(p_elem+2) << 16) | (*(p_elem+3) << 24);

      p_elem += 4;

	ssn = *p_elem++;

	log_user_id = GET_2_BYTE_LE(p_elem);		

	sp_id = (sp_id_t)temp;

	p_sp = GET_SP_FROM_ID(sp_id);
	
	for (count = 0; count < MAX_LOCAL_USERS; count++)
  	{
    		p_sccp_reg = &sccp_reg_table [count] ;

    		if ((p_sccp_reg->uid == log_user_id) && (p_sccp_reg->registered == SS7_TRUE))
    		{
            	if (p_sccp_reg->ssn == ssn)
            	{
                  	MG_TRC(("SCCP::SCMG: " "User LogUid[%d] already registered with SSN[%d]\n", log_user_id, ssn));
                  	return;
            	}
    		}
  	}
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
    		return;
  	}
	if (ssn != 0x00)
  	{
    		if (SS7_NULL == (p_ss = sccp_db_find_ss(p_sp, ssn)))
    		{
      		MG_TRC(("SCCP :: SCMG : Unequipped user SSN %d PC %d registers." " ignored\n", ssn,p_sp->pc ));
		 	SC_A_ERR (ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE);

      		return;
    		}
		if ( ! IS_SS_LOCAL(p_ss))
    		{
      		MG_TRC(("SCCP :: SCMG : Non local user SSN %d PC %d registers." " Ignored\n", ssn, p_sp->pc));
      		SC_A_ERR (ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE);

      		return;
    		}
		p_ss->dst_id = log_user_id;
		p_ss->registered = SS7_TRUE;
		MARK_SS_ALLOWED(p_ss);
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

#ifdef SCCP_REDN_ENABLED
  	SCCP_SEND_REG_ENTRY_UPDATE (p_sccp_reg);
#endif

  return ;
}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_scmg_handle_dereg_status  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_msg when a 
**      De-Register user message for an SS from mate is received. Whenaver
**	  a user registers with a DSCCP instance, it informs all other DSCCP
**	  instances.
**
**      NOTE :
**
***************************************************************************/
void 
dsccp_scmg_handle_dereg_status
#ifdef ANSI_PROTO
	(U8bit * p_info)
#else
	(p_info)
	U8bit *p_info;
#endif
{
	sp_id_t sp_id;
	U8bit ssn;
	U16bit log_user_id;
	U32bit temp;
	U8bit *p_elem;
	U8bit *p_dereg_buffer;
	sp_entry_t *p_sp;

	

	p_elem = p_info + DSCCP_DATA_OFFSET;

	temp = (*p_elem )|(*(p_elem+1) << 8)| (*(p_elem+2) << 16) | (*(p_elem+3) << 24);

    p_elem += 4;

	ssn = *p_elem++;

	log_user_id = GET_2_BYTE_LE(p_elem);		

	sp_id = (sp_id_t)temp;

	p_sp = GET_SP_FROM_ID(sp_id);
	
	/* Now we create a buffer for De-Reg Api */
#if defined(SCCP_ITU) || defined(SCCP_JAPANESE)
    if(COMPARE_ITU || COMPARE_JAPANESE)
	{
/* spr 12318 starts */
		p_dereg_buffer = (U8bit *)sccp_malloc(10);
    	if(p_dereg_buffer == SS7_NULL)
      	{
            return ;
      	}
/* spr 12318 ends */
		p_dereg_buffer[0]=SCCP_DEREGISTER_USER;
		p_dereg_buffer[1]=0x01;
		p_dereg_buffer[2]=0x03;
		p_dereg_buffer[3]=0x0a;
		p_dereg_buffer[4]=0x00;
		p_dereg_buffer[5]=(U8bit)(p_sp->pc);
		p_dereg_buffer[6]=(U8bit)(p_sp->pc>>8);
		p_dereg_buffer[7]=ssn;
		p_dereg_buffer[8]=(U8bit)log_user_id;
		p_dereg_buffer[9]=(U8bit)(log_user_id>>8);
	}
#endif

	
#if defined(SCCP_CHINESE) || defined(SCCP_ANSI)
    if(COMPARE_CHINESE || COMPARE_ANSI)
	{
/* spr 12318 starts */
		p_dereg_buffer = (U8bit *)sccp_malloc(11);
    	if(p_dereg_buffer == SS7_NULL)
      	{
            return ;
      	}
/* spr 12318 ends */

		p_dereg_buffer[0]=SCCP_DEREGISTER_USER;
		p_dereg_buffer[1]=0x01;
		p_dereg_buffer[2]=0x03;
		p_dereg_buffer[3]=0x0b;
		p_dereg_buffer[4]=0x00;
		p_dereg_buffer[5]=(U8bit)(p_sp->pc);
		p_dereg_buffer[6]=(U8bit)(p_sp->pc>>8);
		p_dereg_buffer[7]=(U8bit)(p_sp->pc>>16);
		p_dereg_buffer[8]=ssn;
		p_dereg_buffer[9]=(U8bit)log_user_id;
		p_dereg_buffer[10]=(U8bit)(log_user_id>>8);
	}
#endif
	
	/* Flag that this de-reg is from mate so that 
	we can avoid sending SSP etc again */
	dereg_mate_flag = 1;

	sccp_deregister_user(p_dereg_buffer);
	
	ss7_mem_free(p_dereg_buffer);
	return ;
}

/***************************************************************************
**
**      FUNCTION :
**      dsccp_scmg_handle_scmg_status  
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the dsccp_process_msg when a 
**      SCMG message for a peer SCCP from mate is received The status of the
**	  SCCP is updated. If the status is prohibited, then instance_id
**	  of the sending instance is stored in sst_instance_flag 
**
**      NOTE :
**
***************************************************************************/
void  
dsccp_scmg_handle_scmg_status
#ifdef ANSI_PROTO
	(U8bit * p_info)
#else
	(p_info)
	U8bit *p_info;
#endif
{
	U8bit  * p_scmg_msg;
	dsccp_instance_id_t  instance_id;
	U32bit temp;
/* SPR FIX 7890 starts */
	/* ss_id_t ss_id; */
 /*SPR FIX 7890 ends */
	sp_id_t sp_id;
      U8bit  status;
      sp_entry_t *p_sp;
	U8bit upu_recd;
	extern sc_opt_t sc_opt;


      p_scmg_msg = p_info+DSCCP_DATA_OFFSET;

	temp = (*p_scmg_msg )|(*(p_scmg_msg+1) << 8)| (*(p_scmg_msg+2) << 16) | (*(p_scmg_msg+3) << 24);

	sp_id = (sp_id_t)temp;

	p_scmg_msg += 4;

      status = *p_scmg_msg++;

      upu_recd = *p_scmg_msg++;

	instance_id = (U8bit)*p_scmg_msg;

	p_sp = GET_SP_FROM_ID(sp_id);

	if(status == SCCP_REMOTE_SCCP_AVAILABLE)
	{
            MARK_SCCP_ALLOWED(p_sp);
		if (p_sp->scmg_ss.sst_instance_id == sc_opt.dsccp_local_instance_id)
			sccp_stop_sst(&(p_sp->scmg_ss));

		p_sp->scmg_ss.sst_instance_id = DSCCP_INVALID_INSTANCE_ID;

	}
	else
	{
            MARK_SCCP_PROHIBITED(p_sp);

		p_sp->scmg_ss.sst_instance_id = instance_id;
	}
      sccp_inform_trans_func(p_sp, SS7_NULL);
}
#else /* DISTRIBUTED_SCCP */

/*****************************************************************************
**  This extern declaration is required as ANSI C does not allow an empty 
**  source file. This declaration enables compilation without DISTRIBURTED_SCCP 
**  flag .
*****************************************************************************/

extern return_t dsccp_dummy _ARGS_ ((void));



#endif /* end DISTRIBUTED SCCP */
