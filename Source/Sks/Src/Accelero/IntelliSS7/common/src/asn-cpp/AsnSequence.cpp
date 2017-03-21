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
// LOG: Revision 1.1  2007/03/30 04:53:46  cvsadmin
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
// LOG: Revision 6.2  2002/06/17 21:52:59  hdivoux
// LOG: Added processing for default ASN.1 values.
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

#ident "$Id: AsnSequence.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime AsnSequence class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnSequence.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnSequence::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(0);

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
        staticDesc.SetCloneForFactory(new AsnSequence(0, &staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

AsnSequence& 
AsnSequence::operator=(const AsnSequence& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        RemoveAllElements();
        Assign(rhs); // MUST not be done before.
        _elementVect.resize(rhs.GetSize(), NULL);

        ITS_ASSERT(GetSize() == rhs.GetSize());

        for (size_t i = 0; i < GetSize(); i++)
        {
            if (rhs._elementVect[i] != NULL)
            {
                AsnObject* element = rhs._elementVect[i];

                if (rhs._deleteSubcomponentsAutomatically)
                {
                    AsnObject* clonedElement = element->Clone();
                    _elementVect[i] = clonedElement;
                }
                else
                {
                    _elementVect[i] = element;
                }
            }
            else
            {
                _elementVect[i] = NULL;
            }
        }

        return *this;
    }
}

void 
AsnSequence::EncodeCheck(const AsnOptions& asnOptions)
{
    // Each mandatory element must be present.

    const AsnDescSequence& desc = GetDescription();

    for (size_t i = 0; i < desc.GetSize(); i++)
    {
        ITS_ASSERT(desc.Contains(i));

        const AsnDescObject& elementDesc = desc.ElementAt(i);

        if (!elementDesc.IsClauseOptional() && !elementDesc.IsClauseDefault())
        {
            if (!Contains(i))
            {
                ASN_THROW_ENCODE_ERROR(
                    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE);
            }
        }
    }
}

Octets*
AsnSequence::EncodeReplaceElementTag(
                    Octets* elementOctets, 
                    const AsnOptions& asnOptions)
{
    ITS_REQUIRE(elementOctets != NULL);

    Octets* result = elementOctets;

    for (
        size_t i = 0; 
        i < AsnOptions::GlobalGetSequenceReplaceTagCallbackSize();
        i++)
    {
        const ReplaceTagCallback&
            replaceTagCallback = 
                AsnOptions::GlobalSequenceReplaceTagCallbackAt(i);

        Tag elementTag;

        elementOctets->SetOffset(0);

        // Decode without preserving offset.

        elementTag.Decode(*elementOctets, asnOptions);

        size_t elementLengthValueBeginIndex = elementOctets->GetOffset();
        size_t elementLengthValueEndIndex = elementOctets->GetSize() + 1;

        if (elementTag == replaceTagCallback.GetEncodeToBeReplacedTag() &&
            (replaceTagCallback.GetTypeName() == "" ||
             replaceTagCallback.GetTypeName() == GetName()))
        {
            Tag replacedElementTag = 
                replaceTagCallback.
                    ReplaceTagAfterEncoding(
                        *elementOctets);

            Octets updatedElementLengthValueOctets =
                elementOctets->SubOctets(
                    elementLengthValueBeginIndex,
                    elementLengthValueEndIndex);

            Octets* updatedElementOctets = 
                replacedElementTag.Encode(asnOptions);
            *updatedElementOctets += updatedElementLengthValueOctets;
            delete elementOctets; // To be replaced => delete it before.
            result = updatedElementOctets;
        }
    }

    ITS_ENSURE(result != NULL);
    return result;
}

Octets* 
AsnSequence::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    Octets valOctets;

    for (size_t i = 0; i < GetSize(); i++)
    {
        if (Contains(i))
        {
            AsnObject* element = _elementVect[i];
            ITS_ASSERT(element != NULL);
            Octets* elementOctets = element->InternalEncodeBer(
                                        asnOptions,
                                        level + 1,
                                        element->GetPolymorphDescription());

            if (AsnOptions::GlobalGetSequenceReplaceTagCallbackSize() > 0)
            {
                elementOctets = 
                    EncodeReplaceElementTag(elementOctets, asnOptions);
            }

            valOctets += *elementOctets;
            delete elementOctets;
        }
    }

    if (asnOptions.IsEncodeProcessUnknownElements())
    {
        // Unknown Element(s) processing (added at the end).
        for (size_t j = 0; j < _unknownElementVect.size(); j++)
        {
            valOctets += _unknownElementVect[j];
        }
    }

    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnSequence::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    // Each mandatory element must be present.

    const AsnDescSequence& desc = GetDescription();

    for (size_t i = 0; i < desc.GetSize(); i++)
    {
        ITS_ASSERT(desc.Contains(i));

        const AsnDescObject& elementDesc = desc.ElementAt(i);

        if (!elementDesc.IsClauseOptional())
        {
            if (!Contains(i))
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE,
                    octets);
            }
        }
    }
}

