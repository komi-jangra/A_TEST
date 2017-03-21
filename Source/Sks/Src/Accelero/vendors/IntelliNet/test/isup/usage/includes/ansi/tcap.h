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
 * CONTRACT: Daewoo testbed                                                 *
 *                                                                          *
 *     FILE: tcap.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: tcap.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
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
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:35  hbalimid
 * LOG: Get here for demo isup
 * LOG:
 * LOG: Revision 5.6  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.5  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.4  2001/10/18 20:02:52  mmiers
 * LOG: Avoid many version defines, destination parsing.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 19:16:42  mmiers
 * LOG: Get engine in sync, add missing C++ guards in headers.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 00:18:19  mmiers
 * LOG: Start removing the old short names.
 * LOG: Use the heap instead of buffers if the heap implementation is smart.
 * LOG: GCC 3.0 and later are ANSI/ISO C++.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:41  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:28  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:03  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/11/10 18:06:43  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.6  1999/08/19 22:33:10  mmiers
 * LOG:
 * LOG:
 * LOG: Remove dead parameter.
 * LOG:
 * LOG: Revision 1.5  1999/07/28 16:29:23  mmiers
 * LOG:
 * LOG:
 * LOG: Finish making this dual protocol safe.
 * LOG:
 * LOG: Revision 1.4  1999/06/23 22:58:55  mmiers
 * LOG:
 * LOG:
 * LOG: Have to watch where we define extern "C".
 * LOG:
 * LOG: Revision 1.3  1999/06/15 22:41:41  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build for function signatures, predefines.
 * LOG:
 * LOG: Revision 1.2  1999/05/24 20:26:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add codec signatures to headers.
 * LOG:
 * LOG: Revision 1.1  1998/02/10 22:32:08  mmiers
 * LOG: Separate out the PART specific stuff from its.h.  Everything is now in
 * LOG: its appropriate place.  The TCAP headers moved from common to TCAP.  The
 * LOG: state machine code has been added to the tree.
 * LOG:
 * LOG: Revision 1.2  1998/01/28 02:00:59  rsonak
 * LOG: Update from NMS integration.
 * LOG:
 * LOG: Revision 1.1  1998/01/27 15:42:48  mmiers
 * LOG: New files for NMS and ANSI
 * LOG:
 * LOG: Revision 1.1  1998/01/12 15:55:02  mmiers
 * LOG: new file for ANSI
 * LOG:
 * LOG: Revision 1.1.1.1  1997/12/11 17:22:24  rsonak
 * LOG: baseline
 * LOG:
 * LOG: Revision 1.1  1997/12/11 16:43:41  rsonak
 * LOG: New files
 * LOG:
 * LOG:
 * LOG: New file
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_TCAP_ANSI_H
#define _ITS_TCAP_ANSI_H

#ident "$Id: tcap.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

/*
 * This is so ugly I'll duplicate it
 */
#if !defined(TANDEM)

#if !defined(USE_ITU_SCCP)

#include <ansi/sccp.h>

#else /* USE_ITU_SCCP */

#undef ANSI
#if !defined(CCITT)
#define CCITT 1
#endif
#include <itu/sccp.h>
#undef CCITT
#define ANSI 1

#endif /* defined(USE_ITU_SCCP) */

#else /* TANDEM */

#if !defined(USE_ITU_SCCP)

#include <ansisccp>

#else /* USE_ITU_SCCP */

#undef ANSI
#if !defined(CCITT)
#define CCITT 1
#endif
#include <itusccp>
#undef CCITT
#define ANSI 1

#endif /* defined(USE_ITU_SCCP) */

#endif /* TANDEM */

/*
 * Component Sub Layer Primitive Types:
 *
 * Primitives for Dialogue Handling
 * and Component Handling
 */

/*
 * ANSI T1.114 Package Types
 */
#define TCAP_PT_TC_UNI_ANSI           (0xE1U) /* TC-Uni       : UNI structure */
#define TCAP_PT_TC_QUERY_W_PERM_ANSI  (0xE2U) /* TC-Query-WIP : BEGIN structure */
#define TCAP_PT_TC_QUERY_WO_PERM_ANSI (0xE3U) /* TC-Query-WOP : BEGIN structure */
#define TCAP_PT_TC_RESP_ANSI          (0xE4U) /* TC-Resp      : END structure */
#define TCAP_PT_TC_CONV_W_PERM_ANSI   (0xE5U) /* TC-Conv-WIP  : CONTINUE structure */
#define TCAP_PT_TC_CONV_WO_PERM_ANSI  (0xE6U) /* TC-Conv-WOP  : CONTINUE structure */
#define TCAP_PT_TC_ABORT_ANSI         (0xE7U) /* TC-ABORT     : ABORT structure */
#define TCAP_PT_TC_NOTICE_ANSI        (0xE8U) /* TC-Notice    : NOTICE structure */

