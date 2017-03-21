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
 * LOG: Revision 1.1  2007/03/30 04:49:48  cvsadmin
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
 * LOG: Revision 3.1  2000/08/16 00:04:20  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:36  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:24  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/07/22 00:34:36  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.6  1999/07/02 13:43:35  mmiers
 * LOG:
 * LOG:
 * LOG: Correct linkage of function
 * LOG:
 * LOG: Revision 1.5  1999/03/02 18:14:52  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the header file ordering (I did it again).
 * LOG:
 * LOG: Revision 1.4  1999/02/26 04:09:51  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:47:57  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:27  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:16  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.6  1998/10/23 16:05:34  mmiers
 * LOG: AsnC is now threadsafe, except for ODE.
 * LOG:
 * LOG: Revision 1.5  1998/10/22 00:47:40  whu
 * LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 17:48:19  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 *
 *****************************************************************************/

/* LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 */
#include "pepsy-driver.h"
#include <asn-c/AsnC.h>

#ident "$Id: fre.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $"

extern int pepsylose(modtyp *a, ptpe *b, PE pe, ...);
extern ptpe *next_tpe(ptpe *);
extern void ferrd();
extern void ferr(int n, char *mesg);

#define NEXT_TPE(p)	p = next_tpe(p)
#define CHKTAG(mod, p, pe)	ismatch(p, mod, pe->pe_class, pe->pe_id)

static int fre_seq(char *parm, ptpe *p, modtyp *mod, int dofree);
static int fre_seqof(char *parm, ptpe *p, modtyp *mod, int dofree);
static int fre_choice(char *parm, ptpe *p, modtyp *mod, int dofree);
static int fre_type(char *parm, ptpe *p, modtyp *mod, int dofree);

/*
 * free an objects data. Basic algorithm is to walk through it twice
 * first time freeing all the "children" of the data structure - then
 * the second time free the structure itself
 */
int
fre_obj(char *parm, ptpe *p, modtyp *mod, int dofree)
{
    char   *malptr = NULL;	/* Have we seen a malloc */
    int	    ndofree = dofree;	/* Does the function below deallocate space */

    if (parm == 0)
	return (OK);

    if (p->pe_type != PE_START) {
	(void) pepsylose (mod, p, NULL, "fre_obj: missing PE_START\n");
	return (NOTOK);
    }

    for (p++; p->pe_type != PE_END; NEXT_TPE(p)) {

	/*
	 * we have to have all these cases here because it is different to the
	 * situation when the entry is not the main entry of the typereference.
	 */
	switch (p->pe_type) {
	case MEMALLOC:
	    if (dofree) {
		malptr = parm;
		ndofree = 0;	/* we are deallocating space on this level */
	    }
	    break;

	default:
	    if (fre_type(parm, p, mod, ndofree) != OK)
		return (NOTOK);
	    break;
	}
    }

    if (malptr && dofree) { /* If we saw a malloc free item */
	free(malptr);
	malptr = NULL;
    }

    return (OK);
}

/*
 * Handle freeing of single type field. All the more general routines
 * fall back to this so we can put the code to free something just
 * here once and it will handle all the cases else where
 */
