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
 *  ID: $Id: bssap_sccphandler.cpp,v 1.6 2008/04/29 04:33:02 bsccs2 Exp $
 *
 * LOG: $Log: bssap_sccphandler.cpp,v $
 * LOG: Revision 1.6  2008/04/29 04:33:02  bsccs2
 * LOG: Fix for Mantis 2811
 * LOG:
 * LOG: Revision 1.5  2008/02/22 03:57:59  bsccs2
 * LOG: Changed for RLSD by Ashutosh
 * LOG:
 * LOG: Revision 1.4  2008/02/13 06:19:08  amaresh.prasad
 * LOG: Added for SCCP Error message handelling
 * LOG:
 * LOG: Revision 1.3  2008/02/07 10:13:54  amaresh.prasad
 * LOG: Updated for handle RLSD,CC
 * LOG:
 * LOG: Revision 1.2  2008/02/01 04:28:18  amaresh.prasad
 * LOG: Updated for released call context & passing cause
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/08/31 08:32:39  amaresh.prasad
 * LOG: Added Released Connection
 * LOG:
 * LOG: Revision 1.2  2007/08/06 06:32:50  amaresh.prasad
 * LOG: Updated for CS2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.16  2006/09/14 16:02:24  sjaddu
 * LOG: Fix for SLR and DLR values with morethan 3-octets.
 * LOG:
 * LOG: Revision 1.1.2.15  2006/02/23 05:00:49  yranade
 * LOG: Fix for issueId:3281 (Abjit).
 * LOG:
 * LOG: Revision 1.1.2.14  2005/12/13 09:44:03  mkrishna
 * LOG: Calref assignment after debug trace
 * LOG:
 * LOG: Revision 1.1.2.13  2005/12/05 09:21:32  mkrishna
 * LOG: Added pegs implementation
 * LOG:
 * LOG: Revision 1.1.2.12  2005/11/24 04:43:41  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.11  2005/10/06 08:34:28  adutta
 * LOG: Call object deleted at SendCC
 * LOG:
 * LOG: Revision 1.1.2.10  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.9  2005/08/26 20:19:13  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.8  2005/08/26 06:51:03  adutta
 * LOG: Sending UDT messages
 * LOG:
 * LOG: Revision 1.1.2.7  2005/08/21 15:44:49  adutta
 * LOG: Few changes for MO calls
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/20 18:17:47  adutta
 * LOG: Blocked the RLC
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/19 10:34:46  adutta
 * LOG: Added few more SCCP message traces
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/17 05:31:10  adutta
 * LOG: Added segmentation in DT1
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/16 10:12:29  adutta
 * LOG: Traces added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#include <sccp++.h>
#include <BSSAP++.h>
#include <bssap_common.h>
#include <bssap_cfgdb.h>
#include <bssap_calldb.h>
#include <bssap_cicdb.h>
#include <bssap_cfgdb.h>
#include <bssap_sccphandler.h>
#include <bssap_discriminator.h>
#include <bssap_pegs.h>
#include <bssap_appiddb.h> //04-02-08
#include <bssap_apiid.h> //04-02-08

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif
#if defined (CCITT)
#define FAMILY  FAMILY_ANSI
#else
#define FAMILY  FAMILY_ITU
#endif


