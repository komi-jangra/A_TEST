////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: exc_assert.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:43  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:20  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:17  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:07  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.1  2000/08/16 00:08:37  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:30:28  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.5  1999/06/29 01:28:54  mmiers
// LOG:
// LOG:
// LOG: Portability changes.
// LOG:
// LOG: Revision 1.4  1999/06/28 19:13:59  skarmakar
// LOG:
// LOG:
// LOG: Update with awareness of throw specifier, behavior control defines
// LOG: in its++.h.
// LOG:
// LOG: Revision 1.3  1998/05/20 04:44:09  mmiers
// LOG: Cleanup.
// LOG: Hubert, some iterators need to be constant while others don't.  Please
// LOG: see me about this.
// LOG:
// LOG: Revision 1.2  1998/05/19 23:43:51  mmiers
// LOG: Fix for UNIX builds.
// LOG:
// LOG: Revision 1.1  1998/05/19 22:39:54  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>

#include <exc_assert.h>


GenericException::GenericException() 
    : line(0)
{
}


GenericException::GenericException(const string& reasonParam)
    : reason(reasonParam), line(0)
{
}

GenericException::GenericException(const string& reasonParam, const string& fileParam, unsigned long lineParam)
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
        description.append(file);
        description.append("> | Line <");
        sprintf(ulStr, "%lu", line);
        description.append(ulStr);
        description.append(">");
    }

    for (list<string>::iterator iter = fields.begin(); iter != fields.end(); ++iter)
    {
        if (!(*iter).empty())
        {
            description.append(" | ");
            description.append((*iter));
        }
    }

    description.append(" ]");
}
