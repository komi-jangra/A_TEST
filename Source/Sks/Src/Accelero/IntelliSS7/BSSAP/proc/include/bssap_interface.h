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
 *  ID: $Id: bssap_interface.h,v 1.5 2008/04/29 04:32:54 bsccs2 Exp $
 *
 * LOG: $Log: bssap_interface.h,v $
 * LOG: Revision 1.5  2008/04/29 04:32:54  bsccs2
 * LOG: Fix for Mantis 2811
 * LOG:
 * LOG: Revision 1.4  2008/02/07 10:18:29  amaresh.prasad
 * LOG: Updated for APPId table
 * LOG:
 * LOG: Revision 1.3  2008/02/01 02:42:00  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/10/30 06:43:58  amaresh.prasad
 * LOG: Updated for PC & SSN
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:13  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/20 09:14:33  amaresh.prasad
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/08/06 06:30:01  amaresh.prasad
 * LOG:  Updated for CS2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.10  2006/07/14 16:59:39  sjaddu
 * LOG: Connection Id is changed to U INT.
 * LOG:
 * LOG: Revision 1.1.2.9  2005/12/13 09:39:44  mkrishna
 * LOG: Added one argument constructor, BSSAPData changed to protected
 * LOG:
 * LOG: Revision 1.1.2.8  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.7  2005/09/29 07:44:32  adutta
 * LOG: Error data structure changes
 * LOG:
 * LOG: Revision 1.1.2.6  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/28 04:15:13  adutta
 * LOG: Data structure changes for DTAP
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/26 06:55:09  adutta
 * LOG: Introducing function to send udt to app
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 20:09:28  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:44  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_IFACE_H_
#define  _BSSAP_IFACE_H_

#include <bssap_common.h>
#include <bssap_call.h>
#include <BSSAP++.h>

typedef struct
{
    ITS_OCTET  error_code;
    ITS_USHORT pcm;
    ITS_OCTET  ts;
/* Added by Amaresh */
    ITS_OCTET ssn;
    ITS_UINT pc;
/* Addition completed  by Amaresh */
	
}
ERROR_DATA;
  
typedef struct
{
    ITS_OCTET  mapMsg[BSSAP_DATA_LEN];
    ITS_USHORT len;
}
MAP_DATA;

typedef struct
{
    ITS_OCTET  dtapMsg[BSSAP_DATA_LEN];
    ITS_USHORT len;
}
DTAP_DATA;

typedef struct
{
    ITS_CTXT   callrefId;
    ITS_UINT   appId;
    ITS_OCTET  bssId;
    ITS_OCTET  mssgDisc;
    ITS_OCTET  mssgType;
		ITS_OCTET  hofacause; 
    union
    {
        DTAP_DATA  DTAPdata;
        MAP_DATA   MAPdata;
        ERROR_DATA ERRdata;
    }
    u;
}
BSSAPData;

/*implementation:internal
*
* PURPOSE:
*     It forms the base BSSAP message class which provides common methods
*     for constructing Dtap and Map messages and passing them to the BSSAP
*     stack.
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
*                        ID :: D0290, ID :: D0300 
*/
class BSSAP_Api
{
public:
    BSSAP_Api()
    {
        memset(&bd, 0, sizeof(BSSAPData));
    }

    BSSAP_Api(BSSAPData* d)
    {
        memset(&bd, 0, sizeof(BSSAPData));
        memcpy(&bd, d, sizeof(BSSAPData));
    }

    virtual ~BSSAP_Api(){};

    void SetAppId(ITS_UINT ch)
    {
        printf("SET APP id**** Connection Id %d\n::", ch);
        bd.appId = ch;
    }
    ITS_UINT GetAppId()
    {
        printf("GET APP id**** Connection Id %d\n::", bd.appId);
        return (bd.appId);
    }

    void SetCallRef(ITS_CTXT cref)
    {
        bd.callrefId = cref;
    }
    ITS_CTXT GetCallRef()
    {
        return (bd.callrefId);
    }

    void SetMssgDisc(ITS_OCTET md)
    {
        bd.mssgDisc = md;
    }
    ITS_OCTET GetMssgDisc()
    {
        return (bd.mssgDisc);
    }

