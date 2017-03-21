/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: abis_traffic_management.h,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:52  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.3  2005/12/20 13:56:30  yranade
 *  Immediate Assignment Release related changes: Badrinarayanan
 *
 *  Revision 1.1.2.2  2005/09/23 06:42:59  mkrishna
 *  Bug fixes added
 *
 *  Revision 1.1.2.1  2005/08/16 11:44:14  mkrishna
 *  Added Initial version after unit testing.
 *
 *
 ****************************************************************************/
                                                                                                                                              

#if !defined(ABIS_TMM_H)
#define ABIS_TMM__H

#include <abis_codec.h>

/*   
 * This file contains Traffic Management Information Elements 
 * and Message Structures used at the Abis interface  
 *
 * All the information referred by 3GPP TS 08.58 specification
 * unless specified
 */

/* Message Discriminator */
#define TM_NON_TRANSPARENT_MSG            0x00
#define TM_TRANSPARENT_MSG                0x01
#define TM_RESERVED                       0x00
#define TM_RADIO_LINK_LAYER_MANGMNT_MSG   0x01
#define TM_DEDICATED_CHANNEL_MANGMNT_MSG  0x04
#define TM_COMMON_CHANNEL_MANGMNT_MSG     0x06
#define TM_TRX_MANGMNT_MSG                0x08
#define TM_LOCATION_SERVICE_MSG           0x10

/* Message Type */

/* Radio Link Layer Management Messages */ 
#define TM_RLLM_DATA_REQUEST                  0x01
#define TM_RLLM_DATA_INDICATION               0x02
#define TM_RLLM_ERROR_INDICATION              0x03
#define TM_RLLM_ESTABLISH_REQUEST             0x04
#define TM_RLLM_ESTABLISH_CONFIRM             0x05
#define TM_RLLM_ESTABLISH_INDICATION          0x06
#define TM_RLLM_RELEASE_REQUEST               0x07
#define TM_RLLM_RELEASE_CONFIRM               0x08
#define TM_RLLM_RELEASE_INDICATION            0x09
#define TM_RLLM_UNIT_DATA_REQUEST             0x0A
#define TM_RLLM_UNIT_DATA_INDICATION          0x0B

/* Common Channel Management/TRX Management Messages */
#define TM_CCM_BCCH_INFORMATION              0x11
#define TM_CCM_CCCH_LOAD_INDICATION          0x12
#define TM_CCM_CHANNEL_REQUIRED              0x13
#define TM_CCM_DELETE_INDICATION             0x14
#define TM_CCM_PAGING_COMMAND                0x15
#define TM_CCM_IMMEDIATE_ASSIGN_COMMAND      0x16
#define TM_CCM_SMS_BROADCAST_REQUEST         0x17
#define TM_CCM_RF_RESOURCE_INDICATION        0x19
#define TM_CCM_SACCH_FILLING                 0x1A
#define TM_CCM_OVERLOAD                      0x1B
#define TM_CCM_ERROR_REPORT                  0x1C
#define TM_CCM_SMS_BROADCAST_COMMAND         0x1D
#define TM_CCM_CBCH_LOAD_INDICATION          0x1E
#define TM_CCM_NOTIFICATION_COMMAND          0x1F

/* Dedicated Channel Management Messages  */
#define TM_DCM_CHANNEL_ACTIVATION               0x21
#define TM_DCM_CHANNEL_ACTIVATION_ACK           0x22
#define TM_DCM_CHANNEL_ACTIVATION_NEGATIVE_ACK  0x23
#define TM_DCM_CONNECTION_FAILURE               0x24
#define TM_DCM_DEACTIVATE_SACCH                 0x25
#define TM_DCM_ENCRYPTION_COMMAND               0x26
#define TM_DCM_HANDOVER_DETECTION               0x27
#define TM_DCM_MEASUREMENT_RESULT               0x28
#define TM_DCM_MODE_MODIFY_REQUEST              0x29
#define TM_DCM_MODE_MODIFY_ACK                  0x2A
#define TM_DCM_MODE_MODIFY_NEGATIVE_ACK         0x2B
#define TM_DCM_PHYSICAL_CONTEXT_REQUEST         0x2C
#define TM_DCM_PHYSICAL_CONTEXT_CONFIRM         0x2D
#define TM_DCM_RF_CHANNEL_RELEASE               0x2E
#define TM_DCM_MS_POWER_CONTROL                 0x2F
#define TM_DCM_BS_POWER_CONTROL                 0x30
#define TM_DCM_PREPROCESS_CONFIGURE             0x31
#define TM_DCM_PREPROCESSED_MEASUREMENT_RESULT  0x32
#define TM_DCM_RF_CHANNEL_RELEASE_ACK           0x33
#define TM_DCM_SACCH_INFO_MODIFY                0x34
#define TM_DCM_TALKER_DETECTION                 0x35
#define TM_DCM_LISTENER_DETECTION               0x36
#define TM_DCM_REMOTE_CODEC_CONFIGN_REPORT      0x37
#define TM_DCM_ROUND_TRIP_DELAY_REPORT          0x38
#define TM_DCM_PRE_HANDOVER_NOTIFICATION        0x39
#define TM_DCM_MULTIRATE_CODEC_MOD_REQUEST      0x3A
#define TM_DCM_MULTIRATE_CODEC_MOD_ACK          0x3B
#define TM_DCM_MULTIRATE_CODEC_MOD_NEGATIVE_ACK 0x3C
#define TM_DCM_MULTIRATE_CODEC_MOD_PERFORMED    0x3D
#define TM_DCM_TFO_REPORT                       0x3E
#define TM_DCM_TFO_MODIFICATION_REQUEST         0x3F

/* Location Services Messages */
#define TM_LCS_LOCATION_INFORMATION             0x41

