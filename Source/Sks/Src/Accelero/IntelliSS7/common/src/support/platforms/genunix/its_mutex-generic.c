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
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:09  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:13  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
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
 * LOG: Revision 3.1  2000/08/16 00:05:56  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  2000/06/02 02:05:19  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:52  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/09/30 20:42:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add some stuff for primitive RTOSs.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_mutex.h>

#ident "$Id: its_mutex-generic.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function initializes a mutex to a known state (locked or
 *      unlocked).
 *
 *  Input Parameters:
 *      initState - the desired initial lock state of the mutex.  0 indicates
 *          the mutex should be created unlocked, non-zero indicates that the
 *          mutex should be created locked.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      m - the address of an ITS_MUTEX object
 *
 *  Return Value:
 *      If the mutex is successfully created, ITS_SUCCESS is returned.
 *      Any other error code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_DeleteMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_CreateMutex(ITS_MUTEX *m, int initState)
{
    if (m == NULL)
    {
        return (ITS_EBADMUTEX);
    }
    
    SPINLOCK_Unlock(&m->list_lock);
    m->list = LIST_Create();
    m->locked = initState;
    
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method removes the mutex from the operating system's list of
 *      mutexes associated with this process.
 *
 *  Input Parameters:
 *      m - the address of the mutex to destroy
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
 *      MUTEX_CreateMutex()
 ****************************************************************************/
ITSDLLAPI void
MUTEX_DeleteMutex(ITS_MUTEX *m)
{
    if (m == NULL)
    {
        return;
    }
    
    SPINLOCK_Unlock(&m->list_lock);
    LIST_Delete(m->list);
    m->locked = 0;
}
    
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function attempts to acquire the mutex.  If the mutex is
 *      currently locked, the calling entity will block until the mutex is
 *      unlocked.
 *
 *  Input Parameters:
 *      m - the address of the mutex to acquire
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the mutex was successfully acquired, ITS_SUCCESS is returned.
 *      Any other return value indicates that an IntelliSS7 error occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_ReleaseMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_AcquireMutex(ITS_MUTEX *m)
{
    if (m == NULL)
    {
        return (ITS_EBADMUTEX);
    }

    SPINLOCK_Lock(&m->list_lock);

    if (m->locked && THREAD_GetSelf() != m->owner)
    {
        LIST_AddTail(m->list, THREAD_GetSelf(), sizeof(ITS_THREAD));
        
        SPINLOCK_Unlock(&m->list_lock);

        THREAD_SuspendThread(THREAD_GetSelf());
    }
    else
    {
        m->locked++;

        SPINLOCK_Unlock(&m->list_lock);
    }
    
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method tries to acquire the mutex without blocking the calling
 *      entity.
 *
 *  Input Parameters:
 *      m - the address of the mutex object to acquire
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the mutex was acquired (without blocking), ITS_SUCCESS is returned.
 *      Any other return value indicates that the mutex was not acquired,
 *          or that an IntelliSS7 error occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_AcquireMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_TryAcquireMutex(ITS_MUTEX *m)
{
    if (m == NULL)
    {
        return (ITS_EBADMUTEX);
    }
    
    SPINLOCK_Lock(&m->list_lock);

    if (m->locked && m->owner != THREAD_GetSelf())
    {
        SPINLOCK_Unlock(&m->list_lock);

        return (ITS_EWOULDBLOCK);
    }

    /* not locked, take it */
    m->locked++;

    SPINLOCK_Unlock(&m->list_lock);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method unlocks an already acquired mutex.  If the mutex was not
 *      locked when this function was invoked, the results are undefined.
 *
 *  Input Parameters:
 *      m - the address of the mutex to release.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the mutex was successfully unlocked, ITS_SUCCESS is returned.
 *      Any other return value indicates an error unlocking the mutex.
 *
 *  Notes:
 *
 *  See Also:
 *      MUTEX_AcquireMutex()
 ****************************************************************************/
ITSDLLAPI int
MUTEX_ReleaseMutex(ITS_MUTEX *m)
{
    if (m == NULL)
    {
        return (ITS_EBADMUTEX);
    }

    SPINLOCK_Lock(&m->list_lock);

    if (!m->locked)
    {
        SPINLOCK_Unlock(&m->list_lock);
        
        return (ITS_EINVALIDARGS);
    }
    
    m->locked--;

    if (!m->locked && !LIST_EmptyP(&m->list))
    {
        ITS_THREAD *thread;
        int len;

        LIST_RemHead&m->list, &thread, &len);
        
        assert(len == sizeof(ITS_THREAD *));
        
        SPINLOCK_Unlock(&m->list_lock);

        THREAD_ThreadResume(thread);
    }
    else
    {
        SPINLOCK_Unlock(&m->list_lock);
    }
    
    return (ITS_SUCCESS);
}
