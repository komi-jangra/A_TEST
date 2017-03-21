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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:06  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:58  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:51  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:52  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:55  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.6  2002/01/16 22:13:19  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.5  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:23:28  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:03:21  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnBitString class definition.
//

#if !defined(_ASN_BIT_STRING_H_)
#define _ASN_BIT_STRING_H_

#ident "$Id: AsnBitString.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <Tag.h>
#include <Length.h>
#include <AsnObject.h>
#include <AsnDescBitString.h>

namespace its {

class AsnBitString : public AsnObject
{
public: 

    AsnBitString(const std::vector<bool>& array, bool initialize = true)
    :   _data(array)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnBitString(
        Octets& octets,
        const AsnOptions& asnOptions = AsnOptions(),
        bool initialize = true)
    {
        if (initialize)
        {
            Initialize();
        }

        Decode(octets, asnOptions);
    }

    AsnBitString(bool initialize = true)
    {
        if (initialize)
        {
            Initialize();
        }
    }


    AsnBitString(const AsnBitString& rhs)
    :   AsnObject(rhs)
    {
        _data = rhs._data;
    }

    AsnBitString(AsnDescObject* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    AsnBitString(AsnDescObject* description, const std::vector<bool>& array)
    :   _data(array)
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

    virtual ~AsnBitString()
    {
        // Nothing to do.
    }

    AsnBitString& 
    operator=(const AsnBitString& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            Assign(rhs);
            _data = rhs._data;
            return *this;
        }
    }

    bool 
    operator==(const AsnBitString& rhs) const
    { 
        return Equals(rhs); 
    }

    const std::vector<bool>& 
    GetArray() const
    { 
        return _data; 
    }

    void 
    SetArray(const std::vector<bool>& array)
    { 
        _data = array; 
    }

    void 
    Set()
    {
        for (size_t i = 0; i < _data.size(); i++)
        {
            _data[i] = true;
        }
    }

    void 
    Set(size_t index, bool value = true)
    {
        ITS_REQUIRE(index < GetSize());
        _data[index] = value;
    }

    void 
    Reset()
    {
        for (size_t i = 0; i < _data.size(); i++)
        {
            _data[i] = false;
        }
    }

    void 
    Reset(size_t index)
    {
        ITS_REQUIRE(index < GetSize());
        _data[index] = false;
    }

    bool 
    IsSet(size_t index) const
    { 
        ITS_REQUIRE(index < GetSize());
        return _data[index];
    }

    const AsnDescBitString& 
    GetDescription() const
    {
        return *static_cast<AsnDescBitString*>(_description);
    }

    void 
    SetDescription(AsnDescBitString* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    static Tag* 
    GetUniversalTag()
    {
        return new Tag(
                Tag::ASN_CLASS_UNIVERSAL,
                Tag::ASN_PRIMITIVE,
                Tag::ASN_BIT_STRING);
    }

    virtual AsnObject* 
    Clone() const
    { 
        return new AsnBitString(*this); 
    }

    virtual bool Equals(const AsnObject& rhs) const;

    size_t 
    GetSize() const
    { 
        return _data.size(); 
    }

    virtual std::string 
    GetName() const
    { 
        return "BIT STRING"; 
    }

    virtual std::string 
    GetBaseName() const
    { 
        return "BIT STRING"; 
    }

    virtual void Print(std::ostream& os, size_t level = 0) const;

    // Helper conversion static functions.
    static void VectorBoolToBits(
                            const std::vector<bool>& boolVect,
                            long& numberOfBits,
                            std::vector<byte>& byteVect);

    static void BitsToVectorBool(
                            long numberOfBits,
                            const std::vector<byte>& byteVect,
                            std::vector<bool>& boolVect);

    // Obsolete (for backward compatibility only).
    size_t 
    Size() const
    { 
        return _data.size(); 
    }

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

    std::vector<bool> _data;
};

} // namespace its.

#endif // !defined(_ASN_BIT_STRING_H_)
