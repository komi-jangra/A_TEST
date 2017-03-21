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
 * LOG: Revision 9.1  2005/03/23 12:54:08  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:49  cvsadmin
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
 * LOG: Revision 3.2  2001/03/06 15:59:50  mmiers
 * LOG: Versioning.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:07:22  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/05/11 02:06:16  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:30:04  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/06/01 17:26:41  labuser
 * LOG:
 * LOG:
 * LOG: Get rid of Berkeley byte functions.
 * LOG:
 * LOG: Revision 1.4  1999/04/09 21:30:42  mmiers
 * LOG:
 * LOG:
 * LOG: Remove all 218 warnings.
 * LOG:
 * LOG: Revision 1.3  1998/10/26 15:29:21  mmiers
 * LOG: symbol collision avoidance.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 04:31:16  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:36:59  jpakrasi
 * LOG: Build pepsy on NT.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "asncomp.h"

#ident "$Id: misc.c,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

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

extern void myyerror(char *format,...);
extern void warning(char *format,...);

typedef struct oidlist
{
    OID op_oid;
    char *op_name;
    struct oidlist *op_next;
}
oidlist, *OP;

typedef struct symtable
{
    char *sym_name;
    char *sym_module;
    OID sym_oid;
    int sym_type;
    struct symtable *sym_next;
}
symtable, *SYM;


static OP myoids;
static SYM symtab[MAX_TBLS];


OID
addoid(OID o1, OID o2)
{
    OID noid;

    if (o1 == NULL || o2 == NULL)
	return NULL;

    noid = (OID) calloc(1, sizeof(*noid));
    if (noid == NULL)
	myyerror("out of memory (%d needed)", sizeof(*noid));

    noid->oid_nelem = o1->oid_nelem + o2->oid_nelem;
    noid->oid_elements = (unsigned int *)calloc((unsigned)noid->oid_nelem,
						sizeof(unsigned int));
    if (noid->oid_elements == NULL)
	myyerror("out of memory (%d needed)", noid->oid_nelem);

    memcpy((char *)noid->oid_elements, (char *)o1->oid_elements,
	   o1->oid_nelem * sizeof(unsigned int));
    memcpy((char *)&noid->oid_elements[o1->oid_nelem],
           (char *)o2->oid_elements,
	   o2->oid_nelem * sizeof(unsigned int));
    return noid;
}

void
defineoid(char *name, OID oid)
{
    register char *p;
    register OP op;

    if (oid == NULL)
    {
	myyerror("Warning Null oid in defineoid");
	return;
    }
    for (op = myoids; op; op = op->op_next)
	if (strcmp(op->op_name, name) == 0)
	{
	    if (oid_cmp(op->op_oid, oid) != 0)
	    {
		p = new_string(_sprintoid(oid));
		warning("OID name clash %s => %s & %s",
			name, p, _sprintoid(op->op_oid));
		free(p);
	    }
	    else
		return;
	}
    op = (OP) calloc(1, sizeof *op);
    if (op == NULL)
	myyerror("out of memory (%d needed)", sizeof(*op));
    op->op_oid = oid_cpy(oid);
    op->op_name = new_string(name);
    op->op_next = myoids;
    myoids = op;
}

OID
oidlookup(char *name)
{
    OP op;

    for (op = myoids; op; op = op->op_next)
	if (strcmp(name, op->op_name) == 0)
	    return oid_cpy(op->op_oid);

    warning("unknown Object Identifier '%s'", name);
    return NULL;
}

char *
oidname(OID oid)
{
    OP op;

    for (op = myoids; op; op = op->op_next)
	if (oid_cmp(op->op_oid, oid) == 0)
	    return op->op_name;

    return NULL;
}

OID
int2oid(int n)
{
    OID noid;

    noid = (OID) calloc(1, sizeof(*noid));
    if (noid == NULL)
	myyerror("out of memory (%d needed)", sizeof *noid);

    noid->oid_elements = (unsigned int *)calloc(1, sizeof(unsigned int));
    if (noid->oid_elements == NULL)
	myyerror("out of memory (%d needed)", sizeof(unsigned int));
    noid->oid_nelem = 1;
    noid->oid_elements[0] = n;
    return noid;
}

