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
 *  ID: $Id: printISUPMsg.h,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:07  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:02  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1.6.1  2004/01/05 09:55:46  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.1.4.1.2.1  2003/10/30 05:04:39  akumar
 * LOG: Modification wrt MTP managment msg.
 * LOG:
 * LOG: Revision 7.1.4.1  2003/06/18 09:10:26  tsanthosh
 * LOG: Added latest files.
 * LOG:
 * LOG: Revision 7.1.4.1  2003/05/07 11:10:03  ssingh
 * LOG: Conformation Indication related code removed. Not in Use.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.4  2002/08/01 16:01:46  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.3.2.2  2002/07/31 19:12:37  ssingh
 * LOG: Changes done to support ANSI95 related new params.
 * LOG:
 * LOG: Revision 1.3.2.1  2002/07/25 21:16:12  ssingh
 * LOG: Indication Handling in ISUP_ReceiveMsg.
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
 * LOG: Revision 1.3  2002/02/26 23:53:57  ssharma
 * LOG: Handle timer and error indications.
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
 * LOG: Revision 3.1  2000/08/16 00:11:13  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.4  2000/07/21 21:18:22  hxing
 * LOG: Add print routing label
 * LOG:
 * LOG: Revision 1.3  2000/07/17 20:17:22  hxing
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.2  2000/07/14 22:50:41  hxing
 * LOG: Add more print
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:35  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _PRINT_ISUP_MSG_H_
#define _PRINT_ISUP_MSG_H_


#include <its.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/* Main parameter print function */
int PrintISUPMsg(const ITS_ISUP_IE *ie, int ieCount);


/*
 * Parameters common to ANSI and CCITT
 */

void PrintMessageInPAMPar(const ITS_ISUP_IE *ie);

void PrintRoutingLabel(const ITS_ISUP_IE *ie);
void PrintTimeout(const ITS_ISUP_IE *ie);
void PrintError(const ITS_ISUP_IE *ie);
void PrintIndication(const ITS_ISUP_IE *ie);
void PrintMgmtIndication(const ITS_ISUP_IE *ie);

void PrintAccessTransportPar(const ITS_ISUP_IE *ie);
void PrintAutoCongestionLvlPar(const ITS_ISUP_IE *ie);
void PrintBackwardCallIndPar(const ITS_ISUP_IE *ie);
void PrintCalledPartyNumPar(const ITS_ISUP_IE *ie);
void PrintCallingPartyCategoryPar(const ITS_ISUP_IE *ie);
void PrintCallingPartyNumPar(const ITS_ISUP_IE *ie);
void PrintCallRefPar(const ITS_ISUP_IE *ie);
void PrintCauseIndPar(const ITS_ISUP_IE *ie);
void PrintCircuitGrpSupervisionMsgTypIndPar(const ITS_ISUP_IE *ie);
void PrintCircuitStateIndPar(const ITS_ISUP_IE *ie);
void PrintCircuitValRespIndPar(const ITS_ISUP_IE *ie);
void PrintConnectRequestPar(const ITS_ISUP_IE *ie);
void PrintContinuityIndPar(const ITS_ISUP_IE *ie);
void PrintEOPPar(const ITS_ISUP_IE *ie);
void PrintEventInfoPar(const ITS_ISUP_IE *ie);
void PrintForwCallIndPar(const ITS_ISUP_IE *ie);
void PrintGenericDigitsPar(const ITS_ISUP_IE *ie);
void PrintInfoIndPar(const ITS_ISUP_IE *ie);
void PrintInfoReqIndPar(const ITS_ISUP_IE *ie);
void PrintNatureOfConnectionIndPar(const ITS_ISUP_IE *ie);
void PrintOptBackwardCallIndPar(const ITS_ISUP_IE *ie);
void PrintOrigCalledNumPar(const ITS_ISUP_IE *ie);
void PrintRangeAndStatusPar(const ITS_ISUP_IE *ie);
void PrintRedirectingNumPar(const ITS_ISUP_IE *ie);
void PrintRedirectionInfoPar(const ITS_ISUP_IE *ie);
void PrintServiceActivationPar(const ITS_ISUP_IE *ie);
void PrintSuspendResumeIndPar(const ITS_ISUP_IE *ie);
void PrintTransitNetworkSelectionPar(const ITS_ISUP_IE *ie);
void PrintUserServiceInfoPar(const ITS_ISUP_IE *ie);

