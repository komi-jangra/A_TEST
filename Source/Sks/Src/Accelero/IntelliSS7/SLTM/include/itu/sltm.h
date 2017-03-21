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
 * LOG: Revision 7.1  2002/08/26 22:09:30  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/15 19:21:34  mmiers
 * LOG: Dummy macros for IMAL
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 19:55:46  mmiers
 * LOG: Convert to long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
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
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/06/22 23:11:17  rsonak
 * LOG: Fix macros to set the right fields.
 * LOG:
 * LOG: Revision 2.1  2000/05/11 20:44:30  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the IMAL heartbeat.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:51  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/10/06 22:19:46  mmiers
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
 * LOG: Revision 1.1  1999/10/06 16:23:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add new user part for signalling link test messages.
 * LOG:
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SLTM_CCITT_H_
#define _ITS_SLTM_CCITT_H_

#include <its.h>

#ident "$Id: sltm.h,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $"

#include <itu/mtp3.h>

/*
 * signalling link test messages
 */

/*
 * heading codes
 */
#define SLTM_HEADING_CODE_0_MASK_CCITT   0x0FU
#define SLTM_HEADING_CODE_1_MASK_CCITT   0xF0U

#define SLTM_HC0_SPARE_CCITT          0x00U  /* spare */
#define SLTM_HC0_TST_CCITT            0x01U  /* test messages */

#define SLTM_HC0_GET_CCITT(x)                                       \
    ((x).headingCode & SLTM_HEADING_CODE_0_MASK_CCITT)
#define SLTM_HC0_SET_CCITT(x, v)                                    \
    ((x).headingCode &= ~SLTM_HEADING_CODE_0_MASK_CCITT,            \
     (x).headingCode |= ((v) & SLTM_HEADING_CODE_0_MASK_CCITT))
#define SLTM_HC1_GET_CCITT(x)                                       \
    (((x).headingCode & SLTM_HEADING_CODE_1_MASK_CCITT) >> 4)
#define SLTM_HC1_SET_CCITT(x, v)                                    \
    ((x).headingCode &= ~SLTM_HEADING_CODE_1_MASK_CCITT,            \
     (x).headingCode |= (((v) << 4) & SLTM_HEADING_CODE_1_MASK_CCITT))

/*
 * signalling link test
 */
#define SLTM_HC1_SLTM_CCITT           0x01U   /* signalling link test */
#define SLTM_HC1_SLTA_CCITT           0x02U   /* signalling link test ack */

#define SLTM_LINK_TEST_GET_SPARE_CCITT(x)       \
    ((x).slc_li & 0x0FU)
#define SLTM_LINK_TEST_SET_SPARE_CCITT(x, v)    \
    ((x).slc_li &= ~0x0FU,                      \
     (x).slc_li |= ((v) & 0x0FU))
#define SLTM_LINK_TEST_GET_LENGTH_CCITT(x)      \
    (((x).slc_li >> 4) & 0x0FU)
#define SLTM_LINK_TEST_SET_LENGTH_CCITT(x, v)   \
    ((x).slc_li &= ~0xF0U,                      \
     (x).slc_li |= (((v) << 4) & 0xF0U))
/* these don't exist for ITU */
#define SLTM_LINK_TEST_GET_SLC_CCITT(x)
#define SLTM_LINK_TEST_SET_SLC_CCITT(x, v)

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

SS7DLLAPI int SLTM_Encode_CCITT(ITS_EVENT *ev, MTP3_HEADER_CCITT *mtp3,
                                SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_Decode_CCITT(ITS_EVENT *ev, MTP3_HEADER_CCITT *mtp3,
                                SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SLTM_MESSAGE *msg);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SLTM_CCITT_H_ */
