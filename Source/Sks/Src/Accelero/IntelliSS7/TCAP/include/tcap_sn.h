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
 *     FILE: tcap.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: tcap_sn.h,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:55  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:53  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:29  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1.6.3  2005/01/31 11:30:28  snagesh
 * LOG: TCAP OSS APIs short names added
 * LOG:
 * LOG: Revision 7.2.10.1.6.2  2004/12/24 13:00:31  ssingh
 * LOG: ITS_TCAP_TTC_SRC corrected
 * LOG:
 * LOG: Revision 7.2.10.1.6.1  2004/12/16 02:56:41  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/21 06:59:17  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.2  2003/02/04 07:16:49  yranade
 * LOG: Tcap-Manual Codec Integration.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/16 22:09:15  mmiers
 * LOG: Add the China variant
 * LOG:
 * LOG: Revision 6.3  2002/07/03 17:40:49  mmiers
 * LOG: More china changes
 * LOG:
 * LOG: Revision 6.2  2002/07/03 16:37:27  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
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

#ifndef _ITS_TCAP_SN_H
#define _ITS_TCAP_SN_H

#ident "$Id: tcap_sn.h,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $"

#if defined(CCITT)

#define OTID_IDENT             OTID_IDENT_CCITT
#define DTID_IDENT             DTID_IDENT_CCITT
#define PABT_IDENT             PABT_IDENT_CCITT
#define DIALOG_IDENT           DIALOG_IDENT_CCITT
#define CSEQ_IDENT             CSEQ_IDENT_CCITT

#define TCPPT_TC_UNI           TCAP_PT_TC_UNI_CCITT
#define TCPPT_TC_BEGIN         TCAP_PT_TC_BEGIN_CCITT
#define TCPPT_TC_END           TCAP_PT_TC_END_CCITT
#define TCPPT_TC_CONTINUE      TCAP_PT_TC_CONTINUE_CCITT
#define TCPPT_TC_P_ABORT       TCAP_PT_TC_P_ABORT_CCITT
#define TCPPT_TC_U_ABORT       TCAP_PT_TC_U_ABORT_CCITT
#define TCPPT_TC_NOTICE        TCAP_PT_TC_NOTICE_CCITT

#define TCPPT_TC_INVOKE         TCAP_PT_TC_INVOKE_CCITT
#define TCPPT_TC_RESULT_L       TCAP_PT_TC_RESULT_L_CCITT
#define TCPPT_TC_U_ERROR        TCAP_PT_TC_U_ERROR_CCITT
#define TCPPT_TC_R_REJECT       TCAP_PT_TC_R_REJECT_CCITT
#define TCPPT_TC_RESULT_NL      TCAP_PT_TC_RESULT_NL_CCITT
#define TCPPT_TC_L_CANCEL       TCAP_PT_TC_L_CANCEL_CCITT
#define TCPPT_TC_U_CANCEL       TCAP_PT_TC_U_CANCEL_CCITT
#define TCPPT_TC_L_REJECT       TCAP_PT_TC_L_REJECT_CCITT
#define TCPPT_TC_U_REJECT       TCAP_PT_TC_U_REJECT_CCITT
#define TCAP_PT_TC_TIMER_RESET  TCAP_PT_TC_TIMER_RESET_CCITT

#define TCPPN_INVOKE_TAG       TCAP_PN_INVOKE_TAG_CCITT
#define TCPPN_LOCAL_OP_TAG     TCAP_PN_LOCAL_OP_TAG_CCITT 
#define TCPPN_GLOBAL_OP_TAG    TCAP_PN_GLOBAL_OP_TAG_CCITT
#define TCPPN_LOCAL_ERR_TAG    TCAP_PN_LOCAL_ERR_TAG_CCITT
#define TCPPN_GLOBAL_ERR_TAG   TCAP_PN_GLOBAL_ERR_TAG_CCITT
#define TCPPN_PROBLEM_TAG      TCAP_PN_PROBLEM_TAG_CCITT

#define TCPUABT_AC_NOT_SUP              TCAP_UABT_AC_NOT_SUP_CCITT
#define TCPUABT_USER_DEFINED            TCAP_UABT_USER_DEFINED_CCITT
#define TCPUABT_DLG_REFUSED             TCAP_UABT_DLG_REFUSED_CCITT

#define TCPPABT_ABNORMAL_DLG            TCAP_PABT_ABNORMAL_DLG_CCITT
#define TCPPABT_NO_COMMON_DLG           TCAP_PABT_NO_COMMON_DLG_CCITT

#define TCPABT_REASON_UNREC_MSG_TYPE            TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT
#define TCPABT_REASON_UNREC_TRANS_ID            TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT
#define TCPABT_REASON_BADLY_STRUCT_TRANS_PORT   TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_CCITT
#define TCPABT_REASON_INCORRECT_TRANS_PORT      TCAP_ABT_REASON_INCORRECT_TRANS_PORT_CCITT
#define TCPABT_REASON_RES_UNAVAIL               TCAP_ABT_REASON_RES_UNAVAIL_CCITT

#define TCPPROB_GENERAL         TCAP_PROB_GENERAL_CCITT
#define TCPPROB_INVOKE          TCAP_PROB_INVOKE_CCITT
#define TCPPROB_RETURN_RES      TCAP_PROB_RETURN_RES_CCITT
#define TCPPROB_RETURN_ERR      TCAP_PROB_RETURN_ERR_CCITT

