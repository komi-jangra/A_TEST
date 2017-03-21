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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
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
// LOG: Revision 5.4  2001/08/21 00:23:53  mmiers
// LOG: Warning removal
// LOG:
// LOG: Revision 5.3  2001/08/17 20:31:23  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 5.2  2001/08/17 19:03:02  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.8  2001/08/16 20:15:03  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.7  2001/08/15 23:00:42  hdivoux
// LOG: Correction for string default value in array of strings.
// LOG:
// LOG: Revision 1.6  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.5  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/09 20:30:47  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 1.3  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_constructs.cpp,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_constructs.h: MNT parse constructs implementation.
//
//

#include <mnt_constructs.h>
#include <mnt_interpreter.h>
#include <mnt_evaluator.h>
#include <mnt_exception.h>
#include <mnt_helpers.h>
#include <mnt_errors.h>

#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_STD_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
// Construct.
//

Construct::Construct(const Construct& rhs)
{
    _parent                 = rhs._parent;
    _topLevel               = rhs._topLevel;
    _out                    = rhs._out;
    _valueString            = rhs._valueString;
    _valueByte              = rhs._valueByte;
    _valueLong              = rhs._valueLong;
    _valueBool              = rhs._valueBool;
    _valueStringArray       = rhs._valueStringArray;
    _valueByteArray         = rhs._valueByteArray;
    _valueLongArray         = rhs._valueLongArray;
    _valueBoolArray         = rhs._valueBoolArray;
    _hasValueString         = rhs._hasValueString;
    _hasValueByte           = rhs._hasValueByte;
    _hasValueLong           = rhs._hasValueLong;
    _hasValueBool           = rhs._hasValueBool;
    _hasValueStringArray    = rhs._hasValueStringArray;
    _hasValueByteArray      = rhs._hasValueByteArray;
    _hasValueLongArray      = rhs._hasValueLongArray;
    _hasValueBoolArray      = rhs._hasValueBoolArray;

    _lineNumber         = rhs._lineNumber;

    for (ConstructList::const_iterator iterRhs = rhs._children.begin();
         iterRhs != rhs._children.end();
         iterRhs++)
    {
        _children.push_back((*iterRhs)->Clone());
    }
}

Construct&
Construct::operator=(const Construct& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        _parent                 = rhs._parent;
        _topLevel               = rhs._topLevel;
        _out                    = rhs._out;
        _valueString            = rhs._valueString;
        _valueByte              = rhs._valueByte;
        _valueLong              = rhs._valueLong;
        _valueBool              = rhs._valueBool;
        _valueStringArray       = rhs._valueStringArray;
        _valueByteArray         = rhs._valueByteArray;
        _valueLongArray         = rhs._valueLongArray;
        _valueBoolArray         = rhs._valueBoolArray;
        _hasValueString         = rhs._hasValueString;
        _hasValueByte           = rhs._hasValueByte;
        _hasValueLong           = rhs._hasValueLong;
        _hasValueBool           = rhs._hasValueBool;
        _hasValueStringArray    = rhs._hasValueStringArray;
        _hasValueByteArray      = rhs._hasValueByteArray;
        _hasValueLongArray      = rhs._hasValueLongArray;
        _hasValueBoolArray      = rhs._hasValueBoolArray;
        _lineNumber             = rhs._lineNumber;        

        for (ConstructList::const_iterator iter = _children.begin();
            iter != _children.end();
            iter++)
        {
            delete (*iter);
        }

        _children.erase(_children.begin(), _children.end());

        for (ConstructList::const_iterator iterRhs = rhs._children.begin();
             iterRhs != rhs._children.end();
             iterRhs++)
        {
            _children.push_back((*iterRhs)->Clone());
        }
        
        return *this;
    }
}

Construct::~Construct()
{
    for (ConstructList::const_iterator iter = _children.begin();
         iter != _children.end();
         iter++)
    {
        delete (*iter);
    }
}

void
Construct::Print(ostream& os, size_t level) const
{
    string levelShift;
    levelShift.reserve(level * 4);
    levelShift.append(level * 4, ' ');

    os << levelShift;

    os << GetName() << endl;

    os << levelShift;

    os << "<" << endl;

    if (_hasValueString)
    {
        os << levelShift << "    ";
        os << StringValueToString(_valueString) << endl;
    }

    if (_hasValueByte)
    {
        os << levelShift << "    ";
        os << ByteValueToString(_valueByte) << endl;
    }

    if (_hasValueLong)
    {
        os << levelShift << "    "; 
        os << IntegerValueToString(_valueLong) << endl;
    }

    if (_hasValueBool)
    {
        os << levelShift << "    ";
        os << BooleanValueToString(_valueBool) << endl;
    }

    if (_hasValueStringArray)
    {
        os << levelShift << "    ";
        os << StringArrayValueToString(_valueStringArray) << endl;
    }

    if (_hasValueByteArray)
    {
        os << levelShift << "    ";
        os << ByteArrayValueToString(_valueByteArray) << endl;
    }

    if (_hasValueLongArray)
    {
        os << levelShift << "    "; 
        os << IntegerArrayValueToString(_valueLongArray) << endl;
    }

    if (_hasValueBoolArray)
    {
        os << levelShift << "    ";
        os << BooleanArrayValueToString(_valueBoolArray) << endl;
    }

    if ((_hasValueString        ||
         _hasValueByte          ||
         _hasValueLong          ||
         _hasValueBool          ||
         _hasValueStringArray   ||
         _hasValueByteArray     ||
         _hasValueLongArray     ||
         _hasValueBoolArray) &&
        _children.size() > 0)
    {
        os << endl;
    }

    bool first = true;

    for (ConstructList::const_iterator iter = _children.begin();
         iter != _children.end();
         iter++)
    {
        if (!first)
        {
            os << endl;
        }
        else
        { 
            first = false;
        }

        Construct* child = *iter;

        child->Print(os, level + 1);
    }

    os << levelShift;

    os << ">" << endl;
}

