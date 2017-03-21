/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: printIsupMsg.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:32  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:35:58  hbalimid
 * LOG: Header for the PrintFunctions in printIsupMsg.c
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

int ISUP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event);


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* _PRINT_ISUP_MSG_H_ */


