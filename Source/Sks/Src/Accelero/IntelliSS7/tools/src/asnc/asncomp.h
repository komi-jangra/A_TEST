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
 * LOG: Revision 3.2  2001/03/06 15:59:50  mmiers
 * LOG: Versioning.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:07:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:29:59  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/07/22 00:35:18  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.7  1999/04/21 19:33:38  mmiers
 * LOG:
 * LOG:
 * LOG: Minor tweaks here and there.
 * LOG:
 * LOG: Revision 1.6  1998/10/26 20:29:43  mmiers
 * LOG: #include <errno.h>
 * LOG:
 * LOG: Revision 1.5  1998/10/26 15:29:19  mmiers
 * LOG: symbol collision avoidance.
 * LOG:
 * LOG: Revision 1.4  1998/10/21 19:40:08  mmiers
 * LOG: Fix HPUX build.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 18:22:53  mmiers
 * LOG: Update universal library and IS41 to use the compiler directly.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 04:31:12  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:36:57  jpakrasi
 * LOG: Build pepsy on NT.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#ifndef ASN_COMP_H
#define ASN_COMP_H

#if defined(WIN32)
#pragma warning(disable:4274)
#endif

#ident "$Id: asncomp.h,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

/*.interface
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Usage:
 *      None.
 ****************************************************************************/

#define ASN_COMPILER_BUILD

#include <asn-c/AsnC.h>

#include <errno.h>

#define ASNC_VERSION    "1.0"

struct tuple
{
    int t_type;
    char *t_class;
    char *t_form;
    char *t_id;
    int t_classnum;
    int t_idnum;
};

typedef struct ypv
{
    int yv_code;
#define	YV_UNDF		0x00	/* ??? */
#define	YV_NUMBER	0x01	/* LITNUMBER */
#define	YV_BOOL		0x02	/* TRUE | FALSE */
#define	YV_STRING	0x03	/* LITSTRING */
#define	YV_IDEFINED	0x04	/* ID */
#define	YV_IDLIST	0x05	/* IdentifierList */
#define	YV_VALIST	0x06	/* { Values } */
#define	YV_NULL		0x07	/* NULL */
#define YV_ABSENT	0x08	/* WITH COMPONENTS .. ABSENT */
#define YV_PRESENT	0x09	/*  "     "          .. PRESENT */
#define YV_INCLUDES	0x0a	/* INCLUDES ... */
#define YV_WITHCOMPS	0x0b	/* WITH COMPONENTS */
#define	YV_OIDLIST	0x0c	/* { object identifier } */
#define YV_REAL		0x0d	/* real value */
#define YV_HSTRING	0x0e	/* Hex String */
#define YV_BSTRING	0x0f	/* Bit String */

    union
    {
	int yv_un_number;	/* code = YV_NUMBER
				   code = YV_BOOL */

	double yv_un_real;	/* code = YV_REAL */

	char *yv_un_string;	/* code = YV_STRING */

	struct
	{			/* code = YV_IDEFINED */
	    char *yv_st_module;
	    char *yv_st_modid;
	    char *yv_st_identifier;
	}
	yv_st;

	struct ypv *yv_un_idlist;	/* code = YV_IDLIST
					   code = YV_VALIST
					   code = YV_OIDLIST */

	struct
	{
	    char *yv_sl_xstring;
	    int yv_sl_xlength;
	}
	yv_sl;			/* code = YV_HSTRING
				   code = YV_BSTRING */
    }
    yv_un;
#define	yv_number	yv_un.yv_un_number
#define	yv_string	yv_un.yv_un_string
#define	yv_identifier	yv_un.yv_st.yv_st_identifier
#define	yv_module	yv_un.yv_st.yv_st_module
#define yv_modid	yv_un.yv_st.yv_st_modid
#define yv_idlist	yv_un.yv_un_idlist
#define yv_real		yv_un.yv_un_real
#define yv_xstring	yv_un.yv_sl.yv_sl_xstring
#define yv_xlength	yv_un.yv_sl.yv_sl_xlength

    char *yv_action;
    int yv_act_lineno;

    int yv_flags;
#define	YV_NOFLAGS	0x00	/* no flags */
#define	YV_ID		0x01	/* ID Value */
#define	YV_NAMED	0x02	/* NamedNumber */
#define	YV_TYPE		0x04	/* TYPE Value */
#define	YV_BOUND	0x08	/* named value */
#define	YVBITS	"\020\01ID\02NAMED\03TYPE\04BOUND"

    char *yv_id;		/* flags & YV_ID */

    char *yv_named;		/* flags & YV_NAMED */

    struct ype *yv_type;	/* flags & YV_TYPE */

    struct ypv *yv_next;
}
ypv, *YV;

