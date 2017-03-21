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
 *  ID: $Id: abis_network_management.h,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
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
 *  Revision 1.1.2.8  2006/12/29 05:32:48  sjaddu
 *  Done changes to Support TRX HELLO.
 *
 *  Revision 1.1.2.7  2006/08/11 09:40:37  sjaddu
 *  Modiifed during Integration Testing.
 *
 *  Revision 1.1.2.6  2006/05/15 11:00:58  gdevanand
 *  Added code for FILLER_TRX as object class as per IMR requirement (badri).
 *
 *  Revision 1.1.2.5  2006/04/07 09:29:45  yranade
 *  RF Max Power Reduction IE Added (sgavalkar)
 *
 *  Revision 1.1.2.4  2006/03/28 09:16:32  yranade
 *  TRX Hello message added. (sgavalkar)
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
                                                                                                                                              
#if !defined(ABIS_NMM_H)
#define ABIS_NMM_H

#include <abis_codec.h>

/*
 * This file contains Network Management Information Elements 
 * and Message structures used at the Abis interface.
 *
 * All the information referred by 3GPP TS 12.21 specification
 * unless specified 
 */

/* Message Categories */
#define NM_FORMATTED_OM_MSG                    0x80
#define NM_MMI_TRANSFER_MSG                    0x40
#define NM_TRAU_OM_MSG                         0x20
#define NM_MFD_OM_MSG                          0x10
 
/* Formatted O&M Messages */
#define NM_MSG_WITH_ONE_SEGMENT                0x80
#define NM_FIRST_SEGMENT_OF_MLTI_SEGMENT_MSG   0x40
#define NM_MIDDLE_SEGMENT_OF_MLTI_SEGMENT_MSG  0x20
#define NM_LAST_SEGMENT_OF_MLTI_SEGMENT_MSG    0x10

/* Message Type */ 
#define NM_LOAD_DATA_INTIATE                        0x01
#define NM_LOAD_DATA_INTIATE_ACK                    0x02
#define NM_LOAD_DATA_INTIATE_NACK                   0x03
#define NM_LOAD_DATA_SEGMENT                        0x04
#define NM_LOAD_DATA_SEGMENT_ACK                    0x05
#define NM_LOAD_DATA_ABORT                          0x06
#define NM_LOAD_DATA_END                            0x07
#define NM_LOAD_DATA_END_ACK                        0x08
#define NM_LOAD_DATA_END_NACK                       0x09
#define NM_SW_ACTIVATE_REQUEST                      0x0A
#define NM_SW_ACTIVATE_REQUEST_ACK                  0x0B
#define NM_SW_ACTIVATE_REQUEST_NACK                 0x0C
#define NM_ACTIVATE_SW                              0x0D
#define NM_ACTIVATE_SW_ACK                          0x0E
#define NM_ACTIVATE_SW_NACK                         0x0F
#define NM_SW_ACTIVATED_REPORT                      0x10
#define NM_ESTABLISH_TEI                            0x21
#define NM_ESTABLISH_TEI_ACK                        0x22
#define NM_ESTABLISH_TEI_NACK                       0x23
#define NM_CONNECT_TERRESTRIAL_SIGNALLING           0x24
#define NM_CONNECT_TERRESTRIAL_SIGNALLING_ACK       0x25
#define NM_CONNECT_TERRESTRIAL_SIGNALLING_NACK      0x26
#define NM_DISCONNECT_TERRESTRIAL_SIGNALLING        0x27
#define NM_DISCONNECT_TERRESTRIAL_SIGNALLING_ACK    0x28
#define NM_DISCONNECT_TERRESTRIAL_SIGNALLING_NACK   0x29
#define NM_CONNECT_TERRESTRIAL_TRAFFIC              0x2A
#define NM_CONNECT_TERRESTRIAL_TRAFFIC_ACK          0x2B
#define NM_CONNECT_TERRESTRIAL_TRAFFIC_NACK         0x2C
#define NM_DISCONNECT_TERRESTRIAL_TRAFFIC           0x2D
#define NM_DISCONNECT_TERRESTRIAL_TRAFFIC_ACK       0x2E
#define NM_DISCONNECT_TERRESTRIAL_TRAFFIC_NACK      0x2F
#define NM_CONNECT_MULTI_DROP_LINK                  0x31
#define NM_CONNECT_MULTI_DROP_LINK_ACK              0x32
#define NM_CONNECT_MULTI_DROP_LINK_NACK             0x33
#define NM_DISCONNECT_MULTI_DROP_LINK               0x34
#define NM_DISCONNECT_MULTI_DROP_LINK_ACK           0x35
#define NM_DISCONNECT_MULTI_DROP_LINK_NACK          0x36
#define NM_SET_BTS_ATTRIBUTES                       0x41
#define NM_SET_BTS_ATTRIBUTES_ACK                   0x42
#define NM_SET_BTS_ATTRIBUTES_NACK                  0x43
#define NM_SET_RADIO_CARRIER_ATTRIBUTES             0x44
#define NM_SET_RADIO_CARRIER_ATTRIBUTES_ACK         0x45
#define NM_SET_RADIO_CARRIER_ATTRIBUTES_NACK        0x46
#define NM_SET_CHANNEL_ATTRIBUTES                   0x47
#define NM_SET_CHANNEL_ATTRIBUTES_ACK               0x48
#define NM_SET_CHANNEL_ATTRIBUTES_NACK              0x49
#define NM_PERFORM_TEST                             0x51
#define NM_PERFORM_TEST_ACK                         0x52
#define NM_PERFORM_TEST_NACK                        0x53
#define NM_TEST_REPORT                              0x54
#define NM_SEND_TEST_REPORT                         0x55
#define NM_SEND_TEST_REPORT_ACK                     0x56
#define NM_SEND_TEST_REPORT_NACK                    0x57
#define NM_STOP_TEST                                0x58
#define NM_STOP_TEST_ACK                            0x59
#define NM_STOP_TEST_NACK                           0x5A
#define NM_STATE_CHANGED_EVENT_REPORT               0x61
#define NM_FAILURE_EVENT_REPORT                     0x62
#define NM_STOP_SENDING_EVENT_REPORTS               0x63
#define NM_STOP_SENDING_EVENT_REPORTS_ACK           0x64
#define NM_STOP_SENDING_EVENT_REPORTS_NACK          0x65
#define NM_RESTART_SENDING_EVENT_REPORTS            0x66
#define NM_RESTART_SENDING_EVENT_REPORTS_ACK        0x67
#define NM_RESTART_SENDING_EVENT_REPORTS_NACK       0x68
#define NM_CHANGE_ADMINISTRATIVE_STATE              0x69
#define NM_CHANGE_ADMINISTRATIVE_STATE_ACK          0x6A
#define NM_CHANGE_ADMINISTRATIVE_STATE_NACK         0x6B
#define NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST      0x6C
#define NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST_ACK  0x6D
#define NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST_NACK 0x6E
#define NM_REPORT_OUTSTANDING_ALARMS                0x93
#define NM_REPORT_OUTSTANDING_ALARMS_ACK            0x94
#define NM_REPORT_OUTSTANDING_ALARMS_NACK           0x95
#define NM_CHANGEOVER                               0x71
#define NM_CHANGEOVER_ACK                           0x72
#define NM_CHANGEOVER_NACK                          0x73
#define NM_OPSTART                                  0x74
#define NM_OPSTART_ACK                              0x75
#define NM_OPSTART_NACK                             0x76
#define NM_REINITIALIZE                             0x87
#define NM_REINITIALIZE_ACK                         0x88
#define NM_REINITIALIZE_NACK                        0x89
#define NM_SET_SITE_OUTPUTS                         0x77
#define NM_SET_SITE_OUTPUTS_ACK                     0x78
#define NM_SET_SITE_OUTPUTS_NACK                    0x79
#define NM_CHANGE_HW_CONFIGURATION                  0x90
#define NM_CHANGE_HW_CONFIGURATION_ACK              0x91
#define NM_CHANGE_HW_CONFIGURATION_NACK             0x92
#define NM_MEASUREMENT_RESULT_REQUEST               0x8A
#define NM_MEASUREMENT_RESULT_RESPONSE              0x8B
#define NM_STOP_MEASUREMENT                         0x8C
#define NM_START_MEASUREMENT                        0x8D
#define NM_GET_ATTRIBUTES                           0x81
#define NM_GET_ATTRIBUTES_RESPONSE                  0x82
#define NM_GET_ATTRIBUTES_NACK                      0x83
#define NM_SET_ALARM_THRESOLD                       0X84
#define NM_SET_ALARM_THRESHOLD_ACK                  0x85
#define NM_SET_ALARM_THRESHOLD_NACK                 0x86
#define NM_TRX_HELLO                                0xA0

