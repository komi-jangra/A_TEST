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
 *  ID: $Id: bssap_discriminator.cpp,v 1.7 2008/04/21 05:24:58 bsccs2 Exp $
 *
 * LOG: $Log: bssap_discriminator.cpp,v $
 * LOG: Revision 1.7  2008/04/21 05:24:58  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.6  2008/02/19 00:25:51  ankur.sharda
 * LOG: Changed for Decoder
 * LOG:
 * LOG: Revision 1.5  2008/02/07 10:12:57  amaresh.prasad
 * LOG: Updated for Appid database table
 * LOG:
 * LOG: Revision 1.4  2008/02/01 02:41:03  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2008/02/01 04:23:15  amaresh.prasad
 * LOG: Updated for abnormal case & error cause
 * LOG:
 * LOG: Revision 1.2  2008/01/17 05:04:48  amaresh.prasad
 * LOG: Bugfix 1815 without maintain Call state message type  of DTAP message
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/08/06 06:30:54  amaresh.prasad
 * LOG: Updated for CS2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 03:39:14  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.2.15  2007/01/24 05:57:07  sjaddu
 * LOG: Sending Optional data in ClassmarkUpdate message IssueId:5218 and 5219.
 * LOG:
 * LOG: Revision 1.1.2.14  2006/10/07 12:35:00  sjaddu
 * LOG: Added IMSI_Detach procedure.
 * LOG:
 * LOG: Revision 1.1.2.13  2006/09/14 16:02:24  sjaddu
 * LOG: Fix for SLR and DLR values with morethan 3-octets.
 * LOG:
 * LOG: Revision 1.1.2.12  2006/07/14 16:59:39  sjaddu
 * LOG: Connection Id is changed to U INT.
 * LOG:
 * LOG: Revision 1.1.2.11  2006/02/21 06:14:42  yranade
 * LOG: Fix for issue ID: 3273
 * LOG:
 * LOG: Revision 1.1.2.10  2005/12/13 09:36:05  mkrishna
 * LOG: Stack is opreting on his own memory
 * LOG:
 * LOG: Revision 1.1.2.9  2005/12/05 09:18:22  mkrishna
 * LOG: Pegs implementation and cause value modified
 * LOG:
 * LOG: Revision 1.1.2.8  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.7  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/26 20:19:13  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/26 06:40:32  adutta
 * LOG: Taken care of UDT Bssmap
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/19 19:58:55  adutta
 * LOG: Interface related changes
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

#include <bssap.h>
#include <bssap_discriminator.h>
#include <bssap_error.h>
#include <bssap_calldb.h>
#include <bssap_sccphandler.h>
#include <bssap_pegs.h>
#include <bssap-alarm.h> 
#include <bssap_appiddb.h>
#include <bssap_apiid.h>
#include <bssap_cfgdb.h>
#include <bssapif_common.h>

ITS_INT  CheckParameters(ITS_OCTET msgDisc,BSSAP_Message* iMsg);
ITS_OCTET reject_cause; 

