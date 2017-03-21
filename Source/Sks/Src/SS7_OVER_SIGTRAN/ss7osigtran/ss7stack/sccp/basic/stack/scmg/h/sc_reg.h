/***************************************************************************
**  FILE NAME:
**      sc_bcast.h
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
**  12May'98 Sriganesh. Kini   -----  Original
**  06 Mar02 Sachin Bhatia     -----  Added Dereg functionality
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_REG_H_
#define _SC_REG_H_

#define MAX_LOCAL_USERS 10

#ifdef DISTRIBUTED_SCCP
#define DSCCP_REG_USER_MSG_LEN 14
#define DSCCP_REG_USER_MSG_NELEM 5
#endif

#define NUM_ELEMS_SCCP_DEREG_INDICATION	2 /* The extended API + cause */
#define SCCP_DEREG_INDICATION_SIZE 	9

/* Causes of Deregister */
#define STACK_DEINITIALIZING	0x01



typedef struct
{
	U8bit              ssn;
	Boolean     registered;
	U16bit             uid;
	sp_entry_t       *p_sp;
	ss_entry_t       *p_ss;
} sc_reg_entry_t;

extern sc_reg_entry_t sccp_reg_table[MAX_LOCAL_USERS];

#define IS_REG_ENTRY_ID_VALID(id) 	((id)<MAX_LOCAL_USERS)
#define GET_REG_ENTRY_FROM_ID(id)	(&sccp_reg_table[(id)])
#define GET_REG_STATUS(p_entry) 	((p_entry)->registered)
#define GET_ID_FROM_REG_ENTRY(p_reg_entry) \
									((p_reg_entry) - GET_REG_ENTRY_FROM_ID(0))

extern void sccp_register_ssn
  _ARGS_ ((ss_id_t ss_id, U16bit uid));

extern void sccp_deregister_ssn
  _ARGS_ ((ss_id_t ss_id, U16bit uid));


#ifdef DISTRIBUTED_SCCP
void dsccp_send_reg_user_msg_to_mates
	_ARGS_((sc_reg_entry_t *p_sccp_reg));
#endif

#ifdef DISTRIBUTED_SCCP
void dsccp_send_dereg_user_msg_to_mates
	_ARGS_((sc_reg_entry_t *p_sccp_reg));
#endif

#endif /* _SC_REG_H_ */
