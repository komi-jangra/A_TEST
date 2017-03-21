/****************************************************************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:44  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:41  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:00  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.2  2005/12/23 20:15:59  adutta
 * LOG: Few more updates
 * LOG:
 * LOG: Revision 9.1.8.1  2005/12/20 14:00:50  yranade
 * LOG: Updates.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:19  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:21  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.4.46.1  2005/01/05 07:21:23  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 1.4  2002/11/14 21:54:36  lbana
 * LOG: warning removal in switch statement(missing default.)
 * LOG:
 * LOG: Revision 1.3  2002/11/14 15:34:41  pmandal
 * LOG: missing public and namespace keywords in header.
 * LOG:
 * LOG: Revision 1.2  2002/11/13 23:22:54  lbana
 * LOG: DSM C++ object for commits and retrievals.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/11/13 22:24:57  lbana
 * LOG: C++ object for DSM commits and retrievals.
 * LOG:
 ***************************************************************************/
#include <dsm_ops.h>
#include <its_timers.h>
#include <its_mutex.h>
#include <its_trace.h>

using namespace std;
using namespace its;

// FT Member ship change callback is not 
// yet registered to the Accelero
ITS_USHORT DSMOps::FTRegister::maxFtGroups = 0;
ITS_UINT   DSMOps::FTRegister::selfNodeId  = 0;

std::map<ITS_USHORT, DSMOps::DSMInfo> DSMOps::FTRegister::dsmInfo;

its::Mutex *initGuard = new its::Mutex(0);

/*.
 *******************************************************************
 *  Purpose:
 *     FTRegister has static members for registering Callbacks to
 *     FT Group manager. The registered callback receives notifications
 *     such as Member Join/Leave/Dead from FT Manager, and also records 
 *     the info on num of nodes available in the FT Group.
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
void
DSMOps::FTRegister::InitStaticMembers()
        throw(its::Postcondition)
{
    static bool init = false;
    int ret;

    if ( (ret = initGuard->Acquire()) != ITS_SUCCESS)
    {
        ITS_THROW_ENSURE(ret == ITS_SUCCESS)
    }

    if (!init)
    {
        FTRegister::maxFtGroups = DSM_GetMaxNumFtGroups();

        FTRegister::selfNodeId  = DSM_GetNodeId();

        init = true;
    }

    if ( (ret = initGuard->Release()) != ITS_SUCCESS)
    {
        ITS_THROW_ENSURE(ret == ITS_SUCCESS);
    }

    return;
}

/*.
 *******************************************************************
 *  Purpose:
 *     Removes callback from FTManager for this FTGroupId.
 *
 *  Input Parameters:
 *     ftGroupId - FT Group ID
 *
 *  Output Parameters:
 *
 *  Return Values:
 *     Returns ITS_SUCCESS on removal of callback that is registered 
 *     to the FTGroup.
 *     If this function doesn't find callback manager for ftGroupId
 *     it throws Precondition exception. 
 *     on failure to remove callback, function throws Postcondition.
 *
 *******************************************************************/
int
DSMOps::FTRegister::DeregisterFTGroupCallback(ITS_USHORT ftGroupId)
    throw(its::Precondition, its::Postcondition)
{
    int ret = ITS_SUCCESS;
    CALLBACK_Manager *cb_manager = NULL;
    FTRegister::MAP_ITR_T itr;
    bool flag = false;

    ITS_THROW_REQUIRE(ftGroupId < FTRegister::maxFtGroups);

    if ( (ret = initGuard->Acquire()) != ITS_SUCCESS)
    {
        ITS_THROW_ENSURE(ret == ITS_SUCCESS)
    }

    itr = dsmInfo.find(ftGroupId);

    if (itr != dsmInfo.end())
    {
        // Go ahead and erase the iterator.
        dsmInfo.erase(itr);
    }
    else
    {
        flag = true; // We already deregister Callback from 
                     // FT Group callback manger. 
    }

    if ( (ret = initGuard->Release()) != ITS_SUCCESS)
    {
        ITS_THROW_REQUIRE(ret == ITS_SUCCESS);
    }

    if (!flag)
    {
        cb_manager = DSM_GetMembershipChangeCallbacks(ftGroupId);

        ITS_THROW_REQUIRE(cb_manager != NULL);

        ret= CALLBACK_RemCallback(cb_manager,
                                  RegisterMembershipChangeCB,
                                  NULL);
    }

    ITS_THROW_ENSURE(ret == ITS_SUCCESS);

    return ret;
}

ITS_USHORT
DSMOps::FTRegister::GetMaxFTGroups()
{
    return DSMOps::FTRegister::maxFtGroups;
}

