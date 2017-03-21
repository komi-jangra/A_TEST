/*********************************-*-C-*-************************************
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
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: mtp2.h,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.2  2006/07/18 15:39:38  sjaddu
 * LOG: Fix for Issue Id : #3946, #3955
 * LOG:
 * LOG: Revision 9.1.8.1  2005/09/14 16:23:29  lbana
 * LOG: Added macros for MTP2 implementation. Defined by Mitch Miers.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:16  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 06:50:52  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:12:58  mmiers
 * LOG: Changes for PRC family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.8  2002/01/10 22:59:57  mmiers
 * LOG: Change max msg size for MTP2 to allow for SAAL links.  Need to
 * LOG: start thinking about what needs to be done for MTP3
 * LOG:
 * LOG: Revision 5.7  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.5  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.4  2001/09/06 00:31:57  mmiers
 * LOG: Cut 3.
 * LOG:
 * LOG: Revision 5.3  2001/09/05 23:44:27  mmiers
 * LOG: MTP2 API try 2.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 23:06:41  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
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
 * LOG: Revision 4.1  2001/05/01 00:53:10  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:49  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 15:49:30  hdivoux
 * LOG: Corrections: (x).fsn instead of (x).bsn in FSN and FIB SET macros.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:19  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/10/18 14:48:30  mmiers
 * LOG:
 * LOG:
 * LOG: Add newline at end of file.
 * LOG:
 * LOG: Revision 1.3  1999/09/30 00:24:03  mmiers
 * LOG:
 * LOG:
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.2  1999/08/16 20:14:29  mmiers
 * LOG:
 * LOG:
 * LOG: Turn off tracing by default.
 * LOG:
 * LOG: Revision 1.1  1999/08/12 19:59:49  mmiers
 * LOG:
 * LOG:
 * LOG: New project for encode/decode of MTP2 messages.
 * LOG:
 *                 
 ****************************************************************************/

#if !defined(_ITS_MTP2_CCITT_H_)
#define _ITS_MTP2_CCITT_H_

#include <its.h>

#ident "$Id: mtp2.h,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $"

/*
 * signalling unit formats
 */
typedef struct
{
    ITS_OCTET   bsn;
    ITS_OCTET   fsn;
    ITS_OCTET   len;
    ITS_OCTET   sio;
}
MTP2_HEADER_CCITT;

#define MTP2_GET_BSN_CCITT(x) \
    ((x).bsn & 0x7FU)
#define MTP2_SET_BSN_CCITT(x, v) \
    ((x).bsn &= 0x80U, (x).bsn |= (v) & 0x7FU)

#define MTP2_GET_BIB_CCITT(x) \
    (((x).bsn & 0x80U) >> 7)
#define MTP2_SET_BIB_CCITT(x, v) \
    ((x).bsn &= 0x7FU, (x).bsn |= ((v) << 7) & 0x80U)

#define MTP2_GET_FSN_CCITT(x) \
    ((x).fsn & 0x7FU)
#define MTP2_SET_FSN_CCITT(x, v) \
    ((x).fsn &= 0x80U, (x).fsn |= (v) & 0x7FU)

#define MTP2_GET_FIB_CCITT(x) \
    (((x).fsn & 0x80U) >> 7)
#define MTP2_SET_FIB_CCITT(x, v) \
    ((x).fsn &= 0x7FU, (x).fsn |= ((v) << 7) & 0x80U)

#define MTP2_GET_SPARE_CCITT(x) \
    ((x).len & 0xC0U)
#define MTP2_SET_SPARE_CCITT(x, v) \
    ((x).len &= 0x3FU, (x).len |= (v) & 0xC0U)

#define MTP2_GET_LI_CCITT(x) \
    ((x).len & 0x3FU)
#define MTP2_SET_LI_CCITT(x, v) \
    ((x).len &= 0xC0, (x).len |= (v) & 0x3FU)

#define MTP2_GET_SIO_CCITT(x) \
    ((x).sio)
#define MTP2_SET_SIO_CCITT(x, v) \
    ((x).sio = (v))

#define MTP2_GET_STATUS_CCITT(x) \
    (MTP2_GET_SIO_CCITT(x) & 0x07U)
#define MTP2_SET_STATUS_CCITT(x, v) \
    MTP2_SET_SIO_CCITT(x, (v) & 0x07U)

#define MTP2_MSG_FISU_CCITT  0
#define MTP2_MSG_LSSU_CCITT  1
#define MTP2_MSG_MSU_CCITT   2

#define MTP2_MSG_TYPE_CCITT(x)                   \
    (MTP2_GET_LI_CCITT(x) == 0                   \
        ? MTP2_MSG_FISU_CCITT                    \
        : (MTP2_GET_LI_CCITT(x) == 1 ||          \
           MTP2_GET_LI_CCITT(x) == 2)            \
            ? MTP2_MSG_LSSU_CCITT                \
            : MTP2_MSG_MSU_CCITT)               

#define MTP2_GET_MSU_LEN_CCITT(x)        \
    (MTP2_GET_LI_CCITT(x) * 8)
#define MTP2_SET_MSU_LEN_CCITT(x, v)     \
    (MTP2_SET_LI_CCITT(x, ((v) + 7) / 8))

/*
 * allow for SAAL (was 272)
 */
#define MTP2_MAX_MSG_SIZE_CCITT          4096

/*
 * use of the short names is deprecated and may be removed
 * in a future release.
 */
#include <mtp2_sn.h>

/*
 * include common info
 */
#include <mtp2_cmn.h>

#ifndef __KERNEL__
#include <its_pprint.h>
#else
typedef int RINGBUF_Manager;
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:MTP2_
 *****************************************************************************
 *  Interface:
 *      MTP2_*
 *
 *  Purpose:
 *      Encode/decode MTP2 layer messages.
 *
 *  Usage:
 *      Note that the sif buffer WILL include the SIO.  That is needed
 *      by MTP3 to determine the destination/src UserPart
 *
 *****************************************************************************/
SS7DLLAPI int MTP2_Encode_CCITT(ITS_EVENT *ev, MTP2_HEADER_CCITT* hdr,
                                ITS_OCTET* sif, ITS_USHORT len);
SS7DLLAPI int MTP2_Decode_CCITT(ITS_EVENT *ev, MTP2_HEADER_CCITT* hdr,
                                ITS_OCTET* sif, ITS_USHORT* len);
SS7DLLAPI int MTP2_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                MTP2_HEADER_CCITT *hdr);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_MTP2_CCITT_H */

