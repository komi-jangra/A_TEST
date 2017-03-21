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
 *  ID: $Id: sltm.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $
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
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 02:28:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.2  2004/12/16 00:46:02  randresol
 * LOG: Fix initial link alignment problems
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/26 00:29:15  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG:
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SLTM_TTC_H_
#define _ITS_SLTM_TTC_H_

#include <its.h>

#ident "$Id: sltm.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

#include <japan/mtp3.h>

/*
 * signalling link test messages
 */

/*
 * heading codes
 */
#define SLTM_HEADING_CODE_0_MASK_TTC   0xF0U
#define SLTM_HEADING_CODE_1_MASK_TTC   0x0FU

#define SLTM_HC0_SPARE_TTC          0x00U  /* spare */
#define SLTM_HC0_TST_TTC            0x02U  /* test messages */
#define SLTM_HC0_SRA_TTC            0x08U  /* H0 for SRA ack */

#define SLTM_HC0_GET_TTC(x)                                       \
    (((x).headingCode & SLTM_HEADING_CODE_0_MASK_TTC) >> 4)
#define SLTM_HC0_SET_TTC(x, v)                                    \
    ((x).headingCode &= ~SLTM_HEADING_CODE_0_MASK_TTC,            \
     (x).headingCode |= (((v) << 4) & SLTM_HEADING_CODE_0_MASK_TTC))
#define SLTM_HC1_GET_TTC(x)                                       \
    ((x).headingCode & SLTM_HEADING_CODE_1_MASK_TTC)
#define SLTM_HC1_SET_TTC(x, v)                                    \
    ((x).headingCode &= ~SLTM_HEADING_CODE_1_MASK_TTC,            \
     (x).headingCode |= ((v) & SLTM_HEADING_CODE_1_MASK_TTC))

/*
 * signalling link test
 */
#define SLTM_HC1_SLTM_TTC           0x03U   /* (SRT) signalling link test */
#define SLTM_HC1_SLTA_TTC           0x04U   /* (SRA) signalling link test ack */

#define SLTM_LINK_TEST_GET_SPARE_TTC(x)       \
    ((x).slc_li & 0x0FU)
#define SLTM_LINK_TEST_SET_SPARE_TTC(x, v)    \
    ((x).slc_li &= ~0x0FU,                      \
     (x).slc_li |= ((v) & 0x0FU))
#define SLTM_LINK_TEST_GET_LENGTH_TTC(x)      \
    (((x).slc_li >> 4) & 0x0FU)
#define SLTM_LINK_TEST_SET_LENGTH_TTC(x, v)   \
    ((x).slc_li &= ~0xF0U,                      \
     (x).slc_li |= (((v) << 4) & 0xF0U))
/* these don't exist for ITU */
#define SLTM_LINK_TEST_GET_SLC_TTC(x)
#define SLTM_LINK_TEST_SET_SLC_TTC(x, v)

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

SS7DLLAPI int SLTM_Encode_TTC(ITS_EVENT *ev, MTP3_HEADER_TTC *mtp3,
                                SLTM_MESSAGE *sltm);
SS7DLLAPI int SLTM_Decode_TTC(ITS_EVENT *ev, MTP3_HEADER_TTC *mtp3,
                                SLTM_MESSAGE *sltm);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SLTM_TTC_H_ */
