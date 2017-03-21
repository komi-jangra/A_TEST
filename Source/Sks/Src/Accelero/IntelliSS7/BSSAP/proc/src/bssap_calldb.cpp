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
 *  ID: $Id: bssap_calldb.cpp,v 1.2 2008/02/01 04:19:50 amaresh.prasad Exp $
 *
 * LOG: $Log: bssap_calldb.cpp,v $
 * LOG: Revision 1.2  2008/02/01 04:19:50  amaresh.prasad
 * LOG: Updated for Alarm
 * LOG: CV  ----------------------------------------------------------------------
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

#include <bssap_calldb.h>
#include <bssap.h>
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
BSSAP_CallDB::Initialize() 
{
    ITS_INT ret;
 
    ret = ITS_SingletonMultithreaded<BSSAP_CallDB>::Initialize();

    if (ret == ITS_SUCCESS)
    {
        BSSAP_DEBUG(("BSSAP_CallDB: Call table initialized\n"));
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
BSSAP_CallDB::~BSSAP_CallDB()
{
   HASH_DeleteTable(_BS_Call_info);
}

/*implementation:internal
*
* PURPOSE:
*       Adding call object in to table
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
BSSAP_CallDB::Add(BSSAP_Call* call)
{
    ITS_INT error = 0;
    ITS_CTXT hash = 0;
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_Call* fptr = NULL;

    BSSAP_DEBUG(("BSSAP_CallDB: Add \n"));
 
    hash = call->GetSLR();

    fptr = (BSSAP_Call*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&hash,
                                 sizeof(ITS_CTXT),  
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr = (BSSAP_Call*) DSM_Alloc(DSM_SccpFtGroupId,
                                       DSM_TABLE_BSSAP_CALL_CTXT,
                                       (ITS_OCTET *)&hash,
                                       sizeof(ITS_CTXT),
                                       sizeof(BSSAP_Call),
                                       &error);
        if (!fptr)
        {
            BSSAP_CRITICAL(("Add: Fail to alloc memory\n"));

            return (ITS_ENOMEM); 
        } 
    }

    fptr->SetSLR(call->GetSLR());
    fptr->SetDLR(call->GetDLR());
    fptr->SetAppId(call->GetAppId());
    fptr->SetCIC(call->GetCIC());
    fptr->SetBssId(call->GetBssId());
    fptr->SetMssgType(call->GetMssgType());
    fptr->SetTimerId(call->GetTimerId());
    fptr->SetCallType(call->GetCallType());
		BSSAP_DEBUG(("BSSAP_CallDB: GetBSSAPData\n"));

		/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */ 
		if(call->GetDatalen())
		{
        data = call->GetBSSAPData(&len);
		    BSSAP_DEBUG(("BSSAP_CallDB: extract GetBSSAPData\n"));
		    fptr->SetBSSAPData(data, len);
		    BSSAP_DEBUG(("BSSAP_CallDB: GetBSSAPData have data set in fptr\n"));

        /* Added by Amaresh as on dated 01-07-08 */
		    fptr->SetHoreqDt1(2);

		}	
		else
		{	
   		  BSSAP_DEBUG(("BSSAP_CallDB: GetBSSAPData have no datalen \n"));
	  	  fptr->SetHoreqDt1(1);
        BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: In Fptr HoreqDt1 %d \n",fptr->GetHoreqDt1()));
		}

		BSSAP_DEBUG(("BSSAP_CallDB: outside GetBSSAPData\n"));
		/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */
    fptr->SetHandOver(call->GetHandOver());

    /* Added by Amaresh for Handover releted as on dated 20-05-08 */
		fptr->SetHandOverFailure(call->GetHandOverFailure());
		fptr->SetHandOverOldBss(call->GetHandOverOldBss());
		fptr->SetHandOverNewBss(call->GetHandOverNewBss());
/*Modification Start by Amaresh as on dated 26-08-14 */
		fptr->SetCicst(call->GetCicst());
/*Modification Stop by Amaresh as on dated 26-08-14 */

    /* Addition completed by Amaresh for Handover releted as on dated 20-05-08 */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&hash,
                       sizeof(ITS_CTXT),
                       fptr);
    if (error != ITS_SUCCESS)
    {
        BSSAP_ERROR(("Add: Fail to add CDR %d\n", hash));
        return (error);
    }

    BSSAP_DEBUG(("Add: Added CDR %d\n", hash));
		AddCallLocal(fptr);
    return (error);
}


