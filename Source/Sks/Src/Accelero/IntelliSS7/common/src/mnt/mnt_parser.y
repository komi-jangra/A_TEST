%{

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:27  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:18  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.2  2002/10/28 18:53:25  mmiers
// LOG: Newer bison errors on multiply defined types
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/07/03 19:56:25  mmiers
// LOG: Warning removal
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.4  2001/10/09 19:17:04  hdivoux
// LOG: Added GetArraySize command and allowed for empty arrays.
// LOG:
// LOG: Revision 5.3  2001/08/20 22:06:26  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 5.2  2001/08/17 20:31:23  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.6  2001/08/16 20:15:03  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.5  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/10 22:42:44  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_parser.y,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

#include <mnt.h>
#include <malloc.h>
#include <mnt_constructs.h>

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace mnt;
#endif // defined(ITS_NAMESPACE)

extern int yylineno;
extern int yylex();
extern int yyerror(const char* s);

size_t mntErrorLineNumberG	= 0;
Construct* mntParsedTreeG	= NULL;

#ifdef _MSC_VER
#pragma warning(disable:4701)
#pragma warning(disable:4060)
#endif // _MSC_VER

%}


%token TK_IDENTIFIER
%token TK_BYTE
%token TK_INTEGER
%token TK_STRING
%token TK_ASSIGN_OP
%token TK_LE_OP
%token TK_GE_OP
%token TK_NE_OP
%token TK_MOD_OP
%token TK_AND_OP
%token TK_OR_OP
%token TK_NOT_OP
%token TK_END
%token TK_IF
%token TK_THEN
%token TK_ELSEIF
%token TK_ELSE
%token TK_FROM
%token TK_UNTIL
%token TK_LOOP
%token TK_DO
%token TK_IMPORT
%token TK_PROCEDURE
%token TK_FUNCTION
%token TK_RESULT
%token TK_IS
%token TK_GLOBAL
%token TK_OUT
%token TK_ANY
%token TK_NONE
%token TK_BOOLEAN
%token TK_STRING_KEYWORD
%token TK_BYTE_KEYWORD
%token TK_INTEGER_KEYWORD
%token TK_BOOLEAN_KEYWORD
%token TK_POINTER_KEYWORD
%token TK_ARRAY_BEGIN
%token TK_ARRAY_END



%type<cons> mnt_script
%type<cons> instruction_list
%type<cons> instruction
%type<cons> argument_list
%type<cons> argument
%type<cons> command_instruction
%type<cons> assignment_instruction
%type<cons> array_elt_assignment_instruction
%type<cons> conditional_instruction
%type<cons> then_part_list
%type<cons> then_part
%type<cons> else_part
%type<cons> loop_instruction
%type<cons> primary_expr
%type<cons> postfix_expr
%type<cons> unary_expr
%type<cons> unary_operator
%type<cons> multiplicative_expr
%type<cons> additive_expr
%type<cons> relational_expr
%type<cons> equality_expr
%type<cons> logical_and_expr
%type<cons> logical_or_expr
%type<cons> expr
%type<cons> manifest_array

%type<sval> TK_IDENTIFIER
%type<sval> TK_STRING

%type<lval> TK_INTEGER

%type<bval> TK_BOOLEAN

%type<oval> TK_BYTE

%type<vsval> string_manifest_array
%type<vlval> integer_manifest_array
%type<vbval> boolean_manifest_array
%type<voval> byte_manifest_array

%type<vsval> string_list
%type<vlval> integer_list
%type<vbval> boolean_list
%type<voval> byte_list


%union {
    mnt::Construct*	            cons;
    std::string*                sval;
    long                        lval;
    bool                        bval;
    unsigned char               oval;
    std::vector<std::string>*   vsval;
    std::vector<long>*          vlval;
    std::vector<bool>*          vbval;
    std::vector<unsigned char>* voval; 
}

%%


mnt_script
	:   /* Empty. */
        {
            $$ = new InstructionListCtr();
            $$->SetLineNumber(yylineno);
            mntParsedTreeG = $$;
            mntParsedTreeG->SetTopLevel();
        }	
    |   instruction_list
		{
			mntParsedTreeG = $1;
			mntParsedTreeG->SetTopLevel();
		}
	;

