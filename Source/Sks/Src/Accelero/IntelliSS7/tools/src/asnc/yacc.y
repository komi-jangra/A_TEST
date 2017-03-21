%{
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
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:08  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2002/10/25 21:54:59  mmiers
 * LOG: Fix warnings noted by later bison versions
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 19:01:45  mmiers
 * LOG: Warning removal
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
 * LOG: Revision 3.1  2000/08/16 00:07:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/05/11 02:06:16  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.1  2000/01/28 16:54:52  mmiers
 * LOG:
 * LOG:
 * LOG: Get this to compile in the polluted NT environment.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:30:06  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/07/22 00:35:21  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.4  1999/04/09 21:30:43  mmiers
 * LOG:
 * LOG:
 * LOG: Remove all 218 warnings.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 19:40:08  mmiers
 * LOG: Fix HPUX build.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 18:22:56  mmiers
 * LOG: Update universal library and IS41 to use the compiler directly.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:37:02  jpakrasi
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

#if defined(WIN32)
#pragma warning(disable:4274)
#endif

#ident "$Id: yacc.y,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ANS_COMPILER_BUILD

#ifdef HPUX
#include <alloca.h>
#endif

#include "asncomp.h"

extern int yylineno;

#define YYDEBUG        1

extern int pepydebug;
extern int doexternals;

extern int yylex();

#if defined(WIN32)
#define alloca _alloca
#endif

extern int pass1(), pass2();

int               tagcontrol = TAG_UNKNOWN;
static int        tagdefault;
static int        listtype;
static OID        modid;

static int        yyporting = 0;

extern void addtableref(char *name, OID id, int lt);
extern void addtable(char *name, int lt, int typ);
extern void
pass1_type(char *encpref, char *decpref, char *prfpref,
           char *mod, char *id, YP yp);
extern void check_impexp(YP yp);
extern void myyerror(char *format,...);
extern int setvaltype(YP yp, char *str);
extern int yyerror();

/*
 * encoding/decoding/printing/freeing functions
 */
static char        *efn, *dfn, *pfn, *ffn;

/*
 * clear the ?fn variables for the next coding functions
 */
void
clrfn()
{
    if (efn)
    {
        efn = NULL;
    }
    if (dfn)
    {
        dfn = NULL;
    }
    if (pfn)
    {
        pfn = NULL;
    }
    if (ffn)
    {
        ffn = NULL;
    }
}

typedef struct
{
    char *ys_structname;
    char *ys_ptrname;
}
ysa, *YS;

static YS
new_ys(char* str)
{
    YS        ys;
    char *p, *q;
    char c;

    if ((ys = (YS)malloc(sizeof *ys)) == NULL)
    {
        yyerror ("out of memory");
    }

    q = str;
    while (isspace (*q))
    {
        q++;
    }

    for (p = q; isalnum(*p) || *p == '_'; p++)
    {
        continue;
    }

    if (*p != '\0')
    {
        c = *p;
        *p = '\0';
        ys->ys_structname = new_string (q);
        *p = c;
    }
    else
    {
        ys->ys_structname = new_string (q);
        ys->ys_ptrname = NULL;
        free (str);

        return ys;
    }

    for (q = p; *q != '$'; q++)
    {
        if (! *q)
        {
            free (str);
            ys->ys_ptrname = NULL;

            return ys;
        }
    }

    q++;
    while (isspace (*q))
    {
        q++;
    }

    for (p = q; isalnum(*p) || *p == '_'; p++)
    {
        continue;
    }

    *p = '\0';
    ys->ys_ptrname = new_string (q);
    free (str);

    return ys;
}

#define free_ys(ys) \
    free ((char *)(ys))

static int  final_actions = 0;
static int  start_actions = 0;

char*
hex2bin (char* s, int* pi)
{
    char *d;
    char *start;
    int   c, i;


    if ((d = malloc((unsigned)strlen(s)/2 + 2)) == NULL)
    {
        yyerror ("out of memory");
    }

    start = d;
    for (i = 0; *s; i++)
    {
        if ((c = *s++) >= 'a' && c <= 'f')
        {
            c -= 'a' - 0x0a;
        }
        else
        {
            if (c >= 'A' && c <= 'F')
            {
                c -= 'A' - 0x0a;
            }
            else
            {
                if (c >= '0' && c <= '9')
                {
                    c -= '0';
                }
                else
                {
                    c = 0;
                }
            }
        }

        if (i & 1)
        {
            *d++ |= c & 0xf;
        }
        else
        {
            *d = (c & 0xf) << 4;
        }
    }

    *pi = i;        /* We use number semi-octets ! */

    return start;
}

char*
bit2bin(char* s, int* pi)
{
    char *d;
    char *start;
    int   c, shft, i;


    if ((d = malloc((unsigned)strlen(s)/8 + 2)) == NULL)
    {
        yyerror ("out of memory");
    }

    start = d;
    *d = 0;
    for (i = 0; *s; i++)
    {
        if ((c = *s++) == '1')
        {
            c = 1;
        }
        else if (c == '0')
        {
            c = 0;
        }
        else
        {
            break;        /* ?? */
        }

        shft = 7 - i % 8;        /* shift to get to its bit */
        *d |= c << shft;

        if (shft == 0)        /* last bit in this octet so goto next octet */
        {
            *++d = 0;        /* initialise it to zero */
        }
    }

    *pi = i;
    return start;
}

int
bin2hex (unsigned char* s, char* d, int len)
{
    int    i, g;

    for (i = 0; i < len; i++)
    {
        g = s[i >> 1];

        if ((i & 1) == 0)
        {
            g >>= 4;
        }
        g &= 0xf;

        if (g < 0x0a)
        {
            *d++ = g + '0';
        }
        else
        {
            *d++ = g + 'a' - 0x0a;
        }
    }

    *d = 0;

    return len;
}

int
hex2int(char* s)
{
    int        sum = 0, i;

    while (*s)
    {
        if (!isxdigit(*s))
        {
            break;
        }
        if (isdigit(*s))
        {
            i = *s - '0';
        }
        else
        {
            i = tolower(*s) - 'a' + 10;
        }
        sum = (sum << 4) + i;
        s++;
    }

    return sum;
}

int
bit2int(char* s)
{
    int        sum = 0;

    while (*s)
    {
        if (*s != '0' && *s != '1')
        {
            break;
        }
        if (*s == '1')
        {
            sum <<= 1;
        }
        else
        {
            sum = (sum << 1) + 1;
        }
        s++;
    }

    return sum;
}

%}