/* TODO: Add function
void PrintMTP3Header(const ITS_ISUP_IE *ie);
*/


/*
 * ANSI Parameters
 */
#ifdef ANSI

void PrintBusinessGrpPar(const ITS_ISUP_IE *ie);
void PrintCarrierIdPar(const ITS_ISUP_IE *ie);
void PrintCarrierSelectionInfoPar(const ITS_ISUP_IE *ie);
void PrintChargeNumPar(const ITS_ISUP_IE *ie);
void PrintCircuitGrpCharIndPar(const ITS_ISUP_IE *ie);
void PrintCircuitIdNamePar(const ITS_ISUP_IE *ie);
void PrintCircuitValRespIndPar(const ITS_ISUP_IE *ie);
void PrintCLLICodePar(const ITS_ISUP_IE *ie);
void PrintEgressServicePar(const ITS_ISUP_IE *ie);
void PrintGenericAddrPar(const ITS_ISUP_IE *ie);
void PrintHopCounterPar(const ITS_ISUP_IE *ie);
void PrintJurisdictionPar(const ITS_ISUP_IE *ie);
void PrintNetworkSpecificFacilityPar(const ITS_ISUP_IE *ie);
void PrintNetworkTransportPar(const ITS_ISUP_IE *ie);
void PrintNotificationIndPar(const ITS_ISUP_IE *ie);
void PrintOrigLineInfoPar(const ITS_ISUP_IE *ie);
void PrintOutgoingTrunkGrpNumPar(const ITS_ISUP_IE *ie);
void PrintServiceCodePar(const ITS_ISUP_IE *ie);
void PrintSpecialProcessReqPar(const ITS_ISUP_IE *ie);
void PrintTransactionReqPar(const ITS_ISUP_IE *ie);
void PrintUserServiceInfoPrimePar(const ITS_ISUP_IE *ie);

#if defined(ANSI_ISUP_95)

void PrintCircuitAssignMap(const ITS_ISUP_IE *ie);
void PrintGenericName(const ITS_ISUP_IE *ie);
void PrintHopCouner(const ITS_ISUP_IE *ie);
void PrintOperatorServInfo(const ITS_ISUP_IE *ie);
void PrintPrecedence(const ITS_ISUP_IE *ie);
void PrintRemoteOperations(const ITS_ISUP_IE *ie);
void PrintTransMediumUsed(const ITS_ISUP_IE *ie);
void PrintUserServInfoPrime(const ITS_ISUP_IE *ie);
void PrintUserToUserIndicators(const ITS_ISUP_IE *ie);
void PrintUserToUserInfo(const ITS_ISUP_IE *ie);

#endif

#endif  /* ANSI Parameters */


/*
 * CCITT Parameters
 */
#ifdef CCITT

