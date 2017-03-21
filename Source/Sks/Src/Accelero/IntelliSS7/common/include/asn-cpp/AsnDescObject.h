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
// LOG: Revision 5.5  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.4  2002/01/10 00:09:24  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.3  2002/01/04 15:58:11  hdivoux
// LOG: More update for XER support.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnDescObject class definition.
//

#if !defined(_ASN_DESC_OBJECT_H_)
#define _ASN_DESC_OBJECT_H_

#ident "$Id: AsnDescObject.h,v 1.1.1.1 2007-10-08 11:11:36 bsccs2 Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <Tag.h>

namespace its {

// Forward declaration.
class AsnObject;

class AsnDescObject
{
public:

    AsnDescObject()
    :   _clauseOptional(false),
        _clauseDefault(false),
        _cloneForFactory(NULL), 
        _cloneForDefaultFactory(NULL),
        _namedTypeName(""),
        _typeName("")
    {}

    AsnDescObject(const AsnDescObject& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }

    virtual ~AsnDescObject();

    virtual AsnDescObject* Clone() const = 0;

    AsnObject* Factory() const;

    void SetCloneForFactory(AsnObject* clone);

    AsnObject* DefaultFactory() const;

    void SetCloneForDefaultFactory(AsnObject* clone);

    bool 
    IsClauseOptional() const
    { 
        return _clauseOptional; 
    }

    bool 
    IsClauseDefault() const
    { 
        return _clauseDefault; 
    }

    void 
    SetClauseOptional()
    { 
        _clauseOptional = true; 
    }

    void 
    SetClauseDefault()
    { 
        _clauseDefault = true; 
    }

    virtual bool 
    TagIdentify(const Tag& tag) const
    {
        ITS_REQUIRE(TagLevelNumber() >= 1);
        return tag == *(_tagStack.front());
    }

    virtual const Tag& 
    TagIdentity() const
    {
        ITS_REQUIRE(TagLevelNumber() >= 1);
        return *(_tagStack.front());
    }

    virtual size_t 
    TagLevelNumber() const
    { 
        return _tagStack.size();
    }

    virtual const std::vector<Tag*>& 
    TagStack() const
    {
        return _tagStack;
    }

    virtual void TagAddLevel(Tag* tag);

    void
    SetNamedTypeName(const char* namedTypeName)
    {
        ITS_REQUIRE(namedTypeName != NULL);
        _namedTypeName = namedTypeName;
    }

    const char*
    GetNamedTypeName() const
    {
        return _namedTypeName;
    }

    bool
    IsNamedType() const
    {
        return strlen(_namedTypeName) != 0;
    }

    void
    SetTypeName(const char* typeName)
    {
        ITS_REQUIRE(typeName != NULL);
        _typeName = typeName;
    }

    const char*
    GetTypeName() const
    {
        return _typeName;
    }

    bool
    HasTypeName() const
    {
        return strlen(_typeName) != 0;
    }

    std::string GetName() const;
    std::string GetBaseName() const;

public: // Pseudo-protected.

    bool                _clauseOptional;
    bool                _clauseDefault;
    std::vector<Tag*>   _tagStack;
    AsnObject*          _cloneForFactory;
    AsnObject*          _cloneForDefaultFactory;
    const char*         _namedTypeName;
    const char*         _typeName;
};

} // namespace its.

#endif // !defined(_ASN_DESC_OBJECT_H_)

