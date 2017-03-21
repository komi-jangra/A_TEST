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
// LOG: Revision 1.1.1.1  2007/03/08 15:14:18  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:31  cvsadmin
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
// LOG: Revision 5.4  2001/10/09 19:17:04  hdivoux
// LOG: Added GetArraySize command and allowed for empty arrays.
// LOG:
// LOG: Revision 5.3  2001/08/29 17:12:25  hdivoux
// LOG: Added Exit predefined command.
// LOG:
// LOG: Revision 5.2  2001/08/21 00:23:53  mmiers
// LOG: Warning removal
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.12  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.11  2001/08/14 23:24:05  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.10  2001/08/10 18:51:09  hdivoux
// LOG: Add-on to ignore error when receiver thread is stopping.
// LOG:
// LOG: Revision 1.9  2001/08/09 22:39:53  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 1.8  2001/08/09 21:23:52  hdivoux
// LOG: Port to Unix.
// LOG:
// LOG: Revision 1.7  2001/08/09 20:18:20  hdivoux
// LOG: Port to Unix (Sun CC).
// LOG:
// LOG: Revision 1.6  2001/08/09 20:10:37  hdivoux
// LOG: More port to Sun CC.
// LOG:
// LOG: Revision 1.5  2001/08/09 19:28:19  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/07 23:25:23  hdivoux
// LOG: Update for debug related commands.
// LOG:
// LOG: Revision 1.3  2001/08/07 21:52:59  hdivoux
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

#ident "$Id: mnt_predefined_commands.cpp,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_predefined_commands.cpp: MNT predefined commands implementation.
//
//


#include <mnt_predefined_commands.h>

#include <stdio.h>
#include <errno.h>

#include <its_timers.h>
#include <its_trace.h>

#include <mnt_mnt.h>
#include <mnt_messages.h>


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
// CommandPrint.
//

Command::ReturnType
CommandPrint::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandPrint::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_ANY);
    return argumentTypes;
}

Command::ReturnValue
CommandPrint::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueObject* valueObject = arguments[0];
    
    Mnt::GetPrintLock().Acquire();
    if (valueObject->GetType() == ValueObject::VALUE_TYPE_STRING)
    {
        printf(
            "%s", 
            static_cast<ValueString*>(
                valueObject)->
                    GetValue().
                        c_str());
    }
    else
    {
        printf("%s", valueObject->ToString().c_str());
    }
    Mnt::GetPrintLock().Release();

    return new ValueNone();
}

string
CommandPrint::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command Print.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandSleep.
//

Command::ReturnType
CommandSleep::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandSleep::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandSleep::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger =
            static_cast<ValueInteger*>(
                arguments[0]);

    TIMERS_Sleep(valueInteger->GetValue());

    return new ValueNone();
}

string
CommandSleep::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command Sleep.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandBreakpoint.
//

Command::ReturnType
CommandBreakpoint::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandBreakpoint::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandBreakpoint::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    bool MNT_BREAKPOINT = false;
    ITS_ASSERT(MNT_BREAKPOINT);
    return new ValueNone();
}

string
CommandBreakpoint::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command Breakpoint.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandInitializeNodes.
//

Command::ReturnType
CommandInitializeNodes::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandInitializeNodes::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandInitializeNodes::Execute(
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

    size_t nodeNumber = valueInteger1->GetValue();
    size_t numberOfNodes = valueInteger2->GetValue();

    mnt.SetNodeNumber(nodeNumber);
    mnt.SetNumberOfNodes(numberOfNodes);

    ITS_ASSERT(nodeNumber < numberOfNodes);
    ITS_ASSERT(numberOfNodes < Mnt::MNT_MAX_NODES);

    typedef Semaphore* SemaphorePtr;

    Semaphore** nodesJoinPoint = new SemaphorePtr[numberOfNodes];

    for (size_t i = 0; i < numberOfNodes; i++)
    {
        nodesJoinPoint[i] = new Semaphore(0);
    }

    mnt.SetNodesJoinPoint(nodesJoinPoint);

    return new ValueNone();
}

string
CommandInitializeNodes::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command InitializeNodes.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandInitializeNodesSyncPoints.
//

