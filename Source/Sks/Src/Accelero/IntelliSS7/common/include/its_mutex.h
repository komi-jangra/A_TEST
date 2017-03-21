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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/30 22:34:13  mmiers
 * LOG: Comment updates
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:49:33  mmiers
 * LOG: Syntax error
 * LOG:
 * LOG: Revision 5.3  2001/11/08 16:16:11  mmiers
 * LOG: Make sure things compile without its_bc.h.  Fix MutexGuard.
 * LOG:
 * LOG: Revision 5.2  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.6  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/06/13 19:15:54  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.4  2000/04/25 14:52:52  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.  Also remove race from thread
 * LOG: pool where allocated but not started thread could miss pool
 * LOG: destruction [Ricardo].
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:32  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 21:40:56  mmiers
 * LOG:
 * LOG:
 * LOG: AsnCpp barfs because it doesn't include its.h, but uses ITS features.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:57  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:41  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1999/11/10 16:35:35  mmiers
 * LOG:
 * LOG:
 * LOG: Recursive mutexes for solaris.
 * LOG:
 * LOG: Revision 1.18  1999/11/09 22:15:36  labuser
 * LOG:
 * LOG:
 * LOG: Mutex type has changed on Solaris
 * LOG:
 * LOG: Revision 1.17  1999/09/30 20:42:54  mmiers
 * LOG:
 * LOG:
 * LOG: Add some stuff for primitive RTOSs.
 * LOG:
 * LOG: Revision 1.16  1999/08/30 17:53:41  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.15  1999/06/28 23:45:22  skarmakar
 * LOG:
 * LOG:
 * LOG: More work on portability.
 * LOG:
 * LOG: Revision 1.14  1999/06/28 23:19:02  skarmakar
 * LOG:
 * LOG:
 * LOG: Many many portability fixes.
 * LOG:
 * LOG: Revision 1.13  1998/10/01 00:01:41  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.12  1998/09/22 16:01:24  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.11  1998/06/01 16:35:17  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.10  1998/05/26 22:31:35  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.9  1998/05/19 17:11:47  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.8  1998/05/01 00:24:32  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.7  1998/04/17 21:22:28  mmiers
 * LOG: Thread pools are working.
 * LOG:
 * LOG: Revision 1.6  1998/04/09 14:33:19  mmiers
 * LOG: Visual complains about operator= not having a return value even when hidden
 * LOG: in the private section of the class record and given a stub implementation.
 * LOG:
 * LOG: Revision 1.5  1998/04/09 01:47:18  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.4  1998/04/06 15:26:05  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 22:17:53  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 00:25:59  mmiers
 * LOG: Get them to build on solaris.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:07:11  mmiers
 * LOG: Add some new files for lists, mutex protected lists, and semaphore gated
 * LOG: mutex protected lists.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_MUTEX_H
#define ITS_MUTEX_H

#include <its.h>

