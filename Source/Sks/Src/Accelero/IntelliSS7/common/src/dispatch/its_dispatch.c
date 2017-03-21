/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * LOG: Revision 8.3  2005/03/21 13:51:28  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.40.2  2005/01/05 07:21:24  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.3.40.1  2004/12/16 03:30:35  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.3.36.1  2004/10/25 20:39:57  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.3  2003/02/03 16:09:32  mmiers
 * LOG: Don't include DBC or Iterative in standalone mode.
 * LOG:
 * LOG: Revision 7.2  2002/11/15 00:08:58  randresol
 * LOG: Dynamic Servers have now the option to return to the thread
 * LOG: pool when the dispatcher terminates
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/22 14:21:38  mmiers
 * LOG: Add china dispatcher
 * LOG:
 * LOG: Revision 6.2  2002/08/19 15:03:09  mmiers
 * LOG: Don't set the exit flag if you're a worker.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/11/20 17:42:01  mmiers
 * LOG: Finish DBC conversion.
 * LOG:
 * LOG: Revision 5.4  2001/11/16 16:40:35  mmiers
 * LOG: Don't block in accept.  Make the dispatchers aware of this.
 * LOG:
 * LOG: Revision 5.3  2001/11/08 23:11:03  mmiers
 * LOG: C++ needs a little help with forwards.
 * LOG:
 * LOG: Revision 5.2  2001/10/18 22:15:59  mmiers
 * LOG: Fun with C++.  Was implicitly call a constructor and cloning
 * LOG: the event instead of saying "you're an idiot".
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/14 23:56:33  mmiers
 * LOG: Remove callback frees.  This belongs in the destructor.
 * LOG:
 * LOG: Revision 4.2  2001/06/12 16:45:06  mmiers
 * LOG: Fix boolean inversion bug.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.20  2001/04/25 23:17:59  mmiers
 * LOG: Clean up a few typos in the dispatchers.
 * LOG:
 * LOG: Revision 1.19  2001/04/19 20:43:10  mmiers
 * LOG: More error callbacks for the dispatchers.  Give the user an
 * LOG: option if ITS_Initialize fails.
 * LOG:
 * LOG: Revision 1.18  2001/04/19 19:31:18  labuser
 * LOG: Change NextEventFail logic to (by default - no func given)
 * LOG: terminate the event loop.
 * LOG:
 * LOG: Revision 1.17  2001/04/18 19:59:14  mmiers
 * LOG: Add a preAccept call.
 * LOG:
 * LOG: Revision 1.16  2001/04/10 19:55:45  mmiers
 * LOG: Debug.
 * LOG:
 * LOG: Revision 1.15  2001/03/17 01:12:15  mmiers
 * LOG: Small cleanups for portability.
 * LOG:
 * LOG: Revision 1.14  2001/03/15 23:17:04  mmiers
 * LOG: Implement the pools.  TODO is Worker and WorkItem (and CPP bindings).
 * LOG: Finish tomorrow.
 * LOG:
 * LOG: Revision 1.13  2001/03/15 01:27:10  mmiers
 * LOG: Updates for portability (fsm).  I think these were required anyway,
 * LOG: but VC doesn't complain if they aren't there.  The rest is thinking
 * LOG: about the thread pools.  I think I have a handle on this if I can
 * LOG: remember it tomorrow.  The comments should help.
 * LOG:
 * LOG: Revision 1.12  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 1.11  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.10  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 1.9  2001/03/09 21:26:23  mmiers
 * LOG: Get DLL linkage working.
 * LOG:
 * LOG: Revision 1.8  2001/03/07 01:16:02  mmiers
 * LOG: Shared lib template.  Need to test to see what happens to
 * LOG: symbols in the .so that are defined in the app.
 * LOG:
 * LOG: Revision 1.7  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 1.6  2001/03/02 18:27:17  mmiers
 * LOG: Add work item.  Need to add WorkItemPool.
 * LOG:
 * LOG: Revision 1.5  2001/03/01 17:18:57  mmiers
 * LOG: Revamp for engine.  Really just adding more callbacks.
 * LOG:
 * LOG: Revision 1.4  2001/03/01 01:22:51  mmiers
 * LOG: Add trace config obj.
 * LOG:
 * LOG: Revision 1.3  2001/02/21 16:52:18  mmiers
 * LOG: Extra character
 * LOG:
 * LOG: Revision 1.2  2001/02/15 16:01:17  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 1.1  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.3  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.2  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/08/10 22:46:48  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update, dispatcher rework for generic behavior.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:30  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/10/06 15:59:59  mmiers
 * LOG:
 * LOG:
 * LOG: Add new user part for signalling network management messages.
 * LOG:
 * LOG: Revision 1.4  1999/09/24 14:25:52  mmiers
 * LOG:
 * LOG:
 * LOG: Correct a few behaviors here.
 * LOG:
 * LOG: Revision 1.3  1999/07/28 02:25:56  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize the names for the generic dispatchers.
 * LOG:
 * LOG: Revision 1.2  1999/06/28 21:47:31  skarmakar
 * LOG:
 * LOG:
 * LOG: A fix for the namespace craziness.
 * LOG:
 * LOG: Revision 1.1  1999/06/28 16:59:28  mmiers
 * LOG:
 * LOG:
 * LOG: Move the dispatchers to the support library for convenience.f
 * LOG:
 * LOG: Revision 1.2  1999/06/25 19:29:20  labuser
 * LOG:
 * LOG:
 * LOG: Fix a bunch of brain farts with generic thread dispatchers.
 * LOG: This needs revisiting, as the argument type will screw up
 * LOG: C++ code expecting a true thread function signature.
 * LOG:
 * LOG: Revision 1.1  1999/06/23 19:56:39  mmiers
 * LOG:
 * LOG:
 * LOG: Rework MTP3 for saner implementation of dual protocols.
 * LOG:
 *
 *****************************************************************************/

