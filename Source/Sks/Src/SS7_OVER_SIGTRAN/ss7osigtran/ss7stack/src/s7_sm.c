/*******************************************************************************
**      FUNCTION:
**              It file contains the system management API functions for all stack entities
********************************************************************************
**
** MODULE NAME:
*/


/*******************************************************************************
**      FILE NAME:
**              s7_sm.c
**
**      DESCRIPTION:
**              It file contains the system management API functions for all stack entities
**
**      GLOBAL FUNCTIONS:
**
**
**
**	LOCAL FUNCTIONS:
**
**
*/


/*
**      DATE       NAME         REFERENCE       REASON
**	-----------------------------------------------------
**
**	03Apr98	   Praneet Khare  ANSI_PROTO	Fitting ANSI_PROTOs and
**						removing redn. for MTP2
**      18Feb98    Sunil Mahajan  ISUP-API        Added Redundancy APIs
**      30Jan98    Sunil Mahajan  ISUP-API        .Original Creation
**
**
**
**  Copyright (C) 1997, Hughes Software Systems
********************************************************************************
**
**
**      INCLUDE FILES:
*/

#include"s7_typ.h"
#include"s7_def.h"
#include"s7_error.h"
#include"s7_prot.h"
#include"s7_stpro.h"

#ifndef SCCP
#define SCCP
#endif


#ifdef MTP2
	/* include mtp2 related prototyes */
#include "m2_stack.h"
#endif

#ifdef MTP3
	/* include mtp3 related prototyes */
#include "m3_sfnpr.h"
#include "m3_fnpr.h"
#endif

#ifdef ISUP
	/* include ISUP related prototyes */
#include "is_stpt.h"
#include "is_shpt.h"
#endif

#if defined (TCAP) || defined (SCCP)
	/* include TCAP and SCCP related prototypes */
#include "s7_stpro.h"
#endif
#if 0
extern return_t mtp3_init_stats
#ifdef ANSI_PROTO
       (stat_type_t stats_type,
        error_t *p_ecode);
#else
       (stats_type,p_ecode);
       stat_type_t stats_type;
        error_t *p_ecode;
#endif

extern return_t mtp3_get_stats
#ifdef ANSI_PROTO
       (pvoid p_stats,
       stat_type_t stats_type,
       Boolean reset_flag,
       error_t *p_ecode);
#else
       (p_stats,stats_type,reset_flag,p_ecode);
       pvoid p_stats;
       stat_type_t stats_type;
       Boolean reset_flag;
       error_t *p_ecode;
#endif

return_t mtp3_disable_stats
#ifdef ANSI_PROTO
       (stat_type_t stats_type,
        error_t *p_ecode);
#else
       (stats_type,p_ecode);
       stat_type_t stats_type;
        error_t *p_ecode;
#endif

return_t mtp3_enable_stats
#ifdef ANSI_PROTO
       (stat_type_t stats_type,
        error_t *p_ecode);
#else
       (stats_type,p_ecode);
       stat_type_t stats_type;
        error_t *p_ecode;
#endif

return_t mtp3_get_trace_level
#ifdef ANSI_PROTO
       (U32bit  trace_type,
        U8bit   *p_current_level,
        error_t *p_ecode);
#else
       (trace_type,p_current_level,p_ecode);
        U32bit  trace_type;
        U8bit   *p_current_level;
        error_t *p_ecode;