#define TCPPROB_SPEC_GEN_UNREC_COMP             TCAP_PROB_SPEC_GEN_UNREC_COMP_CCITT
#define TCPPROB_SPEC_GEN_MISTYPED_COMP          TCAP_PROB_SPEC_GEN_MISTYPED_COMP_CCITT
#define TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP      TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_CCITT
#define TCPPROB_SPEC_INV_DUPLICATE_INV_ID       TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_CCITT
#define TCPPROB_SPEC_INV_UNREC_OP_CODE          TCAP_PROB_SPEC_INV_UNREC_OP_CODE_CCITT
#define TCPPROB_SPEC_INV_MISTYPED_PARAM         TCAP_PROB_SPEC_INV_MISTYPED_PARAM_CCITT
#define TCPPROB_SPEC_INV_RESOURCE_LIMIT         TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_CCITT
#define TCPPROB_SPEC_INV_INITIATE_RELEASE       TCAP_PROB_SPEC_INV_INITIATE_RELEASE_CCITT
#define TCPPROB_SPEC_INV_UNREC_LINKED_ID        TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_CCITT
#define TCPPROB_SPEC_INV_UNEXPECTED_LINK_RESP   TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_CCITT
#define TCPPROB_SPEC_INV_UNEXPECTED_LINKED_OP   TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_CCITT
#define TCPPROB_SPEC_RES_UNREC_INVOKE_ID        TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_CCITT
#define TCPPROB_SPEC_RES_UNEXPECTED_RET_RES     TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_CCITT
#define TCPPROB_SPEC_RES_MISTYPED_PARAM         TCAP_PROB_SPEC_RES_MISTYPED_PARAM_CCITT
#define TCPPROB_SPEC_ERR_UNREC_INVOKE_ID        TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_CCITT
#define TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR   TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_CCITT
#define TCPPROB_SPEC_ERR_UNREC_ERROR            TCAP_PROB_SPEC_ERR_UNREC_ERROR_CCITT
#define TCPPROB_SPEC_ERR_UNEXPECTED_ERROR       TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_CCITT
#define TCPPROB_SPEC_ERR_MISTYPED_PARAM         TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_CCITT

/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_TCAP                   ITS_TCAP_CCITT
#define ITS_TCAP_SRC               ITS_TCAP_CCITT_SRC

#elif defined(ANSI)

#define TID_IDENT              TID_IDENT_ANSI
#define PABT_IDENT             PABT_IDENT_ANSI
#define DIALOG_IDENT           DIALOG_IDENT_ANSI
#define CSEQ_IDENT             CSEQ_IDENT_ANSI

#define TCPPT_TC_UNI               TCAP_PT_TC_UNI_ANSI
#define TCPPT_TC_QUERY_W_PERM      TCAP_PT_TC_QUERY_W_PERM_ANSI
#define TCPPT_TC_QUERY_WO_PERM     TCAP_PT_TC_QUERY_WO_PERM_ANSI
#define TCPPT_TC_RESP              TCAP_PT_TC_RESP_ANSI
#define TCPPT_TC_CONV_W_PERM       TCAP_PT_TC_CONV_W_PERM_ANSI
#define TCPPT_TC_CONV_WO_PERM      TCAP_PT_TC_CONV_WO_PERM_ANSI
#define TCPPT_TC_ABORT             TCAP_PT_TC_ABORT_ANSI
#define TCPPT_TC_NOTICE            TCAP_PT_TC_NOTICE_ANSI

#define TCPPT_TC_INVOKE            TCAP_PT_TC_INVOKE_ANSI
#define TCPPT_TC_RESULT_L          TCAP_PT_TC_RESULT_L_ANSI
#define TCPPT_TC_ERROR             TCAP_PT_TC_ERROR_ANSI
#define TCPPT_TC_REJECT            TCAP_PT_TC_REJECT_ANSI
#define TCPPT_TC_INVOKE_NL         TCAP_PT_TC_INVOKE_NL_ANSI
#define TCPPT_TC_RESULT_NL         TCAP_PT_TC_RESULT_NL_ANSI
#define TCPPT_TC_CANCEL            TCAP_PT_TC_CANCEL_ANSI

#define TCPPN_COMPONENT_ID      TCAP_PN_COMPONENT_ID_ANSI
#define TCPPN_INVOKE_TAG        TCAP_PN_COMPONENT_ID_ANSI

#define TCPPN_OCI_NATIONAL_TCAP TCAP_PN_OCI_NATIONAL_TCAP_ANSI
#define TCPPN_OCI_PRIVATE_TCAP  TCAP_PN_OCI_PRIVATE_TCAP_ANSI

#define TCPPN_OF_NOT_USED       TCAP_OF_NOT_USED_ANSI
#define TCPPN_OF_REPLY_REQUIRED TCAP_OF_REPLY_REQUIRED_ANSI
#define TCPPN_OF_PARAMETER      TCAP_OF_PARAMETER_ANSI
#define TCPPN_OF_CHARGING       TCAP_OF_CHARGING_ANSI
#define TCPPN_OF_PROV_INST      TCAP_OF_PROV_INST_ANSI
#define TCPPN_OF_CONN_CTRL      TCAP_OF_CONN_CTRL_ANSI
#define TCPPN_OF_CALLER_INT     TCAP_OF_CALLER_INT_ANSI
#define TCPPN_OF_SEND_NOT       TCAP_OF_SEND_NOT_ANSI
#define TCPPN_OF_NET_MAN        TCAP_OF_NET_MAN_ANSI
#define TCPPN_OF_PROCEDURAL     TCAP_OF_PROCEDURAL_ANSI
#define TCPPN_OF_IS41           TCAP_OF_IS41_ANSI
#define TCPPN_OF_MISC           TCAP_OF_MISC_ANSI
#define TCPPN_OF_RESERVED       TCAP_OF_RESERVED_ANSI