#ident "$Id: its_mutex.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#ifdef __cplusplus
extern "C" {
#endif

/*.interface:MUTEX
 *****************************************************************************
 *  Interface:
 *      MUTEX_*
 *
 *  Purpose:
 *      This interface provides an API for architecture independent mutual
 *      exclusion objects from "C".
 *
 *  Usage:
 *      The usage for the functions in this interface is quite similar to that
 *      of their C++ counterparts; this makes sense if you know that the C++
 *      methods call their corresponding C functions.
 *
 *      On some architectures, it is possible to create a mutex just by
 *      declaring globally an ITS_MUTEX variable;  THIS SHOULD BE AVOIDED
 *      AS THIS METHOD FOR INITIALIZATION IS NOT PORTABLE.  In other words, you
 *      should ALWAYS use MUTEX_CreateMutex().
 *
 *      Usage is as follows:
 *      --------------------------------------------------------------------
 *      ITS_MUTEX m;
 *
 *      ...
 *
 *      * NOTE: In the usage below, note that the user is passing the address
 *      * of an ITS_MUTEX, *NOT* a pointer s/he expects to be filled in.
 *      if (MUTEX_CreateMutex(&m, 0) == ITS_SUCCESS)
 *      {
 *          * the mutex has been created *
 *      }
 *
 *      ...
 *
 *      if (MUTEX_AcquireMutex(&m) == ITS_SUCCESS)
 *      {
 *          * the mutex has been acquired *
 *      }
 *      ...
 *
 *      if (MUTEX_ReleaseMutex(&m) == ITS_SUCCESS)
 *      {
 *          * the mutex has been released *
 *      }
 *
 *      ...
 *
 *      * you can also test for acquiring without blocking; if the
 *      * mutex is available you lock it -- if it isn't available
 *      * this routine returns an error
 *      if (MUTEX_TryAcquireMutex(&m) == ITS_SUCCESS)
 *      {
 *          * You got it *
 *      }
 *      else
 *      {
 *          * You didn't get it *
 *      }
 *
 *      ---
 *
 *      * you should delete mutexes you are finished with *
 *      MUTEX_DeleteMutex(&m);
 *
 *      --------------------------------------------------------------------
 *
 *****************************************************************************/
ITSDLLAPI int MUTEX_CreateMutex(ITS_MUTEX *m, int initState);
ITSDLLAPI void MUTEX_DeleteMutex(ITS_MUTEX *m);
ITSDLLAPI int MUTEX_TryAcquireMutex(ITS_MUTEX *m);
ITSDLLAPI int MUTEX_AcquireMutex(ITS_MUTEX *m);
ITSDLLAPI int MUTEX_ReleaseMutex(ITS_MUTEX *m);

/*
 * Not all platforms will have this implemented.  It is useless
 * for an RTOS where the concept of a 'process' doesn't exist
 * (e.g., vxWorks).
 */
#if !defined(RTOS_PLATFORM)

ITSDLLAPI int MUTEX_CreateIPCMutex(ITS_IPC_MUTEX *m, int key, int initState);
ITSDLLAPI void MUTEX_DeleteIPCMutex(ITS_IPC_MUTEX *m);
ITSDLLAPI int MUTEX_TryAcquireIPCMutex(ITS_IPC_MUTEX *m);
ITSDLLAPI int MUTEX_AcquireIPCMutex(ITS_IPC_MUTEX *m);
ITSDLLAPI int MUTEX_ReleaseIPCMutex(ITS_IPC_MUTEX *m);

#else

#define MUTEX_CreateIPCMutex(m, k, i)   MUTEX_CreateMutex((m), (i))
#define MUTEX_DeleteIPCMutex(m)         MUTEX_DeleteMutex((m))
#define MUTEX_TryAcquireIPCMutex(m)     MUTEX_TryAcquireMutex((m))
#define MUTEX_AcquireIPCMutex(m)        MUTEX_AcquireMutex((m))
#define MUTEX_ReleaseIPCMutex(m)        MUTEX_ReleaseMutex((m))

#endif

#ifdef __cplusplus
}
#endif

#if defined (USE_CPLUSPLUS)

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Mutex
 *****************************************************************************
 *  Interface:
 *      Mutex
 *
 *  Purpose:
 *      The Mutex class provides basic thread synchronization primitives
 *      for IntelliSS7.  It is used quite extensively in the infrastructure
 *      to ensure that IntelliSS7 is thread safe.
 *
 *      NOTE: The Mutex class does NOT provide synchronization primitives
 *      between processes.
 *
 *  Usage:
 *      The Mutex class can be statically or dynamically created.  Usage
 *      of statically created Mutex(s) is discouraged, as the user cannot
 *      know when the constructor for that Mutex is actually invoked;
 *      creating Mutex(s) statically should only be done if the user is
 *      *sure* that there are no dependencies on that mutex existing before
 *      threading actually begins.
 *
 *      Usage of Mutex(s) is very simple:
 *
 *      -----------------------------------------
 *      Mutex m(0); // if this is a global variable this implies
 *                      // static construction.  If this is done in
 *                      // function context, you're fine.
 *      -- or --
 *
 *      Mutex *m = new Mutex(0);    // this is always ok.
 *
 *      ...
 *
 *      if (m->Acquire() == ITS_SUCCESS)
 *      {
 *          // the mutex has been acquired
 *      }
 *
 *      ...
 *
 *      if (m->Release() == ITS_SUCCESS)
 *      {
 *          // the mutex has been released
 *      }
 *
 *      ...
 *
 *      // you can also test for acquiring without blocking; if the
 *      // mutex is available you lock it -- if it isn't available
 *      // this routine returns an error
 *      if (m->TryAcquire() == ITS_SUCCESS)
 *      {
 *          // You got it
 *      }
 *      else
 *      {
 *          // You didn't get it
 *      }
 *
 *      // The destructor does NOT automatically release the mutex.  The
 *      // result of calling the destructor on a locked mutex is undefined,
 *      // so I really wouldn't recommend you trying it.
 *      delete m;
 *      // or just let m go out of scope.
 *      --------------------------------------------------------------------
 *
 *****************************************************************************/
