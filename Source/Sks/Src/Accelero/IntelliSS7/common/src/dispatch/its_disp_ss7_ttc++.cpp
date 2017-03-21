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
 * LOG: Revision 1.1  2007/03/30 04:54:46  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:34  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:10  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 03:30:35  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/25 20:39:57  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG:
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

#ident "$Id: its_disp_ss7_ttc++.cpp,v 1.1.1.1 2007-10-08 11:11:50 bsccs2 Exp $"

#if defined(ANSI)
#undef ANSI
#endif

#if defined(CCITT)
#undef CCITT 
#endif

#if defined(PRC)
#undef PRC 
#endif

#if !defined(TTC)
#define TTC
#endif

#include <japan/mtp3.h>
#include <japan/isup.h>
#include <japan/sccp.h>
#include <japan/tcap.h>

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
DISP_Dispatch_SS7_TTC_CPP(ThreadPoolThread *thr, void *arg)
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
        case ITS_TCAP_TTC_SRC:
            hdr.type = ITS_TCAP_TTC;
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

        case ITS_SCCP_TTC_SRC:
            hdr.type = ITS_SCCP_TTC;
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

        case ITS_ISUP_TTC_SRC:
            hdr.type = ITS_ISUP_TTC;
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

        case ITS_MTP3_TTC_SRC:
            self->SetExit(DISP_DeliverMTP3_TTC_CPP(thr, arg, event));
            break;

        case ITS_MTP2_TTC_SRC:
            Transport::PutEvent(ITS_MTP3_TTC_SRC, event);
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
