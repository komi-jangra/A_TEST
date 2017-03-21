/****************************************************************************
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
 *  ID: $Id: isup.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:35  hbalimid
 * LOG: Get here for demo isup
 * LOG:
 * LOG: Revision 5.13.2.2  2002/04/04 21:39:21  ssanyal
 * LOG: Adding new msg ISUP_MSG_FAC for ANSI95: also, ANSI specific timers are transfered from isup_cmn.h to this file.
 * LOG:
 * LOG: Revision 5.13.2.1  2002/03/01 15:42:08  ssharma
 * LOG: Conflicting signatures.
 * LOG:
 * LOG: Revision 5.13  2002/02/26 23:54:59  ssharma
 * LOG: Add timer and error indications to stack.
 * LOG:
 * LOG: Revision 5.12  2002/02/13 21:21:25  mmiers
 * LOG: Finish up ISUP integration
 * LOG:
 * LOG: Revision 5.11  2002/02/13 18:27:44  mmiers
 * LOG: Finish off the ISUP integration.
 * LOG:
 * LOG: Revision 5.10  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 * LOG: Revision 5.9  2002/02/01 21:17:03  mmiers
 * LOG: Porting.
 * LOG:
 * LOG: Revision 5.8  2002/02/01 21:00:09  mmiers
 * LOG: Use explicit types.
 * LOG:
 * LOG: Revision 5.7  2002/02/01 20:05:56  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.6  2002/01/02 19:55:46  mmiers
 * LOG: Convert to long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:34  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 00:39:53  mmiers
 * LOG: Split the signatures out.  Tomorrow we split out the #defines.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/05/16 22:47:43  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:24  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/11/10 18:06:41  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.2  1999/10/27 15:45:21  mmiers
 * LOG:
 * LOG:
 * LOG: Get the headers in here.
 * LOG:
 * LOG: Revision 1.1  1998/11/18 18:39:48  mmiers
 * LOG: Start thinking about ANSI ISUP.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_ISUP_ANSI_H_
#define _ITS_ISUP_ANSI_H_

#include <its.h>
#include <its_callback.h>

#ident "$Id: isup.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

#include <ansi/mtp3.h>
#include <ansi/sccp.h>

#define ANSI_ISUP

#include <isup_cmn.h>
#include <isup_sn.h>

#ifdef __cplusplus
extern "C"
{
#endif


/*
 ****************************************************************************
 * Message Types Codes (common section, followed by ANSI then
 *                      ITU specific parameters).
 *
 * ANSI Ref: T1.113-1992. page T1.113.3-49.
 * Sec 4.1; Table 3 and 3A/T1.113.3.
 *
 * The Message Type code consists of a one octet field and is mandatory
 * for all messages. The message type code uniquely defines the function
 * and the formet of each ISDN User Part message.
 * All acronyms (last 3/4 letters) are taken from
 * Table 2/Q.762 (03/93), page 14.
 * NOTE: All message types are not supported by the board manufacturer.
 ****************************************************************************/

#define ISUP_MSG_CRM    0xEA    /* Circuit Reservation */
#define ISUP_MSG_CRA    0xE9    /* Circuit Reservation Acknowledgement */
#define ISUP_MSG_CVR    0xEB    /* Circuit Validation Response */
#define ISUP_MSG_CVT    0xEC    /* Circuit Validation Test */
#define ISUP_MSG_EXM    0xED    /* Exit Message */

/*
 ****************************************************************************
 * Parameter Names and Identifiers (common section, followed by ANSI
 *                                  then ITU specific parameters).
 *
 * ANSI Ref: T1.113-1992. page T1.113.3-52.
 * Sec 4.1; Table 4 and 4A/T1.113.3.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/
#define ISUP_PRM_SERVICE_ACTIVATION_ANSI        0xE2

/*
 ****************************************************************************
 * Parameter Names and Identifiers (ANSI specific parameter Names).
 *
 * ANSI Ref: T1.113-1992. page T1.113.3-52.
 * Sec 4.1; Table 4 and 4A/T1.113.3.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/
#define ISUP_PRM_BUSINESS_GROUP                 0xC6
#define ISUP_PRM_CARRIER_ID                     0xC5
#define ISUP_PRM_CARRIER_SELECTION_INFO         0xEE
#define ISUP_PRM_CHARGE_NUMBER                  0xEB
#define ISUP_PRM_CKT_VALIDATION_RESP            0xE6
#define ISUP_PRM_CKT_GRP_CHARACTERISTIC         0xE5
#define ISUP_PRM_CKT_IDENTIFICATION_NAME        0xE8
#define ISUP_PRM_CLLI_CODE                      0xE9
#define ISUP_PRM_EGRESS_SERVICE                 0xC3
#define ISUP_PRM_GENERIC_ADDR                   0xC0
#define ISUP_PRM_JURISDICTION                   0xC4
#define ISUP_PRM_NTWK_TRANSPORT                 0xEF
#define ISUP_PRM_NOTIFICATION                   0xE1
#define ISUP_PRM_ORIG_LINE_INFO                 0xEA
#define ISUP_PRM_OUTGOING_TRUNK_GRP_NUM         0xE7
#define ISUP_PRM_SERVICE_CODE                   0xEC
#define ISUP_PRM_SPECIAL_PROCESS_REQUEST        0xED
#define ISUP_PRM_TRANSACTION_REQUEST            0xE3



/*
 ****************************************************************************
 * Parameter Definitions in the form of structures.(common section, 
 *                       followed by ANSI then ITU specific parameters).
 *
 * ANSI Ref: T1.113-1992.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/


/*
 ****************************************************************************
 * Backward Call Indicators.
 *
 * ANSI Ref: sec 3.3 (Figure 5/T1.113.3), page T1.113.3-3.
 ****************************************************************************/