ITS_UINT
DSMOps::FTRegister::GetSelfNodeID()
{
    return DSMOps::FTRegister::selfNodeId;
}

/*.
 *********************************************************************
 * Purpose:
 *     This function registers a callback RegisterMembershipChangeCB()
 *     to respective FT Group to receieve notifications from FTManager.
 * 
 * Input Parameters:
 *     ftGroupId - FT Group Id to get notifications from FT Group. 
 *
 * Return Value:
 *     if registration is successful the function returns ITS_SUCCESS.
 *     On error it throws Precondition or Postcondition exception. 
 *
 ********************************************************************/
int 
DSMOps::FTRegister::RegisterCallbackToFTGroup(ITS_USHORT ftGroupId)
         throw(its::Precondition, its::Postcondition)
{
    int ret;
    CALLBACK_Manager *manager = NULL;
    FTRegister::MAP_ITR_T itr;
    bool flag = false;

    if ( (ret = initGuard->Acquire()) != ITS_SUCCESS)
    {
        ITS_THROW_REQUIRE(ret == ITS_SUCCESS);
    }

    itr = dsmInfo.find(ftGroupId);

    if (itr != dsmInfo.end())
    {
        DSMInfo &info = itr->second;

        if (info.registered)
        {
            flag = true; // Callback is already registered
                         // to the FT Group.
        }
    }

    if ( (ret = initGuard->Release()) != ITS_SUCCESS)
    {
        ITS_THROW_REQUIRE(ret == ITS_SUCCESS);
    }

    if (!flag)
    {
        manager = DSM_GetMembershipChangeCallbacks(ftGroupId);

        ITS_THROW_REQUIRE(ftGroupId < FTRegister::maxFtGroups && 
                          manager != NULL);

        //Add callback to the FTCallback manager.
        ret = CALLBACK_AddCallback(manager, 
                                   RegisterMembershipChangeCB,
                                   NULL/*user data*/);
        ITS_THROW_ENSURE(ret == ITS_SUCCESS);
    }

    return ITS_SUCCESS;
}

