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
 *  ID: $Id: sccp_pegs.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:50  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/06/22 12:59:35  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG:
 ****************************************************************************/

#ifndef _ITS_SCCP_PEGS_H_
#define _ITS_SCCP_PEGS_H_

/*
 *  SCCP Peg Public interface
 */

typedef struct 
{
    ITS_UINT userMsgsSent;
    ITS_UINT remoteMsgsRcvd;
    ITS_UINT routingFailure;
    ITS_UINT remoteGTTRequest;
    ITS_UINT remoteGTTSucc;
    ITS_UINT remoteGTTFail;
    ITS_UINT remoteMsgsDecodeErr;
    ITS_UINT userMsgsEncodeErr;
    ITS_UINT remoteReassembleErr;
    ITS_UINT hopCounterVilotionErr;
    ITS_UINT userSegmentationErr;
    ITS_UINT timerTiarExpiry;
    ITS_UINT userInitiatedRLSD;
    ITS_UINT userInitiatedReset;
    ITS_UINT remoteUDTRcvd;
    ITS_UINT remoteXUDTRcvd;
    ITS_UINT remoteUDTSRcvd; 
    ITS_UINT remoteXUDTSRcvd;
    ITS_UINT remoteLUDTRcvd;
    ITS_UINT remoteLUDTSRcvd;
    ITS_UINT userUDTSent;
    ITS_UINT userXUDTSent;
    ITS_UINT userUDTSSent;
    ITS_UINT userXUDTSSent;
    ITS_UINT userLUDTSent;
    ITS_UINT userLUDTSSent;
    ITS_UINT userCRSent;
    ITS_UINT sentCREFToRemote;
    ITS_UINT sentRSRToRemote;
    ITS_UINT sentERRToRemote;
    ITS_UINT remoteCRRcvd;
    ITS_UINT remoteCREFRcvd;
    ITS_UINT remoteRSRRcvd;
    ITS_UINT remoteERRRcvd;
    ITS_UINT remoteMsgsForLocalSSRcvd;
    ITS_UINT userDT1Sent;
    ITS_UINT remoteDT1Rcvd;
    ITS_UINT userDT2Sent;
    ITS_UINT remoteDT2Rcvd;
    ITS_UINT userEDSent;
    ITS_UINT remoteEDRcvd;
    ITS_UINT remoteSSPRcvd;
    ITS_UINT remoteSSARcvd;
    ITS_UINT remoteSSCRcvd;
    ITS_UINT localSSProhibited;
    ITS_UINT localSSAllowed;
    ITS_UINT localSSCongested;

}
SCCP_Pegs;

#ifdef __cplusplus
extern "C"
{
#endif


ITSSS7DLLAPI int SCCP_GetAllPegs(SCCP_Pegs *genPegs);

ITSSS7DLLAPI int SCCP_ClearAllPegs();

ITSSS7DLLAPI int SCCP_ClearPeg( ITS_UINT pegId);


#ifdef __cplusplus
}
#endif


#endif /*_ITS_SCCP_PEGS_H_*/
