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
//  ID: $Id: parse_construct.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_construct.h: Construct class implemenation.
//
//


#include <parse_construct.h>
#include <parse_keyword.h>
#include <parse_parser.h>
#include <parse_tokenizer.h>
#include <parse_scanner.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)



////////////////////////////////////////////////////////////////////////////////
//
//  Construct.
//

Construct::Construct(const Construct& rhs)
{
    primaryParser           = rhs.primaryParser;
    parent                  = rhs.parent;
    optional                = rhs.optional;
    parsed                  = rhs.parsed;
    completed               = rhs.completed;
    committed               = rhs.committed;
    topLevel                = rhs.topLevel;
    currentChild            = rhs.currentChild;
    syntaxErrorInformation  = rhs.syntaxErrorInformation;
    syntaxErrorLineNumber   = rhs.syntaxErrorLineNumber;
    syntaxErrorColumnNumber = rhs.syntaxErrorColumnNumber;

    for (ConstructList::const_iterator iterRhs = rhs.children.begin();
         iterRhs != rhs.children.end();
         iterRhs++)
    {
        children.push_back((*iterRhs)->Clone());
    }
}


Construct&
Construct::operator=(const Construct& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        primaryParser           = rhs.primaryParser;
        parent                  = rhs.parent;
        optional                = rhs.optional;
        parsed                  = rhs.parsed;
        completed               = rhs.completed;
        committed               = rhs.committed;
        topLevel                = rhs.topLevel;
        currentChild            = rhs.currentChild;
        syntaxErrorInformation  = rhs.syntaxErrorInformation;
        syntaxErrorLineNumber   = rhs.syntaxErrorLineNumber;
        syntaxErrorColumnNumber = rhs.syntaxErrorColumnNumber;

        for (ConstructList::const_iterator iter = children.begin();
            iter != children.end();
            iter++)
        {
            delete (*iter);
        }

        children.erase(children.begin(), children.end());

        for (ConstructList::const_iterator iterRhs = rhs.children.begin();
             iterRhs != rhs.children.end();
             iterRhs++)
        {
            children.push_back((*iterRhs)->Clone());
        }
        
        return *this;
    }
}


Construct::~Construct()
{
    for (ConstructList::const_iterator iter = children.begin();
         iter != children.end();
         iter++)
    {
        delete (*iter);
    }
}


string
Construct::GetTypeName() const
{
    switch (GetType())
    {
    case CONSTRUCT_TYPE_KEYWORD:
        return "Keyword";

    case CONSTRUCT_TYPE_TERMINAL:
        return "Terminal";

    case CONSTRUCT_TYPE_AGGREGATE:
        return "Aggregate";

    case CONSTRUCT_TYPE_CHOICE:
        return "Choice";

    case CONSTRUCT_TYPE_REPETITION:
        return "Repetition";

    default:
        return "Unknown";
    }
}


void
Construct::Process(Parser& currentParser)
{
    Parse(currentParser);

    if (parsed)
    {
        ApplySemanticActions(currentParser);
    }

    if (!parsed && topLevel)
    {
        if (!HasSyntaxErrorInformation())
        {
            Tokenizer& tokenizer = currentParser.GetTokenizer();
            Scanner& scanner = tokenizer.GetScanner();

            syntaxErrorInformation.erase();
            syntaxErrorInformation.reserve(128);

            syntaxErrorInformation.append("\nExpected: <");
            syntaxErrorInformation.append(currentChild->GetName());
            syntaxErrorInformation.append(">\n");
            syntaxErrorInformation.append("\nFound: <");
            syntaxErrorInformation.append(tokenizer.GetLastInvalidTokenStringValue());
            syntaxErrorInformation.append(">\n");

            syntaxErrorLineNumber = tokenizer.GetLastInvalidTokenLineNumber();
            syntaxErrorColumnNumber = tokenizer.GetLastInvalidTokenColumnNumber();
        }
    }
}


