/******************************************************************************
** FUNCTION :
**	Global type definations.	
**
*******************************************************************************
**
** FILE NAME :
**             s7_sm.h
**
** DESCRIPTION : 
**              Contain global type definitions.
**
**      DATE               NAME            REFERENCE        REASON
**      ----               ----            ---------        ------
**      16/07/02		   Salil Kumar Agrawal 			Fixed SPR 9243 
**      18/06/02           Salil Kumar Agrawal          Added GET and SET state API
**      12/03/02		   Sachin Bhatia                Added Deinit API
**      18/12/01		   Ashish Sawalkar					Fixed SPR 7490 
**      22/10/01		   Prateek Bidwalkar                Fixed SPR 6566
**      13/10/00           V Nagpal                   SPR4463
**	17/05/00	   Dinesh Kori                      Added isup_prov_get_ckt_grp_info 
**	11/06/98	   Praneet Khare		    Adding SysMg stuff
**							for MTP2
**	27/05/98	   P. Srivastava	            System Management APIs added 
**      01/04/98           Anil K.        		    s7_typ.h included 
**      05/12/97           Anil K.         HSS:20800008     Initial
**      05/12/01           rimishra        SPR 6486         SPR Fixed
**	11Nov2002	Pranjal Mishra		SPR 10507
**	24Apr2003	knaveen        		SPR 11302
**
** Copyright 1997, Hughes Software System Ltd.
******************************************************************************/
#ifndef _S7_SM_H_
#define _S7_SM_H_

#include "s7_typ.h"


/* Sytem management commonad category  and commands */

#define SS7_SM_PROV		0x00  /* prov category */ 
#define SS7_SM_CTRL		0x01 /* Ctrl category */
#define SS7_SM_STATS		0x02  /* stats category */
#define SS7_SM_DEBUG		0x03  /* Debug category */
#define SS7_SM_ERROR		0x04 
#define SS7_SM_REDN		0x05 
#define SS7_SM_DISP		0x06 /* Display Status category */

#define SS7_SM_MAX_COMD_CAT	SS7_SM_DISP

/* This is local to ISUP module */
/* provisioning commands for ISUP module */
#define ISUP_PROV_CKT_GRP	0x00
#define ISUP_UNPROV_CKT_GRP	0x01
#define ISUP_INIT_TIMERS	0x02
#define ISUP_PROV_GRP_RANGE	0x03
#define ISUP_INIT_TIMERS_TENS_MS	0x04
#define ISUP_PROV_GET_CKT_GRP_INFO	0x05

/* This is local to BISUP Module */
#define BISUP_INIT_TIMERS       0x00

/* stats commands for all modules */
#define SS7_SM_INIT_STATS	0x00 
#define SS7_SM_GET_STATS	0x01
#define SS7_SM_DISABLE_STATS	0x02
#define SS7_SM_ENABLE_STATS	0x03



/* trace commands for all modules */
#define SS7_SM_GET_TRACE_LEVEL	0x00
#define SS7_SM_SET_TRACE_LEVEL	0x01



/* error commands for all modules */
#define SS7_SM_GET_ERR_LEVEL	0x00
#define SS7_SM_SET_ERR_LEVEL	0x01


/*hash define for the command in events  with category error */

#define SS7_SM_GET_EVENT_REPORTING 	0x02
#define SS7_SM_SET_EVENT_REPORTING 	0x03
#define SS7_SM_MTP2_STATUS  		0x04
#define SS7_SM_MTP3_STATUS 		0x05 
#define SS7_SM_SCCP_STATUS 		0x06
#define SS7_SM_TCAP_STATUS 		0x07 
#define SS7_SM_ISUP_STATUS 		0x08



/* redundancy commands for all modules */
#define SS7_SM_INIT_REDN_DATA	0x00
#define SS7_SM_REDN_REQ_ACT	0x01
#define SS7_SM_REDN_RECV_UPDATE	0x02
#define SS7_SM_ACTIVATE_MODULE	0x03

