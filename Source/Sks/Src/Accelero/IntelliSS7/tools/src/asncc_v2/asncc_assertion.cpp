///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            Copyright 1999 - 2002 IntelliNet Technologies, Inc.            //
//                          All Rights Reserved.                             //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:40  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:19  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:39  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:52:58  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:34  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: asncc_assertion.cpp,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $"

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



