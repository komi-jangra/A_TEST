/* A Bison parser, made by GNU Bison 1.875.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ABSENT = 258,
     ANY = 259,
     APPLICATION = 260,
     BAR = 261,
     BGIN = 262,
     BIT = 263,
     BITSTRING = 264,
     BOOLEAN_kw = 265,
     BSTRING = 266,
     BY = 267,
     CCE = 268,
     CHOICE = 269,
     COMMA = 270,
     COMPONENT = 271,
     COMPONENTS = 272,
     COMPONENTSOF = 273,
     CONTROL = 274,
     DEFAULT = 275,
     DEFINED = 276,
     DEFINITIONS = 277,
     DOT = 278,
     DOTDOT = 279,
     DOTDOTDOT = 280,
     ENCRYPTED = 281,
     END = 282,
     ENUMERATED = 283,
     EXPORTS = 284,
     EXPLICIT = 285,
     L_FALSE = 286,
     FROM = 287,
     HSTRING = 288,
     ID = 289,
     IDENTIFIER = 290,
     IMPLICIT = 291,
     IMPORTS = 292,
     INCLUDES = 293,
     INTEGER = 294,
     LANGLE = 295,
     LBRACE = 296,
     LBRACKET = 297,
     LITNUMBER = 298,
     LITSTRING = 299,
     LPAREN = 300,
     MIN = 301,
     MINUS = 302,
     MAX = 303,
     NAME = 304,
     NIL = 305,
     OBJECT = 306,
     OCTET = 307,
     OCTETSTRING = 308,
     OF_kw = 309,
     OPTIONAL_kw = 310,
     PARAMETERTYPE = 311,
     PLUS = 312,
     PREFIXES = 313,
     PRESENT = 314,
     PRIVATE = 315,
     RBRACE = 316,
     RBRACKET = 317,
     REAL = 318,
     RPAREN = 319,
     STAR = 320,
     SEMICOLON = 321,
     SEQUENCE = 322,
     SEQUENCEOF = 323,
     SET = 324,
     SETOF = 325,
     SIZE_kw = 326,
     STRING = 327,
     TAGS = 328,
     L_TRUE = 329,
     UNIVERSAL = 330,
     VALA = 331,
     VALB = 332,
     VALI = 333,
     VALS = 334,
     VALP = 335,
     VALO = 336,
     VALOID = 337,
     VALR = 338,
     VALT = 339,
     VALTYPE = 340,
     VALQ = 341,
     VALX = 342,
     VLENGTH = 343,
     WITH = 344,
     SCTRL = 345,
     PLUSINFINITY = 346,
     MINUSINFINITY = 347
   };
#endif
#define ABSENT 258
#define ANY 259
#define APPLICATION 260
#define BAR 261
#define BGIN 262
#define BIT 263
#define BITSTRING 264
#define BOOLEAN_kw 265
#define BSTRING 266
#define BY 267
#define CCE 268
#define CHOICE 269
#define COMMA 270
#define COMPONENT 271
#define COMPONENTS 272
#define COMPONENTSOF 273
#define CONTROL 274
#define DEFAULT 275
#define DEFINED 276
#define DEFINITIONS 277
#define DOT 278
#define DOTDOT 279
#define DOTDOTDOT 280
#define ENCRYPTED 281
#define END 282
#define ENUMERATED 283
#define EXPORTS 284
#define EXPLICIT 285
#define L_FALSE 286
#define FROM 287
#define HSTRING 288
#define ID 289
#define IDENTIFIER 290
#define IMPLICIT 291
#define IMPORTS 292
#define INCLUDES 293
#define INTEGER 294
#define LANGLE 295
#define LBRACE 296
#define LBRACKET 297
#define LITNUMBER 298
#define LITSTRING 299
#define LPAREN 300
#define MIN 301
#define MINUS 302
#define MAX 303
#define NAME 304
#define NIL 305
#define OBJECT 306
#define OCTET 307
#define OCTETSTRING 308
#define OF_kw 309
#define OPTIONAL_kw 310
#define PARAMETERTYPE 311
#define PLUS 312
#define PREFIXES 313
#define PRESENT 314
#define PRIVATE 315
#define RBRACE 316
#define RBRACKET 317
#define REAL 318
#define RPAREN 319
#define STAR 320
#define SEMICOLON 321
#define SEQUENCE 322
#define SEQUENCEOF 323
#define SET 324
#define SETOF 325
#define SIZE_kw 326
#define STRING 327
#define TAGS 328
#define L_TRUE 329
#define UNIVERSAL 330
#define VALA 331
#define VALB 332
#define VALI 333
#define VALS 334
#define VALP 335
#define VALO 336
#define VALOID 337
#define VALR 338
#define VALT 339
#define VALTYPE 340
#define VALQ 341
#define VALX 342
#define VLENGTH 343
#define WITH 344
#define SCTRL 345
#define PLUSINFINITY 346
#define MINUSINFINITY 347




/* Copy the first part of user declarations.  */
#line 1 "yacc.y"

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

