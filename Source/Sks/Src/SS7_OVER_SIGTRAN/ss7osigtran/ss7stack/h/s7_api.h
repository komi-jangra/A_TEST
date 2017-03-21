/***************************************************************************
**  FUNCTION:
**      common file for API ids across stack entities
**
****************************************************************************
**
**  FILE NAME:
**      s7_api.h
**
**  DESCRIPTION:
**      Gives the range of each stack entities API IDs along with each API IDs values
**
**      DATE     NAME              REF#    REASON
**      -------  ----------------  -----   --------------------------------
**      10Dec97  vlakshmi          -----   Original 
**      15Jan98  smahajan          -----   added isup apis  
**      25Jun98  tgupta            -----   added TCAP SM API #defines
**  08Aug98  Anil K.           -----   ISNI element added for SCCP cl-ANSI
**  19Aug98  Anil K./P khare   -----   SCCP connection oriented APIs added.
**      26Jan00  Dinesh Kori       -----   SPR 2503
**      26Oct00  Arun Kumar    -----   Adding TRAFFIC Statistics
**      22NOv00  Hemlata Baudhwar  SPR #4585 Replaced SCCP_ELEM_CORR_ID_LEN with  
**                                           SCCP_ELEM_CONNECTION_ID_LEN in macro 
**                                           SCCP_N_CONNECT_RESPONSE_MIN_LEN
**      24Jan01 V Nagpal           BISUP : Add APIs for BISUP.
**                                 Since, we dont have much API ID
**                                 space left, we will let BISUP API
**                                 IDs coincide with ISUP API IDs. 
**      04Apr01  aspathak          -----   SPR 5286
**      24May01  ramehta          Increased SCCP_ELEM_CONNECTION_ID_LEN to 4
**                                and SCCP_ELEM_CORR_ID_LEN to 2 in case flag
**                                SCCP_CONNECTION_ID_CHANGES is defined  
      1 June 2001 Pkmodi        SCCP and TCAP Chinese changes
      27Dec2001 Prateek B.       Added DSCCP_UPDATE_API api
      27Jan2002 Pawanish       Added DTCAP_COMMON_API api
      06Feb2002 Sachin Bhatia  Added DEREG API and EXTENDED API
**		29Oct2002 vibatra	SPR 10359	Added TCAP_TC_TIMER_RESET API for 
**										TCAP JAPANESE variant.
**		29Oct2002 vibatra   SPR 10358   Added TCAP_TC_TIMER_RESET API for 
**										TCAP ITU 97 variant.
**		12Feb2003 Pawanish Modi     	Added optional parameter 
**								SCCP_ELEM_NETWORK_NAME 
**              21Oct2003 Ganesh Kumar          SPR 12500
**              08Apr2004 Hitesh Sharma         SPR 13344
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _S7_API_H_     /* If this file has not been processed, */
#define _S7_API_H_     /* define it as seen--ref '#endif' below. */

#ifndef SIGTRAN_SCM_IF
#define SIGTRAN_SCM_IF
#endif
/* api header length */
/* to be used to calculate API buffer length */
#define SS7_API_HEADER_LEN      5
/* Added by Amaresh start as on dated 08-02-16*/
#define SS7_CARD_STATE_ACTIVE   1
#define SS7_CARD_STATE_STANDBY  0
#define BPM_INVAID_STATE        50
#define SCTP_DATA_LEN           0xFFFF 
/* Added by Amaresh stop as on dated 08-02-16*/

/*
** This is the hashdefine for Timer API ID
*/
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


/********************ISUP API IDs************************************************
**
**  APIs invoked by call Control
**
******************************************************************************/


/* API IDS FROM CC TO ISUP */

#define ISUP_SETUP_REQ          (ISUP_MIN_API + 0x01)
#define ISUP_SETUP_RESP         (ISUP_MIN_API + 0x02)
#define ISUP_PROG_REQ           (ISUP_MIN_API + 0x03)
#define ISUP_ADDR_REQ           (ISUP_MIN_API + 0x04)
#define ISUP_SUSP_REQ           (ISUP_MIN_API + 0x05)
#define ISUP_RES_REQ            (ISUP_MIN_API + 0x06)
#define ISUP_REL_REQ            (ISUP_MIN_API + 0x07)
#define ISUP_REL_RESP           (ISUP_MIN_API + 0x08)
#define ISUP_RESET_REQ          (ISUP_MIN_API + 0x09)
#define ISUP_RESET_RESP         (ISUP_MIN_API + 0x0A)
#define ISUP_BLOCKING_REQ       (ISUP_MIN_API + 0x0B)
#define ISUP_BLOCKING_RESP      (ISUP_MIN_API + 0x0C)
#define ISUP_UNBLOCKING_REQ     (ISUP_MIN_API + 0x0D)
#define ISUP_UNBLOCKING_RESP        (ISUP_MIN_API + 0x0E)
#define ISUP_PAM_REQ            (ISUP_MIN_API + 0x0F)
#define ISUP_CKT_GROUP_QUERY_REQ    (ISUP_MIN_API + 0x10)
#define ISUP_COT_REQ            (ISUP_MIN_API + 0x11)
#define ISUP_CFN_REQ            (ISUP_MIN_API + 0x12)
#define ISUP_INFO_REQ           (ISUP_MIN_API + 0x13)
#define ISUP_INFO_RESP          (ISUP_MIN_API + 0x14)
#define ISUP_FACILITY_REQ       (ISUP_MIN_API + 0x15)
#define ISUP_FACILITY_RESP      (ISUP_MIN_API + 0x16)
#define ISUP_FAC_REQ            (ISUP_MIN_API + 0x17)
#define ISUP_FORWARD_TRANSFER_REQ   (ISUP_MIN_API + 0x18)
#define ISUP_OVERLOAD_REQ       (ISUP_MIN_API + 0x19)
#define ISUP_USER_INFO_REQ      (ISUP_MIN_API + 0x1A)
#define ISUP_NETWORK_RESOURCE_REQ   (ISUP_MIN_API + 0x1B)
#define ISUP_CHARGE_REQ         (ISUP_MIN_API + 0x1C)
#define ISUP_COT_CHECK_REQ      (ISUP_MIN_API + 0x1D)
#define ISUP_UNEQ_CIC_REQ       (ISUP_MIN_API + 0x1E)
#define ISUP_STOP_REQ           (ISUP_MIN_API + 0x1F)
#define ISUP_UNRECOGNIZED_MSG_REQ       (ISUP_MIN_API + 0x20)
#define ISUP_CIR_RES_REQ            (ISUP_MIN_API + 0x21)
#define ISUP_CIR_RES_RESP           (ISUP_MIN_API + 0x22)
#define ISUP_CIR_VALID_REQ          (ISUP_MIN_API + 0x23)
#define ISUP_CIR_VALID_RESP         (ISUP_MIN_API + 0x24)
#define ISUP_EXIT_REQ           (ISUP_MIN_API + 0x25)
#define ISUP_LOOP_ACK_REQ           (ISUP_MIN_API + 0x26)
#define ISUP_LLM_REQ                    (ISUP_MIN_API + 0x27)
#define ISUP_CCL_REQ                    (ISUP_MIN_API + 0x28)
#define ISUP_PREL_REQ           (ISUP_MIN_API + 0x29)
#define ISUP_IDR_REQ            (ISUP_MIN_API + 0x2A)
#define ISUP_IDR_RESP           (ISUP_MIN_API + 0x2B)

