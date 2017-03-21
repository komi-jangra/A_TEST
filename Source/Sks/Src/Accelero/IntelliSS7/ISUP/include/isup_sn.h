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
 *  ID: $Id: isup_sn.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:05  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:49:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.2.6.1.10.2  2005/01/31 11:31:49  snagesh
 * LOG: ISUP OSS APIs short names added
 * LOG:
 * LOG: Revision 7.2.2.2.6.1.10.1  2004/12/16 03:35:28  randresol
 * LOG: Merge JAPAN variant implementation from TTC branch
 * LOG:
 * LOG: Revision 7.2.2.2.6.1.6.1  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.2.2.2.6.1  2004/01/05 09:43:43  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG: CVg: Committing in .
 * LOG:
 * LOG: Revision 7.2.2.2.2.1  2003/11/03 11:02:06  akumar
 * LOG: Added Mgmt Indication func decl.
 * LOG:
 * LOG: Revision 7.2.2.2  2003/07/30 04:31:43  sjaddu
 * LOG: FAC is moned form 97 dir to here.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 09:08:45  ssingh
 * LOG: ANSI/ITU latest changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 8.3  2003/04/04 04:50:16  ssingh
 * LOG: ReceiveConformation is removed.
 * LOG:
 * LOG: Revision 8.2  2003/03/26 10:21:20  ssingh
 * LOG: Changes done in files:
 * LOG: isup_cmn.h      : Indications added for COT reset/release.
 * LOG: isup_sn.h       : UnReserveCIC short name added
 * LOG: ansi/isup.h     : UnReserveCIC declared.
 * LOG: itu/isup.       : UnReserveCIC declared.
 * LOG: isup_variants.h : CIC_INFO is modified for ANSI.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:23  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2003/02/05 17:04:45  sjaddu
 * LOG: ReserveCic changes of itu.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/08/16 22:09:03  mmiers
 * LOG: Add the china variant
 * LOG:
 * LOG: Revision 6.4  2002/08/01 15:47:44  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.3.2.2  2002/07/25 21:32:11  ssingh
 * LOG: Added new functions to handle Indications and Conformations.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/07/06 06:35:53  hbalimid
 * LOG: Fixed ISUP_ReceiveEXMIndication.
 * LOG:
 * LOG: Revision 6.3  2002/06/22 03:05:47  hbalimid
 * LOG: LOP Request and Indications added
 * LOG:
 * LOG: Revision 6.2  2002/05/20 15:28:21  sjaddu
 * LOG: Merge from PR6 to current.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7.2.1  2002/04/04 21:43:55  ssanyal
 * LOG: Adding new msg ISUP_MSG_FAC for ANSI95: also, ANSI & ITU specific timers are transfered from isup_cmn.h to local file.
 * LOG:
 * LOG: Revision 5.7  2002/02/26 23:54:59  ssharma
 * LOG: Add timer and error indications to stack.
 * LOG:
 * LOG: Revision 5.6  2002/02/15 23:19:45  ssharma
 * LOG: Add ValidateCIC to the short names list.
 * LOG:
 * LOG: Revision 5.5  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 * LOG: Revision 5.4  2002/02/01 20:05:56  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.3  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
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

#ifndef _ITS_ISUP_SN_H_
#define _ITS_ISUP_SN_H_

#ident "$Id: isup_sn.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $"

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define ISUP_AllocateCIC        ISUP_AllocateCIC_CCITT

#define ISUP_SetVariant         ISUP_SetVariant_CCITT
#define ISUP_GetVariant         ISUP_GetVariant_CCITT
#define ISUP_ComputeMSize       ISUP_ComputeMSize_CCITT
#define ISUP_GetDescriptor      ISUP_GetDescriptor_CCITT
#define ISUP_GetTimerText       ISUP_GetTimerText_CCITT
#define ISUP_GetMsgAbbr         ISUP_GetMsgAbbr_CCITT
#define ISUP_GetMsgName         ISUP_GetMsgName_CCITT

/* for variant management */
#define __ISUP_DecodeMsgProc    __ISUP_DecodeMsgProc_CCITT
#define __ISUP_EncodeMsgProc    __ISUP_EncodeMsgProc_CCITT

#define ISUP_Decode             ISUP_Decode_CCITT
#define ISUP_Encode             ISUP_Encode_CCITT

