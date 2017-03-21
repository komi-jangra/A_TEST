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
 *  ID: $Id: bssap_timer.cpp,v 1.8 2008/04/08 10:17:08 bsccs2 Exp $
 *
 * LOG: $Log: bssap_timer.cpp,v $
 * LOG: Revision 1.8  2008/04/08 10:17:08  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.7  2008/03/25 09:12:27  amaresh.prasad
 * LOG: Bug fixing of 2481 & Alarm handelling
 * LOG:
 * LOG: Revision 1.6  2008/03/19 03:29:11  bsccs2
 * LOG: BSSMAP_REQ_TRIES value changed to 1 from 2.
 * LOG:
 * LOG: Revision 1.5  2008/02/01 04:29:00  amaresh.prasad
 * LOG: Updated for Alarm,Timer retry
 * LOG:
 * LOG: Revision 1.3  2007/11/08 08:06:02  amaresh.prasad
 * LOG: Updated for Handover
 * LOG:
 * LOG: Revision 1.2  2007/10/30 06:39:02  amaresh.prasad
 * LOG: Updated for T10 timeout
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:15  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/20 09:13:59  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.4  2007/08/01 11:38:48  amaresh.prasad
 * LOG: No change
 * LOG:
 * LOG: Revision 1.3  2007/08/01 11:37:06  amaresh.prasad
 * LOG: Updated for sms data len
 * LOG:
 * LOG: Revision 1.2  2007/06/25 06:44:08  cvsadmin
 * LOG: Modified  for   Retry  count  bugid  483 &484
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:33:41  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.8  2005/12/05 09:22:06  mkrishna
 * LOG: Added pegs implementation
 * LOG:
 * LOG: Revision 1.1.2.7  2005/11/24 04:43:41  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.6  2005/09/29 07:40:08  adutta
 * LOG: Sending notification to app.
 * LOG:
 * LOG: Revision 1.1.2.5  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/20 18:18:26  adutta
 * LOG: Trace enhancements
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/17 05:31:40  adutta
 * LOG: Traces added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/

#include <bssap.h>
#include <bssap_timer.h>
#include <bssap_call.h>
#include <bssap_calldb.h>
#include <bssap_cicdb.h>
#include <bssap_interface.h>
#include <bssap_sccphandler.h>
#include <bssap_pegs.h>
#include <bssap_error.h>
#include <bssap-alarm.h>
#include <bssap_cfgdb.h>

#ifndef NO_REDUNDACY
#define TIMERS_StartTimer TIMERS_StartSharedTimer
#endif