#define ISUP_MAX_CC_API_ID              ISUP_IDR_RESP

#define ISUP_CC_LAST_API_ID             ISUP_IDR_RESP - ISUP_MIN_API


/* API IDS FROM ISUP TO CC */

#define ISUP_SETUP_IND                  (ISUP_MAX_CC_API_ID + 0x01)
#define ISUP_SETUP_CONF                 (ISUP_MAX_CC_API_ID + 0x02)
#define ISUP_PROG_IND                   (ISUP_MAX_CC_API_ID + 0x03)
#define ISUP_ADDR_IND                   (ISUP_MAX_CC_API_ID + 0x04)
#define ISUP_SUSP_IND                   (ISUP_MAX_CC_API_ID + 0x05)
#define ISUP_RES_IND                    (ISUP_MAX_CC_API_ID + 0x06)
#define ISUP_REL_IND                    (ISUP_MAX_CC_API_ID + 0x07)
#define ISUP_REL_CONF                   (ISUP_MAX_CC_API_ID + 0x08)
#define ISUP_RESET_IND                  (ISUP_MAX_CC_API_ID + 0x09)
#define ISUP_RESET_CONF                 (ISUP_MAX_CC_API_ID + 0x0A)
#define ISUP_BLOCKING_IND               (ISUP_MAX_CC_API_ID + 0x0B)
#define ISUP_BLOCKING_CONF              (ISUP_MAX_CC_API_ID + 0x0C)
#define ISUP_UNBLOCKING_IND             (ISUP_MAX_CC_API_ID + 0x0D)
#define ISUP_UNBLOCKING_CONF            (ISUP_MAX_CC_API_ID + 0x0E)
#define ISUP_CKT_GROUP_QUERY_CONF       (ISUP_MAX_CC_API_ID + 0x0F)
#define ISUP_COT_IND                    (ISUP_MAX_CC_API_ID + 0x10)
#define ISUP_CFN_IND                    (ISUP_MAX_CC_API_ID + 0x11)
#define ISUP_INFO_IND                   (ISUP_MAX_CC_API_ID + 0x12)
#define ISUP_INFO_CONF                  (ISUP_MAX_CC_API_ID + 0x13)
#define ISUP_FACILITY_IND               (ISUP_MAX_CC_API_ID + 0x14)
#define ISUP_FACILITY_CONF              (ISUP_MAX_CC_API_ID + 0x15)
#define ISUP_FAC_IND                    (ISUP_MAX_CC_API_ID + 0x16)
#define ISUP_FORWARD_TRANSFER_IND       (ISUP_MAX_CC_API_ID + 0x17)
#define ISUP_OVERLOAD_IND               (ISUP_MAX_CC_API_ID + 0x18)
#define ISUP_USER_INFO_IND              (ISUP_MAX_CC_API_ID + 0x19)
#define ISUP_NETWORK_RESOURCE_IND       (ISUP_MAX_CC_API_ID + 0x1A)
#define ISUP_CHARGE_IND                 (ISUP_MAX_CC_API_ID + 0x1B)
#define ISUP_COT_PROC                   (ISUP_MAX_CC_API_ID + 0x1C)
#define ISUP_COT_LOOP                   (ISUP_MAX_CC_API_ID + 0x1D)
#define ISUP_COT_CHECK_IND              (ISUP_MAX_CC_API_ID + 0x1E)
#define ISUP_PAUSE_IND                  (ISUP_MAX_CC_API_ID + 0x1F)
#define ISUP_RESUME_IND                 (ISUP_MAX_CC_API_ID + 0x20)
#define ISUP_UNEQ_CIC_IND               (ISUP_MAX_CC_API_ID + 0x21)
#define ISUP_STATUS_IND                 (ISUP_MAX_CC_API_ID + 0x22)
#define ISUP_RETRY_INFO_IND             (ISUP_MAX_CC_API_ID + 0x23)
#define ISUP_MAINTENANCE_INFO_IND       (ISUP_MAX_CC_API_ID + 0x24)
#define ISUP_REATTEMPT_CALL             (ISUP_MAX_CC_API_ID + 0x25)
#define ISUP_CONNECT_CIRCUITS           (ISUP_MAX_CC_API_ID + 0x26)
#define ISUP_CONTROL_ECHO_DEVICE        (ISUP_MAX_CC_API_ID + 0x27)
#define ISUP_PAM_IND                    (ISUP_MAX_CC_API_ID + 0x28)
#define ISUP_CHANGE_TRF_BY_STEP         (ISUP_MAX_CC_API_ID + 0x29)
#define ISUP_UNRECOGNIZED_MSG_IND       (ISUP_MAX_CC_API_ID + 0x2A)
#define ISUP_CIR_RES_IND            (ISUP_MAX_CC_API_ID + 0x2B)
#define ISUP_CIR_RES_CONF           (ISUP_MAX_CC_API_ID + 0x2C)
#define ISUP_CIR_VALID_IND          (ISUP_MAX_CC_API_ID + 0x2D)
#define ISUP_CIR_VALID_CONF         (ISUP_MAX_CC_API_ID + 0x2E)
#define ISUP_EXIT_IND           (ISUP_MAX_CC_API_ID + 0x2F)
#define ISUP_LOOP_ACK_IND           (ISUP_MAX_CC_API_ID + 0x30)
#define ISUP_LLM_IND                    (ISUP_MAX_CC_API_ID + 0x31)
#define ISUP_CCL_IND                    (ISUP_MAX_CC_API_ID + 0x32)
#define ISUP_PREL_IND           (ISUP_MAX_CC_API_ID + 0x33)
#define ISUP_IDR_IND            (ISUP_MAX_CC_API_ID + 0x34)
#define ISUP_IDR_RESP_IND           (ISUP_MAX_CC_API_ID + 0x35)

