/***********************************File Header ***************************
  File Name        : oamscfg_hashdefs.h
Purpose          : This file contains hash defineis for CFG

Project          : BSC OAM
Subsystem        : Oams
Author           : Aricent Bangalore
CSCI ID          :
Version          :
 ************************************* End **********************************/

#ifndef _OAMCFG_HASHDEFS_H_
#define _OAMCFG_HASHDEFS_H_
/* hash define used in OAMCFG process */

#define CFG_TERMINATE_CODE             -1

#define OAMCFG_Q_PERM                  0777
#define LOG_FILE_NAME_SIZE             11
#define MAX_ERR_LOG_FL_SZ              1000

#define OAMCFG_ERR_LOG                 "oamcfg.log"

#define MSGTYP0                        0
#define MSGFLG0                        0
#define BCCH_CCCH_TYPE                 1
#define BCCH_CCCH_SDCCH_TYPE           2

/*Changes PCU R2.5 Aricent -- START*/
#define MAX_NUM_MCC_FR_TIMESLOTS       127
#define CFG_INVALID_E1                 0xFF;
#define CFG_INVALID_E1_TS              0xFF;
/*Changes PCU R2.5 Aricent -- END*/

/* cfg response recieved timeout */
#define CFG_OIL_RESP_TIMEOUT           5 /* in seconds */

/* Messages Instance */
#define INSTANCE1                      1 /* Ideal stat */
#define INSTANCE2                      2 /* Message sent to OIL */
#define INSTANCE3                      3 /* SIGALRM recieved for timeout of response message */
#define INSTANCE4                      4 /* Response recieved from OIL */

/* daoId of the history table */
#define HIST_DAO_ID                    123456789 /* to be associated */
#define HIST_BUFFER_SIZE               12

/* tsi PP-TS stream Id */
#define SELF_PP_STREAM_ID              0x00

/* UNIX error 
#define UNIXERR  -1 */

#define INVALID                        0xFF
#define FREE                           0

/* DB queries hash defines */
#define UPDATE_ID                      1
#define INSERT_ID                      2
#define GET_ID                         3
#define DELETE_ID                      4

#define LSB_BIT                        0x00000001
/* Hash define use for a particular tables */
/* Common hash define */
#define MAX_E1_TS                      32
#define MAX_T1_TS                      24
#define MAX_DATALINK_E1_LIST           4
#define MAX_DATALINK_TS_LIST           4

/* aifListTable */
#define MAX_AIF_E1_LIST                5
#define MAX_AIF_START_CIC_LIST         5
#define MAX_AIF_LAC_LIST               15
#define MAX_EIF_LAC_LIST               10
#define MAX_VLR_LAC_LIST               10
#define MAX_DEST_TRANSPORT_LIST        4
#define MAX_ZONE_CODE_LIST             5

/* transportListTable */
#define MAX_TRANSPORT_E1_LIST          4
#define MAX_TRANSPORT_START_CIC_LIST   4

/* Fail points or Panic points */
#define CFG_SUCCESS                    0
#define CFG_FAILURE                    1
#define CFG_ALLOC_FAIL                 2
#define CFG_MSGEGT_FAIL                3
#define CFG_REGD_IPC_FAIL              4
#define CFG_DB_INIT_FAIL               5
#define CFG_PUT_FAIL                   6
#define CFG_INSERT_FAIL                7
#define CFG_DELETE_FAIL                8
#define CFG_UPDATE_FAIL                9
#define CFG_SELECT_FAIL                10
#define CFG_MALLOC_FAIL                11
#define CFG_HIST_RECOVERY_FAIL         12
#define CFG_FILL_HIST_FAIL             13
#define CFG_MSGRCV_FAIL                14
#define CFG_DUMP_FAIL                  15
#define CFG_SEND_ALLOC_FAIL            16
#define CFG_SEND_FAIL                  17


#define   FALSE                        0
#define   TRUE                         1

#define    OAMS_CFG_LOCKED             LOCKED
#define    OAMS_CFG_UNLOCKED           UNLOCKED
#define    OAMS_CFG_SHUTDOWN           SHUTTING_DOWN
/*R2.4 Changes: Start*/
#define  BLOCK SHUTTING_DOWN
/*R2.4 Changes: Ends*/
#define SCM_CFG_RESP_TIMER             20
/***** SPR- Start ***/
#define SYSTEM_STARTUP_TIMER           20
#define BPM_STARTUP_TIMER              60 /* Timer to wait GET CARDINFO from BPM*/
/***** SPR- End ***/
#define MGS_RSP_TIMER                  5

