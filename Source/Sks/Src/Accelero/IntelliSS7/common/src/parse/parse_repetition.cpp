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
//  ID: $Id: parse_repetition.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_repetition.cpp: Repetition class implementation.   
//
//


#include <parse_repetition.h>
#include <parse_parser.h>
#include <parse_tokenizer.h>
#include <parse_scanner.h>
#include <parse_keyword.h>
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
//  Repetition.
//

Repetition::Repetition(const Repetition& rhs) : Construct(rhs)
{
    commitOnKeywordSeparator    = rhs.commitOnKeywordSeparator;
    commitOnConstructSeparator  = rhs.commitOnConstructSeparator;
    atLeastConstraint           = rhs.atLeastConstraint;
    atMostConstraint            = rhs.atMostConstraint;

    if (rhs.keywordSeparator != NULL)
    {
        keywordSeparator = 
            static_cast<Keyword*>(rhs.keywordSeparator->Clone());
    }
    else
    {
        keywordSeparator = NULL;
    }

    if (rhs.constructSeparator != NULL)
    {
        constructSeparator =
            static_cast<Construct*>(rhs.constructSeparator->Clone());
    }
    else
    {
        constructSeparator = NULL;
    }

    //
    //  No need to clone constructSeparators list.
    //
}


Repetition&
Repetition::operator=(const Repetition& rhs)
{
    if (this == &rhs)
    { 
        return *this;
    }
    else
    {
        static_cast<Construct&>(*this) = rhs;

        commitOnKeywordSeparator    = rhs.commitOnKeywordSeparator;
        commitOnConstructSeparator  = rhs.commitOnConstructSeparator;
        atLeastConstraint           = rhs.atLeastConstraint;
        atMostConstraint            = rhs.atMostConstraint;

        if (keywordSeparator != NULL)
        {
            delete keywordSeparator;
        }

        if (rhs.keywordSeparator != NULL)
        {
            keywordSeparator = 
                static_cast<Keyword*>(rhs.keywordSeparator->Clone());
        }
        else
        {
            keywordSeparator = NULL;
        }

        if (constructSeparator != NULL)
        {
            delete constructSeparator;
        }

        if (rhs.constructSeparator != NULL)
        {
            constructSeparator =
                static_cast<Construct*>(rhs.constructSeparator->Clone());
        }
        else
        {
            constructSeparator = NULL;
        }

        //
        //  No need to clone constructSeparators list.
        //

        return *this;
    }
}


Repetition::~Repetition()
{
    if (keywordSeparator != NULL)
    {
        delete keywordSeparator;
    }

    if (constructSeparator != NULL)
    {
        delete constructSeparator;
    }

    for (ConstructList::const_iterator iter = constructSeparators.begin();
         iter != constructSeparators.end();
         iter++)
    {
        delete (*iter);
    }

    // TODO: double check that there is nothing else to do.
}


void
Repetition::SetKeywordSeparator(const std::string& name)
{
    ITS_REQUIRE(!HasKeywordSeparator());
    ITS_REQUIRE(!HasConstructSeparator());

    //
    // Target only primary parser: if more than one parser object is used then
    // the list of keywords must be initialized explicitly.
    //

    Tokenizer& tokenizer = GetPrimaryParser().GetTokenizer();

    if (!tokenizer.HasKeywordStringValue(name))
    {
        // Add keyword in tokenizer.

        tokenizer.InsertKeyword(name);
    }

    keywordSeparator = new Keyword(GetPrimaryParser(), name);

    ITS_ENSURE(HasKeywordSeparator());
    ITS_ENSURE(!HasConstructSeparator());
}


void
Repetition::SetConstructSeparator(Construct* construct)
{
    ITS_REQUIRE(construct != NULL);
    ITS_REQUIRE(!HasConstructSeparator());
    ITS_REQUIRE(!HasKeywordSeparator());

    constructSeparator = construct;

    ITS_ENSURE(HasConstructSeparator());
    ITS_ENSURE(!HasKeywordSeparator());
}



void
Repetition::InAction(Parser& currentParser)
{
    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        (*iter)->ApplySemanticActions(currentParser);

        MiddleAction(currentParser);
    }
}


