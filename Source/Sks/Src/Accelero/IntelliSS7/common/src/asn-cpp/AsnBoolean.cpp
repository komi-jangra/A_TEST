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
// LOG: Revision 1.1  2007/03/30 04:53:11  cvsadmin
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
// LOG: Revision 5.9  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.8  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.7  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.6  2002/01/07 22:58:37  hdivoux
// LOG: First shot at XER encoding.
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

#ident "$Id: AsnBoolean.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime AsnBoolean class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnBoolean.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnBoolean::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBoolean staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnBoolean(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnBoolean::EncodeCheck(const AsnOptions& asnOptions)
{
    // Nothing to do.
}

Octets* 
AsnBoolean::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    vector<byte> array((size_t)ASN_BOOLEAN_LENGTH, 0x00U);

    if (_value)
    {
        array[0] = ASN_BOOLEAN_VALUE_TRUE;
    }
    else
    {
        array[0] = ASN_BOOLEAN_VALUE_FALSE;
    }

    Octets valOctets(array, (size_t)ASN_BOOLEAN_LENGTH);

    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);

    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnBoolean::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnBoolean::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);

    Length length(octets, asnOptions);
    if (length.GetLength() != ASN_BOOLEAN_LENGTH)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BOOLEAN_LENGTH, octets);
    }
    else
    {
        if (!octets.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BOOLEAN_LENGTH, octets);
        }

        byte b = octets.GetOctetAtWithOffset(0);

        if (b == ASN_BOOLEAN_VALUE_FALSE)
        {
            _value = false;
        }
        else
        {
            _value = true;
        }

        octets.IncrementOffset((size_t)ASN_BOOLEAN_LENGTH);
    }

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnBoolean::InternalEncodePer(
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
AsnBoolean::InternalDecodePer(
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
AsnBoolean::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    if (_value)
    {
        str += "TRUE";
    }
    else
    {
        str += "FALSE";
    }

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnBoolean::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnBoolean::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsBoolean(characters, asnOptions);

    string str = content.GetString();

    if (str == "TRUE" || str == "true")
    {
        _value = true;
    }
    else if (str == "FALSE" || str == "false")
    {
        _value = false;
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnBoolean::Equals(const AsnObject& rhs) const
{ 
    const AsnBoolean* other = static_cast<const AsnBoolean*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (_value == other->_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void 
AsnBoolean::Print(ostream& os, size_t level) const
{
    string levelShift  = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";

    if (_value)
    {
        os << "TRUE";
    }
    else
    {
        os << "FALSE";
    }
    os << " ]" << endl;
}


// Relevant constant definitions.
const long AsnBoolean::ASN_BOOLEAN_LENGTH      = 1;
const byte AsnBoolean::ASN_BOOLEAN_VALUE_TRUE  = 0xFFU;
const byte AsnBoolean::ASN_BOOLEAN_VALUE_FALSE = 0x00U;


} // namespace its.

