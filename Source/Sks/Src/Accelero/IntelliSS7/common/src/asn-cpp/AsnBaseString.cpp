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
// LOG: Revision 1.1  2007/03/30 04:53:09  cvsadmin
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
// LOG: Revision 1.5  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 1.4  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 1.3  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 1.2  2002/01/07 22:58:37  hdivoux
// LOG: First shot at XER encoding.
// LOG:
// LOG: Revision 1.1  2002/01/02 23:36:32  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnBaseString.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime AsnBaseString class implementation.
//

#include <stdio.h>

#include <Asn.h>
#include <AsnXml.h>
#include <AsnBaseString.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnBaseString::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBaseString staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnBaseString(&staticDesc));
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnBaseString::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsEncodeIgnoreBaseStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BASE_STRING_SIZE);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BASE_STRING_SIZE);
        }
    }
}

Octets* 
AsnBaseString::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    vector<byte> array((byte*)(&_data[0]), (byte*)(&_data[0] + _data.size()));

    Octets valOctets(array);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnBaseString::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreBaseStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_BASE_STRING_SIZE, octets);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_BASE_STRING_SIZE, octets);
        }
    }
}

void 
AsnBaseString::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    if (tag.GetType() == Tag::ASN_CONSTRUCTED)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_CONSTRUCTED_BASE_STRING, octets);
    }

    Length length(octets, asnOptions);
    if (length.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(
            ASN_E_INDEFINITE_BASE_STRING_LENGTH, 
            octets);
    }
    else
    {
        _data.erase(_data.begin(), _data.end());
        _data.reserve((size_t)length.GetLength());

        for (int i = 0; i < length.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_BASE_STRING_LENGTH,
                    octets);
            }

            byte b = octets.GetOctetAtWithOffset(i);
            _data.append(1, (char)b);
        }

        octets.IncrementOffset((size_t)length.GetLength());
    }

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnBaseString::InternalEncodePer(
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
AsnBaseString::InternalDecodePer(
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
AsnBaseString::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    str += _data;

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnBaseString::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreBaseStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_BASE_STRING_SIZE, 
                characters);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_BASE_STRING_SIZE, 
                characters);
        }
    }
}

void 
AsnBaseString::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsBaseString(characters, asnOptions);

    _data = content.GetString();

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnBaseString::Equals(const AsnObject& rhs) const
{ 
    const AsnBaseString* other = 
        static_cast<const AsnBaseString*>(&rhs);
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
AsnBaseString::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ \"";
    os << _data;
    os << "\" ]" << endl;
}

} // namespace its.