#endif
#endif
/****************************************************************************
**    FUNCTION :
**              ss7_init_stats
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function initializes the ss7 stack stats for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_init_stats
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 stat_type_t 	stats_type,
	 error_t* 	p_ecode)
#else
	(module_id, stats_type, p_ecode)
	module_id_t module_id ;
	stat_type_t stats_type ;
	error_t* p_ecode ;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_STATS_ENABLED
				return(mtp2_init_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_STATS_ENABLED
				return(mtp3_init_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_STATS_ENABLED
				return(isup_init_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
printf("Inside SCCP_MODULE_ID sctc_init_stats : \n");
		case SCCP_MODULE_ID:
#ifdef SCCP_STATS_ENABLED
				return(sctc_init_stats(module_id, stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_STATS_ENABLED
				return(sctc_init_stats(module_id, stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}


/****************************************************************************
**    FUNCTION :
**              ss7_get_stats
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function returns the ss7 stack stats for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_get_stats
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 pvoid 		p_stats_buf,
	 stat_type_t 	stats_type,
	 Boolean 	reset,
	 error_t* 	p_ecode)
#else
	(module_id, p_stats_buf, stats_type, reset, p_ecode)
	module_id_t    module_id ;
	pvoid          p_stats_buf ;
	stat_type_t    stats_type ;
	Boolean        reset ;
	error_t*       p_ecode ;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_STATS_ENABLED
				return(mtp2_get_stats(p_stats_buf,stats_type,reset,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_STATS_ENABLED
				return(mtp3_get_stats(p_stats_buf,stats_type,reset,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_STATS_ENABLED
				return(isup_get_stats(p_stats_buf,stats_type,reset,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_STATS_ENABLED
				return(sctc_get_stats(module_id,p_stats_buf,stats_type,reset,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_STATS_ENABLED
				return(sctc_get_stats(module_id,p_stats_buf,stats_type,reset,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}


/****************************************************************************
**    FUNCTION :
**              ss7_disable_stats
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function disable the ss7 stack stats for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_disable_stats
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 stat_type_t 	stats_type,
	 error_t* 	p_ecode)
#else
	(module_id, stats_type, p_ecode)
	module_id_t 	module_id;
	stat_type_t 	stats_type;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_STATS_ENABLED
				return(mtp2_disable_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_STATS_ENABLED
				return(mtp3_disable_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_STATS_ENABLED
				return(isup_disable_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_STATS_ENABLED
				return(sctc_disable_stats(module_id, stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_STATS_ENABLED
				return(sctc_disable_stats(module_id, stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}


/****************************************************************************
**    FUNCTION :
**              ss7_enable_stats
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function enables the ss7 stack stats for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_enable_stats
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 stat_type_t 	stats_type,
	 error_t* 	p_ecode)
#else
	(module_id, stats_type, p_ecode)
	module_id_t 	module_id;
	stat_type_t 	stats_type;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_STATS_ENABLED
				return(mtp2_enable_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_STATS_ENABLED
				return(mtp3_enable_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_STATS_ENABLED
				return(isup_enable_stats(stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_STATS_ENABLED
				return(sctc_enable_stats(module_id,stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_STATS_ENABLED
				return(sctc_enable_stats(module_id,stats_type,p_ecode));
#else
				*p_ecode = ESS7_STATS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}


/****************************************************************************
**    FUNCTION :
**              ss7_get_trace_level
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function returns the ss7 stack trace level for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_get_trace_level
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
 	 U32bit 	trace_flag,
	 U8bit* 	p_current_level,
	 error_t* 	p_ecode)
#else
	(module_id, trace_flag, p_current_level, p_ecode)
	module_id_t 	module_id;
 	U32bit 		trace_flag;
	U8bit* 		p_current_level;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_TRACE_ENABLED
				return(mtp2_get_trace_level(trace_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_TRACE_ENABLED
				return(mtp3_get_trace_level(trace_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_TRACE_ENABLED
				return(isup_get_trace_level(trace_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_TRACE_ENABLED
				return(sctc_get_trace_level(module_id, trace_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_TRACE_ENABLED
				return(sctc_get_trace_level(module_id, trace_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}


/****************************************************************************
**    FUNCTION :
**              ss7_set_trace_level
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function sets the ss7 stack trace level for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_set_trace_level
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U32bit 	trace_flag,
	 U8bit 		current_level,
	 error_t* 	p_ecode)
#else
	(module_id,trace_flag,current_level,p_ecode)
	module_id_t 	module_id;
	U32bit 		trace_flag;
	U8bit 		current_level;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_TRACE_ENABLED
				return(mtp2_set_trace_level(trace_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_TRACE_ENABLED
				return(mtp3_set_trace_level(trace_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_TRACE_ENABLED
				return(isup_set_trace_level(trace_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_TRACE_ENABLED
				return(sctc_set_trace_level(module_id, trace_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_TRACE_ENABLED
				return(sctc_set_trace_level(module_id, trace_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_TRACES_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}


/****************************************************************************
**    FUNCTION :
**              ss7_get_err_level
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function returns the ss7 stack error level for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_get_err_level
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U32bit 	error_flag,
	 U8bit* 	p_current_level,
	 error_t* 	p_ecode)
#else
	(module_id, error_flag, p_current_level, p_ecode)
	module_id_t 	module_id;
	U32bit 		error_flag;
	U8bit* 		p_current_level;
	error_t* 	p_ecode;
#endif
{
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_ERROR_ENABLED
				return(mtp2_get_error_level(error_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_ERROR_ENABLED
				return(mtp3_get_error_level(error_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_ERROR_ENABLED
				return(isup_get_error_level(error_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_ERROR_ENABLED
				return(sctc_get_error_level(module_id, error_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_ERROR_ENABLED
				return(sctc_get_error_level(module_id, error_flag,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}


/****************************************************************************
**    FUNCTION :
**              ss7_set_err_level
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function sets the ss7 stack trace level for the module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_set_err_level
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U32bit 	error_flag,
	 U8bit 		current_level,
	 error_t* 	p_ecode)
#else
	(module_id, error_flag, current_level, p_ecode)
	module_id_t 	module_id;
	U32bit 		error_flag;
	U8bit 		current_level;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_ERROR_ENABLED
				return(mtp2_set_error_level(error_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_ERROR_ENABLED
				return(mtp3_set_error_level(error_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_ERROR_ENABLED
				return(isup_set_error_level(error_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_ERROR_ENABLED
				return(sctc_set_error_level(module_id, error_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_ERROR_ENABLED
				return(sctc_set_error_level(module_id, error_flag,current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}

/****************************************************************************
**    FUNCTION :
**              ss7_get_event_reporting
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function returns the ss7 stack event reporting flag for the object id ,  
**              module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_get_event_reporting
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U16bit 	object_id,
	 U8bit* 	p_current_level,
	 error_t* 	p_ecode)
#else
	(module_id, object_id, p_current_level, p_ecode)
	module_id_t 	module_id;
	U16bit 		object_id;
	U8bit* 		p_current_level;
	error_t* 	p_ecode;
#endif
{
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_EVENT_REPORTING 
				return(mtp3_get_alarm_level(object_id,p_current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}

}

/****************************************************************************
**    FUNCTION :
**              ss7_set_event_reporting
**
**		
****************************************************************************
**    DESCRIPTION:
**		This function sets the ss7  level of object id ,  module id passed.
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_set_event_reporting
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U16bit 	object_id,
	 U8bit 		current_level,
	 error_t* 	p_ecode)
#else
	(module_id, object_id, current_level, p_ecode)
	module_id_t 	module_id;
	U16bit 		object_id;
	U8bit 		current_level;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP2
		case MTP2_MODULE_ID:
#ifdef MTP2_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_EVENT_REPORTING
				return(mtp3_set_alarm_level(object_id ,current_level,p_ecode));
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_ERROR_ENABLED
#else
				*p_ecode = ESS7_ERRORS_DISABLED;
				return(SS7_FAILURE);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}
#if defined(MTP3)||defined(ISUP)||defined(SCCP)||defined(TCAP)

/****************************************************************************
**    FUNCTION :
**              ss7_activate_module
**
**		
**		This function initializes the redundancy state for the module
****************************************************************************
**    DESCRIPTION:
**		This function initializes the redundancy state for the module
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_activate_module
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 error_t* 	p_ecode)
#else
	(module_id, p_ecode)
	module_id_t 	module_id;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP3
		case MTP3_MODULE_ID:
				return(mtp3_activate_mtp3(p_ecode));
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
				return(isup_activate_isup(p_ecode));
#endif
/* Inserted Mon Sep 11 19:26:39 IST 2000 Alok Singhal */
#if defined SCCP && defined SCCP_REDN_ENABLED
		case SCCP_MODULE_ID:
				return(sccp_activate_sccp(p_ecode));
