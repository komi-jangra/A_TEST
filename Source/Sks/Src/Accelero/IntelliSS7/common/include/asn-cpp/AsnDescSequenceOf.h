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
// ASN.1 runtime AsnDescSequenceOf class definition.
//

#if !defined(_ASN_DESC_SEQUENCE_OF_H_)
#define _ASN_DESC_SEQUENCE_OF_H_

#ident "$Id: AsnDescSequenceOf.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnDescObject.h>

namespace its {

class AsnDescSequenceOf : public AsnDescObject
{
public:

    AsnDescSequenceOf()
    :   _clauseSize(false),
        _maxSize(0), 
        _minSize(0), 
        _element(NULL)
    {}

    AsnDescSequenceOf(const AsnDescSequenceOf& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }

    virtual ~AsnDescSequenceOf()
    {
        // Nothing to do.
    }

    virtual AsnDescObject* 
    Clone() const
    { 
        return new AsnDescSequenceOf(*this); 
    }

    bool 
    IsClauseSize() const
    { 
        return _clauseSize; 
    }

    void 
    SetClauseSize()
    { 
        _clauseSize = true; 
    }

    void 
    SetMaxSize(size_t maxSize)
    { 
        _maxSize = maxSize; 
    }

    size_t 
    GetMaxSize() const
    { 
        return _maxSize; 
    }

    void 
    SetMinSize(size_t minSize)
    { 
        _minSize = minSize; 
    }

    size_t 
    GetMinSize() const
    { 
        return _minSize; 
    }

    const AsnDescObject& 
    GetElement() const
    {
        return *_element;
    }

    void 
    SetElement(AsnDescObject* element)
    {
        ITS_REQUIRE(element != NULL);
        _element = element;
    }

    bool 
    Contains(const Tag& tag) const
    {
        ITS_ASSERT(_element != NULL);
        if (_element->TagIdentify(tag))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

public: // Pseudo-protected.

    bool            _clauseSize;
    size_t          _maxSize;
    size_t          _minSize;
    AsnDescObject*  _element;
};

} // namespace its.

#endif // !defined(_ASN_DESC_SEQUENCE_OF_H_)
