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
 * LOG: Revision 1.1  2007/03/30 04:49:46  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:18  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:13  cvsadmin
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
 * LOG: Revision 3.3  2001/02/14 20:33:12  mmiers
 * LOG: Add ident
 * LOG:
 * LOG: Revision 3.2  2001/01/04 17:21:57  hdivoux
 * LOG: symbol collision
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:36  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:19:17  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:23  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/07/22 00:34:35  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.4  1999/03/02 18:14:52  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the header file ordering (I did it again).
 * LOG:
 * LOG: Revision 1.3  1999/02/26 04:09:51  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1999/02/26 00:47:57  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:04  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.8  1998/10/23 16:05:33  mmiers
 * LOG: AsnC is now threadsafe, except for ODE.
 * LOG:
 * LOG: Revision 1.7  1998/10/22 00:47:39  whu
 * LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 * LOG:
 * LOG: Revision 1.6  1998/10/21 17:48:19  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 *
 *****************************************************************************/

/* LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 */

#include "pepsy-driver.h"
#include <asn-c/AsnC.h>

#ident "$Id: enc.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $"

#ifndef	PEPYPARM
#define PEPYPARM	char *
#endif


extern int pepsylose(modtyp *a, ptpe *b, PE pe, ...);
extern ptpe *next_tpe(ptpe *), *fdflt_f(ptpe *);
extern char *pr_petype();
char   *idname(), *clname();
extern int same(ptpe *typ, ptpe *dflt, char *parm, modtyp *mod);
extern int ismatch(ptpe *p, modtyp *mod, unsigned int cl, unsigned int tag);
extern int hasdata(PEPYPARM parm, ptpe *p, modtyp *mod, int *popt, int *optcnt);

#define NEXT_TPE(p) (p = next_tpe(p))
#define CHKTAG(mod, p, pe)	ismatch(p, mod, pe->pe_class, pe->pe_id)

static char oomsg[] = "Out of memory";
#define oom(a,b)	pepsylose ((a), (b), NULL, oomsg);

#define RET_OK(rpe, pe)	*(rpe) = (pe), (OK)

#define pname(t)	((t)->pe_typename ? *(t)->pe_typename : "???")