#define TRAU_ID                        0
#define AINTERFACE_INDEX               0
#define RADIO_CLOCK_INDEX              0
#define TRAU_START_SIZE                0x08
#define DSP_INIT_SIZE                  0x0a
#define INVALID_BTS                    0xffffffff

typedef enum mgsWtForRsp
{
   MGS_NO_WAIT,
   MGS_WT_FOR_MGS_DSP_BOOT_TEST,
   MGS_WT_FOR_MGS_DSP_INIT_RESP,
   MGS_WT_FOR_MGS_TRAU_START_RESP,
}MgsWtForRsp;

//Changed alarm names
#define CELL_ENABLED                             ALARM_CELL_ENABLED
#define CELL_DISABLED                            ALARM_CELL_DISABLED
#define PSCELL_ENABLED                           ALARM_PSCELL_ENABLED
#define PSCELL_DISABLED                          ALARM_PSCELL_DISABLED
#define AINTERFACE_ENABLED                       ALARM_AINTERFACE_ENABLED
#define AINTERFACE_DISABLED                      ALARM_AINTERFACE_DISABLED
#define GBINTERFACE_ENABLED                      ALARM_GBINTERFACE_ENABLED
#define GBINTERFACE_DISABLED                     ALARM_GBINTERFACE_DISABLED   
#define NSVC_ENABLED                             ALARM_NSVC_ENABLED
#define NSVC_DISABLED                            ALARM_NSVC_DISABLED
#define FRLINK_ENABLED                           ALARM_FRLINK_ENABLED
#define FRLINK_DISABLED                          ALARM_FRLINK_DISABLED
#define E1_ENABLED                               ALARM_E1_ENABLED
#define E1_DISABLED                              ALARM_E1_DISABLED
#define TIMESLOT_ENABLED                         ALARM_TIMESLOT_ENABLED
#define TIMESLOT_DISABLED                        ALARM_TIMESLOT_DISABLED
#define PTRX_ENABLED                             ALARM_PTRX_ENABLED
#define PTRX_DISABLED                            ALARM_PTRX_DISABLED
#define	BSS_LOCKED                               ALARM_BSS_LOCKED
#define	BSS_UNLOCKED                             ALARM_BSS_UNLOCKED
#define	CELL_LOCKED                              ALARM_CELL_LOCKED
#define	CELL_UNLOCKED                            ALARM_CELL_UNLOCKED
#define	PTRX_LOCKED                              ALARM_PTRX_LOCKED
#define	PTRX_UNLOCKED                            ALARM_PTRX_UNLOCKED
#define	E1_LOCKED                                ALARM_E1_LOCKED
#define	E1_UNLOCKED                              ALARM_E1_UNLOCKED
#define	TIMESLOT_LOCKED                          ALARM_TIMESLOT_LOCKED
#define	TIMESLOT_UNLOCKED                        ALARM_TIMESLOT_UNLOCKED
#define	GBINTERFACE_INIT_FAILED                  EVENT_GBINTERFACE_INIT_FAILED
#define OPERATION_TIMEOUT                        EVENT_OPERATION_TIMEOUT
#define SET_BTS_ATTR_NACK                        EVENT_SET_BTS_ATTR_NACK
#define SET_CHAN_ATTR_NACK                       EVENT_SET_CHAN_ATTR_NACK
#define OP_START_NACK                            EVENT_OP_START_NACK
#define OP_STOP_NACK                             EVENT_OP_STOP_NACK
#define CLOCK_DISAPPEAR                          EVENT_CLOCK_DISAPPEAR
#define CLOCK_STABILIZED                         EVENT_CLOCK_STABILIZED   
#define TRAU_INITIALIZATION_FAILED               EVENT_TRAU_INITIALIZATION_FAILED
#define TSI_INITIALIZATION_FAILED                EVENT_TSI_INITIALIZATION_FAILED 
#define TSI_TRAU_INITIALIZATION_FAILED           EVENT_TSI_TRAU_INITIALIZATION_FAILED 
#define TRAU_DOWN_ALM                            ALARM_TRAU_DOWN
#define TRAU_UP_ALM                              ALARM_TRAU_UP

