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
 * LOG: Revision 8.3  2005/03/21 13:50:32  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 14:05:43  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:31  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/17 19:53:01  randresol
 * LOG: fix bug in macro SNMM_USER_PART_UNAVAIL_GET_CAUSE
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.12  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.11  2001/11/14 23:18:36  mmiers
 * LOG: Conformance testing fixes.
 * LOG:
 * LOG: Revision 5.10  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.9  2001/11/01 19:41:34  vnitin
 * LOG: Changed EMERG_CHANGEOVER_SET_SLC def
 * LOG:
 * LOG: Revision 5.8  2001/10/30 23:53:01  mmiers
 * LOG: Today's fixes.
 * LOG:
 * LOG: Revision 5.7  2001/10/30 17:22:24  rsonak
 * LOG: fixed bug in settting Changeback code .
 * LOG:
 * LOG: Revision 5.6  2001/10/30 16:43:15  mmiers
 * LOG: Macro fixes.
 * LOG:
 * LOG: Revision 5.5  2001/10/18 19:16:42  mmiers
 * LOG: Get engine in sync, add missing C++ guards in headers.
 * LOG:
 * LOG: Revision 5.4  2001/09/14 17:37:25  rsonak
 * LOG: Typo in Changeback macro (O was used for 0)
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/08/30 19:53:46  vnitin
 * LOG: Bug fix in macro
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/08/07 18:36:03  mmiers
 * LOG: Found a bunch of typos.
 * LOG:
 * LOG: Revision 4.3  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 00:18:19  mmiers
 * LOG: Start removing the old short names.
 * LOG: Use the heap instead of buffers if the heap implementation is smart.
 * LOG: GCC 3.0 and later are ANSI/ISO C++.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:34  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:56  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/10/06 22:08:57  mmiers
 * LOG:
 * LOG:
 * LOG: Correct codec.
 * LOG:
 * LOG: Revision 1.2  1999/10/06 20:22:13  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize.
 * LOG:
 * LOG: Revision 1.1  1999/10/06 15:59:54  mmiers
 * LOG:
 * LOG:
 * LOG: Add new user part for signalling network management messages.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SNMM_ANSI_H_
#define _ITS_SNMM_ANSI_H_

#include <its.h>

#ident "$Id: snmm.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

#include <ansi/mtp3.h>

/*
 * signalling network and management messages
 */

/*
 * heading codes
 */
#define SNMM_HEADING_CODE_0_MASK_ANSI   0x0FU
#define SNMM_HEADING_CODE_1_MASK_ANSI   0xF0U

#define SNMM_HC0_SPARE_ANSI     0x00U  /* spare */
#define SNMM_HC0_CHM_ANSI       0x01U  /* changeover/changeback */
#define SNMM_HC0_ECM_ANSI       0x02U  /* emergency changeover */
#define SNMM_HC0_FCM_ANSI       0x03U  /* transfer controlled/congestion test */
#define SNMM_HC0_TFM_ANSI       0x04U  /* transfer prohibit/allow/restrict */
#define SNMM_HC0_RSM_ANSI       0x05U  /* route set test */
#define SNMM_HC0_MIM_ANSI       0x06U  /* management inhibit */
#define SNMM_HC0_TRM_ANSI       0x07U  /* traffic restart */
#define SNMM_HC0_DLM_ANSI       0x08U  /* data link connection */
#define SNMM_HC0_UFC_ANSI       0x0AU  /* user flow control */

