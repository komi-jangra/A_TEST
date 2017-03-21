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
 *  ID: $Id: bssap_map.cpp,v 1.22 2008/04/21 05:24:59 bsccs2 Exp $
 *
 * LOG: $Log: bssap_map.cpp,v $
 * LOG: Revision 1.22  2008/04/21 05:24:59  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.20  2008/03/25 09:11:40  amaresh.prasad
 * LOG: Bug fixing  2481 & Alarm Handelling
 * LOG:
 * LOG: Revision 1.19  2008/03/18 07:54:37  amaresh.prasad
 * LOG: Updated for BLO & UBL
 * LOG:
 * LOG: Revision 1.18  2008/03/17 23:10:27  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.17  2008/03/17 22:38:17  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.16  2008/03/17 09:43:24  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.15  2008/03/17 09:30:46  amaresh.prasad
 * LOG: Updated BlockReq from App to pass towards Peer.
 * LOG:
 * LOG: Revision 1.14  2008/02/26 04:48:31  bsccs2
 * LOG: Changed by Amaresh in ResetCktInd function
 * LOG:
 * LOG: Revision 1.13  2008/02/19 00:26:25  ankur.sharda
 * LOG: Changed for Decoder
 * LOG:
 * LOG: Revision 1.12  2008/02/15 10:42:18  amaresh.prasad
 * LOG: Add ClearRequest handelling
 * LOG:
 * LOG: Revision 1.11  2008/02/14 04:55:12  amaresh.prasad
 * LOG: Update for Trace of T7
 * LOG:
 * LOG: Revision 1.10  2008/02/01 02:41:18  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.9  2008/02/01 04:27:13  amaresh.prasad
 * LOG: Updated for CGB,CGBA,CGU,CGUA & all other messages with abnormal case
 * LOG:
 * LOG: Revision 1.4  2007/11/13 05:50:09  amaresh.prasad
 * LOG: Update Handover for Clear command
 * LOG:
 * LOG: Revision 1.3  2007/11/08 08:05:31  amaresh.prasad
 * LOG: Updated for Handover
 * LOG:
 * LOG: Revision 1.2  2007/10/30 06:40:00  amaresh.prasad
 * LOG: Updated for Assignment handelling
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/20 09:13:50  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/08/06 06:32:10  amaresh.prasad
 * LOG: Updated for CS2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 03:39:15  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.2.25  2007/01/24 05:58:46  sjaddu
 * LOG: Sending Block to locally blocked CIC after receiving ResetCircuit from
 * LOG: MSC. IssueId:5220
 * LOG:
 * LOG: Revision 1.1.2.24  2006/10/07 12:35:00  sjaddu
 * LOG: Added IMSI_Detach procedure.
 * LOG:
 * LOG: Revision 1.1.2.23  2006/09/27 13:00:16  sjaddu
 * LOG: Fix for not to send Block/Unblock twice to MSC.
 * LOG: Validating crec for NULL in ProcessUnequipCktInd().
 * LOG:
 * LOG: Revision 1.1.2.22  2006/04/20 11:38:17  adutta
 * LOG: No need to cancel timer for Reset
 * LOG:
 * LOG: Revision 1.1.2.21  2006/02/01 09:06:18  adutta
 * LOG: Return success from clear command
 * LOG:
 * LOG: Revision 1.1.2.20  2006/01/17 13:25:04  mkrishna
 * LOG: Few more msg's added in Direction Check
 * LOG:
 * LOG: Revision 1.1.2.19  2006/01/17 07:24:44  mkrishna
 * LOG: Changes in Bug fixes
 * LOG:
 * LOG: Revision 1.1.2.18  2006/01/06 07:06:30  mkrishna
 * LOG: Bug fix
 * LOG:
 * LOG: Revision 1.1.2.17  2006/01/04 09:01:32  mkrishna
 * LOG: CktGroupBlk/Unblk/unequipped cic local state to BLOCK
 * LOG:
 * LOG: Revision 1.1.2.16  2005/12/30 06:59:40  mkrishna
 * LOG: First round of issue fixes
 * LOG:
 * LOG: Revision 1.1.2.15  2005/12/23 17:50:15  adutta
 * LOG: Changed the CIC list logic
 * LOG:
 * LOG: Revision 1.1.2.14  2005/12/13 09:33:40  mkrishna
 * LOG: Memory release should be done after usage
 * LOG:
 * LOG: Revision 1.1.2.13  2005/12/12 08:59:41  mkrishna
 * LOG: Memory leak rectified
 * LOG:
 * LOG: Revision 1.1.2.12  2005/12/05 09:20:54  mkrishna
 * LOG: Modified for pegs, cause value and abnormal blk/unblk msg's
 * LOG:
 * LOG: Revision 1.1.2.11  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.10  2005/10/06 08:33:52  adutta
 * LOG: Taken care of network id
 * LOG:
 * LOG: Revision 1.1.2.9  2005/09/29 07:39:38  adutta
 * LOG: More circuit related procedures added
 * LOG:
 * LOG: Revision 1.1.2.8  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.7  2005/09/06 10:56:32  adutta
 * LOG: Implementation of MAP timers
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/28 18:57:20  adutta
 * LOG: Handover implemented
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/26 20:19:13  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/26 06:50:21  adutta
 * LOG: Handled Bssmap udt messages
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 20:07:37  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
#include <bssap.h>
#include <bssap_map.h>
#include <BSSAP++.h>
#include <bssap_calldb.h>
#include <bssap_cicdb.h>
#include <bssap_error.h>
#include <bssap_interface.h>
#include <bssap_sccphandler.h>
#include <bssap_timer.h>
#include <bssap_pegs.h>
#include <bssap-alarm.h> 
#include <bssap_cfgdb.h>

#ifdef  NO_REDUNDACY
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
#define DSM_TableIterate     DSM_TableIterateLocal
#endif

its::Mutex* BSSAP_Map::mlock;
ResetData rData;
ResetData sData; 
unsigned int RESET_REQ_FLAG = 0;
unsigned int RESET_IND_FLAG = 0;
OverloadData oData;
ITS_BOOLEAN isFirst = ITS_TRUE;
ITS_OCTET arr_status[40];
ITS_OCTET arr_status_flag = 0;
//ITS_OCTET app_blo_flag  = 0; 
//ITS_OCTET app_ubl_flag  = 0; 
ITS_OCTET app_cgb_flag  = 0;
ITS_OCTET app_cgu_flag  = 0;
ITS_OCTET statuscounter = 0;
ITS_OCTET Unbstatuscounter = 0;
ITS_OCTET CGBFlagStatus = 0;
ITS_OCTET CGUFlagStatus = 0;
ITS_OCTET Unbarr_status[40];
ITS_OCTET Unbarr_status_flag = 0;
ITS_OCTET Unbrcvd_arr_status[40];
ITS_OCTET Unbcomp_arr_status[40]; 
ITS_OCTET rcvd_arr_status[40];
ITS_OCTET comp_arr_status[40];
extern ITS_INT  CheckParameters(ITS_OCTET msgDisc,BSSAP_Message* iMsg);
ITS_INT calrefid = 0;
ITS_INT OAM_FLAG = 1;
ITS_INT UnbOAM_FLAG = 1;
ITS_INT ErrBSSAPEncode(BSSAP_Message* mssg, ITS_OCTET* buff, ITS_INT& len);
/* Added by Amaresh for bug id 2557 */
ITS_USHORT resetpcm = 0;
ITS_OCTET  resetts = 0;
/* Added by Amaresh for bug id 2557 */

#define FIX_KEYVALUE 0x50

typedef struct
{

HASH_Table CIC_Table;
ITS_OCTET bscId;

}
Cic_Entry;


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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0820, ID :: D1060
*/
static ITS_INT
SetAllCIC(ITS_POINTER entry, void *in, void *out)
{
    CICData* crec = (CICData*)entry;
    CICData *Crec_Entry =NULL;
    ITS_UINT cic = 0;
    ITS_INT error = 0;
    ITS_BOOLEAN flag = ITS_FALSE;                 
    Cic_Entry *CIC_ENT=(Cic_Entry *)in;
    unsigned int i=*((ITS_UINT*)out);                                                  
    ITS_UINT key=i|FIX_KEYVALUE<<8;
    int ret=0; 
 
    if(CIC_ENT->bscId <0)
    {
        BSSAP_ERROR(("SetAllCIC: Couldn't find NwID \n"));
    }

    if (!crec)
    {
        BSSAP_ERROR(("SetAllCIC: Couldn't find context \n"));                                         
        return (ITS_ENOTFOUND);
    }

   if (crec->nwId == CIC_ENT->bscId)
     {
         if (!flag)
         {
#if 0
           if (crec->timerId)
            {
              // Cancel running timer if any
               BSSAP_Timer t1(crec->timerType);
               t1.CancelUDTTimer(crec->timerId);
               crec->timerId = 0;
            }
#endif
            cic = (crec->nwId << 16) | ((crec->pcm << 5) | (0x1FU & crec->ts));
            Crec_Entry =(CICData *)malloc(sizeof(CICData));
            memcpy(Crec_Entry,crec,sizeof(CICData));


            if (HASH_AddEntry(CIC_ENT->CIC_Table,_CIC_ENT,key,(ITS_POINTER)Crec_Entry)!= ITS_SUCCESS)
            {
                BSSAP_ERROR(("BSSAP_PEG:Add Entry Fail"));
                if(Crec_Entry)
                 {
                      free(Crec_Entry);
                      Crec_Entry=NULL;
 
                 }
              return !ITS_SUCCESS;

            }
            
       #if defined(CCITT)
              BSSAP_DEBUG(("SetAllCIC: PCM %d ,TimeSlot %d \n",crec->pcm,crec->ts));
       #else
              BSSAP_DEBUG(("SetAllCIC: CIC %d \n",((crec->pcm << 5) | (0x1FU & crec->ts))));
       #endif
         }
           (*(ITS_UINT *)out)+=1;
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0390, ID :: D1060
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
*       checking message direction for only MAP messages
* INPUT:
*       msg Type, up
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if done successfully
*       Error, if not matching
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0390, ID :: D1060
*/
ITS_INT
BSSAP_Map::DirectionCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: DirectionCheck\n"));                     
    if (up)
    {
        BSSAP_DEBUG(("DirectionCheck: Down (MSC -> BSS) event\n"));                                   
        switch (evId)
        {
            case BSSAP_MSG_CIPHER_MODE_CMD:
            case BSSAP_MSG_ASSIGN_REQUEST:
            case BSSAP_MSG_CLEAR_COMMAND:
            case BSSAP_MSG_HANDOVER_REQUEST:
            case BSSAP_MSG_HANDOVER_COMMAND:
            case BSSAP_MSG_CLASSMARK_UPDATE: 
            case BSSAP_MSG_CLASSMARK_REQUEST:
            case BSSAP_MSG_CONFUSION: 
            case BSSAP_MSG_HANDOVER_REQUIRED_REJECT: 
            case BSSAP_MSG_HANDOVER_SUCCEEDED: 
            case BSSAP_MSG_MSC_INVOKE_TRACE: 
            case BSSAP_MSG_LCLS_CONNECT_CONTROL: 
                return (ITS_SUCCESS);

            default:
              break;
        }
    }
    else
    {
        BSSAP_DEBUG(("DirectionCheck: Up (BSS -> MSC) event\n"));                                   
        switch (evId)
        {
            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
            case BSSAP_MSG_CIPHER_MODE_REJECT:
            case BSSAP_MSG_ASSIGN_COMPLETE:
            case BSSAP_MSG_ASSIGN_FAILURE:
            case BSSAP_MSG_CLEAR_COMPLETE:
            case BSSAP_MSG_HANDOVER_REQUIRED:
            case BSSAP_MSG_HANDOVER_FAILURE:
            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
            case BSSAP_MSG_HANDOVER_COMPLETE:
            case BSSAP_MSG_HANDOVER_DETECT:
            case BSSAP_MSG_CLASSMARK_UPDATE: 
            case BSSAP_MSG_LOCATION_UPDATING_REQUEST:
            case BSSAP_MSG_CLEAR_REQUEST: 
            case BSSAP_MSG_HANDOVER_PERFORMED: 
            case BSSAP_MSG_BSS_INVOKE_TRACE: 
            case BSSAP_MSG_QUEUING_INDICATION: 
            case BSSAP_MSG_SAPI_N_REJECT: 
            case BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK: 
            case BSSAP_MSG_LCLS_NOTIFICATION: 
                return (ITS_SUCCESS);

            default:
              break;
        }
    }
    return (!ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       Handover Candidate Response message
* INPUT:
*       mMap, nwid
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
*Amaresh prasad      06-06-2008   VNL-BSC-CS2-HO 
*/

ITS_INT
BSSAP_Map::ProcessHandoverCandidateResponseReq(BSSAP_Message* mMap,
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)

{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverCandidateResponseReq from BSC\n"));
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0440, ID :: D1060
*
* Amaresh Prasad 17-03-08 VNL-BSC-BSSAP-CS2    
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
#if defined(CCITT)
      BSSAP_CRITICAL(("ProcessBlockReq: BlockReq CIC[%d] pcm %d ts %d\n",key,pcm, ts));
#else
      BSSAP_DEBUG(("ProcessBlockReq: BlockReq cic  %d \n", ((pcm << 5) | (0x1FU & ts)) ));
#endif

      crec = cicdb.FetchCICRecord(key,BSSAP_MSG_BLOCK,nwId);
      if (crec)
      {
       if (crec->localState == CIC_ST_BLOCK)
	      {
		     if (crec->statusFlag)
		     {
			    // Before sending Block reset flag to default value
			    crec->statusFlag = ITS_FALSE;                                                      
			    if (crec->timerId)
			    {
				    // Cancel running timer if any
				    BSSAP_Timer t1(crec->timerType);                                              
				    t1.CancelUDTTimer(crec->timerId);
				    crec->timerId = 0;
			    }

			    BSSAP_Timer t(BSSAP_T_1);                                                        

			    ret = t.StartUDTTimer(key, 0, BSSAP_MSG_BLOCK, buff, len,nwId);
			    if (ret == ITS_ETIMERSTARTFAIL)
			    {
				    cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
				    return (ret);
			    }                                                                                 
			    crec->timerId = ret;
			    crec->timerType = BSSAP_T_1;                                                     
			    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);    
			    if (ret != ITS_SUCCESS)
			    {
				    BSSAP_ERROR(("ProcessBlockReq: CIC modification "
							    "failed %d\n", key));
			    }
			    return (ret);
		    }
		    else
		    {
			    BSSAP_DEBUG(("ProcessBlockReq: Block req for already "
						    "blk.\n"));
          crec->app_blo_flag=1;
			    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
			    if (ret != ITS_SUCCESS)
			    {
				    BSSAP_ERROR(("ProcessBlockReq: CIC modification "
							    "failed %d\n", key));
			    }
                            
			  //  app_blo_flag = 1;
			  //  BSSAP_DEBUG(("ProcessBlkReq:Value of app_blo_flag  %d\n",app_blo_flag));
			    /* return (!ITS_SUCCESS); */
			    return (ITS_SUCCESS); //Changed by Amaresh 17-03-08 as requirement of ResetCkt
		    }
	     }
     else
	     {
		    if (crec->timerId)
		    {
			    // Cancel running timer if any
			    BSSAP_Timer t1(crec->timerType);                                                  
			    t1.CancelUDTTimer(crec->timerId);
			    crec->timerId = 0;
		    }

		    BSSAP_Timer t(BSSAP_T_1);
		    ret = t.StartUDTTimer(key, 0, BSSAP_MSG_BLOCK, buff, len, nwId);
		    if (ret == ITS_ETIMERSTARTFAIL)
		    {
			    cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);  
			    return (ret);
		    }
		    crec->localState = CIC_ST_BLOCK;
		    crec->timerId = ret;
		    crec->timerType = BSSAP_T_1;
        crec->app_blo_flag=1;
		    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
		    if (ret != ITS_SUCCESS)
		    {
         		    BSSAP_ERROR(("ProcessBlockReq: CIC modification "
						    "failed %d\n", key));
		    }
	    }
     }
    else
     {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessBlockReq: invalid pcm %d timelsot %d\n",
                                                                     pcm, ts));
#else
            BSSAP_ERROR(("ProcessBlockReq: invalid cic %d \n",((pcm << 5) | (0x1FU & ts))));
#endif
					/*  BSSAP_Alarm_CCITT(5141,__FILE__,__LINE__,"PCM  %d,TimeSlot %d",pcm,ts);*/ 	
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0470, ID :: D1060
*
* Amaresh Prasad 10-01-08 VNL-BSC-BSSAP-CS2  
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
#if defined(CCITT)

		BSSAP_DEBUG(("ProcessUnBlockReq: UnBlockReq pcm %d slot %d\n", pcm,ts));
#else
		BSSAP_DEBUG(("ProcessUnBlockReq: UnBlockReq cic %d \n", (pcm << 5) | (0x1FU & ts)));
#endif

		crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNBLOCK,nwId);
		if (crec)
		{
			if (crec->localState == CIC_ST_BLOCK)
			{
				if (crec->timerId)
				{
					// Cancel running timer if any
					BSSAP_Timer t1(crec->timerType);
					t1.CancelUDTTimer(crec->timerId);
					crec->timerId = 0;
				}
				BSSAP_Timer t(BSSAP_T_1);
				ret = t.StartUDTTimer(key, 0, BSSAP_MSG_UNBLOCK, buff,len, nwId);
				if (ret == ITS_ETIMERSTARTFAIL)
				{
					cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
					return (ret);
				}
				crec->localState = CIC_ST_UNBLK;
				crec->timerId = ret;
				crec->timerType = BSSAP_T_1;
				crec->app_ubl_flag = 1; 
				ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
				if (ret != ITS_SUCCESS)
				{
					BSSAP_ERROR(("ProcessUnBlockReq: CIC modification "
								"failed %d\n", key));
				}
				return (ret);
			}
			else
			{
				if (crec->statusFlag)
				{
					// Before sending UnBlock reset flag to default value
					crec->statusFlag = ITS_FALSE;                                                 
					if (crec->timerId)
					{
						// Cancel running timer if any
						BSSAP_Timer t1(crec->timerType);                                              
						t1.CancelUDTTimer(crec->timerId);
						crec->timerId = 0;
					}
					BSSAP_Timer t(BSSAP_T_1);                                                        
					ret = t.StartUDTTimer(key, 0, BSSAP_MSG_UNBLOCK, buff,len, nwId);
					if (ret == ITS_ETIMERSTARTFAIL)
					{
						cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
						return (ret);
					}                                                                                 
					crec->timerId = ret;
					crec->timerType = BSSAP_T_1;                                                      
				  crec->app_ubl_flag = 1; 
					ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
					if (ret != ITS_SUCCESS)
					{
						BSSAP_ERROR(("ProcessUnBlockReq: CIC modification "
									"failed %d\n", key));
					}
					return (ret);
				}
				else
				{
					BSSAP_ERROR(("ProcessUnBlockReq: UnBlock for unblk cic\n"));
					ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
					if (ret != ITS_SUCCESS)
					{
						BSSAP_ERROR(("ProcessUnBlockReq: CIC modification "
									"failed %d\n", key));
					}
					return (!ITS_SUCCESS);
				}
			}
		}
		else
		{
#if defined(CCITT)
			BSSAP_ERROR(("ProcessUnBlockReq: invalid pcm %d timelsot %d\n",pcm, ts));
#else
			BSSAP_ERROR(("ProcessUnBlockReq: invalid cic %d \n",((pcm << 5) | (0x1FU & ts))));
#endif
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0520, ID :: D1060
*
* Amaresh Prasad 31-01-08 VNL-BSC-BSSAP-CS2    Multiple Reset Req
*/
ITS_INT
BSSAP_Map::ProcessResetReq(BSSAP_Message* mMap,
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)
{
    ITS_INT ret = 0;
    //rData.timerId = 0;
    BSSAP_CALL_CTXT ctxt; 
    BSSAP_Call* call = NULL;
    CICData* Hashcrec=NULL;
    CICData* DSMcrec=NULL;
    ITS_UINT cic = 0;
    ITS_INT error = 0;
    Cic_Entry CIC_Ent;
    int i=1;
    ITS_UINT key;
    ITS_UINT KEY_Limit=1;

    CIC_Ent.CIC_Table=HASH_CreateTable();
    CIC_Ent.bscId=nwId;

    if(RESET_REQ_FLAG== 0)
    {
       rData.timerId = 0;
       RESET_REQ_FLAG=1;
    }
 
    BSSAP_Timer t(BSSAP_T_4);

    /* Added by Amaresh  if multiple time come 31-01-08 */
    if( rData.timerId)
        {
           ret = t.CancelUDTTimer(rData.timerId);
           rData.timerId = 0;
        }
    /* Addition completed by Amaresh if multiple time come 31-01-08*/                                      

    BSSAP_DEBUG(("BSSAP_Map: ProcessResetReq\n"));
    //    DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT,
    //                     NULL, NULL, SetAllCIC);
    rData.timerId = t.StartUDTTimer(0, 0, BSSAP_MSG_RESET, buff, len, nwId);           
    if (rData.timerId == ITS_ETIMERSTARTFAIL)
    {
        return (!ITS_SUCCESS);
    }

    BSSAP_DEBUG(("2.BSSAP_Map: ProcessResetReq\n"));
    DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT,&CIC_Ent,&KEY_Limit,SetAllCIC);    
    BSSAP_DEBUG(("3.BSSAP_Map: ProcessResetReq\n"));
    for(i=1;i<=KEY_Limit;i++)
      {
    BSSAP_DEBUG(("5.BSSAP_Map: ProcessResetReq\n"));
        key=(i|FIX_KEYVALUE<<8);

          if(HASH_FindEntry(CIC_Ent.CIC_Table,_CIC_ENT,key,(ITS_POINTER *)&Hashcrec)==ITS_SUCCESS)          
           {
    BSSAP_DEBUG(("6.BSSAP_Map: ProcessResetReq\n"));
              cic = (Hashcrec->nwId << 16) | ((Hashcrec->pcm << 5) | (0x1FU & Hashcrec->ts)); 
              DSMcrec=(CICData *) DSM_Find(DSM_SccpFtGroupId,DSM_TABLE_BSSAP_CIC_CTXT,(ITS_OCTET *)&cic,sizeof(ITS_UINT),&error);                        if (error != ITS_SUCCESS)
               {
                  BSSAP_ERROR(("SetAllCIC: Couldn't commit context %d\n", cic));
                  return (error);
               }
                DSMcrec->callState = CALL_ST_IDLE;
                DSMcrec->localState = CIC_ST_UNBLK;
                DSMcrec->remoteState = CIC_ST_UNBLK;

                if (DSMcrec->timerId)
                {
                 // Cancel running timer if any
                    BSSAP_Timer t1(DSMcrec->timerType);
                    t1.CancelUDTTimer(DSMcrec->timerId);
                    DSMcrec->timerId = 0;
                }

                error = DSM_Commit(DSM_SccpFtGroupId,DSM_TABLE_BSSAP_CIC_CTXT,(ITS_OCTET *)&cic,sizeof(ITS_UINT),DSMcrec);
                if (error != ITS_SUCCESS)
                 {
                    BSSAP_ERROR(("SetAllCIC: Couldn't commit context %d\n", cic));


                    return (error);
                 }
                else
                 {
                   BSSAP_DEBUG(("SetAllCIC: Modified context %d\n", cic));
                 }

             if(Hashcrec)
             {
                free(Hashcrec);
                Hashcrec=NULL;
             }
           }
       }/*end of for key*/
    
    BSSAP_DEBUG(("4.BSSAP_Map: ProcessResetReq\n"));
      HASH_DeleteTable(CIC_Ent.CIC_Table);

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessResetAckReq(BSSAP_Message* mMap,
                           ITS_OCTET* buff,
                           ITS_INT len,
                           ITS_OCTET nwId)
{
    ITS_INT ret = 0;                                                                        
    BSSAP_DEBUG(("BSSAP_Map: ProcessResetAckReq\n"));                                  
    BSSAP_Timer t(BSSAP_T_13);                                                                      
    ret = t.CancelUDTTimer(sData.timerId);
    sData.timerId = 0;                                                                              
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0540, ID :: D1060
*
* Amaresh Prasad 01-04-08 Fix Bug 2557,1647  VNL-BSC-BSSAP-CS2
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

        /* Added by Amaresh for bug id 2557 as on dated 01-04-08*/
	      resetpcm = pcm;
				resetts = ts; 	
       /* Added by Amaresh for bug id 2557 as on dated 01-04-08 */

        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
 #if defined(CCITT)
        BSSAP_DEBUG(("ProcessResetCktReq: pcm %d slot %d\n", pcm,ts));
 #else
        BSSAP_DEBUG(("ProcessResetCktReq: cic %d \n", ((pcm << 5) | (0x1FU & ts))));
 #endif

        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_RESET_CIRCUIT,nwId);			
        if (crec)
	{
		if (crec->timerId)
		{
			// Cancel running timer if any
			BSSAP_Timer t1(crec->timerType);                                                    
			t1.CancelUDTTimer(crec->timerId);
			crec->timerId = 0;
		}
		BSSAP_Timer t(BSSAP_T_19);
		ret = t.StartUDTTimer(key, 0, BSSAP_MSG_RESET_CIRCUIT, buff,
				len, nwId);
		if (ret == ITS_ETIMERSTARTFAIL)
		{
			cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT);
			return (ret);
		}

		crec->timerId = ret;
		crec->timerType = BSSAP_T_19;
		crec->callState = CALL_ST_IDLE;

		/*Fix Bug 1647 by Amaresh the CIC state is Unblock not to be done*/
		/*  crec->localState = CIC_ST_UNBLK;
		    crec->remoteState = CIC_ST_UNBLK;   */
		/*Fix Bug 1647 by Amaresh the CIC state is Unblock not to be done*/

		ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_ERROR(("ProcessResetCktReq: CIC modification "
						"failed %d\n", key));
		}
		return (ret);
	}
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessResetCktReq: invalid pcm %d timelsot %d\n",
                                                                     pcm, ts));
