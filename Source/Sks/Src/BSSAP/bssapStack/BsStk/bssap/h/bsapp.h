/*******************************************************************************
**      FILE NAME:
**          bsapp.h
**
**      DESCRIPTION:
**              Defines required by Bssap and Bssap-User.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef __BSAPPH__
#define __BSAPPH__


#define EVTBSAPPREQ 0x81
#define EVTAPPSTART  0x82

#define APP_VERSION_1 0x01
#define APP_VERSION_2 0x02 
#define APP_VERSION_3 0x03 
#define APP_VERSION_4 0x04


#define MTP3_MSG_PAUSE          0x22U
#define MTP3_MSG_RESUME         0x23U
#define MTP3_MSG_STATUS         0x24U

/* types */
#define SCCP_SCMG_SS_ALLOWED       (0x01U)
#define SCCP_SCMG_SS_PROHIBIT      (0x02U)
#define SCCP_SCMG_SS_STATUS_TEST   (0x03U)
#define SCCP_SCMG_SS_OOS_REQ       (0x04U)
#define SCCP_SCMG_SS_OOS_GRANT     (0x05U)
#define SCCP_SCMG_SS_CONGESTED     (0x06U)
#define SCCP_SCMG_SS_BACKUP_ROUTE  (0xFDU)
#define SCCP_SCMG_SS_NORMAL_ROUTE  (0xFEU)
#define SCCP_SCMG_SS_ROUTE_STATUS  (0xFFU)


/* Failure Message Indication */
#define BSSAP_HANDOVER_FAILURE_IND                 0x41
#define APP_BSSAP_ENTID    0x53
#define BSSAP_HDR_LEN  13
#define APP_FIX_HDR_LEN 28

/* 'cause_val' ITS_OCTET coding of bits 7 - 1 */
#define C_RADIO_INTERFACE_MSG_FAIL              0x00U
#define C_RADIO_INTERFACE_FAIL                  0x01U
#define C_UPLINK_QUALITY                        0x02U
#define C_UPLINK_STRENGTH                       0x03U
#define C_DOWNLINK_QUALITY                      0x04U
#define C_DOWNLINK_STRENGTH                     0x05U
#define C_DISTANCE                              0x06U
#define C_OAMP_INTERVENTION                     0x07U
#define C_RESPONSE_MSC_INVOCATION               0x08U
#define C_CALL_CONTROL                          0x09U
#define C_REVERT_TO_OLD_CHANNEL                 0x0AU
#define C_HANDOFF_SUCCESSFUL                    0x0BU
#define C_BETTER_CELL                           0x0CU
#define C_DIRECTED_REENTRY                      0x0DU
#define C_JOINED_GROUP_CALL_CHANNEL             0x0EU
#define C_TRAFFIC                               0x0FU
#define C_EQUIPMENT_FAILURE                     0x20U
#define C_RADIO_RESRC_UNAVAILABLE               0x21U
#define C_TERRESTRIAL_RES_UNAVAILABLE           0x22U
#define C_CCCH_OVERLOAD                         0x23U
#define C_PROCESSOR_OVERLOAD                    0x24U
#define C_BSS_NOT_EQUIPPED                      0x25U
#define C_MS_NOT_EQUIPPED                       0x26U
#define C_INVALID_CELL                          0x27U
#define C_TRAFFIC_LOAD                          0x28U
#define C_PREEMPTION                            0x29U
#define C_TRA_UNAVAILABLE                       0x30U
#define C_CIRCUIT_POOL_MISMATCH                 0x31U
#define C_SWITCH_CIRCUIT_POOL                   0x32U
#define C_REQUESTED_SPEECH_VER_UNAVAIALBLE      0x33U
#define C_CIPHER_ALGORITHM_UNSUPPORTED          0x40U
#define C_TERRESTRIAL_CIRCUIT_ALLOCATED         0x50U /*0x48U *//*Changed by Amaresh for Unknown cause */
#define C_INVALID_MSG_CONTENT                   0x51U
#define C_INFO_ELEMENT_MISSING                  0x52U
#define C_ICORRECT_VALUE                        0x53U
#define C_UNKNOWN_MSG_TYPE                      0x54U
#define C_UNKNOWN_INFO_ELEMENT                  0x55U
#ifdef BSSAP_HA
#define C_CALL_IDENTIFIER_ALREADY_ALLOCATED     0x57U
#endif
#define C_PROTOCOL_ERROR                        0x60U
#define C_VGCS_VBS_CALL_NON_EXISTENT            0x61U


/* Message Headers */
#define CP_BSSAP_CIC_TAG          (0x01U) /* CIC header */
#define CP_BSSAP_CFG_TAG          (0x02U) /* Configuration Header */
#define CP_BSSAP_SCCP_TAG         (0x03U) /* SCCP Message Header */
#define CP_BSSAP_MSG_TAG          (0x04U) /* BSSAP Message Header */
#define CP_BSSAP_TIMEOUT_TAG      (0x05U) /* Timeout Header */
#define CP_BSSAP_NETWORK_TAG      (0x06U) /* SS7 Network Header */
#define CP_BSSAP_PROTOCOL_TAG     (0x07U) /* BSSAP Protocol error Header */
#define CP_BSSAP_MANAGEMENT_TAG   (0x08U)  /*MTP3-SCCP Management Message Tag */
#define CP_BSSAP_FAILURE_TAG      (0x09U)  /* Failure Indication Message */


/* BSSAP Message Discriminator */
#define CP_BSSAP_MD_MAP          (0x00U)
#define CP_BSSAP_MD_DTAP         (0x01U)

/* Timeout Message Discriminator */
#define CP_MD_TIMEOUT            (0x02U)

/* Error Message Discriminator */
#define CP_BSSAP_MD_PROTOCOL        (0x04U)

/* Errro code */
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

/* SS7 Network status Message Discriminator */
#define CP_BSSAP_MD_NETWORK         (0x03U)

#define BS_PRINT_APP_MSGTAG_STR(x) ((x==CP_BSSAP_MSG_TAG)?"CP_BSSAP_MSG_TAG":\
                    ((x==CP_BSSAP_SCCP_TAG)?"CP_BSSAP_SCCP_TAG":\
                    ((x==CP_BSSAP_PROTOCOL_TAG)?"CP_BSSAP_PROTOCOL_TAG":\
                    ((x==CP_BSSAP_PROTOCOL_TAG)?"CP_BSSAP_PROTOCOL_TAG":\
                    ((x==CP_BSSAP_PROTOCOL_TAG)?"CP_BSSAP_FAILURE_TAG":\
                    ((x==CP_BSSAP_MANAGEMENT_TAG)?"CP_BSSAP_MANAGEMENT_TAG":\
                    "UNKNOWN"))))))


#endif /* end of __BSAPPH__*/
