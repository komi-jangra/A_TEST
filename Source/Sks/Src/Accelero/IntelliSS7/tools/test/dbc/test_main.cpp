////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
// CONTRACT: IntelliNet Technologies                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//

#include <stdio.h>

#if defined(WIN32)
#include <iostream>
#else
#include <iostream/iostream.h>
#endif

#include <its++.h>
#include <its_exception.h>
#include <its_timers.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_dsm.h>
#include <its_dsm_stub.h>
#include <its_statics.cpp>

#include <test_dbc.h>

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif

 
//
// Dispatcher pool class and member functions.
//

class DispatcherPool : public ITS_ThreadPool
{
public:

    DispatcherPool()
        : ITS_ThreadPool(), count(FIRST_DISPATCHER_THREAD)
    {};

    virtual ITS_ThreadPoolThread* CreatePoolThread(int stackSize);

    // Specific thread functions (one specific thread
    // function for each specific dispatcher thread).
    static void DBG_ThreadFunction(ITS_ThreadPoolThread* thr, void* arg);
    
protected:

    ITS_USHORT count;
};


//
//  To create threads in the dispatcher pool thread (redefined virtual member
//  function).
//

ITS_ThreadPoolThread* DispatcherPool::CreatePoolThread(int stackSize)
{
    ITS_Worker* result = NULL;

    // The third argument of ITS_Worker constructor initialize the instance
    // attribute of the ITS_Worker object. It also identifies the transport
    // object associated with the ITS_Worker object.
    switch (count)
    {        
        case DBG_DISPATCHER_THREAD:
            // Creating the Debug Console dispatcher.
            result = new ITS_Worker(stackSize, "test_debug_console_dispatcher",
                                    count,
                                    ITS_TRANSPORT_FIFO |
                                    ITS_TRANSPORT_DELAY_CREATE);
            break;

        default:
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
    }

    count++;

    ITS_ENSURE(result != NULL);

    return (ITS_ThreadPoolThread *)result;
}

//
//  DBG (Debug Console) dispatch thread function.
//

void DispatcherPool::DBG_ThreadFunction(ITS_ThreadPoolThread* thr, void* arg)
{
    ITS_REQUIRE(thr != NULL);

    ITS_Worker* worker = (ITS_Worker *)thr;
    ITS_Event event;
    ITS_HANDLE handle = NULL;
    int res = ITS_SUCCESS;
    bool itsInitSuccess = false;

    printf("Entering server thread.\n");
    fflush(stdout);

    try
    {
        handle = ITS_Initialize(worker->GetMask(), worker->GetInstance());

        ITS_ASSERT(handle != NULL); // Fatal error if handle == NULL.

        itsInitSuccess = true;

        TestDbcServer testDbcServer("TEST Debug Console", *worker);

        cout << "Going to process command loop" << endl;

        testDbcServer.ProcessCommandsLoop();

        if (itsInitSuccess)
        { 
            ITS_Terminate(handle);
        }

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


//
// Test entry point.
//

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
#endif

extern "C" void TRACE_TurnDebugTraceOnOff(ITS_BOOLEAN);

int 
main(int argc, const char** argv)
{

    DispatcherPool* dispatcherPool = NULL;

#if defined(_DEBUG)

    cout << "Begin Test execution..." << endl;

#endif  // defined(_DEBUG)


    // TRACE_TurnDebugTraceOnOff(ITS_TRUE);

    ITS_AddFeature(itsDSM_StubImplClass);

    int res = ITS_GlobalStart(0);

    if (res != ITS_SUCCESS)
    {
        abort();
    }

    try
    { 
        // Create dispatcher thread pool.

        try 
        {
            dispatcherPool = new DispatcherPool();

            dispatcherPool->CreatePool(NUMBER_DISPATCHER_THREAD, 0);
        }
        catch (ITS_GenericException& exc)
        {

#if defined(_DEBUG)

            cout << "Caught exception during creation of dispatcher pool.";
            cout << endl;

#endif  // defined(_DEBUG)

            throw exc;
        }

        // Set dispatcher thread functions and start dispatcher threads.
        // The order that threads are allocated is the same as the order
        // they were created in the thread pool. Relevant and very
        // important in this case. The order MUST be exactly the same
        // than in the member function DispatcherPool::CreatePoolThread.

        res = dispatcherPool->Dispatch(DispatcherPool::DBG_ThreadFunction,
                                       NULL);
        if (res != ITS_SUCCESS)
        {
            ITS_THROW_ERROR(res);
        }

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

#if defined(HPUX)
    TIMERS_Sleep(300);
#else
    ITS_Thread::Exit(0);
#endif

#if defined(_DEBUG)

    cout << "End of TEST DBC execution..." << endl;

#endif  // defined(_DEBUG)

    return EXIT_SUCCESS;
}