static int
fre_type(char *parm, ptpe *p, modtyp *mod, int dofree)
{

    if (parm == 0)
	return OK;

again:
    switch (p->pe_type) {
    case MEMALLOC:
	break;

    case PE_END:
    case PE_START:
    case UCODE:
	break;

    case BOPTIONAL:
    case FREE_ONLY:  /* this next entry is for us */
    case DFLT_F:
	p++;
	goto again;

    case ETAG:
	switch (p->pe_ucode) {

	default:
	    p++;
	    if (fre_type(parm, p, mod, dofree) != OK)
		return (NOTOK);
	}
	break;

    case SEQ_START:
    case SET_START:
	if (fre_seq(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
	    return (NOTOK);
	break;

    case SEQOF_START:
    case SETOF_START:
	if (fre_seqof(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
	    return (NOTOK);
	break;

    case SSEQ_START:
    case SSET_START:
	if (fre_seq((char *) parm + p->pe_ucode, p, mod, dofree) != OK)
	    return (NOTOK);
	break;

    case SSEQOF_START:
    case SSETOF_START:
	if (fre_seqof((char *) parm + p->pe_ucode, p, mod, dofree) != OK)
	    return (NOTOK);
	break;

    case IMP_OBJ:
	p++;
	if (p->pe_type == EXTOBJ) {
	    if (fre_obj(*(char **) (parm + p->pe_ucode),
		    (EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
		    EXT2MOD(mod, (p + 1)), 1) != OK)
		return (NOTOK);
	} else if (p->pe_type == SEXTOBJ) {
	    if (fre_obj((parm + p->pe_ucode),
		    (EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
		    EXT2MOD(mod, (p + 1)), dofree) != OK)
		return (NOTOK);
	} else if (p->pe_type == SOBJECT) {
	    if (fre_obj((char *) parm + p->pe_ucode, mod->md_dtab[p->pe_tag], mod, dofree) != OK)
		return (NOTOK);
	} else
	    if (fre_obj(*(char **) (parm + p->pe_ucode),
		    mod->md_dtab[p->pe_tag], mod, 1) != OK)
		return (NOTOK);
	break;

    case SOBJECT:
	if (fre_obj((char *) parm + p->pe_ucode, mod->md_dtab[p->pe_tag], mod, dofree) != OK)
	    return (NOTOK);
	break;

    case OBJECT:
	if (fre_obj(*(char **) (parm + p->pe_ucode), mod->md_dtab[p->pe_tag],
		mod, 1) != OK)
	    return (NOTOK);
	break;

    case SCHOICE_START:
	if (fre_choice((char *) parm + p->pe_ucode, p, mod, dofree) != OK)
	    return (NOTOK);
	break;

    case CHOICE_START:
	if (fre_choice(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
	    return (NOTOK);
	break;

    case SEXTOBJ:
	if (p[1].pe_type != EXTMOD) {
	    (void) pepsylose (mod, p, NULL, "fre_type:missing EXTMOD");
	    return (NOTOK);
	}
	if (fre_obj(parm + p->pe_ucode, (EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
		EXT2MOD(mod, (p + 1)), dofree) != OK)
	    return (NOTOK);
	break;

    case EXTOBJ:
	if (p[1].pe_type != EXTMOD) {
	    (void) pepsylose (mod, p, NULL, "fre_type:missing EXTMOD");
	    return (NOTOK);
	}
	if (fre_obj(*(char **) (parm + p->pe_ucode),
		(EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
		EXT2MOD(mod, (p + 1)), 1) != OK)
	    return (NOTOK);
	break;

    case INTEGER:
    case BOOLEAN:
    case ASN_NULL:
    case REALTYPE:
	break;

    case SANY:
	/*
	 * These tests of the pointer don't appear necessary from the
	 * definition of encoding and decoding but ISODE generates
	 * freeing code that does these checks and ISODE's ps layer
	 * definitely requires it
	 */
	if (parm != NULL) {
	    pe_free((PE) parm);
	    parm = NULL;
	}
	break;

    case ANY:
	if (*(char **) (parm + p->pe_ucode) != NULL) {
	    pe_free(*(PE *) (parm + p->pe_ucode));
	    *((PE *) (parm + p->pe_ucode)) = NULL;
	}
	break;

    case SOCTETSTRING:
	if (parm != NULL) {
	    qb_free((struct qbuf *) parm);
	    parm = NULL;
	}
	break;

    case T_STRING:
    case OCTET_PTR:
    case BITSTR_PTR:
	if (*(char **) (parm + p->pe_ucode) != NULL) {
	    free(*(char **) (parm + p->pe_ucode));
	    *(char **) (parm + p->pe_ucode) = NULL;
	}
	break;

    case OCTETSTRING:
	if (*(char **) (parm + p->pe_ucode) != NULL) {
	    qb_free(*(struct qbuf **) (parm + p->pe_ucode));
	    *(struct qbuf **) (parm + p->pe_ucode) = (struct qbuf *)0;
	}
	break;

    case SBITSTRING:
	if (parm != NULL) {
	    pe_free((PE) parm);
	    parm = NULL;
	}
	break;

    case BITSTRING:
	if (*(char **) (parm + p->pe_ucode) != NULL) {
	    pe_free(*(PE *) (parm + p->pe_ucode));
	    *(PE *) (parm + p->pe_ucode) = NULL;
	}
	break;

    case SOBJID:
	if (parm != NULL) {
	    oid_free((OID) parm);
	    parm = NULL;
	}
	break;

    case OBJID:
	if (*(char **) (parm + p->pe_ucode) != NULL) {
	    oid_free(*(OID *) (parm + p->pe_ucode));
	    *(OID *) (parm + p->pe_ucode) = NULL;
	}
	break;

    default:
	(void) pepsylose (mod, p, NULL, "fre_type: %d not implemented\n",
	    p->pe_type);
	return (NOTOK);
    }

    return (OK);
}

/*
 * free elements of a sequential type. e.g. sequence or set
 */
static int
fre_seq(char *parm, ptpe *p, modtyp *mod, int dofree)
{
/*    int    *popt = NULL;	Pointer to optional field */
    char   *malptr = NULL;	/* Have we seen a malloc */
    int	    ndofree = dofree;	/* Does the function below deallocate space */


    if (parm == 0)
	return OK;

    if (p->pe_type != SEQ_START && p->pe_type != SET_START
     && p->pe_type != SSEQ_START && p->pe_type != SSET_START) {
	(void) pepsylose (mod, p, NULL, "fre_seq: bad starting item %d\n",
	    p->pe_type);
	return (NOTOK);
    }
    p++;

    if (p->pe_type == DFLT_B)
	p++;

    while (p->pe_type != PE_END) {

	switch (p->pe_type) {
	case MEMALLOC:
	    if (dofree) {
		malptr = parm;
		ndofree = 0;	/* we are deallocating space on this level */
	    }
	    break;

	case OPTL:
/*	    popt = (int *) (parm + p->pe_ucode); */
	    break;

	case ETAG:
	    p++;
	    continue;

	case UCODE:
	    break;

	case SET_START:
	case SEQ_START:
	    if (fre_seq(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
		return (NOTOK);
	    break;

	case SETOF_START:
	case SEQOF_START:
	    if (fre_seqof(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
		return (NOTOK);
	    break;

	case SSEQ_START:
	case SSET_START:
	    if (fre_seq((char *) parm + p->pe_ucode, p, mod, ndofree) != OK)
		return (NOTOK);
	    break;

	case SSEQOF_START:
	case SSETOF_START:
	    if (fre_seqof((char *) parm + p->pe_ucode, p, mod, ndofree) != OK)
		return (NOTOK);
	    break;

	case IMP_OBJ:
	    p++;
	    continue;

	case SOBJECT:
	    if (fre_obj((char *) parm + p->pe_ucode,
		mod->md_dtab[p->pe_tag], mod, ndofree) != OK)
		return (NOTOK);
	    break;

	case OBJECT:
	    if (fre_obj(*(char **) (parm + p->pe_ucode),
		    mod->md_dtab[p->pe_tag], mod, 1) != OK)
		return (NOTOK);
	    break;

	case SCHOICE_START:
	    if (fre_choice((char *) parm + p->pe_ucode, p, mod, ndofree) != OK)
		return (NOTOK);
	    break;

	case CHOICE_START:
	    if (fre_choice(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
		return (NOTOK);
	    break;

	case SEXTOBJ:
	    if (p[1].pe_type != EXTMOD) {
		(void) pepsylose (mod, p, NULL, "fre_seq:missing EXTMOD");
		return (NOTOK);
	    }
	    if (fre_obj(parm + p->pe_ucode, (EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
		    EXT2MOD(mod, (p + 1)), ndofree) != OK)
		return (NOTOK);
	    break;

	case EXTOBJ:
	    if (p[1].pe_type != EXTMOD) {
		(void) pepsylose (mod, p, NULL, "fre_seq:missing EXTMOD");
		return (NOTOK);
	    }
	    if (fre_obj(*(char **) (parm + p->pe_ucode),
		    (EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
		    EXT2MOD(mod, (p + 1)), 1) != OK)
		return (NOTOK);
	    break;

	default:
	    if (fre_type(parm, p, mod, ndofree) != OK)
		return (NOTOK);
	    break;
	}

	NEXT_TPE(p);
    }
    if (malptr && dofree) {	/* If we saw a malloc free item */
	free(malptr);
	malptr = NULL;
    }
    
    return (OK);

}

/*
 * free all the fields in a SET OF/SEQUENCE OF type structure. We
 * must follow the linked list until the end
 */
static int
fre_seqof(char *parm, ptpe *p, modtyp *mod, int dofree)
{
    ptpe    *start;		/* first entry in list */
    char   *oparm;

    if (parm == 0)
	return OK;

    if (p->pe_type != SEQOF_START && p->pe_type != SETOF_START
     && p->pe_type != SSEQOF_START && p->pe_type != SSETOF_START) {
	(void) pepsylose (mod, p, NULL, "fre_seqof: illegal field");
	return (NOTOK);
    }
    for (start = p; (char *) parm != NULL; p = start) {
	p++;

	if (p->pe_type == DFLT_B)
	    p++;

	while (p->pe_type != PE_END) {

	    switch (p->pe_type) {
	    case MEMALLOC:
		break;

	    case ETAG:
		p++;
		continue;

	    case UCODE:
		break;

	    case SEQ_START:
	    case SET_START:
		if (fre_seq(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
		    return (NOTOK);
		break;

	    case SEQOF_START:
	    case SETOF_START:
		if (fre_seqof(*(char **) (parm + p->pe_ucode), p, mod, 1) != OK)
		    return (NOTOK);
		break;

	    case SSEQ_START:
	    case SSET_START:
		if (fre_seq((char *) parm + p->pe_ucode, p, mod, dofree) != OK)
		    return (NOTOK);
		break;

	    case SSEQOF_START:
	    case SSETOF_START:
		if (fre_seqof((char *) parm + p->pe_ucode, p, mod, dofree) != OK)
		    return (NOTOK);
		break;

	    case IMP_OBJ:
		p++;
		continue;

	    case SOBJECT:
		if (fre_obj(parm + p->pe_ucode, mod->md_dtab[p->pe_tag], mod, 0) != OK)
		    return (NOTOK);
		break;

	    case OBJECT:
		if (fre_obj(*(char **) (parm + p->pe_ucode),
			mod->md_dtab[p->pe_tag], mod, 1) != OK)
		    return (NOTOK);
		break;

	    case SCHOICE_START:
		if (fre_choice((char *) parm + p->pe_ucode, p, mod, 0) != OK)
		    return (NOTOK);
		break;

	    case CHOICE_START:
		if (fre_choice(*(char **)(parm + p->pe_ucode), p, mod, 1) != OK)
		    return (NOTOK);
		break;

	    case SEXTOBJ:
		if (p[1].pe_type != EXTMOD) {
		    (void) pepsylose (mod, p, NULL,
			"fre_seqof: missing EXTMOD");
		    return (NOTOK);
		}
		if (fre_obj(parm + p->pe_ucode, (EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
			EXT2MOD(mod, (p + 1)), 0) != OK)
		    return (NOTOK);
		break;

	    case EXTOBJ:
		if (p[1].pe_type != EXTMOD) {
		    (void) pepsylose (mod, p, NULL,
			"fre_seqof: missing EXTMOD");
		    return (NOTOK);
		}
		if (fre_obj(*(char **) (parm + p->pe_ucode),
			(EXT2MOD(mod, (p + 1)))->md_dtab[p->pe_tag],
			EXT2MOD(mod, (p + 1)), 1) != OK)
		    return (NOTOK);
		break;

	    default:
		if (fre_type(parm, p, mod, 1) != OK)
		    return (NOTOK);
		break;
	    }

	    NEXT_TPE(p);
	}
	oparm = parm;
	parm = *(char **) (parm + p->pe_ucode);	/* Any more ? */
	if (dofree) {
	    free(oparm);
	    oparm = NULL;
	}
    }

    return (OK);

}

/*
 * free the item of the choice. Use the SCTRL field to determine
 * which item is present and then call the appropriate routine to
 * free it
 */
static int
fre_choice(char *parm, ptpe *p, modtyp *mod, int dofree)
{
    int     cnt;
    char   *malptr = NULL;	/* Have we seen a malloc */
    int	    ndofree = dofree;	/* Does the function below deallocate space */

    if (parm == 0)
	return OK;

    if (p->pe_type != CHOICE_START && p->pe_type != SCHOICE_START) {
	(void) pepsylose (mod, p, NULL,
	    "fre_choice:CHOICE_START missing found %d\n", p->pe_type);
    }
    p++;

    if (p->pe_type == DFLT_B)
	p++;

    if (p->pe_type == MEMALLOC) {
	if (dofree) {
	    malptr = parm;
	    ndofree = 0;	/* we are deallocating space on this level */
	}
	p++;
    }
    if (p->pe_type != SCTRL) {
	(void) pepsylose (mod, p, NULL,
	    "fre_choice: missing SCTRL information\n");
	return (NOTOK);
    }
    cnt = *(int *) (parm + p->pe_ucode);
    if (cnt != 0)
	cnt--;
    if (cnt < 0) {
	(void) pepsylose (mod, p, NULL,"fre_choice:offset negative %d", cnt);
	return (NOTOK);
    }
    for (p++; p->pe_type != PE_END; NEXT_TPE(p)) {
	if (ISDTYPE(p)) {
	    if (cnt == 0) {
		if (fre_type(parm, p, mod, ndofree) != OK)
		    return (NOTOK);
		if (malptr && dofree) {	/* If we saw a malloc free item */
		    free(malptr);
		    malptr = NULL;
		}
		return (OK);
	    }
	    cnt--;
	}
    }

    (void) pepsylose (mod, p, NULL, "fre_choice: no choice taken");
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