%start        ModuleDefinition


%union
{
    int     yy_number;
    char   *yy_string;
    YP      yy_type;
    YV      yy_value;
    YT      yy_tag;
    OID     yy_oid;
    YS      yy_sctrl;
    double  yy_real;
}


%token  ABSENT ANY APPLICATION BAR BGIN BIT BITSTRING BOOLEAN_kw
        BSTRING BY CCE CHOICE COMMA COMPONENT COMPONENTS COMPONENTSOF
        CONTROL DEFAULT DEFINED DEFINITIONS DOT DOTDOT
        DOTDOTDOT ENCRYPTED END ENUMERATED EXPORTS
        EXPLICIT L_FALSE FROM HSTRING ID IDENTIFIER IMPLICIT
        IMPORTS INCLUDES INTEGER LANGLE LBRACE LBRACKET LITNUMBER
        LITSTRING LPAREN MIN MINUS MAX NAME NIL OBJECT OCTET
        OCTETSTRING OF_kw OPTIONAL_kw PARAMETERTYPE PLUS PREFIXES PRESENT
        PRIVATE RBRACE RBRACKET REAL RPAREN STAR
        SEMICOLON SEQUENCE SEQUENCEOF SET SETOF SIZE_kw STRING
        TAGS L_TRUE UNIVERSAL VALA VALB VALI VALS VALP VALO VALOID VALR
        VALT VALTYPE VALQ VALX VLENGTH WITH SCTRL PLUSINFINITY
        MINUSINFINITY

%type <yy_number>       LITNUMBER 
%type <yy_number>       ABSENT ANY BGIN APPLICATION BIT BITSTRING
                        BOOLEAN_kw CHOICE COMPONENT COMPONENTS COMPONENTSOF
                        DEFAULT DEFINED DEFINITIONS ENCRYPTED END
                        ENUMERATED EXPLICIT EXPORTS
                        L_FALSE FROM IDENTIFIER IMPLICIT IMPORTS INCLUDES
                        INTEGER MIN MAX NIL OBJECT OCTET OCTETSTRING
                        OF_kw OPTIONAL_kw PREFIXES PRESENT PRIVATE REAL
                        SEQUENCE SEQUENCEOF SET STRING TAGS
                        L_TRUE UNIVERSAL WITH PLUSINFINITY MINUSINFINITY
                        AnyType