/*.
 *******************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
ITS_UINT 
DSMOps::FTRegister::GetNumofNodesInFTGroup(ITS_USHORT ftGroupId)
         throw(its::Precondition)
{
    ITS_UINT      ret = 0;
    FTRegister::MAP_ITR_T itr;

    if (ftGroupId > FTRegister::maxFtGroups) 
    {
        ITS_THROW_REQUIRE(ftGroupId < FTRegister::maxFtGroups);
    }

    if ( (itr = dsmInfo.find(ftGroupId)) != dsmInfo.end())
    {
        DSMInfo &info = itr->second;

        ret = info.numActiveNodes;
    }

    return ret;
}

bool
DSMOps::FTRegister::IsSafeToCallDSMFree(ITS_USHORT ftGroupId)
        throw(its::Precondition)
{
    bool     ret = false;
    FTRegister::MAP_ITR_T itr;

    ITS_THROW_REQUIRE(ftGroupId < FTRegister::maxFtGroups);

    itr = dsmInfo.find(ftGroupId);

    if (itr != dsmInfo.end())
    {
        DSMInfo &info = itr->second;

        // If no more active nodes in the FT Group return true. 
        // Or if there is a node serving actively in the 
        // FT group and the SELF NODE is active we return true.
        // anyother case we return false.
 
        if((info.numActiveNodes == 0) ||
           ((info.numActiveNodes == 1) && 
            info.isSelfNodeActive))
        {
            ret = true;
        }
    }

    return ret;
}

void
DSMOps::FTRegister::UpdateDSMInfo(DSMOps::DSMInfo &info)
{
    DSMOps::FTRegister::MAP_ITR_T itr = 
                       dsmInfo.find(info.ftGroupId);
    if (itr != dsmInfo.end())
    {
        DSMOps::DSMInfo *ptr = &(itr->second);

        ptr->numActiveNodes   = info.numActiveNodes;
        ptr->isSelfNodeActive = info.isSelfNodeActive;
    }
    else
    {
        info.registered = true;      // mark as registered for DSM callback
                                     // for this FT Group Id.

        FTRegister::MAP_VALUE_T value(info.ftGroupId, info);

        itr = dsmInfo.insert(dsmInfo.begin(), value);
    }

    return;
}

/*.
 *******************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
extern "C" void
RegisterMembershipChangeCB(ITS_POINTER object,
                           ITS_POINTER userData,
                           ITS_POINTER callData)
{
    ITS_INT     ret = 0;
    ITS_USHORT  ftGroupId;
    DSM_MembershipChangeCbData *membershipCbData =
              (DSM_MembershipChangeCbData *)callData;

    DSM_MembershipChangeType type;
    DSMOps::DSMInfo     info;

    if (membershipCbData == NULL)
    {
        return;
    }

    try
    {
        DSMOps::FTRegister::InitStaticMembers();
        ftGroupId = membershipCbData->ftGroupId;
        type = membershipCbData->membershipChangeType;

        if (ftGroupId > DSMOps::FTRegister::GetMaxFTGroups())
        {
             ITS_TRACE_CRITICAL(("RegisterMembershipChangeCB: Exceeds Maximum FT Groups\n"));
             abort();
        }

        if ( (ret = initGuard->Acquire()) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("RegisterMembershipChangeCB:"
                             "Failed to Acquire mutex."));

            return;
        }

        switch (type)
        {
            case DSM_FT_GROUP_MEMBER_JOIN:
            case DSM_FT_GROUP_MEMBER_LEAVE:
            case DSM_FT_GROUP_MEMBER_DEAD:

                info.ftGroupId      = ftGroupId;
                info.numActiveNodes = 
                             membershipCbData->numFtGroupMembers;

                if ((membershipCbData->memberNodeId ==
                     DSMOps::FTRegister::GetSelfNodeID()) &&
                    (type != DSM_FT_GROUP_MEMBER_JOIN))
                {
                    info.isSelfNodeActive = false; 
                }
                else if (membershipCbData->memberNodeId == 
                          DSMOps::FTRegister::GetSelfNodeID())
                {
                    info.isSelfNodeActive = true;
                }

                DSMOps::FTRegister::UpdateDSMInfo(info);
    
                break;

            default:
                break;
        }

        if ( (ret = initGuard->Release()) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("RegisterMembershipChangeCB:"
                             "Failed to Release mutex."));

            return;
        }
    }
    catch (its::Precondition exc)
    {
        throw;
    }
    catch (its::Postcondition exc)
    {
        throw;
    }

    return;
}


/*.
 *******************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
DSMOps::DSMOps(ITS_USHORT gid, ITS_UINT tid)
     throw(its::Precondition)
{
    ITS_THROW_REQUIRE(tid > 48 || 
                     gid < DSM_GetMaxNumFtGroups());
 
    ftGroupId = gid;
    ftTableId = tid;

    try
    {
        DSMOps::FTRegister::InitStaticMembers();

        DSMOps::FTRegister::RegisterCallbackToFTGroup(gid);
    }
    catch (its::Precondition exc)
    {
        throw;
    }
    catch (its::Postcondition exc)
    {
        throw;
    }
}

/*.
 *******************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
DSMOps::~DSMOps()
{
    try
    {
        DSMOps::FTRegister::DeregisterFTGroupCallback(ftGroupId);
    }
    catch (its::Precondition exc)
    {
        throw;
    }
    catch (its::Postcondition exc)
    {
        throw;
    }
}

/*.
 *******************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
int
DSMOps::DeleteObject(ITS_OCTET *key, ITS_UINT key_len)
         throw(its::Precondition, its::Postcondition)
{
    int   ret = ITS_ENOTFOUND;
    int   error;
    void  *dsm_ptr;

    ITS_THROW_REQUIRE(key != NULL && key_len != 0);

    do
    {
        dsm_ptr = DSM_Find(ftGroupId, ftTableId,
                           key,
                           key_len,
                           &error);

        if (error == ITS_EINUSE)
        {
            TIMERS_USleep(100);
        }
    }
    while (error == ITS_EINUSE);

    if (dsm_ptr != NULL &&
        error == ITS_SUCCESS)
    {
        /*
         * DSM_Free(ITS_USHORT ftGroupId,
         *          ITS_UINT   tableId,
         *          ITS_OCTET  *key,
         *          ITS_UINT   keyLen,
         *          void       *object);
         *
         * Unlocks the row, locked by DSM_Find().
         */
        ret = DSM_Free(ftGroupId, ftTableId,
                       key,
                       key_len,
                       dsm_ptr);

        if (ret == ITS_SUCCESS)
        {
            dsm_ptr = NULL;
        }
        else
        {
            ITS_THROW_ENSURE(ret == ITS_SUCCESS);
        }
    }

    return (ret);
}

