/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:39  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:18  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:07  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:30  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:19  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:22  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/03/06 15:59:50  mmiers
 * LOG: Versioning.
 * LOG:
 * LOG: Revision 3.2  2001/01/04 17:19:41  hdivoux
 * LOG: symbol collision
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:07:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/05/11 02:06:14  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:30:00  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/07/22 00:35:19  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.2  1999/04/09 21:30:41  mmiers
 * LOG:
 * LOG:
 * LOG: Remove all 218 warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:36:57  jpakrasi
 * LOG: Build pepsy on NT.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asncomp.h"
#include "pass2.h"
#include "table.h"

#ident "$Id: dtabs.c,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

extern char *c_tag(), *c_class();
extern char *ec_tag(), *ec_class();
extern char *strip_last();
extern char *str_yp_code[];
extern char *get_val(), *get_comp(), *strp2name();
extern s_table *lookup_list(), *get_offset();
extern void tdec_loop(FILE *fp, YP yp, char *id, char *type);
extern void gdflt(FILE *fp, YP yp, int which);


extern char *concat();
extern char *my_strcat();
extern char *rm_indirect();
extern char *getfield();
extern char *setfield();
extern char *modsym();
extern char *genstrform();
extern int gen_sentry();
extern void ferr(int, char *);
extern void ferrs(int, char *, char *);
extern void ferrd(int, char *, int);
extern int noindirect(char *f);
extern int gen_modref(char *mod);
extern void gen_identry(FILE *fp, char *t, char *f, YP yp, int (*fn) (/* ??? */));
extern int optfield(YP yp);
extern void prnte(FILE *fp, char *t, char *f, YP yp, char *p1);
extern void prstfield(FILE *fp, char *typ, char *t, char *f, char *cl, char *fl, YP yp);
extern void prtfield(FILE *fp, char *typ, char *t, char *f, char *cl, char *fl, YP yp);
extern void prcte(FILE *fp, char *type, char *t, char *f, YP yp, char *p1);
extern int addptr(char *p);
extern char *int2tstr(int i);
extern char *c_flags(YP yp, PElementClass cl);

int gen_freefn(FILE *fp, YP yp);
void genmalloc(FILE *fp, YP yp);
int hasdatstr(YP yp);

/* extern int explicit; */

#define WORDSIZE	20

/*
 * table encode a type. generate tables for the encoding of a type
 */
