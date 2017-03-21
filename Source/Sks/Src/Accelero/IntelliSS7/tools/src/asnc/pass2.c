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
 * LOG: Revision 6.4  2002/05/22 20:05:31  hdivoux
 * LOG: Put back generation of SS7DLLAPI (does not break compilation anymore).
 * LOG:
 * LOG: Revision 6.2  2002/03/20 20:07:48  mmiers
 * LOG: Move the ASNC library to the VFrame (as on UNIX).
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
 * LOG: Revision 1.5  1999/07/22 00:35:20  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.4  1999/04/09 21:30:43  mmiers
 * LOG:
 * LOG:
 * LOG: Remove all 218 warnings.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 18:22:55  mmiers
 * LOG: Update universal library and IS41 to use the compiler directly.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 04:31:17  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:37:00  jpakrasi
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
#include <ctype.h>
#include <string.h>
#include "asncomp.h"
#include "pass2.h"
#include "table.h"
#include "sym.h"

#ident"$Id: pass2.c,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

extern int doexternals;
extern int sflag, mflag, fflag, Cflag;

extern char *eval;

extern int Aflag;
extern SY mysymbols;
extern char *modsym(), *gfree();
extern char *my_strcat();
extern char *notidtoid();
extern char *rm_indirect(char *p);
extern char *getid(register char *p, register char *buf, register int len);
extern char *getidordot(register char *p, register char *buf, register int len);
extern char *getfield(register char *p);
extern char *sym2type(SY sy);
extern YP lookup_type();
extern MD lookup_module();

char *tab;			/* mymodule - with - changed to _ */

FILE *ffopen(char *name);

void gen_tablefile(char *inc);
void gen_typesfile(char *inc);
void gen_enctbl(FILE *fp, SY sy);
void gen_dectbl(FILE *fp, SY sy);
void gen_prnttbl(FILE *fp, SY sy);
void gen_tpe(FILE *fp);
void gen_modtype(FILE *fp, int no, int f1, int f2, int f3);
void gen_lint(FILE *fp);
int scmp(char *s1, char *s2);
void dump_ptrtab(FILE *fp);

extern void gen_dflts(FILE *fp, YP yp, char *type);
extern void out_final_defs(FILE * fp);
extern int is_stand(char *file);
extern void ferr(int, char *);
extern void ferrs(int, char *, char *);
extern void ferrd(int, char *, int);
extern void init_new_file(void);
extern void end_file(void);
extern void myyerror(char *format,...);
extern int addsptr(char *s);
extern int chkil(char *id);
extern int yyerror(char *);

extern void tdec_typ(FILE *fp, YP yp, char *id, char *type);
extern void tenc_typ(FILE *fp, YP yp, char *id, char *type);
extern void tprnt_typ(FILE *fp, YP yp, char *id, char *type);


void
peri_pass2(void)
{
    char *inc;			/* *_pre_defs.h file */

    if (!sflag)
	(void)fflush(stderr);

    tab = notidtoid(mymodule);

    if (strcmp(mymodule, "UNIV"))
	(void)lookup_module("UNIV", NULL);

    inc = my_strcat(mymodule, HFILE2);

    gen_typesfile(inc);

    gen_tablefile(inc);
}

/*
 * generate the table file which contains:
 * #include types file
 * #include - types files for other (external) modules referenced
 * definitions of data structures used: strings and stuff for defaults
 *              declaractions of functions referenced.
 *              tpe tables - one per type assignment for each of
 *                      encoding, decoding and printing
 *              tables of pointers to all the above tpe tables - one for
 *                      type of tpe table
 *              pointer table - used to hold pointers as tpe table cannot
 *                 hold pointers but only integers which index into this table
 *              module definition - the key to all the data structures os this
 *                      module. contains references to all the tables.
 *              lint declaractions for the "pepy" functions
 */
void
gen_tablefile(char *inc)
{

    int nentries;
    int encflag = 1, decflag = 1, prntflag = 1;
    SY sy;
    YP yp;
    FILE *fphh, *fptab;

    fptab = ffopen(my_strcat(mymodule, TBLNAME));	/* thing_tables.c */

    /* Only need two files <stdio.h> and our types file which includes
     * everything else we need
     * Assumption. types file in the same directory as the _tables
     */
    (void)fprintf(fptab, "#include <stdio.h>\n");
    (void)fprintf(fptab, "#include \"%s%s\"\n\n", mymodule, GENTYPES);

    (void)fprintf(fptab, "\nextern ITS_POINTER %s%s%s[];\t/* forward decl */\n",
		  PREFIX, PTR_TABNAME, tab);

    /*
     * loop through and generate all the default values definitions
     * and what ever else needs to be processed for all the entries
     * e.g. external module references and coding function declarations
     */
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	yp = sy->sy_type;
	if (yp->yp_flags & YP_IMPORTED)
	    continue;
	if (yp->yp_direction & (YP_ENCODER | YP_DECODER | YP_PRINTER)
	    || Aflag)
	{
	    gen_dflts(fptab, sy->sy_type, sy->sy_name);
	}
    }

    (void)fprintf(fptab, "\n#define OFFSET(t,f)\t((int ) &(((t *)0)->f))\n\n");
#ifndef	hpux
    (void)fprintf(fptab, "\n#define AOFFSET(t,f)\t((int ) (((t *)0)->f))\n\n");