#else
            BSSAP_ERROR(("ProcessResetCktReq: invalid cic %d \n",((pcm << 5) | (0x1FU & ts))));
#endif
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0600, ID :: D1060
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
#if defined(CCITT)
		BSSAP_DEBUG(("ProcessUnequipCktReq: pcm %d slot %d nwId %d\n",
					pcm, cicTs, nwId));
#else
		BSSAP_DEBUG(("ProcessUnequipCktReq: cic %d nwId %d\n",((pcm << 5) | (0x1FU & cicTs)),nwId));
#endif
		crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNEQUIPPED_CKT,nwId);
		if (crec)
		{
			if (crec->timerId)
			{
				// Cancel running timer if any
				BSSAP_Timer t1(crec->timerType);                                                   
				t1.CancelUDTTimer(crec->timerId);
				crec->timerId = 0; 
			}                                                                                      
			crec->localState = CIC_ST_BLOCK;                                                          
			ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNEQUIPPED_CKT);                                               
			if (ret != ITS_SUCCESS)
			{
				BSSAP_ERROR(("ProcessUnequipCktReq: CIC modification "
							"failed %d\n", key));
			}
		}
		else
		{
#if defined(CCITT)
			BSSAP_ERROR(("ProcessUnequipCktReq: invalid pcm %d timelsot %d"
						"nwId %d\n", pcm, cicTs, nwId));
#else
			BSSAP_ERROR(("ProcessUnequipCktReq: invalid cic %d  nwId %d\n",((pcm << 5) | (0x1FU & cicTs)),nwId));
#endif

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
#if defined(CCITT)
				BSSAP_DEBUG(("ProcessUnequipCktReq: pcm %d slot %d "
							"nwId %d\n", pcm, ts, nwId));                           
#else 
				BSSAP_DEBUG(("ProcessUnequipCktReq:cic %d  nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));                            
#endif
				crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNEQUIPPED_CKT,nwId);
				if (crec)
				{
					if (crec->timerId)
					{
						// Cancel running timer if any
						BSSAP_Timer t1(crec->timerType);                            
						t1.CancelUDTTimer(crec->timerId);
						crec->timerId = 0;
					}                                                                  
					crec->localState = CIC_ST_BLOCK;                              
					ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNEQUIPPED_CKT);
					if (ret != ITS_SUCCESS)
					{
						BSSAP_ERROR(("ProcessUnequipCktReq: CIC modification "
									"failed %d\n", key));
					}
				}
				else
				{
#if defined(CCITT)
					BSSAP_ERROR(("ProcessUnequipCktReq: invalid pcm %d "
								"timelsot %d nwId %d\n", pcm, ts, nwId));
 #else
					BSSAP_ERROR(("ProcessUnequipCktReq: invalid cic %d nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));
#endif
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0600, ID :: D1060
*
* Amaresh Prasad 15-01-08 VNL-BSC-BSSAP-CS2
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
    ITS_OCTET  startTS = 0,l = 0;
    ITS_OCTET  ts = 0, cicTs = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
    ITS_OCTET stat_counter = 0;
    bzero(arr_status,40);                                                                                                                                          
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupBlkReq\n"));                               
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);                             
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        cicTs = startTS =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & cicTs));
#if defined(CCITT) 
        BSSAP_DEBUG(("ProcessCktGroupBlkReq: pcm %d slot %d "
                              "nwId %d\n", pcm, startTS, nwId));
#else
        BSSAP_DEBUG(("ProcessCktGroupBlkReq: cic %d slot %d\n", ((pcm << 5) | (0x1FU & startTS)), nwId));
#endif
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);                                            
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(crec->timerType);                                       
                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;
            }                                                                          
            BSSAP_Timer t(BSSAP_T_20);                                              
            ret = t.StartUDTTimer(key, 0, BSSAP_MSG_CKT_GROUP_BLOCK, buff,
                                                           len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
                cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
                return (ret);
            }
            crec->timerId = ret;
            crec->timerType = BSSAP_T_20;
            crec->localState = CIC_ST_BLOCK;
        }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessCktGroupBlkReq: invalid pcm %d timelsot %d "
                         "nwId %d\n", pcm, ts, nwId));
#else
            BSSAP_ERROR(("ProcessCktGroupBlkReq: invalid cic %d nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                            BSSAP_MSG_CKT_GROUP_BLOCK, pcm, ts);
            return (!ITS_SUCCESS);
        }                                                                              
        ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_DEBUG(("ProcessCktGroupBlkReq:CIC Modify failed %d\n", key));
            return (ret);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupBlkReq: CIC ie not found\n"));                 
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
            arr_status[stat_counter] = flag;
					  stat_counter++;

            if (flag && (cicTs != ts))
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));                                     
                BSSAP_DEBUG(("ProcessCktGroupBlkReq: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));                                          
                BSSAP_DEBUG(("ProcessCktGroupBlkReq: cic %d nwId %d\n",((pcm << 5) | (0x1FU & ts)), nwId));                                          

                crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
                if (crec)
                {
                    crec->localState = CIC_ST_BLOCK;                                 
                    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
                    if (ret != ITS_SUCCESS)
                    {
                        BSSAP_DEBUG(("ProcessCktGroupBlkReq: CIC Modify "
                                     "failed %d\n", key));
                    }
                }
                else
                {
#if defined(CCITT)
                    BSSAP_ERROR(("ProcessCktGroupBlkReq: invalid pcm %d "
                                  "timelsot %di nwId %d\n", pcm, ts, nwId));
#else
                    BSSAP_ERROR(("ProcessCktGroupBlkReq: invalid cic %d  nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));
#endif
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

     app_cgb_flag = 1;
     BSSAP_DEBUG(("ProcessCktGroupBlkReq:Value of app_cgb_flag  %d\n",app_cgb_flag));

     arr_status_flag = 1;
     BSSAP_DEBUG(("ProcessCktGroupBlkReq:Value of arr_status_flag  %d\n",arr_status_flag));

     for(l = 0;l<stat_counter;l++)
     {
         //printf("%d status array conents are \n",arr_status[l]); 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0490, ID :: D1060
*
* Amaresh Prasad 15-01-08 VNL-BSC-BSSAP-CS2
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
    ITS_OCTET  startTS = 0, l = 0;
    ITS_OCTET  ts = 0, cicTs = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0;
    ITS_OCTET stat_counter = 0;
    bzero(Unbarr_status,40);
                                                                                 
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupUnblkReq\n"));                           
 
    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);                           
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        cicTs = startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & cicTs));                          
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
        if (crec)
        {
            if (crec->timerId)
            {
                // Cancel running timer if any
                BSSAP_Timer t1(crec->timerType);                                      
                t1.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;
            }                                                                        
            BSSAP_Timer t(BSSAP_T_20);                                            
            ret = t.StartUDTTimer(key, 0, BSSAP_MSG_CKT_GRP_UNBLOCK, buff,len, nwId);
            if (ret == ITS_ETIMERSTARTFAIL)
            {
                cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
                return (ret);
            }
            crec->timerId = ret;
            crec->timerType = BSSAP_T_20;
        }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessCktGroupUnblkReq: invalid pcm %d timelsot %d "
                         "nwId %d\n", pcm, ts, nwId));
#else
            BSSAP_ERROR(("ProcessCktGroupUnblkReq: invalid cic %d nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                          BSSAP_MSG_CKT_GRP_UNBLOCK, pcm, ts);
            return (!ITS_SUCCESS);
        }                                                                            

        crec->localState = CIC_ST_UNBLK;
	ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_DEBUG(("ProcessCktGroupUnblkReq:CIC Modify failed %d\n",key));
            return (ret);
        }
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
            Unbarr_status[stat_counter] = flag;
            stat_counter++;

            if (flag && (cicTs != ts))
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts)); 
#if defined(CCITT)
                BSSAP_DEBUG(("ProcessCktGroupUnblkReq: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));                                
#else 
                BSSAP_DEBUG(("ProcessCktGroupUnblkReq: cic %d nwId %d\n",((pcm << 5) | (0x1FU & ts)), nwId));                                 
#endif

                crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
                if (crec)
                {
                    crec->localState = CIC_ST_UNBLK;                                   
                    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
                    if (ret != ITS_SUCCESS)
                    {
                         BSSAP_DEBUG(("ProcessCktGroupUnblkReq: CIC Modify "
                                     "failed %d\n", key));
                    }
                }
                else
                {
#if defined(CCITT)
                    BSSAP_ERROR(("ProcessCktGroupUnblkReq: invalid pcm %d "
                                  "timelsot %di nwId %d\n", pcm, ts, nwId));
#else
                    BSSAP_ERROR(("ProcessCktGroupUnblkReq: invalid cic %d  nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));
#endif
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

   app_cgu_flag = 1;
	 BSSAP_DEBUG(("ProcessCktGroupUnblkReq:Value of app_cgu_flag  %d\n",app_cgu_flag));

	 Unbarr_status_flag = 1;
	 BSSAP_DEBUG(("ProcessCktGroupUnblkReq:Value of Unbarr_status_flag  %d\n",Unbarr_status_flag));

   for(l = 0;l<stat_counter;l++)
    {
       //printf("%d status array conents are \n",Unbarr_status[l]);
    }
    return (ret);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0550, ID :: D1060
* venkat    23-01-2007   
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
    ITS_BOOLEAN isCICLocallyBlkd = ITS_FALSE;
 
    BSSAP_DEBUG(("BSSAP_Map: ProcessResetCktInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        BSSAP_DEBUG(("ProcessResetCktInd: pcm %d slot %d\n", pcm, ts));
        BSSAP_DEBUG(("ProcessResetCktInd: cic %d \n", ((pcm << 5) | (0x1FU & ts))));
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_RESET_CIRCUIT,nwId);
        if (crec)
	{
		if (crec->timerId)
		{
			// Cancel running timer if any
			BSSAP_Timer t1(crec->timerType);                                      
			t1.CancelUDTTimer(crec->timerId);
			crec->timerId = 0;
		}
		if(crec->localState == CIC_ST_BLOCK)
		{
			isCICLocallyBlkd = ITS_TRUE;
		}
		if(isCICLocallyBlkd == ITS_TRUE)
		{
			crec->callState = CALL_ST_IDLE;
			crec->localState = CIC_ST_BLOCK;
			crec->remoteState = CIC_ST_UNBLK;            
#if defined(CCITT) 
			BSSAP_ERROR(("ProcessResetCktInd: CIC[%d] Locally Blocked: set cic callState = CALL_ST_IDLE"
						" pcm:%d, ts:%d",key, pcm, ts));
#endif
		}
		else
		{
			crec->callState = CALL_ST_IDLE;
			crec->localState = CIC_ST_UNBLK;
			crec->remoteState = CIC_ST_UNBLK;
			BSSAP_CRITICAL(("ProcessResetCktInd: CIC[%d] not  Locally Blocked: set cic callState = CALL_ST_IDLE"" pcm:%d, ts:%d",key, pcm, ts));
		}
		ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessResetCktInd:CIC Modify failed %d\n", key));
			return (ret);
		}
	}
        else
        {
#if defined(CCITT) 
            BSSAP_ERROR(("ProcessResetCktInd: invalid pcm %d ts %d\n",pcm, ts));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                         BSSAP_MSG_RESET_CIRCUIT, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
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
#if defined(CCITT)
        BSSAP_DEBUG(("ProcessResetCktAckInd: pcm %d slot %d\n", pcm, ts));
#endif
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_RESET_CIRCUIT_ACK,nwId);
        if (crec)
        {
            if (crec->timerId)
            {
                BSSAP_Timer t(crec->timerType);
                t.CancelUDTTimer(crec->timerId);
                crec->timerId = 0;
                ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT_ACK);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessResetCktAckInd:CIC Modify failed %d\n", key));
			return (ret);
		}
                return (ret);
            }
            else
            {
                if (mMap->GetMsgType() == BSSAP_MSG_RESET_CIRCUIT_ACK)
                {
                    BSSAP_ERROR(("ProcessResetCktAckInd: Reset Ckt. Ack" 
                                 " indication for idle cic\n")); 
                    cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT_ACK);
                    return (!ITS_SUCCESS);
                }
                ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT_ACK);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessResetCktAckInd:CIC Modify failed %d\n", key));
			return (ret);
		}
            }
        }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessResetCktAckInd: invalid pcm %d ts %d\n",
                                                                     pcm, ts));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                         BSSAP_MSG_RESET_CIRCUIT_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);

            return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0590, ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessUnequipCktInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0, range = 0;
    ITS_OCTET  ts = 0, cicTs = 0, flag = 0;
    ITS_OCTET startTS = 0;
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
#if defined(CCITT) 
        BSSAP_DEBUG(("ProcessUnequipCktInd: pcm %d slot %d nwId %d\n",
                                          pcm, cicTs, nwId));                                        
