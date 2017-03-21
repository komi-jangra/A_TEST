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
//  ID: $Id: asncc_print_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_print_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  PrintVisitor implementation.
//

void 
PrintVisitor::VisitModuleBegin(Module* module)
{
    REQUIRE(module != NULL);

    os << endl;

    if (module->HasErrors())
    {
        os << "-- WARNING: current module contains errors."; 
        os << endl << endl;
    }
    else
    {
        // Nothing to do.
    }

    os << module->GetName() << " " << endl;  

    if (!(module->GetDefinitiveId()->empty()))
    {
        os << endl;

        os << "{ ";

        list<string*>* definitiveId = module->GetDefinitiveId();

        for (list<string*>::const_iterator iter = definitiveId->begin();
             iter != definitiveId->end();
             iter++)
        {
            os << *(*iter);
            os << " ";
        }

        os << "}";

        os << endl << endl;
    }
    
    os << "DEFINITIONS ";

    if (module->GetDefaultTagMode() == Tag::MODE_IMPLICIT)
    {
        os << "IMPLICIT TAGS";
    }
    else if (module->GetDefaultTagMode() == Tag::MODE_EXPLICIT)
    {
        os << "EXPLICIT TAGS";
    }
    else if (module->GetDefaultTagMode() == Tag::MODE_AUTOMATIC)
    {
        os << "AUTOMATIC TAGS";
    }
    else
    {
        os << "-- COMPILER ERROR: unknown tag default. --";
    }

    os << " ::= ";
    os << endl << endl;
    os << "BEGIN";
    os << endl << endl;

    if (module->ExportAll())
    {
        os << "EXPORTS";
        os << endl;
        os << ";";
        os << endl << endl;
    }
    else if (!(module->GetExportedSymbolList()->empty()))
    {
        os << "EXPORTS";
        os << endl;

        TypeList* exportedSymbolList = 
            module->
                GetExportedSymbolList();

        for (TypeList::iterator iter = exportedSymbolList->begin();
             iter != exportedSymbolList->end();
             iter++)
        {   
            if ((*iter)->GetType() == TYPE_IMPORTED)
            {
                ImportedType* exportedSymbol = 
                    static_cast<ImportedType*> (*iter);

                os << "    ";
                os << exportedSymbol->GetName(); 

                if (++iter != exportedSymbolList->end())
                {
                    --iter;
                    os << ",";
                    os << endl;
                }
                else
                {
                    --iter;
                    os << endl;
                    os << ";";
                    os << endl << endl;
                }
            }
            else
            {
                // TODO: add compiler error. Inconsistent with grammar.
            }
        }
    }
}


void 
PrintVisitor::VisitModuleEnd(Module* module)
{
    REQUIRE(module != NULL);

    os << "END";
    os << endl << endl;   
}


