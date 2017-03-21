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
 * ID: $Id: bssap_msc-cicdb.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.2  2005/11/28 05:24:17  adutta
 * LOG: Status for Blk/Unblk to check abnormal flow
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_CICDB_H_
#define  _BSSAP_CICDB_H_

#include <bssap-msc.h>
#include <bssap_msc-common.h>

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
    ITS_BOOLEAN statusFlag;
}
CICData;

typedef struct
{
    ITS_SERIAL  timerId;
}
ResetData;

typedef struct
{
    ITS_SERIAL  timerId5;  // T6 >> T5
    ITS_SERIAL  timerId6;
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
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01 
*                        ID :: D0240, ID :: D0230
*/
class BSSAP_CicDB
{
public:
    
    ITS_INT AddCIC(ITS_OCTET nwId, ITS_USHORT pcm,
                      ITS_USHORT startTS, ITS_USHORT endTS = 0);
    ITS_INT ModifyCICRecord(ITS_UINT cic, CICData* cicRec);
    ITS_INT RemoveCICRecord(ITS_UINT cic);
    CICData* FetchCICRecord(ITS_UINT cic);
    ITS_UINT GetCICRecordCount();
};

#endif