Command::ReturnType
CommandInitializeNodesSyncPoints::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandInitializeNodesSyncPoints::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandInitializeNodesSyncPoints::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    size_t numberOfNodesSyncPoints = valueInteger->GetValue();

    mnt.SetNumberOfNodesSyncPoints(numberOfNodesSyncPoints);

    size_t numberOfNodes = mnt.GetNumberOfNodes();

    typedef Semaphore** SemaphorePtrPtr;
    typedef Semaphore* SemaphorePtr;

    Semaphore*** nodesSyncPoints = new SemaphorePtrPtr[numberOfNodes];

    for (size_t i = 0; i < numberOfNodes; i++)
    {
        nodesSyncPoints[i] = new SemaphorePtr[numberOfNodesSyncPoints];
    }

    for (size_t j = 0; j < numberOfNodes; j++)
    {
        for (size_t k = 0; k < numberOfNodesSyncPoints; k++)
        {
            nodesSyncPoints[j][k] = new Semaphore(0);
        }
    }

    mnt.SetNodesSyncPoints(nodesSyncPoints);

    return new ValueNone();
}

string
CommandInitializeNodesSyncPoints::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command InitializeNodesSyncPoints.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandInitializeGcs.
//

Command::ReturnType
CommandInitializeGcs::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandInitializeGcs::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandInitializeGcs::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    char* gcsConnectionName = mnt.GetGcsConnectionName();
    char* gcsMemberName = mnt.GetGcsMemberName();
    size_t nodeNumber = mnt.GetNodeNumber();
    
    string gcsConnectionNameRoot = mnt.GetOptions().GetGcsConnectionNameRoot();


    // Build connectionName from connectionNameRoot and nodeNumber.
    sprintf(
        gcsConnectionName, 
        "%s%d", 
        gcsConnectionNameRoot.c_str(), 
        nodeNumber);

    ITS_ASSERT(strlen(gcsConnectionName) < GCS_MAX_PRIVATE_NAME);

    // Connect to GCS Daemon (MUST be already running).
    int ret = GCS_ConnectTimeout(
                    mnt.GetOptions().GetGcsDaemonName().c_str(),
                    gcsConnectionName,
                    0,
                    1,
                    mnt.GetGcsMailbox(),
                    gcsMemberName,
                    mnt.GetOptions().GetGcsConnectTimeout());
    if (ret != GCS_ACCEPT_SESSION)
    {
        MNT_PRINT_ERROR((
            "CommandInitializeGcs: GCS_ConnectTimeout failed: %d",
            ret));
    }

    // Join (test related) group.
    ret = GCS_Join(
            *mnt.GetGcsMailbox(), 
            mnt.GetOptions().GetGcsGroupName().c_str());
    if (ret < 0)
    {
        MNT_PRINT_ERROR((
            "CommandInitializeGcs: GCS_Join failed: %d",
            ret));
    }

    // Start receiver thread.
    ret = mnt.GetGcsReceiver().Enter(&mnt);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_ERROR((
            "CommandInitializeGcs: GCS Receiver start failed: %d",
            ret));
    }

    return new ValueNone();
}

string
CommandInitializeGcs::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command InitializeGcs.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandTerminateNodes.
//

Command::ReturnType
CommandTerminateNodes::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTerminateNodes::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandTerminateNodes::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    Semaphore** nodesJoinPoint = mnt.GetNodesJoinPoint();

    size_t numberOfNodes = mnt.GetNumberOfNodes();

    if (nodesJoinPoint != NULL)
    {

        for (size_t i = 0; i < numberOfNodes; i++)
        {
            delete nodesJoinPoint[i];
        }

        delete[] nodesJoinPoint;

        mnt.SetNodesJoinPoint(NULL);
    }

    return new ValueNone();
}

string
CommandTerminateNodes::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command TerminateNodes.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandTerminateNodesSyncPoints.
//