#endif
/* Inserted Mon Sep 11 19:26:39 IST 2000 Alok Singhal */
#if defined TCAP && defined TCAP_REDN_ENABLED
		case TCAP_MODULE_ID:
				return(tcap_activate_tcap(p_ecode));
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}


/****************************************************************************
**    FUNCTION :
**              ss7_init_redn_data
**
**		
**		This function initializes the redundancy related trigger based
**		reporting for each module
****************************************************************************
**    DESCRIPTION:
**		This function initializes the redundancy related trigger based
**		reporting for each module
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_init_redn_data
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 Boolean 	event_reporting,
	 error_t* 	p_ecode)
#else
	(module_id, event_reporting, p_ecode)
	module_id_t 	module_id;
	Boolean 	event_reporting;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_REDN_ENABLED
				return(mtp3_init_redn_data(event_reporting,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_REDN_ENABLED
				return(isup_init_redn_data(event_reporting,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_REDN_ENABLED
				return(sccp_init_redn_data(event_reporting,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_REDN_ENABLED
				return(tcap_init_redn_data(event_reporting,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif
		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}

/****************************************************************************
**    FUNCTION :
**              ss7_redn_build_api
**
****************************************************************************
**    DESCRIPTION:
**      This function can be used by SM to convert the raw redn data into a 
**    packed API buffer. 
**
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/
return_t
ss7_redn_build_api
#ifdef ANSI_PROTO
    (module_id_t    module_id,
     U8bit      type_of_data,
     pvoid      p_redn_data,
     s7_len_t      redn_data_len,
     pvoid      *p_redn_api,
     error_t*   p_ecode)
#else
    (module_id, type_of_data, p_redn_data, redn_data_len, p_redn_api, p_ecode)
    module_id_t     module_id;
    U8bit      type_of_data;
    pvoid      p_redn_data;
    s7_len_t      redn_data_len;
    pvoid      *p_redn_api;
    error_t*   p_ecode;
#endif
{
    switch (module_id)
    {
#ifdef MTP3
    case MTP3_MODULE_ID:
#ifdef MTP3_REDN_ENABLED
        return mtp3_redn_build_api (type_of_data, p_redn_data, redn_data_len, 
                                    p_redn_api, p_ecode);
#endif
        break;
#endif

#ifdef SCCP
    case SCCP_MODULE_ID:
#ifdef SCCP_REDN_ENABLED
        return sccp_redn_build_api (type_of_data, p_redn_data, redn_data_len, 
                                    p_redn_api, p_ecode);
#endif
        break;
#endif

#ifdef ISUP
    case ISUP_MODULE_ID:
#ifdef ISUP_REDN_ENABLED
        return isup_redn_build_api (type_of_data, p_redn_data, redn_data_len, 
                                    p_redn_api, p_ecode);
#endif
		break;
#endif

#ifdef TCAP
    case TCAP_MODULE_ID:
#ifdef TCAP_REDN_ENABLED
        return tcap_redn_build_api (type_of_data, p_redn_data, redn_data_len, 
                                    p_redn_api, p_ecode);
#endif
        break;
#endif

    default:
        *p_ecode = ESS7_INVALID_MODULE_ID;
        ss7_mem_free(p_redn_data);
        return SS7_FAILURE;
    }

	return SS7_SUCCESS;
}


#if 0
/* This function has been moved to Encaps */