#ident "$Id: yacc.tab.c,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

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



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 462 "yacc.y"
typedef union YYSTYPE {
    int     yy_number;
    char   *yy_string;
    YP      yy_type;
    YV      yy_value;
    YT      yy_tag;
    OID     yy_oid;
    YS      yy_sctrl;
    double  yy_real;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 727 "yacc.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 739 "yacc.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1059

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  99
/* YYNRULES -- Number of rules. */
#define YYNRULES  225
/* YYNRULES -- Number of states. */
#define YYNSTATES  359

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   347

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,     4,     5,    16,    19,    22,    23,    26,
      28,    29,    34,    35,    39,    40,    45,    46,    48,    49,
      50,    55,    56,    58,    59,    62,    64,    68,    72,    74,
      79,    82,    87,    90,    92,    94,    97,    98,   100,   102,
     104,   106,   111,   113,   115,   117,   119,   120,   122,   123,
     125,   126,   129,   133,   139,   143,   146,   148,   152,   158,
     165,   169,   175,   182,   186,   190,   193,   201,   205,   208,
     212,   216,   219,   222,   226,   227,   231,   237,   239,   241,
     243,   246,   248,   250,   252,   254,   256,   261,   263,   264,
     266,   267,   269,   270,   272,   273,   276,   278,   280,   282,
     285,   287,   289,   291,   292,   293,   295,   296,   298,   302,
     307,   309,   311,   313,   314,   316,   317,   319,   323,   325,
     329,   334,   336,   339,   342,   344,   347,   349,   353,   358,
     360,   362,   364,   365,   370,   372,   374,   376,   378,   380,
     382,   384,   389,   391,   393,   397,   400,   403,   405,   407,
     409,   411,   413,   421,   423,   425,   429,   433,   434,   436,
     437,   439,   443,   445,   448,   450,   452,   455,   457,   460,
     462,   465,   467,   470,   474,   476,   479,   481,   483,   485,
     487,   492,   495,   502,   509,   514,   516,   518,   522,   523,
     525,   527,   529,   531,   533,   535,   538,   542,   544,   547,
     549,   552,   554,   556,   558,   560,   563,   566,   570,   574,
     576,   578,   580,   584,   590,   592,   596,   599,   601,   603,
     605,   606,   608,   610,   612,   614
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short yyrhs[] =
{
      94,     0,    -1,    -1,    -1,    98,    22,    97,    13,    95,
     100,    96,     7,   101,    27,    -1,    30,    73,    -1,    36,
      73,    -1,    -1,    34,    99,    -1,   162,    -1,    -1,    58,
     113,   113,   113,    -1,    -1,   102,   105,   112,    -1,    -1,
      29,   103,   104,    66,    -1,    -1,   110,    -1,    -1,    -1,
      37,   106,   107,    66,    -1,    -1,   108,    -1,    -1,   108,
     109,    -1,   109,    -1,   110,    32,    98,    -1,   110,    15,
     111,    -1,   111,    -1,   110,    15,    47,   111,    -1,    47,
     111,    -1,   110,    15,    57,   111,    -1,    57,   111,    -1,
      34,    -1,    49,    -1,   112,   114,    -1,    -1,    34,    -1,
      49,    -1,   115,    -1,   146,    -1,    34,   118,    13,   116,
      -1,   120,    -1,   122,    -1,   167,    -1,    19,    -1,    -1,
      56,    -1,    -1,    85,    -1,    -1,    10,   127,    -1,    39,
     128,   121,    -1,    28,   128,    41,   134,    61,    -1,   158,
     129,   121,    -1,   157,   130,    -1,    50,    -1,    67,   191,
     126,    -1,   159,   191,   119,   117,   116,    -1,    67,   191,
     119,    41,   137,    61,    -1,    69,   191,   126,    -1,   160,
     191,   119,   117,   116,    -1,    69,   191,   119,    41,   138,
      61,    -1,   144,    36,   116,    -1,   144,    30,   116,    -1,
     144,   116,    -1,    14,   191,   119,   117,    41,   143,    61,
      -1,    49,    40,   116,    -1,   124,   126,    -1,    65,   124,
     126,    -1,    51,    35,   125,    -1,    26,   116,    -1,    63,
     131,    -1,    41,   134,    61,    -1,    -1,    34,   123,   133,
      -1,    34,    23,    34,   123,   133,    -1,    76,    -1,    77,
      -1,    78,    -1,    87,    88,    -1,    82,    -1,    83,    -1,
      84,    -1,   130,    -1,     4,    -1,     4,    21,    12,    49,
      -1,    82,    -1,    -1,    76,    -1,    -1,    77,    -1,    -1,
      78,    -1,    -1,    87,    88,    -1,    84,    -1,   132,    -1,
      79,    -1,    81,    88,    -1,    86,    -1,   132,    -1,    83,
      -1,    -1,    -1,    80,    -1,    -1,   135,    -1,   134,    15,
     135,    -1,    49,    45,   136,    64,    -1,    43,    -1,   152,
      -1,   139,    -1,    -1,   139,    -1,    -1,   140,    -1,   139,
      15,   140,    -1,   141,    -1,   141,    55,   117,    -1,   141,
      20,   147,   117,    -1,   142,    -1,    49,   142,    -1,    49,
     116,    -1,   116,    -1,   161,   116,    -1,   141,    -1,   143,
      15,   141,    -1,    42,   145,   136,    62,    -1,    75,    -1,
       5,    -1,    60,    -1,    -1,    49,   116,    13,   147,    -1,
     148,    -1,   152,    -1,    74,    -1,    31,    -1,    43,    -1,
      11,    -1,    33,    -1,    41,    34,   153,    61,    -1,    44,
      -1,    50,    -1,    41,   154,    61,    -1,    49,   147,    -1,
     116,   147,    -1,   149,    -1,   151,    -1,   150,    -1,    91,
      -1,    92,    -1,    41,    43,    15,    43,    15,    43,    61,
      -1,    34,    -1,    49,    -1,    34,    23,    34,    -1,    15,
      34,   153,    -1,    -1,   155,    -1,    -1,   156,    -1,   155,
      15,   156,    -1,   147,    -1,    52,    72,    -1,    53,    -1,
       9,    -1,     8,    72,    -1,    68,    -1,    67,    54,    -1,
      70,    -1,    69,    54,    -1,    18,    -1,    17,    54,    -1,
      41,   163,    61,    -1,   164,    -1,   163,   164,    -1,   165,
      -1,   166,    -1,    43,    -1,   152,    -1,    49,    45,   165,
      64,    -1,   116,   168,    -1,    69,   179,    54,   191,   117,
     116,    -1,    67,   179,    54,   191,   117,   116,    -1,    45,
     169,   170,    64,    -1,   171,    -1,   172,    -1,     6,   169,
     170,    -1,    -1,   147,    -1,   173,    -1,   174,    -1,   180,
      -1,   179,    -1,   181,    -1,    38,   116,    -1,   175,    24,
     176,    -1,   177,    -1,   177,    40,    -1,   178,    -1,    40,
     178,    -1,   147,    -1,    46,    -1,   147,    -1,    48,    -1,
      71,   168,    -1,    32,   168,    -1,    89,    16,   182,    -1,
      89,    17,   183,    -1,   168,    -1,   184,    -1,   185,    -1,
      41,   186,    61,    -1,    41,    25,    15,   186,    61,    -1,
     187,    -1,   187,    15,   186,    -1,    49,   188,    -1,   188,
      -1,   189,    -1,   190,    -1,    -1,   168,    -1,    59,    -1,
       3,    -1,    90,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   522,   522,   528,   521,   538,   543,   549,   555,   561,
     565,   568,   574,   577,   581,   580,   590,   593,   598,   604,
     603,   612,   615,   616,   619,   620,   623,   629,   633,   637,
     641,   645,   649,   655,   656,   659,   660,   663,   667,   673,
     674,   677,   689,   694,   699,   706,   708,   713,   715,   720,
     730,   735,   740,   749,   755,   764,   769,   773,   778,   797,
     809,   814,   833,   846,   853,   859,   865,   885,   891,   896,
     902,   907,   916,   923,   928,   933,   945,   959,   966,   973,
     980,   987,   994,  1001,  1007,  1010,  1011,  1014,  1016,  1021,
    1023,  1028,  1030,  1035,  1037,  1042,  1048,  1054,  1057,  1064,
    1071,  1078,  1081,  1083,  1089,  1096,  1098,  1103,  1107,  1113,
    1121,  1126,  1129,  1134,  1139,  1144,  1149,  1153,  1159,  1163,
    1173,  1185,  1189,  1196,  1202,  1208,  1215,  1219,  1225,  1232,
    1236,  1240,  1245,  1251,  1257,  1258,  1261,  1266,  1271,  1276,
    1282,  1288,  1296,  1301,  1305,  1310,  1316,  1322,  1329,  1330,
    1333,  1337,  1343,  1353,  1358,  1364,  1372,  1382,  1387,  1392,
    1397,  1401,  1407,  1413,  1417,  1423,  1427,  1433,  1437,  1443,
    1447,  1453,  1457,  1463,  1469,  1470,  1478,  1479,  1482,  1486,
    1493,  1500,  1501,  1518,  1537,  1540,  1541,  1544,  1545,  1548,
    1552,  1553,  1554,  1557,  1558,  1561,  1567,  1570,  1571,  1574,
    1575,  1578,  1582,  1588,  1592,  1598,  1601,  1607,  1611,  1617,
    1620,  1621,  1624,  1627,  1630,  1631,  1634,  1638,  1644,  1645,
    1646,  1649,  1652,  1656,  1662,  1667
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ABSENT", "ANY", "APPLICATION", "BAR", 
  "BGIN", "BIT", "BITSTRING", "BOOLEAN_kw", "BSTRING", "BY", "CCE", 
  "CHOICE", "COMMA", "COMPONENT", "COMPONENTS", "COMPONENTSOF", "CONTROL", 
  "DEFAULT", "DEFINED", "DEFINITIONS", "DOT", "DOTDOT", "DOTDOTDOT", 
  "ENCRYPTED", "END", "ENUMERATED", "EXPORTS", "EXPLICIT", "L_FALSE", 
  "FROM", "HSTRING", "ID", "IDENTIFIER", "IMPLICIT", "IMPORTS", 
  "INCLUDES", "INTEGER", "LANGLE", "LBRACE", "LBRACKET", "LITNUMBER", 
  "LITSTRING", "LPAREN", "MIN", "MINUS", "MAX", "NAME", "NIL", "OBJECT", 
  "OCTET", "OCTETSTRING", "OF_kw", "OPTIONAL_kw", "PARAMETERTYPE", "PLUS", 
  "PREFIXES", "PRESENT", "PRIVATE", "RBRACE", "RBRACKET", "REAL", 
  "RPAREN", "STAR", "SEMICOLON", "SEQUENCE", "SEQUENCEOF", "SET", "SETOF", 
  "SIZE_kw", "STRING", "TAGS", "L_TRUE", "UNIVERSAL", "VALA", "VALB", 
  "VALI", "VALS", "VALP", "VALO", "VALOID", "VALR", "VALT", "VALTYPE", 
  "VALQ", "VALX", "VLENGTH", "WITH", "SCTRL", "PLUSINFINITY", 
  "MINUSINFINITY", "$accept", "ModuleDefinition", "@1", "@2", 
  "TagDefault", "ModuleIdentifier", "AssignedIdentifier", 
  "ModulePrefixes", "ModuleBody", "Exports", "@3", "SymbolsExported", 
  "Imports", "@4", "SymbolsImported", "SymbolsFromModuleList", 
  "SymbolsFromModule", "SymbolList", "Symbol", "AssignmentList", "String", 
  "Assignment", "Typeassignment", "Type", "Control", "ParameterType", 
  "Valtype", "BuiltinType", "NNlist", "DefinedType", "PassValue", 
  "AnyType", "PassOid", "PassAny", "PassBool", "PassInt", "PassBit", 
  "PassString", "PassReal", "NullPass", "ValParameter", "NamedNumberList", 
  "NamedNumber", "NumericValue", "ElementTypes", "MemberTypes", 
  "OptionalTypeList", "OptionalType", "NamedType", "ComponentsOf", 
  "AlternativeTypeList", "Tag", "Class", "Valueassignment", "Value", 
  "BuiltinValue", "RealValue", "SpecialRealValue", "NumericRealValue", 
  "DefinedValue", "IdentifierList", "Values", "NamedValueList", 
  "NamedValue", "Octetstring", "Bitstring", "SequenceOf", "SetOf", 
  "Components", "ObjectIdentifierValue", "ObjIdComponentList", 
  "ObjIdComponent", "NumberForm", "NameAndNumberForm", "SubType", 
  "SubtypeSpec", "SubtypeAlternative", "SubtypeAlternativeList", 
  "SubtypeValueSet", "SubtypeConstraint", "ContainedSubType", 
  "ValueRange", "LowerEndPoint", "UpperEndpoint", "LowerEndValue", 
  "UpperEndValue", "SizeConstraint", "PermittedAlphabet", 
  "InnerTypeConstraint", "SingleTypeConstraint", 
  "MultipleTypeConstraints", "FullSpecification", "PartialSpecification", 
  "TypeConstraints", "NamedConstraint", "Constraint", "ValueConstraint", 
  "PresenceConstraint", "Sctrl", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    93,    95,    96,    94,    97,    97,    97,    98,    99,
      99,   100,   100,   101,   103,   102,   102,   104,   104,   106,
     105,   105,   107,   107,   108,   108,   109,   110,   110,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   115,   116,   116,   116,   117,   117,   118,   118,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   121,   121,   122,   122,   123,   123,   123,
     123,   123,   123,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   129,   129,   129,   130,   130,
     130,   130,   131,   131,   132,   133,   133,   134,   134,   135,
     136,   136,   137,   137,   138,   138,   139,   139,   140,   140,
     140,   140,   140,   141,   141,   142,   143,   143,   144,   145,
     145,   145,   145,   146,   147,   147,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   149,   149,
     150,   150,   151,   152,   152,   152,   153,   153,   154,   154,
     155,   155,   156,   157,   157,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   163,   163,   164,   164,   165,   165,
     166,   167,   167,   167,   168,   169,   169,   170,   170,   171,
     171,   171,   171,   172,   172,   173,   174,   175,   175,   176,
     176,   177,   177,   178,   178,   179,   180,   181,   181,   182,
     183,   183,   184,   185,   186,   186,   187,   187,   188,   188,
     188,   189,   190,   190,   191,   191
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     0,     0,    10,     2,     2,     0,     2,     1,
       0,     4,     0,     3,     0,     4,     0,     1,     0,     0,
       4,     0,     1,     0,     2,     1,     3,     3,     1,     4,
       2,     4,     2,     1,     1,     2,     0,     1,     1,     1,
       1,     4,     1,     1,     1,     1,     0,     1,     0,     1,
       0,     2,     3,     5,     3,     2,     1,     3,     5,     6,
       3,     5,     6,     3,     3,     2,     7,     3,     2,     3,
       3,     2,     2,     3,     0,     3,     5,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     4,     1,     0,     1,
       0,     1,     0,     1,     0,     2,     1,     1,     1,     2,
       1,     1,     1,     0,     0,     1,     0,     1,     3,     4,
       1,     1,     1,     0,     1,     0,     1,     3,     1,     3,
       4,     1,     2,     2,     1,     2,     1,     3,     4,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     1,     3,     2,     2,     1,     1,     1,
       1,     1,     7,     1,     1,     3,     3,     0,     1,     0,
       1,     3,     1,     2,     1,     1,     2,     1,     2,     1,
       2,     1,     2,     3,     1,     2,     1,     1,     1,     1,
       4,     2,     6,     6,     4,     1,     1,     3,     0,     1,
       1,     1,     1,     1,     1,     2,     3,     1,     2,     1,
       2,     1,     1,     1,     1,     2,     2,     3,     3,     1,
       1,     1,     3,     5,     1,     3,     2,     1,     1,     1,
       0,     1,     1,     1,     1,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,    10,     0,     0,     0,     8,     9,     1,     7,   153,
     178,   154,   179,     0,   174,   176,   177,     0,     0,     0,
       0,     0,   173,   175,     5,     6,     2,   155,   154,     0,
      12,   180,     0,     3,    37,    38,     0,     0,     0,    16,
      11,    14,     0,    21,    18,     4,    19,    36,    33,     0,
      34,     0,     0,    17,    28,    23,    13,    30,    32,    15,
       0,     0,    22,    25,     0,    48,     0,    35,    39,    40,
       0,     0,    27,    20,    24,     0,    47,     0,    85,     0,
     165,    92,   225,     0,    94,   104,    94,   132,     0,    56,
       0,     0,   164,   103,     0,   225,   167,   225,   169,     0,
      42,    43,    90,     0,   104,   104,   225,   225,    44,    29,
      31,    26,     0,     0,   166,    91,    51,   224,    50,    71,
      93,     0,     0,    77,    78,    79,    98,     0,    81,    82,
      83,   100,     0,   106,    84,   101,    74,   130,   131,   129,
       0,     0,    88,   163,   102,    72,    90,   168,     0,     0,
      90,   170,     0,    90,     0,     0,   181,    89,    68,     0,
       0,    65,    55,    96,     0,    74,    97,    50,    50,    41,
       0,    49,    46,     0,   104,    99,    80,   105,    75,     0,
      52,   110,     0,   111,    67,    87,    70,    69,   205,   225,
       0,    57,   225,     0,    60,   139,   137,   140,   104,   159,
     138,   142,   154,    56,   136,   150,   151,     0,   133,   134,
     147,   149,   148,   135,     0,     0,   202,     0,   189,   188,
     185,   186,   190,   191,     0,   197,   193,   192,   194,    64,
      63,    95,    54,    46,    46,    86,    45,     0,     0,     0,
     107,   106,     0,   128,    46,   113,    46,   115,     0,   104,
     138,   162,     0,   158,   160,   145,   146,   206,   195,     0,
       0,     0,     0,     0,   198,     0,     0,     0,     0,     0,
      53,    76,    73,     0,     0,   171,     0,   124,     0,   112,
     116,   118,   121,     0,     0,     0,   114,   104,     0,     0,
       0,   144,     0,   209,   207,   220,   208,   210,   211,   188,
     184,     0,   204,   203,   196,   199,    58,    61,     0,   126,
       0,     0,   108,   183,   172,   123,   122,    59,     0,     0,
      46,   125,   182,    62,   157,   141,     0,   161,   223,     0,
     220,   222,   221,     0,   214,   217,   218,   219,   187,   200,
       0,    66,   109,   117,    46,   119,   156,     0,   220,   216,
     212,   220,   127,   120,     0,     0,   215,   152,   213
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     2,    30,    37,    19,     3,     5,    33,    42,    43,
      44,    52,    47,    55,    61,    62,    63,    64,    54,    56,
      36,    67,    68,   207,   237,    77,   172,   100,   180,   101,
     133,   102,   186,   158,   116,   121,   165,   134,   145,   135,
     178,   239,   240,   182,   278,   285,   279,   280,   281,   282,
     310,   103,   140,    69,   218,   209,   210,   211,   212,   213,
     289,   252,   253,   254,   104,   105,   106,   107,   283,     6,
      13,    14,    15,    16,   108,   156,   219,   262,   220,   221,
     222,   223,   224,   304,   225,   305,   226,   227,   228,   294,
     296,   297,   298,   333,   334,   335,   336,   337,   118
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -242
static const short yypact[] =
{
      10,    33,    97,    88,    21,  -242,  -242,  -242,     3,    93,
    -242,    64,  -242,    91,  -242,  -242,  -242,    44,    63,   105,
     113,    96,  -242,  -242,  -242,  -242,  -242,  -242,  -242,    84,
     107,  -242,    24,  -242,  -242,  -242,    24,   161,    24,   144,
    -242,  -242,   149,   147,    86,  -242,  -242,  -242,  -242,    58,
    -242,    58,   120,   172,  -242,    86,    62,  -242,  -242,  -242,
     133,   131,    86,  -242,    39,   140,   939,  -242,  -242,  -242,
      58,    58,  -242,  -242,  -242,    10,  -242,   176,   177,   132,
    -242,   136,   118,   939,   145,    77,   145,    26,   174,  -242,
     187,   152,  -242,   146,   226,   -42,  -242,   -18,  -242,    -7,
    -242,  -242,   156,   772,   130,   -21,   118,   118,  -242,  -242,
    -242,  -242,   939,   221,  -242,  -242,  -242,  -242,   150,   189,
    -242,   195,   203,  -242,  -242,  -242,  -242,   153,  -242,  -242,
    -242,  -242,   158,   159,  -242,  -242,   197,  -242,  -242,  -242,
     128,   939,   162,  -242,  -242,  -242,   156,  -242,   189,   186,
     -26,  -242,   193,   -26,   553,   217,  -242,  -242,  -242,   939,
     939,   189,  -242,  -242,   165,   197,  -242,   150,   150,   189,
     205,  -242,   238,   213,   793,  -242,  -242,  -242,  -242,   213,
    -242,  -242,   202,  -242,   189,  -242,  -242,  -242,  -242,   118,
     230,  -242,   118,   231,  -242,  -242,  -242,  -242,     1,   620,
    -242,  -242,   352,   151,  -242,  -242,  -242,   419,  -242,  -242,
    -242,  -242,  -242,  -242,   189,   939,  -242,    87,   -10,   267,
    -242,  -242,  -242,  -242,   251,   236,  -242,  -242,  -242,   189,
     189,  -242,  -242,   238,   238,  -242,  -242,   237,   232,    20,
    -242,   159,    28,  -242,   238,   839,   238,   839,   245,    45,
     266,  -242,   222,   275,  -242,  -242,  -242,  -242,   189,   189,
     256,   217,   228,   285,  -242,   939,   939,   989,   128,   213,
    -242,  -242,  -242,   939,   244,  -242,   722,   189,   239,   286,
    -242,    12,  -242,   939,   939,   241,   286,   641,   269,   243,
     262,  -242,   553,  -242,  -242,     2,  -242,  -242,  -242,   267,
    -242,   486,  -242,  -242,  -242,  -242,   189,   189,   889,  -242,
      30,   246,  -242,   189,  -242,   189,  -242,  -242,   839,   553,
     238,   189,   189,  -242,   292,  -242,   297,  -242,  -242,   299,
      31,  -242,  -242,   254,   302,  -242,  -242,  -242,  -242,  -242,
     989,  -242,  -242,  -242,   238,  -242,  -242,   277,    53,  -242,
    -242,    53,  -242,  -242,   260,   261,  -242,  -242,  -242
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -242,  -242,  -242,  -242,  -242,   248,  -242,  -242,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,  -242,   268,   287,   123,  -242,
       4,  -242,  -242,   -66,  -225,  -242,    52,  -242,   167,  -242,
    -172,   247,  -242,    42,  -242,   253,  -242,   240,  -242,   235,
     101,   164,    76,    78,  -242,  -242,   100,    40,  -241,    73,
    -242,  -242,  -242,  -242,  -150,  -242,  -242,  -242,  -242,    -3,
      27,  -242,  -242,    65,  -242,  -242,  -242,  -242,  -242,  -242,
    -242,   351,   344,  -242,  -242,  -145,   106,    69,  -242,  -242,
    -242,  -242,  -242,  -242,  -242,    68,    49,  -242,  -242,  -242,
    -242,  -242,  -242,  -210,  -242,    41,  -242,  -242,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -202
static const short yytable[] =
{
      99,    12,   241,   188,   208,   328,   154,  -153,   265,   266,
      12,   150,   147,   153,  -201,   -50,  -153,   119,    12,   273,
    -153,   284,   167,   168,   248,  -153,   309,   329,  -153,   148,
    -201,   137,   319,    17,   328,   269,   151,   161,   155,    18,
      38,  -153,    40,   269,     1,   340,   169,   155,   117,   251,
     157,   330,   255,   148,    60,     9,   328,   256,    34,   171,
     288,   331,  -153,   163,    10,  -153,   164,   320,   248,   257,
      11,    75,   117,    35,     4,   184,   155,   123,   124,   125,
     126,   270,   127,   128,   129,   130,   138,   131,   132,   272,
     331,   341,    48,   229,   230,   345,    65,     7,   155,   352,
     122,   139,   330,   259,   260,   244,  -153,    50,   246,    21,
       8,    66,   331,   303,   293,   241,    20,    24,    26,   353,
      48,   123,   124,   125,   126,     9,   127,   128,   129,   130,
       9,   131,   132,    49,    10,    50,    25,   183,   355,    10,
      11,   356,   251,    51,   149,    28,   152,    27,    31,   258,
     332,   303,    22,   123,   124,   125,   126,  -143,   127,   128,
     129,   130,     9,   131,   132,    32,  -143,    48,    39,   344,
    -143,   181,    57,    41,    58,  -143,    45,    28,  -143,   277,
      70,   277,    50,    72,    46,   332,    59,    60,   187,   112,
      71,  -143,   191,   109,   110,   194,    76,    73,   113,   306,
     307,   277,   190,   332,   114,   193,   332,   313,   117,   126,
     315,   127,  -143,   115,   141,  -143,   131,   321,   322,   233,
     234,    78,   142,   120,   143,    79,    80,    81,   195,   144,
      78,    82,   157,   170,   155,   171,   173,   174,   179,   177,
     189,   175,   315,    83,   185,    84,   176,   192,   196,   214,
     197,   198,   277,   231,   235,   215,    86,   236,   199,    87,
     200,   201,   238,   216,   243,   183,   202,   203,    90,    91,
      92,   245,   247,   261,   277,   263,   264,   268,   267,   287,
      93,   290,    94,   291,    95,    96,    97,    98,   148,    78,
     292,   204,   300,    79,    80,    81,   195,   295,   314,    82,
     317,   318,   323,   324,   325,   326,   217,   288,   205,   206,
     342,    83,   347,    84,   348,   350,   196,   351,   197,   198,
     354,   357,   358,   111,    86,   301,   199,    87,   200,   201,
      74,    53,   232,   302,   202,   203,    90,    91,    92,   136,
     166,   146,   271,   242,   162,   312,   311,   286,    93,   316,
      94,   346,    95,    96,    97,    98,    78,   327,   343,   204,
      79,    80,    81,   195,    23,    29,    82,   299,   338,   339,
       0,   349,     0,     0,     0,     0,   205,   206,    83,     0,
      84,     0,     0,   196,     0,   197,   198,     0,     0,     0,
       0,    86,   141,   199,    87,   200,   201,     0,     0,     0,
       0,   202,   203,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,     0,    94,     0,    95,
      96,    97,    98,    78,     0,     0,   204,    79,    80,    81,
     195,     0,     0,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   205,   206,    83,     0,    84,     0,     0,
     196,     0,   197,   198,     0,     0,     0,     0,    86,     0,
     199,    87,   200,   201,   155,     0,     0,     0,   202,   203,
      90,    91,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,    94,     0,    95,    96,    97,    98,
      78,     0,     0,   204,    79,    80,    81,   195,     0,     0,
      82,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     205,   206,    83,     0,    84,     0,     0,   196,     0,   197,
     198,     0,     0,     0,     0,    86,     0,   199,    87,   200,
     201,     0,     0,     0,   302,   202,   203,    90,    91,    92,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    93,
       0,    94,     0,    95,    96,    97,    98,    78,     0,     0,
     204,    79,    80,    81,   195,     0,     0,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   205,   206,    83,
       0,    84,     0,     0,   196,     0,   197,   198,     0,     0,
       0,     0,    86,     0,   199,    87,   200,   201,     0,     0,
       0,     0,   202,   203,    90,    91,    92,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,     0,    94,     0,
      95,    96,    97,    98,    78,     0,     0,   204,    79,    80,
      81,   195,     0,     0,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   205,   206,    83,  -155,    84,     0,
       0,   196,     0,   197,   249,     0,  -155,     0,     0,    86,
    -155,   199,    87,   250,   201,  -155,     0,     0,  -155,   202,
     203,    90,    91,    92,     0,     0,     0,     0,     0,     0,
       0,  -155,     0,    93,     0,    94,     0,    95,    96,    97,
      98,     0,     0,     0,   204,     0,     0,     0,     0,     0,
       0,     0,  -155,     0,     0,  -155,     0,     0,     0,     0,
       0,   205,   206,     0,     0,     0,     0,   123,   124,   125,
     126,     0,   127,   128,   129,   130,    78,   131,   132,     0,
      79,    80,    81,     0,     0,     0,    82,     0,     0,   274,
     275,     0,     0,     0,     0,     0,     0,     0,    83,     0,
      84,     0,     0,     0,     0,     0,    85,     0,     0,     0,
       0,    86,   141,     0,    87,     0,     0,     0,     0,     0,
       0,    88,    89,    90,    91,    92,    78,     0,     0,     0,
      79,    80,    81,     0,     0,    93,    82,    94,     0,    95,
      96,    97,    98,     0,     0,     0,     0,     0,    83,     0,
      84,     0,   159,     0,     0,     0,    85,     0,   160,     0,
       0,    86,     0,     0,    87,     0,     0,     0,     0,     0,
       0,    88,    89,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    93,     0,    94,     0,    95,
      96,    97,    98,    78,     0,     0,     0,    79,    80,    81,
       0,     0,     0,    82,     0,     0,   274,   275,     0,     0,
       0,     0,     0,     0,     0,    83,     0,    84,     0,   123,
     124,   125,   126,    85,   127,   128,   129,   130,    86,   131,
     132,    87,     0,     0,     0,     0,     0,     0,   276,    89,
      90,    91,    92,    78,     0,     0,     0,    79,    80,    81,
       0,     0,    93,    82,    94,     0,    95,    96,    97,    98,
       0,     0,     0,     0,     0,    83,     0,    84,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,    86,   141,
       0,    87,     0,     0,     0,     0,     0,     0,    88,    89,
      90,    91,    92,    78,     0,     0,     0,    79,    80,    81,
       0,     0,    93,    82,    94,     0,    95,    96,    97,    98,
       0,     0,     0,     0,     0,    83,     0,    84,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,    86,     0,
       0,    87,     0,     0,     0,     0,     0,     0,    88,    89,
      90,    91,    92,    78,     0,     0,     0,    79,    80,    81,
       0,     0,    93,    82,    94,     0,    95,    96,    97,    98,
       0,     0,     0,     0,     0,    83,     0,    84,     0,     0,
       0,     0,     0,    85,     0,     0,     0,     0,    86,     0,
       0,    87,     0,     0,     0,     0,     0,     0,   308,    89,
      90,    91,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,     0,    94,     0,    95,    96,    97,    98
};

static const short yycheck[] =
{
      66,     4,   174,   148,   154,     3,    13,     6,   233,   234,
      13,    95,    54,    97,    24,    41,    15,    83,    21,   244,
      19,   246,   106,   107,    23,    24,   267,    25,    27,    71,
      40,     5,    20,    30,     3,    15,    54,   103,    45,    36,
      36,    40,    38,    15,    34,    15,   112,    45,    90,   199,
      76,    49,   202,    71,    15,    34,     3,   207,    34,    85,
      15,    59,    61,    84,    43,    64,    87,    55,    23,   214,
      49,    32,    90,    49,    41,   141,    45,    76,    77,    78,
      79,    61,    81,    82,    83,    84,    60,    86,    87,    61,
      59,    61,    34,   159,   160,   320,    34,     0,    45,   340,
      23,    75,    49,    16,    17,   189,    61,    49,   192,    45,
      22,    49,    59,   263,   259,   287,    23,    73,    13,   344,
      34,    76,    77,    78,    79,    34,    81,    82,    83,    84,
      34,    86,    87,    47,    43,    49,    73,   140,   348,    43,
      49,   351,   292,    57,    95,    49,    97,    34,    64,   215,
     295,   301,    61,    76,    77,    78,    79,     6,    81,    82,
      83,    84,    34,    86,    87,    58,    15,    34,     7,   319,
      19,    43,    49,    29,    51,    24,    27,    49,    27,   245,
      47,   247,    49,    60,    37,   330,    66,    15,   146,    13,
      57,    40,   150,    70,    71,   153,    56,    66,    21,   265,
     266,   267,   150,   348,    72,   153,   351,   273,    90,    79,
     276,    81,    61,    77,    40,    64,    86,   283,   284,   167,
     168,     4,    35,    78,    72,     8,     9,    10,    11,    83,
       4,    14,    76,    12,    45,    85,    41,    34,    41,    80,
      54,    88,   308,    26,    82,    28,    88,    54,    31,    32,
      33,    34,   318,    88,    49,    38,    39,    19,    41,    42,
      43,    44,    49,    46,    62,   268,    49,    50,    51,    52,
      53,    41,    41,     6,   340,    24,    40,    45,    41,    34,
      63,    15,    65,    61,    67,    68,    69,    70,    71,     4,
      15,    74,    64,     8,     9,    10,    11,    41,    54,    14,
      61,    15,    61,    34,    61,    43,    89,    15,    91,    92,
      64,    26,    15,    28,    15,    61,    31,    15,    33,    34,
      43,    61,    61,    75,    39,    40,    41,    42,    43,    44,
      62,    44,   165,    48,    49,    50,    51,    52,    53,    86,
     105,    94,   241,   179,   104,   269,   268,   247,    63,   276,
      65,   324,    67,    68,    69,    70,     4,   292,   318,    74,
       8,     9,    10,    11,    13,    21,    14,   261,   299,   301,
      -1,   330,    -1,    -1,    -1,    -1,    91,    92,    26,    -1,
      28,    -1,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,    67,
      68,    69,    70,     4,    -1,    -1,    74,     8,     9,    10,
      11,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    91,    92,    26,    -1,    28,    -1,    -1,
      31,    -1,    33,    34,    -1,    -1,    -1,    -1,    39,    -1,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    65,    -1,    67,    68,    69,    70,
       4,    -1,    -1,    74,     8,     9,    10,    11,    -1,    -1,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      91,    92,    26,    -1,    28,    -1,    -1,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    39,    -1,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      -1,    65,    -1,    67,    68,    69,    70,     4,    -1,    -1,
      74,     8,     9,    10,    11,    -1,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    26,
      -1,    28,    -1,    -1,    31,    -1,    33,    34,    -1,    -1,
      -1,    -1,    39,    -1,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,
      67,    68,    69,    70,     4,    -1,    -1,    74,     8,     9,
      10,    11,    -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    26,     6,    28,    -1,
      -1,    31,    -1,    33,    34,    -1,    15,    -1,    -1,    39,
      19,    41,    42,    43,    44,    24,    -1,    -1,    27,    49,
      50,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    -1,    63,    -1,    65,    -1,    67,    68,    69,
      70,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    64,    -1,    -1,    -1,    -1,
      -1,    91,    92,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,     4,    86,    87,    -1,
       8,     9,    10,    -1,    -1,    -1,    14,    -1,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    39,    40,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,     4,    -1,    -1,    -1,
       8,     9,    10,    -1,    -1,    63,    14,    65,    -1,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    26,    -1,
      28,    -1,    30,    -1,    -1,    -1,    34,    -1,    36,    -1,
      -1,    39,    -1,    -1,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    50,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    65,    -1,    67,
      68,    69,    70,     4,    -1,    -1,    -1,     8,     9,    10,
      -1,    -1,    -1,    14,    -1,    -1,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    28,    -1,    76,
      77,    78,    79,    34,    81,    82,    83,    84,    39,    86,
      87,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,     4,    -1,    -1,    -1,     8,     9,    10,
      -1,    -1,    63,    14,    65,    -1,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    39,    40,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,     4,    -1,    -1,    -1,     8,     9,    10,
      -1,    -1,    63,    14,    65,    -1,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,     4,    -1,    -1,    -1,     8,     9,    10,
      -1,    -1,    63,    14,    65,    -1,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    -1,    65,    -1,    67,    68,    69,    70
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    34,    94,    98,    41,    99,   162,     0,    22,    34,
      43,    49,   152,   163,   164,   165,   166,    30,    36,    97,
      23,    45,    61,   164,    73,    73,    13,    34,    49,   165,
      95,    64,    58,   100,    34,    49,   113,    96,   113,     7,
     113,    29,   101,   102,   103,    27,    37,   105,    34,    47,
      49,    57,   104,   110,   111,   106,   112,   111,   111,    66,
      15,   107,   108,   109,   110,    34,    49,   114,   115,   146,
      47,    57,   111,    66,   109,    32,    56,   118,     4,     8,
       9,    10,    14,    26,    28,    34,    39,    42,    49,    50,
      51,    52,    53,    63,    65,    67,    68,    69,    70,   116,
     120,   122,   124,   144,   157,   158,   159,   160,   167,   111,
     111,    98,    13,    21,    72,    77,   127,    90,   191,   116,
      78,   128,    23,    76,    77,    78,    79,    81,    82,    83,
      84,    86,    87,   123,   130,   132,   128,     5,    60,    75,
     145,    40,    35,    72,    83,   131,   124,    54,    71,   179,
     191,    54,   179,   191,    13,    45,   168,    76,   126,    30,
      36,   116,   130,    84,    87,   129,   132,   191,   191,   116,
      12,    85,   119,    41,    34,    88,    88,    80,   133,    41,
     121,    43,   136,   152,   116,    82,   125,   126,   168,    54,
     119,   126,    54,   119,   126,    11,    31,    33,    34,    41,
      43,    44,    49,    50,    74,    91,    92,   116,   147,   148,
     149,   150,   151,   152,    32,    38,    46,    89,   147,   169,
     171,   172,   173,   174,   175,   177,   179,   180,   181,   116,
     116,    88,   121,   119,   119,    49,    19,   117,    49,   134,
     135,   123,   134,    62,   191,    41,   191,    41,    23,    34,
      43,   147,   154,   155,   156,   147,   147,   168,   116,    16,
      17,     6,   170,    24,    40,   117,   117,    41,    45,    15,
      61,   133,    61,   117,    17,    18,    49,   116,   137,   139,
     140,   141,   142,   161,   117,   138,   139,    34,    15,   153,
      15,    61,    15,   168,   182,    41,   183,   184,   185,   169,
      64,    40,    48,   147,   176,   178,   116,   116,    49,   141,
     143,   136,   135,   116,    54,   116,   142,    61,    15,    20,
      55,   116,   116,    61,    34,    61,    43,   156,     3,    25,
      49,    59,   168,   186,   187,   188,   189,   190,   170,   178,
      15,    61,    64,   140,   147,   117,   153,    15,    15,   188,
      61,    15,   141,   117,    43,   186,   186,    61,    61
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrlab1

/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)         \
  Current.first_line   = Rhs[1].first_line;      \
  Current.first_column = Rhs[1].first_column;    \
  Current.last_line    = Rhs[N].last_line;       \
  Current.last_column  = Rhs[N].last_column;
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (cinluded).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylineno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylineno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 522 "yacc.y"
    {
                            mymodule = yyvsp[-3].yy_string;
                            mymoduleid = modid;
                            pass1 ();
                        ;}
    break;

  case 3:
#line 528 "yacc.y"
    {
                            start_actions++;
                        ;}
    break;

  case 4:
#line 532 "yacc.y"
    {
                            pass2 ();
                            final_actions++;
                        ;}
    break;

  case 5:
#line 539 "yacc.y"
    { 
                            tagdefault = 0;
                            tagcontrol = TAG_EXPLICIT;
                        ;}
    break;

  case 6:
#line 544 "yacc.y"
    {
                            tagdefault = YP_IMPLICIT;
                            tagcontrol = TAG_IMPLICIT;
                        ;}
    break;

  case 7:
#line 549 "yacc.y"
    {
                            tagdefault = 0;
                            tagcontrol = TAG_UNKNOWN;
                        ;}
    break;

  case 8:
#line 556 "yacc.y"
    {
                             yyval.yy_string = yyvsp[-1].yy_string;
                         ;}
    break;

  case 9:
#line 562 "yacc.y"
    {
                             modid = yyvsp[0].yy_oid;
                         ;}
    break;

  case 11:
#line 569 "yacc.y"
    {
                            yyencdflt = yyvsp[-2].yy_string;
                            yydecdflt = yyvsp[-1].yy_string;
                            yyprfdflt = yyvsp[0].yy_string;
                        ;}
    break;

  case 14:
#line 581 "yacc.y"
    {
                            listtype = TBL_EXPORT;
                            doexternals = 0;
                            yyporting = 1;
                        ;}
    break;

  case 15:
#line 587 "yacc.y"
    {
                            yyporting = 0;
                        ;}
    break;

  case 17:
#line 594 "yacc.y"
    {
                            yyval.yy_string = yyvsp[0].yy_string;
                        ;}
    break;

  case 18:
#line 598 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 19:
#line 604 "yacc.y"
    {
                            listtype = TBL_IMPORT;
                            yyporting = 1;
                        ;}
    break;

  case 20:
#line 609 "yacc.y"
    {
                            yyporting = 0;
                        ;}
    break;

  case 26:
#line 624 "yacc.y"
    {
                            addtableref (yyvsp[0].yy_string, modid, listtype);
                        ;}
    break;

  case 27:
#line 630 "yacc.y"
    {
                            addtable(yyvsp[0].yy_string, listtype, ER_UNKNOWN);
                        ;}
    break;

  case 28:
#line 634 "yacc.y"
    {
                            addtable (yyvsp[0].yy_string, listtype, ER_UNKNOWN);
                        ;}
    break;

  case 29:
#line 638 "yacc.y"
    {
                            addtable(yyvsp[0].yy_string, listtype, ER_NORMAL);
                        ;}
    break;

  case 30:
#line 642 "yacc.y"
    {
                            addtable (yyvsp[0].yy_string, listtype, ER_NORMAL);
                        ;}
    break;

  case 31:
#line 646 "yacc.y"
    {
                            addtable(yyvsp[0].yy_string, listtype, ER_EXPLICIT);
                        ;}
    break;

  case 32:
#line 650 "yacc.y"
    {
                            addtable (yyvsp[0].yy_string, listtype, ER_EXPLICIT);
                        ;}
    break;

  case 37:
#line 664 "yacc.y"
    {
                            yyval.yy_string = yyvsp[0].yy_string;
                        ;}
    break;

  case 38:
#line 668 "yacc.y"
    {
                            yyval.yy_string = yyvsp[0].yy_string;
                        ;}
    break;

  case 41:
#line 678 "yacc.y"
    {
                            if (yyvsp[-2].yy_string)
                            {
                                yyvsp[0].yy_type->yp_param_type = yyvsp[-2].yy_string;
                            }

                            pass1_type(yyencpref, yydecpref, yyprfpref,
                                       mymodule, yyvsp[-3].yy_string, yyvsp[0].yy_type);
                        ;}
    break;

  case 42:
#line 690 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_direction = yysection;
                        ;}
    break;

  case 43:
#line 695 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_direction = yysection;
                        ;}
    break;

  case 44:
#line 700 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_direction = yysection;
                        ;}
    break;

  case 46:
