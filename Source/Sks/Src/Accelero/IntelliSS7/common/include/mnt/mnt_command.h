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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:08  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:55  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:56  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:02  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:59  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.7  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.6  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.5  2001/08/09 20:10:37  hdivoux
// LOG: More port to Sun CC.
// LOG:
// LOG: Revision 1.4  2001/08/09 19:49:41  hdivoux
// LOG: More update for Sun CC.
// LOG:
// LOG: Revision 1.3  2001/08/09 19:45:19  hdivoux
// LOG: Correction in no multiple include.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:07:15  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_command.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $"

//
//
// mnt_command.h: MNT command.
//
//


#if !defined(_MNT_COMMAND_H_)
#define _MNT_COMMAND_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <mnt.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)

///////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

class Mnt;


///////////////////////////////////////////////////////////////////////////////
//
// ValueObject.
//
// Used to represent a Command value(s) of argument(s) and return value.
//

class ValueObject
{
public:

    ValueObject()
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueObject()
    {
        // Nothing to do.
    }

    // MUST be kept in sync with EvalObject::Type.
    enum Type
    {
        VALUE_TYPE_ANY              = 0,
        VALUE_TYPE_NONE             = 1,
        VALUE_TYPE_BYTE             = 2,
        VALUE_TYPE_INTEGER          = 3,
        VALUE_TYPE_BOOLEAN          = 4,
        VALUE_TYPE_STRING           = 5,
        VALUE_TYPE_BYTE_ARRAY       = 6,
        VALUE_TYPE_INTEGER_ARRAY    = 7,
        VALUE_TYPE_BOOLEAN_ARRAY    = 8,
        VALUE_TYPE_STRING_ARRAY     = 9
    };

    virtual Type GetType() const = 0;

    virtual std::string 
    GetTypeName() const
    { 
        return TypeToString(GetType());
    }

    virtual std::string ToString() const = 0;

    static std::string
    TypeToString(Type type)
    {
        switch (type)
        {
        case VALUE_TYPE_NONE:
            return "none";
        case VALUE_TYPE_ANY:
            return "any";
        case VALUE_TYPE_BYTE:
            return "byte";
        case VALUE_TYPE_INTEGER:
            return "integer";
        case VALUE_TYPE_BOOLEAN:
            return "boolean";
        case VALUE_TYPE_STRING:
            return "string";
        case VALUE_TYPE_BYTE_ARRAY:
            return "byte array";
        case VALUE_TYPE_INTEGER_ARRAY:
            return "integer array";
        case VALUE_TYPE_BOOLEAN_ARRAY:
            return "boolean array";
        case VALUE_TYPE_STRING_ARRAY:
            return "string array";

        default:
            return "unknown";
        }
    }


protected:

};




///////////////////////////////////////////////////////////////////////////////
//
// ValueNone.
//

class ValueNone : public ValueObject
{
public:

    ValueNone()
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueNone()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_NONE;
    }

    virtual std::string ToString() const;

protected:

    // Nothing.
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueByte.
//

class ValueByte : public ValueObject
{
public:

    ValueByte()
    :   _value(0)
    {}

