/*******************************************************************************
**      FILE NAME:
**          s7_api.h
**
**      DESCRIPTION:
**              Gives the range of each stack entities API IDs along with each API IDs values.
**							
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef _S7_API_H_     /* If this file has not been processed, */
#define _S7_API_H_     /* define it as seen--ref '#endif' below. */

/* api header length */
/* to be used to calculate API buffer length */
#define SS7_API_HEADER_LEN      5
#define MAX_OPTIONAL_DATA_LEN 128
/*
** This is the hashdefine for Timer API ID
*/

/* Added by Amaresh start as on dated 08-02-16*/
#define BSSAP_CARD_STATE_ACTIVE   1
#define BSSAP_CARD_STATE_STANDBY  0
/* Added by Amaresh stop as on dated 08-02-16*/

#define SS7_TIMER_API_ID 0
/*
** API Ranges fo each stack entity
*/
#define MTP2_MIN_API 1
#define MTP2_MAX_API 25
#define MTP2_MAX_CLIENT_API     15

#define MTP3_MIN_API 26
#define MTP3_MAX_API 65
#define MTP3_MAX_CLIENT_API 25 /* gives the max. count of client side APIs */

#define ISUP_MIN_API 66
#define ISUP_MAX_API 165
#define ISUP_MAX_CLIENT_API /* gives the max. count of client side APIs */

#define BISUP_MIN_API 66
#define BISUP_MAX_API 165
#define BISUP_MAX_CLIENT_API 50 /* gives the max. count of client side APIs */

#ifdef BACK_UP_SSN
#define SCCP_MIN_API 166
#define SCCP_MAX_API 198
#define TCAP_MIN_API 199
#define TCAP_MAX_API 251
#else
#define SCCP_MIN_API 166
#define SCCP_MAX_API 195
#define TCAP_MIN_API 196
#define TCAP_MAX_API 247
#endif

#ifdef SCCP_INCLUDE_CO_SERVICE
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
#define SCCP_MAX_CLIENT_API 13 /* gives the max. count of client side APIs */
#else
#define SCCP_MAX_CLIENT_API 10 /* gives the max. count of client side APIs */
#endif
#else
#define SCCP_MAX_CLIENT_API 3 /* gives the max. count of client side APIs */
#endif

/* #define TCAP_MAX_CLIENT_API  gives the max. count of client side APIs */
#define HM_API_ID   253

/********************************************* RULES FOR DEFINING API IDs ********
*******
*******            FIRST DEFINE APIs "TO" A PARTICULAR MODULE AND THEN
*******            APIs "FROM" THAT MODULE. 
*******
*******************************************************************************/
/******************************************************************************
**
**  APIs invoked by MTP2, i.e. used in send_from_mtp2 API
**
******************************************************************************/
#define MAX_MTP2_API_LENGTH             (272 + 4 + 5)
#define MTP2_CURRENT_CLIENT_APIS        9

#define MTP2_START_LINK                 (MTP2_MIN_API + 0)
#define MTP2_STOP_LINK                  (MTP2_MIN_API + 1)
#define MTP2_PROCESSOR_OUTAGE           (MTP2_MIN_API + 2)
#define MTP2_MSU_TO_MTP2                (MTP2_MIN_API + 3)
#define MTP2_LAST_BSN_RECV              (MTP2_MIN_API + 4)
#define MTP2_LINK_STATUS_FROM_MTP3      (MTP2_MIN_API + 5)
#define MTP2_FLUSH_RTB                  (MTP2_MIN_API + 6)
#define MTP2_NOT_ACKED_MSUS             (MTP2_MIN_API + 7)
#define MTP2_CONTINUE_FROM_MTP3         (MTP2_MIN_API + 8)

/******************************************************************************
**
**  APIs invoked by MTP2, i.e. used in send_from_mtp2 API
**
******************************************************************************/

#define MTP2_MSU_TO_MTP3                (MTP2_MIN_API + MTP2_MAX_CLIENT_API + 0)
#define MTP2_LINK_STATUS_TO_MTP3        (MTP2_MIN_API + MTP2_MAX_CLIENT_API + 1)
#define MTP2_LAST_BSN_RECV_TO_MTP3      (MTP2_MIN_API + MTP2_MAX_CLIENT_API + 2)
#define MTP2_NOT_ACKED_MSUS_TO_MTP3     (MTP2_MIN_API + MTP2_MAX_CLIENT_API + 3)

/******************************************************************************
**
**  APIs invoked by SAAL NNI , i.e. used in send_from_snni API
**  added for broadband support 
******************************************************************************/
#define SNNI_BSN_NOT_RETRIEVABLE_TO_MTP3 (MTP2_MIN_API + MTP2_MAX_CLIENT_API + 4)
/****************************************************************************
**
**      APIs used by MTP2 System Mg. Entity
**
****************************************************************************/

#define MTP2_SM_REQUEST_API     (MTP2_MIN_API+MTP2_CURRENT_CLIENT_APIS)
#define MTP2_SM_RESPONSE_API    (MTP2_MIN_API+MTP2_CURRENT_CLIENT_APIS+1)

/****************************************************************************
**
**      APIs internally used by MTP2
**
****************************************************************************/

#define MTP2_MTP1_SU_IND        (MTP2_MAX_API - 1)
#define MTP2_MTP1_ERR_IND       (MTP2_MAX_API - 2)
#define MTP2_DATA_RECV          (MTP2_MAX_API - 3)
#define MTP2_LINK_FAILURE       (MTP2_MAX_API - 4)
#define MTP2_SYS_CONGESTION_API     (MTP2_MAX_API - 5)

