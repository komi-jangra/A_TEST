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
 *  ID: $Id: bssap_cfgdb.cpp,v 1.3 2008-02-01 04:20:26 amaresh.prasad Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.2  2008/01/02 09:05:07  bsccs2
 * LOG: Added the code for "Send the NACK for already configured  BSC id"
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/06 08:31:13  adutta
 * LOG: Taken care of network Id
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 ****************************************************************************/

#include <bssap_cfgdb.h>
#include <bssap-alarm.h> //25-01-08 by Amaresh

#ifdef NO_REDUNDACY
/*For LOCAL PATCH*/
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
#endif

ITS_UINT alarmrpc;
ITS_OCTET glb_bscId;
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0860, ID :: D0870,
*                        ID :: D0890, ID :: D1060
*/
ITS_INT
BSSAP_CfgDB::AddCfg(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc, 
                    ITS_OCTET lssn, ITS_OCTET rssn)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* fptr;
    CFGData* fptr1;

    glb_bscId = bscId;
    
/*Modification Start by Amaresh as on dated 26-08-14 */
    AddCfgLocal(bscId,lpc,rpc,lssn,rssn);
/*Modification Stop by Amaresh as on dated 26-08-14 */

    BSSAP_DEBUG(("BSSAP_CfgDB: AddCfg\n"));

    alarmrpc = rpc;
    BSSAP_DEBUG(("BSSAP_CfgDB: AddCfg RPC value %d\n", alarmrpc));
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
        if(fptr)
        {
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
    }
    else
    {
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

        BSSAP_WARNING(("AddCfg: Config data alread exists BssId %d\n", bscId));

       //    return (error);
       // return (!ITS_SUCCESS);
        return (ITS_EDUPLENTRY);
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
        if(fptr1)
        {
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
	       BSSAP_Alarm_CCITT(5129,__FILE__,__LINE__,"DPC %d",rpc);
               BSSAP_ERROR(("AddCfg: Couldn't add config data rpc %d\n", rpc));
               return (error);
           }
           else
           {
            BSSAP_DEBUG(("AddCfg: Added config data rpc %d\n", rpc));
           }
        }
    }
    else
    {
         error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&rpc,
                           sizeof(ITS_UINT),
                           fptr1);
           if (error != ITS_SUCCESS)
           {
                BSSAP_Alarm_CCITT(5129,__FILE__,__LINE__,"DPC %d",rpc);
                BSSAP_ERROR(("AddCfg: Couldn't add config data rpc %d\n", rpc));
                return (error);
           }

         BSSAP_WARNING(("AddCfg: Config data alread exists rpc %d\n", rpc));
       // return (error);
        return (!ITS_SUCCESS);
    }

    return (error);
}



/*implementation:internal
*
* PURPOSE:
*       Adding configuration data in Local to RPC LIST or NWID LIST table
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
* Amaresh Prasad				 26-08-2014
*/

