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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:12  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1  2007/03/30 04:53:10  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:21  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:18  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.8  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.7  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.6  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.5  2002/01/04 15:58:32  hdivoux
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

#ident "$Id: AsnBitString.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime BitString class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnBitString.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnBitString::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

    if (initialized)
    {
        ITS_ENSURE(result != NULL);
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
    else
    {
        ITS_ASSERT(result == NULL);
        staticDesc.SetCloneForFactory(new AsnBitString(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnBitString::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsEncodeIgnoreBitStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE);
        }
    }
}

Octets* 
AsnBitString::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    long numberOfBits = 0;
    vector<byte> arrayBits;
    VectorBoolToBits(_data, numberOfBits, arrayBits);
    long finalOctetUnusedBits = 0;

    if (numberOfBits % ASN_BITS_PER_BYTE != 0)
    {
        finalOctetUnusedBits =
            ASN_BITS_PER_BYTE -
                (numberOfBits %
                    ASN_BITS_PER_BYTE);
    }

    ITS_ASSERT(finalOctetUnusedBits >= 0);
    ITS_ASSERT(finalOctetUnusedBits < ASN_BITS_PER_BYTE);

    vector<byte> array;
    array.reserve(arrayBits.size() + 1);
    array.push_back((byte)finalOctetUnusedBits);
    array.insert(array.end(), arrayBits.begin(), arrayBits.end());
    ITS_ASSERT(array.size() == arrayBits.size() + 1);

    Octets valOctets(array);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnBitString::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreBitStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE, octets);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE, octets);
        }
    }
}

void 
AsnBitString::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    if (tag.GetType() == Tag::ASN_CONSTRUCTED)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_CONSTRUCTED_BIT_STRING, octets);
    }

    Length length(octets, asnOptions);
    if (length.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_BIT_STRING_LENGTH, octets);
    }
    else if (length.GetLength() == 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_NULL_BIT_STRING_LENGTH, octets);
    }
    else
    {
        _data.erase(_data.begin(), _data.end());

        if (!octets.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_LENGTH, octets);
        }

        byte b = octets.GetOctetAtWithOffset(0);
        long finalOctetUnusedBits = (long)b;
        ITS_ASSERT(finalOctetUnusedBits >= 0);

        if (finalOctetUnusedBits >= ASN_BITS_PER_BYTE)
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
                octets);
        }

        vector<byte> arrayBits;
        arrayBits.reserve(length.GetLength() - 1);

        for (int i = 1; i < length.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_LENGTH, 
                    octets);
            }

            arrayBits.push_back(octets.GetOctetAtWithOffset(i));
        }

        if (arrayBits.size() == 0 && finalOctetUnusedBits != 0)
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
                octets);
        }

        long numberOfBits = 
                arrayBits.size() *
                    ASN_BITS_PER_BYTE -
                        finalOctetUnusedBits;
        ITS_ASSERT(numberOfBits >= 0);
        BitsToVectorBool(numberOfBits, arrayBits, _data);
        octets.IncrementOffset((size_t)length.GetLength());
    }

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnBitString::InternalEncodePer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
    return NULL;
}

void 
AsnBitString::InternalDecodePer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
    DecodeCheck(octets, asnOptions);
}

Characters* 
AsnBitString::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    for (size_t i = 0; i < _data.size(); i++)
    {
        if (_data[i])
        {
            str += '1';
        }
        else
        {
            str += '0';
        }
    }

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnBitString::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreBitStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_SIZE, 
                characters);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_SIZE, 
                characters);
        }
    }
}

void 
AsnBitString::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsBitString(characters, asnOptions);

    string str = content.GetString();

    _data.erase(_data.begin(), _data.end());
    _data.reserve(str.size());

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '1')
        {
            _data.push_back(true);
        }
        else
        {
            ITS_ASSERT(str[i] == '0');
            _data.push_back(false);
        }
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnBitString::Equals(const AsnObject& rhs) const
{ 
    const AsnBitString* other = static_cast<const AsnBitString*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (_data == other->_data)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void 
AsnBitString::Print(ostream& os, size_t level) const
{
    static const int ROW_LENGTH = 30;

    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";

    int divisor = ROW_LENGTH;

    ITS_ASSERT(divisor > 1);

    int quotient  = GetSize() / divisor;
    int remainder = GetSize() % divisor;

    int i = 0;
        
    for (i = 0; i < quotient; i++)
    {
        for (int j = 0; j < divisor; j++)
        {
            if (_data[i * divisor + j])
            {
                os << "1";
            }
            else
            {
                os << "0";
            }
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
        if (_data[i * divisor + j])
        {
            os << "1";
        }
        else
        {
            os << "0";
        }
    }

    if (remainder != 0 && quotient != 0)
    {
        for (int j = 0; j < divisor - remainder; j++)
        {
            os << " ";
        }
    }

    os << " ]" << endl;
}

void 
AsnBitString::VectorBoolToBits(
                            const vector<bool>& boolVect,
                            long& numberOfBits,
                            vector<byte>& byteVect)
{
    byteVect.erase(byteVect.begin(), byteVect.end());
    numberOfBits = boolVect.size();

    int numberOfBytes = numberOfBits / ASN_BITS_PER_BYTE;
    if (numberOfBits % ASN_BITS_PER_BYTE > 0)
    {
        numberOfBytes += 1;
    }

    byteVect.reserve(numberOfBytes);

    int n = 0;  // Bit number starting from zero.
    for (int i = 0; i < numberOfBytes; i++)
    {
        byte b = 0x00U;

        for (int j = ASN_BITS_PER_BYTE - 1; j >= 0; j--)
        {
            if (boolVect[n])
            {
                b |= 0x01U << j;
            }

            n++;

            if (n >= numberOfBits)
            {
                break;
            }
        }

        byteVect.push_back(b);
    }
}

void 
AsnBitString::BitsToVectorBool(
                            long numberOfBits,
                            const vector<byte>& byteVect,
                            vector<bool>& boolVect)
{
    ITS_REQUIRE(numberOfBits >= 0);

    unsigned int requiredNumberOfBytes = numberOfBits / ASN_BITS_PER_BYTE;
    if (numberOfBits % ASN_BITS_PER_BYTE > 0)
    {
        requiredNumberOfBytes += 1;
    }

    ITS_REQUIRE(byteVect.size() == requiredNumberOfBytes);

    boolVect.erase(boolVect.begin(), boolVect.end());
    boolVect.reserve(numberOfBits);

    int n = 0;  // Bit number starting from zero.
    for (size_t i = 0; i < byteVect.size(); i++)
    {
        byte b = byteVect[i];

        for (int j = ASN_BITS_PER_BYTE - 1; j >= 0; j--)
        {
            if ((b & (0x01U << j)) != 0x00U)
            {
                boolVect.push_back(true);
            }
            else
            {
                boolVect.push_back(false);
            }

            n++;

            if (n >= numberOfBits)
            {
                break;
            }
        }
    }
}

} // namespace its.