/*
************* Number of elements corresponding to an API
*/

#define MTP2_ELEMENTS_START_LINK        3
#define MTP2_ELEMENTS_STOP_LINK         2
#define MTP2_ELEMENTS_PROCESSOR_OUTAGE      3
#define MTP2_ELEMENTS_MSU_TO_MTP2       3
#define MTP2_ELEMENTS_LAST_BSN_RECV     2
#define MTP2_ELEMENTS_LINK_STATUS_FROM_MTP3 2
#define MTP2_ELEMENTS_FLUSH_RTB         2
#define MTP2_ELEMENTS_NOT_ACKED_MSUS        4
#define MTP2_ELEMENTS_CONTINUE_FROM_MTP3    2


#define MTP2_ELEMENTS_MSU_TO_MTP3       3
#define MTP2_ELEMENTS_LINK_STATUS_TO_MTP3   3
#define MTP2_ELEMENTS_LAST_BSN_RECV_TO_MTP3 3
#define MTP2_ELEMENTS_NOT_ACKED_MSUS_TO_MTP3    6

/* added for broadband support */
#define SNNI_ELEMENTS_BSN_NOT_RETRIEVABLE_TO_MTP3 2




/******************************************************************************
**
**  API element lentghs 
**
******************************************************************************/

#define MTP2_FSN_LENGTH         0x01
#define MTP2_INVOKE_ID_LENGTH       0x01
#define MTP2_LINK_STATUS_LENGTH     0x02
#define MTP2_BSN_LENGTH         0x01
#define MTP2_ALIGN_PROC_LENGTH      0x01
#define MTP2_LINK_ID_LENGTH     0x02
#define MTP2_ID_LENGTH                  0x02
#define MTP2_PROC_OUTAGE_STATUS_LENGTH  0x01
#define MTP2_RETR_MSU_NO_LENGTH     0x01
#define MTP2_START_FSN_LENGTH       0x01
#define MTP2_TOTAL_NUM_MSUS_LENGTH  0x01

#define MTP2_API_ID_LENGTH              0x01
#define MTP2_VER_ID_LENGTH              0x01
#define MTP2_NELEMENTS_LENGTH           0x01
#define MTP2_LENGTH_LENGTH              0x02

#define MTP2_HEADER_LENGTH              (MTP2_API_ID_LENGTH \
                                        + MTP2_VER_ID_LENGTH \
                                        + MTP2_NELEMENTS_LENGTH \
                                        + MTP2_LENGTH_LENGTH)

/* added for broadband support */
#define MTP2_X_BSN_LENGTH                           0x03
#define MTP2_X_FSN_LENGTH                           0x03
#define MTP2_RETR_MSU_NO_LENGTH_FOR_BROADBAND       0x03
#define MTP2_TOTAL_NUM_MSUS_LENGTH_FOR_BROADBAND    0x03

/******************************************************************************
**
**  API element values
**
******************************************************************************/

/*  LinkStatus */

/*
 *  The flags used for extraction of the status info.
 *  The first byte of the status info should be ANDED with these
 *  and then the values compared with the #defined below.
 */
#define MTP2_LINK_SOA_FLAG      0x0001
#define MTP2_LINK_SOS_FLAG      0x0002
#define MTP2_LINK_SCONG_FLAG        0x000C
#define MTP2_LINK_SDISC_FLAG        0x0030
#define MTP2_LINK_RPO_FLAG      0x0040
#define MTP2_LINK_RCONG_FLAG        0x0080
#define MTP2_LINK_LPO_FLAG              0x0100

/*  Signalling link is out of alignment */
#define MTP2_LINK_SOA           0x0001    

/*  Signalling link is out of service */
#define MTP2_LINK_SOS           0x0002    

/*  Signalling link congestion level */
#define MTP2_LINK_SCONG_NO_CONG     0x0000    
#define MTP2_LINK_SCONG_LEVEL_1     0x0004    
#define MTP2_LINK_SCONG_LEVEL_2     0x0008    
#define MTP2_LINK_SCONG_LEVEL_3     0x000C    

/*  Signalling link discard level */
#define MTP2_LINK_SDISC_NO_DISC     0x0000
#define MTP2_LINK_SDISC_LEVEL_1     0x0010
#define MTP2_LINK_SDISC_LEVEL_2     0x0020
#define MTP2_LINK_SDISC_LEVEL_3     0x0030

/*  Signalling link remote processor outage status  */
#define MTP2_LINK_RPO           0x0040
#define MTP2_LINK_LPO                   0x0100

/*  Signalling link remote congection level */
#define MTP2_LINK_RCONG         0x0080

/*  Mtp2AlignProc */

/*  Use normal alignment procedure as initial alignment procedure */
#define MTP2_NORMAL_ALIGNMENT           0x01    
/*  Use emergency alignment procedure as initial alignment procedure */
#define MTP2_EMERGENCY_ALIGNMENT        0x02    

/*  ProcOutageStatus */

/*  Start of local processor outage */
#define MTP2_LOCAL_PROC_OUTAGE_START    0x01    
/*  Cease of local processor outage */
#define MTP2_LOCAL_PROC_OUTAGE_CEASE    0x02    

/*  Congestion start */

