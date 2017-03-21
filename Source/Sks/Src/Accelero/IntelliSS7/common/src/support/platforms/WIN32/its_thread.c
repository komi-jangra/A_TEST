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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:30  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.46.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.3  2002/10/03 16:39:16  mmiers
 * LOG: Correct API call
 * LOG:
 * LOG: Revision 7.2  2002/10/01 15:06:29  mmiers
 * LOG: Add API for yielding CPU
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7  2001/12/12 20:40:18  hdivoux
 * LOG: Added function to get thread ID of calling thread.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 16:39:20  mmiers
 * LOG: More mempool work.
 * LOG:
 * LOG: Revision 5.5  2001/11/09 00:17:20  mmiers
 * LOG: Get the thread initialization right.
 * LOG:
 * LOG: Revision 5.4  2001/11/08 22:29:14  mmiers
 * LOG: externs need to see the local storage API
 * LOG:
 * LOG: Revision 5.3  2001/11/08 21:20:03  mmiers
 * LOG: Get the signature right.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:13  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/04/05 17:45:42  mmiers
 * LOG: Proper class hierarchy for threads.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:53  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:22  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:16  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.17  1998/10/07 17:24:08  whu
 * LOG: Fix a couple of bugs in windows threading, add debug to iniparse.
 * LOG:
 * LOG: Revision 1.16  1998/09/28 16:35:23  mmiers
 * LOG: Add error information to complaint.
 * LOG:
 * LOG: Revision 1.15  1998/09/23 22:54:21  mmiers
 * LOG: Add tracing to the windows implementation.
 * LOG:
 * LOG: Revision 1.14  1998/06/14 17:45:04  ahanda
 * LOG: Fixed _beginthreadex return error check
 * LOG:
 * LOG: Revision 1.13  1998/06/12 16:59:48  ahanda
 * LOG: _beginthreadex() apparently does NOT reset the error number
 * LOG: returned by GetLastError().
 * LOG:
 * LOG: Revision 1.12  1998/06/09 21:00:31  whu
 * LOG: Make thread pool threads suspended on creation.  This removes a race
 * LOG: condition where the worker thread has not reached the suspended state
 * LOG: before the main thread dispatches work to it; in this case, the worker
 * LOG: suspends *before* the work is started, resulting in a wasted dispatch.
 * LOG:
 * LOG: Also fixed a bug where we were adding and removing threads from the
 * LOG: avail list twice.  Had to add a new parameter to the THREAD interface;
 * LOG: document this.
 * LOG:
 * LOG: Revision 1.11  1998/06/01 16:35:37  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.10  1998/05/29 00:32:57  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.9  1998/05/22 23:00:25  whu
 * LOG: Fix bug in thread destructor with unitialized OS thread variable.
 * LOG:
 * LOG: Revision 1.8  1998/04/15 00:07:16  mmiers
 * LOG: Tests and bug fixes for infrastructure.
 * LOG:
 * LOG: Revision 1.7  1998/04/13 20:55:37  mmiers
 * LOG: Update a comment on threads.
 * LOG:
 * LOG: Revision 1.6  1998/04/13 20:41:10  mmiers
 * LOG: Finish tracking down the bugs for Windows sockets.  NOTE:
 * LOG: You MUST call WSAStartup for ALL sockets created --
 * LOG: INCLUDING the socket that is the result of accept().
 * LOG:
 * LOG: Revision 1.5  1998/04/10 15:40:48  mmiers
 * LOG: More debug on the infrastructure.
 * LOG:
 * LOG: Revision 1.4  1998/04/09 23:43:43  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.3  1998/04/06 15:26:53  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.2  1998/04/03 22:17:57  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.1  1998/03/13 04:11:48  mmiers
 * LOG: Update files with latest code.  emlist represents portable message queues.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <its.h>
#include <its_types.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_mem_pool.h>

#ident "$Id: its_thread.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

#define THREAD_ERROR    (0xFFFFFFFFUL)

