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
 *  ID: $Id: ansi-isup_95_intern.h,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:10  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:56  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:54:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1.38.1  2004/12/06 13:39:23  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 10:49:27  ssingh
 * LOG: Latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.2  2003/03/15 13:02:22  ssingh
 * LOG: Changes done to support CRM/CRA messaging for ANSI
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2002/12/02 04:06:14  sjaddu
 * LOG: Handling of continuity in 95
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:49  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/06 06:12:53  hbalimid
 * LOG: Took care of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/03 18:17:52  hbalimid
 * LOG: MessageProcs updated.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/03 14:15:56  hbalimid
 * LOG: ANSI95 specific internal header.
 * LOG:
 *
 ****************************************************************************/

#ifndef ANSI_ISUP_95_INTERN_H
#define ANSI_ISUP_95_INTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ansi/isup_92.h>

/*
 * Functions returning Message handlers
 * depending on message type and call state
 */
__ISUP_MsgHandlerProc __ISUP_GetMsgHandler_ANSI95(ITS_OCTET msgType,
                                                  ITS_ISUP_STATE state);
__ISUP_TimeoutHandlerProc __ISUP_GetTimeoutHandler_ANSI95(ITS_UINT timerID,
                                                          ITS_ISUP_STATE state);

/*
 * Message handling functions for all the call states
 */
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_Idle_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAcm_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAnm_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_RcvdIncomingAnm_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRlc_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRes_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAcm_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAnm_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_SentOutgoingAnm_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRlc_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRes_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRel_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRsc_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingGra_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReportAndCra_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReportHaveCra_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCra_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingIam_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCotAndIam_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingIam_ANSI95(ITS_OCTET msgType);

__ISUP_MsgHandlerProc __ISUP_Received_UnexpectedMsg_ANSI95(ITS_OCTET msgType);

__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReport_ANSI95(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCot_ANSI95(ITS_OCTET msgType);

__ISUP_TimeoutHandlerProc __ISUP_Received_UnexpectedTimeout_ANSI95(ITS_UINT timerID);


#ifdef __cplusplus
}
#endif

#endif /* ANSI_ISUP_95_INTERN_H */

