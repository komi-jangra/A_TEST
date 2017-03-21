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

#ident "$Id: test_dsm_mn_main.cpp,v 1.1.1.1 2007-10-08 11:12:02 bsccs2 Exp $"

//
//  DSM (Distributed Shared Memory) Multi-Nodes Test Tool (MNT) with Engine.
//
//  Regression/performance/endurance testing with different implementations 
//  of DSM (e.g Stub, GCS, SCI...).
//

#include <its++.h>
#include <its_app.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_dsm.h>
#include <its_dsm_gcs.h>
#include <its_dsm_stub.h>

#include <engine.h>

#include <mnt_mnt.h>
#include <mnt_command.h>


using namespace std;
using namespace its;
using namespace mnt;


#if defined(WIN32)
#define EXPORTFUNC   __declspec(dllexport)
#else // !defined(WIN32)
#define EXPORTFUNC
#endif // defined(WIN32)


///////////////////////////////////////////////////////////////////////////////
//
// Forward declarations.
//

typedef std::map<std::string, void*> TypeKeyObjects;

///////////////////////////////////////////////////////////////////////////////
//
//  DsmMnt.
//

class DsmMnt : public Mnt
{
public:

    DsmMnt();

    ~DsmMnt();

    TypeKeyObjects&
    GetKeyObjectsBulk()
    {
        return _keyObjectsBulk;
    }

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
    TypeKeyObjects _keyObjectsBulk;

};

///////////////////////////////////////////////////////////////////////////////
//
// DSM table dump function.
//

static size_t dsmObjectDumpSize = 32; // To be modified accordingly.

extern "C" {
    
int 
DumpEntryDsmTable(ITS_POINTER data, char** pStrDump)
{
    const int PRINT_DATA_MAX_SIZE   = 16384;
    const int PRINT_BUF_MAX_SIZE    = 512;

    static char printBuf[PRINT_BUF_MAX_SIZE];

    *pStrDump = (char*)malloc(PRINT_DATA_MAX_SIZE);

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    **pStrDump = '\0';

    DSM_RowHeader* row = (DSM_RowHeader*)(data - sizeof(DSM_RowHeader));

    while (row != NULL)
    {
        strcat(*pStrDump, "------------------------------\n");

        // Key (always ASCII keys for tests).
        strcat(*pStrDump, "Key:         [");
        memcpy(printBuf, row->key, row->klen);
        printBuf[row->klen] = '\0';
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, "]\n");

        // Key length.
        strcat(*pStrDump, "Key length:  [");
        sprintf(printBuf, "%d", row->klen);
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, "]\n");

        // Object (always ASCII objects for tests).
        DSM_RowHeader* object = row + 1;
        strcat(*pStrDump, "Object:      [");
        memcpy(printBuf, object, dsmObjectDumpSize);
        printBuf[dsmObjectDumpSize] = '\0';
        strcat(*pStrDump, printBuf);
        strcat(*pStrDump, "]\n");

        strcat(*pStrDump, "------------------------------\n");

        row = row->next;
    }

    ITS_ASSERT(strlen(*pStrDump) < PRINT_DATA_MAX_SIZE); 

    return ITS_SUCCESS;
}

} // extern "C".


///////////////////////////////////////////////////////////////////////////////
//
// All DSM related commands.
//

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmJoinFtGroup,
                    "DsmJoinFtGroup",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmLeaveFtGroup,
                    "DsmLeaveFtGroup",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmSynchronizeDsm,
                    "DsmSynchronizeDsm",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmGetNodeId,
                    "DsmGetNodeId",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmGetProcessId,
                    "DsmGetProcessId",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmTableDump,
                    "DsmTableDump",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmAllocateCommitBulkOfRows,
                    "DsmAllocateCommitBulkOfRows",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmFreeBulkOfRows,
                    "DsmFreeBulkOfRows",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmFindBulkOfRows,
                    "DsmFindBulkOfRows",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmAllocateRow,
                    "DsmAllocateRow",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmCommitRow,
                    "DsmCommitRow",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmFreeRow,
                    "DsmFreeRow",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmFindRow,
                    "DsmFindRow",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmLockRow,
                    "DsmLockRow",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmUnlockRow,
                    "DsmUnlockRow",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmLockDsm,
                    "DsmLockDsm",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmUnlockDsm,
                    "DsmUnlockDsm",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmLockTable,
                    "DsmLockTable",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmUnlockTable,
                    "DsmUnlockTable",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmAllocateRowNoLock,
                    "DsmAllocateRowNoLock",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmCommitRowNoLock,
                    "DsmCommitRowNoLock",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmFreeRowNoLock,
                    "DsmFreeRowNoLock",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmFindRowNoLock,
                    "DsmFindRowNoLock",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmLockRowNoLock,
                    "DsmLockRowNoLock",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmUnlockRowNoLock,
                    "DsmUnlockRowNoLock",
                    "dsm");

