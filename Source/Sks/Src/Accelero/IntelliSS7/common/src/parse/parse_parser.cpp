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
//  ID: $Id: parse_parser.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_parser.cpp: Parser class implementation.   
//
//


#include <parse_parser.h>
#include <parse_tokenizer.h>
#include <parse_scanner.h>
#include <parse_construct.h>
#include <parse_exception.h>

#if defined(ITS_STD_STRING_STREAM_PRESENT)
#include <sstream>
#else // !defined(ITS_STD_STRING_STREAM_PRESENT)
#include <strstream>
#endif // defined(ITS_STD_STRING_STREAM_PRESENT)


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Parser.
//

Parser::~Parser()
{
    if (tokenizer != NULL)
    {
        delete tokenizer;
    }

    if (scanner != NULL)
    {
        delete scanner;
    }

    if (inputStream != NULL)
    {
        delete inputStream;
    }

    if (topLevelConstruct != NULL)
    {
        delete topLevelConstruct;
    }
}


void 
Parser::ReinitializeStringToParse(
            const std::string& stringToParseParam)
{
    ITS_REQUIRE(ParseFromString());
    ITS_REQUIRE(HasTokenizer());
    ITS_REQUIRE(HasScanner());
    ITS_REQUIRE(HasInputStream());

    stringToParse = stringToParseParam;

    delete inputStream;

    // [1] Create input stream from string.

#if defined(ITS_STD_STRING_STREAM_PRESENT)

    inputStream = new istringstream(stringToParse);

#else // !defined(ITS_STD_STRING_STREAM_PRESENT)

    inputStream = new istrstream(stringToParse.c_str());

#endif // defined(ITS_STD_STRING_STREAM_PRESENT)


    // [2] Reinitialize input stream in scanner.

    scanner->Reinitialize(*inputStream);
}


void 
Parser::ReinitializeFileToParse(
            const std::string& fileNameToParseParam,
            const std::string& filePathToParseParam)
{
    ITS_REQUIRE(ParseFromFile());
    ITS_REQUIRE(HasTokenizer());
    ITS_REQUIRE(HasScanner());
    ITS_REQUIRE(HasInputStream());

    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}


void 
Parser::ReinitializeInputStreamToParse(
            std::istream& inputStreamToParseParam)
{
    ITS_REQUIRE(ParseFromInputStream());
    ITS_REQUIRE(HasTokenizer());
    ITS_REQUIRE(HasScanner());
    ITS_REQUIRE(HasInputStream());

    inputStreamToParse = &inputStreamToParseParam;

    delete inputStream;

    // [1] Create input stream from input stream.

#if defined(WIN32)        

        //  Not available with VS.NET (okay with VC++ 6.0).

        //  inputStream = new istream(*inputStreamToParse);

        bool not_implemented = false;
        ITS_ASSERT(not_implemented);
        
#else // !defined(WIN32)

        bool not_implemented = false;
        ITS_ASSERT(not_implemented);
        
#endif // defined(WIN32)

    // [2] Reinitialize input stream in scanner.

    scanner->Reinitialize(*inputStream);
}


