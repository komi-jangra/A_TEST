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
 * LOG: Revision 1.2  2007/03/30 04:59:10  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/20 19:18:17  mmiers
 * LOG: Finish up HMI
 * LOG:
 * LOG: Revision 4.2  2001/05/16 20:10:53  mmiers
 * LOG: Locating bottlenecks.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2001/01/17 16:03:20  mmiers
 * LOG: Symbol collision on vxWorks.
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/11/10 23:07:55  mmiers
 * LOG: Some work on bugs, help Laksha out with condvar.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:39  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/08/09 00:08:24  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 1.3  2000/04/27 17:31:17  mmiers
 * LOG:
 * LOG:
 * LOG: Spell the function name correctly
 * LOG:
 * LOG: Revision 1.2  2000/04/25 23:30:02  mmiers
 * LOG:
 * LOG:
 * LOG: Platform cleanup.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:11  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:56  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/06/28 23:45:26  skarmakar
 * LOG:
 * LOG:
 * LOG: More work on portability.
 * LOG:
 * LOG: Revision 1.2  1999/02/25 22:57:11  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.1  1998/10/01 00:01:54  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.5  1998/09/30 20:41:49  jrao
 * LOG: Remove printfs
 * LOG:
 * LOG: Revision 1.4  1998/09/30 20:33:28  jrao
 * LOG: Fix a number of release bugs with pthread_cond_t(s).
 * LOG:
 * LOG: Revision 1.5  1998/09/30 17:58:38  jrao
 * LOG: Bug in in-process semaphore.
 * LOG:
 * LOG: Revision 1.4  1998/09/30 17:20:18  jrao
 * LOG: Update for HPUX.  Convert from UNIX semaphores to condition variables.
 * LOG:
 * LOG: Revision 1.3  1998/09/23 22:04:29  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.2  1998/09/22 16:01:33  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.1  1998/09/21 17:26:23  jrao
 * LOG: New addition.
 * LOG:
 * LOG: Revision 1.2  1998/06/30 01:50:09  mmiers
 * LOG: IS634: Clean up some warnings from a GCC build (ANSI "for" scope rule).
 * LOG: The rest is cleanup.  We can add Linux as a platform, but it is not
 * LOG: safe multithreaded (yet).
 * LOG:
 * LOG: Revision 1.1  1998/06/20 03:50:35  mmiers
 * LOG: Add Linux as a target.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>

#include <its.h>
#include <its_types.h>
#include <its_semaphore.h>
#include <its_trace.h>

