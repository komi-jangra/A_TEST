/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: test8.cpp,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:33  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:15  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:26  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2002/10/28 22:07:39  mmiers
 * LOG: Update tests, add WorkItem test.
 * LOG:
 * LOG: Revision 7.2  2002/10/28 20:43:44  mmiers
 * LOG: Update tests
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.2  2001/01/10 00:28:22  mmiers
 * LOG: Clean up the test.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/06/13 19:16:02  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.22  1999/10/25 18:28:18  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.21  1999/08/20 00:10:40  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a free twice bug in the resource manager.
 * LOG:
 * LOG: Revision 1.20  1999/08/18 14:49:47  mmiers
 * LOG:
 * LOG:
 * LOG: Update comments, test code.
 * LOG:
 * LOG: Revision 1.19  1999/08/18 14:27:50  mmiers
 * LOG:
 * LOG:
 * LOG: Update test to match latest code.
 * LOG:
 * LOG: Revision 1.18  1999/08/18 02:42:58  mmiers
 * LOG:
 * LOG:
 * LOG: Complete framework.
 * LOG:
 * LOG: Revision 1.16  1999/07/27 23:25:04  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more generic dispatchers, this time for an integrated stack
 * LOG: in the application.  Add a method to determine if this is the last
 * LOG: component in a C++ TCAP_Component.
 * LOG:
 * LOG: Revision 1.15  1999/07/27 22:34:20  mmiers
 * LOG:
 * LOG:
 * LOG: Update the infrastructure tests.
 * LOG:
 * LOG: Revision 1.14  1998/11/18 18:07:14  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.13  1998/09/02 22:53:43  mmiers
 * LOG: Correct app selector signature.
 * LOG:
 * LOG: Revision 1.12  1998/07/10 16:03:37  mmiers
 * LOG: Add some warnings about throwing exceptions from the app selector callback.
 * LOG: Add a method to the threadpool for returning an entry to the pool
 * LOG: without dispatching it.
 * LOG:
 * LOG: Revision 1.11  1998/06/24 16:12:31  mmiers
 * LOG: Straighten out the tranport vs. worker issues.
 * LOG:
 * LOG: Revision 1.10  1998/06/17 20:12:14  mmiers
 * LOG: More work on back-compat.
 * LOG:
 * LOG: Revision 1.9  1998/06/15 16:29:07  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.8  1998/05/31 23:05:18  mmiers
 * LOG: Finish off ITS_Worker.
 * LOG:
 * LOG: Revision 1.7  1998/05/31 22:20:17  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.6  1998/05/31 21:22:20  mmiers
 * LOG: Clean up this test for documentation purposes.
 * LOG:
 * LOG: Revision 1.5  1998/05/21 02:15:29  mmiers
 * LOG: General cleanup to reflect TCAP changes (INAP, IS41).  Some missing
 * LOG: files in builds.  Update the test to include the SCCP library.  I'll
 * LOG: have to modify TCAP tomorrow to use SCCP_SendEvent instead of
 * LOG: TRANSPORT_PutEvent().  Less efficient, but more useable with someone
 * LOG: else's SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/05/20 20:15:32  mmiers
 * LOG: Get test8 (process framework) compiled and linked.  Not
 * LOG: all code is linked in (no sending yet, which will cause more
 * LOG: undefined externals).
 * LOG:
 * LOG: Revision 1.3  1998/05/20 17:06:15  mmiers
 * LOG: Get the namespace thing right.  You must include its++.h if
 * LOG: you want to use the its namespace.
 * LOG:
 * LOG: Revision 1.2  1998/05/20 16:00:23  ahanda
 * LOG: ..
 * LOG:
 * LOG: Revision 1.1  1998/04/23 00:12:11  mmiers
 * LOG: New test, HLR like application.
 * LOG:
 * LOG: Revision 1.3  1998/04/19 02:42:52  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.2  1998/04/17 21:22:30  mmiers
 * LOG: Thread pools are working.
 * LOG:
 * LOG: Revision 1.1  1998/04/17 17:43:52  mmiers
 * LOG: Add thread pool test.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <exception>
