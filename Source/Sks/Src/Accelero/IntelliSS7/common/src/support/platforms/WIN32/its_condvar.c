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
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/08/31 18:39:05  mmiers
 * LOG: Reacquire the mutex if we timeout.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/04/05 17:45:42  mmiers
 * LOG: Proper class hierarchy for threads.
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
 * LOG: Revision 3.1  2000/08/16 00:05:51  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.4  2000/08/09 00:08:26  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 1.3  2000/06/22 19:58:05  rsonak
 * LOG:
 * LOG:
 * LOG: Screwed up wait.  1) Release mutex on entry. 2) don't resignal the
 * LOG: event until *after* the mutex is held.
 * LOG:
 * LOG: Revision 1.2  2000/04/25 23:03:31  mmiers
 * LOG:
 * LOG:
 * LOG: Update C service test.
 * LOG:
 * LOG: Revision 1.1  2000/04/24 22:24:51  mmiers
 * LOG:
 * LOG:
 * LOG: Add condvar type.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_condvar.h>
#include <its_trace.h>

#ident "$Id: its_condvar.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

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
    *cv = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (*cv == NULL)
    {
        return (ITS_EBADCONDVAR);
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
CONDVAR_Delete(ITS_CONDVAR *cv)
{
    if (*cv)
    {
        CloseHandle(*cv);
    }
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
    if (!m || MUTEX_ReleaseMutex(m) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (WaitForSingleObject(*cv, INFINITE) != WAIT_OBJECT_0)
    {
        return (ITS_EBADCONDVAR);
    }

    if (m && MUTEX_AcquireMutex(m) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ResetEvent(*cv);

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
ITSDLLAPI int
CONDVAR_WaitWithTimeOut(ITS_CONDVAR *cv, ITS_MUTEX *m, ITS_UINT millisecs)
{
    int ret;

    if (!m || MUTEX_ReleaseMutex(m) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if ((ret = WaitForSingleObject(*cv, millisecs)) != WAIT_OBJECT_0)
    {
        if (ret == WAIT_TIMEOUT)
        {
            MUTEX_AcquireMutex(m);

            return (ITS_ETIMEOUT);
        }

        MUTEX_AcquireMutex(m);

        return (ITS_EBADCONDVAR);
    }

    if (m && MUTEX_AcquireMutex(m) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ResetEvent(*cv);

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
ITSDLLAPI int
CONDVAR_Signal(ITS_CONDVAR *cv)
{
    if (!SetEvent(*cv))
    {
        return (ITS_EBADCONDVAR);
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
ITSDLLAPI int
CONDVAR_Broadcast(ITS_CONDVAR *cv)
{
    if (!PulseEvent(*cv))
    {
        return (ITS_EBADCONDVAR);
    }

    return (ITS_SUCCESS);
}

