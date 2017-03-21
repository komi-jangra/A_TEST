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
 ****************************************************************************/
                                                                                
/*
 * This file contains Radio Resources Management Information Elements
 * and Message Structures used at the Abis interface
 *
 * All the information referred by 3GPP TS 44.018 specification
 * unless specified
 */

#include <its.h>
#include <stdio.h>
#include <its_types.h>
                                                               
#define RR_NOMEM         -1

/* Message Discriminator */
#define SKIP_INDICATOR      0x00U
#define RR_PROTOCOL_DISC    0x06U

/*****************************************************************
 * Message Types : Reference 3GPP TS 44.018 V7.0.0
 ****************************************************************/
/*  Channel Establishment Messages  */
#define RR_MSG_IMMEDIATE_ASSIGN          0x3FU
#define RR_MSG_IMMEDIATE_ASSIGN_REJ      0x3AU  

/*  Ciphering Messages  */
#define RR_MSG_CIPHERING_MODE_CMD        0x35U
#define RR_MSG_CIPHERING_MODE_CMP        0x32U

/*  Handover Messages  */
#define RR_MSG_ASSIGN_CMD                0x2EU
#define RR_MSG_ASSIGN_CMP                0x29U
#define RR_MSG_ASSIGN_FAIL               0x2FU

/* Channel Release Messages   */
#define RR_MSG_CHANNEL_RELEASE           0x0DU

/* Paging and Notification Messages   */
#define RR_MSG_PAGING_RESPONSE           0x27U

/* Miscellaneous Messages     */
#define RR_MSG_MEASUREMENT_REPORT        0x15U
#define RR_MSG_CLASSMARK_CHANGE          0x16U
#define RR_MSG_CLASSMARK_ENQUIRY         0x13U

/***********************************************************************
 * Information Element Identifiers : Reference 3GPP TS 44.018 V7.0.0
 **********************************************************************/
#define RR_IE_VGCS_TARGET_MODE_INDICATION        0x01U
#define RR_IE_MULTIRATE_CONFIG                   0x03U
#define RR_IE_VGCS_CIPHERING_PARA                0x04U
#define RR_IE_FREQUENCY_LIST_AFTER_TIME          0x05U
#define RR_IE_DESC_MULTISLOT_CONFIG              0x10U
#define RR_IE_MODE_OF_CHAN_SET2                  0x11U
#define RR_IE_MODE_OF_CHAN_SET3                  0x13U
#define RR_IE_MODE_OF_CHAN_SET4                  0x14U
#define RR_IE_MODE_OF_CHAN_SET5                  0x15U
#define RR_IE_MODE_OF_CHAN_SET6                  0x16U
#define RR_IE_MODE_OF_CHAN_SET7                  0x17U
#define RR_IE_MODE_OF_CHAN_SET8                  0x18U
#define RR_IE_FREQUENCY_LIST_BEFORE_TIME         0x19U
#define RR_IE_DESC_OF_FIRST_CHAN_BEFORE_TIME     0x1CU
#define RR_IE_DESC_OF_SECOND_CHAN_BEFORE_TIME    0x1DU
#define RR_IE_FREQ_CHAN_SEQ_BEFORE_TIME          0x1EU  
#define RR_IE_MOBILE_ALLOC_BEFORE_TIME           0x21U
#define RR_IE_CELL_CHAN_DESCRIPTION              0x62U
#define RR_IE_MODE_OF_CHAN_SET1                  0x63U
#define RR_IE_DESC_OF_SECOND_CHAN_AFTER_TIME     0x64U
#define RR_IE_MODE_OF_SECOND_CHAN                0x66U
#define RR_IE_MOBILE_ALLOC_AFTER_TIME            0x72U
#define RR_IE_BA_RANGE                           0x73U
#define RR_IE_GROUP_CHAN_DESC                    0x74U
#define RR_IE_BA_LIST_PREF                       0x75U
#define RR_IE_UTRAN_FREQ_LIST                    0x76U
#define RR_IE_CELL_SELECTION_INDICATOR           0x77U
#define RR_IE_GROUP_CHAN_DESCRIPTION2            0x78U
#define RR_IE_STARTING_TIME                      0x7CU
#define RR_IE_GROUP_CIPHER_KEY_NUM               0x80U
#define RR_IE_CIPHER_MODE_SETTING                0x90U
#define RR_IE_EN_DTM_CS_RELEASE_INDICATION       0xA0U
#define RR_IE_GPRS_RESUMPTION                    0xC0U