void
addtable(char *name, int lt, int typ)
                
            
             			/* Does it allow implicit's to work or not */
{
    SYM sp;

    sp = (SYM) calloc(1, sizeof *sp);
    sp->sym_name = new_string(name);
    sp->sym_next = symtab[lt];
    sp->sym_type = typ;
    symtab[lt] = sp;
}

void
addtableref(char *name, OID id, int lt)
{
    SYM sp;
    char *nm;
    OID oid;

    nm = name ? new_string(name) : NULL;
    oid = id ? oid_cpy(id) : NULL;

    for (sp = symtab[lt]; sp; sp = sp->sym_next)
	if (sp->sym_module == NULL && sp->sym_oid == NULL)
	{
	    sp->sym_module = nm;
	    sp->sym_oid = oid;
	}
}

void
print_expimp(void)
{
    SYM sp;
    int ind;
    OID oid = NULL;
    char *p = NULL;

    if ((sp = symtab[TBL_EXPORT]) != NULL)
	(void)printf("\nEXPORTS\n");

    for (ind = 0; sp; sp = sp->sym_next)
    {
	if (ind == 0)
	{
	    (void)putchar('\t');
	    ind = 8;
	}
	(void)printf("%s", sp->sym_name);
	ind += strlen(sp->sym_name);
	if (sp->sym_next)
	{
	    (void)putchar(',');
	    ind++;
	}
	else
	    (void)putchar(';');
	if (ind > 72)
	{
	    (void)putchar('\n');
	    ind = 0;
	}
	else
	{
	    (void)putchar(' ');
	    ind++;
	}
    }
    (void)putchar('\n');

    if ((sp = symtab[TBL_IMPORT]) != NULL)
    {
	(void)printf("\nIMPORTS\n");
	p = sp->sym_module;
	oid = sp->sym_oid;
    }
    for (ind = 0; sp; sp = sp->sym_next)
    {
	if (ind == 0)
	{
	    (void)putchar('\t');
	    ind = 8;
	}
	(void)printf("%s", sp->sym_name);
	ind += strlen(sp->sym_name);
	if (sp->sym_next)
	{
	    if (strcmp(p, sp->sym_next->sym_module) == 0)
	    {
		(void)putchar(',');
		ind++;
		if (ind > 72)
		{
		    (void)putchar('\n');
		    ind = 0;
		}
		else
		{
		    (void)putchar(' ');
		    ind++;
		}
	    }
	    else
	    {
		if (ind != 8)
		    (void)printf("\n\t\t");
		else
		    (void)putchar('\t');
		(void)printf("FROM %s", p);
		if (oid)
		    (void)printf(" %s", oidprint(oid));
		(void)printf("\n\t");
		ind = 8;
		p = sp->sym_next->sym_module;
		oid = sp->sym_next->sym_oid;
	    }
	}
	else
	{
	    if (ind != 8)
		(void)printf("\n\t\t");
	    else
		(void)putchar('\t');
	    (void)printf("FROM %s", p);
	    if (oid)
		(void)printf(" %s", oidprint(oid));
	    (void)printf(";\n");
	}
    }
}

void
check_impexp(YP yp)
{
    SYM sp;

    for (sp = symtab[TBL_EXPORT]; sp; sp = sp->sym_next)
	if (strcmp(sp->sym_name, yp->yp_identifier) == 0)
	{
	    yp->yp_flags |= YP_EXPORTED;
	    break;
	}

    for (sp = symtab[TBL_IMPORT]; sp; sp = sp->sym_next)
	if (strcmp(sp->sym_name, yp->yp_identifier) == 0)
	{
	    if (yp->yp_flags & YP_EXPORTED)
		myyerror("Warning: %s imported & exported!", yp->yp_identifier);
	    yp->yp_module = sp->sym_module;
	    yp->yp_modid = sp->sym_oid;
/*          yp -> yp_flags |= YP_IMPORTED;      */
	}
}
static struct oidtbl
{
    char *oid_name;
    int oid_value;
}
oidtable[] =
{
    /* Top level OIDS */
    { "ccitt", 0 },
    { "iso", 1 },
    { "joint-iso-ccitt", 2 },
    { NULL }
};

