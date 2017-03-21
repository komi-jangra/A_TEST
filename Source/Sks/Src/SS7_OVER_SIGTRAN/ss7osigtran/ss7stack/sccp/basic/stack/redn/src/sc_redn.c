/*****************************************************************************
**
**	FUNCTION:
**		This file contains the redundancy functions for SCCP module
**
******************************************************************************
**
**	FILE NAME:
**		sc_redn.c
**
**
**      DATE		NAME		REFERENCE       REASON
**	--------------------------------------------------------
**  27Feb2004   Hitesh Sharma 			SPR # 13263 
**  24Feb2003   Ashish Sawalkar 			SPR # DE-INIT 
**  15Feb2003   Ashish Sawalkar 			SPR # 11321 
**  28Oct2002   Suyash Tripathi        		SPR # 10246
**  08Oct2002   Suyash Tripathi        		SPR # 10237
**  16jul2002   Salil Kumar Agrawal         SPR # 9243
**  19Jun2002   Suyash Tripathi        		SPR # 8985/9302 
**  18Jun2002   Salil Kumar Agrawal         API SET and Get state added
**  02May2002   Sachin Bhatia          		SPR 8701 Fixed
**  30Apr2002   Sachin Bhatia          		SPR 8684/8685 Fixed
**  24Apr2002   Sachin Bhatia          		SPR 8598 Fixed
**  14Mar2002   Sachin Bhatia          		SPR 8596 Fixed
**  14Mar2002   Sachin Bhatia          		Added INIT Check
**  22Feb2002   Sachin Bhatia          		Added Deregn API Hooks
**	04Mar2002	Samip Garg  	SPR #8556  fixed inappropriate data
**  13Aug2001   Mudit Seth          		Commented out function prototypes    
**      				   					fed to redn buffer
**	20Nov2001	Pawanish Modi				Changes for DSCCP Redn
**	26Aug2000	Ramu Kandula				Fixed SPR # 4322
**  28Mar2000   Ramu Kandula                Modified the Redn impl to make
**                                          the i/f uniform across all layers
**                                          and extended to include SCOC & SCLC
**	15Oct'99    Ramu Kandula   SPR #878     ss7_mem_get replaced
**											with sccp_malloc
**	08Jun'98	Praneet Khare	HSS:###		Original
**
**  	Copyright (C) 1998, Hughes Software Systems
**
*****************************************************************************/

	
#include "sc_stgl.h"
#include "sc_reg.h"
#include "sc_ccb.h"
#include "sc_redn.h"
#include "sc_debug.h"
#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
#endif

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)

SysAddr slfAddr;
#endif


#ifdef SCCP_REDN_ENABLED

/*****************************************************************************
**
**	This data structure contains whther the event based reporting is
**	enabled or not.
**
**	Note : the default is set to enable in all states
**
*****************************************************************************/

U8bit	sccp_redn_stable_state_update = SS7_FALSE ;

extern  void          sccp_init_co_service
                     _ARGS_((U8bit   standard)) ;


static return_t sccp_sync_spmg 
		_ARGS_ ((error_t *p_ecode));

static return_t sccp_sync_ssmg 
		_ARGS_ ((error_t *p_ecode));

static return_t sccp_sync_reg_entry
		_ARGS_ ((error_t *p_ecode));

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
static return_t sccp_sync_scoc
		_ARGS_ ((error_t *p_ecode));
#endif

static return_t sccp_sync_state
		_ARGS_ ((error_t *p_ecode));

/* SPR 8596 Fix Start */
#endif 
/* end of SCCP_REDN_ENABLED */
/* SPR 8596 Fix Ends */
static void sccp_redn_sm_cmd_resp
        _ARGS_ ((U8bit	* p_api,
                 return_t 	ret_val,
                 U8bit 		param,
                 Boolean 	put_param,
	         error_t 	ecode));

/* SPR 8596 Fix Start */
#ifdef SCCP_REDN_ENABLED
/* SPR 8596 Fix Ends */

static return_t sccp_redn_get_ss_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit  		*p_redn_data,
			pvoid		*p_p_segment_info,
	 		error_t* 	p_ecode));

static return_t sccp_redn_get_sp_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit 		*p_redn_data,
			pvoid	    *p_p_segment_info,
	 		error_t* 	p_ecode));

static return_t sccp_redn_get_reg_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit 		*p_redn_data,
			pvoid		*p_p_segment_info,
	 		error_t* 	p_ecode));

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
static return_t sccp_redn_get_scoc_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit 		*p_redn_data,
			pvoid		*p_p_segment_info,
	 		error_t* 	p_ecode));
#endif

static return_t sccp_redn_get_sclc_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit 		*p_redn_data,
			pvoid		*p_p_segment_info,
	 		error_t* 	p_ecode));

static return_t sccp_redn_get_init_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit 		*p_redn_data,
			pvoid		*p_p_segment_info,
	 		error_t* 	p_ecode));

static return_t sccp_redn_get_deinit_data 
	_ARGS_ 	((sccp_redn_options_t 		*p_redn_opt,
	 		s7_len_t 		*p_msg_len,
	 		U8bit 		*p_redn_data,
			pvoid		*p_p_segment_info,
	 		error_t* 	p_ecode));

static void sccp_redn_fill_ss_entry
	_ARGS_  ((ss_id_t				ss_id,
	  		ss_entry_t 				*p_ss,
	  		sccp_redn_ss_entry_t	*p_redn_data));

static void sccp_redn_fill_sp_entry
	_ARGS_  ((sp_id_t				sp_id,
	  		sp_entry_t 				*p_sp,
	  		sccp_redn_sp_entry_t	*p_redn_data));

static void sccp_redn_fill_reg_entry
	 _ARGS_ ((U8bit					reg_entry_id,
	  		sc_reg_entry_t 			*p_reg_entry,
	  		sccp_redn_reg_entry_t	*p_redn_data));

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
static void sccp_redn_fill_scoc_entry
	 _ARGS_ ((U32bit				ccb_id,
	  		sccp_ccb_t 				*p_ccb_entry,
	  		sccp_redn_scoc_entry_t	*p_redn_data));
#endif

static void sccp_redn_fill_sclc_entry
	 _ARGS_ ((U32bit				slr,
	  		sccp_redn_sclc_entry_t	*p_redn_data));

static void sccp_redn_fill_init_entry
	 _ARGS_ ((U8bit				stack_type,
	  		sccp_redn_init_entry_t	*p_redn_data));

static void sccp_redn_fill_deinit_entry
	 _ARGS_ ((U8bit				sccp_state,
	  		sccp_redn_deinit_entry_t	*p_redn_data));

static void sccp_redn_pack_ss_entry
	_ARGS_ 	((U8bit	*p_api_elem,
	 		sccp_redn_ss_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_filled));

static void sccp_redn_pack_sp_entry
	_ARGS_ 	((U8bit	*p_api_elem,
	 		sccp_redn_sp_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_filled));

static void sccp_redn_pack_entry
	_ARGS_ 	((U8bit 	type_of_data,
			U8bit		*p_api_elem,
	 		pvoid		p_redn_entry,
	 		s7_len_t		*p_len_filled));

static void sccp_redn_pack_reg_entry
	_ARGS_ 	((U8bit	*p_api_elem,
	 		sccp_redn_reg_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_filled));

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
static void sccp_redn_pack_scoc_entry
	_ARGS_ 	((U8bit	*p_api_elem,
	 		sccp_redn_scoc_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_filled));
#endif

static void sccp_redn_pack_sclc_entry
	_ARGS_ 	((U8bit	*p_api_elem,
	 		sccp_redn_sclc_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_filled));

static void sccp_redn_pack_init_entry
    _ARGS_  ((U8bit *p_api_elem,
            sccp_redn_init_entry_t      *p_redn_entry,
            s7_len_t        *p_len_filled));

static void sccp_redn_pack_deinit_entry
    _ARGS_  ((U8bit *p_api_elem,
            sccp_redn_deinit_entry_t        *p_redn_entry,
            s7_len_t        *p_len_filled));



static void sccp_redn_unpack_ss_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_ss_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));

static void sccp_redn_unpack_sp_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_sp_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));

static void sccp_redn_unpack_reg_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_reg_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
static void sccp_redn_unpack_scoc_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_scoc_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));
#endif

static void sccp_redn_unpack_sclc_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_sclc_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));

static void sccp_redn_unpack_init_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_init_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));

static void sccp_redn_unpack_deinit_entry
	_ARGS_ 	((U8bit		*p_api_elem,
	 		sccp_redn_deinit_entry_t		*p_redn_entry,
	 		s7_len_t		*p_len_extracted));

static return_t sccp_redn_handle_updates
	_ARGS_ 	((U8bit 		type_of_data,
	 		s7_len_t 		msg_len,
	 		U8bit 		*p_redn_data,
	 		error_t* 	p_ecode));

/* Commented out by Mudit Seth - these prototypes are defined in sc_redn.h */        
/*
return_t sccp_redn_build_api
    _ARGS_ 	((U8bit      type_of_data,
     		pvoid      p_redn_data,
     		s7_len_t   redn_data_len,
     		pvoid      *p_redn_api,
     		error_t*   p_ecode));

return_t sccp_activate_sccp 
	_ARGS_ ((error_t *p_ecode));

return_t sccp_send_sp_entry_update
	_ARGS_ ((sp_id_t	sp_id));

return_t sccp_send_ss_entry_update
	_ARGS_ ((ss_id_t	ss_id));

return_t sccp_send_reg_entry_update
	_ARGS_ ((U8bit		reg_entry_id));

return_t sccp_send_scoc_entry_update
	_ARGS_ ((U32bit		ccb_id));

return_t sccp_send_sclc_entry_update
	_ARGS_ ((void));


return_t sccp_receive_update
	_ARGS_  ((U8bit 	type_of_data,
	 		s7_len_t 		msg_len,
	 		pvoid 		p_redn_data,
	 		error_t* 	p_ecode));
*/        

static return_t sccp_redn_ss_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

static return_t sccp_redn_sp_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

static return_t sccp_redn_reg_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

static return_t sccp_redn_dereg_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
static return_t sccp_redn_scoc_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;
#endif

static return_t sccp_redn_sclc_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

static return_t sccp_redn_init_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

static return_t sccp_redn_deinit_update_database
        _ARGS_((s7_len_t          msg_len,
         	pvoid          p_redn_buf,
         	error_t        *p_ecode)) ;

static U8bit * sccp_build_redn_data_buf
	_ARGS_ 	((U8bit		trans_id,
	 		U8bit 		type_of_data,
	 		sccp_redn_options_t *p_redn_info,
	 		s7_len_t 		redn_msg_len,
	 		U8bit 		*p_redn_msg,
	 		Boolean	more_data_flag,   
	 		U8bit		buf_seq_num,
	 		error_t* 	p_ecode));

static return_t sccp_redn_handle_sm_cmd_req_act
    _ARGS_ ((U8bit * p_api, error_t *p_ecode));

    /* spr #9243 starts */
#if 0    
static return_t sccp_redn_set_state
    _ARGS_ ((U8bit state, error_t *p_ecode));
static return_t sccp_redn_get_state
    _ARGS_ ((U8bit *param, Boolean *put_param, error_t *p_ecode));
#endif
    /* spr #9243 ends */

return_t ss7_send_update(module_id_t module_id,U8bit type_of_data,sccp_redn_options_t *p_redn_info,s7_len_t msg_len,pvoid p_redn_data,error_t* p_ecode);



/*****************************************************************************
**
**  FUNCTION :
** ss7_send_update
**
**  This function send the redundancy data from Active to Standby.
**  
**  Created by Amaresh for Redundancy Implementation. 
******************************************************************************
**
**  DESCRIPTION:
**    This function send updated data solicited/unsolocited .
**
**  RETURN VALUE:
**    SS7_SUCCESS
**    SS7_FAILURE
**
*****************************************************************************/

return_t
ss7_send_update (module_id_t module_id, U8bit type_of_data,sccp_redn_options_t *p_redn_info,s7_len_t msg_len,pvoid p_redn_data, error_t *p_ecode)
{
		 U8bit *p_api_buf;
		 U8bit trans_id;
		 Boolean more_data_flag;
		 Boolean redn_info_flag;
		 U8bit buffer_seq_num, entry_len;

		SC_REDN_TRC (("SCCP::REDN: Entering function ss7_send_update message\n"));
     more_data_flag = SS7_FALSE;
		 trans_id = 0x21;
		 buffer_seq_num = 0;  	
      p_api_buf = SS7_NULL;
      p_api_buf = sccp_build_redn_data_buf(
            trans_id, type_of_data, p_redn_info,
            msg_len, p_redn_data,
            more_data_flag, buffer_seq_num,
            p_ecode);
			if (p_api_buf == SS7_NULL)
      {
				SC_REDN_TRC (("SCCP::REDN:ss7_send_update p_api_buf == SS7_NULL\n"));
        /* send standard response to report FAILURE */
        return (SS7_FAILURE);
      }
			else
			{
    			sccp_sendto_rm (p_api_buf);/* Added by Amaresh for Redn Message updation */
				  SC_REDN_TRC (("SCCP::REDN: Sending ss7_send_update message from Active->Standby \n"));
    	}
			if (p_api_buf)
			{
				  SC_REDN_TRC (("SCCP::REDN: Free the memory from  Active->Standby \n"));
					ss7_mem_free(p_api_buf);
			}
/*    ss7_mem_free(p_redn_data);*//* Commented by Amaresh as on dated 22-02-16 */
    return(SS7_SUCCESS);
}


    
/*****************************************************************************
**
**	FUNCTION :
**		sccp_init_redn_data
**
**	This function initializes the redundancy flag for event based
**	reporting to redundant side.
**
******************************************************************************
**
**	DESCRIPTION:
**		This function initializes the redundancy flag for event based
**		reporting to redundant side.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_init_redn_data
#ifdef ANSI_PROTO
	(Boolean 	event_reporting, 
	 error_t* 	p_ecode)
#else
	(event_reporting, p_ecode)
	Boolean        event_reporting ;
	error_t*       p_ecode ;
#endif
{
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		*p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }

	SC_REDN_TRC (("SCCP::REDN: Event Reporting set to %d\n", event_reporting));
	sccp_redn_stable_state_update = event_reporting;
	*p_ecode = 0;
	return SS7_SUCCESS;
}

/* spr # 9243 starts */
#if 0
/* added by salil */
/*****************************************************************************
**
**	FUNCTION :
**		sccp_redn_set_state
**
**	This function initializes the state(ACTIVE/STANDBY) of sccp if it can
**	reporting to redundant side.
**
******************************************************************************
**
**	DESCRIPTION:
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_redn_set_state
#ifdef ANSI_PROTO
	(U8bit state, 
	 error_t* 	p_ecode)
#else
	(state, p_ecode)
	U8bit state ;
	error_t*       p_ecode ;
#endif
{
    extern U8bit sccp_state;
    extern U8bit sccp_redn_sub_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		*p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }
    else
    {
        SC_REDN_TRC (("SCCP::REDN: Setting the State of SCCP"));
        if ((state == ACTIVE) || (state == STANDBY))
       	{ 
		    sccp_redn_sub_state = state ;
#ifdef DISTRIBUTED_SCCP       
			if (state == ACTIVE)
				dsccp_notify_self_status(sccp_state | 0x40 , SCCP_MODULE_ID);
			else
				dsccp_notify_self_status(sccp_state | 0x80 , SCCP_MODULE_ID);
#endif		
		} 
		else
        {
            SC_A_TRC (("SCCP::INIT: Invalid State received \n"));
            *p_ecode = ESS7_INVALID_STATE;
            return SS7_FAILURE;
        }

    }
	
    *p_ecode = 0;
	return SS7_SUCCESS;
}
/* end */

/* added by salil */
/*****************************************************************************
**
**	FUNCTION :
**		sccp_redn_get_state
**
**	This function returns the state(ACTIVE/STANDBY) of sccp if it can
**
******************************************************************************
**
**	DESCRIPTION:
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/
return_t 
sccp_redn_get_state
#ifdef ANSI_PROTO
	(U8bit *param, Boolean *put_param, 
	 error_t *p_ecode)
#else
	(param, put_param, p_ecode)
	U8bit * param;
    Boolean * put_param;
	error_t *p_ecode ;
#endif
{
    extern U8bit sccp_redn_sub_state;
    SC_REDN_TRC (("SCCP::REDN: Returning the State of SCCP"));
    if ((sccp_redn_sub_state == ACTIVE) || (sccp_redn_sub_state == STANDBY))
    {
        *param = sccp_redn_sub_state;
        *put_param = SS7_TRUE;
        *p_ecode = 0;
        return SS7_SUCCESS;
    }
    else
    {
        SC_A_TRC (("SCCP::INIT: Invalid State \n"));
        *p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }
}
/* end */
#endif
/* spr # 9243 ends */

/*****************************************************************************
**
**	FUNCTION :
**		sccp_activate_sccp
**
******************************************************************************
**
**	DESCRIPTION:
**	This function activates the standby module and brings it in sync with the
**	active module. This function is used by the SM to activate the standby 
**	module.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_activate_sccp
#ifdef ANSI_PROTO
	(error_t *p_ecode) 
#else
	(p_ecode)
	error_t *p_ecode
#endif
{
	return_t ret_val = SS7_SUCCESS;


	if ((ret_val = sccp_sync_spmg(p_ecode)) == SS7_FAILURE)
		return ret_val; 

	if ((ret_val = sccp_sync_ssmg(p_ecode)) == SS7_FAILURE)
		return ret_val; 

	if ((ret_val = sccp_sync_reg_entry(p_ecode)) == SS7_FAILURE)
		return ret_val; 

/** Added this flag so that code can be compiled wthout CO service */
#ifndef SCCP_INCLUDE_CO_SERVICE
	if ((ret_val = sccp_sync_scoc(p_ecode)) == SS7_FAILURE)
		return ret_val; 
#endif

	if ((ret_val = sccp_sync_state(p_ecode)) == SS7_FAILURE)
		return ret_val; 

	return SS7_SUCCESS;
}


/******************************************************************************
**
**	FUNCTION :
**		sccp_request_active
**
**	This function is used by system management to get the redundancy
**	data from active module
**
*******************************************************************************
**
**	DESCRIPTION:
**		This function is used by system management to get the 
**		redundancy data from active module
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
**	NOTE:
**		This function causes a buffer to be allocated for returning the 
**	redundancy data. It is the responsibility of the calling funtion to
** 	ensure that the buffer is released.
**
******************************************************************************/

return_t 
sccp_request_active
#ifdef ANSI_PROTO
	(U8bit 		type_of_data,
	 pvoid 		p_redn_opt,
	 s7_len_t 		*p_msg_len,
	 pvoid 		p_redn_data,
/* start added for CC compilation */
/* assign void* to U8bit* in p_redn_dataand assign void* to sccp_redn_options_t* in p_redn_opt */
/* end added for CC compilation */
	 pvoid		*p_p_segment_info,
	 error_t* 	p_ecode)