/* Other Information Element Identifiers */
#define TM_IEI_CHANNEL_NUMBER              0x01
#define TM_IEI_LINK_IDENTIFIER             0x02
#define TM_IEI_ACTIVATION_TYPE             0x03
#define TM_IEI_BS_POWER                    0x04
#define TM_IEI_CHANNEL_IDENTIFICATION      0x05
#define TM_IEI_CHANNEL_MODE                0x06
#define TM_IEI_ENCRYPTION_INFORMATION      0x07
#define TM_IEI_FRAME_NUMBER                0x08
#define TM_IEI_HANDOVER_REFERENCE          0x09
#define TM_IEI_L1_INFORMATION              0x0A
#define TM_IEI_L3_INFORMATION              0x0B
#define TM_IEI_MS_IDENTITY                 0x0C
#define TM_IEI_MS_POWER                    0x0D
#define TM_IEI_PAGING_GROUP                0x0E
#define TM_IEI_PAGING_LOAD                 0x0F
#define TM_IEI_PHYSICAL_CONTEXT            0x10
#define TM_IEI_ACCESS_DELAY                0x11
#define TM_IEI_RACH_LOAD                   0x12
#define TM_IEI_REQUEST_REFERENCE           0x13
#define TM_IEI_RELEASE_MODE                0x14
#define TM_IEI_RESOURCE_INFORMATION        0x15
#define TM_IEI_RLM_CAUSE                   0x16
#define TM_IEI_STARTING_TIME               0x17
#define TM_IEI_TIMING_ADVANCE              0x18
#define TM_IEI_UPLINK_MEASUREMENTS         0x19
#define TM_IEI_CAUSE                       0x1A
#define TM_IEI_MEASUREMENT_RESULT_NUMBER   0x1B
#define TM_IEI_MESSAGE_IDENTIFIER          0x1C
#define TM_IEI_SYSTEM_INFO_TYPE            0x1E
#define TM_IEI_MS_POWER_PARAMETERS         0x1F
#define TM_IEI_BS_POWER_PARAMETERS         0x20
#define TM_IEI_PRE_PROCESSING_PARAMETERS   0x21
#define TM_IEI_PRE_PROCESSED_MEASUREMENTS  0x22
#define TM_IEI_SMSCB_INFORMATION           0x24
#define TM_IEI_MS_TIMING_OFFSET            0x25
#define TM_IEI_ERRONEOUS_MESSAGE           0x26
#define TM_IEI_FULL_BCCH_INFORMATION       0x27
#define TM_IEI_CHANNEL_NEEDED              0x28
#define TM_IEI_CB_COMMAND_TYPE             0x29
#define TM_IEI_SMSCB_MESSAGE               0x2A
#define TM_IEI_FULL_IMMEDIATE_ASSIGN_INFO  0x2B
#define TM_IEI_SACCH_INFORMATION           0x2C
#define TM_IEI_CBCH_LOAD_INFORMATION       0x2D
#define TM_IEI_SMSCB_CHANNEL_INDICATOR     0x2E
#define TM_IEI_GROUP_CALL_REFERENCE        0x2F
#define TM_IEI_CHANNEL_DESCRIPTION         0x30
#define TM_IEI_NCH_DRX_INFORMATION         0x31
#define TM_IEI_COMMAND_INDICATOR           0x32
#define TM_IEI_EMLPP_PRIORITY              0x33
#define TM_IEI_UIC                         0x34
#define TM_IEI_MAIN_CHANNEL_REFERENCE      0x35
#define TM_IEI_MULTIRATE_CONFIGURATION     0x36
#define TM_IEI_MULTIRATE_CONTROL           0x37
#define TM_IEI_SUPPORTED_CODEC_TYPES       0x38
#define TM_IEI_CODEC_CONFIGURATION         0x39
#define TM_IEI_ROUND_TRIP_DELAY            0x3A
#define TM_IEI_TFO_STATUS                  0x3B
#define TM_IEI_LLP_APDU                    0x3C

/* Channel Number */
#define TM_CN_BM_ACCH             0x01
#define TM_CN_START_LM_ACCH       0x02 
#define TM_CN_END_LM_ACCH         0x03  
#define TM_CN_STRAT_SDCCH_4_ACCH  0x04
#define TM_CN_END_SDCCH_4_ACCH    0x07
#define TM_CN_START_SDCCH_8_ACCH  0x08
#define TM_CN_END_SDCCH_8_ACCH    0x0F
#define TM_CN_BCCH                0x10
#define TM_CN_UPLINK_CCCH         0x11
#define TM_CN_DOWNLINK_CCCH       0x12

/* Link Identifier */
#define TM_LI_SIGNAL_CHANNEL        0x00
#define TM_LI_SACCH                 0x01
#define TM_LI_NORMAL_PRIORITY       0x00
#define TM_LI_HIGH_PRIORITY         0x01
#define TM_LI_LOW_PRIORITY          0x02

/* Activation Type */
#define TM_AT_INTIAL_ACTIVATION      0x00
#define TM_AT_REACTIVATION           0x01
#define TM_AT_IMMEDIATE_ASSIGNMENT   0x00
#define TM_AT_NORMAL_ASSIGNMENT      0x01
#define TM_AT_ASYNCRONOUS_HANDOVER   0x02
#define TM_AT_SYNCRONOUS_HANDOVER    0x03
#define TM_AT_ADDITIONAL_ASSIGNMENT  0x04
#define TM_AT_MULTICAST_CONFIG       0x05

/* BS Power */
#define TM_BP_FPC_NOT_IN_USE         0x00
#define TM_BP_FPC_IN_USE             0x01
#define TM_BP_POWER_LEVEL_PN         0x00
#define TM_BP_POWER_LEVEL_PN_2_DB    0x01
#define TM_BP_POWER_LEVEL_PN_4_DB    0x02
#define TM_BP_POWER_LEVEL_PN_6_DB    0x03 
#define TM_BP_POWER_LEVEL_PN_8_DB    0x04
#define TM_BP_POWER_LEVEL_PN_10_DB   0x05
#define TM_BP_POWER_LEVEL_PN_12_DB   0x06
#define TM_BP_POWER_LEVEL_PN_14_DB   0x07
#define TM_BP_POWER_LEVEL_PN_16_DB   0x08
#define TM_BP_POWER_LEVEL_PN_18_DB   0x09
#define TM_BP_POWER_LEVEL_PN_20_DB   0x0A
#define TM_BP_POWER_LEVEL_PN_22_DB   0x0B
#define TM_BP_POWER_LEVEL_PN_24_DB   0x0C
#define TM_BP_POWER_LEVEL_PN_26_DB   0x0D
#define TM_BP_POWER_LEVEL_PN_28_DB   0x0E
#define TM_BP_POWER_LEVEL_PN_30_DB   0x0F

/* Channel Identification 
 * Reffered Spec : 3GPP TS 04.18 */
#define TM_CI_TCH_FACCH_F_SACCH_M          0x00
#define TM_CI_TCH_FACCH_SACCH_F            0x01
#define TM_CI_START_TCH_H_ACCH             0x02
#define TM_CI_END_TCH_H_ACCH               0x03
#define TM_CI_START_SDCCH_4_SACCH_C4_CBCH  0x04
#define TM_CI_END_SDCCH_4_SACCH_C4_CBCH    0x07
#define TM_CI_START_SDCCH_8_SACCH_C8_CBCH  0x08
#define TM_CI_END_SDCCH_8_SACCH_C8_CBCH    0x0F
#define TM_CI_SIGLE_RF_CHANNEL             0x00
#define TM_CI_RF_HOPPING_CHANNEL           0x01

