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
// LOG: Revision 1.1  2007/03/30 04:53:39  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:22  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.3  2005/03/21 13:51:19  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1.4.1  2003/07/07 12:24:46  mmanikandan
// LOG: License check capability is added.
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.7  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.6  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.5  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.4  2002/01/07 22:58:37  hdivoux
// LOG: First shot at XER encoding.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:05:03  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnObject.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime AsnObject class implementation.
//

#include <Asn.h>
#include <Tag.h>
#include <Length.h>
#include <AsnXml.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnException.h>

using namespace std;

namespace its {

Octets*
AsnObject::Encode(const AsnOptions& asnOptions)
{
    switch (asnOptions.GetEncodingRules())
    {
    case AsnOptions::ASN_BER_ENCODING_RULES:

        return InternalEncodeBer(asnOptions, 0, GetPolymorphDescription());

    case AsnOptions::ASN_PER_BASIC_ALIGNED_ENCODING_RULES:
    case AsnOptions::ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES:
    case AsnOptions::ASN_PER_BASIC_UNALIGNED_ENCODING_RULES:
    case AsnOptions::ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES:

        return InternalEncodePer(asnOptions, 0, GetPolymorphDescription());

    case AsnOptions::ASN_XER_ENCODING_RULES:
        {
            bool invalid_member_function_usage = false;
            ITS_ASSERT(invalid_member_function_usage);

            return NULL;
        }

    default:
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);

            return NULL;
        }
    }
}

void
AsnObject::Decode(Octets& octets, const AsnOptions& asnOptions)
{
    switch (asnOptions.GetEncodingRules())
    {
    case AsnOptions::ASN_BER_ENCODING_RULES:

        InternalDecodeBer(octets, asnOptions, 0, GetPolymorphDescription());
        break;

    case AsnOptions::ASN_PER_BASIC_ALIGNED_ENCODING_RULES:
    case AsnOptions::ASN_PER_CANONICAL_ALIGNED_ENCODING_RULES:
    case AsnOptions::ASN_PER_BASIC_UNALIGNED_ENCODING_RULES:
    case AsnOptions::ASN_PER_CANONICAL_UNALIGNED_ENCODING_RULES:

        InternalDecodePer(octets, asnOptions, 0, GetPolymorphDescription());
        break;

    case AsnOptions::ASN_XER_ENCODING_RULES:
        {
            bool invalid_member_function_usage = false;
            ITS_ASSERT(invalid_member_function_usage);
            break;
        }

    default:
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
            break;
        }
    }
}

Characters* 
AsnObject::EncodeToXml(const AsnOptions& asnOptions)
{
    return InternalEncodeToXml(
                asnOptions,
                0,
                GetPolymorphDescription());
}

void 
AsnObject::DecodeFromXml(Characters& characters, const AsnOptions& asnOptions)
{
    InternalDecodeFromXml(
                characters,
                asnOptions,
                0,
                GetPolymorphDescription());
}

// Helper function to encode according to the format TLTLTL...TLV.
// Use description tag stack.
Octets* 
AsnObject::EncodeTagLengthValue(
                            const Octets& value,
                            const AsnOptions& asnOptions)
{
    ITS_ASSERT(_description != NULL);
    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    const vector<Tag*>& tagStack = _description->TagStack();

    vector<Tag*>::const_reverse_iterator iter = tagStack.rbegin();

    ITS_ASSERT(iter != tagStack.rend());

    // Use class Tag assignment operator.

    Tag tag = **iter;

    Octets* tagOctets = tag.Encode(asnOptions);

    Length length(value.GetLength());

    Octets* lengthOctets = length.Encode(asnOptions);

    Octets* result = new Octets();

    *result += *tagOctets;
    *result += *lengthOctets;
    *result += value;

    delete tagOctets;
    delete lengthOctets;

    iter++;

    // If iter == tagStack.rend() then standard TLV format is used else
    // TLTLTL..TLV format is used (case of non implicit tagging).

    while (iter != tagStack.rend())
    {
        Octets* valOctets = result;

        // Use class Tag assignment operator.

        Tag tag = **iter;

        Octets* tagOctets = tag.Encode(asnOptions);
        Length length(valOctets->GetSize());
        Octets* lengthOctets = length.Encode(asnOptions);
        
        result = new Octets();

        *result += *tagOctets;
        *result += *lengthOctets;
        *result += *valOctets;

        delete tagOctets;
        delete lengthOctets;
        delete valOctets;

        iter++;
    }   

    ITS_ENSURE(result != NULL);
    return result;
}

