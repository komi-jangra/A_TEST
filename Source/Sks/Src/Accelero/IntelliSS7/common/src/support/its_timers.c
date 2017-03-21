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
 * LOG: Revision 1.2  2007/03/30 04:59:22  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5  2003/01/30 00:46:18  randresol
 * LOG: Set the timer class name to STIMERS_CLASS_NAME
 * LOG:
 * LOG: Revision 7.4  2003/01/16 17:12:52  mmiers
 * LOG: Move the base timer implementation to CORE
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.2  2002/11/28 18:39:04  randresol
 * LOG: Fix timers expiration problem
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.16  2002/06/23 18:12:49  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.15  2002/06/20 17:10:09  hdivoux
 * LOG: Added logic to recover timers from peer through DSM callback.
 * LOG:
 * LOG: Revision 6.14  2002/06/18 19:36:17  mmiers
 * LOG: Add ftime back in for WIN32
 * LOG:
 * LOG: Revision 6.13  2002/06/18 16:11:05  yranade
 * LOG: Somehow the TIMERS_USleep function name was removed. Get it to compile.
 * LOG:
 * LOG: Revision 6.12  2002/06/18 16:03:55  lbana
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 6.11  2002/06/18 16:02:08  lbana
 * LOG: fix compiler errors in TIMERS_UTime().
 * LOG:
 * LOG: Revision 6.10  2002/06/18 15:29:04  lbana
 * LOG: change sys call ftime to gettimeofday for performance reasons
 * LOG:
 * LOG: Revision 6.9  2002/06/13 16:59:39  mmiers
 * LOG: Fix warning, add key generation tools
 * LOG:
 * LOG: Revision 6.8  2002/05/15 14:55:20  randresol
 * LOG: Add TIMERS_InitSharedTimerValues and TIMERS_CommitSharedTimerValues
 * LOG:
 * LOG: Revision 6.7  2002/05/14 17:17:09  randresol
 * LOG: Add TIMERS_CancelSharedTimer
 * LOG:
 * LOG: Revision 6.6  2002/04/29 21:52:00  randresol
 * LOG: Unlock the timer mutex guard
 * LOG:
 * LOG: Revision 6.5  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/04/08 23:25:07  mmiers
 * LOG: timer bug.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 18:07:08  mmiers
 * LOG: Rename for clarity
 * LOG:
 * LOG: Revision 6.2  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.15  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.14  2001/12/05 00:00:27  mmiers
 * LOG: Funky timer bug.
 * LOG:
 * LOG: Revision 5.13  2001/11/21 20:54:54  hdivoux
 * LOG: Update to also take into account bad state error after a DSM Find.
 * LOG:
 * LOG: Revision 5.12  2001/11/07 19:27:00  hdivoux
 * LOG: Removed send expired call from walk for remote.
 * LOG:
 * LOG: Revision 5.11  2001/11/06 21:55:01  mmiers
 * LOG: Add needed parts for CB.  At some point when I'm feeling
 * LOG: energetic I need to split the MTP3 specific parts out of
 * LOG: link into a separate structure (and allocate that structure
 * LOG: in any MTP2 analog).
 * LOG:
 * LOG: Revision 5.10  2001/11/06 17:39:40  mmiers
 * LOG: Don't start timers when walking DSM.  Buffer and start later.
 * LOG:
 * LOG: Revision 5.9  2001/11/05 21:31:38  hdivoux
 * LOG: Change to use DSM Table Iterate instead of DSM Table Dump.
 * LOG:
 * LOG: Revision 5.8  2001/11/01 19:43:50  mmiers
 * LOG: Bug fixes Ricardo found.
 * LOG:
 * LOG: Revision 5.7  2001/10/18 21:33:40  mmiers
 * LOG: Update engine to use destinations.
 * LOG:
 * LOG: Revision 5.6  2001/09/19 01:03:26  mmiers
 * LOG: Missed an extra check.
 * LOG:
 * LOG: Revision 5.5  2001/09/18 00:37:08  mmiers
 * LOG: Add msec timers.  There are a number of vxWorks bugs that need to
 * LOG: get fixed in PR5.
 * LOG:
 * LOG: Revision 5.4  2001/08/31 14:23:10  mmiers
 * LOG: Brainstorming on MTP3, routing fixes.
 * LOG:
 * LOG: Revision 5.3  2001/08/29 17:26:54  mmiers
 * LOG: Add maskable routing.  Bug fix for SCTP clients.  Abort if
 * LOG: timer context too large.
 * LOG:
 * LOG: Revision 5.2  2001/08/24 22:17:20  vnitin
 * LOG: More Link flags and data functions
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/08/16 16:08:15  lbana
 * LOG: included timers api from vxworks
 * LOG:
 * LOG: Revision 4.5  2001/08/07 22:15:26  mmiers
 * LOG: Add small interval timers.
 * LOG:
 * LOG: Revision 4.4  2001/07/09 19:59:15  mmiers
 * LOG: Finish off shared timers.
 * LOG:
 * LOG: Revision 4.3  2001/07/06 21:47:13  mmiers
 * LOG: Add shared timers.  The default is still non-shared.
 * LOG:
 * LOG: Revision 4.2  2001/07/05 19:47:22  mmiers
 * LOG:
 * LOG: Start thinking about timers, continue implementing the dma
 * LOG: functionality for DSM.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.11  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.10  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.9  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.8  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.7  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.6  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.5  2000/12/21 01:09:38  mmiers
 * LOG: Fix range check
 * LOG:
 * LOG: Revision 3.4  2000/09/28 21:49:49  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:06:42  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 18:53:29  mmiers
 * LOG: Track down the KDD problem.  The MEMPOOL is really finding some tricky
 * LOG: bugs.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:44  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.7  2000/08/09 00:08:24  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.6  2000/06/20 23:27:29  mmiers
 * LOG:
 * LOG:
 * LOG: Add platform independent usleep.
 * LOG:
 * LOG: Revision 2.5  2000/06/02 02:05:18  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.4  2000/02/14 19:17:45  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.3  2000/02/07 17:48:04  hdivoux
 * LOG: Replaced 2 critical traces by debug traces (successful cases).
 * LOG:
 * LOG: Revision 2.2  2000/02/02 02:20:52  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.1  1999/12/15 18:23:17  mmiers
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:18  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.36  1999/03/24 23:12:42  mmiers
 * LOG:
 * LOG:
 * LOG: Add C++ interface for application class.  Fix clean routine
 * LOG: to remove mem leak.
 * LOG:
 * LOG: Revision 1.35  1999/03/24 22:45:28  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.34  1999/02/25 22:57:13  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.33  1999/02/09 21:46:16  mmiers
 * LOG:
 * LOG:
 * LOG: Normalize the thread function return type.
 * LOG: Create standard thread function exit macro.
 * LOG: Convert support library to use these.
 * LOG: Delete dead file (its_worker).
 * LOG:
 * LOG: Revision 1.32  1999/01/14 18:41:59  rsonak
 * LOG: Add in #ifdef(NDEBUG) for default catch
 * LOG:
 * LOG: Revision 1.31  1998/11/19 00:36:30  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.30  1998/11/12 00:09:15  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.29  1998/11/05 15:45:59  mmiers
 * LOG: A partial fix for the timer problem.  The timers need reimplementing
 * LOG: as a hash table.
 * LOG:
 * LOG: Revision 1.28  1998/11/05 03:29:25  mmiers
 * LOG: Don't change the signature until I've thought about this a bit.
 * LOG:
 * LOG: Revision 1.27  1998/11/05 03:27:05  mmiers
 * LOG: Add serialization counters to transports.
 * LOG:
 * LOG: Revision 1.26  1998/11/03 02:56:20  mmiers
 * LOG: Add registration/deregistration callbacks to TRANSPORT control.
 * LOG:
 * LOG: Revision 1.25  1998/10/30 21:44:16  whu
 * LOG: Fix syntax bugs.
 * LOG:
 * LOG: Revision 1.24  1998/10/30 21:39:54  whu
 * LOG: Add mutex guard around reference number allocation.
 * LOG:
 * LOG: Revision 1.23  1998/09/28 16:31:53  mmiers
 * LOG: Add meaningful information for init.
 * LOG:
 * LOG: Revision 1.22  1998/09/28 16:15:35  mmiers
 * LOG: Fix boolean.
 * LOG:
 * LOG: Revision 1.21  1998/09/22 18:51:21  mmiers
 * LOG: Finish off C-trace.  Turn debug off by default.
 * LOG:
 * LOG: Revision 1.20  1998/08/26 20:32:57  whu
 * LOG: Add exception initializer to ITS_GenericException constructor.
 * LOG:
 * LOG: Fix severe performance degrading bug in timer thread.
 * LOG:
 * LOG: Revision 1.19  1998/08/20 14:41:41  whu
 * LOG: Fix context bug with timers.
 * LOG:
 * LOG: Revision 1.18  1998/07/07 23:53:19  mmiers
 * LOG: Fix timer bug for sub 30 second timers.
 * LOG:
 * LOG: Revision 1.17  1998/07/07 21:12:34  mmiers
 * LOG: Fixes for timers and TCAP cancels.
 * LOG:
 * LOG: Revision 1.16  1998/07/01 23:34:53  mmiers
 * LOG: Modify the route selection interface slightly.
 * LOG:
 * LOG: Revision 1.15  1998/07/01 22:53:19  mmiers
 * LOG: Fix a few bugs in this stuff.  StartTimer wasn't returning a serial like
 * LOG: it should have.
 * LOG:
 * LOG: Revision 1.14  1998/06/30 23:06:32  mmiers
 * LOG: Clean up the timer interface.  This hadn't been dealt with in a while.
 * LOG:
 * LOG: Revision 1.13  1998/06/16 23:41:02  mmiers
 * LOG: Backwards compatibility fixes.
 * LOG:
 * LOG: Revision 1.12  1998/06/09 21:00:32  whu
 * LOG: Make thread pool threads suspended on creation.  This removes a race
 * LOG: condition where the worker thread has not reached the suspended state
 * LOG: before the main thread dispatches work to it; in this case, the worker
 * LOG: suspends *before* the work is started, resulting in a wasted dispatch.
 * LOG:
 * LOG: Also fixed a bug where we were adding and removing threads from the
 * LOG: avail list twice.  Had to add a new parameter to the THREAD interface;
 * LOG: document this.
 * LOG:
 * LOG: Revision 1.11  1998/06/01 16:35:38  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.10  1998/05/31 22:20:15  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.9  1998/05/29 00:32:58  mmiers
 * LOG: More documentation and bug fixes.
 * LOG:
 * LOG: Revision 1.8  1998/04/29 22:43:49  mmiers
 * LOG: Make ITS_TCAP_SRC modification.
 * LOG:
 * LOG: Revision 1.7  1998/04/24 16:20:23  mmiers
 * LOG: Buffer management for C lists.
 * LOG:
 * LOG: Revision 1.6  1998/04/16 15:59:01  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  1998/04/09 23:43:44  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.4  1998/04/06 15:26:53  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 22:17:57  mmiers
 * LOG: More infrastructure.  Add C++ classes for threads, mutexes, and semaphores.
 * LOG: Still have to do timers, lists, mlists, and emlists.
 * LOG:
 * LOG: Revision 1.2  1998/03/13 04:11:48  mmiers
 * LOG: Update files with latest code.  emlist represents portable message queues.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 03:51:21  mmiers
 * LOG: Add the timer task.
 *
 ****************************************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/*
 * regular includes
 */