ITS_OCTET NetworkInd = 0;

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D1060
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
    MTP3_HEADER mtp3hdr; /*National Routing Prob-IOT_UK */
    ITS_BOOLEAN isAllowed=ITS_TRUE;
    ITS_BOOLEAN isNational=ITS_FALSE;
    ITS_OCTET ni=0;
    char sio=0;


    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendUDT ni=%d\n",NetworkInd));

    cfgdata = db.FetchRPCEntry(bssId);
    if (cfgdata)
    {
           // Build MTP Header
        mtphdr.SetOPC(cfgdata->lpc);
        mtphdr.SetDPC(cfgdata->rpc);

        /* Get the NI set at the SCCP and MTP3 level and send NI from BSSAP Accordingly Guru-National MTP Routing Problem -190107*/
#if 0
       if (ROUTE_GetRouteContextStatus(cfgdata->rpc,&isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
         {
            if (ROUTE_GetRouteContextStatus(cfgdata->rpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(cfgdata->rpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                  {
                      if (ROUTE_GetRouteContextStatus(cfgdata->rpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                      {

                                // printf("SET SSN FAIL");
                      }
                      else
                      {
                             ni=MTP3_NIC_RESERVED;
                             isNational=ITS_TRUE;
                      }
                  }
                  else
                  {
                      ni=MTP3_NIC_NATIONAL;
                      isNational=ITS_TRUE;
                  }
              }
              else
              {
                 ni=MTP3_NIC_SPARE;
              }
         }
         else
         {
               ni=MTP3_NIC_INTERNATIONAL;
         }
#endif

        ni=NetworkInd;
        if((NetworkInd == MTP3_NIC_RESERVED)||(NetworkInd == MTP3_NIC_NATIONAL))
        {
                      isNational=ITS_TRUE;
                      
        }
        if(isNational)
           {
               // mtphdr.SetSIO(03); /* This SIO is checked at SCCP */
              //  mtphdr.SetNetworkIndicator(ITS_TRUE);
                 mtp3hdr.sio=(ni | MTP3_SIO_SCCP); /* This SIO is passed to mtp3 */
                 cdp.SetInternationalRouting(ITS_FALSE);
                 cpa.SetInternationalRouting(ITS_FALSE);
           }
        else
          {
                 mtp3hdr.sio=(ni | MTP3_SIO_SCCP); /* This SIO is passed to mtp3 */
                 cdp.SetInternationalRouting(ITS_TRUE);
                 cpa.SetInternationalRouting(ITS_TRUE);
          }

        BSSAP_DEBUG(("SIO = 0x%x  NI=0x%x \n", mtp3hdr.sio,ni));

        ud.SetHeader(mtp3hdr);

        //sio=MTP3_HDR_GET_SIO_CCITT(ud.GetHeader());
        sio=MTP3_HDR_GET_SIO(ud.GetHeader());

        // Build Called party address
        cdp.SetPointCode(cfgdata->rpc);
        cdp.SetSSN(cfgdata->rssn);
        cdp.SetRouteByPCSSN(ITS_TRUE);
        ud.AddIE(&cdp);

        // Build Calling party address
        cpa.SetPointCode(cfgdata->lpc);
        cpa.SetSSN(cfgdata->lssn);
        cpa.SetRouteByPCSSN(ITS_TRUE);
        ud.AddIE(&cpa);

          
#ifdef ASHU

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

#endif


    }
    else
    {
        BSSAP_ERROR(("SendUDT: Fail to send UDT, no rpc\n"));

        return (ITS_SUCCESS);
    }

    pc.SetProtocolClass(pclass);
    ud.AddIE(&pc);

    udt.SetUserData(data, (ITS_INT &)len);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D1060
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

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendDT1 %d\n", call->GetSLR()));

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

   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DT1_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_DT1_SEND,call->GetBssId());

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D1060
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
    MTP3_HEADER mtp3hdr; /*National Routing Prob-IOT_UK */
    MTP3_Header mtphdr;
    ITS_BOOLEAN isAllowed=ITS_TRUE;
    ITS_BOOLEAN isNational=ITS_FALSE;
    ITS_OCTET ni=0;
    SCCP_CalledPartyAddr cdp;
    SCCP_CallingPartyAddr cpa;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendCR %d ni %d \n", call->GetSLR(),NetworkInd));

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
       // Build MTP Header
        mtphdr.SetOPC(cfgdata->lpc);
        mtphdr.SetDPC(cfgdata->rpc);

       /* Get the NI set at the SCCP and MTP3 level and send NI from BSSAP Accordingly Guru-National MTP Routing Problem -190107*/

#if 0
       if (ROUTE_GetRouteContextStatus(cfgdata->rpc,&isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
         {
            if (ROUTE_GetRouteContextStatus(cfgdata->rpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(cfgdata->rpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                  {
                      if (ROUTE_GetRouteContextStatus(cfgdata->rpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),cfgdata->rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                      {

                                 //printf("SET SSN FAIL");
                      }
                      else
                      {
                             ni=MTP3_NIC_RESERVED;
                             isNational=ITS_TRUE;
                      }
                  }
                  else
                  {
                      ni=MTP3_NIC_NATIONAL;
                      isNational=ITS_TRUE;
                  }
              }
              else
              {
                 ni=MTP3_NIC_SPARE;
              }
         }
         else
         {
               ni=MTP3_NIC_INTERNATIONAL;
         }
#endif
         ni=NetworkInd;
        if((NetworkInd == MTP3_NIC_RESERVED)||(NetworkInd == MTP3_NIC_NATIONAL))
        {
                      isNational=ITS_TRUE;
        }

        if(isNational)
           {
              mtphdr.SetSIO(03); /* This SIO is checked at SCCP */
              mtphdr.SetNetworkIndicator(ITS_TRUE);
              mtp3hdr.sio=(ni | MTP3_SIO_SCCP); /* This SIO is passed to mtp3 */
              cdp.SetInternationalRouting(ITS_FALSE);
              cpa.SetInternationalRouting(ITS_FALSE);
           }
        else
          {  
              mtp3hdr.sio=(ni | MTP3_SIO_SCCP); /* This SIO is passed to mtp3 */
              cdp.SetInternationalRouting(ITS_TRUE);
              cpa.SetInternationalRouting(ITS_TRUE);
          }

          /* Set MTP3 HEADER */
         cr.SetHeader(mtp3hdr);
         cdp.SetPointCode(cfgdata->rpc);
         cdp.SetSSN(cfgdata->rssn);
         cdp.SetRouteByPCSSN(ITS_TRUE);
         cr.AddIE(&cdp);

         cpa.SetPointCode(cfgdata->lpc);
         cpa.SetSSN(cfgdata->lssn);
         cpa.SetRouteByPCSSN(ITS_TRUE);
         cr.AddIE(&cpa);

#ifdef ASHU



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


#endif
        SCCP_MessageClass::Send(ISS7_Stack, &hd, &cr);
    }
    else
    {
        BSSAP_ERROR(("SendCR: Fail to send CR, no rpc found\n"));
    }

   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CR_SEND);
       BSSAPPEG_IncrPeg(PEG_BSSAP_CR_SEND,call->GetBssId());

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D1060
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
*      sending sccp CC as CR message received & no waiting from BSC-APP
* INPUT:
*       SLR & DLR
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
* Amaresh Prasad  29-04-08
*/
ITS_INT
BSSAP_SCCPHandler::SendCC(ITS_CTXT slr, ITS_CTXT dlr)
{
    ITS_HDR hd;
    ITS_INT ret = ITS_SUCCESS;

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendCC by Stack\n"));

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D1060
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D1060
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
/************** Added by Amaresh for release of CALL context & CIC maintained by BSSAP ****************/
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
* Amaresh Prasad   13-08-2007   IMR-BSC-SDS-BSAP-CS2
*
*/
ITS_INT
BSSAP_SCCPHandler::SendRLSD(ITS_CTXT callRef,ITS_OCTET cause)
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

       /* SCCP_ReleaseCause rc(SCCP_REF_END_USER_ORG); */
					SCCP_ReleaseCause rc(cause); //24-04-08
        rlsd.AddIE(&rc);

  /*One Optional pamameter are necessary due to extra byte problem*/
#if defined (CCITT)
       	SCCP_Importance Imp(7);
       	rlsd.AddIE(&Imp);
#else
          // Data
        SCCP_UserData ud;
        int len = 10;                              //len=3-130
        ITS_OCTET data[10];
        // fill data
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i; /*garbauge*/
        }
        ud.SetUserData(data, len);
        rlsd.AddIE(&ud);
#endif		     
        BSSAP_DEBUG(("SendRLSD: Sending RLSD from BSC-APP to BSSAP-SCCP slr %d dlr %d\n", call->GetSLR(),
                      call->GetDLR()));


        SCCP_MessageClass::Send(ISS7_Stack, &hd, &rlsd);

        ret = BSSAP_CallDB::GetShared().Remove(callRef);
    }
    else
    {
        BSSAP_ERROR(("SendRLSD: cref[%04x] object not found \n",callRef));
        ret = (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*      sending sccp Abnormal RLSD
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
* Amaresh Prasad   05-02-2008   IMR-BSC-SDS-BSAP-CS2
*
*/

ITS_INT
BSSAP_SCCPHandler::SendAbnormalRLSD(ITS_CTXT appid,ITS_OCTET cause)
{
    ITS_HDR hd;
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_AppId* callapp = NULL;//Amaresh04-02-08

    BSSAP_DEBUG(("BSSAP_SCCPHandler: SendAbnormalRLSD\n"));

    callapp = BSSAP_AppidDB::GetShared().Fetch(appid);

    if (callapp)
    {
        hd.context.conref = callapp->GetSLR();
        hd.type = ITS_SCCP;

        SCCP_Released rlsd;

        SCCP_DestinationLocalRef dlr(callapp->GetDLR());
        rlsd.AddIE(&dlr);

        SCCP_SourceLocalRef slr(callapp->GetSLR());
        rlsd.AddIE(&slr);

/*       SCCP_ReleaseCause rc(SCCP_REF_END_USER_ORG);*/
				SCCP_ReleaseCause rc(cause); //24-04-08
        rlsd.AddIE(&rc);
  /*One Optional pamameter are necessary due to extra byte problem*/
#if defined (CCITT)
       	SCCP_Importance Imp(7);
       	rlsd.AddIE(&Imp);
#else
          // Data
        SCCP_UserData ud;
        int len = 10;                              //len=3-130
        ITS_OCTET data[10];
        // fill data
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i; /*garbage*/
        }
        ud.SetUserData(data, len);
        rlsd.AddIE(&ud);
#endif
		     
        BSSAP_DEBUG(("SendAbnormalRLSD: Sending RLSD from BSC-APP to BSSAP-SCCP slr %d dlr %d\n", callapp->GetSLR(),
                      callapp->GetDLR()));


        SCCP_MessageClass::Send(ISS7_Stack, &hd, &rlsd);

        ret = BSSAP_AppidDB::GetShared().Remove(appid);
    }

        else
    {
        BSSAP_ERROR(("SendRLSD: Call obect not found \n"));
        ret = (!ITS_SUCCESS);
    }

    return (ret);
}

/************** Addition completed by Amaresh for release of CALL context & CIC maintained by BSSAP ****************/





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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0790, ID :: D1060
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0810, ID :: D1060
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0810, ID :: D1060
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0810, ID :: D1060
* Abjit     22-02-2006                              Fix for issue id:3281. 
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
    BSSAP_AppId* callapp = NULL;//Amaresh04-02-08
    ITS_CTXT appId = 0;//Amaresh04-02-08
		BSSAP_CfgDB cfgdb; //Amaresh08-05-08
    CFGData* cfg = NULL; //Amaresh08-05-08
		ITS_OCTET nwId = 0;//Amaresh08-05-08
    BSSAP_Interface intf;
    SCCP_DestinationLocalRef *dlrtmp = NULL;
    SCCP_SourceLocalRef *slr = NULL;
    SCCP_MessageClass *sccpmsg = NULL;
    SCCP_CallingPartyAddr* clp = NULL;
    SCCP_RefusalCause *refuse_cause = NULL;
    SCCP_ReleaseCause *release_cause = NULL;
    SCCP_ErrorCause   *err_cause = NULL; //Amaresh 11-02-08
    ITS_OCTET rcause = NULL;
    MTP3_HEADER   mtp3;
    ITS_EVENT evt;
    ITS_OCTET ni=0;
/*Modification Start by Amaresh as on dated 26-08-14 */
    ITS_OCTET cicst = 0;
/*Modification Stop by Amaresh as on dated 26-08-14 */
    int  offset = 0;
    /* Ashutosh 7-Jan-2011*/
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    /* Ashutosh 7-Jan-2011*/
    static ITS_INT udtCount = 0;
    //BSSAP_DEBUG(("BSSAP_SCCPHandler: BSSAP_Process MSC-SCCPdata\n")); 


    offset++;
    offset += sizeof(ITS_CTXT);
    memset((void*)&mtp3, 0, sizeof(MTP3_HEADER));
    memcpy((void*)&mtp3, &event.GetData()[offset], sizeof(MTP3_HEADER));
    ITS_OCTET sio=MTP3_HDR_GET_SIO(mtp3);
    ITS_UINT dpc=MTP3_RL_GET_DPC_VALUE(mtp3.label);
    ITS_UINT opc=MTP3_RL_GET_OPC_VALUE(mtp3.label);
    //BSSAP_DEBUG(("BSSAP_SCCPHandler:MTP3 HEADER sio %d dpc %d opc %d:\n",sio,dpc,opc));
    pc=opc;

    memset(&hdr, 0, sizeof(ITS_HDR));
    ret = SCCP_MessageClass::Receive(ISS7_Stack, &hdr, event, &sccpmsg);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_CRITICAL(("BSSAP_ProcessSCCPdata: Fail to receive msc-sccp data\n"));
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
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received MSC-SCCP CR\n"));
      /*      setconfig_status(dpc,pc,254,SCCP_SCMG_SS_ALLOWED,ni); */

       //     PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CR_RECV); 

               	call = new BSSAP_Call();
                call->SetSLR(hdr.context.conref);
                slr = (SCCP_SourceLocalRef *)sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
                call->SetDLR(slr->GetRefNum());

                BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: CR received from remote\n"));
								BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: CallRefId %d Received DLR %d\n",
                                                       hdr.context.conref, call->GetDLR()));
								// Send CC as per Requirement by Amaresh as on dated 29-04-08
                SendCC(hdr.context.conref, slr->GetRefNum());
               	if (dataAvl)
								{
										ret = ProcessUserData(data, length, pc, status, call);
               			if (status != ITS_SUCCESS)
               			 {
                    BSSAP_ERROR(("BSSAP_ProcessSCCPdata: Processing of " 
                                                   "MSC-Message payload failed\n"));
                			}
                   cfg = cfgdb.FetchNWIDEntry(pc);
                   if (cfg)
                     {
                          nwId = cfg->Id;
                          BSSAPPEG_IncrPeg(PEG_BSSAP_CR_RECV,nwId);
                     }
//                BSSAPPEG_IncrPeg(PEG_BSSAP_CR_RECV,call->GetBssId());
							}
							else
							{
								BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: CR received from remote have no user data\n"));
						    ret = BSSAP_CallDB::GetShared().Add(call);
								if(ret != ITS_SUCCESS)
								{
								BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: CR received from remote CAll is not added in DB\n"));
								}
								else
								{
								BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: CR received from remote CAll is added in DB\n"));
								}
                   cfg = cfgdb.FetchNWIDEntry(pc);
                   if (cfg)
                     {
                          nwId = cfg->Id;
                          BSSAPPEG_IncrPeg(PEG_BSSAP_CR_RECV,nwId);
                     }
							}
                delete call;
                call = NULL;
            
            break;

       case SCCP_MSG_DT1:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received  MSC-SCCP DT1 %d\n",
                                                     hdr.context.conref));

//            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DT1_RECV);

            if (dataAvl)
            {
                call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
                if (call)
                {
                    ret  = ProcessUserData(data, length, pc, status, call);
                    if (status != ITS_SUCCESS)
                    {
                        BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                               "Fail to processs MSC data for cref[%04x]\n",hdr.context.conref)); 
                    }
                   BSSAPPEG_IncrPeg(PEG_BSSAP_DT1_RECV,call->GetBssId());
                }
                else
                {
                    BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                                   "Fail to processs  MSC-DT1 for cref[%04x]\n",hdr.context.conref));
                }
            }
            break;

       case SCCP_MSG_RLSD:
            call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
             /* Added by Amaresh for RLSD  from peer to free appid with slr & dlr store in APPIDDB 04-02-08*/
            if(call)
               {
                    appId = call->GetAppId();
           //         callapp = BSSAP_AppidDB::GetShared().Fetch(appId);
            BSSAP_CRITICAL(("BSSAP_ProcessSCCPdata : Received SCCP RLSD cref[%04x] AppId[%04x]\n",hdr.context.conref,appId));
               }
	    else
	    {
            BSSAP_CRITICAL(("BSSAP_ProcessSCCPdata : Received SCCP RLSD cref[%04x]\n",hdr.context.conref));
	    }
            /* Added by Amaresh for RLSD from peer to free appid with slr & dlr store in APPIDDB 04-02-08*/
            /*Enhanced by Amaresh for Extracting & Passing cause */
            release_cause = (SCCP_ReleaseCause *)sccpmsg->FindIE(SCCP_PRM_RELEASE_CAUSE);
            if(release_cause != NULL)
              {
                 rcause = (ITS_OCTET)release_cause->GetCause();
                 BSSAP_DEBUG(("BSSAP received SCCP Cause: Received SCCP RLSD\n"));
              }
            /*Enhanced by Amaresh for Extracting & Passing cause */

	         if (call)
           {
               cic = call->GetCIC();
/*Modification Start by Amaresh as on dated 26-08-14 */
               cicst = call->GetCicst();
							 if (cicst != CALL_ST_IDLE)
							 {
               		if (cic)
	        		 		{
						 				crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_CLEAR_COMMAND,call->GetBssId());
		 								if (crec)
	             			{
		           					// By this we know clearly channel is released
		           					call->SetChannelAlloc(ITS_FALSE);
		           					crec->callState = CALL_ST_IDLE;	  
			   								ret = cicdb.ModifyCICRecord(cic, crec,BSSAP_MSG_CLEAR_COMMAND);
	                 			if (ret != ITS_SUCCESS)
	       	          		{
	       		     					BSSAP_DEBUG(("ProcessRLSDCommand:CIC Modify failed \n"));
			   								}
					              BSSAP_CRITICAL(("RLSD From SCCP:CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] AppId[%04x] \n",cic,hdr.context.conref,call->GetAppId()));
		      					}
		 							}
	         				else
		    					{
		      					BSSAP_DEBUG(("ProcessRLSDCommand: No cic found\n"));
		    					}
								}
								else
								{
		      					BSSAP_DEBUG(("ProcessRLSDCommand: Not to Cicrec Fetch & Modify Cicst:%d\n",cicst));
								}
