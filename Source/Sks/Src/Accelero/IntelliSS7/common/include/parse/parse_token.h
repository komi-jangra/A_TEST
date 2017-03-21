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
//  ID: $Id: parse_token.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_token.h: Token class and TokenKeyword class interfaces.   
//
//


#if !defined(_PARSE_TOKEN_H_)
#define _PARSE_TOKEN_H_

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


////////////////////////////////////////////////////////////////////////////////
//
//  Token. Individual elements of lexical analysis.  
//

class Token
{
public:

    // Default constructor defined in protected section.

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~Token()
    {
        // Nothing to do.
    }

    // Reserved token types.

    enum {
        TOKEN_TYPE_INVALID  = -1,
        TOKEN_TYPE_KEYWORD  = 0
    };

    //
    //  Initialize token.
    //

    void Initialize(
            int typeParam,
            const std::string& stringValueParam,
            size_t lineNumberParam,
            size_t columnNumberParam);


    //
    //  Type of token.
    //

    int 
    GetType() const
    { return type; }


    //
    //  Token associated character string value.
    //

    const std::string&
    GetStringValue() const
    { return stringValue; }


    //
    //  Line number in the parsed text.
    //

    size_t
    GetLineNumber() const
    { return lineNumber; }


    //
    //  Column number in the parsed text.
    //

    size_t
    GetColumnNumber() const
    { return columnNumber; }


    //
    //  Consume current token in specified tokenizer.
    //

    virtual PrsResult Consume(Tokenizer& tokenizer) = 0;


    //
    //  Try Consume current token in specified tokenizer (if not consumed 
    //  replace scanner to original position).
    //

    virtual PrsResult TryConsume(Tokenizer& tokenizer);


protected:

    Token()
    :   type(TOKEN_TYPE_INVALID),
        lineNumber(0),
        columnNumber(0)
    {}

    Token(int typeParam)
    :   type(typeParam),
        lineNumber(0),
        columnNumber(0)
    {}

    int type;

    std::string stringValue;

    size_t lineNumber;

    size_t columnNumber;

};


////////////////////////////////////////////////////////////////////////////////
//
//  TokenKeyword. Individual elements of lexical analysis representing a
//  language keyword or a special symbol.  
//

class TokenKeyword : public Token
{
public:

    TokenKeyword() 
    :   Token(TOKEN_TYPE_KEYWORD),
        keywordCode(0),
        hasKeywordCode(false)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~TokenKeyword()
    {
        // Nothing to do.
    }            

    void
    SetKeywordCode(int keywordCodeParam)
    { 
        keywordCode = keywordCodeParam;
        hasKeywordCode = true;
    }

    bool 
    HasKeywordCode() const
    { return hasKeywordCode; }


    //
    //  Identification number of keyword.
    //

    int
    GetKeywordCode() const
    { 
        ITS_REQUIRE(HasKeywordCode());
        
        return keywordCode; 
    }


    //
    //  Consume current token in specified tokenizer.
    //

    virtual PrsResult Consume(Tokenizer& tokenizer);


protected:

    int keywordCode;

    bool hasKeywordCode;
};


////////////////////////////////////////////////////////////////////////////////
//
//  TokenTemplate. Template class to define Tokens.  
//

template<int T>
class TokenTemplate : public its::Token
{
public:

    TokenTemplate()
    :   its::Token(T)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~TokenTemplate()
    {
        // Nothing to do.
    }

    //  
    //  Consume current token in specified tokenizer.
    //

    virtual its::PrsResult Consume(its::Tokenizer& tokenizer);

};


////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_TOKEN. Macro to define Tokens.
//
//  Cannot be traced in by debugger. Switch to template approach if required.
//
//  MUST be kept in sync with template class TokenTemplate.
//

//
//  MP_ClassName => name of class.
//  MP_TokenType => type of token class.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_TOKEN(MP_ClassName, MP_TokenType)                \
                                                                            \
class MP_ClassName : public its::Token                                      \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName()                                                          \
    :   its::Token(MP_TokenType)                                            \
    {}                                                                      \
                                                                            \
    virtual ~MP_ClassName()                                                 \
    {}                                                                      \
                                                                            \
    virtual its::PrsResult Consume(its::Tokenizer& tokenizer);              \
                                                                            \
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_TOKEN_H_)