void 
Construct::PrintValue(std::ostream& os) const
{
    if (_hasValueString)
    {
        os << StringValueToString(_valueString);
    }

    if (_hasValueByte)
    {
        os << ByteValueToString(_valueByte);
    }

    if (_hasValueLong)
    {
        os << IntegerValueToString(_valueLong);
    }

    if (_hasValueBool)
    {
        os << BooleanValueToString(_valueBool);
    }

    if (_hasValueStringArray)
    {
        os << StringArrayValueToString(_valueStringArray);
    }

    if (_hasValueByteArray)
    {
        os << ByteArrayValueToString(_valueByteArray);
    }

    if (_hasValueLongArray)
    {
        os << IntegerArrayValueToString(_valueLongArray);
    }

    if (_hasValueBoolArray)
    {
        os << BooleanArrayValueToString(_valueBoolArray);
    }
}


///////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

static void ExecuteCommand(
                    ExecuteContext& executeContext,
                    IdentifierCtr& identifierCtr, 
                    ArgumentListCtr& argumentListCtr);


///////////////////////////////////////////////////////////////////////////////
//
// All grammar construct related class implementations.
//

void
MntScriptCtr::Execute(ExecuteContext& executeContext)
{
    for (size_t i = 0; i < _children.size(); i++)
    {
        Construct* construct = _children[i];
        construct->Execute(executeContext);
    }
}

void
InstructionListCtr::Execute(ExecuteContext& executeContext)
{
    for (size_t i = 0; i < _children.size(); i++)
    {
        Construct* construct = _children[i];
        construct->Execute(executeContext);
    }
}

void
ArgumentListCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
ArgumentCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
CommandInstructionCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 1 || _children.size() == 2);

    IdentifierCtr* identifierCtr = 
        static_cast<IdentifierCtr*>(_children[0]);

    // From grammar.
    ITS_ASSERT(identifierCtr->GetType() == CTR_TYPE_IDENTIFIER);

    if (_children.size() == 1)
    {
        ArgumentListCtr argumentListCtr;

        ExecuteCommand(
            executeContext,
            *identifierCtr, 
            argumentListCtr);
    }
    else if (_children.size() == 2)
    {
        ArgumentListCtr* argumentListCtr = 
            static_cast<ArgumentListCtr*>(_children[1]);

        // From grammar.
        ITS_ASSERT(argumentListCtr->GetType() == CTR_TYPE_ARGUMENT_LIST);

        ExecuteCommand(
            executeContext,
            *identifierCtr, 
            *argumentListCtr);
    }

    executeContext.GetEvaluator().Clean();
    ITS_ASSERT(executeContext.GetEvaluator().GetEvalStackSize() == 0);
}

void
AssignmentInstructionCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);

    IdentifierCtr* identifierCtr = 
        static_cast<IdentifierCtr*>(_children[0]);

    // From grammar.
    ITS_ASSERT(identifierCtr->GetType() == CTR_TYPE_IDENTIFIER);

    Evaluator& evaluator = executeContext.GetEvaluator();
    evaluator.Clean();

    _children[1]->Execute(executeContext);

    ITS_ASSERT(evaluator.GetEvalStackSize() >= 1);

    EvalObject* value = evaluator.Top();
    evaluator.Pop();

    string variableName = identifierCtr->GetValueString();

    Interpreter& interpreter = executeContext.GetInterpreter();

    if (interpreter.HasCommand(variableName))
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid name %s for variable (same as a command name)",
                variableName.c_str()),
            identifierCtr->GetLineNumber(),
            0,
            MNT_E_INVALID_VAR_NAME_ERROR);
    }

    if (!interpreter.HasVariable(variableName))
    {
        interpreter.InsertVariable(variableName, value);
    }
    else
    {
        EvalObject* 
            previousValue = 
                &interpreter.
                    RetrieveVariable(variableName);

        interpreter.RemoveVariable(variableName);

        delete previousValue;

        interpreter.InsertVariable(variableName, value);
    }

    executeContext.GetEvaluator().Clean();
    ITS_ASSERT(executeContext.GetEvaluator().GetEvalStackSize() == 0);

}

