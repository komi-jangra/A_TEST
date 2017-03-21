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
// LOG: Revision 1.1.1.1  2007/10/04 13:23:59  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:55  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:34  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:41  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:39  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:34  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 1.3  2001/10/18 22:24:27  hdivoux
// LOG: Remove extra ident line.
// LOG:
// LOG: Revision 1.2  2001/10/18 22:13:59  hdivoux
// LOG: Update for working version (from PR5).
// LOG:
// LOG: Revision 1.1  2001/10/16 22:51:19  hdivoux
// LOG: Creation in new directory name.
// LOG:
// LOG: Revision 1.7  2001/10/12 22:30:12  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.6  2001/10/11 22:58:21  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.5  2001/10/11 15:27:49  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.4  2001/10/10 23:06:37  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.3  2001/10/09 22:32:42  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.2  2001/10/08 21:53:39  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.1  2001/10/05 22:34:25  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: test_tcap_mn_main.cpp,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $"


//
// TCAP Multi-Nodes Test Tool (MNT).
//
// Regression/performance/endurance testing for ITU/ANSI TCAP with DSM.
//

#include <its++.h>
#include <its_app.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_thread_pool.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_thread.h>
#include <its_worker.h>
#include <its_assertion.h>
#include <its_gen_disp.h>



#include <engine.h>

#include <mnt_mnt.h>
#include <mnt_command.h>

#if defined(CCITT)
#include <itu/tcap.h>
#else // !defined(CCITT)
#include <ansi/tcap.h>
#endif // defined(CCITT)


#if defined(ITSDLLAPI) && defined(WIN32)
#pragma warning(disable:4273)
#undef ITSDLLAPI
#define ITSDLLAPI
#endif
#include <its_statics.cpp>

#if defined(WIN32)
#define EXPORTFUNC   __declspec(dllexport)
#else // !defined(WIN32)
#define EXPORTFUNC
#endif // defined(WIN32)


using namespace std;
using namespace its;
using namespace mnt;




///////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

void PrintComponentCCITT(unsigned int dialogueId, TCAP_CPT* component);
void PrintDialogueCCITT(unsigned int dialogueId, TCAP_DLG* dialogue);
void PrintComponentANSI(unsigned int dialogueId, TCAP_CPT* component);
void PrintDialogueANSI(unsigned int dialogueId, TCAP_DLG* dialogue);
void PrintAddress(SCCP_ADDR* address, bool raw = false);

///////////////////////////////////////////////////////////////////////////////
//
// TcapMnt.
//

class TcapMnt : public Mnt
{
public:

    TcapMnt();

    ~TcapMnt();

    void 
    SetHandle(ITS_HANDLE handle)
    {
        _handle = handle;
    }

    ITS_HANDLE
    GetHandle() const
    {
        return _handle;
    }

protected:

    ITS_HANDLE _handle;
};



///////////////////////////////////////////////////////////////////////////////
//
// All TCAP related commands.
//

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapInitialize,
                    "TcapInitialize",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapTerminate,
                    "TcapTerminate",
                    "tcap");

#if defined(CCITT)

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapAssembleInvokeComponent,
                    "TcapAssembleInvokeComponent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapDisassembleInvokeComponent,
                    "TcapDisassembleInvokeComponent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapAssembleResultLastComponent,
                    "TcapAssembleResultLastComponent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapDisassembleResultLastComponent,
                    "TcapDisassembleResultLastComponent",
                    "tcap");

#endif // defined(CCITT)

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapInvokeIdToByteArray,
                    "TcapInvokeIdToByteArray",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapByteArrayToInvokeId,
                    "TcapByteArrayToInvokeId",
                    "tcap");

#if defined(CCITT)

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapLinkedIdToByteArray,
                    "TcapLinkedIdToByteArray",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapByteArrayToLinkedId,
                    "TcapByteArrayToLinkedId",
                    "tcap");

#endif // defined(CCITT)

#if defined(CCITT)

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapOperationToByteArray,
                    "TcapOperationToByteArray",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapByteArrayToOperation,
                    "TcapByteArrayToOperation",
                    "tcap");

#endif // defined(CCITT)

#if defined(CCITT)

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapAssembleBeginDialogue,
                    "TcapAssembleBeginDialogue",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapDisassembleBeginDialogue,
                    "TcapDisassembleBeginDialogue",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapAssembleEndDialogue,
                    "TcapAssembleEndDialogue",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapDisassembleEndDialogue,
                    "TcapDisassembleEndDialogue",
                    "tcap");

#endif // defined(CCITT)

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapPointCodeToByteArray,
                    "TcapPointCodeToByteArray",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapByteArrayToPointCode,
                    "TcapByteArrayToPointCode",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapSccpAddressToByteArray,
                    "TcapSccpAddressToByteArray",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapByteArrayToSccpAddress,
                    "TcapByteArrayToSccpAddress",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapQualityOfServiceToByteArray,
                    "TcapQualityOfServiceToByteArray",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapByteArrayToQualityOfService,
                    "TcapByteArrayToQualityOfService",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapPrintComponent,
                    "TcapPrintComponent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapPrintDialogue,
                    "TcapPrintDialogue",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapPrintAddress,
                    "TcapPrintAddress",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapAllocateDialogueId,
                    "TcapAllocateDialogueId",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapSendComponent,
                    "TcapSendComponent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapReceiveComponent,
                    "TcapReceiveComponent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapSendDialogue,
                    "TcapSendDialogue",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapReceiveDialogue,
                    "TcapReceiveDialogue",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapGetNextEvent,
                    "TcapGetNextEvent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapPeekNextEvent,
                    "TcapPeekNextEvent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapIsComponentEvent,
                    "TcapIsComponentEvent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapIsDialogueEvent,
                    "TcapIsDialogueEvent",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapGetComponentType,
                    "TcapGetComponentType",
                    "tcap");

MNT_DEFINE_COMMAND_CLASS(
                    CommandTcapGetDialogueType,
                    "TcapGetDialogueType",
                    "tcap");

///////////////////////////////////////////////////////////////////////////////
//
// TcapInitialize.
//

Command::ReturnType
CommandTcapInitialize::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapInitialize::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BOOLEAN);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapInitialize::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{   
    return new ValueNone();
}

string
CommandTcapInitialize::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command TcapInitialize.";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapTerminate.
//

Command::ReturnType
CommandTcapTerminate::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapTerminate::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandTcapTerminate::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    return new ValueNone();
}

string
CommandTcapTerminate::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command TcapTerminate.";
}

#if defined(CCITT)

///////////////////////////////////////////////////////////////////////////////
//
// TcapAssembleInvokeComponent.
//

Command::ReturnType
CommandTcapAssembleInvokeComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapAssembleInvokeComponent::GetArgumentTypes() const
{
    // Order of arguments: Operation Class, Invoke Id, Linked Id, Operation,
    // Parameters, Timeout.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);

    return argumentTypes;
}

Command::ReturnValue
CommandTcapAssembleInvokeComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueOperationClass = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueByteArray* 
        valueInvokeId = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueLinkedId = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueByteArray* 
        valueOperation = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    ValueByteArray* 
        valueParameters = 
            static_cast<ValueByteArray*>(
                arguments[4]);

    ValueInteger* 
        valueTimeout = 
            static_cast<ValueInteger*>(
                arguments[5]);

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    cpt.ptype = TCAP_PT_TC_INVOKE_CCITT;

    ITS_ASSERT(valueOperationClass->GetValue() >= 1 && 
        valueOperationClass->GetValue() <= 4);
    cpt.u.invoke.opClass = valueOperationClass->GetValue();

    ITS_ASSERT(valueInvokeId->GetValue().size() <= IV_SIZE);
    cpt.u.invoke.invoke_id.len = valueInvokeId->GetValue().size();
    memcpy(
        cpt.u.invoke.invoke_id.data,
        &valueInvokeId->GetValue()[0],
        valueInvokeId->GetValue().size());

    ITS_ASSERT(valueLinkedId->GetValue().size() <= IV_SIZE);
    cpt.u.invoke.linked_id.len = valueLinkedId->GetValue().size();
    memcpy(
        cpt.u.invoke.linked_id.data,
        &valueLinkedId->GetValue()[0],
        valueLinkedId->GetValue().size());

    ITS_ASSERT(valueOperation->GetValue().size() <= OP_SIZE);
    cpt.u.invoke.operation.len = valueInvokeId->GetValue().size();
    memcpy(
        cpt.u.invoke.operation.data,
        &valueOperation->GetValue()[0],
        valueOperation->GetValue().size());

    ITS_ASSERT(valueParameters->GetValue().size() <= PR_SIZE);
    cpt.u.invoke.param.len = valueParameters->GetValue().size();
    memcpy(
        cpt.u.invoke.param.data,
        &valueParameters->GetValue()[0],
        valueParameters->GetValue().size());

    ITS_ASSERT(valueTimeout->GetValue() >= 0 && 
        valueTimeout->GetValue() <= 409);
    cpt.u.invoke.timeout = valueTimeout->GetValue();

    unsigned char* arrayResult = (unsigned char*)&cpt;

    vector<unsigned char> 
        vectorResult(arrayResult, arrayResult + sizeof(TCAP_CPT));

    ValueByteArray* result = new ValueByteArray(vectorResult);

    return result;
}

string
CommandTcapAssembleInvokeComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Assemble an Invoke Component (into a byte array). Only the  \n"
           "parameters relevant to a request can be specified.          \n"
           "                                                            \n"
           "<byte array> TcapAssembleInvokeComponent(                   \n"
           "                            <integer>,                      \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <integer>):                     \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Operation Class (1, 2, 3 or 4).                     \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Invoke Id.                                          \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Linked Id.                                          \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        Operation.                                          \n"
           "                                                            \n"
           " -> Argument #4 (type byte array):                          \n"
           "        Parameters.                                         \n"
           "                                                            \n"
           " -> Argument #5 (integer):                                  \n"
           "        Timeout.                                            \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Assembled Invoke Component.                         \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapDisassembleInvokeComponent.
//

Command::ReturnType
CommandTcapDisassembleInvokeComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapDisassembleInvokeComponent::GetArgumentTypes() const
{
    // Order of arguments: Invoke Component, Operation Class (out),
    // InvokeId (out), LinkedId (out), Operation (out), Parameters (out),
    // Last Component (out).

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BOOLEAN);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapDisassembleInvokeComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueComponent =
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueInteger* 
        valueOperationClass = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueByteArray* 
        valueInvokeId = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueByteArray* 
        valueLinkedId = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    ValueByteArray* 
        valueOperation = 
            static_cast<ValueByteArray*>(
                arguments[4]);

    ValueByteArray* 
        valueParameters = 
            static_cast<ValueByteArray*>(
                arguments[5]);

    ValueBoolean*
        valueLastComponent =
            static_cast<ValueBoolean*>(
                arguments[6]);

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    ITS_ASSERT(valueComponent->GetValue().size() == sizeof(TCAP_CPT));

    memcpy(&cpt, &valueComponent->GetValue()[0], sizeof(TCAP_CPT));

    ITS_ASSERT(cpt.ptype == TCAP_PT_TC_INVOKE_CCITT);

    if (cpt.u.invoke.opClass != 0)
    {
        ITS_ASSERT(
            cpt.u.invoke.opClass == 1 ||
            cpt.u.invoke.opClass == 2 ||
            cpt.u.invoke.opClass == 3 ||
            cpt.u.invoke.opClass == 4);

        valueOperationClass->SetValue(cpt.u.invoke.opClass);
    }

    if (cpt.u.invoke.invoke_id.len != 0)
    {
        ITS_ASSERT(cpt.u.invoke.invoke_id.len <= IV_SIZE);

        vector<unsigned char> array(
            &cpt.u.invoke.invoke_id.data[0],
            &cpt.u.invoke.invoke_id.data[0] + 
            cpt.u.invoke.invoke_id.len);

        valueInvokeId->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueInvokeId->SetValue(array);
    }

    if (cpt.u.invoke.linked_id.len != 0)
    {
        ITS_ASSERT(cpt.u.invoke.linked_id.len <= IV_SIZE);

        vector<unsigned char> array(
            &cpt.u.invoke.linked_id.data[0],
            &cpt.u.invoke.linked_id.data[0] + 
            cpt.u.invoke.linked_id.len);

        valueInvokeId->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueLinkedId->SetValue(array);
    }

    if (cpt.u.invoke.operation.len != 0)
    {
        ITS_ASSERT(cpt.u.invoke.operation.len <= OP_SIZE);

        vector<unsigned char> array(
            &cpt.u.invoke.operation.data[0],
            &cpt.u.invoke.operation.data[0] + 
            cpt.u.invoke.operation.len);

        valueOperation->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueOperation->SetValue(array);
    }

    if (cpt.u.invoke.param.len != 0)
    {
        ITS_ASSERT(cpt.u.invoke.param.len <= PR_SIZE);

        vector<unsigned char> array(
            &cpt.u.invoke.param.data[0],
            &cpt.u.invoke.param.data[0] + 
            cpt.u.invoke.param.len);

        valueParameters->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueParameters->SetValue(array);
    }

    valueLastComponent->SetValue(cpt.last_component ? true : false);

    return new ValueNone();
}