void
initoidtbl(void)
{
    struct oidtbl *op;
    OID oid;

    for (op = oidtable; op->oid_name; op++)
    {
	defineoid(op->oid_name, oid = int2oid(op->oid_value));
	oid_free(oid);
    }
}

char *
oidprint(OID oid)
{
    static char buf[BUFSIZ];
    char *cp;
    char *p;
    OID o2;
    unsigned int *ip;
    int i;

    if (oid == NULL)
	return "";

    (void)strcpy(buf, "{ ");
    cp = buf + strlen(buf);

    i = oid->oid_nelem;
    ip = oid->oid_elements;

    p = oidname(o2 = int2oid((int)*ip));
    oid_free(o2);
    if (p)
    {
	i--;
	ip++;
	(void)sprintf(cp, "%s ", p);
	cp += strlen(cp);
    }

    for (; i > 0; i--)
    {
	(void)sprintf(cp, "%d ", *ip++);
	cp += strlen(cp);
    }

    (void)strcat(cp, " }");
    return buf;
}

/*
 * look at import list and return any clue found as to handling implicit tags
 * on that type
 */
int
chkil(char *id)
{
    SYM sy;

    for (sy = symtab[TBL_IMPORT]; sy; sy = sy->sym_next)
	if (strcmp(sy->sym_name, id) == 0)
	    break;
    if (sy)
	return (sy->sym_type);

    return (ER_UNKNOWN);

}

int	oid_cmp (register OID p, register OID q)
{
    if (p == NULL)
	return (q ? -1 : 0);

    return elem_cmp (p -> oid_elements, p -> oid_nelem,
		     q -> oid_elements, q -> oid_nelem);
}

/*  */

int	elem_cmp (register unsigned int *ip, register int i, register unsigned int *jp, register int j)
{
    while (i > 0) {
	if (j == 0)
	    return 1;
	if (*ip > *jp)
	    return 1;
	else
	    if (*ip < *jp)
		return (-1);

	ip++, i--;
	jp++, j--;
    }
    return (j == 0 ? 0 : -1);
}

OID	oid_cpy (OID q)
{
     unsigned int   i,
			   *ip,
			   *jp;
     OID	oid;

    if (q == NULL)
	return NULL;
    if ((i = q -> oid_nelem) < 1)
	return NULL;
    if ((oid = (OID) malloc (sizeof *oid)) == NULL)
	return NULL;

    if ((ip = (unsigned int *) malloc ((unsigned) (i + 1) * sizeof *ip))
	    == NULL) {
	free ((char *) oid);
	return NULL;
    }

    oid -> oid_elements = ip, oid -> oid_nelem = i;

    for (i = 0, jp = q -> oid_elements; i < (unsigned)oid -> oid_nelem; i++, jp++)
	*ip++ = *jp;

    return oid;
}

void	oid_free (OID oid)
{
    if (oid == NULL)
	return;

    if (oid -> oid_elements)
	free ((char *) oid -> oid_elements);

    free ((char *) oid);
}

char   *_sprintoid (OID oid)
{
     int    i;
     unsigned int  *ip;
     char  *bp,
		   *cp;
    static char buffer[BUFSIZ];

    if (oid == NULL || oid -> oid_nelem < 1)
	return "";

    bp = buffer;

    for (ip = oid -> oid_elements, i = oid -> oid_nelem, cp = "";
	    i-- > 0;
	    ip++, cp = ".") {
	(void) sprintf (bp, "%s%u", cp, *ip);
	bp += strlen (bp);
    }

    return buffer;
}

char *
sprintb(register int v, register char *bits)
{
    register int i, j;
    register char c, *bp;
    static char buffer[BUFSIZ];

    (void) sprintf(buffer, bits && *bits == 010 ? "0%o" : "0x%x", v);
    bp = buffer + strlen(buffer);

    if (bits && *++bits)
    {
	j = 0;
	*bp++ = '<';
	while ((i = *bits++) != 0)
	    if (v & (1 << (i - 1)))
	    {
		if (j++)
		    *bp++ = ',';
		for (; (c = *bits) > 32; bits++)
		    *bp++ = c;
	    }
	    else
		for (; *bits > 32; bits++)
		    continue;
	*bp++ = '>';
	*bp = 0;
    }

    return buffer;
}