%type <yy_real>         RealValue NumericRealValue SpecialRealValue
%type <yy_string>       ID NAME LITSTRING
                        BSTRING HSTRING VALA VALB VALI VALS VALP VALQ
                        VALR VALT VALTYPE VALO VALX VLENGTH VALOID
                        CONTROL PARAMETERTYPE ParameterType Control
                        ValParameter String PassInt PassBool PassOid
                        PassAny PassReal ModuleIdentifier Symbol
                        SymbolList SCTRL
%type <yy_type>         Type BuiltinType DefinedType PassValue PassBit
                        PassString NullPass ElementTypes
                        OptionalTypeList OptionalType NamedType
                        ComponentsOf AlternativeTypeList MemberTypes
                        SubType Valtype
%type <yy_value>        NamedNumberList NamedNumber NumericValue
                        Value BuiltinValue DefinedValue IdentifierList
                        Values NamedValueList NamedValue NNlist
%type <yy_tag>          Tag Class
%type <yy_oid>          ObjIdComponentList ObjectIdentifierValue
                        ObjIdComponent NumberForm NameAndNumberForm
%type   <yy_sctrl>      Sctrl
%%

ModuleDefinition:       ModuleIdentifier DEFINITIONS TagDefault CCE
                        {
                            mymodule = $1;
                            mymoduleid = modid;
                            pass1 ();
                        }
                        ModulePrefixes
                        {
                            start_actions++;
                        }
                        BGIN ModuleBody END
                        {
                            pass2 ();
                            final_actions++;
                        }
;

TagDefault:             EXPLICIT TAGS
                        { 
                            tagdefault = 0;
                            tagcontrol = TAG_EXPLICIT;
                        }
        |               IMPLICIT TAGS
                        {
                            tagdefault = YP_IMPLICIT;
                            tagcontrol = TAG_IMPLICIT;
                        }
        |
                        {
                            tagdefault = 0;
                            tagcontrol = TAG_UNKNOWN;
                        }
;

ModuleIdentifier:        ID AssignedIdentifier
                         {
                             $$ = $1;
                         }
;

AssignedIdentifier:      ObjectIdentifierValue
                         {
                             modid = $1;
                         }
        |
;

ModulePrefixes:         PREFIXES String String String
                        {
                            yyencdflt = $2;
                            yydecdflt = $3;
                            yyprfdflt = $4;
                        }
        |
;

ModuleBody:             Exports Imports AssignmentList
;

Exports:                EXPORTS
                        {
                            listtype = TBL_EXPORT;
                            doexternals = 0;
                            yyporting = 1;
                        }
                        SymbolsExported SEMICOLON
                        {
                            yyporting = 0;
                        }
        |
;

SymbolsExported:        SymbolList
                        {
                            $<yy_string>$ = $1;
                        }
        |
                        {
                            $<yy_string>$ = NULL;
                        }
;

Imports:                IMPORTS
                        {
                            listtype = TBL_IMPORT;
                            yyporting = 1;
                        }
                        SymbolsImported SEMICOLON
                        {
                            yyporting = 0;
                        }
        |
;

SymbolsImported:        SymbolsFromModuleList
        |
;

SymbolsFromModuleList:  SymbolsFromModuleList SymbolsFromModule
        |               SymbolsFromModule
;

SymbolsFromModule:      SymbolList FROM ModuleIdentifier
                        {
                            addtableref ($3, modid, listtype);
                        }
;

SymbolList:             SymbolList COMMA Symbol
                        {
                            addtable($3, listtype, ER_UNKNOWN);
                        }
        |               Symbol
                        {
                            addtable ($1, listtype, ER_UNKNOWN);
                        }
        |               SymbolList COMMA MINUS Symbol
                        {
                            addtable($4, listtype, ER_NORMAL);
                        }
        |               MINUS Symbol
                        {
                            addtable ($2, listtype, ER_NORMAL);
                        }
        |               SymbolList COMMA PLUS Symbol
                        {
                            addtable($4, listtype, ER_EXPLICIT);
                        }
        |               PLUS Symbol
                        {
                            addtable ($2, listtype, ER_EXPLICIT);
                        }
;

Symbol:                 ID
        |               NAME
;

AssignmentList:         AssignmentList Assignment
        |
;

String:                 ID
                        {
                            $$ = $1;
                        }
        |               NAME
                        {
                            $$ = $1;
                        }
;

Assignment:             Typeassignment
        |               Valueassignment
;

