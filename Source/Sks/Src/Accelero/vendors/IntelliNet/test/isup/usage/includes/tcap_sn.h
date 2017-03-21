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
 *  ID: $Id: tcap_sn.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:54:34  cvsadmin
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

#ident "$Id: tcap_sn.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

#if defined(CCITT)

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
#else
#error "Protocol family not defined"
#endif

#endif /* _ITS_TCAP_SN_H */

