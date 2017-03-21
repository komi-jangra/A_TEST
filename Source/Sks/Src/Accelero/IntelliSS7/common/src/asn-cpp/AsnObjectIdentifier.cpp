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
// LOG: Revision 1.1.1.1  2007/08/03 06:49:02  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1  2007/03/30 04:53:40  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:22  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:20  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
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

#ident "$Id: AsnObjectIdentifier.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime AsnObjectIdentifier class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnObjectIdentifier.h>
#include <AsnException.h>

using namespace std;

namespace its {

// Constants for encode/decode checks.
const long OID_FIRST_CPT_CCITT_VALUE            = 0;
const long OID_FIRST_CPT_ISO_VALUE              = 1;
const long OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE  = 2;
const long OID_SECOND_CPT_MINIMUM_VALUE         = 0;
const long OID_SECOND_CPT_MAXIMUM_VALUE         = 39;
const size_t OID_MINIMUM_NUMBER_OF_CPTS         = 2;

// Constants for encode/decode.
const byte OID_FIRST_SUBID_DISC     = 40U;
const byte OID_SUBID_INVALID_VALUE  = 0x80U;
const byte OID_OCTET_BITS           = 0x7FU;
const byte OID_OCTETS_FOLLOW        = 0x80U;
const byte OID_LONG_SHIFT           = 7;

AsnDescObject* 
AsnObjectIdentifier::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescObjectIdentifier staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnObjectIdentifier(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnObjectIdentifier::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetSize() < OID_MINIMUM_NUMBER_OF_CPTS)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID);
    }

    long firstComponentValue = _data[0];

    if (firstComponentValue != OID_FIRST_CPT_CCITT_VALUE              &&
        firstComponentValue != OID_FIRST_CPT_ISO_VALUE                &&
        firstComponentValue != OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID);
    }

    long secondComponentValue = _data[1];

    if (secondComponentValue < OID_SECOND_CPT_MINIMUM_VALUE ||
        secondComponentValue > OID_SECOND_CPT_MAXIMUM_VALUE)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID);
    }

    for (size_t i = 2; i < GetSize(); i++)
    {
        long componentValue = _data[i];

        if (componentValue < 0)
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID);
        }
    }
}

