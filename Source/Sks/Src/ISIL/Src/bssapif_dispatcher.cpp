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
 * LOG: $Log: bssapif_dispatcher.cpp,v $
 * LOG: Revision 1.11  2008/02/13 06:22:06  amaresh.prasad
 * LOG: Added for SCCP error message handelling
 * LOG:
 * LOG: Revision 1.10  2008/02/07 10:19:46  amaresh.prasad
 * LOG: Updated for RLSD message
 * LOG:
 * LOG: Revision 1.9  2008/02/01 02:45:24  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.8  2008/01/24 10:20:39  amaresh.prasad
 * LOG: Updated for Refusal & Release cause
 * LOG:
 * LOG: Revision 1.7  2008/01/24 08:08:38  amaresh.prasad
 * LOG: Updated for RLSD cause
 * LOG:
 * LOG: Revision 1.6  2008/01/18 04:19:29  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.5  2007/12/19 03:10:36  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/11/08 08:10:52  amaresh.prasad
 * LOG: Updated for Handover
 * LOG:
 * LOG: Revision 1.3  2007/10/30 06:37:29  amaresh.prasad
 * LOG: Updated for Network status message
 * LOG:
 * LOG: Revision 1.2  2007/10/22 06:04:12  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.7  2007/10/05 05:59:38  amaresh.prasad
 * LOG: Updated
 * LOG:
 * LOG: Revision 1.6  2007/09/28 05:40:43  amaresh.prasad
 * LOG: Updated Trace enabled
 * LOG:
 * LOG: Revision 1.5  2007/09/27 10:24:41  amaresh.prasad
 * LOG: Updated
 * LOG:
 * LOG: Revision 1.4  2007/09/27 06:34:58  amaresh.prasad
 * LOG: Call Refid is for Need Large context
 * LOG:
 * LOG: Revision 1.3  2007/09/20 09:15:51  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/08/22 05:21:49  vnl
 * LOG: Enhance for  BSCCS2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * LOG: Initialising sources in CVS
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
 * ID: $Id: bssapif_dispatcher.cpp,v 1.11 2008/02/13 06:22:06 amaresh.prasad Exp $
 ****************************************************************************/
#ident "$Id: bssapif_dispatcher.cpp,v 1.11 2008/02/13 06:22:06 amaresh.prasad Exp $"



#include <bssapif_common.h>
#include <bssapif_trace.h>
#include <bssapif_dispatcher.h>
#include <bssap_interface.h>
#include <bssapif_socket.h>
#include <BSSAP++.h>
#include "trace.h"
#include <mtp3_cmn.h>
#include <sccp_cmn.h>
#include <its.h>
#include <its_types.h>

#define ITS_ISUP_CCITT_SRC          (0xFFF8U)
#define ITS_ISUP_SRC        ITS_ISUP_CCITT_SRC

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif
extern "C"
{
 int CL_WriteEventMM(ITS_HANDLE , ITS_EVENT*);
 int Get_SSN(ITS_USHORT ,ITS_USHORT ,ITS_OCTET*,ITS_OCTET);
/* void ISIL_TRACE(int trace ,const char *ftstring, ...);*/
}
extern  ITS_HANDLE CL_Handle_MM ;
extern "C" ITS_OCTET CHECKMM_RESUME;

/* Added by Amaresh */
#define BSSAP_CP_DATA 1
#define BSSAP_CP_DATA_ACK 4
#define CP_SCCP_MSG_RLSD          (0x04U)//SCCP-RLSD from BSC_APP--->BSSAP stack properitary
void printMsgchk(ITS_EVENT *evt);
/* Added by Amaresh */
char b;
#define ITS_BSSAP_SRC 20

#define ISIL_BSSAP_HDR_LEN   18
#define BSSAP_MD_BS_SCCP 2
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
    ITS_CTXT appId = 0;
    ITS_CTXT ref = 0;
    BSSAPData bd;
    BSSMap mMap;   
  

    memset(&bd, 0, sizeof(BSSAPData));
    memset(&mMap, 0, sizeof(BSSMap));

    // Message Discriminator
    bd.mssgDisc = BSSAP_MD_BS_SCCP;

    // Call reference id as per LARGE CONTEXT as on 25-09-07
    bd.callrefId |= evt->data[index++];
    bd.callrefId |= evt->data[index++] << 8;
    bd.callrefId |= evt->data[index++] << 16;
    bd.callrefId |= evt->data[index++] << 24;
    ISIL_DEBUG_TRACE(("BSSAPDispatcher::ProcessSCCPMessage:: Call Reference id  = %d\n", bd.callrefId));
     // App Id
    bd.appId  |= evt->data[index++];
    bd.appId  |= evt->data[index++] << 8;
    bd.appId  |= evt->data[index++] << 16;
    bd.appId  |= evt->data[index++] << 24; 
    ISIL_DEBUG_TRACE(("BSSAPDispatcher::ProcessSCCPMessage::  AppId = %d\n", bd.appId));
		

    //Cause
		bd.hofacause = evt->data[index++]; //24-04-08
		ISIL_DEBUG_TRACE(("BSSAPDispatcher::ProcessSCCPMessage:: Cause of RLSD message  = %d\n", bd.hofacause));

    mMap.SetCallRef(bd.callrefId);
    mMap.SetAppId(bd.appId);
    mMap.SethofaCause(bd.hofacause);
    mMap.SetMssgDisc(BSSAP_MD_BS_SCCP);

    ret = mMap.SendBSSAPMessage(ref);

    return (ret);

}