/* Object Class */ 
#define NM_OC_SITE_MANAGER          0x00
#define NM_OC_BTS                   0x01
#define NM_OC_RADIO_CARRIER         0x02
#define NM_OC_BASEBAND_TRANSCEIVER  0x04
#define NM_OC_CHANNEL               0x03
#define NM_OC_NULL                  0xFF
/*
 * This is not in spec 3GPP TS 12.21 v 8.0.0 release 1999
 * This object class is added as per IMR requirement. 
 */
#define NM_OC_FILLER                0x05

/* Object Instance */ 

/* Attributes and Parameters */
#define NM_ABIS_CHANNEL                      0x01
#define NM_ADDITIONAL_INFO                   0x02
#define NM_ADDITIONAL_TEXT                   0x03
#define NM_ADMINISTRATIVE_STATE              0x04
#define NM_ARFCN_LIST                        0x05
#define NM_AUTONOMOUSLY_REPORT               0x06
#define NM_AVAILABLITY_STATUS                0x07
#define NM_BCCH_ARFCN                        0x08
#define NM_BSIC                              0x09
#define NM_BTS_AIR_TIMER                     0x0A
#define NM_CCCH_LOAD_INDICATION_PERIOD       0x0B
#define NM_CCCH_LOAD_THRESOLD                0x0C
#define NM_CHANNEL_COMBINATION               0x0D
#define NM_CONNECTION_FAILURE_CRITERION      0x0E
#define NM_DESTINATION                       0x0F
#define NM_EVENT_TYPE                        0x11
#define NM_FILE_DATA                         0x47
#define NM_FILE_ID                           0x12
#define NM_FILE_VERSION                      0x13
#define NM_GSM_TIME                          0x14
#define NM_GET_ATTRIBUTE_RESPONSE_INFO       0x44
#define NM_HSN                               0x15
#define NM_HW_CONFIGURATION                  0x16
#define NM_HW_CONF_CHANGE_INFO               0x45
#define NM_HW_DESCRIPTION                    0x17
#define NM_INTAVE_PARAMETER                  0x18
#define NM_INTERFERENCE_LEVEL_BOUNDARIES     0x19
#define NM_LIST_OF_REQUIRED_ATTRIBUTES       0x1A
#define NM_MAIO                              0x1B
#define NM_MANUFACTURE_DEPENDENT_STATE       0x1C
#define NM_MANUFACTURE_DEPENDENT_THRESHOLDS  0x1D
#define NM_MANUFACTURE_ID                    0x1E
#define NM_MAX_TIMING_ADVANCE                0x1F
#define NM_MULTI_DROP_BSC_LINK               0x20
#define NM_MULTI_DROP_NEXT_BTS_LINK          0x21
#define NM_NACK_CAUSES                       0x22
#define NM_NY1                               0x23
#define NM_OPERATIONAL_STATE                 0x24
#define NM_OUTSTANDING_ALARM_SEQUENCE        0x46
#define NM_OVERLOAD_PERIOD                   0x25
#define NM_PHYSICAL_CONFIG                   0x26
#define NM_POWER_CLASS                       0x27
#define NM_POWER_OUTPUT_THRESHOLDS           0x28
#define NM_PROBABLE_CAUSE                    0x29
#define NM_RACH_BUSY_THRESOLD                0x2A
#define NM_RACH_LOAD_AVERAGING_SLOTS         0x2B
#define NM_RADIO_SUB_CHANNEL                 0x2C
#define NM_RF_MAX_POWER_REDUCTION            0x2D
#define NM_SITE_INPUTS                       0x2E
#define NM_SITE_OUTPUTS                      0x2F
#define NM_SOURCE                            0x30
#define NM_SPECIFIC_PROBLEMS                 0x31
#define NM_STARTING_TIME                     0x32
#define NM_T200                              0x33
#define NM_TEI                               0x34
#define NM_TEST_DURATION                     0x35
#define NM_TEST_NO                           0x36
#define NM_TEST_REPORT_INFO                  0x37
#define NM_VSWR_THRESOLDS                    0x38
#define NM_WINDOW_SIZE                       0x39

