///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
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
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:27  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:30  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:52  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.6  2001/08/16 20:15:03  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.5  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/09 19:41:55  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_constructs.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_constructs.h: MNT parse constructs.
//
//


#if !defined(_MNT_CONSTRUCTS_H_)
#define _MNT_CONSTRUCTS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mnt.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
//  Forward declarations.
//

class ExecuteContext;
class Evaluator;
class Interpreter;
class Mnt;

class Construct;
typedef std::vector<Construct*> ConstructList;


///////////////////////////////////////////////////////////////////////////////
//
// Construct.
//

class Construct
{
public:

    Construct() 
    :   _parent(NULL),
        _topLevel(false),
        _out(false),
        _valueString(""),
        _valueByte(0),
        _valueLong(0),
        _valueBool(false),
        _hasValueString(false),
        _hasValueByte(false),
        _hasValueLong(false),
        _hasValueBool(false),
        _hasValueStringArray(false),
        _hasValueByteArray(false),
        _hasValueLongArray(false),
        _hasValueBoolArray(false),
        _lineNumber(0)
    {
        _children.reserve(16);
    }

    // Default copy constructor not ok.
    Construct(const Construct& rhs);

    // Default assignment operator not ok.
    Construct& operator=(const Construct& rhs);

    // MUST be defined in ALL concrete heirs.
    virtual Construct* Clone() const = 0;

    // Destructor semantic:
    // - Delete all the children if any.
    // - Do not delete parent.
    virtual ~Construct();


    ///////////////////////////////////////////////////////
    //
    // Properties.
    //

    // Type of the construct.
    virtual int GetType() const = 0;

    // Name of the construct in the grammar.
    virtual const std::string& GetName() const = 0;

    ///////////////////////////////////
    //
    // Children related.
    //

    const ConstructList&
    GetChildren() const
    { return _children; }

    ConstructList&
    GetChildren()
    { return _children; }

    size_t
    GetChildrenSize() const
    { return _children.size(); }

    ///////////////////////////////////
    //
    // Parent related.
    //

    void
    SetParent(Construct* parent)
    {
        ITS_REQUIRE(parent != NULL);
        _parent = parent;
    }

    bool
    HasParent() const
    { 
        return _parent != NULL;
    }

    const Construct&
    GetParent() const
    {
        ITS_REQUIRE(HasParent());
        return *_parent;
    }

    Construct&
    GetParent()
    {
        ITS_REQUIRE(HasParent());
        return *_parent;
    }

    ///////////////////////////////////
    //
    // TopLevel related.
    //

    void
    SetTopLevel()
    { 
        _topLevel = true; 
    }

    void
    UnsetTopLevel()
    { 
        _topLevel = false; 
    }

    bool
    IsTopLevel() const
    { 
        return _topLevel; 
    }

    ///////////////////////////////////
    //
    // Out related.
    //

    void
    SetOut()
    { 
        _out = true; 
    }

    void
    UnsetOut()
    { 
        _out = false; 
    }

    bool
    IsOut() const
    { 
        return _out; 
    }

    ///////////////////////////////////
    //
    // Value related.
    //

    void
    SetValueString(const std::string& value)
    {
        _valueString = value;
        _hasValueString = true;
    }

    bool
    HasValueString() const
    { 
        return _hasValueString;
    }

    const std::string&
    GetValueString() const
    {
        return _valueString;
    }

    void
    SetValueByte(unsigned char value)
    {
        _valueByte = value;
        _hasValueByte = true;
    }

    bool
    HasValueByte() const
    {
        return _hasValueByte;
    }

    unsigned char
    GetValueByte() const
    {
        return _valueByte;
    }

    void
    SetValueLong(long value)
    {
        _valueLong = value;
        _hasValueLong = true;
    }

    bool
    HasValueLong() const
    {
        return _hasValueLong;
    }

    long
    GetValueLong() const
    {
        return _valueLong;
    }

    void
    SetValueBool(bool value)
    {
        _valueBool = value;
        _hasValueBool = true;
    }

    bool
    HasValueBool() const
    {
        return _hasValueBool;
    }

    bool
    GetValueBool() const
    {
        return _valueBool;
    }

    ///////////////////////////////////
    //
    // Value related (arrays).
    //

    void
    SetValueStringArray(const std::vector<std::string>& value)
    {
        _valueStringArray = value;
        _hasValueStringArray = true;
    }

    bool
    HasValueStringArray() const
    { 
        return _hasValueStringArray;
    }

    const std::vector<std::string>&
    GetValueStringArray() const
    {
        return _valueStringArray;
    }

    void
    SetValueByteArray(const std::vector<unsigned char>& value)
    {
        _valueByteArray = value;
        _hasValueByteArray = true;
    }