#ident "$Id: its_semaphore.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates a counting semaphore, with the initial count
 *      of the semaphore set to the "initState" value.
 *
 *  Input Parameters:
 *      initState = the initial state (or count) of the semaphore.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      s - the address of an ITS_SEMAPHORE object.
 *
 *  Return Value:
 *      If the semaphore was created successfully, ITS_SUCCESS is returned.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      An initState that is zero indicates that the semaphore is created
 *      as not "Post"ed.  Any other value indicates that the semaphore has
 *      been created in the "Post"ed state, with the semaphore count set
 *      to initState.
 *
 *  See Also:
 *      SEMA_DeleteSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_CreateSemaphore(ITS_SEMAPHORE *s, int initCount)
{
    ITS_TRACE_DEBUG(("SEMA_CreateSemaphore:\n"));

    /* create the mutex */
    if (MUTEX_CreateMutex(&s->semGuard, 0) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SEMA_CreateSemaphore: can't create cond mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (CONDVAR_Create(&s->semCondition) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SEMA_CreateSemaphore: can't init condvar\n"));

        return (ITS_EBADCONDVAR);
    }

    s->semCounter = initCount;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys the ITS_SEMAPHORE object.
 *
 *  Input Parameters:
 *      s - the address of the ITS_SEMAPHORE object.
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
 *      The result of destroying a semaphore that has entities "Wait"ing on
 *      it is undefined.
 *
 *  See Also:
 *      SEMA_CreateSemaphore()
 ****************************************************************************/
ITSDLLAPI void
SEMA_DeleteSemaphore(ITS_SEMAPHORE *m)
{
    ITS_TRACE_DEBUG(("SEMA_DeleteSemaphore:\n"));

    MUTEX_DeleteMutex(&m->semGuard);

    CONDVAR_Delete(&m->semCondition);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function attempts to "Wait" for the semaphore in a non-blocking
 *      fashion.
 *
 *  Input Parameters:
 *      s = the address of the ITS_SEMAPHORE object to try waiting on.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the semaphore was posted, ITS_SUCCESS is returned.
 *      Any other return value indicates that the semaphore was not posted,
 *          or that an IntelliSS7 error occurred.
 *
 *  Notes:
 *      This function reduces the semaphore count when successful, just as
 *      if the caller used the "Wait" function.
 *
 *  See Also:
 *      SEMA_WaitSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_TryWaitSemaphore(ITS_SEMAPHORE *s)
{
    ITS_TRACE_DEBUG(("SEMA_TryWaitSemaphore:\n"));

    if (MUTEX_AcquireMutex(&s->semGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SEMA_TryWaitSemaphore: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    if (s->semCounter == 0)
    {
        MUTEX_ReleaseMutex(&s->semGuard);

        return (ITS_EWOULDBLOCK);
    }

    s->semCounter--;

    MUTEX_ReleaseMutex(&s->semGuard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function "Wait"s for the semaphore to become posted.  If the
 *      semaphore is not posted when this function is called, the caller
 *      will block.
 *
 *  Input Parameters:
 *      s - the address of the semaphore to "Wait" for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Once the semaphore becomes "Post"ed, ITS_SUCCESS is returned.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      On success, the semaphore count has been decremented.
 *
 *  See Also:
 *      SEMA_PostSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_WaitSemaphore(ITS_SEMAPHORE *s)
{
    ITS_TRACE_DEBUG(("SEMA_WaitSemaphore:\n"));

    if (MUTEX_AcquireMutex(&s->semGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SEMA_WaitSemaphore: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    while (s->semCounter == 0)
    {
        if (CONDVAR_Wait(&s->semCondition, &s->semGuard) != 0)
        {
            ITS_TRACE_ERROR(("SEMA_WaitSemaphore: can't wait condition\n"));

            MUTEX_ReleaseMutex(&s->semGuard);

            return (ITS_EBADSEMAPHORE);
        }
    }

    s->semCounter--;

    MUTEX_ReleaseMutex(&s->semGuard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function "Wait"s for the semaphore to become posted.  If the
 *      semaphore is not posted when this function is called, the caller
 *      will block until the timeout expires.
 *
 *  Input Parameters:
 *      s - the address of the semaphore to "Wait" for.
 *      millisecs - the number of millisecs to wait.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Once the semaphore becomes "Post"ed, ITS_SUCCESS is returned.
 *      Any other value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      On success, the semaphore count has been decremented.
 *
 *  See Also:
 *      SEMA_PostSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_WaitSemaphoreWithTimeOut(ITS_SEMAPHORE *s, ITS_UINT millisecs)
{
    int ret;

    ITS_TRACE_DEBUG(("SEMA_WaitSemaphore:\n"));

    if (MUTEX_AcquireMutex(&s->semGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SEMA_WaitSemaphore: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    while (s->semCounter == 0)
    {
        if ((ret = CONDVAR_WaitWithTimeOut(&s->semCondition,
                                           &s->semGuard,
                                           millisecs)) != ITS_SUCCESS)
        {
            if (ret == ITS_ETIMEOUT)
            {
                MUTEX_ReleaseMutex(&s->semGuard);

                return (ret);
            }

            ITS_TRACE_ERROR(("SEMA_WaitSemaphore: can't wait condition\n"));

            MUTEX_ReleaseMutex(&s->semGuard);

            return (ITS_EBADSEMAPHORE);
        }
    }

    s->semCounter--;

    MUTEX_ReleaseMutex(&s->semGuard);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function causes the semaphore to be "Post"ed.
 *
 *  Input Parameters:
 *      s - the address of the ITS_SEMAPHORE object that is to be posted.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On successful "Post"ing, ITS_SUCCESS is returned.
 *      Any other value indicates that an IntelliSS7 error has occurred.
 *
 *  Notes:
 *      This function increments the semaphore count.
 *
 *  See Also:
 *      SEMA_WaitSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_PostSemaphore(ITS_SEMAPHORE *s)
{
    ITS_TRACE_DEBUG(("SEMA_PostSemaphore:\n"));

    if (MUTEX_AcquireMutex(&s->semGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SEMA_WaitSemaphore: can't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }

    s->semCounter++;

    CONDVAR_Signal(&s->semCondition);

    MUTEX_ReleaseMutex(&s->semGuard);

    return (ITS_SUCCESS);
}
