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
 *  ID: $Id: bssap_interface.cpp,v 1.6 2008/04/29 04:33:02 bsccs2 Exp $
 *
 * LOG: $Log: bssap_interface.cpp,v $
 * LOG: Revision 1.6  2008/04/29 04:33:02  bsccs2
 * LOG: Fix for Mantis 2811
 * LOG:
 * LOG: Revision 1.5  2008/02/07 10:11:18  amaresh.prasad
 * LOG: Updated for appid entry
 * LOG:
 * LOG: Revision 1.4  2008/02/01 02:41:33  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2008/02/01 04:26:02  amaresh.prasad
 * LOG: Updated for release of CALL context & CIC
 * LOG:
 * LOG: Revision 1.2  2007/10/30 06:42:03  amaresh.prasad
 * LOG: Updated for NWMSG(PAUSE,RESUME etc ) including PC & SSN to application
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.4  2007/09/27 06:30:26  amaresh.prasad
 * LOG: Updated Traces
 * LOG:
 * LOG: Revision 1.3  2007/08/31 07:01:02  amaresh.prasad
 * LOG: Added Released Connection
 * LOG:
 * LOG: Revision 1.2  2007/08/06 06:31:39  amaresh.prasad
 * LOG: Updated for CS2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.15  2006/07/14 16:59:39  sjaddu
 * LOG: Connection Id is changed to U INT.
 * LOG:
 * LOG: Revision 1.1.2.14  2005/12/14 11:13:55  adutta
 * LOG: Heap address passed to app.
 * LOG:
 * LOG: Revision 1.1.2.13  2005/12/13 09:37:18  mkrishna
 * LOG: Stack is opreting on his own memory
 * LOG:
 * LOG: Revision 1.1.2.12  2005/12/12 09:01:19  mkrishna
 * LOG: Memory allocated for event, before adding it to queue
 * LOG:
 * LOG: Revision 1.1.2.11  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.10  2005/09/29 07:38:50  adutta
 * LOG: Error handling for UDT messages
 * LOG:
 * LOG: Revision 1.1.2.9  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.8  2005/08/26 20:19:13  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.7  2005/08/26 06:42:26  adutta
 * LOG: Bssmap UDT dispatch
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/21 15:43:58  adutta
 * LOG: Error checks for PutEvent
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/19 20:06:25  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/19 10:34:06  adutta
 * LOG: Removed unwanted cleanup
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/16 10:12:29  adutta
 * LOG: Traces added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             
