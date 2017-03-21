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
 * ID: $Id: bssap_msc-discriminator.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.9  2006/05/05 05:21:25  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.8  2005/12/21 19:56:54  adutta
 * LOG: BSSAP_Api object created in Handover
 * LOG:
 * LOG: Revision 1.1.2.7  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.6  2005/12/01 10:48:12  mkrishna
 * LOG: Cause value changed to protocol error
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/30 06:44:52  mkrishna
 * LOG: pegs implementation and cause value modified in confusion msg
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/18 06:34:26  mkrishna
 * LOG: Changed interface name
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/08 07:11:16  mkrishna
 * LOG: Changes for Location Update procedure
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/14 10:12:44  adutta
 * LOG: function returns validated
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#include <bssap-msc.h>
#include <bssap_msc-pegs.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-discriminator.h>
#include <bssap_msc-error.h>
#include <bssap_msc-sccphandler.h>


ITS_INT
BSSAP_Discriminator::ProcessOutDTAPMessage(BSSAP_Api* msg)
{
    BSSAP_Call* call = NULL;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    ITS_INT len = 0;
    ITS_INT ret = 0;
    BSSAP_Interface bssIf;
    BSSAP_Message* mDtap = NULL;

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessOutDTAPMessage\n"));

    mDtap = msg->GetBSSAPdata();

    if (BSSAP_Message::Encode(buff, len, mDtap) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutDTAPMessage: DTAP Encode fail\n"));

        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EENCODE);

        delete mDtap;

        return (ITS_SUCCESS);
    }

    call = BSSAP_CallDB::GetShared().Fetch(msg->GetCallRef());
    if (!call)
    {
        BSSAP_ERROR(("ProcessOutDTAPMessage: Call obj. not found \n"));

        return (ITS_ENOTFOUND);
    }

    call->SetBSSAPData(buff, len);

    ret = hndl.SendDT1(call);

    if (mDtap)
    {
        delete mDtap;
    }

    return (ret);
}


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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0350, ID :: D0360,
*                        ID :: D0370, ID :: D0920
*/
ITS_INT
BSSAP_Discriminator::ProcessInBSSAPMessage(ITS_OCTET* data,
                                        ITS_UINT len,
                                        BSSAP_Call* call,
                                        ITS_OCTET nwId)
{
    ITS_OCTET mType = 0;
    ITS_INT ret = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_Message* dec = NULL;
    BSSAP_Dtap dtap;
    BSSAP_Map bssmap;
    BSSAP_Interface bssIf;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;

    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessInBSSAPMessage\n"));

    memset(buff, 0, BSSAP_DATA_LEN);
    memcpy(buff, data, len);

    if (BSSAP_Message::Decode(data, len, &dec) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP payload "
                                                    "decode failed\n"));
                                                                                                                                              
        bssIf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EDECODE);
                                                                                                                                              
        err.SendConfunsion(call, C_INVALID_MSG_CONTENT, nwId, data, len);

        return (!ITS_SUCCESS);
    }

    if (dec->GetMDisc() == BSSAP_MD_DTAP)
    {
        BSSAP_DEBUG(("BSSAP_Discriminator: DTAP payload\n"));

        PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DTAP_RECV);

        if (!call)
        {
            BSSAP_ERROR(("ProcessInBSSAPMessage: DTAP suspected in UDT\n"));

            err.SendConfunsion(call, C_PROTOCOL_ERROR, nwId, NULL, 0);
        
            return (ITS_SUCCESS);
        }

        call->SetBSSAPData(buff, len);
        call->SetBSSAPdata(dec);
 
        // Directly give this load to application 
        // ret = dtap.ProcessInDTAPMessage(call);
        //
        call->SetMssgType(dec->GetMsgType());
        bssIf.DispatchMsgToApp(call);
    }
    else if (dec->GetMDisc() == BSSAP_MD_BSSMAP)
    {
        PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_RECV);

        ie = dec->FindIE(BSSAP_IEI_LAYER3_INFORMATION);
        if (ie)
        {
            ((BSSAP_L3Info*)ie)->GetL3Info(buff, (ITS_INT)len);

            mType = buff[L3MSG_TYPE_POS];

            if (mType == BSSAP_MSG_CM_SERVICE_REQUEST)
            {
                BSSAP_DEBUG(("ProcessInBSSAPMessage: CM_SERVICE_REQUEST\n"));

                PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CMSERV_RECV);

                call->SetCallType(MO_CALL);
            }
            else if (mType == BSSAP_MSG_PAGING_RESPONSE)
            {
                BSSAP_DEBUG(("ProcessInBSSAPMessage: PAGING_RESPONSE\n"));

                PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_PAGRSP_RECV);

                call->SetCallType(MT_CALL);
            }
            else if (mType == BSSAP_MSG_LOCATION_UPDATING_REQUEST)
            {
                BSSAP_DEBUG(("ProcessInBSSAPMessage: "
                                 "LOCATION_UPDATING_REQUEST\n"));
                                                                                                                                              
                call->SetCallType(LU_CALL);
            }
            else
            {
                if (dec->GetMsgType() == BSSAP_MSG_HANDOVER_REQUEST_ACK)
                {
                    call->SetBSSAPData(buff, len);
                    ret = bssmap.ProcessInBSSMAPMessage(call, dec);
                  
                    return (ret); 
                }

                BSSAP_ERROR(("ProcessInBSSAPMessage: Wrong message type %d\n", 
                                                                        mType));
                return (!ITS_SUCCESS);
            }
 
            call->SetBSSAPData(buff, len);
            call->SetBSSAPdata(dec);

            // By-pass FSM and handover to application
            //ret = dtap.ProcessLayer3BSSAPMessage(call, dec);

            call->SetMssgType(dec->GetMsgType());

            ret = BSSAP_CallDB::GetShared().Add(call);
            if (ret != ITS_SUCCESS)
            {
                BSSAP_ERROR(("ProcessOutL3Message: Fail to update CDR %d\n",
                                                           call->GetSLR()));
            }

            ret = bssIf.DispatchMsgToApp(call);

            return (ret);
        }                                                                                                                                               
        BSSAP_DEBUG(("ProcessInBSSAPMessage: BSSMAP payload\n"));

        // CO MAP
        if (call)
        {
            call->SetBSSAPData(buff, len);
            ret = bssmap.ProcessInBSSMAPMessage(call, dec);
        }
        else // UDT MAP
        {
            ret = bssmap.ProcessInBSSMAPUDTMessage(dec, nwId);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessInBSSAPMessage: Message nether MAP nor DTAP\n")); 
    }

    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessInBSSAPMessage: Failed to dispatch message\n"));
    }

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0350, ID :: D0360,
*                        ID :: D0370, ID :: D0920
*/
ITS_INT
BSSAP_Discriminator::ProcessOutBSSAPMessage(ITS_Event& ev)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Dtap dtap;
    BSSAP_Map bssmap;
    BSSAPData data;
    ITS_EVENT evt;

    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessOutBSSAPMessage\n"));

    evt = ev.GetEvent();

    memcpy(&data, evt.data, sizeof(BSSAPData)); 

    BSSAP_Api* mssg = new BSSAP_Api(&data);

    if (mssg->GetMssgDisc() == BSSAP_MD_DTAP)
    {
        // Do not process DTAP messages
        //ret = dtap.ProcessOutDTAPMessage(mssg);

        ret = ProcessOutDTAPMessage(mssg);
    }
    else if (mssg->GetMssgDisc() == BSSAP_MD_BSSMAP)
    {
        ret = bssmap.ProcessOutBSSMAPMessage(mssg);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        } 
    }
    else
    {
        BSSAP_ERROR(("ProcessOutBSSAPMessage: Invalid BSSAP message\n"));

        return (!ITS_SUCCESS);
    }

    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutBSSAPMessage: Failed to dispatch message\n"));
    }

    delete mssg;
    mssg = NULL;

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Handling hanover messages from application 
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
*       deleting call object in this function only. since object is commited
*       in to DSM. no more it is required.
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0920, ID :: D0240,
*                        ID :: D0200
*/
ITS_INT
BSSAP_Discriminator::ProcessHandoverMessages(ITS_Event& ev)
{
    ITS_INT ret = 0;
    ITS_OCTET mType = 0;
    ITS_INT len = 0;
    ITS_EVENT evt;
    ITS_OCTET  buff[BSSAP_DATA_LEN];
    BSSAP_Interface bssIf;
    BSSAPData data;
    BSSAP_Map bssmap;
    BSSAP_Message* mapData = NULL;
    
    BSSAP_Call* call = new BSSAP_Call();

    BSSAP_DEBUG(("BSSAP_Discriminator: ProcessHandoverMessage\n"));

    evt = ev.GetEvent();

    memcpy(&data, evt.data, sizeof(BSSAPData));

    BSSAP_Api* mssg = new BSSAP_Api(&data);

    mapData = mssg->GetBSSAPdata();

    if (mssg->GetMssgType() == BSSAP_MSG_HANDOVER_REQUEST) 
    {
        call->SetCallType(HO_CALL);
    } 

    if (BSSAP_Message::Encode(buff, len, mapData) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessHandoverMessage: BSSMAP Encode fail\n"));

        bssIf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EENCODE);

        delete mapData;

        return (ITS_SUCCESS);
    }

    call->SetAppId(mssg->GetAppId());
    call->SetSLR(mssg->GetCallRef());
    call->SetBSSAPData(buff, len);
    call->SetCurrentEvent(mType);
    call->SetHandOver(ITS_TRUE);
    call->SetMssgType(mType);

    ret = BSSAP_CallDB::GetShared().Add(call);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("BSSAP_Discriminator: Fail to update CDR %d\n",
                                                           call->GetSLR()));
    }

    bssmap.ProcessOutBSSMAPMessage(mssg);

    delete call;
    delete mssg;

    call = NULL;
    mssg = NULL;

    return (ITS_SUCCESS);
}
