///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
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
// LOG: Revision 1.1  2007/03/30 04:53:49  cvsadmin
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

#ident "$Id: AsnSetOf.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime AsnSetOf class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnSetOf.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnSetOf::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSetOf staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnSetOf(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

AsnSetOf& 
AsnSetOf::operator=(const AsnSetOf& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        RemoveAllElements();
        Assign(rhs); // MUST not be done before.

        for (list<AsnObject*>::const_iterator iter = rhs.ElementsBegin();
             iter != rhs.ElementsEnd(); iter++)
        {
            AsnObject* element = *iter;

            if (rhs._deleteSubcomponentsAutomatically)
            {
                AsnObject* clonedElement = element->Clone();
                _elementList.push_back(clonedElement);
            }
            else
            {
                _elementList.push_back(element);
            }
        }        
        
        return *this;
    }
}

void 
AsnSetOf::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsEncodeIgnoreSetOfSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_SET_OF_SIZE);
        }
        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_SET_OF_SIZE);
        }
    }
}

Octets* 
AsnSetOf::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    Octets valOctets;

    for (list<AsnObject*>::const_iterator iter = ElementsBegin();
         iter != ElementsEnd(); iter++)
    {
        AsnObject* element = *iter;
        Octets* elementOctets = element->InternalEncodeBer(
                                        asnOptions,
                                        level + 1,
                                        element->GetPolymorphDescription());
        valOctets += *elementOctets;
        delete elementOctets;
    }

    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnSetOf::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreSetOfSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_SET_OF_SIZE, octets);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_SET_OF_SIZE, octets);
        }
    }
}

void 
AsnSetOf::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    Length length(octets, asnOptions);
    long startOffset = octets.GetOffset();
    bool stop = false;
    if (length.GetLength() == 0)
    {
        stop = true;
    }

    RemoveAllElements();

    while (!stop)
    {
        Tag elementTag;
        elementTag.DecodePreserveOffset(octets, asnOptions);

        if (GetDescription().Contains(elementTag))
        {
            const AsnDescObject& elementDesc = GetDescription().GetElement();

            AsnObject* element = elementDesc.Factory();
            element->InternalDecodeBer(
                                    octets,
                                    asnOptions,
                                    level + 1,
                                    elementDesc);
            AddElement(element);
        }
        else
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_UNKNOWN_ELEMENT_IN_SET_OF,
                octets);
        }

        long currentOffset = octets.GetOffset();

        if (!length.IsIndefinite())
        {
            if (length.GetLength() == currentOffset - startOffset)
            {
                stop = true;
            }
            else if (length.GetLength() > currentOffset - startOffset)
            {
                stop = false;
            }
            else
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_ELEMENT_LENGTH_IN_SET_OF,
                    octets);
            }
        }
        else
        {
            if (length.IsIndefiniteEndMark(octets))
            {
                length.IndefiniteEndMarkIncrementOffset(octets);
                stop = true;
            }
            else
            {
                stop = false;
            }
        }
    }

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnSetOf::InternalEncodePer(
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
AsnSetOf::InternalDecodePer(
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
AsnSetOf::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    if (GetSize() > 0)
    {
        XmlWriteNewLine(str, asnOptions);
    }

    for (list<AsnObject*>::const_iterator iter = ElementsBegin();
         iter != ElementsEnd(); iter++)
    {
        AsnObject* element = *iter;
        const AsnDescObject& elementDesc =
            static_cast<const AsnDescSetOf&>(description).GetElement();
        Characters* elementCharacters = 
            element->InternalEncodeToXml(asnOptions, level + 1, elementDesc);
        str += elementCharacters->GetString();
        delete elementCharacters;

        XmlWriteNewLine(str, asnOptions);
    }

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnSetOf::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreSetOfSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_SET_OF_SIZE, 
                characters);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_SET_OF_SIZE, 
                characters);
        }
    }
}

void 
AsnSetOf::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    XmlStartTag startTag(*this);
    startTag.DecodePreserveOffset(characters, asnOptions);

    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    bool stop = false;

    RemoveAllElements();

    while (!stop)
    {
        XmlStartTag elementStartTag(*this);
        elementStartTag.DecodePreserveOffset(characters, asnOptions);

        const AsnDescObject& elementDesc = GetDescription().GetElement();
        
        string elementDescName;

        if (elementDesc.HasTypeName())
        {
            elementDescName = elementDesc.GetTypeName();
        }
        else
        {
            elementDescName = 
                XmlReplaceUnderscoreByDash(elementDesc.GetName());
        }

        if (elementDescName == elementStartTag.GetName())
        {
            AsnObject* element = elementDesc.Factory();
            element->InternalDecodeFromXml(
                                    characters,
                                    asnOptions,
                                    level + 1,
                                    elementDesc);
            AddElement(element);
        }
        else
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_UNKNOWN_ELEMENT_IN_SET_OF,
                characters);
        }

        XmlEndTag endTag(*this);
        endTag.TryDecodePreserveOffset(characters, asnOptions);

        if (startTag.GetName() == endTag.GetName())
        {
            stop = true;
        }
        else
        {
            stop = false;
        }
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnSetOf::Equals(const AsnObject& rhs) const
{ 
    const AsnSetOf* other = static_cast<const AsnSetOf*>(&rhs);

    // TODO: To be done.
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
    return false;
}

void 
AsnSetOf::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "{" << endl;

    bool first = true;

    for (list<AsnObject*>::const_iterator iter = ElementsBegin();
         iter != ElementsEnd(); iter++)
    {
        AsnObject* element = *iter;

        if (!first)
        {
            os << endl;
        }
        else
        {
            first = false;
        }

        element->Print(os, level + 1);
    }

    os << levelShift;
    os << "}" << endl;
}

} // namespace its.

