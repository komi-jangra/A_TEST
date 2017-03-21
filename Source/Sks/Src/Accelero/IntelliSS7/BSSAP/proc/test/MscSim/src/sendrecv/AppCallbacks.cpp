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
 *  ID: $Id: AppCallbacks.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/12/27 10:43:05  adutta
 * LOG: Modified UDT message handler
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/30 12:23:28  adutta
 * LOG: Modified for UDT (SS)
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/28 05:57:02  adutta
 * LOG: Remodeled for MSC
 * LOG:
 * LOG: Revision 1.2  2005/02/11 10:21:10  csireesh
 * LOG: Committing after sanitizing Sample App (send-recv) for SCCP-CO: yet to take care of Codec
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include <iostream>

#include <its++.h>
#include <sccp++.h>
#include <engine++.h>
#include <its_service.h>
#include <its_iniparse.h>

#include <App.h>
#include <AppDbc.h>
#include <AppTrace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

extern "C" void
APP_HandleUDTCallback( ITS_POINTER object,
                      ITS_POINTER userData,
                      ITS_POINTER callData);


/*****************************************************************************
 *  Purpose:
 *      This is the Application Selector function that is responsible for routing
 *      incoming messages from sccp stack to the receiving application thread.
 *
 *  Input Parameters:
 *      ITS_HDR h,
 *      ITS_EVENT ev.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      transportinstance.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
extern "C" ITS_USHORT
RouteAPP(ITS_HDR* h, ITS_EVENT* ev)
{
    ITS_INT       ret  = !ITS_SUCCESS;
    its::ThreadPoolEntry ent;

    if (engine::workerPool == NULL)
    {
        APP_TRACE_CRITICAL(("RouteAPP:workerPool is NULL"));
        return ITS_NO_SRC;
    }

    while (ret != ITS_SUCCESS)
    {
        ret = engine::workerPool->GetFirstAvailThread(ent);
    }
    engine::Worker* work = (engine::Worker*)ent.GetThread();

    if (work == NULL)
    {
        APP_TRACE_CRITICAL(("RouteAPP: Failed to get Worker"));
        return ITS_NO_SRC;
    }

    DISP_FuncsCPP *cbs = NULL;
    if ( (cbs = work->GetCallbackStruct()) == NULL)
    {
        APP_TRACE_CRITICAL(("RouteAPP: No Callback registered for worker"));
        return ITS_NO_SRC;
    }

    ret = engine::workerPool->DispatchOnThread(ent,
                                               DISP_Dispatch_USER_CPP,
                                               cbs);
    return work->GetInstance();
}

extern "C"
{
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
AppPreFunc()
{

    APP_TRACE_DEBUG(("PRE-FUNC"));
    CALLBACK_AddCallback(SCCP_SSNRoutingCallbacks,
                         APP_HandleUDTCallback, NULL);
}

/*****************************************************************************
 *  Purpose:
 *      This is a Callback to get all SCCP messages.
 *
 *  Input Parameters:
 *      its::ThreadPoolThread *thr,
 *      its::Event& event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE.
 ****************************************************************************/
int
ReceiverMsgHandler(its::ThreadPoolThread *thr, its::Event& event)
{
    APP_TRACE_DEBUG(("ReceiverMsgHandler::Received  Message\n"));

    ProcessSCCPMsg(thr, event);
    return ITS_TRUE;
}

/*****************************************************************************
 *  Purpose:
 *      An engine callback triggered when an event is received from a third 
 *      party source. It is invoked in the context of the Border Transport.
 *      The received event is passed to this callback.
 *
 *  Input Parameters:
 *      its::ThreadPoolThread thr,
 *      its::Event evt.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Success or Failure.
 ****************************************************************************/
int
BorderTransPostNext(its::ThreadPoolThread *thr, its::Event &evt)
{
    APP_TRACE_DEBUG(("Border Transport Post Next \n"));

    for (int i = 0; i < evt.GetLength(); i++)
    {
        printf("%02x ", evt.GetData()[i]);
        if (!((i+1) % 20))
        {
            cout << endl;
        }
    }

    printf("\n\n");

    return (ITS_SUCCESS);

}