/*  Start of local congestion */
#define MTP2_CONGESTION_START       0x01
/*  Stop local congestion */
#define MTP2_CONGESTION_STOP        0x02

/*  Link speed */
#define MTP2_LOW_SPEED_LINK     0x01
#define MTP2_HIGH_SPEED_LINK        0x02

/*  TXRX method */
#define MTP2_TXRX_METHOD_BASIC      0x01
#define MTP2_TXRX_METHOD_PCR        0x02

/*
*******************MTP3 API IDs************************************************
**
**  APIs invoked by Service User , i.e. used in send_to_mtp3 API
**
******************************************************************************/
#define MTP3_UP_START_API           (MTP3_MIN_API)
/* SPR 5286 FIX */
#define MTP3_UP_STOP_API            (MTP3_MIN_API + 2)
#define MTP3_UP_REGISTER_USER_PART  (MTP3_MIN_API + 0)
#define MTP3_UP_TRANSFER_REQUEST    (MTP3_MIN_API + 1)
#define MTP3_UP_DPC_STATUS_REQUEST  (MTP3_MIN_API + 2)
/* SPR 5286 FIX */
#define MTP3_SM_REQUEST_API         (MTP3_MIN_API + 3)


/******************************************************************************
**
**  APIs invoked by MTP3 i.e. used in send_from_mtp3 API
**
******************************************************************************/

#define MTP3_UP_TRANSFER_INDICATION     (MTP3_MIN_API+MTP3_MAX_CLIENT_API+1)
#define MTP3_UP_PAUSE_INDICATION    (MTP3_MIN_API+MTP3_MAX_CLIENT_API+2)
#define MTP3_UP_RESUME_INDICATION       (MTP3_MIN_API+MTP3_MAX_CLIENT_API+3)
#define MTP3_UP_STATUS_INDICATION       (MTP3_MIN_API+MTP3_MAX_CLIENT_API+4)
#define MTP3_SM_RESPONSE_API            (MTP3_MIN_API+MTP3_MAX_CLIENT_API+5)
#define MTP3_ANSI_UP_CLUSTER_PAUSE_INDICATION       (MTP3_MIN_API+MTP3_MAX_CLIENT_API+6)
#define MTP3_ANSI_UP_CLUSTER_RESUME_INDICATION      (MTP3_MIN_API+MTP3_MAX_CLIENT_API+7)
/*
** Hashdefs for Number of elements in MTP3 APIs
*/
#define MTP3_NUM_ELEM_REG_UP        2
#define MTP3_NUM_ELEM_TRANSFER_REQ  1
#define MTP3_NUM_ELEM_DPC_STATUS_REQ    3




#define MTP3_NUM_ELEM_UP_PAUSE_INDICATION   1
#define MTP3_NUM_ELEM_UP_RESUME_INDICATION  1
#define MTP3_NUM_ELEM_UP_STATUS_INDICATION  3
#define MTP3_NUM_ELEM_UP_TRANSFER_INDICATION    1
#define MTP3_ANSI_NUM_ELEM_UP_CLUSTER_PAUSE_IND 1
#define MTP3_ANSI_NUM_ELEM_UP_CLUSTER_RESUME_IND 1

#define MTP3_GET_STATUS_FOR_DPC                 1
#define MTP3_GET_STATUS_FOR_ALL_DPC             2 



/*
** Hashdefs for Length of API elements corresponding to MTP3 APIs
*/
#define MTP3_LENGTH_CAUSE                   1
#define MTP3_LENGTH_CONGESTION_STATUS_LEVEL     1
#define MTP3_LENGTH_LOG_USER_ID             4
#define MTP3_LENGTH_SIO                     1
/* 
** Changed MIN_USER_DATA from 1 to 5 as User data should
** include atleast the SIO and the routing Label for MTP3
** to do the routing
*/
#define MTP3_MIN_USER_DATA                  5
#define MTP3_JAPANESE_MIN_USER_DATA                     6
#define MTP3_CHINESE_MIN_USER_DATA                  8
/* 
** Changed MAX_USER_DATA from 272 to 273 as the SIF field
** can be max. 272 bytes so including the SIO it is 273 bytes
*/
#define MTP3_MAX_USER_DATA          273

#define MTP3_ANSI_MIN_USER_DATA     8
#define MTP3_ANSI_MAX_USER_DATA     273

/* added for broadband support */
#define MTP3_MAX_USER_DATA_FOR_BROADBAND        4096
#define MTP3_ANSI_MAX_USER_DATA_FOR_BROADBAND   4096


/*
** Hashdefs for the values of API elements
*/

/* hashdefs for cause parameter */

#define MTP3_CAUSE_USER_PART_UNAV_UNKNOWN       0
#define MTP3_CAUSE_USER_PART_UNAV_UNEQUIP_REMOTE_USER   1
#define MTP3_CAUSE_USER_PART_UNAV_INACCESS_REMOTE_USER  2
#define MTP3_CAUSE_SIG_NETWORK_CONGESTION       3
/* Fix for SPR NO : 13344 Start */
#define SCCP_CAUSE_SIG_CONGESTION       4
/* Fix for SPR NO : 13344 End */



/* hashdefs for congestion level parameter */

#define MTP3_CONG_LEVEL_NO_CONG 0
#define MTP3_CONG_LEVEL_1       1
#define MTP3_CONG_LEVEL_2       2
#define MTP3_CONG_LEVEL_3       3

