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
 *  ID: $Id: bssap_cicdb.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.5  2006/01/17 07:30:38  mkrishna
 * LOG: timerType added in to cic record
 * LOG:
 * LOG: Revision 1.1.2.4  2005/12/05 09:23:24  mkrishna
 * LOG: Added flag for abnormal blk/unblk messages
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.2  2005/10/06 08:28:39  adutta
 * LOG: Network Id modifications
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_CICDB_H_
#define  _BSSAP_CICDB_H_

#include <bssap.h>
#include <bssap_common.h>

#define BS_CIC_INFO                2

#define CALL_ST_IDLE               1
#define CALL_ST_BUSY               2 

#define CIC_ST_BLOCK               3 
#define CIC_ST_UNBLK               5 

 
typedef struct
{
    ITS_OCTET   ts;
    ITS_USHORT  pcm;
    ITS_OCTET   nwId;
    ITS_OCTET   localState;
    ITS_OCTET   remoteState;
    ITS_OCTET   callState;
    ITS_SERIAL  timerId;
    ITS_OCTET   timerType;
    ITS_BOOLEAN statusFlag;
    ITS_OCTET app_blo_flag;
    ITS_OCTET app_ubl_flag;
}
CICData;

typedef struct
{
    ITS_SERIAL  timerId;
}
ResetData;

typedef struct
{
    ITS_SERIAL  timerId17;  // T18 >> T17
    ITS_SERIAL  timerId18;
}
OverloadData;

/*implementation:internal
*
* PURPOSE:
*       Maintains CIC CTXT table in DSM. each record contains local,
*       remote, call states and timerid.
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
*                        ID :: D0190, ID :: D0200
*/
class BSSAP_CicDB
{
public:
    
    ITS_INT AddCIC(ITS_OCTET nwId, ITS_USHORT pcm,
                      ITS_USHORT startTS, ITS_USHORT endTS = 0);
/*  ITS_INT ModifyCICRecord(ITS_UINT cic, CICData* cicRec); */
		ITS_INT ModifyCICRecord(ITS_UINT cic, CICData* cicRec, ITS_OCTET msgType);/* 21-07-08 */
    ITS_INT RemoveCICRecord(ITS_UINT cic,ITS_OCTET nwId);
/*  CICData* FetchCICRecord(ITS_UINT cic);*/
		CICData* FetchCICRecord(ITS_UINT cic,ITS_OCTET msgType,ITS_OCTET bscId); /* 21-07-08 */
    ITS_UINT GetCICRecordCount();
};

#endif