/* Channel Mode */
#define TM_CM_DTX_NOT_APPLIED       0x00
#define TM_CM_DTX_APPLIED           0x01
#define TM_CM_SPEECH                0x01
#define TM_CM_DATA                  0x02
#define TM_CM_SIGNALLING            0x03
#define TM_CM_SDCCH                 0x01
#define TM_CM_FULL_TCH_BM           0x08 
#define TM_CM_HALF_TCH_LM           0x09
#define TM_CM_FULL_TCH_BI_DIR_BM    0x0A
#define TM_CM_FULL_TCH_UNI_DIR_BM   0x1A
#define TM_CM_FULL_TCH_BM_GROUP     0x18
#define TM_CM_HALF_TCH_LM_GROUP     0x19
#define TM_CM_FULL_TCH_BM_BROADCAST 0x28
#define TM_CM_HALF_TCH_LM_BROADCAST 0x29
#define TM_CM_SPEECH_ALG_VERSION1   0x01
#define TM_CM_SPEECH_ALG_VERSION2   0x11
#define TM_CM_SPEECH_ALG_VERSION3   0x21 
#define TM_CM_NO_RESOURCE_REQUIRED  0x00  
#define TM_CM_TRANSPARENT_SERV      0x00
#define TM_CM_NON_TRANSPARENT_SERV  0x01
#define TM_CM_ASYMEMETRIC_43_5_DOWN_14_5_UP 0x21 
#define TM_CM_ASYMEMETRIC_29_0_DOWN_14_5_UP 0x22
#define TM_CM_ASYMEMETRIC_43_5_DOWN_29_UP   0x23
#define TM_CM_ASYMEMETRIC_14_5_DOWN_43_5_UP 0x29
#define TM_CM_ASYMEMETRIC_14_5_DOWN_29_UP   0x2A
#define TM_CM_ASYMEMETRIC_29_DOWN_43_5_UP   0x2B
#define TM_CM_43_5_KBPS             0x34 
#define TM_CM_28_8_KBPS             0x31                   
#define TM_CM_14_5_KBPS             0x18
#define TM_CM_12_KBPS               0x10
#define TM_CM_6_KBPS                0x11
#define TM_CM_32_KBPS               0x38
#define TM_CM_29_KBPS               0x39
#define TM_CM_14_4_KBPS             0x18
#define TM_CM_9_6_KBPS              0x10
#define TM_CM_4_8_KBPS              0x11
#define TM_CM_2_4_KBPS              0x12 
#define TM_CM_1_2_KBPS              0x13
#define TM_CM_600_BPS               0x14
#define TM_CM_1200_75_BPS           0x15 

/* Encryption Inforamtion */
#define TM_EI_NO_ENCRYPTION         0x01  
#define TM_EI_ALG_VERSION1          0x02
#define TM_EI_GSM_A5_2              0x03
#define TM_EI_GSM_A5_3              0x04 
#define TM_EI_GSM_A5_4              0x05 
#define TM_EI_GSM_A5_5              0x06
#define TM_EI_GSM_A5_6              0x07
#define TM_EI_GSM_A5_7              0x08

/* Frame Number */

/* Handover reference */

/* L1 Information */

/* L3 Inforamtion */

/* MS Identity 
 * Reffered Spec : 3GPP TS 24008 */
#define TM_MI_IMSI            0x01
#define TM_MI_IMEI            0x02
#define TM_MI_IMEISV          0x03
#define TM_MI_TMSI_P_TMSI     0x04
#define TM_MI_NO_IDENTITY     0x00
#define TM_MI_EVEN_IDENTITY   0x00  
#define TM_MI_ODD_IDENTITY    0x01 

/* MS Power */
#define TM_MP_FPC_NOT_IN_USE        0x00 
#define TM_MP_FPC_IN_USE            0x01

/* Paging Group */

/* Paging Load */

/* Physical Context */

/* Access Delay */

/* RACH Load */

/* Request Reference */

/* Release mode */
#define TM_RM_NORMAL              0x00 
#define TM_RM_LOCAL_END           0x01 

/* Resource Information */

/* RLM Cause */
#define TM_RC_TIMER_T200_EXPIRED              0x01 
#define TM_RC_RE_ESTABLISHMENT_REQ            0x02
#define TM_RC_UNSOLICITED_UA_RESP             0x03
#define TM_RC_UNSOLICITED_DM_RESP             0x04 
#define TM_RC_UNSOLICITED_DM_RESP_MULTI_FRAME 0x05
#define TM_RC_UNSOLICITED_SUPERVISORY_RESP    0x06
#define TM_RC_SEQUENCE_ERROR                  0x07
#define TM_RC_U_FRAME_INCORRECT_PARAM         0x08
#define TM_RC_S_FRAME_INCORRECT_PARAM         0x09
#define TM_RC_I_FRAME_INCORRECT_USE           0x0A
#define TM_RC_I_FRAME_INCORRECT_LENGTH        0x0B
#define TM_RC_FRAME_NOT_IMPLEMENTED           0x0C 
#define TM_RC_SABM_COMMAND_MULTIFRAME         0x0D
#define TM_RC_SABM_FRAME_WITH_INFO            0x0E

/* Starting Time */

/* Timing Advance */

/* Uplink Measurements */

/* Cause */
#define TM_CAUSE_RADIO_INTERFACE_FAILURE         0x00 
#define TM_CAUSE_RADIO_LINKFAILURE               0x01
#define TM_CAUSE_HANDOVER_ACCESS_FAILURE         0x02
#define TM_CAUSE_TALKER_ACCESS_FAILURE           0x03 
#define TM_CAUSE_OM_INTERVENTION                 0x07
#define TM_CAUSE_NORMAL_EVENT                    0x0F  
#define TM_CAUSE_EQUIPMENT_FAILURE               0x20
#define TM_CAUSE_RADIO_RESOURCE_NOT_AVAILABLE    0x21
#define TM_CAUSE_TERRISTRIAL_CHANNEL_FAILURE     0x22
#define TM_CAUSE_CCCH_OVERLOAD                   0x23
#define TM_CAUSE_ACCH_OVERLOAD                   0x24
#define TM_CAUSE_PROCCESSOR_OVERLOAD             0x25
#define TM_CAUSE_BTS_NOT_EQUIPPED                0x27  
#define TM_CAUSE_REMOTE_TRANSCODER_FAILURE       0x28
#define TM_CAUSE_NOTIFICATION_OVERFLOW           0x29
#define TM_CAUSE_RESOURCE_NOT_AVAILABLE          0x2F
#define TM_CAUSE_REQ_TRANSCOD_NOT_AVAILABLE      0x30
#define TM_CAUSE_SERVICE_NOT_AVAILABLE           0x3F
#define TM_CAUSE_ENCRYPTION_ALG_NOT_IMPLEMENTED  0x40
#define TM_CAUSE_SERVICE_NOT_IMPLEMENTED         0x4F
#define TM_CAUSE_RADIO_CHANNEL_ALREADY_ACTIVATED 0x50
#define TM_CAUSE_INVALID_MSG                     0x5F
#define TM_CAUSE_MSG_DISCRIMINATOR_ERROR         0x60
#define TM_CAUSE_MSG_TYPE_ERROR                  0x61
#define TM_CAUSE_MSG_SEQUENCE_ERROR              0x62
#define TM_CAUSE_GENERAL_INFO_ELEMENT_ERROR      0x63 
#define TM_CAUSE_MAND_INFO_ELEMENT_ERROR         0x64
#define TM_CAUSE_OPTIONAL_INFO_ELEMENT_ERROR     0x65
#define TM_CAUSE_INFO_ELEMENT_NON_EXIST          0x66
#define TM_CAUSE_INFO_ELEMENT_LEN_ERROR          0x67
#define TM_CAUSE_INVALID_INFO_ELEMENT_CONTENTS   0x68
#define TM_CAUSE_PROTOCAOL_ERROR                 0x6F
#define TM_CAUSE_INTERWORKING                    0x7F 

