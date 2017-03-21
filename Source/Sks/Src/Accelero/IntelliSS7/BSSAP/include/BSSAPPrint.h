/****************************************************************************
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
 *  ID: $Id: BSSAPPrint.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.2.3  2005/11/30 07:33:56  adutta
 * LOG: Added Authentication Failue message
 * LOG:
 * LOG: Revision 9.1.2.2  2005/11/18 05:03:35  adutta
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 9.1.2.1  2005/09/29 07:11:02  adutta
 * LOG: Print paging response
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:34  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/10 16:57:36  ngoel
 * LOG: DTAP merge
 * LOG:
 * LOG: Revision 1.1.2.9  2002/05/31 21:09:28  ngoel
 * LOG: merge MM messages
 * LOG:
 * LOG: Revision 1.1.2.8  2002/05/29 20:48:26  ngoel
 * LOG: add dtmf messages
 * LOG:
 * LOG: Revision 1.1.2.7  2002/05/29 20:10:55  ngoel
 * LOG: add start dtmf
 * LOG:
 * LOG: Revision 1.1.2.6  2002/05/29 16:08:41  ngoel
 * LOG: add prototype
 * LOG:
 * LOG: Revision 1.1.2.5  2002/05/22 17:05:42  ngoel
 * LOG: merge Print Functions
 * LOG:
 * LOG: Revision 1.1.2.4  2002/05/21 14:49:54  ngoel
 * LOG: add comments
 * LOG:
 * LOG: Revision 1.1.2.3  2002/05/10 18:38:03  ngoel
 * LOG: add function
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/09 18:03:50  ngoel
 * LOG: add layer info in BSSAP_Message
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/09 15:06:02  ngoel
 * LOG: add print headers
 * LOG:
 * LOG: Revision 6.1.4.1  2002/04/24 22:20:54  hxing
 * LOG: Back port to PR5.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.4  2001/11/26 15:22:18  dzhang
 * LOG: Modify PrintBSSMAPMsgHandoverRequired()
 * LOG:
 * LOG: Revision 1.3  2001/11/20 14:52:51  dzhang
 * LOG: Minor change in format
 * LOG:
 * LOG: Revision 1.2  2001/11/12 14:42:52  dzhang
 * LOG: update to latest spec version8.9.0
 * LOG:
 * LOG: Revision 1.1  2001/10/02 21:51:58  dzhang
 * LOG: Initially check in after unit test
 * LOG:
 *
 ****************************************************************************/

#ifndef _BSSAPPRINT_H_
#define _BSSAPPRINT_H_

#include <BSSAPPrintIE.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

void PrintBSSAPMessage(ITS_OCTET* buf, int len);

