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
 *  ID: $Id: bssap_cicdb.cpp,v 1.2 2008/02/01 04:21:13 amaresh.prasad Exp $
 *
 * LOG: $Log: bssap_cicdb.cpp,v $
 * LOG: Revision 1.2  2008/02/01 04:21:13  amaresh.prasad
 * LOG: Updated for Alarm
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
 * LOG: Revision 1.1.2.5  2005/12/05 09:13:28  mkrishna
 * LOG: flag for Blk/Unblk ack handling
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.3  2005/10/06 08:31:53  adutta
 * LOG: Taken care of network id.
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/29 07:37:22  adutta
 * LOG: Trace change
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 ****************************************************************************/

#include <bssap_cicdb.h>
#include <bssap-alarm.h> //25-01-08 by Amaresh
#include <bssap_cicdb.h> //25-01-08 by Amaresh
#include <bssap_cfgdb.h>

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0820, ID :: D0830,
*                        ID :: D0840, ID :: D1060
*/
ITS_INT
BSSAP_CicDB::AddCIC(ITS_OCTET nwId, ITS_USHORT pcm,
                    ITS_USHORT startTS, ITS_USHORT endTS)
{
    ITS_INT error = 0;
    ITS_USHORT index;
    ITS_UINT key = 0;
    CICData* fptr;

    /* Added by Amaresh for Alarm 21-07-08 */
		ITS_UINT cic=0;
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */		


    BSSAP_DEBUG(("BSSAP_CicDB: AddCIC\n"));


    if (!endTS)
    {
        endTS = startTS;
    }

    for (index = startTS; index <= endTS; index++)
    {
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & index));
				 cic= pcm << 5|(0x1FU & index);
  
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
            if(fptr)
	    {
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
        }
        else
        {
            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_CIC_CTXT,
                               (ITS_OCTET *)&key,
                               sizeof(ITS_UINT), 
                               fptr);
            if (error != ITS_SUCCESS)
            {
                BSSAP_ERROR(("AddCIC: Couldn't commit context %d \n",key));
                return (error);
            }

            /* Added by Amaresh for Alarm 21-07-08 */
            cfgdata = db.FetchRPCEntry(nwId);
            if (cfgdata)
            {
                DPC = cfgdata->rpc;
            }

            /* Added by Amaresh for Alarm 21-07-08 */
            BSSAP_WARNING(("AddCIC: Duplicate : Already Context exists %d %d\n", pcm, index));
      	    BSSAP_Alarm_CCITT(5130,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic); 
#ifdef NO_REDUNDACY
            return (!ITS_SUCCESS);
#else
            return (ITS_SUCCESS);
