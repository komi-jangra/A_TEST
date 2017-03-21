%expect 15

%{

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: asn1.yacc,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_ast.h>
#include <asncc_util.h>
#include <asncc_command_interpreter.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

extern int yylex();

extern int referenceTokenContextG;
extern int identifierTokenContextG;
extern int braceTokenContextG;
extern int nullTokenContextG;
extern TypeList* currentImportListG;
extern unsigned long lineNumberG;
extern string asn1SrcFileNameG;

Module* moduleG                         = NULL;

static int unnamedFieldCountG           = 1;
static list<string*>* dummyParametersG  = NULL;




static string
GetUnnamedFieldName(unsigned long unnamedFieldCount)
{
    char buffer[32];

    sprintf(buffer, "_unnamed%lu", unnamedFieldCount);

    string result = buffer;
    
    return result;
}


#ifdef _MSC_VER
#pragma warning(disable:4701)
#endif // _MSC_VER

%}

%token TK_IDENTIFIER
%token TK_BIT_IDENTIFIER
%token TK_OID_IDENTIFIER
%token TK_IMPORT_IDENTIFIER
%token TK_MODULE_REFERENCE
%token TK_TYPE_REFERENCE
%token TK_OBJECT_CLASS_REFERENCE
%token TK_TYPE_FIELD_REFERENCE
%token TK_VALUE_FIELD_REFERENCE
%token TK_VALUE_SET_FIELD_REFERENCE
%token TK_OBJECT_FIELD_REFERENCE
%token TK_OBJECT_SET_FIELD_REFERENCE
%token TK_OBJECT_REFERENCE
%token TK_OBJECT_SET_REFERENCE
%token TK_NUMBER
%token TK_OBJECT_IDENTIFIER_VALUE

%token TK_CSTRING
%token TK_OS_BSTRING
%token TK_BS_BSTRING
%token TK_OS_HSTRING
%token TK_BS_HSTRING

%token TK_STRING_BRACE
%token TK_BIT_STRING_BRACE
%token TK_OID_BRACE

%token TK_ABSENT  
%token TK_ABSTRACT_SYNTAX
%token TK_ALL              
%token TK_APPLICATION
%token TK_ASSIGNMENT
%token TK_AUTOMATIC 
%token TK_BEGIN
%token TK_BIT              
%token TK_BMP_STRING
%token TK_BOOLEAN
%token TK_BY
%token TK_CHARACTER        
%token TK_CHOICE  
%token TK_CLASS     
%token TK_COMPONENT      
%token TK_COMPONENTS  
%token TK_CONSTRAINED 
%token TK_DEFAULT
%token TK_DEFINITIONS    
%token TK_EMBEDDED
%token TK_END
%token TK_ENUMERATED
%token TK_EXCEPT 
%token TK_EXPLICIT     
%token TK_EXPORTS   
%token TK_EXTERNAL    
%token TK_FALSE    
%token TK_FROM      
%token TK_GENERAL_STRING    
%token TK_GRAPHIC_STRING
%token TK_IA5_STRING
%token TK_TYPE_IDENTIFIER
%token TK_IDENTIFIER
%token TK_IMPLICIT 
%token TK_IMPORTS   
%token TK_INCLUDES    
%token TK_INSTANCE   
%token TK_INTEGER 
%token TK_INTERSECTION    
%token TK_ISO646_STRING
%token TK_MAX
%token TK_MIN        
%token TK_MINUS_INFINITY
%token TK_NOTATION
%token TK_NULL_VALUE
%token TK_NULL
%token TK_NUMERIC_STRING
%token TK_OBJECT
%token TK_OCTET     
%token TK_OF       
%token TK_OPTIONAL
%token TK_PDV   
%token TK_PLUS_INFINITY
%token TK_PRESENT
%token TK_PRINTABLE_STRING  
%token TK_PRIVATE
%token TK_REAL    
%token TK_SEQUENCE       
%token TK_SET   
%token TK_SIZE         
%token TK_STRING       
%token TK_SYNTAX     
%token TK_T61_STRING     
%token TK_TAGS 
%token TK_TELETEX_STRING    
%token TK_TRUE
%token TK_UNION       
%token TK_UNIQUE      
%token TK_UNIVERSAL        
%token TK_UNIVERSAL_STRING  
%token TK_VIDEOTEX_STRING
%token TK_VISIBLE_STRING
%token TK_GENERALIZED_TIME
%token TK_UTC_TIME
%token TK_VALUE
%token TK_WITH
%token TK_OBJECT_DESCRIPTOR
%token TK_ANY
%token TK_DEFINED

%type <longSemanticValue> TK_NUMBER
%type <longSemanticValue> TagDefault
%type <longSemanticValue> SignedNumber
%type <longSemanticValue> Class
%type <longSemanticValue> ClassNumber
%type <longSemanticValue> PresenceConstraint

%type <stringSemanticValue> TK_CSTRING
%type <stringSemanticValue> TK_BS_BSTRING
%type <stringSemanticValue> TK_OS_BSTRING
%type <stringSemanticValue> TK_BS_HSTRING
%type <stringSemanticValue> TK_OS_HSTRING
%type <stringSemanticValue> TK_IDENTIFIER
%type <stringSemanticValue> TK_BIT_IDENTIFIER
%type <stringSemanticValue> TK_OID_IDENTIFIER
%type <stringSemanticValue> TK_IMPORT_IDENTIFIER
%type <stringSemanticValue> TK_TYPE_REFERENCE
%type <stringSemanticValue> TK_MODULE_REFERENCE
%type <stringSemanticValue> TK_OBJECT_CLASS_REFERENCE
%type <stringSemanticValue> TK_TYPE_FIELD_REFERENCE
%type <stringSemanticValue> TK_VALUE_FIELD_REFERENCE
%type <stringSemanticValue> TK_VALUE_SET_FIELD_REFERENCE
%type <stringSemanticValue> TK_OBJECT_FIELD_REFERENCE
%type <stringSemanticValue> TK_OBJECT_SET_FIELD_REFERENCE
%type <stringSemanticValue> TK_OBJECT_REFERENCE
%type <stringSemanticValue> TK_OBJECT_SET_REFERENCE
%type <stringSemanticValue> TK_OBJECT_IDENTIFIER_VALUE
%type <stringSemanticValue> DefinitiveObjIdComponent
%type <stringSemanticValue> DefinitiveNameAndNumberForm
%type <stringSemanticValue> GlobalModuleReference
%type <stringSemanticValue> Reference
%type <stringSemanticValue> ExternalTypeReference 
%type <stringSemanticValue> ExternalValueReference
%type <stringSemanticValue> SimpleDefinedType
%type <stringSemanticValue> ComponentIdList
%type <stringSemanticValue> CharsDefn
%type <stringSemanticValue> SimpleDefinedValue
%type <stringSemanticValue> FieldName PrimitiveFieldName
%type <stringSemanticValue> DefinedObjectClass
%type <stringSemanticValue> ExternalObjectClassReference
%type <stringSemanticValue> UsefulObjectClassReference
%type <stringSemanticValue> Parameter
%type <stringSemanticValue> UsefulTypeId

%type <listStringSemanticValue> DefinitiveIdentifier
%type <listStringSemanticValue> DefinitiveObjIdComponentList
%type <listStringSemanticValue> BitIdentifierList
%type <listStringSemanticValue> CharSyms
%type <listStringSemanticValue> ParameterList 
%type <listStringSemanticValue> Parameters

