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
//  ID: $Id: parse_scanner.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_scanner.cpp: Scanner class implementation.  
//
//


#include <parse_scanner.h>

#include <iostream>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

////////////////////////////////////////////////////////////////////////////////
//
//  Scanner.
//

Scanner::Scanner(istream& inputStreamParam)
:   inputStream(&inputStreamParam),
    currentLineNumber(1),
    currentColumnNumber(1),
    previousColumnNumber(1),
    readStringReservedSize(SCANNER_DEFAULT_READ_STRING_RESERVED_SIZE)
{
    // Nothing to do.
}


Scanner::~Scanner()
{
    // Nothing to do.
}


void
Scanner::Reinitialize(istream& inputStreamParam)
{
    inputStream = &inputStreamParam;

    currentLineNumber   = 1;
    currentColumnNumber = 1;

    readStringReservedSize = SCANNER_DEFAULT_READ_STRING_RESERVED_SIZE;
}


PrsResult
Scanner::GetChar(char& c)
{
    ClearStreamStatus();
    
    inputStream->get(c);

    PrsResult result = GetStreamStatus();

    if (result != PARSE_SUCCESS)
    {
        return result;
    }

    if (c != '\n')
    {
        currentColumnNumber++;
    }
    else
    {
        currentLineNumber++;

        previousColumnNumber = currentColumnNumber;

        currentColumnNumber = 1;
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::PeekChar(char& c)
{
    ClearStreamStatus();

    c = (char)inputStream->peek();

    PrsResult result = GetStreamStatus();

    // Do not update current line and column numbers.

    return result;
}


PrsResult
Scanner::PutBackChar(char c)
{
    ClearStreamStatus();

    inputStream->putback(c);

    PrsResult result = GetStreamStatus();

    if (result != PARSE_SUCCESS)
    {
        return result;
    }

    if (c != '\n')
    {
        ITS_ASSERT(currentColumnNumber > 1);

        currentColumnNumber--;
    }
    else
    {
        ITS_ASSERT(currentLineNumber > 1);

        currentLineNumber--;

        currentColumnNumber = previousColumnNumber;
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::SkipOverInSet(const string& charSet)
{
    ClearStreamStatus();
    
    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result;
        }

        if (charSet.find(c) != string::npos)
        {
            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }

            return PARSE_SUCCESS;
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result;
        }
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::SkipOverNotInSet(const string& charSet)
{
    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;
    
    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result;
        }

        if (charSet.find(c) == string::npos)
        {
            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }

            return PARSE_SUCCESS;
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result;
        }
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::SkipOverChars(char charToSkip)
{
    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result;
        }

        if (c == charToSkip)
        {
            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }

            return PARSE_SUCCESS;
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result;
        }
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::SkipWhiteSpaces()
{
    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result;
        }

        if (c == ' ' || c == '\t')
        {
            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }

            return PARSE_SUCCESS;
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result;
        }
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::ReadWhiteSpaces(
                    string& readString,
                    size_t localReadStringReservedSize)
{
    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        if (c == ' ' || c == '\t')
        {
            readString.append(1, c);

            currentColumnNumber++;
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result; // readString output parameter ok.
        }
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::ReadUntilEqualChar(
            std::string& readString, 
            char terminalChar, 
            bool appendTerminalChar,
            size_t localReadStringReservedSize)
{
    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        if (c == terminalChar)
        {
            if (appendTerminalChar)
            {
                readString.append(1, c);

                if (c != '\n')
                {
                    currentColumnNumber++;
                }
                else
                {
                    currentLineNumber++;

                    previousColumnNumber = currentColumnNumber;

                    currentColumnNumber = 1;
                }

                return PARSE_SUCCESS;
            }
            else
            {
                inputStream->unget();

                result = GetStreamStatus();

                return result; // readString output parameter ok.
            }
        }
        else
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
    }

    return PARSE_SUCCESS;
}


PrsResult 
Scanner::ReadUntilInSet(
                string& readString,
                const string& charSet,
                bool appendTerminalChar,
                size_t localReadStringReservedSize)
{
    ITS_REQUIRE(charSet.size() > 0);

    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        if (charSet.find(c) == string::npos)
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
        else
        {
            if (appendTerminalChar)
            {
                readString.append(1, c);

                if (c != '\n')
                {
                    currentColumnNumber++;
                }
                else
                {
                    currentLineNumber++;

                    previousColumnNumber = currentColumnNumber;

                    currentColumnNumber = 1;
                }

                return PARSE_SUCCESS;
            }
            else
            {
                inputStream->unget();

                result = GetStreamStatus();

                return result; // readString output parameter ok.
            }
        }
    }

    return PARSE_SUCCESS;
}