// prototypes for Print BSSMAP messages
void PrintBSSMAPMsgAssignComplete(BSSAP_Message*);        
void PrintBSSMAPMsgAssignFailure(BSSAP_Message*);   
void PrintBSSMAPMsgAssignReq(BSSAP_Message*);  
void PrintBSSMAPMsgHandoverCandidateEnq(BSSAP_Message*);
void PrintBSSMAPMsgHandoverCandidateRsp(BSSAP_Message*); 
void PrintBSSMAPMsgHandoverCmd(BSSAP_Message*);
void PrintBSSMAPMsgHandoverComplete(BSSAP_Message*); 
void PrintBSSMAPMsgHandoverDetect(BSSAP_Message*);
void PrintBSSMAPMsgHandoverFailure(BSSAP_Message*);       
void PrintBSSMAPMsgHandoverPerformed(BSSAP_Message*);        
void PrintBSSMAPMsgHandoverReq(BSSAP_Message*);        
void PrintBSSMAPMsgHandoverReqAck(BSSAP_Message*);        
void PrintBSSMAPMsgHandoverRequired(BSSAP_Message*);        
void PrintBSSMAPMsgHandoverRequiredRej(BSSAP_Message*); 
void PrintBSSMAPMsgHandoverSucceeded(BSSAP_Message*); 
void PrintBSSMAPMsgClrCmd(BSSAP_Message*);
void PrintBSSMAPMsgClrComplete(BSSAP_Message*);
void PrintBSSMAPMsgClrReq(BSSAP_Message*); 
//void PrintBSSMAPMsgRel1Reserved(BSSAP_Message*); 
//void PrintBSSMAPMsgRel2Reserved(BSSAP_Message*);
void PrintBSSMAPMsgSAPInRej(BSSAP_Message*);
void PrintBSSMAPMsgConfusion(BSSAP_Message*);
void PrintBSSMAPMsgSuspend(BSSAP_Message*);
void PrintBSSMAPMsgResume(BSSAP_Message*); 
void PrintBSSMAPMsgReset(BSSAP_Message*); 
void PrintBSSMAPMsgResetAck(BSSAP_Message*);  
void PrintBSSMAPMsgOverload(BSSAP_Message*);   
//void PrintBSSMAPMsgGenReserved(BSSAP_Message*); 
void PrintBSSMAPMsgResetCircuit(BSSAP_Message*);
void PrintBSSMAPMsgResetCircuitAck(BSSAP_Message*);
void PrintBSSMAPMsgMSCInvokeTrace(BSSAP_Message*); 
void PrintBSSMAPMsgBSSInvokeTrace(BSSAP_Message*);
void PrintBSSMAPMsgBlock(BSSAP_Message*); 
void PrintBSSMAPMsgBlockAck(BSSAP_Message*); 
void PrintBSSMAPMsgUnblock(BSSAP_Message*);      
void PrintBSSMAPMsgUnblockAck(BSSAP_Message*); 
void PrintBSSMAPMsgCktGroupBlock(BSSAP_Message*);   
void PrintBSSMAPMsgCktGroupBlockAck(BSSAP_Message*); 
void PrintBSSMAPMsgCktGroupUnblock(BSSAP_Message*);
void PrintBSSMAPMsgCktGroupUnblockAck(BSSAP_Message*);
void PrintBSSMAPMsgUnequippedCkt(BSSAP_Message*); 
void PrintBSSMAPMsgChangeCkt(BSSAP_Message*); 
void PrintBSSMAPMsgChangeCktAck(BSSAP_Message*); 
void PrintBSSMAPMsgResourceReq(BSSAP_Message*);        
void PrintBSSMAPMsgResourceInd(BSSAP_Message*);        
void PrintBSSMAPMsgPaging(BSSAP_Message*);        
void PrintBSSMAPMsgPagingResponse(BSSAP_Message*);        
void PrintBSSMAPMsgCipherModeCmd(BSSAP_Message*); 
void PrintBSSMAPMsgCipherModeComplete(BSSAP_Message*); 
void PrintBSSMAPMsgCipherModeRej(BSSAP_Message*);      
void PrintBSSMAPMsgClassmarkUpdate(BSSAP_Message*); 
void PrintBSSMAPMsgClassmarkReq(BSSAP_Message*);
void PrintBSSMAPMsgCompleteLayer3Info(BSSAP_Message*);      
void PrintBSSMAPMsgLoadInd(BSSAP_Message*);                
void PrintBSSMAPMsgQueuingInd(BSSAP_Message*);        
void PrintBSSMAPMsgVGCSVBSSetup(BSSAP_Message*);        
void PrintBSSMAPMsgVGCSVBSSetupAck(BSSAP_Message*);        
void PrintBSSMAPMsgVGCSVBSSetupRefuse(BSSAP_Message*);        
void PrintBSSMAPMsgVGCSVBSAssignReq(BSSAP_Message*);        
void PrintBSSMAPMsgVGCSVBSAssignRsult(BSSAP_Message*);        
void PrintBSSMAPMsgVGCSVBSAssignFailure(BSSAP_Message*);       
void PrintBSSMAPMsgVGCSVBSQueuingInd(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkReq(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkReqAck(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkReqConfirm(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkReleaseInd(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkRejCmd(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkReleaseCmd(BSSAP_Message*);        
void PrintBSSMAPMsgUplinkSeizedCmd(BSSAP_Message*);
void PrintBSSMAPMsgCommonID(BSSAP_Message*);
void PrintBSSMAPMsgLSAInfo(BSSAP_Message*);
void PrintBSSMAPMsgConnOrientInfo(BSSAP_Message*);
void PrintBSSMAPMsgPerformLocReq(BSSAP_Message*);
void PrintBSSMAPMsgPerformLocRsp(BSSAP_Message*);
void PrintBSSMAPMsgPerformLocAbort(BSSAP_Message*);
void PrintBSSMAPMsgConnlessInfo(BSSAP_Message*);
void PrintBSSMAPMsgAlerting(BSSAP_Message*);
void PrintBSSMAPMsgCallConfirm(BSSAP_Message*);
void PrintBSSMAPMsgCallProceeding(BSSAP_Message*);
void PrintBSSMAPMsgConnect(BSSAP_Message* iMsg);
void PrintBSSMAPMsgConnectAck(BSSAP_Message* iMsg);
void PrintBSSMAPMsgEmergencySetup(BSSAP_Message* iMsg);
void PrintBSSMAPMsgProgress(BSSAP_Message* iMsg);
void PrintBSSMAPMsgCCEstablishment(BSSAP_Message* iMsg);
void PrintBSSMAPMsgSetup(BSSAP_Message* iMsg);
void PrintBSSMAPMsgModify(BSSAP_Message* iMsg);
void PrintBSSMAPMsgModifyComplete(BSSAP_Message* iMsg);
void PrintBSSMAPMsgModifyReject(BSSAP_Message* iMsg);
void PrintBSSMAPMsgUserInformation(BSSAP_Message* iMsg);
void PrintBSSMAPMsgHold(BSSAP_Message* iMsg);
void PrintBSSMAPMsgHoldAck(BSSAP_Message* iMsg);
void PrintBSSMAPMsgHoldReject(BSSAP_Message* iMsg);
void PrintBSSMAPMsgRetrieve(BSSAP_Message* iMsg);
void PrintBSSMAPMsgRetrieveAck(BSSAP_Message* iMsg);
void PrintBSSMAPMsgRetrieveReject(BSSAP_Message* iMsg);
void PrintBSSMAPMsgDisconnect(BSSAP_Message* iMsg);
void PrintBSSMAPMsgRelease(BSSAP_Message* iMsg);
void PrintBSSMAPMsgReleaseComplete(BSSAP_Message* iMsg);
void PrintBSSMAPMsgCongestionControl(BSSAP_Message* iMsg);
void PrintBSSMAPMsgNotify(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStartDTMF(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStartDTMFAck(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStartDTMFReject(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStopDTMF(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStopDTMFAck(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStatus(BSSAP_Message* iMsg);
void PrintBSSMAPMsgStatusEnquiry(BSSAP_Message* iMsg);
void PrintBSSMAPMsgIMSIDetachIndication(BSSAP_Message* iMsg);
void PrintBSSMAPMsgLocationUpdatingAccept(BSSAP_Message* iMsg);
void PrintBSSMAPMsgLocationUpdatingReject(BSSAP_Message* iMsg);
void PrintBSSMAPMsgLocationUpdatingRequest(BSSAP_Message* iMsg);
void PrintBSSMAPMsgAuthenticationReject(BSSAP_Message* iMsg);
void PrintBSSMAPMsgAuthenticationRequest(BSSAP_Message* iMsg);
void PrintBSSMAPMsgAuthenticationResponse(BSSAP_Message* iMsg);
void PrintBSSMAPMsgAuthenticationFailure(BSSAP_Message* iMsg);
void PrintBSSMAPMsgTMSIReallocCommand(BSSAP_Message* iMsg);
void PrintBSSMAPMsgTMSIReallocComplete(BSSAP_Message* iMsg);
void PrintBSSMAPMsgIdentityRequest(BSSAP_Message* iMsg);
void PrintBSSMAPMsgIdentityResponse(BSSAP_Message* iMsg);
void PrintBSSMAPMsgCMServiceAccept(BSSAP_Message* iMsg);
void PrintBSSMAPMsgCMServiceReject(BSSAP_Message* iMsg);    
void PrintBSSMAPMsgCMServiceAbort(BSSAP_Message* iMsg);   
void PrintBSSMAPMsgCMServiceRequest(BSSAP_Message* iMsg);   
void PrintBSSMAPMsgCMReestablishmentReq(BSSAP_Message* iMsg);
void PrintBSSMAPMsgAbort(BSSAP_Message* iMsg);
void PrintBSSMAPMsgMMInformation(BSSAP_Message* iMsg);
void PrintBSSMAPMsgMMStatus(BSSAP_Message* iMsg);
void PrintBSSMAPMsgMMNull(BSSAP_Message* iMsg);

#if defined(ITS_NAMESPACE)
}
#endif

#endif  // !_BSSAPPRINT_H_
