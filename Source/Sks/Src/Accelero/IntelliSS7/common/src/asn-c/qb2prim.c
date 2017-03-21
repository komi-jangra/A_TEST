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
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:01  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:50:30  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:19  cvsadmin
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
 * LOG: Revision 3.2  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:30  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:41  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:39  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:49  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:57  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 17:48:37  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 04:30:58  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 02:41:11  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.2  1998/10/20 23:33:04  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * qb2prim.c - octet string to primitive
 */

#include <asn-c/AsnC.h>

#ident "$Id: qb2prim.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

/*
 * form: PRIMitive or CONStructor --
 *
 *	qb2prim  -	octet string (via qbufs) to presentation element
 *
 */

PE
qb2prim_aux (struct qbuf* qb, PElementClass classOf,
             PElementID id, int in_line)
{
    PE	    pe, p;
    struct qbuf *qp;
    
    if (qb == NULL)
    {
        return NULL;
    }
    
    if ((qp = qb->qb_forw) == qb || qp->qb_forw == qb)
    {
        if ((pe = pe_alloc (classOf, PE_FORM_PRIM, id)) == NULL)
        {
            return NULL;
        }
        
        if (in_line)
        {
            if ((pe->pe_len = qp->qb_len) != 0)
            {
                pe->pe_prim = (PElementData) qp->qb_data;
            }
            
            pe->pe_inline = 1;
        }
        else
        {
            if ((pe->pe_len = qp->qb_len) != 0)
            {
                if ((pe->pe_prim = PEDalloc (pe->pe_len)) == NULL)
                {
                    goto no_mem;
                }
                
                PEDcpy (qp->qb_data, pe->pe_prim, pe->pe_len);
            }
        }
    }
    else
    {
        if ((pe = pe_alloc (classOf, PE_FORM_CONS, id)) == NULL)
        {
            return NULL;
        }
        
        do
        {
            if (seq_add (pe, p = pe_alloc (PE_CLASS_UNIV, PE_FORM_PRIM,
                PE_PRIM_OCTS), -1) == NOTOK)
            {
no_mem:
            pe_free (pe);
            
            return NULL;
            }
            
            p->pe_len = qp->qb_len;
            if (in_line)
            {
                p->pe_prim = (PElementData) qp->qb_data;
                p->pe_inline = 1;
            }
            else
            {
                if ((p->pe_prim = PEDalloc (p->pe_len)) == NULL)
                {
                    goto no_mem;
                }
                
                PEDcpy (qp->qb_data, p->pe_prim, p->pe_len);
            }
            
            qp = qp->qb_forw;
        }
        while (qp != qb);
    }
    
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