class Mutex
{
public:
    friend class CondVar;

    /*.implementation:public,inline,Mutex
     ************************************************************************
     *  Purpose:
     *      This method calls the C function ITS_CreateMutex on the ITS_MUTEX
     *      member of the Mutex object.
     *
     *  Input Parameters:
     *      initState = an indicator set to the initial state of the mutex.
     *          Zero indicates that the mutex should be created in the "Released"
     *          state, non-zero indicates that the mutex should be created in
     *          the "Acquired" state.
     *
     *  Notes:
     *      This method can throw an exception if the mutex cannot be successfully
     *      created.
     *
     *  See Also:
     *      ~Mutex()
     ************************************************************************/
    Mutex(int initState)
    {
        if (MUTEX_CreateMutex(&mutex, initState) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,Mutex
     ************************************************************************
     *  Purpose:
     *      This method destroyes the mutex associated with this Mutex
     *      object.
     *
     *  See Also:
     *      Mutex()
     ************************************************************************/
    virtual ~Mutex()
    {
        MUTEX_DeleteMutex(&mutex);
    }

    /*.implementation:public,inline,Mutex
     ************************************************************************
     *  Purpose:
     *      This method attempts to lock a mutex if it is currently unlocked.
     *      If the mutex is already locked, this method will fail.  This method
     *      should be used when non-blocking access to a mutex is required.
     *
     *  Return Value:
     *      If the mutex was locked, ITS_SUCCESS is returned.
     *      Any other return value indicates that the mutex could not be locked,
     *      or an IntelliSS7 error occurred.
     *
     *  See Also:
     *      Acquire()
     ************************************************************************/
    int
    TryAcquire()
    {
        return MUTEX_TryAcquireMutex(&mutex);
    }
    /*.implementation:public,inline,Mutex
     ************************************************************************
     *  Purpose:
     *      This method tries to lock a mutex.  If the mutex is currently locked,
     *      the caller will block until the current holder of the mutex unlocks
     *      it.
     *
     *  Return Value:
     *      If the mutex was successfully locked, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  See Also:
     *      Release()
     ************************************************************************/
    int
    Acquire()
    {
        return MUTEX_AcquireMutex(&mutex);
    }
    /*.implementation:public,inline,Mutex
     ************************************************************************
     *  Purpose:
     *      This method unlocks a mutex.  The results of calling this function
     *      for a mutex that is already unlocked is undefined.
     *
     *  Return Value:
     *      ITS_SUCCESS - mutex released
     *
     *  See Also:
     *      Acquire()
     ************************************************************************/
    int
    Release()
    {
        return MUTEX_ReleaseMutex(&mutex);
    }

private:
    /* sorry folks, no copying these */
    Mutex() {}
    Mutex(Mutex&) {}
    Mutex& operator=(Mutex&) { return *this; }

    ITS_MUTEX mutex;
};

class IPCMutex
{
public:
    /*.implementation:public,inline,IPCMutex
     ************************************************************************
     *  Purpose:
     *      This method calls the C function ITS_CreateMutex on the ITS_MUTEX
     *      member of the IPCMutex object.
     *
     *  Input Parameters:
     *      initState = an indicator set to the initial state of the mutex.
     *          Zero indicates that the mutex should be created in the "Released"
     *          state, non-zero indicates that the mutex should be created in
     *          the "Acquired" state.
     *
     *  Notes:
     *      This method can throw an exception if the mutex cannot be successfully
     *      created.
     *
     *  See Also:
     *      ~IPCMutex()
     ************************************************************************/
    IPCMutex(int key, int initState)
    {
        if (MUTEX_CreateIPCMutex(&mutex, key, initState) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,IPCMutex
     ************************************************************************
     *  Purpose:
     *      This method destroyes the mutex associated with this IPCMutex
     *      object.
     *
     *  See Also:
     *      IPCMutex()
     ************************************************************************/
    virtual ~IPCMutex()
    {
        MUTEX_DeleteIPCMutex(&mutex);
    }

    /*.implementation:public,inline,IPCMutex
     ************************************************************************
     *  Purpose:
     *      This method attempts to lock a mutex if it is currently unlocked.
     *      If the mutex is already locked, this method will fail.  This method
     *      should be used when non-blocking access to a mutex is required.
     *
     *  Return Value:
     *      If the mutex was locked, ITS_SUCCESS is returned.
     *      Any other return value indicates that the mutex could not be locked,
     *      or an IntelliSS7 error occurred.
     *
     *  See Also:
     *      Acquire()
     ************************************************************************/
    int
    TryAcquire()
    {
        return MUTEX_TryAcquireIPCMutex(&mutex);
    }
    /*.implementation:public,inline,IPCMutex
     ************************************************************************
     *  Purpose:
     *      This method tries to lock a mutex.  If the mutex is currently locked,
     *      the caller will block until the current holder of the mutex unlocks
     *      it.
     *
     *  Return Value:
     *      If the mutex was successfully locked, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  See Also:
     *      Release()
     ************************************************************************/
    int
    Acquire()
    {
        return MUTEX_AcquireIPCMutex(&mutex);
    }
    /*.implementation:public,inline,IPCMutex
     ************************************************************************
     *  Purpose:
     *      This method unlocks a mutex.  The results of calling this function
     *      for a mutex that is already unlocked is undefined.
     *
     *  Return Value:
     *      ITS_SUCCESS - mutex released
     *
     *  See Also:
     *      Acquire()
     ************************************************************************/
    int
    Release()
    {
        return MUTEX_ReleaseIPCMutex(&mutex);
    }

private:
    /* sorry folks, no copying these */
    IPCMutex() {}
    IPCMutex(IPCMutex&) {}
    IPCMutex& operator=(IPCMutex&) { return *this; }

    ITS_IPC_MUTEX mutex;
};

/*.interface:SynchGuard
 *****************************************************************************
 *  Interface:
 *      SynchGuard
 *
 *  Purpose:
 *      The SynchGuard class provides a safe way to implement short term
 *      mutex locks with IntelliSS7.  The mutex is acquired in the
 *      constructor, and released in the destructor.
 *
 *  Usage:
 *      This object is intended for use in situations where you need a short
 *      term lock on a mutex, and don't want to have to remember to release
 *      the lock.  The object takes advantage of the automatic call of
 *      C++ desctructors at the end of the scope of an object.
 *
 *      -------------------------------------------------------------
 *
 *      TableObject table;
 *      Mutex tableLock(0);
 *
 *      int
 *      TableObject::UpdateTable(NewInfo& info)
 *      {
 *          SynchGuard<Mutex>(tableLock);  // will throw exception if mutex
 *                                         // cannot be locked
 *          UpdateRow(info.key);
 *
 *          // now we just leave.  The Guard, going out of scope, is
 *          // destructed automatically and the table unlocked.
 *      }
 *
 *      -------------------------------------------------------------
 *  
 *****************************************************************************/
template <class _MutexType_>
class SynchGuard
{
public:
    /*.implementation:public,inline,SynchGuard
     ************************************************************************
     *  Purpose:
     *      This method constructs an automatic mutex guard
     *
     *  Input Parameters:
     *      mutex - the mutex to guard
     *
     *  Notes:
     *      This constructor can throw an exception if the mutex is invalid.
     *
     ************************************************************************/
    SynchGuard<_MutexType_>(_MutexType_& mutexParam)
        : mutex(mutexParam)
    {
        int ret = mutex.Acquire();

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }
    /*.implementation:public,inline,SynchGuard
     ************************************************************************
     *  Purpose:
     *      This method destructs an automatic mutex guard
     *
     ************************************************************************/
    virtual ~SynchGuard<_MutexType_>()
    {
        int ret = mutex.Release();

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }

private:
    _MutexType_& mutex;
};

typedef SynchGuard<Mutex>       MutexGuard;
typedef SynchGuard<IPCMutex>    IPCMutexGuard;

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_MUTEX_H */