/* spr # 9243 starts */
#if 0
/* added by salil */
/* GET & SET state SM api in Redundency to set active or standby state */
#define SS7_SM_REDN_SET_STATE   0x04
#define SS7_SM_REDN_GET_STATE   0x05
/* end */
#endif
/* spr # 9243 ends */

/* maximum commands for any category */
/* should be changed by other modules if they add more than this to any category */
#define SS7_SM_MAX_COMD_PER_CAT		0x06	



/* Length of different SM APIs */

#define SS7_SM_API_MIN_LEN			8  

#define SS7_SM_INIT_STATS_LEN			(SS7_SM_API_MIN_LEN + 1)
#define SS7_SM_GET_STATS_LEN			(SS7_SM_API_MIN_LEN + 2)
#define SS7_SM_DISABLE_STATS_LEN		(SS7_SM_API_MIN_LEN + 1)
#define SS7_SM_ENABLE_STATS_LEN			(SS7_SM_API_MIN_LEN + 1)	
#define SS7_SM_GET_TRACE_LEVEL_LEN		(SS7_SM_API_MIN_LEN + 4)
#define SS7_SM_SET_TRACE_LEVEL_LEN		(SS7_SM_API_MIN_LEN + 5)
#define SS7_SM_GET_ERR_LEVEL_LEN		(SS7_SM_API_MIN_LEN + 4)
#define SS7_SM_SET_ERR_LEVEL_LEN		(SS7_SM_API_MIN_LEN + 5)

#define SS7_SM_GET_EVENT_REPORTING_LEN		(SS7_SM_API_MIN_LEN + 2)
#define SS7_SM_SET_EVENT_REPORTING_LEN		(SS7_SM_API_MIN_LEN + 3)
#define SS7_SM_DISPLAY_MODULE_VERSION_LEN        (SS7_SM_API_MIN_LEN)

/* SPR # 6566 : Fix start */
#define SS7_SM_DISPLAY_SS_STATUS_API_LEN        (SS7_SM_API_MIN_LEN + 3)

#define SS7_SM_DISPLAY_SS_OFFSET				8
/* SPR # 6566 : Fix end */

/* SPR  7490 : Start Fix */
#define SS7_SM_DISPLAY_SP_STATUS_API_LEN        (SS7_SM_API_MIN_LEN + 2)
#define SS7_SM_DISPLAY_SP_OFFSET                8
/* SPR  7490 : End Fix */


/*number of elements in different SM APIs */

#define SS7_SM_API_MIN_NO_ELEM			3  

#define SS7_SM_INIT_STATS_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define SS7_SM_GET_STATS_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 2)
#define SS7_SM_DISABLE_STATS_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define SS7_SM_ENABLE_STATS_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define SS7_SM_GET_TRACE_LEVEL_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define SS7_SM_SET_TRACE_LEVEL_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 2)
#define SS7_SM_GET_ERR_LEVEL_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define SS7_SM_SET_ERR_LEVEL_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 2)

#define SS7_SM_GET_EVENT_REPORTING_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define SS7_SM_SET_EVENT_REPORTING_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 2)
#define SS7_SM_DISPLAY_MODULE_VERSION_NO_ELEM         (SS7_SM_API_MIN_NO_ELEM)
/* SPR # 6566 : Fix Start */
#define SS7_SM_DISPLAY_SS_STATUS_NO_ELEM         (SS7_SM_API_MIN_NO_ELEM + 1)
/* SPR # 6566 : Fix End */

/* SPR  7490 : Start Fix */
#define SS7_SM_DISPLAY_SP_STATUS_NO_ELEM         (SS7_SM_API_MIN_NO_ELEM + 1)
/* SPR  7490 :  End Fix */

/*****************************************************************************
**
**	MTP2 related system management stuff
**
*****************************************************************************/

/*****************************************************************************
**
**      API command ids to be used by the System Management for MTP2
**
*****************************************************************************/