#define NM_PAGING_AG_PARAMS                  0x4A//Added for Integration Testing with Real TRX

#define NM_SYST_INFO_LIST                    0x4B//Added for Integration Testing with Real TRX

#define NM_FN_OFFSET                         0x4C//Added for Integration Testing with Real TRX

#define NM_TSC                               0x40
#define NM_SW_CONFIGURATION                  0x41
#define NM_SW_DESCRIPTION                    0x42
#define NM_PERCEIVED_SEVERITY                0x43
#define NM_MEASUREMENT_RESULT                0x48
#define NM_MEASUREMENT_TYPE                  0x49
#define NM_ONM_PROT_VERSION                  0x4D //Added IMR custom AttrId (helloTRX)
#define NM_HW_CAPAB                          0x4E //Added IMR custom AttrId (helloTRX)

/* Abis Channel */ 
#define NM_AC_START_TIME_SLOT_NUM   0x00
#define NM_AC_END_TIME_SLOT_NUM     0x1F
#define NM_AC_SUBSLOT_NUM_A         0x00
#define NM_AC_SUBSLOT_NUM_B         0x01
#define NM_AC_SUBSLOT_NUM_C         0x02
#define NM_AC_SUBSLOT_NUM_D         0x03
#define NM_AC_SUBSLOT_NUM_64_KBPS   0xFF

/* Additional Info */ 

/* Additional Text */ 

/* Addministrative State */
#define NM_AS_LOCKED         0x01
#define NM_AS_UNLOCKED       0x02
#define NM_AS_SHUTTING_DOWN  0x03
#define NM_AS_NULL           0xFF

/* ARFCN List */
#define NM_AL_START_ARFCN_LIST  0x000
#define NM_AL_END_ARFCN_LIST    0x3FF

/* Autonomously Report */
#define NM_AR_AUTONOMOUSLY_REPOT      0x01
#define NM_AR_NOT_AUTONOMOUSLY_REPOT  0x00

/* Availability Status  */
#define NM_AS_IN_TEST        0x00
#define NM_AS_FAILED         0x01
#define NM_AS_POWER_OFF      0x02
#define NM_AS_OFF_LINE       0x03
#define NM_AS_NOT_USED       0x04
#define NM_AS_DEPENDENCY     0x05
#define NM_AS_DEGRADED       0x06
#define NM_AS_NOT_INSTALLED  0x07

/* BCCH ARFCN */
#define NM_BA_BCCH_START_ARFCN  0x001
#define NM_BA_BCCH_END_ARFCN    0x3FF

/* BSIC */
#define NM_BSIC_START    0x00
#define NM_BSIC_END      0x3F

/* BTS Air Timer */
#define NM_BTS_AT_START_T3105   0x00
#define NM_BTS_AT_END_T3105     0xFF

/* CCCH Load Indication Period */
#define NM_CLIP_START_LOAD_INDIACATION_PERIOD 0x00
#define NM_CLIP_END_LOAD_INDIACATION_PERIOD   0xFF

/* CCCH Load Threshold */
#define NM_CLT_START_LOAD_THRESHOLD 0x00
#define NM_CLT_END_LOAD_THRESHOLD   0x64

/* Channel Combination */
#define NM_CC_TCHFULL          0x00
#define NM_CC_TCHHALF          0x01
#define NM_CC_TCHHALF_2        0x02
#define NM_CC_SDCCH            0x03
#define NM_CC_MAIN_BCCH        0x04
#define NM_CC_BCCH_COMBINED    0x05
#define NM_CC_BCH              0x06
#define NM_CC_BCCH_WITH_CBCH   0x07
#define NM_CC_SDCCH_WITH_CBCH  0x08

/* Connection Failure Criterion */
#define NM_CFC_UPLINK_SACCH_ERROR_RATE    0x01
#define NM_CFC_RXLEV_RXQUAL_MEASUREMENTS  0x02

/* Destination  */

/* Event Type */
#define NM_ET_COMMUNICATION_FAILURE    0x00
#define NM_ET_QUALITY_SERVICE_FAILURE  0x01
#define NM_ET_PROCESSING_FAILURE       0x02
#define NM_ET_EQUIPMENT_FAILURE        0x03
#define NM_ET_ENVIRONMENT_FAILURE      0x04
#define NM_ET_START_MAN_DEP            0x10
#define NM_ET_END_MAN_DEP              0xFF

/* File Data  */

/* File Id */

/* File Version */

/* GSM Time */

/* HSN */
#define NM_HSN_START  0x00
#define NM_HSN_END    0x3F

/* HW Configuration */

/* HW Description */

/* Intave Parameter */
#define NM_IP_START_INTAVE_PARAM    0x01
#define NM_IP_END_INTAVE_PARAM      0x1F

/* Interference Level Boundaries */

/* List of Required Attributes */

/* MAIO */
#define NM_MAIO_START  0x00
#define NM_MAIO_END    0x3F

/* Manufactureer Dependent State */

/* Manufacturer Dependent Thresholds */

/* Manufacturer Id 
 * Reffered Spec : 3GPP TS  */

/* Max Timing Advance */
#define NM_MTA_START_MAX_TIMING_ADVANCE  0x00
#define NM_MTA_END_MAX_TIMING_ADVANCE    0x7F

