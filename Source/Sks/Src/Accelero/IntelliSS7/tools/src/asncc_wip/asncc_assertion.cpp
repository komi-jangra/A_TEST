////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: asncc_assertion.cpp,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  Assertion implementation.
//

#include <asncc_assertion.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)




////////////////////////////////////////////////////////////
//
//  GenericException.
//

GenericException::GenericException() 
    : line(0)
{
}


GenericException::GenericException(const string& reasonParam)
    : reason(reasonParam), line(0)
{
}

GenericException::GenericException(const string& reasonParam,
                                   const string& fileParam,
                                   unsigned long lineParam)
: reason(reasonParam), file(fileParam), line(lineParam)
{
}

GenericException::~GenericException() ITS_THROW_SPEC_NULL
{
}

void GenericException::Register()
{
}

const string& GenericException::Description()
{
    Format();
    return description;
}


void GenericException::Format()
{
    description.erase(description.begin(), description.end());

    description.append("[ ");

    if (!reason.empty())
    {
        description.append(reason);
    }
    else
    {
        description.append("Reason not specified");
    }

    if (!file.empty() && line != 0)
    {
        char ulStr[16];

        description.append(" | File <");
        description.append(StripPath(file));
        description.append("> | Line <");
        sprintf(ulStr, "%ld", line);
        description.append(ulStr);
        description.append(">");
    }

    for (list<string>::iterator iter = fields.begin();
         iter != fields.end();
         ++iter)
    {
        if (!(*iter).empty())
        {
            description.append(" | ");
            description.append((*iter));
        }
    }

    description.append(" ]");
}



