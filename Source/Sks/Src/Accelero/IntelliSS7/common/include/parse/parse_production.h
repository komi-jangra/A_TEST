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
//  ID: $Id: parse_production.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_production.h: Production class interface.  
//
//


#if !defined(_PARSE_PRODUCTION_H_)
#define _PARSE_PRODUCTION_H_

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
//  Forward declarations.
//

class Construct;

typedef std::list<Construct*> ConstructList;


////////////////////////////////////////////////////////////////////////////////
//
//  Production. Grammatical production abstraction.
//

class Production
{
public:

    Production()
    {
        // Nothing to do.
    }

    // Default copy constructor not ok.

    Production(const Production& rhs);

    
    // Default assignment operator not ok.

    Production& operator=(const Production& rhs);

    
    // Destructor must not be virtual (not a base class).

    ~Production();


    ///////////////////////////////////////////////////////
    //
    //  Access.
    //

    const ConstructList& 
    GetConstructList() const
    { return constructList; }


    ConstructList&
    GetConstructList()
    { return constructList; }

    size_t
    GetSize() const
    { return constructList.size(); }


protected:

    ConstructList constructList;

};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_PRODUCTION_H_)
