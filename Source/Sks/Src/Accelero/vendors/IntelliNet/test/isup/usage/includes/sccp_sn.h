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
 *     FILE: sccp.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: sccp_sn.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.6  2002/01/02 20:26:36  mmiers
 * LOG: Add a short name for SCMG
 * LOG:
 * LOG: Revision 5.5  2002/01/02 19:55:46  mmiers
 * LOG: Convert to long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_SCCP_SN_H_
#define _ITS_SCCP_SN_H_

#ident "$Id: sccp_sn.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

/*
 * shortcut names
 */
#if defined(CCITT)

#define SCCP_CPA_HAS_PC     SCCP_CPA_HAS_PC_CCITT
#define SCCP_CPA_HAS_SSN    SCCP_CPA_HAS_SSN_CCITT

#define SCCP_CPA_GTTI_TRANS SCCP_CPA_GTTI_TRANS_CCITT
#define SCCP_CPA_GTTI_TNE   SCCP_CPA_GTTI_TNE_CCITT

#define SCCP_CPA_ROUTE_INT  SCCP_CPA_ROUTE_INT_CCITT
#define SCCP_CPA_ROUTE_NAT  SCCP_CPA_ROUTE_NAT_CCITT

#elif defined(ANSI)

#define SCCP_CPA_HAS_PC     SCCP_CPA_HAS_PC_ANSI
#define SCCP_CPA_HAS_SSN    SCCP_CPA_HAS_SSN_ANSI

#define SCCP_CPA_GTTI_TRANS SCCP_CPA_GTTI_TRANS_ANSI
#define SCCP_CPA_GTTI_TNE   SCCP_CPA_GTTI_TNE_ANSI

#define SCCP_CPA_ROUTE_INT  SCCP_CPA_ROUTE_INT_ANSI
#define SCCP_CPA_ROUTE_NAT  SCCP_CPA_ROUTE_NAT_ANSI

#endif

#if defined(CCITT)

#define SCCP_SCMG                   SCCP_SCMG_CCITT

#define SCCP_EncodeAddr             SCCP_EncodeAddr_CCITT
#define SCCP_DecodeAddr             SCCP_DecodeAddr_CCITT
#define SCCP_GetNextLocalRef        SCCP_GetNextLocalRef_CCITT
#define SCCP_SendUserInService      SCCP_SendUserInService_CCITT
#define SCCP_SendUserOutOfService   SCCP_SendUserOutOfService_CCITT
#define SCCP_SendSetCongestion      SCCP_SendSetCongestion_CCITT
#define SCCP_ComputeMSize           SCCP_ComputeMSize_CCITT
#define SCCP_GetDescriptor          SCCP_GetDescriptor_CCITT

#define SCCP_SendConnectionRequest \
    SCCP_SendConnectionRequest_CCITT
#define SCCP_ReceiveConnectionRequest \
    SCCP_ReceiveConnectionRequest_CCITT
#define SCCP_SendConnectionConfirm \
    SCCP_SendConnectionConfirm_CCITT
#define SCCP_ReceiveConnectionConfirm \
    SCCP_ReceiveConnectionConfirm_CCITT
#define SCCP_SendConnectionRefused \
    SCCP_SendConnectionRefused_CCITT
#define SCCP_ReceiveConnectionRefused \
    SCCP_ReceiveConnectionRefused_CCITT
#define SCCP_SendReleased \
    SCCP_SendReleased_CCITT
#define SCCP_ReceiveReleased \
    SCCP_ReceiveReleased_CCITT
#define SCCP_SendReleaseComplete \
    SCCP_SendReleaseComplete_CCITT
#define SCCP_ReceiveReleaseComplete \
    SCCP_ReceiveReleaseComplete_CCITT
#define SCCP_SendDataForm1 \
    SCCP_SendDataForm1_CCITT
#define SCCP_ReceiveDataForm1 \
    SCCP_ReceiveDataForm1_CCITT
#define SCCP_SendDataForm2 \
    SCCP_SendDataForm2_CCITT
#define SCCP_ReceiveDataForm2 \
    SCCP_ReceiveDataForm2_CCITT
#define SCCP_SendAcknowledgement \
    SCCP_SendAcknowledgement_CCITT
#define SCCP_ReceiveAcknowledgement \
    SCCP_ReceiveAcknowledgement_CCITT
#define SCCP_SendUnitData \
    SCCP_SendUnitData_CCITT
