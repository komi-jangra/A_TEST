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
 * LOG: Revision 1.1  2007/03/30 04:54:47  cvsadmin
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
 *
 ****************************************************************************/

/*
 * dispatcher for generic, true SS7 stacks
 */
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include <its.h>
#include <its_ss7_trans.h>
#include <its_worker.h>
#include <its_assertion.h>
#include <its_route.h>
#include <its_transports.h>

#ident "$Id: its_disp_ss7_ttc.c,v 1.1.1.1 2007-10-08 11:11:50 bsccs2 Exp $"

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
DISPDLLAPI void
DISP_Dispatch_SS7_TTC(TPOOL_THREAD *thr, void *arg)
{
    WORKER_Control* work = (WORKER_Control *)thr;
    DISP_Funcs *cbs = (DISP_Funcs *)arg;
    ITS_HANDLE h;
    ITS_EVENT event;
    int ret;

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
        ITS_USHORT route = ITS_INVALID_SRC;
        ITS_HDR hdr;
        TCAP_DLG* dlg;

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
                    WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
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
                    WORKER_THREAD(work).exit = (cbs->NextEventFailed)(thr, ret);
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

        switch (event.src)
        {
        case ITS_TCAP_TTC_SRC:
            hdr.type = ITS_TCAP_TTC;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event.data[1]);

            dlg = (TCAP_DLG *)(&event.data[sizeof(ITS_OCTET) +
                                           sizeof(ITS_CTXT)]);

            if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG &&
                (dlg->ptype == TCPPT_TC_BEGIN ||
                 dlg->ptype == TCPPT_TC_UNI))
            {
                route = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
            }
            else
            {
                route = ROUTE_SelectApplication(&hdr, &event, ITS_FALSE);
            }

            if (route != ITS_INVALID_SRC && route != ITS_NO_SRC)
            {
                TRANSPORT_PutEvent(route, &event);
            }
            break;

        case ITS_SCCP_TTC_SRC:
            hdr.type = ITS_SCCP_TTC;
            hdr.context.ssn = ITS_GET_CTXT(&event.data[1]);

            switch (SCCP_MSG_TYPE(&event))
            {
            case SCCP_MSG_CR:
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
                route = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
                break;

            default:
                route = ROUTE_SelectApplication(&hdr, &event, ITS_FALSE);
                break;
            }

            if (route != ITS_INVALID_SRC && route != ITS_NO_SRC)
            {
                TRANSPORT_PutEvent(route, &event);
            }
            break;

        case ITS_ISUP_TTC_SRC:
            hdr.type = ITS_ISUP_TTC;
            hdr.context.cic = ITS_GET_CTXT(&event.data[1]);

            switch (ISUP_MSG_TYPE(&event))
            {
            case ISUP_MSG_IAM:
                route = ROUTE_SelectApplication(&hdr, &event, ITS_TRUE);
                break;

            default:
                route = ROUTE_SelectApplication(&hdr, &event, ITS_FALSE);
                break;
            }

            if (route != ITS_INVALID_SRC && route != ITS_NO_SRC)
            {
                TRANSPORT_PutEvent(route, &event);
            }
            break;

        case ITS_MTP3_TTC_SRC:
            WORKER_THREAD(work).exit = DISP_DeliverMTP3_TTC(thr, arg, &event);
            break;

        case ITS_MTP2_TTC_SRC:
            TRANSPORT_PutEvent(ITS_MTP3_TTC_SRC, &event);
            break;

        default:
            if (cbs->DispatchUserEvent)
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