#if 0
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
    ITS_CTXT appId = 0;//30-01-08	
    BSSAP_Api api;
    BSS_INFO bss_cfg;
    //ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessSCCPMessage"));
		ITS_OCTET   cause;

    // Call reference id as per LARGE CONTEXT as on 25-09-07
    callrefId |= evt->data[index++];
    callrefId |= evt->data[index++] << 8;
    callrefId |= evt->data[index++] << 16;
    callrefId |= evt->data[index++] << 24;
    //ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Call Reference id  = %d\n", callrefId));
     // App Id
    appId  |= evt->data[index++];
    appId  |= evt->data[index++] << 8;
    appId  |= evt->data[index++] << 16;
    appId  |= evt->data[index++] << 24; 
		
		// App Id
 /*   appId  |= evt->data[index++];
    appId  |= evt->data[index++] << 8;
    appId  |= evt->data[index++] << 16;
    appId  |= evt->data[index++] << 24;  */
    ISIL_DEBUG_TRACE(("BSSAPDispatcher:: APP id  = %d Call Reference id = %d \n", appId,callrefId));
/*		callrefId = 0; *//*hardcoded due to RLSD & change in CS3 by Amaresh 24-04-08 */
   /* ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Call Reference id  = %d\n", callrefId));   */
		cause = evt->data[index++]; //24-04-08
		//ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Cause of RLSD message  = %d\n", cause));


    if (evt->data[1] == CP_SCCP_ACCEPT)
    {
    ISIL_DEBUG_TRACE(("BSSAPDispatcher:ProcessSCCPMessage Received CC"));
        ret  = api.AcceptConnection(callrefId);
    }
    else if (evt->data[1] == CP_SCCP_REJECT)
    {
        ISIL_DEBUG_TRACE(("BSSAPDispatcher:ProcessSCCPMessage Received CREF"));

        ret = api.RejectConnection(callrefId);
    }
/*    else if (evt->data[1] == CP_SCCP_RELEASE)
    {
        BSSAPIF_TRACE_DEBUG(("ProcessSCCPMessage: Received REL"));
    
        ret = api.ClearConnection(callrefId);
    }  */ // Amaresh
/* Added by Amaresh for release of CALL context & CIC maintained by BSSAP */
    else if (evt->data[1] == CP_SCCP_RELEASE) /*CP_SCCP_MSG_RLSD =0x04*/
    {
    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessSCCP RLSD Message from BSC-APP-->BSSAP"));
       // ret = api.ReleasedConnection(callrefId);
	 ret =  api.ReleasedConnection(callrefId,appId,cause); //24-04-08
    }
