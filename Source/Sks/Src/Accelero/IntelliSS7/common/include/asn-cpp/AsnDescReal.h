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
// LOG: Revision 8.2  2005/03/21 13:50:56  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnDescReal class definition.
//

#if !defined(_ASN_DESC_REAL_H_)
#define _ASN_DESC_REAL_H_

#ident "$Id: AsnDescReal.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnDescObject.h>

namespace its {

class AsnDescReal : public AsnDescObject
{
public:

    AsnDescReal()
    :   _clauseRange(false), 
        _defaultValue(0.0),
        _maxValue(0.0), 
        _minValue(0.0)
    {}

    AsnDescReal(const AsnDescReal& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }

    virtual ~AsnDescReal()
    {
        // Nothing to do.
    }

    virtual AsnDescObject* 
    Clone() const
    { 
        return new AsnDescReal(*this); 
    }

    bool 
    IsClauseRange() const
    { 
        return _clauseRange; 
    }

    void 
    SetClauseRange()
    { 
        _clauseRange = true; 
    }

    void 
    SetMaxValue(double maxValue)
    { 
        _maxValue = maxValue; 
    }

    double 
    GetMaxValue() const
    { 
        return _maxValue; 
    }

    void 
    SetMinValue(double minValue)
    { 
        _minValue = minValue; 
    }

    double 
    GetMinValue() const
    { 
        return _minValue; 
    }

    void 
    SetDefaultValue(double defaultValue)
    { 
        _defaultValue = defaultValue; 
    }

    double     
    GetDefaultValue()
    { 
        return _defaultValue; 
    }

public: // Pseudo-protected.

    bool    _clauseRange;
    double  _defaultValue;
    double  _maxValue;
    double  _minValue;

};

} // namespace its.

#endif // !defined(_ASN_DESC_REAL_H_)