MNT_DEFINE_COMMAND_CLASS(
                    CommandDsmWriteStringToAddress,
                    "DsmWriteStringToAddress",
                    "dsm");


///////////////////////////////////////////////////////////////////////////////
//
// DsmJoinFtGroup.
//

Command::ReturnType
CommandDsmJoinFtGroup::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmJoinFtGroup::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmJoinFtGroup::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    int ftGroupId   = valueInteger->GetValue();

    ITS_ASSERT(ftGroupId >= 0);

    int ret = DSM_JoinFtGroup(ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmJoinFtGroup: DSM_JoinFtGroup failed: %d",
            ret));
    }
    else 
    {
        MNT_PRINT_INFO((
            "CommandDsmJoinFtGroup: DSM_JoinFtGroup succeeded"));
    }
   
    return new ValueNone();
}

string
CommandDsmJoinFtGroup::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Join a Fault Tolerance Group.                               \n"
           "                                                            \n"
           "<none> DsmJoinFtGroup(<integer>):                           \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmLeaveFtGroup.
//

Command::ReturnType
CommandDsmLeaveFtGroup::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmLeaveFtGroup::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmLeaveFtGroup::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    int ftGroupId   = valueInteger->GetValue();

    ITS_ASSERT(ftGroupId >= 0);

    int ret = DSM_LeaveFtGroup(ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmLeaveFtGroup: DSM_LeaveFtGroup failed: %d",
            ret));
    }
    else 
    {
        MNT_PRINT_INFO((
            "CommandDsmLeaveFtGroup: DSM_LeaveFtGroup succeeded"));
    }
   
    return new ValueNone();
}

string
CommandDsmLeaveFtGroup::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Leave a Fault Tolerance Group.                              \n"
           "                                                            \n"
           "<none> DsmLeaveFtGroup(<integer>):                          \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmSynchronizeDsm.
//

Command::ReturnType
CommandDsmSynchronizeDsm::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmSynchronizeDsm::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmSynchronizeDsm::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    int ftGroupId   = valueInteger1->GetValue();
    int msecs       = valueInteger2->GetValue();

    ITS_ASSERT(ftGroupId >= 0);
    ITS_ASSERT(msecs >= 0);

    int ret = DSM_SynchronizeDsm(ftGroupId, msecs);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmSynchronizeDsm: DSM_SynchronizeDsm failed: %d",
            ret));
    }
    else 
    {
        MNT_PRINT_INFO((
            "CommandDsmSynchronizeDsm: DSM_SynchronizeDsm succeeded"));
    }
   
    return new ValueNone();
}

string
CommandDsmSynchronizeDsm::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Synchronize DSM Instance with one of the specified Master   \n"
           "Fault Tolerance Group members (according to their statuses).\n"
           "                                                            \n"
           "<none> DsmSynchronizeDsm(<integer>, <integer>):             \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Timeout in milliseconds.                            \n";
}


///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmGetNodeId.
//

Command::ReturnType
CommandDsmGetNodeId::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmGetNodeId::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandDsmGetNodeId::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ITS_USHORT nodeId = DSM_GetNodeId();

    return new ValueInteger((long)nodeId);
}

