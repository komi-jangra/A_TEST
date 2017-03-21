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
 * ID: $Id: bssap_msc-interface.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.6  2006/06/28 04:54:06  adutta
 * LOG: Added interface for passing pc/ssn for mgmt. messages
 * LOG:
 * LOG: Revision 1.1.2.5  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/28 05:20:08  adutta
 * LOG: Fix for Issue#3073
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/18 06:36:25  mkrishna
 * LOG: Changed BSSAP_Payload to BSSAP_Api
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:14:33  mkrishna
 * LOG: BSSAP message pointer check
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             
#include <engine++.h>
#include <sccp++.h>
#include <bssap-msc.h>
#include <bssap_msc-common.h>
#include <bssap_msc-call.h>
#include <bssap_msc-cfgdb.h>
#include <bssap_msc-cicdb.h>
#include <bssap_msc-interface.h>
#include <bssap_msc-sccphandler.h>

/*implementation:internal
*
* PURPOSE:
*      This function acts as a send API for the application
*      to send BSSAP data to the stack.
* INPUT:
*      bssMssg - contains BSSAP specific data.
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      ITS_SUCCES - success.  Any other value indicates an IntelliSS7
*      processing error.
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0070, ID :: D0340,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Api::SendBSSAPMessage(ITS_CTXT& calref)
{
    ITS_EVENT ev;
    ITS_INT ret = 0;
    ITS_OCTET mType = 0;

    BSSAP_DEBUG(("BSSAP_Api: SendBSSAPMessage\n"));

    if ((this->GetMssgDisc() == BSSAP_MD_BSSMAP) ||
        (this->GetMssgDisc() == BSSAP_MD_DTAP))
    {
        mType = this->GetMssgType();
                                                                                                                                              
        if (mType == BSSAP_MSG_COMPLETE_LAYER3_INFO)
        {
            return (!ITS_SUCCESS);
        }
        else if (mType == BSSAP_MSG_HANDOVER_REQUEST)
        {
            BSSAP_DEBUG(("SendBSSAPMessage : L3 Message\n"));
                                                                                                                                              
            ret = SCCP_GetNextLocalRef(ISS7_Stack, &calref);
            this->SetCallRef(calref);
                                                                                                                                              
            ITS_EVENT_INIT(&ev, BSSAP_HND_SRC, sizeof(BSSAP_Api));
        }
        else
        {
            ITS_EVENT_INIT(&ev, BSSAP_MAP_SRC, sizeof(BSSAP_Api));
        }
                                                                                                                                              
        memcpy(ev.data, &bd, sizeof(BSSAPData));
    }
    else
    {
        BSSAP_WARNING(("SendBSSAPMessage: Invalid BSSAP message received\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }

    ret = TRANSPORT_PutEvent(ITS_BSSAP_SRC, &ev);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendBSSAPMessage: Transport put event failed\n"));

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       setting up the initial configuration 
* INPUT:
*       bscId, lpc, rpc, lssn, rssn 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0150, ID :: D0160,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Api::SetDestinations(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc,
                                   ITS_OCTET lssn, ITS_OCTET rssn)
{
    ITS_INT ret = 0;
    BSSAP_CfgDB db;

    BSSAP_DEBUG(("BSSAP_Api: SetDestinations\n"));

    ret = db.AddCfg(bscId, lpc, rpc, lssn, rssn);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_CRITICAL(("SetDestinations: Fail add config BssId %d\n", bscId));
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO msg to application
* INPUT:
*       call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Api::SetCIC(ITS_OCTET bscId, ITS_USHORT pcm, ITS_USHORT startTs,
                        ITS_USHORT endTS)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_CicDB cic;

    BSSAP_DEBUG(("BSSAP_Api: SetCIC \n"));

    ret = cic.AddCIC(bscId, pcm, startTs, endTS);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO msg to application
* INPUT:
*       call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Api::AcceptConnection(ITS_CTXT callRef)
{
    BSSAP_SCCPHandler sccpHdl;
    ITS_INT ret = ITS_SUCCESS;
 
    BSSAP_DEBUG(("BSSAP_Api: AcceptConnection \n"));

    ret = sccpHdl.SendCC(callRef);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO msg to application
* INPUT:
*       call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Api::RejectConnection(ITS_CTXT callRef)
{
    BSSAP_SCCPHandler sccpHdl;
    ITS_INT ret =ITS_SUCCESS;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Api: RejectConnection \n"));
                                                                                                                                              
    ret = sccpHdl.SendCREF(callRef);
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO msg to application
* INPUT:
*       call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Api::ClearConnection(ITS_CTXT callRef)
{
    BSSAP_SCCPHandler sccpHdl;
    ITS_INT ret =ITS_SUCCESS;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Api: ClearConnection \n"));
                                                                                                                                              
    ret = sccpHdl.SendRLSD(callRef);
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending Sccp Ind to application 
* INPUT:
*       call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Interface::DispatchSccpIndToApp(ITS_OCTET msgType, ITS_OCTET msgCode,
                                          BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_USHORT dest = 0;

    // Application has to delete this
    BSSAP_Api* mSccp = new BSSAP_Api;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Interface: DispatchSccpIndToApp\n"));
                                                                                                                                              
    mSccp->SetMssgDisc(msgType);
    mSccp->SetMssgType(msgCode);

    mSccp->SetCallRef(call->GetSLR());
    mSccp->SetAppId(call->GetAppId());

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mSccp));
    memcpy(ev.data, &mSccp, sizeof(&mSccp));
                                                                                                                                              
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_ERROR(("DispatchSccpIndToApp: Bad route to App %d\n",
                                                       hdr.context.conref));

        delete mSccp;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("DispatchSccpIndToApp: Transport put event failed %d\n"                                                        , hdr.context.conref));
            delete mSccp;
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO msg to application
* INPUT:
*       call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/

ITS_INT
BSSAP_Interface::DispatchMsgToApp(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_USHORT dest = 0;
    BSSAP_Api* mDtap = new BSSAP_Api;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Interface: DispatchMsgToApp\n"));
                                                                                                                                              
    mDtap->SetCallRef(call->GetSLR());
    mDtap->SetAppId(call->GetAppId());
    mDtap->SetMssgDisc(BSSAP_MD_DTAP);
    mDtap->SetMssgType(call->GetMssgType());
                                                                                                                                              
    if (call->GetBSSAPdata())
    {
        mDtap->SetBSSAPdata(call->GetBSSAPdata());
    }
    else
    {
        BSSAP_CRITICAL(("DispatchMsgToApp : missing DTAP message\n"));

        delete mDtap;

        return (!ITS_SUCCESS);
    }

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mDtap));
    memcpy(ev.data, &mDtap, sizeof(&mDtap));
                                                                                                                                              
    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = call->GetSLR();
                                                                                                                                              
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_ERROR(("DispatchMsgToApp: Bad route to App %d\n",
                                                       hdr.context.conref));

        delete mDtap;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("DispatchMsgToApp: Transport put event failed %d\n",
                                                      hdr.context.conref));
            delete mDtap;
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending message to application 
* INPUT:
*       call object, mdata 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Interface::DispatchMsgToApp(BSSAP_Call* call, BSSAP_Message* mdata)
{
    ITS_USHORT dest;
    ITS_CTXT cref = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    ITS_HDR hdr;
    BSSAP_Api* mMap = new  BSSAP_Api;

    BSSAP_DEBUG(("BSSAP_Interface: DispatchMsgToApp\n"));

    cref = call->GetSLR();
    mMap->SetCallRef(cref);
    mMap->SetAppId(call->GetAppId());
    mMap->SetMssgDisc(BSSAP_MD_BSSMAP);
    mMap->SetMssgType(call->GetMssgType());

    mMap->SetBSSAPdata(mdata);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mMap));
    memcpy(ev.data, &mMap, sizeof(&mMap));

    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = cref;
  
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        // ERROR TRACE
        delete mMap;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    } 

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       dispatching error to application 
* INPUT:
*       call object, error type, error code 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Interface::DispatchErrorToApp(BSSAP_Call* call, 
                                    ITS_OCTET errType,
                                    ITS_OCTET errCode)
{
    ITS_USHORT dest = 0;
    ITS_HDR hdr;
    ITS_CTXT cref = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    BSSAPError* mssg  = new BSSAPError;

    BSSAP_DEBUG(("BSSAP_Interface: DispatchErrorToApp\n"));

    if (call)
    { 
        cref = call->GetSLR(); 
        mssg->SetMssgType(call->GetMssgType());
        mssg->SetAppId(call->GetAppId());
        mssg->SetCallRef(cref);
    }
    else
    {
        mssg->SetMssgType(0);
        mssg->SetAppId(0);
        mssg->SetCallRef(0);
    }

    mssg->SetMssgDisc(errType);
    mssg->SetErrCode(errCode);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mssg));
    memcpy(ev.data, &mssg, sizeof(&mssg));

    BSSAP_DEBUG(("DispatchErrorToApp: Error type %d Error code %d "
                            "MessageId %d " 
                            "CallRef %d Channel %d\n", mssg->GetMssgDisc(), 
                             mssg->GetErrCode(), mssg->GetMssgType(), 
                             mssg->GetCallRef(), mssg->GetAppId()));

    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = cref;
 
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_CRITICAL(("DispatchErrorToApp: Bad route to App\n"));

        delete mssg;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO UDT error to application 
* INPUT:
*       error type, error code, msg type, pcm, timeslot 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT
BSSAP_Interface::DispatchErrorToApp(ITS_OCTET errType,
                                    ITS_OCTET errCode,
                                    ITS_OCTET mType,
                                    ITS_USHORT pcm,
                                    ITS_OCTET ts)
{                                   
    ITS_USHORT dest = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    ITS_HDR hdr;
    BSSAPError* mssg = new BSSAPError;
    
    BSSAP_DEBUG(("BSSAP_Interface: DispatchErrorToApp\n"));
    
    mssg->SetMssgDisc(errType);
    mssg->SetErrCode(errCode);
    mssg->SetTimeSlot(ts);
    mssg->SetPcm(pcm);
    mssg->SetMessgType(mType);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mssg));
    memcpy(ev.data, &mssg, sizeof(&mssg));

    hdr.type = ITS_BSSAP_SRC;

    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_CRITICAL(("DispatchErrorToApp: Bad route to App\n"));

        delete mssg;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending CO UDT error to application
* INPUT:
*       error type, error code, msg type, pcm, timeslot
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* adutta  26-06-2006    IMR-MSC-SDS-BSAP-V1.0.01    Added for ssn/pc for
*                                                   mgmt. messages
*/
ITS_INT
BSSAP_Interface::DispatchErrorToApp(ITS_OCTET errType,
                                    ITS_OCTET errCode,
                                    ITS_UINT pc,
                                    ITS_OCTET ssn) 
{
    ITS_USHORT dest = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT ev;
    ITS_HDR hdr;
    BSSAPError* mssg = new BSSAPError;
   
    BSSAP_DEBUG(("BSSAP_Interface: DispatchErrorToApp\n"));

    mssg->SetMssgDisc(errType);
    mssg->SetErrCode(errCode);
    mssg->SetPointCode(pc);

    if (ssn)
    {
        mssg->SetSSN(ssn);
    }

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mssg));
    memcpy(ev.data, &mssg, sizeof(&mssg));

    hdr.type = ITS_BSSAP_SRC;

    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_CRITICAL(("DispatchErrorToApp: Bad route to App\n"));

        delete mssg;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Sending UDT Map msg to application 
* INPUT:
*       msg, nwId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330, ID :: D0920
*/
ITS_INT 
BSSAP_Interface::DispatchMapUDTtoApp(BSSAP_Message* msg, ITS_OCTET nwId)
{
    ITS_INT ret =  ITS_SUCCESS;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_USHORT dest;
    BSSAP_Api* mMapUdt = new BSSAP_Api;

    BSSAP_DEBUG(("BSSAP_Interface: DispatchMapUDTtoApp\n"));

    mMapUdt->SetCallRef(0);
    mMapUdt->SetBssId(nwId);
    mMapUdt->SetAppId(0);
    mMapUdt->SetMssgDisc(BSSAP_MD_BSSMAP);
    mMapUdt->SetMssgType(msg->GetMsgType());
    mMapUdt->SetBSSAPdata(msg);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(&mMapUdt));
    memcpy(ev.data, &mMapUdt, sizeof(&mMapUdt));

    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = 0;

    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_ERROR(("DispatchMapUDTtoApp: Bad route to App\n"));

        delete &mMapUdt;
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev); 
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("DispatchMapUDTtoApp: Send to App failed \n"));

            delete &mMapUdt;
        }
    }

    return (ret);
}
