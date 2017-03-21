//////////////////////////////////-*-C-*-////////////////////////////////////
//                                                                         //
//             Copyright 1997,1998 IntelliNet Technologies, Inc.           //
//                            All Rights Reserved.                         //
//             Manufactured in the United States of America.               //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.      //
//                                                                         //
//   This product and related documentation is protected by copyright and  //
//   distributed under licenses restricting its use, copying, distribution //
//   and decompilation.  No part of this product or related documentation  //
//   may be reproduced in any form by any means without prior written      //
//   authorization of IntelliNet Technologies and its licensors, if any.   //
//                                                                         //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     //
//   government is subject to restrictions as set forth in subparagraph    //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software      //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                       //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// CONTRACT: INTERNAL                                                      //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//
// DBC commnad line interface.
//

#if defined(HPUX)
#include <iostream/iostream.h>
#else
#include <iostream>
#include <strstream>
#endif
#include <string>

#include <its++.h>
#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_exception.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_thread.h>
#include <its_app.h>

#include <dbc_command_client.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)

// Since the code rely on the standard C++ library,
// the following must be accepted by the compiler.
#if !defined(HPUX)
using namespace std;
#endif


static const int DBC_NUMBER_THREAD   = 1;
static const int DBC_THREAD_INSTANCE = 1;

static bool globalStartSuccess = false;
static bool sockInterface = false;

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

#else

int
sigQuit(int signal)
{
    exit(EXIT_SUCCESS);

    /* NOTREACHED */
    return (0);
}

#endif

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

    cerr << "\nUsage: " << strippedPrgName.c_str() << " ";
    cerr << "resource_file \n";
}


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

ITS_ThreadPoolThread*
DbcThreadPool::CreatePoolThread(int stackSize)
{
    ITS_Worker* result = NULL;

    // The third argument of ITS_Worker constructor initialize the instance
    // attribute of the ITS_Worker object. It also identifies the transport
    // object associated with the ITS_Worker object.

    if (sockInterface)
    {
        result = new ITS_Worker(stackSize, "DBG_CMD Transport",
                            DBC_THREAD_INSTANCE,
                            ITS_TRANSPORT_CSOCKET |
                            ITS_TRANSPORT_DELAY_CREATE);
    }
    else
    {
         result = new ITS_Worker(stackSize, "DBG_CMD Transport",
                            DBC_THREAD_INSTANCE,
                            ITS_TRANSPORT_FIFO |
                            ITS_TRANSPORT_DELAY_CREATE);
    }

    ITS_ENSURE(result != NULL);

    return (ITS_ThreadPoolThread *)result;
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
    int res = ITS_SUCCESS;
    bool itsInitSuccess = false;

    try
    {
        dbcClient->SetWorker(worker);

        handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

        ITS_THROW_ASSERT(handle != NULL); // Fatal error if handle == NULL.

        itsInitSuccess = true;

        dbcClient->ProcessCommandsResult();

        ITS_Terminate(handle);

        // No exception handled.

        return;
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();
    }

#if defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();

        exit(EXIT_FAILURE);
    }

#endif  // defined(NDEBUG)

    // Reached only if an exception has occurred.

    if (itsInitSuccess)
    { 
        ITS_Terminate(handle);
    }

    return;
}


#if defined(ITS_NAMESPACE)
}
#endif 


#if defined(ITS_NAMESPACE)
using namespace its;
#endif

int
main(int argc, char** argv)
{
    
    // Parse command line.

    string resourceFile;
	string minString;
	string commandString;

    if (argc < 2)
    {
        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-h") == 0)
    {
        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    int commandIndex;

    for (int i = 1; i < argc; i++)
    {
        if (strstr(argv[i], "-cdp_cache"))
        {
			commandIndex = 1;
		}

        if (strstr(argv[i], "-cdp_by_min"))
        {
            commandIndex = 2;
            minString = argv[i + 1];
        }        
    }

	if (!strcmp(argv[argc - 1], "-SOCKET"))
    {
        sockInterface = true;
		//sockInterface = false;
        resourceFile = argv[argc - 2];
    }
	else
	{
		resourceFile = argv[argc - 1];
	}


    // Copy resource file in the current directory and rename it if necessary.

    if (resourceFile != "VlrDumpCache.ini" && resourceFile != ".\\VlrDumpCache.ini")
    {
#if defined(WIN32)
        string copyCommand = "copy .\\";
#else
        string copyCommand = "cp .\\";
#endif
        copyCommand.append(resourceFile);
        copyCommand.append(" .\\VlrDumpCache.ini > .\\tmp.txt");

        int res = system(copyCommand.c_str());

        if (res)
        {
            cerr << "Fatal error - unable to copy and rename resource file."
                 << endl;

            exit(EXIT_FAILURE);
        }
    }

    // 
    // The exception log and event log objects
    // MUST always be created as static objects.
    //
#if defined(WIN32)
    static ITS_NtExceptionLog exceptionLog("ITS DBC");
    static ITS_NtEventLog eventLog("ITS DBC");

    // Ideally, the following should be done by
    // the installation procedure.

    ITS_NtEventLog::RegistryCreateSource("ITS DBC", "ItsMsgFile.dll");

    // Set the exception log.

    ITS_GenericException::SetExceptionLog(exceptionLog);

    // Set Console Control Handler (to intercept CTRL-C).

    SetConsoleCtrlHandler(ControlHandler, TRUE);

#else

#endif
    
    static DbcThreadPool* dbcThreadPool = NULL;

    try
    {
        ITS_Application::SetName("VlrDumpCache");
        // Initialization of IntelliSS7 subsytems.

        int res = ITS_GlobalStart(0);

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

            cout << "Caught exception during creation of DBC thread pool.";
            cout << endl;

#endif  // defined(_DEBUG)

            throw exc;
        }

        // Temporary: interactive only.

        bool isInteractive = false;

        //istrstream inputStream(strstr(argv[commandIndex], "-c") + 2);
		
		if (commandIndex == 1)
		{
			commandString = "dp_cache";
		}
		else
		{
			char temp[] = "dp_min ";
			commandString = strcat(temp, minString.c_str());			
		}

		istrstream inputStream(commandString.c_str());

		//istream& inputStream = std::cin;

        DbcClient dbcClient(inputStream, isInteractive);

		// Next call resume a thread and ultimately initialize worker in
		// dbcClient object.

        res = dbcThreadPool->Dispatch(DbcThreadPool::DbcThreadFunction,
                                      &dbcClient);

        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

		// Polling synchronization point.

		while (!dbcClient.IsWorkerInitialized())
		{
			Sleep(250);	// To spare CPU.
		}

        // Process commands loop.

        dbcClient.ProcessCommandsFromStream(inputStream, false);

		// Polling synchronization point.

		while (!(dbcClient.GetCommandsResultCounter() >= 1))
		{
			Sleep(250); // To spare CPU.
		}

        if (globalStartSuccess)
        {
            ITS_GlobalStop();
        }

        exit(EXIT_SUCCESS);

        // No exception handled.
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();

        cerr << exc.GetDescription().c_str();
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();

        cerr << standardExc.GetDescription().c_str();
    }

#if defined(NDEBUG)

    catch (...)
    {
        ITS_UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();

        cerr << unknownExc.GetDescription().c_str();

        exit(EXIT_FAILURE);
    }
    
#endif  // defined(NDEBUG)

    // Reached only if an exception has occurred.

    if (globalStartSuccess)
    {
        ITS_GlobalStop();
    }

    cerr << endl;
    cerr << "Fatal Error - exception."
         << endl;

    exit(EXIT_FAILURE);

    /* NOTREACHED */
    return (0);
}


