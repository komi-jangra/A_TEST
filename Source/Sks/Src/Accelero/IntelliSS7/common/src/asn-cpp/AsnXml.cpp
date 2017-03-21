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
// LOG: Revision 1.1  2007/03/30 04:53:51  cvsadmin
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
// LOG: Revision 1.6  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 1.5  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 1.4  2002/01/10 22:58:44  hdivoux
// LOG: Warnings removal.
// LOG:
// LOG: Revision 1.3  2002/01/10 22:51:34  hdivoux
// LOG: Start XER decoding.
// LOG:
// LOG: Revision 1.2  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 1.1  2002/01/07 20:06:19  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnXml.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// ASN.1 runtime XML related class implementations.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnObject.h>
#include <Characters.h>
#include <AsnException.h>

#include <algorithm>


using namespace std;

// Helper functions for parsing.

static bool 
IsWhiteSpace(char c)
{
    switch (c)
    {
    case ' ':
    case '\n':
    case '\r':
    case '\t':
        return true;
    default:
        return false;
    }
}

static bool 
IsNameChar(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return true;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return true;
    }
    else if (c >= '0' && c <= '9')
    {
        return true;
    }
    else
    {
        switch (c)
        {
        case '.':
        case '-':
        case '_':
        case ':':
            return true;
        default:
            return false;
        }
    }
}

static inline bool 
IsNameFirstChar(char c)
{
    return IsNameChar(c);
}

static inline bool
IsDigit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool
IsHexDigit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    else if (c >= 'A' && c <= 'F')
    {
        return true;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return true;
    }
    else
    {
        return false;
    }
}

static inline bool 
IsLeftAngleBracket(char c)
{
    return c == '<';
}

static inline bool 
IsRightAngleBracket(char c)
{
    return c == '>';
}

static inline bool 
IsSlash(char c)
{
    return c == '/';
}

static inline bool 
IsQuote(char c)
{
    return c == '\"';
}

static inline bool
IsDash(char c)
{
    return c == '-';
}

static inline bool
IsZero(char c)
{
    return c == '0';
}

static inline bool
IsOne(char c)
{
    return c == '1';
}

static inline bool
IsDot(char c)
{
    return c == '.';
}

namespace its {

void 
XmlWriteElementStartTag(
    string& str, 
    const string& name,
    const AsnOptions& asnOptions)
{
    str += '<';
    str += name;
    str += '>';
}

void 
XmlWriteElementEndTag(
    string& str, 
    const string& name,
    const AsnOptions& asnOptions)
{
    str += '<';
    str += '/';
    str += name;
    str += '>';
}

void 
XmlWriteEmptyElementTag(
    string& str, 
    const string& name,
    const AsnOptions& asnOptions)
{
    str += '<';
    str += name;
    str += '/';
    str += '>';
}

void 
XmlWriteLevelShift(
    string& str, 
    const AsnOptions& asnOptions, 
    size_t level)
{
    if (!asnOptions.IsEncodeXmlWithoutSeparators())
    {
        str.append(4 * level, ' ');
    }
}

void 
XmlWriteNewLine(
    string& str, 
    const AsnOptions& asnOptions)
{
    if (!asnOptions.IsEncodeXmlWithoutSeparators())
    {
        str += '\n';
    }
}

string
XmlReplaceUnderscoreByDash(const std::string& str)
{
    string result(str);
    replace(result.begin(), result.end(), '_', '-');
    return result;
}

void
XmlTag::DecodePreserveOffset(
    Characters& characters,
    const AsnOptions& asnOptions)
{
    size_t offset = characters.GetOffset();
    Decode(characters, asnOptions);
    characters.SetOffset(offset);
}

void
XmlTag::TryDecodePreserveOffset(
    Characters& characters,
    const AsnOptions& asnOptions)
{
    size_t offset = characters.GetOffset();
    _throwExceptions = false;
    Decode(characters, asnOptions);
    _throwExceptions = true;
    characters.SetOffset(offset);
}

const size_t EXTENDED_ERROR_TEXT_MAX_SIZE = 16384;

string 
XmlTag::GetEncodeExtendedErrorText(
                                AsnError error)
{
    return "No extended encode error text available for XML Tag.";
}

string 
XmlTag::GetDecodeExtendedErrorText(
                                AsnError error, 
                                const Characters& characters)
{
    ostrstream ostrs;

    ostrs << endl;
    ostrs << "ASN.1 Type:";
    ostrs << endl;
    ostrs << _asnObject->GetName();
    ostrs << " (";
    ostrs << _asnObject->GetBaseName();
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

void
XmlStartTag::Decode(
    Characters& characters,
    const AsnOptions& asnOptions)
{
    _name.erase(_name.begin(), _name.end());
    _attributeList.erase(_attributeList.begin(), _attributeList.end());

    bool keepOn         = true;
    bool inName         = false;
    bool inAfterName    = false;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            if (_throwExceptions)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_START_TAG,
                    characters);
            }
            else
            {
                return;
            }
        }

        char c = characters.GetCharAtWithOffset(i);

        if (!inName && !inAfterName)
        {
            if (IsWhiteSpace(c))
            {
                // Ignore.
            }
            else if (IsLeftAngleBracket(c))
            {
                inName = true;
            }
            else
            {
                if (_throwExceptions)
                {
                    ASN_THROW_CHARACTERS_DECODE_ERROR(
                        ASN_E_XML_INVALID_START_TAG,
                        characters);
                }
                else
                {
                    return;
                }
            }
        }
        else if (inName && !inAfterName)
        {
            if (IsNameChar(c))
            {
                _name += c;
            }
            else if (IsRightAngleBracket(c))
            {
                keepOn = false;
            }
            else
            {
                inName = false;
                inAfterName = true;
            }
        }
        else if (!inName && inAfterName)
        {
            if (IsRightAngleBracket(c))
            {
                keepOn = false;
            }
            else
            {
                // Ignore white spaces and attributes.
            }
        }
        else
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
        }

        i++;
    }

    characters.IncrementOffset(i);
}

