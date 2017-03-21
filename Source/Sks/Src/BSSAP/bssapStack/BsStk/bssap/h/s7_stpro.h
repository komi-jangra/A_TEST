/*******************************************************************************
**      FILE NAME:
**          s7_stpro.h
**
**      DESCRIPTION:
**              This files contains the prototypes of the functions common
**  						to BSSAP & BS-USER.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/


/***************************************************************************
**
**  FUNCTION:
**      common file for SCCP & TCAP for prototypes
**
****************************************************************************
**
**  FILE NAME:
**      s7_stpro.h
**
**  DESCRIPTION:
**	This files contains the prototypes of the functions common
**	to SCCP and TCAP entity
**
**      DATE     NAME              REF#    REASON
**-------------------------------------------------------------------------
**	08Apr'98 Praneet Khare		  Original
**
**  Copyright 1998, Hughes Software Systems Ltd.
**
***************************************************************************/

#if defined (TCAP) || defined (SCCP) 
/* Should be included only for SCCP and TCAP */

#ifndef _S7_STPRO_H_     /* If this file has not been processed, */
#define _S7_STPRO_H_     /* define it as seen--ref '#endif' below. */

#if defined (SCCP_STATS_ENABLED) || defined (TCAP_STATS_ENABLED)

return_t	
sctc_init_stats
#ifdef ANSI_PROTO
	(module_id_t   module_id,
         stat_type_t  stats_type,
         error_t       *p_ecode) ;
#else
	( ) ;
#endif

return_t
sctc_get_stats
#ifdef ANSI_PROTO
	(module_id_t   module_id,
         pvoid         p_stats,
         stat_type_t  stats_type,
         Boolean       reset_flag,
         error_t       *p_ecode) ;
#else
	( ) ;
#endif

return_t
sctc_enable_stats
#ifdef ANSI_PROTO
	(module_id_t  module_id,
         stat_type_t  stats_type,
         error_t      *p_ecode) ;
#else
	( ) ;
#endif


return_t
sctc_disable_stats
#ifdef ANSI_PROTO
	(module_id_t  module_id,
         stat_type_t stats_type,
         error_t      *p_ecode) ;
#else
	( ) ;
#endif

#endif /* defined (SCCP_STATS_ENABLED) || defined (TCAP_STATS_ENABLED) */

#if defined (TCAP_TRACE_ENABLED) || defined (SCCP_TRACE_ENABLED)

return_t
sctc_get_trace_level
#ifdef ANSI_PROTO
	(module_id_t  module_id,
         U32bit       trace_flag,
         U8bit        *p_current_level,
         error_t      *p_ecode) ;
#else
	( ) ;
#endif

return_t
sctc_set_trace_level
#ifdef ANSI_PROTO
	(module_id_t  module_id,
         U32bit       trace_flag,
         U8bit        desired_level,
         error_t      *p_ecode) ;
#else
	( ) ;
#endif

#endif /* defined (TCAP_TRACE_ENABLED) || defined (SCCP_TRACE_ENABLED) */

#if defined (SCCP_ERROR_ENABLED) || defined (TCAP_ERROR_ENABLED)

return_t
sctc_get_error_level
#ifdef ANSI_PROTO
	(module_id_t  module_id,
         U32bit       error_flag,
         U8bit        *p_current_level,
         error_t      *p_ecode) ;
#else
	( ) ;
#endif

return_t
sctc_set_error_level
#ifdef ANSI_PROTO
	(module_id_t  module_id,
         U32bit       error_flag,
         U8bit        desired_level,
         error_t      *p_ecode) ;
#else
	( ) ;
#endif

#endif /* defined (SCCP_ERROR_ENABLED) || defined (TCAP_ERROR_ENABLED) */

#if defined (SCCP_REDN_ENABLED)
return_t sccp_init_redn_data
#ifdef ANSI_PROTO
        (Boolean        event_reporting,
         error_t*       p_ecode) ;
#else
	() ;
#endif

return_t sccp_request_active
#ifdef ANSI_PROTO
	(U8bit          type_of_data,
	 pvoid          p_redn_opt,
	 s7_len_t          *p_msg_len,
	 pvoid          p_redn_msg,
	 pvoid          *p_p_seg_info,
	 error_t*       p_ecode) ;
#else
	() ;
#endif

return_t sccp_receive_update
#ifdef ANSI_PROTO
        (U8bit          type_of_data,
         s7_len_t          msg_len,
         pvoid          p_redn_msg,
         error_t*       p_ecode) ;
#else
	() ;
#endif

#endif /* defined (SCCP_REDN_ENABLED) */
        
/* Prototypes added for compiling TCAP on CC compiler - Mudit */
/*
return_t tcap_activate_tcap
#ifdef ANSI_PROTO
        (error_t*       p_ecode);
#else
        ();
#endif
        
return_t tcap_init_redn_data
#ifdef ANSI_PROTO
        (Boolean        event_reporting,
         error_t*       p_ecode);
#else
        ();
#endif

return_t tcap_redn_build_api
#ifdef ANSI_PROTO
        (U8bit      type_of_data,
         pvoid      p_redn_data,
         s7_len_t   redn_data_len,
         pvoid      *p_redn_api,
         error_t*   p_ecode);
#else
        ();
#endif

return_t tcap_request_active
#ifdef ANSI_PROTO
	(U8bit          type_of_data,
	 pvoid          p_redn_opt,
	 s7_len_t          *p_msg_len,
	 pvoid          p_redn_msg,
	 pvoid          *p_p_seg_info,
	 error_t*       p_ecode) ;
#else
	() ;
#endif       
       
return_t tcap_receive_update
#ifdef ANSI_PROTO
        (U8bit          type_of_data,
         s7_len_t          msg_len,
         pvoid          p_redn_msg,
         error_t*       p_ecode) ;
#else
	() ;
#endif        

*/

#endif /* _S7_STST_H_       -- This MUST appear after all code! */

#endif /* defined (TCAP) || defined (SCCP) */
