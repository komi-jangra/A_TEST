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
 * LOG: Revision 3.1  2000/08/16 00:07:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:30:05  mmiers
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
 * LOG: Revision 1.3  1998/10/21 19:20:20  mmiers
 * LOG: Update for ALPHA build.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 18:22:55  mmiers
 * LOG: Update universal library and IS41 to use the compiler directly.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:37:00  jpakrasi
 * LOG: Build pepsy on NT.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#ifndef PASS2_H
#define PASS2_H

#if defined(WIN32)
#pragma warning(disable:4274)
#endif

#ident "$Id: pass2.h,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

/*.interface
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Usage:
 *      None.
 ****************************************************************************/

/* Change the version number only important features change - so people can
 * #ifdef on the version number. Also used to provide backwards compatible
 * macro definitions for posy/pepy.
 */
#define PEPSY_VERSION_NUMBER	2
#define NBPC	8		/* Number of Bits per character - machine dependant */
#define NBPI	sizeof (int)*NBPC	/* Number of bits per integer */

#define PSAP_DOT_H	"\"AsnC.h\""
#define I_PSAP_DOT_H	"<asn-c/AsnC.h>"
#define UNIV_TYPES_DOT_H	"\"UNIV-types.h\""
#define I_UNIV_TYPES_DOT_H	"<asn-c/UNIV-types.h>"
#define	HFILE1	"_defs.h"
#define HFILE2	"_pre_defs.h"
#define ACTIONDEFS	"_action.h"

#define GENTYPES	"-types.h"
#define INCFILE1	"AsnC.h"

#define	ACT1	"_act1"
#define	ACT2	"_act2"
#define	ACT3	"_act3"
#define	ACT4	"_act4"
#define	ACT05	"_act05"

#define PREFIX	"_Z"

#define ETABLE	"et_"
#define DTABLE	"dt_"
#define PTABLE	"pt_"

#define	ENCFNCNAME	"enc_f"
#define	DECFNCNAME	"dec_f"
#define	PRNTFNCNAME	"prnt_f"

#define	ENC_FNCNAME	"enc_f_"
#define	DEC_FNCNAME	"dec_f_"
#define	PRNT_FNCNAME	"prnt_f_"

#define	ENCFILENAME	"_enc.c"
#define	DECFILENAME	"_dec.c"
#define	PRNTFILENAME	"_prnt.c"

#define TBLNAME		"_tables.c"
#define MODTYP_SUFFIX	"_mod"

#define MAXPTRS		200	/* maximum number of pointers in pointer table */

#define PTR_TABNAME	"ptrtab"
extern int p_debug;

#define DEB 1

#ifdef DEB
#define Printf(x, y) if (x <= p_debug) printf y
#else
#define Printf(x, y)
#endif

/*
 * info for handling a Universal type
 */
struct univ_typ
{
    char *univ_name;		/* Name of this Universal type */
    char *univ_data;		/* type to generate for it */
    char *univ_tab;		/* type of table entry it needs */
    PElementID univ_id;		/* tag of the type */
    PElementClass univ_class;	/* class - probably Universal primative */
    char *univ_mod;		/* Name of its module if it has one  */
    int univ_flags;		/* Information about entry */
    int univ_type;		/* Type we can use for its contents */
#define UNF_EXTMOD	1	/* Use an external module reference */
#define UNF_HASDATA	2	/* Has data structure - allocate data for it */
};

extern struct univ_typ *univtyp(char *name);

/* How many entries in an array */
#define NENTRIES(x)	(sizeof (x)/sizeof ((x)[0]))

/* used to specify which tables a routine is to generate */
#define G_ENC	0		/* encoding */
#define G_DEC	1		/* decoding */
#define G_PNT	2		/* printing */

#define	hflag	(options[0])
#define	Hflag	(options[1])
#define h2flag	(options[2])
#define	NOPTIONS	3
extern int options[];

#define STRSIZE 128		/* general buffer size */

extern char *proc_name(char *t, int flag);

extern char *getfield(register char *p), *getfldbit(register char *p, char **pstr);
extern char *class2str(PElementClass cl);

extern int gen_ventry(FILE *fp, YP oyp, YP yp, char *t, char *f);	/* generate a Value Passing Entry */
extern int gen_fnentry(FILE *fp, YP oyp, YP yp, char *fn, char *dummy);	/* generate a function calling entry */
extern char *int2tstr(int i);	/* integer to temporary string */

extern char *getfield(register char *p), *getfldbit(register char *p, char **pstr);
extern char *class2str(PElementClass cl);

#endif /* XXX_XXX_X */