#define SNMM_HC1_COO_ANSI       0x01U   /* changeover */
#define SNMM_HC1_COA_ANSI       0x02U   /* changeover ack */
#define SNMM_HC1_XCO_ANSI       0x03U   /* extended changeover */
#define SNMM_HC1_XCA_ANSI       0x04U   /* extended changeover ack */
#define SNMM_HC1_CBD_ANSI       0x05U   /* changeback */
#define SNMM_HC1_CBA_ANSI       0x06U   /* changeback ack */
#define SNMM_HC1_ECO_ANSI       0x01U   /* emergency changeover */
#define SNMM_HC1_ECA_ANSI       0x02U   /* emergency changeover ack */
#define SNMM_HC1_TFP_ANSI       0x01U   /* transfer prohibited */
#define SNMM_HC1_TCP_ANSI       0x02U   /* transfer cluster prohibited */
#define SNMM_HC1_TFR_ANSI       0x03U   /* transfer restricted */
#define SNMM_HC1_TCR_ANSI       0x04U   /* transfer cluster restricted */
#define SNMM_HC1_TFA_ANSI       0x05U   /* transfer alloweded */
#define SNMM_HC1_TCA_ANSI       0x06U   /* transfer cluster allowed */
#define SNMM_HC1_RSP_ANSI       0x01U   /* route set test prohibited */
#define SNMM_HC1_RSR_ANSI       0x02U   /* route set test restricted */
#define SNMM_HC1_RCP_ANSI       0x03U   /* route set test cluster prohibited */
#define SNMM_HC1_RCR_ANSI       0x04U   /* route set test cluster restricted */
#define SNMM_HC1_LIN_ANSI       0x01U   /* link inhibit */
#define SNMM_HC1_LUN_ANSI       0x02U   /* link uninhibit */
#define SNMM_HC1_LIA_ANSI       0x03U   /* link inhibit ack */
#define SNMM_HC1_LUA_ANSI       0x04U   /* link uninhibit ack */
#define SNMM_HC1_LID_ANSI       0x05U   /* link inhibit denied */
#define SNMM_HC1_LFU_ANSI       0x06U   /* link force uninhibit */
#define SNMM_HC1_LLI_ANSI       0x07U   /* link local inhibit test */
#define SNMM_HC1_LRI_ANSI       0x08U   /* link remote inhibit test */
#define SNMM_HC1_DLC_ANSI       0x01U   /* data link connect */
#define SNMM_HC1_CSS_ANSI       0x02U   /* connection successful */
#define SNMM_HC1_CNS_ANSI       0x03U   /* connection not successful */
#define SNMM_HC1_CNP_ANSI       0x04U   /* connection not possible */
#define SNMM_HC1_RCT_ANSI       0x01U   /* route congestion test */
#define SNMM_HC1_TFC_ANSI       0x02U   /* transfer controlled */
#define SNMM_HC1_TRA_ANSI       0x01U   /* traffic restart allowed */
#define SNMM_HC1_TRW_ANSI       0x02U   /* traffer restart waiting */
#define SNMM_HC1_UPU_ANSI       0x01U   /* user part unavailable */

#define SNMM_HC0_GET_ANSI(x)                                        \
    ((x).headingCode & SNMM_HEADING_CODE_0_MASK_ANSI)
#define SNMM_HC0_SET_ANSI(x, v)                                     \
    ((x).headingCode &= ~SNMM_HEADING_CODE_0_MASK_ANSI,             \
     (x).headingCode |= ((v) & SNMM_HEADING_CODE_0_MASK_ANSI))
#define SNMM_HC1_GET_ANSI(x)                                        \
    (((x).headingCode & SNMM_HEADING_CODE_1_MASK_ANSI) >> 4)
#define SNMM_HC1_SET_ANSI(x, v)                                     \
    ((x).headingCode &= ~SNMM_HEADING_CODE_1_MASK_ANSI,             \
     (x).headingCode |= (((v) << 4) & SNMM_HEADING_CODE_1_MASK_ANSI))

/*
 * Changeover (and acknowledge) COO, COA
 */
typedef struct
{
    ITS_OCTET   slc_fsn[4];
}
SNMM_CHANGEOVER_ANSI;

#define SNMM_CHANGEOVER_GET_SLC_ANSI(x)         \
    ((x).slc_fsn[0] & 0x0FU)
#define SNMM_CHANGEOVER_SET_SLC_ANSI(x, v)      \
    ((x).slc_fsn[0] &= ~0x0FU,                  \
     (x).slc_fsn[0] |= ((v) & 0x0FU))
#define SNMM_CHANGEOVER_GET_FSN_ANSI(x)         \
    (((x).slc_fsn[0] >> 4) |                    \
     (((x).slc_fsn[1] & 0xFFU) << 4))