string
CommandDsmGetNodeId::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Retrieve current node identifier.                           \n"
           "                                                            \n"
           "<integer> DsmGetNodeId():                                   \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Current node identifier.                            \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmGetProcessId.
//

Command::ReturnType
CommandDsmGetProcessId::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmGetProcessId::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandDsmGetProcessId::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ITS_USHORT processId = DSM_GetProcessId();

    return new ValueInteger((long)processId);
}

string
CommandDsmGetProcessId::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Retrieve current process identifier.                        \n"
           "                                                            \n"
           "<integer> DsmGetProcessId():                                \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        Current process identifier.                         \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmTableDump.
//

Command::ReturnType
CommandDsmTableDump::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmTableDump::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmTableDump::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    int ftGroupId   = valueInteger1->GetValue();
    int tableId     = valueInteger2->GetValue();

    ITS_ASSERT(ftGroupId >= 0);
    ITS_ASSERT(tableId >= 0);

    char* strDump = NULL;

    int ret = DSM_TableDump(ftGroupId, tableId, &strDump, DumpEntryDsmTable);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmTableDump: DSM_TableDump failed: %d",
            ret));
    }
    else
    {
        MNT_PRINT_INFO((
            "CommandDsmTableDump: DSM_TableDump succeeded"));
        ITS_ASSERT(strDump != NULL);
        MNT_PRINT_INFO(("\n\n%s\n\n", strDump));
        free(strDump);
    }

    return new ValueNone();
}

string
CommandDsmTableDump::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Dump a table to standard output.                            \n"
           "                                                            \n"
           "<none> DsmTableDump(<integer>, <integer>):                  \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmAllocateCommitBulkOfRows.
//

Command::ReturnType
CommandDsmAllocateCommitBulkOfRows::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmAllocateCommitBulkOfRows::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmAllocateCommitBulkOfRows::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger* 
        valueInteger3 = 
            static_cast<ValueInteger*>(
                arguments[2]);

    ValueInteger* 
        valueInteger4 = 
            static_cast<ValueInteger*>(
                arguments[3]);

    int ftGroupId       = valueInteger1->GetValue();
    int tableId         = valueInteger2->GetValue();
    int numberOfRows    = valueInteger3->GetValue();
    int sizeOfRows      = valueInteger4->GetValue();

    void* ptr;
    int error;
    int ret;
    char key[32];
    char object[64];

    for (int i = 0; i < numberOfRows; i++)
    {
        sprintf(key, "dsm#1-%d", i);
        ptr = DSM_Alloc(
                    ftGroupId,
                    tableId, 
                    (ITS_OCTET*)key, 
                    strlen(key), 
                    sizeOfRows, 
                    &error);

        if (ptr == NULL || error != ITS_SUCCESS)
        {
            MNT_PRINT_INFO((
                "CommandDsmAllocateCommitBulkOfRows: DSM_Alloc failed: %d",
                error));
            break;
        }

        sprintf(object, "dsm#1-%d-abcdefghijklmnopqrstuvwxyz", i);
        memcpy(
            ptr, 
            object, 
            (sizeOfRows > strlen(object)) ? strlen(object) : sizeOfRows);

        ret = DSM_Commit(
                    ftGroupId,
                    tableId, 
                    (ITS_OCTET*)key, 
                    strlen(key), 
                    ptr);
        if (ret != ITS_SUCCESS)
        {
            MNT_PRINT_INFO((
                "CommandDsmAllocateCommitBulkOfRows: DSM_Commit failed: %d",
                ret));
        }
        
        if (ptr != NULL && ret == ITS_SUCCESS)
        {
            // Insert (key, object) in dsmMnt._keyObjectsBulk map to allow to
            // retrieve object from key (required by DSM_Free).

            static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().insert(
                TypeKeyObjects::value_type(
                    key,
                    ptr));
        }
    }
   
    return new ValueNone();
}

string
CommandDsmAllocateCommitBulkOfRows::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command                        \n"
           "DsmAllocateCommitBulkOfRows.";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmFreeBulkOfRows.
//