/* Addition completed by Amaresh for release of CALL context & CIC maintained by BSSAP */

    else
    {
       ISIL_DEBUG_TRACE(("ProcessSCCPMessage: Unknown msg %d", evt->data[1]));
        ret = (!ITS_SUCCESS);
    }

    return (ret);
}
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
BSSAPDispatcher::ProcessCICMessage(ITS_EVENT* evt)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 1;
    ITS_OCTET bscId = 0; 
    ITS_USHORT pcm = 0; 
    ITS_USHORT startTs = 0;
    ITS_USHORT endTs= 0;
    BSSAP_Api api;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessCICMessage"));

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
    BSSDtap mDtap; //Added by Amaresh 
    BSSMap mMap;   //Added by Amaresh
    BSSAP_Api api;//Added by Amaresh

    BSSAPIF_TRACE_DEBUG(("BSSAPDispatcher: ProcessBSSAPMessage"));

    memset(&bd, 0, sizeof(BSSAPData));
   
    // BSC Id
    bd.bssId = evt->data[index++];

    // Call ref id as per LARGE CONTEXT as on 25-09-07
    bd.callrefId  |= evt->data[index++];
    bd.callrefId  |= evt->data[index++] << 8;
    bd.callrefId  |= evt->data[index++] << 16;
    bd.callrefId  |= evt->data[index++] << 24;
    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: CALL_REF_ID = %d\n", bd.callrefId));
    // App Id
    bd.appId  |= evt->data[index++];
    bd.appId  |= evt->data[index++] << 8;
    bd.appId  |= evt->data[index++] << 16;
    bd.appId  |= evt->data[index++] << 24;
    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: APP_ID = %d\n", bd.appId));


    // Message Discriminator
    bd.mssgDisc = evt->data[index++];

    // BSSAP Message name
    bd.mssgType = evt->data[index++];

    // BSSAP Message length
    len = evt->data[index++];
    if (bd.mssgDisc == BSSAP_MD_BSSMAP)
    {
        memcpy(bd.u.MAPdata.mapMsg, &evt->data[index], len);

        mMap.SetBssId(bd.bssId);
        mMap.SetCallRef(bd.callrefId);
        mMap.SetAppId(bd.appId);
        mMap.SetMssgDisc(BSSAP_MD_BSSMAP);
        mMap.SetMssgType(bd.mssgType);
        mMap.SetMAPdata(bd.u.MAPdata.mapMsg, len);

        ret = mMap.SendBSSAPMessage(ref);
    }
    else
    {
        memcpy(bd.u.DTAPdata.dtapMsg, &evt->data[index], len);

        // Build the Dtap object

        mDtap.SetBssId(bd.bssId);
        mDtap.SetCallRef(bd.callrefId);
        mDtap.SetAppId(bd.appId);
        mDtap.SetMssgDisc(BSSAP_MD_DTAP);
        mDtap.SetMssgType(bd.mssgType);
        mDtap.SetDTAPdata(bd.u.DTAPdata.dtapMsg, len);

        ret = mDtap.SendBSSAPMessage(ref);
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

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessCFGMessage"));

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
    ITS_EVENT ev;
    ITS_USHORT len = 0;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessSocketEvent"));
/* Added by Amaresh for print msg type & data  */
    //ISIL_DEBUG_TRACE(("RECEIVED FROM  CP  >>>>>>"));
  //  printMsgchk(evt);
/* Addition completed by Amaresh for print msg type & data  */

    if (evt->data[0] == CP_BSSAP_SCCP_TAG)
    {
#if 0
				ITS_EVENT_INIT(&ev,ITS_ISUP_SRC,evt->len*sizeof(ITS_OCTET));
        ISIL_DEBUG_TRACE(("ProcessSocketEvent:Received CP_BSSAP_SCCP_TAG length %d\n", evt->len));
        ISIL_DEBUG_TRACE(("ProcessSocketEvent:Received CP_BSSAP_SCCP_TAG src: %d len: %d\n", ev.src,ev.len));
		    memcpy(&ev.data[0],&evt->data[0],evt->len);
        ret = TRANSPORT_PutEvent(ITS_BSSAP_SRC, &ev);
#endif
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
       ISIL_ERROR_TRACE(("ProcessSocketEvent:Received unknown event %d\n", evt->data[0]));

        ret = (!ITS_SUCCESS);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  ProcessNetworkDTAP is to fill the ISIL header+BSSAP data & Send to CP i.e BSC-Application. 
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
BSSAPDispatcher::ProcessNetworkDTAP(BSSDtap* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 5;
    ITS_USHORT len = 0; 
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;
 
    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkDTAP"));

 
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, BSSAP_DATA_LEN + ISIL_BSSAP_HDR_LEN);
    /*Fill the ISIL header */ 
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x03; 

    // Tag
    ev.data[index++] = CP_BSSAP_MSG_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id as per LARGE CONTEXT as on 25-09-07
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >> 16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;
    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: CALLREF id = %d\n", callrefId));

    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;
    ev.data[index++] = (appId & 0x00FF0000) >> 16;
    ev.data[index++] = (appId & 0xFF000000) >> 24;

    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: APP id = %d\n", appId));

    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();

   // dtap = api->GetBSSAPdata();  commented by Amaresh
    api->GetDTAPdata(buff, &len);

    // BSSAP message buffer length
    ev.data[index++] = len;

    // BSSAP messge buffer
    memcpy(&ev.data[index], buff, len);

    // Actual length
    len = index + len;
    
    ev.len = len;
    ev.data[3] =len ;
    ev.data[4] = 0; 
    
    ISIL_DEBUG_TRACE(("SEND BSSDTAP Message  TO  CP  >>>>>>"));
    printMsgchk(&ev); //Added by Amaresh 
   
     ret=CL_WriteEventMM(CL_Handle_MM,&ev);
   if(ret!=ITS_SUCCESS)
   {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&ev);
   }


    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  ProcessNetworkMAPErr is to fill the ISIL header+BSSAP data & Send to CP i.e BSC-Application.
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
 *  Notes:Amaresh Prasad
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
BSSAPDispatcher::ProcessNetworkMAPErr(BSSMap* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 5;
    ITS_USHORT len = 0;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkMAPErr"));

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, BSSAP_DATA_LEN + ISIL_BSSAP_HDR_LEN);

    /*Fill the ISIL header */
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x03;

    // Tag
    ev.data[index++] = CP_BSSAP_FAILURE_TAG;

    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();
	
		//Bssap cause
		ev.data[index++] = api->GethofaCause();			

    api->GetMAPdata(buff, &len);

    // BSSAP message buffer length
    ev.data[index++] = len;

    // BSSAP messge buffer
    memcpy(&ev.data[index], buff, len);

		 // Actual length
    len = index + len;
    //Fill ISIL header length
    ev.data[3] =len;
    ev.data[4] = 0;
    ev.len = len;

    ISIL_DEBUG_TRACE(("SEND BSSMAP HO-FAIL Err  Message TO  CP  >>>>>>"));
    printMsgchk(&ev); //Added by Amaresh

 //Send to CP
    ret=CL_WriteEventMM(CL_Handle_MM,&ev);
    if(ret!=ITS_SUCCESS)
   {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&ev);
   }

    return (ret);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  ProcessNetworkMAP is to fill the ISIL header+BSSAP data & Send to CP i.e BSC-Application.  
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
BSSAPDispatcher::ProcessNetworkMAP(BSSMap* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 5;
    ITS_USHORT len = 0; 
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkMAP"));

    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, BSSAP_DATA_LEN + ISIL_BSSAP_HDR_LEN);

    /*Fill the ISIL header */
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x03; 

    // Tag
    ev.data[index++] = CP_BSSAP_MSG_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    ISIL_DEBUG_TRACE(("$$$$$$$$$$$$$ ____BSSID :%d", api->GetBssId()));
    // Call ref Id as per LARGE CONTEXT as on 25-09-07
    callrefId = api->GetCallRef();

    ISIL_DEBUG_TRACE(("$$$$$$$$$$$ ____CallRefId :%d", callrefId));
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >> 16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;
   
    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;
    ev.data[index++] = (appId & 0x00FF0000) >> 16;
    ev.data[index++] = (appId & 0xFF000000) >> 24;

    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: APP ID  = %d\n", appId));


    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();

    api->GetMAPdata(buff, &len);

    // BSSAP message buffer length
    ev.data[index++] = len;

    // BSSAP messge buffer
    memcpy(&ev.data[index], buff, len);

    // Actual length
    len = index + len;
    //Fill ISIL header length 
    ev.data[3] =len;
    ev.data[4] = 0;
    ev.len = len;

    ISIL_DEBUG_TRACE(("SEND BSSMAP Message TO  CP  >>>>>>"));
    printMsgchk(&ev); //Added by Amaresh
    
 //Send to CP     
    ret=CL_WriteEventMM(CL_Handle_MM,&ev);
    if(ret!=ITS_SUCCESS)
   {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&ev);
   }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  Process NetworkTimeout is to fill the ISIL header+BSSAP data & Send to CP i.e BSC-Application. 
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
    ITS_OCTET index = 5;
    ITS_INT len = 0;
    ITS_EVENT ev;
    ITS_UINT appId = 0;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkTimeout"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(ITS_OCTET)*12);
    //Fill ISIL Header
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x03;
    ev.data[3] = 0x0c;
    ev.data[4] = 0x00;
    // Tag
    ev.data[index++] = CP_BSSAP_TIMEOUT_TAG;

    // Message Discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message name
    ev.data[index++] = api->GetErrCode();

     //IssueId:3300
    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;
    ev.data[index++] = (appId & 0x00FF0000) >> 16;
    ev.data[index++] = (appId & 0xFF000000) >> 24;

    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Appid  = %d\n", appId));

    ISIL_DEBUG_TRACE(("SEND Network Timeout Message TO  CP  >>>>>>"));
    ret=CL_WriteEventMM(CL_Handle_MM,&ev);
   if(ret!=ITS_SUCCESS)
   {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&ev);
   }
    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  Process Network Protocol is to fill the ISIL header+BSSAP data & Send to CP i.e BSC-Application.
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
    ITS_OCTET index = 5;
    ITS_CTXT callrefId = 0;
    ITS_USHORT pcm = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT evt;
    ITS_OCTET ts=0;
    ITS_USHORT cic = 0;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkProtocol"));

       ITS_EVENT_INIT(&evt, ITS_BSSAP_SRC, 30);

      //Fill ISIL Header  
      evt.data[0] = 0xc1;
      evt.data[1] = 0x01;
      evt.data[2] = 0x03;

     // Tag
    evt.data[index++] = CP_BSSAP_PROTOCOL_TAG;

    // BSC Id
    evt.data[index++] = api->GetBssId();

    // Call ref Id as per LARGE CONTEXT as on 25-09-07
    callrefId = api->GetCallRef();
    evt.data[index++] = callrefId & 0x000000FF;
    evt.data[index++] = (callrefId & 0x0000FF00) >> 8;
    evt.data[index++] = (callrefId & 0x00FF0000) >> 16;
    evt.data[index++] = (callrefId & 0xFF000000) >> 24;

    //  App Id
    appId = api->GetAppId();
    evt.data[index++] = appId & 0x000000FF;
    evt.data[index++] = (appId & 0x0000FF00) >> 8;
    evt.data[index++] = (appId & 0x00FF0000) >> 16;
    evt.data[index++] = (appId & 0xFF000000) >> 24;

    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: APP ID   = %d\n", appId));

    // Message discriminator
    evt.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    evt.data[index++] = api->GetMssgType();

    // Error code
    evt.data[index++] = api->GetErrCode();

    // PCM
    pcm = api->GetPcm();
    ts  = api->GetTimeSlot();

    cic = (pcm << 5) | (ts & 0x1F);
