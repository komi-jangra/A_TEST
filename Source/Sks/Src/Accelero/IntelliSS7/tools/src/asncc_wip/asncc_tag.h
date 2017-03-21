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
//  ID: $Id: asncc_tag.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(_ASNCC_TAG_H_)
#define _ASNCC_TAG_H_

#include <asncc.h>
#include <asncc_assertion.h>
#include <asncc_visitor.h>


class Tag 
{
public:

    enum TagClass {
        CLASS_UNIVERSAL                 = 0,
        CLASS_APPLICATION               = 1,
        CLASS_CONTEXT_SPECIFIC          = 2,
        CLASS_PRIVATE                   = 3
    };

    enum TagType {
        TYPE_PRIMITIVE                  = 0,
        TYPE_CONSTRUCTED                = 1
    };

    enum TagMode {
        MODE_IMPLICIT,
        MODE_EXPLICIT,
        MODE_AUTOMATIC
    };

    enum UniversalTag {
        UNIVERSAL_ILLEGAL               = 0,
        UNIVERSAL_BOOLEAN               = 1,
        UNIVERSAL_INTEGER               = 2,
        UNIVERSAL_BIT_STRING            = 3,
        UNIVERSAL_OCTET_STRING          = 4,
        UNIVERSAL_NULL                  = 5,
        UNIVERSAL_OBJECT_IDENTIFIER     = 6,
        UNIVERSAL_OBJECT_DESCRIPTOR     = 7,
        UNIVERSAL_EXTERNAL              = 8,
        UNIVERSAL_REAL                  = 9,
        UNIVERSAL_ENUMERATED            = 10,
        UNIVERSAL_EMBEDDED_PDV          = 11, 
      
        // 12 - 15 reserved for future versions.

        UNIVERSAL_SEQUENCE              = 16,
        UNIVERSAL_SET                   = 17,
        UNIVERSAL_NUMERIC_STRING        = 18,
        UNIVERSAL_PRINTABLE_STRING      = 19,
        UNIVERSAL_TELETEX_STRING        = 20,
        UNIVERSAL_VIDEOTEX_STRING       = 21,
        UNIVERSAL_IA5_STRING            = 22,
        UNIVERSAL_UTC_TIME              = 23,
        UNIVERSAL_GENERALIZED_TIME      = 24,
        UNIVERSAL_GRAPHIC_STRING        = 25,
        UNIVERSAL_VISIBLE_STRING        = 26,
        UNIVERSAL_GENERAL_STRING        = 27,
        UNIVERSAL_UNIVERSAL_STRING      = 28,
        UNIVERSAL_BMP_STRING            = 30
    };


    Tag();

    Tag(TagClass tagClassParam, long numberParam, TagMode modeParam);

    // Default copy constructor ok.

    ~Tag()
    {
        // Nothing to do.
    }

    // Default assignment operator ok.

    Tag*
    Clone() const
    { return new Tag(*this); }

    bool 
    operator==(const Tag& rhs) const
    { return Equals(rhs); }

    bool
    Equals(const Tag& rhs) const
    {
        return tagClass     == rhs.tagClass     &&
               type         == rhs.type         &&
               number       == rhs.number       &&
               mode         == rhs.mode;
    }

    void 
    SetTagClass(TagClass tagClassParam)
    {
        REQUIRE(tagClassParam == CLASS_UNIVERSAL        ||
                tagClassParam == CLASS_APPLICATION      ||
                tagClassParam == CLASS_CONTEXT_SPECIFIC ||
                tagClassParam == CLASS_PRIVATE)

        tagClass = tagClassParam;
    }

    void 
    SetTagType(TagType typeParam)
    {
        REQUIRE(typeParam == TYPE_PRIMITIVE     ||
                typeParam == TYPE_CONSTRUCTED);

        type = typeParam;
    }

    void 
    SetNumber(long numberParam)
    {
        REQUIRE(numberParam >= 0);

        number = numberParam;
    }

    void
    SetTagMode(TagMode modeParam)
    {
        REQUIRE(modeParam == MODE_IMPLICIT      ||
                modeParam == MODE_EXPLICIT      ||
                modeParam == MODE_AUTOMATIC);

        mode = modeParam;
    }

    TagClass 
    GetTagClass() const
    { return tagClass; }

    TagType 
    GetTagType() const 
    { return type; }

    long 
    GetNumber() const
    { return number; }

    TagMode
    GetTagMode() const
    { return mode; }

    std::string GetTagClassString() const;

    std::string GetTagTypeString() const;

    void Accept(Visitor* visitor);

    std::string ToString() const;

    void Print(std::ostream& os) const;

    void PrintDebug(std::ostream& os) const;

    ////////////////////////////////////////////////////////////////////////////

    // Set current tag to be special tag any.

    void
    SetAny()
    { isAny = true; }


    // Is current tag special tag any?

    bool
    IsAny() const
    { return isAny; }

    ////////////////////////////////////////////////////////////////////////////

protected:

    TagClass    tagClass;
    TagType     type;
    long        number;

    TagMode     mode;

    ////////////////////////////////////////////////////////////////////////////

    bool        isAny;  // To represent special tag any.

    ////////////////////////////////////////////////////////////////////////////

};





#endif // !defined(_ASNCC_TAG_H_)
