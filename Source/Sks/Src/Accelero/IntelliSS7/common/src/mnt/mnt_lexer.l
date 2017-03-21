%{

/******************************************************************************
**                                                                           **
**     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     **
**             Manufactured in the United States of America.                 **
**       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        **
**                                                                           **
**   This product and related documentation is protected by copyright and    **
**   distributed under licenses restricting its use, copying, distribution   **
**   and decompilation.  No part of this product or related documentation    **
**   may be reproduced in any form by any means without prior written        **
**   authorization of IntelliNet Technologies and its licensors, if any.     **
**                                                                           **
**   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       **
**   government is subject to restrictions as set forth in subparagraph      **
**   (c)(1)(ii) of the Rights in Technical Data and Computer Software        **
**   clause at DFARS 252.227-7013 and FAR 52.227-19.                         **
**                                                                           **
*******************************************************************************
**                                                                           **
** CONTRACT: INTERNAL                                                        **
**                                                                           **
*******************************************************************************
**
** LOG: $Log: not supported by cvs2svn $
** LOG: Revision 1.1.1.1  2007/10/04 13:24:27  bsccs2
** LOG: init tree
** LOG:
** LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
** LOG: BscCs2
** LOG:
** LOG: Revision 1.1.1.1  2007/03/08 15:14:18  cvsadmin
** LOG: BSC project
** LOG:
** LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
** LOG: Begin PR6.5
** LOG:
** LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
** LOG: PR6.4.2 Source Propagated to Current
** LOG:
** LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
** LOG: Begin PR6.2
** LOG:
** LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
** LOG: Begin PR7.
** LOG:
** LOG: Revision 5.4  2001/08/21 00:23:53  mmiers
** LOG: Warning removal
** LOG:
** LOG: Revision 5.3  2001/08/20 22:06:26  hdivoux
** LOG: Update.
** LOG:
** LOG: Revision 5.2  2001/08/17 20:31:23  hdivoux
** LOG: Improvements.
** LOG:
** LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
** LOG: Start PR6.
** LOG:
** LOG: Revision 1.6  2001/08/16 20:15:03  hdivoux
** LOG: Improvements.
** LOG:
** LOG: Revision 1.5  2001/08/14 23:24:05  hdivoux
** LOG: Improvements.
** LOG:
** LOG: Revision 1.4  2001/08/10 22:42:44  hdivoux
** LOG: Improvements.
** LOG:
** LOG: Revision 1.3  2001/08/09 20:54:40  hdivoux
** LOG: Port to GNU g++.
** LOG:
** LOG: Revision 1.2  2001/08/08 20:37:07  hdivoux
** LOG: Improvements.
** LOG:
** LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
** LOG: Creation.
** LOG:
**
******************************************************************************/

#ident "$Id: mnt_lexer.l,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

#include <stdio.h>
#include <mnt.h>
#include <mnt_constructs.h>
#include <mnt_parser.h>

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace mnt;
#endif // defined(ITS_NAMESPACE)

static void Comment();
static string TranslateString(string str);


#ifdef _MSC_VER
#pragma warning(disable:4102)
#endif // _MSC_VER

%}


D           [0-9]
L           [a-zA-Z_]
H           [a-fA-F0-9]
E           [Ee][+-]?{D}+
FS          (f|F|l|L)
IS          (u|U|l|L)*

%option yylineno

%%
"--"            { Comment();                    }

"end"           { return TK_END;                }
"if"            { return TK_IF;                 }
"then"          { return TK_THEN;               }
"elseif"        { return TK_ELSEIF;             }
"else"          { return TK_ELSE;               }
"from"          { return TK_FROM;               }
"until"         { return TK_UNTIL;              }
"loop"          { return TK_LOOP;               }
"do"            { return TK_DO;                 }
"import"        { return TK_IMPORT;             }
"procedure"     { return TK_PROCEDURE;          }
"function"      { return TK_FUNCTION;           }
"result"        { return TK_RESULT;             }
"is"            { return TK_IS;                 }
"global"        { return TK_GLOBAL;             }
"out"           { return TK_OUT;                }
"any"           { return TK_ANY;                }
"none"          { return TK_NONE;               }
"true"          { 
                    yylval.bval = true;
                    return TK_BOOLEAN; 
                }
