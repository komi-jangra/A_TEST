/****************************************************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: readISUPMsg.h,v 1.1.1.1 2007-10-08 11:12:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:57  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:07  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:39  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.4  2002/08/01 16:01:46  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.3.2.1  2002/07/31 19:14:19  ssingh
 * LOG: Changes done to support ANSI95 related new params.
 * LOG:
 * LOG: Revision 1.3  2002/06/23 23:27:27  hbalimid
 * LOG: ITU97 specific parameters in Place.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:49  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/04/06 22:43:30  ssharma
 * LOG: reorganized and added files for xml based ISUP Functional test
 * LOG:
 * LOG: Revision 1.2  2002/02/05 20:19:53  ssharma
 * LOG: IntelliNet ISUP stack test directory.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/29 20:32:12  ssharma
 * LOG: Functional test for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/23 18:14:44  ssharma
 * LOG: Interactive functional test for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:08  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 1.1  2000/12/11 23:14:38  hxing
 * LOG: Add testing files
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:36  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef READ_ISUP_MSG_H
#define READ_ISUP_MSG_H


#include <stdio.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/* used to get IE parameter len in Hex */
#define BASE_16            16


/*
#define BUILD_ISUP_MSG_FROM_FILE
*/

int GetOctetsFromStr(ITS_OCTET *array, int nOctets);

ITS_UINT GetUIntFromStrToken();
ITS_USHORT GetUShortFromStrToken();

int NumOfOctets4Digits(ITS_OCTET nDigits);
int ReadISUPMsg(ITS_OCTET isupMsgType, char *filename, ITS_ISUP_IE *ie,
                int *ieCount);


/*
 * Common Parameters to ANSI & CCITT
 */

int ReadMessageInPAMPar(char *buf, ITS_ISUP_IE *ie);
int ReadAccessTransportPar(char *buf, ITS_ISUP_IE *ie);
int ReadAutoCongestionLvlPar(char *buf, ITS_ISUP_IE *ie);
int ReadBackwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallReferencePar(char *buf, ITS_ISUP_IE *ie);
int ReadCalledPartyNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallingPartyNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallingPartyCategoryPar(char *buf, ITS_ISUP_IE *ie);
int ReadCauseInd(char *buf, ITS_ISUP_IE *ie);
int ReadChargeNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitStateIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadConnectRequestPar(char *buf, ITS_ISUP_IE *ie);
int ReadContinuityIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadEOPPar(char *buf, ITS_ISUP_IE *ie);
int ReadEventInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadForwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericDigitsPar(char *buf, ITS_ISUP_IE *ie);
int ReadInfoIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadInfoReqIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadNatureOfConnectionIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadNotificationIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadOptBackwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadOrigCalledNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadRangeAndStatusPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectingNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadServiceActivationPar(char *buf, ITS_ISUP_IE *ie);
int ReadSuspendResumeIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransactionReqPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransitNetworkSelectionPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserServiceInfoPar(char *buf, ITS_ISUP_IE *ie);


/*
 * ANSI Parameters
 */
#ifdef ANSI

int ReadBusinessGrpPar(char *buf, ITS_ISUP_IE *ie);
int ReadCarrierIdPar(char *buf, ITS_ISUP_IE *ie);
int ReadCarrierSelectionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitGrpCharIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitGrpSupervisionMsgTypIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitIdNamePar(char *buf, ITS_ISUP_IE *ie);
int ReadCircuitValRespIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadCLLICodePar(char *buf, ITS_ISUP_IE *ie);
int ReadEgressServicePar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericAddrPar(char *buf, ITS_ISUP_IE *ie);
int ReadJurisdictionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadNetworkTransportPar(char *buf, ITS_ISUP_IE *ie);
int ReadOrigLineInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadOutgoingTrunkGrpNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadServiceCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadSpecialProcessingReqPar(char *buf, ITS_ISUP_IE *ie);

#if defined(ANSI_ISUP_95)