/*implementation:internal
*
* PURPOSE:
*       Handle in messages from network or remote
* INPUT:
*      buffer, length, call object, nwId
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if handled successfully
*       Error, if any problem
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0340, ID :: D0350,
*                        ID :: D0360, ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 Bug Fix 2675,486,490,491 & HO-Impl 
*/
ITS_INT
BSSAP_Discriminator::ProcessInBSSAPMessage(ITS_OCTET* data,
                                        ITS_UINT len,
                                        BSSAP_Call* call,
                                        ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT ret_cause = 0;
    ITS_OCTET ercause = 0;	
    ITS_OCTET mDisc;
    ITS_OCTET msgType;
    BSSAP_Message* dec = NULL;
    BSSAP_Map bssmap;
    BSSAP_Interface bssIf;
    BSSAP_Error err;
    ITS_OCTET sbuff[BSSAP_DATA_LEN];
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* A dded by Amaresh for Alarm 21-07-08 */

    memcpy(&sbuff, data, len);
    ITS_OCTET msgDisc = data[0]; /* Added by Amaresh for check parameters */
    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessInBSSAPMessage\n"));

    if (data[0] == BSSAP_MD_DTAP)
    {
        //BSSAP_DEBUG(("BSSAP_Discriminator: DTAP payload\n"));

        if (!call)
        {
            BSSAP_ERROR(("ProcessInBSSAPMessage: DTAP suspected in UDT\n"));
            err.SendConfunsion(call, C_PROTOCOL_ERROR, nwId, NULL, 0);
            return (ITS_SUCCESS);
        }
          call->SetBssId(nwId); 
         call->SetBSSAPData(data, len);
    //     PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DTAP_RECV);
        BSSAPPEG_IncrPeg(PEG_BSSAP_DTAP_RECV,nwId);
         // Send it to application transparently
         bssIf.DispatchDtapToApp(call);
    }
    else if (data[0] == BSSAP_MD_BSSMAP)
    {
        /* Enhanced by Amaresh 25-01-08*/
				ret_cause = BSSAP_Message::Decode(data, len, &dec);
        //BSSAP_DEBUG(("Cause value return from Decode: %d\n", ret_cause));
        /* if (BSSAP_Message::Decode(data, len, &dec) != ITS_SUCCESS) */
      	if(ret_cause != ITS_SUCCESS)
         {
            if((data[2] == BSSAP_MSG_CIPHER_MODE_CMD)
              || (data[2] == BSSAP_MSG_ASSIGN_REQUEST)
                || (data[2] == BSSAP_MSG_CLEAR_COMMAND)
                  || (data[2] == BSSAP_MSG_HANDOVER_REQUEST)
                    || (data[2] == BSSAP_MSG_HANDOVER_COMMAND)
                      || (data[2] == BSSAP_MSG_CLASSMARK_UPDATE)
                        || (data[2] == BSSAP_MSG_CLASSMARK_REQUEST)
                          || (data[2] == BSSAP_MSG_CONFUSION)
                            || (data[2] == BSSAP_MSG_HANDOVER_REQUIRED_REJECT)
                              || (data[2] == BSSAP_MSG_HANDOVER_SUCCEEDED)
                                || (data[2] == BSSAP_MSG_MSC_INVOKE_TRACE))
            {
            }
            else
            {
                err.SendConfunsion(call, ITS_EBSSAP_UNKNOWN_MSG_TYPE, nwId, data, len);
                return (!ITS_SUCCESS);
            }
         
            BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload " 
                                           " decode failed\n"));
           	if(ret_cause == ITS_EMISSMAND) /* ITS_EMISSMAND -12 */
                     ercause = C_INFO_ELEMENT_MISSING;
           else
              if(ret_cause == ITS_EBSSAP_UNKNOWN_IE)
                    ercause = c_UNKNOWN_INFO_ELEMENT;
              else
                  if(ret_cause == ITS_EBSSAP_UNKNOWN_MSG_TYPE)
                   {
                     ercause = C_UNKNOWN_MSG_TYPE;
                     /* Added by Amaresh for Alarm 21-07-08 */
                     cfgdata = db.FetchRPCEntry(nwId);
                     if (cfgdata)
                     {
                          DPC = cfgdata->rpc;
                     }
                     /* Added by Amaresh for Alarm 21-07-08 */
                     BSSAP_Alarm_CCITT(5116,__FILE__,__LINE__,"dpc %d",DPC);
                  }
                 else
                      if(ret_cause == ITS_EINVALIDARGS)
                      ercause = C_ICORRECT_VALUE;
                      else
                           if(ret_cause == C_PROTOCOL_ERROR)
                           ercause = C_PROTOCOL_ERROR;
                           else
                               if(ret_cause == ITS_EINVARGSLEN)
                               ercause = C_INVALID_MSG_CONTENT;
                               else
                               ercause = C_INVALID_MSG_CONTENT;

         BSSAP_DEBUG(("Cause value Manipulation from Decoder: %d\n", ercause));
         /* Enhanced by Amaresh 25-01-08*/
         bssIf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EDECODE);
         /* fix for bug id 486 if mandatory parameter missing like Ass req messgae -->Ass Fail */
         if(data[2] == BSSAP_MSG_ASSIGN_REQUEST)
           {
               BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                         " decode failed & send Assignment failure of msg type Ass Req\n"));
               err.SendAssignmentFail(call,ercause,nwId);  /*for bug id 486 */
           }
        else
           {
                 BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                                           " decode failed & do nothing\n"));
           }
         /* fix for bug id 486 if mandatory parameter missing like Ass req messgae -->Ass Fail */
         /* fix for bug id 490 & 491  if mandatory parameter missing like CipherMCmd messgae -->cipherMReject */
        if(data[2] == BSSAP_MSG_CIPHER_MODE_CMD)
           {
                 BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                         " decode failed & send Cipher Mode Reject of msg type CipherMCommand \n"));

               err.SendCipherModeReject(call,ercause,nwId);  /*for bug id 490 & 491*/
          }
        else
          {
                 BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                                           " decode failed & do nothing\n"));
          }
          /* Added by Amaresh for Ho-Req decode failure then BSSAP stack send Ho-Fai as on dated 19-05-08 */
			 if(data[2] == BSSAP_MSG_HANDOVER_REQUEST)
          {
                 BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                         " decode failed & send HO-FAI of msg type HO-REQ \n"));
                call->SetBssId(nwId);
								call->SetCallType(HO_CALL);
								call->SetHandOver(1);
				        call->SetHandOverNewBss(1); /* Added by Amaresh for newBss */
       					call->SetAppId(0);/* Added by Amaresh for newBss appid to zero as on dated 19-05-08 */
								call->SetMssgType(BSSAP_MSG_HANDOVER_REQUEST);
				     		err.SendHandoverFail(call,ercause,nwId);	         
								
								/* Added by Amaresh for send HO-FAI data to BSC-APP 03-07-08*/
								call->SetBSSAPData(data, len);
								BSSAP_DEBUG(("ProcessInBSSAPMessage: Set BSSAP data when HO-REQ decode failed \n"));
               	bssIf.DispatchMapErrToApp(call, dec,BSSAP_EDECODE);
								/* Added by Amaresh for send HO-FAI data to BSC-APP 03-07-08*/
			 
          }
        else
          {
                 BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                                           " decode failed & do nothing\n"));
          }
          /* Added by Amaresh for Ho-Req decode failure then BSSAP stack send Ho-Fai as on dated 19-05-08 */
						
         /* fix for bug id 490 & 491 if mandatory parameter missing like CipherMCmd messgae -->cipherMReject */
	        err.SendConfunsion(call, ret_cause, nwId, data, len); /* Added by Amaresh for cause 25-01-08*/
            return (!ITS_SUCCESS);
       }
			if(dec) /* dec if zero 15-04-08 Bug fix 2657 by Amaresh*/
				{
            /* Enhanced by Amaresh for Decode & Encode check for Mandatory parameters */
            if (CheckParameters(msgDisc, dec) != ITS_SUCCESS)
            {
                  BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP Check mandatory parameter "                                           " decode failed\n"));
                  delete dec;
                  dec = NULL;
                  return (!ITS_SUCCESS);
            }
            /* Enhanced by Amaresh for Decode & Encode check for Mandatory parameters */
          // CO MAP
	  msgType = dec->GetMsgType();
          if (call)
           {
                call->SetBssId(nwId);
	           /* call->SetBSSAPData(data, len); */
	           /* ret = bssmap.ProcessInBSSMAPMessage(call, dec, data, len);*/
              call->SetBSSAPData(sbuff, len);
              ret = bssmap.ProcessInBSSMAPMessage(call, dec, sbuff, len);
            BSSAP_CRITICAL(("RECV FROM MSC:cref[%04x] AppId[%04x]:Incoming DT1 Msg: MsgType[%s] \n",call->GetSLR(),call->GetAppId(),BSSAP_MSG_TYPE_STR(msgType)));
           }
         else // UDT MAP
          {
					  	/* ret = bssmap.ProcessInBSSMAPUDTMessage(dec, nwId, data, len); */
              ret = bssmap.ProcessInBSSMAPUDTMessage(dec, nwId, sbuff, len);
              BSSAP_CRITICAL(("RECV FROM MSC:Incoming UDT Msg:MsgType[%s] \n",BSSAP_MSG_TYPE_STR(msgType)));
          }
		  } /* dec if zero 15-04-08 Bug fix 2657 by Amaresh */
		else
		  {
		     BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                                           "decode failed & fill dec to zero\n"));
    		 bssIf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EDECODE);
    	   err.SendConfunsion(call, C_INVALID_MSG_CONTENT, nwId, data, len);
		     return (!ITS_SUCCESS);		

		  } /* dec if zero 15-04-08 Bug fix 2657 by Amaresh */

        if (ret == ITS_SUCCESS)
        {
       //     PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_RECV);
        BSSAPPEG_IncrPeg( PEG_BSSAP_MAP_RECV,nwId);
        }  
    }
    else
    {
        /* Added by Amaresh for Alarm 21-07-08 */
        cfgdata = db.FetchRPCEntry(nwId);
        if (cfgdata)
         {
           DPC = cfgdata->rpc;
         }
         /* Added  by Amaresh for Alarm 21-07-08 */

         BSSAP_ERROR(("ProcessInBSSAPMessage: Message nether MAP nor DTAP\n"));
				 BSSAP_Alarm_CCITT(5119,__FILE__,__LINE__,"dpc %d",DPC);	
    }

    if(dec)
    { 
       delete dec;
       dec = NULL;
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
BSSAP_Discriminator::ProcessSCCPHandellingMessage(ITS_Event& ev)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_EVENT evt;
    ITS_OCTET index = 2;
    ITS_CTXT callrefId = 0;
    ITS_CTXT appId = 0;	
    BSSAP_Api api;
		ITS_OCTET   cause;
    BSSAPData data;


    evt = ev.GetEvent();
    memcpy(&data, evt.data, sizeof(BSSAPData));

		BSSAP_DEBUG(("ProcessSCCPHandellingMessage\n"));
    // Call reference id as per LARGE CONTEXT
    callrefId = data.callrefId;
     // App Id
    appId  = data.appId;
		
    BSSAP_DEBUG(("ProcessSCCPHandellingMessage:: APP id  = %d Call Reference id = %d \n", appId,callrefId));
		cause = data.hofacause; 

   	ret =  api.ReleasedConnection(callrefId,appId,cause); 

    return (ret);
}