Typeassignment:         ID ParameterType CCE Type
                        {
                            if ($2)
                            {
                                $4->yp_param_type = $2;
                            }

                            pass1_type(yyencpref, yydecpref, yyprfpref,
                                       mymodule, $1, $4);
                        }
;

Type:                   BuiltinType
                        {
                            $$ = $1;
                            $$->yp_direction = yysection;
                        }
        |               DefinedType
                        {
                            $$ = $1;
                            $$->yp_direction = yysection;
                        }
        |               SubType
                        {
                            $$ = $1;
                            $$->yp_direction = yysection;
                        }
;

Control:                CONTROL
        |
                        {
                            $$ = NULL;
                        }
        ;

ParameterType:          PARAMETERTYPE
        |
                        {
                            $$ = NULL;
                        }
;

Valtype:                VALTYPE
                        {
                            $$ = new_type(YP_UNDF, -1);
                            if (setvaltype($$, $1) == 0)
                            {
                                yyerror("syntax error in [[ T ... ]]");
                            }
                            free($1);
                        }
        |
                        {
                            $$ = new_type(YP_UNDF, -1);
                        }
;

BuiltinType:            BOOLEAN_kw PassBool
                        {
                            $$ = new_type (YP_BOOL, $1);
                            $$->yp_intexp = $2;
                        }
        |               INTEGER PassInt NNlist
                        {
                            $$ = new_type ($3 ? YP_INTLIST : YP_INT, $1);
                            $$->yp_intexp = $2;
                            if ($3)
                            {
                                    $$->yp_value = $3;
                            }
                        }
        |               ENUMERATED PassInt LBRACE NamedNumberList RBRACE
                        {
                            $$ = new_type (YP_ENUMLIST, $1);
                            $$->yp_intexp = $2;
                            $$->yp_value = $4;
                        }
        |               Bitstring PassBit NNlist
                        {
                            $$ = $2;
                            $$->yp_code = $3 ? YP_BITLIST: YP_BIT;
                            if ($3)
                            {
                                $$->yp_value = $3;
                            }
                        }
        |               Octetstring PassString
                        {
                            $$ = $2;
                            $$->yp_code = YP_OCT;
                        }
        |               NIL
                        {
                            $$ = new_type(YP_NULL, $1);
                        }
        |               SEQUENCE Sctrl PassAny
                        {
                            $$ = new_type (YP_SEQ, $1);
                            $$->yp_strexp = $3;
                        }
        |               SequenceOf Sctrl Valtype Control Type
                        {
                            $$ = $3;
                            $$->yp_code = YP_SEQTYPE;
                            $$->yp_type = $5;

                            if ($2)
                            {
                                $$->yp_structname = $2->ys_structname;
                                $$->yp_ptrname = $2->ys_ptrname;
                                free_ys ($2);
                            }

                            if ($4)
                            {
                                $$->yp_control = $4;
                                $$->yp_flags |= YP_CONTROLLED;
                            }
                        }
        |               SEQUENCE Sctrl Valtype LBRACE ElementTypes RBRACE
                        {
                            $$ = $3;
                            $$->yp_code = YP_SEQLIST;
                            $$->yp_type = $5;
                            if ($2)
                            {
                                $$->yp_structname = $2->ys_structname;
                                $$->yp_ptrname = $2->ys_ptrname;
                                free_ys ($2);
                            }
                        }
        |               SET Sctrl PassAny
                        {
                            $$ = new_type(YP_SET, $1);
                            $$->yp_strexp = $3;
                        }
        |               SetOf Sctrl Valtype Control Type
                        {
                            $$ = $3;
                            $$->yp_code = YP_SETTYPE;
                            $$->yp_type = $5;

                            if ($2)
                            {
                                $$->yp_structname = $2->ys_structname;
                                $$->yp_ptrname = $2->ys_ptrname;
                                free_ys ($2);
                            }
                            if ($4)
                            {
                                $$->yp_control = $4;
                                $$->yp_flags |= YP_CONTROLLED;
                            }
                        }

        |               SET Sctrl Valtype LBRACE MemberTypes RBRACE
                        {
                            $$ = $3;
                            $$->yp_code = YP_SETLIST;
                            $$->yp_type = $5;

                            if ($2)
                            {
                                $$->yp_structname = $2->ys_structname;
                                $$->yp_ptrname = $2->ys_ptrname;
                                free_ys ($2);
                            }
                        }
        |               Tag IMPLICIT Type
                        {
                            $$ = $3;
                            $$->yp_tag = $1;
                            $$->yp_flags |= (YP_IMPLICIT | YP_TAG);

                        }
        |               Tag EXPLICIT Type
                        {
                            $$ = $3;
                            $$->yp_tag = $1;
                            $$->yp_flags |= YP_TAG;
                        }
        |               Tag Type
                        {
                            $$ = $2;
                            $$->yp_tag = $1;
                            $$->yp_flags |= (YP_TAG| tagdefault);
                        }
        |               CHOICE Sctrl Valtype Control
                        LBRACE AlternativeTypeList RBRACE
                        {
                            $$ = $3;
                            $$->yp_code = YP_CHOICE;
                            $$->yp_type = $6;

                            if ($2)
                            {
                                $$->yp_structname = $2->ys_structname;
                                $$->yp_ptrname = $2->ys_ptrname;
                                free_ys ($2);
                            }

                            if ($4)
                            {
                                $$->yp_control = $4;
                                $$->yp_flags |= YP_CONTROLLED;
                            }
                        }
        |               NAME LANGLE Type
                        {
                            $$ = $3;
                            $$->yp_bound = $1;
                            $$->yp_flags |= YP_BOUND;
                        }
        |               AnyType PassAny
                        {
                            $$ = new_type (YP_ANY, $1);
                            $$->yp_strexp = $2;
                        }
        |               STAR AnyType PassAny
                        {
                            $$ = new_type (YP_ANY, $2);
                            $$->yp_strexp = $3;
                            $$->yp_flags |= YP_WANTIMPLICIT;
                        }
        |               OBJECT IDENTIFIER PassOid
                        {
                            $$ = new_type (YP_OID, $1);
                            $$->yp_strexp = $3;
                        }
        |               ENCRYPTED Type
                        {
                            $$ = $2;
                            $$->yp_tag = new_tag (PE_CLASS_UNIV);
                            $$->yp_tag->yt_value = new_value(YV_NUMBER);
                            $$->yp_tag->yt_value->yv_number = PE_PRIM_ENCR;
                            $$->yp_flags |=
                                    (YP_ENCRYPTED | YP_TAG | YP_IMPLICIT);
                        }
        |               REAL PassReal
                        {
                            $$ = new_type(YP_REAL, $1);
                            $$->yp_strexp = $2;
                        }