Command::ReturnType
CommandDsmFreeBulkOfRows::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmFreeBulkOfRows::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmFreeBulkOfRows::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger* 
        valueInteger3 = 
            static_cast<ValueInteger*>(
                arguments[2]);

    int ftGroupId       = valueInteger1->GetValue();
    int tableId         = valueInteger2->GetValue();
    int numberOfRows    = valueInteger3->GetValue();

    char key[32];

    for (int i = 0; i < numberOfRows; i++)
    {
        sprintf(key, "dsm#1-%d", i);

        void* ptr = NULL;

        // Retrieve object from key through dsmMnt._keyObjectsBulk map.
        TypeKeyObjects::const_iterator iter = 
            static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().find(key);

        if (iter != static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().end())
        {
            ptr = (*iter).second;
        }
        else
        {
            MNT_PRINT_INFO((
                "CommandDsmFreeBulkOfRows: retrieve object from key failed"));
        }

        int ret = DSM_Free(
                        ftGroupId,
                        tableId, 
                        (ITS_OCTET*)key, 
                        strlen(key), 
                        ptr);

        if (ret != ITS_SUCCESS)
        {
            MNT_PRINT_INFO((
                "CommandDsmFreeBulkOfRows: DSM_Free failed: %d",
                ret));
            break;
        }

        // Cleanup dsmMnt._keyObjectsBulk map.
        if (iter != static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().end())
        {
            static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().erase(key);
        }
    }
   
    return new ValueNone();
}

string
CommandDsmFreeBulkOfRows::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmFreeBulkOfRows.";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmFindBulkOfRows.
//

Command::ReturnType
CommandDsmFindBulkOfRows::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmFindBulkOfRows::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmFindBulkOfRows::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    ValueInteger* 
        valueInteger3 = 
            static_cast<ValueInteger*>(
                arguments[2]);

    int ftGroupId       = valueInteger1->GetValue();
    int tableId         = valueInteger2->GetValue();
    int numberOfRows    = valueInteger3->GetValue();

    char key[32];

    for (int i = 0; i < numberOfRows; i++)
    {
        sprintf(key, "dsm#1-%d", i);

        void* ptrFromKey = NULL;

        // Retrieve object from key through dsmMnt._keyObjectsBulk map.
        TypeKeyObjects::const_iterator iter = 
            static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().find(key);

        if (iter != static_cast<DsmMnt&>(mnt).GetKeyObjectsBulk().end())
        {
            ptrFromKey = (*iter).second;
        }
        else
        {
            MNT_PRINT_INFO((
                "CommandDsmFindBulkOfRows: retrieve object from key failed"));
        }

        void* ptr;
        int error;

        ptr = DSM_Find(
                    ftGroupId,
                    tableId, 
                    (ITS_OCTET*)key, 
                    strlen(key), 
                    &error);

        if (ptr == NULL || error != ITS_SUCCESS)
        {
            MNT_PRINT_INFO((
                "CommandDsmFindBulkOfRows: DSM_Find failed: %d",
                error));
            break;
        }

        if (ptr != ptrFromKey)
        {
            MNT_PRINT_INFO((
                "CommandDsmFindBulkOfRows: inconsistency between DSM_Find result "
                "and object retrieved from key"));
        }
    }
   
    return new ValueNone();
}

string
CommandDsmFindBulkOfRows::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmFindBulkOfRows.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmAllocateRow.
//

Command::ReturnType
CommandDsmAllocateRow::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmAllocateRow::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmAllocateRow::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId =
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long size = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int error =
        (int)static_cast<ValueInteger*>(arguments[4])->GetValue();

    void* ptr = DSM_Alloc(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (ITS_UINT)size,
                    &error);

    static_cast<ValueInteger*>(arguments[3])->SetValue((long)error);

    return new ValueInteger((long)ptr);
}