#define SNMM_CHANGEOVER_SET_FSN_ANSI(x, v)      \
    ((x).slc_fsn[0] &= ~0xF0U,                  \
     (x).slc_fsn[0] |= ((v) << 4) & 0xF0U,      \
     (x).slc_fsn[1] = ((v) >> 4) & 0xFFU)
#define SNMM_CHANGEOVER_GET_FSN_SAAL_ANSI(x)    \
    (((x).slc_fsn[0] >> 4) |                    \
     ((x).slc_fsn[1] << 4) |                    \
     ((x).slc_fsn[2] << 12) |                   \
     (((x).slc_fsn[3] & 0x0FU) << 20))
#define SNMM_CHANGEOVER_SET_FSN_SAAL_ANSI(x, v) \
    ((x).slc_fsn[0] &= ~0xF0U,                  \
     (x).slc_fsn[0] |= ((v) << 4) & 0xF0U,      \
     (x).slc_fsn[1] = ((v) >> 4) & 0xFFU,       \
     (x).slc_fsn[2] = ((v) >> 12) & 0xFFU,      \
     (x).slc_fsn[3] = ((v) >> 20) & 0x0FU)

/*
 * Changeback (and acknowldedge) CBD, CBA
 */
typedef struct
{
    ITS_OCTET   slc_cbcode[2];
}
SNMM_CHANGEBACK_ANSI;

#define SNMM_CHANGEBACK_GET_SLC_ANSI(x)        \
    ((x).slc_cbcode[0] & 0x0FU)
#define SNMM_CHANGEBACK_SET_SLC_ANSI(x, v)     \
    ((x).slc_cbcode[0] &= ~0x0FU,              \
     (x).slc_cbcode[0] |= ((v) & 0x0FU))
#define SNMM_CHANGEBACK_GET_CODE_ANSI(x)       \
    (((x).slc_cbcode[0] >> 4) |                \
     (((x).slc_cbcode[1] & 0x0FU) << 4))
#define SNMM_CHANGEBACK_SET_CODE_ANSI(x, v)    \
    ((x).slc_cbcode[0] &= ~0xF0U,               \
     (x).slc_cbcode[0] |= ((v) << 4) & 0xF0U,  \
     (x).slc_cbcode[1] = 0,                    \
     (x).slc_cbcode[1] |= ((v) >> 4) & 0x0FU)

/*
 * Emergency changeover (and acknowledge) ECO, ECA
 */
typedef struct
{
    ITS_OCTET   slc;
}
SNMM_EMERG_CHANGEOVER_ANSI;

#define SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI(x)       \
    ((x).slc & 0x0FU)
#define SNMM_EMERG_CHANGEOVER_SET_SLC_ANSI(x, v)    \
    ((x).slc = ((v) & 0x0FU))  

/*
 * Transfer Prohibited, Allowed, and Restricted
 * TFP, TCP, TFR, TCR, TFA, TCA
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    dest;
}
SNMM_TRANSFER_STATE_ANSI;

#define SNMM_TRANSFER_STATE_GET_DEST_ANSI(x) \
    (MTP3_PC_GET_VALUE_ANSI((x).dest))
#define SNMM_TRANSFER_STATE_SET_DEST_ANSI(x, v) \
    (MTP3_PC_SET_VALUE_ANSI((x).dest, (v)))

/*
 * Route set test messages RSP RSR RCP RCR
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    dest;
}
SNMM_ROUTE_SET_TEST_ANSI;

#define SNMM_ROUTE_SET_TEST_GET_DEST_ANSI(x) \
    (MTP3_PC_GET_VALUE_ANSI((x).dest))
#define SNMM_ROUTE_SET_TEST_SET_DEST_ANSI(x, v) \
    (MTP3_PC_SET_VALUE_ANSI((x).dest, (v)))

/*
 * Inhibit messages
 * LIN LUN LIA LUA LID LFU LLI LRI
 */
typedef struct
{
    ITS_OCTET   slc;
}
SNMM_INHIBIT_ANSI;

#define SNMM_INHIBIT_GET_SLC_ANSI(x)    \
    ((x).slc & 0x0FU)
#define SNMM_INHIBIT_SET_SLC_ANSI(x, v) \
    ((x).slc = ((v) & 0x0FU))