;

NNlist:                 LBRACE NamedNumberList RBRACE
                        {
                            $$ = $2;
                        }
        |
                        {
                            $$ = NULL;
                        }
;

DefinedType:            ID PassValue ValParameter
                        {
                            $$ = $2;
                            $$->yp_code = YP_IDEFINED;
                            $$->yp_identifier = $1;
                            if ($3)
                            {
                                $$->yp_parm = $3;
                                $$->yp_flags |= YP_PARMVAL;
                            }
                            check_impexp ($$);
                        }
        |               ID DOT ID PassValue ValParameter
                        {
                            $$ = $4;
                            $$->yp_code = YP_IDEFINED;
                            $$->yp_identifier = $3;
                            $$->yp_module = $1;
                            if ($5)
                            {
                                $$->yp_parm = $5;
                                $$->yp_flags |= YP_PARMVAL;
                            }
                        }
;

PassValue:              VALA
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = NULL;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 'a';
                        }
        |               VALB
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $1;
                            $$->yp_strexp = NULL;
                            $$->yp_prfexp = 'b';
                        }
        |               VALI
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $1;
                            $$->yp_strexp = NULL;
                            $$->yp_prfexp = 'i';
                        }
        |               VALX VLENGTH
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $2;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 'x';
                        }
        |               VALOID
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = NULL;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 'O';
                        }
        |               VALR
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = NULL;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 'r';
                        }
        |               VALT
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $1;
                            $$->yp_prfexp = 't';
                        }
        |               PassString
;

AnyType:                ANY
        |               ANY DEFINED BY NAME
;
                        
PassOid:                VALOID
        |
                        {
                            $$ = NULL;
                        }
;

PassAny:                VALA
        |
                        {
                            $$ = NULL;
                        }
;

PassBool:               VALB
        |
                        {
                            $$ = NULL;
                        }
;

PassInt:                VALI
        |
                        {
                            $$ = NULL;
                        }
;

PassBit:                VALX VLENGTH
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $2;
                            $$->yp_strexp = $1;
                        }
        |               VALT
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $1;
                            $$->yp_strexp = NULL;
                        }
        |               NullPass
;

