/***************************************************************************
**  FILE NAME:
**      dsccp_stat.h
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION: This file contains the datastructures related to stats for 
** 				 DSCCP. 
**
**
**  DATE     NAME              REF#     REASON
**  -------  ----------------  -----    -------------------------------------
**  24oct'2001 Prateek Bidwalkar ----    Original
**
**  Copyright 2001, Hughes Software Systems
***************************************************************************/



#ifndef __DSCCP_STAT_H__
#define __DSCCP_STAT_H__

/* Data strucure for Mate API */
typedef struct {
		count_t in_api_mate;		/* incoming API's from mates */
		count_t out_api_mate; 		/* outgoing API's to mates */
		count_t err_in_api_mate;	/* error in incoming API's from mates */
		count_t err_out_api_mate;	/* error in outgoing API's to mates */
} dsccp_stats_api_t;


/* Data structure for SCLC event */
typedef struct {
			ss7_event_t  sccp_xudt_bcast; /* non-1st data seg received */
} dsccp_stats_sclc_t;


/* Data structure for SCOC event */
typedef struct {
			ss7_event_t	  sccp_n_disconn_req; /* N_DISCONN req received for an
											  ** unestablished connection
											  */
} dsccp_stats_scoc_t;


#ifdef DSCCP_STATS_ENABLED
extern dsccp_stats_api_t    dsccp_stats_api;

extern dsccp_stats_sclc_t       dsccp_stats_sclc;

extern dsccp_stats_scoc_t       dsccp_stats_scoc;


/* Macros for Incrementing API Stats */
#define DSC_STAT_API_INR_IN_API_MATE()	\
								if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
										  ++dsccp_stats_api.in_api_mate
#define DSC_STAT_API_INR_OUT_API_MATE()  \
								if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
										  ++dsccp_stats_api.out_api_mate
#define DSC_STAT_API_INR_ERR_IN_API_MATE() \
								if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
										  ++dsccp_stats_api.err_in_api_mate
#define DSC_STAT_API_INR_ERR_OUT_API_MATE() \
								if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
										  ++dsccp_stats_api.err_out_api_mate

/* Macros for Handling SCLC events */
#define DSC_STAT_TS_XUDT_BCAST() if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
			ss7_get_absolute_time(&dsccp_stats_sclc.sccp_xudt_bcast.time)
#define DSC_STAT_INR_XUDT_BCAST() if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
			++dsccp_stats_sclc.sccp_xudt_bcast.count


/* Macros for Handling SCOC events */
#define DSC_STAT_TS_DISCONN_REQ() if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
			ss7_get_absolute_time(&dsccp_stats_scoc.sccp_n_disconn_req.time)
#define DSC_STAT_INR_DISCONN_REQ() if(sccp_stats_flag & STATS_PROTO_INTERNAL) \
			++dsccp_stats_scoc.sccp_n_disconn_req.count


#else /* DSCCP_STATS_ENABLED */

#define DSC_STAT_API_INR_IN_API_MATE()	
#define DSC_STAT_API_INR_OUT_API_MATE()
#define DSC_STAT_API_INR_ERR_IN_API_MATE()
#define DSC_STAT_API_INR_ERR_OUT_API_MATE()
#define DSC_STAT_TS_XUDT_BCAST()
#define DSC_STAT_INR_XUDT_BCAST()
#define DSC_STAT_TS_DISCONN_REQ()
#define DSC_STAT_INR_DISCONN_REQ()

#endif /* DSCCP_STATS_ENABLED */

#endif /* __DSCCP_STAT_H__ */