#else
	(type_of_data, p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
	U8bit          type_of_data ;
	pvoid          p_redn_opt ;
	s7_len_t          *p_msg_len ;
	pvoid          p_redn_data ;
/* start added for CC compilation */
/* assign void* to U8bit* in p_redn_dataand assign void* to sccp_redn_
options_t* in p_redn_opt */
/* end added for CC compilation */

	pvoid		   *p_p_segment_info,
	error_t*       p_ecode ;
#endif
{
#if 0
    extern U8bit sccp_state;
/* data Asked for could be Stack State data also */
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		*p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }
#endif

	switch (type_of_data)
	{
		case SCCP_REDN_DATA_SS_ENTRY:
			return (sccp_redn_get_ss_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */

		case SCCP_REDN_DATA_SP_ENTRY:
			return (sccp_redn_get_sp_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */


		case SCCP_REDN_DATA_REG_ENTRY:
			return (sccp_redn_get_reg_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */

#if 0
/* We comment this coz' there is no meaning of asking for deleted data from the stack */
       case SCCP_REDN_DATA_DEREG_ENTRY:
            return (sccp_redn_get_reg_data (
                   (sccp_redn_options_t*)   p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */

#endif

			/** Changed by Pawanish for INCLUDE CO SEVICE FLAG **/
#ifdef SCCP_INCLUDE_CO_SERVICE
		case SCCP_REDN_DATA_SCOC_ENTRY:
			return (sccp_redn_get_scoc_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */

#endif

		case SCCP_REDN_DATA_SCLC_ENTRY:
			return (sccp_redn_get_sclc_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */

		case SCCP_REDN_DATA_INIT_ENTRY:
			return (sccp_redn_get_init_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */

		case SCCP_REDN_DATA_DEINIT_ENTRY:
			return (sccp_redn_get_deinit_data ( 
			       (sccp_redn_options_t*)	p_redn_opt, p_msg_len,(U8bit*) p_redn_data, p_p_segment_info, p_ecode));
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* */
/* end added during CC compilation */


		default:
			SC_A_TRC (("SCCP::REDN: invalid  data type (%d)\n", 
					type_of_data));
			*p_ecode = ESCCP_WRONG_DATA_TYPE ;
			return(SS7_FAILURE) ;
	}
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_receive_update
**
**
*******************************************************************************
**
**	DESCRIPTION:
**	This function is used by system management to update the standby module 
**  with redundancy data from active module
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
******************************************************************************/

return_t 
sccp_receive_update
#ifdef ANSI_PROTO
	(U8bit 		type_of_data,
	 s7_len_t 		msg_len,
	 pvoid 		p_redn_data,
	 error_t* 	p_ecode)
#else
	(type_of_data, msg_len, p_redn_data, p_ecode)
	U8bit          type_of_data ;
	s7_len_t          msg_len ;
	pvoid          p_redn_data ;
	error_t*       p_ecode ;
#endif
{
    extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)&&(type_of_data!=SCCP_REDN_DATA_INIT_ENTRY))
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		*p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }
	/* SPR 11321 Fix */
    if ((sccp_state == BLOCKED)			
			&& 	(type_of_data!=SCCP_REDN_DATA_DEINIT_ENTRY)
				&&	(type_of_data!=SCCP_REDN_DATA_SCOC_ENTRY))
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in BLOCKED State\n"));
		*p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }

	switch(type_of_data)
	{
		case SCCP_REDN_DATA_SS_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating SS Entries ...\n"));
			if (msg_len < sizeof (sccp_redn_ss_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_ss_update_database (
					msg_len, p_redn_data, p_ecode)) ;

		case SCCP_REDN_DATA_SP_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating SP Entries ...\n"));
			if (msg_len < sizeof (sccp_redn_sp_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_sp_update_database (
					msg_len, p_redn_data, p_ecode)) ;

		case SCCP_REDN_DATA_REG_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating REG Entries ...\n"));
			if (msg_len < sizeof (sccp_redn_reg_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_reg_update_database (
					msg_len, p_redn_data, p_ecode)) ;

  		case SCCP_REDN_DATA_DEREG_ENTRY:
            SC_REDN_TRC (("SCCP::REDN: Updating DE-REG Entries ...\n"));
            if (msg_len < sizeof (sccp_redn_reg_entry_t))
            {
                *p_ecode = ESS7_INVALID_LENGTH ;
                return(SS7_FAILURE) ;
            }
            return (sccp_redn_dereg_update_database (
                    msg_len, p_redn_data, p_ecode)) ;


/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
		case SCCP_REDN_DATA_SCOC_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating SCOC Entries ...\n"));
			if (msg_len < sizeof (sccp_redn_scoc_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_scoc_update_database (
					msg_len, p_redn_data, p_ecode)) ;
#endif

		case SCCP_REDN_DATA_SCLC_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating SCLC Entry ...\n"));
			if (msg_len < sizeof (sccp_redn_sclc_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_sclc_update_database (
					msg_len, p_redn_data, p_ecode)) ;

		case SCCP_REDN_DATA_INIT_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating INIT Entry ...\n"));
			if (msg_len < sizeof (sccp_redn_init_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_init_update_database (
					msg_len, p_redn_data, p_ecode)) ;

		case SCCP_REDN_DATA_DEINIT_ENTRY:
			SC_REDN_TRC (("SCCP::REDN: Updating DEINIT Entry ...\n"));
			if (msg_len < sizeof (sccp_redn_deinit_entry_t))
			{
				*p_ecode = ESS7_INVALID_LENGTH ;
				return(SS7_FAILURE) ;
			}
			return (sccp_redn_deinit_update_database (
					msg_len, p_redn_data, p_ecode)) ;

		default:	
			SC_A_TRC (("SCCP::REDN: invalid  data type (%d)\n", 
					type_of_data));
			*p_ecode = ESCCP_WRONG_DATA_TYPE ;
			return(SS7_FAILURE) ;
	}
}

/*****************************************************************************
**
**	FUNCTION :
**		sccp_sync_spmg
**
******************************************************************************
**
**	DESCRIPTION:
**	This functions checks the SP database for consistency and brings it in 
**	sync with the active module. It starts the timers that are supposed to 
**	be active in a particular state.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_sync_spmg
#ifdef ANSI_PROTO
	(error_t *p_ecode) 
#else
	(p_ecode)
	error_t *p_ecode
#endif
{
	sp_id_t		sp_id;
	sp_entry_t	*p_sp;
	ss_entry_t	*p_ss, *p_css;
	U8bit		*p_css_list;
	U32bit		i, j;

	SC_REDN_TRC (("SCCP::REDN: Synchronizing SPMG \n"));

	*p_ecode = 0;
	for (sp_id = 0; sp_id < MAX_SP; ++sp_id)
	{
		p_sp = GET_SP_FROM_ID(sp_id);
		if (IS_SP_CONFIGURED(p_sp))
		{
			SC_REDN_TRC (("SCCP::REDN: Checking pc %d on nw %d ... \n", 
				p_sp->pc, p_sp->nw_id));

			/* reset the congestion parameters and initlate a local bcast */

			p_sp->cls = 0;
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
			if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) ||(COMPARE_CHINESE))
			{
				p_sp->rlm = 0;
				p_sp->rslm = 0;
				sccp_compute_cong_params(p_sp, &p_sp->rl, &p_sp->rsl, &p_sp->ril);
	
				for (i=0, p_ss = GET_SS_LIST_IN_SP(p_sp);
					i < GET_NUM_SS_IN_SP(p_sp); i++, p_ss = GET_NEXT_SS(p_ss))
				{
					for (j=0, p_css_list = GET_CSS_LIST(p_ss);
						j < GET_NUM_CSS(p_ss);
						j++, p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
					{
						p_css = GET_CSS_FROM_LIST(p_css_list);
						/* sccp_local_bcast (p_sp, p_css, LBCS_RIL); ?? */
					}
				}
       			sccp_inform_trans_func(p_sp, SS7_NULL);
			}
#endif
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
    		if ((COMPARE_ANSI) || (COMPARE_BCGR))
    		{
       			/* send SP congested API */
       			/* sccp_local_bcast (p_sp, SS7_NULL, LBCS_SP_CONG) ; ?? */
       			sccp_inform_trans_func(p_sp, SS7_NULL);
    		}
#endif
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**
**	FUNCTION :
**		sccp_sync_ssmg
**
******************************************************************************
**
**	DESCRIPTION:
**	This functions checks the SS database for consistency and brings it in 
**	sync with the active module. It starts the timers that are supposed to 
**	be active in a particular state.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_sync_ssmg
#ifdef ANSI_PROTO
	(error_t *p_ecode) 
#else
	(p_ecode)
	error_t *p_ecode
#endif
{
	ss_id_t		ss_id;
	ss_entry_t	*p_ss;
	sp_entry_t	*p_sp;

	SC_REDN_TRC (("SCCP::REDN: Synchronizing SSMG \n"));

	for (ss_id = 0; ss_id < MAX_SS; ++ss_id)
	{
		p_ss = GET_SS_FROM_ID(ss_id);
		if (IS_SS_CONFIGURED(p_ss))
		{
			SC_REDN_TRC (("SCCP::REDN: Checking ssn %d on sp id %d ... \n", 
				p_ss->ssn, p_ss->sp_id));

			/* Check if the subsystem is prohibited and start the SST
			** if it is a remote subsystem
			*/
/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
			if (! IS_SPID_VALID(p_ss->sp_id)) 
/*			if (!((p_ss->sp_id) < MAX_SP))	*/
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
			{
				/* SS prov data corrupted */
				SET_SS_NOT_CONFIGURED(p_ss);
				continue;
			}
			p_sp = GET_SP_FROM_ID(p_ss->sp_id);

#ifdef DISTRIBUTED_SCCP

			if((p_ss->sst_instance_id == sc_opt.dsccp_local_instance_id) && (p_ss->sst_instance_id != DSCCP_INVALID_INSTANCE_ID))
                  {
                  	p_ss->prev_t_stat_info_timer_val =
                                     sc_tim.t_stat_info_start_timer_val;

				p_ss->t_stat_info_running = SS7_FALSE;
                       	sccp_start_sst(p_ss);
                   }
#else

			if (! p_ss->allowed)
			{
				if (!(p_sp->local) && p_sp->allowed)
				{
					/* Start SST */
					p_ss->prev_t_stat_info_timer_val =
					 	sc_tim.t_stat_info_start_timer_val;
					p_ss->t_stat_info_running = SS7_FALSE;
					sccp_start_sst(p_ss);
				}
			}
#endif
			
			sccp_inform_trans_func (p_sp, p_ss);
		}
	}

	return SS7_SUCCESS;
/* SPR 9302 - Fix Start */
	p_ecode = 0;
/* SPR 9302 - Fix End   */
	
}

/*****************************************************************************
**
**	FUNCTION :
**		sccp_sync_reg_entry
**
******************************************************************************
**
**	DESCRIPTION:
**	This functions checks the Reg entries database for consistency.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_sync_reg_entry
#ifdef ANSI_PROTO
	(error_t *p_ecode) 
#else
	(p_ecode)
	error_t *p_ecode
#endif
{
	/* No action is required to ensure the consistency of this DB */
	SC_REDN_TRC (("SCCP::REDN: Synchronizing Registration Entries \n"));
	*p_ecode = 0;

	return SS7_SUCCESS;
}
/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
/*****************************************************************************
**
**	FUNCTION :
**		sccp_sync_scoc
**
******************************************************************************
**
**	DESCRIPTION:
**	This functions checks the CCB database for consistency and brings it in 
**	sync with the active module. It starts the timers that are supposed to 
**	be active in a particular state.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
*****************************************************************************/

return_t 
sccp_sync_scoc
#ifdef ANSI_PROTO
	(error_t *p_ecode) 
#else
	(p_ecode)
	error_t *p_ecode
#endif
{
	U16bit		ccb_id;
	sccp_ccb_t	*p_ccb, *p_coupled_ccb;
	U8bit		state;

/* SPR 8985 - Fix Start */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
	msg_info_t	msg_info;
	U8bit		tmp_buf[SS7_MAX_BUFFER_SIZE];
#endif
/* SPR 8985 - Fix End  */
	U16bit		i;
	/* SPR 8684/8685 fix Start --Sachin Bhatia */
	U8bit		free_list_head_set=0; /* Used to indicate whether free list head is set or not */
	/*U16bit		last_ccb_id ;*/ /* Last added CCB ID in free list */
	U16bit		last_ccb_id = 0; /* SPR 9302 - warning removal*/
	/* SPR 8684/8685 fix Ends --Sachin Bhatia */

	SC_REDN_TRC (("SCCP::REDN: Synchronizing SCOC \n"));

	for (ccb_id = 0; ccb_id < MAX_SCCP_CO_CONNECTIONS; ++ccb_id)
	{
		p_ccb = GET_CCB_FROM_ID(ccb_id);

		for (i=0; i<MAX_SCCP_CO_TIMERS; ++i)
			p_ccb->sccp_timer[i].timer_status = SCCP_CO_TIMER_NOTRUNNING;

  		p_ccb->p_recv_queue = (sc_queue_t *)SS7_NULL;
		p_ccb->p_trans_queue = (sc_queue_t *)SS7_NULL ;
		p_ccb->p_ed_trans_queue = (sc_queue_t *)SS7_NULL ;
		p_ccb->num_ed_in_queue = 0 ;
		p_ccb->send_seq = 0 ;
		p_ccb->send_seq_x = 0 ;
		p_ccb->lw_edge = 0 ;
		p_ccb->send_seq_ack = 0 ;
		p_ccb->seq_seg = 0 ;
		p_ccb->seg_reass = 0;

		state = p_ccb->c_state;

		if (state != SCCP_CONN_IDLE)
		{
			SC_REDN_TRC(("SCCP::REDN: Checking ccb id %d (conn id = %d) ...\n",
				ccb_id, p_ccb->conn_id));
		}

		switch (state)
		{
		case SCCP_CONN_IDLE:
			/* ccb not used; skip the block */
			/* SPR 8684/8685 fix Start --Sachin Bhatia */
			/* If the node is free it has to be added to the free list 
			   after switch over.  */
			if(free_list_head_set) /* Free List Head is Set */
			{
				/* Add the node here (After the last added Node) */
				sccp_ccb[last_ccb_id].next_ccb_id = ccb_id;
				sccp_ccb[ccb_id].next_ccb_id = SCCP_INVALID_CCB_ID;
				last_ccb_id = ccb_id; /* This is the last added node */
			}
			else /* Free List Head not Set */
			{
				sccp_free_ccb_list_head = ccb_id; /* First free CCB */
				sccp_ccb[sccp_free_ccb_list_head].next_ccb_id = SCCP_INVALID_CCB_ID;
				last_ccb_id = ccb_id; /* This is the last added node */
				free_list_head_set = 1;	/* We have set the head */
				SC_REDN_TRC(("SCCP::REDN: Free List Head -> %d\n", sccp_free_ccb_list_head));

			}
			/* SPR 8684/8685 fix Ends --Sachin Bhatia */
			break;
		
		case SCCP_CONN_START:
			/* SPR 8684/8685 fix Start --Sachin Bhatia */
			/* Node is in Start state so has to be added in the hash table 
			   after switch over.  */
			sccp_utl_add_ccb_to_hash_tbl(ccb_id, sccp_ccb[ccb_id].l_id, sccp_ccb[ccb_id].corr_id);

			/* SPR 8684/8685 fix Ends --Sachin Bhatia */

			/* start the conn_est timer */
			if (SS7_SUCCESS != sccp_start_co_timer(p_ccb, SCCP_T_CONNEST_TIMER,
					p_ecode))
			{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
			}

			break;

		case SCCP_CONN_ESTABLISHED:	
			/* If it is class 3 connection, reset the connection */
/* SPr # 8552 Fix Starts */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SPR # 8552 Fix Ends */
			if (p_ccb->proto_class == PROTOCOL_CLASS_3)
			{
				for (i=0; i<SS7_MAX_BUFFER_SIZE; ++i)
					tmp_buf[i] = 0;
				msg_info.p_api = tmp_buf;
				msg_info.flag = 0;
				msg_info.p_ccb = p_ccb;
				msg_info.reset_cause = SCCP_RSC_NETWORK_OPERATIONAL;
				msg_info.conn_id = p_ccb->conn_id;
				sccp_utl_reset_conn(&msg_info);
			}
/* SPr # 8552 Fix Starts */
#endif
/* SPR # 8552 Fix Ends */

			/* start T_inact_rec timer and T_inact_send timer */
    		if (SS7_SUCCESS != 
				sccp_start_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode))
    		{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
    		}
 
    		if (SS7_SUCCESS != 
				sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode))
    		{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
    		}

			/* NOTE: In case of protocol class 2, the sync procedure is still
			** not complete. If a few segments of a segmented msg have been 
			** received by previosly active module, then this will result in
			** a partial msg, consisting of the remaining segments, being 
			** delivered to the SCCP User. One possible solution is to release
			** the connection !!
			*/

			break;

		case SCCP_CONN_CLOSING:
			/* Start T-rel timer */
    		if (SS7_SUCCESS != 
				sccp_start_co_timer (p_ccb, SCCP_T_REL_TIMER, p_ecode))
    		{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
    		}

			if (IS_COUPLING_PRESENT (p_ccb))
			{
				p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
				sccp_remove_association (p_ccb, p_coupled_ccb) ;
			}

			break;

		case SCCP_CONN_CLOSED:
			/* Start the T-freeze timer */
    		if (SS7_SUCCESS != 
				sccp_start_co_timer (p_ccb, SCCP_T_FREEZE_TIMER, p_ecode))
    		{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
    		}
			
			if (IS_COUPLING_PRESENT (p_ccb))
			{
				p_coupled_ccb = SCCP_GET_COUPLED_CCB (p_ccb) ;
				sccp_remove_association (p_ccb, p_coupled_ccb) ;
			}

			break;

		case SCCP_CONN_RESET:
			/* RESET is not a stable state. The standby module should never
			** have entered this state if Unsolicited mode is used for updation.
			** Change the state to Established 
			*/
			p_ccb->c_state = SCCP_CONN_ESTABLISHED;
			/* If it is class 3 connection, reset the connection */
/* SPr # 8552 Fix Starts */
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SPR # 8552 Fix Ends */
			if (p_ccb->proto_class == PROTOCOL_CLASS_3)
			{
				for (i=0; i<SS7_MAX_BUFFER_SIZE; ++i)
					tmp_buf[i] = 0;
				msg_info.p_api = tmp_buf;
				msg_info.flag = 0;
				msg_info.p_ccb = p_ccb;
				msg_info.reset_cause = SCCP_RSC_NETWORK_OPERATIONAL;
				sccp_utl_reset_conn(&msg_info);
			}
/* SPr # 8552 Fix Starts */
#endif
/* SPR # 8552 Fix Ends */

			/* start T_inact_rec timer and T_inact_send timer */
    		if (SS7_SUCCESS != 
				sccp_start_co_timer (p_ccb, SCCP_T_IAR_TIMER, p_ecode))
    		{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
    		}
 
    		if (SS7_SUCCESS != 
				sccp_start_co_timer (p_ccb, SCCP_T_IAS_TIMER, p_ecode))
    		{
				SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
					" (ccb id = %d)\n", p_ccb->conn_id, ccb_id));
				return SS7_FAILURE;
    		}

			break;

		default:
			p_ccb->c_state = SCCP_CONN_IDLE;
			SC_REDN_TRC (("SCCP::REDN: Syncronization failed for Conn id %d"
				" (ccb id = %d) as it is in invalid state\n", 
				p_ccb->conn_id, ccb_id));
			break;
		}
	}

	return SS7_SUCCESS;
}
#endif
/*****************************************************************************
**
**  FUNCTION :
**      sccp_sync_state
**
******************************************************************************
**
**  DESCRIPTION:
**      Brings SCCP state to Sync
**
**  RETURN VALUE:
**      SS7_SUCCESS
**      SS7_FAILURE
**
*****************************************************************************/
return_t
sccp_sync_state
#ifdef ANSI_PROTO
    (error_t *p_ecode)
#else
    (p_ecode)
    error_t *p_ecode
#endif
{
	extern U8bit sccp_state;
#ifdef SCCP_INCLUDE_CO_SERVICE
	return_t	result;
	/* SPR 9302 - Fix Start */
	/*extern U32bit deinit_timer_id;*/
	extern timer_id_t deinit_timer_id;
	/* SPR 9302 - Fix End  */
	U8bit * deinit_timer_buffer;
	if (sccp_state == BLOCKED)
	{
		/* We'll have to restart the DEINIT Timer */
#if 0
		result = ss7_stop_timer (deinit_timer_id, p_ecode);
		if (result == SS7_FAILURE)
		{
			return(SS7_FAILURE);
		}
#endif
 		deinit_timer_buffer = (U8bit *)sccp_malloc(sizeof(U8bit));
		*(deinit_timer_buffer) = T_DEINIT_TIMER_ID;


		result = ss7_start_timer(SCCP_T_DEINIT_TIMER_DEF_VAL, deinit_timer_buffer, 1, SCCP_MODULE_ID,  &deinit_timer_id, p_ecode );
		if (result == SS7_FAILURE)
		{
			return(SS7_FAILURE);
		}
	}
	else
#endif
	{
		return(SS7_SUCCESS);
	}
	return(SS7_SUCCESS);
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_fill_ss_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function fills the SS entry into redn ss data structure.
**
******************************************************************************/

void
sccp_redn_fill_ss_entry
#ifdef ANSI_PROTO
	 (ss_id_t				ss_id,
	  ss_entry_t 			*p_ss,
	  sccp_redn_ss_entry_t	*p_redn_data)
#else
	(ss_id, p_ss, p_redn_data)
	ss_id_t					ss_id;
	ss_entry_t     			*p_ss;
	sccp_redn_ss_entry_t 	*p_redn_data;
#endif
{
	p_redn_data->ss_id = ss_id;
	p_redn_data->allowed = p_ss->allowed;
#ifdef DISTRIBUTED_SCCP
	p_redn_data->sst_instance_id = p_ss->sst_instance_id;
#endif
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_send_ss_data
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to report the SS redundancy data in both
**		solicited and unsolicited modes; In unsolicited mode the transaction
**		id argument will be 0 and the ss id argument will contain the SS id 
**		if the SS entry that must be sent to SM for updation. In the solicited
**		mode this function iterates thru' SS ids and sends all the configured 
**		SS entries to SM for updation. In this case, the transaction id 
**		argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_ss_data
#ifdef ANSI_PROTO
	(sccp_redn_options_t 		*p_redn_opt,
	 s7_len_t 						*p_msg_len,
	 U8bit 						*p_redn_data,
	 pvoid						*p_p_segment_info,
	 error_t					*p_ecode)
#else
	(p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
	sccp_redn_options_t         *p_redn_opt ;
	s7_len_t          				*p_msg_len ;
	U8bit          				*p_redn_data ;
	pvoid						*p_p_segment_info ;
	error_t       				*p_ecode ;
#endif
{
	ss_entry_t			*p_ss ;
	ss_id_t				ss_id, next_ss_id;
	sccp_redn_options_t *p_segment_info;
	U8bit				*p_entry;
	U16bit				nentries;

	/** Send SS data **/
	p_entry = p_redn_data;
	if (*p_p_segment_info != SS7_NULL)
	{
		/* Continue from the previous dispatch */
		p_segment_info =(sccp_redn_options_t*) *p_p_segment_info;
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* */
/* end added during CC compilation */
		next_ss_id = p_segment_info->ss_id;
		nentries = p_segment_info->nentries;
		sccp_free ((buffer_t*)p_segment_info);
/* start added during CC compilation */
/* assign pvoid to buffer_t* */
/* end added during CC compilation */

		*p_p_segment_info = SS7_NULL;
	}
	else
	{
		/* New Transaction */
		if (p_redn_opt != SS7_NULL)
		{
			/* return 'nentries' number of configured entries starting from
			** ss_id 
			*/
			next_ss_id = p_redn_opt->ss_id;
			nentries = p_redn_opt->nentries;
		}
		else
		{
			/* return all configured entries */
			next_ss_id = 0;
			nentries = MAX_SS;
		}
	}

	for (ss_id=next_ss_id; ss_id<MAX_SS; ++ss_id)
	{
		p_ss = GET_SS_FROM_ID (ss_id) ;
		if (IS_SS_CONFIGURED(p_ss))
		{
			if ((p_entry + sizeof(sccp_redn_ss_entry_t)) > 
				(p_redn_data + *p_msg_len))
			{
				/* No more space in the Redn buffer but more data to be 
				** filled; return the current ss id in p_p_segment_info
				*/
				/** SPR# 9302 Start Fix **/
				p_segment_info = 
						(sccp_redn_options_t*) (void *)sccp_malloc (sizeof(sccp_redn_options_t));
				/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* */
/* end added during CC compilation */
				if (p_segment_info == SS7_NULL)
				{
					*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
					return SS7_FAILURE;
				}
				p_segment_info->ss_id = ss_id;
				p_segment_info->nentries = nentries;
				*p_p_segment_info = p_segment_info;
				*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);
				return SS7_SUCCESS;
			}

			sccp_redn_fill_ss_entry (
				ss_id, p_ss, (sccp_redn_ss_entry_t*) p_entry); 
/* start added during CC compilation */
/* assign pvoid to sccp_redn_ss_entry_t* */
/* end added during CC compilation */

			p_entry += sizeof(sccp_redn_ss_entry_t);
			nentries --;
			if (nentries == 0)
				break;
		}
	}
	*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

	if (p_redn_opt != SS7_NULL)
	{
		if (ss_id == MAX_SS)
			p_redn_opt->ss_id = 0;
		else 
			p_redn_opt->ss_id = ss_id + 1;
	}

	return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_fill_sp_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function fills the SP entry into redn sp data structure.
**
******************************************************************************/

void
sccp_redn_fill_sp_entry
#ifdef ANSI_PROTO
	 (sp_id_t				sp_id,
	  sp_entry_t 			*p_sp,
	  sccp_redn_sp_entry_t	*p_redn_data)
#else
	(sp_id, p_sp, p_redn_data)
	sp_id_t					sp_id;
	sp_entry_t      		*p_sp;
	sccp_redn_sp_entry_t    *p_redn_data;
#endif
{
	p_redn_data->sp_id  	= sp_id;
	p_redn_data->allowed 	= p_sp->allowed;

	p_redn_data->upu_received 	= p_sp->upu_received;
	p_redn_data->upu_cause 		= p_sp->upu_cause;

	p_redn_data->rl 			= p_sp->rl;
	p_redn_data->rsl 			= p_sp->rsl;
	p_redn_data->cls 			= p_sp->cls;
	p_redn_data->ril 			= p_sp->ril;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_send_sp_data
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to report the SP redundancy data in both
**		solicited and unsolicited modes; In unsolicited mode the transaction
**		id argument will be 0 and the ss id argument will contain the SP id 
**		if the SP entry that must be sent to SM for updation. In the solicited
**		mode this function iterates thru' SP ids and sends all the configured 
**		SP entries to SM for updation. In this case, the transaction id 
**		argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_sp_data
#ifdef ANSI_PROTO
	(sccp_redn_options_t 		*p_redn_opt,
	 s7_len_t 						*p_msg_len,
	 U8bit 						*p_redn_data,
	 pvoid						*p_p_segment_info,
	 error_t					*p_ecode)
#else
	(p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
	sccp_redn_options_t         *p_redn_opt ;
	s7_len_t          				*p_msg_len ;
	U8bit          				*p_redn_data ;
	pvoid						*p_p_segment_info ;
	error_t						*p_ecode ;
#endif
{
	sp_entry_t			*p_sp ;
	sp_id_t				sp_id, next_sp_id;
	sccp_redn_options_t *p_segment_info;
	U8bit				*p_entry;
	U16bit				nentries;

	/** Send SP data **/
	p_entry = p_redn_data;

	if (*p_p_segment_info != SS7_NULL)
	{
		/* Continue from the previous dispatch */
		p_segment_info =(sccp_redn_options_t*) *p_p_segment_info;
/* start added during CC compilation */
/* assign  sccp_redn_options_t*to pvoid to */
/* end added during CC compilation */
		next_sp_id = p_segment_info->sp_id;
		nentries = p_segment_info->nentries;
		sccp_free ((buffer_t*) p_segment_info);
/* start added during CC compilation */
/* assign  buffer_t*to pvoid to */
/* end added during CC compilation */

		*p_p_segment_info = SS7_NULL;
	}
	else
	{
		/* New Transaction */
		if (p_redn_opt != SS7_NULL)
		{
			/* return 'nentries' number of configured entries starting from
			** sp_id 
			*/
			next_sp_id = p_redn_opt->sp_id;
			nentries = p_redn_opt->nentries;
		}
		else
		{
			/* return all configured entries */
			next_sp_id = 0;
			nentries = MAX_SP;
		}
	}

	for (sp_id=next_sp_id; sp_id<MAX_SP; ++sp_id)
	{
		p_sp = GET_SP_FROM_ID (sp_id) ;
		if (IS_SP_CONFIGURED(p_sp))
		{
			if ((p_entry + sizeof(sccp_redn_sp_entry_t)) > 
				(p_redn_data + *p_msg_len))
			{
				/* No more space in the Redn buffer but more data to be 
				** filled; return the current sp id in p_p_segment_info
				*/
				/** SPR# 9302 Start Fix **/
				p_segment_info = 
						(sccp_redn_options_t*) (void *)sccp_malloc (sizeof(sccp_redn_options_t));
				/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* */
/* end added during CC compilation */
				if (p_segment_info == SS7_NULL)
				{
					*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
					return SS7_FAILURE;
				}
				p_segment_info->sp_id = sp_id;
				p_segment_info->nentries = nentries;
				*p_p_segment_info = p_segment_info;
				*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);
				return SS7_SUCCESS;
			}

			sccp_redn_fill_sp_entry(
				sp_id, p_sp, (sccp_redn_sp_entry_t*) p_entry); 
/* start added during CC compilation */
/* assign pvoid to sccp_redn_sp_entry_t*  */
/* end added during CC compilation */


			p_entry += sizeof(sccp_redn_sp_entry_t);
			nentries --;
			if (nentries == 0)
				break;
		}
	}
	*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

	if (p_redn_opt != SS7_NULL)
	{
		if (sp_id == MAX_SP)
			p_redn_opt->sp_id = 0;
	}

	return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_fill_reg_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function fills the REG entry into redn data structure.
**
******************************************************************************/

void
sccp_redn_fill_reg_entry
#ifdef ANSI_PROTO
	 (U8bit					reg_entry_id,
	  sc_reg_entry_t 		*p_reg_entry,
	  sccp_redn_reg_entry_t	*p_redn_data)
#else
	(reg_entry_id, p_reg_entry, p_redn_data)
	U8bit					reg_entry_id;
	sc_reg_entry_t 			*p_reg_entry;
	sccp_redn_reg_entry_t	*p_redn_data;
#endif
{
	pc_t	sp_id;

	p_redn_data->reg_entry_id	= reg_entry_id;

	sp_id = GET_ID_FROM_SP(p_reg_entry->p_sp);
	p_redn_data->sp_id = sp_id;

	p_redn_data->ssn 		= p_reg_entry->ssn;

	p_redn_data->log_user_id = p_reg_entry->uid;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_send_reg_data
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to report the registration data to SM in both
**		solicited and unsolicited modes; In unsolicited mode the transaction
**		id argument will be 0 and the ss id argument will contain the SP id 
**		if the SP entry that must be sent to SM for updation. In the solicited
**		mode this function iterates thru' SP ids and sends all the configured 
**		SP entries to SM for updation. In this case, the transaction id 
**		argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_reg_data
#ifdef ANSI_PROTO
	(sccp_redn_options_t 		*p_redn_opt,
	 s7_len_t 						*p_msg_len,
	 U8bit 						*p_redn_data,
	 pvoid						*p_p_segment_info,
	 error_t					*p_ecode)
#else
	(p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
	sccp_redn_options_t         *p_redn_opt ;
	s7_len_t          				*p_msg_len ;
	U8bit          				*p_redn_data ;
	pvoid						*p_p_segment_info ;
	error_t						*p_ecode ;
#endif
{
	U8bit				*p_entry;
	sccp_redn_options_t *p_segment_info;
	sc_reg_entry_t		*p_reg_entry;
	U8bit				reg_entry_id, next_reg_entry_id;
	U16bit				nentries;


	/** Send Reg data **/
	p_entry = p_redn_data;

	if (*p_p_segment_info != SS7_NULL)
	{
		/* Continue from the previous dispatch */
		p_segment_info =(sccp_redn_options_t*) *p_p_segment_info;
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* */
/* end added during CC compilation */
		next_reg_entry_id = p_segment_info->reg_entry_id;
		nentries = p_segment_info->nentries;
		sccp_free ((buffer_t*)p_segment_info);
/* start added during CC compilation */
/* assign pvoid to buffer_t* */
/* end added during CC compilation */

		*p_p_segment_info = SS7_NULL;
	}
	else
	{
		/* New Transaction */
		if (p_redn_opt != SS7_NULL)
		{
			/* return 'nentries' number of registered entries starting from
			** reg_entry_id 
			*/
			next_reg_entry_id = p_redn_opt->reg_entry_id;
			nentries = p_redn_opt->nentries;
		}
		else
		{
			/* return all configured entries */
			next_reg_entry_id = 0;
			nentries = MAX_LOCAL_USERS;
		}
		/* SPR 8701 Fix Start */
#if 0
		/* SPR 8701 Fix Ends */
			next_reg_entry_id = 0;
		/* SPR 8701 Fix Start */
#endif
		/* SPR 8701 Fix Ends */
	}

	for (reg_entry_id=next_reg_entry_id; reg_entry_id<MAX_LOCAL_USERS; ++reg_entry_id)
	{
		p_reg_entry = GET_REG_ENTRY_FROM_ID(reg_entry_id);
		if (GET_REG_STATUS(p_reg_entry) == SS7_TRUE)
		{
			if ((p_entry + sizeof(sccp_redn_reg_entry_t)) > 
				(p_redn_data + *p_msg_len))
			{
				/* No more space in the Redn buffer but more data to be 
				** filled; return the current reg id in p_p_segment_info
				*/
				/** SPR# 9302 Start Fix **/
				p_segment_info = 
						(sccp_redn_options_t*) (void *)sccp_malloc (sizeof(sccp_redn_options_t));
				/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* */
/* end added during CC compilation */
				if (p_segment_info == SS7_NULL)
				{
					*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
					return SS7_FAILURE;
				}
				p_segment_info->reg_entry_id = reg_entry_id;
				*p_p_segment_info = p_segment_info;
				*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);
				return SS7_SUCCESS;
			}
			/** SPR# 9302 Start Fix **/
			sccp_redn_fill_reg_entry(
				reg_entry_id, p_reg_entry, (sccp_redn_reg_entry_t*) (void *)p_entry); 
			/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to sccp_redn_reg_entry_t* */
/* end added during CC compilation */

			p_entry += sizeof(sccp_redn_reg_entry_t);
			nentries --;
			if (nentries == 0)
				break;
		}
	}
	*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

	if (p_redn_opt != SS7_NULL)
	{
		if (reg_entry_id == MAX_LOCAL_USERS)
			p_redn_opt->reg_entry_id = 0;
	}

	return (SS7_SUCCESS) ;
}

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_fill_scoc_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function fills the CCB entry into redn data structure.
**
******************************************************************************/

void
sccp_redn_fill_scoc_entry
#ifdef ANSI_PROTO
	 (U32bit					ccb_id,
	  sccp_ccb_t 				*p_ccb_entry,
	  sccp_redn_scoc_entry_t	*p_redn_data)
#else
	(ccb_id, p_ccb_entry, p_redn_data)
	U32bit					ccb_id;
	sccp_ccb_t 				*p_ccb_entry;
	sccp_redn_scoc_entry_t	*p_redn_data;
#endif
{
	U8bit	i;
	ss_id_t	ss_id;

	p_redn_data->ccb_id 	= ccb_id;

	/* Reset is not a stable state; So an update must never contain this
	** state as the current state
	*/
	if (p_ccb_entry->c_state == SCCP_CONN_RESET)
		p_redn_data->c_state = SCCP_CONN_ESTABLISHED;
	else
		p_redn_data->c_state = p_ccb_entry->c_state;
	p_redn_data->c_status 	= p_ccb_entry->c_status;
	p_redn_data->wait_for_cc_flag = p_ccb_entry->wait_for_cc_flag;

	p_redn_data->conn_id	= p_ccb_entry->conn_id;

	p_redn_data->log_user_id = p_ccb_entry->l_id;

	p_redn_data->corr_id		= p_ccb_entry->corr_id;
	p_redn_data->proto_class	= p_ccb_entry->proto_class;

	p_redn_data->slr		= p_ccb_entry->slr;
	
	p_redn_data->dlr		= p_ccb_entry->dlr;
	
	p_redn_data->sls			= p_ccb_entry->sls;

	p_redn_data->opc		= p_ccb_entry->opc;
	
	ss_id = GET_ID_FROM_SS(p_ccb_entry->p_ss);
	p_redn_data->ss_id		= ss_id;
	
	p_redn_data->cld_pc_ind		= p_ccb_entry->cd_addr.pc_ind;
	p_redn_data->cld_ssn_ind	= p_ccb_entry->cd_addr.ssn_ind;
	p_redn_data->cld_gti		= p_ccb_entry->cd_addr.gti;
	p_redn_data->cld_rout_ind	= p_ccb_entry->cd_addr.rout_ind;
	p_redn_data->cld_pc 		= p_ccb_entry->cd_addr.pc;
	p_redn_data->cld_ssn		= p_ccb_entry->cd_addr.ssn;
	p_redn_data->cld_gt_len		= p_ccb_entry->cd_addr.gt_len;
	for (i=0; i<MAX_GT_LEN; ++i)
		p_redn_data->cld_gt[i] = p_ccb_entry->cd_addr.gt[i];
	p_redn_data->cld_nat_ind	= p_ccb_entry->cd_addr.nat_ind;

	p_redn_data->dpc		= p_ccb_entry->dpc;
	
	p_redn_data->clg_pc_ind		= p_ccb_entry->cg_addr.pc_ind;
	p_redn_data->clg_ssn_ind	= p_ccb_entry->cg_addr.ssn_ind;
	p_redn_data->clg_gti		= p_ccb_entry->cg_addr.gti;
	p_redn_data->clg_rout_ind	= p_ccb_entry->cg_addr.rout_ind;
	p_redn_data->clg_pc			= p_ccb_entry->cg_addr.pc;
	p_redn_data->clg_ssn		= p_ccb_entry->cg_addr.ssn;
	p_redn_data->clg_gt_len		= p_ccb_entry->cg_addr.gt_len;
	for (i=0; i<MAX_GT_LEN; ++i)
		p_redn_data->clg_gt[i] = p_ccb_entry->cg_addr.gt[i];
	p_redn_data->clg_nat_ind	= p_ccb_entry->cg_addr.nat_ind;

	p_redn_data->coupled_ccb_id = p_ccb_entry->coupled_ccb_id;
#if 0
	p_redn_data->credit			= p_ccb_entry->w;
#endif
/* SPR# 8556  Starts  -samip */

	p_redn_data->credit			= p_ccb_entry->credit;

/* SPR# 8556  Ends  */
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_get_scoc_data
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to report the registration data to SM in both
**		solicited and unsolicited modes; In unsolicited mode the transaction
**		id argument will be 0 and the ss id argument will contain the SP id 
**		if the SP entry that must be sent to SM for updation. In the solicited
**		mode this function iterates thru' SP ids and sends all the configured 
**		SP entries to SM for updation. In this case, the transaction id 
**		argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_scoc_data
#ifdef ANSI_PROTO
	(sccp_redn_options_t 		*p_redn_opt,
	 s7_len_t 						*p_msg_len,
	 U8bit 						*p_redn_data,
	 pvoid						*p_p_segment_info,
	 error_t					*p_ecode)
#else
	(p_redn_opt, p_msg_len, p_redn_data, p_ecode)
	sccp_redn_options_t         *p_redn_opt ;
	s7_len_t          				*p_msg_len ;
	U8bit          				*p_redn_data ;
	pvoid						*p_p_segment_info ;
	error_t						*p_ecode ;
#endif
{
	U8bit				*p_entry;
	sccp_redn_options_t *p_segment_info;
	sccp_ccb_t			*p_ccb_entry;
	U32bit				ccb_id, next_ccb_id;
	/* U16bit				nentries, nentries_req; */
	U32bit				nentries, nentries_req;


	if (*p_p_segment_info != SS7_NULL)
	{
		/* Continue from the previous dispatch */
		p_segment_info =(sccp_redn_options_t*) *p_p_segment_info;
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* */
/* end added during CC compilation */
		next_ccb_id = p_segment_info->ccb_id;
		nentries = p_segment_info->nentries;
		sccp_free ((buffer_t*)p_segment_info);
/* start added during CC compilation */
/* assign pvoid to buffer_t* */
/* end added during CC compilation */

		*p_p_segment_info = SS7_NULL;
	}
	else
	{
		/* New Transaction */
		if (p_redn_opt != SS7_NULL)
		{
			/* return 'nentries' number of non-idle entries starting from
			** ccb_id 
			*/
			next_ccb_id = p_redn_opt->ccb_id;
			nentries = p_redn_opt->nentries;
		}
		else
		{
			/* return all configured entries */
			next_ccb_id = 0;
			nentries = MAX_SCCP_CO_CONNECTIONS;
		}
	}


	/** Send SCOC data **/
	p_entry = p_redn_data;
	nentries_req = nentries;

	for (ccb_id=next_ccb_id; ccb_id<MAX_SCCP_CO_CONNECTIONS; ++ccb_id)
	{
		p_ccb_entry = &sccp_ccb[ccb_id];

		/* If unsolicited, send even if idle; nentries_req is used 
		** to determine whether the request is unsolicited 
		*/ 
		if ((p_ccb_entry->c_state != SCCP_CONN_IDLE) ||
			(nentries_req == 1)) 
		{
			if ((p_entry + sizeof(sccp_redn_scoc_entry_t)) > 
				(p_redn_data + *p_msg_len))
			{
				/* No more space in the Redn buffer but more data to be 
				** filled; return the current ccb id in p_p_segment_info
				*/
				/** SPR# 9302 Start Fix **/
				p_segment_info = 
						(sccp_redn_options_t*) (void *)sccp_malloc (sizeof(sccp_redn_options_t));
				/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to  sccp_redn_options_t*  */
/* end added during CC compilation */

				if (p_segment_info == SS7_NULL)
				{
					*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
					return SS7_FAILURE;
				}
				p_segment_info->ccb_id = ccb_id;
				p_segment_info->nentries = nentries;
				*p_p_segment_info = p_segment_info;
				*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);
				return SS7_SUCCESS;
			}
			/** SPR# 9302 Start Fix **/
			sccp_redn_fill_scoc_entry(ccb_id, p_ccb_entry, 
					(sccp_redn_scoc_entry_t*) (void *)p_entry); 
			/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to  sccp_redn_scoc_entry_t*  */
/* end added during CC compilation */

			p_entry += sizeof(sccp_redn_scoc_entry_t);
			nentries --;
			if (nentries == 0)
				break;
		}
	}
	*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

	if (p_redn_opt != SS7_NULL)
	{
		if (ccb_id == MAX_SCCP_CO_CONNECTIONS)
			p_redn_opt->ccb_id = 0;
		else
			p_redn_opt->ccb_id = ccb_id + 1; /* Next CCB to be filled */
	}

	return (SS7_SUCCESS) ;
}
#endif

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_fill_sclc_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function fills the SCLC entry into redn data structure.
**
******************************************************************************/

void
sccp_redn_fill_sclc_entry
#ifdef ANSI_PROTO
	 ( U32bit					slr,
	  sccp_redn_sclc_entry_t	*p_redn_data)
#else
	(slr, p_redn_data)
	U32bit 					slr;
	sccp_redn_sclc_entry_t	*p_redn_data;
#endif
{
	p_redn_data->slr  = slr;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_send_sclc_data
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to report the SCLC data to SM in both
**		solicited and unsolicited modes; In unsolicited mode the transaction
**		id argument will be 0 and the ss id argument will contain the SP id 
**		if the SP entry that must be sent to SM for updation. In the solicited
**		mode this function iterates thru' SP ids and sends all the configured 
**		SP entries to SM for updation. In this case, the transaction id 
**		argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_sclc_data
#ifdef ANSI_PROTO
	(sccp_redn_options_t 		*p_redn_opt,
	 s7_len_t 		*p_msg_len,
	 U8bit 		*p_redn_data,
	 pvoid		*p_p_segment_info,
	 error_t* 	p_ecode)
#else
	(p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
	sccp_redn_options_t          *p_redn_opt ;
	s7_len_t          *p_msg_len ;
	U8bit          *p_redn_data ;
	pvoid		   *p_p_segment_info;
	error_t*       p_ecode ;
#endif
{
	U8bit				*p_entry;
	extern U32bit		segmentation_local_ref; /* defined in sc_segm.c */

	if (*p_p_segment_info != SS7_NULL)
	{
		sccp_free((buffer_t*) *p_p_segment_info);
/* start added during CC compilation */
/* assign pvoid to buffer_t* */
/* end added during CC compilation */
		*p_p_segment_info = SS7_NULL;
	}

	/** Send SCLC data **/
	p_entry = p_redn_data;

	/** SPR# 9302 Start Fix **/
	sccp_redn_fill_sclc_entry(
			segmentation_local_ref, (sccp_redn_sclc_entry_t*) (void *)p_entry); 
	/** SPR# 9302 End Fix **/	
/* start added during  CC compilation */
/* assign pvoid to sccp_redn_sclc_entry_t* */
/* end added during  CC compilation */

	p_entry += sizeof(sccp_redn_sclc_entry_t);
	*p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

	return (SS7_SUCCESS) ;
/* SPR 9302 - Fix Start */
	p_redn_opt = SS7_NULL;
	p_ecode = 0;
/* SPR 9302 - Fix End   */
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_fill_init_entry
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function fills the INIT entry into init data structure.
**
******************************************************************************/

void
sccp_redn_fill_init_entry
#ifdef ANSI_PROTO
     ( U8bit                   redn_stack_type,
      sccp_redn_init_entry_t    *p_redn_data)
#else
    (slr, p_redn_data)
    U8bit                  redn_stack_type;
    sccp_redn_init_entry_t  *p_redn_data;
#endif
{
    p_redn_data->stack_type  = redn_stack_type;
}


/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_send_init_data
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is used to report the INIT data to SM in both
**      solicited and unsolicited modes; In unsolicited mode the transaction
**      id argument will be 0 . In solicited mode, the transaction id
**      argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_init_data
#ifdef ANSI_PROTO
    (sccp_redn_options_t        *p_redn_opt,
     s7_len_t       *p_msg_len,
     U8bit      *p_redn_data,
     pvoid      *p_p_segment_info,
     error_t*   p_ecode)
#else
    (p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
    sccp_redn_options_t          *p_redn_opt ;
    s7_len_t          *p_msg_len ;
    U8bit          *p_redn_data ;
    pvoid          *p_p_segment_info;
    error_t*       p_ecode ;
#endif
{
    U8bit               *p_entry;

    if (*p_p_segment_info != SS7_NULL)
    {
        sccp_free((buffer_t*) *p_p_segment_info);
/* start added during CC compilation */
/* assign pvoid to buffer_t* */
/* end added during CC compilation */
        *p_p_segment_info = SS7_NULL;
    }

    /** Send INIT data **/
    p_entry = p_redn_data;

    sccp_redn_fill_init_entry(
            sc_opt.standard, (sccp_redn_init_entry_t*) p_entry);
/* start added during  CC compilation */
/* assign pvoid to sccp_redn_init_entry_t* */
/* end added during  CC compilation */

    p_entry += sizeof(sccp_redn_init_entry_t);
    *p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

    return (SS7_SUCCESS) ;
/* SPR 9302 - Fix Start */
	p_redn_opt = SS7_NULL;
	p_ecode = 0;
/* SPR 9302 - Fix End   */
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_fill_deinit_entry
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function fills the DEINIT entry into init data structure.
**
******************************************************************************/

void
sccp_redn_fill_deinit_entry
#ifdef ANSI_PROTO
     ( U8bit                   redn_sccp_state,
      sccp_redn_deinit_entry_t    *p_redn_data)
#else
    (sccp_state, p_redn_data)
    U8bit                  redn_sccp_state;
    sccp_redn_deinit_entry_t  *p_redn_data;
#endif
{
#ifdef SCCP_INCLUDE_CO_SERVICE
	extern timer_id_t	deinit_timer_id;
    p_redn_data->deinit_timer_id  = deinit_timer_id;
#else
    p_redn_data->deinit_timer_id  = 0;
#endif 
    p_redn_data->sccp_state  = redn_sccp_state;
}


/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_send_deinit_data
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is used to report the DEINIT data to SM in both
**      solicited and unsolicited modes; In unsolicited mode the transaction
**      id argument will be 0 . In solicited mode, the transaction id
**      argument must be equal to that of the corresponding request API.
**
******************************************************************************/

return_t
sccp_redn_get_deinit_data
#ifdef ANSI_PROTO
    (sccp_redn_options_t        *p_redn_opt,
     s7_len_t       *p_msg_len,
     U8bit      *p_redn_data,
     pvoid      *p_p_segment_info,
     error_t*   p_ecode)
#else
    (p_redn_opt, p_msg_len, p_redn_data, p_p_segment_info, p_ecode)
    sccp_redn_options_t          *p_redn_opt ;
    s7_len_t          *p_msg_len ;
    U8bit          *p_redn_data ;
    pvoid          *p_p_segment_info;
    error_t*       p_ecode ;
#endif
{
    U8bit               *p_entry;
	extern 	U8bit			sccp_state;

    if (*p_p_segment_info != SS7_NULL)
    {
        sccp_free((buffer_t*) *p_p_segment_info);
/* start added during CC compilation */
/* assign pvoid to buffer_t* */
/* end added during CC compilation */
        *p_p_segment_info = SS7_NULL;
    }

    /** Send DEINIT data **/
    p_entry = p_redn_data;

	/** SPR# 9302 Start Fix **/
    sccp_redn_fill_deinit_entry(
            sccp_state, (sccp_redn_deinit_entry_t*)(void *) p_entry);
	/** SPR# 9302 End Fix **/
/* start added during  CC compilation */
/* assign pvoid to sccp_redn_deinit_entry_t* */
/* end added during  CC compilation */

    p_entry += sizeof(sccp_redn_deinit_entry_t);
    *p_msg_len = ((U8bit *)p_entry) - ((U8bit *)p_redn_data);

    return (SS7_SUCCESS) ;
/* SPR 9302 - Fix Start */
	p_redn_opt = SS7_NULL;
	p_ecode = 0;
/* SPR 9302 - Fix End   */
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_send_ss_entry_update
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called when stable states update is to be
**		sent to the other entity (active to standby or vice - versa)
**		for remote machine states
**
******************************************************************************/

return_t
sccp_send_ss_entry_update
#ifdef ANSI_PROTO
	(ss_id_t	ss_id)
#else
	(ss_id)
	ss_id_t        ss_id ;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info;
	sccp_redn_ss_entry_t	redn_entry;
	U8bit					*p_redn_buf;
	s7_len_t					mesg_len ;
	error_t					ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */	
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */	


	p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation */
/* assign pvoid to U8bit* */
/* end added during CC compilation */

	mesg_len = sizeof(sccp_redn_ss_entry_t);
	redn_opt.ss_id = ss_id;
	redn_opt.nentries = 1;
	p_segment_info = SS7_NULL;

/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */	
	p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */	

	if (sccp_request_active (SCCP_REDN_DATA_SS_ENTRY, &redn_opt,
				&mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode) 
			== SS7_FAILURE) 
	{
		return (SS7_FAILURE);
	}
	/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */
	if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_SS_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
	{
		return (SS7_FAILURE) ;
	}

	return (SS7_SUCCESS) ;
	/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_send_sp_entry_update
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called when stable states update is to be
**		sent to the other entity (active to standby or vice - versa)
**		for remote machine states
**
******************************************************************************/

return_t
sccp_send_sp_entry_update
#ifdef ANSI_PROTO
	(sp_id_t	sp_id)
#else
	(sp_id)
	sp_id_t        sp_id ;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info ;
	sccp_redn_sp_entry_t	redn_entry;
	pvoid					p_redn_buf ;
	s7_len_t					mesg_len ;
	error_t					ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	p_redn_buf = (pvoid) &redn_entry;
	mesg_len = sizeof(sccp_redn_sp_entry_t);
	
	redn_opt.sp_id = sp_id;
	redn_opt.nentries = 1;
	p_segment_info = SS7_NULL;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	if (sccp_request_active (SCCP_REDN_DATA_SP_ENTRY, &redn_opt,
				&mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode) 
			== SS7_FAILURE) 
	{
		return (SS7_FAILURE);
	}
	/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */
	if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_SP_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
	{
		return (SS7_FAILURE) ;
	}

	return (SS7_SUCCESS) ;
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_send_reg_entry_update
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called when stable states update is to be
**		sent to the other entity (active to standby or vice - versa)
**		for remote machine states
**
******************************************************************************/

return_t
sccp_send_reg_entry_update
#ifdef ANSI_PROTO
	(U8bit	reg_entry_id)
#else
	(reg_entry_id)
	U8bit  reg_entry_id ;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info ;
	sccp_redn_reg_entry_t	redn_entry;
	U8bit					*p_redn_buf ;
	s7_len_t					mesg_len ;
	error_t					ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation*/
/* assign pvoid to U8bit* */
/* end added during CC compilation*/
	mesg_len = sizeof(sccp_redn_reg_entry_t);
	
	redn_opt.reg_entry_id = reg_entry_id;
	redn_opt.nentries = 1;
	p_segment_info = SS7_NULL;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	if (sccp_request_active (SCCP_REDN_DATA_REG_ENTRY, &redn_opt,
				&mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode) 
			== SS7_FAILURE) 
	{
		return (SS7_FAILURE);
	}
/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */	

	if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_REG_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
	{
		return (SS7_FAILURE) ;
	}

	return (SS7_SUCCESS) ;
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
/******************************************************************************
**
**	FUNCTION :
**		sccp_send_scoc_entry_update
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called when stable states update is to be
**		sent to the other entity (active to standby or vice - versa)
**		for remote machine states
**
******************************************************************************/

return_t
sccp_send_scoc_entry_update
#ifdef ANSI_PROTO
	(U32bit	ccb_id)
#else
	(ccb_id)
	U32bit  ccb_id ;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info ;
	sccp_redn_scoc_entry_t	redn_entry;
	U8bit					*p_redn_buf ;
	s7_len_t					mesg_len ;
	error_t					ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation */
/* assign pvoid to U8bit* */
/* end added during CC compilation */
	mesg_len = sizeof(sccp_redn_scoc_entry_t);
	
	redn_opt.ccb_id = ccb_id;
	redn_opt.nentries = 1;
	p_segment_info = SS7_NULL;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	if (sccp_request_active (SCCP_REDN_DATA_SCOC_ENTRY, &redn_opt,
				&mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode) 
			== SS7_FAILURE) 
	{
		return (SS7_FAILURE);
	}
/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */	
	if ( ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_SCOC_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
	{
		return (SS7_FAILURE) ;
	}

	return (SS7_SUCCESS) ;
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}
#endif

/******************************************************************************
**
**	FUNCTION :
**		sccp_send_sclc_entry_update
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called when stable states update is to be
**		sent to the other entity (active to standby or vice - versa)
**		for remote machine states
**
******************************************************************************/

return_t
sccp_send_sclc_entry_update
#ifdef ANSI_PROTO
	(U32bit slr)
#else
	(slr)
        U32bit slr;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info ;
	sccp_redn_sclc_entry_t	redn_entry;
	U8bit					*p_redn_buf ;
	s7_len_t					mesg_len ;
	error_t					ecode ;

/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

	p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation */
/* assign pvoid to U8bit* */
/* end added during CC compilation */
	mesg_len = sizeof(sccp_redn_sclc_entry_t);
	
	p_segment_info = SS7_NULL;
	/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
/*  p_redn_info = &redn_opt;*/
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */
	if (sccp_request_active (SCCP_REDN_DATA_SCLC_ENTRY, &redn_opt,
				&mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode) 
			== SS7_FAILURE) 
	{
		return (SS7_FAILURE);
	}
/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */	
	if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_SCLC_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
	{
		return (SS7_FAILURE) ;
	}

	return (SS7_SUCCESS) ;
/* SPR 9302 - Fix Start */
	slr = 0;
/* SPR 9302 - Fix End   */
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
	
}


/******************************************************************************
**
**  FUNCTION :
**      sccp_send_dereg_entry_update
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is called when stable states update is to be
**      sent to the other entity (active to standby or vice - versa)
**      for remote machine states
**
******************************************************************************/

return_t
sccp_send_dereg_entry_update
#ifdef ANSI_PROTO
    (U8bit  reg_entry_id)
#else
    (reg_entry_id)
    U8bit  reg_entry_id ;
#endif
{
    sccp_redn_options_t     redn_opt, *p_segment_info ;
    sccp_redn_reg_entry_t   redn_entry;
    U8bit                   *p_redn_buf ;
    s7_len_t                    mesg_len ;
    error_t                 ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */
    p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation*/
/* assign pvoid to U8bit* */
/* end added during CC compilation*/
    mesg_len = sizeof(sccp_redn_reg_entry_t);

    redn_opt.reg_entry_id = reg_entry_id;
    redn_opt.nentries = 1;
    p_segment_info = SS7_NULL;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */
/* We'll Fill Entry Here itself */
#if 0
    if (sccp_request_active (SCCP_REDN_DATA_DEREG_ENTRY, &redn_opt,
                &mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode) 
            == SS7_FAILURE)
    {
        return (SS7_FAILURE);
    }
#endif

	sccp_redn_fill_reg_entry(
                reg_entry_id, GET_REG_ENTRY_FROM_ID(reg_entry_id),  &redn_entry);

	mesg_len=sizeof(sccp_redn_reg_entry_t);
	p_redn_buf = (void *)(&redn_entry);

/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */
    if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_DEREG_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
    {
        return (SS7_FAILURE) ;
    }

    return (SS7_SUCCESS) ;
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_send_init_entry_update
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is called when stable states update is to be
**      sent to the other entity (active to standby or vice - versa)
**      for remote machine states
**
******************************************************************************/

return_t
sccp_send_init_entry_update
#ifdef ANSI_PROTO
    (U8bit  local_stack_type)
#else
    (local_stack_type)
    U8bit  local_stack_type ;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info ;
    sccp_redn_init_entry_t   redn_entry;
    U8bit                   *p_redn_buf ;
    s7_len_t                    mesg_len ;
    error_t                 ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

    p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation*/
/* assign pvoid to U8bit* */
/* end added during CC compilation*/
    mesg_len = sizeof(sccp_redn_init_entry_t);

  	redn_opt.stack_type = local_stack_type;
    redn_opt.nentries = 1;
    p_segment_info = SS7_NULL;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

    if (sccp_request_active (SCCP_REDN_DATA_INIT_ENTRY, &redn_opt,
                &mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode)
            == SS7_FAILURE)
    {
        return (SS7_FAILURE);
    }
/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */
  	if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_INIT_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
    {
        return (SS7_FAILURE) ;
    }

    return (SS7_SUCCESS) ;
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_send_deinit_entry_update
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is called when stable states update is to be
**      sent to the other entity (active to standby or vice - versa)
**      for remote machine states
**
******************************************************************************/

return_t
sccp_send_deinit_entry_update
#ifdef ANSI_PROTO
    (U8bit  local_sccp_state )
#else
    (local_sccp_state)
    U8bit local_sccp_state ;
#endif
{
	sccp_redn_options_t		redn_opt, *p_segment_info ;
    sccp_redn_deinit_entry_t   redn_entry;
    U8bit                   *p_redn_buf ;
    s7_len_t                    mesg_len ;
    error_t                 ecode ;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  sccp_redn_options_t *p_redn_info ;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

    p_redn_buf = (U8bit*) &redn_entry;
/* start added during CC compilation*/
/* assign pvoid to U8bit* */
/* end added during CC compilation*/
    mesg_len = sizeof(sccp_redn_deinit_entry_t);

    redn_opt.sccp_state = local_sccp_state;
    redn_opt.nentries = 1;
    p_segment_info = SS7_NULL;
/* Added by Amaresh start as on dated 11-03-16  for sending unsolicited data */
  p_redn_info = SS7_NULL;
  p_redn_info = &redn_opt;
/* Added by Amaresh stop as on dated 11-03-16  for sending unsolicited data */

    if (sccp_request_active (SCCP_REDN_DATA_DEINIT_ENTRY, &redn_opt,
                &mesg_len, (pvoid) p_redn_buf, (pvoid *) &p_segment_info, &ecode)
            == SS7_FAILURE)
    {
        return (SS7_FAILURE);
    }
/* Modified by Amaresh start as on dated 11-03-16 by passing redn_opt  */
    if (ss7_send_update( SCCP_MODULE_ID, SCCP_REDN_DATA_DEINIT_ENTRY,p_redn_info,mesg_len, p_redn_buf, &ecode) == SS7_FAILURE)
    {
        return (SS7_FAILURE) ;
    }

    return (SS7_SUCCESS) ;
/* Modified by Amaresh stop as on dated 11-03-16 by passing redn_opt  */
}
/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_ss_update_database
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called by common ss7 system management
**		to update the database related to ss_entry on the standby
**		side
**
******************************************************************************/

return_t
sccp_redn_ss_update_database
#ifdef ANSI_PROTO
	(s7_len_t		msg_len,
	 pvoid		p_redn_buf,
	 error_t	*p_ecode)
#else
	(msg_len, p_redn_buf, p_ecode)
	s7_len_t          msg_len ;
	pvoid          p_redn_buf ;
	error_t        *p_ecode ;
#endif
{
	sccp_redn_ss_entry_t	*p_redn_data;
	ss_id_t			ss_id ;
	ss_entry_t		*p_ss ;
	U16bit			nentries, i;
	U8bit			*p_entry;

	nentries = msg_len / sizeof(sccp_redn_ss_entry_t);

	SC_REDN_TRC (("SCCP::REDN: # SS entries for updation = %d\n", nentries));

	p_entry =(U8bit*) p_redn_buf;
/* start added during CC compilation */
/* assign pvoid to U8bit* */
/* end added during CC compilation */
	for (i=0; i<nentries; ++i)
	{
		p_redn_data = (sccp_redn_ss_entry_t*) p_entry;
		p_entry += sizeof(sccp_redn_ss_entry_t);

		ss_id = p_redn_data->ss_id ; 
		p_ss = GET_SS_FROM_ID (ss_id) ;

		SC_REDN_TRC (("SCCP::REDN: Updating ssn %d on sp_id %d\n",
				p_ss->ssn, p_ss->sp_id));

		if (!IS_SS_CONFIGURED (p_ss))
		{
			SC_REDN_TRC(("SCCP::REDN:ERROR: ssn %d on sp_id %d not configured",
				p_ss->ssn, p_ss->sp_id));
				
			*p_ecode = ESCCP_SS_NOT_CONFIGURED ;
			return (SS7_FAILURE) ;
		}

		p_ss->allowed = p_redn_data->allowed ;
	}

	return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_sp_update_database
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called by common ss7 system management
**		to update the database related to sp_entry on the standby
**		side
**
******************************************************************************/

return_t
sccp_redn_sp_update_database
#ifdef ANSI_PROTO
	(s7_len_t		msg_len,
	 pvoid		p_redn_buf,
	 error_t	*p_ecode)
#else
	(msg_len, p_redn_buf, p_ecode)
	s7_len_t          msg_len ;
	pvoid          p_redn_buf ;
	error_t        *p_ecode ;
#endif
{
	sccp_redn_sp_entry_t	*p_redn_data;
	sp_id_t			sp_id ;
	sp_entry_t		*p_sp ;
	U16bit			nentries, i;
	U8bit			*p_entry;

	nentries = msg_len / sizeof(sccp_redn_sp_entry_t);

	SC_REDN_TRC (("SCCP::REDN: # SP entries for updation = %d\n", nentries));

	p_entry =(U8bit*) p_redn_buf;
/* start added during CC compilation */
/* assign pvoid to U8bit* */
/* end added during CC compilation */
	for (i=0; i<nentries; ++i)
	{
		p_redn_data = (sccp_redn_sp_entry_t*) p_entry;
		p_entry += sizeof(sccp_redn_sp_entry_t);

		sp_id = p_redn_data->sp_id ;
		p_sp = GET_SP_FROM_ID (sp_id) ;

		SC_REDN_TRC (("SCCP::REDN: Updating pc %d on mw_id %d\n",
				p_sp->pc, p_sp->nw_id));

		if (!IS_SP_CONFIGURED (p_sp))
		{
			SC_REDN_TRC(("SCCP::REDN:ERROR: pd %d on nw_id %d not configured",
				p_sp->pc, p_sp->nw_id));

			*p_ecode = ESCCP_SP_NOT_CONFIGURED ;
			return (SS7_FAILURE) ;
		}

		p_sp->allowed = p_redn_data->allowed ;
		p_sp->upu_received = p_redn_data->upu_received ;
		p_sp->upu_cause = p_redn_data->upu_cause ;
		p_sp->rl = p_redn_data->rl ;
		p_sp->rsl = p_redn_data->rsl ;
		p_sp->cls = p_redn_data->cls ;
		p_sp->ril = p_redn_data->ril ;
	}

	return (SS7_SUCCESS) ;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_reg_update_database
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called by common ss7 system management
**		to update the database related to reg_entry on the standby
**		side
**
******************************************************************************/

return_t
sccp_redn_reg_update_database
#ifdef ANSI_PROTO
	(s7_len_t		msg_len,
	 pvoid		p_redn_buf,
	 error_t	*p_ecode)
#else
	(msg_len, p_redn_buf, p_ecode)
	s7_len_t          msg_len ;
	pvoid          p_redn_buf ;
	error_t        *p_ecode ;
#endif
{
	sccp_redn_reg_entry_t	*p_redn_data;
	U32bit			sp_id;
	U8bit			reg_entry_id ;
	sc_reg_entry_t	*p_reg_entry ;
	U16bit			nentries, i;
	U8bit			*p_entry;

	*p_ecode = 0;

	nentries = msg_len / sizeof(sccp_redn_reg_entry_t);

	SC_REDN_TRC (("SCCP::REDN: # REG entries for updation = %d\n", nentries));

	p_entry =(U8bit*) p_redn_buf;
/* start added during CC compilation */
 /* assign pvoid to U8bit* */
/* end added during CC compilation */

	for (i=0; i<nentries; ++i)
	{
		/** SPR# 9302 Start Fix **/
		p_redn_data = (sccp_redn_reg_entry_t*)(void *) p_entry;
		/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to sccp_redn_reg_entry_t*  */
/* end added during CC compilation */

		p_entry += sizeof(sccp_redn_reg_entry_t);

		reg_entry_id = (U8bit) (p_redn_data->reg_entry_id);
		p_reg_entry = GET_REG_ENTRY_FROM_ID(reg_entry_id);

		p_reg_entry->registered = SS7_TRUE;

		sp_id = p_redn_data->sp_id ; 
		p_reg_entry->p_sp = GET_SP_FROM_ID (sp_id) ;

		p_reg_entry->ssn = p_redn_data->ssn;
		p_reg_entry->uid = p_redn_data->log_user_id ;

		p_reg_entry->p_ss = sccp_db_find_ss(
								p_reg_entry->p_sp, p_reg_entry->ssn);
		sccp_register_ssn(
			GET_ID_FROM_SS(p_reg_entry->p_ss), p_reg_entry->uid);

		SC_REDN_TRC (("SCCP::REDN: ssn %d on pc %d (nw_id %d) is registered\n",
				p_reg_entry->p_ss->ssn, p_reg_entry->p_sp->pc, 
				p_reg_entry->p_sp->nw_id));
	}

	return (SS7_SUCCESS) ;
}


/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_dereg_update_database
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is called by common ss7 system management
**      to update the database related to reg_entry on the standby
**      side
**
******************************************************************************/

return_t
sccp_redn_dereg_update_database
#ifdef ANSI_PROTO
    (s7_len_t       msg_len,
     pvoid      p_redn_buf,
     error_t    *p_ecode)
#else
    (msg_len, p_redn_buf, p_ecode)
    s7_len_t          msg_len ;
    pvoid          p_redn_buf ;
    error_t        *p_ecode ;
#endif
{
    sccp_redn_reg_entry_t   *p_redn_data;
    U32bit          sp_id;
    U8bit           reg_entry_id ;
    sc_reg_entry_t  *p_reg_entry ;
    U16bit          nentries, i;
    U8bit           *p_entry;

    *p_ecode = 0;

    nentries = msg_len / sizeof(sccp_redn_reg_entry_t);

    SC_REDN_TRC (("SCCP::REDN: # DEREG entries for updation = %d\n", nentries));

    p_entry =(U8bit*) p_redn_buf;
/* start added during CC compilation */
 /* assign pvoid to U8bit* */
/* end added during CC compilation */

    for (i=0; i<nentries; ++i)
    {
		/** SPR# 9302 Start Fix **/
        p_redn_data = (sccp_redn_reg_entry_t*)(void *) p_entry;
		/** SPR# 9302 End Fix **/
/* start added during CC compilation */
/* assign pvoid to sccp_redn_reg_entry_t*  */
/* end added during CC compilation */

        p_entry += sizeof(sccp_redn_reg_entry_t);

        reg_entry_id = (U8bit) (p_redn_data->reg_entry_id);
        p_reg_entry = GET_REG_ENTRY_FROM_ID(reg_entry_id);

        p_reg_entry->registered = SS7_FALSE;

        sp_id = p_redn_data->sp_id ;
        p_reg_entry->p_sp = GET_SP_FROM_ID (sp_id) ;

        p_reg_entry->ssn = p_redn_data->ssn;
        p_reg_entry->uid = p_redn_data->log_user_id ;

        p_reg_entry->p_ss = sccp_db_find_ss(
                                p_reg_entry->p_sp, p_reg_entry->ssn);
        sccp_deregister_ssn(
            GET_ID_FROM_SS(p_reg_entry->p_ss), p_reg_entry->uid);

        SC_REDN_TRC (("SCCP::REDN: ssn %d on pc %d (nw_id %d) is De-Registered\n",
                p_reg_entry->p_ss->ssn, p_reg_entry->p_sp->pc,
                p_reg_entry->p_sp->nw_id));
    }

    return (SS7_SUCCESS) ;
}

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_scoc_update_database
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called by common ss7 system management
**		to update the database related to ccb_entry on the standby
**		side
**
******************************************************************************/

return_t
sccp_redn_scoc_update_database
#ifdef ANSI_PROTO
	(s7_len_t		msg_len,
	 pvoid		p_redn_buf,
	 error_t	*p_ecode)
#else
	(msg_len, p_redn_buf, p_ecode)
	s7_len_t          msg_len ;
	pvoid          p_redn_buf ;
	error_t        *p_ecode ;
#endif
{
	sccp_redn_scoc_entry_t	*p_redn_data;
	U32bit			ccb_id, ss_id ;
	sccp_ccb_t		*p_ccb_entry ;
	U16bit			nentries, i, j;
	U8bit			*p_entry;

	*p_ecode = 0;

	nentries = msg_len / sizeof(sccp_redn_scoc_entry_t);

	SC_REDN_TRC (("SCCP::REDN: # SCOC entries for updation = %d\n", nentries));

	p_entry =(U8bit*) p_redn_buf;
/* start added during CC compilation */
/* assign pvoid to U8bit * */
/* end added during CC compilation */
	for (i=0; i<nentries; ++i)
	{
		/** SPR# 9302 Start Fix **/
		p_redn_data = (sccp_redn_scoc_entry_t*)(void *) p_entry;
		/** SPR# 9302 End Fix **/
/* start added during CC compilation */
 /* assign pvoid to sccp_redn_scoc_entry_t*  */
/* end added during CC compilation */

		p_entry += sizeof(sccp_redn_scoc_entry_t);


		ccb_id = p_redn_data->ccb_id ;
		p_ccb_entry = &(sccp_ccb [ccb_id]);

		p_ccb_entry->c_state = p_redn_data->c_state;
		p_ccb_entry->c_status = p_redn_data->c_status;

		/* SPR 10258 - Fix Start */
		p_ccb_entry->wait_for_cc_flag = p_redn_data->wait_for_cc_flag;
		/* SPR 10258 - Fix End   */
		
		p_ccb_entry->conn_id = p_redn_data->conn_id ;
		p_ccb_entry->l_id = p_redn_data->log_user_id ;
		p_ccb_entry->ccb_id = ccb_id;
		p_ccb_entry->corr_id = p_redn_data->corr_id;
		p_ccb_entry->proto_class = p_redn_data->proto_class;

		p_ccb_entry->slr = p_redn_data->slr; 
		p_ccb_entry->dlr = p_redn_data->dlr; 
		p_ccb_entry->sls = p_redn_data->sls;

		p_ccb_entry->opc = p_redn_data->opc ;
		ss_id = p_redn_data->ss_id;
		p_ccb_entry->p_ss = GET_SS_FROM_ID(ss_id);

		p_ccb_entry->cd_addr.pc_ind = p_redn_data ->cld_pc_ind;
		p_ccb_entry->cd_addr.ssn_ind = p_redn_data ->cld_ssn_ind;
		p_ccb_entry->cd_addr.gti = p_redn_data ->cld_gti;
		p_ccb_entry->cd_addr.rout_ind = p_redn_data ->cld_rout_ind;
		p_ccb_entry->cd_addr.pc = p_redn_data->cld_pc;
		p_ccb_entry->cd_addr.ssn = p_redn_data ->cld_ssn;
		p_ccb_entry->cd_addr.gt_len = p_redn_data ->cld_gt_len;
		for (j=0; j<MAX_GT_LEN; ++j)
			p_ccb_entry->cd_addr.gt[j] = p_redn_data->cld_gt[j];
		p_ccb_entry->cd_addr.nat_ind = p_redn_data ->cld_nat_ind;
		
	
		p_ccb_entry->dpc = p_redn_data->dpc; 
		
		p_ccb_entry->cg_addr.pc_ind = p_redn_data ->clg_pc_ind;
		p_ccb_entry->cg_addr.ssn_ind = p_redn_data ->clg_ssn_ind;
		p_ccb_entry->cg_addr.gti = p_redn_data ->clg_gti;
		p_ccb_entry->cg_addr.rout_ind = p_redn_data ->clg_rout_ind;
		p_ccb_entry->cg_addr.pc = p_redn_data->clg_pc;
		p_ccb_entry->cg_addr.ssn = p_redn_data ->clg_ssn;
		p_ccb_entry->cg_addr.gt_len = p_redn_data ->clg_gt_len;
		for (j=0; j<MAX_GT_LEN; ++j)
			p_ccb_entry->cg_addr.gt[j] = p_redn_data->clg_gt[j];
		p_ccb_entry->cg_addr.nat_ind = p_redn_data ->clg_nat_ind;

		p_ccb_entry->coupled_ccb_id = p_redn_data->coupled_ccb_id;
		
		p_ccb_entry->credit = p_redn_data->credit;
		p_ccb_entry->w = p_ccb_entry->credit;

		SC_REDN_TRC(("SCCP::REDN: Updated conn id %d (ccb_id = %d)\n",
				p_ccb_entry->conn_id, p_ccb_entry->ccb_id));
	}

	return (SS7_SUCCESS) ;
}
#endif

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_sclc_update_database
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is called by common ss7 system management
**		to update the Segmentation Local Reference on the standby
**		side
**
******************************************************************************/

return_t
sccp_redn_sclc_update_database
#ifdef ANSI_PROTO
	(s7_len_t		msg_len,
	 pvoid		p_redn_buf,
	 error_t	*p_ecode)
#else
	(msg_len, p_redn_buf, p_ecode)
	s7_len_t          msg_len ;
	pvoid          p_redn_buf ;
	error_t        *p_ecode ;
#endif
{
	sccp_redn_sclc_entry_t	*p_redn_data;
	extern U32bit		segmentation_local_ref; /* defined in sc_segm.c */

	p_redn_data = (sccp_redn_sclc_entry_t*) p_redn_buf;
	segmentation_local_ref = p_redn_data->slr;

	return SS7_SUCCESS;
/* SPR 9302 - Fix Start */
	msg_len = 0;
	p_ecode = 0;
/* SPR 9302 - Fix End   */
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_init_update_database
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is called by common ss7 system management
**      to update the state on standby side
**
******************************************************************************/
return_t
sccp_redn_init_update_database
#ifdef ANSI_PROTO
    (s7_len_t       msg_len,
     pvoid      p_redn_buf,
     error_t    *p_ecode)
#else
    (msg_len, p_redn_buf, p_ecode)
    s7_len_t          msg_len ;
    pvoid          p_redn_buf ;
    error_t        *p_ecode ;
#endif
{
	S8bit * p_err_str1 =(S8bit *) "standard not included at compile time";
	extern sp_entry_t sccp_local_sp;
	extern U8bit sccp_state ;
	/* Removing Warning */
	/* extern U8bit sccp_data_state ;*/
	return_t  ret_val;
	sc_init_opt_t			sc_init_opt;
	sccp_gtt_sm_info_t      gtt_sm_info;

    sccp_redn_init_entry_t  *p_redn_data;

    p_redn_data = (sccp_redn_init_entry_t*) p_redn_buf;



    switch ( p_redn_data->stack_type)
    {
	        case STACK_ITU:
#ifdef SCCP_CHINESE
            SC_IN_TRC (("SCCP::INIT: ITU initialized\n"));
            break;
#else
#ifndef SCCP_ITU
            SC_IN_TRC (("SCCP::INIT: ITU %s\n", p_err_str1));
            *p_ecode = ESS7_INVALID_STANDARD;
            return SS7_FAILURE;
#else
            SC_IN_TRC (("SCCP::INIT: ITU initialized\n"));
            break;
#endif
#endif

        case STACK_ETSI:
#ifndef SCCP_ETSI
            SC_IN_TRC (("SCCP::INIT: ETSI %s\n", p_err_str1));
            *p_ecode = ESS7_INVALID_STANDARD;
            return SS7_FAILURE;
#else
            SC_IN_TRC (("SCCP::INIT: ETSI initialized\n"));
            break;
#endif

        case STACK_ANSI:
#ifndef SCCP_ANSI
            SC_IN_TRC (("SCCP::INIT: ANSI %s\n", p_err_str1));
            *p_ecode = ESS7_INVALID_STANDARD;
            return SS7_FAILURE;
#else
            SC_IN_TRC (("SCCP::INIT: ANSI initialized\n"));
            break;
#endif

        case STACK_BCGR:
#ifndef SCCP_BCGR
            SC_IN_TRC (("SCCP::INIT: BCGR %s\n", p_err_str1));
            *p_ecode = ESS7_INVALID_STANDARD;
            return SS7_FAILURE;
#else
            SC_IN_TRC (("SCCP::INIT: BCGR initialized\n"));
            break;
#endif

		case STACK_JAPANESE:
#ifndef SCCP_JAPANESE
            SC_IN_TRC (("SCCP::INIT: JAPANESE %s\n", p_err_str1));
            *p_ecode = ESS7_INVALID_STANDARD;
            return SS7_FAILURE;
#else
            SC_IN_TRC (("SCCP::INIT: JAPANESE initialized\n"));
            break;
#endif


        default:
            SC_IN_TRC (("SCCP::INIT: %d standard unknown", p_redn_data->stack_type));
            *p_ecode = ESS7_INVALID_STANDARD;
            return SS7_FAILURE;
    }

    /** SPR # 2757 Fix Start **/
    sccp_local_sp.conf_status = SC_NOT_CONFIGURED ; /* not configured  */
    /** SPR # 2757 Fix Start **/
    sccp_state = STACK_INITIALIZED;
    sc_opt.standard =  p_redn_data->stack_type;

#ifdef DISTRIBUTED_SCCP
	/* Deinit, Init not supported in DSCCP */
	/* return(SS7_FAILURE); */ 
#endif

#if 0
    if (UNINITIALIZED == sccp_data_state)
    {
#endif
        ret_val = sccp_default_init_data(p_ecode);
#if 0
    }
#endif

    SC_IN_TRC (("SCCP::INIT:init %s\n", RESULT_STR(ret_val)));

#ifdef SCCP_INCLUDE_CO_SERVICE
    SC_IN_TRC (("SCCP::BEFORE CALLING sccp_init_co_service"));
    sccp_init_co_service ( p_redn_data->stack_type) ;
    SC_IN_TRC (("SCCP::AFTER CALLING sccp_init_co_service"));
#endif

	sc_init_opt.standard = p_redn_data->stack_type;

	/* SPR 11115 Start Fix */
	/* Calling GTT database init via porting */
	sccp_init_complete_indication(&sc_init_opt);

	/* Adding default MTPSAP via porting  */
    ss7_mem_zero((void *) (&gtt_sm_info), sizeof(sccp_gtt_sm_info_t));
    gtt_sm_info.info_id = SCCP_SM_ADD_MTPSAP;
    gtt_sm_info.sccp_gtt_add_mtpsap_info = 
         (sccp_gtt_add_mtpsap_info_t *)(void *)sccp_malloc(sizeof(sccp_gtt_add_mtpsap_info_t));
    if (SS7_NULL == gtt_sm_info.sccp_gtt_add_mtpsap_info) /* Memory Allocation Failure */
                {
                        *(p_ecode) = ESS7_MEMORY_ALLOCATION_FAILURE;
                        return(SS7_FAILURE);
                }
    gtt_sm_info.sccp_gtt_add_mtpsap_info->mtpsap = 0;
    gtt_sm_info.sccp_gtt_add_mtpsap_info->p_ecode = p_ecode;

    ret_val = sccp_update_gtt_sm_info (&gtt_sm_info);
	/* SPR 11115 End Fix */

    return ret_val;
/* SPR 9302 - Fix Start */
    msg_len = 0;
	p_err_str1 = SS7_NULL;
/* SPR 9302 - Fix End   */
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_deinit_update_database
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is called by common ss7 system management
**      to update the state on standby side
**
******************************************************************************/
return_t
sccp_redn_deinit_update_database
#ifdef ANSI_PROTO
    (s7_len_t       msg_len,
     pvoid      p_redn_buf,
     error_t    *p_ecode)
#else
    (msg_len, p_redn_buf, p_ecode)
    s7_len_t          msg_len ;
    pvoid          p_redn_buf ;
    error_t        *p_ecode ;
#endif
{
	extern U8bit sccp_state;
	extern U8bit sccp_data_state ;
	extern timer_id_t deinit_timer_id;
    sccp_redn_deinit_entry_t  *p_redn_data;
    p_redn_data = (sccp_redn_deinit_entry_t*) p_redn_buf;
	
	sccp_state = p_redn_data->sccp_state;
	sccp_data_state = UNINITIALIZED;
#ifdef SCCP_INCLUDE_CO_SERVICE
	deinit_timer_id = p_redn_data->deinit_timer_id;
#endif
	return(SS7_SUCCESS);
/* SPR 9302 - Fix Start */
	msg_len = 0;
	p_ecode = 0;
/* SPR 9302 - Fix End   */
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_pack_ss_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to pack raw SS entry data structure into an API
**	buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_ss_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_ss_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_filled)
#else
	(p_api_elem, p_redn_entry, p_len_filled)
	U8bit		*p_api_elem;
	sccp_redn_ss_entry_t		*p_redn_entry;
	s7_len_t		*p_len_filled;
#endif
{
	s7_len_t 	offset;

	*p_len_filled = 0;
	offset = 0;

	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id >> 24);

	p_api_elem[offset++] = p_redn_entry->allowed;

	*p_len_filled = offset;
	return;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_pack_sp_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to pack raw SP entry data structure into an API
**	buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_sp_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_sp_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_filled)
#else
	(p_api_elem, p_redn_entry, p_len_filled)
	U8bit		*p_api_elem;
	sccp_redn_sp_entry_t		*p_redn_entry;
	s7_len_t		*p_len_filled;
#endif
{
	s7_len_t 	offset;

	*p_len_filled = 0;
	offset = 0;

	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id >> 24);

	p_api_elem[offset++] = p_redn_entry->allowed;
	p_api_elem[offset++] = p_redn_entry->upu_received;
	p_api_elem[offset++] = p_redn_entry->upu_cause;
	p_api_elem[offset++] = p_redn_entry->rl;
	p_api_elem[offset++] = p_redn_entry->rsl;
	p_api_elem[offset++] = p_redn_entry->cls;
	p_api_elem[offset++] = p_redn_entry->ril;

	*p_len_filled = offset;
	return;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_pack_reg_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to pack raw REG entry data structure into an API
**	buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_reg_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_reg_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_filled)
#else
	(p_api_elem, p_redn_entry, p_len_filled)
	U8bit		*p_api_elem;
	sccp_redn_reg_entry_t		*p_redn_entry;
	s7_len_t		*p_len_filled;
#endif
{
	s7_len_t 	offset;

	*p_len_filled = 0;
	offset = 0;

	p_api_elem[offset++] = (U8bit) (p_redn_entry->reg_entry_id);
	
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->sp_id >> 24);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->ssn);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->log_user_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->log_user_id >> 8);

	*p_len_filled = offset;
	return;
}

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_pack_scoc_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to pack raw SCOC entry data structure into an API
**	buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_scoc_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_scoc_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_filled)
#else
	(p_api_elem, p_redn_entry, p_len_filled)
	U8bit		*p_api_elem;
	sccp_redn_scoc_entry_t		*p_redn_entry;
	s7_len_t		*p_len_filled;
#endif
{
	s7_len_t 	offset, i;

	*p_len_filled = 0;
	offset = 0;

	p_api_elem[offset++] = (U8bit) (p_redn_entry->ccb_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ccb_id >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->c_state);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->c_status);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->wait_for_cc_flag);
     #ifdef SCCP_CONNECTION_ID_CHANGES
        p_api_elem[offset++] = (U8bit) (p_redn_entry->conn_id);
        p_api_elem[offset++] = (U8bit) (p_redn_entry->conn_id >> 8);
        p_api_elem[offset++] = (U8bit) (p_redn_entry->conn_id >> 16);
        p_api_elem[offset++] = (U8bit) (p_redn_entry->conn_id >> 24);
     #else
	p_api_elem[offset++] = (U8bit) (p_redn_entry->conn_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->conn_id >> 8);
     #endif 
	p_api_elem[offset++] = (U8bit) (p_redn_entry->log_user_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->log_user_id >> 8);
     #ifdef SCCP_CONNECTION_ID_CHANGES
        p_api_elem[offset++] = (U8bit) (p_redn_entry->corr_id);
        p_api_elem[offset++] = (U8bit) (p_redn_entry->corr_id >> 8); 
     #else
	p_api_elem[offset++] = (U8bit) (p_redn_entry->corr_id);
     #endif   
	p_api_elem[offset++] = (U8bit) (p_redn_entry->proto_class);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->slr);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->slr >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->slr >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->dlr);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->dlr >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->dlr >> 16);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->sls);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->opc);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->opc >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->opc >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->opc >> 24);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->ss_id >> 24);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_pc_ind);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_ssn_ind);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_gti);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_rout_ind);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_pc);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_pc >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_pc >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_pc >> 24);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_ssn);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_gt_len);
	for (i=0; i<p_redn_entry->cld_gt_len; ++i)
		p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_gt[i]);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->cld_nat_ind);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->dpc);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->dpc >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->dpc >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->dpc >> 24);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_pc_ind);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_ssn_ind);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_gti);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_rout_ind);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_pc);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_pc >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_pc >> 16);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_pc >> 24);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_ssn);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_gt_len);
	for (i=0; i<p_redn_entry->clg_gt_len; ++i)
		p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_gt[i]);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->clg_nat_ind);

	p_api_elem[offset++] = (U8bit) (p_redn_entry->coupled_ccb_id);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->coupled_ccb_id >> 8);

	p_api_elem[offset++] = (U8bit) p_redn_entry->credit;

	*p_len_filled = offset;
	return;
}
#endif

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_pack_sclc_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to pack raw SCLC entry data structure into an API
**	buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_sclc_entry
#ifdef ANSI_PROTO
	( U8bit		*p_api_elem,
	 sccp_redn_sclc_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_filled)
