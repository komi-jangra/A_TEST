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
// LOG: Revision 1.1  2007/03/30 04:53:38  cvsadmin
// LOG: *** empty log message ***
// LOG:
// LOG: Revision 1.1.1.1  2006/12/22 13:34:22  cvsadmin
// LOG: Initialising sources in CVS
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:19  cvsadmin
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

#ident "$Id: AsnNull.cpp,v 1.1.1.1 2007-10-08 11:11:42 bsccs2 Exp $"

//
// ASN.1 runtime AsnNull class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnNull.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnNull::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnNull(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnNull::EncodeCheck(const AsnOptions& asnOptions)
{
    // Nothing to do.
}

Octets* 
AsnNull::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    Octets valOctets; // Default constructor => valOctets.GetLength() == 0.
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnNull::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnNull::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);

    Length length(octets, asnOptions);
    if (length.GetLength() != 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_NULL_LENGTH, octets);
    }

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnNull::InternalEncodePer(
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
AsnNull::InternalDecodePer(
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
AsnNull::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;
    XmlWriteLevelShift(str, asnOptions, level);

    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            XmlWriteEmptyElementTag(
                str,
                description.GetTypeName(),
                asnOptions);
        }
        else
        {
            XmlWriteEmptyElementTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()), 
                asnOptions);
        }
    }
    else if (description.IsNamedType())
    {
        XmlWriteEmptyElementTag(
            str, 
            description.GetNamedTypeName(), 
            asnOptions);
    }
    else
    {
        if (description.HasTypeName())
        {
            XmlWriteEmptyElementTag(
                str,
                description.GetTypeName(),
                asnOptions);
        }
        else
        {
            XmlWriteEmptyElementTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()),
                asnOptions);
        }
    }

    return new Characters(str);
}

void 
AsnNull::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnNull::InternalDecodeFromXml(
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

    XmlEmptyElementTag emptyElementTag(*this);

    emptyElementTag.Decode(characters, asnOptions);

    if (expectedTagName != emptyElementTag.GetName())
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
            characters);
    }

    DecodeCheck(characters, asnOptions);
}

bool 
AsnNull::Equals(const AsnObject& rhs) const
{ 
    const AsnNull* other = static_cast<const AsnNull*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    return true;
}

void 
AsnNull::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ]" << endl;
}

} // namespace its.
