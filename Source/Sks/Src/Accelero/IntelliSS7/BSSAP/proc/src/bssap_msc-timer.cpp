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
 * ID: $Id: bssap_msc-timer.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.6  2005/12/01 10:50:14  mkrishna
 * LOG: Pegs counter placed while resending messages
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/30 06:49:52  mkrishna
 * LOG: Resetdata timer intialised to zero(for abnormal case)
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/28 05:22:43  adutta
 * LOG: Fix for Issue#3064
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/17 06:32:50  mkrishna
 * LOG: Timer tries made configurable
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:18:56  mkrishna
 * LOG: Timeout proceudres for CktGrpBlk/CktGrpUnblk
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#include <bssap-msc.h>
#include <bssap_msc-timer.h>
#include <bssap_msc-fsm.h>
#include <bssap_msc-call.h>
#include <bssap_msc-calldb.h>
#include <bssap_msc-cicdb.h>
#include <bssap_msc-interface.h>
#include <bssap_msc-pegs.h>

extern ITS_OCTET TIMER_Tries[]; 
extern OverloadData oData;
extern ResetData rData;
extern ITS_BOOLEAN isFirst;

/*implementation:internal
*
* PURPOSE:
*       assigning the timer string 
* INPUT:
*       timer value 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       timer string 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0770, ID :: D0740
*/
ITS_CHAR*
BSSAP_Timer::GetTimerString(ITS_OCTET type)
{
    ITS_CHAR* name;

    switch(type)
    {
        case BSSAP_T_303:
            name = "BSSAP_T_303";
        break; 
        case BSSAP_T_310:
            name = "BSSAP_T_310";
        break; 
        case BSSAP_T_301:
            name = "BSSAP_T_301";
        break; 
        case BSSAP_T_306:
            name = "BSSAP_T_306";
        break; 
        case BSSAP_T_308:
            name = "BSSAP_T_308";
        break; 
        case BSSAP_T_313:
            name = "BSSAP_T_313";
        break;
        case BSSAP_T_2:
            name = "BSSAP_T_2";
        break;
        case BSSAP_T_5:
            name = "BSSAP_T_5";
        break;
        case BSSAP_T_6:
            name = "BSSAP_T_6";
        break;
        case BSSAP_T_12:
            name = "BSSAP_T_12";
        break;
        case BSSAP_T_16:
            name = "BSSAP_T_16";
        break;
        case BSSAP_T_21:
            name = "BSSAP_T_21";
        break;
        case BSSAP_T_22:
            name = "BSSAP_T_22";
        break;
        case BSSAP_T_3250:
            name = "BSSAP_T_3250";
        break;
        case BSSAP_T_3260:
            name = "BSSAP_T_3260";
        break;
        case BSSAP_T_3270:
            name = "BSSAP_T_3270";
        break;
        default:
            name = "Unknown Timer";
        break;
    }
   
    return (name);

}

/*implementation:internal
*
* PURPOSE:
*       starting accelero shared timer 
* INPUT:
*       callId, tries 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer started 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0720, ID :: D0740,
*                        ID :: D0710, ID :: D0920
*/
ITS_INT
BSSAP_Timer::StartTimer(BSSAP_Call* call, ITS_OCTET tries)
{

    ITS_SERIAL serial = 0;
    BSSAP_CALL_CTXT ctxt;

    memset(&ctxt, 0, sizeof(BSSAP_CALL_CTXT));

    ctxt.timerType = timer_type;
    ctxt.tries = tries;

    if (call)
    {
        ctxt.evtType = call->GetCurrentEvent();
        ctxt.callrefId = call->GetSLR();

        BSSAP_DEBUG(("BSSAP_Timer: StartTimer\n"));

        ITS_INT sec = TIMERS_GetTimerValue(&BSSAP_Timers, timer_type);

        serial = TIMERS_StartSharedTimer(ITS_BSSAP_SRC, sec, 
                                         (void*)&ctxt, sizeof(ctxt));
        if (serial)
        {
            BSSAP_DEBUG(("StartTimer: Started  timer (%d sec): %s\n", 
                                          sec, GetTimerString(timer_type)));
            call->SetTimerId(serial);
 
            return (ITS_SUCCESS);
        }
    }

    BSSAP_ERROR(("StartTimer: Fail to start timer : %s\n", 
                                     GetTimerString(timer_type)));

    return (ITS_ETIMERSTARTFAIL);
}

