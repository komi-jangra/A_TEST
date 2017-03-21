/***************************************************************************
**  FILE NAME:
**      sc_redn.h
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
**  14 Mar02 Sachin Bhatia         Added structs, prototypes of Init,Deinit Functionality
**  06 Mar02 Sachin Bhatia         Added prototypes of dereg Functionality
**  13Aug'01 Mudit Seth            Added prototypes of common functions  
**  20Nov'01 Pawanish Modi         Changes for DSCCP redundancy. Changed 
**						structure sccp_redn_ss_entry_t
**  28May'01 Rajesh Mehta          Increased coor_id to 16bit and conn_id to
**                                 32bit if SCCP_CONNECTION_ID_CHANGES is defined
**  08Jun'98 Praneet Khare     -----  Original
**
**  Copyright 1998, Hughes Software Systems
***************************************************************************/

#include"s7_typ.h"

#ifndef _SC_REDN_H_
#define _SC_REDN_H_

extern U8bit   sccp_redn_stable_state_update ;

/*****************************************************************************
**
**	Definition for redn options
**
*****************************************************************************/

struct sccp_redn_options {
    sp_id_t      sp_id ;
    ss_id_t      ss_id ;
	U8bit		reg_entry_id;
	U32bit		ccb_id;
	U8bit		stack_type;
	U8bit		sccp_state;
	U16bit		nentries;
	/* SPR 9302 - Fix Start */
	/*U32bit		deinit_timer_id;*/
	timer_id_t		deinit_timer_id;
	/* SPR 9302 - Fix End  */
} ;

typedef struct sccp_redn_options sccp_redn_options_t;

struct sccp_redn_ss_entry {
	ss_id_t		ss_id ;
	Boolean		allowed ;
#ifdef DISTRIBUTED_SCCP
	U8bit sst_instance_id;
#endif
} ;
typedef struct sccp_redn_ss_entry	sccp_redn_ss_entry_t ;

struct sccp_redn_sp_entry {
	sp_id_t		sp_id ;
	Boolean		allowed ;
	Boolean		upu_received ;
	U8bit		upu_cause ;
	S8bit		rl ;
	S8bit		rsl ;
	S8bit		cls ;
	U8bit		ril ;
} ;
typedef struct sccp_redn_sp_entry	sccp_redn_sp_entry_t ;

struct sccp_redn_reg_entry {
	U8bit		reg_entry_id;
	sp_id_t		sp_id;
	U8bit		ssn ;
	U16bit		log_user_id;
} ;
typedef struct sccp_redn_reg_entry	sccp_redn_reg_entry_t ;

struct sccp_redn_scoc_entry {
	U16bit		ccb_id;

	U8bit 		c_state;
	U8bit		c_status;
	U8bit		wait_for_cc_flag;

#ifdef SCCP_CONNECTION_ID_CHANGES
        U32bit          conn_id;
#else
	U16bit		conn_id;
#endif
	U16bit		log_user_id;
#ifdef SCCP_CONNECTION_ID_CHANGES
        U16bit           corr_id;
#else
	U8bit		corr_id;
#endif
	U8bit		proto_class;
	
	U32bit		slr;
	U32bit		dlr;
	U8bit		sls;
		
	pc_t		opc;
	ss_id_t		ss_id;

	/* Called addr */	
	Boolean		cld_pc_ind;
	Boolean		cld_ssn_ind;
	U8bit		cld_gti;
	U8bit		cld_rout_ind;
	pc_t		cld_pc;
	U8bit		cld_ssn;
	U8bit		cld_gt_len;
	U8bit		cld_gt[MAX_GT_LEN];
	U8bit		cld_nat_ind;
	
	pc_t		dpc;

	/* Calling addr */	
	Boolean		clg_pc_ind;
	Boolean		clg_ssn_ind;
	U8bit		clg_gti;
	U8bit		clg_rout_ind;
	pc_t		clg_pc;
	U8bit		clg_ssn;
	U8bit		clg_gt_len;
	U8bit		clg_gt[MAX_GT_LEN];
	U8bit		clg_nat_ind;

	U16bit		coupled_ccb_id;

	U8bit		credit;
} ;
typedef struct sccp_redn_scoc_entry  sccp_redn_scoc_entry_t ;

struct sccp_redn_sclc_entry {
	U32bit slr;
};
typedef struct sccp_redn_sclc_entry  sccp_redn_sclc_entry_t ;

struct sccp_redn_init_entry {
	U8bit stack_type;
};
typedef struct sccp_redn_init_entry sccp_redn_init_entry_t;

struct sccp_redn_deinit_entry {
	U8bit sccp_state;
	timer_id_t deinit_timer_id;
};
typedef struct sccp_redn_deinit_entry sccp_redn_deinit_entry_t;

#ifdef SCCP_REDN_ENABLED
return_t sccp_send_reg_entry_update
         _ARGS_ ((U8bit          reg_entry_id));

