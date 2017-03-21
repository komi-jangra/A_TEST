


%{

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


%}


/*
 *	Union structure.  A terminal or non-terminal can have one of these type
 *  values.
 */

%union
{
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
}


/*
 *	Terminals.
 */

/*
 *  These tokens (literals) have attributes.
 */

%token <charPtr> BINARY_STRING_SYMBOL HEXA_STRING_SYMBOL
                 STRING_SYMBOL IDENTIFIER_SYMBOL

%token <intVal>  NUMBER_SYMBOL



/*
 *  These tokens have no attributes.
 */

%token           DOT_SYMBOL COMMA_SYMBOL LEFTBRACE_SYMBOL RIGHTBRACE_SYMBOL
                 LEFTPAREN_SYMBOL RIGHTPAREN_SYMBOL LEFTBRACKET_SYMBOL
                 RIGHTBRACKET_SYMBOL BAR_SYMBOL SEMI_COLON_SYMBOL
                 SUBSYSTEM_KEYWORD_SYMBOL EXCEPTION_KEYWORD_SYMBOL
                 IS_KEYWORD_SYMBOL END_KEYWORD_SYMBOL NUMBER_KEYWORD_SYMBOL
                 PREFIX_KEYWORD_SYMBOL OPTION_KEYWORD_SYMBOL 
                 REASON_KEYWORD_SYMBOL ATTRIBUTE_TYPE_KEYWORD_SYMBOL
                 PARAMETER_TYPE_KEYWORD_SYMBOL VALUE_KEYWORD_SYMBOL
                 ATTRIBUTE_KEYWORD_SYMBOL ARGUMENT_KEYWORD_SYMBOL
                 CODE_HEADER_BEFORE_KEYWORD_SYMBOL
                 CODE_HEADER_AFTER_KEYWORD_SYMBOL
                 CODE_SOURCE_BEFORE_KEYWORD_SYMBOL
                 CODE_SOURCE_AFTER_KEYWORD_SYMBOL
                 CODE_BEFORE_KEYWORD_SYMBOL CODE_BODY_KEYWORD_SYMBOL
                 CODE_AFTER_KEYWORD_SYMBOL DESCRIPTION_KEYWORD_SYMBOL
                 FILE_NAME_KEYWORD_SYMBOL

/*
 *  Type definitions of non-terminal symbols.
 */

%type <intVal>  NumberEntry

%type <stringPtr> String FileEntry Identifier
                  CodeHeaderBeforeEntry CodeHeaderAfterEntry
                  CodeSourceBeforeEntry CodeSourceAfterEntry
                  PrefixEntry ReasonEntry 
                  CodeBeforeEntry CodeAfterEntry CodeBodyEntry
                  AttributeTypeEntry ParameterTypeEntry ValueEntry

%type <optionListPtr> OptionList OptionClause

%type <optionPtr> Option

%type <exceptionListPtr> ExceptionList SubsystemBody

%type <exceptionPtr> Exception

%type <descriptionListPtr> DescriptionList

%type <descriptionPtr> Description

%type <argumentListPtr> ArgumentList ArgumentClause

%type <argumentPtr> Argument

%type <attributeListPtr> AttributeList

%type <attributePtr> Attribute



%start SubsystemDefinition 
%%



/*
 *  Productions.
 */

SubsystemDefinition:
    SUBSYSTEM_KEYWORD_SYMBOL
    Identifier
    NumberEntry
    PrefixEntry
    FileEntry
    OptionClause
    CodeHeaderBeforeEntry
    CodeHeaderAfterEntry
    CodeSourceBeforeEntry
    CodeSourceAfterEntry
    SubsystemBody
    END_KEYWORD_SYMBOL
    {
        subsystemPtr->name = *($2);
        subsystemPtr->number = $3;
        subsystemPtr->prefix = *($4);
        subsystemPtr->fileName = *($5);
#if 0
        subsystemPtr->optionList.assign(($6)->begin(), ($6)->end());
#else
        subsystemPtr->optionList.erase(subsystemPtr->optionList.begin(),
                                       subsystemPtr->optionList.end());
        subsystemPtr->optionList.insert(subsystemPtr->optionList.end(),
                                        ($6)->begin(), ($6)->end());
#endif
        subsystemPtr->codeHeaderBefore = *($7);
        subsystemPtr->codeHeaderAfter = *($8);
        subsystemPtr->codeSourceBefore = *($9);
        subsystemPtr->codeSourceAfter = *($10);
#if 0
        subsystemPtr->exceptionList.assign(($11)->begin(), ($11)->end());
#else
        subsystemPtr->exceptionList.erase(subsystemPtr->exceptionList.begin(),
                                          subsystemPtr->exceptionList.end());
        subsystemPtr->exceptionList.insert(subsystemPtr->exceptionList.end(),
                                           ($11)->begin(), ($11)->end());
#endif
    }     
;

SubsystemBody:
    ExceptionList
    {
        $$ = $1;
    }
;

ExceptionList:
    ExceptionList Exception
    {
        $1->push_back($2);
        $$ = $1;
    }
  | Exception
    {
        $$ = new ExceptionList();
        $$->push_back($1);
    }
  |
    {
        $$ = new ExceptionList();
    }
;

