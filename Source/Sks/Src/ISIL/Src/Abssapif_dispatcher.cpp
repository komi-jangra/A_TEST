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
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.8  2007/08/01 10:41:41  cvsadmin
 * LOG: SMS  Patch  "event  length change to  BSSAP_DATA_LEN
 * LOG:
 * LOG: Revision 1.7  2007/04/17 08:35:37  ashutosh.singh
 * LOG: Logger Lib related changes
 * LOG:
 * LOG: Revision 1.6  2007/03/20 04:49:34  ashutosh.singh
 * LOG: Trace and DTAP Messages handling  related changes
 * LOG:
 * LOG: Revision 1.5  2007/02/26 05:15:47  cvsadmin
 * LOG: Changes done  for  Length in SSA  and  MTP RESUME
 * LOG:
 * LOG: Revision 1.4  2007/02/19 09:03:22  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2007/02/19 08:55:04  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/01/11 13:35:43  ashutosh.singh
 * LOG: *** empty log message ***
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
 * ID: $Id: Abssapif_dispatcher.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: Abssapif_dispatcher.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $"



#include <bssapif_common.h>
#include <bssapif_trace.h>
#include <bssapif_dispatcher.h>
#include <bssapif_socket.h>
#include <BSSAP++.h>
#include "trace.h"



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
/*
#define ISIL_TRACE_DEBUG   0x01
#define ISIL_TRACE_ERROR   0x02
#define ISIL_TRACE_WARNING 0x03
*/