void 
AsnSequence::DecodeAddDefaults(const AsnOptions& asnOptions)
{
    // Add each missing default element.

    const AsnDescSequence& desc = GetDescription();

    for (size_t i = 0; i < desc.GetSize(); i++)
    {
        ITS_ASSERT(desc.Contains(i));

        const AsnDescObject& elementDesc = desc.ElementAt(i);

        if (elementDesc.IsClauseDefault() && !Contains(i))
        {
            AsnObject* element = elementDesc.DefaultFactory();
            AddElement(i, element);
        }
    }
}

Tag
AsnSequence::DecodeReplaceElementTag(
                        const Tag& elementTag, 
                        const Octets& octets,
                        const AsnOptions& asnOptions)
{
    Tag result = elementTag;

    for (
        size_t i = 0; 
        i < AsnOptions::GlobalGetSequenceReplaceTagCallbackSize(); 
        i++)
    {
        const ReplaceTagCallback&
            replaceTagCallback = 
                AsnOptions::GlobalSequenceReplaceTagCallbackAt(i);

        if (elementTag == replaceTagCallback.GetDecodeToBeReplacedTag() &&
            (replaceTagCallback.GetTypeName() == "" ||
             replaceTagCallback.GetTypeName() == GetName()))
        {
            result =
                replaceTagCallback.
                    ReplaceTagBeforeDecoding(octets);
        }
    }

    return result;
}

void 
AsnSequence::InternalDecodeBer(
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

    size_t index = 0;

    while (!stop)
    {
        Tag elementTag;
        elementTag.DecodePreserveOffset(octets, asnOptions);

        if (AsnOptions::GlobalGetSequenceReplaceTagCallbackSize() > 0)
        {
            elementTag = 
                DecodeReplaceElementTag(elementTag, octets, asnOptions);
        }

        if (index >= GetSize())
        {
            if (!asnOptions.IsDecodeSkipUnknownElementInSequence() &&
                !GetDescription().IsClauseExtensible())
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE, 
                    octets);
            }
            else
            {
                // Unknown Element processing.

                size_t unknownElementBeginIndex = 0;
                size_t unknownElementEndIndex   = 0;

                if (asnOptions.IsDecodeProcessUnknownElements())
                {
                    unknownElementBeginIndex = octets.GetOffset();
                }

                // Skip Unknown Element.

                Tag unknownElementTag(octets, asnOptions);

                Length unknownElementLength(octets, asnOptions);

                octets.IncrementOffset(
                                (size_t)unknownElementLength.GetLength());

                if (asnOptions.IsDecodeProcessUnknownElements())
                {
                    unknownElementEndIndex = octets.GetOffset();

                    Octets unknownElementOctets = 
                        octets.SubOctets(
                            unknownElementBeginIndex,
                            unknownElementEndIndex);

                    _unknownElementVect.push_back(unknownElementOctets);
                }
            }
        }

        size_t descIndex = index;

        while (descIndex < GetDescription().GetSize())
        {
            const AsnDescObject& elementDesc = 
                GetDescription().ElementAt(descIndex);

            if (elementDesc.TagIdentify(elementTag))
            {
                AsnObject* element = elementDesc.Factory();
                element->InternalDecodeBer(
                                        octets,
                                        asnOptions,
                                        level + 1,
                                        elementDesc);

                AddElement(index, element);
                index++;        // Next element in SEQUENCE.
                descIndex++;    // Next element in SEQUENCE description.
                break;
            }
            else
            {
                if (elementDesc.IsClauseOptional() || 
                    elementDesc.IsClauseDefault())
                {
                    index++;     // One optional or default maybe absent.
                    descIndex++; // Try next element in SEQUENCE description.

                    if (descIndex >= GetDescription().GetSize())
                    {
                        if (!asnOptions.
                                IsDecodeSkipUnknownElementInSequence() &&
                            !GetDescription().IsClauseExtensible())
                        {
                            ASN_THROW_DECODE_ERROR(
                                ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE,
                                octets);
                        }
                        else
                        {
                            // Unknown Element processing.
                            size_t unknownElementBeginIndex = 0;
                            size_t unknownElementEndIndex   = 0;

                            if (asnOptions.IsDecodeProcessUnknownElements())
                            {
                                unknownElementBeginIndex = octets.GetOffset();
                            }

                            // Skip Unknown Element.
                            Tag unknownElementTag(octets, asnOptions);
                            Length unknownElementLength(octets, asnOptions);
                            octets.IncrementOffset(
                                    (size_t)unknownElementLength.GetLength());

                            if (asnOptions.IsDecodeProcessUnknownElements())
                            {
                                unknownElementEndIndex = octets.GetOffset();
                                Octets unknownElementOctets = 
                                    octets.SubOctets(
                                        unknownElementBeginIndex,
                                        unknownElementEndIndex);

                                _unknownElementVect.push_back(
                                    unknownElementOctets);
                            }
                        }
                    }
                }
                else
                {
                    ASN_THROW_DECODE_ERROR(
                        ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE,
                        octets);
                }
            }
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
                    ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE,
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

    DecodeAddDefaults(asnOptions);

    DecodeCheck(octets, asnOptions);
}

