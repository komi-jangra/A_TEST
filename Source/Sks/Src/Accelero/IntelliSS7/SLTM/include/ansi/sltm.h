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
 * LOG: Revision 7.1  2002/08/26 22:09:26  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 19:16:42  mmiers
 * LOG: Get engine in sync, add missing C++ guards in headers.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:51  mmiers
 * LOG: Start PR6.
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
 * LOG: Revision 3.1  2000/08/16 00:02:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/06/22 23:11:17  rsonak
 * LOG: Fix macros to set the right fields.
 * LOG:
 * LOG: Revision 2.2  2000/05/17 02:11:45  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some syntax errors in sltm, add missing includes to TALI.
 * LOG:
 * LOG: Revision 2.1  2000/05/11 20:44:29  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the IMAL heartbeat.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:51  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/10/06 22:19:45  mmiers
 * LOG:
 * LOG:
 * LOG: Update new user part, integrate into licensing scheme.
 * LOG:
 * LOG: Revision 1.3  1999/10/06 20:43:50  mmiers
 * LOG:
 * LOG:
 * LOG: Updated files and added code.
 * LOG:
 * LOG: Revision 1.2  1999/10/06 20:35:45  mmiers
 * LOG:
 * LOG:
 * LOG: New user part.
 * LOG:
 * LOG: Revision 1.1  1999/10/06 16:22:59  mmiers
 * LOG:
 * LOG:
 * LOG: Add new user part for signalling link test messages.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SLTM_ANSI_H_
#define _ITS_SLTM_ANSI_H_

#include <its.h>

#ident "$Id: sltm.h,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $"

#include <ansi/mtp3.h>

/*
 * signalling link test messages
 */

/*
 * heading codes
 */
#define SLTM_HEADING_CODE_0_MASK_ANSI   0x0FU
#define SLTM_HEADING_CODE_1_MASK_ANSI   0xF0U

#define SLTM_HC0_SPARE_ANSI          0x00U  /* spare */
#define SLTM_HC0_TST_ANSI            0x01U  /* test messages */

#define SLTM_HC0_GET_ANSI(x)                                        \
    ((x).headingCode & SLTM_HEADING_CODE_0_MASK_ANSI)
#define SLTM_HC0_SET_ANSI(x, v)                                     \
    ((x).headingCode &= ~SLTM_HEADING_CODE_0_MASK_ANSI,             \
     (x).headingCode |= ((v) & SLTM_HEADING_CODE_0_MASK_ANSI))
#define SLTM_HC1_GET_ANSI(x)                                        \
    (((x).headingCode & SLTM_HEADING_CODE_1_MASK_ANSI) >> 4)
#define SLTM_HC1_SET_ANSI(x, v)                                     \
    ((x).headingCode &= ~SLTM_HEADING_CODE_1_MASK_ANSI,             \
     (x).headingCode |= (((v) << 4) & SLTM_HEADING_CODE_1_MASK_ANSI))

/*
 * signalling link test
 */
#define SLTM_HC1_SLTM_ANSI          0x01U   /* signalling link test */
#define SLTM_HC1_SLTA_ANSI          0x02U   /* signalling link test ack */

#define SLTM_LINK_TEST_GET_SLC_ANSI(x)          \
    ((x).slc_li & 0x0FU)
#define SLTM_LINK_TEST_SET_SLC_ANSI(x, v)       \
    ((x).slc_li &= ~0x0FU,                      \
     (x).slc_li |= ((v) & 0x0FU))
#define SLTM_LINK_TEST_GET_LENGTH_ANSI(x)       \
    (((x).slc_li >> 4) & 0x0FU)
#define SLTM_LINK_TEST_SET_LENGTH_ANSI(x, v)    \
    ((x).slc_li &= ~0xF0U,                      \
     (x).slc_li |= (((v) << 4) & 0xF0U))

/*
 * get shared defs
 */
#include <sltm_cmn.h>

/*
 * use of short names is deprecated and may be removed in a
 * future release.
 */
#include <sltm_sn.h>

/*
 * API
 */
#ifdef __cplusplus
extern "C"
{
#endif

SS7DLLAPI int SLTM_Encode_ANSI(ITS_EVENT *ev, MTP3_HEADER_ANSI *mtp3,
                               SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_Decode_ANSI(ITS_EVENT *ev, MTP3_HEADER_ANSI *mtp3,
                               SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SLTM_MESSAGE *msg);

#ifdef __cplusplus
}
#endif

#endif /* _ITS_SLTM_ANSI_H_ */
