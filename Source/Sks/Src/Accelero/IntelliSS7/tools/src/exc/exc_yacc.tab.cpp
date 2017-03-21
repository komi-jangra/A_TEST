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




/* Copy the first part of user declarations.  */
#line 4 "exc_yacc.y"


#include <string>

#include <exc_assert.h>
#include <exc_parse_types.h>

#if defined(__hpux)
#include <alloca.h>
#endif

#if defined(WIN32)
#include <malloc.h>
#define alloca _alloca
#endif

// From the lexical analyser (we must not include exc_lex.h).


#include <stdio.h>

#if !defined(WIN32)
extern "C" {
#endif

extern char* yytext;
extern unsigned long lexLineNumber;
extern FILE* yyin;
int yylex();
void yyrestart(FILE *input_file);

#if !defined(WIN32)
}
#endif


// Forward declaration required.

void yyerror(char* s);


// Boolean used for small errors. Prevent code generation but not prevent the
// later error checking passes.

bool smallError = false;  


// Boolean used incase the lex definition file was compiled with flex. In this
// case the lexical analyzer must be reset for every .exc file parsed, except
// the first.

static bool firstTimeThrough = true;


// Used to hold the root of the parse tree.

Subsystem* subsystemPtr;


// Used to hold the number of parse errors. 

unsigned short parseErrorCount = 0;

#define MAX_PARSE_ERRORS 50

