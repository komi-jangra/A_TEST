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
//  ID: $Id: parse_production.cpp,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_production.cpp: Production class implementation.
//
//


#include <parse_production.h>
#include <parse_construct.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Production.
//

Production::Production(const Production& rhs)
{
    for (ConstructList::const_iterator iterRhs = rhs.constructList.begin();
         iterRhs != rhs.constructList.end();
         iterRhs++)
    {
        constructList.push_back((*iterRhs)->Clone());
    }
}


Production& 
Production::operator=(const Production& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        for (ConstructList::const_iterator iter = constructList.begin();
            iter != constructList.end();
            iter++)
        {
            delete (*iter);
        }

        constructList.erase(constructList.begin(), constructList.end());

        for (ConstructList::const_iterator iterRhs = rhs.constructList.begin();
             iterRhs != rhs.constructList.end();
             iterRhs++)
        {
            constructList.push_back((*iterRhs)->Clone());
        }
        
        return *this;
    }
}


Production::~Production()
{
    for (ConstructList::const_iterator iter = constructList.begin();
         iter != constructList.end();
         iter++)
    {
        delete (*iter);
    }
}




#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)