#define TCPPN_OS_NOT_USED       TCAP_OS_NOT_USED_ANSI
#define TCPPN_OS_PROV_VAL       TCAP_OS_PROV_VAL_ANSI
#define TCPPN_OS_SET_VAL        TCAP_OS_SET_VAL_ANSI
#define TCPPN_OS_BILL_CALL      TCAP_OS_BILL_CALL_ANSI
#define TCPPN_OS_START          TCAP_OS_START_ANSI
#define TCPPN_OS_ASSIST         TCAP_OS_ASSIST_ANSI
#define TCPPN_OS_CONN           TCAP_OS_CONN_ANSI
#define TCPPN_OS_TEMP_CONN      TCAP_OS_TEMP_CONN_ANSI
#define TCPPN_OS_DISCONN        TCAP_OS_DISCONN_ANSI
#define TCPPN_OS_FWD_DISCONN    TCAP_OS_FWD_DISCONN_ANSI
#define TCPPN_OS_PLAY_A         TCAP_OS_PLAY_A_ANSI
#define TCPPN_OS_PLAY_A_CD      TCAP_OS_PLAY_A_CD_ANSI
#define TCPPN_OS_AUTO_CALL_GAP  TCAP_OS_AUTO_CALL_GAP_ANSI
#define TCPPN_OS_TEMP_HO        TCAP_OS_TEMP_HO_ANSI
#define TCPPN_OS_RESERVED       TCAP_OS_RESERVED_ANSI

#define TCPABT_REASON_UNREC_PACK_TYPE          TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI
#define TCPABT_REASON_INCORRECT_TRANS_PORT     TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI
#define TCPABT_REASON_BADLY_STRUCT_TRANS_PORT  TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI
#define TCPABT_REASON_UNREC_TRANS_ID           TCAP_ABT_REASON_UNREC_TRANS_ID_ANSI
#define TCPABT_REASON_PERM_TO_RELEASE          TCAP_ABT_REASON_PERM_TO_RELEASE_ANSI
#define TCPABT_REASON_RES_UNAVAIL              TCAP_ABT_REASON_RES_UNAVAIL_ANSI

#define TCPPN_ECI_NATIONAL_TCAP TCAP_PN_ECI_NATIONAL_TCAP_ANSI
#define TCPPN_ECI_PRIVATE_TCAP  TCAP_PN_ECI_PRIVATE_TCAP_ANSI

#define TCPERR_NOT_USED         TCAP_ERR_NOT_USED_ANSI
#define TCPERR_UNEX_COMP_SEQ    TCAP_ERR_UNEX_COMP_SEQ_ANSI
#define TCPERR_UNEX_DATA_VAL    TCAP_ERR_UNEX_DATA_VAL_ANSI
#define TCPERR_UNAV_RESOURCE    TCAP_ERR_UNAV_RESOURCE_ANSI
#define TCPERR_MISSING_REC      TCAP_ERR_MISSING_REC_ANSI
#define TCPERR_REPLY_OVERDUE    TCAP_ERR_REPLY_OVERDUE_ANSI
#define TCPERR_DATA_UNAV        TCAP_ERR_DATA_UNAV_ANSI
#define TCPERR_TSK_RE           TCAP_ERR_TSK_RE_ANSI
#define TCPERR_Q_FULL           TCAP_ERR_Q_FULL_ANSI
#define TCPERR_NO_Q             TCAP_ERR_NO_Q_ANSI
#define TCPERR_TMR_EX           TCAP_ERR_TMR_EX_ANSI
#define TCPERR_DAT_EX           TCAP_ERR_DAT_EX_ANSI
#define TCPERR_UNAUTH           TCAP_ERR_UNAUTH_ANSI
#define TCPERR_NOT_QD           TCAP_ERR_NOT_QD_ANSI
#define TCPERR_UAS_DN           TCAP_ERR_UAS_DN_ANSI
#define TCPERR_SPARE            TCAP_ERR_SPARE_ANSI
#define TCPERR_NOT_AV           TCAP_ERR_NOT_AV_ANSI
#define TCPERR_VMSR_E           TCAP_ERR_VMSR_E_ANSI

#define TCPPROB_IDENT          TCAP_PN_PROB_IDENT_ANSI

#define TCPPROB_NOT_USED       TCAP_PROB_NOT_USED_ANSI
#define TCPPROB_GENERAL        TCAP_PROB_GENERAL_ANSI
#define TCPPROB_INVOKE         TCAP_PROB_INVOKE_ANSI
#define TCPPROB_RETURN_RES     TCAP_PROB_RETURN_RES_ANSI
#define TCPPROB_RETURN_ERR     TCAP_PROB_RETURN_ERR_ANSI
#define TCPPROB_TRANS_PORTION  TCAP_PROB_TRANS_PORTION_ANSI

