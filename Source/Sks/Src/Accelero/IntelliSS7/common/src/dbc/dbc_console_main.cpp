////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:58  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:07  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.3  2005/03/21 13:51:22  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.3  2002/06/04 19:58:00  mmiers
// LOG: Debugging.
// LOG:
// LOG: Revision 6.2  2002/05/17 20:42:19  hdivoux
// LOG: Update for new FT/HA.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.2  2001/06/19 21:44:57  mmiers
// LOG: GNU cpp > 3.0 can handle real stdc++
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.5  2001/03/06 22:10:46  mmiers
// LOG: Tweaks.
// LOG:
// LOG: Revision 3.4  2001/03/06 02:28:38  mmiers
// LOG: Add dynamic link lib.  Straighten out include order.  Remove instance
// LOG: of CORE++.
// LOG:
// LOG: Revision 3.3  2001/02/15 15:58:23  mmiers
// LOG: Ident
// LOG:
// LOG: Revision 3.2  2000/08/18 13:59:28  mmiers
// LOG: Remove stubs files.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:04:54  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.5  2000/08/04 21:45:31  rsonak
// LOG:
// LOG: Removed its_ss7_stubs.h
// LOG:
// LOG: Revision 2.4  2000/08/03 14:19:38  hdivoux
// LOG: Update for removing #include its_ss7_stubs.h.
// LOG:
// LOG: Revision 2.3  2000/06/13 19:15:56  mmiers
// LOG:
// LOG: C++ assertion no longer throws exception by default.
// LOG:
// LOG: Revision 2.2  2000/02/02 16:36:20  mmiers
// LOG:
// LOG: No more stubs.
// LOG:
// LOG: Revision 2.1  1999/12/16 02:19:19  mmiers
// LOG:
// LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
// LOG: though.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:27:13  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.10  1999/11/15 16:30:45  mmiers
// LOG:
// LOG:
// LOG: Build on Solaris with g++
// LOG:
// LOG: Revision 1.9  1999/10/12 19:45:15  mmiers
// LOG:
// LOG:
// LOG: Workarounds for HPUX.
// LOG:
// LOG: Revision 1.8  1999/09/03 20:15:33  labuser
// LOG:
// LOG:
// LOG: Remove system("cp"); we don't need to do that anymore, our
// LOG: resource database is smarter now.
// LOG:
// LOG: Revision 1.7  1999/08/27 21:54:53  mmiers
// LOG:
// LOG:
// LOG: Remove namespace name.
// LOG:
// LOG: Revision 1.6  1999/07/16 21:25:45  mmiers
// LOG:
// LOG:
// LOG: Wrong define.  Check for ITS_STD_NAMESPACE instead.
// LOG:
// LOG: Revision 1.5  1999/07/16 21:23:15  mmiers
// LOG:
// LOG:
// LOG: Update to work on UNIX.
// LOG:
// LOG: Revision 1.4  1999/07/14 19:52:35  hdivoux
// LOG: Improved synchronization for dbc client and console.
// LOG:
// LOG: Revision 1.3  1999/07/12 23:38:21  hdivoux
// LOG: Work in progress.
// LOG:
// LOG: Revision 1.2  1999/07/09 23:39:56  hdivoux
// LOG: General update for improved version.
// LOG:
// LOG: Revision 1.1  1999/07/02 16:56:20  mmiers
// LOG:
// LOG:
// LOG: Make this look like other subsystems to automate the NT build.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
// DBC console.
//

#if defined(HPUX)
#include <iostream/fstream.h>
#include <iostream/iostream.h>
#include <iostream/strstream.h>
#else
#include <iostream>
#include <strstream>
#include <fstream>
#endif
#include <string>
#include <its++.h>
#include <its_app.h>
#include <its_exception.h>
#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_dsm.h>
#include <its_statics.cpp>

#ident "$Id: dbc_console_main.cpp,v 1.1.1.1 2007-10-08 11:11:43 bsccs2 Exp $"

//
// work around polluted namespace on HPUX
//
#if defined(HPUX)
#undef open
#undef close
#endif

#include <dbc_client.h>


