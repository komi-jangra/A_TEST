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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:21  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/06 20:50:55  mmiers
 * LOG: Add synchronization around tpool deletion
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/01/10 20:16:02  mmiers
 * LOG: Remove some fixme's that have been.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.3  2001/05/02 20:21:45  mmiers
 * LOG: Proper shutdown
 * LOG:
 * LOG: Revision 4.2  2001/05/01 19:19:23  mmiers
 * LOG: Change the create function to allow zero threads.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.13  2001/04/10 23:15:40  mmiers
 * LOG: Debugging, clarification.
 * LOG:
 * LOG: Revision 3.12  2001/04/05 19:27:29  mmiers
 * LOG: Workaround part 2.
 * LOG:
 * LOG: Revision 3.11  2001/04/05 19:20:41  mmiers
 * LOG: Workaround.
 * LOG:
 * LOG: Revision 3.10  2001/04/05 19:06:37  mmiers
 * LOG: Initialize the class record.
 * LOG:
 * LOG: Revision 3.9  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.8  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/06 00:26:00  mmiers
 * LOG: Continue adding assertions.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.2  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:44  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/04/25 23:03:31  mmiers
 * LOG:
 * LOG:
 * LOG: Update C service test.
 * LOG:
 * LOG: Revision 2.3  2000/04/25 14:52:54  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.  Also remove race from thread
 * LOG: pool where allocated but not started thread could miss pool
 * LOG: destruction [Ricardo].
 * LOG:
 * LOG: Revision 2.2  2000/03/23 23:08:13  randresol
 * LOG: In function TPOOL_ThreadFunc, the thread should not be *suspended*
 * LOG: if we are in the process of destroying the thread pool.
 * LOG:
 * LOG: Fix the function TPOOL_DestroyPool to get the right pointer to the thread.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:19:22  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is amazingly unforgiving.  It did find at least 4 bugs,
 * LOG: though.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:17  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/08/22 02:07:38  mmiers
 * LOG:
 * LOG:
 * LOG: Create a synchronization object for thread pools.
 * LOG:
 * LOG: Revision 1.7  1999/02/09 21:46:16  mmiers
 * LOG:
 * LOG:
 * LOG: Normalize the thread function return type.
 * LOG: Create standard thread function exit macro.
 * LOG: Convert support library to use these.
 * LOG: Delete dead file (its_worker).
 * LOG:
 * LOG: Revision 1.6  1998/11/19 00:36:30  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.5  1998/10/29 00:18:15  mmiers
 * LOG: Fix comment (C++ style in C file).
 * LOG:
 * LOG: Revision 1.4  1998/10/28 17:16:35  mmiers
 * LOG: Add/complete C-based thread pools and workers.
 * LOG:
 * LOG: Revision 1.3  1998/10/28 03:08:23  mmiers
 * LOG: Finish thread pool implementation.
 * LOG:
 * LOG: Revision 1.2  1998/10/28 02:02:24  mmiers
 * LOG: Do a test build, make the C thread pool compile.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 17:53:13  mmiers
 * LOG: Start adding C based thread pool.
 * LOG:
 * LOG: Revision 1.9  1998/08/03 20:34:19  mmiers
 * LOG: Add cleaner functionality to ITS_Terminate() for transient transports.
 * LOG:
 * LOG: Revision 1.8  1998/07/03 17:05:56  ahanda
 * LOG: Added NDEBUG conditional compilation for catch (...).
 * LOG:
 * LOG: Revision 1.7  1998/06/24 17:45:16  mmiers
 * LOG: Convert over to using the generated exceptions.
 * LOG:
 * LOG: Revision 1.6  1998/06/22 16:24:22  mmiers
 * LOG: More work with resource files.
 * LOG:
 * LOG: Revision 1.5  1998/06/22 16:11:42  mmiers
 * LOG: Add transport PC/SSN settings.
 * LOG:
 * LOG: Revision 1.4  1998/06/09 21:00:31  whu
 * LOG: Make thread pool threads suspended on creation.  This removes a race
 * LOG: condition where the worker thread has not reached the suspended state
 * LOG: before the main thread dispatches work to it; in this case, the worker
 * LOG: suspends *before* the work is started, resulting in a wasted dispatch.
 * LOG:
 * LOG: Also fixed a bug where we were adding and removing threads from the
 * LOG: avail list twice.  Had to add a new parameter to the THREAD interface;
 * LOG: document this.
 * LOG:
 * LOG: Revision 1.3  1998/06/05 17:19:37  whu
 * LOG: If the user supplied a NULL function for dispatch, don't execute it.
 * LOG:
 * LOG: Revision 1.2  1998/05/29 00:32:57  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.1  1998/05/28 17:28:44  mmiers
 * LOG: More documenation.  Split the thread implementation into basic threads
 * LOG: and thread pools.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_thread.h>
