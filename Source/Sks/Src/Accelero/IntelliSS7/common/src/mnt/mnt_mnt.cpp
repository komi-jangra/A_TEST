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
// LOG: Revision 6.3  2002/05/02 17:16:16  hdivoux
// LOG: Abort if too many receive errors.
// LOG:
// LOG: Revision 6.2  2002/04/29 20:42:23  hdivoux
// LOG: Added appName command line option for compatibility with Engine.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.7  2001/12/18 23:03:08  hdivoux
// LOG: Added gcsDaemonName command line option.
// LOG:
// LOG: Revision 5.6  2001/10/09 19:17:04  hdivoux
// LOG: Added GetArraySize command and allowed for empty arrays.
// LOG:
// LOG: Revision 5.5  2001/08/21 21:23:44  hdivoux
// LOG: Remove warning.
// LOG:
// LOG: Revision 5.4  2001/08/21 00:23:53  mmiers
// LOG: Warning removal
// LOG:
// LOG: Revision 5.3  2001/08/17 19:03:02  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 5.2  2001/08/16 22:28:56  hdivoux
// LOG: Update.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:08  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.7  2001/08/09 21:07:45  hdivoux
// LOG: Port to GNU g++.
// LOG:
// LOG: Revision 1.6  2001/08/09 21:03:15  hdivoux
// LOG: Port to GNU g++.
// LOG:
// LOG: Revision 1.5  2001/08/09 19:28:19  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.4  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
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

#ident "$Id: mnt_mnt.cpp,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

//
//
// mnt_mnt.cpp: MNT class implementation.
//
//


#include <mnt_mnt.h>
#include <mnt_messages.h>
#include <mnt_evaluator.h>
#include <mnt_exception.h>

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

///////////////////////////////////////////////////////////
//
// Global variables.
//

static const char* versionG = "1.0";


///////////////////////////////////////////////////////////////////////////////
//
// Mnt (Multi-Nodes Test Tool).
//

Mnt::Mnt()
:   _nodeNumber(0),
    _numberOfNodes(0),
    _numberOfNodesSyncPoints(0),
    _nodesJoinPoint(NULL),
    _nodesSyncPoints(NULL),
    _gcsMailbox(0),
    _gcsReceiver(0, (ITS_THREAD_FUNC)GcsReceive),
    _gcsReceiverStop(false)
{
    _printLock = new Mutex(0);
    memset(_gcsConnectionName, 0, GCS_MAX_PRIVATE_NAME);
    memset(_gcsMemberName, 0, GCS_MAX_GROUP_NAME);
}

Mnt::~Mnt()
{
    delete _printLock;
    _printLock = NULL;
}

void
Mnt::SetOptions(const MntOptions& mntOptions)
{
    _mntOptions = mntOptions;
}

const MntOptions& 
Mnt::GetOptions() const
{
    return _mntOptions;
}

MntOptions&
Mnt::GetOptions()
{
    return _mntOptions;
}

bool
Mnt::HasCommand(const string& name) const
{
    return _interpreter.HasCommand(name);
}

void
Mnt::InsertCommand(Command* command)
{
    ITS_REQUIRE(command != NULL);

    if (HasCommand(command->GetName()))
    {
        MNT_PRINT_ERROR((
            "Mnt::InsertCommand: detected duplicate command name: %s",
            command->GetName().c_str()));
        exit(EXIT_FAILURE);
    }

    ITS_ASSERT(!HasCommand(command->GetName()));

    _interpreter.InsertCommand(command);
}

const Command&
Mnt::RetrieveCommand(const string& name) const
{
    ITS_REQUIRE(HasCommand(name));

    return _interpreter.RetrieveCommand(name);
}

Command&
Mnt::RetrieveCommand(const string& name)
{
    ITS_REQUIRE(HasCommand(name));

    return _interpreter.RetrieveCommand(name);
}

void
Mnt::RemoveCommand(const string& name)
{
    ITS_REQUIRE(HasCommand(name));

    _interpreter.RemoveCommand(name);
}