void PrintAccessDeliveryInfoPar(const ITS_ISUP_IE *ie);
void PrintCallDiversionInfoPar(const ITS_ISUP_IE *ie);
void PrintCallHistoryInfoPar(const ITS_ISUP_IE *ie);
void PrintClosedUserGrpIntrlckCodePar(const ITS_ISUP_IE *ie);
void PrintConnectedNumPar(const ITS_ISUP_IE *ie);
void PrintEchoControlInfoPar(const ITS_ISUP_IE *ie);
void PrintFacilityIndPar(const ITS_ISUP_IE *ie);
void PrintGenericNotificationIndPar(const ITS_ISUP_IE *ie);
void PrintGenericNumberPar(const ITS_ISUP_IE *ie);
void PrintGenericReferencPar(const ITS_ISUP_IE *ie);
void PrintLocationNumberPar(const ITS_ISUP_IE *ie);
void PrintMCIDRequestIndPar(const ITS_ISUP_IE *ie);
void PrintMCIDResponseIndPar(const ITS_ISUP_IE *ie);
void PrintMLPPPrecedencePar(const ITS_ISUP_IE *ie);
void PrintMsgCompatibiltyInfoPar(const ITS_ISUP_IE *ie);
void PrintNetworkSpecificFacilityPar(const ITS_ISUP_IE *ie);
void PrintOptForwardCallIndPar(const ITS_ISUP_IE *ie);
void PrintOrigISCPointCodePar(const ITS_ISUP_IE *ie);
void PrintParamCompInfoPar(const ITS_ISUP_IE *ie);
void PrintPropDelayCounterPar(const ITS_ISUP_IE *ie);
void PrintRedirectionNumPar(const ITS_ISUP_IE *ie);
void PrintRedirectionNumRestrictPar(const ITS_ISUP_IE *ie);
void PrintRemoteOperationsPar(const ITS_ISUP_IE *ie);
void PrintSignallingPointCodePar(const ITS_ISUP_IE *ie);
void PrintSubsequentNumPar(const ITS_ISUP_IE *ie);
void PrintTXMediumRequirementPar(const ITS_ISUP_IE *ie);
void PrintTXMediumRequirementPrimePar(const ITS_ISUP_IE *ie);
void PrintTXMediumUsedPar(const ITS_ISUP_IE *ie);
void PrintUserServiceInfoPrimePar(const ITS_ISUP_IE *ie);
void PrintUserTeleserviceInfoPar(const ITS_ISUP_IE *ie);
void PrintUserToUserIndPar(const ITS_ISUP_IE *ie);
void PrintUserToUserInfoPar(const ITS_ISUP_IE *ie);

#endif  /* CCITT Parameters */

#if defined(CCITT) && defined(ITU_ISUP_97)

void PrintBackwardGVNSPar (const ITS_ISUP_IE *ie);
void PrintCCSSPar (const ITS_ISUP_IE *ie);
void PrintCallTransferNumberPar (const ITS_ISUP_IE *ie);
void PrintCallTransferReferencePar (const ITS_ISUP_IE *ie);
void PrintForwardGVNSPar (const ITS_ISUP_IE *ie);
void PrintLoopPreventionIndPar (const ITS_ISUP_IE *ie);
void PrintNetworkManagementCtrlsPar (const ITS_ISUP_IE *ie);
void PrintCircuitAssignmentMapPar (const ITS_ISUP_IE *ie);
void PrintCorrelationIdPar (const ITS_ISUP_IE *ie);
void PrintSCFIdPar (const ITS_ISUP_IE *ie);
void PrintCallDiversionTreatmentIndPar (const ITS_ISUP_IE *ie);
void PrintCalledINNumberPar (const ITS_ISUP_IE *ie);
void PrintCallOfferingTreatmentIndPar (const ITS_ISUP_IE *ie);
void PrintChargedPartyIdentificationPar (const ITS_ISUP_IE *ie);
void PrintConferenceTreatmentIndPar (const ITS_ISUP_IE *ie);
void PrintDisplayInformationPar (const ITS_ISUP_IE *ie);
void PrintUIDActionIndPar (const ITS_ISUP_IE *ie);
void PrintUIDCapabilityIndPar (const ITS_ISUP_IE *ie);
void PrintHopCounterPar (const ITS_ISUP_IE *ie);
void PrintCollectCallRequestPar (const ITS_ISUP_IE *ie);

#endif

int ISUP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event);


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* _PRINT_ISUP_MSG_H_ */