#define BSSMAP_REQ_TRIES  1
extern ResetData sData; 
extern ResetData rData; 
extern ITS_OCTET TIMER_Tries[];
extern OverloadData oData;
extern ITS_BOOLEAN isFirst;
extern ITS_OCTET arr_status[40]; 
extern ITS_OCTET Unbarr_status[40];
extern ITS_OCTET CGBFlagStatus; 
extern ITS_OCTET arr_status_flag;
extern ITS_OCTET CGUFlagStatus; 
extern ITS_OCTET Unbarr_status_flag;
extern ITS_OCTET app_cgb_flag; 
extern ITS_OCTET app_cgu_flag; 
//extern ITS_OCTET app_blo_flag;  
//extern ITS_OCTET app_ubl_flag; 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720
*/
ITS_CHAR*
BSSAP_Timer::GetTimerString(ITS_OCTET type)
{
    ITS_CHAR* name;

    switch(type)
    {
        case BSSAP_T_1:
            name = "BSSAP_T_1";
        break;
        case BSSAP_T_4:
            name = "BSSAP_T_4";
        break;
        case BSSAP_T_7:
            name = "BSSAP_T_7";
        break;
        case BSSAP_T_8:
            name = "BSSAP_T_8";
        break;
        case BSSAP_T_10:
            name = "BSSAP_T_10";
        break;
        case BSSAP_T_11:
            name = "BSSAP_T_11";
        break;
        case BSSAP_T_13:
            name = "BSSAP_T_13";
        break;
        case BSSAP_T_17:
            name = "BSSAP_T_17";
        break;
        case BSSAP_T_18:
            name = "BSSAP_T_18";
        break;
        case BSSAP_T_19:
            name = "BSSAP_T_19";
        break;
        case BSSAP_T_20:
            name = "BSSAP_T_20";
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
*       call object, tries
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0730, ID :: D0740,
*                        ID :: D0760, ID :: D1060,
*                        ID :: D0750
* Amaresh Prasad 29-04-08 VNL-BSC-BSSAP-CS2 resolve timer retry
*/
ITS_INT
BSSAP_Timer::StartTimer(BSSAP_Call* call, ITS_OCTET tries)
{

    ITS_SERIAL serial = 0;
    BSSAP_CALL_CTXT ctxt;

    memset(&ctxt, 0, sizeof(BSSAP_CALL_CTXT));
    ctxt.timerType = timer_type;
    /*ctxt.tries = 0; *//* Commented by Amaresh as on dated 29-04-08  */
		ctxt.tries = tries; //29-04-08 by Amaresh
    if (call)
    {
        ctxt.evtType = call->GetMssgType();
        ctxt.callrefId = call->GetSLR();
        BSSAP_DEBUG(("BSSAP_Timer: StartTimer\n"));
        ITS_INT sec = TIMERS_GetTimerValue(&BSSAP_Timers, timer_type);
//      serial = TIMERS_StartSharedTimer(ITS_BSSAP_SRC, sec,(void*)&ctxt, sizeof(ctxt));    
        serial = TIMERS_StartTimer(ITS_BSSAP_SRC, sec,(void*)&ctxt, sizeof(ctxt));
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
*       call object
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0730, ID :: D0740,
*                        ID :: D0770, ID :: D1060,
*                        ID :: D0750
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0780, ID :: D1060
*
* Amaresh Prasad 25-01-08 VNL-BSC-BSSAP-CS2 Added Assignment,Handover Timeout
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
    /* Added by Amaresh for Timeout T10 of Assignment Request message  */
    else if (ctxt.evtType == BSSAP_MSG_ASSIGN_REQUEST)
    {
        ProcessAssignmentRequestTimeout(ctxt);
    }
     else if (ctxt.evtType == BSSAP_MSG_HANDOVER_COMMAND)
    {
        ProcessHandoverCommandTimeout(ctxt);
    }
    else if (ctxt.evtType == BSSAP_MSG_HANDOVER_REQUIRED)
    {
        ProcessHandoverRequiredTimeout(ctxt);
    }

    /* Addition completed  by Amaresh for Timeout T10 of Assignment Request message  */
    else
    {
        call = BSSAP_CallDB::GetShared().Fetch(ctxt.callrefId);

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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0730, ID :: D0740,
*                        ID :: D0780, ID :: D1060
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0740, ID :: D0750,
*                        ID :: D1060
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
    BSSAP_DEBUG(("BSSAP_Timer: CTXT  size  of\n %d", sizeof(ctxt)));
    serial = TIMERS_StartTimer(ITS_BSSAP_SRC, sec,
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessBlockTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    ITS_USHORT pcm = 0;
    ITS_OCTET  ts = 0;
    BSSAP_CicDB cicdb;//25-01-08 by Amaresh
    CICData* crec = NULL; //25-01-08 by Amaresh
    ITS_OCTET cicbuf[2]; //25-01-08 by Amaresh
    ITS_UINT key = 0;//Amaresh 25-01-08
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    ITS_UINT CIC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */	
    /* Added by Amaresh for timeout 2time implementation 25-01-08*/
                                                              
    cicbuf[0] = ctxt.callrefId & 0x000000FF;
    cicbuf[1] = (ctxt.callrefId & 0x0000FF00) >> 8;
    pcm = ((cicbuf[1] << 3) |                            \
     (cicbuf[0] & 0xe0) >> 5);
    ts = (cicbuf[0] & 0x1f);

#if defined(CCITT)
    BSSAP_DEBUG(("ProcessBlockTimeout: pcm %d ts %d\n", pcm ,ts));
#else
    BSSAP_DEBUG(("ProcessBlockTimeout: cic %d \n", ctxt.callrefId));
#endif
    key = (ctxt.destId << 16) | ((pcm << 5) | (0x1FU & ts)); 
    crec = cicdb.FetchCICRecord(key,BSSAP_MSG_BLOCK,ctxt.destId); //25-01-08 by Amaresh	
    if(crec == NULL)
    {
      return (ret);
    }
    /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    BSSAP_DEBUG(("BSSAP_Timer: ProcessBlockTimeout\n"));
    // Shall send BLOCK to MSC 2 times  
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessBlockTimeout: Timeout tries %d\n", ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_1;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_BLOCK, 
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);

   	if (ret == ITS_ETIMERSTARTFAIL)
        {
           ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
           return (ret);
        }
    /* Added by Amaresh for timeout 2time 25-01-08 */      
	  if (crec)
	     {
        	 crec->timerId = ret;
           crec->timerType = BSSAP_T_1;
           ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
	     }
     /* Added by Amaresh for timeout 2time 25-01-08 */

        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen, 
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
          //  PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
              BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
        }
    }
    else
    {
        // Raise alarm OAM 
        BSSAP_ERROR(("ProcessBlockTimeout: Timeout no Block Ack received\n"));

        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);
       /* Added by Amaresh for Alarm 21-07-08 */
        cfgdata = db.FetchRPCEntry(ctxt.destId);
        if (cfgdata)
        {
          DPC = cfgdata->rpc;
          CIC =  pcm << 5|(0x1FU & ts);;
        }
        /* Added by Amaresh for Alarm 21-07-08 */

	if(crec->app_blo_flag == 1)/* 24-03-08 Added by Amaresh for Bug id 2481 */
	{
		crec->app_blo_flag = 0; //24-01-08
		BSSAP_Alarm_CCITT(5101,__FILE__,__LINE__,"dpc %d,cic %d",DPC,CIC);
		bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOBLKACK ,BSSAP_MSG_BLOCK, pcm, ts);
	}
 if(crec)
	{
	    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_BLOCK);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessUnBlockTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET ts = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    BSSAP_CicDB cicdb;//25-01-08 by Amaresh
    CICData* crec = NULL; //25-01-08 by Amaresh
    ITS_OCTET cicbuf[2]; //25-01-08 by Amaresh
    ITS_UINT key = 0;//Amaresh 25-01-08
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    ITS_UINT CIC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */

    /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    cicbuf[0] = ctxt.callrefId & 0x000000FF;
    cicbuf[1] = (ctxt.callrefId & 0x0000FF00) >> 8;
    pcm = ((cicbuf[1] << 3) |                            \
    (cicbuf[0] & 0xe0) >> 5);
    ts = (cicbuf[0] & 0x1f);

    BSSAP_DEBUG(("ProcessUnBlockTimeout: pcm %d ts %d\n", pcm ,ts));
    key = (ctxt.destId << 16) | ((pcm << 5) | (0x1FU & ts));
    crec = cicdb.FetchCICRecord(key,BSSAP_MSG_UNBLOCK,ctxt.destId); //25-01-08 by Amaresh
    if(crec == NULL)
    {
      return (ret);
    }
    /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessUnBlockTimeout: Timeout tries %d\n",ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_1;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_UNBLOCK,
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
           return (ret);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */
        if (crec)
        {
            crec->timerId = ret;
            crec->timerType = BSSAP_T_1;
            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */

        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
           // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
              BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessUnBlockTimeout: Timeout no UnBlk Ack received\n"));
        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);
        /* Added by Amaresh for Alarm 21-07-08 */
        cfgdata = db.FetchRPCEntry(ctxt.destId);
        if (cfgdata)
        {
            DPC = cfgdata->rpc;
            CIC =  pcm << 5|(0x1FU & ts);
        }
        /* Added by Amaresh for Alarm 21-07-08 */

				if(crec->app_ubl_flag == 1) /* 24-03-08 Added by Amaresh for Bug id 2481 */
						{
						  crec->app_ubl_flag = 0;//24-01-08
					   	BSSAP_Alarm_CCITT(5102,__FILE__,__LINE__,"dpc %d,cic %d",DPC,CIC);
		          bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOUNBLKACK,
                                                   BSSAP_MSG_UNBLOCK, pcm, ts);
						}
           if(crec)
	          {
	            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_UNBLOCK);
	          }
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessCktGroupBlkTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET ts = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    BSSAP_CicDB cicdb;//25-01-08 by Amaresh
    CICData* crec = NULL; //25-01-08 by Amaresh
    ITS_OCTET cicbuf[2]; //25-01-08 by Amaresh
    ITS_UINT key = 0;//Amaresh 25-01-08
    /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    cicbuf[0] = ctxt.callrefId & 0x000000FF;
    cicbuf[1] = (ctxt.callrefId & 0x0000FF00) >> 8;
    pcm = ((cicbuf[1] << 3) |                            \
     (cicbuf[0] & 0xe0) >> 5);
    ts = (cicbuf[0] & 0x1f);
