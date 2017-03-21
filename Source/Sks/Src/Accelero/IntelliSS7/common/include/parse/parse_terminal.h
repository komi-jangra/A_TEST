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
//  ID: $Id: parse_terminal.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_terminal.h: Terminal class interface.   
//
//


#if !defined(_PARSE_TERMINAL_H_)
#define _PARSE_TERMINAL_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <parse.h>
#include <parse_construct.h>
#include <parse_token.h>
#include <parse_utilities.h>
#include <parse_tokenizer.h>
#include <parse_parser.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  Terminal. Template class to define Terminal constructs.
//

template<class T> 
class Terminal : public Construct
{
public:

    Terminal(Parser& primaryParserParam) 
    :   Construct(primaryParserParam),
        token()
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    Terminal(const Terminal<T>& rhs) : Construct(rhs)
    {
        token           = rhs.token;
        emptyProduction = rhs.emptyProduction;
    }


    // Default assignment operator not ok.

    Terminal<T>& 
    operator=(const Terminal<T>& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            static_cast<Construct&>(*this) = rhs;

            token           = rhs.token;
            emptyProduction = rhs.emptyProduction;

            return *this;
        }
    }


    //
    //  Reminder: Clone MUST be defined in ALL concrete heirs.
    //


    virtual ~Terminal()
    {
        // Nothing to do.
    }


    //
    //  Type of the construct.
    //

    virtual int
    GetType() const
    { return CONSTRUCT_TYPE_TERMINAL; }


    //
    //  Name of the construct should be defined in heirs.
    //


    //
    //  Meaningless for terminal construct (return an empty list).
    //

    virtual Production& 
    GetProduction()
    { return emptyProduction; }


    virtual void
    PreAction(Parser& currentParser)
    {
        // Nothing to do (not used for terminal).
    }

    virtual void
    InAction(Parser& currentParser)
    {
        // Nothing to do.
    }

    virtual void
    PostAction(Parser& currentParser)
    {
        Action(currentParser);
    }

    //
    //  Only meaningful semantic action for terminal construct. By default does
    //  nothing. To be redefined in heirs.
    //

    virtual void
    Action(Parser& currentParser)
    {
        // Nothing to do (to be redefined in heirs).
    }


    //
    //  Associated token.
    //

    virtual Token* 
    GetToken() const
    { return const_cast<Token*>(static_cast<const Token*>(&token)); }


    //
    //  Get (parsed) value.
    //  

    virtual std::string 
    GetValue() const
    {
        return token.GetStringValue();
    }


    //
    //  Printing.
    //

    virtual void 
    Print(std::ostream& os, size_t level = 0) const
    {
        std::string levelShift = ParseUtilStringFourSpaces(level);

        os << levelShift;

        os << GetName();
        os << " (";
        os << "Terminal";

        if (IsOptional())
        {
            os << " | optional";
        }

        if (IsTopLevel())
        {
            os << " | top level";
        }

        os << ")" << std::endl;

        os << levelShift;

        os << "<";

        std::string strTransformed = 
            ParseUtilStringTransformSpecificCharacters(
                token.GetStringValue());

        os << strTransformed;

        os << ">" << std::endl;
    }


    virtual void
    PrintValue(std::ostream& os) const
    {
        os << token.GetStringValue();
    }


protected:

    T token;

    //
    //  Parse a terminal construct.
    //

    virtual void 
    ParseBody(Parser& currentParser)
    {
        Tokenizer& tokenizer = currentParser.GetTokenizer();

        PrsResult consumeResult = tokenizer.ConsumeToken(token);

        if (consumeResult == PARSE_SUCCESS)
        {
            completed = true;
        }
        else
        {
            completed = false;
        }
    }


    //
    //  Nothing to expand for terminal construct.
    //

    virtual void
    Expand()
    {
        // Nothing to do.
    }


    //
    //  Empty production for Terminal.
    //

    Production emptyProduction;

    
    // Must not be used.

    Terminal() 
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};


////////////////////////////////////////////////////////////////////////////////
//
//  TerminalForMacro. Abstract base class to define Terminal constructs using 
//  macros (instead of specializing template class Terminal).
//
//  MUST be kept in sync with template class Terminal.
//

class TerminalForMacro : public Construct
{
public:

    TerminalForMacro(Parser& primaryParserParam) 
    :   Construct(primaryParserParam)
    {}

    // Default constructor not ok (see protected section).

    // Default copy constructor not ok.

    TerminalForMacro(const TerminalForMacro& rhs) : Construct(rhs)
    {
        emptyProduction = rhs.emptyProduction;
    }


    // Default assignment operator not ok.