/*
 * Signalling data link connection order and results
 * DLC CSS CNS CNP
 */
typedef struct
{
    ITS_OCTET   slc_link[3];
}
SNMM_DATALINK_CONNECT_ANSI;

#define SNMM_DATALINK_CONNECT_GET_SLC_ANSI(x)       \
    ((x).slc_link[0] & 0x0FU)
#define SNMM_DATALINK_CONNECT_SET_SLC_ANSI(x, v)    \
    ((x).slc_link[0] &= ~0x0FU,                     \
     (x).slc_link[0] |= ((v) & 0x0FU))
#define SNMM_DATALINK_CONNECT_GET_LINK_ANSI(x)      \
    (((x).slc_link[0] >> 4) |                       \
     ((x).slc_link[1] << 4) |                       \
     (((x).slc_link[2] & 0x03) << 8))
#define SNMM_DATALINK_CONNECT_SET_LINK_ANSI(x, v)   \
    ((x).slc_link[0] &= ~0xF0U,                     \
     (x).slc_link[0] |= ((v) << 4) & 0xF0U,         \
     (x).slc_link[1] = ((v) >> 4) & 0xFFU,          \
     (x).slc_link[2] = ((v) >> 8) & 0x03U)

typedef struct
{
    ITS_OCTET   slc;
}
SNMM_DATALINK_CONN_ACK_ANSI;

#define SNMM_DATALINK_CONN_ACK_GET_SLC_ANSI(x)    \
    ((x).slc & 0x0FU)
#define SNMM_DATALINK_CONN_ACK_SET_SLC_ANSI(x, v) \
    ((x).slc = ((v) & 0x0FU))

/*
 * route congestion test and transfer controlled RCT, TFC
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    dest;
    ITS_OCTET               status;
}
SNMM_TRANSFER_CONTROL_ANSI;

#define SNMM_TRANSFER_CONTROL_GET_DEST_ANSI(x) \
    (MTP3_PC_GET_VALUE_ANSI((x).dest))
#define SNMM_TRANSFER_CONTROL_SET_DEST_ANSI(x, v) \
    (MTP3_PC_SET_VALUE_ANSI((x).dest, (v)))
#define SNMM_TRANSFER_CONTROL_GET_STATUS_ANSI(x)    \
    ((x).status & 0x03U)
#define SNMM_TRANSFER_CONTROL_SET_STATUS_ANSI(x, v) \
    ((x).status = ((v) & 0x03U))

/*
 * traffic restart TRA TRW
 */

/*
 * User part unavailable UPU
 */
typedef struct
{
    MTP3_POINT_CODE_ANSI    dest;
    ITS_OCTET               user;
}
SNMM_USER_PART_UNAVAILABLE_ANSI;

#define SNMM_USER_PART_UNAVAIL_GET_DEST_ANSI(x) \
    (MTP3_PC_GET_VALUE_ANSI((x).dest))
#define SNMM_USER_PART_UNAVAIL_SET_DEST_ANSI(x, v) \
    (MTP3_PC_SET_VALUE_ANSI((x).dest, (v)))
#define SNMM_USER_PART_UNAVAIL_GET_USER_ANSI(x)    \
    ((x).user & 0x0FU)
#define SNMM_USER_PART_UNAVAIL_SET_USER_ANSI(x, v) \
    ((x).user &= 0xF0U, (x).user |= ((v) & 0x0FU))
#define SNMM_USER_PART_UNAVAIL_GET_CAUSE_ANSI(x)    \
    ((x).user & 0xF0U)
#define SNMM_USER_PART_UNAVAIL_SET_CAUSE_ANSI(x, v) \
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
 * API
 */
#ifdef __cplusplus
extern "C"
{
#endif

SS7DLLAPI int SNMM_Encode_ANSI(ITS_EVENT *ev, MTP3_HEADER_ANSI *label,
                               SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_Decode_ANSI(ITS_EVENT *ev, MTP3_HEADER_ANSI *label,
                               SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SNMM_MESSAGE *msg);

#ifdef __cplusplus
}
#endif

#endif /* _ITS_SNMM_ANSI_H_ */