#if defined(CCITT)
    BSSAP_DEBUG(("ProcessBlockTimeout: pcm %d ts %d\n", pcm ,ts));
#else
    BSSAP_DEBUG(("ProcessBlockTimeout: cic %d \n", ctxt.callrefId));
#endif
    key = (ctxt.destId << 16) | ((pcm << 5) | (0x1FU & ts));
    crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GROUP_BLOCK,ctxt.destId); //25-01-08 by Amaresh
   /* Added by Amaresh for timeout 2time implementation 25-01-08*/
                                                                                                  
    BSSAP_DEBUG(("BSSAP_Timer: ProcessCktGroupBlkTimeout\n"));
                                                                                                         
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessCktGroupBlkTimeout: Timeout tries %d\n",
                                     ctxt.tries));
                                                                                                                                              
        ctxt.tries++;
        timer_type = BSSAP_T_20;
                                                                                                                                              
        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries,
                            BSSAP_MSG_CKT_GROUP_BLOCK, ctxt.mapData,
                            ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
           return (ret);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */
        if (crec)
        {
             crec->timerId = ret;
             crec->timerType = BSSAP_T_20;
             ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
        }
       /* Added by Amaresh for timeout 2time 25-01-08 */
                                                                                                        
        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
           // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
              BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessCktGroupBlkTimeout: Timeout no Blk Ack "
                     "received\n"));
        /*				BSSAP_Alarm_CCITT(5101,__FILE__,__LINE__,NULL,NULL); */
        pcm = (ctxt.callrefId >> 5);
        ts  = (ctxt.callrefId & 0x1F);
				bzero(arr_status,40); //14-01-08 set array status of block to zero
				CGBFlagStatus = 0; //15-01-08
        arr_status_flag = 0; //15-01-08
				app_cgb_flag = 0; //24-01-08                                                                                                                      
        bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOCKTGRPBLKACK,
                                     BSSAP_MSG_CKT_GROUP_BLOCK, pcm, ts);
        if(crec)
	{
	    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GROUP_BLOCK);
	}
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessCktGroupUnblkTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    ITS_USHORT pcm = 0;
    ITS_OCTET ts = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface bssIf;
    BSSAP_CicDB cicdb;//25-01-08 by Amaresh
    CICData* crec = NULL; //25-01-08 by Amaresh
    ITS_OCTET cicbuf[2]; //25-01-08 by Amaresh
    ITS_UINT key = 0;//Amaresh 25-01-08
   /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    cicbuf[0] = ctxt.callrefId & 0x000000FF;
    cicbuf[1] = (ctxt.callrefId & 0x0000FF00) >> 8;
    pcm = ((cicbuf[1] << 3) |                            \
     (cicbuf[0] & 0xe0) >> 5);
    ts = (cicbuf[0] & 0x1f);