/*.
 *******************************************************************
 *  Purpose:
 *      Inserts a user object into the DSM region, with  the user 
 *      provided Hash key and Hash key length.
 *
 *      This method is a private function not for the user.
 *      User invokes template public function Insert().
 *
 *  Input Parameters:
 *      ptr     - address of user object.
 *      objSize - size of the user object.
 *      key     - Hash key.
 *      key_len - hash key length.
 *
 *  Output Parameters:
 * 
 *  Return Values:
 *      Returns ITS_SUCCESS upon commiting the object in DSM region.
 *      If the key or key lenth is not valid this function throws
 *      Precondition exception.
 *      In case of failure it throws Postcondition.
 *
 *******************************************************************/
int 
DSMOps::InsertObject(void *ptr, size_t objSize, ITS_OCTET *key, 
               ITS_UINT key_len)
{
    int  ret = 0;
    void *dsm_ptr = NULL;

    try
    {
        dsm_ptr = Find(key, key_len);

        if (dsm_ptr == NULL)
        {
            dsm_ptr = DSM_Alloc(ftGroupId, ftTableId,
                                key, key_len, objSize, &ret);

            ITS_THROW_ENSURE((dsm_ptr != NULL) &&
	         	     (ret == ITS_SUCCESS));
        }

        memcpy(dsm_ptr, ptr, objSize);

        ret = DSM_Commit(ftGroupId, ftTableId,
                         key, key_len,
                         dsm_ptr);

        ITS_THROW_ENSURE(ret == ITS_SUCCESS);
    }
    catch (...)
    {
        throw;
    }
    return ret;
}

/*.
 *******************************************************************
 *  Purpose:
 *     This function locates the object in DSM if it already exists 
 *     This function holds IMPLICIT lock on the DSM row, user 
 *     need to call UnlockRow on the pointer returned by the user.
 *     The function holds implicit lock only if it finds an object
 *     in DSM. 
 *
 *  Input Parameters:
 *     key     - hash key value for the object to find in DSM
 *     key_len - hash key length.
 *
 *  Output Parameters:
 *
 *  Return Values:
 *     On success the function returns a pointer to a requested
 *     object or else returns NULL.
 *
 *     If user passes NULL key or zero length, the function throws
 *     Precondion exception.
 *
 *******************************************************************/
void *
DSMOps::Find(ITS_OCTET *key, ITS_UINT key_len) 
         throw(its::Precondition, its::Postcondition)
{
    int  ret = 0;
    void *dsm_ptr = NULL;

    if (key == NULL || key_len == 0)
    {
        ITS_THROW_REQUIRE(key != NULL);
    }

    do
    {
        dsm_ptr = DSM_Find(ftGroupId, ftTableId,
                           key, key_len,
                           &ret);

        if (ret == ITS_EINUSE)
        {
            TIMERS_USleep(200);
        }
    }
    while (ret == ITS_EINUSE);

    return dsm_ptr;
}

/*.
 *******************************************************************
 *  Purpose:
 *     THis function is to retrieve the object from the DSM with
 *     hash key and key length. If GetObject finds an object in
 *     DSM it copies into the pointer passed by the user.
 *
 *  Input Parameters:
 *     ptr     - pointer to an object. This pointer should contain
 *               enough buffer to copy user object from DSM.
 *     objSize - size of the user object.
 *     key     - hash key values.
 *     key_len - Hash key length.
 *
 *  Output Parameters:
 *
 *  Return Values:
 *     On success the function returns ITS_SUCCESS.
 *     If key or key_len is not valid then the function
 *     throws Precondition exception.
 *
 *******************************************************************/
int 
DSMOps::GetObject(void *ptr, size_t objSize, ITS_OCTET *key,
                  ITS_UINT key_len)
{
    void *dsm_ptr;
    int  ret = ITS_ENOTFOUND;

    try
    {
        if (ptr == NULL)
        {
            ITS_THROW_REQUIRE(ptr != NULL);
        }

        if ( (dsm_ptr = Find(key, key_len)) != NULL)
        {
            memcpy(ptr, dsm_ptr, objSize);

            ret = UnlockRow(dsm_ptr, key, key_len);
        }
    }
    catch (...)
    {
        throw;
    }

    return ret;
}

/*.
 *******************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Output Parameters:
 *
 *  Return Values:
 *
 *******************************************************************/
bool
DSMOps::UnlockRow(void *dsm_ptr, ITS_OCTET *key, ITS_UINT key_len)
         throw(its::Precondition, its::Postcondition)
{
    int ret;

    if (key == NULL || dsm_ptr == NULL)
    {
        ITS_THROW_REQUIRE(key != NULL && dsm_ptr != NULL);

    }

    ret = DSM_UnlockRow(ftGroupId, ftTableId,
                        key, key_len,
                        dsm_ptr);

    ITS_THROW_ENSURE(ret == ITS_SUCCESS);

    return (ret);
}