/* Measurement Result */

/* Measurement Type */
#define NM_MT_START_MAN_DEP   0x40
#define NM_MT_END_MAN_DEP     0xFF

/* Multi-drop BSC Link */
#define NM_MBL_START_TIME_SLOT_2MBPS_LINK 0x00
#define NM_MBL_END_TIME_SLOT_2MBPS_LINK   0x1F

/* Multi-drop next BTS Link */
#define NM_MNBL_START_TIME_SLOT_2MBPS_LINK 0x00
#define NM_MNBL_END_TIME_SLOT_2MBPS_LINK   0x1F

/* Nack Causes */
#define NM_NC_INCORRECT_MSG_STRUCTURE               0x01
#define NM_NC_INVALID_MSG_TYPE_VALUE                0x02
#define NM_NC_INVALID_OBJECT_CALSS_VALUE            0x05
#define NM_NC_OBJECT_CLASS_NOT_SUPPORTED            0x06
#define NM_NC_BTS_NO_UNKNOWN                        0x07
#define NM_NC_BASEBAND_TRANCEIVER_NO_UNKNOWN        0x08
#define NM_NC_OBJECT_INSTANCE_UNKNOWN               0x09
#define NM_NC_INVALID_ATTRIBUTE_ID_VALUE            0x0C
#define NM_NC_ATTRIBUTE_ID_NOT_SUPPORTED            0x0D
#define NM_NC_PARAM_VAL_OUTSIDE_PERMITTED_RANGE     0x0E
#define NM_NC_INCONSISTENCY_IN_ATTRIBUTE_LIST       0x0F
#define NM_NC_SPECIFIED_IMPLEMENT_NOT_SUPPORTED     0x10
#define NM_NC_MSG_CANNOT_PERFORMED                  0x11
#define NM_NC_RESOURCE_NOT_IMPLEMENTED              0x19
#define NM_NC_RESOURCE_NOT_AVAILABLE                0x1A
#define NM_NC_FREQUENCY_NOT_AVAILABLE               0x1B
#define NM_NC_TEST_NOT_SUPPORTED                    0x1C
#define NM_NC_CAPACITY_RESTRICTIONS                 0x1D
#define NM_NC_PHYSICAL_CONFIG_CANNOT_PERFORM        0x1E
#define NM_NC_TEST_NOT_INITIATED                    0x1F
#define NM_NC_PHYSICAL_CONFIG_CANNOT_RESTORED       0x20
#define NM_NC_NO_SUCH_TEST                          0x21
#define NM_NC_TEST_CANNOT_STOPPED                   0x22
#define NM_NC_MSG_INCOSISTENCY_WITH_PHYSICAL_CONFIG 0x23
#define NM_NC_COMPLETE_FILE_NOT_RECEIVED            0x25
#define NM_NC_FILE_NOT_AVAILABLE_AT_DESTINATION     0x26
#define NM_NC_FILE_CANNOT_ACTIVATED                 0x27
#define NM_NC_REQUEST_NOT_GRANTED                   0x28
#define NM_NC_WAIT                                  0x29
#define NM_NC_NOTHING_REPORTABLE_EXISTING           0x2A
#define NM_NC_MEASUREMENT_NOT_SUPPORTED             0x2B
#define NM_NC_MEASUREMENT_NOT_STARTED               0x2C
#define NM_NC_START_MAN_DEP                         0x80
#define NM_NC_END_MAN_DEP                           0xFE
#define NM_NC_NULL                                  0xFF

/* Ny1 */

/* Operational State */
#define NM_OS_DISABLED  0x01
#define NM_OS_ENABLED   0x02
#define NM_OS_NULL      0xFF

/* Overload Period */

/* Physical Config */

/* Power Class */

/* Power Output Thresholds */
#define NM_POT_START_OPT  0x00
#define NM_POT_END_OPT    0x09
#define NM_POT_START_ROPT 0x00
#define NM_POT_END_ROPT   0x09
#define NM_POT_START_EOPT 0x00
#define NM_POT_END_EOPT   0x03

/* Probable Cause */
#define NM_PC_ISO_CCITT_VALUES     0x01
#define NM_PC_GSM_SPECIFIC_VALUES  0x02
#define NM_PC_MANUFACTURER_VALUES  0x03

/* RACH Busy Threshold */

/* RACH Load Averaging Slots */

/* Radio Sub Channel */
#define NM_RSC_HALF_RATE_CHANNEL_0  0x00
#define NM_RSC_HALF_RATE_CHANNEL_1  0x01

/* RF Max Power Reduction */

/* Site Inputs */

/* Site Outputs */

/* Source */

/* Specific Problems */
#define NM_SP_START_MAN_DEP   0x10
#define NM_SP_END_MAN_DEP     0xFF

/* Starting Time */

/* T200 */
#define NM_T200_NULL    0xFF

/* TEI */
#define NM_TEI_START_INTIAL     0x00
#define NM_TEI_END_INTIAL       0x3F
#define NM_TEI_START_ADDITIONAL 0x40
#define NM_TEI_END_ADDITIONAL   0x7E
#define NM_TEI_NOT_USED         0x7F

/* Test Duration */
#define NM_TD_START_DURATION   0x0001
#define NM_TD_END_DURATION     0xFFFF

/* Test No */
#define NM_TN_RADIO_LOOP_TEST_VIA_ANTENNA     0x00
#define NM_TN_RADIO_LOOP_TEST_VIA_TRANCEIVER  0x01
#define NM_TN_BTS_FUNCTIONAL_OBJECT_SELFTEST  0x02
#define NM_TN_START_MAN_DEP                   0x40
#define NM_TN_END_MAN_DEP                     0xFF

/* Test Report Info */

/* VSWR Thresholds */
#define NM_VSWR_START_FAULTY_ANTENNA       0x00
#define NM_VSWR_END_FAULTY_ANTENNA         0x12
#define NM_VSWR_START_ANTENNA_NOT_ADJUSTED 0x00
#define NM_VSWR_END_ANTENNA_NOT_ADJUSTED   0x12