/* hashdef for DMTP3 */
#define DMTP3_MIN_API           36
#define DMTP3_MAX_API           37
#define DMTP3_API               DMTP3_MIN_API+0


/********************SCCP API IDs************************************************
**
**  SCCP APIs 
**
******************************************************************************/

/** APIs invoked by SCCP-client, i.e. used in send_to_sccp API   **/
#ifdef BACK_UP_SSN

#define SCCP_MIN_API_FROM_TC            (SCCP_MIN_API) /* 166 */
#define SCCP_MAX_NUMBER_API_FROM_TC     (15)

#define SCCP_REGISTER_USER              (SCCP_MIN_API_FROM_TC + 0)
#define SCCP_N_UNITDATA_REQUEST         (SCCP_MIN_API_FROM_TC + 1)
#define SCCP_N_STATE_REQUEST            (SCCP_MIN_API_FROM_TC + 2)
#define SCCP_N_COORD_REQUEST            (SCCP_MIN_API_FROM_TC + 3)
#define SCCP_N_COORD_RESPONSE            (SCCP_MIN_API_FROM_TC + 4)

#ifdef SCCP_INCLUDE_CO_SERVICE
/* SCCP connection oriented CLASS 2 and CLASS 3 service user API(NSU->NSP) */

/* SCCP_N_CONNECT_REQUEST not supported in ETSI */
#define SCCP_N_CONNECT_REQUEST          (SCCP_MIN_API_FROM_TC + 5)
#define SCCP_N_CONNECT_RESPONSE         (SCCP_MIN_API_FROM_TC + 6)
#define SCCP_N_CONNECT_REQUEST_TYPE1    (SCCP_MIN_API_FROM_TC + 7)
#define SCCP_N_CONNECT_REQUEST_TYPE2    (SCCP_MIN_API_FROM_TC + 8)
#define SCCP_N_DATA_REQUEST             (SCCP_MIN_API_FROM_TC + 9)
#define SCCP_N_DISCONNECT_REQUEST       (SCCP_MIN_API_FROM_TC + 10)
#define SCCP_N_INFORM_REQUEST           (SCCP_MIN_API_FROM_TC + 11)

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SCCP connection oriented APIs supported in CLASS 3 only */
#define SCCP_N_EXPEDIATE_DATA_REQUEST   (SCCP_MIN_API_FROM_TC + 12)
#define SCCP_N_RESET_REQUEST            (SCCP_MIN_API_FROM_TC + 13)
#define SCCP_N_RESET_RESPONSE           (SCCP_MIN_API_FROM_TC + 14)

#define SCCP_MAX_API_FROM_TC            SCCP_N_RESET_RESPONSE 
#else
#define SCCP_MAX_API_FROM_TC            SCCP_N_INFORM_REQUEST 
#endif  /* SCCP_INCLUDE_CO_CLASS3_SERVICE */

#else
#define SCCP_MAX_API_FROM_TC            SCCP_N_COORD_RESPONSE 
#endif  /* SCCP_INCLUDE_CO_SERVICE */


/** APIs invoked by SCCP, i.e. used in send_from_sccp API         **/

#define SCCP_MIN_API_TO_TC              (SCCP_MIN_API + \
                                         SCCP_MAX_NUMBER_API_FROM_TC) /* 179 */
#define SCCP_MAX_NUMBER_API_TO_TC       (15)

#define SCCP_N_UNITDATA_INDICATION      (SCCP_MIN_API_TO_TC + 0)
#define SCCP_N_NOTICE_INDICATION        (SCCP_MIN_API_TO_TC + 1)
#define SCCP_N_STATE_INDICATION         (SCCP_MIN_API_TO_TC + 2)
#define SCCP_N_COORD_INDICATION         (SCCP_MIN_API_TO_TC + 3)
#define SCCP_N_COORD_CONFIRM            (SCCP_MIN_API_TO_TC + 4)
#define SCCP_N_PCSTATE_INDICATION       (SCCP_MIN_API_TO_TC + 5)

#ifdef SCCP_INCLUDE_CO_SERVICE
/* SCCP connection oriented CLASS 2 and CLASS 3 service user API(NSP->NSU) */
#define SCCP_N_CONNECT_INDICATION       (SCCP_MIN_API_TO_TC + 6)
#define SCCP_N_CONNECT_CONFIRM          (SCCP_MIN_API_TO_TC + 7)
#define SCCP_N_CONNECT_REPLY            (SCCP_MIN_API_TO_TC + 8)
#define SCCP_N_DATA_INDICATION          (SCCP_MIN_API_TO_TC + 9)
#define SCCP_N_DISCONNECT_INDICATION    (SCCP_MIN_API_TO_TC + 10)
#define SCCP_N_INFORM_INDICATION        (SCCP_MIN_API_TO_TC + 11)

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
#define SCCP_N_EXPEDIATE_DATA_INDICATION  (SCCP_MIN_API_TO_TC + 12)
#define SCCP_N_RESET_INDICATION           (SCCP_MIN_API_TO_TC + 13)
#define SCCP_N_RESET_CONFIRM              (SCCP_MIN_API_TO_TC + 14)

#define SCCP_MAX_API_TO_TC                SCCP_N_RESET_CONFIRM 
#else
#define SCCP_MAX_API_TO_TC                SCCP_N_INFORM_INDICATION
#endif  /* SCCP_INCLUDE_CO_CLASS3_SERVICE*/
#else
#define SCCP_MAX_API_TO_TC                SCCP_N_PCSTATE_INDICATION
#endif