    TerminalForMacro& 
    operator=(const TerminalForMacro& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            static_cast<Construct&>(*this) = rhs;

            emptyProduction = rhs.emptyProduction;

            return *this;
        }
    }


    //
    //  Reminder: Clone MUST be defined in ALL concrete heirs.
    //

    virtual ~TerminalForMacro()
    {
        // Nothing to do.
    }


    //
    //  Type of the construct.
    //

    virtual int
    GetType() const
    { return CONSTRUCT_TYPE_TERMINAL; }


    //
    //  Name of the construct should be defined in heirs.
    //


    //
    //  Meaningless for terminal construct (return an empty list).
    //

    virtual Production& 
    GetProduction()
    { return emptyProduction; }


    virtual void
    PreAction(Parser& currentParser)
    {
        // Nothing to do (not used for terminal).
    }

    virtual void
    InAction(Parser& currentParser)
    {
        // Nothing to do.
    }

    virtual void
    PostAction(Parser& currentParser)
    {
        Action(currentParser);
    }

    //
    //  Only meaningful semantic action for terminal construct. By default does
    //  nothing. To be redefined in heirs.
    //

    virtual void
    Action(Parser& currentParser)
    {
        // Nothing to do (to be redefined in heirs).
    }


    //
    //  Get (parsed) value.
    //  

    virtual std::string 
    GetValue() const
    {
        return GetToken()->GetStringValue();
    }


    //
    //  Printing.
    //

    virtual void 
    Print(std::ostream& os, size_t level = 0) const
    {
        os << GetName();
        os << " (";
        os << "Terminal";

        if (IsOptional())
        {
            os << " | optional";
        }

        if (IsTopLevel())
        {
            os << " | top level";
        }

        os << ")" << std::endl;
        os << "<";

        std::string strTransformed = 
            ParseUtilStringTransformSpecificCharacters(
                GetToken()->GetStringValue());

        os << strTransformed;

        os << ">" << std::endl;
    }


    virtual void
    PrintValue(std::ostream& os) const
    {
        os << GetToken()->GetStringValue();
    }



protected:

    //
    //  Associated token. MUST be redefined in heirs.
    //

    virtual Token* GetToken() const = 0;


    //
    //  Parse a terminal construct.
    //

    virtual void 
    ParseBody(Parser& currentParser)
    {
        Tokenizer& tokenizer = currentParser.GetTokenizer();

        PrsResult consumeResult = tokenizer.ConsumeToken((*GetToken()));

        if (consumeResult == PARSE_SUCCESS)
        {
            completed = true;
        }
        else
        {
            completed = false;
        }
    }


    //
    //  Nothing to expand for terminal construct.
    //

    virtual void
    Expand()
    {
        // Nothing to do.
    }


    Production emptyProduction;

    
    // Must not be used.

    TerminalForMacro() 
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};


////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_TERMINAL. Macro to define Terminal constructs (with 
//  action). 
//
//  Cannot be traced in by debugger. Switch to template approach if required.
//
//  MUST be kept in sync with template class Terminal.
//

//
//  MP_ClassName => name of class.
//  MP_TokenClassName => name of token class.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_TERMINAL(                                        \
                                MP_ClassName,                               \
                                MP_TokenClassName,                          \
                                MP_Name)                                    \
                                                                            \
class MP_ClassName : public its::TerminalForMacro                           \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName(its::Parser& primaryParserParam)                           \
    :   its::TerminalForMacro(primaryParserParam),                          \
        token(),                                                            \
        name(MP_Name)                                                       \
    {}                                                                      \
                                                                            \
    MP_ClassName(const MP_ClassName& rhs) : its::TerminalForMacro(rhs)      \
    {                                                                       \
        token   = rhs.token;                                                \
        name    = rhs.name;                                                 \
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
            static_cast<its::TerminalForMacro&>(*this) = rhs;               \
                                                                            \
            token   = rhs.token;                                            \
            name    = rhs.name;                                             \
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
    {  return name; }                                                       \
                                                                            \
    virtual void Action(its::Parser& currentParser);                        \
                                                                            \
protected:                                                                  \
                                                                            \
    virtual its::Token*                                                     \
    GetToken() const                                                        \
    {                                                                       \
        return const_cast<its::Token*>(                                     \
            static_cast<const its::Token*>(&token));                        \
    }                                                                       \
                                                                            \
    MP_TokenClassName token;                                                \
                                                                            \
    std::string name;                                                       \
                                                                            \
    MP_ClassName()                                                          \
    {                                                                       \
        bool must_not_be_used = false;                                      \
        ITS_ASSERT(must_not_be_used);                                       \
    }                                                                       \
                                                                            \
}


////////////////////////////////////////////////////////////////////////////////
//
//  PARSE_DEFINE_CLASS_TERMINAL_NO_ACTION. Macro to define Terminal constructs
//  (without action). 
//
//  Cannot be traced in by debugger. Switch to template approach if required.
//
//  MUST be kept in sync with template class Terminal.
//

//
//  MP_ClassName => name of class.
//  MP_TokenClassName => name of token class.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define PARSE_DEFINE_CLASS_TERMINAL_NO_ACTION(                              \
                                        MP_ClassName,                       \
                                        MP_TokenClassName,                  \
                                        MP_Name)                            \
                                                                            \
class MP_ClassName : public its::TerminalForMacro                           \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName(its::Parser& primaryParserParam)                           \
    :   its::TerminalForMacro(primaryParserParam),                          \
        token(),                                                            \
        name(MP_Name)                                                       \
    {}                                                                      \
                                                                            \
    MP_ClassName(const MP_ClassName& rhs) : its::TerminalForMacro(rhs)      \
    {                                                                       \
        token   = rhs.token;                                                \
        name    = rhs.name;                                                 \
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
            static_cast<its::TerminalForMacro&>(*this) = rhs;               \
                                                                            \
            token   = rhs.token;                                            \
            name    = rhs.name;                                             \
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
protected:                                                                  \
                                                                            \
    virtual its::Token*                                                     \
    GetToken() const                                                        \
    {                                                                       \
        return const_cast<its::Token*>(                                     \
            static_cast<const its::Token*>(&token));                        \
    }                                                                       \
                                                                            \
    MP_TokenClassName token;                                                \
                                                                            \
    std::string name;                                                       \
                                                                            \
    MP_ClassName()                                                          \
    {                                                                       \
        bool must_not_be_used = false;                                      \
        ITS_ASSERT(must_not_be_used);                                       \
    }                                                                       \
                                                                            \
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_TERMINAL_H_)