/* Window Size */

/* TSC */
#define NM_TSC_START_VALUE   0x00
#define NM_TSC_END_VALUE     0x07

/* SW Configuration */

/* SW Description */

/* Perceived Severity */
#define NM_PS_FAILURE_CEASED         0x00
#define NM_PS_CRITICAL_FAILURE       0x01
#define NM_PS_MAJOR_FAILURE          0x02
#define NM_PS_MINOR_FAILURE          0x03
#define NM_PS_WARNING_LEVEL_FAILURE  0x04
#define NM_PS_INTERMEDIATE_FAILURE   0x05
#define NM_PS_START_MAN_DEP          0x40
#define NM_PS_END_MAN_DEP            0xFF

/* Get Attribute Response Info */

/* Outstanding Alarm Sequence */

/* HW Confg Change Info */
#define NM_HWCCI_DELETION      0x00
#define NM_HWCCI_INSERTION     0x01
#define NM_HWCCI_MODIFICATION  0x02
 
/*
 * Common structures
 */

typedef struct
{
    ITS_OCTET  btsNum;
    ITS_OCTET  baseBandNum;
    ITS_OCTET  timeSlotNum;
}
OBJECT_INSTANCE;

typedef struct
{
    ITS_OCTET        msgDesc;
    ITS_OCTET        placeInd;
    ITS_OCTET        seqNum;
    ITS_OCTET        lenInd;
    ITS_OCTET        msgType;                                                                                                                
    ITS_OCTET        objClass;                                                                                                            
    OBJECT_INSTANCE  objInst;
}
FORM_GEN_ELEMENTS;

/*
 * SW Download Management(SWDM) Messages
 *
 */

typedef struct
{
    ITS_USHORT  fileIdLen;
    ITS_OCTET   fileId[MAX_CONTENT_LENGTH];
    ITS_USHORT  fileVerLen; 
    ITS_OCTET   fileVer[MAX_CONTENT_LENGTH];
}
SW_DESCRIPTION;

typedef struct
{
    ITS_USHORT      length;
    SW_DESCRIPTION  *swDesc; /* user has to allocate memory */
}
SW_CONFIG;

typedef struct
{
    ITS_USHORT   equipIdLen;
    ITS_OCTET    equipId[MAX_CONTENT_LENGTH];
    ITS_USHORT   equipTypeLen;
    ITS_OCTET    equipType[MAX_CONTENT_LENGTH];
    ITS_USHORT   equipVerLen;
    ITS_OCTET    equipVer[MAX_CONTENT_LENGTH];
    ITS_USHORT   locLen;
    ITS_OCTET    location[MAX_CONTENT_LENGTH];
    ITS_USHORT   infoLen;
    ITS_OCTET    info[MAX_CONTENT_LENGTH];
}
HW_DESCRIPTION;

typedef struct
{
    ITS_USHORT      length;
    HW_DESCRIPTION  *hwDesc; /* user has to allocate memory */
}
HW_CONFIG;

/* Load Data Intiative */
typedef struct
{
    SW_DESCRIPTION  swDescr;
    ITS_OCTET       winSize; 
    ITS_OCTET       nackCuase;
}
NM_SWDM_LOAD_DATA_INIT;

/* Load Data Segment */
typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   data[MAX_CONTENT_LENGTH];
}
NM_SWDM_LOAD_DATA_SEG;

/* Load Data Abort */
typedef struct
{
}
NM_SWDM_LOAD_DATA_ABORT;

/* Load Data End */
typedef struct
{
    SW_DESCRIPTION  swDescr;
    ITS_OCTET       nackCuase;
}
NM_SWDM_LOAD_DATA_END;

/* SW Activate Request */
typedef struct
{
    ITS_OCTET   nackCuase;
    SW_CONFIG   swConfig;
    HW_CONFIG   hwConfig;
}
NM_SWDM_SW_ACTIVE_REQ;

/* Activate SW */
typedef struct
{
    ITS_OCTET       optionalBitMap;
    SW_DESCRIPTION  swDescr;
    ITS_OCTET       nackCuase;
}
NM_SWDM_ACTIVE_SW;

/* SW Activated Report */
typedef NM_SWDM_LOAD_DATA_ABORT NM_SWDM_SW_ACT_REPORT; 

/*
 * A-bis Interface Management(ABIM) Messages
 *
 */

typedef struct
{
    ITS_OCTET   btsPortNum;
    ITS_OCTET   timeSlotNum;
    ITS_OCTET   subSlotNum;
}
ABIS_CHANNEL;

/* Establish TEI */
typedef struct
{
    ITS_OCTET  teiVal;
    ITS_OCTET  nackCuase;
}
NM_ABIM_ESTABLISH_TEI;

/* Connect Terrestrial Signalling */
typedef struct
{ 
    ITS_OCTET  nackCuase;
}
NM_ABIM_CONN_TERR_SIG;

/* Disconnect Terrestrial Signalling */
typedef NM_ABIM_CONN_TERR_SIG NM_ABIM_DISCON_TERR_SIG; 

/* Connect Terrestrial Traffic */
typedef struct
{
    ITS_OCTET  optionalBitMap;
    ITS_OCTET  radioSubChanl;
    ITS_OCTET  nackCuase;
}
NM_ABIM_CONN_TERR_TRAFFIC;

/* Disconnect Terrestrial Traffic */
typedef NM_ABIM_CONN_TERR_TRAFFIC NM_ABIM_DISCON_TER_TRAFFIC; 

/*
 * Transmission Management(TRM) Messages
 *
 */

typedef struct
{
    ITS_OCTET   btsPortNum;
    ITS_OCTET   timeSlotNum;
}
MD_BSC_LINK;

typedef MD_BSC_LINK MD_NEXT_BTS_LINK;

/* Connect Multi-drop Link */
typedef struct
{
    MD_BSC_LINK        bscLink; 
    MD_NEXT_BTS_LINK   btsLink;     
    ITS_OCTET          nackCuase;
}
NM_TRM_CON_MULTI_DROP_LINK;