#define ITS_BSSAP_SRC 20
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

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessSCCPMessage\n"));

    // Call reference id
    callrefId |= evt->data[index++];
    callrefId |= evt->data[index++] << 8;

    if (evt->data[1] == CP_SCCP_ACCEPT)
    {
        ISIL_DEBUG_TRACE(("ProcessSCCPMessage: Received CC\n"));
        ret  = api.AcceptConnection(callrefId);
    }
    else if (evt->data[1] == CP_SCCP_REJECT)
    {
        ISIL_DEBUG_TRACE(("ProcessSCCPMessage: Received CREF\n"));
        ret = api.RejectConnection(callrefId);
    }
    else if (evt->data[1] == CP_SCCP_RELEASE)
    {
        ISIL_DEBUG_TRACE(("ProcessSCCPMessage: Received REL\n"));
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

     ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessCICMessage\n"));
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
    ITS_USHORT len = 0;
    ITS_INT index = 1;
    BSSAP_Message* dec = NULL;
    BSSAPData bd;
    BSSAP_Api* api = NULL;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessBSSAPMessage\n"));

   
     for (int i=0 ;i<evt->len;i++)
       {
          printf("%x\t ",evt->data[i]);
       }
       printf("\n");
    

    memset(&bd, 0, sizeof(BSSAPData));
   
    // BSC Id
    bd.bssId = evt->data[index++];

    // Call ref id
    bd.callrefId  |= evt->data[index++];
    bd.callrefId  |= evt->data[index++] << 8;


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
       ISIL_ERROR_TRACE(("ProcessBSSAPMessage: Fail to decode BSSAP data\n"));
        return (!ITS_SUCCESS);
    }

  if (bd.mssgDisc==evt->data[index])
   {
     switch(bd.mssgDisc)
      {
      case BSSAP_MD_BSSMAP:
       {
         ISIL_DEBUG_TRACE(("ProcessBSSAPMessage: Received BSS-MAP\n")); 
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
    break;
    case BSSAP_MD_DTAP : 
      {
         ISIL_DEBUG_TRACE(("ProcessBSSAPMessage: Received BSS-DTAP\n"));
        api = new BSSAP_Api;
        api->SetBssId(bd.bssId);
        api->SetCallRef(bd.callrefId);
        api->SetAppId(bd.appId);
        api->SetMssgDisc(BSSAP_MD_DTAP);
        api->SetMssgType(bd.mssgType);

/*IMR requirement 14 march         api->SetBSSAPdata(dec);*/
       
        api->SetDTAPdata(&evt->data[index],len);
        ret = api->SendBSSAPMessage(ref);

        delete api;
        api = NULL;
     }
    break;
    default :
         ISIL_DEBUG_TRACE(("ProcessBSSAPMessage: Unknown Msg Discriminator\n"));
    
      
   }/*end of switch*/
 }/*end of if*/
 else
 {
         ISIL_DEBUG_TRACE(("ProcessBSSAPMessage:Disc is not match in header as well as in Msg\n"));
         ret=-1;

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

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessCFGMessage\n"));
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

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessSocketEvent\n"));
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
       ISIL_ERROR_TRACE(("ProcessCFGMessage: Received unknown event\n"));
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
   // ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 5;
    ITS_USHORT len = 0;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;
//    BSSAP_Message* dtap = NULL;
   // ITS_OCTET*data=NULL;
    ITS_OCTET  data[BSSAP_DATA_LEN];

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkDTAP\n"));
//    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, 100);
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, BSSAP_DATA_LEN);


    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x01;

    // Tag

    ev.data[index++] = CP_BSSAP_MSG_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;

    //  App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;


    // Message discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message Name/Type
    ev.data[index++] = api->GetMssgType();

   /*change due to IMR Requirement*/
    /*dtap = api->GetBSSAPdata();

    if (BSSAP_Message::Encode(buff, len, dtap) != ITS_SUCCESS)
    {
        BSSAPIF_TRACE_ERROR(("ProcessNetworkDTAP: Encode of BSS-DTAP failed"));

        return (!ITS_SUCCESS);
    }

    if (dtap)
    {
        delete dtap;
    }
   */
     
   /*end of IMR Requirement*/
    api->GetDTAPdata(data,&len);
    // BSSAP message buffer length
    ev.data[index++] = len;

    // BSSAP messge buffer

//    memcpy(&ev.data[index],buff, len);
    memcpy(&ev.data[index],data,len);
    
   /* if (api)
    {
        delete api ;
        api=NULL;
    }*/

    // Actual length
    len = index + len;
    
    ev.len = len;
    ev.data[3] =len ;
    ev.data[4] = 0;

    /*printf("\nISIL_TARCE: Data received from BSSAP: \n");

    for(int i=0;i<ev.len;i++)
    {
    printf("%02x",ev.data[i]);
    }
    printf("\n...........................................\n"); */
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
BSSAPDispatcher::ProcessNetworkMAP(BSSAP_Api* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET index = 5;
    ITS_INT len = 0;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;
    BSSAP_Message* map = NULL;

     ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkMAP\n"));
    // Total length = (BSSAPData structure)
 //  ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, 100);
   ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, BSSAP_DATA_LEN);

    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x01;
    // Tag
    ev.data[index++] = CP_BSSAP_MSG_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;

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
        ISIL_ERROR_TRACE(("ProcessNetworkMAP: Encode of BSS-MAP falied\n"));
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

    ev.data[3] =len ;
    ev.data[4] = 0;
    ev.len = len;

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
BSSAPDispatcher::ProcessNetworkTimeout(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 5;
    ITS_INT len = 0;
    ITS_EVENT ev;

    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkTimeout\n"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, sizeof(ITS_OCTET)*8);
    ev.data[0] = 0xc1;
    ev.data[1] = 0x01;
    ev.data[2] = 0x01;
    ev.data[3] = 0x08;
    ev.data[4] = 0x00;
    // Tag
    ev.data[index++] = CP_BSSAP_TIMEOUT_TAG;

    // Message Discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message name
    ev.data[index++] = api->GetErrCode();

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
BSSAPDispatcher::ProcessNetworkProtocol(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET index = 5;
    ITS_CTXT callrefId = 0;
    ITS_USHORT pcm = 0;
    ITS_CTXT appId = 0;
    ITS_EVENT ev;

      ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkProtocol\n"));
    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, (sizeof(BSSAPData)+5));
    
     ev.data[0] = 0xc1;
      ev.data[1] = 0x01;
      ev.data[2] = 0x01;
    // Tag
    ev.data[index++] = CP_BSSAP_PROTOCOL_TAG;

    // BSC Id
    ev.data[index++] = api->GetBssId();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;

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
      ev.data[3] = (ev.len)&0xff;;
      ev.data[4] = ((ev.len&0xff)>>8);




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
BSSAPDispatcher::ProcessNetworkStaus(BSSAPError* api)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT dpc = 0;
    ITS_OCTET index = 5;
    ITS_INT len = 0;
    ITS_EVENT ev;
    ITS_USHORT src;
    ITS_OCTET ni=0;
    ITS_OCTET SSN=0,ssn=0;    

     ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkStaus\n"));

    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, 11);
      src=0x20;

      ev.data[0] = 0xc1;
      ev.data[1] = 0x01;
      ev.data[2] = 0x01;
    // Tag
    ev.data[index++] = CP_BSSAP_NETWORK_TAG;

    // Message Discriminator
    ev.data[index++] = api->GetMssgDisc();

    // Message name
    ev.data[index++] = api->GetErrCode();
	// Get DPC

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
       ret=CL_WriteEventMM(CL_Handle_MM,&ev);
       if (ret!=ITS_SUCCESS)
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

     ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkSCCPInd\n"));
    // Total length = (BSSAPData structure)
    ITS_EVENT_INIT(&ev, ITS_BSSAP_SRC, (sizeof(BSSAPData)+5));
      ev.data[0] = 0xc1;
      ev.data[1] = 0x01;
      ev.data[2] = 0x01;
  // Tag
    ev.data[index++] = CP_BSSAP_SCCP_TAG;

    // Message name
    ev.data[index++] = api->GetMssgType();

    // Call ref Id
    callrefId = api->GetCallRef();
    ev.data[index++] = callrefId & 0x000000FF;
    ev.data[index++] = (callrefId & 0x0000FF00) >> 8;

    // App Id
    appId = api->GetAppId();
    ev.data[index++] = appId & 0x000000FF;
    ev.data[index++] = (appId & 0x0000FF00) >> 8;


    ev.len = index;
      ev.data[3] = (ev.len)&0xff;;
      ev.data[4] = ((ev.len&0xff)>>8);

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
 
    ISIL_DEBUG_TRACE(("BSSAPDispatcher: ProcessNetworkEvent\n"));
    memcpy(&address, event.GetData(), sizeof(&address)); 

    bssap_api = (BSSAP_Api*)address;

    if (!bssap_api)
    {
        ISIL_ERROR_TRACE(("ProcessNetworkEvent: Invalid data address\n"));
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
