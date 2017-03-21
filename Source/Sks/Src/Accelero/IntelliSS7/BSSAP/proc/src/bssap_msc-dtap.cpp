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
 * ID: $Id: bssap_msc-dtap.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.8  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.7  2005/11/30 06:45:42  mkrishna
 * LOG: Pegs and progress msg implementation
 * LOG:
 * LOG: Revision 1.1.2.6  2005/11/28 05:18:14  adutta
 * LOG: Timer 3250 implemented (Issue fixed)
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/18 06:35:32  mkrishna
 * LOG: Changed API
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/17 06:30:17  mkrishna
 * LOG: Auth. Req/Ident. Req. procedures added
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/08 07:12:17  mkrishna
 * LOG: Procedures added for Location Update
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/14 10:12:44  adutta
 * LOG: function returns validated
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#include <bssap_msc-dtap.h>
#include <bssap_msc-fsm.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-interface.h>
#include <bssap_msc-sccphandler.h>
#include <bssap_msc-pegs.h>

its::Mutex* BSSAP_Dtap::mutex;

/*implementation:internal
*
* PURPOSE:
*       Start timer for Authentication Request 
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
* mkrishna  10-11-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessAuthenReq(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Timer t(BSSAP_T_3260);

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessAuthenReq\n"));

    // Start BSSAP_T_3260
    ret = t.StartTimer(call);
    call->SetTimerName(BSSAP_T_3260);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Cancel timer for Authentication Response 
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
* mkrishna  10-11-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessAuthenRespInd(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Timer t(BSSAP_T_3260);

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessAuthenRespInd\n"));

    // Cancel BSSAP_T_3260 timer
    ret = t.CancelTimer(call);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Start timer for Identity Request 
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
* mkrishna  10-11-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessIdentityReq(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Timer t(BSSAP_T_3270);

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessIdentityReq\n"));

    // Start BSSAP_T_3270 
    ret = t.StartTimer(call);
    call->SetTimerName(BSSAP_T_3270);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Cancel timer for Identity Response 
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
* mkrishna  10-11-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessIdentityRespInd(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Timer t(BSSAP_T_3270);

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessIdentityRespInd\n"));

    // Cancel BSSAP_T_3270
    ret = t.CancelTimer(call);

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Start timer for TMSI Reallocation Command 
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
* mkrishna  10-11-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessTmsiReallocCmdReq(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Timer t(BSSAP_T_3250);
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Dtap: ProcessTmsiReallocCmdReq\n"));
                                                                                                                                              
    // Start BSSAP_T_3250
    ret = t.StartTimer(call);
    call->SetTimerName(BSSAP_T_3250);
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Cancel timer for TMSI Reallocation Complete 
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
* mkrishna  10-11-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessTmsiReallocCmpInd(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Timer t(BSSAP_T_3250);
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Dtap: ProcessTmsiReallocCmpInd\n"));
                                                                                                                                              
    // Cancel BSSAP_T_3250
    ret = t.CancelTimer(call);
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       performing checks to outgoing msgs based on previous msg type 
* INPUT:
*       call object, msg type, toApp 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0410,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessDTAPProcedures(BSSAP_Call* call, 
                                  ITS_OCTET mType,
                                  ITS_BOOLEAN toApp)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET pvType = 0;
    ITS_OCTET callType = 0;

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessDTAPProcedures\n"));

    pvType = call->GetMssgType();

    callType = call->GetCallType();

    if (callType != MO_CALL && callType != MT_CALL && callType != LU_CALL)
    {
        BSSAP_ERROR(("ProcessDTAPProcedures: BSS-DTAP procedure w/o call %d\n",
                                                                    callType));
        return (!ITS_SUCCESS);
    }

    if (!toApp)
    {
        switch (mType)
        {
            case BSSAP_MSG_AUTHENTICATION_REQUEST:
                if (((pvType == BSSAP_MSG_CM_SERVICE_REQUEST) && 
                    (callType != MO_CALL)) ||
                    ((pvType == BSSAP_MSG_PAGING_RESPONSE) && 
                    (callType != MT_CALL)) ||
                    ((pvType == BSSAP_MSG_LOCATION_UPDATING_REQUEST) &&
                    (callType != LU_CALL)))
                {
                    ret = (!ITS_SUCCESS);
                    break;
                }
                ret = ProcessAuthenReq(call); 
            break;
            case BSSAP_MSG_AUTHENTICATION_REJECT:
            case BSSAP_MSG_CM_SERVICE_REJECT:
            case BSSAP_MSG_CM_SERVICE_ACCEPT:
                if (pvType != BSSAP_MSG_AUTHENTICATION_RESPONSE)
                {   
                    ret = (!ITS_SUCCESS);
                }       
            break;
            case BSSAP_MSG_TMSI_REALLOC_COMMAND:
                if (call->GetTmsiReallocCmd())
                {
                    ret = ProcessTmsiReallocCmdReq(call);
                }
                else
                {
                    ret = (!ITS_SUCCESS);
                } 
            break;
            case BSSAP_MSG_IDENTITY_REQUEST:
                ret = ProcessIdentityReq(call);
            break;
            case BSSAP_CC_MSG_PROGRESS:
                if (pvType != BSSAP_CC_MSG_SETUP)
                {
                    ret = (!ITS_SUCCESS);
                }   
            break;
        }
    }
    else
    {
        switch (mType)
        {
            case BSSAP_MSG_AUTHENTICATION_RESPONSE:
            case BSSAP_MSG_AUTHENTICATION_FAILURE:
                if (pvType != BSSAP_MSG_AUTHENTICATION_REQUEST)
                {
                    ret = (!ITS_SUCCESS);
                    break;
                }
                ret = ProcessAuthenRespInd(call);
            break;
            case BSSAP_MSG_IDENTITY_RESPONSE:
                if (pvType != BSSAP_MSG_IDENTITY_REQUEST)
                {  
                    ret = (!ITS_SUCCESS);
                    break;
                }      
                ret = ProcessIdentityRespInd(call);
            break;
            case BSSAP_MSG_TMSI_REALLOC_COMPLETE:
                if (pvType != BSSAP_MSG_TMSI_REALLOC_COMMAND)
                {
                    ret = (!ITS_SUCCESS);
                    break;
                }
                ret = ProcessTmsiReallocCmpInd(call);
            break;
        }
    }
   
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       checking message direction 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0410, ID :: D0920
*/
ITS_INT
BSSAP_Dtap::DirectionCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: DirectionCheck\n"));

    if (!up)
    {
        BSSAP_DEBUG(("DirectionCheck: Down (MSC -> BSS) event\n"));

        switch (evId)
        {
           case BSSAP_MSG_AUTHENTICATION_REQUEST:
           case BSSAP_MSG_AUTHENTICATION_REJECT:
           case BSSAP_MSG_IDENTITY_REQUEST:
           case BSSAP_MSG_TMSI_REALLOC_COMMAND:
           case BSSAP_MSG_LOCATION_UPDATING_ACCEPT:
           case BSSAP_MSG_LOCATION_UPDATING_REJECT:
           case BSSAP_MSG_CM_SERVICE_REJECT:
           case BSSAP_MSG_CM_SERVICE_ACCEPT:
           case BSSAP_MSG_ABORT:
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
           case BSSAP_MSG_AUTHENTICATION_RESPONSE:
           case BSSAP_MSG_AUTHENTICATION_FAILURE:
           case BSSAP_MSG_IDENTITY_RESPONSE:
           case BSSAP_MSG_TMSI_REALLOC_COMPLETE:
           case BSSAP_MSG_LOCATION_UPDATING_REQUEST:
           case BSSAP_MSG_IMSI_DETACH_INDICATION:
           case BSSAP_MSG_CM_SERVICE_REQUEST:
           case BSSAP_MSG_CM_SERVICE_ABORT:
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
*       performing sanity checks on MT calls 
* INPUT:
*       msg type, up 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0410, ID :: D0920
*/
ITS_INT
BSSAP_Dtap::MTSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: MTSanityCheck\n"));

    if (!up)
    {
        BSSAP_DEBUG(("MTSanityCheck: Down event\n"));

        switch (evId)
        {
           case BSSAP_MSG_PAGING_RESPONSE:
           case BSSAP_CC_MSG_CALL_CONFIRMED:
           case BSSAP_CC_MSG_ALERTING:
           case BSSAP_CC_MSG_CONNECT:
           case BSSAP_CC_MSG_PROGRESS: 
              return (!ITS_SUCCESS);

           default:
              break;
        }           
    }
    else
    {
        BSSAP_DEBUG(("MTSanityCheck: Up event\n"));

        switch (evId)
        {
           case BSSAP_CC_MSG_SETUP:
           case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
           case BSSAP_CC_MSG_PROGRESS: 
              return (!ITS_SUCCESS);
           
           default:
              break;
        }
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       performing sanity checks on MO calls 
* INPUT:
*       msg type, up 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0410, ID :: D0920
*/
ITS_INT
BSSAP_Dtap::MOSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: MOSanityCheck\n"));

    if (!up)
    {
        BSSAP_DEBUG(("MOSanityCheck: Down event\n"));

        switch (evId)
        {
           case BSSAP_MSG_CM_SERVICE_REQUEST:
           case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
           case BSSAP_CC_MSG_SETUP:
              return (!ITS_SUCCESS);

           default:
              break;
        }
    }
    else
    {
        BSSAP_DEBUG(("MOSanityCheck: Up event\n"));

        switch (evId)
        {
           case BSSAP_CC_MSG_CALL_PROCEEDING:
           case BSSAP_CC_MSG_ALERTING:
           case  BSSAP_CC_MSG_CONNECT:
           case BSSAP_CC_MSG_PROGRESS: 
              return (!ITS_SUCCESS);

           default:
              break;
        }
    }

    return (ITS_SUCCESS);
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
*                        ID :: D0380, ID :: D0920
*/
void
BSSAP_Dtap::Initialize()
{
    BSSAP_DEBUG(("BSSAP_Dtap: Initialize()"));

    mutex = new Mutex(0);
}

/*implementation:internal
*
* PURPOSE:
*       handling incoming call control messages 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0390, ID :: D0920
*/
ITS_INT
BSSAP_Dtap::HandleInCCMessage(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_Interface intface; 

    BSSAP_DEBUG(("BSSAP_Dtap: HandleInCCMessage %d\n", call->GetSLR()));

    if (mutex->Acquire() != ITS_SUCCESS)
    {
        BSSAP_ERROR(("HandleInCCMessage: Mutex acquire failed\n"));
    }

    BSSAPEvent ev(call->GetCurrentEvent());

    ev.SetCallRefId(call->GetSLR());
    ev.SetCallObject(call);

    if (call->GetCallType() == MT_CALL)
    {
        ret = MTSanityCheck(call->GetCurrentEvent(), ITS_TRUE);
        if (ret == ITS_SUCCESS)
        {
            FsmMT::GetShared().SetState(call->GetPrevEvent());
            ret = FsmMT::GetShared().ProcessEvent(ev);
        }
        else
        {
            BSSAP_WARNING(("HandleInCCMessage: Invalid event " 
                        "in MT state %s\n", DTAP_STR(call->GetCurrentEvent())));

            call->SetCurrentEvent(call->GetPrevEvent());
        }
    }
    else if((call->GetCallType() == MO_CALL) || 
            (call->GetCallType() == HO_CALL))
    {
        ret = MOSanityCheck(call->GetCurrentEvent(), ITS_TRUE);
        if (ret == ITS_SUCCESS)
        {
            FsmMO::GetShared().SetState(call->GetPrevEvent());
            ret = FsmMO::GetShared().ProcessEvent(ev); 
        }
        else
        {
            BSSAP_WARNING(("HandleInCCMessage: Invalid event " 
                        "in MO state %s\n", DTAP_STR(call->GetCurrentEvent())));

            call->SetCurrentEvent(call->GetPrevEvent());
        }
    }
    else if (call->GetCallType() == LU_CALL)
    {
        BSSAP_DEBUG(("HandleInCCMessage: Recvd location update call \n"));

        intface.DispatchMsgToApp(call);
    }
    else
    {
        BSSAP_WARNING(("HandleInCCMessage: Invalid state\n"));
      
        ret =  !ITS_SUCCESS;
    }

    if (mutex->Release() != ITS_SUCCESS)
    {
        BSSAP_ERROR(("HandleInCCMessage: Mutex release failed\n"));
    }

    return (ret);
}
/*implementation:internal
*
* PURPOSE:
*       Handling incoming RR or MM DTAP messages
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*/
ITS_INT
BSSAP_Dtap::ProcessLayer3BSSAPMessage(BSSAP_Call* call, BSSAP_Message* mMap)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET* buff = NULL;
    ITS_INT len = 0;

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessLayer3BSSAPMessage\n"));
                                                                                                                                              
    buff = call->GetBSSAPData(&len);
                                                                                                                                              
    if (((buff[3] & PD_PROT_DISCR_BIT) == PD_MOBILITY_MGMT_MSGS_NON_GPRS) ||
        ((buff[3] & PD_PROT_DISCR_BIT) == PD_RADIO_RESRC_MGMT_MSGS ))
    {
        BSSAP_DEBUG(("ProcessLayer3BSSAPMessage: Recvd. non CC from BSS\n"));
                                                                                                                                              
        call->SetPrevEvent(call->GetCurrentEvent());
        call->SetCurrentEvent(buff[DTAP_MSG_P0S]);

        call->SetMssgType(mMap->GetMsgType());
                                                                                                                                              
        ret = HandleInCCMessage(call);
    }
    else
    {
        BSSAP_ERROR(("ProcessLayer3BSSAPMessage: neither RR nor MM \n")); 
        return (!ITS_SUCCESS);
    } 

    if (ret == ITS_SUCCESS)
    {
        ret = BSSAP_CallDB::GetShared().Add(call);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_CRITICAL(("ProcessLayer3BSSAPMessage: "
                            "Fail to update CDR %d\n", call->GetSLR()));
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Handling incoming DTAP messages 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0390, ID :: D0420,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessInDTAPMessage(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_OCTET* buff = NULL;
    ITS_INT len = 0;
    BSSAP_Interface intface; 

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessInDTAPMessage\n"));

    buff = call->GetBSSAPData(&len);

    if ((buff[3] & PD_PROT_DISCR_BIT) == PD_CALL_CONTROL_MSGS)
    {

        if (call->GetMssgType() == BSSAP_CC_MSG_TIMEOUT_IND)
        {
            BSSAP_ERROR(("ProcessInDTAPMessage: Received event in wrong state\n"));
                                                                                                                                              
            return (!ITS_SUCCESS);
        }

        BSSAP_DEBUG(("ProcessInDTAPMessage: Recvd. CC from BSS\n")); 

        call->SetPrevEvent(call->GetCurrentEvent());

        if (buff[DTAP_MSG_P0S] == BSSAP_CC_MSG_DISCONNECT)
        {
            if (call->GetMssgType() == BSSAP_CC_MSG_RELEASE)
            {
                BSSAP_ERROR(("ProcessInDTAPMessage: DISCONNECT IND is not "
                             "allowed in this state \n"));
                return (!ITS_SUCCESS);
            } 
            call->SetCurrentEvent(BSSAP_CC_MSG_DISCONNECT_IND);
        }
        else if (buff[DTAP_MSG_P0S] == BSSAP_CC_MSG_RELEASE)
        {
            if (call->GetMssgType() == BSSAP_CC_MSG_RELEASE)
            {
                BSSAP_ERROR(("ProcessInDTAPMessage: RELEASE IND is not "
                             "allowed in this state \n"));
                return (!ITS_SUCCESS);
            }
            call->SetCurrentEvent(BSSAP_CC_MSG_RELEASE_IND);
        }
        else if (buff[DTAP_MSG_P0S] == BSSAP_CC_MSG_RELEASE_COMPLETE)
        {
            call->SetCurrentEvent(BSSAP_CC_MSG_RELEASE_COMPLETE_IND);
        }
        else
        {
            call->SetCurrentEvent(buff[DTAP_MSG_P0S]);
        }

        call->SetMssgType(buff[DTAP_MSG_P0S]);

        ret = HandleInCCMessage(call);
    }
    else
    {
        BSSAP_DEBUG(("ProcessInDTAPMessage: Recvd non CC from network\n")); 

        ret = DirectionCheck(buff[DTAP_MSG_P0S], ITS_TRUE);

        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("ProcessInDTAPMessage: Wrong message direction %d\n",
                                                           buff[DTAP_MSG_P0S]));
           return (ret);
        }
        else
        {
            ret = ProcessDTAPProcedures(call, buff[DTAP_MSG_P0S], ITS_TRUE);
            if (ret == ITS_SUCCESS)
            {
                call->SetMssgType(buff[DTAP_MSG_P0S]);

                intface.DispatchMsgToApp(call); 
            }
        }
    } 

    if (ret == ITS_SUCCESS)
    {
        ret = BSSAP_CallDB::GetShared().Add(call);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_CRITICAL(("ProcessInDTAPMessage: Fail to update CDR %d\n",
                                                           call->GetSLR()));
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Handling outgoing call control messages 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0390, ID :: D0920
*/
ITS_INT
BSSAP_Dtap::HandleOutCCMessage(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS; 

    BSSAP_DEBUG(("BSSAP_Dtap: HandleOutCCMessage %d\n", call->GetSLR()));

    if (mutex->Acquire() != ITS_SUCCESS)
    {
        BSSAP_ERROR(("HandleOutCCMessage: Mutex acquire failed\n"));
    }

    BSSAPEvent ev(call->GetCurrentEvent());

    ev.SetCallRefId(call->GetSLR());
    ev.SetCallObject(call);

    if (call->GetCallType() == MT_CALL)
    {
        ret = MTSanityCheck(call->GetCurrentEvent(), ITS_FALSE);
        if (ret == ITS_SUCCESS)
        {
            FsmMT::GetShared().SetState(call->GetPrevEvent());
            ret = FsmMT::GetShared().ProcessEvent(ev);
        }
        else
        {
            call->SetCurrentEvent(call->GetPrevEvent());

            BSSAP_WARNING(("HandleOutCCMessage: Invalid event "
                        "in MT state %s\n", DTAP_STR(call->GetCurrentEvent())));
        }
    }
    else if( call->GetCallType() == MO_CALL)
    {
        ret = MOSanityCheck(call->GetCurrentEvent(), ITS_FALSE);
        if (ret == ITS_SUCCESS)
        {
            FsmMO::GetShared().SetState(call->GetPrevEvent());
            ret = FsmMO::GetShared().ProcessEvent(ev);
        }
        else
        {
            call->SetCurrentEvent(call->GetPrevEvent());

            BSSAP_WARNING(("HandleOutCCMessage: Invalid event "
                        "in MO state %s\n", DTAP_STR(call->GetCurrentEvent())));
        }
    }
    else
    {}

    if (mutex->Release() != ITS_SUCCESS)
    {
        BSSAP_ERROR(("HandleOutCCMessage: Mutex acquire failed\n"));
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       processing outgoing DTAP messages 
* INPUT:
*       payload object 
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0420, ID :: D0440,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Dtap::ProcessOutDTAPMessage(BSSAP_Api* msg)
{
    BSSAP_Call* call = NULL;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    ITS_INT len = 0;
    ITS_INT ret = 0;
    ITS_OCTET mssgType = 0;
    BSSAP_Interface bssIf;
    BSSAP_Message* mMap;
 
    BSSAP_DEBUG(("BSSAP_Dtap: ProcessOutDTAPMessage\n"));

    mMap = msg->GetBSSAPdata();

    if (BSSAP_Message::Encode(buff, len, mMap) != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutDTAPMessage: DTAP Encode fail\n"));
                                                                                                                                          
        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EENCODE);
                                                                                                                                              
        delete mMap;
                                                                                                                                              
        return (ITS_SUCCESS);
    }

    mssgType = mMap->GetMsgType();

    call = BSSAP_CallDB::GetShared().Fetch(msg->GetCallRef());
    if (!call)
    {   
        BSSAP_ERROR(("ProcessOutDTAPMessage: Call obj. not found \n"));

        return (ITS_ENOTFOUND);
    }   

    call->SetAppId(msg->GetAppId());
    call->SetSLR(msg->GetCallRef());
    call->SetBSSAPData(buff, len);

    if ((buff[DTAP_PDISCR_POS] & PD_PROT_DISCR_BIT) == PD_CALL_CONTROL_MSGS)
    {
        BSSAP_DEBUG(("ProcessOutDTAPMessage: Recvd. CC from app\n")); 

        call->SetPrevEvent(call->GetCurrentEvent());
        call->SetCurrentEvent(mssgType);

        ret = HandleOutCCMessage(call);
        if (ret == ITS_SUCCESS)
        { 
            call->SetMssgType(mssgType);
        }
    }
    else
    {
        BSSAP_DEBUG(("ProcessOutDTAPMessage: Recvd. non CC from app\n")); 

        ret = DirectionCheck(mssgType, ITS_FALSE);

        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("ProcessOutDTAPMessage: Wrong message direction %d\n",
                                                                   mssgType));
            return (ret);
        }
        else
        { 
            ret = ProcessDTAPProcedures(call, mssgType, ITS_FALSE);
            if (ret == ITS_SUCCESS)
            {
                call->SetMssgType(mssgType);

                ret = hndl.BSSAP_ProcessAPPdata(call);
            }
            else
            {
                return (ret);
            }
        }
    }

    if (ret == ITS_SUCCESS)
    {
        ret = BSSAP_CallDB::GetShared().Add(call);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("ProcessOutDTAPMessage: Fail to update CDR %d\n",
                                                           call->GetSLR()));
        }

        PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DTAP_SEND);
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
ITS_INT
BSSAP_Dtap::ProcessOutL3Message(BSSAP_Call* call)
{
    ITS_INT ret = 0;
    
    BSSAP_DEBUG(("BSSAP_Dtap: ProcessOutL3Message\n"));

    ret = HandleOutCCMessage(call);

    ret = BSSAP_CallDB::GetShared().Add(call);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_ERROR(("ProcessOutL3Message: Fail to update CDR %d\n",
                                                           call->GetSLR()));
    }

    return (ret);
}