#else
    (void)fprintf(fptab, "\n#define AOFFSET(t,f)\t((int ) &(((t *)0)->f[0]))\n\n");
#endif
    nentries = 0;
    /*
     * generate tpe tables
     */
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	yp = sy->sy_type;
	if (yp->yp_flags & YP_IMPORTED)
	    continue;
	if (yp->yp_direction & YP_ENCODER || Aflag)
	{
	    nentries++;
	    gen_enctbl(fptab, sy);
	}
    }
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	yp = sy->sy_type;
	if (yp->yp_flags & YP_IMPORTED)
	    continue;
	if (yp->yp_direction & YP_DECODER || Aflag)
	    gen_dectbl(fptab, sy);
    }

    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	yp = sy->sy_type;
	if (yp->yp_flags & YP_IMPORTED)
	    continue;
	if (yp->yp_direction & YP_PRINTER || Aflag)
	    gen_prnttbl(fptab, sy);
    }

    fphh = ffopen(inc);		/* thing_pre_defs.h */
    (void)fprintf(fphh, "\nextern SS7DLLAPI modtyp	%s%s%s;\n",
		  PREFIX, tab, MODTYP_SUFFIX);
    out_final_defs(fphh);
    if (fclose(fphh) == EOF)
    {
	(void)fprintf(stderr, "Write error to file");
	perror(inc);
	exit(1);
    }

    gen_tpe(fptab);		/* generate table of pointers to tpe tables */

    gen_modtype(fptab, nentries, encflag, decflag, prntflag);

    gen_lint(fptab);

    if (fclose(fptab) == EOF)
    {
	(void)fprintf(stderr, "Write error to file");
	perror("");
	exit(1);
    }
}

/*
 * generate the *-types.h file
 */
void
gen_typesfile(char *inc)
{
    char *buf;
#ifdef ACT_CODE
    int encflag = 1, decflag = 1, prntflag = 1;
    char *act;
    FILE *fpe, *fpd, *fpp, *fpa;
#endif
    SY sy;
    YP yp;
    FILE *fph;

    fph = ffopen(my_strcat(mymodule, HFILE1));	/* thing_defs.h */
    if (!Cflag)
    {
	if (mflag)
	{
	    (void)fprintf(fph, "#ifndef\tPEPYPATH\n");
	    (void)fprintf(fph, "#include <asn-c/%s>\n", inc);
	    (void)fprintf(fph, "#else\n");
	    (void)fprintf(fph, "#include \"%s\"\n", inc);
	    (void)fprintf(fph, "#endif\n\n\n");
	}
	else
	{
	    if (is_stand(inc))
		(void)fprintf(fph, "#include <asn-c/%s>\n", inc);
	    else
		(void)fprintf(fph, "#include \"%s\"\n", inc);
	}
    }

#ifdef ACT_CODE
    act = my_strcat(mymodule, ACTIONDEFS);

    fpe = ffopen(my_strcat(mymodule, ENCFILENAME));
    file_header(fpe, act);
    fpd = ffopen(my_strcat(mymodule, DECFILENAME));
    file_header(fpd, act);
    fpp = ffopen(my_strcat(mymodule, PRNTFILENAME));
    file_header(fpp, act);
    fpa = ffopen(act);
#endif

    /* define the macros to support posy functions */

    (void)fprintf(fph, "\n#ifndef\tlint\n");
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	eval = sy->sy_name;
	yp = sy->sy_type;

	if (sy->sy_module == NULL)
	    yyerror("no module name associated with symbol");
	if (yp->yp_flags & YP_IMPORTED)
	    continue;
	if (strcmp(sy->sy_module, mymodule))
	{
	    (void)fprintf(stderr, "mymodule unsuitable for module name e.g %s and %s(mymodule)\n", sy->sy_module, mymodule);
	    exit(1);
	}
	if (yp->yp_direction & YP_ENCODER || Aflag)
	{
	    buf = modsym(sy->sy_module, sy->sy_name, yyencdflt);
	    (void)fprintf(fph, "#define %s", buf);
	    (void)fprintf(fph, "(pe, top, len, buffer, parm) \\\n");
	    (void)fprintf(fph, "    %s(%s%s, ", ENCFNCNAME, PREFIX, proc_name(sy->sy_name, 1));
	    (void)fprintf(fph, "&%s%s%s, ", PREFIX, tab, MODTYP_SUFFIX);
	    (void)fprintf(fph, "pe, top, len, buffer, (char *) parm)\n\n");
#ifdef ACT_CODE
	    if (encflag)
	    {
		(void)fprintf(fpe, "%s%s", ENC_FNCNAME, tab);
		open_func(fpe);
		encflag--;
	    }
#endif
	    if (bflag)
		init_new_file();
	    if (bflag)
		end_file();
	}
	if (yp->yp_direction & YP_DECODER || Aflag)
	{
	    buf = modsym(sy->sy_module, sy->sy_name, yydecdflt);
	    if (bflag)
		init_new_file();
	    (void)fprintf(fph, "#define %s", buf);
	    (void)fprintf(fph, "(pe, top, len, buffer, parm) \\\n");
	    (void)fprintf(fph, "    %s(%s%s, ", DECFNCNAME, PREFIX, proc_name(sy->sy_name, 1));
	    (void)fprintf(fph, "&%s%s%s, ", PREFIX, tab, MODTYP_SUFFIX);
	    (void)fprintf(fph, "pe, top, len, buffer, (char **) parm)\n\n");
#if ACT_CODE
	    if (decflag)
	    {
		(void)fprintf(fpd, "%s%s", DEC_FNCNAME, tab);
		open_func(fpd);
		decflag--;
	    }
#endif
	    if (bflag)
		end_file();
	}
	if (yp->yp_direction & YP_PRINTER || Aflag)
	{
	    buf = modsym(sy->sy_module, sy->sy_name, yyprfdflt);
	    if (bflag)
		init_new_file();
	    (void)fprintf(fph, "#define %s", buf);
	    (void)fprintf(fph, "(pe, top, len, buffer, parm) \\\n");
	    (void)fprintf(fph, "    %s(%s%s, ", PRNTFNCNAME, PREFIX, proc_name(sy->sy_name, 1));
	    (void)fprintf(fph, "&%s%s%s, ", PREFIX, tab, MODTYP_SUFFIX);
	    (void)fprintf(fph, "pe, top, len, buffer)\n");
	    (void)fprintf(fph, "#define %s_P", buf);
	    (void)fprintf(fph, "    %s%s, ", PREFIX,
			  proc_name(sy->sy_name, 1));
	    (void)fprintf(fph, "&%s%s%s\n\n", PREFIX, tab, MODTYP_SUFFIX);
#ifdef  ACT_CODE
	    if (prntflag)
	    {
		(void)fprintf(fpp, "%s%s", PRNT_FNCNAME, tab);
		open_func(fpp);
		prntflag--;
	    }
#endif
	    if (bflag)
		end_file();
	}
	if (!bflag && ferror(stdout))
	    myyerror("write error - %s", strerror(errno));
    }
    (void)fprintf(fph, "\n#endif   /* lint */\n");