%type <typeSemanticValue> Type   
%type <typeSemanticValue> BuiltinType
%type <typeSemanticValue> ReferencedType
%type <typeSemanticValue> NamedType
%type <typeSemanticValue> DefinedType
%type <typeSemanticValue> ConstrainedType
%type <typeSemanticValue> TypeWithConstraint
%type <typeSemanticValue> BitStringType
%type <typeSemanticValue> BooleanType
%type <typeSemanticValue> CharacterStringType 
%type <typeSemanticValue> RestrictedCharacterStringType
%type <typeSemanticValue> UnrestrictedCharacterStringType
%type <typeSemanticValue> ChoiceType AlternativeTypeLists
%type <typeSemanticValue> EmbeddedPDVType
%type <typeSemanticValue> EnumeratedType 
%type <typeSemanticValue> Enumerations
%type <typeSemanticValue> ExternalType
%type <typeSemanticValue> IntegerType
%type <typeSemanticValue> NullType
%type <typeSemanticValue> ObjectClassFieldType
%type <typeSemanticValue> ObjectIdentifierType
%type <typeSemanticValue> OctetStringType 
%type <typeSemanticValue> RealType
%type <typeSemanticValue> SequenceType  
%type <typeSemanticValue> ComponentType
%type <typeSemanticValue> ComponentTypeLists
%type <typeSemanticValue> SequenceOfType
%type <typeSemanticValue> SetType
%type <typeSemanticValue> SetOfType
%type <typeSemanticValue> TaggedType
%type <typeSemanticValue> ParameterizedType
%type <typeSemanticValue> SelectionType
%type <typeSemanticValue> UsefulType
%type <typeSemanticValue> TypeFromObject
%type <typeSemanticValue> ContainedSubtype
%type <typeSemanticValue> ActualParameter
%type <typeSemanticValue> UserDefinedConstraintParameter
%type <typeSemanticValue> Symbol
%type <typeSemanticValue> ParameterizedReference
%type <typeSemanticValue> AnyType

%type <typeListSemanticValue> AlternativeTypeList
%type <typeListSemanticValue> ComponentTypeList
%type <typeListSemanticValue> ActualParameterList 
%type <typeListSemanticValue> ActualParameters
%type <typeListSemanticValue> UserDefinedConstraintParameters
%type <typeListSemanticValue> SymbolList

%type <valueSemanticValue> Value BuiltinValue
%type <valueSemanticValue> BuiltinValue
%type <valueSemanticValue> AssignedIdentifier
%type <valueSemanticValue> DefinedValue 
%type <valueSemanticValue> DefinedValueImport
%type <valueSemanticValue> ObjectIdentifierValue
%type <valueSemanticValue> OctetStringValue
%type <valueSemanticValue> BitStringValue
%type <valueSemanticValue> ExceptionSpec
%type <valueSemanticValue> ExceptionIdentification
%type <valueSemanticValue> LowerEndpoint   
%type <valueSemanticValue> LowerEndValue
%type <valueSemanticValue> UpperEndpoint
%type <valueSemanticValue> UpperEndValue
%type <valueSemanticValue> ReferencedValue
%type <valueSemanticValue> BooleanValue
%type <valueSemanticValue> CharacterStringValue 
%type <valueSemanticValue> RestrictedCharacterStringValue
%type <valueSemanticValue> CharacterStringList  
%type <valueSemanticValue> Quadruple
%type <valueSemanticValue> Tuple
%type <valueSemanticValue> ChoiceValue
%type <valueSemanticValue> NullValue
%type <valueSemanticValue> RealValue   
%type <valueSemanticValue> SpecialRealValue
%type <valueSemanticValue> NumericRealValue
%type <valueSemanticValue> SpecialRealValue
%type <valueSemanticValue> SequenceValue NamedValue
%type <valueSemanticValue> ParameterizedValue

%type <valueListSemanticValue> ComponentValueList
%type <valueListSemanticValue> ValueList

%type <namedNumberSemanticValue> NamedBit
%type <namedNumberSemanticValue> EnumerationItem
%type <namedNumberSemanticValue> NamedNumber

%type <namedNumberListSemanticValue> NamedBitList
%type <namedNumberListSemanticValue> Enumeration
%type <namedNumberListSemanticValue> NamedNumberList

%type <constraintElementSemanticValue> IntersectionElements
%type <constraintElementSemanticValue> Elements
%type <constraintElementSemanticValue> Exclusions
%type <constraintElementSemanticValue> SubtypeElements
%type <constraintElementSemanticValue> ObjectSetElements
%type <constraintElementSemanticValue> ValueRange
%type <constraintElementSemanticValue> PermittedAlphabet
%type <constraintElementSemanticValue> InnerTypeConstraints
%type <constraintElementSemanticValue> MultipleTypeConstraints
%type <constraintElementSemanticValue> SizeConstraint
%type <constraintElementSemanticValue> UserDefinedConstraintParameterList
%type <constraintElementSemanticValue> NamedConstraint

%type <constraintElementListSemanticValue> ValueSet
%type <constraintElementListSemanticValue> ElementSetSpec   
%type <constraintElementListSemanticValue> Unions
%type <constraintElementListSemanticValue> Intersections
%type <constraintElementListSemanticValue> TypeConstraints


%type <constraintSemanticValue> Constraint
%type <constraintSemanticValue> ConstraintSpec
%type <constraintSemanticValue> ElementSetSpecs 
%type <constraintSemanticValue> GeneralConstraint
%type <constraintSemanticValue> UserDefinedConstraint
%type <constraintSemanticValue> TableConstraint
%type <constraintSemanticValue> SimpleTableConstraint
%type <constraintSemanticValue> ComponentRelationConstraint
%type <constraintSemanticValue> ObjectSet

/* NOTE:                                                                      */
/* Not used anymore.                                                          */

/*
%type <stringSemanticValue> FieldSetting      
%type <listStringSemanticValue> FieldSettings
%type <stringSemanticValue> Setting
*/

%type <longSemanticValue> Object
%type <longSemanticValue> ObjectDefn

%type <listStringSemanticValue> WithSyntaxSpec
%type <listStringSemanticValue> SyntaxList
%type <listStringSemanticValue> TokenOrGroupSpecs

/* NOTE:                                                                      */
/* Not used anymore.                                                          */

/*
%type <listStringSemanticValue> DefinedSyntax
%type <listStringSemanticValue> DefinedSyntaxTokens
%type <stringSemanticValue> DefinedSyntaxToken
*/

%type <stringSemanticValue> ObjectDefnElements
%type <stringSemanticValue> ObjectDefnElement


%type <stringSemanticValue> TokenOrGroupSpec
%type <stringSemanticValue> RequiredToken
%type <stringSemanticValue> OptionalGroup
%type <stringSemanticValue> Literal

%type <valueSemanticValue> AnyValue



%type <tagSemanticValue> Tag


%union {
    long                            longSemanticValue;
    std::string*                    stringSemanticValue;
    std::list<std::string*>*        listStringSemanticValue;
    Type*                           typeSemanticValue;
    TypeList*                       typeListSemanticValue;
    Value*                          valueSemanticValue;
    ValueList*                      valueListSemanticValue;
    NamedNumber*                    namedNumberSemanticValue;
    NamedNumberList*                namedNumberListSemanticValue;
    Constraint*                     constraintSemanticValue;
    ConstraintElementList*          constraintElementListSemanticValue;
    ConstraintElement*              constraintElementSemanticValue;
    struct {
        Tag::TagClass   tagClass;
        long            tagNumber;
    }                               tagSemanticValue;
}


%%


/*----------------------------------------------------------------------------*/

Module
    :   TK_MODULE_REFERENCE DefinitiveIdentifier TK_DEFINITIONS TagDefault TK_ASSIGNMENT TK_BEGIN
        {
            moduleG = new Module(*$1, $2, (Tag::TagMode)$4);
            moduleG->SetAsn1SrcFileName(asn1SrcFileNameG);
            referenceTokenContextG = TK_TYPE_REFERENCE;

            if (commandInterpreterG != NULL)
            {
                commandInterpreterG->ProcessModule(*moduleG);
            }
        }
        ModuleBody TK_END
        {
            referenceTokenContextG = TK_MODULE_REFERENCE;
            identifierTokenContextG = TK_IDENTIFIER;
            braceTokenContextG = '{';
            nullTokenContextG = TK_NULL;
            TypeList* currentImportListG = NULL;
        }
    ;

DefinitiveIdentifier
    :   '{' DefinitiveObjIdComponentList '}'
        {
            $$ = $2;
        }
    |   TK_OBJECT_IDENTIFIER_VALUE
        {
            $$ = new list<string*>();
            $$->push_back($1);
        }
    |   /* Empty. */
        {
            $$ = new list<string*>();
        }
    ;

DefinitiveObjIdComponentList
    :   DefinitiveObjIdComponent
        {
            $$ = new list<string*>();
            $$->push_back($1);
        }
    |   DefinitiveObjIdComponent DefinitiveObjIdComponentList
        {
            $2->push_front($1);
            $$ = $2;
        }
    ;

