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
//  ID: $Id: asncc_normalize_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_normalize_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  NormalizeVisitor implementation.
//

//
//  [1] Build NamedTypeTable for SequenceType, SetType and ChoiceType.
//
//  [2] Build NamedNumberTable for EnumeratedType.
//
//  [3] Build NamedValueTable for SequenceValue.
//


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

void 
NormalizeVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{

}


void 
NormalizeVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{

}


void 
NormalizeVisitor::VisitTypeBegin(Type* type)
{


}


void 
NormalizeVisitor::VisitTypeEnd(Type* type)
{


}


void 
NormalizeVisitor::VisitDefinedType(DefinedType* definedType)
{

}


void 
NormalizeVisitor::VisitChoiceTypeBegin(ChoiceType* choiceType)
{
    choiceType->MakeNamedTypeTable();
}


void 
NormalizeVisitor::VisitChoiceTypeEnd(ChoiceType* choiceType)
{
    // Nothing to do.
}


void 
NormalizeVisitor::VisitEnumeratedTypeBegin(EnumeratedType* enumeratedType)
{
    enumeratedType->MakeNamedNumberTable();
}


void 
NormalizeVisitor::VisitEnumeratedTypeEnd(EnumeratedType* enumeratedType)
{
    // Nothing to do.
}


void 
NormalizeVisitor::VisitSequenceTypeBegin(SequenceType* sequenceType)
{
    sequenceType->MakeNamedTypeTable();
}


void 
NormalizeVisitor::VisitSequenceTypeEnd(SequenceType* sequenceType)
{
    // Nothing to do.
}


void 
NormalizeVisitor::VisitSetTypeBegin(SetType* setType)
{
    setType->MakeNamedTypeTable();
}


void 
NormalizeVisitor::VisitSetTypeEnd(SetType* setType)
{

}


////////////////////////////////////////////////////////////////////////////////


void 
NormalizeVisitor::VisitValueDefBegin(ValueDef* valueDef)
{


}


void 
NormalizeVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{

}


void 
NormalizeVisitor::VisitValueDefEnd(ValueDef* valueDef)
{

}


void 
NormalizeVisitor::VisitDefinedValue(DefinedValue* definedValue)
{


}


void 
NormalizeVisitor::VisitSequenceValueBegin(SequenceValue* sequenceValue)
{
    sequenceValue->MakeNamedValueTable();
}


void 
NormalizeVisitor::VisitSequenceValueEnd(SequenceValue* sequenceValue)
{
    // Nothing to do.
}


////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