#else 
        BSSAP_DEBUG(("ProcessUnequipCktInd: cic %d  nwId %d\n",
                                         ((pcm << 5) | (0x1FU & cicTs)), nwId));                                         
#endif
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNEQUIPPED_CKT,nwId);
        if (crec)
        { 
            if (crec && crec->timerId)
            {
               // Cancel running timer if any
               BSSAP_Timer t1(crec->timerType);                                       
               t1.CancelUDTTimer(crec->timerId);
               crec->timerId = 0;
            }                                                                        
            crec->remoteState = CIC_ST_BLOCK;                                       
            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNEQUIPPED_CKT);                                                    
            if (ret != ITS_SUCCESS)
            {
                BSSAP_ERROR(("ProcessUnequipCktInd: CIC modification failed %d\n", key));
            }
        }
        else
        {
            return !ITS_SUCCESS;
        }              
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
#if defined(CCITT) 
                BSSAP_DEBUG(("ProcessUnequipCktInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));                                               
#else 
                BSSAP_DEBUG(("ProcessUnequipCktInd: cic %d "
                              "nwId %d\n", ((pcm << 5) | (0x1FU & ts)), nwId));                                                
#endif
                crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNEQUIPPED_CKT,nwId);
                if (crec)
                {
                    if (crec->timerId)
                    {
                        // Cancel running timer if any
                        BSSAP_Timer t1(crec->timerType);                              
                        t1.CancelUDTTimer(crec->timerId);
                        crec->timerId = 0;
                    }                                                               
                    crec->remoteState = CIC_ST_BLOCK;                                 
                    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNEQUIPPED_CKT);                           
                    if (ret != ITS_SUCCESS)
                    {
                        BSSAP_ERROR(("ProcessUnequipCktInd: CIC modification failed %d\n", key));
                    }
                }
                else
                {
#if defined(CCITT)
                    BSSAP_ERROR(("ProcessUnequipCktInd: invalid pcm %d "
                                  "timelsot %d nwId %d\n", pcm, ts, nwId));
#endif
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessResetAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = 0;   
    BSSAP_DEBUG(("BSSAP_Map: ProcessResetAckInd\n"));
    BSSAP_Timer t(BSSAP_T_4);
    ret = t.CancelUDTTimer(rData.timerId);
    rData.timerId = 0;
/*Patch Unable to cancle UDT timer so by default returning it success Start */
    return (ITS_SUCCESS);
/*Patch Unable to cancle UDT timer so by default returning it success End*/
   /* return (ret);*/
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0530, ID :: D1060
*
*	Amaresh Prasad 16-04-08 Bugid 2557 VNL-BSC-CS2	
*/
ITS_INT
BSSAP_Map::ProcessResetInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
	ITS_INT ret = 0;
	BSSAP_CALL_CTXT ctxt; 
	BSSAP_Call* call = NULL;
	//sData.timerId = 0;
	ITS_UINT key = 0;
	CICData* crec = NULL;
	BSSAP_CicDB cicdb;
	BSSAP_DEBUG(("BSSAP_Map: ProcessResetInd\n"));

  if(RESET_IND_FLAG == 0)
  {
    sData.timerId=0;
    RESET_IND_FLAG=1;
  }
  
 if(resetpcm > 0)
 {
	/* Added by Amaresh for Bugid 2557 as on dated 01-04-08 */
	key = (nwId << 16) | ((resetpcm << 5) | (0x1FU & resetts));
	crec = cicdb.FetchCICRecord(key,BSSAP_MSG_RESET,nwId);
	BSSAP_DEBUG(("Check if ResetCktReq timer in reset from MSC\n"));

	if (crec)
	{
		if (crec->timerId)
		{
			BSSAP_Timer t(crec->timerType);
			t.CancelUDTTimer(crec->timerId);
			crec->timerId = 0;
		}
		ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET);
                if (ret != ITS_SUCCESS)
                {
                     BSSAP_ERROR(("ProcessResetInd: CIC modification failed %d\n", key));
                }

	}
 }

	/* Addition completed by Amaresh for Bugid 2557 as on dated 01-04-08 */
	/* Commented by Amaresh for Bug id 2632 as on dated 16-04-08 */
	/*DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT,
	  NULL, NULL, SetAllCIC);   */

	BSSAP_Timer t(BSSAP_T_13);
	/* Added by Amaresh  if multiple time come 31-01-08 */

	if( sData.timerId)
	{
		ret = t.CancelUDTTimer(sData.timerId);
		sData.timerId = 0;
	}

	/* Addition completed by Amaresh if multiple time come 31-01-08*/
	sData.timerId = t.StartUDTTimer(0, 0, BSSAP_MSG_RESET, 0, 0, nwId);

	if (sData.timerId == ITS_ETIMERSTARTFAIL)
	{
		ret = (!ITS_SUCCESS);
	}
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessOverloadInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS; 
    BSSAP_DEBUG(("BSSAP_Map: ProcessOverloadInd\n"));
    if (isFirst)
    {
        BSSAP_Timer t17(BSSAP_T_17);
        BSSAP_Timer t18(BSSAP_T_18);
        oData.timerId17 = t17.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD, 
                                               0, 0, nwId);
        oData.timerId18 = t18.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD, 
                                               0, 0, nwId);
        if (oData.timerId17 == ITS_ETIMERSTARTFAIL || 
                oData.timerId18 == ITS_ETIMERSTARTFAIL)
        {
             ret = (!ITS_SUCCESS);
        }
        isFirst = ITS_FALSE;
    }
    else
    {
        // T17 still runing so ignore overload
        if ((oData.timerId18) && (oData.timerId17))
        {
            BSSAP_WARNING(("ProcessOverloadInd: Ignoring the Overload Ind\n"));
            delete mMap;
            ret = (!ITS_SUCCESS);
        }
        // T17 stopped and T18 running so lets pass the Overload
        else if ((!oData.timerId17) && (oData.timerId18))
        {
            BSSAP_Timer t18(BSSAP_T_18);
            BSSAP_Timer t17(BSSAP_T_17);
            oData.timerId17 = t17.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD,
                                                   0, 0, nwId);
            ret = t18.CancelUDTTimer(oData.timerId18);
            oData.timerId18 = t18.StartUDTTimer(0, 0, BSSAP_MSG_OVERLOAD, 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0450, ID :: D1060
 Amaresh prasad 24-01-08 Bug id 464 VNL-BSC-CS2 
*/
ITS_INT
BSSAP_Map::ProcessCktGroupBlkInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  startTS = 0;
    ITS_OCTET  ts = 0, cicTs = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0, block_cic_flag = 0;                                                                    
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupBlkInd\n"));                             

    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);                            
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        cicTs = startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & cicTs));                                                                                                                          
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
        if (crec)
        {
            if (crec->remoteState != CIC_ST_BLOCK)
            {
#if defined(CCITT)
                BSSAP_DEBUG(("ProcessCktGroupBlkInd: pcm %d slot %d"
                             " nwId %d\n", pcm, cicTs, nwId)); /* changed ts cicTs by Amaresh */
#endif

                crec->remoteState = CIC_ST_BLOCK;
            }
            else
	    {	

#if defined(CCITT)
		    BSSAP_ERROR(("ProcessCktGroupBlkInd: cic already in Blk state"
					    " pcm %d slot %d nwId %d\n", pcm, cicTs, nwId));/*changed ts cicTs by Amaresh*/
#endif
		    block_cic_flag = 1;//Amaresh for bug id 464	
		    BSSAP_ERROR(("ProcessCktGroupBlkInd: Set counter for remotely blocked cic\n"));
	    }
            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
            if (ret != ITS_SUCCESS)
            {
                 BSSAP_DEBUG(("ProcessCktGroupBlkInd:CIC Modify failed %d\n",key));
                return (ret);
            }
        }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessCktGroupBlkInd:invalid pcm %d ts %d nwId %d\n",
                          pcm, cicTs, nwId)); /* changed ts cicTs by Amaresh */
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                BSSAP_MSG_CKT_GROUP_BLOCK, pcm, cicTs); /* changed ts cicTs by Amaresh */
            err.SendUnEquipCkt(pcm, cicTs, nwId); /* changed ts cicTs by Amaresh */                  
            return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
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
            if (flag && (cicTs != ts))
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));                                  
#if defined(CCITT) 
                BSSAP_DEBUG(("ProcessCktGroupBlkInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));                                                                                                                     
#endif
                crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,nwId);
                if (crec)
		{
			if (crec->remoteState != CIC_ST_BLOCK)
			{
				crec->remoteState = CIC_ST_BLOCK;                                            
			}
			else
			{ 
#if defined(CCITT)                              
				BSSAP_ERROR(("ProcessCktGroupBlkIndfor already remotely  block: pcm %d slot %d " "nwId %d\n", pcm, ts, nwId));
#endif
				/* Added by Amaresh for bug id 464 Block by Amaresh
				   for multiple sending of CGBA by BSSAP stack Send Ckt Group Block Ack for already block cic */
				block_cic_flag = 1;
				BSSAP_ERROR(("ProcessCktGroupBlkInd: Set counter for remotely blocked cic\n"));
				/* Addition completed  by Amaresh for bug id 464 */
				//  we are not returning back from here.. bcos more
				//  cic's needs to be checked

			}
			ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
			if (ret != ITS_SUCCESS)
			{
		             BSSAP_DEBUG(("ProcessCktGroupBlkInd: CIC Modify failed %d\n", key));
                             return ret;
			}
		}
                else
                 {
#if defined(CCITT)                              
                     BSSAP_ERROR(("ProcessCktGroupBlkInd: invalid pcm %d "
                                  "ts %d nwId %d\n", pcm, ts, nwId));
#endif
                     bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL,
                                              BSSAP_EUNEQUIPCKT,
                                              BSSAP_MSG_CKT_GROUP_BLOCK,
                                               pcm, ts);
                     err.SendUnEquipCkt(pcm, ts, nwId);
                 }
             }

       }
	       /* Added by Amaresh for bug id 464 if BSC is ckt slave 
             donot send CGBA message towards MSC &if Ckt master send CGBA message towards MSC */
	    if(block_cic_flag == 1)
		   {
          	ret = err.SendCktGroupBlkAck(mMap, pcm, startTS, nwId);	 
        		BSSAP_ERROR(("ProcessCktGroupBlkInd: Sending Ckt group block ack for remotely blocked cic\n"));
         		block_cic_flag = 0;
        		return (!ITS_SUCCESS); //not to send to BSC-APP
         	 /* Addition completed  by Amaresh for bug id 464 */
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
*PURPOSE:
*       Processing of CktGroupBlkAckInd
* INPUT:
*       call object, cause
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if done successfully
*       Error, if error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad   07-12-2007  IMR-BSS-BSSAP-CS2
*/

ITS_INT
BSSAP_Map::ProcessCktGroupBlkAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT result = ITS_SUCCESS;
    ITS_OCTET counter = 0;
    ITS_OCTET stat_counter = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET *ublock_ts,*block_cgb;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0, l = 0;
    ITS_OCTET CGBFlag = 0;
    ITS_OCTET  startTS = 0, cicTs = 0;
    ITS_OCTET my_array[100];
    ITS_INT range = 0, flag = 0, locally_ublock_cic_flag = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ublock_ts = &my_array[0]; 
    bzero(rcvd_arr_status,40);   
    bzero(comp_arr_status,40);
    block_cgb = &comp_arr_status[0];
    ITS_OCTET send_unblock_counter = 0;
		bzero(Unbarr_status,40);
    ITS_OCTET normal_counter = 0;  
 
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupBlkAckInd\n"));

    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    flag = ((BSSAP_CktIDCodeList*)cicIe)->GetStatusBit(0);
    /*arr_status_flag = 0;*//* Change Global variable */

    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = startTS = cicTs = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_BLK_ACK,nwId);
        if (crec)
        {
            if (crec->localState == CIC_ST_BLOCK)
            {
                if (crec->timerId)
                {
                    // Cancel running timer if any
                    BSSAP_Timer t1(crec->timerType);
                    t1.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
#if defined(CCITT)
	            BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Ignore CGBA "
                          "for already block cic pcm %d ts %d "
                          "nwId %d\n", pcm, ts, nwId));
#endif
                }
                else
                {
#if defined(CCITT)
                    BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Ignore CktGroup "
                          "BlkAckInd for already block cic pcm %d ts %d "
                          "nwId %d\n", pcm, ts, nwId));