DefinitiveObjIdComponent
    :   TK_IDENTIFIER  
    |   TK_NUMBER
        {
            $$ = new string(LongToString($1));
        }
    |   DefinitiveNameAndNumberForm
    ;

DefinitiveNameAndNumberForm
    :   TK_IDENTIFIER '(' TK_NUMBER ')'
        {
            $$ = new string();

            $$->append(*$1);
            $$->append("(");
            $$->append(LongToString($3));
            $$->append(")");
        }
    ;

TagDefault
    :   TK_EXPLICIT TK_TAGS
        {
            $$ = Tag::MODE_EXPLICIT;
        }
    |   TK_IMPLICIT TK_TAGS
        {
            $$ = Tag::MODE_IMPLICIT;
        }
    |   TK_AUTOMATIC TK_TAGS
        {
            $$ = Tag::MODE_AUTOMATIC;
        }
    |   /* Empty. */
        {
            $$ = Tag::MODE_EXPLICIT;
        }
    ;

ModuleBody
    :   Exports Imports AssignmentList
    |   /* Empty. */
    ;

Exports
    :   TK_EXPORTS SymbolsExported ';'
    |   /* Empty. */
    ;

SymbolsExported
    :   SymbolList
        {
            moduleG->SetExportedSymbolList($1);
        }
    |   /* Empty. */
        {
            moduleG->SetExportAll();
        }
    ;

Imports
    :   TK_IMPORTS SymbolsImported ';' 
    |   /* Empty. */
    ;

SymbolsImported
    :   SymbolsFromModuleList
    |   /* Empty. */
    ;

SymbolsFromModuleList
    :   SymbolsFromModule
    |   SymbolsFromModuleList SymbolsFromModule
    ;

SymbolsFromModule
    :   SymbolList TK_FROM
        {
            currentImportListG = $1;
            referenceTokenContextG = TK_MODULE_REFERENCE;
        }
        GlobalModuleReference
        {
            moduleG->AddImportedModule(new ImportedModule(*$4, $1));
            currentImportListG = NULL;
        }
  ;

GlobalModuleReference
    :   TK_MODULE_REFERENCE
        {
            referenceTokenContextG = TK_TYPE_REFERENCE;
            braceTokenContextG = TK_OID_BRACE;
        }
        AssignedIdentifier
        {
            braceTokenContextG = '{';
        }
    ;

AssignedIdentifier
    :   DefinedValueImport
    |   ObjectIdentifierValue
    |   /* Empty. */
        {
            $$ = NULL;
        }
    ;

