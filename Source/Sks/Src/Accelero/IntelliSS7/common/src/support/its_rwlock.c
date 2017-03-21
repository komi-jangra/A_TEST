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
 * LOG: Revision 1.2  2007/03/30 04:59:08  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/14 20:46:55  mmiers
 * LOG: Move the lock unlock to appropriate place.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.3  2000/11/10 23:07:55  mmiers
 * LOG: Some work on bugs, help Laksha out with condvar.
 * LOG:
 * LOG: Revision 3.2  2000/09/01 20:56:31  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:38  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/06/22 19:57:26  rsonak
 * LOG:
 * LOG:
 * LOG: Use ITS_SUCCESS rather than magic number for error code check.
 * LOG:
 * LOG: Revision 2.1  2000/05/03 21:07:15  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>

#include <its.h>
#include <its_types.h>
#include <its_condvar.h>
#include <its_rwlock.h>
#include <its_trace.h>

#ident "$Id: its_rwlock.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates a reader/writer lock.
 *
 *  Input Parameters:
 *      rw - the lock to initialize
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the lock is initialized.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_DeleteLock()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_CreateLock(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_CreateLock:\n"));

    /* create the mutex */
    if (MUTEX_CreateMutex(&rw->guard, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_CreateLock: can't create cond mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (CONDVAR_Create(&rw->readerQueue) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_CreateLock: can't init condvar\n"));


        MUTEX_DeleteMutex(&rw->guard);

        return (ITS_EBADCONDVAR);
    }

    if (CONDVAR_Create(&rw->writerQueue) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_CreateLock: can't init condvar\n"));


        CONDVAR_Delete(&rw->readerQueue);

        MUTEX_DeleteMutex(&rw->guard);

        return (ITS_EBADCONDVAR);
    }

    rw->readerWaitCount = 0;
    rw->writerWaitCount = 0;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys the ITS_RWLOCK object.
 *
 *  Input Parameters:
 *      rw - the address of the ITS_RWLOCK object.
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
 *      The result of destroying a lock that has entities "Wait"ing on
 *      it is undefined.
 *
 *  See Also:
 *      RWLOCK_CreateLock()
 ****************************************************************************/
ITSDLLAPI void
RWLOCK_DeleteLock(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_DeleteLock:\n"));

    CONDVAR_Delete(&rw->writerQueue);

    CONDVAR_Delete(&rw->readerQueue);

    MUTEX_DeleteMutex(&rw->guard);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function waits for a non-exclusive lock to be granted.
 *
 *  Input Parameters:
 *      rw - the address of the lock to wait for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Once the lock is granted, ITS_SUCCESS is returned.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_UnlockShared()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_LockShared(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_LockShared:\n"));

    if (MUTEX_AcquireMutex(&rw->guard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_LockShared: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* say we are pending */
    rw->readerWaitCount++;

    if (rw->writerWaitCount > 0)
    {
        /* don't starve writers */
        if (CONDVAR_Wait(&rw->readerQueue, &rw->guard) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("RWLOCK_LockShared: can't wait condition\n"));

            MUTEX_ReleaseMutex(&rw->guard);

            return (ITS_EBADRWLOCK);
        }
    }

    /* wait for writers to get out */
    while (rw->numActive < 0)
    {
        if (CONDVAR_Wait(&rw->readerQueue, &rw->guard) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("RWLOCK_LockShared: can't wait condition\n"));

            MUTEX_ReleaseMutex(&rw->guard);

            return (ITS_EBADRWLOCK);
        }
    }

    /* say we're not pending. */
    rw->readerWaitCount--;

    /* another reader has the lock */
    rw->numActive++;

    MUTEX_ReleaseMutex(&rw->guard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function releases a non-exclusive lock.
 *
 *  Input Parameters:
 *      rw - the address of the ITS_RWLOCK to release
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_LockShared()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_UnlockShared(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_UnlockShared:\n"));

    if (MUTEX_AcquireMutex(&rw->guard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_UnlockShared: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* we do have to indicate we have quit */
    rw->numActive--;

    if (rw->numActive == 0)
    {
        CONDVAR_Signal(&rw->writerQueue);

        MUTEX_ReleaseMutex(&rw->guard);
    }
    else
    {
        MUTEX_ReleaseMutex(&rw->guard);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function waits for an exclusive lock to be granted.
 *
 *  Input Parameters:
 *      rw - the address of the lock to wait for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Once the lock is granted, ITS_SUCCESS is returned.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_UnlockExclusive()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_LockExclusive(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_LockExclusive:\n"));

    if (MUTEX_AcquireMutex(&rw->guard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_LockExclusive: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* inform readers a writer is waiting */
    rw->writerWaitCount++;

    while (rw->numActive != 0)
    {
        if (CONDVAR_Wait(&rw->writerQueue, &rw->guard) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("RWLOCK_LockExclusive: can't wait condition\n"));

            MUTEX_ReleaseMutex(&rw->guard);

            return (ITS_EBADRWLOCK);
        }
    }

    /* say we're not pending. */
    rw->writerWaitCount--;

    /* writer has the lock */
    rw->numActive--;

    MUTEX_ReleaseMutex(&rw->guard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function releases an exclusive lock.
 *
 *  Input Parameters:
 *      rw - the address of the ITS_RWLOCK to release
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_LockExclusive()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_UnlockExclusive(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_UnlockExclusive:\n"));

    if (MUTEX_AcquireMutex(&rw->guard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_UnlockExclusive: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* one fewer writer */
    rw->numActive++;

    /* see if any readers pending, first (don't starve them) */
    if (rw->readerWaitCount)
    {
        CONDVAR_Broadcast(&rw->readerQueue);

        MUTEX_ReleaseMutex(&rw->guard);
    }
    /* if none, see if another writer is waiting. */
    else if (rw->writerWaitCount > 0)
    {
        CONDVAR_Signal(&rw->writerQueue);

        MUTEX_ReleaseMutex(&rw->guard);
    }
    else
    {
        MUTEX_ReleaseMutex(&rw->guard);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function upgrades a non-exclusive lock to exclusive.
 *
 *  Input Parameters:
 *      rw - the address of the ITS_RWLOCK to lock exclusively.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_DowngradeToShared()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_UpgradeToExclusive(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_UpgradeExclusive:\n"));

    if (MUTEX_AcquireMutex(&rw->guard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_UnlockExclusive: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* only reader? */
    if (rw->numActive == 1)
    {
        rw->numActive = -1;
    }
    /* no, so convert ourselves into a write wait */
    else
    {
        rw->writerWaitCount++;

        rw->numActive--;

        while (rw->numActive != 0)
        {
            if (CONDVAR_Wait(&rw->writerQueue, &rw->guard) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("RWLOCK_UpgradeExclusive: "
                                 "can't wait condition\n"));

                MUTEX_ReleaseMutex(&rw->guard);

                return (ITS_EBADRWLOCK);
            }
        }
    }

    MUTEX_ReleaseMutex(&rw->guard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function downgrades an exclusive lock to non-exclusive.
 *
 *  Input Parameters:
 *      rw - the address of the ITS_RWLOCK to lock non-exclusively.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *
 *  See Also:
 *      RWLOCK_UpgradeExclusive()
 ****************************************************************************/
ITSDLLAPI int
RWLOCK_DowngradeToShared(ITS_RWLOCK *rw)
{
    ITS_TRACE_DEBUG(("RWLOCK_DowngradeToShared:\n"));

    if (MUTEX_AcquireMutex(&rw->guard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RWLOCK_DowngradeToShared: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* turn ourself into a reader */
    rw->numActive = 1;

    /* wake the other readers */
    if (rw->readerWaitCount > 0)
    {
        CONDVAR_Broadcast(&rw->readerQueue);

        MUTEX_ReleaseMutex(&rw->guard);
    }
    else
    {
        MUTEX_ReleaseMutex(&rw->guard);
    }

    return (ITS_SUCCESS);
}
