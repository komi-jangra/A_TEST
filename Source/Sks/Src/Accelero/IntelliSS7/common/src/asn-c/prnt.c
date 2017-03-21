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
 * LOG: Revision 1.1  2007/03/30 04:50:20  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:19  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/06 21:05:15  mmiers
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
 * LOG: Revision 3.3  2001/02/14 20:44:32  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.2  2001/01/04 17:21:57  hdivoux
 * LOG: symbol collision
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:27  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:40  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/07/22 00:34:36  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.10  1999/06/30 16:15:51  mmiers
 * LOG:
 * LOG:
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.9  1999/06/11 15:44:30  fhasle
 * LOG:
 * LOG:
 * LOG: Formatting, check for NULL pointer.
 * LOG:
 * LOG: Revision 1.8  1999/06/10 23:15:27  mmiers
 * LOG:
 * LOG:
 * LOG: Dangling memory leak.
 * LOG:
 * LOG: Revision 1.7  1999/06/01 17:15:08  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.6  1999/03/02 18:14:52  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the header file ordering (I did it again).
 * LOG:
 * LOG: Revision 1.5  1999/03/01 18:12:12  mmiers
 * LOG:
 * LOG:
 * LOG: Clean up the current build.
 * LOG:
 * LOG: Revision 1.4  1999/02/26 04:09:51  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:47:58  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:41  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:41  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.17  1998/10/23 18:00:01  jrao
 * LOG: Fix prnt bugs (missing pointers, etc).
 * LOG:
 * LOG: Revision 1.16  1998/10/23 17:51:04  jrao
 * LOG: Must initialize print function.
 * LOG:
 * LOG: Revision 1.15  1998/10/23 17:18:53  jrao
 * LOG: Change tertiary operator to if/then to satisfy HP compiler.
 * LOG:
 * LOG: Revision 1.14  1998/10/23 16:05:34  mmiers
 * LOG: AsnC is now threadsafe, except for ODE.
 * LOG:
 * LOG: Revision 1.13  1998/10/23 00:19:18  mmiers
 * LOG: Working on pepsy.
 * LOG:
 * LOG: Revision 1.12  1998/10/22 16:28:32  mmiers
 * LOG: Getting pepsy thread-safe.
 * LOG:
 * LOG: Revision 1.11  1998/10/22 00:47:40  whu
 * LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 * LOG:
 * LOG: Revision 1.10  1998/10/21 19:43:51  mmiers
 * LOG: HPUX update for autobuild.
 * LOG:
 * LOG: Revision 1.9  1998/10/21 19:20:17  mmiers
 * LOG: Update for ALPHA build.
 * LOG:
 * LOG: Revision 1.8  1998/10/21 17:48:20  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 *
 *****************************************************************************/

#if defined(__STDC__) || defined(WIN32)
#include <stdarg.h>
#else
#include <varargs.h>
#endif

/* LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 */
#include "pepsy-driver.h"
#include <asn-c/AsnC.h>

#ident "$Id: prnt.c,v 1.1.1.1 2007-10-08 11:11:41 bsccs2 Exp $"

#define PRINT_TYPES	1
#define CHOICE_PUSH
#define EXTRA_BRACKETS  1

extern int pepsylose(modtyp *a, ptpe *b, PE pe, ...);
extern PE p_setpresent(PE head, ptpe *p, modtyp *mod);

ptpe *next_ptpe(ptpe *);
extern int  ppepsylose (modtyp *module, ptpe *p, PE pe, ...);
extern void pr_entry(ptpe *p);

#define NEXT_PTPE(p)	        (p = next_ptpe(p))
#define CHKTAG(mod, p, pe)	p_ismatch(p, mod, pe->pe_class, pe->pe_id)

