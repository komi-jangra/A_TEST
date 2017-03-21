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
 *  ID: $Id: itu-isup_97_intern.h,v 1.1.1.1 2007-10-08 11:12:19 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:55  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 11:05:31  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/22 08:52:16  akumar
 * LOG: Added new signature for ITU COT procedure
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:50  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/03 19:35:16  hbalimid
 * LOG: Added/modified for wait_outgoing_gra.
 * LOG:
 * LOG: Revision 1.1  2002/06/19 15:40:38  hbalimid
 * LOG: ITU 97 specific intern header
 * LOG:
 *
 ****************************************************************************/

#ifndef ITU_ISUP_97_INTERN_H
#define ITU_ISUP_97_INTERN_H

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Functions returning Message handlers
 * depending on message type and call state
 */
__ISUP_MsgHandlerProc __ISUP_GetMsgHandler_ITU97(ITS_OCTET msgType,
                                                 ITS_ISUP_STATE state);
/*
 * Message handling functions for all the call states
 */
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_Idle_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAcm_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAnm_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_RcvdIncomingAnm_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRlc_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRes_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAcm_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAnm_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_SentOutgoingAnm_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRlc_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRes_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRel_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRsc_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingGra_ITU97(ITS_OCTET msgType);

__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitCotReport_ITU97(ITS_OCTET msgType);
__ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingCot_ITU97(ITS_OCTET msgType);

#ifdef __cplusplus
}
#endif

#endif /* ITU_ISUP_97_INTERN_H */

