/****************************************************************************
 *                                                                          *
 *                Copyright 2001 IntelliNet Technologies, Inc.              *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: BSSAP.h,v 1.2 2008/01/29 04:18:07 amaresh.prasad Exp $
 *
 * LOG: $Log: BSSAP.h,v $
 * LOG: Revision 1.2  2008/01/29 04:18:07  amaresh.prasad
 * LOG: Updated for cause value
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:12  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.2.6  2006/09/14 16:06:59  sjaddu
 * LOG: Fix for IssueId:3897 (MCC/MNC with 3 digits).
 * LOG:
 * LOG: Revision 9.1.2.5  2005/11/30 07:33:56  adutta
 * LOG: Added Authentication Failue message
 * LOG:
 * LOG: Revision 9.1.2.4  2005/11/18 05:03:35  adutta
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 9.1.2.3  2005/10/19 11:58:47  adutta
 * LOG: Added Skip indicator
 * LOG:
 * LOG: Revision 9.1.2.2  2005/10/14 10:25:12  adutta
 * LOG: Bug fix
 * LOG:
 * LOG: Revision 9.1.2.1  2005/09/21 12:32:02  adutta
 * LOG: Paging response added
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1  2003/10/17 20:09:14  hcho
 * LOG: Fixed the wrong bits-mask symbol caused Inter-MSC handoff failure.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:34  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/10 16:57:36  ngoel
 * LOG: DTAP merge
 * LOG:
 * LOG: Revision 1.1.2.36  2002/06/06 20:45:05  ngoel
 * LOG: after MM changes
 * LOG:
 * LOG: Revision 1.1.2.35  2002/06/04 16:49:32  ngoel
 * LOG: coorrect IEI value
 * LOG:
 * LOG: Revision 1.1.2.34  2002/05/24 20:36:41  ngoel
 * LOG: after MM fixes
 * LOG:
 * LOG: Revision 1.1.2.33  2002/05/23 22:06:55  ngoel
 * LOG: fix tid in l3 header
 * LOG:
 * LOG: Revision 1.1.2.32  2002/05/23 20:11:53  ngoel
 * LOG: add ti mask
 * LOG:
 * LOG: Revision 1.1.2.31  2002/05/17 21:11:35  ngoel
 * LOG: correct errors
 * LOG:
 * LOG: Revision 1.1.2.30  2002/05/17 13:18:54  ngoel
 * LOG: remove tabs
 * LOG:
 * LOG: Revision 1.1.2.29  2002/05/16 15:41:39  ngoel
 * LOG: add priority level ie
 * LOG:
 *
 ****************************************************************************/
#ifndef ITS_BSSAP_H
#define ITS_BSSAP_H

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * This file contains the information element Coding
 * for the GSM A-interface.
 * Refer : GSM08.08 version 8.9.0 Release 1999.
 *         Section 3.2.2
 *
 * NOTE: The module uses macros for setting and getting the
 * data in the information elements. Since the macro does 
 * not have any type checking the user needs to be careful
 * with its usuage.
 */

/*
 * Maximum size that any information element may take.  This is
 * used to pad the information element size for those IE's that
 * have length 1 arrays as their last member
 */
#define BSSAP_MAX_IE_SIZE                       240

/*
 * Message Discriminator
 */
#define BSSAP_MD_BSSMAP    0x00U
#define BSSAP_MD_DTAP      0x01U

#define BSSAP_FAILURE_IND  (0x32U) /* Added by Amaresh 03-07-08 */
#define BSSAP_MD_BS_SCCP    0x02U
/*
 * Message type
 *
 */
/*Added by Amaresh 04-07-08 */
/* Failure Message Indication */
#define BSSAP_HANDOVER_FAILURE_IND                 0x41
/*Added by Amaresh 04-07-08 */

#define BSSAP_MSG_RESERVED                      0x00U

/* Assignment Messages */
#define BSSAP_MSG_ASSIGN_REQUEST                0x01U
#define BSSAP_MSG_ASSIGN_COMPLETE               0x02U
#define BSSAP_MSG_ASSIGN_FAILURE                0x03U

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

/* Release Messages */
#define BSSAP_MSG_CLEAR_COMMAND                 0x20U
#define BSSAP_MSG_CLEAR_COMPLETE                0x21U
#define BSSAP_MSG_CLEAR_REQUEST                 0x22U
//#define BSSAP_MSG_REL1_RESERVED                 0x23U
//#define BSSAP_MSG_REL2_RESERVED                 0x24U
#define BSSAP_MSG_SAPI_N_REJECT                 0x25U
#define BSSAP_MSG_CONFUSION                     0x26U

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

/*
 * Information Elelments
 * Section 3.2.2
 */
#define BSSAP_IEI_CIRCUIT_IDENTITY_CODE         0x01U
/* #define BSSAP_IEI_RESERVED                     0x02U  */
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
/* #define BSSAP_IEI_RESREVED                     0x0FU */
/* #define BSSAP_IEI_RESERVED                     0x10U */
/* #define BSSAP_IEI_RESERVED                     0x11U */
#define BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2   0x12U
#define BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3   0x13U
#define BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED  0x14U
#define BSSAP_IEI_RR_CAUSE                      0x15U
/* #define BSSAP_IEI_RESERVED                     0x16U */
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
#define BSSAP_IEI_MOBILE_IDENTITY               0x17U
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
#define BSSAP_IEI_GERAN_CLASSMARK               0x53U //Added by Amaresh 29-04-08
#define BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO       0x61U
#define BSSAP_IEI_INTER_SYSTEM_INFO             0x63U
#define BSSAP_IEI_SNA_ACCESS_INFO               0x64U //Added by Amaresh 29-04-08
// Field Element - Section 3.2.3
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

/*
 * Call Control related IEI
 */
#define BSSAP_IEI_EXT_MASK                            0x80
#define BSSAP_IEI_CC_SHIFT                            0x90
#define BSSAP_IEI_CC_REPEAT_INDICATOR                 0xd0
#define BSSAP_IEI_CC_MORE_DATA                        0xa0
#define BSSAP_IEI_CC_CLIR_SUPPRESSION                 0xa1
#define BSSAP_IEI_CC_CLIR_INVOCATION                  0xa2
#define BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION     0xa3
#define BSSAP_IEI_CC_BEARER_CAPABILITY                0x04
#define BSSAP_IEI_CC_CAUSE                            0x08
#define BSSAP_IEI_CC_CAPABILITIES                     0x15
#define BSSAP_IEI_CC_ALERTING_PATTERN                 0x19
#define BSSAP_IEI_CC_FACILITY                         0x1c
#define BSSAP_IEI_CC_PROGRESS_INDICATOR               0x1e
#define BSSAP_IEI_CC_AUXILLARY_STATES                 0x24
#define BSSAP_IEI_CC_KEYPAD_FACILITY                  0x2c
#define BSSAP_IEI_CC_STREAM_IDENTIFIER                0x2d
#define BSSAP_IEI_CC_EMERGENCY_CATEGORY               0x2e
#define BSSAP_IEI_CC_NETWORK_CC_CAPABILITIES          0x2f
#define BSSAP_IEI_CC_SIGNAL                           0x34
#define BSSAP_IEI_CC_CAUSE_CLI                        0x3a
#define BSSAP_IEI_CC_SUPPORTED_CODECS                 0x40
#define BSSAP_IEI_CC_BACKUP_BEARER_CAPABILITIES       0x41
#define BSSAP_IEI_CC_CONNECTED_NUMBER                 0x4c
#define BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS            0x4d
#define BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER         0x5c
#define BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS        0x5d
#define BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER          0x5e
#define BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS         0x6d
#define BSSAP_IEI_CC_REDIRECTING_PARTY_BCD_NUMBER     0x74
#define BSSAP_IEI_CC_REDIRECTING_PARTY_SUB_ADDRESS    0x75
#define BSSAP_IEI_CC_ALLOWED_ACTIONS                  0x7b
#define BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY          0x7c
#define BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY         0x7d
#define BSSAP_IEI_CC_USER_USER                        0x7e
#define BSSAP_IEI_CC_SS_VERSION_IND                   0x7f
#define BSSAP_IEI_CC_SETUP_CONTAINER_INTERNAL         0xfe
#define BSSAP_IEI_CC_CONGESTION_LEVEL_INTERNAL        0xfd
#define BSSAP_IEI_CC_NOTIFICATION_INDICATOR_INTERNAL  0xfc
#define BSSAP_IEI_CC_CALL_STATE_INTERNAL              0xff
#define BSSAP_IEI_CC_PRIORITY_LEVEL                   0x80

/**********************************************************************
**
** START OF DTAP SECTION
**
***********************************************************************/
// IE
#define BSSAP_IEI_FOLLOW_ON_PROCEED             0xA1U
#define BSSAP_IEI_CTS_PERMISSION                0xA2U
#define BSSAP_IEI_LOCATION_AREA_IDENTIFIER      0x13U
#define BSSAP_IEI_AUTH_FAILURE_PARAMETER        0x22U

/*NOT IMPLEMENTED IEI IN EARLIER VERSION TABLE ANNEX K*/
#define BSSAP_IEI_LOCATION_UPDATING_TYPE        0xC0U 
#define BSSAP_IEI_CYPHERING_KEY_SEQUENCE        0x90U
#define BSSAP_IEI_PARAMETER_RAND                0xFAU
#define BSSAP_IEI_PARAMETER_SRES                0xF0U
#define BSSAP_IEI_IDENTITY_TYPE                 0xF1U
#define BSSAP_IEI_CM_SERVICE_TYPE               0xF2U
#define BSSAP_IEI_REJECT_CAUSE                  0xF3U
#define BSSAP_IEI_TIME_ZONE                     0xA3U
#define BSSAP_IEI_TIME_ZONE_TIME                0xA4U

// Messages section 10.2
//Registration Messages
#define BSSAP_MSG_IMSI_DETACH_INDICATION        0x01U
#define BSSAP_MSG_LOCATION_UPDATING_ACCEPT      0x02U
#define BSSAP_MSG_LOCATION_UPDATING_REJECT      0x04U
#define BSSAP_MSG_LOCATION_UPDATING_REQUEST     0x08U

// Security Messages
#define BSSAP_MSG_AUTHENTICATION_REJECT         0x11U
#define BSSAP_MSG_AUTHENTICATION_REQUEST        0x12U
#define BSSAP_MSG_AUTHENTICATION_RESPONSE       0x14U
#define BSSAP_MSG_AUTHENTICATION_FAILURE        0x1CU
#define BSSAP_MSG_IDENTITY_REQUEST              0x18U
#define BSSAP_MSG_IDENTITY_RESPONSE             0x19U
#define BSSAP_MSG_TMSI_REALLOC_COMMAND          0x1AU
#define BSSAP_MSG_TMSI_REALLOC_COMPLETE         0x1BU

// Connection Management Messages
#define BSSAP_MSG_CM_SERVICE_ACCEPT             0x21U        
#define BSSAP_MSG_CM_SERVICE_REJECT             0x22U
#define BSSAP_MSG_CM_SERVICE_ABORT              0x23U
#define BSSAP_MSG_CM_SERVICE_REQUEST            0x24U
#define BSSAP_MSG_CM_REESTABLISHMENT_REQ        0x28U
#define BSSAP_MSG_ABORT                         0x29U

// Miscellaneous Messages
#define BSSAP_MSG_MM_INFORMATION                0x32U
#define BSSAP_MSG_MM_STATUS                     0x31U
#define BSSAP_MSG_MM_NULL                       0x30U

/***********************************************************************
 * Location Updating Type
 * Ref: 10.5.3.5
 */
typedef struct
{
    ITS_OCTET    lut;
}
BSSAP_LocUpdatingType;

#define BSSAP_LOCATION_UPDATING_MASK            0x0FU
#define BSSAP_IEI_LOCATION_UPDATING_MASK        0xF0U
#define BSSAP_NORMAL_LOCATION_UPDATING          0x00U
#define BSSAP_PERIDODIC_UPDATING                0x01U
#define BSSAP_IMSI_ATTACH                       0x02U
#define BSSAP_RESERVED                          0x03U
#define BSSAP_NO_FOLLOW_ON_REQUEST              0x00U
#define BSSAP_FOLLOW_ON_REQUEST                 0x01U

#define BSSAP_SET_LOCATION_UPDATING_TYPE(x,y)              \
     (((x).lut &= BSSAP_LOCATION_UPDATING_MASK),           \
      (x).lut |= ((y) & BSSAP_LOCATION_UPDATING_MASK) ,    \
      (x).lut |= (BSSAP_IEI_LOCATION_UPDATING_MASK &       \
         BSSAP_IEI_LOCATION_UPDATING_TYPE))

#define BSSAP_GET_LOCATION_UPDATING_TYPE(x)                \
    ((x).lut & BSSAP_LOCATION_UPDATING_MASK)

/***********************************************************************
 * Cyphering Key Sequence
 * Ref: 10.5.1.2
 */
typedef struct
{
    ITS_OCTET    cks;
}
BSSAP_CypKeySequence;

#define BSSAP_CYPHERING_KEY_SEQUENCE_MASK        0x07U
#define BSSAP_IEI_CYPHERING_KEY_SEQUENCE_MASK    0x70U
#define BSSAP_NO_KEY_AVAILABLE                   0x07U

#define BSSAP_SET_CYPHERING_KEY_SEQUENCE(x,y)                  \
    (((x).cks &= BSSAP_CYPHERING_KEY_SEQUENCE_MASK),           \
      (x).cks |= ((y) & BSSAP_CYPHERING_KEY_SEQUENCE_MASK) ,   \
      (x).cks |= (BSSAP_IEI_CYPHERING_KEY_SEQUENCE_MASK &      \
          BSSAP_IEI_CYPHERING_KEY_SEQUENCE))

#define BSSAP_GET_CYPHERING_KEY_SEQUENCE(x)         \
    ((x).cks & BSSAP_CYPHERING_KEY_SEQUENCE_MASK)

/***********************************************************************
 * Location Area Identifier
 * Ref: 10.5.1.3
 */
typedef struct
{
    ITS_OCTET    MCC[2];    // Mobile COuntry Code 
    ITS_OCTET    MNC;       // Mobile Network Code         
    ITS_OCTET    LAC[2];    // Location Area Code 
}
BSSAP_LocationAreaId;

// MCC and MNC -- For GSM 900 and DCS 1800
// Populate bit 1 - bit 12

// MCC
#define LAI_SET_MCC(x,y)                  \
    ((x).MCC[1] = (((y) >> 8)  & 0x0FU),  \
     (x).MCC[0] = ((y) & 0xFFU))

#define LAI_GET_MCC(x)                    \
    ((((x).MCC[1] << 8) & 0x0FU)  | ((x).MCC[0] & 0xFFU))

// MNC
#define LAI_SET_MNC(x,y)                   \
    ((x).MNC[0] = ((y)  & 0xF0U),          \
     (x).MNC[1] = (((y) >> 8) & 0xFFU))

#define LAI_GET_MNC(x)                     \
    (((x).MNC[1] << 8 )  | ((x).MNC[0] & 0xF0U))

// LAC
#define LAI_SET_LAC(x,y)                   \
    ((x).LAC[1] = (((y) >> 8) & 0xFFU),    \
     (x).LAC[0] = ((y) & 0xFFU))

#define LAI_GET_LAC(x)                     \
    (((x).LAC[1] << 8 ) | (x).LAC[0])

/***********************************************************************
 * PArameter Rand
 * Ref: 10.5.3.1
 */
typedef struct
{
    ITS_OCTET    data[16];
}
BSSAP_ParameterRAND;

/***********************************************************************
 * PArameter Sres
 * Ref: 10.5.3.2
 */
typedef struct
{
    ITS_OCTET    data[4];
}
BSSAP_ParameterSRES;

/***********************************************************************
 * Identity Type
 * Ref: 10.5.3.4
 */
typedef struct
{
    ITS_OCTET    idt;
}
BSSAP_IDType;

#define BSSAP_IDENTITY_TYPE_IMSI                0x01U
#define BSSAP_IDENTITY_TYPE_IMEI                0x02U
#define BSSAP_IDENTITY_TYPE_IMEISV              0x03U
#define BSSAP_IDENTITY_TYPE_TMSI                0x04U

/***********************************************************************
 * CM Service Type
 * Ref: 10.5.3.3
 */
typedef struct
{
    ITS_OCTET    cst;
}
BSSAP_CmServiceType;

#define BSSAP_CM_TYPE_MOBILE_ORIGINATING        0x01U
#define BSSAP_CM_TYPE_EMERGENCY                 0x02U
#define BSSAP_CM_TYPE_SMS                       0x04U
#define BSSAP_CM_TYPE_SSA                       0x08U
#define BSSAP_CM_TYPE_VOICE_GROUP_CALL          0x09U
#define BSSAP_CM_TYPE_VOICE_BROADCAST_CALL      0x0AU
#define BSSAP_CM_TYPE_LOCATION_SERVICE          0x0BU

/***********************************************************************
 * Timezone
 * Ref: 10.5.3.8
 */
typedef struct
{
    ITS_OCTET    tz;
}
BSSAP_TimeZo;

/***********************************************************************
 * TimezoneTime
 * Ref: 10.5.3.9
 */
typedef struct
{
    ITS_OCTET    year;
    ITS_OCTET    month;
    ITS_OCTET    day;
    ITS_OCTET    hour;
    ITS_OCTET    minute;
    ITS_OCTET    second;
    ITS_OCTET    zone;
}
BSSAP_TimeZoTime;

/**********************************************************************
*
*  END OF DTAP SECTION
*
***********************************************************************/

/***********************************************************************
 *  Circuit Identity Code.
 *  Ref: 3.2.2.2
 */
typedef struct
{
    ITS_OCTET    data_2field[2];
}
BSSAP_CircuitIdentityCode;

#define CIC_PCM_HI_BITS                         0xFFU
#define CIC_PCM_LO_BITS                         0xE0U

/*
 * x - BSSAP_CircuitIdentityCode
 * y - PCM Id or TimeSlot
 */
#if defined (CCITT)
#define CIC_SET_PCM_ID(x,y)                                 \
    (((x).data_2field[0] = ((y) >> 3) & CIC_PCM_HI_BITS),   \
      (x).data_2field[1] &= ~CIC_PCM_LO_BITS,               \
      (x).data_2field[1] |= (((y) << 5) & CIC_PCM_LO_BITS))

#define CIC_GET_PCM_ID(x)                                   \
    (((x).data_2field[0] << 3) |                            \
     ((x).data_2field[1] & CIC_PCM_LO_BITS) >> 5)

#define CIC_TIMESLOT_BIT                        0x1FU

#define CIC_SET_TIMESLOT(x,y)                               \
    ((x).data_2field[1] &= ~CIC_TIMESLOT_BIT,               \
     (x).data_2field[1] |= (y) & CIC_TIMESLOT_BIT)

#define CIC_GET_TIMESLOT(x)                                 \
    ((x).data_2field[1] & CIC_TIMESLOT_BIT)

#else

#define CIC_SET_PCM_ID(x,y)                                 \
    (((x).data_2field[1] = ((y) >> 3) & CIC_PCM_HI_BITS),   \
      (x).data_2field[0] &= ~CIC_PCM_LO_BITS,               \
      (x).data_2field[0] |= (((y) << 5) & CIC_PCM_LO_BITS))

#define CIC_GET_PCM_ID(x)                                   \
    (((x).data_2field[1] << 3) |                            \
     ((x).data_2field[0] & CIC_PCM_LO_BITS) >> 5)

#define CIC_TIMESLOT_BIT                        0x1FU

#define CIC_SET_TIMESLOT(x,y)                               \
    ((x).data_2field[0] &= ~CIC_TIMESLOT_BIT,               \
     (x).data_2field[0] |= (y) & CIC_TIMESLOT_BIT)

#define CIC_GET_TIMESLOT(x)                                 \
    ((x).data_2field[0] & CIC_TIMESLOT_BIT)

#endif

/***********************************************************************
 * Connection Release Requested
 * Ref: 3.2.2.3
 * 
 * This is a fixed size (1 octet for Element ID) element. It has no data.
 */

/***********************************************************************
 * Resource Available
 * Ref: 3.2.2.4
 * 
 * Here,
 * Octet 0, 1 - Number of Full Rate Channels available in Band 1
 * Octet 2, 3 - Number of Half Rate Channels available in Band 1
 * Octet 4, 5 - Number of Full Rate Channels available in Band 2
 *  etc...for up to Band 5, and up to Octet 20
 */

typedef struct
{
    ITS_OCTET    full[2];
    ITS_OCTET    half[2];
}
BSSAP_Full_Half;

typedef struct
{
    BSSAP_Full_Half    data_10field[5];
}
BSSAP_ResourceAvailable;

/* x  - BSSAP_ResourceAvailable,
 * y  - Band Number,
 * zf - Number of Full rate channels available
 * zh - Number of Half Rate channels available
 */
#define RA_SET_FULL_HALF_RATE_CHANNELS_AVAILABLE_FOR_BAND(x,y,zf,zh)  \
  (((x).data_10field[y].full[0] = (((zf) >> 8) & 0xFF))),             \
   ((x).data_10field[y].full[1] = ((zf) & 0xFF)),                     \
   (((x).data_10field[y].half[0] = (((zh) >> 8) & 0xFF))),            \
   ((x).data_10field[y].half[1] = ((zh) & 0xFF))                                 
#define RA_GET_FULL_HALF_RATE_CHANNELS_AVAILABLE_FOR_BAND(x,y)        \
    ((x).data_10field[y])

#define RA_GET_FULL_RATE_CHANNELS_AVAILABLE_FOR_BAND(x,y)             \
    (((x).data_10field[y].full[0] << 8)) |                            \
    ((x).data_10field[y].full[1])

#define RA_GET_HALF_RATE_CHANNELS_AVAILABLE_FOR_BAND(x,y)             \
    (((x).data_10field[y].half[0] << 8)) |                            \
    ((x).data_10field[y].half[1])

/***********************************************************************
 * Cause
 * Ref: 3.2.2.5
 * 
 * If the Extension bit is 0, then Cause is 1 octet
 * If the Extension bit is 1, then Cause is 2 octet.
 */

typedef struct
{
    ITS_OCTET    cause_val[1];
}
BSSAP_Cause;

/* extension bit in 1st ITS_OCTET of 'cause_val' */
#define C_NOT_EXTENDED                          0x00U
#define C_IS_EXTENDED                           0x01U
#define C_EXT_BIT                               0x80U

#define C_SET_EXTENSION(x,y)                         \
    (((x).cause_val[0] &= ~C_EXT_BIT),               \
      (x).cause_val[0] |= (((y) << 7) & C_EXT_BIT))

#define C_GET_EXTENSION(x)                           \
    (((x).cause_val[0] & C_EXT_BIT) >> 7)

/*if ext(bit 7) is 0, the cause value is a single octet element*/
#define C_CAUSE_VAL_WITH_0_BIT                  0x7FU

#define C_SET_BASIC_CAUSE(x,y)                       \
    (((x).cause_val[0] &= ~C_CAUSE_VAL_WITH_0_BIT),  \
     (x).cause_val[0] |= ((y) & C_CAUSE_VAL_WITH_0_BIT))

#define C_GET_BASIC_CAUSE(x)                         \
    ((x).cause_val[0])

/*if ext(bit 7) is 1, the cause value is a 2 octet field
 *if 1st octet is 1XXX 0000, the 2nd is reserved for national appli.*/
#define C_CAUSE_VAL_WITH_1_BIT                  0x70U

#define C_SET_EXT_CAUSE_CLASS(x,y)                              \
    (((x).cause_val[0] &= ~C_CAUSE_VAL_WITH_1_BIT),             \
     (x).cause_val[0] |= ((y) << 4 ) & C_CAUSE_VAL_WITH_1_BIT,  \
     (x).cause_val[0] &= 0xF0U)

#define C_GET_EXT_CAUSE_CLASS(x)                                \
    (((x).cause_val[0] & C_CAUSE_VAL_WITH_1_BIT) >> 4)

/* 
 * The Cause's Class.
 * if 1st ITS_OCTET is 1XXX 0000, then xxx is:
 */
#define C_CLASS_NORMAL_EVENT1                   0x00U
#define C_CLASS_NORMAL_EVENT2                   0x01U
#define C_CLASS_RESRC_UNAVAILABLE               0x02U
#define C_CLASS_SERVICE_UNAVAILABLE             0x03U
#define C_CLASS_SERVICE_UNIMPLEMENTED           0x04U
#define C_CLASS_INVALID_MESSAGE                 0x05U
#define C_CLASS_PROTOCOL_ERROR                  0x06U
#define C_CLASS_INTERWORKING                    0x07U

/*
 * when the extension bit is set, the cause appears in the second
 * byte
 */
#define C_SET_EXT_CAUSE(x,y)                           \
    ((x).cause_val[1] = ((y) & 0xFFU))

#define C_GET_EXT_CAUSE(x)                             \
    ((x).cause_val[1])

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
/* #define C_RESERVED_INTERNATIONAL           0x10 to 0x17 */
/* #define C_RESERVED_NATIONAL                0x18 to 0x1F */
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
/* #define C_RESERVED_NATIONAL                0x2A to 0x2F */
#define C_TRA_UNAVAILABLE                       0x30U
#define C_CIRCUIT_POOL_MISMATCH                 0x31U
#define C_SWITCH_CIRCUIT_POOL                   0x32U
#define C_REQUESTED_SPEECH_VER_UNAVAIALBLE      0x33U
/* #define C_RESERVED_INTERNATIONAL           0x34 to 0x3F */
#define C_CIPHER_ALGORITHM_UNSUPPORTED          0x40U
/* #define C_RESERVED_INTERNATIONAL           0x41 to 0x47 */
#define C_TERRESTRIAL_CIRCUIT_ALLOCATED         0x50U /*0x48U *//*Changed by Amaresh for Unknown cause */
#define C_INVALID_MSG_CONTENT                   0x51U
#define C_INFO_ELEMENT_MISSING                  0x52U
#define C_ICORRECT_VALUE                        0x53U
#define C_UNKNOWN_MSG_TYPE                      0x54U
#define    c_UNKNOWN_INFO_ELEMENT               0x55U
/* #define C_RESERVED_INTERNATIONAL           0x56 to 0x57 */
/* #define C_RESERVED_NATIONAL                0x58 to 0x5F */
#define C_PROTOCOL_ERROR                        0x60U
#define C_VGCS_VBS_CALL_NON_EXISTENT            0x61U
/* #define C_RESERVED_INTERNATIONAL           0x62 to 0x67 */
/* #define C_RESERVED_NATIONAL                0x68 to 0x6F */
/* #define C_RESERVED_INTERNATIONAL           0x70 to 0x77 */
/* #define C_RESERVED_NATIONAL                0x78 to 0x7F */

/***********************************************************************
 * Reject Cause
 * Ref: 10.5.3.6
 */
typedef struct
{
    ITS_OCTET rc_value;
}
BSSAP_RejectCause_IE;

