

WHITESPC  [ \t\n\r]


%{

#include <exc_lex.h>

unsigned long lexLineNumber = 0;

void CountNewLines(unsigned long*, char*);

%}

%%

<INITIAL>{WHITESPC}+ { CountNewLines(&lexLineNumber, yytext); }
<INITIAL>"."                return DOT_SYMBOL;
<INITIAL>","                return COMMA_SYMBOL;
<INITIAL>"{"                return LEFTBRACE_SYMBOL;
<INITIAL>"}"                return RIGHTBRACE_SYMBOL;
<INITIAL>"("                return LEFTPAREN_SYMBOL;
<INITIAL>")"                return RIGHTPAREN_SYMBOL;
<INITIAL>"["                return LEFTBRACKET_SYMBOL;
<INITIAL>"]"                return RIGHTBRACKET_SYMBOL;
<INITIAL>"|"                return BAR_SYMBOL;
<INITIAL>";"                return SEMI_COLON_SYMBOL;
<INITIAL>subsystem          return SUBSYSTEM_KEYWORD_SYMBOL;
<INITIAL>exception          return EXCEPTION_KEYWORD_SYMBOL;
<INITIAL>is                 return IS_KEYWORD_SYMBOL;
<INITIAL>end                return END_KEYWORD_SYMBOL;
<INITIAL>number             return NUMBER_KEYWORD_SYMBOL;
<INITIAL>prefix             return PREFIX_KEYWORD_SYMBOL;
<INITIAL>option             return OPTION_KEYWORD_SYMBOL;
<INITIAL>reason             return REASON_KEYWORD_SYMBOL;
<INITIAL>attribute_type     return ATTRIBUTE_TYPE_KEYWORD_SYMBOL;
<INITIAL>parameter_type     return PARAMETER_TYPE_KEYWORD_SYMBOL;
<INITIAL>value              return VALUE_KEYWORD_SYMBOL;
<INITIAL>attribute          return ATTRIBUTE_KEYWORD_SYMBOL;
<INITIAL>argument           return ARGUMENT_KEYWORD_SYMBOL;
<INITIAL>code_header_before return CODE_HEADER_BEFORE_KEYWORD_SYMBOL;
<INITIAL>code_header_after  return CODE_HEADER_AFTER_KEYWORD_SYMBOL;
<INITIAL>code_source_before return CODE_SOURCE_BEFORE_KEYWORD_SYMBOL;
<INITIAL>code_source_after  return CODE_SOURCE_AFTER_KEYWORD_SYMBOL;
<INITIAL>code_before        return CODE_BEFORE_KEYWORD_SYMBOL;
<INITIAL>code_body          return CODE_BODY_KEYWORD_SYMBOL;
<INITIAL>code_after         return CODE_AFTER_KEYWORD_SYMBOL;
<INITIAL>description        return DESCRIPTION_KEYWORD_SYMBOL;
<INITIAL>file_name          return FILE_NAME_KEYWORD_SYMBOL;


<INITIAL>\'[0-1]*\'B {
          CountNewLines(&lexLineNumber, yytext);
          yylval.charPtr = (char*)Malloc(yyleng);
          strncpy(yylval.charPtr, yytext+1, yyleng -1);      /* Strip "'"s. */
          yylval.charPtr[yyleng-2] = '\0';
          return BINARY_STRING_SYMBOL;}

<INITIAL>\'[0-9A-Fa-f]*\'H {
          CountNewLines(&lexLineNumber, yytext);
          yylval.charPtr = (char*)Malloc(yyleng);
          strncpy(yylval.charPtr, yytext+1, yyleng -1);       /* Strip "'"s. */
          yylval.charPtr[yyleng-2] = '\0';
          return HEXA_STRING_SYMBOL;}

<INITIAL>\"([^\"]|"\"\"")*\"  {
          CountNewLines(&lexLineNumber, yytext);
          yylval.charPtr = (char*)Malloc(yyleng);
          strncpy(yylval.charPtr, yytext+1, yyleng -1);       /* Strip '"'s. */
          yylval.charPtr[yyleng-2] = '\0';  /* 2 quotes == quote in a quote. */
          return STRING_SYMBOL;}  

<INITIAL>[a-zA-Z_][a-zA-Z0-9_]* {
          yylval.charPtr = (char*)Malloc(yyleng+1);
          strcpy(yylval.charPtr, yytext);
          yylval.charPtr[yyleng] = '\0';
          return IDENTIFIER_SYMBOL;}

<INITIAL>[1-9][0-9]* { /* First digit cannot be zero on multi-digit #'s. */
          yylval.intVal = atol(yytext);
          return NUMBER_SYMBOL;} 


<INITIAL>"--"(-[^\-\n]|[^\-\n])*("--"|\n|"-\n") {

        /* Eat comments and update line number. */

        CountNewLines(&lexLineNumber, yytext);}


%%

void CountNewLines(unsigned long* cumulativeTotal, char* nullTermStr)
{                                                
    int index = 0;                             

    for(index = 0; nullTermStr[index] != '\0'; index++)
    {
        if (nullTermStr[index] == '\n')
        {
            (*cumulativeTotal)++;
        }
    }
}

/* some platforms are weird */
#ifndef yywrap

int yywrap()
{
	return 1;
}

#endif