void
tdec_typ(FILE *fp, YP yp, char *id, char *type)
{
    char *t, *f;
    char *p1 = NULL;
    YP y;

    if (yp->yp_code < 0 || yp->yp_code > YP_REAL)
	ferrd(1, "tdec_typ: unimplemented type %d\n", yp->yp_code);

    if (yp == NULL)
    {
	ferr(0, "tdec_typ:NULL arguement\n");
	return;
    }

    if (type)
	t = type;
    else if (yp->yp_param_type)
    {
	char *t1;
	/* we have a [[ P type ]] specification */
	if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
	{
	    (void)fprintf(stderr,
		      "\ntdec_typ:SETLIST can't extract direct type from %s\n",
			  yp->yp_param_type);
	    exit(1);
	}
	t = strdup(t1);
    }
    else
	t = my_strcat("struct ", modsym(mymodule, id, "type"));

    if (type == NULL)
    {
	switch (yp->yp_code)
	{
	    /*
	     * These generate MEMALLOC entries inside *_START ..
	     * PE_END fields for historical reasons. One day we might
	     * fix this to be all done the same way.
	     */
	case YP_SEQLIST:
	case YP_SEQTYPE:
	case YP_SETLIST:
	case YP_SETTYPE:
	case YP_CHOICE:
	    break;

	default:
	    if (yp->yp_varexp == NULL)
		break;		/* S* type entry - doesn't need a
				 * malloc */

	    (void)fprintf(fp, "\t{ MEMALLOC, 0, sizeof (%s), 0, %s },\n",
			  t, genstrform(yp));
	    break;
	}
    }


    if ((yp->yp_flags & YP_PARMVAL) && yp->yp_parm)
    {
	if ((f = getfield(yp->yp_parm)) == NULL)
	{
	    (void)fprintf(stderr, "\ntdec_typ: can't extract field from %s\n",
			  yp->yp_parm);
	    exit(1);
	}
	f = strdup(f);
    }
    else
	f = yp->yp_varexp;

    if ((yp->yp_flags & (YP_OPTIONAL | YP_OPTCONTROL | YP_DEFAULT))
	== (YP_OPTIONAL | YP_OPTCONTROL))
    {
	char *f1;
	char *bitno;

	if ((f1 = getfldbit(yp->yp_optcontrol, &bitno)) == NULL)
	{
	    (void)fprintf(stderr,
		     "\ntdec_typ:BOPTIONAL: can't extract field from %s\n",
			  yp->yp_optcontrol);
	    exit(1);
	}
	(void)fprintf(fp, "\t{ BOPTIONAL, AOFFSET(%s, %s), %s, 0, %s},\n", t,
		      f1, bitno, genstrform(yp));
    }

    if (yp->yp_flags & YP_TAG && !(yp->yp_flags & YP_IMPLICIT))
    {
	(void)fprintf(fp, "\t{ ETAG, 0, ");
	(void)fprintf(fp, "%s, %s, %s },\n", ec_tag(yp), ec_class(yp),
		      genstrform(yp));
    }

    switch (yp->yp_code)
    {

    case YP_UNDF:
	ferr(1, "tdec_typ:Undefined type\n");

    case YP_BOOL:
	if (yp->yp_intexp)
	    f = setfield(yp->yp_intexp);
	if (noindirect(f))
	    ferr(1, "tdec_typ:BOOL: must specify a field for boolean\n");
	p1 = "BOOLEAN";
	if (yp->yp_varexp || (yp->yp_intexp && !noindirect(f)))
	    break;
	ferr(1, "tdec_typ:BOOL: couldn't determine type\n");

	/* This needs to be fixed up in the action generating area */
    case YP_INTLIST:

    case YP_INT:

    case YP_ENUMLIST:
	if (yp->yp_intexp)
	    f = setfield(yp->yp_intexp);
	if (noindirect(f))
	    ferr(1, "tdec_typ:INT: must specify a field for an integer\n");
	if (yp->yp_varexp || (yp->yp_intexp && !noindirect(f)))
	{
	    p1 = "INTEGER";
	    break;
	}
	ferr(1, "tdec_typ:INT: couldn't determine type\n");
	break;

    case YP_REAL:
	if (yp->yp_strexp)
	    f = setfield(yp->yp_strexp);
	if (noindirect(f))
	    ferr(1, "tdec_typ:REAL: must specify a field for a REAL\n");
	if (yp->yp_varexp || (yp->yp_strexp && !noindirect(f)))
	{
	    p1 = "REALTYPE";
	    break;
	}
	ferr(1, "tdec_typ:REAL: couldn't determine type\n");
	break;


    case YP_BIT:
    case YP_BITLIST:
	if (yp->yp_strexp && yp->yp_intexp)
	{
	    if (yp->yp_strexp)
		f = setfield(yp->yp_strexp);
	    if (noindirect(f))
		ferr(1, "tdec_typ:BIT: must specify a [[ x ... ]] value\n");
	    p1 = "BITSTR_PTR";
	    prnte(fp, t, f, yp, p1);
	    if (yp->yp_intexp)
		f = setfield(yp->yp_intexp);
	    if (noindirect(f))
		ferr(1, "tdec_typ:BIT: must specify a [[ x ... ]] value\n");
	    p1 = "BITSTR_LEN";
	    break;
	}
	if (yp->yp_strexp == NULL && yp->yp_intexp)
	    f = setfield(yp->yp_intexp);
	if (yp->yp_varexp || (yp->yp_intexp && !noindirect(f)))
	{
	    p1 = "BITSTRING";
	    break;
	}
	t = NULL;
	p1 = NULL;
	(void)fprintf(fp, "\t{ SBITSTRING, 0, %s, %s, %s },\n",
		      c_tag(yp), c_class(yp), genstrform(yp));
	break;

    case YP_OCT:
	if (yp->yp_strexp)
	{
	    switch (yp->yp_prfexp)
	    {
	    case 'q':		/* [[ q parm->qbufptr ]] */
		if (yp->yp_strexp)
		    f = setfield(yp->yp_strexp);
		if (noindirect(f))
		    p1 = "SOCTETSTRING";
		else
		    p1 = "OCTETSTRING";
		break;

	    case 's':		/* [[ s ptr ]] */
		if (yp->yp_strexp)
		    f = setfield(yp->yp_strexp);
		if (noindirect(f))
		    ferr(1, "tdec_typ:OCTET: must specify a field [[ s .. ]]\n");
		p1 = "T_STRING";
		break;

	    case 'o':		/* [[ o ptr $ length ]] */
		if (yp->yp_strexp)
		    f = setfield(yp->yp_strexp);
		if (noindirect(f))
		    ferr(1, "tdec_typ:OCTET: must specify a field [[ o .. ]]\n");
		p1 = "OCTET_PTR";
		prnte(fp, t, f, yp, p1);
		if (yp->yp_intexp)
		    f = setfield(yp->yp_intexp);
		if (noindirect(f))
		    ferr(1, "tdec_typ:OCTET: must specify a field [[ o .. $ .. ]]\n");
		p1 = "OCTET_LEN";
		break;

	    default:
		(void)fprintf(stderr, "\ntdec_typ: Unknown Octet string specifier %c\n",
			      yp->yp_prfexp);
		exit(1);
	    }
	    break;
	}
	if (f)
	{
	    p1 = "OCTETSTRING";
	    break;
	}
	t = NULL;
	p1 = NULL;
	(void)fprintf(fp, "\t{ SOCTETSTRING, 0, %s, %s, %s },\n",
		      c_tag(yp), c_class(yp), genstrform(yp));
	break;

    case YP_OID:
	if (yp->yp_strexp)
	    f = setfield(yp->yp_strexp);
	if (yp->yp_varexp || (yp->yp_strexp && !noindirect(f)))
	{
	    p1 = "OBJID";
	    break;
	}
	t = NULL;
	p1 = NULL;
	(void)fprintf(fp, "\t{ SOBJID, 0, %s, %s, %s },\n",
		      c_tag(yp), c_class(yp), genstrform(yp));
	break;

    case YP_SEQ:
    case YP_SET:
    case YP_ANY:
	if (yp->yp_strexp)
	    f = setfield(yp->yp_strexp);
	if (yp->yp_varexp || (yp->yp_strexp && !noindirect(f)))
	{
	    p1 = "ANY";
	    break;
	}
	t = NULL;
	p1 = NULL;
	(void)fprintf(fp, "\t{ SANY, 0, %s, %s, %s },\n",
		      c_tag(yp), c_class(yp), genstrform(yp));
	break;

    case YP_NULL:
	p1 = "ASN_NULL";
	t = NULL;
	break;

    case YP_IDEFINED:
	p1 = NULL;

	if ((yp->yp_flags & YP_PARMVAL) && yp->yp_prfexp)
	    ferr(1,
		 "\n[[ ? reference ]] [[ p reference ]] is illegal\n\t only one allowed\n");

	if (yp->yp_prfexp)
	{			/* [[ ? parm->field ]] - complex to process */
	    gen_identry(fp, t, f, yp, gen_ventry);

	    if (yp->yp_flags & YP_DEFAULT)
		gdflt(fp, yp, G_DEC);

	    break;
	}

	{
	    /* Predefined Universal Type */
	    struct univ_typ *p, *univtyp();

	    if ((p = univtyp(yp->yp_identifier)))
	    {
		if (p->univ_flags & UNF_EXTMOD)
		{
		    yp->yp_module = p->univ_mod;
		    goto do_obj;
		}
		if (f == NULL || noindirect(f))
		{		/* No offset type */
		    if (yp->yp_flags & YP_TAG
			&& yp->yp_flags & YP_IMPLICIT)
                    {
			prstfield(fp, p->univ_tab, t, f,
				  int2tstr(yp->yp_tag->yt_value->yv_number),
				  c_flags(yp, (PElementClass)yp->yp_tag->yt_class), yp);
                    }
		    else
                    {
			prstfield(fp, p->univ_tab, t, f,
				  int2tstr((int)p->univ_id),
				  c_flags(yp, p->univ_class), yp);
                    }
		    goto out;
		}
		if (yp->yp_flags & YP_TAG && yp->yp_flags & YP_IMPLICIT)
		    prtfield(fp, p->univ_tab, t, f,
			     int2tstr(yp->yp_tag->yt_value->yv_number),
			     c_flags(yp, (PElementClass)yp->yp_tag->yt_class), yp);
		else
		    prtfield(fp, p->univ_tab, t, f,
			     int2tstr((int)p->univ_id),
			     c_flags(yp, p->univ_class), yp);
		goto out;
	    }
	}
      do_obj:
	if (yp->yp_flags & YP_TAG && yp->yp_flags & YP_IMPLICIT)
	    (void)fprintf(fp, "\t{ IMP_OBJ, 0, %s, %s, %s },\n",
			  c_tag(yp), c_class(yp), genstrform(yp));
	if (yp->yp_module == NULL
	    || strcmp(yp->yp_module, mymodule) == 0)
	{
	    if (f == NULL || noindirect(f))
		prstfield(fp, "OBJECT", t, f,
			  concat("_Z", proc_name(yp->yp_identifier, 0)),
			  c_class(yp), yp);
	    else
		prtfield(fp, "OBJECT", t, f,
			 concat("_Z", proc_name(yp->yp_identifier, 0)),
			 c_class(yp), yp);

	}
	else
	{
	    if (f == NULL || noindirect(f))
		prstfield(fp, "EXTOBJ", t, f,
		     concat("_Z", strp2name(yp->yp_identifier, yp->yp_module)),
			  c_class(yp), yp);
	    else
		prtfield(fp, "EXTOBJ", t, f,
		     concat("_Z", strp2name(yp->yp_identifier, yp->yp_module)),
			 c_class(yp), yp);
	    (void)fprintf(fp, "\t{ EXTMOD, %d, 0, 0, %s },\n",
			  gen_modref(yp->yp_module), genstrform(yp));
	}
      out:
	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);
	break;

    case YP_SEQLIST:
	p1 = NULL;
	/* support for -h flag */
	if (yp->yp_varexp == NULL && type != NULL)
	    ferr(1, "tdec_typ:YP_SEQLIST:NULL varexp pointer\n");
	prcte(fp, type, t, f, yp, "SEQ_START");

	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);
	if ((y = yp->yp_type) != NULL)
	{
	    char *t1;

	    if (yp->yp_param_type)
	    {
		/* we have a [[ P type ]] specification */
		if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
		{
		    (void)fprintf(stderr,
		      "\ntdec_typ:SEQLIST can't extract direct type from %s\n",
				  yp->yp_param_type);
		    exit(1);
		}
		yp->yp_structname = strdup(t1);
	    }
	    else if (type)
	    {
		if (yp->yp_declexp == NULL)
		    ferr(1, "tdec_typ:YP_SEQLIST:no declexp\n");
		yp->yp_structname = my_strcat("struct ", yp->yp_declexp);
	    }
	    else
		yp->yp_structname = t;

	    if (!type || !noindirect(f))
		genmalloc(fp, yp);

	    if (optfield(y))
	    {
		(void)fprintf(fp,
			      "\t{ OPTL, OFFSET(%s, optionals), 0, 0, %s },\n",
			      yp->yp_structname, genstrform(y));
	    }
	    tdec_loop(fp, y, id, yp->yp_structname);
	}
	(void)fprintf(fp, "\t{ PE_END, 0, 0, 0, %s },\n", genstrform(yp));
	break;

    case YP_SETLIST:
	p1 = NULL;
	/* support for -h flag */
	p1 = NULL;
	if (yp->yp_varexp == NULL && type != NULL)
	    ferr(1, "tdec_typ:YP_SETLIST:NULL varexp pointer\n");
	prcte(fp, type, t, f, yp, "SET_START");

	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);
	if ((y = yp->yp_type) != NULL)
	{
	    char *t1;

	    if (yp->yp_param_type)
	    {
		/* we have a [[ P type ]] specification */
		if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
		{
		    (void)fprintf(stderr,
		      "\ntdec_typ:SETLIST can't extract direct type from %s\n",
				  yp->yp_param_type);
		    exit(1);
		}
		yp->yp_structname = strdup(t1);
	    }
	    else if (type)
	    {
		if (yp->yp_declexp == NULL)
		    ferr(1, "tdec_typ:YP_SETLIST:no declexp\n");
		yp->yp_structname = my_strcat("struct ", yp->yp_declexp);
	    }
	    else
		yp->yp_structname = t;

	    if (!type || !noindirect(f))
		genmalloc(fp, yp);

	    if (optfield(y))
	    {
		(void)fprintf(fp,
			      "\t{ OPTL, OFFSET(%s, optionals), 0, 0, %s },\n",
			      yp->yp_structname, genstrform(y));
	    }
	    tdec_loop(fp, y, id, yp->yp_structname);
	}
	(void)fprintf(fp, "\t{ PE_END, 0, 0, 0, %s },\n", genstrform(yp));
	break;

    case YP_SEQTYPE:		/* What is the difference ?? */
	p1 = NULL;
	prcte(fp, type, t, f, yp, "SEQOF_START");

	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);

	if ((y = yp->yp_type) != NULL)
	{
	    char *t1;

	    if (yp->yp_param_type)
	    {
		/* we have a [[ P type ]] specification */
		if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
		{
		    (void)fprintf(stderr,
		      "\ntdec_typ:SEQTYPE can't extract direct type from %s\n",
				  yp->yp_param_type);
		    exit(1);
		}
		yp->yp_structname = strdup(t1);
	    }
	    else if (type)
	    {
		if (yp->yp_declexp == NULL)
		    ferr(1, "tdec_typ:YP_SEQTYPE:no declexp\n");
		yp->yp_structname = my_strcat("struct ", yp->yp_declexp);
	    }
	    else
		yp->yp_structname = t;

	    if (!type || !noindirect(f))
		genmalloc(fp, yp);

	    tdec_loop(fp, y, id, yp->yp_structname);
	}
	if (yp->yp_flags & YP_CONTROLLED)
	{
	    char *f1;

	    if ((f1 = getfield(yp->yp_control)) == NULL)
	    {
		(void)fprintf(stderr, "\ntdec_typ:SEQ OF: can't extract field from %s\n",
			      yp->yp_control);
		exit(1);
	    }
	    (void)fprintf(fp, "\t{ PE_END, OFFSET(%s, %s), 0, 0, %s },\n",
			  yp->yp_structname, f1, genstrform(yp));
	}
	else if (yp->yp_structname != NULL)
	    (void)fprintf(fp, "\t{ PE_END, OFFSET(%s, next), 0, 0, %s },\n",
			  yp->yp_structname, genstrform(yp));
	else
	    (void)fprintf(fp, "\t{ PE_END, 0, 0, 0, %s },\n",
			  genstrform(yp));
	break;

    case YP_SETTYPE:
	p1 = NULL;
	prcte(fp, type, t, f, yp, "SETOF_START");

	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);

	if ((y = yp->yp_type) != NULL)
	{
	    char *t1;


	    if (yp->yp_param_type)
	    {
		/* we have a [[ P type ]] specification */
		if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
		{
		    (void)fprintf(stderr,
		      "\ntdec_typ:SETTYPE can't extract direct type from %s\n",
				  yp->yp_param_type);
		    exit(1);
		}
		yp->yp_structname = strdup(t1);
	    }
	    else if (type)
	    {
		if (yp->yp_declexp == NULL)
		    ferr(1, "tdec_typ:YP_SETTYPE:no declexp\n");
		yp->yp_structname = my_strcat("struct ", yp->yp_declexp);
	    }
	    else
		yp->yp_structname = t;

	    if (!type || !noindirect(f))
		genmalloc(fp, yp);

	    tdec_loop(fp, y, id, yp->yp_structname);
	}
	if (yp->yp_flags & YP_CONTROLLED)
	{
	    char *f1;

	    if ((f1 = getfield(yp->yp_control)) == NULL)
	    {
		(void)fprintf(stderr, "\ntdec_typ:SET OF: can't extract field from %s\n",
			      yp->yp_control);
		exit(1);
	    }
	    (void)fprintf(fp, "\t{ PE_END, OFFSET(%s, %s), 0, 0, %s },\n",
			  yp->yp_structname, f1, genstrform(yp));
	}
	else if (yp->yp_structname != NULL)
	    (void)fprintf(fp, "\t{ PE_END, OFFSET(%s, next), 0, 0, %s },\n",
			  yp->yp_structname, genstrform(yp));
	else
	    (void)fprintf(fp, "\t{ PE_END, 0, 0, 0, %s },\n", genstrform(yp));
	break;

    case YP_CHOICE:
	p1 = NULL;
	/* support for -h flag */
	if (hflag && (y = yp->yp_type) && !y->yp_next)
	{
	    tdec_typ(fp, y, id, yp->yp_structname);
	    break;
	}
	if (type == NULL || (type && noindirect(f)))
	    prstfield(fp, "CHOICE_START", t, f, NULL, c_class(yp), yp);
	else
	    prtfield(fp, "CHOICE_START", t, type ? f : NULL,
		     NULL, c_class(yp), yp);

	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);
	if ((y = yp->yp_type) != NULL)
	{
	    char *t1;

	    if (yp->yp_param_type)
	    {
		/* we have a [[ P type ]] specification */
		if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
		{
		    (void)fprintf(stderr,
		       "\ntdec_typ:CHOICE can't extract direct type from %s\n",
				  yp->yp_param_type);
		    exit(1);
		}
		yp->yp_structname = strdup(t1);
	    }
	    else if (type)
	    {
		if (yp->yp_declexp == NULL)
		    ferr(1, "tdec_typ:YP_CHOICE:no declexp\n");
		yp->yp_structname = my_strcat("struct ", yp->yp_declexp);
	    }
	    else
		yp->yp_structname = t;

	    if (!type || !noindirect(f))
		genmalloc(fp, yp);


	    if (yp->yp_flags & YP_CONTROLLED)
	    {
		char *f1;

		if ((f1 = getfield(yp->yp_control)) == NULL)
		{
		    (void)fprintf(stderr, "\ntdec_typ:CHOICE: can't extract field from %s\n",
				  yp->yp_control);
		    exit(1);
		}
		(void)fprintf(fp, "\t{ SCTRL, OFFSET(%s, %s), 0, 0, %s },\n",
			      yp->yp_structname, f1, genstrform(yp));
	    }
	    else if (yp->yp_structname != NULL)
		(void)fprintf(fp, "\t{ SCTRL, OFFSET(%s, offset), 0, 0, %s },\n",
			      yp->yp_structname, genstrform(yp));
	    else
		ferr(1, "\nCHOICE missing SCTRL\n");

	    if (yp->yp_param_type)
	    {
		/* we have a [[ P type ]] specification */
		if ((t1 = rm_indirect(yp->yp_param_type)) == NULL)
		{
		    (void)fprintf(stderr,
		       "\ntdec_typ:CHOICE can't extract direct type from %s\n",
				  yp->yp_param_type);
		    exit(1);
		}
		yp->yp_structname = strdup(t1);
	    }
	    else if (type)
	    {
		if (yp->yp_declexp == NULL)
		    ferr(1, "tdec_typ:YP_CHOICE:no declexp\n");
		yp->yp_structname = my_strcat("struct ", yp->yp_declexp);
	    }
	    else
		yp->yp_structname = t;
	    tdec_loop(fp, y, id, yp->yp_structname);
	}
	(void)fprintf(fp, "\t{ PE_END, 0, 0, 0, %s },\n", genstrform(yp));
	break;

    default:
	ferrd(1, "tdec_typ: yp_code = %d  not implemented\n", yp->yp_code);
    }

    if (p1 != NULL)
    {
	prnte(fp, t, f, yp, p1);

	if (yp->yp_flags & YP_DEFAULT)
	    gdflt(fp, yp, G_DEC);
    }
}