Octets* 
AsnObjectIdentifier::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    vector<byte> array;
    array.reserve(GetSize() * ASN_BYTES_PER_LONG);
    ITS_ASSERT(GetSize() >= 2);

    byte firstSubid = (byte)(_data[0] * OID_FIRST_SUBID_DISC + _data[1]);
    array.push_back(firstSubid);

    for (size_t i = 2; i < GetSize(); i++)
    {
        long value = _data[i];

        byte subid = 0x00U;

        if (value <= OID_OCTET_BITS)
        {
            subid = (byte)value;
            subid &= ~OID_OCTETS_FOLLOW;
            array.push_back(subid);
        }
        else if ((value >> OID_LONG_SHIFT) <= OID_OCTET_BITS)
        {
            subid = (byte)(((value >> OID_LONG_SHIFT) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array.push_back(subid);
            subid = (byte)(value & OID_OCTET_BITS);
            subid &= ~OID_OCTETS_FOLLOW;
            array.push_back(subid);
        }
        else if ((value >> OID_LONG_SHIFT * 2) <= OID_OCTET_BITS)
        {
            subid = (byte)(((value >> OID_LONG_SHIFT * 2) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array.push_back(subid);
            subid = (byte)(((value >> OID_LONG_SHIFT) & 
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array.push_back(subid);
            subid = (byte)(value & OID_OCTET_BITS);
            subid &= ~OID_OCTETS_FOLLOW;
            array.push_back(subid);
        }
        else
        {
            subid = (byte)(((value >> OID_LONG_SHIFT * 3) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array.push_back(subid);
            subid = (byte)(((value >> OID_LONG_SHIFT * 2) &
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array.push_back(subid);
            subid = (byte)(((value >> OID_LONG_SHIFT) & 
                                OID_OCTET_BITS) | OID_OCTETS_FOLLOW);
            array.push_back(subid);
            subid = (byte)(value & OID_OCTET_BITS);
            subid &= ~OID_OCTETS_FOLLOW;
            array.push_back(subid);
        }
    }

    Octets valOctets(array);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnObjectIdentifier::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetSize() < OID_MINIMUM_NUMBER_OF_CPTS)
    {
        ASN_THROW_DECODE_ERROR(
            ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID,
            octets);
    }

    long firstComponentValue = _data[0];

    if (firstComponentValue != OID_FIRST_CPT_CCITT_VALUE              &&
        firstComponentValue != OID_FIRST_CPT_ISO_VALUE                &&
        firstComponentValue != OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE)
    {
        ASN_THROW_DECODE_ERROR(
            ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID,
            octets);
    }

    long secondComponentValue = _data[1];

    if (secondComponentValue < OID_SECOND_CPT_MINIMUM_VALUE ||
        secondComponentValue > OID_SECOND_CPT_MAXIMUM_VALUE)
    {
        ASN_THROW_DECODE_ERROR(
            ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID, 
            octets);
    }

    for (size_t i = 2; i < GetSize(); i++)
    {
        long componentValue = _data[i];

        if (componentValue < 0)
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID,
                octets);
        }
    }
}

void 
AsnObjectIdentifier::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    if (tag.GetType() == Tag::ASN_CONSTRUCTED)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_CONSTRUCTED_OID, octets);
    }

    Length length(octets, asnOptions);

    if (length.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_OID_LENGTH, octets);
    }
    else if (length.GetLength() == 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_NULL_OID_LENGTH, octets);
    }
    else
    {
        _data.erase(_data.begin(), _data.end());

        // Reserve for greatest possible case (to avoid reallocations).
        _data.reserve((size_t)length.GetLength() + 1);

        if (!octets.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_OID_LENGTH, octets);
        }

        // First octet.

        byte b = octets.GetOctetAtWithOffset(0);

        byte firstCptVal    = 0;
        byte secondCptVal   = 0;

        ITS_ASSERT(OID_FIRST_CPT_ISO_VALUE *
                    OID_FIRST_SUBID_DISC +
                        OID_SECOND_CPT_MAXIMUM_VALUE +
                            1 == 
                                OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE *
                                    OID_FIRST_SUBID_DISC);

        if (b > (byte)(
                    OID_FIRST_CPT_ISO_VALUE *
                        OID_FIRST_SUBID_DISC + 
                            OID_SECOND_CPT_MAXIMUM_VALUE))
        {
            firstCptVal = (byte)OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE;

            if (b >= (byte)(
                        OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE *
                            OID_FIRST_SUBID_DISC))
            {
                secondCptVal = 
                    (byte)(
                        b - 
                            OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE *
                                OID_FIRST_SUBID_DISC);
            }
            else
            {
                bool must_not_be_reached = false;
                ITS_ASSERT(must_not_be_reached);
            }
        }
        else
        {
            firstCptVal = (byte)(b / OID_FIRST_SUBID_DISC);
            secondCptVal = (byte)(b % OID_FIRST_SUBID_DISC);
        }

        _data.push_back(firstCptVal);
        _data.push_back(secondCptVal);

        // Remaining octets.

        vector<byte> array;
        array.reserve((size_t)length.GetLength());

        for (int i = 1; i < (int)length.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(ASN_E_INVALID_OID_LENGTH, octets);
            }

            byte b = octets.GetOctetAtWithOffset(i);
            array.push_back(b);
        }

        for (size_t j = 0; j < array.size(); j++)
        {
            long value = 0;
            int numberOfShifts = 0;
            bool firstSubidentifier = true;
            bool stop = false;

            while(!stop)
            {
                byte b = array[j];

                if (firstSubidentifier)
                {
                    if (b == OID_SUBID_INVALID_VALUE)
                    {
                        ASN_THROW_DECODE_ERROR(
                            ASN_E_OID_CPT_VALUE_INVALID, 
                            octets);
                    }

                    firstSubidentifier = false;
                }

                value |= (b & OID_OCTET_BITS) & ASN_BYTE_MASK_IN_LONG;

                if (b & OID_OCTETS_FOLLOW)
                {
                    value <<= OID_LONG_SHIFT;

                    numberOfShifts++;

                    if (numberOfShifts >= ASN_BYTES_PER_LONG)
                    {
                        ASN_THROW_DECODE_ERROR(
                            ASN_E_OID_CPT_VALUE_OUT_OF_RANGE,
                            octets);
                    }

                    j++;

                    if (j >= array.size())
                    {
                        ASN_THROW_DECODE_ERROR(
                            ASN_E_INVALID_OID_LENGTH, 
                            octets);
                    }
                }
                else
                {
                    stop = true;
                }                
            }

            _data.push_back(value);
        }

        octets.IncrementOffset((size_t)length.GetLength());
    }

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnObjectIdentifier::InternalEncodePer(
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
AsnObjectIdentifier::InternalDecodePer(
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
AsnObjectIdentifier::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    char buffer[16];

    for (size_t i = 0; i < _data.size(); i++)
    {
        if (i != 0)
        {
            str += '.';
        }

        memset(buffer, 0, 16);
        sprintf(buffer, "%ld", _data[i]);
        str += buffer;
    }

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnObjectIdentifier::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetSize() < OID_MINIMUM_NUMBER_OF_CPTS)
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_INVALID_NUMBER_OF_CPTS_IN_OID,
            characters);
    }

    long firstComponentValue = _data[0];

    if (firstComponentValue != OID_FIRST_CPT_CCITT_VALUE              &&
        firstComponentValue != OID_FIRST_CPT_ISO_VALUE                &&
        firstComponentValue != OID_FIRST_CPT_JOINT_ISO_CCITT_VALUE)
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_INVALID_FIRST_CPT_VALUE_IN_OID,
            characters);
    }

    long secondComponentValue = _data[1];

    if (secondComponentValue < OID_SECOND_CPT_MINIMUM_VALUE ||
        secondComponentValue > OID_SECOND_CPT_MAXIMUM_VALUE)
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_INVALID_SECOND_CPT_VALUE_IN_OID, 
            characters);
    }

    for (size_t i = 2; i < GetSize(); i++)
    {
        long componentValue = _data[i];

        if (componentValue < 0)
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_NEGATIVE_CPT_VALUE_IN_OID,
                characters);
        }
    }
}

void 
AsnObjectIdentifier::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsObjectIdentifier(characters, asnOptions);

    string str = content.GetString();

    _data.erase(_data.begin(), _data.end());

    string  cptStr;
    long    cptVal;

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            int numFields = sscanf(cptStr.c_str(), "%ld", &cptVal);
            ITS_ASSERT(numFields == 1);
            _data.push_back(cptVal);
            cptStr.erase(cptStr.begin(), cptStr.end());
        }
        else
        {
            cptStr += str[i];
        }
    }

    // Last one.
    int numFields = sscanf(cptStr.c_str(), "%ld", &cptVal);
    ITS_ASSERT(numFields == 1);
    _data.push_back(cptVal);

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnObjectIdentifier::Equals(const AsnObject& rhs) const
{ 
    const AsnObjectIdentifier* other = 
        static_cast<const AsnObjectIdentifier*>(&rhs);
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
AsnObjectIdentifier::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";

    // TODO: To be improved (30 chararcters max per line).

    for (size_t i = 0; i < GetSize(); i++)
    {
        os << _data[i];
        
        if (i != GetSize() - 1)
        {
            os << ", ";
        }
    }

    os << " ]" << endl;
}

} // namespace its.


