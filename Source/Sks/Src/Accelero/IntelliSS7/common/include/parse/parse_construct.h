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
//  ID: $Id: parse_construct.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//
//  parse_construct.h: Construct class interface.
//
//


#if !defined(_PARSE_CONSTRUCT_H_)
#define _PARSE_CONSTRUCT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <parse.h>
#include <parse_production.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

class Parser;

//
//  Note: type ConstructList defined as std::list<Construct*> in file 
//  parse_production.h.
//



////////////////////////////////////////////////////////////////////////////////
//
//  General notion of language construct, characterized by a grammatical 
//  production and associated semantic actions (tree node).
//

class Construct
{
public:

    Construct(Parser& primaryParserParam) 
    :   primaryParser(&primaryParserParam),
        parent(NULL),
        optional(false),
        parsed(false),
        completed(false),
        committed(false),
        topLevel(false),
        currentChild(NULL),
        syntaxErrorLineNumber(0),
        syntaxErrorColumnNumber(0)
    {}

    //  Default constructor not ok (see protected section).


    //  Default copy constructor not ok.

    Construct(const Construct& rhs);


    //  Default assignment operator not ok.

    Construct& operator=(const Construct& rhs);


    //
    //  MUST be defined in ALL concrete heirs.
    //

    virtual Construct* Clone() const = 0;


    //
    //  Delete all the children if any.
    //  Do not delete parent.
    //  Do not delete current child.
    //

    virtual ~Construct();


    //
    //  Types of construct.
    //

    enum {
        CONSTRUCT_TYPE_KEYWORD      = 0,
        CONSTRUCT_TYPE_TERMINAL     = 1,
        CONSTRUCT_TYPE_AGGREGATE    = 2,
        CONSTRUCT_TYPE_CHOICE       = 3,
        CONSTRUCT_TYPE_REPETITION   = 4
    };



    ////////////////////////////////////////////////////////
    //
    //  Access.
    //

    
    //
    //  Type of the construct.
    //

    virtual int GetType() const = 0;


    //
    //  Type name of the construct.
    //

    virtual std::string GetTypeName() const;


    //
    //  Name of the construct in the grammar.
    //

    virtual const std::string& GetName() const = 0;


    //
    //  Right-hand side of the production for the construct.
    //

    virtual Production& GetProduction() = 0;


    //
    //  Current child (i.e. last added child usually through Expand).
    //

    Construct&
    GetCurrentChild() const
    {
        ITS_REQUIRE(HasCurrentChild());

        return *currentChild;
    }


    //
    //  Number of children.
    //

    size_t
    GetChildrenSize() const
    { return children.size(); }


    //
    //  Children.
    //

    const ConstructList&
    GetChildren() const
    { return children; }


    //
    //  Primary parser.
    //

    Parser&
    GetPrimaryParser() const
    {
        ITS_REQUIRE(HasPrimaryParser());

        return *primaryParser;
    }


    //
    //  Parent.
    //

    Construct&
    GetParent() const
    {
        ITS_REQUIRE(HasParent());

        return *parent;
    }



    ////////////////////////////////////////////////////////
    //
    //  Status report.
    //

    bool
    IsOptional() const
    { return optional; }


    //
    //  Has construct been successfully parsed? (True for optional not present.)
    //

    bool
    IsParsed() const
    { return parsed; }


    //
    //  Has the construct been completely recognized? (Like IsParsed, but in 
    //  addition the construct, if optional, must be present.)
    //

    bool
    IsCompleted() const
    { return completed; }


    //
    //  Have enough productions been recognized to interpret failure of parsing
    //  as a syntax error in this construct? (Otherwise the parsing process will
    //  backtrack, trying other possible interpretations of the part already
    //  read.)
    //

    bool
    IsCommitted() const
    { return committed; }


    //
    //  Is current child defined?
    //

    bool 
    HasCurrentChild() const
    { return currentChild != NULL; }


    //
    //  Is primary parser defined?
    //

    bool 
    HasPrimaryParser() const
    { return primaryParser != NULL; }


    //
    //  Is parent defined?
    //

    bool
    HasParent() const
    { return parent != NULL; }


    //
    //  Is the construct the top level construct?
    //

    bool
    IsTopLevel() const
    { return topLevel; }


    //
    //  Has syntax error information?  
    //

    bool
    HasSyntaxErrorInformation() const
    { return !syntaxErrorInformation.empty(); }


    //
    //  Last syntax error information.
    //

    const std::string& 
    GetLastSyntaxErrorInformation() const
    {
        ITS_REQUIRE(HasSyntaxErrorInformation());

        return syntaxErrorInformation;
    }


    //
    //  Last syntax error line number.
    //

    size_t
    GetLastSyntaxErrorLineNumber() const
    {
        ITS_REQUIRE(HasSyntaxErrorInformation());

        return syntaxErrorLineNumber;
    }