#define RR_IE_CLASSMARK_ENQUIRY_MASK             0x10U
#define RR_IE_MOBILE_EQUIP_ID                    0x17U
#define RR_IE_ADDITIONAL_MS_CM_INFO              0x20U

/***********************************************************************
 *  Macros to check presence of Optional IEs
 **********************************************************************/
#define SET_OPT_FLAG_STARTING_TIME(msg)       \
    msg->u.imAssign.optIEFlags |= 0x01

#define GET_OPT_FLAG_STARTING_TIME(msg)       \
    msg->u.imAssign.optIEFlags & 0x01

#define SET_OPT_FLAG_BA_RANGE(msg)            \
    msg->u.chanRelease.optIEFlags1 |= 0x01

#define GET_OPT_FLAG_BA_RANGE(msg)            \
    msg->u.chanRelease.optIEFlags1 & 0x01

#define SET_OPT_FLAG_GROUP_CHAN_DESC(msg)     \
    msg->u.chanRelease.optIEFlags1 |= 0x02

#define GET_OPT_FLAG_GROUP_CHAN_DESC(msg)     \
    msg->u.chanRelease.optIEFlags1 & 0x02

#define SET_OPT_FLAG_GPRS_RESUMP(msg)         \
    msg->u.chanRelease.optIEFlags1 |= 0x04

#define GET_OPT_FLAG_GPRS_RESUMP(msg)         \
    msg->u.chanRelease.optIEFlags1 & 0x04

#define SET_OPT_FLAG_BA_LIST_PREF(msg)        \
    msg->u.chanRelease.optIEFlags1 |= 0x08
                                                                                
#define GET_OPT_FLAG_BA_LIST_PREF(msg)        \
    msg->u.chanRelease.optIEFlags1 & 0x08
 
#define SET_OPT_FLAG_UTRAN_FREQ_LIST(msg)     \
    msg->u.chanRelease.optIEFlags1 |= 0x10

#define GET_OPT_FLAG_UTRAN_FREQ_LIST(msg)     \
    msg->u.chanRelease.optIEFlags1 & 0x10

#define SET_OPT_FLAG_CELL_SELECTION_IND(msg)  \
    msg->u.chanRelease.optIEFlags1 |= 0x20

#define GET_OPT_FLAG_CELL_SELECTION_IND(msg)  \
    msg->u.chanRelease.optIEFlags1 & 0x20

#define SET_OPT_FLAG_CELL_CHAN_DESC(msg)      \
    msg->u.chanRelease.optIEFlags1 |= 0x40

#define GET_OPT_FLAG_CELL_CHAN_DESC(msg)      \
    msg->u.chanRelease.optIEFlags1 & 0x40

#define SET_OPT_FLAG_RELEASE_INDICATION(msg)  \
    msg->u.chanRelease.optIEFlags1 |= 0x80

#define GET_OPT_FLAG_RELEASE_INDICATION(msg)  \
    msg->u.chanRelease.optIEFlags1 & 0x80

#define SET_OPT_FLAG_VGCS_CIPHER_PARA(msg)    \
    msg->u.chanRelease.optIEFlags2 |= 0x01

#define GET_OPT_FLAG_VGCS_CIPHER_PARA(msg)    \
    msg->u.chanRelease.optIEFlags2 & 0x01

#define SET_OPT_FLAG_GROUP_CHAN_DESC2(msg)    \
    msg->u.chanRelease.optIEFlags2 |= 0x02

#define GET_OPT_FLAG_GROUP_CHAN_DESC2(msg)    \
    msg->u.chanRelease.optIEFlags2 & 0x02