DefinedValueImport
    :   ExternalValueReference
        {
            $$ = new DefinedValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_IMPORT_IDENTIFIER
        {
            $$ = new DefinedValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

SymbolList
    :   Symbol
        {
            $$ = new TypeList();
            $$->push_back($1);
        }
    |   Symbol ',' SymbolList
        {
            $3->push_back($1);
            $$ = $3;
        }
    ;

Symbol
    :   Reference
        {
            $$ = new ImportedType(*$1, false);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   ParameterizedReference  /* Only required for X.683. */
    ;

/*----------------------------------------------------------------------------*/

AssignmentList: Assignment 
    |   AssignmentList Assignment
    ;

Assignment
    :   TypeAssignment
    |   ValueAssignment
    |   ValueSetTypeAssignment 
    |   ObjectClassAssignment
    |   ObjectAssignment
    |   ObjectSetAssignment
    |   ParameterizedAssignment
    ;

ValueSetTypeAssignment
    :   TK_TYPE_REFERENCE Type
        {
            identifierTokenContextG = $2->GetIdentifierTokenContext();
            braceTokenContextG = $2->GetBraceTokenContext();
        }
        TK_ASSIGNMENT ValueSet
        {
            identifierTokenContextG = TK_IDENTIFIER;
            braceTokenContextG = '{';
            TypeDef* typeDef = new TypeDef(*$1, $2);
            typeDef->SetConstraintElementList($5);
            moduleG->AddTypeDef(typeDef);
        }
    ;

TypeAssignment
    :   TK_TYPE_REFERENCE TK_ASSIGNMENT Type
        {
            TypeDef* typeDef = new TypeDef(*$1, $3);
            moduleG->AddTypeDef(typeDef);
        }
    |   UsefulTypeId TK_ASSIGNMENT Type
        {
            TypeDef* typeDef = new TypeDef(*$1, $3);
            moduleG->AddTypeDef(typeDef);
        }
    ;

/*----------------------------------------------------------------------------*/

/* NOTE:                                                                      */
/* Not part of ASN.1 specifications. Added for simple useful types processing */
/* by next stages of the compiler.                                            */

UsefulTypeId
    :   TK_BMP_STRING
        {
            $$ = new string("BMPString");
        }
    |   TK_GENERAL_STRING
        {
            $$ = new string("GeneralString");
        }
    |   TK_GRAPHIC_STRING
        {
            $$ = new string("GraphicString");
        }
    |   TK_IA5_STRING
        {
            $$ = new string("IA5String");
        }
    |   TK_ISO646_STRING
        {
            $$ = new string("ISO646String");
        }
    |   TK_NUMERIC_STRING
        {
            $$ = new string("NumericString");
        }
    |   TK_PRINTABLE_STRING
        {
            $$ = new string("PrintableString");
        }
    |   TK_TELETEX_STRING
        {
            $$ = new string("TeletexString");
        }
    |   TK_T61_STRING
        {
            $$ = new string("T61String");
        }
    |   TK_UNIVERSAL_STRING
        {
            $$ = new string("UniversalString");
        }
    |   TK_VIDEOTEX_STRING
        {
            $$ = new string("VideotexString");
        }
    |   TK_VISIBLE_STRING
        {
            $$ = new string("VisibleString");
        }
    |   TK_GENERALIZED_TIME
        {
            $$ = new string("GeneralizedTime");
        }
    |   TK_UTC_TIME
        {
            $$ = new string("UTCTime");
        }
    |   TK_OBJECT_DESCRIPTOR
        {
            $$ = new string("ObjectDescriptor");
        }
    |   TK_EXTERNAL
        {
            $$ = new string("EXTERNAL");
        }
    ;
       
/*----------------------------------------------------------------------------*/

Type
    :   ConstrainedType
    |   ReferencedType
    |   BuiltinType
    ;

BuiltinType
    :   BitStringType
    |   BooleanType 
    |   CharacterStringType 
    |   ChoiceType 
    |   EmbeddedPDVType 
    |   EnumeratedType 
    |   ExternalType 
    |   InstanceOfType
        { }
    |   IntegerType 
    |   NullType 
    |   ObjectClassFieldType
    |   ObjectIdentifierType 
    |   OctetStringType 
    |   RealType 
    |   SequenceType 
    |   SequenceOfType 
    |   SetType 
    |   SetOfType 
    |   TaggedType
    |   AnyType
    ;

ReferencedType
    :   DefinedType
    |   UsefulType
    |   SelectionType
    |   TypeFromObject

/* NOTE:                                                                      */
/* Synonym of identical to TypeFromObject.                                    */

/*  |   ValueSetFromObjects                                                   */
    ;


DefinedType
    :   ExternalTypeReference
        {
            $$ = new DefinedType(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_TYPE_REFERENCE 
        {
            $$ = new DefinedType(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   ParameterizedType

/* NOTE:                                                                      */
/* Synonym of ParametrizedType.                                               */

/*  |   ParameterizedValueSetType                                             */
    ;

ExternalTypeReference
    :   TK_MODULE_REFERENCE '.' TK_TYPE_REFERENCE
        {
            (*$1).append(".");
            (*$1).append(*$3);
        }
    ;

BitStringType
    :   TK_BIT TK_STRING 
        {
            $$ = new BitStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_BIT TK_STRING '{' NamedBitList '}'
        {
            $$ = new BitStringType($4);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }

/* TODO:                                                                      */
/* Review. Added because of token for OID value (if named list contains just  */
/* one element).                                                              */

    |   TK_BIT TK_STRING TK_OBJECT_IDENTIFIER_VALUE
        {
            $$ = new BitStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }


    ;

NamedBitList
    :   NamedBit 
        {
            $$ = new NamedNumberList();
            $$->push_back($1);
        }
    |   NamedBitList ',' NamedBit
        {
            $1->push_front($3);
        }
    ;

NamedBit
    :   TK_IDENTIFIER '(' TK_NUMBER ')' 
        {
            $$ = new NamedNumber(*$1, $3);
        }
    |   TK_IDENTIFIER '(' DefinedValue ')'
        {
            $$ = new NamedNumber(*$1, (DefinedValue*)$3);
        }
    ;

BooleanType
    :   TK_BOOLEAN
        {
            $$ = new BooleanType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

CharacterStringType
    :   RestrictedCharacterStringType
    |   UnrestrictedCharacterStringType
    ;

RestrictedCharacterStringType
    :   TK_BMP_STRING
        {
            $$ = new BMPStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_GENERAL_STRING
        {
            $$ = new GeneralStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_GRAPHIC_STRING
        {
            $$ = new GraphicStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_IA5_STRING
        {
            $$ = new IA5StringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_ISO646_STRING
        {
            $$ = new ISO646StringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_NUMERIC_STRING
        {
            $$ = new NumericStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_PRINTABLE_STRING
        {
            $$ = new PrintableStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_TELETEX_STRING
        {
            $$ = new TeletexStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_T61_STRING
        {
            $$ = new T61StringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_UNIVERSAL_STRING
        {
            $$ = new UniversalStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_VIDEOTEX_STRING
        {
            $$ = new VideotexStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_VISIBLE_STRING
        {
            $$ = new VisibleStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

UnrestrictedCharacterStringType
    :   TK_CHARACTER TK_STRING
        {
            $$ = new UnrestrictedCharacterStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

ChoiceType
    :   TK_CHOICE '{' AlternativeTypeLists '}'
        {
            $$ = $3;
        }
    ;

AlternativeTypeLists
    :   AlternativeTypeList
        {
            $$ = new ChoiceType($1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   AlternativeTypeList ',' ExtensionAndException
        {
            $$ = new ChoiceType($1, true);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   AlternativeTypeList ',' ExtensionAndException  ','  AlternativeTypeList
        {
            $$ = new ChoiceType($1, true, $5);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

AlternativeTypeList
    :   NamedType   
        {
            $$ = new TypeList();
            $$->push_back($1);
        }
    |   AlternativeTypeList ',' NamedType
        {
            $1->push_back($3);
        }
    ;

ExtensionAndException
    :   '.' '.' '.' ExceptionSpec
    ;

NamedType
    :   TK_IDENTIFIER Type
        {
            $2->SetName(*$1);
            $$ = $2;
        }
    |   Type    
        {

/* TODO:                                                                      */
/* Print a warning "unnamed field".                                           */

            $1->SetName(GetUnnamedFieldName(unnamedFieldCountG++));
        }

/* NOTE:                                                                      */
/* A rule in Type production take care of the following alternative.          */
/* the futher stages of the compiler.                                         */

/*  |   SelectionType                                                         */
    ;

EmbeddedPDVType
    :   TK_EMBEDDED TK_PDV
        {
            $$ = new EmbeddedPDVType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

EnumeratedType
    :   TK_ENUMERATED '{' Enumerations '}'
        {
            $$ = $3;
        }
    ;

Enumerations
    :   Enumeration
        {
            $$ = new EnumeratedType($1, false, new NamedNumberList());
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   Enumeration  ',' '.' '.' '.'
        {
            $$ = new EnumeratedType($1, true, new NamedNumberList());
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   Enumeration  ',' '.' '.' '.' ',' Enumeration
        {
            $$ = new EnumeratedType($1, true, $7);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

Enumeration
    :   EnumerationItem
        {
            $$ = new NamedNumberList();
            $$->push_back($1);
        }
    |   Enumeration ',' EnumerationItem
        {
            $1->push_back($3);
            $$ = $1;
        }
    ;

EnumerationItem
    :   TK_IDENTIFIER
        {
            $$ = new NamedNumber(*$1);
            $$->SetAutoNumber();
        }
    |   NamedNumber
    ;

ExternalType
    :   TK_EXTERNAL
        {
            $$ = new ExternalType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

InstanceOfType
    :   TK_INSTANCE TK_OF DefinedObjectClass
    ;

IntegerType
    :   TK_INTEGER
        {
            $$ = new IntegerType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_INTEGER '{' NamedNumberList '}'
        {
            $$ = new IntegerType($3);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }

/* TODO:                                                                      */
/* Review. Added because of token for OID value (if named list contains just  */
/* one element).                                                              */

    |   TK_INTEGER TK_OBJECT_IDENTIFIER_VALUE
        {
            $$ = new IntegerType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

NullType
    :   TK_NULL
        {
            $$ = new NullType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

ObjectClassFieldType
    :   DefinedObjectClass '.' FieldName
        {
            $$ = new ObjectClassFieldType(*$1, *$3);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
  ;

ObjectIdentifierType
    :   TK_OBJECT TK_IDENTIFIER
        {
            $$ = new ObjectIdentifierType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

OctetStringType
    :   TK_OCTET TK_STRING
        {
            $$ = new OctetStringType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

RealType
    :   TK_REAL
        {
            $$ = new RealType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

SequenceType
    :   TK_SEQUENCE '{' ComponentTypeLists '}'
        {
            $$ = $3;
        }
    |   TK_SEQUENCE '{'  '}'
        {
            $$ = new SequenceType(new TypeList(), false, new TypeList());
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_SEQUENCE '{' ExtensionAndException '}'
        {
            $$ = new SequenceType(new TypeList(), true, new TypeList());
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
  ;

ComponentTypeLists
    :   ComponentTypeList
        {
            $$ = new SequenceType($1, false, new TypeList());
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   ComponentTypeList ',' ExtensionAndException
        {
            $$ = new SequenceType($1, true, new TypeList());
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   ComponentTypeList ',' ExtensionAndException ',' ComponentTypeList
        {
            $$ = new SequenceType($1, true, $5);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   ExtensionAndException ',' ComponentTypeList
        {
            $$ = new SequenceType(new TypeList(), true, $3);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

ComponentTypeList
    :   ComponentType
        {
            $$ = new TypeList();
            $$->push_back($1);
        }
    |   ComponentTypeList ',' ComponentType
        {
            $1->push_back($3);
        }
    ;

ComponentType
    :   NamedType
    |   NamedType TK_OPTIONAL
        {
            $1->SetOptional();
        }
    |   NamedType TK_DEFAULT
        {
            identifierTokenContextG = $1->GetIdentifierTokenContext();
        }
    Value   
        {
            identifierTokenContextG = TK_IDENTIFIER;
            $1->SetDefaultValue($4);
        }
    |   TK_COMPONENTS TK_OF Type
        {
            $$ = $3;
            $$->SetComponentsOf();
        }
    ;

SequenceOfType
    :   TK_SEQUENCE TK_OF Type
        {
            $$ = new SequenceOfType($3, NULL);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

SetType
    :   TK_SET '{' ComponentTypeLists '}' 
        {
            $$ = new SetType((SequenceType*)$3);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_SET '{'  '}'
        {
            $$ = new SetType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
	|	TK_SET '{' ExtensionAndException '}'
		{
			$$ = new SetType(new TypeList(), true, new TypeList());
			$$->SetLineNumber(lineNumberG);
			$$->SetModule(moduleG);
		}
    ;

SetOfType
    :   TK_SET TK_OF Type
        {
            $$ = new SetOfType($3, NULL);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

TaggedType
    :   Tag Type
        {
            Tag* tag = new Tag($1.tagClass, $1.tagNumber, moduleG->GetDefaultTagMode());
            $2->AddTag(tag);
            $$ = $2;
        }
    |   Tag TK_IMPLICIT Type  
        {
            Tag* tag = new Tag($1.tagClass, $1.tagNumber, Tag::MODE_IMPLICIT);
            $3->AddTag(tag);
            $$ = $3;
        }
    |   Tag TK_EXPLICIT Type
        {
            Tag* tag = new Tag($1.tagClass, $1.tagNumber, Tag::MODE_EXPLICIT);
            $3->AddTag(tag);
            $$ = $3;
        }
    ;

Tag
    :   '[' Class ClassNumber ']'
        {
            $$.tagClass  = (Tag::TagClass)$2;
            $$.tagNumber = $3;
        }
    ;

AnyType
    :   TK_ANY
        {
            $$ = new AnyType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_ANY TK_DEFINED TK_BY TK_IDENTIFIER
        {
            $$ = new AnyDefinedByType(*$4);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

ClassNumber
    :   TK_NUMBER 
    |   DefinedValue
        {

/* TODO: 
/* Review. Temporary option is to not support. Can be complex if linking      */
/* required. Must add an error.                                               */
            
            $$ = 0;
        }
    ;

Class
    :   TK_UNIVERSAL
        {
            $$ = Tag::CLASS_UNIVERSAL;
        }
    |   TK_APPLICATION
        {
            $$ = Tag::CLASS_APPLICATION;
        }
    |   TK_PRIVATE
        {
            $$ = Tag::CLASS_PRIVATE;
        }
    | /* Empty. */
        {
            $$ = Tag::CLASS_CONTEXT_SPECIFIC;
        }
    ;

SelectionType
    :   TK_IDENTIFIER '<' Type
        {
            $$ = new SelectionType(*$1, $3);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

UsefulType
    :   TK_GENERALIZED_TIME
        {
            $$ = new GeneralizedTimeType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_UTC_TIME
        {
            $$ = new UTCTimeType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_OBJECT_DESCRIPTOR
        {
            $$ = new ObjectDescriptorType();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

TypeFromObject
    :   ReferencedObjects '.' FieldName
        { }
  ;

/* NOTE:                                                                      */
/* Not used. See ValueSetFromObjects rule.                                    */

/*

ValueSetFromObjects                     
  :   ReferencedObjects '.' FieldName    
  ;                                      

*/

ReferencedObjects
    :   DefinedObject
    |   ParameterizedObject
    |   DefinedObjectSet
        { }
    |   ParameterizedObjectSet
        { }
    ;

ParameterizedObject
    :   DefinedObject ActualParameterList
    ;


/*----------------------------------------------------------------------------*/

ConstrainedType
    :   Type Constraint
        {
            $1->AddConstraint($2);
        }
    |   TypeWithConstraint
    ;

TypeWithConstraint
    :   TK_SET Constraint TK_OF Type
        {
            $$ = new SetOfType($4, $2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_SET SizeConstraint TK_OF Type
        {
            $$ = new SetOfType($4, new Constraint($2));
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_SEQUENCE Constraint TK_OF Type
        {
            $$ = new SequenceOfType($4, $2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_SEQUENCE SizeConstraint TK_OF Type
        {
            $$ = new SequenceOfType($4, new Constraint($2));
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

Constraint
    :   '(' ConstraintSpec ExceptionSpec ')'
        {
            $$ = $2;
        }
    ;

ConstraintSpec
    :   ElementSetSpecs
    |   GeneralConstraint
    ;

ExceptionSpec
    :   '!' ExceptionIdentification 
        {
            $$ = $2;
        }
    |   /* Empty. */
        {
            $$ = NULL;
        }
    ;

ExceptionIdentification
    :   SignedNumber
        {
            $$ = new IntegerValue($1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   DefinedValue
    |   Type ':' Value
        {

/* TODO:                                                                      */
/* Add warning. Typed exception not supported.                                */

            $$ = $3;
        }
    ;


ElementSetSpecs
    :   ElementSetSpec
        {
            $$ = new Constraint($1, false, NULL);
        }
    |   ElementSetSpec  ',' '.' '.' '.'
        {
            $$ = new Constraint($1, true, NULL);
        }
    |   '.' '.' '.' ',' ElementSetSpec
        {
            $$ = new Constraint(NULL, true, $5);
        }
    |   ElementSetSpec  ',' '.' '.' '.' ElementSetSpec
        {
            $$ = new Constraint($1, true, $6);
        }

/* TODO:                                                                      */
/* Review. Recently added. Most likely must add a new constructor.            */

    |   '.' '.' '.'
        {
            $$ = NULL;
        }
    ;

ElementSetSpec
    :   Unions
    |   TK_ALL Exclusions
        {
            $$ = new ConstraintElementList();
            $$->push_back(new ConstrainAllConstraintElement($2));
        }
    ;

Unions
    :   Intersections
        {
            $$ = new ConstraintElementList();
            $$->push_back(new ElementListConstraintElement($1));
        }
    |   Unions UnionMark Intersections
        {
            $1->push_back(new ElementListConstraintElement($3));
        }
    ;

Intersections
    :   IntersectionElements 
        {
            $$ = new ConstraintElementList();
            $$->push_back($1);
        }
    |   Intersections IntersectionMark IntersectionElements
        {
            $1->push_back($3);
        }
    ;

IntersectionElements
    :   Elements 
    |   Elements Exclusions
        {
            $1->SetExclusions($2);
        }
    ;

Exclusions
    :   TK_EXCEPT Elements
        {
            $$ = $2;
        }
    ;

UnionMark
    :   '|' 
    |   TK_UNION
    ;

IntersectionMark
    :   '^' 
    |   TK_INTERSECTION
    ;

Elements
    :   SubtypeElements
    |   ObjectSetElements
    |   '(' ElementSetSpec ')'
        {
            $$ = new ElementListConstraintElement($2);
        }
    ;

SubtypeElements
    :   
    
/* TODO:                                                                      */
/* Review. Cause a reduce/reduce conflict with ValueRange. Seems to be        */
/* acceptable till now. Required for constraint like (SIZE(X)).               */
   
        Value
        {
            $$ = new SingleValueConstraintElement($1);
        }

/* TODO:                                                                      */
/* Remove. Experimentation to remove reduce/reduce conflict.                  */

/*
        SignedNumber
        {
            $$ = new SingleValueConstraintElement(new IntegerValue($1));
        }
    |
        DefinedValue
        {
            $$ = new SingleValueConstraintElement($1);
        }

*/

    | 
        ContainedSubtype
        {
            $$ = new SubTypeConstraintElement($1);
        }
    |   ValueRange
		{
			$$ = $1;
		}
    |   PermittedAlphabet
    |   SizeConstraint
		{
			$$ = $1;
		}

/* TODO:                                                                      */
/* Review. Cause a conflict with ContainedSubtype.                            */

/*
    |   TypeConstraint
*/

    |   InnerTypeConstraints
    ;

ValueRange
    :   LowerEndpoint '.' '.' UpperEndpoint
        {
            $$ = new ValueRangeConstraintElement($1, $4);
        }
    ;

LowerEndpoint
    :   LowerEndValue
    |   LowerEndValue '<'
    ;

UpperEndpoint
    :   UpperEndValue
    |   '<' UpperEndValue
        {
            $$ = $2;
        }
    ;

LowerEndValue
    :   Value 
    |   TK_MIN
        {
            $$ = new MinValue();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

UpperEndValue
    :   Value 
    |   TK_MAX
        {
            $$ = new MaxValue();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

PermittedAlphabet
    :   TK_FROM Constraint
        {
            $$ = new FromConstraintElement($2);
        }
    ;

ContainedSubtype
    :   TK_INCLUDES Type
        {
            $$ = $2;
        }

/* TODO:                                                                      */
/* Review. Cause a conflict.                                                  */

/*  
    |   Type
*/

    |   ConstrainedType
    |   BuiltinType
    |   DefinedType
    |   UsefulType
    ;

SizeConstraint
    :   TK_SIZE Constraint
        {
            $$ = new SizeConstraintElement($2);
        }
    ;

InnerTypeConstraints
    :   TK_WITH TK_COMPONENT Constraint
        {
            $$ = new WithComponentConstraintElement(NULL, $3, WithComponentConstraintElement::COMPONENT_DEFAULT);
        }
    |   TK_WITH TK_COMPONENTS MultipleTypeConstraints
        {
            $$ = $3;
        }
    ;

MultipleTypeConstraints
    :   '{' TypeConstraints '}' /* FullSpecification. */
        {
            $$ = new InnerTypeConstraintElement($2, false);
        }
    |   '{'  '.' '.' '.' ',' TypeConstraints '}' /* PartialSpecification. */
        {
            $$ = new InnerTypeConstraintElement($6, true);
        }
    ;

TypeConstraints
    :   NamedConstraint
        {
            $$ = new ConstraintElementList();
            $$->push_back($1);
        }
    |   NamedConstraint ',' TypeConstraints
        {
            $3->push_back($1);
            $$ = $3;
        }
    ;

NamedConstraint
    :   TK_IDENTIFIER PresenceConstraint
        {
            $$ = new WithComponentConstraintElement(*$1, NULL, (int)$2);
        }
    |   TK_IDENTIFIER Constraint PresenceConstraint 
        {
            $$ = new WithComponentConstraintElement(*$1, $2, (int)$3);
        }
    ;

PresenceConstraint
    :   TK_PRESENT
        {
            $$ = WithComponentConstraintElement::COMPONENT_PRESENT;
        }
    |   TK_ABSENT 
        {
            $$ = WithComponentConstraintElement::COMPONENT_ABSENT;
        }
    |   TK_OPTIONAL
        {
            $$ = WithComponentConstraintElement::COMPONENT_OPTIONAL;
        }
    |   /* Empty. */
        {
            $$ = WithComponentConstraintElement::COMPONENT_DEFAULT;
        }
    ;

GeneralConstraint
    :   UserDefinedConstraint
    |   TableConstraint
    ;

UserDefinedConstraint
    :   TK_CONSTRAINED TK_BY '{' UserDefinedConstraintParameterList '}'
        {
            $$ = new Constraint($4);
        }
    ;

UserDefinedConstraintParameterList
    :   /* Empty. */
        {
            $$ = new UserDefinedConstraintElement(NULL);
        }
    |   UserDefinedConstraintParameters
        {
            $$ = new UserDefinedConstraintElement($1);
        }
    ;
 
UserDefinedConstraintParameters
    :   UserDefinedConstraintParameter ',' UserDefinedConstraintParameters
        {
            $3->push_back($1);
            $$ = $3;
        }
    |   UserDefinedConstraintParameter
        {
            $$ = new TypeList();
            $$->push_back($1);
        }
    ;

UserDefinedConstraintParameter
    :   Governor ':' ActualParameter
        {
            $$ = $3;
        }
    |   ActualParameter
    ;

TableConstraint
    :   SimpleTableConstraint
    |   ComponentRelationConstraint
    ;

/* TODO: 
/* Review. Should be defined as [SimpleTableConstraint -> ObjectSet]. Too     */
/* ambiguous and not common use.                                              */

SimpleTableConstraint
    :   '{' DefinedObjectSet '}'
        {
            $$ = NULL;
        }
    ;

ComponentRelationConstraint
    :   '{' DefinedObjectSet '}' '{' AtNotations '}'
        { $$ = NULL; }
    ;

AtNotations
    :   AtNotations ',' AtNotation
    |   AtNotation
    ;

AtNotation
    :   '@' ComponentIdList
    |   '@' '.' ComponentIdList
    ;

ComponentIdList
    :   ComponentIdList '.' TK_IDENTIFIER
    |   TK_IDENTIFIER
    ;

/*----------------------------------------------------------------------------*/

ObjectClassAssignment
    :   TK_OBJECT_CLASS_REFERENCE TK_ASSIGNMENT ObjectClass
        { }
    ;

ObjectAssignment
    :   TK_OBJECT_REFERENCE DefinedObjectClass TK_ASSIGNMENT Object
        { }
    ;

ObjectSetAssignment
    :   TK_OBJECT_SET_REFERENCE DefinedObjectClass TK_ASSIGNMENT ObjectSet
        { }
    ;

ObjectClass
    :   DefinedObjectClass
        { }
    |   ObjectClassDefn 
    |   ParameterizedObjectClass
    ;

DefinedObjectClass
    :   ExternalObjectClassReference
    |   TK_OBJECT_CLASS_REFERENCE
    |   UsefulObjectClassReference
    ;

ExternalObjectClassReference
    :   TK_MODULE_REFERENCE '.' TK_OBJECT_CLASS_REFERENCE
        {
            $$ = $1;
            $1->append(".");
            $1->append(*$3);
        }
    ;

UsefulObjectClassReference
    :   TK_TYPE_IDENTIFIER
        {
            $$ = new string("TYPE-IDENTIFIER");
        }
    |   TK_ABSTRACT_SYNTAX
        {
            $$ = new string("ABSTRACT-SYNTAX");
        }
    ;

ObjectClassDefn
    :   TK_CLASS  '{'  FieldSpecs '}'  WithSyntaxSpec
    ;

FieldSpecs
    :   FieldSpecs ',' FieldSpec
    |   FieldSpec
    ;

FieldSpec
    :   TypeFieldSpec
    |   FixedTypeValueFieldSpec
    |   VariableTypeValueFieldSpec
    |   FixedTypeValueSetFieldSpec
    |   VariableTypeValueSetFieldSpec
    |   ObjectFieldSpec
    |   ObjectSetFieldSpec
    ;

TypeFieldSpec
    :   TK_TYPE_FIELD_REFERENCE TypeOptionalitySpec
        { }
    ;

TypeOptionalitySpec
    :   TK_OPTIONAL
    |   TK_DEFAULT Type
    |   /* Empty. */
    ;

FixedTypeValueFieldSpec
    :   TK_VALUE_FIELD_REFERENCE Type Unique ValueOptionalitySpec
        { }
    ;

Unique
    :   TK_UNIQUE
    |   /* Empty. */
    ;

ValueOptionalitySpec
    :   TK_OPTIONAL
    |   TK_DEFAULT Value
    |   /* Empty. */
    ;

VariableTypeValueFieldSpec
    :   TK_VALUE_FIELD_REFERENCE FieldName ValueOptionalitySpec
        { }
    ;

FixedTypeValueSetFieldSpec
    :   TK_VALUE_SET_FIELD_REFERENCE Type ValueSetOptionalitySpec
        { }
    ;

ValueSetOptionalitySpec
    :   TK_OPTIONAL
    |   TK_DEFAULT ValueSet
    |   /* Empty. */
    ;

VariableTypeValueSetFieldSpec
    :   TK_VALUE_SET_FIELD_REFERENCE FieldName ValueSetOptionalitySpec
        { }
    ;

ObjectFieldSpec
    :   TK_OBJECT_FIELD_REFERENCE DefinedObjectClass ObjectOptionalitySpec
        { }
    ;

ObjectOptionalitySpec
    :   TK_OPTIONAL
    |   TK_DEFAULT Object
    |   /* Empty. */
    ;

ObjectSetFieldSpec
    :   TK_OBJECT_SET_FIELD_REFERENCE DefinedObjectClass ObjectSetOptionalitySpec
        { }
    ;

ObjectSetOptionalitySpec
    :   TK_OPTIONAL
    |   TK_DEFAULT ObjectSet
    |   /* Empty. */
    ;

WithSyntaxSpec
    :   TK_WITH TK_SYNTAX SyntaxList
        {
            $$ = $3;
        }
    |   /* Empty. */
        {
            $$ = new list<string*>();
        }
    ;

SyntaxList
    :   '{' TokenOrGroupSpecs '}'
        {
            $$ = $2;
        }
    |   '{' '}'
        {
            $$ = new list<string*>();
        }
    ;

TokenOrGroupSpecs
    :   TokenOrGroupSpecs TokenOrGroupSpec
        {
            ($1)->push_back($2);
            $$ = $1;
        }
    |   TokenOrGroupSpec
        {
            $$ = new list<string*>();
            ($$)->push_back($1);
        }
    ;

TokenOrGroupSpec
    :   RequiredToken
    |   OptionalGroup
    ;

OptionalGroup
    :   '[' TokenOrGroupSpecs ']'
        {
            $$ = new string();
        }
    ;

RequiredToken
    :   Literal
    |   PrimitiveFieldName
    ;


/* TODO:                                                                      */
/* Review the following. All the tokens should be listed there and processed. */


Literal
    :   TK_TYPE_REFERENCE
        {
            $$ = $1;
        }
    |   TK_IDENTIFIER
        {
            $$ = $1;
        }
    |   TK_BIT
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_BOOLEAN
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_CHARACTER
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_CHOICE
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_EMBEDDED
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_END
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_ENUMERATED
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_EXTERNAL     
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_FALSE
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_INSTANCE
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_NUMBER
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_INTERSECTION
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_MINUS_INFINITY
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_NULL
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_OBJECT
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_OCTET
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_PLUS_INFINITY
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_REAL
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_SEQUENCE
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_SET
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_TRUE
        {
            $$ = new string(); /* Process as an error. */
        }
    |   TK_UNION
        {
            $$ = new string(); /* Process as an error. */
        }
    ;

DefinedObject
    :   ExternalObjectReference
    |   TK_OBJECT_REFERENCE
        { }
    ;

ExternalObjectReference
    :   TK_MODULE_REFERENCE '.' TK_OBJECT_REFERENCE
        { }
    ;

ParameterizedObjectClass
    :   DefinedObjectClass ActualParameterList
        { }
    ;

DefinedObjectSet
    :   ExternalObjectSetReference
        { }
    |   TK_OBJECT_SET_REFERENCE
        { }
    ;

ExternalObjectSetReference
    :   TK_MODULE_REFERENCE '.' TK_OBJECT_SET_REFERENCE
        { }
    ;

ParameterizedObjectSet
    :   DefinedObjectSet ActualParameterList
    ;

FieldName
    :   FieldName '.' PrimitiveFieldName
        {
            $$ = $1;
            $1->append(".");
            $1->append(*$3);
        }
    |   PrimitiveFieldName
    ;

PrimitiveFieldName
    :   TK_TYPE_FIELD_REFERENCE
    |   TK_VALUE_FIELD_REFERENCE
    |   TK_VALUE_SET_FIELD_REFERENCE
    |   TK_OBJECT_FIELD_REFERENCE
    |   TK_OBJECT_SET_FIELD_REFERENCE
    ;

Object
    :   DefinedObject
        { }

    |   ObjectDefn      
        { }
        
/* TODO:                                                                      */
/* Review. Cause a conflict.                                                  */

/*
    |   ObjectFromObject
        { }
*/

    |   ParameterizedObject
        { }
    ;

ObjectDefn                                   
    :   '{' ObjectDefnElements '}'
        {
            $$ = 0;
        }
    ;

ObjectDefnElements
    :   ObjectDefnElements ObjectDefnElement
        {
            $$ = NULL;
        }
    |   ObjectDefnElement
        {
            $$ = NULL;
        }
    ;

ObjectDefnElement
    :   TK_TYPE_REFERENCE
        {
            $$ = NULL;
        }
    |   TK_IDENTIFIER
        {
            $$ = NULL;
        }
    ;
    
    
/* NOTE:                                                                      */
/* Previous rules related to ObjectDefn.                                      */

/*
ObjectDefn
    :   DefaultSyntax  
        {
            $$ = 0;
        }                         
    |   DefinedSyntax                           
        {
            $$ = 0;
        }
    ;                                           
                                              
DefaultSyntax                                  
    :   '{' FieldSettings '}'

*/

/* NOTE:                                                                      */
/* Processed like an empty SequenceValue.                                     */

/*
    |     '{' '}'
*/

/* NOTE:                                                                      */
/* Previous rules related to ObjectDefn (continued).                          */

/*
    ;                                           
                                              
FieldSettings                                
    :   FieldSettings ',' FieldSetting
        { 
            $$ = new list<string*>();
            ($$)->push_back($3);
        }          
    |   FieldSetting                            
        {
            $$ = new list<string*>();
            ($$)->push_back($1);
        }
    ;                                           
                                              
FieldSetting                                 
    :   PrimitiveFieldName Setting  
        {
            $$ = $1;
        }            
    ;                                           
                                              
DefinedSyntax                                
    :   '{' DefinedSyntaxTokens '}'   
        {            
            $$ = $2;
        }
    ;                                           
                                              
DefinedSyntaxTokens                          
    :   DefinedSyntaxTokens DefinedSyntaxToken
        {
            $$ = new list<string*>();
        }
    ;                                           
                                              
DefinedSyntaxToken                                 
    :   Literal                                 
    |   Setting                                 
    ;                                           
                                              
Setting                                      
    :   Type                                    
    |   Value                                   
    |   ValueSet                                
    |   Object    
    |   ObjectSet
    ;  
*/                                           

ObjectSet
    :   '{' ElementSetSpecs '}'
        { }
    ;

ObjectFromObject
    :   ReferencedObjects '.' FieldName
    ;


ObjectSetElements
    :   Object
        { }
    |   DefinedObjectSet
        { }

/* TODO:                                                                      */
/* Review. Cause conflict.                                                    */

/*  
    |   ObjectSetFromObjects
*/

    |   ParameterizedObjectSet
        { }
    ;

ObjectSetFromObjects
    :   ReferencedObjects '.' FieldName
    ;


/*----------------------------------------------------------------------------*/

ParameterizedAssignment
    :   ParameterizedTypeAssignment
    |   ParameterizedValueAssignment
    |   ParameterizedValueSetTypeAssignment
    |   ParameterizedObjectClassAssignment
    |   ParameterizedObjectAssignment
    |   ParameterizedObjectSetAssignment
    ;

ParameterizedTypeAssignment
    :   TK_TYPE_REFERENCE ParameterList
        {
            dummyParametersG = $2;
        }
        TK_ASSIGNMENT Type
        {
            dummyParametersG = NULL;
            TypeDef* typeDef = new TypeDef(*$1, $5);
            typeDef->SetParameterList($2);
            moduleG->AddTypeDef(typeDef);
        }
    ;

ParameterizedValueAssignment
    :   TK_IDENTIFIER ParameterList Type TK_ASSIGNMENT Value
        { }
    ;

ParameterizedValueSetTypeAssignment
  : TK_TYPE_REFERENCE ParameterList Type TK_ASSIGNMENT ValueSet
    { }
  ;

ParameterizedObjectClassAssignment
    :   TK_OBJECT_CLASS_REFERENCE ParameterList TK_ASSIGNMENT ObjectClass
        { }
    ;

ParameterizedObjectAssignment
    :   TK_OBJECT_REFERENCE ParameterList DefinedObjectClass TK_ASSIGNMENT Object
        { }
    ;

ParameterizedObjectSetAssignment
    :   TK_OBJECT_SET_REFERENCE ParameterList DefinedObjectClass TK_ASSIGNMENT ObjectSet
        { }
    ;

ParameterList
    :   '{' Parameters '}'
        {
            $$ = $2;
        }
    ;

Parameters
    :   Parameters ',' Parameter
        {
            $$ = $1;
            $$->push_back($3);
        }
    |   Parameter
        {
            $$ = new list<string*>();
            $$->push_back($1);
        }
    ;

Parameter
    :   Governor ':' Reference
        {
            $$ = $3;
        }
    |   Reference
    ;

Governor
    :   Type
        { }
    |   DefinedObjectClass
        { }
    ;

ParameterizedType
    :   SimpleDefinedType ActualParameterList
        {
            $$ = new ParameterizedType(*$1, $2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

SimpleDefinedType
    :   ExternalTypeReference
    |   TK_TYPE_REFERENCE
    ;


ActualParameterList
    :   '{' ActualParameters '}'
        {
            $$ = $2;
        }
    ;

ActualParameters
    :   ActualParameters ',' ActualParameter
        {
            $1->push_back($3);
            $$ = $1;
        }
    |   ActualParameter
        {
            $$ = new TypeList();
            $$->push_back($1);
        }
    ;

ActualParameter
    :   Type
    |   Value
        { }
    |   ValueSet
        { }
    |   DefinedObjectClass
        { }

/* TODO:                                                                      */
/* Review. Cause conflict.                                                    */

/*  
    |   Object
        { }
    |   ObjectSet
*/

    ;


/*----------------------------------------------------------------------------*/

ValueAssignment 
    :   TK_IDENTIFIER Type
        {
            identifierTokenContextG = $2->GetIdentifierTokenContext();
            braceTokenContextG = $2->GetBraceTokenContext();
            nullTokenContextG = TK_NULL_VALUE;
        }
        TK_ASSIGNMENT Value
        {
            ValueDef* valueDef = new ValueDef(*$1, $2, $5);
            moduleG->AddValueDef(valueDef);
            identifierTokenContextG = TK_IDENTIFIER;
            braceTokenContextG = '{';
            nullTokenContextG = TK_NULL;
        }
    ;


Value
    :   BuiltinValue
    |   ReferencedValue
    ;


BuiltinValue
    :   BitStringValue 
    |   BooleanValue 
    |   CharacterStringValue 
    |   ChoiceValue 

/* NOTE:                                                                      */
/* EnumeratedValue is processed during linking (from DefinedValue). Otherwise */ 
/* generates too many conflicts with DefinedValue.                            */

/* 
    |   EnumeratedValue
*/

/* NOTE:                                                                      */
/* EmbeddedPDVValue is synonym to SequenceValue.                              */
/* ExternalValue is synonym to SequenceValue.                                 */
/* InstanceOfValue is synonym to SequenceValue.                               */

/*
    |   EmbeddedPDVValue
    |   ExternalValue   
    |   InstanceOfValue 
*/

    |   SignedNumber
        {
            $$ = new IntegerValue($1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   NullValue 

/* TODO:                                                                      */
/* Review. Cause conflict.                                                    */

/*  
    |   ObjectClassFieldValue
*/

    |   ObjectIdentifierValue
    |   OctetStringValue
    |   RealValue 
    |   SequenceValue 

/* NOTE:                                                                      */
/* SequenceOfValue is synonym to SequenceValue.                               */
/* SetValue is synonym to SequenceValue.                                      */
/* SetOfValue is synonym to SequenceValue.                                    */
/* TaggedValue is synonym to SequenceValue.                                   */

/*  
    |   SequenceOfValue
    |   SetValue      
    |   SetOfValue    
    |   TaggedValue   
*/

    |   AnyValue
    ;

DefinedValue
    :   ExternalValueReference
        {
            $$ = new DefinedValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_IDENTIFIER
        {
            $$ = new DefinedValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   ParameterizedValue
    ;

ExternalValueReference
    :   TK_MODULE_REFERENCE '.' TK_IDENTIFIER
        {
            $1->append(".");
            $1->append(*$3);
        }
    ;

ObjectIdentifierValue  
    :   TK_OBJECT_IDENTIFIER_VALUE
        {
            $$ = new ObjectIdentifierValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }

OctetStringValue
    :   TK_OS_BSTRING
        {
            $$ = new OctetStringValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_OS_HSTRING
        {
            $$ = new OctetStringValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

BitStringValue
    :   TK_BS_BSTRING
        {
            $$ = new BitStringValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_BS_HSTRING
        {
            $$ = new BitStringValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_BIT_STRING_BRACE BitIdentifierList '}' 
        {
            $$ = new BitStringValue($2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_BIT_STRING_BRACE  '}'
        {
            $$ = new BitStringValue();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

BitIdentifierList
    :   TK_BIT_IDENTIFIER
        {
            $$ = new list<string*>();
        }
    |   BitIdentifierList ',' TK_BIT_IDENTIFIER
        {
            $$ = $1;
        }
    ;

BooleanValue
    :   TK_TRUE
        {
            $$ = new BooleanValue(true);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_FALSE
        {
            $$ = new BooleanValue(false);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

CharacterStringValue
    :   RestrictedCharacterStringValue

/* TODO:                                                                      */
/* Review. Cause a conflict.                                                  */

/*
    | UnrestrictedCharacterStringValue 
*/
    ;

RestrictedCharacterStringValue
    :   TK_CSTRING
        {
            $$ = new CharacterStringValue(*$1);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   CharacterStringList
    |   Quadruple
    |   Tuple
    ;

CharacterStringList
    :   TK_STRING_BRACE CharSyms '}'
        {
            $$ = new CharacterStringValue($2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

CharSyms
    :   CharsDefn
        {
            $$ = new list<string*>();
            $$->push_back($1);
        }
    |   CharSyms ',' CharsDefn
        {
            $1->push_back($3);
        }
    ;

CharsDefn
    :   TK_CSTRING 
    |   DefinedValue
        {

/* TODO:                                                                      */
/* Review. Add warning: defined value in string is not supported.             */

        }
    ;

Quadruple
    :   TK_STRING_BRACE  TK_NUMBER  ','  TK_NUMBER  ','  TK_NUMBER ','  TK_NUMBER '}'
        {

/* TODO:                                                                      */
/* Review. Not supported.                                                     */

            $$ = NULL;
        }
    ;

Tuple
    :   TK_STRING_BRACE TK_NUMBER ',' TK_NUMBER '}'
        {

/* TODO:                                                                      */
/* Review. Not supported.                                                     */

            $$ = NULL;
        }
    ;
        
ChoiceValue
    :   TK_IDENTIFIER ':' Value
        {
            $$ = new ChoiceValue(*$1, $3);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

NullValue
    :   TK_NULL_VALUE
        {
            $$ = new NullValue();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

RealValue
    :   NumericRealValue 
    |   SpecialRealValue
    ;

NumericRealValue
    :   '0'
        {
            $$ = new RealValue(0);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }

/* TODO:                                                                      */
/* Review. Cause a conflict.                                                  */

/*  
    |   SequenceValue                           
*/
    ;

SpecialRealValue
    :   TK_PLUS_INFINITY
        {
            $$ = new RealValue(0);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   TK_MINUS_INFINITY
        {
            $$ = new RealValue(0);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;


SequenceValue
    :   '{' ComponentValueList '}' 
        {
            $$ = new SequenceValue($2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   '{' ValueList '}'
        {
            $$ = new SequenceValue($2);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    |   '{'  '}'                        
        {         
            $$ = new SequenceValue();
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG); 
        } 
    ;

ComponentValueList
    :   NamedValue
        {
            $$ = new ValueList();
            $$->push_back($1);
        }
    |   ComponentValueList ',' NamedValue
        {
            $1->push_back($3);
        }
    ;

NamedValue
    :   TK_IDENTIFIER Value
        {
            $2->SetName(*$1);
            $$ = $2;
        }
    ;

ValueList
    :   Value
        {
            $1->SetName("--AsnCC-Unnamed--");
            $$ = new ValueList();
            $$->push_back($1);
        }
    |   ValueList ',' Value
        {
            $3->SetName("--AsnCC-Unnamed--");
            $1->push_back($3);
        }
    ;


/* NOTE:                                                                      */
/* Not used. SequenceOfValue is a synonym of SequenceValue.                   */

/*
SequenceOfValue           
    :   '{' ValueList '}'    
        {                    
            $$ = NULL;       
        }                    
    |   '{'  '}'             
        {                    
            $$ = NULL;       
        }                    
    ;                        
                           
ValueList                 
    :   Value                
        { }                  
    |   ValueList ',' Value  
        { }                  
    ;                        
*/


/* TODO:                                                                      */
/* Review. Cause a conflict.                                                  */

/*
ObjectClassFieldValue     
    :   OpenTypeFieldVal     
    |   Value                
    ;                        
                           
OpenTypeFieldVal          
    :   Type ':' Value       
    ;                        
*/

ReferencedValue
    :   DefinedValue

/* TODO:                                                                      */
/* Review. Cause a conflict.                                                  */

/*  
    |   ValueFromObject    
*/
    ;

ValueFromObject                      
    :   ReferencedObjects '.' FieldName 
        { }                             
    ;                                   

ParameterizedValue
    :   SimpleDefinedValue ActualParameterList
        { }
    ;

SimpleDefinedValue
    :   ExternalValueReference
    |   TK_IDENTIFIER
    ;


/*----------------------------------------------------------------------------*/

ValueSet
    :   '{' ElementSetSpec '}'
        {
            $$=$2;
        }
    ;


/*----------------------------------------------------------------------------*/

AnyValue                                
    :   Type ':' Value                  
        {                                  
            $$ = new AnyValue($1, $3);       
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);        
        }                                  
;                                      


/*----------------------------------------------------------------------------*/

Reference
    :   TK_TYPE_REFERENCE
    |   TK_IDENTIFIER 
    |   TK_OBJECT_CLASS_REFERENCE
    |   TK_OBJECT_REFERENCE
    |   TK_OBJECT_SET_REFERENCE
    ;

ParameterizedReference
    :   Reference '{' '}'
        {
            $$ = new ImportedType(*$1, true);
            $$->SetLineNumber(lineNumberG);
            $$->SetModule(moduleG);
        }
    ;

NamedNumberList
    :   NamedNumber     
        {
            $$ = new NamedNumberList();
            $$->push_back($1);
        }
    |   NamedNumberList ',' NamedNumber
        {
            $1->push_back($3);
        }
    ;

NamedNumber
    :   TK_IDENTIFIER '(' SignedNumber ')' 
        {
            $$ = new NamedNumber(*$1, $3);
        }
    |   TK_IDENTIFIER '(' DefinedValue ')'
        {
            $$ = new NamedNumber(*$1, (DefinedValue*)$3);
        }
    ;

SignedNumber
    :   TK_NUMBER 
    |   '-' TK_NUMBER
        {
            $$ = -$2;
        }
    ;
