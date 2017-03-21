///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:13  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.2  2007/05/23 06:11:54  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:22  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:21  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.4  2002/01/17 17:21:21  hdivoux
// LOG: Update for missing level argument in print.
// LOG:
// LOG: Revision 5.3  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: Octets.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime Octets class implementation.
//

#include <stdio.h>

#include <Octets.h>

using namespace std;

namespace its
{

bool 
Octets::Equals(const Octets& rhs) const
{
    if (_offset != rhs._offset || GetSize() != rhs.GetSize())
    {
        return false;
    }

    for (size_t i = 0; i < GetSize(); i++)
    {
        if (_data[i] != rhs._data[i])
        {
            return false;
        }
    }

    return true;
}

void 
Octets::Print(ostream& os, size_t level) const
{
    PrintArray(_data, os, level);
}

void 
Octets::PrintWithOffset(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << "[ offset = ";
    os << _offset;
    os << " ]";
    os << endl;

    PrintArray(_data, os, level);
}

static string 
ByteToHexString(byte b)
{
    char strBuf[4];
    memset(strBuf, 0, 4);

    sprintf(strBuf, "%02X", b);

    string result = strBuf;

    return result;
}

void 
Octets::PrintArray(const vector<byte>& array, ostream& os, size_t level)
{
    static const int ROW_LENGTH = 10;

    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << "[ ";

    int divisor = ROW_LENGTH;

    ITS_THROW_ASSERT(divisor > 1);

    int quotient  = array.size() / divisor;
    int remainder = array.size() % divisor;

    int i = 0;
        
    for (i = 0; i < quotient; i++)
    {
        for (int j = 0; j < divisor; j++)
        {
            os << ByteToHexString(array[i * divisor + j]);
            os << " ";
        }

        if (!(remainder == 0) || i != quotient - 1)
        {
            os << endl;
            os << levelShift;
        }

        if (i < quotient - 1)
        {
            os << "  ";
        }
    }

    if (quotient != 0 && !(remainder == 0))
    {
        os << "  ";
    }

    for (int j = 0; j < remainder; j++)
    {
        os << ByteToHexString(array[i * divisor + j]);
        os << " ";
    }

    if (remainder != 0 && quotient != 0)
    {
        for (int j = 0; j < divisor - remainder; j++)
        {
            os << "   ";
        }
    }

    os << "]" << endl;
}

// Helper function to get level shift string (four spaces multiplied by level).

string 
Octets::GetLevelShift(size_t level)
{
#if defined(__SUNPRO_CC)

    string result = "    "; // Require by Sun CC 5.2 C++ runtime (bug).

#else // !defined(__SUNPRO_CC)

    string result;

#endif // defined(__SUNPRO_CC)

    result.reserve((level + 1) * 4);

    result.append(level * 4, ' ');

    return result;
}

ostream& 
operator<<(ostream& os, Octets& octets)
{
    octets.Print(os);
    return os;
}

} // namespace its.


