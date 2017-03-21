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
 * LOG: Revision 8.3  2005/03/21 13:50:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 14:05:43  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:32  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/07/03 16:14:33  mmiers
 * LOG: Add china family
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SNMM_PRC_H_
#define _ITS_SNMM_PRC_H_

#include <its.h>

#ident "$Id: snmm.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

#include <china/mtp3.h>

/*
 * signalling network and management messages
 */

/*
 * heading codes
 */
#define SNMM_HEADING_CODE_0_MASK_PRC   0x0FU
#define SNMM_HEADING_CODE_1_MASK_PRC   0xF0U

#define SNMM_HC0_SPARE_PRC      0x00U  /* spare */
#define SNMM_HC0_CHM_PRC        0x01U  /* changeover/changeback */
#define SNMM_HC0_ECM_PRC        0x02U  /* emergency changeover */
#define SNMM_HC0_FCM_PRC        0x03U  /* transfer controlled/congestion test */
#define SNMM_HC0_TFM_PRC        0x04U  /* transfer prohibit/allow/restrict */
#define SNMM_HC0_RSM_PRC        0x05U  /* route set test */
#define SNMM_HC0_MIM_PRC        0x06U  /* management inhibit */
#define SNMM_HC0_TRM_PRC        0x07U  /* traffic restart */
#define SNMM_HC0_DLM_PRC        0x08U  /* data link connection */
#define SNMM_HC0_UFC_PRC        0x0AU  /* user flow control */

#define SNMM_HC1_COO_PRC        0x01U   /* changeover */
#define SNMM_HC1_COA_PRC        0x02U   /* changeover ack */
#define SNMM_HC1_XCO_PRC        0x03U   /* extended changeover */
#define SNMM_HC1_XCA_PRC        0x04U   /* extended changeover ack */
#define SNMM_HC1_CBD_PRC        0x05U   /* changeback */
#define SNMM_HC1_CBA_PRC        0x06U   /* changeback ack */
#define SNMM_HC1_ECO_PRC        0x01U   /* emergency changeover */
#define SNMM_HC1_ECA_PRC        0x02U   /* emergency changeover ack */
#define SNMM_HC1_TFP_PRC        0x01U   /* transfer prohibited */
#define SNMM_HC1_TFR_PRC        0x03U   /* transfer restricted */
#define SNMM_HC1_TFA_PRC        0x05U   /* transfer alloweded */
#define SNMM_HC1_RSP_PRC        0x01U   /* route set test prohibited */
#define SNMM_HC1_RSR_PRC        0x02U   /* route set test restricted */
#define SNMM_HC1_LIN_PRC        0x01U   /* link inhibit */
#define SNMM_HC1_LUN_PRC        0x02U   /* link uninhibit */
#define SNMM_HC1_LIA_PRC        0x03U   /* link inhibit ack */
#define SNMM_HC1_LUA_PRC        0x04U   /* link uninhibit ack */
#define SNMM_HC1_LID_PRC        0x05U   /* link inhibit denied */
#define SNMM_HC1_LFU_PRC        0x06U   /* link force uninhibit */
#define SNMM_HC1_LLI_PRC        0x07U   /* link local inhibit test */
#define SNMM_HC1_LRI_PRC        0x08U   /* link remote inhibit test */
#define SNMM_HC1_DLC_PRC        0x01U   /* data link connect */
#define SNMM_HC1_CSS_PRC        0x02U   /* connection successful */
#define SNMM_HC1_CNS_PRC        0x03U   /* connection not successful */
#define SNMM_HC1_CNP_PRC        0x04U   /* connection not possible */
#define SNMM_HC1_RCT_PRC        0x01U   /* route congestion test */
#define SNMM_HC1_TFC_PRC        0x02U   /* transfer controlled */
#define SNMM_HC1_TRA_PRC        0x01U   /* traffic restart allowed */
#define SNMM_HC1_TRW_PRC        0x02U   /* traffer restart waiting */
#define SNMM_HC1_UPU_PRC        0x01U   /* user part unavailable */

#define SNMM_HC0_GET_PRC(x)                                         \
    ((x).headingCode & SNMM_HEADING_CODE_0_MASK_PRC)
#define SNMM_HC0_SET_PRC(x, v)                                      \
    ((x).headingCode &= ~SNMM_HEADING_CODE_0_MASK_PRC,              \
     (x).headingCode |= ((v) & SNMM_HEADING_CODE_0_MASK_PRC))
#define SNMM_HC1_GET_PRC(x)                                         \
    (((x).headingCode & SNMM_HEADING_CODE_1_MASK_PRC) >> 4)
#define SNMM_HC1_SET_PRC(x, v)                                      \
    ((x).headingCode &= ~SNMM_HEADING_CODE_1_MASK_PRC,              \
     (x).headingCode |= (((v) << 4) & SNMM_HEADING_CODE_1_MASK_PRC))

/*
 * Changeover (and acknowledge) COO, COA
 */
