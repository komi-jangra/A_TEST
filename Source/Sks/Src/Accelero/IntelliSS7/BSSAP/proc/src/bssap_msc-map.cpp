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
 * ID: $Id: bssap_msc-map.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.19  2006/06/28 04:55:05  adutta
 * LOG: Return !success on receipt of clear complete
 * LOG:
 * LOG: Revision 1.1.2.18  2006/05/24 10:17:36  adutta
 * LOG: No cic check for LocUpdate
 * LOG:
 * LOG: Revision 1.1.2.17  2006/05/24 05:07:32  adutta
 * LOG: RLSD called in ClearComplete (Change Request)
 * LOG:
 * LOG: Revision 1.1.2.16  2006/05/05 05:21:25  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.15  2006/04/25 05:31:49  adutta
 * LOG: Changes as par IMR comments
 * LOG:
 * LOG: Revision 1.1.2.14  2005/12/29 10:25:50  mkrishna
 * LOG: Check removed for Cipher mode cmd
 * LOG:
 * LOG: Revision 1.1.2.13  2005/12/27 10:31:20  mkrishna
 * LOG: Unequipped Ckt cic list logic changed
 * LOG:
 * LOG: Revision 1.1.2.12  2005/12/23 18:01:32  adutta
 * LOG: Changed CIC list logic
 * LOG:
 * LOG: Revision 1.1.2.11  2005/12/23 05:42:39  adutta
 * LOG: Changed the Unequipped logic
 * LOG:
 * LOG: Revision 1.1.2.10  2005/12/22 16:04:31  adutta
 * LOG: Memory free removed
 * LOG:
 * LOG: Revision 1.1.2.9  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.8  2005/12/01 10:49:13  mkrishna
 * LOG: Added confusion message in UDT list
 * LOG:
 * LOG: Revision 1.1.2.7  2005/11/30 06:47:48  mkrishna
 * LOG: Pegs implemetation and cause value change in confusion msg
 * LOG:
 * LOG: Revision 1.1.2.6  2005/11/28 05:21:49  adutta
 * LOG: Fix for Issue#3069/3068/3064
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/18 06:37:02  mkrishna
 * LOG: Changed API
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/17 06:31:56  mkrishna
 * LOG: Trace and funtion return changes
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/08 07:17:39  mkrishna
 * LOG: Procedures for Reset/CktGrpBlk/CktGrpUnBlk
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/14 10:14:09  adutta
 * LOG: Handled handover complete
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#include <bssap_msc-map.h>
#include <bssap_msc-fsm.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-cicdb.h>
#include <bssap_msc-error.h>
#include <bssap_msc-interface.h>
#include <bssap_msc-sccphandler.h>
#include <bssap_msc-pegs.h>

its::Mutex* BSSAP_Map::mlock;
ResetData rData;
OverloadData oData;
ITS_BOOLEAN isFirst = ITS_TRUE;

/*implementation:internal
*
* PURPOSE:
*       Reset the states to default values 
* INPUT:
*       None 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  25-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0560, ID :: D0570
*/
static ITS_INT
SetAllCIC(ITS_POINTER entry, void *in, void *out)
{
    CICData* crec = (CICData*)entry;
    ITS_UINT cic = 0;  
    ITS_INT error = 0;
    ITS_BOOLEAN flag = ITS_FALSE;

    if (!crec) 
    {
        BSSAP_ERROR(("SetAllCIC: Couldn't find context \n"));

        return (ITS_ENOTFOUND);
    }

    /* if all the states are default, no need to commit in DSM again */
    if ((crec->callState == CALL_ST_IDLE) && 
        (crec->localState == CIC_ST_UNBLK) && 
        (crec->remoteState == CIC_ST_UNBLK))
    {
        flag = ITS_TRUE;
    }

    if (!flag)
    {
        crec->callState = CALL_ST_IDLE;
        crec->localState = CIC_ST_UNBLK;
        crec->remoteState = CIC_ST_UNBLK;

        if (crec->timerId)
        {
            // Cancel running timer if any
            BSSAP_Timer t1(BSSAP_T_21);

            t1.CancelUDTTimer(crec->timerId);
            crec->timerId = 0;
        }

        cic = (crec->nwId << 16) | ((crec->pcm << 5) | (0x1FU & crec->ts));

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_CIC_CTXT,
                           (ITS_OCTET *)&cic,
                           sizeof(ITS_UINT),
                           crec);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("SetAllCIC: Couldn't commit context %d\n", cic));

            return (error);
        }
        else
        {
            BSSAP_DEBUG(("SetAllCIC: Modified context %d\n", cic));
        }
    }

    return (error);
}

/*implementation:internal
*
* PURPOSE:
*       performing check for UDT messages 
* INPUT:
*       msg type 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       true, if UDT message found
*       false, if not 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0450, ID :: D0920
*/
ITS_BOOLEAN
BSSAP_Map::IsUDT(ITS_OCTET mType)
{
    ITS_BOOLEAN ret = ITS_FALSE;

    BSSAP_DEBUG(("BSSAP_Map: IsUDT \n"));

    switch (mType)
    {
        case BSSAP_MSG_RESET:
        case BSSAP_MSG_RESET_ACK:
        case BSSAP_MSG_RESET_CIRCUIT:
        case BSSAP_MSG_RESET_CIRCUIT_ACK:
        case BSSAP_MSG_PAGING:
        case BSSAP_MSG_BLOCK:
        case BSSAP_MSG_BLOCK_ACK:                     
        case BSSAP_MSG_UNBLOCK:                      
        case BSSAP_MSG_UNBLOCK_ACK:                 
        case BSSAP_MSG_CKT_GROUP_BLOCK:            
        case BSSAP_MSG_CKT_GRP_BLK_ACK:           
        case BSSAP_MSG_CKT_GRP_UNBLOCK:          
        case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:    
        case BSSAP_MSG_OVERLOAD:    
        case BSSAP_MSG_UNEQUIPPED_CKT:    
        case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:    
        case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:    
        case BSSAP_MSG_RESOURCE_INDICATION:    
        case BSSAP_MSG_RESOURCE_REQUEST:    
        case BSSAP_MSG_LOAD_INDICATION:    
        case BSSAP_MSG_CONNECTIONLESS_INFORMATION:    
        case BSSAP_MSG_CONFUSION:    
            ret = ITS_TRUE;
        break;
    }    

    return (ret);   
}

