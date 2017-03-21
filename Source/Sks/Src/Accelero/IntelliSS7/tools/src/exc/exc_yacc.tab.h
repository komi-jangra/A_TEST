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
     BINARY_STRING_SYMBOL = 258,
     HEXA_STRING_SYMBOL = 259,
     STRING_SYMBOL = 260,
     IDENTIFIER_SYMBOL = 261,
     NUMBER_SYMBOL = 262,
     DOT_SYMBOL = 263,
     COMMA_SYMBOL = 264,
     LEFTBRACE_SYMBOL = 265,
     RIGHTBRACE_SYMBOL = 266,
     LEFTPAREN_SYMBOL = 267,
     RIGHTPAREN_SYMBOL = 268,
     LEFTBRACKET_SYMBOL = 269,
     RIGHTBRACKET_SYMBOL = 270,
     BAR_SYMBOL = 271,
     SEMI_COLON_SYMBOL = 272,
     SUBSYSTEM_KEYWORD_SYMBOL = 273,
     EXCEPTION_KEYWORD_SYMBOL = 274,
     IS_KEYWORD_SYMBOL = 275,
     END_KEYWORD_SYMBOL = 276,
     NUMBER_KEYWORD_SYMBOL = 277,
     PREFIX_KEYWORD_SYMBOL = 278,
     OPTION_KEYWORD_SYMBOL = 279,
     REASON_KEYWORD_SYMBOL = 280,
     ATTRIBUTE_TYPE_KEYWORD_SYMBOL = 281,
     PARAMETER_TYPE_KEYWORD_SYMBOL = 282,
     VALUE_KEYWORD_SYMBOL = 283,
     ATTRIBUTE_KEYWORD_SYMBOL = 284,
     ARGUMENT_KEYWORD_SYMBOL = 285,
     CODE_HEADER_BEFORE_KEYWORD_SYMBOL = 286,
     CODE_HEADER_AFTER_KEYWORD_SYMBOL = 287,
     CODE_SOURCE_BEFORE_KEYWORD_SYMBOL = 288,
     CODE_SOURCE_AFTER_KEYWORD_SYMBOL = 289,
     CODE_BEFORE_KEYWORD_SYMBOL = 290,
     CODE_BODY_KEYWORD_SYMBOL = 291,
     CODE_AFTER_KEYWORD_SYMBOL = 292,
     DESCRIPTION_KEYWORD_SYMBOL = 293,
     FILE_NAME_KEYWORD_SYMBOL = 294
   };
#endif
#define BINARY_STRING_SYMBOL 258
#define HEXA_STRING_SYMBOL 259
#define STRING_SYMBOL 260
#define IDENTIFIER_SYMBOL 261
#define NUMBER_SYMBOL 262
#define DOT_SYMBOL 263
#define COMMA_SYMBOL 264
#define LEFTBRACE_SYMBOL 265
#define RIGHTBRACE_SYMBOL 266
#define LEFTPAREN_SYMBOL 267
#define RIGHTPAREN_SYMBOL 268
#define LEFTBRACKET_SYMBOL 269
#define RIGHTBRACKET_SYMBOL 270
#define BAR_SYMBOL 271
#define SEMI_COLON_SYMBOL 272
#define SUBSYSTEM_KEYWORD_SYMBOL 273
#define EXCEPTION_KEYWORD_SYMBOL 274
#define IS_KEYWORD_SYMBOL 275
#define END_KEYWORD_SYMBOL 276
#define NUMBER_KEYWORD_SYMBOL 277
#define PREFIX_KEYWORD_SYMBOL 278
#define OPTION_KEYWORD_SYMBOL 279
#define REASON_KEYWORD_SYMBOL 280
#define ATTRIBUTE_TYPE_KEYWORD_SYMBOL 281
#define PARAMETER_TYPE_KEYWORD_SYMBOL 282
#define VALUE_KEYWORD_SYMBOL 283
#define ATTRIBUTE_KEYWORD_SYMBOL 284
#define ARGUMENT_KEYWORD_SYMBOL 285
#define CODE_HEADER_BEFORE_KEYWORD_SYMBOL 286
#define CODE_HEADER_AFTER_KEYWORD_SYMBOL 287
#define CODE_SOURCE_BEFORE_KEYWORD_SYMBOL 288
#define CODE_SOURCE_AFTER_KEYWORD_SYMBOL 289
#define CODE_BEFORE_KEYWORD_SYMBOL 290
#define CODE_BODY_KEYWORD_SYMBOL 291
#define CODE_AFTER_KEYWORD_SYMBOL 292
#define DESCRIPTION_KEYWORD_SYMBOL 293
#define FILE_NAME_KEYWORD_SYMBOL 294




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 88 "exc_yacc.y"
typedef union YYSTYPE {
    int              intVal;
    char*            charPtr;
    string*          stringPtr;
    Subsystem*       subsystemPtr;
    Exception*       exceptionPtr;
    ExceptionList*   exceptionListPtr;
    Option*          optionPtr;
    OptionList*      optionListPtr;
    Attribute*       attributePtr;
    AttributeList*   attributeListPtr;
    Argument*        argumentPtr;
    ArgumentList*    argumentListPtr;
    Description*     descriptionPtr;
    DescriptionList* descriptionListPtr;
} YYSTYPE;
/* Line 1250 of yacc.c.  */
#line 131 "exc_yacc.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