void
ArrayEltAssignmentInstructionCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 3);

    IdentifierCtr* identifierCtr = 
        static_cast<IdentifierCtr*>(_children[0]);

    // From grammar.
    ITS_ASSERT(identifierCtr->GetType() == CTR_TYPE_IDENTIFIER);

    Interpreter& interpreter = executeContext.GetInterpreter();

    string variableName = identifierCtr->GetValueString();

    Evaluator& evaluator = executeContext.GetEvaluator();
    evaluator.Clean();

    _children[1]->Execute(executeContext);

    ITS_ASSERT(evaluator.GetEvalStackSize() >= 1);

    EvalObject* evalIndex = evaluator.Top();

    evaluator.Pop();

    size_t index = 0;

    if (evalIndex->GetType() != EvalObject::TYPE_EVAL_BYTE &&
        evalIndex->GetType() != EvalObject::TYPE_EVAL_INTEGER)
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid type %s for index of array variable %s",
                evalIndex->GetTypeName().c_str(),
                variableName.c_str()),
            identifierCtr->GetLineNumber(),
            0,
            MNT_E_INVALID_ARRAY_INDEX_TYPE_ERROR);
    }
    else if (evalIndex->GetType() == EvalObject::TYPE_EVAL_BYTE)
    {
        index = static_cast<EvalByte*>(evalIndex)->GetValue();
    }
    else if (evalIndex->GetType() == EvalObject::TYPE_EVAL_INTEGER)
    {
        index = static_cast<EvalInteger*>(evalIndex)->GetValue();
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    delete evalIndex;

    if (index < 0)
    {
        MNT_THROW_ERROR_VARARGS(
            ("negative value %d for index of array variable %s",
                index,
                variableName.c_str()),
            identifierCtr->GetLineNumber(),
            0,
            MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR);
    }

    evaluator.Clean();

    _children[2]->Execute(executeContext);

    ITS_ASSERT(evaluator.GetEvalStackSize() >= 1);

    EvalObject* value = evaluator.Top();
    evaluator.Pop();

    if (value->GetType() != EvalObject::TYPE_EVAL_BYTE &&
        value->GetType() != EvalObject::TYPE_EVAL_INTEGER &&
        value->GetType() != EvalObject::TYPE_EVAL_BOOLEAN &&
        value->GetType() != EvalObject::TYPE_EVAL_STRING)
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid value of type %s for assignment to element #%d of array "
                "variable %s",
                value->GetTypeName().c_str(),
                index,
                variableName.c_str()),
            identifierCtr->GetLineNumber(),
            0,
            MNT_E_INVALID_VAR_TYPE_ERROR);
    }

    if (interpreter.HasCommand(variableName))
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid name %s for array variable (same as a command name)",
                variableName.c_str()),
            identifierCtr->GetLineNumber(),
            0,
            MNT_E_INVALID_ARRAY_VAR_NAME_ERROR);
    }

    if (!interpreter.HasVariable(variableName))
    {
        switch (value->GetType())
        {
        case EvalObject::TYPE_EVAL_BYTE:
            {
                EvalByteArray* variable = new EvalByteArray();

                variable->GetValue().reserve(index + 1);

                for (size_t i = 0; i <= index; i++)
                {
                    variable->GetValue().push_back(0);
                }

                variable->GetValue()[index] = 
                    static_cast<EvalByte*>(value)->GetValue();

                interpreter.InsertVariable(variableName, variable);
            }
            break;

        case EvalObject::TYPE_EVAL_INTEGER:
            {
                EvalIntegerArray* variable = new EvalIntegerArray();

                variable->GetValue().reserve(index + 1);

                for (size_t i = 0; i <= index; i++)
                {
                    variable->GetValue().push_back(0);
                }

                variable->GetValue()[index] = 
                    static_cast<EvalInteger*>(value)->GetValue();

                interpreter.InsertVariable(variableName, variable);
            }
            break;

        case EvalObject::TYPE_EVAL_BOOLEAN:
            {
                EvalBooleanArray* variable = new EvalBooleanArray();

                variable->GetValue().reserve(index + 1);

                for (size_t i = 0; i <= index; i++)
                {
                    variable->GetValue().push_back(false);
                }

                variable->GetValue()[index] = 
                    static_cast<EvalBoolean*>(value)->GetValue();

                interpreter.InsertVariable(variableName, variable);
            }
            break;

        case EvalObject::TYPE_EVAL_STRING:
            {
                EvalStringArray* variable = new EvalStringArray();

                variable->GetValue().reserve(index + 1);

                for (size_t i = 0; i <= index; i++)
                {
                    variable->GetValue().push_back("");
                }

                variable->GetValue()[index] = 
                    static_cast<EvalString*>(value)->GetValue();

                interpreter.InsertVariable(variableName, variable);
            }
            break;

        default:
            {
                bool must_not_be_reached = false;
                ITS_ASSERT(must_not_be_reached);
            }
        }
    }
    else
    {
        EvalObject*
            variable =
                &interpreter.
                    RetrieveVariable(variableName);

        switch (variable->GetType())
        {
        case EvalObject::TYPE_EVAL_BYTE_ARRAY:
            {
                if (value->GetType() != EvalObject::TYPE_EVAL_BYTE)
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("invalid value of type %s for assignment to element "
                            "#%d of array variable %s of type %s",
                            value->GetTypeName().c_str(),
                            index,
                            variableName.c_str(),
                            variable->GetTypeName().c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_VAR_TYPE_ERROR);
                }

                EvalByteArray*
                    evalByteArray =
                        static_cast<EvalByteArray*>(
                            variable);

                size_t currArraySize = 
                    evalByteArray->GetValue().size();

                if (index >= currArraySize)
                {
                    evalByteArray->GetValue().reserve(index + 1);

                    for (
                        size_t i = 0; 
                        i < index - currArraySize + 1;
                        i++)
                    {
                        evalByteArray->GetValue().push_back(0);
                    }
                }

                evalByteArray->GetValue()[index] = 
                    static_cast<EvalByte*>(value)->GetValue();
            }
            break;

        case EvalObject::TYPE_EVAL_INTEGER_ARRAY:
             {
                if (value->GetType() != EvalObject::TYPE_EVAL_INTEGER)
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("invalid value of type %s for assignment to element "
                            "#%d of array variable %s of type %s",
                            value->GetTypeName().c_str(),
                            index,
                            variableName.c_str(),
                            variable->GetTypeName().c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_VAR_TYPE_ERROR);
                }

                EvalIntegerArray*
                    evalIntegerArray =
                        static_cast<EvalIntegerArray*>(
                            variable);

                size_t currArraySize = 
                    evalIntegerArray->GetValue().size();

                if (index >= currArraySize)
                {
                    evalIntegerArray->GetValue().reserve(index + 1);

                    for (
                        size_t i = 0; 
                        i < index - currArraySize + 1;
                        i++)
                    {
                        evalIntegerArray->GetValue().push_back(0);
                    }
                }

                evalIntegerArray->GetValue()[index] = 
                    static_cast<EvalInteger*>(value)->GetValue();
            }
            break;

        case EvalObject::TYPE_EVAL_BOOLEAN_ARRAY:
            {
                if (value->GetType() != EvalObject::TYPE_EVAL_BOOLEAN)
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("invalid value of type %s for assignment to element "
                            "#%d of array variable %s of type %s",
                            value->GetTypeName().c_str(),
                            index,
                            variableName.c_str(),
                            variable->GetTypeName().c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_VAR_TYPE_ERROR);
                }

                EvalBooleanArray*
                    evalBooleanArray =
                        static_cast<EvalBooleanArray*>(
                            variable);

                size_t currArraySize = 
                    evalBooleanArray->GetValue().size();

                if (index >= currArraySize)
                {
                    evalBooleanArray->GetValue().reserve(index + 1);

                    for (
                        size_t i = 0; 
                        i < index - currArraySize + 1;
                        i++)
                    {
                        evalBooleanArray->GetValue().push_back(false);
                    }
                }

                evalBooleanArray->GetValue()[index] = 
                    static_cast<EvalBoolean*>(value)->GetValue();
            }
            break;

        case EvalObject::TYPE_EVAL_STRING_ARRAY:
            {
                if (value->GetType() != EvalObject::TYPE_EVAL_STRING)
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("invalid value of type %s for assignment to element "
                            "#%d of array variable %s of type %s",
                            value->GetTypeName().c_str(),
                            index,
                            variableName.c_str(),
                            variable->GetTypeName().c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_VAR_TYPE_ERROR);
                }

                EvalStringArray*
                    evalStringArray =
                        static_cast<EvalStringArray*>(
                            variable);

                size_t currArraySize = 
                    evalStringArray->GetValue().size();

                if (index >= currArraySize)
                {
                    evalStringArray->GetValue().reserve(index + 1);

                    for (
                        size_t i = 0; 
                        i < index - currArraySize + 1;
                        i++)
                    {
                        evalStringArray->GetValue().push_back("");
                    }
                }

                evalStringArray->GetValue()[index] = 
                    static_cast<EvalString*>(value)->GetValue();
            }
            break;

        default:
            MNT_THROW_ERROR_VARARGS(
                ("variable %s is not an array",
                    variableName.c_str()),
                identifierCtr->GetLineNumber(),
                0,
                MNT_E_INVALID_ARRAY_VAR_ERROR);
            break;
        }
    }
        
    delete value;

    executeContext.GetEvaluator().Clean();
    ITS_ASSERT(executeContext.GetEvaluator().GetEvalStackSize() == 0);
}

