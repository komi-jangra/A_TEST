/****************************************************************************
 *                                                                          *
 * Copyright 1997-1999 IntelliNet Technologies, Inc. All Rights Reserved.   *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:31  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:52:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.46.1  2005/01/05 07:21:28  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.2  2002/10/01 15:06:29  mmiers
 * LOG: Add API for yielding CPU
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7  2001/12/12 20:40:19  hdivoux
 * LOG: Added function to get thread ID of calling thread.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 16:39:20  mmiers
 * LOG: More mempool work.
 * LOG:
 * LOG: Revision 5.5  2001/11/09 00:27:28  mmiers
 * LOG: Allocate mempool at thread startup.
 * LOG:
 * LOG: Revision 5.4  2001/11/08 22:30:45  mmiers
 * LOG: local storage API needs to be visible to external users.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 21:20:03  mmiers
 * LOG: Get the signature right.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/16 15:47:19  lbana
 * LOG: resolve symbols from global symbol table, and fix compiler errors in thread api
 * LOG:
 * LOG: Revision 4.2  2001/05/16 16:35:07  lbana
 * LOG: allocated memory for taskInit in suspended state.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.4  2001/04/05 17:45:42  mmiers
 * LOG: Proper class hierarchy for threads.
 * LOG:
 * LOG: Revision 1.3  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 1.2  2001/02/12 21:42:33  lbana
 * LOG: ident macro is defined
 * LOG:
 * LOG: Revision 1.1  2001/02/12 21:10:17  lbana
 * LOG: vxworks platform specific implementaion for threads
 * LOG:
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <its.h>
#include <its_types.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_condvar.h>
#include <its_mem_pool.h>

#ident "$Id: its_thread.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $"

#define VX_TASK_PRIORITY 50

/*
 * startup function
 */
static THREAD_RET_TYPE
StartFunc(void *arg)
{
    MEMPOOL_Manager *m;
    ITS_THREAD *t = (ITS_THREAD *)arg;
    THREAD_RET_TYPE ret;

    /*
     * this is a little weird, I know.  Keep this in mind:
     * 1) A thread can't preempt itself.
     * 2) No other thread can see this store.
     */
    if ((m = MEMPOOL_CreateHeapPool(MEMPOOL_POWERS_DEFAULT)) == NULL)
    {
        ITS_TRACE_CRITICAL(("StartFunc: MEMPOOL_CreateHeapPool failed\n"));
        abort();
    }

    if (THREAD_SetLocalStorage(m) != ITS_SUCCESS)
    {
        MEMPOOL_DestroyPool(m);
        ITS_TRACE_CRITICAL(("StartFunc: THREAD_SetLocalStorage failed\n"));
        abort();
    }

    ret = (*t->thread.threadFunc)(t->thread.threadArg[0]);

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
 ****************************************************************************/
static int
InitThread(ITS_Object obj, va_list args)
{
    int ret;
    int sSize;
    char* stackBase;
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
    t->thread.runnable = running;
    t->thread.constructed = ITS_FALSE;

    /* One of the ten arguments. */
    t->thread.threadArgs[0] = arg;

    if (stackSize == 0) 
    {
         sSize = VXWORKS_STACK_SIZE;
    }

    if (t->thread.runnable) 
    {
        if ((t->thread.tID = taskSpawn(0, VX_TASK_PRIORITY, 0, sSize, StartFunc, 
                                       (int)t,
                                       0,0,0,0,0,0,0,0,0)) == ERROR)  
        {
            ITS_TRACE_ERROR(("THREAD_CreateThread: can't create thread\n"));
        
            return (ITS_ENOTHREAD);
        }
       
        t->thread.tVarState = THREAD_NUSE_ACTIVATE;
    }
    else
    {
       char* baseAddrs = (char *) malloc(sSize * sizeof(char)); /* allocate memory for stack */
       WIND_TCB* tTcb = (WIND_TCB*) malloc(sizeof(WIND_TCB)); /* allocate memory for TCB */
  
       t->thread.tID = (int)tTcb;       

       t->thread.tVarState = THREAD_USE_ACTIVATE;

       if( (ret = taskInit((WIND_TCB *)t->thread.tID, 0, VX_TASK_PRIORITY, 0, 
#if (_STACK_DIR == _STACK_GROWS_DOWN)
                 baseAddrs+sSize,     /* Stack base address */
#else
                 baseAddrs,           /* Stack base address */
#endif 
                 sSize, StartFunc, (int)t,0,0,0,0,0,0,0,0,0)) == ERROR)      
       {
           ITS_TRACE_ERROR(("THREAD_CreateThread: can't initialize thread\n"));
        
           return (ITS_ENOTHREAD);
       }

      /* Do not activate thread here.
       * call THREAD_ThreadResume() on this to activate
       */
    }

    return ITS_SUCCESS;  
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function frees any resources that should be released by a thread
 *      after it terminates.
 ****************************************************************************/
static void
DestroyThread(ITS_Object obj)
{
    ITS_THREAD *t = (ITS_THREAD *)obj;

    ITS_TRACE_DEBUG(("THREAD_DeleteThread:\n"));
   
    if (taskDelete((int)t->thread.tID) == ERROR)
    {
        ITS_TRACE_ERROR(("THREAD_DeleteThread: Task can not be deleted\n"));
    }     
}

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
    /* FIXME: Thread local storage key */

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
    /* FIXME: Free thread local storage key */
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
 *      running - start the thread suspended or not
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
    int ret;

    ITS_TRACE_DEBUG(("THREAD_ThreadSuspend:\n"));

    t->thread.runnable = ITS_FALSE;      

    t->thread.tVarState = THREAD_NUSE_ACTIVATE;

    if( (ret = taskSuspend((int) t->thread.tID)) == ERROR)
    {
        ITS_TRACE_ERROR(("THREAD_ThreadSuspend: Task can not be suspended\n"));

        return (ITS_ENOTHREAD);
    }
   
    ITS_TRACE_DEBUG(("THREAD_Thread_Suspend: thread var state is %d\n", 
                     t->thread.tVarState));

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
    int ret;

    ITS_TRACE_DEBUG(("THREAD_ThreadResume:\n"));

    if (t->thread.tVarState == THREAD_USE_ACTIVATE)
    {
        t->thread.runnable = ITS_TRUE;

        if ((ret = taskActivate((int)t->thread.tID)) == ERROR)
        {
            ITS_TRACE_ERROR(("THREAD_Resume: can't activate a thread\n"));

            return ITS_ENOTHREAD;
        }
    }
    else 
    {
        /* call taskResume on thread only if THREAD_NUSE_ACTIVATE
         * var is set
         */

        if ((ret = taskResume((int)t->thread.tID)) == ERROR)
        {
            ITS_TRACE_ERROR(("THREAD_ThreadResume: can't resume thread\n"));
      
            return (ITS_ENOTHREAD);
        }
    }

    t->thread.runnable = ITS_TRUE;

    return ITS_SUCCESS;
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

    exit((*(int*)(status)));
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
    ITS_TRACE_DEBUG(("THREAD_KillThread:\n
                     native func is not available.\n"));   
   
    return ITS_SUCCESS;
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
    ITS_TRACE_DEBUG(("THREAD_WaitForThread:\n 
                      native func is not available.\n"));
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
    ITS_TRACE_DEBUG(("THREAD_Yield:\n 
                      native func is not available.\n"));
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
    /* FIXME: */
    return (NULL);
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
    /* FIXME: */
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
    /* FIXME: */
    return (ITS_UINT)0;
}

