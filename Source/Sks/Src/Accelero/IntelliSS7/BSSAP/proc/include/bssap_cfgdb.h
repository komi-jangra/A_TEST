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
 *  ID: $Id: bssap_cfgdb.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_CFGDB_H_
#define  _BSSAP_CFGDB_H_

#include <bssap.h>
 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0210, ID :: D0220
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
/*Modification Start by Amaresh as on dated 26-08-14 */
    ITS_INT AddCfgLocal(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc, 
                       ITS_OCTET lssn, ITS_OCTET rssn);
    ITS_INT RemoveRPCEntryLocal(ITS_OCTET bscId);
    ITS_INT RemoveNWIDEntryLocal(ITS_UINT pc);
/*Modification Stop by Amaresh as on dated 26-08-14 */
};

#endif
