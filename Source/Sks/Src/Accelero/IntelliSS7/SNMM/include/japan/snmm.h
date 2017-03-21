/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *  ID: $Id: snmm.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:52  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:25  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 02:44:09  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/26 00:29:15  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SNMM_TTC_H_
#define _ITS_SNMM_TTC_H_

#include <its.h>

#ident "$Id: snmm.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

#include <japan/mtp3.h>

/*
 * signalling network and management messages
 */

/*
 * heading codes
 */
#define SNMM_HEADING_CODE_0_MASK_TTC   0x0FU
#define SNMM_HEADING_CODE_1_MASK_TTC   0xF0U

#define SNMM_HC0_SPARE_TTC     0x00U  /* spare */
#define SNMM_HC0_CHM_TTC       0x01U  /* changeover/changeback */
#define SNMM_HC0_ECM_TTC       0x02U  /* emergency changeover */
#define SNMM_HC0_FCM_TTC       0x03U  /* transfer controlled/congestion test */
#define SNMM_HC0_TFM_TTC       0x04U  /* transfer prohibit/allow/restrict */
#define SNMM_HC0_RSM_TTC       0x05U  /* route set test */
#define SNMM_HC0_MIM_TTC       0x06U  /* management inhibit */
#define SNMM_HC0_TRM_TTC       0x07U  /* traffic restart */
#define SNMM_HC0_DLM_TTC       0x08U  /* data link connection */
#define SNMM_HC0_UFC_TTC       0x0AU  /* user flow control */

#define SNMM_HC1_COO_TTC       0x01U   /* changeover */
#define SNMM_HC1_COA_TTC       0x02U   /* changeover ack */
#define SNMM_HC1_XCO_TTC       0x03U   /* extended changeover */
#define SNMM_HC1_XCA_TTC       0x04U   /* extended changeover ack */
#define SNMM_HC1_CBD_TTC       0x05U   /* changeback */
#define SNMM_HC1_CBA_TTC       0x06U   /* changeback ack */
#define SNMM_HC1_ECO_TTC       0x01U   /* emergency changeover */
#define SNMM_HC1_ECA_TTC       0x02U   /* emergency changeover ack */
#define SNMM_HC1_TFP_TTC       0x01U   /* transfer prohibited */
#define SNMM_HC1_TFR_TTC       0x03U   /* transfer restricted */
#define SNMM_HC1_TFA_TTC       0x05U   /* transfer alloweded */
#define SNMM_HC1_RSP_TTC       0x01U   /* route set test prohibited */
#define SNMM_HC1_RSR_TTC       0x02U   /* route set test restricted */
#define SNMM_HC1_LIN_TTC       0x01U   /* link inhibit */
#define SNMM_HC1_LUN_TTC       0x02U   /* link uninhibit */
#define SNMM_HC1_LIA_TTC       0x03U   /* link inhibit ack */
#define SNMM_HC1_LUA_TTC       0x04U   /* link uninhibit ack */
#define SNMM_HC1_LID_TTC       0x05U   /* link inhibit denied */
#define SNMM_HC1_LFU_TTC       0x06U   /* link force uninhibit */
#define SNMM_HC1_LLI_TTC       0x07U   /* link local inhibit test */
#define SNMM_HC1_LRI_TTC       0x08U   /* link remote inhibit test */
#define SNMM_HC1_DLC_TTC       0x01U   /* data link connect */
#define SNMM_HC1_CSS_TTC       0x02U   /* connection successful */
#define SNMM_HC1_CNS_TTC       0x03U   /* connection not successful */
#define SNMM_HC1_CNP_TTC       0x04U   /* connection not possible */
#define SNMM_HC1_RCT_TTC       0x01U   /* route congestion test */
#define SNMM_HC1_TFC_TTC       0x02U   /* transfer controlled */
#define SNMM_HC1_TRA_TTC       0x01U   /* traffic restart allowed */
#define SNMM_HC1_TRW_TTC       0x02U   /* traffer restart waiting */
#define SNMM_HC1_UPU_TTC       0x01U   /* user part unavailable */

#define SNMM_HC0_GET_TTC(x)                                       \
    ((x).headingCode & SNMM_HEADING_CODE_0_MASK_TTC)
#define SNMM_HC0_SET_TTC(x, v)                                    \
    ((x).headingCode &= ~SNMM_HEADING_CODE_0_MASK_TTC,            \
     (x).headingCode |= ((v) & SNMM_HEADING_CODE_0_MASK_TTC))
#define SNMM_HC1_GET_TTC(x)                                       \
    (((x).headingCode & SNMM_HEADING_CODE_1_MASK_TTC) >> 4)
#define SNMM_HC1_SET_TTC(x, v)                                    \
    ((x).headingCode &= ~SNMM_HEADING_CODE_1_MASK_TTC,            \
     (x).headingCode |= (((v) << 4) & SNMM_HEADING_CODE_1_MASK_TTC))

/*
 * Changeover (and acknowledge) COO, COA
 */
typedef struct
{
    ITS_OCTET   fsn[3];
}
SNMM_CHANGEOVER_TTC;

#define SNMM_CHANGEOVER_GET_FSN_TTC(x)                    \
    ((x).fsn[0] & 0x7FU)
#define SNMM_CHANGEOVER_SET_FSN_TTC(x, v)                 \
    ((x).fsn[0] = (v) & 0x7FU)
#define SNMM_CHANGEOVER_GET_FSN_SAAL_TTC(x)               \
    ((x).fsn[0] | ((x).fsn[1] << 8) | ((x).fsn[2] << 16))
