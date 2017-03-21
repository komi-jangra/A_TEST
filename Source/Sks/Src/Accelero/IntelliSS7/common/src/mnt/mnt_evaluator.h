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
// LOG: Revision 1.4  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:06:31  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_evaluator.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_evaluator.h: MNT evaluator (internal to MNT).
//
//


#if !defined(_MNT_EVALUATOR_H_)
#define _MNT_EVALUATOR_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mnt.h>

#include <stack>

#include <mnt_helpers.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)

///////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

class Evaluator;
class EvalByte;
class EvalInteger;
class EvalBoolean;
class EvalString;


///////////////////////////////////////////////////////////////////////////////
//
// EvalObject.
//

class EvalObject
{
public:

    EvalObject()
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* Clone() const = 0;

    virtual ~EvalObject()
    {
        // Nothing to do.
    }

    // MUST be kept in sync with ValueObject::Type.
    enum Type
    {
        TYPE_EVAL_ANY           = 0,
        TYPE_EVAL_NONE          = 1,
        TYPE_EVAL_BYTE          = 2,
        TYPE_EVAL_INTEGER       = 3,
        TYPE_EVAL_BOOLEAN       = 4,
        TYPE_EVAL_STRING        = 5,
        TYPE_EVAL_BYTE_ARRAY    = 6,
        TYPE_EVAL_INTEGER_ARRAY = 7,
        TYPE_EVAL_BOOLEAN_ARRAY = 8,
        TYPE_EVAL_STRING_ARRAY  = 9
    };

    virtual int GetType() const = 0;

    virtual std::string GetTypeName() const = 0;

    virtual std::string ToString() const = 0;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

};


///////////////////////////////////////////////////////////////////////////////
//
// EvalNone.
//

class EvalNone : public EvalObject
{
public:

    EvalNone() 
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalNone(*this);
    }

    virtual ~EvalNone()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_NONE;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "none";
    }

    virtual std::string
    ToString() const
    {
        return "<NONE>";
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    // Nothing.

};

///////////////////////////////////////////////////////////////////////////////
//
// EvalByte.
//

class EvalByte : public EvalObject
{
public:

    EvalByte() 
    :   _value(0)
    {}

    EvalByte(unsigned char value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalByte(*this);
    }

    virtual ~EvalByte()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_BYTE;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "byte";
    }

    virtual std::string
    ToString() const
    {
        return ByteValueToString(_value);
    }

    unsigned char 
    GetValue() const
    {
        return _value;
    }

    void 
    SetValue(unsigned char value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    unsigned char _value;

};

///////////////////////////////////////////////////////////////////////////////
//
// EvalInteger.
//

class EvalInteger : public EvalObject
{
public:

    EvalInteger() 
    :   _value(0)
    {}

    EvalInteger(long value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalInteger(*this);
    }

    virtual ~EvalInteger()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_INTEGER;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "integer";
    }

    virtual std::string
    ToString() const
    {
        return IntegerValueToString(_value);
    }

    long 
    GetValue() const
    {
        return _value;
    }

    void 
    SetValue(long value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    long _value;

};


///////////////////////////////////////////////////////////////////////////////
//
// EvalBoolean.
//

class EvalBoolean : public EvalObject
{
public:

    EvalBoolean() 
    :   _value(false)
    {}

    EvalBoolean(bool value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalBoolean(*this);
    }

    virtual ~EvalBoolean()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_BOOLEAN;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "boolean";
    }

    virtual std::string
    ToString() const
    {
        return BooleanValueToString(_value);
    }

    bool
    GetValue() const
    {
        return _value;
    }

    void 
    SetValue(bool value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    bool _value;

};

   
///////////////////////////////////////////////////////////////////////////////
//
// EvalString.
//

class EvalString : public EvalObject
{
public:

    EvalString() 
    :   _value("")
    {}

    EvalString(const std::string& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalString(*this);
    }

    virtual ~EvalString()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_STRING;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "string";
    }

    virtual std::string
    ToString() const
    {
        return StringValueToString(_value);
    }

    const std::string& 
    GetValue() const
    {
        return _value;
    }

    void 
    SetValue(const std::string& value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    std::string _value;

};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Arrays.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// EvalByteArray.
//

class EvalByteArray : public EvalObject
{
public:

    EvalByteArray() 
    {}

    EvalByteArray(const std::vector<unsigned char>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalByteArray(*this);
    }

    virtual ~EvalByteArray()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_BYTE_ARRAY;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "byteArray";
    }

    virtual std::string
    ToString() const
    {
        return ByteArrayValueToString(_value);
    }

    const std::vector<unsigned char>&
    GetValue() const
    {
        return _value;
    }

    std::vector<unsigned char>&
    GetValue()
    {
        return _value;
    }

    void 
    SetValue(const std::vector<unsigned char>& value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    std::vector<unsigned char> _value;

};