/*
 * ANSI T1.114 component types
 */
#define TCAP_PT_TC_INVOKE_ANSI        (0xE9U) /* TC-Invoke-L  : INVOKE structure */
#define TCAP_PT_TC_RESULT_L_ANSI      (0xEAU) /* TC-Result-L  : RESULT structure */
#define TCAP_PT_TC_ERROR_ANSI         (0xEBU) /* TC-Error     : ERROR structure */
#define TCAP_PT_TC_REJECT_ANSI        (0xECU) /* TC-Reject    : REJECT structure */
#define TCAP_PT_TC_INVOKE_NL_ANSI     (0xEDU) /* TC-Invoke-NL : INVOKE structure */
#define TCAP_PT_TC_RESULT_NL_ANSI     (0xEEU) /* TC-Result-NL : RESULT structure */
#define TCAP_PT_TC_CANCEL_ANSI        (0xEFU) /* this doesn't exist but
                                               * several vendors use it */
/*
 * Primitive parameter name definitions
 */

/*
 * ANSI T1.114 primitive parameters
 */
#define TCAP_PN_COMPONENT_ID_ANSI      (0xCFU) /* component ID tag */

/*
 * invoke tag identifier
 */
#define TCAP_PN_INVOKE_TAG_ANSI        TCAP_PN_COMPONENT_ID_ANSI

/*
 * operation code identifier
 */
#define TCAP_PN_OCI_NATIONAL_TCAP_ANSI (0xD0U)
#define TCAP_PN_OCI_PRIVATE_TCAP_ANSI  (0xD1U)

/*
 * operation family
 */
#define TCAP_OF_NOT_USED_ANSI       (0x00U)

#define TCAP_OF_REPLY_REQUIRED_ANSI (0x80U)

#define TCAP_OF_PARAMETER_ANSI      (0x01U)
#define TCAP_OF_CHARGING_ANSI       (0x02U)
#define TCAP_OF_PROV_INST_ANSI      (0x03U)
#define TCAP_OF_CONN_CTRL_ANSI      (0x04U)
#define TCAP_OF_CALLER_INT_ANSI     (0x05U)
#define TCAP_OF_SEND_NOT_ANSI       (0x06U)
#define TCAP_OF_NET_MAN_ANSI        (0x07U)
#define TCAP_OF_PROCEDURAL_ANSI     (0x08U)
#define TCAP_OF_IS41_ANSI           (0x09U)

#define TCAP_OF_MISC_ANSI           (0xFEU)
#define TCAP_OF_RESERVED_ANSI       (0xFFU)

/*
 * operation specifier
 */
#define TCAP_OS_NOT_USED_ANSI       (0x00U)

#define TCAP_OS_PROV_VAL_ANSI       (0x01U)
#define TCAP_OS_SET_VAL_ANSI        (0x02U)

#define TCAP_OS_BILL_CALL_ANSI      (0x01U)

#define TCAP_OS_START_ANSI          (0x01U)
#define TCAP_OS_ASSIST_ANSI         (0x02U)

#define TCAP_OS_CONN_ANSI           (0x01U)
#define TCAP_OS_TEMP_CONN_ANSI      (0x02U)
#define TCAP_OS_DISCONN_ANSI        (0x03U)
#define TCAP_OS_FWD_DISCONN_ANSI    (0x04U)

#define TCAP_OS_PLAY_A_ANSI         (0x01U)
#define TCAP_OS_PLAY_A_CD_ANSI      (0x02U)

#define TCAP_OS_AUTO_CALL_GAP_ANSI  (0x01U)

#define TCAP_OS_TEMP_HO_ANSI        (0x01U)

#define TCAP_OS_RESERVED_ANSI       (0xFFU)

/*
 * ANSI T1.114 abort causes
 */
#define TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI              (0x00U)
#define TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI         (0x01U)
#define TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI      (0x02U)
#define TCAP_ABT_REASON_UNREC_TRANS_ID_ANSI               (0x03U)
#define TCAP_ABT_REASON_PERM_TO_RELEASE_ANSI              (0x04U)
#define TCAP_ABT_REASON_RES_UNAVAIL_ANSI                  (0x05U)

/*
 * ANSI T1.114 error code indicators
 */
#define TCAP_PN_ECI_NATIONAL_TCAP_ANSI (0xD3U)
#define TCAP_PN_ECI_PRIVATE_TCAP_ANSI  (0xD4U)

