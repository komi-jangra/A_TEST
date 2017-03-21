/***************************************************************************
**  FUNCTION:
**      common file for SCCP & TCAP related error definitions
**
****************************************************************************
**
**  FILE NAME:
**      s7_sterr.h
**
**  DESCRIPTION:
**		This files defines the common definitions to be used by
**		for error habdling by TCAP & SCCP.
**
**      DATE     NAME              REF#    REASON
**      -------  ----------------  -----   --------------------------------
**      15Jan98  gtaneja           -----   Original  
**
**  Copyright 1997, Hughes Software Systems Ltd.
***************************************************************************/

#ifndef _S7_STERR_H_     /* If this file has not been processed, */
#define _S7_STERR_H_     /* define it as seen--ref '#endif' below. */

/* MAXIMUM NUMBER OF ERROR LEVELS */
#define MAX_ERROR_LEVELS                4

/* ERROR FLAGS */
#define SCTC_PROTOCOL_ERROR        0x1  /* protocol releated errors */
#define SCTC_SYSTEM_ERROR          0x2  /* errors in system calls */
#define SCTC_API_ERROR             0x4  /* errors in API parsing and checking */
#define SCTC_ALL_ERROR	      (SCTC_PROTOCOL_ERROR|SCTC_SYSTEM_ERROR|SCTC_API_ERROR)

#define SCTC_INVALID_ERROR         0x0  /* invalid error flag */

/* macro for checking validity of error flag */
#define SS7_INVALID_ERR_FLAG(err_flag)  \
				 ((err_flag!=SCTC_PROTOCOL_ERROR)   &&  \
                                 (err_flag!=SCTC_SYSTEM_ERROR)     &&  \
                                 (err_flag!=SCTC_API_ERROR)        &&  \
                                 (err_flag!=SCTC_ALL_ERROR))

/* macro for checking validity of error level */
#define SS7_INVALID_ERR_LEV(des_lev)     ((des_lev!=NO_ERROR)          &&  \
                                 (des_lev!=CRITICAL_ERROR)    &&  \
                                 (des_lev!=MAJOR_ERROR)       &&  \
                                 (des_lev!=MINOR_ERROR))

#endif /* _S7_STERR_H_       -- This MUST appear after all code! */