/*implementation:internal
*
* PURPOSE:
*       Handle out messages from application
* INPUT:
*       event
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if handled successfully
*       Error, if any problem
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0340, ID :: D0350,
*                        ID :: D0360, ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 Alarm   
*/
ITS_INT
BSSAP_Discriminator::ProcessOutBSSAPMessage(ITS_Event& ev)
{
    ITS_INT ret = 0;
    ITS_UINT addr; 
    ITS_CTXT callrefId = 0; 
    ITS_USHORT channel = 0;
    BSSAP_Map bssmap;
    BSSAPData data;
    ITS_EVENT evt;
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */

    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessOutBSSAPMessage\n"));
    evt = ev.GetEvent(); 
    memcpy(&data, evt.data, sizeof(BSSAPData));
    if (data.mssgDisc == BSSAP_MD_DTAP)
    {
        BSSDtap* dtap = new BSSDtap(&data);
        ret = ProcessOutDTAPMessage(dtap);
        if (ret == ITS_SUCCESS)
        {
//            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DTAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_DTAP_SEND, data.bssId);
        }
        delete dtap;
    }
    else if (data.mssgDisc == BSSAP_MD_BSSMAP)
    {
        BSSMap* map = new BSSMap(&data);
        ret = bssmap.ProcessOutBSSMAPMessage(map, data.u.MAPdata.mapMsg, data.u.MAPdata.len);
        if (ret == ITS_SUCCESS)
        {
//            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND, data.bssId);
        }
        delete map;
    }
    else
    {
        BSSAP_ERROR(("ProcessOutBSSAPMessage: Invalid BSSAP message\n"));
        return (!ITS_SUCCESS);
    }
    if (ret != ITS_SUCCESS)
    {
     /* Added by Amaresh for Alarm 21-07-08 */
     cfgdata = db.FetchRPCEntry(data.bssId);
     if (cfgdata)
      {
        DPC = cfgdata->rpc;
      }
     /* Added by Amaresh for Alarm 21-07-08 */
        BSSAP_ERROR(("ProcessOutBSSAPMessage: Failed to dispatch message\n"));
				BSSAP_Alarm_CCITT(5120,__FILE__,__LINE__,"dpc %d",DPC);
    }
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Handling the complete layer3 info  messages from application
* INPUT:
*       event
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if handled successfully
*       Error, if any problem
* COMMENTS:
* 
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0340, ID :: D0350,
*                        ID :: D0370, ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 Appid table,Alarm,Memory leak 
*/
ITS_INT
BSSAP_Discriminator::ProcessLayer3BSSAPMessage(ITS_Event& ev)
{
    ITS_INT ret = 0;
    ITS_CTXT callrefId = 0;
    ITS_USHORT channel = 0;
    ITS_OCTET mType = 0;
    ITS_INT len = 0;
    ITS_EVENT evt;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    ITS_OCTET  sbuff[BSSAP_DATA_LEN];
    BSSAP_Interface bssIf;
    BSSAP_Map bssmap;
    const BSSAP_Element* ie;
    BSSAP_Message* mapData = NULL;
    BSSAPData data;
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    ITS_UINT CIC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */
   
 
    BSSAP_Call* call = new BSSAP_Call();
    BSSAP_AppId* appid = new BSSAP_AppId();
    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessLayer3BSSAPMessage\n"));
    evt = ev.GetEvent();
    memcpy(&data, evt.data, sizeof(BSSAPData));
    memcpy(&sbuff, &data.u.MAPdata.mapMsg, data.u.MAPdata.len);    
    if (BSSAP_Message::Decode(data.u.MAPdata.mapMsg, data.u.MAPdata.len, &mapData) != ITS_SUCCESS)
    {
            BSSAP_ERROR(("ProcessLayer3BSSAPMessage: BSS-MAP payload "
                                           " decode failed\n"));
		     		/* memeory free in case of failure 10-06-08 */
						delete call;
						call = NULL;
						delete appid;
						appid = NULL;	
				   /* memeory free in case of failure 10-06-08 */
            return (!ITS_SUCCESS);
    }
    ie = mapData->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
   if (!ie)
    {
        BSSAP_ERROR(("ProcessLayer3BSSAPMessage: ie not found\n"));
            /* memeory free in case of failure 10-06-08 */
            delete call;
            call = NULL;
            delete appid;
            appid = NULL;
						delete mapData;
						mapData = NULL;
           /* memeory free in case of failure 10-06-08 */ 
           return (!ITS_SUCCESS); 
    }  
    ((BSSAP_L3Info*)ie)->GetL3Info(buff, len);

    //mType = buff[DTAP_MSG_P0S];
    mType = buff[L3MSG_TYPE_POS]; //Modified for Issue 3273

    if (mType == BSSAP_MSG_CM_SERVICE_REQUEST)
    {
        BSSAP_DEBUG(("ProcessLayer3BSSAPMessage: CM_SERVICE_REQUEST\n"));
        call->SetCallType(MO_CALL);
       // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CMSERV_SEND);
        BSSAPPEG_IncrPeg(PEG_BSSAP_CMSERV_SEND,data.bssId);
    }
    else if (mType == BSSAP_MSG_PAGING_RESPONSE)
    {
        BSSAP_DEBUG(("ProcessLayer3BSSAPMessage: PAGING_RESPONSE\n"));
				call->SetCallType(MT_CALL);
       // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_PAGRSP_SEND);
        BSSAPPEG_IncrPeg(PEG_BSSAP_PAGRSP_SEND,data.bssId);
    }
    else if (mType == BSSAP_MSG_LOCATION_UPDATING_REQUEST)
    {
        BSSAP_DEBUG(("ProcessLayer3BSSAPMessage: LOCATION_UPDATE\n"));
        call->SetCallType(LU_CALL);
    }
    else if (mType == BSSAP_MSG_IMSI_DETACH_INDICATION)
    {
        BSSAP_DEBUG(("ProcessLayer3BSSAPMessage: IMSI_DETACH\n"));
        call->SetCallType(IMSI_DETACH);
    }
    else
    {
       /* Added by Amaresh for Alarm 21-07-08 */
       cfgdata = db.FetchRPCEntry(data.bssId);
       if (cfgdata)
        {
          DPC = cfgdata->rpc;
        }
        /* Added by Amaresh for Alarm 21-07-08 */
        BSSAP_ERROR(("ProcessLayer3BSSAPMessage: Wrong L3 %d\n", mType));
		    BSSAP_Alarm_CCITT(5116,__FILE__,__LINE__,"dpc %d",DPC);
		    /* memeory free in case of failure 10-06-08 */
        delete call;
        call = NULL;
        delete appid;
        appid = NULL;
        delete mapData;
        mapData = NULL;
        /*memeory free in case of failure 10-06-08 */
        return (!ITS_SUCCESS);
   }
    /* setting appid verses slr & dlr by Amaresh 04-02-08*/
    appid->SetAppId(data.appId);
    appid->SetSLR(data.callrefId);
    ret = BSSAP_AppidDB::GetShared().Add(appid);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutL3Message: Fail to update CDR of Appid \n"));
    }
    delete appid;
    appid = NULL;
    /* setting appid verses slr & dlr by Amaresh 04-02-08*/
    call->SetAppId(data.appId);
    call->SetSLR(data.callrefId);
    /*  call->SetBSSAPData(data.u.MAPdata.mapMsg, data.u.MAPdata.len); */
    call->SetBSSAPData(sbuff, data.u.MAPdata.len);
    call->SetBssId(data.bssId);
    call->SetMssgType(mType);
    BSSAP_DEBUG(("ProcessLayer3BSSAPMessage: Connection Id  %d\n", call->GetAppId()));
    bssmap.ProcessOutL3Message(call);
    delete mapData;
		mapData = NULL;
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       processing outgoing DTAP messages
* INPUT:
*       payload object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if done successfully
*       Error, if error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0340, ID :: D0360,
*                        ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 Bug Fix 1815
*/
ITS_INT
BSSAP_Discriminator::ProcessOutDTAPMessage(BSSAP_Api* msg)
{
    BSSAP_Call* call = NULL;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    ITS_USHORT len = 0;
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET mssgType = 0;
    BSSAP_SCCPHandler hndl;
    BSSDtap* dtap = (BSSDtap*)msg;
    ITS_OCTET mapBuff[BSSAP_DATA_LEN];
    ITS_USHORT mapLen   = 0;
    ITS_OCTET mapMsgGrp = 0;

    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessOutDTAPMessage\n"));
    dtap->GetDTAPdata(buff, &len);
    mssgType = buff[DTAP_MSG_P0S];
    call = BSSAP_CallDB::GetShared().Fetch(dtap->GetCallRef());
    if (!call)
    {  
        BSSAP_ERROR(("ProcessOutDTAPMessage: Call obj. not found \n"));
        return (ITS_ENOTFOUND);
    }  
    call->SetAppId(dtap->GetAppId());
    call->SetSLR(dtap->GetCallRef());
    /*
      Below mapBuff changes are for sending classmarkUpdate as
      MAP Message in a DTAP function. 
    */
    mapMsgGrp = buff[DTAP_MSG_P0S - 1];
    mapLen = len-1;
    if((mapMsgGrp == 0x06) && (mssgType == 0x16))
    {
        ITS_OCTET reqBuffLen = mapLen-5;
        mapBuff[0] = 0x00;
        mapBuff[1] = reqBuffLen + 3; 
        mapBuff[2] = 0x54;
        memcpy(&mapBuff[3], &buff[4], (reqBuffLen + 2)); 
        mapBuff[3] = 0x12; //Classmar2 IE
        if(reqBuffLen > 4)
        {
            mapBuff[8] = 0x13; //Classmark3 IE
        }
        call->SetBSSAPData(mapBuff, mapLen);
    }
    else
    {
        call->SetBSSAPData(buff, len);
    }
    /*Bug Fix by Amaresh for 1815 cannot maintain state in DTAP message. */
    /*   call->SetMssgType(mssgType);  */
    /*Bug Fix by Amaresh for 1815 cannot maintain state in DTAP message. */     
    ret = hndl.BSSAP_ProcessAPPdata(call);
    if (ret != ITS_SUCCESS)
    { 
        BSSAP_ERROR(("ProcessOutDTAPMessage: Fail to send DTAP message \n"));
        return (ITS_ESENDFAIL);
    } 
    return (ret);
}
/* Enhanced by Amaresh for Decoding & Encoding Checking for mandatory parameters */


//////////////////////////////////////////////////////////////////////
//
//     Check BSSMAP messages
//
//////////////////////////////////////////////////////////////////////

// Assignment Complete
ITS_INT
CheckBSSMAPMsgAssignComplete(BSSAP_Message *iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("Assignment Complete **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE); // To be Check,

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);
return (ITS_SUCCESS);
}

// Assignment Failure
ITS_INT
CheckBSSMAPMsgAssignFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("Assignment Failure **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return (!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);

    return (ITS_SUCCESS);
}

// Assignment Request
ITS_INT
CheckBSSMAPMsgAssignReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("Assignment Request **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    if(!ie)
    return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION);

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    ie = iMsg->FindIE(BSSAP_IEI_DOWNLINK_DTX_FLAG);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);

    ie = iMsg->FindIE(BSSAP_IEI_TALKER_FLAG);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR);

    ie = iMsg->FindIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND);

    ie = iMsg->FindIE(BSSAP_IEI_SERVICE_HANDOVER);

    return (ITS_SUCCESS);
}