// Reject Cause Values
#define IMSI_UNKNOWN_IN_HLR                        0x02U
#define ILLEGAL_MS                                 0x03U
#define IMSI_UNKNOWN_IN_VLR                        0x04U
#define IMEI_NOT_ACCEPTED                          0x05U
#define ILLEGAL_ME                                 0x06U
#define PLMN_NOT_ALLOWED                           0x0BU
#define LOCATION_AREA_NOT_ALLOWED                  0x0CU
#define ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA  0x0DU
#define NO_SUITABLE_CELLS_IN_LOCATION_AREA         0x0FU
#define NETWORK_FAILURE                            0x11U
#define MAC_FAILURE                                0x14U
#define SYNCH_FAILURE                              0x15U
#define CONGESTION                                 0x16U
#define GSM_AUTHENTICATION_UNACCEPTABLE            0x17U
#define SERVICE_OPTION_NOT_SUPPORTED               0X20U
#define REQUESTED_SERVICE_OPTION_NOT_SUBSCRIBED    0x21U
#define SERVICE_OPTION_TEMPORARILY_OUT_OF_ORDER    0x22U
#define CALL_CANNOT_BE_IDENTIFIED                  0x26U
// 0x30 to 0x3F retry upon entry into a new cell 
#define SEMANTICALLY_INCORRECT_MESSAGE             0x5FU
#define INVALID_MANDATORY_INFO                     0x60U
#define MESSAGE_TYPE_NON_EXISTENT                  0x61U
#define MESSAGE_TYPE_NOT_COMPATIBLE                0x62U
#define IE_NON_EXISTENT                            0x63U
#define CONDITIONAL_IE_ERROR                       0x64U
#define MESSAGE_NOT_COMPATIBLE                     0x65U
#define PROTOCOL_ERROR                             0x6FU 

/***********************************************************************
 * Authentication Failure Parameter
 * Ref: 10.5.3.2.2
 */
typedef struct
{
    ITS_OCTET data[14];
}
BSSAP_AuthFailParameter_IE;

/***********************************************************************
 * IMSI
 * Ref: 3.2.2.6
 * 
 */
typedef struct
{
    ITS_OCTET    digits[1];
}
BSSAP_Imsi;

/*
 * Convert Ascii Digits to Packed BCD equivalent.
 *
 * Eg: in = "1234", out = 0x12, 0x24, len = 2
 *     in = "123", out = 0x12, 0x3F, len =2
 */
ITS_BOOLEAN BSSAP_AsciiDigitsToBcd(const ITS_OCTET* in, ITS_OCTET* out, 
                                   ITS_UINT& len);

/***********************************************************************
 * TMSI
 * Ref: 3.2.2.7
 * 
 * The TMSI element data is un-structured. It is left to the application
 * to handle it.
 */   
typedef struct
{
    ITS_OCTET    data_4field[4];
}
BSSAP_Tmsi;

#define TMSI_SET_TMSI(x,y)                        \
    ((x).data_4field[0] = (((y) >> 24) & 0xFFU)), \
    ((x).data_4field[1] = (((y) >> 16) & 0xFFU)), \
    ((x).data_4field[2] = (((y) >> 8) & 0xFFU)),  \
    ((x).data_4field[3] = (y))

#define TMSI_GET_TMSI(x)                                       \
     (((x).data_4field[0] << 24) | ((x).data_4field[1] << 16)  \
       |((x).data_4field[2] << 8) | ((x).data_4field[3]))

/***********************************************************************
 * Number Of MSs
 * Ref: 3.2.2.8
 * 
 */
typedef struct
{
    ITS_OCTET    numOfMSs;
}
BSSAP_NumberOfMSs;

/***********************************************************************
 * Layer 3 Header Information.
 * Ref: 3.2.2.9
 * 'protocol_discriminator' is coded as 
 * 'transaction_identifier' is coded as
 */
typedef struct
{
    ITS_OCTET    protocol_discriminator;
    ITS_OCTET    transaction_identifier;
}
BSSAP_Layer3HeaderInfo;

/*
 * protocol discriminator. GSM 04.08, Section 10.2
 */
#define PD_CALL_CONTROL_MSGS                    0x03U
#define PD_MOBILITY_MGMT_MSGS_NON_GPRS          0x05U
#define PD_RADIO_RESRC_MGMT_MSGS                0x06U
#define PD_MOBILITY_MGMT_MSGS_GPRS              0x08U
#define PD_SESSION_MGMT_MSGS                    0x0AU
#define PD_PROT_DISCR_BIT                       0x0FU

#define PD_SET_PROT_DISCR(x,y)          \
    ((x) = (y) & PD_PROT_DISCR_BIT )

#define PD_GET_PROT_DISCR(x)            \
    ((x) & PD_PROT_DISCR_BIT )

/* Transaction Identifier - GSM 04.08 Section 10.3.2 */
/* Defined in GSM 04.07 Section 11.2.3.1.3. */
/*
 * Equivalent to Call Reference in Q.931.
 * Bits 0 - 3 are reserved. Bit 7 is TI flag, bits 4 - 6 is TI value.
 */

/* SKIP Value */

#define SKIP_VALUE_0                            0x00U

/* TI Value */
#define TI_VALUE_0                              0x00U
#define TI_VALUE_1                              0x01U
#define TI_VALUE_2                              0x02U
#define TI_VALUE_3                              0x03U
#define TI_VALUE_4                              0x04U
#define TI_VALUE_5                              0x05U
#define TI_VALUE_6                              0x06U

#define TI_VALUE_BITS                           0x70U
#define TI_VALUE_MASK                           0x07U

/* TI Flag */
#define TI_FLAG_FRM_SIDE                        0x00U
#define TI_FLAG_TO_SIDE                         0x01U
#define TI_FLAG_BITS                            0x80U
#define TI_FLAG_MASK                            0x08U

#define TI_SET_TI_VALUE(x,y)         \
    (((x) &= ~TI_VALUE_BITS ),       \
     (x) |= (y) << 4)

#define TI_GET_TI_VALUE(x)           \
    (((x) & TI_VALUE_BITS) >> 4)

#define TI_SET_TI_FLAG(x,y)          \
    (((x) &= ~TI_FLAG_BITS ),        \
      (x) |= (y) << 7)

#define TI_GET_TI_FLAG(x)            \
    (((x) & TI_FLAG_BITS) >> 7)

#define TI_SET_TI_VALUE_L3_HEADER(x,y)   \
    (((x) &= ~TI_VALUE_MASK ),           \
     (x) |= (y))

#define TI_GET_TI_VALUE_L3_HEADER(x)     \
    (((x) & TI_VALUE_MASK))

#define TI_SET_TI_FLAG_L3_HEADER(x,y)    \
    (((x) &= ~TI_FLAG_MASK ),            \
      (x) |= (y) << 3)

#define TI_GET_TI_FLAG_L3_HEADER(x)      \
    (((x) & TI_FLAG_MASK) >> 3)

/* Here we set/get the Layer3 Header Info.*/
#define L3HI_SET_PROT_DISCR(x,y)         \
    (PD_SET_PROT_DISCR((x).protocol_discriminator, (y)))

#define L3HI_GET_PROT_DISCR(x)                                      \
    (PD_GET_PROT_DISCR((x).protocol_discriminator ))

#define L3HI_SET_TRAN_ID_VALUE(x,y)                                 \
    (TI_SET_TI_VALUE_L3_HEADER((x).transaction_identifier, (y)))

#define L3HI_GET_TRAN_ID_VALUE(x)                                   \
    (TI_GET_TI_VALUE_L3_HEADER((x).transaction_identifier))

#define L3HI_SET_TRAN_ID_FLAG(x,y)                                  \
    (TI_SET_TI_FLAG_L3_HEADER((x).transaction_identifier, (y)))

#define L3HI_GET_TRAN_ID_FLAG(x)                                    \
    (TI_GET_TI_FLAG_L3_HEADER((x).transaction_identifier ))

/***********************************************************************
 * Encryption Information.
 * Ref: 3.2.2.10
 *
 * note that the parameter length should be the length of the key + 1
 */
typedef struct
{
    ITS_OCTET    permittedAlgorithms;
    ITS_OCTET    key[1];
}
BSSAP_EncryptionInfo;

/* 'permitted algorithm'. These are bit positions */
#define EI_NO_ENCRYPTION_BIT                    0x01U
#define EI_A5_1_BIT                             0x02U
#define EI_A5_2_BIT                             0x04U
#define EI_A5_3_BIT                             0x08U
#define EI_A5_4_BIT                             0x10U
#define EI_A5_5_BIT                             0x20U
#define EI_A5_6_BIT                             0x40U
#define EI_A5_7_BIT                             0x80U

/* x - BSSAP_EncryptionInfo.
 * y - Type of Encryption being set.
 */
#define EI_SET_NO_ENCRYPTION(x,y)                        \
    (((x).permittedAlgorithms &= ~EI_NO_ENCRYPTION_BIT), \
     (x).permittedAlgorithms |= (y) )

#define EI_GET_NO_ENCRYPTION(x)                          \
    ((x).permittedAlgorithms & EI_NO_ENCRYPTION_BIT)   

#define EI_SET_A5_1(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_1_BIT),          \
      (x).permittedAlgorithms |= (y) << 1 )

#define EI_GET_A5_1(x)                                   \
    (((x).permittedAlgorithms & EI_A5_1_BIT) >> 1) 

#define EI_SET_A5_2(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_2_BIT),          \
      (x).permittedAlgorithms |= (y) << 2 )

#define EI_GET_A5_2(x)                                   \
    (((x).permittedAlgorithms & EI_A5_2_BIT) >> 2) 

#define EI_SET_A5_3(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_3_BIT),          \
      (x).permittedAlgorithms |= (y) << 3 )

#define EI_GET_A5_3(x)                                   \
    (((x).permittedAlgorithms & EI_A5_3_BIT) >> 3)

#define EI_SET_A5_4(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_4_BIT),          \
      (x).permittedAlgorithms |= (y) << 4 )

#define EI_GET_A5_4(x)                                   \
    (((x).permittedAlgorithms & EI_A5_4_BIT) >> 4) 

#define EI_SET_A5_5(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_5_BIT),          \
      (x).permittedAlgorithms |= (y) << 5 )

#define EI_GET_A5_5(x)                                   \
    (((x).permittedAlgorithms & EI_A5_5_BIT) >> 5)  

#define EI_SET_A5_6(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_6_BIT),          \
      (x).permittedAlgorithms |= (y) << 6 )

#define EI_GET_A5_6(x)                                   \
    (((x).permittedAlgorithms & EI_A5_6_BIT) >> 6) 

#define EI_SET_A5_7(x,y)                                 \
    (((x).permittedAlgorithms &= ~EI_A5_7_BIT),          \
      (x).permittedAlgorithms |= (y) << 7 )

#define EI_GET_A5_7(x)                                   \
    (((x).permittedAlgorithms & EI_A5_7_BIT) >> 7) 

/***********************************************************************
 * Channel Type.
 * Ref: 3.2.2.11
 */
typedef struct
{
    ITS_OCTET   speech_or_data;
    ITS_OCTET   chan_rate_type;
    ITS_OCTET   permit_ind_rate[6];
}
BSSAP_ChannelType;

/* 'speech_or_data' ITS_OCTET coding. */
#define CT_SPEECH                                0x01U
#define CT_DATA                                  0x02U
#define CT_SIGNALING                             0x03U

#define CT_SET_SPEECH_DATA_IND(x,y)             \
    ((x).speech_or_data = ((y) & 0x0FU))

#define CT_GET_SPEECH_DATA_IND(x)               \
    ((x).speech_or_data)

/* 'chan_rate_type', if 'speech_or_data' is CT_DATA. */
#define CT_DATA_FULL_RATE_TCH_CHANNEL_BM         0x08U
#define CT_DATA_HALF_RATE_TCH_CHANNEL_LM         0x09U
#define CT_DATA_FULL_OR_HALF_RATE_TCH_CHANNEL1   0x0AU
#define CT_DATA_FULL_OR_HALF_RATE_TCH_CHANNEL2   0x0BU
#define CT_DATA_FULL_OR_HALF_RATE_TCH_CHANNEL3   0x1AU
#define CT_DATA_FULL_OR_HALF_RATE_TCH_CHANNEL4   0x1BU

// CT_DATA_FULL_OR_HALF_RATE_TCH_CHANNEL5 
#define CT_DATA_MAX_ALLOWED_CHANNEL1             0x20U
#define CT_DATA_MAX_ALLOWED_CHANNEL2             0x21U
#define CT_DATA_MAX_ALLOWED_CHANNEL3             0x22U
#define CT_DATA_MAX_ALLOWED_CHANNEL4             0x23U
#define CT_DATA_MAX_ALLOWED_CHANNEL5             0x24U
#define CT_DATA_MAX_ALLOWED_CHANNEL6             0x25U
#define CT_DATA_MAX_ALLOWED_CHANNEL7             0x26U
#define CT_DATA_MAX_ALLOWED_CHANNEL8             0x27U
// CT_DATA_FULL_OR_HALF_RATE_TCH_CHANNEL6
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL1         0x30U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL2         0x31U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL3         0x32U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL4         0x33U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL5         0x34U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL6         0x35U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL7         0x36U
#define CT_DATA_MAX_NOT_ALLOWED_CHANNEL8         0x37U

#define CT_SET_CHANNEL_RATE_DATA(x,y)    \
    (x).chan_rate_type = (y)

#define CT_GET_CHANNEL_RATE_DATA(x)      \
    (x).chan_rate_type

/* 'chan_rate_type', if 'speech_or_data' is CT_SPEECH. */
#define CT_SPEECH_FULL_RATE_TCH_CHANNEL_BM          0x08U
#define CT_SPEECH_HALF_RATE_TCH_CHANNEL_LM          0x09U
#define CT_SPEECH_FULL_OR_HALF_RATE_TCH_CHANNEL1    0x0AU
#define CT_SPEECH_FULL_OR_HALF_RATE_TCH_CHANNEL2    0x0BU
#define CT_SPEECH_FULL_OR_HALF_RATE_TCH_CHANNEL3    0x1AU
#define CT_SPEECH_FULL_OR_HALF_RATE_TCH_CHANNEL4    0x1BU
#define CT_SPEECH_FULL_OR_HALF_RATE_TCH_CHANNEL5    0x0FU
#define CT_SPEECH_FULL_OR_HALF_RATE_TCH_CHANNEL6    0x1FU

#define CT_SET_CHANNEL_RATE_SPCH(x,y)    \
    (x).chan_rate_type = (y)

#define CT_GET_CHANNEL_RATE_SPCH(x)    \
    (x).chan_rate_type

/* 'chan_rate_type', if 'speech_or_data' is CT_SIGNALING. */
#define CT_SIG_SDCCH_OR_FULL_OR_HALF_RATE_TCH_CHANNEL    0x00U
#define CT_SIG_SDCCH                                     0x01U
#define CT_SIG_SDCCH_OR_FULL_RATE_TCH_CHANNEL            0x02U
#define CT_SDCCH_OR_HALF_RATE_TCH_CHANNEL                0x03U
#define CT_SIG_FULL_RATE_TCH_CHANNEL_BM                  0x08U
#define CT_SIG_HALF_RATE_TCH_CHANNEL_LM                  0x09U
#define CT_SIG_FULL_OR_HALF_RATE_TCH_CHANNEL1            0x0AU
#define CT_SIG_FULL_OR_HALF_RATE_TCH_CHANNEL2            0x0BU
#define CT_SIG_FULL_OR_HALF_RATE_TCH_CHANNEL3            0x1AU
#define CT_SIG_FULL_OR_HALF_RATE_TCH_CHANNEL4            0x1BU

#define CT_SET_CHANNEL_RATE_SIG(x,y)    \
    (x).chan_rate_type = (y)

#define CT_GET_CHANNEL_RATE_SIG(x)      \
    (x).chan_rate_type

/* 'permitted_speech_ver_identifier' */
#define CT_PSVI_GSM_FULL_RATE_VER1    0x01U
#define CT_PSVI_GSM_FULL_RATE_VER2    0x11U
#define CT_PSVI_GSM_FULL_RATE_VER3    0x21U
#define CT_PSVI_GSM_HALF_RATE_VER1    0x05U
#define CT_PSVI_GSM_HALF_RATE_VER2    0x15U
#define CT_PSVI_GSM_HALF_RATE_VER3    0x25U

/* Note:
 * Will have to call CT_SET_PERMITTED_SPEECH_VER before 
 * CT_SET_EXT_FOR_PERMITTED_SPEECH_VER
 * x - BSSAP_ChannelType
 * y - ITS_UINT
 * z - ITS_OCTET
 */
#define CT_SET_PERMITTED_SPEECH_VER(x,octetNum,z)            \
    ((x).permit_ind_rate[octetNum] |= ((z) & 0x7FU) )

#define CT_SET_EXT_FOR_PERMITTED_SPEECH_VER(x,octetNum,y)    \
    ((x).permit_ind_rate[octetNum] |= ((y) << 7) & 0x80U )

#define CT_GET_PERMITTED_SPEECH_VER(x,octetNum)              \
    ((x).permit_ind_rate[octetNum] & 0x7FU)

#define CT_GET_EXT_FOR_PERMITTED_SPEECH_VER(x,octetNum)      \
    (((x).permit_ind_rate[octetNum] & 0x80U) >> 7)

/* 'permit_ind_rate' values */
/* These are for 'non-transparent' services, Radio interface data rate */
#define CT_DRTI_NT_RI_12_OR_6_KBPS 0x00U  /*12 for Full rate TCH, 6 for Half*/
#define CT_DRTI_NT_RI_14_5_KBPS    0x18U  /*14.5 kbps*/
#define CT_DRTI_NT_RI_12_KBPS      0x10U  /*12 kbps*/
#define CT_DRTI_NT_RI_6_KBPS       0x11U  /*6 kbps*/

/* These are for 'transparent' services */
#define CT_DRTI_T_14_4_KBPS        0x18U  /* 14.4 kbps */
#define CT_DRTI_T_9_6_KBPS         0x10U  /* 9.6 kbps */
#define CT_DRTI_T_4_8_KBPS         0x11U  /* 4.8 kbps */
#define CT_DRTI_T_2_4_KBPS         0x12U  /* 2.4 kbps */
#define CT_DRTI_T_1_2_KBPS         0x13U  /* 1.2 kbps */
#define CT_DRTI_T_600_BPS          0x14U   /* 600 bits per sec */
#define CT_DRTI_T_1200_75_BPS      0x15U   /* 1200/75 bit/s */

/* These are for 'non-transparent' service, wanted total radio interface data rate */
#define CT_DRTI_NT_RI_58_KBPS               0x16U /*58 kbps*/
#define CT_DRTI_NT_RI_48_OR_43_5_KBPS       0x14U /*48 kbps/43.5 kbps*/
#define CT_DRTI_NT_RI_36_OR_29_KBPS         0x13U /*36 kbps/29 kbps*/
#define CT_DRTI_NT_RI_24_OR_24_OR_29_KBPS   0x12U /*24 or 24 or 29 kbps*/
#define CT_DRTI_NT_RI_18_OR_24_OR_14_5_KBPS 0x11U /*18 kbps/24 kbps/14.5 kbps*/
#define CT_DRTI_NT_RI_12_OR_14_5_KBPS       0x10U /*12 kbps/14.5 kbps*/    

/* These are for 'transparent' service, requested air interface user rate */
#define CT_DRTI_T_AI_64_KBPS_BIT_TRANSPARENT    0x1FU
#define CT_DRTI_T_AI_56_KBPS_BIT_TRANSPARENT    0x1EU
#define CT_DRTI_T_AI_56_KBPS                    0x1DU
#define CT_DRTI_T_AI_48_KBPS                    0x1CU
#define CT_DRTI_T_AI_38_4_KBPS                  0x1BU  /* 38.4 kbps */
#define CT_DRTI_T_AI_28_8_KBPS                  0x1AU  /* 28.8 kbps */
#define CT_DRTI_T_AI_19_2_KBPS                  0x19U  /* 19.2 kbps */
#define CT_DRTI_T_AI_14_4_KBPS                  0x18U  /* 14.4 kbps */
#define CT_DRTI_T_AI_9_6_KBPS                   0x10U  /* 9.6 kbps */

/* Values for Radio Interface Data rate */
#define CT_DRTI_RIDR_F_14_4_ALLOWED_BIT    0x08U
#define CT_DRTI_RIDR_F_9_6_ALLOWED_BIT     0x02U
#define CT_DRTI_RIDR_F_4_8_ALLOWED_BIT     0x01U

#define CT_DRTI_SET_EXTENSION_BIT(x,octetNum, y)             \
    ((x).permit_ind_rate[octetNum] |= ((y) << 7) & 0x80U)

#define CT_DRTI_GET_EXTENSION_BIT(x,octetNum)                \
    (((x).permit_ind_rate[octetNum] & 0x80U) >> 7)
 
#define CT_DRTI_SET_TRANSPARENT_SERVICE(x,y)                 \
    ((x).permit_ind_rate[0] |= ((y) << 6) & 0x40U)

#define CT_DRTI_GET_TYPE_OF_TRASNPARENCY(x)                  \
    (((x).permit_ind_rate[0] & 0x40U) >> 6)

/* Here x - BSSAP_ChannelType, y - one of CT_DRTI_T_xxx or CT_DRTI_NT_xxx */
#define CT_DRTI_SET_RATE(x,y)                   \
    ((x).permit_ind_rate[0] = ((y) & 0x3FU))

#define CT_DRTI_GET_RATE(x)                     \
    ((x).permit_ind_rate[0] & 0x3FU)

/* Here, x- BSSAP_ChannelType, y - one of CT_DRTI_RIDR_F_xxx */
#define CT_DRTI_SET_RIDR_ALLOWED(x,y)           \
    ((x).permit_ind_rate[1] |= ((y) & 0x7FU))

#define CT_DRTI_GET_RIDR_ALLOWED(x)             \
    ((x).permit_ind_rate[1] & 0x7FU)

// Set and Get Asymmetry Indication
#define CT_DRTI_SET_ASYMMETRY_IND(x,y)          \
    ((x).permit_ind_rate[2] |= ((y) << 5) & 0x60U)

#define CT_DRTI_GET_ASYMMETRY_IND(x)            \
    (((x).permit_ind_rate[2] & 0x60U) >> 5)

/***********************************************************************
 * Periodicity
 * Ref: 3.2.2.12
 */
typedef struct
{
    ITS_OCTET    data;
}
BSSAP_Periodicity;

#define P_SET_PERIODICITY(x,y)    \
    ((x).data = (y))

#define P_GET_PERIODICITY(x)      \
    ((x).data )

/***********************************************************************
 * Extended Resource Indicator
 * Ref: 3.2.2.13
 */
typedef struct
{
    ITS_OCTET    data_1field[1];
}
BSSAP_ExtendedResourceIndicator;

#define ERI_SET_TARR(x,y)    \
    ((x).data_1field[0] |= ((y) & 0x01U))

#define ERI_GET_TARR(x)      \
    ((x).data_1field[0] & 0x01U )

#define ERI_SET_SM(x,y)      \
    ((x).data_1field[0] |= (((y) <<1) & 0x02U))

#define ERI_GET_SM(x)        \
    ((x).data_1field[0] >>1)

/***********************************************************************
 * Total Resource Accessible
 * Ref: 3.2.2.14
 */
typedef struct
{
    ITS_OCTET    data_4field[4];
}
BSSAP_TotalResourceAccessible;

#define TRA_SET_FULL_RATE_CHANNELS(x,y)             \
    ((x).data_4field[0] = (((y) >> 8) & 0xFFU)),    \
    ((x).data_4field[1] = (y))

#define TRA_GET_FULL_RATE_CHANNELS(x)               \
    (((x).data_4field[0] << 8) | ((x).data_4field[1]))

#define TRA_SET_HALF_RATE_CHANNELS(x,y)             \
    ((x).data_4field[2] = (((y) >> 8) & 0xFFU)),    \
    ((x).data_4field[3] = (y))

#define TRA_GET_HALF_RATE_CHANNELS(x)               \
    (((x).data_4field[2] << 8) | ((x).data_4field[3]))

/***********************************************************************
 * LSA Identifier
 * Ref: 3.2.2.15
 */

typedef struct
{
    ITS_OCTET    lsa_id[3];
}
BSSAP_LSAIdentifier;

/* LSA ID */
// Set bit 1 seperately
#define LSAID_SET_LSA_ID_BIT_1(x,y)          \
     (((x).lsa_id[2] &= ~0x01U),             \
      ((x).lsa_id[2] |= (y) & 0x01U))

#define LSAID_GET_LSA_ID_BIT_1(x)            \
      ((x).lsa_id[2] & 0x01U)

#define LSAID_SET_LSA_ID(x,y)                \
     (((x).lsa_id[0] &= ~0xFFU),             \
      ((x).lsa_id[0] |= ((y) >> 15) & 0xFFU),\
      ((x).lsa_id[1] &= ~0xFFU),             \
      ((x).lsa_id[1] |= ((y) >> 7) & 0xFFU), \
      ((x).lsa_id[2] &= ~0xFEU),             \
      ((x).lsa_id[2] |= ((y) << 1) & 0xFEU))

#define LSAID_GET_LSA_ID(x)                  \
      ((((x).lsa_id[0] & 0xFFU) << 15) |     \
       (((x).lsa_id[1] & 0xFFU) << 7)  |     \
       (((x).lsa_id[2] & 0xFEU) >> 1))

/***********************************************************************
 * LSA Identity List
 * Ref: 3.2.2.16
 */
typedef struct
{
    ITS_OCTET              ep;
    BSSAP_LSAIdentifier    lsa_id[1];
}
BSSAP_LSAIdentifierList;

// Escape PLMN
#define LSAIDL_SET_EP(x,y)     \
     (((x).ep &= ~0x01U),      \
      ((x).ep |= (y) & 0x01U))

#define LSAIDL_GET_EP(x)       \
      ((x).ep & 0x01U)

/***********************************************************************
 * Cell Identifier
 * Ref: 3.2.2.17
 */
typedef struct
{
    ITS_OCTET    MCC[2];    // Mobile COuntry Code 
    ITS_OCTET    MNC;       // Mobile Network Code 
    ITS_OCTET    LAC[2];    // Location Area Code 
    ITS_OCTET    CI[2];     // Cell Identity 
}
BSSAP_CellGlobalId;

typedef struct
{
    ITS_OCTET    LAC[2];
    ITS_OCTET    CI[2];
}
BSSAP_Lac_Ci;

typedef struct
{
    ITS_OCTET    CI[2];
}
BSSAP_Ci;

typedef struct
{
    ITS_OCTET    MCC[2];
    ITS_OCTET    MNC;
    ITS_OCTET    LAC[2];
    ITS_OCTET    RNCID[2];
}
BSSAP_Plmn_Lac_Rnc;

typedef struct
{
    ITS_OCTET    RNCID[2];
}
BSSAP_Rnc;

typedef struct
{
    ITS_OCTET    LAC[2];
    ITS_OCTET    RNCID[2];
}
BSSAP_Lac_Rnc;

typedef struct
{
    ITS_OCTET    MCC[2];
    ITS_OCTET    MNC;
    ITS_OCTET    LAC[2];
    ITS_OCTET    SAC[2];
}
BSSAP_Sai;

typedef union 
{
    BSSAP_CellGlobalId  cgi;
    BSSAP_Lac_Ci        lac_ci;
    BSSAP_Ci            ci;
    BSSAP_Plmn_Lac_Rnc  plmn_lac_rnc;
    BSSAP_Rnc           rnc;  
    BSSAP_Lac_Rnc       lac_rnc;
    BSSAP_Sai           sai;
}
BSSAP_CellIDType;
 
typedef struct
{
    ITS_OCTET         cell_id_discriminator;
    BSSAP_CellIDType  cell_id;    
}
BSSAP_CellIdentifier;

// Cell Identification Discriminator
#define CI_CID_CGI           0x00U  // Cell Global ID
#define CI_CID_LAC           0x01U  // Location Area Code
#define CI_CID_CI            0x02U  // Cell Identity 
#define CI_CID_NONE          0x03U  // No cell is associated with this transctn
#define CI_CID_PLMN_LAC_RNC  0x08U  // Intersystem handover to UTRAN or cdma2000
#define CI_CID_RNC           0x09U  // Intersystem handover to UTRAN or cdma2000
#define CI_CID_LAC_RNC       0x10U  // Intersystem handover to UTRAN or cdma2000
#define CI_CID_SAI           0x11U  // Serving Area Identity

