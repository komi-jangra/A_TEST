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
 * ID: $Id: bssap_msc-error.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.3  2005/11/30 06:46:24  mkrishna
 * LOG: Pegs implementation
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:13:17  mkrishna
 * LOG: Error procedures for CGBlk/CGUBlk
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#include <bssap-msc.h>
#include <BSSAP++.h>
#include <bssap_msc-error.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-sccphandler.h>
#include <bssap_msc-pegs.h>

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0850, ID :: D0920
*/
ITS_INT
BSSAP_Error::SendConfunsion(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId, 
                               ITS_OCTET* buffer, ITS_UINT len)
{
    ITS_INT ret = 0;
    BSSAP_Confusion cnf;
    BSSAP_Cse cs;
    BSSAP_Diagn diag;
    BSSAP_SCCPHandler hndl;
    ITS_INT bufflen = 0;
    ITS_OCTET  buff[BSSAP_DATA_LEN];


    BSSAP_DEBUG(("BSSAP_Error: SendConfunsion\n"));
    
    cs.SetCause(ITS_FALSE, cause, 0);
    cnf.AddIE(BSSAP_IEI_CAUSE, &cs);

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

    // If CO 
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);

        hndl.BSSAP_ProcessAPPdata(call);

    } // UDT
    else
    {
        hndl.BSSAP_ProcessAPPdata(buff, bufflen, nwId);
    } 

    PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CONF_SEND);

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
*/
ITS_INT
BSSAP_Error::SendAssignmentFail(BSSAP_Call* call, ITS_OCTET cause)
{
    BSSAP_Cse cs;
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

    // If CO
    if (call)
    {
        call->SetBSSAPData(buff, bufflen);

        hndl.BSSAP_ProcessAPPdata(call);
    }
 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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

    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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
                                                                                                                                              
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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
                                                                                                                                              
    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
}

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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

    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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

    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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

    cs.SetCause(ITS_FALSE, C_RADIO_RESRC_UNAVAILABLE, 0); 
    blk.AddIE(BSSAP_IEI_CAUSE, &cs);

    BSSAPEncode(&blk, buff, len); 

    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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

    hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0810, ID :: D0920
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




