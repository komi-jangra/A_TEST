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
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:34:38  lbana
 * LOG: Added for montavista distro
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_mutex.h>
#include <its_trace.h>

#ident "$Id: its_mutex.c,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

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
    pthread_mutexattr_t attr;

    if (pthread_mutexattr_init(&attr) != 0)
    {
        return (ITS_ENOMUTEX);
    }

    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP) != 0)
    {
        return (ITS_ENOMUTEX);
    }

    if (pthread_mutex_init(m, &attr) != 0)
    {
        return (ITS_ENOMUTEX);
    }

    if (initState)
    {
        if (pthread_mutex_lock(m) != 0)
        {
            return (ITS_EBADMUTEX);
        }
    }

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
    pthread_mutex_destroy(m);
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
    if (pthread_mutex_trylock(m) != 0)
    {
        return (ITS_EWOULDBLOCK);
    }

    return (ITS_SUCCESS);
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
    if (pthread_mutex_lock(m) != 0)
    {
        return (ITS_EBADMUTEX);
    }

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
    if (pthread_mutex_unlock(m) != 0)
    {
        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}