#define CI_SET_CELL_ID_DISCRIMINATOR(x,y)    \
    ( (x).cell_id_discriminator = (y) )

#define CI_GET_CELL_ID_DISCRIMINATOR(x)      \
    ( (x).cell_id_discriminator )

/* CGI */
// MCC and MNC -- For GSM 900 and DCS 1800
// Populate bit 1 - bit 12
#define CI_CGI_SET_MCC_GSM_DCS(x,y)          \
    ((x).cgi.MCC[0] = (((y) >> 4) & 0xFFU),  \
     (x).cgi.MCC[1] = ((y) | 0xF0U))

#define CI_CGI_GET_MCC_GSM_DCS(x)            \
    ( ( ((x).cgi.MCC[0] & 0x0f) * 10 + (((x).cgi.MCC[0] & 0xf0 ) >> 4) ) * 10 ) + \
                        ((x).cgi.MCC[1] & 0x0f)

// MNC Needs to be BCD encoded 
// Here, y - int 
#define CI_CGI_SET_MNC_GSM_DCS(x,y)          \
    ((x).cgi.MNC = (y) & 0xFFU)    
                           
#define CI_CGI_GET_MNC_GSM_DCS(x)            \
         ( ((x).cgi.MNC & 0x0f) * 10 ) + ( ((x).cgi.MNC & 0xf0) >> 4)  

#define CI_CGI_GET_MNC_GSM_DCS_3_DIGITS(x) \
     ( ( (((x).cgi.MNC & 0x0f) * 10) + ( ( (x).cgi.MNC & 0xf0) >> 4) ) * 10 ) + \
                        ( ((x).cgi.MCC[1] & 0xf0) >> 4 ) 

// MCC and MNC -- For PCS 1900 for NA
// Populate bit 1 - bit 12
#define CI_CGI_SET_MCC_PCS(x,y)              \
    ((x).cgi.MCC[0] = (((y) >> 4) & 0xFFU),  \
     (x).cgi.MCC[1] = ((y) & 0x0FU))

