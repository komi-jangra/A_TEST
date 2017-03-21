/***************************************************************************
**
**  FILE NAME:
**      sc_reg.c
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  08Sep2003 Salil Agrawal           Fixed SPR 12318
**  08Sep2003 Salil Agrawal           Fixed SPR 12317
**  25Jul2002 Salil Agrawal           Fixed SPR 9361
**  23July02  Suyash Tripathi         Fixed SPR 9302         
**  21June02  Salil Kumar Agrawal     Added register_resp API
**  26June02  Salil Kumar Agrawal     Added MTP3_register_api
**  30Apr2002 Sachin Bhatia           Fixed SPR 8688 / 8689 
**  14Nov2002 Pawanish Modi         Fixed SPR 10610  
**  18Jun2002 Suyash Tripathi         Fixed SPR 8985  
**  18Feb2002 Sachin Bhatia           Added De-Regn Functions	
**  24Oct2001 Prateek Bidwalkar       Fixed SPR 6750
**  29Feb2000 Ramu Kandula            Fixed SPR 2778
**  19Feb2000 Ramu Kandula            Fixed SPR 2632
**  29Apr99  Sudipta Pattar    -----  Fixed SPR 1503
**  20May98  Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"

#include "sc_reg.h"
/* SPR # 6750 Fix Start */
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#include "dsccp_proc.h"
#endif
/* SPR # 6750 Fix End */

sc_reg_entry_t sccp_reg_table[MAX_LOCAL_USERS];

/* SPR 9302 - Fix Start */
/* Protoypes already declared in sc_reg.h */
/*void sccp_register_ssn
  _ARGS_ ((ss_id_t ss_id, U16bit uid));

void sccp_deregister_ssn
  _ARGS_ ((ss_id_t ss_id, U16bit uid));*/
/* SPR 9302 - Fix End   */

#ifdef DISTRIBUTED_SCCP
extern U8bit sccp_state;
extern U8bit dereg_mate_flag;
#endif

/***************************************************************************
**
**      FUNCTION :
**         handles a user register API
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/
/* changes done by salil for register response to user */
/* void  */
return_t
sccp_register_user  
#ifdef ANSI_PROTO
  (U8bit   * p_api,error_t *p_ecode)
#else
  (p_api, p_ecode)
  U8bit  * p_api ;
  error_t *p_ecode ;