#if defined(ITS_NAMESPACE)
namespace its
{
#endif // defined(ITS_NAMESPACE)

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif // defined(ITS_STD_NAMESPACE)


static const int DBC_NUMBER_THREAD   = 1;
static const int DBC_THREAD_INSTANCE = 1;

static bool globalStartSuccess  = false;
static bool bFifoG              = false;
static bool bSocketG            = false;

#if defined(WIN32)

BOOL WINAPI
ControlHandler(DWORD dwCtrlType)
{
    switch(dwCtrlType)
    {
    case CTRL_BREAK_EVENT:  
    case CTRL_C_EVENT:

        if (globalStartSuccess)
        {
            ITS_GlobalStop();
        }

        exit(EXIT_SUCCESS);
    }

    return FALSE;
}

#else // !defined(WIN32)

int
SigQuit(int signal)
{
    exit(EXIT_SUCCESS);

    // Not reached.

    return 0;
}

#endif // defined(WIN32)

//
//  Shared information.
//

class Shared
{
public:

    //
    //  Shared DBC Client.
    //

    static bool
    IsDbcClientNotNull()
    { return dbcClient != NULL; }

    static DbcClient*
    GetDbcClient()
    {
        ITS_REQUIRE(IsDbcClientNotNull());

        return dbcClient;
    }

    static void
    SetDbcClient(DbcClient* dbcClientParam)
    {
        ITS_REQUIRE(dbcClientParam != NULL);

        dbcClient = dbcClientParam;
    }

    static void
    ResetDbcClient()
    { dbcClient = NULL; }


protected:

    static ITS_ThreadPool* workerPool;

    static DbcClient* dbcClient;
};

//
//  Shared information static member definition.
//

DbcClient* Shared::dbcClient = NULL;


//
// Single thread pool class and member functions.
//

class DbcThreadPool : public ITS_ThreadPool
{
public:

    DbcThreadPool()
        : ITS_ThreadPool()
    {};

    virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize);

    static void DbcThreadFunction(ITS_ThreadPoolThread* thr, void* arg);    
};


//
//  To create the unique thread in the pool thread (redefined virtual member
//  function).
//

ThreadPoolThread*
DbcThreadPool::CreatePoolThread(int stackSize)
{
    ITS_Worker* result = NULL;

    // The third argument of ITS_Worker constructor initialize the instance
    // attribute of the ITS_Worker object. It also identifies the transport
    // object associated with the ITS_Worker object.

    if (bSocketG)
    {
        result = new ITS_Worker(stackSize, "debug_console",
                            DBC_THREAD_INSTANCE,
                            ITS_TRANSPORT_CSOCKET |
                            ITS_TRANSPORT_DELAY_CREATE);
    }
    else if (bFifoG)
    {
         result = new ITS_Worker(stackSize, "debug_console",
                            DBC_THREAD_INSTANCE,
                            ITS_TRANSPORT_FIFO |
                            ITS_TRANSPORT_DELAY_CREATE);
    }
    else
    {
        bool must_not_be_reached = false;

        ITS_THROW_ASSERT(must_not_be_reached);
    }

    ITS_ENSURE(result != NULL);

    return (ThreadPoolThread *)result;
}



void
DbcThreadPool::DbcThreadFunction(ITS_ThreadPoolThread* thr, void* arg)
{
    ITS_REQUIRE(thr != NULL);
    ITS_REQUIRE(arg != NULL);

    ITS_Worker* worker = (ITS_Worker *)thr;
    DbcClient* dbcClient = reinterpret_cast<DbcClient*>(arg);
    ITS_Event event;
    ITS_HANDLE handle = NULL;
    bool itsInitSuccess = false;

    try
    {
        handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

        ITS_THROW_ASSERT(handle != NULL); // Fatal error if handle == NULL.

        itsInitSuccess = true;

        dbcClient->SetWorker(worker);

        //
        //  To signal synchronization point that worker is set.
        //

        dbcClient->SynchronizationRelease();

        dbcClient->ProcessCommandsResult();

        ITS_Terminate(handle);

        // No exception handled.

        dbcClient->ResetWorker();

        return;
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();

        cerr << endl;
        cerr << exc.GetDescription().c_str();
        cerr << endl;
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

        cerr << endl;
        cerr << standardExc.GetDescription().c_str();
        cerr << endl;
    }

#if defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();

        cerr << endl;
        cerr << unknownExc.GetDescription().c_str();
        cerr << endl;

        dbcClient->ResetWorker();

        exit(EXIT_FAILURE);
    }

