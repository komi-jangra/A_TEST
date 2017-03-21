////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: parse_aggregate.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_aggregate.cpp: Aggregate class implementation.   
//
//


#include <parse_aggregate.h>
#include <parse_utilities.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)



////////////////////////////////////////////////////////////////////////////////
//
//  Aggregate.
//

Aggregate::Aggregate(const Aggregate& rhs) : Construct(rhs)
{
    commitThreshold     = rhs.commitThreshold;
    commitAlreadyCalled = rhs.commitAlreadyCalled;
}


Aggregate&
Aggregate::operator=(const Aggregate& rhs)
{
    if (this == &rhs)
    { 
        return *this;
    }
    else
    {
        static_cast<Construct&>(*this) = rhs;

        commitThreshold     = rhs.commitThreshold;
        commitAlreadyCalled = rhs.commitAlreadyCalled;

        return *this;
    }
}


void
Aggregate::Commit()
{
    ITS_REQUIRE(!HasCommitAlreadyBeenCalled());

    commitAlreadyCalled = true;

    ITS_ASSERT(GetProduction().GetSize() >= 1);

    commitThreshold = GetProduction().GetSize();
}


void
Aggregate::InAction(Parser& currentParser)
{
    for (ConstructList::iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        Construct* child = *iter;

        child->ApplySemanticActions(currentParser);
    }
}


void
Aggregate::ParseBody(Parser& currentParser)
{
    ITS_REQUIRE(GetChildrenSize() == 0);

    Expand();

    bool wrong = false;

    while (!wrong && HasCurrentChild())
    {
        ParseCurrentChild(currentParser);

        wrong = !(currentChild->IsParsed());

        if (!wrong)
        {
            Expand();
        }
    }

    completed = !wrong;

    //
    // Remove optional(s) that are not present (i.e. not completed).
    //

    ConstructList::iterator iter = children.begin();

    while (iter != children.end())
    {
        Construct* child = *iter;

        if (child->IsOptional() && child->IsParsed() && !(child->IsCompleted()))
        {
            iter = children.erase(iter); 

            //
            // Iterator iter designates next element or end if no such element.
            //

            delete child;
        }
        else
        {
            iter++;
        }
    }
}


void
Aggregate::Expand()
{
    ExpandNext();

    if (commitAlreadyCalled && (commitThreshold < GetChildrenSize()))
    {
        committed = true;
    }
}


string
Aggregate::GetValue() const
{
    string result = "";

    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        Construct* child = *iter;

        result.append(child->GetValue());
    }

    return result;
}


void
Aggregate::Print(ostream& os, size_t level) const
{
    string levelShift = ParseUtilStringFourSpaces(level);

    os << levelShift;

    os << GetName();
    os << " (";
    os << "Aggregate";
    
    if (IsOptional())
    {
        os << " | optional";
    }

    if (IsTopLevel())
    {
        os << " | top level";
    }

    os << ")" << endl;

    os << levelShift;

    os << "<" << endl;

    bool first = true;

    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        if (!first)
        {
            os << endl;
        }
        else
        { 
            first = false;
        }

        Construct* child = *iter;

        child->Print(os, level + 1);
    }

    os << levelShift;

    os << ">" << endl;
}


void 
Aggregate::PrintValue(ostream& os) const
{
    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        Construct* child = *iter;

        child->PrintValue(os);
    }
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