#if defined(CCITT)
    BSSAP_DEBUG(("ProcessBlockTimeout: pcm %d ts %d\n", pcm ,ts));
#else
    BSSAP_DEBUG(("ProcessBlockTimeout: cic %d \n", ctxt.callrefId));
#endif
    key = (ctxt.destId << 16) | ((pcm << 5) | (0x1FU & ts));
    crec = cicdb.FetchCICRecord(key,BSSAP_MSG_CKT_GRP_UNBLOCK,ctxt.destId); //25-01-08 by Amaresh
   /* Added by Amaresh for timeout 2time implementation 25-01-08*/
                                                                                                                                          
    BSSAP_DEBUG(("BSSAP_Timer: ProcessCktGroupUnblkTimeout\n"));
                                                                                                                                              
    if (ctxt.tries < BSSMAP_REQ_TRIES)
    {
        BSSAP_WARNING(("ProcessCktGroupUnblkTimeout: Timeout tries %d\n",
                                     ctxt.tries));
                                                                                                                                              
        ctxt.tries++;
        timer_type = BSSAP_T_20;
                                                                                                                                              
        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries,
                            BSSAP_MSG_CKT_GRP_UNBLOCK, ctxt.mapData,
                            ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
           return (ret);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */
        if (crec)
        {
            crec->timerId = ret;
            crec->timerType = BSSAP_T_20;
            ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */
                                                                                                                                              
        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
           // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
              BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
        }
    }
    else
    {
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessCktGroupUnblkTimeout: Timeout no UnBlk Ack "
                     "received\n"));