return_t sccp_send_dereg_entry_update
         _ARGS_ ((U8bit          reg_entry_id));



return_t sccp_send_sclc_entry_update
   _ARGS_ ((U32bit  )); 
/* start added during CC compilation */
/* assign pvoid to U32bit in sccp_send_sclc_entry_update  */
/* end added during CC compilation */


return_t sccp_send_init_entry_update
   _ARGS_ ((U8bit  )); 

return_t sccp_send_deinit_entry_update
   _ARGS_ ((U8bit  )); 

return_t sccp_send_scoc_entry_update
       _ARGS_ ((U32bit         ccb_id));
/* start added during CC compilation */
/* this sccp_send_reg_entry_update,sccp_send_sclc_entry_update,sccp_send_scoc_entry_update function must be prototype */
/* end added during CC compilation */

/* Adding prototypes of functions required by common stack files - Mudit Seth */
return_t sccp_redn_build_api
    _ARGS_ 	((U8bit      type_of_data,
     		pvoid      p_redn_data,
     		s7_len_t   redn_data_len,
     		pvoid      *p_redn_api,
     		error_t*   p_ecode));

return_t sccp_activate_sccp 
	_ARGS_ ((error_t *p_ecode));

/* SPR 9302 - Fix Start - Warning Removal */
/* Prototypes already present */

#if 0
return_t sccp_send_sp_entry_update
	_ARGS_ ((sp_id_t	sp_id));

return_t sccp_send_ss_entry_update
	_ARGS_ ((ss_id_t	ss_id));

return_t sccp_send_reg_entry_update
	_ARGS_ ((U8bit		reg_entry_id));

return_t sccp_send_scoc_entry_update
	_ARGS_ ((U32bit		ccb_id));

return_t sccp_receive_update
	_ARGS_  ((U8bit 	type_of_data,
	 		s7_len_t 		msg_len,
	 		pvoid 		p_redn_data,
	 		error_t* 	p_ecode));  
#endif

/* SPR 9302 - Fix End   */
/* End of addition of prototypes - Mudit Seth */     
       
#define	SCCP_SEND_SS_ENTRY_UPDATE(p_ss) \
	if (sccp_redn_stable_state_update && sccp_state!=DEINITIALIZING) \
		sccp_send_ss_entry_update (GET_ID_FROM_SS (p_ss))

#define	SCCP_SEND_SP_ENTRY_UPDATE(p_sp) \
	if (sccp_redn_stable_state_update && sccp_state!=DEINITIALIZING) \
		sccp_send_sp_entry_update (GET_ID_FROM_SP (p_sp))

#define	SCCP_SEND_REG_ENTRY_UPDATE(p_reg_entry) \
	if (sccp_redn_stable_state_update && sccp_state!=DEINITIALIZING) \
		sccp_send_reg_entry_update (GET_ID_FROM_REG_ENTRY (p_reg_entry))

/* This entry does not have the "sccp_redn_stable_state_update" check 
   as this is a deletion update and hence is forced update 
									-- Sachin Bhatia                 */
#define	SCCP_SEND_DEREG_ENTRY_UPDATE(p_reg_entry) \
		if (sccp_state!=DEINITIALIZING) \
sccp_send_dereg_entry_update (GET_ID_FROM_REG_ENTRY (p_reg_entry))

#define	SCCP_SEND_SCOC_ENTRY_UPDATE(p_ccb) \
	if (sccp_redn_stable_state_update && sccp_state!=DEINITIALIZING) \
		sccp_send_scoc_entry_update (GET_ID_FROM_CCB (p_ccb))

#define	SCCP_SEND_SCLC_ENTRY_UPDATE(slr) \
	if (sccp_redn_stable_state_update && sccp_state!=DEINITIALIZING) \
		sccp_send_sclc_entry_update (slr)

#define	SCCP_SEND_INIT_ENTRY_UPDATE(stack_type) \
	if (sccp_redn_stable_state_update && sccp_state!=DEINITIALIZING) \
		sccp_send_init_entry_update (stack_type)

#define	SCCP_SEND_DEINIT_ENTRY_UPDATE(sccp_state) \
	if (sccp_redn_stable_state_update ) \
		sccp_send_deinit_entry_update (sccp_state)

#else

#define	SCCP_SEND_SS_ENTRY_UPDATE(p_ss)
#define	SCCP_SEND_SP_ENTRY_UPDATE(p_sp)
#define	SCCP_SEND_REG_ENTRY_UPDATE(p_reg_entry) 
#define	SCCP_SEND_SCOC_ENTRY_UPDATE(p_ccb) 
#define	SCCP_SEND_SCLC_ENTRY_UPDATE(slr) 
#define	SCCP_SEND_DEREG_ENTRY_UPDATE(p_reg_entry) 
#define SCCP_SEND_INIT_ENTRY_UPDATE(stack_type)
#define SCCP_SEND_DEINIT_ENTRY_UPDATE(sccp_state)

#endif

#endif /* _SC_REDN_H_ */