#else
	(p_api_elem, p_redn_entry, p_len_filled)
	U8bit		*p_api_elem;
	sccp_redn_sclc_entry_t		*p_redn_entry;
	s7_len_t		*p_len_filled;
#endif
{
	s7_len_t 	offset;

	*p_len_filled = 0;
	offset = 0;

	p_api_elem[offset++] = (U8bit) (p_redn_entry->slr);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->slr >> 8);
	p_api_elem[offset++] = (U8bit) (p_redn_entry->slr >> 16);

	*p_len_filled = offset;
	return;
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_pack_init_entry
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is used to pack raw INIT entry data structure into an API
**  buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_init_entry
#ifdef ANSI_PROTO
    ( U8bit     *p_api_elem,
     sccp_redn_init_entry_t     *p_redn_entry,
     s7_len_t       *p_len_filled)
#else
    (p_api_elem, p_redn_entry, p_len_filled)
    U8bit       *p_api_elem;
    sccp_redn_init_entry_t      *p_redn_entry;
    s7_len_t        *p_len_filled;
#endif
{
    s7_len_t    offset;

    *p_len_filled = 0;
    offset = 0;

    p_api_elem[offset++] = (U8bit) (p_redn_entry->stack_type);

    *p_len_filled = offset;
    return;
}


