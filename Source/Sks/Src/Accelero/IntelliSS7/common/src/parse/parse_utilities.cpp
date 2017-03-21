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
//  ID: $Id: parse_utilities.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//   parse_utilities.cpp: implementations of utilities for parse library.
//
//


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
//  Utility to add a four space shift before each new line of a string.
//

string 
ParseUtilStringAddLineShifts(const string& str)
{
    const size_t numberOfshifts = 4;

    //
    // Count number of new lines in input string.
    //

    size_t numberOfNewLines = 0;

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '\n')
        {
            numberOfNewLines++;
        }
    }

    string result;

    //
    // Reserve to avoid too many reallocations.
    //

    result.reserve(str.size() + (numberOfNewLines + 1) * numberOfshifts );

    result.append("    ");

    if (str.size() < 1)
    {
        return result;
    }

    ITS_ASSERT(str.size() >= 1);

    for (size_t j = 0; j < str.size() - 1; j++)
    {
        if (str[j] == '\n')
        {
            result.append("\n    ");
        }
        else
        {
            result.append(1, str[j]);
        }
    }

    result.append(1, str[str.size() - 1]);

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Utility to return a string of spaces.
//

string 
ParseUtilStringSpaces(size_t numberOfSpaces)
{
    string result;

    result.reserve(numberOfSpaces);

    result.append(numberOfSpaces, ' ');

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Utility to return a string composed of a multiple of four spaces.
//

string 
ParseUtilStringFourSpaces(size_t numberOfFourSpaces)
{
    string result;

    result.reserve(numberOfFourSpaces * 4);

    result.append(numberOfFourSpaces * 4, ' ');

    return result;
}



////////////////////////////////////////////////////////////////////////////////
//
//  Utility to transform specific characters of a string.
//

string
ParseUtilStringTransformSpecificCharacters(const string& str)
{
    string result;

    result.reserve(str.size() * 2);

    for (size_t i = 0; i < str.size(); i++)
    {
        char c = str[i];

        switch (c)
        {
        case '\n':
            result.append("<LF>");
            break;

        case '\r':
            result.append("<CR>");
            break;

        case '\t':
            result.append("<HTAB>");
            break;

        case '\b':
            result.append("<BCKSP>");
            break;

        case '\v': 
            result.append("<VTAB>");
            break;

        case '\0':
            result.append("<NULL>");
            break;

        default:
            result.append(1, c);
            break;
        }
    }
    
    return result;
}




#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

