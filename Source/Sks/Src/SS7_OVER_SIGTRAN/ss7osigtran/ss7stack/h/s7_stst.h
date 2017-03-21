/***************************************************************************
**  FUNCTION:
**      common file for SCCP & TCAP related statistics
**
****************************************************************************
**
**  FILE NAME:
**      s7_stst.h
**
**  DESCRIPTION:
**		This files defines the common definitions to be used by
**		the TCAP and SCCP stack entities.
**
**      DATE     NAME              REF#    REASON
**      -------  ----------------  -----   --------------------------------
**      01Mar98  Gaurav Taneja     -----   Original  
**      01Nov00  Arun Kumar	   SPR#4543   Adding TRAFFIC Statistics
**
**  Copyright 2000, Hughes Software Systems Ltd.
***************************************************************************/


#ifndef _S7_STST_H_     /* If this file has not been processed, */
#define _S7_STST_H_     /* define it as seen--ref '#endif' below. */

/* STATISTICS TYPE */
#define SCTC_STATS_API             0x1
#define SCTC_STATS_ERROR           0x2
#define SCTC_STATS_PROTO_Q752      0x4
#define SCTC_STATS_TRAFFIC         0x10 /* SPR# 4543 */
#define SCTC_STATS_PROTO_INTERNAL  0x8
#define SCTC_STATS_ALL             (SCTC_STATS_API|SCTC_STATS_ERROR|SCTC_STATS_PROTO_Q752|SCTC_STATS_TRAFFIC)
#define SCTC_STATS_INVALID         0x0 

/* macro for checking validity of statistics type */
#define SS7_INVALID_STATS_TYPE(stats_type) ((stats_type!=SCTC_STATS_API) &&  \
                                      (stats_type!=SCTC_STATS_ERROR)      &&  \
                                      (stats_type!=SCTC_STATS_PROTO_Q752) &&  \
				      (stats_type!=SCTC_STATS_TRAFFIC) && \
                                      (stats_type!=SCTC_STATS_ALL))  /* SPR# 4543 */

#endif /* _S7_STST_H_       -- This MUST appear after all code! */