#define    ISUP_ACM_Desc      ISUP_ACM_Desc_CCITT
#define    ISUP_ANM_Desc      ISUP_ANM_Desc_CCITT
#define    ISUP_CPG_Desc      ISUP_CPG_Desc_CCITT
#define    ISUP_CQM_Desc      ISUP_CQM_Desc_CCITT
#define    ISUP_CQR_Desc      ISUP_CQR_Desc_CCITT
#define    ISUP_CFN_Desc      ISUP_CFN_Desc_CCITT
#define    ISUP_CON_Desc      ISUP_CON_Desc_CCITT
#define    ISUP_COT_Desc      ISUP_COT_Desc_CCITT
#define    ISUP_FRJ_Desc      ISUP_FRJ_Desc_CCITT
#define    ISUP_INF_Desc      ISUP_INF_Desc_CCITT
#define    ISUP_INR_Desc      ISUP_INR_Desc_CCITT
#define    ISUP_IAM_Desc      ISUP_IAM_Desc_CCITT
#define    ISUP_REL_Desc      ISUP_REL_Desc_CCITT
#define    ISUP_RLC_Desc      ISUP_RLC_Desc_CCITT
#define    ISUP_SAM_Desc      ISUP_SAM_Desc_CCITT
#define    ISUP_USR_Desc      ISUP_USR_Desc_CCITT
#define    ISUP_FOT_Desc      ISUP_FOT_Desc_CCITT
#define    ISUP_RES_Desc      ISUP_RES_Desc_CCITT
#define    ISUP_SUS_Desc      ISUP_SUS_Desc_CCITT
#define    ISUP_BLO_Desc      ISUP_BLO_Desc_CCITT
#define    ISUP_BLA_Desc      ISUP_BLA_Desc_CCITT
#define    ISUP_UBL_Desc      ISUP_UBL_Desc_CCITT
#define    ISUP_UBA_Desc      ISUP_UBA_Desc_CCITT
#define    ISUP_CCR_Desc      ISUP_CCR_Desc_CCITT
#define    ISUP_LPA_Desc      ISUP_LPA_Desc_CCITT
#define    ISUP_OLM_Desc      ISUP_OLM_Desc_CCITT
#define    ISUP_RSC_Desc      ISUP_RSC_Desc_CCITT
#define    ISUP_UCIC_Desc     ISUP_UCIC_Desc_CCITT
#define    ISUP_CGB_Desc      ISUP_CGB_Desc_CCITT
#define    ISUP_CGBA_Desc     ISUP_CGBA_Desc_CCITT
#define    ISUP_CGU_Desc      ISUP_CGU_Desc_CCITT
#define    ISUP_CGUA_Desc     ISUP_CGUA_Desc_CCITT
#define    ISUP_GRS_Desc      ISUP_GRS_Desc_CCITT
#define    ISUP_GRA_Desc      ISUP_GRA_Desc_CCITT
#define    ISUP_FAA_Desc      ISUP_FAA_Desc_CCITT
#define    ISUP_FAR_Desc      ISUP_FAR_Desc_CCITT
#define    ISUP_PAM_Desc      ISUP_PAM_Desc_CCITT
#define    ISUP_UPT_Desc      ISUP_UPT_Desc_CCITT
#define    ISUP_UPA_Desc      ISUP_UPA_Desc_CCITT
#define    ISUP_FAC_Desc      ISUP_FAC_Desc_CCITT
#define    ISUP_NRM_Desc      ISUP_NRM_Desc_CCITT
#define    ISUP_IDR_Desc      ISUP_IDR_Desc_CCITT
#define    ISUP_IRS_Desc      ISUP_IRS_Desc_CCITT
#define    ISUP_SGM_Desc      ISUP_SGM_Desc_CCITT
#define    ISUP_LOP_Desc      ISUP_LOP_Desc_CCITT