#define MTP2_SM_INIT_LINK               0x00
#define MTP2_SM_INIT_TIMERS             0x01
#define MTP2_SM_INIT_CONG_PARAMS        0x02

#define MTP2_SM_LOCAL_PROC_OUT          0x00
#define MTP2_SM_CONGESTION              0x01

#define MTP2_SM_API_NUM                 13

/*****************************************************************************
**
**	Length of the MTP2 specific system management commands
**
*****************************************************************************/

#define MTP2_SM_MTP2_INIT_LINK_LEN              (SS7_SM_API_MIN_LEN + 4)
#define MTP2_SM_MTP2_INIT_TIMERS_MIN_LEN        (SS7_SM_API_MIN_LEN + 3)
#define MTP2_SM_MTP2_INIT_CONG_PARAMS_LEN       (SS7_SM_API_MIN_LEN + 20)
#define MTP2_SM_MTP2_LPO_LEN                    (SS7_SM_API_MIN_LEN + 3)
#define MTP2_SM_MTP2_CONGESTION_LEN             (SS7_SM_API_MIN_LEN + 1)

/*****************************************************************************
**
**	no of elements in the MTP2 specific system management commands
**
*****************************************************************************/

#define MTP2_SM_MTP2_INIT_LINK_ELEMS            (SS7_SM_API_MIN_NO_ELEM + 3)
#define MTP2_SM_MTP2_INIT_CONG_ELEMS            (SS7_SM_API_MIN_NO_ELEM + 2)
#define MTP2_SM_MTP2_INIT_TIMERS_ELEMS          (SS7_SM_API_MIN_NO_ELEM + 3)
#define MTP2_SM_MTP2_LPO_ELEMS                  (SS7_SM_API_MIN_NO_ELEM + 2)
#define MTP2_SM_MTP2_CONGESTION_ELEMS           (SS7_SM_API_MIN_NO_ELEM + 1)

/* event level for mtp2 */
#define MTP2_EVENT_REPORTING     1
#define MTP2_NO_EVENT_REPORTING  0


/*
** System Management Command Ids for MTP3
*/


#define MTP3_SM_INIT_TIMER                     0
#define MTP3_SM_ADD_SELF_POINT_CODE            1
#define MTP3_SM_MODIFY_SELF_POINT_CODE         2
#define MTP3_SM_DEL_SELF_POINT_CODE            3
#define MTP3_SM_ADD_DESTINATION                4
#define MTP3_SM_DEL_DESTINATION                5
#define MTP3_SM_ADD_LINK                       6
#define MTP3_SM_MODIFY_LINK                    7
#define MTP3_SM_DEL_LINK                       8
#define MTP3_SM_ADD_LINKSET                    9
#define MTP3_SM_MODIFY_LINKSET                 10
#define MTP3_SM_DEL_LINKSET                    11
#define MTP3_SM_ADD_ROUTE                      12
#define MTP3_SM_MODIFY_ROUTE                   13  
#define MTP3_SM_DEL_ROUTE                      14
#define MTP3_SM_ADD_LINK_TO_LINKSET            15
#define MTP3_SM_DEL_LINK_FROM_LINKSET          16
#define MTP3_SM_ANSI_RESTART_OPTION            17
#define MTP3_SM_UPDATE_TEST_PATTERN            18
#define MTP3_SM_ADD_NEW_LINKSET                19
#define MTP3_SM_ADD_NEW_SELF_POINT_CODE        20
#define MTP3_SM_ADD_NEW_DESTINATION            21
#define MTP3_SM_DEL_NEW_DESTINATION            22
#define MTP3_SM_ADD_NEW_LINK                   23
#define MTP3_SM_ADD_NEW_ROUTE                  24
#define MTP3_SM_DEL_NEW_ROUTE                  25
#define MTP3_SM_GET_PROV_INFO                  26