void 
Mnt::InsertByteVariable(const string& name, unsigned char value)
{
    _interpreter.InsertVariable(name, new EvalByte(value));
}

void 
Mnt::InsertIntegerVariable(const string& name, long value)
{
    _interpreter.InsertVariable(name, new EvalInteger(value));
}

void 
Mnt::InsertBooleanVariable(const string& name, bool value)
{
    _interpreter.InsertVariable(name, new EvalBoolean(value));
}

void 
Mnt::InsertStringVariable(const string& name, const string& value)
{
    _interpreter.InsertVariable(name, new EvalString(value));
}

void
Mnt::Usage()
{
             // 80 characters wide <-->                                                    //
             ////////////////////////////////////////////////////////////////////////////////
             //                                                                            //

    cout << "\nUsage: mnt [-batch <script file>] [additional options] \n";
    cout << "\n";

    cout << "Additional options:\n";
    cout << "\n";

    cout << "   o [-help]\n\n";
    cout << "           Display this help and exit.\n\n\n";

    cout << "   o [-hCmd <command>]\n\n";
    cout << "           Display help for command.\n\n\n";

    cout << "   o [-hListCmds]\n\n";
    cout << "           Display list of all available commands.\n\n\n";

    cout << "   o [-internalDebug]\n\n";
    cout << "           Internal debug mode (print debug information).\n\n\n";

    cout << "   o [-internalParserDebug]\n\n";
    cout << "           Internal debug parser mode (print parser debug information).\n\n\n";

    cout << "   o [-gcsDaemonName <name>]\n\n";
    cout << "           Specify GCS Daemon Name (other than default).\n\n\n";

    cout << "   o [-appName <name>]\n\n";
    cout << "           For compatibility with Engine (ignored).\n\n\n";
    
    cout << "\n";
    cout << "\n";

    cout << "Multi-Nodes Test Tool (MNT) version ";
    cout << versionG;
    cout << ".\n";
    cout << "All rights reserved. (C) 2001 IntelliNet Technologies.\n";
    cout << "\n";
}

void 
Mnt::PrintCommandHelp(const string& commandName)
{
    if (HasCommand(commandName))
    {
        Command& command = RetrieveCommand(commandName);

        cout << "\n";
        cout << command.GetDescription().c_str();
        cout << "\n";
    }
    else
    {
        cout << "\n";
        cout << "Unknown command <" << commandName << ">.";
        cout << "\n";
    }
}

void 
Mnt::PrintCommandList()
{
    vector<string> commandNames = _interpreter.RetrieveCommandNames();

    if (commandNames.size() > 0)
    {
        cout << "\n";
    }

    for (size_t i = 0; i < commandNames.size(); i++)
    {
        cout << commandNames[i];
        cout << "\n";
    }
}

void 
Mnt::RunInBatchMode(const string& scriptFile)
{
    FILE* fDesc = NULL;

    fDesc = fopen(scriptFile.c_str(), "r");

    if (fDesc == NULL)
    {
        MNT_PRINT_ERROR((
            "Mnt::RunInBatchMode: unable to open file %s",
            scriptFile.c_str()));
        exit(EXIT_FAILURE);
    }
    
    try 
    {
        _interpreter.Execute(*this, fDesc);
    }
    catch (MntError& exc)
    {
        MNT_PRINT_ERROR((
            "Mnt::RunInBatchMode: %s - line: %d",
            exc.GetInformation().c_str(),
            exc.GetLineNumber()));
    }
    catch (GenericException& exc)
    {
        MNT_PRINT_ERROR((
            "Mnt::RunInBatchMode: execution failed - caught "
            "its::GenericException: %s",
            exc.GetDescription().c_str()));
        exit(EXIT_FAILURE);
    }
    catch (exception& exc)
    {
        exc = exc;
        MNT_PRINT_ERROR((
            "Mnt::RunInBatchMode: execution failed - caught C++ exception"));
        exit(EXIT_FAILURE);
    }

    fclose(fDesc);
}