/* Change For CS2.2 : Start */
/* PhysicalTrxPreconfiguredTable is replaced by TrxTable in CS2.2 */
#define TIMESLOT_STATUS_FREE 	                 1
#define TIMESLOT_STATUS_BUSY 	                 2
#define CFG_MAX_NUM_TRX		                 MAX_NUM_TRX_PER_BSS
#define CFG_MAX_NUM_CELLS	                 MAX_NUM_CELL_PER_BSS

/*Changes PCU R2.5 Aricent -- START*/
#define OAMS_CFG_MAX_NUM_NSVCS                   MAX_NUM_NSVC_PER_BSS
/*Changes PCU R2.5 Aricent -- END*/
#define CFG_MAX_NUM_E1		                 59
#define CFG_MAX_NUM_EXT_E1	                 39
#define CFG_MIN_NUM_INT_E1                       51
#define CFG_MAX_NUM_INT_E1                       58
#define CFG_MAX_NUM_E1_TS                        32
#define CFG_MAX_NEIGHBOUR_CELLS                  18
#define MAX_LAPD_BIC_IN_E1                       7
#define TS_USAGE_LAPD_TRX                        1
#define TS_USAGE_LAPD_BIC                        2
/* Change For CS2.2 : End */
#define MIN_PKT_AGGR_COUNT                       1
#define MAX_PKT_AGGR_COUNT                       255
//#define MAX_PKT_AGGR_COUNT                       6 //r2.9  code merger 14-june-2016 Gaurav Sinha

/* Change For CS3.0 : Start */
#define MAX_CONFIGURABLE_ARFCNS                  498    /* GSM 900 (1 to 124) - Total 124 
                                                         * GSM 1800 (512 to 885) - Total 374 
                                                         * Total - 124 + 374 = 498 
                                                         */
/* Change For CS3.0 : End */


// CS4.0 MAPPING
#define DEFAULT_ACTION 	                         2
#define DELETE_MAP      	                 0
#define CREATE_MAP                               1

#define INTERNAL_E1                              0
#define EXTERNAL_E1                              1

// CS4.0 MAPPING
/*BSC CS4.0 HA Changes Starts*/
#define PEERCARD_PRESENT                         1
#define PEERCARD_NOT_PRESENT                     0
#define CARDSTATE_INVALID                        0xFF
#define CARD_TYPE_EIC                            12
#define CARD_TYPE_ICC                            15
#define MAX_ICC                                  2
#define INVALID_IP                               "222.222.222.222"
#define INVALID_PORT                             2222
#define CONFIG_CP_PORT                           2222
/*BSC CS4.0 HA Changes Ends*/

#define SYS_TS_FREE                              0
#define SYS_TS_ALLOCATED                         1
#define INVALID_E1                               0xFF
#define INVALID_TS                               0xFF

#define ICCSELFCARD                              3
#define ICCMATECARD                              4
#define EIC0_CARD                                5
#define EIC1_CARD                                6
 
#define PDC_TIMER_START                          300
#define PDC_TIMER_END                            86400
#define PDC_FILE_MAX_SIZE_START                  100
#define PDC_FILE_MAX_SIZE_END                    10240
/* Added For CS4.0 CCU Start */
#define START                                    0
#define STOP                                     1
#define POWER_OFF                                1
#define POWER_ON                                 2
#define ALL_TRX                                  30
#define WHOLE_SITE_EXCEPT_BIC_N_TRANSMISSION     40
#define WHOLE_SITE_EXCEPT_BIC                    50
/* Added For CS4.0 CCU End */

/*BSC CS4.0 MLPPP Changes Starts*/
#define FORCEDCONFIG                             1
#define NORMALCONFIG                             0
#define NUMOFCHANNEL                             16
#define MLPPP_LINK_ENABLED                       1
#define MLPPP_LINK_DISABLED                      0
#define NO_MODE                                  0
#define ETHERNET_MODE                            1
#define MLPPP_MODE                               2
#define STREAM_NUM                               12
#define MLPPP_CHANNEL_ENABLED                    1
#define MLPPP_CHANNEL_DISABLED                   0
/*BSC CS4.0 MLPPP Changes Ends*/

