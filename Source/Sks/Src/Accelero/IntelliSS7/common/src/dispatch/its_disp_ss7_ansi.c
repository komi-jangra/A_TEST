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
 * LOG: Revision 1.1  2007/03/30 04:54:41  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:34  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:27  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 23:18:18  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2001/11/16 16:40:35  mmiers
 * LOG: Don't block in accept.  Make the dispatchers aware of this.
 * LOG:
 * LOG: Revision 5.4  2001/11/08 23:11:03  mmiers
 * LOG: C++ needs a little help with forwards.
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
 * LOG: Revision 1.8  2001/04/19 20:43:10  mmiers
 * LOG: More error callbacks for the dispatchers.  Give the user an
 * LOG: option if ITS_Initialize fails.
 * LOG:
 * LOG: Revision 1.7  2001/04/19 19:31:18  labuser
 * LOG: Change NextEventFail logic to (by default - no func given)
 * LOG: terminate the event loop.
 * LOG:
 * LOG: Revision 1.6  2001/04/10 19:55:45  mmiers
 * LOG: Debug.
 * LOG:
 * LOG: Revision 1.5  2001/03/09 21:26:23  mmiers
 * LOG: Get DLL linkage working.
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
 * LOG: Revision 3.2  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/08/10 22:46:48  mmiers
 * LOG:
 * LOG:
 * LOG: SCTP update, dispatcher rework for generic behavior.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/09/24 14:25:51  mmiers
 * LOG:
 * LOG:
 * LOG: Correct a few behaviors here.
 * LOG:
 * LOG: Revision 1.3  1999/08/05 14:54:23  labuser
 * LOG:
 * LOG:
 * LOG: Make these files independent of the global protocol setting.
 * LOG:
 * LOG: Revision 1.2  1999/07/29 02:11:43  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build errors after addressing Hubert's comments.
 * LOG:
 * LOG: Revision 1.1  1999/07/27 23:25:01  mmiers
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

#include <its.h>
#include <its_ss7_trans.h>
#include <its_worker.h>
#include <its_assertion.h>
#include <its_route.h>
#include <its_transports.h>

#ident "$Id: its_disp_ss7_ansi.c,v 1.1.1.1 2007-10-08 11:11:50 bsccs2 Exp $"

#if defined(CCITT)
#undef CCITT
#endif

#if !defined(ANSI)
#define ANSI
#endif

#include <ansi/mtp3.h>
#include <ansi/isup.h>
#include <ansi/sccp.h>
#include <ansi/tcap.h>

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
DISP_Dispatch_SS7_ANSI(TPOOL_THREAD *thr, void *arg)
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
        case ITS_TCAP_ANSI_SRC:
            hdr.type = ITS_TCAP_ANSI;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event.data[1]);

            dlg = (TCAP_DLG *)(&event.data[sizeof(ITS_OCTET) +
                                           sizeof(ITS_CTXT)]);

            if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG &&
                (dlg->ptype == TCPPT_TC_QUERY_W_PERM ||
                 dlg->ptype == TCPPT_TC_QUERY_WO_PERM ||
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

        case ITS_SCCP_ANSI_SRC:
            hdr.type = ITS_SCCP_ANSI;
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

        case ITS_ISUP_ANSI_SRC:
            hdr.type = ITS_ISUP_ANSI;
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

        case ITS_MTP3_ANSI_SRC:
            WORKER_THREAD(work).exit = DISP_DeliverMTP3_ANSI(thr, arg, &event);
            break;

        case ITS_MTP2_ANSI_SRC:
            TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &event);
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
