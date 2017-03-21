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
 * ID: $Id: bssap_msc-cfgdb.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 *
 * LOG:
 ****************************************************************************/

#include <bssap_msc-cfgdb.h>

#define DSM_LockTable        DSM_LockTableLocal
#define DSM_UnlockTable      DSM_UnlockTableLocal
#define DSM_AllocNoLock      DSM_AllocNoLockLocal
#define DSM_FindNoLock       DSM_FindNoLockLocal
#define DSM_FreeNoLock       DSM_FreeNoLockLocal
#define DSM_CommitNoLock     DSM_CommitNoLockLocal
#define DSM_Alloc            DSM_AllocLocal
#define DSM_Find             DSM_FindLocal
#define DSM_Free             DSM_FreeLocal
#define DSM_Commit           DSM_CommitLocal

/*implementation:internal
*
* PURPOSE:
*       Adding configuration data in to RPC LIST or NWID LIST table 
* INPUT:
*      bscId, lpc, rpc, lssn, rssn 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if added in to table 
*       Error, if failed to add 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0250, ID :: D0260,
*                        ID :: D0270, ID :: D0920
*/
ITS_INT
BSSAP_CfgDB::AddCfg(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc, 
                    ITS_OCTET lssn, ITS_OCTET rssn)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* fptr;
    CFGData* fptr1;

    BSSAP_DEBUG(("BSSAP_CfgDB: AddCfg\n"));

    // BSS/MSC Id  -> Point code mapping
    fptr = (CFGData *)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_RPC_LIST,
                               (ITS_OCTET *)&bscId,
                               sizeof(ITS_OCTET), 
                               &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr = (CFGData*) DSM_Alloc(DSM_SccpFtGroupId,
                                    DSM_TABLE_BSSAP_RPC_LIST,
                                    (ITS_OCTET *)&bscId,
                                    sizeof(ITS_OCTET),
                                    sizeof(CFGData),
                                    &error);
        fptr->lpc = lpc;
        fptr->rpc = rpc;
        fptr->lssn = lssn;
        fptr->rssn = rssn;
        fptr->Id = bscId;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET), 
                           fptr);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("AddCfg: Couldn't add config data BssId %d\n", bscId));

            return (error);
        }
        else
        {
            BSSAP_DEBUG(("AddCfg: Added config data BssId %d\n", bscId));
        }
    }
    else
    {
        BSSAP_WARNING(("AddCfg: Config data alread exists BssId %d\n", bscId));

        return (error);
    }

    //Point code -> BSS/MSC ID mapping
    fptr1 = (CFGData *)DSM_Find(DSM_SccpFtGroupId,
                                DSM_TABLE_BSSAP_NWID_LIST,
                                (ITS_OCTET *)&rpc,
                                sizeof(ITS_UINT),
                                &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr1 = (CFGData*) DSM_Alloc(DSM_SccpFtGroupId,
                                     DSM_TABLE_BSSAP_NWID_LIST,
                                     (ITS_OCTET *)&rpc,
                                     sizeof(ITS_UINT),
                                     sizeof(CFGData),
                                     &error);
        fptr1->Id = bscId;
        fptr1->lpc = lpc;
        fptr1->rpc = rpc;
        fptr1->lssn = lssn;
        fptr1->rssn = rssn;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&rpc,
                           sizeof(ITS_UINT),
                           fptr1);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("AddCfg: Couldn't add config data rpc %d\n", rpc));

            return (error);
        }
        else
        {
            BSSAP_DEBUG(("AddCfg: Added config data rpc %d\n", rpc));
        }
    }
    else
    {
        BSSAP_WARNING(("AddCfg: Config data alread exists rpc %d\n", rpc));

        return (error);
    }

    return (error);
}