#ifdef	ACT_CODE
    if (!encflag)
    {
	close_func(fpe);
    }
    if (!decflag)
    {
	close_func(fpd);
    }
    if (!prntflag)
    {
	close_func(fpp);
    }
#endif

    if (fclose(fph) == EOF)
    {
	(void)fprintf(stderr, "Write error to file");
	perror("");
	exit(1);
    }
#ifdef	ACT_CODE
    fclose(fpe);
    fclose(fpd);
    fclose(fpp);
    fclose(fpa);
#endif
}

void
gen_enctbl(FILE *fp, SY sy)
{
    YP yp;

    yp = sy->sy_type;
    (void)fprintf(fp, "static ptpe %s%s[] = {\n", ETABLE, proc_name(sy->sy_name, 0));
    (void)fprintf(fp, "\t{ PE_START, 0, 0, 0, (char **)&%s%s%s[%d] },\n",
		  PREFIX, PTR_TABNAME, tab, addsptr(sy->sy_name));

    tenc_typ(fp, yp, sy->sy_name, NULL);

    (void)fprintf(fp, "\t{ PE_END, 0, 0, 0, (char **)&%s%s%s[%d] }\n",
		  PREFIX, PTR_TABNAME, tab, addsptr(sy->sy_name));
    (void)fprintf(fp, "\t};\n");
    (void)fprintf(fp, "\n");
}

void
gen_dectbl(FILE *fp, SY sy)
{
    (void)fprintf(fp, "static ptpe %s%s[] = {\n", DTABLE, proc_name(sy->sy_name, 0));
    (void)fprintf(fp, "\t{ PE_START, 0, 0, 0, (char **)&%s%s%s[%d] },\n",
		  PREFIX, PTR_TABNAME, tab, addsptr(sy->sy_name));

    tdec_typ(fp, sy->sy_type, sy->sy_name, NULL);

    (void)fprintf(fp, "\t{ PE_END, 0, 0, 0, (char **)&%s%s%s[%d] }\n",
		  PREFIX, PTR_TABNAME, tab, addsptr(sy->sy_name));
    (void)fprintf(fp, "\t};\n");
    (void)fprintf(fp, "\n");
}

void
gen_prnttbl(FILE *fp, SY sy)
{
    (void)fprintf(fp, "static ptpe %s%s[] = {\n", PTABLE, proc_name(sy->sy_name, 0));
    (void)fprintf(fp, "\t{ PE_START, 0, 0, 0, (char **)&%s%s%s[%d] },\n",
		  PREFIX, PTR_TABNAME, tab, addsptr(sy->sy_name));

    tprnt_typ(fp, sy->sy_type, sy->sy_name, NULL);

    (void)fprintf(fp, "\t{ PE_END, 0, 0, 0, (char **)&%s%s%s[%d] }\n",
		  PREFIX, PTR_TABNAME, tab, addsptr(sy->sy_name));
    (void)fprintf(fp, "\t};\n");
    (void)fprintf(fp, "\n");
}


/*
 * define the tpe index tables and the pointer table
 */