void
XmlEndTag::Decode(
    Characters& characters,
    const AsnOptions& asnOptions)
{
    _name.erase(_name.begin(), _name.end());

    bool keepOn         = true;
    bool inName         = false;
    bool inAfterName    = false;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            if (_throwExceptions)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_END_TAG,
                    characters);
            }
            else
            {
                return;
            }
        }

        char c = characters.GetCharAtWithOffset(i);

        if (!inName && !inAfterName)
        {
            if (IsWhiteSpace(c))
            {
                // Ignore.
            }
            else if (IsLeftAngleBracket(c))
            {
                i++;

                if (!characters.IsIndexWithOffsetValid(i))
                {
                    if (_throwExceptions)
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_XML_INVALID_END_TAG,
                            characters);
                    }
                    else
                    {
                        return;
                    }
                }

                c = characters.GetCharAtWithOffset(i);

                if (!IsSlash(c))
                {
                    if (_throwExceptions)
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_XML_INVALID_END_TAG,
                            characters);
                    }
                    else
                    {
                        return;
                    }
                }

                inName = true;
            }
            else
            {
                if (_throwExceptions)
                {
                    ASN_THROW_CHARACTERS_DECODE_ERROR(
                        ASN_E_XML_INVALID_END_TAG,
                        characters);
                }
                else
                {
                    return;
                }
            }
        }
        else if (inName && !inAfterName)
        {
            if (IsNameChar(c))
            {
                _name += c;
            }
            else if (IsRightAngleBracket(c))
            {
                keepOn = false;
            }
            else
            {
                inName = false;
                inAfterName = true;
            }
        }
        else if (!inName && inAfterName)
        {
            if (IsRightAngleBracket(c))
            {
                keepOn = false;
            }
            else
            {
                // Ignore white spaces.
            }
        }
        else
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
        }

        i++;
    }

    characters.IncrementOffset(i);
}