// Handover Candidate Enquire
ITS_INT
CheckBSSMAPMsgHandoverCandidateEnq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Candidate Enquire **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_NUMBER_OF_MS);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);
 return (ITS_SUCCESS);
}

// Handover Candidate Response
ITS_INT
CheckBSSMAPMsgHandoverCandidateRsp(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Candidate Response **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_NUMBER_OF_MS);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Handover Command
ITS_INT
CheckBSSMAPMsgHandoverCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Command  **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    return (ITS_SUCCESS);
}

// Handover Complete
ITS_INT
CheckBSSMAPMsgHandoverComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Complete  **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);

    return (ITS_SUCCESS);
}

// Handover Detect
ITS_INT
CheckBSSMAPMsgHandoverDetect(BSSAP_Message* iMsg)
{
    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Detect does not have IE **** \n"));
    return (ITS_SUCCESS);
}
// Handover Failure
ITS_INT
CheckBSSMAPMsgHandoverFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Failure **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_RR_CAUSE);
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);

    return (ITS_SUCCESS);
}

// Handover Performed
ITS_INT
CheckBSSMAPMsgHandoverPerformed(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Performed **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);
    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);

    return (ITS_SUCCESS);
}
// Handover Request
ITS_INT
CheckBSSMAPMsgHandoverReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;
    const BSSAP_Element* cie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Request **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_ENCRYPTION_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1);
    cie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    if((!ie) && (!cie))
        return (!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
return (!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    ie = iMsg->FindIE(BSSAP_IEI_DOWNLINK_DTX_FLAG);

    ie = iMsg->FindIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED);

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3);
    ie = iMsg->FindIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1);

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);

    ie = iMsg->FindIE(BSSAP_IEI_TALKER_FLAG);

    ie = iMsg->FindIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);

    ie = iMsg->FindIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS);

    ie = iMsg->FindIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA);

    return (ITS_SUCCESS);
}

