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
 *  ID: $Id: bssap_error.h,v 1.2 2008/02/01 04:18:06 amaresh.prasad Exp $
 *
 * LOG: $Log: bssap_error.h,v $
 * LOG: Revision 1.2  2008/02/01 04:18:06  amaresh.prasad
 * LOG: Updated for new message
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:13  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/20 09:14:33  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/29 07:43:19  adutta
 * LOG: Funtion added for un-equipped circuit
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_ERR_H_
#define  _BSSAP_ERR_H_

#include <bssap_call.h>

/*implementation:internal
*
* PURPOSE:
*       provides different error message API's
* INPUT:
*       None
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
*                        ID :: D0990
*/
class BSSAP_Error
{
public:
    
/*  ITS_INT SendConfunsion(BSSAP_Call* call, ITS_OCTET cause,
                              ITS_OCTET nwId, ITS_OCTET* buffer, ITS_UINT len);  */
    ITS_INT SendConfunsion(BSSAP_Call* call, ITS_INT cause,
                              ITS_OCTET nwId, ITS_OCTET* buffer, ITS_UINT len); /*Changed cause ITS_INT by Amaresh 25-01-08*/

    /* Added by Amaresh for send  message to MSC  for bug id 482,490 & latest enhance nwId parameter added for UDT message 25-01-08*/
    ITS_INT SendAssignmentFail(BSSAP_Call* call, ITS_OCTET cause,ITS_OCTET nwId);
    ITS_INT SendCipherModeReject(BSSAP_Call* call, ITS_OCTET cause, ITS_OCTET nwId);
    ITS_INT SendHandoverFail(BSSAP_Call* call, ITS_OCTET cause,ITS_OCTET nwId);
		ITS_INT SendHandoverFailure(BSSAP_Call* call, ITS_OCTET cause,ITS_OCTET nwId); //03-06-08
    ITS_INT SendVGCSVBSSetupRefuse(BSSAP_Call* call, ITS_OCTET cause,ITS_OCTET nwId);
    ITS_INT SendVGCSVBSAssFail(BSSAP_Call* call, ITS_OCTET cause,ITS_OCTET nwId);
/* Addition completed  by Amaresh for send  message to MSC  for bug id 482,490 & latest enhance nwId parameter added for UDT message 25-01-08*/
	
/*  ITS_INT SendAssignmentFail(BSSAP_Call* call, ITS_OCTET cause);   comented & pass nwid for UDT message */
    ITS_INT SendBlockAck(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendUnBlockAck(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendUnBlock(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendBlock(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendUnEquipCkt(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);

    ITS_INT SendCktGroupBlkAck(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendCktGroupUnblkAck(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET timeslot, ITS_OCTET nwId);

    /* Added by Amaresh for SendCktGroupBlk message to MSC  for bug id 464 25-01-08*/
    ITS_INT SendCktGroupBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                                ITS_OCTET* block_ts, ITS_OCTET counter,ITS_OCTET nwId);

    ITS_INT SendNormalCktGroupBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                                ITS_OCTET* block_ts, ITS_OCTET counter,ITS_OCTET nwId);

    ITS_INT SendNormalCktGroupUnBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                                ITS_OCTET* block_ts, ITS_OCTET counter,ITS_OCTET nwId);


/* Added by Amaresh for  SendCktGroupBlk message to MSC  for bug id 464 25-01-08*/
   
/* Added by Amaresh for SendCktGroupUnBlk message to MSC  for Enhancement TC_022,TC_023 & TC_024 25-01-08*/
    ITS_INT SendCktGroupUnBlk(BSSAP_Message* mMap, ITS_USHORT pcm,
                               ITS_OCTET* ublock_ts, ITS_OCTET counter,ITS_OCTET nwId);
/* Added by Amaresh for  SendCktGroupUnBlk message to MSC  for Enhancement TC_022,TC_023 & TC_024 25-01-08*/

/* Added by Amaresh for T8 expires send CLEAR REQUEST message to MSC */
    ITS_INT SendClearRequest(BSSAP_Call* call, ITS_OCTET cause);
/* Added by Amaresh for T8 expires send CLEAR REQUEST message to MSC */

/* Added by Amaresh for Ho-FAilure(Clear command)handelling send CLEAR COMPLETE  message to MSC 19-05-08*/
		ITS_INT SendClearComplete(BSSAP_Call* call, ITS_OCTET cause,ITS_OCTET nwId);
/* Added by Amaresh for Ho-FAilure(Clear command)handelling send CLEAR COMPLETE  message to MSC 19-05-08*/

private:
   ITS_INT BSSAPEncode(BSSAP_Message* mssg, ITS_OCTET* buff, ITS_INT& len);
};

#endif