void
Repetition::ParseBody(Parser& currentParser)
{
    ITS_ASSERT(
        !HasKeywordSeparator() || 
        (HasKeywordSeparator() && !HasConstructSeparator()));

    ITS_ASSERT(
        !HasConstructSeparator() ||
        (HasConstructSeparator() && !HasKeywordSeparator()));

    Scanner& scanner = currentParser.GetTokenizer().GetScanner();

    bool childFound         = false;
    bool firstChildFound    = false;
    bool separatorFound     = false;
    bool wrong              = false;

    childFound      = ParseOne(currentParser);
    firstChildFound = childFound;

    while(childFound)
    {
        separatorFound  = false;
        childFound      = false;

        if (HasKeywordSeparator())
        {
            Scanner::Position savedPosition = scanner.TellPosition();

            keywordSeparator->Parse(currentParser);

            separatorFound = keywordSeparator->IsParsed();

            if (separatorFound)
            {
                if (commitOnKeywordSeparator)
                {
                    committed = true;
                }
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
                    os << "Parser - Backtracking (separator absent) in ";
                    os << "construct ";
                    os << GetName();
                    os << " (";
                    os << GetTypeName();
                    os << ")...";
                    os << endl;
                }
            }
        }

        if (HasConstructSeparator())
        {
            Scanner::Position savedPosition = scanner.TellPosition();

            Construct* constructSeparatorCloned = constructSeparator->Clone();

            constructSeparatorCloned->Parse(currentParser);

            constructSeparators.push_back(constructSeparatorCloned);

            separatorFound = constructSeparatorCloned->IsParsed();

            if (separatorFound)
            {
                if (commitOnConstructSeparator)
                {
                    committed = true;
                }
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
                    os << "Parser - Backtracking (separator absent) in ";
                    os << "construct ";
                    os << GetName();
                    os << " (";
                    os << GetTypeName();
                    os << ")...";
                    os << endl;
                }
            }
        }

        if (!(HasKeywordSeparator() || HasConstructSeparator()) || 
            separatorFound)
        {
            childFound = ParseOne(currentParser);
        }
    }

    wrong = HasKeywordSeparator() && separatorFound && !childFound;

    completed = firstChildFound && !(committed && wrong);

    // At Least and At Most constraints.

    if (atLeastConstraint > 1)
    {
        if (children.size() < atLeastConstraint)
        {
            syntaxErrorInformation.erase();
            syntaxErrorInformation.reserve(128);

            syntaxErrorInformation.append(
                "At Least constraint violation in <");

            syntaxErrorInformation.append(
                GetName());

            syntaxErrorInformation.append(
                "> | ");
            
            syntaxErrorInformation.append(
                "Number at least expected <");

            char buffer[32];

            memset(buffer, 0, 32);
            sprintf(buffer, "%lu", atLeastConstraint);

            syntaxErrorInformation.append(buffer);

            syntaxErrorInformation.append(
                "> | ");

            syntaxErrorInformation.append(
                "Number found <");

            memset(buffer, 0, 32);
            sprintf(buffer, "%lu", children.size());

            syntaxErrorInformation.append(buffer);

            syntaxErrorInformation.append(
                ">");

            Tokenizer& tokenizer = currentParser.GetTokenizer();
            Scanner& scanner = tokenizer.GetScanner();

            syntaxErrorLineNumber = 
                tokenizer.GetLastInvalidTokenLineNumber();
            syntaxErrorColumnNumber = 
                tokenizer.GetLastInvalidTokenColumnNumber();

            completed = false;
        }
    }

    if (atMostConstraint != (size_t)(-1))
    {
        if (children.size() > atMostConstraint)
        {
            syntaxErrorInformation.erase();
            syntaxErrorInformation.reserve(128);

            syntaxErrorInformation.append(
                "At Most constraint violation in <");

            syntaxErrorInformation.append(
                GetName());

            syntaxErrorInformation.append(
                "> | ");
            
            syntaxErrorInformation.append(
                "Number at most expected <");

            char buffer[32];

            memset(buffer, 0, 32);
            sprintf(buffer, "%lu", atMostConstraint);

            syntaxErrorInformation.append(buffer);

            syntaxErrorInformation.append(
                "> | ");

            syntaxErrorInformation.append(
                "Number found <");

            memset(buffer, 0, 32);
            sprintf(buffer, "%lu", children.size());

            syntaxErrorInformation.append(buffer);

            syntaxErrorInformation.append(
                ">");

            Tokenizer& tokenizer = currentParser.GetTokenizer();
            Scanner& scanner = tokenizer.GetScanner();

            syntaxErrorLineNumber = 
                tokenizer.GetLastInvalidTokenLineNumber();
            syntaxErrorColumnNumber = 
                tokenizer.GetLastInvalidTokenColumnNumber();

            completed = false;
        }
    }
}


