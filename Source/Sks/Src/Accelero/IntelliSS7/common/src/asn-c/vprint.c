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
 * LOG: Revision 1.1  2007/03/30 04:51:07  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:21  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/06 21:05:16  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/10/28 18:46:53  mmiers
 * LOG: 64 bit build issues.
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
 * LOG: Revision 3.1  2000/08/16 00:04:38  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:48  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:52  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/09/07 15:32:00  skarmakar
 * LOG:
 * LOG:
 * LOG: Remove bogus type cast that truncated the pointer (64 bit machines
 * LOG: only).
 * LOG:
 * LOG: Revision 1.10  1999/07/22 00:34:39  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.9  1999/06/11 15:59:07  fhasle
 * LOG:
 * LOG:
 * LOG: Change newbuf() to not try to cache memory.  Memleaks were present; fix
 * LOG: caused corruption.
 * LOG:
 * LOG: Revision 1.8  1999/06/11 15:44:31  fhasle
 * LOG:
 * LOG:
 * LOG: Formatting, check for NULL pointer.
 * LOG:
 * LOG: Revision 1.7  1999/06/10 23:15:27  mmiers
 * LOG:
 * LOG:
 * LOG: Dangling memory leak.
 * LOG:
 * LOG: Revision 1.6  1999/03/02 18:14:53  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the header file ordering (I did it again).
 * LOG:
 * LOG: Revision 1.5  1999/02/26 04:09:52  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.4  1999/02/26 00:48:01  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.3  1998/11/19 02:40:55  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.2  1998/11/10 23:36:03  ite
 * LOG: Fix vprint() bug.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:16:18  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.13  1998/10/23 18:00:01  jrao
 * LOG: Fix prnt bugs (missing pointers, etc).
 * LOG:
 * LOG: Revision 1.12  1998/10/23 16:05:35  mmiers
 * LOG: AsnC is now threadsafe, except for ODE.
 * LOG:
 * LOG: Revision 1.11  1998/10/22 16:28:32  mmiers
 * LOG: Getting pepsy thread-safe.
 * LOG:
 * LOG: Revision 1.10  1998/10/22 00:47:41  whu
 * LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 * LOG:
 * LOG: Revision 1.9  1998/10/21 19:20:18  mmiers
 * LOG: Update for ALPHA build.
 * LOG:
 * LOG: Revision 1.8  1998/10/21 17:48:22  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 *
 *****************************************************************************/

#if defined(__STDC__) || defined(WIN32) || defined(__cplusplus)
#include <stdarg.h>
#else
#include <varargs.h>
#endif

/* LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 */
#include "pepsy-driver.h"
#include <asn-c/AsnC.h>
#include <asn-c/UNIV-types.h>

#ident "$Id: vprint.c,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

static void	vprint1 (VSTRUCT*);
static void	vprint2 (VSTRUCT*);
static void	vwrite (VSTRUCT*, char*);

#if defined(__STDC__) || defined(WIN32) || defined(__cplusplus)
extern void _asprintf (char *, char *, va_list);
#endif

extern int pepsylose(modtyp *a, ptpe *b, PE pe, ...);

#define	VPRINT(s) \
    vprint1 (str), vwrite (str, (s)), vprint2 (str)

static char  *py_classlist[] =
{
    "UNIVERSAL", "APPLICATION", "", "PRIVATE"
};

static char   *oct2str (VSTRUCT *, char *, int len);
static char   *newbuf (VSTRUCT *, int len);

void
vpush (VSTRUCT* str)
{
    if (str->didvpush)
    {
	vwrite (str, "\n"), str->didvpush = 0;
    }
    else
    {
	if (!str->didname && str->docomma)
        {
	    vwrite (str, ",\n");
        }
    }

    if (str->didname)
    {
	vwrite (str, " ");
    }
    else
    {
	if (str->vfp && str->vlevel > 0)
        {
	    (*str->vfnx) (str->vfp, "%*s", (str->vlevel * 3), "");
        }
    }

    vwrite (str, "{");
    str->vlevel++;

    str->didname = str->didvpop = str->docomma = 0, str->didvpush = 1;
}