/*			BSSAP_Alarm_CCITT(5102,__FILE__,__LINE__,NULL,NULL);*/
      pcm = (ctxt.callrefId >> 5);
      ts  = (ctxt.callrefId & 0x1F);
			bzero(Unbarr_status,40); //14-01-08 set array status of block to zero
      CGUFlagStatus = 0; //15-01-08
      Unbarr_status_flag = 0; //15-01-08
			app_cgu_flag = 0; //24-01-08                                                                                                                               
      bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOCKTGRPUNBLKACK,
                                     BSSAP_MSG_CKT_GRP_UNBLOCK, pcm, ts);
        if(crec)
	{
	    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_CKT_GRP_UNBLOCK);
        }
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessResetTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    /* Added by Amaresh for Alarm 21-07-08 */
    
    
    BSSAP_DEBUG(("BSSAP_Timer: ProcessResetTimeout\n"));

    //Guard timer T13 for RESET ACK to MSC
    if (ctxt.timerType == BSSAP_T_13)
    {
         intf.DispatchErrorToApp(BSSAP_MD_TIMEOUT, ctxt.timerType);

         return (ITS_SUCCESS);
    }

    // Shall send REST to MSC "n" times
	  /*fix the Bug 483 by Amaresh */
 	  /*  if (ctxt.tries < TIMER_Tries[BSSAP_T_4] - 1)*/

     /*	if (ctxt.tries < TIMER_Tries[BSSAP_T_4]) After runtime configuration then this line on till it is hardcoded */ 
	
	 if (ctxt.tries < BSSMAP_REQ_TRIES)
	 {
		 BSSAP_WARNING(("ProcessResetTimeout: Timeout tries %d\n",ctxt.tries));

		 ctxt.tries++;
		 timer_type = BSSAP_T_4;
		 /* Added by Amaresh for timeout 2time 30-01-08 */
		 rData.timerId = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_RESET,
				 ctxt.mapData, ctxt.dataLen, ctxt.destId);
		 if (rData.timerId == ITS_ETIMERSTARTFAIL)
		 {
			 return (!ITS_SUCCESS);
		 }
		 /* Added by Amaresh for timeout 2time 30-01-08 */
		 ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
				 ctxt.destId);
		 if (ret == ITS_SUCCESS)
		 {
			 // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
			 BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
		 }
	 }
    else
    {
     /* Added by Amaresh for Alarm 21-07-08 */
     cfgdata = db.FetchRPCEntry(ctxt.destId);
     if (cfgdata)
      {
         DPC = cfgdata->rpc;
      }
       /* Added by Amaresh for Alarm 21-07-08 */
        rData.timerId = 0;
        // Raise alarm OAM
        BSSAP_ERROR(("ProcessResetTimeout: Timeout no Reset Ack received\n"));
				BSSAP_Alarm_CCITT(5103,__FILE__,__LINE__,"dpc %d",DPC);
		    intf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENORESETACK ,
                                                             BSSAP_MSG_RESET);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessResetCktTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;
    ITS_USHORT pcm = 0;//25-01-08 by Amaresh
    ITS_OCTET ts = 0;//25-01-08 by Amaresh
    BSSAP_CicDB cicdb;//25-01-08 by Amaresh
    CICData* crec = NULL; //25-01-08 by Amaresh
    ITS_OCTET cicbuf[2]; //25-01-08 by Amaresh
    ITS_UINT key = 0;//Amaresh 25-01-08
    /* Added by Amaresh for Alarm 21-07-08 */
    BSSAP_CfgDB db;
    CFGData* cfgdata = NULL;
    ITS_UINT DPC = 0;
    ITS_UINT CIC = 0;
   /* Added by Amaresh for Alarm 21-07-08 */
   /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    cicbuf[0] = ctxt.callrefId & 0x000000FF;
    cicbuf[1] = (ctxt.callrefId & 0x0000FF00) >> 8;
    pcm = ((cicbuf[1] << 3) |                            \
     (cicbuf[0] & 0xe0) >> 5);
    ts = (cicbuf[0] & 0x1f);
