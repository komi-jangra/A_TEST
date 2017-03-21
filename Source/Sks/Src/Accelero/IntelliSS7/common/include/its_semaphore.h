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
 * LOG: Revision 8.2  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/30 22:34:13  mmiers
 * LOG: Comment updates
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
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
 * LOG: Revision 3.4  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/17 16:04:03  mmiers
 * LOG: Symbol collision on vxWorks
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:21  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/08/09 00:08:19  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:58  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:43  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.22  1999/09/16 15:16:31  mmiers
 * LOG:
 * LOG:
 * LOG: Make all IPC semaphore operations not undoable on process exit.
 * LOG:
 * LOG: Revision 1.21  1999/08/30 17:53:42  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.20  1999/08/13 23:25:23  mmiers
 * LOG:
 * LOG:
 * LOG: Change the semantics of the IPC semaphore a bit.
 * LOG:
 * LOG: Revision 1.19  1999/07/28 02:17:19  mmiers
 * LOG:
 * LOG: Make arg names more meaningful.
 * LOG:
 * LOG: Revision 1.18  1999/06/28 23:45:23  skarmakar
 * LOG:
 * LOG:
 * LOG: More work on portability.
 * LOG:
 * LOG: Revision 1.17  1999/06/28 23:19:02  skarmakar
 * LOG:
 * LOG:
 * LOG: Many many portability fixes.
 * LOG:
 * LOG: Revision 1.16  1999/06/24 01:01:56  mmiers
 * LOG:
 * LOG:
 * LOG: Add an IPC semaphore.
 * LOG:
 * LOG: Revision 1.15  1998/09/30 20:33:24  jrao
 * LOG: Fix a number of release bugs with pthread_cond_t(s).
 * LOG:
 * LOG: Revision 1.14  1998/09/30 17:20:16  jrao
 * LOG: Update for HPUX.  Convert from UNIX semaphores to condition variables.
 * LOG:
 * LOG: Revision 1.13  1998/09/22 15:17:59  mmiers
 * LOG: Fix brain damage.
 * LOG:
 * LOG: Revision 1.12  1998/09/21 17:25:19  jrao
 * LOG: Added HPUX support
 * LOG:
 * LOG: Revision 1.11  1998/06/20 03:50:25  mmiers
 * LOG: Add Linux as a target.
 * LOG:
 * LOG: Revision 1.10  1998/06/01 16:35:18  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.9  1998/05/26 23:38:13  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.8  1998/05/19 17:11:47  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.7  1998/05/01 00:24:33  mmiers
 * LOG: Update routing functions.
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
 * LOG: Revision 1.3  1998/04/03 23:45:06  mmiers
 * LOG: More changes to support C++.
 * LOG:
 * LOG: Revision 1.2  1998/04/03 22:17:53  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 00:26:26  mmiers
 * LOG: New file for semaphore support.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_SEMAPHORE_H
#define ITS_SEMAPHORE_H

#include <its_mutex.h>
#include <its_condvar.h>

#ident "$Id: its_semaphore.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if !defined(ITS_SEMAPHORE_ONESHOT)
#define ITS_SEMAPHORE_ONESHOT

/*
 * this is now platform independent
 */
typedef struct
{
    ITS_MUTEX         semGuard;
    ITS_UINT          semCounter;
    ITS_CONDVAR       semCondition;
}
ITS_SEMAPHORE;

#endif /* ITS_SEMAPHORE_ONESHOT */

