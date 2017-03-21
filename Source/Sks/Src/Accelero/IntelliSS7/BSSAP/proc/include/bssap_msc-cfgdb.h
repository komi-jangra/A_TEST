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
 * ID: $Id: bssap_msc-cfgdb.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 *
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_CFGDB_H_
#define  _BSSAP_CFGDB_H_

#include <bssap-msc.h>
 
typedef struct
{
    ITS_OCTET Id; 
    ITS_UINT  lpc;
    ITS_UINT  rpc;
    ITS_OCTET lssn ;
    ITS_OCTET rssn ;
}
CFGData;

/*implementation:internal
*
* PURPOSE:
*       Maintains configuration data in RPC or NWID LIST table in DSM.
*       it provides functions to update/remove data by bscId/pc 
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
*                        ID :: D0260, ID :: D0270
*/
class BSSAP_CfgDB
{
public:
    
    ITS_INT AddCfg(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc, 
                       ITS_OCTET lssn, ITS_OCTET rssn);
    ITS_INT RemoveRPCEntry(ITS_OCTET bscId);
    ITS_INT RemoveNWIDEntry(ITS_UINT pc);
    CFGData* FetchRPCEntry(ITS_OCTET bscId);
    CFGData* FetchNWIDEntry(ITS_UINT pc);
};

#endif
