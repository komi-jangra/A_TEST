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
 * ID: $Id: bssap_msc-cicdb.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.2  2005/11/28 05:07:30  adutta
 * LOG: Flag added for abnormal unblk/blk ack (Issue fix)
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 *
 * LOG:
 ****************************************************************************/

#include <bssap_msc-cicdb.h>

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
*       Adding cic info in CIC CTXT table 
* INPUT:
*       nwId, pcm, startTS, endTS 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*      Success, if successfully added in to table 
*      Error, if error occurs while adding
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0220, ID :: D0230,
*                        ID :: D0240, ID :: D0920
*/
ITS_INT
BSSAP_CicDB::AddCIC(ITS_OCTET nwId, ITS_USHORT pcm,
                    ITS_USHORT startTS, ITS_USHORT endTS)
{
    ITS_INT error = 0;
    ITS_USHORT index;
    ITS_UINT key = 0;
    CICData* fptr;

    BSSAP_DEBUG(("BSSAP_CicDB: AddCIC\n"));

    if (!endTS)
    {
        endTS = startTS;
    }

    for (index = startTS; index <= endTS; index++)
    {
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & index));
  
        fptr = (CICData *)DSM_Find(DSM_SccpFtGroupId,
                                   DSM_TABLE_BSSAP_CIC_CTXT,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT), 
                                   &error);
        if (error == ITS_ENOTFOUND)
        {
            fptr = (CICData*) DSM_Alloc(DSM_SccpFtGroupId,
                                        DSM_TABLE_BSSAP_CIC_CTXT,
                                        (ITS_OCTET *)&key,
                                        sizeof(ITS_UINT),
                                        sizeof(CICData),
                                        &error);
            fptr->statusFlag = ITS_FALSE;
            fptr->timerId = 0;
            fptr->localState = CIC_ST_UNBLK;
            fptr->remoteState = CIC_ST_UNBLK;

            fptr->callState = CALL_ST_IDLE;
            fptr->ts = index;
            fptr->pcm = pcm;
            fptr->nwId = nwId;

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_CIC_CTXT,
                               (ITS_OCTET *)&key,
                               sizeof(ITS_UINT), 
                               fptr);
            if (error != ITS_SUCCESS)
            {
                BSSAP_ERROR(("AddCIC: Couldn't add %d %d\n", pcm, index));

                return (error);
            }
            else
            {
                BSSAP_DEBUG(("AddCIC: Added context %d %d\n", pcm, index));
            }
        }
        else
        {
            BSSAP_WARNING(("AddCIC: Context exists %d %d\n", pcm, index));

            return (!ITS_SUCCESS);
        }
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       Fetching cic info from CIC CTXT table 
* INPUT:
*       cic 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      cic data 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0220, ID :: D0230,
*                        ID :: D0240, ID :: D0920
*/
CICData*
BSSAP_CicDB::FetchCICRecord(ITS_UINT cic)
{
    CICData* cdata = NULL;
    ITS_INT error = 0;

    BSSAP_DEBUG(("BSSAP_CicDB: FetchCICRecord\n"));

    cdata = (CICData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_CIC_CTXT,
                               (ITS_OCTET *)&cic,
                               sizeof(ITS_UINT),
                               &error);
    if (error == ITS_ENOTFOUND || !(cdata))
    {
        BSSAP_ERROR(("FetchCICRecord: CIC context not found %d\n", cic));
    }
    else
    {
        BSSAP_DEBUG(("FetchCICRecord: Context found %d\n", cic));
    }

    return (cdata);
}

/*implementation:internal
*
* PURPOSE:
*       Deleting cic info from CIC CTXT table 
* INPUT:
*      cic 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if removed successfully 
*       Error, if error occured while removing 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0220, ID :: D0230,
*                        ID :: D0240, ID :: D0920
*/
ITS_INT
BSSAP_CicDB::RemoveCICRecord(ITS_UINT cic)
{
    ITS_INT error = !ITS_SUCCESS;
    CICData* cdata = NULL;

    BSSAP_DEBUG(("BSSAP_CicDB: RemoveCICRecord\n"));

    cdata = FetchCICRecord(cic);
   
    if (cdata)
    { 
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_CIC_CTXT,
                         (ITS_OCTET *)&cic,
                         sizeof(ITS_UINT),
                         cdata);
        if (error != ITS_SUCCESS)
        {   
            BSSAP_ERROR(("RemoveCICRecord: Fail to remove context  %d\n", cic));

            return (error);
        }
    }
    else
    {
        BSSAP_ERROR(("RemoveCICRecord: Fail to remove context  %d\n", cic));

        return (error);
    }

    BSSAP_DEBUG(("RemoveCICRecord: Context removed %d\n", cic));

    return (error);
}

/*implementation:internal
*
* PURPOSE:
*       Modifying cic info in CIC CTXT table 
* INPUT:
*       cic, cicRec 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if modification done successfully 
*       Error, if error occured while modification 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0220, ID :: D0230,
*                        ID :: D0240, ID :: D0920
*/
ITS_INT
BSSAP_CicDB::ModifyCICRecord(ITS_UINT cic, CICData* cicRec)
{
    ITS_INT error = 0;

    BSSAP_DEBUG(("BSSAP_CicDB: ModifyCICRecord\n"));

    if (cicRec)
    {
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_CIC_CTXT,
                           (ITS_OCTET *)&cic,
                           sizeof(ITS_UINT),
                           cicRec);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("ModifyCICRecord: Couldn't modify context %d\n", cic));

            return (error);
        }
        else
        {
            BSSAP_DEBUG(("ModifyCICRecord: Modified context %d\n", cic));
        }
    }
    else
    {
        BSSAP_ERROR(("ModifyCICRecord: Couldn't modify context %d\n", cic));

        return (ITS_ENOTFOUND);
    }

    return (error);
}

/*implementation:internal
*
* PURPOSE:
*       Get count of the CIC CTXT table records 
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       size of the table 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0220, ID :: D0230,
*                        ID :: D0240, ID :: D0920
*/
ITS_UINT
BSSAP_CicDB::GetCICRecordCount()
{
    ITS_UINT size = 0;

    BSSAP_DEBUG(("BSSAP_CicDB: GetCICRecordCount\n"));

    DSM_TableGetSize(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT, &size);

    return (size);
}

