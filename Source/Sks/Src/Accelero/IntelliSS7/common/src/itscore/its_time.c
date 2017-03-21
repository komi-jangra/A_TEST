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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1  2004/01/05 09:24:05  sjaddu
 * LOG: Merged files from tcs isup branch.
 * LOG:
 * LOG: Revision 7.2.6.1  2003/09/05 10:12:14  akumar
 * LOG: Msg based redundancy commit.
 * LOG:
 * LOG: Revision 7.2.4.1  2003/05/05 22:04:36  randresol
 * LOG: Tag for GCS ISUP Prototype
 * LOG:
 * LOG: Revision 7.2  2003/01/16 17:12:52  mmiers
 * LOG: Move the base timer implementation to CORE
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#if !defined(vxworks)
#include <sys/timeb.h>
#if defined(linux)
#include <sys/time.h>
#endif
#else
#include <timers.h>
#include <time.h>
#endif

#include <its.h>
#include <its_timers.h>
#include <its_assertion.h>
#include <its_dsm.h>
#include <its_mlist.h>
#include <its_trace.h>

/*
 * timer queues
 */
static MLIST_Manager *msecTimers = NULL;
static MLIST_Manager *secTimers = NULL;
static MLIST_Manager *sec30Timers = NULL;
static MLIST_Manager *minTimers = NULL;
static MLIST_Manager *min30Timers = NULL;
static MLIST_Manager *hourTimers = NULL;

static ITS_TIME lastWaken = 0;
static ITS_TIME lastUWaken = 0;

static ITS_MUTEX __timerGuard;

/* Odd timer IDs are local only (not DSM shared) */
static ITS_SERIAL lastCallLocal = 1;

static volatile ITS_BOOLEAN requestRecoverFromPeer = ITS_FALSE;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the current time with second resolution.
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
 ****************************************************************************/
ITSDLLAPI ITS_TIME
TIMERS_Time()
{
    return time(NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the current time with microsecond resolution.
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
 ****************************************************************************/
ITSDLLAPI void
TIMERS_UTime(ITS_TIME *secs, ITS_TIME *usecs)
{
#if defined(vxworks)
    struct timespec tp;

    if(clock_gettime(CLOCK_REALTIME, &tp) == OK)
    {
         *secs = tp.tv_sec;
         *usecs = tp.tv_nsec / NSEC_PER_USEC;
    }
#elif defined(WIN32)
    /* this is the only one even remotely portable. */
    struct timeb tb;

    ftime(&tb);

    *secs = tb.time;
    *usecs = tb.millitm * USEC_PER_MILLISEC;
#else
    /* Most unices have this one. */
    struct timeval tval;

    gettimeofday(&tval, NULL);

    *secs  = tval.tv_sec;
    *usecs = tval.tv_usec;
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Put a thread to sleep for some number of seconds.
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
 ****************************************************************************/
ITSDLLAPI void
TIMERS_Sleep(int secs)
{
#if defined(unix)
    sleep(secs);
#elif defined(WIN32)
    Sleep(secs * MILLISEC_PER_SEC);
#elif defined(vxworks)
    struct timespec tim;
    tim.tv_sec= secs;
    tim.tv_nsec = 10;

    if(nanosleep(&tim, 0) == ERROR)
    {
       ITS_TRACE_ERROR(("TIMERS_Sleep: internal error in nanosleep."));
    }
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Put a thread to sleep for some number of microseconds.
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
 ****************************************************************************/
ITSDLLAPI void
TIMERS_USleep(int micros)
{
#if defined(WIN32)
    Sleep(micros / USEC_PER_MILLISEC);
#elif defined(vxworks) || defined(unix)
    struct timespec tim, rem;

    tim.tv_sec  = micros / USEC_PER_SEC;
    tim.tv_nsec = (micros % USEC_PER_SEC) * NSEC_PER_USEC;
    
    if (nanosleep(&tim, &rem) != 0)
    {
       ITS_TRACE_ERROR(("TIMERS_USleep: internal error in nanosleep."));
    }
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get a timer value from the management block.
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
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI ITS_TIME
TIMERS_GetTimerValue(TIMER_Manager *m, ITS_UINT which)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(which < m->numTimers);

    return (m->timers[which]);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set a timer value in the management block.
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
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI void
TIMERS_SetTimerValue(TIMER_Manager *m, ITS_UINT which, ITS_TIME value)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(which < m->numTimers);

    m->timers[which] = value;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize shared timer values in DSM memory 
 *
 *  Input Parameters:
 *     key  : key in table DSM_TABLE_MGMT_DATA 
 *     size : The number of timers
 *
 *  Input/Output Parameters: 
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI ITS_TIME *
TIMERS_InitSharedTimerValues(ITS_UINT key, ITS_UINT size)
{

    ITS_TIME *timers;
    ITS_INT error;

    if (DSM_LockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1) != ITS_SUCCESS)
    {
        return (NULL);
    }

    timers = (ITS_TIME *) DSM_FindNoLock(DSM_TimersFtGroupId,
                                                 DSM_TABLE_MGMT_DATA_1,
                                                 (ITS_OCTET*)&key,
                                                 sizeof(key),
                                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        timers = (ITS_TIME *)DSM_AllocNoLock(DSM_TimersFtGroupId,
                                           DSM_TABLE_MGMT_DATA_1,
                                           (ITS_OCTET *)&key,
                                           sizeof(key),
                                           sizeof(ITS_TIME)*size,
                                           &error);

        if (error != ITS_SUCCESS || timers == NULL)
        {

            DSM_UnlockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1);

            return NULL;

        }
    }
    else if (error != ITS_SUCCESS || timers == NULL)
    {
        DSM_UnlockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1);

        return NULL;
    }

    DSM_CommitNoLock(DSM_TimersFtGroupId,
                     DSM_TABLE_MGMT_DATA_1,
                     (ITS_OCTET *)&key,
                     sizeof(key),
                     timers);

    DSM_UnlockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1);


    return timers;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commit shared timer values in DSM memory 
 *
 *  Input Parameters:
 *     key  : key in table DSM_TABLE_MGMT_DATA 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI int
TIMERS_CommitSharedTimerValues(ITS_UINT key)
{

    ITS_TIME *timers;
    ITS_INT error;

    if (DSM_LockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1) != ITS_SUCCESS)
    {
        return (ITS_ENOMEM);
    }

    timers = (ITS_TIME *) DSM_FindNoLock(DSM_TimersFtGroupId,
                                                 DSM_TABLE_MGMT_DATA_1,
                                                 (ITS_OCTET*)&key,
                                                 sizeof(key),
                                                 &error);
    if (error != ITS_SUCCESS || timers == NULL)
    {
        DSM_UnlockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1);

        return error;
    }

    DSM_CommitNoLock(DSM_TimersFtGroupId,
                     DSM_TABLE_MGMT_DATA_1,
                     (ITS_OCTET *)&key,
                     sizeof(key),
                     timers);

    DSM_UnlockTable(DSM_TimersFtGroupId, DSM_TABLE_MGMT_DATA_1);

    return ITS_SUCCESS;

}

