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

#ident "$Id: test_mnt_main.cpp,v 1.1.1.1 2007-10-08 11:12:03 bsccs2 Exp $"

//
//
// Test and how to use sample for MNT.
//
//

#include <its++.h>

#include <iostream>

#include <its_statics.cpp>

#include <mnt_mnt.h>
#include <mnt_command.h>


using namespace std;
using namespace its;
using namespace mnt;


///////////////////////////////////////////////////////////////////////////////
//
// Definitions of additional commands.
//

MNT_DEFINE_COMMAND_CLASS(
                    CommandTestUpdateInteger,
                    "TestUpdateInteger",
                    "test-mnt");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTestReturnInteger,
                    "TestReturnInteger",
                    "test-mnt");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTestUpdateByteArray,
                    "TestUpdateByteArray",
                    "test-mnt");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTestReturnByteArray,
                    "TestReturnByteArray",
                    "test-mnt");



///////////////////////////////////////////////////////////////////////////////
//
// Entry point.
//

int 
main(int argc, const char** argv)
{
    cout << "Begin MNT test." << endl;

    Mnt mnt;

    // Insert additional commands.
    mnt.InsertCommand(new CommandTestUpdateInteger());
    mnt.InsertCommand(new CommandTestReturnInteger());
    mnt.InsertCommand(new CommandTestUpdateByteArray());
    mnt.InsertCommand(new CommandTestReturnByteArray());

    // Uncomment next line to always get parser debug on. 
    // mnt.GetOptions().SetParserDebugOn();

    int res = mnt.Run(argc, argv);

    cout << "End MNT test." << endl;

    return EXIT_SUCCESS;
}



///////////////////////////////////////////////////////////////////////////////
//
// Implementation of additional commands.
//

//
// TestUpdateInteger.
//

Command::ReturnType
CommandTestUpdateInteger::GetReturnType() const
{
    // Command has no return value.
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTestUpdateInteger::GetArgumentTypes() const
{
    // Command has one argument of type integer.
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTestUpdateInteger::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    // Command has one argument of type integer: retrieve it.
    ValueInteger* valueInteger = 
        static_cast<ValueInteger*>(arguments[0]);

    // Integer value is what has been passed as command argument in script.
    long integer = valueInteger->GetValue();

    // Update argument (add 1999 to what has been passed as command argument 
    // in script).
    valueInteger->SetValue(integer + 1999);
    
    // Command has no return value.
    return new ValueNone();
}

string
CommandTestUpdateInteger::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return  "Update unique integer argument (must be called with 'out'  \n"
            "specifier in script) by adding 1999 to argument.           \n"
            "                                                           \n"
            "<none> TestUpdateInteger(<integer>):                       \n"
            "                                                           \n"
            " -> Argument #0 (type integer):                            \n"
            "        Integer value to be updated.                       \n";
}


//
// TestReturnInteger.
//

Command::ReturnType
CommandTestReturnInteger::GetReturnType() const
{
    // Command has return value of type integer.
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTestReturnInteger::GetArgumentTypes() const
{
    // Command has no arguments.
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandTestReturnInteger::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    // Command has no arguments: nothing to retrieve.

    static long result = 0;

    result++; // Return 1 firt time called, 2 second time...

    return new ValueInteger(result);
}

string
CommandTestReturnInteger::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return  "Return integer of value 1 first time called, 2 second time \n"
            "called and so on...                                        \n"
            "                                                           \n"
            "<integer> TestReturnInteger():                             \n"
            "                                                           \n"
            " -> No arguments.                                          \n";
}

//
// TestUpdateByteArray.
//

Command::ReturnType
CommandTestUpdateByteArray::GetReturnType() const
{
    // Command has no return value.
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTestUpdateByteArray::GetArgumentTypes() const
{
    // Command has one argument of type byte array.
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTestUpdateByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    // Command has one argument of type byteArray: retrieve it.
    ValueByteArray* valueByteArray = 
        static_cast<ValueByteArray*>(arguments[0]);

    // Array of bytes value is what has been passed as command argument in 
    // script.
    vector<unsigned char> byteArray = valueByteArray->GetValue();

    // Update argument (add 0x01 to each element of array that has been passed
    // as command argument in script).
    for (size_t i = 0; i < byteArray.size(); i++)
    {
        byteArray[i] += 0x01;
    }

    valueByteArray->SetValue(byteArray);
    
    // Command has no return value.
    return new ValueNone();
}

string
CommandTestUpdateByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return  "Update unique array of bytes argument (must be called with \n"
            "'out' specifier in script) by adding 0x01 to each element  \n"
            "of array of bytes.                                         \n"
            "                                                           \n"
            "<none> TestUpdateByteArray(<byteArray>):                   \n"
            "                                                           \n"
            " -> Argument #0 (type byteArray):                          \n"
            "        Array of bytes value to be updated.                \n";
}


//
// TestReturnByteArray.
//

Command::ReturnType
CommandTestReturnByteArray::GetReturnType() const
{
    // Command has return value of type byteArray.
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTestReturnByteArray::GetArgumentTypes() const
{
    // Command has no arguments.
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandTestReturnByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    // Command has no arguments: nothing to retrieve.

    static unsigned char b = 0x01;

    b++;

    vector<unsigned char> result;

    for (size_t i = 0; i < 4; i++)
    {
        result.push_back(b);
    }

    return new ValueByteArray(result);
}

string
CommandTestReturnByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return  "Return array of bytes <<0x01, 0x01, 0x01, 0x01>> firt time \n"
            "called, <<0x02, 0x02, 0x02, 0x02>> second time called and  \n"
            "so on...                                                   \n"
            "                                                           \n"
            "<byteArray> TestReturnByteArray():                         \n"
            "                                                           \n"
            " -> No arguments.                                          \n";
}

