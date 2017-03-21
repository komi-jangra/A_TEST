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
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:32  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/16 17:12:52  mmiers
 * LOG: Move the base timer implementation to CORE
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/05/15 14:55:16  randresol
 * LOG: Add TIMERS_InitSharedTimerValues and TIMERS_CommitSharedTimerValues
 * LOG:
 * LOG: Revision 6.5  2002/05/14 17:17:09  randresol
 * LOG: Add TIMERS_CancelSharedTimer
 * LOG:
 * LOG: Revision 6.4  2002/03/14 21:40:04  mmiers
 * LOG: Changes for OAM
 * LOG:
 * LOG: Revision 6.3  2002/03/14 18:06:58  mmiers
 * LOG: Rename for clarity.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/09/18 16:39:40  mmiers
 * LOG: Field name commit got skipped.
 * LOG:
 * LOG: Revision 5.4  2001/09/18 00:27:03  mmiers
 * LOG: Add millisecond timers.  Found a bug in TIMER_Clean that needs to
 * LOG: get to PR5.
 * LOG:
 * LOG: Revision 5.3  2001/08/31 14:23:10  mmiers
 * LOG: Brainstorming on MTP3, routing fixes.
 * LOG:
 * LOG: Revision 5.2  2001/08/24 22:18:22  vnitin
 * LOG: More Link flags and data functions
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/08/07 22:15:26  mmiers
 * LOG: Add small interval timers.
 * LOG:
 * LOG: Revision 4.4  2001/07/06 21:47:13  mmiers
 * LOG: Add shared timers.  The default is still non-shared.
 * LOG:
 * LOG: Revision 4.3  2001/07/05 22:48:01  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 4.2  2001/07/05 19:47:22  mmiers
 * LOG:
 * LOG: Start thinking about timers, continue implementing the dma
 * LOG: functionality for DSM.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.7  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.5  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.4  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.4  2000/11/10 23:07:54  mmiers
 * LOG: Some work on bugs, help Laksha out with condvar.
 * LOG:
 * LOG: Revision 3.3  2000/09/28 21:49:48  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:36  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/08/09 00:08:20  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.8  2000/06/20 23:27:29  mmiers
 * LOG:
 * LOG:
 * LOG: Add platform independent usleep.
 * LOG:
 * LOG: Revision 2.7  2000/06/13 19:15:54  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
 * LOG:
 * LOG: Revision 2.6  2000/04/27 17:42:44  mmiers
 * LOG:
 * LOG:
 * LOG: Somebody added an assertion but didn't include its_exception.h
 * LOG:
 * LOG: Revision 2.5  2000/04/27 16:41:50  mmiers
 * LOG:
 * LOG:
 * LOG: Mispelled preproc dir
 * LOG:
 * LOG: Revision 2.4  2000/03/18 21:03:33  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:37  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 02:20:48  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.1  1999/12/15 02:44:21  mmiers
 * LOG:
 * LOG:
 * LOG: Straighten out the OO stuff for ITS.  This is starting to gel, but
 * LOG: I'm awaiting feedback from Hubert.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:47  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.16  1999/10/12 16:47:32  mmiers
 * LOG:
 * LOG:
 * LOG: Remove warning on hpux.
 * LOG:
 * LOG: Revision 1.15  1999/08/30 17:53:42  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.14  1998/11/12 00:09:11  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.13  1998/11/05 15:45:58  mmiers
 * LOG: A partial fix for the timer problem.  The timers need reimplementing
 * LOG: as a hash table.
 * LOG:
 * LOG: Revision 1.12  1998/11/05 03:28:31  mmiers
 * LOG: Don't change the signature until I've thought about this a bit.
 * LOG:
 * LOG: Revision 1.11  1998/11/05 03:26:50  mmiers
 * LOG: Add serialization counters to transports.
 * LOG:
 * LOG: Revision 1.10  1998/10/15 01:28:03  mmiers
 * LOG: Add new error code for BADSTATE.
 * LOG:
 * LOG: Revision 1.9  1998/07/07 21:12:34  mmiers
 * LOG: Fixes for timers and TCAP cancels.
 * LOG:
 * LOG: Revision 1.8  1998/06/30 23:06:31  mmiers
 * LOG: Clean up the timer interface.  This hadn't been dealt with in a while.
 * LOG:
 * LOG: Revision 1.7  1998/06/01 16:35:20  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.6  1998/05/31 23:59:10  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.5  1998/05/31 22:20:14  mmiers
 * LOG: A BUNCH of updates to get the test8 (infrastructure test) to link on
 * LOG: Solaris.
 * LOG:
 * LOG: Revision 1.4  1998/04/06 15:27:13  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.3  1998/04/03 23:45:06  mmiers
 * LOG: More changes to support C++.
 * LOG:
 * LOG: Revision 1.2  1998/03/13 04:12:32  mmiers
 * LOG: Update files with latest data for TCAP implementation.  emlist represents
 * LOG: portable message queues.
 * LOG:
 * LOG: Revision 1.1  1998/03/12 03:50:55  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_TIMERS_H
