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
 * ID: $Id: bssap_msc-sccphandler.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.13  2006/05/09 05:17:12  adutta
 * LOG: Added debug print in CR process
 * LOG:
 * LOG: Revision 1.1.2.12  2006/05/05 05:21:25  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.11  2006/04/26 07:21:05  adutta
 * LOG: Added debug trace in CR
 * LOG:
 * LOG: Revision 1.1.2.10  2006/04/25 05:31:49  adutta
 * LOG: Changes as par IMR comments
 * LOG:
 * LOG: Revision 1.1.2.9  2005/12/22 16:08:24  adutta
 * LOG: Call object deleted in RLSD/CREF
 * LOG:
 * LOG: Revision 1.1.2.8  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.7  2005/12/13 09:44:42  mkrishna
 * LOG: Calref assignment after debug trace
 * LOG:
 * LOG: Revision 1.1.2.6  2005/11/30 06:48:40  mkrishna
 * LOG: Pegs implementation
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/20 14:26:01  adutta
 * LOG: CREF indication to app.
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/20 14:10:10  adutta
 * LOG: Removed unwanted call deletion
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/20 14:02:52  mkrishna
 * LOG: Deletion of call context on RLC
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/18 06:37:45  mkrishna
 * LOG: Added CREF/RLSD APIs
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             

#include <sccp++.h>
#include <BSSAP++.h>
#include <bssap_msc-pegs.h>
#include <bssap_msc-common.h>
#include <bssap_msc-fsm.h>
#include <bssap_msc-cfgdb.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-cfgdb.h>
#include <bssap_msc-sccphandler.h>
#include <bssap_msc-discriminator.h>

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