/****************************************************************************
**    FUNCTION :
**              ss7_send_update
**
**		
**		This function is to be ported by system menagement, it contains the data
**		to be reported to other side on a stable state
****************************************************************************
**    DESCRIPTION:
**		This function is to be ported by system menagement, it contains the data
**		to be reported to other side on a stable state
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_send_update
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U8bit 		type_of_data,
 	 s7_len_t 		msg_len,
	 pvoid 		p_redn_data,
         error_t* 	p_ecode)
#else
	(module_id, type_of_data, msg_len, p_redn_data, p_ecode)
	module_id_t 	module_id;
	U8bit 		type_of_data;
 	s7_len_t 		msg_len;
	pvoid 		p_redn_data;
        error_t* 	p_ecode;
#endif
{
	
	/* this function is to be ported */

	ss7_mem_free(p_redn_data);
	return(SS7_SUCCESS);
}

#endif

/****************************************************************************
**    FUNCTION :
**              ss7_request_active
**
**		
**		This function is used by system management to get the redundancy 
**		data from active module
****************************************************************************
**    DESCRIPTION:
**		This function initializes the redundancy related trigger based
**		reporting for each module
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_request_active
#ifdef ANSI_PROTO
	(module_id_t 	module_id,
	 U8bit 		type_of_data, 
	 pvoid 		p_redn_options,
	 s7_len_t 		*p_msg_len,
	 pvoid 		p_redn_msg,
	 pvoid 		*p_p_segment_info,
	 error_t* 	p_ecode)
#else
	(module_id, type_of_data, p_redn_options, p_msg_len, p_redn_msg, 
	 p_p_segment_info, p_ecode)
	module_id_t 	module_id;
	U8bit 		type_of_data;
	pvoid 		p_redn_options;
	s7_len_t 		*p_msg_len;
	pvoid 		p_redn_msg;
	pvoid 		*p_p_segment_info;
	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_REDN_ENABLED
				return(mtp3_request_active(type_of_data,p_redn_options,
							   p_msg_len,p_redn_msg,p_p_segment_info,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_REDN_ENABLED
				return(isup_request_active(type_of_data,p_redn_options,
							   p_msg_len,p_redn_msg,p_p_segment_info,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_REDN_ENABLED
				return(sccp_request_active(type_of_data,p_redn_options,
							   p_msg_len,p_redn_msg,p_p_segment_info,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_REDN_ENABLED
				return(tcap_request_active(type_of_data,p_redn_options,
							   p_msg_len,p_redn_msg,p_p_segment_info,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}

/****************************************************************************
**    FUNCTION :
**              ss7_receive_update
**
**		
**		This function is used by system management to update the redundancy 
**		data from active module to standby side
****************************************************************************
**    DESCRIPTION:
**		This function is used by system management to update the redundancy 
**		data from active module to standby side
**    RETURN VALUE:
**              SS7_SUCCESS
**              SS7_FAILURE
****************************************************************************/