#define SET_OPT_FLAG_CM_ENQUIRY_MASK(msg)     \
    msg->u.cmEnquiry.optIEFlags |= 0x01

#define GET_OPT_FLAG_CM_ENQUIRY_MASK(msg)     \
    msg->u.cmEnquiry.optIEFlags & 0x01

#define SET_OPT_FLAG_MOBILE_EQUIP_ID(msg)     \
    msg->u.cipherComplete.optIEFlags |= 0x01

#define GET_OPT_FLAG_MOBILE_EQUIP_ID(msg)     \
    msg->u.cipherComplete.optIEFlags & 0x01

#define SET_OPT_FLAG_AC_CELL_CHAN_DESC(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x01

#define GET_OPT_FLAG_AC_CELL_CHAN_DESC(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x01

#define SET_OPT_FLAG_AC_MODE_CHAN_SET1(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x02

#define GET_OPT_FLAG_AC_MODE_CHAN_SET1(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x02

#define SET_OPT_FLAG_AC_MODE_CHAN_SET2(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x04
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET2(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x04

#define SET_OPT_FLAG_AC_MODE_CHAN_SET3(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x08
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET3(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x08

#define SET_OPT_FLAG_AC_MODE_CHAN_SET4(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x10
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET4(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x10

#define SET_OPT_FLAG_AC_MODE_CHAN_SET5(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x20
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET5(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x20

#define SET_OPT_FLAG_AC_MODE_CHAN_SET6(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x40
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET6(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x40

#define SET_OPT_FLAG_AC_MODE_CHAN_SET7(msg)   \
    msg->u.assignCommand.optIEFlags1 |= 0x80
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET7(msg)   \
    msg->u.assignCommand.optIEFlags1 & 0x80

#define SET_OPT_FLAG_AC_MODE_CHAN_SET8(msg)   \
    msg->u.assignCommand.optIEFlags2 |= 0x01
                                                                                
#define GET_OPT_FLAG_AC_MODE_CHAN_SET8(msg)   \
    msg->u.assignCommand.optIEFlags2 & 0x01

#define SET_OPT_FLAG_AC_DESC_SC_AT(msg)       \
    msg->u.assignCommand.optIEFlags2 |= 0x02

#define GET_OPT_FLAG_AC_DESC_SC_AT(msg)       \
    msg->u.assignCommand.optIEFlags2 & 0x02

#define SET_OPT_FLAG_AC_MODE_SEC_CHAN(msg)    \
    msg->u.assignCommand.optIEFlags2 |= 0x04

#define GET_OPT_FLAG_AC_MODE_SEC_CHAN(msg)    \
    msg->u.assignCommand.optIEFlags2 & 0x04

#define SET_OPT_FLAG_AC_START_TIME(msg)       \
    msg->u.assignCommand.optIEFlags2 |= 0x08

#define GET_OPT_FLAG_AC_START_TIME(msg)       \
    msg->u.assignCommand.optIEFlags2 & 0x08

#define SET_OPT_FLAG_AC_DESC_FC_BT(msg)       \
    msg->u.assignCommand.optIEFlags2 |= 0x10

#define GET_OPT_FLAG_AC_DESC_FC_BT(msg)       \
    msg->u.assignCommand.optIEFlags2 & 0x10

#define SET_OPT_FLAG_AC_DESC_SC_BT(msg)       \
    msg->u.assignCommand.optIEFlags2 |= 0x20

#define GET_OPT_FLAG_AC_DESC_SC_BT(msg)       \
    msg->u.assignCommand.optIEFlags2 & 0x20

#define SET_OPT_FLAG_AC_CIPHER_MODE_SET(msg)  \
    msg->u.assignCommand.optIEFlags2 |= 0x40

#define GET_OPT_FLAG_AC_CIPHER_MODE_SET(msg)  \
    msg->u.assignCommand.optIEFlags2 & 0x40

#define SET_OPT_FLAG_AC_VGCS_TGT_MODE_IND(msg)\
    msg->u.assignCommand.optIEFlags2 |= 0x80

#define GET_OPT_FLAG_AC_VGCS_TGT_MODE_IND(msg)\
    msg->u.assignCommand.optIEFlags2 & 0x80

#define SET_OPT_FLAG_AC_MULTIRATE_CONFIG(msg) \
    msg->u.assignCommand.optIEFlags3 |= 0x01

#define GET_OPT_FLAG_AC_MULTIRATE_CONFIG(msg) \
    msg->u.assignCommand.optIEFlags3 & 0x01

#define SET_OPT_FLAG_AC_VGCS_CIPHER_PARA(msg) \
    msg->u.assignCommand.optIEFlags3 |= 0x02

#define GET_OPT_FLAG_AC_VGCS_CIPHER_PARA(msg) \
    msg->u.assignCommand.optIEFlags3 & 0x02

/***********************************************************************
 *  RR Information Elements : Reference 3GPP TS 44.018 V7.0.0
 **********************************************************************/

/*       BA Range : 10.5.2.1a        */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   numOfRange;
    ITS_OCTET   range[3];
}
BA_RANGE;

/*       Group Channel Description         */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   chanType;
    ITS_OCTET   tn;
    ITS_OCTET   tsc;
    ITS_OCTET   h;
    ITS_OCTET   maio;
    ITS_OCTET   hsn;
    ITS_USHORT  arfcn;
    ITS_OCTET   mac[8];
}
GROUP_CHAN_DESC;

/*       BA List Pref         */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   val[10];
}
BA_LIST_PREF;

/*       UTRAN Frequency List         */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   val[10];
}
UTRAN_FREQ_LIST;

/*       Cell Selection Indicator after Release of TCH and SDCCH   */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   val[10];
}
CELL_SELECTION_IND;