/*****************************************************************************
 *  Purpose:
 *      This function decides whether to continue or terminate
 *      the loop for next event invoked if either GetNextEvent() or 
 *      PeekNextEvent() failed. The error encounted in Get/PeeoNext() call is
 *      passed to this.  If it returns False, it indicates that the receiver
 *      loop for events needs to be terminated.
 *
 *  Input Parameters:
 *      its::ThreadPoolThread thr, 
 *      int err.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Boolean true or false.
 ****************************************************************************/
int
ReceiverNextEventFailed(its::ThreadPoolThread *thr, int err)
{
    APP_TRACE_DEBUG(("ReceiverNextEventFailed\n"));
    engine::Worker *work = reinterpret_cast<engine::Worker *>(thr);
    return (ITS_SUCCESS);
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
PostFunc(void)
{
    APP_TRACE_DEBUG(("POST-FUNC\n"));
    return;
}

}

/*****************************************************************************
 *  Purpose:
 *      Implementation of MTP3 Management callbacks.
 *      This callback indicates the status of the MTP3.
 *
 *  Input Parameters:
 *      object, userData, callData.
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
extern "C"
{
void
MTP3ManagementCallback(ITS_POINTER object,
                       ITS_POINTER userData,
                       ITS_POINTER callData)
{
    ITS_EVENT   *evt = (ITS_EVENT *)callData;
    ITS_OCTET   mType;
    ITS_OCTET   data[MTP3_MAX_SIF_LENGTH];
    bool        exitFlag = false;
    ITS_USHORT  len;
    MTP3_HEADER hdr;

    if (evt == NULL)
    {
        APP_TRACE_CRITICAL(("Event is empty"));
        exitFlag = true;
    }

    if (!exitFlag)
    {
        if (MTP3_Decode(evt, &mType, &hdr, data, &len) != ITS_SUCCESS)
        {
            APP_TRACE_CRITICAL(("MTP3ManagementCallback:MTP3_Decode Failed"));
            exitFlag = true;
        }
        else
        {
            MTP3_PAUSE_RESUME status;
            ITS_UINT          pc = MTP3_PC_GET_VALUE(status.affected);
            switch (mType)
            {
            case MTP3_MSG_PAUSE:
                cout << "MTP3 Pause for PC = " << pc << endl;
                break;

            case MTP3_MSG_RESUME:
                cout << "MTP3 Resume for PC = " << pc << endl;
                break;

            case MTP3_MSG_STATUS:
                cout << "MTP3 Status for PC = " << pc << endl;
                break;

            default:
                break;
            }
        }
    }

    return;
}

void
APP_HandleUDTCallback( ITS_POINTER object,
                      ITS_POINTER userData,
                      ITS_POINTER callData)
{
    ITS_USHORT dest;
    ITS_HDR hdrntfy;
    SCCP_CALLBACK_DATA* event = ( SCCP_CALLBACK_DATA *)callData;
    ITS_EVENT evt;
    SCCP_PROT_CLASS pc;
    int i = 0;

    for (i = 0; i < event->ieCount; i++)
    {
        if (event->ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
        {
            pc = event->ies[i].param_data.protocolClass;
            break;
        }
    }

    pc.pclass = pc.pclass & SCCP_PCLASS_MASK;

    if ((event->ssn != 1) &&
                (pc.pclass == SCCP_PCLASS_0 || pc.pclass == SCCP_PCLASS_1))
    {
        evt.src = ITS_SCCP_SRC;
        hdrntfy.type = ITS_SCCP;

        if (SCCP_Encode(event->ies, event->ieCount, SCCP_MSG_UDT, &evt, &hdrntfy,
                      &SCCP_UDT_Desc)!=ITS_SUCCESS)
        {
            return;
        }

        dest = RouteAPP(&hdrntfy, &evt);
        TRANSPORT_PutEvent(dest, &evt);

        event->transSuccess = ITS_FALSE;
        //event->transSuccess = ITS_TRUE;
    }
}

}