ITS_INT
BSSAP_CfgDB::AddCfgLocal(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc, 
                    ITS_OCTET lssn, ITS_OCTET rssn)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* fptr;
    CFGData* fptr1;

    BSSAP_DEBUG(("BSSAP_CfgDBLocal: AddCfg\n"));

    alarmrpc = rpc;
    BSSAP_DEBUG(("BSSAP_CfgDBLocal: AddCfg RPC value %d\n", alarmrpc));
    fptr = (CFGData *)DSM_FindLocal(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_RPC_LIST,
                               (ITS_OCTET *)&bscId,
                               sizeof(ITS_OCTET), 
                               &error);

    if (error == ITS_ENOTFOUND)
    {
        fptr = (CFGData*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                    DSM_TABLE_BSSAP_RPC_LIST,
                                    (ITS_OCTET *)&bscId,
                                    sizeof(ITS_OCTET),
                                    sizeof(CFGData),
                                    &error);
        if(fptr)
        {
          fptr->lpc = lpc;
          fptr->rpc = rpc;
          fptr->lssn = lssn;
          fptr->rssn = rssn;
          fptr->Id = bscId;

          error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET), 
                           fptr);
          if (error != ITS_SUCCESS)
          {
            BSSAP_ERROR(("AddCfgLocal: Couldn't add config data BssId %d\n", bscId));

            return (error);
          }
          else
          {
            BSSAP_DEBUG(("AddCfgLocal: Added config data BssId %d\n", bscId));
          }
        }
    }
    else
    {
           error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET),
                           fptr);
          if (error != ITS_SUCCESS)
          {
            BSSAP_ERROR(("AddCfgLocal: Couldn't add config data BssId %d\n", bscId));
            return (error);
          }

        BSSAP_WARNING(("AddCfgLocal: Config data alread exists BssId %d\n", bscId));
        return (!ITS_SUCCESS);
    }

    //Point code -> BSS/MSC ID mapping
    fptr1 = (CFGData *)DSM_FindLocal(DSM_SccpFtGroupId,
                                DSM_TABLE_BSSAP_NWID_LIST,
                                (ITS_OCTET *)&rpc,
                                sizeof(ITS_UINT),
                                &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr1 = (CFGData*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                     DSM_TABLE_BSSAP_NWID_LIST,
                                     (ITS_OCTET *)&rpc,
                                     sizeof(ITS_UINT),
                                     sizeof(CFGData),
                                     &error);
        if(fptr1)
        {
           fptr1->Id = bscId;
           fptr1->lpc = lpc;
           fptr1->rpc = rpc;
           fptr1->lssn = lssn;
           fptr1->rssn = rssn;

           error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&rpc,
                           sizeof(ITS_UINT),
                           fptr1);
           if (error != ITS_SUCCESS)
           {
	  			/*     BSSAP_Alarm_CCITT(5129,__FILE__,__LINE__,"DPC %d",rpc);*/
               BSSAP_ERROR(("AddCfgLocal: Couldn't add config data rpc %d\n", rpc));
               return (error);
           }
           else
           {
            BSSAP_DEBUG(("AddCfgLocal: Added config data rpc %d\n", rpc));
           }
        }
    }
    else
    {
         error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&rpc,
                           sizeof(ITS_UINT),
                           fptr1);
           if (error != ITS_SUCCESS)
           {
              /*  BSSAP_Alarm_CCITT(5129,__FILE__,__LINE__,"DPC %d",rpc);*/
                BSSAP_ERROR(("AddCfgLocal: Couldn't add config data rpc %d\n", rpc));
                return (error);
           }

         BSSAP_WARNING(("AddCfgLocal: Config data alread exists rpc %d\n", rpc));
        return (!ITS_SUCCESS);
    }

    return (error);
}


#if 0
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0860, ID :: D0870,
*                        ID :: D0890, ID :: D1060
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
        return NULL;
    }

    /*change for locking row*/

     error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET),
                           cdata);
    if (error != ITS_SUCCESS)
    {
       BSSAP_ERROR(("CommitCfgData: Fail \n"));
    }
   /*end*/

    BSSAP_DEBUG(("FetchCICRecord: Config data found BssId %d\n", bscId));

    return (cdata);
}

#endif /* Fetch RPC Entry original commented */

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
* Amaresh Prasad  26-08-2014
*/