PassString:             VALS
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = NULL;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 's';
                        }
        |               VALO VLENGTH
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = $2;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 'o';
                        }
        |               VALQ
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = NULL;
                            $$->yp_strexp = $1;
                            $$->yp_prfexp = 'q';
                        }
        |               NullPass
;

PassReal:               VALR 
        |
                        {
                            $$ = NULL;
                        }
;

NullPass:
                        {
                            $$ = new_type (YP_UNDF, -1);
                            $$->yp_intexp = NULL;
                            $$->yp_strexp = NULL;
                        }
;

ValParameter:           VALP
        |
                        {
                            $$ = NULL;
                        }
;

NamedNumberList:        NamedNumber
                        {
                            $$ = $1;
                        }
        |               NamedNumberList COMMA NamedNumber
                        {
                            $$ = add_value ($1, $3);
                        }
;

NamedNumber:            NAME LPAREN NumericValue RPAREN
                        {
                            $$ = $3;
                            $$->yv_named = $1;
                            $$->yv_flags |= YV_NAMED;
                        }
;

NumericValue:           LITNUMBER
                        {
                            $$ = new_value (YV_NUMBER);
                            $$->yv_number = $1;
                        }
        |               DefinedValue
;

ElementTypes:           OptionalTypeList
                        {
                            $$ = $1;
                        }
        |
                        {
                            $$ = NULL;
                        }
;

MemberTypes:            OptionalTypeList
                        {
                            $$ = $1;
                        }
        |
                        {
                            $$ = NULL;
                        }
;

OptionalTypeList:       OptionalType
                        {
                            $$ = $1;
                        }
        |               OptionalTypeList COMMA OptionalType
                        {
                            $$ = add_type ($1, $3);
                        }
;

OptionalType:           NamedType
                        {
                            $$ = $1;
                        }
        |               NamedType OPTIONAL_kw Control
                        {
                            $$ = $1;
                            $$->yp_flags |= YP_OPTIONAL;
                            if ($3)
                            {
                                $$->yp_optcontrol = $3;
                                $$->yp_flags |= YP_OPTCONTROL;
                            }
                        }
        |               NamedType DEFAULT Value Control
                        {
                            $$ = $1;
                            $$->yp_default = $3;
                            $$->yp_flags |= YP_DEFAULT;

                            if ($4)
                            {
                                $$->yp_optcontrol = $4;
                                $$->yp_flags |= YP_OPTCONTROL;
                            }
                        }
        |               ComponentsOf
                        {
                            $$ = $1;
                        }
        |                NAME ComponentsOf
                        {
                            $$ = $2;
                            $$->yp_id = $1;
                        }
;

NamedType:              NAME Type
                        {
                            $$ = $2;
                            $$->yp_id = $1;
                            $$->yp_flags |= YP_ID;
                        }
        |               Type
                        {
                            $$ = $1;
                        }
;

ComponentsOf:           Components Type
                        {
                            $$ = $2;
                            $$->yp_flags |= YP_COMPONENTS;
                        }
;

AlternativeTypeList:    NamedType
                        {
                            $$ = $1;
                        }
        |               AlternativeTypeList COMMA NamedType
                        {
                            $$ = add_type ($1, $3);
                        }
;

Tag:                    LBRACKET Class NumericValue RBRACKET
                        {
                            $$ = $2;
                            $$->yt_value = $3;
                        }
;

Class:                  UNIVERSAL
                        {
                            $$ = new_tag (PE_CLASS_UNIV);
                        }
        |               APPLICATION
                        {
                            $$ = new_tag (PE_CLASS_APPL);
                        }
        |               PRIVATE
                        {
                            $$ = new_tag (PE_CLASS_PRIV);
                        }
        |
                        {
                            $$ = new_tag (PE_CLASS_CONT);
                        }
;


Valueassignment:        NAME Type CCE Value
                        {
                            $<yy_string>$ = NULL;
                        }
;

Value:                  BuiltinValue
        |               DefinedValue
;

