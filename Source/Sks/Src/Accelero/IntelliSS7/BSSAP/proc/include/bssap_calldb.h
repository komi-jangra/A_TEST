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
 *  ID: $Id: bssap_calldb.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.4  2006/09/14 16:01:39  sjaddu
 * LOG: Fix for SLR and DLR values with morethan 3-octets.
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:44  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_CALLDB_H_
#define  _BSSAP_CALLDB_H_

#include <bssap_call.h>
#include <its_hash.h>
#include <its_singleton.h>

#define BS_CALL_INFO  1

/*implementation:internal
*
* PURPOSE:
*       Maintains CALL CTXT table in DSM. it provides Add, Fetch, Remove
*       function to manipulate/remove call object properties
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
*                        ID :: D0180
*/
class BSSAP_CallDB :
     public its::ITS_SingletonMultithreaded<BSSAP_CallDB>
    
{
public:
    
    BSSAP_CallDB() :
               its:: ITS_SingletonMultithreaded<BSSAP_CallDB>()
    {
        _BS_Call_info = HASH_CreateTable();
    }

    ~BSSAP_CallDB();
    
    static ITS_INT Initialize();

    ITS_INT Add(BSSAP_Call* call);
    BSSAP_Call* Fetch(ITS_CTXT callref);
    ITS_INT Remove(ITS_CTXT callref);
/*Modification Start by Amaresh as on dated 26-08-14 */
    ITS_INT AddCallLocal(BSSAP_Call* call);
    ITS_INT RemoveCallLocal(ITS_CTXT callref);
/*Modification Stop by Amaresh as on dated 26-08-14 */

private:

    HASH_Table _BS_Call_info;   

};

#endif