#include <engine++.h>
#include <sccp++.h>
#include <bssap.h>
#include <bssap_common.h>
#include <bssap_call.h>
#include <bssap_cicdb.h>
#include <bssap_calldb.h> /* Added by Amaresh dor Call DB */
#include <bssap_cfgdb.h>
#include <bssap_interface.h>
#include <bssap_sccphandler.h>
#include <bssap_appiddb.h> //04-02-08
#include <bssap_apiid.h> //04-02-08



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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0070, ID :: D0120,
*                        ID :: D0130, ID :: D1060
*/
ITS_INT
BSSAP_Api::SendBSSAPMessage(ITS_CTXT& calref)
{
    ITS_EVENT ev;
    ITS_USHORT len = 0;
    ITS_INT ret = 0;
    ITS_OCTET mType = 0;

    BSSAP_DEBUG(("BSSAP_Api: SendBSSAPMessage DISC[0x%x]\n",this->GetMssgDisc()));

    //BSSAP_DEBUG(("===== App ID  : ::: %d", this->GetAppId()));
    if (this->GetMssgDisc() == BSSAP_MD_DTAP)
    {
        ITS_EVENT_INIT(&ev, BSSAP_DTAP_SRC, sizeof(BSSDtap)); 
  
        memcpy(ev.data, &bd, sizeof(BSSAPData));
    }
    else if (this->GetMssgDisc() == BSSAP_MD_BSSMAP)
    {
        mType = this->GetMssgType();

        if (mType == BSSAP_MSG_COMPLETE_LAYER3_INFO)
        {
            BSSAP_DEBUG(("SendBSSAPMessage : L3 Message\n"));

            ret = SCCP_GetNextLocalRef(ISS7_Stack, &calref);
            this->SetCallRef(calref);

            ITS_EVENT_INIT(&ev, BSSAP_LAYER3_SRC, sizeof(BSSMap));
        }
        else
        {
            ITS_EVENT_INIT(&ev, BSSAP_MAP_SRC, sizeof(BSSMap)); 
        }

        memcpy(ev.data, &bd, sizeof(BSSAPData));
    }
    else if (this->GetMssgDisc() == BSSAP_MD_BS_SCCP)
    {
       BSSAP_DEBUG(("SendBSSAPMessage : BSSAP_MD_SCCP & SCCP REL Message\n"));

       ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, sizeof(BSSMap)); 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0070, ID :: D0120,
*                        ID :: D0140, ID :: D1060
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
*       Adding CIC information in to CIC database 
* INPUT:
*       bscId, pcm, startTs, endTS 
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
*                        ID :: D0070, ID :: D0120,
*                        ID :: D0150, ID :: D1060
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
*       sending SCCP CC message to remote 
* INPUT:
*       callRef
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
*                        ID :: D0070, ID :: D0120,
*                        ID :: D0160, ID :: D1060
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
*       sending SCCP CREF message to remote
* INPUT:
*       callRef
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
*                        ID :: D0070, ID :: D0120,
*                        ID :: D0160, ID :: D1060
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

/************** Added by Amaresh for release of CALL context & CIC maintained by BSSAP ****************/
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
* Amaresh Prasad   13-08-2007   IMR-BSC-SDS-BSAP-CS2
*
*/

ITS_INT
BSSAP_Api::ReleasedConnection(ITS_CTXT callRef,ITS_CTXT appId,ITS_OCTET cause)
{
    BSSAP_SCCPHandler sccpHdl;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    BSSAP_Call* call = NULL;
    BSSAP_AppId* callapp = NULL;//Amaresh04-02-08
    ITS_CTXT slr = 0; //Amaresh04-02-08
    ITS_INT ret =ITS_SUCCESS;
   /* Release CIC for CALLREFID */

   BSSAP_CRITICAL(("ReleasedConnection:SCCP Release from BSC-APP: cref[%04x] : AppId[%04x] \n",callRef,appId));

    callapp = BSSAP_AppidDB::GetShared().Fetch(appId);//Amaresh04-02-08
        if(callapp)
        {
          slr = callapp->GetSLR();
        }
     /* Note :R2-HA:handling for case when callref receive from app is zero.i.e if switchover occur just after sending CR and no CC recieve yet*/ 
	if(callRef == 0)
	{
	 /* call = BSSAP_CallDB::GetShared().Fetch(slr);*//* Commented By Amaresh as on dated 05-09-14*/
	}
	else
	{
	  call = BSSAP_CallDB::GetShared().Fetch(callRef);
	}
	/*R2-HA: End*/
      if(call)
        {
             cic = call->GetCIC();
             if (cic)
              {
                crec = cicdb.FetchCICRecord(cic,0,call->GetBssId());
                if (crec)
                   {
                     // By this we know clearly channel is released
                     call->SetChannelAlloc(ITS_FALSE);
                     crec->callState = CALL_ST_IDLE;
                     ret = cicdb.ModifyCICRecord(cic, crec,0);
                     BSSAP_CRITICAL(("ReleasedConnection:SCCP Release From BSC-APP:CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] AppId[%04x]\n",cic,callRef,appId));
                  }
             }
        ret = BSSAP_AppidDB::GetShared().Remove(appId); //Amaresh 04-02-08
        BSSAP_CRITICAL(("BSSAP_Api: Sending RLSD message towards BSC-APP-->BSSAP for cref[[%04x] AppId[%04x]  \n",callRef,appId));
        ret = sccpHdl.SendRLSD(callRef,cause); //24-04-08
        return (ret);
      }

     /* Added by Amaresh for RLSD message initiated by BSC-APP to BSSAP stack  04-02-08*/
     else
       {
          BSSAP_CRITICAL(("BSSAP_Api: Sending RLSD message towards BSC-APP-->BSSAP for cref[%04x] AppId[%04x] \n",slr,appId));
          BSSAP_CallDB::GetShared().Remove(slr);
          ret = sccpHdl.SendAbnormalRLSD(appId,cause); //24-04-08
          return (ret);
       }
      /* Added by Amaresh for RLSD message initiated by BSC-APP to BSSAP stack  04-02-08*/
      //     BSSAP_WARNING(("No cic found for Release \n")); 04-02-08
      // return (ITS_SUCCESS); 30-01-08

}

#if 0
ITS_INT
BSSAP_Api::ReleasedConnection(ITS_CTXT callRef)
{
    BSSAP_SCCPHandler sccpHdl;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    BSSAP_Call* call = NULL;
    ITS_INT ret =ITS_SUCCESS; 
   /* Release CIC for CALLREFID */

   BSSAP_DEBUG(("BSSAP_SCCPHandler: RELEASE ALL CIC \n"));

    call = BSSAP_CallDB::GetShared().Fetch(callRef);
    cic = call->GetCIC();

    if (cic)
    {
        crec = cicdb.FetchCICRecord(cic);
        if (crec)
        {
            // By this we know clearly channel is released
            call->SetChannelAlloc(ITS_FALSE);

            crec->callState = CALL_ST_IDLE;
            ret = cicdb.ModifyCICRecord(cic, crec);
        }
    }
    else
    {
        BSSAP_WARNING(("No cic found for Release \n"));

        return (ITS_SUCCESS);
    }
/* Release CIC for CALLREFID */

     BSSAP_DEBUG(("BSSAP_Api: Sending RLSD message towards  BSC-APP-->BSSAP \n"));  
    ret = sccpHdl.SendRLSD(callRef); 
    return (ret);
}
#endif
/************** Addition completed by Amaresh for release of CALL context & CIC maintained by BSSAP ****************/


/*implementation:internal
*
* PURPOSE:
*       sending SCCP status information to application
* INPUT:
*       msgType, msgCode, call object 
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
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
*/
ITS_INT
BSSAP_Interface::DispatchSccpIndToApp(ITS_OCTET msgType, ITS_OCTET msgCode,ITS_OCTET cause,BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_USHORT dest = 0;
    BSSAP_Api *mSccp = new BSSAP_Api(); //Application has to delete this memory
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Interface: DispatchSccpIndToApp\n"));
   /*Added by Amaresh for RLSD handelling in case of new BSS HO failure dated 19-05-08*/
		if (call->IsHandOver())
    {
				if (call->IsHandOverNewBss())
				{
	    		BSSAP_DEBUG(("BSSAP_Interface: ProcessDispatchSccpIndToApp  New Bss HO is present \n"));
					if (call->IsHandOverFailure())
				   {
			     			BSSAP_DEBUG(("BSSAP_Interface: ProcessDispatchSccpIndToApp  HoFailure present in call \n"));
								call->SetHandOverFailure(0);
								call->SetHandOverNewBss(0);
								call->SetHandOver(0);
							 return (!ITS_SUCCESS);
					}
				else
				  { 
				     	BSSAP_DEBUG(("BSSAP_Interface: ProcessDispatchSccpIndToApp No HoFailure present in call \n"));
					}
			}
		}
    /*Addition completed by Amaresh for RLSD handelling in case of new BSS HO failure dated 19-05-08*/
    mSccp->SetCallRef(call->GetSLR());
    mSccp->SetAppId(call->GetAppId()); 
    mSccp->SetMssgDisc(msgType);
    mSccp->SetMssgType(msgCode);
    /* Enhanced by Amaresh for cause */
    if(mSccp->GetMssgType() == BSSAP_CON_REL || mSccp->GetMssgType() == BSSAP_CON_REF)
    {
       mSccp->SetERRCause(cause);
       BSSAP_DEBUG(("CAUSE value:cause  %d\n", cause)); 
       BSSAP_DEBUG(("BSSAP_Interface: SET cause value for RLSD & CREF\n"));
    }
    /* Enhanced by Amaresh for cause */
                                                                                                                                          
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSAP_Api));
    memcpy(ev.data, &mSccp, sizeof(&mSccp));
                                                                                                        
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_ERROR(("DispatchSccpIndToApp: Bad route to App %d\n",
                                                       hdr.context.conref));
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("DispatchSccpIndToApp: Transport put event failed\n"));
        }
    }
                                                                                                                               
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       sending DTAP msg to application transperantly
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
*/
ITS_INT
BSSAP_Interface::DispatchDtapToApp(BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_INT len = 0;
    ITS_USHORT dest = 0;
    ITS_OCTET* data = NULL;
    BSSDtap *mDtap = new BSSDtap(); //Application has to delete this memory

    BSSAP_DEBUG(("BSSAP_Interface: DispatchDtapToApp\n"));

    mDtap->SetCallRef(call->GetSLR());
    mDtap->SetAppId(call->GetAppId());
    mDtap->SetMssgDisc(BSSAP_MD_DTAP);
    mDtap->SetMssgType(call->GetMssgType());

    data = call->GetBSSAPData(&len);
    mDtap->SetDTAPdata(data, len);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSDtap));
    memcpy(ev.data, &mDtap, sizeof(&mDtap));
    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = call->GetSLR();
  
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_ERROR(("DispatchDtapToApp: Bad route to App %d\n", 
                                                       hdr.context.conref));
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("DispatchDtapToApp: Transport put event failed %d\n",
                                                      hdr.context.conref));
        }
    } 

    return (ITS_SUCCESS);
}
/*implementation:internal
*
* PURPOSE:
*       sending MAPErr message to application
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
* Amaresh Prasad  03-07-2008   VNL-BSC-CS2-HO Implementation
*/