/*Modification Stop by Amaresh as on dated 26-08-14 */
		      /*******************************************/
		 
/*               intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REL, call);commented by Amaresh */
              	 intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REL,rcause,call); /*passing cause */
                 ret = BSSAP_CallDB::GetShared().Remove(hdr.context.conref);
          }
           /* Added by Amaresh for CREF from peer to free appid with slr store in APPIDDB 04-02-08*/
         // if(callapp)
           //  {
                BSSAP_AppidDB::GetShared().Remove(appId);
          //   }
          /* Added by Amaresh for CREF from peer to free appid with slr store in APPIDDB 04-02-08*/
            break;

           /* Added by Amaresh for ERR messge handelling 11-02-08*/
        case SCCP_MSG_ERR:
                 BSSAP_DEBUG(("BSSAP_ProcessSCCPdata : Received SCCP ERR message\n"));
                 call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);

            if(call)
              {
                 appId = call->GetAppId();
                 callapp = BSSAP_AppidDB::GetShared().Fetch(appId);
              }

            /*Enhanced by Amaresh for Extracting & Passing cause */
            err_cause = (SCCP_ErrorCause *)sccpmsg->FindIE(SCCP_PRM_ERROR_CAUSE);
            if(err_cause != NULL)
             {
                  rcause = (ITS_OCTET)err_cause->GetCause();
                  BSSAP_DEBUG(("BSSAP received SCCP Cause: Received SCCP Error message\n"));
             }
            /*Enhanced by Amaresh for Extracting & Passing cause */

            if (call)
             {
/*               intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REL, call);commented by Amaresh */
                 intf.DispatchSccpIndToApp(BSSAP_MD_SCCP,BSSAP_CON_ERR,rcause,call); /*passing cause */
                 ret = BSSAP_CallDB::GetShared().Remove(hdr.context.conref);
            }
           if(callapp)
            {
                ret = BSSAP_AppidDB::GetShared().Remove(appId);
            }
            break;
            /* Addition completed by Amaresh for ERR messge handelling 11-02-08*/

       case SCCP_MSG_RLC:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP RLC\n"));
            BSSAP_CRITICAL(("BSSAP_ProcessSCCPdata: Received RLC from MSC\n"));
            break;

       case SCCP_MSG_CREF:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP CREF\n"));
            call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
            /* Added by Amaresh for CREF from peer to free appid with slr store in APPIDDB 04-02-08*/
            if(call)
               {
                  appId = call->GetAppId();
                  callapp = BSSAP_AppidDB::GetShared().Fetch(appId);
               }
            /* Added by Amaresh for CREF from peer to free appid with slr store in APPIDDB 04-02-08*/
            /*Enhanced by Amaresh for Extracting & Passing cause */
            refuse_cause = (SCCP_RefusalCause *)sccpmsg->FindIE(SCCP_PRM_REFUSAL_CAUSE);
            if(refuse_cause != NULL)
            {
               rcause= (ITS_OCTET)refuse_cause->GetCause();
               BSSAP_DEBUG(("BSSAP received SCCP Cause: Received SCCP REF\n"));
            }
               /*Enhanced by Amaresh for Extracting & Passing cause */	    
	         if (call)
            {
               /*  intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REF, call);commented by Amaresh */
               		intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_REF,rcause,call);
                  ret = BSSAP_CallDB::GetShared().Remove(hdr.context.conref);
            }
           /* Added by Amaresh for CREF from peer to free appid with slr store in APPIDDB 04-02-08*/
          if(callapp)
            {
                ret = BSSAP_AppidDB::GetShared().Remove(appId);
            }
          /* Added by Amaresh for CREF from peer to free appid with slr store in APPIDDB 04-02-08*/
            break;

       case SCCP_MSG_CC:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP CC\n"));
            dlrtmp = (SCCP_DestinationLocalRef *)
                                sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF); //Fix for 3281.

            call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
            if (call)
            {
                call->SetDLR(dlrtmp->GetRefNum());
                BSSAP_CallDB::GetShared().Add(call);
                BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SLR %d\n",
                                                         dlrtmp->GetRefNum())); //Fix for 3281. 

                /* Added by Amaresh for CC from peer to add dlr & slr store in APPIDDB 04-02-08*/
                appId = call->GetAppId();
                callapp = BSSAP_AppidDB::GetShared().Fetch(appId);
                if(callapp)
                {
                  callapp->SetDLR(dlrtmp->GetRefNum());
                  BSSAP_AppidDB::GetShared().Add(callapp);
                  /* Added by Amaresh for CC from peer to add dlr & slr store in APPIDDB 04-02-08*/
                  /* No cause for CC message  */        
              		intf.DispatchSccpIndToApp(BSSAP_MD_SCCP, BSSAP_CON_ESTD,0,call);
		             /* Changed by Amaresh as on dated 16-03-09 for emergency call for CC in piggyback mode */            }
        if (dataAvl)
            {
              BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received  MSC-SCCP CC messge with piggyback mode %d\n"));
               call = BSSAP_CallDB::GetShared().Fetch(hdr.context.conref);
                if (call)
                {
                    ret  = ProcessUserData(data, length, 0, status, call);
                    if (status != ITS_SUCCESS)
                    {
                        BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                               "Fail to processs MSC data\n"));
                    }
                }
                else
                {
                    BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                                   "Fail to processs  MSC-DT1\n"));
                }
            }
     /* Changed by Amaresh as on dated 16-03-09 for emergency call for CC in piggyback mode */
            }
            else
            {
                BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                                "Fail to processs CC\n"));
            }
            break;

       case SCCP_MSG_UDT:
            BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Received SCCP UDT\n"));
/*
	    if(udtCount == 0)
	    {
               BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: Setting SccpAllowedFlag and route ssnstatus TRUE for First UDT received\n"));
	       setconfig_status(dpc,pc,254,SCCP_SCMG_SS_ALLOWED,ni);
	       udtCount++;
	    }
*/
            clp = (SCCP_CallingPartyAddr *)
                          sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            if(clp)
            {
               pc = clp->GetPointCode();
              ret = ProcessUserData(data, length, pc, status, NULL);
              if (status != ITS_SUCCESS)
              {
                  BSSAP_ERROR(("BSSAP_ProcessSCCPdata: Processing of "
                                                 "MSC-Messagepayload failed\n"));
              }
            }

            break;

        default:
            BSSAP_ERROR(("BSSAP_ProcessSCCPdata: "
                                       "Received unknown MSC-SCCP message\n"));
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