/*implementation:internal
*
* PURPOSE:
*       Fetching config data from RPC LIST table 
* INPUT:
*       bscId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       config data 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0250, ID :: D0260,
*                        ID :: D0270, ID :: D0920
*/
CFGData*
BSSAP_CfgDB::FetchRPCEntry(ITS_OCTET bscId)
{
    CFGData* cdata = NULL;
    ITS_INT error = 0;

    BSSAP_DEBUG(("BSSAP_CfgDB: FetchRPCEntry\n"));

    cdata = (CFGData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_RPC_LIST,
                               (ITS_OCTET *)&bscId,
                               sizeof(ITS_OCTET),
                               &error);
    if (error == ITS_ENOTFOUND || !(cdata))
    {
        BSSAP_ERROR(("FetchCfgData: Config data not found BssId %d\n", bscId));
    }

    BSSAP_DEBUG(("FetchCICRecord: Config data found BssId %d\n", bscId));

    return (cdata);
}

/*implementation:internal
*
* PURPOSE:
*       Fetching config data from NWID LIST table 
* INPUT:
*       point code 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       config data 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0250, ID :: D0260,
*                        ID :: D0270, ID :: D0920
*/
CFGData*
BSSAP_CfgDB::FetchNWIDEntry(ITS_UINT pc)
{
    CFGData* cdata = NULL;
    ITS_INT error = 0;

    BSSAP_DEBUG(("BSSAP_CfgDB: FetchNWIDEntry\n"));

    cdata = (CFGData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_NWID_LIST,
                               (ITS_OCTET *)&pc,
                               sizeof(ITS_UINT),
                               &error);
    if (error == ITS_ENOTFOUND || !(cdata))
    {
        BSSAP_ERROR(("FetchNWIDEntry: Config data not found rpc %d\n", pc));

        return (cdata);
    }

    BSSAP_DEBUG(("FetchNWIDEntry: Config data found rpc %d\n", pc));

    return (cdata);
}

/*implementation:internal
*
* PURPOSE:
*       Deleting config data from RPC LIST table 
* INPUT:
*       bscId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if removed successfully 
*       Error, If any error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0250, ID :: D0260,
*                        ID :: D0270, ID :: D0920
*/
ITS_INT
BSSAP_CfgDB::RemoveRPCEntry(ITS_OCTET bscId)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* cdata = NULL;

    BSSAP_DEBUG(("BSSAP_CfgDB: RemovePRCEntry\n"));

    cdata = FetchRPCEntry(bscId);
   
    if (cdata)
    { 
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_RPC_LIST,
                         (ITS_OCTET *)&bscId,
                         sizeof(ITS_OCTET),
                         cdata);
        if (error != ITS_SUCCESS)
        {   
            BSSAP_ERROR(("RemovePRCEntry: Remove fail %d\n", bscId));

            return (error);
        }
    }
    else
    {
        BSSAP_ERROR(("RemovePRCEntry: Fail to remove config data %d\n", bscId));

        return (error);
    }

    BSSAP_DEBUG(("RemovePRCEntry: Config data removed %d\n", bscId));

    return (error);
}

/*implementation:internal
*
* PURPOSE:
*       Deleting config data from NWID LIST table 
* INPUT:
*       point code 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if removed successfully 
*       Error, If any error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0250, ID :: D0260,
*                        ID :: D0270, ID :: D0920
*/
ITS_INT
BSSAP_CfgDB::RemoveNWIDEntry(ITS_UINT pc)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* cdata = NULL;

    BSSAP_DEBUG(("BSSAP_CfgDB: FetchNWIDEntry\n"));

    cdata = FetchNWIDEntry(pc);
  
    if (cdata)
    {
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_NWID_LIST,
                         (ITS_OCTET *)&pc,
                         sizeof(ITS_UINT),
                         cdata);
        if (error != ITS_SUCCESS)
        {  
            BSSAP_ERROR(("FetchNWIDEntry: Remove fail %d\n", pc));

            return (error);
        }
    }   
    else
    {
        BSSAP_ERROR(("FetchNWIDEntry: Fail to remove config data %d\n", pc));

        return (error);
    }

    BSSAP_DEBUG(("FetchNWIDEntry: Config data removed %d\n", pc));

    return (error);
}