/*implementation:internal
*
* PURPOSE:
*       cancel accelero shared timer 
* INPUT:
*       callId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer stopped 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0720, ID :: D0740,
*                        ID :: D0710, ID :: D0920
*/
ITS_INT 
BSSAP_Timer::CancelTimer(BSSAP_Call* call)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_SERIAL serial = 0;

    BSSAP_DEBUG(("BSSAP_Timer: CancelTimer\n"));

    serial = call->GetTimerId();
    if (serial)
    {
        ret = TIMERS_CancelTimer(call->GetTimerId());
        if (ret == ITS_SUCCESS)
        {
            BSSAP_DEBUG(("CancelTimer: Canceled timer : %s\n", 
                                                 GetTimerString(timer_type))); 
        }
        call->SetTimerId(0);
    }
    else
    {
        BSSAP_WARNING(("CancelTimer: No running timer \n"));
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       hadling time outs for different msgs  
* INPUT:
*       context 
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
BSSAP_Timer::HandleTimeout(BSSAP_CALL_CTXT ctxt)
{
    BSSAP_Call* call = NULL;
    BSSAP_Interface intf;

    BSSAP_DEBUG(("BSSAP_Timer: HandleTimeout %s\n", 
                                               GetTimerString(ctxt.timerType)));

    if (ctxt.evtType == BSSAP_MSG_BLOCK)
    {
        ProcessBlockTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_UNBLOCK)
    {
        ProcessUnBlockTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_CKT_GROUP_BLOCK)
    {
        ProcessCktGroupBlkTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_CKT_GRP_UNBLOCK)
    {
        ProcessCktGroupUnblkTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_RESET)
    {
        ProcessResetTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_RESET_CIRCUIT)
    {
        ProcessResetCktTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_OVERLOAD)
    {
        ProcessOverloadTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_CC_MSG_RELEASE)
    {
        ProcessReleaseTimeout(ctxt);
    }
    else
    {
        call = BSSAP_CallDB::GetShared().Fetch(ctxt.callrefId);

        if (call)
        {
           call->SetMssgType(BSSAP_CC_MSG_TIMEOUT_IND);
        } 

        BSSAP_CallDB::GetShared().Add(call);

        intf.DispatchErrorToApp(call, BSSAP_MD_TIMEOUT, ctxt.timerType);
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       processing this function once time out happens from accelero timer
* INPUT:
*       event 
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
*                        ID :: D0740, ID :: D0710,
*                        ID :: D0750, ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessTimeout(ITS_Event& event)
{
    ITS_TimerData t_data;
    ITS_EVENT ev  = event.GetEvent();
    BSSAP_CALL_CTXT ctxt;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessTimeout \n"));
 
    memset((char*)&t_data, 0, sizeof(ITS_TimerData));
    memcpy((char*)&t_data, (char*)ev.data, sizeof(ITS_TimerData));

    memcpy((char*)&ctxt, t_data.context, sizeof(BSSAP_CALL_CTXT));
   
    HandleTimeout(ctxt);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       starting timer for UDT messages 
* INPUT:
*       cic, tries, msgtype, buff, len, nwId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer started successfully
*       Error, if problem occrs 
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0740, ID :: D0710,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::StartUDTTimer(ITS_USHORT cic, 
                           ITS_OCTET tries,
                           ITS_OCTET msgType,
                           ITS_OCTET* buff, 
                           ITS_INT len,
                           ITS_OCTET nwId)
{

    ITS_SERIAL serial = 0;
    BSSAP_Call* call = NULL;
    BSSAP_CALL_CTXT ctxt;

    BSSAP_DEBUG(("BSSAP_Timer: StartUDTTimer\n"));

    memset(&ctxt, 0, sizeof(BSSAP_CALL_CTXT));

    ctxt.destId = nwId;
    ctxt.evtType = msgType;
    ctxt.callrefId = cic;
    ctxt.timerType = timer_type;
    ctxt.tries = tries;
    if (buff)
    {
        memcpy(ctxt.mapData, buff, len);
        ctxt.dataLen = len;
    } 

    ITS_INT sec = TIMERS_GetTimerValue(&BSSAP_Timers, timer_type);

    serial = TIMERS_StartSharedTimer(ITS_BSSAP_SRC, sec,
                                         (void*)&ctxt, sizeof(ctxt));
    if (serial)
    {
        BSSAP_DEBUG(("StartUDTTimer: Started  timer (%d sec): %s\n",
                                       sec, GetTimerString(timer_type)));

        return (serial);
    }

    BSSAP_ERROR(("StartUDTTimer: Fail to start timer : %s\n",
                                     GetTimerString(timer_type)));

    return (ITS_ETIMERSTARTFAIL);
}

/*implementation:internal
*
* PURPOSE:
*       resending block message twice if timeout happens 
* INPUT:
*       call context 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessBlockTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    ITS_USHORT pcm = 0;
    ITS_OCTET  ts = 0;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessBlockTimeout\n"));

    // Shall send BLOCK to BSC 2 times  
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessBlockTimeout: Timeout tries %d\n", ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_21;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_BLOCK, 
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }
      
        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen, 
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        } 
    }
    else
    {
        // Raise alarm OAM 
        BSSAP_ERROR(("ProcessBlockTimeout: Timeout no Block Ack received\n"));

        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);

        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOBLKACK ,
                                                     BSSAP_MSG_BLOCK, pcm, ts);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending release message twice if timeout happens 
* INPUT:
*       call context 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessReleaseTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    BSSAP_Call* call = NULL;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessReleaseTimeout\n"));

    call = BSSAP_CallDB::GetShared().Fetch(ctxt.callrefId);

    // Shall send RELEASE to BSC 2 times  
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessReleaseTimeout: Timeout tries %d\n", ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_308;

        ret = StartTimer(call, ctxt.tries);    
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }
      
        if (call)
        {
            ret = hndl.BSSAP_ProcessAPPdata(call);

            if (ret == ITS_SUCCESS)
            {
                PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_DTAP_SEND);
            }   
        }
    }
    else
    {
        // Raise alarm OAM 
        BSSAP_ERROR(("ProcessReleaseTimeout: Timeout no Release received\n"));

        if (call)
        {
            bssIf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_ENORELEASECMP);
        }
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending unblock message twice if timeout happens 
* INPUT:
*       call context 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessUnBlockTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET ts = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessUnBlockTimeout\n"));

    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessUnBlockTimeout: Timeout tries %d\n",ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_21;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_UNBLOCK,
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }

        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessUnBlockTimeout: Timeout no UnBlk Ack received\n"));
        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);

        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOUNBLKACK,
                                                   BSSAP_MSG_UNBLOCK, pcm, ts);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending Ckt Group block message twice if timeout happens
* INPUT:
*       call context
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  27-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessCktGroupBlkTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET ts = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Timer: ProcessCktGroupBlkTimeout\n"));
                                                                                                                                              
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessCktGroupBlkTimeout: Timeout tries %d\n",
                                     ctxt.tries));
                                                                                                                                              
        ctxt.tries++;
        timer_type = BSSAP_T_22;
                                                                                                                                              
        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, 
                            BSSAP_MSG_CKT_GROUP_BLOCK, ctxt.mapData,
                            ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }
                                                                                                                                              
        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessCktGroupBlkTimeout: Timeout no UnBlk Ack "
                     "received\n"));
        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);
                                                                                                                                              
        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOCKTGRPBLKACK,
                                     BSSAP_MSG_CKT_GROUP_BLOCK, pcm, ts);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending Ckt Group unblock message twice if timeout
* INPUT:
*       call context
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  27-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessCktGroupUnblkTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET ts = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
                                                                                                                                              
    BSSAP_DEBUG(("BSSAP_Timer: ProcessCktGroupUnblkTimeout\n"));
                                                                                                                                              
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessCktGroupUnblkTimeout: Timeout tries %d\n",
                                     ctxt.tries));
                                                                                                                                              
        ctxt.tries++;
        timer_type = BSSAP_T_22;
                                                                                                                                              
        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries,
                            BSSAP_MSG_CKT_GRP_UNBLOCK, ctxt.mapData,
                            ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }
                                                                                                                                              
        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessCktGroupUnblkTimeout: Timeout no UnBlk Ack "
                     "received\n"));
        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);
                                                                                                                                              
        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOCKTGRPUNBLKACK,
                                     BSSAP_MSG_CKT_GRP_UNBLOCK, pcm, ts);
    }
                                                                                                                                              
    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending reset message twice if timeout happens 
* INPUT:
*       call context 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessResetTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessResetTimeout\n"));

    //Guard timer T2 for RESET ACK to BSC
    if (ctxt.timerType == BSSAP_T_2)
    {
         intf.DispatchErrorToApp(BSSAP_MD_TIMEOUT, ctxt.timerType);

         return (ITS_SUCCESS);
    }

    // Shall send REST to MSC operator dependent times
    //By default msg sent once before timer starts. so reduce 1 from tries
    if (ctxt.tries < TIMER_Tries[BSSAP_T_16] - 1)
    {
        BSSAP_WARNING(("ProcessResetTimeout: Timeout tries %d\n",ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_16;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_RESET,
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }

        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessResetTimeout: Timeout no Reset Ack received\n"));

        intf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENORESETACK ,
                                                             BSSAP_MSG_RESET);
        rData.timerId = 0;
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending reset circuit message twice if timeout happens 
* INPUT:
*       call context 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessResetCktTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessResetCktTimeout\n"));

    // Shall send REST Ckt to MSC operator dependent times
    //By default msg sent once before timer starts. so reduce 1 from tries
    if (ctxt.tries < TIMER_Tries[BSSAP_T_12] - 1)
    {
        BSSAP_WARNING(("ProcessResetCktTimeout: Timeout tries %d\n",
                                                               ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_12;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_RESET_CIRCUIT,
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           return (ret);
        }

        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
        } 
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessResetCktTimeout: "
                                "Timeout no Reset Ckt Ack received\n"));

        intf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENORESETCKTACK,
                                                      BSSAP_MSG_RESET_CIRCUIT);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       resending overload message twice if timeout happens 
* INPUT:
*       call context 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer restarted and sent app data successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0750, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::ProcessOverloadTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessOverloadTimeout\n"));

    if (ctxt.timerType == BSSAP_T_5)
    {
       oData.timerId5 = 0;
    }

    if (ctxt.timerType == BSSAP_T_6)
    {
       isFirst = ITS_TRUE;
       oData.timerId6 = 0;
       intf.DispatchErrorToApp(BSSAP_MD_TIMEOUT, ctxt.timerType);
    }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       cancel UDT timer 
* INPUT:
*       timerId 
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       Success, if timer stopped successfully 
*       Error, if problem occurs
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0720, ID :: D0740,
*                        ID :: D0920
*/
ITS_INT
BSSAP_Timer::CancelUDTTimer(ITS_SERIAL timerId)
{
    ITS_INT ret = ITS_SUCCESS;

    BSSAP_DEBUG(("BSSAP_Timer: CancelUDTTimer\n"));
    
    if (timerId)
    {
        ret = TIMERS_CancelTimer(timerId);
        if (ret == ITS_SUCCESS)
        {
            BSSAP_DEBUG(("CancelUDTTimer: Canceled timer : %s\n",
                                                 GetTimerString(timer_type)));
        }
    }

    return (ret);
}