void
Mnt::RunInInteractiveMode()
{
    string commandLine;
    commandLine.reserve(256);

    cout << "\n";
    cout << "/==========================================\\\n";
    cout << "| Multi-Nodes Test Tool (MNT)              |\n";
    cout << "|                                          |\n";
    cout << "| (C) 2001 IntelliNet Technologies.        |\n";
    cout << "\\==========================================/\n";
    cout << "\n";
    cout << "\n";
    cout << "Type '?<CR>' for help.\n";
    cout << "\n";
    cout << "\n";

    bool bStop = false;

    while (!bStop)
    {
        printf(">>> ");

        commandLine.erase(commandLine.begin(), commandLine.end());

        char c = '\0';

        while ((c = getchar()) != EOF && (c != '\n'))
        {
            commandLine.append(1, c);
        } 

        if (commandLine == "quit" || commandLine == "q")
        {
            bStop = true;
            continue;
        }
        else if (commandLine.size() >= 1 && commandLine[0] == '?')
        {
            if (commandLine.size() == 1)
            {
                cout << "\n";
                cout << "Type '?<CR>' for this help.\n";
                cout << "Type 'q<CR>' or 'quit<CR>' to quit.\n";
                cout << "Type '?all<CR>' for a list of all available commands.\n";
                cout << "Type '?<command><CR>' for a description of a specific command.\n";
                cout << "\n";
            }
            else
            {
                string commandName = commandLine.substr(1, string::npos);

                if (commandName == "all")
                {
                    cout << "\n";
                    cout << "List of all available commands:\n";
                    cout << "===============================\n";
                    PrintCommandList();
                    cout << "\n";
                }
                else
                {
                    PrintCommandHelp(commandName);
                    cout << "\n";
                }
            }

            continue;
        }
        else
        {
            // Nothing to do.
        }

        FILE* tmpDesc = tmpfile();

        if (tmpDesc == NULL)
        {
            MNT_PRINT_ERROR((
                "Mnt::RunInInteractiveMode: unable to open temporary file"));
            exit(EXIT_FAILURE);
        }

        int ret = fwrite(
                    commandLine.c_str(),
                    sizeof(char),
                    commandLine.size(),
                    tmpDesc);

        if ((size_t)ret != commandLine.size())
        {
            MNT_PRINT_ERROR((
                "Mnt::RunInInteractiveMode: error while writing to temporary "
                "file"));
            exit(EXIT_FAILURE);
        }

        ret = fseek(tmpDesc, 0, SEEK_SET);

        if (ret != 0)
        {
            MNT_PRINT_ERROR((
                "Mnt::RunInInteractiveMode: error while seeking in temporary "
                "file"));
            exit(EXIT_FAILURE);
        }

        try 
        {
            _interpreter.Execute(*this, tmpDesc);
        }
        catch (MntError& exc)
        {
            MNT_PRINT_ERROR((
                "Mnt::RunInInteractiveMode: %s - line: %d",
                exc.GetInformation().c_str(),
                exc.GetLineNumber()));
        }
        catch (GenericException& exc)
        {
            MNT_PRINT_ERROR((
                "Mnt::RunInInteractiveMode: execution failed - caught "
                "its::GenericException: %s",
                exc.GetDescription().c_str()));
            exit(EXIT_FAILURE);
        }
        catch (exception& exc)
        {
            exc = exc;
            MNT_PRINT_ERROR((
                "Mnt::RunInInteractiveMode: execution failed - caught C++ "
                "exception"));
            exit(EXIT_FAILURE);
        }

        fclose(tmpDesc);
    }
}

