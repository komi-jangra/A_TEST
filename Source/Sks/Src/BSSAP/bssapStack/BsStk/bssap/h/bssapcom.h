/*******************************************************************************
**      FILE NAME:
**          bssapcom.h
**
**      DESCRIPTION:
**              Defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef __BSSAPCOMH__
#define __BSSAPCOMH__

#define SSN_UP 1
#define PC_UP  2

/*#define FALSE 0
#define TRUE 1*/

#define DTAP 1
#define BSSMAP  0

#define RECEIVE 1
#define TRANSMIT 2

#define CALL_ST_IDLE               0
#define CALL_ST_BUSY               4 

#define CIC_ST_LOCAL_BLOCK         1
#define CIC_ST_LOCAL_UNBLK         0

#define CIC_ST_REMOTE_BLOCK        2 
#define CIC_ST_REMOTE_UNBLK        0

#define CIC_ST_STATUSFLAG_TRUE        8 
#define CIC_ST_STATUSFLAG_FALSE       0 


#define  HANDOVER_TRUE            1    
#define  HANDOVER_FALSE           0    

#define  HANDOVERFAIL_TRUE        2 
#define  HANDOVERFAIL_FALSE        0 

#define HOOLDBSS_TRUE         4
#define HOOLDBSS_FALSE         0 

#define HONEWBSS_TRUE  8
#define HONEWBSS_FALSE  0 

#define DT1HOREQ_TRUE   16
#define DT1HOREQ_FALSE   0

#define DTAP_MSG_P0S             (0x04U)
/*
 * Message Discriminator
 */
#define BSSAP_MD_BSSMAP    0x00U
#define BSSAP_MD_DTAP      0x01U
#define BSSAP_MD_PROP      0x02U 


/*BSSAP Error Message Types */
#define BSSAP_MD_TIMEOUT         (BSSAP_MD_DTAP << 1)
#define BSSAP_MD_NETWORK         ((BSSAP_MD_DTAP << 1) | 0x01U)
#define BSSAP_MD_PROTOCOL        (BSSAP_MD_DTAP << 2)
#define BSSAP_MD_SCCP            (BSSAP_MD_DTAP << 3)

#define BSSAP_FAILURE_IND  (0x32U) 

/*BSSAP Protocol error codes */
#define BSSAP_EENCODE            (0x01U)
#define BSSAP_EDECODE            (0x02U)
#define BSSAP_EINVMESSAGE        (0x03U)
#define BSSAP_ECICNOTFOUND       (0x04U)
#define BSSAP_ENORESETACK        (0x05U)
#define BSSAP_ENOBLKACK          (0x06U)
#define BSSAP_ENOUNBLKACK        (0x07U)
#define BSSAP_ENORESETCKTACK     (0x08U)
#define BSSAP_EUNEQUIPCKT        (0x09U)
#define BSSAP_ENORELEASECMP      (0x0AU)
#define DTAP_EENCODE             (0x0BU)
#define BSSAP_ECKTPROC           (0x0CU)
#define BSSAP_EASSREQFAIL        (0x0DU)
#define BSSAP_ENOCKTGRPBLKACK    (0x0EU)
#define BSSAP_ENOCKTGRPUNBLKACK  (0x0FU)
#define BSSAP_EMSGSENTFAIL       (0x1FU)
#define BSSAP_ENOHANDOVERCMD       (0x20U)
#define BSSAP_ENORESETIPACK       (0x21U) 

#define L3MSG_TYPE_POS           1 
/*
 * Message type
 *
 */
#define BSSAP_MSG_RESERVED                      0x00U

/* Assignment Messages */
#define BSSAP_MSG_ASSIGN_REQUEST                0x01U
#define BSSAP_MSG_ASSIGN_COMPLETE               0x02U
#define BSSAP_MSG_ASSIGN_FAILURE                0x03U

#define BSSAP_MSG_CHAN_MOD_REQUEST              0x08U
/* Handover Messages */
#define BSSAP_MSG_HANDOVER_REQUEST              0x10U
#define BSSAP_MSG_HANDOVER_REQUIRED             0x11U
#define BSSAP_MSG_HANDOVER_REQUEST_ACK          0x12U
#define BSSAP_MSG_HANDOVER_COMMAND              0x13U
#define BSSAP_MSG_HANDOVER_COMPLETE             0x14U
#define BSSAP_MSG_HANDOVER_SUCCEEDED            0x15U
#define BSSAP_MSG_HANDOVER_FAILURE              0x16U
#define BSSAP_MSG_HANDOVER_PERFORMED            0x17U
#define BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE    0x18U
#define BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE   0x19U
#define BSSAP_MSG_HANDOVER_REQUIRED_REJECT      0x1AU
#define BSSAP_MSG_HANDOVER_DETECT               0x1BU
#define BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED    0x70U
#define BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT  0x71U
#define BSSAP_MSG_INTERNAL_HANDOVER_COMMAND     0x72U
#define BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY     0x73U
/* Release Messages */
#define BSSAP_MSG_CLEAR_COMMAND                 0x20U
#define BSSAP_MSG_CLEAR_COMPLETE                0x21U
#define BSSAP_MSG_CLEAR_REQUEST                 0x22U
#define BSSAP_MSG_SAPI_N_REJECT                 0x25U
#define BSSAP_MSG_CONFUSION                     0x26U

/* Other Connection Related Messages */
#define BSSAP_MSG_SUSPEND                       0x28U
#define BSSAP_MSG_RESUME                        0x29U
#define BSSAP_MSG_CONNECTION_ORIENTED_INFO      0x2AU
#define BSSAP_MSG_PERFORM_LOCATION_REQUEST     0x2BU
#define BSSAP_MSG_LSA_INFORMATION               0x2CU
#define BSSAP_MSG_PERFORM_LOCATION_RESPONSE    0x2DU
#define BSSAP_MSG_PERFORM_LOCATION_ABORT       0x2EU
#define BSSAP_MSG_COMMON_ID                     0x2FU

/* General Messages */
#define BSSAP_MSG_RESET                         0x30U
#define BSSAP_MSG_RESET_ACK                     0x31U
#define BSSAP_MSG_OVERLOAD                      0x32U
#define BSSAP_MSG_GEN_RESERVED                  0x33U
#define BSSAP_MSG_RESET_CIRCUIT                 0x34U
#define BSSAP_MSG_RESET_CIRCUIT_ACK             0x35U
#define BSSAP_MSG_MSC_INVOKE_TRACE              0x36U
#define BSSAP_MSG_BSS_INVOKE_TRACE              0x37U
#define BSSAP_MSG_CONNECTIONLESS_INFORMATION    0x3AU
/* Terrestrial Resource Messages */
#define BSSAP_MSG_BLOCK                         0x40U
#define BSSAP_MSG_BLOCK_ACK                     0x41U
#define BSSAP_MSG_UNBLOCK                       0x42U
#define BSSAP_MSG_UNBLOCK_ACK                   0x43U
#define BSSAP_MSG_CKT_GROUP_BLOCK               0x44U
#define BSSAP_MSG_CKT_GRP_BLK_ACK               0x45U
#define BSSAP_MSG_CKT_GRP_UNBLOCK               0x46U
#define BSSAP_MSG_CKT_GRP_UNBLKING_ACK          0x47U
#define BSSAP_MSG_UNEQUIPPED_CKT                0x48U
#define BSSAP_MSG_CHANGE_CKT                    0x4EU
#define BSSAP_MSG_CHANGE_CKT_ACK                0x4FU
/*Local Switching Messages*/
#define BSSAP_MSG_LCLS_CONNECT_CONTROL          0x74U
#define BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK      0x75U
#define BSSAP_MSG_LCLS_NOTIFICATION             0x76U 
/* Radio Resource Messages */
#define BSSAP_MSG_PAGING_RESPONSE               0x27U
#define BSSAP_MSG_RESOURCE_REQUEST              0x50U
#define BSSAP_MSG_RESOURCE_INDICATION           0x51U
#define BSSAP_MSG_PAGING                        0x52U
#define BSSAP_MSG_CIPHER_MODE_CMD               0x53U
#define BSSAP_MSG_CLASSMARK_UPDATE              0x54U
#define BSSAP_MSG_CIPHER_MODE_COMPLETE          0x55U
#define BSSAP_MSG_QUEUING_INDICATION            0x56U
#define BSSAP_MSG_COMPLETE_LAYER3_INFO          0x57U
#define BSSAP_MSG_CLASSMARK_REQUEST             0x58U
#define BSSAP_MSG_CIPHER_MODE_REJECT            0x59U
#define BSSAP_MSG_LOAD_INDICATION               0x5AU
/* VGCS_VBS */
#define BSSAP_MSG_VGCS_VBS_SETUP                0x04U
#define BSSAP_MSG_VGCS_VBS_SETUP_ACK            0x05U
#define BSSAP_MSG_VGCS_VBS_SETUP_REFUSE         0x06U
#define BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST   0x07U
#define BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT    0x1CU
#define BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE   0x1DU
#define BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION   0x1EU
#define BSSAP_MSG_UPLINK_REQUEST                0x1FU
#define BSSAP_MSG_UPLINK_REQUEST_ACK            0x27U
#define BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION   0x49U
#define BSSAP_MSG_UPLINK_RELEASE_INDICATION     0x4AU
#define BSSAP_MSG_UPLINK_REJECT_COMMAND         0x4BU
#define BSSAP_MSG_UPLINK_RELEASE_COMMAND        0x4CU
#define BSSAP_MSG_UPLINK_SEIZED_COMMAND         0x4DU