#endif
{
  scmg_info_t   info, * p_info = &info;
  Boolean       found = SS7_FALSE ;
  sc_reg_entry_t *p_sccp_reg;
  U8bit         count ;
#ifdef SCCP_REDN_ENABLED
  extern U8bit sccp_state;
#endif

  SC_A_TRC (("SCCP :: SCMG : recvd register user\n"));

  sccp_parse_sccp_reg_api (p_api, p_info);

  /* spr 12317 starts */
  if (p_info->uid <= 3) 
  {	
	MG_TRC(("SCCP::SCMG: "
			"User LogUid should be greater than 3\n"));
	return SS7_FAILURE;
  }

  if (p_info->uid == 6)
  {	
	MG_TRC(("SCCP::SCMG: "
			"User LogUid[6] is reserved for System Management Entity\n"));
	return SS7_FAILURE;
  }
  /* spr 12317 ends */


  /* check if User already registered */
  for (count = 0; count < MAX_LOCAL_USERS; count++)
  {
    p_sccp_reg = &sccp_reg_table [count] ;
#if 0
    if ( (p_sccp_reg->uid == p_info->uid) && 
        (p_sccp_reg->registered == SS7_TRUE))
#endif
	/* Changed to allow unique SSN in Regn  */
    if (p_sccp_reg->registered == SS7_TRUE)
    {
		/** SPR # 2778 Fix Start **/
		if (p_sccp_reg->ssn == p_info->ssn)
		{
      		MG_TRC(("SCCP::SCMG: "
				"User LogUid[%d] already registered with SSN[%d]\n",
                p_sccp_reg->uid, p_sccp_reg->ssn));
            *p_ecode = ESCCP_LOG_USER_ID_ALREADY_EXIST;
      		/* return; */

/** SPR Fix 10610 fix start **/
#ifdef DISTRIBUTED_SCCP
			dsccp_send_reg_user_msg_to_mates(p_sccp_reg);
#endif
/** SPR Fix 10610 fix end **/
            return SS7_FAILURE;
		}
		/** SPR # 2778 Fix End **/
    }

#if 0
/* This section has been commented so as to let the multiple applications *
**get registered with the same log user id */
	/* Fix of SPR /8689/8688 Start  Sachin Bhatia*/
	/* Check for repetetion of SSN or Log ID */

	if (((p_sccp_reg->uid == p_info->uid) || (p_sccp_reg->ssn == p_info->ssn)) &&
        (p_sccp_reg->registered == SS7_TRUE))
    {
      		MG_TRC(("SCCP::SCMG: "
				"User LogUid[%d] already registered with SSN[%d]\n",
                p_sccp_reg->uid, p_sccp_reg->ssn));
            *p_ecode = ESCCP_LOG_USER_ID_ALREADY_EXIST;
            /* return; */
            return SS7_FAILURE;
    }
#endif /* end of if 0 */


  }


  /* Take a new register for registering the user */
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
    MG_TRC(("SCCP::SCMG: Max Limit reached. Could not register. "
                "User LogUid[%d] unable to registered with SSN[%d]\n",
                p_info->uid, p_info->ssn));
    /* return; */
    *p_ecode = ESCCP_MAX_SSN_EXCEEDED ;
    return SS7_FAILURE;
  }

  if (SS7_NULL == (p_info->p_sp = sccp_db_find_sp(p_info->nw_id, p_info->pc)))
  {
    MG_TRC(("SCCP :: SCMG : Unequipped user SSN %d PC %d registers."
            " ignored\n", p_info->ssn, p_info->pc));
    SC_A_ERR (ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE);

    /* return; */
    *p_ecode = ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE ;
    return SS7_FAILURE;
  }

  if (p_info->ssn != 0x00)
  {
    if (SS7_NULL == (p_info->p_ss = sccp_db_find_ss(p_info->p_sp, p_info->ssn)))
    {
      MG_TRC(("SCCP :: SCMG : Unequipped user SSN %d PC %d registers."
               " ignored\n", p_info->ssn, p_info->pc));
      SC_A_ERR (ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE);
      *p_ecode = ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE ;
      /* return; */
      return SS7_FAILURE;
    }

    if ( ! IS_SS_LOCAL(p_info->p_ss))
    {
      MG_TRC(("SCCP :: SCMG : Non local user SSN %d PC %d registers."
             " Ignored\n", p_info->ssn, p_info->pc));
      SC_A_ERR (ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE);
      *p_ecode = ESCCP_UNEQUIPPED_USER_DESIRES_SERVICE ;
      /* return; */
      return SS7_FAILURE;
    }

    sccp_register_ssn (GET_ID_FROM_SS(p_info->p_ss), p_info->uid);

	/** SPR # 2632 Fix start **/
	sccp_inform_trans_func (p_info->p_sp, p_info->p_ss);
	/** SPR # 2632 Fix End **/
  }

  p_sccp_reg->registered = SS7_TRUE;
  p_sccp_reg->ssn        = p_info->ssn;
  p_sccp_reg->uid        = p_info->uid;
  p_sccp_reg->p_sp       = p_info->p_sp;
  if (p_info->ssn != 0x00)
    p_sccp_reg->p_ss = p_info->p_ss;
  else
    p_sccp_reg->p_ss = (ss_entry_t *)SS7_NULL;

  SCCP_SEND_REG_ENTRY_UPDATE (p_sccp_reg);/* start added during CC compilation */
/* function must be prototype */
/* end added during CC com
pilation */
  
#ifdef DISTRIBUTED_SCCP
	dsccp_send_reg_user_msg_to_mates(p_sccp_reg);
#endif

  /* return ; */
    return SS7_SUCCESS;
}
/* end */