// Helper function to remove TLTLTL... if TLTLTL...TLV format is used.
void 
AsnObject::DecodeRemoveExtraTagLength(
                                Octets& octets,
                                const AsnOptions& asnOptions)
{
    ITS_ASSERT(_description != NULL);
    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    if (_description->TagLevelNumber() == 1)
    {
        // Standard TLV format used.
        return;
    }
    else
    {
        // TLTLTL..TLV format used. Remove TLTLTL.. and keep TLV.
        ITS_ASSERT(_description->TagLevelNumber() >= 2);

        // Keep TLV => remove description->TagLevelNumber() - 1 TL(s).
        for (size_t i = 1; i < _description->TagLevelNumber(); i++)
        {
            Tag tag(octets, asnOptions);

            Length length(octets, asnOptions);

            if (length.IsIndefinite())
            {
                ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_LENGTH, octets);
            }
        }
    }
}

// Helper function to encode XML element start tag.
void
AsnObject::EncodeXmlElementStartTag(
                                string& str,
                                const AsnOptions& asnOptions, 
                                size_t level,
                                const AsnDescObject& description)
{
    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            XmlWriteElementStartTag(
                str, 
                description.GetTypeName(), 
                asnOptions);
        }
        else
        {
            XmlWriteElementStartTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()), 
                asnOptions);
        }
    }
    else if (description.IsNamedType())
    {
        XmlWriteElementStartTag(
            str, 
            description.GetNamedTypeName(), 
            asnOptions);
    }
    else
    {
        if (description.HasTypeName())
        {
            XmlWriteElementStartTag(
                str, 
                description.GetTypeName(), 
                asnOptions);
        }
        else
        {
            XmlWriteElementStartTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()),
                asnOptions);
        }
    }
}

// Helper function to encode XML element end tag.
void
AsnObject::EncodeXmlElementEndTag(
                                string& str,
                                const AsnOptions& asnOptions, 
                                size_t level,
                                const AsnDescObject& description)
{
    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            XmlWriteElementEndTag(
                str,
                description.GetTypeName(),
                asnOptions);
        }
        else
        {
            XmlWriteElementEndTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()), 
                asnOptions);
        }
    }
    else if (description.IsNamedType())
    {
        XmlWriteElementEndTag(
            str, 
            description.GetNamedTypeName(),
            asnOptions);
    }
    else
    {
        if (description.HasTypeName())
        {
            XmlWriteElementEndTag(
                str,
                description.GetTypeName(),
                asnOptions);
        }
        else
        {
            XmlWriteElementEndTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()),
                asnOptions);
        }
    }
}

// Helper function to decode XML element start tag.
void
AsnObject::DecodeXmlElementStartTag(
                                Characters& characters,
                                const AsnOptions& asnOptions, 
                                size_t level,
                                const AsnDescObject& description)
{
    string expectedTagName;

    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            expectedTagName = description.GetTypeName();
        }
        else
        {
            expectedTagName = XmlReplaceUnderscoreByDash(GetName());
        }
    }
    else if (description.IsNamedType())
    {
            expectedTagName = description.GetNamedTypeName();
    }
    else
    {
        if (description.HasTypeName())
        {
            expectedTagName = description.GetTypeName();
        }
        else
        {
            expectedTagName = XmlReplaceUnderscoreByDash(GetName());
        }
    }

    XmlStartTag startTag(*this);

    startTag.Decode(characters, asnOptions);

    if (expectedTagName != startTag.GetName())
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_START_TAG, 
            characters);
    }
    else
    {
        // Nothing to do.
    }
}