#define CI_CGI_GET_MCC_PCS(x)                \
    ((((x).cgi.MCC[0] & 0xFFU)<< 4) | ((x).cgi.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Here, y - int 
#define CI_CGI_SET_MNC_PCS(x,y)              \
     (((x).cgi.MNC = (y) & 0xFFU),           \
      ((x).cgi.MCC[1] |= ((y) >> 4) & 0xF0U))
                           
#define CI_CGI_GET_MNC_PCS(x)                \
    (((x).cgi.MNC & 0xFFU) | (((x).cgi.MCC[1] & 0xF0) << 4))
       
// LAC
#define CI_CGI_SET_LAC(x,y)                  \
    ((x).cgi.LAC[0] = (((y) >> 8) & 0xFFU),  \
     (x).cgi.LAC[1] = ((y) & 0xFFU))

#define CI_CGI_GET_LAC(x)                    \
    (((x).cgi.LAC[0] << 8 ) | (x).cgi.LAC[1])

// CI
#define CI_CGI_SET_CI(x,y)                   \
    ((x).cgi.CI[0] = (((y) >> 8) & 0xFFU),   \
     (x).cgi.CI[1] = ((y) & 0xFFU))

#define CI_CGI_GET_CI(x)                     \
    (((x).cgi.CI[0] << 8 ) | (x).cgi.CI[1])

/* LAC & CI */
#define CI_LACCI_SET_LAC(x,y)                \
    ((x).lac_ci.LAC[0] = (((y) >> 8) & 0xFFU),  \
     (x).lac_ci.LAC[1] = ((y) & 0xFFU))
#define CI_LACCI_GET_LAC(x)                  \
    (((x).lac_ci.LAC[0] << 8 ) | (x).lac_ci.LAC[1])

#define CI_LACCI_SET_CI(x,y)                 \
    ((x).lac_ci.CI[0] = (((y) >> 8) & 0xFFU),\
     (x).lac_ci.CI[1] = ((y) & 0xFFU))
#define CI_LACCI_GET_CI(x)                   \
    (((x).lac_ci.CI[0] << 8 ) | (x).lac_ci.CI[1])

/* CI */
#define CI_CI_SET_CI(x,y)                    \
    ((x).ci.CI[0] = (((y) >> 8) & 0xFFU),    \
         (x).ci.CI[1] = ((y) & 0xFFU))

#define CI_CI_GET_CI(x)                      \
    (((x).ci.CI[0] << 8 ) | (x).ci.CI[1])

/* PLMN_LAC_RNC */
// MCC
// Populate bit 1 - bit 12
#define CI_PLR_SET_MCC(x,y)                            \
    ((x).plmn_lac_rnc.MCC[0] = (((y) >> 4) & 0xFFU),   \
     (x).plmn_lac_rnc.MCC[1] = ((y) & 0x0FU))

#define CI_PLR_GET_MCC(x)                              \
    ((x).plmn_lac_rnc.MCC[0] << 4 | ((x).plmn_lac_rnc.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CI_PLR_SET_MNC(x,y)                            \
     (((x).plmn_lac_rnc.MNC = (y) & 0xFFU),            \
      ((x).plmn_lac_rnc.MCC[1] |= ((y) >> 4) & 0xF0U))
                           
#define CI_PLR_GET_MNC(x)                              \
    (((x).plmn_lac_rnc.MNC & 0xFFU) | (((x).plmn_lac_rnc.MCC[1] & 0xF0) << 4))

// LAC
#define CI_PLR_SET_LAC(x,y)                            \
    ((x).plmn_lac_rnc.LAC[0] = (((y) >> 8) & 0xFFU),   \
     (x).plmn_lac_rnc.LAC[1] = ((y) & 0xFFU))

#define CI_PLR_GET_LAC(x)                              \
    (((x).plmn_lac_rnc.LAC[0] << 8 ) | (x).plmn_lac_rnc.LAC[1])

// RNC-ID
#define CI_PLR_SET_RNC_ID(x,y)                         \
    ((x).plmn_lac_rnc.RNCID[0] = (((y) >> 8) & 0xFFU), \
     (x).plmn_lac_rnc.RNCID[1] = ((y) & 0xFFU))

#define CI_PLR_GET_RNC_ID(x)                           \
    (((x).plmn_lac_rnc.RNCID[0] << 8 ) | (x).plmn_lac_rnc.RNCID[1])

/* RNC-ID */
#define CI_RNC_SET_RNC_ID(x,y)                         \
    ((x).rnc.RNCID[0] = (((y) >> 8) & 0xFFU),          \
     (x).rnc.RNCID[1] = ((y) & 0xFFU))

#define CI_RNC_GET_RNC_ID(x)                           \
    (((x).rnc.RNCID[0] << 8 ) | (x).rnc.RNCID[1])

/* LAC_RNC */
// LAC
#define CI_LR_SET_LAC(x,y)                             \
    ((x).lac_rnc.LAC[0] = (((y) >> 8) & 0xFFU),        \
     (x).lac_rnc.LAC[1] = ((y) & 0xFFU))

#define CI_LR_GET_LAC(x)                               \
    (((x).lac_rnc.LAC[0] << 8 ) | (x).lac_rnc.LAC[1])

// RNC-ID
#define CI_LR_SET_RNC_ID(x,y)                          \
    ((x).lac_rnc.RNCID[0] = (((y) >> 8) & 0xFFU),      \
     (x).lac_rnc.RNCID[1] = ((y) & 0xFFU))

#define CI_LR_GET_RNC_ID(x)                            \
    (((x).lac_rnc.RNCID[0] << 8 ) | (x).lac_rnc.RNCID[1])

/* SAI */
// MCC
// Populate bit 1 - bit 12
#define CI_SAI_SET_MCC(x,y)                            \
    ((x).sai.MCC[0] = (((y) >> 4) & 0xFFU),            \
     (x).sai.MCC[1] = ((y) & 0x0FU))

#define CI_SAI_GET_MCC(x)                              \
    ((x).sai.MCC[0] << 4 | ((x).sai.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CI_SAI_SET_MNC(x,y)                            \
     (((x).sai.MNC = (y) & 0xFFU),                     \
      ((x).sai.MCC[1] |= ((y) >> 4) & 0xF0U))
                           
#define CI_SAI_GET_MNC(x)                              \
    (((x).sai.MNC & 0xFFU) | (((x).sai.MCC[1] & 0xF0) << 4))

// LAC
#define CI_SAI_SET_LAC(x,y)                            \
    ((x).sai.LAC[0] = (((y) >> 8) & 0xFFU),            \
     (x).sai.LAC[1] = ((y) & 0xFFU))

#define CI_SAI_GET_LAC(x)                              \
    (((x).sai.LAC[0] << 8 ) | (x).sai.LAC[1])

// SAC
#define CI_SAI_SET_SAC(x,y)                            \
    ((x).sai.SAC[0] = (((y) >> 8) & 0xFFU),            \
     (x).sai.SAC[1] = ((y) & 0xFFU))

#define CI_SAI_GET_SAC(x)                              \
    (((x).sai.SAC[0] << 8 ) | (x).sai.SAC[1])

/***********************************************************************
 * Priority.
 * Ref: 3.2.18
 */
typedef struct
{
    ITS_OCTET    pri;
}
BSSAP_Priority;

/* priority level */
#define P_SPARE             0x00U
#define P_PRI_LEVEL_1       0x01U   /* Highest priority */
#define P_PRI_LEVEL_2       0x02U
#define P_PRI_LEVEL_3       0x03U
#define P_PRI_LEVEL_4       0x04U
#define P_PRI_LEVEL_5       0x05U
#define P_PRI_LEVEL_6       0x06U
#define P_PRI_LEVEL_7       0x07U
#define P_PRI_LEVEL_8       0x08U
#define P_PRI_LEVEL_9       0x09U
#define P_PRI_LEVEL_10      0x0AU
#define P_PRI_LEVEL_11      0x0BU
#define P_PRI_LEVEL_12      0x0CU
#define P_PRI_LEVEL_13      0x0DU
#define P_PRI_LEVEL_14      0x0EU   /* Lowest priority */
#define P_PRI_LEVEL_UNUSED  0x0FU

/* priority */
#define P_PRIORITY_BITS 0x3CU

#define P_SET_PRIORITY(x,y)                         \
    (((x).pri &= ~P_PRIORITY_BITS),                 \
     (x).pri |= (((y) << 2) & P_PRIORITY_BITS))

#define P_GET_PRIORITY(x)                           \
    (((x).pri & P_PRIORITY_BITS) >> 2)

/* queuing */
#define P_NO_QUEUING           0x00U
#define P_QUEUING_ALLOWED      0x01U
#define P_QUEUEING_BIT         0x02U

#define P_SET_QUEUING(x,y)                         \
    (((x).pri &= ~P_QUEUEING_BIT),                 \
     (x).pri |= (((y) << 1) & P_QUEUEING_BIT))

#define P_GET_QUEUING(x)                           \
    (((x).pri & P_QUEUEING_BIT) >> 1)

/* preemption capability */
#define P_NO_PREEMPTION        0x00U
#define P_PREEMPTION_ALLOWED   0x01U
#define P_PREEMPT_CAP_BIT      0x40U

#define P_SET_PREEMPTION_CAPABILITY(x,y)           \
    (((x).pri &= ~P_PREEMPT_CAP_BIT),              \
      (x).pri |= (((y) << 6) & P_PREEMPT_CAP_BIT))

#define P_GET_PREEMPTION_CAPABILITY(x)             \
    (((x).pri & P_PREEMPT_CAP_BIT) >> 6)

/* preemption vulnerability */
#define P_CONN_NOT_REQ       0x00U
#define P_CONN_BE_REQ        0x01U
#define P_PREEMPT_VUL_BIT    0x01U

#define P_SET_PREEMPTION_VULNERAIBILITY(x,y)       \
    (((x).pri &= ~P_PREEMPT_VUL_BIT),              \
      (x).pri |= ((y) & P_PREEMPT_VUL_BIT))

#define P_GET_PREEMPTION_VULNERABILITY(x)          \
    ((x).pri & P_PREEMPT_VUL_BIT)

/***********************************************************************
 * Classmark Information type 2.
 * Ref: 3.2.2.19
 *      GSM04.08 Section 10.5.1.6
 */
typedef struct
{
    ITS_OCTET  data_4field;   /*Has Revision level, ES, A5/1, RF cap.*/
    ITS_OCTET  data_6field_1; /*Has PS cap., SS ind., SM cap.,VBS, VGCS, FC*/
    ITS_OCTET  data_6field_2; /*Has CM3, LCSVA cap., SoLSA, CMSP, A5/3, A5/2*/
}
BSSAP_ClassmarkInfoType2;

/*
 * data_4 field.
 */

/* 'Revision Level' */
#define CIT2_REV_LEVEL_PHASE_1      0x00U
#define CIT2_REV_LEVEL_PHASE_2      0x01U
#define CIT2_REV_LEVEL_BITS         0x60U

#define CIT2_SET_REV_LEVEL(x,y)                    \
    (((x).data_4field &= ~CIT2_REV_LEVEL_BITS),    \
        (x).data_4field |= ((y) << 5 ) & CIT2_REV_LEVEL_BITS)

#define CIT2_GET_REV_LEVEL(x)                      \
    (((x).data_4field & CIT2_REV_LEVEL_BITS) >> 5)

/* 'ES Ind' */
#define CIT2_ES_IND_IS_IMPLEMENTED       0x00U
#define CIT2_ES_IND_IS_NOT_IMPLEMENTED   0x01U
#define CIT2_ES_IND_BIT                  0x10U

#define CIT2_SET_ES_IND(x,y)                       \
    (((x).data_4field &= ~CIT2_ES_IND_BIT),        \
      (x).data_4field |= ((y) << 4 ) & CIT2_ES_IND_BIT)

#define CIT2_GET_ES_IND(x)                         \
    (((x).data_4field & CIT2_ES_IND_BIT) >> 4)

/* A5/1 */
#define CIT2_A5_1_IS_AVAILABLE        0x00U
#define CIT2_A5_1_IS_NOT_AVAILABLE    0x01U
#define CIT2_A5_1_IND_BIT             0x08U

#define CIT2_SET_A5_1_IND(x,y)                     \
    (((x).data_4field &= ~CIT2_A5_1_IND_BIT),      \
      (x).data_4field |= ((y) << 3 ) & CIT2_A5_1_IND_BIT)

#define CIT2_GET_A5_1_IND(x)                       \
    (((x).data_4field & CIT2_A5_1_IND_BIT) >> 3)

/* 'RF Power capabilities' */
#define CIT2_RF_POWER_CAP_CLASS1      0x00U
#define CIT2_RF_POWER_CAP_CLASS2      0x01U
#define CIT2_RF_POWER_CAP_CLASS3      0x02U
#define CIT2_RF_POWER_CAP_CLASS4      0x03U
#define CIT2_RF_POWER_CAP_CLASS5      0x04U
#define CIT2_RF_POWER_CAP_IND_BITS    0x07U

#define CIT2_SET_RF_POWER_CAP(x,y)                      \
    (((x).data_4field &= ~CIT2_RF_POWER_CAP_IND_BITS),  \
      (x).data_4field |= ((y)  & CIT2_RF_POWER_CAP_IND_BITS))

#define CIT2_GET_RF_POWER_CAP(x)                        \
    ((x).data_4field & CIT2_RF_POWER_CAP_IND_BITS)

/*
 * data_6field_1.
 */

/* 'PS capability' */
#define CIT2_PS_CAP_NOT_PRESENT    0x00U
#define CIT2_PS_CAP_PRESENT        0x01U
#define CIT2_PS_CAP_IND_BIT        0x40U

#define CIT2_SET_PS_CAP(x,y)                       \
    (((x).data_6field_1 &= ~CIT2_PS_CAP_IND_BIT),  \
      (x).data_6field_1 |= ((y) << 6 ) & CIT2_PS_CAP_IND_BIT)

#define CIT2_GET_PS_CAP(x)                         \
    (((x).data_6field_1 & CIT2_PS_CAP_IND_BIT) >> 6)

/* 'SS Screen Indicator' */
#define CIT2_SS_SCREEN_IND_1     0x00U
#define CIT2_SS_SCREEN_IND_2     0x01U
#define CIT2_SS_SCREEN_IND_3     0x02U
#define CIT2_SS_SCREEN_IND_4     0x03U

#define CIT2_SS_SCREEN_IND_BITS  0x30U

#define CIT2_SET_SS_SCREEN_IND(x,y)                    \
    (((x).data_6field_1 &= ~CIT2_SS_SCREEN_IND_BITS),  \
      (x).data_6field_1 |= ((y) << 4 ) & CIT2_SS_SCREEN_IND_BITS)

#define CIT2_GET_SS_SCREEN_IND(x)                      \
    (((x).data_6field_1 & CIT2_PS_CAP_IND_BIT) >> 4)

/* 'SM capability' */
#define CIT2_SM_CAP_NOT_SUPPORTED    0x00U
#define CIT2_SM_CAP_SUPPORTED        0x01U
#define CIT2_SM_CAP_IND_BIT          0x08U

#define CIT2_SET_SM_CAP(x,y)                        \
    (((x).data_6field_1 &= ~CIT2_SM_CAP_IND_BIT),                     \
      (x).data_6field_1 |= ((y) << 3 ) & CIT2_SM_CAP_IND_BIT)

#define CIT2_GET_SM_CAP(x)                        \
    (((x).data_6field_1 & CIT2_SM_CAP_IND_BIT) >> 3)

/* 'VBS Notification' */
#define CIT2_VBS_CAP_NOT_NEEDED    0x00U
#define CIT2_VBS_CAP_NEEDED        0x01U
#define CIT2_VBS_CAP_IND_BIT       0x04U

#define CIT2_SET_VBS_CAP(x,y)                        \
    (((x).data_6field_1 &= ~CIT2_VBS_CAP_IND_BIT),                  \
      (x).data_6field_1 |= ((y) << 2 ) & CIT2_VBS_CAP_IND_BIT)

#define CIT2_GET_VBS_CAP(x)                        \
    (((x).data_6field_1 & CIT2_VBS_CAP_IND_BIT) >> 2)

/* 'VGCS Notification' */
#define CIT2_VGCS_CAP_NOT_NEEDED    0x00U
#define CIT2_VGCS_CAP_NEEDED        0x01U
#define CIT2_VGCS_CAP_IND_BIT       0x02U

#define CIT2_SET_VGCS_CAP(x,y)                        \
    (((x).data_6field_1 &= ~CIT2_VGCS_CAP_IND_BIT),                 \
      (x).data_6field_1 |= ((y) << 1 ) & CIT2_VGCS_CAP_IND_BIT)

#define CIT2_GET_VGCS_CAP(x)                        \
    (((x).data_6field_1 & CIT2_VGCS_CAP_IND_BIT) >> 1)

/* 'FC' - Frequency Capability */
#define CIT2_FC_NOT_SUPPORTED    0x00U
#define CIT2_FC_SUPPORTED        0x01U

#define CIT2_FC_IND_BIT          0x01U

#define CIT2_SET_FC(x,y)                      \
    (((x).data_6field_1 &= ~CIT2_FC_IND_BIT),                 \
      (x).data_6field_1 |= ((y)  & CIT2_FC_IND_BIT))

#define CIT2_GET_FC(x)                        \
    ((x).data_6field_1 & CIT2_FC_IND_BIT)

/*
 * data_6field_2.
 */

/* 'CM3' */
#define CIT2_CM3_OPTIONS_NOT_SUPPORTED    0x00U
#define CIT2_CM3_OPTIONS_SUPPORTED        0x01U
#define CIT2_CM3_OPTIONS_BIT              0x80U

#define CIT2_SET_CM3(x,y)                        \
    (((x).data_6field_2 &= ~CIT2_CM3_OPTIONS_BIT),                  \
      (x).data_6field_2 |= ((y) << 7 ) & CIT2_CM3_OPTIONS_BIT)

#define CIT2_GET_CM3(x)                            \
    (((x).data_6field_2 & CIT2_CM3_OPTIONS_BIT) >> 7)

/* 'LCS VA capability' */
#define CIT2_LCS_VA_CAP_NOT_SUPPORTED    0x00U
#define CIT2_LCS_VA_CAP_SUPPORTED        0x01U
#define CIT2_LCS_VA_CAP_BIT              0x20U

#define CIT2_SET_LCS_VA_CAP(x,y)                    \
    (((x).data_6field_2 &= ~CIT2_LCS_VA_CAP_BIT),                   \
      (x).data_6field_2 |= ((y) << 5 ) & CIT2_LCS_VA_CAP_BIT)

#define CIT2_GET_LCS_VA_CAP(x)                        \
    (((x).data_6field_2 & CIT2_LCS_VA_CAP_BIT) >> 5)

/* 'SoLSA' */
#define CIT2_SOLSA_NOT_SUPPORTED    0x00U
#define CIT2_SOLSA_SUPPORTED        0x01U
#define CIT2_SOLSA_BIT              0x08U

#define CIT2_SET_SOLSA(x,y)                    \
    (((x).data_6field_2 &= ~CIT2_SOLSA_BIT),                \
      (x).data_6field_2 |= ((y) << 3 ) & CIT2_SOLSA_BIT)

#define CIT2_GET_SOLSA(x)                    \
    (((x).data_6field_2 & CIT2_SOLSA_BIT) >> 3)

/* 'CMSP' */
#define CIT2_CMSP_NOT_SUPPORTED     0x00U
#define CIT2_CMSP_SUPPORTED         0x01U
#define CIT2_CMSP_BIT               0x04U

#define CIT2_SET_CMSP(x,y)                    \
    (((x).data_6field_2 &= ~CIT2_CMSP_BIT),                 \
      (x).data_6field_2 |= ((y) << 2 ) & CIT2_CMSP_BIT)

#define CIT2_GET_CMSP(x)                    \
    (((x).data_6field_2 & CIT2_CMSP_BIT) >> 2)

/* 'A5/3' */
#define CIT2_A5_3_NOT_SUPPORTED    0x00U
#define CIT2_A5_3_SUPPORTED        0x01U
#define CIT2_A5_3_BIT              0x02U

#define CIT2_SET_A5_3(x,y)                    \
    (((x).data_6field_2 &= ~CIT2_A5_3_BIT),                 \
      (x).data_6field_2 |= ((y) << 1 ) & CIT2_A5_3_BIT)

#define CIT2_GET_A5_3(x)                    \
    (((x).data_6field_2 & CIT2_A5_3_BIT) >> 1)

/* 'A5/2' */
#define CIT2_A5_2_NOT_SUPPORTED    0x00U
#define CIT2_A5_2_SUPPORTED        0x01U
#define CIT2_A5_2_BIT              0x01U

#define CIT2_SET_A5_2(x,y)                    \
    (((x).data_6field_2 &= ~CIT2_A5_2_BIT),                 \
      (x).data_6field_2 |= ((y) & CIT2_A5_2_BIT))

#define CIT2_GET_A5_2(x)                    \
    ((x).data_6field_2 & CIT2_A5_2_BIT)

/***********************************************************************
 * Classmark Information Type 3.
 * Ref: 3.2.2.20
 *     GSM 04.08 Section 10.5.17
 *
 */
typedef struct
{
    ITS_OCTET  data_field1_2[2];
    ITS_OCTET  data_field2_2[1];
    ITS_OCTET  data_field3_4[2];
}
BSSAP_ClassmarkInfoType3;

#define  CIT3_ENCRIPTION_A5_4_BITS                 0x01U
#define  CIT3_ENCRIPTION_A5_5_BITS                 0x02U
#define  CIT3_ENCRIPTION_A5_6_BITS                 0x04U
#define  CIT3_ENCRIPTION_A5_7_BITS                 0x08U
#define  CIT3_ASS_RADIO_CAP1_BITS                  0x0FU
#define  CIT3_ASS_RADIO_CAP2_BITS                  0xF0U
// batch set Multiband supported 
#define  CIT3_MULTI_BAND_SUPPORT_BITS              0x70U
// set Multiband supported seperately
#define  CIT3_P_GSM_SUPPORT_BITS                   0x10U   //band 1
#define  CIT3_EorR_GSM_SUPPORT_BITS                0x20U   //band 2
#define  CIT3_DCS1800_SUPPORT_BITS                 0x40U   //band 3

// Set and Get A5
#define CIT3_SET_ENCRIPTION_A54(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_ENCRIPTION_A5_4_BITS),                  \
      (x).data_field1_2[0] |= (y) & CIT3_ENCRIPTION_A5_4_BITS)

#define CIT3_GET_ENCRIPTION_A54(x)                            \
    ((x).data_field1_2[0] & CIT3_ENCRIPTION_A5_4_BITS)

#define CIT3_SET_ENCRIPTION_A55(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_ENCRIPTION_A5_5_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 1 ) & CIT3_ENCRIPTION_A5_5_BITS)

#define CIT3_GET_ENCRIPTION_A55(x)                            \
    (((x).data_field1_2[0] & CIT3_ENCRIPTION_A5_5_BITS) >> 1)

#define CIT3_SET_ENCRIPTION_A56(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_ENCRIPTION_A5_6_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 2 ) & CIT3_ENCRIPTION_A5_6_BITS)

#define CIT3_GET_ENCRIPTION_A56(x)                            \
    (((x).data_field1_2[0] & CIT3_ENCRIPTION_A5_6_BITS) >> 2)

#define CIT3_SET_ENCRIPTION_A57(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_ENCRIPTION_A5_6_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 3 ) & CIT3_ENCRIPTION_A5_7_BITS)

#define CIT3_GET_ENCRIPTION_A57(x)                            \
    (((x).data_field1_2[0] & CIT3_ENCRIPTION_A5_7_BITS) >> 3)

// Set And Get Multiband supported
#define CIT3_SET_MULTI_BAND_SUPPORT(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_MULTI_BAND_SUPPORT_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 4 ) & CIT3_MULTI_BAND_SUPPORT_BITS)

#define CIT3_GET_MULTI_BAND_SUPPORT(x)                            \
    (((x).data_field1_2[0] & CIT3_MULTI_BAND_SUPPORT_BITS) >> 4)

// Set and Get Multiband supported seperately
//band 
#define CIT3_SET_P_GSM_SUPPORT(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_P_GSM_SUPPORT_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 4 ) & CIT3_P_GSM_SUPPORT_BITS)

#define CIT3_GET_P_GSM_SUPPORT(x)                            \
    (((x).data_field1_2[0] & CIT3_P_GSM_SUPPORT_BITS) >> 4)

//band 2
#define CIT3_SET_EorR_GSM_SUPPORT(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_EorR_GSM_SUPPORT_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 5 ) & CIT3_EorR_GSM_SUPPORT_BITS)

#define CIT3_GET_EorR_GSM_SUPPORT(x)                            \
    (((x).data_field1_2[0] & CIT3_EorR_GSM_SUPPORT_BITS) >> 5)

//band 3
#define CIT3_SET_DCS1800_SUPPORT(x,y)                        \
    (((x).data_field1_2[0] &= ~CIT3_DCS1800_SUPPORT_BITS),                  \
      (x).data_field1_2[0] |= ((y) << 6 ) & CIT3_DCS1800_SUPPORT_BITS)

#define CIT3_GET_DCS1800_SUPPORT(x)                            \
    (((x).data_field1_2[0] & CIT3_DCS1800_SUPPORT_BITS) >> 6)

// Set and Get Associate Radio Capbility
#define CIT3_SET_ASS_RADIO_CAP1(x,y)                        \
    (((x).data_field1_2[1] &= ~CIT3_ASS_RADIO_CAP1_BITS),                  \
      (x).data_field1_2[1] |= (y) & CIT3_ASS_RADIO_CAP1_BITS)

#define CIT3_GET_ASS_RADIO_CAP1(x)                            \
    ((x).data_field1_2[1] & CIT3_ASS_RADIO_CAP1_BITS)

#define CIT3_SET_ASS_RADIO_CAP2(x,y)                        \
    (((x).data_field1_2[1] &= ~CIT3_ASS_RADIO_CAP2_BITS),                  \
      (x).data_field1_2[1] |= ((y) << 4) & CIT3_ASS_RADIO_CAP2_BITS)

#define CIT3_GET_ASS_RADIO_CAP2(x)                            \
    (((x).data_field1_2[1] & CIT3_ASS_RADIO_CAP2_BITS) >> 4)

#define  CIT3_R_GSM_BAND_ASS_RADIO_CAP_BITS           0xE0U
#define  CIT3_MULTI_SLOT_CLASS_BITS                   0x1FU

// Set and Get R-GSM band Associate Radio Capability
#define CIT3_SET_R_GSM_BAND_ASS_RADIO_CAP(x,y)                        \
    (((x).data_field2_2[0] &= ~CIT3_R_GSM_BAND_ASS_RADIO_CAP_BITS),   \
      (x).data_field2_2[0] |= ((y) << 5) & CIT3_R_GSM_BAND_ASS_RADIO_CAP_BITS)

#define CIT3_GET_R_GSM_BAND_ASS_RADIO_CAP(x)                          \
    (((x).data_field2_2[0] & CIT3_R_GSM_BAND_ASS_RADIO_CAP_BITS) >> 5)

// Set and Get R Support
#define CIT3_SET_MULTI_SLOT_CLASS(x,y)                        \
    (((x).data_field2_2[0] &= ~CIT3_MULTI_SLOT_CLASS_BITS),                  \
      (x).data_field2_2[0] |= (y)& CIT3_MULTI_SLOT_CLASS_BITS)

#define CIT3_GET_MULTI_SLOT_CLASS(x)                            \
    ((x).data_field2_2[0] & CIT3_MULTI_SLOT_CLASS_BITS)

// Temp encode like this way, ensure later
#define CIT3_UCS_2_TREATMENT_BITS                    0x80U
#define CIT3_EXT_MEAS_CAP_BITS                       0x40U
#define CIT3_SMS_VALUE_BITS                          0x3CU
#define CIT3_SM_VALUE_HI_BITS                        0x03U
#define CIT3_SM_VALUE_LO_BITS                        0xC0U
// MS Positioning Method Capability
#define CIT3_MS_CON_GPS_BITS                         0x02U //bit 1
#define CIT3_MS_BASED_GPS_BITS                       0x04U //bit 2
#define CIT3_MS_ASSISTED_GPS_BITS                    0x08U //bit 3
#define CIT3_MS_BASED_E_OTD_BITS                     0x10U //bit 4
#define CIT3_MS_ASSISTED_E_OTD_BITS                  0x20U //bit 5

// Set and Get SM_Value
#define CIT3_SET_SM_VALUE(x,y)                                    \
  (((x).data_field3_4[0] |= ((y) >> 2) & CIT3_SM_VALUE_HI_BITS),  \
    (x).data_field3_4[1] &= ~CIT3_SM_VALUE_LO_BITS,               \
    (x).data_field3_4[1] |= (((y) << 6) & CIT3_SM_VALUE_LO_BITS))

#define CIT3_GET_SM_VALUE(x)                                   \
    ((((x).data_field3_4[0] & CIT3_SM_VALUE_HI_BITS) << 2) |   \
      ((x).data_field3_4[1] & CIT3_SM_VALUE_LO_BITS) >> 6)

// Set and Get SMS_Value
#define CIT3_SET_SMS_VALUE(x,y)                        \
    (((x).data_field3_4[0] &= ~CIT3_SMS_VALUE_BITS),                  \
      (x).data_field3_4[0] |= ((y) << 2) & CIT3_SMS_VALUE_BITS)

#define CIT3_GET_SMS_VALUE(x)                            \
    (((x).data_field3_4[0] & CIT3_SMS_VALUE_BITS) >> 2)

// Set and Get Extended Measurement Capability
#define CIT3_SET_EXT_MEAS_CAP(x,y)                        \
    (((x).data_field3_4[0] &= ~CIT3_EXT_MEAS_CAP_BITS),                  \
      (x).data_field3_4[0] |= ((y) << 6) & CIT3_EXT_MEAS_CAP_BITS)

#define CIT3_GET_EXT_MEAS_CAP(x)                            \
    (((x).data_field3_4[0] & CIT3_EXT_MEAS_CAP_BITS) >> 6)

// Set and Get UCS2 Treatment
#define CIT3_SET_UCS_2_TREATMENT(x,y)                        \
    (((x).data_field3_4[0] &= ~CIT3_UCS_2_TREATMENT_BITS),                  \
      (x).data_field3_4[0] |= ((y) << 7) & CIT3_UCS_2_TREATMENT_BITS)

#define CIT3_GET_UCS_2_TREATMENT(x)                            \
    (((x).data_field3_4[0] & CIT3_UCS_2_TREATMENT_BITS) >> 7)

// Set and Get MS Positioning Method
#define CIT3_SET_CONVENTIONAL_GPS(x,y)                        \
    (((x).data_field3_4[1] &= ~CIT3_MS_CON_GPS_BITS),                  \
      (x).data_field3_4[1] |= ((y) << 1) & CIT3_MS_CON_GPS_BITS)

#define CIT3_GET_CONVENTIONAL_GPS(x)                            \
    (((x).data_field3_4[1] & CIT3_MS_CON_GPS_BITS) >> 1)

#define CIT3_SET_MS_BASED_GPS(x,y)                        \
    (((x).data_field3_4[1] &= ~CIT3_MS_BASED_GPS_BITS),                  \
      (x).data_field3_4[1] |= ((y) << 2) & CIT3_MS_BASED_GPS_BITS)

#define CIT3_GET_MS_BASED_GPS(x)                            \
    (((x).data_field3_4[1] & CIT3_MS_BASED_GPS_BITS) >> 2)

#define CIT3_SET_MS_ASSISTED_GPS(x,y)                        \
    (((x).data_field3_4[1] &= ~CIT3_MS_ASSISTED_GPS_BITS),                  \
      (x).data_field3_4[1] |= ((y) << 3) & CIT3_MS_ASSISTED_GPS_BITS)

#define CIT3_GET_MS_ASSISTED_GPS(x)                            \
    (((x).data_field3_4[1] & CIT3_MS_ASSISTED_GPS_BITS) >> 3)

#define CIT3_SET_MS_BASED_E_OTD(x,y)                        \
    (((x).data_field3_4[1] &= ~CIT3_MS_BASED_E_OTD_BITS),                  \
      (x).data_field3_4[1] |= ((y) << 4) & CIT3_MS_BASED_E_OTD_BITS)

#define CIT3_GET_MS_BASED_E_OTD(x)                            \
    (((x).data_field3_4[1] & CIT3_MS_BASED_E_OTD_BITS) >> 4)

#define CIT3_SET_MS_ASSISTED_E_OTD(x,y)                        \
    (((x).data_field3_4[1] &= ~CIT3_MS_ASSISTED_E_OTD_BITS),                  \
      (x).data_field3_4[1] |= ((y) << 5) & CIT3_MS_ASSISTED_E_OTD_BITS)

#define CIT3_GET_MS_ASSISTED_E_OTD(x)                            \
    (((x).data_field3_4[1] & CIT3_MS_ASSISTED_E_OTD_BITS) >> 5)

/***********************************************************************
 * Interference Band to be used
 * Ref: 3.2.2.21
 */
typedef struct
{
    ITS_OCTET    band_to_be_used;
}
BSSAP_BandToBeUsed;

#define P_SET_BAND_TO_BE_USED(x,y)    \
    ((x).band_to_be_used = ((y) & 0x1FU))

#define P_GET_BAND_TO_BE_USED(x)    \
    ((x).band_to_be_used)

/***********************************************************************
 * RR Cause
 * Ref: 3.2.2.22
 */
typedef struct
{
    ITS_OCTET    rr_cause;
}
BSSAP_RRCause;

#define RRC_NORMAL_EVENT                         0x00U
#define RRC_ABN_REL_UNSPECIFIED                  0x01U
#define RRC_ABN_REL_CHANNEL_UNACCEPTABLE         0x02U
#define RRC_ABN_REL_TIMER_EXPIRED                0x03U
#define RRC_ABN_REL_NO_ACTIVITY_ON_RADIO_PATH    0x04U
#define RRC_PREEMPTIVE_RELEASE                   0x05U
#define RRC_HANDOVER_IMPOSSIBLE                  0x08U
#define RRC_CHANNEL_MODE_UNACCEPTABLE            0x09U
#define RRC_FREQUENCY_NOT_IMPLEMENTED            0x0AU
#define RRC_CALL_ALREADY_CLEARED                 0x41U
#define RRC_SEMANTICALLY_INCORRECT_MSG           0x5FU
#define RRC_INVALID_MANDATORY_INFO               0x60U
#define RRC_MSG_TYPE_NON_IMPLEMENTED             0x61U
#define RRC_MSG_TYPE_NOT_COMPATIBLE              0x62U
#define RRC_CONDITIONAL_IE_ERROR                 0x64U
#define RRC_NO_CELL_ALLOCATION_AVAILABLE         0x65U
#define RRC_PROTOCOL_ERROR_UNSPECIFIED           0x6FU

#define P_SET_RR_CAUSE(x,y)    \
    ((x).rr_cause = ((y) & 0xFFU))

#define P_GET_RR_CAUSE(x)    \
    ((x).rr_cause)

/***********************************************************************
 * LSA Information.
 * Ref: 3.2.2.23
 */
typedef struct
{
    ITS_OCTET    data_field1;
    ITS_OCTET    lsa_id[3];
}
BSSAP_LSA;

typedef struct
{
    ITS_OCTET    lsa_ind;
    BSSAP_LSA    lsa_info[1];
}
BSSAP_LSAInfo;

// LSA only access indicator
#define LSAI_SET_LSA_INDICATOR(x,y)     \
     (((x).lsa_ind &= ~0x01U),     \
      ((x).lsa_ind |= (y) & 0x01U))

#define LSAI_GET_LSA_INDICATOR(x)       \
      ((x).lsa_ind & 0x01U)

// LSA ID field 1 -- priority, pref, and act
// Priority value is between 1 and 16, 16 presents highest priority
#define LSAI_SET_LSA_ID_PRIORITY(x,y)         \
     (((x).data_field1 &= ~0x0FU),     \
      ((x).data_field1 |= (y) & 0x0FU))

#define LSAI_GET_LSA_ID_PRIORITY(x)       \
      ((x).data_field1 & 0x0FU)

#define LSAI_SET_LSA_ID_PREF(x,y)         \
     (((x).data_field1 &= ~0x10U),     \
      ((x).data_field1 |= ((y) << 4) & 0x10U))

#define LSAI_GET_LSA_ID_PREF(x)           \
      (((x).data_field1 & 0x10U) >> 4)

#define LSAI_SET_LSA_ID_ACT(x,y)          \
     (((x).data_field1 &= ~0x20U),     \
      ((x).data_field1 |= ((y) << 5) & 0x20U))

#define LSAI_GET_LSA_ID_ACT(x)           \
      (((x).data_field1 & 0x20U) >> 5)

/* LSA ID */
// Set bit 1 seperately
#define LSAI_SET_LSA_ID_BIT_1(x,y)          \
     (((x).lsa_id[2] &= ~0x01U),     \
      ((x).lsa_id[2] |= (y) & 0x01U))

#define LSAI_GET_LSA_ID_BIT_1(x)            \
      ((x).lsa_id[2] & 0x01U)

#define LSAI_SET_LSA_ID(x,y)                \
     (((x).lsa_id[0] &= ~0xFFU),     \
      ((x).lsa_id[0] |= ((y) >> 15) & 0xFFU),  \
      ((x).lsa_id[1] &= ~0xFFU),     \
      ((x).lsa_id[1] |= ((y) >> 7) & 0xFFU),  \
      ((x).lsa_id[2] &= ~0xFEU),     \
      ((x).lsa_id[2] |= ((y) << 1) & 0xFEU))

#define LSAI_GET_LSA_ID(x)                \
      ((((x).lsa_id[0] & 0xFEU) << 15) |  \
       (((x).lsa_id[1] & 0xFFU) << 7)  |  \
       (((x).lsa_id[2] & 0xFEU) >> 1) )

/***********************************************************************
 * Layer 3 Information.
 * Ref: 3.2.2.24
 * 'layer3_info' contains the radio interface messages.
 */
typedef struct
{
    ITS_OCTET    layer3_info[1];
}
BSSAP_Layer3Info;

/***********************************************************************
 * Supported Codecs List
 * Ref: 10.5.4.32
 */
typedef struct
{
    ITS_OCTET  value[1];
}
BSSAP_SupportedCodecs_IE;

/* System ID -- Reference 3GPP TS 26.103 Section 6.1 */
#define SYS_ID_GSM     0x00U
#define SYS_ID_UMTS    0x04U

/***********************************************************************
 * DLCI - Data Link Connection Identification
 * Ref: 3.2.2.25
 *      GSM 08.06 Section 6.3.2
 *  DLCI -> 1 byte -> c2 c1 x x x s3 s2 s1
 *    c2, c1 - for control channel identification.
 *     s3,s2,s1 - for radio channel identification (SAPI) 
 */
typedef struct
{
    ITS_OCTET    dlci;
}
BSSAP_DLCI;

/* Control Channel fields */
#define DLCI_CONTROL_CHANNEL_NOT_SPECIFIED    0x00U
#define DLCI_FACCH_OR_SDCCH                   0x02U
#define DLCI_SACCH                            0x03U
#define DLCI_CONTROL_CHANNEL_BITS             0xC0U

#define DLCI_SET_CONTROL_CHANNEL(x,y)                \
    (((x).dlci &= ~DLCI_CONTROL_CHANNEL_BITS),        \
      (x).dlci |= ((y) << 6) & DLCI_CONTROL_CHANNEL_BITS)

#define DLCI_GET_CONTROL_CHANNEL(x)                \
    (((x).dlci & DLCI_CONTROL_CHANNEL_BITS) >> 6)

/* Radio channel fields (SAPI) - GSM 04.06*/
#define DLCI_SAPI_CMRS              0x00U
#define DLCI_SAPI_SHORT_MSG_SVS     0x03U
// All others are reserved

#define DLCI_SAPI_BITS              0x07U

#define DLCI_SET_SAPI(x,y)                \
    (((x).dlci &= ~DLCI_SAPI_BITS),        \
      (x).dlci |= ((y) & DLCI_SAPI_BITS))

#define DLCI_GET_SAPI(x)                \
    ((x).dlci & DLCI_SAPI_BITS)

/***********************************************************************
 * Downlink DTX Flag
 * Ref: 3.2.2.26
 */
typedef struct
{
    ITS_OCTET    downLink_DTX;
}
BSSAP_DownlinkDTX;

#define DLDTX_ACTIVATE_ALLOWED         0x00U
#define DLDTX_ACTIVATE_FORBIDDEN       0x01U
#define DLDTX_BIT                      0x01U

#define DLDTX_SET_DOWNLINK(x,y)                    \
    (x).downLink_DTX = (y)

#define DLDTX_GET_DOWNLINK(x)                \
    ((x).downLink_DTX)

/***********************************************************************
 * Cell Identifier List
 * Ref: 3.2.2.27
 *     Note:     Similar to 'Cell Identifier'.
 *        See BSSAP_CellGlobalId, BSSAP_Lac_Ci, BSSAP_Ci under 'Cell Identifer'.
 */
typedef struct
{
    ITS_OCTET    MCC[2];    // Mobile Country Code 
    ITS_OCTET    MNC;       // Mobile Network Code 
    ITS_OCTET    LAC[2];    // Location Area Code 
}
BSSAP_Lai;

typedef struct
{
    ITS_OCTET    LAC[2];    // Location Area Code 
}
BSSAP_Lac;

typedef union 
{
    BSSAP_CellGlobalId  cgi;
    BSSAP_Lac_Ci        lac_ci;
    BSSAP_Ci            ci;
    BSSAP_Lai           lai;
    BSSAP_Lac           lac;
    BSSAP_Plmn_Lac_Rnc  plmn_lac_rnc;
    BSSAP_Rnc           rnc;  
    BSSAP_Lac_Rnc       lac_rnc;
}
BSSAP_CellIDT;

typedef struct
{
    ITS_OCTET         cell_id_discriminator;
    BSSAP_CellIDT     cell_id[1];
}
BSSAP_CellIdentifierList;

#define CIL_CID_CGI           0x00U // Cell Global ID
#define CIL_CID_LAC_CI        0x01U // Location Area Code and Cell Id
#define CIL_CID_CI            0x02U // Cell Identity
#define CIL_CID_NONE          0x03U // No cell is associated with this transacn
#define CIL_CID_LAI           0x04U // Location Area Identification
#define CIL_CID_LAC           0x05U // Location Area Code
#define CIL_CID_ALL_CELLS     0x06U // All cells on the BSS are identified
#define CIL_CID_PLMN_LAC_RNC  0x08U // Intersystem handover to UTRAN or cdma2000
#define CIL_CID_RNC           0x09U // Intersystem handover to UTRAN or cdma2000
#define CIL_CID_LAC_RNC       0x10U // Intersystem handover to UTRAN or cdma2000

#define CIL_SET_CELL_ID_DISCRIMINATOR(x,y)            \
    ((x).cell_id_discriminator = ((y) & 0x0FU))

#define CIL_GET_CELL_ID_DISCRIMINATOR(x)            \
    ((x).cell_id_discriminator)

/* CGI */
// MCC and MNC -- For GSM 900 and DCS 1800
// Populate bit 1 - bit 12
#define CIL_CGI_SET_MCC_GSM_DCS(x,y)                                \
    ((x).cgi.MCC[0] = (((y) >> 4) & 0xFFU),                 \
     (x).cgi.MCC[1] = ((y) | 0xF0U))

#define CIL_CGI_GET_MCC_GSM_DCS(x)                                  \
    ((x).cgi.MCC[0] << 4 | ((x).cgi.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CIL_CGI_SET_MNC_GSM_DCS(x,y)                                \
    ((x).cgi.MNC = (y) & 0xFFU)    
                           
#define CIL_CGI_GET_MNC_GSM_DCS(x)                                  \
    ((x).cgi.MNC & 0xFFU)

// MCC and MNC -- For PCS 1900 for NA
// Populate bit 1 - bit 12
#define CIL_CGI_SET_MCC_PCS(x,y)                                \
    ((x).cgi.MCC[0] = (((y) >> 4) & 0xFFU),                 \
     (x).cgi.MCC[1] = ((y) & 0x0FU))

#define CIL_CGI_GET_MCC_PCS(x)                                  \
    ((((x).cgi.MCC[0] & 0xFFU)<< 4) | ((x).cgi.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CIL_CGI_SET_MNC_PCS(x,y)                                \
     (((x).cgi.MNC = (y) & 0xFFU),                              \
      ((x).cgi.MCC[1] |= ((y) >> 4) & 0xF0U))
                           
#define CIL_CGI_GET_MNC_PCS(x)                                  \
    (((x).cgi.MNC & 0xFFU) | (((x).cgi.MCC[1] & 0xF0) << 4))

// LAC
#define CIL_CGI_SET_LAC(x,y)                            \
    ((x).cgi.LAC[0] = (((y) >> 8) & 0xFFU),             \
     (x).cgi.LAC[1] = ((y) & 0xFFU))

#define CIL_CGI_GET_LAC(x)                   \
    (((x).cgi.LAC[0] << 8 ) | (x).cgi.LAC[1])

// CI
#define CIL_CGI_SET_CI(x,y)                             \
    ((x).cgi.CI[0] = (((y) >> 8) & 0xFFU),              \
     (x).cgi.CI[1] = ((y) & 0xFFU))

#define CIL_CGI_GET_CI(x)                               \
    (((x).cgi.CI[0] << 8 ) | (x).cgi.CI[1])

/* LAC & CI */
#define CIL_LACCI_SET_LAC(x,y)                          \
    ((x).u.lac_ci.LAC[0] = (((y) >> 8) & 0xFFU),        \
     (x).lac_ci.LAC[1] = ((y) & 0xFFU))

#define CIL_LACCI_GET_LAC(x)                             \
    (((x).lac_ci.LAC[0] << 8 ) | (x).lac_ci.LAC[1])

#define CIL_LACCI_SET_CI(x,y)                            \
    ((x).lac_ci.CI[0] = (((y) >> 8) & 0xFFU),            \
     (x).lac_ci.CI[1] = ((y) & 0xFFU))

#define CIL_LACCI_GET_CI(x)                              \
    (((x).lac_ci.CI[0] << 8 ) | (x).lac_ci.CI[1])

/* CI */
#define CIL_CI_SET_CI(x,y)                              \
    ((x).ci.CI[0] = (((y) >> 8) & 0xFFU),               \
        (x).ci.CI[1] = ((y) & 0xFFU))

#define CIL_CI_GET_CI(x)                                \
    (((x).ci.CI[0] << 8 ) | (x).ci.CI[1])

/* LAI */
// MCC and MNC -- For GSM 900 and DCS 1800
// Populate bit 1 - bit 12
#define CIL_LAI_SET_MCC_GSM_DCS(x,y)                                \
    ((x).lai.MCC[0] = (((y) >> 4) & 0xFFU),                 \
     (x).lai.MCC[1] = ((y) | 0xF0U))

#define CIL_LAI_GET_MCC_GSM_DCS(x)                                  \
   ( ( ((x).lai.MCC[0] & 0x0f) * 10 + (((x).lai.MCC[0] & 0xf0 ) >> 4) ) * 10 ) + \
                        ((x).lai.MCC[1] & 0x0f)

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CIL_LAI_SET_MNC_GSM_DCS(x,y)                                \
    ((x).lai.MNC = (y) & 0xFFU)    
                           
#define CIL_LAI_GET_MNC_GSM_DCS(x)                                  \
         ( ((x).lai.MNC & 0x0f) * 10 ) + ( ((x).lai.MNC & 0xf0) >> 4)


#define CIL_LAI_GET_MNC_GSM_DCS_3_DIGITS(x)                                  \
     ( ( (((x).lai.MNC & 0x0f) * 10) + ( ( (x).lai.MNC & 0xf0) >> 4) ) * 10 ) + \
                        ( ((x).lai.MCC[1] & 0xf0) >> 4 )

// MCC and MNC -- For PCS 1900 for NA
// Populate bit 1 - bit 12
#define CIL_LAI_SET_MCC_PCS(x,y)                                \
    ((x).lai.MCC[0] = (((y) >> 4) & 0xFFU),                 \
     (x).lai.MCC[1] = ((y) & 0x0FU))

#define CIL_LAI_GET_MCC_PCS(x)                                  \
    ((((x).lai.MCC[0] & 0xFFU)<< 4) | ((x).lai.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CIL_LAI_SET_MNC_PCS(x,y)                                \
     (((x).lai.MNC = (y) & 0xFFU),                               \
      ((x).lai.MCC[1] |= ((y) >> 4) & 0xF0U))
                           
#define CIL_LAI_GET_MNC_PCS(x)                                  \
    (((x).lai.MNC & 0xFFU) | (((x).lai.MCC[1] & 0xF0) << 4))

// LAC
#define CIL_LAI_SET_LAC(x,y)                            \
    ((x).lai.LAC[0] = (((y) >> 8) & 0xFFU),           \
         (x).lai.LAC[1] = ((y) & 0xFFU))

#define CIL_LAI_GET_LAC(x)                   \
    (((x).lai.LAC[0] << 8 ) | (x).lai.LAC[1])

/* LAC */
#define CIL_LAC_SET_LAC(x,y)                               \
    ((x).lac.LAC[0] = (((y) >> 8) & 0xFFU),              \
     (x).lac.LAC[1] = ((y) & 0xFFU))

#define CIL_LAC_GET_LAC(x)                                 \
    (((x).lac.LAC[0] << 8 ) | (x).lac.LAC[1])

/* PLMN_LAC_RNC */
// MCC
// Populate bit 1 - bit 12
#define CIL_PLR_SET_MCC(x,y)                                \
    ((x).plmn_lac_rnc.MCC[0] = (((y) >> 4) & 0xFFU),                 \
     (x).plmn_lac_rnc.MCC[1] = ((y) & 0x0FU))

#define CIL_PLR_GET_MCC(x)                                  \
    ( ( ((x).plmn_lac_rnc.MCC[0] & 0x0f) * 10 + (((x).plmn_lac_rnc.MCC[0] & 0xf0 ) >> 4) ) * 10 ) + \
                        ((x).plmn_lac_rnc.MCC[1] & 0x0f)

// MNC Needs to be BCD encoded 
// Populate bit 1 - bit 12
// Here, y - int 
#define CIL_PLR_SET_MNC(x,y)                                \
     (((x).plmn_lac_rnc.MNC = (y) & 0xFFU),                               \
      ((x).plmn_lac_rnc.MCC[1] |= ((y) >> 4) & 0xF0U))
                           
#define CIL_PLR_GET_MNC(x)                                  \
         ( ((x).plmn_lac_rnc.MNC & 0x0f) * 10 ) + ( ((x).plmn_lac_rnc.MNC & 0xf0) >> 4)

#define CIL_PLR_GET_MNC_3_DIGITS(x)                                  \
    ( ( (((x).plmn_lac_rnc.MNC & 0x0f) * 10) + ( ( (x).plmn_lac_rnc.MNC & 0xf0) >> 4) ) * 10 ) + \
                        ( ((x).plmn_lac_rnc.MCC[1] & 0xf0) >> 4 )

// LAC
#define CIL_PLR_SET_LAC(x,y)                                \
    ((x).plmn_lac_rnc.LAC[0] = (((y) >> 8) & 0xFFU),                 \
     (x).plmn_lac_rnc.LAC[1] = ((y) & 0xFFU))

#define CIL_PLR_GET_LAC(x)                                  \
    (((x).plmn_lac_rnc.LAC[0] << 8 ) | (x).plmn_lac_rnc.LAC[1])

// RNC-ID
#define CIL_PLR_SET_RNC_ID(x,y)                                \
    ((x).plmn_lac_rnc.RNCILD[0] = (((y) >> 8) & 0xFFU),                 \
     (x).plmn_lac_rnc.RNCILD[1] = ((y) & 0xFFU))

#define CIL_PLR_GET_RNC_ID(x)                                  \
    (((x).plmn_lac_rnc.RNCILD[0] << 8 ) | (x).plmn_lac_rnc.RNCILD[1])

/* RNC-ID */
#define CIL_RNC_SET_RNC_ID(x,y)                                \
    ((x).rnc.RNCILD[0] = (((y) >> 8) & 0xFFU),                 \
     (x).rnc.RNCILD[1] = ((y) & 0xFFU))

#define CIL_RNC_GET_RNC_ID(x)                                  \
    (((x).rnc.RNCILD[0] << 8 ) | (x).rnc.RNCILD[1])

/* LAC_RNC */
// LAC
#define CIL_LR_SET_LAC(x,y)                                \
    ((x).lac_rnc.LAC[0] = (((y) >> 8) & 0xFFU),            \
     (x).lac_rnc.LAC[1] = ((y) & 0xFFU))

#define CIL_LR_GET_LAC(x)                                  \
    (((x).lac_rnc.LAC[0] << 8 ) | (x).lac_rnc.LAC[1])

// RNC-ID
#define CIL_LR_SET_RNC_ID(x,y)                                \
    ((x).lac_rnc.RNCILD[0] = (((y) >> 8) & 0xFFU),            \
     (x).lac_rnc.RNCILD[1] = ((y) & 0xFFU))

#define CIL_LR_GET_RNC_ID(x)                                  \
    (((x).lac_rnc.RNCILD[0] << 8 ) | (x).lac_rnc.RNCILD[1])

/***********************************************************************
 * Response Request.
 * Ref: 3.2.2.28
 * Only element identifier in this IE.
 */

/***********************************************************************
 * Resource Indication Method
 * Ref: 3.2.2.29
 * Note: The values are subclause of section 3.1.3.1
 */
typedef struct
{
    ITS_OCTET    resource_ind_method;
}
BSSAP_ResourceIndMethod;

#define RIM_SUBCLAUSE_1    0x00U
#define RIM_SUBCLAUSE_2    0x01U
#define RIM_SUBCLAUSE_3    0x02U
#define RIM_SUBCLAUSE_4    0x03U

#define RIM_SET_RES_IND_METHOD(x,y)            \
    ((x).resource_ind_method = ((y) & 0x0FU))

#define RIM_GET_RES_IND_METHOD(x)            \
    ((x).resource_ind_method & 0x0FU)

/***********************************************************************
 * Classmark Information type 1.
 * Ref: 3.2.2.30
 *      GSM04.08 Section 10.5.1.5
 */
typedef struct
{
    ITS_OCTET   data_4field;  /* Has Revision level, ES, A5/1, RF cap. */
}
BSSAP_ClassmarkInfoType1;

/* 'Revision Level' */
#define CIT1_REV_LEVEL_PHASE_1      0x00U
#define CIT1_REV_LEVEL_PHASE_2      0x01U
#define CIT1_REV_LEVEL_BITS         0x60U

#define CIT1_SET_REV_LEVEL(x,y)                        \
    (((x).data_4field &= ~CIT1_REV_LEVEL_BITS),          \
      (x).data_4field |= ((y) << 6) & CIT2_REV_LEVEL_BITS)

#define CIT1_GET_REV_LEVEL(x)            \
    (((x).data_4field & CIT1_REV_LEVEL_BITS) >> 6)

/* 'ES Ind' */
#define CIT1_ES_IND_IS_IMPLEMENTED       0x00U
#define CIT1_ES_IND_IS_NOT_IMPLEMENTED   0x01U
#define CIT1_ES_IND_BIT                  0x10U

#define CIT1_SET_ES_IND(x,y)                             \
    (((x).data_4field &= ~CIT1_ES_IND_BIT),              \
      (x).data_4field |= ((y) << 4) & CIT1_ES_IND_BIT)

#define CIT1_GET_ES_IND(x)                               \
    (((x).data_4field & CIT1_ES_IND_BIT) >> 4)

/* A5/1 */
#define CIT1_A5_1_IS_AVAILABLE        0x00U
#define CIT1_A5_1_IS_NOT_AVAILABLE    0x01U
#define CIT1_A5_1_IND_BIT             0x08U

#define CIT1_SET_A5_1_IND(x,y)                              \
    (((x).data_4field &= ~CIT1_A5_1_IND_BIT),               \
      (x).data_4field |= ((y) << 3 ) & CIT1_A5_1_IND_BIT)

#define CIT1_GET_A5_1_IND(x)                    \
    (((x).data_4field & CIT1_A5_1_IND_BIT) >> 3)

/* 'RF Power capabilities' */
#define CIT1_RF_POWER_CAP_CLASS1      0x00U
#define CIT1_RF_POWER_CAP_CLASS2      0x01U
#define CIT1_RF_POWER_CAP_CLASS3      0x02U
#define CIT1_RF_POWER_CAP_CLASS4      0x03U
#define CIT1_RF_POWER_CAP_CLASS5      0x04U
#define CIT1_RF_POWER_CAP_IND_BITS    0x07U

#define CIT1_SET_RF_POWER_CAP(x,y)                    \
    (((x).data_4field &= ~CIT1_RF_POWER_CAP_IND_BITS),              \
      (x).data_4field |= ((y)  & CIT1_RF_POWER_CAP_IND_BITS))

#define CIT1_GET_RF_POWER_CAP(x)                    \
    ((x).data_4field & CIT1_RF_POWER_CAP_IND_BITS)

/***********************************************************************
 * Circuit Identity Code List
 * Ref: 3.2.2.31
 */
typedef struct
{
    ITS_OCTET    range;
    ITS_OCTET    status[1];
}
BSSAP_CircuitIdCodeList;

#define CCL_SET_RANGE(x,y) ((x).range = (y) & 0xFFU) 
#define CCL_GET_RANGE(x)   ((x).range & 0xFFU) 

/***********************************************************************
 * Diagnostics
 * Ref: 3.2.2.32
 *
 * Note 1: For the first octet of error_pointer, the intermediate values 0x02U
 *       to 0x0FBU represent erroneous Octet number. It is left to the application
 *       to provide the correct values as it would not make sense to #define them here.
 * Note 2: The 'message_received' represents an 'n' Octet field. It is left to the
 *       application to decide and provide the data in it.
 */
typedef struct
{
    ITS_OCTET    error_pointer[2];
    ITS_OCTET    message_received[1];
}
BSSAP_Diagnostics;

#define DIAG_ERROR_LOCATION_NOT_DETERMINED     0x00U
#define DIAG_ERRONEOUS_OCTET_1                 0x01U
#define DIAG_ERRONEOUS_OCTET_252               0xFCU
#define DIAG_ERRONEOUS_BSSAP_HEADER_OCTET_1    0xFDU   /* Discrimination */
#define DIAG_ERRONEOUS_BSSAP_HEADER_OCTET_2    0xFEU   /* DLCI */
#define DAIG_ERRONEOUS_BSSAP_HEADER_OCTET_3    0xFFU   /* length */

#define DIAG_SET_ERROR_POINTER(x,y)            \
    ((x).error_pointer[0] = ((y) & 0xFFU))

#define DIAG_GET_ERROR_POINTER(x)            \
    ((x).error_pointer[0] & 0xFFU)

#define DIAG_NO_ERROR                   0x00U
#define DIAG_ERROR_BIT_POSITION_1       0x01U
#define DIAG_ERROR_BIT_POSITION_2       0x02U
#define DIAG_ERROR_BIT_POSITION_3       0x03U
#define DIAG_ERROR_BIT_POSITION_4       0x04U
#define DIAG_ERROR_BIT_POSITION_5       0x05U
#define DIAG_ERROR_BIT_POSITION_6       0x06U
#define DIAG_ERROR_BIT_POSITION_7       0x07U
#define DIAG_ERROR_BIT_POSITION_8       0x08U

#define DIAG_SET_ERROR_BIT_POSITION(x,y)        \
    ((x).error_pointer[1] = ((y) & 0x0FU))

#define DIAG_GET_ERROR_BIT_POSITION(x)            \
    ((x).error_pointer[1] & 0x0FU)

/***********************************************************************
 * Chosen Channel
 * Ref: 3.2.2.33
 */
typedef struct
{
    ITS_OCTET    data_2field;
}
BSSAP_ChosenChannel;

/* channel mode */
#define CC_CH_NO_CHANNEL        0x00U
#define CC_CH_SPEECH            0x09U   /* Speech. Full rate or Half rate */
#define CC_CH_DATA_14_5_KBPS    0x0EU   /* Data. 14.5 kbps */
#define CC_CH_DATA_12_KBPS      0x0BU   /* Data. 12 kbps */
#define CC_CH_DATA_6_KBPS       0x0CU   /* Data. 6 kbps */
#define CC_CH_DATA_3_6_KBPS     0x0DU   /* Data. 3.6 kbps */
#define CC_CH_DATA_SIGNALING    0x08U   /* Signaling only */
#define CC_CH_CHANNEL_BITS      0x0FU

#define CC_SET_CHANNEL(x,y)            \
    (((x).data_2field &= ~CC_CHANNEL_BITS),    \
      (x).data_2field |= ((y) & CC_CHANNEL_BITS))

#define CC_GET_CHANNEL(x)                \
    ((x).data_2field & CC_CHANNEL_BITS)

/* channel */
#define CC_CM_NONE              0x00U
#define CC_CM_SDCCH             0x01U
#define CC_CM_1_FULL_RATE_TCH   0x08U
#define CC_CM_1_HALF_RATE_TCH   0x09U
#define CC_CM_2_FULL_RATE_TCH   0x0AU
#define CC_CM_3_FULLRATE_TCH    0x0BU
#define CC_CM_4_FULLRATE_TCH    0x0CU
#define CC_CM_5_FULLRATE_TCH    0x0DU
#define CC_CM_6_FULLRATE_TCH    0x0EU
#define CC_CM_7_FULLRATE_TCH    0x0FU
#define CC_CM_8_FULLRATE_TCH    0x04U
#define CC_CHANNEL_MODE_BITS    0xF0U

#define CC_SET_CHANNEL_MODE(x,y)                \
    (((x).data_2field &= ~CC_CHANNEL_MODE_BITS),        \
      (x).data_2field |= (((y) << 4) & CC_CHANNEL_MODE_BITS))

#define CC_GET_CHANNEL_MODE(x)                    \
    (((x).data_2field & CC_CHANNEL_MODE_BITS) >> 4)

/***********************************************************************
 * Cipher Response Mode
 * Ref: 3.2.2.34
 */
typedef struct
{
    ITS_OCTET    cipher_resp_mode;
}
BSSAP_CipherResponseMode;

#define CRM_IMEISV_NOT_INCLUDED     0x00U
#define CRM_IMEISV_INLCUDED         0x01U    
#define CRM_IND_BIT                 0x01U

#define CRM_SET_INDICATOR(x,y)                \
    ((x).cipher_resp_mode = ((y) & CRM_IND_BIT))

#define CRM_GET_INDICATOR(x)                \
    ((x).cipher_resp_mode & CRM_IND_BIT)

/***********************************************************************
 * Layer3 Message Contents
 * Ref: 3.2.2.35
 * 
 * Note: The actual radio interface layer 3 message content. No IE for this.
 */
typedef struct
{
    ITS_OCTET   l3MsgCnt[1];
}
BSSAP_L3MessageContents;

/***********************************************************************
 * Channel Needed
 * Ref: 3.2.2.36
 */
typedef struct
{
    ITS_OCTET    channel;
}
BSSAP_ChannelNeeded;

#define CN_CHANNEL_ANY_CHANNEL       0x00U
#define CN_CHANNEL_SDCCH             0x01U
#define CN_CHANNEL_TCH_F             0x02U
#define CN_CHANNEL_TCH_H_OR_TCH_F    0x03U
#define CN_CHANNEL_INDICATOR_BITS    0x0FU

#define CN_CHANNEL_SET_CHANNEL_NEEDED(x,y)        \
    ((x).channel = ((y) & CN_CHANNEL_INDICATOR_BITS))

#define CN_CHANNEL_GET_CHANNEL_NEEDED(x)        \
    ((x).channel & CN_CHANNEL_INDICATOR_BITS)

/***********************************************************************
 * Trace Type
 * Ref: 3.2.2.37
 *     defined in GSM 12.08 MSC/BSS Trace Type
 */
typedef struct
{
    ITS_OCTET    traceType;
}
BSSAP_TraceType;

// Invoking Events
#define TT_IE_ELEVEN_EVENTS          0x00
#define TT_IE_SEVEN_EVENTS           0x01
#define TT_IE_THREE_EVENTS           0x02
#define TT_IE_OPERATOR               0x03
#define TT_IE_BITS                   0x03U

#define TT_SET_INVOKE_EVENTS(x,y)        \
    ((x).traceType = ((y) & TT_IE_BITS))

#define TT_GET_INVOKE_EVENTS(x)        \
    ((x).traceType & TT_IE_BITS )

// MSC Record Type          
#define TT_MRT_BASIC                 0x00
#define TT_MRT_DETAILED              0x01
#define TT_MRT_SPARE                 0x02
#define TT_MRT_NO_MSC_TRACE          0x03
#define TT_MRT_BITS                  0x0CU

#define TT_SET_MSC_RECORD_TYPE(x,y)        \
    ((x).traceType |= (((y) << 2) & TT_MRT_BITS))

#define TT_GET_MSC_RECORD_TYPE(x)        \
    (((x).traceType & TT_MRT_BITS) >> 2)

// BSS Record Type 
#define TT_BRT_BASIC                 0x00
#define TT_BRT_HANDOVER              0x01
#define TT_BRT_RADIO                 0x02
#define TT_BRT_NO_BSS_TRACE          0x03
#define TT_BRT_BITS                  0x30U

#define TT_SET_BSS_RECORD_TYPE(x,y)        \
    ((x).traceType |= (((y) << 4) & TT_BRT_BITS))

#define TT_GET_BSS_RECORD_TYPE(x)        \
    (((x).traceType & TT_BRT_BITS) >> 4)

// Priority Indication
#define TT_PI_NO_PRI                 0x00
#define TT_PI_PRI                    0x01
#define TT_PI_BITS                   0x80U

#define TT_SET_PRI_IND(x,y)        \
    ((x).traceType |= (((y) << 7) & TT_PI_BITS))

#define TT_GET_PRI_IND(x)        \
    (((x).traceType & TT_PI_BITS) >> 7)

/***********************************************************************
 * Trigger ID
 * Ref: 3.2.2.38
 *      See OMC Id
 */
typedef struct
{
    ITS_OCTET    entityId[1];
}
BSSAP_TriggerID;

/***********************************************************************
 * Trace Reference
 * Ref: 3.2.2.39
 */
typedef struct
{
    ITS_OCTET    traceRef[2];
}
BSSAP_TraceReference;

#define TR_SET_TRACE_REFERENCE(x,y)                    \
    (((x).traceRef[0] = (((y) & 0xFF00U) >> 8 )),  \
      (x).traceRef[1] = ((y) & 0x00FF))

#define TR_GET_TRACE_REFERENCE(x)            \
    (((x).traceRef[0] << 8) | ((x).traceRef[1]))

/***********************************************************************
 * Transaction Identifier
 * Ref: 3.2.2.40
 */
typedef struct
{
    ITS_OCTET    transId[2];
}
BSSAP_TransactionId;

#define TI_SET_TRANSACTION_ID(x,y)                    \
    (((x).transId[0] = (((y) & 0xFF00U) >> 8 )),   \
      (x).transId[1] = ((y) & 0x00FF))

#define TI_GET_TRANSACTION_ID(x)                    \
    (((x).transId[0] << 8) | ((x).transId[1]))

/***********************************************************************
 * Mobile Identity
 * Ref: 3.2.2.41
 *
 * The content is one of IMSI, IMEISV or IMEI. Encoding is Packed BCD.
 */
typedef struct
{
    ITS_OCTET    data_3field;
    ITS_OCTET    digit[1];
}
BSSAP_MobileIdentity;

/* 'data_3field' ITS_OCTET has 3 bits for type of identity, */
/* 4th bit for odd/even indicator. */
#define MI_NO_ID_CODE         0x00U
#define MI_IMSI               0x01U
#define MI_IMEI               0x02U
#define MI_IMEISV             0x03U
#define MI_EVEN_DIGITS        0x00U
#define MI_ODD_DIGITS         0x01U
#define MI_ODD_EVEN_BIT       0x08U

#define MI_SET_ODD_EVEN_IND(x,y)                        \
    ((x).data_3field &= ~MI_ODD_EVEN_BIT,               \
     (x).data_3field |= ((y) << 3) & MI_ODD_EVEN_BIT)
#define MI_GET_ODD_EVEN_IND(x)                          \
    (((x).data_3field & MI_ODD_EVEN_BIT) >> 3)

#define MI_TYPE_IDENTITY_BIT  0x07U

#define MI_SET_TYPE_IDENTITY(x,y)                       \
    ((x).data_3field &= ~MI_TYPE_IDENTITY_BIT,          \
     (x).data_3field |= (y) & MI_TYPE_IDENTITY_BIT)
#define MI_GET_TYPE_IDENTITY(x)                         \
    ((x).data_3field & MI_TYPE_IDENTITY_BIT)

/***********************************************************************
 * OMCID
 * Ref: 3.2.2.42
 *      TS 12.20
 */
typedef struct
{
    ITS_OCTET    omcId[1];
}
BSSAP_Omcid;

/***********************************************************************
 * Forward Indicator
 * Ref: 3.2.2.43
 */
typedef struct
{
    ITS_OCTET    forwardInd;
}
BSSAP_ForwardInd;

#define FI_FORWARD_NO_TRACE         0x01U
#define FI_FORWARD_TRACE            0x02U
#define FI_FORWARD_TRACE_IND_BITS   0x0FU

#define FI_FORWARD_SET_INDICATOR(x,y)        \
    ((x).forwardInd = ((y) & FI_FORWARD_TRACE_IND_BITS))

#define FI_FORWARD_GET_INDICATOR(x)        \
    ((x).forwardInd & FI_FORWARD_TRACE_IND_BITS)

/***********************************************************************
 * Chosen Encryption Algorithm
 * Ref: 3.2.2.44
 */
typedef struct
{
    ITS_OCTET    algorithmId;
}
BSSAP_ChosenEncrptAlgorithm;

#define CEA_NO_ENCRYPTION       0x01U
#define CEA_GSM_A_5_1           0x02U    /* GSM A5/1 */
#define CEA_GSM_A_5_2           0x03U    /* GSM A5/2 */
#define CEA_GSM_A_5_3           0x04U    /* GSM A5/3 */
#define CEA_GSM_A_5_4           0x05U    /* GSM A5/4 */
#define CEA_GSM_A_5_5           0x06U    /* GSM A5/5 */
#define CEA_GSM_A_5_6           0x07U    /* GSM A5/6 */
#define CEA_GSM_A_5_7           0x08U    /* GSM A5/7 */

#define CEA_SET_ENCRYPTION_ID(x,y)        \
    ((x).algorithmId = ((y) & 0xFFU))

#define CEA_GET_ENCRYPTION_ID(x)        \
    ((x).algorithmId & 0xFFU)

/***********************************************************************
 * Circuit Pool
 * Ref: 3.2.2.45
 */
typedef struct
{
    ITS_OCTET    circuitPoolNum;
}
BSSAP_CircuitPool;

#define CP_NUMBER_1         0x01U
#define CP_NUMBER_2         0x02U
#define CP_NUMBER_3         0x03U
#define CP_NUMBER_4         0x04U
#define CP_NUMBER_5         0x05U
#define CP_NUMBER_6         0x06U
#define CP_NUMBER_7         0x07U
#define CP_NUMBER_8         0x08U
#define CP_NUMBER_9         0x09U
#define CP_NUMBER_10        0x0AU
#define CP_NUMBER_11        0x0BU
#define CP_NUMBER_12        0x0CU
#define CP_NUMBER_13        0x0DU
#define CP_NUMBER_14        0x0EU
#define CP_NUMBER_15        0x0FU
#define CP_NUMBER_16        0x10U
#define CP_NUMBER_17        0x11U
#define CP_NUMBER_18        0x12U
#define CP_NUMBER_19        0x13U
#define CP_NUMBER_20        0x14U
#define CP_NUMBER_21        0x15U
#define CP_NUMBER_22        0x16U
#define CP_NUMBER_23        0x17U
#define CP_NUMBER_24        0x18U
#define CP_NUMBER_25        0x19U
#define CP_NUMBER_26        0x1AU
#define CP_NUMBER_27        0x1BU
#define CP_NUMBER_28        0x1CU
#define CP_NUMBER_29        0x1DU
#define CP_NUMBER_30        0x1EU
#define CP_NUMBER_31        0x1FU
#define CP_NUMBER_32        0x20U
#define CP_NUMBER_33        0x21U
#define CP_NUMBER_34        0x22U
#define CP_NUMBER_35        0x23U

#define CP_SET_CIRCUIT_POOL_NUM(x,y)        \
    ((x).circuitPoolNum = ((y) & 0xFFU))

#define CP_GET_CIRCUIT_POOL_NUM(x)        \
    ((x).circuitPoolNum & 0xFFU)

/***********************************************************************
 * Circuit Pool List
 * Ref: 3.2.2.46
 *
 * Note: This is a list of Circuit Pool Number, whose values are given 
 *       above. The set and get is left to the application.
 */
typedef struct
{
    BSSAP_CircuitPool    cktPlList[1];
}
BSSAP_CircuitPoolList;

/***********************************************************************
 * Time Indication
 * Ref: 3.2.2.47
 */
typedef struct
{
    ITS_OCTET    time;
}
BSSAP_TimeIndication;

#define TI_SET_TIME_VAL(x,y)        \
    ((x).time = ((y) & 0xFFU))

#define TI_GET_TIME_VAL(x)        \
    ((x).time & 0xFFU)

/***********************************************************************
 * Resource Situation
 * Ref: 3.2.2.48
 */
typedef struct
{
    ITS_OCTET    resource_type;
    ITS_OCTET    num_of_channels[2];
}
BSSAP_ResSitnElmnt;

typedef struct
{
    BSSAP_ResSitnElmnt    res_sitn[1];
}
BSSAP_ResourceSituation;

/* 'channel type' */
#define    RS_CHANNEL_TYPE_SDCCH           0x01U
#define    RS_CHANNEL_TYPE_FULL_RATE_TCH   0x08U
#define    RS_CHANNEL_TYPE_HALF_RATE_TCH   0x09U
#define    RS_CHANNEL_TYPE_IND_BITS        0x0FU

#define RS_SET_CHANNEL_TYPE(x,y)                \
    (((x).resource_type &= ~RS_CHANNEL_TYPE_IND_BITS),     \
      (x).resource_type |= ((y) & RS_CHANNEL_TYPE_IND_BITS))

#define RS_GET_CHANNEL_TYPE(x)                    \
    ((x).resource_type & RS_CHANNEL_TYPE_IND_BITS)

/* 'resource and interference band indicator' */
#define RS_RIBI_TOT_NUM_OF_CHANNELS_ACCESSIBLE   0x00U
#define RS_RIBI_INTERFERENCE_BAND_1              0x01U
#define RS_RIBI_INTERFERENCE_BAND_2              0x02U
#define RS_RIBI_INTERFERENCE_BAND_3              0x03U
#define RS_RIBI_INTERFERENCE_BAND_4              0x04U
#define RS_RIBI_INTERFERENCE_BAND_5              0x05U
#define RS_RIBI_NUM_OF_CHANNELS_AVAILABLE        0x0Eu
#define    RS_RIBI_IND_BITS                      0xF0U

#define RS_SET_RADIO_INT_BAND_IND(x,y)                    \
    (((x).resource_type &= ~RS_RIBI_IND_BITS),            \
      (x).resource_type |= (((y) << 4) & RS_RIBI_IND_BITS))

#define RS_GET_RADIO_INT_BAND_IND(x)                    \
    (((x).resource_type & RS_RIBI_IND_BITS) >> 4)

#define RS_EXTENSION_ABSENT         0x00U
#define RS_EXTENSION_PRESENT        0x01U
#define RS_EXTENSION_IND_BIT        0x80U

#define RS_SET_EXTENSION_BIT(x,y)                    \
    (((x).num_of_channels[0] &= ~RS_EXTENSION_IND_BIT),        \
      (x).num_of_channels[0] |= (((y) << 7) & RS_EXTENSION_IND_BIT))

#define RS_GET_EXTENSION_BIT(x)                \
    (((x).num_of_channels[0] & RS_EXTENSION_IND_BIT) >> 7)

#define RS_BASE_VALUE_IND_BITS            0x7FU
#define RS_EXT_VALUE_IND_BITS            0xFFU

#define RS_SET_NUMBER_OF_CHANNEL_BASE_VALUE(x,y)            \
    (((x).num_of_channels[0] &= ~RS_BASE_VALUE_IND_BITS),        \
      (x).num_of_channels[0] |= ((y) & RS_BASE_VALUE_IND_BITS))

#define RS_GET_NUMBER_OF_CHANNEL_BASE_VALUE(x)        \
    ((x).num_of_channels[0] & RS_BASE_VALUE_IND_BITS)

#define RS_SET_NUMBER_OF_CHANNEL_EXT_VALUE(x,y)                \
    ((x).num_of_channels[1] = ((y) & RS_EXT_VALUE_IND_BITS))

#define RS_GET_NUMBER_OF_CHANNEL_EXT_VALUE(x)                \
    ((x).num_of_channels[1] & RS_EXT_VALUE_IND_BITS)

/***********************************************************************
 * Current Channel Type 1
 * Ref: 3.2.2.49
 */    
typedef struct
{
    ITS_OCTET    data_2field;
}
BSSAP_CurrentChannelType1;

/* 'channel mode' */
#define CC_CHANNEL_MODE_SIGNALING               0x00U
#define CC_CHANNEL_MODE_SPEECH                  0x01U
#define CC_CHANNEL_MODE_DATA_14_5_KBPS          0x06U
#define CC_CHANNEL_MODE_DATA_12_KBPS            0x03U
#define CC_CHANNEL_MODE_DATA_6_KBPS             0x04U
#define CC_CHANNEL_MODE_DATA_3_6_KBPS           0x05U
#define CC_CHANNEL_MODE_DATA_29_KBPS            0x07U
#define CC_CHANNEL_MODE_DATA_32_KBPS            0x08U
#define CC_CHANNEL_MODE_DATA_43_5_KBPS          0x09U
#define CC_CHANNEL_MODE_DATA_43_5_DOWN_14_5_UP  0x02U
#define CC_CHANNEL_MODE_DATA_29_DOWN_14_5_UP    0x0AU
#define CC_CHANNEL_MODE_DATA_43_5_DOWN_29_UP    0x0BU
#define CC_CHANNEL_MODE_DATA_14_5_DOWN_43_5_UP  0x0CU
#define CC_CHANNEL_MODE_DATA_14_5_DOWN_29_UP    0x0DU
#define CC_CHANNEL_MODE_DATA_29_DOWN_43_5_UP    0x0EU
#define CC_CHANNEL_MODE_BITS                    0xF0U

#define CC_CHANNEL_MODE_SET_CHANNEL_MODE(x,y)            \
    (((x).data_2field &= ~CC_CHANNEL_MODE_BITS),        \
      (x).data_2field |= (((y) << 4) & CC_CHANNEL_MODE_BITS))

#define CC_CHANNEL_MODE_GET_CHANNEL_MODE(x)        \
    (((x).data_2field & CC_CHANNEL_MODE_BITS) >> 4)

/* 'channel' */
#define CC_CHANNEL_SDCCH                0x01U
#define CC_CHANNEL_1_FULL_RATE_TCH      0x08U
#define CC_CHANNEL_1_HALF_RATE_TCH      0x09U
#define CC_CHANNEL_2_FULL_RATE_TCH      0x0AU
#define CC_CHANNEL_3_FULL_RATE_TCH      0x0BU
#define CC_CHANNEL_4_FULL_RATE_TCH      0x0CU
#define CC_CHANNEL_5_FULL_RATE_TCH      0x0DU
#define CC_CHANNEL_6_FULL_RATE_TCH      0x0EU
#define CC_CHANNEL_7_FULL_RATE_TCH      0x0FU
#define CC_CHANNEL_8_FULL_RATE_TCH      0x04U
#define CC_CHANNEL_BITS                 0x0FU

#define CC_CHANNEL_SET_CHANNEL(x,y)            \
    (((x).data_2field &= ~CC_CHANNEL_BITS),    \
      (x).data_2field |= ((y) & CC_CHANNEL_BITS))

#define CC_CHANNEL_GET_CHANNEL(x)            \
    ((x).data_2field & CC_CHANNEL_BITS)

/***********************************************************************
 * Queuing Indicator
 * Ref: 3.2.2.50
 */    
typedef struct
{
    ITS_OCTET    data_1field;
}
BSSAP_QueuingIndicator;

#define QI_QUEUING_NOT_ALLOWED  0x00U
#define QI_QUEUING_ALLOWED      0x01U
#define QI_QUEUING_IND_BIT      0x02U

#define QI_SET_QUEUING_IND(x,y)                    \
    (((x).data_1field &= ~QI_QUEUING_IND_BIT),        \
      (x).data_1field |= (((y) << 1) & QI_QUEUING_IND_BIT))

#define QI_GET_QUEUING_IND(x)                    \
    (((x).data_1field & QI_QUEUING_IND_BIT) >> 1)

/***********************************************************************
 * Speech Version
 * Ref: 3.2.2.51
 * 
 * Note: See 'Channel type' IE's 'permitted sppech version Identifier'
 */    
typedef struct
{
    ITS_OCTET    data_1field;
}
BSSAP_SpeechVersion;

#define SV_GSM_FULL_RATE_VER1    0x01U
#define SV_GSM_FULL_RATE_VER2    0x11U
#define SV_GSM_FULL_RATE_VER3    0x21U
#define SV_GSM_HALF_RATE_VER1    0x05U
#define SV_GSM_HALF_RATE_VER2    0x15U
#define SV_GSM_HALF_RATE_VER3    0x25U
#define SV_SPEECH_VER_IND_BITS   0x7FU

#define SV_SET_SPEECH_VERSION(x,y)                \
    (((x).data_1field &= ~SV_SPEECH_VER_IND_BITS),        \
      (x).data_1field |= ((y) & SV_SPEECH_VER_IND_BITS))

#define SV_GET_SPEECH_VERSION(x)                \
    ((x).data_1field & SV_SPEECH_VER_IND_BITS)

/***********************************************************************
 * Assignment Requirement
 * Ref: 3.2.2.52
 */    
typedef struct
{
    ITS_OCTET    data_1field;
}
BSSAP_AssignmentRequirement;

#define AR_DELAYED      0x00U
#define AR_IMMEDIATE    0x01U
#define AR_IND_BITS     0xFFU

#define AR_SET_ASSIGNMENT_REQUIREMENT(x,y)        \
    ((x).data_1field = ((y) & AR_IND_BITS))

#define AR_GET_ASSIGNMENT_REQUIREMENT(x)        \
    ((x).data_1field & AR_IND_BITS)

/***********************************************************************
 * Talker Flag
 * Ref: 3.2.2.54
 *
 * This IE has one octet as Element Identifier and no data fields.
 */    

/***********************************************************************
 * Group Call Reference
 * Ref: 3.2.2.55
 *    GSM 04.08, Section 10.5.1.9 - Descriptive group or broadcast call 
 *  reference
 */    
typedef struct
{
    ITS_OCTET    data_5field[5];
}
BSSAP_GroupCallReference;

/* Binary coding of the group or broadcast call reference.
 *
 * x - BSSAP_GroupCallReference
 * y - unsigned long, 32 bits
 */
#define GCR_CALL_REFERENCE_LOWER_BITS    0xE0U

#define GCR_SET_CALL_REFERENCE(x,y)                                         \
    ((((x).data_5field[3] &= ~GCR_CALL_REFERENCE_LOWER_BITS),               \
       (x).data_5field[3] |= (((y) << 5) & GCR_CALL_REFERENCE_LOWER_BITS)), \
       (x).data_5field[2] = (((y) >> 11) & 0xFFU),                          \
       (x).data_5field[1] = (((y) >> 19) & 0xFFU),                          \
       (x).data_5field[0] = (((y) >> 27) & 0xFFU))

#define GCR_GET_CALL_REFERENCE(x)                               \
    (((x).data_5field[3] >> 5) | ((x).data_5field[2] << 11) |   \
     ((x).data_5field[1] << 19) | ((x).data_5field[0] << 27))

/* 'SF' */
#define GCR_SF_VBS          0x00U
#define GCR_SF_VGCS         0x01U
#define GCR_SF_IND_BIT      0x10U

#define GCR_SET_SF(x,y)                                       \
    (((x).data_5field[3] &= ~GCR_SF_IND_BIT),                 \
      (x).data_5field[3] |= (((y) << 4) & GCR_SF_IND_BIT))

#define GCR_GET_SF(x)                        \
    (((x).data_5field[3] & GCR_SF_IND_BIT) >> 4)

/* 'AF' */
#define GCR_AF_ACK_NOT_REQUIRED    0x00U
#define GCR_AF_ACK_REQUIRED        0x01U
#define GCR_AF_IND_BIT             0x08U

#define GCR_SET_AF(x,y)                                      \
    (((x).data_5field[3] &= ~GCR_AF_IND_BIT),                \
      (x).data_5field[3] |= (((y) << 3) & GCR_AF_IND_BIT))

#define GCR_GET_AF(x)                        \
    (((x).data_5field[3] & GCR_AF_IND_BIT) >> 3)

/* 'call priority' */
#define GCR_CALL_PRIORITY_NO_PRI    0x00U
#define GCR_CALL_PRIORITY_LEVEL_4   0x01U
#define GCR_CALL_PRIORITY_LEVEL_3   0x02U
#define GCR_CALL_PRIORITY_LEVEL_2   0x03U
#define GCR_CALL_PRIORITY_LEVEL_1   0x04U
#define GCR_CALL_PRIORITY_LEVEL_0   0x05U
#define GCR_CALL_PRIORITY_LEVEL_B   0x06U
#define GCR_CALL_PRIORITY_LEVEL_A   0x07U
#define GCR_CALL_PRIORITY_BITS      0x07U

#define GCR_SET_CALL_PRIORITY(x,y)                           \
    (((x).data_5field[3] &= ~GCR_CALL_PRIORITY_BITS),        \
      (x).data_5field[3] |= ((y) & GCR_CALL_PRIORITY_BITS))

#define GCR_GET_CALL_PRIORITY(x)     \
    ((x).data_5field[3] & GCR_CALL_PRIORITY_BITS)

/* 'Ciphering information' */
#define GCR_NO_CIPHERING           0x00U
#define GCR_CIPHERING_KEY_1        0x01U
#define GCR_CIPHERING_KEY_2        0x02U
#define GCR_CIPHERING_KEY_3        0x03U
#define GCR_CIPHERING_KEY_4        0x04U
#define GCR_CIPHERING_KEY_5        0x05U
#define GCR_CIPHERING_KEY_6        0x06U
#define GCR_CIPHERING_KEY_7        0x07U
#define GCR_CIPHERING_KEY_8        0x08U
#define GCR_CIPHERING_KEY_9        0x09U
#define GCR_CIPHERING_KEY_A        0x0AU
#define GCR_CIPHERING_KEY_B        0x0BU
#define GCR_CIPHERING_KEY_C        0x0CU
#define GCR_CIPHERING_KEY_D        0x0DU
#define GCR_CIPHERING_KEY_E        0x0EU
#define GCR_CIPHERING_KEY_F        0x0FU
#define GCR_CIPHERING_BITS         0xF0U

#define GCR_SET_CIPHERING_KEY(x,y)                              \
    (((x).data_5field[4] &= ~GCR_CIPHERING_BITS),               \
      (x).data_5field[4] |= (((y) << 4) & GCR_CIPHERING_BITS))

#define GCR_GET_CIPHERING_KEY(x)                    \
        (((x).data_5field[4] & GCR_CIPHERING_BITS) >> 4)

/***********************************************************************
 * eMLPP Priority
 * Ref: 3.2.2.56
 *      GSM 04.08, Section 10.5.1.9 - Descriptive group or broadcast call 
 *    reference.
 *
 * Note: 'call priority' has the same values as above.
 * 
 */    
typedef struct
{
    ITS_OCTET    call_pri;
}
BSSAP_eMLPP_Priority;

#define EP_SET_CALL_PRIORITY(x,y)                       \
    (((x).call_pri &= ~GCR_CALL_PRIORITY_BITS),         \
      (x).call_pri |= ((y) & GCR_CALL_PRIORITY_BITS))

#define EP_GET_CALL_PRIORITY(x)                    \
    ((x).call_pri & GCR_CALL_PRIORITY_BITS)

/***********************************************************************
 * Configuration Evolution Indication
 * Ref: 3.2.2.57
 */
typedef struct
{
    ITS_OCTET    smi;
}
BSSAP_ConfigEvolutionInd;

#define CE_NO_MODIFICATION_ALLOWED          0x00U
#define CE_MODIFICATION_ALLOWED_TCH_F_1     0x01U
#define CE_MODIFICATION_ALLOWED_TCH_F_2     0x02U
#define CE_MODIFICATION_ALLOWED_TCH_F_3     0x03U
#define CE_MODIFICATION_ALLOWED_TCH_F_4     0x04U

#define CE_MODIFICATION_IND_BITS            0x0FU

#define CE_SET_MODIFICATION_IND(x,y)                \
    (((x).smi &= ~CE_MODIFICATION_IND_BITS),        \
      (x).smi |= ((y) & CE_MODIFICATION_IND_BITS))

#define CE_GET_MODIFICATION_IND(x)                \
    ((x).smi & CE_MODIFICATION_IND_BITS)

/***********************************************************************
 * Old BSS to New BSS Information
 * Ref: 3.2.2.58
 */

/***********************************************************************
 * LCS QoS
 * Ref: 3.2.2.60
 */
typedef struct
{
    ITS_OCTET   vert;
    ITS_OCTET   ha_horacc;
    ITS_OCTET   va_vertacc;
    ITS_OCTET   rt;
}
BSSAP_LCSQoS;

// Response Time Category 
#define LQ_RT_RSP_TIME_NOT_SPEC              0x00U
#define LQ_RT_LOW_DELAY                      0x01U
#define LQ_RT_DELAY_TOLERANT                 0x02U

// x - object;
// y - data;
#define LQ_SET_VERT_COORD_IND(x,y)           \
    (((x).vert &= ~0x01U),     \
      (x).vert |= ((y) & 0x01U))

#define LQ_GET_VERT_COORD_IND(x)                \
    ((x).vert & 0x01U)

#define LQ_SET_HOR_ACC_IND(x,y)           \
    (((x).ha_horacc &= ~0x80U),     \
      (x).ha_horacc |= (((y) << 7) & 0x80U))

#define LQ_GET_HOR_ACC_IND(x)                \
    (((x).ha_horacc & 0x7FU) >> 7)

#define LQ_SET_HOR_ACC(x,y)           \
    (((x).ha_horacc &= ~0x7FU),     \
      (x).ha_horacc |= ((y) & 0x7FU))

#define LQ_GET_HOR_ACC(x)                \
    ((x).ha_horacc & 0x7FU)

#define LQ_SET_VA_ACC_IND(x,y)           \
    (((x).va_vertacc &= ~0x80U),     \
      (x).va_vertacc |= (((y) << 7) & 0x80U))

#define LQ_GET_VA_ACC_IND(x)                \
    (((x).va_vertacc & 0x80U) >> 7)

#define LQ_SET_VA_ACC(x,y)           \
    (((x).va_vertacc &= ~0x7FU),     \
      (x).va_vertacc |= ((y) & 0x7FU))

#define LQ_GET_VA_ACC(x)                \
    ((x).va_vertacc & 0x7FU

#define LQ_SET_RT(x,y)           \
    (((x).rt &= ~0xC0U),     \
      (x).rt |= (((y) << 6) & 0xC0U))

#define LQ_GET_RT(x)                \
    (((x).rt & 0xC0U) >> 6)

/***********************************************************************
 * LSA Access Control Suppression
 * Ref: 3.2.2.61
 */
typedef struct
{
    ITS_OCTET   emergency;
}
BSSAP_LSAAccessControlSuppr;

// x - object;
// y - data;
#define LACS_SET_EMERGENCY(x,y)           \
    (((x).emergency &= ~0x01U),     \
      (x).emergency |= ((y) & 0x01U))

#define LACS_GET_EMERGENCY(x)                \
    ((x).emergency & 0x01U)

/***********************************************************************
 * LCS Priority -- encode format is ASN.1 format, has 1 octet
 * Ref: 3.2.2.62, 3GPP TS 09.02 
 */
typedef struct
{
    ITS_OCTET   priority[1];
}
BSSAP_LCSPriority;

/***********************************************************************
 * Location Type
 * Ref: 3.2.2.63
 */
typedef struct
{
    ITS_OCTET   loc_info;
    ITS_OCTET   pos_mthd;
}
BSSAP_LocationType;

// Location Information
#define LT_LI_CRRT_GEO_LOC                   0x00U
#define LT_LI_LOC_IFNO_FOR_MS                0x01U
#define LT_LI_DECIPHER_KEYS_FOR_MS           0x02U

// x - object;
// y - data;
#define LT_SET_LOC_TYPE(x,y)           \
    (((x).loc_info &= ~0xFFU),     \
      (x).loc_info |= ((y) & 0xFFU))

#define LT_GET_LOC_TYPE(x)                \
    ((x).loc_info & 0xFFU)

// Positioning Method
#define LT_PM_MOBILE_ASSISTED_E_OTD          0x01U
#define LT_PM_MOBILE_BASED_E_OTD             0x02U
#define LT_PM_ASSISTED_GPS                   0x03U

#define LT_SET_POS_METHOD(x,y)          \
    (((x).pos_mthd &= ~0xFFU),     \
      (x).pos_mthd |= ((y) & 0xFFU))

#define LT_GET_POS_METHOD(x)            \
    ((x).pos_mthd & 0xFFU)

/***********************************************************************
 * Location Estimate
 * Ref: 3.2.2.64
 */
typedef struct
{
    ITS_OCTET   loc_est[1];
}
BSSAP_LocationEstimate;

/***********************************************************************
 * Positioning Data
 * Ref: 3.2.2.65
 */

typedef struct
{
    ITS_OCTET   pos_data_discr;
    ITS_OCTET   pos_mthd[1];
}
BSSAP_PositioningData;

// Positioning Data Discriminator
#define PD_POS_DATA_DISCR                   0x00U
// All other values are reserved

// x - object;
// y - data;
// z - index
#define PD_SET_POS_DATA_DISCR(x,y)           \
    (((x).pos_data_discr &= ~0x0FU),     \
      (x).pos_data_discr |= ((y) & 0x0FU))

#define PD_GET_POS_DATA_DISCR(x)                \
    ((x).pos_data_discr & 0x0FU)

// Positioning Method
#define PD_PM_TIME_ADVANCE                   0x00U
#define PD_PM_TOA                            0x01U
#define PD_PM_AOA                            0x02U
#define PD_PM_MOBILE_ASSISTED_E_OTD          0x03U
#define PD_PM_MOBILE_BASED_E_OTD             0x04U
#define PD_PM_MOBILE_ASSISTED_GPS            0x05U
#define PD_PM_MOBILE_BASED_GPS               0x06U
#define PD_PM_CONVENT IONAL                  0x07U

#define PD_SET_POS_METHOD(x,y,z)          \
    (((x).pos_mthd[z] &= ~0xF8U),     \
      (x).pos_mthd[z] |= (((y) << 3) & 0xF8U))

#define PD_GET_POS_METHOD(x,z)            \
    (((x).pos_mthd[z] & 0xF8U) >> 3)

// Usage
#define PD_USAGE_UNSUCCESS_DUE_TO_FAIL                          0x00U
#define PD_USAGE_SUCCESS_RESULT_NOT_USED_TO_LOC                 0x01U
#define PD_USAGE_SUCCESS_RESULT_USED_TO_VERIFY_NOT_TO_LOC       0x02U
#define PD_USAGE_SUCCESS_RESULT_USED_TO_LOC                     0x03U
#define PD_USAGE_SUPPORT_METHOD_CASE                            0x04U

#define PD_SET_USAGE(x,y,z)          \
    (((x).pos_mthd[z] &= ~0x07U),     \
      (x).pos_mthd[z] |= ((y) & 0x07U))

#define PD_GET_USAGE(x,z)            \
    ((x).pos_mthd[z] & 0x07U)

/***********************************************************************
 * LCS Cause
 * Ref: 3.2.2.66
 */

typedef struct
{
    ITS_OCTET   cause_value;
    ITS_OCTET   diag_value;
}
BSSAP_LCSCause;

// Cause value
#define LC_CV_UNSPECIFIED                        0x00U
#define LC_CV_SYS_FAILURE                        0x01U
#define LC_CV_PROT_ERROR                         0x02U
#define LC_CV__DATA_MISS_IN_POS_REQ              0x03U
#define LC_CV_UNEXP_DATA_IN_POS_REQ              0x04U
#define LC_CV_POS_MTHD_FAILURE                   0x05U
#define LC_CV_TARGET_MS_UNRCH                    0x06U
#define LC_CV_LOC_REQ_ABORT                      0x07U
#define LC_CV_FACIL_NOT_SUPPT                    0x08U
#define LC_CV_INTER_BSC_HANDOVER_ONGING          0x09U
#define LC_CV_INTER_BSC_HANDOVER_CMPLT           0x10U
#define LC_CV_CONGESTION                         0x11U

// x - object;
// y - data;
#define LC_SET_CAUSE_VALUE(x,y)           \
    (((x).cause_value &= ~0xFFU),     \
      (x).cause_value |= ((y) & 0xFFU))

#define LC_GET_CAUSE_VALUE(x)                \
    ((x).cause_value & 0xFFU)

// Diagnostics Values are defined in 3GPP TS 09.02
#define LC_SET_DIAGNOSTICS_VALUE(x,y)          \
    (((x).diag_value &= ~0xFFU),            \
      (x).diag_value |= ((y) & 0xFFU))

#define LC_GET_DIAGNOSTICS_VALUE(x)            \
    ((x).diag_value & 0xFFU)

/***********************************************************************
 * LCS Client Type
 * Ref: 3.2.2.67
 */
typedef struct
{
    ITS_OCTET   client_cat_subtype;
}
BSSAP_LCSClientType;

#define LCT_CLIENT_SUBTYPE_BITS                   0x0FU
#define LCT_CLIENT_CATEGORY_BITS                  0xF0U
// x - object;
// y - data;
#define LCT_SET_CLIENT_SUBTYPE(x,y)           \
    (((x).client_cat_subtype &= ~LCT_CLIENT_SUBTYPE_BITS),     \
      (x).client_cat_subtype |= ((y) & LCT_CLIENT_SUBTYPE_BITS))

#define LCT_GET_CLIENT_SUBTYPE(x)                \
    ((x).client_cat_subtype & LCT_CLIENT_SUBTYPE_BITS)

#define LCT_SET_CLIENT_CATEGORY(x,y)          \
    (((x).client_cat_subtype &= ~LCT_CLIENT_CATEGORY_BITS),     \
      (x).client_cat_subtype |= (((y) << 4) & LCT_CLIENT_CATEGORY_BITS))

#define LCT_GET_CLIENT_CATEGORY(x)            \
    (((x).client_cat_subtype & LCT_CLIENT_CATEGORY_BITS) >> 4)

/***********************************************************************
 * APDU
 * Ref: 3.2.2.68
 */

typedef struct
{
    ITS_OCTET   prot_id;
    ITS_OCTET   embed_msg[1];
}
BSSAP_APDU;

// Protocol ID
#define APDU_PROT_BSSLAP                          0x01U
#define APDU_PROT_LLP                             0x02U
#define APDU_PROT_SMLCCP                          0x03U
#define APDU_PROT_ID_BITS                         0x7FU

// x - object;
// y - data;
#define APDU_SET_PROT_ID(x,y)           \
    (((x).prot_id &= ~APDU_PROT_ID_BITS),     \
      (x).prot_id |= ((y) & APDU_PROT_ID_BITS))

#define APDU_GET_PROT_ID(x)                \
    ((x).prot_id & APDU_PROT_ID_BITS)

/***********************************************************************
 * Network Element Identity
 * Ref: 3.2.2.69
 */
typedef struct
{
    ITS_OCTET    MCC[2];    // Mobile Country Code
    ITS_OCTET    MNC;       // Mobile Network Code 
    ITS_OCTET    LAC[2];    // Location Area Code
}
BSSAP_LAI;

typedef struct
{
    ITS_OCTET    LAC[2];    // Location Area Code 
}
BSSAP_LAC;

typedef union 
{
    BSSAP_CellGlobalId  cgi;
    BSSAP_Lac_Ci        lac_ci;
    BSSAP_LAI           lai;
    BSSAP_LAC           lac;
}
BSSAP_NetID;
 
typedef struct
{
    ITS_OCTET         id_discriminator;
    BSSAP_NetID       net_elmnt_id;    
}
BSSAP_NetworkElementIdentity;

#define NEI_ID_CGI      0x00U  // MCC + MNC + LAC + CI
#define NEI_ID_LAC_CI   0x01U  // LAC + CI
#define NEI_ID_LAI      0x04U  // MCC + MNC + LAC
#define NEI_ID_LAC      0x05U  // LAC

#define NEI_SET_ID_DISCRIMINATOR(x,y)    \
    ((x).id_discriminator = (y))

#define NEI_GET_ID_DISCRIMINATOR(x)        \
    ((x).id_discriminator)

/* CGI -- MCC + MNC + LAC + CI */
// MCC
#define NEI_CGI_SET_MCC(x,y)                                \
    ((x).cgi.MCC[0] = (((y) >> 8) & 0xFFU),                 \
     (x).cgi.MCC[1] = ((y) | 0xF0U))

#define NEI_CGI_GET_MCC(x)                                  \
    ((x).cgi.MCC[0] << 8 | ((x).cgi.MCC[1] & 0x0FU))

/* MNC Needs to be BCD encoded */
// Here, y - int
#define NEI_CGI_SET_MNC(x,y)                            \
    { if( y > 9) {                      \
    (x).cgi.MNC = (((y)/10) << 8);         \
    (x).cgi.MNC |= ((y)%10);             \
      }    else  (x).cgi.MNC = (y);                \
    } 

#define NEI_CGI_GET_MNC(x)                             \
    ( ((((x).cgi.MNC & 0xF0U) >> 4) * 10)         \
    + ((x).cgi.MNC & 0x0FU) )

// LAC
#define NEI_CGI_SET_LAC(x,y)                                \
    ((x).cgi.LAC[0] = (((y) >> 8) & 0xFFU),                 \
     (x).cgi.LAC[1] = ((y) & 0xFFU))

#define NEI_CGI_GET_LAC(x)                                  \
    (((x).cgi.LAC[0] << 8 ) | (x).cgi.LAC[1])

// CI
#define NEI_CGI_SET_CI(x,y)                                 \
    ((x).cgi.CI[0] = (((y) >> 8) & 0xFFU),            \
     (x).cgi.CI[1] = ((y) & 0xFFU))

#define NEI_CGI_GET_CI(x)                                   \
    (((x).cgi.CI[0] << 8 ) | (x).cgi.CI[1])

/* LAC & CI */
//LAC
#define NEI_LACCI_SET_LAC(x,y)                              \
    ((x).lac_ci.LAC[0] = (((y) >> 8) & 0xFFU),              \
     (x).lac_ci.LAC[1] = ((y) & 0xFFU))

#define NEI_LACCI_GET_LAC(x)                                \
    (((x).lac_ci.LAC[0] << 8 ) | (x).lac_ci.LAC[1])

// CI
#define NEI_LACCI_SET_CI(x,y)                               \
    ((x).lac_ci.CI[0] = (((y) >> 8) & 0xFFU),         \
     (x).lac_ci.CI[1] = ((y) & 0xFFU))

#define NEI_LACCI_GET_CI(x)                                 \
    (((x).lac_ci.CI[0] << 8 ) | (x).lac_ci.CI[1])

/* LAI -- MCC + MNC + LAC */
//MCC
#define NEI_LAI_SET_MCC(x,y)                                \
    ((x).lai.MCC[0] = (((y) >> 8) & 0xFFU),           \
        (x).lai.MCC[1] = ((y) | 0xF0U))

#define NEI_LAI_GET_MCC(x)                                  \
    ((x).lai.MCC[0] << 8 | ((x).lai.MCC[1] & 0x0FU))

// MNC Needs to be BCD encoded 
// Here, y - int 
#define NEI_LAI_SET_MNC(x,y)                            \
    { if( y > 9) {                      \
    (x).lai.MNC = (((y)/10) << 8);         \
    (x).lai.MNC |= ((y)%10);             \
      }    else  (x).lai.MNC = (y);                \
    } 
   
#define NEI_LAI_GET_MNC(x)                              \
    (((((x).lai.MNC & 0xF0U) >> 4) * 10)         \
    + ((x).lai.MNC & 0x0FU))

// LAC
#define NEI_LAI_SET_LAC(x,y)                            \
    ((x).lai.LAC[0] = (((y) >> 8) & 0xFFU),           \
     (x).lai.LAC[1] = ((y) & 0xFFU))

#define NEI_LAI_GET_LAC(x)                   \
    (((x).lai.LAC[0] << 8 ) | (x).lai.LAC[1])

/* LAC */
#define NEI_LAC_SET_LAC(x,y)                               \
    ((x).lac.LAC[0] = (((y) >> 8) & 0xFFU),              \
     (x).lac.LAC[1] = ((y) & 0xFFU))

#define NEI_LAC_GET_LAC(x)                                 \
    (((x).lac.LAC[0] << 8) | (x).lac.LAC[1])


/***********************************************************************
 * GPS Assistance Data
 * Ref: 3.2.2.70
 */
typedef struct
{
    ITS_OCTET    satid;
    ITS_OCTET    iode;
}
BSSAP_SATID_IODE;

typedef struct
{
    ITS_OCTET           data_field3;
    ITS_OCTET           data_field4;
    ITS_OCTET           data_field5[2];
    ITS_OCTET           data_field7;
    ITS_OCTET           data_field8;
    BSSAP_SATID_IODE    satid_iode[1];
}
BSSAP_GPSAssistanceData;

// x - object;
// y - data;

#define GAD_SET_ALMANAC(x,y)                \
    (((x).data_field3 &= ~0x01),        \
      (x).data_field3 |= ((y) & 0x01))

#define GAD_GET_ALMANAC(x)                \
    ((x).data_field3 & 0x01)

#define GAD_SET_UTC_MODEL(x,y)                \
    (((x).data_field3 &= ~0x02),        \
      (x).data_field3 |= (((y) << 1) & 0x02))

#define GAD_GET_UTC_MODEL(x)                \
    (((x).data_field3 & 0x02) >> 1)

#define GAD_SET_LONOSPHERIC_MODEL(x,y)                \
    (((x).data_field3 &= ~0x04),        \
      (x).data_field3 |= (((y) << 2) & 0x04))

#define GAD_GET_LONOSPHERIC_MODEL(x)                \
    (((x).data_field3 & 0x04) >> 2)

#define GAD_SET_NAVIGATION_MODEL(x,y)                \
    (((x).data_field3 &= ~0x08),        \
      (x).data_field3 |= (((y) << 3) & 0x08))

#define GAD_GET_NAVIGATION_MODEL(x)                \
    (((x).data_field3 & 0x08) >> 3)

#define GAD_SET_DGPS_CORRECTIONS(x,y)                \
    (((x).data_field3 &= ~0x10),        \
      (x).data_field3 |= (((y) << 4) & 0x10))

#define GAD_GET_DGPS_CORRECTIONS(x)                \
    (((x).data_field3 & 0x10) >> 4)

#define GAD_SET_REF_LOC(x,y)                \
    (((x).data_field3 &= ~0x20),        \
      (x).data_field3 |= (((y) << 5) & 0x20))

#define GAD_GET_REF_LOC(x)                \
    (((x).data_field3 & 0x20) >> 5)

#define GAD_SET_REF_TIME(x,y)                \
    (((x).data_field3 &= ~0x20),        \
      (x).data_field3 |= (((y) << 6) & 0x40))

#define GAD_GET_REF_TIME(x)                \
    (((x).data_field3 & 0x40) >> 6)

#define GAD_SET_ACQ_ASSIST(x,y)                \
    (((x).data_field3 &= ~0x80),        \
      (x).data_field3 |= (((y) << 7) & 0x80))

#define GAD_GET_ACQ_ASSIST(x)                \
    (((x).data_field3 & 0x80) >> 7)

#define GAD_SET_REAL_TIME_INTG(x,y)              \
    (((x).data_field4 &= ~0x01),                 \
      (x).data_field4 |= ((y) & 0x01))

#define GAD_GET_REAL_TIME_INTG(x)                \
    ((x).data_field4 & 0x01)

#define GAD_SET_GPS_WEEK(x,y)                    \
    (((x).data_field5[0] &= ~0xC0),              \
      (x).data_field5[0] |= (((y) >> 2) & 0xC0), \
     ((x).data_field5[1] &= ~0xFF),              \
      (x).data_field5[1] |= ((y) & 0xFF))

#define GAD_GET_GPS_WEEK(x)                      \
    ((((x).data_field5[0] & 0xC0) << 2) | ((x).data_field5[1] & 0xFF) )
      
#define GAD_SET_GPS_TOE(x,y)                     \
    (((x).data_field7 &= ~0xFF),                 \
      (x).data_field7 |= ((y) & 0xFF))

#define GAD_GET_GPS_TOE(x)                       \
    ((x).data_field7 & 0xFF)

#define GAD_SET_NSAT(x,y)                        \
    (((x).data_field8 &= ~0xF0),                 \
      (x).data_field8 |= (((y) << 4) & 0xF0))

#define GAD_GET_NSAT(x)                          \
    (((x).data_field8 & 0xF0) >> 4)

#define GAD_SET_T_TOE_LIMIT(x,y)                 \
    (((x).data_field8 &= ~0x0F),                 \
      (x).data_field8 |= ((y) & 0x0F))

#define GAD_GET_T_TOE_LIMIT(x)                   \
    ((x).data_field8 & 0x0F)

// SatID and IODE
#define GAD_SET_SAT_ID(x,y)                      \
    (((x).satid &= ~0x3F),                       \
      (x).satid |= ((y) & 0x3F))

#define GAD_GET_SAT_ID(x)                        \
    ((x).satid & 0x3F)

#define GAD_SET_IODE(x,y)                        \
    (((x).iode &= ~0xFF),                        \
      (x).iode |= ((y) & 0xFF))

#define GAD_GET_IODE(x)                          \
    ((x).iode & 0xFF)

/***********************************************************************
 * Deciphering Keys
 * Ref: 3.2.2.71
 */
typedef struct
{
    ITS_OCTET    keyFlag;
    ITS_OCTET    crrtKeyValue[7];
    ITS_OCTET    nextKeyValue[7];
}
BSSAP_DecipheringKeys;

#define DK_KEY_FLAG_BITS                     0x01U

// x - object;
// y - data;

// Set and Get Key Flag
#define DK_SET_KEY_FLAG(x,y)                    \
    (((x).keyFlag &= ~DK_KEY_FLAG_BITS),        \
      (x).keyFlag |= ((y) & DK_KEY_FLAG_BITS))

#define DK_GET_KEY_FLAG(x)                      \
    ((x).keyFlag & DK_KEY_FLAG_BITS)

/***********************************************************************
 * Return Error Request
 * Ref: 3.2.2.72
 */
typedef struct
{
    ITS_OCTET    errorType;
}
BSSAP_ReturnErrorRequest;

#define RER_UNSEG_APDU_OR_FIRST_SEG_APDU      0x00U
// All others are reserved

#define RER_ERROR_TYPE_BITS                   0xFFU
// x - object;
// y - data;
#define RER_SET_ERROR_TYPE(x,y)                      \
    (((x).errorType &= ~RER_ERROR_TYPE_BITS),        \
      (x).errorType |= ((y) & RER_ERROR_TYPE_BITS))

#define RER_GET_ERROR_TYPE(x)                        \
    ((x).errorType & RER_ERROR_TYPE_BITS)

/***********************************************************************
 * Return Error Cause
 * Ref: 3.2.2.73
 */
typedef struct
{
    ITS_OCTET    causeValue;
}
BSSAP_ReturnErrorCause;

#define REC_UNSPECIFIED                       0x00U
#define REC_SYSTEM_FAILURE                    0x01U
#define REC_PROTOCOL_ERROR                    0x02U
#define REC_DESTINATION_UNKNOWN               0x03U
#define REC_DESTINATION_UNREACHABLE           0x04U
#define REC_CONGESTION                        0x05U

#define REC_CAUSE_VALUE_BITS                  0xFFU
// x - object;
// y - data;
#define REC_SET_CAUSE_VALUE(x,y)                       \
    (((x).causeValue &= ~REC_CAUSE_VALUE_BITS),        \
      (x).causeValue |= ((y) & REC_CAUSE_VALUE_BITS))

#define REC_GET_CAUSE_VALUE(x)                         \
    ((x).causeValue & REC_CAUSE_VALUE_BITS)

/***********************************************************************
 * Segmentation
 * Ref: 3.2.2.74
 */
typedef struct
{
    ITS_OCTET  seg_msg_info[3];
}
BSSAP_Segmentation;

// x - object;
// y - data;

#define SG_SEGMENT_NUM_BITS                  0x0FU

#define SG_SET_SEGMENT_NUMBER(x,y)                         \
    (((x).seg_msg_info[0] &= ~SG_SEGMENT_NUM_BITS),        \
      (x).seg_msg_info[0] |= ((y) & SG_SEGMENT_NUM_BITS))

#define SG_GET_SEGMENT_NUMBER(x)                           \
    ((x).seg_msg_info[0] & SG_SEGMENT_NUM_BITS)

#define SG_SET_SEGMENT_BIT(x,y)                            \
    (((x).seg_msg_info[0] &= ~0x10U),                      \
      (x).seg_msg_info[0] |= (((y) << 4) & 0x10U))

#define SG_GET_SEGMENT_BIT(x)                              \
    (((x).seg_msg_info[0] & 0x10U) >> 4)

#define SG_SEGMENT_MSG_INFO_BITS             0xFFU

#define SG_SET_MESSAGE_ID(x,y)                             \
    (((x).seg_msg_info[1] = ((y) >> 8) & SG_SEGMENT_MSG_INFO_BITS),   \
      (x).seg_msg_info[2] &= ~SG_SEGMENT_MSG_INFO_BITS,               \
      (x).seg_msg_info[2] |= ((y) & SG_SEGMENT_MSG_INFO_BITS))

#define SG_GET_MESSAGE_ID(x)                               \
    (((x).seg_msg_info[1] << 8) |                          \
      (x).seg_msg_info[2] & SG_SEGMENT_MSG_INFO_BITS)

/***********************************************************************
 * Service Handover
 * Ref: 3.2.2.75
 */
typedef struct
{
    ITS_OCTET    shi;
}
BSSAP_ServiceHandover;

#define SH_HANDPVER_TO_EITHER_SHOULD_PERFORM          0x00U
#define SH_HANDPVER_TO_NEITHER_SHOULD_NOT_PERFORM     0x01U
#define SH_HANDPVER_TO_NEITHER_SHALL_NOT_PERFORM      0x02U
#define SH_SERV_HANDOVER_INFO_BITS                    0x07U

#define SH_SET_SERV_HANDOVER_INFO(x,y)                \
    (((x).shi &= ~SH_SERV_HANDOVER_INFO_BITS),        \
      (x).shi |= ((y) & SH_SERV_HANDOVER_INFO_BITS))

#define SH_GET_SERV_HANDOVER_INFO(x)                  \
    ((x).shi & SH_SERV_HANDOVER_INFO_BITS)

/***********************************************************************
 * Soruce RNC to Target RNC Transparent Information (UMTS)
 * Ref: 3.2.2.76
 */
typedef struct
{
    ITS_OCTET    rnc_umts_info[1];
}
BSSAP_SoruceRNCtoTargetRNCInfoUMTS;

/***********************************************************************
 * Soruce RNC to Target RNC Transparent Information (CDMA)
 * Ref: 3.2.2.77
 */
typedef struct
{
    ITS_OCTET    rnc_cdma_info[1];
}
BSSAP_SoruceRNCtoTargetRNCInfoCDMA;

/***********************************************************************
 * Inter System Information
 * Ref: 3.2.2.81
 */
typedef struct
{
    ITS_OCTET    transp_cont[1];
}
BSSAP_InterSysInfo;

/***********************************************************************
 * Signalling Field Element- section 3.2.3
 */

/***********************************************************************
 * Extra Information
 * Ref: 3.2.3.1
 */
typedef struct
{
    ITS_OCTET    data_field;
}
BSSAP_ExtraInformation;

#define EI_SET_PRE_EMPTION_RECOM(x,y)              \
    (((x).data_field &= ~0x01),                    \
      (x).data_field |= ((y) & 0x01))

#define EI_GET_PRE_EMPTION_RECOM(x)                \
    ((x).data_field & 0x01)

#define EI_SET_LOC_SERV_INFO(x,y)                  \
    (((x).data_field &= ~0x02),                    \
      (x).data_field |= (((y) << 1) & 0x02))

#define EI_GET_LOC_SERV_INFO(x)                    \
    (((x).data_field & 0x02) >> 1)

/***********************************************************************
 * Current Channel Type 2
 * Ref: 3.2.3.2
 */
typedef struct
{
    ITS_OCTET    chan_mode;
    ITS_OCTET    chan_field;
}
BSSAP_CurrentChannelType2;

// Channel Mode
#define CCT2_CM_SIGNAL_ONLY                0x00U
#define CCT2_CM_SPEECH                     0x01U
#define CCT2_CM_DATA_12                    0x03U
#define CCT2_CM_DATA_6                     0x04U
#define CCT2_CM_DATA_3_6                   0x05U
#define CCT2_CM_DATA_14_5                  0x06U

#define CCT2_SET_CHAN_MODE(x,y)                \
    (((x).chan_mode &= ~0x0F),                 \
      (x).chan_mode |= ((y) & 0x0F))

#define CCT2_GET_CHAN_MODE(x)                  \
    ((x).chan_mode & 0x0F)

// Channel Field
#define CCT2_CF_SDCCH                      0x01U
#define CCT2_CF_1_FULL_RATE                0x08U
#define CCT2_CF_1_HALF_RATE                0x09U
#define CCT2_CF_2_FULL_RATE                0x0AU
#define CCT2_CF_3_FULL_RATE                0x0BU
#define CCT2_CF_4_FULL_RATE                0x0CU
#define CCT2_CF_5_FULL_RATE                0x0DU
#define CCT2_CF_6_FULL_RATE                0x0EU
#define CCT2_CF_7_FULL_RATE                0x0FU
#define CCT2_CF_8_FULL_RATE                0x04U

#define CCT2_SET_CHAN_FIELD(x,y)               \
    (((x).chan_field &= ~0x0F),                \
        (x).chan_field |= ((y) & 0x0F))

#define CCT2_GET_CHAN_FIELD(x)                 \
    ((x).chan_field & 0x0F)

/***********************************************************************
 * Target Cell Radio Information
 * Ref: 3.2.3.3
 */
typedef struct
{
    ITS_OCTET    data_field;
}
BSSAP_TargetCellRadioInformation;

#define TCRI_SET_RXLEV_NCELL(x,y)              \
    (((x).data_field &= ~0x1F),                \
      (x).data_field |= ((y) & 0x1F))

#define TCRI_GET_RXLEV_NCELL(x)                \
    ((x).data_field & 0x1F)

/***********************************************************************
 * GPRS Suspend Information
 * Ref: 3.2.3.4
 */
typedef struct
{
    ITS_OCTET    tlli_rai_srn[1];
}
BSSAP_GPRSSuspendInformation;

/***********************************************************************
 * Multirate Configuration Information
 * Ref: 3.2.3.5
 */
typedef struct
{
    ITS_OCTET    data_field1;
    ITS_OCTET    data_field2;
    ITS_OCTET    multi_speech[4];
}
BSSAP_MultirateConfigInformation;

// Codec Mode
#define MCI_CODEC_MODE_1              0x00U
#define MCI_CODEC_MODE_2              0x01U
#define MCI_CODEC_MODE_3              0x02U
#define MCI_CODEC_MODE_4              0x03U

// Multirate Speech Version
#define MCI_ADAPTIVE_MR_SPCH_VER_1    0x01U

#define MCI_SET_START_MODE(x,y)           \
    (((x).data_field1 &= ~0x01),          \
      (x).data_field1 |= ((y) & 0x03))

#define MCI_GET_START_MODE(x)             \
    ((x).data_field1 & 0x03)

#define MCI_SET_ICMI(x,y)                 \
    (((x).data_field1 &= ~0x04),          \
      (x).data_field1 |= (((y) << 2) & 0x04))

#define MCI_GET_ICMI(x)                   \
    (((x).data_field1 & 0x04) >> 2)

#define MCI_SET_MR_VERSION(x,y)           \
    (((x).data_field1 &= ~0xE0),          \
      (x).data_field1 |= (((y) << 5) & 0xE0))

#define MCI_GET_MR_VERSION(x)             \
    (((x).data_field1 & 0xE0) >> 5)

// ARM Codec Modes
#define MCI_SET_ARM_CODEC_MODE_1(x,y)     \
    (((x).data_field2 &= ~0x01),          \
      (x).data_field2 |= ((y) & 0x01))

#define MCI_GET_ARM_CODEC_MODE_1(x)       \
    ((x).data_field2 & 0x01)

#define MCI_SET_ARM_CODEC_MODE_2(x,y)     \
    (((x).data_field2 &= ~0x02),          \
      (x).data_field2 |= (((y) << 1) & 0x02))

#define MCI_GET_ARM_CODEC_MODE_2(x)       \
    (((x).data_field2 & 0x02) >> 1)

#define MCI_SET_ARM_CODEC_MODE_3(x,y)     \
    (((x).data_field2 &= ~0x04),          \
      (x).data_field2 |= (((y) << 2) & 0x04))

#define MCI_GET_ARM_CODEC_MODE_3(x)       \
    (((x).data_field2 & 0x04) >> 2)

#define MCI_SET_ARM_CODEC_MODE_4(x,y)     \
    (((x).data_field2 &= ~0x08),          \
      (x).data_field2 |= (((y) << 3) & 0x08))

#define MCI_GET_ARM_CODEC_MODE_4(x)       \
    (((x).data_field2 & 0x08) >> 3)

#define MCI_SET_ARM_CODEC_MODE_5(x,y)     \
    (((x).data_field2 &= ~0x10),          \
      (x).data_field2 |= (((y) << 4) & 0x10))

#define MCI_GET_ARM_CODEC_MODE_5(x)       \
    (((x).data_field2 & 0x10) >> 4)

#define MCI_SET_ARM_CODEC_MODE_6(x,y)     \
    (((x).data_field2 &= ~0x20),          \
      (x).data_field2 |= (((y) << 5) & 0x20))

#define MCI_GET_ARM_CODEC_MODE_6(x)       \
    (((x).data_field2 & 0x20) >> 5)

#define MCI_SET_ARM_CODEC_MODE_7(x,y)     \
    (((x).data_field2 &= ~0x40),          \
      (x).data_field2 |= (((y) << 6) & 0x40))

#define MCI_GET_ARM_CODEC_MODE_7(x)       \
    (((x).data_field2 & 0x40) >> 6)

#define MCI_SET_ARM_CODEC_MODE_8(x,y)     \
    (((x).data_field2 &= ~0x80),          \
      (x).data_field2 |= (((y) << 7) & 0x80))

#define MCI_GET_ARM_CODEC_MODE_8(x)       \
    (((x).data_field2 & 0x80) >> 7)

/***********************************************************************
 * Dual Transfer Mode Information
 * Ref: 3.2.3.6
 */
typedef struct
{
    ITS_OCTET    data_field;
}
BSSAP_DualTransferModeInformation;

#define DTMI_SET_DTM_IND(x,y)            \
    (((x).data_field &= ~0x01),          \
      (x).data_field |= ((y) & 0x01))

#define DTMI_GET_DTM_IND(x)              \
    ((x).data_field & 0x01)

#define DTMI_SET_STO_IND(x,y)            \
    (((x).data_field &= ~0x02),          \
      (x).data_field |= (((y) << 1) & 0x02))

#define DTMI_GET_STO_IND(x)              \
    (((x).data_field & 0x02) >> 1)

#define DTMI_SET_EGPRS_IND(x,y)          \
    (((x).data_field &= ~0x04),          \
      (x).data_field |= (((y) << 2) & 0x04))

#define DTMI_GET_EGPRS_IND(x)            \
    (((x).data_field & 0x04) >> 2)

/***********************************************************************
 * Inter RAT Handover Information
 * Ref: 3.2.3.7
 */
typedef struct
{
    ITS_OCTET    irathand_info[1];
}
BSSAP_iRATHandInfo;

/***********************************************************************
 * UE Capability Information
 * Ref: 3.2.3.7
 */
typedef struct
{
    ITS_OCTET    ue_info[1];
}
BSSAP_UECapInformation;

/***********************************************************************
 * cdma2000 Capability Information
 * Ref: 3.2.3.8
 */
typedef struct
{
    ITS_OCTET    cdma_info[1];
}
BSSAP_cdma2000CapInformation;

/***********************************************************************
 * Downlink Cell Load Information
 * Ref: 3.2.3.9
 */
typedef struct
{
    ITS_OCTET  cellCapClassValue;
    ITS_OCTET  loadValue;
    ITS_OCTET  rtLoadValue;
    ITS_OCTET  nrtLoadInfo;
}
BSSAP_DownlinkCellLoadInfo;

/***********************************************************************
 * Uplink Cell Load Information
 * Ref: 3.2.3.10
 */
typedef struct
{
    ITS_OCTET  cellCapClassValue;
    ITS_OCTET  loadValue;
    ITS_OCTET  rtLoadValue;
    ITS_OCTET  nrtLoadInfo;
}
BSSAP_UplinkCellLoadInfo;

/***********************************************************************
 * UTRAN Pre-configuration indication set
 * Ref: 3.2.3.
 */
typedef struct
{
    ITS_OCTET    utran_set[1];
}
BSSAP_UTRANPreconfigIndSet;

/*___________________CC Related IEs________________*/

/* 10.5.1.11 Priority Level */

typedef struct
{
    ITS_OCTET prior;
}
BSSAP_PriorityLevel_IE;

#define PRIORITY_LEVEL_MASK    0x07
#define PRIORITY_LEVEL_NONE    0x00
#define PRIORITY_LEVEL_4       0x01
#define PRIORITY_LEVEL_3       0x02
#define PRIORITY_LEVEL_2       0x03
#define PRIORITY_LEVEL_1       0x04
#define PRIORITY_LEVEL_0       0x05
#define PRIORITY_LEVEL_A       0x06
#define PRIORITY_LEVEL_B       0x07

/* 10.5.4.15 Facility */

#define MAX_FACILITY_LEN     100

typedef struct 
{
    ITS_OCTET data[MAX_FACILITY_LEN];
}
BSSAP_Facility_IE;

/*
 * User To User Information 10.5.4.25
 */

#define MAX_USER_TO_USER_INFO_LEN 131

typedef struct
{
    ITS_OCTET disc;
    ITS_OCTET info[MAX_USER_TO_USER_INFO_LEN];
}
BSSAP_UserToUserInfo;

#define USER_DEFINED_PROT_DISC 0x00
#define OSI_PROT_DISC          0x01
#define X244_PROT_DISC         0x02
#define IA5_PROT_DISC          0x04
#define V220_PROT_DISC         0x07
#define Q931_PROT_DISC         0x08

/*
 * SS Version 10.5.4.24
 */

#define MAX_SS_VERSION_LEN 10

typedef struct
{
    ITS_OCTET data[MAX_SS_VERSION_LEN];
}
BSSAP_SSVersion_IE;

/*
 * Repeat Indication 10.5.4.22
 */

typedef struct
{
    ITS_OCTET value;
}
BSSAP_RepeatIndication;

#define REPEAT_INDICATOR_MASK        0x0f
#define REPEAT_INDICATOR_CIRCULAR    0x01
#define REPEAT_INDICATOR_SEQUENTIAL  0x03

/*
 * Reverse Call Setup Direction 10.5.4.22a
 */
typedef struct
{
   ITS_OCTET value;
}
BSSAP_ReverseCallSetupDirection_IE;

/*
 * Cause 10.5.4.11
 */

#define MAX_DIAG_INFO_LEN    30

typedef struct
{
    ITS_OCTET codingAndLocation;
    ITS_OCTET recommendation;
    ITS_OCTET cause;
    ITS_OCTET diagInfo[MAX_DIAG_INFO_LEN];
}
BSSAP_CCCause_IE;

#define CODING_STANDARD_MASK                    0x60
#define CODING_STANDARD_Q931                    0x00
#define CODING_STANDARD_RESERVED                0x01
#define CODING_STANDARD_NATIONAL                0x02
#define CODING_STANDARD_GSM_PLMN                0x03

#define LOCATION_MASK                           0x0f
#define LOCTION_USER                            0
#define LOCATION_PRIVATE_NETWORK_LOCAL          1
#define LOCATION_PUBLIC_NETWORK_LOCAL           2
#define LOCATION_TRANSIT_NETWORK                3
#define LOCATION_PUBLIC_NETWORK_REMOTE          4
#define LOCATION_PRIVATE_NETWORK_REMOTE         5
#define LOCATION_INTERNATIONAL_NETWORK          7
#define LOCATION_NETWORK_BEYOND_ITW_POINT       10

#define CAUSE_UNASSIGNED                        0
#define CAUSE_NO_ROUTE_TO_DEST                  3
#define CAUSE_CHANNEL_UNACCEPTABLE              6
#define OPERATOR_DETERMINED_BARRING             8
#define CAUSE_NORMAL_CALL_CLEARING              16
#define CAUSE_USER_BUSY                         17
#define CAUSE_NO_USER_RESPONDING                18
#define CAUSE_ALERTING_NO_ANSWER                19
#define CAUSE_CALL_REJECTED                     21
#define CAUSE_NUMBER_CHANGED                    22
#define CAUSE_PREEMPTION                        25
#define CAUSE_NS_USER_CLEARING                  26
#define CAUSE_DEST_OUT_OF_ORDER                 27
#define CAUSE_INV_NUM_FORMAT                    28
#define CAUSE_FACILITY_REJECTED                 29
#define CAUSE_RES_TO_STAT_ENQUIRY               30
#define CAUSE_NORMAL                            31
#define CAUSE_NO_CIRCUIT_AVAILABLE              34
#define CAUSE_NETWORK_OUT_OF_ORDER              38
#define CAUSE_TEMP_FAILURE                      41
#define CAUSE_EQUIPMENT_CONG                    42
#define CAUSE_ACCESS_INFO_DISCARDED             43
#define CAUSE_REQUESTED_CKT_NA                  44
#define CAUSE_RESOURCE_UNAVAIL                  47
#define CAUSE_QUALITY_OF_SERVICE                49
#define CAUSE_FACILITY_NOT_SUBS                 50
#define CAUSEINCOMING_CALL_BARRED               55
#define CAUSE_BEARER_CAPAB_NOT_AUTH             57
#define CAUSE_BEARER_CAPAB_NOT_AVAIL            58
#define CAUSE_SERVICE_OPTION_NOT_AVAIL          63
#define CAUSE_BEARER_NOT_IMPLEMENTED            65
#define CAUSE_ACM_EQ_OR_GT_ACM_MAX              68
#define CAUSE_FACILITY_NOT_IMPL                 69
#define CAUSE_ONLY_RESTRICTED_DIGITAL_INFO      70
#define CAUSE_SERVICE_NOT_IMPL                  79
#define CAUSE_INV_TRANS_ID                      81
#define CAUSE_USER_NOT_MEM_CVG                  87
#define CAUSE_INCOMPATIBLE_DEST_PARAM           88
#define CAUSE_INV_TRANSIT_NETWORK_SELECTION     91
#define CAUSE_SEMANTIC_INCORRECT_MSG            95
#define CAUSE_INV_MANDATORY_INFO                96
#define CAUSE_MSG_TYP_NON_EXISTENT              97
#define CAUSE_MSG_TYP_NOT_COMPATIBLE            98
#define CAUSE_IE_NON_EXISTENR                   99
#define CAUSE_CONDITIONAL_IE_ERROR              100
#define CAUSE_RECOVER_TMR_EXP                   102
#define CAUSE_PROTOCOL_ERROR                    111
#define CAUSE_INTERWORKING_UNSPECIFIED          127

/*
 * Congestion Level 10.5.4.12
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_CongestionLevel_IE;

#define CONG_LEVEL_MASK                         0x0f
#define CONG_LEVEL_RECEIVER_READY               0x00
#define RECEIVER_NOT_READY                      0x0f

/*
 * Notification Indicator 10.5.4.20
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_NotificationIndicator_IE;

#define NOTIFY_USER_SUSPENDED   0
#define NOTIFY_USER_RESUMED     1
#define NOTIFY_BEARER_CHANGE    2

/*
 * Connected Number 10.5.4.13
 */

#define MAX_CN_DIGITS     11

typedef struct
{
    ITS_OCTET typeAndNumPlan;
    ITS_OCTET presentationScreening;
    ITS_OCTET digits[MAX_CN_DIGITS];
}
BSSAP_ConnectedNumber_IE;

/*
 * Connected Sub address 10.5.4.14
 */

#define MAX_CON_SUB_ADDRESS_INFO_LEN    20

typedef struct
{
    ITS_OCTET typeInfo;
    ITS_OCTET info[MAX_CON_SUB_ADDRESS_INFO_LEN];
}
BSSAP_ConnectedSubAddress_IE;

/* 
 * Allowed Actions 10.5.4.27
 */

typedef struct
{
    ITS_OCTET value;
}
BSSAP_AllowedAction_IE;

#define ACTIVATION_OF_CCBS_MASK       0x80
#define ACTIVATION_OF_CCBS_NOT_POS    0
#define ACTIVATION_OF_CCBS_POS        1

/*
 * High Level Compatibility
 */

#define MAX_HIGH_LEVEL_COMP_INFO  3

typedef struct
{
   ITS_OCTET codingPrsInterpret;
   ITS_OCTET characterstics;
   ITS_OCTET extendedCharacterstics;
}
BSSAP_HighLevelCompInfo_IE;

/*
 * Low Level Compatibility
 */

#define MAX_LOW_LEVEL_COMP_INFO    13

typedef struct
{
   ITS_OCTET data[MAX_LOW_LEVEL_COMP_INFO];
}
BSSAP_LowLevelCompInfo_IE;

/*
 * Progress Indicator 10.5.4.21
 */

typedef struct 
{
    ITS_OCTET codingAndLocation;
    ITS_OCTET description;
}
BSSAP_ProgressIndicator_IE;

#define PROGRESS_CALL_NOT_END_TO_END_PLMN        1
#define PROGRESS_DEST_ADDR_NOT_PLMN              2
#define PROGRESS_ORIG_ADDR_NOT_PLMN              3
#define PROGRESS_CALL_RETURN_TO_PLMN             4
#define PROGRESS_IN_BAND_INFO_PATTERN_AVAILABLE  8
#define PROGRESS_CALL_END_TO_END_PLMN            32
#define PROGRESS_QUEUING                         64

/*
 * Setup Container Message
 */

#define MAX_SETUP_MSG_LEN    100

typedef struct
{
    ITS_OCTET data[MAX_SETUP_MSG_LEN];
}
BSSAP_SetupContainer_IE;

/*
 * Auxillary States 10.5.4.17
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_KeyPadFacility_IE;

/*
 * Auxillary States 10.5.4.4
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_AuxState_IE;

#define HOLD_AUX_STATE_MASK               0x0c
#define HOLD_AUX_STATE_IDLE               0x01
#define HOLD_AUX_STATE_REQUEST            0x02
#define HOLD_AUX_STATE_CALL_HELD          0x02
#define HOLD_AUX_STATE_RTRV_REQ           0x03

#define MULTI_PARTY_AUX_STATE_MASK        0x03
#define MULTI_PARTY_AUX_STATE_IDLE        0
#define MULTI_PARTY_AUX_STATE_REQUEST     1
#define MULTI_PARTY_AUX_STATE_MPTY        2
#define MULTI_PARTY_AUX_STATE_SPLIT_REQ   3

/*
 * Stream Identifier 10.5.4.28
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_StreamIdentifier_IE;

/*
 * Emergency Category/Service Category 10.5.4.33
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_EmergencyCategory_IE;

#define EMERGENCY_CATEGORY_VALUE_MASK  0x1f

/*
 * Call State 10.5.4.6
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_CallState_IE;

#define CALL_STATE_CODING_MASK         0xc0
#define CALL_STATE_MASK                0x3f

/*
 * Signal 10.5.4.23
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_Signal_IE;

#define SIGNAL_DIAL_TONE_ON                     0
#define SIGNAL_RING_BACK_TONE_ON                1
#define SIGNAL_INTERCEPT_TONE_ON                2
#define SIGNAL_NETWORK_CONGESTION_TONE_ON       3
#define SIGNAL_BUSY_TONE_ON                     4
#define SIGNAL_CONFIRM_TONE_ON                  5
#define SIGNAL_ANSWER_TONE_ON                   6
#define SIGNAL_CWT_TONE_ON                      7
#define SIGNAL_OFFHOOK_WARNING_TONE_ON          8
#define SIGNAL_ALL_TONES_OFF                    63 
#define SIGNAL_ALERTING_OFF                     79

/*
 * CC Capabilities 10.5.4.5a
 */
typedef struct
{
    ITS_OCTET value;
}
BSSAP_CCCapabilities_IE;

#define CC_CAPAB_DTMF_MASK    0x01
#define CC_CAPAB_PCP_MASK     0x02

/*
 * Alerting pattern 10.5.4.26
 */

typedef struct
{
    ITS_OCTET value;
}
BSSAP_AlertingPattern_IE;

#define ALERTING_PATTERN_MASK  0x0f
#define ALERTING_PATTERN_1     0x00
#define ALERTING_PATTERN_2     0x01
#define ALERTING_PATTERN_3     0x02
#define ALERTING_PATTERN_4     0x03
#define ALERTING_PATTERN_5     0x04
#define ALERTING_PATTERN_6     0x05
#define ALERTING_PATTERN_7     0x06
#define ALERTING_PATTERN_8     0x07
#define ALERTING_PATTERN_9     0x08

/*
 * Called party BCD Number 10.5.4.7
 */

#define MAX_CALLED_NUM_LEN 40

typedef struct
{
    ITS_OCTET typeAndNumPlan;
    ITS_OCTET digits[MAX_CALLED_NUM_LEN];
}
BSSAP_CalledPartyBCDNumber_IE;

#define TYPE_OF_NUMBER_MASK               0x70
#define TYPE_OF_NUMBER_UNKNOWN            0
#define TYPE_OF_NUMBER_INTL               1
#define TYPE_OF_NUMBER_NAT                2
#define TYPE_OF_NUMBER_NETWORK_SPECIFIC   3
#define TYPE_OF_NUMBER_DEDICATED_ACCESS   4

#define NUM_PLAN_MASK                     0x0f
#define NUM_PLAN_UNKOWN                   0
#define NUM_PLAN_ISDN                     1
#define NUM_PLAN_DATA                     3
#define NUM_PLAN_TELEX                    4
#define NUM_PLAN_NATIONAL                 8
#define NUM_PLAN_PRIVATE                  9
#define NUM_PLAN_CTS_RESERVED             11

/*
 * Called Party Sub address 10.5.4.8
 */

#define MAX_CD_SUB_ADDRESS_INFO_LEN       20

typedef struct
{
    ITS_OCTET typeInfo;
    ITS_OCTET info[MAX_CD_SUB_ADDRESS_INFO_LEN];
}
BSSAP_CalledPartySubAddress_IE;

#define SUB_ADDRESS_TYPE_MASK             0x70
#define SUB_ADDRESS_TYPE_NSAP             0
#define SUB_ADDRESS_TYPE_USER_SPECIFIED   2
#define SUB_ADDRESS_ODDEVEN_MASK          0x08
#define SUB_ADDRESS_EVEN_SIGNAL           0
#define SUB_ADDRESS_ODD_SIGNAL            1

/*
 * Calling party BCD Number 10.5.4.9
 */

#define MAX_CALLING_NUM_LEN               40

typedef struct
{
    ITS_OCTET typeAndNumPlan;
    ITS_OCTET presentationScreening;
    ITS_OCTET digits[MAX_CALLING_NUM_LEN];
}
BSSAP_CallingPartyBCDNumber_IE;

#define USER_SCREENING_MASK                 0x03
#define USER_PROVIDED_NOT_SCREENED          0
#define USER_PROVIDED_VERIFIED_AND_PASSED   1
#define USER_PROVIDED_VERIFIED_AND_FAILED   2
#define NETWORK_PROVIDED_SCREENING          3

#define PRESENTATION_MASK                   0x60
#define PRESENTATION_ALLOWED                0
#define PRESENTATION_RESTRICTED             1
#define PRESENTATION_NUMBER_NOT_AVAILABLE   2

/*
 * Calling Party Sub address 10.5.4.10
 */

#define MAX_CG_SUB_ADDRESS_INFO_LEN    20

typedef struct
{
    ITS_OCTET typeInfo;
    ITS_OCTET info[MAX_CG_SUB_ADDRESS_INFO_LEN];
}
BSSAP_CallingPartySubAddress_IE;

/*
 * Redirecting party BCD Number 10.5.4.21b
 */

#define MAX_REDIRECTING_NUM_LEN 40

typedef struct
{
    ITS_OCTET typeAndNumPlan;
    ITS_OCTET presentationScreening;
    ITS_OCTET digits[MAX_REDIRECTING_NUM_LEN];
}
BSSAP_RedirectingPartyBCDNumber_IE;

/*
 * Redirecting Party Sub address 10.5.4.21c
 */

#define MAX_RD_SUB_ADDRESS_INFO_LEN    20

typedef struct
{
    ITS_OCTET typeInfo;
    ITS_OCTET info[MAX_RD_SUB_ADDRESS_INFO_LEN];
}
BSSAP_RedirectingPartySubAddress_IE;

/*
 * Bearer Data 10.5.4.5
 */

#define MAX_BEARER_DATA_LEN            20
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  octet3;
    ITS_OCTET  octet3a;
    ITS_OCTET  data[MAX_BEARER_DATA_LEN];
}
BSSAP_BearerData_IE;

#define BEARER_DATA_RADIO_CHANNEL_MASK                     0x60
#define RADIO_CHANNEL_REQUIREMENT_RESERVED                 0x00
#define RADIO_CHANNEL_REQUIREMENT_FULL_RATE_SUPPORT_ONLY   0x01
#define RADIO_CHANNEL_REQUIREMENT_HALF_RATE_PREFERED       0x02
#define RADIO_CHANNEL_REQUIREMENT_FULL_RATE_PREFERED       0x03

#define BEARER_DATA_CODING_MASK                            0x10

#define BEARER_DATA_GSM_CODING                             0
#define BEARER_DATA_RESERVED_CODING                        1
#define BEARER_DATA_TRANSFER_MODE_MASK                     0x08
#define BEARER_DATA_TRANSFER_MODE_CKT                      0
#define BEARER_DATA_TRANSFER_MODE_PACKET                   1
#define BEARER_DATA_INFO_TRANSFER_CAPAB_MASK               0x07
#define INFO_TRANSFER_CAPAB_SPEECH                         0
#define INFO_TRANSFER_CAPAB_UNRESTRICTED_DIGITAL           1
#define INFO_TRANSFER_CAPAB_31K_AUDIO                      2
#define INFO_TRANSFER_CAPAB_FAX_GROUP                      3
#define INFO_TRANSFER_CAPAB_OTHER_ITC                      5
#define INFO_TRANSFER_CAPAB_RESERVED                       7

/* Octet 3a */

#define SPEECH_VERSION_MASK              0x0f
#define GSM_FULL_RATE_SPEECH_VERSION_1   0x00
#define GSM_FULL_RATE_SPEECH_VERSION_2   0x01
#define GSM_FULL_RATE_SPEECH_VERSION_3   0x04
#define GSM_HALF_RATE_SPEECH_VERSION_1   0x02
#define GSM_HALF_RATE_SPEECH_VERSION_3   0x05

/* octet 4 */

#define BEARER_DATA_COMPRESSION_MASK     9x40
#define DATA_COMPRESSION_NOT_POOSIBLE    0
#define DATA_COMPRESSION_POSSIBLE        1
#define BEARER_DATA_DUPLEX_MODE_MASK     0x08
#define HALF_DUPLEX_MODE                 0
#define FULL_DUPLEX_MODE                 1

#define BEARER_DATA_SERVICE_DATA_STRUCTURE_MASK   0x30
#define SERVICE_DATA_INTEGRITY                    0
#define SERVICE_DATA_UNSTRUCTURED                 3
#define BEARER_DATA_CONF_MASK                     0x04
#define CONF_POINT_TO_POINT                       0
#define BEARER_DATA_NRR_MASK                      0x02
#define NRR_NO_MEANING                            0
#define NRR_DATA_UPTO_4800                        1

/* Octet 5 */
#define BEARER_DATA_ACCESS_IDENTITY_MASK   0x60
#define ACCESS_IDENTITY_OCTET_IDENTIFIER   0x00
#define BEARER_DATA_RATE_ADAPTATION_MASK   0x18
#define RATE_ADAPTATION_NONE               0x00
#define RATE_ADAPTATION_V110               0x01
#define RATE_ADAPTATION_CCITT_X31          0x02
#define RATE_ADAPTATION_OTHER              0x03
#define BEARER_DATA_ACCESS_PROTOCOL_MASK   0x07
#define ACCESS_PROTOCOL_I440               0x01
#define ACCESS_PROTOCOL_X21                0x02
#define ACCESS_PROTOCOL_X21_DEDICATED_IND  0x03
#define ACCESS_PROTOCOL_X21_DEDICATED_UNIV 0x04
#define ACCESS_PROTOCOL_X21_NON_DEDICATED  0x05
#define ACCESS_PROTOCOL_X32                0x06

/* Octet 5a */

#define BEARER_DATA_OTHER_RATE_ADAPTATION_MASK       0x18
#define OTHER_RATE_ADAPTATION_V120                   0x00
#define BEARER_DATA_OTHER_INFO_TRANSFER_CAPAB_MASK   0x60
#define OTHER_INFO_TRANSFER_CAPAB_RSTR_DIGITAL_INFO  0x00


/* Octet 5b */
#define BEARER_DATA_RATE_ADAPTATION_HEADER_MASK      0x40
#define RATE_ADAPTATION_HEADER_INCLUDED              0
#define RATE_ADAPTATION_HEADER_NOT_INCLUDED          1
#define BEARER_DATA_MULTIFRAME_MASK                  0x20
#define MULTIFRAME_SUPPORTED                         0
#define MULTIFRAME_NOT_SUPPORTED                     1
#define BEARER_DATA_MODE_OF_OPERATION_MASK           0x10
#define MODE_OF_OPERATION_TRANSPARENT                0
#define MODE_OF_OPERATION_NON_TRANSPARENT            1
#define BEARER_DATA_LOGICAL_LINK_ID                  0x80
#define LOGICAL_LINK_ID_DEFAULT                      0
#define LOGICAL_LINK_ID_NOT_DEFAULT                  1
#define BEARER_DATA_ASSIGN_MASK                      0x40
#define MSG_ORIG_DEFAULT_ASSIGNEE                    0
#define MSG_ORIG_ASSIGNOR                            1
#define BEARER_DATA_NEGOTIATE_TYPE                   0x20
#define NEGOTIATE_TYPE_IN_BAND                       0
#define NEGOTIATE_TYPE_USER_INFO                     1

/*Octet 6 */
#define BEARER_DATA_LAYER1_ID_MASK        0x60
#define LAYER1_ID_OCTET_IDENTIFIER        1
#define BEARER_DATA_USER_INFO_LAYER_1     0x1e
#define USER_INFO_LAYER_1_DEFAULT         0x00
#define BEARER_DATA_SYNC_MASK             0x01
#define PROTOCOL_SYNC                     0
#define PROTOCOL_ASYNC                    1

/*Octet 6a */
#define BEARER_DATA_STOP_BIT_MASK         0x40
#define STOP_BIT_ONE                      0
#define STOP_BIT_TWO                      1
#define BEARER_DATA_NEGOTIATION_OPT_MASK  0x20
#define IN_BAND_NEGOTIATION_NOT_POSSIBLE  0
#define BEARER_DATA_DATA_BIT_MASK         0x10
#define DATA_BIT_SEVEN                    0
#define DATA_BIT_EIGTH                    1
#define BEARER_DATA_USER_RATE_MASK        0x0f
#define USER_RATE_03KBPS                  0x01
#define USER_RATE_12KBPS                  0x02
#define USER_RATE_24KBPS                  0x03
#define USER_RATE_48KBPS                  0x04
#define USER_RATE_96KBPS                  0x05
#define USER_RATE_120KBPS                 0x06
#define USER_RATE_112KBPS                 0x07

/*Octet 6b */
#define BEARER_DATA_INTERMEDIATE_RATE_MASK          0x60
#define INTERMEDIATE_RATE_08KBPS                    0x02
#define INTERMEDIATE_RATE_116KBPS                   0x03
#define BEARER_DATA_NETWORK_IND_CLOCK_TRANS_MASK    0x10
#define NETWORK_IND_CLOCK_TRANS_REQUIRED            0x00
#define NETWORK_IND_CLOCK_TRANS_NOT_REQUIRED        0x01
#define BEARER_DATA_NETWORK_IND_CLOCK_RCV_MASK      0x08
#define NETWORK_IND_CLOCK_RCV_REQUIRED              0x00
#define NETWORK_IND_CLOCK_RCV_NOT_REQUIRED          0x01
#define BEARER_DATA_PARITY_INFO_MASK                0x07
#define PARITY_INFO_ODD                             0x00
#define PARITY_INFO_EVEN                            0x02
#define PARITY_INFO_NONE                            0x03
#define PARITY_INFO_FORCED_TO_0                     0x04
#define PARITY_INFO_FORCED_TO_1                     0x05

/* Octet 6c */
#define BEARER_DATA_CONN_ELMT_MASK                  0x60
#define CONN_ELMT_TRANSPARENT                       0
#define CONN_ELMT_NON_TRANSPARENT                   1
#define CONN_ELMT_TRANSPARENT_PREFERRED             2
#define CONN_ELMT_NON_TRANSPARENT_PREFERRED         2
#define BEARER_DATA_MODEM_TYPE_MASK                 0x1f
#define MODEM_TYPE_NONE                             0x00
#define MODEM_TYPE_V21                              0x01
#define MODEM_TYPE_V22                              0x02
#define MODEM_TYPE_V22BIS                           0x03
#define MODEM_TYPE_V23                              0x04
#define MODEM_TYPE_V26TER                           0x05
#define MODEM_TYPE_V32                              0x06
#define MODEM_TYPE_UNDEFINED_INTERFACE              0x07
#define MODEM_TYPE_AUTO_BAUDING                     0x08

/*Octet 6d */
#define BEARER_DATA_OTHER_MODEM_TYPE_MASK           0x60
#define OTHER_MODEM_TYPE_NONE                       0x00
#define OTHER_MODEM_TYPE_V32                        0x02
#define BEARER_DATA_FIXED_NETWORK_USER_RATE_MASK    0x1f
#define FIXED_NETWORK_USER_RATE_NOT_APPLICABLE      0x00
#define FIXED_NETWORK_USER_RATE_96K                 0x01
#define FIXED_NETWORK_USER_RATE_144K                0x02
#define FIXED_NETWORK_USER_RATE_192K                0x03
#define FIXED_NETWORK_USER_RATE_288K                0x04
#define FIXED_NETWORK_USER_RATE_384K                0x05
#define FIXED_NETWORK_USER_RATE_480K                0x06
#define FIXED_NETWORK_USER_RATE_560K                0x07
#define FIXED_NETWORK_USER_RATE_640K                0x08

/* Octet 6e */
#define BEARER_DATA_ACCEPTABLE_CHANNEL_MASK         0x78
#define ACCEPTABLE_CHANNEL_TCH_144_NOT_ACCEPTABLE   0x00
#define ACCEPTABLE_CHANNEL_TCH_144_ACCEPTABLE       0x40
#define ACCEPTABLE_CHANNEL_TCH_96_NOT_ACCEPTABLE    0x00
#define ACCEPTABLE_CHANNEL_TCH_96_ACCEPTABLE        0x10
#define ACCEPTABLE_CHANNEL_TCH_48_NOT_ACCEPTABLE    0x00
#define ACCEPTABLE_CHANNEL_TCH_48_ACCEPTABLE        0x08
#define BEARER_DATA_NUMBER_OF_TRAFFIC_CHANNELS      0x07
#define NUMBER_OF_TRAFFIC_CHANNELS_1TCH             0x00
#define NUMBER_OF_TRAFFIC_CHANNELS_2TCH             0x01
#define NUMBER_OF_TRAFFIC_CHANNELS_3TCH             0x02
#define NUMBER_OF_TRAFFIC_CHANNELS_4TCH             0x03
#define NUMBER_OF_TRAFFIC_CHANNELS_5TCH             0x04
#define NUMBER_OF_TRAFFIC_CHANNELS_6TCH             0x05
#define NUMBER_OF_TRAFFIC_CHANNELS_7TCH             0x06
#define NUMBER_OF_TRAFFIC_CHANNELS_8TCH             0x07

/* Octet 6f */
#define BEARER_DATA_UIMI_MASK                       0x70
#define UIMI_NOT_ALLOWED                            0
#define UIMI_1TCH_ALLOWED                           1
#define UIMI_2TCH_ALLOWED                           2
#define UIMI_3TCH_ALLOWED                           3
#define UIMI_4TCH_ALLOWED                           4
#define BEARER_DATA_AIR_INTERFACE_RATE_MASK         0x0f
#define AIR_INTERFACE_RATE_NOT_APPLICABLE           0
#define AIR_INTERFACE_RATE_96                       1
#define AIR_INTERFACE_RATE_144                      2
#define AIR_INTERFACE_RATE_192                      3
#define AIR_INTERFACE_RATE_288                      5
#define AIR_INTERFACE_RATE_384                      6
#define AIR_INTERFACE_RATE_1432                     7
#define AIR_INTERFACE_RATE_576                      8
#define AIR_INTERFACE_RATE_INTERPRETED_NETWORK      9

/*Octet 7 */
#define BEARER_DATA_LAYER2_IDENTITY_MASK            0x60
#define LAYER2_IDENTITY_OCTET_STRING                0x02
#define BEARER_DATA_LAYER2_USER_INFO                0x1f
#define LAYER2_USER_INFO_X25                        0x06
#define LAYER2_USER_INFO_ISO_6429                   0x08
#define LAYER2_USER_INFO_VIDEOTEX_PROF1             0x0a
#define LAYER2_USER_INFO_COPNOFICI                  0x0c
#define LAYER2_USER_INFO_X75                        0x0d

/***********************************************************************
 * UE Security Information
 * Ref: 3.2.3.10
 */
typedef struct
{
    ITS_OCTET    sec_info[1];
}
BSSAP_UESecurityInformation;

/***********************************************************************
 * union of above (plus a pad), for messages
 */
typedef struct
{
    ITS_OCTET   param_id;
    ITS_OCTET   param_length;
    union
    {
        BSSAP_CircuitIdentityCode           circuitIdentityCode;
        BSSAP_ResourceAvailable             resourceAvailable;
        BSSAP_Cause                         cause;
        BSSAP_RejectCause_IE                rejectCause;
        BSSAP_AuthFailParameter_IE          authFailParameter;
        BSSAP_Imsi                          imsi;
        BSSAP_Tmsi                          tmsi;
        BSSAP_NumberOfMSs                   numberOfMSs;
        BSSAP_Layer3HeaderInfo              layer3HeaderInfo;
        BSSAP_EncryptionInfo                encryptionInfo;
        BSSAP_ChannelType                   chanType;
        BSSAP_Periodicity                   periodicity;
        BSSAP_ExtendedResourceIndicator     extendedResInd;
        BSSAP_TotalResourceAccessible       totalResAccessible;
        BSSAP_LSAIdentifier                 lsaId;
        BSSAP_LSAIdentifierList             lsaIdList;
        BSSAP_CellIdentifier                cellId;
        BSSAP_Priority                      priority;
        BSSAP_ClassmarkInfoType2            classmarkInfo2;
        BSSAP_ClassmarkInfoType3            classmarkInfo3;
        BSSAP_BandToBeUsed                  bandToBeUsed;
        BSSAP_RRCause                       rrCause;
        BSSAP_Layer3Info                    layer3Info;
        BSSAP_DLCI                          dlci;
        BSSAP_DownlinkDTX                   downLinkDTX;
        BSSAP_CellIdentifierList            cellIdList;
        BSSAP_LSAInfo                       lsaInfo;
        /* BSSAP_ResponseRequest            responseRequest; only Element ID*/
        BSSAP_ResourceIndMethod             resourceIndMethod;
        BSSAP_ClassmarkInfoType1            classmarkInfo1;
        BSSAP_CircuitIdCodeList             circuitIdCodeList;
        BSSAP_Diagnostics                   diagnostics;
        BSSAP_ChosenChannel                 chosenChannel;
        BSSAP_CipherResponseMode            cipherResponseMode;
        BSSAP_L3MessageContents             l3MsgContents;
        BSSAP_ChannelNeeded                 channelNeeded;
        BSSAP_TraceType                     traceType;
        BSSAP_TriggerID                     triggerId;
        BSSAP_TraceReference                traceRef;
        BSSAP_TransactionId                 transactionId;
        BSSAP_MobileIdentity                mobileId;
        BSSAP_Omcid                         omcid;
        BSSAP_ForwardInd                    forwardInd;
        BSSAP_ChosenEncrptAlgorithm         chosenEncryptAlgorithm;
        BSSAP_CircuitPool                   circuitPool;
        BSSAP_CircuitPoolList               circuitPoolList;
        BSSAP_TimeIndication                timeInd;
        BSSAP_ResourceSituation             resSituation;
        BSSAP_CurrentChannelType1           crrtChanType1;
        BSSAP_QueuingIndicator              queuingInd;
        BSSAP_SpeechVersion                 speechVer;
        BSSAP_AssignmentRequirement         assignmentRequirement;
        /* BSSAP_TalkerFlag                 talkerFlag; -- Only Element ID */
        BSSAP_GroupCallReference            groupCallRef;
        BSSAP_eMLPP_Priority                eMLPP_pri;
        BSSAP_ConfigEvolutionInd            configEvolutionInd;
        /*BSSAP_OldBSStoNewBSSInformation   bssInfo; -no struct defined here */
        BSSAP_LCSQoS                        lcsQoS;
        BSSAP_LSAAccessControlSuppr         lsaAccCtrlSuppr;
        BSSAP_LCSPriority                   lcsPrio;
        BSSAP_LocationType                  locType;
        BSSAP_LocationEstimate              locEst;
        BSSAP_PositioningData               posData;
        BSSAP_LCSCause                      lcsCause;
        BSSAP_LCSClientType                 clientType;
        BSSAP_APDU                          apdu;
        BSSAP_NetworkElementIdentity        netElmntID;
        BSSAP_GPSAssistanceData             gpsAssistData;
        BSSAP_DecipheringKeys               decipherKeys;
        BSSAP_ReturnErrorRequest            returnErrReq;
        BSSAP_ReturnErrorCause              returnErrCse;
        BSSAP_Segmentation                  segmentation;
        BSSAP_ServiceHandover               serviceHandover;
        BSSAP_SoruceRNCtoTargetRNCInfoUMTS  srtriUmts;
        BSSAP_SoruceRNCtoTargetRNCInfoCDMA  srtriCdma;
        BSSAP_InterSysInfo                  interSysInfo;
        BSSAP_ExtraInformation              extraInfo;
        BSSAP_CurrentChannelType2           crrtChanType2;
        BSSAP_TargetCellRadioInformation    tcrInfo;
        BSSAP_GPRSSuspendInformation        grpsInfo;
        BSSAP_MultirateConfigInformation    mcInfo;
        BSSAP_DualTransferModeInformation   dtmInfo;
        BSSAP_UECapInformation              ueCapInfo;
        BSSAP_cdma2000CapInformation        cdmaCapInfo;
        BSSAP_DownlinkCellLoadInfo          dlCellLoadInfo;
        BSSAP_UplinkCellLoadInfo            ulCellLoadInfo;
        BSSAP_UTRANPreconfigIndSet          utranSet;
        BSSAP_UESecurityInformation         ueSecurityInfo;
        BSSAP_Facility_IE                   facility;
        BSSAP_UserToUserInfo                userToUserInfo;
        BSSAP_ProgressIndicator_IE          progressIndicator;
        BSSAP_RepeatIndication              repeatIndicator;
        BSSAP_CCCause_IE                    ccCause;
        BSSAP_CongestionLevel_IE            congestionLevel;
        BSSAP_ConnectedNumber_IE            connectedNumber;
        BSSAP_ConnectedSubAddress_IE        connectedSubAddress;
        BSSAP_AllowedAction_IE              allowedAction;
        BSSAP_HighLevelCompInfo_IE          highLevelCompInfo;
        BSSAP_LowLevelCompInfo_IE           lowLevelCompInfo;
        BSSAP_SetupContainer_IE             setupContainer;
        BSSAP_Signal_IE                     signal;
        BSSAP_CalledPartyBCDNumber_IE       calledPartyBCDNumber;
        BSSAP_CalledPartySubAddress_IE      calledPartySubAddress;
        BSSAP_CallingPartyBCDNumber_IE      callingPartyBCDNumber;
        BSSAP_CallingPartySubAddress_IE     callingPartySubAddress;
        BSSAP_RedirectingPartyBCDNumber_IE  redirectingPartyBCDNumber;
        BSSAP_RedirectingPartySubAddress_IE redirectingPartySubAddress;
        BSSAP_BearerData_IE                 bearerData;
        BSSAP_SSVersion_IE                  ssVersion;
        BSSAP_NotificationIndicator_IE      notificationIndicator;
        BSSAP_CCCapabilities_IE             ccCapabilities;
        BSSAP_AlertingPattern_IE            alertingPattern; 
        BSSAP_AuxState_IE                   auxState;
        BSSAP_KeyPadFacility_IE             keyPadFacility;
        BSSAP_StreamIdentifier_IE           streamIdentifier;
        BSSAP_EmergencyCategory_IE          emergencyCategory;
        BSSAP_SupportedCodecs_IE            supportedCodecs;
        BSSAP_CallState_IE                  callState;
        BSSAP_PriorityLevel_IE              priorityLevel;
        BSSAP_LocUpdatingType               locationUpdatingType;
        BSSAP_CypKeySequence                CypheringKeySequence;
        BSSAP_LocationAreaId                LocationAreaIdentifier;
        BSSAP_ParameterRAND                 ParameterRand;
        BSSAP_ParameterSRES                 ParameterSres;
        BSSAP_IDType                        IdentityType;
        BSSAP_CmServiceType                 CMServiceType;
        BSSAP_TimeZo                        TimeZone;
        BSSAP_TimeZoTime                    TimeZoneTime;

        ITS_OCTET                          pad[BSSAP_MAX_IE_SIZE];
    }
    param_data;
}
ITS_BSSAP_IE;

#if defined(__cplusplus)
}
#endif

#endif ITS_BSSAP_H
