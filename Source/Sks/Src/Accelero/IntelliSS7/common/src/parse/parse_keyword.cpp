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
//  ID: $Id: parse_keyword.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_keyword.cpp: Keyword class implementation.   
//
//


#include <parse_keyword.h>
#include <parse_parser.h>
#include <parse_tokenizer.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Keyword. 
//

Keyword::Keyword(const Keyword& rhs) : Terminal<TokenKeyword>(rhs)
{
    name = rhs.name;
}


Keyword&
Keyword::operator=(const Keyword& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        static_cast<Terminal<TokenKeyword>&>(*this) = rhs;

        name = rhs.name;

        return *this;
    }
}


void
Keyword::InitializeKeywordCode()
{
    Tokenizer& tokenizer = GetPrimaryParser().GetTokenizer();

    //
    // Tokenizer MUST already contains keyword name. See member function 
    // Construct::AddKeyword for more details.
    //
    // Target only primary parser: if more than one parser object is used then
    // the list of keywords must be initialized explicitly.
    //

    ITS_ASSERT(tokenizer.HasKeywordStringValue(name));

    int keywordCode = tokenizer.RetrieveKeywordCodeFromStringValue(name);

    token.SetKeywordCode(keywordCode);
}


string
Keyword::GetValue() const
{
    return name;
}


void
Keyword::Print(ostream& os, size_t level) const
{
    string levelShift = ParseUtilStringFourSpaces(level);

    os << levelShift;

    os << name;
    os << " (";
    os << "Keyword";

    if (IsOptional())
    {
        os << " | optional";
    }

    if (IsTopLevel())
    {
        os << " | top level";
    }

    os << ")" << endl;
}


void
Keyword::PrintValue(ostream& os) const
{
    os << name;    
}



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)