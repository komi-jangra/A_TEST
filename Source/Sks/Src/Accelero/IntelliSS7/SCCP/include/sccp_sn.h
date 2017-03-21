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
 *  ID: $Id: sccp_sn.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:50  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.1  2005/09/21 12:58:42  adutta
 * LOG: Resgistering api with SCCP
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.2.6.2  2005/01/31 11:28:29  snagesh
 * LOG: SCCP OSS APIs short names added
 * LOG:
 * LOG: Revision 7.1.14.2.6.1  2004/12/16 02:22:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.14.2  2004/09/21 06:56:54  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1.14.1  2004/01/27 05:56:51  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/16 22:09:57  mmiers
 * LOG: Add the China variant
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:51:01  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
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

#ident "$Id: sccp_sn.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $"

/*
 * shortcut names
 */
#if defined(CCITT)

#define SCCP_CPA_HAS_PC     SCCP_CPA_HAS_PC_CCITT
#define SCCP_CPA_HAS_SSN    SCCP_CPA_HAS_SSN_CCITT

#define SCCP_CPA_GTTI_TRANS SCCP_CPA_GTTI_TRANS_CCITT
#define SCCP_CPA_GTTI_TNE   SCCP_CPA_GTTI_TNE_CCITT

#elif defined(ANSI)

#define SCCP_CPA_HAS_PC     SCCP_CPA_HAS_PC_ANSI
#define SCCP_CPA_HAS_SSN    SCCP_CPA_HAS_SSN_ANSI

#define SCCP_CPA_GTTI_TRANS SCCP_CPA_GTTI_TRANS_ANSI
#define SCCP_CPA_GTTI_TNE   SCCP_CPA_GTTI_TNE_ANSI

#elif defined(PRC)

#define SCCP_CPA_HAS_PC     SCCP_CPA_HAS_PC_PRC
#define SCCP_CPA_HAS_SSN    SCCP_CPA_HAS_SSN_PRC

#define SCCP_CPA_GTTI_TRANS SCCP_CPA_GTTI_TRANS_PRC
#define SCCP_CPA_GTTI_TNE   SCCP_CPA_GTTI_TNE_PRC

#elif defined(TTC)

#define SCCP_CPA_HAS_PC     SCCP_CPA_HAS_PC_TTC
#define SCCP_CPA_HAS_SSN    SCCP_CPA_HAS_SSN_TTC

#define SCCP_CPA_GTTI_TRANS SCCP_CPA_GTTI_TRANS_TTC
#define SCCP_CPA_GTTI_TNE   SCCP_CPA_GTTI_TNE_TTC

#endif

#if defined(CCITT)

#define SCCP_SCMG                   SCCP_SCMG_CCITT

#define SCCP_EnableUserPart         SCCP_EnableUserPart_CCITT
#define SCCP_UserPartOwner          SCCP_UserPartOwner_CCITT
#define SCCP_EncodeAddr             SCCP_EncodeAddr_CCITT
#define SCCP_DecodeAddr             SCCP_DecodeAddr_CCITT
#define SCCP_GetNextLocalRef        SCCP_GetNextLocalRef_CCITT
#define SCCP_GetSharedLocalRef      SCCP_GetSharedLocalRef_CCITT
#define SCCP_SendUserInService      SCCP_SendUserInService_CCITT
#define SCCP_SendUserOutOfService   SCCP_SendUserOutOfService_CCITT
#define SCCP_SendSetCongestion      SCCP_SendSetCongestion_CCITT
#define SCCP_ComputeMSize           SCCP_ComputeMSize_CCITT
#define SCCP_GetDescriptor          SCCP_GetDescriptor_CCITT
#define SCCP_PPrint                 SCCP_PPrint_CCITT

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
#define SCCP_EnableUserPart         SCCP_EnableUserPart_ANSI
#define SCCP_UserPartOwner          SCCP_UserPartOwner_ANSI

#define SCCP_EncodeAddr             SCCP_EncodeAddr_ANSI
#define SCCP_DecodeAddr             SCCP_DecodeAddr_ANSI
#define SCCP_GetNextLocalRef        SCCP_GetNextLocalRef_ANSI
#define SCCP_GetSharedLocalRef      SCCP_GetSharedLocalRef_ANSI
#define SCCP_SendUserInService      SCCP_SendUserInService_ANSI
#define SCCP_SendUserOutOfService   SCCP_SendUserOutOfService_ANSI
#define SCCP_SendSetCongestion      SCCP_SendSetCongestion_ANSI
#define SCCP_ComputeMSize           SCCP_ComputeMSize_ANSI
#define SCCP_GetDescriptor          SCCP_GetDescriptor_ANSI
#define SCCP_PPrint                 SCCP_PPrint_ANSI

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

