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
//  ID: $Id: parse_repetition.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_repetition.h: Repetition class interface.   
//
//


#if !defined(_PARSE_REPETITION_H_)
#define _PARSE_REPETITION_H_

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
// Forward declarations.
//

class Keyword;


////////////////////////////////////////////////////////////////////////////////
//
//  Repetition. Constructs whose specimens are sequences of specimens of a 
//  specified base construct, delimited or not by a specified keyword separator
//  or a specified construct separator.
//
    
class Repetition : public Construct
{
public:

    Repetition(Parser& primaryParserParam) 
    :   Construct(primaryParserParam),
        commitOnKeywordSeparator(true),
        commitOnConstructSeparator(true),
        atLeastConstraint(1),
        atMostConstraint((size_t)(-1)),
        keywordSeparator(NULL),
        constructSeparator(NULL)
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    Repetition(const Repetition& rhs);


    // Default assignment operator not ok.

    Repetition& operator=(const Repetition& rhs);


    //
    //  Reminder: Clone MUST be defined in ALL concrete heirs.
    //


    virtual ~Repetition();


    //
    //  Type of construct.
    //

    virtual int
    GetType() const
    { return CONSTRUCT_TYPE_REPETITION; }


    //
    //  Commit on keyword separator (true by default).
    //

    bool
    IsCommitOnKeywordSeparator() const
    { return commitOnKeywordSeparator; }

    void
    SetCommitOnKeywordSeparator()
    { commitOnKeywordSeparator = true; }

    void
    UnsetCommitOnKeywordSeparator()
    { commitOnKeywordSeparator = false; }


    //
    //  Commit on construct separator (true by default).
    //

    bool
    IsCommitOnConstructSeparator() const
    { return commitOnConstructSeparator; }

    void
    SetCommitOnConstructSeparator()
    { commitOnConstructSeparator = true; }

    void
    UnsetCommitOnConstructSeparator()
    { commitOnConstructSeparator = false; }


    //
    //  At least constraint.
    //

    void
    SetAtLeastConstraint(size_t atLeastConstraintParam)
    { 
        ITS_REQUIRE(atLeastConstraintParam >= 1);
        ITS_REQUIRE(atLeastConstraintParam <= GetAtMostConstraint());

        atLeastConstraint = atLeastConstraintParam;
    }

    size_t
    GetAtLeastConstraint() const
    { return atLeastConstraint; }

    bool
    HasAtLeastConstraint() const
    { return atLeastConstraint != 1; }


    //
    //  At most constraint.
    //

    void
    SetAtMostConstraint(size_t atMostConstraintParam)
    {
        ITS_REQUIRE(atMostConstraintParam >= 1);
        ITS_REQUIRE(atMostConstraintParam >= GetAtLeastConstraint());

        atMostConstraint = atMostConstraintParam;
    }

    size_t
    GetAtMostConstraint() const
    { return atMostConstraint; }

    bool
    HasAtMostConstraint() const
    { return atMostConstraint != (size_t)(-1); }


    //
    //  Keyword separator.
    //

    void SetKeywordSeparator(const std::string& name);

    bool
    HasKeywordSeparator() const
    { return keywordSeparator != NULL; }


    //
    //  Construct separator.
    //

    void SetConstructSeparator(Construct* construct);

    bool 
    HasConstructSeparator() const
    { return constructSeparator != NULL; }


    //
    //  Apply semantic actions on current construct by applying semantic actions  
    //  on children in sequence.
    //

    virtual void InAction(Parser& currentParser);

    
    //
    //  Apply middle semantic action after parsing each child. Does nothing by
    //  default. May be redefined in heirs.
    //

    virtual void 
    MiddleAction(Parser& currentParser)
    {
        // Do nothing by default.
    }


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

    bool commitOnKeywordSeparator;

    bool commitOnConstructSeparator;

    size_t atLeastConstraint;

    size_t atMostConstraint;

    Keyword* keywordSeparator;

    Construct* constructSeparator;

    //
    //  List of separator constructs parsed (used only if separator is 
    //  construct and therefore constructSeparator is not NULL).
    //

    ConstructList constructSeparators;


    //
    //  Attempt to find a repetition of constructs with separators or not 
    //  starting at current position. Set committed to true at first separator
    //  if commitOnSeparator is true (commitOnSeparator is true by default).
    //

    virtual void ParseBody(Parser& currentParser);


    //
    //  Parse one element of the repetition and return true if successful.
    //

    virtual bool ParseOne(Parser& currentParser);


    //
    //  Expand next construct to be parsed and insert it in the list of items of
    //  the repetition.
    //

    virtual void Expand();


    // Must not be used.

    Repetition()
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};


////////////////////////////////////////////////////////////////////////////////
//
//  RepetitionTemplate. Template class to define Repetition constructs.
//

template<class N>
class RepetitionTemplate : public Repetition
{
public:

    RepetitionTemplate(Parser& primaryParserParam)
    :   Repetition(primaryParserParam),
        name(N::GetName())
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    RepetitionTemplate(const RepetitionTemplate& rhs)
    :   Repetition(rhs)
    {
        name = rhs.name;
    }


    // Default assignment operator not ok.

    RepetitionTemplate&
    operator=(const RepetitionTemplate& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            static_cast<Repetition&>(*this) = rhs;

            name = rhs.name;

            return *this;
        }
    }

    virtual ~RepetitionTemplate()
    {
        // Nothing to do.
    }

    virtual Construct*
    Clone() const
    { return new RepetitionTemplate(*this); }

    virtual const std::string&
    GetName() const
    { return name; }

    virtual Production& GetProduction();

    virtual void PreAction(Parser& currentParser);

    virtual void MiddleAction(Parser& currentParser);

    virtual void PostAction(Parser& currentParser);

protected:

    std::string name;

    // Must not be used.

    RepetitionTemplate()
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }
};


////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_REPETITION. Macro to define Repetition constructs.
//
//  Cannot be traced in by debugger. Switch to template approach if required.
//
//  MUST be kept in sync with template RepetitionTemplate class.
//

//
//  MP_ClassName => name of class.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_REPETITION(MP_ClassName, MP_Name)                \
                                                                            \
class MP_ClassName : public its::Repetition                                 \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName(its::Parser& primaryParserParam)                           \
    :   its::Repetition(primaryParserParam),                                \
        name(MP_Name)                                                       \
    {}                                                                      \
                                                                            \
    MP_ClassName(const MP_ClassName& rhs)                                   \
    :   its::Repetition(rhs)                                                \
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
            static_cast<its::Repetition&>(*this) = rhs;                     \
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
    virtual void MiddleAction(its::Parser& currentParser);                  \
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

#endif // !defined(_PARSE_REPETITION_H_)
