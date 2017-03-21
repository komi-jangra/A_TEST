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
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2002/02/25 21:41:12  mmiers
 * LOG: Try something else.
 * LOG:
 * LOG: Revision 5.2  2002/02/25 21:27:31  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.3  2001/05/04 14:30:52  mmiers
 * LOG: A few bug fixes from PR4.
 * LOG:
 * LOG: Revision 4.2  2001/05/02 19:58:55  mmiers
 * LOG: Add thread pool shutdown logic.  People using the C API
 * LOG: need to convert to WORKER_GetExit() instead of TPOOL_THREAD_EXIT().
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.22  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 * LOG: Revision 3.21  2001/04/11 20:10:08  mmiers
 * LOG:
 * LOG: Minor tweaks.
 * LOG:
 * LOG: Revision 3.20  2001/04/05 19:19:19  mmiers
 * LOG: Workaround.
 * LOG:
 * LOG: Revision 3.19  2001/04/05 18:40:09  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.18  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.17  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.16  2001/04/02 19:50:14  mmiers
 * LOG: Solaris build.
 * LOG:
 * LOG: Revision 3.15  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.14  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.13  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 3.12  2001/03/01 22:10:46  mmiers
 * LOG: Added thread pool.  Need application and serious thought on how
 * LOG: to glue it together.
 * LOG:
 * LOG: Revision 3.11  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.10  2001/02/05 22:43:58  hxing
 * LOG: Order of namespace termination outside HAVE_STL
 * LOG:
 * LOG: Revision 3.9  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.8  2001/01/31 23:40:53  mmiers
 * LOG: Work around thread data duplication.
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:21:50  hxing
 * LOG: More bugs to remove from new ThreadPoolEntry et al.
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:11:08  mmiers
 * LOG: Extra constructor.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:00:01  mmiers
 * LOG: Typo fix, thread bug.
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 19:07:11  mmiers
 * LOG: add namespace
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/04/25 23:03:30  mmiers
 * LOG:
 * LOG:
 * LOG: Update C service test.
 * LOG:
 * LOG: Revision 2.4  2000/04/25 14:52:53  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.  Also remove race from thread
 * LOG: pool where allocated but not started thread could miss pool
 * LOG: destruction [Ricardo].
 * LOG:
 * LOG: Revision 2.3  2000/04/24 16:50:07  mmiers
 * LOG:
 * LOG:
 * LOG: Fix for growth-without-end thread pool list.
 * LOG:
 * LOG: Revision 2.2  1999/12/17 22:11:17  mmiers
 * LOG: DEC tweaks.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:59  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:47  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1999/08/23 01:28:51  labuser
 * LOG:
 * LOG:
 * LOG: Don't include the namespace.  HPUX chokes on this.
 * LOG:
 * LOG: Revision 1.18  1999/08/22 20:42:26  labuser
 * LOG:
 * LOG:
 * LOG: Some thread pool implementation helpers.
 * LOG:
 * LOG: Revision 1.17  1999/08/22 02:51:31  mmiers
 * LOG:
 * LOG:
 * LOG: Friends so that linkage works ok.
 * LOG:
 * LOG: Revision 1.16  1999/08/22 02:07:37  mmiers
 * LOG:
 * LOG:
 * LOG: Create a synchronization object for thread pools.
 * LOG:
 * LOG: Revision 1.15  1999/06/30 17:23:27  mmiers
 * LOG:
 * LOG:
 * LOG: Sun wants a forward declaration for a class name before it is used
 * LOG: as an argument.
 * LOG:
 * LOG: Revision 1.14  1998/11/19 00:36:20  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.13  1998/10/28 16:16:34  mmiers
 * LOG: Fix for NT build.
 * LOG:
 * LOG: Revision 1.12  1998/10/28 03:08:22  mmiers
 * LOG: Finish thread pool implementation.
 * LOG:
 * LOG: Revision 1.10  1998/10/27 17:53:12  mmiers
 * LOG: Start adding C based thread pool.
 * LOG:
 * LOG: Revision 1.9  1998/09/22 16:01:26  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.8  1998/07/10 16:03:37  mmiers
 * LOG: Add some warnings about throwing exceptions from the app selector callback.
 * LOG: Add a method to the threadpool for returning an entry to the pool
 * LOG: without dispatching it.
 * LOG:
 * LOG: Revision 1.7  1998/07/03 16:05:47  hdivoux
 * LOG: Make ThreadPoolThread and ThreadPool destructors virtual.
 * LOG:
 * LOG: Revision 1.6  1998/06/05 17:20:16  whu
 * LOG: Don't let the user set a null function to execute on a thread.
 * LOG:
 * LOG: Revision 1.5  1998/06/02 19:43:15  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.4  1998/06/01 16:35:20  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.3  1998/05/29 03:31:33  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.2  1998/05/29 00:32:55  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.1  1998/05/28 17:28:42  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_THREAD_POOL_H