Command::ReturnType
CommandTerminateNodesSyncPoints::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTerminateNodesSyncPoints::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandTerminateNodesSyncPoints::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    Semaphore*** nodesSyncPoints = mnt.GetNodesSyncPoints();

    size_t numberOfNodes = mnt.GetNumberOfNodes();
    size_t numberOfNodesSyncPoints = mnt.GetNumberOfNodesSyncPoints();

    if (nodesSyncPoints != NULL)
    {
        for (size_t i = 0; i < numberOfNodes; i++)
        {
            for (size_t j = 0; j < numberOfNodesSyncPoints; j++)
            {
                delete nodesSyncPoints[i][j];
            }
        }

        for (size_t k = 0; k < numberOfNodes; k++)
        {
            delete[] nodesSyncPoints[k];
        }

        delete[] nodesSyncPoints;

        mnt.SetNodesSyncPoints(NULL);
    }

    return new ValueNone();
}

string
CommandTerminateNodesSyncPoints::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command TerminateNodesSyncPoints.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandTerminateGcs.
//

Command::ReturnType
CommandTerminateGcs::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandTerminateGcs::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandTerminateGcs::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    // Stop receiver thread.
    mnt.SetGcsReceiverStop(true);

    // Cannot wait for Receiver thread (might stay stuck in GCS_Receive 
    // blocking call).

    // If Receiver thread is stuck in GCS_Receive, call will exit with an
    // error that we need to ignore => Turn error trace off (if they are on).
    if (TRACE_ErrorTraceOn())
    {
        TRACE_TurnErrorTraceOnOff(ITS_FALSE);
    }

    // Leave (test related) group.
    int ret = GCS_Leave(
                *mnt.GetGcsMailbox(), 
                mnt.GetOptions().GetGcsGroupName().c_str());
    if (ret < 0)
    {
        MNT_PRINT_ERROR((
            "CommandTerminateGcs: GCS_Leave failed: %d",
            ret));
    }

    // Disconnect from GCS Daemon.
    ret = GCS_Disconnect(*mnt.GetGcsMailbox());
    if (ret < 0)
    {
        MNT_PRINT_ERROR((
            "CommandTerminateGcs: GCS_Disconnect failed: %d",
            ret));
    }

    return new ValueNone();
}

string
CommandTerminateGcs::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command TerminateGcs.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandWaitForNodeJoinPoint.
//

Command::ReturnType
CommandWaitForNodeJoinPoint::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandWaitForNodeJoinPoint::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandWaitForNodeJoinPoint::Execute(
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

    size_t nodeNumber = valueInteger1->GetValue();
    int timeout = valueInteger2->GetValue();

    ITS_ASSERT(nodeNumber < mnt.GetNumberOfNodes());
    ITS_ASSERT(timeout >= 0);

    Semaphore* semaphore = mnt.GetNodesJoinPoint()[nodeNumber];

    ITS_ASSERT(semaphore != NULL);

    int ret = semaphore->WaitWithTimeOut(timeout * 1000);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_ERROR((
            "CommandWaitForNodeJoinPoint: its::Semaphore::WaitWithTimeOut "
            "failed: %d",
            ret));
        return new ValueNone();
    }

    // Drain semaphore.
    while (semaphore->TryWait() == ITS_SUCCESS)
    {
    }

    return new ValueNone();
}

string
CommandWaitForNodeJoinPoint::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command WaitForNodeJoinPoint.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandWaitForNodeSyncPoint.
//

Command::ReturnType
CommandWaitForNodeSyncPoint::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandWaitForNodeSyncPoint::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandWaitForNodeSyncPoint::Execute(
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

    size_t nodeNumber = valueInteger1->GetValue();
    size_t syncPointNumber = valueInteger2->GetValue();
    int timeout = valueInteger3->GetValue();

    ITS_ASSERT(nodeNumber < mnt.GetNumberOfNodes());
    ITS_ASSERT(syncPointNumber < mnt.GetNumberOfNodesSyncPoints());
    ITS_ASSERT(timeout >= 0);

    Semaphore* 
        semaphore = 
            mnt.GetNodesSyncPoints()[nodeNumber][syncPointNumber];

    ITS_ASSERT(semaphore != NULL);

    int ret = semaphore->WaitWithTimeOut(timeout * 1000);
    if (ret != ITS_SUCCESS)
    {
        MNT_PRINT_ERROR((
            "CommandWaitForNodeSyncPoint: its::Semaphore::WaitWithTimeOut "
            "failed: %d",
            ret));
        return new ValueNone();
    }

    // Drain semaphore.
    while (semaphore->TryWait() == ITS_SUCCESS)
    {
    }

    return new ValueNone();
}