string
CommandDsmAllocateRow::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Allocate a row in specified Fault Tolerance Group (i.e. DSM)\n"
           "within specified table with specified key.                  \n"
           "                                                            \n"
           "<integer> DsmAllocateRow(                                   \n"
           "                    <integer>,                              \n"
           "                    <integer>,                              \n"
           "                    <string>,                               \n"
           "                    <integer>,                              \n"
           "                    <integer>):                             \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Size of row in octets.                              \n"
           "                                                            \n"
           " -> Argument #4 (type integer):                             \n"
           "        Error code on failure (must use 'out' specifier).   \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        A pointer to allocated row (mem) or NULL.           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmCommitRow.
//

Command::ReturnType
CommandDsmCommitRow::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmCommitRow::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmCommitRow::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int res = DSM_Commit(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmCommitRow::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Commit a row in specified Fault Tolerance Group (i.e. DSM)  \n"
           "within specified table with specified key.                  \n"
           "                                                            \n"
           "<integer>DsmCommitRow(                                      \n"
           "                    <integer>,                              \n"
           "                    <integer>,                              \n"
           "                    <string>,                               \n"
           "                    <integer>):                             \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Row to commit (integer but in fact a pointer).      \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmFreeRow.
//

Command::ReturnType
CommandDsmFreeRow::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmFreeRow::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmFreeRow::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int res = DSM_Free(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmFreeRow::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Free a row in specified Fault Tolerance Group (i.e. DSM)    \n"
           "within specified table with specified key.                  \n"
           "                                                            \n"
           "<integer> DsmFreeRow(                                       \n"
           "                <integer>,                                  \n"
           "                <integer>,                                  \n"
           "                <string>,                                   \n"
           "                <integer>):                                 \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Row to free (integer but in fact a pointer).        \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmFindRow.
//

Command::ReturnType
CommandDsmFindRow::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmFindRow::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmFindRow::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    int error =
        (int)static_cast<ValueInteger*>(arguments[3])->GetValue();

    void* ptr = DSM_Find(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    &error);

    static_cast<ValueInteger*>(arguments[2])->SetValue((long)error);

    return new ValueInteger((long)ptr);
}

string
CommandDsmFindRow::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Find a row in specified Fault Tolerance Group (i.e. DSM)    \n"
           "within specified table with specified key.                  \n"
           "                                                            \n"
           "<integer> DsmFindRow(                                       \n"
           "                <integer>,                                  \n"
           "                <integer>,                                  \n"
           "                <string>,                                   \n"
           "                <integer>):                                 \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Error code on failure (must use 'out' specifier).   \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        A pointer to row (mem) found or NULL.               \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmLockRow.
//

Command::ReturnType
CommandDsmLockRow::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmLockRow::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmLockRow::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int res = DSM_LockRow(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmLockRow::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Lock a row in specified Fault Tolerance Group (i.e. DSM)    \n"
           "within specified table with specified key.                  \n"
           "                                                            \n"
           "<integer>DsmLockRow(                                        \n"
           "                <integer>,                                  \n"
           "                <integer>,                                  \n"
           "                <string>,                                   \n"
           "                <integer>):                                 \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Row to lock (integer but in fact a pointer).        \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmUnlockRow.
//

Command::ReturnType
CommandDsmUnlockRow::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmUnlockRow::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmUnlockRow::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[1])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[2])->GetValue();

    int res = DSM_UnlockRow(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmUnlockRow::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Unlock a row in specified Fault Tolerance Group (i.e. DSM)  \n"
           "within specified table with specified key.                  \n"
           "                                                            \n"
           "<integer>DsmUnlockRow(                                      \n"
           "                <integer>,                                  \n"
           "                <integer>,                                  \n"
           "                <string>,                                   \n"
           "                <integer>):                                 \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Row to unlock (integer but in fact a pointer).      \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmLockDsm.
//

Command::ReturnType
CommandDsmLockDsm::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmLockDsm::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmLockDsm::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    int ret = DSM_LockDsm((ITS_USHORT)ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmLockDsm: DSM_LockDsm failed: %d",
            ret));
    }
    else
    {
        MNT_PRINT_INFO((
            "CommandDsmLockDsm: DSM_LockDsm succeeded"));
    }

    return new ValueInteger((long)ret);
}

string
CommandDsmLockDsm::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmLockDsm.";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmUnlockDsm.
//