string
CommandTcapDisassembleInvokeComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Disassemble an Invoke Component (from a byte array). Only   \n"
           "the operation class and the parameters relevant to an       \n"
           "indication can be retrieved.                                \n"
           "                                                            \n"
           "<none> TcapDisassembleInvokeComponent(                      \n"
           "                            <byte array>,                   \n"
           "                            <integer>,                      \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <boolean>):                     \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Invoke Component.                                   \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Operation Class (out).                              \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Invoke Id (out).                                    \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        Linked Id (out).                                    \n"
           "                                                            \n"
           " -> Argument #4 (type byte array):                          \n"
           "        Operation (out).                                    \n"
           "                                                            \n"
           " -> Argument #5 (type byte array):                          \n"
           "        Parameters (out).                                   \n"
           "                                                            \n"
           " -> Argument #6 (type boolean):                             \n"
           "        Last Component (out).                               \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapAssembleResultLastComponent.
//

Command::ReturnType
CommandTcapAssembleResultLastComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapAssembleResultLastComponent::GetArgumentTypes() const
{
    // Order of arguments: Invoke Id, Operation, Parameters.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);

    return argumentTypes;
}

Command::ReturnValue
CommandTcapAssembleResultLastComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueInvokeId = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueByteArray* 
        valueOperation = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueParameters = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    cpt.ptype = TCAP_PT_TC_RESULT_L_CCITT;

    ITS_ASSERT(valueInvokeId->GetValue().size() <= IV_SIZE);
    cpt.u.result.invoke_id.len = valueInvokeId->GetValue().size();
    memcpy(
        cpt.u.result.invoke_id.data,
        &valueInvokeId->GetValue()[0],
        valueInvokeId->GetValue().size());

    ITS_ASSERT(valueOperation->GetValue().size() <= OP_SIZE);
    cpt.u.result.operation.len = valueOperation->GetValue().size();
    memcpy(
        cpt.u.result.operation.data,
        &valueOperation->GetValue()[0],
        valueOperation->GetValue().size());

    ITS_ASSERT(valueParameters->GetValue().size() <= PR_SIZE);
    cpt.u.result.param.len = valueParameters->GetValue().size();
    memcpy(
        cpt.u.result.param.data,
        &valueParameters->GetValue()[0],
        valueParameters->GetValue().size());

    unsigned char* arrayResult = (unsigned char*)&cpt;

    vector<unsigned char> 
        vectorResult(arrayResult, arrayResult + sizeof(TCAP_CPT));

    ValueByteArray* result = new ValueByteArray(vectorResult);

    return result;
}

string
CommandTcapAssembleResultLastComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Assemble a Result Last Component (into a byte array). Only  \n"
           "the parameters relevant to a request can be specified.      \n"
           "                                                            \n"
           "<byte array> TcapAssembleResultLastComponent(               \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>):                  \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Invoke Id.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Operation.                                          \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Parameters.                                         \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Assembled Result Last Component.                    \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapDisassembleResultLastComponent.
//

Command::ReturnType
CommandTcapDisassembleResultLastComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapDisassembleResultLastComponent::GetArgumentTypes() const
{
    // Order of arguments: Result Last Component, InvokeId (out), 
    // Operation (out), Parameters (out), Last Component (out).

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BOOLEAN);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapDisassembleResultLastComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueComponent =
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueByteArray* 
        valueInvokeId = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueOperation = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueByteArray* 
        valueParameters = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    ValueBoolean*
        valueLastComponent =
            static_cast<ValueBoolean*>(
                arguments[4]);

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    ITS_ASSERT(valueComponent->GetValue().size() == sizeof(TCAP_CPT));

    memcpy(&cpt, &valueComponent->GetValue()[0], sizeof(TCAP_CPT));

    ITS_ASSERT(cpt.ptype == TCAP_PT_TC_RESULT_L_CCITT);

    if (cpt.u.result.invoke_id.len != 0)
    {
        ITS_ASSERT(cpt.u.result.invoke_id.len <= IV_SIZE);

        vector<unsigned char> array(
            &cpt.u.result.invoke_id.data[0],
            &cpt.u.result.invoke_id.data[0] + 
            cpt.u.result.invoke_id.len);

        valueInvokeId->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueInvokeId->SetValue(array);
    }

    if (cpt.u.result.operation.len != 0)
    {
        ITS_ASSERT(cpt.u.result.operation.len <= OP_SIZE);

        vector<unsigned char> array(
            &cpt.u.result.operation.data[0],
            &cpt.u.result.operation.data[0] + 
            cpt.u.result.operation.len);

        valueOperation->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueOperation->SetValue(array);
    }

    if (cpt.u.result.param.len != 0)
    {
        ITS_ASSERT(cpt.u.result.param.len <= PR_SIZE);

        vector<unsigned char> array(
            &cpt.u.result.param.data[0],
            &cpt.u.result.param.data[0] + 
            cpt.u.result.param.len);

        valueParameters->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueParameters->SetValue(array);
    }

    valueLastComponent->SetValue(cpt.last_component ? true : false);

    return new ValueNone();
}

string
CommandTcapDisassembleResultLastComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Disassemble a Result Last Component (from a byte array).    \n"
           "Only the parameters relevant to an indication can be        \n"
           "retrieved.                                                  \n"
           "                                                            \n"
           "<none> TcapDisassembleResultLastComponent(                  \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <boolean>):                     \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Result Last Component.                              \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Invoke Id (out).                                    \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Operation (out).                                    \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        Parameters (out).                                   \n"
           "                                                            \n"
           " -> Argument #4 (type boolean):                             \n"
           "        Last Component (out).                               \n";
}

#endif // defined(CCITT)

///////////////////////////////////////////////////////////////////////////////
//
// TcapInvokeIdToByteArray.
//

Command::ReturnType
CommandTcapInvokeIdToByteArray::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapInvokeIdToByteArray::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapInvokeIdToByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ITS_ASSERT(valueInteger->GetValue() > 0 && valueInteger->GetValue() < 255);

    ValueByteArray* result = new ValueByteArray();

#if defined(CCITT)
    result->GetValue().push_back(TCAP_PN_INVOKE_TAG_CCITT);
#else // !defined(CCITT)
    result->GetValue().push_back(TCAP_PN_INVOKE_TAG_ANSI);
#endif // defined(CCITT)
    result->GetValue().push_back(1);
    result->GetValue().push_back(valueInteger->GetValue());
   
    return result;
}

string
CommandTcapInvokeIdToByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert an Invoke Id (as integer) to a byte array.          \n"
           "                                                            \n"
           "<byte array> TcapInvokeIdToByteArray(<integer>):            \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Invoke Id.                                          \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Byte array representing an Invoke Id for suitable   \n"
           "        commands.                                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapByteArrayToInvokeId.
//

Command::ReturnType
CommandTcapByteArrayToInvokeId::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapByteArrayToInvokeId::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapByteArrayToInvokeId::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ITS_ASSERT(valueByteArray->GetValue().size() == 3);

#if defined(CCITT)
    ITS_ASSERT(valueByteArray->GetValue()[0] == TCAP_PN_INVOKE_TAG_CCITT);
#else // !defined(CCITT)
    ITS_ASSERT(valueByteArray->GetValue()[0] == TCAP_PN_INVOKE_TAG_ANSI);
#endif // defined(CCITT)

    ITS_ASSERT(valueByteArray->GetValue()[1] == 1);

    ValueInteger* result = new ValueInteger();

    result->SetValue(valueByteArray->GetValue()[2]);
   
    return result;
}

string
CommandTcapByteArrayToInvokeId::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a byte array to an Invoke Id (as integer).          \n"
           "                                                            \n"
           "<integer> TcapByteArrayToInvokeId(<byte array>):            \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Byte array representing an Invoke Id from suitable  \n"
           "        commands.                                           \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Invoke Id.                                          \n";
}

#if defined(CCITT)

///////////////////////////////////////////////////////////////////////////////
//
// TcapLinkedIdToByteArray.
//

Command::ReturnType
CommandTcapLinkedIdToByteArray::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapLinkedIdToByteArray::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapLinkedIdToByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ITS_ASSERT(valueInteger->GetValue() > 0 && valueInteger->GetValue() < 255);

    ValueByteArray* result = new ValueByteArray();

    result->GetValue().push_back(TCAP_PN_INVOKE_TAG_CCITT);
    result->GetValue().push_back(1);
    result->GetValue().push_back(valueInteger->GetValue());
   
    return result;
}

string
CommandTcapLinkedIdToByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a Linked Id (as integer) to a byte array.           \n"
           "                                                            \n"
           "<byte array> TcapLinkedIdToByteArray(<integer>):            \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Linked Id.                                          \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Byte array representing a Linked Id for suitable    \n"
           "        commands.                                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapByteArrayToLinkedId.
//

Command::ReturnType
CommandTcapByteArrayToLinkedId::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapByteArrayToLinkedId::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapByteArrayToLinkedId::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ITS_ASSERT(valueByteArray->GetValue().size() == 3);

    ITS_ASSERT(valueByteArray->GetValue()[0] == TCAP_PN_INVOKE_TAG_CCITT);

    ITS_ASSERT(valueByteArray->GetValue()[1] == 1);

    ValueInteger* result = new ValueInteger();

    result->SetValue(valueByteArray->GetValue()[2]);
   
    return result;
}

string
CommandTcapByteArrayToLinkedId::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a byte array to a Linked Id (as integer).           \n"
           "                                                            \n"
           "<integer> TcapByteArrayToLinkedId(<byte array>):            \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Byte array representing a Linked Id from suitable   \n"
           "        commands.                                           \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Linked Id.                                          \n";
}

#endif // defined(CCITT)

#if defined(CCITT)

///////////////////////////////////////////////////////////////////////////////
//
// TcapOperationToByteArray.
//

Command::ReturnType
CommandTcapOperationToByteArray::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapOperationToByteArray::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapOperationToByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ITS_LONG code = valueInteger->GetValue();

    int opSize = sizeof(ITS_LONG);

    if (code < 0)
    {
        while (opSize > 1 &&
               ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
        {
            opSize--;
        }
    }
    else if (code > 0)
    {
        while (opSize > 1 &&
               ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
        {
            opSize--;
        }
    }
    else
    {
        opSize = 1;
    }

    vector<unsigned char> array;

    array.push_back(TCAP_PN_LOCAL_OP_TAG_CCITT);
    array.push_back(opSize);

    for (int i = opSize; i > 0; i--)
    {
        array.push_back((code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF);
    }

    ITS_ASSERT(array.size() == opSize + 2);

    ValueByteArray* result = new ValueByteArray();

    result->SetValue(array);
   
    return result;
}

string
CommandTcapOperationToByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert an Operation (as integer) to a byte array.          \n"
           "                                                            \n"
           "<byte array> TcapOperationToByteArray(<integer>):           \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Operation.                                          \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Byte array representing an Operation for suitable   \n"
           "        commands.                                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapByteArrayToOperation.
//

Command::ReturnType
CommandTcapByteArrayToOperation::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapByteArrayToOperation::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapByteArrayToOperation::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ITS_ASSERT(valueByteArray->GetValue().size() <= 2 + sizeof(ITS_LONG));

    ITS_ASSERT(valueByteArray->GetValue()[0] == TCAP_PN_LOCAL_OP_TAG_CCITT);

    ITS_ASSERT(valueByteArray->GetValue().size() - 2 == 
        valueByteArray->GetValue()[1]);

    int opSize = valueByteArray->GetValue()[1];

    ITS_LONG code = 0;

    if (valueByteArray->GetValue()[1] & 0x80U)
    {
        code = -1;
    }
    else
    {
        code = 0;
    }

    for (int i = opSize; i > 0; i--)
    {
        code |=
            ((ITS_LONG)(valueByteArray->GetValue()[2 + opSize - i]) & 0x0FF)
             << ((i - 1) * ITS_BITS_PER_BYTE);
    }

    ValueInteger* result = new ValueInteger();

    result->SetValue(code);
   
    return result;
}

string
CommandTcapByteArrayToOperation::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a byte array to an Operation (as integer).          \n"
           "                                                            \n"
           "<integer> TcapByteArrayToOperation(<byte array>):           \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Byte array representing an Operation from suitable  \n"
           "        commands.                                           \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Operation.                                          \n";
}

#endif // defined(CCITT)

#if defined(CCITT)

///////////////////////////////////////////////////////////////////////////////
//
// TcapAssembleBeginDialogue.
//