#if 0
/* added by salil to add register resp functionality */
/***************************************************************************
**
**      FUNCTION :
**         handles a user register API
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/
void
sccp_register_resp
#ifdef ANSI_PROTO
  (U8bit *p_api,return_t ret_val, error_t p_ecode)
#else
  (p_api,ret_val,ecode)
  U8bit  *p_api ;
  return_t ret_val;
  error_t ecode;
#endif
{
    U8bit * p_buf, * p_elem, nelem, buff_len ;
    error_t p_ecode ;
    
#ifdef SCCP_TRACE_ENABLED
    S8bit * p_trstr = (S8bit *)"response to SCUSER";
#endif 
    SC_A_TRC (("SCCP::SCMG: Building %s\n", p_trstr));
    if (ret_val == SS7_FAILURE)
    {
        buff_len = API_HEADER_LEN + 1 + 2;
        nelem = 2 ;
    }
    else
    {
        buff_len = API_HEADER_LEN + 1;
        nelem = 1;
    }
    
    if (SS7_NULL == (p_buf = sccp_malloc(buff_len)))
    {
        SC_A_TRC (("SCCP::SCMG: Cannot %s\n", p_trstr));
        return ;
    }
    sccp_fill_api_header (p_buf, SCCP_REG_RESPONSE_API,nelem,buff_len);
    p_elem = p_buf + API_HEADER_LEN;
    *p_elem = ret_val;
    if (ret_val == SS7_FAILURE)
    {
        p_elem ++;
        *p_elem++ = (U8bit)ecode;
        *p_elem++ = (U8bit)(ecode >> 8);
    }
    SC_A_TRC (("SCCP::SCMG: Built %s\n", p_trstr));
    p_elem = p_api + API_HEADER_LEN + PC_SIZE + 1;
    dst_id 
    if (SS7_FAILURE == send_from_sccp(p_buf,GET_API_LEN(p_buf),SCCP_MODULE_ID, /* put destination id */ ,&p_ecode))
    {
        sccp_free(p_buf);
    }
}
/* end */
#endif

/***************************************************************************
**
**      FUNCTION :
**         handles a sccp - MTP3 register API
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/
return_t
sccp_mtp3_register_req
#ifdef ANSI_PROTO
    (U8bit sio, U32bit log_user_id)
#else
    (sio,log_user_id)
    U8bit sio;
    U32bit log_user_id;
#endif
{
    U8bit * p_buf, * p_elem, nelem, buff_len ;
    error_t p_ecode ;
#ifdef SCCP_TRACE_ENABLED
    S8bit * p_trstr = (S8bit *)"REGISTER REQUEST to MTP3";
#endif 
    SC_A_TRC (("SCCP::SCMG: Building %s\n", p_trstr));
    
    buff_len = API_HEADER_LEN + 1 + 4; 
    /* 1 is size of sio and 4 is size of log user id */
    nelem = 2; 
    
    if (SS7_NULL == (p_buf = sccp_malloc(buff_len)))
    {
        SC_A_TRC (("SCCP::SCMG: Cannot %s\n", p_trstr));
        return SS7_FAILURE;
    }
    sccp_fill_api_header (p_buf, MTP3_UP_REGISTER_USER_PART,nelem,buff_len);
    p_elem = p_buf + API_HEADER_LEN;
    *p_elem++ = sio ;
    *p_elem++ = (U8bit )(log_user_id);
    *p_elem++ = (U8bit )(log_user_id >> 8);
    *p_elem++ = (U8bit )(log_user_id >> 16);
    *p_elem   = (U8bit )(log_user_id >> 24);
    
    SC_A_TRC (("SCCP::SCMG: Built %s\n", p_trstr));
    
    if (SS7_FAILURE == send_from_sccp(p_buf,GET_API_LEN(p_buf),SCCP_MODULE_ID,MTP3_MODULE_ID,&p_ecode))
    {
        sccp_free(p_buf);
        return SS7_FAILURE;
    }
    return SS7_SUCCESS;
}

/***************************************************************************
**
**      FUNCTION :
**         handles a user deregister API
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void
sccp_deregister_user
#ifdef ANSI_PROTO
  (U8bit   * p_api)
#else
  (p_api)
  U8bit  * p_api ;
#endif
{
  scmg_info_t   info, * p_info = &info;
  Boolean       found = SS7_FALSE ;
  sc_reg_entry_t *p_sccp_reg;
  U8bit         count;
  U8bit         *n_dis_buffer ;
#ifdef SCCP_REDN_ENABLED
  extern U8bit sccp_state;
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
/* changes for 256 K Connections */
  /* U16bit         conn_count; */
  U32bit         conn_count;
  error_t     ecode ;
  return_t    result ;
  msg_info_t  dis_info ;
