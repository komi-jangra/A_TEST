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
 *  ID: $Id: bssap_timer.h,v 1.5 2008-03-19 03:28:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.4  2008/02/06 22:25:04  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2008/01/18 04:19:58  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/11/08 08:06:45  amaresh.prasad
 * LOG: Updated for Handover
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/20 09:14:34  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/06/25 06:45:28  cvsadmin
 * LOG: Mantis Issue 483  &484  (Retries of  Reset and Reset  Ack )
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.6  2006/09/29 06:10:34  sjaddu
 * LOG: Modified callrefId type from ITS_USHORT to ITS_CTXT.
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.4  2005/09/29 07:45:47  adutta
 * LOG: Error notifications to app.
 * LOG:
 * LOG: Revision 1.1.2.3  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:43:06  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_TIMER_H_
#define  _BSSAP_TIMER_H_


#include <its++.h>
#include <its_timers.h>
#include <bssap_common.h>
#include <bssap_call.h>

using namespace std;
using namespace its;

extern TIMER_Manager    BSSAP_Timers;

#define BSSAP_NUM_TIMERS                          (0x0FU) 
#define BSSMAP_REQ_TRIES                          (0x01U) 

// MAP timers
#define   BSSAP_T_1                               (0x00U) 
#define   BSSAP_T_4                               (0x01U) 
#define   BSSAP_T_7                               (0x02U) 
#define   BSSAP_T_8                               (0x03U) 
#define   BSSAP_T_10                              (0x04U) 
#define   BSSAP_T_11                              (0x05U) 
#define   BSSAP_T_13                              (0x06U) 
#define   BSSAP_T_17                              (0x07U) 
#define   BSSAP_T_18                              (0x08U) 
#define   BSSAP_T_19                              (0x09U) 
#define   BSSAP_T_20                              (0x0AU) 

#define   BSSAP_T1_INFO_STRING                    "T1"
#define   BSSAP_T4_INFO_STRING                    "T4"
#define   BSSAP_T7_INFO_STRING                    "T7"
#define   BSSAP_T8_INFO_STRING                    "T8"
#define   BSSAP_T10_INFO_STRING                   "T10"
#define   BSSAP_T11_INFO_STRING                   "T11"
#define   BSSAP_T13_INFO_STRING                   "T13"
#define   BSSAP_T17_INFO_STRING                   "T17"
#define   BSSAP_T18_INFO_STRING                   "T18"
#define   BSSAP_T19_INFO_STRING                   "T19"
#define   BSSAP_T20_INFO_STRING                   "T20"

/*
typedef struct
{
    ITS_OCTET   destId;
    ITS_OCTET   evtType;
    ITS_OCTET   timerType;
    ITS_CTXT    callrefId;
    ITS_OCTET   tries;
    ITS_OCTET   mapData[BSSAP_DATA_LEN];
    ITS_INT     dataLen;
}
BSSAP_CALL_CTXT;
*/

#define   BSSAP_TIMER_DATA_LEN        0xFFU


typedef struct
{
    ITS_OCTET   destId;
    ITS_OCTET   evtType;
    ITS_OCTET   timerType;
    ITS_CTXT    callrefId;
    ITS_OCTET   tries;
    ITS_OCTET   mapData[BSSAP_TIMER_DATA_LEN];
    ITS_INT     dataLen;
}
BSSAP_CALL_CTXT;




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
*                        ID :: D0740, ID :: D0720
*/
class BSSAP_Timer
{
public:

    BSSAP_Timer(){};

    BSSAP_Timer(ITS_OCTET type)
    {
        timer_type = type;
    }    

    ITS_INT StartTimer(BSSAP_Call* call, ITS_OCTET tries = 0);
    ITS_INT CancelTimer(BSSAP_Call* call);

    ITS_INT StartUDTTimer(ITS_USHORT cic, ITS_OCTET tries, ITS_OCTET msgType, 
                                 ITS_OCTET* buff, ITS_INT len, ITS_OCTET nwId);
    ITS_INT CancelUDTTimer(ITS_SERIAL timerId);
    ITS_INT ProcessTimeout(ITS_Event& event);

    ITS_CHAR* GetTimerString(ITS_OCTET type);

private:
    ITS_INT HandleTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessBlockTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessUnBlockTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessResetTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessResetCktTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessOverloadTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessCktGroupBlkTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessCktGroupUnblkTimeout(BSSAP_CALL_CTXT ctxt); 
/*Added by Amaresh for Timeout Assignment Message */
    ITS_INT ProcessAssignmentRequestTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessHandoverCommandTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessHandoverRequiredTimeout(BSSAP_CALL_CTXT ctxt);
/*Addition completed by Amaresh for Timeout Assignment Message */
private:
   ITS_OCTET timer_type;  

};

#endif

