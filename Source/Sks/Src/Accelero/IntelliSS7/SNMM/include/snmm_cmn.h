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
 *  ID: $Id: snmm_cmn.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:52  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:25  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:32  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 02:44:09  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:31  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 16:14:33  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/12/29 00:12:09  mmiers
 * LOG: Fix ITU version
 * LOG:
 * LOG: Revision 5.3  2001/12/28 20:48:23  mmiers
 * LOG: CCITT uses the SLS field for SLC
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_SNMM_CMN_H_
#define _ITS_SNMM_CMN_H_

#ident "$Id: snmm_cmn.h,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

typedef struct
{
    ITS_OCTET                   headingCode;
    union
    {
        SNMM_CHANGEOVER             changeOver;
        SNMM_CHANGEBACK             changeBack;
#if !defined(CCITT) && !defined(PRC) && !defined(TTC)
        SNMM_INHIBIT                managementInhibit;
        SNMM_EMERG_CHANGEOVER       emergencyChangeOver;
        SNMM_DATALINK_CONN_ACK      datalinkConnectAck;
#endif
        SNMM_DATALINK_CONNECT       datalinkConnect;
        SNMM_TRANSFER_STATE         transferState;
        SNMM_ROUTE_SET_TEST         routeSetTest;
        SNMM_TRANSFER_CONTROL       transferControl;
        SNMM_USER_PART_UNAVAILABLE  userPartUnavailable;
    }
    data;
}
SNMM_MESSAGE;

#endif /* _ITS_SNMM_CMN_H_ */

