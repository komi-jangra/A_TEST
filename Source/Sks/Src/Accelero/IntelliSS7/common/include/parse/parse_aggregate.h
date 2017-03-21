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
//  ID: $Id: parse_aggregate.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_aggregate.h: Aggregate class interface.   
//
//


#if !defined(_PARSE_AGGREGATE_H_)
#define _PARSE_AGGREGATE_H_

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
//  Aggregate. Constructs whose specimens are obtained by concatenating 
//  specimens of constructs of zero or more specified constructs.
//

class Aggregate : public Construct
{
public:

    Aggregate(Parser& primaryParserParam) 
    :   Construct(primaryParserParam),
        commitThreshold(0),
        commitAlreadyCalled(false)
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    Aggregate(const Aggregate& rhs);


    // Default assignment operator not ok.

    Aggregate& operator=(const Aggregate& rhs);


    //
    //  Reminder: Clone MUST be defined in ALL concrete heirs.
    //


    virtual ~Aggregate()
    {
        // Nothing to do.

        // TODO: double check.
    }


    //
    //  Type of construct.
    //

    virtual int
    GetType() const
    { return CONSTRUCT_TYPE_AGGREGATE; }


    //
    //  If the construct is one among several possible ones then discard the
    //  others.
    //

    void Commit();

    
    //
    //  Has Commit already been called?
    //

    bool
    HasCommitAlreadyBeenCalled() const
    { return commitAlreadyCalled; }


    //
    //  Apply semantic actions to children.
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
    //  Threshold of successfully parsed subconstructs above which the construct
    //  is committed.
    //

    size_t commitThreshold;


    bool commitAlreadyCalled;


    //
    //  Parse an aggregate construct. Attempt to find input matching the 
    //  components of the aggregate starting at current position. Set parsed to
    //  true if successful.
    //

    virtual void ParseBody(Parser& currentParser);


    //
    //  Expand next component of the aggregate.
    //

    virtual void Expand();
    

    // Must not be used.

    Aggregate() 
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};


////////////////////////////////////////////////////////////////////////////////
//
//  AggregateTemplate. Template class to define Aggregate constructs.
//

template<class N>
class AggregateTemplate : public Aggregate
{
public:

    AggregateTemplate(Parser& primaryParserParam)
    :   Aggregate(primaryParserParam),
        name(N::GetName())
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    AggregateTemplate(const AggregateTemplate& rhs) 
    :   Aggregate(rhs)
    {
        name = rhs.name;
    }


    // Default assignment operator not ok.

    AggregateTemplate& 
    operator=(const AggregateTemplate& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            static_cast<Aggregate&>(*this) = rhs;

            name = rhs.name;

            return *this;
        }
    }
        

    virtual ~AggregateTemplate()
    {
        // Nothing to do.
    }

    virtual Construct*
    Clone() const
    { return new AggregateTemplate(*this); }


    virtual const std::string& 
    GetName() const
    { return name; }

    virtual Production& GetProduction();

    virtual void PreAction(Parser& currentParser);

    virtual void PostAction(Parser& currentParser);

protected:

    std::string name;

    // Must not be used.

    AggregateTemplate()
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }
};


////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_AGGREGATE. Macro to define Aggregate constructs.
//
//  Cannot be traced in by debugger. Switch to template approach if required.
//
//  MUST be kept in sync with template AggregateTemplate class.
//

//
//  MP_ClassName => name of class.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_AGGREGATE(MP_ClassName, MP_Name)                 \
                                                                            \
class MP_ClassName : public its::Aggregate                                  \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName(its::Parser& primaryParserParam)                           \
    :   its::Aggregate(primaryParserParam),                                 \
        name(MP_Name)                                                       \
    {}                                                                      \
                                                                            \
    MP_ClassName(const MP_ClassName& rhs)                                   \
    :   its::Aggregate(rhs)                                                 \
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
            static_cast<its::Aggregate&>(*this) = rhs;                      \
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

#endif // !defined(_PARSE_AGGREGATE_H_)
