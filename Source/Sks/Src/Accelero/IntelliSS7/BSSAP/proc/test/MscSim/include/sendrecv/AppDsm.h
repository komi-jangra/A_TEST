/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * 
 *  ID: $Id: AppDsm.h,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.1  2005/09/28 05:51:20  adutta
 * LOG: Remodeled for MSC
 * LOG:
 * LOG: Revision 1.2  2005/02/11 10:25:37  csireesh
 * LOG: Committing after sanitizing Sample App (send-recv) for SCCP-CO: yet to take care of Codec
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include<its++.h>
#include<sccp_intern.h>

#include <App.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/* Used for DSM data */
#define APP_FT_GROUP_ID 0
#define APP_FT_TABLE_ID 49

struct SCCPInfo
{
    ITS_UINT        dlr;
    ITS_UINT        slr;
    SCCP_CONN_STATE state;
};

struct DsmInfo
{
    int opc;
    int dpc;
    SCCP_CallingPartyAddr *cgpa;
    SCCP_CalledPartyAddr  *cdpa;
    SCCPInfo sccpinfo;
    ITS_BOOLEAN src;     /* Denotes initiator of the session:
                            TRUE means CR was sent by self
                            False means CR was received from Remote */
};

int SaveContext(DsmInfo* info, ITS_OCTET *key, ITS_USHORT len);
int RetrieveContext(DsmInfo **info, ITS_OCTET *key, ITS_USHORT len);
int DeleteContext(ITS_OCTET *key, ITS_USHORT len);
