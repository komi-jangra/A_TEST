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
 * LOG: Revision 5.2  2001/11/07 22:53:58  mmiers
 * LOG: Add IPC mutex.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
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
 * LOG: Revision 3.1  2000/08/16 00:05:52  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:19  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:47  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/09/16 15:16:33  mmiers
 * LOG:
 * LOG:
 * LOG: Make all IPC semaphore operations not undoable on process exit.
 * LOG:
 * LOG: Revision 1.2  1999/08/13 23:25:25  mmiers
 * LOG:
 * LOG:
 * LOG: Change the semantics of the IPC semaphore a bit.
 * LOG:
 * LOG: Revision 1.1  1999/06/24 00:59:12  mmiers
 * LOG:
 * LOG:
 * LOG: Add an IPC type semaphore
 * LOG:
 * LOG: Revision 1.8  1998/09/23 22:54:20  mmiers
 * LOG: Add tracing to the windows implementation.
 * LOG:
 * LOG: Revision 1.7  1998/06/01 16:35:36  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.6  1998/05/27 22:08:09  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.5  1998/05/26 23:38:15  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.4  1998/04/06 15:26:52  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 22:17:56  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.2  1998/03/12 03:50:58  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 00:26:03  mmiers
 * LOG: Get them to build on solaris.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <limits.h>
#include <its.h>
#include <its_types.h>
#include <its_semaphore.h>
#include <its_trace.h>

#ident "$Id: its_ipc_semaphore.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

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
 *      s - the address of an ITS_IPC_SEMAPHORE object.
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
 *      SEMA_DeleteIPCSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_CreateIPCSemaphore(ITS_IPC_SEMAPHORE *s, int key)
{
    char buf[ITS_PATH_MAX];

    ITS_TRACE_DEBUG(("SEMA_CreateIPCSemaphore:\n"));

    sprintf(buf, "%d", key);

    *s = CreateSemaphore(NULL, 0, INT_MAX, buf);

    if (GetLastError() != 0)
    {
        *s = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, buf);

        if (GetLastError() != 0)
        {
            return (ITS_ENOSEMAPHORE);
        }

        return (ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys the ITS_IPC_SEMAPHORE object.
 *
 *  Input Parameters:
 *      s - the address of the ITS_IPC_SEMAPHORE object.
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
 *      SEMA_CreateIPCSemaphore()
 ****************************************************************************/
ITSDLLAPI void
SEMA_DeleteIPCSemaphore(ITS_IPC_SEMAPHORE *s)
{
    ITS_TRACE_DEBUG(("SEMA_DeleteIPCSemaphore:\n"));

    CloseHandle(*s);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function attempts to "Wait" for the semaphore in a non-blocking
 *      fashion.
 *
 *  Input Parameters:
 *      s = the address of the ITS_IPC_SEMAPHORE object to try waiting on.
 *      undo = specifies if the operation should be undone on exit
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
 *      if the caller used the "Wait" function.  The undo argument is
 *      ineffective on NT.
 *
 *  See Also:
 *      SEMA_WaitIPCSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_TryWaitIPCSemaphore(ITS_IPC_SEMAPHORE *s, ITS_BOOLEAN undo)
{
    DWORD ret;

    ITS_TRACE_DEBUG(("SEMA_TryWaitIPCSemaphore:\n"));

    ret = WaitForSingleObject(*s, 0);

    if (ret == WAIT_OBJECT_0 || ret == WAIT_ABANDONED)
    {
        return (ITS_SUCCESS);
    }
    else if (ret == WAIT_TIMEOUT)
    {
        return (ITS_EWOULDBLOCK);
    }

    return (ITS_EBADSEMAPHORE);
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
 *      undo = specifies if the operation should be undone on exit
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
 *      On success, the semaphore count has been decremented.  The undo argument
 *      is ineffective on NT.
 *
 *  See Also:
 *      SEMA_PostIPCSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_WaitIPCSemaphore(ITS_IPC_SEMAPHORE *s, ITS_BOOLEAN undo)
{
    DWORD ret;

    ITS_TRACE_DEBUG(("SEMA_WaitIPCSemaphore:\n"));

    ret = WaitForSingleObject(*s, INFINITE);

    if (ret == WAIT_OBJECT_0 || ret == WAIT_ABANDONED)
    {
        return (ITS_SUCCESS);
    }

    return (ITS_EBADSEMAPHORE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function causes the semaphore to be "Post"ed.
 *
 *  Input Parameters:
 *      s - the address of the ITS_IPC_SEMAPHORE object that is to be posted.
 *      undo - should operations done by this process be undone if the
 *          process exits.
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
 *      This function increments the semaphore count.  The undo argument
 *      is ineffective on NT.
 *
 *  See Also:
 *      SEMA_WaitIPCSemaphore()
 ****************************************************************************/
ITSDLLAPI int
SEMA_PostIPCSemaphore(ITS_IPC_SEMAPHORE *s, ITS_BOOLEAN undo)
{
    LONG last;

    ITS_TRACE_DEBUG(("SEMA_PostIPCSemaphore:\n"));

    if (ReleaseSemaphore(*s, (LONG)1, &last) == 0)
    {
        return (ITS_EBADSEMAPHORE);
    }

    return (ITS_SUCCESS);
}