bool
Repetition::ParseOne(Parser& currentParser)
{
    bool result         = false;
    bool tmpCommitted   = false;

    Expand();

    ITS_ASSERT(HasCurrentChild());

    Scanner& scanner = currentParser.GetTokenizer().GetScanner();

    Scanner::Position savedPosition = scanner.TellPosition();

    if (HasKeywordSeparator() || HasConstructSeparator())
    {
        currentChild->Parse(currentParser);
    }
    else
    {
        tmpCommitted = committed;
        committed = false;
        currentChild->Parse(currentParser);
        committed = committed || tmpCommitted;
    }

    result = currentChild->IsParsed();

    if (!currentChild->IsParsed())
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
            os << "Parser - Backtracking (specimen absent) in ";
            os << "construct ";
            os << GetName();
            os << " (";
            os << GetTypeName();
            os << ")...";
            os << endl;
        }

        ITS_ASSERT(children.size() >= 1);

        Construct* construct = children.back();

        delete construct;

        children.pop_back();
    }

    return result;
}


void
Repetition::Expand()
{
    //
    //  Should be equal to one only. Others are ignored.
    //

    ITS_ASSERT(GetProduction().GetSize() >= 1);

    ConstructList::const_iterator iter = 
        GetProduction().
            GetConstructList().
                begin();

    ITS_ASSERT(iter != GetProduction().GetConstructList().end());

    Construct* construct = (*iter)->Clone();

    construct->SetParent(this);

    children.push_back(construct);

    currentChild = construct;

    ITS_ENSURE(children.size() >= 1);
}


string
Repetition::GetValue() const
{
    string result = "";
    
    ConstructList::const_iterator separatorIter = constructSeparators.begin();

    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        Construct* child = *iter;

        result.append(child->GetValue());

        bool lastChild = false;

        if (++iter == children.end())
        {
            --iter;

            lastChild = true;
        }
        else
        {
            --iter;
        }

        if (!lastChild)
        {
            // Add separator if any.

            if (HasKeywordSeparator())
            {
                result.append(keywordSeparator->GetValue());
            }

            if (HasConstructSeparator())
            {
                if (separatorIter != constructSeparators.end())
                {
                    result.append((*separatorIter)->GetValue());

                    separatorIter++;
                }
                else
                {
                    //  Nothing to do (no separator added).
                }
            }
        }
    }

    return result;
}


void
Repetition::Print(ostream& os, size_t level) const
{
    string levelShift = ParseUtilStringFourSpaces(level);

    os << levelShift;

    os << GetName();
    os << " (";
    os << "Repetition";

    if (IsOptional())
    {
        os << " | optional";
    }

    if (IsTopLevel())
    {
        os << " | top level";
    }

    if (HasAtLeastConstraint())
    {
        os << " | at least <";
        os << GetAtLeastConstraint();
        os << ">";
    }

    if (HasAtMostConstraint())
    {
        os << " | at most <";
        os << GetAtMostConstraint();
        os << ">";
    }

    os << ")" << endl;

    os << levelShift;

    os << "<" << endl;

    bool first = true;

    //
    //  Used only if separator is a construct (and not a keyword).
    //

    ConstructList::const_iterator separatorIter = constructSeparators.begin();


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

        // Is last child?

        bool lastChild = false;

        if (++iter == children.end())
        {
            lastChild = true;

            --iter;

        }
        else
        {
            --iter;
        }

        if (!lastChild)
        {
            // Add separator if any.

            if (HasKeywordSeparator())
            {
                os << endl;

                keywordSeparator->Print(os, level + 1);
            }

            if (HasConstructSeparator())
            {
                os << endl;

                if (separatorIter != constructSeparators.end())
                {
                    (*separatorIter)->Print(os, level + 1);

                    separatorIter++;
                }
                else
                {
                    os << levelShift; 

                    os << "    (Construct separator) ";

                    os << constructSeparator->GetName();

                    os << " <SEPARATOR>";
                }

                os << endl;
            }
        }
    }

    os << levelShift;

    os << ">" << endl;
}


void
Repetition::PrintValue(ostream& os) const
{
    //
    //  Used only if separator is a construct (and not a keyword).
    //

    ConstructList::const_iterator separatorIter = constructSeparators.begin();


    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        Construct* child = *iter;

        child->PrintValue(os);

        bool lastChild = false;

        if (++iter == children.end())
        {
            --iter;

            lastChild = true;
        }
        else
        {
            --iter;
        }

        if (!lastChild)
        {
            // Add separator if any.

            if (HasKeywordSeparator())
            {
                keywordSeparator->PrintValue(os);
            }

            if (HasConstructSeparator())
            {
                if (separatorIter != constructSeparators.end())
                {
                    (*separatorIter)->PrintValue(os);

                    separatorIter++;
                }
                else
                {
                    os << " <SEPARATOR> ";
                }
            }
        }
    }
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)




