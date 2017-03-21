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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2002/10/01 15:06:52  mmiers
 * LOG: Add API to yield CPU
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/13 20:45:23  mmiers
 * LOG: Comment correction
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7  2002/02/15 17:05:16  hdivoux
 * LOG: Remove typo.
 * LOG:
 * LOG: Revision 5.6  2001/12/12 23:09:25  hdivoux
 * LOG: Added comment: get thread ID is for internal use only.
 * LOG:
 * LOG: Revision 5.5  2001/12/12 20:40:00  hdivoux
 * LOG: Added function to get thread ID of calling thread.
 * LOG:
 * LOG: Revision 5.4  2001/11/19 22:51:57  mmiers
 * LOG: Convert DBC server to C.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 22:29:14  mmiers
 * LOG: externs need to see the local storage API
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.13  2001/04/05 23:07:00  mmiers
 * LOG: Debugging C++ API.
 * LOG:
 * LOG: Revision 3.12  2001/04/05 20:24:41  mmiers
 * LOG: Add virtual destructor.
 * LOG:
 * LOG: Revision 3.11  2001/04/05 19:46:49  mmiers
 * LOG: Add virtual class.
 * LOG:
 * LOG: Revision 3.10  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.9  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.8  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.7  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/31 23:40:53  mmiers
 * LOG: Work around thread data duplication.
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:58  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:46  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.44  1999/08/30 17:53:42  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.43  1999/08/23 01:47:28  mmiers
 * LOG:
 * LOG:
 * LOG: Work this for Solaris build.
 * LOG:
 * LOG: Revision 1.42  1999/08/23 01:12:08  mmiers
 * LOG:
 * LOG:
 * LOG: Add signal mask handling correctly.
 * LOG:
 * LOG: Revision 1.41  1999/07/28 02:17:19  mmiers
 * LOG:
 * LOG: Make arg names more meaningful.
 * LOG:
 * LOG: Revision 1.40  1999/06/28 23:45:23  skarmakar
 * LOG:
 * LOG:
 * LOG: More work on portability.
 * LOG:
 * LOG: Revision 1.39  1999/06/28 23:19:02  skarmakar
 * LOG:
 * LOG:
 * LOG: Many many portability fixes.
 * LOG:
 * LOG: Revision 1.38  1999/06/23 20:07:10  mmiers
 * LOG:
 * LOG:
 * LOG: Change C++ protection syntax.
 * LOG:
 * LOG: Revision 1.37  1999/02/25 23:03:57  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for CC.
 * LOG:
 * LOG: Revision 1.36  1999/02/09 21:46:16  mmiers
 * LOG:
 * LOG:
 * LOG: Normalize the thread function return type.
 * LOG: Create standard thread function exit macro.
 * LOG: Convert support library to use these.
 * LOG: Delete dead file (its_worker).
 * LOG:
 * LOG: Revision 1.35  1998/10/01 00:01:41  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.34  1998/09/30 17:20:16  jrao
 * LOG: Update for HPUX.  Convert from UNIX semaphores to condition variables.
 * LOG:
 * LOG: Revision 1.33  1998/09/26 02:46:59  mmiers
 * LOG: Linux code base cleanup.
 * LOG:
 * LOG: Revision 1.32  1998/09/22 23:21:42  jrao
 * LOG: Stupid HP compiler.
 * LOG:
 * LOG: Revision 1.31  1998/09/22 22:36:33  jrao
 * LOG: Hacks for POSIX threads (Suspend()/Resume()).  An attempt to allow the
 * LOG: user to start suspended threads.
 * LOG:
 * LOG: Revision 1.30  1998/09/22 16:01:25  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.29  1998/07/07 21:12:33  mmiers
 * LOG: Fixes for timers and TCAP cancels.
 * LOG:
 * LOG: Revision 1.28  1998/06/20 03:50:26  mmiers
 * LOG: Add Linux as a target.
 * LOG:
 * LOG: Revision 1.27  1998/06/09 21:00:30  whu
 * LOG: Make thread pool threads suspended on creation.  This removes a race
 * LOG: condition where the worker thread has not reached the suspended state
 * LOG: before the main thread dispatches work to it; in this case, the worker
 * LOG: suspends *before* the work is started, resulting in a wasted dispatch.
 * LOG:
 * LOG: Also fixed a bug where we were adding and removing threads from the
 * LOG: avail list twice.  Had to add a new parameter to the THREAD interface;
 * LOG: document this.
 * LOG:
 * LOG: Revision 1.26  1998/06/02 19:43:15  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.25  1998/06/01 16:35:20  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.24  1998/05/29 03:31:32  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.23  1998/05/29 00:32:54  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.22  1998/05/28 18:56:44  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.21  1998/05/28 17:28:42  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 * LOG: Revision 1.20  1998/05/19 17:50:25  ahanda
 * LOG: Fix thread usage problems.
 * LOG:
 * LOG: Revision 1.19  1998/05/19 17:11:48  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.18  1998/05/04 23:54:18  mmiers
 * LOG: Add user managed thread dispatch for common thread pools.
 * LOG:
 * LOG: Revision 1.17  1998/05/01 00:24:35  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.16  1998/04/27 20:00:26  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.15  1998/04/19 02:42:48  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.14  1998/04/17 21:22:28  mmiers
 * LOG: Thread pools are working.
 * LOG:
 * LOG: Revision 1.13  1998/04/17 17:43:20  mmiers
 * LOG: Working thread pool.  Still have to do something about termination.
 * LOG:
 * LOG: Revision 1.12  1998/04/17 15:31:54  mmiers
 * LOG: A better implementation of the thread pool.
 * LOG:
 * LOG: Revision 1.11  1998/04/17 03:36:27  mmiers
 * LOG: Start with a FIRST CUT at an implementation for thread pools.
 * LOG:
 * LOG: Revision 1.10  1998/04/13 21:16:29  mmiers
 * LOG: Resolving some cross-platform issues.
 * LOG:
 * LOG: Revision 1.9  1998/04/13 20:41:09  mmiers
 * LOG: Finish tracking down the bugs for Windows sockets.  NOTE:
 * LOG: You MUST call WSAStartup for ALL sockets created --
 * LOG: INCLUDING the socket that is the result of accept().
 * LOG:
 * LOG: Revision 1.8  1998/04/10 15:40:47  mmiers
 * LOG: More debug on the infrastructure.
 * LOG:
 * LOG: Revision 1.7  1998/04/09 23:43:42  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.6  1998/04/09 14:33:20  mmiers
 * LOG: Visual complains about operator= not having a return value even when hidden
 * LOG: in the private section of the class record and given a stub implementation.
 * LOG:
 * LOG: Revision 1.5  1998/04/09 01:47:19  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.4  1998/04/06 15:27:13  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 22:17:54  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.2  1998/03/13 04:12:31  mmiers
 * LOG: Update files with latest data for TCAP implementation.  emlist represents
 * LOG: portable message queues.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 23:29:59  mmiers
 * LOG: Add a definition for threads.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_THREAD_H