    bool
    HasValueByteArray() const
    {
        return _hasValueByteArray;
    }

    const std::vector<unsigned char>& 
    GetValueByteArray() const
    {
        return _valueByteArray;
    }

    void
    SetValueLongArray(const std::vector<long>& value)
    {
        _valueLongArray = value;
        _hasValueLongArray = true;
    }

    bool
    HasValueLongArray() const
    {
        return _hasValueLongArray;
    }

    const std::vector<long>&
    GetValueLongArray() const
    {
        return _valueLongArray;
    }

    void
    SetValueBoolArray(const std::vector<bool>& value)
    {
        _valueBoolArray = value;
        _hasValueBoolArray = true;
    }

    bool
    HasValueBoolArray() const
    {
        return _hasValueBoolArray;
    }

    const std::vector<bool>&
    GetValueBoolArray() const
    {
        return _valueBoolArray;
    }

    ///////////////////////////////////
    //
    // Line number related.
    //

    void
    SetLineNumber(size_t lineNumber)
    {
        _lineNumber = lineNumber;
    }

    size_t
    GetLineNumber() const
    {
        return _lineNumber;
    }

    ///////////////////////////////////////////////////////
    //
    // Semantic.
    //

    // Semantic action associated with construct. By default does nothing. To
    // be redefined in heirs.
    virtual void
    Execute(ExecuteContext& executeContext)
    {
        // Nothing to do (to be redefined in heirs).
    }


    ///////////////////////////////////////////////////////
    //
    // Printing.
    //

    virtual void Print(std::ostream& os, size_t level = 0) const;

    virtual void PrintValue(std::ostream& os) const;

protected:

    Construct*                  _parent; // Must not be deleted by destructor.
    ConstructList               _children;
    bool                        _topLevel;
    bool                        _out;
    std::string                 _valueString;
    unsigned char               _valueByte;
    long                        _valueLong;
    bool                        _valueBool;
    std::vector<std::string>    _valueStringArray;
    std::vector<unsigned char>  _valueByteArray;
    std::vector<long>           _valueLongArray;
    std::vector<bool>           _valueBoolArray;
    bool                        _hasValueString;
    bool                        _hasValueByte;
    bool                        _hasValueLong;
    bool                        _hasValueBool;
    bool                        _hasValueStringArray;
    bool                        _hasValueByteArray;
    bool                        _hasValueLongArray;
    bool                        _hasValueBoolArray;
    size_t                      _lineNumber;
};

///////////////////////////////////////////////////////////
//
// Construct ostream operator<< declaration.
//

std::ostream& operator<< (std::ostream& os, const Construct& construct);


///////////////////////////////////////////////////////////////////////////////
//
// MNT_DEFINE_CONSTRUCT_CLASS. Macro to define construct classes.
//
// Cannot be traced in by debuggers (macro).
//
// Using templates instead results in too much code bloat.
//
//

//
//  MP_ClassName => name of class.
//  MP_ConstructType => type of construct.
//  MP_Name => string returned by GetName member function.
//
//  MP = Macro Parameter.
//

#define MNT_DEFINE_CONSTRUCT_CLASS(MP_ClassName, MP_ConstructType, MP_Name) \
                                                                            \
class MP_ClassName : public mnt::Construct                                  \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName()                                                          \
    :   _name(MP_Name)                                                      \
    {}                                                                      \
                                                                            \
    MP_ClassName(const MP_ClassName& rhs)                                   \
    :   mnt::Construct(rhs)                                                 \
    {                                                                       \
        _name = rhs._name;                                                  \
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
            static_cast<mnt::Construct&>(*this) = rhs;                      \
            _name = rhs._name;                                              \
            return *this;                                                   \
        }                                                                   \
    }                                                                       \
                                                                            \
    virtual ~MP_ClassName()                                                 \
    {}                                                                      \
                                                                            \
    virtual mnt::Construct*                                                 \
    Clone() const                                                           \
    { return new MP_ClassName(*this); }                                     \
                                                                            \
    virtual const std::string&                                              \
    GetName() const                                                         \
    { return _name; }                                                       \
                                                                            \
    virtual int                                                             \
    GetType() const                                                         \
    { return MP_ConstructType; }                                            \
                                                                            \
                                                                            \
    virtual void Execute(ExecuteContext& executeContext);                   \
                                                                            \
protected:                                                                  \
                                                                            \
    std::string _name;                                                      \
                                                                            \
}


///////////////////////////////////////////////////////////////////////////////
//
// All grammar construct types.
//