int
Mnt::Run(int argc, const char** argv)
{
    string scriptFileOptArg;
    string commandNameOptArg;
    string gcsDaemonNameOptArg;
    
    bool bBatch                 = false;
    bool bHelpCommand           = false;
    bool bHelpListCommands      = false;
    bool bInternalDebug         = false;
    bool bInternalParserDebug   = false;
    bool bGcsDaemonName         = false;

    // Parse command line argument(s).

    for (int currArg = 1; currArg < argc;)
    { 
        if (argv[currArg][0] == '-' && argv[currArg][1] != '\0')
        {
            if (strcmp(argv[currArg], "-batch") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else
                {
                    scriptFileOptArg = argv[currArg + 1];
                    bBatch = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-help") == 0)
            {
                Usage();
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(argv[currArg], "-hCmd") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else
                {
                    commandNameOptArg = argv[currArg + 1];
                    bHelpCommand = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-hListCmds") == 0)
            {
                bHelpListCommands = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-internalDebug") == 0)
            {
                bInternalDebug = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-internalParserDebug") == 0)
            {
                bInternalParserDebug = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-gcsDaemonName") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else
                {
                    gcsDaemonNameOptArg = argv[currArg + 1];
                    bGcsDaemonName = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-appName") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage();
                    exit(EXIT_FAILURE);
                }
                else
                {
                    // For compatibility with Engine (ignore).
                    currArg += 2;
                }
            }
            else 
            {
                Usage();
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            Usage();
            exit(EXIT_FAILURE);
        }
    }

    // Non-exclusive options.
    if (bInternalDebug)
    {
        _mntOptions.SetDebugOn();
    }

    if (bInternalParserDebug)
    {
        _mntOptions.SetParserDebugOn();
    }

    if (bGcsDaemonName)
    {
        _mntOptions.SetGcsDaemonName(gcsDaemonNameOptArg);
    }

    // Exclusive options.
    if (bHelpCommand)
    {
        PrintCommandHelp(commandNameOptArg);
        exit(EXIT_SUCCESS);
    }
    else if (bHelpListCommands)
    {
        PrintCommandList();
        exit(EXIT_SUCCESS);
    }
    else if (bBatch)
    {
        RunInBatchMode(scriptFileOptArg);
    }
    else
    {
        RunInInteractiveMode();
    }



    return EXIT_SUCCESS;
}

Mutex& 
Mnt::GetPrintLock()
{
    ITS_ASSERT(_printLock != NULL);
    return *_printLock;
}

void 
Mnt::PrintInfo(const char* format, va_list argptr)
{
    _printLock->Acquire();
    printf("\n ---- MNT Info [");
    vprintf(format, argptr);
    printf("].\n\n");
    _printLock->Release();
}

void 
Mnt::PrintDebug(const char* format, va_list argptr)
{
    MntOptions mntOptions;

    if (mntOptions.IsDebugOn())
    {
        _printLock->Acquire();
        printf("\n ---- MNT Debug [");
        vprintf(format, argptr);
        printf("].\n\n");
        _printLock->Release();
    }
}

void 
Mnt::PrintError(const char* format, va_list argptr)
{
    _printLock->Acquire();
    printf("\n ---- MNT Error [");
    vprintf(format, argptr);
    printf("].\n\n");
    _printLock->Release();
}

void
Mnt::SetNodeNumber(size_t nodeNumber)
{
    ITS_REQUIRE(nodeNumber < MNT_MAX_NODES);
    _nodeNumber = nodeNumber;
}

size_t
Mnt::GetNodeNumber() const
{
    return _nodeNumber;
}

void 
Mnt::SetNumberOfNodes(size_t numberOfNodes)
{
    ITS_REQUIRE(numberOfNodes < MNT_MAX_NODES);
    _numberOfNodes = numberOfNodes;
}

size_t
Mnt::GetNumberOfNodes() const
{
    return _numberOfNodes;
}

void
Mnt::SetNumberOfNodesSyncPoints(size_t numberOfNodesSyncPoints)
{
    _numberOfNodesSyncPoints = numberOfNodesSyncPoints;
}

size_t
Mnt::GetNumberOfNodesSyncPoints() const
{
    return _numberOfNodesSyncPoints;
}

void 
Mnt::SetNodesJoinPoint(its::Semaphore** nodesJoinPoint)
{
    _nodesJoinPoint = nodesJoinPoint;
}

its::Semaphore**
Mnt::GetNodesJoinPoint()
{
    return _nodesJoinPoint;
}

void 
Mnt::SetNodesSyncPoints(its::Semaphore*** nodesSyncPoints)
{
    _nodesSyncPoints = nodesSyncPoints;
}

its::Semaphore*** 
Mnt::GetNodesSyncPoints()
{
    return _nodesSyncPoints;
}

GCS_MAILBOX*
Mnt::GetGcsMailbox()
{
    return &_gcsMailbox;
}

char* 
Mnt::GetGcsConnectionName()
{
    return _gcsConnectionName;    
}

char* 
Mnt::GetGcsMemberName()
{
    return _gcsMemberName;
}

Thread&
Mnt::GetGcsReceiver()
{
    return _gcsReceiver;
}

void 
Mnt::SetGcsReceiverStop(bool gcsReceiverStop)
{
    _gcsReceiverStop = gcsReceiverStop;
}

THREAD_RET_TYPE 
Mnt::GcsReceive(void* arg)
{
    ITS_REQUIRE(arg != NULL);

    Mnt* obj = static_cast<Mnt*>(arg);

    static char msg[MNT_MAX_MSG_SIZE];
    GCS_SERVICE service = 0;
    char        sender[GCS_MAX_GROUP_NAME];
    char        groups[MNT_MAX_NODES + 4][GCS_MAX_GROUP_NAME];
    int         maxGroups = MNT_MAX_NODES + 4;
    int         numGroups = 0;
    short       msgType = 0;
    int         endianMismatch = 0;
    int         maxReceiveErrors = 8;
    int         receiveErrors = 0;

    while (!obj->_gcsReceiverStop)
    {
        // Blocking call (not anymore if disconnection).
        int ret = GCS_Receive(
                obj->_gcsMailbox,
                &service,
                sender,
                maxGroups,
                &numGroups,
                groups,
                &msgType,
                &endianMismatch,
                MNT_MAX_MSG_SIZE,
                msg);
        if (ret < 0)
        {
            if (ret == GCS_GROUPS_TOO_SHORT)
            {
                if (!obj->_gcsReceiverStop)
                {
                    MNT_PRINT_ERROR((
                        "Mnt::GcsReceive: GCS_Received failed - groups buffer "
                        "too short: %d\n",
                        ret));

                    receiveErrors++;
                    if (receiveErrors >= maxReceiveErrors)
                    {
                        MNT_PRINT_ERROR((
                            "Mnt::GcsReceive: too many receive errors - "
                            "abort\n"));

                        abort();
                    }
                }
            }
            else if (ret == GCS_BUFFER_TOO_SHORT)
            {
                if (!obj->_gcsReceiverStop)
                {
                    MNT_PRINT_ERROR((
                        "Mnt::GcsReceive: GCS_Received failed - message buffer"
                        " too short: %d\n",
                        ret));

                    receiveErrors++;
                    if (receiveErrors >= maxReceiveErrors)
                    {
                        MNT_PRINT_ERROR((
                            "Mnt::GcsReceive: too many receive errors - "
                            "abort\n"));

                        abort();
                    }
                }
            }
            else
            {
                if (!obj->_gcsReceiverStop)
                {
                    MNT_PRINT_ERROR((
                        "Mnt::GcsReceive: GCS_Receive failed: %d\n",
                        ret));
                }

                receiveErrors++;
                if (receiveErrors >= maxReceiveErrors)
                {
                    MNT_PRINT_ERROR((
                        "Mnt::GcsReceive: too many receive errors - abort\n"));

                    abort();
                }
            }
        }
        else
        {
            ITS_ASSERT(ret >= 0);

            if (GCS_IsRegularMsg(service))
            {
                if (obj->GetOptions().IsDebugOn())
                {
                    static char serviceStr[32];

                    if (GCS_IsUnreliableMsg(service))
                    {
                        strcpy(serviceStr, "UNRELIABLE");
                    }
                    else if (GCS_IsReliableMsg(service))
                    {
                        strcpy(serviceStr, "RELIABLE");
                    }
                    else if (GCS_IsFifoMsg(service))
                    {
                        strcpy(serviceStr, "FIFO");
                    }
                    else if (GCS_IsCausalMsg(service))
                    {
                        strcpy(serviceStr, "CAUSAL");
                    }
                    else if (GCS_IsAgreedMsg(service))
                    {
                        strcpy(serviceStr, "AGREED");
                    }
                    else if (GCS_IsSafeMsg(service))
                    {
                        strcpy(serviceStr, "SAFE");
                    }
                    else
                    {
                        bool must_not_be_reached = false;
                        strcpy(serviceStr, "UNKNOWN");
                        ITS_ASSERT(must_not_be_reached);
                    }


                    MNT_PRINT_DEBUG((
                        "Mnt::GcsReceive: received %s regular message "
                        "from %s - "
                        "type: %s - "
                        "endian: %d - "
                        "number of groups: %d - "
                        "size: %d",
                        serviceStr,
                        sender,
                        msgType,
                        endianMismatch,
                        numGroups,
                        ret));
                }

                switch (msgType)
                {
                case MNT_MSG_NODE_SYNC_POINT_REACHED:

                    obj->GcsProcedureNodeSyncPointReached(
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        msg);

                    break;

                default:
                    {
                        bool must_not_be_reached = false;
                        ITS_ASSERT(must_not_be_reached);
                    }
                }
            }
            else if (GCS_IsMembershipMsg(service))
            {
                if (GCS_IsRegMembMsg(service))
                {
                    int numBytes = 0;
                    GCS_GROUP_ID* groupId;
                    int* numVs;
                    char* vsMembers;

                    groupId = (GCS_GROUP_ID*)&msg[numBytes];
                    numBytes += sizeof(GCS_GROUP_ID);
                    numVs = (int*)&msg[numBytes];
                    numBytes += sizeof(ITS_INT);
                    vsMembers = &msg[numBytes];

                    if (obj->GetOptions().IsDebugOn())
                    {
                        MNT_PRINT_DEBUG((
                            "Mnt::GcsReceive: received REGULAR membership message for "
                            "group: %s - "
                            "number of members: %d - "
                            "I am member: %d\n",
                            sender,
                            numGroups,
                            msgType));

                        static char infoStr[1024];
                        strcpy(
                            infoStr, 
                            "Mnt::GcsReceive: membership message list of "
                            "members:\n");

                        for (int i = 0; i < numGroups; i++)
                        {
                            strcat(infoStr, "\t");
                            strcat(infoStr, groups[i]);
                            strcat(infoStr, "\n");
                        }

                        ITS_ASSERT(strlen(infoStr) < 1024);

                        MNT_PRINT_DEBUG(("%s", infoStr));

                        MNT_PRINT_DEBUG((
                            "Mnt::GcsReceive: membership message group id: "
                            "%d %d %d\n",
                            groupId->id[0],
                            groupId->id[1],
                            groupId->id[2]));
                    }

                    if (GCS_IsCausedJoinMsg(service))
                    {
                        MNT_PRINT_DEBUG((
                            "Mnt::GcsReceive: membership message due to JOIN "
                            "of %s\n",
                            vsMembers));

                        obj->GcsProcedureJoin(
                            service,
                            sender,
                            numGroups,
                            groups,
                            ret,
                            msg);
                    }
                    else if (GCS_IsCausedLeaveMsg(service))
                    {
                        MNT_PRINT_DEBUG((
                            "Mnt::GcsReceive: membership message due to LEAVE "
                            "of %s\n",
                            vsMembers));

                        obj->GcsProcedureLeave(
                            service,
                            sender,
                            numGroups,
                            groups,
                            ret,
                            msg);
                    }
                    else if (GCS_IsCausedDisconnectMsg(service))
                    {
                        MNT_PRINT_DEBUG((
                            "Mnt::GcsReceive: membership message due to "
                            "DISCONNECT of %s\n",
                            vsMembers));

                        obj->GcsProcedureDisconnect(
                            service,
                            sender,
                            numGroups,
                            groups,
                            ret,
                            msg);
                    }
                    else if (GCS_IsCausedNetworkMsg(service))
                    {   
                        MNT_PRINT_DEBUG((
                            "Mnt::GcsReceive: membership message due to "
                            "NETWORK change\n"));

                        if (obj->GetOptions().IsDebugOn())
                        {
                            static char infoStr[1024];

                            sprintf(
                                infoStr, 
                                "Mnt::GcsReceive: membership message due to "
                                "NETWORK change has %d VS members:\n", 
                                *numVs);

                            for (int i = 0; 
                                 i < *numVs;
                                 i++, vsMembers += GCS_MAX_GROUP_NAME)
                            {
                                strcat(infoStr, "\t");
                                strcat(infoStr, vsMembers);
                                strcat(infoStr, "\n");
                            }

                            ITS_ASSERT(strlen(infoStr) < 1024);

                            MNT_PRINT_DEBUG(("%s", infoStr));
                        }

                        obj->GcsProcedureNetworkChange(
                            service,
                            sender,
                            numGroups,
                            groups,
                            ret,
                            msg);                    
                    }
                    else
                    {
                        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                        ITS_ASSERT(must_not_be_reached);
                    }
                }
                else if (GCS_IsTransitionMsg(service))
                {
                    MNT_PRINT_DEBUG((
                        "Mnt::GcsReceive: received TRANSITIONAL membership "
                        "message for group %s\n",
                        sender));
                }
                else if (GCS_IsCausedLeaveMsg(service))
                {
                    int numBytes = 0;
                    GCS_GROUP_ID* groupId;
                    ITS_INT* numVs;
                    char* vsMembers;

                    groupId = (GCS_GROUP_ID*)&msg[numBytes];
                    numBytes += sizeof(GCS_GROUP_ID);
                    numVs = (ITS_INT*)&msg[numBytes];
                    numBytes += sizeof(ITS_INT);
                    vsMembers = &msg[numBytes];

                    MNT_PRINT_DEBUG((
                        "Mnt::GcsReceive: received self-leave membership "
                        "message for group: %s - I am leaving member: %s\n",
                        sender,
                        obj->_gcsMemberName));

                    MNT_PRINT_DEBUG((
                        "Mnt::GcsReceive: membership message (non-regular) "
                        "due to self-leave of: %s\n",
                        obj->_gcsMemberName));

                    obj->GcsProcedureLeave(
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        msg);
                }
                else
                {
                    MNT_PRINT_ERROR((
                        "Mnt::GcsReceive: received invalid membership message "
                        "of type 0x%X\n",
                        service));
                }
            }
            else if (GCS_IsRejectMsg(service))
            {
                MNT_PRINT_DEBUG((
                    "Mnt::GcsReceive: received REJECTED message from: %s - "
                    "service: 0x%X - "
                    "type: %d - "
                    "number of groups: %d - "
                    "size: %d\n",
                    sender,
                    service,
                    msgType,
                    endianMismatch,
                    numGroups,
                    ret));
            }
            else
            {
                MNT_PRINT_ERROR((
                    "Mnt::GcsReceive: receive unknown message from: %s - "
                    "service (unknown): 0x%X - "
                    "size: %d\n",
                    sender,
                    service,
                    ret));
            }
        }
    }

    THREAD_NORMAL_EXIT;
}

void 
Mnt::GcsProcedureNodeSyncPointReached(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg)
{
    ITS_REQUIRE(GCS_IsRegularMsg(service));
    ITS_REQUIRE(size >= sizeof(MntMsg));

    MntMsg* nodeSyncPointReachedMsg = (MntMsg*)msg;

    ITS_REQUIRE(
        nodeSyncPointReachedMsg->discriminator = 
            MNT_MSG_NODE_SYNC_POINT_REACHED);

    size_t nodeNumber = 
            nodeSyncPointReachedMsg->
                u.nodeSyncPointReached.nodeNumber;

    size_t syncPointNumber =
            nodeSyncPointReachedMsg->
                u.nodeSyncPointReached.syncPointNumber;

    ITS_ASSERT(nodeNumber < _numberOfNodes);
    ITS_ASSERT(syncPointNumber < _numberOfNodesSyncPoints);

    Semaphore* semaphore = _nodesSyncPoints[nodeNumber][syncPointNumber];

    ITS_ASSERT(semaphore != NULL);

    semaphore->Post();
}

void 
Mnt::GcsProcedureJoin(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg)
{
    ITS_REQUIRE(GCS_IsMembershipMsg(service));
    ITS_REQUIRE(GCS_IsCausedJoinMsg(service));

    int numBytes = 0;
    GCS_GROUP_ID* groupId;
    int* numMembers;
    char* joiningMemberName;

    groupId = (GCS_GROUP_ID*)&msg[numBytes];
    numBytes += sizeof(GCS_GROUP_ID);
    numMembers = (int*)&msg[numBytes];
    numBytes += sizeof(int);
    joiningMemberName = &msg[numBytes];

    size_t joiningNodeNumber = GcsMemberNameToNodeNumber(joiningMemberName);

    ITS_ASSERT(joiningNodeNumber < _numberOfNodes);

    Semaphore* semaphore = _nodesJoinPoint[joiningNodeNumber];

    ITS_ASSERT(semaphore != NULL);

    semaphore->Post();

    if (strcmp(joiningMemberName, _gcsMemberName) == 0)
    {
        // Join message to self. Need to post join point semaphores for all
        // other members already in group.

        for (int i = 0; i < numGroups; i++)
        {
            if (strcmp(joiningMemberName, groups[i]) != 0)
            {
                size_t alreadyMemberNodeNumber = 
                            GcsMemberNameToNodeNumber(groups[i]);

                ITS_ASSERT(alreadyMemberNodeNumber < _numberOfNodes);

                Semaphore* 
                    semaphore = 
                        _nodesJoinPoint[alreadyMemberNodeNumber];

                ITS_ASSERT(semaphore != NULL);

                semaphore->Post();
            }
        }
    }
}

void 
Mnt::GcsProcedureLeave(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg)
{
    // Nothing to do.
}

void 
Mnt::GcsProcedureDisconnect(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg)
{
    // Nothing to do.
}

void 
Mnt::GcsProcedureNetworkChange(
             GCS_SERVICE service,
             char sender[GCS_MAX_GROUP_NAME],
             int numGroups,
             char groups[][GCS_MAX_GROUP_NAME],
             size_t size,
             char* msg)
{
    // Nothing to do.
}

size_t 
Mnt::GcsMemberNameToNodeNumber(const char* memberName)
{
    // 
    // MemberName format is "#s1d#s2" where:
    // '#'              = number sign character.
    // s1 (string)      = connectionNameRoot.
    // d  (integer)     = nodeId.
    // '#'              = number sign character.
    // s2 (string)      = IP associated name (in configuration).
    //

    ITS_REQUIRE(memberName != NULL);
    ITS_REQUIRE(strlen(memberName) > 0);

    // Find connectionNameRoot substring.
    char* ptr = (char*)strstr(
                        memberName, 
                        _mntOptions.GetGcsConnectionNameRoot().c_str());
    if (ptr == NULL || strlen(ptr) == 0)
    {
        return (size_t)(-1);
    }

    ptr += strlen(_mntOptions.GetGcsConnectionNameRoot().c_str());

    // Retrieve nodeId.
    size_t d = 0;
    int ret = sscanf(ptr, "%d", &d);
    if (ret != 1)
    {
        return (size_t)(-1);
    }

    return d;
}

Mutex* Mnt::_printLock = NULL;


///////////////////////////////////////////////////////////////////////////////
//
//  MntOptions.
//

bool MntOptions::_debug = false;


///////////////////////////////////////////////////////////////////////////////
//
//  Print related functions.
//

void 
PrintInfo(const char* format, ...)
{
    va_list alist;
    va_start(alist, format);
    Mnt::PrintInfo(format, alist);
    va_end(alist);
}

void 
PrintDebug(const char* format, ...)
{
    va_list alist;
    va_start(alist, format);
    Mnt::PrintDebug(format, alist);
    va_end(alist);
}

void 
PrintError(const char* format, ...)
{
    va_list alist;
    va_start(alist, format);
    Mnt::PrintError(format, alist);
    va_end(alist);
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


