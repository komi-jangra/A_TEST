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
 * LOG: Revision 8.2  2005/03/21 13:52:16  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
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
 * LOG: Revision 1.1  2001/02/12 21:11:03  lbana
 * LOG: vxworks platform specific for condition variable implementation
 * LOG:
 *
 ****************************************************************************/

#include <unistd.h>
#include <time.h>

#include <its.h>
#include <its_condvar.h>
#include <its_trace.h>

#ident "$Id: its_condvar.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
CONDVAR_Create(ITS_CONDVAR *cv)
{
    cv->waiters = 0;
    cv->wasBroadcast = ITS_FALSE;

    if ((cv->cv_sema = semCCreate(SEM_Q_FIFO, 0)) == NULL)
    {
        return (ITS_EBADSEMAPHORE);
    }

    if (MUTEX_CreateMutex(&cv->waiterLock, 0) == -1)
    {
        semDelete(cv->cv_sema);

        return (ITS_EBADMUTEX);
    }

    if ( (cv->waitersDone = semCCreate(SEM_Q_FIFO, 0)) == NULL)
    {
        MUTEX_DeleteMutex(&cv->waiterLock);

        semDelete(cv->cv_sema);

        return (ITS_EBADSEMAPHORE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
CONDVAR_Destroy(ITS_CONDVAR *cv)
{
    semDelete(cv->waitersDone);

    MUTEX_DeleteMutex(&cv->waiterLock);

    semDelete(cv->cv_sema);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
CONDVAR_Delete(ITS_CONDVAR *cv)
{
    semDelete(cv->waitersDone);

    MUTEX_DeleteMutex(&cv->waiterLock);

    semDelete(cv->cv_sema);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
CONDVAR_Wait(ITS_CONDVAR *cv, ITS_MUTEX *m)
{
    ITS_BOOLEAN lastWaiter = ITS_FALSE;
    int result = 0;

    /* Prevent race conditions on the <waiters> count. */
    if (MUTEX_AcquireMutex(&cv->waiterLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    cv->waiters++;

    MUTEX_ReleaseMutex(&cv->waiterLock);

    /*
     * We keep the lock held just long enough to increment the count of
     * waiters by one.  Note that we can't keep it held across the call
     * to semTake() since that will deadlock other calls to
     * CONDVAR_Signal().
     */
    if (MUTEX_ReleaseMutex(m) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /*
     * Wait to be awakened by a CONDVAR_Signal() or
     * CONDVAR_Broadcast().  Note that there isn't much
     * we can do if the take fails
     */
    semTake(cv->cv_sema, WAIT_FOREVER);

    /* Reacquire lock to avoid race conditions on the <waiters> count. */
    if (MUTEX_AcquireMutex(&cv->waiterLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* We're ready to return, so there's one less waiter. */
    cv->waiters--;

    lastWaiter = cv->wasBroadcast && cv->waiters == 0;

    /*
     * Release the lock so that other collaborating threads can make
     * progress.
     */
    MUTEX_ReleaseMutex(&cv->waiterLock);

    /* release the hounds */
    if (lastWaiter)
    {
        semGive(cv->waitersDone);
    }

    return MUTEX_AcquireMutex(m);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
CONDVAR_WaitWithTimeOut(ITS_CONDVAR *cv, ITS_MUTEX *m,
                        ITS_UINT millisecs)
{
    volatile ITS_BOOLEAN lastWaiter = ITS_FALSE;

    if (millisecs == TIME_FOREVER)
    {
        return CONDVAR_Wait(cv, m);
    }

    /* Prevent race conditions on the <waiters> count. */
    if (MUTEX_AcquireMutex(&cv->waiterLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    cv->waiters++;

    MUTEX_ReleaseMutex(&cv->waiterLock);

    /*
     * We keep the lock held just long enough to increment the count
     * of waiters by one
     */
    if (MUTEX_ReleaseMutex(m) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    /* Wait to be awakened by a signal() or broadcast(). */
    /* note that there's not much we can do if this fails */
    semTake(cv->cv_sema, millisecs * sysClkRateGet() / MSEC_PER_SEC);

    /* Reacquire lock to avoid race conditions. */
    /* assume success */
    MUTEX_AcquireMutex(&cv->waiterLock);

    cv->waiters--;

    lastWaiter = cv->wasBroadcast && cv->waiters == 0;

    MUTEX_ReleaseMutex(&cv->waiterLock);

    /* release the hounds */
    if (lastWaiter)
    {
        semGive(cv->waitersDone);
    }

    return MUTEX_AcquireMutex(m);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
CONDVAR_Signal(ITS_CONDVAR *cv)
{
    volatile ITS_BOOLEAN haveWaiters;

    if (MUTEX_AcquireMutex(&cv->waiterLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    haveWaiters = (cv->waiters > 0) ? ITS_TRUE : ITS_FALSE;

    MUTEX_ReleaseMutex(&cv->waiterLock);

    if (haveWaiters != 0)
    {
        return semGive(cv->cv_sema);
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
ITSDLLAPI int
CONDVAR_Broadcast(ITS_CONDVAR *cv)
{
    volatile ITS_BOOLEAN haveWaiters = ITS_FALSE;
    int i;

    if (MUTEX_AcquireMutex(&cv->waiterLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (cv->waiters > 0)
    {
        /*
         * We are broadcasting, even if there is just one waiter...
         * Record the fact that we are broadcasting.  This helps the
         * cond_wait() method know how to optimize itself.  Be sure to
         * set this with the <waitLock> held.
         */
        cv->wasBroadcast = ITS_TRUE;

        haveWaiters = ITS_TRUE;
    }

    if (haveWaiters)
    {
        /* wake up all the waiters. */
        for (i = 0; i < cv->waiters; i++)
        {
            if (semGive(cv->cv_sema) != OK)
            {
                cv->wasBroadcast = ITS_FALSE;

                MUTEX_ReleaseMutex(&cv->waiterLock);

                return (ITS_EBADSEMAPHORE);
            }
        }

        MUTEX_ReleaseMutex(&cv->waiterLock);

        /*
         * Wait for all the awakened threads to acquire their part of
         * the counting semaphore.
         */
        if (semTake(cv->waitersDone, WAIT_FOREVER) != OK)
        {
            cv->wasBroadcast = ITS_FALSE;

            return (ITS_EBADSEMAPHORE);
        }

        cv->wasBroadcast = ITS_FALSE;
    }
    else
    {
        MUTEX_ReleaseMutex(&cv->waiterLock);
    }

    return (ITS_SUCCESS);
}