CFGData*
BSSAP_CfgDB::FetchRPCEntry(ITS_OCTET bscId)
{
    CFGData* fptr = NULL;
    CFGData* cdata = NULL;
    ITS_INT error = 0;

    BSSAP_DEBUG(("BSSAP_CfgDB: First Checkin FetchRPCEntryLocal\n"));

    fptr = (CFGData*)DSM_FindLocal(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_RPC_LIST,
                               (ITS_OCTET *)&bscId,
                               sizeof(ITS_OCTET),
                               &error);

    if (error == ITS_ENOTFOUND)
    {
      cdata = (CFGData*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_RPC_LIST,
                                 (ITS_OCTET *)&bscId,
                                 sizeof(ITS_OCTET),
                                 &error);
      if (error == ITS_ENOTFOUND || !(cdata))
      {
          BSSAP_ERROR(("FetchRPCEntryLocal: Global Config data not found BssId %d\n", bscId));
          return NULL;
      }

        fptr = (CFGData*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                    DSM_TABLE_BSSAP_RPC_LIST,
                                    (ITS_OCTET *)&bscId,
                                    sizeof(ITS_OCTET),
                                    sizeof(CFGData),
                                    &error);
        if(fptr)
        {
          fptr->lpc = cdata->lpc;
          fptr->rpc = cdata->rpc;
          fptr->lssn = cdata->lssn;
          fptr->rssn = cdata->rssn;
          fptr->Id = cdata->Id;

          error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET), 
                           fptr);
          if (error != ITS_SUCCESS)
          {
            BSSAP_ERROR(("FetchRPCEntryLocal: Couldn't add config data BssId %d\n", bscId));
            error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET),
                           cdata);
             if (error != ITS_SUCCESS)
             {
                BSSAP_ERROR(("FetchRPCEntryLocal: CommitCfgData: Fail 1 \n"));
             }

          }
          else
          {
            error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET),
                           cdata);
             if (error != ITS_SUCCESS)
             {
                BSSAP_ERROR(("FetchRPCEntryLocal: CommitCfgData: Fail 1 \n"));
             }
          }
        }
        else
        {

            error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET),
                           cdata);
           if (error != ITS_SUCCESS)
           {
               BSSAP_ERROR(("FetchRPCEntryLocal: CommitCfgData: Fail 2 \n"));
           }
        }
    }
    else
    {
           error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_RPC_LIST,
                           (ITS_OCTET *)&bscId,
                           sizeof(ITS_OCTET),
                           fptr);
          if (error != ITS_SUCCESS)
          {
            BSSAP_ERROR(("FetchRPCEntryLocal: Couldn't add config data BssId %d\n", bscId));
          }

    }

    BSSAP_DEBUG(("FetchRPCEntryLocal: Config data found BssId %d\n", bscId));

    return (fptr);
}
#if 0
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0860, ID :: D0870,
*                        ID :: D0890, ID :: D1060
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
       	BSSAP_Alarm_CCITT(5125,__FILE__,__LINE__,"DPC %d",pc);
        BSSAP_ERROR(("FetchNWIDEntry: Config data not found rpc %d\n", pc));
        return (cdata);
    }

    /*change for locking row*/
     error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&pc,
                           sizeof(ITS_UINT),
                           cdata);
   /*end*/
    BSSAP_DEBUG(("FetchNWIDEntry: Config data found rpc %d\n", pc));

    return (cdata);
}

#endif /* Fetch NWID Entry original commented */


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
* Amaresh Prasad				 26-08-2014
*/

