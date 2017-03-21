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
 * ID: $Id: bssap_msc-call.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.8  2006/05/05 05:21:56  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.7  2006/04/25 05:33:13  adutta
 * LOG: Changed as par IMR comments
 * LOG:
 * LOG: Revision 1.1.2.6  2005/12/19 05:06:16  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/28 05:23:31  adutta
 * LOG: Flag for TMSI addded
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/18 06:39:52  mkrishna
 * LOG: Changed variable name
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/17 06:14:58  mkrishna
 * LOG: Channel allocation flag added
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:20:21  mkrishna
 * LOG: Set/Get for BSSAP_Message
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             
#ifndef  _BSSAP_CALL_H_
#define  _BSSAP_CALL_H_

#include <BSSAP++.h>
#include <bssap_msc-common.h>

using namespace std;
using namespace its;


class Fsm;

typedef enum 
{
   MO_CALL = 1,
   MT_CALL,
   HO_CALL,
   LU_CALL
}
CALL_TYPE;

/*implementation:internal
*
* PURPOSE:
*       Maintains complete call object information 
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
*                        ID :: D0190, ID :: D0200,
*                        ID :: D0210
*/

class BSSAP_Call
{
public:

     BSSAP_Call()
     {
        handOver = ITS_FALSE;
        channelAlloc = ITS_FALSE;
        tmsiFlag = ITS_FALSE;
        msgType = 0;
        bssId = cic = slr = dlr = currEvent = prevEvent = 0; 
        memset(data, 0, BSSAP_DATA_LEN);
        bssapMsg = NULL;
        appId = 0;
     }

     ITS_CTXT GetSLR() 
     { 
         return slr;
     }

     void SetSLR(ITS_CTXT sl)
     { 
         slr = sl;
     }

     ITS_CTXT GetDLR() 
     { 
         return dlr;
     }

     void SetDLR(ITS_CTXT dl)
     { 
         dlr = dl;
     }

     ITS_CTXT GetAppId()
     { 
         return appId; 
     }

     void SetAppId(ITS_CTXT id)
     { 
         appId = id;
     }

     ITS_OCTET* GetBSSAPData(ITS_INT* l)
     {
          *l = datalen;
          return data; 
     }

     void SetBSSAPData(ITS_OCTET* m, ITS_INT l)
     {
          memcpy(data, m, l);
          datalen = l;
     }

     void SetCurrentEvent(ITS_OCTET evt)
     {
         currEvent = evt;
     }

     ITS_OCTET GetCurrentEvent()
     {
         return currEvent;
     }

     void SetPrevEvent(ITS_OCTET evt)
     {
         prevEvent = evt;
     }
     ITS_OCTET GetPrevEvent()
     {
         return prevEvent;
     }

     void SetMssgType(ITS_OCTET m)
     { 
         msgType = m;
     }

     ITS_OCTET GetMssgType()
     {
         return msgType;
     }
    
     void SetCallType(ITS_OCTET type) 
     {
         callType = type;
     } 

     ITS_OCTET GetCallType()
     {
         return  callType;
     }

     void SetTimerId(ITS_SERIAL serial)
     {
         timerId = serial;
     }

     ITS_SERIAL  GetTimerId()
     {
         return timerId;
     }

     void SetHandOver(ITS_BOOLEAN h)
     {
         handOver = h;
     }

     ITS_BOOLEAN GetHandOver()
     {
         return (handOver);
     }

     void SetChannelAlloc(ITS_BOOLEAN ca)
     {
         channelAlloc = ca;
     }

     ITS_BOOLEAN GetChannelAlloc()
     {
         return (channelAlloc);
     }
   
     void SetTmsiReallocCmd(ITS_BOOLEAN trc)
     {
         tmsiFlag = trc;
     }
                                                                                                                                              
     ITS_BOOLEAN GetTmsiReallocCmd()
     {
         return (tmsiFlag);
     }

     ITS_BOOLEAN IsHandOver()
     {
         return (handOver);
     }

     void SetBssId(ITS_OCTET id)
     {
         bssId = id;
     }

     ITS_OCTET GetBssId()
     {
         return (bssId);
     }

     void SetCIC(ITS_UINT key)
     {
         cic = key;
     }

     ITS_UINT GetCIC()
     {
         return (cic);
     }

     void SetTimerName(ITS_OCTET name)
     {
         timerName = name;
     }
                                                                                                                                              
     ITS_OCTET GetTimerName()
     {
         return timerName;
     }

     void SetBSSAPdata(BSSAP_Message* mMssg)
     {
         bssapMsg = mMssg;
     }
                                                                                                                                              
     BSSAP_Message* GetBSSAPdata()
     {
         return (bssapMsg);
     }

private:
     ITS_CTXT    dlr;
     ITS_CTXT    slr;
     ITS_UINT    cic;
     ITS_CTXT    appId;
     ITS_OCTET   bssId;
     ITS_OCTET   currEvent;
     ITS_OCTET   prevEvent;
     ITS_OCTET   msgType;
     ITS_INT     datalen;
     ITS_OCTET   data[BSSAP_DATA_LEN];
     ITS_OCTET   callType;
     ITS_SERIAL  timerId;
     ITS_BOOLEAN handOver;
     ITS_OCTET   timerName;
     ITS_BOOLEAN channelAlloc;
     ITS_BOOLEAN tmsiFlag;
     BSSAP_Message* bssapMsg; 
};

#endif
