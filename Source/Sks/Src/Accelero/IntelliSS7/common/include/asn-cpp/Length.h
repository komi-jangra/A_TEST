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
// LOG: Revision 5.4  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
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
// ASN.1 runtime Length class definition.
//

#if !defined(_ASN_LENGTH_H_)
#define _ASN_LENGTH_H_

#ident "$Id: Length.h,v 1.1.1.1 2007-10-08 11:11:37 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnError.h>
#include <Octets.h>

namespace its {

class Length
{
public:

    Length(long length)
    :   _length(length)
    {
        // Nothing else to do.
    }

    Length(Octets& octets, const AsnOptions& asnOptions = AsnOptions())
    { 
        Decode(octets, asnOptions); 
    }

    Length(const Length& rhs)
    :   _length(rhs._length)
    { 
        // Nothing else to do.
    }

    virtual ~Length()
    {
        // Nothing to do.
    }

    Length& 
    operator=(const Length& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            _length   = rhs._length;
            return *this;
        }
    }

    bool 
    operator==(const Length& rhs) const
    { 
        return Equals(rhs); 
    }

    void 
    SetLength(long length)
    {
        ITS_REQUIRE(length >= 0 || length == ASN_INDEFINITE);
        _length = length;
    }

    long 
    GetLength() const
    {
        return _length;
    }

    bool 
    IsIndefinite()
    { 
        return _length == ASN_INDEFINITE; 
    }

    Octets* Encode(const AsnOptions& asnOptions = AsnOptions());

    void Decode(Octets& octets, const AsnOptions& asnOptions = AsnOptions());

    void DecodePreserveOffset(
                    Octets& octets, 
                    const AsnOptions& asnOptions = AsnOptions());

    bool IsIndefiniteEndMark(const Octets& octets);

    void 
    IndefiniteEndMarkIncrementOffset(Octets octets)
    { 
        octets.IncrementOffset(ASN_INDEFINITE_END_MARK_LENGTH); 
    }

    Length* 
    Clone()
    { 
        return new Length(*this); 
    }

    bool 
    Equals(const Length& rhs) const
    { 
        return _length == rhs._length; 
    }

    std::string 
    GetEncodeExtendedErrorText(AsnError error)
    { 
        return "No extended encode error text available for Length."; 
    }

    std::string 
    GetDecodeExtendedErrorText(AsnError error, const Octets& octets)
    { 
        return "No extended decode error text available for Length."; 
    }

    static const long ASN_INDEFINITE;
    static const byte ASN_INDEFINITE_FORM_VALUE;
    static const byte ASN_SHORT_FORM_MAX_VALUE;
    static const byte ASN_LENGTH_LENGTH_MASK;
    static const byte ASN_LONG_FORM_INDICATOR;
    static const int  ASN_LONG_FORM_MAX_LENGTH;
    static const int  ASN_INDEFINITE_END_MARK_LENGTH;
    static const byte ASN_INDEFINITE_END_MARK_BYTE_ONE;
    static const byte ASN_INDEFINITE_END_MARK_BYTE_TWO;

protected:

    long _length;

};

} // namespace its.

#endif // !defined(_ASN_LENGTH_H_)