/* Disconnect Multi-drop Link */
typedef NM_TRM_CON_MULTI_DROP_LINK  NM_TRM_DISCON_MULTI_DROP_LINK;

/*
 * Air Interface Management(AIM) Messages
 *
 */
                                                                                                                                              
typedef struct
{
    ITS_OCTET   interfBound0;
    ITS_OCTET   interfBound1;
    ITS_OCTET   interfBound2;
    ITS_OCTET   interfBound3;
    ITS_OCTET   interfBound4;
    ITS_OCTET   interfBound5;  
}
INTER_LEVEL_BOUND;

typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   failCrit;
    ITS_OCTET   critVal[MAX_CONTENT_LENGTH];
}
CON_FAIL_CRITERION;

typedef struct
{
    ITS_OCTET   sdcch;
    ITS_OCTET   facchFull;
    ITS_OCTET   facchHalf;
    ITS_OCTET   sacchSap10;
    ITS_OCTET   sacchSdcch;   
    ITS_OCTET   sdcchSap13;
    ITS_OCTET   sacchSap13;
}
T200;

typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   period[MAX_CONTENT_LENGTH];
}
OVERLOAD_PERIOD;

typedef struct
{
    ITS_OCTET   tch;
    ITS_OCTET   sdcch;
}
AIR_T3105;
                                                                                
typedef struct
{
    ITS_OCTET   tch;
    ITS_OCTET   sdcch;
}
NY1;

typedef struct
{
    ITS_USHORT  length;
    ITS_USHORT  arfcn[MAX_CONTENT_LENGTH];
}
ARFCN_LIST;

typedef struct
{
    ITS_OCTET   bsPaMfrms;
    ITS_OCTET   bsCcchChans;
    ITS_OCTET   bsAgRes;
    ITS_OCTET   pageAlg;
}
PAGING_AG_PARAMS;
                                                                                
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   six[MAX_CONTENT_LENGTH];
}
SYST_INFO_LIST;

/* Set BTS Attributes */
typedef struct
{
    ITS_USHORT          optionalBitMap; 
    ITS_OCTET           optBitMap;
    INTER_LEVEL_BOUND   interLevel;
    ITS_OCTET           intaveParam;  
    CON_FAIL_CRITERION  conFail;
    T200                t200;
    ITS_OCTET           maxTimeAdv;
    OVERLOAD_PERIOD     overldPeriod;
    ITS_OCTET           threshold;
    ITS_OCTET           initPeriod;
    ITS_OCTET           busyThreshold;
    ITS_USHORT          avgSlots; 
    AIR_T3105           airT3105;
    NY1                 ny1;
    ITS_USHORT          arfcn;
    ITS_OCTET           bsic;
    ITS_OCTET           powerRedn;
    ITS_USHORT          startCurFrameNo;
    ITS_OCTET           nackCuase;
    PAGING_AG_PARAMS    pageAgParams;
    SYST_INFO_LIST      systInfoList;
    ITS_OCTET           fnOffset;
}
NM_AIM_SET_BTS_ATTR;

/* Set Radio Carrier Attributes */
typedef struct
{
    ITS_OCTET   optionalBitMap; 
    ITS_OCTET   powerRedu;
    ARFCN_LIST  arfcnList;
    ITS_OCTET   nackCuase;
}
NM_AIM_SET_RADIO_ATTR;

typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   maio[MAX_CONTENT_LENGTH];
}
MAIO_LIST;

/* Set Channel Attributes */
typedef struct
{
    ITS_OCTET   optionalBitMap; 
    ITS_OCTET   chanlComb;
    ITS_OCTET   hsn;
    MAIO_LIST   maioList;
    ARFCN_LIST  arfcnList;
    ITS_USHORT  startCurFrameNo;
    ITS_OCTET   tscSeqCode;
    ITS_OCTET   powerRedn;
    ITS_OCTET   nackCuase;
}
NM_AIM_SET_CHANNEL_ATTR;

/*
 * Test Management(TM) Messages
 *
 */

typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   testConfig[MAX_CONTENT_LENGTH]; /* Manufacturer dependent */
}
PHYSICAL_CONFIG;

/* Perform Test */
typedef struct
{
    ITS_OCTET        autoRep;
    ITS_USHORT       testDura;
    ITS_OCTET        optionalBitMap; 
    PHYSICAL_CONFIG  phyContext; 
    ITS_OCTET        nackCuase;
}
NM_TM_PERFORM_TEST;

/* Test Report */
typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   resultInfo[MAX_CONTENT_LENGTH];
}
NM_TM_TEST_REP;

/* Send Test Report */
typedef struct
{
    ITS_OCTET   nackCuase;
}
NM_TM_SEND_TEST_REP;

/* Stop Test */
typedef NM_TM_SEND_TEST_REP NM_TM_STOP_TEST;


/*
 * State Management and Event Report(SM) Messages
 *
 */

typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   status[MAX_CONTENT_LENGTH];
}
AVAILABILITY_STATUS;

typedef struct
{
    ITS_BOOLEAN  state;
    ITS_OCTET    input;
}
ATTRIBUTES;

typedef struct
{
    ITS_USHORT  length;
    ATTRIBUTES  attr[MAX_OCTET_LENGTH];
}
SITE_INPUTS;

typedef struct
{
    ITS_OCTET   type;
    ITS_USHORT  value;
}
PROBABLE_CAUSE;

typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   value[MAX_CONTENT_LENGTH];
}
ADDITIONAL_TEXT;

typedef ADDITIONAL_TEXT ADDITIONAL_INFO;

/* State Changed Event Report */
typedef struct
{
    ITS_OCTET            optionalBitMap; 
    ITS_OCTET            operanStat;
    AVAILABILITY_STATUS  availStat;
    ITS_OCTET            mfdDepen;
    SITE_INPUTS          siteInputs; 
}
NM_SM_STATE_CHNG_EVENT_REP;