#line 708 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 48:
#line 715 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 49:
#line 721 "yacc.y"
    {
                            yyval.yy_type = new_type(YP_UNDF, -1);
                            if (setvaltype(yyval.yy_type, yyvsp[0].yy_string) == 0)
                            {
                                yyerror("syntax error in [[ T ... ]]");
                            }
                            free(yyvsp[0].yy_string);
                        ;}
    break;

  case 50:
#line 730 "yacc.y"
    {
                            yyval.yy_type = new_type(YP_UNDF, -1);
                        ;}
    break;

  case 51:
#line 736 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_BOOL, yyvsp[-1].yy_number);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                        ;}
    break;

  case 52:
#line 741 "yacc.y"
    {
                            yyval.yy_type = new_type (yyvsp[0].yy_value ? YP_INTLIST : YP_INT, yyvsp[-2].yy_number);
                            yyval.yy_type->yp_intexp = yyvsp[-1].yy_string;
                            if (yyvsp[0].yy_value)
                            {
                                    yyval.yy_type->yp_value = yyvsp[0].yy_value;
                            }
                        ;}
    break;

  case 53:
#line 750 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_ENUMLIST, yyvsp[-4].yy_number);
                            yyval.yy_type->yp_intexp = yyvsp[-3].yy_string;
                            yyval.yy_type->yp_value = yyvsp[-1].yy_value;
                        ;}
    break;

  case 54:
#line 756 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-1].yy_type;
                            yyval.yy_type->yp_code = yyvsp[0].yy_value ? YP_BITLIST: YP_BIT;
                            if (yyvsp[0].yy_value)
                            {
                                yyval.yy_type->yp_value = yyvsp[0].yy_value;
                            }
                        ;}
    break;

  case 55:
#line 765 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_code = YP_OCT;
                        ;}
    break;

  case 56:
#line 770 "yacc.y"
    {
                            yyval.yy_type = new_type(YP_NULL, yyvsp[0].yy_number);
                        ;}
    break;

  case 57:
#line 774 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_SEQ, yyvsp[-2].yy_number);
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                        ;}
    break;

  case 58:
#line 779 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-2].yy_type;
                            yyval.yy_type->yp_code = YP_SEQTYPE;
                            yyval.yy_type->yp_type = yyvsp[0].yy_type;

                            if (yyvsp[-3].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-3].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-3].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-3].yy_sctrl);
                            }

                            if (yyvsp[-1].yy_string)
                            {
                                yyval.yy_type->yp_control = yyvsp[-1].yy_string;
                                yyval.yy_type->yp_flags |= YP_CONTROLLED;
                            }
                        ;}
    break;

  case 59:
#line 798 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-3].yy_type;
                            yyval.yy_type->yp_code = YP_SEQLIST;
                            yyval.yy_type->yp_type = yyvsp[-1].yy_type;
                            if (yyvsp[-4].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-4].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-4].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-4].yy_sctrl);
                            }
                        ;}
    break;

  case 60:
#line 810 "yacc.y"
    {
                            yyval.yy_type = new_type(YP_SET, yyvsp[-2].yy_number);
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                        ;}
    break;

  case 61:
#line 815 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-2].yy_type;
                            yyval.yy_type->yp_code = YP_SETTYPE;
                            yyval.yy_type->yp_type = yyvsp[0].yy_type;

                            if (yyvsp[-3].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-3].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-3].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-3].yy_sctrl);
                            }
                            if (yyvsp[-1].yy_string)
                            {
                                yyval.yy_type->yp_control = yyvsp[-1].yy_string;
                                yyval.yy_type->yp_flags |= YP_CONTROLLED;
                            }
                        ;}
    break;

  case 62:
#line 834 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-3].yy_type;
                            yyval.yy_type->yp_code = YP_SETLIST;
                            yyval.yy_type->yp_type = yyvsp[-1].yy_type;

                            if (yyvsp[-4].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-4].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-4].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-4].yy_sctrl);
                            }
                        ;}
    break;

  case 63:
#line 847 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_tag = yyvsp[-2].yy_tag;
                            yyval.yy_type->yp_flags |= (YP_IMPLICIT | YP_TAG);

                        ;}
    break;

  case 64:
#line 854 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_tag = yyvsp[-2].yy_tag;
                            yyval.yy_type->yp_flags |= YP_TAG;
                        ;}
    break;

  case 65:
#line 860 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_tag = yyvsp[-1].yy_tag;
                            yyval.yy_type->yp_flags |= (YP_TAG| tagdefault);
                        ;}
    break;

  case 66:
#line 867 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-4].yy_type;
                            yyval.yy_type->yp_code = YP_CHOICE;
                            yyval.yy_type->yp_type = yyvsp[-1].yy_type;

                            if (yyvsp[-5].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-5].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-5].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-5].yy_sctrl);
                            }

                            if (yyvsp[-3].yy_string)
                            {
                                yyval.yy_type->yp_control = yyvsp[-3].yy_string;
                                yyval.yy_type->yp_flags |= YP_CONTROLLED;
                            }
                        ;}
    break;

  case 67:
#line 886 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_bound = yyvsp[-2].yy_string;
                            yyval.yy_type->yp_flags |= YP_BOUND;
                        ;}
    break;

  case 68:
#line 892 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_ANY, yyvsp[-1].yy_number);
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                        ;}
    break;

  case 69:
#line 897 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_ANY, yyvsp[-1].yy_number);
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_flags |= YP_WANTIMPLICIT;
                        ;}
    break;

  case 70:
#line 903 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_OID, yyvsp[-2].yy_number);
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                        ;}
    break;

  case 71:
#line 908 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_tag = new_tag (PE_CLASS_UNIV);
                            yyval.yy_type->yp_tag->yt_value = new_value(YV_NUMBER);
                            yyval.yy_type->yp_tag->yt_value->yv_number = PE_PRIM_ENCR;
                            yyval.yy_type->yp_flags |=
                                    (YP_ENCRYPTED | YP_TAG | YP_IMPLICIT);
                        ;}
    break;

  case 72:
#line 917 "yacc.y"
    {
                            yyval.yy_type = new_type(YP_REAL, yyvsp[-1].yy_number);
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                        ;}
    break;

  case 73:
#line 924 "yacc.y"
    {
                            yyval.yy_value = yyvsp[-1].yy_value;
                        ;}
    break;

  case 74:
#line 928 "yacc.y"
    {
                            yyval.yy_value = NULL;
                        ;}
    break;

  case 75:
#line 934 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-1].yy_type;
                            yyval.yy_type->yp_code = YP_IDEFINED;
                            yyval.yy_type->yp_identifier = yyvsp[-2].yy_string;
                            if (yyvsp[0].yy_string)
                            {
                                yyval.yy_type->yp_parm = yyvsp[0].yy_string;
                                yyval.yy_type->yp_flags |= YP_PARMVAL;
                            }
                            check_impexp (yyval.yy_type);
                        ;}
    break;

  case 76:
#line 946 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-1].yy_type;
                            yyval.yy_type->yp_code = YP_IDEFINED;
                            yyval.yy_type->yp_identifier = yyvsp[-2].yy_string;
                            yyval.yy_type->yp_module = yyvsp[-4].yy_string;
                            if (yyvsp[0].yy_string)
                            {
                                yyval.yy_type->yp_parm = yyvsp[0].yy_string;
                                yyval.yy_type->yp_flags |= YP_PARMVAL;
                            }
                        ;}
    break;

  case 77:
#line 960 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = NULL;
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_prfexp = 'a';
                        ;}
    break;

  case 78:
#line 967 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_strexp = NULL;
                            yyval.yy_type->yp_prfexp = 'b';
                        ;}
    break;

  case 79:
#line 974 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_strexp = NULL;
                            yyval.yy_type->yp_prfexp = 'i';
                        ;}
    break;

  case 80:
#line 981 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_strexp = yyvsp[-1].yy_string;
                            yyval.yy_type->yp_prfexp = 'x';
                        ;}
    break;

  case 81:
#line 988 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = NULL;
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_prfexp = 'O';
                        ;}
    break;

  case 82:
#line 995 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = NULL;
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_prfexp = 'r';
                        ;}
    break;

  case 83:
#line 1002 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_prfexp = 't';
                        ;}
    break;

  case 88:
#line 1016 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 90:
#line 1023 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 92:
#line 1030 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 94:
#line 1037 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 95:
#line 1043 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_strexp = yyvsp[-1].yy_string;
                        ;}
    break;

  case 96:
#line 1049 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_strexp = NULL;
                        ;}
    break;

  case 98:
#line 1058 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = NULL;
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_prfexp = 's';
                        ;}
    break;

  case 99:
#line 1065 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_strexp = yyvsp[-1].yy_string;
                            yyval.yy_type->yp_prfexp = 'o';
                        ;}
    break;

  case 100:
#line 1072 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = NULL;
                            yyval.yy_type->yp_strexp = yyvsp[0].yy_string;
                            yyval.yy_type->yp_prfexp = 'q';
                        ;}
    break;

  case 103:
#line 1083 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 104:
#line 1089 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_UNDF, -1);
                            yyval.yy_type->yp_intexp = NULL;
                            yyval.yy_type->yp_strexp = NULL;
                        ;}
    break;

  case 106:
#line 1098 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 107:
#line 1104 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 108:
#line 1108 "yacc.y"
    {
                            yyval.yy_value = add_value (yyvsp[-2].yy_value, yyvsp[0].yy_value);
                        ;}
    break;

  case 109:
#line 1114 "yacc.y"
    {
                            yyval.yy_value = yyvsp[-1].yy_value;
                            yyval.yy_value->yv_named = yyvsp[-3].yy_string;
                            yyval.yy_value->yv_flags |= YV_NAMED;
                        ;}
    break;

  case 110:
#line 1122 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_NUMBER);
                            yyval.yy_value->yv_number = yyvsp[0].yy_number;
                        ;}
    break;

  case 112:
#line 1130 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 113:
#line 1134 "yacc.y"
    {
                            yyval.yy_type = NULL;
                        ;}
    break;

  case 114:
#line 1140 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 115:
#line 1144 "yacc.y"
    {
                            yyval.yy_type = NULL;
                        ;}
    break;

  case 116:
#line 1150 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 117:
#line 1154 "yacc.y"
    {
                            yyval.yy_type = add_type (yyvsp[-2].yy_type, yyvsp[0].yy_type);
                        ;}
    break;

  case 118:
#line 1160 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 119:
#line 1164 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-2].yy_type;
                            yyval.yy_type->yp_flags |= YP_OPTIONAL;
                            if (yyvsp[0].yy_string)
                            {
                                yyval.yy_type->yp_optcontrol = yyvsp[0].yy_string;
                                yyval.yy_type->yp_flags |= YP_OPTCONTROL;
                            }
                        ;}
    break;

  case 120:
#line 1174 "yacc.y"
    {
                            yyval.yy_type = yyvsp[-3].yy_type;
                            yyval.yy_type->yp_default = yyvsp[-1].yy_value;
                            yyval.yy_type->yp_flags |= YP_DEFAULT;

                            if (yyvsp[0].yy_string)
                            {
                                yyval.yy_type->yp_optcontrol = yyvsp[0].yy_string;
                                yyval.yy_type->yp_flags |= YP_OPTCONTROL;
                            }
                        ;}
    break;

  case 121:
#line 1186 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 122:
#line 1190 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_id = yyvsp[-1].yy_string;
                        ;}
    break;

  case 123:
#line 1197 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_id = yyvsp[-1].yy_string;
                            yyval.yy_type->yp_flags |= YP_ID;
                        ;}
    break;

  case 124:
#line 1203 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 125:
#line 1209 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                            yyval.yy_type->yp_flags |= YP_COMPONENTS;
                        ;}
    break;

  case 126:
#line 1216 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 127:
#line 1220 "yacc.y"
    {
                            yyval.yy_type = add_type (yyvsp[-2].yy_type, yyvsp[0].yy_type);
                        ;}
    break;

  case 128:
#line 1226 "yacc.y"
    {
                            yyval.yy_tag = yyvsp[-2].yy_tag;
                            yyval.yy_tag->yt_value = yyvsp[-1].yy_value;
                        ;}
    break;

  case 129:
#line 1233 "yacc.y"
    {
                            yyval.yy_tag = new_tag (PE_CLASS_UNIV);
                        ;}
    break;

  case 130:
#line 1237 "yacc.y"
    {
                            yyval.yy_tag = new_tag (PE_CLASS_APPL);
                        ;}
    break;

  case 131:
#line 1241 "yacc.y"
    {
                            yyval.yy_tag = new_tag (PE_CLASS_PRIV);
                        ;}
    break;

  case 132:
#line 1245 "yacc.y"
    {
                            yyval.yy_tag = new_tag (PE_CLASS_CONT);
                        ;}
    break;

  case 133:
#line 1252 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 136:
#line 1262 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_BOOL);
                            yyval.yy_value->yv_number = 1;
                        ;}
    break;

  case 137:
#line 1267 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_BOOL);
                            yyval.yy_value->yv_number = 0;
                        ;}
    break;

  case 138:
#line 1272 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_NUMBER);
                            yyval.yy_value->yv_number = yyvsp[0].yy_number;
                        ;}
    break;

  case 139:
#line 1277 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_BSTRING);
                            yyval.yy_value->yv_xstring = bit2bin(yyvsp[0].yy_string, &yyval.yy_value->yv_xlength);
                            free(yyvsp[0].yy_string);
                        ;}
    break;

  case 140:
#line 1283 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_HSTRING);
                            yyval.yy_value->yv_xstring = hex2bin(yyvsp[0].yy_string, &yyval.yy_value->yv_xlength);
                            free(yyvsp[0].yy_string);
                        ;}
    break;

  case 141:
#line 1289 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_IDLIST);
                            yyval.yy_value->yv_idlist = new_value (YV_IDEFINED);
                            yyval.yy_value->yv_idlist->yv_identifier = yyvsp[-2].yy_string;
                            if (yyvsp[-1].yy_value)
                                yyval.yy_value = add_value (yyval.yy_value, yyvsp[-1].yy_value);
                        ;}
    break;

  case 142:
#line 1297 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_STRING);
                            yyval.yy_value->yv_string = yyvsp[0].yy_string;
                        ;}
    break;

  case 143:
#line 1302 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_NULL);
                        ;}
    break;

  case 144:
#line 1306 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_VALIST);
                            yyval.yy_value->yv_idlist = yyvsp[-1].yy_value;
                        ;}
    break;

  case 145:
#line 1311 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                            yyval.yy_value->yv_id = yyvsp[-1].yy_string;
                            yyval.yy_value->yv_flags |= YV_ID;
                        ;}
    break;

  case 146:
#line 1317 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                            yyval.yy_value->yv_type = yyvsp[-1].yy_type;
                            yyval.yy_value->yv_flags |= YV_TYPE;
                        ;}
    break;

  case 147:
#line 1323 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_REAL);
                            yyval.yy_value->yv_real = yyvsp[0].yy_real;
                        ;}
    break;

  case 150:
#line 1334 "yacc.y"
    {
                            yyval.yy_real = PE_REAL_INFINITY;
                        ;}
    break;

  case 151:
#line 1338 "yacc.y"
    {
                            yyval.yy_real = - PE_REAL_INFINITY;
                        ;}
    break;

  case 152:
#line 1344 "yacc.y"
    {
                                if (yyvsp[-3].yy_number != 2 && yyvsp[-3].yy_number != 10)
                                {
                                        myyerror ("Illegal base value %d", yyvsp[-3].yy_number);
                                }
                                yyval.yy_real = yyvsp[-5].yy_number * pow ((double)yyvsp[-3].yy_number, (double)yyvsp[-1].yy_number);
                        ;}
    break;

  case 153:
#line 1354 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_IDEFINED);
                            yyval.yy_value->yv_identifier = yyvsp[0].yy_string;
                        ;}
    break;

  case 154:
#line 1359 "yacc.y"
    {        /* XXX */
                            yyval.yy_value = new_value (YV_IDEFINED);
                            yyval.yy_value->yv_identifier = yyvsp[0].yy_string;
                            yyval.yy_value->yv_flags |= YV_BOUND;
                        ;}
    break;

  case 155:
#line 1365 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_IDEFINED);
                            yyval.yy_value->yv_identifier = yyvsp[0].yy_string;
                            yyval.yy_value->yv_module = yyvsp[-2].yy_string;
                        ;}
    break;

  case 156:
#line 1373 "yacc.y"
    {
                            yyval.yy_value = new_value (YV_IDEFINED);
                            yyval.yy_value->yv_identifier = yyvsp[-1].yy_string;
                            if (yyvsp[0].yy_value)
                            {
                                yyval.yy_value = add_value (yyvsp[0].yy_value, yyval.yy_value);
                            }
                        ;}
    break;

  case 157:
#line 1382 "yacc.y"
    {
                            yyval.yy_value = NULL;
                        ;}
    break;

  case 158:
#line 1388 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 159:
#line 1392 "yacc.y"
    {
                            yyval.yy_value = NULL;
                        ;}
    break;

  case 160:
#line 1398 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 161:
#line 1402 "yacc.y"
    {
                            yyval.yy_value = add_value (yyvsp[-2].yy_value, yyvsp[0].yy_value);
                        ;}
    break;

  case 162:
#line 1408 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 163:
#line 1414 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 164:
#line 1418 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 165:
#line 1424 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 166:
#line 1428 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 167:
#line 1434 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 168:
#line 1438 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 169:
#line 1444 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 170:
#line 1448 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 171:
#line 1454 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 172:
#line 1458 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 173:
#line 1464 "yacc.y"
    {
                            yyval.yy_oid = yyvsp[-1].yy_oid;
                        ;}
    break;

  case 175:
#line 1471 "yacc.y"
    {
                                yyval.yy_oid = addoid(yyvsp[-1].yy_oid, yyvsp[0].yy_oid);
                                oid_free (yyvsp[-1].yy_oid);
                                oid_free (yyvsp[0].yy_oid);
                        ;}
    break;

  case 178:
#line 1483 "yacc.y"
    {
                            yyval.yy_oid = int2oid (yyvsp[0].yy_number);
                        ;}
    break;

  case 179:
#line 1487 "yacc.y"
    {
                            yyval.yy_oid = oidlookup(yyvsp[0].yy_value->yv_identifier);
                            free((char *)yyvsp[0].yy_value);
                        ;}
    break;

  case 180:
#line 1494 "yacc.y"
    {
                            free (yyvsp[-3].yy_string);
                            yyval.yy_oid = yyvsp[-1].yy_oid;
                        ;}
    break;

  case 182:
#line 1502 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_SETTYPE, yyvsp[-5].yy_number);
                            yyval.yy_type->yp_type = yyvsp[0].yy_type;
                            if (yyvsp[-2].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-2].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-2].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-2].yy_sctrl);
                            }

                            if (yyvsp[-1].yy_string)
                            {
                                yyval.yy_type->yp_control = yyvsp[-1].yy_string;
                                yyval.yy_type->yp_flags |= YP_CONTROLLED;
                            }
                        ;}
    break;

  case 183:
#line 1519 "yacc.y"
    {
                            yyval.yy_type = new_type (YP_SEQTYPE, yyvsp[-5].yy_number);
                            yyval.yy_type->yp_type = yyvsp[0].yy_type;
                            if (yyvsp[-2].yy_sctrl)
                            {
                                yyval.yy_type->yp_structname = yyvsp[-2].yy_sctrl->ys_structname;
                                yyval.yy_type->yp_ptrname = yyvsp[-2].yy_sctrl->ys_ptrname;
                                free_ys (yyvsp[-2].yy_sctrl);
                            }

                            if (yyvsp[-1].yy_string)
                            {
                                yyval.yy_type->yp_control = yyvsp[-1].yy_string;
                                yyval.yy_type->yp_flags |= YP_CONTROLLED;
                            }
                        ;}
    break;

  case 189:
#line 1549 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 195:
#line 1562 "yacc.y"
    {
                            yyval.yy_type = yyvsp[0].yy_type;
                        ;}
    break;

  case 201:
#line 1579 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 202:
#line 1583 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 203:
#line 1589 "yacc.y"
    {
                            yyval.yy_value = yyvsp[0].yy_value;
                        ;}
    break;

  case 204:
#line 1593 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 206:
#line 1602 "yacc.y"
    {
                            yyval.yy_type = NULL;
                        ;}
    break;

  case 207:
#line 1608 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 208:
#line 1612 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 216:
#line 1635 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 217:
#line 1639 "yacc.y"
    {
                            yyval.yy_string = NULL;
                        ;}
    break;

  case 222:
#line 1653 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 223:
#line 1657 "yacc.y"
    {
                            yyval.yy_number = 0;
                        ;}
    break;

  case 224:
#line 1663 "yacc.y"
    {
                            yyval.yy_sctrl = new_ys (yyvsp[0].yy_string);
                        ;}
    break;

  case 225:
#line 1667 "yacc.y"
    {
                            yyval.yy_sctrl = NULL;
                        ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 3512 "yacc.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("syntax error, unexpected ") + 1;
	  yysize += yystrlen (yytname[yytype]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* Return failure if at end of input.  */
      if (yychar == YYEOF)
        {
	  /* Pop the error token.  */
          YYPOPSTACK;
	  /* Pop the rest of the stack.  */
	  while (yyss < yyssp)
	    {
	      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
	      yydestruct (yystos[*yyssp], yyvsp);
	      YYPOPSTACK;
	    }
	  YYABORT;
        }

      YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
      yydestruct (yytoken, &yylval);
      yychar = YYEMPTY;

    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab2;


/*----------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action.  |
`----------------------------------------------------*/
yyerrlab1:

  /* Suppress GCC warning that yyerrlab1 is unused when no action
     invokes YYERROR.  Doesn't work in C++ */
#ifndef __cplusplus
#if defined (__GNUC_MINOR__) && 2093 <= (__GNUC__ * 1000 + __GNUC_MINOR__)
  __attribute__ ((__unused__))
#endif
#endif


  goto yyerrlab2;


/*---------------------------------------------------------------.
| yyerrlab2 -- pop states until the error token can be shifted.  |
`---------------------------------------------------------------*/
yyerrlab2:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      yyvsp--;
      yystate = *--yyssp;

      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1671 "yacc.y"


#include "lex.yy.c"