void 
Construct::Parse(Parser& currentParser)
{    
    Scanner& scanner = currentParser.GetTokenizer().GetScanner();

    Scanner::Position savedPosition = scanner.TellPosition();

    parsed      = false;
    completed   = false;
    committed   = false;

    if (topLevel)
    {
        committed = true; // TODO: double check that point.
    }

    if (currentParser.IsDebugOn() && currentParser.HasOutputStreamForDebug())
    {
        ostream& os = currentParser.GetOutputStreamForDebug();

        string parseLevelShift =
            ParseUtilStringSpaces(
                2 * currentParser.GetParseLevel());

        if (IsTopLevel())
        {
            os << endl;
        }

        os << parseLevelShift; 
        os << "Parser - Attempt to parse construct ";
        os << GetName();
        os << " (";
        os << GetTypeName();
        os << ")...";
        os << endl;

        currentParser.IncrementParseLevel();
    }

    ParseBody(currentParser);

    if (!completed && IsOptional())
    {
        scanner.SeekPosition(savedPosition); 

        parsed = !committed;

        if (currentParser.IsDebugOn() && 
            currentParser.HasOutputStreamForDebug())
        {
            ostream& os = currentParser.GetOutputStreamForDebug();

            string parseLevelShift =
                ParseUtilStringSpaces(
                    2 * currentParser.GetParseLevel());

            os << parseLevelShift;
            os << "Parser - Backtracking (optional absent) in construct ";
            os << GetName();
            os << " (";
            os << GetTypeName();
            os << ")...";
            os << endl;
        }
    }
    else
    {
        parsed = completed;
    }

    if (currentParser.IsDebugOn() && currentParser.HasOutputStreamForDebug())
    {
        currentParser.DecrementParseLevel();

        ostream& os = currentParser.GetOutputStreamForDebug();

        string parseLevelShift =
            ParseUtilStringSpaces(
                2 * currentParser.GetParseLevel());

        if (completed)
        {
            os << parseLevelShift; 
            os << "Parser - Parse construct ";
            os << GetName();
            os << " succeeded.";
            os << endl;
        }
        else
        {
            os << parseLevelShift; 
            os << "Parser - Parse construct ";
            os << GetName();
            os << " failed.";
            os << endl;
        }
    }
}   


void 
Construct::AddConstruct(Construct* construct)
{
    ITS_REQUIRE(construct != NULL);

    GetProduction().GetConstructList().push_back(construct);
}


void 
Construct::AddKeyword(const std::string& name)
{
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

    Keyword* keyword = new Keyword(GetPrimaryParser(), name);

    AddConstruct(keyword);
}


void 
Construct::AddOptionalKeyword(const std::string& name)
{
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

    Keyword* keyword = new Keyword(GetPrimaryParser(), name);

    keyword->SetOptional();

    AddConstruct(keyword);
}


void
Construct::ExpandNext()
{
    if (GetProduction().GetSize() > GetChildrenSize())
    {
        ConstructList::const_iterator iter = 
            GetProduction().
                GetConstructList().
                    begin();

        size_t childrenSize = GetChildrenSize();

        size_t index = 0;

        while   (index < childrenSize)
        {
            iter++;
            index++;
        }

        ITS_ASSERT(iter != GetProduction().GetConstructList().end());

        Construct* construct = (*iter)->Clone();

        construct->SetParent(this);

        children.push_back(construct);

        currentChild = construct;

        ITS_ENSURE(children.size() >= 1);
    }
    else
    {
        currentChild = NULL;
    }
}


void
Construct::ParseCurrentChild(Parser& currentParser)
{
    ITS_REQUIRE(HasCurrentChild());

    currentChild->Parse(currentParser);

    if (currentChild->IsCommitted())
    {
        committed = true;
    }

    if (committed && !(currentChild->IsParsed() || currentChild->IsCommitted()))
    {
        Tokenizer& tokenizer = currentParser.GetTokenizer();
        Scanner& scanner = tokenizer.GetScanner();

        if (!currentChild->HasSyntaxErrorInformation())
        {
            syntaxErrorInformation.erase();
            syntaxErrorInformation.reserve(128);

            syntaxErrorInformation.append(
                "Expected <");

            syntaxErrorInformation.append(
                currentChild->GetName());

            syntaxErrorInformation.append(
                "> | ");

            syntaxErrorInformation.append(
                "Found <");

            syntaxErrorInformation.append(
                tokenizer.GetLastInvalidTokenStringValue());

            syntaxErrorInformation.append(
                ">");

            syntaxErrorLineNumber = 
                tokenizer.GetLastInvalidTokenLineNumber();
            syntaxErrorColumnNumber = 
                tokenizer.GetLastInvalidTokenColumnNumber();
        }
        else
        {
            syntaxErrorInformation = 
                currentChild->GetLastSyntaxErrorInformation();

            syntaxErrorLineNumber =
                currentChild->GetLastSyntaxErrorLineNumber();

            syntaxErrorColumnNumber =
                currentChild->GetLastSyntaxErrorColumnNumber();
        }
    }
    else
    {
        if (currentChild->HasSyntaxErrorInformation())
        {
            syntaxErrorInformation = 
                currentChild->GetLastSyntaxErrorInformation();

            syntaxErrorLineNumber =
                currentChild->GetLastSyntaxErrorLineNumber();

            syntaxErrorColumnNumber =
                currentChild->GetLastSyntaxErrorColumnNumber();
        }
    }
}


////////////////////////////////////////////////////////////
//
//  Construct ostream operator<< implementation.
//

ostream& 
operator<< (ostream& os, const Construct& construct)
{
    construct.Print(os);
    return os;
}



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)