#define ITS_THREAD_POOL_H

#include <its_mlist.h>
#include <its_thread.h>
#include <its_semaphore.h>

#ident "$Id: its_thread_pool.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * per-thread structure
 */
typedef struct _tpool_thread TPOOL_THREAD;

typedef struct
{
    void            (*thisFunc)(TPOOL_THREAD *, void *);
    void*           thisArg;
    ITS_BOOLEAN     exit;
    void*           back;       /* points to ThreadPoolThread in C++ */
    struct _tpool   *pool;      /* parent pool (for HMI) */
}
TPOOL_ThreadObjectPart;

struct _tpool_thread
{
    ITS_CoreObjectPart      core;
    ITS_ThreadPart          thread;
    TPOOL_ThreadObjectPart  tpool;
};

#define TPOOL_THREAD_FUNC(x) \
    (((TPOOL_THREAD *)(x))->tpool.thisFunc)

#define TPOOL_THREAD_ARG(x) \
    (((TPOOL_THREAD *)(x))->tpool.thisArg)

#define TPOOL_THREAD_EXIT(x) \
    (((TPOOL_THREAD *)(x))->tpool.exit)

#define TPOOL_THREAD_BACK(x) \
    (((TPOOL_THREAD *)(x))->tpool.back)

#define TPOOL_THREAD_POOL(x) \
    (((TPOOL_THREAD *)(x))->tpool.pool)

/*
 * class record
 */
ITSDLLAPI extern ITS_ClassRec itsTPOOLTHREAD_ClassRec;
ITSDLLAPI extern ITS_Class    itsTPOOLTHREAD_Class;

/*
 * creation and destruction
 */
TPOOL_THREAD *  TPOOLTHREAD_Create(int stackSize);
void            TPOOLTHREAD_Destroy(TPOOL_THREAD *thr);

/*
 * this structure is allocated on the heap and passed as the argument to
 * the TPOOL_THREAD function (aka PoolFunc for TPOOL objects) to
 * provide the thread with information it needs for processing.  It is
 * passed on the heap as the CreatePool() method may return before
 * the threads it creates can start; by the same token, it cannot use
 * a structure on the stack as a thread it creates may not start before
 * the next thread is created.
 */
typedef struct
{
    TPOOL_THREAD*           entry;
    struct _tpool*          pool;
    struct _tpool_heap_obj* refCounter;
}
TPOOL_THREAD_ARG;

typedef void (*TPOOL_FUNC)(struct _tpool_thread *, void *);

/*
 * this structure is used as a reference counting mechanism for destroying
 * TPOOL_THREADs after the TPOOL object has been destroyed.
 */
typedef struct _tpool_heap_obj
{
    MLIST_Manager*  avail;
    MLIST_Manager*  busy;
    volatile int    thrCount;
    ITS_BOOLEAN     exit;
}
TPOOL_HEAP_OBJ;

/*
 * tpool object record
 */
typedef struct
{
    MLIST_Manager*  availThreads;
    MLIST_Manager*  busyThreads;
    TPOOL_HEAP_OBJ* heapObj;
    void*           back;
    void*           userData;
}
TPOOL_ObjectPart;

typedef struct _tpool
{
    ITS_CoreObjectPart    core;
    TPOOL_ObjectPart      tpool;
}
TPOOL;

#define TPOOL_AVAIL_THREADS(x) \
    (((TPOOL *)(x))->tpool.availThreads)

#define TPOOL_BUSY_THREADS(x) \
    (((TPOOL *)(x))->tpool.busyThreads)

#define TPOOL_HEAP_OBJ(x) \
    (((TPOOL *)(x))->tpool.heapObj)

#define TPOOL_USER_DATA(x) \
    (((TPOOL *)(x))->tpool.userData)

#define TPOOL_BACK(x) \
    (((TPOOL *)(x))->tpool.back)

/*
 * tpool class record
 */
typedef struct
{
    ITS_SEMAPHORE     syncObj;
}
TPOOL_ClassPart;

typedef struct
{
    ITS_CoreClassPart  coreClass;
    TPOOL_ClassPart    tpoolClass;
}
TPOOL_ClassRec, *TPOOL_Class;

#define TPOOL_CLASS_SYNC_OBJ(x) \
    (((TPOOL_Class)(x))->tpoolClass.syncObj)

ITSDLLAPI extern TPOOL_ClassRec   itsTPOOL_ClassRec;
ITSDLLAPI extern TPOOL_Class      itsTPOOL_Class;

#define TPOOL_CLASS_NAME    "TPOOL_Class"

/*
 * user defined function.
 */
