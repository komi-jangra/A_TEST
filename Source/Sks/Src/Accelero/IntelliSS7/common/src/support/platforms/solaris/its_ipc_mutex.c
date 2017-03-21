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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:31  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:45  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 21:39:00  mmiers
 * LOG: Solaris wants nonnegative semaphores
 * LOG:
 * LOG: Revision 5.5  2001/11/08 22:04:18  mmiers
 * LOG: Change initCount behavior
 * LOG:
 * LOG: Revision 5.4  2001/11/08 21:53:12  mmiers
 * LOG: Adjust return value.
 * LOG:
 * LOG: Revision 5.3  2001/11/07 23:01:41  mmiers
 * LOG: A bug fix, adding IPC mutex.
 * LOG:
 * LOG: Revision 1.1  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/11/07 22:41:38  mmiers
 * LOG: New file.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#include <its.h>
#include <its_types.h>
#include <its_semaphore.h>
#include <its_trace.h>

#ident "$Id: its_ipc_mutex.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create an IPC mutex.
 *
 *  Input Parameters:
 *      m - the mutex to initialize
 *      key - the IPC key for this mutex
 *      initState - the initial count for the mutex.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_SUCCESS - mutex created.  Any other return value indicates a
 *      processing error
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI int
MUTEX_CreateIPCMutex(ITS_IPC_MUTEX *m, int key, int initCount)
{
    struct sembuf op;

    ITS_TRACE_DEBUG(("MUTEX_CreateIPCMutex:\n"));

    if ((*m = semget(key, 1,
                     IPC_CREAT|IPC_EXCL|S_IRUSR|
                     S_IWUSR|S_IRGRP|S_IWGRP)) < 0)
    {
        if ((*m = semget(key, 1,
                         S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) < 0)
        {
            ITS_TRACE_ERROR(("MUTEX_CreateIPCMutex: semget failed: errno %d\n",
                             errno));

            return (ITS_ENOMUTEX);
        }

        return (ITS_SUCCESS);
    }

    op.sem_num = 0;
    if (initCount)
    {
        op.sem_op = 0;
    }
    else
    {
        op.sem_op = 1;
    }
    op.sem_flg = 0;

    if (semop(*m, &op, 1) != 0)
    {
        ITS_TRACE_ERROR(("MUTEX_ReleaseIPCMutex: semop failed: errno %d\n",
                         errno));

        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete an IPC mutex
 *
 *  Input Parameters:
 *      m - the mutex to delete
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
MUTEX_DeleteIPCMutex(ITS_IPC_MUTEX *m)
{
    ITS_TRACE_DEBUG(("MUTEX_DeleteIPCMutex:\n"));

    semctl(*m, 1, IPC_RMID, NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Try to acquire an IPC mutex.
 *
 *  Input Parameters:
 *      m - the mutex to try to acquire
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
MUTEX_TryAcquireIPCMutex(ITS_IPC_MUTEX *m)
{
    struct sembuf op;

    ITS_TRACE_DEBUG(("MUTEX_TryAcquireIPCMutex:\n"));

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = IPC_NOWAIT|SEM_UNDO;

    if (semop(*m, &op, 1) != 0)
    {
        if (errno != EWOULDBLOCK)
        {
            ITS_TRACE_ERROR(("MUTEX_TryAcquireIPCMutex: semop failed: "
                             "errno %d\n", errno));

            return (ITS_EBADMUTEX);
        }

        return (ITS_EWOULDBLOCK);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Acquire an IPC mutex.  If someone else owns it, you will sleep.
 *
 *  Input Parameters:
 *      m - the mutex to acquire.
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
MUTEX_AcquireIPCMutex(ITS_IPC_MUTEX *m)
{
    struct sembuf op;

    ITS_TRACE_DEBUG(("MUTEX_AcquireIPCMutex:\n"));

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;

    if (semop(*m, &op, 1) != 0)
    {
        ITS_TRACE_ERROR(("MUTEX_AcquireIPCMutex: semop failed: errno %d\n",
                         errno));

        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Release an IPC mutex.  This will wake at least one sleeper (if any
 *      exist).
 *
 *  Input Parameters:
 *      m - the mutex to release.
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
MUTEX_ReleaseIPCMutex(ITS_IPC_MUTEX *m)
{
    struct sembuf op;

    ITS_TRACE_DEBUG(("MUTEX_ReleaseIPCMutex:\n"));

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = SEM_UNDO;

    if (semop(*m, &op, 1) != 0)
    {
        ITS_TRACE_ERROR(("MUTEX_ReleaseIPCMutex: semop failed: errno %d\n",
                         errno));

        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}