#ifdef DISTRIBUTED_MTP3
#define DMTP3_SM_ADD_DMTP3_INSTANCE            27
/* START SPR FIX 6486 */
#define DMTP3_SM_ADD_DNR_INSTANCE              28
/* END SPR FIX 6486 */
#endif /* DSITRIBUTED_MTP3 */

/* For testing purpose */
#define MTP3_SM_TRF_GEN            	       19



/*
** #defines for System Management Control Commands
*/
#define MTP3_SM_DEACTIVATE_USER  0 
#define MTP3_SM_INH_LINK   	1
#define MTP3_SM_UNINH_LINK   	2
#define MTP3_SM_START_LINK      3
#define MTP3_SM_STOP_LINK       4 
#define MTP3_SM_START_LINKSET   5   
#define MTP3_SM_STOP_LINKSET    6   
#define MTP3_SM_START_LINK_TEST 7
#define MTP3_SM_STOP_LINK_TEST  8   
#define MTP3_SM_SP_CONG_CHANGE  9
#define MTP3_SM_LOCAL_PROC_OUT  10
#define MTP3_SM_PLC_LINKSET_REST_OPC  11
#define MTP3_SM_PLC_LINKSET_REST_DPC  12
#define MTP3_SM_PLC_LINKSET_UNREST_OPC  13
#define MTP3_SM_PLC_LINKSET_UNREST_DPC  14



/*
** #defines for System Management Display STATUS  APIs 
*/
#define MTP3_SM_GET_SELF_PC_STATUS    0
#define MTP3_SM_GET_DPC_STATUS        1
#define MTP3_SM_GET_LINK_STATUS       2
#define MTP3_SM_GET_ROUTE_STATUS      3
/* DISPLAY commands for all modules */
#define SS7_SM_DISPLAY_MODULE_VERSION    4
/* SPR # 6566 : Fix start */
#define SS7_SM_DISPLAY_SS_STATUS      5
/* SPR # 6566 : Fix end */

/* SPR 7490 : Start Fix */
#define  SS7_SM_DISPLAY_SP_STATUS       6
/* SPR 7490 : End Fix */

/* event types defined for MTP3 */

#define MTP3_SM_OBJECT_SELF_PC      	 0
#define MTP3_SM_OBJECT_ROUTE 		 1
#define MTP3_SM_OBJECT_LINK		 2
#define MTP3_SM_OBJECT_DPC		 3
#define MTP3_SM_OBJECT_INV_MSG		 4
#define MTP3_SM_OBJECT_CLUSTER     	 5 
#define MTP3_SM_OBJECT_X_MEM       	 6
#define MTP3_SM_OBJECT_CLUSTER_ROUTE	 7 
#define MTP3_SM_OBJECT_UNEXPECT_MSG	 8 
#define MTP3_SM_ALL_OBJECTS 	 	 9

/* event level for mtp3 */
#define MTP3_EVENT_RPT     1
#define MTP3_NO_EVENT_RPT  0 



#define MTP3_NUM_PROV_CMD 31
#define MTP3_NUM_CTRL_CMD 15 
#define MTP3_NUM_STATS_CMD 4
#define MTP3_NUM_DEBUG_CMD 2
#define MTP3_NUM_ERROR_CMD 4
#define MTP3_NUM_REDN_CMD  4
#define MTP3_NUM_DISP_CMD  5

/*
** Number of elements associated with different Commands
*/
/*  for PROV SM APIs */
#define MTP3_NUM_ELEM_ADD_SPC       5
#define MTP3_NUM_ELEM_DEL_SPC       4
#define MTP3_NUM_ELEM_ADD_DEST      5
#define MTP3_NUM_ELEM_DEL_DEST      4
#define MTP3_NUM_ELEM_ADD_LINK      9
#define MTP3_NUM_ELEM_DEL_LINK      4
#define MTP3_NUM_ELEM_ADD_LINKSET   8 
#define MTP3_NUM_ELEM_DEL_LINKSET   4
#define MTP3_NUM_ELEM_ADD_ROUTE     9
#define MTP3_NUM_ELEM_DEL_ROUTE     4
#define MTP3_NUM_ELEM_ADD_LINK_LINKSET  6
#define MTP3_NUM_ELEM_DEL_LINK_LINKSET  6
#define MTP3_NUM_ELEM_INIT_TIMER       5
#define MTP3_NUM_ELEM_ANSI_RESTART_OPT       4
#define MTP3_NUM_ELEM_UPD_TEST_PAT       4
#define MTP3_NUM_ELEM_TRF_GEN       5

