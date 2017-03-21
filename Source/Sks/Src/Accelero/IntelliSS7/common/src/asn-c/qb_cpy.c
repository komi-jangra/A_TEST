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
 *  ID: $Id: qb_cpy.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:12  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:01  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:50:32  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:20  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:15  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:16  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:02  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/04/27 16:49:38  mmiers
 * LOG:
 * LOG:
 * LOG: Remove spurious carriage returns.
 * LOG:
 * LOG: Revision 2.1  2000/04/13 21:28:23  mmiers
 * LOG:
 * LOG:
 * LOG: More changes from Saritel integration.
 * LOG:
 *
 *****************************************************************************/
/*
 * qb_cpy.c - qbuf to qbuf
 */

#include <asn-c/AsnC.h>

struct qbuf*
qb_cpy(struct qbuf* q)
{
    char *str = qb2str(q);
    int len = qb2len(q);
    struct qbuf* p = str2qb(str, len, 0);

    if (str)
    {
        free(str);
    }

    return p;
}

/****************************************************************************
 *
 * The ISODE is openly available but is NOT in the public domain.  You
 * are allowed and encouraged to take this software and build commercial
 * products.  However, as a condition of use, you are required to ``hold
 * harmless'' all contributors.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that this notice and the reference to this notice appearing in each
 * software module be retained unaltered, and that the name of any
 * contributors shall not be used in advertising or publicity pertaining
 * to distribution of the software without specific written prior permission.
 * No contributor makes any representations about the suitability of this
 * software for any purpose.  It is provided ``as is'' without express or
 * implied warranty.
 * 
 *      ALL CONTRIBUTORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 *      SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 *      AND FITNESS FOR THE PARTICULAR PURPOSE, TITLE, AND NON-INFRINGEMENT.
 *
 *      IN NO EVENT SHALL ANY CONTRIBUTOR BE LIABLE FOR ANY SPECIAL,
 *      INDIRECT OR CONSEQUENTIAL DAMAGES, WHETHER IN CONTRACT, TORT, OR
 *      OTHER FORM OF ACTION, ARISING OUT OF OR IN CONNECTION WITH, THE
 *      USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ***************************************************************************/