void
ConditionalInstructionCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2 || _children.size() == 1);

    ThenPartListCtr* thenPartListCtr =
        static_cast<ThenPartListCtr*>(_children[0]);

    // From grammar.
    ITS_ASSERT(thenPartListCtr->GetType() == CTR_TYPE_THEN_PART_LIST);

    ElsePartCtr* elsePartCtr = NULL;

    if (_children.size() == 2)
    {
        elsePartCtr = static_cast<ElsePartCtr*>(_children[1]);

        // From grammar.
        ITS_ASSERT(elsePartCtr->GetType() == CTR_TYPE_ELSE_PART);
    }

    bool alternativeExecuted = false;

    for (size_t i = 0; i < thenPartListCtr->GetChildren().size(); i++)
    {
        ThenPartCtr* thenPartCtr = 
            static_cast<ThenPartCtr*>(thenPartListCtr->GetChildren()[i]);

        // From grammar.
        ITS_ASSERT(thenPartCtr->GetType() == CTR_TYPE_THEN_PART);

        // From grammar.
        ITS_ASSERT(thenPartCtr->GetChildren().size() == 2);

        Evaluator& evaluator = executeContext.GetEvaluator();
        evaluator.Clean();

        thenPartCtr->GetChildren()[0]->Execute(executeContext);

        ITS_ASSERT(evaluator.GetEvalStackSize() >= 1);

        EvalObject* value = evaluator.Top();
        evaluator.Pop();

        if (value->GetType() != EvalObject::TYPE_EVAL_BOOLEAN)
        {
            MNT_THROW_ERROR(
                "then part condition expression must be of type boolean",
                thenPartCtr->GetLineNumber(),
                0,
                MNT_E_INVALID_EXPR_TYPE_ERROR);
        }

        if (static_cast<EvalBoolean*>(value)->GetValue() == true)
        {
            thenPartCtr->GetChildren()[1]->Execute(executeContext);

            alternativeExecuted = true;

            delete value;
             
            break;
        }
        else
        {
            // Nothing to do: continue to try other alternatives.

            delete value;
        }
    }

    if (elsePartCtr != NULL && !alternativeExecuted)
    {
        // From grammar.
        ITS_ASSERT(elsePartCtr->GetChildren().size() == 1);

        elsePartCtr->GetChildren()[0]->Execute(executeContext);
    }

    executeContext.GetEvaluator().Clean();
    ITS_ASSERT(executeContext.GetEvaluator().GetEvalStackSize() == 0);
}

void
ThenPartListCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
ThenPartCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
ElsePartCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
LoopInstructionCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 3);

    _children[0]->Execute(executeContext);

    bool bStop = false;

    while (!bStop)
    {
        Evaluator& evaluator = executeContext.GetEvaluator();
        evaluator.Clean();

        _children[1]->Execute(executeContext);

        ITS_ASSERT(evaluator.GetEvalStackSize() >= 1);

        EvalObject* value = evaluator.Top();
        evaluator.Pop();

        if (value->GetType() != EvalObject::TYPE_EVAL_BOOLEAN)
        {
            MNT_THROW_ERROR(
                "loop condition expression must be of type boolean",
                _children[1]->GetLineNumber(),
                0,
                MNT_E_INVALID_EXPR_TYPE_ERROR);
        }

        if (static_cast<EvalBoolean*>(value)->GetValue() == false)
        {
            _children[2]->Execute(executeContext);
        }
        else
        {
            bStop = true;
        }

        delete value;
    }

    executeContext.GetEvaluator().Clean();
    ITS_ASSERT(executeContext.GetEvaluator().GetEvalStackSize() == 0);

}