ITS_INT
BSSAP_Interface::DispatchMapErrToApp(BSSAP_Call* call, BSSAP_Message* mdata, ITS_OCTET cause)
{
    ITS_USHORT dest;
    ITS_CTXT cref = 0;
    ITS_INT ret;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_OCTET* data = NULL;
    ITS_INT len = 0;
    BSSMap *mMap = new BSSMap(); //Application has to delete this memory
		
		call->SetMssgType(BSSAP_HANDOVER_FAILURE_IND); 
		call->SetHandOverFailureCause(cause);		
	  cref = call->GetSLR();
    mMap->SetCallRef(cref);
    mMap->SetAppId(call->GetAppId());
    mMap->SetMssgDisc(BSSAP_FAILURE_IND);
    mMap->SetMssgType(call->GetMssgType());
    mMap->SetBssId(call->GetBssId()); //Added by Amaresh as on dated 09-05-08
    mMap->SethofaCause(call->GetHandOverFailureCause());
		data = call->GetBSSAPData(&len);

    BSSAP_DEBUG(("BSSAP STack MapErrToApp*******:App Id = %d \n", mMap->GetAppId()));
    mMap->SetMAPdata(data, len);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSMap));
    memcpy(ev.data, &mMap, sizeof(&mMap));
    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = cref;

    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        // ERROR TRACE
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    }
		return (ITS_SUCCESS);
}