/* Failure Event Report */
typedef struct
{
    ITS_OCTET        evtType;
    ITS_OCTET        percvdSever;
    PROBABLE_CAUSE   probCause; 
    ITS_OCTET        optionalBitMap; 
    ITS_OCTET        specProbs;
    HW_DESCRIPTION   hwDescr;
    SW_DESCRIPTION   swDescr;
    ADDITIONAL_TEXT  addText;
    ADDITIONAL_INFO  addInfo;
    ITS_OCTET        alarmSeq;
}
NM_SM_FAIL_EVENT_REP;

/* Stop Sending Event Reports */
typedef struct
{
    ITS_OCTET            optionalBitMap; 
    ITS_OCTET            operanStat;
    AVAILABILITY_STATUS  availStat;
    ITS_OCTET            mfdDepen;
    PROBABLE_CAUSE       probCause;
    ITS_OCTET            specProbs;
    ITS_OCTET            nackCuase;
}
NM_SM_STOP_SEND_EVENT_REP;

/* Restart Sending Event Reports */
typedef NM_SM_STOP_SEND_EVENT_REP NM_SM_RESTART_SEND_EVENT_REP; 

/* Change Administrative State */
typedef struct
{
    ITS_OCTET  adminStat;  
    ITS_OCTET  nackCuase;
}
NM_SM_CHNG_ADMIN_STATE;

/* Change Administrative State Request */
typedef NM_SM_CHNG_ADMIN_STATE NM_SM_CHNG_ADMIN_STATE_REQ; 

/* Report Outstanding Alarms */
typedef struct
{
    ITS_OCTET   nackCuase;
}
NM_SM_REP_OUTSTAND_ALARM;

typedef struct
{
    ITS_OCTET versionX;
    ITS_OCTET versionY;
}
ONM_PROTOCOL_VERSION;
                                                                                
typedef struct
{
    ITS_OCTET   freqHop;
    ITS_OCTET   diversity;
    ITS_OCTET   powClassSup;
    ITS_OCTET   freqBand;
    ITS_OCTET   lsclAvail;
    ITS_OCTET   memoryCapb;
}
HW_CAPABILITY;
                                                                                
/*    TRX Hello                  */
typedef struct
{
    ONM_PROTOCOL_VERSION   onmProtoVer;
    HW_CAPABILITY          hwCapab;
    SW_DESCRIPTION         swDesc;
    HW_DESCRIPTION         hwDesc;
    ITS_OCTET              optBitMap;
}
NM_SM_TRX_HELLO;

/*
 * Equipment Management(EM) Messages
 *
 */

typedef ADDITIONAL_TEXT SOURCE;

typedef ADDITIONAL_TEXT DESTINATION; 

/* Changeover */
typedef struct
{
    SOURCE       src;
    DESTINATION  dest;
    ITS_OCTET    nackCuase;
}
NM_EM_CHANGE_OVER;

/* Opstart */
typedef struct
{
    ITS_OCTET   nackCuase;
}
NM_EM_OPSTART;

/* Reinitialize */
typedef struct
{
    ITS_OCTET       optionalBitMap; 
    HW_DESCRIPTION  hwDesc;    
    ITS_OCTET       nackCuase;
}
NM_EM_REINITIALIZE;

/* Set Site Outputs */
typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   output[MAX_CONTENT_LENGTH];
    ITS_OCTET   nackCuase;
}
NM_EM_SET_SITE_OUTPUTS;

/* Change HW Configuration */
typedef NM_EM_SET_SITE_OUTPUTS NM_EM_CHNG_HW_CONFIG; 

/*
 * Measurment Management(MM) Messages
 *
 */


/* Measurement Result Request */
typedef struct
{
}
NM_MM_MEAS_RES_REQ;

/* Measurement Result Response */
typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   measResult[MAX_CONTENT_LENGTH]; 
}
NM_MM__MEAS_RES_RESP;

/* Start Measurment */
typedef NM_MM_MEAS_RES_REQ NM_MM_START_MEAS; 

/* Stop Measurement */
typedef NM_MM_MEAS_RES_REQ NM_MM_STOP_MEAS; 

/*
 * Miscellaneous(MS) Messages
 *
 */

typedef struct
{
    ITS_OCTET   fault;
    ITS_OCTET   reduced;
    ITS_OCTET   excessive;
}
POWER_OUTPUT_THRESHOLD;

typedef struct
{
    ITS_OCTET   faulty;
    ITS_OCTET   notAdjusted;
}
VSWR_THRESHOLD; 

typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   mfdDependnt[MAX_CONTENT_LENGTH];
}
MFD_THRESHOLDS;

/* Get Attributes */
typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   atrrId[MAX_CONTENT_LENGTH];
    ITS_OCTET   nackCuase;
}
NM_MS_GET_ATTR;

/* Set Alarm Threshold */
typedef struct
{
    PROBABLE_CAUSE          probCause;     
    ITS_OCTET               optionalBitMap;
    POWER_OUTPUT_THRESHOLD  powerOutput;
    VSWR_THRESHOLD          vswr;
    MFD_THRESHOLDS          mfdThresh;
    ITS_OCTET               nackCuase;
}
NM_MS_SET_ALARM_THRESHOLD;

/* Get Attribute Response */
typedef struct
{
    ITS_USHORT  length;
    ITS_OCTET   notRepCount;
    ITS_OCTET   notRep[MAX_CONTENT_LENGTH];
    ITS_OCTET   reported[MAX_CONTENT_LENGTH];
}
NM_MS_GET_ATTR_RESP;



/* SW Download Manangement Messages */ 
typedef struct
{
    /* LOAD DATA ABORT, SW ACTIVATED REPORT messages are same as
     * FORM_GEN_ELEMENTS. 
     */
    union
    {
        NM_SWDM_LOAD_DATA_INIT  loadInit; 
        NM_SWDM_LOAD_DATA_SEG   loadSeg;
        NM_SWDM_LOAD_DATA_END   loadEnd;
        NM_SWDM_SW_ACTIVE_REQ   actReq;
        NM_SWDM_ACTIVE_SW       actSw;   
    }
    u;
}
NM_SW_DOWNLOAD_MANAGEMENT_MSG;

