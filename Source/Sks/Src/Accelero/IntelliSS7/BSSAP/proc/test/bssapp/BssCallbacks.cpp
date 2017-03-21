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
 *  ID: $Id: BssCallbacks.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:58  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/24 05:23:50  adutta
 * LOG: BSSAP api changes
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/27 10:59:38  adutta
 * LOG: Messages added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/26 07:02:17  adutta
 * LOG: Initial checkin of BSS stack application.
 * LOG:
 ****************************************************************************/
/*
#include <iostream>
#include <its.h>
#include <its_thread_pool.h>
#include <its_worker.h>
#include <engine.h>
*/

#include<iostream>
#include <time.h>
#include <sys/timeb.h>
#include<stdlib.h>
#include <dlfcn.h>
#include <its++.h>
#include <its_callback.h>
#include <its_assertion.h>
#include <engine++.h>


#include <bssap_interface.h>
#include <bssap_cfgdb.h>
#include <bssap_cicdb.h>
#include <BssMessage.h>

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace engine;
#endif

static ITS_UINT bssInstance;

ITS_USHORT callrefId = 0;



extern "C"
{

static
void SendEvent(ITS_ThreadPoolThread *thr, void *arg)
{
    ITS_OCTET data[25];
    ITS_INT len;
    ITS_INT ret;
    BSSDtap bs;
    BSSMap  mMap;
    BSSAP_Message* mMapData = NULL;
    ITS_OCTET mType;

    for(;;)
    {
        mType = GetChoice();
        mMapData = BuildMsg(mType, data, &len);

        if (mMapData)
        {
            mMap.SetBssId(200);
            mMap.SetMssgType(mMapData->GetMsgType());
            mMap.SetMssgDisc(BSSAP_MD_BSSMAP);
            mMap.SetCallRef(callrefId);
            mMap.SetAppId(0);

            mMap.SetMAPdata(mMapData);
            ret = mMap.SendBSSAPMessage(callrefId);
            printf("\t++++ Sending BSS MAP \n");
        }
        else
        {
            bs.SetBssId(200);
            bs.SetMssgType(mType); 
            bs.SetCallRef(callrefId);
            bs.SetMssgDisc(BSSAP_MD_DTAP);
            bs.SetDTAPdata(data, len);

            ret = bs.SendBSSAPMessage(callrefId);
            printf("\t++++ DTAP messasge len %d %d\n",len, callrefId); 
        }
   
    }
}


void 
ProcessMessage(ITS_EVENT* ev)
{
    ITS_UINT addr;
    BSSAP_Api* bs;
    BSSMap* map;

    bs = (BSSAP_Api*)ev->data;

    callrefId = bs->GetCallRef();

    printf("\t++++ CallRef %d\n", callrefId);
    printf("\t++++ Channel %d\n", bs->GetAppId());


    if (bs->GetMssgDisc() == BSSAP_MD_DTAP)
    {
        printf("\t++++ BSSAP Message type: BSSAP_MD_DTAP\n");
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_BSSMAP)
    {
        printf("\t++++ BSSAP Message type: BSSAP_MD_BSSMAP\n");
        map = (BSSMap*)bs;
        EncodeMapMessage(map->GetMAPdata());
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_TIMEOUT)
    {
        BSSAPError* err = (BSSAPError*)bs;
        printf("\t++++ BSSAP Message type: BSSAP_MD_TIMEOUT\n");
        printf("\t++++ BSSAP Error   code: %d\n", err->GetErrCode());
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_PROTOCOL)
    {
        BSSAPError* err = (BSSAPError*)bs;
        printf("\t++++ BSSAP Error   code: %d\n", err->GetErrCode());
    }
    else
    {
        printf("\t!!! BSSAP Message type: WRONG MESSAGE !!!\n");
    }

}

ITS_USHORT
RouteToApp(ITS_HDR *hdr, ITS_EVENT *event)
{
    if (event->src == ITS_BSSAP_SRC)
    {
        printf("\t+++++ In BSSAP App +++++\n");

        return  bssInstance;
    }

    return ITS_NO_SRC;
}

static void
ReceiveEvent(ITS_ThreadPoolThread *thr, void *arg)
{
    ITS_INT ret;
    ITS_USHORT inst = 0;
    its::Event evt;

    its::Worker* worker = (its::Worker *)thr;

    while(1)
    {
        ret = worker->GetNextEvent(evt);

        if (ret != ITS_SUCCESS)
        {
            printf("\t\n++++ IntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
            continue;
        }

        printf("\t++++ Received event form BSSAP stack\n");

        ITS_EVENT* event = &evt.GetEvent();

        switch (event->src)
        {
        case ITS_BSSAP_SRC:
            ProcessMessage(event);
            break;

        default:
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
AppPreFunc()
{
    printf("\t ++++ In Applicaiton PreFunc\n");
    ITS_INT ret;
    BSSAP_CfgDB cfg;
    BSSAP_Api intf;
    BSSAP_CicDB cic;
    ITS_ThreadPoolEntry thrEntry;
    ITS_ThreadPoolEntry thrEntry2;

    intf.SetDestinations(200, 2, 1, 254, 8);
    cic.AddCIC(1, 0, 1);

    ret = (engine::workerPool)->GetFirstAvailThread(thrEntry);

    ret = (engine::workerPool)->DispatchOnThread(thrEntry,
                                       ReceiveEvent,
                                       NULL);

    ITS_Worker* wThread = (ITS_Worker*)thrEntry.GetThread();

    bssInstance = wThread->GetInstance();

    printf("\t++++ BSSAP APP Instance %d\n",bssInstance);

    ret = (engine::workerPool)->GetFirstAvailThread(thrEntry2);

    ret = (engine::workerPool)->DispatchOnThread(thrEntry2,
                                       SendEvent,
                                       NULL);


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
PostFunc(void)
{
    return;
}

}