/*
 * ANSI T1.114 error codes
 */
#define TCAP_ERR_NOT_USED_ANSI         (0x00U)
#define TCAP_ERR_UNEX_COMP_SEQ_ANSI    (0x01U)
#define TCAP_ERR_UNEX_DATA_VAL_ANSI    (0x02U)
#define TCAP_ERR_UNAV_RESOURCE_ANSI    (0x03U)
#define TCAP_ERR_MISSING_REC_ANSI      (0x04U)
#define TCAP_ERR_REPLY_OVERDUE_ANSI    (0x05U) /* ANSI-92 (later?) says spare */
#define TCAP_ERR_DATA_UNAV_ANSI        (0x06U)
#define TCAP_ERR_TSK_RE_ANSI           (0x07U) /* not valid for ANSI-88 */
#define TCAP_ERR_Q_FULL_ANSI           (0x08U) /* not valid for ANSI-88 */
#define TCAP_ERR_NO_Q_ANSI             (0x09U) /* not valid for ANSI-88 */
#define TCAP_ERR_TMR_EX_ANSI           (0x0AU) /* not valid for ANSI-88 */
#define TCAP_ERR_DAT_EX_ANSI           (0x0BU) /* not valid for ANSI-88 */
#define TCAP_ERR_UNAUTH_ANSI           (0x0CU) /* not valid for ANSI-88 */
#define TCAP_ERR_NOT_QD_ANSI           (0x0DU) /* not valid for ANSI-88 */
#define TCAP_ERR_UAS_DN_ANSI           (0x0EU) /* not valid for ANSI-88 */
#define TCAP_ERR_SPARE_ANSI            (0x0FU) /* not valid for ANSI-88 */
#define TCAP_ERR_NOT_AV_ANSI           (0x10U) /* not valid for ANSI-88 */
#define TCAP_ERR_VMSR_E_ANSI           (0x11U) /* not valid for ANSI-88 */

/*
 * ANSI T1.114 problem code identifier
 */
#define TCAP_PN_PROB_IDENT_ANSI          (0xD5U)

/*
 * ANSI T1.114 problem types
 */
#define TCAP_PROB_NOT_USED_ANSI       (0x00U)
#define TCAP_PROB_GENERAL_ANSI        (0x01U)
#define TCAP_PROB_INVOKE_ANSI         (0x02U)
#define TCAP_PROB_RETURN_RES_ANSI     (0x03U)
#define TCAP_PROB_RETURN_ERR_ANSI     (0x04U)
#define TCAP_PROB_TRANS_PORTION_ANSI  (0x05U)

/*
 * ANSI T1.114 problem specifiers
 */
#define TCAP_PROB_SPEC_ALL_RESERVED_ANSI                  (0xFFU)
#define TCAP_PROB_SPEC_ALL_NOTUSED_ANSI                   (0x00U)
#define TCAP_PROB_SPEC_GEN_UNREC_COMP_ANSI                (0x01U) 
#define TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI            (0x02U)
#define TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_ANSI         (0x03U)    
#define TCAP_PROB_SPEC_INV_DUPLICATE_INV_ID_ANSI          (0x01U) 
#define TCAP_PROB_SPEC_INV_UNREC_OP_CODE_ANSI             (0x02U) 
#define TCAP_PROB_SPEC_INV_INCORRECT_PARAM_ANSI           (0x03U) 
#define TCAP_PROB_SPEC_INV_UNREC_COREL_ID_ANSI            (0x04U) 
#define TCAP_PROB_SPEC_RES_UNREC_COREL_ID_ANSI            (0x01U) 
#define TCAP_PROB_SPEC_RES_UNEXPECTED_RET_RES_ANSI        (0x02U) 
#define TCAP_PROB_SPEC_RES_INCORRECT_PARAM_ANSI           (0x03U) 
#define TCAP_PROB_SPEC_ERR_UNREC_COREL_ID_ANSI            (0x01U) 
#define TCAP_PROB_SPEC_ERR_UNEXPECTED_RET_ERROR_ANSI      (0x02U) 
#define TCAP_PROB_SPEC_ERR_UNREC_ERROR_ANSI               (0x03U) 
#define TCAP_PROB_SPEC_ERR_UNEXPECTED_ERROR_ANSI          (0x04U) 
#define TCAP_PROB_SPEC_ERR_INCORRECT_PARAM_ANSI           (0x05U) 
#define TCAP_PROB_SPEC_TRANS_UNREC_PACK_TYPE_ANSI         (0x01U) 
#define TCAP_PROB_SPEC_TRANS_INCORRECT_TRANS_PORT_ANSI    (0x02U) 
#define TCAP_PROB_SPEC_TRANS_BADLY_STRUCT_TRANS_PORT_ANSI (0x03U) 
#define TCAP_PROB_SPEC_TRANS_UNREC_TRANS_ID_ANSI          (0x04U) 
#define TCAP_PROB_SPEC_TRANS_PERM_TO_RELEASE_ANSI         (0x05U)
#define TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI             (0x06U)

