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
 *  ID: $Id: bssap_appiddb.cpp,v 1.1 2008-02-07 10:09:55 amaresh.prasad Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.9  2006/09/18 12:26:48  sjaddu
 * LOG: Done changes to use NEED_LARGE_CONTEXT.
 * LOG:
 * LOG: Revision 1.1.2.8  2006/09/14 16:02:24  sjaddu
 * LOG: Fix for SLR and DLR values with morethan 3-octets.
 * LOG:
 * LOG: Revision 1.1.2.7  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.6  2005/10/06 08:30:18  adutta
 * LOG: Removed the deletion of call object
 * LOG:
 * LOG: Revision 1.1.2.5  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/20 18:16:05  adutta
 * LOG: Few more traces added
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/16 10:12:29  adutta
 * LOG: Traces added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/

#include <bssap_appiddb.h>
#include <bssap.h>

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

/*implementation:internal
*
* PURPOSE:
*       Initialization of Call Table
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if table gets intialized
*       Error, if problem in intializing table
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0900, ID :: D1060
*/
ITS_INT
BSSAP_AppidDB::Initialize() 
{
    ITS_INT ret;
 
    ret = ITS_SingletonMultithreaded<BSSAP_AppidDB>::Initialize();

    if (ret == ITS_SUCCESS)
    {
        BSSAP_DEBUG(("BSSAP_AppidDB: Appid  table initialized\n"));
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*      Deleting call table
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
*                        ID :: D0900, ID :: D1060
*/
BSSAP_AppidDB::~BSSAP_AppidDB()
{
   HASH_DeleteTable(_BS_Appid_info);
}

/*implementation:internal
*
* PURPOSE:
*       Adding APIID object in to table
* INPUT:
*       Call object
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
*                        ID :: D0900, ID :: D0910,
*                        ID :: D1060
*/
ITS_INT
BSSAP_AppidDB::Add(BSSAP_AppId* Appid)
{
    ITS_INT error = 0;
    ITS_CTXT hash = 0;
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_AppId* fptr = NULL;
/*Modification Start by Amaresh as on dated 26-08-14 */
		AddAppidLocal(Appid);
/*Modification Stop by Amaresh as on dated 26-08-14 */

    BSSAP_DEBUG(("BSSAP_AppidDB::Add Appid \n"));
 
    hash = Appid->GetAppId();

    fptr = (BSSAP_AppId*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_APPID_LIST,
                                 (ITS_OCTET *)&hash,
                                 sizeof(ITS_CTXT),  
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr = (BSSAP_AppId*) DSM_Alloc(DSM_SccpFtGroupId,
                                       DSM_TABLE_BSSAP_APPID_LIST,
                                       (ITS_OCTET *)&hash,
                                       sizeof(ITS_CTXT),
                                       sizeof(BSSAP_AppId),
                                       &error);
        if (!fptr)
        {
            BSSAP_CRITICAL(("Add: Fail to alloc memory for APPID table\n"));

            return (ITS_ENOMEM); 
        } 
    }

    fptr->SetSLR(Appid->GetSLR());
    fptr->SetDLR(Appid->GetDLR());
    fptr->SetAppId(Appid->GetAppId());

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_APPID_LIST,
                       (ITS_OCTET *)&hash,
                       sizeof(ITS_CTXT),
                       fptr);
    if (error != ITS_SUCCESS)
    {
        BSSAP_ERROR(("Add: Fail to add CDR for APPID table %d\n", hash));

        return (error);
    }

    BSSAP_DEBUG(("Add: Added CDR for APPID entry %d\n", hash));

    return (error);
}

/*implementation:internal
*
* PURPOSE:
*       Adding APIID object in to Local table
* INPUT:
*       Call object
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
* Amaresh Prasad				 26-08-2014
*/

ITS_INT
BSSAP_AppidDB::AddAppidLocal(BSSAP_AppId* Appid)
{
    ITS_INT error = 0;
    ITS_CTXT hash = 0;
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_AppId* fptr = NULL;

    BSSAP_DEBUG(("BSSAP_AppidDBLocal::Add Appid \n"));
 
    hash = Appid->GetAppId();

    fptr = (BSSAP_AppId*)DSM_FindLocal(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_APPID_LIST,
                                 (ITS_OCTET *)&hash,
                                 sizeof(ITS_CTXT),  
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr = (BSSAP_AppId*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                       DSM_TABLE_BSSAP_APPID_LIST,
                                       (ITS_OCTET *)&hash,
                                       sizeof(ITS_CTXT),
                                       sizeof(BSSAP_AppId),
                                       &error);
        if (!fptr)
        {
            BSSAP_CRITICAL(("AddApiidDBLocal: Fail to alloc memory for APPID table\n"));

            return (ITS_ENOMEM); 
        } 
    }

    fptr->SetSLR(Appid->GetSLR());
    fptr->SetDLR(Appid->GetDLR());
    fptr->SetAppId(Appid->GetAppId());

    error = DSM_CommitLocal(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_APPID_LIST,
                       (ITS_OCTET *)&hash,
                       sizeof(ITS_CTXT),
                       fptr);
    if (error != ITS_SUCCESS)
    {
        BSSAP_ERROR(("AddApiidDBLocal: Fail to add CDR for APPID table %d\n", hash));

        return (error);
    }

    BSSAP_DEBUG(("AddApiidDBLocal: Added CDR for APPID entry %d\n", hash));

    return (error);
}




#if 0
/*implementation:internal
*
* PURPOSE:
*       Fetching call object from call table by providing callref
*       as input
* INPUT:
*       call reference
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       call object
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0900, ID :: D0910,
*                        ID :: D1060
*/
BSSAP_AppId*
BSSAP_AppidDB::Fetch(ITS_CTXT appid)
{
    ITS_INT error = 0;                 
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_AppId* fptr = NULL;

    BSSAP_DEBUG(("BSSAP_AppidDB::Fetch AppID %d\n", appid));

    fptr = (BSSAP_AppId*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_APPID_LIST,
                                 (ITS_OCTET *)&appid,
                                 sizeof(ITS_CTXT),
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        BSSAP_ERROR(("Fetch: Fail to retreive CDR from APPID table %d\n", appid));
        return NULL;
    }

    /*Change for locking*/
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_APPID_LIST,
                       (ITS_OCTET *)&appid,
                       sizeof(ITS_CTXT),
                       fptr);

    if (error != ITS_SUCCESS)
    {
        BSSAP_ERROR(("Fetch: Fail to add CDR for APPID table %d\n",appid ));

        return (fptr);
    }
    /*end */

    return (fptr);
}