/*       Cell Channel Description         */
typedef struct
{
    ITS_OCTET   val[16];
}
CELL_CHAN_DESC;

/*       VGCS Ciphering Parameter - Ref : 10.5.2.42b   */
typedef struct
{
    ITS_OCTET   len;
//    ITS_OCTET   val[13];
    ITS_OCTET   randInd;
    ITS_OCTET   lacInd;
    ITS_OCTET   cellInd;
    ITS_OCTET   b22Count;
    ITS_OCTET   cgCount;
}
VGCS_CIPHER_PARA;

/*       Group Channel Description 2         */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   val[11];
}
GROUP_CHAN_DESC2;

/*       Power Command         */
typedef struct
{
    ITS_OCTET   powLevel;
    ITS_OCTET   fpcEpc;
    ITS_OCTET   epc;
}
POWER_COMMAND;

/*       Description of the First Channel After Time  */
typedef struct
{
    ITS_OCTET   chanType;
    ITS_OCTET   tn;
    ITS_OCTET   tsc;
    ITS_OCTET   h;
    ITS_OCTET   maio;
    ITS_OCTET   hsn;
    ITS_USHORT  arfcn;
}
CHAN_DESC_2;

/*       Channel Description   */
typedef struct
{
    ITS_OCTET   chanType;
    ITS_OCTET   tn;
    ITS_OCTET   tsc;
    ITS_OCTET   h;
    ITS_OCTET   maio;
    ITS_OCTET   hsn;
    ITS_USHORT  arfcn;
}
CHAN_DESC;

/*      Request Reference   */
typedef struct
{
    ITS_OCTET  ra;
    ITS_OCTET  t[2];
}
REQUEST_REF;

/*      Mobile Allocation   */
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  val[8];
}
MOBILE_ALLOC;

/*      Starting Time     */
typedef struct
{
    ITS_OCTET  t1;
    ITS_OCTET  t2;
    ITS_OCTET  t3;
}
STARTING_TIME;

/*     Description of Multislot Allocation */
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  da;
    ITS_OCTET  ua;
    ITS_OCTET  chanSet[8];
}
DESC_MULTISLOT;

/*     Mobile Equipment ID       */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   typeOfID;
    ITS_OCTET   oddEven;
    ITS_OCTET   idDigits[16];
}
MOBILE_EQUIP_ID;

/*     Classmark Enquiry Mask    */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   val;
}
CM_ENQUIRY_MASK;

