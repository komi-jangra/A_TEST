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
 * LOG: Revision 9.1  2005/03/23 12:52:04  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:37  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:37  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:06  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.1  2000/09/08 14:35:59  labuser
 * LOG: cbascon: add header files in include directory
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:33  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/07/06 18:37:16  labuser
 * LOG: Move print function declaration for UserTeleserviceInformation to
 * LOG: CCITT instead of ANSI ifdef
 * LOG:
 * LOG: Revision 2.5  2000/05/16 15:11:33  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.4  2000/01/11 18:11:19  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.3  1999/12/30 15:54:12  labuser
 * LOG: Clean up...
 * LOG:
 * LOG: Revision 2.2  1999/12/21 19:25:09  cbascon
 * LOG: Added print functions for IAM parameters(CCITT)
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:03  cbascon
 * LOG: Encoded and sent the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
 * LOG:
 * LOG: Received and decoded the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/11/24 19:26:02  cbascon
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  1999/11/14 23:14:25  cbascon
 * LOG: Added print functions for parameters.
 * LOG:
 *
 ****************************************************************************/

#ifndef _PRINT_ISUP_MSG_H_
#define _PRINT_ISUP_MSG_H_


#include <its.h>
#include <itu/isup.h>
#include <ansi/isup.h>

/* Main parameter print function */
int PrintISUPMsg(const ITS_ISUP_IE *ie, int ieCount);


/*
 * Parameters common to ANSI and CCITT
 */

void PrintMessageInPAMPar(const ITS_ISUP_IE *ie);

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

/* TODO: Need to add 
void PrintSupervisionMsgTypePar(const ITS_ISUP_IE *ie);
 */

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

#endif /* _PRINT_ISUP_MSG_H_ */

