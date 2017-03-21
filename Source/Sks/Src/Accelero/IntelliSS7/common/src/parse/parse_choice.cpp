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
//  ID: $Id: parse_choice.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_choice.cpp: Choice class implementation.   
//
//


#include <parse_choice.h>
#include <parse_parser.h>
#include <parse_tokenizer.h>
#include <parse_scanner.h>
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
//  Choice.
//

Choice::Choice(const Choice& rhs) : Construct(rhs)
{
    if (rhs.retained != NULL)
    {
        retained = rhs.retained->Clone();
    }
    else
    {
        retained = NULL;
    }
}


Choice&
Choice::operator=(const Choice& rhs)
{
    if (this == &rhs)
    { 
        return *this;
    }
    else
    {
        static_cast<Construct&>(*this) = rhs;

        if (rhs.retained != NULL)
        {
            retained = rhs.retained->Clone();
        }
        else
        {
            retained = NULL;
        }

        return *this;
    }
}


void
Choice::InAction(Parser& currentParser)
{
    if (retained != NULL)
    {
        retained->ApplySemanticActions(currentParser);
    }
}


void
Choice::ParseBody(Parser& currentParser)
{
    ITS_REQUIRE(GetChildrenSize() == 0);

    Scanner& scanner = currentParser.GetTokenizer().GetScanner();

    Scanner::Position savedPosition = scanner.TellPosition();

    Expand();

    while (!HasRetained() && HasCurrentChild())
    {
        ParseCurrentChild(currentParser);

        if (currentChild->IsParsed())
        {
            retained = &GetCurrentChild();
        }
        else if (currentChild->IsCommitted())
        {
            retained = &GetCurrentChild();
        }
        else
        {
            scanner.SeekPosition(savedPosition);

            if (currentParser.IsDebugOn() && 
                currentParser.HasOutputStreamForDebug())
            {
                ostream& os = currentParser.GetOutputStreamForDebug();

                string parseLevelShift =
                    ParseUtilStringSpaces(
                        2 * currentParser.GetParseLevel());

                os << parseLevelShift;
                os << "Parser - Backtracking in construct ";
                os << GetName();
                os << " (";
                os << GetTypeName();
                os << ")...";
                os << endl;
            }
        }

        if (!HasRetained())
        {
            Expand();
        }
    }

    if (HasRetained())
    {
        parsed = retained->IsParsed();

        completed = retained->IsCompleted();

        committed = retained->IsCommitted();
    }
    else
    {
        completed = false;
    }

    //
    // A choice once parsed is not used as a tree node. It has only one child
    // accessed through retained.
    //

    for (ConstructList::const_iterator iter = children.begin();
        iter != children.end();
        iter++)
    {
        // Delete all children except the retained child.

        if (*iter != retained)
        {
            delete (*iter);
        }
    }

    children.erase(children.begin(), children.end());
}


void
Choice::Expand()
{
    ExpandNext();
}


string
Choice::GetValue() const
{
    string result = "";

    if (HasRetained())
    {
        result.append(retained->GetValue());
    }

    return result;
}


void
Choice::Print(ostream& os, size_t level) const
{
    string levelShift = ParseUtilStringFourSpaces(level);

    os << levelShift;

    os << GetName();
    os << " (";
    os << "Choice";

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

    if (HasRetained())
    {
        retained->Print(os, level + 1);
    }

    os << levelShift;

    os << ">" << endl;
}


void
Choice::PrintValue(ostream& os) const
{
    if (HasRetained())
    {
        retained->PrintValue(os);
    }
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)