///////////////////////////////////////////////////////////////////////////////
//
// EvalIntegerArray.
//

class EvalIntegerArray : public EvalObject
{
public:

    EvalIntegerArray() 
    {}

    EvalIntegerArray(const std::vector<long>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalIntegerArray(*this);
    }

    virtual ~EvalIntegerArray()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_INTEGER_ARRAY;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "integerArray";
    }

    virtual std::string
    ToString() const
    {
        return IntegerArrayValueToString(_value);
    }

    const std::vector<long>&
    GetValue() const
    {
        return _value;
    }

    std::vector<long>&
    GetValue()
    {
        return _value;
    }

    void 
    SetValue(const std::vector<long>& value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    std::vector<long> _value;

};


///////////////////////////////////////////////////////////////////////////////
//
// EvalBooleanArray.
//

class EvalBooleanArray : public EvalObject
{
public:

    EvalBooleanArray() 
    :   _value(false)
    {}

    EvalBooleanArray(const std::vector<bool>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalBooleanArray(*this);
    }

    virtual ~EvalBooleanArray()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_BOOLEAN_ARRAY;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "booleanArray";
    }

    virtual std::string
    ToString() const
    {
        return BooleanArrayValueToString(_value);
    }

    const std::vector<bool>&
    GetValue() const
    {
        return _value;
    }

    std::vector<bool>&
    GetValue()
    {
        return _value;
    }

    void 
    SetValue(const std::vector<bool>& value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    std::vector<bool> _value;

};

   
///////////////////////////////////////////////////////////////////////////////
//
// EvalStringArray.
//

class EvalStringArray : public EvalObject
{
public:

    EvalStringArray() 
    {}

    EvalStringArray(const std::vector<std::string>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual EvalObject* 
    Clone() const
    { 
        return new EvalStringArray(*this);
    }

    virtual ~EvalStringArray()
    {
        // Nothing to do.
    }

    virtual int 
    GetType() const
    { 
        return TYPE_EVAL_STRING_ARRAY;
    }

    virtual std::string 
    GetTypeName() const
    {
        return "stringArray";
    }

    virtual std::string
    ToString() const
    {
        return StringArrayValueToString(_value);
    }

    const std::vector<std::string>& 
    GetValue() const
    {
        return _value;
    }

    std::vector<std::string>& 
    GetValue()
    {
        return _value;
    }

    void 
    SetValue(const std::vector<std::string>& value)
    { 
        _value = value;
    }

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationAdd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationSub(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMul(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationDiv(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationMod(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationLte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGt(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationGte(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationEq(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationNe(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationAnd(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    virtual EvalObject* OperationOr(
                Evaluator& evaluator, 
                const EvalObject& other) const;

    ///////////////////////////////////////////////////////

    virtual EvalObject* OperationNot(Evaluator& evaluator) const; 

    ///////////////////////////////////////////////////////

protected:

    std::vector<std::string> _value;

};


///////////////////////////////////////////////////////////////////////////////
//
// Evaluator.
//

class Evaluator
{
public:

    Evaluator()
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~Evaluator()
    {
        Clean();
    }

    size_t 
    GetCurrentLineNumber() const
    { 
        return _currentLineNumber;
    }

    size_t
    GetCurrentColumnNumber() const
    {
        return _currentColumnNumber;
    }

    void
    SetCurrentLineNumber(size_t currentLineNumber)
    {
        _currentLineNumber = currentLineNumber;
    }

    void
    SetCurrentColumnNumber(size_t currentColumnNumber)
    {
        _currentColumnNumber = currentColumnNumber;
    }

    size_t
    GetEvalStackSize() const
    {
        return _evalStack.size();
    }

    void
    Push(EvalObject* evalObject)
    {
        ITS_REQUIRE(evalObject != NULL);
        _evalStack.push(evalObject);
    }

    void
    Pop()
    {
        ITS_REQUIRE(GetEvalStackSize() > 0);
        _evalStack.pop();
    }

    EvalObject*
    Top() const
    {
        ITS_REQUIRE(GetEvalStackSize() > 0);
        return _evalStack.top();
    }

    void
    Clean()
    {
        while (_evalStack.size() > 0)
        {
            EvalObject* evalObject = _evalStack.top();
            _evalStack.pop();

            delete evalObject;
        }
    }

protected:

    size_t _currentLineNumber;
    size_t _currentColumnNumber;

    std::stack<EvalObject*> _evalStack;

};



#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_EVALUATOR_H_)
