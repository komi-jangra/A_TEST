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
//  ID: $Id: asncc_tag.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////



#include <asncc_tag.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


Tag::Tag()
:   tagClass(CLASS_UNIVERSAL),
    type(TYPE_PRIMITIVE),
    number(UNIVERSAL_ILLEGAL),
    mode(MODE_EXPLICIT),
    isAny(false)
{
}



Tag::Tag(TagClass tagClassParam, long numberParam, TagMode modeParam)
:   isAny(false)
{
    REQUIRE(tagClassParam == CLASS_UNIVERSAL        ||
            tagClassParam == CLASS_APPLICATION      ||
            tagClassParam == CLASS_CONTEXT_SPECIFIC ||
            tagClassParam == CLASS_PRIVATE);

    REQUIRE(numberParam >= 0);

    REQUIRE(modeParam == MODE_EXPLICIT      ||
            modeParam == MODE_IMPLICIT      ||
            modeParam == MODE_AUTOMATIC);

    tagClass    = tagClassParam;
    number      = numberParam;
    mode        = modeParam;

    type        = TYPE_PRIMITIVE;
}


string 
Tag::GetTagClassString() const
{
    switch (tagClass)
    {
    case CLASS_UNIVERSAL:
        return "CLASS_UNIVERSAL";
    case CLASS_APPLICATION:
        return "CLASS_APPLICATION";
    case CLASS_CONTEXT_SPECIFIC:
        return "CLASS_CONTEXT_SPECIFIC";
    case CLASS_PRIVATE:
        return "CLASS_PRIVATE";

    default:
        {
            bool must_not_be_reached = false;
            ASSERT(must_not_be_reached);
            return "Not Reached";
        }
    }
}


string 
Tag::GetTagTypeString() const
{
    switch (type)
    {
    case TYPE_PRIMITIVE:
        return "PRIMITIVE";
    case TYPE_CONSTRUCTED:
        return "CONSTRUCTED";

    default:
        {
            bool must_not_be_reached = false;
            ASSERT(must_not_be_reached);
            return "Not Reached";
        }
    }
}


void
Tag::Accept(Visitor* visitor)
{
    visitor->VisitTag(this);
}


string
Tag::ToString() const
{
    ostrstream ostrs;

    Print(ostrs);

    ostrs << '\0';

    string result(ostrs.str());

    ostrs.rdbuf()->freeze(false);

    return result;
}


void
Tag::Print(ostream& os) const
{
    os << "[";

    if (tagClass == CLASS_UNIVERSAL)
    {
        os << "UNIVERSAL ";
    }
    else if (tagClass == CLASS_APPLICATION)
    {
        os << "APPLICATION "; 
    }
    else if (tagClass == CLASS_CONTEXT_SPECIFIC)
    {
        os << "";
    }
    else if (tagClass == CLASS_PRIVATE)
    {
        os << "PRIVATE ";
    }
    else
    {
        os << "-- COMPILER ERROR: unknown tag class. -- ";
    }

    os << number;

    os << "]";

    if (mode == MODE_IMPLICIT)
    {
        os << " IMPLICIT ";
    }
    else if (mode == MODE_EXPLICIT)
    {
        os << " EXPLICIT ";
    }
    else if (mode == MODE_AUTOMATIC)
    {
        os << " AUTOMATIC ";
    }
    else
    {
        os << "-- COMPILER ERROR: unknown tag mode. -- ";
    }
}


void
Tag::PrintDebug(ostream& os) const
{
    os << "[";


    // Class.

    if (tagClass == CLASS_UNIVERSAL)
    {
        os << " UNIV ";
    }
    else if (tagClass == CLASS_APPLICATION)
    {
        os << " APPL "; 
    }
    else if (tagClass == CLASS_CONTEXT_SPECIFIC)
    {
        os << " CTXT ";
    }
    else if (tagClass == CLASS_PRIVATE)
    {
        os << " PRIV ";
    }
    else
    {
        os << " -- COMPILER ERROR: unknown tag class. -- ";
    }


    // Type.

    if (type == TYPE_PRIMITIVE)
    {
        os << "P ";
    }
    else if (type == TYPE_CONSTRUCTED)
    {
        os << "C ";
    }
    else
    {
        os << "-- COMPILER ERROR: unknown tag type. -- ";
    }


    // Number.

    os << number << " ";


    // Mode.

    if (mode == MODE_IMPLICIT)
    {
        os << "IMPL ";
    }
    else if (mode == MODE_EXPLICIT)
    {
        os << "EXPL ";
    }
    else if (mode == MODE_AUTOMATIC)
    {
        os << "AUTO ";
    }
    else
    {
        os << "-- COMPILER ERROR: unknown tag mode. -- ";
    }


    os << "]";
}