void
gen_tpe(FILE *fp)
{
    SY sy;
    int empty = 1;

    (void)fprintf(fp, "static ptpe *etabl[] = {\n");
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	if (sy->sy_type->yp_flags & YP_IMPORTED)
	    continue;
	if (sy->sy_type->yp_direction & YP_ENCODER || Aflag)
	{
	    (void)fprintf(fp, "\t%s%s,\n", ETABLE, proc_name(sy->sy_name, 0));
	    empty = 0;
	}
    }
    if (empty)
	(void)fprintf(fp, "\t0,\n");
    (void)fprintf(fp, "\t};\n\n");
    empty = 1;

    (void)fprintf(fp, "static ptpe *dtabl[] = {\n");
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	if (sy->sy_type->yp_flags & YP_IMPORTED)
	    continue;
	if (sy->sy_type->yp_direction & YP_DECODER || Aflag)
	{
	    (void)fprintf(fp, "\t%s%s,\n", DTABLE, proc_name(sy->sy_name, 0));
	    empty = 0;
	}
    }
    if (empty)
	(void)fprintf(fp, "\t0,\n");
    (void)fprintf(fp, "\t};\n\n");
    empty = 1;

    (void)fprintf(fp, "static ptpe *ptabl[] = {\n");
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	if (sy->sy_type->yp_flags & YP_IMPORTED)
	    continue;
	if (sy->sy_type->yp_direction & YP_PRINTER || Aflag)
	{
	    (void)fprintf(fp, "\t%s%s,\n", PTABLE, proc_name(sy->sy_name, 0));
	    empty = 0;
	}
    }
    if (empty)
	(void)fprintf(fp, "\t0,\n");
    (void)fprintf(fp, "\t};\n\n");

    /* produce pointer table */
    dump_ptrtab(fp);
}

/*
 * output the module structure for this module
 */
void
gen_modtype(FILE *fp, int no, int f1, int f2, int f3)
{
    if (!f1)
	(void)fprintf(fp, "extern PE\t%s%s();\n", ENC_FNCNAME, tab);
    if (!f2)
	(void)fprintf(fp, "extern PE\t%s%s();\n", DEC_FNCNAME, tab);
    if (!f3)
	(void)fprintf(fp, "extern PE\t%s%s();\n", PRNT_FNCNAME, tab);
    (void)fprintf(fp, "\n");
    (void)fprintf(fp, "SS7DLLAPI modtyp %s%s%s = {\n", PREFIX, tab, MODTYP_SUFFIX);
    (void)fprintf(fp, "\t\"%s\",\n", mymodule);		/* name */
    (void)fprintf(fp, "\t%d,\n", no);	/* number of entries */
    /* coding tables */
    (void)fprintf(fp, "\tetabl,\n");
    (void)fprintf(fp, "\tdtabl,\n");
    (void)fprintf(fp, "\tptabl,\n");
    /* action tables */
    (void)fprintf(fp, "\t0,\n");	/* no action code */
    (void)fprintf(fp, "\t0,\n");	/* no action code */
    (void)fprintf(fp, "\t0,\n");	/* no action code */

    (void)fprintf(fp, "\t%s%s%s,\n", PREFIX, PTR_TABNAME, tab);
    (void)fprintf(fp, "\t};\n\n");
}

/*
 * open a file called name
 */
FILE *
ffopen(char *name)
{
    FILE *fp;

    if ((fp = fopen(name, "w")) == NULL)
    {
	(void)fprintf(stderr, "Can't create the file %s", name);
	exit(1);
    }
    return fp;
}

#ifdef ACT_CODE
/*
 * output the file prologue to the file specified by fp
 */
file_header(fp, act)
     FILE *fp;
     char *act;
{
    (void)fprintf(fp, "#include %s\n", PSAP_DOT_H);
    (void)fprintf(fp, "#include \"%s\"\n", INCFILE1);
    (void)fprintf(fp, "#include \"%s\"\n", act);
    (void)fprintf(fp, "#include \"%s%s\"\n\n", mymodule, GENTYPES);
    (void)fprintf(fp, "#ifndef PEPYPARM\n");
    (void)fprintf(fp, "#define PEPYPARM char *\n");
    (void)fprintf(fp, "#endif\n");
    (void)fprintf(fp, "extern PEPYPARM NullParm;\n\n");
}

#endif

/*
 * output the function prologue to the file specified by fp
 */
void
open_func(FILE *fp)
{

    (void)fprintf(fp, "(pe, parm, p, mod)\n");
    (void)fprintf(fp, "PE\tpe;\n");
    (void)fprintf(fp, "PEPYPARM\tparm;\n");
    (void)fprintf(fp, "ptpe\t*p;\n");
    (void)fprintf(fp, "modtyp\t*mod;\n");
    (void)fprintf(fp, "{\n");
    /* action 0 ???? */
    (void)fprintf(fp, "\tswitch (p->pe_ucode) {\n");
}

/*
 * output the function epilogue to the file specified by fp
 */
void
close_func(FILE *fp)
{
    (void)fprintf(fp, "\t\tdefault:\n");
    (void)fprintf(fp, "\t\t\tbreak;\n");
    (void)fprintf(fp, "\t}\n");
    (void)fprintf(fp, "\treturn OK;\n}\n\n");
}

/*
 * print the table id_table
 */
