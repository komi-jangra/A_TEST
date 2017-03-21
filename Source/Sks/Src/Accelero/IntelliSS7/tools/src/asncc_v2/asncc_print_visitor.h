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
// LOG: Revision 1.1.1.1  2007/08/03 06:49:20  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:15  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:00  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(_ASNCC_PRINT_VISITOR_H_)
#define _ASNCC_PRINT_VISITOR_H_

#ident "$Id: asncc_print_visitor.h,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $"

#include <asncc_visitor.h>


////////////////////////////////////////////////////////////////////////////////
//
//  PrintVisitor interface.
//

class PrintVisitor : public Visitor
{
public:

    PrintVisitor(std::ostream& osParam) 
    :   os(osParam),
        indentLevel(0)
    {
        SetVisitRecursive();
    }

    // Default copy constructor ok.

    // Default destructor ok (no memory management).

    // Default assignment operator ok.

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitModuleBegin(Module* module);
    
    virtual void VisitModuleEnd(Module* module);

    virtual void VisitImportedModule(ImportedModule* importedModule);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitTypeDefBegin(TypeDef* typeDef);

    virtual void VisitTypeDefEnd(TypeDef* typeDef);

    virtual void VisitTypeBegin(Type* type);

    virtual void VisitTypeEnd(Type* type);

    virtual void VisitTypeDefaultValue(Type* type, Value* value);

    virtual void VisitTypeConstraintList(ConstraintList* constraintlist);

    virtual void VisitBitStringTypeBegin(BitStringType* bitStringType);

    virtual void VisitBitStringTypeEnd(BitStringType* bitStringType);

    virtual void VisitBooleanType(BooleanType* booleanType);

    virtual void VisitChoiceTypeBegin(ChoiceType* choiceType);

    virtual void VisitChoiceTypeEnd(ChoiceType* choiceType);

    virtual void VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType);

    virtual void VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType);

    virtual void VisitIntegerTypeBegin(IntegerType* integerType);

    virtual void VisitIntegerTypeEnd(IntegerType* integerType);

    virtual void VisitObjectIdentifierType(
                                ObjectIdentifierType* objectIdentifierType);

    virtual void VisitNullType(NullType* nullType);

    virtual void VisitRealType(RealType* realType);

    virtual void VisitSequenceTypeBegin(SequenceType* sequenceType);

    virtual void VisitSequenceTypeEnd(SequenceType* sequenceType);

    virtual void VisitSequenceOfTypeBegin(SequenceOfType* sequenceOfType);

    virtual void VisitSequenceOfTypeEnd(SequenceOfType* sequenceOfType);

    virtual void VisitSequenceOfConstraint(Constraint* constraint);

    virtual void VisitSetTypeBegin(SetType* setType);

    virtual void VisitSetTypeEnd(SetType* setType);

    virtual void VisitSetOfTypeBegin(SetOfType* setOfType);

    virtual void VisitSetOfTypeEnd(SetOfType* setOfType);

    virtual void VisitSetOfConstraint(Constraint* constraint);

    virtual void VisitOctetStringType(OctetStringType* octetStringType);

    virtual void VisitDefinedType(DefinedType* definedType);

    virtual void VisitAnyType(AnyType* anyType);

    virtual void VisitAnyDefinedByType(AnyDefinedByType* anyDefinedByType);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitValueDefBegin(ValueDef* valueDef);

    virtual void VisitValueDefMiddle(ValueDef* valueDef);

    virtual void VisitValueDefEnd(ValueDef* valueDef);

    virtual void VisitValueBegin(Value* value);

    virtual void VisitValueEnd(Value* value);

    virtual void VisitBitStringValue(BitStringValue* bitStringValue);

    virtual void VisitBooleanValue(BooleanValue* booleanValue);

    virtual void VisitCharacterStringValue(
                                CharacterStringValue* characterStringValue);

    virtual void VisitChoiceValue(ChoiceValue* choiceValue);

    virtual void VisitEnumeratedValue(EnumeratedValue* enumeratedValue);

    virtual void VisitIntegerValue(IntegerValue* integerValue);

    virtual void VisitObjectIdentifierValue(
                                ObjectIdentifierValue* objectIdentifierValue);

    virtual void VisitOctetStringValue(OctetStringValue* octetStringValue);

    virtual void VisitMaxValue(MaxValue* maxValue);

    virtual void VisitMinValue(MinValue* minValue);

    virtual void VisitNullValue(NullValue* nullValue);

    virtual void VisitRealValue(RealValue* realValue);

    virtual void VisitSequenceValueBegin(SequenceValue* sequenceValue);

    virtual void VisitSequenceValueEnd(SequenceValue* sequenceValue);

    virtual void VisitDefinedValue(DefinedValue* definedValue);

    virtual void VisitAnyValue(AnyValue* anyValue);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitNamedNumberBegin(NamedNumber* namedNumber);

    virtual void VisitNamedNumberEnd(NamedNumber* namedNumber);

    virtual void VisitTag(Tag* tag);

    virtual void VisitConstraintBegin(Constraint* constraint);

    virtual void VisitConstraintEnd(Constraint* constraint);

    virtual void VisitSingleValueConstraintElementBegin(
                        SingleValueConstraintElement*
                            singleValueConstraintElement);

    virtual void VisitSingleValueConstraintElementEnd(
                        SingleValueConstraintElement*
                            singleValueConstraintElement);

    virtual void VisitValueRangeConstraintElementBegin(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement);

    virtual void VisitValueRangeConstraintElementMiddle(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement);

    virtual void VisitValueRangeConstraintElementEnd(
                        ValueRangeConstraintElement*
                            valueRangeConstraintElement);

    virtual void VisitSizeConstraintElementBegin(
                        SizeConstraintElement* 
                            sizeConstraintElement);

    virtual void VisitSizeConstraintElementEnd(
                        SizeConstraintElement*
                            sizeConstraintElement);

    ////////////////////////////////////////////////////////////////////////////

    int
    GetIndentLevel() const
    { return indentLevel; }

    std::string GetIndent() const;

protected:

    std::ostream& os;

    std::string defaultValueString;

    std::string constraintListString;

    std::string sequenceOfConstraintString;

    std::string setOfConstraintString;

    int indentLevel;
};



#endif // !defined(_ASNCC_PRINT_VISITOR_H_)