#define SCCP_ReceiveUnitData \
    SCCP_ReceiveUnitData_CCITT
#define SCCP_SendExtendedUnitData \
    SCCP_SendExtendedUnitData_CCITT
#define SCCP_ReceiveExtendedUnitData \
    SCCP_ReceiveExtendedUnitData_CCITT
#define SCCP_SendUnitDataService \
    SCCP_SendUnitDataService_CCITT
#define SCCP_ReceiveUnitDataService \
    SCCP_ReceiveUnitDataService_CCITT
#define SCCP_SendExtendedUnitDataService \
    SCCP_SendExtendedUnitDataService_CCITT
#define SCCP_ReceiveExtendedUnitDataService \
    SCCP_ReceiveExtendedUnitDataService_CCITT
#define SCCP_SendExpeditedData \
    SCCP_SendExpeditedData_CCITT
#define SCCP_ReceiveExpeditedData \
    SCCP_ReceiveExpeditedData_CCITT
#define SCCP_SendExpeditedDataAck \
    SCCP_SendExpeditedDataAck_CCITT
#define SCCP_ReceiveExpeditedDataAck \
    SCCP_ReceiveExpeditedDataAck_CCITT
#define SCCP_SendResetRequest \
    SCCP_SendResetRequest_CCITT
#define SCCP_ReceiveResetRequest \
    SCCP_ReceiveResetRequest_CCITT
#define SCCP_SendResetConfirmation \
    SCCP_SendResetConfirmation_CCITT
#define SCCP_ReceiveResetConfirmation \
    SCCP_ReceiveResetConfirmation_CCITT
#define SCCP_SendError \
    SCCP_SendError_CCITT
#define SCCP_ReceiveError \
    SCCP_ReceiveError_CCITT
#define SCCP_SendInactivityTest \
    SCCP_SendInactivityTest_CCITT
#define SCCP_ReceiveInactivityTest \
    SCCP_ReceiveInactivityTest_CCITT
#define SCCP_SendLongUnitData \
    SCCP_SendLongUnitData_CCITT
#define SCCP_ReceiveLongUnitData \
    SCCP_ReceiveLongUnitData_CCITT
#define SCCP_SendLongUnitDataService \
    SCCP_SendLongUnitDataService_CCITT
#define SCCP_ReceiveLongUnitDataService \
    SCCP_ReceiveLongUnitDataService_CCITT

#define SCCP_CR_Desc        SCCP_CR_Desc_CCITT
#define SCCP_CC_Desc        SCCP_CC_Desc_CCITT
#define SCCP_CREF_Desc      SCCP_CREF_Desc_CCITT
#define SCCP_RLSD_Desc      SCCP_RLSD_Desc_CCITT
#define SCCP_RLC_Desc       SCCP_RLC_Desc_CCITT
#define SCCP_DT1_Desc       SCCP_DT1_Desc_CCITT
#define SCCP_DT2_Desc       SCCP_DT2_Desc_CCITT
#define SCCP_AK_Desc        SCCP_AK_Desc_CCITT
#define SCCP_UDT_Desc       SCCP_UDT_Desc_CCITT
#define SCCP_XUDT_Desc      SCCP_XUDT_Desc_CCITT
#define SCCP_UDTS_Desc      SCCP_UDTS_Desc_CCITT
#define SCCP_XUDTS_Desc     SCCP_XUDTS_Desc_CCITT
#define SCCP_ED_Desc        SCCP_ED_Desc_CCITT
#define SCCP_EA_Desc        SCCP_EA_Desc_CCITT
#define SCCP_RSR_Desc       SCCP_RSR_Desc_CCITT
#define SCCP_RSC_Desc       SCCP_RSC_Desc_CCITT
#define SCCP_ERR_Desc       SCCP_ERR_Desc_CCITT
#define SCCP_IT_Desc        SCCP_IT_Desc_CCITT
#define SCCP_LUDT_Desc      SCCP_LUDT_Desc_CCITT
#define SCCP_LUDTS_Desc     SCCP_LUDTS_Desc_CCITT

#define SCCP_ManagementCallbacks    SCCP_CCITT_ManagementCallbacks
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#define SCCP_SSNRoutingCallbacks    SCCP_CCITT_SSNRoutingCallbacks

/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_SCCP            ITS_SCCP_CCITT
#define ITS_SCCP_SRC        ITS_SCCP_CCITT_SRC

