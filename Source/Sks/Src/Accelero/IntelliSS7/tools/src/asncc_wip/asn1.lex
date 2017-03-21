
%{

/*******************************************************************************
**                                                                            **
**      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     **
**              Manufactured in the United States of America.                 **
**        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        **
**                                                                            **
**    This product and related documentation is protected by copyright and    **
**    distributed under licenses restricting its use, copying, distribution   **
**    and decompilation.  No part of this product or related documentation    **
**    may be reproduced in any form by any means without prior written        **
**    authorization of IntelliNet Technologies and its licensors, if any.     **
**                                                                            **
**    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       **
**    government is subject to restrictions as set forth in subparagraph      **
**    (c)(1)(ii) of the Rights in Technical Data and Computer Software        **
**    clause at DFARS 252.227-7013 and FAR 52.227-19.                         **
**                                                                            **
********************************************************************************
**                                                                            **
** CONTRACT: INTERNAL                                                         **
**                                                                            **
********************************************************************************
**
**  ID: $Id: asn1.lex,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
**
*******************************************************************************/


#include <asncc.h>
#include <asncc_ast.h>
#include <asncc_parser.h>

#include <ctype.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif /* defined(ITS_STD_NAMESPACE) */

extern FILE * yyin;

extern unsigned long    lineNumberG;
extern string           asn1SrcFileNameG;  

extern Module*          moduleG; 

int lexEchoG = false;

#define YY_USER_ACTION if (lexEchoG) cout << yytext << flush;


int referenceTokenContextG      = TK_MODULE_REFERENCE;
int identifierTokenContextG     = TK_IDENTIFIER;
int braceTokenContextG          = '{';
int nullTokenContextG           = TK_NULL;


TypeList* currentImportListG    = NULL;

extern "C" int yywrap() { return 1; }


static void 
UpdateLineNumber(unsigned long& currentLineNumber, string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '\n')
        {
            currentLineNumber++;
        }
    }
}

static string 
RemoveWhiteSpacesAndNewLines(string str)
{
    string result;
    result.reserve(str.size());

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '\n' || str[i] == ' ')
        {
            // Nothing to do.
        }
        else
        {
            result.append(1, str[i]);
        }
    }

    return result;
}

static string
RemoveQuotesOrBraces(string str)
{
    string result;
    result.reserve(str.size());

    for (size_t i = 0; i < str.size(); i++)
    {
        if ((i == 0) || (i == str.size() - 1))
        {
            // Nothing to do.
        }
        else
        {
            result.append(1, str[i]);
        }
    }

    return result;
}

static string
RemoveQuotesAndQualifier(string str)
{
    string result;
    result.reserve(str.size());

    for (size_t i = 0; i < str.size(); i++)
    {
        if ((i == 0) || (i == str.size() - 1) || (i == str.size() - 2))
        {
            // Nothing to do.
        }
        else
        {
            result.append(1, str[i]);
        }
    }

    return result;
}


%}

%x COMMENT

BS_BSTRING \'[0-1]*\'B

BS_HSTRING \'[0-1]*\'H

OS_BSTRING \'[0-9A-Fa-f]*\'B

OS_HSTRING \'[0-9A-Fa-f]*\'H