#define TCPPROB_SPEC_ALL_RESERVED                  TCAP_PROB_SPEC_ALL_RESERVED_ANSI
#define TCPPROB_SPEC_ALL_NOTUSED                   TCAP_PROB_SPEC_ALL_NOTUSED_ANSI
#define TCPPROB_SPEC_GEN_UNREC_COMP                TCAP_PROB_SPEC_GEN_UNREC_COMP_ANSI
#define TCPPROB_SPEC_GEN_INCORRECT_COMP            TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI
#define TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP         TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_ANSI
#define TCPPROB_SPEC_INV_DUPLICATE_INV_ID          TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_ANSI
#define TCPPROB_SPEC_INV_UNREC_OP_CODE             TCAP_PROB_SPEC_INV_UNREC_OP_CODE_ANSI
#define TCPPROB_SPEC_INV_INCORRECT_PARAM           TCAP_PROB_SPEC_INV_INCORRECT_PARAM_ANSI
#define TCPPROB_SPEC_INV_UNREC_COREL_ID            TCAP_PROB_SPEC_INV_UNREC_COREL_ID_ANSI
#define TCPPROB_SPEC_RES_UNREC_COREL_ID            TCAP_PROB_SPEC_RES_UNREC_COREL_ID_ANSI
#define TCPPROB_SPEC_RES_UNEXPECTED_RET_RES        TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_ANSI
#define TCPPROB_SPEC_RES_INCORRECT_PARAM           TCAP_PROB_SPEC_RES_INCORRECT_PARAM_ANSI
#define TCPPROB_SPEC_ERR_UNREC_COREL_ID            TCAP_PROB_SPEC_ERR_UNREC_COREL_ID_ANSI
#define TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR      TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_ANSI
#define TCPPROB_SPEC_ERR_UNREC_ERROR               TCAP_PROB_SPEC_ERR_UNREC_ERROR_ANSI
#define TCPPROB_SPEC_ERR_UNEXPECTED_ERROR          TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_ANSI
#define TCPPROB_SPEC_ERR_INCORRECT_PARAM           TCAP_PROB_SPEC_ERR_INCORRECT_PARAM_ANSI
#define TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE         TCAP_PROB_SPEC_TRANS_UNREC_PACK_TYPE_ANSI
#define TCPPROB_SPEC_TRANS_INCORRECT_TRANS_PORT    TCAP_PROB_SPEC_TRANS_INCORRECT_TRANS_PORT_ANSI
#define TCPPROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT TCAP_PROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT_ANSI
#define TCPPROB_SPEC_TRANS_UNREC_TRANS_ID          TCAP_PROB_SPEC_TRANS_UNREC_TRANS_ID_ANSI
#define TCPPROB_SPEC_TRANS_PERM_TO_RELEASE         TCAP_PROB_SPEC_TRANS_PERM_TO_RELEASE_ANSI
#define TCPPROB_SPEC_TRANS_RES_UNAVAIL             TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI

#define ITS_TCAP                ITS_TCAP_ANSI
#define ITS_TCAP_SRC            ITS_TCAP_ANSI_SRC

#elif defined(PRC)
#define OTID_IDENT             OTID_IDENT_PRC
#define DTID_IDENT             DTID_IDENT_PRC
#define PABT_IDENT             PABT_IDENT_PRC
#define DIALOG_IDENT           DIALOG_IDENT_PRC
#define CSEQ_IDENT             CSEQ_IDENT_PRC

#define TCPPT_TC_UNI           TCAP_PT_TC_UNI_PRC
#define TCPPT_TC_BEGIN         TCAP_PT_TC_BEGIN_PRC
#define TCPPT_TC_END           TCAP_PT_TC_END_PRC
#define TCPPT_TC_CONTINUE      TCAP_PT_TC_CONTINUE_PRC
#define TCPPT_TC_P_ABORT       TCAP_PT_TC_P_ABORT_PRC
#define TCPPT_TC_U_ABORT       TCAP_PT_TC_U_ABORT_PRC
#define TCPPT_TC_NOTICE        TCAP_PT_TC_NOTICE_PRC

#define TCPPT_TC_INVOKE         TCAP_PT_TC_INVOKE_PRC
#define TCPPT_TC_RESULT_L       TCAP_PT_TC_RESULT_L_PRC
#define TCPPT_TC_U_ERROR        TCAP_PT_TC_U_ERROR_PRC
#define TCPPT_TC_R_REJECT       TCAP_PT_TC_R_REJECT_PRC
#define TCPPT_TC_RESULT_NL      TCAP_PT_TC_RESULT_NL_PRC
#define TCPPT_TC_L_CANCEL       TCAP_PT_TC_L_CANCEL_PRC
#define TCPPT_TC_U_CANCEL       TCAP_PT_TC_U_CANCEL_PRC
#define TCPPT_TC_L_REJECT       TCAP_PT_TC_L_REJECT_PRC
#define TCPPT_TC_U_REJECT       TCAP_PT_TC_U_REJECT_PRC
#define TCAP_PT_TC_TIMER_RESET  TCAP_PT_TC_TIMER_RESET_PRC

#define TCPPN_INVOKE_TAG       TCAP_PN_INVOKE_TAG_PRC
#define TCPPN_LOCAL_OP_TAG     TCAP_PN_LOCAL_OP_TAG_PRC 
#define TCPPN_GLOBAL_OP_TAG    TCAP_PN_GLOBAL_OP_TAG_PRC
#define TCPPN_LOCAL_ERR_TAG    TCAP_PN_LOCAL_ERR_TAG_PRC
#define TCPPN_GLOBAL_ERR_TAG   TCAP_PN_GLOBAL_ERR_TAG_PRC
#define TCPPN_PROBLEM_TAG      TCAP_PN_PROBLEM_TAG_PRC

