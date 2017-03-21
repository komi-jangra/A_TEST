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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:12  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:50:38  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:20  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:16  cvsadmin
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
 * LOG: Revision 3.2  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:32  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:42  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:48:00  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:50  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:16:01  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:40  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:31:02  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:13  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:33:07  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * real2prim.c - real to presentation element
 */

#include <asn-c/AsnC.h>

#ident "$Id: real2prim.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

PE
real2prim (double d, PElementClass pclass, PElementID id)
{
    PE pe;
    double	mant, nm;
    int	exponent;
    int	expsign;
    int	parts[sizeof (double)];
    int	sign, i, maxi = 0, mask;
    int	n, explen;
    PElementData	dp;
    
    if ((pe = pe_alloc (pclass, PE_FORM_PRIM, id)) == NULL)
    {
        return NULL;
    }
    
    if (d == 0.0)
    {
        return pe;
    }
    
    mant = frexp (d, &exponent);
    
    if (mant < 0.0)
    {
        sign = -1;
        mant = -mant;
    }
    else
    {
        sign = 1;
    }
    
    nm = mant;
    for (i = 0; i < sizeof (double) ; i++)
    {
        int intnm;
        
        nm *= (1<<8);
        intnm = ((int)nm) & 0xff;
        nm -= intnm;
        
        if (intnm)
        {
            maxi = i + 1;
        }
        
        parts[i] = intnm;
    }
    
    exponent -= 8 * maxi;
    
    expsign = exponent >= 0 ? exponent : exponent ^ (-1);
    mask = 0x1ff << (((n = sizeof exponent) - 1) * 8 - 1);
    while (n > 1 && (expsign & mask) == 0)
    {
        mask >>= 8, n--;
    }
    
    explen = n;
    if (n > 3)
    {
        n ++;
    }
    
    if ((pe->pe_prim = PEDalloc (n + maxi + 1)) == NULL)
    {
        pe_free (pe);
        
        return NULL;
    }
    
    dp = pe->pe_prim + (pe->pe_len = n + maxi + 1);
    
    for (; maxi > 0; maxi --)
    {
        *--dp = (ITS_OCTET)(parts[maxi - 1]);
    }
    
    for (n = explen; n-- > 0; exponent >>= 8)
    {
        *--dp = (ITS_OCTET)(exponent & 0xff);
    }

    if (explen > 3)
    {
        *--dp = (ITS_OCTET)(explen & 0xff);
    }
    
    switch (explen)
    {
    case 1:
        explen = PE_REAL_B_EF1;
        break;
    case 2:
        explen = PE_REAL_B_EF2;
        break;
    case 3:
        explen = PE_REAL_B_EF3;
        break;
    default:
        explen = PE_REAL_B_EF3;
        break;
    }
    
    *--dp = (ITS_OCTET)(PE_REAL_BINENC
                | PE_REAL_B_B2
                | (sign == -1 ? PE_REAL_B_S : 0)
                | explen);
    
    return pe;
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