#define ISUP_MAX_API_IDS                ISUP_IDR_RESP_IND 

/* ISUP System Management APIs */ 
#define ISUP_SM_REQUEST_API     ISUP_MAX_API - 1  
#define ISUP_SM_RESPONSE_API        ISUP_MAX_API - 2  


/* defines used for ISUP APIs  */

/* used for stop activity api */

#define STOP_BLO           0x01
#define STOP_UBL           0x02
#define STOP_CGB           0x03
#define STOP_CGU           0x04
#define STOP_GRS           0x05
#define STOP_CCR           0x06
#define STOP_REL           0x07
#define STOP_RSC           0x08
#define STOP_UP_AVL        0x09

/* used for reattempt APIs */
#define REATTEMPT_DUAL_SEIZURE             0x01
#define REATTEMPT_BLOCKED                  0x02
#define REATTEMPT_COT_FAIL                 0x03
#define REATTEMPT_RESET                    0x04
#define REATTEMPT_UNREASONABLE_MSG         0x05
#define REATTEMPT_UNEQUIPPED_CKT           0x06   /* SPR 2503 */
/* used by retry indication */
#define RETRY_BLO          0x01
#define RETRY_UBL          0x02
#define RETRY_CGB          0x03
#define RETRY_CGU          0x04
#define RETRY_GRS          0x05
#define RETRY_CCR          0x06
#define RETRY_UP_AVL       0x07
#define RETRY_REL          0x08
#define RETRY_RSC          0x09


/* used by status api indication */
#define UP_UNAVL           0x01
#define UP_AVL             0x02
#define UP_INACC           0x03
#define UP_UNEQUIP         0x04
#define DPC_CONGSETED      0x05

/* used for status field */
#define DPC_AVAILABLE            0x01
#define DPC_UNAVAILABLE         0x02

/* used in maint info ind */
#define MSG_SENT_TO_NW      0x01
#define MSG_RETRY       0x02
#define UNEXPECTED_MSG      0x03
#define UNEXPECTED_RANGE    0x04
#define MSG_RCVD            0x05  /* added by Dinesh for informing about */
                      /* receiption of few messages (BLO etc. */
                      /* from network */
#define MSG_RCVD_COT_FAIL   0x06  /* added by Suparna when a COT Fail is rcvd */
#define MSG_RCVD_COT_SUCCESS    0x07  /* added by Suparna when a COT Success is rcvd */
#define NO_ACK_FRM_NW       0x08  /* added by Suparna when secondary Timer
                    Expires  and no response is rcvd */



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


#ifdef SIGTRAN_SCM_IF

/* Added by Amaresh for SCM handelling for BSSAP/SCCP/M3UA/SCTP as on dated 11-12-2015 start */

#define M3UA_SM_REQUEST_API               (SCCP_SM_RESPONSE_API + 1) /* 194*/
#define M3UA_SM_RESPONSE_API              (SCCP_SM_RESPONSE_API + 2)

#define SCTP_SM_REQUEST_API               (SCCP_SM_RESPONSE_API + 3)
#define SCTP_SM_RESPONSE_API              (SCCP_SM_RESPONSE_API + 4)

#define BSSAP_SM_REQUEST_API               (SCCP_SM_RESPONSE_API + 5)
#define BSSAP_SM_RESPONSE_API              (SCCP_SM_RESPONSE_API + 6)
/* Added by Amaresh for SCM handelling for BSSAP/SCCP/M3UA/SCTP as on dated 11-12-2015 stop */
#endif

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
#ifdef SIGTRAN_SCM_IF

/* Added by Amaresh for SCM handelling for BSSAP/SCCP/M3UA/SCTP as on dated 11-12-2015 start */

#define M3UA_SM_REQUEST_API               (SCCP_SM_RESPONSE_API + 1) /* 194*/
#define M3UA_SM_RESPONSE_API              (SCCP_SM_RESPONSE_API + 2)

#define SCTP_SM_REQUEST_API               (SCCP_SM_RESPONSE_API + 3)
#define SCTP_SM_RESPONSE_API              (SCCP_SM_RESPONSE_API + 4)

#define BSSAP_SM_REQUEST_API               (SCCP_SM_RESPONSE_API + 5)
#define BSSAP_SM_RESPONSE_API              (SCCP_SM_RESPONSE_API + 6)
/* Added by Amaresh for SCM handelling for BSSAP/SCCP/M3UA/SCTP as on dated 11-12-2015 stop */
#endif
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
#define SCCP_ELEM_CORR_ID_LEN               0x4  /* Change by Amaresh as on dated 20-01-16 */
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