/* VGCS_VBS */
#define BSSAP_MSG_VGCS_VBS_SETUP                0x04U
#define BSSAP_MSG_RESET_IP                      0x3DU
#define BSSAP_MSG_RESET_IP_ACK                  0x3EU

/*
 * Call Control Related Messages
 */
#define BSSAP_CC_MSG_ALERTING                   0x01
#define BSSAP_CC_MSG_CALL_CONFIRMED             0x08
#define BSSAP_CC_MSG_CALL_PROCEEDING            0x02
#define BSSAP_CC_MSG_CONNECT                    0x07
#define BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE        0x0f
#define BSSAP_CC_MSG_EMERGENCY_SETUP            0x0e
#define BSSAP_CC_MSG_PROGRESS                   0x03
#define BSSAP_CC_ESTABLISHMENT                  0x04
#define BSSAP_CC_MSG_ESTABLISHMENT_CONFIRMED    0x06
#define BSSAP_CC_MSG_RECALL                     0x0b
#define BSSAP_CC_MSG_START_CC                   0x09
#define BSSAP_CC_MSG_SETUP                      0x05
/* Call Information */
#define BSSAP_CC_MSG_MODIFY                     0x17
#define BSSAP_CC_MSG_MODIFY_COMPLETE            0x1f
#define BSSAP_CC_MSG_MODIFY_REJECT              0x13
#define BSSAP_CC_MSG_USER_INFORMATION           0x10
#define BSSAP_CC_MSG_HOLD                       0x18
#define BSSAP_CC_MSG_HOLD_ACKNOWLEDGE           0x19
#define BSSAP_CC_MSG_HOLD_REJECT                0x1a
#define BSSAP_CC_MSG_RETRIEVE                   0x1c
#define BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE       0x1d
#define BSSAP_CC_MSG_RETRIEVE_REJECT            0x1e

/* Call Clearing Messages */
#define BSSAP_CC_MSG_DISCONNECT                 0x25
#define BSSAP_CC_MSG_RELEASE                    0x2d
#define BSSAP_CC_MSG_RELEASE_COMPLETE           0x2a

/* Misc Messages */
#define BSSAP_CC_MSG_CONGESTION_CONTROL         0x39
#define BSSAP_CC_MSG_NOTIFY                     0x3e
#define BSSAP_CC_MSG_STATUS                     0x3d
#define BSSAP_CC_MSG_STATUS_ENQUIRY             0x34
#define BSSAP_CC_MSG_START_DTMF                 0x35
#define BSSAP_CC_MSG_STOP_DTMF                  0x31
#define BSSAP_CC_MSG_STOP_DTMF_ACK              0x32
#define BSSAP_CC_MSG_START_DTMF_ACK             0x36
#define BSSAP_CC_MSG_START_DTMF_REJECT          0x37
#define BSSAP_CC_MSG_FACILITY                   0x3a
#define BSSAP_CC_MSG_REGISTER                   0x3b
/*
 * Information Elelments
 * Section 3.2.2
 */
#define BSSAP_IEI_DUMMY                         0x00U
#define BSSAP_IEI_CIRCUIT_IDENTITY_CODE         0x01U
#define BSSAP_IEI_RESOURCE_AVAILABLE            0x03U
#define BSSAP_IEI_CAUSE                         0x04U
#define BSSAP_IEI_CELL_IDENTIFIER               0x05U
#define BSSAP_IEI_PRIORITY                      0x06U
#define BSSAP_IEI_LAYER3_HEADER_INFORMATION     0x07U
#define BSSAP_IEI_IMSI                          0x08U
#define BSSAP_IEI_TMSI                          0x09U
#define BSSAP_IEI_ENCRYPTION_INFORMATION        0x0AU
#define BSSAP_IEI_CHANNEL_TYPE                  0x0BU
#define BSSAP_IEI_PERIODICITY                   0x0CU
#define BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR   0x0DU
#define BSSAP_IEI_NUMBER_OF_MS                  0x0EU
#define BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2   0x12U
#define BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3   0x13U
#define BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED  0x14U
#define BSSAP_IEI_RR_CAUSE                      0x15U
#define BSSAP_IEI_LAYER3_INFORMATION            0x17U
#define BSSAP_IEI_DLCI                          0x18U
#define BSSAP_IEI_DOWNLINK_DTX_FLAG             0x19U
#define BSSAP_IEI_CELL_IDENTIFIER_LIST          0x1AU
#define BSSAP_IEI_RESPONSE_REQUEST              0x1BU
#define BSSAP_IEI_RESOURCE_INDICATION_METHOD    0x1CU
#define BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1   0x1DU
#define BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST    0x1EU
#define BSSAP_IEI_DIAGNOSTICS                   0x1FU
#define BSSAP_IEI_LAYER3_MESSAGE_CONTENT        0x20U
#define BSSAP_IEI_CHOSEN_CHANNEL                0x21U
#define BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE     0x22U
#define BSSAP_IEI_CIPHER_RESPONSE_MODE          0x23U
#define BSSAP_IEI_CHANNEL_NEEDED                0x24U
#define BSSAP_IEI_TRACE_TYPE                    0x25U
#define BSSAP_IEI_TRIGGER_ID                    0x26U
#define BSSAP_IEI_TRACE_REFERENCE               0x27U
#define BSSAP_IEI_TRANSACTION_ID                0x28U
#define BSSAP_IEI_MOBILE_IDENTITY               0x29U
#define BSSAP_IEI_OMC_ID                        0x2AU
#define BSSAP_IEI_FORWARD_INDICATOR             0x2BU
#define BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM   0x2CU
#define BSSAP_IEI_CIRCUIT_POOL                  0x2DU
#define BSSAP_IEI_CIRCUIT_POOL_LIST             0x2EU
#define BSSAP_IEI_TIME_INDICATION               0x2FU
#define BSSAP_IEI_RESOURCE_SITUATION            0x30U
#define BSSAP_IEI_CURRENT_CHANNEL_TYPE_1        0x31U
#define BSSAP_IEI_QUEUING_INDICATOR             0x32U
#define BSSAP_IEI_SPEECH_VERSION                0x40U
#define BSSAP_IEI_ASSIGNMENT_REQUIREMENT        0x33U
#define BSSAP_IEI_TALKER_FLAG                   0x35U
#define BSSAP_IEI_CONNECTION_RELEASE_REQUESTED  0x36U
#define BSSAP_IEI_GROUP_CALL_REFERENCE          0x37U
#define BSSAP_IEI_eMLPP_PRIORITY                0x38U
#define BSSAP_IEI_CONFIGURATION_EVOLUTION_IND   0x39U
#define BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO       0x3AU
#define BSSAP_IEI_LSA_IDENTIFIER                0x3BU
#define BSSAP_IEI_LSA_IDENTIFIER_LIST           0x3CU
#define BSSAP_IEI_LSA_INFORMATION               0x3DU
#define BSSAP_IEI_LCS_QOS                       0x3EU
#define BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR         0x3FU
#define BSSAP_IEI_LCS_PRIORITY                  0x43U
#define BSSAP_IEI_LOCATION_TYPE                 0x44U
#define BSSAP_IEI_LOCATION_ESTIMATE             0x45U
#define BSSAP_IEI_POSITIONING_DATA              0x46U
#define BSSAP_IEI_LCS_CAUSE                     0x47U
#define BSSAP_IEI_LCS_CLIENT_TYPE               0x48U
#define BSSAP_IEI_APDU                          0x49U
#define BSSAP_IEI_NETWORK_ELEMENT_IDENTITY      0x4AU
#define BSSAP_IEI_GPS_ASSISTANCE_DATA           0x4BU
#define BSSAP_IEI_DECIPHERING_KEYS              0x4CU
#define BSSAP_IEI_RETURN_ERROR_REQUEST          0x4DU
#define BSSAP_IEI_RETURN_ERROR_CAUSE            0x4EU
#define BSSAP_IEI_SEGMENTATION                  0x4FU
#define BSSAP_IEI_SERVICE_HANDOVER              0x50U
#define BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS  0x51U
#define BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA  0x52U
#define BSSAP_IEI_GERAN_CLASSMARK               0x53U 
#define BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO       0x61U
#define BSSAP_IEI_INTER_SYSTEM_INFO             0x63U
#define BSSAP_IEI_SNA_ACCESS_INFO               0x64U
/* Field Element - Section 3.2.3 */
#define BSSAP_IEI_EXTRA_INFORMATION             0x01U
#define BSSAP_IEI_CURRENT_CHANNEL_TYPE_2        0x02U
#define BSSAP_IEI_TARGET_CELL_RADIO_INFO        0x03U
#define BSSAP_IEI_GPRS_SUSPEND_INFO             0x04U
#define BSSAP_IEI_MULTIRATE_CONFIG_INFO         0x05U
#define BSSAP_IEI_DUAL_TRANSFER_MODE_INFO       0x06U
#define BSSAP_IEI_INTER_RAT_HANDOVER_INFO       0x07U
#define BSSAP_IEI_UE_CAP_INFO                   0x07U
#define BSSAP_IEI_CDMA_2000_CAP_INFO            0x08U
#define BSSAP_IEI_DOWNLINK_CELL_LOAD_INFO       0x09U
#define BSSAP_IEI_UPLINK_CELL_LOAD_INFO         0x0AU
#define BSSAP_IEI_CELL_LOAD_INFO_GROUP          0x0BU
#define BSSAP_IEI_CELL_LOAD_INFO                0x0CU
#define BSSAP_IEI_UTRAN_PRECONFIG_IND_SET_INFO  0x09U
#define BSSAP_IEI_UE_SECURITY_INFO              0x0AU
#define BSSAP_IEI_TALKER_PRIORITY               0x6AU
#define BSSAP_IEI_AOIP                          0x7CU
#define BSSAP_IEI_CODEC_LIST                    0x7DU
#define BSSAP_IEI_SPEECH_CODEC                  0x7EU
#define BSSAP_IEI_CALLID_LIST                   0x80U
#define BSSAP_IEI_CALL_ID                       0x7FU
#define BSSAP_IEI_PROFILE_ID                    0x82U
#define BSSAP_IEI_AIF_SELECTOR                  0x81U
#define BSSAP_IEI_KC128                         0x83U
#define BSSAP_IEI_GLB_CALL_REF                  0x89U
#define BSSAP_IEI_LCLS_CONFIG                   0x8AU
#define BSSAP_IEI_LCLS_CONN_STATUS_CNTRL        0x8BU
#define BSSAP_IEI_LCLS_CORR_NOT_NED             0x8CU
#define BSSAP_IEI_LCLS_BSS_STATUS               0x8DU
#define BSSAP_IEI_LCLS_BRK_REQ                  0x8EU