#define TCPUABT_AC_NOT_SUP              TCAP_UABT_AC_NOT_SUP_PRC
#define TCPUABT_USER_DEFINED            TCAP_UABT_USER_DEFINED_PRC
#define TCPUABT_DLG_REFUSED             TCAP_UABT_DLG_REFUSED_PRC

#define TCPPABT_ABNORMAL_DLG            TCAP_PABT_ABNORMAL_DLG_PRC
#define TCPPABT_NO_COMMON_DLG           TCAP_PABT_NO_COMMON_DLG_PRC

#define TCPABT_REASON_UNREC_MSG_TYPE            TCAP_ABT_REASON_UNREC_MSG_TYPE_PRC
#define TCPABT_REASON_UNREC_TRANS_ID            TCAP_ABT_REASON_UNREC_TRANS_ID_PRC
#define TCPABT_REASON_BADLY_STRUCT_TRANS_PORT   TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_PRC
#define TCPABT_REASON_INCORRECT_TRANS_PORT      TCAP_ABT_REASON_INCORRECT_TRANS_PORT_PRC
#define TCPABT_REASON_RES_UNAVAIL               TCAP_ABT_REASON_RES_UNAVAIL_PRC

#define TCPPROB_GENERAL         TCAP_PROB_GENERAL_PRC
#define TCPPROB_INVOKE          TCAP_PROB_INVOKE_PRC
#define TCPPROB_RETURN_RES      TCAP_PROB_RETURN_RES_PRC
#define TCPPROB_RETURN_ERR      TCAP_PROB_RETURN_ERR_PRC

#define TCPPROB_SPEC_GEN_UNREC_COMP             TCAP_PROB_SPEC_GEN_UNREC_COMP_PRC
#define TCPPROB_SPEC_GEN_MISTYPED_COMP          TCAP_PROB_SPEC_GEN_MISTYPED_COMP_PRC
#define TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP      TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_PRC
#define TCPPROB_SPEC_INV_DUPLICATE_INV_ID       TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_PRC
#define TCPPROB_SPEC_INV_UNREC_OP_CODE          TCAP_PROB_SPEC_INV_UNREC_OP_CODE_PRC
#define TCPPROB_SPEC_INV_MISTYPED_PARAM         TCAP_PROB_SPEC_INV_MISTYPED_PARAM_PRC
#define TCPPROB_SPEC_INV_RESOURCE_LIMIT         TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_PRC
#define TCPPROB_SPEC_INV_INITIATE_RELEASE       TCAP_PROB_SPEC_INV_INITIATE_RELEASE_PRC
#define TCPPROB_SPEC_INV_UNREC_LINKED_ID        TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_PRC
#define TCPPROB_SPEC_INV_UNEXPECTED_LINK_RESP   TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_PRC
#define TCPPROB_SPEC_INV_UNEXPECTED_LINKED_OP   TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_PRC
#define TCPPROB_SPEC_RES_UNREC_INVOKE_ID        TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_PRC
#define TCPPROB_SPEC_RES_UNEXPECTED_RET_RES     TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_PRC
#define TCPPROB_SPEC_RES_MISTYPED_PARAM         TCAP_PROB_SPEC_RES_MISTYPED_PARAM_PRC
#define TCPPROB_SPEC_ERR_UNREC_INVOKE_ID        TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_PRC
#define TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR   TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_PRC
#define TCPPROB_SPEC_ERR_UNREC_ERROR            TCAP_PROB_SPEC_ERR_UNREC_ERROR_PRC
#define TCPPROB_SPEC_ERR_UNEXPECTED_ERROR       TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_PRC
#define TCPPROB_SPEC_ERR_MISTYPED_PARAM         TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_PRC

/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_TCAP                   ITS_TCAP_PRC
#define ITS_TCAP_SRC               ITS_TCAP_PRC_SRC

#elif defined(TTC)
#define OTID_IDENT             OTID_IDENT_TTC
#define DTID_IDENT             DTID_IDENT_TTC
#define PABT_IDENT             PABT_IDENT_TTC
#define DIALOG_IDENT           DIALOG_IDENT_TTC
#define CSEQ_IDENT             CSEQ_IDENT_TTC

#define TCPPT_TC_UNI           TCAP_PT_TC_UNI_TTC
#define TCPPT_TC_BEGIN         TCAP_PT_TC_BEGIN_TTC
#define TCPPT_TC_END           TCAP_PT_TC_END_TTC
#define TCPPT_TC_CONTINUE      TCAP_PT_TC_CONTINUE_TTC
#define TCPPT_TC_P_ABORT       TCAP_PT_TC_P_ABORT_TTC
#define TCPPT_TC_U_ABORT       TCAP_PT_TC_U_ABORT_TTC
#define TCPPT_TC_NOTICE        TCAP_PT_TC_NOTICE_TTC