#define PARSE_ERROR()                                                          \
parseErrorCount++;                                                             \
parsedSystem.status = PARSE_ERRORS;                                            \
if (parseErrorCount > MAX_PARSE_ERRORS)                                        \
{                                                                              \
    fprintf(stderr, "Parse error count exceeds 50 - stopping compilation.\n"); \
    exit(1);                                                                   \
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
/* Line 191 of yacc.c.  */
#line 247 "exc_yacc.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 259 "exc_yacc.tab.c"

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  31
/* YYNRULES -- Number of rules. */
#define YYNRULES  51
/* YYNRULES -- Number of states. */
#define YYNSTATES  110

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,    16,    18,    21,    23,    24,    40,    43,
      45,    46,    52,    56,    60,    61,    65,    67,    69,    75,
      78,    80,    81,    87,    91,    95,    99,   103,   107,   110,
     114,   115,   119,   121,   123,   126,   128,   130,   134,   138,
     139,   143,   144,   148,   149,   153,   154,   158,   159,   163,
     164,   168
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      41,     0,    -1,    18,    62,    56,    57,    63,    58,    64,
      65,    66,    67,    42,    21,    -1,    43,    -1,    43,    44,
      -1,    44,    -1,    -1,    19,    62,    56,    55,    58,    64,
      65,    66,    67,    68,    69,    70,    45,    51,    21,    -1,
      45,    46,    -1,    46,    -1,    -1,    38,    62,    47,    48,
      21,    -1,    28,    20,    61,    -1,    30,    49,    21,    -1,
      -1,    49,     9,    50,    -1,    50,    -1,    62,    -1,    62,
      24,    68,    70,    21,    -1,    51,    52,    -1,    52,    -1,
      -1,    29,    62,    53,    54,    21,    -1,    26,    20,    61,
      -1,    27,    20,    61,    -1,    25,    20,    61,    -1,    22,
      20,     7,    -1,    23,    20,    62,    -1,    23,    20,    -1,
      24,    59,    21,    -1,    -1,    59,     9,    60,    -1,    60,
      -1,    62,    -1,    61,     5,    -1,     5,    -1,     6,    -1,
      39,    20,    61,    -1,    31,    20,    61,    -1,    -1,    32,
      20,    61,    -1,    -1,    33,    20,    61,    -1,    -1,    34,
      20,    61,    -1,    -1,    35,    20,    61,    -1,    -1,    36,
      20,    61,    -1,    -1,    37,    20,    61,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   187,   187,   228,   235,   240,   246,   252,   307,   312,
     318,   324,   345,   354,   361,   367,   372,   380,   386,   400,
     405,   411,   417,   431,   440,   449,   458,   467,   474,   482,
     489,   495,   500,   508,   516,   521,   529,   537,   546,   553,
     559,   566,   572,   579,   585,   592,   598,   605,   611,   618,
     624,   631
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BINARY_STRING_SYMBOL", 
  "HEXA_STRING_SYMBOL", "STRING_SYMBOL", "IDENTIFIER_SYMBOL", 
  "NUMBER_SYMBOL", "DOT_SYMBOL", "COMMA_SYMBOL", "LEFTBRACE_SYMBOL", 
  "RIGHTBRACE_SYMBOL", "LEFTPAREN_SYMBOL", "RIGHTPAREN_SYMBOL", 
  "LEFTBRACKET_SYMBOL", "RIGHTBRACKET_SYMBOL", "BAR_SYMBOL", 
  "SEMI_COLON_SYMBOL", "SUBSYSTEM_KEYWORD_SYMBOL", 
  "EXCEPTION_KEYWORD_SYMBOL", "IS_KEYWORD_SYMBOL", "END_KEYWORD_SYMBOL", 
  "NUMBER_KEYWORD_SYMBOL", "PREFIX_KEYWORD_SYMBOL", 
  "OPTION_KEYWORD_SYMBOL", "REASON_KEYWORD_SYMBOL", 
  "ATTRIBUTE_TYPE_KEYWORD_SYMBOL", "PARAMETER_TYPE_KEYWORD_SYMBOL", 
  "VALUE_KEYWORD_SYMBOL", "ATTRIBUTE_KEYWORD_SYMBOL", 
  "ARGUMENT_KEYWORD_SYMBOL", "CODE_HEADER_BEFORE_KEYWORD_SYMBOL", 
  "CODE_HEADER_AFTER_KEYWORD_SYMBOL", "CODE_SOURCE_BEFORE_KEYWORD_SYMBOL", 
  "CODE_SOURCE_AFTER_KEYWORD_SYMBOL", "CODE_BEFORE_KEYWORD_SYMBOL", 
  "CODE_BODY_KEYWORD_SYMBOL", "CODE_AFTER_KEYWORD_SYMBOL", 
  "DESCRIPTION_KEYWORD_SYMBOL", "FILE_NAME_KEYWORD_SYMBOL", "$accept", 
  "SubsystemDefinition", "SubsystemBody", "ExceptionList", "Exception", 
  "DescriptionList", "Description", "ValueEntry", "ArgumentClause", 
  "ArgumentList", "Argument", "AttributeList", "Attribute", 
  "AttributeTypeEntry", "ParameterTypeEntry", "ReasonEntry", 
  "NumberEntry", "PrefixEntry", "OptionClause", "OptionList", "Option", 
  "String", "Identifier", "FileEntry", "CodeHeaderBeforeEntry", 
  "CodeHeaderAfterEntry", "CodeSourceBeforeEntry", "CodeSourceAfterEntry", 
  "CodeBeforeEntry", "CodeBodyEntry", "CodeAfterEntry", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    40,    41,    42,    43,    43,    43,    44,    45,    45,
      45,    46,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    51,    52,    53,    54,    55,    56,    57,    57,    58,
      58,    59,    59,    60,    61,    61,    62,    63,    64,    64,
      65,    65,    66,    66,    67,    67,    68,    68,    69,    69,
      70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,    12,     1,     2,     1,     0,    15,     2,     1,
       0,     5,     3,     3,     0,     3,     1,     1,     5,     2,
       1,     0,     5,     3,     3,     3,     3,     3,     2,     3,
       0,     3,     1,     1,     2,     1,     1,     3,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,    36,     0,     1,     0,     0,     0,     0,
       0,    26,    28,     0,    30,    27,     0,     0,    39,    35,
      37,     0,    32,    33,     0,    41,    34,     0,    29,     0,
       0,    43,    31,    38,     0,     0,    45,    40,     0,     0,
       6,    42,     0,     0,     0,     3,     5,    44,     0,     2,
       4,     0,     0,    30,     0,    39,    25,    41,    43,    45,
      47,     0,    49,     0,     0,    51,    46,     0,     0,    10,
      48,     0,     0,    21,     9,    50,     0,     0,     8,     0,
      20,     0,    14,     0,     7,    19,     0,     0,     0,     0,
       0,    12,     0,    16,    17,    11,     0,     0,     0,     0,
      13,    47,    23,     0,    22,    15,    51,    24,     0,    18
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     2,    44,    45,    46,    73,    74,    82,    88,    92,
      93,    79,    80,    90,    98,    53,     7,    10,    18,    21,
      22,    20,    23,    14,    25,    31,    36,    40,    62,    65,
      69
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -37
static const yysigned_char yypact[] =
{
     -11,    -4,     9,   -37,   -10,   -37,    -2,    -3,    12,     1,
     -17,   -37,    -4,     3,     0,   -37,    20,    -4,     2,   -37,
      22,    -6,   -37,   -37,     8,     4,   -37,    -4,   -37,    20,
      10,     5,   -37,    22,    20,    11,     6,    22,    20,    14,
      13,    22,    20,    -4,    16,    13,   -37,    22,   -10,   -37,
     -37,    19,    21,     0,    20,     2,    22,     4,     5,     6,
      15,    25,    -7,    20,    26,    17,    22,    20,    27,    18,
      22,    20,    -4,   -21,   -37,    22,    23,    -4,   -37,   -16,
     -37,    28,    29,    31,   -37,   -37,    20,    -4,    32,    35,
      33,    22,    -5,   -37,    37,   -37,    20,    42,    43,    -4,
     -37,    15,    22,    20,   -37,   -37,    17,    22,    44,   -37
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -37,   -37,   -37,   -37,     7,   -37,   -24,   -37,   -37,   -37,
     -36,   -37,   -13,   -37,   -37,   -37,    24,   -37,    30,   -37,
      40,   -28,    -1,   -37,    34,    36,    38,    41,   -32,   -37,
     -33
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
       4,    33,     3,    27,    99,    84,    37,     1,    77,     5,
      41,    15,     6,    77,    47,    28,   100,    72,     8,    11,
       9,    12,    13,    16,    17,    19,    56,    26,    29,    64,
      34,    38,    43,    24,    42,    66,    30,    49,    35,    70,
      39,    54,    48,    75,    52,    63,    67,    71,    86,    78,
      61,    81,    50,    95,    68,    96,    72,    89,    91,    87,
      97,   101,   103,   105,   104,   109,    85,    32,   102,   106,
       0,    76,    51,   108,     0,   107,    83,     0,     0,     0,
       0,     0,     0,    55,     0,     0,    94,     0,     0,    57,
       0,     0,     0,    58,     0,     0,    59,     0,    94,     0,
      60
};

static const yysigned_char yycheck[] =
{
       1,    29,     6,     9,     9,    21,    34,    18,    29,     0,
      38,    12,    22,    29,    42,    21,    21,    38,    20,     7,
      23,    20,    39,    20,    24,     5,    54,     5,    20,    36,
      20,    20,    19,    31,    20,    63,    32,    21,    33,    67,
      34,    20,    43,    71,    25,    20,    20,    20,    20,    73,
      35,    28,    45,    21,    37,    20,    38,    26,    86,    30,
      27,    24,    20,    99,    21,    21,    79,    27,    96,   101,
      -1,    72,    48,   106,    -1,   103,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    87,    -1,    -1,    55,
      -1,    -1,    -1,    57,    -1,    -1,    58,    -1,    99,    -1,
      59
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    18,    41,     6,    62,     0,    22,    56,    20,    23,
      57,     7,    20,    39,    63,    62,    20,    24,    58,     5,
      61,    59,    60,    62,    31,    64,     5,     9,    21,    20,
      32,    65,    60,    61,    20,    33,    66,    61,    20,    34,
      67,    61,    20,    19,    42,    43,    44,    61,    62,    21,
      44,    56,    25,    55,    20,    58,    61,    64,    65,    66,
      67,    35,    68,    20,    36,    69,    61,    20,    37,    70,
      61,    20,    38,    45,    46,    61,    62,    29,    46,    51,
      52,    28,    47,    62,    21,    52,    20,    30,    48,    26,
      53,    61,    49,    50,    62,    21,    20,    27,    54,     9,
      21,    24,    61,    20,    21,    50,    68,    61,    70,    21
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
#line 199 "exc_yacc.y"
    {
        subsystemPtr->name = *(yyvsp[-10].stringPtr);
        subsystemPtr->number = yyvsp[-9].intVal;
        subsystemPtr->prefix = *(yyvsp[-8].stringPtr);
        subsystemPtr->fileName = *(yyvsp[-7].stringPtr);
#if 0
        subsystemPtr->optionList.assign((yyvsp[-6].optionListPtr)->begin(), (yyvsp[-6].optionListPtr)->end());
#else
        subsystemPtr->optionList.erase(subsystemPtr->optionList.begin(),
                                       subsystemPtr->optionList.end());
        subsystemPtr->optionList.insert(subsystemPtr->optionList.end(),
                                        (yyvsp[-6].optionListPtr)->begin(), (yyvsp[-6].optionListPtr)->end());
#endif
        subsystemPtr->codeHeaderBefore = *(yyvsp[-5].stringPtr);
        subsystemPtr->codeHeaderAfter = *(yyvsp[-4].stringPtr);
        subsystemPtr->codeSourceBefore = *(yyvsp[-3].stringPtr);
        subsystemPtr->codeSourceAfter = *(yyvsp[-2].stringPtr);
#if 0
        subsystemPtr->exceptionList.assign((yyvsp[-1].exceptionListPtr)->begin(), (yyvsp[-1].exceptionListPtr)->end());
#else
        subsystemPtr->exceptionList.erase(subsystemPtr->exceptionList.begin(),
                                          subsystemPtr->exceptionList.end());
        subsystemPtr->exceptionList.insert(subsystemPtr->exceptionList.end(),
                                           (yyvsp[-1].exceptionListPtr)->begin(), (yyvsp[-1].exceptionListPtr)->end());
#endif
    ;}
    break;

  case 3:
#line 229 "exc_yacc.y"
    {
        yyval.exceptionListPtr = yyvsp[0].exceptionListPtr;
    ;}
    break;

  case 4:
#line 236 "exc_yacc.y"
    {
        yyvsp[-1].exceptionListPtr->push_back(yyvsp[0].exceptionPtr);
        yyval.exceptionListPtr = yyvsp[-1].exceptionListPtr;
    ;}
    break;

  case 5:
#line 241 "exc_yacc.y"
    {
        yyval.exceptionListPtr = new ExceptionList();
        yyval.exceptionListPtr->push_back(yyvsp[0].exceptionPtr);
    ;}
    break;

  case 6:
#line 246 "exc_yacc.y"
    {
        yyval.exceptionListPtr = new ExceptionList();
    ;}
    break;

  case 7:
#line 267 "exc_yacc.y"
    {
        yyval.exceptionPtr = new Exception();
        yyval.exceptionPtr->name = *(yyvsp[-13].stringPtr);
        yyval.exceptionPtr->number = yyvsp[-12].intVal;
        yyval.exceptionPtr->reason = *(yyvsp[-11].stringPtr);
#if 0
        yyval.exceptionPtr->optionList.assign((yyvsp[-10].optionListPtr)->begin(), (yyvsp[-10].optionListPtr)->end());
#else
        subsystemPtr->optionList.erase(subsystemPtr->optionList.begin(),
                                       subsystemPtr->optionList.end());
        subsystemPtr->optionList.insert(subsystemPtr->optionList.end(),
                                        (yyvsp[-10].optionListPtr)->begin(), (yyvsp[-10].optionListPtr)->end());
#endif
        yyval.exceptionPtr->codeHeaderBefore = *(yyvsp[-9].stringPtr);
        yyval.exceptionPtr->codeHeaderAfter = *(yyvsp[-8].stringPtr);
        yyval.exceptionPtr->codeSourceBefore = *(yyvsp[-7].stringPtr);
        yyval.exceptionPtr->codeSourceAfter = *(yyvsp[-6].stringPtr);
        yyval.exceptionPtr->codeBefore = *(yyvsp[-5].stringPtr);
        yyval.exceptionPtr->codeBody = *(yyvsp[-4].stringPtr);
        yyval.exceptionPtr->codeAfter = *(yyvsp[-3].stringPtr);
#if 0
        yyval.exceptionPtr->descriptionList.assign((yyvsp[-2].descriptionListPtr)->begin(), (yyvsp[-2].descriptionListPtr)->end());
#else
        yyval.exceptionPtr->descriptionList.erase(yyval.exceptionPtr->descriptionList.begin(),
                                  yyval.exceptionPtr->descriptionList.end());
        yyval.exceptionPtr->descriptionList.insert(yyval.exceptionPtr->descriptionList.end(),
                                   (yyvsp[-2].descriptionListPtr)->begin(), (yyvsp[-2].descriptionListPtr)->end());
#endif
#if 0
        yyval.exceptionPtr->attributeList.assign((yyvsp[-1].attributeListPtr)->begin(), (yyvsp[-1].attributeListPtr)->end());
#else
        yyval.exceptionPtr->attributeList.erase(yyval.exceptionPtr->attributeList.begin(),
                                yyval.exceptionPtr->attributeList.end());
        yyval.exceptionPtr->attributeList.insert(yyval.exceptionPtr->attributeList.end(),
                                 (yyvsp[-1].attributeListPtr)->begin(), (yyvsp[-1].attributeListPtr)->end());
#endif
    ;}
    break;

  case 8:
#line 308 "exc_yacc.y"
    {
        yyvsp[-1].descriptionListPtr->push_back(yyvsp[0].descriptionPtr);
        yyval.descriptionListPtr = yyvsp[-1].descriptionListPtr;
    ;}
    break;

  case 9:
#line 313 "exc_yacc.y"
    {
        yyval.descriptionListPtr = new DescriptionList();
        yyval.descriptionListPtr->push_back(yyvsp[0].descriptionPtr);
    ;}
    break;

  case 10:
#line 318 "exc_yacc.y"
    {
        yyval.descriptionListPtr = new DescriptionList();
    ;}
    break;

  case 11:
#line 329 "exc_yacc.y"
    {
        yyval.descriptionPtr = new Description();
        yyval.descriptionPtr->name = *(yyvsp[-3].stringPtr);
        yyval.descriptionPtr->value = *(yyvsp[-2].stringPtr);
#if 0
        yyval.descriptionPtr->argumentList.assign((yyvsp[-1].argumentListPtr)->begin(), (yyvsp[-1].argumentListPtr)->end());
#else
        yyval.descriptionPtr->argumentList.erase(yyval.descriptionPtr->argumentList.begin(),
                               yyval.descriptionPtr->argumentList.end());
        yyval.descriptionPtr->argumentList.insert(yyval.descriptionPtr->argumentList.end(),
                                (yyvsp[-1].argumentListPtr)->begin(), (yyvsp[-1].argumentListPtr)->end());
#endif
    ;}
    break;

  case 12:
#line 348 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 13:
#line 357 "exc_yacc.y"
    {
        yyval.argumentListPtr = yyvsp[-1].argumentListPtr;
    ;}
    break;

  case 14:
#line 361 "exc_yacc.y"
    {
        yyval.argumentListPtr = new ArgumentList();
    ;}
    break;

  case 15:
#line 368 "exc_yacc.y"
    {
        yyvsp[-2].argumentListPtr->push_back(yyvsp[0].argumentPtr);
        yyval.argumentListPtr = yyvsp[-2].argumentListPtr;
    ;}
    break;

  case 16:
#line 373 "exc_yacc.y"
    {
        yyval.argumentListPtr = new ArgumentList();
        yyval.argumentListPtr->push_back(yyvsp[0].argumentPtr);
    ;}
    break;

  case 17:
#line 381 "exc_yacc.y"
    {
        yyval.argumentPtr = new Argument();
        yyval.argumentPtr->name = *(yyvsp[0].stringPtr);
    ;}
    break;

  case 18:
#line 391 "exc_yacc.y"
    {
        yyval.argumentPtr = new Argument();
        yyval.argumentPtr->name = *(yyvsp[-4].stringPtr);
        yyval.argumentPtr->codeBefore = *(yyvsp[-2].stringPtr);
        yyval.argumentPtr->codeAfter = *(yyvsp[-1].stringPtr);
    ;}
    break;

  case 19:
#line 401 "exc_yacc.y"
    {
        yyvsp[-1].attributeListPtr->push_back(yyvsp[0].attributePtr);
        yyval.attributeListPtr = yyvsp[-1].attributeListPtr;
    ;}
    break;

  case 20:
#line 406 "exc_yacc.y"
    {
        yyval.attributeListPtr = new AttributeList();
        yyval.attributeListPtr->push_back(yyvsp[0].attributePtr);
    ;}
    break;

  case 21:
#line 411 "exc_yacc.y"
    {
        yyval.attributeListPtr = new AttributeList();
    ;}
    break;

  case 22:
#line 422 "exc_yacc.y"
    {
        yyval.attributePtr = new Attribute();
        yyval.attributePtr->name = *(yyvsp[-3].stringPtr);
        yyval.attributePtr->attributeType = *(yyvsp[-2].stringPtr);
        yyval.attributePtr->parameterType = *(yyvsp[-1].stringPtr);
    ;}
    break;

  case 23:
#line 434 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 24:
#line 443 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 25:
#line 452 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 26:
#line 461 "exc_yacc.y"
    {
        yyval.intVal = yyvsp[0].intVal;
    ;}
    break;

  case 27:
#line 470 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 28:
#line 476 "exc_yacc.y"
    {
        yyval.stringPtr = new string;
    ;}
    break;

  case 29:
#line 485 "exc_yacc.y"
    {
        yyval.optionListPtr = yyvsp[-1].optionListPtr;
    ;}
    break;

  case 30:
#line 489 "exc_yacc.y"
    {
        yyval.optionListPtr = new OptionList();
    ;}
    break;

  case 31:
#line 496 "exc_yacc.y"
    {
        yyvsp[-2].optionListPtr->push_back(yyvsp[0].optionPtr);
        yyval.optionListPtr = yyvsp[-2].optionListPtr;
    ;}
    break;

  case 32:
#line 501 "exc_yacc.y"
    {
        yyval.optionListPtr = new OptionList();
        yyval.optionListPtr->push_back(yyvsp[0].optionPtr);
    ;}
    break;

  case 33:
#line 509 "exc_yacc.y"
    {
        yyval.optionPtr = new Option();
        yyval.optionPtr->name = *(yyvsp[0].stringPtr);
    ;}
    break;

  case 34:
#line 517 "exc_yacc.y"
    {
        yyvsp[-1].stringPtr->append(yyvsp[0].charPtr);
        yyval.stringPtr = yyvsp[-1].stringPtr;
    ;}
    break;

  case 35:
#line 522 "exc_yacc.y"
    {
        yyval.stringPtr = new string(yyvsp[0].charPtr);
    ;}
    break;

  case 36:
#line 530 "exc_yacc.y"
    {
        yyval.stringPtr = new string(yyvsp[0].charPtr);
    ;}
    break;

  case 37:
#line 540 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 38:
#line 549 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 39:
#line 553 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;

  case 40:
#line 562 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 41:
#line 566 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;

  case 42:
#line 575 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 43:
#line 579 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;

  case 44:
#line 588 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 45:
#line 592 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;

  case 46:
#line 601 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 47:
#line 605 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;

  case 48:
#line 614 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 49:
#line 618 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;

  case 50:
#line 627 "exc_yacc.y"
    {
        yyval.stringPtr = yyvsp[0].stringPtr;
    ;}
    break;

  case 51:
#line 631 "exc_yacc.y"
    {
        yyval.stringPtr = new string("");
    ;}
    break;


    }

/* Line 991 of yacc.c.  */
#line 1676 "exc_yacc.tab.c"

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


#line 639 "exc_yacc.y"


void yyerror(char *s)
{
	fprintf(stderr,"File \"%s\", line %ld : ERROR - %s at symbol \"%s\".\n",
            subsystemPtr->excSrcFileName.c_str(), lexLineNumber, s, yytext);
}



// Given a Subsystem*, the file name associated with the open FILE* fDesc,
// InitExcParser sets up the yacc/lex parser to parse an Exc subsystem read from
// fDesc and write the parse results into the given Subsystem* subsystem.

void InitExcParser(Subsystem* subsystem, const string& fileName, FILE* fDesc)
{
    REQUIRE(subsystem != NULL);
    REQUIRE(fDesc != NULL);

    yyin = fDesc;

    // Reset lexical analyzer input file fDesc (only do this on successive calls
    // or yyrestart seg faults).

#ifdef FLEX

    if (!firstTimeThrough)
    {
        yyrestart(fDesc); 
    }

    firstTimeThrough = false;

#endif

    // Init subsystemPtr.

    subsystemPtr = subsystem;

    subsystem->excSrcFileName = fileName;
    subsystem->status = Subsystem::OK;
   
    // Reset line number to 1.

    lexLineNumber = 1;


    // Reset error count.

    parseErrorCount = 0;


    // Reset non critical error indicator.

    smallError = false;
}