#if defined(CCITT)
    evt.data[index++]=(cic & 0xFF00) >> 8;
    evt.data[index++]=(cic & 0x00FF);
#else
    evt.data[index++]=(cic & 0x00FF);
    evt.data[index++]=(cic & 0xFF00) >> 8;
#endif
    //evt.data[index++] =  pcm & 0x00FF;
    //evt.data[index++] =  (pcm & 0xFF00) >> 8;

    // TS
    //evt.data[index++] = api->GetTimeSlot();

    evt.len = index;
    //Fill ISIL Header length 
    evt.data[3] = (evt.len)&0xff;;
    evt.data[4] = ((evt.len&0xff)>>8);

    ISIL_DEBUG_TRACE(("SEND TO  CP cic %d >>>>>>",cic));
    printMsgchk(&evt);
    
    ret=CL_WriteEventMM(CL_Handle_MM,&evt);
   if(ret!=ITS_SUCCESS)
   {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&evt);
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
BSSAPDispatcher::ProcessNetworkStaus(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 5;
    ITS_INT len = 0;
    ITS_EVENT ev;
/* Added by Amaresh for Network status message */
    ITS_USHORT dpc = 0;
    ITS_USHORT src;
    ITS_OCTET ni=MTP3_NIC_INTERNATIONAL;
    ITS_OCTET SSN=0,ssn=0;
/* Addition completed by Amaresh for Network status message */
  
    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkStaus"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(ITS_OCTET)*11); //changed length by Amaresh
 
    src=0x20;
    /*Fill the ISIL header */
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x03;
//    ev.data[3] = 0x08;
//    ev.data[4] = 0x00;    

    // Tag
//    ev.data[index++] = CP_BSSAP_NETWORK_TAG;
    ev.data[index++] = CP_BSSAP_MANAGEMENT_TAG;

    // Message Discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message name
    ev.data[index++] = api->GetErrCode();
/* Added by Amaresh for find DPC */
    dpc =(ITS_USHORT)(api->GetPointCode());

   ISIL_DEBUG_TRACE(("BSSAPDispatcher:DPC %d",dpc));

  if (api->GetErrCode()==0x01||
         api->GetErrCode()==0x02||
           api->GetErrCode()==0x03||
             api->GetErrCode()==0x04||
               api->GetErrCode()==0x05)
      {
         ssn=api->GetSSN();
         ev.data[index++] = ssn;
      }

    ev.data[index++] = (ITS_OCTET)(dpc & 0x00FF);
    ev.data[index++] = (ITS_OCTET)((dpc >> 8) & 0x00FF);
    ev.len=index;
/*  Length  will be  different  in MTP2  Resume  and SSA  */  
    ev.data[3] = (ev.len & 0x00ff);
    ev.data[4] = ((ev.len & 0xff00)>>8 );

        CHECKMM_RESUME=1;
        Get_SSN(dpc,src,&SSN,ni);
   // printf("\n\nSSN_VALUE=%d",SSN);

 if (SSN==0xFE)
      {
    ISIL_DEBUG_TRACE(("SEND TO  CP  >>>>>>"));
    printMsgchk(&ev); 
    ret=CL_WriteEventMM(CL_Handle_MM,&ev);
   if(ret!=ITS_SUCCESS)
     {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&ev);
     }
  }
else
        {
        ISIL_DEBUG_TRACE(("BSSAPDispatcher:BSSAP is not registerd as SCCP User\n"));
        ITS_EVENT_TERM(&ev);
        ret=-1;
        }