void
XmlEmptyElementTag::Decode(
    Characters& characters,
    const AsnOptions& asnOptions)
{
    _name.erase(_name.begin(), _name.end());
    _attributeList.erase(_attributeList.begin(), _attributeList.end());

    bool keepOn         = true;
    bool inName         = false;
    bool inAfterName    = false;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            if (_throwExceptions)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
                    characters);
            }
            else
            {
                return;
            }
        }

        char c = characters.GetCharAtWithOffset(i);

        if (!inName && !inAfterName)
        {
            if (IsWhiteSpace(c))
            {
                // Ignore.
            }
            else if (IsLeftAngleBracket(c))
            {
                inName = true;
            }
            else
            {
                if (_throwExceptions)
                {
                    ASN_THROW_CHARACTERS_DECODE_ERROR(
                        ASN_E_XML_INVALID_START_TAG,
                        characters);
                }
                else
                {
                    return;
                }
            }
        }
        else if (inName && !inAfterName)
        {
            if (IsNameChar(c))
            {
                _name += c;
            }
            else if (IsSlash(c))
            {
                i++;

                if (!characters.IsIndexWithOffsetValid(i))
                {
                    if (_throwExceptions)
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
                            characters);
                    }
                    else
                    {
                        return;
                    }
                }

                c = characters.GetCharAtWithOffset(i);

                if (!IsRightAngleBracket(c))
                {
                    if (_throwExceptions)
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
                            characters);
                    }
                    else
                    {
                        return;
                    }
                }

                keepOn = false;
            }
            else
            {
                inName = false;
                inAfterName = true;
            }
        }
        else if (!inName && inAfterName)
        {
            if (IsSlash(c))
            {
                i++; 

                if (!characters.IsIndexWithOffsetValid(i))
                {
                    if (_throwExceptions)
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
                            characters);
                    }
                    else
                    {
                        return;
                    }
                }

                c = characters.GetCharAtWithOffset(i);

                if (!IsRightAngleBracket(c))
                {
                    if (_throwExceptions)
                    {
                        ASN_THROW_CHARACTERS_DECODE_ERROR(
                            ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
                            characters);
                    }
                    else
                    {
                        return;
                    }
                }

                keepOn = false;
            }
            else
            {
                // Ignore white spaces and attributes.
            }
        }
        else
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
        }

        i++;
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsBaseString(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool keepOn = true;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_BASE_STRING_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(i);

        if (IsLeftAngleBracket(c))
        {
            if (i == 0)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_BASE_STRING_CONTENT,
                    characters);
            }

            keepOn = false;
        }
        else
        {
            _data += c;
        }
        
        if (keepOn)
        {
            i++;
        }
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsBitString(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool keepOn = true;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_BIT_STRING_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(i);

        if (IsLeftAngleBracket(c))
        {
            if (i == 0)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_BIT_STRING_CONTENT,
                    characters);
            }

            keepOn = false;
        }
        else if (IsZero(c) || IsOne(c))
        {
            _data += c;
        }
        else
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_BIT_STRING_CONTENT,
                characters);
        }

        if (keepOn)
        {
            i++;
        }
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsBoolean(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool keepOn = true;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_BOOLEAN_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(i);

        if (IsLeftAngleBracket(c))
        {
            keepOn = false;
        }
        else
        {
            _data += c;
        }

        if (keepOn)
        {
            i++;
        }
    }

    if (_data != "TRUE"   &&
        _data != "true"   && 
        _data != "FALSE"  &&
        _data != "false")
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_BOOLEAN_CONTENT,
            characters);
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsEnumerated(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    try
    {
        XmlEmptyElementTag emptyElementTag(*_asnObject);

        emptyElementTag.Decode(characters, asnOptions);

        _data = emptyElementTag.GetName();
    }
    catch (AsnCharactersDecodeError& exc)
    {
        exc = exc;

        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_ENUMERATED_CONTENT,
            characters);
    }
}

void 
XmlContent::DecodeAsInteger(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool keepOn = true;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_INTEGER_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(i);

        if (IsLeftAngleBracket(c))
        {
            if (i == 0)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_INTEGER_CONTENT,
                    characters);
            }

            keepOn = false;
        }
        else if (IsDash(c))
        {
            if (i != 0)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_INTEGER_CONTENT,
                    characters);
            }

            _data += c;
        }
        else if (IsDigit(c))
        {
            _data += c;
        }
        else
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_INTEGER_CONTENT,
                characters);
        }

        if (keepOn)
        {
            i++;
        }
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsObjectIdentifier(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool keepOn     = true;
    bool prevIsDot  = true;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_OID_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(i);

        if (IsLeftAngleBracket(c))
        {
            if (i == 0)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_OID_CONTENT,
                    characters);
            }

            keepOn = false;
        }
        else if (IsDot(c))
        {
            if (prevIsDot)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_OID_CONTENT,
                    characters);
            }

            _data += c;

            prevIsDot = true;
        }
        else if (IsDigit(c))
        {
            _data += c;

            prevIsDot = false;
        }
        else
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_OID_CONTENT,
                characters);
        }

        if (keepOn)
        {
            i++;
        }
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsOctetString(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool keepOn = true;

    size_t i = 0;

    while (keepOn)
    {
        if (!characters.IsIndexWithOffsetValid(i))
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_OCTET_STRING_CONTENT,
                characters);
        }

        char c = characters.GetCharAtWithOffset(i);

        if (IsLeftAngleBracket(c))
        {
            if (i == 0)
            {
                ASN_THROW_CHARACTERS_DECODE_ERROR(
                    ASN_E_XML_INVALID_OCTET_STRING_CONTENT,
                    characters);
            }

            keepOn = false;
        }
        else if (IsHexDigit(c))
        {
            _data += c;
        }
        else
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_XML_INVALID_OCTET_STRING_CONTENT,
                characters);
        }

        if (keepOn)
        {
            i++;
        }
    }

    if (_data.size() % 2 != 0)
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_OCTET_STRING_CONTENT,
            characters);
    }

    characters.IncrementOffset(i);
}

void 
XmlContent::DecodeAsReal(
                    Characters& characters,
                    const AsnOptions& asnOptions)
{
    _data.erase(_data.begin(), _data.end());

    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}

string 
XmlContent::GetEncodeExtendedErrorText(
                                AsnError error)
{
    return "No extended encode error text available for XML Content.";
}

string 
XmlContent::GetDecodeExtendedErrorText(
                                AsnError error, 
                                const Characters& characters)
{
    ostrstream ostrs;

    ostrs << endl;
    ostrs << "ASN.1 Type:";
    ostrs << endl;
    ostrs << _asnObject->GetName();
    ostrs << " (";
    ostrs << _asnObject->GetBaseName();
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

} // namespace its.