enum
{
    CTR_TYPE_MNT_SCRIPT                         = 1,
    CTR_TYPE_INSTRUCTION_LIST                   = 2,
    CTR_TYPE_INSTRUCTION                        = 3,
    CTR_TYPE_ARGUMENT_LIST                      = 4,
    CTR_TYPE_ARGUMENT                           = 5,
    CTR_TYPE_COMMAND_INSTRUCTION                = 6,
    CTR_TYPE_ASSIGNMENT_INSTRUCTION             = 7,
    CTR_TYPE_ARRAY_ELT_ASSIGNMENT_INSTRUCTION   = 8,
    CTR_TYPE_CONDITIONAL_INSTRUCTION            = 9,
    CTR_TYPE_THEN_PART_LIST                     = 10,
    CTR_TYPE_THEN_PART                          = 11,
    CTR_TYPE_ELSE_PART                          = 12,
    CTR_TYPE_LOOP_INSTRUCTION                   = 13,
    CTR_TYPE_PRIMARY_EXPR                       = 14,
    CTR_TYPE_POSTFIX_EXPR                       = 15,
    CTR_TYPE_UNARY_EXPR                         = 16,
    CTR_TYPE_UNARY_OPERATOR                     = 17,
    CTR_TYPE_MULTIPLICATIVE_EXPR                = 18,
    CTR_TYPE_ADDITIVE_EXPR                      = 19,
    CTR_TYPE_RELATIONAL_EXPR                    = 20,
    CTR_TYPE_EQUALITY_EXPR                      = 21,
    CTR_TYPE_LOGICAL_AND_EXPR                   = 22,
    CTR_TYPE_LOGICAL_OR_EXPR                    = 23,
    CTR_TYPE_EXPR                               = 24,
    CTR_TYPE_IDENTIFIER                         = 25,
    CTR_TYPE_STRING                             = 26,
    CTR_TYPE_BYTE                               = 27,
    CTR_TYPE_INTEGER                            = 28,
    CTR_TYPE_BOOLEAN                            = 29,
    CTR_TYPE_STRING_ARRAY                       = 30,
    CTR_TYPE_BYTE_ARRAY                         = 31,
    CTR_TYPE_INTEGER_ARRAY                      = 32,
    CTR_TYPE_BOOLEAN_ARRAY                      = 33
};




///////////////////////////////////////////////////////////////////////////////
//
// All grammar construct related classes.
//

MNT_DEFINE_CONSTRUCT_CLASS(
                        MntScriptCtr,
                        CTR_TYPE_MNT_SCRIPT,
                        "MntScript");

MNT_DEFINE_CONSTRUCT_CLASS(
                        InstructionListCtr,
                        CTR_TYPE_INSTRUCTION_LIST,
                        "InstructionList");

MNT_DEFINE_CONSTRUCT_CLASS(
                        InstructionCtr,
                        CTR_TYPE_INSTRUCTION,
                        "Instruction");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ArgumentListCtr,
                        CTR_TYPE_ARGUMENT_LIST,
                        "ArgumentList");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ArgumentCtr,
                        CTR_TYPE_ARGUMENT,
                        "Argument");

MNT_DEFINE_CONSTRUCT_CLASS(
                        CommandInstructionCtr,
                        CTR_TYPE_COMMAND_INSTRUCTION,
                        "CommandInstruction");

MNT_DEFINE_CONSTRUCT_CLASS(
                        AssignmentInstructionCtr,
                        CTR_TYPE_ASSIGNMENT_INSTRUCTION,
                        "AssignmentInstruction");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ArrayEltAssignmentInstructionCtr,
                        CTR_TYPE_ARRAY_ELT_ASSIGNMENT_INSTRUCTION,
                        "ArrayEltAssignmentInstruction");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ConditionalInstructionCtr,
                        CTR_TYPE_CONDITIONAL_INSTRUCTION,
                        "ConditionalInstruction");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ThenPartListCtr,
                        CTR_TYPE_THEN_PART_LIST,
                        "ThenPartList");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ThenPartCtr,
                        CTR_TYPE_THEN_PART,
                        "ThenPart");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ElsePartCtr,
                        CTR_TYPE_ELSE_PART,
                        "ElsePart");

MNT_DEFINE_CONSTRUCT_CLASS(
                        LoopInstructionCtr,
                        CTR_TYPE_LOOP_INSTRUCTION,
                        "LoopInstruction");

MNT_DEFINE_CONSTRUCT_CLASS(
                        PrimaryExprCtr,
                        CTR_TYPE_PRIMARY_EXPR,
                        "PrimaryExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        PostfixExprCtr,
                        CTR_TYPE_POSTFIX_EXPR,
                        "PostfixExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        UnaryExprCtr,
                        CTR_TYPE_UNARY_EXPR,
                        "UnaryExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        UnaryOperatorCtr,
                        CTR_TYPE_UNARY_OPERATOR,
                        "UnaryOperator");