#endif
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0820, ID :: D0830,
*                        ID :: D0840, ID :: D1060
*/
CICData*
BSSAP_CicDB::FetchCICRecord(ITS_UINT cic,ITS_OCTET msgType,ITS_OCTET nwId)
{
    CICData* cdata = NULL;
    ITS_INT error = 0;
    ITS_OCTET cicbuf[2];//Amaresh 25-01-08
    ITS_USHORT pcm = 0; //Amaresh 25-01-08
    ITS_OCTET  ts = 0; //Amaresh 25-01-08
		ITS_USHORT Cic = 0; //Amaresh 25-01-08

    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT pc=0;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */	

    BSSAP_DEBUG(("BSSAP_CicDB: FetchCICRecord\n"));


    cdata = (CICData*)DSM_Find(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_CIC_CTXT,
                               (ITS_OCTET *)&cic,
                               sizeof(ITS_UINT),
                               &error);
   /* Added by Amaresh for Alarm implementation 25-01-08*/

    cicbuf[0] = cic & 0x000000FF;
    cicbuf[1] = (cic & 0x0000FF00) >> 8;
    cicbuf[2] = (cic & 0x00FF0000) >> 16;
    cicbuf[3] = (cic & 0xFF000000) >> 24;

	  pcm = ((cicbuf[1] << 3) |                            \
	     (cicbuf[0] & 0xe0) >> 5);
	  ts = (cicbuf[0] & 0x1f);
#if defined(CCITT)
	  BSSAP_DEBUG(("Fetch CIC record : pcm %d ts %d\n", pcm ,ts));
#endif

    /* Added by Amaresh for Alarm implementation 21-01-08*/
  	Cic=pcm << 5|(0x1FU & ts);	
 
    if (error == ITS_ENOTFOUND || !(cdata))
    {
        cfgdata = db.FetchRPCEntry(nwId);
        if (cfgdata)
        {
           DPC = cfgdata->rpc;
        }

    	BSSAP_Alarm_CCITT(5131,__FILE__,__LINE__,"dpc %d cic  %d ",DPC,Cic); //25-01-08 by Amaresh
      BSSAP_ERROR(("FetchCICRecord: CIC context not found %d\n", cic));
   }
   else
   {
   /*change for locking row*/
    /*           error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_BSSAP_CIC_CTXT,
                               (ITS_OCTET *)&cic,
                               sizeof(ITS_UINT), 
                               cdata);*/
   /*end*/
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0820, ID :: D0830,
*                        ID :: D0840, ID :: D1060
*/
ITS_INT
BSSAP_CicDB::RemoveCICRecord(ITS_UINT cic,ITS_OCTET nwId)
{
    ITS_INT error = !ITS_SUCCESS;
    CICData* cdata = NULL;
		ITS_OCTET cicbuf[2];//Amaresh 25-01-08
    ITS_USHORT pcm = 0; //Amaresh 25-01-08
    ITS_USHORT Cic = 0; //Amaresh 25-01-08
    ITS_OCTET  ts = 0; //

    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */

    BSSAP_DEBUG(("BSSAP_CicDB: RemoveCICRecord\n"));


    cdata = FetchCICRecord(cic,0,nwId);
		cicbuf[0] = cic & 0x000000FF;
    cicbuf[1] = (cic & 0x0000FF00) >> 8;
    cicbuf[2] = (cic & 0x00FF0000) >> 16;
    cicbuf[3] = (cic & 0xFF000000) >> 24;

    pcm = ((cicbuf[1] << 3) |                            \
             (cicbuf[0] & 0xe0) >> 5);

    ts = (cicbuf[0] & 0x1f);
    Cic= pcm << 5|(0x1FU & ts);
        cfgdata = db.FetchRPCEntry(nwId);
        if (cfgdata)
        {
           DPC = cfgdata->rpc;
        }
   
    if (cdata)
    { 
        error = DSM_Free(DSM_SccpFtGroupId,
                         DSM_TABLE_BSSAP_CIC_CTXT,
                         (ITS_OCTET *)&cic,
                         sizeof(ITS_UINT),
                         cdata);
        if (error != ITS_SUCCESS)
        {  
		  			BSSAP_Alarm_CCITT(5132,__FILE__,__LINE__,"dpc %d cic %d",DPC,Cic); //25-01-08 by Amaresh
            BSSAP_ERROR(("RemoveCICRecord: Fail to remove context  %d\n", cic));

            return (error);
        }
    }
    else
    {
       	BSSAP_Alarm_CCITT(5132,__FILE__,__LINE__,"dpc %d cic %d",DPC,Cic);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0820, ID :: D0830,
*                        ID :: D0840, ID :: D1060
*/
ITS_INT
BSSAP_CicDB::ModifyCICRecord(ITS_UINT cic, CICData* cicRec, ITS_OCTET msgType)
{
   ITS_INT error = 0;
	 ITS_OCTET cicbuf[2];
   ITS_USHORT pcm = 0;
   ITS_USHORT Cic = 0;
   ITS_OCTET  ts = 0;

    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT pc=0;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */


    BSSAP_DEBUG(("BSSAP_CicDB: ModifyCICRecord\n"));

    /* Added by Amaresh for Alarm 21-07-08 */
    if(cicRec)
    {
       cfgdata = db.FetchRPCEntry(cicRec->nwId);
       if (cfgdata)
        {
          DPC = cfgdata->rpc;
        }
    }
    cicbuf[0] = cic & 0x000000FF;
    cicbuf[1] = (cic & 0x0000FF00) >> 8;
    cicbuf[2] = (cic & 0x00FF0000) >> 16;
    cicbuf[3] = (cic & 0xFF000000) >> 24;

    pcm = ((cicbuf[1] << 3) |                            \
             (cicbuf[0] & 0xe0) >> 5);

    ts = (cicbuf[0] & 0x1f);
    Cic= pcm << 5|(0x1FU & ts);

    /* Added by Amaresh for Alarm 21-07-08 */
    if (cicRec)
    {
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_BSSAP_CIC_CTXT,
                           (ITS_OCTET *)&cic,
                           sizeof(ITS_UINT),
                           cicRec);
        if (error != ITS_SUCCESS)
        {
         			BSSAP_Alarm_CCITT(5133,__FILE__,__LINE__,"dpc %d cic  %d msgtype %d",DPC,Cic,msgType);
              BSSAP_ERROR(("ModifyCICRecord: Couldn't modify context %d\n", cic));
              return (error);
        }
        else
        {
            BSSAP_DEBUG(("ModifyCICRecord: Modified context %d\n", cic));
        }
      error = 0;
    }
    else
    {
//          	BSSAP_Alarm_CCITT(5133,__FILE__,__LINE__,"dpc %d cic  %d msgtype %d",DPC,Cic,msgType);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0820, ID :: D0830,
*                        ID :: D0840, ID :: D1060
*/

/*It will nor work in case of Redundancy*/
ITS_UINT
BSSAP_CicDB::GetCICRecordCount()
{
    ITS_UINT size = 0;

    BSSAP_DEBUG(("BSSAP_CicDB: GetCICRecordCount\n"));

    DSM_TableGetSize(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT, &size);

    return (size);
}