/*implementation:internal
*
* PURPOSE:
*       Adding call object in to Local table
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
* Amaresh Prasad  			 26-08-2014
*/

ITS_INT
BSSAP_CallDB::AddCallLocal(BSSAP_Call* call)
{
    ITS_INT error = 0;
    ITS_CTXT hash = 0;
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_Call* fptr = NULL;

    BSSAP_DEBUG(("BSSAP_CallDBLocal: Add \n"));
 
    hash = call->GetSLR();

    fptr = (BSSAP_Call*)DSM_FindLocal(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&hash,
                                 sizeof(ITS_CTXT),  
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr = (BSSAP_Call*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                       DSM_TABLE_BSSAP_CALL_CTXT,
                                       (ITS_OCTET *)&hash,
                                       sizeof(ITS_CTXT),
                                       sizeof(BSSAP_Call),
                                       &error);
        if (!fptr)
        {
            BSSAP_CRITICAL(("AddCALLDBLocal: Fail to alloc memory\n"));

            return (ITS_ENOMEM); 
        } 
    }

    fptr->SetSLR(call->GetSLR());
    fptr->SetDLR(call->GetDLR());
    fptr->SetAppId(call->GetAppId());
    fptr->SetCIC(call->GetCIC());
    fptr->SetBssId(call->GetBssId());
    fptr->SetMssgType(call->GetMssgType());
    fptr->SetTimerId(call->GetTimerId());
    fptr->SetCallType(call->GetCallType());
		BSSAP_DEBUG(("BSSAP_CallDBLocal: GetBSSAPData\n"));

		/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */ 
		if(call->GetDatalen())
		{
        data = call->GetBSSAPData(&len);
		    BSSAP_DEBUG(("BSSAP_CallDBLocal: extract GetBSSAPData\n"));
		    fptr->SetBSSAPData(data, len);
		    BSSAP_DEBUG(("BSSAP_CallDBLocal: GetBSSAPData have data set in fptr\n"));

        /* Added by Amaresh as on dated 01-07-08 */
		    fptr->SetHoreqDt1(2);

		}	
		else
		{	
   		  BSSAP_DEBUG(("BSSAP_CallDBLocal: GetBSSAPData have no datalen \n"));
	  	  fptr->SetHoreqDt1(1);
        BSSAP_DEBUG(("BSSAP_ProcessSCCPdataLocal: In Fptr HoreqDt1 %d \n",fptr->GetHoreqDt1()));
		}

		BSSAP_DEBUG(("BSSAP_CallDBLocal: outside GetBSSAPData\n"));
		/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */
    fptr->SetHandOver(call->GetHandOver());

    /* Added by Amaresh for Handover releted as on dated 20-05-08 */
		fptr->SetHandOverFailure(call->GetHandOverFailure());
		fptr->SetHandOverOldBss(call->GetHandOverOldBss());
		fptr->SetHandOverNewBss(call->GetHandOverNewBss());

/*Modification Start by Amaresh as on dated 26-08-14 */
		fptr->SetCicst(call->GetCicst());
/*Modification Stop by Amaresh as on dated 26-08-14 */

    /* Addition completed by Amaresh for Handover releted as on dated 20-05-08 */
    error = DSM_CommitLocal(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&hash,
                       sizeof(ITS_CTXT),
                       fptr);
    if (error != ITS_SUCCESS)
    {
        BSSAP_ERROR(("AddCALLDBLocal: DSM_CommitLocal Fail to add Callref[%04x]\n", hash));
        return (error);
    }

    BSSAP_DEBUG(("AddCALLDBLocal: Added Callref[%04x]\n", hash));
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
BSSAP_Call*
BSSAP_CallDB::Fetch(ITS_CTXT callref)
{
    ITS_INT error = 0;                 
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_Call* fptr = NULL;

    BSSAP_DEBUG(("BSSAP_CallDB: Fetch %d\n", callref));

    fptr = (BSSAP_Call*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&callref,
                                 sizeof(ITS_CTXT),
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        BSSAP_ERROR(("Fetch: Fail to retreive CDR %d\n", callref));
        return NULL;
    }

    /*change due to Locking of Row*/
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&callref,
                       sizeof(ITS_CTXT),
                       fptr);

    if (error == ITS_ENOTFOUND|| error== ITS_EINUSE)
    {
        BSSAP_ERROR(("Fetch: Fail to commit CDR %d\n", callref));
    }
    return (fptr);
}