#define ISUP_SendACMRequest              ISUP_SendACMRequest_CCITT
#define ISUP_ReceiveACMIndication        ISUP_ReceiveACMIndication_CCITT
#define ISUP_SendANMRequest              ISUP_SendANMRequest_CCITT
#define ISUP_ReceiveANMIndication        ISUP_ReceiveANMIndication_CCITT
#define ISUP_SendCPGRequest              ISUP_SendCPGRequest_CCITT
#define ISUP_ReceiveCPGIndication        ISUP_ReceiveCPGIndication_CCITT
#define ISUP_SendCQMRequest              ISUP_SendCQMRequest_CCITT
#define ISUP_ReceiveCQMIndication        ISUP_ReceiveCQMIndication_CCITT
#define ISUP_SendCQRRequest              ISUP_SendCQRRequest_CCITT
#define ISUP_ReceiveCQRIndication        ISUP_ReceiveCQRIndication_CCITT
#define ISUP_SendCFNRequest              ISUP_SendCFNRequest_CCITT
#define ISUP_ReceiveCFNIndication        ISUP_ReceiveCFNIndication_CCITT
#define ISUP_SendCONRequest              ISUP_SendCONRequest_CCITT
#define ISUP_ReceiveCONIndication        ISUP_ReceiveCONIndication_CCITT
#define ISUP_SendCOTRequest              ISUP_SendCOTRequest_CCITT
#define ISUP_ReceiveCOTIndication        ISUP_ReceiveCOTIndication_CCITT
#define ISUP_SendFRJRequest              ISUP_SendFRJRequest_CCITT
#define ISUP_ReceiveFRJIndication        ISUP_ReceiveFRJIndication_CCITT
#define ISUP_SendINFRequest              ISUP_SendINFRequest_CCITT
#define ISUP_ReceiveINFIndication        ISUP_ReceiveINFIndication_CCITT
#define ISUP_SendINRRequest              ISUP_SendINRRequest_CCITT
#define ISUP_ReceiveINRIndication        ISUP_ReceiveINRIndication_CCITT
#define ISUP_SendIAMRequest              ISUP_SendIAMRequest_CCITT
#define ISUP_ReceiveIAMIndication        ISUP_ReceiveIAMIndication_CCITT
#define ISUP_SendRELRequest              ISUP_SendRELRequest_CCITT
#define ISUP_ReceiveRELIndication        ISUP_ReceiveRELIndication_CCITT
#define ISUP_SendRLCRequest              ISUP_SendRLCRequest_CCITT
#define ISUP_ReceiveRLCIndication        ISUP_ReceiveRLCIndication_CCITT
#define ISUP_SendSAMRequest              ISUP_SendSAMRequest_CCITT
#define ISUP_ReceiveSAMIndication        ISUP_ReceiveSAMIndication_CCITT
#define ISUP_SendUSRRequest              ISUP_SendUSRRequest_CCITT
#define ISUP_ReceiveUSRIndication        ISUP_ReceiveUSRIndication_CCITT
#define ISUP_SendFOTRequest              ISUP_SendFOTRequest_CCITT
#define ISUP_ReceiveFOTIndication        ISUP_ReceiveFOTIndication_CCITT
#define ISUP_SendSUSRequest              ISUP_SendSUSRequest_CCITT
#define ISUP_ReceiveSUSIndication        ISUP_ReceiveSUSIndication_CCITT
#define ISUP_SendRESRequest              ISUP_SendRESRequest_CCITT
#define ISUP_ReceiveRESIndication        ISUP_ReceiveRESIndication_CCITT
#define ISUP_SendBLORequest              ISUP_SendBLORequest_CCITT
#define ISUP_ReceiveBLOIndication        ISUP_ReceiveBLOIndication_CCITT
#define ISUP_SendBLARequest              ISUP_SendBLARequest_CCITT
#define ISUP_ReceiveBLAIndication        ISUP_ReceiveBLAIndication_CCITT
#define ISUP_SendUBLRequest              ISUP_SendUBLRequest_CCITT
#define ISUP_ReceiveUBLIndication        ISUP_ReceiveUBLIndication_CCITT
#define ISUP_SendUBARequest              ISUP_SendUBARequest_CCITT
#define ISUP_ReceiveUBAIndication        ISUP_ReceiveUBAIndication_CCITT
#define ISUP_SendCCRRequest              ISUP_SendCCRRequest_CCITT
#define ISUP_ReceiveCCRIndication        ISUP_ReceiveCCRIndication_CCITT
#define ISUP_SendLPARequest              ISUP_SendLPARequest_CCITT
#define ISUP_ReceiveLPAIndication        ISUP_ReceiveLPAIndication_CCITT
#define ISUP_SendOLMRequest              ISUP_SendOLMRequest_CCITT
#define ISUP_ReceiveOLMIndication        ISUP_ReceiveOLMIndication_CCITT
#define ISUP_SendRSCRequest              ISUP_SendRSCRequest_CCITT
#define ISUP_ReceiveRSCIndication        ISUP_ReceiveRSCIndication_CCITT
#define ISUP_SendUCICRequest             ISUP_SendUCICRequest_CCITT
#define ISUP_ReceiveUCICIndication       ISUP_ReceiveUCICIndication_CCITT
#define ISUP_SendCGBRequest              ISUP_SendCGBRequest_CCITT
#define ISUP_ReceiveCGBIndication        ISUP_ReceiveCGBIndication_CCITT
#define ISUP_SendCGBARequest             ISUP_SendCGBARequest_CCITT
#define ISUP_ReceiveCGBAIndication       ISUP_ReceiveCGBAIndication_CCITT
#define ISUP_SendCGURequest              ISUP_SendCGURequest_CCITT
#define ISUP_ReceiveCGUIndication        ISUP_ReceiveCGUIndication_CCITT
#define ISUP_SendCGUARequest             ISUP_SendCGUARequest_CCITT
#define ISUP_ReceiveCGUAIndication       ISUP_ReceiveCGUAIndication_CCITT
#define ISUP_SendGRSRequest              ISUP_SendGRSRequest_CCITT
#define ISUP_ReceiveGRSIndication        ISUP_ReceiveGRSIndication_CCITT
#define ISUP_SendGRARequest              ISUP_SendGRARequest_CCITT
#define ISUP_ReceiveGRAIndication        ISUP_ReceiveGRAIndication_CCITT
#define ISUP_SendFARRequest              ISUP_SendFARRequest_CCITT
#define ISUP_ReceiveFARIndication        ISUP_ReceiveFARIndication_CCITT
#define ISUP_SendFAARequest              ISUP_SendFAARequest_CCITT
#define ISUP_ReceiveFAAIndication        ISUP_ReceiveFAAIndication_CCITT
#define ISUP_SendPAMRequest              ISUP_SendPAMRequest_CCITT
#define ISUP_ReceivePAMIndication        ISUP_ReceivePAMIndication_CCITT
#define ISUP_SendUPTRequest              ISUP_SendUPTRequest_CCITT
#define ISUP_ReceiveUPTIndication        ISUP_ReceiveUPTIndication_CCITT
#define ISUP_SendUPARequest              ISUP_SendUPARequest_CCITT
#define ISUP_ReceiveUPAIndication        ISUP_ReceiveUPAIndication_CCITT
#define ISUP_SendFACRequest              ISUP_SendFACRequest_CCITT
#define ISUP_ReceiveFACIndication        ISUP_ReceiveFACIndication_CCITT
#define ISUP_SendNRMRequest              ISUP_SendNRMRequest_CCITT
#define ISUP_ReceiveNRMIndication        ISUP_ReceiveNRMIndication_CCITT
#define ISUP_SendIDRRequest              ISUP_SendIDRRequest_CCITT
#define ISUP_ReceiveIDRIndication        ISUP_ReceiveIDRIndication_CCITT
#define ISUP_SendIRSRequest              ISUP_SendIRSRequest_CCITT
#define ISUP_ReceiveIRSIndication        ISUP_ReceiveIRSIndication_CCITT
#define ISUP_SendSGMRequest              ISUP_SendSGMRequest_CCITT
#define ISUP_ReceiveSGMIndication        ISUP_ReceiveSGMIndication_CCITT
#define ISUP_ReceiveTimeoutIndication    ISUP_ReceiveTimeoutIndication_CCITT
#define ISUP_ReceiveErrorIndication      ISUP_ReceiveErrorIndication_CCITT
#define ISUP_ReceiveIndication           ISUP_ReceiveIndication_CCITT
#define ISUP_ReceiveMgmtIndication       ISUP_ReceiveMgmtIndication_CCITT