#if defined(CCITT)
    BSSAP_DEBUG(("ProcessResetCktTimeout: pcm %d ts %d\n", pcm ,ts));
#else
    BSSAP_DEBUG(("ProcessBlockTimeout: cic %d \n", ctxt.callrefId));
#endif
    key = (ctxt.destId << 16) | ((pcm << 5) | (0x1FU & ts));
    crec = cicdb.FetchCICRecord(key,BSSAP_MSG_RESET_CIRCUIT,ctxt.destId); //25-01-08 by Amaresh
    /* Added by Amaresh for timeout 2time implementation 25-01-08*/

    // Shall send REST Ckt to MSC "n" times
	  /*fix the Bug 484 by Amaresh */
	  /*  if (ctxt.tries < TIMER_Tries[BSSAP_T_19] - 1) */
    /*	if (ctxt.tries < TIMER_Tries[BSSAP_T_19]) After runtime configuration then this line on till it is hardcoded */
   	if (ctxt.tries < BSSMAP_REQ_TRIES)
	   {
        BSSAP_WARNING(("ProcessResetCktTimeout: Timeout tries %d\n",
                                                               ctxt.tries));

        ctxt.tries++;
        timer_type = BSSAP_T_19;

        ret = StartUDTTimer(ctxt.callrefId, ctxt.tries, BSSAP_MSG_RESET_CIRCUIT,
                               ctxt.mapData, ctxt.dataLen, ctxt.destId);
        if (ret == ITS_ETIMERSTARTFAIL)
        {
           ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT);
           return (ret);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */
        if (crec)
        {
           crec->timerId = ret;
           crec->timerType = BSSAP_T_19;
           ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT);
        }
        /* Added by Amaresh for timeout 2time 25-01-08 */

        ret =  hndl.BSSAP_ProcessAPPdata(ctxt.mapData, ctxt.dataLen,
                                            ctxt.destId);

        if (ret == ITS_SUCCESS)
        {
           // PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
              BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
        }
    }
    else
    {
     /* Added by Amaresh for Alarm 21-07-08 */
     cfgdata = db.FetchRPCEntry(ctxt.destId);
     if (cfgdata)
      {
        DPC = cfgdata->rpc;
        CIC =  pcm << 5|(0x1FU & ts);;
      }
      /* Added by Amaresh for Alarm 21-07-08 */

        // Raise alarm OAM
        BSSAP_ERROR(("ProcessResetCktTimeout: "
                               "Timeout no Reset Ckt Ack received\n"));
				BSSAP_Alarm_CCITT(5104,__FILE__,__LINE__,"dpc %d,cic %d",DPC,CIC);
        intf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENORESETCKTACK,
                                                      BSSAP_MSG_RESET_CIRCUIT);
        if(crec)
	{
	    ret = cicdb.ModifyCICRecord(key, crec,BSSAP_MSG_RESET_CIRCUIT);
        }
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0720, ID :: D0780,
*                        ID :: D1060
*/
ITS_INT
BSSAP_Timer::ProcessOverloadTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;

    BSSAP_DEBUG(("BSSAP_Timer: ProcessOverloadTimeout\n"));

    if (ctxt.timerType == BSSAP_T_17)
    {
       oData.timerId17 = 0;
    }

    if (ctxt.timerType == BSSAP_T_18)
    {
       isFirst = ITS_TRUE;
       oData.timerId18 = 0;
       intf.DispatchErrorToApp(BSSAP_MD_TIMEOUT, ctxt.timerType);
    }

    return (ret);
}
/*implementation:internal
*
* PURPOSE:
*       Sending Assignment Failure message towards MSC if Timeout happens
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
 HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  06-08-2007   BSSAP-CS2
*                                      
*/