#include <iostream.h>

#include <its++.h>
#include <its_app.h>
#include <its_exception.h>
#include <its_event_log.h>
#include <its_exception_log.h>
#include <its_route.h>
#include <its_service.h>
#include <its_timers.h>
#include <its_transports.h>
#include <its_ss7_trans.h>
#include <its_worker.h>
#include <its_statics.cpp>

#include <tcap++.h>
#include <sccp++.h>

#if defined(ANSI)
#define USE_STACK   ISS7_ANSI_Stack
#elif defined(CCITT)
#define USE_STACK   ISS7_CCITT_Stack
#elif defined(PRC)
#define USE_STACK   ISS7_PRC_Stack
#endif

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

//
// these values represent the instance ids of the border transports
//
#define GATE_DISPATCHER     1
#define VLR_DISPATCHER      2
#define MSC_DISPATCHER      3
#define MAX_DISPATCHERS     3

#define FIRST_INVOKE_THREAD 4

//.interface:
//////////////////////////////////////////////////////////////////////////////
//  Name:
//      HLR_Invoke pool
//
//  Purpose:
//      A class to create dispatcher threads
//
//  Usage:
//      INLINE
//////////////////////////////////////////////////////////////////////////////
class HLR_DispatcherPool : public ThreadPool
{
public:
    HLR_DispatcherPool()
        : ThreadPool(), count(GATE_DISPATCHER)
    {
    }

    virtual ThreadPoolThread* CreatePoolThread(int stackSize)
    {
        Worker* work;

        //
        // recall that "instance" is the third constructor arg.
        // When used, this identifies the "transport id" for each
        // thread.
        // 
        switch (count)
        {
        case GATE_DISPATCHER:
            // creating the Gateway dispatcher?   
            work = new Worker(stackSize, "Gateway Dispatch",
                              count,
                              ITS_SCCP|ITS_TRANSPORT_CSOCKET|
                              ITS_TRANSPORT_DELAY_CREATE);
            break;

        case VLR_DISPATCHER:
            // creating the VLR dispatcher?   
            work = new Worker(stackSize, "VLR Dispatch",
                              count,
                              ITS_SCCP|ITS_TRANSPORT_FIFO|
                              ITS_TRANSPORT_DELAY_CREATE);
            break;

        case MSC_DISPATCHER:
            // creating the MSC dispatcher?   
            work = new Worker(stackSize, "MSC Dispatch",
                              count,
                              ITS_SCCP|ITS_TRANSPORT_FIFO|
                              ITS_TRANSPORT_DELAY_CREATE);
            break;

        default:
            std::exception ex;

            throw ex;
        }

        count++;

        return (ThreadPoolThread *)work;
    }

    // the work function for this pool
    static void Dispatcher(ThreadPoolThread *thr, void *arg);
    
private:
    ITS_USHORT count;
};

//.implementation:extern
//////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Dispatch all indications to SCCP (our border transports function
//      as MTP3).
//
//  Input Parameters:
//      thr - a pointer to an Worker thread
//      arg - the argument to this function execution session
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
//////////////////////////////////////////////////////////////////////////////
void
HLR_DispatcherPool::Dispatcher(ThreadPoolThread *thr, void *arg)
{
    Worker* work = (Worker *)thr;
    ITS_HANDLE h;
    Event event;

    // getting NULL here is a fatal error
    h = ITS_Initialize(work->GetMask(),
                       work->GetInstance());
    ITS_THROW_ASSERT(h != NULL);
    
    // dispatcher loop.  Take all incoming messages and send them to SCCP.
    while (!work->GetExit())
    {
        // Note: we could use ITS_GetNextEvent() here.
        if (work->GetNextEvent(event) != ITS_SUCCESS)
        {
            continue;
        }

        event.SetSource(ITS_MTP3_SRC);

        if (Transport::PutEvent(ITS_SCCP_SRC, event) != ITS_SUCCESS)
        {
            printf("Couldn't send message to SCCP\n");
        }
    }
    
    // this is good practice
    ITS_Terminate(h);
}