static int p_pr_obj(int expl, PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_type(int expl, PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_seq(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_set(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_seqof(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_setof(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_choice(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_pr_etype(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str);

static void dmp_ptpe(char *s, ptpe *p, modtyp *mod, VSTRUCT* str);
static int p_ismatch(ptpe *p, modtyp *mod, unsigned int cl, unsigned int tag);

/*
 * to guarentee the rules that vname and a vprint-type routine are called
 * alternatively. Basically can't have two vname's in a row
 */
/* if vnamelock > 0 don't call vname */
#define VNAME(x) \
    if (str->vnamelock++ <= 0) vname(str, (x))
#define VTAG(cl, tag) \
    if (str->vnamelock++ <= 0) vtag(str, (int)cl, (int)tag)
#define VPRINT(x) \
    (str->vnamelock = 0, vprint x)
#define VSTRING(x) \
    (str->vnamelock = 0, vstring(str, x))
#define VUNKNOWN(x) \
    (str->vnamelock = 0, vunknown(str, x))
#define VPUSH(x) \
    (str->vnamelock = 0, vpush(x))
#define VPOP(x) \
    (str->vnamelock = 0, vpop(x))


int do_prnt(int typ, modtyp *mod, PE pe, int isExplicit, VSTRUCT* str);

/*
 * Print out ASN data given in pe using the information given in the tables
 * int	   typ; 		which type it is
 * modtyp *mod;			ASN Module it is from
 * PE      pe;
 * int     isExplicit;	nonzero means we are call top level 
 *			 print final \n
 * int    *len;
 * char  **buf;
 */
int
prnt_f(int typ, modtyp *mod, PE pe, int isExplicit, int *len, char **buf)
{
    VSTRUCT str;

    memset(&str, 0, sizeof(VSTRUCT));

    str.vfp = stdout;
    str.vfnx = fprintf;

    return do_prnt(typ, mod, pe, isExplicit, &str);
}

int
do_prnt(int typ, modtyp *mod, PE pe, int isExplicit, VSTRUCT* str)
{
    ptpe   *p;

    if (typ < 0 || typ >= mod->md_nentries)
    {
	return (ppepsylose (mod, NULL, pe, "prnt_f:Illegal type %d\n",typ));
    }

    p = mod->md_ptab[typ];

    if (p->pe_type != PE_START)
    {
	return (ppepsylose (mod, p, pe, "prnt_f: missing PE_START\n"));
    }

#if EXTRA_BRACKETS
    if (isExplicit)
    {
	if (p->pe_typename)
        {
	    VNAME(*p->pe_typename);
        }
    }
    VPUSH(str);
#endif


    if (p_pr_obj(isExplicit, pe, p, mod, str) == NOTOK)
    {
#if EXTRA_BRACKETS
	VPOP(str);
#endif
	return (NOTOK);
    }

#if EXTRA_BRACKETS
    VPOP(str);
#endif
    return (OK);
}

/*
 * Parse an object. The top level of an object does not have any
 * offset field which makes it different to pr_type routine which
 * must assume that it has an offset.
 */
static int
p_pr_obj(int expl, PE pe, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    int     cnt = 0;

#if PRINT_TYPES
    if (p->pe_typename)
    {
	VNAME(*p->pe_typename);
    }
#endif
    if (pe == NULL)
    {
	return ppepsylose(mod, p, pe, "PE empty");
    }

    p++;
    while (p->pe_type != PE_END)
    {
	if (ISDTYPE(p) && expl && CHKTAG(mod, p, pe) == 0)
        {
	    if (DEFAULT(p))
            {
		return (ppepsylose (mod, p, pe,
		    "p_pr_obj:Default not implemented\n"));
	    }
	    else if (POPTIONAL(p))
            {
		return (NO_DATA_USED);
            }
	    else
            {
		return (ppepsylose (mod, p, pe,
		    "p_pr_obj:missing mandatory parameter", p, mod));
	    }
	}
	if (p->pe_typename)
        {
	    VNAME(*p->pe_typename);
        }

	switch (p->pe_type)
        {
	case PE_END:
	case PE_START:
	    goto bad;

	case UCODE:
	    if (mod->md_pucode == NULL ||
                (*mod->md_pucode) (pe, p) == NOTOK)
            {
		goto bad;
            }
	    break;


	default:
	    if (p_pr_type(expl, pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;
	}

	if (ISDTYPE(p) && cnt > 0)
        {
	    return (ppepsylose (mod, p, pe, "p_pr_obj:compound type found\n"));
        }

	if (ISDTYPE(p) && pe != NULL)
        {
	    return (OK);
	}

	if (NEXT_PTPE(p) == NULL)
        {
	    goto bad;
        }
    }

    return (OK);

bad:
    return (NOTOK);
}


/*
 * Parse a single type. If a basic type parse it, if a compound type
 * call the appropriate parsing routine
 */
static int
p_pr_type(int expl, PE pe, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    int     cnt = 0;
    integer i;
    OID     oid;

    if (pe == NULL)
    {
	return ppepsylose(mod, p, pe, "PE empty");
    }

    while (p->pe_type != PE_END)
    {
	if (ISDTYPE(p) && expl && CHKTAG(mod, p, pe) == 0)
        {
	    if (DEFAULT(p))
            {
#ifdef	PRINT_DEFAULTS
		setpval(p, p + 1, mod);
#endif
		return (OK);
	    }
            else if (POPTIONAL(p))
            {
		return (OK);
            }
	    else
            {
		dmp_ptpe("p_pr_type:missing mandatory parameter", p, mod, str);
		
                goto bad;
	    }
	}

	switch (p->pe_type)
        {
	case PE_END:
	case PE_START:
	    goto bad;

	case BOPTIONAL:
	    if (CHKTAG(mod, p + 1, pe) == 0)
            {
		return (OK);
	    }
	    p++;
	    continue;

	case UCODE:
	    if (mod->md_pucode == NULL ||
                (*mod->md_pucode) (pe, p) == NOTOK)
            {
		goto bad;
            }
	    break;

	case ETAG:
	    if (p_pr_etype(pe->pe_cons, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case SSEQ_START:
	case SEQ_START:
	    if (p_pr_seq(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SSEQOF_START:
	case SEQOF_START:
	    if (p_pr_seqof(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SSET_START:
	case SET_START:
	    if (p_pr_set(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SSETOF_START:
	case SETOF_START:
	    if (p_pr_setof(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case IMP_OBJ:
	    p++;
	    if (p->pe_type == EXTOBJ || p->pe_type == SEXTOBJ)
            {
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		    goto bad;
                }
	    }
            else
            {
		if (p_pr_obj(0, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
	    }
	    break;

	case SOBJECT:
	case OBJECT:
	    if (p_pr_obj(expl, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SCHOICE_START:
	case CHOICE_START:
	    if (p_pr_choice(pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case SEXTOBJ:
	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD)
            {
		return (ppepsylose (mod, p, pe, "p_pr_type: missing EXTMOD"));
	    }
	    if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
            {
		   goto bad;
            }
	    break;

	case INTEGER:
	    if (pe != NULL)
            {
		if ((i = prim2num(pe)) == NOTOK && pe->pe_errno != PE_ERR_NONE)
                {
		    goto bad;
                }
		VPRINT((str, "%d", i));
	    }
	    break;

#ifdef	PEPSY_REALS
	case REALTYPE:
	    if (pe != NULL)
            {
		double r;

		if ((r = prim2real(pe)) == NOTOK &&
                    pe->pe_errno != PE_ERR_NONE)
                {
		    goto bad;
                }
		VPRINT((str, "%g", r));
	    }
	    break;
#endif

	case BOOLEAN:
	    if (pe != NULL)
            {
		if ((i = prim2flag(pe)) == NOTOK)
                {
		    goto bad;
                }
		VPRINT((str, i ? "TRUE" : "FALSE"));
	    }
	    break;

	case ASN_NULL:
	    VPRINT((str, "NULL"));
	    break;

	case SANY:
	    if (pe != NULL)
            {
		if (pe->pe_errno != PE_ERR_NONE)
                {
		    goto bad;
		}
                else
                {
		    VUNKNOWN(pe);
                }
	    }
	    break;


	case ANY:
	    if (pe != NULL)
            {
		if (pe->pe_errno != PE_ERR_NONE)
                {
		    goto bad;
		}
                else
                {
		    VUNKNOWN(pe);
                }
	    }
	    break;

	case SOCTETSTRING:
	    if (pe != NULL)
            {
		VSTRING(pe);
	    }
	    break;

	case OCTETSTRING:
	case T_STRING:
	case OCTET_PTR:
	    if (pe != NULL)
            {
		VSTRING(pe);
	    }
	    break;

	case SBITSTRING:
	    if (pe != NULL)
            {
		PE	bstr;

		if ((bstr = prim2bit(pe)) == NULL)
                {
		    goto bad;
                }
		if (p -> pe_ucode >= 0 && mod->md_ptrtab &&
		    mod -> md_ptrtab[p -> pe_ucode] &&
		    bstr -> pe_nbits < LOTSOFBITS)
                {
                    char *c = NULL;

                    c = bit2str(str, bstr,
  			        mod -> md_ptrtab[p -> pe_ucode]);
		    VPRINT((str, "%s", c));
                    if (c)
                    {
                        free(c);
                    }
                }
		else if (bstr->pe_nbits < LOTSOFBITS)
                {
                    char *c = NULL;

                    c = bit2str(str, bstr, "\020");
		    VPRINT((str, "%s", c));
                    if (c)
                    {
                        free(c);
                    }
                }
		else
                {
		    VUNKNOWN(pe);
                }
	    }
	    break;

	case BITSTR_PTR:
	case BITSTRING:
	    if (pe != NULL)
            {
		PE	bstr;

		if ((bstr = prim2bit(pe)) == NULL)
                {
		    goto bad;
                }
		if (p -> pe_ucode >= 0 && mod->md_ptrtab &&
		    mod -> md_ptrtab[p -> pe_ucode] &&
		    bstr -> pe_nbits < LOTSOFBITS)
                {
                    char *c = NULL;

                    c = bit2str(str, bstr,
			        mod -> md_ptrtab[p -> pe_ucode]);
		    VPRINT((str, "%s", c));
                    if (c)
                    {
                        free(c);
                    }
                }
		else if (bstr->pe_nbits < LOTSOFBITS)
                {
                    char *c = NULL;
                    
                    c = bit2str(str, bstr, "\020");
		    VPRINT((str, "%s", c));
                    if (c)
                    {
                        free(c);
                    }
                }
		else
                {
		    VUNKNOWN(pe);
                }
	    }
	    break;

	case SOBJID:
	    if ((oid = (OID) prim2oid(pe)) == NULL)
            {
		goto bad;
	    }
            else
            {
                char buf[BUFSIZ];

		if (oid2ode(oid, buf, BUFSIZ) == ITS_SUCCESS)
                {
                    VPRINT((str, buf));
                }
                else
                {
                    VPRINT((str, "overflow"));
                }

                oid_free(oid);
	    }
	    break;

	case OBJID:
	    if ((oid = (OID) prim2oid(pe)) == NULL)
            {
		goto bad;
	    }
            else
            {
                char buf[BUFSIZ];

		if (oid2ode(oid, buf, BUFSIZ) == ITS_SUCCESS)
                {
                    VPRINT((str, buf));
                }
                else
                {
                    VPRINT((str, "overflow"));
                }

                oid_free(oid);
	    }
	    break;

	default:
	    return (ppepsylose (mod, p, pe, "p_pr_type: %d not implemented\n",
		p->pe_type));
	}

	if (ISDTYPE(p) && cnt > 0)
        {
	    return (ppepsylose (mod, p, pe, "p_pr_type:compound type found\n"));
        }

	if (ISDTYPE(p) && pe != NULL)
        {
	    return (OK);
        }

	if (NEXT_PTPE(p) == NULL)
        {
	    goto bad;
        }
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * Parse a sequence, calling appropriate routines to parse each sub
 * type
 */
static int
p_pr_seq(PE head, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    PE	    pe;

    if (p->pe_type != SEQ_START && p->pe_type != SSEQ_START)
    {
	return (ppepsylose (mod, p, head, "p_pr_seq: missing SEQ_START\n"));
    }

#if PRINT_TYPES
    if (p->pe_typename)
    {
	VNAME(*p->pe_typename);
    }
#endif
    VPUSH(str);

    if (head == NULL)
    {
	return ppepsylose(mod, p, head, "PE empty");
    }

    p++;
    if (p->pe_type == DFLT_B)
    {
	p++;
    }

    pe = first_member(head);
    while (p->pe_type != PE_END)
    {
	if (ISDTYPE(p) && POPTIONAL(p))
        {
	    if (pe == NULL || CHKTAG(mod, p, pe) == 0)
            {
		goto next;
            }
	}
        else if (ISDTYPE(p) && (pe == NULL || CHKTAG(mod, p, pe) == 0))
        {
	    if (DEFAULT(p))
            {
#ifdef	PRINT_DEFAULTS
		setpval(p, p + 1, mod);
#endif
		goto next;
	    }
            else
            {
		dmp_ptpe("p_pr_seq:missing mandatory parameter", p, mod, str);
		
                goto bad;
	    }
	}

	if (p->pe_typename)
        {
	    VNAME(*p->pe_typename);
        }

	switch (p->pe_type)
        {
	case OPTL:
	    break;

	case UCODE:
	    if (mod->md_pucode == NULL ||
                (*mod->md_pucode) (pe, p) == NOTOK)
            {
		goto bad;
            }
	    break;

	case BOPTIONAL:
	    if (CHKTAG(mod, p + 1, pe) == 0)
            {
		goto next;
            }
	    p++;
	    continue;

	case ETAG:
	    if (p_pr_type(1, pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case SEQ_START:
	    if (p_pr_seq(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SEQOF_START:
	    if (p_pr_seqof(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SET_START:
	    if (p_pr_set(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SETOF_START:
	    if (p_pr_setof(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case IMP_OBJ:
	    p++;
	    if (p->pe_type == EXTOBJ)
            {
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		    goto bad;
                }
	    }
            else
            {
		if (p_pr_obj(0, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
	    }
	    break;

	case SOBJECT:
	    if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case OBJECT:
#if PRINT_TYPES
            if (p->pe_typename)
            {
	        VNAME(*p->pe_typename);
            }
#endif
	    if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SCHOICE_START:
	case CHOICE_START:
	    if (p_pr_choice(pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case SEXTOBJ:
	    if (p[1].pe_type != EXTMOD)
            {
		return (ppepsylose (mod, p, pe, "p_pr_seq: missing EXTMOD"));
	    }
	    if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD)
            {
		return (ppepsylose (mod, p, pe, "p_pr_seq: missing EXTMOD"));
	    }
	    if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	default:
	    if (p_pr_type(1, pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;
	}

	if (ISDTYPE(p) && pe != NULL)
        {
	    pe = next_member(head, pe);
        }
next:
	if (NEXT_PTPE(p) == NULL)
        {
	    goto bad;
        }
    }

    VPOP(str);
    return (OK);

bad:
    VPOP(str);
    return (NOTOK);
}


/*
 * Parse a set, calling appropriate routines to parse each sub type
 */
static int
p_pr_set(PE head, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    PE pe = NULL;

    if (p->pe_type != SET_START && p->pe_type != SSET_START)
    {
	return (ppepsylose (mod, p, head, "p_pr_seq: missing SET_START\n"));
    }

#if PRINT_TYPES
    if (p->pe_typename)
    {
	VNAME(*p->pe_typename);
    }
#endif
    VPUSH(str);

    if (head == NULL)
    {
	return ppepsylose(mod, p, head, "PE empty");
    }

    p++;
    if (p->pe_type == DFLT_B)
    {
	p++;
    }

    while (p->pe_type != PE_END)
    {

	head -> pe_errno = PE_ERR_NONE;
	if (ISDTYPE(p) && POPTIONAL(p))
        {
	    pe = (PE) p_setpresent(head, p, mod);
	    if (pe == NULL && head -> pe_errno != PE_ERR_NONE)
            {
		goto bad;
            }

	    if (pe == NULL)
            {
		goto next;
            }
	}
        else if (ISDTYPE(p) &&
                 (pe = (PE) p_setpresent(head, p, mod)) == NULL)
        {
	    if (head -> pe_errno != PE_ERR_NONE)
            {
		goto bad;
            }

	    if (DEFAULT(p))
            {
#ifdef PRINT_DEFAULTS
		setpval(p, p + 1, mod);
#endif
		goto next;
	    }
            else
            {
		dmp_ptpe("p_pr_set:missing mandatory parameter", p, mod, str);
		
                goto bad;
	    }
	}

	if (p->pe_typename)
        {
	    VNAME(*p->pe_typename);
        }

	switch (p->pe_type)
        {
	case OPTL:
	    break;

	case UCODE:
	    if (mod->md_pucode == NULL ||
                (*mod->md_pucode) (pe, p) == NOTOK)
            {
		goto bad;
            }
	    break;

	case BOPTIONAL:
	    if ((pe = (PE) p_setpresent(head, p + 1, mod)) == NULL)
            {
		if (head -> pe_errno == PE_ERR_NONE)
                {
		    goto next;
                }
		else
                {
		    goto bad;
                }
	    }
	    p++;
	    continue;

	case ETAG:
	    if (p_pr_type(1, pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case SEQ_START:
	    if (p_pr_seq(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SEQOF_START:
	    if (p_pr_seqof(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SET_START:
	    if (p_pr_set(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SETOF_START:
	    if (p_pr_setof(pe, p, mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case IMP_OBJ:
	    p++;
	    if (p->pe_type == EXTOBJ)
            {
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		       goto bad;
                }
	    }
            else
            {
		if (p_pr_obj(0, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
	    }
	    break;

	case SOBJECT:
	    if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case OBJECT:
	    if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
            {
		goto bad;
	    }
	    break;

	case SCHOICE_START:
	case CHOICE_START:
	    if (p_pr_choice(pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	case SEXTOBJ:
	    if (p[1].pe_type != EXTMOD)
            {
		return (ppepsylose (mod, p, pe, "p_pr_set: missing EXTMOD"));
	    }

	    if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
            {
		    return (NOTOK);
            }
	    break;

	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD)
            {
		return (ppepsylose (mod, p, pe, "p_pr_set: missing EXTMOD"));
	    }

	    if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
            {
		goto bad;
            }
	    break;

	default:
	    if (p_pr_type(1, pe, p, mod, str) == NOTOK)
            {
		goto bad;
            }
	    break;
	}

next:
	if (NEXT_PTPE(p) == NULL)
        {
	    goto bad;
        }
    }

    VPOP(str);
    return (OK);

bad:
    VPOP(str);
    return (NOTOK);
}


/*
 * Parse a sequence of calling appropriate routines to parse each sub
 * type
 */
static int
p_pr_seqof(PE head, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    PE	    pe;
    ptpe   *start;		/* first entry in list */
    int     dflt = 0;

    if (p->pe_type != SEQOF_START && p->pe_type != SSEQOF_START)
    {
	return (ppepsylose (mod, p, head, "p_pr_seqof: missing SEQOF_START\n"));
    }

#if PRINT_TYPES
    if (p->pe_typename)
    {
	VNAME(*p->pe_typename);
    }
#endif
    VPUSH(str);

    if (head == NULL)
    {
	return ppepsylose(mod, p, head, "PE empty");
    }

    p++;
    if (p->pe_type == DFLT_B)
    {
	p++;
    }

    start = p;

    pe = first_member(head);
    while (pe != NULL)
    {
	while (p->pe_type != PE_END)
        {
	    if (ISDTYPE(p) && CHKTAG(mod, p, pe) == 0)
            {
		if (DEFAULT(p))
                {
		    return (ppepsylose (mod, p, pe,
			"p_pr_seqof:Default not implemented\n"));
                }
		else if (POPTIONAL(p))
                {
		    goto next;
                }
		else
                {
		    return (ppepsylose (mod, p, pe,
			"p_pr_seqof:missing mandatory parameter"));
		}
	    }

	    if (p->pe_typename)
            {
		VNAME(*p->pe_typename);
            }

	    switch (p->pe_type)
            {
	    case UCODE:
		if (mod->md_pucode == NULL ||
                    (*mod->md_pucode) (pe, p) == NOTOK)
                {
		    goto bad;
                }
		break;

	    case BOPTIONAL:
		if (CHKTAG(mod, p + 1, pe) == 0)
                {
		    goto next;
                }
		p++;
		continue;

	    case ETAG:
		if (p_pr_type(1, pe, p, mod, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    /*
	     * case SCTRL:	parm = (char *) ((char *) parm);
	     * break;
	     */

	    case SEQ_START:
		if (p_pr_seq(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SEQOF_START:
		if (p_pr_seqof(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SET_START:
		if (p_pr_set(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SETOF_START:
		if (p_pr_setof(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SOBJECT:
		if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case OBJECT:
		if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SCHOICE_START:
	    case CHOICE_START:
		if (p_pr_choice(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    case SEXTOBJ:
		if (p[1].pe_type != EXTMOD)
                {
		    return (ppepsylose (mod, p, pe,"p_pr_seqof:missing EXTMOD"));
		}
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		     goto bad;
                }
		break;

	    case EXTOBJ:
		if (p[1].pe_type != EXTMOD)
                {
		    return (ppepsylose (mod, p, pe,"p_pr_seqof:missing EXTMOD"));
		}
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    default:
		if (p_pr_type(1, pe, p, mod, str) == NOTOK)
                {
		    goto bad;
                }
		break;
	    }

	    if (ISDTYPE(p) && dflt == 0)
            {
		pe = next_member(head, pe);
            }
next:
	    if (NEXT_PTPE(p) == NULL)
            {
		goto bad;
            }
	}

	/* parm = (char *) (parm); */
	p = start;
    }

    VPOP(str);
    return (OK);

bad:
    VPOP(str);
    return (NOTOK);
}

/*
 * Parse a setof, calling appropriate routines to parse each sub type
 */
static int
p_pr_setof(PE head, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    PE	    pe;
    ptpe   *start;

    if (p->pe_type != SETOF_START && p->pe_type != SSETOF_START)
    {
	return (ppepsylose (mod, p, head, "p_pr_setof: missing SETOF_START\n"));
    }

#if PRINT_TYPES
    if (p->pe_typename)
    {
	VNAME(*p->pe_typename);
    }
#endif
    VPUSH(str);

    if (head == NULL)
    {
	return ppepsylose(mod, p, head, "PE empty");
    }

    p++;
    if (p->pe_type == DFLT_B)
    {
	p++;
    }

    start = p;
    for (pe = first_member(head); pe; pe = next_member(head, pe))
    {
	while (p->pe_type != PE_END)
        {
	    if (pe == NULL || CHKTAG(mod, p, pe) == 0)
            {
		if (DEFAULT(p))
                {
#ifdef PRINT_DEFAULTS
		    setpval(p, p + 1, mod);
#endif
		    goto next;
		}
                else
                {
		    dmp_ptpe("p_pr_setof:missing mandatory parameter", p, mod, str);
		    goto bad;
		}
	    }

	    if (p->pe_typename)
            {
		VNAME(*p->pe_typename);
            }

	    switch (p->pe_type)
            {
	    case UCODE:
		if (mod->md_pucode == NULL ||
                    (*mod->md_pucode) (pe, p) == NOTOK)
                {
		    goto bad;
                }
		break;

	    case BOPTIONAL:
		if ((pe = (PE) p_setpresent(head, p + 1, mod)) == NULL)
                {
		    goto next;
                }
		p++;
		continue;

	    case ETAG:
		if (p_pr_type(1, pe->pe_cons, p, mod, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    /*
	     * case SCTRL: parm = (char *) (parm); break;
	     */

	    case SEQ_START:
		if (p_pr_seq(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SEQOF_START:
		if (p_pr_seqof(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SET_START:
		if (p_pr_set(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SETOF_START:
		if (p_pr_setof(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SOBJECT:
		if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case OBJECT:
		if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
                {
		    goto bad;
		}
		break;

	    case SCHOICE_START:
	    case CHOICE_START:
		if (p_pr_choice(pe, p, mod, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    case SEXTOBJ:
		if (p[1].pe_type != EXTMOD)
                {
		    return (ppepsylose (mod, p, pe,"p_pr_setof:missing EXTMOD"));
		}
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    case EXTOBJ:
		if (p[1].pe_type != EXTMOD)
                {
		    return (ppepsylose (mod, p, pe,"p_pr_setof:missing EXTMOD"));
		}
		if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
                {
		    goto bad;
                }
		break;

	    default:
		if (p_pr_type(1, pe, p, mod, str) == NOTOK)
                {
		    goto bad;
                }
		break;
	    }

next:
	    if (NEXT_PTPE(p) == NULL)
            {
		goto bad;
            }
	}

        /* parm = (char *)(parm); */
	p = start;
    }

    VPOP(str);
    return (OK);

bad:
    VPOP(str);
    return (NOTOK);

}

/*
 * parse a choice field. This means find which choice is taken
 */
static int
p_pr_choice(PE head, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    if (p->pe_type != CHOICE_START && p->pe_type != SCHOICE_START)
    {
	return (ppepsylose (mod, p, head, "p_pr_choice:missing CHOICE_START"));
    }

#if PRINT_TYPES
    if (p->pe_typename)
    {
	VNAME(*p->pe_typename);
    }
#endif

#ifdef CHOICE_PUSH
    VPUSH(str);
#endif
    if (head == NULL)
    {
	return ppepsylose(mod, p, head, "PE empty");
    }

    p++;
    if (p->pe_type == DFLT_B)
    {
	p++;
    }

    if (p->pe_type == SCTRL)
    {
	p++;
    }

    for (; p->pe_type != PE_END; NEXT_PTPE(p))
    {
	if (ISDTYPE(p) && p_ismatch(p, mod, head->pe_class, head->pe_id))
        {
	    if (p->pe_typename)
            {
		VNAME(*p->pe_typename);
            }

	    if (p_pr_type(0, head, p, mod, str) == NOTOK)
            {
		return (NOTOK);
            }

#ifdef CHOICE_PUSH
	    VPOP(str);
#endif
	    NEXT_PTPE(p);
	    if (p->pe_type == UCODE)
            {
		if (mod->md_pucode == NULL ||
                    (*mod->md_pucode) (head, p) == NOTOK)
                {
		    return (NOTOK);
                }
	    }

	    return (OK);
	}
    }

    dmp_ptpe("p_pr_choice: no choice taken", p, mod, str);
#ifdef CHOICE_PUSH
    VPOP(str);
#endif

    return (NOTOK);
}

/*
 * Calculate the next ptpe entry in the sequence. Count a sequence as
 * one element
 */
ptpe   *
next_ptpe(ptpe *p)
{
    int     level;

    level = 0;
    if (p->pe_type == PE_END)
    {
	ppepsylose (NULL, p, NULL,
	    "next_ptpe: unexpected PE_END");

        return (NULL);
    }

    do
    {
again:
	switch (p->pe_type)
        {
	case SSEQ_START:
	case SSEQOF_START:
	case SSET_START:
	case SSETOF_START:
	case SCHOICE_START:
	case SEQ_START:
	case SEQOF_START:
	case SET_START:
	case SETOF_START:
	case CHOICE_START:
	    level++;
	    break;

	case UCODE:
	case SCTRL:
	case CH_ACT:
	case INTEGER:
	case REALTYPE:
	case BOOLEAN:
	case SANY:
	case ANY:
	case ASN_NULL:
	case OBJECT:
	case SOBJECT:
	case BITSTRING:
	case SBITSTRING:
	case BITSTR_LEN:
	case OCTETSTRING:
	case T_STRING:
	case OCTET_LEN:
	case SOCTETSTRING:
	case OBJID:
	case SOBJID:
	case OPTL:
	case EXTMOD:
	case DFLT_B:
	    break;

	case OCTET_PTR:
	case BITSTR_PTR:
	case IMP_OBJ:
	case ETAG:
	case EXTOBJ:
	case SEXTOBJ:
	case DFLT_F:
	case BOPTIONAL:
	    p++;
	    goto again;

	case PE_END:
	    level--;
	    break;

	default:
	    ppepsylose (NULL, p, NULL,
		"next_ptpe: unknown type %d\n", p->pe_type);
	    
            return (NULL);
	}

	p++;
    }
    while (level > 0 || p->pe_type == DFLT_B);

    return (p);
}

/*
 * Parse a single type for explicit tag If a basic type parse it, if
 * a compound type call the appropriate parsing routine
 */
static int
p_pr_etype(PE pe, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    integer	i;
    OID     oid;

    if (p->pe_type != ETAG)
    {
	return (ppepsylose (mod, p, pe, "p_pr_etype: missing ETAG\n"));
    }    

    if (PRINT_TAG(p))
    {
	VTAG (CLASS (p), TAG (p));
    }

    if (pe == NULL)
    {
	return ppepsylose(mod, p, pe, "PE empty");
    }
    p++;

    switch (p->pe_type)
    {
    case PE_END:
    case PE_START:
	goto bad;

    case UCODE:
	if (mod->md_pucode == NULL ||
            (*mod->md_pucode) (pe, p) == NOTOK)
        {
	    goto bad;
        }
	break;

    case BOPTIONAL:
	return (ppepsylose (mod, p, pe, "p_pr_etype:illegal BOPTIONAL\n"));

    case ETAG:
	if (p_pr_etype(pe->pe_cons, p, mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case SSEQ_START:
    case SEQ_START:
	if (p_pr_seq(pe, p, mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case SSEQOF_START:
    case SEQOF_START:
	if (p_pr_seqof(pe, p, mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case SSET_START:
    case SET_START:
	if (p_pr_set(pe, p, mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case SSETOF_START:
    case SETOF_START:
	if (p_pr_setof(pe, p, mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case IMP_OBJ:
	p++;
	if (p->pe_type == EXTOBJ)
        {
	    if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
            {
		   goto bad;
            }
	}
        else
        {
#if PRINT_TYPES
            if (p->pe_typename)
            {
                VNAME(*p->pe_typename);
            }
#endif
	    if (p_pr_obj(0, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
            {
		goto bad;
            }
	}
	break;

    case SOBJECT:
#if PRINT_TYPES
        if (p->pe_typename)
        {
	    VNAME(*p->pe_typename);
        }
#endif
	if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case OBJECT:
#if PRINT_TYPES
        if (p->pe_typename)
        {
            VNAME(*p->pe_typename);
        }
#endif
	if (p_pr_obj(1, pe, mod->md_ptab[p->pe_tag], mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case SCHOICE_START:
    case CHOICE_START:
	if (p_pr_choice(pe, p, mod, str) == NOTOK)
        {
	    goto bad;
        }
	break;

    case SEXTOBJ:
	if (p[1].pe_type != EXTMOD)
        {
	    return (ppepsylose (mod, p, pe, "p_pr_etype: missing EXTMOD"));
	}
	if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
        {
	       goto bad;
        }
	break;

    case EXTOBJ:
	if (p[1].pe_type != EXTMOD)
        {
	    return (ppepsylose (mod, p, pe, "p_pr_etype: missing EXTMOD"));
	}
	if (do_prnt(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0, str) == NOTOK)
        {
	       goto bad;
        }
	break;

    case INTEGER:
	if (pe != NULL)
        {
	    if ((i = prim2num(pe)) == NOTOK && pe->pe_errno != PE_ERR_NONE)
            {
		goto bad;
            }
	    VPRINT((str, "%d", i));
	}
	break;

#ifdef	PEPSY_REALS
    case REALTYPE:
	if (pe != NULL)
        {
	    double r;

	    if ((r = prim2real(pe)) == NOTOK &&
                pe->pe_errno != PE_ERR_NONE)
            {
		goto bad;
            }
	    VPRINT((str, "%g", r));
	}
	break;
#endif


    case BOOLEAN:
	if (pe != NULL)
        {
	    if ((i= prim2flag(pe)) == NOTOK)
            {
		goto bad;
            }
	    VPRINT((str, i ? "TRUE" : "FALSE"));
	}
	break;

    case ASN_NULL:
	VPRINT((str, "NULL"));
	break;

    case ANY:
	if (pe != NULL)
        {
	    if (pe->pe_errno != PE_ERR_NONE)
            {
		goto bad;
	    }
            else
            {
		VUNKNOWN(pe);
            }
	}
	break;

    case SANY:
	if (pe != NULL)
        {
	    if (pe->pe_errno != PE_ERR_NONE)
            {
		goto bad;
	    }
            else
            {
		VUNKNOWN(pe);
            }
	}
	break;

    case SOCTETSTRING:
    case OCTETSTRING:
    case T_STRING:
    case OCTET_PTR:
	if (pe != NULL)
        {
	    VSTRING(pe);
	}
	break;

    case BITSTRING:
    case BITSTR_PTR:
    case SBITSTRING:
	if (pe != NULL)
        {
	    PE	bstr;

	    if ((bstr = prim2bit(pe)) == NULL)
            {
		goto bad;
            }

	    if (p -> pe_ucode >= 0 && mod->md_ptrtab &&
		mod -> md_ptrtab[p -> pe_ucode] &&
		bstr -> pe_nbits < LOTSOFBITS)
            {
                char *c = NULL;

                c = bit2str(str, bstr,
		            mod -> md_ptrtab[p -> pe_ucode]);
		VPRINT((str, "%s", c));
                if (c)
                {
                    free(c);
                }
            }
	    else if (bstr->pe_nbits < LOTSOFBITS)
            {
                char *c = NULL;

                c = bit2str(str, bstr, "\020");
		VPRINT((str, "%s", c));
                if (c)
                {
                    free(c);
                }
            }
	    else
            {
		VUNKNOWN(pe);
            }
	}
	break;

    case SOBJID:
	if ((oid = prim2oid(pe)) == NULL)
        {
	    goto bad;
	}
        else
        {
            char buf[BUFSIZ];

	    if (oid2ode(oid, buf, BUFSIZ) == ITS_SUCCESS)
            {
                VPRINT((str, buf));
            }
            else
            {
                VPRINT((str, "overflow"));
            }

            oid_free(oid);
	}
	break;

    case OBJID:
	if ((oid = prim2oid(pe)) == NULL)
        {
	    goto bad;
	}
        else
        {
            char buf[BUFSIZ];

	    if (oid2ode(oid, buf, BUFSIZ) == ITS_SUCCESS)
            {
                VPRINT((str, buf));
            }
            else
            {
                VPRINT((str, "overflow"));
            }

            oid_free(oid);
	}
	break;

    default:
	return (ppepsylose (mod, p, pe, "p_pr_etype: %d not implemented\n",
	    p->pe_type));
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * Is there a match at for this tag and class pair. Return 1 if yes 0
 * if no We will search through contained objects and through choices
 */
static int 
p_ismatch(ptpe *p, modtyp *mod, unsigned int cl, unsigned int tag)
{
    if (!ISDTYPE(p))
    {
	return (0);
    }

    switch (p->pe_type)
    {
    case SOBJECT:
    case OBJECT:
	/* Needs to be changed for optional and default */
	return (p_ismatch(p = mod->md_ptab[p->pe_tag] + 1, mod, cl, tag));

    case SEXTOBJ:
    case EXTOBJ:
	if (p[1].pe_type != EXTMOD)
        {
	    ppepsylose (mod, p, NULL, "p_ismatch: missing EXTMOD");

	    return (0); /* fixup ismatch return -1 */
	}
	return (p_ismatch(EXT2MOD(mod, (p + 1))->md_ptab[p->pe_tag] + 1,
			  EXT2MOD(mod, (p + 1)), cl, tag));

    case SCHOICE_START:
    case CHOICE_START:
	for (p++; p->pe_type != PE_END; NEXT_PTPE(p))
        {
	    if (!ISDTYPE(p))
            {
		continue;
            }
	    if (p_ismatch(p, mod, cl, tag))
            {
		return (1);
            }
	}
	return (0);

    case SANY:
	return (1);

    case ANY:
	if (STAG(p) == -1)
	    return (1);
	/* else fall through - not sure if this is needed */

    default:
	return (tag == TAG(p) && cl == CLASS(p));
    }
    /* NOTREACHED */
    /* return (0); */
}

/*
 * determine if the given field is present in the data This is simple
 * if the field is a simple type with an obvious tag but in the case
 * of an object or a CHOICE type the tag is not obvious. If the
 * object is a CHOICE there are more than one possible tag that could
 * match and in this case we must try to match each one of them.
 */
PE
p_setpresent(PE head, ptpe *p, modtyp *mod)
{
    PE	    pe;
    modtyp	*nmod;

    while (!ISDTYPE(p) && p->pe_type != PE_END)
    {
	p++;
    }

    if (!ISDTYPE(p) || p->pe_type == PE_END)
    {
	return (NULL);
    }

    switch (p->pe_type)
    {
    case EXTOBJ:
    case SEXTOBJ:
	/* Needs to be changed for optional and default */
	nmod = EXT2MOD(mod, (p + 1));
	return (p_setpresent(head, p = nmod->md_ptab[p->pe_tag] + 1, nmod));

    case OBJECT:
    case SOBJECT:
	/* Needs to be changed for optional and default */
	return (p_setpresent(head, p = mod->md_ptab[p->pe_tag] + 1, mod));

    case SCHOICE_START:
    case CHOICE_START:
	for (p++; p->pe_type != PE_END; NEXT_PTPE(p))
        {
	    if (!ISDTYPE(p))
            {
		continue;
            }
	    if ((pe = (PE) p_setpresent(head, p, mod)))
            {
		return (pe);
            }
	}
	return (NULL);

    default:
	return (set_find(head, CLASS(p), TAG(p)));
    }
}

#ifdef PRINT_DEFAULTS
/*
 * set the default value to that value in the structure
 */
setpval(ptpe *typ, ptpe *dflt, modtyp *mod)
{
    int     len, i;
    integer intval;
    char   *ptr, *optr;
    PE	    pe_ptr;

    switch (typ->pe_type)
    {
    case INTEGER:
	intval = IVAL(mod, dflt);
	(*str->vfnx) (str->vfp, "%d (DEFAULT INTEGER)\n", intval);
	break;

#ifdef	PEPSY_REALS
    case REALTYPE:
	(*str->vfnx) (str->vfp, "%f (DEFAULT Real)\n", RVAL(mod, dflt));
	break;
#endif

    case BOOLEAN:
	intval = IVAL(mod, dflt);
	/*
	 * (*str->vfnx) (str->vfp, "%s  %d (DEFAULT BOOLEAN)\n",
	 * (typ->pe_typename) ? typ->pe_typename : "", charval);
	 */
	(*str->vfnx) (str->vfp, "%d (DEFAULT BOOLEAN)\n", intval);
	break;

    case ASN_NULL:
	/* Only one value */
	break;

    case SBITSTRING:
    case BITSTRING:
	(PE) pe_ptr = strb2bitstr(PVAL(mod, dflt), IVAL(mod, dflt), 0, 0);
	(*str->vfnx) (str->vfp, " '");

        optr = ptr = bitstr2strb((PE) pe_ptr, &len);
	for (i = 0; i < len; i += 8)
        {
	    (*str->vfnx) (str->vfp, "%.2x", *ptr++);
        }
	(*str->vfnx) (str->vfp, "'H (DEFAULT BITSTRING)\n");

        pe_free (pe_ptr);
	free (optr);
	break;

    case SOCTETSTRING:
    case OCTETSTRING:
	ptr = PVAL(mod, dflt);	/* array of octets */
	intval = IVAL(mod, dflt);		/* length of array */
	if (printable(ptr, intval))
        {
	    (*str->vfnx) (str->vfp, "\"");
	    for (; *ptr && intval-- > 0; ptr++)
            {
		fputc(*ptr, str->vfp);
            }
	    (*str->vfnx) (str->vfp, "\"\n");
	}
        else
        {
	    (*str->vfnx) (str->vfp, "'");
	    if (ptr)
            {
		for (; intval-- > 0; ptr++)
                {
		    (*str->vfnx) (str->vfp, "%.2x", *ptr & 0xff);
                }
	    }
	    (*str->vfnx) (str->vfp, "'H \n");
	}
	break;

    case OBJECT:
	setpval(mod->md_ptab[typ->pe_tag] + 1, dflt, mod);
	break;

    case SOBJECT:
	setpval(mod->md_ptab[typ->pe_tag] + 1, dflt, mod);
	break;

    case IMP_OBJ:
	typ++;

    case ANY:
    case SANY:
    case SEXTOBJ:
    case EXTOBJ:
    case OBJID:
    case SOBJID:
    case SEQ_START:
    case SET_START:
    case -1:			/* Just use the pepy method of null
				 * pointers */
	/*
	 * This is the posy/pepy hack way of doing things at the
	 * moment
	 */
	(char *) ptr = NULL;
	break;

    default:
	return (ppepsylose (mod, p, pe, "setpval: type %d not implemented\n",
	    typ->pe_type));
	break;
    }

}
#endif

/*
 * return non zero if we can print out the string
 */
int
printable(char *strptr, int len)
{
    if (strptr == NULL || *strptr == '\0')
    {
	return (0);
    }

     while (len-- > 0)
     {
	if (!isprint(*strptr++))
        {
	    return (0);
        }
    }

    return (1);
}

/*
 * (Dump) Print out a printable entry in a human recognisable form
 */
static void
dmp_ptpe(char *s, ptpe *p, modtyp *mod, VSTRUCT* str)
{
    int     i, j;
    ptpe  **par, **prev;
    char   *name = NULL;

    fprintf(str->vfp, "%s:(%s)", s, mod->md_name);
    /*
     * Calculate what table it is in - we assume they are in order of
     * increasing address
     */

    par = NULL;
    if (mod->md_ptab != NULL && mod->md_ptab[0] < p)
    {
	par = mod->md_ptab;
	name = "Printing:";
    }
    if (par == NULL)
    {
	fprintf(str->vfp, "can't find entry %p\n", p);
	return;
    }
    prev = par;
    for (i = mod->md_nentries; i > 0; i--)
    {
	if (*par > p)
        {
	    break;
        }
	par++;
    }

    if (par == prev)
    {
	ppepsylose (mod, p, NULL,
	    "dmp_ptpe:par == prev == %p internal error\n", par);

        return;
    }

    par--;
    j = p - *par;

    fprintf(str->vfp, "%s type %d + %d ", name, par - prev, j);
    pr_entry(p);
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

