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
 *  ID: $Id: bssap_error.cpp,v 1.2 2008/02/01 04:24:39 amaresh.prasad Exp $
 *
 * LOG: $Log: bssap_error.cpp,v $
 * LOG: Revision 1.2  2008/02/01 04:24:39  amaresh.prasad
 * LOG: Updated for Abnormal case & Bugfix
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/20 09:13:40  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2005/12/05 09:19:14  mkrishna
 * LOG: Added pegs implementation
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/29 07:38:11  adutta
 * LOG: Function to send UnEquipped circuit
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 ****************************************************************************/

#include <bssap.h>
#include <BSSAP++.h>
#include <bssap_error.h>
#include <bssap_calldb.h>
#include <bssap_sccphandler.h>
#include <bssap_pegs.h>
#include <bssap_timer.h> 
#include <bssap_cicdb.h> 
#include <bssap_cfgdb.h>
ITS_OCTET array_block[100];
int ArrayGetSearchLinearRowI( int searchS, ITS_OCTET*  arraySA,int no);


/*implementation:internal
*
* PURPOSE:
*       building and sending confusion error msg
* INPUT:
*       call object, cause value, nwId, buufer and buff length
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 cause changes ITS_OCTET to ITS_INT
*/
ITS_INT
BSSAP_Error::SendConfunsion(BSSAP_Call* call, ITS_INT cause, ITS_OCTET nwId, 
                               ITS_OCTET* buffer, ITS_UINT len)
{
    ITS_INT ret = 0;
    BSSAP_Confusion cnf;
    ITS_OCTET ercause = 0;
    BSSAP_Cse cs;
    BSSAP_Diagn diag;
    BSSAP_SCCPHandler hndl;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];


    BSSAP_DEBUG(("BSSAP_Error: SendConfunsion\n"));
    /* Enhanced by Amaresh for err cause 25-01-08 */
    if(cause == ITS_EMISSMAND) /* ITS_EMISSMAND -12 */
        ercause = C_INFO_ELEMENT_MISSING;
    else
        if(cause == ITS_EBSSAP_UNKNOWN_IE)
                ercause = c_UNKNOWN_INFO_ELEMENT;
    else
        if(cause == ITS_EBSSAP_UNKNOWN_MSG_TYPE)
                ercause = C_UNKNOWN_MSG_TYPE;
    else
        if(cause == ITS_EINVALIDARGS)
                ercause = C_ICORRECT_VALUE;
    else
        if(cause == C_PROTOCOL_ERROR)
             ercause = C_PROTOCOL_ERROR;
    else
        if(cause == ITS_EINVARGSLEN)
                ercause = C_INVALID_MSG_CONTENT;
    else
        ercause = C_INVALID_MSG_CONTENT;

    cs.SetCause(ITS_FALSE, ercause, 0);
    cnf.AddIE(BSSAP_IEI_CAUSE, &cs);
    /* Enhanced by Amaresh for err cause 25-01-08 */	
    
    /*    cs.SetCause(ITS_FALSE, cause, 0);
    cnf.AddIE(BSSAP_IEI_CAUSE, &cs); */

    // populate Diagnostics, Error pointer
    diag.SetErrPtr(DIAG_ERROR_LOCATION_NOT_DETERMINED);
    // populate Diagnostics, Bit pointer
    diag.SetBitPtr(DIAG_NO_ERROR);
    // Actual message recived
    diag.SetMsgRcvd(buffer, len);
    cnf.AddIE(BSSAP_IEI_DIAGNOSTICS, &diag);
    if (BSSAP_Message::Encode(buff, bufflen, &cnf) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendConfunsion: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO 
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        ret = hndl.BSSAP_ProcessAPPdata(call);

    } // UDT
    else
    {
        ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    } 
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CONF_SEND);
     BSSAPPEG_IncrPeg(PEG_BSSAP_CONF_SEND,nwId);
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending assignment fail error msg
* INPUT:
*       call object, cause
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 Bug Fix 482,Pegs maintain
*/
ITS_INT
BSSAP_Error::SendAssignmentFail(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId) 
{
    BSSAP_Cse cs;
    ITS_INT ret = 0;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_AssignmentFailure assFail;

    BSSAP_DEBUG(("BSSAP_Error: SendAssignmentFail\n"));    
    cs.SetCause(ITS_FALSE, cause, 0);
    assFail.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &assFail) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendAssignmentFail: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        hndl.BSSAP_ProcessAPPdata(call);
    }
	else  //UDT For fix Bug id 482 by Amaresh 25-01-08
	{
           ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
	}
	//UDT For fix Bug id 482 by Amaresh