#endif
                 /*   return (!ITS_SUCCESS);*/
                }
            }
	        else
            {
#if defined(CCITT)
                BSSAP_ERROR(("ProcessCktGroupBlkAckInd: BlockAck indicaton "
                "for unblock cic"" pcm %d slot %d nwId %d\n", pcm, ts, nwId));
#endif
                 locally_ublock_cic_flag = locally_ublock_cic_flag+1;
                 my_array[counter] = cicTs = ts;
                 counter = counter+1;
                 /* if CIC is locally block  update global array 14-01-08 */

                 Unbarr_status[send_unblock_counter] = flag;
                 send_unblock_counter++;
                 /* if CIC is locally block  update global array 14-01-08*/
	              /*return (ITS_SUCCESS);*/
            }

        }
        else
 	{
#if defined(CCITT)
            BSSAP_ERROR(("ProcessCktGroupBlkAckInd: invalid pcm %d "
                         "ts %d nwId %d\n", pcm, ts, nwId));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                           BSSAP_MSG_CKT_GRP_BLK_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS);
        }
        ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_BLK_ACK);
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


   clIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST);
   if (clIe)
    {
        range = ((BSSAP_CktIDCodeList*)clIe)->GetRange() + 1;
        range += startTS;

        for (ts = startTS; ts < range; ts++)
        {
            flag = ITS_FALSE;
            flag = ((BSSAP_CktIDCodeList*)clIe)->GetStatusBit(ts - startTS);
            rcvd_arr_status[stat_counter] = flag;
            stat_counter++;
            if (flag && (cicTs != ts))
            {
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
#if defined(CCITT)
                BSSAP_DEBUG(("ProcessCktGroupBlkInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));
#endif
                crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_BLK_ACK,nwId);
		 if (crec)
                 {
                   if (crec->localState == CIC_ST_BLOCK)
                    {
                       if (crec->timerId)
                        {
                         // Cancel running timer if any
                            BSSAP_Timer t1(crec->timerType);
                            t1.CancelUDTTimer(crec->timerId);
                            crec->timerId = 0;
                        }
                        else
                        {
#if defined(CCITT)
                           BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Ignore CktGroup "
                             "BlkAckInd for already block cic pcm %d ts %d "
                               "nwId %d\n", pcm, ts, nwId));
#endif
                            /* return (!ITS_SUCCESS);*/
                        }
                     }
                    else
                     {
#if defined(CCITT)
                          BSSAP_ERROR(("ProcessCktGroupBlkAckInd: BlockAck indicaton "
                          "for unblock cic"" pcm %d slot %d nwId %d\n", pcm, ts, nwId));
#endif
                          my_array[counter] =  ts;
                          counter = counter+1;
                          locally_ublock_cic_flag = locally_ublock_cic_flag+1;
                          /* if CIC is locally block  update global array 14-01-08 */

                          Unbarr_status[send_unblock_counter] = flag;
                          send_unblock_counter++;
                          /* if CIC is locally block  update global array 14-01-08*/
                          /*return (ITS_SUCCESS);*/
                     } 
                      ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_BLK_ACK);
            	      if (ret != ITS_SUCCESS)
                      {
                             BSSAP_DEBUG(("ProcessCktGroupBlkAckInd:CIC Modify " "failed %d\n", key));
                             return (ret);
                      }
                     
                   }
             }
          }

          /* Added by Amaresh for Enhancement TC_022,TC_023 & TC_024*/
					if((locally_ublock_cic_flag == 0) && (counter == 0))
						{
							BSSAP_ERROR(("ProcessCktGroupBlkAckInd: do nothing \n"))
						}
					else
						{
       			 if(locally_ublock_cic_flag == counter)
              	{
   	  							Unbstatuscounter = send_unblock_counter; // update Unbstatuscounter for send CGU
	         				 for(l = 0;l<send_unblock_counter;l++)  
                    {
                        //printf("%d Received CGBA status of UnBlock cic conents are \n",Unbarr_status[l]);
          							BSSAP_DEBUG(("Received CGBA status of UnBlock cic conents are" "%d\n", Unbarr_status[l]));
	      			      }
                  	  Unbarr_status_flag = 1;
                 	    BSSAP_DEBUG(("ProcessCktGroupUnBlkReq:Value of Unbarr_status_flag  %d\n",Unbarr_status_flag));          
                      ret = err.SendCktGroupUnBlk(mMap, pcm, ublock_ts, counter, nwId);
                      BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Sending Ckt group UNBLOCK \n"));
                      locally_ublock_cic_flag = 0;
                      /* Addition completed  by Amaresh for Enhancement TC_022,TC_023 & TC_024 */
              	 }
		         }
      }

    for(l = 0;l<stat_counter;l++)
    {
      // printf("%d Received CGBA status array conents are \n",rcvd_arr_status[l]);
       BSSAP_DEBUG(("Received CGBA status array conents are" "%d\n", rcvd_arr_status[l]));
    }

    if(arr_status_flag == 0)
	   {
         BSSAP_DEBUG(("BSSAP_Map: Abnormal Handle or CktGroupBlkAckInd without send of CGB\n"));
     }
    else
     {
	      for(l = 0;l<statuscounter;l++)
       	if(arr_status[l] == rcvd_arr_status[l])
	       {
          	BSSAP_DEBUG(("ProcessCktGroupBlkAckInd: checking status bit of CGBA to zero\n"));
          	comp_arr_status[l] = 0;
         }
       	else
         {
            	BSSAP_DEBUG(("ProcessCktGroupBlkAckInd:checking status bit of CGBA to one\n"));
            	comp_arr_status[l] = 1;
              CGBFlag = 1;
            	CGBFlagStatus = 1;
            	normal_counter++;
         }
        for(l = 0;l<stat_counter;l++)
          {
            //	printf("%d Compared CGBA status array conents are \n",comp_arr_status[l]);
              BSSAP_DEBUG(("Compared CGBA status array conents are" "%d\n", comp_arr_status[l]));
          }

        if (CGBFlagStatus == 0)
       	{
        	 CGBFlag = 0;
           BSSAP_DEBUG(("Status of CGB FLAG is " "%d\n", CGBFlag));  
       	}
	     else
	      {
          	CGBFlag = 1;
            BSSAP_DEBUG(("Status of CGB FLAG is " "%d\n", CGBFlag));
	      }

       if(CGBFlag == 1)
	      {
         	if(OAM_FLAG == 1)
	         {
              	statuscounter=normal_counter;
               	result = err.SendNormalCktGroupBlk(mMap, pcm, block_cgb,stat_counter,nwId);
                arr_status_flag = 1; /* Change Global variable */
               	BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Send CGB towards MSC\n"));
                OAM_FLAG++;
                /* Update the global array */
                for(l = 0;l<stat_counter;l++)
               	arr_status[l] = comp_arr_status[l];	
          }
	        else
	        {
            	BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Send ALARM report to OAM\n"));
             	BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Set OAM_FLAG & arr_status_flag if CGB is one \n"));
              OAM_FLAG = 1;
              arr_status_flag = 0; /* Change Global variable */
			       	CGBFlagStatus = 0;
        	}
       }
	   else
	     {
        	BSSAP_ERROR(("ProcessCktGroupBlkAckInd: Set OAM_FLAG & arr_status_flag if CGB is zero \n"));
          OAM_FLAG = 1;
          arr_status_flag = 0; /* Change Global variable */
				  CGBFlagStatus = 0;
       }

     }/* end of  else Block arr_status_flag  */
     //   arr_status_flag = 0; /* Change Global variable */ 14/11/08
     /* Added by Amaresh 23-01-08 for not send adnormal message to App */
     if(app_cgb_flag == 1) 
	   {
       	app_cgb_flag = 0;	
        return (ret);
	   }
	  else
	   {
     	return (!ITS_SUCCESS);
	   }
     /* Added by Amaresh 23-01-08 for not send adnormal message to App */
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0500, ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessCktGroupUnblkInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
	ITS_INT ret = ITS_SUCCESS;
	ITS_USHORT pcm = 0;
	ITS_UINT key = 0;
	ITS_OCTET  startTS = 0;
	ITS_OCTET  ts = 0, cicTs = 0;
	BSSAP_CicDB cicdb;
	CICData* crec = NULL;
	const BSSAP_Element* cicIe = NULL;
	const BSSAP_Element* clIe = NULL;
	BSSAP_Error err;
	BSSAP_Interface bssIf;
	BSSAP_CktIDCodeList cicList;
	ITS_INT range = 0, flag = 0, unblock_cic_flag = 0;                                                                             

	BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupUnblkInd\n"));                                           

	cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);                                            
	if (cicIe)
	{
		pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
		cicTs = startTS = ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
		key = (nwId << 16) | ((pcm << 5) | (0x1FU & cicTs));                                                                                         
		crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
		if (crec)
		{
			if (crec->remoteState != CIC_ST_UNBLK)
			{
#if defined(CCITT)
				BSSAP_DEBUG(("ProcessCktGroupUnblkInd: pcm %d slot %d"
							" nwId %d\n", pcm, ts, nwId));
#endif

				crec->remoteState = CIC_ST_UNBLK;
			}
			else
			{
#if defined(CCITT)
				BSSAP_ERROR(("ProcessCktGroupUnblkInd: cic already in Unblk "
							" state pcm %d slot %d nwId %d\n", pcm, ts, nwId));
#endif
				unblock_cic_flag = 1;//Amaresh fix for bug id 466

			} 
			ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
			if (ret != ITS_SUCCESS)
			{
				BSSAP_DEBUG(("ProcessCktGroupUnblkInd: CIC Modify "
							"failed %d\n", key));
				return (ret);
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

			if (flag && (cicTs != ts))
			{
				key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));                                 
#if defined(CCITT)
				BSSAP_DEBUG(("ProcessCktGroupUnblkInd: pcm %d slot %d "
							"nwId %d\n", pcm, ts, nwId));                                         
#endif
				crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,nwId);
				if (crec)
				{
					if (crec->remoteState != CIC_ST_UNBLK)
					{
						crec->remoteState = CIC_ST_UNBLK;                                            
					}
					else
					{
						BSSAP_ERROR(("ProcessCktGroupUnblkInd: cic "
									"already unblock\n"));
						/* Added by Amaresh for bug id 466 */
						/* Block by Amaresh for multiple sending of CGUBA by BSSAP stack*/  
						unblock_cic_flag = 1;
						BSSAP_ERROR(("ProcessCktGroupUnblkInd: Set counter for Unblocked  cic\n"));
					}                                                                                                                                   
					ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
					if (ret != ITS_SUCCESS)
					{
						BSSAP_DEBUG(("ProcessCktGroupUnblkInd: CIC Modify "
									"failed %d\n", key));
						return ret;
					}
				}
				else
				{
#if defined(CCITT)
					BSSAP_ERROR(("ProcessCktGroupUnblkInd: invalid "
								"pcm %d ts %d nwId %d\n", pcm, ts, nwId));
#endif
					bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL,
							BSSAP_EUNEQUIPCKT,
							BSSAP_MSG_CKT_GRP_UNBLOCK,
							pcm, ts);
					err.SendUnEquipCkt(pcm, ts, nwId);
				}
			}
		}

		/* Added by Amaresh for bug id 466 if BSC is ckt slave 
		   donot send CGBA message towards MSC &if Ckt master send CGBA message towards MSC */
		if(unblock_cic_flag == 1)
		{
			// Send Ckt Group Unblock Ack for already block cic
			ret = err.SendCktGroupUnblkAck(mMap, pcm, startTS, nwId);
			BSSAP_ERROR(("ProcessCktGroupUnblkInd: Sending Ckt group UnblockAck for unblock cic\n"));
			unblock_cic_flag = 0;
		}
		/* Addition completed  by Amaresh for bug id 466 */                
	}
	else
	{
		BSSAP_ERROR(("ProcessCktGroupUnblkInd: CIC LIST ie not found\n"));                           
		return (!ITS_SUCCESS);
	}
	return (ret);
}

/*implementation:internal
*PURPOSE:
*       Processing of CktGroupUnblkAckInd
* INPUT:
*       call object, cause
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if done successfully
*       Error, if error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad   01-12-2007  IMR-BSS-BSSAP-CS2
*/
ITS_INT
BSSAP_Map::ProcessCktGroupUnblkAckInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_INT result = ITS_SUCCESS; 
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0, cic_ts = 0,cicTs = 0;
    ITS_OCTET my_array[100];	
    ITS_OCTET *block_ts,*unblock_cgb;
    ITS_OCTET counter = 0;
    ITS_OCTET  startTS = 0,l = 0;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;
    const BSSAP_Element* cicIe = NULL;
    const BSSAP_Element* clIe = NULL;
    BSSAP_Error err;
    BSSAP_Interface bssIf;
    BSSAP_CktIDCodeList cicList;
    ITS_INT range = 0, flag = 0, locally_block_cic_flag = 0;
    block_ts = &my_array[0];
    ITS_OCTET stat_counter = 0;
    ITS_OCTET CGUFlag = 0;
    bzero(Unbrcvd_arr_status,40);    
    bzero(Unbcomp_arr_status,40);
    unblock_cgb = &Unbcomp_arr_status[0];
 
    BSSAP_DEBUG(("BSSAP_Map: ProcessCktGroupUnblkAckInd\n"));

    ITS_OCTET send_block_counter = 0;
    bzero(arr_status,40);

    cicIe = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    flag = ((BSSAP_CktIDCodeList*)cicIe)->GetStatusBit(0);
    ITS_OCTET unbnormal_counter = 0;
	
    if (cicIe)
    {
        pcm = ((BSSAP_CktIDCode*)cicIe)->GetPCMID();
        ts = startTS = cicTs =  ((BSSAP_CktIDCode*)cicIe)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLKING_ACK,nwId);
        if (crec)
        {
            if (crec->localState != CIC_ST_BLOCK)
            {
                if (crec->timerId)
                {
                  	// Cancel running timer if any
                    BSSAP_Timer t1(crec->timerType);
                    t1.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
                }
                else
                {
#if defined(CCITT)
                    BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: Ignore CktGroup "
                          "UnBlkAckInd for already idle cic pcm %d ts %d "
                          "nwId %d\n", pcm, ts, nwId));
#endif
                    /*  return (!ITS_SUCCESS); */
                }
            }
            else
            {
#if defined(CCITT)
                 BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: UnBlockAck indicaton "
                                                    "for block cic"
                             " pcm %d slot %d nwId %d\n", pcm, ts, nwId));
#endif
                 locally_block_cic_flag = locally_block_cic_flag+1;//Amaresh for bug id 465
                 my_array[counter] = cic_ts = ts;
                 counter = counter+1;
                 /* if CIC is locally block  update global array 16-01-08 */
                 arr_status[send_block_counter] = flag;
								 send_block_counter++;

                 /* if CIC is locally block  update global array 16-01-08*/
                 /*return (ITS_SUCCESS);*/
            }
        }
        else
	{
#if defined(CCITT)
            BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: invalid pcm %d "
                         "ts %d nwId %d\n", pcm, ts, nwId));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                  BSSAP_MSG_CKT_GRP_UNBLKING_ACK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS);
        }

        ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLKING_ACK);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_DEBUG(("ProcessCktGroupUnblkAckInd:CIC Modify failed %d\n", key));
            return (ret);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: CIC ie not found\n"));
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
            Unbrcvd_arr_status[stat_counter] = flag;
            stat_counter++;
            if (flag && (cicTs != ts))
            {
#if defined(CCITT)
                key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
                BSSAP_DEBUG(("ProcessCktGroupBlkInd: pcm %d slot %d "
                              "nwId %d\n", pcm, ts, nwId));
#endif
               crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLKING_ACK,nwId);
           	if (crec)
		{
			if (crec->localState != CIC_ST_BLOCK)
			{
				if (crec->timerId)
				{
					// Cancel running timer if any
					BSSAP_Timer t1(crec->timerType);
					t1.CancelUDTTimer(crec->timerId);
					crec->timerId = 0;
				} 
				else
				{
#if defined(CCITT)
					BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: Ignore CktGroup "
								"UnBlkAckInd for already idle cic pcm %d ts %d "
								"nwId %d\n", pcm, ts, nwId));
#endif
					/* return (!ITS_SUCCESS);*/
				}
			}
			else
			{
#if defined(CCITT)
				BSSAP_ERROR(("ProcessCktGroupUnblkAckInd: UnBlockAck indicaton "
							"for block cic "
							" %d ts %d "
							"nwId %d\n", pcm, ts, nwId));
#endif
				my_array[counter] = ts; 
				counter = counter+1;
				locally_block_cic_flag = locally_block_cic_flag+1;//Amaresh for bug id 465

				/* if CIC is locally block  update global array 14-01-08 */
				arr_status[send_block_counter] = flag;
				send_block_counter++;
			}
			/* if CIC is locally block  update global array 14-01-08*/
			ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLKING_ACK);
			if (ret != ITS_SUCCESS)
			{
				BSSAP_DEBUG(("ProcessCktGroupUnblkAckInd:CIC Modify " "failed %d\n", key));
				return (ret);
			}


		}
           }
         }

        /* Added by Amaresh for bug id 465 */
	      if((locally_block_cic_flag == 0) && (counter == 0))
         {
            BSSAP_ERROR(("ProcessCktGroupUnBlkAckInd: do nothing \n"))
         }
        else
        {
           if(locally_block_cic_flag == counter)
               {
               		statuscounter = send_block_counter; //17-01-08 update statuscounter for send CGB
              		for(l = 0;l<send_block_counter;l++) 
                		{ 
                     		 //printf("%d Received CGUBA status of Block cic conents are \n",arr_status[l]);
                  	  	 BSSAP_DEBUG(("Received CGUBA status of Block cic conents are" "%d\n", arr_status[l]));
		                }
                   	arr_status_flag = 1;
                		BSSAP_DEBUG(("ProcessCktGroupBlkReq:Value of arr_status_flag  %d\n",arr_status_flag));	
          	        ret = err.SendCktGroupBlk(mMap, pcm, block_ts, counter, nwId);
                    BSSAP_ERROR(("ProcessCktGroupUnBlkAckInd: Sending Ckt group block for Locally blocked cic\n"));
                    locally_block_cic_flag = 0;
                }
  			}
    }
    /* Addition completed  by Amaresh for bug id 465 */

   for(l = 0;l<stat_counter;l++)
     {
   //    printf("%d Received CGUBA status array conents are \n",Unbrcvd_arr_status[l]);
       BSSAP_DEBUG(("Received CGUBA status array conents are" "%d\n", Unbrcvd_arr_status[l]));
     }
   if(Unbarr_status_flag == 0)
	  {
       BSSAP_DEBUG(("BSSAP_Map: Abnormal Handle or CktGroupUnblkAckInd without send of CGUB\n"));
	  }
	 else
	 {
        //for(l = 0;l<stat_counter;l++) 18-01-08 orig
       	for(l = 0;l<Unbstatuscounter;l++) //18-01-08
         if(Unbarr_status[l] == Unbrcvd_arr_status[l])
         {
              BSSAP_DEBUG(("ProcessCktGroupUnBlkAckInd: checking status bit of CGUBA to zero\n"));
              Unbcomp_arr_status[l] = 0;
         }
        else
        {
             BSSAP_DEBUG(("ProcessCktGroupUnBlkAckInd:checking status bit of CGUBA to one\n"));
             Unbcomp_arr_status[l] = 1;
             CGUFlag = 1;
           	 CGUFlagStatus = 1;
            unbnormal_counter++;
        }
       for(l = 0;l<stat_counter;l++)
        {
          //   printf("%d Compared CGUBA status array conents are \n",Unbcomp_arr_status[l]);
            BSSAP_DEBUG(("Compared CGUBA status array conents are" "%d\n", Unbcomp_arr_status[l]));
        }
       if (CGUFlagStatus == 0)
        {
           CGUFlag = 0;
           BSSAP_DEBUG(("Status of CGU FLAG is " "%d\n", CGUFlag));
        }
       else
        {
           CGUFlag = 1;
           BSSAP_DEBUG(("Status of CGU FLAG is " "%d\n", CGUFlag));
        }
       if(CGUFlag == 1)
        {
          if(UnbOAM_FLAG == 1)
           {
				     Unbstatuscounter = unbnormal_counter;
             result = err.SendNormalCktGroupUnBlk(mMap, pcm, unblock_cgb,stat_counter,nwId);
		         Unbarr_status_flag = 1; /* Change Global variable */
             BSSAP_ERROR(("ProcessCktGroupUnBlkAckInd: Send CGU towards MSC\n"));
             UnbOAM_FLAG++;
            /* Update the global array */
             for(l = 0;l<stat_counter;l++)
             Unbarr_status[l] = Unbcomp_arr_status[l];
           }
          else
           {
              BSSAP_ERROR(("ProcessCktGroupUnBlkAckInd: Send ALARM report to OAM\n"));
	            BSSAP_ERROR(("ProcessCktGroupUnBlkAckInd: Set OAM_FLAG & unbarr_status_flag if CGU is one \n"));   
             	Unbarr_status_flag = 0; /* Change Global variable */
              UnbOAM_FLAG = 1;
             	CGUFlagStatus = 0; 
            }
        }
	    else
	      {
        	 BSSAP_ERROR(("ProcessCktGroupUnBlkAckInd: Set OAM_FLAG & unbarr_status_flag if CGU is zero \n"));
           UnbOAM_FLAG = 1;
           Unbarr_status_flag = 0; /* Change Global variable */         }
           CGUFlagStatus = 0;
        }/* end of  else Unbarr_status_flag  */
         /* Added by Amaresh 24-01-08 for not send adnormal message to App */
        if(app_cgu_flag == 1)
         {
           app_cgu_flag = 0;
           return (ret);
         }
        else
         {
            return (!ITS_SUCCESS);
         }

         /* Added by Amaresh 24-01-08 for not send adnormal message to App */
}