void
vpop (VSTRUCT* str)
{
    if (str->didname || str->docomma)
    {
	vwrite (str, "\n");
    }

    str->vlevel--;
    if (!str->didvpush && str->vfp && str->vlevel > 0)
    {
	(*str->vfnx) (str->vfp, "%*s", (str->vlevel * 3), "");
    }

    vwrite (str, "}");

    if (str->vlevel == 0)
    {
	vwrite (str, "\n");
    }

    str->didname = str->didvpush = 0, str->didvpop = str->docomma = str->vlevel ? 1 : 0;
}

/*
 * VNAME/VTAG
 */
void
vname (VSTRUCT* str, char *name)
{
    if (str->didvpush)
    {
	vwrite (str, "\n"), str->didvpush = 0;
    }
    else
    {
	if (str->docomma)
        {
	    vwrite (str, ",\n");
        }
    }

    if (str->vfp && str->vlevel > 0)
    {
	(*str->vfnx) (str->vfp, "%*s", (str->vlevel * 3), "");
    }
    vwrite (str, name);

    str->didname = 1;
}


void
vtag (VSTRUCT *str, int pclass, int id)
{
    char *bp;
    char buffer[BUFSIZ];

    if (str->didname)
    {
	return;
    }

    bp = buffer;
    *bp++ = '[';
    switch (pclass)
    {
	case PE_CLASS_UNIV: 
	case PE_CLASS_APPL: 
	case PE_CLASS_PRIV: 
	    sprintf (bp, "%s ", py_classlist[pclass]);
	    bp += strlen (bp);
	    break;

	case PE_CLASS_CONT: 
	default:
	    break;
    }
    sprintf (bp, "%d]", id);

    vname (str, buffer);
}

/*
 * VPRINT
 */