/*     Mobile Station Classmark  */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   revLevel;
    ITS_OCTET   esInd;
    ITS_OCTET   a51;
    ITS_OCTET   rfPowCap;
    ITS_OCTET   psCap;
    ITS_OCTET   ssScreenInd;
    ITS_OCTET   smCap;
    ITS_OCTET   vbs;
    ITS_OCTET   vgcs;
    ITS_OCTET   fc;
    ITS_OCTET   cm3;
    ITS_OCTET   lcsvaCap;
    ITS_OCTET   ucs2;
    ITS_OCTET   soLSA;
    ITS_OCTET   cmsp;
    ITS_OCTET   a53;
    ITS_OCTET   a52;
}
MS_CLASSMARK;

/* Additional Mobile Station Classmark  */
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  val[12];
}
ADD_MS_CM_INFO;

/*  Frequency List, after time          */
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  formatID;
    ITS_OCTET  val[16];
}
FREQ_LIST;

/*  Mode of the channel Set - Ref : 10.5.2.6   */
typedef struct
{
    ITS_OCTET  mode;
}
CHAN_MODE;

/*  Channel Mode 2 - Ref : 10.5.2.7    */
typedef struct
{
    ITS_OCTET  mode;
}
CHAN_MODE_2;

/*  Frequency Channel Sequence -- Ref: 10.5.2.12  */
typedef struct
{
    ITS_OCTET  lowARFCN;
    ITS_OCTET  isARFCN[16];
}
FREQ_CHAN_SEQ;

/*  Cipher Mode Setting - Ref : 10.5.2.9  */
typedef struct
{
    ITS_OCTET  sc;
    ITS_OCTET  algorithmID;
}
CIPHER_MODE_SET;

/*  VGCS Target Mode Indicator - Ref : 10.5.2.42a */
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  tgtMode;
    ITS_OCTET  groupCipherKey;
}
VGCS_TGT_MODE_IND;

/*  Multirate Configuration - Ref : 10.5.2.21aa */
typedef struct
{
    ITS_OCTET  len;
    ITS_OCTET  msVersion;
    ITS_OCTET  nscb;
    ITS_OCTET  icmi;
    ITS_OCTET  startMode;
    ITS_OCTET  amrCodecMode;
}
MULTIRATE_CONFIG;

/* Measurement Result - Ref : 10.5.2.20  */
typedef struct
{
    ITS_OCTET  baUsed;
    ITS_OCTET  dtxUsed;
    ITS_OCTET  rxLevFull;
    ITS_OCTET  baUsed3G;
    ITS_OCTET  measValid;
    ITS_OCTET  rxLevSub;
    ITS_OCTET  rxQualFull;
    ITS_OCTET  rxQualSub;
    ITS_OCTET  noNCellM;
    ITS_OCTET  rxLevNCell1;
    ITS_OCTET  bcchFreqNCell1;
    ITS_OCTET  bsicNCell1;
    ITS_OCTET  rxLevNCell2;
    ITS_OCTET  bcchFreqNCell2;
    ITS_OCTET  bsicNCell2;
    ITS_OCTET  rxLevNCell3;
    ITS_OCTET  bcchFreqNCell3;
    ITS_OCTET  bsicNCell3;
    ITS_OCTET  rxLevNCell4;
    ITS_OCTET  bcchFreqNCell4;
    ITS_OCTET  bsicNCell4;
    ITS_OCTET  rxLevNCell5;
    ITS_OCTET  bcchFreqNCell5;
    ITS_OCTET  bsicNCell5;
    ITS_OCTET  rxLevNCell6;
    ITS_OCTET  bcchFreqNCell6;
    ITS_OCTET  bsicNCell6;
}
MEASUREMENT_RESULT;

/*********************************************************************** 
 *  RR MESSAGES   :   Reference 3GPP TS 44.018 V7.0.0 
 **********************************************************************/

/*  AssignmentComplete -- Ref: Specs 44.018 - Section 9.1.3 */
typedef struct
{
    ITS_OCTET   rrCause;
}
RR_ASSIGN_COMPLETE;