void 
PrintVisitor::VisitImportedModule(ImportedModule* importedModule)
{
    REQUIRE(importedModule != NULL);

    if (IsIterBegin())
    {
        os << "IMPORTS";
        os << endl;
    }

    TypeList* importedSymbolList =
        importedModule->
            GetImportedSymbolList();

    for (TypeList::iterator iter = importedSymbolList->begin();
         iter != importedSymbolList->end();
         iter++)
    {
        if ((*iter)->GetType() == TYPE_IMPORTED)
        {
            ImportedType* importedType = static_cast<ImportedType*> (*iter);

            os << "    ";
            os << importedType->GetName();

            if (++iter != importedSymbolList->end())
            {
                --iter;
                os << ",";
                os << endl;
            }
            else
            {
                --iter;
                os << endl;
            }
        }
    }

    os << "FROM ";
    os << importedModule->GetName();

    // TODO: add Assigned Identifier (e.g. OID).

    os << endl;

    if (IsIterEnd() || GetIterSize() == 1)
    {
        os << ";";
        os << endl << endl;
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
PrintVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{
    defaultValueString          = "";
    constraintListString        = "";
    sequenceOfConstraintString  = "";
    setOfConstraintString       = "";

    os << endl;

    os << "-- ";
    os << typeDef->GetDefinedName();
    os << " information: ";
    os << endl;

    typeDef->IsRecursive() ? 
        (os << "-- [recursive]" << endl) : 
        (os << "-- [not recursive]" << endl); 

    typeDef->IsExported() ?
        (os << "-- [exported]" << endl) :
        (os << "-- [not exported]" << endl);

    typeDef->IsCommon() ?
        (os << "-- [common]" << endl) :
        (os << "-- [not common]" << endl);

    os << "-- [local reference counter = ";
    os << typeDef->GetLocalRefCount() << "]";
    os << endl;

    os << "-- [import reference counter = ";
    os << typeDef->GetImportRefCount();
    os << "]";
    os << endl;

    os << endl;
    os << typeDef->GetDefinedName();
    os << " ::= ";
}


void 
PrintVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    os << endl << endl << endl;
}


void 
PrintVisitor::VisitTypeBegin(Type* type)
{
    if (type->IsNamed())
    {
        os << GetIndent();
        os << type->GetName();
        os << " ";
    }

    if (!(type->GetTagList()->empty()))
    {
        Tag* tag = type->GetTagList()->front();

        tag->Print(os);
    }

    if (type->IsComponentsOf())
    {
        os << GetIndent();
        os << "COMPONENTS OF ";
    }
}


void 
PrintVisitor::VisitTypeEnd(Type* type)
{
    Type* baseType = type->GetBaseType();

    if (!(type->GetConstraintList()->empty()))
    {
        if (baseType->GetType() == TYPE_SET_OF ||
            baseType->GetType() == TYPE_SEQUENCE_OF)
        {
            // Nothing to do.
        }
        else
        {
            os << " ";
            os << constraintListString;
            os << " ";
        }
    }

    if (type->IsNamed() && type->IsOptional())
    {
        os << " OPTIONAL";
    }

    if (type->IsNamed() && type->HasDefaultValue())
    {
        os << " DEFAULT ";
        os << defaultValueString;
    }

    if (GetIterSize() > 1)
    {
        if ((type->IsNamed() || type->IsComponentsOf()) &&
            (IsIterBegin() || IsIterMiddle()))
        {
            os << ",";
            os << endl << endl;
        }

        if ((type->IsNamed() || type->IsComponentsOf()) && IsIterEnd())
        {
            os << endl;
        }
    }
    else
    {
        if (type->IsNamed() || type->IsComponentsOf())
        {
            os << endl;
        }
    }

    if (bPrintTagsG)
    {
        TagList* fullTagList = type->GetFullTagList();

        os << endl << GetIndent() << GetIndent();

        os << "-- FTL: ";

        for (TagList::iterator fIter = fullTagList->begin();
             fIter != fullTagList->end();
             fIter++)
        {
            (*fIter)->PrintDebug(os);
        }


        TagList* adjustedTagList = type->GetAdjustedTagList();

        os << endl << GetIndent() << GetIndent();

        os << "-- ATL: ";

        for (TagList::iterator aIter = adjustedTagList->begin();
             aIter != adjustedTagList->end();
             aIter++)
        {
            (*aIter)->PrintDebug(os);
        }

        os << endl << endl;
    }
}


void
PrintVisitor::VisitTypeDefaultValue(Type* type, Value* value)
{   
    defaultValueString = value->ToString();
}


void
PrintVisitor::VisitTypeConstraintList(ConstraintList* constraintList)
{
    constraintListString = "";

    for (ConstraintList::iterator cIter = constraintList->begin();
         cIter != constraintList->end();
         cIter++)
    {
        constraintListString.append((*cIter)->ToString());

        if (++cIter != constraintList->end())
        {
            constraintListString.append(" ");
            --cIter;
        }
        else
        {
            --cIter;
        }
    }
}


void 
PrintVisitor::VisitBitStringTypeBegin(BitStringType* bitStringType)
{
    os << "BIT STRING";
    
    if (bitStringType->HasNamedNumberList())
    {
        os << endl;
        os << GetIndent();
        os << "{";
        os << endl;

        indentLevel += 1;
    }

}


void 
PrintVisitor::VisitBitStringTypeEnd(BitStringType* bitStringType)
{
    if (bitStringType->HasNamedNumberList())
    {
        indentLevel -= 1;

        os << GetIndent();
        os << "}";
    }
}


void 
PrintVisitor::VisitBooleanType(BooleanType* booleanType)
{
    os << "BOOLEAN";
}


void 
PrintVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    os << "CHOICE";
    os << endl;
    
    os << GetIndent();
    os << "{";
    os << endl;

    indentLevel += 1;
}


