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
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:59  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.3  2006/04/20 11:39:21  adutta
 * LOG: Added Iterator
 * LOG:
 * LOG: Revision 9.1.8.2  2005/12/23 20:16:21  adutta
 * LOG: Few more updates
 * LOG:
 * LOG: Revision 9.1.8.1  2005/12/20 14:00:29  yranade
 * LOG: Updates.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:18  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:21  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
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

#ifndef DSM_OPS_H
#define DSM_OPS_H

#include <its++.h>
#include <its_dsm.h>

#include <map>

extern "C"
{
// If the the objects are not standalone, user needs to
// register this function in xml configuration file.
//
// Sample configuration for one FTGroup.
//
// <FtGroup      ftGroupId   = "0"
//               ftGroupName = "FTGroup0">
//
//        <!-- FT Group configuration follows. -->
//
//     <Callbacks>
//            <MembershipChangeCallback
//                       library = "libDRIVER++D.so"
//                       function = "RegisterMembershipChangeCB"
//            />
//     </Callbacks>
//
// </FtGroup>
//
void RegisterMembershipChangeCB(ITS_POINTER object,
                                ITS_POINTER userData,
                                ITS_POINTER callData);
}

/*
 *  DSM Operations data type for user application. By creating
 *  an instance of DSMOps on ftgroupid and tableid, user can 
 *  commit/retrieve the objects to/from DSM region. 
 *
 *  FTRegister class contains static members for registering 
 *  callback to the FT Group manager. The callback function
 *  gets the notifications from FTGroup Manager and updates
 *  the numNodes for number of nodes availabile 
 *  in respective FTGroupID.
 *
 */
class DSMOps
{
    public:
        struct DSMInfo
        {
            ITS_USHORT ftGroupId;
            ITS_UINT   numActiveNodes;
            bool       registered;
            bool       isSelfNodeActive; 
        };

        class FTRegister
        {
            public:
               static void InitStaticMembers() 
                               throw(its::Postcondition);

               static int  RegisterCallbackToFTGroup(ITS_USHORT ftGroupId) 
                               throw(its::Precondition, its::Postcondition);

               static int  DeregisterFTGroupCallback(ITS_USHORT ftGroupId) 
                               throw(its::Precondition, its::Postcondition);

               static ITS_UINT GetNumofNodesInFTGroup(ITS_USHORT ftGroupID)
                               throw(its::Precondition);

               static bool IsSafeToCallDSMFree(ITS_USHORT ftGroupId)
                               throw(its::Precondition);

               static ITS_USHORT GetMaxFTGroups();

               static ITS_UINT   GetSelfNodeID();

               static void UpdateDSMInfo(DSMInfo &info);

            private:

               static ITS_USHORT maxFtGroups;

               static ITS_UINT   selfNodeId;

               static std::map<ITS_USHORT, DSMOps::DSMInfo> dsmInfo;

               typedef std::map<ITS_USHORT, DSMOps::DSMInfo>::iterator   
                                                     MAP_ITR_T;
               typedef std::map<ITS_USHORT, DSMOps::DSMInfo>::value_type 
                                                     MAP_VALUE_T;
        };

        DSMOps(ITS_USHORT ftGroupId = 0, 
               ITS_UINT ftTableId = 48) throw(its::Precondition);

        virtual ~DSMOps();

        template <class Type>
        int InsertObject(Type &T, ITS_OCTET *key,
                          ITS_UINT key_len) throw(its::Precondition,
                                              its::Postcondition)
        {
            int ret = ITS_SUCCESS;

            try
            {
                ret = InsertObject((void *)&T, sizeof(Type), key, key_len);
            }
            catch (...)
            {
                throw;
            }

            return (ret);
        }

        template <class Type>
        int GetObject(Type *T, ITS_OCTET *key, 
                       ITS_UINT key_len) throw(its::Precondition, 
                                               its::Postcondition)
        {
            int ret = ITS_SUCCESS;

            try
            {
                ret = GetObject(T, sizeof(Type), key, key_len);
            }
            catch (...)
            {
                throw;
            }
            return ret;
        }

        void *Find(ITS_OCTET *key,
                   ITS_UINT key_len) throw(its::Precondition, 
                                          its::Postcondition);
    
        bool UnlockRow(void *dsm_ptr, ITS_OCTET *key, 
                       ITS_UINT key_len) throw(its::Precondition,
                                                its::Postcondition);

        int DeleteObject(ITS_OCTET *key, ITS_UINT key_len) 
                 throw(its::Precondition, its::Postcondition);

        void Iterate(DSM_IterateEntryProc iterateEntryFn)
        {
            DSM_TableIterate(ftGroupId, ftTableId, NULL, NULL, iterateEntryFn);
        }

    private:

        int InsertObject(void *ptr, size_t objsize, ITS_OCTET *key,
                   ITS_UINT key_len);

        int GetObject(void *ptr, size_t size, ITS_OCTET *key,
                       ITS_UINT key_len);

        ITS_USHORT        ftGroupId;
        ITS_UINT          ftTableId;
};

#endif

