/****************************************************************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 * ID:$Id: ISUP_SendMsg.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:19  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 1.1  2003/02/19 15:35:50  vnitin
 * LOG:Add functional tester for Tandem
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
 ****************************************************************************/

#ifndef _SEND_ISUP_MSG_H_
#define _SEND_ISUP_MSG_H_

#include <its.h>


#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


#ifdef ANSI
#define FILENAME        "$nodea.vnitin.ANSIMSG"
#else
#define FILENAME        "ccitt_msgs.txt"
#endif


char* GetFilename();

/*
 * Messages common to Both ITU93 and ANSI92
 *
 * Address Complete - ACM
 * Answer - ANM
 * Blocking - BLO
 * Blocking Acknowledgement - BLA
 * Call Progress - CPG
 * Circuit Group Blocking - CGB
 * Circuit Group Blocking Acknowledgement - CGBA
 * Circuit Query - CQM
 * Circuit Query Response - CQR
 * Circuit Group Unblocking - CGU
 * Circuit Group Unblocking Acknowledgement - CGUA
 * Circuit Group Reset - GRS
 * Circuit Group Reset Acknowledgement - GRA
 * Confusion - CFN
 * Continuity - COT
 * Continuity Check Request - CCR
 * Forward Transfer - FOT
 * Information Request - INR
 * Information - INF
 * Initial Address - IAM
 * Loop Back Acknowledgement - LPA
 * Pass Along - PAM
 * Release - REL
 * Release Complete - RLC
 * Reset Circuit - RSC
 * Resume - RES
 * Suspend - SUS
 * Unblocking - UBL
 * Unblocking Acknowledgement - UBA
 * Unequipped Circuit Identification Code - UCIC
 *
 */

/*
 * Messages only in ITU93 ISUP
 *
 * Charge Information - CRG
 * Connect - CON
 * Facility - FAC
 * Facility Accepted - FAA
 * Facility Reject - FRJ
 * Facility Request - FAR
 * Identification Request - IDR
 * Identification Response - IRS
 * Network Resource Management - NRM
 * Overload - OLM
 * Segmentation - SGM
 * Subsequent Address - SAM
 * User Part Available - UPA
 * User Part Test - UPT
 * User to User - USR
 *
 * Loop Prevention - LOP (only in ITU97)
 *
 */

/*
 * Messages only in ANSI92 ISUP
 *
 * Circuit Reservation - CRM
 * Circuit Reservation Acknowledgement - CRA
 * Circuit Validation Test - CVT
 * Circuit Validation Response - CVR
 * Exit - EXM
 *
 * Facility - FAC (only in ANSI95)
 *
 */


/*
 * Common for Both ITU93 and ANSI92
 */
 
int TestSendACMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendANMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendBLARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendBLORequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCCRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCFNRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGBRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGBARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGURequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCOTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCPGRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCQMRequest(ITS_HANDLE handle, ITS_HDR *hdr);


int TestSendFOTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendGRARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendGRSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendINFRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendINRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendLPARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendPAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRELRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRESRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRSCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSUSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUBLRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUBARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUCICRequest(ITS_HANDLE handle, ITS_HDR *hdr);


/*
 * Only in ANSI92 - Generic ANSI Variant
 */

#ifdef ANSI

int TestSendCRARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCRMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCVRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCVTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendEXMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif


/*
 * Only in ITU93 - Generic ITU Variant
 */

#ifdef CCITT

int TestSendCONRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFACRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFAARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFARRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFRJRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIDRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIRSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendNRMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendOLMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSGMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUPARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUPTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUSRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif

/*
 * Only in ITU97 variant
 */

#if defined (CCITT) && defined (ITU_ISUP_97)

int TestSendLOPRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif

/*
 * Only in ANSI95 variant
 */

#if defined (ANSI) && defined (ANSI_ISUP_95)

int TestSendFACRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* _SEND_ISUP_MSG_H_ */