/*implementation:internal
*
* PURPOSE:
*       modifying cic record for block req message 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0510,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT 
BSSAP_Map::ProcessBlockReq(BSSAP_Message* mMap, 
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessBlockReq\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessBlockReq: BlockReq pcm %d slot %d nwId %d\n", 
                                                  pcm, ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->localState == CIC_ST_BLOCK)
            {
                BSSAP_ERROR(("ProcessBlockReq: Block for already blk. cic\n"));

                return (!ITS_SUCCESS);
            }
            else
            {
                crec->localState = CIC_ST_BLOCK;
                ret = cicdb.ModifyCICRecord(key, crec);
        
                // Since MSC is master, it shall not send BLOCK 
                return (BSSAP_EMSCMASTER);
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessBlockReq: invalid pcm %d ts %d nwId %d\n",
                                                                pcm, ts, nwId));
            // Send BSSAP_ECICNOTFOUND to the application
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND, 
                                                     BSSAP_MSG_BLOCK, pcm, ts);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessBlockReq: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifying cic record for unblock req message 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0530,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessUnBlockReq(BSSAP_Message* mMap,
                             ITS_OCTET* buff,
                             ITS_INT len,
                             ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessUnBlockReq\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessUnBlockReq: UnBlockReq pcm %d slot %d nwId %d\n", 
                                                           pcm,ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->localState == CIC_ST_BLOCK)
            {
                crec->localState = CIC_ST_UNBLK;
                ret = cicdb.ModifyCICRecord(key, crec);

                // Since MSC is master, it shall not send UN-BLOCK 
                return (BSSAP_EMSCMASTER);
            }
            else
            {
                BSSAP_ERROR(("ProcessUnBlockReq: UnBlock for unblk cic\n"));

                return (!ITS_SUCCESS);
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessUnBlockReq: invalid pcm %d timelsot %d 
                                                 nwId %d\n", pcm, ts, nwId));

            // Send BSSAP_ECICNOTFOUND to the application
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                                BSSAP_MSG_UNBLOCK, pcm, ts);
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessUnBlockReq: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifying cic record for reset req message 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0560,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetReq(BSSAP_Message* mMap,
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)
{
    ITS_INT ret = 0;
    rData.timerId = 0;
                                                                                                                                              
    BSSAP_Timer t(BSSAP_T_16);

    DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT,
                     NULL, NULL, SetAllCIC);

    rData.timerId = t.StartUDTTimer(0, 0, BSSAP_MSG_RESET, buff, len, nwId);

    if (rData.timerId == ITS_ETIMERSTARTFAIL)
    {
        return (!ITS_SUCCESS);
    }

    return (ret); 
}

/*implementation:internal
*
* PURPOSE:
*       Cancel timer for Reset message
* INPUT:
*       mMap, buff, len, nwid
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer cancelled successfully
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0570,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetAckReq(BSSAP_Message* mMap,
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_Map: ProcessResetAckReq\n"));
                                                                                                                                              
    BSSAP_Timer t(BSSAP_T_2);

    if (rData.timerId)
    {
        ret = t.CancelUDTTimer(rData.timerId);

        rData.timerId = 0;
    }
    else
    {
        return (!ITS_SUCCESS);
    }          

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       modifying cic record for reset circuit req message 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetCktReq(BSSAP_Message* mMap,
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessResetCktReq\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessResetCktReq: pcm %d slot %d nwId %d\n", 
                                                         pcm, ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(BSSAP_T_21);

                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;
            }

            BSSAP_Timer t(BSSAP_T_12);

            ret = t.StartUDTTimer(key, 0, BSSAP_MSG_RESET_CIRCUIT, buff,
                                                                   len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
                return (ret);
            }

            crec->timerId = ret;
            crec->callState = CALL_ST_IDLE;
            crec->localState = CIC_ST_UNBLK;
            crec->remoteState = CIC_ST_UNBLK;

            ret = cicdb.ModifyCICRecord(key, crec);

            return (ret);
        }
        else
        {
            BSSAP_ERROR(("ProcessResetCktReq: invalid pcm %d "
                                    "timelsot %di nwId %d\n", pcm, ts, nwId));

            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                             BSSAP_MSG_RESET_CIRCUIT, pcm, ts);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessResetCktReq: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       removing cic record from the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record removed successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessUnequipCktReq(BSSAP_Message* mMap,
                                ITS_OCTET* buff,
                                ITS_INT len,
                                ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0, flag = 0;
    ITS_OCTET  ts = 0, range = 0, cicTs = 0;
    ITS_OCTET  startTS = 0; 
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* ie = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Interface bssIf;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessUnequipCktReq\n"));
                                                                                                                                              
    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        cicTs = startTS = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & cicTs));
                                                                                                                                              
        BSSAP_DEBUG(("ProcessUnequipCktReq: pcm %d slot %d nwId %d\n",
                                                   pcm, cicTs, nwId));
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(BSSAP_T_21);

                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;
            }

            crec->localState = CIC_ST_BLOCK;

            ret = cicdb.ModifyCICRecord(key, crec);
            if (ret != ITS_SUCCESS)
            {
                BSSAP_DEBUG(("ProcessUnequipCktInd: CIC modification "
                             "failed %d\n", key));
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessUnequipCktReq: invalid pcm %d timelsot %d"
                         "nwId %d\n", pcm, cicTs, nwId));

            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                         BSSAP_MSG_UNEQUIPPED_CKT, pcm, cicTs);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessUnequipCktReq: CIC ie not found\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }

    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST); 

    if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1; 

        range += startTS;
 
        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;

            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts - startTS); 

            if (flag && (cicTs != ts))
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
                BSSAP_DEBUG(("ProcessUnequipCktReq: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));
                                                                                                                                              
                crec = cicdb.FetchCICRecord(key);
                if (crec)
                {
                    if (crec->timerId)
                    {
                        // Cancel running timer if any
                        BSSAP_Timer t1(BSSAP_T_21);
                                                                                                                                              
                        t1.CancelUDTTimer(crec->timerId);
                        crec->timerId = 0;
                    }
                                                                                                                                              
                    crec->localState = CIC_ST_BLOCK;
                                                                                                                                              
                    ret = cicdb.ModifyCICRecord(key, crec);

                    if (ret != ITS_SUCCESS)
                    {
                        BSSAP_DEBUG(("ProcessUnequipCktInd: CIC modification "
                                     "failed %d\n", key));
                    }
                }
                else
                {
                    BSSAP_ERROR(("ProcessUnequipCktReq: invalid pcm %d "
                                  "timelsot %d nwId %d\n", pcm, ts, nwId));
                    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, 
                                             BSSAP_ECICNOTFOUND,
                                             BSSAP_MSG_CKT_GROUP_BLOCK, 
                                             pcm, ts);
                }
            }
        } 
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       update cic records in the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic records updated successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCktGroupBlkReq(BSSAP_Message* mMap,
                                 ITS_OCTET* buff,
                                 ITS_INT len,
                                 ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    ITS_OCTET  startTS = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupBlkReq\n"));
                                                                                                                                              
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
    } 
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkReq: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST); 
    if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1; 
        range += startTS;

        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;

            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts - startTS); 

            if (flag)
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
                BSSAP_DEBUG(("ProcessCktGroupBlkReq: pcm %d slot %d "
                                               "nwId %d\n", pcm, ts, nwId));

                crec = cicdb.FetchCICRecord(key);
                if (crec)
                {
                    crec->localState = CIC_ST_BLOCK;

                    ret = cicdb.ModifyCICRecord(key, crec);
                    if (ret != ITS_SUCCESS)
                    {
                        BSSAP_DEBUG(("ProcessCktGroupBlkReq: CIC Modify "
                                     "failed %d\n", key));
                    }
                }
                else
                {
                    BSSAP_ERROR(("ProcessCktGroupBlkReq: invalid pcm %d "
                                  "timelsot %di nwId %d\n", pcm, ts, nwId));

                    // Since MSC is master, it shall not send BLOCK
                    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, 
                                             BSSAP_ECICNOTFOUND,
                                             BSSAP_MSG_CKT_GROUP_BLOCK, 
                                             pcm, ts);
                }
            }
        } 
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupBlkReq: CIC LIST ie not found\n"));

        return (!ITS_SUCCESS);
    }

    // Since MSC is master, it shall not send GRP-BLOCK

    return (BSSAP_EMSCMASTER);
}

/*implementation:internal
*
* PURPOSE:
*       update cic records in the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic records updated successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCktGroupUnblkReq(BSSAP_Message* mMap,
                                   ITS_OCTET* buff,
                                   ITS_INT len,
                                   ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    ITS_OCTET  startTS = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupUnblkReq\n"));
                                                                                                                                              
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkReq: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST); 
    if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1; 
        range += startTS;

        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;

            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts - startTS); 

            if (flag)
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
                BSSAP_DEBUG(("ProcessCktGroupUnblkReq: pcm %d slot %d "
                                                "nwId %d\n", pcm, ts, nwId));

                crec = cicdb.FetchCICRecord(key);
                if (crec)
                {
                    crec->localState = CIC_ST_UNBLK;

                    ret = cicdb.ModifyCICRecord(key, crec);
                    if (ret != ITS_SUCCESS)
                    {
                        BSSAP_DEBUG(("ProcessCktGroupUnblkReq: CIC Modify "
                                                         "failed %d\n", key));
                    }
                }
                else
                {
                    BSSAP_ERROR(("ProcessCktGroupUnblkReq: invalid pcm %d "
                                  "timelsot %di nwId %d\n", pcm, ts, nwId));

                    // Since MSC is master, it shall not send BLOCK
                    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, 
                                             BSSAP_ECICNOTFOUND,
                                             BSSAP_MSG_CKT_GRP_UNBLOCK, 
                                             pcm, ts);
                }
            }
        } 
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkReq: CIC LIST ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (BSSAP_EMSCMASTER);
}

/*implementation:internal
*
* PURPOSE:
*       processing incoming reset circuit message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record found successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0590,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetCktInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessResetCktInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessResetCktInd: pcm %d slot %d nwId %d\n",
                                                 pcm, ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(BSSAP_T_21);
                                                                                                                                              
                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;
            }
            crec->callState = CALL_ST_IDLE;
            crec->localState = CIC_ST_UNBLK;
            crec->remoteState = CIC_ST_UNBLK;
            ret = cicdb.ModifyCICRecord(key, crec);
        }
        else 
        {
            BSSAP_ERROR(("ProcessResetCktInd: invalid pcm %d ts %d nwId %d\n",
                                                               pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                         BSSAP_MSG_RESET_CIRCUIT, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessResetCktInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifying cic record for incomig reset circuit ack message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetCktAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessResetCktAckInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessResetCktAckInd: pcm %d slot %d nwId %d\n",
                                                       pcm, ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->timerId)
            {
                BSSAP_Timer t(BSSAP_T_12);

                t.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;

                ret = cicdb.ModifyCICRecord(key, crec);

                return (ret);
            }
            else
            {
                if (mMap->GetMsgType() == BSSAP_MSG_RESET_CIRCUIT_ACK)
                {
                    BSSAP_ERROR(("ProcessResetCktAckInd: Reset Ckt. Ack 
                                                  indication for idle cic\n")); 
                    return (!ITS_SUCCESS);
                }
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessResetCktAckInd: invalid pcm %d"
                                        " ts %d nwId %d\n", pcm, ts, nwId));

            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                         BSSAP_MSG_RESET_CIRCUIT_ACK, pcm, ts);

            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessResetCktAckInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       removing cic record by receiving unequipment circuit message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record removed successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  28-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0620,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessUnequipCktInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0, range = 0;
    ITS_OCTET  ts = 0, cicTs = 0, flag = 0;
    ITS_OCTET  startTS = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Interface bssIf;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessUnequipCktInd\n"));
                                                                                                                                              
    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        cicTs = startTS = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & cicTs));
                                                                                                                                              
        BSSAP_DEBUG(("ProcessUnequipCktInd: pcm %d slot %d nwId %d\n",
                                          pcm, cicTs, nwId));
                                                                                                                                              
        crec = cicdb.FetchCICRecord(key);
        if (crec && crec->timerId)
        {
            // Cancel running timer if any
            BSSAP_Timer t1(BSSAP_T_21);
                                                                                                                                              
            t1.CancelUDTTimer(crec->timerId);
            crec->timerId = 0;  
        }

        crec->localState = CIC_ST_BLOCK;

        ret = cicdb.ModifyCICRecord(key, crec);
    } 
    else
    {
        BSSAP_ERROR(("ProcessUnequipCktInd: CIC ie not found\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }
                                                                                                                                              
    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST); 

    if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1; 

        range += startTS;

        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;

            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts - startTS); 

            if (flag && (cicTs != ts))
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
                BSSAP_DEBUG(("ProcessUnequipCktInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));
                                                                                                                                              
                crec = cicdb.FetchCICRecord(key);
                if (crec)
                {
                    if (crec->timerId)
                    {
                        // Cancel running timer if any
                        BSSAP_Timer t1(BSSAP_T_21);
                                                                                                                                              
                        t1.CancelUDTTimer(crec->timerId);
                        crec->timerId = 0; 
                    }

                    crec->localState = CIC_ST_BLOCK;

                    ret = cicdb.ModifyCICRecord(key, crec);
                    if (ret != ITS_SUCCESS)
                    {
                        BSSAP_DEBUG(("ProcessUnequipCktInd: CIC modification "
                                     "failed %d\n", key));
                    }
                }
                else
                {
                    BSSAP_ERROR(("ProcessUnequipCktInd: invalid pcm %d "
                                  "timelsot %d nwId %d\n", pcm, ts, nwId));
                    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, 
                                             BSSAP_ECICNOTFOUND,
                                             BSSAP_MSG_CKT_GROUP_BLOCK, 
                                             pcm, ts);
                }
            }
        } 
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       cancel timer by receiving reset ack message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer canceled successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0560,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = 0;
   
    BSSAP_DEBUG(("BSSAP_Map: ProcessResetAckInd\n"));

    BSSAP_Timer t(BSSAP_T_16);

    if (rData.timerId)  
    {
        ret = t.CancelUDTTimer(rData.timerId);

        rData.timerId = 0;   
    }
    else
    {
        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       start timer by receving reset message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer started successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0570,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessResetInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = 0;
    rData.timerId = 0;
  
    BSSAP_DEBUG(("BSSAP_Map: ProcessResetInd\n"));

    BSSAP_Timer t(BSSAP_T_2);

    rData.timerId = t.StartUDTTimer(0, 0, BSSAP_MSG_RESET, 0, 0, nwId);

    if (rData.timerId == ITS_ETIMERSTARTFAIL)
    {
        return (!ITS_SUCCESS);
    }

    DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT,
                     NULL, NULL, SetAllCIC);
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       start timer by receving overload message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer started successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0490,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessOverloadInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
 
    BSSAP_DEBUG(("BSSAP_Map: ProcessOverloadInd\n"));

    if (isFirst)
    {
        BSSAP_Timer t5(BSSAP_T_5);
        BSSAP_Timer t6(BSSAP_T_6);

        oData.timerId5 = t5.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD, 
                                               0, 0, nwId);
        oData.timerId6 = t6.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD, 
                                               0, 0, nwId);

        if (oData.timerId5 == ITS_ETIMERSTARTFAIL || 
                oData.timerId6 == ITS_ETIMERSTARTFAIL)
        {
            ret = (!ITS_SUCCESS);
        }

        isFirst = ITS_FALSE;
    }
    else
    {
        // T5 still runing so ignore overload
        if ((oData.timerId6) && (oData.timerId5))
        {
            BSSAP_WARNING(("ProcessOverloadInd: Ignoring the Overload Ind\n"));

            delete mMap;

            ret = (!ITS_SUCCESS);
        }
        // T5 stopped and T6 running so lets pass the Overload
        else if ((!oData.timerId5) && (oData.timerId6))
        {
            BSSAP_Timer t6(BSSAP_T_6);
            BSSAP_Timer t5(BSSAP_T_5);

            oData.timerId5 = t5.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD,
                                                   0, 0, nwId);
            ret = t6.CancelUDTTimer(oData.timerId6);
            oData.timerId6 = t6.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD, 
                                                   0, 0, nwId);
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       update cic records in the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic records updated successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCktGroupBlkInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    ITS_OCTET  startTS = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupBlkInd\n"));
                                                                                                                                              
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
                                                                                                                                              
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(BSSAP_T_21);
                                                                                                                                              
                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;

                ret = cicdb.ModifyCICRecord(key, crec);
                if (ret != ITS_SUCCESS)
                {
                    BSSAP_DEBUG(("ProcessCktGroupBlkInd:CIC Modify failed %d\n",
                                                key));
                    return (ret);
                }
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessCktGroupBlkInd: invalid pcm %d ts %d nwId %d\n"
                                                              , pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                      BSSAP_MSG_CKT_GROUP_BLOCK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
                                                                                                                                              
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupBlkInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }
                                                                                                                                              
    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST); 
    if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1; 
        range += startTS;

        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;

            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts - startTS); 

            if (flag)
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
                BSSAP_DEBUG(("ProcessCktGroupBlkInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));
                                                                                                                                              
                crec = cicdb.FetchCICRecord(key);
                if (crec)
                {
                    if (crec->remoteState != CIC_ST_BLOCK)
                    {
                        crec->remoteState = CIC_ST_BLOCK;

                        ret = cicdb.ModifyCICRecord(key, crec);
                        if (ret != ITS_SUCCESS)
                        {
                            BSSAP_DEBUG(("ProcessCktGroupBlkInd: CIC Modify "
                                         "failed %d\n", key));
                        }
                    }
                    else
                    {
                        BSSAP_ERROR(("ProcessCktGroupBlkInd: cic " 
                                     "already block\n"));
                                                                                                                                              
                        // Send Ckt Group Block Ack for already block cic
                        ret = err.SendCktGroupBlkAck(mMap, pcm, ts, nwId);

                        //  we are not returning back from here.. bcos more 
                        //  cic's needs to be checked
                        //
                    }
                }
                else
                {
                    BSSAP_ERROR(("ProcessCktGroupBlkInd: invalid pcm %d "
                                 "ts %d nwId %d\n", pcm, ts, nwId));
                    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL,
                                             BSSAP_EUNEQUIPCKT,
                                             BSSAP_MSG_CKT_GROUP_BLOCK,
                                             pcm, ts);
                    err.SendUnEquipCkt(pcm, ts, nwId);
                }
            }
        } 
    } 
    else
    {
        BSSAP_ERROR(("ProcessCktGroupBlkInd: CIC LIST ie not found\n"));

        return (!ITS_SUCCESS);
    }
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       update cic records in the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic records updated successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCktGroupBlkAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupBlkAckInd\n"));
                                                                                                                                              
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
                                                                                                                                              
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->localState == CIC_ST_BLOCK)
            {
                if (crec->timerId)
                {
                    // Cancel running timer if any
                    BSSAP_Timer t1(BSSAP_T_22);
                                                                                                                                              
                    t1.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
                }
                else
                {
                    BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Ignore CktGroup "
                          "BlkAckInd for already block cic pcm %d ts %d "
                          "nwId %d\n", pcm, ts, nwId));
                    return (!ITS_SUCCESS);
                }
            }
            else
            {
                BSSAP_ERROR(("ProcessCktGroupBlkAckInd: BlockAck indicaton "
                                                    "for unblock cic\n"));
                return (ITS_SUCCESS);
            }

        }
        else
        {
            BSSAP_ERROR(("ProcessCktGroupBlkAckInd: invalid pcm %d "
                         "ts %d nwId %d\n", pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                           BSSAP_MSG_CKT_GRP_BLK_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
                                                                                                                                              
            return (!ITS_SUCCESS);
        }

        ret = cicdb.ModifyCICRecord(key, crec);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_DEBUG(("ProcessCktGroupBlkAckInd:CIC Modify "
                         "failed %d\n", key));
            return (ret);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupBlkAckInd: CIC ie not found\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       update cic records in the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic records updated successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCktGroupUnblkInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    ITS_OCTET  startTS = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupUnblkInd\n"));
                                                                                                                                              
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
                                                                                                                                              
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(BSSAP_T_21);
                                                                                                                                              
                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;

                ret = cicdb.ModifyCICRecord(key, crec);
                if (ret != ITS_SUCCESS)
                {
                    BSSAP_DEBUG(("ProcessCktGroupUnblkInd: CIC Modify "
                                 "failed %d\n", key));
                    return (ret);
                }
            }
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkInd: CIC ie not found\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }
                                                                                                                                              
    clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST); 
    if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1; 
        range += startTS;

        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;

            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts-startTS); 
            if (flag)
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
                BSSAP_DEBUG(("ProcessCktGroupUnblkInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));
                                                                                                                                              
                crec = cicdb.FetchCICRecord(key);
                if (crec)
                {
                    if (crec->remoteState != CIC_ST_UNBLK)
                    {
                        crec->remoteState = CIC_ST_UNBLK;

                        ret = cicdb.ModifyCICRecord(key, crec);
                        if (ret != ITS_SUCCESS)
                        {
                            BSSAP_DEBUG(("ProcessCktGroupUnblkInd: CIC Modify "
                                         "failed %d\n", key));
                        }
                    }
                    else
                    {
                        BSSAP_ERROR(("ProcessCktGroupUnblkInd: cic "
                                     "already unblock\n"));
                                                                                                                                              
                        // Send Ckt Group Unblock Ack for already block cic
                        ret = err.SendCktGroupUnblkAck(mMap, pcm, ts, nwId);
                                                                                                                                              
                        /*  we are not returning back from here.. bcos more 
                         *  cic's need to be checked
                         */
                    }
                }
                else
                {
                    BSSAP_ERROR(("ProcessCktGroupUnblkInd: invalid "
                                 "pcm %d ts %d nwId %d\n", pcm, ts, nwId));
                    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL,
                                             BSSAP_EUNEQUIPCKT,
                                             BSSAP_MSG_CKT_GRP_UNBLOCK,
                                             pcm, ts);
                    err.SendUnEquipCkt(pcm, ts, nwId);
                                                                                                                                              
                }
            }
        } 
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkInd: CIC LIST ie not found\n"));

        return (!ITS_SUCCESS);
    }
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       update cic records in the cic database 
* INPUT:
*       mMap, buff, len, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic records updated successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  26-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0580,
*                        ID :: D0620, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCktGroupUnblkAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupUnblkAckInd\n"));
                                                                                                                                              
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
                                                                                                                                              
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->localState != CIC_ST_BLOCK)
            {
                if (crec->timerId)
                {
                    // Cancel running timer if any
                    BSSAP_Timer t1(BSSAP_T_22);
                                                                                                                                              
                    t1.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
                }
                else
                {
                    BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: Ignore CktGroup "
                          "BlkAckInd for already idle cic pcm %d ts %d "
                          "nwId %d\n", pcm, ts, nwId));
                    return (!ITS_SUCCESS);
                }
            }
            else
            {
                BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: UnBlockAck indicaton "
                                                    "for block cic\n"));
                return (ITS_SUCCESS);
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: invalid pcm %d "
                         "ts %d nwId %d\n", pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                  BSSAP_MSG_CKT_GRP_UNBLKING_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
                                                                                                                                              
            return (!ITS_SUCCESS);
        }
                                                                                                                                              
        ret = cicdb.ModifyCICRecord(key, crec);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_DEBUG(("ProcessCktGroupUnblkAckInd:CIC Modify "
                         "failed %d\n", key));
            return (ret);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: CIC ie not found\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record receving block message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0520,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessBlockInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessBlockInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
 
        BSSAP_DEBUG(("ProcessBlockInd: BlockInd pcm %d ts %d nwId %d\n",
                                                         pcm, ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->remoteState == CIC_ST_BLOCK)
            {
                BSSAP_ERROR(("ProcessBlockInd: cic already block\n"));

                // Send Block Ack for already block cic
                ret = err.SendBlockAck(pcm, ts, nwId);    

                return (ITS_SUCCESS);
            }
            else //CIC_ST_UNBLOCK
            {
                if (crec->timerId)
                {
                    BSSAP_Timer t(BSSAP_T_12);

                    t.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
                }

                crec->remoteState = CIC_ST_BLOCK;
                ret = cicdb.ModifyCICRecord(key, crec);
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessBlockInd: invalid pcm %d ts %d nwId %d\n", 
                                                            pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                                     BSSAP_MSG_BLOCK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessBlockInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record receving unblock message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0540,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessUnBlockInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessUnBlockInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessUnBlockInd: UnBlockInd pcm %d slot %d nwId %d\n", 
                                                             pcm, ts, nwId));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->remoteState == CIC_ST_BLOCK)
            {
                crec->remoteState = CIC_ST_UNBLK;
                ret = cicdb.ModifyCICRecord(key, crec);
            }
            else
            {
                BSSAP_WARNING(("ProcessUnBlockInd: cic already unblock\n"));

                // Send UnBlock Ack for already unblock cic
                ret = err.SendUnBlockAck(pcm, ts, nwId);

                return (ITS_SUCCESS);
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessUnBlockInd: invalid pcm %d ts %d nwId %d\n",
                                                             pcm, ts, nwId));

            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                           BSSAP_MSG_UNBLOCK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessUnBlockInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record receving block ack message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0510,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessBlockAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessBlockAckInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessBlockAckInd: BlockAckInd pcm %d slot %d nwId %d\n", 
                                                                pcm, ts, nwId));
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->localState == CIC_ST_BLOCK)
            {
                if (crec->timerId)
                {
                    BSSAP_Timer t(BSSAP_T_21);

                    t.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
                    
                    ret = cicdb.ModifyCICRecord(key, crec);
                  
                    return (ret);
                }
                else
                {
                    BSSAP_ERROR(("ProcessBlockAckInd: Ignore BlockAckInd "
                         "for already block cic pcm %d ts %d nwId %d\n",
                          pcm, ts, nwId));
                    return (!ITS_SUCCESS);
                }
            }
            else
            {
                BSSAP_ERROR(("ProcessBlockAckInd: BlockAck indicaton "   
                                                    "for unblock cic\n"));
                // Now UnBlock message can be sent to remote
                crec->statusFlag = ITS_TRUE;

                ret = cicdb.ModifyCICRecord(key, crec);

                return (ret);
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessBlockAckInd: invalid pcm %d ts %d nwId %d\n",
                                                               pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                                  BSSAP_MSG_BLOCK_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessBlockAckInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record receving unblock ack message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0530,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessUnBlockAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessUnBlockAckInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        BSSAP_DEBUG(("ProcessUnBlockAckInd: UnBlockAckInd pcm %d slot %d nwId %d\n",
                                                                 pcm, ts, nwId));
        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->localState == CIC_ST_BLOCK)
            {
                BSSAP_ERROR(("ProcessUnBlockAckInd: UnBlockAck for already "
                                                               "block cic\n"));
                // Now Block message can be sent to remote
                crec->statusFlag = ITS_TRUE;

                ret = cicdb.ModifyCICRecord(key, crec);

                return (ret);
            }
            else
            {
                if (crec->timerId)
                {
                    BSSAP_Timer t(BSSAP_T_21);

                    t.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;

                    ret = cicdb.ModifyCICRecord(key, crec);

                    return (ret);
                }
                else
                {
                    BSSAP_ERROR(("ProcessUnBlockAckInd: Ignore UnBlockAckInd "
                         "for already unblock cic pcm %d ts %d nwId %d\n",
                          pcm, ts, nwId));

                    return (!ITS_SUCCESS);
                }
            }
        }
        else
        {
            BSSAP_ERROR(("ProcessUnBlockAckInd: invalid pcm %d ts %d nwId %d\n",
                                                                pcm, ts, nwId));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                                BSSAP_MSG_UNBLOCK_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessUnBlockAckInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       None
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessClearComplete(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = !ITS_SUCCESS;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Map: ProcessClearComplete\n"));

    // Don't wait for app. to terminate connection
    hndl.SendRLSD(call->GetSLR());

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing call state by receving clear command message 
* INPUT:
*       mMap, nwid 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0600,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessClearCommand(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;

    BSSAP_DEBUG(("BSSAP_Map: ProcessClearCommand\n"));

    cic = call->GetCIC();

    if (cic)
    {
        crec = cicdb.FetchCICRecord(cic);
        if (crec)
        {
            // By this we know clearly channel is released
            call->SetChannelAlloc(ITS_FALSE);

            crec->callState = CALL_ST_IDLE;
            ret = cicdb.ModifyCICRecord(cic, crec);
        }
    }
 
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record by sending assign req message 
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0610,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessAssignmentRequest(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    ITS_UINT nwId = 0;
    ITS_OCTET cause;
    BSSAP_CicDB cicdb;
    CICData* crec;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessAssignmentRequest\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        nwId = call->GetBssId();

        BSSAP_DEBUG(("ProcessAssignmentRequest: pcm %d ts %d nwId %d\n", 
                          pcm, ts, nwId));
 
        key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            if (crec->callState == CALL_ST_BUSY)
            {
                BSSAP_ERROR(("ProcessAssignmentRequest: CALL in BUSY state "
                               "pcm %d timeslot %d nwId %d\n", pcm ,ts, nwId));
            }
            else if ((crec->localState == CIC_ST_UNBLK))
            {
                crec->callState = CALL_ST_BUSY;

                cicdb.ModifyCICRecord(key, crec);
                call->SetCIC(key);

                return (ITS_SUCCESS);
            }
            else // CIC_ST_BLOCK
            {
                BSSAP_ERROR(("ProcessAssignmentRequest: CIC in BLK state "
                                         "pcm %d timeslot %d\n", pcm ,ts));
            }

            //Send Assignment fail (CIC already assigned/block)
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,
                                      BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);

            return (!ITS_SUCCESS);
        }
        else
        {
            BSSAP_ERROR(("ProcessAssignmentRequest: CIC pool mismatch "
                            "pcm %d timeslot %d\n", pcm ,ts));

            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                         BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, call->GetBssId());

            return (!ITS_SUCCESS);
        }
    }

    return (ITS_SUCCESS);  
}