#elif defined(ANSI)

#define SCCP_SCMG                   SCCP_SCMG_ANSI

#define SCCP_EncodeAddr             SCCP_EncodeAddr_ANSI
#define SCCP_DecodeAddr             SCCP_DecodeAddr_ANSI
#define SCCP_GetNextLocalRef        SCCP_GetNextLocalRef_ANSI
#define SCCP_SendUserInService      SCCP_SendUserInService_ANSI
#define SCCP_SendUserOutOfService   SCCP_SendUserOutOfService_ANSI
#define SCCP_SendSetCongestion      SCCP_SendSetCongestion_ANSI
#define SCCP_ComputeMSize           SCCP_ComputeMSize_ANSI
#define SCCP_GetDescriptor          SCCP_GetDescriptor_ANSI

#define SCCP_SendConnectionRequest \
    SCCP_SendConnectionRequest_ANSI
#define SCCP_ReceiveConnectionRequest \
    SCCP_ReceiveConnectionRequest_ANSI
#define SCCP_SendConnectionConfirm \
    SCCP_SendConnectionConfirm_ANSI
#define SCCP_ReceiveConnectionConfirm \
    SCCP_ReceiveConnectionConfirm_ANSI
#define SCCP_SendConnectionRefused \
    SCCP_SendConnectionRefused_ANSI
#define SCCP_ReceiveConnectionRefused \
    SCCP_ReceiveConnectionRefused_ANSI
#define SCCP_SendReleased \
    SCCP_SendReleased_ANSI
#define SCCP_ReceiveReleased \
    SCCP_ReceiveReleased_ANSI
#define SCCP_SendReleaseComplete \
    SCCP_SendReleaseComplete_ANSI
#define SCCP_ReceiveReleaseComplete \
    SCCP_ReceiveReleaseComplete_ANSI
#define SCCP_SendDataForm1 \
    SCCP_SendDataForm1_ANSI
#define SCCP_ReceiveDataForm1 \
    SCCP_ReceiveDataForm1_ANSI
#define SCCP_SendDataForm2 \
    SCCP_SendDataForm2_ANSI
#define SCCP_ReceiveDataForm2 \
    SCCP_ReceiveDataForm2_ANSI
#define SCCP_SendAcknowledgement \
    SCCP_SendAcknowledgement_ANSI
#define SCCP_ReceiveAcknowledgement \
    SCCP_ReceiveAcknowledgement_ANSI
#define SCCP_SendUnitData \
    SCCP_SendUnitData_ANSI
#define SCCP_ReceiveUnitData \
    SCCP_ReceiveUnitData_ANSI
#define SCCP_SendExtendedUnitData \
    SCCP_SendExtendedUnitData_ANSI
#define SCCP_ReceiveExtendedUnitData \
    SCCP_ReceiveExtendedUnitData_ANSI
#define SCCP_SendUnitDataService \
    SCCP_SendUnitDataService_ANSI
#define SCCP_ReceiveUnitDataService \
    SCCP_ReceiveUnitDataService_ANSI
#define SCCP_SendExtendedUnitDataService \
    SCCP_SendExtendedUnitDataService_ANSI
#define SCCP_ReceiveExtendedUnitDataService \
    SCCP_ReceiveExtendedUnitDataService_ANSI
#define SCCP_SendExpeditedData \
    SCCP_SendExpeditedData_ANSI
#define SCCP_ReceiveExpeditedData \
    SCCP_ReceiveExpeditedData_ANSI
#define SCCP_SendExpeditedDataAck \
    SCCP_SendExpeditedDataAck_ANSI
#define SCCP_ReceiveExpeditedDataAck \
    SCCP_ReceiveExpeditedDataAck_ANSI
#define SCCP_SendResetRequest \
    SCCP_SendResetRequest_ANSI
#define SCCP_ReceiveResetRequest \
    SCCP_ReceiveResetRequest_ANSI
#define SCCP_SendResetConfirmation \
    SCCP_SendResetConfirmation_ANSI
#define SCCP_ReceiveResetConfirmation \
    SCCP_ReceiveResetConfirmation_ANSI
#define SCCP_SendError \
    SCCP_SendError_ANSI
#define SCCP_ReceiveError \
    SCCP_ReceiveError_ANSI
#define SCCP_SendInactivityTest \
    SCCP_SendInactivityTest_ANSI