void
Parser::InitializeTokenizer()
{
    ITS_REQUIRE(!HasInputStream());
    ITS_REQUIRE(!HasScanner());
    ITS_REQUIRE(!HasTokenizer());

    if (parseFromString)
    {
        // [1] Create input stream from string.

#if defined(ITS_STD_STRING_STREAM_PRESENT)

        inputStream = new istringstream(stringToParse);

#else // !defined(ITS_STD_STRING_STREAM_PRESENT)

        inputStream = new istrstream(stringToParse.c_str());

#endif // defined(ITS_STD_STRING_STREAM_PRESENT)

        
        // [2] Create scanner from input stream.

        scanner = new Scanner(*inputStream);


        // [3] Create tokenizer from scanner.

        tokenizer = new Tokenizer(*scanner);
    }
    else if (parseFromFile)
    {
        bool not_implemented = false;
        ITS_ASSERT(not_implemented);
    }
    else if (parseFromInputStream)
    {
        // [1] Create input stream from input stream.
        
#if defined(WIN32)

        //  Not available with VS.NET (okay with VC++ 6.0).

        //  inputStream = new istream(*inputStreamToParse);

        bool not_implemented = false;
        ITS_ASSERT(not_implemented);
        
#else // !defined(WIN32)

        bool not_implemented = false;
        ITS_ASSERT(not_implemented);
        
#endif // defined(WIN32)

        // [2] Create scanner from input stream.

        scanner = new Scanner(*inputStream);

        // [3] Create tokenizer from scanner.

        tokenizer = new Tokenizer(*scanner);
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    ITS_ENSURE(HasInputStream());
    ITS_ENSURE(HasScanner());
    ITS_ENSURE(HasTokenizer());
}


void
Parser::TerminateTokenizer()
{
    if (inputStream != NULL)
    {
        delete inputStream;

        inputStream = NULL;
    }

    if (scanner != NULL)
    {
        delete scanner;

        scanner = NULL;
    }

    if (tokenizer != NULL)
    {
        delete tokenizer; 

        tokenizer = NULL;
    }

    ITS_ENSURE(!HasInputStream());
    ITS_ENSURE(!HasScanner());
    ITS_ENSURE(!HasTokenizer());
}


void
Parser::ForceDestructTopLevelConstruct()
{
    delete topLevelConstruct;

    topLevelConstruct = NULL;
}


void
Parser::Parse()
{
    ITS_REQUIRE(HasInputStream());
    ITS_REQUIRE(HasScanner());
    ITS_REQUIRE(HasTokenizer());

    if (topLevelConstruct != NULL)
    {
        delete topLevelConstruct;

        topLevelConstruct = NULL;
    }

    inputParsed = false; // Reset.

    inputPartiallyParsed = false; // Reset.

    topLevelConstruct = MakeTopLevelConstruct();

    topLevelConstruct->Process(*this); // Parse and apply semantic actions.

    inputParsed = topLevelConstruct->IsParsed();

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Analyse if input has been only partially parsed.
    //

    if (!inputParsed)
    {
        inputPartiallyParsed = false;
    }
    else
    {
        //
        //  Attempt to read one more character to determine if EOF.
        //

        Scanner& scanner = GetScanner();

        char c = '\0';

        PrsResult result = scanner.GetChar(c);

        if (result != PARSE_ERROR_STREAM_EOF)
        {
            inputPartiallyParsed = true;
        }
        else
        {
            inputPartiallyParsed = false;
        }
    }

    //
    ////////////////////////////////////////////////////////////////////////////



    if (!inputParsed)
    {
        ITS_ASSERT(topLevelConstruct->HasSyntaxErrorInformation());

        syntaxErrorInformation = 
            topLevelConstruct->GetLastSyntaxErrorInformation();

        syntaxErrorLineNumber = 
            topLevelConstruct->GetLastSyntaxErrorLineNumber();

        syntaxErrorColumnNumber = 
            topLevelConstruct->GetLastSyntaxErrorColumnNumber();
    }
    else if (inputPartiallyParsed)
    {
        Tokenizer& tokenizer = GetTokenizer();

        syntaxErrorInformation.erase();

        syntaxErrorInformation.append(
            "Partially parsed until <");

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
        // Nothing to do.
    }

    if (!inputParsed && throwParseSyntaxError)
    {
        PARSE_THROW_SYNTAX_ERROR(
            syntaxErrorInformation, 
            syntaxErrorLineNumber,
            syntaxErrorColumnNumber);
    }
}


void
Parser::PrintParsedTree(ostream& os) const
{
    ITS_REQUIRE(IsInputParsed());
    ITS_REQUIRE(HasTopLevelConstruct());

    topLevelConstruct->Print(os);
}


void
Parser::PrintParsedInput(ostream& os) const
{
    ITS_REQUIRE(IsInputParsed());
    ITS_REQUIRE(HasTopLevelConstruct());

    topLevelConstruct->PrintValue(os);
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)