/********************TCAP API IDs************************************************
**
**  TCAP APIs 
**
******************************************************************************/
/* SERVICE USER API IDENTIFIERS: TC USER TO TCAP */

/* APIs common to ITU & ANSI */
#ifdef BACK_UP_SSN

#define TCAP_TC_REGISTER_TCUSER           (TCAP_MIN_API + 0x01)
#define TCAP_TC_UNI_REQUEST               (TCAP_MIN_API + 0x02)
#define TCAP_TC_U_ABORT_REQUEST           (TCAP_MIN_API + 0x03)
#define TCAP_TC_RESULT_L_REQUEST          (TCAP_MIN_API + 0x04)
#define TCAP_TC_RESULT_NL_REQUEST         (TCAP_MIN_API + 0x05)
#define TCAP_TC_U_ERROR_REQUEST           (TCAP_MIN_API + 0x06)
#define TCAP_TC_U_REJECT_REQUEST          (TCAP_MIN_API + 0x07)
#define TCAP_TC_U_CANCEL_REQUEST          (TCAP_MIN_API + 0x08)
#define TCAP_TC_N_STATE_REQUEST           (TCAP_MIN_API + 0x09)
#define TCAP_TC_N_COORD_REQUEST           (TCAP_MIN_API + 10)
#define TCAP_TC_N_COORD_RESPONSE           (TCAP_MIN_API + 11)
#ifdef TCAP_CHINESE
#define TCAP_TC_TIMER_RESET               (TCAP_MIN_API + 12)

/* APIs specific for ITU */
#define TCAP_ITU_REQ_API_BASE           ((TCAP_TC_TIMER_RESET)+1)
#else
#define TCAP_ITU_REQ_API_BASE           ((TCAP_TC_N_COORD_RESPONSE)+1)
#endif

#define TCAP_TC_BEGIN_REQUEST             (TCAP_ITU_REQ_API_BASE)
#define TCAP_TC_CONTINUE_REQUEST          ((TCAP_ITU_REQ_API_BASE)+1)
#define TCAP_TC_END_REQUEST              ((TCAP_ITU_REQ_API_BASE)+2)
#define TCAP_TC_INVOKE_REQUEST           ((TCAP_ITU_REQ_API_BASE)+3) 
/* 
******* APIs specific for ANSI 
*/
#define TCAP_ANSI_REQ_API_BASE           (TCAP_ITU_REQ_API_BASE)

#define TCAP_TC_ANSI_QWP_REQ            (TCAP_ANSI_REQ_API_BASE)
#define TCAP_TC_ANSI_QWOP_REQ           ((TCAP_ANSI_REQ_API_BASE)+1)
#define TCAP_TC_ANSI_CWP_REQ            ((TCAP_ANSI_REQ_API_BASE)+2)
#define TCAP_TC_ANSI_CWOP_REQ           ((TCAP_ANSI_REQ_API_BASE)+3)
#define TCAP_TC_ANSI_RESPONSE_REQ        ((TCAP_ANSI_REQ_API_BASE)+4)
#define TCAP_TC_ANSI_INVOKE_L_REQ        ((TCAP_ANSI_REQ_API_BASE)+5)
#define TCAP_TC_ANSI_INVOKE_NL_REQ        ((TCAP_ANSI_REQ_API_BASE)+6)

/* maximum APIs from Service User is set to 50 */
#define TCAP_MAX_CLIENT_API            ((TCAP_TC_ANSI_INVOKE_NL_REQ)-(TCAP_MIN_API))

/* SERVICE USER API IDENTIFIERS: TCAP TO TC USER */
/* APIs common to ITU & ANSI */
#define TCAP_IND_API_BASE              (TCAP_MIN_API+TCAP_MAX_CLIENT_API+1)

#define TCAP_TC_UNI_INDICATION           (TCAP_IND_API_BASE)
#define TCAP_TC_U_ABORT_INDICATION         (TCAP_IND_API_BASE+1)
#define TCAP_TC_RESULT_L_INDICATION        (TCAP_IND_API_BASE+2)
#define TCAP_TC_RESULT_NL_INDICATION         (TCAP_IND_API_BASE+3)
#define TCAP_TC_U_ERROR_INDICATION           (TCAP_IND_API_BASE+4)
#define TCAP_TC_U_REJECT_INDICATION         (TCAP_IND_API_BASE+5)
#define TCAP_TC_L_CANCEL_INDICATION          (TCAP_IND_API_BASE+6)
#define TCAP_TC_L_REJECT_INDICATION         (TCAP_IND_API_BASE+7)
#define TCAP_TC_R_REJECT_INDICATION         (TCAP_IND_API_BASE+8)
#define TCAP_TC_P_ABORT_INDICATION          (TCAP_IND_API_BASE+9)
#define TCAP_TC_N_STATE_INDICATION          (TCAP_TC_P_ABORT_INDICATION+1)

#define TCAP_TC_N_COORD_INDICATION          (TCAP_TC_N_STATE_INDICATION+1)
#define TCAP_TC_N_COORD_CONFIRM          (TCAP_TC_N_COORD_INDICATION+1)
#define TCAP_TC_N_PCSTATE_INDICATION        (TCAP_TC_N_COORD_CONFIRM+1)
#define TCAP_TC_NOTICE_INDICATION          (TCAP_TC_N_PCSTATE_INDICATION+1) 
/* APIs for ITU */
#define TCAP_ITU_IND_API_BASE               (TCAP_TC_NOTICE_INDICATION+1)

#define TCAP_TC_BEGIN_INDICATION        (TCAP_ITU_IND_API_BASE)
#define TCAP_TC_CONTINUE_INDICATION      (TCAP_ITU_IND_API_BASE+1)
#define TCAP_TC_END_INDICATION          (TCAP_ITU_IND_API_BASE+2)
#define TCAP_TC_INVOKE_INDICATION         (TCAP_ITU_IND_API_BASE+3) 
/*  APIs for ANSI */
#define TCAP_ANSI_IND_API_BASE          (TCAP_ITU_IND_API_BASE)