#endif


/*implementation:internal
*
* PURPOSE:
*       Fetching call object from call table by providing callref
*       as input
* INPUT:
*       call reference
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       call object
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad				 26-08-2014
*/

BSSAP_AppId*
BSSAP_AppidDB::Fetch(ITS_CTXT appid)
{
    ITS_INT error = 0;                 
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_AppId* fptr = NULL;
    BSSAP_AppId* lfptr = NULL;

    BSSAP_DEBUG(("BSSAP_AppidDB::Fetch AppIDLocal AppId[%04x]\n", appid));

    lfptr = (BSSAP_AppId*)DSM_FindLocal(DSM_SccpFtGroupId,
                               			 	 	DSM_TABLE_BSSAP_APPID_LIST,
                                 				(ITS_OCTET *)&appid,
                                 				sizeof(ITS_CTXT),
                                 				&error);

    if (error == ITS_ENOTFOUND)
    {
      fptr = (BSSAP_AppId*)DSM_Find(DSM_SccpFtGroupId,
                                   DSM_TABLE_BSSAP_APPID_LIST,
                                   (ITS_OCTET *)&appid,
                                    sizeof(ITS_CTXT),
                                    &error);

      if (error == ITS_ENOTFOUND || !(fptr))
      { 
        BSSAP_ERROR(("Fetch: Fail to retreive CDR from APPID table [%04x]\n", appid));
        return NULL;
      }

	      lfptr = (BSSAP_AppId*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                       				DSM_TABLE_BSSAP_APPID_LIST,
                                       				(ITS_OCTET *)&appid,
                                       				sizeof(ITS_CTXT),
                                       				sizeof(BSSAP_AppId),
                                       				&error);

        if(lfptr)
        {
					lfptr->SetSLR(fptr->GetSLR());
			    lfptr->SetDLR(fptr->GetDLR());
    			lfptr->SetAppId(fptr->GetAppId());

          error = DSM_CommitLocal(DSM_SccpFtGroupId,
				                       		DSM_TABLE_BSSAP_APPID_LIST,
        				               		(ITS_OCTET *)&appid,
                				       		sizeof(ITS_CTXT),
                       				 		lfptr);

          if (error != ITS_SUCCESS)
          {
        		BSSAP_ERROR(("FetchAPPIDLocal: Fail to add CDR for APPID table [%04x]\n",appid ));
            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_APPID_LIST,
                       (ITS_OCTET *)&appid,
                       sizeof(ITS_CTXT),
                       fptr);

             if (error != ITS_SUCCESS)
             {
        				BSSAP_ERROR(("FetchAPPIDLocal: CommitAPPIDData Fail 1 for appId[%04x] \n",appid));
             }

          }
          else
          {
            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_APPID_LIST,
                       (ITS_OCTET *)&appid,
                       sizeof(ITS_CTXT),
                       fptr);

             if (error != ITS_SUCCESS)
             {
                BSSAP_ERROR(("FetchAPPID: CommitAPPIDData Fail 1 for appId[%04x] \n",appid));
             }
          }
        }
        else
        {

            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_APPID_LIST,
                       (ITS_OCTET *)&appid,
                       sizeof(ITS_CTXT),
                       fptr);

           if (error != ITS_SUCCESS)
           {
               BSSAP_ERROR(("FetchAPPID: CommitAPPIDData Fail  2 for appId[%04x]\n",appid));
           }
        }
    }
    else
    {
           error = DSM_CommitLocal(DSM_SccpFtGroupId,
                                  DSM_TABLE_BSSAP_APPID_LIST,
                                  (ITS_OCTET *)&appid,
                                  sizeof(ITS_CTXT),
                                  lfptr);

          if (error != ITS_SUCCESS)
          {
        		BSSAP_ERROR(("FetchAPPIDLocal: Fail to add CDR for APPID table [%04x]\n",appid ));
          }

    }
		if (lfptr != NULL)
    return (lfptr);
		else
    return (fptr);
}


