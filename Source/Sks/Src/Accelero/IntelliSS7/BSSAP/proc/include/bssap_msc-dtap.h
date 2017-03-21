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
 * ID: $Id: bssap_msc-dtap.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.5  2005/11/28 05:24:54  adutta
 * LOG: T3260 timer implementation api
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/18 06:41:11  mkrishna
 * LOG: Changed API
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/17 06:20:22  mkrishna
 * LOG: Function definition for AuthReq and IdentReq
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:23:54  mkrishna
 * LOG: Loaction Update procedure
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             
#ifndef  _BSSAP_DTAP_H_
#define  _BSSAP_DTAP_H_

#include <BSSAP++.h>
#include <bssap_msc-call.h>
#include <bssap_msc-interface.h>


/*implementation:internal
*
* PURPOSE:
*       It provides API for in/out DTAP messages from BSS/application.
*       also it provides helper functions and sanity check for MO 
*       and MT calls 
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
*                        ID :: D0420
*/
class BSSAP_Dtap
{
public:
     void Initialize();
     ITS_INT ProcessInDTAPMessage(BSSAP_Call* call);
     ITS_INT ProcessOutDTAPMessage(BSSAP_Api* msg);
     ITS_INT ProcessOutL3Message(BSSAP_Call* call);
     ITS_INT ProcessLayer3BSSAPMessage(BSSAP_Call* call, BSSAP_Message* mMap);

private:
     
     ITS_INT HandleInCCMessage(BSSAP_Call* call);
     ITS_INT HandleOutCCMessage(BSSAP_Call* call);
     ITS_INT MOSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up);
     ITS_INT MTSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up);
     ITS_INT DirectionCheck(ITS_OCTET evId, ITS_BOOLEAN up);
     ITS_INT ProcessDTAPProcedures(BSSAP_Call* call, ITS_OCTET mType,
                                                        ITS_BOOLEAN toApp);

     ITS_INT ProcessAuthenReq(BSSAP_Call* call);
     ITS_INT ProcessAuthenRespInd(BSSAP_Call* call);

     ITS_INT ProcessIdentityReq(BSSAP_Call* call);
     ITS_INT ProcessIdentityRespInd(BSSAP_Call* call);

     ITS_INT ProcessTmsiReallocCmdReq(BSSAP_Call* call);
     ITS_INT ProcessTmsiReallocCmpInd(BSSAP_Call* call); 
private:
     static its::Mutex* mutex;
};


#endif
