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
 * LOG: Revision 3.1  2000/08/16 00:07:20  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/05/11 02:06:15  mmiers
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
 * LOG: Revision 2.0  1999/12/03 23:30:03  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/04/21 19:33:39  mmiers
 * LOG:
 * LOG:
 * LOG: Minor tweaks here and there.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 18:22:54  mmiers
 * LOG: Update universal library and IS41 to use the compiler directly.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:36:58  jpakrasi
 * LOG: Build pepsy on NT.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/
%{

#if defined(WIN32)
#pragma warning(disable:4274)
#endif

#ident "$Id: lex.l,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

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

struct table
{
    char   *t_keyword;
    int     t_value;
    int     t_porting;
};

extern int lineno;

#ifndef DEFAULT
#error "HELP"
#endif

static struct table reserved[] =
{
    { "ABSENT", ABSENT, 0 },
    { "ANY", ANY, 0 },
    { "APPLICATION", APPLICATION, 0 },
    { "BEGIN", BGIN, 0 },
    { "BIT", BIT, 0 },
    { "BITSTRING", BITSTRING, 0 },
    { "BOOLEAN", BOOLEAN_kw, 0 },
    { "BY", BY, 0 },
    { "CHOICE", CHOICE, 0 },
    { "COMPONENT", COMPONENT, 0 },
    { "COMPONENTS", COMPONENTS, 0 },
    { "COMPONENTSOF", COMPONENTSOF, 0 },
    { "DEFAULT", DEFAULT, 0 },
    { "DEFINED", DEFINED, 0 },
    { "DEFINITIONS", DEFINITIONS, 0 },
    { "ENCRYPTED", ENCRYPTED, 0 },
    { "END", END, 0 },
    { "ENUMERATED", ENUMERATED, 0 },
    { "EXPLICIT", EXPLICIT, 0 },
    { "EXPORTS", EXPORTS, 0 },
    { "FALSE", L_FALSE, 0 },
    { "FROM", FROM, 0 },
    { "IDENTIFIER", IDENTIFIER, 0 },
    { "IMPLICIT", IMPLICIT, 0 },
    { "IMPORTS", IMPORTS, 0 },
    { "INCLUDE", INCLUDES, 0 },
    { "INTEGER", INTEGER, 0 },
    { "MIN", MIN, 0 },
    { "MAX", MAX, 0 },
    { "NULL", NIL, 0 },
    { "OBJECT", OBJECT, 0 },
    { "OCTET", OCTET, 0 },
    { "OCTETSTRING", OCTETSTRING, 0 },
    { "OF", OF_kw, 0 },
    { "OPTIONAL", OPTIONAL_kw, 0 },
    { "PREFIXES", PREFIXES, 0 },
    { "PRESENT", PRESENT, 0 },
    { "PRIVATE", PRIVATE, 0 },
    { "REAL", REAL, 0 },
    { "SEQUENCE", SEQUENCE, 0 },
    { "SEQUENCEOF", SEQUENCEOF, 0 },
    { "SET", SET, 0 },
    { "SETOF", SETOF, 0 },
    { "SIZE", SIZE_kw, 0 },
    { "STRING", STRING, 0 },
    { "TAGS", TAGS, 0 },
    { "TRUE", L_TRUE, 0 },
    { "UNIVERSAL", UNIVERSAL, 0 },
    { "WITH", WITH, 0 },
    { "PLUS-INFINITY", PLUSINFINITY, 0 },
    { "MINUS-INFINITY", MINUSINFINITY, 0 },
    { NULL, 0 }
};

%}

%%

"--"                    {
                            int c, d;

                            for (d = 0; (c = input ()) != 0; d = c == '-')
                            {
                                if (c == '\n')
                                {
                                    lineno++;
                                    break;
                                }
                                if (d && c == '-')
                                {
                                    break;
                                }
                            }
                        }
[ \t]*                  {
                            if (yydebug)
                            {
                                fprintf (stderr, "WT\n");
                            }
                        }
\n                      {
                            lineno++;
                            if (yydebug)
                            {
                                fprintf (stderr, "NL\n");
                            }
                        }
"::="                   {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: CCE\n");
                            }
                            return CCE;
                        }
"..."                   {
                            if (yydebug)
                            {
                                    fprintf (stderr, "SY: DOTDOTDOT\n");
                            }
                            return DOTDOTDOT;
                        }
