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
//  ID: $Id: asncc_visitor.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_VISITOR_H_)
#define _ASNCC_VISITOR_H_

#include <asncc.h>
#include <asncc_assertion.h>


////////////////////////////////////////////////////////////////////////////////

class Module;
class ImportedModule;

class TypeDef;
class Type;
class BitStringType;
class BooleanType;
class ChoiceType;
class EnumeratedType;
class IntegerType;
class NullType;
class ObjectIdentifierType;
class OctetStringType;
class RealType;
class SequenceType;
class SequenceOfType;
class SetType;
class SetOfType;
class DefinedType;
class AnyType;
class AnyDefinedByType;

class ValueDef;
class Value;
class BitStringValue;
class BooleanValue;
class CharacterStringValue;
class ChoiceValue;
class EnumeratedValue;
class IntegerValue;
class ObjectIdentifierValue;
class OctetStringValue;
class MaxValue;
class MinValue;
class NullValue;
class RealValue;
class SequenceValue;
class DefinedValue;
class AnyValue;

class NamedNumber;
class Tag;
class Constraint;
class ConstraintElement;
class ConstrainAllConstraintElement;
class ElementListConstraintElement;
class SingleValueConstraintElement;
class ValueRangeConstraintElement;
class NestedConstraintConstraintElement;
class SizeConstraintElement;
class FromConstraintElement;
class WithComponentConstraintElement;
class InnerTypeConstraintElement;
class UserDefinedConstraintElement;
class SubTypeConstraintElement;


typedef std::list<Constraint*> ConstraintList;
typedef std::list<Type*> TypeList;


////////////////////////////////////////////////////////////////////////////////
//
//  Visitor interface.
//

class Visitor
{
public:

    Visitor()
    :   iterPosition(ITER_BEGIN),
        iterSize(0),
        visitRecursive(false),
        visitFlattened(false)
    {}

    // Default copy constructor ok.

    // Default destructor ok (no memory management).

    // Default assignment operator ok.

    ////////////////////////////////////////////////////////////////////////////

    virtual void 
    VisitModuleBegin(Module* module) 
    {}

    virtual void 
    VisitModuleEnd(Module* module)
    {}

    virtual void 
    VisitImportedModule(ImportedModule* importedModule)
    {}

    ////////////////////////////////////////////////////////////////////////////

    virtual void 
    VisitTypeDefBegin(TypeDef* typeDef) 
    {}

    virtual void 
    VisitTypeDefEnd(TypeDef* typeDef) 
    {}

    virtual void 
    VisitTypeBegin(Type* type) 
    {}

    virtual void 
    VisitTypeEnd(Type* type) 
    {}

    virtual void VisitTypeDefaultValue(Type* type, Value* value);

    virtual void VisitTypeConstraintList(ConstraintList* constraintList);

    virtual void 
    VisitBitStringTypeBegin(BitStringType* bitStringType)
    {}

    virtual void 
    VisitBitStringTypeEnd(BitStringType* bitStringType)
    {}

    virtual void 
    VisitBooleanType(BooleanType* booleanType)
    {}

    virtual void 
    VisitChoiceTypeBegin(ChoiceType* choiceType)
    {}

    virtual void 
    VisitChoiceTypeEnd(ChoiceType* choiceType)
    {}

    virtual void VisitChoiceTypeList(TypeList* typeList);

    virtual void 
    VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
    {}

    virtual void 
    VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
    {}

    virtual void 
    VisitIntegerTypeBegin(IntegerType* integerType)
    {}

    virtual void 
    VisitIntegerTypeEnd(IntegerType* integerType)
    {}

    virtual void
    VisitObjectIdentifierType(ObjectIdentifierType* objectIdentifierType)
    {}

    virtual void
    VisitNullType(NullType* nullType)
    {}

    virtual void
    VisitRealType(RealType* realType)
    {}

    virtual void
    VisitSequenceTypeBegin(SequenceType* sequenceType) 
    {}

    virtual void
    VisitSequenceTypeEnd(SequenceType* sequenceType) 
    {}

    virtual void VisitSequenceTypeList(TypeList* typeList);