#endif /* Amaresh Commented code for fetch implementation as on dated 26-08-14 */


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

BSSAP_Call*
BSSAP_CallDB::Fetch(ITS_CTXT callref)
{
    ITS_INT error = 0;                 
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_Call* fptr = NULL;
    BSSAP_Call* lfptr = NULL;

    BSSAP_DEBUG(("BSSAP_CallDB: Fetch Callref[%04x]\n", callref));

    lfptr = (BSSAP_Call*)DSM_FindLocal(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&callref,
                                 sizeof(ITS_CTXT),
                                 &error);
		if (error == ITS_ENOTFOUND)
    {
			fptr = (BSSAP_Call*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&callref,
                                 sizeof(ITS_CTXT),
                                 &error);

      if (error == ITS_ENOTFOUND || !(fptr))
      {
					BSSAP_ERROR(("BSSAP_CallDB: DSM_Find Fail to retreive Callref[%04x] \n", callref));
          return NULL;
      }

       lfptr =  (BSSAP_Call*) DSM_AllocLocal(DSM_SccpFtGroupId,
                                       DSM_TABLE_BSSAP_CALL_CTXT,
                                       (ITS_OCTET *)&callref,
                                       sizeof(ITS_CTXT),
                                       sizeof(BSSAP_Call),
                                       &error); 
				if(lfptr)
        {
					lfptr->SetSLR(fptr->GetSLR());
  			  lfptr->SetDLR(fptr->GetDLR());
			    lfptr->SetAppId(fptr->GetAppId());
			    lfptr->SetCIC(fptr->GetCIC());
			    lfptr->SetBssId(fptr->GetBssId());
			    lfptr->SetMssgType(fptr->GetMssgType());
			    lfptr->SetTimerId(fptr->GetTimerId());
			    lfptr->SetCallType(fptr->GetCallType());

					 /* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */
			    if(fptr->GetDatalen())
    			{
        			data = fptr->GetBSSAPData(&len);
        			lfptr->SetBSSAPData(data, len);
        			BSSAP_DEBUG(("BSSAP_CallDB: GetBSSAPData have data set in fptr\n"));
        			/* Added by Amaresh as on dated 01-07-08 */
        			lfptr->SetHoreqDt1(2);
    			}
    			else
    			{
        			BSSAP_DEBUG(("BSSAP_CallDB: GetBSSAPData have no datalen \n"));
        			lfptr->SetHoreqDt1(1);
        			BSSAP_DEBUG(("BSSAP_CallDB: In Fptr HoreqDt1 %d \n",fptr->GetHoreqDt1()));
    			}

    			BSSAP_DEBUG(("BSSAP_CallDB: outside GetBSSAPData\n"));
    			/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */
    			lfptr->SetHandOver(fptr->GetHandOver());

					/* Added by Amaresh for Handover releted as on dated 20-05-08 */
    			lfptr->SetHandOverFailure(fptr->GetHandOverFailure());
    			lfptr->SetHandOverOldBss(fptr->GetHandOverOldBss());
    			lfptr->SetHandOverNewBss(fptr->GetHandOverNewBss());

          error  = DSM_CommitLocal(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&callref,
                       sizeof(ITS_CTXT),
                       lfptr);

          if (error != ITS_SUCCESS)
          {
						BSSAP_ERROR(("BSSAP_CallDB: DSM_CommitLocal  1 Fail to retreive Callref[%04x]\n", callref));
            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&callref,
                       sizeof(ITS_CTXT),
                       fptr);

             if (error != ITS_SUCCESS || error == ITS_EINUSE)
             {
								BSSAP_ERROR(("BSSAP_CallDB: DSM_Commit 1 Fail to Commit Callref[%04x]\n", callref));
             }
          }
					else
          {
            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&callref,
                       sizeof(ITS_CTXT),
                       fptr);

             if (error != ITS_SUCCESS || error == ITS_EINUSE)
             {
								BSSAP_ERROR(("BSSAP_CallDB: DSM_Commit 2 Fail to Commit Callref[%04x]\n", callref));
             }
          }
        }
        else
        {

            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&callref,
                       sizeof(ITS_CTXT),
                       fptr);
           if (error != ITS_SUCCESS || error == ITS_EINUSE)
           {
							BSSAP_ERROR(("BSSAP_CallDB: DSM_Commit 3 Fail to Commit Callref[%04x]\n", callref));
           }
        }
    }
    else
    {
           error =  DSM_CommitLocal(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&callref,
                       sizeof(ITS_CTXT),
                       lfptr);

          if (error != ITS_SUCCESS)
          {
						BSSAP_ERROR(("BSSAP_CallDB: DSM_CommitLocal  2  Fail to retreive Callref[%04x]\n", callref));
          }

    }
		if(lfptr != NULL)
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
BSSAP_CallDB::Remove(ITS_CTXT callref)
{
    ITS_INT error = ITS_ENOTFOUND;
    BSSAP_Call* call = NULL;
    BSSAP_Call* fptr = NULL;
		/*Modification Start by Amaresh as on dated 26-08-14 */
		RemoveCallLocal(callref);
		/*Modification Stop by Amaresh as on dated 26-08-14 */
    
		BSSAP_DEBUG(("Entering BSSAP_CallDB: Remove  %d\n", callref));

/*    call = Fetch(callref);*/

    /*because lock are required before free*/
    fptr = (BSSAP_Call*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&callref,
                                 sizeof(ITS_CTXT),
                                 &error);

    if (error == ITS_ENOTFOUND|| error== ITS_EINUSE)
    {
        BSSAP_ERROR(("Fetch: DSM_Find Fail to retreive Callref[%04x] \n", callref));
        return ITS_ENOTFOUND;
    }

    if (fptr)
    {
				BSSAP_DEBUG(("BSSAP_CallDB: fptr present \n"));
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_CALL_CTXT,
                         (ITS_OCTET *)&callref,
                         sizeof(ITS_CTXT),
                         fptr);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("Remove: Fail to remove CDR %d\n", callref));
        }
    }
    else
    { 

        BSSAP_ERROR(("Remove: Fail to remove CDR %d\n", callref));

   }
   	BSSAP_DEBUG(("BSSAP_CallDB: fptr remove successfully\n"));

    return (error);
}