#define TCPPT_TC_INVOKE         TCAP_PT_TC_INVOKE_TTC
#define TCPPT_TC_RESULT_L       TCAP_PT_TC_RESULT_L_TTC
#define TCPPT_TC_U_ERROR        TCAP_PT_TC_U_ERROR_TTC
#define TCPPT_TC_R_REJECT       TCAP_PT_TC_R_REJECT_TTC
#define TCPPT_TC_RESULT_NL      TCAP_PT_TC_RESULT_NL_TTC
#define TCPPT_TC_L_CANCEL       TCAP_PT_TC_L_CANCEL_TTC
#define TCPPT_TC_U_CANCEL       TCAP_PT_TC_U_CANCEL_TTC
#define TCPPT_TC_L_REJECT       TCAP_PT_TC_L_REJECT_TTC
#define TCPPT_TC_U_REJECT       TCAP_PT_TC_U_REJECT_TTC
#define TCAP_PT_TC_TIMER_RESET  TCAP_PT_TC_TIMER_RESET_TTC

#define TCPPN_INVOKE_TAG       TCAP_PN_INVOKE_TAG_TTC
#define TCPPN_LOCAL_OP_TAG     TCAP_PN_LOCAL_OP_TAG_TTC 
#define TCPPN_GLOBAL_OP_TAG    TCAP_PN_GLOBAL_OP_TAG_TTC
#define TCPPN_LOCAL_ERR_TAG    TCAP_PN_LOCAL_ERR_TAG_TTC
#define TCPPN_GLOBAL_ERR_TAG   TCAP_PN_GLOBAL_ERR_TAG_TTC
#define TCPPN_PROBLEM_TAG      TCAP_PN_PROBLEM_TAG_TTC

#define TCPUABT_AC_NOT_SUP              TCAP_UABT_AC_NOT_SUP_TTC
#define TCPUABT_USER_DEFINED            TCAP_UABT_USER_DEFINED_TTC
#define TCPUABT_DLG_REFUSED             TCAP_UABT_DLG_REFUSED_TTC

#define TCPPABT_ABNORMAL_DLG            TCAP_PABT_ABNORMAL_DLG_TTC
#define TCPPABT_NO_COMMON_DLG           TCAP_PABT_NO_COMMON_DLG_TTC

#define TCPABT_REASON_UNREC_MSG_TYPE            TCAP_ABT_REASON_UNREC_MSG_TYPE_TTC
#define TCPABT_REASON_UNREC_TRANS_ID            TCAP_ABT_REASON_UNREC_TRANS_ID_TTC
#define TCPABT_REASON_BADLY_STRUCT_TRANS_PORT   TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_TTC
#define TCPABT_REASON_INCORRECT_TRANS_PORT      TCAP_ABT_REASON_INCORRECT_TRANS_PORT_TTC
#define TCPABT_REASON_RES_UNAVAIL               TCAP_ABT_REASON_RES_UNAVAIL_TTC

#define TCPPROB_GENERAL         TCAP_PROB_GENERAL_TTC
#define TCPPROB_INVOKE          TCAP_PROB_INVOKE_TTC
#define TCPPROB_RETURN_RES      TCAP_PROB_RETURN_RES_TTC
#define TCPPROB_RETURN_ERR      TCAP_PROB_RETURN_ERR_TTC

#define TCPPROB_SPEC_GEN_UNREC_COMP             TCAP_PROB_SPEC_GEN_UNREC_COMP_TTC
#define TCPPROB_SPEC_GEN_MISTYPED_COMP          TCAP_PROB_SPEC_GEN_MISTYPED_COMP_TTC
#define TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP      TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_TTC
#define TCPPROB_SPEC_INV_DUPLICATE_INV_ID       TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_TTC
#define TCPPROB_SPEC_INV_UNREC_OP_CODE          TCAP_PROB_SPEC_INV_UNREC_OP_CODE_TTC
#define TCPPROB_SPEC_INV_MISTYPED_PARAM         TCAP_PROB_SPEC_INV_MISTYPED_PARAM_TTC
#define TCPPROB_SPEC_INV_RESOURCE_LIMIT         TCAP_PROB_SPEC_INV_RESOURCE_LIMIT_TTC
#define TCPPROB_SPEC_INV_INITIATE_RELEASE       TCAP_PROB_SPEC_INV_INITIATE_RELEASE_TTC
#define TCPPROB_SPEC_INV_UNREC_LINKED_ID        TCAP_PROB_SPEC_INV_UNREC_LINKED_ID_TTC
#define TCPPROB_SPEC_INV_UNEXPECTED_LINK_RESP   TCAP_PROB_SPEC_INV_UNEXPECTED_LINK_RESP_TTC
#define TCPPROB_SPEC_INV_UNEXPECTED_LINKED_OP   TCAP_PROB_SPEC_INV_UNEXPECTED_LINKED_OP_TTC
#define TCPPROB_SPEC_RES_UNREC_INVOKE_ID        TCAP_PROB_SPEC_RES_UNREC_INVOKE_ID_TTC
#define TCPPROB_SPEC_RES_UNEXPECTED_RET_RES     TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_TTC
#define TCPPROB_SPEC_RES_MISTYPED_PARAM         TCAP_PROB_SPEC_RES_MISTYPED_PARAM_TTC
#define TCPPROB_SPEC_ERR_UNREC_INVOKE_ID        TCAP_PROB_SPEC_ERR_UNREC_INVOKE_ID_TTC
#define TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR   TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_TTC
#define TCPPROB_SPEC_ERR_UNREC_ERROR            TCAP_PROB_SPEC_ERR_UNREC_ERROR_TTC
#define TCPPROB_SPEC_ERR_UNEXPECTED_ERROR       TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_TTC
#define TCPPROB_SPEC_ERR_MISTYPED_PARAM         TCAP_PROB_SPEC_ERR_MISTYPED_PARAM_TTC

