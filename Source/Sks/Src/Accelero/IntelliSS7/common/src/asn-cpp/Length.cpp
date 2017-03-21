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
// LOG: Revision 1.1  2007/03/30 04:53:53  cvsadmin
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
// LOG: Revision 5.4  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:05:03  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: Length.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime Length class implementation.
//

#include <Asn.h>
#include <Length.h>
#include <AsnException.h>

using namespace std;

namespace its {

Octets* 
Length::Encode(const AsnOptions& asnOptions)
{
    vector<byte> array(ASN_LONG_FORM_MAX_LENGTH + 1, 0x00U);

    int inc = 0;

    if (_length == ASN_INDEFINITE)
    {
        array[0] = ASN_INDEFINITE_FORM_VALUE;
        inc = 1;
    }
    else if (_length <= ASN_SHORT_FORM_MAX_VALUE)
    {
        array[0] = (byte)_length;
        inc = 1;
    }
    else
    {
        bool maxShrink = false;
        inc = 1;

        for(int i = 1; i <= ASN_LONG_FORM_MAX_LENGTH; i++)
        {
            if (!maxShrink)
            {
                byte b = (byte)(((unsigned)_length) >>
                                ((ASN_LONG_FORM_MAX_LENGTH - i) *
                                ASN_BITS_PER_BYTE));

                if (b == 0)
                {
                    continue;
                }
                else
                {
                    array[0] = ASN_LONG_FORM_INDICATOR;
                    array[0] |= ASN_LONG_FORM_MAX_LENGTH - (byte)(i - 1);
                    maxShrink = true;
                }
            }

            array[inc] = (byte)(((unsigned)_length) >>
                                ((ASN_LONG_FORM_MAX_LENGTH - i) *
                                ASN_BITS_PER_BYTE));

            inc++;
        }

    }

    Octets* result = new Octets(array, inc);

    return result;
}

void 
Length::Decode(Octets& octets, const AsnOptions& asnOptions)
{
    if (!octets.IsIndexWithOffsetValid(0))
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_LENGTH_LENGTH, octets);
    }

    byte b = octets.GetOctetAtWithOffset(0);

    if (b == ASN_INDEFINITE_FORM_VALUE)
    {
        _length = ASN_INDEFINITE;
        octets.IncrementOffset();
    }
    else if (!(b & ASN_LONG_FORM_INDICATOR))
    {
        _length = b;
        octets.IncrementOffset();
    }
    else
    {
        byte ll = (byte)(b & ASN_LENGTH_LENGTH_MASK);

        _length = 0;

        for (int i = 1; i <= ll; i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(ASN_E_INVALID_LENGTH_LENGTH, octets);
            }

            _length |= ((long)octets.GetOctetAtWithOffset(i) &
                       ASN_BYTE_MASK_IN_LONG) << (ASN_BITS_PER_BYTE * (ll - i));
        }

        octets.IncrementOffset(1 + ll);
    }
}

void 
Length::DecodePreserveOffset(Octets& octets, const AsnOptions& asnOptions)
{
    size_t offset = octets.GetOffset();

    Decode(octets, asnOptions);

    octets.SetOffset(offset);
}


bool 
Length::IsIndefiniteEndMark(const Octets& octets)
{
    if (!octets.IsIndexWithOffsetValid(0) ||
        !octets.IsIndexWithOffsetValid(1))
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_INDEFINITE_LENGTH_LENGTH, octets);
    }

    byte b1 = octets.GetOctetAtWithOffset(0);
    byte b2 = octets.GetOctetAtWithOffset(1);

    if (b1 == ASN_INDEFINITE_END_MARK_BYTE_ONE &&
        b2 == ASN_INDEFINITE_END_MARK_BYTE_TWO)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Constant definitions.
const long Length::ASN_INDEFINITE                   = -1;
const byte Length::ASN_INDEFINITE_FORM_VALUE        = (byte)0x80U;
const byte Length::ASN_SHORT_FORM_MAX_VALUE         = (byte)0x7FU;
const byte Length::ASN_LENGTH_LENGTH_MASK           = (byte)0x7FU;
const byte Length::ASN_LONG_FORM_INDICATOR          = (byte)0x80U;
const int  Length::ASN_LONG_FORM_MAX_LENGTH         = ASN_BYTES_PER_LONG;
const int  Length::ASN_INDEFINITE_END_MARK_LENGTH   = 2;
const byte Length::ASN_INDEFINITE_END_MARK_BYTE_ONE = (byte)0x00U;
const byte Length::ASN_INDEFINITE_END_MARK_BYTE_TWO = (byte)0x00U;

} // namespace its.

