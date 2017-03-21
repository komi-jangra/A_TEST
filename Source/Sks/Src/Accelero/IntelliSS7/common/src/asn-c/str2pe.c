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
 * LOG: Revision 1.1  2007/03/30 04:50:51  cvsadmin
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
 * LOG: Revision 3.1  2000/08/16 00:04:34  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:44  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:19:17  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:47  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/02/26 15:41:09  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Solaris C++ build.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:48:00  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:52  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:16:08  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:43  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/21 04:31:06  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 02:41:18  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.3  1998/10/20 23:33:11  mmiers
 * LOG: Cleanup, start making this stuff reentrant.
 * LOG:
 *
 *****************************************************************************/
/*
 * str2pe.c - create an Inline CONStructor PElement
 */

#include <asn-c/AsnC.h>

#ident "$Id: str2pe.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

static PElementLen	str_get_len (char *s, int len, int *result);
static int  str_get_start (char **sp, int *n,
                           PElementClass *pclass, PElementForm *form,
                           PElementID *id, PElementLen *plen, int *result);

#define	seterr(e,v)		(*result = (e), (v))


PE
str2pe (char *s, int len, int *advance, int *result)
{
    char   *sp;
    PElementClass   pclass;
    PElementForm    form;
    PElementID    id;
    PElementLen plen;
     PE	    pe;

    *result = PS_ERR_NONE;

    sp = s;
    if (str_get_start (&sp, &len, &pclass, &form, &id, &plen, result) == NOTOK)
    {
	return NULL;
    }

    if (form == PE_FORM_CONS)
    {
	form = PE_FORM_ICONS;
    }

    if (plen == PE_LEN_INDF &&
        (plen = str_get_len (sp, len, result)) == PE_LEN_INDF)
    {
	return NULL;
    }

    if ((pe = pe_alloc (pclass, form, id)) == NULL)
    {
	return (PE)seterr (PS_ERR_NMEM, NULL);
    }

    pe->pe_ilen = sp - s;
    if (form == PE_FORM_ICONS)
    {
	pe->pe_len = pe->pe_ilen + plen;
	pe->pe_prim = (PElementData) s;
    }
    else
    {
	if ((pe->pe_len = plen) != 0)
        {
	    pe->pe_prim = (PElementData) sp;
        }
    }

    pe->pe_inline = 1;

    if (advance)
    {
	*advance = pe->pe_ilen + plen;
    }

    return pe;
}

static int
str_get_start (char **sp, int *n,
               PElementClass *pclass, PElementForm *form,
               PElementID *id, PElementLen *plen, int *result)
{
     int i, len;
     char *s;
     byte c, d;
     PElementID    jd;
     PElementLen qlen;

    s = *sp, len = *n;
    if (len-- <= 0)
    {
	return seterr (PS_ERR_EOF, NOTOK);
    }

    c = *s++;

    *pclass = (PElementClass)(((int)(c & PE_CLASS_MASK)) >> PE_CLASS_SHIFT);
    *form = (PElementForm)(((int)(c & PE_FORM_MASK)) >> PE_FORM_SHIFT);
    if ((jd = (c & PE_CODE_MASK)) == PE_ID_XTND)
    {
	for (jd = 0;; jd <<= PE_ID_SHIFT)
        {
	    if (len-- <= 0)
            {
		return seterr (PS_ERR_EOFID, NOTOK);
            }

	    d = *s++;

	    jd |= d & PE_ID_MASK;
	    if (!(d & PE_ID_MORE))
            {
		break;
            }
	    if (jd & (PE_ID_MASK << (PE_ID_SHIFT - 1)))
            {
		return seterr (PS_ERR_OVERID, NOTOK);
            }
	}
    }

    *id = jd;
    if (len-- <= 0)
    {
	return seterr (PS_ERR_EOFLEN, NOTOK);
    }

    c = *s++;

    if ((i = c) & PE_LEN_XTND)
    {
	if ((i &= PE_LEN_MASK) > sizeof (PElementLen))
        {
	    return seterr (PS_ERR_OVERLEN, NOTOK);
        }

	if (i)
        {
	    for (qlen = 0; i-- > 0;)
            {
		if (len-- <= 0)
                {
		    return seterr (PS_ERR_EOFLEN, NOTOK);
                }
		c = *s++;

		qlen = (qlen << 8) | (c & 0xff);
	    }

	    *plen = qlen;
	}
	else
        {
	    if (*form == PE_FORM_PRIM)
            {
		return seterr (PS_ERR_INDF, NOTOK);
            }
	    else
            {
		*plen = PE_LEN_INDF;
            }
        }
    }
    else
    {
	*plen = i;
    }

    *sp = s, *n = len;

    return OK;
}

static PElementLen
str_get_len (char *s, int len, int *result)
{
    char   *sp;
    PElementClass pclass;
    PElementForm form;
    PElementID id;
    PElementLen plen;

    for (sp = s;;)
    {
	if (str_get_start (&sp, &len, &pclass, &form, &id, &plen, result)
	        == NOTOK)
	    return PE_LEN_INDF;

	if (pclass == PE_CLASS_UNIV && id == PE_UNIV_EOC)
	    return ((PElementLen) (sp - s));

	if (plen == PE_LEN_INDF
		&& (plen = str_get_len (sp, len, result)) == PE_LEN_INDF)
	    return PE_LEN_INDF;

	sp += plen, len -= plen;
    }
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

