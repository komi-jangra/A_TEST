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
// LOG: Revision 1.1.1.1  2007/03/08 15:13:52  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:53  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:57  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 1.1  2002/01/16 22:15:37  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnOpenType class definition.
//

#if !defined(_ASN_OPEN_TYPE_H_)
#define _ASN_OPEN_TYPE_H_

#ident "$Id: AsnOpenType.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <Tag.h>
#include <Length.h>
#include <AsnObject.h>
#include <AsnDescOpenType.h>

namespace its {

class AsnOpenType : public AsnObject
{
public: 

    AsnOpenType(AsnObject* openType, bool initialize = true)
    :   _openType(openType), 
        _decodedOctets(false),
        _decodedCharacters(false),
        _decodedLength(0)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnOpenType(
        Octets& octets,
        const AsnOptions& asnOptions = AsnOptions(),
        bool initialize = true)
    :   _openType(NULL), 
        _decodedOctets(false),
        _decodedCharacters(false),
        _decodedLength(0)
    {
        if (initialize)
        {
            Initialize();
        }

        Decode(octets, asnOptions);
    }

    AsnOpenType(bool initialize = true)
    :   _openType(NULL), 
        _decodedOctets(false),
        _decodedCharacters(false),
        _decodedLength(0)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnOpenType(const AsnOpenType& rhs) 
    :   AsnObject(rhs), 
        _decodedOctets(rhs._decodedOctets),
        _decodedCharacters(rhs._decodedCharacters),
        _decodedTag(rhs._decodedTag),
        _decodedLength(rhs._decodedLength), 
        _decodedOctetsData(rhs._decodedOctetsData),
        _decodedCharactersData(rhs._decodedCharactersData)
    {
        if (rhs._openType != NULL)
        {
            if (rhs._deleteSubcomponentsAutomatically)
            {
                _openType = rhs._openType->Clone();
            }
            else
            {
                _openType = rhs._openType;
            }
        }
        else
        {
            _openType = NULL;
        }
    }

    AsnOpenType(AsnDescObject* description)
    :   _openType(NULL), 
        _decodedOctets(false),
        _decodedCharacters(false),
        _decodedLength(0)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    AsnOpenType(AsnDescObject* description, AsnObject* openType)
    :   _openType(openType), 
        _decodedOctets(false),
        _decodedCharacters(false),
        _decodedLength(0)
    {
        ITS_REQUIRE(description != NULL);    
        _description = description;
    }

protected:

    void 
    Initialize()
    {
        ITS_ASSERT(_description == NULL);
        _description = GetStaticDescription();
    }

    static AsnDescObject* GetStaticDescription();

public:

    virtual ~AsnOpenType()
    {
        if (_openType != NULL)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _openType;
            }
        }
    }

    AsnOpenType& operator=(const AsnOpenType& rhs);

    bool 
    operator==(const AsnOpenType& rhs) const
    { 
        return Equals(rhs); 
    }

    const AsnObject& 
    GetOpenType() const
    {
        ITS_REQUIRE(ContainsOpenType());
        return *_openType;
    }

    void 
    SetOpenType(AsnObject* openType)
    {
        if (_openType != NULL)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _openType;
            }
        }

        _openType = openType;
        _decodedOctets = false;
        _decodedCharacters = false;
    }

    void 
    SetOpenType(const AsnObject& openType)
    {
        if (_openType != NULL)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _openType;
            }
        }

        if (_deleteSubcomponentsAutomatically)
        {
            _openType = openType.Clone();
        }
        else
        {
            _openType = const_cast<AsnObject*>(&openType);
        }

        _decodedOctets = false;
        _decodedCharacters = false;
    }

    bool 
    Contains(const Tag& tag) const
    {
        if (_openType == NULL)
        {
            return false;
        }

        if (_openType->GetPolymorphDescription().TagIdentify(tag))
        {
            return true;
        }

        return false;
    }

    bool 
    ContainsOpenType() const
    { 
        return _openType != NULL; 
    }

    bool 
    IsDecoded() const
    { 
        return _decodedOctets; 
    }

    bool
    IsDecodedOctets() const
    {
        return _decodedOctets;
    }

    bool
    IsDecodedCharacters() const
    {
        return _decodedCharacters;
    }

    const Tag& 
    GetDecodedTag() const
    { 
        ITS_REQUIRE(IsDecoded());
        return _decodedTag;
    }

    const Length& 
    GetDecodedLength() const
    {
        ITS_REQUIRE(IsDecoded());
        return _decodedLength;
    }

    const Octets& 
    GetDecodedOctets() const
    { 
        ITS_REQUIRE(IsDecoded());
        return _decodedOctetsData;
    }

    const Characters&
    GetDecodedCharacters() const
    {
        ITS_REQUIRE(IsDecoded());
        return _decodedCharactersData;
    }

    const AsnDescOpenType& 
    GetDescription() const
    {
        return *static_cast<AsnDescOpenType*>(_description);
    }

    void 
    SetDescription(AsnDescOpenType* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    virtual AsnObject* 
    Clone() const
    { 
        return new AsnOpenType(*this); 
    }

    virtual bool Equals(const AsnObject& rhs) const;

    virtual std::string 
    GetName() const
    { 
        return "OPEN TYPE"; 
    }

    virtual std::string 
    GetBaseName() const
    { 
        return "OPEN TYPE"; 
    }

    virtual void Print(std::ostream& os, size_t level = 0) const;

public: // Pseudo-protected.

    virtual Octets* InternalEncodeBer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodeBer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual Octets* InternalEncodePer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodePer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual Characters* InternalEncodeToXml(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void InternalDecodeFromXml(
                            Characters& characters,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

protected:

    void EncodeCheck(const AsnOptions& asnOptions);
    void DecodeCheck(Octets& octets, const AsnOptions& asnOptions);
    void DecodeCheck(Characters& characters, const AsnOptions& asnOptions);

    AsnObject*  _openType;
    bool        _decodedOctets;
    bool        _decodedCharacters;
    Tag         _decodedTag;
    Length      _decodedLength;
    Octets      _decodedOctetsData;
    Characters  _decodedCharactersData;
};

} // namespace its.

#endif // !defined(_ASN_OPEN_TYPE_H_)