void
print_table(void)
{
    int i;
    id_entry *t;

    for (i = 0; i < TABLESIZE; i++)
    {
	for (t = id_table[i]; t != NULL; t = t->next)
	    (void)printf("%s(%d) -->   ", t->r_value, t->def_value);
	if (id_table[i] != NULL)
	    (void)printf("NULL -- %d\n", i);
    }
}
static struct univ_typ univ_tab[] =
{
    {"EXTERNAL", "struct	type_UNIV_EXTERNAL	*", "EXTERNAL", 8, 0,
     "UNIV", UNF_EXTMOD | UNF_HASDATA, YP_SEQLIST,},
    {"GeneralString", "struct	qbuf	*", "OCTETSTRING", 27, 0,
     "UNIV", 0, YP_OCT,},
    {"GeneralisedTime", "struct	qbuf	*", "OCTETSTRING", 24, 0,
     "UNIV", 0, YP_OCT,},
    {"GeneralizedTime", "struct	qbuf	*", "OCTETSTRING", 24, 0,
     "UNIV", 0, YP_OCT,},
    {"GraphicString", "struct	qbuf	*", "OCTETSTRING", 25, 0,
     "UNIV", 0, YP_OCT,},
    {"IA5String", "struct	qbuf	*", "OCTETSTRING", 22, 0,
     "UNIV", 0, YP_OCT,},
    {"ISO646String", "struct	qbuf	*", "OCTETSTRING", 26, 0,
     "UNIV", 0, YP_OCT,},
    {"NumericString", "struct	qbuf	*", "OCTETSTRING", 18, 0,
     "UNIV", 0, YP_OCT,},
    {"PrintableString", "struct	qbuf	*", "OCTETSTRING", 19, 0,
     "UNIV", 0, YP_OCT,},
    {"TeletexString", "struct	qbuf	*", "OCTETSTRING", 20, 0,
     "UNIV", 0, YP_OCT,},
    {"T61String", "struct	qbuf	*", "OCTETSTRING", 20, 0,
     "UNIV", 0, YP_OCT,},
    {"UTCTime", "struct	qbuf	*", "OCTETSTRING", 23, 0,
     "UNIV", 0, YP_OCT,},
    {"UniversalTime", "struct	qbuf	*", "OCTETSTRING", 23, 0,
     "UNIV", 0, YP_OCT,},
    {"VideotexString", "struct	qbuf	*", "OCTETSTRING", 21, 0,
     "UNIV", 0, YP_OCT,},
    {"VisibleString", "struct	qbuf	*", "OCTETSTRING", 26, 0,
     "UNIV", 0, YP_OCT,},
};

extern struct univ_typ *simptyp();

/*
 * Determine wether the type name matches one of the Universal types
 * which are to be treated specially. If so return a pointer to the
 * data structure which contains the parameters describing how it
 * should be processed
 */
struct univ_typ *
univtyp(char *name)
{
    int low, high, i;
    struct univ_typ *p;

    low = 0;
    high = NENTRIES(univ_tab) - 1;
    while (low <= high)
    {
	p = univ_tab + (low + high) / 2;
	if ((i = scmp(name, p->univ_name)) == 0)
	    return (p);
	if (low == high)
	    return (NULL);
	if (i < 0)
	    high = p - univ_tab - 1;
	else
	    low = p - univ_tab + 1;
    }

#if OPTIMISED
    if ((p = simptyp(name)) == NULL)
	return (p);
#endif

    return (NULL);
}

/*
 * Compare two strings returning a number representing the character
 * where they differ or 0 if are the same - I wrote this because I
 * couldn't trust strcmp to work the same way between numbers and
 * letters everywhere. longer strings are greater shorter strings
 * numbers are greater then all letters lower case are greater then
 * upper case There must be a better way !
 */
int
scmp(char *s1, char *s2)
{
    while (*s1 == *s2 && *s2)
	s1++, s2++;
    if (*s1 == '\0' && *s2 == '\0')
	return (0);
    if (*s1 == '\0')
	return (-1);
    if (*s2 == '\0')
	return (1);
    if (isalpha(*s1) && isalpha(*s2))
    {
	if (isupper(*s1) && isupper(*s2))
	    return (*s1 - *s2);
	if (islower(*s1) && islower(*s1))
	    return (*s1 - *s2);
	if (isupper(*s1))
	    return (-1);
	if (islower(*s1))
	    return (1);
    }
    if (isdigit(*s1) && isdigit(*s2))
	return (*s1 - *s2);
    if (isdigit(*s1))
	return (1);
    if (isdigit(*s2))
	return (-1);
    return (*s1 - *s2);
}

/*
 * lookup a symbol and return a pointer to it
 */
SY
syfind(char *name)
{
    SY sy;

    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	if (sy->sy_type->yp_flags & YP_IMPORTED)
	    continue;
	if (strcmp(name, sy->sy_name) == 0)
	    return (sy);
    }
    return (NULL);
}
#if OPTIMISED
/*
 * determine if the symbol is a simple type that is optimised
 */
struct univ_typ *
simptyp(yp)
     YP yp;
{
    struct univ_typ *p;

    static struct univ_typ bitstring =
    {"Bitstring", "struct	PElement	*", "BITSTRING", 3, 0}, octetstring =
    {"GeneralString", "struct	qbuf	*", "OCTETSTRING", 4, 0}, oid =
    {"Object Identifier", "struct	OIDentifier	*", "OBJIDENT", 6, 0}, obj =
    {"Module", "struct	OIDentifier	*",
     "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", 27, 0};

#define MSTRING 30		/* number of Xs in the above string */

    switch (yp->yp_code)
    {
    case YP_BIT:
    case YP_BITLIST:
	return (&bitstring);

    case YP_SEQ:
    case YP_SET:
    case YP_ANY:
	return (&bitstring);

    case YP_OCT:
	return (&octetstring);

    case YP_OID:
	return (&oid);

    case YP_IDEFINED:
	(void)strncpy(p->univ_tab, yp->yp_identifier, MSTRING);
	return (&obj);


    case YP_SEQLIST:
    case YP_SETLIST:
    case YP_CHOICE:

    default:
	return (NULL);
    }
}
#endif