#endif
/* spr 12318 starts */
  n_dis_buffer = (U8bit *)sccp_malloc(10);
  if (n_dis_buffer ==  SS7_NULL)
  {
	return ;
  }
/* spr 12318 ends */

  SC_A_TRC (("SCCP :: SCMG : Recvd De-Register user\n"));

  /* API structure is same as reg user so we can use this function here */
  sccp_parse_sccp_reg_api (p_api, p_info);

  /* check if User already registered */
  for (count = 0; count < MAX_LOCAL_USERS; count++)
  {
    p_sccp_reg = &sccp_reg_table [count] ;
    if ((p_sccp_reg->uid == p_info->uid) &&
        (p_sccp_reg->registered == SS7_TRUE))
    {
        if ((p_sccp_reg->ssn == p_info->ssn) && (p_sccp_reg->p_sp->pc == p_info->pc))
        {
			/* We have such a user Registered with us */
			found=SS7_TRUE;
			break;
        }
    }
  }
  
    /* No Registered user found */
  	if(found==SS7_FALSE)
	{
		SC_A_TRC (("SCCP :: SCMG : Trying to De-Register an Unregistered  user\n"));
		/* starts SPR # 9361 */	
		ss7_mem_free(n_dis_buffer);
		/* end  SPR # 9361 */	
		return;
	}

#ifdef DISTRIBUTED_SCCP
	if(!dereg_mate_flag && (sccp_state != DEINITIALIZING))
	{
    	dsccp_send_dereg_user_msg_to_mates(p_sccp_reg);
	}
#endif

	/* Do actual work here */
	/* For All Established Connections Check and send N_Disconnect_Req*/

#ifdef SCCP_INCLUDE_CO_SERVICE
  dis_info.p_api = n_dis_buffer ;

	n_dis_buffer[0] = SCCP_N_DISCONNECT_REQUEST;
	n_dis_buffer[1] = 0x01;
	n_dis_buffer[2] = 0x02;
#ifdef SCCP_CONNECTION_ID_CHANGES
	n_dis_buffer[3] = 0x0a;
	n_dis_buffer[4] = 0x00;
/* Currently fill the conn id to be 0 */
	n_dis_buffer[5] = 0x00;
	n_dis_buffer[6] = 0x00;
	n_dis_buffer[7] = 0x00;
	n_dis_buffer[8] = 0x00;
	n_dis_buffer[9] = 0x01;
#else
	n_dis_buffer[3] = 0x08;
	n_dis_buffer[4] = 0x00;
/* Currently fill the conn id to be 0 */
	n_dis_buffer[5] = 0x00;
	n_dis_buffer[6] = 0x00;
	n_dis_buffer[7] = 0x01;
#endif


	/* For All CCB check which are for this ss */
	for(conn_count = 0; conn_count < MAX_SCCP_CO_CONNECTIONS; conn_count++)
	{
		if((sccp_ccb[conn_count].l_id == p_info->uid) && (sccp_ccb[conn_count].c_state == SCCP_CONN_ESTABLISHED))
		{
			/* We have to Free this Connection */
			dis_info.event = SCCP_N_DISCONNECT_REQ_EVENT ;
			dis_info.p_api = n_dis_buffer ;

#ifdef SCCP_CONNECTION_ID_CHANGES
			n_dis_buffer[5]=(U8bit)(sccp_ccb[conn_count].conn_id);
			n_dis_buffer[6]=(U8bit)((sccp_ccb[conn_count].conn_id)>>8);
			n_dis_buffer[7]=(U8bit)((sccp_ccb[conn_count].conn_id)>>16);
			n_dis_buffer[8]=(U8bit)((sccp_ccb[conn_count].conn_id)>>24);
#else
			n_dis_buffer[5]=(U8bit)(sccp_ccb[conn_count].conn_id);
			n_dis_buffer[6]=(U8bit)((sccp_ccb[conn_count].conn_id)>>8);
#endif
			
      		result = sccp_handle_co_mesg (&dis_info, &ecode) ;
			
		} 
	}
#endif

  	SC_A_TRC (("SCCP :: SCMG : De-Register work here\n"));