/*implementation:internal
*
* PURPOSE:
*       Handover Candidate Enquire message
* INPUT:
*       mMap, nwid
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
*Amaresh prasad      06-06-2008   VNL-BSC-CS2-HO 
*/
ITS_INT
BSSAP_Map::ProcessHandoverCandidateEnquireInd(BSSAP_Message* mMap, ITS_OCTET nwId)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverCandidateEnquireInd received from MSC\n"));
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0430, ID :: D1060
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
 
#if defined(CCITT)
        BSSAP_DEBUG(("ProcessBlockInd: BlockInd pcm %d ts %d\n", pcm, ts));
#endif

        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_BLOCK,nwId);
        if (crec)
        {
            if (crec->remoteState == CIC_ST_BLOCK)
            {
                BSSAP_ERROR(("ProcessBlockInd: cic already block\n"));

                // Send Block Ack for already block cic
                ret = err.SendBlockAck(pcm, ts, nwId);   
                cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
                return (!ITS_SUCCESS); /* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
            }
            else //CIC_ST_UNBLOCK
            {
                if (crec->timerId)
                {
                    BSSAP_Timer t(crec->timerType);                                                 
                    t.CancelUDTTimer(crec->timerId);
                    crec->timerId = 0;
								}
                crec->remoteState = CIC_ST_BLOCK;
                ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessBlockInd:CIC Modify failed %d\n", key));
			return (ret);
		}
            }
        }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessBlockInd: invalid pcm %d timelsot %d\n",pcm, ts));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                                     BSSAP_MSG_BLOCK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS);  /* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0480, ID :: D1060
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
#if defined(CCITT)
        BSSAP_DEBUG(("ProcessUnBlockInd: UnBlockInd pcm %d slot %d\n",pcm, ts));
#endif
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNBLOCK,nwId);
        if (crec)
        {
            if (crec->remoteState == CIC_ST_BLOCK)
            {
                crec->remoteState = CIC_ST_UNBLK;
                ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessUnBlockInd:CIC Modify failed %d\n", key));
			return (ret);
		}
            }
            else
            {
                BSSAP_WARNING(("ProcessUnBlockInd: cic already unblock\n"));
                // Send UnBlock Ack for already unblock cic
                ret = err.SendUnBlockAck(pcm, ts, nwId);
                cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
                return (!ITS_SUCCESS);
            }
        }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessUnBlockInd: invalid pcm %d timelsot %d\n",pcm, ts));
#endif
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                           BSSAP_MSG_UNBLOCK, pcm, ts);
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
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
    ITS_INT len = 0; //Amaresh
    ITS_OCTET buff[BSSAP_DATA_LEN]; //Amaresh
    BSSAP_CktIDCode cktId;//Amaresh
    BSSAP_Unblock unblk;//Amaresh	
    BSSAP_DEBUG(("BSSAP_Map: ProcessBlockAckInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

#if defined(CCITT)
        BSSAP_DEBUG(("ProcessBlockAckInd: BlockAckInd pcm %d slot %d\n", 
                                                                      pcm, ts));
#endif
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_BLOCK_ACK,nwId);
        if (crec)
	      {
      		if (crec->localState == CIC_ST_BLOCK)
		       {
        		if (crec->timerId)
			       {
      				BSSAP_Timer t(crec->timerType);
      				t.CancelUDTTimer(crec->timerId);
			      	crec->timerId = 0;
       			//	ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
			     	/* Added by Amaresh 18-03-08 for app_blo_flag to 0 */
				    if(crec->app_blo_flag == 1)
				    {
     					crec->app_blo_flag = 0;
		    		  ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
				    	BSSAP_DEBUG(("ProcessBlockAckInd::Value of app_blo_flag  %d\n",crec->app_blo_flag));//18-03-08
					    return (ret);
				    }
			   	 else
				    {
				       ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
					     return (!ITS_SUCCESS);
					     /* Changed 25-03-08 not to send data directly BSC-APP (!ITS_SUCCESS)*/
				    }
			     }
			    else
			     {
				     //ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
#if defined(CCITT)
				     BSSAP_ERROR(("ProcessBlockAckInd: Ignore BlockAckInd "
							"for already block cic pcm %d ts %d\n", pcm , ts));
#endif
				    /* Added by Amaresh 18-03-08 for app_blo_flag to 0 */
				    if(crec->app_blo_flag == 1)
				    {
					     crec->app_blo_flag = 0;
   				     ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
					     BSSAP_DEBUG(("ProcessBlockAckInd::Value of app_blo_flag  %d\n",crec->app_blo_flag));//18-03-08
					     return (ret);
				    }
				   ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
		  	  }
			  return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
		    }
		  else
		    {
#if defined(CCITT)
			    BSSAP_ERROR(("ProcessBlockAckInd: BlockAck indicaton "
						"in unblock state & BSSMAP stack send Unblock message towards MSC for same pcm %d ts %d nwId %d\n",
						pcm, ts, nwId));
#endif
			    //  UnBlock message can be sent to remote by Amaresh for Bugid-459 as on dated 16-11-07
			    // Before sending UnBlock reset flag TRUE value
			    crec->statusFlag = ITS_TRUE;

			    cktId.SetPCMID(pcm);
    			cktId.SetTimeslot(ts);
		    	unblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    			ErrBSSAPEncode(&unblk, buff, len);	
    			if (crec->timerId)
		    	{
			    	// Cancel running timer if any
				    BSSAP_Timer t1(crec->timerType);                                       
				    t1.CancelUDTTimer(crec->timerId);
				     crec->timerId = 0;
			    }
     			BSSAP_Timer t(BSSAP_T_1);                                                    
		    	ret = t.StartUDTTimer(key, 0, BSSAP_MSG_UNBLOCK, buff,len, nwId);
     			if (ret == ITS_ETIMERSTARTFAIL)
		     	{
				    cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
				    return (ret);
			    }

    			crec->timerId = ret;
		    	crec->timerType = BSSAP_T_1;

		    	/*           crec->statusFlag = ITS_TRUE; orginal*/
			    err.SendUnBlock(pcm, ts, nwId); //SPR fix by Amaresh for Bugid-459

			    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK_ACK);
			    if (ret != ITS_SUCCESS)
			    {
				     BSSAP_DEBUG(("ProcessBlockAckInd:CIC Modify failed %d\n", key));
				     return (ret);
			    }
			    /*   return (ret); *//*24-03-08  by Amaresh not to send data BSC-APP */
			    return(!ITS_SUCCESS);/*24-03-08  by Amaresh not to send data BSC-APP Bugid-2481*/                                                                                  

			    //  UnBlock message can be sent to remote by Amaresh for Bugid-459 as on dated 16-11-07

		      }
	      }
        else
        {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessBlockAckInd: invalid pcm %d timelsot %d\n",
                                                                     pcm, ts));
#endif
            /* Added by Amaresh for bug id 2545 as on dated 01-04-08*/
                bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,BSSAP_MSG_BLOCK_ACK, pcm, ts);
            /* Added by Amaresh for bug id 2545 as on dated 01-04-08*/
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS); /* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessBlockAckInd: CIC ie not found\n"));

        return (!ITS_SUCCESS);
    }
    /* Added by Amaresh 24-01-08 for not send adnormal message to App */
   /* Added by Amaresh 24-01-08 for not send adnormal message to App */
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
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
    ITS_INT len = 0;
    ITS_OCTET buff[BSSAP_DATA_LEN]; 
    BSSAP_CktIDCode cktId;
    BSSAP_Block blk;
    BSSAP_Cse cs;
    BSSAP_DEBUG(("BSSAP_Map: ProcessUnBlockAckInd\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
    if (ie)
    {
        pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
        ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
        key = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
#if defined(CCITT)
        BSSAP_DEBUG(("ProcessUnBlockAckInd: UnBlockAckInd pcm %d slot %d\n",
                                                                      pcm, ts));
#else
        BSSAP_DEBUG(("ProcessUnBlockAckInd: UnBlockAckInd cic %d \n",
                                                                      (pcm << 5) | (0x1FU & ts)));
#endif
        crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNBLOCK_ACK,nwId);
        if (crec)
	      {
      		if (crec->localState == CIC_ST_BLOCK)
		        {
         			BSSAP_ERROR(("ProcessUnBlockAckInd: UnBlockAck in "
				      		"block state & BSSAP stack send BLOCK message towards MSC\n"));
			        //  Block message can be sent to remote by Amaresh for Bugid-460 as on dated 15-11-07
			        // Before sending Block reset flag to TRUE value
        		 crec->statusFlag = ITS_TRUE; /*Amaresh */
			       cktId.SetPCMID(pcm);
      			 cktId.SetTimeslot(ts);
			       blk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
      			 cs.SetCause(ITS_FALSE, C_OAMP_INTERVENTION, 0);
			       blk.AddIE(BSSAP_IEI_CAUSE, &cs);
			       ErrBSSAPEncode(&blk, buff, len);

      			 /* crec->statusFlag = ITS_TRUE;*/ /*orginal*/
			       if (crec->timerId)
			       {
     				   // Cancel running timer if any
		    		   BSSAP_Timer t1(crec->timerType);
				       t1.CancelUDTTimer(crec->timerId);
    				   crec->timerId = 0;
		     	   }
    		  	 BSSAP_Timer t(BSSAP_T_1);                                                        
		    	   ret = t.StartUDTTimer(key, 0, BSSAP_MSG_BLOCK, buff,len,nwId);
      			 if (ret == ITS_ETIMERSTARTFAIL)
			       {
              		cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK_ACK);                                                                      return (ret);
			       }                                                                                
			       crec->timerId = ret;
			       crec->timerType = BSSAP_T_1;                                                      
			       err.SendBlock(pcm, ts, nwId);  //SPR fix by Amaresh for Bugid-460                 
      		   ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK_ACK);                                          
			       if (ret != ITS_SUCCESS)
			       {
				       BSSAP_DEBUG(("ProcessUnBlockAckInd:CIC Modify failed %d\n", key));
				       return (ret);
			       }
			      return(!ITS_SUCCESS);/*24-03-08  by Amaresh not to send data BSC-APP Bugid-2481*/ 
			       //  Block message can be sent to remote by Amaresh for Bugid-460 as on dated 15-11-07
		      }
		     else
		      {
			      if (crec->timerId)
			      {
        			 BSSAP_Timer t(crec->timerType);
				       t.CancelUDTTimer(crec->timerId);
               crec->timerId = 0;

				      /* Added by Amaresh 18-03-08 for app_ubl_flag to 0 */
     		  		if(crec->app_ubl_flag == 1)
		     	  	{
					      crec->app_ubl_flag = 0;
         		    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK_ACK);
      					BSSAP_DEBUG(("Process UnBlockAckInd:Value of app_ubl_flag  %d\n",crec->app_ubl_flag));
			      		return (ret);	
				      }
       				/* Added by Amaresh 18-03-08 for app_ubl_flag to 0 */
			    	else
				    {
         		      ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK_ACK);
					        return (!ITS_SUCCESS);
          				/* Changed 25-03-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
				    } 
			    }
			   else
			    {
             cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK_ACK);
#if defined(CCITT)
				     BSSAP_ERROR(("ProcessUnBlockAckInd: Ignore UnBlockAckInd "
							"for already unblock cic pcm %d ts %d nwId %d\n",
							pcm, ts, nwId));
#else
				     BSSAP_ERROR(("ProcessUnBlockAckInd: Ignore UnBlockAckInd "
							"for already unblock cic cic %d  nwId %d\n",
							(pcm << 5) | (0x1FU & ts), nwId));
#endif
     		 		return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
		    	}
		    }
	     }
      else
       {
#if defined(CCITT)
            BSSAP_ERROR(("ProcessUnBlockAckInd: invalid pcm %d ts %d\n",
                                                                     pcm, ts));
#else
            BSSAP_ERROR(("ProcessUnBlockAckInd: invalid cic %d \n",
                                                                   (pcm << 5) | (0x1FU & ts)));
#endif
            /* Added by Amaresh for bug id 2545 as on dated 01-04-08*/
               bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
                                                BSSAP_MSG_UNBLOCK_ACK, pcm, ts);
            /* Added by Amaresh for bug id 2545 as on dated 01-04-08*/
            err.SendUnEquipCkt(pcm, ts, nwId);
            return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
       }
    }
    else
    {
        BSSAP_ERROR(("ProcessUnBlockAckInd: CIC ie not found\n"));
        return (!ITS_SUCCESS);
    }

    /* Added by Amaresh 24-01-08 for not send adnormal message to App */
           return (ret);
     /* Added by Amaresh 24-01-08 for not send adnormal message to App */

}