instruction_list
	:	instruction
		{
			$$ = new InstructionListCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);
		}
	|	instruction_list instruction
		{
			$$->GetChildren().push_back($2);
			$2->SetParent($$);
		}
    |
        instruction_list ';' instruction
        {
            $$->GetChildren().push_back($3);
            $3->SetParent($$);
        }
	;

instruction
	:	command_instruction
		{
			$$ = $1;
		}
	|	assignment_instruction
		{
			$$ = $1;
		}
    |   array_elt_assignment_instruction
        {
            $$ = $1;
        }
	|	conditional_instruction
		{
			$$ = $1;
		}
	|	loop_instruction
		{
			$$ = $1;
		}
	;

argument_list
	:	argument
		{
			$$ = new ArgumentListCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);
		}
	|	argument_list ',' argument
		{
			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
	;

argument
	:	expr
		{
			$$ = $1;
		}
    |   TK_OUT TK_IDENTIFIER
        {
            $$ = new IdentifierCtr();
            $$->SetLineNumber(yylineno);
            $$->SetValueString(*$2);
            delete $2;
            $$->SetOut();
        }
	;

command_instruction
	:   TK_IDENTIFIER '(' ')'
        {
            $$ = new CommandInstructionCtr();
            $$->SetLineNumber(yylineno);

            IdentifierCtr* identifierCtr = new IdentifierCtr();
            identifierCtr->SetLineNumber(yylineno);
            identifierCtr->SetValueString(*$1);
			delete $1;

            $$->GetChildren().push_back(identifierCtr);
			identifierCtr->SetParent($$);
        }
	|   TK_IDENTIFIER '(' argument_list ')'
        {
            $$ = new CommandInstructionCtr();
            $$->SetLineNumber(yylineno);

            IdentifierCtr* identifierCtr = new IdentifierCtr();
            identifierCtr->SetLineNumber(yylineno);
            identifierCtr->SetValueString(*$1);
			delete $1;

            $$->GetChildren().push_back(identifierCtr);
			identifierCtr->SetParent($$);

            $$->GetChildren().push_back($3);
			$3->SetParent($$);
        }
	;

assignment_instruction
	:	TK_IDENTIFIER TK_ASSIGN_OP expr
		{
			$$ = new AssignmentInstructionCtr();
			$$->SetLineNumber(yylineno);

            IdentifierCtr* identifierCtr = new IdentifierCtr();
            identifierCtr->SetLineNumber(yylineno);
            identifierCtr->SetValueString(*$1);
			delete $1;

            $$->GetChildren().push_back(identifierCtr);
			identifierCtr->SetParent($$);

            $$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
	;

array_elt_assignment_instruction
    :   TK_IDENTIFIER '[' argument ']' TK_ASSIGN_OP expr
        {
            $$ = new ArrayEltAssignmentInstructionCtr();
            $$->SetLineNumber(yylineno);

            IdentifierCtr* identifierCtr = new IdentifierCtr();
            identifierCtr->SetLineNumber(yylineno);
            identifierCtr->SetValueString(*$1);
            delete $1;

            $$->GetChildren().push_back(identifierCtr);
            identifierCtr->SetParent($$);

            $$->GetChildren().push_back($3);
            $3->SetParent($$);

            $$->GetChildren().push_back($6);
            $6->SetParent($$);
        }
	;

conditional_instruction
	:	TK_IF then_part_list TK_END
		{
			$$ = new ConditionalInstructionCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($2);
			$2->SetParent($$);
		}
	|	TK_IF then_part_list else_part TK_END
		{
			$$ = new ConditionalInstructionCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($2);
			$2->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}	
	;

then_part_list
	:	then_part
		{
			$$ = new ThenPartListCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);
		}
	|	then_part_list TK_ELSEIF then_part
		{
			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
	;

then_part
	:	expr TK_THEN instruction_list
		{
			$$ = new ThenPartCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
	;

else_part
	:	TK_ELSE instruction_list
		{
			$$ = new ElsePartCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($2);
			$2->SetParent($$);
		}
	;

loop_instruction
	:	TK_FROM instruction_list TK_UNTIL expr TK_LOOP instruction_list TK_END
		{
			$$ = new LoopInstructionCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($2);
			$2->SetParent($$);

			$$->GetChildren().push_back($4);
			$4->SetParent($$);

			$$->GetChildren().push_back($6);
			$6->SetParent($$);
		}
	;

primary_expr
	:	TK_IDENTIFIER
		{
			$$ = new IdentifierCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueString(*$1);
			delete $1;
		}
    |   TK_BYTE
        {
            $$ = new ByteCtr();
            $$->SetLineNumber(yylineno);
            $$->SetValueByte($1);
        }		
	|	TK_INTEGER
		{
			$$ = new IntegerCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueLong($1);
		}
	|	TK_STRING
		{
			$$ = new StringCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueString(*$1);
			delete $1;
		}
	|	TK_BOOLEAN
		{
			$$ = new BooleanCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueBool($1);
		}
    |   manifest_array
        {
            $$ = $1;
        }
	|	'(' expr ')'
		{
			$$ = $2;
		}
	;

manifest_array
    :   string_manifest_array
        {
            $$ = new StringArrayCtr();
			$$->SetLineNumber(yylineno);
            $$->SetValueStringArray(*$1);
            delete $1;
        }
    |   integer_manifest_array
        {
            $$ = new IntegerArrayCtr();
			$$->SetLineNumber(yylineno);
            $$->SetValueLongArray(*$1);
            delete $1;
        }
    |   boolean_manifest_array
        {
            $$ = new BooleanArrayCtr();
			$$->SetLineNumber(yylineno);
            $$->SetValueBoolArray(*$1);
            delete $1;
        }
    |   byte_manifest_array
        {
            $$ = new ByteArrayCtr();
			$$->SetLineNumber(yylineno);
            $$->SetValueByteArray(*$1);
            delete $1;
        }
    ;

string_manifest_array
    :   TK_ARRAY_BEGIN string_list TK_ARRAY_END
        {
            $$ = $2;
        }
    |   TK_ARRAY_BEGIN TK_STRING_KEYWORD TK_ARRAY_END
        {
            $$ = new vector<string>;
        }
    ;

integer_manifest_array
    :   TK_ARRAY_BEGIN integer_list TK_ARRAY_END
        {
            $$ = $2;
        }
    |   TK_ARRAY_BEGIN TK_INTEGER_KEYWORD TK_ARRAY_END
        {
            $$ = new vector<long>;
        }
    ;

boolean_manifest_array
    :   TK_ARRAY_BEGIN boolean_list TK_ARRAY_END
        {
            $$ = $2;
        }
    |   TK_ARRAY_BEGIN TK_BOOLEAN_KEYWORD TK_ARRAY_END
        {
            $$ = new vector<bool>;
        }
    ;

byte_manifest_array
    :   TK_ARRAY_BEGIN byte_list TK_ARRAY_END
        {
            $$ = $2;
        }
    |   TK_ARRAY_BEGIN TK_BYTE_KEYWORD TK_ARRAY_END
        {
            $$ = new vector<unsigned char>;
        }
    ;

string_list
    :   TK_STRING
        {
            $$ = new vector<string>;
            $$->push_back(*$1);
            delete $1;
        }
    |   string_list ',' TK_STRING
        {
            $$->push_back(*$3);
            delete $3;
        }
    ;

integer_list
    :   TK_INTEGER
        {
            $$ = new vector<long>;
            $$->push_back($1);
        }
    |   integer_list ',' TK_INTEGER
        {
            $$->push_back($3);
        }
    ;

boolean_list
    :   TK_BOOLEAN
        {
            $$ = new vector<bool>;
            $$->push_back($1);
        }
    |   boolean_list ',' TK_BOOLEAN
        {
            $$->push_back($3);
        }
    ;
        
byte_list
    :   TK_BYTE
        {
            $$ = new vector<unsigned char>;
            $$->push_back($1);
        }
    |   byte_list ',' TK_BYTE
        {
            $$->push_back($3);
        }
    ;

postfix_expr
	:	primary_expr
		{
			$$ = $1;
		}
	|	postfix_expr '(' ')'
		{
			$$ = new PostfixExprCtr();
			$$->SetLineNumber(yylineno);
            $$->SetValueString("command");

			$$->GetChildren().push_back($1);
			$1->SetParent($$);
		}
	|	postfix_expr '(' argument_list ')'
		{
			$$ = new PostfixExprCtr();
			$$->SetLineNumber(yylineno);
            $$->SetValueString("command");

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
    |   TK_IDENTIFIER '[' argument ']'
        {
            $$ = new PostfixExprCtr();
            $$->SetLineNumber(yylineno);
            $$->SetValueString("arrayEltAccess");

            IdentifierCtr* identifierCtr = new IdentifierCtr();
            identifierCtr->SetLineNumber(yylineno);
            identifierCtr->SetValueString(*$1);
            delete $1;

            $$->GetChildren().push_back(identifierCtr);
            identifierCtr->SetParent($$);

            $$->GetChildren().push_back($3);
			$3->SetParent($$);
        }
	;

unary_expr
	:	postfix_expr
		{
			$$ = $1;
		}
	|	unary_operator primary_expr
		{
			$$ = new UnaryExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($2);
			$2->SetParent($$);
		}
	;

unary_operator
	:	'+'
		{
			$$ = new UnaryOperatorCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueString("+");
		}
	|	'-'
		{
			$$ = new UnaryOperatorCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueString("-");
		}
	|	TK_NOT_OP
		{
			$$ = new UnaryOperatorCtr();
			$$->SetLineNumber(yylineno);
			$$->SetValueString("not");
		}
	;

multiplicative_expr
	:	unary_expr
		{
			$$ = $1;
		}
	|	multiplicative_expr '*' unary_expr
		{
			$$ = new MultiplicativeExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("*");
		}
	|	multiplicative_expr '/' unary_expr
		{
			$$ = new MultiplicativeExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("/");
		}
	|	multiplicative_expr TK_MOD_OP unary_expr
		{
			$$ = new MultiplicativeExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("mod");
		}
	;

additive_expr
	:	multiplicative_expr
		{
			$$ = $1;
		}
	|	additive_expr '+' multiplicative_expr
		{
			$$ = new AdditiveExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("+");
		}
	|	additive_expr '-' multiplicative_expr
		{
			$$ = new AdditiveExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("-");
		}
	;

relational_expr
	:	additive_expr
		{
			$$ = $1;
		}
	|	relational_expr '<' additive_expr
		{
			$$ = new RelationalExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("<");
		}
	|	relational_expr '>' additive_expr
		{
			$$ = new RelationalExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString(">");
		}
	|	relational_expr TK_LE_OP additive_expr
		{
			$$ = new RelationalExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("<=");
		}
	|	relational_expr TK_GE_OP additive_expr
		{
			$$ = new RelationalExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString(">=");
		}
	;

equality_expr
	:	relational_expr
		{
			$$ = $1;
		}
	|	equality_expr '=' relational_expr
		{
			$$ = new EqualityExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("=");
		}
	|	equality_expr TK_NE_OP relational_expr
		{
			$$ = new EqualityExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);

			$$->SetValueString("/=");
		}
	;

logical_and_expr
	:	equality_expr
		{
			$$ = $1;
		}
	|	logical_and_expr TK_AND_OP equality_expr
		{
			$$ = new LogicalAndExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
	;

logical_or_expr
	:	logical_and_expr
		{
			$$ = $1;
		}
	|	logical_or_expr TK_OR_OP logical_and_expr
		{
			$$ = new LogicalOrExprCtr();
			$$->SetLineNumber(yylineno);

			$$->GetChildren().push_back($1);
			$1->SetParent($$);

			$$->GetChildren().push_back($3);
			$3->SetParent($$);
		}
	;

expr
	:	logical_or_expr
		{
			$$ = $1;
		}
	;


%%

int
yyerror(const char* s)
{
	mntErrorLineNumberG = yylineno;
	return 0;
}