//    PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);//peg incement by Amaresh 
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
    return (ITS_SUCCESS);
}
/*implementation:internal
*
* PURPOSE:
*       building and sending Cipher Mode Reject error msg
* INPUT:
*       call object, cause
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
* Amaresh Prasad   04-12-2007  VNL-BSC-BSSAP-CS2 CM-REJ Implementation,BugFix 490,Pegs maintain
*/

ITS_INT
BSSAP_Error::SendCipherModeReject(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId)
{
    BSSAP_Cse cs;
    ITS_INT ret = 0;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_CipherModeReject ciphermReject;

    BSSAP_DEBUG(("BSSAP_Error: Send Cipher Mode Reject\n"));
    cs.SetCause(ITS_FALSE, cause, 0);
    ciphermReject.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &ciphermReject) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendCipherModeReject: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        hndl.BSSAP_ProcessAPPdata(call);
    }
 else  //UDT
    {
        ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    }
    //PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending SendHandoverFail error msg
* INPUT:
*       call object, cause
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
* Amaresh Prasad   05-12-2007 VNL-BSC-BSSAP-CS2 HO-FAI Implementation 
*/

ITS_INT
BSSAP_Error::SendHandoverFail(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId)
{
    BSSAP_Cse cs;
    ITS_INT ret = 0;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_HandoverFailure handFail;

	  BSSAP_DEBUG(("BSSAP_Error: Send HandoverFaill \n"));
    cs.SetCause(ITS_FALSE, cause, 0);
    handFail.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &handFail) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendHandoverFail: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if(call)
    {	 
    if (call->IsHandOver())
    {
			if (call->IsHandOverNewBss())
				{
           call->SetBSSAPData(buff, bufflen);
           /* Added by Amaresh for Handover failure flag set as on dated 16-05-08 */
   		     call->SetAppId(0);
	    	 	 call->SetHandOverFailure(1); /* Set Hofailure flag */
           ret = hndl.BSSAP_ProcessAPPdata(call);
           if (ret != ITS_SUCCESS)
    			 {
       		     BSSAP_ERROR(("Fail to send HoFailure message\n"));
       		 }
					else
					{
		   		    ret = BSSAP_CallDB::GetShared().Add(call);
					}
				}
		}
    }
    /* Added by Amaresh for Handover failure flag set as on dated 16-05-08 */
    else
  //UDT
    {
        ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    }
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_HOFAIL_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
    BSSAPPEG_IncrPeg(PEG_BSSAP_HOFAIL_SEND,nwId);
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending SendHandoverFailure for same connection but different CIC 
* INPUT:
*       call object, cause
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
* Amaresh Prasad   03-06-2008 VNL-BSC-BSSAP-CS2 HO-FAI same SCCP-con & diff CIC
*/

ITS_INT
BSSAP_Error::SendHandoverFailure(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId)
{
    BSSAP_Cse cs;
    ITS_INT ret = 0;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_HandoverFailure handFail;

    BSSAP_DEBUG(("BSSAP_Error: Send HandoverFaillure for same SCCP-CON but different CIC \n"));
    cs.SetCause(ITS_FALSE, cause, 0);
    handFail.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &handFail) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendHandoverFail: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
