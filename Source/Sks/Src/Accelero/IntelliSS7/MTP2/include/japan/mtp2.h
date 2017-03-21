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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.1  2005/12/21 06:30:56  yranade
 * LOG: Added macros for MTP2 implementation. Defined by Mitch Miers/lbana.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.2  2004/12/21 04:22:15  kannanp
 * LOG: match braces.
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 01:57:33  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/08 23:38:49  randresol
 * LOG: Start Japan SS7
 * LOG:
 * LOG:
 ****************************************************************************/

#if !defined(_ITS_MTP2_TTC_H_)
#define _ITS_MTP2_TTC_H_

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
MTP2_HEADER_TTC;

#define MTP2_GET_BSN_TTC(x) \
    ((x).bsn & 0x7FU)
#define MTP2_SET_BSN_TTC(x, v) \
    ((x).bsn &= 0x80U, (x).bsn |= (v) & 0x7FU)

#define MTP2_GET_BIB_TTC(x) \
    ((x).bsn & 0x80U)
#define MTP2_SET_BIB_TTC(x, v) \
    ((x).bsn &= 0x7FU, (x).bsn |= (v) & 0x80U)

#define MTP2_GET_FSN_TTC(x) \
    ((x).fsn & 0x7FU)
#define MTP2_SET_FSN_TTC(x, v) \
    ((x).fsn &= 0x80U, (x).fsn |= (v) & 0x7FU)

#define MTP2_GET_FIB_TTC(x) \
    ((x).fsn & 0x80U)
#define MTP2_SET_FIB_TTC(x, v) \
    ((x).fsn &= 0x7FU, (x).fsn |= (v) & 0x80U)

#define MTP2_GET_LI_TTC(x) \
    ((x).len & 0x3FU)
#define MTP2_SET_LI_TTC(x, v) \
    ((x).len &= 0xC0, (x).len |= (v) & 0x3FU)

#define MTP2_GET_SIO_TTC(x) \
    ((x).sio)
#define MTP2_SET_SIO_TTC(x, v) \
    ((x).sio = (v))

#define MTP2_MSG_FISU_TTC  0
#define MTP2_MSG_LSSU_TTC  1
#define MTP2_MSG_MSU_TTC   2

#define MTP2_MSG_TYPE_TTC(x)                   \
    (MTP2_GET_LI_TTC(x) == 0                   \
        ? MTP2_MSG_FISU_TTC                    \
        : (MTP2_GET_LI_TTC(x) == 1 ||          \
           MTP2_GET_LI_TTC(x) == 2)            \
            ? MTP2_MSG_LSSU_TTC                \
            : MTP2_MSG_MSU_TTC)               
/*    ) */

#define MTP2_GET_MSU_LEN_TTC(x)        \
    (MTP2_GET_LI_TTC(x) * 8)
#define MTP2_SET_MSU_LEN_TTC(x, v)     \
    (MTP2_SET_LI_TTC(x, ((v) + 7) / 8))

/*
 * allow for SAAL (was 272)
 */
#define MTP2_MAX_MSG_SIZE_TTC          4096

/*
 * include common info
 */
#include <mtp2_cmn.h>

#ifndef __KERNEL__
#include <its_pprint.h>
#else
typedef int RINGBUF_Manager;
#endif


/*
 * use of the short names is deprecated and may be removed
 * in a future release.
 */
#include <mtp2_sn.h>

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
SS7DLLAPI int MTP2_Encode_TTC(ITS_EVENT *ev, MTP2_HEADER_TTC* hdr,
                                ITS_OCTET* sif, ITS_USHORT len);
SS7DLLAPI int MTP2_Decode_TTC(ITS_EVENT *ev, MTP2_HEADER_TTC* hdr,
                                ITS_OCTET* sif, ITS_USHORT* len);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_MTP2_TTC_H */

