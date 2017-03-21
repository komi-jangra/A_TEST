///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
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
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:30  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.3  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_command.cpp,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_command.cpp: MNT command implementation.
//
//


#include <mnt_command.h>

#include <mnt_helpers.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
// ValueNone.
//

string 
ValueNone::ToString() const
{
    return "<NONE>";
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueByte.
//

string 
ValueByte::ToString() const
{
    return ByteValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueInteger.
//

string 
ValueInteger::ToString() const
{
    return IntegerValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueBoolean.
//

string
ValueBoolean::ToString() const
{
    return BooleanValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueString.
//

string
ValueString::ToString() const
{
    return StringValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueByteArray.
//

string
ValueByteArray::ToString() const
{
    return ByteArrayValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueIntegerArray.
//

string
ValueIntegerArray::ToString() const
{
    return IntegerArrayValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueBooleanArray.
//

string
ValueBooleanArray::ToString() const
{
    return BooleanArrayValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// ValueStringArray.
//

string
ValueStringArray::ToString() const
{
    return StringArrayValueToString(_value);
}


///////////////////////////////////////////////////////////////////////////////
//
// Command.
//

// Nothing.



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