#elif defined(PRC)

#define SCCP_SCMG                   SCCP_SCMG_PRC

#define SCCP_EncodeAddr             SCCP_EncodeAddr_PRC
#define SCCP_DecodeAddr             SCCP_DecodeAddr_PRC
#define SCCP_GetNextLocalRef        SCCP_GetNextLocalRef_PRC
#define SCCP_GetSharedLocalRef      SCCP_GetSharedLocalRef_PRC
#define SCCP_SendUserInService      SCCP_SendUserInService_PRC
#define SCCP_SendUserOutOfService   SCCP_SendUserOutOfService_PRC
#define SCCP_SendSetCongestion      SCCP_SendSetCongestion_PRC
#define SCCP_ComputeMSize           SCCP_ComputeMSize_PRC
#define SCCP_GetDescriptor          SCCP_GetDescriptor_PRC
#define SCCP_PPrint                 SCCP_PPrint_PRC

#define SCCP_SendConnectionRequest \
    SCCP_SendConnectionRequest_PRC
#define SCCP_ReceiveConnectionRequest \
    SCCP_ReceiveConnectionRequest_PRC
#define SCCP_SendConnectionConfirm \
    SCCP_SendConnectionConfirm_PRC
#define SCCP_ReceiveConnectionConfirm \
    SCCP_ReceiveConnectionConfirm_PRC
#define SCCP_SendConnectionRefused \
    SCCP_SendConnectionRefused_PRC
#define SCCP_ReceiveConnectionRefused \
    SCCP_ReceiveConnectionRefused_PRC
#define SCCP_SendReleased \
    SCCP_SendReleased_PRC
#define SCCP_ReceiveReleased \
    SCCP_ReceiveReleased_PRC
#define SCCP_SendReleaseComplete \
    SCCP_SendReleaseComplete_PRC
#define SCCP_ReceiveReleaseComplete \
    SCCP_ReceiveReleaseComplete_PRC
#define SCCP_SendDataForm1 \
    SCCP_SendDataForm1_PRC
#define SCCP_ReceiveDataForm1 \
    SCCP_ReceiveDataForm1_PRC
#define SCCP_SendDataForm2 \
    SCCP_SendDataForm2_PRC
#define SCCP_ReceiveDataForm2 \
    SCCP_ReceiveDataForm2_PRC
#define SCCP_SendAcknowledgement \
    SCCP_SendAcknowledgement_PRC
#define SCCP_ReceiveAcknowledgement \
    SCCP_ReceiveAcknowledgement_PRC
#define SCCP_SendUnitData \
    SCCP_SendUnitData_PRC
#define SCCP_ReceiveUnitData \
    SCCP_ReceiveUnitData_PRC
#define SCCP_SendExtendedUnitData \
    SCCP_SendExtendedUnitData_PRC
#define SCCP_ReceiveExtendedUnitData \
    SCCP_ReceiveExtendedUnitData_PRC
#define SCCP_SendUnitDataService \
    SCCP_SendUnitDataService_PRC
#define SCCP_ReceiveUnitDataService \
    SCCP_ReceiveUnitDataService_PRC
#define SCCP_SendExtendedUnitDataService \
    SCCP_SendExtendedUnitDataService_PRC
#define SCCP_ReceiveExtendedUnitDataService \
    SCCP_ReceiveExtendedUnitDataService_PRC
#define SCCP_SendExpeditedData \
    SCCP_SendExpeditedData_PRC
#define SCCP_ReceiveExpeditedData \
    SCCP_ReceiveExpeditedData_PRC
#define SCCP_SendExpeditedDataAck \
    SCCP_SendExpeditedDataAck_PRC
#define SCCP_ReceiveExpeditedDataAck \
    SCCP_ReceiveExpeditedDataAck_PRC
#define SCCP_SendResetRequest \
    SCCP_SendResetRequest_PRC
#define SCCP_ReceiveResetRequest \
    SCCP_ReceiveResetRequest_PRC
#define SCCP_SendResetConfirmation \
    SCCP_SendResetConfirmation_PRC
#define SCCP_ReceiveResetConfirmation \
    SCCP_ReceiveResetConfirmation_PRC