#endif  // defined(NDEBUG)

    // Reached only if an exception has occurred.

    if (itsInitSuccess)
    { 
        ITS_Terminate(handle);
    }

    dbcClient->ResetWorker();

    cerr << endl;
    cerr << "(!) Fatal Error - exception (see previously).";
    cerr << endl;

    exit(EXIT_FAILURE);

    // Not reached.

    return;
}


void
Usage(const string& prgName)
{
    string strippedPrgName;

    string::size_type pos = prgName.find_last_of("\\/"); 

    if (pos == string::npos)
    {
        strippedPrgName = prgName;
    }
    else
    {
        strippedPrgName = prgName.substr(pos + 1);
    }

             ////////////////////////////////////////////////////////////////////////////////

    cerr << "\nUsage: " << strippedPrgName.c_str() << " [Options]\n";
    cerr << "\n";
    cerr << "Options:\n";
    cerr << "\n";
    cerr << "   [-socket | -fifo]\n";
    cerr << "\n";
    cerr << "     - [-socket]               Use socket transport (fifo is default).\n";
    cerr << "     - [-fifo]                 Use fifo transport (default).\n";
    cerr << "\n";
    cerr << "\n";
    cerr << "   [-configDir <name> | -configFile <name> | -appName <name> ]\n";
    cerr << "\n";
    cerr << "     - [-configDir <name>]     Specify configuration directory.\n";
    cerr << "     - [-configFile <name>]    Specify configuration file.\n";
    cerr << "     - [-appName <name>]       Specify application name (config file basename).\n";
    cerr << "\n";
    cerr << "\n";
    cerr << "   [-cmdFile <name> | -cmdLine <line> | -cmdStdin]\n";
    cerr << "\n";
    cerr << "     - [-cmdFile <name>]       Specify a command file (stdin is default).\n";
    cerr << "     - [-cmdLine <line>]       Specify a command line (stdin is default).\n";
    cerr << "     - [-cmdStdin]             Specify standard input for commands (default).\n";
    cerr << "\n";
    cerr << "\n";
    cerr << "   [-interactive | -nonInteractive]\n";
    cerr << "\n";
    cerr << "     - [-interactive]          Force interactive mode.\n";
    cerr << "     - [-nonInteractive]       Force non-interactive mode.\n";
    cerr << "\n";
    cerr << "\n";
    cerr << "   [-h]                        Display this help and exit.\n";
    cerr << "\n";
    cerr << "\n";
    cerr << "- If option [-configDir <name>] is chosen, the configuration directory\n";
    cerr << "  must contain a configuration file named \"dbc_console.ini\".\n";
    cerr << "- If options [-configDir <name>] and [-configFile <name>] are not used\n";
    cerr << "  Debug Console checks to see if the environment variable ISS7_CONFIG_DIR\n";
    cerr << "  is set. If set, then the value of that variable is used as the\n";
    cerr << "  configuration directory name. If not set, Debug Console searches the\n";
    cerr << "  working directory for a configuration file named \"dbc_console.ini\".\n";
    cerr << "- If option [-cmdLine <line>] is chosen, the line of command(s) must be\n";
    cerr << "  between quotes if necessary (i.e. if it includes white spaces).\n";
    cerr << "- By default interactive mode is selected only if standard input is\n";
    cerr << "  specified.\n";
    cerr << "\n";
    cerr << "\n";
}


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)


#if defined(ITS_NAMESPACE)
using namespace its;
#endif // defined(ITS_NAMESPACE)