/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_TCAP                   ITS_TCAP_TTC
#define ITS_TCAP_SRC               ITS_TCAP_TTC_SRC

#endif

#if defined(CCITT)
#define TCAP_AllocateDialogueId             TCAP_AllocateDialogueId_CCITT
#define TCAP_SendComponent                  TCAP_SendComponent_CCITT
#define TCAP_SendDialogue                   TCAP_SendDialogue_CCITT
#define TCAP_ReceiveComponent               TCAP_ReceiveComponent_CCITT
#define TCAP_ReceiveDialogue                TCAP_ReceiveDialogue_CCITT
#define TCAP_FetchAddrs                     TCAP_FetchAddrs_CCITT
#define TCAP_SetAddrs                       TCAP_SetAddrs_CCITT
#define TCAP_FetchQOS                       TCAP_FetchQOS_CCITT
#define TCAP_SetQOS                         TCAP_SetQOS_CCITT
#define TCAP_SetVariant                     TCAP_SetVariant_CCITT
#define TCAP_GetVariant                     TCAP_GetVariant_CCITT
#define TCAP_PPrint                         TCAP_PPrint_CCITT
#define TCAP_Variant                        CCITT_TCAP_Variant
#define TCAP_BLUE_BOOK                      CCITT_TCAP_BLUE_BOOK
#define TCAP_WHITE_BOOK                     CCITT_TCAP_WHITE_BOOK
#define TCAP_WHITE_BOOK_97                  CCITT_TCAP_WHITE_BOOK_97
#elif defined(ANSI)
#define TCAP_AllocateDialogueId             TCAP_AllocateDialogueId_ANSI
#define TCAP_SendComponent                  TCAP_SendComponent_ANSI
#define TCAP_SendDialogue                   TCAP_SendDialogue_ANSI
#define TCAP_ReceiveComponent               TCAP_ReceiveComponent_ANSI
#define TCAP_ReceiveDialogue                TCAP_ReceiveDialogue_ANSI
#define TCAP_FetchAddrs                     TCAP_FetchAddrs_ANSI
#define TCAP_SetAddrs                       TCAP_SetAddrs_ANSI
#define TCAP_FetchQOS                       TCAP_FetchQOS_ANSI
#define TCAP_SetQOS                         TCAP_SetQOS_ANSI
#define TCAP_SetVariant                     TCAP_SetVariant_ANSI
#define TCAP_GetVariant                     TCAP_GetVariant_ANSI
#define TCAP_PPrint                         TCAP_PPrint_ANSI
#define TCAP_Variant                        ANSI_TCAP_Variant
#elif defined(PRC)
#define TCAP_AllocateDialogueId             TCAP_AllocateDialogueId_PRC
#define TCAP_SendComponent                  TCAP_SendComponent_PRC
#define TCAP_SendDialogue                   TCAP_SendDialogue_PRC
#define TCAP_ReceiveComponent               TCAP_ReceiveComponent_PRC
#define TCAP_ReceiveDialogue                TCAP_ReceiveDialogue_PRC
#define TCAP_FetchAddrs                     TCAP_FetchAddrs_PRC
#define TCAP_SetAddrs                       TCAP_SetAddrs_PRC
#define TCAP_FetchQOS                       TCAP_FetchQOS_PRC
#define TCAP_SetQOS                         TCAP_SetQOS_PRC
#define TCAP_SetVariant                     TCAP_SetVariant_PRC
#define TCAP_GetVariant                     TCAP_GetVariant_PRC
#define TCAP_PPrint                         TCAP_PPrint_PRC
#define TCAP_Variant                        PRC_TCAP_Variant
#define TCAP_BLUE_BOOK                      PRC_TCAP_BLUE_BOOK
#define TCAP_WHITE_BOOK                     PRC_TCAP_WHITE_BOOK
#define TCAP_WHITE_BOOK_97                  PRC_TCAP_WHITE_BOOK_97
#elif defined(TTC)
#define TCAP_AllocateDialogueId             TCAP_AllocateDialogueId_TTC
#define TCAP_SendComponent                  TCAP_SendComponent_TTC
#define TCAP_SendDialogue                   TCAP_SendDialogue_TTC
#define TCAP_ReceiveComponent               TCAP_ReceiveComponent_TTC
#define TCAP_ReceiveDialogue                TCAP_ReceiveDialogue_TTC
#define TCAP_FetchAddrs                     TCAP_FetchAddrs_TTC
#define TCAP_SetAddrs                       TCAP_SetAddrs_TTC
#define TCAP_FetchQOS                       TCAP_FetchQOS_TTC
#define TCAP_SetQOS                         TCAP_SetQOS_TTC
#define TCAP_SetVariant                     TCAP_SetVariant_TTC
#define TCAP_GetVariant                     TCAP_GetVariant_TTC
#define TCAP_Variant                        TTC_TCAP_Variant
#define TCAP_BLUE_BOOK                      TTC_TCAP_BLUE_BOOK
#define TCAP_WHITE_BOOK                     TTC_TCAP_WHITE_BOOK
#define TCAP_WHITE_BOOK_97                  TTC_TCAP_WHITE_BOOK_97
#else
#error "Protocol family not defined"
#endif

