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
 *  ID: $Id: bssap_sccphandler.h,v 1.3 2008/04/29 04:32:54 bsccs2 Exp $
 *
 * LOG: $Log: bssap_sccphandler.h,v $
 * LOG: Revision 1.3  2008/04/29 04:32:54  bsccs2
 * LOG: Fix for Mantis 2811
 * LOG:
 * LOG: Revision 1.2  2008/02/07 10:17:52  amaresh.prasad
 * LOG: Updated for APPId
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.3  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/26 06:56:36  adutta
 * LOG: Introducing function to send udt to network
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_SCCPHNDL_H_
#define  _BSSAP_SCCPHNDL_H_

#include <bssap.h>
#include <bssap_call.h>

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0800, ID :: D0810
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
		 ITS_INT SendCC(ITS_CTXT slr, ITS_CTXT dlr); //Added by Amaresh 29-04-08	
     ITS_INT SendCREF(ITS_CTXT callRef);
     ITS_INT SendRLSD(ITS_CTXT callRef,ITS_OCTET cause); //24-04-08
     ITS_INT SendAbnormalRLSD(ITS_CTXT appid,ITS_OCTET cause); //04-01-08	
     ITS_INT SendCR(BSSAP_Call* call);
     ITS_INT SendDT1(BSSAP_Call* call);
     ITS_INT SendRLC(ITS_HDR hd, BSSAP_Call* call);

     ITS_INT SendUDT(ITS_OCTET* data, ITS_UINT len, ITS_OCTET bssId);
};



#endif
