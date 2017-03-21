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
 * ID: $Id: bssap_msc-interface.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.6  2006/06/28 04:55:50  adutta
 * LOG: Added interface for pc/ssn passing for mgmt. messages
 * LOG:
 * LOG: Revision 1.1.2.5  2005/12/19 05:06:16  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/18 06:41:51  mkrishna
 * LOG: Added SCCP connection control APIs
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/17 06:24:49  mkrishna
 * LOG: Error interface changes
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:25:41  mkrishna
 * LOG: Variable name changed
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_IFACE_H_
#define  _BSSAP_IFACE_H_

#include <bssap_msc-common.h>
#include <bssap_msc-call.h>
#include <BSSAP++.h>

typedef struct
{
    ITS_OCTET  error_code;
    ITS_USHORT pcm;
    ITS_OCTET  ts;
    ITS_OCTET ssn;
    ITS_UINT pc;
}
ERROR_DATA;
  
typedef struct
{
    ITS_CTXT   callrefId;
    ITS_CTXT   appId;
    ITS_OCTET  bssId;
    ITS_OCTET  mssgDisc;
    ITS_OCTET  mssgType;
    ERROR_DATA ERRdata;
    BSSAP_Message* bssapMsg;
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
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

    void SetAppId(ITS_CTXT id)
    {
        bd.appId = id;
    }
    ITS_CTXT GetAppId()
    {
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

    void SetBSSAPdata(BSSAP_Message* mMssg)
    {
        bd.bssapMsg = mMssg;
    }

    BSSAP_Message* GetBSSAPdata()
    {
        return (bd.bssapMsg);
    }

    ITS_INT  SetDestinations(ITS_OCTET bscId, ITS_UINT lpc, ITS_UINT rpc,
                                 ITS_OCTET lssn, ITS_OCTET rssn);

    ITS_INT  SendBSSAPMessage(ITS_CTXT& calref);

    ITS_INT SetCIC(ITS_OCTET bscId, ITS_USHORT pcm, ITS_USHORT startTs, 
                   ITS_USHORT endTS = 0);

    ITS_INT AcceptConnection(ITS_CTXT callRef);
    ITS_INT RejectConnection(ITS_CTXT callRef);
    ITS_INT ClearConnection(ITS_CTXT callRef);

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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
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
        bd.ERRdata.error_code = err;
    }
    ITS_OCTET GetErrCode()
    {
        return (bd.ERRdata.error_code);
    }

    void SetPcm(ITS_USHORT pcm)
    {
        bd.ERRdata.pcm = pcm;
    }
    ITS_USHORT GetPcm()
    {
        return (bd.ERRdata.pcm);
    }

    void SetTimeSlot(ITS_OCTET ts)
    {
        bd.ERRdata.ts = ts;
    }
    ITS_OCTET GetTimeSlot()
    {
        return (bd.ERRdata.ts);
    }

    void SetPointCode(ITS_UINT pc)
    {
        bd.ERRdata.pc = pc;
    }
    ITS_OCTET GetPointCode()
    {
        return (bd.ERRdata.pc);
    }

    void SetSSN(ITS_OCTET ssn)
    {
        bd.ERRdata.ssn = ssn;
    }
    ITS_OCTET GetSSN()
    {
        return (bd.ERRdata.ssn);
    }


    void SetMessgType(ITS_OCTET mType)
    {
        bd.mssgType = mType;
    }
    ITS_OCTET GetMessgType()
    {
        return (bd.mssgType);
    }
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0330
*/
class BSSAP_Interface
{
public:

    ITS_INT  DispatchMsgToApp(BSSAP_Call* call, BSSAP_Message* mdata);
    ITS_INT  DispatchSccpIndToApp(ITS_OCTET msgType, ITS_OCTET msgCodei, 
                                     BSSAP_Call* call);
    ITS_INT  DispatchMsgToApp(BSSAP_Call* call);
    ITS_INT  DispatchMapUDTtoApp(BSSAP_Message* msg, ITS_OCTET nwId);
    ITS_INT  DispatchErrorToApp(BSSAP_Call* call, ITS_OCTET errType,
                                    ITS_OCTET errCode);
    ITS_INT  DispatchErrorToApp(ITS_OCTET errType, ITS_OCTET errCode,
                                    ITS_OCTET mType = 0, ITS_USHORT pcm = 0, 
                                        ITS_OCTET ts = 0);
    ITS_INT  DispatchErrorToApp(ITS_OCTET errType, ITS_OCTET errCode,
                                    ITS_UINT pc, ITS_OCTET ssn); 

};

#endif