//.interface:
//////////////////////////////////////////////////////////////////////////////
//  Name:
//      HLR_Invoke pool
//
//  Purpose:
//      A class to handle "invokee" threads
//
//  Usage:
//      INLINE
//////////////////////////////////////////////////////////////////////////////
class HLR_InvokePool : public ThreadPool
{
public:
    HLR_InvokePool()
        : ThreadPool(), count(FIRST_INVOKE_THREAD)
    {
    }

    //
    // recall that we used 3 instances above.  So we must start at
    // 4 here.
    // 
    virtual ThreadPoolThread* CreatePoolThread(int stackSize)
    {
        char iThreadName[16];

        sprintf(iThreadName,"InvokeThread%d",count);

        Worker* work =
            new Worker(stackSize, iThreadName,
                           count, ITS_TRANSPORT_TQUEUE);
        count++;

        return (ThreadPoolThread *)work;
    }

    // this function handles all external invokes.
    static void Invoke(ThreadPoolThread *s, void *arg);
    
private:
    ITS_USHORT count;
};

//.implementation:extern
//////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      This function represents a TCAP "unit-of-work", or transaction handler
//
//  Input Parameters:
//      thr - a pointer to an Worker thread
//      arg - the argument to this function execution session
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      None.
//
//  Notes:
//
//  See Also:
//////////////////////////////////////////////////////////////////////////////
void
HLR_InvokePool::Invoke(ThreadPoolThread *s, void *arg)
{
    Worker* self = (Worker*)s;
    ITS_HANDLE hd;
    Event ev;
    TCAP_Dialogue *dlg;
    TCAP_Component *cpt;

    // getting NULL here is a fatal error
    hd = ITS_Initialize(self->GetMask(),
                        self->GetInstance());

    ITS_THROW_ASSERT(hd != NULL);
    
    // Get the Dialog portion of the TCAP message
    self->GetNextEvent(ev);

    // this will throw an exception if the event is not a dialogue
    ITS_THROW_ASSERT(TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_DLG);
    TCAP_Dialogue::Receive(USE_STACK, ev, &dlg);
    
    // Get the component portion of the TCAP message
    self->GetNextEvent(ev);

    // make sure we got a component
    ITS_THROW_ASSERT(TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_CPT);
    TCAP_Component::Receive(USE_STACK, ev, dlg, &cpt);

    // handle invokes
    if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
    {
        bool isNat;
        ITS_OCTET family, op;
        TCAP_Invoke* inv = (TCAP_Invoke *)cpt;

        inv->GetOperation(isNat, family, op);

        // what to do for each operation
        switch(op)
        {
        case 1:
            // yadada
            break;

        default:
            break;
        }
     }
     else 
     {
         // if it's not an invoke, it's an application error
         ITS_THROW_ASSERT(ITS_FALSE);
     }
}

//
// a class for the service
//
class HLR_Service : public Service
{
public:
    HLR_Service(const std::string displayedName,
                const std::string internalName,
                ExceptionLog& exceptionLog,
                EventLog& eventLog)
        : Service(displayedName, internalName,
                      exceptionLog, eventLog),
          dispatcherPool(NULL),
          invokePool(NULL)
    {
        static int instanceCounter = 0;
        //
        // Note: Instance counter mechanism is not thread safe.
        //

        instanceCounter++;

        if (instanceCounter > 1)
        {
            bool only_one_instance_must_be_created = false;

            ITS_THROW_ASSERT(only_one_instance_must_be_created);
        }
    }

    virtual ~HLR_Service()
    {
        // Nothing to do
    }

