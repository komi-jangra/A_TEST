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
//  ID: $Id: parse_tokenizer.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_tokenizer.h: Tokenizer class interface.   
//
//


#if !defined(_PARSE_TOKENIZER_H_)
#define _PARSE_TOKENIZER_H_

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

class Token;
class Scanner;


////////////////////////////////////////////////////////////////////////////////
//
//  Tokenizer. Simple due to parser driven algorithm. Can be extended in the 
//  future.
//


class Tokenizer
{
public:

    Tokenizer(Scanner& scannerParam);

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok (see protected section).

    // Default assignment operator not ok (see protected section).

    virtual ~Tokenizer();


    //
    //  Reinitialize (do not affect keyword containers and properties).
    //

    void Reinitialize(Scanner& scannerParam);


    //
    //  Associated scanner.
    //

    bool
    HasScanner() const
    { return scanner != NULL; }

    Scanner&
    GetScanner() const
    { 
        ITS_REQUIRE(HasScanner());

        return *scanner; 
    }


    //
    //  Consume specifed token and return result accordingly.
    //

    PrsResult ConsumeToken(Token& token);


    //
    //  Keyword related.
    //

    bool HasKeywordStringValue(const std::string& stringValue) const;

    bool HasKeywordCode(int code) const;

    void InsertKeyword(const std::string& stringValue);

    int RetrieveKeywordCodeFromStringValue(const std::string& stringValue) const;

    const std::string& RetrieveKeywordStringValueFromCode(int code) const;

    void 
    SetKeywordCaseSensitive()
    { keywordCaseSensitive = true; }

    void 
    SetKeywordCaseInsensitive()
    { keywordCaseSensitive = false; }

    bool 
    IsKeywordCaseSensitive() const
    { return keywordCaseSensitive; }

    const std::string&
    GetLastInvalidTokenStringValue() const
    { return lastInvalidTokenStringValue; }

    size_t
    GetLastInvalidTokenLineNumber() const
    { return lastInvalidTokenLineNumber; }

    size_t
    GetLastInvalidTokenColumnNumber() const
    { return lastInvalidTokenColumnNumber; }


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


protected:

    Scanner* scanner; // Associated scanner.


    // Keyword related containers.

    typedef std::vector<std::string> TypeTableKeywordCodeToStringValue;

    typedef std::map<std::string, int> TypeTableKeywordStringValueToCode;

    TypeTableKeywordCodeToStringValue tableKeywordCodeToStringValue;

    TypeTableKeywordStringValueToCode tableKeywordStringValueToCode;


    // Keyword related.

    bool keywordCaseSensitive;


    // Error reporting.

    std::string lastInvalidTokenStringValue;

    size_t lastInvalidTokenLineNumber;

    size_t lastInvalidTokenColumnNumber;


    // Debugging related.

    bool debugOn;

    std::ostream* outputStreamForDebug; // Must not be deleted by destructor.


    // Must not be used.

    Tokenizer();

    Tokenizer(const Tokenizer& rhs);

    Tokenizer& operator=(const Tokenizer& rhs);

};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_TOKENIZER_H_)