#define DIAG_ERROR_LOCATION_NOT_DETERMINED      0x00U
#define DIAG_NO_ERROR                           0x00U

#define CIC_PCM_HI_BITS                         0xFFU
#define CIC_PCM_LO_BITS                         0xE0U


#define CIC_TIMESLOT_BIT                        0x1FU

#define CT_SPEECH                                0x01U
#define CT_DATA                                  0x02U
#define CT_SIGNALING                             0x03U
/* Added by Amaresh start for fix Mantis-Id 30762 */
#define CT_SPEECH_CTM_TXT_TELEPHONY              0x04U
/* Added by Amaresh stop for fix Mantis-Id 30762 */

/*Registration Messages */
#define BSSAP_MSG_IMSI_DETACH_INDICATION        0x01U
#define BSSAP_MSG_LOCATION_UPDATING_ACCEPT      0x02U
#define BSSAP_MSG_LOCATION_UPDATING_REJECT      0x04U
#define BSSAP_MSG_LOCATION_UPDATING_REQUEST     0x08U

/* Security Messages*/
#define BSSAP_MSG_AUTHENTICATION_REJECT         0x11U
#define BSSAP_MSG_AUTHENTICATION_REQUEST        0x12U
#define BSSAP_MSG_AUTHENTICATION_RESPONSE       0x14U
#define BSSAP_MSG_AUTHENTICATION_FAILURE        0x1CU
#define BSSAP_MSG_IDENTITY_REQUEST              0x18U
#define BSSAP_MSG_IDENTITY_RESPONSE             0x19U
#define BSSAP_MSG_TMSI_REALLOC_COMMAND          0x1AU
#define BSSAP_MSG_TMSI_REALLOC_COMPLETE         0x1BU

/* Connection Management Messages */
#define BSSAP_MSG_CM_SERVICE_ACCEPT             0x21U
#define BSSAP_MSG_CM_SERVICE_REJECT             0x22U
#define BSSAP_MSG_CM_SERVICE_ABORT              0x23U
#define BSSAP_MSG_CM_SERVICE_REQUEST            0x24U
#define BSSAP_MSG_CM_REESTABLISHMENT_REQ        0x28U
#define BSSAP_MSG_ABORT                         0x29U

/* Miscellaneous Messages*/
#define BSSAP_MSG_MM_INFORMATION                0x32U
#define BSSAP_MSG_MM_STATUS                     0x31U
#define BSSAP_MSG_MM_NULL                       0x30U


/*SCCP messages */
#define BSSAP_CON_ESTD           (0x04U) 
#define BSSAP_CON_REL            (0x05U)
#define BSSAP_CON_REF            (0x06U) 
#define BSSAP_CON_ERR            (0x07U) 


#define SCCP_MSG_CR         (0x01U)     /* Connection Request */
#define SCCP_MSG_CC         (0x02U)     /* Conection Confirm */
#define SCCP_MSG_CREF       (0x03U)     /* Connection REFused */
#define SCCP_MSG_RLSD       (0x04U)     /* ReLeaSed */
#define SCCP_MSG_RLC        (0x05U)     /* ReLease Complete */
#define SCCP_MSG_DT1        (0x06U)     /* DaTa form 1 */
#define SCCP_MSG_DT2        (0x07U)     /* DaTa form 2 */
#define SCCP_MSG_AK         (0x08U)     /* AcKnowledgement */
#define SCCP_MSG_UDT        (0x09U)     /* Unit DaTa */
#define SCCP_MSG_XUDT       (0x11U)     /* eXtended Unit DaTa */
#define SCCP_MSG_UDTS       (0x0AU)     /* Unit DaTa Service */
#define SCCP_MSG_XUDTS      (0x12U)     /* eXtended Unit DaTa Service */
#define SCCP_MSG_ED         (0x0BU)     /* Expedited Data */
#define SCCP_MSG_EA         (0x0CU)     /* Expedited data Acknowledgement */
#define SCCP_MSG_RSR        (0x0DU)     /* ReSet Request */
#define SCCP_MSG_RSC        (0x0EU)     /* ReSet Confirmation */
#define SCCP_MSG_ERR        (0x0FU)     /* ERRor */
#define SCCP_MSG_IT         (0x10U)     /* Inactivity Test */
#define SCCP_MSG_NOTICE     (0xFFU)     /* Notice from MTP3/to user */
#define SCCP_MSG_LUDT       (0x13U)     /* Long Unitdata message */
#define SCCP_MSG_LUDTS      (0x14U)     /* Long Unitdata Service Msg */


#define SCCP_SCMG_SS_ALLOWED       (0x01U)
#define SCCP_SCMG_SS_PROHIBIT      (0x02U)
#define SCCP_SCMG_SS_STATUS_TEST   (0x03U)
#define SCCP_SCMG_SS_OOS_REQ       (0x04U)
#define SCCP_SCMG_SS_OOS_GRANT     (0x05U)
#define SCCP_SCMG_SS_CONGESTED     (0x06U)
#define SCCP_SCMG_SS_BACKUP_ROUTE  (0xFDU)
#define SCCP_SCMG_SS_NORMAL_ROUTE  (0xFEU)
#define SCCP_SCMG_SS_ROUTE_STATUS  (0xFFU)

/*define ONLY PRINT PURPOSE*/
#define MTP3_SCMG_SP_RESUME        (0xAAU)
#define MTP3_SCMG_SP_PAUSE         (0xABU)
#define MTP3_SCMG_SP_CONGESTED     (0XACU) 
#define SCCP_SCMG_SS               (0xADU)
#define MTP3_SCMG_SP               (0xACU)
#define BSSAP_CP_DATA              (0x01U)
#define BSSAP_CP_DATA_ACK          (0x04U)

#define MGMT_SCCP_MSG_TYPE_STR(x) ((x==SCCP_SCMG_SS_ALLOWED)?"SCCP_SCMG_SS_ALLOWED":\
                             ((x==SCCP_SCMG_SS_PROHIBIT)?"SCCP_SCMG_SS_PROHIBIT":\
                             ((x==SCCP_SCMG_SS_STATUS_TEST)?"SCCP_SCMG_SS_STATUS_TEST":\
                             ((x==SCCP_SCMG_SS_CONGESTED)?"SCCP_SCMG_SS_CONGESTED":\
                             "UNKNOWN"))))

#define SCCP_MSG_TYPE_STR(x) ((x==MTP3_SCMG_SP_RESUME)?"MTP3_SCMG_SP_RESUME":\
                             ((x==MTP3_SCMG_SP_PAUSE)?"MTP3_SCMG_SP_PAUSE":\
                             ((x==MTP3_SCMG_SP_CONGESTED)?"MTP3_SCMG_SP_CONGESTED":\
                             ((x==SCCP_SCMG_SS)?"SCCP_SCMG_SS":\
                             ((x==SCCP_MSG_CR)?"SCCP_MSG_CR":\
                             ((x==SCCP_MSG_CC)?"SCCP_MSG_CC":\
                             ((x==SCCP_MSG_DT1)?"SCCP_MSG_DT1":\
                             ((x==SCCP_MSG_CREF)?"SCCP_MSG_CREF":\
                             ((x==SCCP_MSG_RLSD)?"SCCP_MSG_RLSD":\
                             ((x==SCCP_MSG_UDT)?"SCCP_MSG_UDT":\
                             ((x==MTP3_SCMG_SP)?"MTP3_SCMG_SP":\
                             "UNKNOWN")))))))))))