void 
PrintVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{
    if (choiceType->IsExtendable())
    {
        if (choiceType->GetTypeList()->size() != 0 ||
            choiceType->GetExtensions()->size() != 0)
        {
            os << endl;
        }

        os << GetIndent();

        if (choiceType->GetTypeList()->size() != 0 ||
            choiceType->GetExtensions()->size() != 0)
        {
            os << ", ";
        }

        os << "..." << endl;
    }

    indentLevel -= 1;

    os << GetIndent();
    os << "}";
}


void 
PrintVisitor::VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
{
    os << "ENUMERATED";
    os << endl;

    os << GetIndent();
    os << "{";
    os << endl;

    indentLevel += 1;
}


void 
PrintVisitor::VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
{
    indentLevel -= 1;

    os << GetIndent();
    os << "}";
}


void 
PrintVisitor::VisitIntegerTypeBegin(IntegerType* integerType)
{
    os << "INTEGER";
    
    if (integerType->HasNamedNumberList())
    {
        os << endl;
        os << GetIndent();
        os << "{";
        os << endl;

        indentLevel += 1;
    }
}


void 
PrintVisitor::VisitIntegerTypeEnd(IntegerType* integerType)
{
    if (integerType->HasNamedNumberList())
    {
        indentLevel -= 1;

        os << GetIndent();
        os << "}";
    }
}


void
PrintVisitor::VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType)
{
    os << "OBJECT IDENTIFIER";
}


void
PrintVisitor::VisitNullType(NullType* nullType)
{
    os << "NULL";
}


void
PrintVisitor::VisitRealType(RealType* realType)
{
    os << "REAL";
}


void 
PrintVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    os << "SEQUENCE";
    os << endl;
    
    os << GetIndent();
    os << "{";
    os << endl;

    indentLevel += 1;
}


void 
PrintVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{
    if (sequenceType->IsExtendable())
    {
        if (sequenceType->GetTypeList()->size() != 0 ||
            sequenceType->GetExtensions()->size() != 0)
        {
            os << endl;
        }

        os << GetIndent();

        if (sequenceType->GetTypeList()->size() != 0 ||
            sequenceType->GetExtensions()->size() != 0)
        {
            os << ", ";
        }

        os << "..." << endl;
    }

    indentLevel -= 1;

    os << GetIndent();
    os << "}";
}


void 
PrintVisitor::VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType)
{
    os << "SEQUENCE ";

    if (sequenceOfType->HasConstraint())
    {
        os << sequenceOfConstraintString;
        os << " ";
    }
   
    os << "OF ";
}


void 
PrintVisitor::VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType)
{
    // Nothing to do.
}


void
PrintVisitor::VisitSequenceOfConstraint(Constraint* constraint)
{
    sequenceOfConstraintString = constraint->ToString();
}


void 
PrintVisitor::VisitSetTypeBegin(SetType* setType)
{
    os << "SET";
    os << endl;
    
    os << GetIndent();
    os << "{";
    os << endl;

    indentLevel += 1;
}