#define ITS_TIMERS_H

#include <its.h>
#include <its_types.h>
#include <its_object.h>

#ident "$Id: its_timers.h,v 1.2 2008-02-06 22:28:04 bsccs2 Exp $"

/*
 * definition for a timer.  Simple, really, as we don't go subsecond.
 * the idea is that the ITS_TIMER structure appears as the data in an
 * ITS_EVENT when the timer expires.  The event source is ITS_TIMER.
 * The total context len is an arbitrary value.
 */
/* 
#define ITS_MAX_TIMER_CONTEXT                           \
    (256 - 2 * sizeof(ITS_TIME) - sizeof(ITS_SERIAL) -  \
     2 * sizeof(ITS_USHORT) - 2 * sizeof(ITS_BOOLEAN))
*/    
    
#define ITS_MAX_TIMER_CONTEXT                           \
    (512 - 2 * sizeof(ITS_TIME) - sizeof(ITS_SERIAL) -  \
     2 * sizeof(ITS_USHORT) - 2 * sizeof(ITS_BOOLEAN))

typedef struct
{
    ITS_TIME        expiry;
    ITS_TIME        uexpiry;
    ITS_SERIAL      serial;
    ITS_USHORT      sendTo;
    ITS_USHORT      nodeId;
    ITS_BOOLEAN     shared;
    ITS_BOOLEAN     canceled;
    ITS_OCTET       context[ITS_MAX_TIMER_CONTEXT];
}
ITS_TimerData;

/*
 * decay rates
 */
#define THIRTY_SECS         (30)
#define SECS_PER_MIN        (60)
#define THIRTY_MINS         (60*30)
#define SECS_PER_HOUR       (60*60)
#define ONE_SEC             (1)
#define MILLISEC_PER_SEC    (1000)
#define USEC_PER_MILLISEC   (1000)
#define USEC_PER_SEC        (1000000)
#define NSEC_PER_USEC       (1000)
#define NSEC_PER_SEC        (1000000000)

/*
 * special time value
 */
#define TIME_FOREVER        (-1)

/*
 * A failed timer returns this value.
 */
#define TIMER_BAD_SERIAL    (0)

/*
 * shared data struct
 */
typedef struct
{
    ITS_SERIAL  lastCall;
}
TIMER_MgmtRec;

/*
 * DSM retry in this milliseconds
 */
#define TIMERS_DSM_RETRY    10

/*
 * Really simple structure
 */
typedef struct
{
    char        *name;
    ITS_UINT    numTimers;
    ITS_TIME    *timers;
}
TIMER_Manager;

#define TIMERS_DECL_SUBSYS(s, p) \
    TIMER_Manager s##_Timers = { #s, sizeof(p) / sizeof(ITS_TIME), (p) }

/*.interface:TIMERS
 *****************************************************************************
 *  Interface:
 *      TIMERS_*
 *
 *  Purpose:
 *      This interface describes how the application writer can user timers
 *      with IntelliSS7.  Timers have a minimum granularity of 1 second.
 *
 *  Usage:
 *      The timer subsystem is initialized by a call to TIMERS_Initialize().
 *      This function should be called before any of the timer functions are
 *      used.
 *
 *      TIMERS_StartTimer() begins a timer.
 *
 *      TIMERS_CancelTimer() cancels a running timer.
 *
 *      Note: timers are only available in a multithreaded application.
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

ITSDLLAPI ITS_SERIAL TIMERS_StartTimer(ITS_USHORT sendTo, int secs,
                                       void *context, int clen);
ITSDLLAPI ITS_SERIAL TIMERS_StartSharedTimer(ITS_USHORT sendTo, int secs,
                                             void *context, int clen);
ITSDLLAPI ITS_SERIAL TIMERS_StartUTimer(ITS_USHORT sendTo, int usecs,
                                        void *context, int clen);
ITSDLLAPI ITS_SERIAL TIMERS_StartSharedUTimer(ITS_USHORT sendTo, int usecs,
                                              void *context, int clen);
ITSDLLAPI int TIMERS_CancelTimer(ITS_SERIAL which);
ITSDLLAPI int TIMERS_CancelSharedTimer(ITS_SERIAL which);
ITSDLLAPI int TIMERS_Clean(ITS_USHORT id);

ITSDLLAPI void TIMERS_Sleep(int secs);
ITSDLLAPI void TIMERS_USleep(int micros);

ITSDLLAPI ITS_TIME    TIMERS_Time();
ITSDLLAPI void        TIMERS_UTime(ITS_TIME *secs, ITS_TIME *usecs);

ITSDLLAPI ITS_TIME    TIMERS_GetTimerValue(TIMER_Manager *, ITS_UINT which);
ITSDLLAPI void        TIMERS_SetTimerValue(TIMER_Manager *, ITS_UINT which,
                                           ITS_TIME value);

ITSDLLAPI ITS_TIME * TIMERS_InitSharedTimerValues(ITS_UINT key, ITS_UINT size);
ITSDLLAPI int TIMERS_CommitSharedTimerValues(ITS_UINT key);

/*
 * class data
 */