Command::ReturnType
CommandTcapAssembleBeginDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapAssembleBeginDialogue::GetArgumentTypes() const
{
    // Order of arguments: Quality of Service, Application Context Name,
    // User Information, Origination Address, Destination Address, Origination
    // Point code, Destination Point Code.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapAssembleBeginDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueQualityOfService = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueByteArray* 
        valueApplicationContextName = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueUserInformation = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueByteArray* 
        valueOriginationAddress = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    ValueByteArray* 
        valueDestinationAddress = 
            static_cast<ValueByteArray*>(
                arguments[4]);

    ValueByteArray* 
        valueOriginationPointCode = 
            static_cast<ValueByteArray*>(
                arguments[5]);

    ValueByteArray* 
        valueDestinationPointCode = 
            static_cast<ValueByteArray*>(
                arguments[6]);

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    dlg.ptype = TCAP_PT_TC_BEGIN_CCITT;

    if (valueQualityOfService->GetValue().size() != 0)
    {
        ITS_ASSERT(valueQualityOfService->GetValue().size() == 3);

        dlg.u.begin.qos.indicator = valueQualityOfService->GetValue()[0];
        dlg.u.begin.qos.sls_key = valueQualityOfService->GetValue()[1];
        dlg.u.begin.qos.priority = valueQualityOfService->GetValue()[2];
    }

    ITS_ASSERT(valueApplicationContextName->GetValue().size() <= AC_SIZE);
    dlg.u.begin.ac_name.len = valueApplicationContextName->GetValue().size();
    memcpy(
        dlg.u.begin.ac_name.data,
        &valueApplicationContextName->GetValue()[0],
        valueApplicationContextName->GetValue().size());

    ITS_ASSERT(valueUserInformation->GetValue().size() <= UI_SIZE);
    dlg.u.begin.user_info.len = valueUserInformation->GetValue().size();
    memcpy(
        dlg.u.begin.user_info.data,
        &valueUserInformation->GetValue()[0],
        valueUserInformation->GetValue().size());

    ITS_ASSERT(valueOriginationAddress->GetValue().size() <= 
        SCCP_MAX_ADDR_LEN);
    dlg.u.begin.orig_addr.len = valueOriginationAddress->GetValue().size();
    memcpy(
        dlg.u.begin.orig_addr.data,
        &valueOriginationAddress->GetValue()[0],
        valueOriginationAddress->GetValue().size());

    ITS_ASSERT(valueDestinationAddress->GetValue().size() <= 
        SCCP_MAX_ADDR_LEN);
    dlg.u.begin.dest_addr.len = valueDestinationAddress->GetValue().size();
    memcpy(
        dlg.u.begin.dest_addr.data,
        &valueDestinationAddress->GetValue()[0],
        valueDestinationAddress->GetValue().size());

    if (valueOriginationPointCode->GetValue().size() != 0)
    {
        ITS_ASSERT(valueOriginationPointCode->GetValue().size() == 2);
        memcpy(
            dlg.u.begin.opc.data,
            &valueOriginationPointCode->GetValue()[0],
            valueOriginationPointCode->GetValue().size());
    }

    if (valueDestinationPointCode->GetValue().size() != 0)
    {
        ITS_ASSERT(valueDestinationPointCode->GetValue().size() == 2);
        memcpy(
            dlg.u.begin.dpc.data,
            &valueDestinationPointCode->GetValue()[0],
            valueDestinationPointCode->GetValue().size());
    }

    unsigned char* arrayResult = (unsigned char*)&dlg;

    vector<unsigned char> 
        vectorResult(arrayResult, arrayResult + sizeof(TCAP_DLG));

    ValueByteArray* result = new ValueByteArray(vectorResult);

    return result;
}

string
CommandTcapAssembleBeginDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Assemble a Begin Dialogue (into a byte array). Only the     \n"
           "parameters relevant to a request can be specified.          \n"
           "                                                            \n"
           "<byte array> TcapAssembleBeginDialogue(                     \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>):                  \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Quality of Service.                                 \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Application Context Name.                           \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        User Information.                                   \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        Origination Address.                                \n"
           "                                                            \n"
           " -> Argument #4 (type byte array):                          \n"
           "        Destination Address.                                \n"
           "                                                            \n"
           " -> Argument #5 (type byte array):                          \n"
           "        Origination Point Code.                             \n"
           "                                                            \n"
           " -> Argument #6 (type byte array):                          \n"
           "        Destination Point Code.                             \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Assembled Begin Dialogue.                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapDisassembleBeginDialogue.
//

Command::ReturnType
CommandTcapDisassembleBeginDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapDisassembleBeginDialogue::GetArgumentTypes() const
{
    // Order of arguments: Begin Dialogue, Quality of Service, Application 
    // Context Name, User Information, Origination Address, Destination 
    // Address, Origination Point code, Destination Point Code, Component 
    // Present.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BOOLEAN);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapDisassembleBeginDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueDialogue =
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueByteArray* 
        valueQualityOfService = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueApplicationContextName = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueByteArray* 
        valueUserInformation = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    ValueByteArray* 
        valueOriginationAddress = 
            static_cast<ValueByteArray*>(
                arguments[4]);

    ValueByteArray* 
        valueDestinationAddress = 
            static_cast<ValueByteArray*>(
                arguments[5]);

    ValueByteArray* 
        valueOriginationPointCode = 
            static_cast<ValueByteArray*>(
                arguments[6]);

    ValueByteArray* 
        valueDestinationPointCode = 
            static_cast<ValueByteArray*>(
                arguments[7]);

    ValueBoolean*
        valueComponentPresent =
            static_cast<ValueBoolean*>(
                arguments[8]);

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    ITS_ASSERT(valueDialogue->GetValue().size() == sizeof(TCAP_DLG));

    memcpy(&dlg, &valueDialogue->GetValue()[0], sizeof(TCAP_DLG));

    ITS_ASSERT(dlg.ptype == TCAP_PT_TC_INVOKE_CCITT);

    {
        vector<unsigned char> array;
        array.push_back(dlg.u.begin.qos.indicator);
        array.push_back(dlg.u.begin.qos.sls_key);
        array.push_back(dlg.u.begin.qos.priority);

        valueQualityOfService->SetValue(array);
    }

    if (dlg.u.begin.ac_name.len != 0)
    {
        ITS_ASSERT(dlg.u.begin.ac_name.len <= AC_SIZE);

        vector<unsigned char> array(
            &dlg.u.begin.ac_name.data[0],
            &dlg.u.begin.ac_name.data[0] + 
            dlg.u.begin.ac_name.len);

        valueApplicationContextName->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueApplicationContextName->SetValue(array);
    }
        
    if (dlg.u.begin.user_info.len != 0)
    {
        ITS_ASSERT(dlg.u.begin.user_info.len <= UI_SIZE);

        vector<unsigned char> array(
            &dlg.u.begin.user_info.data[0],
            &dlg.u.begin.user_info.data[0] + 
            dlg.u.begin.user_info.len);

        valueUserInformation->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueUserInformation->SetValue(array);
    }

    if (dlg.u.begin.orig_addr.len != 0)
    {
        ITS_ASSERT(dlg.u.begin.orig_addr.len <= SCCP_MAX_ADDR_LEN);

        vector<unsigned char> array(
            &dlg.u.begin.orig_addr.data[0],
            &dlg.u.begin.orig_addr.data[0] + 
            dlg.u.begin.orig_addr.len);

        valueOriginationAddress->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueOriginationAddress->SetValue(array);
    }

    if (dlg.u.begin.dest_addr.len != 0)
    {
        ITS_ASSERT(dlg.u.begin.dest_addr.len <= SCCP_MAX_ADDR_LEN);

        vector<unsigned char> array(
            &dlg.u.begin.dest_addr.data[0],
            &dlg.u.begin.dest_addr.data[0] + 
            dlg.u.begin.dest_addr.len);

        valueDestinationAddress->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueDestinationAddress->SetValue(array);
    }

    {
        vector<unsigned char> array;
        array.push_back(dlg.u.begin.opc.data[0]);
        array.push_back(dlg.u.begin.opc.data[1]);

        valueOriginationPointCode->SetValue(array);
    }

    {
        vector<unsigned char> array;
        array.push_back(dlg.u.begin.dpc.data[0]);
        array.push_back(dlg.u.begin.dpc.data[1]);

        valueDestinationPointCode->SetValue(array);
    }

    valueComponentPresent->SetValue(dlg.u.begin.cpt_present ? true : false);

    return new ValueNone();
}

string
CommandTcapDisassembleBeginDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Disassemble a Begin Dialogue (from a byte array). Only the  \n"
           "parameters relevant to an indication can be retrieved.      \n"
           "                                                            \n"
           "<none> TcapDisassembleBeginDialogue(                        \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <boolean>):                     \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Begin Dialogue.                                     \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Quality of Service (out).                           \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Application Context Name (out).                     \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        User Information (out).                             \n"
           "                                                            \n"
           " -> Argument #4 (type byte array):                          \n"
           "        Origination Address (out).                          \n"
           "                                                            \n"
           " -> Argument #5 (type byte array):                          \n"
           "        Destination Address (out).                          \n"
           "                                                            \n"
           " -> Argument #6 (type byte array):                          \n"
           "        Origination Point Code (out).                       \n"
           "                                                            \n"
           " -> Argument #7 (type byte array):                          \n"
           "        Destination Point Code (out).                       \n"
           "                                                            \n"
           " -> Argument #8 (type boolean):                             \n"
           "        Component Present (out).                            \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapAssembleEndDialogue.
//

Command::ReturnType
CommandTcapAssembleEndDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapAssembleEndDialogue::GetArgumentTypes() const
{
    // Order of arguments: Quality of Service, Application Context Name,
    // User Information, Termination.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BOOLEAN);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapAssembleEndDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueQualityOfService = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueByteArray* 
        valueApplicationContextName = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueUserInformation = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueBoolean* 
        valueTermination = 
            static_cast<ValueBoolean*>(
                arguments[3]);

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    dlg.ptype = TCAP_PT_TC_END_CCITT;

    if (valueQualityOfService->GetValue().size() != 0)
    {
        ITS_ASSERT(valueQualityOfService->GetValue().size() == 3);

        dlg.u.end.qos.indicator = valueQualityOfService->GetValue()[0];
        dlg.u.end.qos.sls_key = valueQualityOfService->GetValue()[1];
        dlg.u.end.qos.priority = valueQualityOfService->GetValue()[2];
    }

    ITS_ASSERT(valueApplicationContextName->GetValue().size() <= AC_SIZE);
    dlg.u.end.ac_name.len = valueApplicationContextName->GetValue().size();
    memcpy(
        dlg.u.end.ac_name.data,
        &valueApplicationContextName->GetValue()[0],
        valueApplicationContextName->GetValue().size());

    ITS_ASSERT(valueUserInformation->GetValue().size() <= UI_SIZE);
    dlg.u.end.user_info.len = valueUserInformation->GetValue().size();
    memcpy(
        dlg.u.end.user_info.data,
        &valueUserInformation->GetValue()[0],
        valueUserInformation->GetValue().size());

    dlg.u.end.termination = (valueTermination->GetValue() ? 1 : 0);

    unsigned char* arrayResult = (unsigned char*)&dlg;

    vector<unsigned char> 
        vectorResult(arrayResult, arrayResult + sizeof(TCAP_DLG));

    ValueByteArray* result = new ValueByteArray(vectorResult);

    return result;
}

string
CommandTcapAssembleEndDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Assemble an End Dialogue (into a byte array). Only the      \n"
           "parameters relevant to a request can be specified.          \n"
           "                                                            \n"
           "<byte array> TcapAssembleEndDialogue(                       \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <boolean>):                     \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Quality of Service.                                 \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Application Context Name.                           \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        User Information.                                   \n"
           "                                                            \n"
           " -> Argument #3 (type boolean):                             \n"
           "        Termination.                                        \n"
           "                                                            \n"           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Assembled End Dialogue.                             \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapDisassembleEndDialogue.
//

Command::ReturnType
CommandTcapDisassembleEndDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapDisassembleEndDialogue::GetArgumentTypes() const
{
    // Order of arguments: End Dialogue, Quality of Service, Application 
    // Context Name, User Information, Component Present.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BOOLEAN);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapDisassembleEndDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueDialogue =
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueByteArray* 
        valueQualityOfService = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    ValueByteArray* 
        valueApplicationContextName = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    ValueByteArray* 
        valueUserInformation = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    ValueBoolean*
        valueComponentPresent =
            static_cast<ValueBoolean*>(
                arguments[4]);

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    ITS_ASSERT(valueDialogue->GetValue().size() == sizeof(TCAP_DLG));

    memcpy(&dlg, &valueDialogue->GetValue()[0], sizeof(TCAP_DLG));

    ITS_ASSERT(dlg.ptype == TCAP_PT_TC_END_CCITT);

    {
        vector<unsigned char> array;
        array.push_back(dlg.u.end.qos.indicator);
        array.push_back(dlg.u.end.qos.sls_key);
        array.push_back(dlg.u.end.qos.priority);

        valueQualityOfService->SetValue(array);
    }

    if (dlg.u.end.ac_name.len != 0)
    {
        ITS_ASSERT(dlg.u.end.ac_name.len <= AC_SIZE);

        vector<unsigned char> array(
            &dlg.u.end.ac_name.data[0],
            &dlg.u.end.ac_name.data[0] + 
            dlg.u.end.ac_name.len);

        valueApplicationContextName->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueApplicationContextName->SetValue(array);
    }
        
    if (dlg.u.end.user_info.len != 0)
    {
        ITS_ASSERT(dlg.u.end.user_info.len <= UI_SIZE);

        vector<unsigned char> array(
            &dlg.u.end.user_info.data[0],
            &dlg.u.end.user_info.data[0] + 
            dlg.u.end.user_info.len);

        valueUserInformation->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueUserInformation->SetValue(array);
    }

    valueComponentPresent->SetValue(dlg.u.end.cpt_present ? true : false);

    return new ValueNone();
}

string
CommandTcapDisassembleEndDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Disassemble an End Dialogue (from a byte array). Only the   \n"
           "parameters relevant to an indication can be retrieved.      \n"
           "                                                            \n"
           "<none> TcapDisassembleEndDialogue(                          \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <byte array>,                   \n"
           "                            <boolean>):                     \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        End Dialogue.                                       \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Quality of Service (out).                           \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Application Context Name (out).                     \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        User Information (out).                             \n"
           "                                                            \n"
           " -> Argument #4 (type boolean):                             \n"
           "        Component Present (out).                            \n";
}

#endif // defined(CCITT)

///////////////////////////////////////////////////////////////////////////////
//
// TcapPointCodeToByteArray.
//

Command::ReturnType
CommandTcapPointCodeToByteArray::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapPointCodeToByteArray::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapPointCodeToByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueByteArray* result = new ValueByteArray();

    vector<unsigned char> array;

#if defined(CCITT)

    MTP3_POINT_CODE_CCITT pointCode;

    MTP3_PC_SET_VALUE_CCITT(pointCode, valueInteger->GetValue());

    array.push_back(pointCode.data[0]);
    array.push_back(pointCode.data[1]);