/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_pack_deinit_entry
**      
*******************************************************************************
**
**  DESCRIPTION :
**      This function is used to pack raw DEINIT entry data structure into an API
**  buffer. The length of the packed entry is returned in p_len_filled
**  
******************************************************************************/

void
sccp_redn_pack_deinit_entry
#ifdef ANSI_PROTO
    ( U8bit     *p_api_elem,
     sccp_redn_deinit_entry_t     *p_redn_entry,
     s7_len_t       *p_len_filled)
#else
    (p_api_elem, p_redn_entry, p_len_filled)
    U8bit       *p_api_elem;
    sccp_redn_deinit_entry_t      *p_redn_entry;
    s7_len_t        *p_len_filled;
#endif
{
    s7_len_t    offset;

    *p_len_filled = 0;
    offset = 0;

    p_api_elem[offset++] = (U8bit) (p_redn_entry->sccp_state);


	/* Changed Coz timer_id is 32 bit */  
    p_api_elem[offset++] = (U8bit) (p_redn_entry->deinit_timer_id);
    p_api_elem[offset++] = (U8bit) (p_redn_entry->deinit_timer_id >> 8);
    p_api_elem[offset++] = (U8bit) (p_redn_entry->deinit_timer_id >> 16);
    p_api_elem[offset++] = (U8bit) (p_redn_entry->deinit_timer_id >> 24);

    *p_len_filled = offset;
    return;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_pack_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to pack raw redn data structure into an API
**	buffer. The length of the packed entry is returned in p_len_filled
**
******************************************************************************/

void
sccp_redn_pack_entry
#ifdef ANSI_PROTO
	(U8bit		type_of_data,
	 U8bit		*p_api_elem,
	 pvoid		p_redn_entry,
	 s7_len_t		*p_len_filled)
#else
	(type_of_data, p_api_elem, p_redn_entry, p_len_filled)
	U8bit		type_of_data;
	U8bit		*p_api_elem;
	pvoid		p_redn_entry;
	s7_len_t		*p_len_filled;
#endif
{
	switch (type_of_data)
	{
	case SCCP_REDN_DATA_SS_ENTRY:
		sccp_redn_pack_ss_entry ( 
				p_api_elem,(sccp_redn_ss_entry_t*) p_redn_entry, p_len_filled);
 /* start added during CC compilation */
/* assign pvoid to sccp_redn_ss_entry_t* */
/* end added during CC compilation */
		return;

	case SCCP_REDN_DATA_SP_ENTRY:
		sccp_redn_pack_sp_entry ( 
				p_api_elem,(sccp_redn_sp_entry_t*) p_redn_entry, p_len_filled);
/* start added during CC compilation */
 /* assign pvoid to sccp_redn_sp_entry_t* */
 /* end added during CC compilation */

		return;

	case SCCP_REDN_DATA_REG_ENTRY:
	case SCCP_REDN_DATA_DEREG_ENTRY: /* Entry is same as  Reg Entry --Sachin */
		sccp_redn_pack_reg_entry ( 
				p_api_elem,(sccp_redn_reg_entry_t*) p_redn_entry, p_len_filled);
/* start added during CC compilation */
/* assign pvoid to sccp_redn_reg_entry_t* */
/* end added during CC compilation */

		return;

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
	case SCCP_REDN_DATA_SCOC_ENTRY:
		sccp_redn_pack_scoc_entry ( 
				p_api_elem,(sccp_redn_scoc_entry_t*) p_redn_entry, p_len_filled);
/* start added during CC compilation */
/* assign pvoid to sccp_redn_scoc_entry_t* */
/* end added during CC compilation */

		return;
#endif

	case SCCP_REDN_DATA_SCLC_ENTRY:
		sccp_redn_pack_sclc_entry ( 
				p_api_elem,(sccp_redn_sclc_entry_t*) p_redn_entry, p_len_filled);
/* start added during CC compilation */
 /* assign pvoid to sccp_redn_sclc_entry_t* */
 /* end added during CC compilation */

		return;

    case SCCP_REDN_DATA_INIT_ENTRY:
	sccp_redn_pack_init_entry (
                p_api_elem,(sccp_redn_init_entry_t*) p_redn_entry, p_len_filled);
		return;

    case SCCP_REDN_DATA_DEINIT_ENTRY:
	sccp_redn_pack_deinit_entry (
                p_api_elem,(sccp_redn_deinit_entry_t*) p_redn_entry, p_len_filled);
		return;


	}

	return;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_send_redn_data_buf
**
*******************************************************************************
**
**	DESCRIPTION:
**  	This function constructs ann sends the response to SM Request Active 
**  API either as a response to the request API or as an unsolicited message.
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
*******************************************************************************
** 
**  NOTE:
** 		The format of the Request Active Response is identical to that of the
**  SM Recv Update API that the SM sends to standby module. The only difference
**  is that the spare octet after Trans id in Recv Update API is used to report
**  the status. 
**
******************************************************************************/

U8bit * 
sccp_build_redn_data_buf
#ifdef ANSI_PROTO
	(U8bit		trans_id,
	 U8bit 		type_of_data,
	 sccp_redn_options_t *p_redn_info,
	 s7_len_t 		redn_msg_len,
	 U8bit 		*p_redn_msg,
	 Boolean	more_data_flag,   
	 U8bit		buf_seq_num,
	 error_t* 	p_ecode)
#else
	(trans_id, type_of_data, p_redn_info, redn_msg_len, p_redn_msg, 
	 more_data_flag, buf_seq_num, p_ecode)
	U8bit	   trans_id;
	U8bit      type_of_data ;
	sccp_redn_options_t *p_redn_info;
	s7_len_t      redn_msg_len ;
	U8bit      *p_redn_msg ;
	Boolean    more_data_flag,   
	U8bit      buf_seq_num,
	error_t*   p_ecode ;
#endif
{
	U16bit				entry_len;
	U8bit				*p_api_buf, *p_elem;
	U8bit				*p_entry;
	U16bit				nentries;
	s7_len_t				len_filled;
	U16bit				i;


	/** calculate number of entries in p_redn_data **/
	switch (type_of_data)
	{
	case SCCP_REDN_DATA_SS_ENTRY:
		entry_len = sizeof(sccp_redn_ss_entry_t);
		break;

	case SCCP_REDN_DATA_SP_ENTRY:
		entry_len = sizeof(sccp_redn_sp_entry_t);
		break;

	case SCCP_REDN_DATA_REG_ENTRY:
		entry_len = sizeof(sccp_redn_reg_entry_t);
		break;

  	case SCCP_REDN_DATA_DEREG_ENTRY:
        entry_len = sizeof(sccp_redn_reg_entry_t);
        break;

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
	case SCCP_REDN_DATA_SCOC_ENTRY:
		entry_len = sizeof(sccp_redn_scoc_entry_t);
		break;
#endif

	case SCCP_REDN_DATA_SCLC_ENTRY:
		entry_len = sizeof(sccp_redn_sclc_entry_t);
		break;

    case SCCP_REDN_DATA_INIT_ENTRY:
        entry_len=sizeof(sccp_redn_init_entry_t);
        break;

    case SCCP_REDN_DATA_DEINIT_ENTRY:
        entry_len=sizeof(sccp_redn_deinit_entry_t);
        break;

	default:
		*p_ecode = ESCCP_WRONG_DATA_TYPE;
		return (SS7_FAILURE);
	}

	nentries = redn_msg_len / entry_len;


	p_api_buf = SS7_NULL;
	if ( (p_api_buf = sccp_malloc(SCCP_SM_REDN_MAX_API_LEN)) == SS7_NULL )
	{
		*p_ecode = ESS7_MEMORY_ALLOCATION_FAILURE;
		return SS7_NULL;
	}

	SC_STAT_API_INR_OUT_API_SM () ;
   	SC_A_TRC (("SCCP::INIT: Building Response to SM Request Active \n"
			   "\t\tTrans id = %d; Total number of Entries = %d; 	"
			   "Type of Data = %d;\n",
				trans_id, nentries, type_of_data));

	/* fill the REQ ACTIVE RESP API buffer for redn data */
	p_entry = p_redn_msg;

	p_elem = p_api_buf + API_HEADER_LEN;
	
	/* category */
	*p_elem = SS7_SM_REDN;
	p_elem += SM_CATEGORY_LEN;

	/* command */
/*	*p_elem = SS7_SM_REDN_REQ_ACT;*//* Orginal commented by Amaresh 29-02-16 for Response Request */
	*p_elem = SS7_SM_REDN_RECV_UPDATE;
	p_elem += SM_COMMAND_LEN;
	
	/* transaction id */
	*p_elem = trans_id;
	p_elem += SM_TRANS_ID_LEN;

	/* Status */
	*p_elem++ = SS7_SUCCESS;

	/* More Data flag */
	*p_elem++ = (U8bit) more_data_flag;
	
	/* Buffer Sequence Number */
	*p_elem++ = (U8bit) buf_seq_num;

	/* Type of data */
	*p_elem++ = type_of_data;

	/** Layer Specific REDN Info **/
	switch (type_of_data)
	{
	case SCCP_REDN_DATA_SS_ENTRY:
		if (p_redn_info != SS7_NULL)
		{
			if (p_redn_info->ss_id != 0)
			{
				*p_elem++ = SS7_TRUE; /* redn info flag */

				*p_elem++ = (U8bit) (p_redn_info->ss_id);
				*p_elem++ = (U8bit) (p_redn_info->ss_id >> 8);
				*p_elem++ = (U8bit) (p_redn_info->ss_id >> 16);
				*p_elem++ = (U8bit) (p_redn_info->ss_id >> 24);
				
				*p_elem++ = (U8bit) (p_redn_info->nentries);
				*p_elem++ = (U8bit) (p_redn_info->nentries >> 8);
			}
			else
			{
				/* Redn Info Flag */
				*p_elem++ = 0; 
				p_elem += 6; /* skip redn info */
			}
		}
		else
		{
			/* Redn Info Flag */
			*p_elem++ = 0; 
			p_elem += 6; /* skip redn info */
		}
		break;

	case SCCP_REDN_DATA_SP_ENTRY:
		if (p_redn_info != SS7_NULL)
		{
			if (p_redn_info->sp_id != 0)
			{
				*p_elem++ = SS7_TRUE; /* redn info flag */

				*p_elem++ = (U8bit) (p_redn_info->sp_id);
				*p_elem++ = (U8bit) (p_redn_info->sp_id >> 8);
				*p_elem++ = (U8bit) (p_redn_info->sp_id >> 16);
				*p_elem++ = (U8bit) (p_redn_info->sp_id >> 24);
				
				*p_elem++ = (U8bit) (p_redn_info->nentries);
				*p_elem++ = (U8bit) (p_redn_info->nentries >> 8);
			}
			else
			{
				/* Redn Info Flag */
				*p_elem++ = 0; 
				p_elem += 6; /* skip redn info */
			}
		}
		else
		{
			/* Redn Info Flag */
			*p_elem++ = 0; 
			p_elem += 6; /* skip redn info */
		}
		break;

	case SCCP_REDN_DATA_DEREG_ENTRY:
	case SCCP_REDN_DATA_REG_ENTRY:
		if (p_redn_info != SS7_NULL)
		{
			if (p_redn_info->reg_entry_id != 0)
			{
				*p_elem++ = SS7_TRUE; /* redn info flag */

				*p_elem++ = (U8bit) ((U32bit)(p_redn_info->reg_entry_id));
				*p_elem++ = (U8bit) ((U32bit)(p_redn_info->reg_entry_id) >> 8);
				*p_elem++ = (U8bit) ((U32bit)(p_redn_info->reg_entry_id) >> 16);
				*p_elem++ = (U8bit) ((U32bit)(p_redn_info->reg_entry_id) >> 24);
				
				*p_elem++ = (U8bit) (p_redn_info->nentries);
				*p_elem++ = (U8bit) (p_redn_info->nentries >> 8);
			}
			else
			{
				/* Redn Info Flag */
				*p_elem++ = 0; 
				p_elem += 6; /* skip redn info */
			}
		}
		else
		{
			/* Redn Info Flag */
			*p_elem++ = 0; 
			p_elem += 6; /* skip redn info */
		}
		break;


/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
	case SCCP_REDN_DATA_SCOC_ENTRY :
		if (p_redn_info != SS7_NULL)
		{
			if (p_redn_info->ccb_id != 0)
			{
				*p_elem++ = SS7_TRUE; /* redn info flag */

				*p_elem++ = (U8bit) (p_redn_info->ccb_id);
				*p_elem++ = (U8bit) (p_redn_info->ccb_id >> 8);
				*p_elem++ = (U8bit) (p_redn_info->ccb_id >> 16);
				*p_elem++ = (U8bit) (p_redn_info->ccb_id >> 24);
				
				*p_elem++ = (U8bit) (p_redn_info->nentries);
				*p_elem++ = (U8bit) (p_redn_info->nentries >> 8);
			}
			else
			{
				/* Redn Info Flag */
				*p_elem++ = 0; 
				p_elem += 6; /* skip redn info */
			}
		}
		else
		{
			/* Redn Info Flag */
			*p_elem++ = 0; 
			p_elem += 6; /* skip redn info */
		}
		break;
#endif

	case SCCP_REDN_DATA_SCLC_ENTRY :
	case SCCP_REDN_DATA_INIT_ENTRY :
	case SCCP_REDN_DATA_DEINIT_ENTRY :
		/* Redn Info Flag */
		*p_elem++ = 0; 
		p_elem += 6; /* skip redn info */
		break;
	}
	
	/* REDN entries */
	for (i=0; i<nentries; ++i)
	{
		sccp_redn_pack_entry(type_of_data, p_elem, p_entry, &len_filled);
		p_elem += len_filled; 
		p_entry += entry_len;
	}

/*	sccp_fill_api_header(p_api_buf, SCCP_SM_RESPONSE_API, 
			SCCP_SM_REDN_REQ_ACT_RESP_NELEM, 
			((U8bit *)p_elem - (U8bit *)p_api_buf));*//* Orginal commented by Amaresh 29-02-16 for Response Request */


	sccp_fill_api_header(p_api_buf, SCCP_SM_REQUEST_API, 
			SCCP_SM_REDN_REQ_ACT_RESP_NELEM, 
			((U8bit *)p_elem - (U8bit *)p_api_buf));


	return p_api_buf;
}

/*****************************************************************************
**      FUNCTION :
**           handles SM command Request Active if REDN is compile time enabled
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_redn_handle_sm_cmd_req_act
#ifdef ANSI_PROTO
	(U8bit * p_api,
	 error_t *p_ecode)
#else
	(p_api, p_ecode)
	 U8bit * p_api;
	 error_t *p_ecode;
#endif
{
	U8bit * p_elem, type_of_data;
	Boolean more_data_flag;
	U8bit buffer_seq_num, entry_len;
	U8bit *p_redn_data=SS7_NULL;
	s7_len_t redn_data_len=0;
	U8bit trans_id;
	Boolean redn_info_flag;
	sccp_redn_options_t redn_info, *p_redn_info;
	sccp_redn_options_t *p_segment_info;
	return_t ret_val;
	U8bit *p_api_buf;
	U8bit redn_data[SS7_MAX_BUFFER_SIZE - SCCP_SM_REDN_REQ_ACT_RESP_MIN_LEN];

	SC_REDN_TRC (("SCCP::REDN: recvd REDN-REQ-ACT\n")); 

	trans_id = *(p_api + SM_TRANS_ID_OFFSET); 

	p_elem = p_api + SS7_SM_API_MIN_LEN;
	type_of_data = *p_elem ++;

	/** Redn Info Specific to SCCP **/
	p_redn_info = SS7_NULL;
	redn_info_flag = *p_elem ++;
	switch (type_of_data)
	{
	case SCCP_REDN_DATA_SS_ENTRY:
		if (redn_info_flag)
		{
			redn_info.ss_id = (U32bit) (*p_elem) | 
					   		((U32bit) *(p_elem+1)) << 8 |
					   		((U32bit) *(p_elem+2)) << 16 |
					   		((U32bit) *(p_elem+3)) << 24;
			p_elem += 4;
			redn_info.nentries = (U16bit) (*p_elem) |
					   		((U16bit) *(p_elem+1)) << 8;
			p_elem += 2;
			p_redn_info = &redn_info;
		}
		else
		{
			/* Skip Redn Info */
			p_elem += 6;
		}
		break;

	case SCCP_REDN_DATA_SP_ENTRY:
		if (redn_info_flag)
		{
			redn_info.sp_id = (U32bit) (*p_elem) | 
					   			((U32bit) *(p_elem+1)) << 8 |
					   			((U32bit) *(p_elem+2)) << 16 |
					   			((U32bit) *(p_elem+3)) << 24;
			p_elem += 4;
			redn_info.nentries = (U16bit) (*p_elem) |
					   			((U16bit) *(p_elem+1)) << 8;
			p_elem += 2;
			p_redn_info = &redn_info;
		}
		else
		{
			/* Skip Redn Info */
			p_elem += 6;
		}
		break;

	case SCCP_REDN_DATA_REG_ENTRY:
		if (redn_info_flag)
		{
			redn_info.reg_entry_id = (U32bit) (*p_elem) | 
					   			((U32bit) *(p_elem+1)) << 8 |
					   			((U32bit) *(p_elem+2)) << 16 |
					   			((U32bit) *(p_elem+3)) << 24;
			p_elem += 4;
			redn_info.nentries = (U16bit) (*p_elem) |
						   		((U16bit) *(p_elem+1)) << 8;
			p_elem += 2;
			p_redn_info = &redn_info;
		}
		break;

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
	case SCCP_REDN_DATA_SCOC_ENTRY :
		if (redn_info_flag)
		{
			redn_info.ccb_id = (U32bit) (*p_elem) | 
						   		((U32bit) *(p_elem+1)) << 8 |
						   		((U32bit) *(p_elem+2)) << 16 |
						   		((U32bit) *(p_elem+3)) << 24;
			p_elem += 4;
			redn_info.nentries = (U16bit) (*p_elem) |
						   		((U16bit) *(p_elem+1)) << 8;
			p_elem += 2;
			p_redn_info = &redn_info;
		}
		else
		{
			/* Skip Redn Info */
			p_elem += 6;
		}
		break;
#endif

	case SCCP_REDN_DATA_SCLC_ENTRY :
	case SCCP_REDN_DATA_INIT_ENTRY :
	case SCCP_REDN_DATA_DEINIT_ENTRY :
		/* Skip Redn Info */
		p_elem += 6;
		break;

	
	default:
		*p_ecode = ESCCP_WRONG_DATA_TYPE;
		return (SS7_FAILURE);
	}

	/** calculate entry len of each entry in the p_redn_data **/
	switch (type_of_data)
	{
	case SCCP_REDN_DATA_SS_ENTRY:
		entry_len = sizeof(sccp_redn_ss_entry_t);
		break;

	case SCCP_REDN_DATA_SP_ENTRY:
		entry_len = sizeof(sccp_redn_sp_entry_t);
		break;

	case SCCP_REDN_DATA_REG_ENTRY:
		entry_len = sizeof(sccp_redn_reg_entry_t);
		break;

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
	case SCCP_REDN_DATA_SCOC_ENTRY:
		entry_len = sizeof(sccp_redn_scoc_entry_t);
		break;
#endif

	case SCCP_REDN_DATA_SCLC_ENTRY:
		entry_len = sizeof(sccp_redn_sclc_entry_t);
		break;

	case SCCP_REDN_DATA_INIT_ENTRY :
		entry_len = sizeof(sccp_redn_init_entry_t);
		break;

	case SCCP_REDN_DATA_DEINIT_ENTRY :
		entry_len = sizeof(sccp_redn_deinit_entry_t);
		break;

	default:
		*p_ecode = ESCCP_WRONG_DATA_TYPE;
		return (SS7_FAILURE);
	}

	buffer_seq_num = 0;
	p_segment_info = SS7_NULL;
	do {
		p_redn_data = (U8bit *)redn_data;
		redn_data_len = SS7_MAX_BUFFER_SIZE -
						SCCP_SM_REDN_REQ_ACT_RESP_MIN_LEN;

		ret_val = sccp_request_active ( 
					type_of_data, p_redn_info, 
					&redn_data_len, (pvoid) p_redn_data, 
					(pvoid *)&p_segment_info, p_ecode);
		if (ret_val == SS7_SUCCESS)
		{
			buffer_seq_num ++;
			more_data_flag = SS7_TRUE;
			if (p_segment_info == SS7_NULL)
				more_data_flag = SS7_FALSE;

			p_api_buf = SS7_NULL;
			p_api_buf = sccp_build_redn_data_buf(
						trans_id, type_of_data, p_redn_info,
						redn_data_len, p_redn_data, 
						more_data_flag, buffer_seq_num,
						p_ecode);
			if (p_api_buf == SS7_NULL)
			{
				/* send standard response to report FAILURE */
				return (SS7_FAILURE);
			}
		sccp_sendto_rm (p_api_buf);/* Added by Amaresh for Redn Message updation */
	/*	sccp_sendto_sm (p_api_buf);*/  /* Redn message send by sccp sccp_send_to_rm function only Amaresh 22-02-16 */
		}
		else
		{
			return (SS7_FAILURE);
		}
	} while (p_segment_info != SS7_NULL);

	return SS7_SUCCESS;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_unpack_ss_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to unpack SS entry data structure from an API
**	buffer. The length of the packed entry in API is returned in 
**	p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_ss_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_ss_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_extracted)
#else
	(p_api_elem, p_redn_entry, p_len_extracted)
	U8bit		*p_api_elem;
	sccp_redn_ss_entry_t		*p_redn_entry;
	s7_len_t		*p_len_extracted;
#endif
{
	s7_len_t 	offset;
	
	SC_REDN_TRC (("SCCP::REDN: Unpacking SS Entry ...\n"));

	offset = 0;
	p_redn_entry->ss_id = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;

	p_redn_entry->allowed = p_api_elem[offset ++];

	*p_len_extracted = offset;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_unpack_sp_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to unpack SP entry data structure from an API
**	buffer. The length of the packed entry in API is returned in 
**	p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_sp_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_sp_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_extracted)
#else
	(p_api_elem, p_redn_entry, p_len_extracted)
	U8bit		*p_api_elem;
	sccp_redn_sp_entry_t		*p_redn_entry;
	s7_len_t		*p_len_extracted;
#endif
{
	s7_len_t 	offset;
	
	SC_REDN_TRC (("SCCP::REDN: Unpacking SP Entry ...\n"));

	offset = 0;
	p_redn_entry->sp_id = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;

	p_redn_entry->allowed 		= p_api_elem[offset ++];
	p_redn_entry->upu_received 	= p_api_elem[offset ++];
	p_redn_entry->upu_cause 	= p_api_elem[offset ++];
	p_redn_entry->rl 			= p_api_elem[offset ++];
	p_redn_entry->rsl 			= p_api_elem[offset ++];
	p_redn_entry->cls 			= p_api_elem[offset ++]; /* SPR # 4322 Fix */
	p_redn_entry->ril 			= p_api_elem[offset ++];

	*p_len_extracted = offset;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_unpack_reg_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to unpack REG entry data structure from an API
**	buffer. The length of the packed entry in API is returned in 
**	p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_reg_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_reg_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_extracted)
#else
	(p_api_elem, p_redn_entry, p_len_extracted)
	U8bit		*p_api_elem;
	sccp_redn_reg_entry_t		*p_redn_entry;
	s7_len_t		*p_len_extracted;
#endif
{
	s7_len_t 	offset;
	
	SC_REDN_TRC (("SCCP::REDN: Unpacking REG Entry ...\n"));

	offset = 0;

	p_redn_entry->reg_entry_id = p_api_elem[offset ++];

	p_redn_entry->sp_id = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;

	p_redn_entry->ssn = p_api_elem[offset ++];

	p_redn_entry->log_user_id = ((U16bit) p_api_elem[offset]) |
						  		(((U16bit) p_api_elem[offset+1]) << 8) ;
	offset += 2;

	*p_len_extracted = offset;
}

/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_unpack_scoc_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to unpack SCOC entry data structure from an API
**	buffer. The length of the packed entry in API is returned in 
**	p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_scoc_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_scoc_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_extracted)
#else
	(p_api_elem, p_redn_entry, p_len_extracted)
	U8bit		*p_api_elem;
	/* sccp_redn_ss_entry_t		*p_redn_entry; */
	/* SPR 8598 Fix Starts */
	sccp_redn_scoc_entry_t		*p_redn_entry; 
	/* SPR 8598 Fix Ends */
	s7_len_t		*p_len_extracted;