/* Addition completed by Amaresh for Network status message */  
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
    ITS_OCTET index = 5;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_INT len = 0;
    ITS_EVENT ev;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkSCCPInd"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC,(sizeof(BSSAPData)+10)); /* changed by Amaresh from 5 to 10 */

    /*Fill the ISIL header */
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x03;
 	
    // Tag
    ev.data[index++] = CP_BSSAP_SCCP_TAG;

    // Message name
    ev.data[index++] = api->GetMssgType();

    // Call ref Id as per LARGE CONTEXT as on 25-09-07
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;
    ev.data[index++] = (callrefId & 0x00FF0000) >>16;
    ev.data[index++] = (callrefId & 0xFF000000) >> 24;
    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Call Ref id  = %d\n", callrefId));
    // App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;
    ev.data[index++] = (appId & 0x00FF0000) >>16;
    ev.data[index++] = (appId & 0xFF000000) >> 24;

    ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: APP ID  = %d\n", appId));
/* Added by Amaresh for get error cause */
        if(api->GetMssgType() == CP_BSSAP_CON_ESTD)
        {
        ev.data[index++] = 0;
        ev.data[index++] = 0;
        ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkSCCPInd CP_BSSAP_CON_ESTD with REF & RLC cause is zero"));
        }
        if(api->GetMssgType() == CP_BSSAP_CON_REL)
        {
        ev.data[index++] = 0;
        ev.data[index++] =  api->GetERRCause();
        ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Get SCCP-RELERRCause  = %d\n", api->GetERRCause()));
        ISIL_DEBUG_TRACE(("BSSAPDispatcher:ProcessNetworkSCCPInd CP_BSSAP_CON_REL with REF zero & RLC cause is set"));
        }
        if(api->GetMssgType() == CP_BSSAP_CON_REF)
        {
        ev.data[index++] =  api->GetERRCause();
        ev.data[index++] = 0;
        ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: GetRefusalCause  = %d\n", api->GetERRCause()));
        ISIL_DEBUG_TRACE(("BSSAPDispatcher:ProcessNetworkSCCPInd CP_BSSAP_CON_REL with REF cause is set & RLC cause is zero"));
        }
/* Amaresh new entry for err mesage of SCCP as on dated 11-02-08*/
         if(api->GetMssgType() == CP_BSSAP_CON_ERR)
        {
        ev.data[index++] = 0;
        ev.data[index++] = 0;
        ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkSCCPInd CP_BSSAP_CON_ESTD with REF & RLC cause is zero"));
 ev.data[index++] =  api->GetERRCause();
        ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:: Get SCCP-ERRORCause  = %d\n", api->GetERRCause()));
        ISIL_DEBUG_TRACE(("BSSAPDispatcher:ProcessNetworkSCCPInd CP_BSSAP_CON_ERR with ERR cause is set"));
        }
/* Amaresh new entry for err mesage of SCCP as on dated 11-02-08*/


/* Added by Amaresh for get error cause */
    ITS_Event event(&ev);

    ev.len = index;
    ev.data[3] = (ev.len)&0xff;;
    ev.data[4] = ((ev.len&0xff)>>8); 

    ISIL_DEBUG_TRACE(("SEND TO  CP  >>>>>>"));
    printMsgchk(&ev);

     ret=CL_WriteEventMM(CL_Handle_MM,&ev);
   if(ret!=ITS_SUCCESS)
   {
     CL_Handle_MM=NULL;
     ITS_EVENT_TERM(&ev);
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
BSSAPDispatcher::ProcessNetworkEvent(ITS_Event& event)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET msgDisc = 0;
    ITS_UINT address;
    BSSAP_Api* bssap_api = NULL;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkEvent"));

    memcpy(&address, event.GetData(), sizeof(&address)); 

    bssap_api = (BSSAP_Api*)address;

    if (!bssap_api)
    {
        ISIL_ERROR_TRACE(("ProcessNetworkEvent: Invalid data address"));

        return (!ITS_SUCCESS);
    }

    msgDisc = bssap_api->GetMssgDisc();

    if (msgDisc == BSSAP_MD_DTAP)
    {
        ret =  ProcessNetworkDTAP((BSSDtap*)bssap_api); 
    }
    else if (msgDisc == BSSAP_MD_BSSMAP)
    {
        ret = ProcessNetworkMAP((BSSMap*)bssap_api); 
    }
/* Added by Amaresh for HO-FAI 03-07-08 */
		else if (msgDisc == BSSAP_FAILURE_IND)
    {
        ret = ProcessNetworkMAPErr((BSSMap*)bssap_api);
    }
/* Added by Amaresh for HO-FAI 03-07-08 */
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
     ISIL_ERROR_TRACE(("ProcessNetworkEvent: Unknown event %d", msgDisc));
    }

    if (bssap_api)
    {
        delete bssap_api;
    }

    return (ret);
}