/* Measurement Result Number */

/* Message Identifier */ 

/* SAACH Information */
#define TM_SI_SYSTEM_INFO_5           0x05
#define TM_SI_SYSTEM_INFO_6           0x06
#define TM_SI_SYSTEM_INFO_5_BIS       0x0D
#define TM_SI_SYSTEM_INFO_5_TER       0x0E
#define TM_SI_EXTN_MEASUREMENT_ORDER  0x47
#define TM_SI_MEASUREMENT_INFO        0x48

/* System Info Type */
#define TM_SIT_SYSTEM_INFO_8             0x00 
#define TM_SIT_SYSTEM_INFO_1             0x01
#define TM_SIT_SYSTEM_INFO_2             0x02
#define TM_SIT_SYSTEM_INFO_3             0x03
#define TM_SIT_SYSTEM_INFO_4             0x04
#define TM_SIT_SYSTEM_INFO_5             0x05
#define TM_SIT_SYSTEM_INFO_6             0x06
#define TM_SIT_SYSTEM_INFO_7             0x07
#define TM_SIT_SYSTEM_INFO_16            0x08
#define TM_SIT_SYSTEM_INFO_17            0x09 
#define TM_SIT_SYSTEM_INFO_2_BIS         0x0A
#define TM_SIT_SYSTEM_INFO_2_TER         0x0B
#define TM_SIT_SYSTEM_INFO_5_BIS         0x0D
#define TM_SIT_SYSTEM_INFO_5_TER         0x0E
#define TM_SIT_SYSTEM_INFO_10            0x0F
#define TM_SIT_EXTN_MEASUREMENT_ORDER    0x47
#define TM_SIT_MEASUREMENT_INFO          0x48
#define TM_SIT_SYSTEM_INFO_13            0x28
#define TM_SIT_SYSTEM_INFO_2_QUATER      0x29
#define TM_SIT_SYSTEM_INFO_9             0x2A
#define TM_SIT_SYSTEM_INFO_18            0x2B
#define TM_SIT_SYSTEM_INFO_19            0x2C
#define TM_SIT_SYSTEM_INFO_20            0x2D

/* MS Power Parameters */

/* BS Power Parameters */

/* Pre-processing Parameters */
#define TM_PPP_BASIC_MEASUREMENT         0x00 
#define TM_PPP_PRE_PROCESSED_MEASUREMENT 0x01

/* Pre-processed Measurements */

/* Full Immediate Assign Info */

/* SMSCB Information */

/* MS Timing Offset */

/* Erroneous Message */

/* Full BCCH Information */

/* Channel Needed */
#define TM_CN_ANY_CHANNEL       0x00
#define TM_CN_SDCCH             0x01
#define TM_CN_TCH_F_FULL_RATE   0x02
#define TM_CN_TCH_DUAL_RATE     0x03

/* CB Command Type */
#define TM_CCT_NORMAL_MSG_BROADCAST    0x00 
#define TM_CCT_SCHEDULE_MSG_BROADCAST  0x08
#define TM_CCT_DEFAULT_MSG_BROADCAST   0x07
#define TM_CCT_NULL_MSG_BROADCAST      0x0F
#define TM_CCT_NORMAL_MSG              0x00 
#define TM_CCT_NULL_MSG                0x01
#define TM_CCT_BLOCK_4                 0x00  
#define TM_CCT_BLOCK_1                 0x01 
#define TM_CCT_BLOCK_2                 0x02
#define TM_CCT_BLOCK_3                 0x03

/* SMSCB Message */

/* CBCH Load Information */
#define TM_CLI_UNDERFLOW                 0x00 
#define TM_CLI_OVERFLOW                  0x01
#define TM_CLI_AMOUNT_SMSCB_MSG          0x00
#define TM_CLI_AMOUNT_DELAY_IN_MSG_SLOTS 0x01

/* SMSCB Channel Indicator */
#define TM_SCT_BASIC_CBCH         0x00
#define TM_SCT_EXTENDED_CBCH      0x01

/* Group Call Reference 
 * Reffered Spec : 3GPP TS 24.008 */
#define TM_GCR_VBS               0x00
#define TM_GCR_VGGS              0x01
#define TM_GCR_ACK_REQUIRED      0x01
#define TM_GCR_ACK_NOT_REQUIRED  0x00
#define TM_GCR_NO_PRIORITY       0x00
#define TM_GCR_PRIORITY_LEVEL_4  0x01
#define TM_GCR_PRIORITY_LEVEL_3  0x02
#define TM_GCR_PRIORITY_LEVEL_2  0x03
#define TM_GCR_PRIORITY_LEVEL_1  0x04
#define TM_GCR_PRIORITY_LEVEL_0  0x05
#define TM_GCR_PRIORITY_LEVEL_B  0x06
#define TM_GCR_PRIORITY_LEVEL_A  0x07
#define TM_GCR_NO_CIPHERING      0x00
#define TM_GCR_CIPHERING_KEY_1   0x01
#define TM_GCR_CIPHERING_KEY_2   0x02
#define TM_GCR_CIPHERING_KEY_3   0x03 
#define TM_GCR_CIPHERING_KEY_4   0x04
#define TM_GCR_CIPHERING_KEY_5   0x05
#define TM_GCR_CIPHERING_KEY_6   0x06
#define TM_GCR_CIPHERING_KEY_7   0x07
#define TM_GCR_CIPHERING_KEY_8   0x08
#define TM_GCR_CIPHERING_KEY_9   0x09
#define TM_GCR_CIPHERING_KEY_A   0x0A
#define TM_GCR_CIPHERING_KEY_B   0x0B
#define TM_GCR_CIPHERING_KEY_C   0x0C
#define TM_GCR_CIPHERING_KEY_D   0x0D
#define TM_GCR_CIPHERING_KEY_E   0x0E
#define TM_GCR_CIPHERING_KEY_F   0x0F 

/* Channel Description 
 * Reffered Spec : 3GPP TS 04.18 */
#define TM_CD_TCH_FS_ACCH             0x01
#define TM_CD_START_TCH_HS_ACCH       0x02
#define TM_CD_END_TCH_HS_ACCH         0x03
#define TM_CD_START_SDCCH_4_SACCH_C4  0x04
#define TM_CD_END_SDCCH_4_SACCH_C4    0x07
#define TM_CD_START_SDCCH_8_SACCH_C8  0x08
#define TM_CD_END_SDCCH_8_SACCH_C8    0x0F
#define TM_CD_SIGLE_RF_CHANNEL        0x00
#define TM_CD_RF_HOPPING_CHANNEL      0x01

/* NCH DRX information */

/* Command Indiactor */
#define TM_CI_START   0x00 
#define TM_CI_STOP    0x01

/* eMLPP Priority */

/* UIC */

/* Main channel reference */

/* MultiRate Configuration 
 * Reffered Spec : 3GPP TS  04.18 */