/* 
 * ShortNames specific to ITU97
 */
#define ISUP_SendLOPRequest              ISUP_SendLOPRequest_CCITT
#define ISUP_ReceiveLOPIndication        ISUP_ReceiveLOPIndication_CCITT
/* ITU97 */

#define ISUP_ManagementCallbacks    ISUP_CCITT_ManagementCallbacks

#define __ISUP_StartTimer           __ISUP_StartTimer_CCITT
#define __ISUP_StopTimer            __ISUP_StopTimer_CCITT


/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_ISUP            ITS_ISUP_CCITT
#define ITS_ISUP_SRC        ITS_ISUP_CCITT_SRC
#define ITS_ISUP_IE         ITS_ISUP_IE_CCITT

#elif defined(ANSI)

#define ISUP_AllocateCIC    ISUP_AllocateCIC_ANSI

#define ISUP_SetVariant     ISUP_SetVariant_ANSI
#define ISUP_GetVariant     ISUP_GetVariant_ANSI
#define ISUP_ComputeMSize   ISUP_ComputeMSize_ANSI
#define ISUP_GetDescriptor  ISUP_GetDescriptor_ANSI
#define ISUP_GetTimerText   ISUP_GetTimerText_ANSI
#define ISUP_GetMsgAbbr     ISUP_GetMsgAbbr_ANSI
#define ISUP_GetMsgName     ISUP_GetMsgName_ANSI

/* for variant management */
#define __ISUP_DecodeMsgProc    __ISUP_DecodeMsgProc_ANSI
#define __ISUP_EncodeMsgProc    __ISUP_EncodeMsgProc_ANSI

#define ISUP_Decode         ISUP_Decode_ANSI
#define ISUP_Encode         ISUP_Encode_ANSI