#else // !defined(CCITT)

    MTP3_POINT_CODE_ANSI pointCode;

    MTP3_PC_SET_VALUE_ANSI(pointCode, valueInteger->GetValue());

    array.push_back(pointCode.data[0]);
    array.push_back(pointCode.data[1]);
    array.push_back(pointCode.data[2]);

#endif // defined(CCITT)

    result->SetValue(array);

    return result;
}

string
CommandTcapPointCodeToByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a Point Code (as integer) to a byte array.          \n"
           "                                                            \n"
           "<byte array> TcapPointCodeToByteArray(<integer>):           \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Point Code.                                         \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Byte array representing a Point Code for suitable   \n"
           "        commands.                                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapByteArrayToPointCode.
//

Command::ReturnType
CommandTcapByteArrayToPointCode::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapByteArrayToPointCode::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapByteArrayToPointCode::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[0]);

#if defined(CCITT)

    ITS_ASSERT(valueByteArray->GetValue().size() == 2);

    MTP3_POINT_CODE_CCITT pointCode;

    pointCode.data[0] = valueByteArray->GetValue()[0];
    pointCode.data[1] = valueByteArray->GetValue()[1];

    long value = MTP3_PC_GET_VALUE_CCITT(pointCode);

#else // !defined(CCITT)

    ITS_ASSERT(valueByteArray->GetValue().size() == 3);

    MTP3_POINT_CODE_ANSI pointCode;

    pointCode.data[0] = valueByteArray->GetValue()[0];
    pointCode.data[1] = valueByteArray->GetValue()[1];
    pointCode.data[2] = valueByteArray->GetValue()[2];

    long value = MTP3_PC_GET_VALUE_CCITT(pointCode);

#endif // defined(CCITT)

    ValueInteger* result = new ValueInteger();

    result->SetValue(value);
   
    return result;
}

string
CommandTcapByteArrayToPointCode::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a byte array to a Point Code (as integer).          \n"
           "                                                            \n"
           "<integer> TcapByteArrayToPointCode(<byte array>):           \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Byte array representing a Point Code from suitable  \n"
           "        commands.                                           \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Point Code.                                         \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapSccpAddressToByteArray.
//

Command::ReturnType
CommandTcapSccpAddressToByteArray::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapSccpAddressToByteArray::GetArgumentTypes() const
{
    // Order of arguments: Address Indicator, Point Code, SSN, GTT Information.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapSccpAddressToByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueAddressIndicator = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger*
        valuePointCode = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger*
        valueSsn = 
            static_cast<ValueInteger*>(
                arguments[2]);

    ValueByteArray* 
        valueGttInformation = 
            static_cast<ValueByteArray*>(
                arguments[3]);

    SCCP_ADDR sccpAddress;
    memset(&sccpAddress, 0, sizeof(SCCP_ADDR));

#if defined(CCITT)

    int encodeResult = SCCP_EncodeAddr_CCITT(
                            &sccpAddress, 
                            valueAddressIndicator->GetValue(),
                            valuePointCode->GetValue(),
                            valueSsn->GetValue(),
                            &valueGttInformation->GetValue()[0],
                            valueGttInformation->GetValue().size());

#else // !defined(CCITT)

    int encodeResult = SCCP_EncodeAddr_ANSI(
                            &sccpAddress, 
                            valueAddressIndicator->GetValue(),
                            valuePointCode->GetValue(),
                            valueSsn->GetValue(),
                            &valueGttInformation->GetValue()[0],
                            valueGttInformation->GetValue().size());

#endif // defined(CCITT)

    ITS_ASSERT(encodeResult == ITS_SUCCESS);

    vector<unsigned char> array;

    for (size_t i = 0; i < sccpAddress.len; i++)
    {
        array.push_back(sccpAddress.data[i]);
    }

    ValueByteArray* result = new ValueByteArray();

    result->SetValue(array);

    return result;
}

string
CommandTcapSccpAddressToByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a SCCP Address to a byte array.                     \n"
           "                                                            \n"
           "<byte array> TcapSccpAddressToByteArray(                    \n"
           "                                    <integer>,              \n"
           "                                    <integer>,              \n"
           "                                    <integer>,              \n"
           "                                    <byte array>):          \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Address Indicator.                                  \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Point Code.                                         \n"
           "                                                            \n"
           " -> Argument #2 (type integer):                             \n"
           "        SSN.                                                \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        GTT Information.                                    \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Byte array representing a SCCP Address for suitable \n"
           "        commands.                                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapByteArrayToSccpAddress.
//

Command::ReturnType
CommandTcapByteArrayToSccpAddress::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapByteArrayToSccpAddress::GetArgumentTypes() const
{
    // Order of arguments: Sccp Address, Address Indicator, Point Code, SSN,
    // GTT Information.

    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapByteArrayToSccpAddress::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueSccpAddress = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueInteger*
        valueAddressIndicator = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger*
        valuePointCode = 
            static_cast<ValueInteger*>(
                arguments[2]);

    ValueInteger*
        valueSsn = 
            static_cast<ValueInteger*>(
                arguments[3]);

    ValueByteArray* 
        valueGttInformation = 
            static_cast<ValueByteArray*>(
                arguments[4]);

    SCCP_ADDR sccpAddress;
    memset(&sccpAddress, 0, sizeof(SCCP_ADDR));

    ITS_ASSERT(valueSccpAddress->GetValue().size() <= SCCP_MAX_ADDR_LEN);
    sccpAddress.len = valueSccpAddress->GetValue().size();
    memcpy(
        sccpAddress.data,
        &valueSccpAddress->GetValue()[0],
        valueSccpAddress->GetValue().size());

    ITS_OCTET addressIndicator;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_USHORT gttLen;
    ITS_OCTET gttInfo[SCCP_MAX_ADDR_LEN];

#if defined(CCITT)

    int decodeResult = SCCP_DecodeAddr_CCITT(
                            &sccpAddress, 
                            &addressIndicator,
                            &pointCode,
                            &ssn,
                            gttInfo,
                            &gttLen);

#else // !defined(CCITT)

    int decodeResult = SCCP_DecodeAddr_ANSI(
                            &sccpAddress, 
                            &addressIndicator,
                            &pointCode,
                            &ssn,
                            gttInfo,
                            &gttLen);

#endif // defined(CCITT)

    ITS_ASSERT(decodeResult == ITS_SUCCESS);

    valueAddressIndicator->SetValue(addressIndicator);

    valuePointCode->SetValue(pointCode);

    valueSsn->SetValue(ssn);

    vector<unsigned char> array;

    for (size_t i = 0; i < gttLen; i++)
    {
        array.push_back(gttInfo[i]);
    }

    ValueByteArray* result = new ValueByteArray();

    result->SetValue(array);

    return result;
}

string
CommandTcapByteArrayToSccpAddress::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a SCCP Address to a byte array.                     \n"
           "                                                            \n"
           "<none> TcapByteArrayToSccpAddress(                          \n"
           "                            <byte array>,                   \n"
           "                            <integer>,                      \n"
           "                            <integer>,                      \n"
           "                            <integer>,                      \n"
           "                            <byte array>):                  \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Sccp Address.                                       \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Point Code out).                                    \n"
           "                                                            \n"
           " -> Argument #2 (type integer):                             \n"
           "        SSN (out).                                          \n"
           "                                                            \n"
           " -> Argument #3 (type byte array):                          \n"
           "        GTT Information (out).                              \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapQualityOfServiceToByteArray.
//

Command::ReturnType
CommandTcapQualityOfServiceToByteArray::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BYTE_ARRAY;
}

Command::ArgumentTypes
CommandTcapQualityOfServiceToByteArray::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapQualityOfServiceToByteArray::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueIndicator = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger*
        valueSlsKey = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger*
        valuePriority = 
            static_cast<ValueInteger*>(
                arguments[2]);

    ValueByteArray* result = new ValueByteArray();

    vector<unsigned char> array;
    array.push_back(valueIndicator->GetValue());
    array.push_back(valueSlsKey->GetValue());
    array.push_back(valuePriority->GetValue());

    result->SetValue(array);

    return result;
}

string
CommandTcapQualityOfServiceToByteArray::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert Quality of Service to a byte array.                 \n"
           "                                                            \n"
           "<byte array> TcapQualityOfServiceToByteArray(               \n"
           "                                        <integer>,          \n"
           "                                        <integer>,          \n"
           "                                        <integer>):         \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        QOS Indicator.                                      \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        QOS SLS Key.                                        \n"
           "                                                            \n"
           " -> Argument #2 (type integer):                             \n"
           "        QOS Priority.                                       \n"
           "                                                            \n"
           " -> Return value (type byte array):                         \n"
           "        Byte array representing a Quality of Service for    \n"
           "        suitable commands.                                  \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapByteArrayToQualityOfService.
//

Command::ReturnType
CommandTcapByteArrayToQualityOfService::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapByteArrayToQualityOfService::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapByteArrayToQualityOfService::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueInteger*
        valueIndicator = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger*
        valueSlsKey = 
            static_cast<ValueInteger*>(
                arguments[2]);

    ValueInteger*
        valuePriority = 
            static_cast<ValueInteger*>(
                arguments[3]);

    ITS_ASSERT(valueByteArray->GetValue().size() == 3);

    valueIndicator->SetValue(valueByteArray->GetValue()[0]);
    valueSlsKey->SetValue(valueByteArray->GetValue()[1]);
    valuePriority->SetValue(valueByteArray->GetValue()[2]);

    return new ValueNone();
}

string
CommandTcapByteArrayToQualityOfService::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Convert a byte array to an Invoke Id (as integer).          \n"
           "                                                            \n"
           "<none> TcapByteArrayToQualityOfService(                     \n"
           "                                    <byte array>,           \n"
           "                                    <integer>,              \n"
           "                                    <integer>,              \n"
           "                                    <integer>):             \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Byte array representing a Quality of Service from   \n"
           "        suitable commands.                                  \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        QOS Indicator (out).                                \n"
           "                                                            \n"
           " -> Argument #2 (type integer):                             \n"
           "        QOS SLS Key (out).                                  \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        QOS Priority (out).                                 \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapPrintComponent.
//

Command::ReturnType
CommandTcapPrintComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapPrintComponent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapPrintComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    long dialogueId = valueInteger->GetValue();

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    ITS_ASSERT(valueByteArray->GetValue().size() == sizeof(TCAP_CPT));

    memcpy(&cpt, &valueByteArray->GetValue()[0], sizeof(TCAP_CPT));

#if defined(CCITT)

    PrintComponentCCITT(dialogueId, &cpt);

#else // !defined(CCITT)

    PrintComponentANSI(dialogueId, &cpt);

#endif // defined(CCITT)

    return new ValueNone();
}

string
CommandTcapPrintComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Print a Component (defined by a byte array).                \n"
           "                                                            \n"
           "<none> TcapPrintComponent(<integer>, <byte array>):         \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Dialogue Id.                                        \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Component.                                          \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapPrintDialogue.
//

Command::ReturnType
CommandTcapPrintDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapPrintDialogue::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapPrintDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    long dialogueId = valueInteger->GetValue();

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    ITS_ASSERT(valueByteArray->GetValue().size() == sizeof(TCAP_DLG));

    memcpy(&dlg, &valueByteArray->GetValue()[0], sizeof(TCAP_DLG));

#if defined(CCITT)

    PrintDialogueCCITT(dialogueId, &dlg);

#else // !defined(CCITT)

    PrintDialogueANSI(dialogueId, &dlg);

#endif // defined(CCITT)

    return new ValueNone();
}

string
CommandTcapPrintDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Print a Dialogue (defined by a byte array).                 \n"
           "                                                            \n"
           "<none> TcapPrintDialogue(<integer>, <byte array>):          \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Dialogue Id.                                        \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Dialogue.                                           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapPrintAddress.
//

Command::ReturnType
CommandTcapPrintAddress::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTcapPrintAddress::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapPrintAddress::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray*
        valueByteArray = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    SCCP_ADDR address;
    memset(&address, 0, sizeof(SCCP_ADDR));

    ITS_ASSERT(valueByteArray->GetValue().size() <= SCCP_MAX_ADDR_LEN);

    address.len = valueByteArray->GetValue().size();

    memcpy(
        address.data,
        &valueByteArray->GetValue()[0],
        valueByteArray->GetValue().size());

    PrintAddress(&address, false);

    return new ValueNone();
}

string
CommandTcapPrintAddress::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Print an Address (defined by a byte array).                 \n"
           "                                                            \n"
           "<none> TcapPrintAddress(<byte array>):                      \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Address.                                            \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapAllocateDialogueId.
//

Command::ReturnType
CommandTcapAllocateDialogueId::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapAllocateDialogueId::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapAllocateDialogueId::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueDialogueId = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ITS_USHORT dialogueId = 0;

#if defined(CCITT)

    int res = TCAP_AllocateDialogueId_CCITT(&dialogueId);

#else // !defined(CCITT)

    int res = TCAP_AllocateDialogueId_ANSI(&dialogueId);

#endif // defined(CCITT)

    valueDialogueId->SetValue(dialogueId);

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapAllocateDialogueId::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Allocate a Dialogue Id.                                     \n"
           "                                                            \n"
           "<integer> TcapAllocateDialogueId(<integer>):                \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Dialogue Id (out).                                  \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapSendComponent.
//