void
PrimaryExprCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
PostfixExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 1 || _children.size() == 2);

    // From grammar.
    ITS_ASSERT(HasValueString());

    // From grammar.
    ITS_ASSERT(
        GetValueString() == "command" || 
        GetValueString() == "arrayEltAccess");

    IdentifierCtr* identifierCtr = 
        static_cast<IdentifierCtr*>(_children[0]);

    if (identifierCtr->GetType() == CTR_TYPE_IDENTIFIER)
    {
        if (_children.size() == 1)
        {
            ArgumentListCtr argumentListCtr;

            ExecuteCommand(
                executeContext,
                *identifierCtr, 
                argumentListCtr);
        }
        else if (_children.size() == 2)
        {
            if (GetValueString() == "command")
            {
                ArgumentListCtr* argumentListCtr = 
                    static_cast<ArgumentListCtr*>(_children[1]);

                // From grammar.
                ITS_ASSERT(
                    argumentListCtr->GetType() == CTR_TYPE_ARGUMENT_LIST);

                ExecuteCommand(
                    executeContext,
                    *identifierCtr, 
                    *argumentListCtr);
            }
            else if (GetValueString() == "arrayEltAccess")
            {
                Interpreter& interpreter = executeContext.GetInterpreter();

                string variableName = identifierCtr->GetValueString();
                
                Construct* argument = _children[1];

                argument->Execute(executeContext);

                EvalObject* evalIndex = executeContext.GetEvaluator().Top();

                executeContext.GetEvaluator().Pop();

                size_t index = 0;

                if (evalIndex->GetType() != EvalObject::TYPE_EVAL_BYTE &&
                    evalIndex->GetType() != EvalObject::TYPE_EVAL_INTEGER)
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("invalid type %s for index of array variable %s",
                            evalIndex->GetTypeName().c_str(),
                            variableName.c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_ARRAY_INDEX_TYPE_ERROR);
                }
                else if (evalIndex->GetType() == EvalObject::TYPE_EVAL_BYTE)
                {
                    index = static_cast<EvalByte*>(evalIndex)->GetValue();
                }
                else if (evalIndex->GetType() == EvalObject::TYPE_EVAL_INTEGER)
                {
                    index = static_cast<EvalInteger*>(evalIndex)->GetValue();
                }
                else
                {
                    bool must_not_be_reached = false;
                    ITS_ASSERT(must_not_be_reached);
                }

                delete evalIndex;

                if (index < 0)
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("negative value %d for index of array variable %s",
                            index,
                            variableName.c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR);
                }

                if (!interpreter.HasVariable(variableName))
                {
                    MNT_THROW_ERROR_VARARGS(
                        ("use of unknown array variable of name %s",
                            variableName.c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_ARRAY_VAR_NAME_ERROR);
                }

                EvalObject* 
                    evalObject =
                        &interpreter.
                            RetrieveVariable(variableName);

                switch (evalObject->GetType())
                {
                case EvalObject::TYPE_EVAL_BYTE_ARRAY:
                    {
                        EvalByteArray*
                            evalByteArray =
                                static_cast<EvalByteArray*>(
                                    evalObject);

                        if (index >= evalByteArray->GetValue().size())
                        {
                            MNT_THROW_ERROR_VARARGS(
                                ("index out of range for array variable of "
                                    "name %s (index is %d and should be less "
                                    "than %d)",
                                    variableName.c_str(),
                                    index,
                                    evalByteArray->GetValue().size()),
                                identifierCtr->GetLineNumber(),
                                0,
                                MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR);
                        }

                        unsigned char eltValue = 
                            evalByteArray->GetValue()[index];

                        EvalByte* evalByte = 
                            new EvalByte(eltValue);

                        executeContext.GetEvaluator().Push(evalByte);
                    }
                    break;

                case EvalObject::TYPE_EVAL_INTEGER_ARRAY:
                    {
                        EvalIntegerArray*
                            evalIntegerArray =
                                static_cast<EvalIntegerArray*>(
                                    evalObject);

                        if (index >= evalIntegerArray->GetValue().size())
                        {
                            MNT_THROW_ERROR_VARARGS(
                                ("index out of range for array variable of "
                                    "name %s (index is %d and should be less "
                                    "than %d)",
                                    variableName.c_str(),
                                    index,
                                    evalIntegerArray->GetValue().size()),
                                identifierCtr->GetLineNumber(),
                                0,
                                MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR);
                        }

                        long eltValue = 
                            evalIntegerArray->GetValue()[index];

                        EvalInteger* evalInteger = 
                            new EvalInteger(eltValue);

                        executeContext.GetEvaluator().Push(evalInteger);
                    }
                    break;

                case EvalObject::TYPE_EVAL_BOOLEAN_ARRAY:
                    {
                        EvalBooleanArray*
                            evalBooleanArray =
                                static_cast<EvalBooleanArray*>(
                                    evalObject);

                        if (index >= evalBooleanArray->GetValue().size())
                        {
                            MNT_THROW_ERROR_VARARGS(
                                ("index out of range for array variable of "
                                    "name %s (index is %d and should be less "
                                    "than %d)",
                                    variableName.c_str(),
                                    index,
                                    evalBooleanArray->GetValue().size()),
                                identifierCtr->GetLineNumber(),
                                0,
                                MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR);
                        }

                        bool eltValue = 
                            evalBooleanArray->GetValue()[index];

                        EvalBoolean* evalBoolean = 
                            new EvalBoolean(eltValue);

                        executeContext.GetEvaluator().Push(evalBoolean);
                    }
                    break;

                case EvalObject::TYPE_EVAL_STRING_ARRAY:
                    {
                        EvalStringArray*
                            evalStringArray =
                                static_cast<EvalStringArray*>(
                                    evalObject);

                        if (index >= evalStringArray->GetValue().size())
                        {
                            MNT_THROW_ERROR_VARARGS(
                                ("index out of range for array variable of "
                                    "name %s (index is %d and should be less "
                                    "than %d)",
                                    variableName.c_str(),
                                    index,
                                    evalStringArray->GetValue().size()),
                                identifierCtr->GetLineNumber(),
                                0,
                                MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR);
                        }

                        string eltValue = 
                            evalStringArray->GetValue()[index];

                        EvalString* evalString = 
                            new EvalString(eltValue);

                        executeContext.GetEvaluator().Push(evalString);
                    }
                    break;

                default:
                    MNT_THROW_ERROR_VARARGS(
                        ("variable %s is not an array",
                            variableName.c_str()),
                        identifierCtr->GetLineNumber(),
                        0,
                        MNT_E_INVALID_ARRAY_VAR_ERROR);
                    break;
                }
            }
            else
            {
                bool must_not_be_reached = false;
                ITS_ASSERT(must_not_be_reached);
            }
        }
    }
    else
    {
        if (GetValueString() == "command")
        {
            MNT_THROW_ERROR_VARARGS(
                ("invalid command name (identifier expected)"),
                identifierCtr->GetLineNumber(),
                0,
                MNT_E_INVALID_COMMAND_ERROR);
        }
        else if (GetValueString() == "arrayEltAccess")
        {
            MNT_THROW_ERROR_VARARGS(
                ("invalid array variable name (identifier expected)"),
                identifierCtr->GetLineNumber(),
                0,
                MNT_E_INVALID_ARRAY_VAR_ERROR);
        }
        else
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
        }
    }
}

