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
 * LOG: Revision 1.1  2007/03/30 04:49:41  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:18  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:12  cvsadmin
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
 * LOG: Revision 5.1  2001/08/16 20:46:01  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/02/14 20:33:12  mmiers
 * LOG: Add ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:35  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:21  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/06/01 17:15:06  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:26  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:00  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 17:48:22  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 04:30:39  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 02:40:38  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.2  1998/10/20 23:32:49  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * bit_opts.c - operations on bit strings
 */

#include <asn-c/AsnC.h>

#ident "$Id: bit_ops.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $"

static PE
ffb_pe(PE pe)
{
    PE p, q;

    for (p = pe->pe_cons, q = NULL; p; q = p, p = p->pe_next)
    {
        continue;
    }
    
    if (q != NULL)
    {
        switch (q->pe_form)
        {
        case PE_FORM_PRIM: 
            return q;
            
        case PE_FORM_CONS: 
            return ffb_pe(q);
        }
    }
    
    return pe;
}

static PElementData
ffb_aux(PE pe, int *n, int *mask)
{
    int    i, nbits;
    PElementData bp;
    PE      p;
    
    switch (pe->pe_form)
    {
    case PE_FORM_PRIM: 
        if ((nbits = pe->pe_nbits) > (i = *n))
        {
            *mask = 1 << (7 - (i % 8));
            
            return (pe->pe_prim + i / 8 + 1);
        }
        
        *n -= nbits;
        break;
        
    case PE_FORM_CONS: 
        for (p = pe->pe_cons; p; p = p->pe_next)
        {
            if ((bp = ffb_aux (p, n, mask)) != NULL)
            {
                return bp;
            }
        }
        break;
    }
    
    return NULL;
}

static PElementData
ffb(PE pe, int n, int *mask, int xtnd)
{
    int len, i, j;
    PElementData bp;
    PE *p, q, r;
    
    i = (j = n) / 8 + 1;
    if ((bp = ffb_aux (pe, &j, mask)) != NULL || !xtnd)
    {
        return bp;
    }
    
    if (pe->pe_form == PE_FORM_CONS)
    {
        pe = ffb_pe (pe);
    }
    
    switch (pe->pe_form)
    {
    case PE_FORM_PRIM: 
        if (pe->pe_len < (PElementLen) (len = i + 1))
        {
            if ((bp = PEDalloc (len)) == NULL)
            {
                return NULL;
            }
            memset ((char *) bp, 0, len);
            if (pe->pe_prim)
            {
                PEDcpy (pe->pe_prim, bp, pe->pe_len);
                
                if (pe->pe_inline)
                {
                    pe->pe_inline = 0;
                }
                else
                {
                    PEDfree (pe->pe_prim);
                }
            }
            pe->pe_prim = bp, pe->pe_len = len;
        }
        
        pe->pe_nbits = n + 1;
        
        *mask = 1 << (7 - (n % 8));
        
        return (pe->pe_prim + i);
        
    case PE_FORM_CONS: 
        if ((r = pe_alloc (pe->pe_class, PE_FORM_PRIM, pe->pe_id)) == NULL)
        {
            return NULL;
        }
        if ((r->pe_prim = PEDalloc (len = r->pe_len = j / 8 + 2)) == NULL)
        {
            pe_free (r);
            
            return NULL;
        }
        
        memset ((char *) r->pe_prim, 0, len);
        
        r->pe_nbits = j + 1;
        
        *mask = 1 << (7 - (j % 8));
        
        for (p = &pe->pe_cons; (q = *p) != NULL; p = &q->pe_next)
        {
            continue;
        }
        
        *p = r;
        
        return (r->pe_prim + len - 1);
        
    default:
        return NULL;
    }
}

/*
 * the first octet indicates how many unused bits are in the last octet --
 *
 *	prim2bit  -	presentation element to bit string
 *	bit2prim  -	bit string to presentation element
 *	bit_on	  -	turn a bit ON
 *	bit_off	  -	turn a bit OFF
 *	pbit_test  -	test a bit
 */


int
pbit_on(PE pe, int i)
{
    int     mask;
    PElementData bp;
    
    if ((bp = ffb(pe, i, &mask, 1)) == NULL)
    {
        return pe_seterr (pe, PE_ERR_NMEM, NOTOK);
    }
    
    *bp |= mask;
    
    return OK;
}

int
pbit_off(PE pe, int i)
{
    int     mask;
    PElementData bp;
    
    if ((bp = ffb(pe, i, &mask, 1)) == NULL)
    {
        return pe_seterr (pe, PE_ERR_NMEM, NOTOK);
    }
    
    *bp &= ~mask;
    
    return OK;
}

int
pbit_test(PE pe, int i)
{
    int     mask;
    PElementData bp;
    
    if ((bp = ffb(pe, i, &mask, 0)) == NULL)
    {
        return pe_seterr (pe, PE_ERR_BIT, NOTOK);
    }
    
    return (*bp & mask ? 1 : 0);
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

