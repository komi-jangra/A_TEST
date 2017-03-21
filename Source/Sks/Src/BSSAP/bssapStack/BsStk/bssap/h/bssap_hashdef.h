/*******************************************************************************
**      FILE NAME:
**          bssap_hashdefs.h
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
#ifndef __BSSAP_HASHDEFS_H
#define __BSSAP_HASHDEFS_H 

/* BSSAP Message Data Length */
#define BSSAP_DATA_LEN              (0xFFU)

/*  Message Tag */
#define CP_BSSAP_CIC_TAG            (0x01U) /*  CIC header */
#define CP_BSSAP_CFG_TAG            (0x02U) /*  Configuration Header */
#define CP_BSSAP_SCCP_TAG           (0x03U) /*  SCCP Message Header */
#define CP_BSSAP_MSG_TAG            (0x04U) /*  BSSAP Message Header */
#define CP_BSSAP_TIMEOUT_TAG        (0x05U) /*  Timeout Header */
#define CP_BSSAP_NETWORK_TAG        (0x06U) /*  SS7 Network Header */
#define CP_BSSAP_PROTOCOL_TAG       (0x07U) /*  BSSAP Protocol error Header */
#define CP_BSSAP_MANAGEMENT_TAG     (0x08U) /*  Management Tag SCCP/MTP3 */
#define CP_BSSAP_FAILURE_TAG        (0x09U) /*  Failure Tag CS3.0 */

/*  Message Discriminator */
/*  BSSAP Message Discriminator */
#define CP_BSSAP_MD_MAP             (0x00U)
#define CP_BSSAP_MD_DTAP            (0x01U)
#define CP_BSSAP_MD_PROP            (0x02U)
/*  Timeout Message Discriminator */
#define CP_MD_TIMEOUT               (0x02U)
/*  SS7 Network status Message Discriminator */
#define CP_BSSAP_MD_NETWORK         (0x03U)
/*  Error Message Discriminator */
#define CP_BSSAP_MD_PROTOCOL        (0x04U)
/* BSSAP FAILURE Message Discriminator  */
#define CP_BSSAP_FAILURE_IND        (0x32U)
/*  SCCP Message Discriminator (to network) */
#define CP_SCCP_ACCEPT              (0x01U) /*  SCCP-CC */
#define CP_SCCP_RELEASE             (0x02U) /*  SCCP-REL */
#define CP_SCCP_REJECT              (0x03U) /*  SCCP-CREF */
/*  SCCP Message Discriminator (from network) */
#define CP_BSSAP_CON_ESTD           (0x04U) /*  SCCP-CC */
#define CP_BSSAP_CON_REL            (0x05U) /*  SCCP-REL */
#define CP_BSSAP_CON_REF            (0x06U) /*  SCCP-CREF */

/*  BSSAP Messages */
#define BSSAP_MSG_RESERVED          		0x00U
/* Assignment Messages */
#define BSSAP_MSG_ASSIGN_REQ        		0x01U
#define BSSAP_MSG_ASSIGN_COMPLETE   		0x02U
#define BSSAP_MSG_ASSIGN_FAILURE    		0x03U
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
#define BSSAP_MSG_HANDOVER_FAILURE_IND          0x41
/* Release Messages */
#define BSSAP_MSG_CLEAR_COMMAND         	0x20U
#define BSSAP_MSG_CLEAR_COMPLETE        	0x21U
#define BSSAP_MSG_CLEAR_REQUEST         	0x22U
#define BSSAP_MSG_SAPI_N_REJECT         	0x25U
#define BSSAP_MSG_CONFUSION             	0x26U
/* Other Connection Related Messages */
#define BSSAP_MSG_SUSPEND                       0x28U
#define BSSAP_MSG_RESUME                        0x29U
#define BSSAP_MSG_CONNECTION_ORIENTED_INFO      0x2AU
#define BSSAP_MSG_PERFORM_LOCACTION_REQUEST     0x2BU
#define BSSAP_MSG_LSA_INFORMATION               0x2CU
#define BSSAP_MSG_PERFORM_LOCACTION_RESPONSE    0x2DU
#define BSSAP_MSG_PERFORM_LOCACTION_ABORT       0x2EU
#define BSSAP_MSG_COMMON_ID                     0x2FU
/* General Messages */
#define BSSAP_MSG_RESET                         0x30U
#define BSSAP_MSG_RESET_ACK                     0x31U
#define BSSAP_MSG_OVERLOAD                      0x32U
#define BSSAP_MSG_GEN_RESERVED                  0x33U
#define BSSAP_MSG_RESET_CKT                     0x34U
#define BSSAP_MSG_RESET_CKT_ACK                 0x35U
#define BSSAP_MSG_MSC_INVOKE_TRACE              0x36U
#define BSSAP_MSG_BSS_INVOKE_TRACE              0x37U
#define BSSAP_MSG_CONNECTIONLESS_INFORMATION    0x3AU
#define BSSAP_MSG_RESET_IP_RESOURCE		0x3DU
#define BSSAP_MSG_RESET_IP_RESOURCE_ACK		0x3EU
/* Terrestrial Resource Messages */
#define BSSAP_MSG_BLOCK                         0x40U
#define BSSAP_MSG_BLOCK_ACK                     0x41U
#define BSSAP_MSG_UNBLOCK                       0x42U
#define BSSAP_MSG_UNBLOCK_ACK                   0x43U
#define BSSAP_MSG_CKT_GROUP_BLOCK               0x44U
#define BSSAP_MSG_CKT_GROUP_BLOCK_ACK           0x45U
#define BSSAP_MSG_CKT_GROUP_UNBLOCK             0x46U
#define BSSAP_MSG_CKT_GROUP_UNBLOCK_ACK         0x47U
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
/* Call Control Related Messages  */
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
/* Proprietry Messages */
#define BSSAP_CHG_APPID_CALLREFID_REQ		0x81
#define BSSAP_CHG_APPID_CALLREFID_ACK		0x82