/* Bits D & C: Called Party's Status Indicator. */
#define BKWD_EXCESSIVE_DELAY    0x03

/* Bit J: End-to-end Information Indicator */
#define BKWD_ADITNL_INFO_RVCD   0x01


/*
 ****************************************************************************
 * Called Party Number.
 *
 * ANSI Ref: sec 3.6 (Figure 8/T1.113.3), page T1.113.3-5.
 ****************************************************************************/

/* The other 7 bits of the octet 'addr_ind' represent the */
/* Nature of Address Indicator, as defined below */
#define CDPN_SPARE_RESERVED     0x02
/* 0x05-> 0x70, 0x78 -> 0xFF: Spare/Reserved */
#define CDPN_SUB_NUM_OPERATOR    0x71
#define CDPN_NATL_NUM_OPERATOR   0x72
#define CDPN_INTL_NUM_OPERATOR   0x73
#define CDPN_NO_NUM_OPERATOR     0x74
#define CDPN_NO_NUM_CUT_THROUGH  0x75
#define CDPN_950_CALL            0x76
#define CDPN_TEST_LINE_TEST_CODE 0x77

/*
 * The MSB of the octet 'num_plan' represents the Internal Network Number
 * Indicator (INN ind) (CCITT only, Spare for ANSI).
 */

/*
 * Bits 7->5 of the octet 'num_plan' represent the  Numbering Plan Indicator,
 * Bits 4->1 are reserved (ANSI) or spare (CCITT).
 */
#define CDPN_UNKNOWN_ANSI            0x00
#define CDPN_PRIVATE                 0x05
#define CDPN_RESERVED_NATL           0x06


/* Nature of Address Indicator */
#define CGPN_SPARE_NATL_USE         0x02
#define CGPN_NON_UNIQUE_SUB_NUM     0x71
#define CGPN_SPARE_NATL_USE1        0x72
#define CGPN_NON_UNIQUE_NATL_NUM    0x73
#define CGPN_NON_UNIQUE_INTL_NUM    0x74
#define CGPN_TEST_LINE_CODE         0x77

/*
 ****************************************************************************
 * Cause Indicator.
 *
 * ANSI Ref: sec 3.9 (Figure 10 and 10A/T1.113.3), page T1.113.3-8.
 ****************************************************************************/

#define CI_LOC_INTERFACE        0x06
#define CI_LOC_UNKNOWN          0x0A

/* cause values, as per Q.850, Table 1 */
#define CI_CAUSE_UNALLOCATED_DEST_NUM        23
#define CI_CAUSE_UNKWN_BUSINESS_GROUP        24

#define CI_CAUSE_PREEMPTION                 45
#define CI_CAUSE_PRECEDENCE_CALL_BLOCK        46

#define CI_CAUSE_CALL_TYPE_INCOMPATIBLE          51
#define CI_CAUSE_OUTGOING_CALL_BARRED_IN_CUG    53
#define CI_CAUSE_CALL_BLCKD_GRP_RESTRICTIONS    54

/*
 ****************************************************************************
 * Circuit State Indicator.
 *
 * ANSI Ref: sec 3.11B (Figure 11B/T1.113.3), page T1.113.3-13.
 ***************************************************************************/

#define CKTS_IN_CTK_BUSY_ACTIVE     0x04
#define CKTS_IN_CTK_BUSY_LBLOCKED   0x05
#define CKTS_IN_CTK_BUSY_RBLOCKED   0x06
#define CKTS_IN_CTK_BUSY_LRBLOCKED  0x07
#define CKTS_OUT_CTK_BUSY_ACTIVE    0x08
#define CKTS_OUT_CTK_BUSY_LBLOCKED  0x09
#define CKTS_OUT_CTK_BUSY_RBLOCKED  0x0A
#define CKTS_OUT_CTK_BUSY_LRBLOCKED 0x0B
#define CKTS_IDLE                   0x0C
#define CKTS_IDLE_LBLOCKED          0x0D
#define CKTS_IDLE_RBLOCKED          0x0E
#define CKTS_IDLE_LRBLOCKED         0x0F
/* other values: Spare. */