void Print_BSSMAP(ITS_EVENT *evt)
{
    switch (evt->data[16])
    {
	        case BSSAP_MSG_ASSIGN_COMPLETE:
	            ISIL_DEBUG_TRACE(("BSSAP_MSG_ASSIGN_COMPLETE:\n"));
	        break;
		            case BSSAP_MSG_ASSIGN_FAILURE:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_ASSIGN_FAILURE:\n"));
                break;
                case BSSAP_MSG_ASSIGN_REQUEST:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_ASSIGN_REQUEST:\n"));
                break;

                case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:\n"));
                break;

                case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:\n"));
                break;

                case BSSAP_MSG_HANDOVER_COMMAND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_COMMAND:\n"));
                break;

                case BSSAP_MSG_HANDOVER_COMPLETE:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_COMPLETE:\n"));
                break;
                case BSSAP_MSG_HANDOVER_DETECT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_DETECT:\n"));
                break;

                case BSSAP_MSG_HANDOVER_FAILURE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_FAILURE:\n"));
                break;
                case BSSAP_MSG_HANDOVER_PERFORMED:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_PERFORMED:\n"));
                break;

                case BSSAP_MSG_HANDOVER_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_REQUEST:\n"));
                break;

                case BSSAP_MSG_HANDOVER_REQUEST_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_REQUEST_ACK:\n"));
                break;

                case BSSAP_MSG_HANDOVER_REQUIRED:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_REQUIRED:\n"));
                break;
		case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_REQUIRED_REJECT:\n"));
                break;

                case BSSAP_MSG_HANDOVER_SUCCEEDED:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_HANDOVER_SUCCEEDED:\n"));
                break;

                case BSSAP_MSG_CLEAR_COMMAND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CLEAR_COMMAND:\n"));
                break;

                 case BSSAP_MSG_CLEAR_COMPLETE:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_CLEAR_COMPLETE:\n"));
                break;

                case BSSAP_MSG_CLEAR_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CLEAR_REQUEST:\n"));
                break;

                case BSSAP_MSG_SAPI_N_REJECT:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_SAPI_N_REJECT:\n"));
                break;

		case BSSAP_MSG_CONFUSION:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_CONFUSION:\n"));
                break;

		case BSSAP_MSG_SUSPEND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_SUSPEND:\n"));
                break;

		case BSSAP_MSG_RESUME:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_RESUME:\n"));
                break;
		case BSSAP_MSG_RESET:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_RESET:\n"));
                break;

		case BSSAP_MSG_RESET_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_RESET_ACK:\n"));
                break;
		case BSSAP_MSG_RESET_CIRCUIT:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_RESET_CIRCUIT:\n"));
                break;

		case BSSAP_MSG_RESET_CIRCUIT_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_RESET_CIRCUIT_ACK:\n"));
	         break;

		case BSSAP_MSG_OVERLOAD:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_OVERLOAD:\n"));
                break;

		case BSSAP_MSG_MSC_INVOKE_TRACE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_MSC_INVOKE_TRACE:\n"));
                break;

		case BSSAP_MSG_BSS_INVOKE_TRACE:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_BSS_INVOKE_TRACE:\n"));
                break;

		case BSSAP_MSG_BLOCK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_BLOCK:\n"));
                break;

		case BSSAP_MSG_BLOCK_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_BLOCK_ACK:\n"));
                break;

		case BSSAP_MSG_UNBLOCK:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_UNBLOCK:\n"));
                break;

		case BSSAP_MSG_UNBLOCK_ACK:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_UNBLOCK_ACK:\n"));
                break;

		case BSSAP_MSG_CKT_GROUP_BLOCK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CKT_GROUP_BLOCK:\n"));
                break;

		case BSSAP_MSG_CKT_GRP_BLK_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CKT_GRP_BLK_ACK:\n"));
                break;
		case BSSAP_MSG_CKT_GRP_UNBLOCK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CKT_GRP_UNBLOCK:\n"));
                break;

		case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CKT_GRP_UNBLKING_ACK:\n"));
                break;

		case BSSAP_MSG_UNEQUIPPED_CKT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_UNEQUIPPED_CKT:\n"));
                break;

		case BSSAP_MSG_CHANGE_CKT:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_CHANGE_CKT:\n"));
                break;

		case BSSAP_MSG_CHANGE_CKT_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CHANGE_CKT_ACK:\n"));
                break;

		case BSSAP_MSG_RESOURCE_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CHANGE_CKT_ACK:\n"));
                break;

		case BSSAP_MSG_RESOURCE_INDICATION:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_RESOURCE_INDICATION:\n"));
                 break;

		case BSSAP_MSG_PAGING:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_PAGING:\n"));
                 break;

		case BSSAP_MSG_PAGING_RESPONSE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_PAGING_RESPONSE:\n"));
                 break;
		case BSSAP_MSG_CIPHER_MODE_CMD:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CIPHER_MODE_CMD:\n"));
                 break;

		case BSSAP_MSG_CIPHER_MODE_COMPLETE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CIPHER_MODE_COMPLETE:\n"));
                 break;
		case BSSAP_MSG_CIPHER_MODE_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CIPHER_MODE_REJECT:\n"));
                break;

		case BSSAP_MSG_CLASSMARK_UPDATE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CLASSMARK_UPDATE:\n"));
                 break;

		case BSSAP_MSG_CLASSMARK_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CLASSMARK_REQUEST:\n"));
                break;

		case BSSAP_MSG_COMPLETE_LAYER3_INFO:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_COMPLETE_LAYER3_INFO:\n"));
                 break;

            case BSSAP_MSG_LOAD_INDICATION:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_LOAD_INDICATION:\n"));
                 break;

            case BSSAP_MSG_QUEUING_INDICATION:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_QUEUING_INDICATION:\n"));
                 break;

            case BSSAP_MSG_VGCS_VBS_SETUP:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_SETUP:\n"));
                 break;
             case BSSAP_MSG_VGCS_VBS_SETUP_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_SETUP_ACK:\n"));
                 break;

            case BSSAP_MSG_VGCS_VBS_SETUP_REFUSE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_SETUP_REFUSE:\n"));
                 break;

            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST:\n"));
                break;

            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT:\n"));
                 break;
	    case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE:\n"));
                break;

            case BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION:\n"));
                break;

            case BSSAP_MSG_UPLINK_REQUEST:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_UPLINK_REQUEST:\n"));
                break;

            case BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION:
                          ISIL_DEBUG_TRACE(("BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION:\n"));
                break;

            case BSSAP_MSG_UPLINK_RELEASE_INDICATION:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_UPLINK_RELEASE_INDICATION:\n"));
                break;

            case BSSAP_MSG_UPLINK_REJECT_COMMAND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_UPLINK_REJECT_COMMAND:\n"));
                break;

            case BSSAP_MSG_UPLINK_RELEASE_COMMAND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_UPLINK_RELEASE_COMMAND:\n"));
                break;

            case BSSAP_MSG_UPLINK_SEIZED_COMMAND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_UPLINK_SEIZED_COMMAND:\n"));
                break;
        default:
            ISIL_DEBUG_TRACE(("Print_BSSMAP: default\n"));
            break;
    }
}