Command::ReturnType
CommandDsmUnlockDsm::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmUnlockDsm::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmUnlockDsm::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    int ret = DSM_UnlockDsm((ITS_USHORT)ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmUnlockDsm: DSM_UnlockDsm failed: %d",
            ret));
    }
    else
    {
        MNT_PRINT_INFO((
            "CommandDsmUnlockDsm: DSM_UnlockDsm succeeded"));
    }

    return new ValueInteger((long)ret);
}

string
CommandDsmUnlockDsm::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmUnlockRegion.";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmLockTable.
//

Command::ReturnType
CommandDsmLockTable::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmLockTable::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmLockTable::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    int ftGroupId   = valueInteger1->GetValue();
    int tableId     = valueInteger2->GetValue();

    ITS_ASSERT(ftGroupId >= 0);
    ITS_ASSERT(tableId >= 0);

    int ret = DSM_LockTable(ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmLockTable: DSM_LockTable failed: %d",
            ret));
    }
    else
    {
        MNT_PRINT_INFO((
            "CommandDsmLockTable: DSM_LockTable succeeded"));
    }

    return new ValueInteger((long)ret);
}

string
CommandDsmLockTable::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmLockTable.";
}

///////////////////////////////////////////////////////////////////////////////
//
// DsmUnlockTable.
//

Command::ReturnType
CommandDsmUnlockTable::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmUnlockTable::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmUnlockTable::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger1 = 
            static_cast<ValueInteger*>(
                arguments[0]);

    ValueInteger* 
        valueInteger2 = 
            static_cast<ValueInteger*>(
                arguments[1]);

    int ftGroupId   = valueInteger1->GetValue();
    int tableId     = valueInteger2->GetValue();

    ITS_ASSERT(ftGroupId >= 0);
    ITS_ASSERT(tableId >= 0);

    int ret = DSM_UnlockTable(ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_INFO((
            "CommandDsmUnlockTable: DSM_UnlockTable failed: %d",
            ret));
    }
    else
    {
        MNT_PRINT_INFO((
            "CommandDsmUnlockTable: DSM_UnlockTable succeeded"));
    }

    return new ValueInteger((long)ret);
}

string
CommandDsmUnlockTable::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmUnlockTable.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmAllocateRowNoLock.
//

Command::ReturnType
CommandDsmAllocateRowNoLock::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmAllocateRowNoLock::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmAllocateRowNoLock::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId =
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long size = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int error =
        (int)static_cast<ValueInteger*>(arguments[4])->GetValue();

    void* ptr = DSM_AllocNoLock(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (ITS_UINT)size,
                    &error);

    static_cast<ValueInteger*>(arguments[3])->SetValue((long)error);

    return new ValueInteger((long)ptr);
}

string
CommandDsmAllocateRowNoLock::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Allocate a row in specified Fault Tolerance Group (i.e. DSM)\n"
           "within specified table with specified key. No lock is hold  \n"
           "on the row.                                                 \n"
           "                                                            \n"
           "MUST be used only when specified table is locked or         \n"
           "specified Fault Tolerance Group (i.e. DSM) is locked (see   \n"
           "DSM_TableLock/Unlock and DSM_DsmLock/Unlock).               \n"
           "                                                            \n"
           "<integer> DsmAllocateRowNoLock(                             \n"
           "                    <integer>,                              \n"
           "                    <integer>,                              \n"
           "                    <string>,                               \n"
           "                    <integer>,                              \n"
           "                    <integer>):                             \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        size of row in octets.                              \n"
           "                                                            \n"
           " -> Argument #4 (type integer):                             \n"
           "        Error code on failure (must use 'out' specifier).   \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        A pointer to allocated row (mem) or NULL.           \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmCommitRowNoLock.
//

