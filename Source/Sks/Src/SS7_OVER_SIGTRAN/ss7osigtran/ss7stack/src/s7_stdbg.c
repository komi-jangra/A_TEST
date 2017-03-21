/******************************************************************************
**      FUNCTION:
**          Functions for control of debugging information provided by the 
**          SCCP & TCAP - common code.
*******************************************************************************
**
**      FILE NAME:
**          s7_stdbg.c
**      
**      DESCRIPTION:
**          The Debug Module provides a functional interface for:
**          (1)Run time control of amount and type of debugging information 
**             through the use of debug trace levels and trace flags. 
**          (2)Logging/Recording of debugging information through macros.
**             These will be ported.          
**
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**           
**      06Dec99    Rahul Gupta       -----------        Fixing SPR#2215
**                                                        making it compatible 
**	   					          to both sccp & tcap 
**                                                        simultaneously
**
**      19Jan98    GAURAV.TANEJA     HSS:????????         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems Ltd.
**
******************************************************************************/

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_stdbg.h"
#include "s7_error.h"
#include "s7_stpro.h"

#if (defined TCAP_TRACE_ENABLED) || (defined SCCP_TRACE_ENABLED)


/* Table to convert global trace flags into SCCP/TCAP trace flag. To be used 
   until all stack entities are merged later */
U32bit trace_map [] =      { SCTC_INCOMING_TRACE,
			     SCTC_OUTGOING_TRACE,
			     SCTC_API_TRACE,
			     SCTC_INVALID_TRACE,
			     SCTC_SYS_ERR_TRACE,
			     SCTC_INVALID_TRACE,
			     SCTC_INIT_TRACE,
			     SCTC_PROTO_EXCEPTION_TRACE};
/*SPR#2215 Start */

/******************************************************************************
**  GLOBAL FUNCTION:
**     Gets the trace level associated with the specified trace flag.
**  DESCRIPTION:
**     This function reads the current trace level of the specified trace 
**     flag and copies it into p_current_level. It also checks the input 
**     parameters i.e. value of module_id and trace_flag. 
**
******************************************************************************/

return_t
sctc_get_trace_level(module_id_t  module_id,
                    U32bit       trace_flag,
                    U8bit        *p_current_level,
                    error_t      *p_ecode)
{

/* trace level indication */
  U8bit tr_lev; 

/* pointer to trace table:for SCCP or TCAP */
 U32bit *p_trace_table;

  /* Convert into TCAP/SCCP #defines */
  if ((trace_flag >= INCOMING_TRACE) && (trace_flag <= PROTO_EXCEPTION_TRACE))
    {
      trace_flag = trace_map [(U8bit)trace_flag-1];
    }
  
  /* check validity of module_id */
  
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :
    p_trace_table = tcap_trace_table;
    if(trace_flag==ALL_TRACE)
      trace_flag = TC_ALL_TRACE;
    /* check for validity of trace flag */
    if(TC_INVALID_TRACE_FLAG(trace_flag)) {
      *p_ecode=ESS7_INVALID_TRACE_FLAG;
       return SS7_FAILURE;
    }  
    
    break;
#endif

#ifdef SCCP
  case SCCP_MODULE_ID :

    p_trace_table = sccp_trace_table;
    if(trace_flag==ALL_TRACE)
      trace_flag = SC_ALL_TRACE;
    /* check for validity of trace flag */
    if(SC_INVALID_TRACE_FLAG(trace_flag)) {
      *p_ecode=ESS7_INVALID_TRACE_FLAG;
      return SS7_FAILURE;
    }  
    
    break;
#endif
  default :
    *p_ecode=ESS7_INVALID_MODULE_ID;
    return SS7_FAILURE;
  }
  
  /* set current trace level to NO_TRACE */
  *p_current_level=(U8bit)NO_TRACE;
  
  /* check for BRIEF, MEDIUM or DETAILED trace */
  for(tr_lev=DETAILED_TRACE;tr_lev>=BRIEF_TRACE;--tr_lev)
    if(p_trace_table[tr_lev] & trace_flag) {
      *p_current_level=tr_lev;
      break;
    }


  return SS7_SUCCESS;
}

/******************************************************************************
**  GLOBAL FUNCTION:
**     Sets the current level of the specied trace flag to the desired level.
**  DESCRIPTION:
**     This function sets the current trace level of the specified trace 
**     flag to the desired level. It also checks the input parameters i.e. 
**     value of module_id,trace_flag and desired level.     
**
******************************************************************************/

return_t
sctc_set_trace_level(module_id_t  module_id,
                    U32bit       trace_flag,
                    U8bit        desired_level,
                    error_t      *p_ecode)
{

  /* trace level indication */ 
  U8bit tr_lev;
  
/* pointer to trace table:for SCCP or TCAP */
 U32bit *p_trace_table;

  /* Convert into TCAP/SCCP #defines */
  if ((trace_flag >= INCOMING_TRACE) && (trace_flag <= PROTO_EXCEPTION_TRACE))
    {
      trace_flag = trace_map [(U8bit)trace_flag-1];
    }
 

  
  /* check validity of desired level */
  if(SS7_INVALID_TRACE_LEV(desired_level)) {
    *p_ecode=ESS7_INVALID_TRACE_LEVEL;
    return SS7_FAILURE;
  }
  
  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :
    p_trace_table = tcap_trace_table;
    if(trace_flag==ALL_TRACE)
      trace_flag = TC_ALL_TRACE;
    /* check for validity of trace flag */
    if(TC_INVALID_TRACE_FLAG(trace_flag)) {
      *p_ecode=ESS7_INVALID_TRACE_FLAG;
      return SS7_FAILURE;
    }  
    
    break;
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :
     p_trace_table = sccp_trace_table;
     if(trace_flag==ALL_TRACE)
       trace_flag = SC_ALL_TRACE;
     /* check for validity of trace flag */
     if(SC_INVALID_TRACE_FLAG(trace_flag)) {
       *p_ecode=ESS7_INVALID_TRACE_FLAG;
       return SS7_FAILURE;
     }  
     
     break;
#endif
  default :
    *p_ecode=ESS7_INVALID_MODULE_ID;
    return SS7_FAILURE;
  }
  
  /* disable all existing trace levels */
  for(tr_lev=DETAILED_TRACE;tr_lev>=BRIEF_TRACE;--tr_lev)
    p_trace_table [tr_lev] &= ~trace_flag;
  
  /* set current trace level to the desired level */
  for (;desired_level>=BRIEF_TRACE; desired_level--)
    p_trace_table [desired_level] |=trace_flag;
  
  return SS7_SUCCESS;
} 

/*SPR#2215 End */

#endif  /* #if (defined TCAP_TRACE_ENABLED) || (defined SCCP_TRACE_ENABLED) */






