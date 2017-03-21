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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:20  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:08  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:54:44  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:34  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:28  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:52  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/08/22 14:23:07  mmiers
 * LOG: Add china dispatchers
 * LOG:
 * LOG: Revision 6.2  2002/03/08 20:36:42  mmiers
 * LOG: Add try/catch
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7  2001/12/28 18:43:21  mmiers
 * LOG: A few mistakes to fix.
 * LOG:
 * LOG: Revision 5.6  2001/11/16 16:40:35  mmiers
 * LOG: Don't block in accept.  Make the dispatchers aware of this.
 * LOG:
 * LOG: Revision 5.5  2001/11/08 23:11:03  mmiers
 * LOG: C++ needs a little help with forwards.
 * LOG:
 * LOG: Revision 5.4  2001/10/18 22:15:59  mmiers
 * LOG: Fun with C++.  Was implicitly call a constructor and cloning
 * LOG: the event instead of saying "you're an idiot".
 * LOG:
 * LOG: Revision 5.3  2001/10/18 22:06:42  mmiers
 * LOG: Add MTP2 capability to the SS7 dispatchers.
 * LOG:
 * LOG: Revision 5.2  2001/09/21 22:58:57  mmiers
 * LOG: Add handlers for SS7 ISUP
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:04  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.11  2001/04/19 20:43:10  mmiers
 * LOG: More error callbacks for the dispatchers.  Give the user an
 * LOG: option if ITS_Initialize fails.
 * LOG:
 * LOG: Revision 1.10  2001/04/19 19:31:18  labuser
 * LOG: Change NextEventFail logic to (by default - no func given)
 * LOG: terminate the event loop.
 * LOG:
 * LOG: Revision 1.9  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 1.8  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.7  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 1.6  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 1.5  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 1.4  2001/03/07 01:16:02  mmiers
 * LOG: Shared lib template.  Need to test to see what happens to
 * LOG: symbols in the .so that are defined in the app.
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
 * LOG: Revision 3.1  2000/08/16 00:05:24  mmiers
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
 * LOG: Revision 2.0  1999/12/03 23:27:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/09/24 14:25:51  mmiers
 * LOG:
 * LOG:
 * LOG: Correct a few behaviors here.
 * LOG:
 * LOG: Revision 1.2  1999/08/05 14:54:23  labuser
 * LOG:
 * LOG:
 * LOG: Make these files independent of the global protocol setting.
 * LOG:
 * LOG: Revision 1.1  1999/07/27 23:25:02  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more generic dispatchers, this time for an integrated stack
 * LOG: in the application.  Add a method to determine if this is the last
 * LOG: component in a C++ TCAP_Component.
 * LOG:
 *
 ****************************************************************************/

/*
 * dispatcher for generic, true SS7 stacks
 */
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include <its++.h>
#include <its_transports.h>
#include <its_ss7_trans.h>
#include <its_worker.h>
#include <its_route.h>
#include <its_mem_pool.h>
#include <its_assertion.h>

#ident "$Id: its_disp_ss7_prc++.cpp,v 1.1.1.1 2007-10-08 11:11:50 bsccs2 Exp $"

#if defined(ANSI)
#undef ANSI
#endif

#if !defined(CCITT)
#define CCITT
#endif

#include <itu/mtp3.h>
#include <itu/isup.h>
#include <itu/sccp.h>
#include <itu/tcap.h>

#include <its_gen_disp.h>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function dispatches events from a generic, true SS7 stack
 *      in an integrated environment.
 *
 *  Input Parameters:
 *      thr - this thread
 *      arg - argument sent when this thread was dispatched.
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
extern "C" DISPDLLAPI void
DISP_Dispatch_SS7_PRC_CPP(ThreadPoolThread *thr, void *arg)
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
                        self->SetExit((cbs->NextEventFailed)(thr, ret));
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
                        self->SetExit((cbs->NextEventFailed)(thr, ret));
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

        ITS_USHORT route = ITS_INVALID_SRC;
        ITS_HDR hdr;
        TCAP_DLG* dlg;

        switch (event.GetSource())
        {
        case ITS_TCAP_PRC_SRC:
            hdr.type = ITS_TCAP_PRC;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event.GetData()[1]);

            dlg = (TCAP_DLG *)(&event.GetData()[sizeof(ITS_OCTET) +
                                                sizeof(ITS_CTXT)]);

            if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_DLG &&
                (dlg->ptype == TCPPT_TC_BEGIN ||
                 dlg->ptype == TCPPT_TC_UNI))
            {
                route = ROUTE_SelectApplication(&hdr, &event.GetEvent(),
                                                ITS_TRUE);
            }
            else
            {
                route = ROUTE_SelectApplication(&hdr, &event.GetEvent(),
                                                ITS_FALSE);
            }

            if (route != ITS_INVALID_SRC && route != ITS_NO_SRC)
            {
                Transport::PutEvent(route, event);
            }
            break;

        case ITS_SCCP_PRC_SRC:
            hdr.type = ITS_SCCP_PRC;
            hdr.context.ssn = ITS_GET_CTXT(&event.GetData()[1]);

            switch (SCCP_MSG_TYPE(&event.GetEvent()))
            {
            case SCCP_MSG_CR:
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
                route = ROUTE_SelectApplication(&hdr, &event.GetEvent(),
                                                ITS_TRUE);
                break;

            default:
                route = ROUTE_SelectApplication(&hdr, &event.GetEvent(),
                                                ITS_FALSE);
                break;
            }

            if (route != ITS_INVALID_SRC && route != ITS_NO_SRC)
            {
                Transport::PutEvent(route, event);
            }
            break;

        case ITS_ISUP_PRC_SRC:
            hdr.type = ITS_ISUP_PRC;
            hdr.context.cic = ITS_GET_CTXT(&event.GetData()[1]);

            switch (ISUP_MSG_TYPE(&event.GetEvent()))
            {
            case ISUP_MSG_IAM:
                route = ROUTE_SelectApplication(&hdr, &event.GetEvent(),
                                                ITS_TRUE);
                break;

            default:
                route = ROUTE_SelectApplication(&hdr, &event.GetEvent(),
                                                ITS_FALSE);
                break;
            }

            if (route != ITS_INVALID_SRC && route != ITS_NO_SRC)
            {
                Transport::PutEvent(route, event);
            }
            break;

        case ITS_MTP3_PRC_SRC:
            self->SetExit(DISP_DeliverMTP3_PRC_CPP(thr, arg, event));
            break;

        case ITS_MTP2_PRC_SRC:
            Transport::PutEvent(ITS_MTP3_PRC_SRC, event);
            break;

        default:
            if (cbs->DispatchUserEvent)
            {
                try
                {
                    self->SetExit((cbs->DispatchUserEvent)(thr, event));
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