#ifdef __cplusplus
extern "C" {
#endif

/*.interface:SEMA
 *****************************************************************************
 *  Interface:
 *      SEMA_*
 *
 *  Purpose:
 *      The ITS_SEMAPHORE function group provides the behavior of
 *      Semaphore objects to users implementing in C.  The
 *      C++ object methods are very similar to the C API; not
 *      surprisingly, as the C++ methods merely call their C
 *      counterparts.
 *
 *      For more information on the basics of semaphores, see the
 *      interface description of the Semaphore class above,
 *      or consult any decent book on Operating Systems.
 *
 *  Usage:
 *      The usage of ITS_SEMAPHORE(s) is described below.  Note that
 *      some operating systems allow semaphore objects to be declared
 *      globally, thus circumventing the need for explicit creation.
 *      THIS BEHAVIOR IS NOT SUPPORTED BY IntelliSS7.  Useage of
 *      ITS_SEMAPHORE objects in this fashion is strongly discouraged,
 *      as it is inherently non-portable.  You have been warned.
 *
 *      -----------------------------------------------------------------
 *      ITS_SEMAPHORE s;
 *
 *      ...
 *
 *      * Create the semaphore
 *      * The 0 indicates that the semaphore should be created
 *      * in the unsignalled state.
 *      if (SEMA_CreateSemaphore(&s, 0) != ITS_SUCCESS)
 *      {
 *          * indicates that the semaphore was not
 *          * correctly initialized
 *      }
 *
 *      ...
 *
 *      * the "owner" of the semaphore "Wait"s on it:
 *      for (;;)
 *      {
 *          if (SEMA_WaitSemaphore(&s) == ITS_SUCCESS)
 *          {
 *              * the condition was signalled.  Wait() will return
 *              * (nonblocking) for the number of times the semaphore
 *              * was "Post"ed.
 *          }
 *      }
 *
 *      ...
 *
 *      * as an alternative, the user can see if the semaphore
 *      * has been posted without blocking
 *      if (SEMA_TryWaitSemaphore(&s) == ITS_SUCCESS)
 *      {
 *          * the semaphore had been posted *
 *      }
 *      else
 *      {
 *          * the semaphore had not been posted *
 *      }
 *
 *      ...
 *
 *      * other entities (but possibly the semaphore owner) may be
 *      * interested in posting the semaphore.  This operation
 *      * is by definition thread-safe.
 *      SEMA_PostSemaphore(&s);
 *
 *      ...
 *
 *      * semaphores should be deleted when no longer of use.
 *      * The result of deleting a semaphore that has an entity
 *      * "Wait"ing for it is undefined.
 *      SEMA_DeleteSemaphore(&s);
 *
 *      -----------------------------------------------------------------
 *
 *      The Semaphore methods are all thread-safe.
 *
 *
 *****************************************************************************/
ITSDLLAPI int SEMA_CreateSemaphore(ITS_SEMAPHORE *sem, int initCount);
ITSDLLAPI void SEMA_DeleteSemaphore(ITS_SEMAPHORE *sem);
ITSDLLAPI int SEMA_TryWaitSemaphore(ITS_SEMAPHORE *sem);
ITSDLLAPI int SEMA_WaitSemaphore(ITS_SEMAPHORE *sem);
ITSDLLAPI int SEMA_WaitSemaphoreWithTimeOut(ITS_SEMAPHORE *sem, ITS_UINT millisecs);
ITSDLLAPI int SEMA_PostSemaphore(ITS_SEMAPHORE *sem);

/*
 * Not all platforms will have this implemented.  It is useless
 * for an RTOS where the concept of a 'process' doesn't exist
 * (e.g., vxWorks).
 */
#if !defined(RTOS_PLATFORM)

ITSDLLAPI int SEMA_CreateIPCSemaphore(ITS_IPC_SEMAPHORE *sem, int key);
ITSDLLAPI void SEMA_DeleteIPCSemaphore(ITS_IPC_SEMAPHORE *sem);
ITSDLLAPI int SEMA_TryWaitIPCSemaphore(ITS_IPC_SEMAPHORE *sem, ITS_BOOLEAN undo);
ITSDLLAPI int SEMA_WaitIPCSemaphore(ITS_IPC_SEMAPHORE *sem, ITS_BOOLEAN undo);
ITSDLLAPI int SEMA_PostIPCSemaphore(ITS_IPC_SEMAPHORE *sem, ITS_BOOLEAN undo);

#else

#define SEMA_CreateIPCSemaphore(s, k)   SEMA_CreateSemaphore((s), 0)
#define SEMA_DeleteIPCSemaphore(s)      SEMA_DeleteSemaphore((s))
#define SEMA_TryWaitIPCSemaphore(s, u)  SEMA_TryWaitSemaphore((s))
#define SEMA_WaitIPCSemaphore(s, u)     SEMA_WaitSemaphore((s))
#define SEMA_PostIPCSemaphore(s, u)     SEMA_PostSemaphore((s))

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

/*.interface:Semaphore
 *****************************************************************************
 *  Interface:
 *      ITS_Semphore
 *
 *  Purpose:
 *      The Semaphore class is intended to support lightweight semaphores
 *      for intertask communication.  They are NOT intended to support
 *      interprocess synchronization, although for some operating systems
 *      (i.e., those that don't support condition variables) they are
 *      implemented as kernel objects.  (NOTE: this last observation may
 *      change in favor of hand-built condition variables on those OS's that
 *      don't natively support them).
 *
 *      An Semaphore is used to signal tasks waiting on the semaphore
 *      that a condition has occurred, or a resource has become available.
 *      Semaphore(s) are very similar to ITS_Mutex(s) in that they can
 *      "gate" access to a resource (or critical section).  Syntactically
 *      they are similar, while semantically they are not.
 *
 *  Usage:
 *      Typically, Semaphores are waited for by one entity, and posted
 *      by multilple entities.  The Semaphore is a counting semaphore,
 *      NOT a binary semaphore.
 *
 *      The most common useage of Semaphore(s) in IntelliSS7 is as a
 *      condition variable indicating that data is present on a task queue.
 *      The (one and only) task consuming messages from the task queue
 *      "Wait"s on the semaphore; any entity that "Post"s a message on the
 *      task queue effectively wakes the waiting task so that the message
 *      can be processed.
 *
 *      Semaphore(s) can be created in the non-signalled state or the
 *      signalled state.  As with ITS_Mutex(s), Semaphore(s) should
 *      not be declared global unless the user *knows* that the semaphore
 *      will be created before it can ever be used.
 *
 *      -----------------------------------------------------------------
 *      Semaphore *s = new Semaphore(0);    // 0 -- unsignalled
 *
 *      ...
 *
 *      // the "owner" of the semaphore "Wait"s on it:
 *      for (;;)
 *      {
 *          if (s->Wait() == ITS_SUCCESS)
 *          {
 *              // the condition was signalled.  Wait() will return
 *              // (nonblocking) for the number of times the semaphore
 *              // was "Post"ed.
 *          }
 *      }
 *
 *      ...
 *
 *      // as an alternative, the user can see if the semaphore
 *      // has been posted without blocking
 *      if (s->TryWait() == ITS_SUCCESS)
 *      {
 *          // the semaphore had been posted
 *      }
 *      else
 *      {
 *          // the semaphore had not been posted
 *      }
 *
 *      ...
 *
 *      // other entities (but possibly the semaphore owner) may be
 *      // interested in posting the semaphore.  This operation
 *      // is by definition thread-safe.
 *      s->Post();
 *
 *      ...
 *
 *      // semaphores should be deleted when no longer of use.
 *      // The result of deleting a semaphore that has an entity
 *      // "Wait"ing for it is undefined.
 *      delete s;
 *      -----------------------------------------------------------------
 *
 *      The Semaphore methods are all thread-safe.
 *
 *****************************************************************************/
class Semaphore
{
public:
    /*.implementation:public,inline,Semaphore
     ************************************************************************
     *  Purpose:
     *      This method creates an Semaphore object, initializing the
     *      contained ITS_SEMAPHORE object according to the constructor args.
     *
     *  Input Parameters:
     *      initCount - indicates the initial count the semaphore should have
     *          at the time of creation.  0 indicates an unsignaled semaphore.
     *          Non-zero indicates a signaled semaphore that has been posted
     *          initCount times.
     *
     *  Notes:
     *      This method may throw an exception if the semaphore cannot be
     *      created.
     *
     *  See Also:
     *      ~Semaphore()
     ************************************************************************/
    Semaphore(int initCount)
    {
        if (SEMA_CreateSemaphore(&semaphore, initCount) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSEMAPHORE, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,Semaphore
     ************************************************************************
     *  Purpose:
     *      This method destroys the Semaphore object.
     *
     *  Notes:
     *      The result of calling this method while entities are pending on
     *      the semaphore is undefined.
     *
     *  See Also:
     *      Semaphore()
     ************************************************************************/
    virtual ~Semaphore()
    {
        SEMA_DeleteSemaphore(&semaphore);
    }

    /*.implementation:public,inline,Semaphore
     ************************************************************************
     *  Purpose:
     *      This method will try to see if the semaphore has been posted in a
     *      non-blocking fashion.
     *
     *  Return Value:
     *      If the semaphore was posted, ITS_SUCCESS is returned.
     *      Any other return value indicates that the semaphore was not posted,
     *          or that an IntelliSS7 error occurred.
     *
     *  Notes:
     *      If the semaphore was posted, the semaphore count is reduced by 1
     *      if ITS_SUCCESS is returned, exactly as if the semaphore had been
     *      "Wait"ed on.
     *
     *  See Also:
     *      Wait()
     ************************************************************************/
    int
    TryWait()
    {
        return SEMA_TryWaitSemaphore(&semaphore);
    }
    /*.implementation:public,inline,Semaphore
     ************************************************************************
     *  Purpose:
     *      This method will check to see if the semaphore has been "Post"ed.  If
     *      the semaphore has not been "Post"ed, the caller will be blocked until
     *      such time as the "Post" occurs.
     *
     *  Return Value:
     *      The result of a successful call is ITS_SUCCESS.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The semaphore count is reduced by 1 every time this method
     *      successfully returns.  When the semaphore count reaches zero,
     *      the semaphore goes to the un"Post"ed state.
     *
     *  See Also:
     *      Post()
     ************************************************************************/
    int
    Wait()
    {
        return SEMA_WaitSemaphore(&semaphore);
    }
    /*.implementation:public,inline,Semaphore
     ************************************************************************
     *  Purpose:
     *      This method will check to see if the semaphore has been "Post"ed.  If
     *      the semaphore has not been "Post"ed, the caller will be blocked until
     *      such time as the "Post" occurs or the timeout expires.
     *
     *  Input Parameters:
     *      millisecs - the number of millisecs to wait.
     *
     *  Return Value:
     *      The result of a successful call is ITS_SUCCESS.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The semaphore count is reduced by 1 every time this method
     *      successfully returns.  When the semaphore count reaches zero,
     *      the semaphore goes to the un"Post"ed state.
     *
     *  See Also:
     *      Post()
     ************************************************************************/
    int
    WaitWithTimeOut(ITS_UINT millisecs)
    {
        return SEMA_WaitSemaphoreWithTimeOut(&semaphore, millisecs);
    }
    /*.implementation:public,inline,Semaphore
     ************************************************************************
     ************************************************************************/
    int
    Post()
    {
        return SEMA_PostSemaphore(&semaphore);
    }

private:
    /* sorry folks, no copying these */
    Semaphore() {}
    Semaphore(Semaphore&) {}
    Semaphore& operator=(Semaphore&) { return *this; }

    ITS_SEMAPHORE semaphore;
};

class IPCSemaphore
{
public:
    /*.implementation:public,inline,IPCSemaphore
     ************************************************************************
     *  Purpose:
     *      This method creates an Semaphore object, initializing the
     *      contained ITS_IPC_SEMAPHORE object according to the constructor args.
     *
     *  Input Parameters:
     *      initCount - indicates the initial count the semaphore should have
     *          at the time of creation.  0 indicates an unsignaled semaphore.
     *          Non-zero indicates a signaled semaphore that has been posted
     *          initCount times.
     *
     *  Notes:
     *      This method may throw an exception if the semaphore cannot be
     *      created.
     *
     *  See Also:
     *      ~Semaphore()
     ************************************************************************/
    IPCSemaphore(int key)
    {
        if (SEMA_CreateIPCSemaphore(&semaphore, key) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSEMAPHORE, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,IPCSemaphore
     ************************************************************************
     *  Purpose:
     *      This method destroys the Semaphore object.
     *
     *  Notes:
     *      The result of calling this method while entities are pending on
     *      the semaphore is undefined.
     *
     *  See Also:
     *      Semaphore()
     ************************************************************************/
    ~IPCSemaphore()
    {
        SEMA_DeleteIPCSemaphore(&semaphore);
    }

    /*.implementation:public,inline,IPCSemaphore
     ************************************************************************
     *  Purpose:
     *      This method will try to see if the semaphore has been posted in a
     *      non-blocking fashion.
     *
     *  Input Parameters:
     *      undo - should the operation be canceled if the application
     *      exits
     *
     *  Return Value:
     *      If the semaphore was posted, ITS_SUCCESS is returned.
     *      Any other return value indicates that the semaphore was not posted,
     *          or that an IntelliSS7 error occurred.
     *
     *  Notes:
     *      If the semaphore was posted, the semaphore count is reduced by 1
     *      if ITS_SUCCESS is returned, exactly as if the semaphore had been
     *      "Wait"ed on.
     *
     *  See Also:
     *      Wait()
     ************************************************************************/
    int
    TryWait(bool undo = true)
    {
        return SEMA_TryWaitIPCSemaphore(&semaphore,
                                        undo ? ITS_TRUE : ITS_FALSE);
    }
    /*.implementation:public,inline,IPCSemaphore
     ************************************************************************
     *  Purpose:
     *      This method will check to see if the semaphore has been "Post"ed.
     *      If the semaphore has not been "Post"ed, the caller will be
     *      blocked until such time as the "Post" occurs.
     *
     *  Input Parameters:
     *      undo - should the operation be canceled if the application
     *      exits
     *
     *  Return Value:
     *      The result of a successful call is ITS_SUCCESS.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The semaphore count is reduced by 1 every time this method
     *      successfully returns.  When the semaphore count reaches zero,
     *      the semaphore goes to the un"Post"ed state.
     *
     *  See Also:
     *      Post()
     ************************************************************************/
    int
    Wait(bool undo = true)
    {
        return SEMA_WaitIPCSemaphore(&semaphore,
                                     undo ? ITS_TRUE : ITS_FALSE);
    }
    /*.implementation:public,inline,IPCSemaphore
     ************************************************************************
     *  Purpose:
     *      This method "Post"s a semaphore; essentially this means the semaphore
     *      count is set to a non-zero value.  Any entities "Wait"ing for the
     *      semaphore will be resumed.
     *
     *  Input Parameters:
     *      undo - should the operation be canceled if the application
     *      exits
     *
     *  Return Value:
     *      On successful posting, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 error.
     *
     *  See Also:
     *      Wait()
     ************************************************************************/
    int
    Post(bool undo = true)
    {
        return SEMA_PostIPCSemaphore(&semaphore,
                                     undo ? ITS_TRUE : ITS_FALSE);
    }

private:
    /* sorry folks, no copying these */
    IPCSemaphore() {}
    IPCSemaphore(IPCSemaphore&) {}
    IPCSemaphore& operator=(IPCSemaphore&) { return *this; }

    ITS_IPC_SEMAPHORE semaphore;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_SEMAPHORE_H */