// Handover Request Acknowledge
ITS_INT
CheckBSSMAPMsgHandoverReqAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Request Acknowledge **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE); // Clearity Required,

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER);

    return (ITS_SUCCESS);
}

// Handover Required
ITS_INT
CheckBSSMAPMsgHandoverRequired(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;
    const BSSAP_Element* ieBSS;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Required **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_RESPONSE_REQUEST);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);

    ie = iMsg->FindIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1);

    ie = iMsg->FindIE(BSSAP_IEI_SPEECH_VERSION);

    ie = iMsg->FindIE(BSSAP_IEI_QUEUING_INDICATOR);

    return (ITS_SUCCESS);
}

// Handover Required Reject
ITS_INT
CheckBSSMAPMsgHandoverRequiredRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Required Reject **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// Handover Succeeded
ITS_INT
CheckBSSMAPMsgHandoverSucceeded(BSSAP_Message* iMsg)
{
    BSSAP_DEBUG(("BSSMAP MESSAGE ::Handover Succeeded does not have any IE **** \n"));
    return (ITS_SUCCESS);
}

// Clear Command
ITS_INT
CheckBSSMAPMsgClrCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Clear Command **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);
    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION);

    return (ITS_SUCCESS);
}

// Clear Complete
ITS_INT
CheckBSSMAPMsgClrComplete(BSSAP_Message* iMsg)
{
    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Clear Complete does not have any IE **** \n"));
    return (ITS_SUCCESS);
}

// Clear Request
ITS_INT
CheckBSSMAPMsgClrReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Clear Request **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// SAPI n Reject
ITS_INT
CheckBSSMAPMsgSAPInRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::SAPI n Reject **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_DLCI);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Confusion
ITS_INT
CheckBSSMAPMsgConfusion(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Confusion **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_DIAGNOSTICS);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Suspend
ITS_INT
CheckBSSMAPMsgSuspend(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Suspend does not have any IE **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_DLCI);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Resume
ITS_INT
CheckBSSMAPMsgResume(BSSAP_Message* iMsg)
{
const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Resume does not have any IE **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_DLCI);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Reset
ITS_INT
CheckBSSMAPMsgReset(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Reset **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// Reset Ack
ITS_INT
CheckBSSMAPMsgResetAck(BSSAP_Message* iMsg)
{
     //BSSAP_DEBUG(("BSSMAP MESSAGE ::ResetAck does not have any IE **** \n"));
     return (ITS_SUCCESS);
}

// Reset Circuit
ITS_INT
CheckBSSMAPMsgResetCircuit(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Reset Circuit **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Reset Circuit Ack
ITS_INT
CheckBSSMAPMsgResetCircuitAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Reset Circuit Ack **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
       return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Overload
ITS_INT
CheckBSSMAPMsgOverload(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Overload **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);

    return (ITS_SUCCESS);
}

// MSC Invoke Trace
ITS_INT
CheckBSSMAPMsgMSCInvokeTrace(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::MSC Invoke Trace **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_REFERENCE);
    if(!ie)
        return(!ITS_SUCCESS);
    ie = iMsg->FindIE(BSSAP_IEI_TRIGGER_ID);

    ie = iMsg->FindIE(BSSAP_IEI_TRANSACTION_ID);
    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);

    ie = iMsg->FindIE(BSSAP_IEI_OMC_ID);

    return (ITS_SUCCESS);
}

// BSS Invoke Trace
ITS_INT
CheckBSSMAPMsgBSSInvokeTrace(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::BSS Invoke Trace **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_TRACE_REFERENCE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_FORWARD_INDICATOR);

    ie = iMsg->FindIE(BSSAP_IEI_TRIGGER_ID);

    ie = iMsg->FindIE(BSSAP_IEI_TRANSACTION_ID);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);

    ie = iMsg->FindIE(BSSAP_IEI_OMC_ID);
return (ITS_SUCCESS);
}
// Block
ITS_INT
CheckBSSMAPMsgBlock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Block **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return (!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return (!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CONNECTION_RELEASE_REQUESTED);

    return (ITS_SUCCESS);
}

