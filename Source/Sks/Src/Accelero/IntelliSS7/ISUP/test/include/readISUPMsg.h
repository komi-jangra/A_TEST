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
 *  ID: $Id: readISUPMsg.h,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:50:01  cvsadmin
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
 * LOG: Revision 3.1  2000/08/15 23:59:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/05/16 15:11:34  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.5  2000/01/11 22:33:51  labuser
 * LOG: Add read function for OutgoingTrunkGroupNumber parameter.
 * LOG:
 * LOG: Revision 2.4  2000/01/11 18:11:20  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.3  1999/12/30 15:54:12  labuser
 * LOG: Clean up...
 * LOG:
 * LOG: Revision 2.2  1999/12/27 19:01:48  cbascon
 * LOG: Added functions for reading and printing parameters for ACM, ANM, CPG,
 * LOG: REL, RLC, CFN, CON, SAM, UCIC, RSC for CCITT only.
 * LOG:
 * LOG: Revision 2.1  1999/12/21 19:24:12  cbascon
 * LOG: Added read functions for IAM parameters(CCITT).
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/11/24 19:28:23  cbascon
 * LOG: Change name from ReadChargeNum() to ReadChargeNumPar() for uniformity.
 * LOG:
 * LOG: Revision 1.1  1999/11/14 23:15:48  cbascon
 * LOG: Renamed freadfunc source files.
 * LOG:
 *
 ****************************************************************************/

#ifndef READ_ISUP_MSG_H
#define READ_ISUP_MSG_H


#include <stdio.h>

#include <itu/isup.h>
#include <ansi/isup.h>


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


#endif /* CCITT */



#endif /*  READ_ISUP_MSG_H */

