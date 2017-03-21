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
// LOG: Revision 5.2  2001/10/18 22:22:06  hdivoux
// LOG: Update for improvements (from PR5).
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.5  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/09 20:58:32  hdivoux
// LOG: Port to GNU g++.
// LOG:
// LOG: Revision 1.2  2001/08/09 20:30:47  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_evaluator.cpp,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_evaluator.cpp: MNT evaluator implementation.
//
//


#include <mnt_evaluator.h>
#include <mnt_exception.h>
#include <mnt_errors.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)

#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
// EvalObject.
//

EvalObject* 
EvalObject::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("addition operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("subtraction operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("multiplication operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("division operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("modulo operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("less than operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("less than or equal operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("greater than operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("greather than or equal operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("equality operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("not equal operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("and operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    MNT_THROW_ERROR_VARARGS(
        ("or operator is invalid between types %s and %s",
            this->GetTypeName().c_str(),
            other.GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}

EvalObject* 
EvalObject::OperationNot(
    Evaluator& evaluator) const
{
    MNT_THROW_ERROR_VARARGS(
        ("not operator is invalid for type %s",
            this->GetTypeName().c_str()),
        evaluator.GetCurrentLineNumber(),
        evaluator.GetCurrentColumnNumber(),
        MNT_E_INVALID_OPERATION_ERROR);

    return NULL;
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalNone.
//

EvalObject* 
EvalNone::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAdd(evaluator, other);
}

EvalObject* 
EvalNone::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalNone::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalNone::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalNone::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalNone::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLt(evaluator, other);
}

EvalObject* 
EvalNone::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLte(evaluator, other);
}

EvalObject* 
EvalNone::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGt(evaluator, other);
}

EvalObject* 
EvalNone::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGte(evaluator, other);
}

EvalObject* 
EvalNone::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationEq(evaluator, other);
}

EvalObject* 
EvalNone::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationNe(evaluator, other);
}

EvalObject* 
EvalNone::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalNone::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalNone::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalByte.
//

EvalObject* 
EvalByte::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalByte(
                        this->GetValue() + 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        (long)this->GetValue() +
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationAdd(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalByte(
                        this->GetValue() - 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        (long)this->GetValue() -
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationSub(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalByte(
                        this->GetValue() * 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        (long)this->GetValue() *
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationMul(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalByte(
                        this->GetValue() /
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        (long)this->GetValue() /
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationDiv(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalByte(
                        this->GetValue() % 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        (long)this->GetValue() %
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationMod(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() < 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        (long)this->GetValue() <
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationLt(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() <= 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        (long)this->GetValue() <=
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationLte(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() > 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        (long)this->GetValue() >
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationGt(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() >= 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        (long)this->GetValue() >=
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationGte(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() == 
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        (long)this->GetValue() ==
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationEq(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() !=
                        ((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        (long)this->GetValue() !=
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationLt(evaluator, other);
    }
}

EvalObject* 
EvalByte::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalByte::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalByte::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalInteger.
//

EvalObject* 
EvalInteger::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalInteger(
                        this->GetValue() + 
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        this->GetValue() + 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationAdd(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalInteger(
                        this->GetValue() - 
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        this->GetValue() - 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationSub(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalInteger(
                        this->GetValue() * 
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        this->GetValue() * 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationMul(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalInteger(
                        this->GetValue() / 
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        this->GetValue() /
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationDiv(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalInteger(
                        this->GetValue() % 
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalInteger(
                        this->GetValue() % 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationMod(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() < 
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        this->GetValue() < 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationLt(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() <=
                        (long)((EvalByte&)other).GetValue());


    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        this->GetValue() <= 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationLte(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() >
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        this->GetValue() > 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationGt(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() >=
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        this->GetValue() >= 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationGte(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() ==
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        this->GetValue() == 
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationEq(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalBoolean(
                        this->GetValue() !=
                        (long)((EvalByte&)other).GetValue());

    case TYPE_EVAL_INTEGER:
        return new EvalBoolean(
                        this->GetValue() !=
                        ((EvalInteger&)other).GetValue());

    default:
        return EvalObject::OperationLt(evaluator, other);
    }
}

EvalObject* 
EvalInteger::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalInteger::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalInteger::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalBoolean.
//

EvalObject* 
EvalBoolean::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAdd(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLt(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLte(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGt(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGte(evaluator, other);
}

EvalObject* 
EvalBoolean::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BOOLEAN:
        return new EvalBoolean(
                        this->GetValue() ==
                        ((EvalBoolean&)other).GetValue());

    default:
        return EvalObject::OperationEq(evaluator, other);
    }  
}

EvalObject* 
EvalBoolean::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BOOLEAN:
        return new EvalBoolean(
                        this->GetValue() !=
                        ((EvalBoolean&)other).GetValue());

    default:
        return EvalObject::OperationNe(evaluator, other);
    }  

}

EvalObject* 
EvalBoolean::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BOOLEAN:
        return new EvalBoolean(
                        this->GetValue() &&
                        ((EvalBoolean&)other).GetValue());

    default:
        return EvalObject::OperationAnd(evaluator, other);
    }
}

EvalObject* 
EvalBoolean::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BOOLEAN:
        return new EvalBoolean(
                        this->GetValue() ||
                        ((EvalBoolean&)other).GetValue());

    default:
        return EvalObject::OperationOr(evaluator, other);
    }
}

EvalObject* 
EvalBoolean::OperationNot(
    Evaluator& evaluator) const 
{
    return new EvalBoolean(!this->GetValue());
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalString.
//

EvalObject* 
EvalString::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_BYTE:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalByte&)other).ToString());

    case TYPE_EVAL_INTEGER:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalInteger&)other).ToString());

    case TYPE_EVAL_BOOLEAN:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalBoolean&)other).ToString());

    case TYPE_EVAL_STRING:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalString&)other).GetValue());

    case TYPE_EVAL_BYTE_ARRAY:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalByteArray&)other).ToString());

    case TYPE_EVAL_INTEGER_ARRAY:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalIntegerArray&)other).ToString());

    case TYPE_EVAL_BOOLEAN_ARRAY:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalBooleanArray&)other).ToString());

    case TYPE_EVAL_STRING_ARRAY:
        return new EvalString(
                        this->GetValue() + 
                        ((EvalStringArray&)other).ToString());

    default:
        return EvalObject::OperationAdd(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalString::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalString::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalString::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalString::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_STRING:
        return new EvalBoolean(
                        this->GetValue() < 
                        ((EvalString&)other).GetValue());

    default:
        return EvalObject::OperationLt(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_STRING:
        return new EvalBoolean(
                        this->GetValue() <=
                        ((EvalString&)other).GetValue());

    default:
        return EvalObject::OperationLte(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_STRING:
        return new EvalBoolean(
                        this->GetValue() >
                        ((EvalString&)other).GetValue());

    default:
        return EvalObject::OperationGt(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_STRING:
        return new EvalBoolean(
                        this->GetValue() >= 
                        ((EvalString&)other).GetValue());

    default:
        return EvalObject::OperationGte(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_STRING:
        return new EvalBoolean(
                        this->GetValue() ==
                        ((EvalString&)other).GetValue());

    default:
        return EvalObject::OperationEq(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    switch (other.GetType())
    {
    case TYPE_EVAL_STRING:
        return new EvalBoolean(
                        this->GetValue() !=
                        ((EvalString&)other).GetValue());

    default:
        return EvalObject::OperationNe(evaluator, other);
    }
}

EvalObject* 
EvalString::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalString::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalString::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalByteArray.
//

EvalObject* 
EvalByteArray::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAdd(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLt(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLte(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGt(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGte(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationEq(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationNe(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalByteArray::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalIntegerArray.
//

EvalObject* 
EvalIntegerArray::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAdd(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLt(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLte(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGt(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGte(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationEq(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationNe(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalIntegerArray::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalBooleanArray.
//

EvalObject* 
EvalBooleanArray::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAdd(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLt(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLte(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGt(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGte(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationEq(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationNe(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalBooleanArray::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


///////////////////////////////////////////////////////////////////////////////
//
// EvalStringArray.
//

EvalObject* 
EvalStringArray::OperationAdd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAdd(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationSub(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationSub(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationMul(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMul(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationDiv(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationDiv(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationMod(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationMod(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationLt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLt(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationLte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationLte(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationGt(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGt(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationGte(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationGte(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationEq(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationEq(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationNe(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationNe(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationAnd(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationAnd(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationOr(
    Evaluator& evaluator, 
    const EvalObject& other) const
{
    return EvalObject::OperationOr(evaluator, other);
}

EvalObject* 
EvalStringArray::OperationNot(
    Evaluator& evaluator) const 
{
    return EvalObject::OperationNot(evaluator);
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


