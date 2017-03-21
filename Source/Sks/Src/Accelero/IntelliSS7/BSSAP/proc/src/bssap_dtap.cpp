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
 *  ID: $Id: bssap_dtap.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.14  2006/07/14 16:59:39  sjaddu
 * LOG: Connection Id is changed to U INT.
 * LOG:
 * LOG: Revision 1.1.2.13  2005/10/06 08:48:42  adutta
 * LOG: Call object commit only for CC DTAP
 * LOG:
 * LOG: Revision 1.1.2.12  2005/10/06 08:33:02  adutta
 * LOG: Mutex release
 * LOG:
 * LOG: Revision 1.1.2.11  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.10  2005/08/28 04:10:19  adutta
 * LOG: Some corrections in MT/MO flow
 * LOG:
 * LOG: Revision 1.1.2.9  2005/08/26 20:19:13  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.8  2005/08/26 06:41:24  adutta
 * LOG: FSM changes
 * LOG:
 * LOG: Revision 1.1.2.7  2005/08/21 15:43:11  adutta
 * LOG: Few changes for non cc dtaps
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/20 18:16:44  adutta
 * LOG: Fix for MO call
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/19 20:05:31  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/19 11:04:50  adutta
 * LOG: Handling disconnect from remote
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 10:33:09  adutta
 * LOG: Initialized the fsm object
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/

#include <bssap_dtap.h>
#include <bssap_fsm.h>
#include <bssap_calldb.h>
#include <bssap_interface.h>
#include <bssap_sccphandler.h>

its::Mutex* BSSAP_Dtap::mutex;

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

    if (callType != MO_CALL && callType != MT_CALL)
    {
        BSSAP_ERROR(("ProcessDTAPProcedures: BSS-DTAP procedure w/o call %d\n",
                                                                     callType));

        return (!ITS_SUCCESS);
    }

    if (toApp)
    {
        switch (mType)
        {
            case BSSAP_MSG_AUTHENTICATION_REQUEST:
            case BSSAP_MSG_AUTHENTICATION_REJECT:
                if (pvType != BSSAP_MSG_CM_SERVICE_REQUEST)
                {
                    return (!ITS_SUCCESS);
                }
            break;
            case BSSAP_MSG_CM_SERVICE_REJECT:
            case BSSAP_MSG_CM_SERVICE_ACCEPT:
                if (pvType != BSSAP_MSG_AUTHENTICATION_RESPONSE)
                {   
                    return (!ITS_SUCCESS);
                }       
            break;
            case BSSAP_MSG_TMSI_REALLOC_COMMAND:
                if (pvType != BSSAP_MSG_CIPHER_MODE_COMPLETE ||
                            pvType != BSSAP_MSG_IDENTITY_RESPONSE)
                {  
                    return (!ITS_SUCCESS);
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
                    return (!ITS_SUCCESS);
                }
            break;
            case BSSAP_MSG_IDENTITY_RESPONSE:
                if (pvType != BSSAP_MSG_IDENTITY_REQUEST)
                {  
                    return (!ITS_SUCCESS);
                }      
            break;
        }
    }
   
    return (ret);
}

ITS_INT
BSSAP_Dtap::DirectionCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: DirectionCheck\n"));

    if (up)
    {
        BSSAP_DEBUG(("DirectionCheck: Up (Network -> MS) event\n"));

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
        BSSAP_DEBUG(("DirectionCheck: Down (MS -> Network) event\n"));

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

/****************************************************************************
 *  Purpose:
 *         
 *  Input Parameters:
 *      None.
 *         
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0250
 *****************************************************************************/
ITS_INT
BSSAP_Dtap::MTSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: MTSanityCheck\n"));

    if (up)
    {
        BSSAP_DEBUG(("MTSanityCheck: Up event\n"));

        switch (evId)
        {
           case BSSAP_MSG_PAGING_RESPONSE:
           case BSSAP_CC_MSG_CALL_CONFIRMED:
           case BSSAP_CC_MSG_ALERTING:
           case BSSAP_CC_MSG_CONNECT:
              return (!ITS_SUCCESS);

           default:
              break;
        }           
    }
    else
    {
        BSSAP_DEBUG(("MTSanityCheck: Down event\n"));

        switch (evId)
        {
           case BSSAP_CC_MSG_SETUP:
           case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
              return (!ITS_SUCCESS);
           
           default:
              break;
        }
    }

    return (ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *         
 *  Input Parameters:
 *      None.
 *         
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0250
 *****************************************************************************/
ITS_INT
BSSAP_Dtap::MOSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up)
{
    BSSAP_DEBUG(("BSSAP_Dtap: MOSanityCheck\n"));

    if (up)
    {
        BSSAP_DEBUG(("MOSanityCheck: Up event\n"));

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
        BSSAP_DEBUG(("MOSanityCheck: Down event\n"));

        switch (evId)
        {
           case BSSAP_CC_MSG_CALL_PROCEEDING:
           case BSSAP_CC_MSG_ALERTING:
           case  BSSAP_CC_MSG_CONNECT:
              return (!ITS_SUCCESS);

           default:
              break;
        }
    }

    return (ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *         
 *  Input Parameters:
 *      None.
 *         
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0250
 *****************************************************************************/
void
BSSAP_Dtap::Initialize()
{
    BSSAP_DEBUG(("BSSAP_Dtap: Initialize()\n"));

    mutex = new Mutex(0);
}

/****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0250
 *****************************************************************************/
ITS_INT
BSSAP_Dtap::HandleInCCMessage(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;

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
            FsmMT::GetShared().ProcessEvent(ev);
        }
        else
        {
            call->SetCurrentEvent(call->GetPrevEvent());

            BSSAP_WARNING(("HandleInCCMessage: Invalid event " 
                        "in MT state %s\n", DTAP_STR(call->GetCurrentEvent())));
        }
    }
    else if( call->GetCallType() == MO_CALL)
    {
        ret = MOSanityCheck(call->GetCurrentEvent(), ITS_TRUE);
        if (ret == ITS_SUCCESS)
        {
            FsmMO::GetShared().SetState(call->GetPrevEvent());
            FsmMO::GetShared().ProcessEvent(ev); 
        }
        else
        {
            call->SetCurrentEvent(call->GetPrevEvent());

            BSSAP_WARNING(("HandleInCCMessage: Invalid event " 
                        "in MO state %s\n", DTAP_STR(call->GetCurrentEvent())));
        }
    }
    else
    {
        BSSAP_WARNING(("HandleInCCMessage: Invalid state\n"));

        ret = !ITS_SUCCESS;
    }

    if (mutex->Release() != ITS_SUCCESS)
    {
        BSSAP_ERROR(("HandleInCCMessage: Mutex release failed\n"));
    }

    if (ret == ITS_SUCCESS)
    {
        ret = BSSAP_CallDB::GetShared().Add(call);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_CRITICAL(("HandleInCCMessage: Fail to add call record\n"));
        }
    }

    return (ret);
}