/*
 ****************************************************************************
 * Circuit group supervision message type indicator.
 *
 * ANSI Ref: sec 3.11 (Figure 11/T1.113.3), page T1.113.3-12.
 ****************************************************************************/

#define BLOCK_WO_RELEASE        0x00
#define BLOCK_W_IMDIAT_RELEASE  0x01


/*
 ****************************************************************************
 * Event Info Indicator 
 *
 * ANSI Ref: sec 3.17A (Figure 15B/T1.113.3), page T1.113.3-14.
 ****************************************************************************/

/* The rest of the 7 bits can be coded as one of the following: */
#define EI_NOTIFICATION_SUP_SER 0x08
#define EI_SERVICE_INFO_INCL    0xDF


/*
 ****************************************************************************
 * Forward Call Indicators.
 *
 * ANSI Ref: sec 3.20 (Figure 18/T1.113.3), page T1.113.3-15.
 ****************************************************************************/

/* Bit E: IAM segmentation indicator (ANSI) */
#define FWD_IAM_SEG_NO_INDICATION   0x00
#define FWD_IAM_SEG_ADITNL_INF      0x01


/*
 ****************************************************************************
 * Information Indicators.
 *
 * ANSI Ref: sec 3.22 (Figure 20/T1.113.3), page T1.113.3-17.
 ****************************************************************************/

/* Bit H: Solicited information indicator */

/* Bit P: Multi-location business group information response indicator */
#define INFOI_MULTI_LOC_BUS_GRP_NOT_PROVIDED  0x00
#define INFOI_MULTI_LOC_BUS_GRP_INCLUDED      0x01

/*
 ****************************************************************************
 * Information Request Indicators.
 *
 * ANSI Ref: sec 3.24C (Figure 22C/T1.113.3), page T1.113.3-19.
 ****************************************************************************/


/* Bit P: Multi-location Business Group Information indicator  */
#define INFO_REQ_BUG_GRP_INFO_NOT_REQUESTED 0x00 
#define INFO_REQ_BUG_GRP_INFO_REQUESTED     0x01


/*
 ****************************************************************************
 * Nature Of Connection Indicators.
 *
 * ANSI Ref: sec 3.24 (Figure 22/T1.113.3), page T1.113.3-18.
 ****************************************************************************/
#define NCI_THREE_SATELLITE_CKT 0x03


/*
 ****************************************************************************
 *  Optional Backward Call Indicators.
 *
 * ANSI Ref: sec 3.24C (Figure 22C/T1.113.3), page T1.113.3-19.
 ****************************************************************************/

/* Bit B: Call Forwarding may occur Indicator. */
#define OBKWD_NO_CALL_FORWARD         0x00
#define OBKWD_CALL_FORWARD_MAY_OCCUR  0x01

/* Bit H: User-Network interaction indicator */
#define OBKWD_USER_NTWRK_NO_IND         0x00
#define OBKWD_USER_NTWRK_CUT_THROUGH    0x01



/*
 ****************************************************************************
 * Service Activation.
 *
 * ANSI Ref: sec 3.29B (Figure 25C/T1.113.3), page T1.113.3-21.
 ****************************************************************************/

/* no data defined for CCITT and ANSI, except the following for ANSI */
#define CALL_WAITING_INVOKED        0x7C
#define DIAL_CALL_WAITING_INVOKED   0x7D
#define ISDN_ALL_THE_WAY            0x7E
#define ISDN_NOT_ALL_THE_WAY        0x7F



/* network id plan for national net id. */
#define TNS_3_DIGITS_CARRIER_ID        0x01
#define TNS_4_DIGITS_CARRIER_ID        0x01

/* Circuit Code */
#define TSN_UNSPECIFIED             0x00
#define TSN_INTNL_CALL_NO_OPERATOR  0x01
#define TSN_INTNL_CALL_OPERATOR     0x02
/* other values: reserved */


/*
 * OCTET 1: Coding Standard (bits 7,6)
 * and Information transfer capability (bits 5->1)
 */
#define USI_AUDIO_7KHZ      0x11


/* OCTET 2.1 (ANSI): 0->1 and 31 -> 127 reserved. */

/* OCTET 3: User information layer 1 protocol (bits 5->1). */
#define USI_CCITT_G722_G725     0x05

#define USI_R_7200BITS_I460     0x06
#define USI_R_8KBITS_V6         0x07
#define USI_R_64KBITS_X1        0x10

#define USI_NEGOTIATION_N_APPLICABLE    0x00

/* OCTET 4: User information layer 3 protocol.*/
#define USI_REC_Q931_ANSI_T1_607    0x02


