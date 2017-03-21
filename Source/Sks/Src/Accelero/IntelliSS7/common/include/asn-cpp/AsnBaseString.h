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
// LOG: Revision 7.1  2002/08/26 22:09:41  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 1.3  2002/01/16 22:13:19  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 1.2  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 1.1  2002/01/02 23:37:11  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnBaseString class definition.
//

#if !defined(_ASN_BASE_STRING_H_)
#define _ASN_BASE_STRING_H_

#ident "$Id: AsnBaseString.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <Tag.h>
#include <Length.h>
#include <AsnObject.h>
#include <AsnDescBaseString.h>

namespace its {

class AsnBaseString : public AsnObject
{
public:

    AsnBaseString(const std::string& str, bool initialize = true)
    :   _data(str)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnBaseString(
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

    AsnBaseString(bool initialize = true)
    {
        if (initialize)
        {
            Initialize();
        }
    }

    AsnBaseString(const AsnBaseString& rhs)
    :   AsnObject(rhs)
    {
        _data = rhs._data;
    }

    AsnBaseString(AsnDescObject* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    AsnBaseString(AsnDescObject* description, const std::string& str)
    :   _data(str)
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

    virtual ~AsnBaseString()
    {
        // Nothing to do.
    }

    AsnBaseString& 
    operator=(const AsnBaseString& rhs)
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
    operator==(const AsnBaseString& rhs) const
    { 
        return Equals(rhs); 
    }

    const std::string& 
    GetString() const
    { 
        return _data; 
    }

    void 
    SetString(const std::string& str)
    { 
        _data = str; 
    }

    const AsnDescBaseString& 
    GetDescription() const
    {
        return *static_cast<AsnDescBaseString*>(_description);
    }

    void 
    SetDescription(AsnDescBaseString* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    virtual AsnObject* 
    Clone() const
    { 
        return new AsnBaseString(*this);
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
        return "BASE STRING"; 
    }

    virtual std::string 
    GetBaseName() const
    {
        return "BASE STRING"; 
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

    std::string _data;
};

} // namespace its.

#endif // !defined(_ASN_BASE_STRING_H_)