#define TRX_BLOCK 1
#define CELL_BLOCK 2
#define CBS_BIND_RESP 3
#define CBS_BIND_REPEAT 4

/*Diagnostic Changes*/
#define DIAG_BPM_RESP          5
#define DIAG_INTERVAL          6 
#define DIAG_NO_TIMER_RUNNING  0 


#define CBS_BIND_RESP_TIMER 180
#define CBS_BIND_REPEAT_TIMER 180
/*BSC R2.0 Changes Starts*/
#define FillObjTypeFromSlotId(slotId, objType) { \
  if((slotId == ICCSELFCARD) || (slotId == ICCMATECARD)) \
     objType = OAMS_OBJTYPE_ICC; \
  else \
     objType = OAMS_OBJTYPE_EIC; \
}
 
#define FillObjTypeFromNodeType(nodeType, objType) { \
  if((nodeType == SYS_NODE_TYPE_R2_BTS_TRX) || (nodeType == SYS_NODE_TYPE_TRX)) \
     objType = OAMS_OBJTYPE_PTRX; \
  else if((nodeType == SYS_NODE_TYPE_R2_BTS) || (nodeType == SYS_NODE_TYPE_BIC)) \
     objType = OAMS_OBJTYPE_BIC; \
  else if((nodeType == SYS_NODE_TYPE_R3_BTS) || (nodeType == SYS_NODE_TYPE_R2_BTS_IP)) \
     objType = OAMS_OBJTYPE_BIC; \
  else \
     objType = OAMS_OBJTYPE_ICC; \
}

/*DSP Reset Values to be filled in db table*/ 
#define DSP_RESET       1
#define DSP_NO_RESET    2
  
/*BSC R2.0 Changes Ends*/

/* Change For R2.2 :Start */
#define CFG_MAX_NUM_BTS		                 MAX_NUM_BTS_PER_BSS 

/* Change For R2.2 :End */


/*Changes PCU R2.5 Aricent -- START*/

#define OAMS_CFG_MS_TX_PWR_MIN_VALUE_FOR_GSM_900               5
#define OAMS_CFG_MS_TX_PWR_MAX_VALUE_FOR_GSM_900               19
#define OAMS_CFG_MS_TX_PWR_MIN_VALUE_FOR_GSM_1800              0
#define OAMS_CFG_MS_TX_PWR_MAX_VALUE_FOR_GSM_1800              15

#define OAMS_CFG_MS_TX_POWER_MAX_CCH_MIN_VALUE_FOR_GSM_900     5
#define OAMS_CFG_MS_TX_POWER_MAX_CCH_MAX_VALUE_FOR_GSM_900     19
#define OAMS_CFG_MS_TX_POWER_MAX_CCH_MIN_VALUE_FOR_GSM_1800    0
#define OAMS_CFG_MS_TX_POWER_MAX_CCH_MAX_VALUE_FOR_GSM_1800    15

#define OAMS_CFG_MAX_NUM_FREE_HR_MIN_VALUE                     1
#define OAMS_CFG_MAX_NUM_FREE_HR_MAX_VALUE                     3

#define OAMS_CFG_RA_COLOR_MAX_VALUE                            7
#define OAMS_CFG_PRIORITY_ACC_THR_MAX_VALUE                    7

#define OAMS_CFG_BVC_ID_MIN_VALUE                              2
#define OAMS_CFG_BVC_ID_MAX_VALUE                              65535

#define OAMS_CFG_MAX_NUM_PDCH_CELL_MIN_VALUE                   1
#define OAMS_CFG_MAX_NUM_PDCH_CELL_MAX_VALUE                   ((MAX_NUM_TRX_PER_CELL * 8) - 1)

#define OAMS_CFG_MIN_NUM_PDCH_CELL_MAX_VALUE                   ((MAX_NUM_TRX_PER_CELL * 8) - 1)

#define OAMS_CFG_SSB_MAX_VALUE                                 63

#define OAMS_CFG_MAX_NUM_TBF_CELL_MIN_VALUE                    1
#define OAMS_CFG_MAX_NUM_TBF_CELL_MAX_VALUE                    7