// If CO
    if(call)
    {	 
    if (call->IsHandOver())
    {
      if (call->IsHandOverNewBss())
        {
           call->SetBSSAPData(buff, bufflen);
           /* Added by Amaresh for Handover failure flag set as on dated 03-06-08 */
           call->SetAppId(0);
           call->SetHandOverFailure(0); /* Set Hofailure flag */
           ret = hndl.BSSAP_ProcessAPPdata(call);
           if (ret != ITS_SUCCESS)
            {
               BSSAP_ERROR(("Fail to send HoFailure message\n"));
            }
          else
            {
					    BSSAP_DEBUG(("BSSAP_DEBUG: Send HandoverFaillure successfully towards MSC without add call \n"));
              /* ret = BSSAP_CallDB::GetShared().Add(call); */
            }
        }
    }
    }
    /* Added by Amaresh for Handover failure flag set as on dated 03-06-08 */
    else
  //UDT
    {
        ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    }
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_HOFAIL_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
    BSSAPPEG_IncrPeg(PEG_BSSAP_HOFAIL_SEND,nwId);
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending SendVGCSVBSSetupRefuse error msg
* INPUT:
*       call object, cause
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
* Amaresh Prasad   05-12-2007 VNL-BSC-BSSAP-CS2 VBCSVBSrefuse Implementation
*/

ITS_INT
BSSAP_Error::SendVGCSVBSSetupRefuse(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId)
{
    BSSAP_Cse cs;
    ITS_INT ret = 0;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_VGCSVBSSetupRefuse vvsr;

    BSSAP_DEBUG(("BSSAP_Error: Send Cipher Mode Reject\n"));
    cs.SetCause(ITS_FALSE, cause, 0);
    vvsr.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &vvsr) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendVGCSVBSSetupRefuse: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        hndl.BSSAP_ProcessAPPdata(call);
    }
else  //UDT
    {
        ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    }
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,call->GetBssId());
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending SendVGCSVBSAssFail error msg
* INPUT:
*       call object, cause
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
* Amaresh Prasad   05-12-2007 VNL-BSC-BSSAP-CS2 VBCSVBSFail
*/

ITS_INT
BSSAP_Error::SendVGCSVBSAssFail(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId)
{
    BSSAP_Cse cs;
    ITS_INT ret = 0;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_VGCSVBSAssignmentFailure vvaf;

    BSSAP_DEBUG(("BSSAP_Error: SendVGCSVBSAssFail\n"));
    cs.SetCause(ITS_FALSE, cause, 0);
    vvaf.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &vvaf) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("SendVGCSVBSAssFil: BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        hndl.BSSAP_ProcessAPPdata(call);
    }
 else  //UDT
    {
        ret = hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    }
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
    return (ITS_SUCCESS);
}


/*implementation:internal
*
* PURPOSE:
*       building and sending Clear Request error msg when T8 expires
* INPUT:
*       call object, cause
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
* Amaresh Prasad   08-08-2007  VNL-BSC-BSSAP-CS2 Clear Request Implementation
*/

