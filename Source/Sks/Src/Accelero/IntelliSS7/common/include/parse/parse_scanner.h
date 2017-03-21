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
//  ID: $Id: parse_scanner.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_scanner.h: Scanner class interface.   
//
//


#if !defined(_PARSE_SCANNER_H_)
#define _PARSE_SCANNER_H_

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
//  Scanner.
//

class Scanner 
{
public:

    Scanner(std::istream& inputStreamParam);

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok (see protected section).

    // Default assignment operator not ok (see protected section).

    virtual ~Scanner();

    //
    //  Reinitialize.
    //

    void Reinitialize(std::istream& inputStreamParam);


    //
    //  Get next character.
    //

    PrsResult GetChar(char& c);


    //
    //  Peek next character.
    //

    PrsResult PeekChar(char& c);


    //
    //  Put back character.
    //

    PrsResult PutBackChar(char c);


    //
    //  Skip over characters in chararacter set.
    //

    PrsResult SkipOverInSet(const std::string& charSet);


    //
    //  Skip over characters not in character set.
    //

    PrsResult SkipOverNotInSet(const std::string& charSet);


    //
    //  Skip over characters equal to character.
    //

    PrsResult SkipOverChars(char charToSkip);


    //
    //  Skip over white spaces.
    //

    PrsResult SkipWhiteSpaces();

    
    //
    //  Read white spaces.
    //  

    PrsResult ReadWhiteSpaces(
                        std::string& readString,
                        size_t localReadStringReservedSize = 0);


    //
    //  Read characters until one character equal to terminal character.
    //  
    
    PrsResult ReadUntilEqualChar(
                        std::string& readString, 
                        char terminalChar, 
                        bool appendTerminalChar = false,
                        size_t localReadStringReservedSize = 0);



    //
    //  Read characters until one character in character set.
    //

    PrsResult ReadUntilInSet(
                        std::string& readString,
                        const std::string& charSet,
                        bool appendTerminalChar = false,
                        size_t localReadStringReservedSize = 0);


    //
    //  Read characters while every character in character set.
    //

    PrsResult ReadWhileInSet(
                        std::string& readString,
                        const std::string& charSet,
                        bool appendTerminalChar = false,
                        size_t localReadStringReservedSize = 0);


    //
    //  Read characters until one character in character range.
    //

    PrsResult ReadUntilInRange(
                        std::string& readString,
                        const std::pair<char, char>& range,
                        size_t localReadStringReservedSize = 0);


    //
    //  Read characters until one character in character range(s).
    //

    PrsResult ReadUntilInRanges(
                        std::string& readString,
                        const std::vector<std::pair<char, char> >& ranges,
                        size_t localReadStringReservedSize = 0);


    //
    //  Read characters while every character in character range.
    //

    PrsResult ReadWhileInRange(
                        std::string& readString,
                        const std::pair<char, char>& range,
                        size_t localReadStringReservedSize = 0);


    //
    //  Read characters while every character in character range(s).

    PrsResult ReadWhileInRanges(
                        std::string& readString,
                        const std::vector<std::pair<char, char> >& ranges,
                        size_t localReadStringReservedSize = 0);


    //
    //  Scanner stream position typedef.
    //

    
#if !defined(__GNUC__) || (__GNUC__ >= 3)
        
    typedef std::ios::pos_type StreamPosition;
    
#else // defined(__GNUC)
    
    typedef std::streampos StreamPosition;
    
#endif // !defined(__GNUC__)


    //
    //  Position interface and implementation.
    //

    class Position
    {
    public:

        // Default constructor must not be used (see protected section).

        Position(
            StreamPosition streamPositionParam,
            size_t lineNumberParam,
            size_t columnNumberParam)
        :   streamPosition(streamPositionParam),
            lineNumber(lineNumberParam),
            columnNumber(columnNumberParam)
        {}

        // Default copy constructor ok.

        // Default assignment operator ok.

        // Destructor must not be virtual (not a base class).

        ~Position()
        {
            // Nothing to do.
        }

        StreamPosition
        GetStreamPosition() const
        { return streamPosition; }

        size_t 
        GetLineNumber() const
        { return lineNumber; }

        size_t
        GetColumnNumber() const
        { return columnNumber; }

    protected:

        StreamPosition streamPosition;

        size_t lineNumber;

        size_t columnNumber;

        // Must not be used.

        Position()
        {
            bool must_not_be_used = false;
            ITS_ASSERT(must_not_be_used);
        }

    };


    //
    //  Tell current scanner position in underlying stream.
    //

    Position
    TellPosition()
    { 
        ClearStreamStatus();

        return Position(
                    inputStream->tellg(),
                    currentLineNumber,
                    currentColumnNumber);
    }
                    

    //
    //  Seek scanner to position in underlying stream.
    //

    void
    SeekPosition(Position position)
    { 
        ClearStreamStatus();

        inputStream->seekg(position.GetStreamPosition());
        currentLineNumber = position.GetLineNumber();
        currentColumnNumber = position.GetColumnNumber();
    }


    //
    //  Current line number.
    //

    size_t
    GetCurrentLineNumber() const
    { return currentLineNumber; }


    //
    //  Current column number.
    //

    size_t
    GetCurrentColumnNumber() const
    { return currentColumnNumber; }


    //
    //  Default read string reserved size.
    //

    enum {
        SCANNER_DEFAULT_READ_STRING_RESERVED_SIZE = 32
    };

    void
    SetReadStringReservedSize(size_t readStringReservedSizeParam)
    { readStringReservedSize = readStringReservedSizeParam; }


    bool 
    HasInputStream() const
    { return inputStream != NULL; }

    std::istream&
    GetInputStream() const
    {
        ITS_REQUIRE(HasInputStream());

        return *inputStream;
    }

protected:

    void ClearStreamStatus();

    PrsResult GetStreamStatus();

    std::istream* inputStream;  // Must not be deleted by destructor.

    size_t currentLineNumber;

    size_t currentColumnNumber;

    size_t previousColumnNumber; // Internal only.

    size_t readStringReservedSize;


    // Must not be used (see implementation).

    Scanner();

    Scanner(const Scanner& rhs);

    Scanner& operator=(const Scanner& rhs);

};



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_SCANNER_H_)