    ValueByte(unsigned char value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueByte()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_BYTE;
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

    virtual std::string ToString() const;

protected:

    unsigned char _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueInteger.
//

class ValueInteger : public ValueObject
{
public:

    ValueInteger()
    :   _value(0)
    {}

    ValueInteger(long value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueInteger()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_INTEGER;
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

    virtual std::string ToString() const;

protected:

    long _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueBoolean.
//

class ValueBoolean : public ValueObject
{
public:

    ValueBoolean()
    :   _value(false)
    {}

    ValueBoolean(bool value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueBoolean()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_BOOLEAN;
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

    virtual std::string ToString() const;

protected:

    bool _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueString.
//

class ValueString : public ValueObject
{
public:

    ValueString()
    :   _value("")
    {}

    ValueString(const std::string& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueString()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_STRING;
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

    virtual std::string ToString() const;

protected:

    std::string _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueByteArray.
//

class ValueByteArray : public ValueObject
{
public:

    ValueByteArray()
    {}

    ValueByteArray(const std::vector<unsigned char>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueByteArray()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_BYTE_ARRAY;
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

    virtual std::string ToString() const;

protected:

    std::vector<unsigned char>  _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueIntegerArray.
//

class ValueIntegerArray : public ValueObject
{
public:

    ValueIntegerArray()
    {}

    ValueIntegerArray(const std::vector<long>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueIntegerArray()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_INTEGER_ARRAY;
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

    virtual std::string ToString() const;

protected:

    std::vector<long>  _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueBooleanArray.
//

class ValueBooleanArray : public ValueObject
{
public:

    ValueBooleanArray()
    {}

    ValueBooleanArray(const std::vector<bool>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueBooleanArray()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_BOOLEAN_ARRAY;
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

    virtual std::string ToString() const;

protected:

    std::vector<bool>  _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// ValueStringArray.
//

class ValueStringArray : public ValueObject
{
public:

    ValueStringArray()
    {}

    ValueStringArray(const std::vector<std::string>& value)
    :   _value(value)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~ValueStringArray()
    {
        // Nothing to do.
    }

    virtual Type
    GetType() const
    {
        return VALUE_TYPE_STRING_ARRAY;
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

    virtual std::string ToString() const;

protected:

    std::vector<std::string>  _value;
};


///////////////////////////////////////////////////////////////////////////////
//
// Command.
//

class Command
{
public:

    // Default constructor not ok (see private section).

    Command(const std::string& name, const std::string& group = "")
    :   _name(name),
        _group(group)
    {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual ~Command()
    {
        // Nothing to do.
    }

    const std::string&
    GetName() const
    {
        return _name;
    }

    const std::string&
    GetGroup() const
    {
        return _group;
    }

    ///////////////////////////////////////////////////////

    typedef ValueObject::Type ReturnType;

    virtual ReturnType GetReturnType() const = 0;

    ///////////////////////////////////////////////////////

    typedef std::vector<ValueObject::Type> ArgumentTypes;

    virtual ArgumentTypes GetArgumentTypes() const = 0;

    ///////////////////////////////////////////////////////

    typedef ValueObject* ReturnValue;
    typedef std::vector<ValueObject*> Arguments;

    virtual ReturnValue Execute(Mnt& mnt, Arguments& arguments) = 0;

    ///////////////////////////////////////////////////////

    virtual std::string GetDescription() const = 0;

    ///////////////////////////////////////////////////////

protected:

    std::string _name;
    std::string _group;
    std::string _description;

private:

    Command()
    :   _name(""),
        _group("")
    {}
};



///////////////////////////////////////////////////////////////////////////////
//
// MNT_DEFINE_COMMAND_CLASS. Macro to define command classes.
//
// Cannot be traced in by debuggers (macro).
//
// Using a template instead results in too much code bloat.
//
//

//
//  MP_ClassName => name of command class.
//  MP_CommandName => name of command.
//  MP_CommandGroup => name of command group ("" can be used by default).
//
//  MP = Macro Parameter.
//

#define MNT_DEFINE_COMMAND_CLASS(                                           \
                            MP_ClassName,                                   \
                            MP_CommandName,                                 \
                            MP_CommandGroup)                                \
                                                                            \
class MP_ClassName : public mnt::Command                                    \
{                                                                           \
public:                                                                     \
                                                                            \
    MP_ClassName()                                                          \
    :   mnt::Command(MP_CommandName, MP_CommandGroup)                       \
    {}                                                                      \
                                                                            \
    virtual ~MP_ClassName()                                                 \
    {}                                                                      \
                                                                            \
    virtual ReturnType GetReturnType() const;                               \
                                                                            \
    virtual ArgumentTypes GetArgumentTypes() const;                         \
                                                                            \
    virtual ReturnValue Execute(Mnt& mnt, Arguments& arguments);            \
                                                                            \
    virtual std::string GetDescription() const;                             \
                                                                            \
protected:                                                                  \
                                                                            \
}

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_COMMNAND_H_)