return_t 
ss7_receive_update
#ifdef  ANSI_PROTO
	(module_id_t 	module_id,
	 U8bit 		type_of_data, 
	 s7_len_t 		msg_len,
	 pvoid 		p_redn_msg,
 	 error_t* 	p_ecode)
#else
	(module_id, type_of_data, msg_len, p_redn_msg, p_ecode)
	module_id_t 	module_id;
	U8bit 		type_of_data;
	s7_len_t 		msg_len;
	pvoid 		p_redn_msg;
 	error_t* 	p_ecode;
#endif
{
	
	switch(module_id)
	{
#ifdef MTP3
		case MTP3_MODULE_ID:
#ifdef MTP3_REDN_ENABLED
				return(mtp3_receive_update(type_of_data,
							   msg_len,p_redn_msg,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif
#ifdef ISUP
		case ISUP_MODULE_ID:
#ifdef ISUP_REDN_ENABLED
				return(isup_receive_update(type_of_data,
							   msg_len,p_redn_msg,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

#ifdef SCCP
		case SCCP_MODULE_ID:
#ifdef SCCP_REDN_ENABLED
				return(sccp_receive_update(type_of_data,
							   msg_len,p_redn_msg,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

#ifdef TCAP
		case TCAP_MODULE_ID:
#ifdef TCAP_REDN_ENABLED
				return(tcap_receive_update(type_of_data,
							   msg_len,p_redn_msg,p_ecode));
#else
				return(SS7_SUCCESS);
#endif
#endif

		default:
				*p_ecode = ESS7_INVALID_MODULE_ID;
				return(SS7_FAILURE);
	}
}
#endif /* redundancy functions */

/*****************************************************************************
***************** END OF FILE *************************************************
****************************************************************************/
