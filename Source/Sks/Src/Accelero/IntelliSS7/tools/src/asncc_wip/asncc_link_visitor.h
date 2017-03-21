////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: asncc_link_visitor.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_LINK_VISITOR_H_)
#define _ASNCC_LINK_VISITOR_H_

#include <asncc_visitor.h>


////////////////////////////////////////////////////////////////////////////////
//
//  LinkVisitor interface.
//

class LinkVisitor : public Visitor
{
public:

    LinkVisitor(AsnCC& asnCCParam, Module* moduleParam) 
    :   asnCC(asnCCParam),
        module(moduleParam)
    {
        REQUIRE(module != NULL);

        SetVisitRecursive();
    }

    // Default copy constructor ok.

    // Default destructor ok (no memory management).

    // Default assignment operator ok.

    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitDefinedType(DefinedType* definedType);

    ////////////////////////////////////////////////////////////////////////////

    virtual void VisitDefinedValue(DefinedValue* definedValue);

    ////////////////////////////////////////////////////////////////////////////


    ////////////////////////////////////////////////////////////////////////////


    AsnCC&
    GetAsnCC()
    { return asnCC; }

    Module*
    GetModule() const
    { return module; }

protected:

    AsnCC& asnCC;

    Module* module;

};


#endif // !defined(_ASNCC_LINK_VISITOR_H_)
