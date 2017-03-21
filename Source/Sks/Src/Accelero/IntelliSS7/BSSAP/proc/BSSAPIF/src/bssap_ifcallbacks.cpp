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
 *
 *  ID: $Id: bssap_ifcallbacks.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/12/22 17:38:52  adutta
 * LOG: Can act as server with non-Accelero platform
 * LOG:
 * LOG: Revision 1.1.2.2  2005/12/21 19:49:54  adutta
 * LOG: Added Native define
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 ****************************************************************************/
#ident "$Id: bssap_ifcallbacks.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $"

#include <its++.h>
#include <its_callback.h>
#include <its_assertion.h>
#include <engine++.h>

#include <bssapif_transport.h>
#include <bssapif_trace.h>
#include <bssapif_socket.h>
#include <bssapif_dispatcher.h>

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace engine;
#endif

static ITS_UINT bssapIfInstance;

extern "C"
{


ITS_USHORT
RouteToApp(ITS_HDR *hdr, ITS_EVENT *event)
{
    if (event->src == ITS_BSSAP_SRC)
    {
        return  bssapIfInstance;
    }

    BSSAPIF_TRACE_CRITICAL(("RouteToApp: Unknown source"));

    return ITS_NO_SRC;
}

static void
ReceiveEventFromStack(ITS_ThreadPoolThread *thr, void *arg)
{
    ITS_INT ret;
    ITS_USHORT inst = 0;
    its::Event evt;
    BSSAPDispatcher disp;

    its::Worker* worker = (its::Worker *)thr;

    while(1)
    {
        ret = worker->GetNextEvent(evt);

        if (ret != ITS_SUCCESS)
        {
            BSSAPIF_TRACE_ERROR(("ReceiveEventFromStack: %s", 
                                                   ITS_GetErrorText(ret)));
            continue;
        }


        ITS_EVENT* event = &evt.GetEvent();

        switch (event->src)
        {
        case ITS_BSSAP_SRC:
            BSSAPIF_TRACE_DEBUG(("ReceiveEventFromStack: "
                                       "Received event from stack"));
            disp.ProcessNetworkEvent(evt); 
            break;

        default:
            BSSAPIF_TRACE_ERROR(("Unknown event received from stack"));
            break;
        }
    }
}



/*****************************************************************************
 *  Purpose:
 *      An Engine Callback to perform App-Specific initialization duties.
 *
 *  Input Parameters:
 *      argc - arg count, argv - arg vector.
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
void
BSSAPIFPreFunc()
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_ThreadPoolEntry thrEntry;

    EnableBSSAPIFTracing();

#if defined(NATIVE)
    printf("BSSAPIFPreFunc: Using native calls\n");
    ITS_CLASS_EXTENSION(&itsSOCKTRAN_ClientClassRec) =
                            (ITS_ClassExt)&MyBasicReadWrite;
    ITS_CLASS_EXTENSION(&itsSOCKTRAN_ServerClassRec) =
                            (ITS_ClassExt)&MyBasicReadWrite;

#endif

    ret = (engine::workerPool)->GetFirstAvailThread(thrEntry);

    ret = (engine::workerPool)->DispatchOnThread(thrEntry,
                                                 ReceiveEventFromStack,
                                                 NULL);

    ITS_Worker* wThread = (ITS_Worker*)thrEntry.GetThread();

    bssapIfInstance = wThread->GetInstance();

    ROUTE_SetApplicationSelector(RouteToApp);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is called when the App is Terminating.
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
void
BSSAPIFPostFunc(void)
{
    return;
}

ITS_INT
BSSAPIFPostInit(ThreadPoolThread *thr, ITS_HANDLE handle)
{
    SocketCom* sCom = SocketCom::GetInstance();
    ITS_Worker* work = (ITS_Worker *)thr;

    BSSAPIF_TRACE_DEBUG(("BSSAPIFPostInit"));

    if (handle == NULL)
    {
       BSSAPIF_TRACE_CRITICAL(("BSSAPIFPostInit: Client transport failed"));
    }

    ITS_ASSERT(handle != NULL);

    sCom->SetSocketTransHandle(handle);

    sCom->SetSocketTransInst(work->GetInstance());


    return (ITS_SUCCESS);
}

ITS_INT
BSSAPIFPostNext(ThreadPoolThread *thr, Event &event)
{
    ITS_INT count = 0;
    ITS_INT len = 0;
    BSSAPDispatcher disp;

    BSSAPIF_TRACE_DEBUG(("BSSAPIFPostNext: Received event from socket"));

    printf("\nData received from socket..............\n\n");
    for (len = 0; len < event.GetLength(); len++)
    {
        printf("%02x ", event.GetData()[len]);
    }
    printf("\n\n............................................\n");

    disp.ProcessSocketEvent(&event);

    return (!ITS_SUCCESS);
}


}