typedef void (*TIMER_NotifyProc)(ITS_TimerData *);

typedef struct
{
    TIMER_NotifyProc    notifyProc;
}
TIMERS_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    TIMERS_ClassPart    timerClass;
}
TIMERS_ClassRec;

#define TIMERS_NOTIFY_PROC(cl) \
    (((TIMERS_ClassRec *)(cl))->timerClass.notifyProc)
 
#define TIMERS_CLASS_NAME   "TIMERS_CLASS"
#define STIMERS_CLASS_NAME  "SUPPORT TIMERS_CLASS"

/* 
 * interface
 */
ITSDLLAPI extern TIMERS_ClassRec    itsTIMERS_ClassRec;
ITSDLLAPI extern ITS_Class          itsTIMERS_Class;

/*
 * support implementation
 */
ITSDLLAPI extern ITS_ClassRec       itsSTIMERS_ClassRec;
ITSDLLAPI extern ITS_Class          itsSTIMERS_Class;

/*
 * basic implementation functions
 */
ITSDLLAPI void TIMERS_SetStartTime();
ITSDLLAPI void TIMERS_RunTimers();

/*
 * recovery for DSM (private)
 */
ITSDLLAPI int   TIMERS_RecoverFromPeer();

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:ITS_Timer
 *****************************************************************************
 *  Interface:
 *      ITS_Timer
 *
 *  Purpose:
 *      This interface describes how the application writer can user timers
 *      with IntelliSS7.  Timers have a minimum granularity of 1 second.
 *
 *  Usage:
 *      Note: timers are only available in a multithreaded application.
 *
 *****************************************************************************/
class ITS_Timer
{
public:
    /*.implementation:public,inline,ITS_Timer
     ************************************************************************
     *  Purpose:
     *      This method constructs a single timer object
     *
     *  Input Parameters:
     *      sendTo - the transport to send the timeout notification to
     *      secs - the duration of the timer in seconds
     *      context - a pointer to timer specific context data
     *      clen - the size of the context data.
     *
     *  Notes:
     *      This constructor can throw an exception if the timer cannot
     *      be started.
     *
     ************************************************************************/
    ITS_Timer(const ITS_USHORT sendToParam, const int secs,
              const void *contextParam, const int clen)
        : serial(0),
          duration(secs),
          context(NULL),
          contextLength(clen),
          sendTo(sendToParam),
          isRunning(false)
    {
        if (contextLength != 0)
        {
            context = new ITS_OCTET[clen];

            memcpy(context, contextParam, contextLength);
        }

        serial = TIMERS_StartTimer(sendTo, duration,
                                   context, contextLength);

        ITS_THROW_ASSERT(serial != 0);
        isRunning = true;
    }

    /*.implementation:public,inline,ITS_Timer
     ************************************************************************
     *  Purpose:
     *      This method destructs a single timer object
     *
     *  Notes:
     *      If the timer has not expired then the timer is automatically
     *      cancelled.  Specifically, if the IsTimeoutMatch() method
     *      has not been called with an Event (or IsTimeoutMatch()
     *      did not return true), the timer is cancelled.
     *
     ************************************************************************/
    virtual ~ITS_Timer()
    {
        if (isRunning)
        {
            TIMERS_CancelTimer(serial);
        }

        if (context && contextLength != 0)
        {
            delete [] static_cast<ITS_OCTET *>(context);
        }
    }

    /*.implementation:public,inline,ITS_Timer
     ************************************************************************
     *  Purpose:
     *      A predicate to see if a particular Event is a timeout notice
     *      for this timer object
     *
     *  Input Parameters:
     *      ev - the Event to check
     *
     *  Return Value:
     *      true if this event represents a timeout indication for
     *      this timer.  false otherwise.
     *
     ************************************************************************/
    bool
    IsTimeoutMatch(Event& ev)
    {
        ITS_TimerData* td = (ITS_TimerData *)ev.GetData();

        if (ev.GetLength() != sizeof(ITS_TimerData))
        {
            return false;
        }

        if (td->serial != serial || td->sendTo != sendTo)
        {
            return false;
        }

        if (contextLength != 0 &&
            memcmp(td->context, context, contextLength) != 0)
        {
            return false;
        }

        isRunning = false;

        return true;
    }

private:
    ITS_SERIAL  serial;
    int         duration;
    void        *context;
    int         contextLength;
    ITS_USHORT  sendTo;
    bool        isRunning;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_TIMERS_H */