#define    ISUP_ACM_Desc      ISUP_ACM_Desc_ANSI
#define    ISUP_ANM_Desc      ISUP_ANM_Desc_ANSI
#define    ISUP_CPG_Desc      ISUP_CPG_Desc_ANSI
#define    ISUP_CQM_Desc      ISUP_CQM_Desc_ANSI
#define    ISUP_CQR_Desc      ISUP_CQR_Desc_ANSI
#define    ISUP_CFN_Desc      ISUP_CFN_Desc_ANSI
#define    ISUP_COT_Desc      ISUP_COT_Desc_ANSI
#define    ISUP_CRA_Desc      ISUP_CRA_Desc_ANSI
#define    ISUP_CRM_Desc      ISUP_CRM_Desc_ANSI
#define    ISUP_CVR_Desc      ISUP_CVR_Desc_ANSI
#define    ISUP_CVT_Desc      ISUP_CVT_Desc_ANSI
#define    ISUP_EXM_Desc      ISUP_EXM_Desc_ANSI
#define    ISUP_INF_Desc      ISUP_INF_Desc_ANSI
#define    ISUP_INR_Desc      ISUP_INR_Desc_ANSI
#define    ISUP_IAM_Desc      ISUP_IAM_Desc_ANSI
#define    ISUP_REL_Desc      ISUP_REL_Desc_ANSI
#define    ISUP_RLC_Desc      ISUP_RLC_Desc_ANSI
#define    ISUP_FOT_Desc      ISUP_FOT_Desc_ANSI
#define    ISUP_RES_Desc      ISUP_RES_Desc_ANSI
#define    ISUP_SUS_Desc      ISUP_SUS_Desc_ANSI
#define    ISUP_BLO_Desc      ISUP_BLO_Desc_ANSI
#define    ISUP_BLA_Desc      ISUP_BLA_Desc_ANSI
#define    ISUP_UBL_Desc      ISUP_UBL_Desc_ANSI
#define    ISUP_UBA_Desc      ISUP_UBA_Desc_ANSI
#define    ISUP_CCR_Desc      ISUP_CCR_Desc_ANSI
#define    ISUP_LPA_Desc      ISUP_LPA_Desc_ANSI
#define    ISUP_RSC_Desc      ISUP_RSC_Desc_ANSI
#define    ISUP_UCIC_Desc     ISUP_UCIC_Desc_ANSI
#define    ISUP_CGB_Desc      ISUP_CGB_Desc_ANSI
#define    ISUP_CGBA_Desc     ISUP_CGBA_Desc_ANSI
#define    ISUP_CGU_Desc      ISUP_CGU_Desc_ANSI
#define    ISUP_CGUA_Desc     ISUP_CGUA_Desc_ANSI
#define    ISUP_GRS_Desc      ISUP_GRS_Desc_ANSI
#define    ISUP_GRA_Desc      ISUP_GRA_Desc_ANSI
#define    ISUP_PAM_Desc      ISUP_PAM_Desc_ANSI
#define    ISUP_FAC_Desc      ISUP_FAC_Desc_ANSI