// Block Acknowledge
ITS_INT
CheckBSSMAPMsgBlockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Block Acknowledge **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return (!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// Unblock
ITS_INT
CheckBSSMAPMsgUnblock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Unblock **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return (!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Unblock Acknowledge
ITS_INT
CheckBSSMAPMsgUnblockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Unblock Ack **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return (!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Circuit Group Block
ITS_INT
CheckBSSMAPMsgCktGroupBlock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;
//BSSAP_DEBUG(("BSSMAP MESSAGE ::Circuit Group Block **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Circuit Group Block Ack
ITS_INT
CheckBSSMAPMsgCktGroupBlockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Circuit Group Block Ack **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// Circuit Group Unblock
ITS_INT
CheckBSSMAPMsgCktGroupUnblock(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Circuit Group Unblock **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Circuit Group Unblock Ack
ITS_INT
CheckBSSMAPMsgCktGroupUnblockAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    //BSSAP_DEBUG(("BSSMAP MESSAGE ::Circuit Group Unblock Ack **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if(!ie)
         return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// Unequipped Circuit
ITS_INT
CheckBSSMAPMsgUnequippedCkt(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Unequipped Circuit  **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);

    return (ITS_SUCCESS);
}

// Change Circuit
ITS_INT
CheckBSSMAPMsgChangeCkt(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Change Circuit  **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// Change Circuit Ack
ITS_INT
CheckBSSMAPMsgChangeCktAck(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Change Circuit Ack  **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Resource Request
ITS_INT
CheckBSSMAPMsgResourceReq(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Resource Request **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_PERIODICITY);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);
    ie = iMsg->FindIE(BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR);

    return (ITS_SUCCESS);
}

// Resource Indication
ITS_INT
CheckBSSMAPMsgResourceInd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;
BSSAP_DEBUG(("BSSMAP MESSAGE ::Resource Indication **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_AVAILABLE);

    ie = iMsg->FindIE(BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE);

    return (ITS_SUCCESS);
}

// Paging
ITS_INT
CheckBSSMAPMsgPaging(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Paging **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_IMSI);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_TMSI);

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_NEEDED);

    ie = iMsg->FindIE(BSSAP_IEI_eMLPP_PRIORITY);
    return (ITS_SUCCESS);
}

// Paging Response
ITS_INT
CheckBSSMAPMsgPagingResponse(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Paging Response **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);

    ie = iMsg->FindIE(BSSAP_IEI_MOBILE_IDENTITY);

    return (ITS_SUCCESS);
}

// Cipher Mode Command
ITS_INT
CheckBSSMAPMsgCipherModeCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Cipher Mode Command **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_ENCRYPTION_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION);

    ie = iMsg->FindIE(BSSAP_IEI_CIPHER_RESPONSE_MODE);

    return (ITS_SUCCESS);
}

// Cipher Mode Complete
ITS_INT
CheckBSSMAPMsgCipherModeComplete(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Cipher Mode Complete **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_MESSAGE_CONTENT);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM);

    return (ITS_SUCCESS);
}

// Cipher Mode Reject
ITS_INT
CheckBSSMAPMsgCipherModeRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Cipher Mode Reject **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Classmark Update
ITS_INT
CheckBSSMAPMsgClassmarkUpdate(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Classmark Update **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3);

    return (ITS_SUCCESS);
}

// Classmark Request
ITS_INT
CheckBSSMAPMsgClassmarkReq(BSSAP_Message* iMsg)
{
    BSSAP_DEBUG(("BSSMAP MESSAGE ::Classmark Request does not have any IE **** \n"));
    return (ITS_SUCCESS);
}

// Complete Layer 3 Information
ITS_INT
CheckBSSMAPMsgCompleteLayer3Info(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Complete Layer 3 Information **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LSA_IDENTIFIER_LIST);

    return (ITS_SUCCESS);
}
// Load Indication
ITS_INT
CheckBSSMAPMsgLoadInd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Load Indication **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_TIME_INDICATION);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER_LIST);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_RESOURCE_SITUATION);

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);

    return (ITS_SUCCESS);
}

// Queuing Indication
ITS_INT
CheckBSSMAPMsgQueuingInd(BSSAP_Message* iMsg)
{
    BSSAP_DEBUG(("BSSMAP MESSAGE ::QueuingIndication does not have any IE  **** \n"));
    return (ITS_SUCCESS);
}

// VGCSVBS Setup
ITS_INT
CheckBSSMAPMsgVGCSVBSSetup(BSSAP_Message* iMsg)
{
 const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS Setup  **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);
    if(!ie)
    return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);

    return (ITS_SUCCESS);
}

// VGCSVBS Setup Ack
ITS_INT
CheckBSSMAPMsgVGCSVBSSetupAck(BSSAP_Message* iMsg)
{
    BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS SetupAck does not have any IE   **** \n"));
    return (ITS_SUCCESS);
}

// VGCSVBS Setup Refuse
ITS_INT
CheckBSSMAPMsgVGCSVBSSetupRefuse(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS Setup Refuse **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// VGCSVBS Assign Req
ITS_INT
CheckBSSMAPMsgVGCSVBSAssignReq(BSSAP_Message* iMsg)
{
 const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS Setup Req **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_ASSIGNMENT_REQUIREMENT);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_GROUP_CALL_REFERENCE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_PRIORITY);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    ie = iMsg->FindIE(BSSAP_IEI_DOWNLINK_DTX_FLAG);

    ie = iMsg->FindIE(BSSAP_IEI_ENCRYPTION_INFORMATION);

    return (ITS_SUCCESS);
}

// VGCSVBSAssignRsult
ITS_INT
CheckBSSMAPMsgVGCSVBSAssignRsult(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS Assign Rsult **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CHANNEL_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);

    return (ITS_SUCCESS);
}

// VGCSVBSAssignFailure
ITS_INT
CheckBSSMAPMsgVGCSVBSAssignFailure(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS AssignFailure **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL);

    ie = iMsg->FindIE(BSSAP_IEI_CIRCUIT_POOL_LIST);
    return (ITS_SUCCESS);
}

// VGCSVBS Queuing Indication
ITS_INT
CheckBSSMAPMsgVGCSVBSQueuingInd(BSSAP_Message* iMsg)
{
     BSSAP_DEBUG(("BSSMAP MESSAGE ::VGCSVBS QueuingInd does not have any IE **** \n"));
     return (ITS_SUCCESS);
}

// HandOff Required Reject
ITS_INT
CheckBSSMAPMsgHORequiredRej(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::HandOff Required Reject **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);

    return (ITS_SUCCESS);
}

// Uplink Request
ITS_INT
CheckBSSMAPMsgUplinkReq(BSSAP_Message* iMsg)
{
  BSSAP_DEBUG(("BSSMAP MESSAGE ::UplinkRequest does not have any IE **** \n"));
  return (ITS_SUCCESS);
}

// Uplink Req Ack
ITS_INT
CheckBSSMAPMsgUplinkReqAck(BSSAP_Message* iMsg)
{
   BSSAP_DEBUG(("BSSMAP MESSAGE ::UplinkRequest Ack does not have any IE **** \n"));
   return (ITS_SUCCESS);
}