#ifdef DISTRIBUTED_SCCP
	/* Send SSP etc only if 
	   You received Dergister and this is NON DEINITIALLIZING state
	   or,
	   Stack is deinitialing and you are manager */
	if ((!dereg_mate_flag && sccp_state != DEINITIALIZING)|| (sccp_state == DEINITIALIZING &&  dsccp_i_am_manager()))
	{
#endif

		/* Check here for Non-Mate API */
		SC_A_TRC (("SCCP :: SCMG : Now Sending SSP.\n"));

		/* Using the Same buffer for N-State Request */	
		n_dis_buffer[0] = SCCP_N_STATE_REQUEST;
		n_dis_buffer[1] = 0x01;
		n_dis_buffer[2] = 0x02;

#if (defined(SCCP_ITU) || defined(SCCP_JAPANESE))
		if((COMPARE_ITU) || (COMPARE_JAPANESE))
		{
			n_dis_buffer[3] = 0x09;
			n_dis_buffer[4] = 0x00;
			n_dis_buffer[5] = (U8bit)(p_sccp_reg->p_sp->pc);
			n_dis_buffer[6] = (U8bit)((p_sccp_reg->p_sp->pc)>>8);
			n_dis_buffer[7] = (U8bit)(p_sccp_reg->p_ss->ssn);
			n_dis_buffer[8] = 0x01;
		}		
#endif

#if defined(SCCP_CHINESE) || defined(SCCP_ANSI)
		if(COMPARE_CHINESE || COMPARE_ANSI)
		{
			n_dis_buffer[3] = 0x0a;
			n_dis_buffer[4] = 0x00;
			n_dis_buffer[5] = (U8bit)(p_sccp_reg->p_sp->pc);
			n_dis_buffer[6] = (U8bit)((p_sccp_reg->p_sp->pc)>>8);
			n_dis_buffer[7] = (U8bit)((p_sccp_reg->p_sp->pc)>>16);
			n_dis_buffer[8] = (U8bit)(p_sccp_reg->p_ss->ssn);
			n_dis_buffer[9] = 0x01;
		}
#endif

		/* Sending N-State Request */
		sccp_n_state_req(n_dis_buffer);

#ifdef DISTRIBUTED_SCCP
	}	
#endif

	/* Now we can change status etc */
	/* SPR 8601 fix Starts */
	/* Send entries from p_sccp_reg rether than p_info */
    sccp_deregister_ssn (GET_ID_FROM_SS(p_sccp_reg->p_ss), p_info->uid);

	/* Check here ... we'll have to tell GTT that this SS is gone */
    sccp_inform_trans_func (p_sccp_reg->p_sp, p_sccp_reg->p_ss);
	/* SPR 8601 fix Ends */

  	p_sccp_reg->registered = SS7_FALSE;

 /* 	SCCP_SEND_DEREG_ENTRY_UPDATE (p_sccp_reg);  *//* Commented by Amaresh dueto crash & SCM send also command to StandBy card SCCP as on dated 03_11_16 */

	
	/* Now reset this Flag */
#ifdef DISTRIBUTED_SCCP
	dereg_mate_flag=0;
#endif

	/* Free the memory */
	ss7_mem_free(n_dis_buffer);

	return ;
}

/***************************************************************************
**
**      FUNCTION :
**         debug time function to register a user
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void 
sccp_register_ssn 
#ifdef ANSI_PROTO
  (ss_id_t   ss_id, 
   U16bit   uid)
#else
  (ss_id, uid)
  ss_id_t        ss_id ;
  U16bit         uid ;
#endif

{
  ss_entry_t * p_ss;

  p_ss = GET_SS_FROM_ID(ss_id);
  /* SPR 9404 - Fix Start - warning removal */
  /*p_ss->dst_id = uid;*/
  p_ss->dst_id = (U8bit)uid;
  /* SPR 9404 - Fix End   */

  /* added because now User Deregisters also */
  MARK_SS_ALLOWED(p_ss);

  /* SPR 1503: Set subsystem to registered */
  p_ss->registered = SS7_TRUE;
}

/***************************************************************************
**
**      FUNCTION :
**         function to de register a ssn
****************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
***************************************************************************/

void
sccp_deregister_ssn
#ifdef ANSI_PROTO
  (ss_id_t   ss_id,
   U16bit   uid)
#else
  (ss_id, uid)
  ss_id_t        ss_id ;
  U16bit         uid ;
#endif