typedef TPOOL_THREAD*   (*TPOOL_CreateThread)(TPOOL* pool, int stackSize);
typedef ITS_BOOLEAN     (*TPOOL_FindThread)(TPOOL* pool, TPOOL_THREAD *thr,
                                            void *userData);

ITSDLLAPI TPOOL *         TPOOL_InitPool(void *userData);
ITSDLLAPI void            TPOOL_DestroyPool(TPOOL* pool);
ITSDLLAPI int             TPOOL_CreatePool(TPOOL* pool, int numThreads, int thrStackSize,
                                           TPOOL_CreateThread thrCreator);
ITSDLLAPI int             TPOOL_AddThreadToPool(TPOOL* pool, int stackSize,
                                                TPOOL_CreateThread thrCreator);
ITSDLLAPI int             TPOOL_RemThreadFromPool(TPOOL* pool, TPOOL_THREAD *thr);
ITSDLLAPI int             TPOOL_FindThreadInPool(TPOOL *pool, TPOOL_FindThread thrFinder,
                                                 TPOOL_THREAD **thr, void *userData);
ITSDLLAPI int             TPOOL_GetFirstAvailThread(TPOOL* pool, TPOOL_THREAD** first);
ITSDLLAPI int             TPOOL_ReturnToAvailThreads(TPOOL* pool, TPOOL_THREAD* thr);
ITSDLLAPI int             TPOOL_DispatchOnThread(TPOOL_THREAD* thr,
                                                 TPOOL_FUNC func, void *arg);
ITSDLLAPI int             TPOOL_Dispatch(TPOOL* pool, TPOOL_FUNC func, void *arg);

ITSDLLAPI void            TPOOL_WaitForDestroyComplete();

ITSDLLAPI THREAD_RET_TYPE TPOOL_ThreadFunc(void *arg);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

class ThreadPool;
class ThreadPoolThread;

typedef void (*ITS_ThreadCallFunc)(class ThreadPoolThread *, void *);

/*.interface:ThreadPoolThread
 *****************************************************************************
 *  Interface:
 *      ThreadPoolThread
 *
 *  Purpose:
 *      A thread pool thread is a thread that lives in a pool of similar
 *      or related threads.  The ThreadPoolThread inherits the behavior
 *      if Thread; see
 *      <A HREF=its_thread.html>Thread</A>
 *      for details about Thread.
 *
 *      The ThreadPoolThread class extends the Thread with information
 *      necessary for manipulating threads contained in the pool.  This
 *      includes such information as
 *          o   Which function they should execute
 *          o   The argument to pass to the function
 *          o   A flag to indicate that a thread should exit.
 *      The ThreadPool class is a friend of ThreadPoolThread, and
 *      thus has access to this information.
 *
 *      ThreadPoolThreads cannot be used standalone; they are only
 *      intended for use with a thread pool.  See
 *      <A HREF=#tpTag1>ThreadPool</A>
 *      for more information about thread pools.  Note that they *can*
 *      be created standalone, but that there is no way to change their thread
 *      function.  The execution function set for ThreadPoolThread objects
 *      is the function ThreadPool::PoolFunc, and is set by the constructor.
 *
 *  Usage:
 *      This object should not be created standalone.
 *
 *      The functions executed by threads of this type have a different
 *      signature than straight Thread functions.  The function signature
 *      is defined as taking two arguments: the first is a pointer to the
 *      ThreadPoolThread object, the second is the standard arg pointer
 *      value (which is common to ThreadPoolThread and Thread).
 *      This allows ThreadPoolThread functions to find and/or manipulate
 *      their own thread and exit flag.
 *
 *****************************************************************************/
class ThreadPoolThread : public Thread
{
public:
    friend class ThreadPool;

    ThreadPoolThread(int stackSize, size_t objSize = sizeof(TPOOL_THREAD))
        : Thread(stackSize, TPOOL_ThreadFunc, ITS_FALSE, objSize),
          cppFunc(NULL)
    {
        int dummy = 0, ret;

        ret = Initialize(dummy, stackSize);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }
    virtual ~ThreadPoolThread()
    {
        // superclass handles this.
    }

    /*.implementation:public,inline,ThreadPoolThread
     **************************************************************************
     *  Purpose:
     *      This method can be invoked by consumers of this class to determine
     *      if the pool object containing this thread has been destroyed.
     *      When this method returns ITS_TRUE, the user should return from
     *      the function they are executing.
     *
     *  Return Value:
     *      ITS_TRUE - the thread should exit, as the containing pool has been
     *          destroyed.
     *      ITS_FALSE - the thread may continue executing.
     *
     **************************************************************************/
    virtual ITS_BOOLEAN
    GetExit()
    {
        return TPOOL_THREAD_EXIT(thread);
    }