/*implementation:internal
*
* PURPOSE:
*       Deleting call object from Local table
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
* Amaresh Prasad				 26-08-2014
*/

ITS_INT
BSSAP_CallDB::RemoveCallLocal(ITS_CTXT callref)
{
    ITS_INT error = ITS_ENOTFOUND;
    BSSAP_Call* call = NULL;
    BSSAP_Call* fptr = NULL; 
    BSSAP_DEBUG(("Entering BSSAP_CallDBLocal: Remove  %d\n", callref));

  /*  call = Fetch(callref);*/

    /*because lock are required before free*/
    fptr = (BSSAP_Call*)DSM_FindLocal(DSM_SccpFtGroupId,

                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&callref,
                                 sizeof(ITS_CTXT),
                                 &error);

    if (error == ITS_ENOTFOUND|| error== ITS_EINUSE)
    {
        BSSAP_ERROR(("FetchCALLDBLocal: DSM_FindLocal Fail to retreive Callref[%04x] \n", callref));
        return ITS_ENOTFOUND;
    }

    if (fptr)
    {
    		BSSAP_DEBUG(("BSSAP_CallDBLocal: fptr present\n"));
        error = DSM_FreeLocal(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_CALL_CTXT,
                         (ITS_OCTET *)&callref,
                         sizeof(ITS_CTXT),
                         fptr);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("RemoveCALLDBLocal: Fail to remove CDR %d\n", callref));
        }
    }
    else
    { 

        BSSAP_ERROR(("RemoveCALLDBLOcal: Fail to remove CDR %d\n", callref));

   }
   	BSSAP_DEBUG(("BSSAP_CallDBLocal: fptr remove successfully\n"));
    return (error);
}