#endif
{
	s7_len_t 	offset, i;
	
	SC_REDN_TRC (("SCCP::REDN: Unpacking SCOC Entry ...\n"));

	offset = 0;

	p_redn_entry->ccb_id = ((U16bit) p_api_elem[offset]) |
						   (((U16bit) p_api_elem[offset+1]) << 8) ;
	offset += 2;

	p_redn_entry->c_state = p_api_elem[offset ++];
	p_redn_entry->c_status = p_api_elem[offset ++];
	p_redn_entry->wait_for_cc_flag = p_api_elem[offset ++];
     #ifdef SCCP_CONNECTION_ID_CHANGES
         p_redn_entry->conn_id = ((U32bit) p_api_elem[offset]) |
                                                  (((U32bit) p_api_elem[offset+1]) << 8) |
                                                  (((U32bit) p_api_elem[offset+2]) << 16) |
                                                  (((U32bit) p_api_elem[offset+3]) << 24) ;
        offset += 4;
     #else     
	p_redn_entry->conn_id = ((U16bit) p_api_elem[offset]) |
						   (((U16bit) p_api_elem[offset+1]) << 8) ;
	offset += 2;
     #endif 

	p_redn_entry->log_user_id = ((U16bit) p_api_elem[offset]) |
						   (((U16bit) p_api_elem[offset+1]) << 8) ;
	offset += 2;
#ifdef SCCP_CONNECTION_ID_CHANGES
        p_redn_entry->corr_id = ((U16bit) p_api_elem[offset]) |
                                                   (((U16bit) p_api_elem[offset+1]) << 8) ;
        offset += 2;
#else 
	p_redn_entry->corr_id = p_api_elem[offset ++];
#endif
	p_redn_entry->proto_class = p_api_elem[offset ++];

	p_redn_entry->slr = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) ;
	offset += 3;

	p_redn_entry->dlr = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) ;
	offset += 3;

	p_redn_entry->sls = p_api_elem[offset ++];

	p_redn_entry->opc = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;

	p_redn_entry->ss_id = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;

	p_redn_entry->cld_pc_ind = p_api_elem[offset ++];
	p_redn_entry->cld_ssn_ind = p_api_elem[offset ++];
	p_redn_entry->cld_gti = p_api_elem[offset ++];
	p_redn_entry->cld_rout_ind = p_api_elem[offset ++];
	p_redn_entry->cld_pc = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;
	p_redn_entry->cld_ssn = p_api_elem[offset ++];
	p_redn_entry->cld_gt_len = p_api_elem[offset ++];
	for (i=0; i<p_redn_entry->cld_gt_len; ++i)
		p_redn_entry->cld_gt[i] = p_api_elem[offset ++];
	p_redn_entry->cld_nat_ind = p_api_elem[offset ++];

	p_redn_entry->dpc = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;

	p_redn_entry->clg_pc_ind = p_api_elem[offset ++];
	p_redn_entry->clg_ssn_ind = p_api_elem[offset ++];
	p_redn_entry->clg_gti = p_api_elem[offset ++];
	p_redn_entry->clg_rout_ind = p_api_elem[offset ++];
	p_redn_entry->clg_pc = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) |
						  (((U32bit) p_api_elem[offset+3]) << 24) ;
	offset += 4;
	p_redn_entry->clg_ssn = p_api_elem[offset ++];
	p_redn_entry->clg_gt_len = p_api_elem[offset ++];
	for (i=0; i<p_redn_entry->clg_gt_len; ++i)
		p_redn_entry->clg_gt[i] = p_api_elem[offset ++];
	p_redn_entry->clg_nat_ind = p_api_elem[offset ++];

	p_redn_entry->coupled_ccb_id = ((U16bit) p_api_elem[offset]) |
						   (((U16bit) p_api_elem[offset+1]) << 8) ;
	offset += 2;

	p_redn_entry->credit = p_api_elem[offset ++];

	*p_len_extracted = offset;
}
#endif

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_unpack_sclc_entry
**
*******************************************************************************
**
**	DESCRIPTION :
**		This function is used to unpack SCLC entry data structure from an API
**	buffer. The length of the packed entry in API is returned in 
**	p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_sclc_entry
#ifdef ANSI_PROTO
	(U8bit		*p_api_elem,
	 sccp_redn_sclc_entry_t		*p_redn_entry,
	 s7_len_t		*p_len_extracted)