#define ISUP_SendACMRequest              ISUP_SendACMRequest_ANSI
#define ISUP_ReceiveACMIndication        ISUP_ReceiveACMIndication_ANSI
#define ISUP_SendANMRequest              ISUP_SendANMRequest_ANSI
#define ISUP_ReceiveANMIndication        ISUP_ReceiveANMIndication_ANSI
#define ISUP_SendCPGRequest              ISUP_SendCPGRequest_ANSI
#define ISUP_ReceiveCPGIndication        ISUP_ReceiveCPGIndication_ANSI
#define ISUP_SendCQMRequest              ISUP_SendCQMRequest_ANSI
#define ISUP_ReceiveCQMIndication        ISUP_ReceiveCQMIndication_ANSI
#define ISUP_SendCQRRequest              ISUP_SendCQRRequest_ANSI
#define ISUP_ReceiveCQRIndication        ISUP_ReceiveCQRIndication_ANSI
#define ISUP_SendCFNRequest              ISUP_SendCFNRequest_ANSI
#define ISUP_ReceiveCFNIndication        ISUP_ReceiveCFNIndication_ANSI
#define ISUP_SendCOTRequest              ISUP_SendCOTRequest_ANSI
#define ISUP_ReceiveCOTIndication        ISUP_ReceiveCOTIndication_ANSI
#define ISUP_SendCRARequest              ISUP_SendCRARequest_ANSI   
#define ISUP_ReceiveCRAIndication        ISUP_ReceiveCRAIndication_ANSI
#define ISUP_SendCRMRequest              ISUP_SendCRMRequest_ANSI   
#define ISUP_ReceiveCRMIndication        ISUP_ReceiveCRMIndication_ANSI
#define ISUP_SendCVRRequest              ISUP_SendCVRRequest_ANSI   
#define ISUP_ReceiveCVRIndication        ISUP_ReceiveCVRIndication_ANSI
#define ISUP_SendCVTRequest              ISUP_SendCVTRequest_ANSI   
#define ISUP_ReceiveCVTIndication        ISUP_ReceiveCVTIndication_ANSI
#define ISUP_SendEXMRequest              ISUP_SendEXMRequest_ANSI
#define ISUP_ReceiveEXMIndication        ISUP_ReceiveEXMIndication_ANSI
#define ISUP_SendINFRequest              ISUP_SendINFRequest_ANSI
#define ISUP_ReceiveINFIndication        ISUP_ReceiveINFIndication_ANSI
#define ISUP_SendINRRequest              ISUP_SendINRRequest_ANSI
#define ISUP_ReceiveINRIndication        ISUP_ReceiveINRIndication_ANSI
#define ISUP_SendIAMRequest              ISUP_SendIAMRequest_ANSI
#define ISUP_ReceiveIAMIndication        ISUP_ReceiveIAMIndication_ANSI
#define ISUP_SendRELRequest              ISUP_SendRELRequest_ANSI
#define ISUP_ReceiveRELIndication        ISUP_ReceiveRELIndication_ANSI
#define ISUP_SendRLCRequest              ISUP_SendRLCRequest_ANSI
#define ISUP_ReceiveRLCIndication        ISUP_ReceiveRLCIndication_ANSI
#define ISUP_SendFOTRequest              ISUP_SendFOTRequest_ANSI
#define ISUP_ReceiveFOTIndication        ISUP_ReceiveFOTIndication_ANSI
#define ISUP_SendSUSRequest              ISUP_SendSUSRequest_ANSI
#define ISUP_ReceiveSUSIndication        ISUP_ReceiveSUSIndication_ANSI
#define ISUP_SendRESRequest              ISUP_SendRESRequest_ANSI
#define ISUP_ReceiveRESIndication        ISUP_ReceiveRESIndication_ANSI
#define ISUP_SendBLORequest              ISUP_SendBLORequest_ANSI
#define ISUP_ReceiveBLOIndication        ISUP_ReceiveBLOIndication_ANSI
#define ISUP_SendBLARequest              ISUP_SendBLARequest_ANSI
#define ISUP_ReceiveBLAIndication        ISUP_ReceiveBLAIndication_ANSI
#define ISUP_SendUBLRequest              ISUP_SendUBLRequest_ANSI
#define ISUP_ReceiveUBLIndication        ISUP_ReceiveUBLIndication_ANSI
#define ISUP_SendUBARequest              ISUP_SendUBARequest_ANSI
#define ISUP_ReceiveUBAIndication        ISUP_ReceiveUBAIndication_ANSI
#define ISUP_SendCCRRequest              ISUP_SendCCRRequest_ANSI
#define ISUP_ReceiveCCRIndication        ISUP_ReceiveCCRIndication_ANSI
#define ISUP_SendLPARequest              ISUP_SendLPARequest_ANSI
#define ISUP_ReceiveLPAIndication        ISUP_ReceiveLPAIndication_ANSI
#define ISUP_SendRSCRequest              ISUP_SendRSCRequest_ANSI
#define ISUP_ReceiveRSCIndication        ISUP_ReceiveRSCIndication_ANSI
#define ISUP_SendUCICRequest             ISUP_SendUCICRequest_ANSI
#define ISUP_ReceiveUCICIndication       ISUP_ReceiveUCICIndication_ANSI
#define ISUP_SendCGBRequest              ISUP_SendCGBRequest_ANSI
#define ISUP_ReceiveCGBIndication        ISUP_ReceiveCGBIndication_ANSI
#define ISUP_SendCGBARequest             ISUP_SendCGBARequest_ANSI
#define ISUP_ReceiveCGBAIndication       ISUP_ReceiveCGBAIndication_ANSI
#define ISUP_SendCGURequest              ISUP_SendCGURequest_ANSI
#define ISUP_ReceiveCGUIndication        ISUP_ReceiveCGUIndication_ANSI
#define ISUP_SendCGUARequest             ISUP_SendCGUARequest_ANSI
#define ISUP_ReceiveCGUAIndication       ISUP_ReceiveCGUAIndication_ANSI
#define ISUP_SendGRSRequest              ISUP_SendGRSRequest_ANSI
#define ISUP_ReceiveGRSIndication        ISUP_ReceiveGRSIndication_ANSI
#define ISUP_SendGRARequest              ISUP_SendGRARequest_ANSI
#define ISUP_ReceiveGRAIndication        ISUP_ReceiveGRAIndication_ANSI
#define ISUP_SendPAMRequest              ISUP_SendPAMRequest_ANSI
#define ISUP_ReceivePAMIndication        ISUP_ReceivePAMIndication_ANSI
#define ISUP_SendFACRequest              ISUP_SendFACRequest_ANSI
#define ISUP_ReceiveFACIndication        ISUP_ReceiveFACIndication_ANSI
#define ISUP_ReceiveTimeoutIndication    ISUP_ReceiveTimeoutIndication_ANSI
#define ISUP_ReceiveErrorIndication      ISUP_ReceiveErrorIndication_ANSI
#define ISUP_ReceiveIndication           ISUP_ReceiveIndication_ANSI
#define ISUP_ReceiveMgmtIndication       ISUP_ReceiveMgmtIndication_ANSI