BuiltinValue:           L_TRUE
                        {
                            $$ = new_value (YV_BOOL);
                            $$->yv_number = 1;
                        }
        |               L_FALSE
                        {
                            $$ = new_value (YV_BOOL);
                            $$->yv_number = 0;
                        }
        |               LITNUMBER
                        {
                            $$ = new_value (YV_NUMBER);
                            $$->yv_number = $1;
                        }
        |               BSTRING
                        {
                            $$ = new_value (YV_BSTRING);
                            $$->yv_xstring = bit2bin($1, &$$->yv_xlength);
                            free($1);
                        }
        |               HSTRING
                        {
                            $$ = new_value (YV_HSTRING);
                            $$->yv_xstring = hex2bin($1, &$$->yv_xlength);
                            free($1);
                        }
        |               LBRACE ID IdentifierList RBRACE
                        {
                            $$ = new_value (YV_IDLIST);
                            $$->yv_idlist = new_value (YV_IDEFINED);
                            $$->yv_idlist->yv_identifier = $2;
                            if ($3)
                                $$ = add_value ($$, $3);
                        }
        |               LITSTRING
                        {
                            $$ = new_value (YV_STRING);
                            $$->yv_string = $1;
                        }
        |               NIL
                        {
                            $$ = new_value (YV_NULL);
                        }
        |               LBRACE Values RBRACE
                        {
                            $$ = new_value (YV_VALIST);
                            $$->yv_idlist = $2;
                        }
        |               NAME Value
                        {
                            $$ = $2;
                            $$->yv_id = $1;
                            $$->yv_flags |= YV_ID;
                        }
        |               Type Value
                        {
                            $$ = $2;
                            $$->yv_type = $1;
                            $$->yv_flags |= YV_TYPE;
                        }
        |               RealValue
                        {
                            $$ = new_value (YV_REAL);
                            $$->yv_real = $1;
                        }
;

RealValue:              NumericRealValue
        |               SpecialRealValue
;

SpecialRealValue:       PLUSINFINITY
                        {
                            $$ = PE_REAL_INFINITY;
                        } 
        |               MINUSINFINITY
                        {
                            $$ = - PE_REAL_INFINITY;
                        }
;

NumericRealValue:       LBRACE LITNUMBER COMMA LITNUMBER COMMA LITNUMBER RBRACE
                        {
                                if ($4 != 2 && $4 != 10)
                                {
                                        myyerror ("Illegal base value %d", $4);
                                }
                                $$ = $2 * pow ((double)$4, (double)$6);
                        }
;

DefinedValue:           ID
                        {
                            $$ = new_value (YV_IDEFINED);
                            $$->yv_identifier = $1;
                        }
        |               NAME
                        {        /* XXX */
                            $$ = new_value (YV_IDEFINED);
                            $$->yv_identifier = $1;
                            $$->yv_flags |= YV_BOUND;
                        }
        |               ID DOT ID
                        {
                            $$ = new_value (YV_IDEFINED);
                            $$->yv_identifier = $3;
                            $$->yv_module = $1;
                        }
;

IdentifierList:         COMMA ID IdentifierList
                        {
                            $$ = new_value (YV_IDEFINED);
                            $$->yv_identifier = $2;
                            if ($3)
                            {
                                $$ = add_value ($3, $$);
                            }
                        }
        |
                        {
                            $$ = NULL;
                        }
;

Values:                 NamedValueList
                        {
                            $$ = $1;
                        }
        |
                        {
                            $$ = NULL;
                        }
;

NamedValueList:         NamedValue
                        {
                            $$ = $1;
                        }
        |               NamedValueList COMMA NamedValue
                        {
                            $$ = add_value ($1, $3);
                        }
;

NamedValue:             Value
                        {
                            $$ = $1;
                        }
;

Octetstring:            OCTET STRING
                        {
                            $<yy_number>$ = 0;
                        }
        |               OCTETSTRING
                        {
                            $<yy_number>$ = 0;
                        }
;

Bitstring:              BITSTRING
                        {
                            $<yy_number>$ = 0;
                        }
        |               BIT STRING
                        {
                            $<yy_number>$ = 0;
                        }
;

SequenceOf:             SEQUENCEOF
                        {
                            $<yy_number>$ = 0;
                        }
        |               SEQUENCE OF_kw
                        {
                            $<yy_number>$ = 0;
                        }
;

SetOf:                  SETOF
                        {
                            $<yy_number>$ = 0;
                        }
        |               SET OF_kw
                        {
                            $<yy_number>$ = 0;
                        }
;

Components:             COMPONENTSOF
                        {
                            $<yy_number>$ = 0;
                        }
        |               COMPONENTS OF_kw
                        {
                            $<yy_number>$ = 0;
                        }
;

ObjectIdentifierValue:  LBRACE ObjIdComponentList RBRACE
                        {
                            $$ = $2;
                        }
;

ObjIdComponentList:     ObjIdComponent
        |               ObjIdComponentList ObjIdComponent
                        {
                                $$ = addoid($1, $2);
                                oid_free ($1);
                                oid_free ($2);
                        }