#define MTP3_NUM_ELEM_ADD_NEW_SPC       6
#define MTP3_NUM_ELEM_ADD_NEW_DEST      7 /* change for adding SLS field */
#define MTP3_NUM_ELEM_DEL_NEW_DEST      6
#define MTP3_NUM_ELEM_ADD_NEW_LINK      11
#define MTP3_NUM_ELEM_ADD_NEW_LINKSET   11 
#define MTP3_NUM_ELEM_ADD_NEW_ROUTE     10
/* Start Spr 11302 Fix */
#define MTP3_NUM_ELEM_DEL_NEW_ROUTE     6
/* Stop Spr 11302 Fix */
/* Added for New Provisioning Api's where SME will ask for Provisioned Data */

#define MTP3_NUM_ELEM_GET_PROV_INFO     4
#ifdef DISTRIBUTED_MTP3
#define DMTP3_NUM_ELEM_ADD_DMTP3_INSTANCE 4
/* START SPR FIX 6486 */
#define DMTP3_NUM_ELEM_ADD_DNR_INSTANCE  4
/* END SPR FIX 6486 */
#endif /* DISTRIBUTED_MTP3 */
 
 
#define MTP3_NUM_ELEM_INH_LINK          4
#define MTP3_NUM_ELEM_UNINH_LINK        4
#define MTP3_NUM_ELEM_START_LINK        5
#define MTP3_NUM_ELEM_STOP_LINK         4
#define MTP3_NUM_ELEM_START_LINKSET     5
#define MTP3_NUM_ELEM_STOP_LINKSET      4
#define MTP3_NUM_ELEM_START_LINK_TEST   5
#define MTP3_NUM_ELEM_STOP_LINK_TEST    4
#define MTP3_NUM_ELEM_SP_CONG_CHANGE    4
#define MTP3_NUM_ELEM_DEACTIVATE_USER   4
#define MTP3_NUM_ELEM_LOCAL_PROC_OUT    5
#define MTP3_NUM_ELEM_LOCAL_PROC_OUT    5
#define MTP3_NUM_ELEM_PLC_LSET_REST_OPC    6
#define MTP3_NUM_ELEM_PLC_LSET_REST_DPC    7
#define MTP3_NUM_ELEM_PLC_UNREST_OPC    5
#define MTP3_NUM_ELEM_PLC_UNREST_DPC    5

#define MTP3_NUM_ELEM_INIT_STATS           4
/* SPR4463 fix begins (MTP3_NUM_ELEM_GET_STATS : 6 -> 5)*/
#define MTP3_NUM_ELEM_GET_STATS		   5
/* SPR4463 fix ends */
#define MTP3_NUM_ELEM_DISABLE_STATS        4		
#define MTP3_NUM_ELEM_ENABLE_STATS         4
#define MTP3_NUM_ELEM_GET_TRACE_LEVEL      4
#define MTP3_NUM_ELEM_SET_TRACE_LEVEL      5
#define MTP3_NUM_ELEM_GET_ERR_LEVEL        4
#define MTP3_NUM_ELEM_SET_ERR_LEVEL        5

#define MTP3_NUM_ELEM_GET_EVENT_REPORTING        4
#define MTP3_NUM_ELEM_SET_EVENT_REPORTING        5

