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
// LOG: Revision 8.3  2005/03/21 13:50:57  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1.4.1  2003/07/07 12:23:06  mmanikandan
// LOG: License check capability is added.
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.8  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.7  2002/01/11 22:19:19  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.6  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.5  2002/01/07 22:59:02  hdivoux
// LOG: First shot at XER encoding.
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
// ASN.1 runtime AsnObject class definition.
//

#if !defined(_ASN_OBJECT_H_)
#define _ASN_OBJECT_H_

#ident "$Id: AsnObject.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnError.h>
#include <Octets.h>
#include <Characters.h>

#include <its_license.h>

namespace its {

// Forward declaration.
class AsnDescObject;

class AsnObject
{
public:

    AsnObject() 
    :   _description(NULL),
        _deleteSubcomponentsAutomatically(true)
    {}

    AsnObject(const AsnObject& rhs)
    {
        _description = rhs._description;
        _deleteSubcomponentsAutomatically = 
            rhs._deleteSubcomponentsAutomatically;
    }

    virtual ~AsnObject()
    {
        // Nothing to do.
    }

    void 
    Assign(const AsnObject& rhs)
    {
        if (_description)
        {
            if (rhs._description)
            {
                _description = rhs._description;
            }
            else
            {
                _description = NULL;
            }
        }
        else
        {
            if (rhs._description)
            {
                _description = rhs._description;
            }
            else
            {
                _description = NULL;
            }
        }

        _deleteSubcomponentsAutomatically = 
            rhs._deleteSubcomponentsAutomatically;
    }

    virtual Octets* Encode(const AsnOptions& asnOptions = AsnOptions());

    virtual void Decode(
                    Octets& octets, 
                    const AsnOptions& asnOptions = AsnOptions());

    virtual Characters* EncodeToXml(
                            const AsnOptions& asnOptions = AsnOptions());

    virtual void DecodeFromXml(
                            Characters& characters,
                            const AsnOptions& asnOptions = AsnOptions());

    virtual std::string GetName() const = 0;
    virtual std::string GetBaseName() const = 0;

    virtual AsnObject* Clone() const = 0;

    const AsnDescObject& 
    GetPolymorphDescription() const
    {
        return *_description;
    }

    void 
    SetDescription(AsnDescObject* description)
    {
        ITS_REQUIRE(description != NULL);
        _description = description;
    }

    virtual bool Equals(const AsnObject& rhs) const = 0;

    virtual void Print(std::ostream& os, size_t level = 0) const = 0;

    virtual std::string GetEncodeExtendedErrorText(AsnError error);

    virtual std::string GetDecodeExtendedErrorText(
                            AsnError error,
                            const Octets& octets);

    virtual std::string GetDecodeExtendedErrorText(
                            AsnError error,
                            const Characters& characters);

    // To use automatic subcomponents memory management (default).
    void
    SetDeleteSubcomponentsAutomatically()
    { 
        _deleteSubcomponentsAutomatically = true; 
    }

    // To use manual subcomponents memory management (not recommended).
    void
    UnsetDeleteSubcomponentsAutomatically()
    { 
        _deleteSubcomponentsAutomatically = false; 
    }

    // To check if automatic subcomponents memory management.
    bool
    IsDeleteSubcomponentsAutomatically() const
    { 
        return _deleteSubcomponentsAutomatically; 
    }

public: // Pseudo-protected.

    virtual Octets* InternalEncodeBer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description) = 0;

    virtual void InternalDecodeBer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description) = 0;

    virtual Octets* InternalEncodePer(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description) = 0;

    virtual void InternalDecodePer(
                            Octets& octets,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description) = 0;

    virtual Characters* InternalEncodeToXml(
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description) = 0;

    virtual void InternalDecodeFromXml(
                            Characters& characters,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description) = 0;

protected:

    virtual Octets* EncodeTagLengthValue(
                            const Octets& value, 
                            const AsnOptions& asnOptions);

    virtual void DecodeRemoveExtraTagLength(
                            Octets& octets,
                            const AsnOptions& asnOptions);

    virtual void EncodeXmlElementStartTag(
                            std::string& str,
                            const AsnOptions& asnOptions, 
                            size_t level,
                            const AsnDescObject& description);

    virtual void EncodeXmlElementEndTag(
                            std::string& str,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void DecodeXmlElementStartTag(
                            Characters& characters,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    virtual void DecodeXmlElementEndTag(
                            Characters& characters,
                            const AsnOptions& asnOptions,
                            size_t level,
                            const AsnDescObject& description);

    std::string GetLevelShift(size_t level) const;

    AsnDescObject*  _description;
    bool            _deleteSubcomponentsAutomatically;
};

// AsnObject ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const AsnObject& asnObject);

} // namespace its.

extern ITS_BOOLEAN CheckLicense(int val);

#endif // !defined(_ASN_OBJECT_H_)

