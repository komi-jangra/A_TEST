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
 * LOG: Revision 6.4  2002/08/22 14:21:38  mmiers
 * LOG: Add china dispatcher
 * LOG:
 * LOG: Revision 6.3  2002/08/19 15:03:09  mmiers
 * LOG: Don't set the exit flag if you're a worker.
 * LOG:
 * LOG: Revision 6.2  2002/03/08 20:36:42  mmiers
 * LOG: Add try/catch
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
 * LOG: Revision 1.16  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 1.15  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.14  2001/03/17 01:12:15  mmiers
 * LOG: Small cleanups for portability.
 * LOG:
 * LOG: Revision 1.13  2001/03/15 23:17:04  mmiers
 * LOG: Implement the pools.  TODO is Worker and WorkItem (and CPP bindings).
 * LOG: Finish tomorrow.
 * LOG:
 * LOG: Revision 1.12  2001/03/15 01:27:10  mmiers
 * LOG: Updates for portability (fsm).  I think these were required anyway,
 * LOG: but VC doesn't complain if they aren't there.  The rest is thinking
 * LOG: about the thread pools.  I think I have a handle on this if I can
 * LOG: remember it tomorrow.  The comments should help.
 * LOG:
 * LOG: Revision 1.11  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 1.10  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.9  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 1.8  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 1.7  2001/03/07 01:16:02  mmiers
 * LOG: Shared lib template.  Need to test to see what happens to
 * LOG: symbols in the .so that are defined in the app.
 * LOG:
 * LOG: Revision 1.6  2001/03/06 22:01:23  mmiers
 * LOG: New statics file for CPP globals.  Down to one SUPPORT lib.
 * LOG:
 * LOG: Revision 1.5  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 1.4  2001/03/02 18:27:17  mmiers
 * LOG: Add work item.  Need to add WorkItemPool.
 * LOG:
 * LOG: Revision 1.3  2001/03/01 17:18:57  mmiers
 * LOG: Revamp for engine.  Really just adding more callbacks.
 * LOG:
 * LOG: Revision 1.2  2001/02/15 16:01:17  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 1.1  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.2  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/08/10 22:46:48  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update, dispatcher rework for generic behavior.
 * LOG:
 * LOG: Revision 2.1  2000/06/13 19:15:58  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws exception by default.
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

#include <its++.h>
#include <its_license.h>
#include <its_thread.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <its_assertion.h>
#include <its_ip_trans.h>

#if !defined(STANDALONE)
#include <its_trace.h>
#endif

#include <dbc_serv.h>