/*implementation:internal
*
* PURPOSE:
*       sending UDT messages 
* INPUT:
*       buffer, buf len, bssId 
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendUDT(ITS_OCTET* data, 
                           ITS_UINT len, 
                           ITS_OCTET bssId)
{
    ITS_INT ret;
    ITS_OCTET pclass = SCCP_PCLASS_0;
    BSSAP_Interface bssIf;
    ITS_HDR hd;
    MTP3_Header mtphdr;
    CFGData* cfgdata = NULL;
    BSSAP_CfgDB db;
    SCCP_CallingPartyAddr cpa;
    SCCP_CalledPartyAddr  cdp;
    SCCP_ProtocolClass pc;
    SCCP_UnitData ud;
    SCCP_UserData udt;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendUDT\n"));

    cfgdata = db.FetchRPCEntry(bssId);
    if (cfgdata)
    {
        // Build MTP Header
        mtphdr.SetOPC(cfgdata->lpc);
        mtphdr.SetDPC(cfgdata->rpc);

        // Build Called party address
        cdp.SetPointCode(cfgdata->rpc);
        cdp.SetSSN(cfgdata->rssn);
        cdp.SetRouteByPCSSN(ITS_TRUE);
        cdp.SetInternationalRouting(ITS_TRUE);
        ud.AddIE(&cdp);

        // Build Calling party address
        cpa.SetPointCode(cfgdata->lpc);
        cpa.SetSSN(cfgdata->lssn);
        cpa.SetRouteByPCSSN(ITS_TRUE);
        cpa.SetInternationalRouting(ITS_TRUE);
        ud.AddIE(&cpa);
    }
    else
    {
        BSSAP_ERROR(("SendUDT: Fail to send UDT, no rpc\n"));

        return (ITS_SUCCESS);
    }

    pc.SetProtocolClass(pclass);
    ud.AddIE(&pc);

    udt.SetUserData(data, (ITS_INT)len);
    ud.AddIE(&udt);

    hd.type = ITS_SCCP;
    hd.context.conref = 0;

    ret = SCCP_MessageClass::Send(ISS7_Stack, &hd, &ud);
     
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       sending sccp DT1 messages
* INPUT:
*       call object 
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendDT1(BSSAP_Call* call)
{
    ITS_INT ret;
    ITS_INT len = 0;
    ITS_CTXT callrefId = 0;
    ITS_HDR hd;
    ITS_OCTET* tmpdata = NULL;
    BSSAP_Message* msg;
    SCCP_UserData ud;
    SCCP_DataForm1 dt1;
    SCCP_SegmentReassem sr;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendDT1\n"));

    callrefId = call->GetSLR();

    hd.context.conref = callrefId;
    hd.type = ITS_SCCP;

    SCCP_DestinationLocalRef dlr(call->GetDLR());
    dt1.AddIE(&dlr); 

    tmpdata = call->GetBSSAPData(&len);
    ud.SetUserData(tmpdata, len);
    dt1.AddIE(&ud);   

    sr.SetSegmentReassem(ITS_FALSE); 
    dt1.AddIE(&sr);

    SCCP_MessageClass::Send(ISS7_Stack, &hd, &dt1);

    PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DT1_SEND);

    BSSAP_DEBUG(("SendDT1: Sending DT1 slr %d dlr %d\n", call->GetSLR(),call->GetDLR()));


    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       sending sccp connection request 
* INPUT:
*       call object 
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendCR(BSSAP_Call *call)
{
    ITS_INT ret = 0;
    ITS_INT len = 0;
    ITS_OCTET* tmpdata = NULL;
    ITS_HDR hd;
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    BSSAP_Message* msg = NULL;
    SCCP_ConnectionRequest cr;
    SCCP_UserData ud;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendCR %d\n", call->GetSLR()));

    hd.context.conref = call->GetSLR();

    SCCP_SourceLocalRef slr(hd.context.conref);
    cr.AddIE(&slr);

    SCCP_ProtocolClass pclass(SCCP_PCLASS_2);
    cr.AddIE(&pclass);

    tmpdata = call->GetBSSAPData(&len);
    ud.SetUserData(tmpdata, len);
    cr.AddIE(&ud);   

    cfgdata = db.FetchRPCEntry(call->GetBssId());
    if (cfgdata)
    {
        SCCP_CalledPartyAddr cdp;
        cdp.SetPointCode(cfgdata->rpc);
        cdp.SetSSN(cfgdata->rssn);
        cdp.SetRouteByPCSSN(ITS_TRUE);
        cdp.SetInternationalRouting(ITS_TRUE);
        cr.AddIE(&cdp);

        SCCP_CallingPartyAddr cpa;
        cpa.SetPointCode(cfgdata->lpc);
        cpa.SetSSN(cfgdata->lssn);
        cpa.SetRouteByPCSSN(ITS_TRUE);
        cpa.SetInternationalRouting(ITS_TRUE);
        cr.AddIE(&cpa);

        SCCP_MessageClass::Send(ISS7_Stack, &hd, &cr);

        PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CR_SEND);
    }
    else
    {
        BSSAP_ERROR(("SendCR: Fail to send CR, no rpc found\n"));
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*      sending sccp CC 
* INPUT:
*       callref
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendCC(ITS_CTXT callRef)
{
    ITS_HDR hd;
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Call* call = NULL;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendCC\n"));

    call = BSSAP_CallDB::GetShared().Fetch(callRef);

    if (call)
    { 
        hd.context.conref = callRef;
        hd.type = ITS_SCCP;

        SCCP_ConnectionConfirm cc;

        SCCP_SourceLocalRef slr(call->GetSLR());
        cc.AddIE(&slr);

        SCCP_DestinationLocalRef dlr(call->GetDLR());
        cc.AddIE(&dlr);

        SCCP_ProtocolClass pclass(SCCP_PCLASS_2);
        cc.AddIE(&pclass);

        BSSAP_DEBUG(("SendCC: Sending CC slr %d dlr %d\n", call->GetSLR(),
                      call->GetDLR()));

        SCCP_MessageClass::Send(ISS7_Stack, &hd, &cc);
    }
    else
    {
        BSSAP_ERROR(("SendCC: Call obect not found \n"));

        ret = (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*      sending sccp CC
* INPUT:
*       callref
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
*                        ID :: D0650, ID :: D0920
*/