void
#if defined(__STDC__) || defined(WIN32) || defined(__cplusplus)
vprint (VSTRUCT* str, ...)
{
    va_list ap;

    char    buffer[BUFSIZ];
    
    vprint1 (str);

    va_start (ap, str);
#else
vprint (va_alist)
va_dcl
{
    va_list ap;

    char    buffer[BUFSIZ];
    
    vprint1 (str);

    va_start (ap);
#endif

    _asprintf (buffer, NULL, ap);
    
    va_end (ap);

    vwrite (str, buffer);

    vprint2 (str);
}


static	void
vprint1 (VSTRUCT* str)
{
    if (str->didvpush)
    {
	vwrite (str, "\n"), str->didvpush = 0;

	goto indent;
    }
    else
    {
	if (str->didname)
        {
	    vwrite (str, " ");
        }
	else
        {
	    if (str->docomma)
            {
		vwrite (str, ",\n");
            }
indent:
	    if (str->vfp && str->vlevel > 0)
            {
		(*str->vfnx) (str->vfp, "%*s", (str->vlevel * 3), "");
            }
	}
    }
}


static	void
vprint2 (VSTRUCT* str)
{
    if (str->vlevel == 0)
    {
	vwrite (str, "\n");
    }

    str->didname = str->didvpop = 0, str->docomma = str->vlevel ? 1 : 0;
}

/*
 * VWRITE
 */
static	void
vwrite (VSTRUCT* str, char *s)
{
    if (str->vfp)
    {
	(*str->vfnx) (str->vfp, "%s", s);
    }
    else
    {
	 char   c, *cp;

	if (str->vps)
        {
	    for (cp = s; *cp; cp++)
            {
		if (*cp == '\n' )
                {
		    ps_write (str->vps, (PElementData) " ", 1);
                }
		else
                {
		    ps_write (str->vps, (PElementData) cp, 1);
                }
	    }
        }
	else
        {
	    for (cp = s; *cp; )
            {
	        *str->vbp++ = (char)((c = *cp++) != '\n' ? c : ' ');
            }
        }
    }
}

/*
 * VSTRING
 */
void
vstring (VSTRUCT* str, PE pe)
{
     PE	    p;
     char *c = NULL;

    switch (pe->pe_form)
    {
	case PE_FORM_PRIM: 
	case PE_FORM_ICONS:
            c = oct2str (str, (char *) pe->pe_prim, (int) pe->pe_len);
    	    VPRINT (c);
            if (c)
            {
                free(c);
            }
	    break;

	case PE_FORM_CONS: 
	    vpush (str);
	    for (p = pe->pe_cons; p; p = p->pe_next)
            {
		vstring (str, p);
            }
	    vpop (str);
	    break;
    }
}

static char *
oct2str (VSTRUCT* str, char *s, int len)
{
    int     ia5ok;
    int    k;
    char  *bp, *cp, *dp, *zp = NULL;

    ia5ok = 1, k = 0;
    for (dp = (cp = s) + len; cp < dp; cp++)
    {
	switch (*cp)
        {
	    case ' ': 
		continue;

	    case '"': 
		break;

	    case '\b':
	    case '\f':
	    case '\n':
	    case '\r':
	    case '\t':
	    case '\\':
		ia5ok = -1, k++;
		continue;

	    case '-': 
		if (cp > s && *(cp + 1) == '-')
		    break;
		continue;

	    default: 
		if (iscntrl (*cp) || isspace (*cp) || (*cp & 0x80))
		    break;
		continue;
	}
	ia5ok = 0;
	break;
    }

    switch (ia5ok)
    {
	case 1: 
	    zp = newbuf (str, len + 2);
	    sprintf (zp, "\"%*.*s\"", len, len, s);
	    break;

	case -1: 
	    bp = zp = newbuf (str, len + k + 2);
	    *bp++ = '"';
	    for (cp = s; cp < dp; cp++)
            {
		if (*cp >= ' ' && *cp != '\\')
		    *bp++ = *cp;
		else {
		    *bp++ = '\\';
		    switch (*cp) {
			case '\b':
			    *bp++ = 'b';
			    break;
			case '\f':
			    *bp++ = 'f';
			    break;
			case '\n':
			    *bp++ = 'n';
			    break;
			case '\r':
			    *bp++ = 'r';
			    break;
			case '\t':
			    *bp++ = 't';
			    break;

			case '\\':
			    *bp++ =  '\\';
			    break;
		    }
		}
            }
	    sprintf (bp, "\"");
	    break;

	case 0: 
	default: 
	    bp = zp = newbuf (str, len * 2 + 3);
	    *bp++ = '\'';
	    for (cp = s; cp < dp; cp++)
            {
		sprintf (bp, "%02x", *cp & 0xff);
		bp += strlen (bp);
	    }
	    sprintf (bp, "'H");
	    break;
    }

    return zp;
}

char *
bit2str (VSTRUCT *str, PE pe, char *s)
{
    int     ia5ok;
    int    hit = 0, i, j, k;
    char  *bp, *cp, *zp = NULL;

    j = pe->pe_nbits;
    if ((cp = s) && *++cp)
    {
	ia5ok = 1, hit = 0;
	for (i = 0; i < j;)
        {
	    if (pbit_test (pe, i++) == 1)
            {
		do
                {
		    if (!(k = *cp++ & 0xff))
			break;
		    if (k == i)
                    {
			hit += hit ? 2 : 1;
			for (; *cp > ' '; cp++)
			    hit++;
		    }
		    else
			for (; *cp > ' '; cp++)
			    continue;
		}
                while (k != 0 && k < i);

		if (k == 0 || k > i)
                {
		    ia5ok = 0;
		    break;
		}
	    }
        }
    }
    else
	ia5ok = 0;

    if (ia5ok)
    {
	bp = zp = newbuf (str, hit + 3);
	*bp++ = '{';

	cp = s, cp++;
	for (i = hit = 0; i < j;)
        {
	    if (pbit_test (pe, i++) == 1)
            {
		do
                {
		    if (!(k = *cp++ & 0xff))
			break;

		    if (k == i)
                    {
			if (hit)
			    *bp++ = ',';
			*bp++ = ' ';
			for (; *cp > ' '; cp++)
			    *bp++ = *cp;
		    }
		    else
			for (; *cp > ' '; cp++)
			    continue;
		}
                while (k != 0 && k < i);

		if (k == 0 || k > i)
		    break;
		hit++;
	    }
        }

	sprintf (bp, "%s}", hit ? " " : "");
    }
    else
    {
	bp = zp = newbuf (str, j + 3);
	*bp++ = '\'';
	for (i = 0; i < j; i++)
	    *bp++ = (char)(pbit_test (pe, i) ? '1' : '0');
	sprintf (bp, "'B");
    }

    return zp;
}

#ifdef vunknown
#undef vunknown
#endif

void
vunknown (VSTRUCT* str, PE pe)
{
    int     i;
#ifdef	notyet	    /* could comment this in, but then all programs need -lm */
    double  j;
#endif
    OID	    oid;
    PE	    p;

    switch (pe->pe_form)
    {
	case PE_FORM_PRIM: 
	    switch (PE_ID (pe->pe_class, pe->pe_id))
            {
		case PE_ID (PE_CLASS_UNIV, PE_PRIM_BOOL): 
		    if ((i = prim2flag (pe)) == NOTOK)
			goto bad_pe;
		    VPRINT (i ? "TRUE" : "FALSE");
		    break;

		case PE_ID (PE_CLASS_UNIV, PE_PRIM_INT): 
		case PE_ID (PE_CLASS_UNIV, PE_PRIM_ENUM): 
		    if ((i = prim2num (pe)) == NOTOK
			    && pe->pe_errno != PE_ERR_NONE)
			goto bad_pe;
		    vprint (str, "%d", i);
		    break;

#ifdef	notyet
		case PE_ID (PE_CLASS_UNIV, PE_PRIM_REAL): 
		    if ((j = prim2real (pe)) == NOTOK
			    && pe->pe_errno != PE_ERR_NONE)
			goto bad_pe;
		    vprint (str, "%g", j);
		    break;
#endif

		case PE_ID (PE_CLASS_UNIV, PE_PRIM_BITS): 
		    if ((p = prim2bit (pe)) == NULL)
			goto bad_pe;
		    if (p->pe_nbits < LOTSOFBITS) {
                        char *c = NULL;

                        c = bit2str (str, p, "\020");
			VPRINT (c);
                        if (c)
                        {
                            free(c);
                        }
			break;
		    }
		    /* else fall... */

		default: 
	    bad_pe: ;
		    vtag (str, (int) pe->pe_class, (int) pe->pe_id);
		/* fall */

		case PE_ID (PE_CLASS_UNIV, PE_PRIM_OCTS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_IA5S): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_NUMS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_PRTS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_T61S): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_VTXS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_GENT): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_UTCT): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_GFXS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_VISS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_GENS): 
		case PE_ID (PE_CLASS_UNIV, PE_DEFN_CHRS): 
		case PE_ID (PE_CLASS_UNIV, PE_PRIM_ODE): 
		    vstring (str, pe);
		    break;

		case PE_ID (PE_CLASS_UNIV, PE_PRIM_NULL):
		    VPRINT ("NULL");
		    break;

		case PE_ID (PE_CLASS_UNIV, PE_PRIM_OID): 
                    {
                        char buf[BUFSIZ];

		        if ((oid = prim2oid (pe)) == NULL)
                        {
		            goto bad_pe;
                        }

		        if (oid2ode (oid, buf, BUFSIZ) == ITS_SUCCESS)
                        {
                            VPRINT ((buf));
                        }

                        oid_free(oid);

		        break;
                    }
	    }
	    break;

	case PE_FORM_CONS: 
	    switch (PE_ID (pe->pe_class, pe->pe_id))
            {
		case PE_ID (PE_CLASS_UNIV, PE_CONS_SEQ):
		case PE_ID (PE_CLASS_UNIV, PE_CONS_SET):
		    break;

		case PE_ID (PE_CLASS_UNIV, PE_CONS_EXTN):
		    print_UNIV_EXTERNAL (pe, 1, NULL, NULL,
						NULL);
		    return;

		default:
		    vtag (str, (int) pe->pe_class, (int) pe->pe_id);
		    break;
	    }
	    vpush (str);
	    for (p = pe->pe_cons; p; p = p->pe_next)
		vunknown (str, p);
	    vpop (str);
	    break;

	case PE_FORM_ICONS:
	    vtag (str, (int) pe->pe_class, (int) pe->pe_id);
	    vstring (str, pe);
	    break;
    }
}

void
vpushstr (VSTRUCT* str, char *cp)
{
    str->vfp = NULL;
    str->vbp = str->vsp = cp;

    str->vlevel = str->didname = str->didvpush = str->didvpop = str->docomma = 0;
}

void
vpopstr (VSTRUCT* str)
{
    while (--str->vbp >= str->vsp)
	if (*str->vbp != ' ')
	    break;
    *++str->vbp = 0;

    str->vfp = stdout;
}

static char *
newbuf (VSTRUCT* str, int i)
{
    return (char *)malloc ((unsigned int) i + 1);
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

