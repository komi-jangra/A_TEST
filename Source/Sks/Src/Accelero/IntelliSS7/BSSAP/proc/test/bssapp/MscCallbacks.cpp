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
 * ID: $Id: MscCallbacks.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.5  2006/04/25 05:40:40  adutta
 * LOG: Modified- Accept call api is blocked
 * LOG:
 * LOG: Revision 1.1.2.4  2005/12/19 09:32:31  adutta
 * LOG: Changed APIs
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/18 06:46:31  adutta
 * LOG: Calling AcceptConnection api to estd. SCCP CO
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:29:18  adutta
 * LOG: Access to the BSSAP_Message get method for message type
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:21:53  adutta
 * LOG: MSC test app
 * LOG:
 ****************************************************************************/

#include<iostream>
#include <time.h>
#include <sys/timeb.h>
#include<stdlib.h>
#include <dlfcn.h>
#include <its++.h>
#include <its_callback.h>
#include <its_assertion.h>
#include <engine++.h>

#include <bssap_msc-interface.h>
#include <bssap_msc-cfgdb.h>
#include <bssap_msc-cicdb.h>
#include <BssMessage.h>

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace engine;
#endif

static ITS_UINT bssInstance;

extern "C"
{

static
void SendEvent(ITS_ThreadPoolThread *thr, void *arg)
{
    ITS_OCTET data[25];
    ITS_INT len;
    ITS_INT ret;
    ITS_INT bssId;
    ITS_OCTET bssId1;
    ITS_CTXT callrefId; 
    BSSAP_Api mMap;
    BSSAP_Message* mMapData = NULL;
    ITS_OCTET mType;

    for(;;)
    {
        mType = GetChoice();
        if (mType == 99)
        {
            break;
        }
        mMapData = BuildMsg(mType, data, &len);

        if (mMapData)
        {
            cout <<"Enter bss id" <<endl; 
            scanf("%d", &bssId);  
            cout <<"Enter call ref id "<<endl;
            scanf("%d", &callrefId);  
            mMap.SetBssId(bssId);
            bssId1 = mMap.GetBssId();
            mMap.SetMssgType(mMapData->GetMsgType());
            mMap.SetMssgDisc(mMapData->GetMDisc());
            mMap.SetCallRef(callrefId);
            mMap.SetAppId(0);

            mMap.SetBSSAPdata(mMapData);
            ret = mMap.SendBSSAPMessage(callrefId);
            printf("\t++++ Sending BSS MAP \n");
        }
    }
}

void 
ProcessMessage(ITS_EVENT* ev)
{
    ITS_UINT addr;
    BSSAP_Api* bs = NULL;
    ITS_CTXT callrefId; 
    BSSAP_Message *msg;
    ITS_UINT address;

    memcpy(&address, ev->data, sizeof(&address));

    bs = (BSSAP_Api*)address;
    msg = bs->GetBSSAPdata(); 

    callrefId = bs->GetCallRef();

    printf("\t++++ CallRef %d\n", callrefId);
    printf("\t++++ Channel %d\n", bs->GetAppId());


    if (bs->GetMssgType() == BSSAP_MSG_COMPLETE_LAYER3_INFO)
    {
        printf("\t++++ BSSAP Message type: BSSAP_MSG_COMPLETE_LAYER3_INFO\n");
        //bs->RejectConnection(callrefId);
        //bs->AcceptConnection(callrefId);
    }

    if (bs->GetMssgDisc() == BSSAP_MD_DTAP)
    {
        printf("\t++++ BSSAP Message type: BSSAP_MD_DTAP %02x\n", msg->GetMsgType());
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_BSSMAP)
    {
        printf("\t++++ BSSAP Message type: BSSAP_MD_BSSMAP %02x\n", msg->GetMsgType());
       // GetMessageName(bs->GetBSSAPdata());
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_TIMEOUT)
    {
        BSSAPError* err = (BSSAPError*)bs;
        printf("\t++++ BSSAP Message type: BSSAP_MD_TIMEOUT\n");
        printf("\t++++ BSSAP Error   code: %d\n", err->GetErrCode());
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_SCCP)
    {
        if (bs->GetMssgType() == BSSAP_CON_REL)
        {
            printf("\t++++ BSSAP Message Type : BSSAP_MD_SCCP \n");
            printf("\t++++ BSSAP Message code : BSSAP_CON_REL \n");
        }  

        if (bs->GetMssgType() == BSSAP_CON_ESTD)
        {
            printf("\t++++ BSSAP Message Type : BSSAP_MD_SCCP \n");
            printf("\t++++ BSSAP Message code : BSSAP_CON_ESTD \n");
        } 
    }
    else if (bs->GetMssgDisc() == BSSAP_MD_PROTOCOL)
    {
        BSSAPError* err = (BSSAPError*)bs;
        ITS_OCTET ts = err->GetTimeSlot();
        ITS_USHORT pcm = err->GetPcm();
                                                                                                                                              
        printf("\t++++ BSSAP Message type: BSSAP_MD_PROTOCOL\n");
                                                                                                                                              
        switch(err->GetErrCode())
        {
            case BSSAP_EENCODE:
                printf("\t++++ BSSAP Error   code: BSSAP_EENCODE\n");
            break;
            case BSSAP_EDECODE:
                printf("\t++++ BSSAP Error   code: BSSAP_EDECODE\n");
            break;
            case BSSAP_EINVMESSAGE:
                printf("\t++++ BSSAP Error   code: BSSAP_EINVMESSAGE\n");
            break;
            case BSSAP_ECICNOTFOUND:
                printf("\t++++ BSSAP Error   code: BSSAP_ECICNOTFOUND\n");
                printf("\t++++ PCM %d TS %d \n", pcm, ts);
            break;
            case BSSAP_ENORESETACK:
                printf("\t++++ BSSAP Error   code: BSSAP_ENORESETACK\n");
            break;
            case BSSAP_ENOBLKACK:
                printf("\t++++ BSSAP Error   code: BSSAP_ENOBLKACK\n");
            break;
            case BSSAP_ENOUNBLKACK:
                printf("\t++++ BSSAP Error   code: BSSAP_ENOUNBLKACK\n");
            break;
            case BSSAP_ENORESETCKTACK:
                printf("\t++++ BSSAP Error   code: BSSAP_ENORESETCKTACK\n");
            break;
            case BSSAP_EUNEQUIPCKT:
                printf("\t++++ BSSAP Error   code: BSSAP_EUNEQUIPCKT\n");
                printf("\t++++ PCM %d TS %d \n", pcm, ts);
            break;
            default:
                printf("\t++++ BSSAP Error   code: UNKNOWN\n");
            break;
        }
    }
    else
    {
        printf("\t!!! BSSAP Message type: WRONG MESSAGE !!!\n");
    }

     delete bs;
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
    ITS_ThreadPoolEntry thrEntry;
    ITS_ThreadPoolEntry thrEntry2;

    intf.SetDestinations(200, 2, 1, 254, 8);
    intf.SetCIC(200, 1, 0, 7);

    intf.SetDestinations(201, 2, 3, 254, 8);
    intf.SetCIC(201, 1, 1, 1);

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