/*implementation:internal
*
* PURPOSE:
*       processing assign complete message 
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record found successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0610,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessAssignmentComplete(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessAssignmentComplete\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();

        BSSAP_DEBUG(("ProcessAssignmentComplete: pcm %d ts %d\n", pcm ,ts));

        key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));

        crec = cicdb.FetchCICRecord(key);
        if (!crec)
        {
            BSSAP_ERROR(("ProcessAssignmentComplete: CIC pool mismatch "
                            "pcm %d timeslot %d\n", pcm ,ts));
        }
        else
        {
            // By this response we know clearly channel is getting alloted 
            call->SetChannelAlloc(ITS_TRUE);
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       None
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       Success 
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessHandoverRequired(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverRequired\n"));

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Enabling handover call. 
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessHandoverCommand(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverCommand\n"));

    call->SetHandOver(ITS_TRUE);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*      sending handover request as CR 
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Not Success 
* COMMENTS:
*       don't return success. it prevents to resend data as DT1 or CR. 
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessHandoverRequest(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    const BSSAP_Element* ie = NULL;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverRequest\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
                                                                                                                                              
    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
                                                                                                                                              
        key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));
                                                                                                                                              
        crec = cicdb.FetchCICRecord(key);
        if (!crec)
        {
            BSSAP_ERROR(("ProcessHandoverRequest: CIC pool mismatch "
                            "pcm %d timeslot %d\n", pcm ,ts));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                        BSSAP_MSG_HANDOVER_REQUEST, pcm, ts);
            return (!ITS_SUCCESS);
        }  
    }

    ret = hndl.SendCR(call);

    if (ret == ITS_SUCCESS)
    {
       BSSAP_DEBUG(("ProcessHandoverRequest: Send CR \n"));
    }

    return (!ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       Disabling handover call. 
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessHandoverFailure(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverFailure\n"));

    call->SetHandOver(ITS_FALSE);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record by processing handover req ack msg 
* INPUT:
*       mmap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0630,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessHandoverReqAck(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    const BSSAP_Element* ie = NULL;

    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverReqAck\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();

        key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));

        crec = cicdb.FetchCICRecord(key);
        if (crec)
        {
            cicdb.ModifyCICRecord(key, crec);
            call->SetCIC(key);
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       modifing cic record by processing handover complete msg
* INPUT:
*       mmap, call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessHandoverComplete(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverComplete\n"));
                                                                                                                                              
    cic = call->GetCIC();
                                                                                                                                              
    if (cic)
    {
        crec = cicdb.FetchCICRecord(cic);
        if (crec)
        {
            crec->callState = CALL_ST_BUSY;
            ret = cicdb.ModifyCICRecord(cic, crec);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessHandoverComplete: No cic found\n"));
                                                                                                                                              
        return (!ITS_SUCCESS);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       changing call state to IDLE, and update cic record  
* INPUT:
*       mmap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if cic record modified successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0480, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessAssignmentFail(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;

    BSSAP_DEBUG(("BSSAP_Map: ProcessAssignmentFail\n"));

    cic = call->GetCIC();

    if (cic)
    {
        crec = cicdb.FetchCICRecord(cic);
        if (crec)
        {
            crec->callState = CALL_ST_IDLE;
            ret = cicdb.ModifyCICRecord(cic, crec);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessAssignmentFail: No cic found\n"));

        return (!ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing UDT procedures  
* INPUT:
*       mmap, nwId, toApp 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if msg sent successfully to app/BSS
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0450, ID :: D0480,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessUDTMapProcedures(BSSAP_Message* mMap, ITS_OCTET nwId,
                                   ITS_BOOLEAN toAPP)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    ITS_OCTET mType;
    BSSAP_Interface bssIf;
    BSSAP_SCCPHandler hndl;

    mType = mMap->GetMsgType();

    BSSAP_DEBUG(("BSSAP_Map: ProcessUDTMapProcedures\n"));

    // BSS -> MSC
    if (toAPP)
    {
        switch (mType)
        {
            case BSSAP_MSG_BLOCK:
                ret = ProcessBlockInd(mMap, nwId);
            break;

            case BSSAP_MSG_BLOCK_ACK:
                ret = ProcessBlockAckInd(mMap, nwId);
            break;

            case BSSAP_MSG_UNBLOCK:
                ret = ProcessUnBlockInd(mMap, nwId);
            break;

            case BSSAP_MSG_UNBLOCK_ACK:
                ret = ProcessUnBlockAckInd(mMap, nwId);
            break;

            case BSSAP_MSG_RESET_ACK:
                ret = ProcessResetAckInd(mMap, nwId);
            break;

            case BSSAP_MSG_RESET:
                ret = ProcessResetInd(mMap, nwId);
            break;

            case BSSAP_MSG_RESET_CIRCUIT:
                ret = ProcessResetCktInd(mMap, nwId);
            break;

            case BSSAP_MSG_RESET_CIRCUIT_ACK:
                ret = ProcessResetCktAckInd(mMap, nwId);
            break;

            case BSSAP_MSG_UNEQUIPPED_CKT:
                ret = ProcessUnequipCktInd(mMap, nwId);
            break;

            case BSSAP_MSG_OVERLOAD:
                ret = ProcessOverloadInd(mMap, nwId);
            break;

            case BSSAP_MSG_CKT_GROUP_BLOCK:
                ret = ProcessCktGroupBlkInd(mMap, nwId);
            break;

            case BSSAP_MSG_CKT_GRP_BLK_ACK:
                ret = ProcessCktGroupBlkAckInd(mMap, nwId);
            break;

            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                ret = ProcessCktGroupUnblkInd(mMap, nwId);
            break;

            case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                ret = ProcessCktGroupUnblkAckInd(mMap, nwId);
            break;

            case BSSAP_MSG_CONFUSION:
                PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CONF_RECV);
            break;
        }
    }
    else
    { 
        if (BSSAP_Message::Encode(buff, len, mMap) != ITS_SUCCESS)
        {
            BSSAP_ERROR(("ProcessUDTMapProcedures: BSSMAP Encode fail\n"));
                                                                                                                                              
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EENCODE);
                                                                                                                                              
            delete mMap;
                                                                                                                                              
            return (ITS_SUCCESS);
        }

        // MSC -> BSS
        switch (mType)
        {
            case BSSAP_MSG_BLOCK:
               ret = ProcessBlockReq(mMap, buff, len, nwId);
            break;

            case BSSAP_MSG_UNBLOCK:
                ret = ProcessUnBlockReq(mMap, buff, len, nwId);
            break;

            case BSSAP_MSG_RESET:
                ret = ProcessResetReq(mMap, buff, len, nwId);
            break;

            case BSSAP_MSG_RESET_ACK:
                ret = ITS_SUCCESS; 
            break;

            case BSSAP_MSG_RESET_CIRCUIT:
                ret = ProcessResetCktReq(mMap, buff, len, nwId);
            break;
   
            case BSSAP_MSG_UNEQUIPPED_CKT:
                ret = ProcessUnequipCktReq(mMap, buff, len, nwId);
            break;

            case BSSAP_MSG_CKT_GROUP_BLOCK:
                ret = ProcessCktGroupBlkReq(mMap, buff, len, nwId);
            break;

            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                ret = ProcessCktGroupUnblkReq(mMap, buff, len, nwId);
            break;
        }

        if ((ret == ITS_SUCCESS))
        {
            hndl.BSSAP_ProcessAPPdata(buff, len, nwId);
        }
    }

    // Block/Un-Block messges should not be semd from MSC
    if (ret == BSSAP_EMSCMASTER)
    {
        return (ITS_SUCCESS);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing CO map procedures 
* INPUT:
*       mMap, call object, callrefId, toApp 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if msg sent successfully to app/BSS
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0450, ID :: D0490,
*                        ID :: D0480, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessCOMapProcedures(BSSAP_Message* mMap, 
                                  BSSAP_Call* call,
                                  ITS_CTXT callrefId, 
                                  ITS_BOOLEAN toAPP)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    ITS_OCTET mType = 0;
    ITS_OCTET pvType = 0;
    ITS_OCTET callType = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;


    BSSAP_DEBUG(("BSSAP_Map: ProcessCOMapProcedures\n"));

    callType = call->GetCallType();

    if (callType != MO_CALL && callType != MT_CALL && callType != HO_CALL && 
        callType != LU_CALL)
    {
        BSSAP_ERROR(("ProcessCOMapProcedures: BSS-MAP procedure w/o call "
                     ": %02x \n", callType));

        return (!ITS_SUCCESS);
    }

    mType = mMap->GetMsgType();
    pvType = call->GetMssgType();

    // App -> BSS
    if (!toAPP)
    {
        if (BSSAP_Message::Encode(buff, len, mMap) != ITS_SUCCESS)
        {
            BSSAP_ERROR(("ProcessCOMapProcedures: BSSMAP Encode fail\n"));

            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EENCODE);

            delete mMap;

            return (ITS_SUCCESS);
        }

        switch (mType)
        {
            case BSSAP_MSG_ASSIGN_REQUEST:
                ret = ProcessAssignmentRequest(mMap, call);
            break;

            case BSSAP_MSG_CLEAR_COMMAND:
                ret = ProcessClearCommand(mMap, call);
            break;

            case BSSAP_MSG_HANDOVER_REQUEST:
                ret = ProcessHandoverRequest(mMap, call);
            break;

            case BSSAP_MSG_HANDOVER_COMMAND:
                ret = ProcessHandoverCommand(mMap, call);
            break;
        }

        if (ret == ITS_SUCCESS)
        {
            call->SetBSSAPData(buff, len);

            ret = hndl.BSSAP_ProcessAPPdata(call);
        }

        if (mMap)
        {
            delete mMap;
        }
    }
    else
    {   
        // BSS -> App

        switch (mType)
        {
            case BSSAP_MSG_ASSIGN_COMPLETE:
                if (pvType != BSSAP_MSG_ASSIGN_REQUEST)
                {
                    ret =  (!ITS_SUCCESS);
                    break;
                }
                ret = ProcessAssignmentComplete(mMap, call);
            break;

            case BSSAP_MSG_ASSIGN_FAILURE:
                if (pvType != BSSAP_MSG_ASSIGN_REQUEST)
                {
                    ret = (!ITS_SUCCESS);
                    break;
                }
                ret = ProcessAssignmentFail(mMap, call);
            break;

            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
            case BSSAP_MSG_CIPHER_MODE_REJECT:
                if (pvType != BSSAP_MSG_CIPHER_MODE_CMD)
                {
                    ret = (!ITS_SUCCESS);
                    break;
                }
                // Now TMSI Reallocation Command can send
                call->SetTmsiReallocCmd(ITS_TRUE); 
            break;

            case BSSAP_MSG_PERFORM_LOCACTION_RESPONSE:
                if (pvType != BSSAP_MSG_PERFORM_LOCACTION_REQUEST)
                {
                    ret = (!ITS_SUCCESS);
                }
            break;

            case BSSAP_MSG_CLEAR_COMPLETE:
                ret = ProcessClearComplete(mMap, call);
            break;

            case BSSAP_MSG_HANDOVER_REQUIRED:
                ret = ProcessHandoverRequired(mMap, call);
            break;

            case BSSAP_MSG_HANDOVER_FAILURE:
                ret = ProcessHandoverFailure(mMap, call);
            break;

            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
                ret = ProcessHandoverReqAck(mMap, call);
            break;

	    case BSSAP_MSG_HANDOVER_COMPLETE:
                ret = ProcessHandoverComplete(mMap, call);
                call->SetCallType(MT_CALL);
                call->SetCurrentEvent(BSSAP_MSG_HANDOVER_COMPLETE);
            break;

            case BSSAP_MSG_CONFUSION:
                 PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CONF_RECV); 
            break;
        }
    }

    if (ret == ITS_SUCCESS)
    {
        call->SetMssgType(mType);

        BSSAP_CallDB::GetShared().Add(call);
    }


    return (ret);
}

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
*                        ID :: D0920
*/
void
BSSAP_Map::Initialize()
{
    BSSAP_DEBUG(("BSSAP_Map: Initialize()\n"));
 
    mlock = new Mutex(0);
}