/*
 ****************************************************************************
 * Parameter Definitions in the form of structures.(ANSI specific parameters).
 *
 * ANSI Ref: T1.113-1992.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/

/*
 ****************************************************************************
 * Business group.
 *
 * ANSI Ref: sec 3.3A (Figure 5A/T1.113.3), page T1.113.3-3.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET party_selector;
    ITS_OCTET business_group_ident[3];
    ITS_OCTET sub_group_ident[2];
    ITS_OCTET line_privileges;
}
ISUP_BUSINESS_GROUP;

/* Business group attendant status: no indication, attendant line */
#define BUS_GRP_ATTENDANT_STAT_NO   0x00
#define BUS_GRP_ATTENDANT_STAT_LINE 0x01

/* Business group identifier status: multi_location, interworking */
#define BUS_GRP_IDENT_STAT_MULTI_LOCATION   0x00
#define BUS_GRP_IDENT_STAT_INTERWORKING     0x01

/* Business group line privileges info: fixed, customer */
#define BUS_GRP_LINE_PRIVILEG_INFO_FIXED   0x00
#define BUS_GRP_LINE_PRIVILEG_INFO_CUST    0x01

/* Business group party selector: No indication -> Original Called Number */
#define BUS_GRP_PARTY_SEL_NO        0x00
#define BUS_GRP_PARTY_SEL_CG_NB     0x01
#define BUS_GRP_PARTY_SEL_CD_NB     0x02
#define BUS_GRP_PARTY_SEL_CONN_NB   0x03
#define BUS_GRP_PARTY_SEL_REDIR_NB  0x04
#define BUS_GRP_PARTY_SEL_ORIG_NB   0x05

/*
 * Business group line privileges: unrestricted -> denied then spare.
 * or Customer defined (if line privileges info = 1.
 */
#define BUS_GRP_LINE_PRIVILEG_UN_R              0x00
#define BUS_GRP_LINE_PRIVILEG_SEMI_R            0x01
#define BUS_GRP_LINE_PRIVILEG_FULLY_R           0x02
#define BUS_GRP_LINE_PRIVILEG_FULLY_R_INTRA_SW  0x03
#define BUS_GRP_LINE_PRIVILEG_DENIED            0x04


/*
 ****************************************************************************
 * Carrier Identification.
 *
 * ANSI Ref: sec 3.8A(Figure 9A 9B/T1.113.3), page T1.113.3-8.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   network;
    ITS_OCTET   digit2and1;
    ITS_OCTET   digit4and3;
}
ISUP_CARRIER_IDENTIFICATION;

/* network: type of network id, network id plan */
#define CID_NATL_NTWRK_ID   0x2
/* other values spare */

#define CID_UNKNOWN     0x00
#define CID_3_DIGITS    0x01
#define CID_4_DIGITS    0x02
/* other values spare */


/*
 ****************************************************************************
 * Carrier Selection Information.
 *
 * ANSI Ref: sec 3.8B(Figure 9C/T1.113.3), page T1.113.3-8.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   information;
}
ISUP_CARRIER_SELECTION_INFO;

#define CSINFO_PRE_SUB_NO_INDICATION       0x00
#define CSINFO_PRE_SUB_NOT_INPUT_CGPA      0x01
#define CSINFO_PRE_SUB_INPUT_CGPA          0x02
#define CSINFO_PRE_SUB_INPUT_UNDETERMINED  0x03
#define CSINFO_NOT_PRE_SUB_INPUT_CGPA      0x04
/* 0x05 -> 0xEF: Spare */
#define CSINFO_PRE_SUB_RESERVED            0xFF


/*
 ****************************************************************************
 * Charge Number.
 *
 * ANSI Ref: sec 3.10(Figure 10B/T1.113.3), page T1.113.3-11.
 *
 * Note: see called Party Number.
 ****************************************************************************/
typedef ISUP_CALLED_PARTY_NUM ISUP_CHARGE_NUMBER;
/*
 * Defines and macros are the same except the following defines,
 * for the Nature of Address Indicator.
 */
#define CHARGE_NUM_ANI_CGPA_SUB_NBR        0x01
#define CHARGE_NUM_ANI_CGPA_NOT_AVAILABLE  0x02
#define CHARGE_NUM_ANI_CGPA_NATL_NBR       0x03
#define CHARGE_NUM_ANI_CDPA_SUB_NBR        0x05
#define CHARGE_NUM_ANI_CDPA_NOT_AVAILABLE  0x06
#define CHARGE_NUM_ANI_CDPA_NATL_NBR       0x07
/* 0x04, 0x00 and 0x08->0xFF: Spare or reserved */


/*
 ****************************************************************************
 * Circuit group characteristic.
 *
 * ANSI Ref: sec 3.1OA (Figure 10C/T1.113.3), page T1.113.3-12.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   indicator;
}
ISUP_CIRCUIT_GROUP_CHARACTERISTIC;

#define CTKGC_UNKNOWN           0x00

/* Bits BA: Circuit Group Carrier indicator */
#define CTKGC_ANALOG            0x01
#define CTKGC_DIGITAL           0x02
#define CTKGC_ANALOG_DIGITAL    0x03