int
main(int argc, char* argv[])
{
    // Genaral message before starting.

    cerr << endl;
    cerr << "IntelliSS7 Debug Console (DBC) version 1.1."
         << endl;
    cerr << "(C) 1999 IntelliNet Technologies." 
         << endl;
    cerr << endl;

    // Parse command line.

    if (argc > 7)
    {
        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    bool bSocket                = false;
    bool bFifo                  = false;

    bool bConfigDirPresent      = false;
    bool bConfigFilePresent     = false;
    bool bCmdFilePresent        = false;
    bool bCmdLinePresent        = false;
    bool bCmdStdinPresent       = false;
    bool bForceInteractive      = false;
    bool bForceNonInteractive   = false;

    string configDir;
    string configFile;
    string cmdFile;
    string cmdLine;

    //
    // Set default IntelliSS7 Application name.
    //

    ITS_Application::SetName("dbc_console");

    // Parse command line arguments.

    for (int currArg = 1; currArg < argc;)
    { 
        if (argv[currArg][0] == '-' && argv[currArg][1] != '\0')
        {
            if (strcmp(argv[currArg], "-h") == 0)
            {
                Usage(argv[0]);
                exit(EXIT_SUCCESS);
            }
            if (strcmp(argv[currArg], "-socket") == 0)
            {
                if (bFifo)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bSocket = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-fifo") == 0)
            {
                if (bSocket)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bFifo = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-appName") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    ITS_Application::SetName(argv[currArg + 1]);
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-configDir") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (bConfigFilePresent)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    configDir = argv[currArg + 1];
                    bConfigDirPresent = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-configFile") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (bConfigDirPresent)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    configFile = argv[currArg + 1];
                    bConfigFilePresent = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cmdFile") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (bCmdLinePresent || bCmdStdinPresent)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cmdFile = argv[currArg + 1];
                    bCmdFilePresent = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cmdLine") == 0)
            {
                if (currArg == argc - 1)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (argv[currArg + 1][0] == '-')
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else if (bCmdFilePresent || bCmdStdinPresent)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    cmdLine = argv[currArg + 1];
                    bCmdLinePresent = true;
                    currArg += 2;
                }
            }
            else if (strcmp(argv[currArg], "-cmdStdin") == 0)
            {
                if (bCmdFilePresent || bCmdLinePresent)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bCmdStdinPresent = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-interactive") == 0)
            {
                if (bForceNonInteractive)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bForceInteractive = true;
                    currArg++;
                }
            }
            else if (strcmp(argv[currArg], "-nonInteractive") == 0)
            {
                if (bForceInteractive)
                {
                    Usage(argv[0]);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    bForceNonInteractive = true;
                    currArg++;
                }
            }
            else 
            {
                Usage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            Usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Set default options.

    if (!bSocket && !bFifo)
    {
        bFifo = true;
    }

    if (!bCmdFilePresent && !bCmdLinePresent && !bCmdStdinPresent)
    {
        bCmdStdinPresent = true;
    }

    // Set option global variables.

    bFifoG      = bFifo;
    bSocketG    = bSocket;

    if (bConfigDirPresent)
    {
        ITS_Application::SetConfigDir(const_cast<char*> (configDir.c_str()));
    }
    else if (bConfigFilePresent)
    {
        ITS_Application::SetConfigFileName(configFile.c_str());
    }
    else
    {
        // Nothing to do.
    }


    // 
    // The exception log and event log objects MUST always be created as static
    // objects.
    //
#if defined(WIN32)

    static ITS_NtExceptionLog exceptionLog("ITS DBC");
    static ITS_NtEventLog eventLog("ITS DBC");

    // Ideally, the following should be done by the installation procedure.

    ITS_NtEventLog::RegistryCreateSource("ITS DBC", "ItsMsgFile.dll");

    // Set the exception log.

    ITS_GenericException::SetExceptionLog(exceptionLog);

    // Set Console Control Handler (to intercept CTRL-C).

    SetConsoleCtrlHandler(ControlHandler, TRUE);

#else // !defined(WIN32)

    static ITS_UnixExceptionLog exceptionLog("ITS DBC");
    static ITS_UnixEventLog eventLog("ITS DBC");

#endif // defined(WIN32)
    
    static DbcThreadPool* dbcThreadPool = NULL;

    // Input stream definitions.

    istream* inputStream = &cin; // Default initialization for reference.

    ifstream inputFileStream;

    istrstream inputStringStream(cmdLine.c_str());

    try
    {
        // Add DSM STUB feature.

        int res = ITS_AddFeature(itsDSM_StubImplClass);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

        // Initialization of IntelliSS7 subsytems.

        res = ITS_GlobalStart(0);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

        globalStartSuccess = true;

        // Create DBC thread pool.

        try 
        {
            dbcThreadPool = new DbcThreadPool();

            dbcThreadPool->CreatePool(DBC_NUMBER_THREAD, 0);
        }
        catch (ITS_GenericException& exc)
        {

#if defined(_DEBUG)

            cerr << endl;
            cerr << "(!) Fatal error - exception during creation of DBC tread pool.";
            cerr << endl;

#endif // defined(_DEBUG)

            throw exc;
        }

        //
        //  Interactive mode selection.
        //

        bool isInteractive = false;

        if (bCmdStdinPresent)
        {
            isInteractive = true;
        }
        else
        {
            isInteractive = false;
        }

        // Override interactive mode.

        if (bForceInteractive)
        {
            isInteractive = true;
        }

        if (bForceNonInteractive)
        {
            isInteractive = false;
        }

        //
        //  Input stream selection.
        //

        if (bCmdStdinPresent)
        {
            // This is not ANSI C++.  The standard says this equate
            // is not defined.  Besides, the default initialization
            // (construction) above already has done this.
            inputStream = &cin;
        }
        else if (bCmdFilePresent)
        {
            inputFileStream.open((const char *)cmdFile.c_str());
            
            if (!inputFileStream.good())
            {
                bool failed_to_open_command_file = false;

                ITS_THROW_ASSERT(failed_to_open_command_file);
            }

            inputStream = &inputFileStream;
        }
        else if (bCmdLinePresent)
        {
            inputStream = &inputStringStream;
        }
        else
        {
            bool must_not_be_reached = false;

            ITS_THROW_ASSERT(must_not_be_reached);
        }


        DbcClient dbcClient(*inputStream, isInteractive);

        // Set shared DbcClient.

        Shared::SetDbcClient(&dbcClient);

        // Execute DbcThreadFunction using unique thread from thread pool. Will
        // set worker attribute in dbcClient object.

        res = dbcThreadPool->Dispatch(DbcThreadPool::DbcThreadFunction,
                                      &dbcClient);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

        //
        // Synchronization point: wait for worker attribute to be set (by
        // DbcThreadFunction) in dbcClient object.
        //

        dbcClient.SynchronizationWait();


        //
        // To allow to send initial command.
        //

        dbcClient.SynchronizationRelease();

        // Process commands loop.

        dbcClient.ProcessCommandsFromStream();


        if (bCmdLinePresent)
        {
            // Force Quit event.
            char quitBuf[5] = { 'q', 'u', 'i', 't', 0 };

#if defined(ITS_STD_NAMESPACE) && \
    (!defined(__GNUC__) || (defined(__GNUC__) && __GNUC__ >= 3))
            inputStringStream.rdbuf()->pubsetbuf(quitBuf, strlen(quitBuf));
#else
            inputStringStream.rdbuf()->setbuf(quitBuf, strlen(quitBuf));
#endif

            dbcClient.ProcessCommandsFromStream();
        }


        //
        // Synchronization point: wait for DbcThreadFunction to finish its job
        // (e.g. printing last command result).
        //

        dbcClient.SynchronizationWait();


        Shared::ResetDbcClient();

        if (globalStartSuccess)
        {
            ITS_GlobalStop();
        }

#if !defined(ITS_STD_NAMESPACE)
        if (inputFileStream.rdbuf()->is_open())
#else
        if (inputFileStream.is_open())
#endif
        {
            inputFileStream.close();
        }

        // No exception handled.

        exit(EXIT_SUCCESS);
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();

        cerr << endl;
        cerr << exc.GetDescription().c_str();
        cerr << endl;
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

        cerr << endl;
        cerr << standardExc.GetDescription().c_str();
        cerr << endl;
    }

#if 0 //defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();

        cerr << endl;
        cerr << unknownExc.GetDescription().c_str();
        cerr << endl;

        exit(EXIT_FAILURE);
    }
    
#endif  // defined(NDEBUG)

    // Reached only if an exception has occurred.

    Shared::ResetDbcClient();

    if (globalStartSuccess)
    {
        ITS_GlobalStop();
    }

#if !defined(ITS_STD_NAMESPACE)
    if (inputFileStream.rdbuf()->is_open())
#else
    if (inputFileStream.is_open())
#endif
    {
        inputFileStream.close();
    }

    cerr << endl;
    cerr << "(!) Fatal Error - exception (see previously).";
    cerr << endl;

    exit(EXIT_FAILURE);

    // Not reached.

    return 0;
}