    virtual void BeforeApplicationLoop(int argc, const char **argv);
    virtual void ApplicationLoop();
    virtual void AfterApplicationLoop();

    static ITS_USHORT ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event);

    HLR_DispatcherPool *
    GetDispatcherPool()
    {
        ITS_THROW_ASSERT(dispatcherPool != NULL);

        return dispatcherPool;
    }

    HLR_InvokePool *
    GetInvokePool()
    {
        ITS_THROW_ASSERT(invokePool != NULL);

        return invokePool;
    }

protected:
    HLR_DispatcherPool * dispatcherPool;
    HLR_InvokePool *     invokePool;
};

//.implementation:extern
//////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Routes the TCAP message to the application based on the dialog id
//      This functions as the "application selector" as documented by
//      ITS_RoutingMap
//
//  Input Parameters:
//      hdr - the per-thread application context (dialogue_id).
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      returns the instance id of the first available dispatch thread
//
//  Notes:
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//
//   DO NOT THROW EXCEPTIONS FROM THIS CALL.  THE CALLER IS A "C" FUNCTION
//   THAT HAS A LOCKED MUTEX.  AN UNCAUGHT EXCEPTION ORIGINATING FROM THIS
//   FUNCTION MEANS THE MUTEX WILL STAY LOCKED, EFFECTIVELY BLOCKING ANY NEW
//   TCAP TRANSACTION OR SCCP CONNECTION FROM THE PROGRAM.  YOU HAVE BEEN
//   WARNED.
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//
//  On some systems, the linkage type of this function must be "C".
//
//  See Also:
//////////////////////////////////////////////////////////////////////////////
extern "C" ITS_USHORT
SelectApplication(ITS_HDR *hdr, ITS_EVENT* event)
{
    try
    {
        return HLR_Service::ApplicationSelector(hdr, event);
    }
    catch (...)
    {
        return (ITS_INVALID_SRC);
    }
}

//.implementation:extern
//////////////////////////////////////////////////////////////////////////////
//  Purpose:
//      Routes the TCAP message to the application based on the dialog id
//      This functions as the "application selector" as documented by
//      ITS_RoutingMap
//
//  Input Parameters:
//      hdr - the per-thread application context (dialogue_id).
//      event - the event that begins this unit of work.
//
//  Input/Output Parameters:
//      None.
//
//  Output Parameters:
//      None.
//
//  Return Value:
//      returns the instance id of the first available dispatch thread
//
//  Notes:
//
//  See Also:
//////////////////////////////////////////////////////////////////////////////
ITS_USHORT
HLR_Service::ApplicationSelector(ITS_HDR* hdr, ITS_EVENT* event)
{
    ThreadPoolEntry iThread;
    HLR_Service& service =
        reinterpret_cast<HLR_Service&>(Service::GetCurrentService());
    
    int did = hdr->context.dialogue_id;

    int ret = service.GetInvokePool()->GetFirstAvailThread(iThread);
    
    ITS_THROW_ASSERT(ret == ITS_SUCCESS);

    Worker* wThread = (Worker*)iThread.GetThread();

    ITS_USHORT qid = wThread->GetInstance();
        
    RoutingMap::AddApplication(qid, hdr);
        
    // Invoke the Function for the thread
    ret = service.GetInvokePool()->DispatchOnThread(iThread,
                                                    HLR_InvokePool::Invoke,
                                                    NULL);
                                                    
    ITS_THROW_ASSERT(ret == ITS_SUCCESS); 
        
    return (qid);
}

