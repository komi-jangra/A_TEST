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
//  ID: $Id: parse_parser.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_parser.h: Parser class interface.   
//
//


#if !defined(_PARSE_PARSER_H_)
#define _PARSE_PARSER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <parse.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

class Tokenizer;
class Scanner;
class Construct;
class SemanticActionsVisitor;


////////////////////////////////////////////////////////////////////////////////
//
//  Parser. Abstract class. Heirs need to redefine member function that returns
//  top construct of grammar (MakeTopLevelConstruct).
//


class Parser 
{
public:

    //
    // Default constructor.
    //

    Parser()
    :   parseFromString(false),
        parseFromFile(false),
        parseFromInputStream(false),
        inputStreamToParse(NULL),
        tokenizer(NULL),
        scanner(NULL),
        inputStream(NULL),
        topLevelConstruct(NULL),
        inputParsed(false),
        inputPartiallyParsed(false),
        throwParseSyntaxError(false),
        syntaxErrorLineNumber(0),
        syntaxErrorColumnNumber(0),
        debugOn(false),
        outputStreamForDebug(NULL),
        parseLevel(0)
    {}


    //
    //  Parse from a string.
    //

    Parser(
        const std::string& stringToParseParam) 
    :   parseFromString(true),
        parseFromFile(false),
        parseFromInputStream(false),
        stringToParse(stringToParseParam),
        inputStreamToParse(NULL),
        tokenizer(NULL),
        scanner(NULL),
        inputStream(NULL),
        topLevelConstruct(NULL),
        inputParsed(false),
        inputPartiallyParsed(false),
        throwParseSyntaxError(false),
        syntaxErrorLineNumber(0),
        syntaxErrorColumnNumber(0),
        debugOn(false),
        outputStreamForDebug(NULL),
        parseLevel(0),
        semanticActionsVisitor(NULL)
    {}


    //
    //  Parse from a file.
    //  

    Parser(
        const std::string& fileNameToParseParam, 
        const std::string& filePathToParseParam)
    :   parseFromString(false),
        parseFromFile(true),
        parseFromInputStream(false),
        fileNameToParse(fileNameToParseParam),
        filePathToParse(filePathToParseParam),
        inputStreamToParse(NULL),
        tokenizer(NULL),
        scanner(NULL),
        inputStream(NULL),
        topLevelConstruct(NULL),
        inputParsed(false),
        inputPartiallyParsed(false),
        throwParseSyntaxError(false),
        syntaxErrorLineNumber(0),
        syntaxErrorColumnNumber(0),
        debugOn(false),
        outputStreamForDebug(NULL),
        parseLevel(0),
        semanticActionsVisitor(NULL)
    {}


    //
    //  Parse from an input stream.
    //

    Parser(
        std::istream& inputStreamToParseParam)
    :   parseFromString(false),
        parseFromFile(false),
        parseFromInputStream(true),
        inputStreamToParse(&inputStreamToParseParam),
        tokenizer(NULL),
        scanner(NULL),
        inputStream(NULL),
        topLevelConstruct(NULL),
        inputParsed(false),
        inputPartiallyParsed(false),
        throwParseSyntaxError(false),
        syntaxErrorLineNumber(0),
        syntaxErrorColumnNumber(0),
        debugOn(false),
        outputStreamForDebug(NULL),
        parseLevel(0),
        semanticActionsVisitor(NULL)
    {}

    // Default copy constructor not ok (see protected section).

    // Default assignment operator not ok (see protected section).

    virtual ~Parser();
   
    bool 
    ParseFromString() const
    { return parseFromString; }

    bool
    ParseFromFile() const
    { return parseFromFile; }

    bool
    ParseFromInputStream() const
    { return parseFromInputStream; }

    bool
    HasInputStreamToParse() const
    { return inputStreamToParse != NULL; }

    void
    SetStringToParse(
                const std::string& stringToParseParam)
    {
        parseFromString         = true;
        parseFromFile           = false;
        parseFromInputStream    = false;

        stringToParse = stringToParseParam;
    }