/**     APIs for communicating with system management */
#define SCCP_MIN_API_SM                   (SCCP_MIN_API + \
                                          SCCP_MAX_NUMBER_API_FROM_TC + \
                                          SCCP_MAX_NUMBER_API_TO_TC) /* 192 */
#define SCCP_SM_REQUEST_API               (SCCP_MIN_API_SM + 0)
#define SCCP_SM_RESPONSE_API              (SCCP_MIN_API_SM + 1)



#else /** else of ifdef BACK_UP_SSN**/



#define SCCP_MIN_API_FROM_TC            (SCCP_MIN_API) /* 166 */
#define SCCP_MAX_NUMBER_API_FROM_TC     (13)

#define SCCP_REGISTER_USER              (SCCP_MIN_API_FROM_TC + 0)
#define SCCP_N_UNITDATA_REQUEST         (SCCP_MIN_API_FROM_TC + 1)
#define SCCP_N_STATE_REQUEST            (SCCP_MIN_API_FROM_TC + 2)

#ifdef SCCP_INCLUDE_CO_SERVICE
/* SCCP connection oriented CLASS 2 and CLASS 3 service user API(NSU->NSP) */

/* SCCP_N_CONNECT_REQUEST not supported in ETSI */
#define SCCP_N_CONNECT_REQUEST          (SCCP_MIN_API_FROM_TC + 3)
#define SCCP_N_CONNECT_RESPONSE         (SCCP_MIN_API_FROM_TC + 4)
#define SCCP_N_CONNECT_REQUEST_TYPE1    (SCCP_MIN_API_FROM_TC + 5)
#define SCCP_N_CONNECT_REQUEST_TYPE2    (SCCP_MIN_API_FROM_TC + 6)
#define SCCP_N_DATA_REQUEST             (SCCP_MIN_API_FROM_TC + 7)
#define SCCP_N_DISCONNECT_REQUEST       (SCCP_MIN_API_FROM_TC + 8)
#define SCCP_N_INFORM_REQUEST           (SCCP_MIN_API_FROM_TC + 9)

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
/* SCCP connection oriented APIs supported in CLASS 3 only */
#define SCCP_N_EXPEDIATE_DATA_REQUEST   (SCCP_MIN_API_FROM_TC + 10)
#define SCCP_N_RESET_REQUEST            (SCCP_MIN_API_FROM_TC + 11)
#define SCCP_N_RESET_RESPONSE           (SCCP_MIN_API_FROM_TC + 12)

#define SCCP_MAX_API_FROM_TC            SCCP_N_RESET_RESPONSE
#else
#define SCCP_MAX_API_FROM_TC            SCCP_N_INFORM_REQUEST
#endif  /* SCCP_INCLUDE_CO_CLASS3_SERVICE */

#else
#define SCCP_MAX_API_FROM_TC            SCCP_N_STATE_REQUEST
#endif  /* SCCP_INCLUDE_CO_SERVICE */

#define SCCP_MIN_API_TO_TC              (SCCP_MIN_API + \
                                         SCCP_MAX_NUMBER_API_FROM_TC) /* 179 */
#define SCCP_MAX_NUMBER_API_TO_TC       (13)

#define SCCP_N_UNITDATA_INDICATION      (SCCP_MIN_API_TO_TC + 0)
#define SCCP_N_NOTICE_INDICATION        (SCCP_MIN_API_TO_TC + 1)
#define SCCP_N_STATE_INDICATION         (SCCP_MIN_API_TO_TC + 2)
#define SCCP_N_PCSTATE_INDICATION       (SCCP_MIN_API_TO_TC + 3)

#ifdef SCCP_INCLUDE_CO_SERVICE
/* SCCP connection oriented CLASS 2 and CLASS 3 service user API(NSP->NSU) */
#define SCCP_N_CONNECT_INDICATION       (SCCP_MIN_API_TO_TC + 4)
#define SCCP_N_CONNECT_CONFIRM          (SCCP_MIN_API_TO_TC + 5)
#define SCCP_N_CONNECT_REPLY            (SCCP_MIN_API_TO_TC + 6)
#define SCCP_N_DATA_INDICATION          (SCCP_MIN_API_TO_TC + 7)
#define SCCP_N_DISCONNECT_INDICATION    (SCCP_MIN_API_TO_TC + 8)
#define SCCP_N_INFORM_INDICATION        (SCCP_MIN_API_TO_TC + 9)

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
#define SCCP_N_EXPEDIATE_DATA_INDICATION  (SCCP_MIN_API_TO_TC + 10)
#define SCCP_N_RESET_INDICATION           (SCCP_MIN_API_TO_TC + 11)
#define SCCP_N_RESET_CONFIRM              (SCCP_MIN_API_TO_TC + 12)

#define SCCP_MAX_API_TO_TC                SCCP_N_RESET_CONFIRM
#else
#define SCCP_MAX_API_TO_TC                SCCP_N_INFORM_INDICATION
#endif  /* SCCP_INCLUDE_CO_CLASS3_SERVICE*/
#else
#define SCCP_MAX_API_TO_TC                SCCP_N_PCSTATE_INDICATION
#endif

/**     APIs for communicating with system management */
#define SCCP_MIN_API_SM                   (SCCP_MIN_API + \
                                          SCCP_MAX_NUMBER_API_FROM_TC + \
                                          SCCP_MAX_NUMBER_API_TO_TC) /* 192 */
