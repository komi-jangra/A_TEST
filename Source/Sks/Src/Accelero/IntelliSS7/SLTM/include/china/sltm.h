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
 *  ID: $Id: sltm.h,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:24  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:31  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 14:03:32  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/22 20:38:41  omayor
 * LOG: Missing macros for LINK_TEST caused run time unresolved symbols.
 * LOG:
 * LOG: Revision 1.1  2002/07/03 15:59:00  mmiers
 * LOG: Changes for china family
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SLTM_PRC_H_
#define _ITS_SLTM_PRC_H_

#include <its.h>

#ident "$Id: sltm.h,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $"

#include <china/mtp3.h>

/*
 * signalling link test messages
 */

/*
 * heading codes
 */
#define SLTM_HEADING_CODE_0_MASK_PRC   0x0FU
#define SLTM_HEADING_CODE_1_MASK_PRC   0xF0U

#define SLTM_HC0_SPARE_PRC          0x00U  /* spare */
#define SLTM_HC0_TST_PRC            0x01U  /* test messages */

#define SLTM_HC0_GET_PRC(x)                                         \
    ((x).headingCode & SLTM_HEADING_CODE_0_MASK_PRC)
#define SLTM_HC0_SET_PRC(x, v)                                      \
    ((x).headingCode &= ~SLTM_HEADING_CODE_0_MASK_PRC,              \
     (x).headingCode |= ((v) & SLTM_HEADING_CODE_0_MASK_PRC))
#define SLTM_HC1_GET_PRC(x)                                         \
    (((x).headingCode & SLTM_HEADING_CODE_1_MASK_PRC) >> 4)
#define SLTM_HC1_SET_PRC(x, v)                                      \
    ((x).headingCode &= ~SLTM_HEADING_CODE_1_MASK_PRC,              \
     (x).headingCode |= (((v) << 4) & SLTM_HEADING_CODE_1_MASK_PRC))

/*
 * signalling link test
 */
#define SLTM_HC1_SLTM_PRC           0x01U   /* signalling link test */
#define SLTM_HC1_SLTA_PRC           0x02U   /* signalling link test ack */

#define SLTM_LINK_TEST_GET_SPARE_PRC(x)         \
    ((x).slc_li & 0x0FU)
#define SLTM_LINK_TEST_SET_SPARE_PRC(x, v)      \
    ((x).slc_li &= ~0x0FU,                      \
     (x).slc_li |= ((v) & 0x0FU))
#define SLTM_LINK_TEST_GET_LENGTH_PRC(x)        \
    (((x).slc_li >> 4) & 0x0FU)
#define SLTM_LINK_TEST_SET_LENGTH_PRC(x, v)     \
    ((x).slc_li &= ~0xF0U,                      \
     (x).slc_li |= (((v) << 4) & 0xF0U))
/* these don't exist for CHINA ?? TODO Find out... */
#define SLTM_LINK_TEST_GET_SLC_PRC(x)
#define SLTM_LINK_TEST_SET_SLC_PRC(x, v)

/*
 * get shared defs
 */
#include <sltm_cmn.h>

/*
 * use of short names is deprecated and may be removed in a
 * future release.
 */
#include <sltm_sn.h>

#if defined(__cplusplus)
extern "C"
{
#endif

SS7DLLAPI int SLTM_Encode_PRC(ITS_EVENT *ev, MTP3_HEADER_PRC *mtp3,
                              SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_Decode_PRC(ITS_EVENT *ev, MTP3_HEADER_PRC *mtp3,
                              SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SLTM_MESSAGE *msg);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SLTM_PRC_H_ */