#include <its_thread_pool.h>
#include <its_assertion.h>
#include <its_worker.h>

#ident "$Id: its_thread_pool.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a thread pool thread
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 ****************************************************************************/
static int
CreatePoolThread(ITS_Object obj, va_list args)
{
    int stackSize;

    stackSize = va_arg(args, int);

    ((ITS_THREAD *)(obj))->thread.stackSize = stackSize;
    TPOOL_THREAD_FUNC(obj) = NULL;
    TPOOL_THREAD_ARG(obj) = NULL;
    TPOOL_THREAD_EXIT(obj) = ITS_FALSE;
    TPOOL_THREAD_BACK(obj) = NULL;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a thread pool thread
 *
 *  Input Parameters:
 *      None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 ****************************************************************************/
static void
DestroyPoolThread(ITS_Object obj)
{
    /* nothing to do */
}

/*
 * class record
 */
ITSDLLAPI ITS_ClassRec itsTPOOLTHREAD_ClassRec =
{
    {
        &itsCORE_ClassRec,
        sizeof(TPOOL_THREAD),
        ITS_FALSE,
        0,
        "TPOOLTHREAD class",
        ITS_CLASS_NO_INIT,
        ITS_CLASS_NO_DEST,
        ITS_CLASS_PART_NO_INIT,
        ITS_CLASS_PART_NO_DEST,
        CreatePoolThread,
        DestroyPoolThread,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    }
};
ITSDLLAPI ITS_Class itsTPOOLTHREAD_Class = &itsTPOOLTHREAD_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create a thread pool thread
 *
 ****************************************************************************/
TPOOL_THREAD *
TPOOLTHREAD_Create(int stackSize)
{
    return (TPOOL_THREAD *)ITS_ConstructObject(itsTPOOLTHREAD_Class,
                                               stackSize);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create a thread pool thread
 *
 ****************************************************************************/
void
TPOOLTHREAD_Destroy(TPOOL_THREAD *thr)
{
    ITS_DestructObject((ITS_Object)thr);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the thread pool class
 *
 *  Input Parameters:
 *      subClass - the thread pool class to initialize.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 ****************************************************************************/
static int
ClassInit(ITS_Class subClass)
{
    if (SEMA_CreateSemaphore(&TPOOL_CLASS_SYNC_OBJ(subClass), 0) !=
        ITS_SUCCESS)
    {
        return (ITS_EBADSEMAPHORE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the thread pool class
 *
 *  Input Parameters:
 *      p - the pool structure to initialize.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 ****************************************************************************/
static void
ClassDestroy(ITS_Class subClass)
{
    SEMA_DeleteSemaphore(&TPOOL_CLASS_SYNC_OBJ(subClass));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize a C thread pool object.
 *
 *  Input Parameters:
 *      p - the pool structure to initialize.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - indicates the pool was successfully initialized.
 *      Any other return code indicates an IntellISS7 processing error.
 *
 *  Notes:
 *      This function sets up the overhead objects for the pool, but does
 *      not actually create the threads.
 *
 *  See Also:
 *      DestroyPool()
 ****************************************************************************/
static int
ConstructPool(ITS_Object h, va_list args)
{
    TPOOL* p = (TPOOL *)h;

    TPOOL_USER_DATA(p) = va_arg(args, void *);

    if ((TPOOL_AVAIL_THREADS(p) = MLIST_Create()) == NULL)
    {
        return (ITS_ENOLIST);
    }

    if ((TPOOL_BUSY_THREADS(p) = MLIST_Create()) == NULL)
    {
        MLIST_Delete(TPOOL_AVAIL_THREADS(p));

        return (ITS_ENOLIST);
    }

    if ((TPOOL_HEAP_OBJ(p) =
            (TPOOL_HEAP_OBJ *)calloc(1, sizeof(TPOOL_HEAP_OBJ))) == NULL)
    {
        MLIST_Delete(TPOOL_BUSY_THREADS(p));
        MLIST_Delete(TPOOL_AVAIL_THREADS(p));

        return (ITS_ENOMEM);
    }

    TPOOL_HEAP_OBJ(p)->avail = TPOOL_AVAIL_THREADS(p);
    TPOOL_HEAP_OBJ(p)->busy = TPOOL_BUSY_THREADS(p);
    TPOOL_HEAP_OBJ(p)->exit = ITS_FALSE;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Begin the destroy procedure for a thread pool.
 *
 *  Input Parameters:
 *      p - the pool to destroy
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
 *      The pool is not necessarily completely destroyed when this function
 *      returns.  In particular, the pool is not completely destroyed until
 *      the last thread in the pool exits.
 *
 *  See Also:
 ****************************************************************************/
static void
DestroyPool(ITS_Object h)
{
    TPOOL* p = (TPOOL *)h;
    LIST_Entry *ent;

    TPOOL_HEAP_OBJ(p)->exit = ITS_TRUE;

    MLIST_Lock(TPOOL_AVAIL_THREADS(p));

    for (ent = LIST_HEAD(TPOOL_AVAIL_THREADS(p)); ent != NULL; ent = ent->next)
    {
        TPOOL_THREAD *pt = *(TPOOL_THREAD **)ent->data;

        if (ITS_IsInstanceOf(itsWORKER_Class, (ITS_Object)pt))
        {
            WORKER_SetExit((WORKER_Control *)pt, ITS_TRUE);
        }
        else
        {
            TPOOL_THREAD_EXIT(pt) = ITS_TRUE;
        }

        THREAD_ThreadResume((ITS_THREAD *)pt);
    }

    MLIST_Unlock(TPOOL_AVAIL_THREADS(p));

    MLIST_Lock(TPOOL_BUSY_THREADS(p));

    for (ent = LIST_HEAD(TPOOL_BUSY_THREADS(p)); ent != NULL; ent = ent->next)
    {
        TPOOL_THREAD *pt = *(TPOOL_THREAD **)ent->data;

        if (ITS_IsInstanceOf(itsWORKER_Class, (ITS_Object)pt))
        {
            WORKER_SetExit((WORKER_Control *)pt, ITS_TRUE);
        }
        else
        {
            TPOOL_THREAD_EXIT(pt) = ITS_TRUE;
        }
    }

    MLIST_Unlock(TPOOL_BUSY_THREADS(p));

    SEMA_PostSemaphore(&TPOOL_CLASS_SYNC_OBJ(itsTPOOL_Class));
}

/*
 * the class record
 */
ITSDLLAPI TPOOL_ClassRec itsTPOOL_ClassRec =
{
    /* core */
    {
        &itsCORE_ClassRec,         /* core superclass */
        sizeof(TPOOL),             /* instance size */
        ITS_FALSE,                 /* not initialized */
        0,                         /* initial ref count */
        TPOOL_CLASS_NAME,          /* class name */
        ClassInit,                 /* class initializer */
        ClassDestroy,              /* class destructor */
        ITS_CLASS_PART_NO_INIT,    /* class part constructor */
        ITS_CLASS_PART_NO_DEST,    /* class part destructor */
        ConstructPool,             /* instance constructor */
        DestroyPool,               /* instance destructor */
        ITS_INST_CLONE_INHERIT,    /* inherit clone */
        ITS_INST_PRINT_INHERIT,    /* inherit print */
        ITS_INST_SERIAL_INHERIT,   /* inherit serial */
        ITS_INST_EQUALS_INHERIT,   /* inherit equals */
        ITS_INST_HASH_INHERIT,     /* inherit hash */
        NULL                       /* no meaningful extension */
    },
    /* tpool */
    /* nothing to say */
};

ITSDLLAPI TPOOL_Class itsTPOOL_Class = &itsTPOOL_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize a C thread pool object.
 *
 *  Input Parameters:
 *      p - the pool structure to initialize.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - indicates the pool was successfully initialized.
 *      Any other return code indicates an IntellISS7 processing error.
 *
 *  Notes:
 *      This function sets up the overhead objects for the pool, but does
 *      not actually create the threads.
 *
 *  See Also:
 *      DestroyPool()
 ****************************************************************************/
ITSDLLAPI TPOOL *
TPOOL_InitPool(void *userData)
{
    return (TPOOL *)ITS_ConstructObject((ITS_Class)itsTPOOL_Class,
                                        userData,  NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Begin the destroy procedure for a thread pool.
 *
 *  Input Parameters:
 *      p - the pool to destroy
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
 *      The pool is not necessarily completely destroyed when this function
 *      returns.  In particular, the pool is not completely destroyed until
 *      the last thread in the pool exits.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
TPOOL_DestroyPool(TPOOL *pool)
{
    ITS_DestructObject((ITS_Object)pool);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create the threads that will live in this pool.
 *
 *  Input Parameters:
 *      pool - the pool to create threads into
 *      numThreads - the number of threads that will be created in this
 *          pool
 *      stackSize - the stackSize for each thread.  Pass 0 to accept the
 *          OS default stackSize.
 *      thrCreator - the thread creation function.  The user passes a
 *          pointer to the function that creates one thread based on
 *          user context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - pool created.  Any other return code indicates an
 *      IntellISS7 processing error.
 *
 *  Notes:
 *      This function calls the supplied creation function pointer to create
 *      each thread that will live in this pool.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_CreatePool(TPOOL* pool, int numThreads, int stackSize,
                 TPOOL_CreateThread thrCreator)
{
    int i, ret;
    ITS_Class saveClass;

    ITS_C_REQUIRE(pool != NULL);
    ITS_C_REQUIRE(thrCreator != NULL);

    if (numThreads < 0)
    {
        return (ITS_EINVALIDARGS);
    }

    TPOOL_HEAP_OBJ(pool)->thrCount = numThreads;

    for (i = 0; i < numThreads; i++)
    {
        TPOOL_THREAD* newThread = (*thrCreator)(pool, stackSize);
        TPOOL_THREAD_ARG* arg;

        if (newThread == NULL)
        {
            return (ITS_ENOMEM);
        }

        if ((arg = (TPOOL_THREAD_ARG *)calloc(1, sizeof(TPOOL_THREAD_ARG)))
            == NULL)
        {
            return (ITS_ENOMEM);
        }

        ret = MLIST_AddTail(TPOOL_AVAIL_THREADS(pool),
                            &newThread, sizeof(TPOOL_THREAD *));
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        arg->entry = newThread;
        arg->pool = pool;
        arg->refCounter = TPOOL_HEAP_OBJ(pool);

        saveClass = ITS_OBJ_CLASS(newThread);

        if (THREAD_CreateThread((ITS_THREAD *)newThread, stackSize,
                                TPOOL_ThreadFunc, (void *)arg,
                                ITS_FALSE) != ITS_SUCCESS)
        {
            return (ITS_EBADTHREAD);
        }

        if (saveClass)
        {
            ITS_OBJ_CLASS(newThread) = saveClass;
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a thread to an existing pool
 *
 *  Input Parameters:
 *      pool - the pool to create threads into
 *      stackSize - the stackSize for each thread.  Pass 0 to accept the
 *          OS default stackSize.
 *      thrCreator - the thread creation function.  The user passes a
 *          pointer to the function that creates one thread based on
 *          user context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - thread added.  Any other return code indicates an
 *      IntellISS7 processing error.
 *
 *  Notes:
 *      This function calls the supplied creation function pointer to create
 *      the new thread.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_AddThreadToPool(TPOOL* pool, int stackSize,
                      TPOOL_CreateThread thrCreator)
{
    int ret;
    ITS_Class saveClass;
    TPOOL_THREAD* newThread;
    TPOOL_THREAD_ARG* arg;

    ITS_C_REQUIRE(pool != NULL);
    ITS_C_REQUIRE(thrCreator != NULL);

    if (ITS_OBJ_BEING_DESTROYED(pool))
    {
        return (ITS_EINVALIDARGS);
    }

    newThread = (*thrCreator)(pool, stackSize);

    if (newThread == NULL)
    {
        return (ITS_ENOMEM);
    }

    if ((arg = (TPOOL_THREAD_ARG *)calloc(1, sizeof(TPOOL_THREAD_ARG)))
        == NULL)
    {
        return (ITS_ENOMEM);
    }

    ret = MLIST_AddTail(TPOOL_AVAIL_THREADS(pool),
                        &newThread, sizeof(TPOOL_THREAD *));
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    arg->entry = newThread;
    arg->pool = pool;
    arg->refCounter = TPOOL_HEAP_OBJ(pool);

    saveClass = ITS_OBJ_CLASS(newThread);

    if (THREAD_CreateThread((ITS_THREAD *)newThread, stackSize,
                            TPOOL_ThreadFunc, (void *)arg,
                            ITS_FALSE) != ITS_SUCCESS)
    {
        return (ITS_EBADTHREAD);
    }

    if (saveClass)
    {
        ITS_OBJ_CLASS(newThread) = saveClass;
    }

    TPOOL_HEAP_OBJ(pool)->thrCount++;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Remove a thread from an existing pool
 *
 *  Input Parameters:
 *      pool - the pool to remove the thread from
 *      thr - the thread to remove
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - thread removed.  Any other return code indicates an
 *      IntellISS7 processing error.
 *
 *  Notes:
 *      The caller is responsible for ensuring that the thread actually
 *      exits.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_RemThreadFromPool(TPOOL* pool, TPOOL_THREAD *thr)
{
    int ret;
    LIST_Entry *entry;

    ITS_C_REQUIRE(pool != NULL);
    ITS_C_REQUIRE(thr != NULL);

    /* try avail first */
    if ((ret = MLIST_Lock(TPOOL_AVAIL_THREADS(pool))) != ITS_SUCCESS)
    {
        return (ret);
    }

    for (entry = LIST_HEAD(TPOOL_AVAIL_THREADS(pool));
         entry != NULL;
         entry = entry->next)
    {
        if (thr == *(TPOOL_THREAD **)entry->data)
        {
            ret = MLIST_RemoveNoLock(TPOOL_AVAIL_THREADS(pool), entry);
            ITS_Free(entry->data);
            ITS_Free(entry);

            MLIST_Unlock(TPOOL_AVAIL_THREADS(pool));

            return (ITS_SUCCESS);
        }
    }

    MLIST_Unlock(TPOOL_AVAIL_THREADS(pool));

    /* nope, not there, try busy. */
    if ((ret = MLIST_Lock(TPOOL_BUSY_THREADS(pool))) != ITS_SUCCESS)
    {
        return (ret);
    }

    for (entry = LIST_HEAD(TPOOL_BUSY_THREADS(pool));
         entry != NULL;
         entry = entry->next)
    {
        if (thr == *(TPOOL_THREAD **)entry->data)
        {
            MLIST_RemoveNoLock(TPOOL_BUSY_THREADS(pool), entry);
            ITS_Free(entry->data);
            ITS_Free(entry);

            MLIST_Unlock(TPOOL_BUSY_THREADS(pool));

            return (ITS_SUCCESS);
        }
    }

    MLIST_Unlock(TPOOL_BUSY_THREADS(pool));

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add a thread to an existing pool
 *
 *  Input Parameters:
 *      pool - the pool to create threads into
 *      stackSize - the stackSize for each thread.  Pass 0 to accept the
 *          OS default stackSize.
 *      thrCreator - the thread creation function.  The user passes a
 *          pointer to the function that creates one thread based on
 *          user context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - thread added.  Any other return code indicates an
 *      IntellISS7 processing error.
 *
 *  Notes:
 *      This function calls the supplied creation function pointer to create
 *      the new thread.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_FindThreadInPool(TPOOL *pool, TPOOL_FindThread thrFinder,
                       TPOOL_THREAD **thr, void *userData)
{
    int ret;
    LIST_Entry *entry;

    *thr = NULL;

    /* try avail first */
    if ((ret = MLIST_Lock(TPOOL_AVAIL_THREADS(pool))) != ITS_SUCCESS)
    {
        return (ret);
    }

    for (entry = LIST_HEAD(TPOOL_AVAIL_THREADS(pool));
         entry != NULL;
         entry = entry->next)
    {
        if ((*thrFinder)(pool, *(TPOOL_THREAD **)entry->data,
                         userData) == ITS_SUCCESS)
        {
            *thr = *(TPOOL_THREAD **)entry->data;

            MLIST_Unlock(TPOOL_AVAIL_THREADS(pool));

            return (ITS_SUCCESS);
        }
    }

    MLIST_Unlock(TPOOL_AVAIL_THREADS(pool));

    /* nope, not there, try busy. */
    if ((ret = MLIST_Lock(TPOOL_BUSY_THREADS(pool))) != ITS_SUCCESS)
    {
        return (ret);
    }

    for (entry = LIST_HEAD(TPOOL_BUSY_THREADS(pool));
         entry != NULL;
         entry = entry->next)
    {
        if ((*thrFinder)(pool, *(TPOOL_THREAD **)entry->data,
                         userData) == ITS_SUCCESS)
        {
            *thr = *(TPOOL_THREAD **)entry->data;

            MLIST_Unlock(TPOOL_BUSY_THREADS(pool));

            return (ITS_SUCCESS);
        }
    }

    MLIST_Unlock(TPOOL_BUSY_THREADS(pool));

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Dequeue the first available thread from the thread pool.
 *
 *  Input Parameters:
 *      tpool - the thread pool to get a thread from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      first - the address of a pointer that will be set to
 *          the first available thread.
 *
 *  Return Value:
 *      ITS_SUCCESS - the thread was successfully dequeued.  Any other
 *      return code indicates that a thread is not available or that
 *      a processing error has occurred.
 *
 *  Notes:
 *      This function does NOT add the thread to the busy list.  If
 *      the thread fails to dispatch, you must add it back to the free
 *      pool via TPOOL_ReturnToAvailThreads().
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_GetFirstAvailThread(TPOOL* pool, TPOOL_THREAD** first)
{
    int ret, len;
    void *data;

    ITS_C_REQUIRE(pool != NULL);
    ITS_C_REQUIRE(first != NULL);

    ret = MLIST_RemHead(TPOOL_AVAIL_THREADS(pool), &data, &len);

    *first = NULL;

    if (ret == ITS_SUCCESS && len == sizeof(TPOOL_THREAD *))
    {
        *first = *(TPOOL_THREAD **)data;

        ITS_Free(data);
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Return a thread back to the avail list.
 *
 *  Input Parameters:
 *      tpool - the pool to return the thread to.
 *      thr - the thread to return
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the thread was successfully returned to the avail
 *      pool.  Any other return code indicates an IntelliSS7 processing
 *      error.
 *
 *  Notes:
 *      This function should only be called if a thread cannot be
 *      dispatched for some reason.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_ReturnToAvailThreads(TPOOL* pool, TPOOL_THREAD* thr)
{
    ITS_C_REQUIRE(pool != NULL);
    ITS_C_REQUIRE(thr != NULL);

    return MLIST_AddTail(TPOOL_AVAIL_THREADS(pool),
                         &thr, sizeof(TPOOL_THREAD *));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Dispatch an allocated thread to execute a particular function.
 *
 *  Input Parameters:
 *      thr - the thread that will execute the function
 *      func - the function that will execute
 *      arg - the argument to pass to the function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the thread was successfully dispatched.
 *      Any other return code indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_DispatchOnThread(TPOOL_THREAD* thr, TPOOL_FUNC func, void *arg)
{
    ITS_C_REQUIRE(thr != NULL);
    ITS_C_REQUIRE(func != NULL);

    TPOOL_THREAD_FUNC(thr) = func;
    TPOOL_THREAD_ARG(thr) = arg;

    THREAD_ThreadResume((ITS_THREAD *)thr);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a thread from the pool and dispatch it on a particular
 *      execution function.
 *
 *  Input Parameters:
 *      tpool - the pool to allocate from
 *      func - the function that will execute
 *      arg - the argument to pass to the function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the thread was successfully allocated and dispatched.
 *      Any other return code indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *      This function combines a call to TPOOL_GetFirstAvailThread(),
 *      followed by a call to TPOOL_DispatchOnThread().
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TPOOL_Dispatch(TPOOL* pool, TPOOL_FUNC func, void *arg)
{
    int ret;
    TPOOL_THREAD* head;

    ITS_C_REQUIRE(pool != NULL);

    if ((ret = TPOOL_GetFirstAvailThread(pool, &head)) == ITS_SUCCESS)
    {
        return TPOOL_DispatchOnThread(head, func, arg);
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function provides the thread management for the thread
 *      pool.  It is responsible for catching and pausing newly
 *      created threads, and for avail/busy manipulation before and
 *      after units of work.
 *
 *  Input Parameters:
 *      arg - an argument passed for management purposes.  It points to
 *      a TPOOL_THREAD_ARG allocated by InitPool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The return value is OS dependent.  However, it is not visible
 *      to the user.
 *
 *  Notes:
 *      This function should be considered private.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI THREAD_RET_TYPE
TPOOL_ThreadFunc(void *arg)
{
    TPOOL_THREAD_ARG* poolArg = (TPOOL_THREAD_ARG *)arg;
    TPOOL_HEAP_OBJ* refCounter = poolArg->refCounter;
    TPOOL_THREAD* entry = poolArg->entry;
    MLIST_Manager *avail = refCounter->avail, *busy = refCounter->busy;

    /* we don't need this anymore */
    free(poolArg);

    while (entry != NULL && !TPOOL_THREAD_EXIT(entry) && !refCounter->exit)
    {
        LIST_Entry* ent;

        /*
         * add to busy queue
         * Dispatch() and DispatchOnThread() remove us from the avail list.
         */
        MLIST_AddTail(busy, &entry, sizeof(TPOOL_THREAD *));

        /*
         * We've been resumed to perform some action
         */
        if (TPOOL_THREAD_FUNC(entry) != NULL)
        {
            (TPOOL_THREAD_FUNC(entry))(entry, TPOOL_THREAD_ARG(entry));
        }

        MLIST_Lock(busy);

        for (ent = LIST_HEAD(busy); ent != NULL; ent = ent->next)
        {
            if (*((TPOOL_THREAD **)ent->data) == entry)
            {
                MLIST_RemoveNoLock(busy, ent);

                break;
            }
        }

        ITS_Free(ent->data);
        ITS_Free(ent);

        MLIST_Unlock(busy);

        MLIST_AddTail(avail, &entry, sizeof(TPOOL_THREAD *));

        if (TPOOL_THREAD_EXIT(entry) || refCounter->exit)
        {
            /* 
             * The state of the thread has changed during its execution. 
             * We are now in the process of destroying the ThreadPool  
             */
            break;
        }

        /* wait for something to do */
        THREAD_ThreadSuspend((ITS_THREAD *)entry);
    }

    /*
     * bailing out
     */
    free(entry);
    /* FIXME: That free should be TPOOLTHREAD_Destroy(entry); */

    refCounter->thrCount--;

    if (refCounter->thrCount == 0)
    {
        SEMA_WaitSemaphore(&TPOOL_CLASS_SYNC_OBJ(itsTPOOL_Class));

        MLIST_Delete(refCounter->avail);
        MLIST_Delete(refCounter->busy);
        free(refCounter);

        SEMA_PostSemaphore(&TPOOL_CLASS_SYNC_OBJ(itsTPOOL_Class));
    }

    THREAD_ThreadExit(NULL);

    /* NOTREACHED */
    THREAD_NORMAL_EXIT;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Wait for the deletion of a thread pool to signal complete
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
TPOOL_WaitForDestroyComplete()
{
    SEMA_WaitSemaphore(&TPOOL_CLASS_SYNC_OBJ(itsTPOOL_Class));
}