#define OAMS_CFG_GPRS_CS_MAX_MIN_VALUE                         1
#define OAMS_CFG_GPRS_CS_MAX_MAX_VALUE                         4

#define OAMS_CFG_GPRS_CS_INITIAL_MIN_VALUE                     1
#define OAMS_CFG_GPRS_CS_INITIAL_MAX_VALUE                     4

#define OAMS_CFG_DUAL_TRAFFIC_MIN_VALUE                        0
#define OAMS_CFG_DUAL_TRAFFIC_MAX_VALUE                        ((MAX_NUM_TRX_PER_CELL * 8) - 1)

#define OAMS_CFG_VALID_ARFCN_MIN_VALUE                         1
#define OAMS_CFG_VALID_ARFCN_MAX_VALUE                         17

#define OAMS_CFG_ARFCN_MIN_VALUE_FOR_GSM_1900                  512
#define OAMS_CFG_ARFCN_MAX_VALUE_FOR_GSM_1900                  810

#define OAMS_CFG_ARFCN_MIN_VALUE_FOR_GSM_850                   128
#define OAMS_CFG_ARFCN_MAX_VALUE_FOR_GSM_850                   251

#define OAMS_CFG_T_FC_C_MIN_VALUE                              1
#define OAMS_CFG_T_FC_C_MAX_VALUE                              10

#define OAMS_CFG_T_FC_TH_MIN_VALUE                             5
#define OAMS_CFG_T_FC_TH_MAX_VALUE                             6000

#define OAMS_CFG_T_FC_SUP_MIN_VALUE                            1
#define OAMS_CFG_T_FC_SUP_MAX_VALUE                            99

#define OAMS_CFG_N_MAX_FC_REP_MIN_VALUE                        1
#define OAMS_CFG_N_MAX_FC_REP_MAX_VALUE                        3

#define OAMS_CFG_T_WAIT_CONFIG_MIN_VALUE                       10
#define OAMS_CFG_T_WAIT_CONFIG_MAX_VALUE                       100

#define OAMS_CFG_FR_CHN_ID_MIN_VALUE                           1
#define OAMS_CFG_FR_CHN_ID_MAX_VALUE                           OAMS_CFG_MAX_NUM_NSVCS

#define OAMS_CFG_DLCI_MIN_VALUE                                16
#define OAMS_CFG_DLCI_MAX_VALUE                                991

#define OAMS_CFG_NMO_MAX_VALUE                                 1
#define OAMS_CFG_SGSNR_MAX_VALUE                               1
#define OAMS_CFG_T_AVG_W_MAX_VALUE                             25
#define OAMS_CFG_T_AVG_T_MAX_VALUE                             25
#define OAMS_CFG_N_AVG_I_MAX_VALUE                             15

#define OAMS_CFG_LEP_PORT_MIN_VALUE                            1024
#define OAMS_CFG_LEP_PORT_MAX_VALUE                            65535

#define OAMS_CFG_LEP_LENGTH                                    25
#define OAMS_CFG_REP_LENGTH                                    25

/*Changes PCU R2.5 Aricent -- END*/
/* R2.4 Changes Start */
#define CBS_NAME_SIZE                  20

#define CBS_NOT_ENTITLED               not_entitled
#define CBS_TEMPORARY_OVERLOAD         temporary_overload
#define CBS_TEMPORARY_FAILURE          temporary_failure
#define CBS_INCORRECT_ID_OR_PASSWORD   incorrect_ID_or_password
#define CBS_VERSION_UNSUPPORTED        version_unsupported

#define LINK_DOWN 0x00
#define LINK_UP 0x01

#define BIND_FAIL 0x00
#define BIND_SUCCESS 0x01
#define SMSCB_VERION 0x00

#define MAX_CBS_SERVER    255

/* R2.4 Changes End */

/*Changes for R2.3.4 Starts*/
#define PSU0_CARD       1
#define PSU1_CARD       2
/*Changes for R2.3.4 Ends*/

#define TRX_POSITION_1       1
#define TRX_POSITION_2       2

//A6 inframe changes
#define MAX_INFRAME_TRX 6