    //
    //  Last syntax error column number.
    //

    size_t
    GetLastSyntaxErrorColumnNumber() const
    {
        ITS_REQUIRE(HasSyntaxErrorInformation());

        return syntaxErrorColumnNumber;
    }



    ////////////////////////////////////////////////////////
    //
    //  Status setting.
    //

    void
    SetOptional() 
    { optional = true; }

    void
    SetParsed()
    { parsed = true; }

    void
    SetTopLevel()
    { topLevel = true; }


    ////////////////////////////////////////////////////////
    //
    //  Transformations.
    //

    //
    //  Parse a specimen of the construct, then apply semantic actions if
    //  parsing successful. 
    //

    virtual void Process(Parser& currentParser);


    //  
    //  Attempt to analyze incoming lexical tokens according to current 
    //  construct. Set parsed to true if successful and return to orginal
    //  position in input otherwise.
    //

    virtual void Parse(Parser& currentParser);


    //
    //  If this construct is one among several possible ones, discard the
    //  others. By default does nothing. To be redefined in heirs. To be used in
    //  concrete heirs within GetProduction.
    //

    virtual void 
    Commit()
    {
        // Nothing to do (to be redefined in heirs if necessary).
    }


    //
    //  Add a construct to the production. To be used in concrete heirs within
    //  GetProduction. 
    //

    virtual void AddConstruct(Construct* construct);


    //
    //  Add a keyword to the production. To be used in concrete heirs within 
    //  GetProduction.
    //

    virtual void AddKeyword(const std::string& name);


    //
    //  Add an optional keyword to the production. To be used in concrete heirs
    //  within GetProduction.
    //

    virtual void AddOptionalKeyword(const std::string& name);


    //  
    //  Apply semantic actions in order: PreAction, InAction and PostAction.
    //

    virtual void
    ApplySemanticActions(Parser& currentParser)
    {
        PreAction(currentParser);

        InAction(currentParser);

        PostAction(currentParser);
    }


    //
    //  Semantic action executed before construct is parsed. By default does
    //  nothing. To be redefined in heirs.
    //

    virtual void
    PreAction(Parser& currentParser)
    {
        // Nothing to do (to be redefined in heirs).
    }


    //  
    //  Semantic action executed after construct is parsed. By default does 
    //  nothing. To be redefined in heirs.
    //

    virtual void
    PostAction(Parser& currentParser)
    {
        // Nothing to do (to be redefined in heirs).
    }


    //
    //  Perform a certain semantic operation when construct is parsed. To be
    //  defined in heirs.
    //

    virtual void InAction(Parser& currentParser) = 0;


    //
    //  Set parent.
    //

    void
    SetParent(Construct* parentParam)
    {
        ITS_REQUIRE(parentParam != NULL);

        parent = parentParam;
    }


    //
    //  Get (parsed) value.
    //  

    virtual std::string GetValue() const = 0;


    ////////////////////////////////////////////////////////
    //
    //  Printing.
    //

    virtual void Print(std::ostream& os, size_t level = 0) const = 0;

    virtual void PrintValue(std::ostream& os) const = 0;



protected:

    //
    //  Perform any special parsing action for a particular type of construct.
    //  Call Parse on each child construct. Set committed to true if enough
    //  has been recognized to freeze the parse tree built so far. Set completed
    //  to true if the whole construct has been correctly recognized. To be 
    //  defined in heirs.
    //

    virtual void ParseBody(Parser& currentParser) = 0;


    //
    //  Expand the next child of current node after current child. This is most
    //  likely the version of Expand for types of construct where each
    //  subconstruct must be expanded in turn.
    //

    virtual void ExpandNext();


    //    
    //  Create next construct to be parsed. Used by Parse to build the 
    //  production that is expected at each node, according to production. To 
    //  be defined in heirs.
    //

    virtual void Expand() = 0;


    //
    //  Parse current child recursively to build the tree. An error is output
    //  the first time a Parse call fails in an uncomitted child of a committed
    //  parent (i.e. at the deepest point known to be meaningful).
    //

    virtual void ParseCurrentChild(Parser& currentParser);




    Parser* primaryParser; // Must not be deleted by destructor.

    Construct* parent; // Must not be deleted by destructor.

    ConstructList children;

    bool optional;

    bool parsed; 

    bool completed;

    bool committed;

    bool topLevel;

    Construct* currentChild; // Must not be deleted by destructor.


    std::string syntaxErrorInformation;
    size_t      syntaxErrorLineNumber;
    size_t      syntaxErrorColumnNumber;


    // Must not be used.

    Construct() 
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

};

////////////////////////////////////////////////////////////
//
//  Construct ostream operator<< declaration.
//

std::ostream& operator<< (std::ostream& os, const Construct& construct);



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_PARSE_CONSTRUCT_H_)