Command::ReturnType
CommandTcapSendComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapSendComponent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapSendComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueDialogueId = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueByteArray* 
        valueComponent = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    TcapMnt& tcapMnt = static_cast<TcapMnt&>(mnt);

    ITS_HANDLE handle = tcapMnt.GetHandle();

    ITS_USHORT dialogueId = valueDialogueId->GetValue();

    ITS_ASSERT(valueComponent->GetValue().size() == sizeof(TCAP_CPT));

    TCAP_CPT cpt;
    memcpy(&cpt, &valueComponent->GetValue()[0], sizeof(TCAP_CPT));

    ITS_HDR hdr;

    hdr.context.dialogue_id = dialogueId;

#if defined(CCITT)

    int res = TCAP_SendComponent_CCITT(handle, &hdr, &cpt);

#else // !defined(CCITT)

    int res = TCAP_SendComponent_ANSI(handle, &hdr, &cpt);

#endif // defined(CCITT)

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapSendComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Send a Component.                                           \n"
           "                                                            \n"
           "<integer> TcapSendComponent(<integer>, <byte array>):       \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Dialogue Id.                                        \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Component.                                          \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapReceiveComponent.
//

Command::ReturnType
CommandTcapReceiveComponent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapReceiveComponent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);

    return argumentTypes;
}

Command::ReturnValue
CommandTcapReceiveComponent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueEvent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueInteger* 
        valueDialogueId = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueByteArray* 
        valueComponent = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    TcapMnt& tcapMnt = static_cast<TcapMnt&>(mnt);

    ITS_HANDLE handle = tcapMnt.GetHandle();

    ITS_ASSERT(valueEvent->GetValue().size() >= 2);

    ITS_EVENT event;
    memset(&event, 0, sizeof(ITS_EVENT));

    unsigned char sourceMsb = valueEvent->GetValue()[0];
    unsigned char sourceLsb = valueEvent->GetValue()[1];

    event.src = sourceMsb << 8 | sourceLsb;
    event.len = valueEvent->GetValue().size() - 2;
    event.data = &valueEvent->GetValue()[2];

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    ITS_HDR hdr;
    memset(&hdr, 0, sizeof(ITS_HDR));

#if defined(CCITT)

    int res = TCAP_ReceiveComponent_CCITT(handle, &event, &hdr, &cpt);

#else // !defined(CCITT)

    int res = TCAP_ReceiveComponent_ANSI(handle, &event, &hdr, &cpt);

#endif // defined(CCITT)

    ITS_USHORT dialogueId = hdr.context.dialogue_id;

    valueDialogueId->SetValue(dialogueId);

    unsigned char* arrayCpt = (unsigned char*)&cpt;

    vector<unsigned char> array(arrayCpt, arrayCpt + sizeof(TCAP_CPT));

    valueComponent->SetValue(array);

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapReceiveComponent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Receive a Component (from an Event).                        \n"
           "                                                            \n"
           "<integer> TcapReceiveComponent(                             \n"
           "                            <byte array>,                   \n"
           "                            <integer>,                      \n"
           "                            <byte array>):                  \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Event.                                              \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Dialogue Id (out).                                  \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Component (out).                                    \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapSendDialogue.
//

Command::ReturnType
CommandTcapSendDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapSendDialogue::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapSendDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueDialogueId = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueByteArray* 
        valueDialogue = 
            static_cast<ValueByteArray*>(
                arguments[1]);

    TcapMnt& tcapMnt = static_cast<TcapMnt&>(mnt);

    ITS_HANDLE handle = tcapMnt.GetHandle();

    ITS_USHORT dialogueId = valueDialogueId->GetValue();

    ITS_ASSERT(valueDialogue->GetValue().size() == sizeof(TCAP_DLG));

    TCAP_DLG dlg;
    memcpy(&dlg, &valueDialogue->GetValue()[0], sizeof(TCAP_DLG));

    ITS_HDR hdr;

    hdr.context.dialogue_id = dialogueId;

#if defined(CCITT)

    int res = TCAP_SendDialogue_CCITT(handle, &hdr, &dlg);

#else // !defined(CCITT)

    int res = TCAP_SendDialogue_ANSI(handle, &hdr, &dlg);

#endif // defined(CCITT)

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapSendDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Send a Dialogue.                                            \n"
           "                                                            \n"
           "<integer> TcapSendDialogue(<integer>, <byte array>):        \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        Dialogue Id.                                        \n"
           "                                                            \n"
           " -> Argument #1 (type byte array):                          \n"
           "        Dialogue.                                           \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapReceiveDialogue.
//

Command::ReturnType
CommandTcapReceiveDialogue::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapReceiveDialogue::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);

    return argumentTypes;
}

Command::ReturnValue
CommandTcapReceiveDialogue::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueEvent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ValueInteger* 
        valueDialogueId = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueByteArray* 
        valueDialogue = 
            static_cast<ValueByteArray*>(
                arguments[2]);

    TcapMnt& tcapMnt = static_cast<TcapMnt&>(mnt);

    ITS_HANDLE handle = tcapMnt.GetHandle();

    ITS_ASSERT(valueEvent->GetValue().size() >= 2);

    ITS_EVENT event;
    memset(&event, 0, sizeof(ITS_EVENT));

    unsigned char sourceMsb = valueEvent->GetValue()[0];
    unsigned char sourceLsb = valueEvent->GetValue()[1];

    event.src = sourceMsb << 8 | sourceLsb;
    event.len = valueEvent->GetValue().size() - 2;
    event.data = &valueEvent->GetValue()[2];

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    ITS_HDR hdr;
    memset(&hdr, 0, sizeof(ITS_HDR));

#if defined(CCITT)

    int res = TCAP_ReceiveDialogue_CCITT(handle, &event, &hdr, &dlg);

#else // !defined(CCITT)

    int res = TCAP_ReceiveDialogue_ANSI(handle, &event, &hdr, &dlg);

#endif // defined(CCITT)

    ITS_USHORT dialogueId = hdr.context.dialogue_id;

    valueDialogueId->SetValue(dialogueId);

    unsigned char* arrayDlg = (unsigned char*)&dlg;

    vector<unsigned char> array(arrayDlg, arrayDlg + sizeof(TCAP_DLG));

    valueDialogue->SetValue(array);

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapReceiveDialogue::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Receive a Dialogue (from an Event).                         \n"
           "                                                            \n"
           "<integer> TcapReceiveDialogue(                              \n"
           "                            <byte array>,                   \n"
           "                            <integer>,                      \n"
           "                            <byte array>):                  \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Event.                                              \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Dialogue Id (out).                                  \n"
           "                                                            \n"
           " -> Argument #2 (type byte array):                          \n"
           "        Dialogue (out).                                     \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapGetNextEvent.
//

Command::ReturnType
CommandTcapGetNextEvent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapGetNextEvent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapGetNextEvent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueEvent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    TcapMnt& tcapMnt = static_cast<TcapMnt&>(mnt);

    ITS_HANDLE handle = tcapMnt.GetHandle();

    ITS_EVENT event;
    memset(&event, 0, sizeof(ITS_EVENT));

    int res = ITS_GetNextEvent(handle, &event);

    if (res == ITS_SUCCESS)
    {
        vector<unsigned char> array;

        array.reserve(event.len + 2);

        array.push_back(event.src >> 8 & 0x00FF);
        array.push_back(event.src & 0x00FF);

        for (size_t i = 0; i < event.len; i++)
        {
            array.push_back(event.data[i]);
        }

        valueEvent->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueEvent->SetValue(array);
    }

    ITS_EVENT_TERM(&event);

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapGetNextEvent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Get next Event (blocking call).                             \n"
           "                                                            \n"
           "<integer> GetNextEvent(<byte array>):                       \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Event (out).                                        \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapPeekNextEvent.
//

Command::ReturnType
CommandTcapPeekNextEvent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapPeekNextEvent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapPeekNextEvent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueEvent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    TcapMnt& tcapMnt = static_cast<TcapMnt&>(mnt);

    ITS_HANDLE handle = tcapMnt.GetHandle();

    ITS_EVENT event;
    memset(&event, 0, sizeof(ITS_EVENT));

    int res = ITS_PeekNextEvent(handle, &event);

    if (res == ITS_SUCCESS)
    {
        vector<unsigned char> array;

        array.reserve(event.len + 2);

        array.push_back(event.src >> 8 & 0x00FF);
        array.push_back(event.src & 0x00FF);

        for (size_t i = 0; i < event.len; i++)
        {
            array.push_back(event.data[i]);
        }

        valueEvent->SetValue(array);
    }
    else
    {
        vector<unsigned char> array;

        valueEvent->SetValue(array);
    }

    ITS_EVENT_TERM(&event);

    ValueInteger* result = new ValueInteger();

    result->SetValue(res);

    return result;
}

string
CommandTcapPeekNextEvent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Peek next Event (non-blocking call).                        \n"
           "                                                            \n"
           "<integer> PeekNextEvent(<byte array>):                      \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Event (out).                                        \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Result (zero if success, negative value if failure).\n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapIsComponentEvent.
//

Command::ReturnType
CommandTcapIsComponentEvent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BOOLEAN;
}

Command::ArgumentTypes
CommandTcapIsComponentEvent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapIsComponentEvent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueEvent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ITS_ASSERT(valueEvent->GetValue().size() >= 2);

    ITS_EVENT event;
    memset(&event, 0, sizeof(ITS_EVENT));

    unsigned char sourceMsb = valueEvent->GetValue()[0];
    unsigned char sourceLsb = valueEvent->GetValue()[1];

    event.src = sourceMsb << 8 | sourceLsb;
    event.len = valueEvent->GetValue().size() - 2;
    event.data = &valueEvent->GetValue()[2];

    ValueBoolean* result = new ValueBoolean();

    if (TCAP_MSG_TYPE(&event) == ITS_TCAP_CPT)
    {
        result->SetValue(true);
    }
    else
    {
        result->SetValue(false);
    }

    return result;
}

string
CommandTcapIsComponentEvent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Is Component Event?                                         \n"
           "                                                            \n"
           "<boolean> IsComponentEvent(<byte array>):                   \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Event.                                              \n"
           "                                                            \n"
           " -> Return value (type boolean):                            \n"
           "        True if component, false if not component.          \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapIsDialogueEvent.
//

Command::ReturnType
CommandTcapIsDialogueEvent::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_BOOLEAN;
}

Command::ArgumentTypes
CommandTcapIsDialogueEvent::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapIsDialogueEvent::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueEvent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    ITS_ASSERT(valueEvent->GetValue().size() >= 2);

    ITS_EVENT event;
    memset(&event, 0, sizeof(ITS_EVENT));

    unsigned char sourceMsb = valueEvent->GetValue()[0];
    unsigned char sourceLsb = valueEvent->GetValue()[1];

    event.src = sourceMsb << 8 | sourceLsb;
    event.len = valueEvent->GetValue().size() - 2;
    event.data = &valueEvent->GetValue()[2];

    ValueBoolean* result = new ValueBoolean();

    if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG)
    {
        result->SetValue(true);
    }
    else
    {
        result->SetValue(false);
    }

    return result;
}

string
CommandTcapIsDialogueEvent::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Is Dialogue Event?                                          \n"
           "                                                            \n"
           "<boolean> IsDialogueEvent(<byte array>):                    \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Event.                                              \n"
           "                                                            \n"
           " -> Return value (type boolean):                            \n"
           "        True if component, false if not component.          \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapGetComponentType.
//

Command::ReturnType
CommandTcapGetComponentType::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapGetComponentType::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapGetComponentType::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueComponent = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    TCAP_CPT cpt;
    memset(&cpt, 0, sizeof(TCAP_CPT));

    ITS_ASSERT(valueComponent->GetValue().size() == sizeof(TCAP_CPT));

    memcpy(&cpt, &valueComponent->GetValue()[0], sizeof(TCAP_CPT));

    ValueInteger* result = new ValueInteger();

    result->SetValue(cpt.ptype);

    return result;
}

string
CommandTcapGetComponentType::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Get Component type.                                         \n"
           "                                                            \n"
           "<integer> GetComponentType(<byte array>):                   \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Component.                                          \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Component type.                                     \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// TcapGetDialogueType.
//

Command::ReturnType
CommandTcapGetDialogueType::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandTcapGetDialogueType::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_BYTE_ARRAY);
    return argumentTypes;
}

Command::ReturnValue
CommandTcapGetDialogueType::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueByteArray* 
        valueDialogue = 
            static_cast<ValueByteArray*>(
                arguments[0]);

    TCAP_DLG dlg;
    memset(&dlg, 0, sizeof(TCAP_DLG));

    ITS_ASSERT(valueDialogue->GetValue().size() == sizeof(TCAP_DLG));

    memcpy(&dlg, &valueDialogue->GetValue()[0], sizeof(TCAP_DLG));

    ValueInteger* result = new ValueInteger();

    result->SetValue(dlg.ptype);

    return result;
}

string
CommandTcapGetDialogueType::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Get Dialogue type.                                          \n"
           "                                                            \n"
           "<integer> GetDialogueType(<byte array>):                    \n"
           "                                                            \n"
           " -> Argument #0 (type byte array):                          \n"
           "        Dialogue.                                           \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Dialogue type.                                      \n";
}

///////////////////////////////////////////////////////////////////////////////
//
//  Printing related.
//

#if defined(CCITT)