extern YV new_value(int code);
extern YV add_value(register YV y, register YV z);
extern YV copy_value(register YV yv);

typedef struct ypt
{
    int yt_class;

    YV yt_value;
}
ypt, *YT;

YT new_tag(PElementClass class);
YT copy_tag(register YT yt);

extern int e_actions, d_actions, p_actions;

#define ER_UNKNOWN	0	/* Unknown what the type is - warn if used */
#define ER_NORMAL	1	/* Implicit works normally */
#define ER_EXPLICIT	2	/* Implicit should be translated to explicit */


typedef struct ype
{
    int yp_code;
#define	YP_UNDF		0x00	/* type not yet known */
#define	YP_BOOL		0x01	/* BOOLEAN */
#define	YP_INT		0x02	/* INTEGER */
#define	YP_INTLIST	0x03	/* INTEGER [ NamedNumberList ] */
#define	YP_BIT		0x04	/* BITSTRING */
#define	YP_BITLIST	0x05	/* BITSTRING [ NamedNumberList ] */
#define	YP_OCT		0x06	/* OCTETSTRING */
#define	YP_NULL		0x07	/* NULL */
#define	YP_SEQ		0x08	/* SEQUENCE */
#define	YP_SEQTYPE	0x09	/* SEQUENCE OF Type */
#define	YP_SEQLIST	0x0a	/* SEQUENCE [ ElementTypes ] */
#define	YP_SET		0x0b	/* SET */
#define	YP_SETTYPE	0x0c	/* SET OF Type */
#define	YP_SETLIST	0x0d	/* SET [ MemberTypes ] */
#define	YP_CHOICE	0x0e	/* CHOICE [ AlternativeTypeList ] */
#define	YP_ANY		0x0f	/* ANY */
#define	YP_OID		0x10	/* OBJECT IDENTIFIER */
#define	YP_IDEFINED	0x11	/* identifier */
#define YP_ENUMLIST	0x12	/* ENUMERATED */
#define YP_REAL		0x13	/* Real (floating-point) */
#define YP_IMPTYPE	0x14	/* Imported - real type unknown */

    int yp_direction;
#define YP_DECODER	0x01
#define YP_ENCODER	0x02
#define	YP_PRINTER	0x04

    union
    {
	struct
	{			/* code = YP_IDEFINED */
	    char *yp_st_module;	/* module name */
	    OID yp_st_modid;	/* module id */
	    char *yp_st_identifier;	/* definition name */
	}
	yp_st;

	struct ype *yp_un_type;	/* code = YP_SEQTYPE
				   code = YP_SEQLIST
				   code = YP_SETTYPE
				   code = YP_SETLIST
				   code = YP_CHOICE */

	YV yp_un_value;		/* code = YP_INTLIST
				   code = YP_BITLIST */
    }
    yp_un;
#define	yp_identifier	yp_un.yp_st.yp_st_identifier
#define	yp_module	yp_un.yp_st.yp_st_module
#define yp_modid	yp_un.yp_st.yp_st_modid
#define	yp_type		yp_un.yp_un_type
#define	yp_value	yp_un.yp_un_value

    char *yp_intexp;		/* expressions to pass (use) as extra */
    char *yp_strexp;		/* parameters (primitive values) */
    char yp_prfexp;

    char *yp_declexp;
    char *yp_varexp;

    char *yp_structname;
    char *yp_ptrname;

    char *yp_param_type;

    char *yp_action0;
    int yp_act0_lineno;

    char *yp_action05;
    int yp_act05_lineno;

    char *yp_action1;
    int yp_act1_lineno;

    char *yp_action2;
    int yp_act2_lineno;

    char *yp_action3;
    int yp_act3_lineno;

    int yp_flags;
#define	YP_NOFLAGS	0x0000	/* no flags */
#define	YP_OPTIONAL	0x0001	/* OPTIONAL */
#define	YP_COMPONENTS	0x0002	/* COMPONENTS OF */
#define	YP_IMPLICIT	0x0004	/* IMPLICIT */
#define	YP_DEFAULT	0x0008	/* DEFAULT */
#define	YP_ID		0x0010	/* ID */
#define	YP_TAG		0x0020	/* Tag */
#define	YP_BOUND	0x0040	/* ID LANGLE */
#define	YP_PULLEDUP	0x0080	/* member is a choice */
#define YP_PARMVAL	0x0100	/* value to be passed to parm is present */
#define YP_CONTROLLED	0x0200	/* encoding item has a controller */
#define	YP_OPTCONTROL	0x0400	/*   .. */
#define	YP_ACTION1	0x0800	/* action1 acted upon */
#define	YP_PARMISOID	0x1000	/* value to be passed to parm is OID */
#define YP_ENCRYPTED	0x2000	/* encypted - which is a bit hazy */
#define YP_IMPORTED	0x4000	/* value imported from another module */
#define YP_EXPORTED	0x8000	/* value exported to another module */
#define YP_WANTIMPLICIT 0x10000	/* Keep the implicit tag */
#define	YPBITS	"\020\01OPTIONAL\02COMPONENTS\03IMPLICIT\04DEFAULT\05ID\06TAG\
\07BOUND\010PULLEDUP\011PARMVAL\012CONTROLLED\013OPTCONTROL\
\014ACTION1\015PARMISOID\016ENCRYPTED\017IMPORTED\020EXPORTED"

    YV yp_default;		/* flags & YP_DEFAULT */

    char *yp_id;		/* flags & YP_ID */

    YT yp_tag;			/* flags & YP_TAG */

    char *yp_bound;		/* flags & YP_BOUND */

    char *yp_parm;		/* flags & YP_PARMVAL */

    char *yp_control;		/* flags & YP_CONTROLLED */

    char *yp_optcontrol;	/* flags & YP_OPTCONTROL */

    char *yp_offset;

    struct ype *yp_next;

    int yp_lineno;		/* line number for diagnostics */
}
ype, *YP;