#define ISUP_ManagementCallbacks    ISUP_ANSI_ManagementCallbacks

#define __ISUP_StartTimer           __ISUP_StartTimer_ANSI
#define __ISUP_StopTimer            __ISUP_StopTimer_ANSI


#define ITS_ISUP            ITS_ISUP_ANSI
#define ITS_ISUP_SRC        ITS_ISUP_ANSI_SRC
#define ITS_ISUP_IE         ITS_ISUP_IE_ANSI

#endif

/******************************** ISUP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define ISUP_Initialize         ISUP_Initialize_CCITT
#define ISUP_Terminate          ISUP_Terminate_CCITT
#define ISUP_SendEvent          ISUP_SendEvent_CCITT
#define ISUP_ReceiveEvent       ISUP_ReceiveEvent_CCITT
#define ISUP_DecodeMTP3         ISUP_DecodeMTP3_CCITT
#define ISUP_EncodeMTP3         ISUP_EncodeMTP3_CCITT
#define ISUP_MessageSanityCheck ISUP_MessageSanityCheck_CCITT
#define ISUP_ReserveCIC         ISUP_ReserveCIC_CCITT
#define ISUP_UnReserveCIC       ISUP_UnReserveCIC_CCITT

#elif defined(ANSI)

#define ISUP_Initialize         ISUP_Initialize_ANSI
#define ISUP_Terminate          ISUP_Terminate_ANSI
#define ISUP_SendEvent          ISUP_SendEvent_ANSI
#define ISUP_ReceiveEvent       ISUP_ReceiveEvent_ANSI
#define ISUP_DecodeMTP3         ISUP_DecodeMTP3_ANSI
#define ISUP_EncodeMTP3         ISUP_EncodeMTP3_ANSI
#define ISUP_MessageSanityCheck ISUP_MessageSanityCheck_ANSI
#define ISUP_ReserveCIC         ISUP_ReserveCIC_ANSI
#define ISUP_UnReserveCIC       ISUP_UnReserveCIC_ANSI

#endif


/*
 * * * OSS APIs short names * * *
 */   
#if defined(ANSI)

#define ISUP_OSS_GetGeneralCfg      ISUP_OSS_GetGeneralCfg_ANSI
#define ISUP_OSS_SetGeneralCfg      ISUP_OSS_SetGeneralCfg_ANSI
#define ISUP_OSS_AddCics            ISUP_OSS_AddCics_ANSI
#define ISUP_OSS_DeleteCics         ISUP_OSS_DeleteCics_ANSI
#define ISUP_OSS_GetCics            ISUP_OSS_GetCics_ANSI
#define ISUP_OSS_GetCicState        ISUP_OSS_GetCicState_ANSI
#define ISUP_OSS_SetCicState        ISUP_OSS_SetCicState_ANSI
#define ISUP_OSS_AddDestInfo        ISUP_OSS_AddDestInfo_ANSI
#define ISUP_OSS_GetDestInfo        ISUP_OSS_GetDestInfo_ANSI
#define ISUP_OSS_SetExchangeType    ISUP_OSS_SetExchangeType_ANSI
#define ISUP_OSS_GetExchangeType    ISUP_OSS_GetExchangeType_ANSI
#define ISUP_OSS_SetCongLevel       ISUP_OSS_SetCongLevel_ANSI
#define ISUP_OSS_GetCongLevel       ISUP_OSS_GetCongLevel_ANSI
#define ISUP_OSS_AddVariant         ISUP_OSS_AddVariant_ANSI
#define ISUP_OSS_SetTimer           ISUP_OSS_SetTimer_ANSI
#define ISUP_OSS_GetTimers          ISUP_OSS_GetTimers_ANSI
#define ISUP_OSS_GetGenPegs         ISUP_OSS_GetGenPegs_ANSI
#define ISUP_OSS_ClearGenPeg        ISUP_OSS_ClearGenPeg_ANSI
#define ISUP_OSS_GetMsgSentPegs     ISUP_OSS_GetMsgSentPegs_ANSI
#define ISUP_OSS_ClearMsgSentPegs   ISUP_OSS_ClearMsgSentPegs_ANSI
#define ISUP_OSS_GetMsgRcvdPegs     ISUP_OSS_GetMsgRcvdPegs_ANSI
#define ISUP_OSS_ClearMsgRcvdPegs   ISUP_OSS_ClearMsgRcvdPegs_ANSI
#define ISUP_OSS_GetCicPegs         ISUP_OSS_GetCicPegs_ANSI
#define ISUP_OSS_ClearCicPeg        ISUP_OSS_ClearCicPeg_ANSI
#define ISUP_OSS_SendUBL            ISUP_OSS_SendUBL_ANSI
#define ISUP_OSS_SendBLO            ISUP_OSS_SendBLO_ANSI
#define ISUP_OSS_SendRSC            ISUP_OSS_SendRSC_ANSI
#define ISUP_OSS_SendRLC            ISUP_OSS_SendRLC_ANSI
#define ISUP_OSS_SendGRS            ISUP_OSS_SendGRS_ANSI
#define ISUP_OSS_SendCGU            ISUP_OSS_SendCGU_ANSI
#define ISUP_OSS_SendCGB            ISUP_OSS_SendCGB_ANSI
#define ISUP_OSS_SendCQM            ISUP_OSS_SendCQM_ANSI