"false"         { 
                    yylval.bval = false;
                    return TK_BOOLEAN;    
                }
"mod"           { return TK_MOD_OP;             }
"and"           { return TK_AND_OP;             }
"or"            { return TK_OR_OP;              }
"not"           { return TK_NOT_OP;             }
"string"        { return TK_STRING_KEYWORD;     }
"byte"          { return TK_BYTE_KEYWORD;       }
"integer"       { return TK_INTEGER_KEYWORD;    }
"boolean"       { return TK_BOOLEAN_KEYWORD;    }
"pointer"       { return TK_POINTER_KEYWORD;    }


0[xX]{H}{H}         {
                        yylval.oval = (unsigned char)strtoul(yytext, NULL, 0);
                        return TK_BYTE;
                    }
0[xX]{H}+           {
                        yylval.lval = (long)strtoul(yytext, NULL, 0);
                        return TK_INTEGER;
                    }
0{D}+               { 
                        yylval.lval = (long)strtoul(yytext, NULL, 0);
                        return TK_INTEGER;  
                    }
{D}+                { 
                        yylval.lval = (long)strtoul(yytext, NULL, 0);
                        return TK_INTEGER;
                    }
{L}({L}|{D})*       { 
                        yylval.sval = new string(yytext);
                        return TK_IDENTIFIER; 
                    }
\"(\\.|[^\\"])*\"   { 
                        yylval.sval = new string(TranslateString(yytext));
                        return TK_STRING;
                    }

":="        { return TK_ASSIGN_OP;      }
"<="        { return TK_LE_OP;          }
">="        { return TK_GE_OP;          }
"/="        { return TK_NE_OP;          }
"<<"        { return TK_ARRAY_BEGIN;    }
">>"        { return TK_ARRAY_END;      }
";"         { return ';';               }
"{"         { return '{';               }
"}"         { return '}';               }
","         { return ',';               }
":"         { return ':';               }
"="         { return '=';               }
"("         { return '(';               }
")"         { return ')';               }
"["         { return '[';               }
"]"         { return ']';               }
"."         { return '.';               }
"&"         { return '&';               }
"!"         { return '!';               }
"~"         { return '~';               }
"-"         { return '-';               }
"+"         { return '+';               }
"*"         { return '*';               }
"/"         { return '/';               }
"%"         { return '%';               }
"<"         { return '<';               }
">"         { return '>';               }
"^"         { return '^';               }
"|"         { return '|';               }
"?"         { return '?';               }

[ \t\v\n\f] {                       }
.           {                       }

%%

int
yywrap()
{
    return 1;
}

void 
Comment()
{
    char c = yyinput();

    while (c != EOF)
    {
        if (c == '\n')
        {
            break;
        }

        c = yyinput();
    }
}

static string
TranslateString(string str)
{
    string result;
    result.reserve(str.size());

    char previousCharacter = '\0';

    for (size_t i = 0; i < str.size(); i++)
    {
        if ((i == 0) || (i == str.size() - 1))
        {
            // Nothing to do.
        }
        else
        {
            if (previousCharacter == '\\')
            {
                ITS_ASSERT(result.size() >= 1);
                
                switch (str[i])
                {
                case 'n':
                    result[result.size() - 1] = '\n';
                    break;

                case 'r':
                    result[result.size() - 1] = '\r';
                    break;

                case 't':
                    result[result.size() - 1] = '\t';
                    break;

                case 'v':
                    result[result.size() - 1] = '\v';
                    break;

                case '"':
                    result[result.size() - 1] = '\"';
                    break;

                case '\'':
                    result[result.size() - 1] = '\'';
                    break;

                case '\\':
                    result[result.size() - 1] = '\\';
                    break;

                default:
                    result.append(1, str[i]);
                }
            }
            else
            {               
                result.append(1, str[i]);
            }
        }

        previousCharacter = str[i];
    }

    return result;
}