/* Bits DC: Double Seizing Control indicator */
#define CTKGC_NO_CIC_CONTROL    0x00
#define CTKGC_ODD_CIC_CONTROL   0x01
#define CTKGC_EVEN_CIC_CONTROL  0x02
#define CTKGC_ALL_CIC_CONTROL   0x03

/* Bits FE: Alarm Carrier indicator */
#define CTKGC_SOFTW_CARRIER_HANDLING    0x01
#define CTKGC_HARDW_CARRIER_HANDLING    0x02
#define CTKGC_SPARE                     0x03

/* Bits HG: Continuity Check Requirements indicator */
#define CTKGC_NONE          0x01
#define CTKGC_STATISTICAL   0x02
#define CTKGC_PER_CALL      0x03


/*
 ****************************************************************************
 * Circuit identification name (sending side).
 *
 * ANSI Ref: sec 3.11A (Figure 11A/T1.113.3), page T1.113.3-12.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   trunkNum[4];
    ITS_OCTET   clliCode_officeA[11];
    ITS_OCTET   clliCode_officeZ[11];
}
ISUP_CIRCUIT_IDENTIFICATION_NAME;


/*
 ****************************************************************************
 * Circuit validation response.
 *
 * ANSI Ref: sec 3.11C (Figure 11C/T1.113.3), page T1.113.3-13.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   indicator;
}
ISUP_CIRCUIT_VALIDATION_RESPONSE;

#define CTKVR_SUCCESSFUL    0x00
#define CTKVR_FAILURE       0x01


/*
 ****************************************************************************
 * COMMON LANGUAGE location identification (CLLI) code.
 *
 * ANSI Ref: sec 3.16A(Figure 15A/T1.113.3), page T1.113.3-14.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   town[4];
    ITS_OCTET   state[2];
    ITS_OCTET   building[2];
    ITS_OCTET   buildingSubdiv[3];
}
ISUP_CLLI_CODE;


/*
 ****************************************************************************
 * Egress Service.
 *
 * ANSI Ref: sec 3.16A(Figure 15A/T1.113.3), page T1.113.3-14.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   data[128];
}
ISUP_EGRESS_SERVICE;


/*
 ****************************************************************************
 * Generic Address.
 *
 * ANSI Ref: sec 3.20A(Figure 18A/T1.113.3), page T1.113.3-15.
 *
 * Note: see calling Party Number.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET type_of_addr;
    ITS_OCTET addr_ind;
    ITS_OCTET subfields4;
    ITS_OCTET dgts[MAX_NB_OCTETS_DIGITS];
}
ISUP_GENERIC_ADRRESS;
 
/* Type of Address */
#define GEN_ADDR_DIALLED_NUM                 0x00
#define GEN_ADDR_DEST_NUM                    0x01
#define GEN_ADDR_USER_PROVIDED_FAIL_NTWRK    0x02
#define GEN_ADDR_USER_PROVIDED_NOT_SCREENED  0x03
#define GEN_ADDR_COMPLETION_NUM              0x04   
/* other values: Spare/Reserved */


/*
 ****************************************************************************
 * Jurisdiction.
 *
 * ANSI Ref: sec 3.23A (Figure 21A/T1.113.3), page T1.113.3-18.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   digits[3];
}
ISUP_JURISDICTION;


/*
 ****************************************************************************
 * Network transport.
 *
 * ANSI Ref: sec 3.24A (Figure 22A/T1.113.3), page T1.113.3-18.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   data[128];
}
ISUP_NETWORK_TRANSPORT;


/*
 ****************************************************************************
 * Notification Indicator.
 *
 * ANSI Ref: sec 3.24B (Figure 22B/T1.113.3), page T1.113.3-18.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   indicator;
}
ISUP_NOTIFICATION;

#define NOT_WAITING_CALL                    0x60
#define NOT_TRANSFER_IN_PROGRESS            0x61
#define NOT_CALL_ISOLATED_FROM_CONF_CALL    0x62
#define NOT_CALL_SPLIT_FROM_CONF_CALL       0x63
#define NOT_CALL_REATTACHED_FROM_CONF_CALL  0x64    
#define NOT_CALL_ADDED_FROM_CONF_CALL       0x65
#define NOT_REMOTE_HOLD                     0x79
#define NOT_REMOTE_HOLD_RELEASED            0x7A    
#define NOT_CALL_IS_FORWARDED               0x7B
/* other values are spared, 0xFF is reserved */


/*
 ****************************************************************************
 * Originating Line information.
 *
 * ANSI Ref: sec 3.26A (Figure 23B/T1.113.3), page T1.113.3-19.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET data;
}
ISUP_ORIG_LINE_INFO;


/*
 ****************************************************************************
 * Outgoing Trunk Group Number.
 *
 * ANSI Ref: sec 3.26B (Figure 23C/T1.113.3), page T1.113.3-20.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET digits[3];
}
ISUP_OUTGOING_TRUNK_GRP_NUM;


/*
 ****************************************************************************
 * Service Code.
 *
 * ANSI Ref: sec 3.29C (Figure 25D/T1.113.3), page T1.113.3-22.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   code;
}
ISUP_SERVICE_CODE;


/*
 ****************************************************************************
 * Special Processing Request.
 *
 * ANSI Ref: sec 3.30A (Figure 26A/T1.113.3), page T1.113.3-22.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   data;
}
ISUP_SPECIAL_PROCESS_REQUEST;

/* other values are spare/ reserved (intl, natl, network). */
#define SPR_SRVC_PROCESS_REQUIRED   0x7F