#else
	(p_api_elem, p_redn_entry, p_len_extracted)
	U8bit		*p_api_elem;
	/* sccp_redn_ss_entry_t		*p_redn_entry; */
	/* SPR 8598 Fix Starts */
	sccp_redn_sclc_entry_t		*p_redn_entry; 
	/* SPR 8598 Fix Ends */
	s7_len_t		*p_len_extracted;
#endif
{
	s7_len_t 	offset;

	SC_REDN_TRC (("SCCP::REDN: Unpacking SCLC Entry ...\n"));
	
	offset = 0;
	p_redn_entry->slr = ((U32bit) p_api_elem[offset]) |
						  (((U32bit) p_api_elem[offset+1]) << 8) |
						  (((U32bit) p_api_elem[offset+2]) << 16) ;
	offset += 3;

	*p_len_extracted = offset;
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_unpack_init_entry
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is used to unpack INIT entry data structure from an API
**  buffer. The length of the packed entry in API is returned in
**  p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_init_entry
#ifdef ANSI_PROTO
    (U8bit      *p_api_elem,
     sccp_redn_init_entry_t     *p_redn_entry,
     s7_len_t       *p_len_extracted)
#else
    (p_api_elem, p_redn_entry, p_len_extracted)
    U8bit       *p_api_elem;
    sccp_redn_init_entry_t        *p_redn_entry;
    s7_len_t        *p_len_extracted;
#endif
{
    s7_len_t    offset;

    SC_REDN_TRC (("SCCP::REDN: Unpacking INIT Entry ...\n"));

    offset = 0;
    p_redn_entry->stack_type = (((U8bit) p_api_elem[offset])) ;
    offset += 1;

    *p_len_extracted = offset;
}

/******************************************************************************
**
**  FUNCTION :
**      sccp_redn_unpack_deinit_entry
**
*******************************************************************************
**
**  DESCRIPTION :
**      This function is used to unpack DEINIT entry data structure from an API
**  buffer. The length of the packed entry in API is returned in
**  p_len_extracted
**
******************************************************************************/

void
sccp_redn_unpack_deinit_entry
#ifdef ANSI_PROTO
    (U8bit      *p_api_elem,
     sccp_redn_deinit_entry_t     *p_redn_entry,
     s7_len_t       *p_len_extracted)
#else
    (p_api_elem, p_redn_entry, p_len_extracted)
    U8bit       *p_api_elem;
    sccp_redn_deinit_entry_t        *p_redn_entry;
    s7_len_t        *p_len_extracted;
#endif
{
    s7_len_t    offset;

    SC_REDN_TRC (("SCCP::REDN: Unpacking DEINIT Entry ...\n"));

    offset = 0;
    p_redn_entry->sccp_state = (((U8bit) p_api_elem[offset])) ;
    offset += 1;

	/* Timer ID has to be read too */
 	p_redn_entry->deinit_timer_id = ((U32bit) p_api_elem[offset]) |
                                                  (((U32bit) p_api_elem[offset+1]) << 8) |
                                                  (((U32bit) p_api_elem[offset+2]) << 16) |
                                                  (((U32bit) p_api_elem[offset+3]) << 24) ;

    offset+=4;


    *p_len_extracted = offset;
}

/******************************************************************************
**
**	FUNCTION :
**		sccp_redn_handle_updates
**
**
*******************************************************************************
**
**	DESCRIPTION:
**	This function is used to unpack the Redn entries from RECV UPDATE api and 
**  update the database
**
**	RETURN VALUE:
**		SS7_SUCCESS
**		SS7_FAILURE
**
******************************************************************************/

return_t 
sccp_redn_handle_updates
#ifdef ANSI_PROTO
	(U8bit 		type_of_data,
	 s7_len_t 		msg_len,
	 U8bit 		*p_redn_data,
	 error_t* 	p_ecode)
#else
	(type_of_data, msg_len, p_redn_data, p_ecode)
	U8bit          type_of_data ;
	s7_len_t          msg_len ;
	pvoid          p_redn_data ;
	error_t*       p_ecode ;
#endif
{
	s7_len_t	offset;
	U8bit	*p_elem;
	sccp_redn_ss_entry_t redn_ss_entry;
	sccp_redn_sp_entry_t redn_sp_entry;
	sccp_redn_reg_entry_t redn_reg_entry;
	sccp_redn_scoc_entry_t redn_scoc_entry;
	sccp_redn_sclc_entry_t redn_sclc_entry;
	sccp_redn_init_entry_t redn_init_entry;
	sccp_redn_deinit_entry_t redn_deinit_entry;
	pvoid 	p_redn_entry;
	s7_len_t	redn_entry_len, packed_entry_len;
	

	offset = 0;
	while (offset <msg_len)
	{
		p_elem = p_redn_data + offset;
		switch(type_of_data)
		{
			case SCCP_REDN_DATA_SS_ENTRY:
			sccp_redn_unpack_ss_entry (
					p_elem, &redn_ss_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_ss_entry;
			redn_entry_len = sizeof(sccp_redn_ss_entry_t);
			break;
	
			case SCCP_REDN_DATA_SP_ENTRY:
			sccp_redn_unpack_sp_entry (
					p_elem, &redn_sp_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_sp_entry;
			redn_entry_len = sizeof(sccp_redn_sp_entry_t);
			break;
	
		
			case SCCP_REDN_DATA_REG_ENTRY:
			sccp_redn_unpack_reg_entry (
					p_elem, &redn_reg_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_reg_entry;
			redn_entry_len = sizeof(sccp_redn_reg_entry_t);
			break;

			case SCCP_REDN_DATA_DEREG_ENTRY:
			sccp_redn_unpack_reg_entry (
					p_elem, &redn_reg_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_reg_entry;
			redn_entry_len = sizeof(sccp_redn_reg_entry_t);
			break;
	
	
/** Added this flag so that code can be compiled wthout CO service */
#ifdef SCCP_INCLUDE_CO_SERVICE
			case SCCP_REDN_DATA_SCOC_ENTRY:
			sccp_redn_unpack_scoc_entry (
					p_elem, &redn_scoc_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_scoc_entry;
			redn_entry_len = sizeof(sccp_redn_scoc_entry_t);
			break;
#endif
	
	
			case SCCP_REDN_DATA_SCLC_ENTRY:
			sccp_redn_unpack_sclc_entry (
					p_elem, &redn_sclc_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_sclc_entry;
			redn_entry_len = sizeof(sccp_redn_sclc_entry_t);
			break;

			case SCCP_REDN_DATA_INIT_ENTRY:
			sccp_redn_unpack_init_entry (
					p_elem, &redn_init_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_init_entry;
			redn_entry_len = sizeof(sccp_redn_init_entry_t);
			break;

			case SCCP_REDN_DATA_DEINIT_ENTRY:
			sccp_redn_unpack_deinit_entry (
					p_elem, &redn_deinit_entry, &packed_entry_len);
			offset += packed_entry_len;
			p_redn_entry = &redn_deinit_entry;
			redn_entry_len = sizeof(sccp_redn_deinit_entry_t);
			break;
	
	
			default:	
				SC_A_TRC (("SCCP::REDN: invalid  data type (%d)\n", 
						type_of_data));
				*p_ecode = ESCCP_WRONG_DATA_TYPE ;
				return(SS7_FAILURE) ;
		}

		if (sccp_receive_update(
						type_of_data, redn_entry_len, p_redn_entry, p_ecode)
				== SS7_FAILURE)
		{
			return SS7_FAILURE;
		}
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**           handles SM command category REDN if REDN is compile time enabled
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_redn_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	error_t ecode;
	Boolean event_reporting;
	U8bit param = 0; Boolean put_param = SS7_FALSE;
	U8bit * p_elem, cmd, type_of_data;
	return_t ret_val = SS7_SUCCESS;
	U16bit api_len, update_seq_num;
	U8bit *p_redn_data=SS7_NULL;
	s7_len_t redn_data_len=0;
	U8bit trans_id;
	Boolean redn_info_flag;
	Boolean more_data_flag;
	/* SPR 10237 - Fix Start */
#ifdef DISTRIBUTED_SCCP       
	U8bit	self_instance_id;
	extern	U8bit		dsccp_instance_status_tbl[]; 
#endif
	/* SPR 10237 - Fix End   */
	extern U8bit sccp_state;


	api_len = GET_API_LEN(p_api);
	trans_id = *(p_api + SM_TRANS_ID_OFFSET); 
	cmd = GET_SM_CMD(p_api);

	switch (cmd)
	{
		case SS7_SM_INIT_REDN_DATA:
		/*	LOG_PRINT(INFO,"SCCP::REDN: recvd INIT-REDN-DATA req\n ");*/
			SC_REDN_TRC (("SCCP::REDN: recvd INIT-REDN-DATA req\n")); 
			extern U8bit sccp_redn_sub_state ;
			p_elem = p_api + SS7_SM_API_MIN_LEN;
			event_reporting = *p_elem;
			ret_val = sccp_init_redn_data (event_reporting, &ecode);
			/* Added by Amaresh start for REDN implementation as on dated 01-06-16 */
			if (p_api[9] == 0x01)
			{
				SC_REDN_TRC (("SCCP::REDN: recvd state as ACTIVE\n")); 
				sccp_redn_sub_state = ACTIVE;
			}
			else
			{
				SC_REDN_TRC (("SCCP::REDN: recvd state as STACK_STANDBY\n")); 
				sccp_redn_sub_state = STACK_STANDBY;
			}
			/* Added by Amaresh stop for REDN implementation as on dated 01-06-16 */
			if (ret_val == SS7_SUCCESS)
			{
					SC_REDN_TRC (("SCCP::REDN: recvd INIT-REDN-DATA req Noresponse from Stack\n")); 
			}
			return;
			break;

		case SS7_SM_REDN_REQ_ACT:
			SC_REDN_TRC (("SCCP::REDN: recvd SS7_SM_REDN_REQ_ACT req\n")); 
			if (sccp_redn_handle_sm_cmd_req_act(p_api, &ecode) == SS7_SUCCESS)
			{
				/* No need to send std response */
				return;
			}
			break;


		case SS7_SM_REDN_RECV_UPDATE:
			SC_REDN_TRC (("SCCP::REDN: recvd REDN-RECV-UPDATE\n")); 
			p_elem = p_api + SS7_SM_API_MIN_LEN;

			p_elem ++; /* skip the reserved octet */

			more_data_flag = *p_elem++;

			update_seq_num = *p_elem++; 

			type_of_data = *p_elem++;

			/* skip redn info */
			redn_info_flag = *p_elem ++;
			p_elem += 6;


			p_redn_data = p_elem;
			redn_data_len = ((U8bit *)p_api + api_len) - (U8bit *)p_redn_data;
			/* SPR 10246 - Fix Start */
			if(((U8bit *)p_api + api_len) < (U8bit *)p_redn_data)
				ret_val=SS7_FAILURE;
			/* SPR 10246 - Fix Start */

			if (ret_val != SS7_FAILURE)
			{
				ret_val = sccp_redn_handle_updates ( 
							type_of_data, redn_data_len, p_redn_data, &ecode);
			}
			break;

		case SS7_SM_ACTIVATE_MODULE:
			SC_REDN_TRC (("SCCP::REDN: recvd ACTIVATE\n")); 
			ret_val = sccp_activate_sccp (&ecode);

			SC_REDN_TRC (("SCCP::REDN: recvd ACTIVATE (%d)\n",ret_val)); 
            /* spr #9243 starts */
            if (ret_val == SS7_SUCCESS)
            {
                extern U8bit sccp_redn_sub_state ;
#ifdef DISTRIBUTED_SCCP       
				/* SPR 10237 - Fix Start */
         		/*extern U8bit sccp_state;*/
        		/* dsccp_notify_self_status(sccp_state | 0x40 , SCCP_MODULE_ID); */
				self_instance_id=sc_opt.dsccp_local_instance_id;
				dsccp_notify_self_status (dsccp_instance_status_tbl[self_instance_id]|0x40,
											SCCP_MODULE_ID);
				/* SPR 10237 - Fix End  */
#endif	
				sccp_redn_sub_state = ACTIVE;
			SC_A_TRC (("SCCP::REDN: sccp_redn_sub_state (%d)\n", sccp_redn_sub_state));

				/* SPR DE-INIT Fix */
	 			if (sccp_state == DEINITIALIZING) 
				{
					SC_A_TRC (("SCCP::REDN: sccp_state (%d)\n", sccp_state));
					/* Receiving Activate in DEINITIALIZING state indicates, incomplete
					 * De-Init procedure at previously active instance. So restarting
					 * De-Init procedure.
					 */
					if (SS7_FAILURE == sccp_deinit(&ecode))
						ret_val = SS7_FAILURE;
				}
            }
						SC_REDN_TRC (("SCCP::REDN: recvd ACTIVATE No response\n")); 
						return; /* Amaresh added no response */
            /* spr #9243 ends */
			break;
            
/* spr #9243 starts */            
#if 0            
/* added by salil */            
/* set state api to set the state of sccp either active of standby so that standby can discard the message and in the case of redn + distributed stack 2 msb can be filled */
        case SS7_SM_REDN_SET_STATE:
            {
                U8bit state;
                SC_REDN_TRC (("SCCP::REDN: recvd SET_STATE\n")); 
                p_elem = p_api + SS7_SM_API_MIN_LEN;
                state  = *p_elem;
                ret_val = sccp_redn_set_state(state, &ecode);
            }
            break;
/* end */
/* added by salil */
/* returns the state of the sccp either ACITVE or STANDBY */
        case SS7_SM_REDN_GET_STATE:
            {
                SC_REDN_TRC(("SCCP::REDN: recvd GET_STATE\n")); 
                ret_val = sccp_redn_get_state(&param,&put_param,&ecode); 
            }
            break ;
#endif
/* spr # 9243 ends */            
            
        default:
			SC_A_TRC (("SCCP::REDN: invalid  command (%d)\n", cmd));
			ret_val = SS7_FAILURE;
			ecode = ESS7_INVALID_API_ELEMENT;
			break;
	}

	if (SS7_FAILURE == ret_val)
		SC_A_ERR (ecode);

		sccp_redn_sm_cmd_resp (p_api, ret_val, param, put_param, ecode);
}

/****************************************************************************
**    FUNCTION :
**              ss7_redn_build_api
**
****************************************************************************
**    DESCRIPTION:
**      This function can be used by SM to convert the raw SCCP redn data 
**    into a packed API buffer in case of unsolicited updates.
**
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t
sccp_redn_build_api
#ifdef ANSI_PROTO
    (U8bit      type_of_data,
     pvoid      p_redn_data,
     s7_len_t   redn_data_len,
     pvoid      *p_redn_api,
     error_t*   p_ecode)
#else
    (type_of_data, p_redn_data, redn_data_len, p_redn_api, p_ecode)
    U8bit      type_of_data;
    pvoid      p_redn_data;
    s7_len_t   redn_data_len;
    pvoid      *p_redn_api;
    error_t*   p_ecode;
#endif
{
	U8bit  trans_id;
	pvoid  p_redn_info;
	Boolean more_data_flag;
	U8bit  buffer_seq_num;
#if 0
/* This is removed for DEINIt/INIT + Redn to work --Sachin Bhatia */
	extern U8bit sccp_state;
    if ((sccp_state == UNINITIALIZED)||(sccp_state == BLOCKED) )
    {
        SC_A_TRC (("SCCP::INIT:SM Command Received in UN-INIIALIZED State\n"));
		*p_ecode = ESS7_INVALID_STATE;
        return SS7_FAILURE;
    }
#endif

	

	trans_id = 0; /* Unsolicited Update */
	p_redn_info = SS7_NULL;
	more_data_flag = SS7_FALSE;
	buffer_seq_num = 1;
	*p_redn_api = sccp_build_redn_data_buf(
					trans_id, type_of_data,(sccp_redn_options_t*) p_redn_info,
					redn_data_len,(U8bit*) p_redn_data, 
					more_data_flag, buffer_seq_num,
					p_ecode);
/* start added during CC compilation */
/* assign pvoid to sccp_redn_options_t* and U8bit* for p_redn_info and p_redn_data */
/* end added during CC compilation */ 

	if (*p_redn_api == SS7_NULL)
		return SS7_FAILURE;

	return SS7_SUCCESS;
}

#else 

/*****************************************************************************
**      FUNCTION :
**           handles SM command category REDN if REDN is compile time disabled
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_redn_handle_sm_cmd
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
	U8bit param = 0; Boolean put_param = SS7_FALSE;

	sccp_redn_sm_cmd_resp (p_api, SS7_FAILURE, param, put_param,
	                       ESCCP_REDN_DISABLED);

}

#endif

/*****************************************************************************
**      FUNCTION :
**            sends response to SM REDN category command
******************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
*****************************************************************************/

void
sccp_redn_sm_cmd_resp
#ifdef ANSI_PROTO
	(U8bit 		* p_api,
	 return_t 	ret_val,
	 U8bit 		param,
         Boolean 	put_param,
	 error_t 	ecode)
#else
	(p_api, ret_val, param, put_param, ecode)
	 U8bit 		* p_api;
	 return_t 	ret_val;
	 U8bit 		param;
         Boolean 	put_param;
	 error_t 	ecode;

#endif
{
	sccp_sm_cmd_std_resp (p_api, ret_val, param, put_param, ecode);
}


