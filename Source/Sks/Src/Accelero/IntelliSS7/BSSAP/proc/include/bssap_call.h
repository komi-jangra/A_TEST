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
 *  ID: $Id: bssap_call.h,v 1.1.1.1 2007/10/08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: bssap_call.h,v $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:13  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.11  2006/10/07 12:40:43  sjaddu
 * LOG: Added IMSI_Detach procedure.
 * LOG:
 * LOG: Revision 1.1.2.10  2006/09/14 16:01:39  sjaddu
 * LOG: Fix for SLR and DLR values with morethan 3-octets.
 * LOG:
 * LOG: Revision 1.1.2.9  2006/07/14 16:59:39  sjaddu
 * LOG: Connection Id is changed to U INT.
 * LOG:
 * LOG: Revision 1.1.2.8  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.7  2005/10/06 08:27:49  adutta
 * LOG: CIC declaration changes
 * LOG:
 * LOG: Revision 1.1.2.6  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/28 19:05:28  adutta
 * LOG: Handover call type added
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/26 20:20:16  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/26 06:52:42  adutta
 * LOG: Fsm related changes
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:44  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             
#ifndef  _BSSAP_CALL_H_
#define  _BSSAP_CALL_H_

#include <BSSAP++.h>
#include <bssap_common.h>

using namespace std;
using namespace its;


class Fsm;

typedef enum 
{
   MO_CALL = 1,
   MT_CALL,
   LU_CALL,
   HO_CALL,
   IMSI_DETACH
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0170
*/
class BSSAP_Call
{
public:

     BSSAP_Call()
     {
        //handOver = ITS_FALSE;
					handOver = 0;
        channelAlloc = ITS_FALSE;
        msgType = 0;
        bssId = cic = slr = dlr = 0; 
				hafailure = hooldbss = honewbss = dt1horeq = 0 ;
				datalen = 0;
				hofaicause = 0;
        cicst = 0; /* Added by Amaresh 26-08-14 for cicstate handle */ 
        memset(data, 0, BSSAP_DATA_LEN);
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

     ITS_UINT GetAppId()
     { 
         return appId; 
     }

     void SetAppId(ITS_UINT ai)
     { 
         appId = ai;
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
     /* Added by Amaresh for Handover failure flag set as on dated 16-05-08 */
		void SetHandOverFailureCause(ITS_OCTET hfc)
     {
         hofaicause = hfc;
     }

     ITS_OCTET  GetHandOverFailureCause()
     {
         return (hofaicause);
     }

		void SetHandOverFailure(ITS_OCTET hf)
     {
         hafailure = hf;
     }

     ITS_OCTET  GetHandOverFailure()
     {
         return (hafailure);
     }

     ITS_OCTET IsHandOverFailure()
     {
         return (hafailure);
     }
		 void SetHandOverOldBss(ITS_OCTET obss)
     {
         hooldbss = obss;
     }

     ITS_OCTET GetHandOverOldBss()
     {
         return (hooldbss);
     }

     ITS_OCTET IsHandOverOldBss()
     {
         return (hooldbss);
     }
		void SetHandOverNewBss(ITS_OCTET nbss)
     {
         honewbss = nbss;
     }

     ITS_OCTET GetHandOverNewBss()
     {
         return (honewbss);
     }

     ITS_OCTET IsHandOverNewBss()
     {
         return (honewbss);
     }
		void SetHoreqDt1(ITS_OCTET dt1)
     {
         dt1horeq = dt1;
     }

     ITS_OCTET GetHoreqDt1()
     {
         return (dt1horeq);
     }

     ITS_OCTET IsHoreqDt1()
     {
         return (dt1horeq);
     }

		/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */
		ITS_INT GetDatalen()
     {
         return (datalen);
     }
		/* Added by Amaresh for handelling CR message having no user data as on dated 19-06-08 */
	/*Modification Start by Amaresh as on dated 26-08-14 */	
     void SetCicst(ITS_OCTET h)
     {
         cicst = h;
     }

     ITS_OCTET GetCicst()
     {
         return (cicst);
     }
/*Modification Start by Amaresh as on dated 26-08-14 */
/* Added by Amaresh for Handover failure flag set as on dated 16-05-08 */
     void SetHandOver(ITS_OCTET h)
     {
         handOver = h;
     }

     ITS_OCTET GetHandOver()
     {
         return (handOver);
     }

     ITS_OCTET IsHandOver()
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

private:
     ITS_CTXT dlr;
     ITS_CTXT slr;
     ITS_UINT cic;
     ITS_UINT appId;
     ITS_OCTET  bssId;
     ITS_OCTET  msgType;
     ITS_OCTET  callType;
     ITS_SERIAL timerId;
     ITS_INT    datalen;
     ITS_OCTET  data[BSSAP_DATA_LEN];
     ITS_OCTET handOver;
		 /* Added by Amaresh for Handover failure flag set as on dated 16-05-08 */
     ITS_OCTET hafailure;
		 ITS_OCTET hooldbss;
		 ITS_OCTET honewbss;
		 ITS_OCTET dt1horeq; 
		 ITS_OCTET hofaicause; 		
		/* Added by Amaresh for Handover failure flag set as on dated 16-05-08 */
		 ITS_OCTET cicst; /* Added by Amaresh as on dated 26-08-14 cicstate handle */		
     ITS_BOOLEAN channelAlloc;
};

#endif
