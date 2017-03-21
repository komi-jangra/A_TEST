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
//  ID: $Id: asncc_visitor.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#include <asncc_visitor.h>
#include <asncc_ast.h>
#include <asncc_util.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Visitor (default) implementation.
//

void
Visitor::VisitTypeDefaultValue(Type* type, Value* value)
{
    value->Accept(this);
}


void
Visitor::VisitTypeConstraintList(ConstraintList* constraintList)
{
    PushIterContext();

    SetIterSize(constraintList->size());

    for (ConstraintList::iterator cIter = constraintList->begin();
         cIter != constraintList->end();
         cIter++)
    {
        if (cIter == constraintList->begin())
        {
            SetIterBegin();
        }
        else if (++cIter == constraintList->end())
        {
            --cIter;
            SetIterEnd();
        }
        else
        {
            --cIter;
            SetIterMiddle();
        }

        (*cIter)->Accept(this);
    }

    PopIterContext();
}


void
Visitor::VisitChoiceTypeList(TypeList* typeList)
{
    REQUIRE(typeList != NULL);

    PushIterContext();

    SetIterSize(typeList->size());

    for (TypeList::iterator tIter = typeList->begin();
         tIter != typeList->end();
         tIter++)
    {
        if (tIter == typeList->begin())
        {
            SetIterBegin();
        }
        else if (++tIter == typeList->end())
        {
            --tIter;
            SetIterEnd();
        }
        else
        {
            --tIter;
            SetIterMiddle();
        }

        (*tIter)->Accept(this);
    }

    PopIterContext();
}


void
Visitor::VisitSequenceTypeList(TypeList* typeList)
{
    REQUIRE(typeList != NULL);

    PushIterContext();

    SetIterSize(typeList->size());

    for (TypeList::iterator tIter = typeList->begin();
         tIter != typeList->end();
         tIter++)
    {
        if (tIter == typeList->begin())
        {
            SetIterBegin();
        }
        else if (++tIter == typeList->end())
        {
            --tIter;
            SetIterEnd();
        }
        else
        {
            --tIter;
            SetIterMiddle();
        }

        (*tIter)->Accept(this);
    }

    PopIterContext();
}


void
Visitor::VisitSequenceOfTypeType(Type* type)
{
    REQUIRE(type != NULL);

    type->Accept(this);
}


void 
Visitor::VisitSequenceOfConstraint(Constraint* constraint)
{
    REQUIRE(constraint != NULL);

    constraint->Accept(this);
}


void
Visitor::VisitSetTypeList(TypeList* typeList)
{
    REQUIRE(typeList != NULL);

    PushIterContext();

    SetIterSize(typeList->size());

    for (TypeList::iterator tIter = typeList->begin();
         tIter != typeList->end();
         tIter++)
    {
        if (tIter == typeList->begin())
        {
            SetIterBegin();
        }
        else if (++tIter == typeList->end())
        {
            --tIter;
            SetIterEnd();
        }
        else
        {
            --tIter;
            SetIterMiddle();
        }

        (*tIter)->Accept(this);
    }

    PopIterContext();
}


void
Visitor::VisitSetOfTypeType(Type* type)
{
    REQUIRE(type != NULL);

    type->Accept(this);
}


void 
Visitor::VisitSetOfConstraint(Constraint* constraint)
{
    REQUIRE(constraint != NULL);

    constraint->Accept(this);
}


void 
Visitor::VisitValueDefType(ValueDef* valueDef, Type* type)
{
    REQUIRE(valueDef != NULL);
    REQUIRE(type != NULL);

    type->Accept(this);
}