#define TCAP_TC_ANSI_QWP_IND            (TCAP_ANSI_IND_API_BASE)
#define TCAP_TC_ANSI_QWOP_IND           ((TCAP_ANSI_IND_API_BASE)+1)
#define TCAP_TC_ANSI_CWP_IND            ((TCAP_ANSI_IND_API_BASE)+2)
#define TCAP_TC_ANSI_CWOP_IND           ((TCAP_ANSI_IND_API_BASE)+3)
#define TCAP_TC_ANSI_RESPONSE_IND       ((TCAP_ANSI_IND_API_BASE)+4)
#define TCAP_TC_ANSI_INVOKE_L_IND       ((TCAP_ANSI_IND_API_BASE)+5)
#define TCAP_TC_ANSI_INVOKE_NL_IND      ((TCAP_ANSI_IND_API_BASE)+6)
/* maximum number of indication APIs from TCAP to TC-USER */
#define TCAP_MAX_IND_API                (TCAP_TC_ANSI_INVOKE_NL_IND)
/* SM APIs for TCAP */
#define TCAP_SM_API_BASE                (TCAP_MAX_IND_API+1)
#define TCAP_SM_REQUEST_API             (TCAP_SM_API_BASE)
#define TCAP_SM_RESPONSE_API            (TCAP_SM_API_BASE+1)

#define TCAP_SM_REQUEST_API_ID          TCAP_SM_REQUEST_API
#define TCAP_TC_DLG_ID_GEN_REQUEST        (TCAP_SM_API_BASE + 03)
#define TCAP_TC_DLG_ID_REL_REQUEST        (TCAP_SM_API_BASE + 04)
#define TCAP_TC_DLG_ID_GEN_RESPONSE          (TCAP_SM_API_BASE+05)


#else  /** else of BACK_UP_SSN **/

#define TCAP_TC_REGISTER_TCUSER           (TCAP_MIN_API + 0x01)
#define TCAP_TC_UNI_REQUEST               (TCAP_MIN_API + 0x02)
#define TCAP_TC_U_ABORT_REQUEST           (TCAP_MIN_API + 0x03)
#define TCAP_TC_RESULT_L_REQUEST          (TCAP_MIN_API + 0x04)
#define TCAP_TC_RESULT_NL_REQUEST         (TCAP_MIN_API + 0x05)
#define TCAP_TC_U_ERROR_REQUEST           (TCAP_MIN_API + 0x06)
#define TCAP_TC_U_REJECT_REQUEST          (TCAP_MIN_API + 0x07)
#define TCAP_TC_U_CANCEL_REQUEST          (TCAP_MIN_API + 0x08)
#define TCAP_TC_N_STATE_REQUEST           (TCAP_MIN_API + 0x09)

/* APIs specific for ITU */
#define TCAP_ITU_REQ_API_BASE           ((TCAP_TC_N_STATE_REQUEST)+1)

#define TCAP_TC_BEGIN_REQUEST             (TCAP_ITU_REQ_API_BASE)
#define TCAP_TC_CONTINUE_REQUEST          ((TCAP_ITU_REQ_API_BASE)+1)
#define TCAP_TC_END_REQUEST              ((TCAP_ITU_REQ_API_BASE)+2)
#define TCAP_TC_INVOKE_REQUEST           ((TCAP_ITU_REQ_API_BASE)+3)

/*	SPR 10359 Fix starts
	TCAP_TC_TIMER_RESET API is available for TCAP_JAPANESE
*/
/*  SPR 10358 Fix starts
	TCAP_TC_TIMER_RESET API is available for TCAP_ITU 97. Also added for the
	TCAP ETSI variant.
*/
#if	defined(TCAP_CHINESE) || defined(TCAP_ITU) || defined(TCAP_JAPANESE) || defined(TCAP_ETSI)
#define TCAP_TC_TIMER_RESET     ((TCAP_ITU_REQ_API_BASE)+4)
#endif
/*	SPR 10358 Fix ends	*/
/*	SPR 10359 Fix ends	*/

/*
******* APIs specific for ANSI
*/
#define TCAP_ANSI_REQ_API_BASE           (TCAP_ITU_REQ_API_BASE)

#define TCAP_TC_ANSI_QWP_REQ            (TCAP_ANSI_REQ_API_BASE)
#define TCAP_TC_ANSI_QWOP_REQ           ((TCAP_ANSI_REQ_API_BASE)+1)
#define TCAP_TC_ANSI_CWP_REQ            ((TCAP_ANSI_REQ_API_BASE)+2)
#define TCAP_TC_ANSI_CWOP_REQ           ((TCAP_ANSI_REQ_API_BASE)+3)
#define TCAP_TC_ANSI_RESPONSE_REQ        ((TCAP_ANSI_REQ_API_BASE)+4)
#define TCAP_TC_ANSI_INVOKE_L_REQ        ((TCAP_ANSI_REQ_API_BASE)+5)
#define TCAP_TC_ANSI_INVOKE_NL_REQ        ((TCAP_ANSI_REQ_API_BASE)+6)

/* maximum APIs from Service User is set to 50 */
#define TCAP_MAX_CLIENT_API            ((TCAP_TC_ANSI_INVOKE_NL_REQ)-(TCAP_MIN_API))

/* SERVICE USER API IDENTIFIERS: TCAP TO TC USER */
/* APIs common to ITU & ANSI */
#define TCAP_IND_API_BASE              (TCAP_MIN_API+TCAP_MAX_CLIENT_API+1)