#define SCCP_SM_REQUEST_API               (SCCP_MIN_API_SM + 0)
#define SCCP_SM_RESPONSE_API              (SCCP_MIN_API_SM + 1)
#endif /** End of ifdef BACK_UP_SSN **/


/**     API related definitions                       **/

/** Values for parameters ID in the APIs to/from SCCP to TCAP **/

#define SCCP_ELEM_AFFECTED_SIGNALLING_POINT        0x01
#define SCCP_ELEM_AFFECTED_SUBSYSTEM               0x02
#define SCCP_ELEM_CALLED_ADDR                      0x03   /* CL, CO APIs */
#define SCCP_ELEM_CALLING_ADDR                     0x04   /* CL, CO APIs */
#define SCCP_ELEM_LOG_USER_ID                      0x06   /* CL, CO APIs */
#define SCCP_ELEM_REASON_FOR_RETURN                0x07
#define SCCP_ELEM_SSN                              0x0d
#define SCCP_ELEM_USER_DATA                        0x0f   /* CL, CO APIs */
#define SCCP_ELEM_USER_STATUS                      0x10
#define SCCP_ELEM_IMPORTANCE                       0x12   /* CL, CO APIs */
#define SCCP_ELEM_REMOTE_SCCP_STATUS               0x20
#define SCCP_ELEM_RESTR_IMPORTANCE_LEVEL           0x21
#define SCCP_ELEM_RETURN_OPTION                    0x22
#define SCCP_ELEM_SEQUENCE_CONTROL                 0x23
#define SCCP_ELEM_STATUS                           0x24
#define SCCP_ELEM_SUBSYSTEM_MULT_IND               0x25
#define SCCP_ELEM_ISNI                             0x26
#define SCCP_ELEM_CORR_ID                          0x30    /* CO APIs */
#define SCCP_ELEM_CREDIT                           0x31    /* CO APIs */
#define SCCP_ELEM_EXPEDIATE_DATA_SELECTION         0x32    /* CO APIs */
#define SCCP_ELEM_RESPONDING_ADDR                  0x33    /* CO APIs */
#define SCCP_ELEM_RPLY_REQ_INDICATOR               0x34    /* CO APIs */
#define SCCP_ELEM_REFUSAL_REASON                   0x35    /* CO APIs */
#define SCCP_ELEM_PROTOCOL_CLASS                   0x36    /* CO APIs */
#define SCCP_ELEM_CONNECTION_ID                    0x37    /* CO APIs */
#define SCCP_ELEM_OPC                              0x38    /* CO APIs */
#define SCCP_ELEM_SLR_NUMBER                       0x39    /* CO APIs */
#define SCCP_ELEM_RESET_REASON                     0x3a    /* CO APIs */
#define SCCP_ELEM_DISCONNECT_REASON                0x3b    /* CO APIs */
#define SCCP_ELEM_INF_REASON                       0x3c    /* CO APIs */
#define SCCP_ELEM_LOG_USER_ID_O                    0x3d    /* CO APIs */
#define SCCP_ELEM_NETWORK_NAME                 		0x3e    /* CO APIs */


/**   Lenghth of the API elements                            **/

#define SCCP_ELEM_ID_LEN                    0x1
#define SCCP_ELEM_LEN_LEN                   0x2
#define SCCP_ELEM_ANSI_AFFECTED_SP_LEN               0x3
#define SCCP_ELEM_ITU_ETSI_AFFECTED_SP_LEN           0x2
#define SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN        0x4
#define SCCP_ELEM_ITU_ETSI_AFFECTED_SUBSYSTEM_LEN    0x3
#define SCCP_ELEM_IMPORTANCE_LEN            0x1
#define SCCP_ELEM_LOG_USER_ID_LEN           0x2
#define SCCP_ELEM_REASON_FOR_RETURN_LEN     0x1
#define SCCP_ELEM_REMOTE_SCCP_STATUS_LEN    0x1
#define SCCP_ELEM_RESTR_IMP_LEVEL_LEN       0x1
#define SCCP_ELEM_RETURN_OPTION_LEN         0x1
#define SCCP_ELEM_SEQ_CONTROL_LEN           0x1
#define SCCP_ELEM_SIG_POINT_STATUS_LEN      0x1
#define SCCP_ELEM_MULTIPLICITY_IND_LEN      0x1
#define SCCP_ELEM_USER_STATUS_LEN           0x1
#ifdef SCCP_CONNECTION_ID_CHANGES
#define SCCP_ELEM_CORR_ID_LEN               0x4 /*Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
#define SCCP_ELEM_CORR_ID_LEN               0x1
#endif
#define SCCP_ELEM_CREDIT_LEN                0x1
#define SCCP_ELEM_PROTOCOL_CLASS_LEN        0x1
#ifdef SCCP_CONNECTION_ID_CHANGES
#define SCCP_ELEM_CONNECTION_ID_LEN         0x4
#else
#define SCCP_ELEM_CONNECTION_ID_LEN         0x2
#endif
#define SCCP_ELEM_ANSI_POINT_CODE_LEN       0x3
#define SCCP_ELEM_ITU_ETSI_POINT_CODE_LEN   0x2
#define SCCP_ELEM_LOCAL_REF_LEN             0x3
#define SCCP_ELEM_RESET_CAUSE_LEN           0x1
#define SCCP_ELEM_REFUSAL_CAUSE_LEN         0x1
#define SCCP_ELEM_DISC_ORG_LEN              0x1
#define SCCP_ELEM_INF_REASON_LEN            0x1
#define SCCP_ELEM_REASON_FOR_RESET_LEN      0x1
#define SCCP_ELEM_RESET_ORG_LEN             0x1
#define SCCP_ELEM_SUBSYSTEM_LEN             0x1
/* SPR 12500 FIX Start */
#define SCCP_MAN_ELEM_DATA_MIN_LEN          0x1
/* SPR 12500 FIX End */