static int en_obj(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_type(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_seq(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_set(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_setof(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_seqof(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_choice(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);
static int en_etype(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe);

extern int set_addon (PE pe, PE last, PE newPE);

/*
 * encode the specified type of the specified module into the given
 * pe
 */
int
enc_f(int typ, modtyp *mod, PE *pe, int explicitly, int len, char *buf, char *parm)
{
     ptpe *p;

    if (typ < 0 || typ >= mod->md_nentries) {
	(void) pepsylose (mod, NULL, NULL, "enc_f:Illegal typ %d", typ);
	return NOTOK;
    }

    p = mod->md_etab[typ];
    if (p->pe_type != PE_START) {
	return (pepsylose (mod, NULL, NULL, "enc_f: missing PE_START"));
    }
    p++;

    if (en_obj(parm, p, mod, pe) == NOTOK) {
	    return NOTOK;
    }
    return OK;
}

/*
 * Encode an object. If the object is a simple type it may have a
 * compressed type reference. If it is a compound type it will not
 * have an offset. This is very important as it means we cannot just
 * use en_type to handle this which must always assume the field can
 * have an offset.
 */
static int
en_obj(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    PE      pe = NULL;	/* for pepsylose calls */
    int     cnt = 0;

    *rpe = NULL;	/* default case */

    while (p->pe_type != PE_END) {

	switch (p->pe_type) {
	case PE_END:
	case PE_START:
	    return (pepsylose (mod, p, pe, "en_obj:END/START type"));

	/*
	 * This allows Functions to be called at the very end of the 
	 * encoding -- With the encoded data - very messy
	 */
	case UCODE:
	    if (mod->md_eucode == NULL
	    || (*mod->md_eucode) (parm, &pe, p) == NOTOK)
		goto bad;
	    break;

	default:
	    if (en_type(parm, p, mod, &pe) == NOTOK)
		goto bad;
	    break;
	}
	if (ISDTYPE(p) && cnt++ > 0)
	    return pepsylose (mod, p, NULL, "en_obj:compound type found");

	if (ISDTYPE(p)) {
	    if (pe == NULL)
		return pepsylose (mod, p, NULL,
				  "en_obj: missing mandatory value");
	}
	/* make sure any final UCODEs get run
	if (ISDTYPE(p) && pe != NULL)
	    return (RET_OK(rpe, pe));
	 */

	if (NEXT_TPE(p) == NULL)
	    goto bad;
    }

    return (RET_OK(rpe, pe));

bad:
    return (NOTOK);
}

/*
 * Encode a single type. If a basic type encode it, if a compound
 * type call the appropriate encoding routine
 */
static int
en_type(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    PE      pe = NULL;
    int     cnt = 0;
    int     i;			/* Integer for encoding type */
    ptpe    *tmp;
    char   *cp;

    *rpe = NULL;
    while (p->pe_type != PE_END) {

	switch (p->pe_type) {
	case PE_END:
	case PE_START:
	    return (pepsylose (mod, p, pe, "en_type:END/START type"));

	case DFLT_F:
	    tmp = p;
	    p = FDFLT_F(p);
	    if ((i = same(p, tmp, parm, mod)) == NOTOK)
		return (NOTOK); /* Error */
	    if (i)
		return (RET_OK(rpe, NULL));/* don't encode it */
	    p = tmp + 1;
	    continue;

	case BOPTIONAL:
	    if (IF_USELECT(p)) {
		if (mod -> md_eucode == NULL)
		    goto bad;
		if ((*mod->md_eucode) (parm, &pe, p) == 0)
		    return (RET_OK(rpe,NULL)); /* don't encode it */
	    } else if (!OPT_PRESENT(p, parm))
		return (RET_OK(rpe, NULL));/* don't encode it */
	    p++; /* encode it */
	    continue;

	case UCODE:
	    if (mod->md_eucode == NULL
	    || (*mod->md_eucode) (parm, &pe, p) == NOTOK)
		goto bad;
	    break;

	case ETAG:
	    if ((pe = pe_alloc(CLASS(p), PE_FORM_CONS, TAG(p))) == NULL)
		return oom (mod, p);

	    switch (p->pe_ucode) {

	    default:
		p++;
		if (en_etype(parm, p, mod, &pe->pe_cons) == NOTOK)
		    goto bad;
	    }
	    break;

	case SEQ_START:
	    if (en_seq(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEQOF_START:
	    if (en_seqof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SET_START:
	    if (en_set(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SETOF_START:
	    if (en_setof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SSEQ_START:
	    if (en_seq(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SSEQOF_START:
	    if (en_seqof(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SSET_START:
	    if (en_set(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SSETOF_START:
	    if (en_setof(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case IMP_OBJ:
	    tmp = p++;
	    if (p->pe_type == EXTOBJ) {
		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		      0, (char *)0, *(char **) (parm + p->pe_ucode)) == NOTOK)
		      return (NOTOK);
	    } else if (p->pe_type == SEXTOBJ) {
		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		      0, (char *)0, (parm + p->pe_ucode)) == NOTOK)
		      return (NOTOK);
	    } else if (p->pe_type == SOBJECT) {
		if (en_obj((char *) (parm + p->pe_ucode), mod->md_etab[p->pe_tag] + 1, mod, &pe)
		  == NOTOK)
		     goto bad;;
	    } else
		if (en_obj(*(char **) (parm + p->pe_ucode),
			mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		    goto bad;

	    pe->pe_class = CLASS(tmp);
	    pe->pe_id = TAG(tmp);
	    break;

	case SOBJECT:
	    if (en_obj((char *) (parm + p->pe_ucode), mod->md_etab[p->pe_tag] + 1, mod, &pe)
	      == NOTOK)
		goto bad;
	    break;

	case OBJECT:
	    if (en_obj(*(char **) (parm + p->pe_ucode),
	      mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case CHOICE_START:
	    if (en_choice(*(char **) (parm + p->pe_ucode), p, mod, &pe) ==NOTOK)
		goto bad;
	    break;

	case SCHOICE_START:
	    if (en_choice(parm + p->pe_ucode, p, mod, &pe) ==NOTOK)
		goto bad;
	    break;

	case SEXTOBJ:
	    if (p[1].pe_type != EXTMOD)
		return pepsylose (mod, &p[1], NULL,
				  "en_seq: missing EXTMOD");
	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		  (char *) (parm + p->pe_ucode)) == NOTOK)
		  return (NOTOK);
	    break;

	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD)
		return pepsylose (mod, &p[1], NULL,
				  "en_seq: missing EXTMOD");
	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		  *(char **) (parm + p->pe_ucode)) == NOTOK)
		  return (NOTOK);
	    break;

	case INTEGER:
	    if ((pe = num2prim(*(integer *) (parm + p->pe_ucode),
			       CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

#ifdef	PEPSY_REALS
	case REALTYPE:
	    if ((pe = real2prim(*(double *) (parm + p->pe_ucode),
			       CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

#endif
	case BOOLEAN:
	    if ((pe = flag2prim(*(char *) (parm + p->pe_ucode),
				CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

	case ASN_NULL:
	    if ((pe = pe_alloc(CLASS(p), PE_FORM_PRIM,
			       TAG(p))) == NULL)
		return oom(mod,p);

	    break;

	case SANY:
	    (pe = (PE) (parm + p->pe_ucode))->pe_refcnt++;
	    break;

	case ANY:
	    if ((parm + p->pe_ucode) == 0 || *(PE *) (parm + p->pe_ucode) == 0)
#if ROSAP_HACK
		/* hack for ROSAP. expects this strangeness */
		pe = pe_alloc(PE_CLASS_UNIV, PE_FORM_PRIM, PE_PRIM_NULL);
#else
		pe = NULL;
#endif
	    else
		(pe = *(PE *) (parm + p->pe_ucode))->pe_refcnt++;
	    break;

	case SOCTETSTRING:
	    if ((pe = (struct PElement*)qb2prim((struct qbuf *) (parm + p->pe_ucode), CLASS(p), TAG(p)))
		== NULL)
		return oom(mod, p)
	    break;

	case OCTETSTRING:
	    if ((pe = (struct PElement*)qb2prim(*(struct qbuf **) (parm + p->pe_ucode),
			      CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

	case T_STRING:
	    if (*(char **) (parm + p->pe_ucode) == NULL)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:T_STRING missing pointer");
	    if ((pe = str2prim(*(char **) (parm + p->pe_ucode),
                           (int)strlen(*(char **) (parm + p->pe_ucode)),
          		  	       CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

	case OCTET_PTR:
	    if (p[1].pe_type != OCTET_LEN)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:missing OCTET_LEN");

	    if (*(char **) (parm + p->pe_ucode) == NULL)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:OCTET_PTR  missing pointer");

	    if (*(int *) (parm + (p + 1)->pe_ucode) < 0)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:OCTET_LEN negative length");

	    if ((pe = str2prim(*(char **) (parm + p->pe_ucode),
			      *(int *) (parm + (p + 1)->pe_ucode),
			      CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

	case BITSTR_PTR:
	    if (p[1].pe_type != BITSTR_LEN)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:missing BITSTR_LEN");

	    if (*(char **) (parm + p->pe_ucode) == NULL)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:BITSTR_PTR  missing pointer");

	    if (*(int *) (parm + (p + 1)->pe_ucode) < 0)
		return pepsylose (mod, &p[1], NULL,
				  "en_type:BITSTR_LEN negative length");

	    if ((pe = strb2bitstr(*(char **) (parm + p->pe_ucode),
			      *(int *) (parm + (p + 1)->pe_ucode),
			      CLASS(p), TAG(p))) == NULL
		|| (pe = bit2prim(pe)) == NULL)
		return oom(mod, p);
	    break;

	case SBITSTRING:
	    if ((cp = bitstr2strb((PE) (parm + p->pe_ucode), &i)) == NULL)
		return oom(mod, p);
	    if ((pe = strb2bitstr(cp, i, CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    free(cp);
	    if ((pe = bit2prim(pe)) == NULL)
		return oom(mod, p);
	    break;

	case BITSTRING:
	    if ((cp = bitstr2strb(*(PE *) (parm + p->pe_ucode), &i))
		== NULL)
		return oom(mod, p);

	    if ((pe = strb2bitstr(cp, i, CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);

	    free(cp);
	    if ((pe = bit2prim(pe)) == NULL)
		return oom(mod, p);
	    break;

	case SOBJID:
	    if ((pe = obj2prim((OID) (parm + p->pe_ucode), CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

	case OBJID:
	    if ((pe = obj2prim(*(OID *) (parm + p->pe_ucode), CLASS(p), TAG(p)))
		== NULL)
		return oom(mod, p);
	    break;

	default:
	    return pepsylose (mod, p, NULL, "en_type: type not implemented");
	}
	if (ISDTYPE(p) && cnt++ > 0)
	    return pepsylose (mod, p, NULL, "en_type:compound type found");

	if (ISDTYPE(p)) {
	    if (pe == NULL)
		return pepsylose (mod, p, NULL,
				  "en_type: missing mandatory value");
	}
	if (ISDTYPE(p) && pe != NULL)
	    return (RET_OK(rpe, pe));
	if (NEXT_TPE(p) == NULL)
	    goto bad;
    }

    return (RET_OK(rpe, pe));

bad:
    return (NOTOK);
}

/*
 * Build a sequence, calling appropriate routines to build each sub
 * type
 */
static int
en_seq(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    PE      head;
    PE      pe = NULL;
    ptpe    *tmp;		/* first entry in list */
    int    *popt = NULL;	/* Pointer to optional field */
    int     optcnt = 0;		/* Number of optionals bits so far */
    int	    val;

    if (p->pe_type != SEQ_START && p->pe_type != SSEQ_START)
	    return (pepsylose (mod, p, pe, "en_seq: missing SEQ_START\n"));

    if ((head = pe_alloc(CLASS(p), PE_FORM_CONS, TAG(p))) == NULL)
	return oom (mod, p);
    p++;

    while (p->pe_type != PE_END) {

	if (ISDTYPE(p) && POPTIONAL(p)) {
	    switch (p->pe_type) {
	    case INTEGER:
	    case REALTYPE:
	    case BOOLEAN:
	    case ASN_NULL:
		if (!TESTBIT(*popt, optcnt++))
		    goto next;	/* Missing so skip */
		break;

	    case ETAG:
		if ((val = hasdata(parm, p + 1, mod, popt, &optcnt)) == NOTOK)
		    goto bad;
		if (val == 0)
		    goto next;
		break;

	    case IMP_OBJ:
		if ((p[1].pe_type == SOBJECT && parm == NULL)
		    || *((char **) (parm + p[1].pe_ucode)) == NULL)
		    goto next;
		break;

	    case SOBJECT:
		if (((char *) parm) == NULL)
		    goto next;
		break;

	    default:
		if (*((char **) (parm + p->pe_ucode)) == NULL)
		    goto next;
		break;
	    }
	}
	switch (p->pe_type) {
	case OPTL:
	    popt = (int *) (parm + p->pe_ucode);
	    break;

	case UCODE:
	    if (mod->md_eucode == NULL
	    || (*mod->md_eucode) (parm, &pe, p) == NOTOK)
		goto bad;
	    break;

	case ETAG:
	    if (en_type(parm, p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEQ_START:
	    if (en_seq(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEQOF_START:
	    if (en_seqof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SET_START:
	    if (en_set(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SETOF_START:
	    if (en_setof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case IMP_OBJ:
	    tmp = p++;
	    if (p->pe_type == EXTOBJ || p->pe_type == SEXTOBJ) {
		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		      0, (char *)0, *(char **) (parm + p->pe_ucode)) == NOTOK)
		      return (NOTOK);
	    } else if (p->pe_type == SOBJECT) {
		if (en_obj((char *) (parm + p->pe_ucode), mod->md_etab[p->pe_tag] + 1, mod,
		      &pe) == NOTOK)
		    goto bad;
	    } else
		if (en_obj(*(char **) (parm + p->pe_ucode),
			mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		    goto bad;
	    pe->pe_class = CLASS(tmp);
	    pe->pe_id = TAG(tmp);
	    break;

	case SOBJECT:
	    if (en_obj((char *) (parm + p->pe_ucode), mod->md_etab[p->pe_tag] + 1, mod, &pe)
		    == NOTOK)
		goto bad;
	    break;

	case OBJECT:
	    if (en_obj(*(char **) (parm + p->pe_ucode),
		    mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case CHOICE_START:
	    if (en_choice(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SCHOICE_START:
	    if (en_choice((char *) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEXTOBJ:
	    if (p[1].pe_type != EXTMOD)
		return pepsylose (mod, &p[1], NULL, "en_seq: missing EXTMOD");
	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		  (char *) (parm + p->pe_ucode)) == NOTOK)
		  return (NOTOK);
	    break;

	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD)
		return pepsylose (mod, &p[1], NULL, "en_seq: missing EXTMOD");

	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		  *(char **) (parm + p->pe_ucode)) == NOTOK)
		  return (NOTOK);
	    break;

	default:
	    if (en_type(parm, p, mod, &pe) == NOTOK)
		goto bad;
	    break;
	}

	if ((ISDTYPE(p) || p->pe_type == BOPTIONAL) && pe != NULL) {
	    if (seq_add(head, pe, -1) == NOTOK)
		return pepsylose (mod, p, NULL, "en_seq bad sequence: %s",
		       pe_error(pe->pe_errno));
	}
next:
	if (NEXT_TPE(p) == NULL)
	    return (NOTOK);
    }

    return (RET_OK(rpe, head));

bad:
    return (NOTOK);
}


/*
 * Parse a set, calling appropriate routines to parse each sub type
 */
static int
en_set(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    PE      head;
    PE      pe = NULL;
    ptpe    *tmp;
    int    *popt = NULL;	/* Pointer to optional field */
    int     optcnt = 0;		/* Number of optionals bits so far */
    int	    val;

    if (p->pe_type != SET_START && p->pe_type != SSET_START)
	return pepsylose (mod, p, pe, "en_set: missing SET_START");

    if ((head = pe_alloc(CLASS(p), PE_FORM_CONS, TAG(p))) == NULL)
	return oom(mod, p);

    p++;
    while (p->pe_type != PE_END) {

	if (ISDTYPE(p) && POPTIONAL(p)) {
	    switch (p->pe_type) {
	    case INTEGER:
	    case REALTYPE:
	    case BOOLEAN:
	    case ASN_NULL:
		if (!TESTBIT(*popt, optcnt++))
		    goto next;	/* Missing so skip */
		break;

	    case ETAG:
		if ((val = hasdata(parm, p + 1, mod, popt, &optcnt)) == NOTOK)
		    goto bad;
		if (val == 0)
		    goto next;
		break;

	    case IMP_OBJ:
		if ((p[1].pe_type == SOBJECT && parm == NULL)
		    || *((char **) (parm + p[1].pe_ucode)) == NULL)
		    goto next;
		break;

	    case SOBJECT:
		if (((char *) (parm + p->pe_ucode)) == NULL)
		    goto next;
		break;

	    default:
		if (*((char **) (parm + p->pe_ucode)) == NULL)
		    goto next;
		break;
	    }
	}
	switch (p->pe_type) {
	case OPTL:
	    popt = (int *) (parm + p->pe_ucode);
	    break;

	case UCODE:
	    if (mod->md_eucode == NULL
	    || (*mod->md_eucode) (parm, &pe, p) == NOTOK)
		goto bad;
	    break;

	case ETAG:
	    if (en_type(parm, p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEQ_START:
	    if (en_seq(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEQOF_START:
	    if (en_seqof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SET_START:
	    if (en_set(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SETOF_START:
	    if (en_setof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case IMP_OBJ:
	    tmp = p++;
	    if (p->pe_type == EXTOBJ || p->pe_type == SEXTOBJ) {
		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		      0, (char *)0, *(char **) (parm + p->pe_ucode)) == NOTOK)
		      return (NOTOK);
	    } else if (p->pe_type == SOBJECT) {
		if (en_obj((char *) parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1, mod,
			&pe) == NOTOK)
		    goto bad;
	    } else
		if (en_obj(*(char **) (parm + p->pe_ucode),
			mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		    goto bad;
	    pe->pe_class = CLASS(tmp);
	    pe->pe_id = TAG(tmp);
	    break;

	case SOBJECT:
	    if (en_obj(parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case OBJECT:
	    if (en_obj(*(char **) (parm + p->pe_ucode),
		    mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case CHOICE_START:
	    if (en_choice(*(char **) (parm + p->pe_ucode), p, mod, &pe) ==NOTOK)
		goto bad;
	    break;


	case SCHOICE_START:
	    if (en_choice((char *) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		goto bad;
	    break;

	case SEXTOBJ:
	    if (p[1].pe_type != EXTMOD)
		return pepsylose (mod, p, NULL, "en_set: missing EXTMOD");

	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		  parm + p->pe_ucode) == NOTOK)
		  return (NOTOK);
	    break;

	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD) 
		return pepsylose (mod, p, NULL, "en_set: missing EXTMOD");

	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		  *(char **) (parm + p->pe_ucode)) == NOTOK)
		  return (NOTOK);
	    break;

	default:
	    if (en_type(parm, p, mod, &pe) == NOTOK)
		goto bad;
	    break;
	}

	if ((ISDTYPE(p) || p->pe_type == BOPTIONAL) && pe != NULL) {
	    if (set_add(head, pe) == NOTOK)
		return pepsylose (mod, p, NULL, "en_set bad set: %s",
				  pe_error(pe->pe_errno));
	}
next:
	NEXT_TPE(p);
    }

    return (RET_OK(rpe, head));

bad:
    return (NOTOK);
}


/*
 * Parse a sequence of calling appropriate routines to parse each sub
 * type
 */
static int
en_seqof(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    PE      head;
    PE      pe = NULL;
    ptpe    *start;		/* first entry in list */
    ptpe    *tmp;

    if (p->pe_type != SEQOF_START && p->pe_type != SSEQOF_START)
	return pepsylose (mod, p, NULL, "en_seqof: missing SEQOF_START");

    if ((head = pe_alloc(CLASS(p), PE_FORM_CONS, TAG(p))) == NULL)
	return oom(mod, p);

    start = p;
    while ((char *) parm != NULL) {
	p++;
	while (p->pe_type != PE_END) {

	    switch (p->pe_type) {
	    case UCODE:
		if (mod->md_eucode == NULL
		|| (*mod->md_eucode) (parm, &pe, p) == NOTOK)
		    goto bad;
		break;

	    case ETAG:
		if (en_type(parm, p, mod, &pe) == NOTOK)
		    goto bad;
		break;

	    case SEQ_START:
		if (en_seq(*(char **) (parm + p->pe_ucode), p, mod, &pe)==NOTOK)
		    goto bad;
		break;

	    case SEQOF_START:
		if (en_seqof(*(char **) (parm + p->pe_ucode), p, mod, &pe)
			== NOTOK)
		    goto bad;
		break;

	    case SET_START:
		if (en_set(*(char **) (parm + p->pe_ucode), p, mod, &pe)==NOTOK)
		    goto bad;
		break;

	    case SETOF_START:
		if (en_setof(*(char **) (parm + p->pe_ucode), p, mod, &pe)
			== NOTOK)
		    goto bad;
		break;

	    case IMP_OBJ:
		tmp = p++;
		if (p->pe_type == EXTOBJ || p->pe_type == SEXTOBJ) {
		    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		       0, (char *)0, *(char **) (parm + p->pe_ucode)) == NOTOK)
		       return (NOTOK);
		} else if (p->pe_type == SOBJECT) {
		    if (en_obj((char *) (parm + p->pe_ucode), mod->md_etab[p->pe_tag] + 1,
			    mod, &pe) == NOTOK)
			goto bad;
		} else if (en_obj(*(char **) (parm + p->pe_ucode),
			    mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
			goto bad;
		pe->pe_class = CLASS(tmp);
		pe->pe_id = TAG(tmp);
		break;

	    case SOBJECT:
		if (en_obj(parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1, mod, &pe) ==NOTOK)
		    goto bad;
		break;

	    case OBJECT:
		if (en_obj(*(char **) (parm + p->pe_ucode),
			mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		    goto bad;
		break;

	    case CHOICE_START:
		if (en_choice(*(char **) (parm + p->pe_ucode), p, mod, &pe)
			== NOTOK)
		    goto bad;
		break;


	    case SCHOICE_START:
		if (en_choice((char *) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		    goto bad;
		break;

	    case SEXTOBJ:
		if (p[1].pe_type != EXTMOD)
		    return pepsylose (mod, p+1, NULL,
				      "en_seqof: missing EXTMOD");
		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		      parm + p->pe_ucode) == NOTOK)
		      return (NOTOK);
		break;

	    case EXTOBJ:
		if (p[1].pe_type != EXTMOD) 
		    return pepsylose (mod, p+1, NULL,
				      "en_seqof: missing EXTMOD");

		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		      *(char **) (parm + p->pe_ucode)) == NOTOK)
		      return (NOTOK);
		break;

	    default:
		if (en_type(parm, p, mod, &pe) == NOTOK)
		    goto bad;
		break;
	    }
	    if (ISDTYPE(p) && pe != NULL) {
		if (seq_add(head, pe, -1) == NOTOK)
		    return pepsylose (mod, p, NULL,
				      "en_seqof bad sequence: %s",
				      pe_error(pe->pe_errno));
	    }
	    if (NEXT_TPE(p) == NULL)
		goto bad;
	}
	parm = *(char **) (parm + p->pe_ucode);	/* Any more ? */
	p = start;
    }

    return (RET_OK(rpe, head));

bad:
    return (NOTOK);
}

/*
 * Parse a setof, calling appropriate routines to parse each sub type
 */
static int
en_setof(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    PE      head;
    PE      pe = NULL, last = NULL;
    ptpe    *start;
    ptpe    *tmp;

    if (p->pe_type != SETOF_START && p->pe_type != SSETOF_START)
	return pepsylose (mod, p, NULL, "en_setof: missing SETOF_START");

    if ((head = pe_alloc(CLASS(p), PE_FORM_CONS, TAG(p))) == NULL)
	return oom(mod,p);

    start = p;
    while ((char *) parm != NULL) {
	p++;
	while (p->pe_type != PE_END) {
	    switch (p->pe_type) {
	    case UCODE:
		if (mod->md_eucode == NULL
		|| (*mod->md_eucode) (parm, &pe, p) == NOTOK)
		    goto bad;
		break;

	    case ETAG:
		if (en_type(parm, p, mod, &pe) == NOTOK)
		    goto bad;
		break;

	    case SEQ_START:
		if (en_seq(*(char **) (parm + p->pe_ucode), p, mod, &pe)==NOTOK)
		    goto bad;
		break;

	    case SEQOF_START:
		if (en_seqof(*(char **) (parm + p->pe_ucode), p, mod, &pe)
			== NOTOK)
		    goto bad;
		break;

	    case SET_START:
		if (en_set(*(char **) (parm + p->pe_ucode), p, mod, &pe)==NOTOK)
		    goto bad;
		break;

	    case SETOF_START:
		if (en_setof(*(char **) (parm + p->pe_ucode), p, mod, &pe)
			== NOTOK)
		    goto bad;
		break;

	    case IMP_OBJ:
		tmp = p++;
		if (p->pe_type == EXTOBJ || p->pe_type == SEXTOBJ) {
		    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		       0, (char *)0, *(char **) (parm + p->pe_ucode)) == NOTOK)
		       return (NOTOK);
		} else if (p->pe_type == SOBJECT) {
		    if (en_obj((char *) parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1,
			    mod, &pe) == NOTOK)
			goto bad;
		} else
		    if (en_obj(*(char **) (parm + p->pe_ucode),
			    mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
			goto bad;
		pe->pe_class = CLASS(tmp);
		pe->pe_id = TAG(tmp);
		break;

	    case SOBJECT:
		if (en_obj(parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1, mod, &pe) ==NOTOK)
		    goto bad;
		break;

	    case OBJECT:
		if (en_obj(*(char **) (parm + p->pe_ucode),
			mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		    goto bad;
		break;

	    case CHOICE_START:
		if (en_choice(*(char **) (parm + p->pe_ucode), p, mod, &pe)
			== NOTOK)
		    goto bad;
		break;


	    case SCHOICE_START:
		if (en_choice((char *) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
		    goto bad;
		break;

	    case SEXTOBJ:
		if (p[1].pe_type != EXTMOD)
		    return pepsylose (mod, p + 1, NULL,
				      "en_setof: missing EXTMOD");
		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		      parm + p->pe_ucode) == NOTOK)
		      return (NOTOK);
		break;

	    case EXTOBJ:
		if (p[1].pe_type != EXTMOD)
		    return pepsylose (mod, p + 1, NULL,
				      "en_setof: missing EXTMOD");

		if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
		      *(char **) (parm + p->pe_ucode)) == NOTOK)
		      return (NOTOK);
		break;

	    default:
		if (en_type(parm, p, mod, &pe) == NOTOK)
		    goto bad;
		break;
	    }

	    if (ISDTYPE(p) && pe != NULL) {
		if (set_addon(head, last, pe) == NOTOK)
		    return pepsylose (mod, p, NULL, "en_setof bad set: %s",
				      pe_error(pe->pe_errno));
		else
		    last = pe;
	    }

	    if (NEXT_TPE(p) == NULL)
		goto bad;;
	}
	parm = *(char **) (parm + p->pe_ucode);	/* Any more ? */
	p = start;
    }

    return (RET_OK(rpe, head));


bad:
    return (NOTOK);
}

/*
 * encode a choice field. This means find which choice is taken and
 * call en_type to encode it
 */
static int
en_choice(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    int     cnt;
    ptpe *p2;
    
    if (p->pe_type != CHOICE_START && p->pe_type != SCHOICE_START)
	return pepsylose (mod, p, NULL, "en_choice:missing CHOICE_START");

    p2 = p++;

    if (p->pe_type != SCTRL)
	return pepsylose (mod, p, NULL, "en_choice:missing SCTRL");

    if (IF_USELECT(p)) {
	if (mod->md_eucode == NULL ||
	    (cnt = (*mod -> md_eucode) (parm, (PE *)&rpe, p)) == NOTOK)
	    return pepsylose (mod, p, NULL, "choice selection failed");
    }
    else
	cnt = *(int *) (parm + p->pe_ucode);

    if (cnt != 0)
	cnt--;
    if (cnt < 0)
	return pepsylose (mod, p, NULL, "en_choice:offset %d negative", cnt);

    for (p++; p->pe_type != PE_END; NEXT_TPE(p)) {
	if (cnt == 0 && p->pe_type == UCODE) {
		if (mod->md_eucode == NULL
		|| (*mod->md_eucode) (parm, (PE*)&rpe, p) == NOTOK)
		    return (NOTOK);
	}
	if (ISDTYPE(p)) {
	    if (cnt == 0) {
		if (en_etype(parm, p, mod, rpe) == NOTOK)
		    return (NOTOK);
		return (OK);
	    }
	    cnt--;
	}
    }

    return pepsylose (mod, p, NULL, "en_choice: no choice taken");
}


/*
 * check to see if the object is present or not
 */
static int
chkobj(modtyp *mod, ptpe *p, PE head)
{

    for (; p->pe_type != PE_END; NEXT_TPE(p)) {
	if (!ISDTYPE(p))
	    continue;

	if (p->pe_type == OBJECT) {
	    if (chkobj(mod, p, head))
		return (1);
	} else if (CHKTAG(mod, p, head))
	    return (1);

	if (POPTIONAL(p) || DEFAULT(p))
	    continue;

	return (0);
    }
    return (0);
}

/*
 * Encode a single type for an explicit tag field If a basic type
 * encode it, if a compound type call the appropriate encoding
 * routine. Similar to en_type except we do the indirection on the
 * ucode field
 */
static int
en_etype(PEPYPARM parm, ptpe *p, modtyp *mod, PE *rpe)
{
    ptpe    *tmp;
    PE      pe = NULL;

    switch (p->pe_type) {
    case PE_END:
    case PE_START:
	return (pepsylose (mod, p, pe, "en_etype:END/START type"));

    case UCODE:
	if (mod->md_eucode == NULL
	|| (*mod->md_eucode) (parm, &pe, p) == NOTOK)
	    goto bad;
	break;

    case ETAG:
	if ((pe = pe_alloc(CLASS(p), PE_FORM_CONS, TAG(p))) == NULL)
	    return oom(mod, p);
	switch (p->pe_ucode) {
	default:
	    p++;
	    if (en_etype(parm, p, mod, &pe->pe_cons) == NOTOK)
		goto bad;
	}
	break;

    case SEQ_START:
	if (en_seq(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SEQOF_START:
	if (en_seqof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SET_START:
	if (en_set(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SETOF_START:
	if (en_setof(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SSEQ_START:
	if (en_seq(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SSEQOF_START:
	if (en_seqof(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SSET_START:
	if (en_set(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SSETOF_START:
	if (en_setof(parm + p->pe_ucode, p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case IMP_OBJ:
	tmp = p++;
	if (p->pe_type == EXTOBJ || p->pe_type == SEXTOBJ) {
	    if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1,
		  0, (char *)0, *(char **) (parm + p->pe_ucode)) == NOTOK)
		  return (NOTOK);
	} else if (p->pe_type == SOBJECT) {
	    if (en_obj((char *) parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1, mod, &pe)
		    == NOTOK)
		goto bad;
	} else
	    if (en_obj(*(char **) (parm + p->pe_ucode),
		    mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
		goto bad;
	pe->pe_class = CLASS(tmp);
	pe->pe_id = TAG(tmp);
	break;

    case SOBJECT:
	if (en_obj(parm + p->pe_ucode, mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case OBJECT:
	if (en_obj(*(char **) (parm + p->pe_ucode),
		mod->md_etab[p->pe_tag] + 1, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case CHOICE_START:
	if (en_choice(*(char **) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
	    goto bad;
	break;

    case SCHOICE_START:
        if (en_choice((char *) (parm + p->pe_ucode), p, mod, &pe) == NOTOK)
          goto bad;
      break;

    case INTEGER:
	if ((pe = num2prim(*(integer *) (parm + p->pe_ucode), CLASS(p), TAG(p))) == NULL)
	    return oom (mod, p);

	break;

#ifdef	PEPSY_REALS
    case REALTYPE:
	    if ((pe = real2prim(*(double *) (parm + p->pe_ucode),
			       CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    break;

#endif
    case BOOLEAN:
	if ((pe = flag2prim(*(char *) (parm + p->pe_ucode), CLASS(p), TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case ASN_NULL:
	if ((pe = pe_alloc(CLASS(p), PE_FORM_PRIM, TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case SANY:
	(pe = (PE) (parm + p->pe_ucode))->pe_refcnt++;
	break;

    case ANY:
	if ((parm + p->pe_ucode) == 0 || *(PE *) (parm + p->pe_ucode) == 0)
#if ROSAP_HACK
	    /* hack for ROSAP. expects this strangeness */
	    pe = pe_alloc(PE_CLASS_UNIV, PE_FORM_PRIM, PE_PRIM_NULL);
#else
	    pe = NULL;
#endif
	else
	    (pe = *(PE *) (parm + p->pe_ucode))->pe_refcnt++;
	break;

    case SEXTOBJ:
	if (p[1].pe_type != EXTMOD)
	    return pepsylose (mod, p+1, NULL, "en_etype: missing EXTMOD");
	if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
	    parm + p->pe_ucode) == NOTOK)
	    return (NOTOK);
	break;

    case EXTOBJ:
	if (p[1].pe_type != EXTMOD)
	    return pepsylose (mod, p+1, NULL, "en_etype: missing EXTMOD");
	if (enc_f(p->pe_tag, EXT2MOD(mod, (p + 1)), &pe, 1, 0, (char *)0,
	      *(char **) (parm + p->pe_ucode)) == NOTOK)
	      return (NOTOK);
	break;

    case SOCTETSTRING:
	if ((pe = (struct PElement*)qb2prim((struct qbuf *) (parm + p->pe_ucode), CLASS(p), TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case SBITSTRING:
	{
	    char   *cp;
	    int     i;

	    if ((cp = bitstr2strb((PE) (parm + p->pe_ucode), &i)) == NULL)
		return oom(mod, p);
	    if ((pe = strb2bitstr(cp, i, CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    free(cp);
	    if ((pe = bit2prim (pe)) == NULL)
		return oom(mod, p);
	}
	break;

    case OCTETSTRING:
	if ((pe = (struct PElement*)qb2prim(*(struct qbuf **) (parm + p->pe_ucode), CLASS(p), TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case T_STRING:
	if (*(char **) (parm + p->pe_ucode) == NULL)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype:T_STRING missing pointer");

	if ((pe = str2prim(*(char **) (parm + p->pe_ucode),
	        		   (int)strlen(*(char **) (parm + p->pe_ucode)),
                       CLASS(p), TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case OCTET_PTR:
	if (p[1].pe_type != OCTET_LEN)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype: missing OCTET_LEN");

	if (*(char **) (parm + p->pe_ucode) == NULL)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype:OCTET_PTR missing pointer");

	if (*(int *) (parm + (p + 1)->pe_ucode) < 0)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype:OCTET_LEN negative length");

	if ((pe = str2prim(*(char **) (parm + p->pe_ucode),
			  *(int *) (parm + (p + 1)->pe_ucode),
			  CLASS(p), TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case BITSTR_PTR:
	if (p[1].pe_type != BITSTR_LEN)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype:missing BITSTR_LEN");

	if (*(char **) (parm + p->pe_ucode) == NULL)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype:BITSTR_PTR  missing pointer");

	if (*(int *) (parm + (p + 1)->pe_ucode) < 0)
	    return pepsylose (mod, &p[1], NULL,
			      "en_etype:BITSTR_LEN negative length");

	if ((pe = strb2bitstr(*(char **) (parm + p->pe_ucode),
			  *(int *) (parm + (p + 1)->pe_ucode),
			  CLASS(p), TAG(p))) == NULL
	    || (pe = bit2prim(pe)) == NULL)
	    return oom(mod, p);
	break;

    case BITSTRING:
	{
	    char   *cp;
	    int     i;

	    if ((cp = bitstr2strb(*(PE *) (parm + p->pe_ucode), &i)) == NULL)
		return oom(mod, p);
	    if ((pe = strb2bitstr(cp, i, CLASS(p), TAG(p))) == NULL)
		return oom(mod, p);
	    free(cp);
	    if ((pe = bit2prim(pe)) == NULL)
		return oom(mod, p);
	}
	break;

    case SOBJID:
	if ((pe = obj2prim((OID) (parm + p->pe_ucode), CLASS(p), TAG(p))) == NULL)
	    return oom(mod, p);
	break;

    case OBJID:
	if ((pe = obj2prim(*(OID *) (parm + p->pe_ucode), CLASS(p), TAG(p)))
	    == NULL)
	    return oom(mod, p);
	break;

    default:
	return pepsylose (mod, p, NULL, "en_etype: type not implemented");
    }
    return (RET_OK(rpe, pe));

bad:
    return (NOTOK);
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