#define TCAP_TC_UNI_INDICATION           (TCAP_IND_API_BASE)
#define TCAP_TC_U_ABORT_INDICATION         (TCAP_IND_API_BASE+1)
#define TCAP_TC_RESULT_L_INDICATION        (TCAP_IND_API_BASE+2)
#define TCAP_TC_RESULT_NL_INDICATION         (TCAP_IND_API_BASE+3)
#define TCAP_TC_U_ERROR_INDICATION           (TCAP_IND_API_BASE+4)
#define TCAP_TC_U_REJECT_INDICATION         (TCAP_IND_API_BASE+5)
#define TCAP_TC_L_CANCEL_INDICATION          (TCAP_IND_API_BASE+6)
#define TCAP_TC_L_REJECT_INDICATION         (TCAP_IND_API_BASE+7)
#define TCAP_TC_R_REJECT_INDICATION         (TCAP_IND_API_BASE+8)
#define TCAP_TC_P_ABORT_INDICATION          (TCAP_IND_API_BASE+9)
#define TCAP_TC_N_STATE_INDICATION          (TCAP_TC_P_ABORT_INDICATION+1)
#define TCAP_TC_N_PCSTATE_INDICATION        (TCAP_TC_N_STATE_INDICATION+1)
#define TCAP_TC_NOTICE_INDICATION          (TCAP_TC_N_PCSTATE_INDICATION+1)
/* APIs for ITU */
#define TCAP_ITU_IND_API_BASE               (TCAP_TC_NOTICE_INDICATION+1)

#define TCAP_TC_BEGIN_INDICATION        (TCAP_ITU_IND_API_BASE)
#define TCAP_TC_CONTINUE_INDICATION      (TCAP_ITU_IND_API_BASE+1)
#define TCAP_TC_END_INDICATION          (TCAP_ITU_IND_API_BASE+2)
#define TCAP_TC_INVOKE_INDICATION         (TCAP_ITU_IND_API_BASE+3)
/*  APIs for ANSI */
#define TCAP_ANSI_IND_API_BASE          (TCAP_ITU_IND_API_BASE)

#define TCAP_TC_ANSI_QWP_IND            (TCAP_ANSI_IND_API_BASE)
#define TCAP_TC_ANSI_QWOP_IND           ((TCAP_ANSI_IND_API_BASE)+1)
#define TCAP_TC_ANSI_CWP_IND            ((TCAP_ANSI_IND_API_BASE)+2)
#define TCAP_TC_ANSI_CWOP_IND           ((TCAP_ANSI_IND_API_BASE)+3)
#define TCAP_TC_ANSI_RESPONSE_IND       ((TCAP_ANSI_IND_API_BASE)+4)
#define TCAP_TC_ANSI_INVOKE_L_IND       ((TCAP_ANSI_IND_API_BASE)+5)
#define TCAP_TC_ANSI_INVOKE_NL_IND      ((TCAP_ANSI_IND_API_BASE)+6)
/* maximum number of indication APIs from TCAP to TC-USER */
#define TCAP_MAX_IND_API                (TCAP_TC_ANSI_INVOKE_NL_IND)
/* SM APIs for TCAP */
#define TCAP_SM_API_BASE                (TCAP_MAX_IND_API+1)
#define TCAP_SM_REQUEST_API             (TCAP_SM_API_BASE)
#define TCAP_SM_RESPONSE_API            (TCAP_SM_API_BASE+1)

#define TCAP_SM_REQUEST_API_ID          TCAP_SM_REQUEST_API
#define TCAP_TC_DLG_ID_GEN_REQUEST        (TCAP_SM_API_BASE + 03)
#define TCAP_TC_DLG_ID_REL_REQUEST        (TCAP_SM_API_BASE + 04)
#define TCAP_TC_DLG_ID_GEN_RESPONSE          (TCAP_SM_API_BASE+05)
#endif /** end of BACK_UP_SSN ***/

#ifdef DISTRIBUTED_TCAP
#define DTCAP_COMMON_API 250    
#endif





/* SYSTEM MANAGEMENT API defines */

#define TCAP_ENTITY                      5  
#define SYSMG_ENTITY                     6
#define TCAP_NELEMENTS_OFFSET            2
#define TCAP_LENGTH_OFFSET               3
#define TCAP_API_ID_OFFSET               0
#define TCAP_VER_ID_OFFSET               1
#define TCAP_SM_CATEGORY_OFFSET          5
#define TCAP_SM_COMMAND_OFFSET          (TCAP_SM_CATEGORY_OFFSET+1)
#define TCAP_SM_TRANS_ID_OFFSET         (TCAP_SM_COMMAND_OFFSET+1)


#define SS7_REQ_API_HEADER_LEN          (SS7_API_HEADER_LEN + 3)
#define SS7_RES_API_HEADER_LEN          (SS7_REQ_API_HEADER_LEN+1) 
/* one extra for command status */

#define TCAP_SM_STATS_TYPE_OFFSET       (SS7_REQ_API_HEADER_LEN)
#define TCAP_SM_CMD_STATUS_OFFSET       (SS7_RES_API_HEADER_LEN-1)
#define TCAP_SM_TCAP_INIT_STATS_ELEMS    4
#define TCAP_SM_TCAP_GET_STATS_ELEMS     5
#define TCAP_SM_TCAP_DISABLE_STATS_ELEMS 4
#define TCAP_SM_TCAP_ENABLE_STATS_ELEMS  TCAP_SM_TCAP_DISABLE_STATS_ELEMS

#define TCAP_SM_SUCC_RES_API_MIN_NELEMS  4
#define TCAP_SM_SUCC_RES_API_NELEMS      TCAP_SM_SUCC_RES_API_MIN_NELEMS 
#define TCAP_SM_FAIL_RES_API_NELEMS      5

#define TCAP_SM_GET_TRACE_LEVEL_NELEMS   4
#define TCAP_SM_SET_TRACE_LEVEL_NELEMS   5
#define TCAP_SM_GET_ERROR_LEVEL_NELEMS   4
#define TCAP_SM_SET_ERROR_LEVEL_NELEMS   5
 

#define TCAP_SM_SUCC_RES_API_LEN        (SS7_RES_API_HEADER_LEN)