#if defined(CCITT)
#define TCAP_Initialize                     TCAP_Initialize_CCITT
#define TCAP_Terminate                      TCAP_Terminate_CCITT
#define TCAP_ComponentSanityCheck           TCAP_ComponentSanityCheck_CCITT
#define TCAP_DialogueSanityCheck            TCAP_DialogueSanityCheck_CCITT
#define TCAP_VendorComponentSanityCheck     TCAP_VendorComponentSanityCheck_CCITT
#define TCAP_VendorDialogueSanityCheck      TCAP_VendorDialogueSanityCheck_CCITT
#elif defined(ANSI)
#define TCAP_Initialize                     TCAP_Initialize_ANSI
#define TCAP_Terminate                      TCAP_Terminate_ANSI
#define TCAP_ComponentSanityCheck           TCAP_ComponentSanityCheck_ANSI
#define TCAP_DialogueSanityCheck            TCAP_DialogueSanityCheck_ANSI
#define TCAP_VendorComponentSanityCheck     TCAP_VendorComponentSanityCheck_ANSI
#define TCAP_VendorDialogueSanityCheck      TCAP_VendorDialogueSanityCheck_ANSI
#elif defined(PRC)
#define TCAP_Initialize                     TCAP_Initialize_PRC
#define TCAP_Terminate                      TCAP_Terminate_PRC
#define TCAP_ComponentSanityCheck           TCAP_ComponentSanityCheck_PRC
#define TCAP_DialogueSanityCheck            TCAP_DialogueSanityCheck_PRC
#define TCAP_VendorComponentSanityCheck     TCAP_VendorComponentSanityCheck_PRC
#define TCAP_VendorDialogueSanityCheck      TCAP_VendorDialogueSanityCheck_PRC
#elif defined(TTC)
#define TCAP_Initialize                     TCAP_Initialize_TTC
#define TCAP_Terminate                      TCAP_Terminate_TTC
#define TCAP_ComponentSanityCheck           TCAP_ComponentSanityCheck_TTC
#define TCAP_DialogueSanityCheck            TCAP_DialogueSanityCheck_TTC
#define TCAP_VendorComponentSanityCheck     TCAP_VendorComponentSanityCheck_TTC
#define TCAP_VendorDialogueSanityCheck      TCAP_VendorDialogueSanityCheck_TTC
#else
#error "Protocol family not defined"
#endif

#if defined (CCITT)
#define TCAP_GetSub                 TCAP_GetSub_CCITT
#define TCAP_GetTag                 TCAP_GetTag_CCITT
#define TCAP_GetLength              TCAP_GetLength_CCITT
#define TCAP_GetTID                 TCAP_GetTID_CCITT
#define TCAP_SetLength              TCAP_SetLength_CCITT
#elif defined (ANSI)
#define TCAP_GetSub                 TCAP_GetSub_ANSI
#define TCAP_GetTag                 TCAP_GetTag_ANSI
#define TCAP_GetLength              TCAP_GetLength_ANSI
#define TCAP_GetTID                 TCAP_GetTID_ANSI
#define TCAP_SetLength              TCAP_SetLength_ANSI
#elif defined (PRC)
#define TCAP_GetSub                 TCAP_GetSub_PRC
#define TCAP_GetTag                 TCAP_GetTag_PRC
#define TCAP_GetLength              TCAP_GetLength_PRC
#define TCAP_GetTID                 TCAP_GetTID_PRC
#define TCAP_SetLength              TCAP_SetLength_PRC
#elif defined (TTC)
#define TCAP_GetSub                 TCAP_GetSub_TTC
#define TCAP_GetTag                 TCAP_GetTag_TTC
#define TCAP_GetLength              TCAP_GetLength_TTC
#define TCAP_GetTID                 TCAP_GetTID_TTC
#define TCAP_SetLength              TCAP_SetLength_TTC

#else
#error "Protocol family not defined"
#endif


/*
 * * * OSS APIs short names * * *
 */   
#if defined(ANSI)

#define TCAP_OSS_GetGeneralCfg      TCAP_OSS_GetGeneralCfg_ANSI
#define TCAP_OSS_SetGeneralCfg      TCAP_OSS_SetGeneralCfg_ANSI
#define TCAP_OSS_GetBehaviors       TCAP_OSS_GetBehaviors_ANSI
#define TCAP_OSS_SetBehavior        TCAP_OSS_SetBehavior_ANSI
#define TCAP_OSS_GetPegs            TCAP_OSS_GetPegs_ANSI
#define TCAP_OSS_ClearPeg           TCAP_OSS_ClearPeg_ANSI

#elif defined(CCITT) 

#define TCAP_OSS_GetGeneralCfg      TCAP_OSS_GetGeneralCfg_CCITT
#define TCAP_OSS_SetGeneralCfg      TCAP_OSS_SetGeneralCfg_CCITT
#define TCAP_OSS_GetBehaviors       TCAP_OSS_GetBehaviors_CCITT
#define TCAP_OSS_SetBehavior        TCAP_OSS_SetBehavior_CCITT
#define TCAP_OSS_GetPegs            TCAP_OSS_GetPegs_CCITT
#define TCAP_OSS_ClearPeg           TCAP_OSS_ClearPeg_CCITT
#define TCAP_OSS_GetTimers          TCAP_OSS_GetTimers_CCITT
#define TCAP_OSS_SetTimer           TCAP_OSS_SetTimer_CCITT

#elif defined(PRC) 
/* To be defined later */
#elif defined(TTC) 
/* To be defined later */
#endif


#endif /* _ITS_TCAP_SN_H */