#define SCCP_SendError \
    SCCP_SendError_PRC
#define SCCP_ReceiveError \
    SCCP_ReceiveError_PRC
#define SCCP_SendInactivityTest \
    SCCP_SendInactivityTest_PRC
#define SCCP_ReceiveInactivityTest \
    SCCP_ReceiveInactivityTest_PRC
#define SCCP_SendLongUnitData \
    SCCP_SendLongUnitData_PRC
#define SCCP_ReceiveLongUnitData \
    SCCP_ReceiveLongUnitData_PRC
#define SCCP_SendLongUnitDataService \
    SCCP_SendLongUnitDataService_PRC
#define SCCP_ReceiveLongUnitDataService \
    SCCP_ReceiveLongUnitDataService_PRC

#define SCCP_CR_Desc        SCCP_CR_Desc_PRC
#define SCCP_CC_Desc        SCCP_CC_Desc_PRC
#define SCCP_CREF_Desc      SCCP_CREF_Desc_PRC
#define SCCP_RLSD_Desc      SCCP_RLSD_Desc_PRC
#define SCCP_RLC_Desc       SCCP_RLC_Desc_PRC
#define SCCP_DT1_Desc       SCCP_DT1_Desc_PRC
#define SCCP_DT2_Desc       SCCP_DT2_Desc_PRC
#define SCCP_AK_Desc        SCCP_AK_Desc_PRC
#define SCCP_UDT_Desc       SCCP_UDT_Desc_PRC
#define SCCP_XUDT_Desc      SCCP_XUDT_Desc_PRC
#define SCCP_UDTS_Desc      SCCP_UDTS_Desc_PRC
#define SCCP_XUDTS_Desc     SCCP_XUDTS_Desc_PRC
#define SCCP_ED_Desc        SCCP_ED_Desc_PRC
#define SCCP_EA_Desc        SCCP_EA_Desc_PRC
#define SCCP_RSR_Desc       SCCP_RSR_Desc_PRC
#define SCCP_RSC_Desc       SCCP_RSC_Desc_PRC
#define SCCP_ERR_Desc       SCCP_ERR_Desc_PRC
#define SCCP_IT_Desc        SCCP_IT_Desc_PRC
#define SCCP_LUDT_Desc      SCCP_LUDT_Desc_PRC
#define SCCP_LUDTS_Desc     SCCP_LUDTS_Desc_PRC


#define SCCP_ManagementCallbacks    SCCP_PRC_ManagementCallbacks
#define SCCP_GlobalTitleTranslator  SCCP_PRC_GlobalTitleTranslator
#define SCCP_SSNRoutingCallbacks    SCCP_PRC_SSNRoutingCallbacks

#define ITS_SCCP            ITS_SCCP_PRC
#define ITS_SCCP_SRC        ITS_SCCP_PRC_SRC

#elif defined(TTC)

#define SCCP_SCMG                   SCCP_SCMG_TTC

#define SCCP_EncodeAddr             SCCP_EncodeAddr_TTC
#define SCCP_DecodeAddr             SCCP_DecodeAddr_TTC
#define SCCP_GetNextLocalRef        SCCP_GetNextLocalRef_TTC
#define SCCP_GetSharedLocalRef      SCCP_GetSharedLocalRef_TTC
#define SCCP_SendUserInService      SCCP_SendUserInService_TTC
#define SCCP_SendUserOutOfService   SCCP_SendUserOutOfService_TTC
#define SCCP_SendSetCongestion      SCCP_SendSetCongestion_TTC
#define SCCP_ComputeMSize           SCCP_ComputeMSize_TTC
#define SCCP_GetDescriptor          SCCP_GetDescriptor_TTC

#define SCCP_SendConnectionRequest \
    SCCP_SendConnectionRequest_TTC
#define SCCP_ReceiveConnectionRequest \
    SCCP_ReceiveConnectionRequest_TTC
#define SCCP_SendConnectionConfirm \
    SCCP_SendConnectionConfirm_TTC
#define SCCP_ReceiveConnectionConfirm \
    SCCP_ReceiveConnectionConfirm_TTC
#define SCCP_SendConnectionRefused \
    SCCP_SendConnectionRefused_TTC
#define SCCP_ReceiveConnectionRefused \
    SCCP_ReceiveConnectionRefused_TTC
#define SCCP_SendReleased \
    SCCP_SendReleased_TTC
#define SCCP_ReceiveReleased \
    SCCP_ReceiveReleased_TTC
