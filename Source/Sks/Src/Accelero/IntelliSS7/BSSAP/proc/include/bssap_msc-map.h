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
 * ID: $Id: bssap_msc-map.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.5  2006/05/05 05:21:56  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/18 06:42:22  mkrishna
 * LOG: Changed API
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/08 07:26:33  mkrishna
 * LOG: Procedures for ResetAck/CktGrpBlk/CktGrpUnblk
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/14 10:15:20  adutta
 * LOG: Handled handover complete
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_MAP_H_
#define  _BSSAP_MAP_H_

#include <BSSAP++.h>
#include <bssap_msc-call.h>
#include <bssap_msc-interface.h>

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0470
*/
class BSSAP_Map
{
public:

     void Initialize();

     ITS_INT ProcessInBSSMAPMessage(BSSAP_Call* call, BSSAP_Message* mMap);
     ITS_INT ProcessOutBSSMAPMessage(BSSAP_Api* msg);
     ITS_INT ProcessInBSSMAPUDTMessage(BSSAP_Message* msg, ITS_OCTET nwId);

private:
     ITS_INT ProcessUDTMapProcedures(BSSAP_Message* mMap, ITS_OCTET nwId,
                                        ITS_BOOLEAN toAPP);

     ITS_INT ProcessCOMapProcedures(BSSAP_Message* mMap, BSSAP_Call* call,
                                       ITS_CTXT callrefId, ITS_BOOLEAN toAPP);

     ITS_BOOLEAN IsUDT(ITS_OCTET mType);


     // CO MAP Process
     ITS_INT ProcessClearComplete(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessClearCommand(BSSAP_Message* mMap, BSSAP_Call* call);

     ITS_INT ProcessAssignmentRequest(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessAssignmentFail(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessAssignmentComplete(BSSAP_Message* mMap, BSSAP_Call* call);

     ITS_INT ProcessHandoverFailure(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverCommand(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverRequired(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverRequest(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverReqAck(BSSAP_Message* mMap, BSSAP_Call* call);
     ITS_INT ProcessHandoverComplete(BSSAP_Message* mMap, BSSAP_Call* call);
    

     // UDT MAP Process
     ITS_INT ProcessBlockInd(BSSAP_Message* mMap, ITS_OCTET nwId);
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

#endif