/* A-bis Interface Manangement Messages */
typedef struct
{
    ABIS_CHANNEL       abisChanl;    
    union
    {
        NM_ABIM_ESTABLISH_TEI       estaTei;
        NM_ABIM_CONN_TERR_SIG       connTerr;
        NM_ABIM_DISCON_TERR_SIG     disconTerr;
        NM_ABIM_CONN_TERR_TRAFFIC   connTraf;
        NM_ABIM_DISCON_TER_TRAFFIC  disconTraf;
    }
    u;                                                                                                                               
}
NM_ABIS_INTERFACE_MANAGEMENT_MSG;

/* Transmission Manangement Messages */
typedef struct
{
    union
    {
        NM_TRM_CON_MULTI_DROP_LINK     conLink;
        NM_TRM_DISCON_MULTI_DROP_LINK  disconLink;
    }
    u;                                                                                                                                        
}
NM_TRASMISSION_MANAGEMENT_MSG;

/* Air Interface Manangement Messages */
typedef struct
{
    union
    {
        NM_AIM_SET_BTS_ATTR      btsAttr;
        NM_AIM_SET_RADIO_ATTR    radioAttr;
        NM_AIM_SET_CHANNEL_ATTR  chanlAttr;
    }
    u;                                                                                                                              
}
NM_AIR_INTERFACE_MANAGEMENT_MSG;

/* Test Manangement Messages */ 
typedef struct
{
    ITS_OCTET  testNum;
    union
    {
        NM_TM_PERFORM_TEST   perfTest;
        NM_TM_TEST_REP       testRep; 
        NM_TM_SEND_TEST_REP  sendRep;
        NM_TM_STOP_TEST      stopTest;
    }
    u;                                                                                                                            
}
NM_TEST_MANAGEMENT_MSG;

/* State Manangement and Event Report Messages */
typedef struct
{
    union
    {
        NM_SM_STATE_CHNG_EVENT_REP    changeEv;
        NM_SM_FAIL_EVENT_REP          failEv;
        NM_SM_STOP_SEND_EVENT_REP     stopEv;
        NM_SM_RESTART_SEND_EVENT_REP  restartEv;
        NM_SM_CHNG_ADMIN_STATE        state;
        NM_SM_CHNG_ADMIN_STATE_REQ    stateReq;
        NM_SM_REP_OUTSTAND_ALARM      repAlarm;
        NM_SM_TRX_HELLO               trxHello;
    }
    u;                                                                                                                                       
}
NM_STATE_MANAGEMENT_MSG;

/* Equipment Manangement Messages */
typedef struct
{
    union
    {
        NM_EM_CHANGE_OVER       changeOver;
        NM_EM_OPSTART           opStart;
        NM_EM_REINITIALIZE      reInit;
        NM_EM_SET_SITE_OUTPUTS  siteOutput;
        NM_EM_CHNG_HW_CONFIG    hwConfig;
    }
    u;                                                                                                                                
}
NM_EQUIPMENT_MANAGEMENT_MSG;

/* Measurement Manangement Messages */
typedef struct
{
    ITS_OCTET  measId;
    union
    {
        NM_MM_MEAS_RES_REQ    measReq;
        NM_MM__MEAS_RES_RESP  measResp;
        NM_MM_START_MEAS      startMeas;
        NM_MM_STOP_MEAS       stopMeas;
    }
    u;                                                                                                                                 
}
NM_MEASUREMENT_MANAGEMENT_MSG;

/* Miscellaneous Messages */
typedef struct
{
    union
    {
        NM_MS_GET_ATTR             getAttr;
        NM_MS_SET_ALARM_THRESHOLD  alarmThresh;
        NM_MS_GET_ATTR_RESP        getAttrResp;
    }
    u; 
}
NM_MISCELLANEOUS_MANAGEMENT_MSG;

/* Formatted O&M Messages */
typedef struct
{
    FORM_GEN_ELEMENTS     formGenElemnts;
    union
    {
        NM_SW_DOWNLOAD_MANAGEMENT_MSG     swdmMsg;
        NM_ABIS_INTERFACE_MANAGEMENT_MSG  abisMsg;
        NM_TRASMISSION_MANAGEMENT_MSG     transMsg;
        NM_AIR_INTERFACE_MANAGEMENT_MSG   airMsg;
        NM_TEST_MANAGEMENT_MSG            testMsg;
        NM_STATE_MANAGEMENT_MSG           stateMsg;
        NM_EQUIPMENT_MANAGEMENT_MSG       equipMsg;
        NM_MEASUREMENT_MANAGEMENT_MSG     measMsg;
        NM_MISCELLANEOUS_MANAGEMENT_MSG   miscMsg;
    }
    u;
}
NM_FORMATTED_OM_MSGS;

/* MMI Transfer */
typedef struct
{
    /* future purpose */
}
NM_MMI_TRANSFER;

/* TRAU O&M Messages */
typedef struct
{
    /* future purpose */
}
NM_TRAU_OM_MSGS;

/* Manufactured-Defined O&M Messages */
typedef struct
{
    /* future purpose */
}
NM_MFD_OM_MSGS;

/* Network Management Messages */
typedef struct
{
    union
    {
        NM_FORMATTED_OM_MSGS  formMsg;
        NM_MMI_TRANSFER       mmiTrans;
        NM_TRAU_OM_MSGS       trauMsg;
        NM_MFD_OM_MSGS        mfdMsg;
    }
    u;
}
ABIS_NETWORK_MANAGEMENT_MSG;

/* API Declaration part */
#ifdef __cplusplus
extern "C"
{
#endif
ITS_INT ABIS_NMM_Encode(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *length,
                        ITS_OCTET *buffer);
                                                                                                                                              
ITS_INT ABIS_NMM_Decode(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT bufLen,
                        ITS_OCTET *buffer);

#ifdef __cplusplus
}
#endif
#endif