#define MTP3_NUM_ELEM_INIT_REDN_DATA       4
#define MTP3_NUM_ELEM_ACT_MTP3             3
#define MTP3_NUM_ELEM_RECEIVE_UPDATE       6
#define MTP3_NUM_ELEM_REQUEST_ACTIVE       5

#define MTP3_NUM_ELEM_GET_SELF_PC_STATUS   5
/* SPR 4463 : fix begins (change value from 6 -> 5)*/
#define MTP3_NUM_ELEM_GET_DPC_STATUS       5
/* SPR 4463 : fix ends */
#define MTP3_NUM_ELEM_GET_LINK_STATUS      5
#define MTP3_NUM_ELEM_GET_ROUTE_STATUS     5


 /* System Management Commands */
#define ISUP_MAX_SM_COMD                ISUP_INIT_TIMERS_TENS_MS 


#define ISUP_PROV_CKT_GRP_LEN           (SS7_SM_API_MIN_LEN + 11)
#define ISUP_UNPROV_CKT_GRP_LEN         (SS7_SM_API_MIN_LEN + 8)
#define ISUP_INIT_TIMERS_MIN_LEN        (SS7_SM_API_MIN_LEN + 1)
#define ISUP_INIT_TIMERS_MAX_LEN        (SS7_SM_API_MIN_LEN + 118)
#define ISUP_INIT_REDN_DATA_LEN		(SS7_SM_API_MIN_LEN + 1)
#define ISUP_ACTIVATE_MODULE_DATA_LEN	(SS7_SM_API_MIN_LEN)
#define ISUP_REDN_REQ_ACT_LEN		(SS7_SM_API_MIN_LEN + 9)
#define ISUP_REDN_RECV_UPDATE_LEN_MIN 	(SS7_SM_API_MIN_LEN + 10)
#define ISUP_PROV_GRP_RANGE_LEN         (SS7_SM_API_MIN_LEN + 10)




#define ISUP_PROV_CKT_GRP_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 6)
#define ISUP_UNPROV_CKT_GRP_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 4)
#define ISUP_INIT_TIMERS_NO_ELEM 	    	(SS7_SM_API_MIN_NO_ELEM + 2)
#define ISUP_INIT_REDN_DATA_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 1)
#define ISUP_ACTIVATE_MODULE_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM)
#define ISUP_REDN_REQ_ACT_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 5)
#define ISUP_REDN_RECV_UPDATE_MIN_NO_ELEM	(SS7_SM_API_MIN_NO_ELEM + 6)
#define ISUP_REDN_RECV_UPDATE_MAX_NO_ELEM	(SS7_SM_API_MIN_NO_ELEM + 7)
#define ISUP_PROV_GRP_RANGE_NO_ELEM		(SS7_SM_API_MIN_NO_ELEM + 4)

/*** BISUP Specific defines ***/
#define BISUP_INIT_TIMERS_MIN_LEN               (SS7_SM_API_MIN_LEN + 1)
#define BISUP_INIT_TIMERS_NO_ELEM               (SS7_SM_API_MIN_NO_ELEM + 2)



/* DATA TYPE FOR EVENTS */
/* Used to maintain events */
typedef struct {
        count_t  count;
        ss7_time_t   time;
} ss7_event_t;

/* API STATISTICS */
typedef struct {
        count_t  in_api_su;      /* incoming API's from service user */
        count_t  out_api_su;     /* outgoing API's to service user */
        count_t  in_api_ll;      /* incoming API's from lower layer */
        count_t  out_api_ll;     /* outgoing API's to lower layer */
        count_t  in_api_sm;      /* incoming API's from system management */
        count_t  out_api_sm;     /* outgoing API's to system management */
        count_t  err_api_su;     /* errors in incoming API's from SU */
        count_t  err_api_ll;     /* errors in incoming API's from LL */
        count_t  err_api_sm;     /* errors in incoming API's from SM */
        count_t  err_out_api_ll; /* errors in outgoing API's to LL */
        count_t  err_api_misc;   /* miscellaneous API errors   */
} ss7_stats_api_t;