{
  ss_entry_t * p_ss;

  p_ss = GET_SS_FROM_ID(ss_id);

  MARK_SS_PROHIBITED(p_ss);
  p_ss->registered = SS7_FALSE;

  /* SPR 9302 - Fix Start */
  uid = 0;
  /* SPR 9302 - Fix End   */
}


#ifdef DISTRIBUTED_SCCP
/***************************************************************************
**
**      FUNCTION :dsccp_send_dereg_user_msg_to_mates
****************************************************************************
**
**      DESCRIPTION : this function is used to send deregister user message to all other DSCCP instances
**
**
**      NOTE :
**
***************************************************************************/
void
dsccp_send_dereg_user_msg_to_mates
#ifdef ANSI_PROTO
	(sc_reg_entry_t *p_sccp_reg)
#else
	(p_sccp_reg)
	sc_reg_entry_t *p_sccp_reg;	
#endif
{
	U8bit *p_buffer;
	U8bit *p_elem;
	U32bit temp;
	error_t ecode;
	return_t ret_val;

	/* Length would be same as that of register user Message */
	p_buffer = (U8bit *)sccp_malloc(DSCCP_REG_USER_MSG_LEN);
	if(p_buffer == SS7_NULL)
      {
            ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
            return ;
      }

	sccp_fill_api_header(p_buffer,DSCCP_MATE_API,DSCCP_REG_USER_MSG_NELEM, DSCCP_REG_USER_MSG_LEN);
	p_elem = p_buffer + API_HEADER_LEN;
	*p_elem++ = DSCCP_API_CAT_SCMG;	
	*p_elem++ = DSCCP_API_CMD_SCMG_DEREG_STATUS;	
	temp = (U32bit)p_sccp_reg->p_ss->sp_id;
	*p_elem++ = (U8bit)temp;
	*p_elem++ = (U8bit)(temp >> 8);
	*p_elem++ = (U8bit)(temp >> 16);
	*p_elem++ = (U8bit)(temp >> 24);
	*p_elem++ = (U8bit)(p_sccp_reg->ssn);
	*p_elem++ = (U8bit)(p_sccp_reg->uid);
	*p_elem++ = (U8bit)(p_sccp_reg->uid >> 8);

	ret_val = dsccp_broadcast_to_mates(p_buffer, DSCCP_REG_USER_MSG_LEN, &ecode);
}
#endif


#ifdef DISTRIBUTED_SCCP
/***************************************************************************
**
**      FUNCTION :dsccp_send_reg_user_msg_to_mates
****************************************************************************
**
**      DESCRIPTION : this function is used to send register user message to all other DSCCP instances
**
**
**      NOTE :
**
***************************************************************************/
void
dsccp_send_reg_user_msg_to_mates
#ifdef ANSI_PROTO
    (sc_reg_entry_t *p_sccp_reg)
#else
    (p_sccp_reg)
    sc_reg_entry_t *p_sccp_reg;
#endif
{
    U8bit *p_buffer;
    U8bit *p_elem;
    U32bit temp;
    error_t ecode;
    return_t ret_val;

	p_buffer = (U8bit *)sccp_malloc(DSCCP_REG_USER_MSG_LEN);
	if(p_buffer == SS7_NULL)
    {
    	ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
    	return ;
    }

    sccp_fill_api_header(p_buffer,DSCCP_MATE_API,DSCCP_REG_USER_MSG_NELEM, DSCCP_REG_USER_MSG_LEN);
    p_elem = p_buffer + API_HEADER_LEN;
    *p_elem++ = DSCCP_API_CAT_SCMG;
    *p_elem++ = DSCCP_API_CMD_SCMG_REG_STATUS;
    temp = (U32bit)p_sccp_reg->p_ss->sp_id;
    *p_elem++ = (U8bit)temp;
    *p_elem++ = (U8bit)(temp >> 8);
    *p_elem++ = (U8bit)(temp >> 16);
    *p_elem++ = (U8bit)(temp >> 24);
    *p_elem++ = (U8bit)(p_sccp_reg->ssn);
    *p_elem++ = (U8bit)(p_sccp_reg->uid);
    *p_elem++ = (U8bit)(p_sccp_reg->uid >> 8);

    ret_val = dsccp_broadcast_to_mates(p_buffer, DSCCP_REG_USER_MSG_LEN, &ecode);
}
#endif
