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
 *  ID: $Id: its_ipc_mutex.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:30  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 21:49:12  mmiers
 * LOG: Update project, correct return value.
 * LOG:
 * LOG: Revision 5.2  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:52  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:18  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:44  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1998/04/17 21:22:28  mmiers
 * LOG: Thread pools are working.
 * LOG:
 * LOG: Revision 1.4  1998/04/06 15:26:51  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 22:17:56  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 03:50:57  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 00:26:02  mmiers
 * LOG: Get them to build on solaris.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <its.h>
#include <its_types.h>
#include <its_mutex.h>

#ident "$Id: its_ipc_mutex.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create an IPC mutex.
 *
 *  Input Parameters:
 *      m - the mutex to initialize
 *      key - the IPC key for this mutex
 *      initState - the initial state of the mutex
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
MUTEX_CreateIPCMutex(ITS_IPC_MUTEX *m, int key, int initState)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "%d", key);

    *m = CreateMutex(NULL, initState, buf);

    if (GetLastError() != 0)
    {
        return (ITS_ENOMUTEX);
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
    CloseHandle(*m);
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
    WaitForSingleObject(*m, 0);

    if (GetLastError() != 0)
    {
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
    WaitForSingleObject(*m, INFINITE);

    if (GetLastError() != 0)
    {
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
    ReleaseMutex(*m);

    if (GetLastError() != 0)
    {
        return (ITS_EBADMUTEX);
    }

    return (ITS_SUCCESS);
}