/*
 ****************************************************************************
 * Transaction Request.
 *
 * ANSI Ref: sec 3.31B (Figure 27B/T1.113.3), page T1.113.3-22.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   transaction_id[4];
    SCCP_ADDR   SCCP_addr;   
}
ISUP_TRANSACTION_REQUEST;


/*
 * externs for all message types
 */

extern SS7DLLAPI ISUP_MSG_DESC   ISUP_ACM_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_ANM_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CPG_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CQM_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CQR_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CFN_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_COT_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_INF_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_INR_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_IAM_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_REL_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_RLC_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FOT_Desc_ANSI;                                  
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_RES_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_SUS_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_BLO_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_BLA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UBL_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UBA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CCR_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_LPA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_RSC_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UCIC_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGB_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGBA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGU_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGUA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_GRS_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_GRA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_PAM_Desc_ANSI; 
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FAC_Desc_ANSI; 
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CRA_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CRM_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CVR_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CVT_Desc_ANSI;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_EXM_Desc_ANSI;


typedef struct
{
    ITS_OCTET   param_id;
    ITS_OCTET   param_length;
    union
    {
        /*
         * Msg type of the msg included in the PAM:
         * this MUST BE THE FIRST PARAM (no need to populate
         * param_len of param_id).
         * the ieCount parameter in the function ISUP_SendPAMRequest()
         * must represent the number of params for the msg included in
         * the PAM + 1 (for ie  msgTypeInPAM ).
         * ieCount in ISUP_ReceivePAMIndication() will represent the
         * number of params for the msg included in the PAM received + 1
         * for msgTypeInPAM .
         */
        ITS_OCTET                           msgTypeInPAM;
        ISUP_ACCESS_TRANSPORT               accessTransport;
        ISUP_AUTOMATIC_CONGESTION_LEVEL     autoCongestionLevel;
        ISUP_BKWD_CALL_INDICATORS           backwardCallIndicators;
        ISUP_CALL_REFERENCE                 callRef;
        ISUP_CALLING_PARTY_CATEGORY         callingPartyCategory;
        ISUP_CALLING_PARTY_NUM              callingPartyNum;
        ISUP_CALLED_PARTY_NUM               calledPartyNum;
        ISUP_CAUSE_INDICATOR                causeIndicator;
        ISUP_CIRCUIT_STATE_INDICATORS       circuitStateIndicators;
        ISUP_CONNECTION_REQUEST             connectionRequest;
        ISUP_CONTINUITY_INDICATORS          continuityIndicators;
        ISUP_FORWARD_CALL_INDICATORS        forwardCallIndicators;
        ISUP_EVENT_INFO                     eventInfo;
        ISUP_GENERIC_DIGITS                 genericDigits;
        ISUP_INFORMATION_INDICATORS         informationIndicators;
        ISUP_INFORMATION_REQUEST_INDICATORS informationRequestIndicators;
        ISUP_CONNECTION_INDICATORS          connectionIndicator;
        ISUP_OPT_BKWD_CALL_INDICATORS       optBkwdCallIndicators;
        ISUP_ORIG_CALLED_NUM                origCalledNum;
        ISUP_RANGE_AND_STATUS               rangeAndStatus;
        ISUP_REDIRECTING_NUM                redirectingNum;                
        ISUP_REDIRECTION_INFO               redirectionInfo;
        ISUP_SERVICE_ACTIVATION             servactivation;
        ISUP_SUPERVISION_MSG_TYPE           supervisionMsgType;
        ISUP_SUSPEND_RESUME_INDICATORS      suspendResumeInd;
        ISUP_TRANSIT_NETWORK_SELECTION      transitNetworkSelection;
        ISUP_USER_SERVICE_INFO              userServiceInfo;
        MTP3_HEADER                         routingLabel;
        ISUP_TIMER_ENTRY                    timerData;
        ISUP_ERROR_ENTRY                    errorData;
        PAD_BUF                             pad;
                  /*  ANSI specific messages */
        ISUP_BUSINESS_GROUP                 businessGroup;
        ISUP_CARRIER_IDENTIFICATION         carrierIdentification;
        ISUP_CARRIER_SELECTION_INFO         carrierSelectionInfo;
        ISUP_CHARGE_NUMBER                  chargeNumber;
        ISUP_CIRCUIT_GROUP_CHARACTERISTIC   circuitGrpCharacteristic;
        ISUP_CIRCUIT_IDENTIFICATION_NAME    circuitIdName;
        ISUP_CIRCUIT_VALIDATION_RESPONSE    circuitValidationResponse;
        ISUP_CLLI_CODE                      clliCode;
        ISUP_EGRESS_SERVICE                 egressService;
        ISUP_GENERIC_ADRRESS                genericAddress;
        ISUP_JURISDICTION                   jurisdiction;
        ISUP_NETWORK_TRANSPORT              networkTransport;
        ISUP_NOTIFICATION                   notification;
        ISUP_ORIG_LINE_INFO                 origLineInfo;
        ISUP_OUTGOING_TRUNK_GRP_NUM         outgoingTrunkNum;
        ISUP_SERVICE_CODE                   serviceCode;
        ISUP_SPECIAL_PROCESS_REQUEST        specialProcessing;
        ISUP_TRANSACTION_REQUEST            transactionRequest;
    }
    param_data;
}
ITS_ISUP_IE_ANSI;