/* ERROR STATISTICS */
typedef struct {
        count_t  err_api;        /* errors in incomming API's */
        count_t  err_msg;        /* erroneous messages received from peer */
        count_t  err_sys;        /* system call failures */
        count_t  err_system_res; /* system resource failures */
} ss7_stats_error_t;

/***************************************************************************
**          SCCP system management related stuff
***************************************************************************/

/* commands for category PROV */

#define SCCP_SM_INIT_TIMER       0
#define SCCP_SM_ADD_SP           1
#define SCCP_SM_ADD_SS           2
#define SCCP_SM_ADD_CSS          3
#define SCCP_SM_ADD_CSP          4
#define SCCP_SM_DEL_SP            5
#define SCCP_SM_DEL_SS            6
#define SCCP_SM_DEL_CSS           7
#define SCCP_SM_DEL_CSP           8
#define SCCP_SM_GET_TIMER_INFO	  9
#define SCCP_SM_GET_SP_INFO	  	  10
#define SCCP_SM_GET_SS_INFO	  	  11
#define SCCP_SM_GET_CSS_INFO	  12
#define SCCP_SM_GET_CSP_INFO	  13
#define SCCP_SM_ADD_BACKUP_SSN   14
#ifdef DISTRIBUTED_SCCP
#define DSCCP_SM_CONF_NEW_INSTANCE 15
#endif
#define SCCP_SM_ACTIVATE_INSTANCE 16

/* New Commands for provisioning trans funcs --Sachin Bhatia */
/* Yhe ID used are from 17 as they are in category prov ... 
   should not be  confused with SCCP_SM_DEINIT_INSTANCE which 
   is also 17 but under category CTRL */

#define SCCP_SM_ADD_MTPSAP	17
#define SCCP_SM_ADD_TRANS_RULE 18
#define SCCP_SM_ADD_TO_DPC_SSN_TABLE 19
#define SCCP_SM_DEL_MTPSAP 20
#define SCCP_SM_DEL_TRANS_RULE 21
#define SCCP_SM_DEL_FROM_DPC_SSN_TABLE 22
#define SCCP_SM_GET_MTPSAP_INFO 23
#define SCCP_SM_GET_TRANS_FUNC_LIST_INFO 24
#define SCCP_SM_GET_RULE_LIST_PER_TRANS_FUNC_INFO 25

/* New Commands end here */

/* commands for category CTRL */
#define SCCP_SM_DEINIT_INSTANCE 17
#define SCCP_SM_INIT_INSTANCE 18



/* lengths of elements */
#define SCCP_SM_TIMER_ID_LEN   1
#define SCCP_SM_TIMER_DUR_LEN  4
#define SCCP_SM_NUM_TIMER_LEN  1
#define SCCP_SM_NW_ID_LEN      1
#define SCCP_SM_SP_ID_LEN      4
#define SCCP_SM_SS_ID_LEN      4
#define SCCP_SM_PC_LEN         4
#define SCCP_SM_SSN_LEN        1
#define SCCP_SM_FLAGS_LEN      1
#define SCCP_SM_SSF_LEN        1

