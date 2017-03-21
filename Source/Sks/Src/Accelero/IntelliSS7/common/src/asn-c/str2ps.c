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
 * LOG: Revision 1.1  2007/03/30 04:50:53  cvsadmin
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
 * LOG: Revision 3.1  2000/08/16 00:04:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:44  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:47  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/07/22 00:34:39  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.3  1999/06/01 17:15:08  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.2  1999/02/26 00:48:00  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:16:09  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:44  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:31:08  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:19  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:33:12  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * str2ps.c - string-backed abstraction for PStreams
 */

#include <stdio.h>

#include <asn-c/AsnC.h>

#ident "$Id: str2ps.c,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

static int
str_read (PS ps, PElementData data, PElementLen n, int in_line)
{
     int    cc;

    if (ps->ps_base == NULL || (cc = ps->ps_cnt) <= 0)
    {
	return 0;
    }

    if (cc > n)
    {
	cc = n;
    }

    memcpy ((char *)data, ps->ps_ptr, cc);
    ps->ps_ptr += cc, ps->ps_cnt -= cc;

    return cc;
}

static int
str_write (PS ps, PElementData data, PElementLen n, int in_line)
{
    int    cc;
    char  *cp;
    
    if (ps->ps_base == NULL)
    {
        if ((cp = (char *)malloc ((unsigned) (cc = n + BUFSIZ))) == NULL)
        {
            return ps_seterr (ps, PS_ERR_NMEM, NOTOK);
        }
        
        ps->ps_base = ps->ps_ptr = cp;
        ps->ps_bufsiz = ps->ps_cnt = cc;
    }
    else
    {
        if (ps->ps_cnt < n)
        {
            int    curlen = ps->ps_ptr - ps->ps_base;
            
            if (ps->ps_inline)
            {
                n = ps->ps_cnt;
                
                goto partial;
            }
            
            if ((cp = (char *)realloc (ps->ps_base,
                                       (unsigned) (ps->ps_bufsiz
                                        + (cc = n + BUFSIZ)))) == NULL)
            {
                return ps_seterr (ps, PS_ERR_NMEM, NOTOK);
            }
            ps->ps_ptr = (ps->ps_base = cp) + curlen;
            ps->ps_bufsiz += cc, ps->ps_cnt += cc;
        }
    }
    
partial:
    memcpy (ps->ps_ptr, (char *) data, n);
    ps->ps_ptr += n, ps->ps_cnt -= n;
    
    return n;
}


static int
str_close (PS ps)
{
    if (ps->ps_base && !ps->ps_inline)
    {
	free (ps->ps_base);
    }

    return OK;
}

int
str_open (PS ps)
{
    ps->ps_readP = str_read;
    ps->ps_writeP = str_write;
    ps->ps_closeP = str_close;

    return OK;
}


int
str_setup (PS ps, char *cp, int cc, int in_line)
{
    char  *dp;
    
    if (in_line)
    {
        ps->ps_inline = 1;
        ps->ps_base = ps->ps_ptr = cp;
        ps->ps_bufsiz = ps->ps_cnt = cc;
    }
    else
    {
        if (cc > 0)
        {
            if ((dp = (char *)malloc ((unsigned) (cc))) == NULL)
            {
                return ps_seterr (ps, PS_ERR_NMEM, NOTOK);
            }
            
            ps->ps_base = ps->ps_ptr = dp;
            if (cp != NULL)
            {
                memcpy (dp, cp, cc);
            }
            
            ps->ps_bufsiz = ps->ps_cnt = cc;
        }
    }
    
    return OK;
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