#include <its.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_transports.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_dsm.h>

#ident "$Id: its_timers.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

static ITS_THREAD timerThread;

static ITS_BOOLEAN running = ITS_TRUE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Send a notification of an expired timer
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
NotifyProc(ITS_TimerData *data)
{
    ITS_EVENT ev;

    ev.len = sizeof(ITS_TimerData);
    ev.src = ITS_TIMER_SRC;
    ev.data = ITS_Malloc(sizeof(ITS_TimerData));
    if (ev.data == NULL)
    {
        ITS_TRACE_ERROR(("Out of memory building timeout\n"));

        return;
    }

    memcpy(ev.data, data, sizeof(ITS_TimerData));

    ITS_TRACE_DEBUG(("SendExpired: sending timeout for hourly timer\n"));

    /* send it */
    TRANSPORT_PutEvent(data->sendTo, &ev);
}

/*.implementation:static
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
 ****************************************************************************/
static THREAD_RET_TYPE
ITS_TimerThread(void *arg)
{
    TIMERS_SetStartTime();

    ITS_TRACE_DEBUG(("TIMERS_Main: timer thread starting\n"));

    while (running)
    {
        TIMERS_RunTimers();
    }

    /* NOTREACHED */
    THREAD_NORMAL_EXIT;
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
    /* Set the notify proc */
    TIMERS_NOTIFY_PROC(itsTIMERS_Class) = NotifyProc;

    /* launch thread */
    if (THREAD_CreateThread(&timerThread, 0, ITS_TimerThread,
                            NULL, ITS_TRUE) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TIMERS_Initialize: couldn't create timer thread\n"));

        return (ITS_ENOTHREAD);
    }

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
    void *status;

    ITS_TRACE_DEBUG(("TIMERS_Terminate\n"));

    TIMERS_NOTIFY_PROC(itsTIMERS_Class) = NULL;

    running = ITS_FALSE;

    THREAD_WaitForThread(&timerThread, &status);

    THREAD_DeleteThread(&timerThread);
}

/*
 * the class record
 */
ITSDLLAPI ITS_ClassRec itsSTIMERS_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        STIMERS_CLASS_NAME,             /* class name */
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
    }
};

ITSDLLAPI ITS_Class itsSTIMERS_Class = (ITS_Class)&itsSTIMERS_ClassRec;