/*implementation:internal
*
* PURPOSE:
*       sending MAP message to application
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
*/
ITS_INT
BSSAP_Interface::DispatchMapToApp(BSSAP_Call* call, BSSAP_Message* mdata)
{
    ITS_USHORT dest;
    ITS_CTXT cref = 0;
    ITS_INT ret;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_OCTET* data = NULL;
    ITS_INT len = 0;
    BSSMap *mMap = new BSSMap(); //Application has to delete this memory

    cref = call->GetSLR();
    mMap->SetCallRef(cref);
    mMap->SetAppId(call->GetAppId());
    mMap->SetMssgDisc(BSSAP_MD_BSSMAP);
    mMap->SetMssgType(call->GetMssgType());
    mMap->SetBssId(call->GetBssId()); //Added by Amaresh as on dated 09-05-08
    data = call->GetBSSAPData(&len);    

    BSSAP_DEBUG(("BSSAP STack*******:App Id = %d \n", mMap->GetAppId()));
    mMap->SetMAPdata(data, len);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSMap));
    memcpy(ev.data, &mMap, sizeof(&mMap));
    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = cref;
  
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        // ERROR TRACE
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    } 

    return (ITS_SUCCESS);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
*/
ITS_INT
BSSAP_Interface::DispatchErrorToApp(BSSAP_Call* call, 
                                    ITS_OCTET errType,
                                    ITS_OCTET errCode)
{
    ITS_USHORT dest = 0;
    ITS_CTXT cref = 0;
    ITS_INT ret;
    ITS_EVENT ev;
    ITS_HDR hdr;
    BSSAPError *mssg = new BSSAPError();//Application has to delete this memory

    BSSAP_DEBUG(("BSSAP_Interface: DispatchErrorToApp\n"));

    if (call)
    { 
        BSSAP_DEBUG(("BSSAP_Interface: DispatchErrorToApp cref %d msgtype %d AppId %d errType %d errCode %d \n",call->GetSLR(),call->GetMssgType(),call->GetAppId(),errType,errCode));
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

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSAPError));
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
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    }
    return (ITS_SUCCESS);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