static DWORD    ctxt = THREAD_ERROR;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a key for thread local storage.
 *
 *  Input Parameters:
 *      objClass - the class to init.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInit(ITS_Class objClass)
{
    ctxt = TlsAlloc();
    if (ctxt == THREAD_ERROR)
    {
        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a key for thread local storage.
 *
 *  Input Parameters:
 *      objClass - the class to init.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassTerm(ITS_Class objClass)
{
    if (ctxt != THREAD_ERROR)
    {
        TlsFree(ctxt);

        ctxt = THREAD_ERROR;
    }
}

/*
 * Initial function for a thread
 */
static THREAD_RET_TYPE
StartThread(void *arg)
{
    ITS_THREAD *t = (ITS_THREAD *)arg;
    MEMPOOL_Manager *m;
    /* stupid windows type modifiers */
    unsigned ret;

    /*
     * this is a little weird, I know.  Keep this in mind:
     * 1) A thread can't preempt itself.
     * 2) No other thread can see this store.
     */
    if ((m = MEMPOOL_CreateHeapPool(MEMPOOL_POWERS_DEFAULT)) == NULL)
    {
        ITS_TRACE_CRITICAL(("StartThread: MEMPOOL_CreateHeapPool failed\n"));
        abort();
    }

    if (THREAD_SetLocalStorage(m) != ITS_SUCCESS)
    {
        MEMPOOL_DestroyPool(m);
        ITS_TRACE_CRITICAL(("StartThread: THREAD_SetLocalStorage failed\n"));
        abort();
    }

    ret = (*t->thread.threadFunc)(t->thread.threadArg);

    if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)
    {
        MEMPOOL_DestroyPool(m);

        THREAD_SetLocalStorage(NULL);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function creates a thread.
 *
 *  Return Value:
 *      If the thread is created successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an error.
 *
 ****************************************************************************/
static int
InitThread(ITS_Object obj, va_list args)
{
    DWORD threadID;
    ITS_THREAD *t = (ITS_THREAD *)obj;
    int stackSize;
    ITS_THREAD_FUNC entryPoint;
    void *arg;
    ITS_BOOLEAN running;

    stackSize = va_arg(args, int);
    entryPoint = va_arg(args, ITS_THREAD_FUNC);
    arg = va_arg(args, void *);
    running = va_arg(args, ITS_BOOLEAN);

    ITS_TRACE_DEBUG(("THREAD_CreateThread:\n"));

    t->thread.threadFunc = entryPoint;
    t->thread.threadArg = arg;
    t->thread.runnable = running;
    t->thread.constructed = ITS_FALSE;
    t->thread.stackSize = stackSize;

    t->thread.thread = INVALID_HANDLE_VALUE;

    if (running)
    {
        t->thread.thread = (HANDLE)_beginthreadex(NULL, stackSize,
                                                  StartThread,
                                                  t, 0,
                                                  &threadID);
    }
    else
    {
        t->thread.thread = (HANDLE)_beginthreadex(NULL, stackSize,
                                                  StartThread,
                                                  t, CREATE_SUSPENDED,
                                                  &threadID);
    }

    if (!(t->thread.thread)) //_beginthreadex returns 0L for failure
    {
        return (ITS_ENOTHREAD);
    }

    t->thread.constructed = ITS_TRUE;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Release the resources associated with a thread.  There's a unique
 *      occurrence, here.  Normally, you should call the destructor BEFORE
 *      the thread actually terminates -- which means the thread HANDLE is
 *      closed.  However, since the thread is still executing, the HANDLE
 *      remains OPEN until _endthreadex() is called (in other words, when
 *      the thread exits).
 *
 *  Input Parameters:
 *      t - the thread to clean up
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      A thread may call this for itself.
 *
 *  See Also:
 *      THREAD_CreateThread()
 ****************************************************************************/
static void
DestroyThread(ITS_Object obj)
{
    ITS_THREAD *t = (ITS_THREAD *)obj;

    ITS_TRACE_DEBUG(("THREAD_DeleteThread:\n"));

    if (t->thread.constructed)
    {
        CloseHandle(t->thread.thread);
    }
}

/*
 * thread class record
 */
ITSDLLAPI ITS_ClassRec itsTHREAD_ClassRec =
{
    {
        &itsCORE_ClassRec,
        sizeof(ITS_THREAD),
        ITS_FALSE,
        0,
        "THREAD Class",
        ClassInit,
        ClassTerm,
        ITS_CLASS_PART_NO_INIT,
        ITS_CLASS_PART_NO_DEST,
        InitThread,
        DestroyThread,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    }
};
ITSDLLAPI ITS_Class itsTHREAD_Class = &itsTHREAD_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates a thread.
 *
 *  Input Parameters:
 *      stackSize - the initial stack size for the thread.
 *      entryPoint - a pointer to the function that the thread is to execute
 *      arg - the argument to the function that the thread is to execute
 *      running - start suspended or not
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      t - a pointer to the thread object to be initialized
 *
 *  Return Value:
 *      If the thread is created successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an error.
 *
 *  Notes:
 *      Passing a stackSize of 0 to this function is a hint to the operating
 *      system to use the default thread stack size.  Usually, passing 0
 *      is recommended, as the thread creation can be significantly faster
 *      when the default is used.
 *
 *  See Also:
 *      THREAD_DeleteThread()
 ****************************************************************************/
ITSDLLAPI int
THREAD_CreateThread(ITS_THREAD *t, int stackSize,
                    ITS_THREAD_FUNC entryPoint, void *arg,
                    ITS_BOOLEAN running)
{
    ITS_Object ret;

    ret = ITS_ConstructObjectIn(t, itsTHREAD_Class, stackSize,
                                entryPoint, arg, running);

    if (ret != (ITS_Object)t)
    {
        return (ITS_EINVALIDARGS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function frees any resources that should be released by a thread
 *      after it terminates.
 *
 *  Input Parameters:
 *      t - the thread to clean up after.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      This routine is a no-op for Solaris.
 *      This routine must NOT be called before the thread exits.
 *
 *  See Also:
 *      THREAD_CreateThread()
 ****************************************************************************/
ITSDLLAPI void
THREAD_DeleteThread(ITS_THREAD *t)
{
    ITS_DestructObject((ITS_Object)t);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function suspends a thread.  In practice, this means the thread
 *      will not be scheduled until it resumes.  The result of suspending a
 *      suspended thread is not defined.
 *
 *  Input Parameters:
 *      t - the thread to suspend
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread was suspended, ITS_SUCCESS is returned.
 *      Any other return value indicates an error.
 *
 *  Notes:
 *      A thread may call this for itself.
 *
 *  See Also:
 *      THREAD_ThreadResume()
 ****************************************************************************/
ITSDLLAPI int
THREAD_ThreadSuspend(ITS_THREAD *t)
{
    ITS_TRACE_DEBUG(("THREAD_ThreadSuspend:\n"));

    if (SuspendThread(t->thread.thread) == THREAD_ERROR)
    {
        ITS_TRACE_ERROR(("THREAD_ThreadSuspend: error suspending thread: "
                         "error %08x\n", GetLastError()));

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function resumes a suspended thread.  In practice, this means
 *      the thread will be returned to the scheduler.  The result of
 *      resuming a running thread is undefined.
 *
 *  Input Parameters:
 *      t - the thread to resume
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread was successfully resumed, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntellISS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      THREAD_ThreadSuspend()
 ****************************************************************************/
ITSDLLAPI int
THREAD_ThreadResume(ITS_THREAD *t)
{
    ITS_TRACE_DEBUG(("THREAD_ThreadResume:\n"));

    if (ResumeThread(t->thread.thread) == THREAD_ERROR)
    {
        ITS_TRACE_ERROR(("THREAD_ThreadResume: error resuming thread: "
                         "error %08x\n", GetLastError()));

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function should be called for a thread that wants to safely
 *      exit (returning its resources to the process).
 *
 *  Input Parameters:
 *      status - a pointer value to return to the process.  If an entity
 *          is waiting on this thread, this is the value the entity
 *          will receive.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
THREAD_ThreadExit(void *status)
{
    MEMPOOL_Manager *m;

    ITS_TRACE_DEBUG(("THREAD_ThreadExit:\n"));

    if ((m = (MEMPOOL_Manager *)THREAD_GetLocalStorage()) != NULL)
    {
        MEMPOOL_DestroyPool(m);

        THREAD_SetLocalStorage(NULL);
    }

    _endthreadex((unsigned)status);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used to kill a thread.  This function is included
 *      for completeness only and should NOT be used.  You have been warned.
 *
 *  Input Parameters:
 *      t - the thread to kill
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread was killed, ITS_SUCCESS is returned.
 *      Any other return value indicate an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
THREAD_KillThread(ITS_THREAD *t)
{
    ITS_TRACE_DEBUG(("THREAD_KillThread:\n"));

    if (!TerminateThread(t->thread.thread, 0))
    {
        ITS_TRACE_ERROR(("THREAD_ThreadSuspend: error terminating thread\n"));

        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used by the caller to wait for the return
 *      code of a spawned thread.
 *
 *  Input Parameters:
 *      t - the thread to wait for
 *      status - the address of a pointer where the return code should be
 *          placed
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread exists, and exited, ITS_SUCCESS is returned
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
THREAD_WaitForThread(ITS_THREAD *t, void **status)
{
    int ret;

    ITS_TRACE_DEBUG(("THREAD_WaitForThread:\n"));

    ret = WaitForSingleObject(t->thread.thread, INFINITE);
    
    if (ret != WAIT_OBJECT_0)
    {
        return (ITS_EBADTHREAD);
    }

    if (!GetExitCodeThread(t->thread.thread, (LPDWORD)status))
    {
        return (ITS_EBADTHREAD);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function can be used by the caller to voluntarily yield the
 *      CPU.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the thread exists, and exited, ITS_SUCCESS is returned
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
THREAD_Yield(void)
{
    ITS_TRACE_DEBUG(("THREAD_Yield:\n"));

    SwitchToThread();
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Fetch the local storage for this thread.
 *
 *  Input Parameters:
 *      thr - thread to fetch from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the thread local storage, or NULL if it hasn't been
 *      set yet.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void *
THREAD_GetLocalStorage()
{
    return TlsGetValue(ctxt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the local storage for this thread.
 *
 *  Input Parameters:
 *      thr - thread to fetch from
 *      set - the value to set the local storage to.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
THREAD_SetLocalStorage(void *set)
{
    if (TlsSetValue(ctxt, set))
    {
        return (ITS_SUCCESS);
    }

    return (ITS_ENOMEM);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Retrieve the thread identifier of the calling thread.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_UINT - thread identifier of the calling thread.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_UINT
THREAD_GetCurrentThreadID()
{
    return (ITS_UINT)GetCurrentThreadId();
}

