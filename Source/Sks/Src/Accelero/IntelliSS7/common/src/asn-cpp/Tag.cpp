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
// LOG: Revision 1.1  2007/03/30 04:53:56  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:22  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.3  2005/03/21 13:51:21  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.6  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.5  2002/01/04 15:58:33  hdivoux
// LOG: More update for XER support.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:23:03  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:05:03  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: Tag.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime Tag class implementation.
//

#include <Asn.h>
#include <Tag.h>
#include <AsnException.h>

using namespace std;

namespace its {

Octets* 
Tag::Encode(const AsnOptions& asnOptions)
{
    vector<byte> array(ASN_MAX_LENGTH, 0x00U);

    int inc = 0;

    if (_tagClass == ASN_CLASS_UNIVERSAL)
    {
        array[0] = _tagClass << ASN_CLASS_SHIFT;
        array[0] |= _type << ASN_TYPE_SHIFT;
        array[0] |= (byte)_number;
        inc = 1;
    }
    else
    {
        array[0] = _tagClass << ASN_CLASS_SHIFT;
        array[0] |= _type << ASN_TYPE_SHIFT;
        if (_number < ASN_EXTENDED)
        {
            array[0] |= (byte)_number;
            inc = 1;
        }
        else
        {
            array[0] |= (byte)ASN_EXTENDED;
            if (_number <= ASN_OCTET_BITS)
            {
                array[1] = (byte)_number;
                array[1] &= ~ASN_OCTETS_FOLLOW;
                inc = 2;
            }
            else if ((_number >> ASN_LONG_SHIFT) <= ASN_OCTET_BITS)
            {
                array[1] = (byte)(((_number >> ASN_LONG_SHIFT) &
                                   ASN_OCTET_BITS) | ASN_OCTETS_FOLLOW);
                array[2] = (byte)(_number & ASN_OCTET_BITS);
                array[2] &= ~ASN_OCTETS_FOLLOW;
                inc = 3;
            }
            else if ((_number >> ASN_LONG_SHIFT * 2) <= ASN_OCTET_BITS)
            {
                array[1] = (byte)(((_number >> ASN_LONG_SHIFT * 2) &
                                   ASN_OCTET_BITS) | ASN_OCTETS_FOLLOW);
                array[2] = (byte)(((_number >> ASN_LONG_SHIFT) & 
                                   ASN_OCTET_BITS) | ASN_OCTETS_FOLLOW);
                array[3] = (byte)(_number & ASN_OCTET_BITS);
                array[3] &= ~ASN_OCTETS_FOLLOW;
                inc = 4;
            }
            else
            {
                array[1] = (byte)(((_number >> ASN_LONG_SHIFT * 3) &
                                   ASN_OCTET_BITS) | ASN_OCTETS_FOLLOW);
                array[2] = (byte)(((_number >> ASN_LONG_SHIFT * 2) &
                                   ASN_OCTET_BITS) | ASN_OCTETS_FOLLOW);
                array[3] = (byte)(((_number >> ASN_LONG_SHIFT) & 
                                   ASN_OCTET_BITS) | ASN_OCTETS_FOLLOW);
                array[4] = (byte)(_number & ASN_OCTET_BITS);
                array[4] &= ~ASN_OCTETS_FOLLOW;
                inc = 5;
            }
        }
    }

    Octets* result = new Octets(array, inc);

    return result;
}

void 
Tag::Decode(Octets& octets, const AsnOptions& asnOptions)
{
    if (!octets.IsIndexWithOffsetValid(0))
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_TAG_LENGTH, octets);
    }

    byte b = octets.GetOctetAtWithOffset(0);

    _tagClass = (byte)((b >> ASN_CLASS_SHIFT) & ASN_CLASS_BITS);
    _type = (byte)((b >> ASN_TYPE_SHIFT) & ASN_TYPE_BITS);
    _number = (unsigned long)(b & ASN_NUMBER_BITS);

    if (_tagClass == ASN_CLASS_UNIVERSAL)
    {
        if (!IsUniversal(_number))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_UNIVERSAL_NUMBER, octets);
        }
                
        octets.IncrementOffset();
    }
    else
    {
        if (_number != ASN_EXTENDED)
        {
            octets.IncrementOffset();
        }
        else
        {
            _number = 0;
            int i = 0;

            while (i < ASN_MAX_LENGTH)
            {
                i++;

                if (!octets.IsIndexWithOffsetValid(i))
                {
                    ASN_THROW_DECODE_ERROR(ASN_E_INVALID_TAG_LENGTH, octets);
                }

                _number |= (octets.GetOctetAtWithOffset(i) & ASN_OCTET_BITS) &
                          ASN_BYTE_MASK_IN_LONG;

                if ((octets.GetOctetAtWithOffset(i) & ASN_OCTETS_FOLLOW) != 0)
                {
                    _number <<= ASN_LONG_SHIFT;
                }
                else
                {
                    break;
                }
            }

            octets.IncrementOffset(i + 1);

        }
    }
}

void 
Tag::DecodePreserveOffset(Octets& octets, const AsnOptions& asnOptions)
{
    size_t offset = octets.GetOffset();

    Decode(octets, asnOptions);

    octets.SetOffset(offset);
}