void 
PrintVisitor::VisitSetTypeEnd(SetType* setType)
{
    if (setType->IsExtendable())
    {
        if (setType->GetTypeList()->size() != 0 ||
            setType->GetExtensions()->size() != 0)
        {
            os << endl;
        }

        os << GetIndent();

        if (setType->GetTypeList()->size() != 0 ||
            setType->GetExtensions()->size() != 0)
        {
            os << ", ";
        }

        os << "..." << endl;
    }

    indentLevel -= 1;

    os << GetIndent();
    os << "}";
}


void 
PrintVisitor::VisitSetOfTypeBegin(SetOfType* setOfType)
{
    os << "SET ";

    if (setOfType->HasConstraint())
    {
        os << setOfConstraintString;
        os << " ";
    }
   
    os << "OF ";
}


void 
PrintVisitor::VisitSetOfTypeEnd(SetOfType* setOfType)
{
    // Nothing to do.
}


void
PrintVisitor::VisitSetOfConstraint(Constraint* constraint)
{
    setOfConstraintString = constraint->ToString();
}


void 
PrintVisitor::VisitOctetStringType(OctetStringType* octetStringType)
{
    os << "OCTET STRING";
}


void
PrintVisitor::VisitDefinedType(DefinedType* definedType)
{
    os << definedType->GetName();

    if (definedType->IsLinked())
    {
        os << " -- [linked] --";
    }
    else
    {
        os << " -- [not linked] --";
    }
}


void
PrintVisitor::VisitAnyType(AnyType* anyType)
{
    os << "ANY";
}