    /*.implementation:public,inline,ThreadPoolThread
     **************************************************************************
     *  Purpose:
     *      This method can be invoked by consumers of the thread pool class
     *      to signal this thread that the pool object containing this thread
     *      has been destroyed.
     *
     **************************************************************************/
    virtual void
    SetExit(ITS_BOOLEAN exitState)
    {
        TPOOL_THREAD_EXIT(thread) = exitState;
    }

private:
    ITS_ThreadCallFunc  cppFunc;

    /*.implementation:private,inline,ThreadPoolThread
     **************************************************************************
     *  Purpose:
     *      Intialize this portion of an ITS_THEAD subclass.
     *
     **************************************************************************/
     int
     Initialize(int dummy, ...)
     {
        int ret;
        va_list args;

        va_start(args, dummy);

        if (!ITS_CLASS_INITTED(itsTPOOLTHREAD_Class))
        {
            ret = ITS_InitializeClass(itsTPOOLTHREAD_Class);

            ITS_ASSERT(ret == ITS_SUCCESS);
        }

        ret = ITS_CLASS_OBJECT_INSTANTIATE(itsTPOOLTHREAD_Class)(
                                                           (ITS_Object)thread,
                                                           args);

        va_end(args);

        /* a kludge to avoid the wrong class record. */
        /* see its_thread_pool.c:TPOOL_CreatePool:THREAD_CreateThread */
        ITS_OBJ_CLASS(thread) = itsTPOOLTHREAD_Class;

        TPOOL_THREAD_BACK(thread) = this;

        return (ret);
    }
};

/*.interface:ThreadPoolEntry
 *****************************************************************************
 *  Interface:
 *      ThreadPoolEntry
 *
 *  Purpose:
 *      The thread pool consists of lists of these ThreadPoolThreads, kept
 *      in two lists (a busy and a free list).  The lists are MList
 *      objects; see
 *      <A HREF=its_mlist.html>MList</A>
 *      for details.
 *
 *      For more information on thread pools, see
 *      <A HREF=#tpTag1>ThreadPool</A>.
 *
 *  Usage:
 *
 *****************************************************************************/
class ThreadPoolEntry
{
public:
    friend class ThreadPool;

    /*.implementation:public,inline,ThreadPoolEntry
     **************************************************************************
     *  Purpose:
     *      This method constructs an ThreadPoolEntry.
     *
     *  Notes:
     *      The default constructor can only be used when the user knows
     *      that a call to ThreadPool::GetFirstAvailThread() or
     *      ThreadPool::Dispatch() will be called.
     *
     *  See Also:
     *      ~ThreadPoolEntry()
     **************************************************************************/
    ThreadPoolEntry()
        : poolThread(NULL)
    {
    }
    /*.implementation:public,inline,ThreadPoolEntry
     **************************************************************************
     *  Purpose:
     *      This method constructs an ThreadPoolEntry.  It need do
     *      no more that initialize the thread member variable.
     *
     *  Input Parameters:
     *      _thread - a pointer to the Thread object contained by this
     *          entry
     *
     *  See Also:
     *      ~ThreadPoolEntry()
     **************************************************************************/
    ThreadPoolEntry(TPOOL_THREAD* _thread)
        : poolThread((ThreadPoolThread *)TPOOL_THREAD_BACK(_thread))
    {
    }

    /*.implementation:public,inline,ThreadPoolEntry
     **************************************************************************
     *  Purpose:
     *      This method destroys an ThreadPoolEntry object.
     *
     *  See Also:
     *      ThreadPoolEntry()
     **************************************************************************/
    virtual ~ThreadPoolEntry()
    {
    }

    /*.implementation:public,inline,ThreadPoolEntry
     **************************************************************************
     *  Purpose:
     *      This method provides access to the ThreadPoolThread pointer
     *      contained in this object.  This member is not required when
     *      subclassing from ITS_ListEntry.
     *
     *  Return Value:
     *      The value of the thread member variable.
     *
     **************************************************************************/
    ThreadPoolThread*
    GetThread()
    {
        return poolThread;
    }

private:
    ThreadPoolThread* poolThread;
};

/*
 * helper.
 */
extern "C"
{
    static inline ITS_BOOLEAN LocateThread(TPOOL *pool,
                                           TPOOL_THREAD *thr,
                                           void *userData);
}