// UplinkReqConfirm
ITS_INT
CheckBSSMAPMsgUplinkReqConfirm(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::UplinkRequest Confirm **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// UplinkReleaseInd
ITS_INT
CheckBSSMAPMsgUplinkReleaseInd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Uplink Release Ind **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Uplink Rej Cmd
ITS_INT
CheckBSSMAPMsgUplinkRejCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Uplink Rej Cmd **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Uplink Release Cmd
ITS_INT
CheckBSSMAPMsgUplinkReleaseCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Uplink Release Cmd **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Uplink Seized Cmd
ITS_INT
CheckBSSMAPMsgUplinkSeizedCmd(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Uplink Seized Cmd **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);
 return (ITS_SUCCESS);
}

// CommonID
ITS_INT
CheckBSSMAPMsgCommonID(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Common ID **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_IMSI);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}
// LSA Information
ITS_INT
CheckBSSMAPMsgLSAInfo(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::LSA Information **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_LSA_INFORMATION);
    if(!ie)
        return(!ITS_SUCCESS);

    return (ITS_SUCCESS);
}

// Connection Oriented Information
ITS_INT
CheckBSSMAPMsgConnOrientInfo(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Connection Oriented Information **** \n"));
    ie = iMsg->FindIE(BSSAP_IEI_APDU);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_SEGMENTATION);

    return (ITS_SUCCESS);
}

// Perform Location Request
ITS_INT
CheckBSSMAPMsgPerformLocReq(BSSAP_Message* iMsg)
{
 const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Perform Location Request **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CELL_IDENTIFIER);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LCS_CLIENT_TYPE);
    if(!ie)
        return(!ITS_SUCCESS);
    ie = iMsg->FindIE(BSSAP_IEI_CHOSEN_CHANNEL);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LCS_QOS);

    ie = iMsg->FindIE(BSSAP_IEI_GPS_ASSISTANCE_DATA);

    ie = iMsg->FindIE(BSSAP_IEI_APDU);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_LCS_PRIORITY);

return (ITS_SUCCESS);
}

// Perform Location Response
ITS_INT
CheckBSSMAPMsgPerformLocRsp(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Perform Location Response **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_LOCATION_ESTIMATE);

    ie = iMsg->FindIE(BSSAP_IEI_DECIPHERING_KEYS);

    ie = iMsg->FindIE(BSSAP_IEI_LCS_CAUSE);

    ie = iMsg->FindIE(BSSAP_IEI_POSITIONING_DATA);

    return (ITS_SUCCESS);
}

// Perform Location Abort
ITS_INT
CheckBSSMAPMsgPerformLocAbort(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Perform Location Abort **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_LCS_CAUSE);
    if(!ie)
        return(!ITS_SUCCESS);
    return (ITS_SUCCESS);
}

// Connectionless Information
ITS_INT
CheckBSSMAPMsgConnlessInfo(BSSAP_Message* iMsg)
{
    const BSSAP_Element* ie;

    BSSAP_DEBUG(("BSSMAP MESSAGE ::Connectionless Information **** \n"));

    ie = iMsg->FindIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_APDU);
    if(!ie)
        return(!ITS_SUCCESS);

    ie = iMsg->FindIE(BSSAP_IEI_SEGMENTATION);

    ie = iMsg->FindIE(BSSAP_IEI_RETURN_ERROR_REQUEST);
    ie = iMsg->FindIE(BSSAP_IEI_RETURN_ERROR_CAUSE);

    return (ITS_SUCCESS);
}