#define fillFailTypeFromNodeType(nodeType, failType)\
{\
switch(nodeType)\
{\
  case SYS_NODE_TYPE_BSC :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_BSC");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_BSC;\
  break;\
  case SYS_NODE_TYPE_TRX :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_TRX");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_TRX;\
  break;\
  case SYS_NODE_TYPE_BIC :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_BIC");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_BIC;\
  break;\
  case  SYS_NODE_TYPE_EIC :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_EIC");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_EIC;\
  break;\
  case SYS_NODE_TYPE_DSP :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_DSP");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_DSP;\
  break;\
  case SYS_NODE_TYPE_R2_BTS :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_R2_BTS");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_R2_BTS;\
  break;\
  case SYS_NODE_TYPE_R2_BTS_TRX :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_R2_TRX");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_R2_TRX;\
  break;\
  case SYS_NODE_TYPE_R2_BTS_IP :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_R2_BTS_IP");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_R2_BTS_IP;\
  break;\
  case SYS_NODE_TYPE_R2_BTS_IP_TRX :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_R2_BTS_IP_TRX");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_R2_BTS_IP_TRX;\
  break;\
  case SYS_NODE_TYPE_R3_BTS :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_R3_BTS");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_R3_BTS;\
  break;\
  case SYS_NODE_TYPE_R3_BTS_TRX :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_R3_BTS_TRX");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS_FOR_R3_BTS_TRX;\
  break;\
  default :\
    LOG_PRINT(DEBUG,"SwAct failtype is for NODE_TYPE_UNKNOWN err..");\
    failType = CM_ERR_SW_DWNLD_OR_ACT_IN_PROGRESS;\
  break;\
}\
}

/* Changes For E1-T1 */
#define TRAU_MU_LAW 1
#define TRAU_A_LAW  2

/*BSC-R2.5.5 Diagnostics Changes Start*/
#define  DIAG_BPM_RESP_TIMER          420
#define  DIAG_BPM_ICC_TSI_RESP_TIMER  3420
#define  DIAG_INTERVAL_TIMER          2
/*BSC-R2.5.5 Diagnostics Changes End*/

/* Changes For WCDMA-GSM HO */
#define CFG_MAX_NUM_SCRAMBLING_CODE_PER_ARFCN  16
#define CFG_MAX_NUM_NEIGHBOUR_WCDMA_FDD_CELL   16

/* EGPRS Changes Starts */
#define OAMS_CFG_EGPRS_MCS_MAX_MIN_VALUE  5
#define OAMS_CFG_EGPRS_MCS_MAX_MAX_VALUE  13

#define OAMS_CFG_EGPRS_8PSK_MCS_INITIAL_MIN_VALUE  9
#define OAMS_CFG_EGPRS_8PSK_MCS_INITIAL_MAX_VALUE  13

#define OAMS_CFG_EGPRS_GMSK_MCS_INITIAL_MIN_VALUE   5
#define OAMS_CFG_EGPRS_GMSK_MCS_INITIAL_MAX_VALUE   8

/* EGPRS Changes Ends */

/* Changes for R2.8 Starts*/

/*ApplTei Status*/
#define TEI_NOT_ALLOCATED   0
#define TEI_ALLOCATED       1
/*ApplTei User Type*/
#define TEI_USR_INVALID               0
#define TEI_USR_BTS                   1
#define TEI_USR_TRX                   2

/*ApplTei User Id*/
#define TEI_USRID_INVALID             0
#define CFG_TRX_APP_TEI_START_INDEX   163 /*(123+40 Tei for R3/R2_IP BTS */ 

/* Changes for R2.8 Starts*/
/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
#define FAIL 0
#define GOOD 1
#define INLET_MODULE 1
#define OUTLET_MODULE 2
#define IMX_MODULE 3
/*Added for 1U BSC Gaurav Sinha 05-07-2016*/
//Mantis 31749
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
#define CARD_TYPE_OBM 1
#define CARD_TYPE_OBF 2
#define CARD_TYPE_HOST 0
#define SYS_OMC_INDEX 1003
/*Added for 1U BSC/IP_BSC Switchover Gaurav Sinha 24-08-2016*/
//Mantis 31749
#endif /*_OAMCFG_HASHDEFS_H_ */

/********************************* Change History ***************************
  Release     Patch       Author         Description

 ************************************** End *********************************/