".."                    {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: DOTDOT\n");
                            }
                            return DOTDOT;
                        }
"."                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: DOT\n");
                            }
                            return DOT;
                        }
";"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: SEMICOLON");
                            }
                            return SEMICOLON;
                        }
","                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: COMMA\n");
                            }
                            return COMMA;
                        }
"{"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: LBRACE\n");
                            }
                            return LBRACE;
                        }
"}"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: RBRACE\n");
                            }
                            return RBRACE;
                        }
"|"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: BAR\n");
                            }
                            return BAR;
                        }
"-"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: MINUS\n");
                            }
                            return MINUS;
                        }
"+"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: PLUS\n");
                            }
                            return PLUS;
                        }
"[["|"$"|"<<"           {
                            int tok = 0, c, d, len;
                            char *cp, *ep, *pp;

                            if (*yytext == '$')
                            {
                                tok = VLENGTH;
                            }
                            else
                            {
                                if (*yytext == '<')
                                {
                                    tok = CONTROL;
                                }
                                else
                                {
                                    while((c = input()) == ' ' || c =='\t')
                                    {
                                        continue;
                                    }
                                    switch (c)
                                    {
                                    case 'a': tok = VALA;
                                        break;
                                    case 'b': tok = VALB;
                                        break;
                                    case 'i': tok = VALI;
                                        break;
                                    case 's': tok = VALS;
                                        break;
                                    case 'o': tok = VALO;
                                        break;
                                    case 'x': tok = VALX;
                                        break;
                                    case 'p': tok = VALP;
                                        break;
                                    case 'q': tok = VALQ;
                                        break;
                                    case 'r': tok = VALR;
                                        break;
                                    case 't': tok = VALT;
                                        break;
                                    case 'O': tok = VALOID;
                                        break;
                                    case 'P': tok = PARAMETERTYPE;
                                        break;
                                    case 'T': tok = VALTYPE;
                                        break;
                                    default : myyerror ("unknown token: \"%s\"", yytext);
                                        break;
                                    }

                                    if ((c = input()) != ' ' && c != '\t'
                                        && c != '\n')
                                    {
                                        yyerror ("syntax error in [[ ... ]]");
                                    }
                                }
                            }
 
                            if ((pp = malloc ((unsigned) (len = BUFSIZ)))
                                    == NULL)
                            {
                                yyerror ("out of memory");
                            }

                            for (ep = (cp = pp) + len - 1, d = 0; ; d = c)
                            {
                                if ((c = input ()) == 0)
                                {
                                    yyerror ("end-of-file while reading value");
                                }
                                if ((d == ']' && c == ']' && tok !=CONTROL) ||
                                    (c == '$' && (tok ==VALX || tok ==VALO)) ||
                                    (d == '>' && c == '>' && tok ==CONTROL))
                                {
                                    if ((tok == VALX || tok == VALO) &&
                                       (c != '$'))
                                    {
                                       yyerror("Missing '$' in [[ - ]]");
                                    }

                                    if (c == '$')
                                    {
                                        unput(c);
                                        *cp = 0;
                                    }
                                    else
                                    {
                                        *--cp = 0;
                                    }
                                    yylval.yy_string = pp;

                                    if (yydebug)
                                    {
                                        fprintf (stderr, "VAL: \"%s\"\n",
                                                yylval.yy_string);
                                    }
                                    return tok;
                                }

                                if (cp >= ep)
                                {
                                    int curlen = cp - pp;
                                    char *dp;

                                    if ((dp = realloc (pp, (len += BUFSIZ)))
                                            == NULL)
                                    {
                                        yyerror ("out of memory");
                                    }
                                    cp = dp + curlen;
                                    ep = (pp = dp) + len - 1;
                                }
                                *cp++ = c;
                            }
                        }
"["                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: LBRACKET\n");
                            }
                            return LBRACKET;
                        }
"]"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: RBRACKET\n");
                            }
                            return RBRACKET;
                        }
"<"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: LANGLE\n");
                            }
                            return LANGLE;
                        }
"("                        {
                            if (yydebug)
                                fprintf (stderr, "SY: LPAREN\n");
                            return LPAREN;
                        }
")"                     {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: RPAREN\n");
                            }
                            return RPAREN;
                        }
"\*"                    {
                            if (yydebug)
                            {
                                fprintf (stderr, "SY: STAR\n");
                            }
                            return STAR;
                        }
