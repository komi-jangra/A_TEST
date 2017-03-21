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
/* Line 1250 of yacc.c.  */
#line 231 "yacc.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