ITS_INT
BSSAP_Error::SendClearRequest(BSSAP_Call* call, ITS_OCTET cause)
{
    BSSAP_Cse cs;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_ClearRequest clearreq;

    BSSAP_DEBUG(("BSSAP_Error: SendCLEAR REQUEST from BSC-->MSC after T8 expires \n"));
    cs.SetCause(ITS_FALSE, cause, 0);
    clearreq.AddIE(BSSAP_IEI_CAUSE, &cs);
    if (BSSAP_Message::Encode(buff, bufflen, &clearreq) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("Send CLEAR REQUEST : BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        hndl.BSSAP_ProcessAPPdata(call);
    }
   // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,call->GetBssId());
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending Clear Complete msg Clear Command comes from MSC for HO case
* INPUT:
*       call object, cause
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
* Amaresh Prasad   19-05-08  VNL-BSC-BSSAP-CS2 Clear Complete Implementation
*/

ITS_INT
BSSAP_Error::SendClearComplete(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId)
{
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    BSSAP_ClearComplete clearcomp;

    BSSAP_DEBUG(("BSSAP_Error: Send CLEAR COMPLETE message from BSC-->MSC for HO case \n"));
     if (BSSAP_Message::Encode(buff, bufflen, &clearcomp) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("Send CLEAR Complete : BSSAP Encode fail\n"));
        return (ITS_SUCCESS);
    }
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,bufflen);
#endif
    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);
        hndl.BSSAP_ProcessAPPdata(call);
    }
	//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,call->GetBssId());
    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending block ack error msg
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendBlockAck(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_BlockAcknowledge blkAck;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Error: SendBlockAck\n"));
    cktId.SetPCMID(pcm);                             
    cktId.SetTimeslot(timeslot);     
    blkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    BSSAPEncode(&blkAck, buff, len); 
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
		//PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending circuit group block ack error msg
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       mMap, pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendCktGroupBlkAck(BSSAP_Message* mMap, ITS_USHORT pcm,
                                ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0, clen = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN], range = 0;
    ITS_OCTET buf[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_CktIDCodeList cicList;
    BSSAP_CircuitGroupBlockAcknowledge grpBlkAck;
    const BSSAP_Element* clIe = NULL;
    BSSAP_SCCPHandler hndl;                                                                                                                                             
    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupBlkAck\n"));                                              
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(timeslot);                                                                      
    grpBlkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);                                        
    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if (clIe)
    {
       range = ((BSSAP_CktIDCodeList*)clIe)->GetRange();
       cicList.SetRange(range);                                                                 
       ((BSSAP_CktIDCodeList*)clIe)->GetStatus(buf, clen);
       cicList.SetStatus(buf, clen);                                                                  
       grpBlkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
    }                                                                                                 
    BSSAPEncode(&grpBlkAck, buff, len);
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
//		PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending circuit group unblock ack error msg
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       mMap, pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendCktGroupUnblkAck(BSSAP_Message* mMap, ITS_USHORT pcm,
                                 ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0, clen = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN], range = 0;
    ITS_OCTET buf[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_CktIDCodeList cicList;
    BSSAP_CircuitGroupUnblockAck grpUnblkAck;
    const BSSAP_Element* clIe = NULL;
    BSSAP_SCCPHandler hndl;                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupUnblkAck\n"));                                          
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(timeslot);                                                                      
    grpUnblkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);                                      
    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if (clIe)
    {
       range = ((BSSAP_CktIDCodeList*)clIe)->GetRange();
       cicList.SetRange(range);                                                                       
       ((BSSAP_CktIDCodeList*)clIe)->GetStatus(buf, clen);
       cicList.SetStatus(buf, clen);                                                                 
       grpUnblkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
    }                                                                                                
    BSSAPEncode(&grpUnblkAck, buff, len);
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
                                                                                                 
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
//		PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
    BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}
 
/*implementation:internal
*
* PURPOSE:
*       building and sending CktGroupBlk  msg for locally blocked cic
* INPUT:
*       call object, cause
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
* Amaresh Prasad   01-12-2007  VNL-BSC-BSSAP-CS2 CktGrpBlk Implementation
*/
ITS_INT
BSSAP_Error::SendNormalCktGroupBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET* timeslot, ITS_OCTET counter, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = 0, clen = 0, ele = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN], range = 0;
    ITS_OCTET range_set = 0;
    ITS_OCTET buf[BSSAP_DATA_LEN];
    ITS_UINT key = 0;
    ITS_OCTET set_counter = 0;
    BSSAP_CktIDCode cktId;
