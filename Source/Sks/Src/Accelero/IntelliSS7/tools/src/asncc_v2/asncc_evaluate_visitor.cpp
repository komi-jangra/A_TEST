///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            Copyright 1999 - 2002 IntelliNet Technologies, Inc.            //
//                          All Rights Reserved.                             //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
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
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:41  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:19  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:45  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:52:59  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/06/17 21:51:43  hdivoux
// LOG: Added processing for default ASN.1 values.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_evaluate_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"


#include <asncc_evaluate_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  EvaluateVisitor implementation.
//

//
//  [1] Decorate each Value object with associated Type.
//
//  [2] Check type validity of Value objects.
//


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

void 
EvaluateVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{

}


void 
EvaluateVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{

}


void 
EvaluateVisitor::VisitTypeBegin(Type* type)
{


}


void 
EvaluateVisitor::VisitTypeEnd(Type* type)
{


}


void
EvaluateVisitor::VisitTypeDefaultValue(Type* type, Value* value)
{
    REQUIRE(type != NULL);

    Type* baseType = type->GetBaseType();

    if (value != NULL)
    {
        value->SetAssociatedType(baseType);

        value->Accept(this);
    }
}


void 
EvaluateVisitor::VisitDefinedType(DefinedType* definedType)
{

}


////////////////////////////////////////////////////////////////////////////////


void 
EvaluateVisitor::VisitValueDefBegin(ValueDef* valueDef)
{
    Value* value = valueDef->GetValue();
    Type* type = valueDef->GetType();
    Type* baseType = type->GetBaseType();

    value->SetAssociatedType(baseType);
}


void 
EvaluateVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{
    // Nothing to do.
}


void 
EvaluateVisitor::VisitValueDefEnd(ValueDef* valueDef)
{
    // Nothing to do.
}


void 
EvaluateVisitor::VisitValueBegin(Value* value)
{
    REQUIRE(value != NULL);

    valueStack.push_front(value);

}


void 
EvaluateVisitor::VisitValueEnd(Value* value)
{
    valueStack.pop_front();
}


void 
EvaluateVisitor::VisitDefinedValue(DefinedValue* definedValue)
{
    // EnumeratedValues are processed as unlinked DefinedValues.

    if (!(definedValue->IsLinked()))
    {
        Type* associatedType = definedValue->GetAssociatedType();

        if (associatedType->GetType() != TYPE_ENUMERATED)
        {
            // Process as a link error (see link visitor).

            Module* localModule = definedValue->GetModule();

            PrintErrLoc(
                localModule->GetAsn1SrcFileName(),
                definedValue->GetLineNumber());
            cerr << "ERROR - value definition \"";
            cerr << definedValue->GetName();
            cerr << "\" ";
            cerr << "used but not local and not imported.";
            cerr << endl;

            localModule->AddError(Module::MODULE_LINK_ERROR);
        }
        else 
        {
            EnumeratedType* enumeratedType = 
                static_cast<EnumeratedType*> (associatedType);

            if (enumeratedType->HasNamedNumber(definedValue->GetName()))
            {
                definedValue->SetEnumeratedValue();
            }
            else
            {
                Module* localModule = definedValue->GetModule();

                PrintErrLoc(
                    localModule->GetAsn1SrcFileName(),
                    definedValue->GetLineNumber());
                cerr << "ERROR - ENUMERATED value is not valid.";
                cerr << endl;

                localModule->AddError(Module::MODULE_EVALUATE_ERROR);
            }
        }
    }
    else
    {
        // Nothing to do.
    }
}