int ReadCircuitAssignMap(char *buf, ITS_ISUP_IE *ie);
int ReadGenericName(char *buf, ITS_ISUP_IE *ie);
int ReadHopCouner(char *buf, ITS_ISUP_IE *ie);
int ReadOperatorServInfo(char *buf, ITS_ISUP_IE *ie);
int ReadPrecedence(char *buf, ITS_ISUP_IE *ie);
int ReadRemoteOperations(char *buf, ITS_ISUP_IE *ie);
int ReadTransMediumUsed(char *buf, ITS_ISUP_IE *ie);
int ReadUserServInfoPrime(char *buf, ITS_ISUP_IE *ie);
int ReadUserToUserIndicators(char *buf, ITS_ISUP_IE *ie);
int ReadUserToUserInfo(char *buf, ITS_ISUP_IE *ie);

#endif

#endif /* ANSI */


/*
 * CCITT Parameters
 */
#ifdef CCITT

int ReadAccessDeliveryInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallDiversionInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadCallHistoryInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadClosedUserGroupInterlockCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadConnectedNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadEchoControlInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadFacilityIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadFreephoneIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericNumberPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericNotificationPar(char *buf, ITS_ISUP_IE *ie);
int ReadGenericReferencePar(char *buf, ITS_ISUP_IE *ie);
int ReadHopCounterPar(char *buf, ITS_ISUP_IE *ie);
int ReadLocationNumberPar(char *buf, ITS_ISUP_IE *ie);
int ReadMCIDRequestIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadMCIDResponseIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadMLPPPrecedencePar(char *buf, ITS_ISUP_IE *ie);
int ReadMessageCompInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadNetworkSpecificFacilityPar(char *buf, ITS_ISUP_IE *ie);
int ReadOptionalForwardCallIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadOrigISCPointCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadParamCompInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadPropagationDelayCounterPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectionNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadRedirectionNumRestrictPar(char *buf, ITS_ISUP_IE *ie);
int ReadRemoteOperationsPar(char *buf, ITS_ISUP_IE *ie);
int ReadSignallingPointCodePar(char *buf, ITS_ISUP_IE *ie);
int ReadSubsequentNumPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransmissionMediumRequirementPar(char *buf, ITS_ISUP_IE *ie);
int ReadTransmissionMediumRequirementPrimePar(char *buf, ITS_ISUP_IE *ie);
int ReadTransmissionMediumUsedPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserServiceInfoPrimePar(char *buf, ITS_ISUP_IE *ie);
int ReadUserTeleserviceInfoPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserToUserIndPar(char *buf, ITS_ISUP_IE *ie);
int ReadUserToUserInfoPar(char *buf, ITS_ISUP_IE *ie);

#if defined(ITU_ISUP_97)

int ReadCallTransferReference(char *buf, ITS_ISUP_IE *ie);
int ReadCCSS(char *buf, ITS_ISUP_IE *ie);

#endif


#endif /* CCITT */

#ifdef CCITT