/*implementation:internal
*
* PURPOSE:
*       Enabling ErrBSSAPEncode call.
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
* Amaresh Prasad  19-11-07   IMR-BSS-BSSAP-CS2
*/
ITS_INT
ErrBSSAPEncode(BSSAP_Message* mssg, 
                         ITS_OCTET* buff, 
                         ITS_INT& len)
{
    BSSAP_DEBUG(("BSSAP_Error: BSSAPEncode\n"));

    if (BSSAP_Message::Encode(buff, len, mssg) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("BSSAPEncode: BSSAP Encode fail\n"));

        return (!ITS_SUCCESS);
    }

    return (ITS_SUCCESS);
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
* Amaresh prasad  19-05-08  VNL-BSC-CS2 					Updated for HO-MO-MT 
*                      
*                     
*/
ITS_INT
BSSAP_Map::ProcessClearCommand(BSSAP_Message* mMap, BSSAP_Call* call)
{
	ITS_INT ret = 0;
	ITS_UINT cic = 0;
	BSSAP_CicDB cicdb;
	CICData* crec;
	BSSAP_CALL_CTXT ctxt;

	/* Added by Amaresh for send Clear complete for Ho-Fai 19-05-08 */
	BSSAP_Error err;
	ITS_INT nwId = 0;
	ITS_OCTET cause = 0;
	/* Addition completed by Amaresh for send Clear complete for Ho-Fai 19-05-08 */

	BSSAP_DEBUG(("BSSAP_Map: ProcessClearCommand\n"));
	if (call) /* Added by Amaresh for Abnormal condition */
	{
		BSSAP_DEBUG(("BSSAP_Map:ProcessClearCommand:CALL found\n"));
		if(call->IsHandOverFailure())
		{
			BSSAP_DEBUG(("BSSAP_Map:ProcessClearCommand:No need for modify CIC for Handoverfailure case at NewBSC\n"));
		}
		else
		{
			cic = call->GetCIC();
			if (cic)
			{
				crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_CLEAR_COMMAND,call->GetBssId());
				if (crec)
				{
					// By this we know clearly channel is released
					call->SetChannelAlloc(ITS_FALSE);
					call->SetCicst(CALL_ST_IDLE);
					crec->callState = CALL_ST_IDLE;
					ret = cicdb.ModifyCICRecord(cic, crec,BSSAP_MSG_CLEAR_COMMAND);
					if (ret != ITS_SUCCESS)
					{
						BSSAP_DEBUG(("ProcessClearCommand:CIC Modify failed \n"));
						return (ret);
					}
					BSSAP_CRITICAL(("ProcessClearCommand:CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
				}
			}
			else
			{
				BSSAP_CRITICAL(("ProcessClearCommand: No cic found for cref[%04x] CIC[%d]\n",call->GetSLR(),cic));
			}
		}

		BSSAP_DEBUG(("BSSAP_Map:ProcessClearCommand:Enter for Handover checking\n"));
		if (call->IsHandOver())
		{
			BSSAP_DEBUG(("BSSAP_Map:ProcessClearCommand:Handover is found in CALL\n"));
			if (call->IsHandOverOldBss())
			{
				BSSAP_DEBUG(("BSSAP_Map: ProcessClearCommand for OldBss from MSC\n"));
				call->SetHandOver(0);
				call->SetHandOverOldBss(0);
				return (ITS_SUCCESS);
			}
			else if (call->IsHandOverNewBss())
			{
				BSSAP_DEBUG(("BSSAP_Map: ProcessClearCommand for NewBss from MSC \n"));
				if(call->IsHandOverFailure())
				{
					BSSAP_DEBUG(("BSSAP_Map: ProcessClearCommand for NewBss from MSC for Hofailure \n"));
					call->SetMssgType(BSSAP_MSG_CLEAR_COMPLETE);
					err.SendClearComplete(call, cause,nwId);
					return (!ITS_SUCCESS);
				}
				else
				{
					BSSAP_DEBUG(("BSSAP_Map: ProcessClearCommand for NewBss from MSC for no Hofailure\n"));
					return (ITS_SUCCESS);
				}
			}
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0570, ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessAssignmentRequest(BSSAP_Message* mMap, BSSAP_Call* call)
{
	ITS_INT ret = 0;
	ITS_USHORT pcm = 0;
	ITS_UINT key = 0;
	ITS_UINT key_old = 0;
	ITS_OCTET  ts = 0;
	ITS_OCTET cause;
	BSSAP_CicDB cicdb;
	CICData* crec;
	CICData* crec_old;
	BSSAP_Error err;
	const BSSAP_Element* ie = NULL;
	BSSAP_Interface bssIf;
	ITS_INT nwId = 0;/* Added by Amaresh for Block */
	ITS_OCTET speechDataId;
	/* Added by Amaresh for Alarm 21-07-08 */
	ITS_USHORT cic=0;
	BSSAP_CfgDB db;
	CFGData* cfgdata = NULL;
	ITS_UINT DPC = 0;
	/* Added by Amaresh for Alarm 21-07-08 */
	/* Added by Amaresh for Alarm 21-07-08 */
	cfgdata = db.FetchRPCEntry(call->GetBssId());
	if (cfgdata)
	{
		DPC = cfgdata->rpc;
	}
	/* Added by Amaresh for Alarm 21-07-08 */

	BSSAP_DEBUG(("BSSAP_Map: ProcessAssignmentRequest\n"));
	ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
	if (ie)
	{
		pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
		ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();
		key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));
		cic= pcm << 5|(0x1FU & ts);
#if defined(CCITT)
		BSSAP_CRITICAL(("ProcessAssignmentRequest: cref[%04x] CIC[%d] pcm %d ts %d\n",call->GetSLR(),key, pcm ,ts));
#else 
		BSSAP_DEBUG(("ProcessAssignmentRequest: cic %d \n", (pcm << 5) | (0x1FU & ts))); 
#endif
		crec = cicdb.FetchCICRecord(key,BSSAP_MSG_ASSIGN_REQUEST,call->GetBssId());
		if (crec)
		{
			if (crec->callState == CALL_ST_BUSY)
			{
#if defined(CCITT)
				BSSAP_ERROR(("ProcessAssignmentRequest: CALL in BUSY state cref[%04x] CIC[%d]"
							"pcm %d timeslot %d BscId[%d] \n",call->GetSLR(),key, pcm ,ts,call->GetBssId()));
#else
				BSSAP_ERROR(("ProcessAssignmentRequest: CALL in BUSY state cic %d \n", (pcm << 5) | (0x1FU & ts)));
#endif
				BSSAP_Alarm_CCITT(5134,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic);
				cause = C_TERRESTRIAL_CIRCUIT_ALLOCATED;
			}
			else if ((crec->localState == CIC_ST_UNBLK))
			{
			       if(call->GetCIC() > 0)
				{   
				    key_old=call->GetCIC(); 
		                    crec_old = cicdb.FetchCICRecord(key_old,BSSAP_MSG_ASSIGN_REQUEST,call->GetBssId());
				    if(crec_old)
			            {		 
				       crec_old->callState = CALL_ST_IDLE;
				       cicdb.ModifyCICRecord(key_old, crec_old,BSSAP_MSG_ASSIGN_REQUEST);
			               BSSAP_CRITICAL(("ProcessAssignmentRequest:old CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
				    }  
				    else
				    {
		                        BSSAP_DEBUG(("ProcessAssignmentRequest: Key %d not Match in DB\n",key_old)); 

			            }		
				}    
				call->SetCIC(key);
				call->SetMssgType(BSSAP_MSG_ASSIGN_REQUEST);/*Added by Amaresh for CALL timer */
				BSSAP_Timer t(BSSAP_T_10);
				ret = t.StartTimer(call);
				if(cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_ASSIGN_REQUEST))
				{
		         		BSSAP_ERROR(("ProcessClearCommand:CIC Modify failed %d\n", key));
					return (!ITS_SUCCESS);
				}
				return (ret);
			}
			else // CIC_ST_BLOCK
			{

				cause = C_TERRESTRIAL_RES_UNAVAILABLE; /*added by LN*/
#if defined(CCITT)
				BSSAP_ERROR(("ProcessAssignmentRequest: CIC[%d] in BLK state "
							"pcm %d timeslot %d\n",key, pcm ,ts));
#else
				BSSAP_ERROR(("ProcessAssignmentRequest: CIC in BLK state cic %d \n",(pcm << 5) | (0x1FU & ts)));
#endif
				BSSAP_Alarm_CCITT(5135,__FILE__,__LINE__,"dpc %d,cic %d ",DPC,cic);
			}
			//Send Assignment fail (CIC already assigned/block)
			err.SendAssignmentFail(call, cause,nwId); 

			/* Enhanced by Amaresh if cic locally blocked the BSSAP stack also send BLOCK message to MSC */
			if((crec->localState == CIC_ST_BLOCK))	
			{
				nwId = call->GetBssId();
				BSSAP_DEBUG(("ProcessAssignmentRequest: nwId %d \n", nwId));
				err.SendBlock(pcm, ts, nwId);
				BSSAP_CRITICAL(("Sending BLOCK Message towards MSC if CIC[%d] is locally block in ASSIGNMENT REQUEST",key));
			}
			else
			{
				BSSAP_DEBUG(("Do nothing if cic state is not blocked in  ASSIGNMENT REQUEST"));	
			}

			/* Enhanced by Amaresh completed if cic locally blocked the BSSAP stack also send BLOCK message to MSC */
		//	bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);
        bssIf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL,BSSAP_EASSREQFAIL);
	   		cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_ASSIGN_REQUEST);
			return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
		}
		else
		{
#if defined(CCITT)
			BSSAP_ERROR(("ProcessAssignmentRequest: CIC[%d] pool mismatch "
						"pcm %d timeslot %d\n",key, pcm ,ts));
#else
			BSSAP_ERROR(("ProcessAssignmentRequest: CIC pool mismatch cic %d \n",(pcm << 5) | (0x1FU & ts)));
#endif

			BSSAP_Alarm_CCITT(5136,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic);	
			/* If crec not found in BSSAP stack the BSSAP stack send Assignment failure followed by Unequipckt message towards MSC  */
			/*fix by Amaresh for bug id 489 */
			cause = C_TERRESTRIAL_RES_UNAVAILABLE;	
			//Send Assignment fail (CIC already assigned/block)
			err.SendAssignmentFail(call, cause,nwId);
			bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
					BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);
			err.SendUnEquipCkt(pcm, ts, call->GetBssId());
			return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
		}
	}
	else
	{
		ie = mMap->FindIE(BSSAP_IEI_CHANNEL_TYPE);
		if(ie)
		{
			speechDataId = ((BSSAP_ChanType*)ie)->GetSpeechDataID();
			if(speechDataId == CT_SIGNALING)
			{
				return (ITS_SUCCESS);
			}
			else
			{
				cause = C_PROTOCOL_ERROR;
				BSSAP_ERROR(("ProcessAssignmentRequest: Cic not present "));
				err.SendAssignmentFail(call,cause,nwId);
				return (!ITS_SUCCESS);
			}
		}
		else
		{
			cause = C_PROTOCOL_ERROR;
			BSSAP_ERROR(("ProcessAssignmentRequest: Cic not present "));
			err.SendAssignmentFail(call,cause,nwId);
			return (!ITS_SUCCESS);
		}
	}
#ifdef ANKUR
	/* Bugid 1791 resolved by Amaresh for without cic */
	else
	{
		cause = C_PROTOCOL_ERROR; 
		BSSAP_ERROR(("ProcessAssignmentRequest: Cic not present "));
		err.SendAssignmentFail(call,cause,nwId);
		return (!ITS_SUCCESS);
	}
	/* Bugid 1791 resolved by Amaresh for without cic */	
#endif // ANKUR	
	return (ITS_SUCCESS);  
}