#include <string.h>
#include <stdlib.h>

#include <its.h>
#include <its_license.h>
#include <its_thread.h>
#include <its_worker.h>
#include <its_assertion.h>
#include <its_work_item.h>
#include <its_work_item_pool.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_ip_trans.h>
#include <its_thread_pool.h>
#include <dbc_serv.h>

#if !defined(STANDALONE)
#include <its_trace.h>
#endif

#ident "$Id: its_dispatch.c,v 1.1.1.1 2006-12-22 13:34:34 cvsadmin Exp $"

#define SIMULTANEOUS_PROTOCOL_FAMILIES

#if !defined(ANSI)
#define ANSI
#endif
#if !defined(CCITT)
#define CCITT
#endif
#if !defined(PRC)
#define PRC
#endif
#if !defined(TTC)
#define TTC
#endif

#include <ansi/mtp3.h>
#include <itu/mtp3.h>
#include <china/mtp3.h>
#include <japan/mtp3.h>

#include <its_gen_disp.h>

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI ITS_BOOLEAN
DISP_DeliverMTP3_ANSI(TPOOL_THREAD *thr, void *arg, ITS_EVENT *event)
{
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    int ret = ITS_SUCCESS;

    if (MTP3_MSG_TYPE(event) != MTP3_MSG_USER_DATA)
    {
        /* user message */
        if (cbs->DispatchUserEvent)
        {
            ret = (cbs->DispatchUserEvent)(thr, event);
        }

        return (ret != ITS_SUCCESS);
    }

    /* change source and dispatch */
    event->src = ITS_MTP3_ANSI_SRC;

    switch (event->data[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (ITS_TRUE);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            ret = (cbs->DispatchSCCPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_SCCP_ANSI_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        return (ITS_FALSE);

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            ret = (cbs->DispatchISUPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_ISUP_ANSI_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (ITS_TRUE);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (ITS_TRUE);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (ITS_TRUE);
    }

    return (ret != ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_ANSI(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    ITS_EVENT event;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    ITS_EVENT_INIT(&event, 0, 0);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            if (h)
            {
                ITS_Terminate(h);
            }

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        int ret;

        if (cbs->PreNextEvent)
        {
            if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
            {
                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event);

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = WORKER_GetNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }
        else
        {
            if ((ret = WORKER_PeekNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            if ((cbs->PostNextEvent)(thr, &event) != ITS_SUCCESS)
            {
                continue;
            }
        }

        if (event.src == ITS_MTP2_ANSI_SRC)
        {
            TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &event);
        }
        else
        {
            if ( (ITS_GET_TRANSPORT_TYPE(WORKER_MASK(work))
                                        == ITS_TRANSPORT_TQUEUE) ||
                 (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_ANSI(thr, arg, &event))
                {
                    break;
                }
            }
            else
            {
                WORKER_THREAD(work).exit = DISP_DeliverMTP3_ANSI(thr, arg, &event);
            }
        }
    }
    
    ITS_EVENT_TERM(&event);

    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI ITS_BOOLEAN
DISP_DeliverMTP3_CCITT(TPOOL_THREAD *thr, void *arg, ITS_EVENT *event)
{
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    int ret = ITS_SUCCESS;

    if (MTP3_MSG_TYPE(event) != MTP3_MSG_USER_DATA)
    {
        /* what did this come from ? */
        if (cbs->DispatchUserEvent)
        {
            ret = (cbs->DispatchUserEvent)(thr, event);
        }

        return (ret != ITS_SUCCESS);
    }

    event->src = ITS_MTP3_CCITT_SRC;

    switch (event->data[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (ITS_TRUE);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            ret = (cbs->DispatchSCCPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_SCCP_CCITT_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        return (ITS_FALSE);

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            ret = (cbs->DispatchISUPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_ISUP_CCITT_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (ITS_TRUE);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (ITS_TRUE);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (ITS_TRUE);
    }

    return (ret != ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_CCITT(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    ITS_EVENT event;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    ITS_EVENT_INIT(&event, 0, 0);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            if (h)
            {
                ITS_Terminate(h);
            }

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        int ret;

        if (cbs->PreNextEvent)
        {
            if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
            {
                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event);

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = WORKER_GetNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }
        else
        {
            if ((ret = WORKER_PeekNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            if ((cbs->PostNextEvent)(thr, &event) != ITS_SUCCESS)
            {
                continue;
            }
        }

        if (event.src == ITS_MTP2_CCITT_SRC)
        {
            TRANSPORT_PutEvent(ITS_MTP3_CCITT_SRC, &event);
        }
        else
        {
            if ( (ITS_GET_TRANSPORT_TYPE(WORKER_MASK(work))
                                        == ITS_TRANSPORT_TQUEUE) ||
                 (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_CCITT(thr, arg, &event))
                {
                    break;
                }
            }
            else
            {
                WORKER_THREAD(work).exit = DISP_DeliverMTP3_CCITT(thr, arg, &event);
            }
        }
    }
    
    ITS_EVENT_TERM(&event);

    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI ITS_BOOLEAN
DISP_DeliverMTP3_PRC(TPOOL_THREAD *thr, void *arg, ITS_EVENT *event)
{
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    int ret = ITS_SUCCESS;

    if (MTP3_MSG_TYPE(event) != MTP3_MSG_USER_DATA)
    {
        /* what did this come from ? */
        if (cbs->DispatchUserEvent)
        {
            ret = (cbs->DispatchUserEvent)(thr, event);
        }

        return (ret != ITS_SUCCESS);
    }

    event->src = ITS_MTP3_PRC_SRC;

    switch (event->data[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (ITS_TRUE);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            ret = (cbs->DispatchSCCPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_SCCP_PRC_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        return (ITS_FALSE);

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            ret = (cbs->DispatchISUPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_ISUP_PRC_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (ITS_TRUE);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (ITS_TRUE);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (ITS_TRUE);
    }

    return (ret != ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_PRC(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    ITS_EVENT event;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    ITS_EVENT_INIT(&event, 0, 0);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            if (h)
            {
                ITS_Terminate(h);
            }

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        int ret;

        if (cbs->PreNextEvent)
        {
            if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
            {
                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event);

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = WORKER_GetNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }
        else
        {
            if ((ret = WORKER_PeekNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            if ((cbs->PostNextEvent)(thr, &event) != ITS_SUCCESS)
            {
                continue;
            }
        }

        if (event.src == ITS_MTP2_PRC_SRC)
        {
            TRANSPORT_PutEvent(ITS_MTP3_PRC_SRC, &event);
        }
        else
        {
            if ( (ITS_GET_TRANSPORT_TYPE(WORKER_MASK(work))
                                        == ITS_TRANSPORT_TQUEUE) ||
                 (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_PRC(thr, arg, &event))
                {
                    break;
                }
            }
            else
            {
                WORKER_THREAD(work).exit = DISP_DeliverMTP3_PRC(thr, arg, &event);
            }
        }
    }
    
    ITS_EVENT_TERM(&event);

    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI ITS_BOOLEAN
DISP_DeliverMTP3_TTC(TPOOL_THREAD *thr, void *arg, ITS_EVENT *event)
{
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    int ret = ITS_SUCCESS;

    if (MTP3_MSG_TYPE(event) != MTP3_MSG_USER_DATA)
    {
        /* what did this come from ? */
        if (cbs->DispatchUserEvent)
        {
            ret = (cbs->DispatchUserEvent)(thr, event);
        }

        return (ret != ITS_SUCCESS);
    }

    event->src = ITS_MTP3_TTC_SRC;

    switch (event->data[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (ITS_TRUE);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            ret = (cbs->DispatchSCCPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_SCCP_TTC_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        return (ITS_FALSE);

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            ret = (cbs->DispatchISUPEvent)(thr, event);
        }
        else
        {
            ret = TRANSPORT_PutEvent(ITS_ISUP_TTC_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (ITS_TRUE);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (ITS_TRUE);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (ITS_TRUE);
    }

    return (ret != ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_TTC(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    ITS_EVENT event;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    ITS_EVENT_INIT(&event, 0, 0);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            if (h)
            {
                ITS_Terminate(h);
            }

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        int ret;

        if (cbs->PreNextEvent)
        {
            if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
            {
                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event);

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = WORKER_GetNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }
        else
        {
            if ((ret = WORKER_PeekNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            if ((cbs->PostNextEvent)(thr, &event) != ITS_SUCCESS)
            {
                continue;
            }
        }

        if (event.src == ITS_MTP2_TTC_SRC)
        {
            TRANSPORT_PutEvent(ITS_MTP3_TTC_SRC, &event);
        }
        else
        {
            if ( (ITS_GET_TRANSPORT_TYPE(WORKER_MASK(work))
                                        == ITS_TRANSPORT_TQUEUE) ||
                 (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_TTC(thr, arg, &event))
                {
                    break;
                }
            }
            else
            {
                WORKER_THREAD(work).exit = DISP_DeliverMTP3_TTC(thr, arg, &event);
            }
        }
    }
    
    ITS_EVENT_TERM(&event);

    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }
}


/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_USER(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    ITS_EVENT event;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    ITS_EVENT_INIT(&event, 0, 0);

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            if (h)
            {
                ITS_Terminate(h);
            }

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!WORKER_THREAD(work).exit)
    {
        int ret;

        if (cbs->PreNextEvent)
        {
            if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
            {
                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event);

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = WORKER_GetNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }
        else
        {
            if ((ret = WORKER_PeekNextEvent(work, &event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    if (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
                    {
                        if ((cbs->NextEventFailed)(thr, ret))
                        {
                            break;
                        }
                    }
                    else
                    {
                        WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
                    }
                }
                else
                {
                    WORKER_THREAD(work).exit = ITS_TRUE;
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            if ((cbs->PostNextEvent)(thr, &event) != ITS_SUCCESS)
            {
                continue;
            }
        }

        if (cbs->DispatchUserEvent)
        {
            if ( (ITS_GET_TRANSPORT_TYPE(WORKER_MASK(work))
                                        == ITS_TRANSPORT_TQUEUE) ||
                 (WORKER_MASK(work) & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if ((cbs->DispatchUserEvent)(thr, &event))
                {
                    break;
                }
            }
            else
            {
                WORKER_THREAD(work).exit = (cbs->DispatchUserEvent)(thr, &event);
            }
        }
    }
    
    ITS_EVENT_TERM(&event);

    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }
}


#if !defined(STANDALONE)
/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_ITERATIVE(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    /* make sure we have a pool */
    ITS_C_ASSERT(cbs->pool != NULL);

    /* make sure we're *supposed* to be here */
    ITS_C_ASSERT((WORKER_MASK(work) & (ITS_TRANSPORT_SSOCKET|
                                       ITS_TRANSPORT_SSOCKET_ITER)) ==
                 (ITS_TRANSPORT_SSOCKET|ITS_TRANSPORT_SSOCKET_ITER));

    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            ITS_Terminate(h);

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* dispatcher loop.  Accept and dispatch */
    while (!WORKER_THREAD(work).exit)
    {
        SOCKTRAN_Manager *socket = (SOCKTRAN_Manager *)WORKER_TRANSPORT(work);
        WORKER_Control *disp;

        /* get the thread */
        if (TPOOL_GetFirstAvailThread(cbs->pool,
                                      (TPOOL_THREAD **)&disp) != ITS_SUCCESS)
        {
            continue;
        }

        if (cbs->PreAccept)
        {
            if ((cbs->PreAccept)(thr, (TPOOL_THREAD *)disp) != ITS_SUCCESS)
            {
                TPOOL_ReturnToAvailThreads(cbs->pool, (TPOOL_THREAD *)disp);

                continue;
            }
        }

        /* accept a connection */
        if (SOCKTRAN_IterativeAccept(socket,
                                     WORKER_NAME(disp),
                                     WORKER_INSTANCE(disp),
                                     WORKER_MASK(disp)) == NULL)
        {
            TPOOL_ReturnToAvailThreads(cbs->pool, (TPOOL_THREAD *)disp);

            if (TRANSPORT_GetExit(WORKER_TRANSPORT(work)))
            {
                continue;
            }

            if (cbs->NextEventFailed)
            {
                WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr,
                                                                  ITS_ENOTRANSPORT);
            }
            else
            {
                WORKER_THREAD(work).exit = ITS_TRUE;
            }

            continue;
        }

        if (cbs->OnAccept)
        {
            if ((cbs->OnAccept)(thr, (TPOOL_THREAD *)disp) != ITS_SUCCESS)
            {
                TPOOL_ReturnToAvailThreads(cbs->pool, (TPOOL_THREAD *)disp);

                continue;
            }
        }

        /* dispatch 'em on this cbs */
        TPOOL_DispatchOnThread((TPOOL_THREAD *)disp, cbs->dispAccept,
                               WORKER_BACK_PTR(disp));
    }

    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }

    TPOOL_DestroyPool(cbs->pool);

    TPOOL_WaitForDestroyComplete();
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch a debug console
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - don't care
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
 ************************************************************************/
DISPDLLAPI void
DISP_Dispatch_DBC(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    DBC_Server *dbc;

    ITS_C_REQUIRE(work != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if ((dbc = (DBC_Server *)LOCKABLE_GetShared(
                        (LOCKABLE_Class)itsDBC_ServerClass)) == NULL)
    {
        /* make this an abort() to hit lusers in the face with it */
        ITS_TRACE_CRITICAL(( "DBC Server Not Accessible\n" ));
        abort();
    }

    /* make this an assert for similar reasons */
    if (cbs->PreInitialize)
    {
        if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
        {
            return;
        }
    }

    /* getting NULL here is a fatal error */
    h = ITS_Initialize(WORKER_MASK(work), WORKER_INSTANCE(work));
    
    if (cbs->PostInitialize)
    {
        if ((cbs->PostInitialize)(thr, h) != ITS_SUCCESS)
        {
            if (h)
            {
                ITS_Terminate(h);
            }

            return;
        }
    }
    else if (h == NULL)
    {
        if (cbs->PostTerminate)
        {
            (cbs->PostTerminate)(thr);
        }

        return;
    }

    /* do the DBC */
    DBC_ProcessCommandsLoop(dbc, WORKER_INSTANCE(work));

    /* clean up */
    if (cbs->PreTerminate)
    {
        (cbs->PreTerminate)(thr);
    }

    /* this is good practice */
    ITS_Terminate(h);

    if (cbs->PostTerminate)
    {
        (cbs->PostTerminate)(thr);
    }
}

#endif /* !STANDALONE */