/*
 * base API
 */
SS7DLLAPI int ISUP_ValidateCIC_ANSI(ITS_HANDLE h,
                                    ITS_OCTET sio,
                                    ITS_UINT opc, ITS_UINT dpc,
                                    ITS_USHORT cic,
                                    ITS_OCTET* cic_state,
                                    ITS_USHORT *vcic);

SS7DLLAPI ITS_UINT ISUP_ComputeMSize_ANSI(ITS_OCTET type);

SS7DLLAPI int ISUP_Encode_ANSI(ITS_ISUP_IE_ANSI *ies, int ieCount,
                                ITS_OCTET msgType, ITS_EVENT *event,
                                ITS_HDR *hdr, ISUP_MSG_DESC* desc);
SS7DLLAPI int ISUP_Decode_ANSI(ITS_ISUP_IE_ANSI *ies, int *ieCount,
                                ITS_EVENT *ev, ISUP_MSG_DESC* desc);

SS7DLLAPI extern CALLBACK_Manager*    ISUP_ANSI_ManagementCallbacks;

/* Function to get the string equivalent for a TimerId (both ITU & ANSI) */
SS7DLLAPI char* ISUP_GetTimerText_ANSI(ITS_UINT timerid);

/* Function to get string equivalent for ISUP msg; abbreviated & full form */
SS7DLLAPI char* ISUP_GetMsgAbbr_ANSI(ITS_UINT msgType);
SS7DLLAPI char* ISUP_GetMsgName_ANSI(ITS_UINT msgType);

/* for variant management */
typedef int             (*__ISUP_DecodeMsgProc_ANSI)(ITS_Class, ITS_EVENT,
                                                     ITS_OCTET, ITS_OCTET,
                                                     ITS_ISUP_IE_ANSI*,
                                                     int*, ITS_HDR*);
typedef int             (*__ISUP_EncodeMsgProc_ANSI)(ITS_Class,
                                                     ITS_ISUP_IE_ANSI*,
                                                     int,
                                                     ITS_OCTET, ITS_OCTET,
                                                     ITS_HDR*, ITS_EVENT*);

/*******************************************************************
 *                       ISUP interface
 *******************************************************************/
/*** ACM ***/
SS7DLLAPI int ISUP_SendACMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveACMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** ANM ***/
SS7DLLAPI int ISUP_SendANMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveANMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CPG ***/
SS7DLLAPI int ISUP_SendCPGRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);         
SS7DLLAPI int ISUP_ReceiveCPGIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CQM ***/
SS7DLLAPI int ISUP_SendCQMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCQMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CQR ***/
SS7DLLAPI int ISUP_SendCQRRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCQRIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);  

/*** CFN ***/
SS7DLLAPI int ISUP_SendCFNRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCFNIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** COT ***/
SS7DLLAPI int ISUP_SendCOTRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCOTIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** INF ***/
SS7DLLAPI int ISUP_SendINFRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveINFIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,          
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** INR ***/
SS7DLLAPI int ISUP_SendINRRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveINRIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** IAM ***/
SS7DLLAPI int ISUP_SendIAMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveIAMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);
                                                                               

/*** REL ***/
SS7DLLAPI int ISUP_SendRELRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRELIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** RLC ***/
SS7DLLAPI int ISUP_SendRLCRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRLCIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);
                                                                               
/*** FOT ***/
SS7DLLAPI int ISUP_SendFOTRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveFOTIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** SUS ***/
SS7DLLAPI int ISUP_SendSUSRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveSUSIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** RES ***/
SS7DLLAPI int ISUP_SendRESRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRESIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,                     
                                            ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** BLO ***/
SS7DLLAPI int ISUP_SendBLORequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveBLOIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** BLA ***/
SS7DLLAPI int ISUP_SendBLARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveBLAIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** UBL ***/
SS7DLLAPI int ISUP_SendUBLRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);      
SS7DLLAPI int ISUP_ReceiveUBLIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** UBA ***/
SS7DLLAPI int ISUP_SendUBARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUBAIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CCR ***/
SS7DLLAPI int ISUP_SendCCRRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCCRIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);  