bool 
Tag::IsUniversal(unsigned long number)
{
    if (number == ASN_BOOLEAN           ||
        number == ASN_INTEGER           ||
        number == ASN_BIT_STRING        ||
        number == ASN_OCTET_STRING      ||
        number == ASN_NULL              ||
        number == ASN_OBJECT_IDENTIFIER ||
        number == ASN_OBJECT_DESCRIPTOR ||
        number == ASN_EXTERNAL          ||
        number == ASN_REAL              ||
        number == ASN_ENUMERATED        ||
        number == ASN_ENCRYPTED         ||
        number == ASN_EMBEDDED_PDV      ||
        number == ASN_UTF8_STRING       ||
        number == ASN_RELATIVE_OID      ||
        number == ASN_SEQUENCE          ||
        number == ASN_SET               ||
        number == ASN_NUMERIC_STRING    ||
        number == ASN_PRINTABLE_STRING  ||
        number == ASN_TELETEX_STRING    ||
        number == ASN_VIDEOTEX_STRING   ||
        number == ASN_IA5_STRING        ||
        number == ASN_UTC_TIME          ||
        number == ASN_GENERALIZED_TIME  ||
        number == ASN_GRAPHICS_STRING   ||
        number == ASN_VISIBLE_STRING    ||
        number == ASN_GENERAL_STRING    ||
        number == ASN_UNIVERSAL_STRING  ||
        number == ASN_CHARACTER_STRING  ||
        number == ASN_BMP_STRING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//
// Constant definitions.
//

// Tag classes.
const byte Tag::ASN_CLASS_UNIVERSAL         = 0x00U;
const byte Tag::ASN_CLASS_APPLICATION       = 0x01U;
const byte Tag::ASN_CLASS_CONTEXT_SPECIFIC  = 0x02U;
const byte Tag::ASN_CLASS_PRIVATE           = 0x03U;

// Tag types.
const byte Tag::ASN_PRIMITIVE   = 0x00U;
const byte Tag::ASN_CONSTRUCTED = 0x01U;

// Universal tag numbers.
const unsigned long Tag::ASN_BOOLEAN            = 1;
const unsigned long Tag::ASN_INTEGER            = 2;
const unsigned long Tag::ASN_BIT_STRING         = 3;
const unsigned long Tag::ASN_OCTET_STRING       = 4;
const unsigned long Tag::ASN_NULL               = 5;
const unsigned long Tag::ASN_OBJECT_IDENTIFIER  = 6;
const unsigned long Tag::ASN_OBJECT_DESCRIPTOR  = 7;
const unsigned long Tag::ASN_EXTERNAL           = 8;
const unsigned long Tag::ASN_REAL               = 9;
const unsigned long Tag::ASN_ENUMERATED         = 10;
const unsigned long Tag::ASN_ENCRYPTED          = 11;
const unsigned long Tag::ASN_EMBEDDED_PDV       = 11;
const unsigned long Tag::ASN_UTF8_STRING        = 12;
const unsigned long Tag::ASN_RELATIVE_OID       = 13;
// 14 - 15 reserved for future versions.
const unsigned long Tag::ASN_SEQUENCE           = 16;
const unsigned long Tag::ASN_SET                = 17;
const unsigned long Tag::ASN_NUMERIC_STRING     = 18;
const unsigned long Tag::ASN_PRINTABLE_STRING   = 19;
const unsigned long Tag::ASN_TELETEX_STRING     = 20;
const unsigned long Tag::ASN_VIDEOTEX_STRING    = 21;
const unsigned long Tag::ASN_IA5_STRING         = 22;
const unsigned long Tag::ASN_UTC_TIME           = 23;
const unsigned long Tag::ASN_GENERALIZED_TIME   = 24;
const unsigned long Tag::ASN_GRAPHICS_STRING    = 25;
const unsigned long Tag::ASN_VISIBLE_STRING     = 26;
const unsigned long Tag::ASN_GENERAL_STRING     = 27;
const unsigned long Tag::ASN_UNIVERSAL_STRING   = 28;
const unsigned long Tag::ASN_CHARACTER_STRING   = 29;
const unsigned long Tag::ASN_BMP_STRING         = 30;
// 31 reserved for future versions.

// Helper constant for encoding/decoding extended tag numbers.
const unsigned long Tag::ASN_EXTENDED          = 31;

// Binary format helper constants.
const int  Tag::ASN_CLASS_SHIFT     = 6;
const byte Tag::ASN_CLASS_BITS      = 0x03U;
const int  Tag::ASN_TYPE_SHIFT      = 5;
const byte Tag::ASN_TYPE_BITS       = 0x01U;
const byte Tag::ASN_NUMBER_BITS     = 0x1FU;
const byte Tag::ASN_OCTET_BITS      = 0x7FU;
const byte Tag::ASN_OCTETS_FOLLOW   = 0x80U;
const int  Tag::ASN_MAX_LENGTH      = 5;
const int  Tag::ASN_LONG_SHIFT      = 7;

} // namespace its.