;

ObjIdComponent:         NumberForm
        |               NameAndNumberForm
;

NumberForm:             LITNUMBER
                        {
                            $$ = int2oid ($1);
                        }
        |               DefinedValue
                        {
                            $$ = oidlookup($1->yv_identifier);
                            free((char *)$1);
                        }
;

NameAndNumberForm:      NAME LPAREN NumberForm RPAREN
                        {
                            free ($1);
                            $$ = $3;
                        }
;

SubType:                Type SubtypeSpec
        |               SET SizeConstraint OF_kw Sctrl Control Type
                        {
                            $$ = new_type (YP_SETTYPE, $1);
                            $$->yp_type = $6;
                            if ($4)
                            {
                                $$->yp_structname = $4->ys_structname;
                                $$->yp_ptrname = $4->ys_ptrname;
                                free_ys ($4);
                            }

                            if ($5)
                            {
                                $$->yp_control = $5;
                                $$->yp_flags |= YP_CONTROLLED;
                            }
                        }
        |               SEQUENCE SizeConstraint OF_kw Sctrl Control Type
                        {
                            $$ = new_type (YP_SEQTYPE, $1);
                            $$->yp_type = $6;
                            if ($4)
                            {
                                $$->yp_structname = $4->ys_structname;
                                $$->yp_ptrname = $4->ys_ptrname;
                                free_ys ($4);
                            }

                            if ($5)
                            {
                                $$->yp_control = $5;
                                $$->yp_flags |= YP_CONTROLLED;
                            }
                        }
        ;

SubtypeSpec:            LPAREN SubtypeAlternative SubtypeAlternativeList RPAREN
;

SubtypeAlternative:     SubtypeValueSet
        |               SubtypeConstraint
;

SubtypeAlternativeList: BAR SubtypeAlternative SubtypeAlternativeList
        |
;

SubtypeValueSet:        Value
                        {
                            $<yy_value>$ = $1;
                        }
        |               ContainedSubType
        |               ValueRange
        |               PermittedAlphabet
;

SubtypeConstraint:      SizeConstraint
        |               InnerTypeConstraint
;

ContainedSubType:       INCLUDES Type
                        {
                            $<yy_type>$ = $2;
                        }
;

ValueRange:             LowerEndPoint DOTDOT UpperEndpoint
;

LowerEndPoint:          LowerEndValue
        |               LowerEndValue LANGLE
;

UpperEndpoint:          UpperEndValue
        |               LANGLE UpperEndValue
;

LowerEndValue:          Value
                        {
                            $<yy_value>$ = $1;
                        }
        |               MIN
                        {
                            $<yy_number>$ = 0;
                        }
;

UpperEndValue:          Value
                        {
                            $<yy_value>$ = $1;
                        }
        |               MAX
                        {
                            $<yy_number>$ = 0;
                        }
;

SizeConstraint:         SIZE_kw SubtypeSpec
;

PermittedAlphabet:      FROM SubtypeSpec
                        {
                            $<yy_type>$ = NULL;
                        }
;

InnerTypeConstraint:    WITH COMPONENT SingleTypeConstraint
                        {
                            $<yy_number>$ = 0;
                        }
        |               WITH COMPONENTS MultipleTypeConstraints
                        {
                            $<yy_number>$ = 0;
                        }
;

SingleTypeConstraint:   SubtypeSpec
;

MultipleTypeConstraints:FullSpecification
        |               PartialSpecification
;

FullSpecification:      LBRACE TypeConstraints RBRACE
;

PartialSpecification:   LBRACE DOTDOTDOT COMMA TypeConstraints RBRACE
;

TypeConstraints:        NamedConstraint
        |               NamedConstraint COMMA TypeConstraints
;

NamedConstraint:        NAME Constraint
                        {
                            $<yy_string>$ = NULL;
                        }
        |               Constraint
                        {
                            $<yy_string>$ = NULL;
                        }
;

Constraint:             ValueConstraint
        |               PresenceConstraint
        |
;

ValueConstraint:        SubtypeSpec
        ;

PresenceConstraint:     PRESENT
                        {
                            $<yy_number>$ = 0;
                        }
        |               ABSENT
                        {
                            $<yy_number>$ = 0;
                        }
;

Sctrl:                  SCTRL
                        {
                            $$ = new_ys ($1);
                        }
        |
                        {
                            $$ = NULL;
                        }
;
%%

#include "lex.yy.c"