/* Network Status Messages */
#define MTP3_MSG_PAUSE              (0x22U)
#define MTP3_MSG_RESUME             (0x23U)
#define MTP3_MSG_STATUS             (0x24U)
#define SCCP_SCMG_SS_ALLOWED        (0x01U)
#define SCCP_SCMG_SS_PROHIBIT       (0x02U)

/*  SS7 status code */
#define CP_MTP_RESUME               MTP3_MSG_RESUME
#define CP_MTP_PAUSE                MTP3_MSG_PAUSE
#define CP_MTP_STATUS               MTP3_MSG_STATUS
#define CP_SCCP_ALLOWED             SCCP_SCMG_SS_ALLOWED
#define CP_SCCP_PROHIBIT            SCCP_SCMG_SS_PROHIBIT

/*  Error code */
#define CP_BSSAP_EENCODE            (0x01U)
#define CP_BSSAP_EDECODE            (0x02U)
#define CP_BSSAP_EINVMESSAGE        (0x03U)
#define CP_BSSAP_ECICNOTFOUND       (0x04U)
#define CP_BSSAP_ENORESETACK        (0x05U)
#define CP_BSSAP_ENOBLKACK          (0x06U)
#define CP_BSSAP_ENOUNBLKACK        (0x07U)
#define CP_BSSAP_ENORESETCKTACK     (0x08U)
#define CP_BSSAP_EUNEQUIPCKT        (0x09U)
#define CP_BSSAP_ENORELEASECMP      (0x0AU)
#define CP_DTAP_EENCODE             (0x0BU)
#define CP_BSSAP_ECKTPROC           (0x0CU)
#define CP_BSSAP_EASSREQFAIL        (0x0DU)
#define CP_BSSAP_ENOCKTGRPBLKACK    (0x0EU)
#define CP_BSSAP_ENOCKTGRPUNBLKACK  (0x0FU)
#define CP_BSSAP_EMSGSENTFAIL       (0x1FU)
#define CP_BSSAP_ECICCKTUNVL        (0x2FU)
#define CP_BSSAP_ECICCKTALCTD       (0x3FU)
#define CP_BSSAP_EPROTOCOLERR       (0x4FU)
#define CP_BSSAP_ENORESETIPACK      (0x5FU)

/* TIMER IDs */
#define   BSSAP_T_1		(0x00U) 
#define   BSSAP_T_4		(0x01U) 
#define   BSSAP_T_10		(0x04U) 
#define   BSSAP_T_11		(0x05U) 
#define   BSSAP_T_13		(0x06U) 
#define   BSSAP_T_17		(0x07U) 
#define   BSSAP_T_18		(0x08U) 
#define   BSSAP_T_19		(0x09U) 
#define   BSSAP_T_20		(0x0AU) 

#endif /* __BSSAP_HASHDEFS_H___  */