#define SNMM_CHANGEOVER_SET_FSN_SAAL_TTC(x, v)            \
    ((x).fsn[0] = (v), (x).fsn[1] = ((v) >> 8),             \
     (x).fsn[2] = ((v) >> 16))

/*
 * Changeback (and acknowldedge) CBD, CBA
 */
typedef struct
{
    ITS_OCTET   cbcode;
}
SNMM_CHANGEBACK_TTC;

#define SNMM_CHANGEBACK_GET_CODE_TTC(x)       \
    ((x).cbcode)
#define SNMM_CHANGEBACK_SET_CODE_TTC(x, v)    \
    ((x).cbcode = (v))

/*
 * Emergency changeover (and acknowledge) ECO, ECA
 */

/*
 * Transfer Prohibited, Allowed, and Restricted
 * TFP, TCP, TFR, TCR, TFA, TCA
 */
typedef struct
{
    MTP3_POINT_CODE_TTC   dest;
}
SNMM_TRANSFER_STATE_TTC;

#define SNMM_TRANSFER_STATE_GET_DEST_TTC(x)    \
    (MTP3_PC_GET_VALUE_TTC((x).dest))
#define SNMM_TRANSFER_STATE_SET_DEST_TTC(x, v) \
    (MTP3_PC_SET_VALUE_TTC((x).dest, (v)))

/*
 * Route set test messages RSP RSR RCP RCR
 */
typedef struct
{
    MTP3_POINT_CODE_TTC   dest;
}
SNMM_ROUTE_SET_TEST_TTC;

#define SNMM_ROUTE_SET_TEST_GET_DEST_TTC(x)    \
    (MTP3_PC_GET_VALUE_TTC((x).dest))
#define SNMM_ROUTE_SET_TEST_SET_DEST_TTC(x, v) \
    (MTP3_PC_SET_VALUE_TTC((x).dest, (v)))

/*
 * Inhibit messages
 * LIN LUN LIA LUA LID LFU LLI LRI
 */

/*
 * Signalling data link connection order and results
 * DLC CSS CNS CNP
 */
typedef struct
{
    ITS_OCTET   link[2];
}
SNMM_DATALINK_CONNECT_TTC;

#define SNMM_DATALINK_CONNECT_GET_LINK_TTC(x)     \
    (((x).link[0]) |                                \
     (((x)link[1] & 0x0F) << 8))
#define SNMM_DATALINK_CONNECT_SET_LINK_TTC(x, v)  \
    ((x).link[0] = (v) & 0xFFU,                     \
     (x).link[2] = ((v) >> 8) & 0x0FU)

/*
 * route congestion test and transfer controlled RCT, TFC
 */
typedef struct
{
    MTP3_POINT_CODE_TTC   dest;
    ITS_OCTET               status;
}
SNMM_TRANSFER_CONTROL_TTC;

#define SNMM_TRANSFER_CONTROL_GET_DEST_TTC(x)         \
    MTP3_PC_GET_VALUE_TTC((x).dest)
#define SNMM_TRANSFER_CONTROL_SET_DEST_TTC(x, v)      \
    MTP3_PC_SET_VALUE_TTC((x).dest, (v))
#define SNMM_TRANSFER_CONTROL_GET_STATUS_TTC(x)       \
    ((x).status & 0x03U)
#define SNMM_TRANSFER_CONTROL_SET_STATUS_TTC(x, v)    \
    ((x).status = ((v) & 0x03U))

/*
 * traffic restart TRA TRW
 */

/*
 * User part unavailable UPU
 */
typedef struct
{
    MTP3_POINT_CODE_TTC   dest;
    ITS_OCTET               user;
}
SNMM_USER_PART_UNAVAILABLE_TTC;

#define SNMM_USER_PART_UNAVAIL_GET_DEST_TTC(x)        \
    (MTP3_PC_GET_VALUE_TTC((x).dest))
#define SNMM_USER_PART_UNAVAIL_SET_DEST_TTC(x, v)     \
    (MTP3_PC_SET_VALUE_TTC((x).dest, (v)))
#define SNMM_USER_PART_UNAVAIL_GET_USER_TTC(x)        \
    ((x).user & 0x0FU)
#define SNMM_USER_PART_UNAVAIL_SET_USER_TTC(x, v)     \
    ((x).user &= 0xF0U, (x).user |= ((v) & 0x0FU))
#define SNMM_USER_PART_UNAVAIL_GET_CAUSE_TTC(x)       \
    ((x).user & 0xF0U)
#define SNMM_USER_PART_UNAVAIL_SET_CAUSE_TTC(x, v)    \
    ((x).user &= 0x0FU, (x).user |= ((v) & 0xF0U))

#define SNMM_UPU_CAUSE_UNKNOWN      0x00U
#define SNMM_UPU_CAUSE_UNEQUIPPED   0x10U
#define SNMM_UPU_CAUSE_INACCESS     0x20U

/*
 * use of the short names is deprecated and may be removed in
 * a future release
 */
#include <snmm_sn.h>

/*
 * include shared defs
 */
#include <snmm_cmn.h>

/*
 * codec
 */
#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * these function return a message encoded for MTP3 transmission/reception
 * (aka USER_DATA).
 */
SS7DLLAPI int SNMM_Encode_TTC(ITS_EVENT *ev, MTP3_HEADER_TTC *label,
                                SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_Decode_TTC(ITS_EVENT *ev, MTP3_HEADER_TTC *label,
                                SNMM_MESSAGE *msg);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _ITS_SNMM_CMN_H_ */