CFGData*
BSSAP_CfgDB::FetchNWIDEntry(ITS_UINT pc)
{
    CFGData* cdata = NULL;
    CFGData* fptr = NULL;
    ITS_INT error = 0;

    BSSAP_DEBUG(("BSSAP_CfgDB: FetchNWIDEntry\n"));

		fptr = (CFGData*)DSM_FindLocal(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_NWID_LIST,
                               (ITS_OCTET *)&pc,
                               sizeof(ITS_UINT),
                               &error);

    if (error == ITS_ENOTFOUND)
    {
      cdata =(CFGData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_NWID_LIST,
                               (ITS_OCTET *)&pc,
                               sizeof(ITS_UINT),
                               &error);

      if (error == ITS_ENOTFOUND || !(cdata))
      {
					BSSAP_Alarm_CCITT(5125,__FILE__,__LINE__,"DPC %d",pc);
        	BSSAP_ERROR(("FetchNWIDEntry: Config data not found rpc %d\n", pc));
          return (cdata);
      }

        fptr = (CFGData*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                    DSM_TABLE_BSSAP_NWID_LIST,
                                    (ITS_OCTET *)&pc,
                                    sizeof(ITS_UINT),
                                    sizeof(CFGData),
                                    &error);
        if(fptr)
        {
          fptr->lpc = cdata->lpc;
          fptr->rpc = cdata->rpc;
          fptr->lssn = cdata->lssn;
          fptr->rssn = cdata->rssn;
          fptr->Id = cdata->Id;

          error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&pc,
                           sizeof(ITS_UINT), 
                           fptr);
          if (error != ITS_SUCCESS)
          {
        	  BSSAP_ERROR(("FetchNWIDEntry: Config data not found rpc %d\n", pc));
            error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&pc,
                           sizeof(ITS_UINT),
                           cdata);
             if (error != ITS_SUCCESS)
             {
                BSSAP_ERROR(("FetchNWIDEntryLocal: CommitCfgData: Fail 1 \n"));
             }

          }
          else
          {
            error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&pc,
                           sizeof(ITS_UINT),
                           cdata);
             if (error != ITS_SUCCESS)
             {
                BSSAP_ERROR(("FetchNWIDEntryLocal: CommitCfgData: Fail 1 \n"));
             }
          }
        }
        else
        {

            error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&pc,
                           sizeof(ITS_UINT),
                           cdata);
           if (error != ITS_SUCCESS)
           {
               BSSAP_ERROR(("FetchNWIDEntryLocal: CommitCfgData: Fail 2 \n"));
           }
        }
    }
    else
    {
           error = DSM_CommitLocal(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_NWID_LIST,
                           (ITS_OCTET *)&pc,
                           sizeof(ITS_UINT),
                           fptr);
          if (error != ITS_SUCCESS)
          {
        		BSSAP_ERROR(("FetchNWIDEntryLocal: Config data not found rpc %d\n", pc));
          }

    }
    BSSAP_DEBUG(("FetchNWIDEntry: Config data found rpc %d\n", pc));
    return (fptr);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0860, ID :: D0870,
