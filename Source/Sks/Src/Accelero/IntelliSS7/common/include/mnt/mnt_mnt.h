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
// LOG: Revision 1.1.1.1  2007/10/04 13:24:09  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:55  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:57  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:03  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2001/10/09 19:17:22  hdivoux
// LOG: Added GetArraySize command and allowed for empty arrays.
// LOG:
// LOG: Revision 5.2  2001/08/16 22:28:56  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:59  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.4  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/07 21:52:41  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:07:15  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_mnt.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $"

//
//
// mnt_mnt.h: MNT (Multi-Nodes Test Tool) class definition.
//
//


#if !defined(_MNT_MNT_H_)
#define _MNT_MNT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <mnt.h>

#include <stdarg.h>

#include <its_mutex.h>
#include <its_semaphore.h>
#include <its_thread.h>
#include <its_exception.h>

#include <gcs_client.h>

#include <mnt_options.h>
#include <mnt_command.h>
#include <mnt_interpreter.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
//  Mnt (Multi-Nodes Test Tool).
//

class Mnt
{
public:

    Mnt();

    // Default copy constructor not ok (see protected section).

    // Default assignment operator not ok (see protected section).

    virtual ~Mnt();

    ///////////////////////////////////////////////////////

    void SetOptions(const MntOptions& mntOptions);

    const MntOptions& GetOptions() const;

    MntOptions& GetOptions();

    ///////////////////////////////////////////////////////

    bool HasCommand(const std::string& name) const;

    void InsertCommand(Command* command);

    const Command& RetrieveCommand(const std::string& name) const;

    Command& RetrieveCommand(const std::string& name);

    void RemoveCommand(const std::string& name);

    ///////////////////////////////////////////////////////

    void InsertByteVariable(const std::string& name, unsigned char value);
    void InsertIntegerVariable(const std::string& name, long value);
    void InsertBooleanVariable(const std::string& name, bool value);
    void InsertStringVariable(const std::string& name, const std::string& value);

    ///////////////////////////////////////////////////////

    virtual int Run(int argc, const char** argv);

    ///////////////////////////////////////////////////////

    static its::Mutex& GetPrintLock();
    static void PrintInfo(const char* format, va_list argptr);
    static void PrintError(const char* format, va_list argptr);
    static void PrintDebug(const char* format, va_list argptr);

    ///////////////////////////////////////////////////////

    enum { MNT_MAX_NODES = 8 };

    void SetNodeNumber(size_t nodeNumber);
    size_t GetNodeNumber() const;

    void SetNumberOfNodes(size_t numberOfNodes);
    size_t GetNumberOfNodes() const;

    void SetNumberOfNodesSyncPoints(size_t numberOfNodesSyncPoints);
    size_t GetNumberOfNodesSyncPoints() const;

    ///////////////////////////////////////////////////////

    void SetNodesJoinPoint(its::Semaphore** nodesJoinPoint);
    its::Semaphore** GetNodesJoinPoint();

    void SetNodesSyncPoints(its::Semaphore*** nodesSyncPoints);
    its::Semaphore*** GetNodesSyncPoints();

    ///////////////////////////////////////////////////////

    GCS_MAILBOX* GetGcsMailbox();

    char* GetGcsConnectionName();

    char* GetGcsMemberName();

    its::Thread& GetGcsReceiver();

    void SetGcsReceiverStop(bool gcsReceiverStop);

protected:

    MntOptions _mntOptions;

    Interpreter _interpreter;

    static its::Mutex* _printLock;

    size_t _nodeNumber;
    size_t _numberOfNodes;
    size_t _numberOfNodesSyncPoints;

    its::Semaphore** _nodesJoinPoint;
    its::Semaphore*** _nodesSyncPoints;

    GCS_MAILBOX _gcsMailbox;
    char _gcsConnectionName[GCS_MAX_PRIVATE_NAME];
    char _gcsMemberName[GCS_MAX_GROUP_NAME];

    its::Thread _gcsReceiver;

    bool _gcsReceiverStop;

    static THREAD_RET_TYPE GcsReceive(void* arg);

    void GcsProcedureNodeSyncPointReached(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg);

    void GcsProcedureJoin(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg);

    void GcsProcedureLeave(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg);

    void GcsProcedureDisconnect(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg);

    void GcsProcedureNetworkChange(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg);

    size_t GcsMemberNameToNodeNumber(const char* memberName);

    void Usage();

    void PrintCommandHelp(const std::string& commandName);

    void PrintCommandList();

    void RunInBatchMode(const std::string& scriptFile);

    void RunInInteractiveMode();

    Mnt(const Mnt& rhs)
    :   _gcsReceiver(0, (ITS_THREAD_FUNC)GcsReceive)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
    }

    Mnt& 
    operator= (const Mnt& rhs)
    {
        bool must_not_be_used = false;
        ITS_ASSERT(must_not_be_used);
        return *this;
    }
};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_MNT_H_)
