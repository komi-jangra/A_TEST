////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: parse_choice.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_choice.h: Choice class interface.   
//
//


#if !defined(_PARSE_CHOICE_H_)
#define _PARSE_CHOICE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <parse.h>
#include <parse_construct.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Choice. Constructs whose specimens are specimens of constructs chosen among 
//  a specified list.
//

class Choice : public Construct
{
public:

    Choice(Parser& primaryParserParam)
    :   Construct(primaryParserParam),
        retained(NULL)
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    Choice(const Choice& rhs);


    // Default assignment operator not ok.

    Choice& operator=(const Choice& rhs);


    //
    //  Reminder: Clone MUST be defined in ALL concrete heirs.
    //


    virtual ~Choice()
    {
        if (retained != NULL)
        {
            delete retained;
        }

        // TODO: double check that there is nothing else to do.
    }


    //
    //  Type of construct.
    // 

    virtual int
    GetType() const
    { return CONSTRUCT_TYPE_CHOICE; }


    //
    //  Has a valid choice been retained?
    //

    bool
    HasRetained() const
    { return retained != NULL; }


    //
    //  Retained choice (if any).
    //

    Construct&
    GetRetained() const
    {
        ITS_REQUIRE(HasRetained());

        return *retained;
    }


    //
    //  Apply semantic actions to choice if any.
    //

    virtual void InAction(Parser& currentParser);


    //
    //  Get (parsed) value.
    //  

    virtual std::string GetValue() const;


    //
    //  Printing.
    //

    virtual void Print(std::ostream& os, size_t level = 0) const;

    virtual void PrintValue(std::ostream& os) const;


protected:

    //
    //  Child that matches the input. NULL if none.
    //

    Construct* retained; // Must be deleted by destructor if not NULL.


    //
    //  Parse a choice construct. Try each possible expansion and keep the valid
    //  one if any. 
    //

    virtual void ParseBody(Parser& currentParser);


    //
    //  Expand next possible choice.
    //

    virtual void Expand();


    // Must not be used.

    Choice()
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};


////////////////////////////////////////////////////////////////////////////////
//
//  ChoiceTemplate. Template class to define Choice constructs.
//

template<class N>
class ChoiceTemplate : public Choice
{
public:

    ChoiceTemplate(Parser& primaryParserParam)
    :   Choice(primaryParserParam),
        name(N::GetName())
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    ChoiceTemplate(const ChoiceTemplate& rhs)
    :   Choice(rhs)
    {
        name = rhs.name;
    }


    // Default assignment operator not ok.

    ChoiceTemplate&
    operator=(const ChoiceTemplate& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            static_cast<Choice&>(*this) = rhs;

            name = rhs.name;

            return *this;
        }
    }

    virtual ~ChoiceTemplate()
    {
        // Nothing to do.
    }

    virtual Construct*
    Clone() const
    { return new ChoiceTemplate(*this); }

    virtual const std::string&
    GetName() const
    { return name; }

    virtual Production& GetProduction();

    virtual void PreAction(Parser& currentParser);

    virtual void PostAction(Parser& currentParser);

protected:

    std::string name;

    // Must not be used.

    ChoiceTemplate()
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }
};


////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_CHOICE. Macro to define Choice constructs.
//
//  Cannot be traced in by debugger. Switch to template approach if required.
//
//  MUST be kept in sync with template ChoiceTemplate class.
//

//
//  MP_ClassName => name of class.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_CHOICE(MP_ClassName, MP_Name)                    \
                                                                            \
class MP_ClassName : public its::Choice                                     \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName(its::Parser& primaryParserParam)                           \
    :   its::Choice(primaryParserParam),                                    \
        name(MP_Name)                                                       \
    {}                                                                      \
                                                                            \
    MP_ClassName(const MP_ClassName& rhs)                                   \
    :   its::Choice(rhs)                                                    \
    {                                                                       \
        name = rhs.name;                                                    \
    }                                                                       \
                                                                            \
    MP_ClassName&                                                           \
    operator=(const MP_ClassName& rhs)                                      \
    {                                                                       \
        if (this == &rhs)                                                   \
        {                                                                   \
            return *this;                                                   \
        }                                                                   \
        else                                                                \
        {                                                                   \
            static_cast<its::Choice&>(*this) = rhs;                         \
                                                                            \
            name = rhs.name;                                                \
                                                                            \
            return *this;                                                   \
        }                                                                   \
    }                                                                       \
                                                                            \
    virtual ~MP_ClassName()                                                 \
    {}                                                                      \
                                                                            \
    virtual its::Construct*                                                 \
    Clone() const                                                           \
    { return new MP_ClassName(*this); }                                     \
                                                                            \
    virtual const std::string&                                              \
    GetName() const                                                         \
    { return name; }                                                        \
                                                                            \
    virtual its::Production& GetProduction();                               \
                                                                            \
    virtual void PreAction(its::Parser& currentParser);                     \
                                                                            \
    virtual void PostAction(its::Parser& currentParser);                    \
                                                                            \
protected:                                                                  \
                                                                            \
    std::string name;                                                       \
                                                                            \
    MP_ClassName()                                                          \
    {                                                                       \
        bool must_not_be_used = false;                                      \
        ITS_ASSERT(must_not_be_used);                                       \
    }                                                                       \
}



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_CHOICE_H_)
