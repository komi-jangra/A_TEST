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
 * ID: $Id: bssap_msc-sccphandler.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2006/05/09 06:54:04  adutta
 * LOG: Context set to large
 * LOG:
 * LOG: Revision 1.1.2.3  2006/04/25 05:33:13  adutta
 * LOG: Changed as par IMR comments
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/18 06:43:02  mkrishna
 * LOG: Added SendCREF/RLSD apis
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_SCCPHNDL_H_
#define  _BSSAP_SCCPHNDL_H_

#include <bssap-msc.h>
#include <bssap_msc-call.h>

/*implementation:internal
*
* PURPOSE:
*       None
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
*                        ID :: D0650, ID :: D0660
*/
class BSSAP_SCCPHandler
{

public:
     ITS_INT BSSAP_ProcessSCCPdata(ITS_Event& evt);

     // Process DTAP and CO MAP message
     ITS_INT BSSAP_ProcessAPPdata(BSSAP_Call* call);

     // Process MAP (CL) message
     ITS_INT BSSAP_ProcessAPPdata(ITS_OCTET* data, ITS_UINT len,
                                     ITS_OCTET bssId);

public:
     ITS_INT ProcessUserData(ITS_OCTET* data, ITS_UINT len,
                                ITS_UINT pc, ITS_INT& status, BSSAP_Call* call);
     ITS_INT SendCC(ITS_CTXT callRef);
     ITS_INT SendCC(ITS_CTXT slr, ITS_CTXT dlr);
     ITS_INT SendCREF(ITS_CTXT callRef);
     ITS_INT SendRLSD(ITS_CTXT callRef);
     ITS_INT SendCR(BSSAP_Call* call);
     ITS_INT SendDT1(BSSAP_Call* call);
     ITS_INT SendRLC(ITS_HDR hd, BSSAP_Call* call);

     ITS_INT SendUDT(ITS_OCTET* data, ITS_UINT len, ITS_OCTET bssId);
};



#endif