ITS_INT
BSSAP_Timer::ProcessAssignmentRequestTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;
    ITS_OCTET cause;
    BSSAP_Call* call = NULL;
    BSSAP_Error err;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;


   		BSSAP_DEBUG(("BSSAP_Timer: ProcessBSSAP ASSIGNMENT REQUEST Timeout\n"));
			cause = C_RADIO_INTERFACE_MSG_FAIL;
			call = BSSAP_CallDB::GetShared().Fetch(ctxt.callrefId);
			if(call) /* Added by Amaresh for Bug fix 1627 */
        {
			   	 BSSAP_DEBUG(("BSSAP_Timer: ProcessBSSAP ASSIGNMENT REQUEST Timeout presence of Call\n"));
			     cic = call->GetCIC();
      	   if (cic)
  		      {
                crec = cicdb.FetchCICRecord(cic,BSSAP_MSG_ASSIGN_REQUEST,call->GetBssId());
                if (crec)
                {
                    crec->callState = CALL_ST_IDLE;
                    ret = cicdb.ModifyCICRecord(cic, crec,BSSAP_MSG_ASSIGN_REQUEST);
                }
            }
           else
           {
               BSSAP_ERROR(("AssignmentFail for TimeOut : No cic found\n"));
               return (!ITS_SUCCESS);
           }
           BSSAP_DEBUG(("Send Assignment fail by BSSAP stack for T10 Timeout\n")); 
           err.SendAssignmentFail(call, cause,0);
           BSSAP_ERROR(("Send ProcessAssignmentRequestTimeout to BSC-APP:cref[%04x] CIC[%04x] \n",ctxt.callrefId,cic));
           /* Added by Amaresh for dispatch error to APP as on dated 25-10-07 */
           pcm = (ctxt.callrefId >> 5);
           ts  = (ctxt.callrefId & 0x1F);

     //      intf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,BSSAP_MSG_ASSIGN_REQUEST, pcm, ts);          
               intf.DispatchErrorToApp(call, BSSAP_MD_PROTOCOL,BSSAP_EASSREQFAIL);

        /* Addition completed  by Amaresh for dispatch error to APP as on dated 25-10-07 */ 		
       }
      else  /* Added by Amaresh for Bug fix 1627 */
       {
          BSSAP_DEBUG(("BSSAP_Timer: ProcessBSSAP ASSIGNMENT REQUEST Timeout Absence of Call\n"));
       }

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Sending Handover Required Timeout Indication message towards BSC-APP if Timeout happens
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
 HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  06-08-2007   BSSAP-CS2