Command::ReturnType
CommandDsmCommitRowNoLock::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmCommitRowNoLock::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmCommitRowNoLock::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int res = DSM_CommitNoLock(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmCommitRowNoLock::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Commit a row in specified Fault Tolerance Group (i.e. DSM)  \n"
           "within specified table with specified key. No check that row\n"
           "is locked is performed.                                     \n"
           "                                                            \n"
           "MUST be used only when specified table is locked or         \n"
           "specified Fault Tolerance Group (i.e. DSM) is locked (see   \n"
           "DSM_TableLock/Unlock and DSM_DsmLock/Unlock).               \n"
           "                                                            \n"
           "<integer>DsmCommitRowNoLock(                                \n"
           "                        <integer>,                          \n"
           "                        <integer>,                          \n"
           "                        <string>,                           \n"
           "                        <integer>):                         \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Row to commit (integer but in fact a pointer).      \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmFreeRowNoLock.
//

Command::ReturnType
CommandDsmFreeRowNoLock::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmFreeRowNoLock::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmFreeRowNoLock::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[3])->GetValue();

    int res = DSM_FreeNoLock(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmFreeRowNoLock::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Free a row in specified Fault Tolerance Group (i.e. DSM)    \n"
           "within specified table with specified key. No check that row\n"
           "is locked is performed.                                     \n"
           "                                                            \n"
           "MUST be used only when specified table is locked or         \n"
           "specified Fault Tolerance Group (i.e. DSM) is locked (see   \n"
           "DSM_TableLock/Unlock and DSM_DsmLock/Unlock).               \n"
           "                                                            \n"
           "<integer> DsmFreeRowNoLock(                                 \n"
           "                        <integer>,                          \n"
           "                        <integer>,                          \n"
           "                        <string>,                           \n"
           "                        <integer>):                         \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Row to free (integer but in fact a pointer).        \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmFindRowNoLock.
//

Command::ReturnType
CommandDsmFindRowNoLock::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmFindRowNoLock::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmFindRowNoLock::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long tableId = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    string key = 
        static_cast<ValueString*>(arguments[2])->GetValue();

    int error =
        (int)static_cast<ValueInteger*>(arguments[3])->GetValue();

    void* ptr = DSM_FindNoLock(
                    (ITS_USHORT)ftGroupId,
                    (ITS_UINT)tableId,
                    (ITS_OCTET*)key.c_str(),
                    (ITS_UINT)key.size(),
                    &error);

    static_cast<ValueInteger*>(arguments[2])->SetValue((long)error);

    return new ValueInteger((long)ptr);
}

string
CommandDsmFindRowNoLock::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Find a row in specified Fault Tolerance Group (i.e. DSM)    \n"
           "within specified table with specified key. No lock is hold  \n"
           "on the row.                                                 \n"
           "                                                            \n"
           "MUST be used only when specified table is locked or         \n"
           "specified Fault Tolerance Group (i.e. DSM) is locked (see   \n"
           "DSM_TableLock/Unlock and DSM_DsmLock/Unlock).               \n"
           "                                                            \n"
           "<integer> DsmFindRowNoLock(                                 \n"
           "                        <integer>,                          \n"
           "                        <integer>,                          \n"
           "                        <string>,                           \n"
           "                        <integer>):                         \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        TableId.                                            \n"
           "                                                            \n"
           " -> Argument #2 (type string):                              \n"
           "        Key identifying row in table.                       \n"
           "                                                            \n"
           " -> Argument #3 (type integer):                             \n"
           "        Error code on failure (must use 'out' specifier).   \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        A pointer to row (mem) found or NULL.               \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmLockRowNoLock.
//