string
CommandWaitForNodeSyncPoint::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command WaitForNodeSyncPoint.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandPublishNodeSyncPointReached.
//

Command::ReturnType
CommandPublishNodeSyncPointReached::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandPublishNodeSyncPointReached::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandPublishNodeSyncPointReached::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger*
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    size_t syncPointNumber = valueInteger->GetValue();

    ITS_ASSERT(syncPointNumber < mnt.GetNumberOfNodesSyncPoints());

    MntMsg nodeSyncPointReachedMsg;

    nodeSyncPointReachedMsg.discriminator = MNT_MSG_NODE_SYNC_POINT_REACHED;

    nodeSyncPointReachedMsg.
        u.nodeSyncPointReached.nodeNumber = mnt.GetNodeNumber();
    nodeSyncPointReachedMsg.
        u.nodeSyncPointReached.syncPointNumber = syncPointNumber;
    strcpy(
        nodeSyncPointReachedMsg.u.nodeSyncPointReached.originMemberName,
        mnt.GetGcsMemberName());

    int ret = GCS_Multicast(
                *mnt.GetGcsMailbox(),
                GCS_SAFE_MSG,
                mnt.GetOptions().GetGcsGroupName().c_str(),
                MNT_MSG_NODE_SYNC_POINT_REACHED,
                sizeof(MntMsg),
                (const char*)&nodeSyncPointReachedMsg);
    if (ret < 0)
    {
        MNT_PRINT_ERROR((
            "CommandPublishNodeSyncPointReached: GCS_Multicast failed: %d",
            ret));
    }

    return new ValueNone();
}

string
CommandPublishNodeSyncPointReached::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command PublishNodeSyncPointReached.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandSetInternalDebugOn.
//

Command::ReturnType
CommandSetInternalDebugOn::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandSetInternalDebugOn::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandSetInternalDebugOn::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    mnt.GetOptions().SetDebugOn();
    return new ValueNone();
}

string
CommandSetInternalDebugOn::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command SetInternalDebugOn.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandSetInternalDebugOff.
//

Command::ReturnType
CommandSetInternalDebugOff::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandSetInternalDebugOff::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandSetInternalDebugOff::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    mnt.GetOptions().SetDebugOff();
    return new ValueNone();
}

string
CommandSetInternalDebugOff::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command SetInternalDebugOff.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandSetInternalParserDebugOn.
//

Command::ReturnType
CommandSetInternalParserDebugOn::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandSetInternalParserDebugOn::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandSetInternalParserDebugOn::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    mnt.GetOptions().SetParserDebugOn();
    return new ValueNone();
}

string
CommandSetInternalParserDebugOn::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command SetInternalParserDebugOn.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandSetInternalParserDebugOff.
//

Command::ReturnType
CommandSetInternalParserDebugOff::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandSetInternalParserDebugOff::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    return argumentTypes;
}

Command::ReturnValue
CommandSetInternalParserDebugOff::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    mnt.GetOptions().SetParserDebugOff();
    return new ValueNone();
}

string
CommandSetInternalParserDebugOff::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command SetInternalParserDebugOff.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandSystem.
//

Command::ReturnType
CommandSystem::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandSystem::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    return argumentTypes;
}

Command::ReturnValue
CommandSystem::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueString* 
        valueString = 
            static_cast<ValueString*>(
                arguments[0]);
    
    string shellCommand = valueString->GetValue();

    // Lookup for shell interpreter.
    if (system(NULL) == 0)
    {
        MNT_PRINT_ERROR((
            "CommandSystem: unable to find shell interpreter"));

        return new ValueInteger(0);
    }

    int ret = system(shellCommand.c_str());

    return new ValueInteger(ret);
}

string
CommandSystem::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command System.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandRedirectStdout.
//

Command::ReturnType
CommandRedirectStdout::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandRedirectStdout::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    return argumentTypes;
}