*
*/

ITS_INT
BSSAP_Timer::ProcessHandoverRequiredTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;
    ITS_OCTET cause;
    BSSAP_Call* call = NULL;
    BSSAP_Error err;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    ITS_USHORT pcm = 0;
    ITS_UINT key = 0;
    ITS_OCTET  ts = 0;

		/* Added by Amaresh for Bug fix 1627 as on dated 29-04-08*/
		call = BSSAP_CallDB::GetShared().Fetch(ctxt.callrefId);
		if(call) /* Added by Amaresh for Bug fix 1627 as on dated 29-04-08*/
      {
         if (ctxt.tries < BSSMAP_REQ_TRIES)
           {
                 BSSAP_WARNING(("ProcessHandoverRequiredTimeout: Timeout tries %d\n", ctxt.tries));

                 ctxt.tries++;
                 BSSAP_Timer t(BSSAP_T_7);
                 ret = t.StartTimer(call,ctxt.tries);
                 ret = hndl.BSSAP_ProcessAPPdata(call);
                 if (ret == ITS_SUCCESS)
                  {
                          BSSAP_CallDB::GetShared().Add(call);
              //            PEG_IncrPeg(BSSAP_Pegs, PEG_BSSAP_MAP_SEND);
              BSSAPPEG_IncrPeg(PEG_BSSAP_MAP_SEND,ctxt.destId);
                  }
           }
          /* Addition completed by Amaresh for Bug fix 1627 as on dated 29-04-08*/
         else 
           {

               #if 0
               BSSAP_DEBUG(("Send Handover Required Timeout by BSSAP stack for T7 \n"));
               err.SendAssignmentFail(call, cause);
               #endif
               BSSAP_ERROR(("Send ProcessHandoverRequiredTimeout to BSC-APP on expiry of T7: \n"));
               /* Added by Amaresh for dispatch error to APP as on dated 25-10-07 */
               pcm = (ctxt.callrefId >> 5);
               ts  = (ctxt.callrefId & 0x1F);

               intf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_ENOHANDOVERCMD,
                                                      BSSAP_MSG_HANDOVER_REQUIRED, pcm, ts);

               /* Addition completed  by Amaresh for dispatch error to APP as on dated 25-10-07 */
               return (ret);
			    }
	     }
}
/*implementation:internal
*
* PURPOSE:
*       Sending HandoverCommand Timeout message towards MSC if Timeout happens
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
 HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Amaresh Prasad  08-08-2007   BSSAP-CS2
*
*/

ITS_INT
BSSAP_Timer::ProcessHandoverCommandTimeout(BSSAP_CALL_CTXT ctxt)
{
    ITS_INT ret = 0;
    BSSAP_SCCPHandler hndl;
    BSSAP_Interface intf;
    ITS_OCTET cause;
    BSSAP_Call* call = NULL;
    BSSAP_Error err;
    ITS_UINT cic = 0;
    BSSAP_CicDB cicdb;
    CICData* crec;
    BSSAP_DEBUG(("BSSAP_Timer: ProcessBSSAP HANDOVER COMMAND Timeout\n"));

        cause = C_RADIO_INTERFACE_MSG_FAIL;
        call = BSSAP_CallDB::GetShared().Fetch(ctxt.callrefId);
			  BSSAP_DEBUG(("Send Clear Request  by BSSAP stack to MSC  for T8 Timeout\n"));
			  err.SendClearRequest(call, cause);
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0740, ID :: D0750,
*                        ID :: D1060
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