void Print_DTAP(ITS_EVENT *evt,char b)
{

     if(b==9) //0x9 for SMS management
	{
         ISIL_DEBUG_TRACE(("BSSAP_MSG_BSSAP_SMS_DATA:\n"));
         switch (evt->data[22])
         {
              case BSSAP_CP_DATA:
                    ISIL_DEBUG_TRACE(("BSSAP_MSG_BSSAP_CP_DATA:\n"));
                    break;

              case BSSAP_CP_DATA_ACK:
                    ISIL_DEBUG_TRACE(("BSSAP_MSG_BSSAP_CP_DATA_ACK:\n"));
                    break;
              default :
                    break;
         }
     }

     else if(b==3) //0xb3 call control
	{
          switch (evt->data[22])
          {
                case BSSAP_CC_MSG_ALERTING:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_ALERTING:\n"));
                    break;

                case BSSAP_CC_MSG_CALL_PROCEEDING:
                         ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_CALL_PROCEEDING:\n"));
                    break;
                case BSSAP_CC_MSG_CONNECT:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_CONNECT:\n"));
                    break;

                case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:\n"));
                    break;

                case BSSAP_CC_MSG_SETUP:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_SETUP:\n"));
                    break;

                 case BSSAP_CC_MSG_CALL_CONFIRMED:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_CALL_CONFIRMED:\n"));
                     break;

                case BSSAP_CC_MSG_EMERGENCY_SETUP:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_EMERGENCY_SETUP:\n"));
                break;

                case BSSAP_CC_MSG_PROGRESS:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_PROGRESS:\n"));
                    break;

                case BSSAP_CC_MSG_MODIFY:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_MODIFY:\n"));
                    break;

                case BSSAP_CC_MSG_MODIFY_COMPLETE:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_MODIFY_COMPLETE:\n"));
                    break;
          case BSSAP_CC_MSG_MODIFY_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_MODIFY_REJECT:\n"));
                    break;

                case BSSAP_CC_MSG_USER_INFORMATION:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_USER_INFORMATION:\n"));
                    break;

                case BSSAP_CC_MSG_HOLD:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_HOLD:\n"));
                    break;

                case BSSAP_CC_MSG_HOLD_ACKNOWLEDGE:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_HOLD_ACKNOWLEDGE:\n"));
                    break;

                case BSSAP_CC_MSG_HOLD_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_HOLD_REJECT:\n"));
                    break;

                 case BSSAP_CC_MSG_RETRIEVE:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_RETRIEVE:\n"));
                 break;

                case BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE:\n"));
                    break;

                case BSSAP_CC_MSG_RETRIEVE_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_RETRIEVE_REJECT:\n"));
                    break;

                case BSSAP_CC_MSG_DISCONNECT:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_DISCONNECT:\n"));
                    break;

                case BSSAP_CC_MSG_RELEASE:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_RELEASE:\n"));
                    break;

                 case BSSAP_CC_MSG_RELEASE_COMPLETE:
                         ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_RELEASE_COMPLETE:\n"));
                    break;
     case BSSAP_CC_MSG_CONGESTION_CONTROL:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_CONGESTION_CONTROL:\n"));
                    break;

                case BSSAP_CC_MSG_NOTIFY:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_NOTIFY:\n"));
                    break;

                case BSSAP_CC_MSG_STATUS:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_STATUS:\n"));
                    break;

                case BSSAP_CC_MSG_STATUS_ENQUIRY:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_STATUS_ENQUIRY:\n"));
                    break;
                case BSSAP_CC_MSG_START_DTMF:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_START_DTMF:\n"));
                    break;

                case BSSAP_CC_MSG_START_DTMF_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_START_DTMF_ACK:\n"));
                    break;

                case BSSAP_CC_MSG_START_DTMF_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_START_DTMF_REJECT:\n"));
                    break;

                case BSSAP_CC_MSG_STOP_DTMF:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_STOP_DTMF:\n"));
                    break;

                case BSSAP_CC_MSG_STOP_DTMF_ACK:
                        ISIL_DEBUG_TRACE(("BSSAP_CC_MSG_STOP_DTMF_ACK:\n"));
                    break;
          }
     }

  else if(b==5) //0x5 for mobility management
	   {
            switch (evt->data[22])
            {
                case BSSAP_MSG_IMSI_DETACH_INDICATION:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_IMSI_DETACH_INDICATION:\n"));
                    break;

                case BSSAP_MSG_LOCATION_UPDATING_ACCEPT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_LOCATION_UPDATING_ACCEPT:\n"));
                    break;

                case BSSAP_MSG_LOCATION_UPDATING_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_LOCATION_UPDATING_REJECT:\n"));
                  break;

                case BSSAP_MSG_LOCATION_UPDATING_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_LOCATION_UPDATING_REQUEST:\n"));
                    break;

                case BSSAP_MSG_AUTHENTICATION_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_AUTHENTICATION_REJECT:\n"));
                    break;

                case BSSAP_MSG_AUTHENTICATION_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_AUTHENTICATION_REQUEST:\n"));
                    break;

                case BSSAP_MSG_AUTHENTICATION_RESPONSE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_AUTHENTICATION_RESPONSE:\n"));
                    break;

                case BSSAP_MSG_TMSI_REALLOC_COMMAND:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_TMSI_REALLOC_COMMAND:\n"));
                    break;

                case BSSAP_MSG_TMSI_REALLOC_COMPLETE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_TMSI_REALLOC_COMPLETE:\n"));
                    break;

                case BSSAP_MSG_CM_SERVICE_ABORT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CM_SERVICE_ABORT:\n"));
                    break;
   case BSSAP_MSG_CM_SERVICE_ACCEPT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CM_SERVICE_ACCEPT:\n"));
                    break;

                case BSSAP_MSG_CM_SERVICE_REJECT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CM_SERVICE_REJECT:\n"));
                    break;
                 case BSSAP_MSG_CM_SERVICE_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CM_SERVICE_REQUEST:\n"));
                    break;

                case BSSAP_MSG_CM_REESTABLISHMENT_REQ:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_CM_REESTABLISHMENT_REQ:\n"));
                    break;

                case BSSAP_MSG_ABORT:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_ABORT:\n"));
                    break;

                case BSSAP_MSG_MM_INFORMATION:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_MM_INFORMATION:\n"));
                    break;

                case BSSAP_MSG_MM_STATUS:
                         ISIL_DEBUG_TRACE(("BSSAP_MSG_MM_STATUS:\n"));
                    break;

                case BSSAP_MSG_MM_NULL:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_MM_NULL:\n"));
                    break;

                case BSSAP_MSG_IDENTITY_REQUEST:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_IDENTITY_REQUEST:\n"));
                    break;

                case BSSAP_MSG_IDENTITY_RESPONSE:
                        ISIL_DEBUG_TRACE(("BSSAP_MSG_IDENTITY_RESPONSE:\n"));
                    break;

                 default :
                   break;
               }
       }
       else
       { 
           ISIL_DEBUG_TRACE(("Print_DTAP Else case :\n"));
       }
}