Command::ReturnType
CommandDsmLockRowNoLock::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmLockRowNoLock::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmLockRowNoLock::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    int res = DSM_LockRowNoLock((ITS_USHORT)ftGroupId, (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmLockRowNoLock::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Lock a row.                                                 \n"
           "                                                            \n"
           "<integer>DsmLockRowNoLock(<integer>, <integer>):            \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Row to lock (integer but in fact a pointer).        \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmUnlockRowNoLock.
//

Command::ReturnType
CommandDsmUnlockRowNoLock::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandDsmUnlockRowNoLock::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmUnlockRowNoLock::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    long ftGroupId = 
        static_cast<ValueInteger*>(arguments[0])->GetValue();

    long object = 
        static_cast<ValueInteger*>(arguments[1])->GetValue();

    int res = DSM_UnlockRowNoLock((ITS_USHORT)ftGroupId, (void*)object);

    return new ValueInteger((long)res);
}

string
CommandDsmUnlockRowNoLock::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "Unlock a row.                                               \n"
           "                                                            \n"
           "<integer>DsmUnlockRowNoLock(<integer>, <integer>):          \n"
           "                                                            \n"
           " -> Argument #0 (type integer):                             \n"
           "        FtGroupId.                                          \n"
           "                                                            \n"
           " -> Argument #1 (type integer):                             \n"
           "        Row to unlock (integer but in fact a pointer).      \n"
           "                                                            \n"
           " -> Return value (type integer):                            \n"
           "        ITS_SUCCESS (0) on success or ITS error code.       \n";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandDsmWriteStringToAddress.
//

Command::ReturnType
CommandDsmWriteStringToAddress::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandDsmWriteStringToAddress::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    return argumentTypes;
}

Command::ReturnValue
CommandDsmWriteStringToAddress::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    void* ptr = (void*)static_cast<ValueInteger*>(arguments[0])->GetValue();

    string str = static_cast<ValueString*>(arguments[1])->GetValue();

    memcpy(ptr, str.c_str(), str.size() + 1);

    return new ValueNone();
}

string
CommandDsmWriteStringToAddress::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command DsmWriteStringToAddress.";
}



///////////////////////////////////////////////////////////////////////////////
//
//  DsmMnt implementation.
//

DsmMnt::DsmMnt() 
:   Mnt()
{
    InsertCommand(new CommandDsmJoinFtGroup());
    InsertCommand(new CommandDsmLeaveFtGroup());
    InsertCommand(new CommandDsmSynchronizeDsm());
    InsertCommand(new CommandDsmGetNodeId());
    InsertCommand(new CommandDsmGetProcessId());
    InsertCommand(new CommandDsmTableDump());
    InsertCommand(new CommandDsmAllocateCommitBulkOfRows());
    InsertCommand(new CommandDsmFreeBulkOfRows());
    InsertCommand(new CommandDsmFindBulkOfRows());
    InsertCommand(new CommandDsmAllocateRow());
    InsertCommand(new CommandDsmCommitRow());
    InsertCommand(new CommandDsmFreeRow());
    InsertCommand(new CommandDsmFindRow());
    InsertCommand(new CommandDsmLockRow());
    InsertCommand(new CommandDsmUnlockRow());
    InsertCommand(new CommandDsmLockDsm());
    InsertCommand(new CommandDsmUnlockDsm());
    InsertCommand(new CommandDsmLockTable());
    InsertCommand(new CommandDsmUnlockTable());
    InsertCommand(new CommandDsmAllocateRowNoLock());
    InsertCommand(new CommandDsmCommitRowNoLock());
    InsertCommand(new CommandDsmFreeRowNoLock());
    InsertCommand(new CommandDsmFindRowNoLock());
    InsertCommand(new CommandDsmLockRowNoLock());
    InsertCommand(new CommandDsmUnlockRowNoLock());
    InsertCommand(new CommandDsmWriteStringToAddress());
}

DsmMnt::~DsmMnt()
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
        DsmMnt dsmMnt;

        dsmMnt.SetHandle(handle);

        dsmMnt.Run(argcForMntG, argvForMntG);

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

int 
main(int argc, const char** argv)
{
    bool mntOnly = false;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "MntOnly") == 0)
        {
            mntOnly = true;
        }
    }

    // Argument(s) for MNT.
    argcForMntG = argc;
    argvForMntG = argv;

    if (mntOnly)
    {
        DsmMnt dsmMnt;

        dsmMnt.Run(argcForMntG, argvForMntG);
    }
    else
    {
        ITS_AddFeature(itsDSM_GcsImplClass);

        ITS_AddFeature(itsDSM_StubImplClass);

        ENGINE_Initialize(argc, argv, NULL, 0);

        ENGINE_Run(argc, argv);
    }

    return EXIT_SUCCESS;
}