/*implementation:internal
*PURPOSE:
*       Processing of ChangeCircuit
* INPUT:
*       call object, cause
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if done successfully
*       Error, if error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad   07-12-2007  IMR-BSS-BSSAP-CS2
*/
ITS_INT
BSSAP_Map::ProcessChangeCircuit(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    ITS_OCTET cause;
    BSSAP_CicDB cicdb;
    CICData* crec;
    BSSAP_Error err;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;
    ITS_INT nwId = 0;/* Added by Amaresh for Block */

     BSSAP_DEBUG(("BSSAP_Map: ProcessChangeCircuit\n"));

    //cause = mMap->FindIE(BSSAP_IEI_CAUSE);	
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0580, ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessAssignmentComplete(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_UINT cic = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    const BSSAP_Element* ie = NULL;
    BSSAP_Interface bssIf;
    /* Bug fix 1627 by Amaresh if no CIC is present in Message */
    BSSAP_DEBUG(("BSSAP_Map: ProcessAssignmentComplete\n"));

    ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);

    cic = call->GetCIC();
    BSSAP_DEBUG(("ProcessAssignmentComplete: cic %d \n", cic));
    if (cic)
    {
        crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_ASSIGN_COMPLETE,call->GetBssId());
        if(crec)
        {  
         pcm = crec->pcm;
       	 ts =  crec->ts;
#if defined(CCITT)
       	 BSSAP_DEBUG(("ProcessAssignmentComplete: pcm %d ts %d\n", pcm ,ts));
#else
       	 BSSAP_DEBUG(("ProcessAssignmentComplete: cic %d \n", ((pcm << 5) | (0x1FU & ts))));
#endif
      	 key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));       
        }

        /* Bug fix 1627 by Amaresh if no CIC is present in Message  */
        
       if (!crec)
        {
            BSSAP_ERROR(("ProcessAssignmentComplete: CIC pool mismatch "));

				    bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ECICNOTFOUND,
                                         BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);  
            return (!ITS_SUCCESS);
        }
       else
        {
            BSSAP_Timer t(BSSAP_T_10);                                                              
            t.CancelTimer(call);                                                                     
            crec->callState = CALL_ST_BUSY;
	           call->SetCicst(CALL_ST_BUSY);/* Setting Cic State Busy in Call Context Table*/
            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_ASSIGN_COMPLETE);
            // By this response we know clearly channel is getting alloted
            BSSAP_CRITICAL(("ProcessAssignmentComplete:CIC[%d] Modify to callState = CALL_ST_BUSY  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
            call->SetChannelAlloc(ITS_TRUE);
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Handelling of Clear Request 
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
* Amaresh Prasad  14-02-08   IMR-BSS-BSSAP-CS2
*/

ITS_INT
BSSAP_Map::ProcessClearRequest(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;

	BSSAP_DEBUG(("BSSAP_Map: ProcessClearRequest\n"));
	cic = call->GetCIC();

    if (cic)
     {
        crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_CLEAR_REQUEST,call->GetBssId());
	if(crec)
	{ 
		crec->callState = CALL_ST_IDLE;
	  call->SetCicst(CALL_ST_IDLE);/* Setting Cic State idle in Call Context Table*/
		ret = cicdb.ModifyCICRecord(cic, crec,BSSAP_MSG_CLEAR_REQUEST);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessClearRequest:CIC Modify failed \n"));
			return (ret);
		}
		BSSAP_CRITICAL(("ProcessClearRequest:CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
	}
    }	
   if (call->GetTimerId())
    {
       	BSSAP_Timer t10(BSSAP_T_10);
        ret = t10.CancelTimer(call);
    }
   if(call->GetCallType() == HO_CALL)
	 {
	
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
* Amaresh prasad  29-04-08 VNL-BSC-CS2
*/


ITS_INT
BSSAP_Map::ProcessHandoverRequired(BSSAP_Message* mMap, BSSAP_Call* call,ITS_OCTET *data,ITS_UINT dlen)
{
    ITS_INT ret = 0;
		BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverRequired\n"));  
    call->SetMssgType(BSSAP_MSG_HANDOVER_REQUIRED);
		call->SetBSSAPData(data, dlen);
		call->SetCallType(HO_CALL);
		call->SetHandOver(1);
		call->SetHandOverOldBss(1);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0630, ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessHandoverCommand(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverCommand\n"));

    //call->SetHandOver(1);

#if 0
   BSSAP_Timer t(BSSAP_T_7);

    ret = t.CancelTimer(call);

    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    BSSAP_Timer t1(BSSAP_T_8);
    call->SetMssgType(BSSAP_MSG_HANDOVER_COMMAND);/*Added by Amaresh for CALL timer */                                                                                                                                              
    ret = t1.StartTimer(call);
#endif
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
* Amaresh Prasad  10-08-07   IMR-BSS-BSSAP-CS2
*/

ITS_INT
BSSAP_Map::ProcessHandoverRequiredReject(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;

    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverRequiredReject\n"));
	//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_HORRJ_RECV);
     BSSAPPEG_IncrPeg(PEG_BSSAP_HORRJ_RECV,call->GetBssId());     
    return (ret);
}


/*implementation:internal
*
* PURPOSE:
*      sending handover request as CR/DT1
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
* Amaresh prasad  29-04-08   VNL-BSC-CS2
*/
ITS_INT
BSSAP_Map::ProcessHandoverRequest(BSSAP_Message* mMap, BSSAP_Call* call)
{
	ITS_INT ret = ITS_SUCCESS;
	/*Added by Amaresh for CIC in HoReq 29-04-08 */
	ITS_USHORT pcm = 0;
	ITS_UINT key = 0;
	ITS_UINT key_old = 0;
	ITS_OCTET  ts = 0;
	ITS_OCTET cause;
	BSSAP_CicDB cicdb;
	CICData* crec;
	CICData* crec_old;
	BSSAP_Error err;
	const BSSAP_Element* ie = NULL;
	BSSAP_Interface bssIf;
	ITS_INT nwId = 0;/* Added by Amaresh for Block */

	/* Added by Amaresh for check purpose 29-04-08 */
	ITS_INT error = 0;
	ITS_UINT callrefId = 0;
	ITS_CTXT hash = 0;
	ITS_INT len  = 0;
	ITS_OCTET* data = NULL;
	BSSAP_Call* fptr = NULL;

	/* Added by Amaresh for Alarm 21-07-08 */
	ITS_USHORT cic=0;
	BSSAP_CfgDB db;
	CFGData* cfgdata = NULL;
	ITS_UINT DPC = 0;
	/* Added by Amaresh for Alarm 21-07-08 */
	/* Added by Amaresh for Alarm 21-07-08 */
	cfgdata = db.FetchRPCEntry(call->GetBssId());
	if (cfgdata)
	{
		DPC = cfgdata->rpc;
	}
	/* Added by Amaresh for Alarm 21-07-08 */


	BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverRequest\n"));

	callrefId = hash = call->GetSLR();
	BSSAP_DEBUG(("BSSAP_CallDB: DSM_FIND in HO-REQ case  \n"));
	fptr = (BSSAP_Call*)DSM_Find(DSM_SccpFtGroupId,
			DSM_TABLE_BSSAP_CALL_CTXT,
			(ITS_OCTET *)&hash,
			sizeof(ITS_CTXT),
			&error);
	if(fptr)
	{	
		BSSAP_DEBUG(("BSSAP_ProcessSCCPdata: In Fptr HoreqDt1 %d \n",fptr->GetHoreqDt1()));
	}
	if(fptr == NULL || fptr->IsHoreqDt1() == 1)
	{
		BSSAP_DEBUG(("BSSAP_Map: SCCP-New connection for HO-REQ case(CR)/(DT1) \n"));
                if(fptr)
                {
                   error = DSM_Commit(DSM_SccpFtGroupId,DSM_TABLE_BSSAP_CALL_CTXT,(ITS_OCTET *)&hash,sizeof(ITS_CTXT),fptr);
                   if (error != ITS_SUCCESS)
                   {
                       BSSAP_ERROR(("ProcessHandoverRequest: Couldn't commit context \n"));
                       return (error);
                   }
                }
		ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
		if (ie)
		{
			pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
			ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();

#if defined(CCITT)
			BSSAP_DEBUG(("ProcessHandoverRequest: pcm %d ts %d\n", pcm ,ts));
#endif
			key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));
			cic= pcm << 5|(0x1FU & ts);
			crec = cicdb.FetchCICRecord(key,BSSAP_MSG_HANDOVER_REQUEST,call->GetBssId());
			if (crec)
			{
				if (crec->callState == CALL_ST_BUSY)
				{
#if defined(CCITT)
					BSSAP_ERROR(("ProcessHandoverRequest: CALL in BUSY state "
								"pcm %d timeslot %d\n", pcm ,ts));
#endif
					BSSAP_Alarm_CCITT(5134,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic); 
					/* Added by Amaresh for send HO-FAI data to BSC-APP 03-07-08*/
					bssIf.DispatchMapErrToApp(call, mMap,BSSAP_ECICCKTALCTD); 	
					/* Added by Amaresh for send HO-FAI data to BSC-APP 03-07-08*/

					cause = C_TERRESTRIAL_CIRCUIT_ALLOCATED;
				}
				else if ((crec->localState == CIC_ST_UNBLK))
				{
				       if(call->GetCIC() > 0 )
				       {
				          key_old=call->GetCIC(); 
                                          crec_old = cicdb.FetchCICRecord(key_old,BSSAP_MSG_HANDOVER_REQUEST,call->GetBssId());
		                          if(crec_old)
			                  {		 
                			       crec_old->callState = CALL_ST_IDLE;
		          		       cicdb.ModifyCICRecord(key_old, crec_old,BSSAP_MSG_HANDOVER_REQUEST);
		                               BSSAP_CRITICAL(("ProcessHandoverRequest:old CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
			                  }  
				        else
				          {
		                             BSSAP_DEBUG(("ProcessHandoverRequest: Key %d not Match in DB\n",key_old)); 

			                  }		

				       }   
					call->SetCIC(key);
					/*Added by Amaresh as per requirement 28-05-08 */
					crec->callState = CALL_ST_BUSY; 
	    call->SetCicst(CALL_ST_BUSY);/* Setting Cic State Busy in Call Context Table*/
					cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_HANDOVER_REQUEST);
					/*Added by Amaresh as per requirement 28-05-08 */	
                                        BSSAP_CRITICAL(("ProcessHandoverRequest:CIC[%d] Modify to callState = CALL_ST_BUSY  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
					return (ret);
				}
				else // CIC_ST_BLOCK
				{

					cause = C_TERRESTRIAL_RES_UNAVAILABLE;
#if defined(CCITT)
					BSSAP_ERROR(("ProcessHandoverRequest: CIC in BLK state "
								"pcm %d timeslot %d\n", pcm ,ts));
#endif
					BSSAP_Alarm_CCITT(5135,__FILE__,__LINE__,"dpc %d,cic %d ",DPC,cic);
					/* Added by Amaresh for send HO-FAI data to BSC-APP 03-07-08*/
					bssIf.DispatchMapErrToApp(call, mMap,BSSAP_ECICCKTUNVL);
					/* Added by Amaresh for send HO-FAI data to BSC-APP 03-07-08*/

				}
				//Send Handover failure (CIC already assigned/block)
				err.SendHandoverFail(call, cause,nwId);
				/* Enhanced by Amaresh if cic locally blocked the BSSAP stack also send BLOCK message to MSC */
				if((crec->localState == CIC_ST_BLOCK))
				{
					nwId = call->GetBssId();
					BSSAP_DEBUG(("ProcessHandoverRequest: nwId %d \n", nwId));
					err.SendBlock(pcm, ts, nwId);
					BSSAP_DEBUG(("Sending BLOCK Message towards MSC if CIC is locally block in HANDOVER REQUEST"));
				}
				else
				{
					BSSAP_DEBUG(("Do nothing if cic state is not blocked in  HANDOVER REQUEST"));
				}
				/* Enhanced by Amaresh completed if cic locally blocked the BSSAP stack also send BLOCK message to MSC */
				/* As on dated 22-05-08 */
				/* bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,
				   BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);  */
                                cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_HANDOVER_REQUEST);
				return (!ITS_SUCCESS);
			}
			else
			{
#if defined(CCITT)
				BSSAP_ERROR(("ProcessHandoverRequest: CIC pool mismatch "
							"pcm %d timeslot %d\n", pcm ,ts));
#endif
				BSSAP_Alarm_CCITT(5136,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic);		

				cause = C_TERRESTRIAL_RES_UNAVAILABLE;
				bssIf.DispatchMapErrToApp(call, mMap,BSSAP_EUNEQUIPCKT);/*03-07-08 */
				err.SendHandoverFail(call, cause,nwId);

				bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
						BSSAP_MSG_HANDOVER_REQUEST, pcm, ts);
				err.SendUnEquipCkt(pcm, ts, call->GetBssId());

				return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
			}
		}
		else
		{
			cause = C_PROTOCOL_ERROR; //C_INVALID_MSG_CONTENT 06-06-08
			BSSAP_ERROR(("ProcessHandoverRequest: Cic not present "));
			/* fix for Bug-id 4339 by Amaresh as on dated 26-09-08 by reversing the order*/
			bssIf.DispatchMapErrToApp(call, mMap,BSSAP_EPROTOCOLERR);/*03-07-08 */
			err.SendHandoverFail(call,cause,nwId);
			/* fix for Bug-id 4339 by Amaresh as on dated 26-09-08 by reversing the order*/
			return (!ITS_SUCCESS);
		}
		return (ITS_SUCCESS);
	}
	/*Addition completed by Amaresh for CIC in HoReq 29-04-08 */
	else 
	{

		BSSAP_ERROR(("ProcessHandoverRequest: Enter same SCCP-Connection \n"));
                error = DSM_Commit(DSM_SccpFtGroupId,DSM_TABLE_BSSAP_CALL_CTXT,(ITS_OCTET *)&hash,sizeof(ITS_CTXT),fptr);
                if (error != ITS_SUCCESS)
                 {
                    BSSAP_ERROR(("ProcessHandoverRequest: Couldn't commit context \n"));
                    return (error);
                 }

		ie = mMap->FindIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE);
		if (ie)
		{
			pcm = ((BSSAP_CktIDCode*)ie)->GetPCMID();
			ts = ((BSSAP_CktIDCode*)ie)->GetTimeslot();

#if defined(CCITT)
			BSSAP_DEBUG(("ProcessHandoverRequest: pcm %d ts %d\n", pcm ,ts));
#endif

			key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));
			cic= pcm << 5|(0x1FU & ts);

			crec = cicdb.FetchCICRecord(key,BSSAP_MSG_HANDOVER_REQUEST,call->GetBssId());
			if (crec)
			{
				if (crec->callState == CALL_ST_BUSY)
				{
#if defined(CCITT)
					BSSAP_ERROR(("ProcessHandoverRequest: CALL in BUSY state "
								"pcm %d timeslot %d\n", pcm ,ts));
#endif
					BSSAP_Alarm_CCITT(5134,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic);
					BSSAP_ERROR(("ProcessHandoverRequest: Enter same SCCP-Connection with Same CIC \n"));
                                        cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_HANDOVER_REQUEST);                                                                 return (!ITS_SUCCESS);
				}
				else if ((crec->localState == CIC_ST_UNBLK))
				{
					BSSAP_ERROR(("ProcessHandoverRequest: Enter same SCCP-Connection with different CIC \n"));
					cause = C_PROTOCOL_ERROR; //C_INVALID_MSG_CONTENT 06-06-08
					bssIf.DispatchMapErrToApp(call, mMap,BSSAP_EPROTOCOLERR);/*03-07-08 */
					err.SendHandoverFailure(call, cause,nwId);
                                        cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_HANDOVER_REQUEST);
					return (!ITS_SUCCESS);
				} 
				else // CIC_ST_BLOCK
				{

					cause = C_TERRESTRIAL_RES_UNAVAILABLE; /*added by LN*/
#if defined(CCITT)
					BSSAP_ERROR(("ProcessHandoverRequest: CIC in BLK state "
								"pcm %d timeslot %d\n", pcm ,ts));
#endif
					BSSAP_Alarm_CCITT(5135,__FILE__,__LINE__,"dpc %d,cic %d ",DPC,cic);
					bssIf.DispatchMapErrToApp(call, mMap,BSSAP_ECICCKTUNVL);/*03-07-08 */
				}
				//Send Handover Request fail (CIC already assigned/block)
				err.SendHandoverFail(call, cause,nwId);

				/* Enhanced by Amaresh if cic locally blocked the BSSAP stack also send BLOCK message to MSC */
				if((crec->localState == CIC_ST_BLOCK))
				{
					nwId = call->GetBssId();
					BSSAP_DEBUG(("ProcessHandoverRequest: nwId %d \n", nwId));
					err.SendBlock(pcm, ts, nwId);
					BSSAP_DEBUG(("Sending BLOCK Message towards MSC if CIC is locally block in HANDOVER REQUEST"));
				}
				else
				{
					BSSAP_DEBUG(("Do nothing if cic state is not blocked in  HANDOVER REQUEST"));
				}

				/* Enhanced by Amaresh completed if cic locally blocked the BSSAP stack also send BLOCK message to MSC */
				/*            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,
					      BSSAP_MSG_ASSIGN_REQUEST, pcm, ts); */
                                cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_HANDOVER_REQUEST);
				return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
			}
			else
			{
#if defined(CCITT)
				BSSAP_ERROR(("ProcessHandoverRequest: CIC pool mismatch "
							"pcm %d timeslot %d\n", pcm ,ts));
#endif

				BSSAP_Alarm_CCITT(5136,__FILE__,__LINE__,"dpc %d,cic %d",DPC,cic);
				/* If crec not found in BSSAP stack the BSSAP
				   stack send Handover Failure followed by Unequipckt message towards MSC  *//*fix by Amaresh for bug id 489 */
				cause = C_TERRESTRIAL_RES_UNAVAILABLE; /*for bug id 489 */
				//Send Handover Request fail (CIC already assigned/block)
				bssIf.DispatchMapErrToApp(call, mMap,BSSAP_EUNEQUIPCKT);/*03-07-08 */	
				err.SendHandoverFail(call, cause,nwId);  /*for bug id 489 */

				bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EUNEQUIPCKT,
						BSSAP_MSG_HANDOVER_REQUEST, pcm, ts);
				err.SendUnEquipCkt(pcm, ts, call->GetBssId());

				return (!ITS_SUCCESS);/* Changed 10-01-08 to send data directly BSC-APP (!ITS_SUCCESS)*/
			}
		}
		/* Bugid 1791 resolved by Amaresh for without cic */
		else
		{
			cause = C_PROTOCOL_ERROR; //C_INVALID_MSG_CONTENT 06-06-08 
			BSSAP_ERROR(("ProcessHandoverRequest: Cic not present "));
			/* fix for Bug-id 4339 by Amaresh as on dated 26-09-08 by reversing the order*/
			bssIf.DispatchMapErrToApp(call, mMap,BSSAP_EPROTOCOLERR);/*03-07-08 */
			err.SendHandoverFail(call,cause,nwId);
			/* fix for Bug-id 4339 by Amaresh as on dated 26-09-08 by reversing the order*/

			return (!ITS_SUCCESS);
		}
	}// else Same SCCP-connection

	return (ITS_SUCCESS);
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
* Amaresh prasad     24-05-2008   VNL-BSC-CS2                       
*/
ITS_INT
BSSAP_Map::ProcessHandoverFailure(BSSAP_Message* mMap, BSSAP_Call* call)
{
	ITS_INT ret = 0;
	/* Added by Amaresh for CIC record free for HO-failure for new BSC 24-05-08*/
	ITS_UINT cic = 0;
	BSSAP_CicDB cicdb;
	CICData* crec;

	BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverFailure\n"));
	if (call->IsHandOver())
	{
		if (call->IsHandOverOldBss())  
		{
			BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverFailure for OldBss from BSC-APP\n"));
			//PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_HOFAIL_SEND);
			BSSAPPEG_IncrPeg(PEG_BSSAP_HOFAIL_SEND,call->GetBssId());     
			return (ret);
		}
		else if (call->IsHandOverNewBss())
		{
			call->SetHandOverFailure(1); /* Set Hofailure flag */
			BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverFailure for NewBss from BSC-APP \n"));	
			cic = call->GetCIC();
			if (cic)
			{
				crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_HANDOVER_FAILURE,call->GetBssId());
				if (crec)
				{
					crec->callState = CALL_ST_IDLE;
	                                call->SetCicst(CALL_ST_IDLE);/* Setting Cic State idle in Call Context Table*/
					ret = cicdb.ModifyCICRecord(cic, crec,BSSAP_MSG_HANDOVER_FAILURE);
					if (ret != ITS_SUCCESS)
					{
						BSSAP_DEBUG(("ProcessHandoverFailure:CIC Modify failed \n"));
						return (ret);
					}
		                        BSSAP_CRITICAL(("ProcessHandoverFailure:CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
				}
			}
			else
			{
				BSSAP_ERROR(("ProcessHandoverFailure: No CIC found in HOFailure case\n"));
				return (!ITS_SUCCESS);
			}
			//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_HOFAIL_SEND);
			BSSAPPEG_IncrPeg(PEG_BSSAP_HOFAIL_SEND,call->GetBssId());     
			return (ret);
		}
	}
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
* HISTOR`Y:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D0650, ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessHandoverReqAck(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
    ITS_UINT cic = 0;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    const BSSAP_Element* ie = NULL;
    /* Bug fix 1627 by Amaresh if no CIC is present in Message */
    BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverReqAck\n"));
    cic = call->GetCIC();
    BSSAP_DEBUG(("ProcessHandoverReqAck: cic %d \n", cic));
    if (cic)
    {
        crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_HANDOVER_REQUEST_ACK,call->GetBssId());
        /* Bug fix 1627 by Amaresh if no CIC is present in Message  */
        if (crec)
	{
		pcm = crec->pcm;
		ts =  crec->ts;
#if defined(CCITT)
		BSSAP_DEBUG(("ProcessHandoverReqAck: pcm %d ts %d\n", pcm ,ts));
#endif
		key = (call->GetBssId() << 16) | ((pcm << 5) | (0x1FU & ts));
		call->SetChannelAlloc(ITS_TRUE);	        
		ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_HANDOVER_REQUEST_ACK);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessHandoverReqAck:CIC Modify failed %d\n", key));
			return (ret);
		}
	}
    }
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Process Handover Complete message
* INPUT:
*       mmap, call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success,
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  07-08-2007   IMR-BSS-BSAP-CS2
*/

ITS_INT
BSSAP_Map::ProcessHandoverComplete(BSSAP_Message* mMap, BSSAP_Call* call)
{
		ITS_INT ret = 0;
		BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverComplete \n"));
	//	PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_HOCMP_SEND);	
            BSSAPPEG_IncrPeg(PEG_BSSAP_HOCMP_SEND,call->GetBssId());     
   #if 0 /*Amaresh not need as per spec */
    if (call->IsHandOver())
    {
        BSSAP_Timer t(BSSAP_T_8);
        ret = t.CancelTimer(call);
        BSSAP_DEBUG(("BSSAP_Map: Cancel T8 Timer after receive ProcessHandoverComplete \n"));
    }
   /*Amaresh not need as per spec */
    call->SetCallType(HO_CALL);
   #endif
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Process Handover Performed message
* INPUT:
*       mmap, call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success,
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  09-08-2007   IMR-BSS-BSAP-CS2
*/
ITS_INT
BSSAP_Map::ProcessHandoverPerformed(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
		 BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverPerformed due to success intra BTS handover towards MSC \n"));
    call->SetCallType(HO_CALL);
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Process Handover Succeeded message
* INPUT:
*       mmap, call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  09-08-2007   IMR-BSS-BSAP-CS2
*/
ITS_INT
BSSAP_Map::ProcessHandoverSucceeded(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
 		BSSAP_DEBUG(("BSSAP_Map: ProcessHandoverSucceeded due to some cause towards MSc \n"));
    call->SetCallType(HO_CALL);
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Process Handover Detect message
* INPUT:
*       mmap, call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success,
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  09-08-2007   IMR-BSS-BSAP-CS2
*/
ITS_INT
BSSAP_Map::ProcessHandoverDetect(BSSAP_Message* mMap, BSSAP_Call* call)
{
    ITS_INT ret = 0;
		BSSAP_DEBUG(("BSSAP_Map: Entering Process Handover detect to pass to MSC \n"));
		BSSAP_DEBUG(("BSSAP_Map: Do Nothing just pass to MSC \n"));
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0410, ID :: D0420,
*                        ID :: D1060
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
        crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_ASSIGN_FAILURE,call->GetBssId());
	if (crec)
	{
		crec->callState = CALL_ST_IDLE;
	        call->SetCicst(CALL_ST_IDLE);/* Setting Cic State idle in Call Context Table*/
		ret = cicdb.ModifyCICRecord(cic, crec,BSSAP_MSG_ASSIGN_FAILURE);
		if (ret != ITS_SUCCESS)
		{
			BSSAP_DEBUG(("ProcessAssignmentFail:CIC Modify failed \n"));
			return (ret);
		}
		BSSAP_CRITICAL(("ProcessAssignmentFail:CIC[%d] Modify to callState = CALL_ST_IDLE  for cref[%04x] \n",call->GetCIC(),call->GetSLR()));
		BSSAP_Timer t(BSSAP_T_10);
		ret = t.CancelTimer(call);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0380, ID :: D0400,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessUDTMapProcedures(BSSAP_Message* mMap, ITS_OCTET nwId,
                                   ITS_BOOLEAN toAPP, ITS_OCTET *data, ITS_UINT len)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET mType;
    BSSAP_Interface bssIf;
    BSSAP_SCCPHandler hndl;
    mType = mMap->GetMsgType();
    BSSAP_DEBUG(("BSSAP_Map: ProcessUDTMapProcedures\n"));

    // MSC -> BSS
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
						/* Added by Amaresh as on dated 06-06-08 */
						case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
                ret = ProcessHandoverCandidateEnquireInd(mMap, nwId);
            break;
						/* Added by Amaresh as on dated 06-06-08 */
            case BSSAP_MSG_CONFUSION:
//                PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CONF_RECV);
                 BSSAPPEG_IncrPeg(PEG_BSSAP_CONF_RECV,nwId);
            break;
        }
    }
    else
    { 
        // BSS -> MSC

        switch (mType)
        {
            case BSSAP_MSG_BLOCK:
               ret = ProcessBlockReq(mMap, data, len, nwId);
            break;

            case BSSAP_MSG_UNBLOCK:
                ret = ProcessUnBlockReq(mMap, data, len, nwId);
            break;

            case BSSAP_MSG_RESET:
                ret = ProcessResetReq(mMap, data, len, nwId);
            break;

            case BSSAP_MSG_RESET_ACK:
                ret = ProcessResetAckReq(mMap, data, len, nwId);
            break;

            case BSSAP_MSG_RESET_CIRCUIT:
                ret = ProcessResetCktReq(mMap, data, len, nwId);
            break;

            case BSSAP_MSG_UNEQUIPPED_CKT:
                ret = ProcessUnequipCktReq(mMap, data, len, nwId);
            break;
                                                                                      
            case BSSAP_MSG_CKT_GROUP_BLOCK:
                ret = ProcessCktGroupBlkReq(mMap, data, len, nwId);
            break;
						 /* Added by Amaresh as on dated 06-06-08 */
            case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
                ret = ProcessHandoverCandidateResponseReq(mMap, data, len, nwId);
            break;
            /* Added by Amaresh as on dated 06-06-08 */
                                                                                 
            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                ret = ProcessCktGroupUnblkReq(mMap, data, len, nwId);
            break;
        }

        if (mMap)
        {
             delete mMap;
             mMap = NULL;
        }

        if (ret == ITS_SUCCESS)
        {
             hndl.BSSAP_ProcessAPPdata(data, len, nwId);
        }
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0380, ID :: D0400,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessCOMapProcedures(BSSAP_Message* mMap,
                                  BSSAP_Call* call,
                                  ITS_USHORT callrefId,
                                  ITS_BOOLEAN toAPP,
                                  ITS_OCTET *data,
                                  ITS_UINT dlen)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET mType = 0;
    ITS_OCTET pvType = 0;
    ITS_OCTET callType = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    BSSAP_DEBUG(("BSSAP_Map: ProcessCOMapProcedures\n"));

    callType = call->GetCallType();
    if (callType != MO_CALL && callType != MT_CALL && callType != HO_CALL &&
        callType != LU_CALL && callType != IMSI_DETACH )
    {
           BSSAP_ERROR(("ProcessCOMapProcedures: BSS-MAP procedure w/o call\n"));
           return (!ITS_SUCCESS);
    }
     mType = mMap->GetMsgType();
     pvType = call->GetMssgType();

    // MSC -> BSS
    if (toAPP)
    {
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
            case BSSAP_MSG_CONFUSION:
               //  PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_CONF_RECV);
                 BSSAPPEG_IncrPeg(PEG_BSSAP_CONF_RECV,call->GetBssId());
            break;
           /* Added by Amaresh for Handover */
            case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
                ret = ProcessHandoverRequiredReject(mMap, call);
            break;
						case BSSAP_MSG_HANDOVER_SUCCEEDED:
                ret = ProcessHandoverSucceeded(mMap, call);
            break;
            /* Added by Amaresh for Handover */
            /* Enhance by Amaresh for Change Ckt TC_049 */
            case BSSAP_MSG_CHANGE_CKT:
                ret = ProcessChangeCircuit(mMap, call);
            break;
            /* Enhance by Amaresh for Change Ckt TC_049 */
            case BSSAP_MSG_LCLS_CONNECT_CONTROL:
                ret = ITS_SUCCESS;
            break;
	    }
   }
  else
   {   
      // BSS -> MSC
      /* Enhanced by Amaresh for Decode & Encode check for Mandatory parameters */
      if (CheckParameters(BSSAP_MD_BSSMAP, mMap) != ITS_SUCCESS)
       {
         BSSAP_ERROR(("ProcessCOMapProcedures: BSSMAP Encode fail check mandatory parameter " " encode failed\n"));
         bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EENCODE);
         delete mMap;
         return (ITS_SUCCESS);
       }

      /* Enhanced by Amaresh for Decode & Encode check for Mandatory parameters */
      switch (mType)
        {
            case BSSAP_MSG_ASSIGN_COMPLETE:
                if (pvType != BSSAP_MSG_ASSIGN_REQUEST)
                {
                  /*  return (!ITS_SUCCESS); */ /* Commented by Amaresh not to check mtype 02-04-08*/
									BSSAP_DEBUG(("BSSAP_Map: != BSSAP_MSG_ASSIGN_REQUEST\n"));
                }
                ret = ProcessAssignmentComplete(mMap, call);
            break;

            case BSSAP_MSG_ASSIGN_FAILURE:
                if (pvType != BSSAP_MSG_ASSIGN_REQUEST)
                {
                   /* return (!ITS_SUCCESS);*/ /* Commented by Amaresh not to check mtype 02-04-08*/
									BSSAP_DEBUG(("BSSAP_Map: != BSSAP_MSG_ASSIGN_REQUEST\n"));
                }
                ret = ProcessAssignmentFail(mMap, call);
            break;

            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
            case BSSAP_MSG_CIPHER_MODE_REJECT:
                if (pvType != BSSAP_MSG_CIPHER_MODE_CMD)
                {
                   /* return (!ITS_SUCCESS);*/ /* Commented by Amaresh not to check mtype 02-04-08*/
									BSSAP_DEBUG(("BSSAP_Map: != BSSAP_MSG_CIPHER_MODE_CMD\n"));
                }
            break;

            case BSSAP_MSG_PERFORM_LOCACTION_RESPONSE:
                if (pvType != BSSAP_MSG_PERFORM_LOCACTION_REQUEST)
                {
                  /*  return (!ITS_SUCCESS);*/ /* Commented by Amaresh not to check mtype 02-04-08*/
									BSSAP_DEBUG(("BSSAP_Map: != BSSAP_MSG_PERFORM_LOCACTION_REQUEST\n"));
                }
            break;

           /* Added by Amaresh for handle BSSAP_MSG_CLEAR_REQUEST message from BSC-->MSC 14-02-08*/
 	          case BSSAP_MSG_CLEAR_REQUEST:
                ret = ProcessClearRequest(mMap, call);
            break;	

            /* Added by Amaresh for handle BSSAP_MSG_CLEAR_REQUEST message from BSC-->MSC 14-02-08*/
            case BSSAP_MSG_HANDOVER_REQUIRED:
                /*  ret = ProcessHandoverRequired(mMap, call); */ //29-04-08 by Amaresh
									ret = ProcessHandoverRequired(mMap,call,data,dlen); //Added by Amaresh as on dated 29-04-08
            break;

            case BSSAP_MSG_HANDOVER_FAILURE:
                ret = ProcessHandoverFailure(mMap, call);
            break;

            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
                ret = ProcessHandoverReqAck(mMap, call);
            break;

	          case BSSAP_MSG_HANDOVER_COMPLETE:
                /* Added by Amaresh for handle Handover Complete message from BSC-->MSC */
                ret = ProcessHandoverComplete(mMap, call);
                /* Added by Amaresh for handle Handover Complete message from BSC-->MSC */
            break;

            	   /* Added by Amaresh for handle Handover Complete message from BSC-->MSC */
            case BSSAP_MSG_HANDOVER_DETECT:
                ret = ProcessHandoverDetect(mMap, call);
            break;
            case BSSAP_MSG_HANDOVER_PERFORMED:
                ret = ProcessHandoverPerformed(mMap, call);
           break;
                 /* Added by Amaresh for handle Handover Complete message from BSC-->MSC */
            case BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK:
                ret = ITS_SUCCESS;
            break;
            case BSSAP_MSG_LCLS_NOTIFICATION:
                ret = ITS_SUCCESS;
            break;
      }
     if (mMap)
      {
          delete mMap;
          mMap = NULL;
      }
     if (ret == ITS_SUCCESS)
      {
           call->SetBSSAPData(data, dlen);
           ret = hndl.BSSAP_ProcessAPPdata(call);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D1060
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
*       processing outgoing msgs from BSC application
* INPUT:
*       msg
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if msg sent successfully to MSC 
*       Error, if problem occurs
* COMMENTS:
*       This function handle seperatly for CO & CL msgs
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0380, ID :: D0400,
*                        ID :: D1060
*/
ITS_INT 
BSSAP_Map::ProcessOutBSSMAPMessage(BSSAP_Api* msg, ITS_OCTET *data, ITS_UINT len)
{
    ITS_INT ret;
    BSSAP_Message* dec = NULL;
    ITS_CTXT ref = 0;
    ITS_OCTET mType = 0;
    BSSAP_Call* call = NULL;
    ITS_OCTET sbuff[BSSAP_DATA_LEN]; 
    BSSMap* mMap = (BSSMap*)msg;
		BSSAP_Interface bssIf;/* 15-04-08 for Bug id 2657 */
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */
	

    BSSAP_DEBUG(("BSSAP_Map: ProcessOutBSSMAPMessage\n"));
    memcpy(&sbuff, data, len);
    mType = mMap->GetMssgType();
    if (BSSAP_Message::Decode(data, len, &dec) != ITS_SUCCESS)
    {
            BSSAP_ERROR(("ProcessOUTBSSMAPMessage: BSS-MAP payload "
                                           " decode failed\n"));
            return (!ITS_SUCCESS);
    }
	  if(dec) /* dec if zero 15-04-08 Bug fix 2657 by Amaresh*/
		{
      if (!IsUDT(mType))
       {
           ret = DirectionCheck(mType, ITS_FALSE);                                         
           if (ret != ITS_SUCCESS)
            {
               BSSAP_ERROR(("ProcessOutBSSMAPMessage: Wrong message direction "
                                                        "%d\n", mType));
               /* Added by Amaresh for Alarm 21-07-08 */
                cfgdata = db.FetchRPCEntry(mMap->GetBssId());
               if (cfgdata)
                {
                   DPC = cfgdata->rpc;
                }
               /* Added by Amaresh for Alarm 21-07-08 */
                BSSAP_Alarm_CCITT(5115,__FILE__,__LINE__,"dpc %d",DPC);

          			/* Abnormal case for memory free 10-06-08*/
					     delete dec;
     					 dec = NULL;
		           /* Abnormal case for memory free 10-06-08*/
               return (ret);
          }

         // Send as CO
         ref = mMap->GetCallRef();
         BSSAP_DEBUG(("ProcessOutBSSMAPMessage : Sending CO MAP %d\n",
                                                       mMap->GetMssgType()));
				
         call = BSSAP_CallDB::GetShared().Fetch(ref);
					
         if (call)
         {
             call->SetBssId(mMap->GetBssId());
					 	/* Bug id is fixed 4788 by Amaresh */
					 	call->SetAppId(mMap->GetAppId());
					  /* Bug id is fixed 4788 by Amaresh */
             BSSAP_CRITICAL(("SEND TO MSC:cref[%04x] AppId[%04x]:Outgoing DT1 Msg:MsgType:[%s]\n",call->GetSLR(),call->GetAppId(),BSSAP_MSG_TYPE_STR(mType)));
				    ret = ProcessCOMapProcedures(dec, call, ref, ITS_FALSE, sbuff, len);
        }
        else
        {
         BSSAP_CRITICAL(("From BSC-APP:BsProcessOutBSSMAPMessage : Call not found for cref[%04x] MsgType:[%s]\n",ref,BSSAP_MSG_TYPE_STR(mType)));
				   /* Abnormal case for memory free 10-06-08*/
           delete dec;
           dec = NULL;
				  /*Abnormal case for memory free 10-06-08*/
	        return (!ITS_SUCCESS);
        }
   	 }
  	 else
  	 {
        // Send as UDT 
         BSSAP_DEBUG(("ProcessOutBSSMAPMessage : Sending (UDT) BSSMAP %d\n", 
                                                         mMap->GetMssgType()));
	 BSSAP_CRITICAL(("SEND TO MSC:Outgoing UDT Msg: MsgType:[%s]  \n",BSSAP_MSG_TYPE_STR(mType)));
         ret = ProcessUDTMapProcedures(dec, mMap->GetBssId(), ITS_FALSE, sbuff, len);
   	 }
		
	} /* dec if zero 15-04-08 Bug fix 2657 by Amaresh*/
	else
	{
			BSSAP_ERROR(("ProcessOUTBSSMAPMessage: BSS-MAP payload "" decode failed & fill dec to zero\n"));
			bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EENCODE);
			return (!ITS_SUCCESS);
	}  /* dec if zero 15-04-08 Bug fix 2657 by Amaresh*/
	    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing incoming CO MAP msgs from MSC 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0380, ID :: D0400,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessInBSSMAPMessage(BSSAP_Call* call, BSSAP_Message* mMap, ITS_OCTET *data, ITS_UINT len)
{
    ITS_INT ret = 0;
    ITS_OCTET mType = 0;
    BSSAP_Error err;
    BSSAP_Interface intface;
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */

    BSSAP_DEBUG(("BSSAP_Map: ProcessInBSSMAPMessage\n"));
    mType = mMap->GetMsgType();     

    if (IsUDT(mType) && (mType != BSSAP_MSG_CONFUSION))
    {
       BSSAP_ERROR(("ProcessInBSSMAPMessage: Recv. UDT MAP as CO\n"));
       ret = err.SendConfunsion(call, C_PROTOCOL_ERROR, 0, NULL, 0);
       return (ret);
    }
    ret = DirectionCheck(mType, ITS_TRUE);                                                                                                                   
    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessInBSSMAPMessage: message %d\n", mType));
	 /*change for nepal problem*/
        if(mType != 0x2f)
        {	    
            BSSAP_ERROR(("ProcessInBSSMAPMessage: Wrong message direction %d\n",mType));
            err.SendConfunsion(call, ITS_EBSSAP_UNKNOWN_MSG_TYPE, 0, data, len);
            /* Added by Amaresh for Alarm 21-07-08 */
            cfgdata = db.FetchRPCEntry(call->GetBssId());
            if (cfgdata)
            {
              DPC = cfgdata->rpc;
            }
            /* Added by Amaresh for Alarm 21-07-08 */
            BSSAP_Alarm_CCITT(5115,__FILE__,__LINE__,"dpc %d",DPC);
        }	    


       return (ret);
    }
    if (mType == BSSAP_MSG_HANDOVER_REQUEST)
    {
        call->SetCallType(HO_CALL);
				call->SetHandOver(1);	
				call->SetHandOverNewBss(1); /* Added by Amaresh for newBss */
				call->SetAppId(0);/* Added by Amaresh for newBss appid to zero as on dated 19-05-08 */
    }

    ret = ProcessCOMapProcedures(mMap, call, call->GetSLR(), ITS_TRUE, data, len); 
    if (ret == ITS_SUCCESS)
    {
        intface.DispatchMapToApp(call, mMap);
    }
	   return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing incoming CL MAP msgs from MSC 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0380, ID :: D0400,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessInBSSMAPUDTMessage(BSSAP_Message* msg, ITS_OCTET nwId, ITS_OCTET *data, ITS_UINT len)
{
    ITS_INT ret;
    ITS_OCTET msgType; 
    BSSAP_Interface intface;
    BSSAP_Error err;

    BSSAP_DEBUG(("BSSAP_Map: ProcessInBSSMAPUDTMessage\n"));
    msgType = msg->GetMsgType();
    if (IsUDT(msg->GetMsgType()))
    {
        ret = ProcessUDTMapProcedures(msg, nwId, ITS_TRUE, data, len);
        if (ret == ITS_SUCCESS)
        {
            intface.DispatchMapUDTtoApp(msg, nwId, data, len);
        }
    }
    else
    {
        BSSAP_ERROR(("ProcessInBSSMAPUDTMessage: Recv. CO MAP as UDT\n"));
        /* fix for bug id  482 & 492 by Amaresh if wrong UDT like CipherMCmd messgae -->cipherMReject */
      	if(msgType == BSSAP_MSG_CIPHER_MODE_CMD)
    		{
            BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP wrong UDT  message  & send Cipher Mode Reject of msg type CipherMCommand \n"));
            err.SendCipherModeReject(NULL,C_PROTOCOL_ERROR, nwId);  /*for bug id 492 */
        }
       else
        {
            BSSAP_ERROR(("ProcessInBSSAPMessage: wrong UDT message\n"));
        }
	     if(msgType == BSSAP_MSG_ASSIGN_REQUEST)
		   {
            BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP wrong UDT  message  & send Assign Failure of msg type Assignment Request \n"));
            err.SendAssignmentFail(NULL,C_PROTOCOL_ERROR, nwId);  /*for bug id 492 */
       }
      else
       {
            BSSAP_ERROR(("ProcessInBSSAPMessage: wrong UDT message\n"));
       }

	    if(msgType == BSSAP_MSG_HANDOVER_REQUEST)
       {
            BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP wrong UDT  message  & send HANDOVER FAILURE of msg type HANDOVER REQUEST \n"));
            err.SendHandoverFail(NULL,C_PROTOCOL_ERROR, nwId);  /*for bug id 492 */
       }
      else
       {
           BSSAP_ERROR(("ProcessInBSSAPMessage: wrong UDT message\n"));
       }

	   if(msgType == BSSAP_MSG_VGCS_VBS_SETUP)
      {
            BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP wrong UDT  message  & send VGCS/VBS SETUP REFUSE of msg type VGCS/VBS SETUP \n"));
            err.SendVGCSVBSSetupRefuse(NULL,C_PROTOCOL_ERROR, nwId);  /*for bug id 492 */
      }
     else
     {
           BSSAP_ERROR(("ProcessInBSSAPMessage: wrong UDT message\n"));
     }

	  if(msgType == BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST)
     {
         BSSAP_ERROR(("ProcessInBSSAPMessage: BSS-MAP wrong UDT  message  & send BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST of msg type BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE \n"));
         err.SendVGCSVBSAssFail(NULL,C_PROTOCOL_ERROR, nwId);  /*for bug id 492 */
     }
    else
     {
         BSSAP_ERROR(("ProcessInBSSAPMessage: wrong UDT message\n"));
     }

		
     /* fix for bug id  482 & 492 by Amaresh if wrong UDT like CipherMCmd messgae -->cipherMReject */
	   ret = err.SendConfunsion(NULL, C_PROTOCOL_ERROR, nwId, NULL, 0);
   }
     return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Sending complete layer3 information messages to remote as CR
* INPUT:
*       call object
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if done successfully
*       Error, if error occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0380, ID :: D0400,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Map::ProcessOutL3Message(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_SCCPHandler hndl;

    BSSAP_DEBUG(("BSSAP_Map: ProcessOutL3Message\n"));
    ret = hndl.SendCR(call);

    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutL3Message: Fail to send L3 message\n"));
        delete call;
        call = NULL;
        return (ret);
    }
    ret = BSSAP_CallDB::GetShared().Add(call);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutL3Message: Fail to update CDR %d\n",
                                                           call->GetSLR()));
    }
    delete call;
    call = NULL;
    return (ret);
}