void printMsgchk(ITS_EVENT *evt)
{
   if(evt->data[5] == CP_BSSAP_MSG_TAG)
   {
        switch (evt->data[15])
        {
            case BSSAP_MD_BSSMAP: 
                printf("\nBSSAP_MD_BSSMAP");
                Print_BSSMAP(evt);
                break;
            case BSSAP_MD_DTAP: 
                printf("\nBSSAP_MD_DTAP");
                b=evt->data[21] & 0x0f;
                Print_DTAP(evt,b);
                break;
            default:
                printf("\nDefault");
                break;
        } 
   }
   else if (evt->data[5] == CP_BSSAP_PROTOCOL_TAG)
   {
    if (evt->data[15] == 0x04)  //CP_BSSAP_MD_PROTOCOL
        {
                if ((evt->data[17] >= 0x01) && (evt->data[17] <= 0x20))
                {
        switch (evt->data[17])
                {
                case BSSAP_EENCODE:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_EENCODE:"));
                break;
                case BSSAP_EDECODE:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_EDECODE:"));
                break;
                case BSSAP_EINVMESSAGE:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_EINVMESSAGE:"));
                break;
                case BSSAP_ECICNOTFOUND:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ECICNOTFOUND:"));
                break;
                case BSSAP_ENORESETACK:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENORESETACK:"));
                break;
                case BSSAP_ENOBLKACK:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENOBLKACK:"));
                break;
                case BSSAP_ENOUNBLKACK:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENOUNBLKACK:"));
								break;
								case BSSAP_ENORESETCKTACK:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENORESETCKTACK:"));
                break;
                case BSSAP_EUNEQUIPCKT :
                        ISIL_DEBUG_TRACE(("CP_BSSAP_EUNEQUIPCKT:"));
                break;
                case BSSAP_ENORELEASECMP:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENORELEASECMP:"));
                break;
                case DTAP_EENCODE:
                        ISIL_DEBUG_TRACE(("CP_DTAP_EENCODE:"));
                break;
                case BSSAP_ECKTPROC:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ECKTPROC:"));
                break;
                case BSSAP_EASSREQFAIL:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_EASSREQFAIL:"));
                break;
                case BSSAP_ENOCKTGRPBLKACK:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENOCKTGRPBLKACK:"));
                break;
                case BSSAP_ENOCKTGRPUNBLKACK:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENOCKTGRPUNBLKACK:"));
                break;
                case BSSAP_EMSGSENTFAIL:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_EMSGSENTFAIL:"));
                break;
		case BSSAP_ENOHANDOVERCMD:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_ENOHANDOVER_COMMAND:"));
                break;
                default :
                    break;
                          }
                }
        }
}


//   else if (evt->data[5] == CP_BSSAP_NETWORK_TAG)
   else if (evt->data[5] == CP_BSSAP_MANAGEMENT_TAG)
   {
		if (evt->data[6] == BSSAP_MD_NETWORK)
        {
          switch (evt->data[7])
                {
                case CP_MTP_RESUME:
                        ISIL_DEBUG_TRACE(("CP_MTP_RESUME:"));
                break;
                case CP_MTP_PAUSE:
                        ISIL_DEBUG_TRACE(("CP_MTP_PAUSE:"));
                break;
                case CP_MTP_STATUS:
                        ISIL_DEBUG_TRACE(("CP_MTP_STATUS:"));
                break;
                case CP_SCCP_ALLOWED:
                        ISIL_DEBUG_TRACE(("CP_SCCP_ALLOWED:"));
                break;
                case CP_SCCP_PROHIBIT:
                        ISIL_DEBUG_TRACE(("CP_SCCP_PROHIBIT:"));
                break;

                default :
                    break;
                  }
        }
}
   else if (evt->data[5] == CP_BSSAP_SCCP_TAG)
   {	
		switch (evt->data[6])
                {
								case CP_SCCP_ACCEPT:
                        ISIL_DEBUG_TRACE(("TO NETWORK-CP_SCCP_ACCEPT:SCCP-CC"));
                break;
                case CP_SCCP_RELEASE:
                        ISIL_DEBUG_TRACE(("TO NETWORK-CP_SCCP_RELEASE:SCCP-REL"));
                break;
                case CP_SCCP_REJECT:
                        ISIL_DEBUG_TRACE(("TO NETWORK-CP_SCCP_REJECT:SCCP-CREF"));
                break;
                case CP_BSSAP_CON_ESTD:
                        ISIL_DEBUG_TRACE(("FROM NETWORK-CP_BSSAP_CON_ESTD:SCCP-CC"));
                break;
                case CP_BSSAP_CON_REL:
                        ISIL_DEBUG_TRACE(("FROM NETWORK-CP_BSSAP_CON_REL:SCCP-REL"));
                break;
                case CP_BSSAP_CON_REF:
                        ISIL_DEBUG_TRACE(("FROM NETWORK-CP_BSSAP_CON_REF:SCCP-CREF"));
                break;
								case CP_BSSAP_CON_ERR:
                        ISIL_DEBUG_TRACE(("CP_BSSAP_CON_ERR:SCCP-CERR"));
                break;


        }
}
#ifdef TRACE_DUMP
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,evt->data,evt->len);
#endif
#endif

}