void
PrintVisitor::VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType)
{
    os << "ANY";
    os << " DEFINED BY ";
    os << anyDefinedByType->GetName();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void
PrintVisitor::VisitValueDefBegin(ValueDef* valueDef)
{
    os << endl;

    os << "-- ";
    os << valueDef->GetDefinedName();
    os << " information: ";
    os << endl;

    valueDef->IsExported() ?
        (os << "-- [exported]" << endl) :
        (os << "-- [not exported]" << endl);

    os << "-- [local reference counter = ";
    os << valueDef->GetLocalRefCount();
    os << "]";
    os << endl;

    os << "-- [import reference counter = ";
    os << valueDef->GetImportRefCount();
    os << "]";
    os << endl;

    os << endl;
    os << valueDef->GetDefinedName();
    os << " ";
}


void
PrintVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{
    os << " ::= ";
}


void
PrintVisitor::VisitValueDefEnd(ValueDef* valueDef)
{
    os << endl << endl << endl;
}


void 
PrintVisitor::VisitValueBegin(Value* value)
{
    if (value->IsNamed())
    {
        os << GetIndent();
        os << value->GetName();
        os << " ";
    }
}


void 
PrintVisitor::VisitValueEnd(Value* value)
{
    if (GetIterSize() > 1)
    {
        if (value->IsNamed() && (IsIterBegin() || IsIterMiddle()))
        {
            os << ",";
            os << endl << endl;
        }

        if (value->IsNamed() && IsIterEnd())
        {
            os << endl;
        }
    }
    else
    {
        if (value->IsNamed())
        {
            os << endl;
        }
    }
}


void
PrintVisitor::VisitBitStringValue(BitStringValue* bitStringValue)
{
    os << "'";
    os << bitStringValue->GetValue();
    os << "'B";
}


void
PrintVisitor::VisitBooleanValue(BooleanValue* booleanValue)
{
    if (booleanValue->GetValue())
    {
        os << "TRUE";
    }
    else
    {
        os << "FALSE";
    }
}


void
PrintVisitor::VisitCharacterStringValue(
                            CharacterStringValue* characterStringValue)
{
    os << "\"";
    os << characterStringValue->GetValue();
    os << "\"";
}


void
PrintVisitor::VisitChoiceValue(ChoiceValue* choiceValue)
{
    os << choiceValue->GetName();
    os << " : ";
}


void
PrintVisitor::VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
{
    os << enumeratedValue->GetName();
}


void
PrintVisitor::VisitIntegerValue(IntegerValue* integerValue)
{
    os << integerValue->GetValue();
}


void
PrintVisitor::VisitObjectIdentifierValue(
                            ObjectIdentifierValue* objectIdentifierValue)
{
    os << "{";
    os << objectIdentifierValue->GetValue();
    os << "}";
}


void
PrintVisitor::VisitOctetStringValue(OctetStringValue* octetStringValue)
{
    os << "'";
    os << octetStringValue->GetValue();
    os << "'H";
}


void
PrintVisitor::VisitMaxValue(MaxValue* maxValue)
{
    os << "MAX";
}


void
PrintVisitor::VisitMinValue(MinValue* minValue)
{
    os << "MIN";
}


void
PrintVisitor::VisitNullValue(NullValue* nullValue)
{
    os << "NULL";
}


void
PrintVisitor::VisitRealValue(RealValue* realValue)
{
    os << realValue->GetValue();
}


void 
PrintVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{
    os << endl;

    os << GetIndent();
    os << "{";
    os << endl;

    indentLevel += 1;
}


void 
PrintVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{
    indentLevel -=1;

    os << GetIndent();
    os << "}";
}


void 
PrintVisitor::VisitDefinedValue(DefinedValue* definedValue)
{
    os << definedValue->GetName();

    if (definedValue->IsEnumeratedValue())
    {
        os << " -- [enum value] --";
    }
    else if (definedValue->IsLinked())
    {
        os << " -- [linked] --";
    }
    else
    {
        os << " -- [not linked] --";
    }
}


void 
PrintVisitor::VisitAnyValue(AnyValue* anyValue)
{
    Type* type = anyValue->GetType();

    if (type->GetType() == TYPE_DEFINED)
    {
        DefinedType* definedType = static_cast<DefinedType*>(type);

        os << definedType->GetName();
        os << " : ";
    }  
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void 
PrintVisitor::VisitNamedNumberBegin(NamedNumber* namedNumber)
{
    os << GetIndent() << namedNumber->GetName();

    if (namedNumber->HasNumber())
    {
        os << "(";
        os << namedNumber->GetNumber();
        os << ")";
    }

    if (namedNumber->HasDefinedValue())
    {
        os << "( ";
    }
}


void 
PrintVisitor::VisitNamedNumberEnd(NamedNumber* namedNumber)
{
    if (namedNumber->HasDefinedValue())
    {
        os << " )";
    }

    if ((IsIterBegin() || IsIterMiddle()) && GetIterSize() > 1)
    {
        os << ",";
        os << endl;
    }

    if (IsIterEnd() || GetIterSize() == 1)
    {
        os << endl;
    }
}


void 
PrintVisitor::VisitTag(Tag* tag)
{

}


void 
PrintVisitor::VisitConstraintBegin(Constraint* constraint)
{
    os << "(";
}


void 
PrintVisitor::VisitConstraintEnd(Constraint* constraint)
{
    os << ")";
}


void
PrintVisitor::VisitSingleValueConstraintElementBegin(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{

}


void
PrintVisitor::VisitSingleValueConstraintElementEnd(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{

}


void
PrintVisitor::VisitValueRangeConstraintElementBegin(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}


void
PrintVisitor::VisitValueRangeConstraintElementMiddle(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    os << "..";
}


void
PrintVisitor::VisitValueRangeConstraintElementEnd(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}



void PrintVisitor::VisitSizeConstraintElementBegin(
                            SizeConstraintElement* 
                                sizeConstraintElement)
{
    os << "SIZE";
}


void PrintVisitor::VisitSizeConstraintElementEnd(
                            SizeConstraintElement*
                                sizeConstraintElement)
{


}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

string
PrintVisitor::GetIndent() const
{
    string result;
    result.reserve(indentLevel * 4);

    for (int i = 0; i < indentLevel; i++)
    {
        result.append("    ");
    }

    return result;
}