PrsResult
Scanner::ReadWhileInSet(                        
                string& readString,
                const string& charSet,
                bool appendTerminalChar,
                size_t localReadStringReservedSize)
{
    ITS_REQUIRE(charSet.size() > 0);

    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }  
        
        if (charSet.find(c) != string::npos)
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
        else
        {
            if (appendTerminalChar)
            {
                readString.append(1, c);

                if (c != '\n')
                {
                    currentColumnNumber++;
                }
                else
                {
                    currentLineNumber++;

                    previousColumnNumber = currentColumnNumber;

                    currentColumnNumber = 1;
                }

                return PARSE_SUCCESS;
            }
            else
            {
                inputStream->unget();

                result = GetStreamStatus();

                return result; // readString output parameter ok.
            }
        }
    }

    return PARSE_SUCCESS;
}


PrsResult 
Scanner::ReadUntilInRange(
                string& readString,
                const pair<char, char>& range,
                size_t localReadStringReservedSize)
{
    ITS_REQUIRE(range.first < range.second);

    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        if (c < range.first || c > range.second)
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result; // readString output parameter ok.
        }
    }

    return PARSE_SUCCESS;
}


PrsResult 
Scanner::ReadWhileInRange(
                string& readString,
                const pair<char, char>& range,
                size_t localReadStringReservedSize)
{
    ITS_REQUIRE(range.first < range.second);

    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        if (c >= range.first && c <= range.second)
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result; // readString output parameter ok.
        }
    }

    return PARSE_SUCCESS;
}


PrsResult 
Scanner::ReadUntilInRanges(
                string& readString,
                const vector<pair<char, char> >& ranges,
                size_t localReadStringReservedSize)
{
    ITS_REQUIRE(ranges.size() > 0);

    vector<pair<char, char> >::const_iterator iter = NULL;

    for (iter = ranges.begin(); iter != ranges.end(); iter++)
    {
        ITS_REQUIRE(iter->first < iter->second);
    }

    // Should also require that ranges are exclusives.

    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        bool inRanges = false;

        for (iter = ranges.begin(); iter != ranges.end(); iter++)
        {
            if (c >= iter->first && c <= iter->second)
            {
                inRanges = true;
                
                break;
            }
        }

        if (!inRanges)
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result; // readString output parameter ok.
        }
    }

    return PARSE_SUCCESS;
}


PrsResult 
Scanner::ReadWhileInRanges(
                string& readString,
                const vector<pair<char, char> >& ranges,
                size_t localReadStringReservedSize)
{
    ITS_REQUIRE(ranges.size() > 0);

    vector<pair<char, char> >::const_iterator iter = NULL;

    for (iter = ranges.begin(); iter != ranges.end(); iter++)
    {
        ITS_REQUIRE(iter->first < iter->second);
    }

    // Should also require that ranges are exclusives.

    readString.erase();

    if (localReadStringReservedSize == 0)
    {
        readString.reserve(readStringReservedSize);
    }
    else
    {
        readString.reserve(localReadStringReservedSize);
    }

    ClearStreamStatus();

    char c = '\0';

    PrsResult result = PARSE_SUCCESS;

    while (true)
    {
        inputStream->get(c);

        result = GetStreamStatus();

        if (result != PARSE_SUCCESS)
        {
            return result; // readString output parameter ok.
        }

        bool inRanges = false;

        for (iter = ranges.begin(); iter != ranges.end(); iter++)
        {
            if (c >= iter->first && c <= iter->second)
            {
                inRanges = true;

                break;
            }
        }

        if (inRanges)
        {
            readString.append(1, c);

            if (c != '\n')
            {
                currentColumnNumber++;
            }
            else
            {
                currentLineNumber++;

                previousColumnNumber = currentColumnNumber;

                currentColumnNumber = 1;
            }
        }
        else
        {
            inputStream->unget();

            result = GetStreamStatus();

            return result; // readString output parameter ok.
        }
    }

    return PARSE_SUCCESS;
}


void
Scanner::ClearStreamStatus()
{
    inputStream->clear();
}


PrsResult
Scanner::GetStreamStatus()
{
    if (inputStream->good())
    { 
        return PARSE_SUCCESS;
    }
    else if (inputStream->eof())
    {
        return PARSE_ERROR_STREAM_EOF;
    }
    else if (inputStream->fail())
    {
        return PARSE_ERROR_STREAM_FAIL;
    }
    else if (inputStream->bad())
    {
        return PARSE_ERROR_STREAM_BAD;
    }
    else
    {
        return PARSE_ERROR_STREAM_UNKNOWN;
    }
}


////////////////////////////////////////////////////////////
//
//  Must not be used.
//

Scanner::Scanner() 
:   inputStream(&cin), // Use cin as always available istream.
    currentLineNumber(1),
    currentColumnNumber(1),
    previousColumnNumber(1),
    readStringReservedSize(0)
{
    bool must_not_be_used = false;
    ITS_ASSERT(must_not_be_used);
}


Scanner::Scanner(const Scanner& rhs) : inputStream(rhs.inputStream)
{
    bool must_not_be_used = false;
    ITS_ASSERT(must_not_be_used);
}


Scanner&
Scanner::operator=(const Scanner& rhs)
{
    bool must_not_be_used = false;
    ITS_ASSERT(must_not_be_used);

    return *this;
}



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