*/
ITS_INT
BSSAP_Interface::DispatchErrorToApp(ITS_OCTET errType,
                                    ITS_OCTET errCode,
                                    ITS_OCTET mType,
                                    ITS_USHORT pcm,
                                    ITS_OCTET ts)
{                                   
    ITS_USHORT dest = 0;
    ITS_INT ret;
    ITS_EVENT ev;
    ITS_HDR hdr;
    BSSAPError *mssg = new BSSAPError();//Application has to delete this memory
    
    BSSAP_DEBUG(("BSSAP_Interface: DispatchErrorToApp\n"));
    
    mssg->SetMssgDisc(errType);
    mssg->SetErrCode(errCode);
    mssg->SetTimeSlot(ts);
    mssg->SetPcm(pcm);
    mssg->SetMssgType(mType);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSAPError));
    memcpy(ev.data, &mssg, sizeof(&mssg));

    hdr.type = ITS_BSSAP_SRC;

    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_CRITICAL(("DispatchErrorToApp: Bad route to App\n"));
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev);
    }
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       sending NWMSG(PAUSE,RESUME etc ) including PC & SSN to application
* INPUT:
*       error type, error code, pc,ssn
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
* --------------- ----------------------------------------------------------
* Amaresh Prasad         23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0310, ID :: D0320,
*                        ID :: D0330, ID :: D1060
*/
ITS_INT
BSSAP_Interface::DispatchMapUDTtoApp(BSSAP_Message* msg, ITS_OCTET nwId, ITS_OCTET *data, ITS_UINT len) 
{
    BSSMap *mMapUdt = new BSSMap(); //Application has to delete this memory
    ITS_INT ret;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_USHORT dest;

    BSSAP_DEBUG(("BSSAP_Interface: DispatchMapUDTtoApp\n"));

    mMapUdt->SetCallRef(0);
    mMapUdt->SetBssId(nwId);
    mMapUdt->SetAppId(0);
    mMapUdt->SetMssgDisc(BSSAP_MD_BSSMAP);
    mMapUdt->SetMssgType(msg->GetMsgType());

    mMapUdt->SetMAPdata(data, len);

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(BSSMap));
    memcpy(ev.data, &mMapUdt, sizeof(&mMapUdt));

    hdr.type = ITS_BSSAP_SRC;
    hdr.context.conref = 0;

    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        BSSAP_ERROR(("DispatchMapUDTtoApp: Bad route to App\n"));
    }
    else
    {
        ret =  TRANSPORT_PutEvent(dest, &ev); 
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("DispatchMapUDTtoApp: Send to App failed \n"));
        }
    }
    return (ITS_SUCCESS);
}