//    CICData* crec = NULL;
    CICData* crec_timer = NULL;
    BSSAP_CicDB cicdb;
    BSSAP_CktIDCodeList cicList;
    BSSAP_Cse  cs;
    BSSAP_CircuitGroupBlock grpBlk;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* cicIe_timer = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_SCCPHandler hndl;
    ITS_OCTET  ts,StartTs,EndTs,type = 0;
    BSSAP_DEBUG(("BSSAP_Error: Again SendCktGroupBlk\n"));

    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = StartTs = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
   //     crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
   }

    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if (clIe)
    {
      range_set = ((BSSAP_CktIDCodeList*)clIe)->GetRange();
      range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1;
    }
    EndTs = StartTs + range;
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(ts);
    grpBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate Cause, add it to the message
    cs.SetCause(0, C_OAMP_INTERVENTION,0);
    /*  cs.SetNationalCause(C_CLASS_RESRC_UNAVAILABLE, octet);*/ //octet =0x11 if 1
    grpBlk.AddIE(BSSAP_IEI_CAUSE, &cs);
    cicList.SetRange(range_set);

    for (int i = StartTs; i<EndTs; i++)
    {
       if (timeslot[set_counter] == 1 )
        {
            cicList.SetStatusBitPos(1, i, StartTs, range);
            set_counter++;
            BSSAP_DEBUG(("Type to be set :   %d setcounter value: %d " "\n",timeslot[i],set_counter));

        }
        else
        {
            cicList.SetStatusBitPos(0, i, StartTs, range);
            set_counter++;
            BSSAP_DEBUG(("Type to be set : %d  setcounter value: %d " "\n",timeslot[i],set_counter));

        }
    }
    grpBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

    BSSAPEncode(&grpBlk, buff, len);
    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupBlk data towards MSC & start timer T20\n"));

#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif

   cicIe_timer = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
   if (cicIe_timer)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        crec_timer = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
   }
        if (crec_timer)
        {
            if (crec_timer->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(crec_timer->timerType);

                t1.CancelUDTTimer(crec_timer->timerId);
                crec_timer->timerId = 0;
            }
             BSSAP_Timer t(BSSAP_T_20);

            ret = t.StartUDTTimer(key, 0, BSSAP_MSG_CKT_GROUP_BLOCK, buff,
                                                           len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
                cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GROUP_BLOCK);
                return (ret);
            }

           hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
		//	   	 PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);

           crec_timer->timerId = ret;
           crec_timer->timerType = BSSAP_T_20;

           ret = cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GROUP_BLOCK);
           if (ret != ITS_SUCCESS)
           {
               BSSAP_DEBUG(("ProcessCktGroupBlkReqInitiatedbyStack:CIC Modify failed %d\n", key));
               return (ret);
           }
       }
      else
       {
          BSSAP_DEBUG(("BSSAP_Error: NO CIC record found for CKTGroupBlk\n"));
       }
}

/*implementation:internal
*
* PURPOSE:
*       building and sending CktGroupUnBlk  msg
* INPUT:
*       call object, cause
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
* Amaresh Prasad   01-12-2007  VNL-BSC-BSSAP-CS2 CktGrpUnblock Implementation
*/
ITS_INT
BSSAP_Error::SendNormalCktGroupUnBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET* timeslot, ITS_OCTET counter, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = 0, clen = 0, ele = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN], range = 0;
    ITS_OCTET range_set = 0;
    ITS_OCTET buf[BSSAP_DATA_LEN];
    ITS_UINT key = 0;
    ITS_OCTET set_counter = 0;
    BSSAP_CktIDCode cktId;
   // CICData* crec = NULL;
    CICData* crec_timer = NULL;
    BSSAP_CicDB cicdb;
    BSSAP_CktIDCodeList cicList;
    BSSAP_Cse  cs;
    BSSAP_CircuitGroupUnblock grpUnBlk;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* cicIe_timer = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_SCCPHandler hndl;
    ITS_OCTET  ts,StartTs,EndTs,type = 0;
    BSSAP_DEBUG(("BSSAP_Error: Again SendCktGroupUnBlk\n"));

    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = StartTs = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
       // crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
   }
    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
    if (clIe)
    {
        range_set = ((BSSAP_CktIDCodeList*)clIe)->GetRange();
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1;
    }

    EndTs = StartTs + range;
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(ts);
    grpUnBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    cicList.SetRange(range_set);

    for (int i = StartTs; i<EndTs; i++)
    {
       if (timeslot[set_counter] == 1 )
        {
            cicList.SetStatusBitPos(1, i, StartTs, range);
            set_counter++;
            BSSAP_DEBUG(("Type to be set for NormalCGU :   %d setcounter value: %d " "\n",timeslot[i],set_counter));

        }
        else
        {
            cicList.SetStatusBitPos(0, i, StartTs, range);
            set_counter++;
            BSSAP_DEBUG(("Type to be set for NormalCGU : %d  setcounter value: %d " "\n",timeslot[i],set_counter));
        }
    }
    grpUnBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
    BSSAPEncode(&grpUnBlk, buff, len);
    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupUnBlk data towards MSC & start timer T20\n"));