// Helper function to decode XML element end tag.
void
AsnObject::DecodeXmlElementEndTag(
                                Characters& characters,
                                const AsnOptions& asnOptions, 
                                size_t level,
                                const AsnDescObject& description)
{
    string expectedTagName;

    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            expectedTagName = description.GetTypeName();
        }
        else
        {
            expectedTagName = XmlReplaceUnderscoreByDash(GetName());
        }
    }
    else if (description.IsNamedType())
    {
        expectedTagName = description.GetNamedTypeName();
    }
    else
    {
        if (description.HasTypeName())
        {
            expectedTagName = description.GetTypeName();
        }
        else
        {
            expectedTagName = XmlReplaceUnderscoreByDash(GetName());
        }
    }

    XmlEndTag endTag(*this);

    endTag.Decode(characters, asnOptions);

    if (expectedTagName != endTag.GetName())
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_END_TAG, 
            characters);
    }
    else
    {
        // Nothing to do.
    }
}

// Helper function to get level shift string (four spaces multiplied by level).
string 
AsnObject::GetLevelShift(size_t level) const
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

const size_t EXTENDED_ERROR_TEXT_MAX_SIZE = 16384;


// Function related to extended error text.
string 
AsnObject::GetEncodeExtendedErrorText(AsnError error)
{
    ostrstream ostrs;

    ostrs << endl;
    ostrs << "ASN.1 Type and Value:";
    ostrs << endl;
    Print(ostrs);
    ostrs << endl;
    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    if (result.size() > EXTENDED_ERROR_TEXT_MAX_SIZE)
    {
        result.resize(EXTENDED_ERROR_TEXT_MAX_SIZE - 5);
        result.append(" ...\0");
    }

    return result;
}

string 
AsnObject::GetDecodeExtendedErrorText(
                                    AsnError error,
                                    const Octets& octets)
{
    ostrstream ostrs;

    ostrs << endl;
    ostrs << "ASN.1 Type:";
    ostrs << endl;
    ostrs << GetName();
    ostrs << " (";
    ostrs << GetBaseName();
    ostrs << ")";
    ostrs << endl;
    ostrs << endl;
    ostrs << "Raw TLV Dump:";
    ostrs << endl;
    octets.PrintWithOffset(ostrs);
    ostrs << endl;

    ostrs << '\0';

    string result (ostrs.str());

    ostrs.rdbuf()->freeze(false);

    if (result.size() > EXTENDED_ERROR_TEXT_MAX_SIZE)
    {
        result.resize(EXTENDED_ERROR_TEXT_MAX_SIZE - 5);
        result.append(" ...\0");
    }

    return result;
}

string 
AsnObject::GetDecodeExtendedErrorText(
                                    AsnError error,
                                    const Characters& characters)
{
    ostrstream ostrs;

    ostrs << endl;
    ostrs << "ASN.1 Type:";
    ostrs << endl;
    ostrs << GetName();
    ostrs << " (";
    ostrs << GetBaseName();
    ostrs << ")";
    ostrs << endl;
    ostrs << endl;
    ostrs << "Raw Text Dump:";
    ostrs << endl;
    characters.PrintWithOffset(ostrs);
    ostrs << endl;

    ostrs << '\0';

    string result (ostrs.str());

    ostrs.rdbuf()->freeze(false);

    if (result.size() > EXTENDED_ERROR_TEXT_MAX_SIZE)
    {
        result.resize(EXTENDED_ERROR_TEXT_MAX_SIZE - 5);
        result.append(" ...\0");
    }

    return result;
}

ostream& 
operator<<(ostream& os, const AsnObject& asnObject)
{
    asnObject.Print(os);
    return os;
}

} // namespace its.

ITS_BOOLEAN
CheckLicense(int val)
{
    static ITS_BOOLEAN licenseChecked = ITS_FALSE;

    if (!licenseChecked)
    {
        ITS_InitializeClass(itsLICENSE_Class);

        if (LICENSE_Validate() == ITS_SUCCESS)
        {
            if (LICENSE_VerifyCapability(val))
            {
                licenseChecked = ITS_TRUE;
            }
        }
    }
    return licenseChecked;
}