YP new_type(int code, int lineno), add_type(register YP y, register YP z), copy_type(register YP yp), lkup(YP yp);

char *new_string(register char *s);

#define	TBL_EXPORT	0
#define TBL_IMPORT	1
#define MAX_TBLS	2

extern int tagcontrol;
#define TAG_UNKNOWN 	0
#define TAG_IMPLICIT	1
#define TAG_EXPLICIT	2

#define CH_FULLY	0
#define CH_PARTIAL	1

typedef struct yop
{
    char *yo_name;

    YP yo_arg;
    YP yo_result;
    YV yo_errors;
    YV yo_linked;

    int yo_opcode;
}
yop, *YO;


typedef struct yerr
{
    char *ye_name;

    YP ye_param;

    int ye_errcode;

    int ye_offset;
}
yerr, *YE;

typedef struct modlist
{
    char *md_module;
    OID md_oid;
    int md_flags;
#define MDF_SEEN              1	/* Seen this module */

    struct modlist *md_next;
}
modlist, *MD;

extern int yysection;
extern char *yyencpref;
extern char *yydecpref;
extern char *yyprfpref;
extern char *yyencdflt;
extern char *yydecdflt;
extern char *yyprfdflt;

extern int yydebug;
extern int lineno;

#if USING_FLEX
extern char *yytext;
#else
extern char yytext[];
#endif

extern char *mymodule;

extern OID mymoduleid;

extern char *bflag;
extern int Cflag;
extern int dflag;
extern int Pflag;
extern char *sysin;

extern char *module_actions;

OID addoid(OID o1, OID o2);
OID int2oid(int n);
OID oidlookup(char *name);
char *oidname(OID oid);
char *oidprint(OID oid);
char   *_sprintoid (OID oid);

#endif	/* XXX_XXX_X */