#define TCAP_SM_FAIL_RES_API_LEN        (SS7_RES_API_HEADER_LEN+2)
/* 2 extra for ecode */


#define TCAP_SM_ECODE_OFFSET            (SS7_RES_API_HEADER_LEN)
#define TCAP_TC_USER_DEREGISTER     2


                                                     
#define SS7_SM_GET_ERROR_LEVEL           00                  
#define SS7_SM_SET_ERROR_LEVEL           01                  
#define TCAP_SM_TRACE_FLAG_OFFSET        8   
#define TCAP_SM_ERROR_FLAG_OFFSET        8  


#define TCAP_API_STATS_LEN               44
#define TCAP_Q752_STATS_LEN              36
#define TCAP_ERROR_STATS_LEN             16
#ifdef DISTRIBUTED_TCAP
#define TCAP_TRAFFIC_STATS_LEN           40 
#else
#define TCAP_TRAFFIC_STATS_LEN           28 /* SPR# 4543 */
#endif


/* SPR # 7530 Fix Start */
#ifdef DISTRIBUTED_SCCP
/* SPR # 7530 Fix End */
/********************DSCCP API IDs************************************************
**
**  APIs used by DSCCP
**
******************************************************************************/
#define DSCCP_MATE_API 252
/* SPR # 7450 Fix Start */
#define DSCCP_UPDATE_API 253
/* SPR # 7450 Fix End */

/* SPR # 7530 Fix Start */
#endif
/* SPR # 7530 Fix End */

/********************NEW SCCP API IDs************************************************
**
**  New APIs used by SCCP
**
******************************************************************************/
#define SCCP_DEREGISTER_USER 254

/********************BISUP API IDs************************************************
**
**  APIs used by BISUP
**
******************************************************************************/


/* APIs towards BISUP i.e. used in send_to_bisup */
/* API IDS FROM Exchange application process TO BISUP */

/* Mark the start of the ANF -> BISUP APIs */
#define BISUP_UP_START_API            BISUP_SETUP_REQ

#define BISUP_SETUP_REQ              (BISUP_MIN_API + 0x00)
#define BISUP_ADDRESS_COMPLETE_REQ   (BISUP_MIN_API + 0x01)
#define BISUP_INCOMING_RESOURCES_ACCEPTED_REQ (BISUP_MIN_API + 0x02)
#define BISUP_INCOMING_RESOURCES_REJECTED_REQ (BISUP_MIN_API + 0x03)
#define BISUP_SUBSEQUENT_ADDRESS_REQ          (BISUP_MIN_API + 0x04)
#define BISUP_RELEASE_REQ            (BISUP_MIN_API + 0x05)
#define BISUP_RELEASE_RSP            (BISUP_MIN_API + 0x06)
#define BISUP_ANSWER_REQ             (BISUP_MIN_API + 0x07)
#define BISUP_PROGRESS_REQ           (BISUP_MIN_API + 0x08)
#define BISUP_SUSPEND_REQ            (BISUP_MIN_API + 0x09)
#define BISUP_RESUME_REQ             (BISUP_MIN_API + 0x0a)
#define BISUP_FORWARD_TRANSFER_REQ   (BISUP_MIN_API + 0x0b)
#define BISUP_NETWORK_RESOURCE_MANAGEMENT_REQ  (BISUP_MIN_API + 0x0c)
#define BISUP_SEGMENT_REQ            (BISUP_MIN_API + 0x0d)
#define BISUP_BLOCK_RESOURCE_REQ     (BISUP_MIN_API + 0x0e)
#define BISUP_BLOCK_RESOURCE_RSP     (BISUP_MIN_API + 0x0f)
#define BISUP_UNBLOCK_RESOURCE_REQ   (BISUP_MIN_API + 0x10)
#define BISUP_UNBLOCK_RESOURCE_RSP   (BISUP_MIN_API + 0x11)
#define BISUP_RESET_RESOURCE_REQ     (BISUP_MIN_API + 0x12)
#define BISUP_RESET_RESOURCE_RSP      (BISUP_MIN_API + 0x13)
#define BISUP_USER_PART_AVAILABLE_REQ (BISUP_MIN_API + 0x14)
#define BISUP_USER_PART_AVAILABLE_RSP (BISUP_MIN_API + 0x15)
#define BISUP_CHECK_RESOURCE_BEGIN_REQ (BISUP_MIN_API + 0x16)
#define BISUP_CHECK_RESOURCE_BEGIN_RSP (BISUP_MIN_API + 0x17)
#define BISUP_CHECK_RESOURCE_END_REQ  (BISUP_MIN_API + 0x18)
#define BISUP_CHECK_RESOURCE_END_RSP  (BISUP_MIN_API + 0x19)
#define BISUP_UNRECOGNIZED_MESSAGE_TYPE_REQ (BISUP_MIN_API + 0x1a)
#define BISUP_USER_TO_USER_INFORMATION_REQ  (BISUP_MIN_API + 0x1b)
#define BISUP_CONFUSION_REQ           (BISUP_MIN_API + 0x1c)
#define BISUP_QUERY_SID_REQ             (BISUP_MIN_API + 0x1d)
#define BISUP_KILL_SID_REQ              (BISUP_MIN_API + 0x1e)
/* Mark the end of the ANF -> BISUP APIs */
#define BISUP_UP_STOP_API            BISUP_KILL_SID_REQ

#define BISUP_NUM_UP_APIS            (BISUP_UP_STOP_API - BISUP_UP_START_API + 1)
/* API ID from SME to BISUP */
#define BISUP_SM_REQUEST_API         (BISUP_MIN_API + BISUP_MAX_CLIENT_API - 1)