Exception:
    EXCEPTION_KEYWORD_SYMBOL
    Identifier
    NumberEntry
    ReasonEntry
    OptionClause
    CodeHeaderBeforeEntry
    CodeHeaderAfterEntry
    CodeSourceBeforeEntry
    CodeSourceAfterEntry
    CodeBeforeEntry
    CodeBodyEntry
    CodeAfterEntry
    DescriptionList
    AttributeList
    END_KEYWORD_SYMBOL
    {
        $$ = new Exception();
        $$->name = *($2);
        $$->number = $3;
        $$->reason = *($4);
#if 0
        $$->optionList.assign(($5)->begin(), ($5)->end());
#else
        subsystemPtr->optionList.erase(subsystemPtr->optionList.begin(),
                                       subsystemPtr->optionList.end());
        subsystemPtr->optionList.insert(subsystemPtr->optionList.end(),
                                        ($5)->begin(), ($5)->end());
#endif
        $$->codeHeaderBefore = *($6);
        $$->codeHeaderAfter = *($7);
        $$->codeSourceBefore = *($8);
        $$->codeSourceAfter = *($9);
        $$->codeBefore = *($10);
        $$->codeBody = *($11);
        $$->codeAfter = *($12);
#if 0
        $$->descriptionList.assign(($13)->begin(), ($13)->end());
#else
        $$->descriptionList.erase($$->descriptionList.begin(),
                                  $$->descriptionList.end());
        $$->descriptionList.insert($$->descriptionList.end(),
                                   ($13)->begin(), ($13)->end());
#endif
#if 0
        $$->attributeList.assign(($14)->begin(), ($14)->end());
#else
        $$->attributeList.erase($$->attributeList.begin(),
                                $$->attributeList.end());
        $$->attributeList.insert($$->attributeList.end(),
                                 ($14)->begin(), ($14)->end());
#endif
    }
;

DescriptionList:
    DescriptionList Description
    {
        $1->push_back($2);
        $$ = $1;
    }
  | Description
    {
        $$ = new DescriptionList();
        $$->push_back($1);
    }
  |
    {
        $$ = new DescriptionList();
    }
;

Description:
    DESCRIPTION_KEYWORD_SYMBOL
    Identifier
    ValueEntry
    ArgumentClause
    END_KEYWORD_SYMBOL
    {
        $$ = new Description();
        $$->name = *($2);
        $$->value = *($3);
#if 0
        $$->argumentList.assign(($4)->begin(), ($4)->end());
#else
        $$->argumentList.erase($$->argumentList.begin(),
                               $$->argumentList.end());
        $$->argumentList.insert($$->argumentList.end(),
                                ($4)->begin(), ($4)->end());
#endif
    }
;

ValueEntry:
    VALUE_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
;

ArgumentClause:
    ARGUMENT_KEYWORD_SYMBOL
    ArgumentList
    END_KEYWORD_SYMBOL
    {
        $$ = $2;
    }
  |
    {
        $$ = new ArgumentList();
    }
;

ArgumentList:
    ArgumentList COMMA_SYMBOL Argument
    {
        $1->push_back($3);
        $$ = $1;
    }
  | Argument
    {
        $$ = new ArgumentList();
        $$->push_back($1);
    }
;

Argument:
    Identifier
    {
        $$ = new Argument();
        $$->name = *($1);
    }
  |
    Identifier
    OPTION_KEYWORD_SYMBOL
    CodeBeforeEntry
    CodeAfterEntry
    END_KEYWORD_SYMBOL
    {
        $$ = new Argument();
        $$->name = *($1);
        $$->codeBefore = *($3);
        $$->codeAfter = *($4);
    }
;

AttributeList:
    AttributeList Attribute
    {
        $1->push_back($2);
        $$ = $1;
    }
  | Attribute
    {
        $$ = new AttributeList();
        $$->push_back($1);
    }
  |
    {
        $$ = new AttributeList();
    }
;

Attribute:
    ATTRIBUTE_KEYWORD_SYMBOL
    Identifier
    AttributeTypeEntry
    ParameterTypeEntry
    END_KEYWORD_SYMBOL
    {
        $$ = new Attribute();
        $$->name = *($2);
        $$->attributeType = *($3);
        $$->parameterType = *($4);
    }
;

AttributeTypeEntry:
    ATTRIBUTE_TYPE_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
;

ParameterTypeEntry:
    PARAMETER_TYPE_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
;

ReasonEntry:
    REASON_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
;

NumberEntry:
    NUMBER_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    NUMBER_SYMBOL
    {
        $$ = $3;
    }
;

PrefixEntry:
    PREFIX_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    Identifier
    {
        $$ = $3;
    }
    |
    PREFIX_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    {
        $$ = new string;
    }
;

OptionClause:
    OPTION_KEYWORD_SYMBOL
    OptionList
    END_KEYWORD_SYMBOL
    {
        $$ = $2;
    }
  |
    {
        $$ = new OptionList();
    }
;

OptionList:
    OptionList COMMA_SYMBOL Option
    {
        $1->push_back($3);
        $$ = $1;
    }
  | Option
    {
        $$ = new OptionList();
        $$->push_back($1);
    }
;

Option:
    Identifier
    {
        $$ = new Option();
        $$->name = *($1);
    }
;

String:
    String STRING_SYMBOL
    {
        $1->append($2);
        $$ = $1;
    }
  | STRING_SYMBOL
    {
        $$ = new string($1);
    } 
;


Identifier:
    IDENTIFIER_SYMBOL
    {
        $$ = new string($1);
    }
;

FileEntry:

    FILE_NAME_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
;

CodeHeaderBeforeEntry:
    CODE_HEADER_BEFORE_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;

CodeHeaderAfterEntry:
    CODE_HEADER_AFTER_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;

CodeSourceBeforeEntry:
    CODE_SOURCE_BEFORE_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;

CodeSourceAfterEntry:
    CODE_SOURCE_AFTER_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;

CodeBeforeEntry:
    CODE_BEFORE_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;

CodeBodyEntry:
    CODE_BODY_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;

CodeAfterEntry:
    CODE_AFTER_KEYWORD_SYMBOL
    IS_KEYWORD_SYMBOL
    String
    {
        $$ = $3;
    }
  |
    {
        $$ = new string("");
    }
;
        
    


%%

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