/*
 * generate tables for encoding a contructed type
 */
void
tdec_loop(FILE *fp, YP yp, char *id, char *type)
{
    for (; yp != NULL; yp = yp->yp_next)
    {
	tdec_typ(fp, yp, id, type);
    }
}

/*
 * Generate a malloc of for the given object
 */
void
genmalloc(FILE *fp, YP yp)
{
    if (hasdatstr(yp))
	(void)fprintf(fp, "\t{ MEMALLOC, 0, sizeof (%s), 0, %s },\n",
		      yp->yp_structname, genstrform(yp));
}
/*
 * Has Data Structure,
 * determine if this type needs a data structure allocated to it - calls
 * itself recursively to handle the cases of pulled up types
 * returns non zero if it does need a type allocated for it
 */
int
hasdatstr(YP yp)
{
    YP y;
    YP yp1;
    struct univ_typ *p;

    switch (yp->yp_code)
    {
    case YP_BIT:
    case YP_BITLIST:
    case YP_SEQ:
    case YP_SET:
    case YP_ANY:
    case YP_OCT:
    case YP_OID:
	break;

    case YP_IDEFINED:

	yp1 = lkup(yp);

	if (yp1->yp_code == YP_IDEFINED)
	{
	    if ((p = univtyp(yp1->yp_identifier)) == NULL
		|| p->univ_type <= YP_UNDF)
	    {
		return (1);	/* we can't tell unless we know what this is */
		/* ferr(0, "\tcomptag:treated as implicit\n"); */
	    }
	    if (p->univ_flags & UNF_HASDATA)
		return (1);
	    return (0);
	}
	else
	    return (hasdatstr(yp1));

    case YP_SEQLIST:
    case YP_SETLIST:
    case YP_CHOICE:
	if (hflag && (y = yp->yp_type) && !y->yp_next)
	{
	    return (hasdatstr(y));
	}
	/* else fall */

    default:
	return (1);
    }
    return (0);
}

/*
 * generate an entry for the freeing routines
 * if there is a freeing function just call that
 * if not specify the type and offset so the free routines know how to free it
 * return non zero if we don't want the normal decoding entry to be
 * generated after us for freeing purposes.
 */
int
gen_freefn(FILE *fp, YP yp)
{
    (void)fprintf(fp, "\t{ FREE_ONLY, 0, 0, 0, %s},\n",
		  genstrform(yp));
    return (0);

}
