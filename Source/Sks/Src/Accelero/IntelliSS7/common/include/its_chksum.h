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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/01/15 23:04:56  mmiers
 * LOG: Add CRC32C.  Update M2PA as far as I can without SCTP support.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/07/03 21:16:22  mmiers
 * LOG: Move RM and DSM.
 * LOG:
 * LOG: Revision 4.2  2001/07/03 20:32:49  mmiers
 * LOG: Add CRC-32
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.7  2001/03/06 02:50:16  mmiers
 * LOG: Fixups for DLLs, make
 * LOG:
 * LOG: Revision 3.6  2001/03/05 23:54:56  mmiers
 * LOG: Prep for dynamic linking.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2000/10/03 21:17:04  mmiers
 * LOG: Today's installment.  Getting real close now.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:09  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/05/24 18:55:48  mmiers
 * LOG:
 * LOG:
 * LOG: Warning removal ("incomplete last line")
 * LOG:
 * LOG: Revision 1.1  2000/05/22 17:00:24  mmiers
 * LOG:
 * LOG:
 * LOG: Add Adler32 generation
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_ADLER_H)
#define ITS_ADLER_H

#ident "$Id: its_chksum.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:ADLER_*
 *****************************************************************************
 *  Interface:
 *      ADLER_*
 *
 *  Purpose:
 *      The ADLER interface is used to generate checksums.  The routines are
 *      required both for RUDP and SCTP.
 *
 *
 *  Usage:
 *
 *****************************************************************************/
ITSDLLAPI ITS_UINT    ADLER_UpdateChksum32(ITS_UINT adler,
                                           ITS_OCTET *buf, ITS_UINT len);
ITSDLLAPI ITS_UINT    ADLER_Chksum32(ITS_OCTET *buf, ITS_UINT len);

ITSDLLAPI ITS_USHORT  IP_Chksum16(ITS_OCTET *buf, ITS_UINT size);

ITSDLLAPI ITS_UINT    CRC_Chksum32(const ITS_OCTET *buf, ITS_UINT len);
ITSDLLAPI ITS_UINT    CRC_Chksum32C(const ITS_OCTET *buf, ITS_UINT len);

#if defined(__cplusplus)
}
#endif

#endif /* ITS_ADLER_H */