Octets* 
AsnSequence::InternalEncodePer(
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
AsnSequence::InternalDecodePer(
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
AsnSequence::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    XmlWriteNewLine(str, asnOptions);

    for (size_t i = 0; i < GetSize(); i++)
    {
        if (Contains(i))
        {
            AsnObject* element = _elementVect[i];
            ITS_ASSERT(element != NULL);
            const AsnDescObject& elementDesc = 
                static_cast<const AsnDescSequence&>(description).ElementAt(i);
            Characters* elementCharacters = 
                element->InternalEncodeToXml(
                    asnOptions, 
                    level + 1, 
                    elementDesc);
            str += elementCharacters->GetString();
            delete elementCharacters;

            XmlWriteNewLine(str, asnOptions);
        }
    }

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnSequence::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    // Each mandatory element must be present.

    const AsnDescSequence& desc = GetDescription();

    for (size_t i = 0; i < desc.GetSize(); i++)
    {
        ITS_ASSERT(desc.Contains(i));

        const AsnDescObject& elementDesc = desc.ElementAt(i);

        if (!elementDesc.IsClauseOptional())
        {
            if (!Contains(i))
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE,
                    characters);
            }
        }
    }
}

void 
AsnSequence::InternalDecodeFromXml(
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

    size_t index = 0;

    while (!stop)
    {
        XmlStartTag elementStartTag(*this);
        elementStartTag.DecodePreserveOffset(characters, asnOptions);

        if (index >= GetSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE,
                characters);
        }

        size_t descIndex = index;

        while (descIndex < GetDescription().GetSize())
        {
            const AsnDescObject& elementDesc =
                GetDescription().ElementAt(descIndex);

            ITS_ASSERT(elementDesc.IsNamedType());

            if (elementDesc.GetNamedTypeName() == 
                elementStartTag.GetName())
            {
                AsnObject* element = elementDesc.Factory();
                element->InternalDecodeFromXml(
                                        characters,
                                        asnOptions,
                                        level + 1,
                                        elementDesc);
                AddElement(index, element);
                index++;        // Next element in SEQUENCE.
                descIndex++;    // Next element in SEQUENCE description.
                break;
            }
            else
            {
                if (elementDesc.IsClauseOptional() || 
                    elementDesc.IsClauseDefault())
                {
                    index++;     // One optional maybe absent.
                    descIndex++; // Try next element in SEQUENCE description.

                    if (descIndex >= GetDescription().GetSize())
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE,
                            characters);
                    }
                }
                else
                {
                    ASN_THROW_CHARACTERS_DECODE_ERROR(
                        ASN_E_MISSING_MANDATORY_ELEMENT_IN_SEQUENCE,
                        characters);
                }
            }
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

    DecodeAddDefaults(asnOptions);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnSequence::Equals(const AsnObject& rhs) const
{ 
    const AsnSequence* other = static_cast<const AsnSequence*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (GetSize() != other->GetSize())
    {
        return false;
    }

    vector<AsnObject*>::const_iterator iter = ElementsBegin();
    vector<AsnObject*>::const_iterator iterOther = other->ElementsBegin();

    while (iter != ElementsEnd() && iterOther != ElementsEnd())
    {
        AsnObject* element = *iter;
        AsnObject* elementOther = *iterOther;

        if (element == NULL && elementOther == NULL)
        {
            continue;
        }
        else if (element == NULL && elementOther != NULL)
        { 
            return false;
        }
        else if (element != NULL && elementOther == NULL)
        {
            return false;
        }
        else
        {
            ITS_ASSERT(element != NULL);
            ITS_ASSERT(elementOther != NULL);

            if (!element->Equals(*elementOther))
            {
                return false;
            }
            else
            {
                continue;
            }
        }
    }

    return true;
}

void 
AsnSequence::Print(ostream& os, size_t level) const
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

    for (size_t i = 0; i < GetSize(); i++)
    {
        AsnObject* element = _elementVect[i];

        if (element != NULL)
        {
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
    }

    os << levelShift;
    os << "}" << endl;
}

} // namespace its.
