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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.6  2006/06/28 04:56:32  adutta
 * LOG: Modified for pc/ssn passing
 * LOG:
 * LOG: Revision 1.1.2.5  2006/05/05 05:30:11  adutta
 * LOG: Large context makeup
 * LOG:
 * LOG: Revision 1.1.2.4  2005/12/22 16:27:51  adutta
 * LOG: Set data length to 100
 * LOG:
 * LOG: Revision 1.1.2.3  2005/12/21 19:50:41  adutta
 * LOG: Memory overwrite fix
 * LOG:
 * LOG: Revision 1.1.2.2  2005/12/20 17:45:03  adutta
 * LOG: Added SCCP clear connection
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: bssapif_dispatcher.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_dispatcher.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $"



#include <bssapif_common.h>
#include <bssapif_trace.h>
#include <bssapif_dispatcher.h>
#include <bssapif_socket.h>

#include <BSSAP++.h>



#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessSCCPMessage(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 2;
    ITS_CTXT callrefId = 0;
    BSSAP_Api api;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessSCCPMessage"));

    // Call reference id
    callrefId |= evt->data[index++];
    callrefId |= evt->data[index++] << 8;
    callrefId |= evt->data[index++] << 16;
    callrefId |= evt->data[index++] << 24;

    if (evt->data[1] == CP_SCCP_ACCEPT)
    {
        BSSAPIF_TRACE_DEBUG(("ProcessSCCPMessage: Received CC"));

        ret  = api.AcceptConnection(callrefId);
    }
    else if (evt->data[1] == CP_SCCP_REJECT)
    {
        BSSAPIF_TRACE_DEBUG(("ProcessSCCPMessage: Received CREF"));

        ret = api.RejectConnection(callrefId);
    }
    else if (evt->data[1] == CP_SCCP_RELEASE)
    {
        BSSAPIF_TRACE_DEBUG(("ProcessSCCPMessage: Received REL"));
    
        ret = api.ClearConnection(callrefId);
    }
    else
    {

        ret = (!ITS_SUCCESS);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessCICMessage(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 1;
    ITS_OCTET bscId = 0; 
    ITS_USHORT pcm = 0; 
    ITS_USHORT startTs = 0;
    ITS_USHORT endTs= 0;
    BSSAP_Api api;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessCICMessage"));

    // BSC Id
    bscId = evt->data[index++];

    // PCM
    pcm  |= evt->data[index++];
    pcm  |= evt->data[index++] << 8;

    // Start Timeslot
    startTs  |= evt->data[index++];

    // End Timeslot
    endTs  |= evt->data[index++];

    ret = api.SetCIC(bscId, pcm, startTs, endTs);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessBSSAPMessage(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_CTXT ref = 0;
    ITS_INT len = 0;
    ITS_INT index = 1;
    BSSAP_Message* dec = NULL;
    BSSAPData bd;
    BSSAP_Api* api = NULL;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessBSSAPMessage"));

    memset(&bd, 0, sizeof(BSSAPData));

    // BSC Id
    bd.bssId = evt->data[index++];

    // Call ref id
    bd.callrefId  |= evt->data[index++];
    bd.callrefId  |= evt->data[index++] << 8;
    bd.callrefId  |= evt->data[index++] << 16;
    bd.callrefId  |= evt->data[index++] << 24;


    // App Id
    bd.appId  |= evt->data[index++];
    bd.appId  |= evt->data[index++] << 8;


    // Message Discriminator
    bd.mssgDisc = evt->data[index++];

    // BSSAP Message name
    bd.mssgType = evt->data[index++];

    // BSSAP Message length
    len = evt->data[index++];

    if (BSSAP_Message::Decode(&evt->data[index], len, &dec)
                                                        != ITS_SUCCESS)
    {
        BSSAPIF_TRACE_ERROR(("ProcessBSSAPMessage: Fail to decode BSSAP data"));

        return (!ITS_SUCCESS);
    }

    if (bd.mssgDisc == BSSAP_MD_BSSMAP)
    {
        BSSAPIF_TRACE_DEBUG(("ProcessBSSAPMessage: Received BSS-MAP"));

        api = new BSSAP_Api;

        api->SetBssId(bd.bssId);
        api->SetCallRef(bd.callrefId);
        api->SetAppId(bd.appId);
        api->SetMssgDisc(BSSAP_MD_BSSMAP);
        api->SetMssgType(bd.mssgType);
        api->SetBSSAPdata(dec);

        ret = api->SendBSSAPMessage(ref);

        delete api;
        api = NULL;
    }
    else
    {
        BSSAPIF_TRACE_DEBUG(("ProcessBSSAPMessage: Received BSS-DTAP"));

        api = new BSSAP_Api;
 
        api->SetBssId(bd.bssId);
        api->SetCallRef(bd.callrefId);
        api->SetAppId(bd.appId);
        api->SetMssgDisc(BSSAP_MD_DTAP);
        api->SetMssgType(bd.mssgType);
        api->SetBSSAPdata(dec);

        ret = api->SendBSSAPMessage(ref);

        delete api;
        api = NULL;
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessCFGMessage(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 1;
    ITS_OCTET bscId = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT lpc = 0;
    ITS_UINT rpc = 0;
    ITS_OCTET lssn  =0;
    ITS_OCTET rssn  =0;
    BSSAP_Api api;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessCFGMessage"));

    // BSC Id
    bscId = evt->data[index++];

    // LPC
    lpc  |= evt->data[index++];
    lpc  |= evt->data[index++] << 8;
    lpc  |= evt->data[index++] << 16;
    lpc  |= evt->data[index++] << 24;

    // RPC 
    rpc  |= evt->data[index++];
    rpc  |= evt->data[index++] << 8;
    rpc  |= evt->data[index++] << 16;
    rpc  |= evt->data[index++] << 24;

    // LSSN
    lssn =  evt->data[index++];

    // RSSN
    rssn =  evt->data[index++];

    ret = api.SetDestinations(bscId, lpc, rpc, lssn, rssn);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT 
BSSAPDispatcher::ProcessSocketEvent(Event* event)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT* evt = &event->GetEvent();

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessSocketEvent"));

    if (evt->data[0] == CP_BSSAP_SCCP_TAG)
    {
        ret = ProcessSCCPMessage(evt);
    }
    else if (evt->data[0] == CP_BSSAP_CIC_TAG)
    {
        ret = ProcessCICMessage(evt);
    }
    else if (evt->data[0] == CP_BSSAP_CFG_TAG)
    {
        ret = ProcessCFGMessage(evt);
    }
    else if (evt->data[0] == CP_BSSAP_MSG_TAG)
    {
        ret = ProcessBSSAPMessage(evt);
    }
    else
    {
        BSSAPIF_TRACE_ERROR(("ProcessCFGMessage: Received unknown event"));

        ret = (!ITS_SUCCESS);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkDTAP(BSSAP_Api* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 0;
    ITS_INT len = 0;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;
    BSSAP_Message* dtap = NULL;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkDTAP"));

 
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, 100);

    // Tag
    ev.data[index++] = CP_BSSAP_MSG_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >> 16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;

    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;


    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();

    dtap = api->GetBSSAPdata();
    if (BSSAP_Message::Encode(buff, len, dtap) != ITS_SUCCESS)
    {
        BSSAPIF_TRACE_ERROR(("ProcessNetworkDTAP: Encode of BSS-DTAP failed"));

        return (!ITS_SUCCESS);
    }

    if (dtap)
    {
        delete dtap;
    }


    // BSSAP message buffer length
    ev.data[index++] = len;

    // BSSAP messge buffer
    memcpy(&ev.data[index], buff, len);

    // Actual length
    len = index + len;
    
    ev.len = len;
    
    ITS_Event event(&ev);
    
    ITS_EVENT_TERM(&ev);

    SocketCom* bsifPPCom = SocketCom::GetInstance();

    ret = bsifPPCom->SendToSocket(event);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkMAP(BSSAP_Api* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 0;
    ITS_INT len = 0;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;
    BSSAP_Message* map = NULL;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkMAP"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, 100);

    // Tag
    ev.data[index++] = CP_BSSAP_MSG_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >> 16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;

    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;


    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();

    map = api->GetBSSAPdata();
    if (BSSAP_Message::Encode(buff, len, map) != ITS_SUCCESS)
    {
        BSSAPIF_TRACE_ERROR(("ProcessNetworkMAP: Encode of BSS-MAP falied"));

        return (!ITS_SUCCESS);
    }

    if (map)
    {
        delete map;
    }

    // BSSAP message buffer length
    ev.data[index++] = len;

    // BSSAP messge buffer
    memcpy(&ev.data[index], buff, len);

    // Actual length
    len = index + len;

    ev.len = len;

    ITS_Event event(&ev);

    ITS_EVENT_TERM(&ev);

    map = NULL;

    SocketCom* bsifPPCom = SocketCom::GetInstance();

    ret = bsifPPCom->SendToSocket(event);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkTimeout(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 0;
    ITS_INT len = 0;
    ITS_EVENT ev;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkTimeout"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(ITS_OCTET)*3);

    // Tag
    ev.data[index++] = CP_BSSAP_TIMEOUT_TAG;

    // Message Discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message name
    ev.data[index++] = api->GetErrCode();

    ITS_Event event(&ev);

    ITS_EVENT_TERM(&ev);

    SocketCom* bsifPPCom = SocketCom::GetInstance();

    ret = bsifPPCom->SendToSocket(event);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkProtocol(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 0;
    ITS_CTXT callrefId = 0;
    ITS_USHORT pcm = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkProtocol"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSAPData));

    // Tag
    ev.data[index++] = CP_BSSAP_PROTOCOL_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >> 16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;

    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;

    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();

    // Error code
    ev.data[index++] = api->GetErrCode();

    // PCM
    pcm = api->GetPcm();
    ev.data[index++] =  pcm & 0x00FF;
    ev.data[index++] =  (pcm & 0xFF00) >> 8;

    // TS
    ev.data[index++] = api->GetTimeSlot();

    ev.len = index;

    ITS_Event event(&ev);

    ITS_EVENT_TERM(&ev);

    SocketCom* bsifPPCom = SocketCom::GetInstance();

    ret = bsifPPCom->SendToSocket(event);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkStaus(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 0;
    ITS_OCTET size = 0;
    ITS_OCTET ssn = 0;
    ITS_INT len = 0;
    ITS_EVENT ev;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkStaus"));

    // Total length = (BSSAPData structure)
    if (ssn = api->GetSSN())
    {
        size = sizeof(ITS_OCTET)*4 +sizeof(ITS_UINT);
    }
    else
    {
        size = sizeof(ITS_OCTET)*3 +sizeof(ITS_UINT);
    }

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, size);

    // Tag
    ev.data[index++] = CP_BSSAP_NETWORK_TAG;

    // Message Discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message name
    ev.data[index++] = api->GetErrCode();

    // Point Code
    ITS_UINT pc = api->GetPointCode();
    ev.data[index++] = pc & 0x000000FF;
    ev.data[index++] = (pc & 0x0000FF00) >> 8;
    ev.data[index++] = (pc & 0x00FF0000) >> 16;
    ev.data[index++] = (pc & 0xFF000000) >> 24;

    // SSN
    if (ssn)
    {
        ev.data[index++] = ssn;
    }
    
    ITS_Event event(&ev);

    ITS_EVENT_TERM(&ev);

    SocketCom* bsifPPCom = SocketCom::GetInstance();

    ret = bsifPPCom->SendToSocket(event);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkSCCPInd(BSSAP_Api* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 0;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_INT len = 0;
    ITS_EVENT ev;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkSCCPInd"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSAPData));

    // Tag
    ev.data[index++] = CP_BSSAP_SCCP_TAG;

    // Message name
    ev.data[index++] = api->GetMssgType();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >> 16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;

    // App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;

    ITS_Event event(&ev);

    ev.len = index;

    ITS_EVENT_TERM(&ev);

    SocketCom* bsifPPCom = SocketCom::GetInstance();

    ret = bsifPPCom->SendToSocket(event);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkEvent(ITS_Event& event)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET msgDisc = 0;
    ITS_UINT address;
    BSSAP_Api* bssap_api = NULL;

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessNetworkEvent"));

    memcpy(&address, event.GetData(), sizeof(&address)); 

    bssap_api = (BSSAP_Api*)address;

    if (!bssap_api)
    {
        BSSAPIF_TRACE_ERROR(("ProcessNetworkEvent: Invalid data address"));

        return (!ITS_SUCCESS);
    }

    msgDisc = bssap_api->GetMssgDisc();

    if (msgDisc == BSSAP_MD_DTAP)
    {
        ret = ProcessNetworkDTAP(bssap_api); 
    }
    else if (msgDisc == BSSAP_MD_BSSMAP)
    {
        ret = ProcessNetworkMAP(bssap_api); 
    }
    else if (msgDisc == BSSAP_MD_TIMEOUT)
    {
        ret = ProcessNetworkTimeout((BSSAPError*)bssap_api); 
    }
    else if (msgDisc == BSSAP_MD_PROTOCOL)
    {
        ret = ProcessNetworkProtocol((BSSAPError*)bssap_api); 
    }
    else if (msgDisc == BSSAP_MD_NETWORK)
    {
        ret = ProcessNetworkStaus((BSSAPError*)bssap_api); 
    }
    else if (msgDisc == BSSAP_MD_SCCP)
    {
        ret = ProcessNetworkSCCPInd(bssap_api);
    }
    else
    {
    }

    if (bssap_api)
    {
        delete bssap_api;
    }

    return (ret);
}