ITS_INT
BSSAP_SCCPHandler::SendCC(ITS_CTXT slr, ITS_CTXT dlr)
{
    ITS_HDR hd;
    ITS_INT ret = ITS_SUCCESS;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendCC\n"));

    hd.context.conref = slr;
    hd.type = ITS_SCCP;

    SCCP_ConnectionConfirm cc;

    SCCP_SourceLocalRef sl(slr);
    cc.AddIE(&sl);

    SCCP_DestinationLocalRef dl(dlr);
    cc.AddIE(&dl);

    SCCP_ProtocolClass pclass(SCCP_PCLASS_2);
    cc.AddIE(&pclass);

    BSSAP_DEBUG(("SendCC: Sending CC slr %d dlr %d\n", slr, dlr));

    ret = SCCP_MessageClass::Send(ISS7_Stack, &hd, &cc);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*      sending sccp CREF 
* INPUT:
*       callref
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendCREF(ITS_CTXT callRef)
{
    ITS_HDR hd;
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Call* call = NULL;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendCREF\n"));
                                                                                                                                              
    call = BSSAP_CallDB::GetShared().Fetch(callRef);
                                                                                                                                              
    if (call)
    {
        hd.context.conref = callRef;
        hd.type = ITS_SCCP;
                                                                                                                                              
        SCCP_ConnectionRefused cref;
                                                                                                                                              
        SCCP_DestinationLocalRef dlr(call->GetDLR());
        cref.AddIE(&dlr);
                                                                                                                                              
        SCCP_RefusalCause rc(SCCP_REF_END_USER_ORG);
        cref.AddIE(&rc);
 
        BSSAP_DEBUG(("SendCREF: Sending CREF slr %d dlr %d\n", call->GetSLR(),
                      call->GetDLR()));
                                                                                                                                              
        SCCP_MessageClass::Send(ISS7_Stack, &hd, &cref);

         ret = BSSAP_CallDB::GetShared().Remove(callRef);
    }
    else
    {
        BSSAP_ERROR(("SendCREF: Call obect not found \n"));
                                                                                                                                              
        ret = (!ITS_SUCCESS);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*      sending sccp RLSD 
* INPUT:
*       callref
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendRLSD(ITS_CTXT callRef)
{
    ITS_HDR hd;
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Call* call = NULL;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendRLSD\n"));
                                                                                                                                              
    call = BSSAP_CallDB::GetShared().Fetch(callRef);
                                                                                                                                              
    if (call)
    {
        hd.context.conref = callRef;
        hd.type = ITS_SCCP;
                      
        SCCP_Released rlsd;                                                                               
        
        SCCP_DestinationLocalRef dlr(call->GetDLR());
        rlsd.AddIE(&dlr);

        SCCP_SourceLocalRef slr(call->GetSLR());
        rlsd.AddIE(&slr);

        SCCP_ReleaseCause rc(SCCP_REF_END_USER_ORG);
        rlsd.AddIE(&rc);
                                                                                                                                              
        BSSAP_DEBUG(("SendRLSD: Sending RLSD slr %d dlr %d\n", call->GetSLR(),
                      call->GetDLR()));
                                                                                                                                              
        SCCP_MessageClass::Send(ISS7_Stack, &hd, &rlsd);

        ret = BSSAP_CallDB::GetShared().Remove(callRef);
    }
    else
    {
        BSSAP_ERROR(("SendRLSD: Call obect not found \n"));
                                                                                                                                              
        ret = (!ITS_SUCCESS);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending sccp release complete 
* INPUT:
*       hd, call object 
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
*                        ID :: D0650, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::SendRLC(ITS_HDR hd, BSSAP_Call *call)
{
    SCCP_ReleaseComplete rlc;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendRLC %d\n", call->GetSLR()));

    SCCP_SourceLocalRef slr(call->GetSLR());
    rlc.AddIE(&slr);

    SCCP_DestinationLocalRef dlr(call->GetDLR());
    rlc.AddIE(&dlr);

    SCCP_ProtocolClass pclass(SCCP_PCLASS_2);
    rlc.AddIE(&pclass);

    SCCP_MessageClass::Send(ISS7_Stack, &hd, &rlc);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       processing sccp user data 
* INPUT:
*       data, len, pc, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       status 
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0640, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::ProcessUserData(ITS_OCTET* data,
                                   ITS_UINT len,
                                   ITS_UINT pc,
                                   ITS_INT& status,
                                   BSSAP_Call* call)
{
    ITS_OCTET nwId = 0;
    BSSAP_Discriminator dis;
    BSSAP_CfgDB cfgdb;
    CFGData* cfg = NULL;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: ProcessUserData\n"));

    if (pc)
    {
        cfg = cfgdb.FetchNWIDEntry(pc);
        if (cfg)
        {
            nwId = cfg->Id;
        }
        else
        {
            return (ITS_ENOTFOUND);
        }
    }
 
    status = dis.ProcessInBSSAPMessage(data, len, call, nwId);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       sending application data(CO msg) to remote 
* INPUT:
*       call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if sent succefully
*       Error, if can't send  
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0660, ID :: D0920
*/
ITS_INT 
BSSAP_SCCPHandler::BSSAP_ProcessAPPdata(BSSAP_Call* call)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: BSSAP_ProcessAPPdata (call)\n"));

    if (call->GetSLR())
    {
        ret = SendDT1(call);
    }
    else
    { 
        ret = SendCR(call);     
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       sending application data(CL msg) to remote 
* INPUT:
*       data, len, bssId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if sent succefully
*       Error, if can't send  
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0660, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::BSSAP_ProcessAPPdata(ITS_OCTET* data, 
                                        ITS_UINT len,
                                        ITS_OCTET bssId)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: BSSAP_ProcessAPPdata (UDT)\n"));

    ret = SendUDT(data, len, bssId);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       analysing the incoming sccp info 
* INPUT:
*       event 
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
*                        ID :: D0660, ID :: D0920
*/
ITS_INT
BSSAP_SCCPHandler::BSSAP_ProcessSCCPdata(ITS_Event& event)
{
    ITS_INT ret = 0;
    ITS_UINT pc = 0;
    ITS_HDR hdr;
    ITS_OCTET data[SCCP_MAX_DATA];
    ITS_INT status = ITS_SUCCESS;
    ITS_INT length = SCCP_MAX_DATA;
    ITS_BOOLEAN dataAvl = ITS_FALSE;
    BSSAP_Call* call = NULL;
    SCCP_DestinationLocalRef *dlrtmp = NULL;
    SCCP_SourceLocalRef *slr = NULL;
    SCCP_MessageClass *sccpmsg = NULL;
    SCCP_CallingPartyAddr* clp = NULL;
    BSSAP_Interface intf;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: BSSAP_ProcessSCCPdata\n"));

    memset(&hdr, 0, sizeof(ITS_HDR));

    ret = SCCP_MessageClass::Receive(ISS7_Stack, &hdr, event, &sccpmsg);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_CRITICAL(("BSSAP_ProcessSCCPdata: Fail to receive sccp data\n"));
        if (sccpmsg)
        {
            delete sccpmsg;
        }
        ITS_EVENT_TERM(&event.GetEvent());
    }

    SCCP_UserData *ud = (SCCP_UserData *)(sccpmsg->FindIE(SCCP_PRM_DATA));

    if (ud != NULL)
    {
        memset(data, 0, SCCP_MAX_DATA);
        dataAvl = ITS_TRUE;
        ud->GetUserData(data, length);
    }

    switch (sccpmsg->GetMsgType())
    {
        case SCCP_MSG_CR:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP CR\n"));

            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CR_RECV);

            call = new BSSAP_Call();

            call->SetSLR(hdr.context.conref);

            slr = (SCCP_SourceLocalRef *)
                              sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            call->SetDLR(slr->GetRefNum());

            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: CallRefId %d Received DLR %d\n", 
                                                       hdr.context.conref, call->GetDLR()));

            // Send CC as par IMR discussion
            SendCC(hdr.context.conref, slr->GetRefNum());

            if (dataAvl)
            {
                ret = ProcessUserData(data, length, pc, status, call);
                if (status != ITS_SUCCESS)
                {
                    BSSAP_ERROR(("BSSAP_ProcessSCCPdata: Processing of 
                                                           payload failed\n"));
                }
            }
            // In case of missing payload estd. connection and
            // send indication application.
            else
            {
                intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_ESTD, call);

                ret = BSSAP_CallDB::GetShared().Add(call);
            }

            delete call;
            call = NULL;

            break;

        case SCCP_MSG_DT1:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP DT1 %d\n",
                                                     hdr.context.conref));
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DT1_RECV);
            if (dataAvl)
            {
                call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
                if (call)
                {
                    ret  = ProcessUserData(data, length, 0, status, call);
                    if (status != ITS_SUCCESS)
                    {
                        BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                               "Fail to processs user data\n")); 
                    }
                }
                else
                {
                    BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                                   "Fail to processs DT1\n"));
                }
            }
            break;

        case SCCP_MSG_RLSD:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata : Received SCCP RLSD\n"));
            BSSAP_CRITICAL(("BSSAP_ProcessSCCPdata: Received RLSD from BSS\n"));
            break;

        case SCCP_MSG_RLC:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP RLC\n"));

            call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
            if (call)
            {
                ret = BSSAP_CallDB::GetShared().Remove(hdr.context.conref);

                intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REL, call);
            }
            break;

        case SCCP_MSG_CREF:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP CREF\n"));
            call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
            if (call)
            {
                intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REF, call);
            }
            break;

        case SCCP_MSG_CC:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP CC\n"));
            dlrtmp = (SCCP_DestinationLocalRef *)
                                sccpmsg->FindIE(SCCP_PRM_DEST_LOCAL_REF);

            call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
            if (call)
            {
                call->SetDLR(dlrtmp->GetRefNum());
                BSSAP_CallDB::GetShared().Add(call);
                
                intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_ESTD, call);
            }
            else
            {
                BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                                "Fail to processs CC\n"));
            }
            break;

        case SCCP_MSG_UDT:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP UDT\n"));
            clp = (SCCP_CallingPartyAddr *)
                          sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            pc = clp->GetPointCode();
            ret = ProcessUserData(data, length, pc, status, NULL);
            if (status != ITS_SUCCESS)
            {
                BSSAP_ERROR(("BSSAP_ProcessSCCPdata: Processing of "
                                               "payload failed\n"));
            }

            break;

        default:
            BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                       "Received unknown SCCP message\n"));
            break;

    }

    if (sccpmsg)
    {
        delete sccpmsg;
        sccpmsg = NULL;
    }

    ITS_EVENT_TERM(&event.GetEvent());

    return (ITS_SUCCESS);
}