void 
PrintComponentCCITT(unsigned int dialogueId, TCAP_CPT* component)
{
    ITS_REQUIRE(component != NULL);

    Mnt::GetPrintLock().Acquire();

    printf("\n ---- TCAP Info [ Component:\n");

    switch (component->ptype)
    {
    // Printing TC_Invoke Cpt.
    case TCAP_PT_TC_INVOKE_CCITT:
        printf("\n TC_Invoke (dialogue id: %d)", dialogueId);

        // Invoke Id.
        printf("\n Invoke Id (total length = %d): ", 
            component->u.invoke.invoke_id.len);

        if (component->u.invoke.invoke_id.len > 0)
        {
            for (int i = 0; i < component->u.invoke.invoke_id.len; i++)
            {
                printf("0x%02X ", component->u.invoke.invoke_id.data[i]);
            }
        }

        // Linked Id.
        printf("\n Linked Id (total length = %d): ", 
            component->u.invoke.linked_id.len);

        if (component->u.invoke.linked_id.len > 0)
        {
            for (int i = 0; i < component->u.invoke.linked_id.len; i++)
            {
                printf("0x%02X ", component->u.invoke.linked_id.data[i]);
            }
        }
        
        // Operation Class.
        printf("\n Operation class: %d",  component->u.invoke.opClass);

        // Timeout.
        printf("\n Timeout (in seconds): %d", component->u.invoke.timeout);


        // Operation Code.
        printf("\n Operation code (Total length = %d): ", 
            component->u.invoke.operation.len);

        if (component->u.invoke.operation.len > 0)
        {
            if (component->u.invoke.operation.data[0] == 
                TCAP_PN_GLOBAL_OP_TAG_CCITT)
            {
                printf("\n Global Operation Code: ");
            }
            else if (component->u.invoke.operation.data[0] == 
                TCAP_PN_LOCAL_OP_TAG_CCITT)
            {
                printf("\n Global Operation Code: ");
            }
            else
            {
                printf("\n Operation Code Tag unknown (0x%02X):",
                    component->u.invoke.operation.data[0]);
            }

            for (int i = 0; i < component->u.invoke.operation.len; i++)
            {
                printf("0x%02X ", component->u.invoke.operation.data[i]);
            }
        }

        // Parameters.
        printf("\n Parameters (total length: %d):",
            component->u.invoke.param.len);

        if (component->u.invoke.param.len > 0)
        {            
            printf("\n Data: ");
            for (int i = 0; i < component->u.invoke.param.len; i++)
            {
                printf("0x%02X ", component->u.invoke.param.data[i]);
            }
        }
        
        // Last component.
        printf("\n This is%s the last component",
            ((component->last_component) ? "" : " not"));
           
        break;

    case TCAP_PT_TC_RESULT_L_CCITT:
    case TCAP_PT_TC_RESULT_NL_CCITT:
        printf("\n TC_Result_%s (dialogue id: %d)",
            ((component->ptype == TCAP_PT_TC_RESULT_L_CCITT) ? "L" : "NL"),
            dialogueId);

        // Invoke Id.
        printf("\n Invoke Id (total length = %d): ", 
            component->u.result.invoke_id.len);

        if (component->u.result.invoke_id.len > 0)
        {
            for (int i = 0; i < component->u.result.invoke_id.len; i++)
            {
                printf("0x%02X ", component->u.result.invoke_id.data[i]);
            }
        }
        
        // Operation Code.
        printf("\n Operation code (Total length = %d): ", 
            component->u.result.operation.len);

        if (component->u.result.operation.len > 0)
        {
            if (component->u.result.operation.data[0] == 
                TCAP_PN_LOCAL_OP_TAG_CCITT)
            {
                printf("\n Local Operation Code: ");
            }
            else if (component->u.result.operation.data[0] == 
                TCAP_PN_GLOBAL_OP_TAG_CCITT)
            {
                printf("\n Global Operation Code: ");
            }
            else
            {
                printf("\n Operation Code Tag unknown (0x%02X):",
                    component->u.result.operation.data[0]);
            }

            for (int i = 0; i < component->u.result.operation.len; i++)
            {
                printf("0x%02X ", component->u.result.operation.data[i]);
            }
        }

        // Parameters.
        printf("\n Parameters (total length: %d):",
            component->u.result.param.len);

        if (component->u.result.param.len > 0)
        {            
            printf("\n Data: ");
            for (int i = 0; i < component->u.result.param.len; i++)
            {
                printf("0x%02X ", component->u.result.param.data[i]);
            }
        }

        // Last component.
        printf("\n This is%s the last component",
            ((component->last_component) ? "" : " not"));

        break;

    case TCAP_PT_TC_U_ERROR_CCITT:
        printf("\n TC_U_Error (dialogue id: %d)", 
            dialogueId);

        // Invoke Id.
        printf("\n Invoke Id (total length = %d): ", 
            component->u.error.invoke_id.len);

        if (component->u.error.invoke_id.len > 0)
        {
            for (int i = 0; i < component->u.error.invoke_id.len; i++)
            {
                printf("0x%02X ", component->u.error.invoke_id.data[i]);
            }
        }

        // Error Code.
        printf("\n Error code (total length = %d): ", 
               component->u.error.error.len);

        if (component->u.error.error.len > 0)
        {
            if (component->u.error.error.data[0] == 
                TCAP_PN_LOCAL_ERR_TAG_CCITT)
            {
                printf("\n Local Error Code: ");
            }
            else if (component->u.error.error.data[0] == 
                TCAP_PN_GLOBAL_ERR_TAG_CCITT)
            {
                printf("\n Global Error Code: ");
            }
            else
            {
                printf("\n Error Code Tag unknown (0x%02X):",
                       component->u.error.error.data[0]);
            }

            for (int i = 0; i < component->u.error.error.len; i++)
            {
                printf("0x%02X ", component->u.error.error.data[i]);
            }
        }
        
        // Parameters.
        printf("\n Parameters (total length: %d):",
            component->u.error.param.len);

        if (component->u.error.param.len > 0)
        {            
            printf("\n Data: ");
            for (int i = 0; i < component->u.error.param.len; i++)
            {
                printf("0x%02X ", component->u.error.param.data[i]);
            }
        }
        
        // Last component.
        printf("\n This is%s the last component",
            ((component->last_component) ? "" : " not"));

        break;
    
    case TCAP_PT_TC_L_CANCEL_CCITT:
    case TCAP_PT_TC_U_CANCEL_CCITT:
        printf("\n TC_%s_Cancel (dialogue id: %d)",
            ((component->ptype == TCAP_PT_TC_L_CANCEL_CCITT) ? "L" : "U"), 
            dialogueId);

        // Invoke id.
        printf("\n Invoke Id (total length = %d): ", 
            component->u.cancel.invoke_id.len);

        if (component->u.cancel.invoke_id.len > 0)
        {
            for (int i = 0; i < component->u.cancel.invoke_id.len; i++)
            {
                printf("0x%02X ", component->u.cancel.invoke_id.data[i]);
            }
        }
        break;
    
    case TCAP_PT_TC_L_REJECT_CCITT:
    case TCAP_PT_TC_U_REJECT_CCITT:
    case TCAP_PT_TC_R_REJECT_CCITT:
        printf("\n TC_%s_Reject (dialogue id: %d)",
           ((component->ptype == TCAP_PT_TC_L_REJECT_CCITT) ? "L" :
           ((component->ptype == TCAP_PT_TC_U_REJECT_CCITT) ? "U" : "R")),
           dialogueId);

        // Invoke id.
        printf("\n Invoke Id (total length = %d): ", 
            component->u.reject.invoke_id.len);

        if (component->u.reject.invoke_id.len > 0)
        {
            for (int i = 0; i < component->u.reject.invoke_id.len; i++)
            {
                printf("0x%02X ", component->u.reject.invoke_id.data[i]);
            }
        }

        // Problem.
        switch (component->u.reject.problem.data[0])
        {
        case TCAP_PROB_GENERAL_CCITT:
            switch (component->u.reject.problem.data[2])
            {
            case TCAP_PROB_SPEC_GEN_UNREC_COMP_CCITT:
                printf("\n General problem: Unrecognized component");
                break;
            case TCAP_PROB_SPEC_GEN_MISTYPED_COMP_CCITT:
                printf("\n General problem: Mistyped component");
                break;
            case TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_CCITT:
                printf("\n General problem: Badly structured component");
                break;
            default:
                printf("\n Unknown General problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        case TCAP_PROB_INVOKE_CCITT:
            switch (component->u.reject.problem.data[2])
            {
            case TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_CCITT:
                printf("\n Invoke problem: Duplicate invoke Id");
                break;
            case TCAP_PROB_SPEC_INV_UNREC_OP_CODE_CCITT:
                printf("\n Invoke problem: Unrecognized operation");
                break;
            case TCAP_PROB_SPEC_INV_MISTYPED_PARAM_CCITT:
                printf("\n Invoke problem: Mistyped parameter");
                break;
            case TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_CCITT:
                printf("\n Invoke problem: Resource limitation");
                break;
            case TCAP_PROB_SPEC_INV_INITIATE_RELEASE_CCITT:
                printf("\n Invokev problem: Initiating release");
                break;
            case TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_CCITT:
                printf("\n Invoke problem: Unrecognized linked Id");
                break;
            case TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_CCITT:
                printf("\n Invoke problem: Linked response unexpected");
                break;
            case TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_CCITT:
                printf("\n Invoke problem: Unexpected Linked operation");
                break;
            default:
                printf("\n Unknown Invoke problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        case TCAP_PROB_RETURN_RES_CCITT:
            switch (component->u.reject.problem.data[2])
            {
            case TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_CCITT:
                printf("\n Return Result problem: Unrecognized invoke Id");
                break;
            case TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_CCITT:
                printf("\n Return Result problem: Return result unexpected");
                break;
            case TCAP_PROB_SPEC_RES_MISTYPED_PARAM_CCITT:
                printf("\n Return Result problem: Mistyped parameter");
                break;
            default:
                printf("\n Unknown Return Result problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        case TCAP_PROB_RETURN_ERR_CCITT:
            switch (component->u.reject.problem.data[2])
            {
            case TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_CCITT:
                printf("\n Return Error problem: Unrecognized invoke Id");
                break;
            case TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_CCITT:
                printf("\n Return Error problem: Return Error unexpected");
                break;
            case TCAP_PROB_SPEC_ERR_UNREC_ERROR_CCITT:
                printf("\n Return Error problem: Unrecognized error");
                break;
            case TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_CCITT:
                printf("\n Return Error problem: Unexpected error");
                break;
            case TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_CCITT:
                printf("\n Return Error problem: Mistyped parameter");
                break;
            default:
                printf("\n Unknown Return Error problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        default:
            printf("\n Unknown Problem Tag (0x%02)",
                   component->u.reject.problem.data[0]);
            break;
        }

        // Last component.
        printf("\n This is%s the last component",
            ((component->last_component) ? "" : " not"));

        break;            
    }

    Mnt::GetPrintLock().Release();

    printf("\n].\n\n");
}

void 
PrintDialogueCCITT(unsigned int dialogueId, TCAP_DLG* dialogue)
{
    ITS_REQUIRE(dialogue != NULL);

    Mnt::GetPrintLock().Acquire();

    printf("\n ---- TCAP Info [ Dialogue:\n");

    switch (dialogue->ptype)
    {
    case TCAP_PT_TC_UNI_CCITT:
        printf("\n TC_Uni (dialogue id: %d)", dialogueId); 

        if (dialogue->u.uni.orig_addr.len)
        {
            printf("\n Calling Party Address: ");
            PrintAddress(&dialogue->u.uni.orig_addr, true);
        }
        else
        {
            printf("\n Calling Party Address: Not present");
        }

        if (dialogue->u.uni.dest_addr.len)
        {
            printf("\n Called Party Address: ");
            PrintAddress(&dialogue->u.uni.dest_addr, true);        
        }
        else
        {
            printf("\n Called Party Address: Not present");
        }

        // Quality of service.
        if (dialogue->u.uni.qos.indicator)
        {
            printf(
                "\n Quality of Service (Indicator: %d, SLS Key: %d, Priority:"
                " %d) present",
                dialogue->u.uni.qos.indicator,
                dialogue->u.uni.qos.sls_key,
                dialogue->u.uni.qos.priority); 
        }
        else
        {
            printf("\n Quality of Service not present");
        }

        // Application Context Name.
        printf("\n Application Context Name (length: %d)",
            dialogue->u.uni.ac_name.len);
        if (dialogue->u.uni.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.uni.ac_name.len; i++)
            {
                printf("0x%02X ", dialogue->u.uni.ac_name.data[i]);
            }            
        }

        // User Information.
        printf("\n User Information (length: %d)",
            dialogue->u.uni.user_info.len);
        if (dialogue->u.uni.user_info.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.uni.user_info.len; i++)
            {
                printf("0x%02X ", dialogue->u.uni.user_info.data[i]);
            }
        }

        // Component(s) present.
        printf("\n Component%s present",
            ((dialogue->u.uni.cpt_present) ? "(s) is(are)" : " not"));
        break;

    case TCAP_PT_TC_BEGIN_CCITT:            
        printf("\n TC_Begin (dialogue id: %d)", dialogueId); 
        
        if (dialogue->u.begin.orig_addr.len)
        {
            printf("\n Calling Party Address: ");
            PrintAddress(&dialogue->u.begin.orig_addr, true);
        }
        else
        {
            printf("\n Calling Party Address: Not present");
        }

        if (dialogue->u.begin.dest_addr.len)
        {
            printf("\n Called Party Address: ");
            PrintAddress(&dialogue->u.begin.dest_addr, true);        
        }
        else
        {
            printf("\n Called Party Address: Not present");
        }

        // Quality of service.
        if (dialogue->u.begin.qos.indicator)
        {
            printf(
                "\n Quality of Service (Indicator: %d, SLS Key: %d, Priority:"
                " %d) present",
                dialogue->u.begin.qos.indicator,
                dialogue->u.begin.qos.sls_key,
                dialogue->u.begin.qos.priority); 
        }
        else
        {
            printf("\n Quality of Service not present");
        }

        // Application Context Name.
        printf("\n Application Context Name (length: %d)",
            dialogue->u.begin.ac_name.len);
        if (dialogue->u.begin.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.begin.ac_name.len; i++)
            {
                printf("0x%02X ", dialogue->u.begin.ac_name.data[i]);
            }            
        }

        // User Information.
        printf("\n User Information (length: %d)",
               dialogue->u.begin.user_info.len);
        if (dialogue->u.begin.user_info.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.begin.user_info.len; i++)
            {
                printf("0x%02X ", dialogue->u.begin.user_info.data[i]);
            }
        }

        // Component(s) present.
        printf("\n Component%s present",
            ((dialogue->u.begin.cpt_present) ? "(s) is(are)" : " not"));

        break;

    case TCAP_PT_TC_END_CCITT:
        printf("\n TC_End (dialogue id: %d)", dialogueId);

        // Quality of service.
        if (dialogue->u.end.qos.indicator)
        {
            printf(
                "\n Quality of Service (Indicator: %d, SLS Key: %d, Priority:"
                " %d) present",
                dialogue->u.end.qos.indicator,
                dialogue->u.end.qos.sls_key,
                dialogue->u.end.qos.priority); 
        }
        else
        {
            printf("\n Quality of Service not present");
        }

        // Termination.
        printf("\n Termination is set to %s",
            ((dialogue->u.end.termination) ? "Pre-arranged end" : 
            "Basic end"));
        
        // Application Context.
         printf("\n Application Context Name (length: %d)",
            dialogue->u.end.ac_name.len);
        if (dialogue->u.end.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.end.ac_name.len; i++)
            {
                printf("0x%02X ", dialogue->u.end.ac_name.data[i]);
            }            
        }

        // User Information present.
        printf("\n Application Context Name (length: %d)",
               dialogue->u.end.ac_name.len);
        if (dialogue->u.end.user_info.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.end.user_info.len; i++)
            {
                printf("0x%02X ", dialogue->u.end.user_info.data[i]);
            }
        }

        // Component(s) present.
            printf("\n Component%s present",
                ((dialogue->u.end.cpt_present) ? "(s) is(are)" : " not"));

        break;

    case TCAP_PT_TC_CONTINUE_CCITT:
        printf("\n TC_Continue (dialogue id: %d)", dialogueId);

        // Quality of service.
        if (dialogue->u.cont.qos.indicator)
        {
            printf(
                "\n Quality of Service (Indicator: %d, SLS Key: %d, Priority:"
                " %d) present",
                dialogue->u.cont.qos.indicator,
                dialogue->u.cont.qos.sls_key,
                dialogue->u.cont.qos.priority); 
        }
        else
        {
            printf("\n Quality of Service not present");
        }

        // Calling party address.
        if (dialogue->u.cont.orig_addr.len > 0)
        {
            printf("\n Calling Party Address");
            PrintAddress(&dialogue->u.cont.orig_addr, true);
        }

        // Application Context Name.
        printf("\n Application Context Name (length: %d)",
            dialogue->u.cont.ac_name.len);
        if (dialogue->u.cont.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.cont.ac_name.len; i++)
            {
                printf("0x%02X ", dialogue->u.cont.ac_name.data[i]);
            }
        }

       // User Information.
        printf("\n User Information (length: %d)",
               dialogue->u.cont.user_info.len);
        if (dialogue->u.cont.user_info.len > 0)
        {
            printf("\n Data: ");
            for (int i = 0; i < dialogue->u.cont.user_info.len; i++)
            {
                printf("0x%02X ", dialogue->u.cont.user_info.data[i]);
            }
        }

        // Component(s) present.
        printf("\n Component%s present",
            ((dialogue->u.cont.cpt_present) ? "(s) is(are)" : " not"));

        break;

    case TCAP_PT_TC_P_ABORT_CCITT:
    case TCAP_PT_TC_U_ABORT_CCITT:
        printf("\n TC_%s_Abort (dialogue id: %d)" ,
            ((dialogue->ptype == TCAP_PT_TC_U_ABORT_CCITT) ? "U" : "P"), 
             dialogueId);

        if (dialogue->ptype == TCAP_PT_TC_P_ABORT_CCITT)
        {
            switch(dialogue->u.abort.abort_reason)
            {
            case TCPABT_REASON_UNREC_MSG_TYPE:
                printf("\n Abort reason: Unrecognized Message Type");
                break;
            case TCPABT_REASON_UNREC_TRANS_ID:
                printf("\n Abort reason: Unrecognized Transaction ID");
                    break;
            case TCPABT_REASON_BADLY_STRUCT_TRANS_PORT:
                printf("\n Abort reason: Badly Formatted Transaction Portion");
                break;
            case TCPABT_REASON_INCORRECT_TRANS_PORT:
                printf("\n Abort reason: Incorrect Transaction Portion");
                break;
            case TCPABT_REASON_RES_UNAVAIL:
                printf("\n Abort reason: Resource Limitation");
                break;
            default:
                printf("\n Abort reason: 0x%02X",
                       dialogue->u.abort.abort_reason);
                break;
            }
        }
        else
        {
            switch(dialogue->u.abort.abort_reason)
            {
            case TCPUABT_AC_NOT_SUP:
                printf("\n Abort reason: Application context not supported");
                break;
            case TCPUABT_USER_DEFINED:
                printf("\n abort reason: User defined");
                    break;
            default:
                printf("\n abort reason: 0x%02X",
                       dialogue->u.abort.abort_reason);
                break;
            }

            // Application Context Name.
            printf("\n Application Context Name (length: %d)",
                dialogue->u.abort.ac_name.len);
            if (dialogue->u.abort.ac_name.len > 0)
            {
                printf("\n Data: ");
                for (int i = 0; i < dialogue->u.abort.ac_name.len;
                     i++)
                {
                    printf("0x%02X ", dialogue->u.abort.ac_name.data[i]);
                }
            }

            // User Information.
            printf("\n User Information (length: %d)",
                dialogue->u.abort.user_info.len);
            if (dialogue->u.abort.user_info.len > 0)
            {
                printf("\n Data: ");
                for (int i = 0; i < dialogue->u.abort.user_info.len;
                     i++)
                {
                    printf("0x%02X ", dialogue->u.abort.user_info.data[i]);
                }
            }
        }
        break;

    case TCAP_PT_TC_NOTICE_CCITT:
        printf("\n TC_Notice (dialogue id: %d)", dialogueId); 
        printf("\n Return Cause: 0x%02X", dialogue->u.notice.report_cause);
        break;            
    }

    Mnt::GetPrintLock().Release();

    printf("\n].\n\n");

}

#else // !defined(CCITT)

void 
PrintComponentANSI(unsigned int dialogueId, TCAP_CPT* component)
{
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}

void 
PrintDialogueANSI(unsigned int dialogueId, TCAP_DLG* dialogue)
{
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}

#endif // defined(CCITT)

void 
PrintAddress(SCCP_ADDR* address, bool raw)
{
    ITS_REQUIRE(address != NULL);

    ITS_OCTET addressIndicator;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_USHORT gttLen;
    ITS_OCTET gttInfo[SCCP_MAX_ADDR_LEN];

    SCCP_DecodeAddr(
                address, 
                &addressIndicator, 
                &pointCode, 
                &ssn, 
                gttInfo, 
                &gttLen);

    if (!raw)
    {
        Mnt::GetPrintLock().Acquire();

        printf("\n ---- TCAP Info [ SCCP Address:");
    }



    printf("\n     Address Indicator: 0x%02X", addressIndicator);

    if (addressIndicator & SCCP_CPA_HAS_PC)
    {
        printf("\n     Point code: 0x%04X, ", pointCode);
    }
    else
    {
        printf("\n     Point code not present, ");
    }

    if (addressIndicator & SCCP_CPA_HAS_SSN)
    {
        printf("SSN: %d", ssn);
    }
    else
    {
        printf("SSN not present");
    }
    if (gttLen > 0)
    {
        printf("\n     Global Title Information: ");
        for (size_t i = 0; i < gttLen; i++)
        {
            printf("0x%02X ", gttInfo[i]);
        }
    }
    else
    {
        printf("\n     Global Title Information not present\n");
    }

    if (!raw)
    {
        Mnt::GetPrintLock().Release();
        printf("\n].\n\n");
    }
}



///////////////////////////////////////////////////////////////////////////////
//
//  TcapMnt implementation.
//

TcapMnt::TcapMnt() 
:   Mnt()
{
    InsertCommand(new CommandTcapInitialize());
    InsertCommand(new CommandTcapTerminate());
#if defined(CCITT)
    InsertCommand(new CommandTcapAssembleInvokeComponent());
    InsertCommand(new CommandTcapDisassembleInvokeComponent());
    InsertCommand(new CommandTcapAssembleResultLastComponent());
    InsertCommand(new CommandTcapDisassembleResultLastComponent());
#endif // defined(CCITT)
    InsertCommand(new CommandTcapInvokeIdToByteArray());
    InsertCommand(new CommandTcapByteArrayToInvokeId());
#if defined(CCITT)
    InsertCommand(new CommandTcapLinkedIdToByteArray());
    InsertCommand(new CommandTcapByteArrayToLinkedId());
#endif // defined(CCITT)
#if defined(CCITT)
    InsertCommand(new CommandTcapOperationToByteArray());
    InsertCommand(new CommandTcapByteArrayToOperation());
#endif // defined(CCITT)
#if defined(CCITT)
    InsertCommand(new CommandTcapAssembleBeginDialogue());
    InsertCommand(new CommandTcapDisassembleBeginDialogue());
    InsertCommand(new CommandTcapAssembleEndDialogue());
    InsertCommand(new CommandTcapDisassembleEndDialogue());
#endif // defined(CCITT)
    InsertCommand(new CommandTcapPointCodeToByteArray());
    InsertCommand(new CommandTcapByteArrayToPointCode());
    InsertCommand(new CommandTcapSccpAddressToByteArray());
    InsertCommand(new CommandTcapByteArrayToSccpAddress());
    InsertCommand(new CommandTcapQualityOfServiceToByteArray());
    InsertCommand(new CommandTcapByteArrayToQualityOfService());
    InsertCommand(new CommandTcapPrintComponent());
    InsertCommand(new CommandTcapPrintDialogue());
    InsertCommand(new CommandTcapPrintAddress());
    InsertCommand(new CommandTcapAllocateDialogueId());
    InsertCommand(new CommandTcapSendComponent());
    InsertCommand(new CommandTcapReceiveComponent());
    InsertCommand(new CommandTcapSendDialogue());
    InsertCommand(new CommandTcapReceiveDialogue());
    InsertCommand(new CommandTcapGetNextEvent());
    InsertCommand(new CommandTcapPeekNextEvent());
    InsertCommand(new CommandTcapIsComponentEvent);
    InsertCommand(new CommandTcapIsDialogueEvent());
    InsertCommand(new CommandTcapGetComponentType);
    InsertCommand(new CommandTcapGetDialogueType());

    // Predefined variable for SCCP.
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_NONE", 0x00U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_NATURE", 0x04U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_ALL", 0x10U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_MASK", 0x1CU);
    InsertIntegerVariable(
        "SCCP_CPA_ROUTE_GTTI", 0x00U);
    InsertIntegerVariable(
        "SCCP_CPA_ROUTE_SSN", 0x40U);
#if defined(CCITT)
    InsertIntegerVariable(
        "SCCP_CPA_HAS_PC_CCITT", 0x01U);
    InsertIntegerVariable(
        "SCCP_CPA_HAS_SSN_CCITT", 0x02U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_TRANS_CCITT", 0x08U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_TNE_CCITT", 0x0CU);
    InsertIntegerVariable(
        "SCCP_CPA_ROUTE_INT_CCITT", 0x80U);
    InsertIntegerVariable(
        "SCCP_CPA_ROUTE_NAT_CCITT", 0x00U);
#else // !defined(CCITT)
    InsertIntegerVariable(
        "SCCP_CPA_HAS_PC_ANSI", 0x02U);
    InsertIntegerVariable(
        "SCCP_CPA_HAS_SSN_ANSI", 0x01U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_TRANS_ANSI", 0x08U);
    InsertIntegerVariable(
        "SCCP_CPA_GTTI_TNE_ANSI", 0x04U);
    InsertIntegerVariable(
        "SCCP_CPA_ROUTE_NAT_ANSI", 0x80U);
    InsertIntegerVariable(
        "SCCP_CPA_ROUTE_INT_ANSI", 0x00U);
#endif // defined(CCITT)

    // Predefined variables for TCAP.
#if defined(CCITT)
    InsertIntegerVariable(
        "TCAP_PT_TC_UNI_CCITT", 0x61U);
    InsertIntegerVariable(
        "TCAP_PT_TC_BEGIN_CCITT", 0x62U);
    InsertIntegerVariable(
        "TCAP_PT_TC_END_CCITT", 0x64U);
    InsertIntegerVariable(
        "TCAP_PT_TC_CONTINUE_CCITT", 0x65U);
    InsertIntegerVariable(
        "TCAP_PT_TC_P_ABORT_CCITT", 0x67U);
    InsertIntegerVariable(
        "TCAP_PT_TC_U_ABORT_CCITT", 0x68U);
    InsertIntegerVariable(
        "TCAP_PT_TC_NOTICE_CCITT", 0x69U);

    InsertIntegerVariable(
        "TCAP_PT_TC_INVOKE_CCITT", 0xA1U);
    InsertIntegerVariable(
        "TCAP_PT_TC_RESULT_L_CCITT", 0xA2U);
    InsertIntegerVariable(
        "TCAP_PT_TC_U_ERROR_CCITT", 0xA3U);
    InsertIntegerVariable(
        "TCAP_PT_TC_R_REJECT_CCITT", 0xA4U);
    InsertIntegerVariable(
        "TCAP_PT_TC_RESULT_NL_CCITT", 0xA7U);
    InsertIntegerVariable(
        "TCAP_PT_TC_L_CANCEL_CCITT", 0xA8U);
    InsertIntegerVariable(
        "TCAP_PT_TC_U_CANCEL_CCITT", 0xA9U);
    InsertIntegerVariable(
        "TCAP_PT_TC_L_REJECT_CCITT", 0xAAU);
    InsertIntegerVariable(
        "TCAP_PT_TC_U_REJECT_CCITT", 0xABU);
    InsertIntegerVariable(
        "TCAP_PT_TC_TIMER_RESET_CCITT", 0xACU);

    InsertIntegerVariable(
        "TCAP_PN_INVOKE_TAG_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PN_LOCAL_OP_TAG_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PN_GLOBAL_OP_TAG_CCITT", 0x06U);
    InsertIntegerVariable(
        "TCAP_PN_LOCAL_ERR_TAG_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PN_GLOBAL_ERR_TAG_CCITT", 0x06U);

    InsertIntegerVariable(
        "TCAP_UABT_AC_NOT_SUP_CCITT", 1);
    InsertIntegerVariable(
        "TCAP_UABT_DLG_REFUSED_CCITT", 2);
    InsertIntegerVariable(
        "TCAP_UABT_USER_DEFINED_CCITT", 3);

    InsertIntegerVariable(
        "TCAP_PABT_ABNORMAL_DLG_CCITT", 126);
    InsertIntegerVariable(
        "TCAP_PABT_NO_COMMON_DLG_CCITT", 127);

    InsertIntegerVariable(
        "TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT", 0x00U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT", 0x01U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_INCORRECT_TRANS_PORT_CCITT", 0x03U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_RES_UNAVAIL_CCITT", 0x04U);

    InsertIntegerVariable(
        "TCAP_PROB_GENERAL_CCITT", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_INVOKE_CCITT", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_RETURN_RES_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_RETURN_ERR_CCITT", 0x03U);

    InsertIntegerVariable(
        "TCAP_PROB_SPEC_GEN_UNREC_COMP_CCITT", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_GEN_MISTYPED_COMP_CCITT", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_CCITT", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_UNREC_OP_CODE_CCITT", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_MISTYPED_PARAM_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_CCITT", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_INITIATE_RELEASE_CCITT", 0x04U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_CCITT", 0x05U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_CCITT", 0x06U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_CCITT", 0x07U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_CCITT", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_CCITT", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_RES_MISTYPED_PARAM_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_CCITT", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_CCITT", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNREC_ERROR_CCITT", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_CCITT", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_CCITT", 0x04U);
#else // !defined(CCITT)
    InsertIntegerVariable(
        "TCAP_PT_TC_UNI_ANSI", 0xE1U);
    InsertIntegerVariable(
        "TCAP_PT_TC_QUERY_W_PERM_ANSI", 0xE2U);
    InsertIntegerVariable(
        "TCAP_PT_TC_QUERY_WO_PERM_ANSI", xE3U);
    InsertIntegerVariable(
        "TCAP_PT_TC_RESP_ANSI", 0xE4U);
    InsertIntegerVariable(
        "TCAP_PT_TC_CONV_W_PERM_ANSI", 0xE5U);
    InsertIntegerVariable(
        "TCAP_PT_TC_CONV_WO_PERM_ANSI", 0xE6U);
    InsertIntegerVariable(
        "TCAP_PT_TC_ABORT_ANSI", 0xE7U);
    InsertIntegerVariable(
        "TCAP_PT_TC_NOTICE_ANSI", 0xE8U);


    InsertIntegerVariable(
        "TCAP_PT_TC_INVOKE_ANSI", 0xE9U);
    InsertIntegerVariable(
        "TCAP_PT_TC_RESULT_L_ANSI", 0xEAU);
    InsertIntegerVariable(
        "TCAP_PT_TC_ERROR_ANSI", 0xEBU);
    InsertIntegerVariable(
        "TCAP_PT_TC_REJECT_ANSI", 0xECU);
    InsertIntegerVariable(
        "TCAP_PT_TC_INVOKE_NL_ANSI", 0xEDU);
    InsertIntegerVariable(
        "TCAP_PT_TC_RESULT_NL_ANSI", 0xEEU);
    InsertIntegerVariable(
        "TCAP_PT_TC_CANCEL_ANSI", 0xEFU);
                                             
    InsertIntegerVariable(
        "TCAP_PN_COMPONENT_ID_ANSI", 0xCFU);

    InsertIntegerVariable(
        "TCAP_PN_INVOKE_TAG_ANSI", 0xCFU);

    InsertIntegerVariable(
        "TCAP_PN_OCI_NATIONAL_TCAP_ANSI", xD0U);
    InsertIntegerVariable(
        "TCAP_PN_OCI_PRIVATE_TCAP_ANSI", 0xD1U);

    InsertIntegerVariable(
        "TCAP_OF_NOT_USED_ANSI", 0x00U);

    InsertIntegerVariable(
        "TCAP_OF_REPLY_REQUIRED_ANSI", x80U);

    InsertIntegerVariable(
        "TCAP_OF_PARAMETER_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_OF_CHARGING_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_OF_PROV_INST_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_OF_CONN_CTRL_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_OF_CALLER_INT_ANSI", 0x05U);
    InsertIntegerVariable(
        "TCAP_OF_SEND_NOT_ANSI", 0x06U);
    InsertIntegerVariable(
        "TCAP_OF_NET_MAN_ANSI", 0x07U);
    InsertIntegerVariable(
        "TCAP_OF_PROCEDURAL_ANSI", 0x08U);
    InsertIntegerVariable(
        "TCAP_OF_IS41_ANSI", 0x09U);

    InsertIntegerVariable(
        "TCAP_OF_MISC_ANSI", 0xFEU);
    InsertIntegerVariable(
        "TCAP_OF_RESERVED_ANSI", 0xFFU);

    InsertIntegerVariable(
        "TCAP_OS_NOT_USED_ANSI", 0x00U);

    InsertIntegerVariable(
        "TCAP_OS_PROV_VAL_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_OS_SET_VAL_ANSI", 0x02U);

    InsertIntegerVariable(
        "TCAP_OS_BILL_CALL_ANSI", 0x01U);

    InsertIntegerVariable(
        "TCAP_OS_START_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_OS_ASSIST_ANSI", 0x02U);

    InsertIntegerVariable(
        "TCAP_OS_CONN_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_OS_TEMP_CONN_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_OS_DISCONN_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_OS_FWD_DISCONN_ANSI", 0x04U);

    InsertIntegerVariable(
        "TCAP_OS_PLAY_A_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_OS_PLAY_A_CD_ANSI", 0x02U);

    InsertIntegerVariable(
        "TCAP_OS_AUTO_CALL_GAP_ANSI", 0x01U);

    InsertIntegerVariable(
        "TCAP_OS_TEMP_HO_ANSI", 0x01U);

    InsertIntegerVariable(
        "TCAP_OS_RESERVED_ANSI", 0xFFU);

    InsertIntegerVariable(
        "TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI", 0x00U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_UNREC_TRANS_ID_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_PERM_TO_RELEASE_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_ABT_REASON_RES_UNAVAIL_ANSI", 0x05U);

    InsertIntegerVariable(
        "TCAP_PN_ECI_NATIONAL_TCAP_ANSI", xD3U);
    InsertIntegerVariable(
        "TCAP_PN_ECI_PRIVATE_TCAP_ANSI", 0xD4U);

    InsertIntegerVariable(
        "TCAP_ERR_NOT_USED_ANSI", 0x00U);
    InsertIntegerVariable(
        "TCAP_ERR_UNEX_COMP_SEQ_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_ERR_UNEX_DATA_VAL_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_ERR_UNAV_RESOURCE_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_ERR_MISSING_REC_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_ERR_REPLY_OVERDUE_ANSI", 0x05U);
    InsertIntegerVariable(
        "TCAP_ERR_DATA_UNAV_ANSI", 0x06U);
    InsertIntegerVariable(
        "TCAP_ERR_TSK_RE_ANSI", 0x07U);
    InsertIntegerVariable(
        "TCAP_ERR_Q_FULL_ANSI", 0x08U);
    InsertIntegerVariable(
        "TCAP_ERR_NO_Q_ANSI", 0x09U);
    InsertIntegerVariable(
        "TCAP_ERR_TMR_EX_ANSI", 0x0AU);
    InsertIntegerVariable(
        "TCAP_ERR_DAT_EX_ANSI", 0x0BU);
    InsertIntegerVariable(
        "TCAP_ERR_UNAUTH_ANSI", 0x0CU);
    InsertIntegerVariable(
        "TCAP_ERR_NOT_QD_ANSI", 0x0DU);
    InsertIntegerVariable(
        "TCAP_ERR_UAS_DN_ANSI", 0x0EU);
    InsertIntegerVariable(
        "TCAP_ERR_SPARE_ANSI", 0x0FU);
    InsertIntegerVariable(
        "TCAP_ERR_NOT_AV_ANSI", 0x10U);
    InsertIntegerVariable(
        "TCAP_ERR_VMSR_E_ANSI", 0x11U);

    InsertIntegerVariable(
        "TCAP_PN_PROB_IDENT_ANSI", 0xD5U);

    InsertIntegerVariable(
        "TCAP_PROB_NOT_USED_ANSI", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_GENERAL_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_INVOKE_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_RETURN_RES_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_RETURN_ERR_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_PROB_TRANS_PORTION_ANSI", 0x05U);

    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ALL_RESERVED_ANSI", 0xFFU);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ALL_NOTUSED_ANSI", 0x00U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_GEN_UNREC_COMP_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_UNREC_OP_CODE_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_INCORRECT_PARAM_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_INV_UNREC_COREL_ID_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_RES_UNREC_COREL_ID_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_RES_INCORRECT_PARAM_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNREC_COREL_ID_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNREC_ERROR_ANSI", 0x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_ERR_INCORRECT_PARAM_ANSI", 0x05U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_TRANS_UNREC_PACK_TYPE_ANSI", 0x01U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_TRANS_INCORRECT_TRANS_PORT_ANSI", 0x02U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT_ANSI", x03U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_TRANS_UNREC_TRANS_ID_ANSI", 0x04U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_TRANS_PERM_TO_RELEASE_ANSI", 0x05U);
    InsertIntegerVariable(
        "TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI", 0x06U);
#endif // defined(CCITT)
}

TcapMnt::~TcapMnt()
{
    // Nothing to do.
}


///////////////////////////////////////////////////////////////////////////////
//
// Global Variables.
//

static int argcForMntG = 0;
static const char** argvForMntG = NULL;


///////////////////////////////////////////////////////////////////////////////
//
// ApplicationSelector (always returns MNT phony Border Transport instance).
//

extern "C" EXPORTFUNC ITS_USHORT
ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event)
{
    unsigned short mntTransportInstance = 0;

    // Start at 20000 because MntMain transport belongs to border pool.

    for (unsigned short i = 20000; i < 20064; i++)
    {
        TRANSPORT_Control* tc = TRANSPORT_FindTransport(i);

        if (tc != NULL && strcmp(tc->transport.name, "MntMain") == 0)
        {
            mntTransportInstance = i;
            break;
        }
    }

    if (mntTransportInstance != 0)
    {
        return mntTransportInstance;
    }
    else
    {
        return ITS_DEFAULT_USER_SRC;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// MNT Main (to be called by Engine through MNT phony Border Transport).  
//

extern "C" EXPORTFUNC void
MntMainFunction(ThreadPoolThread* thread, void* arg)
{
    Worker* worker = static_cast<Worker*>(thread);
    DISP_FuncsCPP* cbs = static_cast<DISP_FuncsCPP*>(arg);
    ITS_HANDLE handle = NULL;

    ITS_C_REQUIRE(worker != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thread) != ITS_SUCCESS)
        {
            free(cbs);

            return;
        }
    }

    handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thread, handle) != ITS_SUCCESS)
        {
            if (handle)
            {
                ITS_Terminate(handle);
            }

            free(cbs);

            return;
        }
    }
    else if (handle == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thread);
        }

        return;
    }

    // Dispatcher loop => Changed to run MNT that interfaces to event APIs.
    while (!worker->GetExit())
    {
        TcapMnt tcapMnt;

        tcapMnt.SetHandle(handle);

        tcapMnt.Run(argcForMntG, argvForMntG);

        // Stop application.
        SERVICE_DefaultStopHandler();
        SERVICE_SetStopped();

        // Stop loop.
        break;
    }
    
    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thread);
    }

    ITS_Terminate(handle);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thread);
    }

    free(cbs);
}


///////////////////////////////////////////////////////////////////////////////
//
// Entry point.
//

int main(int argc, const char** argv)
{
    ///////////////////////////////////////////////////////
    // Set Application name (allow to find XML init file).

#if defined(WIN32)
    APPL_SetName("test_tcap_mn_win32");
#else // !defined(WIN32)
    APPL_SetName("test_tcap_mn_unix");
#endif // defined(WIN32)

    // Argument(s) for Engine.
    int argcForEngine = 1;
    const char* argvForEngine[1];
    argvForEngine[0] = argv[0];

    // Argument(s) for MNT.
    argcForMntG = argc;
    argvForMntG = argv;

    ENGINE_Initialize(argcForEngine, argvForEngine, NULL, 0);

    ENGINE_Run(argc, argv);

    return EXIT_SUCCESS;
}



