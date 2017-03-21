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
//  ID: $Id: parse_keyword.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_keyword.h: Keyword class interface.   
//
//


#if !defined(_PARSE_KEYWORD_H_)
#define _PARSE_KEYWORD_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <parse.h>
#include <parse_terminal.h>
#include <parse_token.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Keyword. Terminal constructs with just one specimen representing a keyword
//  of the language or a special symbol.
//

class Keyword : public Terminal<TokenKeyword>
{
public:

    Keyword(Parser& primaryParserParam, const std::string& nameParam)
    :   Terminal<TokenKeyword>(primaryParserParam),
        name(nameParam)
    {
        InitializeKeywordCode();
    }

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    Keyword(const Keyword& rhs);


    // Default assignment operator not ok.

    Keyword& operator=(const Keyword& rhs);


    //
    //  Definition is mandatory (see ancestors).
    //
    
    virtual Construct*
    Clone() const
    { return new Keyword(*this); }


    virtual ~Keyword()
    {
        // Nothing to do.

        // TODO: double check.
    }


    //
    //  Initialize associated token keyword identification number. Member
    //  function must not be virtual (called from constructor).
    //

    void InitializeKeywordCode();


    //
    //  Name of the keyword (i.e. keyword associated character string value).
    //

    virtual const std::string&
    GetName() const
    { return name; }


    //
    //  Type of the construct.
    //

    virtual int
    GetType() const
    { return CONSTRUCT_TYPE_KEYWORD; }


    //
    //  Get (parsed) value.
    //  

    virtual std::string GetValue() const;


    //
    //  Printing.
    //

    virtual void Print(std::ostream& os, size_t level = 0) const;

    virtual void PrintValue(std::ostream& os) const;


protected:

    std::string name;

    
    // Must not be used.

    Keyword() 
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_KEYWORD_H_)