MNT_DEFINE_CONSTRUCT_CLASS(
                        MultiplicativeExprCtr,
                        CTR_TYPE_MULTIPLICATIVE_EXPR,
                        "MultiplicativeExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        AdditiveExprCtr,
                        CTR_TYPE_ADDITIVE_EXPR,
                        "AdditiveExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        RelationalExprCtr,
                        CTR_TYPE_RELATIONAL_EXPR,
                        "RelationalExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        EqualityExprCtr,
                        CTR_TYPE_EQUALITY_EXPR,
                        "EqualityExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        LogicalAndExprCtr,
                        CTR_TYPE_LOGICAL_AND_EXPR,
                        "LogicalAndExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        LogicalOrExprCtr,
                        CTR_TYPE_LOGICAL_OR_EXPR,
                        "LogicalOrExpr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ExprCtr,
                        CTR_TYPE_EXPR,
                        "Expr");

MNT_DEFINE_CONSTRUCT_CLASS(
                        IdentifierCtr,
                        CTR_TYPE_IDENTIFIER,
                        "Identifier");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ByteCtr,
                        CTR_TYPE_BYTE,
                        "Byte");

MNT_DEFINE_CONSTRUCT_CLASS(
                        IntegerCtr,
                        CTR_TYPE_INTEGER,
                        "Integer");

MNT_DEFINE_CONSTRUCT_CLASS(
                        BooleanCtr,
                        CTR_TYPE_BOOLEAN,
                        "Boolean");

MNT_DEFINE_CONSTRUCT_CLASS(
                        StringCtr,
                        CTR_TYPE_STRING,
                        "String");

MNT_DEFINE_CONSTRUCT_CLASS(
                        ByteArrayCtr,
                        CTR_TYPE_BYTE_ARRAY,
                        "ByteArray");

MNT_DEFINE_CONSTRUCT_CLASS(
                        IntegerArrayCtr,
                        CTR_TYPE_INTEGER_ARRAY,
                        "IntegerArray");

MNT_DEFINE_CONSTRUCT_CLASS(
                        BooleanArrayCtr,
                        CTR_TYPE_BOOLEAN_ARRAY,
                        "BooleanArray");

MNT_DEFINE_CONSTRUCT_CLASS(
                        StringArrayCtr,
                        CTR_TYPE_STRING_ARRAY,
                        "StringArray");



///////////////////////////////////////////////////////////////////////////////
//
// ExecuteContext.
//

class ExecuteContext
{
public:

    ExecuteContext()
    :   _evaluator(NULL),
        _interpreter(NULL)
    {}

    // Default copy constructor not ok (see protected section).

    // Default assignment operator not ok (see protected section).

    virtual ~ExecuteContext()
    {
        // Nothing to do.
    }

    void
    SetEvaluator(Evaluator* evaluator)
    {
        ITS_REQUIRE(evaluator != NULL);
        _evaluator = evaluator;
    }

    bool
    HasEvaluator() const
    {
        return _evaluator != NULL;
    }

    const Evaluator& 
    GetEvaluator() const
    { 
        ITS_REQUIRE(HasEvaluator());
        return *_evaluator;
    }

    Evaluator&
    GetEvaluator()
    {
        ITS_REQUIRE(HasEvaluator());
        return *_evaluator;
    }

    void
    SetInterpreter(Interpreter* interpreter)
    {
        ITS_REQUIRE(interpreter != NULL);
        _interpreter = interpreter;
    }

    bool
    HasInterpreter() const
    {
        return _interpreter != NULL;
    }

    const Interpreter& 
    GetInterpreter() const
    { 
        ITS_REQUIRE(HasInterpreter());
        return *_interpreter;
    }

    Interpreter&
    GetInterpreter()
    {
        ITS_REQUIRE(HasInterpreter());
        return *_interpreter;
    }

    void
    SetMnt(Mnt* mnt)
    {
        ITS_REQUIRE(mnt != NULL);
        _mnt = mnt;
    }

    bool
    HasMnt() const
    {
        return _mnt != NULL;
    }

    const Mnt& 
    GetMnt() const
    { 
        ITS_REQUIRE(HasMnt());
        return *_mnt;
    }

    Mnt&
    GetMnt()
    {
        ITS_REQUIRE(HasMnt());
        return *_mnt;
    }

protected:

    Evaluator*      _evaluator;
    Interpreter*    _interpreter;
    Mnt*            _mnt;

    ExecuteContext(const ExecuteContext& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

    ExecuteContext& 
    operator= (const ExecuteContext& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
        return *this;
    }

};
   



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_CONSTRUCTS_H_)