/*
 * lookup a type name until you get something that is not a name
 */
YP
lkup(YP yp)
{
    YP yp1;

    if (yp == NULL)
	return (yp);

    while (yp->yp_code == YP_IDEFINED)
    {
	if ((yp1 = lookup_type(yp->yp_module, yp->yp_identifier)) == NULL)
	    return (yp);
	yp = yp1;
    }

    return (yp);
}
/*
 * compute the type of tag it should be given the tag and the type it is
 * being applied to
 */
int
comptag(int tag, YP yp)
{
    static int warned = 0;
    YP yp1;
    struct univ_typ *p;
    int code;

    if (tag == 0)
	return (0);

    yp1 = lkup(yp);

    if (yp1->yp_code == YP_IDEFINED)
    {
	if ((p = univtyp(yp1->yp_identifier)) == NULL
	    || p->univ_type <= YP_UNDF)
	{
	    switch (chkil(yp1->yp_identifier))
	    {
	    case ER_NORMAL:
		return (tag);

	    case ER_EXPLICIT:
		return (0);

	    default:
		break;
	    }

	    if (warned++ <= 3)
	    {
		ferrs(0, "\ncomptag:warning implicit tag of unknown type %s\n",
		      yp1->yp_identifier);
		ferr(0, "\tcomptag:treated as implicit\n");
	    }
	    return (tag);
	}
	code = p->univ_type;
    }
    else
    {
	code = yp1->yp_code;
	if (code == YP_ANY && yp1->yp_flags & YP_WANTIMPLICIT)
	    return (tag);
    }

    if (code == YP_CHOICE || code == YP_ANY)
	return (0);

    return (tag);
}

/*
 * Generate function definitions for all the macros so that lint
 * can type check all their uses
 */
void
gen_lint(FILE *fp)
{
    char *buf;
    SY sy;
    YP yp;

    (void)fprintf(fp, "\n#if\tdefined(lint) || defined(PEPSY_LINKABLE_FUNCS)\n");
    for (sy = mysymbols; sy; sy = sy->sy_next)
    {
	eval = sy->sy_name;
	yp = sy->sy_type;

	if (sy->sy_module == NULL)
	    yyerror("no module name associated with symbol");
	if (yp->yp_flags & YP_IMPORTED)
	    continue;
	if (strcmp(sy->sy_module, mymodule))
	{
	    (void)fprintf(stderr,
	       "mymodule unsuitable for module name e.g %s and %s(mymodule)\n",
			  sy->sy_module, mymodule);
	    exit(1);
	}
	if (yysection & YP_ENCODER)
	{
	    /* Encoding routine */
	    buf = modsym(sy->sy_module, sy->sy_name, yyencdflt);
	    (void)fprintf(fp, "\n#undef %s\n", buf);
	    (void)fprintf(fp, "int	%s", buf);
	    (void)fprintf(fp, "(pe, top, len, buffer, parm)\n");
	    (void)fprintf(fp, "PE     *pe;\n");
	    (void)fprintf(fp, "int\ttop,\n\tlen;\n");
	    (void)fprintf(fp, "char   *buffer;\n");
	    (void)fprintf(fp, "%s *parm;\n", sym2type(sy));
	    (void)fprintf(fp, "{\n  return (%s(%s%s, ",
			  ENCFNCNAME, PREFIX, proc_name(sy->sy_name, 1));
	    (void)fprintf(fp, "&%s%s%s, ", PREFIX, tab, MODTYP_SUFFIX);
	    (void)fprintf(fp, "pe, top, len, buffer,\n\t\t(char *) parm));\n}\n");
	}

	if (yysection & YP_DECODER)
	{
	    /* Decoding routine */
	    buf = modsym(sy->sy_module, sy->sy_name, yydecdflt);
	    (void)fprintf(fp, "\n#undef %s\n", buf);
	    (void)fprintf(fp, "int	%s", buf);
	    (void)fprintf(fp, "(pe, top, len, buffer, parm)\n");
	    (void)fprintf(fp, "PE\tpe;\n");
	    (void)fprintf(fp, "int\ttop,\n       *len;\n");
	    (void)fprintf(fp, "char  **buffer;\n");
	    (void)fprintf(fp, "%s **parm;\n", sym2type(sy));
	    (void)fprintf(fp, "{\n  return (%s(%s%s, ",
			  DECFNCNAME, PREFIX, proc_name(sy->sy_name, 1));
	    (void)fprintf(fp, "&%s%s%s, ", PREFIX, tab, MODTYP_SUFFIX);
	    (void)fprintf(fp, "pe, top, len, buffer,\n\t\t(char **) parm));\n}\n");
	}

	if (yysection & YP_PRINTER)
	{
	    /* Printing routine */
	    buf = modsym(sy->sy_module, sy->sy_name, yyprfdflt);
	    (void)fprintf(fp, "\n#undef %s\n/* ARGSUSED */\n", buf);
	    (void)fprintf(fp, "int	%s", buf);
	    (void)fprintf(fp, "(pe, top, len, buffer, parm)\n");
	    (void)fprintf(fp, "PE\tpe;\n");
	    (void)fprintf(fp, "int\ttop,\n       *len;\n");
	    (void)fprintf(fp, "char  **buffer;\n");
	    (void)fprintf(fp, "%s *parm;\n", sym2type(sy));
	    (void)fprintf(fp, "{\n  return (%s(%s%s, ",
			  PRNTFNCNAME, PREFIX, proc_name(sy->sy_name, 1));
	    (void)fprintf(fp, "&%s%s%s, ", PREFIX, tab, MODTYP_SUFFIX);
	    (void)fprintf(fp, "pe, top, len, buffer));\n}\n");
	}

	if (!fflag)
	    continue;

	switch (yp->yp_code)
	{
	    /* see do_struct1 in pepsy.c for this list */
	case YP_BIT:
	case YP_BITLIST:
	case YP_SEQ:
	case YP_SET:
	case YP_ANY:

	case YP_OCT:
	case YP_OID:
	    continue;		/* these are all #defined... */
	}

	/* Free routine */
	buf = modsym(sy->sy_module, sy->sy_name, "free");
	(void)fprintf(fp, "\n#undef %s\n", buf);
	(void)fprintf(fp, "void %s(val)\n", buf);
	(void)fprintf(fp, "%s *val;\n", sym2type(sy));
	(void)fprintf(fp, "{\n");
	(void)fprintf(fp, "%s;\n", gfree(sy->sy_module, sy->sy_name, "val"));
	(void)fprintf(fp, "}\n");

    }

    (void)fprintf(fp, "\n#endif\t/* lint||PEPSY_LINKABLE_FUNCS */\n");

    if (ferror(fp))
	myyerror("write error - %s", strerror(errno));
}