#define SCCP_SendReleaseComplete \
    SCCP_SendReleaseComplete_TTC
#define SCCP_ReceiveReleaseComplete \
    SCCP_ReceiveReleaseComplete_TTC
#define SCCP_SendDataForm1 \
    SCCP_SendDataForm1_TTC
#define SCCP_ReceiveDataForm1 \
    SCCP_ReceiveDataForm1_TTC
#define SCCP_SendDataForm2 \
    SCCP_SendDataForm2_TTC
#define SCCP_ReceiveDataForm2 \
    SCCP_ReceiveDataForm2_TTC
#define SCCP_SendAcknowledgement \
    SCCP_SendAcknowledgement_TTC
#define SCCP_ReceiveAcknowledgement \
    SCCP_ReceiveAcknowledgement_TTC
#define SCCP_SendUnitData \
    SCCP_SendUnitData_TTC
#define SCCP_ReceiveUnitData \
    SCCP_ReceiveUnitData_TTC
#define SCCP_SendExtendedUnitData \
    SCCP_SendExtendedUnitData_TTC
#define SCCP_ReceiveExtendedUnitData \
    SCCP_ReceiveExtendedUnitData_TTC
#define SCCP_SendUnitDataService \
    SCCP_SendUnitDataService_TTC
#define SCCP_ReceiveUnitDataService \
    SCCP_ReceiveUnitDataService_TTC
#define SCCP_SendExtendedUnitDataService \
    SCCP_SendExtendedUnitDataService_TTC
#define SCCP_ReceiveExtendedUnitDataService \
    SCCP_ReceiveExtendedUnitDataService_TTC
#define SCCP_SendExpeditedData \
    SCCP_SendExpeditedData_TTC
#define SCCP_ReceiveExpeditedData \
    SCCP_ReceiveExpeditedData_TTC
#define SCCP_SendExpeditedDataAck \
    SCCP_SendExpeditedDataAck_TTC
#define SCCP_ReceiveExpeditedDataAck \
    SCCP_ReceiveExpeditedDataAck_TTC
#define SCCP_SendResetRequest \
    SCCP_SendResetRequest_TTC
#define SCCP_ReceiveResetRequest \
    SCCP_ReceiveResetRequest_TTC
#define SCCP_SendResetConfirmation \
    SCCP_SendResetConfirmation_TTC
#define SCCP_ReceiveResetConfirmation \
    SCCP_ReceiveResetConfirmation_TTC
#define SCCP_SendError \
    SCCP_SendError_TTC
#define SCCP_ReceiveError \
    SCCP_ReceiveError_TTC
#define SCCP_SendInactivityTest \
    SCCP_SendInactivityTest_TTC
#define SCCP_ReceiveInactivityTest \
    SCCP_ReceiveInactivityTest_TTC
#define SCCP_SendLongUnitData \
    SCCP_SendLongUnitData_TTC
#define SCCP_ReceiveLongUnitData \
    SCCP_ReceiveLongUnitData_TTC
#define SCCP_SendLongUnitDataService \
    SCCP_SendLongUnitDataService_TTC
#define SCCP_ReceiveLongUnitDataService \
    SCCP_ReceiveLongUnitDataService_TTC

#define SCCP_CR_Desc        SCCP_CR_Desc_TTC
#define SCCP_CC_Desc        SCCP_CC_Desc_TTC
#define SCCP_CREF_Desc      SCCP_CREF_Desc_TTC
#define SCCP_RLSD_Desc      SCCP_RLSD_Desc_TTC
#define SCCP_RLC_Desc       SCCP_RLC_Desc_TTC
#define SCCP_DT1_Desc       SCCP_DT1_Desc_TTC
#define SCCP_DT2_Desc       SCCP_DT2_Desc_TTC
#define SCCP_AK_Desc        SCCP_AK_Desc_TTC
#define SCCP_UDT_Desc       SCCP_UDT_Desc_TTC
#define SCCP_XUDT_Desc      SCCP_XUDT_Desc_TTC
#define SCCP_UDTS_Desc      SCCP_UDTS_Desc_TTC
#define SCCP_XUDTS_Desc     SCCP_XUDTS_Desc_TTC
#define SCCP_ED_Desc        SCCP_ED_Desc_TTC
#define SCCP_EA_Desc        SCCP_EA_Desc_TTC
#define SCCP_RSR_Desc       SCCP_RSR_Desc_TTC
#define SCCP_RSC_Desc       SCCP_RSC_Desc_TTC
#define SCCP_ERR_Desc       SCCP_ERR_Desc_TTC
#define SCCP_IT_Desc        SCCP_IT_Desc_TTC
#define SCCP_LUDT_Desc      SCCP_LUDT_Desc_TTC
#define SCCP_LUDTS_Desc     SCCP_LUDTS_Desc_TTC