Command::ReturnValue
CommandRedirectStdout::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueString* 
        valueString = 
            static_cast<ValueString*>(
                arguments[0]);

    string file = valueString->GetValue();

    FILE* stream = freopen(file.c_str(), "w", stdout);

    if (stream == NULL)
    {
        MNT_PRINT_ERROR((
            "CommandRedirectStdout: freopen failed: %d",
            errno));
    }

    return new ValueNone();
}

string
CommandRedirectStdout::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command RedirectStdout.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandPrintFile.
//

Command::ReturnType
CommandPrintFile::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandPrintFile::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_STRING);
    return argumentTypes;
}

Command::ReturnValue
CommandPrintFile::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueString* 
        valueString = 
            static_cast<ValueString*>(
                arguments[0]);

    string file = valueString->GetValue();

    FILE* stream = fopen(file.c_str(), "r");
    if (stream == NULL)
    {
        MNT_PRINT_ERROR((
            "CommandPrintFile: unable to open file: %s",
            file.c_str()));

        return new ValueNone();
    }

    Mnt::GetPrintLock().Acquire();

    int c;

    while ((c = fgetc(stream)) != EOF)
    {
        fputc(c, stdout);
    }

    Mnt::GetPrintLock().Release();

    fclose(stream);

    return new ValueNone();
}

string
CommandPrintFile::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command PrintFile.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandExit.
//

Command::ReturnType
CommandExit::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_NONE;
}

Command::ArgumentTypes
CommandExit::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_INTEGER);
    return argumentTypes;
}

Command::ReturnValue
CommandExit::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueInteger* 
        valueInteger = 
            static_cast<ValueInteger*>(
                arguments[0]);

    exit(valueInteger->GetValue());

    return new ValueNone(); // Not reached.
}

string
CommandExit::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command Exit.";
}

///////////////////////////////////////////////////////////////////////////////
//
// CommandGetArraySize.
//

Command::ReturnType
CommandGetArraySize::GetReturnType() const
{
    return ValueObject::VALUE_TYPE_INTEGER;
}

Command::ArgumentTypes
CommandGetArraySize::GetArgumentTypes() const
{
    ArgumentTypes argumentTypes;
    argumentTypes.push_back(ValueObject::VALUE_TYPE_ANY);
    return argumentTypes;
}

Command::ReturnValue
CommandGetArraySize::Execute(
    Mnt& mnt,
    Command::Arguments& arguments)
{
    ValueObject* 
        valueObject = 
            static_cast<ValueObject*>(
                arguments[0]);

    size_t size = 0;

    switch (valueObject->GetType())
    {
    case ValueObject::VALUE_TYPE_BYTE_ARRAY:
        {
            ValueByteArray*
                valueByteArray = 
                    static_cast<ValueByteArray*>(
                        arguments[0]);

            size = valueByteArray->GetValue().size();

            break;
        }

    case ValueObject::VALUE_TYPE_INTEGER_ARRAY:
        {
            ValueIntegerArray*
                valueIntegerArray = 
                    static_cast<ValueIntegerArray*>(
                        arguments[0]);

            size = valueIntegerArray->GetValue().size();

            break;
        }

    case ValueObject::VALUE_TYPE_BOOLEAN_ARRAY:
        {
            ValueBooleanArray*
                valueBooleanArray = 
                    static_cast<ValueBooleanArray*>(
                        arguments[0]);

            size = valueBooleanArray->GetValue().size();

            break;
        }

    case ValueObject::VALUE_TYPE_STRING_ARRAY:
        {
            ValueStringArray*
                valueStringArray = 
                    static_cast<ValueStringArray*>(
                        arguments[0]);

            size = valueStringArray->GetValue().size();

            break;
        }

    default:

        {
            MNT_PRINT_ERROR((
                "CommandGetArraySize: invalid type: %s",
                valueObject->GetTypeName().c_str()));                

            size = 0;
        }
    }

    ValueInteger* result = new ValueInteger();

    result->SetValue(size);

    return result;
}

string
CommandGetArraySize::GetDescription() const
{
    // ----> - - - - - - - - - [60 characters wide] - - - - - - - - - - <----
    return "No description available for command GetArraySize.";
}

#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)
