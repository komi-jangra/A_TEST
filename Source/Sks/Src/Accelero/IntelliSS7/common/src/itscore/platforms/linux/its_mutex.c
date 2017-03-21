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
 * LOG: Revision 9.1  2005/03/23 12:53:30  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:55  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/09 16:08:26  mmiers
 * LOG: Add DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:39  mmiers
 * LOG: Convert rcsid to ident
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:09  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  2000/01/27 00:05:09  mmiers
 * LOG:
 * LOG: Make core lib smarter
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:26  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:53  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/11/22 19:23:32  mmiers
 * LOG:
 * LOG:
 * LOG: Cleanup from Linux build.  Removed nested comment in iniparse,
 * LOG: cleaned up decls in gdi_trans.
 * LOG:
 * LOG: Revision 1.6  1998/11/19 02:17:31  mmiers
 * LOG: Straighten out a few potential bugs.
 * LOG:
 * LOG: Revision 1.5  1998/09/30 19:09:10  jrao
 * LOG: Mutex implementations MUST NOT include trace, or recursion problems
 * LOG: will result.
 * LOG:
 * LOG: Revision 1.4  1998/09/26 02:47:00  mmiers
 * LOG: Linux code base cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/09/23 23:13:00  jrao
 * LOG: Finish adding trace.
 * LOG:
 * LOG: Revision 1.3  1998/09/23 19:37:50  jrao
 * LOG: HPUX support fixes.
 * LOG:
 * LOG: Revision 1.2  1998/09/22 22:36:34  jrao
 * LOG: Hacks for POSIX threads (Suspend()/Resume()).  An attempt to allow the
 * LOG: user to start suspended threads.
 * LOG:
 * LOG: Revision 1.1  1998/09/22 16:01:32  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.1  1998/06/20 03:50:31  mmiers
 * LOG: Add Linux as a target.
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

    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE) != 0)
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