/* Number of elements in messages */
#define SCCP_SM_INIT_TIMER_NELEM   (SS7_SM_API_MIN_NO_ELEM + 2)
#define SCCP_SM_ADD_SP_NELEM       (SS7_SM_API_MIN_NO_ELEM + 5)
#define SCCP_SM_ADD_SS_NELEM       (SS7_SM_API_MIN_NO_ELEM + 3)
#define SCCP_SM_ADD_CSS_NELEM      (SS7_SM_API_MIN_NO_ELEM + 2)
#define SCCP_SM_ADD_CSP_NELEM      (SS7_SM_API_MIN_NO_ELEM + 2)
#define SCCP_SM_DEL_SP_NELEM        (SS7_SM_API_MIN_NO_ELEM + 1)
#define SCCP_SM_DEL_SS_NELEM        (SS7_SM_API_MIN_NO_ELEM + 1)
#define SCCP_SM_DEL_CSS_NELEM       (SS7_SM_API_MIN_NO_ELEM + 2)
#define SCCP_SM_DEL_CSP_NELEM       (SS7_SM_API_MIN_NO_ELEM + 2)
#define SCCP_SM_GET_TIMER_INFO_NLEM (SS7_SM_API_MIN_NO_ELEM)
#define SCCP_SM_GET_SP_INFO_NLEM 	(SS7_SM_API_MIN_NO_ELEM)
#define SCCP_SM_GET_SS_INFO_NLEM 	(SS7_SM_API_MIN_NO_ELEM)
#define SCCP_SM_GET_CSS_INFO_NLEM 	(SS7_SM_API_MIN_NO_ELEM + 1)
#define SCCP_SM_GET_CSP_INFO_NLEM 	(SS7_SM_API_MIN_NO_ELEM + 1)

/* lengths of various messages */
#define SCCP_SM_INIT_TIMER_LEN  (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_NUM_TIMER_LEN + \
                                 SCCP_SM_TIMER_ID_LEN + \
                                 SCCP_SM_TIMER_DUR_LEN)

#define SCCP_SM_ADD_SP_LEN     (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SP_ID_LEN + \
                                 SCCP_SM_NW_ID_LEN + \
                                 SCCP_SM_PC_LEN + \
                                 SCCP_SM_FLAGS_LEN + \
                                 SCCP_SM_SSF_LEN)

#define SCCP_SM_ADD_SS_LEN     (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SS_ID_LEN + \
                                 SCCP_SM_SP_ID_LEN + \
                                 SCCP_SM_SSN_LEN + \
                                 SCCP_SM_FLAGS_LEN)

#define SCCP_SM_ADD_CSS_LEN    (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SS_ID_LEN + \
                                 SCCP_SM_SS_ID_LEN)

#define SCCP_SM_ADD_CSP_LEN    (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SS_ID_LEN + \
                                 SCCP_SM_SP_ID_LEN)

#define SCCP_SM_DEL_SP_LEN      (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SP_ID_LEN + \
                                 SCCP_SM_FLAGS_LEN)

#define SCCP_SM_DEL_SS_LEN      (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SS_ID_LEN + \
                                 SCCP_SM_FLAGS_LEN)

#define SCCP_SM_DEL_CSS_LEN     (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SS_ID_LEN + \
                                 SCCP_SM_SS_ID_LEN)

#define SCCP_SM_DEL_CSP_LEN     (SS7_SM_API_MIN_LEN + \
                                 SCCP_SM_SS_ID_LEN + \
                                 SCCP_SM_SP_ID_LEN)

#define SCCP_SM_GET_TIMER_INFO_LEN		SS7_SM_API_MIN_LEN
#define SCCP_SM_GET_SP_INFO_LEN			SS7_SM_API_MIN_LEN
#define SCCP_SM_GET_SS_INFO_LEN			SS7_SM_API_MIN_LEN
#define SCCP_SM_GET_CSS_INFO_LEN		(SS7_SM_API_MIN_LEN + \
										 SCCP_SM_SS_ID_LEN)
#define SCCP_SM_GET_CSP_INFO_LEN		(SS7_SM_API_MIN_LEN + \
										 SCCP_SM_SS_ID_LEN)

/** end of SCCP system management related stuff                        **/

/***************************************************************************
**          TCAP system management related stuff
***************************************************************************/

/* commands for category CTRL */
#define TCAP_SM_DEINIT_INSTANCE 19
#define TCAP_SM_INIT_INSTANCE   20

/* START FIX SPR 10507 */
#define TCAP_SM_DTCAP_ACTIVATE_INSTANCE	21
/* END FIX SPR 10507 */

/** end of TCAP system management related stuff                        **/

#endif  /* end of _S7_SM_H_ */