/*
 * Get the rest from the ITU definitions.
 */
#if !defined(TANDEM)
#include <tcap_cmn.h>
#else /* TANDEM */
#include <tcapcmnh>
#endif /* TANDEM */

/*
 * the use of short names is deprecated and may be removed in
 * a future release.
 */
#if !defined(TANDEM)
#include <tcap_sn.h>
#else /* TANDEM */
#include <tcapsnh>
#endif /* TANDEM */

/*.interface:TCAP
 *****************************************************************************
 *  Interface:
 *      TCAP_*
 *
 *  Purpose:
 *      This interface defines the user's C programming model for TCAP.
 *
 *  Usage:
 *
 *****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

SS7DLLAPI int TCAP_SendComponent_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                      TCAP_CPT *cpt);
SS7DLLAPI int TCAP_ReceiveComponent_ANSI(ITS_HANDLE handle, ITS_EVENT *event,
                                         ITS_HDR *hdr, TCAP_CPT *cpt);

#if !defined(TANDEM)
SS7DLLAPI int TCAP_AllocateDialogueId_ANSI(ITS_HANDLE handle,
                                           ITS_USHORT *dialogue_id);
#else
SS7DLLAPI int TCAP_AllocateDialogueId_ANSI(ITS_UINT *dialogue_id);
#endif

SS7DLLAPI int TCAP_SendDialogue_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                     TCAP_DLG *dlg);
SS7DLLAPI int TCAP_ReceiveDialogue_ANSI(ITS_HANDLE handle, ITS_EVENT *event,
                                        ITS_HDR *hdr, TCAP_DLG *dlg);

/*
 * these functions are not available for all stacks.
 *
 * The meaning of the oaddr and daddr fields depends on the
 * DIR bit (high bit of the dialogue id).  If the DIR bit is
 * set (incoming dialogue), then oaddr is the remote addr.
 * If the DIR bit is clear (outgoing dialogue), then the oaddr
 * is the local addr.  For daddr, the reverse is true.
 * A NULL pointer is an indication to not change the respective
 * address.
 *
 * These functions will fail before a TC-BEGIN is sent or
 * received.  They will fail after a TC-END is sent or
 * received.
 */
SS7DLLAPI int TCAP_FetchAddrs_ANSI(ITS_HANDLE handle, ITS_USHORT did,
                                   SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
SS7DLLAPI int TCAP_SetAddrs_ANSI(ITS_HANDLE handle, ITS_USHORT did,
                                 SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
SS7DLLAPI int TCAP_FetchQOS_ANSI(ITS_HANDLE handle, ITS_USHORT did,
                                 DLG_QOS *qos);
SS7DLLAPI int TCAP_SetQOS_ANSI(ITS_HANDLE handle, ITS_USHORT did,
                               DLG_QOS *qos);

/*
 * this is only for ANSI.  The default variant is '96.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define ANSI_TCAP_1988      ITS_FIRST_GEN
#define ANSI_TCAP_1992      ITS_SECOND_GEN
#define ANSI_TCAP_1996      ITS_THIRD_GEN

SS7DLLAPI int TCAP_SetVariant_ANSI(int variant);
SS7DLLAPI int TCAP_GetVariant_ANSI();

/*
 * this needs to be a well known global to control which TCAP
 * variant is in use.  Users should NOT change this directly
 * (use the functions instead).
 */
SS7DLLAPI extern int  ANSI_TCAP_Variant;

/******************************** TCAP PRIVATE *******************************/

/*
 * users should not invoke these functions
 */
SS7DLLAPI int TCAP_ComponentSanityCheck_ANSI(TCAP_CPT* cpt);
SS7DLLAPI int TCAP_DialogueSanityCheck_ANSI(TCAP_DLG* dlg);

/*
 * these are for vendor implementations to check messages
 * that only originate from the stack.  Users should not
 * call either function directly.
 */
SS7DLLAPI int TCAP_VendorComponentSanityCheck_ANSI(TCAP_CPT* cpt);
SS7DLLAPI int TCAP_VendorDialogueSanityCheck_ANSI(TCAP_DLG* dlg);

#ifdef __cplusplus
}
#endif

#endif /* _ITS_TCAP_ANSI_H */
