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
 * ID:$Id: ISUP_PrintMsg.h,v 1.1.1.1 2007-10-08 11:12:23 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:19  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:18  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 1.1  2003/02/19 15:35:50  vnitin
 * LOG:Add functional tester for Tandem
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
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
void PrintConformation(const ITS_ISUP_IE *ie);

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