/* Proprietry Messages  */
#define BSSAP_CHG_APPID_CALLREFID_REQ                0x81
#define BSSAP_CHG_APPID_CALLREFID_ACK                0x82

/*Macros*/
#define BSSAP_MSG_TYPE_STR(x) ((x==BSSAP_MSG_ASSIGN_COMPLETE)?"BSSAP_MSG_ASSIGN_COMPLETE":\
                    ((x==BSSAP_MSG_ASSIGN_FAILURE)?"BSSAP_MSG_ASSIGN_FAILURE":\
                    ((x==BSSAP_MSG_ASSIGN_REQUEST)?"BSSAP_MSG_ASSIGN_REQUEST":\
                    ((x==BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE)?"BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE":\
                    ((x==BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE)?"BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE":\
                    ((x==BSSAP_MSG_HANDOVER_COMMAND)?"BSSAP_MSG_HANDOVER_COMMAND":\
                    ((x==BSSAP_MSG_HANDOVER_COMPLETE)?"BSSAP_MSG_HANDOVER_COMPLETE":\
                    ((x==BSSAP_MSG_HANDOVER_DETECT)?"BSSAP_MSG_HANDOVER_DETECT":\
                    ((x==BSSAP_MSG_HANDOVER_FAILURE)?"BSSAP_MSG_HANDOVER_FAILURE":\
                    ((x==BSSAP_MSG_HANDOVER_PERFORMED)?"BSSAP_MSG_HANDOVER_PERFORMED":\
                    ((x==BSSAP_MSG_HANDOVER_REQUEST)?"BSSAP_MSG_HANDOVER_REQUEST":\
                    ((x==BSSAP_MSG_HANDOVER_REQUEST_ACK)?"BSSAP_MSG_HANDOVER_REQUEST_ACK":\
                    ((x==BSSAP_MSG_HANDOVER_REQUIRED)?"BSSAP_MSG_HANDOVER_REQUIRED":\
                    ((x==BSSAP_MSG_HANDOVER_REQUIRED_REJECT)?"BSSAP_MSG_HANDOVER_REQUIRED_REJECT":\
                    ((x==BSSAP_MSG_HANDOVER_SUCCEEDED)?"BSSAP_MSG_HANDOVER_SUCCEEDED":\
                    ((x==BSSAP_MSG_CLEAR_COMMAND)?"BSSAP_MSG_CLEAR_COMMAND":\
                    ((x==BSSAP_MSG_CLEAR_COMPLETE)?"BSSAP_MSG_CLEAR_COMPLETE":\
                    ((x==BSSAP_MSG_CLEAR_REQUEST)?"BSSAP_MSG_CLEAR_REQUEST":\
                    ((x==BSSAP_MSG_SAPI_N_REJECT)?"BSSAP_MSG_SAPI_N_REJECT":\
                    ((x==BSSAP_MSG_CONFUSION)?"BSSAP_MSG_CONFUSION":\
                    ((x==BSSAP_MSG_SUSPEND)?"BSSAP_MSG_SUSPEND":\
                    ((x==BSSAP_MSG_RESUME)?"BSSAP_MSG_RESUME":\
                    ((x==BSSAP_MSG_RESET)?"BSSAP_MSG_RESET":\
                    ((x==BSSAP_MSG_RESET_ACK)?"BSSAP_MSG_RESET_ACK":\
                    ((x==BSSAP_MSG_RESET_IP)?"BSSAP_MSG_RESET_IP":\
                    ((x==BSSAP_MSG_RESET_IP_ACK)?"BSSAP_MSG_RESET_IP_ACK":\
                    ((x==BSSAP_MSG_RESET_CIRCUIT)?"BSSAP_MSG_RESET_CIRCUIT":\
                    ((x==BSSAP_MSG_RESET_CIRCUIT_ACK)?"BSSAP_MSG_RESET_CIRCUIT_ACK":\
                    ((x==BSSAP_MSG_OVERLOAD)?"BSSAP_MSG_OVERLOAD":\
                    ((x==BSSAP_MSG_MSC_INVOKE_TRACE)?"BSSAP_MSG_MSC_INVOKE_TRACE":\
                    ((x==BSSAP_MSG_BSS_INVOKE_TRACE)?"BSSAP_MSG_BSS_INVOKE_TRACE":\
                    ((x==BSSAP_MSG_BLOCK)?"BSSAP_MSG_BLOCK":\
                    ((x==BSSAP_MSG_BLOCK_ACK)?"BSSAP_MSG_BLOCK_ACK":\
                    ((x==BSSAP_MSG_UNBLOCK)?"BSSAP_MSG_UNBLOCK":\
                    ((x==BSSAP_MSG_UNBLOCK_ACK)?"BSSAP_MSG_UNBLOCK_ACK":\
                    ((x==BSSAP_MSG_CKT_GROUP_BLOCK)?"BSSAP_MSG_CKT_GROUP_BLOCK":\
                    ((x==BSSAP_MSG_CKT_GRP_BLK_ACK)?"BSSAP_MSG_CKT_GRP_BLK_ACK":\
                    ((x==BSSAP_MSG_CKT_GRP_UNBLOCK)?"BSSAP_MSG_CKT_GRP_UNBLOCK":\
                    ((x==BSSAP_MSG_CKT_GRP_UNBLKING_ACK)?"BSSAP_MSG_CKT_GRP_UNBLKING_ACK":\
                    ((x==BSSAP_MSG_UNEQUIPPED_CKT)?"BSSAP_MSG_UNEQUIPPED_CKT":\
                    ((x==BSSAP_MSG_CHANGE_CKT)?"BSSAP_MSG_CHANGE_CKT":\
                    ((x==BSSAP_MSG_CHANGE_CKT_ACK)?"BSSAP_MSG_CHANGE_CKT_ACK":\
                    ((x==BSSAP_MSG_RESOURCE_REQUEST)?"BSSAP_MSG_RESOURCE_REQUEST":\
                    ((x==BSSAP_MSG_RESOURCE_INDICATION)?"BSSAP_MSG_RESOURCE_INDICATION":\
                    ((x==BSSAP_MSG_PAGING)?"BSSAP_MSG_PAGING":\
                    ((x==BSSAP_MSG_PAGING_RESPONSE)?"BSSAP_MSG_PAGING_RESPONSE":\
                    ((x==BSSAP_MSG_CIPHER_MODE_CMD)?"BSSAP_MSG_CIPHER_MODE_CMD":\
                    ((x==BSSAP_MSG_CIPHER_MODE_COMPLETE)?"BSSAP_MSG_CIPHER_MODE_COMPLETE":\
                    ((x==BSSAP_MSG_CIPHER_MODE_REJECT)?"BSSAP_MSG_CIPHER_MODE_REJECT":\
                    ((x==BSSAP_MSG_CLASSMARK_UPDATE)?"BSSAP_MSG_CLASSMARK_UPDATE":\
                    ((x==BSSAP_MSG_CLASSMARK_REQUEST)?"BSSAP_MSG_CLASSMARK_REQUEST":\
                    ((x==BSSAP_MSG_COMPLETE_LAYER3_INFO)?"BSSAP_MSG_COMPLETE_LAYER3_INFO":\
                    ((x==BSSAP_MSG_LOAD_INDICATION)?"BSSAP_MSG_LOAD_INDICATION":\
                    ((x==BSSAP_MSG_QUEUING_INDICATION)?"BSSAP_MSG_QUEUING_INDICATION":\
                    ((x==BSSAP_MSG_VGCS_VBS_SETUP)?"BSSAP_MSG_VGCS_VBS_SETUP":\
                    ((x==BSSAP_MSG_VGCS_VBS_SETUP_ACK)?"BSSAP_MSG_VGCS_VBS_SETUP_ACK":\
                    ((x==BSSAP_MSG_VGCS_VBS_SETUP_REFUSE)?"BSSAP_MSG_VGCS_VBS_SETUP_REFUSE":\
                    ((x==BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST)?"BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST":\
                    ((x==BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT)?"BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT":\
                    ((x==BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE)?"BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE":\
                    ((x==BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION)?"BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION":\
                    ((x==BSSAP_MSG_UPLINK_REQUEST)?"BSSAP_MSG_UPLINK_REQUEST":\
                    ((x==BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION)?"BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION":\
                    ((x==BSSAP_MSG_UPLINK_RELEASE_INDICATION)?"BSSAP_MSG_UPLINK_RELEASE_INDICATION":\
                    ((x==BSSAP_MSG_UPLINK_REJECT_COMMAND)?"BSSAP_MSG_UPLINK_REJECT_COMMAND":\
                    ((x==BSSAP_MSG_UPLINK_RELEASE_COMMAND)?"BSSAP_MSG_UPLINK_RELEASE_COMMAND":\
                    ((x==BSSAP_MSG_UPLINK_SEIZED_COMMAND)?"BSSAP_MSG_UPLINK_SEIZED_COMMAND":\
                    ((x==BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY)?"BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY":\
                    ((x==BSSAP_MSG_INTERNAL_HANDOVER_COMMAND)?"BSSAP_MSG_INTERNAL_HANDOVER_COMMAND":\
                    ((x==BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT)?"BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT":\
                    ((x==BSSAP_MSG_PERFORM_LOCATION_REQUEST)?"BSSAP_MSG_PERFORM_LOCATION_REQUEST":\
                    ((x==BSSAP_MSG_LSA_INFORMATION)?"BSSAP_MSG_LSA_INFORMATION":\
                    ((x==BSSAP_MSG_PERFORM_LOCATION_RESPONSE)?"BSSAP_MSG_PERFORM_LOCATION_RESPONSE":\
                    ((x==BSSAP_MSG_PERFORM_LOCATION_ABORT)?"BSSAP_MSG_PERFORM_LOCATION_ABORT":\
                    ((x==BSSAP_MSG_LCLS_CONNECT_CONTROL)?"BSSAP_MSG_LCLS_CONNECT_CONTROL":\
                    ((x==BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK)?"BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK":\
                    ((x==BSSAP_MSG_LCLS_NOTIFICATION)?"BSSAP_MSG_LCLS_NOTIFICATION":\
                    ((x==BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED)?"BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED":\
                    "UNKNOWN"))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

#define BSSAP_MAP_ERR_CAUSE(x) ((x==BSSAP_EMISSMAND)?C_INFO_ELEMENT_MISSING:\
                    ((x==BSSAP_EUNKNOWN_IE)?C_UNKNOWN_INFO_ELEMENT:\
                    ((x=BSSAP_EUNKNOWN_MSG_TYPE)?C_UNKNOWN_MSG_TYPE:\
                    ((x==BSSAP_EINVALIDARGS)?C_ICORRECT_VALUE:\
                    ((x==C_PROTOCOL_ERROR)?C_PROTOCOL_ERROR:\
                    ((x==BSSAP_EINVARGSLEN)?C_INVALID_MSG_CONTENT:\
                    C_INVALID_MSG_CONTENT))))))

#define BSSAP_DIAG_SET_ERROR_POINTER(x,y)            \
    ((x).error_pointer[0] = ((y) & 0xFFU))


#define BSSAP_DIAG_SET_ERROR_BIT_POSITION(x,y)        \
    ((x).error_pointer[1] = ((y) & 0x0FU))

#define BSSAP_SET_CIC_VALUE(x,y)                                   \
    (((x).cic[0] = (0xff00 & y)>>8) |                            \
     ((x).cic[1] = (y & 0x00ff)))


#define BSSAP_CIC_GET_PCM_ID(x)                                   \
    (((x).cic[0] << 3) |                            \
     ((x).cic[1] & CIC_PCM_LO_BITS) >> 5)

#define BSSAP_CIC_GET_TIMESLOT(x)                                 \
    ((x).cic[1] & CIC_TIMESLOT_BIT)

#define BSSAP_CIC_SET_PCM_ID(x,y)                                 \
    (((x).cic[0] = ((y) >> 3) & CIC_PCM_HI_BITS),   \
      (x).cic[1] &= ~CIC_PCM_LO_BITS,               \
      (x).cic[1] |= (((y) << 5) & CIC_PCM_LO_BITS))

#define BSSAP_CIC_SET_TIMESLOT(x,y)                               \
    ((x).cic[1] &= ~CIC_TIMESLOT_BIT,               \
     (x).cic[1] |= (y) & CIC_TIMESLOT_BIT)

#define BSSAP_CT_GET_SPEECH_DATA_IND(x)               \
    ((x).speech_or_data)

#define tshift      0x05
#define GET_PCM_VAL(x)                                   \
    (((x) & 0x0000ffe0 ) >> tshift)                             

#define GET_TIMESLOT_VAL(x)                                 \
    (((x) & 0x0000ffe0 ) >> tshift)

#ifndef ZS
#define BS_PRINT_EVENT_STR(x) ((x==EVTSPTSTAIND)?"SPT:Status Indication ":\
                    ((x==EVTSPTUDATIND)?"SPT:Unit Data Indication":\
                    ((x==EVTSPTDATIND)?"SPT:Data Indication":\
                    ((x==EVTSPTBNDCFM)?"SPT:Bind Confirm":\
                    ((x==EVTSPTCONCFM)?"SPT: Connection Confirm":\
                    ((x==EVTSPTCONIND)?"SPT: Connection Indication":\
                    ((x==EVTSPTDISREQ)?"SPT: Disconnect Request":\
                    ((x==EVTSPTDISIND)?"SPT: Disconnect Indication":\
                    ((x==EVTSPTSTEIND)?"SPT: Status Indication":\
                    ((x==EVTSPTPCSTEIND)?"SPT: PC Status Indication":\
                    ((x==EVTLBSCNTRLREQ)?"LM: Control Request":\
                    ((x==EVTLBSSTSREQ)?"LM: Statistic Request":\
                    ((x==EVTLBSCFGREQ)?"LM: Configuration Request":\
                    ((x==EVTLBSCFGCFM)?"LM: Configuration Confirm":\
                    ((x==EVTLBSSTSCFM)?"LM: Statistic Confirm":\
                    ((x==EVTLBSSTAIND)?"LM: Status Indication":\
                    ((x==EVTLBSSTACFM)?"LM: Status Confirm":\
                    ((x==EVTLBSCNTRLCFM)?"LM: Control Confirm":\
                    ((x==EVTBSAPPREQ)?"APP: Application Request":\
                    ((x==EVTSHTCNTRLREQ)?"SH: Control Request":\
                    ((x==EVTSHTCNTRLCFM)?"SH: Control Confirm":\
                    "UNKNOWN")))))))))))))))))))))
#else
#define BS_PRINT_EVENT_STR(x) ((x==EVTSPTSTAIND)?"SPT:Status Indication ":\
                    ((x==EVTSPTUDATIND)?"SPT:Unit Data Indication":\
                    ((x==EVTSPTDATIND)?"SPT:Data Indication":\
                    ((x==EVTSPTBNDCFM)?"SPT:Bind Confirm":\
                    ((x==EVTSPTCONCFM)?"SPT: Connection Confirm":\
                    ((x==EVTSPTCONIND)?"SPT: Connection Indication":\
                    ((x==EVTSPTDISREQ)?"SPT: Disconnect Request":\
                    ((x==EVTSPTDISIND)?"SPT: Disconnect Indication":\
                    ((x==EVTSPTSTEIND)?"SPT: Status Indication":\
                    ((x==EVTSPTPCSTEIND)?"SPT: PC Status Indication":\
                    ((x==EVTLBSCNTRLREQ)?"LM: Control Request":\
                    ((x==EVTLBSSTSREQ)?"LM: Statistic Request":\
                    ((x==EVTLBSCFGREQ)?"LM: Configuration Request":\
                    ((x==EVTLBSCFGCFM)?"LM: Configuration Confirm":\
                    ((x==EVTLBSSTSCFM)?"LM: Statistic Confirm":\
                    ((x==EVTLBSSTAIND)?"LM: Status Indication":\
                    ((x==EVTLBSSTACFM)?"LM: Status Confirm":\
                    ((x==EVTLBSCNTRLCFM)?"LM: Control Confirm":\
                    ((x==EVTBSAPPREQ)?"APP: Application Request":\
                    ((x==EVTSHTCNTRLREQ)?"SH: Control Request":\
                    ((x==EVTSHTCNTRLCFM)?"SH: Control Confirm":\
                    ((x==EVTZSMILZSCNTRLREQ)?"SH: SM Control Request":\
                    ((x==EVTZSMILZSCFGREQ)?"SH: SM CFG Request":\
                    ((x==EVTZSMILZSCFGCFM)?"SH: SM CFG Confirm":\
                    ((x==EVTZSMILZSCNTRLCFM)?"SH: SM Control Confirm":\
                    "UNKNOWN")))))))))))))))))))))))))
#endif

#define BS_PRINT_TMR_EVT_STR(x) ((x==TMR_TINT)?"LOWER SAP BIND TIMER":\
                    ((x==BSSAP_T_1)?"BSSAP_T_1":\
                    ((x==BSSAP_T_4)?"BSSAP_T_4":\
                    ((x==BSSAP_T_7)?"BSSAP_T_7":\
                    ((x==BSSAP_T_8)?"BSSAP_T_8":\
                    ((x==BSSAP_T_10)?"BSSAP_T_10":\
                    ((x==BSSAP_T_11)?"BSSAP_T_11":\
                    ((x==BSSAP_T_13)?"BSSAP_T_13":\
                    ((x==BSSAP_T_17)?"BSSAP_T_17":\
                    ((x==BSSAP_T_18)?"BSSAP_T_18":\
                    ((x==BSSAP_T_19)?"BSSAP_T_19":\
                    ((x==BSSAP_T_20)?"BSSAP_T_20":\
                    ((x==BSSAP_T_25)?"BSSAP_T_25":\
                    ((x==BSSAP_T_RBSC)?"BSSAP_T_RBSC":\
                    "UNKNOWN"))))))))))))))


#define BS_PRINT_SRC_ENT_STR(x) ((x==ENTSM)?"ENTSM":\
                    ((x==ENTSP)?"ENTSP":\
                    ((x==ENTSN)?"ENTSN":\
                    ((x==ENTBSSAP)?"ENTBSSAP":\
                    ((x==ENTBS)?"ENTBS":\
                    ((x==ENTAPP)?"ENTAPP":\
                    ((x==ENTSH)?"ENTSH":\
                    "UNKNOWN")))))))

#define BS_DTAP_MSG_TYPE_STR(x) ((x==BSSAP_MSG_AUTHENTICATION_REJECT)?"BSSAP_MSG_AUTHENTICATION_REJECT":\
                    ((x==BSSAP_MSG_AUTHENTICATION_REQUEST)?"BSSAP_MSG_AUTHENTICATION_REQUEST":\
                    ((x==BSSAP_MSG_AUTHENTICATION_RESPONSE)?"BSSAP_MSG_AUTHENTICATION_RESPONSE":\
                    ((x==BSSAP_MSG_AUTHENTICATION_FAILURE)?"BSSAP_MSG_AUTHENTICATION_FAILURE":\
                    ((x==BSSAP_MSG_IDENTITY_REQUEST)?"BSSAP_MSG_IDENTITY_REQUEST":\
                    ((x==BSSAP_MSG_IDENTITY_RESPONSE)?"BSSAP_MSG_IDENTITY_RESPONSE":\
                    ((x==BSSAP_MSG_TMSI_REALLOC_COMMAND)?"BSSAP_MSG_TMSI_REALLOC_COMMAND":\
                    ((x==BSSAP_MSG_TMSI_REALLOC_COMPLETE)?"BSSAP_MSG_TMSI_REALLOC_COMPLETE":\
                    ((x==BSSAP_MSG_LOCATION_UPDATING_ACCEPT)?"BSSAP_MSG_LOCATION_UPDATING_ACCEPT":\
                    ((x==BSSAP_MSG_LOCATION_UPDATING_REJECT)?"BSSAP_MSG_LOCATION_UPDATING_REJECT":\
                    ((x==BSSAP_MSG_LOCATION_UPDATING_REQUEST)?"BSSAP_MSG_LOCATION_UPDATING_REQUEST":\
                    ((x==BSSAP_MSG_CM_SERVICE_ACCEPT)?"BSSAP_MSG_CM_SERVICE_ACCEPT":\
                    ((x==BSSAP_MSG_CM_SERVICE_REJECT)?"BSSAP_MSG_CM_SERVICE_REJECT":\
                    ((x==BSSAP_MSG_CM_SERVICE_REQUEST)?"BSSAP_MSG_CM_SERVICE_REQUEST":\
                    ((x==BSSAP_CC_MSG_ALERTING)?"BSSAP_CC_MSG_ALERTING":\
                    ((x==BSSAP_CC_MSG_CALL_CONFIRMED)?"BSSAP_CC_MSG_CALL_CONFIRMED":\
                    ((x==BSSAP_CC_MSG_CALL_PROCEEDING)?"BSSAP_CC_MSG_CALL_PROCEEDING":\
                    ((x==BSSAP_CC_MSG_CONNECT)?"BSSAP_CC_MSG_CONNECT":\
                    ((x==BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE)?"BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE":\
                    ((x==BSSAP_CC_MSG_EMERGENCY_SETUP)?"BSSAP_CC_MSG_EMERGENCY_SETUP":\
                    ((x==BSSAP_CC_MSG_PROGRESS)?"BSSAP_CC_MSG_PROGRESS":\
                    ((x==BSSAP_CC_ESTABLISHMENT)?"BSSAP_CC_ESTABLISHMENT":\
                    ((x==BSSAP_CC_MSG_ESTABLISHMENT_CONFIRMED)?"BSSAP_CC_MSG_ESTABLISHMENT_CONFIRMED":\
                    ((x==BSSAP_CC_MSG_RECALL)?"BSSAP_CC_MSG_RECALL":\
                    ((x==BSSAP_CC_MSG_START_CC)?"BSSAP_CC_MSG_START_CC":\
                    ((x==BSSAP_CC_MSG_SETUP)?"BSSAP_CC_MSG_SETUP":\
                    ((x==BSSAP_CC_MSG_DISCONNECT)?"BSSAP_CC_MSG_DISCONNECT":\
                    ((x==BSSAP_CC_MSG_RELEASE)?"BSSAP_CC_MSG_RELEASE":\
                    ((x==BSSAP_CC_MSG_RELEASE_COMPLETE)?"BSSAP_CC_MSG_RELEASE_COMPLETE":\
                    ((x==BSSAP_CC_MSG_MODIFY)?"BSSAP_CC_MSG_MODIFY":\
                    ((x==BSSAP_CC_MSG_MODIFY_COMPLETE)?"BSSAP_CC_MSG_MODIFY_COMPLETE":\
                    ((x==BSSAP_CC_MSG_MODIFY_REJECT)?"BSSAP_CC_MSG_MODIFY_REJECT":\
                    ((x==BSSAP_CC_MSG_USER_INFORMATION)?"BSSAP_CC_MSG_USER_INFORMATION":\
                    ((x==BSSAP_CC_MSG_HOLD)?"BSSAP_CC_MSG_HOLD":\
                    ((x==BSSAP_CC_MSG_HOLD_ACKNOWLEDGE)?"BSSAP_CC_MSG_HOLD_ACKNOWLEDGE":\
                    ((x==BSSAP_CC_MSG_HOLD_REJECT)?"BSSAP_CC_MSG_HOLD_REJECT":\
                    ((x==BSSAP_CC_MSG_RETRIEVE)?"BSSAP_CC_MSG_RETRIEVE":\
                    ((x==BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE)?"BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE":\
                    ((x==BSSAP_CC_MSG_RETRIEVE_REJECT)?"BSSAP_CC_MSG_RETRIEVE_REJECT":\
                    ((x==BSSAP_MSG_IMSI_DETACH_INDICATION)?"BSSAP_MSG_IMSI_DETACH_INDICATION":\
                    "UNKNOWN"))))))))))))))))))))))))))))))))))))))))

#define BS_PRINT_ALARM_EVENT_STR(x) ((x==LCM_EVENT_BND_FAIL)?"LCM_EVENT_BND_FAIL":\
                    ((x==LBS_EVENT_TIME_OUT_NO_BLOCK_ACK_RECEIVED)?"LBS_EVENT_TIME_OUT_NO_BLOCK_ACK_RECEIVED(ID:2150)":\
                    ((x==LBS_EVENT_TIME_OUT_NO_UNBLOCK_ACK_RECEIVED)?"LBS_EVENT_TIME_OUT_NO_UNBLOCK_ACK_RECEIVED(ID:2151)":\
                    ((x==LBS_EVENT_TIME_OUT_NO_RESET_ACK_RECEIVED)?"LBS_EVENT_TIME_OUT_NO_RESET_ACK_RECEIVED(ID:2152)":\
                    ((x==LBS_EVENT_TIME_OUT_NO_RESET_CKT_ACK_RECEIVED)?"LBS_EVENT_TIME_OUT_NO_RESET_CKT_ACK_RECEIVED(ID:2153)":\
                    ((x==LBS_EVENT_TIME_OUT_NO_RESETIP_ACK_RECEIVED)?"LBS_EVENT_TIME_OUT_NO_RESETIP_ACK_RECEIVED(ID:2154)":\
                    ((x==LBS_EVENT_WRONG_MSG_DIRECTION)?"LBS_EVENT_WRONG_MSG_DIRECTION(ID:2155)":\
                    ((x==LBS_EVENT_WRONG_MSG_TYPE)?"LBS_EVENT_WRONG_MSG_TYPE(ID:2156)":\
                    ((x==LBS_EVENT_REMOTE_SUBSYSTEM_DOWN)?"LBS_EVENT_REMOTE_SUBSYSTEM_DOWN(ID:2157)":\
                    ((x==LBS_EVENT_NETWORK_DOWN)?"LBS_EVENT_NETWORK_DOWN(ID:2158)":\
                    ((x==LBS_EVENT_NEITHER_MAP_NOR_DTAP_MSG)?"LBS_EVENT_NEITHER_MAP_NOR_DTAP_MSG(ID:2159)":\
                    ((x==LBS_EVENT_FAILED_TO_DISPATCH_MSG_TO_PEER)?"LBS_EVENT_FAILED_TO_DISPATCH_MSG_TO_PEER(ID:2160)":\
                    ((x==LBS_EVENT_CONFIG_DATA_NOT_FOUND)?"LBS_EVENT_CONFIG_DATA_NOT_FOUND(ID:2161)":\
                    ((x==LBS_EVENT_FAIL_TO_REMOVE_DPC)?"LBS_EVENT_FAIL_TO_REMOVE_DPC(ID:2162)":\
                    ((x==LBS_EVENT_CAN_NOT_ADD_DPC)?"LBS_EVENT_CAN_NOT_ADD_DPC(ID:2163)":\
                    ((x==LBS_EVENT_CONTEXT_ALREADY_EXIST)?"LBS_EVENT_CONTEXT_ALREADY_EXIST(ID:2164)":\
                    ((x==LBS_EVENT_CIC_CONTEXT_NOT_FOUND)?"LBS_EVENT_CIC_CONTEXT_NOT_FOUND(ID:2165)":\
                    ((x==LBS_EVENT_FAILED_TO_REMOVE_CONTEXT)?"LBS_EVENT_FAILED_TO_REMOVE_CONTEXT(ID:2166)":\
                    ((x==LBS_EVENT_COULD_NOT_MODIFIED_CONTEXT)?"LBS_EVENT_COULD_NOT_MODIFIED_CONTEXT(ID:2167)":\
                    ((x==LBS_EVENT_CALL_IN_BUSY_STATE)?"LBS_EVENT_CALL_IN_BUSY_STATE(ID:2168)":\
                    ((x==LBS_EVENT_CIC_IN_BLOCK_STATE)?"LBS_EVENT_CIC_IN_BLOCK_STATE(ID:2169)":\
                    ((x==LBS_EVENT_CIC_POOL_MISMATCH)?"LBS_EVENT_CIC_POOL_MISMATCH(ID:2170)":\
                    ((x==LBS_EVENT_INVALID_CIC)?"LBS_EVENT_INVALID_CIC(ID:2171)":\
                    "UNKNOWN")))))))))))))))))))))))

#define BS_PRINT_ALARM_CATAGORY_STR(x) ((x==LCM_CATEGORY_PROTOCOL)?"LCM_CATEGORY_PROTOCOL":\
                    ((x==LCM_CATEGORY_INTERFACE)?"LCM_CATEGORY_INTERFACE":\
                    ((x==LCM_CATEGORY_INTERNAL)?"LCM_CATEGORY_INTERNAL":\
                    ((x==LCM_CATEGORY_RESOURCE)?"LCM_CATEGORY_RESOURCE":\
                    ((x==LCM_CATEGORY_PSF_FTHA)?"LCM_CATEGORY_PSF_FTHA":\
                    ((x==LCM_CATEGORY_PERF_MONIT)?"LCM_CATEGORY_PERF_MONIT":\
                    ((x==LCM_CATEGORY_DNS_RECORDS)?"LCM_CATEGORY_DNS_RECORDS":\
                    ((x==LCM_CATEGORY_LYR_SPECIFIC)?"LCM_CATEGORY_LYR_SPECIFIC":\
                    "UNKNOWN"))))))))

#define BS_PRINT_ALARM_CAUSE_STR(x) ((x==LCM_CAUSE_UNKNOWN)?"LCM_CAUSE_UNKNOWN":\
                    ((x==LCM_CAUSE_INV_SAP)?"LCM_CAUSE_INV_SAP":\
                    ((x==LCM_CAUSE_INV_SPID)?"LCM_CAUSE_INV_SPID":\
                    ((x==LCM_CAUSE_INV_SUID)?"LCM_CAUSE_INV_SUID":\
                    ((x==LCM_CAUSE_INV_NETWORK_MSG)?"LCM_CAUSE_INV_NETWORK_MSG":\
                    ((x==LCM_CAUSE_DECODE_ERR)?"LCM_CAUSE_DECODE_ERR":\
                    ((x==LCM_CAUSE_USER_INITIATED)?"LCM_CAUSE_USER_INITIATED":\
                    ((x==LCM_CAUSE_MGMT_INITIATED)?"LCM_CAUSE_MGMT_INITIATED":\
                    ((x==LCM_CAUSE_INV_STATE)?"LCM_CAUSE_INV_STATE":\
                    ((x==LCM_CAUSE_TMR_EXPIRED)?"LCM_CAUSE_TMR_EXPIRED":\
                    ((x==LCM_CAUSE_PROT_NOT_ACTIVE)?"LCM_CAUSE_PROT_NOT_ACTIVE":\
                    ((x==LCM_CAUSE_INV_PAR_VAL)?"LCM_CAUSE_INV_PAR_VAL":\
                    "UNKNOWN"))))))))))))


#define BS_PRINT_SAP_STATE(x) ((x==BS_UNBND)?"UN_BIND":\
                    ((x==BS_BND)?"BIND":\
                    ((x==BS_WT_BNDCFM)?"WAIT_BIND_CFM":\
                    "UNKNOWN")))

#define BS_PRINT_SWTCH_TYPE(x) ((x==LBS_SW_ITU)?"ITU":\
                    ((x==LBS_SW_ANSI)?"ANSI":\
                    "UNKNOWN"))
#define CCL_GET_RANGE(x)   ((x).range & 0xFFU)

#define BS_GET_LOCALSTATE(x,y) (y = (x) & 0x01U)
#define BS_SET_LOCALSTATE_BLOCK(x) ((x) = (x) | 0x01U)
#define BS_SET_LOCALSTATE_UNBLOCK(x) ((x) = (x) & 0xFEU)
 
#define BS_GET_REMOTESTATE(x,y) (y = (x) & 0x02U)
#define BS_SET_REMOTESTATE_BLOCK(x) ((x) =(x) | 0x02U)
#define BS_SET_REMOTESTATE_UNBLOCK(x) ((x) = (x) & 0xFDU)

#define BS_GET_CALLSTATE(x,y) (y = (x) & 0x04U)
#define BS_SET_CALLSTATE_BUSY(x) ((x) = (x) | 0x04U)
#define BS_SET_CALLSTATE_IDLE(x) ((x) = (x) & 0xFBU)


#define BS_GET_STATUSFLAG(x,y) (y = (x) & 0x08U)
#define BS_SET_STATUSFLAG_TRUE(x) ((x) = (x) | 0x08U)
#define BS_SET_STATUSFLAG_FALSE(x) ((x) = (x) & 0xF7U)

#define BS_GET_HANDOVER(x,y) (y = (x) & 0x01U)
#define BS_SET_HANDOVER_TRUE(x) ((x) = (x) | 0x01U)
#define BS_SET_HANDOVER_FALSE(x) ((x) = (x) & 0xFEU)

#define BS_GET_HANDOVERFAIL(x,y) (y = (x) & 0x02U)
#define BS_SET_HANDOVERFAIL_TRUE(x) ((x) =(x) | 0x02U)
#define BS_SET_HANDOVERFAIL_FALSE(x) ((x) = (x) & 0xFDU)

#define BS_GET_HOOLDBSS(x,y) (y = (x) & 0x04U)
#define BS_SET_HOOLDBSS_TRUE(x) ((x) = (x) | 0x04U)
#define BS_SET_HOOLDBSS_FALSE(x) ((x) = (x) & 0xFBU)


#define BS_GET_HONEWBSS(x,y) (y = (x) & 0x08U)
#define BS_SET_HONEWBSS_TRUE(x) ((x) = (x) | 0x08U)
#define BS_SET_HONEWBSS_FALSE(x) ((x) = (x) & 0xF7U)


#define BS_GET_DT1HOREQ(x,y) (y = (x) & 0x10U)
#define BS_SET_DT1HOREQ_TRUE(x) ((x) = (x) | 0x10U)
#define BS_SET_DT1HOREQ_FALSE(x) ((x) = (x) & 0xEFU)

#define BS_SET_SSN_STATUS_UP(x) ((x) = (x) | 0x01U)
#define BS_SET_SSN_STATUS_DOWN(x) ((x) = (x) & 0xFEU)
#define BS_GET_SSN_STATUS(x,y) (y = (x) & 0x01U)

#define BS_SET_PC_STATUS_UP(x) ((x) = (x) | 0x02U)
#define BS_SET_PC_STATUS_DOWN(x) ((x) = (x) & 0xFDU)
#define BS_GET_PC_STATUS(x,y) (y = (x) & 0x02U)

#define BS_SET_PC_STATUS_CONG(x) ((x) = (x) | 0x03U)
#define BS_SET_PC_STATUS_NOT_CONG(x) ((x) = (x) & 0xFBU)
#define BS_GET_PC_STATUS_CONG(x,y) (y = (x) & 0x03U)

#define BS_SET_CICLIST_RANGE(x,y) ((x).range = (y) & 0xFFU)
#define BS_GET_CICLIST_RANGE(x,y)   (y = ((x).range & 0xFFU) + 1)
#define BS_DTAP_MSG_TYPE_STR_CC(x) ((x==BSSAP_CC_MSG_NOTIFY)?"BSSAP_CC_MSG_NOTIFY":\
                    ((x==BSSAP_CC_MSG_CONGESTION_CONTROL)?"BSSAP_CC_MSG_CONGESTION_CONTROL":\
                    ((x==BSSAP_CC_MSG_STATUS)?"BSSAP_CC_MSG_STATUS":\
                    ((x==BSSAP_CC_MSG_STATUS_ENQUIRY)?"BSSAP_CC_MSG_STATUS_ENQUIRY":\
                    ((x==BSSAP_CC_MSG_START_DTMF)?"BSSAP_CC_MSG_START_DTMF":\
                    ((x==BSSAP_CC_MSG_STOP_DTMF)?"BSSAP_CC_MSG_STOP_DTMF":\
                    ((x==BSSAP_CC_MSG_STOP_DTMF_ACK)?"BSSAP_CC_MSG_STOP_DTMF_ACK":\
                    ((x==BSSAP_CC_MSG_START_DTMF_ACK)?"BSSAP_CC_MSG_START_DTMF_ACK":\
                    ((x==BSSAP_CC_MSG_START_DTMF_REJECT)?"BSSAP_CC_MSG_START_DTMF_REJECT":\
                    ((x==BSSAP_CC_MSG_FACILITY)?"BSSAP_CC_MSG_FACILITY":\
                    ((x==BSSAP_CC_MSG_ALERTING)?"BSSAP_CC_MSG_ALERTING":\
                    ((x==BSSAP_CC_MSG_CALL_CONFIRMED)?"BSSAP_CC_MSG_CALL_CONFIRMED":\
                    ((x==BSSAP_CC_MSG_CALL_PROCEEDING)?"BSSAP_CC_MSG_CALL_PROCEEDING":\
                    ((x==BSSAP_CC_MSG_CONNECT)?"BSSAP_CC_MSG_CONNECT":\
                    ((x==BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE)?"BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE":\
                    ((x==BSSAP_CC_MSG_EMERGENCY_SETUP)?"BSSAP_CC_MSG_EMERGENCY_SETUP":\
                    ((x==BSSAP_CC_MSG_PROGRESS)?"BSSAP_CC_MSG_PROGRESS":\
                    ((x==BSSAP_CC_ESTABLISHMENT)?"BSSAP_CC_ESTABLISHMENT":\
                    ((x==BSSAP_CC_MSG_ESTABLISHMENT_CONFIRMED)?"BSSAP_CC_MSG_ESTABLISHMENT_CONFIRMED":\
                    ((x==BSSAP_CC_MSG_RECALL)?"BSSAP_CC_MSG_RECALL":\
                    ((x==BSSAP_CC_MSG_START_CC)?"BSSAP_CC_MSG_START_CC":\
                    ((x==BSSAP_CC_MSG_SETUP)?"BSSAP_CC_MSG_SETUP":\
                    ((x==BSSAP_CC_MSG_DISCONNECT)?"BSSAP_CC_MSG_DISCONNECT":\
                    ((x==BSSAP_CC_MSG_RELEASE)?"BSSAP_CC_MSG_RELEASE":\
                    ((x==BSSAP_CC_MSG_RELEASE_COMPLETE)?"BSSAP_CC_MSG_RELEASE_COMPLETE":\
                    ((x==BSSAP_CC_MSG_MODIFY)?"BSSAP_CC_MSG_MODIFY":\
                    ((x==BSSAP_CC_MSG_MODIFY_COMPLETE)?"BSSAP_CC_MSG_MODIFY_COMPLETE":\
                    ((x==BSSAP_CC_MSG_MODIFY_REJECT)?"BSSAP_CC_MSG_MODIFY_REJECT":\
                    ((x==BSSAP_CC_MSG_USER_INFORMATION)?"BSSAP_CC_MSG_USER_INFORMATION":\
                    ((x==BSSAP_CC_MSG_HOLD)?"BSSAP_CC_MSG_HOLD":\
                    ((x==BSSAP_CC_MSG_HOLD_ACKNOWLEDGE)?"BSSAP_CC_MSG_HOLD_ACKNOWLEDGE":\
                    ((x==BSSAP_CC_MSG_HOLD_REJECT)?"BSSAP_CC_MSG_HOLD_REJECT":\
                    ((x==BSSAP_CC_MSG_RETRIEVE)?"BSSAP_CC_MSG_RETRIEVE":\
                    ((x==BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE)?"BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE":\
                    ((x==BSSAP_CC_MSG_RETRIEVE_REJECT)?"BSSAP_CC_MSG_RETRIEVE_REJECT":\
                    ((x==BSSAP_MSG_IMSI_DETACH_INDICATION)?"BSSAP_MSG_IMSI_DETACH_INDICATION":\
                    "CC-UNKNOWN-MSG"))))))))))))))))))))))))))))))))))))
#define BS_DTAP_MSG_TYPE_STR_MM(x) ((x==BSSAP_MSG_IMSI_DETACH_INDICATION)?"BSSAP_MSG_IMSI_DETACH_INDICATION":\
                    ((x==BSSAP_MSG_LOCATION_UPDATING_ACCEPT)?"BSSAP_MSG_LOCATION_UPDATING_ACCEPT":\
                    ((x==BSSAP_MSG_LOCATION_UPDATING_REJECT)?"BSSAP_MSG_LOCATION_UPDATING_REJECT":\
                    ((x==BSSAP_MSG_LOCATION_UPDATING_REQUEST)?"BSSAP_MSG_LOCATION_UPDATING_REQUEST":\
                    ((x==BSSAP_MSG_AUTHENTICATION_REJECT)?"BSSAP_MSG_AUTHENTICATION_REJECT":\
                    ((x==BSSAP_MSG_AUTHENTICATION_REQUEST)?"BSSAP_MSG_AUTHENTICATION_REQUEST":\
                    ((x==BSSAP_MSG_AUTHENTICATION_RESPONSE)?"BSSAP_MSG_AUTHENTICATION_RESPONSE":\
                    ((x==BSSAP_MSG_AUTHENTICATION_FAILURE)?"BSSAP_MSG_AUTHENTICATION_FAILURE":\
                    ((x==BSSAP_MSG_IDENTITY_REQUEST)?"BSSAP_MSG_IDENTITY_REQUEST":\
                    ((x==BSSAP_MSG_IDENTITY_RESPONSE)?"BSSAP_MSG_IDENTITY_RESPONSE":\
                    ((x==BSSAP_MSG_TMSI_REALLOC_COMMAND)?"BSSAP_MSG_TMSI_REALLOC_COMMAND":\
                    ((x==BSSAP_MSG_TMSI_REALLOC_COMPLETE)?"BSSAP_MSG_TMSI_REALLOC_COMPLETE":\
                    ((x==BSSAP_MSG_CM_SERVICE_ACCEPT)?"BSSAP_MSG_CM_SERVICE_ACCEPT":\
                    ((x==BSSAP_MSG_CM_SERVICE_REJECT)?"BSSAP_MSG_CM_SERVICE_REJECT":\
                    ((x==BSSAP_MSG_CM_SERVICE_ABORT)?"BSSAP_MSG_CM_SERVICE_ABORT":\
                    ((x==BSSAP_MSG_CM_SERVICE_REQUEST)?"BSSAP_MSG_CM_SERVICE_REQUEST":\
                    ((x==BSSAP_MSG_CM_REESTABLISHMENT_REQ)?"BSSAP_MSG_CM_REESTABLISHMENT_REQ":\
                    ((x==BSSAP_MSG_ABORT)?"BSSAP_MSG_ABORT":\
                    ((x==BSSAP_MSG_MM_INFORMATION)?"BSSAP_MSG_MM_INFORMATION":\
                    ((x==BSSAP_MSG_MM_STATUS)?"BSSAP_MSG_MM_STATUS":\
                    ((x==BSSAP_MSG_MM_NULL)?"BSSAP_MSG_MM_NULL":\
                    "MM-UNKNOWN-MSG")))))))))))))))))))))
#define BS_DTAP_MSG_TYPE_STR_SMS(x) ((x==BSSAP_CP_DATA)?"BSSAP_CP_DATA":\
                    ((x==BSSAP_CP_DATA_ACK)?"BSSAP_CP_DATA_ACK":\
                    "SMS-UNKNOWN-MSG"))

#define PRINT_SCCP_MSG(x) ((x==SCCP_N_UNITDATA_INDICATION)?"SCCP_N_UNITDATA_INDICATION":\
                    ((x==SCCP_N_STATE_INDICATION)?"SCCP_N_STATE_INDICATION":\
                    ((x==SCCP_N_PCSTATE_INDICATION)?"SCCP_N_PCSTATE_INDICATION":\
                    ((x==SCCP_N_CONNECT_INDICATION)?"SCCP_N_CONNECT_INDICATION":\
                    ((x==SCCP_N_CONNECT_CONFIRM)?"SCCP_N_CONNECT_CONFIRM":\
                    ((x==SCCP_N_DATA_INDICATION)?"SCCP_N_DATA_INDICATION":\
                    ((x==SCCP_N_DISCONNECT_INDICATION)?"SCCP_N_DISCONNECT_INDICATION":\
                    "UNKNOWN-MSG")))))))
#endif /*End of __BSSAPCOMH__*/

