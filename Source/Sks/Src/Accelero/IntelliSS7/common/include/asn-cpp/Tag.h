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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:07  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
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
// LOG: Revision 5.5  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
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
// ASN.1 runtime Tag class definition.
//

#if !defined(_ASN_TAG_H_)
#define _ASN_TAG_H_

#ident "$Id: Tag.h,v 1.1.1.1 2007-10-08 11:11:37 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnError.h>
#include <Octets.h>

namespace its {

class Tag  
{
public:

    Tag(byte tagClass, byte type, unsigned long number)
    :   _tagClass(tagClass),
        _type(type),
        _number(number)
    {
        // Nothing else to do.
    }

    Tag(Octets& octets, const AsnOptions& asnOptions = AsnOptions())
    {
        Decode(octets, asnOptions);
    }

	Tag()
    :   _tagClass(ASN_CLASS_UNIVERSAL),
        _type(ASN_PRIMITIVE),
        _number(ASN_BOOLEAN)
    {
        // Nothing else to do.
    }

    Tag(const Tag& rhs)
    :   _tagClass(rhs._tagClass),
        _type(rhs._type),
        _number(rhs._number)
    {
        // Nothing else to do.
    }

	virtual ~Tag()
    {
        // Nothing to do.
    }

    Tag& 
    operator=(const Tag& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            _tagClass   = rhs._tagClass;
            _type       = rhs._type;
            _number     = rhs._number;
            return *this;
        }
    }

    bool 
    operator==(const Tag& rhs) const
    { 
        return Equals(rhs); 
    }

    void 
    SetTagClass(byte tagClass)
    {
        _tagClass = tagClass;
    }

    void 
    SetType(byte type)
    {
        _type = type;
    }

    void 
    SetNumber(unsigned long number)
    { 
        _number = number; 
    }

    byte 
    GetTagClass() const
    {
        return _tagClass;
    }

    byte 
    GetType() const
    {
        return _type;
    }

    unsigned long 
    GetNumber() const
    { 
        return _number; 
    }

    Octets* Encode(const AsnOptions& asnOptions = AsnOptions());

    void Decode(Octets& octets, const AsnOptions& asnOptions = AsnOptions());

    void DecodePreserveOffset(
                    Octets& octets, 
                    const AsnOptions& asnOptions = AsnOptions());

    Tag* 
    Clone() const
    { 
        return new Tag(*this); 
    }

    bool 
    Equals(const Tag& rhs) const
    {
        if (_tagClass   == rhs._tagClass &&
            _type       == rhs._type     &&
            _number     == rhs._number)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string 
    GetEncodeExtendedErrorText(AsnError error)
    { 
        return "No extended encode error text available for Tag."; 
    }

    std::string 
    GetDecodeExtendedErrorText(AsnError error, const Octets& octets)
    { 
        return "No extended decode error text available for Tag."; 
    }

    // Tag classes.
    static const byte ASN_CLASS_UNIVERSAL;
    static const byte ASN_CLASS_APPLICATION;
    static const byte ASN_CLASS_CONTEXT_SPECIFIC;
    static const byte ASN_CLASS_PRIVATE;

    // Tag types.
    static const byte ASN_PRIMITIVE;
    static const byte ASN_CONSTRUCTED;

    // Universal tag numbers.
    static const unsigned long ASN_BOOLEAN;
    static const unsigned long ASN_INTEGER;
    static const unsigned long ASN_BIT_STRING;
    static const unsigned long ASN_OCTET_STRING;
    static const unsigned long ASN_NULL;
    static const unsigned long ASN_OBJECT_IDENTIFIER;
    static const unsigned long ASN_OBJECT_DESCRIPTOR;
    static const unsigned long ASN_EXTERNAL;
    static const unsigned long ASN_REAL;
    static const unsigned long ASN_ENUMERATED;
    static const unsigned long ASN_ENCRYPTED;
    static const unsigned long ASN_EMBEDDED_PDV;
    static const unsigned long ASN_UTF8_STRING;
    static const unsigned long ASN_RELATIVE_OID;
    // 14 - 15 reserved for future versions.
    static const unsigned long ASN_SEQUENCE;
    static const unsigned long ASN_SET;
    static const unsigned long ASN_NUMERIC_STRING;
    static const unsigned long ASN_PRINTABLE_STRING;
    static const unsigned long ASN_TELETEX_STRING;
    static const unsigned long ASN_VIDEOTEX_STRING;
    static const unsigned long ASN_IA5_STRING;
    static const unsigned long ASN_UTC_TIME;
    static const unsigned long ASN_GENERALIZED_TIME;
    static const unsigned long ASN_GRAPHICS_STRING;
    static const unsigned long ASN_VISIBLE_STRING;
    static const unsigned long ASN_GENERAL_STRING;
    static const unsigned long ASN_UNIVERSAL_STRING;
    static const unsigned long ASN_CHARACTER_STRING;
    static const unsigned long ASN_BMP_STRING;
    // 31 reserved for future versions.

    // Helper constant for encoding/decoding extended tag numbers.
    static const unsigned long ASN_EXTENDED;
    
    // Binary format helper constants.
    static const int  ASN_CLASS_SHIFT;
    static const byte ASN_CLASS_BITS;
    static const int  ASN_TYPE_SHIFT;
    static const byte ASN_TYPE_BITS;
    static const byte ASN_NUMBER_BITS;
    static const byte ASN_OCTET_BITS;
    static const byte ASN_OCTETS_FOLLOW;
    static const int  ASN_MAX_LENGTH;
    static const int  ASN_LONG_SHIFT;

protected:

    bool IsUniversal(unsigned long number);

    bool 
    Invariant()
    {
        if (_tagClass == ASN_CLASS_UNIVERSAL && !IsUniversal(_number))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    byte          _tagClass;
    byte          _type;
    unsigned long _number;
};


//
// ReplaceTagCallback (abstract base class). To be used for protocol standards
// that are not fully compliant with ASN.1 (e.g. two identical context tags in 
// a SET).
//
class ReplaceTagCallback
{
public:

    // Used by runtime to decide tag replacement.
    virtual Tag GetEncodeToBeReplacedTag()  const = 0;

    // MUST be used by 'ReplaceTagAfterEncoding' in concrete heirs.
    virtual Tag GetEncodeReplacedTag()      const = 0;

    // Used by runtime to decide tag replacement.
    virtual Tag GetDecodeToBeReplacedTag()  const = 0;

    // MUST be used by 'ReplaceTagBeforeEncoding' in concrete heirs.
    virtual Tag GetDecodeReplacedTag()      const = 0;

    // Used by runtime to decide tag replacement. MUST return either the ASN.1
    // type name for which the tag MAY be replaced or "" (i.e. if empty 
    // string) if for any types.
    virtual std::string GetTypeName()   const = 0;

    // Argument 'octets' contains the value (TLV) of the element. MUST not be
    // modified (i.e. do a copy if required). MUST return the "after encoding"
    // tag value (i.e. the tag value that is part of the protocol standard).
    virtual Tag ReplaceTagAfterEncoding(const Octets& octets)  const = 0;

    // Argument 'octets' contains the value TLV of the enclosing container type
    // (SEQUENCE or SET) with the offset positioned at the beginning of the 
    // element TLV. MUST not be modified (i.e. do a copy if required). MUST 
    // return the "before decoding" tag value (i.e. the tag value that is not
    // part of the protocol standard and that is used to satisfy ASN.1 rules
    // for the ASN.1 runtime).
    virtual Tag ReplaceTagBeforeDecoding(const Octets& octets) const = 0;

};

} // namespace its.

#endif // !defined(_ASN_TAG_H_)