#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    cicIe_timer = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe_timer)
     {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        crec_timer = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
     }
        if (crec_timer)
        {
            if (crec_timer->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(crec_timer->timerType);

                t1.CancelUDTTimer(crec_timer->timerId);
                crec_timer->timerId = 0;
            }

            BSSAP_Timer t(BSSAP_T_20);

            ret = t.StartUDTTimer(key, 0, BSSAP_MSG_CKT_GRP_UNBLOCK, buff,
                                                           len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
                cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GRP_UNBLOCK);
                return (ret);
	    }	
    				hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
		    	//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
            crec_timer->timerId = ret;
            crec_timer->timerType = BSSAP_T_20;
            ret = cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GRP_UNBLOCK);
            if (ret != ITS_SUCCESS)
            {
               BSSAP_DEBUG(("ProcessCktGroupBlkReqInitiatedbyStack:CIC Modify failed %d\n", key));
                return (ret);
            }
        }
      else
        {
        BSSAP_DEBUG(("BSSAP_Error: NO CIC record found for CKTGroupUnBlk\n"));
        }
}

/*implementation:internal
*
* PURPOSE:
*       building and sending CktGroupBlk  msg for locally blocked cic
* INPUT:
*       call object, cause
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
* Amaresh Prasad   01-12-2007  VNL-BSC-BSSAP-CS2 CGB Implementation & BugFix 465
*/

ITS_INT
BSSAP_Error::SendCktGroupBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET* timeslot, ITS_OCTET counter, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = 0, clen = 0, ele = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN], range = 0;
    ITS_OCTET range_set = 0;
    ITS_OCTET buf[BSSAP_DATA_LEN];
    ITS_UINT key = 0;
    BSSAP_CktIDCode cktId;
    //CICData* crec = NULL;
    CICData* crec_timer = NULL;
    BSSAP_CicDB cicdb;
    BSSAP_CktIDCodeList cicList;
    BSSAP_Cse  cs;
    BSSAP_CircuitGroupBlock grpBlk;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* cicIe_timer = NULL;
    BSSAP_SCCPHandler hndl;
    ITS_OCTET  ts,StartTs,EndTs,type = 0;

    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupBlk\n"));
    StartTs = timeslot[0];
    EndTs = timeslot[counter -1 ];
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
       /* ts =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot(); */
          ts = StartTs;
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

    //    crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
/*      range = ((BSSAP_CktIDCodeList*)cicIe)->GetRange(); */
        range_set = EndTs - StartTs;
 cktId.SetPCMID(pcm);
    cktId.SetTimeslot(StartTs);
    grpBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


  // populate Cause, add it to the message
       cs.SetCause(0, C_OAMP_INTERVENTION,0);
      /*  cs.SetNationalCause(C_CLASS_RESRC_UNAVAILABLE, octet);*/ //octet =0x11 if 1
       grpBlk.AddIE(BSSAP_IEI_CAUSE, &cs);

      cicList.SetRange(range_set);
//      range = cicList.GetRange() + 1;
    for (int i = StartTs; i <=EndTs; i++)
    {
type = ArrayGetSearchLinearRowI(i,timeslot,counter);
BSSAP_DEBUG(("Type to be set :  type %d i %d  " "\n", type,i));
       if (type == 1 )
        {
            cicList.SetStatusBitPos(1, i, StartTs, range_set);
            array_block[ele] = 1;
            ele = ele + 1;
        }
        else
        {
            cicList.SetStatusBitPos(0, i, StartTs, range_set);
            array_block[ele] = 0;
            ele = ele + 1;
        }
    }
grpBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
    }

    BSSAPEncode(&grpBlk, buff, len);
    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupBlk data towards MSC & start timer T20\n"));

#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif

cicIe_timer = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe_timer)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
       /* ts =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();        */
          ts =  StartTs;/* Updated for Cancel timer */
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        crec_timer = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
   }
         if (crec_timer)
        {
            if (crec_timer->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(crec_timer->timerType);

                t1.CancelUDTTimer(crec_timer->timerId);
                crec_timer->timerId = 0;
            }

            BSSAP_Timer t(BSSAP_T_20);
	 ret = t.StartUDTTimer(key, 0, BSSAP_MSG_CKT_GROUP_BLOCK, buff,
                                                           len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
               cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GROUP_BLOCK);
                return (ret);
            }
        hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
			//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
        crec_timer->timerId = ret;
        crec_timer->timerType = BSSAP_T_20;
        ret = cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GROUP_BLOCK);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_DEBUG(("ProcessCktGroupBlkReqInitiatedbyStack:CIC Modify failed %d\n", key));
            return (ret);
        }

        }
        else
        {
        BSSAP_DEBUG(("BSSAP_Error: NO CIC record found for CKTGroupBlk\n"));
        }
}/*  Amaresh for bug id 465 fix */

/*implementation:internal
*
* PURPOSE:
*       building and sending CktGroupUnBlk  msg
* INPUT:
*       call object, cause
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
* Amaresh Prasad   07-12-2007  VNL-BSC-BSSAP-CS2 CGU Implementation 
*/

ITS_INT
BSSAP_Error::SendCktGroupUnBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET* timeslot, ITS_OCTET counter, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = 0, clen = 0 ;
    ITS_OCTET buff[BSSAP_DATA_LEN], range = 0;
    ITS_OCTET range_set = 0;
    ITS_OCTET buf[BSSAP_DATA_LEN];
    ITS_UINT key = 0;
    BSSAP_CktIDCode cktId;
    //CICData* crec = NULL;
   CICData* crec_timer = NULL;
    BSSAP_CicDB cicdb;
    BSSAP_CktIDCodeList cicList;
    BSSAP_CircuitGroupUnblock grpUnBlk;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* cicIe_timer = NULL;
    BSSAP_SCCPHandler hndl;
    ITS_OCTET  ts,StartTs,EndTs,type = 0;

    BSSAP_DEBUG(("BSSAP_Error: SendCktGroupUNBLOCK\n"));
    StartTs = timeslot[0];
    EndTs = timeslot[counter -1 ];

    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
      /*ts =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot(); */
        ts = StartTs;
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        //crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
/*      range = ((BSSAP_CktIDCodeList*)cicIe)->GetRange(); */
 range_set = EndTs - StartTs;

    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(StartTs);
    grpUnBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    cicList.SetRange(range_set);
//    range = cicList.GetRange() + 1;


  for (int i = StartTs; i <=EndTs; i++)
    {
type = ArrayGetSearchLinearRowI(i,timeslot,counter);
BSSAP_DEBUG(("Type to be set :  type %d i %d  " "\n", type,i));
        if (type ==  1)
        {
            cicList.SetStatusBitPos(1, i, StartTs, range_set);
        }
        else
        {
            cicList.SetStatusBitPos(0, i, StartTs, range_set);
        }
    }
    grpUnBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
    }
		 BSSAPEncode(&grpUnBlk, buff, len);
		 BSSAP_DEBUG(("BSSAP_Error: SendCktGroupUnBlk data towards MSC & start timer T20\n"));
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
cicIe_timer = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe_timer)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        /*ts =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot(); */
         ts = StartTs;
        key  = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        crec_timer = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
   }
         if (crec_timer)
        {
            if (crec_timer->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(crec_timer->timerType);

                t1.CancelUDTTimer(crec_timer->timerId);
                crec_timer->timerId = 0;
            }
            BSSAP_Timer t(BSSAP_T_20);
            ret = t.StartUDTTimer(key, 0, BSSAP_MSG_CKT_GRP_UNBLOCK, buff,
                                                          len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
                cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GRP_UNBLOCK);
                return (ret);
            }
		hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
