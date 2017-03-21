/******************************************************************************
**      FUNCTION:
**          Functions for control of error reporting by TCAP & SCCP -
**	    common code.
**
*******************************************************************************
**
**      FILE NAME:
**          s7_sterr.c
**      
**      DESCRIPTION:
**          The Error Module provides a functional interface for:
**          (1)Run time control of amount and type of error reporting through
**             use of error levels and error flags. 
**          (2)Reporting of errors through the use of a common error handler
**             function.This function will be ported.            
**
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**           
**	08Apr98	   Praneet Khare			  Hiding file for
**							MTP2, MTP3, ISUP
**								&
**							changing func. names
**      16Jan98    GAURAV.TANEJA     HSS:????????         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems Ltd.
**
******************************************************************************/


#include "s7_typ.h"

#include "s7_def.h"
#include "s7_error.h"
#include "s7_sterr.h"
#include "s7_stpro.h"

#if defined(SCCP_ERROR_ENABLED) || defined(TCAP_ERROR_ENABLED)

#ifdef TCAP
extern U32bit tcap_error_table[];
#endif
#ifdef SCCP
extern U32bit sccp_error_table[];
#endif
 
 
/* pointer to trace table */
static U32bit *p_error_table;

/* Table to convert global error flags into SCCP/TCAP error flag. To be used 
   until all stack entities are merged later */
U32bit err_map [] = {  SCTC_PROTOCOL_ERROR,
		       SCTC_SYSTEM_ERROR,
		       SCTC_INVALID_ERROR,
		       SCTC_API_ERROR,
			   SCTC_INVALID_ERROR,/* SPR FIX 10637*/
		       SCTC_ALL_ERROR};

/******************************************************************************
**  GLOBAL FUNCTION:
**     Gets the error level associated with the specied error flag.
**  DESCRIPTION:
**     This function reads the current error level of the specified error 
**     flag and copies it into p_current_level. It also checks the input 
**     parameters i.e. value of module_id and error_flag. 
**
******************************************************************************/

return_t
sctc_get_error_level(module_id_t  module_id,
                  U32bit       error_flag,
                  U8bit        *p_current_level,
                  error_t      *p_ecode)
{

/* error level indication */
  U8bit err_lev; 
  
  /* Convert into TCAP/SCCP #defines */
   if ((error_flag < STACK_PROTOCOL_ERROR) || (error_flag > ALL_ERROR)) {
    /* invalid error flag received */
    *p_ecode=ESS7_INVALID_ERROR_FLAG;
    return SS7_FAILURE;
  }
  error_flag = err_map [(U8bit)error_flag-1];

/* check for validity of error flag */
  if(SS7_INVALID_ERR_FLAG(error_flag)) {
    *p_ecode=ESS7_INVALID_ERROR_FLAG;
    return SS7_FAILURE;
  }  


  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :
     p_error_table = tcap_error_table;
     break;
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :
     p_error_table = sccp_error_table;
     break;
#endif
  default :
     *p_ecode=ESS7_INVALID_MODULE_ID;
     return SS7_FAILURE;
  }

/* set current error level to NO_ERROR */
    *p_current_level=(U8bit)NO_ERROR;  

/* check for CRITICAL, MAJOR, or MINOR ERRORS */
  for(err_lev=MINOR_ERROR;err_lev>=CRITICAL_ERROR;--err_lev)
    if(p_error_table [err_lev] & error_flag) {
       *p_current_level=err_lev;
       break; 
    }
  
  return SS7_SUCCESS;
}


/******************************************************************************
**  GLOBAL FUNCTION:
**     Sets the current level of the specied error flag to the desired level.
**  DESCRIPTION:
**     This function sets the current error level of the specified error 
**     flag to the desired level. It also checks the input parameters i.e. 
**     value of module_id,error_flag and desired level.     
**
******************************************************************************/

return_t 
sctc_set_error_level(module_id_t  module_id,
                  U32bit       error_flag,
                  U8bit        desired_level,
                  error_t      *p_ecode)
{
/* error level indication */
  U8bit err_lev; 

  /* Convert into TCAP/SCCP #defines */
   if ((error_flag < STACK_PROTOCOL_ERROR) || (error_flag > ALL_ERROR)) {
    /* invalid error flag received */
    *p_ecode=ESS7_INVALID_ERROR_FLAG;
    return SS7_FAILURE;
  }
  error_flag = err_map [(U8bit)error_flag-1];

/* check for validity of error_flag */
  if(SS7_INVALID_ERR_FLAG(error_flag)) {
    *p_ecode=ESS7_INVALID_ERROR_FLAG;
    return SS7_FAILURE;
  }

/* check validity of desired level */
  if(SS7_INVALID_ERR_LEV(desired_level)) {
    *p_ecode=ESS7_INVALID_ERROR_LEVEL;
    return SS7_FAILURE;
  }

  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :
     p_error_table = tcap_error_table;
     break;
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :
     p_error_table = sccp_error_table;
     break;
#endif
  default :
     *p_ecode=ESS7_INVALID_MODULE_ID;
     return SS7_FAILURE;
  }

/* disable existing error level */
  for(err_lev=MINOR_ERROR;err_lev > desired_level;--err_lev)
     p_error_table [err_lev] &= ~error_flag;
  
/* set current error level to the desired level */
  for(err_lev=desired_level; err_lev >= CRITICAL_ERROR;--err_lev)
     p_error_table [err_lev] |= error_flag;

  return SS7_SUCCESS;
}

#endif
