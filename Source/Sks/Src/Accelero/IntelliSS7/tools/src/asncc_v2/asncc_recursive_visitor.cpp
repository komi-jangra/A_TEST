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
// LOG: Revision 8.2  2005/03/21 13:53:01  cvsadmin
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

#ident "$Id: asncc_recursive_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $"


#include <asncc_recursive_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  RecursiveVisitor implementation.
//

// TODO: add check for recursive COMPONENTS OF and Selection Type.


void 
RecursiveVisitor::VisitTypeDefBegin(TypeDef* typeDef)
{
    REQUIRE(typeDef != NULL);

    typeDef->Mark();
}


void 
RecursiveVisitor::VisitTypeDefEnd(TypeDef* typeDef)
{
    REQUIRE(typeDef != NULL);

    typeDef->Unmark();
}


void
RecursiveVisitor::VisitDefinedType(DefinedType* definedType)
{
    REQUIRE(definedType != NULL);
    REQUIRE(definedType->IsLinked());

    TypeDef* typeDef = definedType->GetTypeDefLink();

    Type* type = typeDef->GetType();

    if (typeDef->IsMarked())
    {
        typeDef->SetRecursive();

        PrintErrLoc(module->GetAsn1SrcFileName(), type->GetLineNumber());
        cerr << "ERROR - type definition \"";
        cerr << typeDef->GetDefinedName();
        cerr << "\" is recursive.";
        cerr << endl;

        module->AddError(Module::MODULE_RECURSIVE_ERROR);
    }
    else
    {
        typeDef->Accept(this);
    }
}


////////////////////////////////////////////////////////////////////////////////


void 
RecursiveVisitor::VisitValueDefBegin(ValueDef* valueDef)
{
    REQUIRE(valueDef != NULL);

    valueDef->Mark();
}


void 
RecursiveVisitor::VisitValueDefMiddle(ValueDef* valueDef)
{
    REQUIRE(valueDef != NULL);

    // Nothing to do.
}


void 
RecursiveVisitor::VisitValueDefEnd(ValueDef* valueDef)
{
    REQUIRE(valueDef != NULL);

    valueDef->Unmark();
}


void 
RecursiveVisitor::VisitDefinedValue(DefinedValue* definedValue)
{
    REQUIRE(definedValue != NULL);

    if (!definedValue->IsLinked())
    {
        // Nothing to do.

        return;
    }

    ASSERT(definedValue->IsLinked());

    ValueDef* valueDef = definedValue->GetValueDefLink();

    Value* value = valueDef->GetValue();

    if (valueDef->IsMarked())
    {
        valueDef->SetRecursive();

        PrintErrLoc(module->GetAsn1SrcFileName(), value->GetLineNumber());
        cerr << "ERROR - value definition \"";
        cerr << valueDef->GetDefinedName();
        cerr << "\" is recursive.";
        cerr << endl;

        module->AddError(Module::MODULE_RECURSIVE_ERROR);
    }
    else
    {
        valueDef->Accept(this);
    }
}