    void SetMssgType(ITS_OCTET mt)
    {
        bd.mssgType = mt;
    }
    ITS_OCTET GetMssgType()
    {
        return (bd.mssgType);
    }

    void SetBssId(ITS_OCTET id)
    {
        bd.bssId = id;
    }
    ITS_OCTET GetBssId()
    {
        return (bd.bssId);
    }
     /* Added by Amaresh for Enhancement */

/* Added by Amaresh as on dated 04-07-08 */
	 void SethofaCause(ITS_OCTET cause)
    {
        bd.hofacause = cause;
    }
    ITS_OCTET GethofaCause()
    {
        return (bd.hofacause);
    }
/* Added by Amaresh as on dated 04-07-08 */

    void SetDTAPdata(DTAP_DATA dtap)
    {
        bd.u.DTAPdata = dtap;
    }
    DTAP_DATA GetDTAPdata()
    {
        return (bd.u.DTAPdata);
    }
    void  SetBSSMAPdata(MAP_DATA map)
    {
        bd.u.MAPdata = map;
    }

    MAP_DATA  GetBSSMAPdata()
    {
        return (bd.u.MAPdata);
    }

    void SetERRCause(ITS_OCTET cause)
    {
        bd.u.ERRdata.error_code = cause;
    }
    ITS_OCTET GetERRCause()
    {
        return (bd.u.ERRdata.error_code);
    }
    /* Addition completed by Amaresh for Enhancement */	
    ITS_INT  SetDestinations(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc,
                                 ITS_OCTET lssn, ITS_OCTET rssn);

    ITS_INT  SendBSSAPMessage(ITS_CTXT& calref);

    ITS_INT SetCIC(ITS_OCTET bscId, ITS_USHORT pcm, ITS_USHORT startTs,
                   ITS_USHORT endTS = 0);

    ITS_INT AcceptConnection(ITS_CTXT callRef);
    ITS_INT RejectConnection(ITS_CTXT callRef);
/*  ITS_INT ReleasedConnection(ITS_CTXT callRef); */
    ITS_INT ReleasedConnection(ITS_CTXT callRef,ITS_CTXT appId,ITS_OCTET cause); //24-04-08	
protected:
    BSSAPData bd;
};

/*implementation:internal
*
* PURPOSE:
*     It is derived from BSSAP_Api and has methods for constructing error
*     messages.
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
*/
class BSSDtap : public BSSAP_Api
{

public:
    BSSDtap()
    {
        memset(&bd, 0, sizeof(BSSAPData));
    }

    BSSDtap(BSSAPData* d) : BSSAP_Api(d)
    {
        memset(&bd, 0, sizeof(BSSAPData));
        memcpy(&bd, d, sizeof(BSSAPData));
    }

    ~BSSDtap(){};

    void SetDTAPdata(ITS_OCTET* d, ITS_USHORT l)
    {
        memcpy(bd.u.DTAPdata.dtapMsg, d, l);
        bd.u.DTAPdata.len = l;
    }

    void GetDTAPdata(ITS_OCTET* d, ITS_USHORT* l)
    {
        *l = bd.u.DTAPdata.len;
        memcpy(d, bd.u.DTAPdata.dtapMsg, bd.u.DTAPdata.len);
    }

    void SetBSSAPData(BSSAPData* d)
    {
        memcpy(&bd, d, sizeof(BSSAPData));
    }
                                                                                                                                              
    BSSAPData* GetBSSAPData()
    {
        return (&bd);
    }
};

/*implementation:internal
*
* PURPOSE:
*      It is derived from BSSAP_Api and has methods for constructing BSSMap 
*      messages. 
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
*/
class BSSMap : public BSSAP_Api
{

public:
    BSSMap()
    {
        memset(&bd, 0, sizeof(BSSAPData));
    }

    BSSMap(BSSAPData* d) : BSSAP_Api(d)
    {
        memset(&bd, 0, sizeof(BSSAPData));
        memcpy(&bd, d, sizeof(BSSAPData));
    }

    ~BSSMap(){};