/* APIs from BISUP i.e. used in send_from_bisup */
#define BISUP_SEND_FROM_API_START    (BISUP_MIN_API + BISUP_MAX_CLIENT_API)
/* API IDS FROM BISUP to Exchange application process */
#define BISUP_SETUP_IND              (BISUP_SEND_FROM_API_START + 0x00)
#define BISUP_ADDRESS_COMPLETE_IND   (BISUP_SEND_FROM_API_START + 0x01)
#define BISUP_INCOMING_RESOURCES_ACCEPTED_IND (BISUP_SEND_FROM_API_START + 0x02)
#define BISUP_INCOMING_RESOURCES_REJECTED_IND (BISUP_SEND_FROM_API_START + 0x03)
#define BISUP_SUBSEQUENT_ADDRESS_IND (BISUP_SEND_FROM_API_START + 0x04)
#define BISUP_RELEASE_IND            (BISUP_SEND_FROM_API_START + 0x05)
#define BISUP_RELEASE_CNF            (BISUP_SEND_FROM_API_START + 0x06)
#define BISUP_ANSWER_IND             (BISUP_SEND_FROM_API_START + 0x07)
#define BISUP_PROGRESS_IND           (BISUP_SEND_FROM_API_START + 0x08)
#define BISUP_SUSPEND_IND            (BISUP_SEND_FROM_API_START + 0x09)
#define BISUP_RESUME_IND             (BISUP_SEND_FROM_API_START + 0x0a)
#define BISUP_FORWARD_TRANSFER_IND   (BISUP_SEND_FROM_API_START + 0x0b)
#define BISUP_NETWORK_RESOURCE_MANAGEMENT_IND  (BISUP_SEND_FROM_API_START + 0x0c)
#define BISUP_SEGMENT_IND            (BISUP_SEND_FROM_API_START + 0x0d)
#define BISUP_BLOCK_RESOURCE_IND     (BISUP_SEND_FROM_API_START + 0x0e)
#define BISUP_BLOCK_RESOURCE_CNF     (BISUP_SEND_FROM_API_START + 0x0f)
#define BISUP_UNBLOCK_RESOURCE_IND   (BISUP_SEND_FROM_API_START + 0x10)
#define BISUP_UNBLOCK_RESOURCE_CNF   (BISUP_SEND_FROM_API_START + 0x11)
#define BISUP_RESET_RESOURCE_IND     (BISUP_SEND_FROM_API_START + 0x12)
#define BISUP_RESET_RESOURCE_CNF      (BISUP_SEND_FROM_API_START + 0x13)
#define BISUP_USER_PART_AVAILABLE_IND (BISUP_SEND_FROM_API_START + 0x14)
#define BISUP_USER_PART_AVAILABLE_CNF (BISUP_SEND_FROM_API_START + 0x15)
#define BISUP_CHECK_RESOURCE_BEGIN_IND (BISUP_SEND_FROM_API_START + 0x16)
#define BISUP_CHECK_RESOURCE_BEGIN_CNF (BISUP_SEND_FROM_API_START + 0x17)
#define BISUP_CHECK_RESOURCE_END_IND  (BISUP_SEND_FROM_API_START + 0x18)
#define BISUP_CHECK_RESOURCE_END_CNF  (BISUP_SEND_FROM_API_START + 0x19)
#define BISUP_UNRECOGNIZED_MESSAGE_TYPE_IND (BISUP_SEND_FROM_API_START + 0x1a)
#define BISUP_USER_TO_USER_INFORMATION_IND  (BISUP_SEND_FROM_API_START + 0x1b)
#define BISUP_CONFUSION_IND           (BISUP_SEND_FROM_API_START + 0x1c)
#define BISUP_ERROR_IND           (BISUP_SEND_FROM_API_START + 0x1d)
#define BISUP_DSTN_UNAVAILABLE_IND (BISUP_SEND_FROM_API_START + 0x1e)
#define BISUP_DSTN_AVAILABLE_IND   (BISUP_SEND_FROM_API_START + 0x1f)
#define BISUP_REMOTE_STATUS_IND    (BISUP_SEND_FROM_API_START + 0x20)
#define BISUP_QUERY_SID_ANSWER     (BISUP_SEND_FROM_API_START + 0x21)

#define BISUP_SEND_FROM_API_STOP BISUP_QUERY_SID_ANSWER
#define BISUP_NUM_SEND_FROM_APIS (BISUP_SEND_FROM_API_STOP - BISUP_SEND_FROM_API_START + 1)

/* API ID from BISUP to SME */
#define BISUP_SM_RESPONSE_API         (BISUP_MAX_API)

/* start and stop of MTP3 APIs used by BISUP */
#define BISUP_MTP3_IND_START_API      (MTP3_UP_TRANSFER_INDICATION)
#define BISUP_MTP3_IND_STOP_API       (MTP3_UP_STATUS_INDICATION)

/********************Extended API IDs*****************************************
**
**  APIs Extended 
**
******************************************************************************/

/* Extended APIs */
/* Note here that for extended API we'll be reading two more byte 
   which will contain one more ID */
#define SS7_EXTENDED_API    255

/* SPR 9284 fix starts - added for DMR and UMR init and deinit APIs */
#define TCAP_MIN_EXTENDED_API   30000

#define TCAP_TC_DEREGISTER_IND  (TCAP_MIN_EXTENDED_API+0x00)
#define TCAP_TC_DMR_INIT_REQ    (TCAP_MIN_EXTENDED_API+0x01)
#define TCAP_TC_UMR_INIT_REQ    (TCAP_MIN_EXTENDED_API+0x02)
#define TCAP_TC_DMR_DEINIT_REQ  (TCAP_MIN_EXTENDED_API+0x03)
#define TCAP_TC_UMR_DEINIT_REQ  (TCAP_MIN_EXTENDED_API+0x04)

#define TCAP_MAX_EXTENDED_API   39999

#define SCCP_DEREGISTER_INDICATION		20000
#define SCCP_DMR_INIT					20001
#define SCCP_DMR_DEINIT					20001
#define	SCCP_UMR_INIT					20001
#define SCCP_UMR_DEINIT					20001

/* SPR 9284 fix ends */

#endif /* _S7_API_H_       -- This MUST appear after all code! */



