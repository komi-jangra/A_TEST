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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:07  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:58  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:55  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:58  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 1.5  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 1.4  2002/01/11 22:19:19  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 1.3  2002/01/10 22:51:55  hdivoux
// LOG: Start XER decoding.
// LOG:
// LOG: Revision 1.2  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 1.1  2002/01/07 20:07:06  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime XML related class definitions.
//

#if !defined(_ASN_XML_H_)
#define _ASN_XML_H_

#ident "$Id: AsnXml.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnError.h>
#include <Characters.h>


namespace its {

// Forward declarations.

class AsnObject;


// Write helper functions.

void XmlWriteElementStartTag(
        std::string& str, 
        const std::string& name,
        const AsnOptions& asnOptions);

void XmlWriteElementEndTag(
        std::string& str, 
        const std::string& name,
        const AsnOptions& asnOptions);

void XmlWriteEmptyElementTag(
        std::string& str, 
        const std::string& name,
        const AsnOptions& asnOptions);

void XmlWriteLevelShift(
        std::string& str, 
        const AsnOptions& asnOptions, 
        size_t level);

void XmlWriteNewLine(
        std::string& str, 
        const AsnOptions& asnOptions);


// Substitution function.
std::string XmlReplaceUnderscoreByDash(const std::string& str);

class XmlAttribute
{
public:

    XmlAttribute()
    : _name(""), _value("")
    {}

    XmlAttribute(const std::string& name, const std::string& value)
    : _name(name), _value(value)
    {}

    // Default copy constructor ok.

    // Destructor must not be virtual.

    ~XmlAttribute()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    const std::string&
    GetName() const
    {
        return _name;
    }

    void
    SetName(const std::string& name)
    {
        _name = name;
    }

    const std::string&
    GetValue() const
    {
        return _value;
    }

    void
    SetValue(const std::string& value)
    {
        _value = value;
    }

protected:

    std::string _name;
    std::string _value;

};

class XmlTag
{
public:

    // Default constructor not ok.

    XmlTag(const AsnObject& asnObject)
    : _name(""), _asnObject(&asnObject), _throwExceptions(true)
    {}

    XmlTag(const std::string& name, const AsnObject& asnObject)
    : _name(name), _asnObject(&asnObject), _throwExceptions(true)
    {}

    // Default copy constructor ok.

    virtual ~XmlTag()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    const std::string&
    GetName() const
    {
        return _name;
    }

    void
    SetName(const std::string& name)
    {
        _name = name;
    }

    virtual void Decode(
        Characters& characters, 
        const AsnOptions& asnOptions) = 0;

    virtual void DecodePreserveOffset(
        Characters& characters, 
        const AsnOptions& asnOptions);

    virtual void TryDecodePreserveOffset(
        Characters& characters,
        const AsnOptions& asnOptions);

    std::string GetEncodeExtendedErrorText(
                                AsnError error);

    std::string GetDecodeExtendedErrorText(
                                AsnError error, 
                                const Characters& characters);

protected:

    std::string         _name;
    const AsnObject*    _asnObject;
    bool                _throwExceptions;

    XmlTag()
    : _name(""), _asnObject(NULL)
    {}

};

class XmlStartTag : public XmlTag
{
public:

    // Default constructor not ok.

    XmlStartTag(const AsnObject& asnObject)
    : XmlTag(asnObject)
    {}

    XmlStartTag(const std::string& name, const AsnObject& asnObject)
    : XmlTag(name, asnObject)
    {}

    // Default copy constructor ok.

    virtual ~XmlStartTag()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    void
    AddAttribute(const XmlAttribute& attribute)
    {
        _attributeList.push_back(attribute);
    }

    const std::list<XmlAttribute>&
    GetAttributeList() const
    {
        return _attributeList;
    }

    virtual void Decode(
        Characters& characters, 
        const AsnOptions& asnOptions);

protected:

    std::list<XmlAttribute> _attributeList;

    XmlStartTag()
    {}

};

class XmlEndTag : public XmlTag
{
public:

    XmlEndTag(const AsnObject& asnObject)
    : XmlTag(asnObject)
    {}

    XmlEndTag(const std::string& name, const AsnObject& asnObject)
    : XmlTag(name, asnObject)
    {}

    // Default copy constructor ok.

    virtual ~XmlEndTag()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    virtual void Decode(
        Characters& characters, 
        const AsnOptions& asnOptions);

protected:

    XmlEndTag()
    {}

};

class XmlEmptyElementTag : public XmlTag
{
public:

    // Default constructor not ok.

    XmlEmptyElementTag(const AsnObject& asnObject)
    : XmlTag(asnObject)
    {}

    XmlEmptyElementTag(const std::string& name, const AsnObject& asnObject)
    : XmlTag(name, asnObject)
    {}

    // Default copy constructor ok.

    virtual ~XmlEmptyElementTag()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    void
    AddAttribute(const XmlAttribute& attribute)
    {
        _attributeList.push_back(attribute);
    }

    const std::list<XmlAttribute>&
    GetAttributeList() const
    {
        return _attributeList;
    }

    virtual void Decode(
                    Characters& characters, 
                    const AsnOptions& asnOptions);

protected:

    std::list<XmlAttribute> _attributeList;

    XmlEmptyElementTag()
    {}

};

class XmlContent
{
public:

    // Default constructor not ok.

    XmlContent(const AsnObject& asnObject)
    : _data(""), _asnObject(&asnObject)
    {}

    // Default copy constructor ok.

    virtual ~XmlContent()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    const std::string&
    GetString() const
    {
        return _data;
    }

    void DecodeAsBaseString(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsBitString(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsBoolean(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsEnumerated(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsInteger(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsObjectIdentifier(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsOctetString(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    void DecodeAsReal(
                    Characters& characters,
                    const AsnOptions& asnOptions);

    std::string GetEncodeExtendedErrorText(
                    AsnError error);

    std::string GetDecodeExtendedErrorText(
                    AsnError error, 
                    const Characters& characters);

protected:

    std::string         _data;
    const AsnObject*    _asnObject;

    XmlContent()
    {}

};

} // namespace its.

#endif // !defined(_ASN_XML_H_)