static const char paramArray[0xFF+1][0xFF+1] = { "(0x00) End Of Optional Parameters",
"(0x01) Call Refernce (national use)", "(0x02) Transmission Medium Requirements",
"(0x03) Access Transport", "(0x04) Called Party Number",
"(0x05) Subsequent Number", "(0x06) Nature Of Connection Indicators",
"(0x07) Forward Call Indicators", "(0x08) Optional Forward Call Indicators",
"(0x09) Calling Party's Category", "(0x0A) Calling Pary Number",
"(0x0B) Redirecting Number", "(0x0C) Redirection Number",
"(0x0D) Connection Request", "(0x0E) Information Request Indicators (Nat'l use)",
"(0x0F) Information Indicators (National use)",  "(0x10) Continuity Indicators",
"(0x11) Backward Call Indicators", "(0x12) Cause Indicators",
"(0x13) Redirection Information", "(0x14) CCITT RED ONLY",
"(0x15) Circuit Group supervision msg type indicators", "(0x16) Range and Status",
"(0x17) ITU BLUE ONLY", "(0x18) Facility Indicator",
"(0x19) CCITT RED ONLY", "(0x1A) Closed user group interlock code",
"(0x1B) CCITT RED ONLY", "(0x1C) CCITT RED ONLY",
"(0x1D) User Service Information", "(0x1E) Signalling Point Code",
"(0x1F) CCITT RED ONLY", "(0x20) User-to-user information",
"(0x21) Connected Number", "(0x22) Suspend resume Indicators",
"(0x23) Transit Network selection (national use)", "(0x24) Event Information",
"(0x25) Circuit Assignment Map Parameter", "(0x26) Circuit State Indicator",
"(0x27) Automatic congestion level", "(0x28) Original Called Number",
"(0x29) Optional backward call indicators", "(0x2A) User-to-user indicators",
"(0x2B) Origination ISC point code", "(0x2C) Generic Notification",
"(0x2D) Call history information", "(0x2E) Access delivery information",
"(0x2F) Network specific facilities", "(0x30) User Service Information Prime",
"(0x31) Propagtion Delay counter", "(0x32) Remote Operations",
"(0x33) Service Activation", "(0x34) User Teleservice Information",
"(0x35) Transmision medium used", "(0x36) Call diversion information",
"(0x37) Echo Control information", "(0x38) Message compatibility information",
"(0x39) Parameter compatibility information", "(0x3A) MLPP precedence",
"(0x3B) MCID request indicator", "(0x3C) MCID response indicator",
"(0x3D) Hop counter", "(0x3E) Transmission medium requirement prime",
"(0x3F) Location Number", "(0x40) REdirection Number restriction",
"(0x41) Freephone indicators (reserved)", "(0x42) Generic Refernce",
"(0x43) Call Transfer Reference", "(0x44) Loop prevention indicators",
"(0x45) Call transfer number", "(0x46) Undefined parameter",
"(0x47) Undefined parameter", "(0x48) Undefined parameter",
"(0x49) Undefined parameter", "(0x4A) Undefined parameter",
"(0x4B) CCSS Call indicator", "(0x4C) Forward GVNS parameter",
"(0x4D) Backward GVNS parameter", "(0x4E) Redirect Capability (rsvd for natl use)",
"(0x4F) Undefined Parameter", "(0x50) Undefined Parameter",
"(0x51) Undefined Parameter", "(0x52) Undefined Parameter",
"(0x53) Undefined Parameter", "(0x54) Undefined Parameter",
"(0x55) Undefined Parameter", "(0x56) Undefined Parameter",
"(0x57) Undefined Parameter", "(0X58) Undefined Parameter",
"(0X59) Undefined Parameter", "(0X5A) Undefined Parameter",
"(0x5B) Network Management controls parameter", "(0x5C) Undefined Parameter",
"(0x5D) Undefined Parameter", "(0x5E) Undefined Parameter",
"(0x5F) Undefined Parameter", "(0x60) Undefined Parameter",
"(0x61) Undefined Parameter", "(0x62) Undefined Parameter",
"(0x63) Undefined Parameter", "(0x64) Undefined Parameter",
"(0x65) Correlation ID", "(0x66) SCF ID",
"(0x67) Undefined Parameter", "(0x68) Undefined Parameter",
"(0x69) Undefined Parameter", "(0x6A) Undefined Parameter",
"(0x6B) Undefined Parameter", "(0x6C) Undefined Parameter",
"(0x6D) Undefined Parameter", "(0x6E) Call diversion treatment indicators",
"(0x6F) Called IN number parameter", "(0x70) Call offering treatment indicators parameter",
"(0x71) Charged Party Identification", "(0x72) Conference Treatment Indicators",
"(0x73) Display Information Parameter", "(0x74) UID action indicators",
"(0x75) UID capability indicators", "(0x76) Udefined parameter",
"(0x77) Redirect Counter (rsvd for natl use)", "(0x78) Undefined Parameter",
"(0x79) Collect call request", "(0x7A) Undefined parameter",
"(0x7B) Undefined parameter", "(0x7C) Undefined parameter",
"(0x7D) Undefined parameter", "(0x7E) Undefined parameter",
"(0x7F) Undefined parameter", "(0x80) Undefined parameter",
"(0x81) Undefined parameter", "(0x82) Undefined parameter",
"(0x83) Undefined parameter", "(0x84) Undefined parameter",
"(0x85) Undefined parameter", "(0x86) Undefined parameter",
"(0x87) Undefined parameter", "(0x88) Undefined parameter",
"(0x89) Undefined parameter", "(0x8A) Undefined parameter",
"(0x8B) Undefined parameter", "(0x8C) Undefined parameter",
"(0x8D) Undefined parameter", "(0x8E) Undefined parameter",
"(0x8F) Undefined parameter", "(0x90) Undefined parameter",
"(0x91) Undefined parameter", "(0x92) Undefined parameter",
"(0x93) Undefined parameter", "(0x94) Undefined parameter",
"(0x95) Undefined parameter", "(0x96) Undefined parameter",
"(0x97) Undefined parameter", "(0x98) Undefined parameter",
"(0x99) Undefined parameter", "(0x9A) Undefined parameter",
"(0x9B) Undefined parameter", "(0x9C) Undefined parameter",
"(0x9D) Undefined parameter", "(0x9E) Undefined parameter",
"(0x9F) Undefined parameter", "(0xA0) Undefined parameter",
"(0xA1) Undefined parameter", "(0xA2) Undefined parameter",
"(0xA3) Undefined parameter", "(0xA4) Undefined parameter",
"(0xA5) Undefined parameter", "(0xA6) Undefined parameter",
"(0xA7) Undefined parameter", "(0xA8) Undefined parameter",
"(0xA9) Undefined parameter", "(0xAA) Undefined parameter",
"(0xAB) Undefined parameter", "(0xAC) Undefined parameter",
"(0xAD) Undefined parameter", "(0xAE) Undefined parameter",
"(0xAF) Undefined parameter", "(0xB0) Undefined parameter",
"(0xB1) Undefined parameter", "(0xB2) Undefined parameter",
"(0xB3) Undefined parameter", "(0xB4) Undefined parameter",
"(0xB5) Undefined parameter", "(0xB6) Undefined parameter",
"(0xB7) Undefined parameter", "(0xB8) Undefined parameter",
"(0xB9) Undefined parameter", "(0xBA) Undefined parameter",
"(0xBB) Undefined parameter", "(0xBC) Undefined parameter",
"(0xBD) Undefined parameter", "(0xBE) Undefined parameter",
"(0xBF) Undefined parameter", "(0xC0) Generic Number",
"(0xC1) Generic Digits", "(0xC2) Generic Refernce (reserved)",
"(0xC3) Undefined parameter", "(0xC4) Undefined parameter",
"(0xC5) Undefined parameter", "(0xC6) Undefined parameter",
"(0xC7) Undefined parameter", "(0xC8) Undefined parameter",
"(0xC9) Undefined parameter", "(0xCA) Undefined parameter",
"(0xCB) Undefined parameter", "(0xCC) Undefined Parameter",
"(0xCD) Undefined parameter",
"(0xCE) Undefined parameter", "(0xCF) Undefined parameter",
"(0xD0) Undefined parameter", "(0xD1) Undefined parameter",
"(0xD2) Undefined parameter", "(0xD3) Undefined parameter",
"(0xD4) Undefined parameter", "(0xD5) Undefined parameter",
"(0xD6) Undefined parameter", "(0xD7) Undefined parameter",
"(0xD8) Undefined parameter", "(0xD9) Undefined parameter",
"(0xDA) Undefined parameter", "(0xDB) Undefined parameter",
"(0xDC) Undefined parameter", "(0xDD) Undefined parameter",
"(0xDE) Undefined parameter", "(0xDF) Undefined parameter",
"(0xE0) Undefined parameter", "(0xE1) Undefined parameter",
"(0xE2) Undefined parameter", "(0xE3) Undefined parameter",
"(0xE4) Undefined parameter", "(0xE5) Undefined parameter",
"(0xE6) Undefined parameter", "(0xE7) Undefined parameter",
"(0xE8) Undefined parameter", "(0xE9) Undefined parameter",
"(0xEA) Undefined parameter", "(0xEB) Undefined parameter",
"(0xEC) Undefined parameter", "(0xED) Undefined parameter",
"(0xEE) Undefined parameter",
"(0xEF) Undefined parameter", "(0xF0) Undefined parameter",
"(0xF1) Undefined parameter", "(0xF2) Undefined parameter",
"(0xF3) Undefined parameter", "(0xF4) Undefined parameter",
"(0xF5) Undefined parameter", "(0xF6) Undefined parameter",
"(0xF7) Undefined parameter", "(0xF8) Undefined parameter",
"(0xF9) Undefined parameter", "(0xFA) Undefined parameter",
"(0xFB) Undefined parameter", "(0xFC) Undefined parameter",
"(0xFD) Undefined parameter", "(0xFE) Undefined parameter",
"(0xFF) MTP3 Header"};

#endif


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */



#endif /*  READ_ISUP_MSG_H */

