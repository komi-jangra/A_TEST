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
//  ID: $Id: parse_token.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_token.cpp: Token class implementation.     
//
//


#include <parse_token.h>
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
//  Token.
//

void 
Token::Initialize(
            int typeParam,
            const std::string& stringValueParam,
            size_t lineNumberParam,
            size_t columnNumberParam)
{
    type            = typeParam;
    stringValue     = stringValueParam;
    lineNumber      = lineNumberParam;
    columnNumber    = columnNumberParam;
}


PrsResult
Token::TryConsume(Tokenizer& tokenizer)
{
    Scanner& scanner = tokenizer.GetScanner();

    Scanner::Position savedPosition = scanner.TellPosition();

    PrsResult consumeResult = Consume(tokenizer);

    if (consumeResult == PARSE_SUCCESS)
    {
        return PARSE_SUCCESS;
    }
    else
    {
        scanner.SeekPosition(savedPosition);

        return PARSE_ERROR_NOT_CONSUMED;
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  TokenKeyword.
//

PrsResult
TokenKeyword::Consume(Tokenizer& tokenizer)
{
    ITS_REQUIRE(HasKeywordCode());
    ITS_REQUIRE(tokenizer.HasKeywordCode(GetKeywordCode()));

    string tokenStringValue = 
        tokenizer.RetrieveKeywordStringValueFromCode(keywordCode);

    if (!tokenizer.IsKeywordCaseSensitive())
    {
        for (size_t i = 0; i < tokenStringValue.size(); i++)
        {
            tokenStringValue[i] = (char)tolower(tokenStringValue[i]);
        }
    }

    Scanner& scanner = tokenizer.GetScanner();

    lineNumber = scanner.GetCurrentLineNumber();
    columnNumber = scanner.GetCurrentColumnNumber();

    stringValue.erase();
    stringValue.reserve(tokenStringValue.size());

    char tokenChar  = '\0';
    char c          = '\0';
    char savedChar  = '\0';

    PrsResult result = PARSE_SUCCESS;

    size_t index = 0;

    while (index < tokenStringValue.size())
    {
        tokenChar = tokenStringValue[index];

        result = scanner.GetChar(c);

        savedChar = c;

        if (result != PARSE_SUCCESS)
        {
            if (result == PARSE_ERROR_STREAM_EOF)
            {
                // Append "<EOF>" to token string value (for syntax error
                // reporting mechanism).

                stringValue.append("<EOF>");
            }

            return result;
        }

        if (!tokenizer.IsKeywordCaseSensitive())
        {
            c = tolower(c);
        }

        if (tokenChar == c)
        {
            // Append character to token string value and continue comparison.

            stringValue.append(1, savedChar);
        }
        else
        {
            // Still append character to token string value (for syntax error
            // reporting mechanism).

            stringValue.append(1, savedChar);

            return PARSE_ERROR_KEYWORD_COMPARISON;
        }

        index++;
    }

    return PARSE_SUCCESS;
}



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