/*  AssignmentCommand -- Ref: Specs 44.018 - Section 9.1.2  */
typedef struct
{
    CHAN_DESC_2         descFCAT;
    POWER_COMMAND       powCmd;
    FREQ_LIST           freqListAT;
    ITS_OCTET           optIEFlags1;
    CELL_CHAN_DESC      cellChanDesc;
    DESC_MULTISLOT      descMultiSlot;
    CHAN_MODE           modeChanSet1;
    CHAN_MODE           modeChanSet2;
    CHAN_MODE           modeChanSet3;
    CHAN_MODE           modeChanSet4;
    CHAN_MODE           modeChanSet5;
    CHAN_MODE           modeChanSet6;
    CHAN_MODE           modeChanSet7;
    ITS_OCTET           optIEFlags2;
    CHAN_MODE           modeChanSet8;
    CHAN_DESC           descSCAT;
    CHAN_MODE_2         modeSecChan;
    MOBILE_ALLOC        mobAllocAT;
    STARTING_TIME       startTime;
    FREQ_LIST           freqListBT;
    CHAN_DESC_2         descFCBT;
    CHAN_DESC           descSCBT;
    FREQ_CHAN_SEQ       freqChanSeqBT;
    MOBILE_ALLOC        mobAllocBT;
    CIPHER_MODE_SET     cipherModeSet;
    VGCS_TGT_MODE_IND   vgcsTgtModeInd;
    ITS_OCTET           optIEFlags3;
    MULTIRATE_CONFIG    multirateConfig;
    VGCS_CIPHER_PARA    vgcsCipherPara;
}
RR_ASSIGN_COMMAND;

/*  AssignmentFailure -- Ref: Specs 44.018 - Section 9.1.4  */
typedef struct
{
    ITS_OCTET   rrCause;
}
RR_ASSIGN_FAILURE;

/*  ImmediateAssignment -- Ref: Specs 44.018 - Section 9.1.18  */
typedef struct
{
    ITS_OCTET         pageMode;
    ITS_OCTET         dediMode;
    CHAN_DESC         chanDesc;
    ITS_OCTET         packChanDesc[3];
    REQUEST_REF       reqRef;
    ITS_OCTET         timingAdv;
    MOBILE_ALLOC      mobAlloc;
    ITS_OCTET         optIEFlags;
    STARTING_TIME     startTime;
    ITS_OCTET         iaRestOct[11];
}
RR_IMMEDIATE_ASSIGN;

/*  ImmediateAssignmentReject -- Ref: Specs 44.018 - Section 9.1.20  */
typedef struct
{
    ITS_OCTET         pageMode;
    REQUEST_REF       reqRef1;
    ITS_OCTET         waitInd1;
    REQUEST_REF       reqRef2;
    ITS_OCTET         waitInd2;
    REQUEST_REF       reqRef3;
    ITS_OCTET         waitInd3;
    REQUEST_REF       reqRef4;
    ITS_OCTET         waitInd4;
    ITS_OCTET         iarRestOct[3];
}
RR_IMMEDIATE_ASSIGN_REJ;

/*  CipherModeCommand -- Ref: Specs 44.018 - Section 9.1.19  */
typedef struct
{
    ITS_OCTET   cmsAlgoid;
    ITS_OCTET   cmsSC;
	ITS_OCTET   CR;
}
RR_CIPHER_MODE_COMMAND;

/*  CipherModeComplete -- Ref: Specs 44.018 - Section 9.1.10 */
typedef struct
{
    ITS_OCTET        optIEFlags;
    ITS_OCTET        len;
    MOBILE_EQUIP_ID  mobEquipID;
}
RR_CIPHER_MODE_COMPLETE;