#define TM_MRC_SPEECH_VERSION    0x01 
#define TM_MRC_NSCB_USED         0x00 
#define TM_MRC_NSCB_TURNED_OFF   0x01 
#define TM_MRC_IMPLICIT_RULE     0x00 
#define TM_MRC_START_MODE_FIELD  0x01 

/* MultiRate Control */ 
#define TM_MRC_TFO_ENABLED                     0x00 
#define TM_MRC_TFO_DISABLED                    0x01
#define TM_MRC_RATSCCH_ENABLED_BTS_CHANGE_AMR  0x00
#define TM_MRC_RATSCCH_ENABLED_BSC_USE_CODEC   0x01
#define TM_MRC_RESERVED                        0x02 
#define TM_MRC_RATSCCH_DISABLED                0x03
#define TM_MRC_HANDOVER_NOT_EXPECTED           0x00 
#define TM_MRC_HANDOVER_EXPECTED_SOON          0x01

/* Supported Codec Types */
#define TM_SCT_SPEECH_CODEC_SUPPORTED       0x01 
#define TM_SCT_CODEC_MODE_SUPPORTED         0x01 
#define TM_SCT_MAX_FOUR_SUPPORTED_IN_ACS    0x00
#define TM_SCT_MAX_ONE_SUPPORTED_IN_ACS     0x01
#define TM_SCT_MAX_TWO_SUPPORTED_IN_ACS     0x02 
#define TM_SCT_MAX_THREE_SUPPORTED_IN_ACS   0x03
#define TM_SCT_TFO_VERSION0                 0x00 
#define TM_SCT_FULL_RATE_PREFFERED          0x00 
#define TM_SCT_HALF_RATE_PREFFERED          0x01
#define TM_SCT_ENHANCD_FULL_RATE_PREFFERED  0x02
#define TM_SCT_FR_MULTI_RATE_PREFFERED      0x03
#define TM_SCT_HR_MULTI_RATE_PREFFERED      0x04 
#define TM_SCT_NO_PREFFERED_TYPE            0xFF

/* Codec Configuration */
#define TM_CC_FULL_RATE_IN_USE          0x00 
#define TM_CC_HALF_RATE_IN_USE          0x01
#define TM_CC_ENHANCD_FULL_RATE_IN_USE  0x02 
#define TM_CC_FR_MULTI_RATE_IN_USE      0x03
#define TM_CC_HR_MULTI_RATE_IN_USE      0x04 

/* Round Trip Delay */
#define TM_RTD_BTS_TRANSCODER_RTD    0x00
#define TM_RTD_BTS_REMOTE_BTS_RTD    0x01

/* TFO Status */
#define TM_TFO_NOT_ESTABLISHED    0x00 
#define TM_TFO_ESTABLISHED        0x01  

/* LLP APDU */


/*
 * Structures part for Traffic Management part
 */

typedef struct
{
    ITS_OCTET  timeSlotNum;
    ITS_OCTET  chanlBits;
}
TM_CHANNEL_NUMBER;

typedef struct
{
    ITS_OCTET    SAPI;
    ITS_OCTET    priority;
    ITS_OCTET    chanlBits;
    ITS_BOOLEAN  NA; 
}
TM_LINK_IDENTIFIER;

typedef struct
{
    ITS_OCTET  trasparent;
    ITS_OCTET  msgGruop;
}
TM_MSG_DESCRIMINATOR;

typedef struct
{
    TM_MSG_DESCRIMINATOR  msgDesc;
    ITS_OCTET             msgType;
}
GEN_ELEMENTS;

typedef struct
{
    TM_CHANNEL_NUMBER   chanlNum;
    TM_LINK_IDENTIFIER  linkId;
}
RLLM_GEN_ELEMENTS;

typedef struct
{
    TM_CHANNEL_NUMBER  chanlNum;
}
DCM_GEN_ELEMENTS;

typedef DCM_GEN_ELEMENTS CCM_GEN_ELEMENTS;

typedef struct
{
    ITS_USHORT  lengthInd; 
    ITS_OCTET   LLSDU[MAX_CONTENT_LENGTH];
}
TM_L3_INFORMATION;

/*
 * Radio Link Layer Managment(RLLM) messages
 *
 */

/* Data Request */
typedef struct
{
    TM_L3_INFORMATION  l3Info;
}
TM_RLLM_DATA_REQ;

/* Data Indication */
typedef TM_RLLM_DATA_REQ TM_RLLM_DATA_IND;

/* Error Indication */
typedef struct
{
    ITS_OCTET   rlmLen;
    ITS_USHORT  causeVal;
}
TM_RLLM_ERROR_IND;

/* Establish Request */
typedef struct
{
}
TM_RLLM_EST_REQ;

/* Establish Confirm */
typedef TM_RLLM_EST_REQ TM_RLLM_EST_CONF;

/* Establish Indication */
typedef struct
{
    ITS_OCTET          optionalBitMap; 
    TM_L3_INFORMATION  l3Info;
}
TM_RLLM_EST_IND;

/* Release Request */
typedef struct
{
    ITS_BOOLEAN  modeBit;
}
TM_RLLM_REL_REQ;

/* Release Confirm */
typedef TM_RLLM_EST_REQ TM_RLLM_REL_CONF;

/* Release Indication */
typedef TM_RLLM_EST_REQ TM_RLLM_REL_IND;

/* Unit Data Request */
typedef TM_RLLM_DATA_REQ TM_RLLM_UNIT_DATA_REQ;

/* Unit Data Indication */
typedef TM_RLLM_DATA_REQ TM_RLLM_UNIT_DATA_IND;



/*
 * Dedicated Channel Managment(DCM) messages
 *
 */

typedef struct
{
    ITS_OCTET    length; 
    ITS_BOOLEAN  dtxd;
    ITS_BOOLEAN  dtxu;  
    ITS_OCTET    indicator;
    ITS_OCTET    rateAndType;
    ITS_OCTET    codingAlg;
    ITS_OCTET    rate; /* optional fields */
    ITS_BOOLEAN  service;
}
TM_CHANNEL_MODE;

typedef struct
{
    ITS_OCTET  length;
    ITS_OCTET  descLen;
    ITS_OCTET  chanlDesc[MAX_OCTET_LENGTH];
    ITS_OCTET  allocLen; 
    ITS_OCTET  mobAlloc[MAX_OCTET_LENGTH];    
}
TM_CHANNEL_ID;

typedef struct
{
    ITS_OCTET  length;
    ITS_OCTET  algorithmId;
    ITS_OCTET  key[MAX_OCTET_LENGTH];
}
TM_ENCRYPTION_INFO;

typedef struct
{
    ITS_OCTET    powerLevel;
    ITS_BOOLEAN  FPC;   
}
TM_BS_POWER;

typedef TM_BS_POWER TM_MS_POWER; 

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  powerControl[MAX_OCTET_LENGTH]; /* coding is operator dependent */ 
}
TM_BS_POWER_PARAMS;

typedef TM_BS_POWER_PARAMS TM_MS_POWER_PARAMS;