/*
 * pointer table support routines
 */
static char **ptr_tab;		/* reference of the pointer */
static int ptr_cnt = 0;
static int ptr_max = 0;
/*
 * add the given pointer to the pointer table and return its index
 */
int
addptr(char *p)
{
    int ind;
    register int i;
    register char *s;

    /*
     * try to eliminate common pointers by returning a ponter if it matches
     * previously
     */
    for (i = 0; i < ptr_cnt; i++)
	if (strcmp(p, ptr_tab[i]) == 0)
	    return (i);

    if (ptr_max <= ptr_cnt)
    {
	if (ptr_max == 0)
	    ptr_tab = (char **)malloc((unsigned)sizeof(char **) * (ptr_max = 100));
	else
	    ptr_tab = (char **)realloc((char *)ptr_tab, (unsigned)sizeof(char **) * (ptr_max *= 2));
    }
    if (ptr_tab == NULL)
    {
	(void)fprintf(stderr, "\npointer table out of memeory (%d needed)\n",
		      ptr_cnt);
	exit(1);
    }

    if ((s = malloc((unsigned)(strlen(p) + 1))) == NULL)
    {
	(void)fprintf(stderr, "\naddptr:out of memory\n");
	exit(1);
    }
    (void)strcpy(s, p);

    ptr_tab[ind = ptr_cnt++] = s;

    return (ind);
}

void
dump_ptrtab(FILE *fp)
{
    int i;


    (void)fprintf(fp, "\n/* Pointer table %d entries */\n", ptr_cnt);

#ifdef PUT_PEPSY_STATIC_BACK
    /* 
       Appears to be valid ANSI and K&R c, but gives some compilers 
       a real hard time.  So leave it out, unless really needed.
     */

    (void)fprintf(fp, "static ITS_POINTER %s%s%s[] = {\n", PREFIX, PTR_TABNAME, tab);
#else

    (void)fprintf(fp, "ITS_POINTER %s%s%s[] = {\n", PREFIX, PTR_TABNAME, tab);
#endif

    for (i = 0; i < ptr_cnt; i++)
	(void)fprintf(fp, "    (ITS_POINTER) %s,\n", ptr_tab[i]);

    if (ptr_cnt <= 0)
	(void)fprintf(fp, "    (ITS_POINTER) 0,\n");	/* for fussy C compilers */

    (void)fprintf(fp, "};\n");
}

/*
 * routines to parse and analyse C types to support the pepy-like extensions
 * of pepsy
 */

/*
 * remove a level of indirection from the given type. If possible. if not
 * return NULL, otherwise return the new type in a temporary buffer
 */
char *
rm_indirect(char *p)
{
    static char buf[STRSIZE];
    int i;

    if (p == NULL || *p == '\0' || (i = strlen(p)) >= STRSIZE)
	return (NULL);

    (void)strncpy(buf, p, STRSIZE);

    for (; i >= 0; i--)
    {
	if (buf[i] == '*')
	{
	    buf[i] = '\0';
	    return (buf);
	}
    }

    return (NULL);

}

/*
 * extract the field from the C arguement and the following constant
 * expression for the bit number. 
 * if it fails return NULL
 */
char *
getfldbit(register char *p, char **pstr)
{
    static char buf[STRSIZE];

    if (p == NULL || pstr == (char **)0)
	return (NULL);

    if ((p = getidordot(p, buf, STRSIZE)) == NULL)
	return (NULL);

    while (*p && isspace(*p))
	p++;

    if (*p != '$')
    {				/* must be a -> */

	if (strncmp(p, "->", 2) != 0)
	    return (NULL);

	p += 2;

	if ((p = getidordot(p, buf, STRSIZE)) == NULL)
	    return (NULL);

	while (*p && isspace(*p))
	    p++;

	if (*p != '$')
	    return (NULL);
    }

    *pstr = p + 1;		/* have to leave it up to the compiler to verify the
				 * constant expression for the bit number
				 */
    return (buf);
}