CSTRING (\"[^\"]*\")(\"[^\"]*\")*

NUMBER (0|[1-9][0-9]*)

IDENTIFIER ([a-z]|([a-z][a-zA-Z0-9_-]*[a-zA-Z0-9_]))

REFERENCE ([A-Z]|([A-Z][a-zA-Z0-9_-]*[a-zA-Z0-9_]))

VALUE_FIELD_REFERENCE "&"([a-z]|([a-z][a-zA-Z0-9_-]*[a-zA-Z0-9_]))

TYPE_FIELD_REFERENCE "&"([A-Z]|([A-Z][a-zA-Z0-9_-]*[a-zA-Z0-9_]))

OBJECT_IDENTIFIER_VALUE "{"[ ]*({IDENTIFIER}[ \t\r\n]*"("[ \t\r\n]*{NUMBER}[ \t\r\n]*")"[ \t\r\n]*)+[ \t\r\n]*"}"


%%

"::="                               { return TK_ASSIGNMENT;          }
"ABSENT"                            { return TK_ABSENT;              }              
"ABSTRACT-SYNTAX"                   { return TK_ABSTRACT_SYNTAX;     }
"ALL"                               { return TK_ALL;                 }
"APPLICATION"                       { return TK_APPLICATION;         }
"AUTOMATIC"                         { return TK_AUTOMATIC;           }
"BEGIN"                             { return TK_BEGIN;               }
"BIT"                               { return TK_BIT;                 }
"BMPString"                         { return TK_BMP_STRING;          }
"BOOLEAN"                           { return TK_BOOLEAN;             }
"BY"                                { return TK_BY;                  }
"CHARACTER"                         { return TK_CHARACTER;           }
"CHOICE"                            { return TK_CHOICE;              }
"CLASS"                             { return TK_CLASS;               }
"COMPONENT"                         { return TK_COMPONENT;           }
"COMPONENTS"                        { return TK_COMPONENTS;          }
"CONSTRAINED"                       { return TK_CONSTRAINED;         }
"DEFAULT"                           { return TK_DEFAULT;             }
"DEFINITIONS"                       { return TK_DEFINITIONS;         }
"EMBEDDED"                          { return TK_EMBEDDED;            }
"END"                               { return TK_END;                 }
"ENUMERATED"                        { return TK_ENUMERATED;          }
"EXCEPT"                            { return TK_EXCEPT;              }
"EXPLICIT"                          { return TK_EXPLICIT;            }
"EXPORTS"                           { return TK_EXPORTS;             }
"EXTERNAL"                          { return TK_EXTERNAL;            }
"FALSE"                             { return TK_FALSE;               }
"FROM"                              { return TK_FROM;                }
"GeneralString"                     { return TK_GENERAL_STRING;      }
"GraphicString"                     { return TK_GRAPHIC_STRING;      }
"IA5String"                         { return TK_IA5_STRING;          }
"TYPE-IDENTIFIER"                   { return TK_TYPE_IDENTIFIER;     }
"IDENTIFIER"                        { return TK_IDENTIFIER;          }
"IMPLICIT"                          { return TK_IMPLICIT;            }
"IMPORTS"                           { return TK_IMPORTS;             }
"INCLUDES"                          { return TK_INCLUDES;            }
"INSTANCE"                          { return TK_INSTANCE;            }
"INTEGER"                           { return TK_INTEGER;             }
"INTERSECTION"                      { return TK_INTERSECTION;        }
"ISO646String"                      { return TK_ISO646_STRING;       }
"MAX"                               { return TK_MAX;                 }
"MIN"                               { return TK_MIN;                 }
"MINUS-INFINITY"                    { return TK_MINUS_INFINITY;      }
"NOTATION"                          { return TK_NOTATION;            }
"NULL"                              { return nullTokenContextG;      }
"NumericString"                     { return TK_NUMERIC_STRING;      }
"OBJECT"                            { return TK_OBJECT;              }
"OCTET"                             { return TK_OCTET;               }
"OF"                                { return TK_OF;                  }
"OPTIONAL"                          { return TK_OPTIONAL;            }
"PDV"                               { return TK_PDV;                 }
"PLUS-INFINITY"                     { return TK_PLUS_INFINITY;       }
"PRESENT"                           { return TK_PRESENT;             }
"PrintableString"                   { return TK_PRINTABLE_STRING;    }
"PRIVATE"                           { return TK_PRIVATE;             }
"REAL"                              { return TK_REAL;                }
"SEQUENCE"                          { return TK_SEQUENCE;            }
"SET"                               { return TK_SET;                 }
"SIZE"                              { return TK_SIZE;                }
"STRING"                            { return TK_STRING;              }
"SYNTAX"                            { return TK_SYNTAX;              }
"T61String"                         { return TK_T61_STRING;          }
"TAGS"                              { return TK_TAGS;                }
"TeletexString"                     { return TK_TELETEX_STRING;      }
"TRUE"                              { return TK_TRUE;                }
"UNION"                             { return TK_UNION;               }
"UNIQUE"                            { return TK_UNIQUE;              }
"UNIVERSAL"                         { return TK_UNIVERSAL;           }
"UniversalString"                   { return TK_UNIVERSAL_STRING;    }
"VALUE"                             { return TK_VALUE;               }
"VideotexString"                    { return TK_VIDEOTEX_STRING;     }
"VisibleString"                     { return TK_VISIBLE_STRING;      }
"WITH"                              { return TK_WITH;                }
"ANY"                               { return TK_ANY;                 }
"DEFINED"                           { return TK_DEFINED;             }

                                                                 

"--" {
    
    BEGIN(COMMENT);
}

<COMMENT>"--" {
    
    BEGIN(INITIAL);
}

<COMMENT>\n {
    
    lineNumberG++;
    BEGIN(INITIAL);
}

<COMMENT>. 
{

}


"@"  { return '@'; }

"{"  { return braceTokenContextG; }

"}"  { return '}'; }

"["  { return '['; }

"]"  { return ']'; }

"("  { return '('; }

")"  { return ')'; }

"<"  { return '<'; }

">"  { return '>'; }

"|"  { return '|'; }

";"  { return ';'; }

"+"  { return '+'; }

"-"  { return '-'; }

"*"  { return '*'; }

"/"  { return '/'; }

","  { return ','; }

"."  { return '.'; }

":"  { return ':'; }

"="  { return '='; }

'|'  { return '|'; }

"^"  { return '^'; }



{BS_BSTRING} {

    UpdateLineNumber(lineNumberG, yytext);
    
    string str = RemoveWhiteSpacesAndNewLines(yytext);
    str = RemoveQuotesAndQualifier(str);
    yylval.stringSemanticValue = new string(str);
    return TK_BS_BSTRING;
}


{BS_HSTRING} {

    UpdateLineNumber(lineNumberG, yytext);
    
    string str = RemoveWhiteSpacesAndNewLines(yytext);
    str = RemoveQuotesAndQualifier(str);
    yylval.stringSemanticValue = new string(str);
    return TK_BS_HSTRING;
}


{OS_BSTRING} {

    UpdateLineNumber(lineNumberG, yytext);

    string str = RemoveWhiteSpacesAndNewLines(yytext);
    str = RemoveQuotesAndQualifier(str);
    yylval.stringSemanticValue = new string(str);
    return TK_OS_BSTRING;
}


{OS_HSTRING} {

    UpdateLineNumber(lineNumberG, yytext);

    string str = RemoveWhiteSpacesAndNewLines(yytext);
    str = RemoveQuotesAndQualifier(str);
    yylval.stringSemanticValue = new string(str);
    return TK_OS_HSTRING;
}


{CSTRING} {

    UpdateLineNumber(lineNumberG, yytext);

    string str = RemoveWhiteSpacesAndNewLines(yytext);
    str = RemoveQuotesOrBraces(str);
    yylval.stringSemanticValue = new string(str);
    return TK_CSTRING;
}


{NUMBER} {   

    yylval.longSemanticValue = atol(yytext);
    return TK_NUMBER;
}


{IDENTIFIER} {

    yylval.stringSemanticValue = new string(yytext);

    if (moduleG != NULL)
    {
        if (moduleG->HasObjectReference(*(yylval.stringSemanticValue)))
        {
            return TK_OBJECT_REFERENCE;
        }
    }

    bool foundAsImport = false;

    if (currentImportListG != NULL)
    {
        for (TypeList::iterator iter = currentImportListG->begin();
             iter != currentImportListG->end();
             iter++)
        {
            Type* type = *iter;

            if (type->GetType() == TYPE_IMPORTED)
            {
                ImportedType* importedType = static_cast<ImportedType*> (type);

                if (importedType->GetName() == *(yylval.stringSemanticValue))
                {
                    foundAsImport = true;
                }
            }
        }
    }

    if (foundAsImport)
    {
        return TK_IMPORT_IDENTIFIER;
    }
    else
    {
        return identifierTokenContextG;
    }
}



{VALUE_FIELD_REFERENCE} {   

    yylval.stringSemanticValue = new string(yytext);
    return TK_VALUE_FIELD_REFERENCE;
}



{TYPE_FIELD_REFERENCE} {    

    yylval.stringSemanticValue = new string(yytext);
    return TK_TYPE_FIELD_REFERENCE;
}


{REFERENCE} {       
   
    yylval.stringSemanticValue = new string(yytext);

    if (moduleG != NULL)
    {
        if (moduleG->HasObjectClassReference(*(yylval.stringSemanticValue)))
        {
            return TK_OBJECT_CLASS_REFERENCE; 
        }

        if (moduleG->HasObjectSetReference(*(yylval.stringSemanticValue)))
        {
            return TK_OBJECT_SET_REFERENCE;
        }
    }

    bool foundAsImport = false;

    if (currentImportListG != NULL)
    {
        for (TypeList::iterator iter = currentImportListG->begin();
             iter != currentImportListG->end();
             iter++)
        {
            Type* type = *iter;

            if (type->GetType() == TYPE_IMPORTED)
            {
                ImportedType* importedType = static_cast<ImportedType*> (type);

                if (importedType->GetName() == *(yylval.stringSemanticValue))
                {
                    foundAsImport = true;
                }
            }
        }
    }

    if (foundAsImport)
    {
        return TK_IMPORT_IDENTIFIER;
    }
    else
    {
        return referenceTokenContextG;
    }
}

{OBJECT_IDENTIFIER_VALUE} {

    UpdateLineNumber(lineNumberG, yytext);

    string str = RemoveQuotesOrBraces(yytext);
    yylval.stringSemanticValue = new string(str);
    return TK_OBJECT_IDENTIFIER_VALUE;
}


[ \t\r] { 

}


\n {
    
    lineNumberG++;
}

. {
    fprintf(stderr,"%s(%d) : ERROR - unknown token \"%s\".\n",
            asn1SrcFileNameG.c_str(), lineNumberG, yytext);
}


%%