#define SCCP_ManagementCallbacks    SCCP_TTC_ManagementCallbacks
#define SCCP_GlobalTitleTranslator  SCCP_TTC_GlobalTitleTranslator
#define SCCP_SSNRoutingCallbacks    SCCP_TTC_SSNRoutingCallbacks

#define ITS_SCCP            ITS_SCCP_TTC
#define ITS_SCCP_SRC        ITS_SCCP_TTC_SRC


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
#define SCCP_GetSharedLocalRef  SCCP_GetSharedLocalRef_CCITT
#define SCCP_AddConcernedSubSystem  SCCP_AddConcernedSubSystem_CCITT
#define SCCP_RemConcernedSubSystem  SCCP_RemConcernedSubSystem_CCITT
#define SCCP_AddDuplicatedSubSystem SCCP_AddDuplicatedSubSystem_CCITT
#define SCCP_RemDuplicatedSubSystem SCCP_RemDuplicatedSubSystem_CCITT

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
#define SCCP_GetSharedLocalRef  SCCP_GetSharedLocalRef_ANSI
#define SCCP_AddConcernedSubSystem  SCCP_AddConcernedSubSystem_ANSI
#define SCCP_RemConcernedSubSystem  SCCP_RemConcernedSubSystem_ANSI
#define SCCP_AddDuplicatedSubSystem SCCP_AddDuplicatedSubSystem_ANSI
#define SCCP_RemDuplicatedSubSystem SCCP_RemDuplicatedSubSystem_ANSI

#elif defined(PRC)

#define SCCP_Encode             SCCP_Encode_PRC
#define SCCP_Decode             SCCP_Decode_PRC
#define SCCP_EncodeMTP3         SCCP_EncodeMTP3_PRC
#define SCCP_DecodeMTP3         SCCP_DecodeMTP3_PRC
#define SCCP_SendEvent          SCCP_SendEvent_PRC
#define SCCP_ReceiveEvent       SCCP_ReceiveEvent_PRC
#define SCCP_IsSSNEquipped      SCCP_IsSSNEquipped_PRC
#define SCCP_IsSSNAllowed       SCCP_IsSSNAllowed_PRC
#define SCCP_IsSSNCongested     SCCP_IsSSNCongested_PRC
#define SCCP_GetNextLocalRef    SCCP_GetNextLocalRef_PRC
#define SCCP_GetSharedLocalRef    SCCP_GetSharedLocalRef_PRC
#define SCCP_AddConcernedSubSystem  SCCP_AddConcernedSubSystem_PRC
#define SCCP_RemConcernedSubSystem  SCCP_RemConcernedSubSystem_PRC
#define SCCP_AddDuplicatedSubSystem SCCP_AddDuplicatedSubSystem_PRC
#define SCCP_RemDuplicatedSubSystem SCCP_RemDuplicatedSubSystem_PRC

#elif defined(TTC)

#define SCCP_Encode             SCCP_Encode_TTC
#define SCCP_Decode             SCCP_Decode_TTC
#define SCCP_EncodeMTP3         SCCP_EncodeMTP3_TTC
#define SCCP_DecodeMTP3         SCCP_DecodeMTP3_TTC
#define SCCP_SendEvent          SCCP_SendEvent_TTC
#define SCCP_ReceiveEvent       SCCP_ReceiveEvent_TTC
#define SCCP_IsSSNEquipped      SCCP_IsSSNEquipped_TTC
#define SCCP_IsSSNAllowed       SCCP_IsSSNAllowed_TTC
#define SCCP_IsSSNCongested     SCCP_IsSSNCongested_TTC
#define SCCP_GetNextLocalRef    SCCP_GetNextLocalRef_TTC
#define SCCP_GetSharedLocalRef    SCCP_GetSharedLocalRef_TTC
#define SCCP_AddConcernedSubSystem  SCCP_AddConcernedSubSystem_TTC
#define SCCP_RemConcernedSubSystem  SCCP_RemConcernedSubSystem_TTC
#define SCCP_AddDuplicatedSubSystem SCCP_AddDuplicatedSubSystem_TTC
#define SCCP_RemDuplicatedSubSystem SCCP_RemDuplicatedSubSystem_TTC