/*** LPA ***/
SS7DLLAPI int ISUP_SendLPARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveLPAIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** RSC ***/
SS7DLLAPI int ISUP_SendRSCRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRSCIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** UCIC ***/
SS7DLLAPI int ISUP_SendUCICRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUCICIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,                 
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CGB ***/
SS7DLLAPI int ISUP_SendCGBRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGBIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CGBA ***/
SS7DLLAPI int ISUP_SendCGBARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGBAIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CGU ***/
SS7DLLAPI int ISUP_SendCGURequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,        
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGUIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CGUA ***/
SS7DLLAPI int ISUP_SendCGUARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGUAIndication_ANSI(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** GRS ***/
SS7DLLAPI int ISUP_SendGRSRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveGRSIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);  

/*** GRA ***/
SS7DLLAPI int ISUP_SendGRARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveGRAIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** PAM ***/
SS7DLLAPI int ISUP_SendPAMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceivePAMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CRA ***/
SS7DLLAPI int ISUP_SendCRARequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCRAIndication_ANSI(ITS_HANDLE handle,                
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CRM ***/
SS7DLLAPI int ISUP_SendCRMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCRMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CRT ***/
SS7DLLAPI int ISUP_SendCRTRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCRTIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);
                                                                               
/*** CVR ***/
SS7DLLAPI int ISUP_SendCVRRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCVRIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** CVT ***/
SS7DLLAPI int ISUP_SendCVTRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCVTIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** EXM ***/
SS7DLLAPI int ISUP_SendEXMRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_ISUP_IE_ANSI *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveEXMIndication_ANSI(ITS_HANDLE handle,
                                             ITS_EVENT *event,
                                             ITS_HDR *hdr,                     
                                             ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** Timeout Indication ***/
SS7DLLAPI int ISUP_ReceiveTimeoutIndication_ANSI(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*** Error Indication ***/
SS7DLLAPI int ISUP_ReceiveErrorIndication_ANSI(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_ANSI *ies, int *ieCount);

/*
 * This is only for ANSI.  The default variant is '92.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define ANSI_ISUP_1988      1
#define ANSI_ISUP_1992      2

/******************************** ISUP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

/*
 * Users shouldn't call these
 */
SS7DLLAPI int ISUP_EncodeMTP3_ANSI(ITS_ISUP_IE_ANSI *ies, int ieCount,
                                   ITS_OCTET msgType, ITS_EVENT *event,
                                   ITS_HDR *hdr, ISUP_MSG_DESC* desc);
SS7DLLAPI int ISUP_DecodeMTP3_ANSI(ITS_ISUP_IE_ANSI *ies, int *ieCount,
                                   ITS_EVENT *ev, ISUP_MSG_DESC* desc);        

SS7DLLAPI int ISUP_SendEvent_ANSI(ITS_HANDLE handle, ITS_OCTET type,
                                  ITS_HDR *hdr, ITS_ISUP_IE_ANSI *ies,
                                  int ieCount, ISUP_MSG_DESC *desc);
SS7DLLAPI int ISUP_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                     ITS_HDR *hdr, ITS_ISUP_IE_ANSI *ies,
                                     int *ieCount, ISUP_MSG_DESC *desc);
SS7DLLAPI int ISUP_MessageSanityCheck_ANSI(ITS_OCTET type, ITS_ISUP_IE_ANSI *ies,
                                           int ieCount, ISUP_MSG_DESC *desc);

SS7DLLAPI ISUP_MSG_DESC *ISUP_GetDescriptor_ANSI(ITS_OCTET msgType);

SS7DLLAPI extern CALLBACK_Manager*    ISUP_ANSI_ManagementCallbacks;
                    

/* ANSI specific Timer definitions */
#define ITS_ISUP_TIMER_TACCr    40 
#define ITS_ISUP_TIMER_TCCR     41 
#define ITS_ISUP_TIMER_TCCRr    42 
#define ITS_ISUP_TIMER_TCGB     43
#define ITS_ISUP_TIMER_TCRA     44
#define ITS_ISUP_TIMER_TCRM     45
#define ITS_ISUP_TIMER_TCVT     46
#define ITS_ISUP_TIMER_TEXMd    47
#define ITS_ISUP_TIMER_TGRS     48
#define ITS_ISUP_TIMER_THGA     49
#define ITS_ISUP_TIMER_TSCGA    50 
#define ITS_ISUP_TIMER_TSCGAd   51 
                                                                                                                                   
#if defined(INCLUDE_CODEC)

/*
 * this needs to be a well known global to control which ISUP
 * variant is in use.
 */
SS7DLLAPI extern int  ANSI_ISUP_Variant;

#endif /* INCLUDE_CODEC */
                                                                               
#ifdef __cplusplus
}
#endif

#endif /* _ITS_ISUP_ANSI_H_ */


