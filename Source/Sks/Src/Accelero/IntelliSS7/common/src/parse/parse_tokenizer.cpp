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
//  ID: $Id: parse_tokenizer.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_tokenizer.cpp: Tokenizer class implementation.   
//
//


#include <parse_tokenizer.h>

#include <iostream>

#include <parse_token.h>
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
//  Tokenizer.
//

Tokenizer::Tokenizer(Scanner& scannerParam) 
:   scanner(&scannerParam),
    keywordCaseSensitive(false),
    lastInvalidTokenLineNumber(1),
    lastInvalidTokenColumnNumber(1),
    debugOn(false),
    outputStreamForDebug(NULL)
{
    // Nothing to do.
}


Tokenizer::~Tokenizer()
{
    // Nothing to do.
}


void
Tokenizer::Reinitialize(Scanner& scannerParam)
{
    scanner = &scannerParam;
}


PrsResult
Tokenizer::ConsumeToken(Token& token)
{
    if (IsDebugOn() && HasOutputStreamForDebug())
    {
        ostream& os = GetOutputStreamForDebug();
        Scanner& scanner = GetScanner();

        os << endl;
        os << "Tokenizer - Attempt to consume token at line <";
        os << scanner.GetCurrentLineNumber();
        os << "> and column <";
        os << scanner.GetCurrentColumnNumber();
        os << ">...";
        os << endl;
    }

    PrsResult result = token.Consume(*this);

    if (result != PARSE_SUCCESS)
    {
        lastInvalidTokenStringValue = token.GetStringValue();

        lastInvalidTokenLineNumber = token.GetLineNumber();

        lastInvalidTokenColumnNumber = token.GetColumnNumber();

        if (IsDebugOn() && HasOutputStreamForDebug())
        {
            ostream& os = GetOutputStreamForDebug();

            string value =
                ParseUtilStringTransformSpecificCharacters(
                    token.GetStringValue());

            os << "Tokenizer - Failed to consume token with retrieved value <";
            os << value; 
            os << "> and error <";
            os << PrsErrorGetText(result);
            os << ">.";
            os << endl;
            os << endl;
        }
    }
    else 
    {
        if (IsDebugOn() && HasOutputStreamForDebug())
        {
            ostream& os = GetOutputStreamForDebug();

            string value = 
                ParseUtilStringTransformSpecificCharacters(
                    token.GetStringValue());

            os << "Tokenizer - Succeeded to consume token of value <";
            os << value;
            os << ">.";
            os << endl;
            os << endl;
        }
    }

    return result;
}


bool
Tokenizer::HasKeywordStringValue(const string& stringValue) const
{
    TypeTableKeywordStringValueToCode::const_iterator iter = 
        tableKeywordStringValueToCode.find(stringValue);

    return iter != tableKeywordStringValueToCode.end();
}


bool
Tokenizer::HasKeywordCode(int code) const
{
    ITS_REQUIRE(code >= 1);

    return ((size_t)code < tableKeywordCodeToStringValue.size());
}


void
Tokenizer::InsertKeyword(const string& stringValue)
{
    ITS_REQUIRE(stringValue.size() > 0);
    ITS_REQUIRE(!HasKeywordStringValue(stringValue));

    if (tableKeywordCodeToStringValue.size() == 0)
    {
        // First element in vector not used because keyword codes are >= 1.

        tableKeywordCodeToStringValue.push_back("");
    }

    ITS_ASSERT(tableKeywordCodeToStringValue.size() >= 1);

    tableKeywordCodeToStringValue.push_back(stringValue);

    size_t code = tableKeywordCodeToStringValue.size() - 1;

    ITS_ASSERT(code >= 1);

    pair<TypeTableKeywordStringValueToCode::iterator, bool>
        insertRes =
            tableKeywordStringValueToCode.insert(
                TypeTableKeywordStringValueToCode::value_type(
                    stringValue,
                        code));

    ITS_ENSURE(insertRes.second);
}


int 
Tokenizer::RetrieveKeywordCodeFromStringValue(const string& stringValue) const
{
    ITS_REQUIRE(HasKeywordStringValue(stringValue));

    TypeTableKeywordStringValueToCode::const_iterator iter =
        tableKeywordStringValueToCode.find(stringValue);

    ITS_ASSERT(iter != tableKeywordStringValueToCode.end());

    return (*iter).second;
}


const string&
Tokenizer::RetrieveKeywordStringValueFromCode(int code) const
{
    ITS_REQUIRE(code >= 1);
    ITS_REQUIRE(HasKeywordCode(code));

    return tableKeywordCodeToStringValue[code];
}



////////////////////////////////////////////////////////////
//
//  Must not be used.
//

Tokenizer::Tokenizer() 
:   scanner(new Scanner(cin)) // Use cin as always available istream.
{
    bool must_not_be_used = false;
    ITS_ASSERT(must_not_be_used);
}


Tokenizer::Tokenizer(const Tokenizer& rhs) : scanner(rhs.scanner)
{
    bool must_not_be_used = false;
    ITS_ASSERT(must_not_be_used);
}


Tokenizer&
Tokenizer::operator=(const Tokenizer& rhs)
{
    bool must_not_be_used = false;
    ITS_ASSERT(must_not_be_used);

    return *this;
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)