typedef struct
{
    ITS_OCTET  length;
    ITS_OCTET  content[MAX_OCTET_LENGTH];
}
TM_PHYSICAL_CONTEXT;

typedef struct
{
    ITS_OCTET  typeOfMsg;
    ITS_OCTET  length; 
    ITS_OCTET  msg[MAX_OCTET_LENGTH];
}
TM_SACCH_MSG_INFO;

typedef struct
{
    ITS_OCTET          length;
    ITS_OCTET          numOfMsgs;
    TM_SACCH_MSG_INFO  *msgInfo; /* User has to allocate memory */   
}
TM_SACCH_INFO;

typedef TM_PHYSICAL_CONTEXT TM_MULTIRATE_CONFIG;

typedef struct
{
    ITS_BOOLEAN  TFO;
    ITS_BOOLEAN  PRE;
    ITS_OCTET    RAE;
}
TM_MULTIRATE_CONTROL;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  sysId;
    ITS_OCTET  codecList;
    ITS_OCTET  MACS[MAX_PARAM_LENGTH];  /* optional parameters */
    ITS_OCTET  TFO_VER[MAX_PARAM_LENGTH];
    ITS_OCTET  SCS[MAX_PARAM_LENGTH]; 
    ITS_OCTET  prefCodecType; 
}
TM_SUPP_CODEC_TYPES;
        
typedef struct
{
    ITS_USHORT  number;
}
TM_FRAME_NUMBER;

typedef struct
{
    ITS_OCTET   length; 
    ITS_USHORT  causeVal;
    ITS_OCTET   diagnostics[MAX_CONTENT_LENGTH];
}
TM_CAUSE;

typedef struct
{
    ITS_OCTET    length; 
    ITS_OCTET    rxlevFullUp;
    ITS_OCTET    rxlevSubUp;
    ITS_OCTET    rxqualFullUp;
    ITS_OCTET    rxqualSubUp;
    ITS_BOOLEAN  rfu;
    ITS_BOOLEAN  dtxd;
    ITS_OCTET    SMI[MAX_OCTET_LENGTH];
}
TM_UPLINK_MEAS;

typedef struct
{
    ITS_OCTET    powerLevel;
    ITS_OCTET    timingAdvns;
    ITS_BOOLEAN  FPC;
}
TM_L1_INFORMATION;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  codecType;
    ITS_OCTET  ICM;
    ITS_OCTET  codecSet;
}
TM_CODEC_CONFIG;

/* Channel Activation */
typedef struct
{
    ITS_OCTET             actType;
    ITS_BOOLEAN           procedure; /* 0 or non-zero */
    TM_CHANNEL_MODE       chnlMode;
    ITS_USHORT            optionalBitMap; 
    TM_CHANNEL_ID         chnlId;
    TM_ENCRYPTION_INFO    encryption;
    ITS_OCTET             handRef;
    TM_BS_POWER           bsPower; 
    TM_MS_POWER           msPower;
    ITS_OCTET             timingAdv;
    TM_BS_POWER_PARAMS    bsParams;
    TM_MS_POWER_PARAMS    msParams;
    TM_PHYSICAL_CONTEXT   phyContext;
    TM_SACCH_INFO         sacchInfo;
    ITS_OCTET             uicLen;
    ITS_OCTET             uicInfo;
    ITS_OCTET             mainChnlRefTn;
    TM_MULTIRATE_CONFIG   mrConfig;
    TM_MULTIRATE_CONTROL  mrControl;    
    TM_SUPP_CODEC_TYPES   codecTypes;
}
TM_DCM_CHAN_ACTIV;

/* Channel Activation Acknowledge */
typedef struct
{
    ITS_USHORT  frameNum;
}
TM_DCM_CHAN_ACTIV_ACK;

/* Channel Activation Negative Acknowledge */
typedef struct
{
    ITS_OCTET   length; 
    ITS_USHORT  causeVal;
    ITS_OCTET   diagnostics[MAX_CONTENT_LENGTH];
}
TM_DCM_CHAN_ACTIV_NACK;

/* Connection Failure Indication */
typedef TM_DCM_CHAN_ACTIV_NACK TM_DCM_CONN_FAIL_IND;

/* Deactive SACCH */

/* Encryption Command */
typedef struct
{
    TM_ENCRYPTION_INFO   encryption;    
    TM_LINK_IDENTIFIER   linkId;
    TM_L3_INFORMATION    l3Info; 
}
TM_DCM_ENCR_CMD;

/* Handover Detection */
typedef struct
{
    ITS_OCTET  optionalBitMap; 
    ITS_OCTET  accessDelay;
}
TM_DCM_HANDO_DET;

/* Measurement Result */
typedef struct
{
    ITS_OCTET          measResultNum;
    TM_UPLINK_MEAS     uplinkMeas;
    TM_BS_POWER        bsPower;
    ITS_OCTET          optionalBitMap;
    TM_L1_INFORMATION  l1Info;
    TM_L3_INFORMATION  l3Info;
    ITS_OCTET          timingOffset;
}
TM_DCM_MEAS_RES;

/* Mode Modify */
typedef struct
{
    TM_CHANNEL_MODE       chnlMode;           
    ITS_OCTET             optionalBitMap; 
    TM_ENCRYPTION_INFO    encryption;
    ITS_OCTET             mainChnlRefTn;
    TM_MULTIRATE_CONFIG   mrConfig;
    TM_MULTIRATE_CONTROL  mrControl;
    TM_SUPP_CODEC_TYPES   codecTypes;       
}
TM_DCM_MODE_MODIFY_REQ;

/* Mode Modify Acknowledge */

/* Mode Modify Negative Acknowledge */
typedef TM_DCM_CHAN_ACTIV_NACK TM_DCM_MODE_MODIFY_NACK; 

/* Physical Context Request */

/* Physical Context Confirm */
typedef struct
{
    ITS_OCTET            optionalBitMap;
    TM_BS_POWER          bsPower;
    TM_MS_POWER          msPower;
    ITS_OCTET            timingAdv;
    TM_PHYSICAL_CONTEXT  phyContext;
}
TM_DCM_PHY_CONTEXT_CONF;

/* RF Channel Release */

/* MS Power Control */
typedef struct
{
    ITS_OCTET          optionalBitMap;
    TM_MS_POWER        msPower;
    TM_MS_POWER_PARAMS msParams;     
}
TM_DCM_MSPOWER_CONTROL;

/* BS Power Control */
typedef struct
{
    ITS_OCTET          optionalBitMap;
    TM_BS_POWER        bsPower;
    TM_BS_POWER_PARAMS bsParams;    
}
TM_DCM_BSPOWER_CONTROL;

/* Preprocess Configure */
typedef struct 
{
    ITS_OCTET    length; 
    ITS_OCTET    processParam[MAX_OCTET_LENGTH]; /* coding is operator dependent */
    ITS_BOOLEAN  procedure;
}
TM_DCM_PREPROC_CONFIG; 

/* Preprocess Measurement Reesult */
typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  processMeas[MAX_OCTET_LENGTH]; /* coding is operator dependent */
}
TM_DCM_PREPOC_MEAS_RES;

/* RF Channel Release Acknowledge */