typedef struct
{
    ITS_OCTET   fsn[3];
}
SNMM_CHANGEOVER_PRC;

#define SNMM_CHANGEOVER_GET_FSN_PRC(x)                      \
    ((x).fsn[0] & 0x7FU)
#define SNMM_CHANGEOVER_SET_FSN_PRC(x, v)                   \
    ((x).fsn[0] = (v) & 0x7F0U)
#define SNMM_CHANGEOVER_GET_FSN_SAAL_PRC(x)                 \
    ((x).fsn[0] | ((x).fsn[1] << 8) | ((x).fsn[2] << 16))
#define SNMM_CHANGEOVER_SET_FSN_SAAL_PRC(x, v)              \
    ((x).fsn[0] = (v), (x).fsn[1] = ((v) >> 8),             \
     (x).fsn[2] = ((v) >> 16))

/*
 * Changeback (and acknowldedge) CBD, CBA
 */
typedef struct
{
    ITS_OCTET   cbcode;
}
SNMM_CHANGEBACK_PRC;

#define SNMM_CHANGEBACK_GET_CODE_PRC(x)         \
    ((x).cbcode)
#define SNMM_CHANGEBACK_SET_CODE_PRC(x, v)      \
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
    MTP3_POINT_CODE_PRC   dest;
}
SNMM_TRANSFER_STATE_PRC;

#define SNMM_TRANSFER_STATE_GET_DEST_PRC(x)     \
    (MTP3_PC_GET_VALUE_PRC((x).dest))
#define SNMM_TRANSFER_STATE_SET_DEST_PRC(x, v)  \
    (MTP3_PC_SET_VALUE_PRC((x).dest, (v)))

/*
 * Route set test messages RSP RSR RCP RCR
 */
typedef struct
{
    MTP3_POINT_CODE_PRC   dest;
}
SNMM_ROUTE_SET_TEST_PRC;

#define SNMM_ROUTE_SET_TEST_GET_DEST_PRC(x)     \
    (MTP3_PC_GET_VALUE_PRC((x).dest))
#define SNMM_ROUTE_SET_TEST_SET_DEST_PRC(x, v)  \
    (MTP3_PC_SET_VALUE_PRC((x).dest, (v)))

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
SNMM_DATALINK_CONNECT_PRC;

#define SNMM_DATALINK_CONNECT_GET_LINK_PRC(x)       \
    (((x).link[0]) |                                \
     (((x).link[1] & 0x0F) << 8))
#define SNMM_DATALINK_CONNECT_SET_LINK_PRC(x, v)    \
    ((x).link[0] = (v) & 0xFFU,                     \
     (x).link[2] = ((v) >> 8) & 0x0FU)

/*
 * route congestion test and transfer controlled RCT, TFC
 */
typedef struct
{
    MTP3_POINT_CODE_PRC   dest;
    ITS_OCTET               status;
}
SNMM_TRANSFER_CONTROL_PRC;

#define SNMM_TRANSFER_CONTROL_GET_DEST_PRC(x)           \
    MTP3_PC_GET_VALUE_PRC((x).dest)
#define SNMM_TRANSFER_CONTROL_SET_DEST_PRC(x, v)        \
    MTP3_PC_SET_VALUE_PRC((x).dest, (v))
#define SNMM_TRANSFER_CONTROL_GET_STATUS_PRC(x)         \
    ((x).status & 0x03U)
#define SNMM_TRANSFER_CONTROL_SET_STATUS_PRC(x, v)      \
    ((x).status = ((v) & 0x03U))

/*
 * traffic restart TRA TRW
 */

/*
 * User part unavailable UPU
 */
typedef struct
{
    MTP3_POINT_CODE_PRC   dest;
    ITS_OCTET               user;
}
SNMM_USER_PART_UNAVAILABLE_PRC;

#define SNMM_USER_PART_UNAVAIL_GET_DEST_PRC(x)          \
    (MTP3_PC_GET_VALUE_PRC((x).dest))
#define SNMM_USER_PART_UNAVAIL_SET_DEST_PRC(x, v)       \
    (MTP3_PC_SET_VALUE_PRC((x).dest, (v)))
#define SNMM_USER_PART_UNAVAIL_GET_USER_PRC(x)          \
    ((x).user & 0x0FU)
#define SNMM_USER_PART_UNAVAIL_SET_USER_PRC(x, v)       \
    ((x).user &= 0xF0U, (x).user |= ((v) & 0x0FU))
#define SNMM_USER_PART_UNAVAIL_GET_CAUSE_PRC(x)         \
    ((x).user & 0xF0U)
#define SNMM_USER_PART_UNAVAIL_SET_CAUSE_PRC(x, v)      \
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
SS7DLLAPI int SNMM_Encode_PRC(ITS_EVENT *ev, MTP3_HEADER_PRC *label,
                              SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_Decode_PRC(ITS_EVENT *ev, MTP3_HEADER_PRC *label,
                              SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SNMM_MESSAGE *msg);
#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* _ITS_SNMM_CMN_H_ */
