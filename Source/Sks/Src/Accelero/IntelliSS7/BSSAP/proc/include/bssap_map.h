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
 *  ID: $Id: bssap_map.h,v 1.4 2008/02/15 10:43:06 amaresh.prasad Exp $
 *
 * LOG: $Log: bssap_map.h,v $
 * LOG: Revision 1.4  2008/02/15 10:43:06  amaresh.prasad
 * LOG: Added for ClearRequest handelling
 * LOG:
 * LOG: Revision 1.3  2008/02/01 02:42:08  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2008/02/01 04:18:53  amaresh.prasad
 * LOG: Updated for New message
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
 * LOG: Revision 1.1.2.8  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.7  2005/09/29 07:45:19  adutta
 * LOG: More circuit related procedures added
 * LOG:
 * LOG: Revision 1.1.2.6  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.5  2005/09/06 10:58:26  adutta
 * LOG: Implemented MAP timers
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/28 19:04:44  adutta
 * LOG: Handover implementation
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/26 06:55:46  adutta
 * LOG: Introducing function to send udt
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 20:09:28  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_MAP_H_
#define  _BSSAP_MAP_H_

#include <BSSAP++.h>
#include <bssap_call.h>
#include <bssap_interface.h>

/*implementation:internal
*
* PURPOSE:
*       It provides API for in/out MAP messages from BSS/application.
*       also it provides helper functions for CO and UDT msgs
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
*                        ID :: D0400, ID :: D0410
*/
class BSSAP_Map
{
public:

     void Initialize();

     ITS_INT ProcessInBSSMAPMessage(BSSAP_Call* call, BSSAP_Message* mMap, ITS_OCTET *data, ITS_UINT len);
     ITS_INT ProcessOutBSSMAPMessage(BSSAP_Api* msg, ITS_OCTET *data, ITS_UINT len);
     ITS_INT ProcessOutL3Message(BSSAP_Call* call);
     ITS_INT ProcessInBSSMAPUDTMessage(BSSAP_Message* msg, ITS_OCTET nwId, ITS_OCTET *data, ITS_UINT len);

private:
     ITS_INT ProcessUDTMapProcedures(BSSAP_Message* mMap, ITS_OCTET nwId,
                                        ITS_BOOLEAN toAPP, ITS_OCTET *data, ITS_UINT len);

     ITS_INT ProcessCOMapProcedures(BSSAP_Message* mMap, BSSAP_Call* call,
                                       ITS_USHORT callrefId, ITS_BOOLEAN toAPP, ITS_OCTET *data, ITS_UINT len);

     ITS_BOOLEAN IsUDT(ITS_OCTET mType);

     ITS_INT DirectionCheck(ITS_OCTET evId, ITS_BOOLEAN up);


     // CO MAP Process
     ITS_INT ProcessClearCommand(BSSAP_Message* mMap, BSSAP_Call* call);

/* Added by Amaresh for ClearRequest 14-02-08  */
     ITS_INT ProcessClearRequest(BSSAP_Message* mMap, BSSAP_Call* call);
/* Added by Amaresh for ClearRequest 14-02-08 */

     ITS_INT ProcessAssignmentRequest(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessAssignmentFail(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessAssignmentComplete(BSSAP_Message* mMap, BSSAP_Call* call);

     ITS_INT ProcessHandoverFailure(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverCommand(BSSAP_Message* mMap, BSSAP_Call* call);
//   ITS_INT ProcessHandoverRequired(BSSAP_Message* mMap, BSSAP_Call* call); 29-04-08
		 ITS_INT ProcessHandoverRequired(BSSAP_Message* mMap, BSSAP_Call* call,ITS_OCTET *data,ITS_UINT dlen); //Added by Amaresh 29-04-08
     ITS_INT ProcessHandoverRequest(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverReqAck(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverComplete(BSSAP_Message* mMap, BSSAP_Call* call);
     /* Added by Amaresh for HANDOVER  */
     ITS_INT  ProcessHandoverDetect(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT  ProcessHandoverPerformed(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT  ProcessHandoverSucceeded(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT  ProcessHandoverRequiredReject(BSSAP_Message* mMap, BSSAP_Call* call);   
    /* Added by Amaresh for HANDOVER  */

    /* Enhance by Amaresh for Change Ckt TC_049 25-01-08*/
    ITS_INT  ProcessChangeCircuit(BSSAP_Message* mMap, BSSAP_Call* call);
    /* Enhance by Amaresh for Change Ckt TC_049 25-01-08*/
      // UDT MAP Process
     ITS_INT ProcessBlockInd(BSSAP_Message* mMap, ITS_OCTET nwId);
	   ITS_INT ProcessHandoverCandidateEnquireInd(BSSAP_Message* mMap, ITS_OCTET nwId);	//06-06-08
		 ITS_INT ProcessHandoverCandidateResponseReq(BSSAP_Message* mMap, ITS_OCTET* buff,
                                                  ITS_INT len, ITS_OCTET nwId); 	 //06-06-08
     ITS_INT ProcessBlockReq(BSSAP_Message* mMap, ITS_OCTET* buff, ITS_INT len,
                                                           ITS_OCTET nwId);

     ITS_INT ProcessUnBlockInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessUnBlockReq(BSSAP_Message* mMap, ITS_OCTET* buff, 
                                                  ITS_INT len, ITS_OCTET nwId);

     ITS_INT ProcessResetInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessResetReq(BSSAP_Message* mMap, ITS_OCTET* buff, ITS_INT len,
                                                           ITS_OCTET nwId);

     ITS_INT ProcessResetAckReq(BSSAP_Message* mMap, ITS_OCTET* buff,
                                ITS_INT len, ITS_OCTET nwId);
     ITS_INT ProcessUnequipCktReq(BSSAP_Message* mMap, ITS_OCTET* buff,
                                ITS_INT len, ITS_OCTET nwId);
                                                                                                                                              
     ITS_INT ProcessCktGroupBlkReq(BSSAP_Message* mMap, ITS_OCTET* buff,
                                   ITS_INT len, ITS_OCTET nwId);
     ITS_INT ProcessCktGroupBlkInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessCktGroupBlkAckInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessCktGroupUnblkReq(BSSAP_Message* mMap, ITS_OCTET* buff,
                                     ITS_INT len, ITS_OCTET nwId);
     ITS_INT ProcessCktGroupUnblkInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessCktGroupUnblkAckInd(BSSAP_Message* mMap, ITS_OCTET nwId);

     ITS_INT ProcessBlockAckInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessUnBlockAckInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessResetAckInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessResetCktAckInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessUnequipCktInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessOverloadInd(BSSAP_Message* mMap, ITS_OCTET nwId);
     ITS_INT ProcessResetCktInd(BSSAP_Message* mMap, ITS_OCTET nwId);

     ITS_INT ProcessResetCktReq(BSSAP_Message* mMap, ITS_OCTET* buff, 
                                                  ITS_INT len, ITS_OCTET nwId);
private:
     static its::Mutex* mlock;
};
#define _CIC_ENT  0xac
#endif
