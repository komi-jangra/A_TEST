/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:15  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:46  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/15 14:54:05  randresol
 * LOG: Add BEHAVIORS_InitSharedBehaviors and BEHAVIORS_CommitSharedBehaviors
 * LOG:
 * LOG: Revision 6.2  2002/03/14 21:40:04  mmiers
 * LOG: Changes for OAM
 * LOG:
 * LOG: Revision 6.1  2002/03/14 18:01:34  mmiers
 * LOG: license fixes, new behaviors implementation, timer block
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_assertion.h>
#include <its_behaviors.h>
#include <its_dsm.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Get a behavior setting
 *
 *  Input Parameters:
 *      m - behavior manager
 *      which - behavior index
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
BEHAVIORS_GetBehavior(BEHAVIOR_Manager *m, ITS_UINT which)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(which < m->numBehaviors);

    return (m->behaviors[which]);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set a behavior.
 *
 *  Input Parameters:
 *      m - behavior manager
 *      which - behavior index
 *      setting - new value
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
BEHAVIORS_SetBehavior(BEHAVIOR_Manager *m,
                      ITS_UINT which,
                      ITS_BOOLEAN setting)
{
    ITS_C_ASSERT(m != NULL);
    ITS_C_ASSERT(which < m->numBehaviors);

    m->behaviors[which] = setting;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      Behavior key in DSM table DSM_TABLE_MGMT_DATA.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI int
BEHAVIORS_CommitSharedBehaviors(ITS_UINT key)
{

    ITS_BOOLEAN *behaviors;
    ITS_INT error;

    if (DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        return (ITS_ENOMEM);
    }

    behaviors = (ITS_BOOLEAN *) DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                                                 DSM_TABLE_MGMT_DATA,
                                                 (ITS_OCTET*)&key,
                                                 sizeof(key),
                                                 &error);
    if (error != ITS_SUCCESS || behaviors == NULL)
    {
        DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        return error;
    }

    DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&key,
                     sizeof(key),
                     behaviors);

    DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);


    return ITS_SUCCESS;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      key : Behavior key in DSM table DSM_TABLE_MGMT_DATA
 *      size: Number of behaviors
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN *
BEHAVIORS_InitSharedBehaviors(ITS_UINT key, ITS_UINT size)
{
    
    ITS_BOOLEAN *behaviors;
    ITS_INT error;

    if (DSM_LockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA) != ITS_SUCCESS)
    {
        return (NULL);
    }

    behaviors = (ITS_BOOLEAN *) DSM_FindNoLock(DSM_MgmtDataFtGroupId,
                                                 DSM_TABLE_MGMT_DATA,
                                                 (ITS_OCTET*)&key,
                                                 sizeof(key),
                                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        /* new entry, allocate the bucket */
        behaviors = (ITS_BOOLEAN *)DSM_AllocNoLock(DSM_MgmtDataFtGroupId,
                                           DSM_TABLE_MGMT_DATA,
                                           (ITS_OCTET *)&key,
                                           sizeof(key),
                                           sizeof(ITS_BOOLEAN)*size,
                                           &error);

        if (error != ITS_SUCCESS || behaviors == NULL)
        {

            DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

            return NULL;
        }
    }
    else if (error != ITS_SUCCESS || behaviors == NULL)
    {
        DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);

        return NULL;
    }

    DSM_CommitNoLock(DSM_MgmtDataFtGroupId,
                     DSM_TABLE_MGMT_DATA,
                     (ITS_OCTET *)&key,
                     sizeof(key),
                     behaviors);

    DSM_UnlockTable(DSM_MgmtDataFtGroupId, DSM_TABLE_MGMT_DATA);


    return behaviors;


}
