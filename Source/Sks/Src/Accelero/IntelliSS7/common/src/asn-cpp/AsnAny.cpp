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
// LOG: Revision 1.1  2007/03/30 04:53:08  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:21  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:17  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.7  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
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
// LOG: Revision 5.3  2001/12/24 21:05:02  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnAny.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime AsnAny class implementation.
//

#include <Asn.h>
#include <AsnAny.h>
#include <AsnXml.h>
#include <AsnException.h>

using namespace std;

// Helper function for parsing.
static inline bool 
IsLeftAngleBracket(char c)
{
    return c == '<';
}

namespace its {

AsnDescObject* 
AsnAny::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescAny staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnAny(&staticDesc));
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

AsnAny& 
AsnAny::operator=(const AsnAny& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        if (rhs._any != NULL)
        {
            if (_any != NULL)
            {
                if (_deleteSubcomponentsAutomatically)
                {
                    delete _any;
                }
            }

            if (rhs._deleteSubcomponentsAutomatically)
            {
                _any = rhs._any->Clone();
            }
            else
            {
                _any = rhs._any;
            }
        }
        else
        {
            if (_any != NULL)
            {
                if (_deleteSubcomponentsAutomatically)
                {
                    delete _any;
                }
            }

            _any = NULL;
        }

        Assign(rhs); // MUST not be done before.

        _decodedOctets          = rhs._decodedOctets;
        _decodedCharacters      = rhs._decodedCharacters;
        _decodedTag             = rhs._decodedTag;
        _decodedLength          = rhs._decodedLength;
        _decodedOctetsData      = rhs._decodedOctetsData;
        _decodedCharactersData  = rhs._decodedCharactersData;
        
        return *this;
    }
}

void 
AsnAny::EncodeCheck(const AsnOptions& asnOptions)
{
    if (_any == NULL)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_NO_ANY_PRESENT);
    }
}

Octets* 
AsnAny::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    Octets* anyOctets = NULL;

    if (_decodedOctets)
    {
        // Special case if ANY already decoded: just re-encode.
        anyOctets = new Octets();
        *anyOctets += _decodedOctetsData;
    }
    else
    {
        // Standard case.
        EncodeCheck(asnOptions);
        anyOctets = _any->InternalEncodeBer(
                                    asnOptions,
                                    level + 1,
                                    _any->GetPolymorphDescription());
    }

    ITS_ASSERT(anyOctets != NULL);
    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    if (_description->TagLevelNumber() == 1)
    {
        Octets* result = anyOctets;
        ITS_ENSURE(result != NULL);
        return result;
    }
    else
    {
        // Next call is valid since ASN.1 Object description tag stack is used
        // (contains one or more tags as description->TagLevelNumber() >= 2). 
        Octets* result = EncodeTagLengthValue(*anyOctets, asnOptions);
        delete anyOctets;
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnAny::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnAny::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    DecodeRemoveExtraTagLength(octets, asnOptions);

    _decodedTag.Decode(octets, asnOptions);
    _decodedLength.Decode(octets, asnOptions);

    if (_decodedLength.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_ANY_LENGTH, octets);
    }
    else
    {
        vector<byte> array;
        array.reserve(_decodedLength.GetLength());

        for (int i = 0; i < _decodedLength.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(ASN_E_INVALID_ANY_LENGTH, octets);
            }

            byte b = octets.GetOctetAtWithOffset(i);
            array.push_back(b);
        }

        Octets* tagOctets = _decodedTag.Encode(asnOptions);
        Octets* lengthOctets = _decodedLength.Encode(asnOptions);
        Octets valOctets(array);

        _decodedOctetsData =  *tagOctets;
        _decodedOctetsData += *lengthOctets;
        _decodedOctetsData += valOctets;

        delete tagOctets;
        delete lengthOctets;

        octets.IncrementOffset((size_t)_decodedLength.GetLength());
    }

    DecodeCheck(octets, asnOptions);

    _decodedOctets = true;
}

Octets* 
AsnAny::InternalEncodePer(
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
AsnAny::InternalDecodePer(
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
AsnAny::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    XmlWriteNewLine(str, asnOptions);

    if (_decodedCharacters)
    {
        // Special case if ANY already decoded: just re-encode.
        str += _decodedCharactersData.GetString();
    }
    else
    {
        // Standard case.
        EncodeCheck(asnOptions);
        Characters* anyCharacters = 
            _any->InternalEncodeToXml(
                asnOptions,
                level + 1, 
                _any->GetPolymorphDescription());
        str += anyCharacters->GetString();
        delete anyCharacters;
    }

    XmlWriteNewLine(str, asnOptions);

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnAny::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnAny::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    XmlStartTag startTag(*this);
    startTag.DecodePreserveOffset(characters, asnOptions);

    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    bool keepOn = true;

    string str;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_ANY_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(0);

        if (IsLeftAngleBracket(c))
        {
            XmlEndTag endTag(*this);
            endTag.TryDecodePreserveOffset(characters, asnOptions);

            if (startTag.GetName() == endTag.GetName())
            {
                keepOn = false;
            }
            else
            {
                keepOn = true;
                str += c;
            }
        }
        else
        {
            str += c;
        }

        if (keepOn)
        {
            characters.IncrementOffset();
        }
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);

    _decodedCharactersData.SetString(str);
    _decodedCharacters = true;
}

bool 
AsnAny::Equals(const AsnObject& rhs) const
{ 
    const AsnAny* other = static_cast<const AsnAny*>(&rhs);
    // Useful only if dynamic cast is used.    
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (_decodedOctets != other->_decodedOctets)
    {
        return false;
    }

    if (_decodedCharacters != other->_decodedCharacters)
    {
        return false;
    }

    if (!(_decodedTag == other->_decodedTag))
    {
        return false;
    }

    if (!(_decodedLength == other->_decodedLength))
    {
        return false;
    }

    if (!(_decodedOctetsData == other->_decodedOctetsData))
    {
        return false;
    }

    if (!(_decodedCharactersData == other->_decodedCharactersData))
    {
        return false;
    }

    if (_any == NULL && other->_any == NULL)
    {
        return true;
    }
    else if (_any == NULL && other->_any != NULL)
    {
        return false;
    }
    else if (_any != NULL && other->_any == NULL)
    {
        return false;
    }
    else
    {
        return _any->Equals(*(other->_any));
    }
}

void 
AsnAny::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "{" << endl;

    if (_any != NULL)
    {
        _any->Print(os, level + 1);
    }
    else
    {
        if (_decodedOctets)
        {
            _decodedOctetsData.Print(os, level + 1);
        }
        else if (_decodedCharacters)
        {
            _decodedCharactersData.Print(os, level + 1);
        }
        else
        {
            os << endl;
        }
    }

    os << levelShift;
    os << "}" << endl;
}

} // namespace its.