#ident "$Id: its_dispatch++.cpp,v 1.1.1.1 2006-12-22 13:34:34 cvsadmin Exp $"

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

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - cbs rec
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      true - fatal error.  false on success.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
extern "C" bool
DISP_DeliverMTP3_ANSI_CPP(ThreadPoolThread *thr, void *arg,
                          Event &event)
{
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    int ret = ITS_SUCCESS;

    if (event.GetData()[0] != MTP3_MSG_USER_DATA)
    {
        /* user message */
        if (cbs->DispatchUserEvent)
        {
            try
            {
                ret = (cbs->DispatchUserEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }

        return (ret != ITS_SUCCESS);
    }

    /* change source and dispatch */
    event.SetSource(ITS_MTP3_ANSI_SRC);

    switch (event.GetData()[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (true);

    case MTP3_SIO_SCCP:
        /* user message */
        if (cbs->DispatchSCCPEvent)
        {
            try
            {
                ret = (cbs->DispatchSCCPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_SCCP_ANSI_SRC, event);
        }

        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        break;

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            try
            {
                ret = (cbs->DispatchISUPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_ISUP_ANSI_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (true);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (true);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (true);
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
extern "C" DISPDLLAPI void
DISP_Dispatch_ANSI_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;
    Event event;
    int ret;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());

    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            ITS_Terminate(hd);

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            ITS_Terminate(hd);

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!self->GetExit())
    {
        if (cbs->PreNextEvent)
        {
            try
            {
                if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
                {
                    break;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                break;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event.GetEvent());

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = self->GetNextEvent(event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }
        else
        {
            if ((ret = self->PeekNextEvent(event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            try
            {
                if ((cbs->PostNextEvent)(thr, event) != ITS_SUCCESS)
                {
                    continue;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                continue;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                continue;
            }
        }

        if (event.GetSource() == ITS_MTP2_ANSI_SRC)
        {
            Transport::PutEvent(ITS_MTP3_ANSI_SRC, event);
        }
        else
        {
            if (  (ITS_GET_TRANSPORT_TYPE(self->GetMask())
                                        == ITS_TRANSPORT_TQUEUE) ||
                  (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_ANSI_CPP(thr, arg, event))
                {
                    break;
                }
            }
            else
            {
                self->SetExit(DISP_DeliverMTP3_ANSI_CPP(thr, arg, event));
            }
        }
    }
    
    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - cbs rec
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      true - fatal error.  false on success.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
extern "C" DISPDLLAPI bool
DISP_DeliverMTP3_CCITT_CPP(ThreadPoolThread *thr, void *arg,
                           Event &event)
{
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    int ret = ITS_SUCCESS;
    ITS_TRACE_CRITICAL(("Enter event.GetData()[0] %d:\n",event.GetData()[0]));

    if (event.GetData()[0] != MTP3_MSG_USER_DATA)
    {
        /* user message */
        if (cbs->DispatchUserEvent)
        {
            try
            {
                ret = (cbs->DispatchUserEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }

        return (ret != ITS_SUCCESS);
    }

    event.SetSource(ITS_MTP3_CCITT_SRC);
    ITS_TRACE_CRITICAL(("TO SCCP First Byte:%d\n",event.GetData()[1] & MTP3_SIO_UP_MASK));

    switch (event.GetData()[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (true);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            try
            {
                ret = (cbs->DispatchSCCPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ITS_TRACE_CRITICAL(("TO SCCP :\n"));
            ret = Transport::PutEvent(ITS_SCCP_CCITT_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        break;

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            try
            {
                ret = (cbs->DispatchISUPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_ISUP_CCITT_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (true);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (true);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (true);
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
extern "C" DISPDLLAPI void
DISP_Dispatch_CCITT_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;
    Event event;
    int ret;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);
//    ITS_TRACE_CRITICAL(("Enter in DISP_Dispatch_CCITT_CPP \n"));

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
  //  ITS_TRACE_CRITICAL(("Enter in DISP_Dispatch_CCITT_CPP:cbs->PostInitialize \n"));

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());

    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    //ITS_TRACE_CRITICAL(("Enter in DISP_Dispatch_CCITT_CPP:cbs->cbs->PreNextEvent \n"));
    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!self->GetExit())
    {
        if (cbs->PreNextEvent)
        {
            try
            {
                if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
                {
                    break;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                break;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event.GetEvent());

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = self->GetNextEvent(event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }
        else
        {
            if ((ret = self->PeekNextEvent(event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            try
            {
                if ((cbs->PostNextEvent)(thr, event) != ITS_SUCCESS)
                {
                    continue;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                continue;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                continue;
            }
        }

  /*change for REDUNDNACY*/
       ITS_TRACE_CRITICAL(("Enter in DISP with event.GetSource()=%x:\n",event.GetSource()));
       if (event.GetSource() == ITS_SCCP_CCITT_SRC)
        {
            ITS_TRACE_CRITICAL(("Enter in DISP SCCP to MTP3:\n"));
            Transport::PutEvent(ITS_MTP3_CCITT_SRC, event);
        }
 /*end of changes */
       else
        {
          if (event.GetSource() == ITS_MTP2_CCITT_SRC)
           {
            ITS_TRACE_CRITICAL(("Enter in DISP MTP2 to MTP3:\n"));
             Transport::PutEvent(ITS_MTP3_CCITT_SRC, event);
           }
          else
          {
            if (  (ITS_GET_TRANSPORT_TYPE(self->GetMask())
                                        == ITS_TRANSPORT_TQUEUE) ||
                  (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_CCITT_CPP(thr, arg, event))
                {
                 ITS_TRACE_CRITICAL(("Enter DISP_DeliverMTP3_CCITT_CPP:\n"));
                    break;
                }
            }
            else
            {
                ITS_TRACE_CRITICAL(("Enter self->SetExit:DISP_DeliverMTP3_CCITT_CPP len %d:\n",event.GetLength()));
                if( (event.GetSource() != 0x03)&&(event.GetSource() != ITS_MTP3_CCITT_SRC))
                {        
                  ITS_TRACE_CRITICAL(("Enter self->SetExit:DISP_DeliverMTP3_CCITT_CPP len %d:\n",event.GetLength()));
                  self->SetExit(DISP_DeliverMTP3_CCITT_CPP(thr, arg, event));
                }
            }
         }
      }
    }
    ITS_TRACE_CRITICAL(("Enter in DISP_Dispatch_CCITT_CPP:cbs->cbss->PreTerminate \n"));
    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - cbs rec
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      true - fatal error.  false on success.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
extern "C" DISPDLLAPI bool
DISP_DeliverMTP3_PRC_CPP(ThreadPoolThread *thr, void *arg,
                           Event &event)
{
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    int ret = ITS_SUCCESS;

    if (event.GetData()[0] != MTP3_MSG_USER_DATA)
    {
        /* user message */
        if (cbs->DispatchUserEvent)
        {
            try
            {
                ret = (cbs->DispatchUserEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }

        return (ret != ITS_SUCCESS);
    }

    event.SetSource(ITS_MTP3_PRC_SRC);

    switch (event.GetData()[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (true);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            try
            {
                ret = (cbs->DispatchSCCPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_SCCP_PRC_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        break;

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            try
            {
                ret = (cbs->DispatchISUPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_ISUP_PRC_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (true);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (true);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (true);
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
extern "C" DISPDLLAPI void
DISP_Dispatch_PRC_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;
    Event event;
    int ret;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());

    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!self->GetExit())
    {
        if (cbs->PreNextEvent)
        {
            try
            {
                if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
                {
                    break;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                break;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event.GetEvent());

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = self->GetNextEvent(event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }
        else
        {
            if ((ret = self->PeekNextEvent(event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            try
            {
                if ((cbs->PostNextEvent)(thr, event) != ITS_SUCCESS)
                {
                    continue;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                continue;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                continue;
            }
        }

        if (event.GetSource() == ITS_MTP2_PRC_SRC)
        {
            Transport::PutEvent(ITS_MTP3_PRC_SRC, event);
        }
        else
        {
            if (  (ITS_GET_TRANSPORT_TYPE(self->GetMask())
                                        == ITS_TRANSPORT_TQUEUE) ||
                  (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_PRC_CPP(thr, arg, event))
                {
                    break;
                }
            }
            else
            {
                self->SetExit(DISP_DeliverMTP3_PRC_CPP(thr, arg, event));
            }
        }
    }
    
    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch an event to the correct stack handler
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - cbs rec
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      true - fatal error.  false on success.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
extern "C" DISPDLLAPI bool
DISP_DeliverMTP3_TTC_CPP(ThreadPoolThread *thr, void *arg,
                           Event &event)
{
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    int ret = ITS_SUCCESS;

    if (event.GetData()[0] != MTP3_MSG_USER_DATA)
    {
        /* user message */
        if (cbs->DispatchUserEvent)
        {
            try
            {
                ret = (cbs->DispatchUserEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }

        return (ret != ITS_SUCCESS);
    }

    event.SetSource(ITS_MTP3_TTC_SRC);

    switch (event.GetData()[1] & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
    case MTP3_SIO_MTP_TEST:
        /* probably don't need anything here */
        return (true);

    case MTP3_SIO_SCCP:
        if (cbs->DispatchSCCPEvent)
        {
            try
            {
                ret = (cbs->DispatchSCCPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_SCCP_TTC_SRC, event);
        }
        break;

    case MTP3_SIO_TUP:
        /* when (if) we ever do TUP */
        break;

    case MTP3_SIO_ISUP:
        if (cbs->DispatchISUPEvent)
        {
            try
            {
                ret = (cbs->DispatchISUPEvent)(thr, event);
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                ret = !ITS_SUCCESS;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                ret = !ITS_SUCCESS;
            }
        }
        else
        {
            ret = Transport::PutEvent(ITS_ISUP_TTC_SRC, event);
        }
        break;

    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
        /* eh? */
        return (true);

    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        /* maybe should go to ISUP? */
        return (true);

    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_SPARE5:
    default:
        /* Nothing to do */
        return (true);
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
extern "C" DISPDLLAPI void
DISP_Dispatch_TTC_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;
    Event event;
    int ret;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());

    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!self->GetExit())
    {
        if (cbs->PreNextEvent)
        {
            try
            {
                if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
                {
                    break;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                break;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event.GetEvent());

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = self->GetNextEvent(event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }
        else
        {
            if ((ret = self->PeekNextEvent(event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            try
            {
                if ((cbs->PostNextEvent)(thr, event) != ITS_SUCCESS)
                {
                    continue;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                continue;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                continue;
            }
        }

        if (event.GetSource() == ITS_MTP2_TTC_SRC)
        {
            Transport::PutEvent(ITS_MTP3_TTC_SRC, event);
        }
        else
        {
            if (  (ITS_GET_TRANSPORT_TYPE(self->GetMask())
                                        == ITS_TRANSPORT_TQUEUE) ||
                  (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
               )
            {
                if (DISP_DeliverMTP3_TTC_CPP(thr, arg, event))
                {
                    break;
                }
            }
            else
            {
                self->SetExit(DISP_DeliverMTP3_TTC_CPP(thr, arg, event));
            }
        }
    }
    
    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
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
extern "C" DISPDLLAPI void
DISP_Dispatch_USER_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;
    Event event;
    int ret;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());

    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    /* dispatcher loop.  Take all incoming messages and send them to SCCP. */
    while (!self->GetExit())
    {
        if (cbs->PreNextEvent)
        {
            try
            {
                if ((cbs->PreNextEvent)(thr) != ITS_SUCCESS)
                {
                    break;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                break;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                break;
            }
        }

        /* guard against silly users */
        ITS_EVENT_TERM(&event.GetEvent());

        /* Note: we could use ITS_GetNextEvent() here. */
        if (cbs->type == DISP_BLOCKING)
        {
            if ((ret = self->GetNextEvent(event)) != ITS_SUCCESS)
            {
                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }
        else
        {
            if ((ret = self->PeekNextEvent(event)) != ITS_SUCCESS)
            {
                if (ret == ITS_ENOMSG)
                {
                    continue;
                }

                if (cbs->NextEventFailed)
                {
                    try
                    {
                        if (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                        {
                            if ((cbs->NextEventFailed)(thr, ret))
                            {
                                /* return the thread to Iterative server pool */
                                break;
                            }
                        }
                        else
                        {
                            self->SetExit((cbs->NextEventFailed)(thr, ret));
                        }
                    }
                    catch (its::GenericException& ge)
                    {
                        ge.Log();

                        self->SetExit(true);
                    }
                    catch (std::exception& ex)
                    {
                        its::GenericException ge(ex.what());

                        ge.Log();

                        self->SetExit(true);
                    }
                }
                else
                {
                    self->SetExit(true);
                }

                continue;
            }
        }

        if (cbs->PostNextEvent)
        {
            try
            {
                if ((cbs->PostNextEvent)(thr, event) != ITS_SUCCESS)
                {
                    continue;
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();

                continue;
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();

                continue;
            }
        }

        if (cbs->DispatchUserEvent)
        {
            try
            {
                if (  (ITS_GET_TRANSPORT_TYPE(self->GetMask())
                                            == ITS_TRANSPORT_TQUEUE) ||
                       (self->GetMask() & ITS_TRANSPORT_SSOCKET_DYN)
                   )
                {
                    if ((cbs->DispatchUserEvent)(thr, event))
                    {
                        break;
                    }
                }
                else
                {
                    self->SetExit((cbs->DispatchUserEvent)(thr, event));
                }
            }
            catch (its::GenericException& ge)
            {
                ge.Log();
            }
            catch (std::exception& ex)
            {
                its::GenericException ge(ex.what());

                ge.Log();
            }
        }
    }
    
    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
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
extern "C" DISPDLLAPI void
DISP_Dispatch_ITERATIVE_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    /* make sure we have a pool */
    ITS_C_ASSERT(cbs->pool != NULL);

    /* make sure we're *supposed* to be here */
    ITS_C_ASSERT((self->GetMask() & (ITS_TRANSPORT_SSOCKET|
                                     ITS_TRANSPORT_SSOCKET_ITER)) ==
                 (ITS_TRANSPORT_SSOCKET|ITS_TRANSPORT_SSOCKET_ITER));

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());
    
    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    /* dispatcher loop.  Accept and dispatch */
    while (!self->GetExit())
    {
        SOCKTRAN_Manager *socket = (SOCKTRAN_Manager *)hd;
        ThreadPoolEntry disp;
        Worker *accept;

        /* get the thread */
        if (cbs->pool->GetFirstAvailThread(disp) != ITS_SUCCESS)
        {
            continue;
        }

        accept = (Worker *)disp.GetThread();

        if (cbs->PreAccept)
        {
            if ((cbs->PreAccept)(thr, disp.GetThread()) != ITS_SUCCESS)
            {
                cbs->pool->ReturnToAvailThreads(disp);

                continue;
            }
        }

        /* accept a connection */
        if (SOCKTRAN_IterativeAccept(socket,
                                     accept->GetName(),
                                     accept->GetInstance(),
                                     accept->GetMask()) == NULL)
        {
            cbs->pool->ReturnToAvailThreads(disp);

            if (TRANSPORT_GetExit((TRANSPORT_Control *)hd))
            {
                continue;
            }

            if (cbs->NextEventFailed)
            {
                try
                {
                    self->SetExit((cbs->NextEventFailed)(self,
                                                         ITS_ENOTRANSPORT));
                }
                catch (its::GenericException& ge)
                {
                    ge.Log();

                    self->SetExit(true);
                }
                catch (std::exception& ex)
                {
                    its::GenericException ge(ex.what());

                    ge.Log();

                    self->SetExit(true);
                }
            }
            else
            {
                self->SetExit(true);
            }

            continue;
        }
        if (cbs->OnAccept)
        {
            if ((cbs->OnAccept)(thr, disp.GetThread()) != ITS_SUCCESS)
            {
                cbs->pool->ReturnToAvailThreads(disp);

                continue;
            }
        }

        /* dispatch 'em on this cbs */
        cbs->pool->DispatchOnThread(disp, cbs->dispAccept, cbs);
    }

    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    delete cbs->pool;

    ThreadPool::WaitForDeletionComplete();
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch a DBC handler
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
extern "C" DISPDLLAPI void
DISP_Dispatch_DBC_CPP(ThreadPoolThread *thr, void *arg)
{
    Worker * self = (Worker *)thr;
    DISP_FuncsCPP *cbs = (DISP_FuncsCPP *)arg;
    ITS_HANDLE hd;
    DBC_Server *dbc;

    ITS_C_REQUIRE(self != NULL);
    ITS_C_REQUIRE(cbs != NULL);

    if ((dbc = (DBC_Server *)LOCKABLE_GetShared(
                        (LOCKABLE_Class)itsDBC_ServerClass)) == NULL)
    {
        /* make this an abort() to hit lusers in the face with it */
        ITS_TRACE_CRITICAL(( "DBC Server Not Accessible\n" ));
        abort();
    }

    if (cbs->PreInitialize)
    {
        try
        {
            if ((cbs->PreInitialize)(thr) != ITS_SUCCESS)
            {
                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }

    /* getting NULL here is a fatal error */
    hd = ITS_Initialize(self->GetMask(), self->GetInstance());

    if (cbs->PostInitialize)
    {
        try
        {
            if ((cbs->PostInitialize)(thr, hd) != ITS_SUCCESS)
            {
                if (hd)
                {
                    ITS_Terminate(hd);
                }

                return;
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();

            return;
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();

            return;
        }
    }
    else if (hd == NULL)
    {
        try
        {
            if (cbs->PostTerminate)
            {
                (cbs->PostTerminate)(thr);
            }
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }

        return;
    }

    /* process commands */
    DBC_ProcessCommandsLoop(dbc, self->GetInstance());

    /* clean up */
    if (cbs->PreTerminate)
    {
        try
        {
            (cbs->PreTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }

    /* this is good practice */
    ITS_Terminate(hd);

    if (cbs->PostTerminate)
    {
        try
        {
            (cbs->PostTerminate)(thr);
        }
        catch (its::GenericException& ge)
        {
            ge.Log();
        }
        catch (std::exception& ex)
        {
            its::GenericException ge(ex.what());

            ge.Log();
        }
    }
}

#endif /* !STANDALONE */
