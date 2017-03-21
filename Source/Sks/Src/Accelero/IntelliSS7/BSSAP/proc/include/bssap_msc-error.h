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
 * ID: $Id: bssap_msc-error.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.2  2005/11/08 07:24:52  mkrishna
 * LOG: Error procedures for CktGrpBlk/CktGrpUnblk
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_ERR_H_
#define  _BSSAP_ERR_H_

#include <bssap_msc-call.h>

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01 
*                        ID :: D0810
*/
class BSSAP_Error
{
public:
    
    ITS_INT SendConfunsion(BSSAP_Call* call, ITS_OCTET cause,
                              ITS_OCTET nwId, ITS_OCTET* buffer, ITS_UINT len);

    ITS_INT SendAssignmentFail(BSSAP_Call* call, ITS_OCTET cause);
    ITS_INT SendBlockAck(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendUnBlockAck(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendUnBlock(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendBlock(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendUnEquipCkt(ITS_USHORT pcm, ITS_OCTET timeslot, ITS_OCTET nwId);

    ITS_INT SendCktGroupBlkAck(BSSAP_Message* mMap, ITS_USHORT pcm, 
                               ITS_OCTET timeslot, ITS_OCTET nwId);
    ITS_INT SendCktGroupUnblkAck(BSSAP_Message* mMap, ITS_USHORT pcm, 
                               ITS_OCTET timeslot, ITS_OCTET nwId);

private:
   ITS_INT BSSAPEncode(BSSAP_Message* mssg, ITS_OCTET* buff, ITS_INT& len);
};

#endif