    virtual void
    VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType) 
    {}

    virtual void
    VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType) 
    {}

    virtual void VisitSequenceOfTypeType(Type* type);

    virtual void VisitSequenceOfConstraint(Constraint* constraint);

    virtual void
    VisitSetTypeBegin(SetType* setType) 
    {}

    virtual void
    VisitSetTypeEnd(SetType* setType) 
    {}

    virtual void VisitSetTypeList(TypeList* typeList);

    virtual void
    VisitSetOfTypeBegin(SetOfType* setOfType) 
    {}

    virtual void
    VisitSetOfTypeEnd(SetOfType* setOfType) 
    {}

    virtual void VisitSetOfTypeType(Type* type);

    virtual void VisitSetOfConstraint(Constraint* constraint);

    virtual void 
    VisitOctetStringType(OctetStringType* octetStringType)
    {}

    virtual void
    VisitDefinedType(DefinedType* definedType)
    {}

    virtual void
    VisitAnyType(AnyType* anyType)
    {}

    virtual void
    VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType)
    {}

    ////////////////////////////////////////////////////////////////////////////

    virtual void
    VisitValueDefBegin(ValueDef* valueDef)
    {}

    virtual void 
    VisitValueDefMiddle(ValueDef* valueDef)
    {}

    virtual void
    VisitValueDefEnd(ValueDef* valueDef)
    {}

    virtual void VisitValueDefType(ValueDef* valueDef, Type* type);

    virtual void 
    VisitValueBegin(Value* value)
    {}

    virtual void 
    VisitValueEnd(Value* value)
    {}

    virtual void
    VisitBitStringValue(BitStringValue* bitStringValue)
    {}

    virtual void
    VisitBooleanValue(BooleanValue* booleanValue)
    {}

    virtual void
    VisitCharacterStringValue(CharacterStringValue* characterStringValue)
    {}

    virtual void
    VisitChoiceValue(ChoiceValue* choiceValue)
    {}

    virtual void
    VisitEnumeratedValue(EnumeratedValue* enumeratedValue)
    {}

    virtual void
    VisitIntegerValue(IntegerValue* integerValue)
    {}

    virtual void
    VisitObjectIdentifierValue(ObjectIdentifierValue* objectIdentifierValue)
    {}

    virtual void
    VisitOctetStringValue(OctetStringValue* octetStringValue)
    {}

    virtual void
    VisitMaxValue(MaxValue* maxValue)
    {}

    virtual void
    VisitMinValue(MinValue* minValue)
    {}

    virtual void
    VisitNullValue(NullValue* nullValue)
    {}

    virtual void
    VisitRealValue(RealValue* realValue)
    {}

    virtual void
    VisitSequenceValueBegin(SequenceValue* sequenceValue)
    {}

    virtual void
    VisitSequenceValueEnd(SequenceValue* sequenceValue)
    {}

    virtual void
    VisitDefinedValue(DefinedValue* definedValue)
    {}

    virtual void
    VisitAnyValue(AnyValue* anyValue)
    {}

    ////////////////////////////////////////////////////////////////////////////

    virtual void 
    VisitNamedNumberBegin(NamedNumber* namedNumber) 
    {}

    virtual void 
    VisitNamedNumberEnd(NamedNumber* namedNumber) 
    {}

    virtual void 
    VisitTag(Tag* tag)
    {}

    virtual void 
    VisitConstraintBegin(Constraint* constraint) 
    {}

    virtual void 
    VisitConstraintEnd(Constraint* constraint) 
    {}

    virtual void
    VisitConstrainAllConstraintElementBegin(
                        ConstrainAllConstraintElement*
                            constrainAllConstraintElement)
    {}

    virtual void
    VisitConstrainAllConstraintElementEnd(
                        ConstrainAllConstraintElement*
                            constrainAllConstraintElement)
    {}

    virtual void
    VisitElementListConstraintElementBegin(
                        ElementListConstraintElement*
                            elementListConstraintElement)
    {}

    virtual void
    VisitElementListConstraintElementEnd(
                        ElementListConstraintElement*
                            elementListConstraintElement)
    {}

    virtual void
    VisitSingleValueConstraintElementBegin(
                        SingleValueConstraintElement*
                            singleValueConstraintElement)
    {}

    virtual void
    VisitSingleValueConstraintElementEnd(
                        SingleValueConstraintElement*
                            singleValueConstraintElement)
    {}

    virtual void
    VisitValueRangeConstraintElementBegin(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement)
    {}

    virtual void
    VisitValueRangeConstraintElementMiddle(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement)
    {}

    virtual void
    VisitValueRangeConstraintElementEnd(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement)
    {}

    virtual void
    VisitNestedConstraintConstraintElementBegin(
                        NestedConstraintConstraintElement*
                            nestedConstraintConstraintElement)
    {}

    virtual void
    VisitNestedConstraintConstraintElementEnd(
                        NestedConstraintConstraintElement*
                            nestedConstraintConstraintElement)
    {}

    virtual void
    VisitSizeConstraintElementBegin(
                        SizeConstraintElement*
                            sizeConstraintElement)
    {}

    virtual void
    VisitSizeConstraintElementEnd(
                        SizeConstraintElement*
                            sizeConstraintElement)
    {}

    virtual void
    VisitFromConstraintElementBegin(
                        FromConstraintElement*
                            fromConstraintElement)
    {}

    virtual void
    VisitFromConstraintElementEnd(
                        FromConstraintElement*
                            fromConstraintElement)
    {}

    virtual void
    VisitWithComponentConstraintElementBegin(
                        WithComponentConstraintElement*
                            withComponentConstraintElement)
    {}

    virtual void
    VisitWithComponentConstraintElementEnd(
                        WithComponentConstraintElement*
                            withComponentConstraintElement)
    {}

    virtual void
    VisitInnerTypeConstraintElementBegin(
                        InnerTypeConstraintElement*
                            innerTypeConstraintElement)
    {}

    virtual void
    VisitInnerTypeConstraintElementEnd(
                        InnerTypeConstraintElement*
                            innerTypeConstraintElement)
    {}
    
    virtual void
    VisitUserDefinedConstraintElementBegin(
                        UserDefinedConstraintElement*
                            userDefinedConstraintElement)
    {}

    virtual void
    VisitUserDefinedConstraintElementEnd(
                        UserDefinedConstraintElement*
                            userDefinedConstraintElement)
    {}

    virtual void
    VisitSubTypeConstraintElementBegin(
                        SubTypeConstraintElement*
                            subTypeConstraintElement)
    {}

    virtual void
    VisitSubTypeConstraintElementEnd(
                        SubTypeConstraintElement*
                            subTypeConstraintElement)
    {}


    ////////////////////////////////////////////////////////////////////////////

    typedef unsigned int IterSize;

    void
    SetIterBegin()
    { iterPosition = ITER_BEGIN; }

    bool
    IsIterBegin() const
    { return iterPosition == ITER_BEGIN; }

    void
    SetIterMiddle()
    { iterPosition = ITER_MIDDLE; }

    bool
    IsIterMiddle() const
    { return iterPosition == ITER_MIDDLE; }

    void
    SetIterEnd()
    { iterPosition = ITER_END; }

    bool
    IsIterEnd()
    { return iterPosition == ITER_END; }

    void
    SetIterSize(IterSize iterSizeParam)
    { iterSize = iterSizeParam; }

    IterSize
    GetIterSize() const
    { return iterSize; }

    void 
    PushIterContext()
    {
        iterPositionStack.push_front(iterPosition);
        iterSizeStack.push_front(iterSize);
    }

    bool
    IsIterContextPushed() const
    { return !(iterPositionStack.empty() || iterSizeStack.empty()); }

    void 
    PopIterContext()
    {
        REQUIRE(IsIterContextPushed());

        iterPosition = iterPositionStack.front();
        iterPositionStack.pop_front();

        iterSize = iterSizeStack.front();
        iterSizeStack.pop_front();
    }

    ////////////////////////////////////////////////////////////////////////////

    void
    SetVisitRecursive()
    { visitRecursive = true; }

    void
    UnsetVisitRecursive()
    { visitRecursive = false; }

    bool
    VisitRecursive() const
    { return visitRecursive; }

    void
    SetVisitFlattened()
    { visitFlattened = true; }

    void
    UnsetVisitFlattened()
    { visitFlattened = false; }

    bool
    VisitFlattened() const
    { return visitFlattened; }



    ////////////////////////////////////////////////////////////////////////////

protected:

    enum IterPosition {
        ITER_BEGIN,
        ITER_MIDDLE,
        ITER_END
    };

    IterPosition iterPosition;

    IterSize iterSize;

    // IterPosition Context push/pop.

    std::list<IterPosition> iterPositionStack;

    // IterSize Context push/pop.

    std::list<IterSize> iterSizeStack;

    bool visitRecursive;

    bool visitFlattened;
};



#endif // !defined(_ASNCC_VISITOR_H_)