/*implementation:internal
*
* PURPOSE:
*       Deleting call object from table
* INPUT:
*       call reference
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      success, if call object gets deleted
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0900, ID :: D0910,
*                        ID :: D1060
*/
ITS_INT
BSSAP_AppidDB::Remove(ITS_CTXT appid)
{
    ITS_INT error = ITS_ENOTFOUND;
    BSSAP_AppId* Appid = NULL;

		/*Modification Start by Amaresh as on dated 26-08-14 */
    RemoveAppidLocal(appid);
    /*Modification Start by Amaresh as on dated 26-08-14 */
 
    BSSAP_DEBUG(("BSSAP_AppidDB::Remove APPID from APPIDDB table  %d\n", appid));

      Appid= (BSSAP_AppId*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_APPID_LIST,
                                 (ITS_OCTET *)&appid,
                                 sizeof(ITS_CTXT),
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        BSSAP_ERROR(("FetchAPPIDDB: Fail to retreive CDR from APPID table %d\n", appid));
        return NULL;
    }
    if (Appid)
    {
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_APPID_LIST,
                         (ITS_OCTET *)&appid,
                         sizeof(ITS_CTXT),
                         Appid);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("RemoveAPPIDDB: Fail to remove CDR from APPIDDB table %d\n", appid));
        }
    }
    else
    {
        BSSAP_ERROR(("RemoveAPPIDDB: Fail to remove CDR %d\n", appid));
    }

    return (error);
}


/*implementation:internal
*
* PURPOSE:
*       Deleting APPID object from table
* INPUT:
*       call reference
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      success, if APPID object gets deleted
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad 				 26-08-2014
*/

ITS_INT
BSSAP_AppidDB::RemoveAppidLocal(ITS_CTXT appid)
{
    ITS_INT error = ITS_ENOTFOUND;
    BSSAP_AppId* Appid = NULL;
 
    BSSAP_DEBUG(("BSSAP_AppidDBLocal::Remove APPID from APPIDDB table  %d\n", appid));

      Appid= (BSSAP_AppId*)DSM_FindLocal(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_APPID_LIST,
                                 (ITS_OCTET *)&appid,
                                 sizeof(ITS_CTXT),
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        BSSAP_ERROR(("FetchAPPIDDBLocal: Fail to retreive CDR from APPID table %d\n", appid));
        return NULL;
    }
    if (Appid)
    {
        error = DSM_FreeLocal(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_APPID_LIST,
                         (ITS_OCTET *)&appid,
                         sizeof(ITS_CTXT),
                         Appid);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("RemoveAPPIDDBLocal: Fail to remove CDR from APPIDDB table %d\n", appid));
        }
    }
    else
    {
        BSSAP_ERROR(("RemoveAPPIDDBLocal: Fail to remove CDR %d\n", appid));
    }

    return (error);
}