void 
EvaluateVisitor::VisitBitStringValue(BitStringValue* bitStringValue)
{
    // TODO: OctetStringValue and BitStringValue are exchangeable. Add
    // polymorphic type for both.

    ASSERT(bitStringValue->HasAssociatedType());

    Type* associatedType = bitStringValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_BIT_STRING &&
        associatedType->GetType() != TYPE_OCTET_STRING)
    {
        PrintErrLoc(
            bitStringValue->GetModule()->GetAsn1SrcFileName(),
            bitStringValue->GetLineNumber());
        cerr << "ERROR - BIT STRING value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}


void 
EvaluateVisitor::VisitBooleanValue(BooleanValue* booleanValue)
{
    ASSERT(booleanValue->HasAssociatedType());

    Type* associatedType = booleanValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_BOOLEAN)
    {
        PrintErrLoc(
            booleanValue->GetModule()->GetAsn1SrcFileName(),
            booleanValue->GetLineNumber());
        cerr << "ERROR - BOOLEAN value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}


void 
EvaluateVisitor::VisitCharacterStringValue(
                            CharacterStringValue* 
                                characterStringValue)
{
    ASSERT(characterStringValue->HasAssociatedType());

    Type* associatedType = characterStringValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_CHARACTER_STRING &&
        associatedType->GetType() != TYPE_OCTET_STRING)
    {
        PrintErrLoc(
            characterStringValue->GetModule()->GetAsn1SrcFileName(),
            characterStringValue->GetLineNumber());
        cerr << "ERROR - CHARACTER STRING value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}


void 
EvaluateVisitor::VisitChoiceValue(ChoiceValue* choiceValue)
{
    ASSERT(choiceValue->HasAssociatedType());

    Type* associatedType = choiceValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_CHOICE)
    {
        PrintErrLoc(
            choiceValue->GetModule()->GetAsn1SrcFileName(),
            choiceValue->GetLineNumber());
        cerr << "ERROR - CHOICE value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
    else
    {
        Value* value = choiceValue->GetValue();

        ChoiceType* choiceType =
            static_cast<ChoiceType*> (associatedType);

        if (choiceType->HasNamedType(choiceValue->GetName()))
        {
            Type* namedType = 
                choiceType->
                    RetrieveNamedType(choiceValue->GetName());

            Type* baseType = namedType->GetBaseType();

            value->SetAssociatedType(baseType);
        }
        else
        {
            PrintErrLoc(
                choiceValue->GetModule()->GetAsn1SrcFileName(),
                choiceValue->GetLineNumber());
            cerr << "ERROR - CHOICE value contains unknown value ";
            cerr << "name \"";
            cerr << choiceValue->GetName();
            cerr << "\".";
            cerr << endl;

            module->AddError(Module::MODULE_SEMANTIC_ERROR);
        }
    }
}


void 
EvaluateVisitor::VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
{
    // Nothing to do. EnumeratedValues are processed as DefinedValues.
}


void 
EvaluateVisitor::VisitIntegerValue(IntegerValue* integerValue)
{
    ASSERT(integerValue->HasAssociatedType());

    Type* associatedType = integerValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_INTEGER)
    {
        PrintErrLoc(
            integerValue->GetModule()->GetAsn1SrcFileName(),
            integerValue->GetLineNumber());
        cerr << "ERROR - INTEGER value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}


void 
EvaluateVisitor::VisitObjectIdentifierValue(
                                    ObjectIdentifierValue* 
                                        objectIdentifierValue)
{
    ASSERT(objectIdentifierValue->HasAssociatedType());

    Type* associatedType = objectIdentifierValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_OBJECT_IDENTIFIER)
    {
        PrintErrLoc(
            objectIdentifierValue->GetModule()->GetAsn1SrcFileName(),
            objectIdentifierValue->GetLineNumber());
        cerr << "ERROR - OBJECT IDENTIFIER value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }

    // Build component list.

    objectIdentifierValue->MakeComponentList();
}


void
EvaluateVisitor::VisitOctetStringValue(OctetStringValue* octetStringValue)
{
    // TODO: OctetStringValue and BitStringValue are exchangeable. Add 
    // polymorphic type for both.


    ASSERT(octetStringValue->HasAssociatedType());

    Type* associatedType = octetStringValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_OCTET_STRING &&
        associatedType->GetType() != TYPE_BIT_STRING)
    {
        PrintErrLoc(
            octetStringValue->GetModule()->GetAsn1SrcFileName(),
            octetStringValue->GetLineNumber());
        cerr << "ERROR - OCTET STRING value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}


void 
EvaluateVisitor::VisitMaxValue(MaxValue* maxValue)
{
    // Nothing to do (used in constraints only).
}


void 
EvaluateVisitor::VisitMinValue(MinValue* minValue)
{
    // Nothing to do (used in constraints only).
}


void 
EvaluateVisitor::VisitNullValue(NullValue* nullValue)
{
    ASSERT(nullValue->HasAssociatedType());

    Type* associatedType = nullValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_NULL)
    {
        PrintErrLoc(
            nullValue->GetModule()->GetAsn1SrcFileName(),
            nullValue->GetLineNumber());
        cerr << "ERROR - NULL value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}

 
void 
EvaluateVisitor::VisitRealValue(RealValue* realValue)
{
    ASSERT(realValue->HasAssociatedType());

    Type* associatedType = realValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_REAL)
    {
        PrintErrLoc(
            realValue->GetModule()->GetAsn1SrcFileName(),
            realValue->GetLineNumber());
        cerr << "ERROR - REAL value is not a valid type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
}


void 
EvaluateVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{
    ASSERT(sequenceValue->HasAssociatedType());

    Type* associatedType = sequenceValue->GetAssociatedType();

    if (associatedType->GetType() != TYPE_SEQUENCE      &&
        associatedType->GetType() != TYPE_SEQUENCE_OF   &&
        associatedType->GetType() != TYPE_SET           &&
        associatedType->GetType() != TYPE_SET_OF)
    {
        PrintErrLoc(
            sequenceValue->GetModule()->GetAsn1SrcFileName(),
            sequenceValue->GetLineNumber());
        cerr << "ERROR - SEQUENCE, SEQUENCE OF, SET or SET OF is not a valid ";
        cerr << "type.";
        cerr << endl;

        module->AddError(Module::MODULE_EVALUATE_ERROR);
    }
    else
    {
        if (associatedType->GetType() == TYPE_SEQUENCE)
        {
            SequenceType* sequenceType = 
                static_cast<SequenceType*> (associatedType);

            if (sequenceValue->HasUnnamedValue())
            {
                PrintErrLoc(
                    sequenceValue->GetModule()->GetAsn1SrcFileName(),
                    sequenceValue->GetLineNumber());
                cerr << "ERROR - SEQUENCE value contains unnamed value.";
                cerr << endl;

                module->AddError(Module::MODULE_SEMANTIC_ERROR);

                return; // Skip following processing.
            }

            ValueList* valueList = sequenceValue->GetValueList();

            for (ValueList::iterator vIter = valueList->begin();
                 vIter != valueList->end();
                 vIter++)
            {
                Value* value = *vIter;

                // Mandatory assumptions.

                ASSERT(value->IsNamed());
                ASSERT(value->GetName() != "--AsnCC-Unnamed--");

                if (sequenceType->HasNamedType(value->GetName()))
                {
                    Type* namedType = 
                        sequenceType->
                            RetrieveNamedType(value->GetName());

                    Type* baseType = namedType->GetBaseType();

                    value->SetAssociatedType(baseType);
                }
                else
                {
                    PrintErrLoc(
                        sequenceValue->GetModule()->GetAsn1SrcFileName(),
                        sequenceValue->GetLineNumber());
                    cerr << "ERROR - SEQUENCE value contains unknown value ";
                    cerr << "name \"";
                    cerr << value->GetName();
                    cerr << "\".";
                    cerr << endl;

                    module->AddError(Module::MODULE_SEMANTIC_ERROR);
                }
            }

            // TODO: add checking for optional and default components. 
            // Done by runtime anyway.
        }
        else if (associatedType->GetType() == TYPE_SET)
        {
            SetType* setType = 
                static_cast<SetType*> (associatedType);

            sequenceValue->SetPolymorphValueTypeSet();

            if (sequenceValue->HasUnnamedValue())
            {
                PrintErrLoc(
                    sequenceValue->GetModule()->GetAsn1SrcFileName(),
                    sequenceValue->GetLineNumber());
                cerr << "ERROR - SET value contains unnamed value.";
                cerr << endl;

                module->AddError(Module::MODULE_SEMANTIC_ERROR);

                return; // Skip following processing.
            }

            ValueList* valueList = sequenceValue->GetValueList();

            for (ValueList::iterator vIter = valueList->begin();
                 vIter != valueList->end();
                 vIter++)
            {
                Value* value = *vIter;

                // Mandatory assumptions.

                ASSERT(value->IsNamed());
                ASSERT(value->GetName() != "--AsnCC-Unnamed--");

                if (setType->HasNamedType(value->GetName()))
                {
                    Type* namedType =
                        setType->
                            RetrieveNamedType(value->GetName());

                    Type* baseType = namedType->GetBaseType();

                    value->SetAssociatedType(baseType);
                }
                else
                {
                    PrintErrLoc(
                        sequenceValue->GetModule()->GetAsn1SrcFileName(),
                        sequenceValue->GetLineNumber());
                    cerr << "ERROR - SET value contains unknown value name \"";
                    cerr << value->GetName();
                    cerr << "\".";
                    cerr << endl;

                    module->AddError(Module::MODULE_SEMANTIC_ERROR);
                }
            }

            // TODO: add checking for optional and default components.
            // Done by runtime anyway.
        }
        else if (associatedType->GetType() == TYPE_SEQUENCE_OF)
        {
            SequenceOfType* sequenceOfType =
                static_cast<SequenceOfType*> (associatedType);

            sequenceValue->SetPolymorphValueTypeSequenceOf();

            if (sequenceValue->HasNamedValue())
            {
                PrintErrLoc(
                    sequenceValue->GetModule()->GetAsn1SrcFileName(),
                    sequenceValue->GetLineNumber());
                cerr << "WARNING - SEQUENCE OF contains named value.";
                cerr << endl;
            }

            ValueList* valueList = sequenceValue->GetValueList();

            for (ValueList::iterator vIter = valueList->begin();
                 vIter != valueList->end();
                 vIter++)
            {
                Value* value = *vIter;

                Type* type = sequenceOfType->GetSequenceOfType();

                Type* baseType = type->GetBaseType();

                value->SetAssociatedType(baseType);
            }
        }
        else if (associatedType->GetType() == TYPE_SET_OF)
        {
            SetOfType* setOfType =
                static_cast<SetOfType*> (associatedType);

            sequenceValue->SetPolymorphValueTypeSetOf();

            if (sequenceValue->HasNamedValue())
            {
                PrintErrLoc(
                    sequenceValue->GetModule()->GetAsn1SrcFileName(),
                    sequenceValue->GetLineNumber());
                cerr << "WARNING - SET OF contains named value.";
                cerr << endl;
            }

            ValueList* valueList = sequenceValue->GetValueList();

            for (ValueList::iterator vIter = valueList->begin();
                 vIter != valueList->end();
                 vIter++)
            {
                Value* value = *vIter;

                Type* type = setOfType->GetSetOfType();

                Type* baseType = type->GetBaseType();

                value->SetAssociatedType(baseType);
            }
        }   
    }
}


void 
EvaluateVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{
    // Nothing to do.
}


void
EvaluateVisitor::VisitAnyValue(AnyValue* anyValue)
{
    Type* type = anyValue->GetType();

    Type* baseType = type->GetBaseType();

    anyValue->GetValue()->SetAssociatedType(baseType);
}


////////////////////////////////////////////////////////////////////////////////

void
EvaluateVisitor::VisitSingleValueConstraintElementBegin(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{
    Value* value = singleValueConstraintElement->GetValue();

    Value* baseValue = value->GetBaseValue();

    if (baseValue->GetValueType() == VALUE_INTEGER)
    {
        value->SetAssociatedType(new IntegerType());
    }
}


void
EvaluateVisitor::VisitSingleValueConstraintElementEnd(
                            SingleValueConstraintElement*
                                singleValueConstraintElement)
{

}


void
EvaluateVisitor::VisitValueRangeConstraintElementBegin(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{
    Value* lowerValue = valueRangeConstraintElement->GetLower();
    Value* upperValue = valueRangeConstraintElement->GetUpper();

    Value* lowerBaseValue = lowerValue->GetBaseValue();
    Value* upperBaseValue = upperValue->GetBaseValue();

    if (lowerBaseValue->GetValueType() == VALUE_INTEGER)
    {
        lowerValue->SetAssociatedType(new IntegerType());
    }

    if (lowerBaseValue->GetValueType() == VALUE_MIN)
    {
        lowerValue->SetAssociatedType(new IntegerType());
    }

    if (upperBaseValue->GetValueType() == VALUE_INTEGER)
    {
        upperValue->SetAssociatedType(new IntegerType());
    }

    if (upperBaseValue->GetValueType() == VALUE_MAX)
    {
        upperValue->SetAssociatedType(new IntegerType());
    }
}


void
EvaluateVisitor::VisitValueRangeConstraintElementMiddle(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}


void
EvaluateVisitor::VisitValueRangeConstraintElementEnd(
                            ValueRangeConstraintElement*
                                valueRangeConstraintElement)
{

}

////////////////////////////////////////////////////////////////////////////////