/**  lengths and min/max num elems in various apis */
#define SCCP_N_CONNECT_REQUEST_MIN_LEN (SCCP_ELEM_LOG_USER_ID_LEN + \
                                        SCCP_ELEM_CORR_ID_LEN + \
                                        SCCP_ELEM_PROTOCOL_CLASS_LEN) 
                                        
/* SPR # 4585 Fix Start */
/* Replaced SCCP_ELEM_CORR_ID_LEN with SCCP_ELEM_CONNECTION_ID_LEN */
#define SCCP_N_CONNECT_RESPONSE_MIN_LEN (SCCP_ELEM_LOG_USER_ID_LEN + \
                                         SCCP_ELEM_CONNECTION_ID_LEN + \
                                         SCCP_ELEM_PROTOCOL_CLASS_LEN) 
/* SPR # 4585 Fix End */

#define SCCP_N_CONNECT_REQUEST_TYPE1_MIN_LEN (SCCP_ELEM_LOG_USER_ID_LEN + \
                                              SCCP_ELEM_CORR_ID_LEN + \
                                              SCCP_ELEM_PROTOCOL_CLASS_LEN) 

#define SCCP_N_CONNECT_REQUEST_TYPE2_MIN_LEN (SCCP_ELEM_LOG_USER_ID_LEN + \
                                              SCCP_ELEM_CORR_ID_LEN + \
                                              SCCP_ELEM_PROTOCOL_CLASS_LEN + \
                                              SCCP_ELEM_ITU_ETSI_POINT_CODE_LEN + \
                                              SCCP_ELEM_LOCAL_REF_LEN) 

#define SCCP_N_DISCONNECT_REQUEST_MIN_LEN (SCCP_ELEM_CONNECTION_ID_LEN  + \
                                            SCCP_ELEM_REFUSAL_CAUSE_LEN ) 
        /* SPR 12500 FIX Start */
#define SCCP_N_DATA_REQUEST_MIN_LEN   ((SCCP_ELEM_CONNECTION_ID_LEN) + \
                                        SCCP_MAN_ELEM_DATA_MIN_LEN)
        /* SPR 12500 FIX End */


#define SCCP_N_ED_REQUEST_MIN_LEN     (SCCP_ELEM_CONNECTION_ID_LEN)

#define SCCP_N_RESET_REQUEST_LEN      (SCCP_ELEM_CONNECTION_ID_LEN + \
                                       SCCP_ELEM_RESET_CAUSE_LEN)

#define SCCP_N_RESET_RESPONSE_LEN     (SCCP_ELEM_CONNECTION_ID_LEN)

#define SCCP_N_INFORM_REQUEST_MIN_LEN (SCCP_ELEM_CONNECTION_ID_LEN + \
                                       SCCP_ELEM_INF_REASON_LEN)

#define SCCP_ANSI_N_STATE_REQ_LEN   (SS7_API_HEADER_LEN + \
                                    SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN + \
                                    SCCP_ELEM_USER_STATUS_LEN)

#define SCCP_ITU_ETSI_N_STATE_REQ_LEN (SS7_API_HEADER_LEN + \
                                   SCCP_ELEM_ITU_ETSI_AFFECTED_SUBSYSTEM_LEN + \
                                   SCCP_ELEM_USER_STATUS_LEN)

#define SCCP_N_STATE_REQ_NELEM     2

#define SCCP_ANSI_N_STATE_IND_LEN   (SS7_API_HEADER_LEN + \
                                    SCCP_ELEM_SUBSYSTEM_LEN + \
                                    SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN + \
                                    SCCP_ELEM_USER_STATUS_LEN)

#define SCCP_ITU_ETSI_N_STATE_IND_LEN (SS7_API_HEADER_LEN + \
                                   SCCP_ELEM_SUBSYSTEM_LEN + \
                                   SCCP_ELEM_ITU_ETSI_AFFECTED_SUBSYSTEM_LEN + \
                                   SCCP_ELEM_USER_STATUS_LEN)

#define SCCP_N_COORD_IND_LEN (SS7_API_HEADER_LEN + \
                                   SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN + 1)
#define SCCP_N_COORD_CONFIRM_LEN (SS7_API_HEADER_LEN + \
                                   SCCP_ELEM_ANSI_AFFECTED_SUBSYSTEM_LEN + 1)
#define SCCP_N_STATE_IND_NELEM     3

#define SCCP_ANSI_N_PCSTATE_IND_MIN_LEN  (SS7_API_HEADER_LEN + \
                                     SCCP_ELEM_SUBSYSTEM_LEN + \
                                     SCCP_ELEM_ANSI_AFFECTED_SP_LEN + \
                                     SCCP_ELEM_SIG_POINT_STATUS_LEN)