/*
 * with DSM things change a bit.
 *
 * Timers can be started on any node.
 * Timer data can be stored in DSM.
 * Timer expiry can be handled by any node?
 * Only the node that started the timer can expire it (no one
 * else knows until the initiator dies)
 * On node failure, a designated backup needs to walk the
 * timer list and start monitoring timers for it's backup?
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start an application defined timer.
 *
 *  Input Parameters:
 *      sendTo - the transport instance to send the timeout message to
 *      secs - the number of seconds to wait
 *      context - the context the timer creator wants to associate with
 *          this timer
 *      clen - the length of the timer context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer was successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The context length must be less than or equal to ITS_MAX_TIMER_CONTEXT
 *      bytes (approximately 230).
 *
 *  See Also:
 ****************************************************************************/
static int
StartTimerLow(int secs, ITS_TimerData *td)
{
    MLIST_Manager *lm = NULL;
    int ret;

    /* choose a list */
    if (secs / SECS_PER_HOUR)
    {
        lm = hourTimers;
    }
    else if (secs / THIRTY_MINS)
    {
        lm = min30Timers;
    }
    else if (secs / SECS_PER_MIN)
    {
        lm = minTimers;
    }
    else if (secs / THIRTY_SECS)
    {
        lm = sec30Timers;
    }
    else if (secs != 0)
    {
        lm = secTimers;
    }
    else
    {
        lm = msecTimers;
    }

    /* add it in */
    if ((ret = MLIST_AddTail(lm, td, sizeof(ITS_TimerData))) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TIMERS_StartTimer: couldn't add to timer queue\n"));

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start an application defined timer.
 *
 *  Input Parameters:
 *      shared - is this a node private timer or not
 *      sendTo - the transport instance to send the timeout message to
 *      secs - the number of seconds to wait
 *      context - the context the timer creator wants to associate with
 *          this timer
 *      clen - the length of the timer context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer was successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The context length must be less than or equal to ITS_MAX_TIMER_CONTEXT
 *      bytes (approximately 230).
 *
 *  See Also:
 ****************************************************************************/
static ITS_SERIAL
StartOneTimer(ITS_BOOLEAN shared, ITS_USHORT sendTo,
              int secs, int usecs,
              void *context, int clen)
{
    ITS_TimerData td, *share;
    ITS_UINT mgmtKey = DSM_MGMT_REC_TIMERS;
    volatile ITS_SERIAL retVal = 0;
    TIMER_MgmtRec *mgmt;
    int error;

    ITS_TRACE_DEBUG(("StartOneTimer: sendTo %04x timeout %d\n",
                     sendTo, secs));

    if (secs == 0 && usecs == 0)
    {
        ITS_TRACE_ERROR(("StartOneTimer: no timeout specified\n"));

        return (TIMER_BAD_SERIAL);
    }

    if (clen > ITS_MAX_TIMER_CONTEXT)
    {
        ITS_TRACE_ERROR(("StartOneTimer: context too big\n"));

        abort();
    }

    if (MUTEX_AcquireMutex(&__timerGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("StartOneTimer: failed to acquire mutex\n"));

        return (TIMER_BAD_SERIAL);
    }

    /* get the management struct */
    do
    {
        mgmt = DSM_Find(DSM_TimersFtGroupId,
                        DSM_TABLE_MGMT_DATA_1,
                        (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                        &error);

        if (error == ITS_EINUSE || error == ITS_EBADSTATE)
        {
            TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
        }
    }
    while (error == ITS_EINUSE || error == ITS_EBADSTATE);

    if (error != ITS_SUCCESS || mgmt == NULL)
    {
        MUTEX_ReleaseMutex(&__timerGuard);

        return (TIMER_BAD_SERIAL);
    }

    /* increment serial */
    mgmt->lastCall++;
    if (mgmt->lastCall == TIMER_BAD_SERIAL)
    {
        mgmt->lastCall++;
    }

    /* construct data */
    TIMERS_UTime(&td.expiry, &td.uexpiry);
    td.expiry += secs;
    td.uexpiry += usecs;
    if (td.uexpiry > USEC_PER_SEC)
    {
        td.expiry++;
        td.uexpiry %= USEC_PER_SEC;
    }
    td.serial = mgmt->lastCall;
    td.sendTo = sendTo;
    td.nodeId = DSM_GetNodeId();
    td.shared = shared;
    td.canceled = ITS_FALSE;

    ITS_C_ASSERT(clen <= ITS_MAX_TIMER_CONTEXT);

    if (clen)
    {
        memcpy(td.context, context, clen);
    }

    retVal = mgmt->lastCall;

    /* allocate shared record */
    if (shared)
    {
        if ((share = DSM_Alloc(DSM_TimersFtGroupId,
                               DSM_TABLE_TIMERS,
                               (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                               sizeof(ITS_TimerData), &error)) == NULL)
        {
            mgmt->lastCall--;

            if (mgmt->lastCall == TIMER_BAD_SERIAL)
            {
                mgmt->lastCall--;
            }

            DSM_Commit(DSM_TimersFtGroupId,
                       DSM_TABLE_MGMT_DATA_1,
                       (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                       mgmt);

            MUTEX_ReleaseMutex(&__timerGuard);

            return (TIMER_BAD_SERIAL);
        }

        /* store shared rec */
        memcpy(share, &td, sizeof(ITS_TimerData));

        if (DSM_Commit(DSM_TimersFtGroupId,
                       DSM_TABLE_TIMERS,
                       (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                       share) != ITS_SUCCESS)
        {
            mgmt->lastCall--;

            if (mgmt->lastCall == TIMER_BAD_SERIAL)
            {
                mgmt->lastCall--;
            }

            DSM_Commit(DSM_TimersFtGroupId,
                       DSM_TABLE_MGMT_DATA_1,
                       (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                       mgmt);

            MUTEX_ReleaseMutex(&__timerGuard);

            return (TIMER_BAD_SERIAL);
        }
    }

    DSM_Commit(DSM_TimersFtGroupId,
               DSM_TABLE_MGMT_DATA_1,
               (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
               mgmt);

    MUTEX_ReleaseMutex(&__timerGuard);

    if (StartTimerLow(secs, &td) != ITS_SUCCESS)
    {
        do
        {
            share = DSM_Find(DSM_TimersFtGroupId,
                             DSM_TABLE_TIMERS,
                             (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                             &error);

            if (error == ITS_EINUSE || error == ITS_EBADSTATE)
            {
                TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
            }
        }
        while (error == ITS_EINUSE || error == ITS_EBADSTATE);

        if (error == ITS_SUCCESS && share)
        {
            DSM_Free(DSM_TimersFtGroupId,
                     DSM_TABLE_TIMERS,
                     (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                     share);
        }

        return (TIMER_BAD_SERIAL);
    }

    return retVal;
}

ITSDLLAPI ITS_SERIAL
StartOneTimerLocal(ITS_BOOLEAN shared, ITS_USHORT sendTo,
              int secs, int usecs,
              void *context, int clen)

{

    if (shared)
    {
#if 0
        ITS_TimerData td, *share;
        ITS_UINT mgmtKey = DSM_MGMT_REC_TIMERS;
        volatile ITS_SERIAL retVal = 0;
        TIMER_MgmtRec *mgmt;
        int error;

        ITS_TRACE_DEBUG(("StartOneTimer: sendTo %04x timeout %d\n",
                         sendTo, secs));

        if (secs == 0 && usecs == 0)
        {
            ITS_TRACE_ERROR(("StartOneTimer: no timeout specified\n"));

            return (TIMER_BAD_SERIAL);
        }

        if (clen > ITS_MAX_TIMER_CONTEXT)
        {
            ITS_TRACE_ERROR(("StartOneTimer: context too big\n"));

            abort();
        }

        if (MUTEX_AcquireMutex(&__timerGuard) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("StartOneTimer: failed to acquire mutex\n"));

            return (TIMER_BAD_SERIAL);
        }

        /* get the management struct */
        do
        {
            mgmt = DSM_FindLocal(DSM_TcapTimersFtGroupId,
                            DSM_TABLE_MGMT_DATA,
                            (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                            &error);

            if (error == ITS_EINUSE || error == ITS_EBADSTATE)
            {
                TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
            }
        }
        while (error == ITS_EINUSE || error == ITS_EBADSTATE);

        if (error != ITS_SUCCESS || mgmt == NULL)
        {
            MUTEX_ReleaseMutex(&__timerGuard);

            return (TIMER_BAD_SERIAL);
        }

        /* increment serial */
        /* NOTE: Ricardo even TIMER IDs are shared in DSM*/
        mgmt->lastCallLocal+=2;
        if (mgmt->lastCallLocal == TIMER_BAD_SERIAL)
        {
            mgmt->lastCallLocal+=1;
        }

        /* construct data */
        TIMERS_UTime(&td.expiry, &td.uexpiry);
        td.expiry += secs;
        td.uexpiry += usecs;
        if (td.uexpiry > USEC_PER_SEC)
        {
            td.expiry++;
            td.uexpiry %= USEC_PER_SEC;
        }
        td.serial = mgmt->lastCallLocal;
        td.sendTo = sendTo;
        td.nodeId = DSM_GetNodeId();
        td.shared = shared;
        td.canceled = ITS_FALSE;

        ITS_C_ASSERT(clen <= ITS_MAX_TIMER_CONTEXT);

        if (clen)
        {
            memcpy(td.context, context, clen);
        }

        retVal = mgmt->lastCallLocal;

        /* allocate shared record */
        if (shared)
        {
            if ((share = DSM_AllocLocal(DSM_TcapTimersFtGroupId,
                                   DSM_TABLE_TIMERS,
                                   (ITS_OCTET *)&td.serial,
sizeof(ITS_SERIAL),
                                   sizeof(ITS_TimerData), &error)) == NULL)
            {
                mgmt->lastCallLocal-=2;

                if (mgmt->lastCallLocal == TIMER_BAD_SERIAL)
                {
                    mgmt->lastCallLocal-=2;
                }

                DSM_CommitLocal(DSM_TcapTimersFtGroupId,
                           DSM_TABLE_MGMT_DATA,
                           (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                           mgmt);

                MUTEX_ReleaseMutex(&__timerGuard);

                return (TIMER_BAD_SERIAL);
            }

            /* store shared rec */
            memcpy(share, &td, sizeof(ITS_TimerData));

            if (DSM_CommitLocal(DSM_TcapTimersFtGroupId,
                           DSM_TABLE_TIMERS,
                           (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                           share) != ITS_SUCCESS)
            {
                mgmt->lastCallLocal-=2;

                if (mgmt->lastCall == TIMER_BAD_SERIAL)
                {
                    mgmt->lastCallLocal-=1;
                }

                DSM_CommitLocal(DSM_TcapTimersFtGroupId,
                           DSM_TABLE_MGMT_DATA,
                           (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                           mgmt);

                MUTEX_ReleaseMutex(&__timerGuard);

                return (TIMER_BAD_SERIAL);
            }
        }

        DSM_CommitLocal(DSM_TcapTimersFtGroupId,
                   DSM_TABLE_MGMT_DATA,
                   (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                   mgmt);

        MUTEX_ReleaseMutex(&__timerGuard);

        if (StartTimerLow(secs, &td) != ITS_SUCCESS)
        {
            do
            {
                share = DSM_FindLocal(DSM_TcapTimersFtGroupId,
                                 DSM_TABLE_TIMERS,
                                 (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                                 &error);

                if (error == ITS_EINUSE || error == ITS_EBADSTATE)
                {
                    TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
                }
            }
            while (error == ITS_EINUSE || error == ITS_EBADSTATE);

            if (error == ITS_SUCCESS && share)
            {
                DSM_FreeLocal(DSM_TcapTimersFtGroupId,
                         DSM_TABLE_TIMERS,
                         (ITS_OCTET *)&td.serial, sizeof(ITS_SERIAL),
                         share);
            }

            return (TIMER_BAD_SERIAL);
        }

        return retVal;
#endif

    }
    else
    {
        MLIST_Manager *lm = NULL;
        ITS_TimerData td;
        volatile ITS_SERIAL retVal = 0;

        //ITS_TRACE_ERROR(("TIMERS_StartTimer: sendTo %04x timeout sec%d usec %d \n", sendTo, secs,usecs));

        if (secs == 0 && usecs == 0)
        {
            ITS_TRACE_ERROR(("TIMERS_StartTimer: no timeout specified\n"));

            return 0;
        }

        if (clen > ITS_MAX_TIMER_CONTEXT)
        {
            ITS_TRACE_ERROR(("TIMERS_StartTimer: context too big\n"));

            return 0;
        }

        if (MUTEX_AcquireMutex(&__timerGuard) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("TIMERS_StartTimer: failed to acquire mutex\n"));

            return (0);
        }
        lastCallLocal+=2;
        if (lastCallLocal == 0)
        {
            lastCallLocal+=1;
        }

        TIMERS_UTime(&td.expiry, &td.uexpiry);
        //ITS_TRACE_ERROR(("TIMERS_StartTimer: sendTo %04x timeout sec%d usec %d  td.expiry %d td.uexpiry %d\n", sendTo, secs,usecs,td.expiry,td.uexpiry));
        td.expiry += secs;
        td.uexpiry += usecs;
        //ITS_TRACE_ERROR(("TIMERS_StartTimer: sendTo %04x timeout sec%d usec %d  td.expiry %d td.uexpiry %d\n", sendTo, secs,usecs,td.expiry,td.uexpiry));
        if (td.uexpiry > USEC_PER_SEC)
        {
            td.expiry++;
            td.uexpiry %= USEC_PER_SEC;
        }
        td.serial = lastCallLocal;
        td.sendTo = sendTo;
        td.nodeId = DSM_GetNodeId();
        td.shared = ITS_FALSE;
        td.canceled = ITS_FALSE;
        //ITS_TRACE_ERROR(("TIMERS_StartTimer: sendTo %04x timeout sec%d usec %d  td.expiry %d td.uexpiry %d td.serial %d \n", sendTo, secs,usecs,td.expiry,td.uexpiry,td.serial));

        retVal = lastCallLocal;

        MUTEX_ReleaseMutex(&__timerGuard);

        ITS_C_ASSERT(clen <= ITS_MAX_TIMER_CONTEXT);

        if (clen)
        {
            memcpy(td.context, context, clen);
        }

        if (StartTimerLow(secs, &td) != ITS_SUCCESS)
        {
            return 0;
        }

        return retVal;
    }

}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start an application defined timer.
 *
 *  Input Parameters:
 *      sendTo - the transport instance to send the timeout message to
 *      secs - the number of seconds to wait
 *      context - the context the timer creator wants to associate with
 *          this timer
 *      clen - the length of the timer context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer was successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The context length must be less than or equal to ITS_MAX_TIMER_CONTEXT
 *      bytes (approximately 230).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_SERIAL
TIMERS_StartTimer(ITS_USHORT sendTo, int secs,
                  void *context, int clen)
{
    /*printf("*** TIMERS: Start from id:%d ***\n", sendTo);*/
    return StartOneTimerLocal(ITS_FALSE, sendTo, secs, 0, context, clen);
}
/*Note to make local timer in milli sec*/
ITSDLLAPI ITS_SERIAL
TIMERS_StartTimer_MSEC(ITS_USHORT sendTo, int usecs,
                  void *context, int clen)
{
    /*printf("*** TIMERS: Start from id:%d ***\n", sendTo);*/
    return StartOneTimerLocal(ITS_FALSE, sendTo,
                         usecs / USEC_PER_SEC, usecs % USEC_PER_SEC,
                         context, clen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start an application defined timer.
 *
 *  Input Parameters:
 *      sendTo - the transport instance to send the timeout message to
 *      secs - the number of seconds to wait
 *      context - the context the timer creator wants to associate with
 *          this timer
 *      clen - the length of the timer context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer was successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The context length must be less than or equal to ITS_MAX_TIMER_CONTEXT
 *      bytes (approximately 230).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_SERIAL
TIMERS_StartSharedTimer(ITS_USHORT sendTo, int secs,
                        void *context, int clen)
{
    return StartOneTimer(ITS_TRUE, sendTo, secs, 0, context, clen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start an application defined timer.
 *
 *  Input Parameters:
 *      sendTo - the transport instance to send the timeout message to
 *      usecs - the number of microseconds to wait
 *      context - the context the timer creator wants to associate with
 *          this timer
 *      clen - the length of the timer context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer was successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The context length must be less than or equal to ITS_MAX_TIMER_CONTEXT
 *      bytes (approximately 230).
 *      We say microseconds but the minimum granularity is 100 msecs
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_SERIAL
TIMERS_StartUTimer(ITS_USHORT sendTo, int usecs,
                   void *context, int clen)
{
   /* printf("*** TIMERS: Start UTimer from id:%d ***\n", sendTo); */
    return StartOneTimer(ITS_FALSE, sendTo,
                         usecs / USEC_PER_SEC, usecs % USEC_PER_SEC,
                         context, clen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start an application defined timer.
 *
 *  Input Parameters:
 *      sendTo - the transport instance to send the timeout message to
 *      usecs - the number of microseconds to wait
 *      context - the context the timer creator wants to associate with
 *          this timer
 *      clen - the length of the timer context
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer was successfully started, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      The context length must be less than or equal to ITS_MAX_TIMER_CONTEXT
 *      bytes (approximately 230).
 *      We say microseconds but the minimum granularity is 100 msecs
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_SERIAL
TIMERS_StartSharedUTimer(ITS_USHORT sendTo, int usecs,
                         void *context, int clen)
{
 /*   printf("*** TIMERS:  Start Shared UTimer from id:%d ***\n", sendTo); */
    return StartOneTimer(ITS_TRUE, sendTo,
                         usecs / USEC_PER_SEC, usecs % USEC_PER_SEC,
                         context, clen);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete a timer (maybe) from a list of timers.
 *
 *  Input Parameters:
 *      list - the list to delete from
 *      serial - the serial number of the timer.
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
 *
 *  See Also:
 ****************************************************************************/
static int
DeleteBySerial(MLIST_Manager *list, ITS_SERIAL which)
{
    LIST_Entry *entry, *tmp;
    ITS_TimerData *data, *share;
    int error;

    MLIST_Lock(list);
    for (entry = LIST_HEAD(list); entry != NULL; entry = tmp)
    {
        tmp = entry->next;

        data = (ITS_TimerData *)entry->data;

        if (data->serial == which)
        {
            ITS_TRACE_DEBUG(("TIMERS_CancelTimer: deleted from seconds\n"));

            MLIST_RemoveNoLock(list, entry);
            MLIST_Unlock(list);

            if (data->shared)
            {
                do
                {
                    share = DSM_Find(DSM_TimersFtGroupId,
                                     DSM_TABLE_TIMERS,
                                     (ITS_OCTET *)&which, sizeof(ITS_SERIAL),
                                     &error);

                    if (error == ITS_EINUSE || error == ITS_EBADSTATE)
                    {
                        TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
                    }
                }
                while (error == ITS_EINUSE || error == ITS_EBADSTATE);

                if (error == ITS_SUCCESS && share)
                {
                    DSM_Free(DSM_TimersFtGroupId,
                             DSM_TABLE_TIMERS,
                             (ITS_OCTET *)&which, sizeof(ITS_SERIAL),
                             share);
                }
            }

            ITS_Free(entry->data);
            ITS_Free(entry);

            return (ITS_SUCCESS);
        }
    }

    MLIST_Unlock(list);

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Stop a running timer.
 *
 *  Input Parameters:
 *      serial - the serial number of the timer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer is successfully stopped, ITS_SUCCESS is returned.
 *      Any other value indicates that the timer was not found, or
 *        an error occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TIMERS_CancelTimer(ITS_SERIAL which)
{
    ITS_TRACE_DEBUG(("TIMERS_CancelTimer: serial %08x\n", which));

    /* millisecond interval */
    if (DeleteBySerial(msecTimers, which) == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }

    /* second interval */
    if (DeleteBySerial(secTimers, which) == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }

    /* 30 second interval */
    if (DeleteBySerial(sec30Timers, which) == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }

    /* minute interval */
    if (DeleteBySerial(minTimers, which) == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }

    /* 30 minute interval */
    if (DeleteBySerial(min30Timers, which) == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }

    /* hour interval */
    if (DeleteBySerial(hourTimers, which) == ITS_SUCCESS)
    {
        return (ITS_SUCCESS);
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Stop a running timer stored in shared memory. This function 
 *      allows any node to stop the timer. 
 *
 *  Input Parameters:
 *      serial - the serial number of the timer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer is successfully stopped, ITS_SUCCESS is returned.
 *      Any other value indicates that the timer was not found, or
 *        an error occurred.
 *
 *  Notes:
 *    The node that started the timer owns it. Therefore a timer has
 *    only one owner. Only the owner can delete the timer context. When 
 *    other nodes in the shared cluster cancel a timer, only a flag bit is
 *    set to indicate that the timer is canceled. On expiry, the owner checks
 *    that flag to decide whether of not to send the timeout event.  
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TIMERS_CancelSharedTimer(ITS_SERIAL which)
{

    ITS_TimerData *share;
    ITS_USHORT nodeId;
    int error;

    ITS_TRACE_DEBUG(("TIMERS_CancelSharedTimer: serial %08x\n", which));

    do
    {
        share = DSM_Find(DSM_TimersFtGroupId,
                         DSM_TABLE_TIMERS,
                         (ITS_OCTET *)&which, sizeof(ITS_SERIAL),
                         &error);

        if (error == ITS_EINUSE || error == ITS_EBADSTATE)
        {
            TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
        }
    }
    while (error == ITS_EINUSE || error == ITS_EBADSTATE);

    if (error == ITS_SUCCESS  && share)
    {
        share->canceled = ITS_TRUE;
        nodeId = share->nodeId;   
        
        DSM_Commit(DSM_TimersFtGroupId,
                   DSM_TABLE_TIMERS,
                   (ITS_OCTET *)&which, sizeof(ITS_SERIAL),
                   share);

        if (nodeId == DSM_GetNodeId())
        {
            return TIMERS_CancelTimer(share->serial); 
        }

        return ITS_SUCCESS;
    }

    return ITS_ENOTFOUND;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete a timer (maybe) from a list of timers.
 *
 *  Input Parameters:
 *      list - the list to delete from
 *      serial - the serial number of the timer.
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
 *
 *  See Also:
 ****************************************************************************/
static void
DeleteById(MLIST_Manager *list, ITS_USHORT id)
{
    LIST_Entry *entry, *tmp;
    ITS_TimerData *data, *share;
    int error;

    MLIST_Lock(list);
    for (entry = LIST_HEAD(list); entry != NULL; entry = tmp)
    {
        tmp = entry->next;

        data = (ITS_TimerData *)entry->data;

        if (data->sendTo == id)
        {
            ITS_TRACE_DEBUG(("TIMERS_CancelTimer: deleted from seconds\n"));

            MLIST_RemoveNoLock(list, entry);
            MLIST_Unlock(list);

            if (data->shared)
            {
                do
                {
                    share = DSM_Find(DSM_TimersFtGroupId,
                                     DSM_TABLE_TIMERS,
                                     (ITS_OCTET *)&data->serial, sizeof(ITS_SERIAL),
                                     &error);

                    if (error == ITS_EINUSE || error == ITS_EBADSTATE)
                    {
                        TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
                    }
                }
                while (error == ITS_EINUSE || error == ITS_EBADSTATE);

                if (error == ITS_SUCCESS && share)
                {
                    DSM_Free(DSM_TimersFtGroupId,
                             DSM_TABLE_TIMERS,
                             (ITS_OCTET *)&data->serial, sizeof(ITS_SERIAL),
                             share);
                }
            }

            ITS_Free(entry->data);
            ITS_Free(entry);
        }
    }

    MLIST_Unlock(list);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Stop all timers started by this thread.
 *
 *  Input Parameters:
 *      id - the transport to stop
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the timer is successfully stopped, ITS_SUCCESS is returned.
 *      Any other value indicates that the timer was not found, or
 *        an error occurred.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
TIMERS_Clean(ITS_USHORT id)
{
    ITS_TRACE_DEBUG(("TIMERS_Clean: id %04x\n", id));

    /* msec timers */
    DeleteById(msecTimers, id);

    /* second interval */
    DeleteById(secTimers, id);

    /* 30 second interval */
    DeleteById(sec30Timers, id);

    /* minute interval */
    DeleteById(minTimers, id);

    /* 30 minute interval */
    DeleteById(min30Timers, id);

    /* hour interval */
    DeleteById(hourTimers, id);

    return (ITS_ENOMSG);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Callback to be registered with DSM in ClassInitialize. Purpose is to
 *      be aware when peer is leaving Timers Fault Tolerance Group and call
 *      TIMERS_RecoverFromPeer (this is done by Timers Thread through 
 *      requestRecoverFromPeer boolean). Valid on a two nodes system only.
 *
 *  Input Parameters:
 *      object      - see DSM API.
 *      userData    - see DSM API.
 *      callData    - see DSM API.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
MembershipChangeCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    DSM_MembershipChangeCbData* 
        membershipChangeCbData =
            (DSM_MembershipChangeCbData*)callData;

    /* Two nodes system only. */
    if (membershipChangeCbData->memberNodeId != DSM_GetNodeId())
    {
        if (membershipChangeCbData->
                membershipChangeType ==
                    DSM_FT_GROUP_MEMBER_LEAVE)
        {
            ITS_TRACE_DEBUG((
                "MembershipChangeCb: request recover from peer\n"));

            requestRecoverFromPeer = ITS_TRUE;
        }
        else
        {
            /* Ignore. */
        }
    }
    else 
    {
        /* Ignore. */
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Move a timer from a larger interval list to the next smaller one.
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
 ****************************************************************************/
static void
MoveFromTo(MLIST_Manager *from, MLIST_Manager *to, LIST_Entry *entry)
{
    MLIST_RemoveNoLock(from, entry);

    MLIST_AddTail(to, entry->data, entry->length);
    ITS_Free(entry->data);
    ITS_Free(entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send notification of an expired timer.
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
 ****************************************************************************/
static void
SendExpiredLow(ITS_TimerData *data)
{
    ITS_TimerData *share;
    ITS_BOOLEAN canceled = ITS_FALSE;
    int error;

    /* remove the shared entry */
    if (data->shared)
    {
        do
        {
            share = DSM_Find(DSM_TimersFtGroupId,
                             DSM_TABLE_TIMERS,
                             (ITS_OCTET *)&data->serial, sizeof(ITS_SERIAL),
                             &error);

            if (error == ITS_EINUSE || error == ITS_EBADSTATE)
            {
                TIMERS_USleep(TIMERS_DSM_RETRY * USEC_PER_MILLISEC);
            }
        }
        while (error == ITS_EINUSE || error == ITS_EBADSTATE);

        if (error == ITS_SUCCESS && share)
        {
            canceled = share->canceled;

            DSM_Free(DSM_TimersFtGroupId,
                     DSM_TABLE_TIMERS,
                     (ITS_OCTET *)&data->serial, sizeof(ITS_SERIAL),
                     share);
        }
    }

    /* build an event, if the timer is not already canceled */
    if (!canceled)
    {
        if (TIMERS_NOTIFY_PROC(itsTIMERS_Class) != NULL)
        {
            TIMERS_NOTIFY_PROC(itsTIMERS_Class)(data);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send notification of an expired timer.
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
 ****************************************************************************/
static void
SendExpired(MLIST_Manager *list, LIST_Entry *entry, ITS_TimerData *data)
{
    SendExpiredLow(data);

    MLIST_RemoveNoLock(list, entry);
    ITS_Free(entry->data);
    ITS_Free(entry);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the start time for the timer processing loop.
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
 ****************************************************************************/
ITSDLLAPI void
TIMERS_SetStartTime()
{
    TIMERS_UTime(&lastWaken, &lastUWaken);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process expired timers since the last run.
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
 ****************************************************************************/
ITSDLLAPI void
TIMERS_RunTimers()
{
    ITS_TIME interval;
    ITS_TIME thisWake, thisUWake;
    LIST_Entry *entry, *tmp;
    ITS_TimerData *data;
    int ret;
    //ITS_TRACE_ERROR(("TIMERS_RunTimers: Function called \n"));

    if (requestRecoverFromPeer)
    {
        ITS_TRACE_DEBUG(("TIMERS_RunTimers: recover timers from peer\n"));

        /* Reset. */
        requestRecoverFromPeer = ITS_FALSE;

        ret = TIMERS_RecoverFromPeer();
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "TIMERS_RunTimers: TIMERS_RecoverFromPeer failed: %d\n",
                ret));
        }
        else
        {
            ITS_TRACE_DEBUG((
                "TIMERS_RunTimers: TIMERS_RecoverFromPeer succeeded\n"));
        }
    }

    /* sleep 100 milliseconds.  This may need tuning (to say 250 or 500) */
    TIMERS_USleep(100 * USEC_PER_MILLISEC);

    TIMERS_UTime(&thisWake, &thisUWake);
    //ITS_TRACE_ERROR(("TIMERS_RunTimers: Function thisWake = %d thisUWake %d  lastWaken %d\n",thisWake,thisUWake,lastWaken));

    /* hysteresis */
    if (thisWake == lastWaken)
    {
        /* decay msec timers only in this case */
        MLIST_Lock(msecTimers);

        for (entry = LIST_HEAD(msecTimers);
             entry != NULL;
             entry = tmp)
        {
            data = (ITS_TimerData *)entry->data;

            tmp = entry->next;
          //  ITS_TRACE_ERROR(("TIMERS_RunTimers: Function data->uexpiry  = %d thisUWake %d  lastWaken %d\n",data->uexpiry,thisUWake,lastWaken));

            if(data->expiry <= thisWake)
           {
            if (data->uexpiry <= thisUWake)
            {
                //ITS_TRACE_ERROR(("TIMERS_RunTimers: Function Sending Expiry  expiry  uexpiry  serial  sendTo \n",data->expiry,data->uexpiry,data->serial,data->sendTo));
                SendExpired(msecTimers, entry, data);
            }
           }
        }

        MLIST_Unlock(msecTimers);

        return;
    }

    /* decay older, long duration timers  */
    for (interval = lastWaken + 1; interval <= thisWake; interval++)
    {
        /* decay hour timers? */
        if ((interval % SECS_PER_HOUR) == 0)
        {
            MLIST_Lock(hourTimers);

            for (entry = LIST_HEAD(hourTimers);
                 entry != NULL;
                 entry = tmp)
            {
                data = (ITS_TimerData *)entry->data;

                tmp = entry->next;

                if (data->expiry <= interval)
                {
                    if (data->uexpiry == 0)
                    {
                        SendExpired(hourTimers, entry, data);
                    }
                    else
                    {
                        MoveFromTo(hourTimers, msecTimers, entry);
                    }
                }
                else if (data->expiry - interval <= THIRTY_SECS)
                {
                    MoveFromTo(hourTimers, secTimers, entry);
                }
                else if (data->expiry - interval <= SECS_PER_MIN)
                {
                    MoveFromTo(hourTimers, sec30Timers, entry);
                }
                else if (data->expiry - interval <= THIRTY_MINS)
                {
                    MoveFromTo(hourTimers, minTimers, entry);
                }
                else if (data->expiry - interval <= SECS_PER_HOUR)
                {
                    MoveFromTo(hourTimers, min30Timers, entry);
                }
            }

            MLIST_Unlock(hourTimers);
        }

        /* decay min30 timers? */
        if ((interval % THIRTY_MINS) == 0)
        {
            MLIST_Lock(min30Timers);

            for (entry = LIST_HEAD(min30Timers);
                 entry != NULL;
                 entry = tmp)
            {
                data = (ITS_TimerData *)entry->data;

                tmp = entry->next;

                if (data->expiry <= interval)
                {
                    if (data->uexpiry == 0)
                    {
                        SendExpired(min30Timers, entry, data);
                    }
                    else
                    {
                        MoveFromTo(min30Timers, msecTimers, entry);
                    }
                }
                else if (data->expiry - interval <= THIRTY_SECS)
                {
                    MoveFromTo(min30Timers, secTimers, entry);
                }
                else if (data->expiry - interval <= SECS_PER_MIN)
                {
                    MoveFromTo(min30Timers, sec30Timers, entry);
                }
                else if (data->expiry - interval <= THIRTY_MINS)
                {
                    MoveFromTo(min30Timers, minTimers, entry);
                }
            }

            MLIST_Unlock(min30Timers);
        }

        /* decay min timers? */
        if ((interval % SECS_PER_MIN) == 0)
        {
            MLIST_Lock(minTimers);

            for (entry = LIST_HEAD(minTimers);
                 entry != NULL;
                 entry = tmp)
            {
                data = (ITS_TimerData *)entry->data;

                tmp = entry->next;

                if (data->expiry <= interval)
                {
                    if (data->uexpiry == 0)
                    {
                        SendExpired(minTimers, entry, data);
                    }
                    else
                    {
                        MoveFromTo(minTimers, msecTimers, entry);
                    }
                }
                else if (data->expiry - interval <= THIRTY_SECS)
                {
                    MoveFromTo(minTimers, secTimers, entry);
                }
                else if (data->expiry - interval <= SECS_PER_MIN)
                {
                    MoveFromTo(minTimers, sec30Timers, entry);
                }
            }

            MLIST_Unlock(minTimers);
        }

        /* decay sec30 timers? */
        if ((interval % THIRTY_SECS) == 0)
        {
            MLIST_Lock(sec30Timers);

            for (entry = LIST_HEAD(sec30Timers);
                 entry != NULL;
                 entry = tmp)
            {
                data = (ITS_TimerData *)entry->data;

                tmp = entry->next;

                if (data->expiry <= interval)
                {
                    if (data->uexpiry == 0)
                    {
                        SendExpired(sec30Timers, entry, data);
                    }
                    else
                    {
                        MoveFromTo(sec30Timers, msecTimers, entry);
                    }
                }
                else if (data->expiry - interval <= THIRTY_SECS)
                {
                    MoveFromTo(sec30Timers, secTimers, entry);
                }
            }

            MLIST_Unlock(sec30Timers);
        }

        /* decay second timers */
        MLIST_Lock(secTimers);

        for (entry = LIST_HEAD(secTimers);
             entry != NULL;
             entry = tmp)
        {
            data = (ITS_TimerData *)entry->data;

            tmp = entry->next;

            if (data->expiry <= interval)
            {
                if (data->uexpiry == 0)
                {
                    SendExpired(secTimers, entry, data);
                }
                else
                {
                    MoveFromTo(secTimers, msecTimers, entry);
                }
            }
        }

        MLIST_Unlock(secTimers);

        /* decay msec timers */
        MLIST_Lock(msecTimers);

        for (entry = LIST_HEAD(msecTimers);
             entry != NULL;
             entry = tmp)
        {
            data = (ITS_TimerData *)entry->data;

            tmp = entry->next;

            if ((data->expiry < interval) || (data->uexpiry <= thisUWake))
            {
                SendExpired(msecTimers, entry, data);
            }
        }

        MLIST_Unlock(msecTimers);
    }

    lastWaken = thisWake;
    lastUWaken = thisUWake;
}

/*
 * need this for walking DSM
 */
static LIST_Manager *recoveryList;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Function called for each timer node.
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
 *
 *  Notes:
 *
 ****************************************************************************/
static int
WalkForRemote(ITS_POINTER node, void* in, void* out)
{
    ITS_TimerData *data = (ITS_TimerData *)node;

    /*
     * walk the table, adding timers if we don't own them.
     */
    if (data->nodeId != DSM_GetNodeId())
    {
        LIST_AddTail(recoveryList, data, sizeof(ITS_TimerData));
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Recover lost timers (due to peer failure).
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
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI int
TIMERS_RecoverFromPeer()
{
    ITS_TIME curTime, curUTime;
    LIST_Entry *ent;
    int ret;

    if ((recoveryList = LIST_Create()) == NULL)
    {
        return (ITS_ENOMEM);
    }

    ret = DSM_TableIterate(
                DSM_TimersFtGroupId, 
                DSM_TABLE_TIMERS, 
                NULL, 
                NULL, 
                WalkForRemote);

    if (ret != ITS_SUCCESS)
    {
        LIST_Delete(recoveryList);

        return (ret);
    }

    TIMERS_UTime(&curTime, &curUTime);

    for (ent = LIST_HEAD(recoveryList); ent != NULL; ent = ent->next)
    {
        ITS_TimerData *data = (ITS_TimerData *)ent->data;

        /* avoid starting a timer if we don't have to.  Race avoidance. */
        if ( (data->expiry <= curTime && data->uexpiry <= curUTime) ||
             data->canceled )
        {
            SendExpiredLow(data);
        }
        else
        {
            StartTimerLow(curTime - data->expiry, data);
        }
    }

    LIST_Delete(recoveryList);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the TIMERS class.
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
 *      ITS_SUCCESS
 *
 *  Notes:
 *
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_UINT mgmtKey = DSM_MGMT_REC_TIMERS;
    TIMER_MgmtRec *mgmt;
    CALLBACK_Manager* cbManager;
    int error;
    int ret;

    ITS_TRACE_DEBUG(("TIMERS_Initialize:\n"));

    /* gate */
    if (MUTEX_CreateMutex(&__timerGuard, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("TIMERS_Initialize: failed to create mutex\n"));

        return (ITS_EBADMUTEX);
    }

    /* lists */
    if ((msecTimers = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create msec timer queue\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        return (ITS_ENOLIST);
    }

    if ((secTimers = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create sec timer queue\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        MLIST_Delete(msecTimers);

        return (ITS_ENOLIST);
    }

    if ((sec30Timers = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create sec timer queue\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        MLIST_Delete(msecTimers);
        MLIST_Delete(secTimers);

        return (ITS_ENOLIST);
    }

    if ((minTimers = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create sec timer queue\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        MLIST_Delete(msecTimers);
        MLIST_Delete(secTimers);
        MLIST_Delete(sec30Timers);

        return (ITS_ENOLIST);
    }

    if ((min30Timers = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create sec timer queue\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        MLIST_Delete(msecTimers);
        MLIST_Delete(secTimers);
        MLIST_Delete(sec30Timers);
        MLIST_Delete(minTimers);

        return (ITS_ENOLIST);
    }

    if ((hourTimers = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create sec timer queue\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        MLIST_Delete(msecTimers);
        MLIST_Delete(secTimers);
        MLIST_Delete(sec30Timers);
        MLIST_Delete(minTimers);
        MLIST_Delete(min30Timers);

        return (ITS_ENOLIST);
    }

    /* shared data */
    mgmt = DSM_Alloc(DSM_TimersFtGroupId,
                     DSM_TABLE_MGMT_DATA_1,
                     (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                     sizeof(TIMER_MgmtRec), &error);

    if (mgmt == NULL)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create mgmt rec\n"));

        MUTEX_DeleteMutex(&__timerGuard);

        MLIST_Delete(msecTimers);
        MLIST_Delete(secTimers);
        MLIST_Delete(sec30Timers);
        MLIST_Delete(minTimers);
        MLIST_Delete(min30Timers);
        MLIST_Delete(hourTimers);

        return (ITS_ENOTHREAD);
    }

    mgmt->lastCall = 0;

    DSM_Commit(DSM_TimersFtGroupId,
               DSM_TABLE_MGMT_DATA_1,
               (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
               mgmt);

    /* 
     * Register membership change callback (to recover timers from peer). 
     */
    cbManager = DSM_GetMembershipChangeCallbacks(DSM_TimersFtGroupId);
    if (cbManager == NULL)
    {
        ITS_TRACE_ERROR((
            "TIMERS_Initialize: DSM_GetMembershipChangeCallbacks failed\n"));
        return (ITS_ENOTFOUND);
    }

    ret = CALLBACK_AddCallback(cbManager, MembershipChangeCb, NULL);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TIMERS_Initialize: CALLBACK_AddCallback failed: %d\n", 
            ret));
        return (ret);
    }

    ITS_TRACE_DEBUG(("TIMERS_Initialize: Initialization successful\n"));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy the TIMERS class.
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
 *      a constant pointer to the application name
 *
 *  Notes:
 *
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    int error;
    ITS_UINT mgmtKey = DSM_MGMT_REC_TIMERS;
    TIMER_MgmtRec *mgmt;

    mgmt = DSM_Find(DSM_TimersFtGroupId,
                    DSM_TABLE_MGMT_DATA_1,
                    (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                    &error);
    if (mgmt)
    {
        DSM_Free(DSM_TimersFtGroupId,
                 DSM_TABLE_MGMT_DATA_1,
                 (ITS_OCTET *)&mgmtKey, sizeof(ITS_UINT),
                 mgmt);
    }

    MLIST_Delete(msecTimers);
    MLIST_Delete(secTimers);
    MLIST_Delete(sec30Timers);
    MLIST_Delete(minTimers);
    MLIST_Delete(min30Timers);
    MLIST_Delete(hourTimers);

    MUTEX_DeleteMutex(&__timerGuard);
}

/*
 * the class record
 */
ITSDLLAPI TIMERS_ClassRec itsTIMERS_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        TIMERS_CLASS_NAME,              /* class name */
        ClassInitialize,                /* class init */
        ClassDestroy,                   /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* timers part */
    {
        NULL
    }
};

ITSDLLAPI ITS_Class itsTIMERS_Class = (ITS_Class)&itsTIMERS_ClassRec;