/* SACCH Info Modify */
typedef struct
{
    ITS_OCTET          optionalBitMap; 
    ITS_OCTET          sysInfoType;
    TM_L3_INFORMATION  l3Info;
    ITS_USHORT         startingTime;
}
TM_DCM_SACCH_INFO_MOD;

/* Talker Detection */
typedef TM_DCM_HANDO_DET TM_DCM_TALKER_DET;

/* Listener Detection */
typedef TM_DCM_HANDO_DET TM_DCM_LISTENER_DET;

/* Remote Codec Configured Report */
typedef struct
{
    TM_CODEC_CONFIG      config;                                                                                                 
    TM_SUPP_CODEC_TYPES  codecTypes;    
}
TM_DCM_REMOTE_CODEC_CONF_REP;

/* Round Trip Delay Report */
typedef struct
{
    ITS_OCTET    RTD;
    ITS_BOOLEAN  delay;
}
TM_DCM_RTD_REP; 

/* Pre-Handover Notification */
typedef struct
{
    TM_MULTIRATE_CONTROL mrControl;                                                                                                  
    TM_CODEC_CONFIG      config; 
}
TM_DCM_PRE_HANDO_NOTIF;

/* Multirate Codec Modification Request */
typedef struct
{
    ITS_OCTET            optionalBitMap; 
    TM_MULTIRATE_CONFIG  mrConfig;                                                                                                         
}
TM_DCM_MR_CODEC_MOD_REQ;

/* Multirate Codec Modification Acknolewdge */
typedef TM_DCM_MR_CODEC_MOD_REQ TM_DCM_MR_CODEC_MOD_ACK; 

/* Multirate Codec Modification Negative Acknolewdge */
typedef TM_DCM_CHAN_ACTIV_NACK TM_DCM_MR_CODEC_MOD_NACK; 

/*  Multirate Codec Modification Performed */
typedef TM_DCM_MR_CODEC_MOD_REQ TM_DCM_MR_CODEC_MOD_PER; 

/* TFO Report */
typedef struct
{
    ITS_BOOLEAN  tfoStatus;
}
TM_DCM_TFO_REP;

/* TFO Modification Request */
typedef struct
{
    ITS_OCTET            optionalBitMap;
    TM_MULTIRATE_CONTROL mrControl;                                        
    TM_SUPP_CODEC_TYPES  codecTypes;    
}
TM_DCM_TFO_MOD_REQ;


/*
 * Common Channel Managment(CCM) messages
 *
 */

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  msg[MAX_OCTET_LENGTH]; 
}
TM_FULL_BCCH_INFO;

typedef struct
{
    ITS_OCTET   length; 
    ITS_USHORT  slotCount;
    ITS_USHORT  busyCount;
    ITS_USHORT  accessCount;
    ITS_OCTET   info[MAX_OCTET_LENGTH];
}
TM_RACH_LOAD;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  identity[MAX_OCTET_LENGTH];
}
TM_MS_IDENTITY;
     
typedef struct
{
    ITS_OCTET    lastlock;
    ITS_OCTET    command;
    ITS_BOOLEAN  broadcast;
}
TM_CB_CMD_TYPE;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  msg[MAX_OCTET_LENGTH];
}
TM_SMSCB_MSG;

typedef struct
{
    ITS_OCTET  length; 
    ITS_USHORT cmdVal;
}
TM_COMMAND_IND;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  descGroup[MAX_OCTET_LENGTH];
}
TM_GROUP_CALL_REF;
 
typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  chanlDesc[MAX_OCTET_LENGTH];
}
TM_GROUP_CHANNEL_DESC;
 
typedef struct
{
    ITS_OCTET   length; 
    ITS_OCTET   NLN;
    ITS_OCTET   emlpp;
    ITS_BOOLEAN status;
}
TM_NCH_DRX_INFO;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  descr[MAX_OCTET_LENGTH]; 
}
TM_GROUP_CALL_DESCRIPTION;

/* BCCH Information */
typedef struct
{
    ITS_OCTET          optionalBitMap;
    ITS_OCTET          sysInfoType;
    TM_FULL_BCCH_INFO  fullBcch;
    ITS_USHORT         startingTime;
}
TM_CCM_BCCH_INFO;

/* CCCH Load Indication */
typedef struct
{
    TM_RACH_LOAD  rach;
    ITS_USHORT    pagBufSpace;
}
TM_CCM_CCCH_LOAD_IND;

/* Channel Required */
typedef struct
{
    ITS_OCTET            optionalBitMap;
    ITS_OCTET            RA;
    ITS_USHORT           reqRefNum;
    ITS_OCTET            accessDelay;
    TM_PHYSICAL_CONTEXT  phyContext;
}
TM_CCM_CHAN_RQD;

/* Delete Indication */
typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  assignInfo[MAX_OCTET_LENGTH];
}
TM_CCM_DELETE_IND;

/* Paging Command */
typedef struct
{
    ITS_OCTET       pagingGroup;
    TM_MS_IDENTITY  msIdentity;
    ITS_OCTET       optionalBitMap;
    ITS_OCTET       chanlNeed;
    ITS_OCTET       callPriority;
}
TM_CCM_PAGING_CMD;

/* Immediate Assign Command */
typedef TM_CCM_DELETE_IND TM_CCM_IMMEDIATE_ASSGN_CMD; 

/* SMS Broadcast required */
typedef struct
{
    ITS_OCTET  smscbInfoLen;
    ITS_OCTET  smscbInfo[MAX_OCTET_LENGTH];
    ITS_OCTET  optionalBitMap;
    ITS_OCTET  chanlInd;
}
TM_CCM_SMS_BC_REQ;

/* SMS Broadcast Command */
typedef struct
{
    TM_CB_CMD_TYPE cmdType;
    TM_SMSCB_MSG   smscbMsg;
    ITS_OCTET      optionalBitMap;
    ITS_OCTET      chanlInd;
}
TM_CCM_SMS_BC_CMD;

/* CBCH Load Indication */
typedef struct
{
    ITS_OCTET    slotCount;
    ITS_BOOLEAN  type;
    ITS_OCTET    optionalBitMap; 
    ITS_OCTET    chanlInd;
}
TM_CCM_CBCH_LOAD_IND;

/* Notification Command */
typedef struct
{
    TM_COMMAND_IND         cmdInd;
    ITS_OCTET              optionalBitMap;
    TM_GROUP_CALL_REF      callRef;
    TM_GROUP_CHANNEL_DESC  chanlDesc;
    TM_NCH_DRX_INFO        nchDrx;
}
TM_CCM_NOT_CMD;


/*
 * TRX Managment(TRXM) messages
 *
 */
typedef struct
{
    TM_CHANNEL_NUMBER  chanlNum;
    ITS_OCTET          interfBand;
}
TM_CORRESP_CHANNEL;
 
typedef struct
{
    ITS_OCTET  type;
}
TM_MESSAGE_ID;

typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  recvdMsg[MAX_OCTET_LENGTH]; 
}
TM_ERRONEOUS_MSG;

