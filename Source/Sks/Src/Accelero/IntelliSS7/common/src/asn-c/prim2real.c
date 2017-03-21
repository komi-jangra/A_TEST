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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:11  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:01  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:50:16  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:19  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:15  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:17  mmiers
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
 * LOG: Revision 3.3  2001/03/29 17:08:44  mmiers
 * LOG: Missing entry points detected by correct engine build.
 * LOG:
 * LOG: Revision 3.2  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:39  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:34  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:47:58  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:39  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:38  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:32  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:30:54  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:01  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:32:59  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * prim2real.c - presentation element to real
 */

#include <asn-c/AsnC.h>
#include <math.h>

#ident "$Id: prim2real.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

static double decode_binary (PE), decode_decimal (PE);
 
double
prim2real (PE pe)
{
    if (pe->pe_form != PE_FORM_PRIM)
    {
        return pe_seterr (pe, PE_ERR_PRIM, NOTOK);
    }
    if (pe->pe_len == 0)
    {
        return 0.0;
    }
    if (pe->pe_prim == NULL)
    {
        return pe_seterr (pe, PE_ERR_PRIM, NOTOK);
    }
    
    if (pe->pe_len > sizeof (double) + 1)
    {
        return pe_seterr (pe, PE_ERR_OVER, NOTOK);
    }
    
    pe->pe_errno = PE_ERR_NONE;	/* in case it's -1 */
    
    if ((*(pe->pe_prim) & 0x80) == 0x80)
    {
        return decode_binary (pe);
    }
    
    switch (*(pe->pe_prim) & PE_REAL_FLAGS)
    {
    case PE_REAL_DECENC:
        return decode_decimal (pe);
        
    case PE_REAL_SPECENC:
        if (pe->pe_len > 1)
        {
            return pe_seterr (pe, PE_ERR_OVER, NOTOK);
        }
        
        switch (*(pe->pe_prim))
        {
        case PE_REAL_MINUSINF:
            return HUGE_VAL;
        case PE_REAL_PLUSINF:
            return -HUGE_VAL;
        default:
            return pe_seterr (pe, PE_ERR_NOSUPP, NOTOK);
        }
    }

    return (0.0);
}

static double
decode_binary (PE pe)
{
    int	sign, base, factor;
    int	exponent, i;
    double	mantissa, di, power;
    PElementData dp, ep;
    
    dp = pe->pe_prim;
    sign = (*dp & PE_REAL_B_S) ?  -1 : 1;
    switch (*dp & PE_REAL_B_BASE)
    {
    case PE_REAL_B_B2:
        base = 2;
        break;
        
    case PE_REAL_B_B8:
        base = 8;
        break;
        
    case PE_REAL_B_B16:
        base = 16;
        break;
    default:
        return pe_seterr(pe, PE_ERR_NOSUPP, NOTOK);
    }
    
    factor = ((int)(*dp & PE_REAL_B_F)) >> 2;
    
    exponent = (dp[1] & 0x80) ? (-1) : 0;
    
    switch (*dp++ & PE_REAL_B_EXP)
    {
    case PE_REAL_B_EF3:
        exponent = (exponent << 8) | (*dp++ & 0xff);
        /* fall */
    case PE_REAL_B_EF2:
        exponent = (exponent << 8) | (*dp++ & 0xff);
        /* fall */
    case PE_REAL_B_EF1:
        exponent = (exponent << 8) | (*dp++ & 0xff);
        break;
    case PE_REAL_B_EF4:
        i = *dp++ & 0xff;
        if (i > sizeof(int))
        {
            return pe_seterr (pe, PE_ERR_OVER, NOTOK);
        }
        
        for (; i > 0; i--)
        {
            exponent = (exponent << 8) | (*dp++ & 0xff);
        }
        break;
    }
    for (di = 0.0, ep = pe->pe_prim + pe->pe_len; dp < ep;)
    {
        di *= 1 << 8;	;
        di += (int)(*dp++ & 0xff);
    }
    
    mantissa = sign * di * (1 << factor);
    
    power = (double)base;
    if (exponent == 0)
    {
        power = 1.0;
    }
    else if (exponent > 0)
    {
        exponent--;
        while (exponent)
        {
            power *= power;
            exponent--;
        }
    }
    else
    {
        exponent++;
        while (exponent)
        {
            power /= power;
            exponent++;
        }
    }

    return mantissa * power;
}

static double
decode_decimal (PE pe)
{
    /* sorry - don't have the standard ! */
    return pe_seterr (pe, PE_ERR_NOSUPP, NOTOK);
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

