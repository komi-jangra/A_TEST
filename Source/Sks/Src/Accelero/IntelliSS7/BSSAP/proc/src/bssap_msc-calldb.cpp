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
 * ID: $Id: bssap_msc-calldb.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.4  2006/05/05 05:21:24  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.3  2006/04/26 07:28:10  adutta
 * LOG: Added debug print in Add()
 * LOG:
 * LOG: Revision 1.1.2.2  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 *
 * LOG: 
 ****************************************************************************/

#include <bssap_msc-calldb.h>
#include <bssap-msc.h>

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0190, ID :: D0200,
*                        ID :: D0920
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0190, ID :: D0200
*                        ID :: D0920
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0190, ID :: D0200,
*                        ID :: D0210, ID :: D0920
*/
ITS_INT
BSSAP_CallDB::Add(BSSAP_Call* call)
{
    ITS_INT error = 0;
    ITS_USHORT hash = 0;
    ITS_INT len  = 0;
    ITS_OCTET* data = NULL;
    BSSAP_Call* fptr = NULL;

    BSSAP_DEBUG(("BSSAP_CallDB: Add \n"));
 
    hash = call->GetSLR();

    fptr = (BSSAP_Call*)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_BSSAP_CALL_CTXT,
                                 (ITS_OCTET *)&hash,
                                 sizeof(ITS_USHORT),  
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        fptr = (BSSAP_Call*) DSM_Alloc(DSM_SccpFtGroupId,
                                       DSM_TABLE_BSSAP_CALL_CTXT,
                                       (ITS_OCTET *)&hash,
                                       sizeof(ITS_USHORT),
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
    fptr->SetCurrentEvent(call->GetCurrentEvent());
    fptr->SetPrevEvent(call->GetPrevEvent());
    fptr->SetMssgType(call->GetMssgType());
    fptr->SetTimerId(call->GetTimerId());
    fptr->SetCallType(call->GetCallType());

    data = call->GetBSSAPData(&len);
    fptr->SetBSSAPData(data, len);

    fptr->SetHandOver(call->GetHandOver());

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_BSSAP_CALL_CTXT,
                       (ITS_OCTET *)&hash,
                       sizeof(ITS_USHORT),
                       fptr);
    if (error != ITS_SUCCESS)
    {
        BSSAP_ERROR(("Add: Fail to add CDR %d\n", hash));

        return (error);
    }

    BSSAP_DEBUG(("Add: Added CDR %d slr %d dlr %d\n", hash, 
                                              fptr->GetSLR(), fptr->GetDLR()));

    return (error);
}

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0190, ID :: D0200,
*                        ID :: D0210, ID :: D0920
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
                                 sizeof(ITS_USHORT),
                                 &error);
    if (error == ITS_ENOTFOUND)
    {
        BSSAP_ERROR(("Fetch: Fail to retreive CDR %d\n", callref));
    }

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0190, ID :: D0200,
*                        ID :: D0210, ID :: D0920
*/
ITS_INT
BSSAP_CallDB::Remove(ITS_CTXT callref)
{
    ITS_INT error = ITS_ENOTFOUND;
    BSSAP_Call* call = NULL;
 
    BSSAP_DEBUG(("BSSAP_CallDB: Remove  %d\n", callref));

    call = Fetch(callref);

    if (call)
    {
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_CALL_CTXT,
                         (ITS_OCTET *)&callref,
                         sizeof(ITS_USHORT),
                         call);
        if (error != ITS_SUCCESS)
        {
            BSSAP_ERROR(("Remove: Fail to remove CDR %d\n", callref));
        }
    }
    else
    {
        BSSAP_ERROR(("Remove: Fail to remove CDR %d\n", callref));
    }

    return (error);
}