*                        ID :: D0890, ID :: D1060
*/
ITS_INT
BSSAP_CfgDB::RemoveRPCEntry(ITS_OCTET bscId)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* cdata = NULL;

		 /*Modification Start by Amaresh as on dated 26-08-14 */
    RemoveRPCEntryLocal(bscId);
    /*Modification Start by Amaresh as on dated 26-08-14 */

    BSSAP_DEBUG(("BSSAP_CfgDB: RemovePRCEntry\n"));

    //cdata = FetchRPCEntry(bscId);
     cdata = (CFGData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_RPC_LIST,
                               (ITS_OCTET *)&bscId,
                               sizeof(ITS_OCTET),
                               &error);

    if (error == ITS_ENOTFOUND || !(cdata))
    {
       BSSAP_ERROR(("FetchCfgData: Config data not found BssId %d\n", bscId));

    }
   else
    {
       BSSAP_DEBUG(("FetchCfgData: Config data found BssId %d\n", bscId));
    }

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
*       Deleting config data from LOCAL RPC LIST table
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
* AMaresh Prasad         26-08-2014
*/
ITS_INT
BSSAP_CfgDB::RemoveRPCEntryLocal(ITS_OCTET bscId)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* cdata = NULL;

    BSSAP_DEBUG(("BSSAP_CfgDB: RemovePRCEntryLocal\n"));

     cdata = (CFGData*)DSM_FindLocal(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_RPC_LIST,
                               (ITS_OCTET *)&bscId,
                               sizeof(ITS_OCTET),
                               &error);

    if (error == ITS_ENOTFOUND || !(cdata))
    {
       BSSAP_ERROR(("FetchCfgDataLocal: Config data not found BssId %d\n", bscId));

    }
   else
    {
       BSSAP_DEBUG(("FetchCfgDataLocal: Config data found BssId %d\n", bscId));
    }

    if (cdata)
    { 
        error = DSM_FreeLocal(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_RPC_LIST,
                         (ITS_OCTET *)&bscId,
                         sizeof(ITS_OCTET),
                         cdata);
        if (error != ITS_SUCCESS)
        {   
            BSSAP_ERROR(("RemovePRCEntryLocal: Remove fail %d\n", bscId));

            return (error);
        }
    }
    else
    {
        BSSAP_ERROR(("RemovePRCEntryLocal: Fail to remove config data %d\n", bscId));

        return (error);
    }

    BSSAP_DEBUG(("RemovePRCEntryLocal: Config data removed %d\n", bscId));

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0860, ID :: D0870,
*                        ID :: D0890, ID :: D1060
*/
ITS_INT
BSSAP_CfgDB::RemoveNWIDEntry(ITS_UINT pc)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* cdata = NULL;

		/*Modification Start by Amaresh as on dated 26-08-14 */
    RemoveNWIDEntryLocal(pc);
		/*Modification Stop by Amaresh as on dated 26-08-14 */

    BSSAP_DEBUG(("BSSAP_CfgDB: FetchNWIDEntry\n"));

    //cdata = FetchNWIDEntry(pc);
    cdata = (CFGData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_NWID_LIST,
                               (ITS_OCTET *)&pc,
                               sizeof(ITS_UINT),
                               &error);

    if (error == ITS_ENOTFOUND || !(cdata))
    {
        BSSAP_ERROR(("FetchNWIDEntry: Config data not found rpc %d\n", pc));
        BSSAP_Alarm_CCITT(5125,__FILE__,__LINE__,"dpc %d",pc);
        return (error);
    }

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
       	BSSAP_Alarm_CCITT(5127,__FILE__,__LINE__,"DPC %d",pc);
        BSSAP_ERROR(("FetchNWIDEntry: Fail to remove config data %d\n", pc));

        return (error);
    }

    BSSAP_DEBUG(("FetchNWIDEntry: Config data removed %d\n", pc));

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
* Amaresh Prasad 				 26-08-2014
*/

ITS_INT
BSSAP_CfgDB::RemoveNWIDEntryLocal(ITS_UINT pc)
{
    ITS_INT error = !ITS_SUCCESS;
    CFGData* cdata = NULL;

    BSSAP_DEBUG(("BSSAP_CfgDB: FetchNWIDEntryLocal\n"));

    //cdata = FetchNWIDEntry(pc);
    cdata = (CFGData*)DSM_FindLocal(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_NWID_LIST,
                               (ITS_OCTET *)&pc,
                               sizeof(ITS_UINT),
                               &error);

    if (error == ITS_ENOTFOUND || !(cdata))
    {
        BSSAP_ERROR(("FetchNWIDEntryLocal: Config data not found rpc %d\n", pc));
      /*  BSSAP_Alarm_CCITT(5125,__FILE__,__LINE__,"dpc %d",pc);*/
        return (error);
    }

    if (cdata)
    {
        error = DSM_FreeLocal(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_NWID_LIST,
                         (ITS_OCTET *)&pc,
                         sizeof(ITS_UINT),
                         cdata);
        if (error != ITS_SUCCESS)
        {  
            BSSAP_ERROR(("FetchNWIDEntryLocal: Remove fail %d\n", pc));

            return (error);
        }
    }   
    else
    {
     /*  	BSSAP_Alarm_CCITT(5127,__FILE__,__LINE__,"DPC %d",pc);*/
        BSSAP_ERROR(("FetchNWIDEntryLocal: Fail to remove config data %d\n", pc));

        return (error);
    }

    BSSAP_DEBUG(("FetchNWIDEntryLocal: Config data removed %d\n", pc));

    return (error);
}