[0-9]+                  {
                            sscanf (yytext, "%d", &yylval.yy_number);
                            if (yydebug)
                            {
                                fprintf (stderr, "LIT: 0x%x\n",
                                         yylval.yy_number);
                            }
                            return LITNUMBER;
                        }
-[0-9]+                 {
                            sscanf (yytext, "%d", &yylval.yy_number);
                            if (yydebug)
                            {
                                fprintf (stderr, "LIT: 0x%x\n",
                                         yylval.yy_number);
                            }
                            return LITNUMBER;
                        }
'[^'$]*'[BbHh]          {
                            char *cp;

                            switch (*(cp = yytext + strlen (yytext) - 1))
                            {
                            case 'H':
                            case 'h':
                                *--cp = 0;
                                for (cp = yytext + 1; *cp; cp++)
                                {
                                    if (!isxdigit(*cp))
                                    {
                                        yyerror ("bad hex string");
                                    }
                                }

                                yylval.yy_string = new_string(yytext + 1);
                                if (yydebug)
                                {
                                    fprintf (stderr,
                                        "HSTRING: %s\n", yylval.yy_string);
                                }
                                return HSTRING;

                            case 'B':
                            case 'b':
                                *--cp = 0;
                                for (cp = yytext + 1; *cp; cp++)
                                {
                                    if (*cp != '0' && *cp != '1')
                                    {
                                        yyerror ("bad bit string");
                                    }
                                }

                                yylval.yy_string = new_string(yytext + 1);

                                if (yydebug)
                                {
                                    fprintf (stderr,
                                        "BSTRING: %s\n", yylval.yy_string);
                                }
                                return BSTRING;
                            }

                            yyerror ("illegal string");
                        }
\"[^\"$]*\"             {
                            yytext[strlen(yytext) - 1] = 0;
                            yylval.yy_string = new_string (yytext + 1);
                            if (yydebug)
                            {
                                fprintf(stderr, "LIT: \"%s\"\n",
                                        yylval.yy_string);
                            }
                            return LITSTRING;
                        }
[A-Z][A-Za-z0-9-]*      {
                            struct table *t;

                            for (t = reserved; t -> t_keyword; t++)
                            {
                                if (strcmp (t -> t_keyword, yytext) == 0)
                                {
                                    if (yyporting && t -> t_porting)
                                    {
                                        break;
                                    }
                                    if (yydebug)
                                    {
                                        fprintf (stderr,
                                                  "KE: \"%s\"\n", yytext);
                                    }

                                    yylval.yy_number = lineno;

                                    return t -> t_value;
                                }
                            }

                            yylval.yy_string = new_string (yytext);
                            if (yydebug)
                            {
                                fprintf(stderr, "ID: \"%s\"\n",
                                        yylval.yy_string);
                            }
                            return ID;
                        }
[a-z][A-Za-z0-9-]*      {
                            yylval.yy_string = new_string (yytext);
                            if (yydebug)
                            {
                                fprintf(stderr, "NAME: \"%s\"\n",
                                        yylval.yy_string);
                            }
                            return NAME;
                        }
"%["                    {
                            int c, d, len;
                            char *cp, *ep, *pp;

                            if ((pp = malloc((len = BUFSIZ))) == NULL)
                            {
                                yyerror ("out of memory");
                            }

                            for (ep = (cp = pp) + len - 1, d = 0; ; d = c)
                            {
                                if ((c = input ()) == 0)
                                {
                                    yyerror ("end-of-file while reading value");
                                }

                                if (d == '%' && c == ']' )
                                {
                                    *--cp = 0;
                                    yylval.yy_string = pp;

                                    if (yydebug)
                                    {
                                        fprintf (stderr, "VAL: \"%s\"\n",
                                                 yylval.yy_string);
                                    }
                                    return SCTRL;
                                }

                                if (d == '\n')
                                {
                                    yyerror ("newline in %[ %] construct");
                                }
                                if (cp >= ep)
                                {
                                    int curlen = cp - pp;
                                    char *dp;

                                    if ((dp = realloc (pp, (len += BUFSIZ)))
                                            == NULL)
                                    {
                                        yyerror ("out of memory");
                                    }

                                    cp = dp + curlen;
                                    ep = (pp = dp) + len - 1;
                                }

                                *cp++ = c;
                            }
                        }
.                       {   
                            myyerror ("unknown token: \"%s\"", yytext);
                        }

%%