#define SCCP_ReceiveInactivityTest \
    SCCP_ReceiveInactivityTest_ANSI
#define SCCP_SendLongUnitData \
    SCCP_SendLongUnitData_ANSI
#define SCCP_ReceiveLongUnitData \
    SCCP_ReceiveLongUnitData_ANSI
#define SCCP_SendLongUnitDataService \
    SCCP_SendLongUnitDataService_ANSI
#define SCCP_ReceiveLongUnitDataService \
    SCCP_ReceiveLongUnitDataService_ANSI

#define SCCP_CR_Desc        SCCP_CR_Desc_ANSI
#define SCCP_CC_Desc        SCCP_CC_Desc_ANSI
#define SCCP_CREF_Desc      SCCP_CREF_Desc_ANSI
#define SCCP_RLSD_Desc      SCCP_RLSD_Desc_ANSI
#define SCCP_RLC_Desc       SCCP_RLC_Desc_ANSI
#define SCCP_DT1_Desc       SCCP_DT1_Desc_ANSI
#define SCCP_DT2_Desc       SCCP_DT2_Desc_ANSI
#define SCCP_AK_Desc        SCCP_AK_Desc_ANSI
#define SCCP_UDT_Desc       SCCP_UDT_Desc_ANSI
#define SCCP_XUDT_Desc      SCCP_XUDT_Desc_ANSI
#define SCCP_UDTS_Desc      SCCP_UDTS_Desc_ANSI
#define SCCP_XUDTS_Desc     SCCP_XUDTS_Desc_ANSI
#define SCCP_ED_Desc        SCCP_ED_Desc_ANSI
#define SCCP_EA_Desc        SCCP_EA_Desc_ANSI
#define SCCP_RSR_Desc       SCCP_RSR_Desc_ANSI
#define SCCP_RSC_Desc       SCCP_RSC_Desc_ANSI
#define SCCP_ERR_Desc       SCCP_ERR_Desc_ANSI
#define SCCP_IT_Desc        SCCP_IT_Desc_ANSI
#define SCCP_LUDT_Desc      SCCP_LUDT_Desc_ANSI
#define SCCP_LUDTS_Desc     SCCP_LUDTS_Desc_ANSI


#define SCCP_ManagementCallbacks    SCCP_ANSI_ManagementCallbacks
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#define SCCP_SSNRoutingCallbacks    SCCP_ANSI_SSNRoutingCallbacks

#define ITS_SCCP            ITS_SCCP_ANSI
#define ITS_SCCP_SRC        ITS_SCCP_ANSI_SRC

#endif

#if defined(CCITT)

#define SCCP_Encode             SCCP_Encode_CCITT
#define SCCP_Decode             SCCP_Decode_CCITT
#define SCCP_EncodeMTP3         SCCP_EncodeMTP3_CCITT
#define SCCP_DecodeMTP3         SCCP_DecodeMTP3_CCITT
#define SCCP_SendEvent          SCCP_SendEvent_CCITT
#define SCCP_ReceiveEvent       SCCP_ReceiveEvent_CCITT
#define SCCP_IsSSNEquipped      SCCP_IsSSNEquipped_CCITT
#define SCCP_IsSSNAllowed       SCCP_IsSSNAllowed_CCITT
#define SCCP_IsSSNCongested     SCCP_IsSSNCongested_CCITT
#define SCCP_GetNextLocalRef    SCCP_GetNextLocalRef_CCITT

#elif defined(ANSI)

#define SCCP_Encode             SCCP_Encode_ANSI
#define SCCP_Decode             SCCP_Decode_ANSI
#define SCCP_EncodeMTP3         SCCP_EncodeMTP3_ANSI
#define SCCP_DecodeMTP3         SCCP_DecodeMTP3_ANSI
#define SCCP_SendEvent          SCCP_SendEvent_ANSI
#define SCCP_ReceiveEvent       SCCP_ReceiveEvent_ANSI
#define SCCP_IsSSNEquipped      SCCP_IsSSNEquipped_ANSI
#define SCCP_IsSSNAllowed       SCCP_IsSSNAllowed_ANSI
#define SCCP_IsSSNCongested     SCCP_IsSSNCongested_ANSI
#define SCCP_GetNextLocalRef    SCCP_GetNextLocalRef_ANSI

#endif

#endif /* _ITS_SCCP_CMN_H_ */