#elif defined(CCITT) 

#define ISUP_OSS_GetGeneralCfg      ISUP_OSS_GetGeneralCfg_CCITT
#define ISUP_OSS_SetGeneralCfg      ISUP_OSS_SetGeneralCfg_CCITT
#define ISUP_OSS_AddCics            ISUP_OSS_AddCics_CCITT
#define ISUP_OSS_DeleteCics         ISUP_OSS_DeleteCics_CCITT
#define ISUP_OSS_GetCics            ISUP_OSS_GetCics_CCITT
#define ISUP_OSS_GetCicState        ISUP_OSS_GetCicState_CCITT
#define ISUP_OSS_SetCicState        ISUP_OSS_SetCicState_CCITT
#define ISUP_OSS_AddDestInfo        ISUP_OSS_AddDestInfo_CCITT
#define ISUP_OSS_GetDestInfo        ISUP_OSS_GetDestInfo_CCITT
#define ISUP_OSS_SetExchangeType    ISUP_OSS_SetExchangeType_CCITT
#define ISUP_OSS_GetExchangeType    ISUP_OSS_GetExchangeType_CCITT
#define ISUP_OSS_SetCongLevel       ISUP_OSS_SetCongLevel_CCITT
#define ISUP_OSS_GetCongLevel       ISUP_OSS_GetCongLevel_CCITT
#define ISUP_OSS_AddVariant         ISUP_OSS_AddVariant_CCITT
#define ISUP_OSS_SetTimer           ISUP_OSS_SetTimer_CCITT
#define ISUP_OSS_GetTimers          ISUP_OSS_GetTimers_CCITT
#define ISUP_OSS_GetGenPegs         ISUP_OSS_GetGenPegs_CCITT
#define ISUP_OSS_ClearGenPeg        ISUP_OSS_ClearGenPeg_CCITT
#define ISUP_OSS_GetMsgSentPegs     ISUP_OSS_GetMsgSentPegs_CCITT
#define ISUP_OSS_ClearMsgSentPegs   ISUP_OSS_ClearMsgSentPegs_CCITT
#define ISUP_OSS_GetMsgRcvdPegs     ISUP_OSS_GetMsgRcvdPegs_CCITT
#define ISUP_OSS_ClearMsgRcvdPegs   ISUP_OSS_ClearMsgRcvdPegs_CCITT
#define ISUP_OSS_GetCicPegs         ISUP_OSS_GetCicPegs_CCITT
#define ISUP_OSS_ClearCicPeg        ISUP_OSS_ClearCicPeg_CCITT
#define ISUP_OSS_SendUBL            ISUP_OSS_SendUBL_CCITT
#define ISUP_OSS_SendBLO            ISUP_OSS_SendBLO_CCITT
#define ISUP_OSS_SendRSC            ISUP_OSS_SendRSC_CCITT
#define ISUP_OSS_SendRLC            ISUP_OSS_SendRLC_CCITT
#define ISUP_OSS_SendGRS            ISUP_OSS_SendGRS_CCITT
#define ISUP_OSS_SendCGU            ISUP_OSS_SendCGU_CCITT
#define ISUP_OSS_SendCGB            ISUP_OSS_SendCGB_CCITT
#define ISUP_OSS_SendCQM            ISUP_OSS_SendCQM_CCITT

#elif defined(PRC) 
/* To be defined later */
#elif defined(TTC) 
/* To be defined later */
#endif


#endif /* _ITS_ISUP_SN_H_ */