/*implementation:internal
*
* PURPOSE:
*       processing outgoing msgs from MSC application 
* INPUT:
*       mMap 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if msg sent successfully to BSS
*       Error, if problem occurs
* COMMENTS:
*       This function handle seperatly for CO & CL msgs
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0470, ID :: D0490,
*                        ID :: D0450, ID :: D0920
*/
ITS_INT 
BSSAP_Map::ProcessOutBSSMAPMessage(BSSAP_Api* mMap)
{
    ITS_INT ret;
    ITS_CTXT ref = 0;
    ITS_OCTET mType = 0;
    BSSAP_Call* call = NULL;

    BSSAP_DEBUG(("BSSAP_Map: ProcessOutBSSMAPMessage\n"));

    mType = mMap->GetMssgType();

    if (!IsUDT(mType))
    {
        // Send as CO
        ref = mMap->GetCallRef();
      
        BSSAP_DEBUG(("ProcessOutBSSMAPMessage : Sending CO MAP %d\n",
                                                       mMap->GetMssgType()));
        call = BSSAP_CallDB::GetShared().Fetch(ref);
        if (call)
        {
            call->SetBssId(mMap->GetBssId());

            ret = ProcessCOMapProcedures(mMap->GetBSSAPdata(), call, 
                                            ref, ITS_FALSE);
        }
        else
        {
            return (!ITS_SUCCESS);
        }
    }
    else
    {
        // Send as UDT 
        BSSAP_DEBUG(("ProcessOutBSSMAPMessage : Sending (UDT) BSSMAP %d\n", 
                                                         mMap->GetMssgType()));

        ret = ProcessUDTMapProcedures(mMap->GetBSSAPdata(), mMap->GetBssId(), 
                                                                    ITS_FALSE);

    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing incoming CO MAP msgs from BSS 
* INPUT:
*       mMap, call object 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if msg sent successfully to app 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0470, ID :: D0450,
*                        ID :: D0490, ID :: D0920
*/
ITS_INT
BSSAP_Map::ProcessInBSSMAPMessage(BSSAP_Call* call, BSSAP_Message* mMap)
{
    ITS_INT ret = 0;
    ITS_OCTET mType = 0;
    BSSAP_Error err;
    BSSAP_Interface intface;

    BSSAP_DEBUG(("BSSAP_Map: ProcessInBSSMAPMessage\n"));

    mType = mMap->GetMsgType(); 
    

    if (IsUDT(mType) && (mType != BSSAP_MSG_CONFUSION))
    {
       BSSAP_ERROR(("ProcessInBSSMAPMessage: Recv. UDT MAP as CO\n"));

       ret = err.SendConfunsion(call, C_PROTOCOL_ERROR, 0, NULL, 0);

       return (ret);
    }

    ret = ProcessCOMapProcedures(mMap, call, call->GetSLR(), ITS_TRUE);   

    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }
   
    intface.DispatchMsgToApp(call, mMap);
    
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing incoming CL MAP msgs from BSS 
* INPUT:
*       msg, nwId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if msg sent successfully to app
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0470, ID :: D0450,
*                        ID :: D0490
*/
ITS_INT
BSSAP_Map::ProcessInBSSMAPUDTMessage(BSSAP_Message* msg, ITS_OCTET nwId)
{
    ITS_INT ret;
    BSSAP_Interface intface;
    BSSAP_Error err;

    BSSAP_DEBUG(("BSSAP_Map: ProcessInBSSMAPUDTMessage\n"));

    if (IsUDT(msg->GetMsgType()))
    {
        ret = ProcessUDTMapProcedures(msg, nwId, ITS_TRUE);

        if (ret == ITS_SUCCESS)
        {
            intface.DispatchMapUDTtoApp(msg, nwId);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessInBSSMAPUDTMessage: Recv. CO MAP as UDT\n"));

        ret = err.SendConfunsion(NULL, C_PROTOCOL_ERROR, nwId, NULL, 0);
    }

    return (ret);
}