ITS_INT  CheckParameters(ITS_OCTET msgDisc,BSSAP_Message* iMsg)
{
    ITS_ASSERT(iMsg != NULL);
    ITS_OCTET msgType = iMsg->GetMsgType();

    if (msgDisc == BSSAP_MD_BSSMAP)
    {
        switch (msgType)
        {
            case BSSAP_MSG_ASSIGN_COMPLETE:
                return CheckBSSMAPMsgAssignComplete(iMsg);

            case BSSAP_MSG_ASSIGN_FAILURE:
                return CheckBSSMAPMsgAssignFailure(iMsg);

            case BSSAP_MSG_ASSIGN_REQUEST:
                return CheckBSSMAPMsgAssignReq(iMsg);

            case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
                return CheckBSSMAPMsgHandoverCandidateEnq(iMsg);

            case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
                return CheckBSSMAPMsgHandoverCandidateRsp(iMsg);

            case BSSAP_MSG_HANDOVER_COMMAND:
                return CheckBSSMAPMsgHandoverCmd(iMsg);

            case BSSAP_MSG_HANDOVER_COMPLETE:
                return CheckBSSMAPMsgHandoverComplete(iMsg);

            case BSSAP_MSG_HANDOVER_DETECT:
                return CheckBSSMAPMsgHandoverDetect(iMsg);
           case BSSAP_MSG_HANDOVER_FAILURE:
                return CheckBSSMAPMsgHandoverFailure(iMsg);

            case BSSAP_MSG_HANDOVER_PERFORMED:
                return CheckBSSMAPMsgHandoverPerformed(iMsg);
            case BSSAP_MSG_HANDOVER_REQUEST:
                return CheckBSSMAPMsgHandoverReq(iMsg);

            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
                return CheckBSSMAPMsgHandoverReqAck(iMsg);

            case BSSAP_MSG_HANDOVER_REQUIRED:
                return CheckBSSMAPMsgHandoverRequired(iMsg);

            case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
                return CheckBSSMAPMsgHandoverRequiredRej(iMsg);

            case BSSAP_MSG_HANDOVER_SUCCEEDED:
                return CheckBSSMAPMsgHandoverSucceeded(iMsg);

            case BSSAP_MSG_CLEAR_COMMAND:
                return CheckBSSMAPMsgClrCmd(iMsg);

            case BSSAP_MSG_CLEAR_COMPLETE:
                return CheckBSSMAPMsgClrComplete(iMsg);

            case BSSAP_MSG_CLEAR_REQUEST:
                return CheckBSSMAPMsgClrReq(iMsg);

            case BSSAP_MSG_SAPI_N_REJECT:
                return CheckBSSMAPMsgSAPInRej(iMsg);

            case BSSAP_MSG_CONFUSION:
                return CheckBSSMAPMsgConfusion(iMsg);

            case BSSAP_MSG_SUSPEND:
                return CheckBSSMAPMsgSuspend(iMsg);

	          case BSSAP_MSG_RESUME:
                return CheckBSSMAPMsgResume(iMsg);

	          case BSSAP_MSG_RESET:
                return CheckBSSMAPMsgReset(iMsg);

            case BSSAP_MSG_RESET_ACK:
                return CheckBSSMAPMsgResetAck(iMsg);

            case BSSAP_MSG_RESET_CIRCUIT:
                return CheckBSSMAPMsgResetCircuit(iMsg);

            case BSSAP_MSG_RESET_CIRCUIT_ACK:
                return CheckBSSMAPMsgResetCircuitAck(iMsg);

            case BSSAP_MSG_OVERLOAD:
                return CheckBSSMAPMsgOverload(iMsg);

            case BSSAP_MSG_MSC_INVOKE_TRACE:
                return CheckBSSMAPMsgMSCInvokeTrace(iMsg);

            case BSSAP_MSG_BSS_INVOKE_TRACE:
                return CheckBSSMAPMsgBSSInvokeTrace(iMsg);

            case BSSAP_MSG_BLOCK:
                return CheckBSSMAPMsgBlock(iMsg);

            case BSSAP_MSG_BLOCK_ACK:
                return CheckBSSMAPMsgBlockAck(iMsg);

            case BSSAP_MSG_UNBLOCK:
                return CheckBSSMAPMsgUnblock(iMsg);

            case BSSAP_MSG_UNBLOCK_ACK:
                return CheckBSSMAPMsgUnblockAck(iMsg);

  	        case BSSAP_MSG_CKT_GROUP_BLOCK:
                  return CheckBSSMAPMsgCktGroupBlock(iMsg);

            case BSSAP_MSG_CKT_GRP_BLK_ACK:
                return CheckBSSMAPMsgCktGroupBlockAck(iMsg);

            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                return CheckBSSMAPMsgCktGroupUnblock(iMsg);

            case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                return CheckBSSMAPMsgCktGroupUnblockAck(iMsg);

            case BSSAP_MSG_UNEQUIPPED_CKT:
                return CheckBSSMAPMsgUnequippedCkt(iMsg);

            case BSSAP_MSG_CHANGE_CKT:
                return CheckBSSMAPMsgChangeCkt(iMsg);

            case BSSAP_MSG_CHANGE_CKT_ACK:
                return CheckBSSMAPMsgChangeCktAck(iMsg);

            case BSSAP_MSG_RESOURCE_REQUEST:
                return CheckBSSMAPMsgResourceReq(iMsg);

            case BSSAP_MSG_RESOURCE_INDICATION:
                return CheckBSSMAPMsgResourceInd(iMsg);

            case BSSAP_MSG_PAGING:
                 return CheckBSSMAPMsgPaging(iMsg);

            case BSSAP_MSG_PAGING_RESPONSE:
                 return CheckBSSMAPMsgPagingResponse(iMsg);

            case BSSAP_MSG_CIPHER_MODE_CMD:
                 return CheckBSSMAPMsgCipherModeCmd(iMsg);

            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
                 return CheckBSSMAPMsgCipherModeComplete(iMsg);

            case BSSAP_MSG_CIPHER_MODE_REJECT:
                return CheckBSSMAPMsgCipherModeRej(iMsg);

       	    case BSSAP_MSG_CLASSMARK_UPDATE:
                 return CheckBSSMAPMsgClassmarkUpdate(iMsg);

            case BSSAP_MSG_CLASSMARK_REQUEST:
                return CheckBSSMAPMsgClassmarkReq(iMsg);

            case BSSAP_MSG_COMPLETE_LAYER3_INFO:
                 return CheckBSSMAPMsgCompleteLayer3Info(iMsg);

            case BSSAP_MSG_LOAD_INDICATION:
                 return CheckBSSMAPMsgLoadInd(iMsg);

            case BSSAP_MSG_QUEUING_INDICATION:
                 return CheckBSSMAPMsgQueuingInd(iMsg);

            case BSSAP_MSG_VGCS_VBS_SETUP:
		             return CheckBSSMAPMsgVGCSVBSSetup(iMsg);

            case BSSAP_MSG_VGCS_VBS_SETUP_ACK:
                 return CheckBSSMAPMsgVGCSVBSSetupAck(iMsg);

            case BSSAP_MSG_VGCS_VBS_SETUP_REFUSE:
                 return CheckBSSMAPMsgVGCSVBSSetupRefuse(iMsg);

            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST:
                return CheckBSSMAPMsgVGCSVBSAssignReq(iMsg);

            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT:
                 return CheckBSSMAPMsgVGCSVBSAssignRsult(iMsg);

            case BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE:
                return CheckBSSMAPMsgVGCSVBSAssignFailure(iMsg);

            case BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION:
                return CheckBSSMAPMsgVGCSVBSQueuingInd(iMsg);

            case BSSAP_MSG_UPLINK_REQUEST:
                return CheckBSSMAPMsgUplinkReq(iMsg);
#if 0
            case BSSAP_MSG_UPLINK_REQUEST_ACK:
                return CheckBSSMAPMsgUplinkReqAck(iMsg);
#endif
            case BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION:
                 return CheckBSSMAPMsgUplinkReqConfirm(iMsg);

            case BSSAP_MSG_UPLINK_RELEASE_INDICATION:
                 return CheckBSSMAPMsgUplinkReleaseInd(iMsg);

            case BSSAP_MSG_UPLINK_REJECT_COMMAND:
             		return CheckBSSMAPMsgUplinkRejCmd(iMsg);

            case BSSAP_MSG_UPLINK_RELEASE_COMMAND:
                return CheckBSSMAPMsgUplinkReleaseCmd(iMsg);

            case BSSAP_MSG_UPLINK_SEIZED_COMMAND:
                return CheckBSSMAPMsgUplinkSeizedCmd(iMsg);

            case BSSAP_MSG_PERFORM_LOCACTION_REQUEST:
                 return CheckBSSMAPMsgPerformLocReq(iMsg);

            case BSSAP_MSG_PERFORM_LOCACTION_RESPONSE:
                 return CheckBSSMAPMsgPerformLocRsp(iMsg);

            case BSSAP_MSG_PERFORM_LOCACTION_ABORT:
                 return CheckBSSMAPMsgPerformLocAbort(iMsg);

            case BSSAP_MSG_LSA_INFORMATION:
                 return CheckBSSMAPMsgLSAInfo(iMsg);

            case BSSAP_MSG_COMMON_ID:
                 return CheckBSSMAPMsgCommonID(iMsg);

            case BSSAP_MSG_CONNECTIONLESS_INFORMATION:
                 return CheckBSSMAPMsgConnlessInfo(iMsg);

            case BSSAP_MSG_LCLS_CONNECT_CONTROL:
                 return ITS_SUCCESS;
		 
            case BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK:
                 return ITS_SUCCESS;

            case BSSAP_MSG_LCLS_NOTIFICATION:
                 return ITS_SUCCESS;

            default:
                BSSAP_ERROR(("Unknown message type!!\n"));
break;
        }
    }

    return ITS_SUCCESS;
}
   /* Enhanced by Amaresh for Decoding & Encoding Checking for mandatory parameters */