/* RF Resource Indication */
typedef struct
{
    ITS_OCTET           length; 
    TM_CORRESP_CHANNEL  info[MAX_OCTET_LENGTH];
}
TM_TRAX_RF_RES_IND;

/* SACCH Filling */
typedef struct
{
    ITS_OCTET          optionalBitMap;
    ITS_OCTET          sysInfoType;
    TM_L3_INFORMATION  l3Info;
    ITS_USHORT         startingTime;
}
TM_TRAX_SACCH_FILL;

/* Overload */
typedef struct
{
    ITS_OCTET   length;
    ITS_USHORT  causeVal;
    ITS_OCTET   diagnostics[MAX_CONTENT_LENGTH];
}
TM_TRAX_OVERLOAD;

/* Error Report */
typedef struct
{
    TM_CAUSE            cause;
    ITS_OCTET           optionalBitMap; 
    ITS_OCTET           msgId;
    TM_CHANNEL_NUMBER   chanlNum;
    TM_LINK_IDENTIFIER  linkId;
    TM_ERRONEOUS_MSG    errMsg;
}
TM_TRAX_ERROR_REPORT;

/*
 * Location Services(LCS) messages
 *
 */

/* Location Information */
typedef struct
{
    ITS_OCTET  length; 
    ITS_OCTET  facIEI[MAX_OCTET_LENGTH];
}
TM_LCS_LOC_INFO;

/* Radio Link Layer Management Message */
typedef struct
{
    /* ESTABLISH REQUEST, ESTABLISH CONFIRM, RELASE CONFIRM, 
     * RELASE INDICATION messages are same as RLLM_GEN_ELEMENTS */      
    RLLM_GEN_ELEMENTS rllmGenElements; 
    union
    {
        TM_RLLM_DATA_REQ       dataReq;
        TM_RLLM_DATA_IND       dataInd;
        TM_RLLM_ERROR_IND      errorInd;
        TM_RLLM_EST_REQ        estReq;
        TM_RLLM_EST_CONF       estConf;
        TM_RLLM_EST_IND        estInd;
        TM_RLLM_REL_REQ        relReq;
        TM_RLLM_REL_CONF       relConf;
        TM_RLLM_REL_IND        relInd; 
        TM_RLLM_UNIT_DATA_REQ  unitDataReq;
        TM_RLLM_UNIT_DATA_IND  unitDataInd; 
    }
    u;
}
RADIO_LINK_LAYER_MSG;

/* Dedicated Channel Management Message */
typedef struct
{
    /* DEACTIVE SAACH, MODE MODIFY ACKNOWLEDGE, PHYSICAL CONTEXT REQUEST, 
     * RF CHANNEL RELEASE, RF CHANNEL RELEASE ACKNOWLEDGE messages are same 
     * as DCM_GEN_ELEMENTS */      
    DCM_GEN_ELEMENTS dcmGenElements;
    union
    {
        TM_DCM_CHAN_ACTIV             chanActiv;
        TM_DCM_CHAN_ACTIV_ACK         chanActivAck;
        TM_DCM_CHAN_ACTIV_NACK        chanActivNack;
        TM_DCM_CONN_FAIL_IND          connFailInd;
        TM_DCM_ENCR_CMD               encrCmd;
        TM_DCM_HANDO_DET              handoDet;
        TM_DCM_MEAS_RES               measRes;
        TM_DCM_MODE_MODIFY_REQ        modeModifyReq;
        TM_DCM_MODE_MODIFY_NACK       modeModifyNack; 
        TM_DCM_PHY_CONTEXT_CONF       phyContextConf;
        TM_DCM_MSPOWER_CONTROL        mspowerControl;
        TM_DCM_BSPOWER_CONTROL        bspowerControl;
        TM_DCM_PREPROC_CONFIG         preprocConfig; 
        TM_DCM_PREPOC_MEAS_RES        prepocMeasRes;
        TM_DCM_SACCH_INFO_MOD         sacchInfoMod;
        TM_DCM_TALKER_DET             talkerDet;
        TM_DCM_LISTENER_DET           listenerDet;
        TM_DCM_REMOTE_CODEC_CONF_REP  remoteCodecConfRep;
        TM_DCM_RTD_REP                rtdRep; 
        TM_DCM_PRE_HANDO_NOTIF        preHandoNotif;
        TM_DCM_MR_CODEC_MOD_REQ       mrCodecModReq;
        TM_DCM_MR_CODEC_MOD_ACK       mrCodecModAck; 
        TM_DCM_MR_CODEC_MOD_NACK      mrCodecModNack;  
        TM_DCM_MR_CODEC_MOD_PER       mrCodecModPer; 
        TM_DCM_TFO_REP                tfoRep;
        TM_DCM_TFO_MOD_REQ            tfoModReq;
    }
    u; 
}
DEDICATED_CHANNEL_MSG;

/* Common Channel Management Message */
typedef struct
{
    CCM_GEN_ELEMENTS ccmGenElements;
    union
    {
        TM_CCM_BCCH_INFO            bcchInfo;
        TM_CCM_CCCH_LOAD_IND        ccchLoadInd; 
        TM_CCM_CHAN_RQD             chanRqd;
        TM_CCM_DELETE_IND           deleteInd;
        TM_CCM_PAGING_CMD           pagingCmd;
        TM_CCM_IMMEDIATE_ASSGN_CMD  immdAssignCmd;
        TM_CCM_SMS_BC_REQ           smsBcReq;
        TM_CCM_SMS_BC_CMD           smsBcCmd;
        TM_CCM_CBCH_LOAD_IND        cbchLoadInd;
        TM_CCM_NOT_CMD              notCmd;
    }
    u; 
}
COMMON_CHANNEL_MSG;

/* TRX Management Message */
typedef struct
{
    union
    {
        TM_TRAX_RF_RES_IND    rfResInd;
        TM_TRAX_SACCH_FILL    sacchFill;
        TM_TRAX_OVERLOAD      overload;
        TM_TRAX_ERROR_REPORT  errorReport;
    }
    u;
}
TRXM_MSG;

/* Location Service Message */
typedef struct
{
    union
    {
        TM_LCS_LOC_INFO   lcsLocInfo;
    }
    u;
}
LOCATION_SERVICE_MSG;

/* Complete Traffic Management Message Structure */
typedef struct
{
    GEN_ELEMENTS  genElemnts;
    union
    {
        RADIO_LINK_LAYER_MSG   rllmMsg;
        DEDICATED_CHANNEL_MSG  dcmMsg;
        COMMON_CHANNEL_MSG     ccmMsg;
        TRXM_MSG               trxmMsg;
        LOCATION_SERVICE_MSG   lcsMsg;
    }
    u;
}
ABIS_TRAFFIC_MANAGEMENT_MSG;

/* API Declaration part */
#ifdef __cplusplus
extern "C"
{
#endif
ITS_INT ABIS_TMM_Encode(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *length,
                        ITS_OCTET *buffer);

ITS_INT ABIS_TMM_Decode(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT bufLen,
                        ITS_OCTET *buffer);

#ifdef __cplusplus
}
#endif
#endif

