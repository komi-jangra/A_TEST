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
 * LOG: Revision 1.1  2007/03/30 04:50:04  cvsadmin
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
 * LOG: Revision 3.2  2001/02/14 20:33:12  mmiers
 * LOG: Add ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:38  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/06/01 17:15:07  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:38  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:29  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/22 19:28:08  mmiers
 * LOG: Continue making PSAP threadsafe.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 17:48:27  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:40:50  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:32:54  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * pe2qb_f.c - presentation element to qbuf, the qbuf must be one piece.
 */

#include <asn-c/AsnC.h>

#ident "$Id: pe2qb_f.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

#define moveit(c, l)                                        \
    if(*Qcp + l > Ecp)                                      \
    {                                                       \
	printf("pe2qb_f: Qcp %o Ecp %o len %d\n",           \
		**Qcp, *Ecp, l);                            \
	return(NOTOK);                                      \
    }                                                       \
    if(l == 1)                                              \
    {                                                       \
	**Qcp = *c;                                         \
        (*Qcp)++;                                           \
	(*Len)++;                                           \
    }                                                       \
    else                                                    \
    {                                                       \
	    memcpy(*Qcp, (char *)c, l);                     \
	    *Qcp += l;                                      \
	    *Len += l;                                      \
    }

static PElement pe_eoc =
{
    PE_CLASS_UNIV,
    PE_FORM_PRIM,
    PE_UNIV_EOC,
    0
};

int
pe2qb_f (PE pe, char **Qcp, char *Ecp, int *Len)
{
    PE	    p;
    int elm_len;
    byte    elmbuffer[1 + sizeof(PElementLen)];
    byte  *bp,  *ep;
    PElementForm    form;
    PElementID id;
    PElementLen len;
    
    if ((form = pe->pe_form) == PE_FORM_ICONS)
    {
        elm_len = pe->pe_len;
        moveit(pe->pe_prim, elm_len);
        
        return(*Len);
    }
    
    /* Put the id into the qbuf */
    
    **Qcp = (char)(((pe->pe_class << PE_CLASS_SHIFT) & PE_CLASS_MASK)
                    | ((form << PE_FORM_SHIFT) & PE_FORM_MASK));
    
    if ((id = pe->pe_id) < PE_ID_XTND)
    {
        **Qcp |= id;
        (*Qcp)++;
        (*Len)++;
    }
    else
    {
        byte    idbuffer[1 + sizeof (PElementID)];
        PElementID jd;
        
        ep = (bp = idbuffer);
        *bp = (byte)(**Qcp | PE_ID_XTND);
        for (jd = id; jd != 0; jd >>= PE_ID_SHIFT)
        {
            ep++;
        }
        
        for (bp = ep; id != 0; id >>= PE_ID_SHIFT)
        {
            *bp-- = (byte)(id & PE_ID_MASK);
        }
        for (bp = idbuffer + 1; bp < ep; bp++)
        {
            *bp |= PE_ID_MORE;
        }
        
        bp = ++ep;
        elm_len = bp - idbuffer;
        moveit(idbuffer, elm_len);
    }
    
    
    /* Put the length into the qbuf */
    if ((len = pe->pe_len) == PE_LEN_INDF)
    {
        **Qcp = (char)PE_LEN_XTND;
        (*Qcp)++;
        (*Len)++;
    }
    else
    {
        if (len <= PE_LEN_SMAX)
        {
            **Qcp = (char)(len & 0xff);
            (*Qcp)++;
            (*Len)++;
        }
        else
        {
            ep = elmbuffer + sizeof elmbuffer - 1;
            for (bp = ep; len != 0 && elmbuffer < bp; len >>= 8)
            {
                *bp-- = (byte)(len & 0xff);
            }
            *bp = (byte)(PE_LEN_XTND | ((ep - bp) & 0xff));
            elm_len = ep - bp + 1;
            moveit(bp, elm_len);
        }
    }
    
    /* Now put the actual value into the qbuf */
    switch (pe->pe_form)
    {
    case PE_FORM_PRIM: 
        elm_len = pe->pe_len;
        moveit(pe->pe_prim, elm_len);
        break;
        
    case PE_FORM_CONS: 
        if (pe->pe_len)
        {
            for (p = pe->pe_cons; p; p = p->pe_next)
            {
                if (pe2qb_f (p, Qcp, Ecp, Len) == NOTOK)
                {
                    return NOTOK;
                }
            }
            
            if (pe->pe_len == PE_LEN_INDF &&
                pe2qb_f (&pe_eoc, Qcp, Ecp, Len) == NOTOK)
            {
                return NOTOK;
            }
        }
        break;
        
    default:
        abort();
    }
    
    return(*Len);
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