#define ITS_THREAD_H

#include <its_mutex.h>
#include <its_mem_pool.h>

#ident "$Id: its_thread.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#ifdef __cplusplus
extern "C"
{
#endif

/*.interface:THREAD
 *****************************************************************************
 *  Interface:
 *      THREAD_*
 *
 *  Purpose:
 *      The ITS_THREAD interface defines how IntelliSS7 users interact with
 *      native thread implementations on different operating systems.  The
 *      implementation is portable, so code written on one platform should
 *      be usable on many platforms (with several minor exceptions).
 *
 *      These routines work directly on thread objects, and as such do not
 *      maintain any context information for individual threads, other than
 *      the thread handle.
 *
 *  Usage:
 *      Usage of ITS_THREAD is fairly simple:
 *      ----------------------------------------------------------------
 *      * must have a thread function *
 *      THREAD_RET_TYPE
 *      ThreadFunc(void *arg)
 *      {
 *          ITS_THREAD *thr = (ITS_THREAD *)arg;
 *
 *          printf("foo\n");
 *
 *          ITS_ThreadExit();
 *      }
 *
 *      ...
 *
 *      * Create the thread *
 *      ITS_THREAD thr;
 *      if (THREAD_CreateThread(&thr, 0, ThreadFunc, (void *)&thr,
 *                              ITS_TRUE) != ITS_SUCCESS)
 *      {
 *          * an error occurred *
 *      }
 *
 *      ...
 *
 *      * Threads can be killed, but is VERY STRONGLY discouraged *
 *      THREAD_KillThread(&thr);
 *
 *      ...
 *
 *      * Threads can be suspended and resumed *
 *      if (THREAD_ThreadSuspend(&thr) != ITS_SUCCESS)
 *      {
 *          * an error has occurred *
 *      }
 *
 *      if (THREAD_ThreadResume(&thr) != ITS_SUCCESS)
 *      {
 *          * an error has occurred *
 *      }
 *
 *      ...
 *
 *      * and threads can be waited for *
 *      void *status;
 *      if (THREAD_WaitForThread(&thr, &status) != ITS_SUCCESS)
 *      {
 *          * an error occurred *
 *      }
 *      -----------------------------------------------------------------------
 *
 *      All thread routines are reentrant and thread safe.
 *
 *****************************************************************************/
ITSDLLAPI int THREAD_CreateThread(ITS_THREAD *thr, int stackSize,
                                  ITS_THREAD_FUNC entryPoint, void *arg,
                                  ITS_BOOLEAN running);
ITSDLLAPI void THREAD_DeleteThread(ITS_THREAD *thr);
ITSDLLAPI int THREAD_ThreadSuspend(ITS_THREAD *thr);
ITSDLLAPI int THREAD_ThreadResume(ITS_THREAD *thr);
ITSDLLAPI void THREAD_ThreadExit(void *status);
ITSDLLAPI int THREAD_KillThread(ITS_THREAD *thr);
ITSDLLAPI int THREAD_WaitForThread(ITS_THREAD *thr, void **status);
ITSDLLAPI void THREAD_Yield(void);

/*
 * these are for internal use only (at this time).
 */
ITSDLLAPI void *  THREAD_GetLocalStorage();
ITSDLLAPI int     THREAD_SetLocalStorage(void *);

/* 
 * for internal use only. 
 * NOTE: need to be reexamined for 64 bits operating systems.
 */
ITSDLLAPI ITS_UINT THREAD_GetCurrentThreadID();

/*
 * class record
 */
ITSDLLAPI extern ITS_ClassRec itsTHREAD_ClassRec;
ITSDLLAPI extern ITS_Class    itsTHREAD_Class;

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Thread
 *****************************************************************************
 *  Interface:
 *      Thread
 *
 *  Purpose:
 *      The Thread class brings thread support to the IntelliSS7 C++ API.
 *      As with many other classes in the support library, the Thread
 *      class is implemented as a wrapper around the C function counterparts
 *      of each method -- although there are some exceptions to that.
 *
 *      A thread is defined as a thread of execution in a process space.
 *      In traditional multiprocessing systems, each process had a single
 *      thread of execution within the process address space.  Put a different
 *      way, such processes were "single threaded" -- there was only one
 *      sequence of operations as defined by the program logic.
 *
 *      Multithreaded applications introduces the concept of multiple threads
 *      of execution within a single process space.  The scheduling of each
 *      thread can be preemptive or cooperative, just as the scheduling of
 *      processes in a traditional multiprocessing architecture.  Threads
 *      can either be scheduled by the user, or by the operating system kernel,
 *      as the implementation allows.
 *
 *      Multithreading is a very powerful programming tool; it allows a single
 *      application to perform two or more loosely coupled tasks at the same
 *      time.  However, it does complicate *some* programming activities --
 *      specifically those which are associated with communication between
 *      the threads.  The application programmer now has to be familiar with
 *      critical sections, mutual exclusion, race conditions, and deadlock.
 *      In the interest of brevity, those terms will not be explained here;
 *      consult any good operating systems textbook for more information.
 *
 *      IntelliSS7 requires preemptive, kernel scheduled threads for best
 *      execution.  Run-to-completion threads will probably NOT work for
 *      IntelliSS7 (i.e., what MS terms "fibers").
 *
 *  Usage:
 *      The usage for Thread is fairly straightfoward.  Let's start
 *      by examining a typical thread function:
 *      -------------------------------------------------------------------
 *      // a thread execution function; deal with WIN32 oddities
 *      THREAD_RET_TYPE
 *      ThreadFunc(void *arg)
 *      {
 *          Thread *thr = (Thread *)arg;
 *
 *          printf("foo\n");
 *
 *          // what's this?  See below
 *          delete thr;
 *
 *          Thread::Exit();
 *      }
 *      -------------------------------------------------------------------
 *
 *      That looks a little strange, doesn't it?  We delete the thread
 *      object before the thread returns.
 *
 *      There is a reason for that.  Keep in mind that threads are (usually)
 *      an operating system object; the Thread object only contains
 *      housekeeping information about the thread.  Deleting a thread object
 *      does NOT cause the thread to terminate, it only "schedules" the
 *      thread for removal, but the thread will not be destroyed until
 *      it ceases execution, <I>even though the Thread object no longer
 *      exists</I>.
 *
 *      The method Thread::Exit() is a static method, and thus does not
 *      require a thread object when invoked.  The Thread::Exit() method
 *      causes a thread of execution to actually terminate.  It is possible
 *      just to return from the thread function (which accomplishes the same
 *      effect on most platforms), but it is recommended that the user
 *      call Thread::Exit() instead, for portability reasons.
 *
 *      It is STRONGLY recommended that Thread objects be created using
 *      operator new.  If Thread objects are not created this way,
 *      and the object goes out of scope, the object will no longer be valid;
 *      this can (and will) cause confusion if the Thread object is
 *      passed to the thread function, as the object will be destroyed at
 *      an unknown time.
 *
 *      That's confusing, so let's try an example:
 *      -------------------------------------------------------------------
 *      int
 *      foo()
 *      {
 *          Thread thr(0, ThreadFunc);
 *
 *          if (thr.Enter((void *)&thr) != ITS_SUCCESS)
 *          {
 *              // an error occurred
 *          }
 *
 *          return (0);
 *      }
 *      -------------------------------------------------------------------
 *
 *      Consider: when we enter function foo(), a thread object is allocated
 *      on the stack, and the constructor is called.  The constructor
 *      sets the stack size, and the function to execute.  IT DOES NOT
 *      CREATE THE THREAD.  The Thread method Enter() is where the
 *      thread is actually created.  Once Enter() is invoked, the new thread
 *      begins executing the ThreadFunc -- but in a new thread of execution.
 *      The original thread of execution continues after the call to Enter(),
 *      which means the function foo() will return, <I>thus destroying the
 *      Thread object</I>.  THIS means that the address we passed into
 *      the function is not valid.  The time at which the address becomes
 *      invalid is not defined -- the scheduler determines (according to its
 *      own algorithm) whether the new thread or the original thread executes
 *      first.
 *
 *      The bottom line: DO NOT CREATE THREADS THIS WAY.  The proper way
 *      to create threads is as follows:
 *      -------------------------------------------------------------------
 *      int
 *      foo()
 *      {
 *          Thread *thr = new Thread(0, ThreadFunc);
 *
 *          if (thr->Enter((void *)thr) != ITS_SUCCESS)
 *          {
 *              // an error occurred
 *          }
 *
 *          return (0);
 *      }
 *      -------------------------------------------------------------------
 *
 *      By using operator new, the Thread object is created on the heap,
 *      and will not be affected by the Thread <I>pointer</I> going
 *      out of scope.
 *
 *      Threads can be suspended (pause execution), and resumed (continue
 *      execution) either by themselves or by other threads.  (This behavior
 *      is key to the implementation of thread pools, by the way.  See
 *      <A HREF=its_threadpool.html>ITS_ThreadPool</A>
 *      for details).  For example:
 *      -------------------------------------------------------------------
 *      ...
 *          if (thr->Suspend() != ITS_SUCCESS)
 *          {
 *              // an error occurred
 *          }
 *
 *      ...
 *
 *          if (thr->Resume() != ITS_SUCCESS)
 *          {
 *              // an error occurred
 *          }
 *      --------------------------------------------------------------------
 *
 *      It is *possible* to kill a thread, but is <B><I>very, very strongly
 *      discouraged</I></B>.  The reasons for this are many:
 *          o   A thread may have possession of a mutex when it is destroyed.
 *              The mutex is not automatically released.
 *          o   The thread may be in the process of updating a critical
 *              resource, and the update may only be partially complete.
 *          o   The process may be left in an inconsistent state.
 *      For these reasons (among others), do NOT kill threads unless you
 *      KNOW that nothing bad will happen.  In practice, this means NEVER.
 *
 *      Threads can also be waited on.  This allows a thread to transmit
 *      its exit code to the waiter:
 *      --------------------------------------------------------------------
 *      // don't do this
 *      thr->Kill();
 *
 *      ...
 *
 *      // but this is ok
 *      void *status;
 *      if (thr->WaitFor(&status) != ITS_SUCCESS)
 *      {
 *          // an error occurred
 *      }
 *      ---------------------------------------------------------------------
 *
 *      For a concrete example, we have included our thread unit test
 *      to give a more accurate example of Thread usage, and how to
 *      subclass from Thread:
 *      ---------------------------------------------------------------------
 *      #include <stdio.h>
 *      #include <stdlib.h>
 *      #include <string.h>
 *      #include <assert.h>
 *      #include <time.h>
 *
 *      #if defined(unix)
 *      #include <unistd.h>
 *      #include <signal.h>
 *      #endif
 *
 *      #include <exception>
 *
 *      #include <its++.h>
 *      #include <its_thread.h>
 *
 *      #if defined(ITS_NAMESPACE)
 *      using namespace its;
 *      #endif
 *
 *      class TestThread : public Thread
 *      {
 *      public:
 *          TestThread(ITS_THREAD_FUNC thread, int which)
 *          {
 *          }
 *          ~TestThread()
 *          {
 *          }
 *  
 *          static THREAD_RET_TYPE Action(void *arg);
 *
 *          int which;
 *      };
 *
 *      THREAD_RET_TYPE
 *      TestThread::Action(void *arg)
 *      {
 *          TestThread *work = (TestThread *)arg;
 *
 *          TIMERS_Sleep(5);
 *
 *          if (!(work->which % 100))
 *          {
 *              time_t tm;
 *
 *              time(&tm);
 *              printf("Thread %d exiting: %s\n", work->which, ctime(&tm));
 *          }
 *
 *          delete work;
 *          TestThread::Exit(NULL);
 *
 *          return (0);
 *      }
 *
 *      int
 *      main(int argc, char **argv)
 *      {
 *          time_t tm;
 *
 *          time(&tm);
 *          printf("Start time: %s\n", ctime(&tm));
 *
 *          for (int i = 0; i < 1000; i++)
 *          {
 *              TestThread *work = new TestThread(TestThread::Action, i);
 *
 *              assert(work->Enter((void *)work) == ITS_SUCCESS);
 *          }
 *
 *          printf("End time: %s\n", ctime(&tm));
 *
 *          Thread::Exit(0);
 *
 *          return (0);
 *      }
 *      -------------------------------------------------------------------
 *
 *      This test creates a thousand threads and waits for them all to exit.
 *      The test takes about 7 seconds to run on a SPARC 4 workstation, about
 *      6 seconds on a 333 MHz Pentium Pro.  Note that each thread sleeps
 *      for *5* seconds. time(1) on Solaris indicates 6.2 seconds of real
 *      time, 0.8 seconds of user time, and 0.8 seconds of system time.
 *
 *                              ---------------
 *
 *      Note that a thread waiting for itself to exit (which is about as
 *      useful as contemplating your navel) is considered an error (deadlock).
 *
 *      All thread methods are reentrant.  All Thread methods are thread
 *      safe, with the exception of the constructor.  The result of calling
 *      Thread::Enter() multiple times on the same thread is undefined.
 *
 *****************************************************************************/
class Thread
{
public:
    friend class ThreadPool;

    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This method constructs the housekeeping C++ object for threads.
     *      Note that the constructor does NOT create the thread.
     *
     *  Input Parameters:
     *      stackSize - the initial stack size for the thread.
     *      entryPoint - a pointer to the function that the thread is to execute
     *
     *  Notes:
     *      Passing a stackSize of 0 to this function is a hint to the operating
     *      system to use the default thread stack size.  Usually, passing 0
     *      is recommended, as the thread creation can be significantly faster
     *      when the default is used.
     *
     *  See Also:
     *      ~Thread()
     ************************************************************************/
    Thread(int _stackSize, ITS_THREAD_FUNC _entryPoint,
           ITS_BOOLEAN _running = ITS_TRUE,
           size_t objSize = sizeof(ITS_THREAD))
    {
        /* use C allocator to avoid new()/delete() overloads */
        thread = (ITS_THREAD *)calloc(1, objSize);
        ITS_THROW_ASSERT(thread != NULL);

        thread->thread.stackSize = _stackSize;
        thread->thread.threadFunc = _entryPoint;
        thread->thread.runnable = _running;
        thread->thread.constructed = ITS_FALSE;
    }
    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This method cleans up after a thread.  It may be safely invoked
     *      before the thread exits, but it is up to the caller to ensure that
     *      the housekeeping object is not needed after it is destroyed.
     *
     *  Notes:
     *      A thread may call this for itself.
     *
     *  See Also:
     *      Thread()
     ************************************************************************/
    virtual ~Thread()
    {
        if (thread->thread.constructed)
        {
            THREAD_DeleteThread(thread);
        }

        free(thread);
    }

    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This method actully creates a thread.  The thread is created
     *      "running", and will begin executing the C function provided by
     *      the constructor.
     *
     *  Return Value:
     *      If the thread is created successfully, ITS_SUCCESS is returned.
     *      Any other return code indicates an error.
     *
     ************************************************************************/
    int
    Enter(void *arg)
    {
        int ret = THREAD_CreateThread((ITS_THREAD *)thread,
                                      thread->thread.stackSize,
                                      thread->thread.threadFunc,
                                      arg,
                                      thread->thread.runnable);

        thread->thread.constructed = true;

        return (ret);
    }
    /*.implementation:static,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This function should be called for a thread that wants to safely
     *      exit (returning its resources to the process).
     *
     *  Input Parameters:
     *      status - a pointer value to return to the process.  If an entity
     *          is waiting on this thread, this is the value the entity
     *          will receive.
     *
     ************************************************************************/
    static void
    Exit(void *status)
    {
        THREAD_ThreadExit(status);
    }
    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This function suspends a thread.  In practice, this means the thread
     *      will not be scheduled until it resumes.  The result of suspending a
     *      suspended thread is not defined.
     *
     *  Return Value:
     *      If the thread was suspended, ITS_SUCCESS is returned.
     *      Any other return value indicates an error.
     *
     *  Notes:
     *      A thread may call this for itself.
     *
     *  See Also:
     *      Resume()
     ************************************************************************/
    int
    Suspend()
    {
        return THREAD_ThreadSuspend(thread);
    }
    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This function resumes a suspended thread.  In practice, this means
     *      the thread will be returned to the scheduler.  The result of
     *      resuming a running thread is undefined.
     *
     *  Return Value:
     *      If the thread was successfully resumed, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntellISS7 error.
     *
     *  See Also:
     *      Suspend()
     ************************************************************************/
    int
    Resume()
    {
        return THREAD_ThreadResume(thread);
    }
    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This function can be used to kill a thread.  This function is
     *      included for completeness only and should NOT be used.  You have
     *      been warned.
     *
     *  Return Value:
     *      If the thread was killed, ITS_SUCCESS is returned.
     *      Any other return value indicate an IntelliSS7 error.
     *
     ************************************************************************/
    int
    Kill()
    {
        return THREAD_KillThread(thread);
    }
    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      This method can be used by the caller to wait for the return
     *      code of a spawned thread.
     *
     *  Input Parameters:
     *      status - the address of a pointer where the return code should be
     *          placed
     *
     *  Return Value:
     *      If the thread exists, and exited, ITS_SUCCESS is returned
     *      Any other return code indicates an IntelliSS7 error.
     *
     ************************************************************************/
    int
    WaitFor(void **status)
    {
        return THREAD_WaitForThread(thread, status);
    }

    ITS_THREAD GetID()  { return *thread; }
    ITS_THREAD *GetPtr(){ return thread; }

    /*.implementation:public,inline,Thread
     ************************************************************************
     *  Purpose:
     *      Retrieve the thread identifier of the calling thread.
     *
     *  Return Value:
     *      ITS_UINT - thread identifier of the calling thread.
     *
     *  Note:
     *      For internal use only (see underlying C function comment).
     *
     ************************************************************************/
    static ITS_UINT 
    GetCurrentThreadID()
    {
        return THREAD_GetCurrentThreadID();
    }

protected:
    ITS_THREAD *thread;

private:
    /* sorry folks, no copying these */
    Thread() {}
    Thread(Thread&) {}
    Thread& operator=(Thread&) { return *this; }
};

/*
 * a class for the C++ purists (abstract base).
 */
class VirtualThread : public Thread
{
public:
    VirtualThread(int stackSize, bool running, void *arg)
        : Thread(stackSize, (ITS_THREAD_FUNC)CallVirtual,
                 running ? ITS_TRUE : ITS_FALSE)
    {
        thread->thread.threadArg = arg;

        Enter(this);
    }

    virtual ~VirtualThread()
    {
    }

    /* user needs to supply */
    virtual void Execute(void *arg) = 0;

private:
    /* C/C++ linkage */
    static THREAD_RET_TYPE
    CallVirtual(void *arg)
    {
        VirtualThread *thr = (VirtualThread *)arg;

        thr->Execute(thr->thread->thread.threadArg);

        THREAD_NORMAL_EXIT;
    }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_THREAD_H */