/*.interface:ThreadPool
 *****************************************************************************
 *  <A NAME=#tpTag1></A>
 *  Interface:
 *      ThreadPool
 *
 *  Purpose:
 *      The ThreadPool object is a container object for manipulating
 *      a pool of thread resources.  It is intended to allow operations to
 *      be dispatched on different threads, while each operation proceeds
 *      in ignorance of any and all operations happening simultaneously.
 *      For details about threads, refer to the ThreadPoolThread
 *      interface description above.
 *
 *      The ThreadPool is designed to work hand in hand with the
 *      IntelliSS7 routing and transport mechanisms in a multithreaded
 *      environment.  Applications can combine the application selection
 *      available via the routing subsystem with the transport mechanism
 *      to dispatch messages related to a single unit-of-work to the
 *      thread executing that unit-of-work.  For more information on how
 *      all of these associations are handled, see
 *      <A HREF=its_worker.html>ITS_Worker</A>.
 *
 *  Usage:
 *      The easiest way to show how to use the ThreadPool object
 *      is to include some sample code.  Below is one of our unit-tests:
 *      ------------------------------------------------------------------
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
 *      #include <its_thread_pool.h>
 *
 *      #if defined(ITS_NAMESPACE)
 *      using namespace its;
 *      #endif
 *
 *      ------------------------------------------------------------------
 *
 *      Here we break and talk about modifying the default
 *      ThreadPoolThread.  If a thread requires some information about
 *      the task it is to perform, we can subclass from ThreadPoolThread
 *      and add the information we need.
 *
 *      In fact, this is *exactly* what ITS_Worker does.  ITS_Worker
 *      inherits from ThreadPoolThread, but associates a) a transport
 *      and b) a resource file with each thread.  The transport allows
 *      the thread to talk with other threads via ITS_Transport::PutEvent(),
 *      and receive information from its own transport via GetNextEvent().
 *      The resource file allows each identified worker to initialize
 *      their transport with unique information (such as adjacent point
 *      code, etc.).  See
 *      <A HREF=its_transport.html>ITS_Transport</a>
 *      for details about transports, and
 *      <A HREF=its_iniparse.html>ITS_ResourceFile</A>
 *      for details about resource files.
 *
 *      ------------------------------------------------------------------
 *      //
 *      // test thread inheriting from ThreadPoolThread
 *      // This shows how the user can extend the ThreadPoolThread
 *      // to contain information that the user wishes to associate
 *      // with a thread.
 *      //
 *      class TestThread : public ThreadPoolThread
 *      {
 *      public:
 *          TestThread(int stackSize)
 *              : ThreadPoolThread(stackSize)
 *          {
 *          }
 *          ~TestThread()
 *          {
 *          }
 *
 *          int which;
 *      };
 *
 *      ------------------------------------------------------------------
 *
 *      Next we demonstrate how to subclass from ThreadPool so that
 *      the derived class creates the kind of ThreadPoolThread that
 *      we want.  We *could* possibly have used templates for
 *      ThreadPool, but the additional required to do this (and for
 *      the user to comprehend the implementation) did not seem worth
 *      it, compared to a single virtual function override -- that of
 *      ThreadPool::CreatePoolThread():
 *
 *      ------------------------------------------------------------------
 *      //
 *      // test creating an ThreadPool implementation
 *      // This example shows how to modify the ThreadPool base
 *      // class if the user wishes to define their own ThreadPoolThread
 *      // derivative.  As you can see, the user need only define a new
 *      // method for creating threads for the thread pool.
 *      //
 *      class ThreadPool : public ThreadPool
 *      {
 *      public:
 *          ThreadPool()
 *              : ThreadPool(), count(0)
 *          {
 *          }
 *
 *          // override
 *          virtual
 *          ThreadPoolThread* CreatePoolThread(int stackSize)
 *          {
 *              TestThread* work = new TestThread(stackSize);
 *
 *              work->which = count;
 *              count++;
 *
 *              return (ThreadPoolThread *)work;
 *          }
 *
 *      private:
 *          int count;
 *      };
 *
 *      ------------------------------------------------------------------
 *
 *      As mentioned, the signature for ThreadPoolThread work functions
 *      is different from that of Thread.  One nice side effect is
 *      that we need no longer be aware of platform differences.
 *
 *      ------------------------------------------------------------------
 *      //
 *      // This is an example of the kind of functions that can
 *      // be written for dispatch by the threads in a thread pool.
 *      // Note the signature of the function, which is different
 *      // from that of Thread.
 *      //
 *      void
 *      WorkFunc1(ThreadPoolThread *thr, void *arg)
 *      {
 *          printf("Func 1: thr %d\n", ((TestThread *)thr)->which);
 *          fflush(stdout);
 *
 *          TIMERS_Sleep(5);
 *      }
 *
 *      //
 *      // This is a second example of a thread pool dispatch function
 *      //
 *      void
 *      WorkFunc2(ThreadPoolThread *thr, void *arg)
 *      {
 *          printf("Func 2: thr %d\n", ((TestThread *)thr)->which);
 *          fflush(stdout);
 *
 *          TIMERS_Sleep(2);
 *      }
 *
 *      //
 *      // It's easiest if this is global
 *      //
 *      ThreadPool* pool = NULL;
 *
 *      int
 *      main(int argc, char **argv)
 *      {
 *          // try to create a thread pool containing 100 threads
 *          try
 *          {
 *              pool = new ThreadPool();
 *
 *              pool->CreatePool(100, 0);
 *          }
 *          catch (exception& ex)
 *          {
 *              printf("Caught exception creating pool\n");
 *
 *              exit(0);
 *          }
 *
 *          // Now try to dispatch 300 functions on the 100 threads.
 *          for (int i = 0; i < 300; i++)
 *          {
 *      ------------------------------------------------------------------
 *
 *      First we give an example of what we call "anonymous" dispatch,
 *      where a unit-of-work is given to the first available thread.
 *      In this case, we are ignorant of which thread gets dispatched,
 *      and the thread is operating without any context beyond that which
 *      it had when it was created.
 *
 *      ------------------------------------------------------------------
 *              // Dispatch WorkFunc1 using the anonymous thread method
 *              if (i & 1)
 *              {
 *                  if (pool->Dispatch(WorkFunc1, NULL) != ITS_SUCCESS)
 *                  {
 *                      printf("Out of dispatch threads: Func1\n");
 *                      TIMERS_Sleep(1);
 *                  }
 *              }
 *              // Dispatch WorkFunc2 using the known thread method.
 *              else
 *              {
 *      ------------------------------------------------------------------
 *
 *      Second, we show an example of what we call "explicit" dispatch.
 *      Using this method, we are aware of (or can find) the identity
 *      of each thread when it is dispatched.  Because of this, we
 *      can store context information about which thread is processing
 *      which unit-of-work.  We can also modify the thread itself so
 *      that it knows which unit-of-work to expect.
 *
 *      It turns out that this information is *exactly* what the ITS_Worker
 *      class needs, and what IntelliSS7 needs; when a new unit-of-SS7-work
 *      begins, we can allocate a thread to handle it.  The thread can
 *      be informed of what unit-of-work to expect, and we can record
 *      which thread to dispatch unit-of-work related information to.
 *
 *      ------------------------------------------------------------------
 *                  ThreadPoolEntry ent;
 *
 *                  // first locate an available thread
 *                  if (pool->GetFirstAvailThread(ent) == ITS_SUCCESS)
 *                  {
 *                      //
 *                      // dispatch on that thread.  Note at this point
 *                      // you could modify per thread information
 *                      //
 *                      // ent.GetThread()->count = 5;
 *                      //
 *                      if (pool->DispatchOnThread(ent,
 *                                                 WorkFunc2,
 *                                                 NULL) != ITS_SUCCESS)
 *                      {
 *                          printf("Out of dispatch threads: Func2\n");
 *                          TIMERS_Sleep(1);
 *                      }
 *                  }
 *              }
 *          }
 *
 *          delete pool;
 *
 *          Thread::Exit(0);
 *
 *          return (0);
 *      }
 *
 *      -----------------------------------------------------------------
 *
 *      A single instance of ThreadPool is thread-safe in general
 *      use.  That is, different threads can call methods on the same
 *      ThreadPool object without worrying about serialization of
 *      access to the thread pool.  The exceptions to this rule are
 *      the constructor, the destructor, and the CreateThreadPool()
 *      method.  Note that the ThreadPool object *can* be destroyed
 *      while threads are running -- the threads kill themselves in
 *      a delayed action; the last thread to exit destroys the
 *      availThreads and busyThreads lists.
 *
 *
 *****************************************************************************/