    void
    SetFileToParse(
                const std::string& fileNameToParseParam,
                const std::string& filePathToParseParam)
    {
        parseFromString         = false;
        parseFromFile           = true;
        parseFromInputStream    = false;

        fileNameToParse = fileNameToParseParam;
        filePathToParse = filePathToParseParam;
    }

    void
    SetInputStreamToParse(
                std::istream& inputStreamToParseParam)
    {
        parseFromString         = false;
        parseFromFile           = false;
        parseFromInputStream    = true;

        inputStreamToParse = &inputStreamToParseParam;
    }


    void ReinitializeStringToParse(
                const std::string& stringToParseParam);

    void ReinitializeFileToParse(
                const std::string& fileNameToParseParam,
                const std::string& filePathToParseParam);

    void ReinitializeInputStreamToParse(
                std::istream& inputStreamToParseParam);

    bool
    HasTokenizer() const
    { return tokenizer != NULL; }

    Tokenizer&
    GetTokenizer() const
    {
        ITS_REQUIRE(HasTokenizer());

        return *tokenizer;
    }

    bool
    HasScanner () const
    { return scanner != NULL; }

    Scanner&
    GetScanner() const
    {
        ITS_REQUIRE(HasScanner());

        return *scanner;
    }

    bool
    HasInputStream() const
    { return inputStream != NULL; }

    std::istream&
    GetInputStream() const
    {
        ITS_REQUIRE(HasInputStream());

        return *inputStream;
    }


    //
    //  Must be redefined in heirs if more than one parser object is used (e.g. 
    //  multi-threaded application). In this case, InitializeTokenizer must also
    //  define all the keywords of the grammar, using InsertKeyword member
    //  function of class Tokenizer.
    //

    virtual void InitializeTokenizer();

    virtual void TerminateTokenizer();


    //
    //  Has top level construct (and therefore parsed tree)?
    //

    bool
    HasTopLevelConstruct() const
    { return topLevelConstruct != NULL; }


    //
    //  Access to top level construct (and therefore parsed tree). Created by
    //  Parse member function.
    //

    Construct&
    GetTopLevelConstruct() const
    {
        ITS_REQUIRE(HasTopLevelConstruct());

        return *topLevelConstruct;
    }


    //
    //  Force destruct of top level construct (and therefore parsed tree).
    //

    void ForceDestructTopLevelConstruct();


    //
    //  Return an instance of top level construct of grammar. MUST be redefined
    //  by heirs. Called by Parse member function. (instance of top level 
    //  construct is deleted by explicit call to ForceDestructTopLevelConstruct,
    //  destructor or next call to Parse.
    //
    
    virtual Construct* MakeTopLevelConstruct() = 0;


    //
    //  Parse input and apply semantic actions. May throw exception 
    //  ParseSyntaxError according to setting.
    //

    virtual void Parse();


    //
    //  Has input been successfully parsed?
    //

    bool
    IsInputParsed() const
    { return inputParsed; }


    //
    //  Has input been successfully partially parsed?
    //

    bool
    IsInputPartiallyParsed() const
    { return inputPartiallyParsed; }


    //
    //  Has syntax error information?
    //

    bool
    HasSyntaxErrorInformation() const
    { return !syntaxErrorInformation.empty(); }


    //
    //  Last syntax error information.
    //

    const std::string& 
    GetLastSyntaxErrorInformation() const
    {
        ITS_REQUIRE(!IsInputParsed() || IsInputPartiallyParsed());
        ITS_REQUIRE(HasSyntaxErrorInformation());

        return syntaxErrorInformation;
    }


    //
    //  Last syntax error line number.
    //

    size_t
    GetLastSyntaxErrorLineNumber() const
    {
        ITS_REQUIRE(!IsInputParsed() || IsInputPartiallyParsed());

        return syntaxErrorLineNumber;
    }


    //
    //  Last syntax error column number.
    //