#define SCCP_ITU_ETSI_N_PCSTATE_IND_MIN_LEN  (SS7_API_HEADER_LEN + \
                                     SCCP_ELEM_SUBSYSTEM_LEN + \
                                     SCCP_ELEM_ITU_ETSI_AFFECTED_SP_LEN + \
                                     SCCP_ELEM_SIG_POINT_STATUS_LEN)

#define SCCP_ANSI_N_PCSTATE_IND_MAX_LEN  (SS7_API_HEADER_LEN + \
                                     SCCP_ELEM_SUBSYSTEM_LEN + \
                                     SCCP_ELEM_ANSI_AFFECTED_SP_LEN + \
                                     SCCP_ELEM_SIG_POINT_STATUS_LEN + \
           /* optional elem */       SCCP_ELEM_ID_LEN + \
                                     SCCP_ELEM_LEN_LEN + \
                                     SCCP_ELEM_REMOTE_SCCP_STATUS_LEN + \
                                     SCCP_ELEM_ID_LEN + \
                                     SCCP_ELEM_LEN_LEN + \
                                     SCCP_ELEM_RESTR_IMP_LEVEL_LEN)

#define SCCP_ITU_ETSI_N_PCSTATE_IND_MAX_LEN  (SS7_API_HEADER_LEN + \
                                     SCCP_ELEM_SUBSYSTEM_LEN + \
                                     SCCP_ELEM_ITU_ETSI_AFFECTED_SP_LEN + \
                                     SCCP_ELEM_SIG_POINT_STATUS_LEN + \
           /* optional elem */       SCCP_ELEM_ID_LEN + \
                                     SCCP_ELEM_LEN_LEN + \
                                     SCCP_ELEM_REMOTE_SCCP_STATUS_LEN + \
                                     SCCP_ELEM_ID_LEN + \
                                     SCCP_ELEM_LEN_LEN + \
                                     SCCP_ELEM_RESTR_IMP_LEVEL_LEN)

#define SCCP_N_PCSTATE_IND_MIN_NELEM     3
#define SCCP_N_PCSTATE_IND_MAX_NELEM     5

#define SCCP_N_UNITDATA_REQ_MIN_NELEM    3
#define SCCP_N_UNITDATA_REQ_MAX_NELEM    6

#define SCCP_N_UNITDATA_IND_MIN_NELEM    3
#define SCCP_N_UNITDATA_IND_MAX_NELEM    6

#define SCCP_N_NOTICE_IND_MIN_NELEM      4
#define SCCP_N_NOTICE_IND_MAX_NELEM      5

#define SCCP_N_CONNECT_IND_MIN_NELEM     3
#define SCCP_N_CONNECT_CONF_MIN_NELEM    3
#define SCCP_N_CONNECT_REPLY_MIN_NELEM   4
#define SCCP_N_DATA_IND_MIN_NELEM        2
#define SCCP_N_ED_DATA_IND_NELEM         2
#define SCCP_N_RESET_IND_NELEM           3
#define SCCP_N_RESET_CONF_NELEM          1
#define SCCP_N_DISCONNECT_IND_NELEM      3

/* possible values for the element:SCCP_ELEM_REMOTE_SCCP_STATUS */
#define SCCP_REMOTE_SCCP_AVAILABLE                 0x1
#define SCCP_REMOTE_SCCP_UNAVAILABLE               0x2    
#define SCCP_REMOTE_SCCP_UNEQUIPPED                0x3
#define SCCP_REMOTE_SCCP_INACCESIBLE               0x4 
#define SCCP_REMOTE_SCCP_CONGESTED                 0x5

/* possible values for the element:SCCP_RETURN_OPTION */
#define SCCP_DISCARD_MSG                           0x0 
#define SCCP_RETURN_MSG                            0x1 

/* possible values for the element:SCCP_SIGNALLING_POINT_STATUS */
#define SP_INACCESSIBLE                            0x1
#define SP_CONGESTED                               0x2 
#define SP_ACCESSIBLE                              0x3

/* possible values for the element:SCCP_USER_STATUS */ 
#define SCCP_USER_IN_SERVICE                       0x0
#define SCCP_USER_OUT_OF_SERVICE                   0x1 

/* Reset/Relase originators */
#define SCCP_NETWORK_SERVICE_USER                  0x00
#define SCCP_NETWORK_SERVICE_PROVIDER              0x01
#define SCCP_ORIGINATOR_UNDEFINED                  0xFF


/** End of SCCP api related definitions **/

/********************NEW SCCP API IDs************************************************
**
**  New APIs used by SCCP
**
******************************************************************************/
#define SCCP_DEREGISTER_USER 254

/********************Extended API IDs*****************************************
**
**  APIs Extended 
**
******************************************************************************/

/* Extended APIs */
/* Note here that for extended API we'll be reading two more byte 
   which will contain one more ID */
#define SS7_EXTENDED_API    255

#define SCCP_DEREGISTER_INDICATION		20000
#define SCCP_DMR_INIT					20001
#define SCCP_DMR_DEINIT					20001
#define	SCCP_UMR_INIT					20001
#define SCCP_UMR_DEINIT					20001

/* SPR 9284 fix ends */

#ifdef LOGGER_IMR
#define BS_Dump(buffer, no_of_octets) \
   { \
      PRINT_HEX_DUMP(DEBUG,buffer,no_of_octets); \
   }
#endif


#endif /* _S7_API_H_       -- This MUST appear after all code! */