/*  ChannelRelease -- Ref: Specs 44.018 - Section 9.1.7 */
typedef struct
{
    ITS_OCTET           rrCause;
    ITS_OCTET           optIEFlags1;
    BA_RANGE            baRange;
    GROUP_CHAN_DESC     groupChanDesc;
    ITS_OCTET           groupCipherKey;
    ITS_OCTET           gprsResump;
    BA_LIST_PREF        baListPref;
    UTRAN_FREQ_LIST     utranFreqList;
    CELL_SELECTION_IND  cellSelIndl;
    CELL_CHAN_DESC      cellChanDesc;
    ITS_OCTET           enRelInd;
    ITS_OCTET           optIEFlags2;
    VGCS_CIPHER_PARA    vgcsCipherPara;
    GROUP_CHAN_DESC2    groupChanDesc2; 
}
RR_CHANNEL_RELEASE;


/*  Classmark Change -- Ref: Specs 44.018 - Section 9.1.11    */
typedef struct
{
   MS_CLASSMARK    msClassmark;
   ADD_MS_CM_INFO  addMsCmInfo;
}
RR_CLASSMARK_CHANGE;

/*  Classmark Enquiry -- Ref: Specs 44.018 - Section 9.1.12  */
typedef struct
{
    ITS_OCTET        optIEFlags;
    CM_ENQUIRY_MASK  cmEnquiryMask;
}
RR_CLASSMARK_ENQUIRY;
 
/*  Measurement Report -- Ref: Specs 44.018 - Section 9.1.21 */
typedef struct
{
    MEASUREMENT_RESULT  measureResult;   
}
RR_MEASUREMENT_REPORT;

/*  Paging Response  -- Ref: Specs 44.018 - Section 9.1.25 */
typedef struct
{
    ITS_OCTET        cipherKeySeq;
    MS_CLASSMARK     msClassmark;
    MOBILE_EQUIP_ID  mobileID;
}
RR_PAGING_RESPONSE;

/***********************************************************************
 * Complete RR Management Message Structure : Ref 3GPP TS 44.018 V7.0.0
 **********************************************************************/
typedef struct
{
    ITS_OCTET  l2PseudoLen;
    ITS_OCTET  msgSkipDisc;
    ITS_OCTET  msgType;
    union
    {
        RR_ASSIGN_COMPLETE       assignComplete;
        RR_ASSIGN_COMMAND        assignCommand;
        RR_ASSIGN_FAILURE        assignFailure;
        RR_CIPHER_MODE_COMMAND   cipherCommand;
        RR_CIPHER_MODE_COMPLETE  cipherComplete;
        RR_CHANNEL_RELEASE       chanRelease;
        RR_IMMEDIATE_ASSIGN      imAssign;
        RR_IMMEDIATE_ASSIGN_REJ  imAssignRej;
        RR_CLASSMARK_CHANGE      cmChange;
        RR_CLASSMARK_ENQUIRY     cmEnquiry;
        RR_MEASUREMENT_REPORT    measureReport;
        RR_PAGING_RESPONSE       pagingResp;
    }
    u;
}
RR_MANAGEMENT_MSG;

#ifdef __cplusplus
extern "C"
{
#endif
ITS_INT
RR_Encode(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_Decode(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);
#ifdef __cplusplus
}
#endif

ITS_INT
RR_EncodeImAssign(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeImAssign(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeImAssignRej(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeImAssignRej(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeCipherModeCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer);

ITS_INT
RR_DecodeCipherModeCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer);

ITS_INT
RR_EncodeCipherModeCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer);
                                                                                
ITS_INT
RR_DecodeCipherModeCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                       ITS_OCTET *buffer);

ITS_INT
RR_EncodeAssignCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeAssignCmd(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeAssignCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeAssignCmp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeAssignFail(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeAssignFail(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeChanRelease(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeChanRelease(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeCMChange(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeCMChange(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeCMEnquiry(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodeCMEnquiry(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_EncodeMeasureReport(RR_MANAGEMENT_MSG *msg, ITS_INT *size, 
                                          ITS_OCTET *buffer);

ITS_INT
RR_DecodeMeasureReport(RR_MANAGEMENT_MSG *msg, ITS_INT *size,
                                          ITS_OCTET *buffer);

ITS_INT
RR_EncodePagingResp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);

ITS_INT
RR_DecodePagingResp(RR_MANAGEMENT_MSG *msg, ITS_INT *size, ITS_OCTET *buffer);