//		PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
                crec_timer->timerId = ret;
                crec_timer->timerType = BSSAP_T_20;
                ret = cicdb.ModifyCICRecord(key, crec_timer,BSSAP_MSG_CKT_GRP_UNBLOCK);
                if (ret != ITS_SUCCESS)
                {
          BSSAP_DEBUG(("ProcessCktGroupBlkReqInitiatedbyStack:CIC Modify failed %d\n", key));
            return (ret);
                }
        }
        else
        {
        BSSAP_DEBUG(("BSSAP_Error: NO CIC record found for CKTGroupUnBlk\n"));
        }
}/*  Amaresh Enhancement TC_022 & TC_023 */


/*implementation:internal
*
* PURPOSE:
*       building and sending unblock ack error msg
* INPUT:
*       pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendUnBlockAck(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_UnblockAcknowledge unblkAck;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Error: SendUnBlockAck\n"));
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(timeslot);
    unblkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    BSSAPEncode(&unblkAck, buff, len); 
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
//		PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);	
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending unblock error msg
* INPUT:
*       pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendUnBlock(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_Unblock unblk;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Error: SendUnBlock\n"));
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(timeslot);
    unblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    BSSAPEncode(&unblk, buff, len); 
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
//		PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending block error msg
* INPUT:
*       pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendBlock(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_Cse       cs;
    BSSAP_ConRlsReq crReq;
    BSSAP_Block blk;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Error: SendBlock\n"));

    cktId.SetPCMID(pcm);                             
    cktId.SetTimeslot(timeslot);                   
    blk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    cs.SetCause(0, C_OAMP_INTERVENTION,0); /* Change Cause to C_OAMP_INTERVENTION*/
  /*  cs.SetCause(ITS_FALSE, C_RADIO_RESRC_UNAVAILABLE, 0);  */
    blk.AddIE(BSSAP_IEI_CAUSE, &cs);
    BSSAPEncode(&blk, buff, len); 
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
	//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);	
            BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}

/*implementation:internal
*
* PURPOSE:
*       building and sending unequip circuit error msg
* INPUT:
*       pcm, timeslot, nwId
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::SendUnEquipCkt(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId)
{
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_CktIDCode cktId;
    BSSAP_UnequippedCircuit unCkt;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Error: SendUnEquipCkt\n"));
    cktId.SetPCMID(pcm);
    cktId.SetTimeslot(timeslot);
    unCkt.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    BSSAPEncode(&unCkt, buff, len);
#ifdef LOGGER_IMR
        PRINT_HEX_DUMP(INFO,buff,len);
#endif
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
	//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
     BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,nwId);
}

/*implementation:internal
*
* PURPOSE:
*       encoding the BSSAP message
* INPUT:
*      mssg
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buff, len
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
*                        ID :: D0950, ID :: D0980
*                        ID :: D0990, ID :: D1060
*/
ITS_INT
BSSAP_Error::BSSAPEncode(BSSAP_Message* mssg, 
                         ITS_OCTET* buff, 
                         ITS_INT& len)
{
    BSSAP_DEBUG(("BSSAP_Error: BSSAPEncode\n"));

    if (BSSAP_Message::Encode(buff, len, mssg) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("BSSAPEncode: BSSAP Encode fail\n"));

        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
}

/* Added by Amaresh for linear search */

int ArrayGetSearchLinearRowI( int searchS, ITS_OCTET*  arraySA,int no)
{
int i;
for (i=0; i<no; i++) {
     if (searchS == arraySA[i]) {
       return 1;
     }
   }
   return -1;
}
/* Added by Amaresh for linear search */