/****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0240
 *****************************************************************************/
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
        call->SetMssgType(buff[DTAP_MSG_P0S]);

        BSSAP_DEBUG(("ProcessInDTAPMessage: Recvd. CC from network\n")); 

        call->SetPrevEvent(call->GetCurrentEvent());

        if (buff[DTAP_MSG_P0S] == BSSAP_CC_MSG_DISCONNECT)
        {
            call->SetCurrentEvent(BSSAP_CC_MSG_DISCONNECT_IND);
        }
        else if (buff[DTAP_MSG_P0S] == BSSAP_CC_MSG_RELEASE)
        {
            call->SetCurrentEvent(BSSAP_CC_MSG_RELEASE_IND);
        }
        else
        {
            call->SetCurrentEvent(buff[DTAP_MSG_P0S]);
        }

        HandleInCCMessage(call);
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

                intface.DispatchDtapToApp(call); 
            }
        }
    } 

    return (ret);
}

/****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                         Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0250
 *****************************************************************************/
ITS_INT
BSSAP_Dtap::HandleOutCCMessage(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    BSSAP_SCCPHandler hndl;

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
            FsmMT::GetShared().ProcessEvent(ev);
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
            FsmMO::GetShared().ProcessEvent(ev);
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

    if (ret == ITS_SUCCESS)
    {
        ret = BSSAP_CallDB::GetShared().Add(call);
        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("HandleOutCCMessage: Fail to update CDR %d\n",
                                                           call->GetSLR()));
        }
    }

    return (ret);
}

/****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0240
 *****************************************************************************/
ITS_INT
BSSAP_Dtap::ProcessOutDTAPMessage(BSSAP_Payload* msg)
{
    BSSAP_Call* call = NULL;
    ITS_OCTET buff[BSSAP_DATA_LEN];
    BSSAP_SCCPHandler hndl;
    ITS_USHORT len = 0;
    ITS_INT ret = 0;
    ITS_OCTET mssgType = 0;
    BSSDtap* dtap = (BSSDtap*)msg;

    BSSAP_DEBUG(("BSSAP_Dtap: ProcessOutDTAPMessage\n"));

    dtap->GetDTAPdata(buff, &len);
    mssgType = buff[DTAP_MSG_P0S];

    call = BSSAP_CallDB::GetShared().Fetch(dtap->GetCallRef());
    if (!call)
    {   
        BSSAP_ERROR(("ProcessOutDTAPMessage: Call obj. not found \n"));

        return (ITS_ENOTFOUND);
    }   

    call->SetChannel(dtap->GetChannel());
    call->SetSLR(dtap->GetCallRef());
    call->SetBSSAPData(buff, len);

    if ((buff[DTAP_PDISCR_POS] & PD_PROT_DISCR_BIT) == PD_CALL_CONTROL_MSGS)
    {
        BSSAP_DEBUG(("ProcessOutDTAPMessage: Recvd. CC from app\n")); 

        call->SetPrevEvent(call->GetCurrentEvent());
        call->SetCurrentEvent(mssgType);
        call->SetMssgType(mssgType);

        ret = HandleOutCCMessage(call);
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

    return (ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                          Description
 *  --------------------------------------------------------------------------
 *  adutta    17/8/05     IMR-DESP-BSSAP-01-V1.1 ID::D0240
 *****************************************************************************/
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

    BSSAP_DEBUG(("BSSAP_Dtap: Connection Id  %d\n", call->GetAppId()));
    delete call;

    call = NULL;

    return (ret);
}