#endif


/*
 * * * OSS APIs short names * * *
 */   
#if defined(ANSI)

#define SCCP_OSS_GetGeneralCfg      SCCP_OSS_GetGeneralCfg_ANSI
#define SCCP_OSS_SetGeneralCfg      SCCP_OSS_SetGeneralCfg_ANSI
#define SCCP_OSS_GetBehaviors       SCCP_OSS_GetBehaviors_ANSI
#define SCCP_OSS_SetBehavior        SCCP_OSS_SetBehavior_ANSI
#define SCCP_OSS_AddLocalSSN        SCCP_OSS_AddLocalSSN_ANSI
#define SCCP_OSS_RemoveLocalSSN     SCCP_OSS_RemoveLocalSSN_ANSI
#define SCCP_OSS_AddRemoteSSN       SCCP_OSS_AddRemoteSSN_ANSI
#define SCCP_OSS_RemoveRemoteSSN    SCCP_OSS_RemoveRemoteSSN_ANSI
#define SCCP_OSS_GetAllSSN          SCCP_OSS_GetAllSSN_ANSI
#define SCCP_OSS_AddConcernedSSN    SCCP_OSS_AddConcernedSSN_ANSI
#define SCCP_OSS_RemoveConcernedSSN SCCP_OSS_RemoveConcernedSSN_ANSI
#define SCCP_OSS_GetConcernedSSN    SCCP_OSS_GetConcernedSSN_ANSI
#define SCCP_OSS_GetPegs            SCCP_OSS_GetPegs_ANSI
#define SCCP_OSS_ClearPeg           SCCP_OSS_ClearPeg_ANSI
#define SCCP_OSS_GetTimers          SCCP_OSS_GetTimers_ANSI
#define SCCP_OSS_SetTimer           SCCP_OSS_SetTimer_ANSI
#define SCCP_OSS_SendSSA            SCCP_OSS_SendSSA_ANSI
#define SCCP_OSS_SendSSP            SCCP_OSS_SendSSP_ANSI
#define SCCP_OSS_SendSST            SCCP_OSS_SendSST_ANSI

#elif defined(CCITT) 

#define SCCP_OSS_GetGeneralCfg      SCCP_OSS_GetGeneralCfg_CCITT
#define SCCP_OSS_SetGeneralCfg      SCCP_OSS_SetGeneralCfg_CCITT
#define SCCP_OSS_GetBehaviors       SCCP_OSS_GetBehaviors_CCITT
#define SCCP_OSS_SetBehavior        SCCP_OSS_SetBehavior_CCITT
#define SCCP_OSS_AddLocalSSN        SCCP_OSS_AddLocalSSN_CCITT
#define SCCP_OSS_RemoveLocalSSN     SCCP_OSS_RemoveLocalSSN_CCITT
#define SCCP_OSS_AddRemoteSSN       SCCP_OSS_AddRemoteSSN_CCITT
#define SCCP_OSS_RemoveRemoteSSN    SCCP_OSS_RemoveRemoteSSN_CCITT
#define SCCP_OSS_GetAllSSN          SCCP_OSS_GetAllSSN_CCITT
#define SCCP_OSS_AddConcernedSSN    SCCP_OSS_AddConcernedSSN_CCITT
#define SCCP_OSS_RemoveConcernedSSN SCCP_OSS_RemoveConcernedSSN_CCITT
#define SCCP_OSS_GetConcernedSSN    SCCP_OSS_GetConcernedSSN_CCITT
#define SCCP_OSS_GetPegs            SCCP_OSS_GetPegs_CCITT
#define SCCP_OSS_ClearPeg           SCCP_OSS_ClearPeg_CCITT
#define SCCP_OSS_GetTimers          SCCP_OSS_GetTimers_CCITT
#define SCCP_OSS_SetTimer           SCCP_OSS_SetTimer_CCITT
#define SCCP_OSS_SendSSA            SCCP_OSS_SendSSA_CCITT
#define SCCP_OSS_SendSSP            SCCP_OSS_SendSSP_CCITT
#define SCCP_OSS_SendSST            SCCP_OSS_SendSST_CCITT

#elif defined(PRC) 
/* To be defined later */
#elif defined(TTC) 
/* To be defined later */
#endif


#endif /* _ITS_SCCP_CMN_H_ */