/* return a pointer after the current batch of white space if any */
char *
skipspace(char *p)
{
    if (p == NULL)
	return (NULL);

    while (*p && isspace(*p))
	p++;

    return (p);
}

/*
 * extract the field from the C arguement and return it in a static buffer
 * else return NULL
 */
char *
getfield(register char *p)
{
    static char buf[STRSIZE];
    char *buf1;

    if (p == NULL)
	return (NULL);

    while (*p && isspace(*p))
	p++;

    if (*p == '*')		/* to support *parm field */
	return (p);

    if ((p = getidordot(p, buf, STRSIZE)) == NULL)
	return (NULL);

    while (*p && isspace(*p))
	p++;

    if (*p == '\0')
	return (buf);

    if (strncmp(p, "->", 2) != 0)
	return (NULL);

    p += 2;

    /* if we have an & keep it on the field */
    if (*buf == '&')
	buf1 = buf + 1;
    else
	buf1 = buf;

    if ((p = getidordot(p, buf1, STRSIZE)) == NULL)
	return (NULL);

    while (*p && isspace(*p))
	p++;

    if (*p == '\0')
	return (buf);

    return (NULL);
}

/*
 * get an identifier into the given buffer [A-Za-z_] are legal chars
 */
char *
getid(register char *p, register char *buf, register int len)
{
    char *fbuf;

    fbuf = buf;

    while (*p && isspace(*p))
	p++;

    while (*p && (isalnum(*p) || *p == '_'))
    {
	if (len-- >= 0)
	    *buf++ = *p;
	p++;
    }

    if (fbuf == buf)
	return (NULL);

    *buf = '\0';

    return (p);

}

/*
 * get an identifier into the given buffer - '.' are considered part of an 
 * identifier - should really be called get field reference
 */
char *
getidordot(register char *p, register char *buf, register int len)
{
    char *fbuf;

    fbuf = buf;

    while (*p && isspace(*p))
	p++;

    if (*p == '&')
    {
	len--;
	*buf++ = *p++;

	while (*p && isspace(*p))
	    p++;
    }

    while (*p && (isalnum(*p) || *p == '_' || *p == '.'))
    {
	if (len-- >= 0)
	    *buf++ = *p;
	p++;
    }

    if (fbuf == buf)
	return (NULL);

    *buf = '\0';

    return (p);

}
static char *noindstr[] =
{
    "*", "*parm", "&", "&parm",
    NULL
};

/*
 * determine if the given field means no indirection wanted and so return 1
 * else return 0
 */
int
noindirect(char *f)
{
    char *p, **ps;
    int l;

    if (f == NULL)
	return (1);

    f = skipspace(f);

    if (f == NULL)
	return (1);

    if (*f == '&')
	return (1);

    for (p = f; *p && !isspace(*p); p++)
	;
    l = p - f;

    for (ps = noindstr; *ps; ps++)
	if (l == (int)strlen(*ps) && strncmp(f, *ps, l) == 0)
	    return (1);

    return (0);
}

/*
 * process the T - the Type and field specifier
 * the given YP to the appropriate values for VALTYPE string
 * Namely the yp_parm_type to contain the (Parameter) type string.
 * then if there is a $ the yp_parm to the part after the $, the field
 */
int
setvaltype(YP yp, char *str)
{
    char *p;

    if (str == NULL || *(str = skipspace(str)) == '\0')
	return (0);

    if ((p = strchr(str, '$')) != NULL)
    {
	*p++ = '\0';
	p = skipspace(p);
	yp->yp_parm = strdup(p);
	yp->yp_flags |= YP_PARMVAL;
    }

    yp->yp_param_type = strdup(str);

    return (1);

}

/*
 * produce a temporary copy of the type specified in the ParameterType
 * specification
 * i.e. a [[ P type ]] specification
 */
char *
partyp2str(YP yp)
{
    char *p;

    if (yp->yp_param_type == NULL)
    {
	(void)fprintf(stderr, "\npartyp2str no param_type field\n");
	exit(1);
    }

    if ((p = rm_indirect(yp->yp_param_type)) == NULL)
    {
	(void)fprintf(stderr, "\npartyp2str can't extract direct type from %s\n",
		      yp->yp_param_type);
	exit(1);
    }

    return (p);
}
/*
 * produce a string giving the type of a symbol, in a static buffer
 */
char *
sym2type(SY sy)
{
    static char buffer[STRSIZE];

    if (sy->sy_type && sy->sy_type->yp_param_type)
	return (partyp2str(sy->sy_type));

    (void)sprintf(buffer, "struct %s", modsym(sy->sy_module, sy->sy_name, "type"));

    return (buffer);
}

char *
genstrform(YP yp)
{
    char *s;
    int pindex;
    static char genbuf[BUFSIZ];

    if ((s = yp->yp_id) == NULL)
    {
	if ((s = yp->yp_identifier) == NULL)
	    return "NULL";

	if (yp->yp_code == YP_IDEFINED &&
	    yp->yp_module != NULL &&
	    strcmp(yp->yp_module, mymodule) != 0)
	{
	    (void)sprintf(genbuf, "%s.%s", yp->yp_module, s);
	    s = genbuf;
	}
    }
    pindex = addsptr(s);
    (void)sprintf(genbuf, "(char **)&%s%s%s[%d]",
		  PREFIX, PTR_TABNAME, tab, pindex);
    return genbuf;
}