//
// Before the main loop
//
void
HLR_Service::BeforeApplicationLoop(int argc,
                                   const char **argv)
{
    // First things first
    int ret = ITS_GlobalStart(ITS_TCAP|ITS_SCCP);

    ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    
    // set the application selector for TCAP
    ROUTE_AppSelector last =
        RoutingMap::SetApplicationSelector(SelectApplication);

    ITS_THROW_ASSERT(last != NULL);

    // create your internal threads FIRST
    try
    {
        invokePool = new HLR_InvokePool();

        invokePool->CreatePool(100, 0);
    }
    catch (GenericException& ex)
    {
        ex.Log();
    }
    catch (std::exception& exc)
    {
        StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();
    }
#if defined(NDEBUG)
    catch (...)
    {
        UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();
    }
#endif // defined(NDEBUG)

    // then create your external interfaces.
    try
    {
        dispatcherPool = new HLR_DispatcherPool();

        dispatcherPool->CreatePool(MAX_DISPATCHERS, 0);

        //
        // the order that threads are allocated is the same as the order
        // they were created in.  Not relevant here, but good to know.
        //
        int ret = dispatcherPool->Dispatch(HLR_DispatcherPool::Dispatcher,
                                           NULL);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        ret = dispatcherPool->Dispatch(HLR_DispatcherPool::Dispatcher,
                                       NULL);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        ret = dispatcherPool->Dispatch(HLR_DispatcherPool::Dispatcher,
                                       NULL);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }
    catch (GenericException& ex)
    {
        ex.Log();
    }
    catch (std::exception& exc)
    {
        StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();
    }
#if defined(NDEBUG)
    catch (...)
    {
        UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();
    }
#endif // defined(NDEBUG)
}

//
// main loop
//
void
HLR_Service::ApplicationLoop()
{
    TIMERS_Sleep(5);
}

//
// after main loop
//
void
HLR_Service::AfterApplicationLoop()
{
    // Kill your exterior comm points FIRST
    if (dispatcherPool)
    {
        delete dispatcherPool;
    }
    if (invokePool)
    {
        delete invokePool;
    }
}

//
// and the entry point.
//
int
main(int argc, char **argv)
{
    //
    // The exception log and event log objects MUST always be created as static
    // objects.  Also, no point in doing this in a try catch as if these
    // constructors throw an exception we can't report it.
    //

#if defined(WIN32)

    static NtExceptionLog exceptionLog("TCAP Server");
    static NtEventLog eventLog("TCAP Server");

    //
    // Ideally the following should be done by the installation procedure.
    //

    NtEventLog::RegistryCreateSource("TCAP Server", "ItsMsgFile.dll");

#else // !defined(WIN32)

    static UnixExceptionLog exceptionLog("TCAP Server");
    static UnixEventLog eventLog("TCAP Server");

#endif // defined(WIN32)

    try
    {
        HLR_Service service("HLR Service", "HLR_Service",
                            exceptionLog, eventLog);


        // Process command line.
        service.ProcessCommandLine(argc, (const char **)argv);

        //
        // Set the application name.  This can be done in ProcessCommandLine().
        //
        // Application::SetName("TCAP_Server");

        // set path for configuration directory.  Or let ProcessCommandLine()
        // do this.
        // Application::SetConfigDir("./");

        // Override default behavior - force to foreground
        service.SetApplicationType(Service::AT_CONSOLE_APPLICATION);

        if (service.GetApplicationType() == Service::AT_SERVICE)
        {
            service.RunAsService();
        }
        else if (service.GetApplicationType() ==
                 Service::AT_CONSOLE_APPLICATION)
        {
            service.RunAsConsoleApplication(argc, (const char **)argv);
        }

        //
        // at this point, the main application thread has done it's work.  It
        // is no longer necessary for this thread to continue.  More, we won't
        // even get here under most common circumstances
        //
        exit(service.GetExitCode());
    }
    catch (GenericException& exc)
    {
        exc.Log();
    }
    catch (std::exception& exc)
    {
        StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log();
    }

#if defined(NDEBUG)

    catch (...)
    {
        UnknownException unknownExc(__FILE__, __LINE__);

        unknownExc.Log();
    }

#endif // defined(NDEBUG)

    // Reached only if an exception has occurred.

    return (EXIT_FAILURE);
}