    void SetMAPdata(ITS_OCTET* d, ITS_USHORT l)
    {
        memcpy(bd.u.MAPdata.mapMsg, d, l);
        bd.u.MAPdata.len = l;
    }

    void GetMAPdata(ITS_OCTET* d, ITS_USHORT* l)
    {
        *l = bd.u.MAPdata.len;
        memcpy(d, bd.u.MAPdata.mapMsg, bd.u.MAPdata.len);
    }

    void SetBSSAPData(BSSAPData* d)
    {
        memcpy(&bd, d, sizeof(BSSAPData));
    }

    BSSAPData* GetBSSAPData()
    {
        return (&bd);
    }

};

/*implementation:internal
*
* PURPOSE:
*     It is derived from BSSAP_Api and has methods for constructing error
*     messages.
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
*/
class BSSAPError : public BSSAP_Api
{

public:
    BSSAPError()
    {
        memset(&bd, 0, sizeof(BSSAPData));
    }

    ~BSSAPError(){};

    void SetErrCode(ITS_OCTET err)
    {
        bd.u.ERRdata.error_code = err;
    }
    ITS_OCTET GetErrCode()
    {
        return (bd.u.ERRdata.error_code);
    }

    void SetPcm(ITS_USHORT pcm)
    {
        bd.u.ERRdata.pcm = pcm;
    }
    ITS_USHORT GetPcm()
    {
        return (bd.u.ERRdata.pcm);
    }

    void SetTimeSlot(ITS_OCTET ts)
    {
        bd.u.ERRdata.ts = ts;
    }
    ITS_OCTET GetTimeSlot()
    {
        return (bd.u.ERRdata.ts);
    }
/* Added by Amaresh for point code ,ssn & Msg Type */
    void SetPointCode(ITS_UINT pc)
    {
        bd.u.ERRdata.pc = pc;
    }
    ITS_UINT GetPointCode()
    {
        return (bd.u.ERRdata.pc);
    }

    void SetSSN(ITS_OCTET ssn)
    {
        bd.u.ERRdata.ssn = ssn;
    }
    ITS_OCTET GetSSN()
    {
        return (bd.u.ERRdata.ssn);
    }
#if 0
    void SetMessgType(ITS_OCTET mType)
    {
        bd.u.mssgType = mType;
    }
    ITS_OCTET GetMessgType()
    {
        return (bd.u.mssgType);
    }
#endif
/* Addition completed  by Amaresh for point code ,ssn & Msg Type */

};

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
*                        ID :: D0980
*/
class BSSAP_Interface
{
public:

    ITS_INT  DispatchDtapToApp(BSSAP_Call* call);
    ITS_INT  DispatchMapToApp(BSSAP_Call* call, BSSAP_Message* mdata);
/* Added by Amaresh as on dated 03-07-08 error in HO-REQ */
		ITS_INT  DispatchMapErrToApp(BSSAP_Call* call, BSSAP_Message* mdata,ITS_OCTET cause);
/* Added by Amaresh as on dated 03-07-08 error in HO-REQ */
    ITS_INT  DispatchMapUDTtoApp(BSSAP_Message* msg, ITS_OCTET nwId, ITS_OCTET *data, ITS_UINT len);
    ITS_INT  DispatchErrorToApp(BSSAP_Call* call, ITS_OCTET errType,
                                    ITS_OCTET errCode);
/* Enhanced by Amaresh for passing cause to BSC-USER */
/*    ITS_INT  DispatchSccpIndToApp(ITS_OCTET msgType, ITS_OCTET msgCode,
                                    BSSAP_Call* call);  */
      ITS_INT  DispatchSccpIndToApp(ITS_OCTET msgType, ITS_OCTET msgCode,ITS_OCTET cause,BSSAP_Call* call);	
    ITS_INT  DispatchErrorToApp(ITS_OCTET errType, ITS_OCTET errCode,
                                    ITS_OCTET mType = 0, ITS_USHORT pcm = 0, 
                                        ITS_OCTET ts = 0);
/* Enhanced by Amaresh for PC & SSN to User */
   ITS_INT  DispatchErrorToApp(ITS_OCTET errType, ITS_OCTET errCode,
                                    ITS_UINT pc, ITS_OCTET ssn);
};

#endif