void
UnaryExprCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
UnaryOperatorCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
MultiplicativeExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);
    ITS_ASSERT(HasValueString());

    _children[0]->Execute(executeContext);
    _children[1]->Execute(executeContext);

    Evaluator& evaluator = executeContext.GetEvaluator();

    evaluator.SetCurrentColumnNumber(0);
    evaluator.SetCurrentLineNumber(GetLineNumber());
    
    ITS_ASSERT(evaluator.GetEvalStackSize() >= 2);

    EvalObject* evalObject1 = evaluator.Top();
    evaluator.Pop();

    EvalObject* evalObject2 = evaluator.Top();
    evaluator.Pop();

    EvalObject* result = NULL;

    if (GetValueString() == "*")
    {
        result = evalObject2->OperationMul(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == "/")
    {
        result = evalObject2->OperationDiv(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == "mod")
    {
        result = evalObject2->OperationMod(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    delete evalObject1;
    delete evalObject2;
}

void
AdditiveExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);
    ITS_ASSERT(HasValueString());

    _children[0]->Execute(executeContext);
    _children[1]->Execute(executeContext);

    Evaluator& evaluator = executeContext.GetEvaluator();

    evaluator.SetCurrentColumnNumber(0);
    evaluator.SetCurrentLineNumber(GetLineNumber());
    
    ITS_ASSERT(evaluator.GetEvalStackSize() >= 2);

    EvalObject* evalObject1 = evaluator.Top();
    evaluator.Pop();

    EvalObject* evalObject2 = evaluator.Top();
    evaluator.Pop();

    EvalObject* result = NULL;

    if (GetValueString() == "+")
    {
        result = evalObject2->OperationAdd(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == "-")
    {
        result = evalObject2->OperationSub(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    delete evalObject1;
    delete evalObject2;
}

void
RelationalExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);
    ITS_ASSERT(HasValueString());

    _children[0]->Execute(executeContext);
    _children[1]->Execute(executeContext);

    Evaluator& evaluator = executeContext.GetEvaluator();

    evaluator.SetCurrentColumnNumber(0);
    evaluator.SetCurrentLineNumber(GetLineNumber());
    
    ITS_ASSERT(evaluator.GetEvalStackSize() >= 2);

    EvalObject* evalObject1 = evaluator.Top();
    evaluator.Pop();

    EvalObject* evalObject2 = evaluator.Top();
    evaluator.Pop();

    EvalObject* result = NULL;

    if (GetValueString() == "<")
    {
        result = evalObject2->OperationLt(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == ">")
    {
        result = evalObject2->OperationGt(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == "<=")
    {
        result = evalObject2->OperationLte(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == ">=")
    {
        result = evalObject2->OperationGte(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    delete evalObject1;
    delete evalObject2;
}

void
EqualityExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);
    ITS_ASSERT(HasValueString());

    _children[0]->Execute(executeContext);
    _children[1]->Execute(executeContext);

    Evaluator& evaluator = executeContext.GetEvaluator();

    evaluator.SetCurrentColumnNumber(0);
    evaluator.SetCurrentLineNumber(GetLineNumber());
    
    ITS_ASSERT(evaluator.GetEvalStackSize() >= 2);

    EvalObject* evalObject1 = evaluator.Top();
    evaluator.Pop();

    EvalObject* evalObject2 = evaluator.Top();
    evaluator.Pop();

    EvalObject* result = NULL;

    if (GetValueString() == "=")
    {
        result = evalObject2->OperationEq(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else if (GetValueString() == "/=")
    {
        result = evalObject2->OperationNe(evaluator, *evalObject1);
        evaluator.Push(result);
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }

    delete evalObject1;
    delete evalObject2;
}

void
LogicalAndExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);
    ITS_ASSERT(HasValueString());

    _children[0]->Execute(executeContext);
    _children[1]->Execute(executeContext);

    Evaluator& evaluator = executeContext.GetEvaluator();

    evaluator.SetCurrentColumnNumber(0);
    evaluator.SetCurrentLineNumber(GetLineNumber());
    
    ITS_ASSERT(evaluator.GetEvalStackSize() >= 2);

    EvalObject* evalObject1 = evaluator.Top();
    evaluator.Pop();

    EvalObject* evalObject2 = evaluator.Top();
    evaluator.Pop();

    EvalObject* result = evalObject2->OperationAnd(evaluator, *evalObject1);
    evaluator.Push(result);

    delete evalObject1;
    delete evalObject2;
}

void
LogicalOrExprCtr::Execute(ExecuteContext& executeContext)
{
    // From grammar.
    ITS_ASSERT(_children.size() == 2);
    ITS_ASSERT(HasValueString());

    _children[0]->Execute(executeContext);
    _children[1]->Execute(executeContext);

    Evaluator& evaluator = executeContext.GetEvaluator();

    evaluator.SetCurrentColumnNumber(0);
    evaluator.SetCurrentLineNumber(GetLineNumber());
    
    ITS_ASSERT(evaluator.GetEvalStackSize() >= 2);

    EvalObject* evalObject1 = evaluator.Top();
    evaluator.Pop();

    EvalObject* evalObject2 = evaluator.Top();
    evaluator.Pop();

    EvalObject* result = evalObject2->OperationOr(evaluator, *evalObject1);
    evaluator.Push(result);

    delete evalObject1;
    delete evalObject2;
}

void
ExprCtr::Execute(ExecuteContext& executeContext)
{
    // Nothing to do.
}

void
IdentifierCtr::Execute(ExecuteContext& executeContext)
{
    string name = GetValueString();

    Interpreter& interpreter = executeContext.GetInterpreter();

    if (interpreter.HasCommand(name) && 
        interpreter.HasVariable(name))
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
    }
    else if (interpreter.HasVariable(name))
    {
        const EvalObject& value = 
            interpreter.
                RetrieveVariable(
                    name);

        executeContext.GetEvaluator().Push(value.Clone());
    }
    else if (interpreter.HasCommand(name))
    {
        // Nothing to do.
    }
    else
    {
        MNT_THROW_ERROR_VARARGS(
            ("use of unknown variable of name %s",
                name.c_str()),
            GetLineNumber(),
            0,
            MNT_E_INVALID_VAR_NAME_ERROR);
    }
}

void
ByteCtr::Execute(ExecuteContext& executeContext)
{
    EvalByte* 
        evalByte = 
            new EvalByte(
                GetValueByte());
    executeContext.GetEvaluator().Push(evalByte);
}

void
IntegerCtr::Execute(ExecuteContext& executeContext)
{
    EvalInteger* 
        evalInteger = 
            new EvalInteger(
                GetValueLong());
    executeContext.GetEvaluator().Push(evalInteger);
}

void
BooleanCtr::Execute(ExecuteContext& executeContext)
{
    EvalBoolean* 
        evalBoolean = 
            new EvalBoolean(
                GetValueBool());
    executeContext.GetEvaluator().Push(evalBoolean);
}

void
StringCtr::Execute(ExecuteContext& executeContext)
{
    EvalString* 
        evalString = 
            new EvalString(
                GetValueString());
    executeContext.GetEvaluator().Push(evalString);
}

void
ByteArrayCtr::Execute(ExecuteContext& executeContext)
{
    EvalByteArray* 
        evalByteArray = 
            new EvalByteArray(
                GetValueByteArray());
    executeContext.GetEvaluator().Push(evalByteArray);
}

void
IntegerArrayCtr::Execute(ExecuteContext& executeContext)
{
    EvalIntegerArray* 
        evalIntegerArray = 
            new EvalIntegerArray(
                GetValueLongArray());
    executeContext.GetEvaluator().Push(evalIntegerArray);
}

void
BooleanArrayCtr::Execute(ExecuteContext& executeContext)
{
    EvalBooleanArray* 
        evalBooleanArray = 
            new EvalBooleanArray(
                GetValueBoolArray());
    executeContext.GetEvaluator().Push(evalBooleanArray);
}

void
StringArrayCtr::Execute(ExecuteContext& executeContext)
{
    EvalStringArray* 
        evalStringArray = 
            new EvalStringArray(
                GetValueStringArray());
    executeContext.GetEvaluator().Push(evalStringArray);
}

///////////////////////////////////////////////////////////////////////////////
//
// Helpers.
//

void
ExecuteCommand(
        ExecuteContext& executeContext,
        IdentifierCtr& identifierCtr, 
        ArgumentListCtr& argumentListCtr)
{
    Interpreter& interpreter = executeContext.GetInterpreter();

    string commandName = identifierCtr.GetValueString();

    if (!interpreter.HasCommand(commandName))
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid command %s", commandName.c_str()),
            identifierCtr.GetLineNumber(),
            0,
            MNT_E_INVALID_COMMAND_ERROR);
    }

    Command& command = interpreter.RetrieveCommand(commandName);

    Command::ReturnType returnType = command.GetReturnType();
    Command::ArgumentTypes argumentTypes = command.GetArgumentTypes();

    if (argumentTypes.size() != argumentListCtr.GetChildrenSize())
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid number of arguments for command %s", 
                commandName.c_str()),
            identifierCtr.GetLineNumber(),
            0,
            MNT_E_INVALID_NB_OF_ARGS_ERROR);
    }

    Command::Arguments arguments;

    for (size_t i = 0; i < argumentTypes.size(); i++)
    {
        Construct* argument = argumentListCtr.GetChildren()[i];

        argument->Execute(executeContext);

        ITS_ASSERT(executeContext.GetEvaluator().GetEvalStackSize() == 1);

        EvalObject* evalObject = executeContext.GetEvaluator().Top();

        executeContext.GetEvaluator().Pop();

        if (argumentTypes[i] != ValueObject::VALUE_TYPE_ANY && 
            evalObject->GetType() != (int)argumentTypes[i])
        {
            MNT_THROW_ERROR_VARARGS(
                ("invalid type for argument #%d of command %s "
                    "(formal argument type is %s actual argument type is %s)",
                    i,
                    commandName.c_str(),
                    ValueObject::TypeToString(argumentTypes[i]).c_str(),
                    evalObject->GetTypeName().c_str()),
                identifierCtr.GetLineNumber(),
                0,
                MNT_E_INVALID_ARG_TYPE_ERROR);
        }

        if (argument->IsOut() && argument->GetType() != CTR_TYPE_IDENTIFIER)
        {
            MNT_THROW_ERROR_VARARGS(
                ("invalid out argument #%d of command %s "
                    "(out specifier must be applied only to a variable name)",
                    i,
                    commandName.c_str()),
                identifierCtr.GetLineNumber(),
                0,
                MNT_E_INVALID_OUT_ARG_ERROR);
        }
        else if (argument->IsOut())
        {
            string variableName = argument->GetValueString();

            Interpreter& interpreter = executeContext.GetInterpreter();

            if (!interpreter.HasVariable(variableName))
            {
                MNT_THROW_ERROR_VARARGS(
                    ("invalid out argument #%d of command %s "
                        "(out specifier applied to a name %s that is not a "
                        "variable name)",
                        i,
                        commandName.c_str(),
                        variableName.c_str()),
                    identifierCtr.GetLineNumber(),
                    0,
                    MNT_E_INVALID_OUT_ARG_ERROR);
            }
        }

        ValueObject* valueObject = NULL;

        switch (evalObject->GetType())
        {
        case EvalObject::TYPE_EVAL_BYTE:
            valueObject = 
                new ValueByte(
                    static_cast<EvalByte*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_INTEGER:
            valueObject = 
                new ValueInteger(
                    static_cast<EvalInteger*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_BOOLEAN:
            valueObject = 
                new ValueBoolean(
                    static_cast<EvalBoolean*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_STRING:
            valueObject = 
                new ValueString(
                    static_cast<EvalString*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_BYTE_ARRAY:
            valueObject = 
                new ValueByteArray(
                    static_cast<EvalByteArray*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_INTEGER_ARRAY:
            valueObject = 
                new ValueIntegerArray(
                    static_cast<EvalIntegerArray*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_BOOLEAN_ARRAY:
            valueObject = 
                new ValueBooleanArray(
                    static_cast<EvalBooleanArray*>(
                        evalObject)->GetValue());
            break;

        case EvalObject::TYPE_EVAL_STRING_ARRAY:
            valueObject = 
                new ValueStringArray(
                    static_cast<EvalStringArray*>(
                        evalObject)->GetValue());
            break;

        default:
            {
                bool must_not_be_reached = false;
                ITS_ASSERT(must_not_be_reached);
            }
            break;
        }

        delete evalObject;

        arguments.push_back(valueObject);
    }

    Mnt& mnt = executeContext.GetMnt();

    Command::ReturnValue returnValue = command.Execute(mnt, arguments);

    for (size_t j = 0; j < arguments.size(); j++)
    {
        Construct* argument = argumentListCtr.GetChildren()[j];

        if (argument->IsOut())
        {
            // Check done previously (begin of function).
            ITS_ASSERT(argument->GetType() == CTR_TYPE_IDENTIFIER);

            string variableName = argument->GetValueString();

            Interpreter& interpreter = executeContext.GetInterpreter();

            // Check done previously (begin of function).
            ITS_ASSERT(interpreter.HasVariable(variableName));

            EvalObject* 
                evalObject =
                    &interpreter.
                        RetrieveVariable(variableName);

            ITS_ASSERT(arguments[j]->GetType() == evalObject->GetType());

            switch (evalObject->GetType())
            {
            case EvalObject::TYPE_EVAL_BYTE:
                static_cast<EvalByte*>(evalObject)->SetValue(
                    static_cast<ValueByte*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_INTEGER:
                static_cast<EvalInteger*>(evalObject)->SetValue(
                    static_cast<ValueInteger*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_BOOLEAN:
                static_cast<EvalBoolean*>(evalObject)->SetValue(
                    static_cast<ValueBoolean*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_STRING:
                static_cast<EvalString*>(evalObject)->SetValue(
                    static_cast<ValueString*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_BYTE_ARRAY:
                static_cast<EvalByteArray*>(evalObject)->SetValue(
                    static_cast<ValueByteArray*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_INTEGER_ARRAY:
                static_cast<EvalIntegerArray*>(evalObject)->SetValue(
                    static_cast<ValueIntegerArray*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_BOOLEAN_ARRAY:
                static_cast<EvalBooleanArray*>(evalObject)->SetValue(
                    static_cast<ValueBooleanArray*>(arguments[j])->GetValue());
                break;

            case EvalObject::TYPE_EVAL_STRING_ARRAY:
                static_cast<EvalStringArray*>(evalObject)->SetValue(
                    static_cast<ValueStringArray*>(arguments[j])->GetValue());
                break;

            default:
                {
                    bool must_not_be_reached = false;
                    ITS_ASSERT(must_not_be_reached);
                }
                break;
            }
        }

        delete arguments[j];
    }

    if (returnType != ValueObject::VALUE_TYPE_ANY && 
        returnValue->GetType() != returnType)
    {
        MNT_THROW_ERROR_VARARGS(
            ("invalid type for return value of command %s "
                "(formal return value type is %s actual return value type is "
                "%s)",
                commandName.c_str(),
                ValueObject::TypeToString(returnType).c_str(),
                ValueObject::TypeToString(returnValue->GetType()).c_str()),
            identifierCtr.GetLineNumber(),
            0,
            MNT_E_INVALID_RET_VAL_TYPE_ERROR);
    }

    EvalObject* commandReturn = NULL;

    switch (returnValue->GetType())
    {
    case ValueObject::VALUE_TYPE_NONE:
        commandReturn = new EvalNone();
        break;

    case ValueObject::VALUE_TYPE_BYTE:
        commandReturn =
            new EvalByte(
                static_cast<ValueByte*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_INTEGER:
        commandReturn =
            new EvalInteger(
                static_cast<ValueInteger*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_BOOLEAN:
        commandReturn =
            new EvalBoolean(
                static_cast<ValueBoolean*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_STRING:
        commandReturn =
            new EvalString(
                static_cast<ValueString*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_BYTE_ARRAY:
        commandReturn =
            new EvalByteArray(
                static_cast<ValueByteArray*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_INTEGER_ARRAY:
        commandReturn =
            new EvalIntegerArray(
                static_cast<ValueIntegerArray*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_BOOLEAN_ARRAY:
        commandReturn =
            new EvalBooleanArray(
                static_cast<ValueBooleanArray*>(
                    returnValue)->GetValue());
        break;

    case ValueObject::VALUE_TYPE_STRING_ARRAY:
        commandReturn =
            new EvalStringArray(
                static_cast<ValueStringArray*>(
                    returnValue)->GetValue());
        break;

    default:
        {
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
        }
    }

    delete returnValue;

    executeContext.GetEvaluator().Push(commandReturn);
}
 

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