    size_t
    GetLastSyntaxErrorColumnNumber() const
    {
        ITS_REQUIRE(!IsInputParsed() || IsInputPartiallyParsed());

        return syntaxErrorColumnNumber;
    }

    
    //
    //  Set throw ParseSyntaxError exception (not set by default).
    //

    void
    SetThrowParseSyntaxError()
    { throwParseSyntaxError = true; }


    //
    //  Unset throw ParseSyntaxError exception (not set by default).
    //

    void
    UnsetThrowParseSyntaxError()
    { throwParseSyntaxError = false; }


    ////////////////////////////////////////////////////////
    //
    //  Semantic actions visitor.
    //

    void
    SetSemanticActionsVisitor(
        SemanticActionsVisitor* 
            semanticActionsVisitorParam)
    {
        ITS_REQUIRE(semanticActionsVisitorParam != NULL);

        semanticActionsVisitor = semanticActionsVisitorParam;
    }


    SemanticActionsVisitor*
    GetSemanticActionsVisitor()
    {
        ITS_REQUIRE(HasSemanticActionsVisitor());

        return semanticActionsVisitor;
    }


    bool
    HasSemanticActionsVisitor() const
    { return semanticActionsVisitor != NULL; }


    ////////////////////////////////////////////////////////
    //
    //  Printing.
    //

    virtual void PrintParsedTree(std::ostream& os) const;

    virtual void PrintParsedInput(std::ostream& os) const;


    ////////////////////////////////////////////////////////
    //
    //  Debugging.
    //

    void
    SetDebugOn()
    { debugOn = true; }

    void
    SetDebugOff()
    { debugOn = false; }

    bool
    IsDebugOn() const
    { return debugOn; }

    void
    SetOutputStreamForDebug(
                std::ostream& outputStreamForDebugParam)
    { 
        outputStreamForDebug = &outputStreamForDebugParam; 
    }

    std::ostream&
    GetOutputStreamForDebug() const
    { 
        ITS_REQUIRE(HasOutputStreamForDebug());

        return *outputStreamForDebug;
    }

    bool
    HasOutputStreamForDebug() const
    { return outputStreamForDebug != NULL; }

    void
    SetParseLevel(size_t parseLevelParam)
    { parseLevel = parseLevelParam; }

    size_t
    GetParseLevel() const
    { return parseLevel; }

    void
    IncrementParseLevel()
    { 
        ITS_REQUIRE(GetParseLevel() < (size_t)(-1));
        
        parseLevel++; 
    }

    void
    DecrementParseLevel()
    { 
        ITS_REQUIRE(GetParseLevel() > 0);

        parseLevel--; 
    }

protected:

    bool parseFromString;
    bool parseFromFile;
    bool parseFromInputStream;

    std::string stringToParse;

    std::string fileNameToParse;
    std::string filePathToParse;

    std::istream*   inputStreamToParse; // Must not be deleted by destructor.

    Tokenizer*      tokenizer;
    Scanner*        scanner;
    std::istream*   inputStream;

    Construct*      topLevelConstruct;

    bool            inputParsed;

    bool            inputPartiallyParsed;

    bool            throwParseSyntaxError; 

    std::string     syntaxErrorInformation;
    size_t          syntaxErrorLineNumber;
    size_t          syntaxErrorColumnNumber;

    bool            debugOn;

    std::ostream*   outputStreamForDebug; // Must not be deleted by destructor.

    size_t          parseLevel;


    // Must not be deleted by destructor.

    SemanticActionsVisitor* semanticActionsVisitor; 


    // Must not be used.

    Parser(const Parser& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

    Parser& operator=(const Parser& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);

        return *this;
    }
};


////////////////////////////////////////////////////////////////////////////////
//
//  SemanticActionsVisitor. Base class for semantic actions visitors.
//

class SemanticActionsVisitor
{
public:

    SemanticActionsVisitor() {}

    virtual ~SemanticActionsVisitor() {}

};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_PARSER_H_)