/*
 * the pool itself
 */
class ThreadPool
{
public:
    friend class ThreadPoolThread;

    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      This method constructs an ThreadPool object.  It creates
     *      ITS_MList(s) availThreads and busyThreads. Further, it allocates
     *      an object of type ITS_ThreadPoolHeapObj, which it intializes with
     *      the pointers to the ITS_MList(s).
     *
     ************************************************************************/
    ThreadPool()
    {
        pool = TPOOL_InitPool(this);

        ITS_THROW_ASSERT(pool != NULL);

        TPOOL_BACK(pool) = this;
    }

    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      This method destroyes the ThreadPool object.  The actions
     *      taken by this method are very simple; 
     *
     ************************************************************************/
    virtual
    ~ThreadPool()
    {
        TPOOL_DestroyPool(pool);
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method provides the default implementation of thread pool
     *      thread creation for the ThreadPool object.  It is expected
     *      that subclasses of ThreadPool redefine this method to create
     *      ThreadPoolThread subclasses as needed by the application;
     *      it is provided for mostly for documentation reasons.
     *
     *  Input Parameters:
     *      stackSize - the size of the stack to allocate for the created
     *          thread.  If the value 0 is given for stackSize, the
     *          operating system will provide a default value.
     *
     *  Return Value:
     *      A pointer to the allocated object
     *
     *  Notes:
     *      This method can throw exceptions if the application is running
     *      out of memory.
     *
     **************************************************************************/
    virtual ThreadPoolThread*
    CreatePoolThread(int stackSize)
    {
        return new ThreadPoolThread(stackSize);
    }

    /*.implementation:static,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Provide a common interface to the C allocator.
     *
     *  Input Parameters:
     *      p - the TPOOL to create into
     *      stackSize - stack size for each thread
     *
     ************************************************************************/
    static TPOOL_THREAD *
    MakePoolThread(TPOOL *p, int stackSize)
    {
        ThreadPool *pool = (ThreadPool *)TPOOL_BACK(p);
        ThreadPoolThread *tmp;

        tmp = pool->CreatePoolThread(stackSize);

        ITS_THROW_ASSERT(tmp != NULL);

        return ((TPOOL_THREAD *)(tmp->thread));
    }

    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Create the thread pool
     *
     *  Input Parameters:
     *      numThreads - number of threads in the pool
     *      thrStackSize - stack size for each thread
     *
     ************************************************************************/
    virtual void
    CreatePool(int numThreads, int thrStackSize)
    {
        TPOOL_CreatePool(pool, numThreads, thrStackSize,
                         (TPOOL_CreateThread)MakePoolThread);
    }

    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Add to the thread pool
     *
     *  Input Parameters:
     *      thrStackSize - stack size for each thread
     *
     ************************************************************************/
    virtual int
    AddThread(int thrStackSize)
    {
        return TPOOL_AddThreadToPool(pool, thrStackSize,
                                     (TPOOL_CreateThread)MakePoolThread);
    }
    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Remove from the thread pool
     *
     *  Input Parameters:
     *      thrStackSize - stack size for each thread
     *
     ************************************************************************/
    virtual int
    RemThread(int thrStackSize, ThreadPoolThread& thr)
    {
        return TPOOL_RemThreadFromPool(pool, (TPOOL_THREAD *)thr.thread);
    }
    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Find a thread in the thread pool
     *
     *  Input Parameters:
     *      thrStackSize - stack size for each thread
     *
     ************************************************************************/
    virtual int
    FindThread(ThreadPoolThread **thr, void *userData)
    {
        TPOOL_THREAD *tp;
        int ret;

        ITS_ASSERT(thr != NULL);

        tp = NULL;
        ret = TPOOL_FindThreadInPool(pool, LocateThread, &tp, userData);
        if (ret == ITS_SUCCESS && tp)
        {
            *thr = (ThreadPoolThread *)TPOOL_THREAD_BACK(tp);
        }

        return (ret);
    }
    /*.implementation:public,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Thread match method.  User must override.
     *
     *  Input Parameters:
     *      thrStackSize - stack size for each thread
     *
     ************************************************************************/
    virtual bool
    MatchThread(ThreadPoolThread *thr, void *userData)
    {
        return (false);
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method attempts to dequeue the head of the list of free
     *      threads.  If no threads are available, an error will be returned.
     *
     *  Input Parameters:
     *      first - a reference to the ThreadPoolEntry object to populate
     *          with information from the dequeued node
     *
     *  Return Value:
     *      If a node was available, and dequeued, ITS_SUCCESS is returned.
     *      Any other return value indicates that either no free threads were
     *          available, or that an IntelliSS7 error occurred.
     *
     *  Notes:
     *      Clever subclasses of ThreadPool (such as one that dynamically
     *      creates threads when the pool is empty) may want to override this
     *      method with one of their own.
     *
     *  See Also:
     *      DispatchOnThread()
     **************************************************************************/
    virtual int
    GetFirstAvailThread(ThreadPoolEntry& first)
    {
        int ret;
        TPOOL_THREAD *thr = NULL;

        ret = TPOOL_GetFirstAvailThread(pool, &thr);

        if (thr)
        {
            first.poolThread = (ThreadPoolThread *)TPOOL_THREAD_BACK(thr);
        }

        return (ret);
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      In some error conditions, we may have allocated a thread but for
     *      whatever reason we might not want to dispatch it but return it to
     *      the free pool.
     *
     *  Input Parameters:
     *      thr - the thread pool entry to return to the avail pool
     *
     *  Return Value:
     *      Returns the result off AddTail on the availThreads list.
     *
     **************************************************************************/
    virtual int
    ReturnToAvailThreads(ThreadPoolEntry& thr)
    {
        ITS_THROW_ASSERT(thr.poolThread != NULL);

        return TPOOL_ReturnToAvailThreads(pool, (TPOOL_THREAD *)thr.poolThread->
                                                                        thread);
    }

    /*.implementation:static,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Call a C++ thread function
     *
     *  Input Parameters:
     *      thread - the TPOOL_THREAD to dispatch
     *      arg - the arg to pass to the thread
     *
     ************************************************************************/
    static void
    CallThreadFunc(TPOOL_THREAD *thread, void *arg)
    {
        ThreadPoolThread *tmp = (ThreadPoolThread *)TPOOL_THREAD_BACK(thread);

        try
        {
    	    (tmp->cppFunc)(tmp, arg);
        }
        catch (GenericException& iex)
        {
            iex.Log();
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

#endif  // defined(NDEBUG)
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method provides a way for the user to dispatch a function
     *      on a known thread.  The user should have acquired the thread by
     *      calling the method GetFirstAvailThread().
     *
     *  Input Parameters:
     *      ent - the ThreadPoolEntry object containing the dispatch thread
     *      func - the funtion the thread is to execute
     *      arg - the argument to the function to execute
     *
     *  Return Value:
     *      If the function was successfully dispatched, ITS_SUCCESS is
     *          returned.
     *      Any other return value indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *      Clever subclasses of ThreadPool (such as one that dynamically
     *      creates threads when the pool is empty) may want to override this
     *      method with one of their own.
     *
     *  See Also:
     *      GetFirstAvailThread()
     **************************************************************************/
    virtual int
    DispatchOnThread(ThreadPoolEntry& ent,
                     ITS_ThreadCallFunc func, void *arg)
    {
        ThreadPoolThread* thr = ent.GetThread();

        ITS_THROW_ASSERT(thr != NULL);
        ITS_THROW_ASSERT(func != NULL);

        thr->cppFunc = func;
        TPOOL_THREAD_FUNC(thr->thread) = (TPOOL_FUNC)CallThreadFunc;
        TPOOL_THREAD_ARG(thr->thread) = arg;

        thr->Resume();

        return (ITS_SUCCESS);
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method combines the operations of GetFirstAvailThread() and
     *      DispatchOnThread() into a single operation.
     *
     *  Input Parameters:
     *      func - the function the thread should execute
     *      arg - the argument to the function
     *
     *  Return Value:
     *      If a thread was available, and dispatched sucessfully, ITS_SUCCESS
     *          is returned.
     *      Any other return value indicates that either a thread was not
     *          available for dispatch, or that an IntelliSS7 error occurred.
     *
     *  See Also:
     *      GetFirstAvailThread(), DispatchOnThread()
     **************************************************************************/
    int
    Dispatch(ITS_ThreadCallFunc func, void *arg)
    {
        ThreadPoolEntry ent;
        int ret;

        if ((ret = GetFirstAvailThread(ent)) == ITS_SUCCESS)
        {
            return DispatchOnThread(ent, func, arg);
        }

        return (ret);
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method provides a way for the main thread of an application
     *      to wait until total deletion of a thread pool has occurred.  Note
     *      that to wait on the deletion of a particular pool, the user must
     *      serialize delete and WaitForDeletionComplete() statements.
     *
     *  Notes:
     *      The function returns when the delete synchronization object
     *      is signalled.
     *
     **************************************************************************/
    static void
    WaitForDeletionComplete()
    {
        TPOOL_WaitForDestroyComplete();
    }

protected:
    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method provides subclasses of ThreadPool with access
     *      to the list of available threads.
     *
     *  Return Value:
     *      A pointer to the list of free threads.
     *
     *  See Also:
     *      GetBusyList()
     **************************************************************************/
    MLIST_Manager*
    GetAvailList()
    {
        return pool->tpool.availThreads;
    }

    /*.implementation:public,inline,ThreadPool
     **************************************************************************
     *  Purpose:
     *      This method provides subclasses of ThreadPool with access 
     *      to the list of busy threads.
     *
     *  Return Value:
     *      A pointer to the list of busy threads.
     *
     *  See Also:
     *      GetAvailList()
     **************************************************************************/
    MLIST_Manager*
    GetBusyList()
    {
        return pool->tpool.busyThreads;
    }

private:
    /* no copying this */
    ThreadPool& operator=(ThreadPool&) { return *this; }

    TPOOL   *pool;
};

extern "C"
{
    /*.implementation:static,inline,ThreadPool
     ************************************************************************
     *  Purpose:
     *      Thread match method.  User must override.
     *
     *  Input Parameters:
     *      thrStackSize - stack size for each thread
     *
     ************************************************************************/
    static inline ITS_BOOLEAN
    LocateThread(TPOOL *pool, TPOOL_THREAD *thr, void *userData)
    {
        ThreadPool *p;
        ThreadPoolThread *t;

        ITS_ASSERT(pool != NULL);
        ITS_ASSERT(thr != NULL);

        p = (ThreadPool *)TPOOL_BACK(pool);
        t = (ThreadPoolThread *)TPOOL_THREAD_BACK(thr);

        if (p->MatchThread(t, userData))
        {
            return (ITS_TRUE);
        }

        return (ITS_FALSE);
    }
}

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_THREAD_POOL_H */
