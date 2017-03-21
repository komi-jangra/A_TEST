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
// LOG: Revision 1.1.1.1  2007/03/08 15:14:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:14  cvsadmin
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

#ident "$Id: asncc_normalize_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"


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
