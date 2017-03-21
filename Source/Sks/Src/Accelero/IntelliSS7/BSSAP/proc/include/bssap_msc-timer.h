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
 * ID: $Id: bssap_msc-timer.h,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/28 05:26:41  adutta
 * LOG: Timer T3250 added
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/17 06:25:40  mkrishna
 * LOG: Auth. Req/Ident. Req. timer implemented
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:27:17  mkrishna
 * LOG: Error procedures for ResetAck/CktGrpBlk/CktGrpUnblk
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_TIMER_H_
#define  _BSSAP_TIMER_H_


#include <its++.h>
#include <its_timers.h>
#include <bssap_msc-common.h>
#include <bssap_msc-call.h>

using namespace std;
using namespace its;

extern TIMER_Manager    BSSAP_Timers;

#define BSSAP_NUM_TIMERS                          (0x1FU) 
#define BSSMAP_REQ_TRIES                          (0x01U) 

// MAP timers
#define   BSSAP_T_301                             (0x00U)
#define   BSSAP_T_303                             (0x01U)
#define   BSSAP_T_306                             (0x02U) 
#define   BSSAP_T_308                             (0x03U) 
#define   BSSAP_T_310                             (0x04U) 
#define   BSSAP_T_313                             (0x05U) 

#define   BSSAP_T301_INFO_STRING                  "T301"
#define   BSSAP_T303_INFO_STRING                  "T303"
#define   BSSAP_T306_INFO_STRING                  "T306"
#define   BSSAP_T308_INFO_STRING                  "T308"
#define   BSSAP_T310_INFO_STRING                  "T310"
#define   BSSAP_T313_INFO_STRING                  "T313"


// DTAP timers
#define   BSSAP_T_2                               (0x06U)
#define   BSSAP_T_5                               (0x07U)
#define   BSSAP_T_6                               (0x08U)
#define   BSSAP_T_12                              (0x09U)
#define   BSSAP_T_16                              (0x0AU)
#define   BSSAP_T_21                              (0x0BU)
#define   BSSAP_T_22                              (0x0CU)
#define   BSSAP_T_3260                            (0x0DU) 
#define   BSSAP_T_3270                            (0x0EU) 
#define   BSSAP_T_3250                            (0x0FU) 

#define   BSSAP_T2_INFO_STRING                    "T2"
#define   BSSAP_T5_INFO_STRING                    "T5"
#define   BSSAP_T6_INFO_STRING                    "T6"
#define   BSSAP_T12_INFO_STRING                   "T12"
#define   BSSAP_T16_INFO_STRING                   "T16"
#define   BSSAP_T21_INFO_STRING                   "T21"
#define   BSSAP_T22_INFO_STRING                   "T22"
#define   BSSAP_T3260_INFO_STRING                 "T3260"
#define   BSSAP_T3270_INFO_STRING                 "T3270"
#define   BSSAP_T3250_INFO_STRING                 "T3250"


typedef struct
{
    ITS_OCTET   destId;
    ITS_OCTET   evtType;
    ITS_OCTET   timerType;
    ITS_USHORT  callrefId;
    ITS_OCTET   tries;
    ITS_OCTET   mapData[BSSAP_DATA_LEN];
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0740, ID :: D0720,
*                        ID :: D0710
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
    ITS_INT ProcessReleaseTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessCktGroupBlkTimeout(BSSAP_CALL_CTXT ctxt);
    ITS_INT ProcessCktGroupUnblkTimeout(BSSAP_CALL_CTXT ctxt);

private:
   ITS_OCTET timer_type;  

};

#endif
